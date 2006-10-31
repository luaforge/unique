#!/usr/bin/env lua5.1

print"Enter lUnique5.1 session...."
lang="ru_RU"
print("Change locale to \""..lang.."\" ok!")
print"Loading modules...."

require"indep"
require"unbase"
require"unmath"

print "Modules loaded...."

print(unbase.CPU())

local t0=unbase.rdtsc()
local t1=unbase.rdtsc()
print("Empty tacts: ",t1-t0)

local ru=unbase.RESUSAGE()
ru()
for i=1,100000000 do end
ru()

print(ru.sys.time,ru.sys.delta,ru.user.time,ru.user.delta)
print(ru.user.delta*unbase.CPU.freq)
print(ru.inblock,ru.oublock)
print(ru.inblock,ru.oublock)
print(ru.ixrss,ru.idrss,ru.isrss,ru.mxrss)

print"Leave lUnique5.1 session...."
print"Thanks for use lUnique...."
