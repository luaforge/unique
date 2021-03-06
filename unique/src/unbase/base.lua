function import(name) for i,v in _G[name] do _G[i]=v end end

lang=lang or "en_EN"
function help_rest(cont) -- Delete prefix and suffix tabulation
   if string.sub(cont,1,1)==" " or string.sub(cont,1,1)=="\t" then cont=string.sub(cont,2) end
   return cont
end
function help_parag(cont,llen) -- Paragraphisation
   for n,v in pairs(conword) do cont=string.gsub(cont,"$"..n,v) end
   local offs=string.len(locword.lpref)+string.len(locword.lsuff)
   llen=llen-offs
   local i=llen
   repeat
      if string.find(string.sub(cont,i-llen-offs+1,i),"\n")==nil then
	 cont=string.sub(cont,0,i)..locword.lsuff..locword.lpref..help_rest(string.sub(cont,i+1))
	 i=i+llen+offs+1
      else 
	 i=string.find(cont,"\n",i)
	 if i==nil then i=string.len(cont) else i=i+llen+offs+1 end
      end
   until i>=string.len(cont)
   cont=string.gsub(cont,"\n",locword.psuff..locword.ppref)
   cont=locword.ppref..cont..locword.psuff
   return cont
end
function help_proc(cont,args) -- Help info preprocessing
   if string.sub(cont,1,1)=="(" and string.sub(cont,-1,-1)==")" then cont=string.sub(cont,2,-2) end
   cont=locword.top..locword.title..cont..locword.bottom
   cont=string.gsub(cont,"$overview{(.-)}",function(c) return "  ::: "..locword.overview.." :::\n\n"..help_parag(c,80).."\n" end)
   cont=string.gsub(cont,"$property{(.-)\\(.-)}",function(n,c) return help_parag("  * "..n.." - "..c,80).."\n" end)
   cont=string.gsub(cont,"$method{(.-)\\(.-)}",  function(n,c) return help_parag("  * "..n.." - "..c,80).."\n" end)
   cont=string.gsub(cont,"$properties{(.-)}",function(c) if c==nil or c=="" then c=help_parag(locword.properties_ne,80) end
						return "  ::: "..locword.properties.." :::\n\n"..c.."" end)
   cont=string.gsub(cont,"$methods{(.-)}",   function(c) if c==nil or c=="" then c=help_parag(locword.methods_ne,80) end
						return "  ::: "..locword.methods.." :::\n\n"..c.."" end)
   for n,v in pairs(args) do cont=string.gsub(cont,"$"..n,v) end
   return cont
end
help__info={
   en_EN={
      top    ="===============================begin=lunique=inline=documentation======================\n",
      bottom ="\n=================================end=lunique=inline=documentation======================\n",
      title  ="\t\t\t.:: Info about \"$@\" ::. \n",
      info_nf="Info about subject \"$@\" not found",
      subj_ne="Subject \"$@\" not exist",
      ppref="\t ",
      lpref="\t",
      psuff="\n",
      lsuff="\n",
      overview="Overview",
      properties="Properties",
      methods="Methods",
      properties_ne="properties undefined",
      methods_ne="methods not exists"
   },
   ru_RU={
      top    ="===============================начало=встроенной=документации=lunique==================\n",
      bottom ="\n================================конец=встроенной=документации=lunique==================\n",
      title  ="\t\t\t.:: Информация о \"$@\" ::.  \n",
      info_nf="Информация по \"$@\" не найдена",
      subj_ne="Субъект \"$@\" не существует",
      ppref="\t ",
      lpref="\t",
      psuff="\n",
      lsuff="\n",
      overview="Обзор",
      properties="Свойства",
      methods="Методы",
      properties_ne="свойства не определены",
      methods_ne="методов не существует"
   },
   __index=function(self,name)
	      return help__info[lang][name] or "unrecognized word"
	   end
}
locword={}
setmetatable(locword,help__info)
conword={
   ["\>"]="\n = ",
}
function help(obj) -- Print documentation for module or object
   local args={}
   if type(obj)=="string" then obj=_G[obj] end
   if not obj then return help_proc(locword.subj_ne,args) end
   args["@"]=tolua.type(obj)
   if not obj.__info then return help_proc(locword.info_nf,args) end
   if type(obj.__info)=="function" or type(obj.__info)=="cfunction" then return help_proc(obj:__info(lang),args) end
   if type(obj.__info)=="table" then return help_proc(obj.__info[lang],args) end
   return help_proc(obj.__info,args)
end
function script(name) -- Include lua script
   dofile(DATA.path.root..DATA.path.lua..name)
end

