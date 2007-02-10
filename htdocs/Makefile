
all: build

include config

-include src/tpl/*.html
-include src/tpl/*.make
-include src/opt/*.make

-include src/loc/*.make

# $(1) - page lang
define batch_template
$(info Generate rule for locale LANG=$(1))

-include $(call T.pagemake,locale,$(1))
#source.$(1)=$(foreach i,$(target),$(call T.pagesrcn,$($(i).name),$(1)))
#object.$(1)=$(foreach i,$(target),$(call T.pagename,$($(i).name),$(1)))

probe.$(1):
	@echo LANG=$(1)
	@echo source=$$(source.$(1))
	@echo object=$$(object.$(1))
	@echo target=$(target)
#	@echo $(D.src) $(D.src)/*
#	@echo -ne T.menupanel="$(T.menupanel)"
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

# $(1) - page lang, $(2) - page name, $(3) - page source
define batch_page
$(info Generate rule for page LANG=$(1),PAGE=$(2),SOURCE=$(3))
-include $(call T.pagemake,$(3),$(1))
source.$(1)+=$(call T.pagesrcn,$(3),$(1))
object.$(1)+=$(call T.pagename,$(2),$(1))
#$(%.page): $(%.file)
$(call T.pagesrcn,$(3),$(1)):
	@echo -ne "$$(call T.emptypage)" > $$@
$(call T.pagename,$(2),$(1)): $(call T.pagesrcn,$(3),$(1)) $$(call T.pagename,$$(call T.$$($(2).model).depend,$(2),$(1)),$(1))
	@echo Generate page $$@ LANG=$(1),PAGE=$(2),SOURCE=$(3) Depend $$^
	@echo -ne "\
$$(call T.page,$(2),\
  $$(call T.menupanel,\
    $$(foreach i,$(target),\
      $$(if $$(findstring $$(i),$(2)),\
        $$(call T.menuitem_active,$$($(1).$$(i).caption)),\
        $$(call T.menuitem,$$(call T.pagename,$$(i),$(1)),$$($(1).$$(i).caption))\
        )\
      ),\
    $$(foreach i,$(lang),\
      $$(if $$(findstring $$(i),$(1)),\
        $$(call T.langitem_active,$$($$(i).title)),\
        $$(call T.langitem,$$(call T.pagename,$(2),$$(i)),$$($$(i).title))\
        )\
      )\
    ),\
  $$(call T.headline,\
    $$($(1).$(2).title)\
    ),\
  $$(call M.$$($(2).model),$(2),$$(shell cat $$<),$$($(2).template),$(1))\
  )" > $$@
endef


$(foreach l,$(lang),\
$(foreach p,$(target),\
$(eval $(call batch_page,$(l),$(p),$(p)))))

$(foreach l,$(lang),\
$(foreach p,$(target),\
$(foreach r,$(call T.$($(p).model).depend,$(p),$(l)),\
$(eval $(call batch_page,$(l),$(r),$(call T.$($(p).model).require,$(r),$(l)))))))

$(foreach l,$(lang),\
$(eval $(call batch_template,$(l))))
batch_group=$(addprefix $(1).,$(lang))


build: $(call batch_group,build)
clean: $(call batch_group,clean)
probe: $(call batch_group,probe)
	@echo lang=$(lang)

