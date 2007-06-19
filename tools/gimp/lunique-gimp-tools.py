#!/usr/bin/env python

###########################################################################################################
##
## lUnique GIMP texture tool
##
###########################################################################################################

__program__="lUnique GIMP Texture Tools"
__version__="0.1.4-beta"
__developer__="PhoeniX11 Kayo <phoenix11@users.luaforge.net>"
__documentator__="Konstantin Kirik <snegovick@users.luaforge.net>"
__website__="http://unique.luaforge.net"
__date__="2007-06-09"
__copyright__="Copyleft (L) 2007 RareSky lUnique"
__license__="""
		    GNU GENERAL PUBLIC LICENSE
		       Version 2, June 1991

 Copyright (C) 1989, 1991 Free Software Foundation, Inc.
                          675 Mass Ave, Cambridge, MA 02139, USA
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.

			    Preamble

  The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
License is intended to guarantee your freedom to share and change free
software--to make sure the software is free for all its users.  This
General Public License applies to most of the Free Software
Foundation's software and to any other program whose authors commit to
using it.  (Some other Free Software Foundation software is covered by
the GNU Library General Public License instead.)  You can apply it to
your programs, too.

  When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
this service if you wish), that you receive source code or can get it
if you want it, that you can change the software or use pieces of it
in new free programs; and that you know you can do these things.

  To protect your rights, we need to make restrictions that forbid
anyone to deny you these rights or to ask you to surrender the rights.
These restrictions translate to certain responsibilities for you if you
distribute copies of the software, or if you modify it.

  For example, if you distribute copies of such a program, whether
gratis or for a fee, you must give the recipients all the rights that
you have.  You must make sure that they, too, receive or can get the
source code.  And you must show them these terms so they know their
rights.

  We protect your rights with two steps: (1) copyright the software, and
(2) offer you this license which gives you legal permission to copy,
distribute and/or modify the software.

  Also, for each author's protection and ours, we want to make certain
that everyone understands that there is no warranty for this free
software.  If the software is modified by someone else and passed on, we
want its recipients to know that what they have is not the original, so
that any problems introduced by others will not reflect on the original
authors' reputations.

  Finally, any free program is threatened constantly by software
patents.  We wish to avoid the danger that redistributors of a free
program will individually obtain patent licenses, in effect making the
program proprietary.  To prevent this, we have made it clear that any
patent must be licensed for everyone's free use or not licensed at all.

  The precise terms and conditions for copying, distribution and
modification follow.

		    GNU GENERAL PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. This License applies to any program or other work which contains
a notice placed by the copyright holder saying it may be distributed
under the terms of this General Public License.  The "Program", below,
refers to any such program or work, and a "work based on the Program"
means either the Program or any derivative work under copyright law:
that is to say, a work containing the Program or a portion of it,
either verbatim or with modifications and/or translated into another
language.  (Hereinafter, translation is included without limitation in
the term "modification".)  Each licensee is addressed as "you".

Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running the Program is not restricted, and the output from the Program
is covered only if its contents constitute a work based on the
Program (independent of having been made by running the Program).
Whether that is true depends on what the Program does.

  1. You may copy and distribute verbatim copies of the Program's
source code as you receive it, in any medium, provided that you
conspicuously and appropriately publish on each copy an appropriate
copyright notice and disclaimer of warranty; keep intact all the
notices that refer to this License and to the absence of any warranty;
and give any other recipients of the Program a copy of this License
along with the Program.

You may charge a fee for the physical act of transferring a copy, and
you may at your option offer warranty protection in exchange for a fee.

  2. You may modify your copy or copies of the Program or any portion
of it, thus forming a work based on the Program, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions:

    a) You must cause the modified files to carry prominent notices
    stating that you changed the files and the date of any change.

    b) You must cause any work that you distribute or publish, that in
    whole or in part contains or is derived from the Program or any
    part thereof, to be licensed as a whole at no charge to all third
    parties under the terms of this License.

    c) If the modified program normally reads commands interactively
    when run, you must cause it, when started running for such
    interactive use in the most ordinary way, to print or display an
    announcement including an appropriate copyright notice and a
    notice that there is no warranty (or else, saying that you provide
    a warranty) and that users may redistribute the program under
    these conditions, and telling the user how to view a copy of this
    License.  (Exception: if the Program itself is interactive but
    does not normally print such an announcement, your work based on
    the Program is not required to print an announcement.)

These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Program,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Program, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote it.

Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Program.

In addition, mere aggregation of another work not based on the Program
with the Program (or with a work based on the Program) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.

  3. You may copy and distribute the Program (or a work based on it,
under Section 2) in object code or executable form under the terms of
Sections 1 and 2 above provided that you also do one of the following:

    a) Accompany it with the complete corresponding machine-readable
    source code, which must be distributed under the terms of Sections
    1 and 2 above on a medium customarily used for software interchange; or,

    b) Accompany it with a written offer, valid for at least three
    years, to give any third party, for a charge no more than your
    cost of physically performing source distribution, a complete
    machine-readable copy of the corresponding source code, to be
    distributed under the terms of Sections 1 and 2 above on a medium
    customarily used for software interchange; or,

    c) Accompany it with the information you received as to the offer
    to distribute corresponding source code.  (This alternative is
    allowed only for noncommercial distribution and only if you
    received the program in object code or executable form with such
    an offer, in accord with Subsection b above.)

The source code for a work means the preferred form of the work for
making modifications to it.  For an executable work, complete source
code means all the source code for all modules it contains, plus any
associated interface definition files, plus the scripts used to
control compilation and installation of the executable.  However, as a
special exception, the source code distributed need not include
anything that is normally distributed (in either source or binary
form) with the major components (compiler, kernel, and so on) of the
operating system on which the executable runs, unless that component
itself accompanies the executable.

If distribution of executable or object code is made by offering
access to copy from a designated place, then offering equivalent
access to copy the source code from the same place counts as
distribution of the source code, even though third parties are not
compelled to copy the source along with the object code.

  4. You may not copy, modify, sublicense, or distribute the Program
except as expressly provided under this License.  Any attempt
otherwise to copy, modify, sublicense or distribute the Program is
void, and will automatically terminate your rights under this License.
However, parties who have received copies, or rights, from you under
this License will not have their licenses terminated so long as such
parties remain in full compliance.

  5. You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Program or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Program (or any work based on the
Program), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Program or works based on it.

  6. Each time you redistribute the Program (or any work based on the
Program), the recipient automatically receives a license from the
original licensor to copy, distribute or modify the Program subject to
these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties to
this License.

  7. If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Program at all.  For example, if a patent
license would not permit royalty-free redistribution of the Program by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Program.

If any portion of this section is held invalid or unenforceable under
any particular circumstance, the balance of the section is intended to
apply and the section as a whole is intended to apply in other
circumstances.

It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system, which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.

This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.

  8. If the distribution and/or use of the Program is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Program under this License
may add an explicit geographical distribution limitation excluding
those countries, so that distribution is permitted only in or among
countries not thus excluded.  In such case, this License incorporates
the limitation as if written in the body of this License.

  9. The Free Software Foundation may publish revised and/or new versions
of the General Public License from time to time.  Such new versions will
be similar in spirit to the present version, but may differ in detail to
address new problems or concerns.

Each version is given a distinguishing version number.  If the Program
specifies a version number of this License which applies to it and "any
later version", you have the option of following the terms and conditions
either of that version or of any later version published by the Free
Software Foundation.  If the Program does not specify a version number of
this License, you may choose any version ever published by the Free Software
Foundation.

  10. If you wish to incorporate parts of the Program into other free
programs whose distribution conditions are different, write to the author
to ask for permission.  For software which is copyrighted by the Free
Software Foundation, write to the Free Software Foundation; we sometimes
make exceptions for this.  Our decision will be guided by the two goals
of preserving the free status of all derivatives of our free software and
of promoting the sharing and reuse of software generally.

			    NO WARRANTY

  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.

  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

		     END OF TERMS AND CONDITIONS

	Appendix: How to Apply These Terms to Your New Programs

  If you develop a new program, and you want it to be of the greatest
possible use to the public, the best way to achieve this is to make it
free software which everyone can redistribute and change under these terms.

  To do so, attach the following notices to the program.  It is safest
to attach them to the start of each source file to most effectively
convey the exclusion of warranty; and each file should have at least
the "copyright" line and a pointer to where the full notice is found.

    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 19yy  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Also add information on how to contact you by electronic and paper mail.

If the program is interactive, make it output a short notice like this
when it starts in an interactive mode:

    Gnomovision version 69, Copyright (C) 19yy name of author
    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.

The hypothetical commands `show w' and `show c' should show the appropriate
parts of the General Public License.  Of course, the commands you use may
be called something other than `show w' and `show c'; they could even be
mouse-clicks or menu items--whatever suits your program.

You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the program, if
necessary.  Here is a sample; alter the names:

  Yoyodyne, Inc., hereby disclaims all copyright interest in the program
  `Gnomovision' (which makes passes at compilers) written by James Hacker.

  <signature of Ty Coon>, 1 April 1989
  Ty Coon, President of Vice

This General Public License does not permit incorporating your program into
proprietary programs.  If your program is a subroutine library, you may
consider it more useful to permit linking proprietary applications with the
library.  If this is what you want to do, use the GNU Library General
Public License instead of this License.

"""


