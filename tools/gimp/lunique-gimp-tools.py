#!/usr/bin/env python

###########################################################################################################
##
## lUnique GIMP texture tool
##
###########################################################################################################

import gimp,gimpplugin
from gimpenums import *
from gimpfu import *
import pygtk
pygtk.require('2.0')
import gtk
import pickle,os

###########################################################################################################
##
## lUnique GIMP texture tool :: common functions section
##
###########################################################################################################

def makepath(p):
    op=0
    pn=''
    while 1:
	sp=p.find('/',op)
	if sp>=op and sp<len(p):
	    pn+=p[op:sp]
	    try:
		os.mkdir(pn,0755)
	    except OSError:
		pass
	#print('Directory "'+pn+'" exists')
	    pn+='/'
	    op=sp+1
	else:
	    break

def range_lock(v,b,e):
    if v<b: return e
    if v>e: return b
    return v
def tobool(v):
    if v=='True':
	return True
    else:
	return False
def toindex(g,v):
    i=0
    for n in g:
	if n.value==v:
	    return i
	i+=1
    return 0

param_prefix="__lUnique_texture_tool__"
def param_is(object,name):
    if object.parasite_find(param_prefix+str(name)):
	return True
    else:
	return False
def param_get(object,name,default):
    p=object.parasite_find(param_prefix+str(name))
    if p==None: return str(default)
    return p.data
def param_set(object,name,value):
    object.attach_new_parasite(param_prefix+str(name),1,str(value))

###########################################################################################################
##
## lUnique GIMP texture tool :: GNU gettext init
##
###########################################################################################################

try:
    import gettext
    catalog = gettext.Catalog('messages')
    _ = catalog.gettext
except IOError, e:
    print("locale error")
    def _(s): return s

###########################################################################################################
##
## lUnique GIMP texture tool :: texture options GUI section
##
###########################################################################################################

class PNGOptions(gtk.HBox):
    param=_("Portable Network Graphics (.png)")
    value="PNG"
    format_param=["Coloured","Grayscale","Indexed"]
    format_value=["c","g","i"]
    numofc_value=[32,1,256,1,16]
    compress_value=[9,1,9,1,2]
    def on_format_changed(self,o):
	if self.format_value[self.combo_format.get_active()]=="i":
	    self.spin_numofc.show()
	else:
	    self.spin_numofc.hide()
    def load(self,o): # PNG_format, PNG_numofc (for indexed), PNG_compress
	self.combo_format.set_active(self.format_value.index(param_get(o,"PNG_format",self.format_value[0])))
	self.spin_numofc.set_value(int(param_get(o,"PNG_numofc",self.numofc_value[0])))
	self.spin_compress.set_value(int(param_get(o,"PNG_compress",self.compress_value[0])))
    def save(self,o):
	param_set(o,"PNG_format",self.format_value[self.combo_format.get_active()])
	param_set(o,"PNG_numofc",str(int(self.spin_numofc.get_value())))
	param_set(o,"PNG_compress",str(int(self.spin_compress.get_value())))
    def __init__(self):
	gtk.HBox.__init__(self)
	# LEFT CELL
	left_cell=gtk.VBox()
	self.pack_start(left_cell)
	# RIGHT CELL
	right_cell=gtk.VBox()
	self.pack_end(right_cell)
	# format
	self.label_format=gtk.Label(_("Format:"))
	left_cell.pack_start(self.label_format)
	self.combo_format=gtk.combo_box_new_text()
	for n in self.format_param: self.combo_format.append_text(n)
	right_cell.pack_start(self.combo_format)
	self.combo_format.connect("changed",self.on_format_changed)
	# num of colors
	self.label_numofc=gtk.Label(_("Num of colors:"))
	left_cell.pack_start(self.label_numofc)
	self.spin_numofc=gtk.SpinButton(gtk.Adjustment(self.numofc_value[0],
						       self.numofc_value[1],
						       self.numofc_value[2],
						       self.numofc_value[3],
						       self.numofc_value[4]))
	right_cell.pack_start(self.spin_numofc)
	# compress level
	self.label_compress=gtk.Label(_("Compression level:"))
	left_cell.pack_start(self.label_compress)
	self.spin_compress=gtk.SpinButton(gtk.Adjustment(self.compress_value[0],
							 self.compress_value[1],
							 self.compress_value[2],
							 self.compress_value[3],
							 self.compress_value[4]))
	right_cell.pack_start(self.spin_compress)
