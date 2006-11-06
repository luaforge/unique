#!/usr/bin/env lua5.1

function helpusage()
   return [=[PhoeniX11 @ RareSky .Org
]=]..arg[0]..[=[: OpenGL extensions config header generator
Usage: ]=]..arg[0]..[=[ -o <out header file> -i {GROUP1,GROUP2,....} <in header file>
Options:
	   ....
]=]
end

function prefix()
   return [=[
/*
 *  OpenGL Extensions Config
 */
/*
 *  Registering extensions:
 *
 *    GLEXT_FUNC(pseudo function name, real extension function type, real extension function name);
 *
 *    type of function is a PFN{type}PROC
 *    name of function is a {name}
 */
]=]
end

function suffix()
   return [=[

/*
 *  End of OpenGL extensions config
 */
]=]
end

function gensep(n) -- generate separator spaces
   local r=""
   for i=1,n do r=r.." " end
   return r
end

function cortege(name,real,lenname,lenreal)
   local type=string.upper(real)
   local sepname,sepreal=lenname-#name,lenreal-#real
   return "GLEXT_FUNC("..name..","..gensep(sepname)..type..","..gensep(sepreal)..real..gensep(sepreal)..");\n"
end

vendor_ext={
   ARB="Architecture Review Board",
   EXT="EXT novendor",
   SGI="Silicon Graphics",
   SUN="Sun MicroSystems",
   NV="NVIDIA Corporation",
   ATI="ATI Corporation",
   HP="Hewlett Packard",
   PGI="PGI",
   IBM="IBM Corporation",
   INTEL="Intel Corporation",
   APPLE="Apple Corporation",
   REND="REND",
   INGR="INGR",
   ["3DFX"]="3DFX Vendor",
   MESA="MESA Library",
   OML="OML",
   I3D="I3D",
   S3="S3",
   ["3DL"]="3DL",
   MESAX="MESA Library",
   GREMEDY="GREMEDY"
}

function genname(real)
   for k in pairs(vendor_ext) do
      real=string.gsub(real,k.."S","")
      real=string.gsub(real,k.."X","")
      real=string.gsub(real,k,"")
   end
   return real
end

function maxlen(ts)
   if type(ts)=="table" then
      local lr,ln=0,0
      for _,v in pairs(ts) do
	 local r,n=#v,#genname(v)
	 if lr<r then lr=r end
	 if ln<n then ln=n end
      end
      return lr,ln
   end
   return 0,0
end

function process(ta,src)
   local te={}
   do -- parse input header
      --local pat="APIENTRY%s+(gl.+)%;\n"
      --local pat="^%s*([^%(\n]+)%s*(%b())%s*(c?o?n?s?t?)%s*(=?%s*0?)%s*;%s*"
      local codepat="#ifndef%s+([^%(\n]+)%s*(.-)%s*#endif%s*"
      local funcpat="(gl[^%s%(\n]+)%s*%b()%s*;"
      for ne,ce in string.gmatch(src,codepat) do
	 local i=1
	 te[ne]={}
	 for ve in string.gmatch(ce,funcpat) do
	    te[ne][i]=ve
	    i=i+1
	 end
      end
   end
   local tl={
      name=0,
      real=0
   }
   do -- calculate lengths
      for ne,ce in pairs(te) do
	 for _,v in pairs(ce) do
	    local r,n=#v,#genname(v)
	    if tl.real<r then tl.real=r end
	    if tl.name<n then tl.name=n end
	 end
      end
   end
   local dst=""
   do -- generate output header
      if ta.include then
	 local tu={}
	 for _,ne in pairs(ta.include) do
	    local ce=te[ne]
	    if type(ce)=="table" then
	       local lr,ln=maxlen(ce)
	       dst=dst.."#ifdef "..ne.."\n"
	       dst=dst.."/* >> Extensions `"..ne.."` >> */\n"
	       for _,v in pairs(ce) do
		  local n=genname(v)
		  if not tu[n] then
		     tu[n]=true
		     dst=dst..cortege(n,v,ln+1,lr+1)
		  end
	       end
	       dst=dst.."/* << Extensions `"..ne.."` << */\n"
	       dst=dst.."#endif\n"
	    end
	 end
      end
   end
   return dst
end

function split(s)
   if string.sub(s,#s)~="," then s=s.."," end
   local r={}
   local i=1
   for v in string.gmatch(s,"([%w%_]+),") do
      r[i]=v
      i=i+1
   end
   return r
end

function main(arg)
   local ta={ -- table of arguments
      help=nil,
      input=nil,
      output=nil,
      include=nil
   }
   do -- parse command line
      local pa="" -- previous argument
      local ca="" -- current argument
      for i=1,#arg do
	 ca=arg[i]
	 if     ca=="-h" or ca=="--help" then
	    ta.help=true
	 elseif (pa=="-i" or pa=="--include") and string.sub(ca,1,1)~="-" then
	    if not ta.include then ta.include={} end
	    local le=split(ca)
	    local i=#ta.include+1
	    for _,v in pairs(le) do
	       ta.include[i]=v
	       i=i+1
	    end
	 elseif (pa=="-o" or pa=="--output") and string.sub(ca,1,1)~="-" then
	    ta.output=ca
	 elseif string.sub(ca,1,1)~="-" then
	    ta.input=ca
	 end
	 pa=ca
      end
   end
   if ta.help then
      print(helpusage())
      os.exit(1)
   end
   if not ta.input then
      print(arg[0]..": no input files")
      os.exit(2)
   end
   local fd={ -- file descriptors
      input=nil,
      output=nil,
   }
   do -- open file descriptors
      fd.input=io.open(ta.input)
      if not fd.input then
	 print(arg[0]..": input file `"..ta.input.."` not found")
	 os.exit(2)
      end
      if ta.output then
	 fd.output=io.open(ta.output,"w")
      else
	 fd.output=io.output()
      end
   end
   local sc={ -- contents
      input=nil,
      output=nil,
   }
   do -- read contents
      sc.input=fd.input:read("*a")
   end
   do -- parse input header
      sc.output=process(ta,sc.input)
      if not sc.output then sc.output=" fatal error :-( " end
   end
   do -- read contents
      fd.output:write(prefix()..sc.output..suffix())
   end
   do -- close file descriptors
      fd.input:close()
      fd.output:close()
   end
end

main(arg)