# common imports
import os,sys,pickle

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
## lUnique GIMP texture tool :: gtk init
##
###########################################################################################################

try:
    # GTK binding import
    import pygtk
    pygtk.require('2.0')
    import gtk
except ImportError,info:
    print("ERROR: GTK bindings not found in your python installation..\n"+
	  "Please solve this problem and try again....")
    sys.exit()

###########################################################################################################
##
## lUnique GIMP texture tool :: logo image
##
###########################################################################################################

try:
    import base64
except:
    class LogoImage(gtk.Image):
	pass
else:
    class LogoImage(gtk.Image):
	__data__="""
	iVBORw0KGgoAAAANSUhEUgAAAP0AAAD9CAMAAABA64HOAAABgFBMVEUXFxccHBwfHx8gICAjIyMnJycpKSkrKystLS0uLi4wMDA0
	NDQ1NTU2NjY4ODg5OTk7Ozs+Pj4/Pz9CQkJDQ0NFRUVGRkZISEhKSkpLS0tOTk5QUFBRUVFSUlJTU1NVVVVXV1dZWVlbW1tcXFxf
	X19gYGBiYmJjY2NmZmZnZ2doaGhqampsbGxubm5vb29xcXF0dHR2dnZ3d3d5eXl8fHx9fX1+fn6AgICCgoKEhISFhYWIiIiKioqL
	i4uMjIyNjY2Pj4+QkJCTk5OUlJSXl5eYmJiampqbm5udnZ2fn5+hoaGioqKkpKSnp6eoqKipqamrq6utra2wsLCysrK0tLS1tbW3
	t7e5ubm7u7u9vb2+vr6/v7/BwcHDw8PFxcXGxsbHx8fJycnKysrMzMzPz8/R0dHT09PU1NTV1dXX19fZ2dnb29vc3Nzf39/h4eHi
	4uLj4+Pl5eXo6Ojp6enr6+vt7e3w8PDx8fHy8vL19fX39/f4+Pj5+fn7+/v+/v7///+k5Eq9AAAACXBIWXMAAA2wAAANsAF9ZVn6
	AAAAB3RJTUUH1wYTBDY3OKsXQAAAIABJREFUeNrV3Ylj2kbCKPC8ffu93ddut22SJo2T+AIbjDGIWyBASIABA+Yyh41xHAy+4vtI
	TOJY//qb0T2SAGHk403T1iMLwo+R5p7RC+ahw8/9nRHCqeyVd0ejvPLobvTP9uL54h+B/+IZ4x+e/+JZ4tsnj8N/8Rzx282140fh
	y/R32wWSOGHOz87unhi/sbtbfRS+pN81TVixD10mOWk6flL85/Xd3d29R0l9UX/8ZyBgsZq7zBfzYvlJ8RtdqN97jNQX9dO+6bnk
	FNAziy7vU2Z4jS6n338EvqC//MNvuztg9SGX9WnxvP4R+IJ+66O5xnD6JGb6+VT4HYjv7q63oX6/evTAfFH/3tzg9QGX7Wnx3XqY
	aEP9fu2B+eKV/5sL5/TXJk/oyfAdiG+EiwWiDfUHD3zxi7neq/DrYhfoz91L1uoT4eudDosvFIslln9w8LCpL+q3XiWmX06apt47
	fY7bJ8F3AB7oG0QB6ovEDtQ/LF+q7SRe+dIkQdI2y9HT4TsAv8rpYeofPDBfVtM9WHj1cfbjx/jNE+I7AC/oy8QO1B8+IF/Qd/96
	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
	"""
	def __init__(self):
	    gtk.Image.__init__(self)
	    db=base64.decodestring(self.__data__)
	    fn=os.tmpnam()
	    fd=open(fn,"wb")
	    fd.write(db)
	    fd.close()
	    self.set_from_file(fn)
	    os.system("rm -f "+fn)