class JPGOptions(gtk.HBox):
    param=_("Joint Photographic Experts Group (.jpg)")
    value="JPG"
    format_param=["Coloured","Grayscale"]
    format_value=["c","g"]
    quality_value=[85,1,100,1,10]
    def load(self,o): # JPG_format, JPG_quality
	self.combo_format.set_active(self.format_value.index(param_get(o,"JPG_format",self.format_value[0])))
	self.spin_quality.set_value(int(param_get(o,"JPG_quality",self.quality_value[0])))
    def save(self,o):
	param_set(o,"JPG_format",self.format_value[self.combo_format.get_active()])
	param_set(o,"JPG_quality",str(int(self.spin_quality.get_value())))
    def __init__(self):
	gtk.HBox.__init__(self)
	# LEFT CELL
	left_cell=gtk.VBox()
	self.pack_start(left_cell)
	# RIGHT CELL
	right_cell=gtk.VBox()
	self.pack_end(right_cell)
	# format
	self.label_format=gtk.Label(_("Format:"))
	left_cell.pack_start(self.label_format)
	self.combo_format=gtk.combo_box_new_text()
	for n in self.format_param: self.combo_format.append_text(n)
	right_cell.pack_start(self.combo_format)
	# quality
	self.label_quality=gtk.Label(_("Quality[%]:"))
	left_cell.pack_start(self.label_quality)
	self.spin_quality=gtk.SpinButton(gtk.Adjustment(self.quality_value[0],
							self.quality_value[1],
							self.quality_value[2],
							self.quality_value[3],
							self.quality_value[4]))
	right_cell.pack_start(self.spin_quality)
