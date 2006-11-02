#!/usr/bin/env lua5.1

print"Enter lUnique5.1 session...."
lang="ru_RU"
print("Change locale to \""..lang.."\" ok!")
print"Loading modules...."

require"indep"
require"unbase"

print "Modules loaded...."
print("CPU Frequency:   ",unbase.CPU.freq,"\nCPU Vendor:     ",unbase.CPU.vendor,"\nCPU Extensions: ",unbase.CPU.extens,"\n"..unbase.CPU.info)
local t=unbase.TIME()

print("Test PATH")
local p=unbase.PATH("/usr/src//////toluaxx////")
print("Source path: #"..tostring(#p).." ["..tostring(p).."]")
for k,n in p do print("[",k,"]=",n) end
p=p.."backup/0.1"
print(p)

print("Test PATHS")
local ps=unbase.PATHS()
print(ps)
ps.texture=p
ps.material=unbase.PATH("/local/data")
ps.mesh=ps.texture
print(ps)
for k,n in ps do print("[",k,"]=",n) end
ps.material[1]="global"
print(ps)
ps.mesh=nil
print(ps)

print("Test NAMES")
local ns=unbase.NAMES()
print(ns)
ns.texture="kkk"
ns.base="vv"
print(ns)
for k,n in ns do print("[",k,"]=",n) end
ns.texture=nil
print(ns)

print("Test REPOS")

print("Test DIRECTORY")
local d=unbase.DIRECTORY()
d.location="."
d.path.opt=unbase.PATH("opt")
d.ext.opt="?"
print("src is directory? ",d:restype(unbase.PATH("src"))==d.dir)
print("config is stream? ",d:restype(unbase.PATH("config"))==d.stm)
print("option not exist? ",d:restype(unbase.PATH("option"))==d.non)

print("src/unbase is directory? ",d:restype("unbase")==d.dir)
print("opt/global is stream? ",d:restype("global","opt")==d.stm)
print("option not exist? ",d:restype("global","option")==d.non)

t()
print("Full time: "..t.delta)
print"Leave lUnique5.1 session...."
print"Thanks for use lUnique...."