###########################################################################################################
##
## lUnique GIMP texture tool :: self installation system
##
###########################################################################################################

def check_sudo_mode():
    p=os.popen("groups")
    groups=p.read().replace("\n","").split(" ")
    p.close()
    for n in groups:
	if n=="root":
	    return True
    return False
def check_gimp_version():
    p=os.popen("gimp -v")
    version=p.read().replace("\n","")
    p.close()
    b=version.find("GIMP")
    if 0<b and b<len(version): version=version[b:]
    name,full_version=version.split(" ")
    version=full_version.split(".")
    return name,version,full_version

class InstallDialog(gtk.Dialog):
    install_param=[_("for current user"),
		   _("for all users")]
    install_value=["user","system"]
    name=_(".:: lUnique GIMP Texture Tools installator ::.")
    preface=_("\n\n\n\n\n\n")
    comment=_("""
    You seem to be system administrator (root), you can select installation type
    """)
    def __init__(self):
	sudo_mode=check_sudo_mode()
	name,version,full_version=check_gimp_version()
	title=_("lUnique GIMP tools :: Install")
	if sudo_mode:
	    title=_("lUnique GIMP tools :: Install (sudo mode)")
	# Init dialog
	gtk.Dialog.__init__(self,title,None,0,
			    (gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,
			     gtk.STOCK_OK,gtk.RESPONSE_OK))
	# MAIN HBOX
	common=gtk.HBox()
	self.vbox.pack_start(common)
	# Logo Image
	logo_image=LogoImage()
	common.pack_start(logo_image)
	# VBOX
	main=gtk.VBox()
	common.pack_start(main)
	label_name=gtk.Label(self.name)
	main.pack_start(label_name)
	label_preface=gtk.Label(self.preface)
	main.pack_start(label_preface)
	label_info=gtk.Label(_("GIMP version ")+full_version+_(" found! \n"))
	main.pack_start(label_info)
	label_comment=gtk.Label(self.comment)
	main.pack_start(label_comment)
	label_comment.set_sensitive(sudo_mode)
	# HBOX
	pannel=gtk.HBox()
	main.pack_start(pannel)
	label_install=gtk.Label(_("Install type:"))
	pannel.pack_start(label_install)
	label_install.set_sensitive(sudo_mode)
	self.combo_install=gtk.combo_box_new_text()
	for n in self.install_param: self.combo_install.append_text(n)
	self.combo_install.set_active(0)
	self.combo_install.set_sensitive(sudo_mode)
	pannel.pack_start(self.combo_install)
    def show(self):
	self.show_all()
    def dump(self): #
	return self.install_value[self.combo_install.get_active()]

