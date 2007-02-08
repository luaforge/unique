#!BPY

""" Registration info for Blender menus:
Name: 'lUniquE....'
Blender: 241
Group: 'Export'
Tip: 'Export to lUnique data repository.'
"""

__name__="lUnique Export to Lua"
__author__="PhoenixIV"
__url__=["http://unique.luaforge.net/","lUniqueProject"]
__email__=["phoenix11@users.luaforge.net","AuthorEMAIL"]
__version__="0.1.6"

__bpydoc__="""\
This script in an exporter to Unique virtual world files.

Usage:

Run it's from "File->Export" menu.
"""


# $Id: lunique_export.py,v 1.1 2007-02-08 15:29:07 phoenix11 Exp $
#
# +---------------------------------------------------------+

version={'mesh':[0,3,0,4]}
option={'mesh_as_text':0,'export_as_global':0}
msh={'v':1,'n':2,'t':3,'b':4,'f':5,'b':6}
dir={'scn':'scene/','obj':'object/','met':'metric/','nurb':'metric/','mat':'material/','arm':'bones/','tex':'texture/','texdata':'texture/'}
ext={'scn':'.lua','met':'.mesh','nurb':'.nurb','mat':'.lua','obj':'.lua','arm':'.bones','img':'','tex':'.lua','texdata':'.tex'}
objname={'scene':'scene'}

import Blender
from Blender import BGL
#from Blender import *
import sys,time,struct,os,math,types,string

################################### Utility functions ######################################
######### Link info related ##########
#
#  for example:  getLinkInfo('mat','metal') ==> 'script'
#
def getLinkInfo(category,objname):
  for o in Blender.Text.Get():
    if o.getName()==category+'_'+objname:
      s=''
      for l in o.asLines():
        s+=l+'\n'
      return s
  return ''
def getLinkProp(obj):
  s=''
  for p in obj.getAllProperties():
    s+='  '+p.getName()+'='
    t=p.getType()
    d=p.getData()
    if t=='BOOL':
      if d==1:
        s+='true'
      else:
        s+='false'
    elif t=='INT' or t=='FLOAT':
      s+=str(d)
    elif t=='STRING':
      s+='"'+d+'"'
    s+=',\n'
  return s
#    if t=='Boolean'
#    if p.getName()=='shadow' and p.getData()==1:
#      file.write('o.shadow=true\n')
######### File path related ##########
##### Object directory group
def getNameGroup(n):
  dp=n.find('.')
  if dp:
    return n[0:dp]
  else:
    return ''
def getNameObj(n):
  dp=n.find('.')
  if dp:
    return n[dp:]
  else:
    return n
def getNamePath(n):
  n=n.replace('.','/')
  return n
def makeNamePath(p):
  op=0
  pn=''
  while 1:
    sp=p.find('/',op)
    if sp>=op and sp<len(p):
      pn+=p[op:sp]
      try:
        os.mkdir(pn,0755)
      except OSError:
        print('Directory "'+pn+'" exists')
      pn+='/'
      op=sp+1
    else:
      break
def srcPath(n):
  s=Blender.Get("filename")
  sp=s.rfind('/')
  if n[0:2]=="//": n=n[2:]
  return s[:sp]+'/'+n
###### Data files path
def fullPath(n,t):
  return dir[t]+n+ext[t]
def fullNamePath(n,t):
  return fullPath(getNamePath(n),t)
def fullName(n,t):
  return n+ext[t]
def validName(n):
  ret=''
  for i in n:
    if i==',' or i==':': ret=ret+'_'
    elif i=='/': ret=ret+'.'
    else: ret=ret+i
  return ret
def nohierName(n):
  ret=''
  for i in n:
    if i==',' or i==':': ret=ret+'_'
    elif i=='.': ret=ret+'_'
    else: ret=ret+i
  return ret
def toPath(path,tp):
  c=path.find(dir[tp])
  path=path[c+len(dir[tp]):]
  return path
def relPath(path):
  c=path.find(config.set['data_dir']+'/')
  path=path[c+len(config.set['data_dir'])+1:]
  c=path.find('/')
  return path[c+1:]
def fileName(path):
  c=path.rfind("/")
  if not c: c=-1
  e=path.rfind(".")
  return path[c+1:e]
