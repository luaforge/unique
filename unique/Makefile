##                                    ##
##  Copyright (C) 2006 by PhoeniX IV  ##
##                                    ##
##  RareSky Community 2012            ##
##                                    ##
##             Platform GNU Makefile  ##
##                                    ##

##
## Enhanced make based build system
##

all: build

########## >> config section >> ###########
## include main config

include opt/global
-include opt/local
-include config
-include opt/option
## include platform config
-include opt/$(PLATFORM)-$(COMPILER).local
include opt/$(PLATFORM)-$(COMPILER)
########## << config section << ###########

########## >> predefine section >> ###########
## >> define variables >>
T.NAME=$(NAME)
## << define variables <<
## >> linking variables >>
ifeq ($(DEBUG),enable)
  C.FLAGS+=$(C.FLAGS.DEBUG)
else
  C.FLAGS+=$(C.FLAGS.RELEASE)
endif
ifneq ($(C.I.path),)
  C.FLAGS+=$(call C.I,$(C.I.path))
endif
ifneq ($(L.L.path),)
  L.OPTS+=$(call L.L,$(L.L.path)) # lib paths
endif
ifneq ($(L.l.name),)
  L.OPTS+=$(call L.l,$(L.l.name)) # lib names
endif
## << linking variables <<
########## << predefine section << ###########

########## >> template section >> ###########
define T.MODULE
## >> include local module config >>
include src/$(1)/config
## << include local module config <<
## >> check if module is enable >>
ifeq ($$($(1).state),enable)
#### >> template variables >>
###### >> sources and objects variables >>
$(1).src+=$$(wildcard $$(call C.S,$(1),*))
$(1).obj+=$$(patsubst $$(call C.S,$(1),%),$$(call C.O,$(1),%),$$($(1).src))
$(1).pkg+=$$(wildcard $$(call P.S,$(1),*))
$(1).pks+=$$(patsubst $$(call P.S,$(1),%),$$(call P.O,$(1),%),$$($(1).pkg))
$(1).src+=$$($(1).pks)
$(1).tps+=$$(wildcard $$(call U.T,$(1)))
###### << sources and objects variables <<
###### >> module depend variables >>
$(1).modep+=$$(call L.SO,$$($(1).dep))
###### << module depend variables <<
###### >> compile variables >>
ifneq ($$($(1).C.I),)
  $(1).C.flags+=$$(call C.I,$$($(1).C.I))
endif
###### << compile variables <<
###### >> linking variables >>
ifneq ($$($(1).L.L),)
  $(1).L.opts+=$$(call L.L,$$($(1).L.L))
endif
ifneq ($$($(1).L.l),)
  $(1).L.opts+=$$(call L.l,$$($(1).L.l))
endif
#ifneq ($$($(1).dep),)
#  $(1).L.opts+=$$(call L.d,$$($(1).dep))           # lib dep name
#endif
T.L.opts+=$$($(1).L.opts)
###### << linking variables <<
#### << template variables <<
#### >> module specific rules >>
###### >> compile pattern rule >>
#obj/$(1).%$(X.OXX): src/$(1)/%$(X.CXX)
$(call C.O,$(1),%): $(call C.S,$(1),%)
	@$(call U.EH,Compile $$< to $$@)
	@$(call U.EX,$(call C.XX,$$<,$$@,$$($(1).C.flags) $(C.FLAGS)))
###### << compile pattern rule <<
###### >> binding pattern rule >>
$(call P.O,$(1),%): $(call P.S,$(1),%)
	@$(call U.EH,Preproc $$< to $$@)
	@$(call U.EX,$(call P.XX,$$<,$$@,$$($(1).P.flags) $(P.FLAGS)))
.PRECIOUS: $(call P.O,$(1),%)
###### << binding pattern rule <<
###### >> module build rule >>
ifeq ($(DESIGN),module) # build module
$(call L.SO,$(1)): $$($(1).obj) $$($(1).modep)
	@$(call U.EH,Build $(1) module)