def lunique_install(selfname):
    dialog=InstallDialog()
    dialog.show()
    if dialog.run()==gtk.RESPONSE_OK:
	mode=dialog.dump()
	name,version,full=check_gimp_version()
	install_path=os.environ["HOME"]+"/.gimp-"+\
	    str(version[0])+"."+str(version[1])+"/plug-ins/"
	if mode=="system":
	    install_path="/usr/lib/gimp/"+version[0]+".0/plug-ins/"
	install_name=install_path+selfname
	remove_command="rm -f "+install_name
	try:
	    open(install_name)
	except IOError:
	    pass
	else:
	    os.system(remove_command)
	install_command="cp "+selfname+" "+install_path
	if os.system(install_command):
	    msg="" #sys.stderr.read()
	    m=gtk.MessageDialog(None,gtk.DIALOG_DESTROY_WITH_PARENT,
				gtk.MESSAGE_INFO,gtk.BUTTONS_OK,
				_("lUnique GIMP tools :: Installation failed")+"\n"+msg)
	    m.run()
	    m.destroy()
	    return -1
	else:
	    m=gtk.MessageDialog(None,gtk.DIALOG_DESTROY_WITH_PARENT,
				gtk.MESSAGE_INFO,gtk.BUTTONS_OK,
				_("lUnique GIMP tools :: Installed successfull"))
	    m.run()
	    m.destroy()
    return 0