class TextureOptionsDialog(gtk.Dialog):
    type_param=[_("Diffuse map"),
		_("Relief map"),
		_("Specular map"),
		_("Mixed map")]
    type_value=["d","r","s","m"]
    size_param=[2,4,8,16,32,64,128,256,512,1024,2048,4096,8192]
    size_value=[2,2,8192,1,2]
    format_file=[PNGOptions,JPGOptions]
    format_option=[]
    def on_toggle_state_clicked(self,o):
	if o.get_active():
	    self.common.show_all()
	    self.on_format_changed(0)
	else:
	    self.common.hide_all()
	    self.on_format_changed(0)
    def on_format_changed(self,o):
	for o in self.format_option:
	    if self.format_option.index(o)==self.combo_format.get_active() \
		    and self.toggle_state.get_active(): o.show_all()
	    else: o.hide_all()
    def on_size_changed(self,o):
	v=int(o.get_value())
	d=v-o.prev_value
	if d==self.size_value[3]:
	    o.prev_value=self.size_param[range_lock(self.size_param.index(o.prev_value)+self.size_value[3],
						   0,len(self.size_param)-1)]
	    o.set_value(o.prev_value)
	    return
	if d==-self.size_value[3]:
	    o.prev_value=self.size_param[range_lock(self.size_param.index(o.prev_value)-self.size_value[3],
						   0,len(self.size_param)-1)]
	    o.set_value(o.prev_value)
	    return
	if d==self.size_value[4]:
	    o.prev_value=self.size_param[range_lock(self.size_param.index(o.prev_value)+self.size_value[4],
						   0,len(self.size_param)-1)]
	    o.set_value(o.prev_value)
	    return
	if d==-self.size_value[4]:
	    o.prev_value=self.size_param[range_lock(self.size_param.index(o.prev_value)-self.size_value[4],
						   0,len(self.size_param)-1)]
	    o.set_value(o.prev_value)
	    return
	for i in range(1,len(self.size_param)-1):
	    if self.size_param[i-1]<v and v<self.size_param[i]:
		if v-self.size_param[i-1]>self.size_param[i]-v:
		    o.set_value(self.size_param[i])
		else:
		    o.set_value(self.size_param[i-1])
	o.prev_value=v
    def load(self,o): # Load settings: state,type,format
	# SET PARAMETERS
	self.toggle_state.set_active(tobool(param_get(o,"state","False")))
	self.combo_type.set_active(self.type_value.index(param_get(o,"type",self.type_value[0])))
	self.combo_format.set_active(toindex(self.format_file,param_get(o,"format",self.format_option[0].value)))
	self.spin_width.set_value(float(param_get(o,"width",o.width)))
	self.spin_height.set_value(float(param_get(o,"height",o.height)))
	for n in self.format_option: n.load(o)
    def save(self,o):
	#str(state) str(type) str(format)
	param_set(o,"state",str(self.toggle_state.get_active()))
	param_set(o,"type",self.type_value[self.combo_type.get_active()])
	param_set(o,"format",self.format_file[self.combo_format.get_active()].value)
	param_set(o,"width",str(self.spin_width.get_value()))
	param_set(o,"height",str(self.spin_height.get_value()))
	for n in self.format_option: n.save(o)
    def __init__(self):
	# Init dialog
	gtk.Dialog.__init__(self,_("Texture option"),None,0,
			    (gtk.STOCK_CANCEL,
			     gtk.RESPONSE_CANCEL,
			     gtk.STOCK_OK,
			     gtk.RESPONSE_OK))
	# texture state
	self.toggle_state=gtk.CheckButton(_("Enable texture map"))
	self.toggle_state.connect("clicked",self.on_toggle_state_clicked)
	self.vbox.pack_start(self.toggle_state)
	# TOP PANEL (self.common)
	pannel_top=gtk.HBox()
	self.vbox.pack_start(pannel_top)
	self.common=pannel_top
	# BOTTOM PANEL (self.special)
	pannel_bottom=gtk.HBox()
	self.vbox.pack_start(pannel_bottom)
	self.special=pannel_bottom
	# TOP LEFT CELL
	top_left=gtk.VBox()
	pannel_top.pack_start(top_left)
	# TOP RIGHT CELL
	top_right=gtk.VBox()
	pannel_top.pack_start(top_right)
	# texture map type
	label_type=gtk.Label(_("Texture type:"))
	top_left.pack_start(label_type)
	self.combo_type=gtk.combo_box_new_text()
	for n in self.type_param: self.combo_type.append_text(n)
	top_right.pack_start(self.combo_type)
	# texture file format
	label_format=gtk.Label(_("Texture format:"))
	top_left.pack_start(label_format)
	self.combo_format=gtk.combo_box_new_text()
	for n in self.format_file: self.combo_format.append_text(n.param)
	top_right.pack_start(self.combo_format)
	self.combo_format.connect("changed",self.on_format_changed)
	# format specified option boxes
	for o in self.format_file:
	    self.format_option.append(o())
	    self.vbox.pack_start(self.format_option[len(self.format_option)-1])
	# texture width
	label_width=gtk.Label(_("Texture width:"))
	top_left.pack_start(label_width)
	self.spin_width=gtk.SpinButton(gtk.Adjustment(self.size_value[0],
						      self.size_value[1],
						      self.size_value[2],
						      self.size_value[3],
						      self.size_value[4]))
	self.spin_width.connect("value-changed",self.on_size_changed)
	self.spin_width.prev_value=self.size_value[0]
	top_right.pack_start(self.spin_width)
	# texture height
	label_height=gtk.Label(_("Texture height:"))
	top_left.pack_start(label_height)
	self.spin_height=gtk.SpinButton(gtk.Adjustment(self.size_value[0],
						       self.size_value[1],
						       self.size_value[2],
						       self.size_value[3],
						       self.size_value[4]))
	self.spin_height.connect("value-changed",self.on_size_changed)
	self.spin_height.prev_value=self.size_value[0]
	top_right.pack_start(self.spin_height)
	# show all
	self.toggle_state.show()

