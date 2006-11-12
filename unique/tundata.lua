#!/usr/bin/env lua5.1

print"Enter lUnique5.1 session...."
lang="ru_RU"
print("Change locale to \""..lang.."\" ok!")
print"Loading modules...."

require"indep"
require"unbase"
require"undata"

print "Modules loaded...."
local t=unbase.TIME()

print("Test PATH")
local p=undata.PATH("/usr/src//////toluaxx////")
print("Source path: #"..tostring(#p).." ["..tostring(p).."]")
for k,n in p do print("[",k,"]=",n) end
p=p.."backup/0.1"
print(p)
p("?path/?/to/?.?.test?")
print("Apply ",p,p:apply("local"))

print("Test PATHS")
local ps=undata.PATHS()
print(ps)
ps.texture=p
ps.material="/local/data"
ps.mesh=ps.texture
print(ps)
for k,n in ps do print("[",k,"]=",n) end
print(ps)
ps.mesh=nil
print(ps)

print("Test NAMES")
local ns=undata.NAMES()
print(ns)
ns.texture="kkk"
ns.base="vv"
print(ns)
for k,n in ns do print("[",k,"]=",n) end
ns.texture=nil
print(ns)

print("Test REPOS")
print(undata.repos)

print("Test DIRECTORY")
local d=undata.DIRECTORY()
undata.repos.base=d
print(undata.repos)
d.location="."
d.path.opt="opt/?:opt/?.config"
print(d.path)
print(d.path.opt)
d.path.opt=nil
print(d.path)
d.path.opt="opt/?:opt/?.local"

local r=undata.resource("linux-mingw")
print(r)
local r=undata.resource("linux-mingw","opt")
print(r)
local s=r:stream(undata.STREAM.inp)
print(s)

os.exit()
print("src is directory? yes",d:restype(undata.PATH("src"))==d.dir)
print("config is stream? yes",d:restype(undata.PATH("config"))==d.stm)
print("option not exist? yes",d:restype(undata.PATH("option"))==d.non)

print("unbase is directory? no",d:restype("unbase")==d.dir)
print("opt/global is stream? yes",d:restype("global","opt")==d.stm)
print("option not exist? yes",d:restype("global","option")==d.non)

t()
print("Full time: "..t.delta)
print"Leave lUnique5.1 session...."
print"Thanks for use lUnique...."
