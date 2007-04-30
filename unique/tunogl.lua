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

local cs=unbase.CONTEXTS()
local c=unogl.GLAPP()
cs.main=c
print(cs)
c.size=unmath.vec2(640,480)
--c.size=unmath.vec2(1024,768)
--c.mode=true

c:open()

print(c.state)

local frames=0
local oldtime,curtime=unbase.TIME(),unbase.TIME()
local run=true

print(gl.glGetString(gl.GL_VERSION))

while run do

for _,k in c.key do
  if k.state then
    if k.code==k.esc then run=false end
    if k.code==k.f1 then c.mode=not c.mode end
  end
end

c:bind()

draw()

c:ubind()

curtime()
frames=frames+1
if (curtime-oldtime).time>=1 then
  oldtime()
  print(frames)
  frames=0
end

end

c:close()