###########################################################################################################
##
## lUnique GIMP texture tool :: texture export GUI section
##
###########################################################################################################

class TextureExportOptions:
    configfile=".lUnique_texture_tool.rc"
    set={
	"path":os.environ["HOME"],
	"level":0,
	"limit":0,
    }
    def load(self):
	try:
	    f=open(os.environ["HOME"]+"/"+self.configfile,"r")
	except IOError:
	    return
	try:
	    new_set=pickle.load(f)
	except EOFError:
	    return
	for k in new_set: self.set[k]=new_set[k]
	f.close()
    def save(self):
	try:
	    f=open(os.environ["HOME"]+"/"+self.configfile,"wb")
	except EOFError:
	    return
	try:
	    pickle.dump(self.set,f)
	except EOFError:
	    return
	f.close()
	pass

class TextureExportDialog(gtk.Dialog,TextureExportOptions):
    level_value=[0,0,12,1,3]
    limit_value=[0,0,12,1,3]
    def __init__(self):
	# Init dialog
	gtk.Dialog.__init__(self,_("Texture export"),None,0,
			    (gtk.STOCK_CANCEL,
			     gtk.RESPONSE_CANCEL,
			     gtk.STOCK_OK,
			     gtk.RESPONSE_OK))
	# parameters group
	main_panel=gtk.HBox()
	self.vbox.pack_start(main_panel)
	left_cell=gtk.VBox()
	main_panel.pack_start(left_cell)
	right_cell=gtk.VBox()
	main_panel.pack_end(right_cell)
	# path selector
	label_path=gtk.Label(_("Export path:"))
	left_cell.pack_start(label_path)
	dialog_path=gtk.FileChooserDialog(_("Select path to export texture"),None,
					  gtk.FILE_CHOOSER_ACTION_SELECT_FOLDER,
					  (gtk.STOCK_CANCEL,
					   gtk.RESPONSE_CANCEL,
					   gtk.STOCK_OPEN,
					   gtk.RESPONSE_ACCEPT))
	self.select_path=gtk.FileChooserButton(dialog_path)
	right_cell.pack_start(self.select_path)
	# change level
	label_level=gtk.Label(_("Detail level:"))
	left_cell.pack_start(label_level)
	self.spin_level=gtk.SpinButton(gtk.Adjustment(self.level_value[0],
						      self.level_value[1],
						      self.level_value[2],
						      self.level_value[3],
						      self.level_value[4]))
	right_cell.pack_start(self.spin_level)
	# change limit
	label_limit=gtk.Label(_("Detail limit:"))
	left_cell.pack_start(label_limit)
	self.spin_limit=gtk.SpinButton(gtk.Adjustment(self.limit_value[0],
						      self.limit_value[1],
						      self.limit_value[2],
						      self.limit_value[3],
						      self.limit_value[4]))
	right_cell.pack_start(self.spin_limit)
    def load(self):
	TextureExportOptions.load(self)
	self.select_path.set_filename(self.set["path"])
	self.spin_level.set_value(self.set["level"])
	self.spin_limit.set_value(self.set["limit"])
    def save(self):
	self.set["path"]=self.select_path.get_filename()
	self.set["level"]=int(self.spin_level.get_value())
	self.set["limit"]=int(self.spin_limit.get_value())
	TextureExportOptions.save(self)
    def show(self):
	self.show_all()

###########################################################################################################
##
## lUnique GIMP texture tool :: texture export section
##
###########################################################################################################