####################################### Exporting ##########################################
def scene_explore(scn):
  os.chdir(config.set['data_dir'])
  scn=validName(scn)
  scnf=fullNamePath(scn,'scn')
  makeNamePath(scnf)
  scf=open(scnf,'w')
  print 'Export scene to \"'+scn+'\" ->'
  scf.write('--------- lUniquE 3D EnginE :: scene `'+scn+'` define file ----------\n'+
            'local s=SCENE()\n'+
            'engine.scene.'+scn+'=s\n'+
            'scene=s\n')
  if config.set['export_obj']:
    scf.write('---- Scene `'+scn+'` objects:\n')
    for obj in Blender.Object.Get():
      if obj.layers.count(1):
        obn=validName(obj.getName())
        obnf=fullNamePath(obn,'obj')
        makeNamePath(obnf)
        obf=open(obnf,'w')
        export_object(obj,obf)
        obf.close()
        scf.write('load(s.object.'+obn+')\n')
    scf.write('---- Scene `'+scn+'` locations:\n')
#    for obj in Blender.Object.Get():
#      if obj.layers.count(1):
#        export_locate(obj,scf)
  scf.write('---- End scene `'+scn+'` ----\n'+
            'scene=nil\n'+
            'return s\n')
  scf.close()
  print '<- End export scene'
  if config.set['export_mat']:
    print 'Export materials ->'
    for mt in Blender.Material.Get():
      export_material(mt)
    print '<- End export materials'
    print '\n\n'
def export_locate(obj,scf):
  if obj.getParent():
    scf.write('s.object.'+scn+'.'+obn+'.locate=s.object.'+scn+'.'+validName(obj.getParent().getName())+'\n')
def export_texture(obj,mf):
  mf.write('--------- lUniquE 3D EnginE :: texture define file ----------\n'+
           '---- Texture \"'+validName(obj.getName())+'\"\n'+
           'local t=TEX2D{\n')
  img=obj.getImage()
  if img:
    fn=srcPath(img.getFilename())
    dn=validName(obj.getName())
    rn=fullNamePath(dn,'texdata')
    makeNamePath(rn)
    dif=open(fn,'r')
    dof=open(rn,'w')
    dof.write(dif.read())
    dif.close()
    dof.close()
    mf.write('  src="'+dn+'",\n')
  mf.write('  filter=TEXTURE.anisotropy,\n')
  mf.write('}\n')
  if option['export_as_global']:
    mf.write('global_scene_texture_'+nohierName(dn)+'=t\n')
  mf.write(getLinkInfo('t',obj.getName())+'\n')
  mf.write('return t\n')
def include_mat(mt,out):
  return
#	out.write('material "'+mt.getName()+ext['mat']+'"\n')
def export_material(mt):
  mtn=validName(mt.getName())
  mtnf=fullNamePath(mtn,'mat')
  print ' Export material \"'+mtn+'\" to \"'+mtnf+'\"'
  makeNamePath(mtnf)
  mtf=open(mtnf,'w')
  mtf.write('--------- lUniquE 3D EnginE :: material define file ----------\n'+
            '---- Material \"'+mtn+'\"\n'+
            'local m=MATERIAL{\n'+
            '  color={\n'+
            '    diffuse='+luaVecs(mt.getRGBCol(),mt.getAlpha())+',\n'+
#            '    ambient='  +luaVecs(,mt.getAmb())+'\n'+
            '    specular='+luaVecs(mt.getSpecCol(),mt.getSpec())+',\n'+
            '    emission='+luaVecs(mt.getEmit(),mt.getEmit(),mt.getEmit(),mt.getEmit())+',\n')
  if mt.getRef()>0:
    mtf.write('    shininess='+str(mt.getRef()*100)+',\n')
  mtf.write('  },\n')
  # Textures
  mtf.write('  texture={\n')
  texunit=0
  for node in mt.getTextures():
    if node:
      mtf.write('    ['+str(texunit)+']='+objname['scene']+'.texture.'+validName(node.tex.getName())+',\n')
      texunit=texunit+1
  mtf.write('  },\n')
  mtf.write('}\n')
  if option['export_as_global']:
    mtf.write('global_scene_material_'+nohierName(mtn)+'=m\n')
  mtf.write(getLinkInfo('m',mtn)+'\n')
  mtf.write('return m\n')
  mtf.close()
  # export textures
  for node in mt.getTextures():
    if node:
      txn=validName(node.tex.getName())
      txnf=fullNamePath(txn,'tex')
      makeNamePath(txnf)
      tf=open(txnf,'w')
      export_texture(node.tex,tf)
      tf.close()

