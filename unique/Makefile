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



-include config
-include opt/option
include opt/global
-include opt/local

## include platform config
CONFIG=$(PLATFORM)-$(COMPILER)
-include opt/$(CONFIG).local
include opt/$(CONFIG)
########## << config section << ###########

########## >> predefine section >> ###########
## >> define variables >>
T.NAME=$(NAME)
## << define variables <<
## >> compiling variables >>
ifeq ($(DEBUG),enable)
  C.FLAGS+=$(C.FLAGS.DEBUG)
else
  C.FLAGS+=$(C.FLAGS.RELEASE)
  ifeq ($(OPTIM),disable)
    C.FLAGS+=$(C.FLAGS.OPTIM.DISABLE)
  endif
  ifeq ($(OPTIM),enspeed)
    C.FLAGS+=$(C.FLAGS.OPTIM.ENSPEED)
  endif
  ifeq ($(OPTIM),ensize)
    C.FLAGS+=$(C.FLAGS.OPTIM.ENSIZE)
  endif
endif
ifneq ($(C.I.path),)
  C.FLAGS+=$(call C.I,$(C.I.path))
endif
## << compiling variables <<
## >> linking variables >>
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
ifneq ($$($(CONFIG).$(1).C.flags),)
  $(1).C.flags+=$$(call C.I,$$($(CONFIG).$(1).C.flags))
endif
ifneq ($$($(CONFIG).$(1).C.I),)
  $(1).C.flags+=$$(call C.I,$$($(CONFIG).$(1).C.I))
endif
ifneq ($$($(1).C.I),)
  $(1).C.flags+=$$(call C.I,$$($(1).C.I))
endif
###### << compile variables <<
###### >> linking variables >>
ifneq ($$($(CONFIG).$(1).L.opts),)
  $(1).L.opts+=$$($(CONFIG).$(1).L.opts)
endif
ifneq ($$($(CONFIG).$(1).L.L),)
  $(1).L.opts+=$$(call L.L,$$($(CONFIG).$(1).L.L))
endif
ifneq ($$($(CONFIG).$(1).L.l),)
  $(1).L.opts+=$$(call L.l,$$($(CONFIG).$(1).L.l))
endif
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
$(call C.O,$(1),%): $(call C.S,$(1),%)
	@$(call U.EH,Compile $$< to $$@)
	@$(call U.EX,$(call C.XX,$$<,$$@,$$($(1).C.flags) $(C.FLAGS)))
  T.obj+=$$($(1).obj)
###### << compile pattern rule <<
###### >> binding pattern rule >>
$(call P.O,$(1),%): $(call P.S,$(1),%)
	@$(call U.EH,Preproc $$< to $$@)
	@$(call U.EX,$(call P.XX,$$<,$$@,$$($(1).P.flags) $(P.FLAGS)))
.PRECIOUS: $(call P.O,$(1),%)
###### << binding pattern rule <<
###### >> module build rule >>
ifneq ($$($(1).design),option)
ifeq ($(findstring modules,$(DESIGN)),modules) # build module
  T.target+=$(1)
  $(1).target=$(call L.SO,$(1))
$$($(1).target): $$($(1).obj) $$($(1).modep)
	@$(call U.EH,Build $(1) module)
#	@$(call U.EX,$(call L.XX,$$(filter $(call C.O,$(1),%),$$^),$$@,$$($(1).L.opts) $(L.OPTS))) 
	@$(call U.EX,$$(call L.XX,$$^,$$@,$$($(1).L.opts) $(L.OPTS))) 
.PHONY: prepare.$(1)
build.$(1): prepare.$(1) $$($(1).target)
  T.build+=build.$(1)
endif
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
TARGET.MODULES=$(filter-out %.hxx %.hpp %.opt CVS,$(patsubst src/%,%,$(wildcard src/*)))
## >> template implementation >>
$(foreach cortege,$(TARGET.MODULES),$(eval $(call T.MODULE,$(cortege))))
## << template implementation <<

## >> global probe >>
probe: $(T.probe)
	@$(call U.EH,Global options {)
	@$(call U.EH,  C.FLAGS = $(C.FLAGS))
	@$(call U.EH,  L.OPTS  = $(L.OPTS))
	@$(call U.EH,  T.build = $(T.build))
	@$(call U.EH,  T.clean = $(T.clean))
	@$(call U.EH,  T.obj = $(T.obj))
	@$(call U.EH,  T.L.opts = $(T.L.opts))
	@$(call U.EH,})
## << global probe <<
## >> global build >>
TARGET.DESIGN=$(addsuffix .$(1),$(2))
#### >> design modules >>
modules.build: $(T.build)
	@$(call U.EH,Build modules complete....)
modules.clean: $(T.clean)
	@$(call U.EH,Clean modules complete....)
#### << design modules <<
#### >> design monolith >>
monolith.target=$(call L.SO,$(T.NAME))
$(monolith.target): $(T.obj)
	@$(call U.EH,Build $(T.NAME) module)
	@$(call U.EX,$(call L.XX,$^,$@,$(L.OPTS) $(T.L.opts)))
monolith.build: $(monolith.target)
	@$(call U.EH,Build monolith complete....)
monolith.clean: $(T.clean)
	@$(call U.RM,$(monolith.target))
	@$(call U.EH,Clean monolith complete....)
#### << design monolith <<
#### >> design runable >>
runable.target=$(call L.RO,$(T.NAME))
$(runable.target): $(T.obj)
	@$(call U.EH,Build $(T.NAME) module)
	@$(call U.EX,$(call L.RX,$^,$@,$(L.OPTS) $(T.L.opts)))
runable.build: $(runable.target)
	@$(call U.EH,Build runable complete....)
runable.clean: $(T.clean)
	@$(call U.RM,$(runable.target))
	@$(call U.EH,Clean runable complete....)
#### << design runable <<
.PHONY: prepare prepare.local prepare.global modules.prepare runable.prepare monolith.prepare
prepare.global:
	@$(call U.EH,Preparing build lunique for PLATFORM=$(PLATFORM) with COMPILER=$(COMPILER) MODE=$(MODE)....)
prepare: prepare.global prepare.local $(call TARGET.DESIGN,prepare,$(DESIGN))
build: prepare $(call TARGET.DESIGN,build,$(DESIGN))
clean: $(call TARGET.DESIGN,clean,$(DESIGN))
## << global build rules

########## << implementation section << ###########
### $(call of,cthulhu)
