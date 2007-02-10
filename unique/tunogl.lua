#!/usr/bin/env lua5.1

print "Enter lUnique4 session...."

lang="ru_RU"
print("Change locale to \""..lang.."\" ok!")
print "Loading modules...."
require"indep"
require"unbase"
require"unmath"
require"unogl"
print "Modules loaded...."

function draw()
   gl.glBegin(gl.GL_TRIANGLES)
     gl.glVertex3d( 0.0, 1.0, 0.0)
     gl.glVertex3d(-1.0,-0.5, 0.0)
     gl.glVertex3d( 1.0,-0.5, 0.0)
   gl.glEnd()
end

local cs=unbase.CTXGROUP()
local c=unogl.GLAPP()
cs.main=c
print(cs)
c.size=unmath.vec2(640,480)
--c.size=unmath.vec2(1024,768)
--c.mode=true

c.buffering=2
c.sampling=4

c:open()

print(c.state)

if c.state.state then
   local frames=0
   local oldtime,curtime=unbase.TIME(),unbase.TIME()
   local run=true

   --print(gl.glGetString(gl.GL_VERSION))
   print(c.renderer,c.version,c.vendor,"\n",string.gsub(c.extensions," ","\n"))
   print(string.gsub(c.localextensions," ","\n"))

   gl.glClearColor(0.0,0.0,0.0,1.0)

   while run do
      if not c.state.state then print(c.state) run=false end

      for _,k in c.key do
        if k.state then
          if k.code==k.esc then run=false end
          if k.code==k.f1 then c.mode=not c.mode end
        end
      end

      c:bind()

      gl.glClear(gl.GL_COLOR_BUFFER_BIT+gl.GL_DEPTH_BUFFER_BIT)
      draw()

      c:ubind()

      curtime()
      frames=frames+1
      if (curtime-oldtime).time>=1 then
        oldtime()
        print("FPS:",frames)
        frames=0
      end
   end
end

c:close()

print(c.state)