def luaVec(v):
  s='unmath.vec'+str(len(v))+'('+str(v[0])
  for i in range(1,len(v)):
    s=s+', '+str(v[i])
  s=s+')'
  return s

def luaVecs(*a):
  l=0
  for i in a:
    if type(i)==types.ListType:
      l+=len(i)
    else:
      l+=1
  r='unmath.vec'+str(l)+'('
  for i in a:
    if type(i)==types.ListType:
      for k in i:
        r+=str(k)+', '
    else:
      r+=str(i)+', '
  r=r[0:-2]+')'
  return r

def luaMatrix(m):
  s='\n'
  for j in range(0,3):
    for i in range(0,3):
      s+='  '+str(m[j][i])+','
    s+='\n'
  return s[0:-2]
def luaQuat(q):
  from Blender.Mathutils import Quaternion
  from math import sin,cos
  e=q.toEuler()
  e[0]*=0.5
  e[1]*=0.5
  e[2]*=0.5
  q=Quaternion(0,0,sin(e[2]),cos(e[2]))*Quaternion(0,sin(e[1]),0,cos(e[1]))*Quaternion(sin(e[0]),0,0,cos(e[0]))
  return 'unmath.quat('+str(q[0])+', '+str(q[1])+', '+str(q[2])+', '+str(q[3])+')'

def detobjclass(obj):
  obt=obj.getType()
  if   obt=='Mesh':
    return 'MESH'
  elif obt=='Camera':
    return 'CAMERA'
  elif obt=='Lamp':
    return 'LIGHT'
  elif obt=='Effect':
    return 'PARTICLE'
  elif obt=='Curve':
    return 'CURVE'
  elif obt=='Empty':
    return 'GROUP'

def global_location(obj):	
  if obj.getParent():
    return obj.getLocation() #+global_location(obj.getParent())
  else:
    return obj.getLocation()

def export_object(obj,file):
  obn=obj.getName()
  obt=obj.getType()
  obd=obj.getData()
  if obd:
    obc=type(obd)
  else:
    obc='null'
  print ' export object \"'+obn+'\"'
  rot=obj.getEuler().toQuat()
  file.write('--------- lUniquE 3D EnginE :: object define ----------\n'+
             '---- Object \"'+validName(obn)+'\"\n'+
             'local o='+detobjclass(obj)+'{\n'+
             '  pos='+luaVec(global_location(obj))+',\n'+
             '  rot='+luaQuat(rot)+',\n'+
             getLinkProp(obj))
  if   obt=='Mesh':
    if option['mesh_as_text']:
      export_mesh_as_text(obj,file)
    else:
      export_mesh(obj,file)
  elif obt=='Camera':
    export_camera(obj,file)
  elif obt=='Lamp':
    export_light(obj,file)
  elif obt=='Armature':
    export_bones(obj)
  elif obt=='Curve':
    export_curve(obj)
  #file.write('  mat={')
  #for node in obj.getMaterials():
  #  file.write('    '+node.name+'='+objname['scene']+'.material.'+validName(node.getName())+',\n')
  #file.write('  },\n')
  file.write('}\n')
  if option['export_as_global']:
    file.write('global_scene_'+nohierName(obn)+'=o\n')
  # Test only begin
  if obt=='Camera':
    file.write('script"camera"\n'
               'user_camera(o)\n')
  # Test only end
  file.write(getLinkInfo('o',validName(obn))+'\n')
  file.write('return o\n')

def export_bones(obj):
  bf=open(fullPath(obj.getName(),'arm'),'w')
  bf.write('--- armature bones ---\n')
  bf.write('Armature.'+obj.getName()+'={')
  for node in Armature.Get(obj.getName()).getBones():
    bf.write('\n  '+node.getName()+'={\n')
    if node.getParent():
      bf.write('    parent='+node.getParent().getName()+',\n')
    bf.write('    matrix='+luaMatrix(node.getRestMatrix('bonespace'),'    ')+',\n')
    bf.write('    head='+luaVec(node.getHead())+',\n')
    bf.write('    loc='+luaVec(node.getLoc())+',\n')
    bf.write('    quat='+luaQuat(node.getQuat())+'\n')
    bf.write('  },')
  bf.write('\n}--- end armature bones ---\n')
  bf.close()

