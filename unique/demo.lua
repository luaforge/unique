#!/usr/bin/env lua5.1


local screen_width,screen_height,screen_full=640,480,false

print "Enter lUnique4 session...."

lang="ru_RU"
print("Change locale to \""..lang.."\" ok!")
print"Loading modules...."
require"indep"
require"unbase"
require"unmath"
require"unogl"
require"unoal"
require"undata"
require"unvis"
require"unobj"
require"ungeom"
--require"uneff"
require"unsnd"
--require"ungui"
require"unfbo"
require"unique"
print"Modules loaded...."

local q=unmath.quat()
q:axis(unmath.vec3(0.0,0.0,1.0),45)
local m=unmath.mat3(q)
print("quat:",q,"mat:",m,m:inv())

collectgarbage("stop")

print"Init resource Repository...."
undata.repos.share=undata.DIRECTORY{
   location="../share",
   path={
      shader="shader/?;shader/?.lua;shader/?.glsl;shader/?.shader",
      shaderdata="shader/?.glsl;shader/?.shader",
      script="script/?;script/?.lua",
      texture="texture/?;texture/?.lua",
      texturedata="texture/?;texture/?.tex;texture/?.png;texture/?.jpg;texture/?.tga;texture/?.dss",
      material="material/?;material/?.lua",
      fontdata="font/?;font/?.ttf",
      meshdata="metric/?;metric/?.mesh",
      object="object/?;object/?.lua",
      scene="scene/?;scene/?.lua",
   }
}
undata.repos.data=undata.DIRECTORY{
   location="../data",
   path={
      texture="texture/?;texture/?.lua",
      texturedata="texture/?;texture/?.tex",
      material="material/?;material/?.lua",
      object="object/?;object/?.lua",
      meshdata="metric/?;metric/?.mesh",
      scene="scene/?;scene/?.lua",
   }
}

print"Repository inited...."

print("CPU Frequency:   ",unbase.CPU.freq,"\nCPU Vendor:     ",unbase.CPU.vendor,"\nCPU Extensions: ",unbase.CPU.extens,"\n"..unbase.CPU.info)

print "Open graphics rendering context...."
local r=unogl.GLAPP()
r.buffering=2
r.sampling=4
r.size.width=screen_width
r.size.height=screen_height
if screen_full then r.mode=true end
r:open()

--r.gamma.R=100.0
--r.gamma.G=50.0
print("Graphics Info( Vendor: ",r.vendor," || Renderer: ",r.renderer," || Version: ",r.version," )")
print("Graphics Extensions:   ",r.extensions)
engine.render.glmain=r

function load(n) end

print"Loading hier scene...."
load(engine.scene.myroom)
print(engine.scene.myroom.camera)
print"Loading data scene...."
engine.scene.myroom:update()
engine.scene.myroom.eventer=engine.render.glmain

local o=unobj.OBJECT()
function o:eventhandle(e)
   for _,k in e.key do
      if k.key==k.esc and k.state then engine.run=false end
      if k.key==k.f11 and k.state then print("Frame per second now: "..engine.fps.." delta:"..engine.time.delta.." step:"..engine.steptime.delta.." draw:"..engine.drawtime.delta) end
      if k.key==k.f9 and k.state then
	 print(engine.scene.myroom.object)
	 print(engine.scene.myroom.object.camera.user)
      end
   end
end
o.tex=engine.scene.myroom.texture.arch.brick.bigdecc
--o.mat.def=engine.scene.myroom.material.arch.brick.bigdecor
function o:_drawhandle(m)
   --gl.glDisable(gl.GL_LIGHTING)
   self.tex:bind()
   gl.glBegin(gl.GL_TRIANGLES)
   
   gl.glColor3d(0.0,1.0,0.0)
   gl.glTexCoord2d( 0.0, 1.0)
   gl.glVertex3d( 0.0, 1.0, 0.0)
   
   gl.glColor3d(1.0,0.0,0.0)
   gl.glTexCoord2d( 1.0, 0.0)
   gl.glVertex3d(-1.0,-0.5, 0.0)
   
   gl.glColor3d(0.0,0.0,1.0)
   gl.glTexCoord2d( 0.0, 0.0)
   gl.glVertex3d( 1.0,-0.5, 0.0)
   
   gl.glEnd()
   self.tex:ubind()
end
function o:stephandle(t)
   local dr=unmath.quat(1.0*t.delta,0.001,0.0,1.0)
   dr:norm()
   --self.rot=self.rot+dr
   --self.rot:norm()
end
engine.scene.myroom.object.handler=o

local ts=engine.scene.myroom.material.arch.brick.bigdecor.texture
--print("loaded: ",ts[0],ts[0].state,ts[1],ts[1].state)

--print("loaded: ",engine.scene.myroom.object.room.small.i001.state)
--[[
function hfer(k,n)
   print("loaded: ",k," : ",n.texture[0],n.texture[1],n.texture[2],n.texture[3])
   if tolua.type(n)=="unvis::MATGROUP" then
      for k,o in n do
	 hfer(k,o)
      end
   end
end
hfer("root",engine.scene.myroom.material)
]]--
print("Shader:",engine.scene.myroom.shader.bmp)

print "Run simulation...."
engine:loop()

print "Close rendering context...."
engine.render.glmain:close()