###########################################################################################################
##
## lUnique GIMP texture tool :: texture export options
##
###########################################################################################################

class TextureExportOptions(dict):
    configfile=".lUnique_texture_tool.rc"
    def __init__(self):
	self["path"]=os.environ["HOME"]
	self["level"]=0
	self["limit"]=0
    def load(self):
	try:
	    f=open(os.environ["HOME"]+"/"+self.configfile,"r")
	except IOError:
	    return
	try:
	    new_set=pickle.load(f)
	except EOFError:
	    return
	for k in new_set: self[k]=new_set[k]
	f.close()
    def save(self):
	try:
	    f=open(os.environ["HOME"]+"/"+self.configfile,"wb")
	except EOFError:
	    return
	try:
	    pickle.dump(self,f)
	except EOFError:
	    return
	f.close()
	pass

###########################################################################################################
##
## lUnique GIMP texture tool :: commandline based export system
##
###########################################################################################################

def lunique_batch_export(selfname,file,path="",level=-1,limit=-1):
    if file=="":
	print(_("ERROR: please give .xcf file for exporting (option --input|-f)"))
	return -2
    opt=TextureExportOptions()
    opt.load()
    if path=="": path=opt["path"]
    if level==-1: level=opt["level"]
    if limit==-1: limit=opt["limit"]
    try:
	open(file)
    except IOError:
	print(_("ERROR: file `")+file+_("` not found!"))
	return -3
    try:
	os.path.exists(path)
    except IOError:
	print(_("ERROR: path `")+path+_("` not exist!"))
	return -4
    if os.system("gimp --no-interface --batch '(lunique-texture-export-batch RUN-NONINTERACTIVE 0 0 \""+
		 file+"\" \""+path+"\" "+str(int(float(level)))+" "+str(int(float(limit)))+
		 ")' '(gimp-quit 1)'"):
	print(_("ERROR: texture exporting error!"))
	return -1
    return 0

###########################################################################################################
##
## lUnique GIMP texture tool :: commandline arguments parser
##
###########################################################################################################

class ArgDict(dict):
    def __init__(self,argv):
	dict.__init__(self)
	self.argv=argv
	self["exec"]=argv[0]
    def define(self,par,name,val=False):
	if type(name)==list:
	    for n in name:
		if self.define(par,n,val):
		    return
	if type(name)==str:
	    self[par]=val
	    for n in self.argv:
		if n.find(name)==0:
		    if len(n)>len(name):
			if n[len(name)]=="=":
			    self[par]=n[len(name)+1:]
			    return True
		    else:
			if len(n)==len(name):
			    k=self.argv.index(n)
			    if val!=False and k+1<len(self.argv):
				self[par]=self.argv[k+1]
			    else:
				self[par]=True
			    return True
	return False

###########################################################################################################
##
## lUnique GIMP texture tool :: out GIMP running
##
###########################################################################################################

def lunique_batch_help(selfname):
    print("""
    """+__program__+""" :: batch mode help page
    
    """+__copyright__+"""
    
    usage: """+selfname+""" [options]
    Available options:
    --install|-i                          Install plug-in
    --export|-e                           Batch export
    --input|--input-file|-f[ |=]file      Input .xcf file for export
    --output|--output-path|-o[ |=]path    Path for save textures
    --level|-s                            Texture detail level [0:12]
    --limit|-m                            Texture detail level limit [0:12]
    --help|-h                             This help page
    --version|-v                          Plug-in version number
    --about|--authors|-a                  About authors
    --license|-l                          License
    """)
    return 0
def lunique_batch_version(selfname):
    print("""
    """+__program__+""" :: version info
    
    """+selfname+" "+__version__+"""
    
    """+__copyright__+"""
    """)
    return 0
def lunique_batch_about(selfname):
    print("""
    """+__program__+""" :: authors info
    
    Developer:
        """+__developer__+"""
    Documentator:
        """+__documentator__+"""
    """)
    return 0
