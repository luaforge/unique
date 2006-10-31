#!/usr/bin/env lua5.1

print"Enter lUnique5.1 session...."
lang="ru_RU"
print("Change locale to \""..lang.."\" ok!")
print"Loading modules...."

require"indep"
require"unbase"
require"unmath"

print "Modules loaded...."
print("CPU Frequency:   ",unbase.CPU.freq,"\nCPU Vendor:     ",unbase.CPU.vendor,"\nCPU Extensions: ",unbase.CPU.extens,"\n"..unbase.CPU.info)
t=unbase.TIME()
print("Test vec2")
d,a,b=0,unmath.vec2(2,3),unmath.vec2(4,5)
assert(string.find(tostring(a),"vec2")==1,"operator string failed")
assert(a==unmath.vec2(2,3) and b==unmath.vec2(4,5) and a~=b,"operator== failed")
assert(#a==math.sqrt(2^2+3^2) and #a~=#b,"operator# failed")
assert(a+b==unmath.vec2(6,8),"operator+ failed")
assert(b-a==unmath.vec2(2,2),"operator- failed")
assert(a+unmath.vec2.null==a and a+unmath.vec2.one==unmath.vec2(3,4),"operator+const failed")
assert(a%unmath.vec2.null==unmath.vec2.null,"operator%const operator==const failed")

print("Test vec3")
print("Test mat3")
print("Test mat4")
local v,m=unmath.vec3(1.3,2.2,3.1),unmath.mat4.null
print(m*v)

print("Test index newindex")
local v=unmath.vec2()
v[0]=1.2
print(v[1])

--t() for i=0,1000000 do d=a*b end t()
--print("test1:: local d,a,b=0,vec2(),vec2() for i=0,1000000 do d=a*b end",t.time,t.delta)
t()
print("Full time: "..t.delta)
print"Leave lUnique5.1 session...."
print"Thanks for use lUnique...."
