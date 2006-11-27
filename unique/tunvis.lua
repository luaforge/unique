#!/usr/bin/env lua5.1

print"Enter lUnique5.1 session...."
lang="ru_RU"
print("Change locale to \""..lang.."\" ok!")
print"Loading modules...."

require"indep"
require"unbase"
require"undata"
require"unmath"
require"unvis"

print "Modules loaded...."

local t=unbase.TIME()

t()
-- init repository
local d=undata.DIRECTORY()
d.location="../data/"
d.path.material="material/?;material/?.lua"
d.path.texture="texture/?;texture/?.lua"
d.path.texturedata="texture/?.tex;texture/?.tga;texture/?.png;texture/?.jpg"
d.path.shader="shader/?;shader/?.lua"
d.path.shaderdata="shader/?.shader;shader/?.prog"
undata.repos.main=d
print(undata.repos)

-- test resource
-- catalog
local r=undata.resource("metall","material")
print(r)
if r.type==r.dir then
   
end
-- stream
-- hier level 0
local r=undata.resource("default","material")
print(r)
if r.type==r.stm then
   local s=r:stream()
   print(s)
   print(s:read())
end
-- hier level 1
local r=undata.resource("metall.silver","material")
print(r)
if r.type==r.stm then
   local s=r:stream()
   print(s)
   print(s:read())
end

-- test material nodes
local ms=unvis.MATGROUP()
print(ms,mg,mn,md)
local mn=ms.metall.silver
local mg=ms.metall
local md=ms.default
print(ms,mg,mn,md)

print(unvis.TEXTURE())

--texture
local ts=unvis.TEXGROUP()
print(ts,tg,tn,td)
local tn=ts.metall.silver
local tg=ts.metall
local td=ts.default
print(ts,tg,tn,td)

t()

print("Full test time: "..t.delta)
print"Leave lUnique5.1 session...."
print"Thanks for use lUnique...."
