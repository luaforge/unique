#!/usr/bin/env lua5.1

__option_={
   header=[=[
########################################
##                                    ##
##  Name: <module_name>               ##
##                                    ##
##  Description:                      ##
##    <module_description>            ##
##                                    ##
##  Version: <module version>         ##
##                                    ##
##  Developers:                       ##
##    <module_developer>              ##
##                                    ##
########################################

   ]=],
   common=[=[
<module_name>.state = <module_state>
<module_name>.dep = <module_dep>
   ]=],
}

__message_={}
__message_.en_EN={
   help=[=[
   lUniquE modules configure
	 Usage: ./config.lua <action> [<modulename>]
	    <action>:
	 enable|disable|status
	 
   ]=],
   error="Error: ",
   fatal_error="Fatal error",
   incorrect_action="Incorrect action `%s`",
   module_notexist="Module `%s` not exist",
   module_status_enable="Module `%s` enable",
   module_status_disable="Module `%s` disable"
}
__message_.ru_RU={
   help=[=[
   Конфигуратор модулей lUniquE
	 Использование: ./config.lua <действие> [<имя модуля>]
	 Где <действие>:
	 status         - просмотр статуса модуля
	 enable|disable - разрешить|запретить модуль
	 register       - зарегистрировать модуль
   ]=],
   error="Ошибка: ",
   fatal_error="Неисправимая ошибка",
   incorrect_action="Неверное действие `%s`",
   module_notexist="Модуль `%s` не найден",
   module_status_enable="Модуль `%s` разрешен",
   module_status_disable="Модуль `%s` запрещен"
}
__message_.def_DEF=__message_.en_EN

function iconv(text,from,to)
   return text
end

function gettext(text)
   local locale,charset=string.match(os.getenv("LANG"),"([%w%_%-]*)%.?([%w%_%-]*)")
   if not __message_[locale] then locale="def_DEF" end
   if not __message_[locale][text] then return ":notext:" end
   return iconv(__message_[locale][text],"UTF-8",charset)
end

function msg(...)
   if #arg<1 or gettext(arg[1])==":notext:" then return ":nomsg:" end
   return string.format(gettext(arg[1]),unpack(arg,2,#arg))
end

function error(msg,hlp)
   print(gettext("error")..msg.." !")
   if hlp then print(gettext(hlp)) end
   os.exit(-1)
end

function opt(o,n)
   if type(o)=="table" then
      if not n then
	 o=o[1]
      else
	 for i,s in pairs(o) do
	    local k,l=opt(s)
	    if k==n then o=l return l end
	 end
      end
   end
   local name,value=string.match(o,"([%w%_%-%.]*)%s*%=%s*([^%s]*)")
   return name,value
end

function content(name,cont)
   if cont then
      local fd=io.open(name,"w")
      if not fd then return nil end
      fd:write(cont)
      return true
   else
      local fd=io.open(name)
      if not fd then
	 content(name,"")
	 return nil
      end
      local ct=fd:read("*a")
      return ct
   end
end

function compile(s,o)
   for _,v in pairs(o) do
      local k,n=opt(v)
      s=string.match(s,"%<"..k.."%>",n)
   end
   return s
end

function modules()
   local fd=io.popen("dir src")
   if not fd then return nil end
   local ds=fd:read("*a")
   fd:close()
   local ms={}
   local i=1
   for m in string.gmatch(ds,"([%w%_]*)%s*") do
      if m and m~="" and m~="CVS" then
	 ms[i]=m
	 i=i+1
      end
   end
   return ms
end

function class(n)
   if not _G[n] then _G[n]={} end
   _G[n].__index=function(self,index)
		    local v=rawget(self,index)
		    if not v then
		       v=getmetatable(self)[index]
		    end
		    return v
		 end
   _G[n].__newindex=function(self,index,value)
		       rawset(self,index,value)
		    end
   _G[n].__tostring=function(self)
		       return self:str()
		    end
   setmetatable(_G[n],{
		   __call=function(self,...)
			     local new={}
			     setmetatable(new,self)
			     if type(self.new)=="function" then
				self.new(new,unpack(arg))
			     end
			     return new
			  end
		})
end

class'CONFIG'

function CONFIG:new(name)
   self.name=name
   self.file="src/"..name.."/config"
   local ct=content(self.file)
   if not ct then error(msg("module_notexist",self.name)) end
   self:parse(ct)
end

function CONFIG:parse(ct)
   self.header=string.match(ct,"(.*)\n%s*"..self.name..".state")
   self.state=string.match(ct,"\n%s*"..self.name..".state%s*=%s*(%w*)\n")
   self.dep=string.match(ct,"\n%s*"..self.name..".dep%s*=%s*(%w*)\n")
end

function optfmt(s)
   
end

function CONFIG:str()
   return tostring(self.header).."\n"..tostring(self.state).."\n"..tostring(self.dep).."\n"
end

__action_={}

function __action_.info(module,option)
   local c=CONFIG(module)
   print(tostring(c))
end

function __action_.chstate(module,option)
   if module=="all" then
      local ms=modules()
      for _,m in pairs(ms) do
	 __action_.chstate(m,option)
      end
   else
      local config="src/"..module.."/config"
      local ct=content(config)
      if not ct then error(msg("module_notexist",module)) end
      local st=opt(option,"state")
      if st then
	 ct=string.gsub(ct,"(\n%s*"..module..".state%s*=%s*)(%w*)(\n)","%1"..st.."%3")
	 content(config,ct)
      else
	 
      end
   end
end

function __action_.enable(module,option)
   option[#option+1]="state=enable"
   __action_.chstate(module,option)
end

function __action_.disable(module,option)
   option[#option+1]="state=disable"
   __action_.chstate(module,option)
end

function __action_.status(module,option)
   if module=="all" then
      local ms=modules()
      for _,m in pairs(ms) do
	 __action_.status(m,option)
      end
   else
      local ct=content("src/"..module.."/config")
      if not ct then error(msg("module_notexist",module)) end
      local state=string.match(ct,"\n%s*"..module..".state%s*=%s*(%w*)\n")
      if state=="enable" then
	 print(msg("module_status_enable",module))
      else
	 print(msg("module_status_disable",module))
      end
   end
end

function __action_.register(module,option)
   if module=="all" then
      local ms=modules()
      for _,m in pairs(ms) do
	 --__action_.register(m,option)
      end
   else
      
   end
end

function main(arg)
   local param={
      module="all",
      action=info,
      option={},
   }
   if #arg==0 then
      print(gettext("help"))
      os.exit(0)
   end
   if #arg>0 then
      if __action_[arg[1]] then
	 param.action=__action_[arg[1]]
      else
	 error(msg("incorrect_action",arg[1]),"help")
      end
   end
   if #arg>1 and not string.find(arg[2],"=") then
      param.module=arg[2]
      param.option={unpack(arg,3,#arg)}
   else
      param.module="all"
      param.option={unpack(arg,2,#arg)}
   end
   param.action(param.module,param.option)
end

main(arg)