def export_curve(obj):
  obn=obj.getName()
  obd=obj.getData()
  mf=open(fullPath(obn,'nurb'),'w')
  mf.write('---nurb <'+obn+'> v0.0.1---\n')
  mf.write('_LOAD.'+obn+'={\n')
  mf.write('  class=NURB,\n')
  mf.write('  resol={u='+str(obd.getResolu())+',v='+str(obd.getResolv())+'},\n')
  mf.write('}\n')
  mf.close()

def pack_mesh_chunk(id,el,tp,size,pk,pn):
  if config.set['mesh_fmt']=='text':
    return "chunk={id="+str(id)+",element="+str(el)+",type="+tp+",format="+str(pk)+",compon="+str(pn)+"},\n"
  else:
    return struct.pack('<2IBI3B',id,el,msh[tp],size,pk,pn,14)
def pack_mesh_id(id):
  if config.set['mesh_fmt']=='text':
    return "id="+str(id)+",\n"
  else:
    return struct.pack('I',id)
def pack_version(ver):
  if config.set['mesh_fmt']=='text':
    return "version={"+str(ver[0])+","+str(ver[1])+","+str(ver[2])+","+str(ver[3])+"}\n"
  else:
    return struct.pack('4b',ver[0],ver[1],ver[2],ver[3])
def pack_v(v):
  if config.set['mesh_fmt']=='text':
    r='{'
    for c in v:
      r+=str(c)+","
    r=r[:-1]
    r+='},\n'
    return r
  else:
    r=''
    for c in v:
      r+=struct.pack('f',c)
    return r
def pack_t(v):
  if config.set['mesh_fmt']=='text':
    r='{'
    i=0
    for c in v:
      s=1
      if i==1: s=-1
      r+=str(s*c)+","
      i+=1
    r=r[:-1]
    r+='},\n'
    return r
  else:
    r=''
    i=0
    for c in v:
      s=1
      if i==1: s=-1
      r+=struct.pack('f',s*c)
      i+=1
    return r
def pack_i(v,l):
  if   l==1:
    f='1B'
  elif l==2:
    f='1H'
  else:
    f='1I'
  r=''
  for c in v:
    r+=struct.pack(fmt,i)
  return r

def dump_mesh_smooth(o,d,s,id): # file, meshdata, surface, chunk index
# Output Bloks info
#
# Output Vertexes blok
#  mf.write(pack_mesh_id(1))
#  for v in md.verts:
#    mf.write(pack_v(v))
# Output Normal blok
#  mf.write(pack_mesh_id(2))
#  for v in md.verts:
#    mf.write(pack_v(v.no))
# Output Faces blok
#  if len(md.faces)>0:
#    mf.write(pack_mesh_id(3))
#    for f in md.faces:
#      mf.write(pack_vindex(f.v,fns))
# This code is commented in new version
# Output UV coords
#    if md.faces[0].uv:
#      mf.write(pack_mesh_id(4))
#      uvmap=[]
#      for i in range(len(md.verts)):
#        uvmap.append(0)
#      for f in md.faces:
#        for i in range(len(f.uv)):
#          uvmap[f.v[i].index]=f.uv[i]
#      for i in uvmap:
#        mf.write(pack_v(i))
  return id

def dump_mesh_head_raw(o,d,e,i): # file, meshdata, surface, chunk index
# Output Bloks info
  vert_id=i
  i+=1
  norm_id=i
  i+=1
  texc_id=0
  nv=0
  for f in d.faces:
    if f.mat==e:
      if f.uv:
        texc_id=i
        i+=1
      if len(f.v)==3: nv+=3
      if len(f.v)==4: nv+=6
  print("Export surface head:"+str(i)+" elements:"+str(nv)+"")
  o.write(pack_mesh_chunk(vert_id,e,'v',nv,4,3))
  o.write(pack_mesh_chunk(norm_id,e,'n',nv,4,3))
  if texc_id:
    o.write(pack_mesh_chunk(texc_id,e,'t',nv,4,2))
  return i