class PNGExport:
    param="PNG"
    comment="This texture automatically generated by lUnique texture tool for GIMP"
    def type(self,t):
	if t=="c":
	    return RGB
	if t=="g":
	    return GRAY
	if t=="i":
	    return INDEXED
	return RGB
    def export(self,image,drawable,filename,o):
	format=self.type(param_get(o,"PNG_format","c"))
	numofc=int(float(param_get(o,"PNG_numofc",256)))
	compress=int(float(param_get(o,"PNG_compress",9)))
	if format!=image.base_type:
	    if format==RGB:
		pdb.gimp_image_convert_rgb(image)
	    if format==GRAY:
		pdb.gimp_image_convert_grayscale(image)
	    if format==INDEXED:
		pdb.gimp_image_convert_indexed(image,NO_DITHER,MAKE_PALETTE,numofc,NO_DITHER,0,0)
	interlace,compression,bkgd,gama,offs,phys,time,comment,svtrans=pdb.file_png_get_defaults()
	compression=compress
	#comment=self.comment
	pdb.file_png_save2(image,drawable,filename,filename,interlace,
			   compression,bkgd,gama,offs,phys,time,comment,svtrans)
class JPGExport:
    param="JPG"
    comment="This texture automatically generated by lUnique texture tool for GIMP"
    def type(self,t):
	if t=="c":
	    return RGB
	if t=="g":
	    return GRAY
	return RGB
    def export(self,image,drawable,filename,o):
	format=self.type(param_get(o,"JPG_format","c"))
	quality=float(param_get(o,"JPG_quality",85))/100
	if format!=image.base_type:
	    if format==RGB:
		pdb.gimp_image_convert_rgb(image)
	    if format==GRAY:
		pdb.gimp_image_convert_grayscale(image)
	comment=self.comment
	pdb.file_jpeg_save(image,drawable,filename,filename,quality,0,1,0,comment,0,1,0,0)
def level_lock(value,level,limit):
    limit+=1
    for i in range(0,level):
	new_value=int(value/2)
	if new_value<2**limit:
	    return int(value)
	value=new_value
    return int(value)
class TextureExport:
    extension=".tex"
    format_file=[PNGExport,JPGExport]
    format_option=[]
    def __init__(self):
	for n in self.format_file:
	    self.format_option.append(n())
    def export(self,drawable,path,level,limit):
	# filename processing
	filename=drawable.image.name
	b=filename.rfind("/")
	if 0<b and b<len(filename): filename=filename[b+1:]
	e=filename.rfind(".")
	if 0<e and e<len(filename): filename=filename[:e]
	filename=filename.replace(".","/")
	type=param_get(drawable,"type","_")
	filename=path+"/"+filename
	makepath(filename)
	filename=filename+""+type+self.extension
	# image processing
	image=gimp.Image(drawable.width,drawable.height,drawable.image.base_type)
	#image.add_layer(drawable.copy(),0) # doesn't not work
	drawable_copy=pdb.gimp_layer_new_from_drawable(drawable,image)
	pdb.gimp_image_add_layer(image,drawable_copy,0)
	width=level_lock(int(float(param_get(drawable,"width",512))),level,limit)
	height=level_lock(int(float(param_get(drawable,"height",512))),level,limit)
	pdb.gimp_image_scale(image,width,height)
	format=param_get(drawable,"format","NON")
	for n in self.format_option:
	    if n.param==format:
		#gimp.message("Export format:"+format)
		n.export(image,drawable_copy,filename,drawable)
	gimp.delete(image)

###########################################################################################################
##
## lUnique GIMP texture tool :: plug-in registry section
##
###########################################################################################################

