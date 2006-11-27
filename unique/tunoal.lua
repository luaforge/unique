#!/usr/bin/env lua5.1

print"Enter lUnique5.1 session...."
lang="ru_RU"
print("Change locale to \""..lang.."\" ok!")
print"Loading modules...."

require"indep"
require"unbase"
require"unoal"

print "Modules loaded...."
print("CPU Frequency:   ",unbase.CPU.freq,"\nCPU Vendor:     ",unbase.CPU.vendor,"\nCPU Extensions: ",unbase.CPU.extens,"\n"..unbase.CPU.info)
local t=unbase.TIME()

t()

local a=unoal.ALAPP()

a:open()

print(a.state,a.device,a.version,a.vendor,a.extensions)

a:close()

t()

print("Full time: "..t.delta)
print"Leave lUnique5.1 session...."
print"Thanks for use lUnique...."
