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

t()

local mn=unbase.MULTNAME()
mn("chrome.{1,2,white,black,00}.tex")

for i=1,#mn do
  print(mn[i],mn(i))
end

t()

print("Full time: "..t.delta)
print"Leave lUnique5.1 session...."
print"Thanks for use lUnique...."