def lunique_batch_license(selfname):
    print("""
    """+__program__+""" :: license information
    
    """+__copyright__+"""
    
    """+__license__+"""
    """)
    return 0

def lunique_main():
    arg=ArgDict(sys.argv)
    arg.define("install",["--install","-i"])
    arg.define("export",["--export","-e"])
    arg.define("help",["--help","-h"])
    arg.define("version",["--version","-v"])
    arg.define("license",["--license","-l"])
    arg.define("about",["--about","--authors","-a"])
    arg.define("output",["--output","--output-path","-o"],"")
    arg.define("input",["--input","--input-file","-f"],"")
    arg.define("level",["--level","-s"],-1)
    arg.define("limit",["--limit","-m"],-1)
    if arg["help"]:
	sys.exit(lunique_batch_help(arg["exec"]))
    if arg["version"]:
	sys.exit(lunique_batch_version(arg["exec"]))
    if arg["about"]:
	sys.exit(lunique_batch_about(arg["exec"]))
    if arg["license"]:
	sys.exit(lunique_batch_license(arg["exec"]))
    if arg["install"]:
	sys.exit(lunique_install(arg["exec"]))
    if arg["export"]:
	file=arg["input"]
	path=arg["output"]
	level=arg["level"]
	limit=arg["limit"]
	sys.exit(lunique_batch_export(arg["exec"],file,path,level,limit))
    print(_("Please run this plug-in from GIMP or use with --help option for help.."))
    sys.exit(0)

###########################################################################################################
##
## lUnique GIMP texture tool :: from GIMP running
##
###########################################################################################################

# in gimp running
try:
    import gimp,gimpplugin
    from gimpenums import *
    from gimpfu import *
except ImportError,info:
    lunique_main()
# other import

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
	# BACK HBOX
	back=gtk.HBox()
	self.vbox.pack_start(back)
	back.show()
	# Logo Image
	logo_image=LogoImage()
	back.pack_start(logo_image)
	logo_image.show()
	# MAIN VBOX
	main=gtk.VBox()
	back.pack_start(main)
	main.show()
	# texture state
	self.toggle_state=gtk.CheckButton(_("Enable texture map"))
	self.toggle_state.connect("clicked",self.on_toggle_state_clicked)
	main.pack_start(self.toggle_state)
	# TOP PANEL (self.common)
	pannel_top=gtk.HBox()
	main.pack_start(pannel_top)
	self.common=pannel_top
	# BOTTOM PANEL (self.special)
	pannel_bottom=gtk.HBox()
	main.pack_start(pannel_bottom)
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
	    main.pack_start(self.format_option[len(self.format_option)-1])
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