def dump_mesh_data_raw(o,d,e,i):
# Gen Bloks info
  vert_id=i
  i+=1
  norm_id=i
  i+=1
  texc_id=0
  nv=0
  for f in d.faces:
    if f.mat==e:
      if f.uv:
        texc_id=i
        i+=1
      if len(f.v)==3: nv+=3
      if len(f.v)==4: nv+=6
  print("Export surface data:"+str(i)+" elements:"+str(nv)+"")
# Write chunk data
  if vert_id:
    o.write(pack_mesh_id(vert_id))
    for f in d.faces:
      if f.mat==e:
        v=f.v
        if len(v)==3:
          o.write(pack_v(v[0])+pack_v(v[1])+pack_v(v[2]))
        if len(v)==4:
          o.write(pack_v(v[0])+pack_v(v[1])+pack_v(v[2])+pack_v(v[2])+pack_v(v[3])+pack_v(v[0]))
  if norm_id:
    o.write(pack_mesh_id(norm_id))
    for f in d.faces:
      if f.mat==e:
        v=f.v
        if f.smooth:
          if len(v)==3:
            o.write(pack_v(v[0].no)+pack_v(v[1].no)+pack_v(v[2].no))
          if len(v)==4:
            o.write(pack_v(v[0].no)+pack_v(v[1].no)+pack_v(v[2].no)+pack_v(v[2].no)+pack_v(v[3].no)+pack_v(v[0].no))
        else:
          no=f.no
          if len(v)==3:
            o.write(pack_v(no)+pack_v(no)+pack_v(no))
          if len(v)==4:
            o.write(pack_v(no)+pack_v(no)+pack_v(no)+pack_v(no)+pack_v(no)+pack_v(no))
  if texc_id:
    o.write(pack_mesh_id(texc_id))
    for f in d.faces:
      if f.mat==e:
        t={}
        for c in range(0,len(f.uv)):
          t[c]={}
          for n in range(0,len(f.uv[c])):
            s=1
            #if n==1: s=-1
            t[c][n]=s*f.uv[c][n]
        #print("len t"+str(len(t)))
        t=f.uv
        if len(t)==3:
          o.write(pack_v(t[0])+pack_v(t[1])+pack_v(t[2]))
        if len(t)==4:
          o.write(pack_v(t[0])+pack_v(t[1])+pack_v(t[2])+pack_v(t[2])+pack_v(t[3])+pack_v(t[0]))
  return i

def export_mesh(obj,file):
# Write header
  id=0
  md=Blender.NMesh.GetRawFromObject(obj.name)
  mn=validName(md.name)
  mp=fullNamePath(mn,'met')
  makeNamePath(mp)
  print('Mesh name:'+mn+' Mesh path:'+mp)
  file.write('  src=\"'+mn+'\",\n')
#  try:
  mf=open(mp,'w')
  mf.write('#!UNMESH')
  mf.write(pack_version(version['mesh']))
# Dump mesh data
  mode=md.getMode()
  surfaces=len(md.materials)
  print("Surfaces:"+str(surfaces))
# Export surfaces per material
  if mode&Blender.NMesh.Modes.AUTOSMOOTH:
    print("With faces")
    for e in range(0,surfaces):
      id=dump_mesh_smooth(mf,md,e,id)
  else:
    print("Without faces")
    id=1
    file.write('  mat={\n')
    for e in range(0,surfaces): # Write header
      file.write('    ['+str(e)+']=scene.material.'+md.materials[e].name+',\n')
      id=dump_mesh_head_raw(mf,md,e,id)
    file.write('  },\n')
    mf.write(pack_mesh_id(0))
# Pick separator
    id=1
    for e in range(0,surfaces): # Write data
      id=dump_mesh_data_raw(mf,md,e,id)
    mf.write(pack_mesh_id(0))
  mf.close()

def export_camera(obj,stm):
  data=obj.getData()
  if data.getType()==0:
    ct='persp'
  else:
    ct='ortho'
  stm.write('  type=CAMERA.'+ct+',\n'+
            '  aspf='+luaVec([data.getClipStart(),data.getClipEnd()])+',\n'+
            '  aspy={x='+str((1-data.getLens()/251)*100)+'},\n')