#	@$(call U.EX,$(call L.XX,$$(filter $(call C.O,$(1),%),$$^),$$@,$$($(1).L.opts) $(L.OPTS))) 
	@$(call U.EX,$$(call L.XX,$$^,$$@,$$($(1).L.opts) $(L.OPTS))) 
  $(1).target=$(call L.SO,$(1))
build.$(1): $$($(1).target)
  T.build+=build.$(1)
else
  T.obj+=$$($(1).obj)
endif
###### << module build rule <<
###### >> module clean rule >>
clean.$(1):
	@$(call U.EH,Clean $(1) module)
	@$(call U.EX,$(call U.RM,$$($(1).obj) $$($(1).pks) $$($(1).target) $$($(1).tps)))
T.clean+=clean.$(1)
###### << module clean rule <<
###### >> probe and test rules >>
probe.$(1):
	@$(call U.EH,Module $(1) options {)
	@$(call U.EH,  $(1).target = $$($(1).target))
	@$(call U.EH,  $(1).pkg    = $$($(1).pkg))
	@$(call U.EH,  $(1).pks    = $$($(1).pks))
	@$(call U.EH,  $(1).src    = $$($(1).src))
	@$(call U.EH,  $(1).obj    = $$($(1).obj))
	@$(call U.EH,  $(1).dep    = $$($(1).dep))
	@$(call U.EH,})
T.probe+=probe.$(1)
###### << probe and test rules <<
#### << module specific rules <<
.PHONY: probe.$(1) clean.$(1)
## << check if module is enable <<
else
## >> check if module is disable >>
build.$(1):
	@$(call U.EH,Module $(1) build disabled)
T.build+=build.$(1)
clean.$(1):
	@$(call U.EH,Module $(1) clean disabled)
T.clean+=clean.$(1)
probe.$(1):
	@$(call U.EH,Module $(1) probe disabled)
T.probe+=probe.$(1)
endif
## << check if module is disable <<
endef
########## << template section << ###########

########## >> implementation section >> ###########
TARGET.MODULES=$(filter-out %.hxx %.hpp %.opt,$(patsubst src/%,%,$(wildcard src/*)))
## >> template implementation >>
$(foreach cortege,$(TARGET.MODULES),$(eval $(call T.MODULE,$(cortege))))
## << template implementation <<
## >> global probe >>
probe: $(T.probe)
	@$(call U.EH,Global options {)
	@$(call U.EH,  C.FLAGS = $(C.FLAGS))
	@$(call U.EH,  L.OPTS  = $(L.OPTS))
	@$(call U.EH,})
	@$(call U.EH,Target options {)
	@$(call U.EH,  T.obj    = $(T.obj))
	@$(call U.EH,  T.L.opts = $(T.L.opts))
	@$(call U.EH,})
## << global probe <<
## >> global build >>
ifeq ($(DESIGN),module)
build: $(T.build)
	@$(call U.EH,Build complete....)
clean: $(T.clean)
	@$(call U.EH,Clean complete....)
endif
ifeq ($(DESIGN),monolith)
$(call L.SO,$(T.NAME)): $(T.obj)
	@$(call U.EH,Build $(T.NAME) module)
#	@$(call U.EX,$(call L.XX,$$(filter $(call C.O,,%),$^),$@,$(L.OPTS) $(T.L.opts)))
	@$(call U.EX,$(call L.XX,$^,$@,$(T.L.opts) $(L.OPTS)))
build: $(call L.SO,$(T.NAME))
	@$(call U.EH,Build complete....)
clean: $(T.clean)
	@$(call U.RM,$(call L.SO,$(T.NAME)))
	@$(call U.EH,Clean complete....)
endif
ifeq ($(DESIGN),runable)
  
endif
## << global build rules

########## << implementation section << ###########
### $(call of,cthulhu)