class TextureExportDialog(gtk.Dialog):
    level_value=[0,0,12,1,3]
    limit_value=[0,0,12,1,3]
    def __init__(self):
	# Init dialog
	self.opt=TextureExportOptions()
	gtk.Dialog.__init__(self,_("Texture export"),None,0,
			    (gtk.STOCK_CANCEL,
			     gtk.RESPONSE_CANCEL,
			     gtk.STOCK_OK,
			     gtk.RESPONSE_OK))
	# BACK HBOX
	back=gtk.HBox()
	self.vbox.pack_start(back)
	# Logo Image
	logo_image=LogoImage()
	back.pack_start(logo_image)
	# parameters group
	main_panel=gtk.HBox()
	back.pack_start(main_panel)
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
	self.opt.load()
	self.select_path.set_filename(self.opt["path"])
	self.spin_level.set_value(self.opt["level"])
	self.spin_limit.set_value(self.opt["limit"])
    def save(self):
	self.opt["path"]=self.select_path.get_filename()
	self.opt["level"]=int(self.spin_level.get_value())
	self.opt["limit"]=int(self.spin_limit.get_value())
	self.opt.save()
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
	gimp.install_procedure("lunique_about_tools",
			       "About dialog",
			       "About dialog",
			       __developer__,
			       __copyright__,
                               __date__,
			       "<Image>/lUnique/_About tools",
			       "RGB*, GRAY*, ,INDEXED*",
			       PLUGIN,
                               [(PDB_INT32, "run-mode", "interactive/noninteractive"),
				(PDB_IMAGE,"image","dummy"),
				(PDB_DRAWABLE,"drawable","dummy")],
			       [])
	gimp.install_procedure("lunique_texture_option",
			       "Set texture option dialog",
			       "set texture option",
			       __developer__,
			       __copyright__,
                               __date__,
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
			       __developer__,
			       __copyright__,
			       __date__,
			       "<Image>/lUnique/Texture _export",
			       "RGB*, GRAY*, ,INDEXED*",
			       PLUGIN,
			       [(PDB_INT32,"run-mode","interactive/noninteractive"),
				(PDB_IMAGE,"image","The image to work on"),
				(PDB_DRAWABLE,"drawable","dummy"),
				(PDB_STRING,"path","Path to texture produce files"),
				(PDB_INT32,"level","Texture detail level [0:12] 0-1:1 12-1:2^12"),
				(PDB_INT32,"limit","Texture detail limit [0:12] 0->2^1 12->2^12")],
			       [])
	gimp.install_procedure("lunique_texture_export_batch",
			       "Export textures for the lUnique engine",
			       "Export textures for the lUnique engine",
			       __developer__,
			       __copyright__,
			       __date__,
			       "",
			       "RGB*, GRAY*, INDEXED*",
			       PLUGIN,
			       [(PDB_INT32,"run-mode","dummy"),
				(PDB_IMAGE,"image","dummy"),
				(PDB_DRAWABLE,"drawable","dummy"),
				(PDB_STRING,"filename","Path to .xcf file"),
				(PDB_STRING,"path","Path to output texture files"),
				(PDB_INT32,"level","Texture detail level [0:12] 0-1:1 12-1:2^12"),
				(PDB_INT32,"limit","Texture detail limit [0:12] 0->2^1 12->2^12")],
			       [])
        # note that this method name matches the first arg of
        # gimp.install_procedure
    def lunique_about_tools(self,mode,image,drawable):
	# gui create
	if mode==RUN_INTERACTIVE:
	    dialog=gtk.AboutDialog()
	    dialog.set_name(__program__)
	    dialog.set_authors([__developer__])
	    dialog.set_documenters([__documentator__])
	    dialog.set_license(__license__)
	    dialog.set_copyright(__copyright__)
	    dialog.set_website_label(__program__)
	    dialog.set_website(__website__)
	    image=LogoImage()
	    dialog.set_logo(image.get_pixbuf())
	    dialog.set_version(__version__)
	    dialog.show()
	    dialog.run()
	    dialog.destroy()
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
    def lunique_texture_export(self,mode,image,drawable,path="",level=-1,limit=-1): # do what ever this plugin should do
	if mode==RUN_INTERACTIVE:
	    # create gui
	    dialog=TextureExportDialog()
	    # run dialog
	    dialog.show()
	    dialog.load()
	    if dialog.run()==gtk.RESPONSE_OK:
		dialog.save()
		if path=="": path=dialog.opt["path"]
		if level==-1: level=dialog.opt["level"]
		if limit==-1: limit=dialog.opt["limit"]
		self.lunique_texture_export(RUN_NONINTERACTIVE,image,drawable,
					    path,level,limit)
	    dialog.save()
	    # gui destroy
	    dialog.destroy()
	if mode==RUN_NONINTERACTIVE:
	    for layer in image.layers:
		if param_is(layer,"state"):
		    self.lunique_export_texture_map(mode,image,layer,path,level,limit)
    def lunique_export_texture_map(self,mode,image,drawable,path,level,limit):
	#gimp.message(drawable.name)
	map=TextureExport()
	map.export(drawable,path,level,limit)
    def lunique_texture_export_batch(self,mode,image,drawable,filename,path="",level=-1,limit=-1):
	opt=TextureExportOptions()
	opt.load()
	if path=="": path=opt["path"]
	if level==-1: level=opt["level"]
	if limit==-1: limit=opt["limit"]
	image=pdb.gimp_xcf_load(0,filename,filename)
	self.lunique_texture_export(RUN_NONINTERACTIVE,image,0,
				    path,level,limit)
	gimp.delete(image)

###########################################################################################################
##
## lUnique GIMP texture tool :: main code section
##
###########################################################################################################

def fail(msg):
    '''Display error message and quit'''
    gimp.message(msg)
    raise error, msg

if __name__ == '__main__': lunique_plugin().start()