def export_light(obj,stm):
  data=obj.getData()
  tp=data.getType()
  if   tp==0:
    tn='positional'
  elif tp==1:
    tn='directional'
  elif tp==2:
    tn='positional'
  elif tp==3:
    tn='hemi'
  elif tp==4:
    tn='area'
  stm.write('  type=LIGHT.'+tn+',\n')
  dif=data.col
  dif.append(1.0)
  stm.write('  diffuse='+luaVec(dif)+',\n')

#Window.FileSelector(scene_explore, 'Export SolvEngine LuaScript',Get('filename')[:-6])

import pickle
class Config:
	configfile=".uniquexport"
	set={
		"data_dir":"/home/fenix/devel/unique/data",
		"mesh_fmt":"binary",
		"export_obj":1,
		"export_mat":1,
		"export_gmt":1,
                "export_as_global":1,
	}
	def __init__(self):
		self.load()
		self.save()
	def load(self):
		print("Load settings....")
		try:
			f=open(os.environ["HOME"]+"/"+self.configfile,"r")
		except IOError:
			return
		try:
			self.set=pickle.load(f)
		except EOFError:
			return
		f.close()
	def save(self):
		print("Save settings....")
		f=open(os.environ["HOME"]+"/"+self.configfile,"wb")
		pickle.dump(self.set,f)
		f.close()

# GUI
evn={'exit':1,'export':2,'scenename':3,'data_dir':4,'export_mat':5,'export_obj':6,'export_gmt':7}
gui={'scenename':Blender.Draw.Create(fileName(Blender.Get('filename'))),'data_dir':Blender.Draw.Create(""),'export_mat':Blender.Draw.Create(""),'export_obj':Blender.Draw.Create(""),'export_gmt':Blender.Draw.Create("")}

def draw():
  # Script gui header
  Blender.BGL.glColor3f(1.0,0.0,0.2)
  Blender.BGL.glRasterPos2i(50,180)
  Blender.Draw.Text("Unique 3D engine scene exporter",'large')
  Blender.BGL.glColor3f(0.2,0.0,0.2)
  Blender.BGL.glRasterPos2i(50,150)
  Blender.Draw.Text("version : "+__version__+" for Blender3D (version : "+str(Blender.Get('version'))+")",'small')
	# Preference gui
  Blender.BGL.glColor3f(0.0,0.2,0.0)
  Blender.BGL.glRasterPos2i(10,127)
  Blender.Draw.Text("Root data dir : ",'normal')
  gui['data_dir']=Blender.Draw.String("",evn['data_dir'],100,120,300,24,gui['data_dir'].val,200,"Please enter your root data directory")
  gui['export_mat']=Blender.Draw.Toggle("Export material",evn['export_mat'],10,80,100,24,config.set['export_mat'],"Exporting materials")
  gui['export_obj']=Blender.Draw.Toggle("Export object",evn['export_obj'],120,80,100,24,config.set['export_obj'],"Exporting objects")
  gui['export_gmt']=Blender.Draw.Toggle("Export geometry",evn['export_gmt'],230,80,100,24,config.set['export_gmt'],"Exporting geometry")
  # Exporting gui
  Blender.Draw.Button("Quit",evn['exit'],0,0,60,24,"Press for exiting")
  gui['scenename']=Blender.Draw.String("",evn['scenename'],70,0,200,24,gui['scenename'].val,200,"Please enter your scene name")
  Blender.Draw.Button("Export",evn['export'],280,0,60,24,"Press for exporting")
  #Blender.Draw.String("Press ESC to leave.",62,0)

def expget():
	gui['data_dir'].val=config.set['data_dir']
def expset():
	config.set['data_dir']=gui['data_dir'].val
	config.save()
def event(e,v):
  if not v: return
  if e==Blender.Draw.ESCKEY:
    expset()
    Blender.Draw.Exit()
def bevent(e):
  if e==evn['exit']:
    expset()
    Blender.Draw.Exit()
  if e==evn['export_mat']:
    config.set['export_mat']=not config.set['export_mat']
  if e==evn['export_obj']:
    config.set['export_obj']=not config.set['export_obj']
  if e==evn['export_gmt']:
    config.set['export_gmt']=not config.set['export_gmt']
    Blender.Blender.Redraw(1)
  if e==evn['export']:
    scene_explore(gui['scenename'].val)
    Blender.Redraw(1)

config=Config()
config.set['mesh_fmt']='bin'
expget()
Blender.Draw.Register(draw,event,bevent)