class lunique_plugin(gimpplugin.plugin):
    '''The main plugin class defines and installs the lunique_tool function.'''
    version='0.0.3'
    def init(self): # initialisation routines called when gimp starts.
	return
    def quit(self): # clean up routines called when gimp exits (normally).
	return
    def query(self): # called to find what functionality the plugin provides.
	gimp.install_procedure("lunique_texture_option",
			       "Set texture option",
			       "set texture option",
			       "Phoenix kayo",
			       "RareSky Sonarium",
                               "2006-2007",
			       "<Image>/lUnique/Texture _option",
			       "RGB*, GRAY*, ,INDEXED*",
			       PLUGIN,
                               [(PDB_INT32, "run-mode", "interactive/noninteractive"),
				(PDB_IMAGE,"image","The image to work on"),
				(PDB_DRAWABLE,"drawable","The drawable to work on")],
			       [])
	gimp.install_procedure("lunique_texture_export",
			       "Export textures for the lUnique engine",
			       "Export textures for the lUnique engine",
			       "Phoenix 11 Kayo",
			       "Phoenix 11 Kayo",
			       "2005-2007",
			       "<Image>/lUnique/Texture _export",
			       "RGB*, GRAY*, ,INDEXED*",
			       PLUGIN,
			       [(PDB_INT32,"run-mode","interactive/noninteractive"),
				(PDB_IMAGE,"image","The image to work on"),
				(PDB_DRAWABLE,"drawable","dummy")],
			       [])
	gimp.install_procedure("lunique_texture_export_batch",
			       "Export textures for the lUnique engine",
			       "Export textures for the lUnique engine",
			       "Phoenix 11 Kayo",
			       "Phoenix 11 Kayo",
			       "2005-2007",
			       "",
			       "RGB*, GRAY*, INDEXED*",
			       PLUGIN,
			       [(PDB_INT32,"run-mode","dummy"),
				(PDB_IMAGE,"image","dummy"),
				(PDB_DRAWABLE,"drawable","dummy"),
				(PDB_STRING,"filename","Path to .xcf file")],
			       [])
        # note that this method name matches the first arg of
        # gimp.install_procedure	
    def lunique_texture_option(self,mode,image,drawable): # do what ever this plugin should do
	# gui create
	if mode==RUN_INTERACTIVE:
	    dialog=TextureOptionsDialog()
	    # run dialog
	    dialog.show()
	    dialog.load(drawable)
	    if dialog.run()==gtk.RESPONSE_OK:
		dialog.save(drawable)
	    # gui destroy
	    dialog.destroy()
	if mode==RUN_NONINTERACTIVE:
	    gimp.message("Please call texture options dialog from lUnique > texture option")
    def lunique_texture_export(self,mode,image,drawable,path="",level=0,limit=0): # do what ever this plugin should do
	if mode==RUN_INTERACTIVE:
	    # create gui
	    dialog=TextureExportDialog()
	    # run dialog
	    dialog.show()
	    dialog.load()
	    if dialog.run()==gtk.RESPONSE_OK:
		dialog.save()
		self.lunique_texture_export(RUN_NONINTERACTIVE,image,drawable,
					    dialog.set["path"],dialog.set["level"],dialog.set["limit"])
	    # gui destroy
	    dialog.destroy()
	if mode==RUN_NONINTERACTIVE:
	    for layer in image.layers:
		if param_is(layer,"state"):
		    self.lunique_export_texture_map(mode,image,layer,path,level,limit)
    def lunique_export_texture_map(self,mode,image,drawable,path="",level=0,limit=0):
	#gimp.message(drawable.name)
	map=TextureExport()
	map.export(drawable,path,level,limit)
    def lunique_texture_export_batch(self,mode,image,drawable,filename):
	opt=TextureExportOptions()
	opt.load()
	image=pdb.gimp_xcf_load(0,filename,filename)
	self.lunique_texture_export(RUN_NONINTERACTIVE,image,0,
				    opt.set["path"],opt.set["level"],opt.set["limit"])
	gimp.delete(image)

###########################################################################################################
##
## lUnique GIMP texture tool :: main code section
##
###########################################################################################################

def fail(msg):
    '''Display and error message and quit'''
    gimp.message(msg)
    raise error, msg

if __name__ == '__main__': lunique_plugin().start()
