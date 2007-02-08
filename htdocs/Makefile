
all: build

include config

-include src/tpl/*.html
-include src/tpl/*.make
-include src/opt/*.make

-include src/loc/*.make


define batch_template

#locale_name=$(LANG)/$(1)

#option=$(patsubst src/opt/%.make,%,$(wildcard src/opt/*.make))
#target=$(subst 9.,,$(subst 8.,,$(subst 7.,,$(subst 6.,,$(subst 5.,,$(subst 4.,,$(subst 3.,,$(subst 2.,,$(subst 1.,,$(subst 0.,,$(option)))))))))))
source.$(1)=$(foreach i,$(target),$(call T.pagesrcn,$($(i).name),$(1)))
object.$(1)=$(foreach i,$(target),$(call T.pagename,$($(i).name),$(1)))

probe.$(1):
	@echo LANG=$(1)
	@echo source=$$(source.$(1))
	@echo object=$$(object.$(1))
	@echo target=$(target)
#	@echo $(D.src) $(D.src)/*
#	@echo -ne T.menupanel="$(T.menupanel)"

#$(%.page): $(%.file)
%.$(1).html: $(D.src)/$(1)/%.html
	@echo Generate page $$* for LANG=$(1)
	@echo -ne "\
$$(call T.page,$$($$*.name),\
  $$(call T.menupanel,\
    $$(foreach i,$(target),\
      $$(if $$(findstring $$($$(i).name),$$*),\
        $$(call T.menuitem_active,$$($(1).$$(i).caption)),\
        $$(call T.menuitem,$$(call T.pagename,$$($$(i).name),$(1)),$$($(1).$$(i).caption))\
        )\
      ),\
    $$(foreach i,$(AVAILABLE_LANGS),\
      $$(if $$(findstring $$(i),$(1)),\
        $$(call T.langitem_active,$$($$(i).title)),\
        $$(call T.langitem,$$(call T.pagename,$$($$*.name),$$(i)),$$($$(i).title))\
        )\
      )\
    ),\
  $$(call T.headline,\
    $$($(1).$$*.title)\
    ),\
  $$(call M.$$($$*.model),$$($$*.name),$$(shell cat $$(call T.pagesrcn,$$($$*.name),$(1))),$$($$*.template),$(1))\
  )" > $$(call T.pagename,$$($$*.name),$(1))

#$(D.src)/$(1).%.html:
#	@echo -ne "$(T.emptypage)" > $@

build.$(1): $$(object.$(1))
	@echo Pages for LANG=$(1) generation complete....

clean.$(1): 
	@rm -f $$(object.$(1))
	@echo Pages for LANG=$(1) cleaning complete....

.PHONY: build.$(1) clean.$(1)
#.PRECIOUS: src/doc/%.html

endef

AVAILABLE_LANGS=$(notdir $(wildcard $(D.src)/*))
$(foreach i,$(AVAILABLE_LANGS),$(eval $(call batch_template,$(i))))
batch_group=$(addprefix $(1).,$(AVAILABLE_LANGS))

build: $(call batch_group,build)
clean: $(call batch_group,clean)
probe: $(call batch_group,probe)
	@echo AVAILABLE_LANGS=$(AVAILABLE_LANGS)

