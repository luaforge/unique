
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
object.$(1)+=$(call T.pagetarget,$(2),$(1))
#$(%.page): $(%.file)
$(call T.pagesrcn,$(3),$(1)):
	@echo -ne "$$(call T.emptypage)" > $$@
$(call T.pagetarget,$(2),$(1)): $(call T.pagesrcn,$(3),$(1)) $$(call T.pagetarget,$$(call T.$$($(2).model).depend,$(2),$(1)),$(1))
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

##
##  Images processing
##

$(D.img_dst)/%.png: $(D.img_src)/%.dia
	@echo Create image $*
	@dia --nosplash --export=$@ --export-to-format=png $^
$(D.img_dst)/%.png: $(D.img_src)/%.svg
	@echo Create image $*
	@inkscape --without-gui --export-bbox-page --export-png=$@ $^

source_image=$(wildcard $(D.img_src)/*.dia $(D.img_src)/*.svg)
target_image=$(basename $(notdir $(source_image)))
object_image=$(addsuffix .png,$(addprefix $(D.img_dst)/,$(target_image)))

image.build: $(object_image)
image.clean:
	@echo Clean images
	@rm -f $(object_image)
image.probe:
	@echo Generated images
	@echo source_image=$(source_image)
	@echo target_image=$(target_image)
	@echo object_image=$(object_image)

batch_image=$(addprefix image.,$(1))

##
##  Style Sheet
##

source_style=$(wildcard $(D.sty_src)/*.css $(D.sty_src)/*.html)
target_style=$(notdir $(source_style))
object_style=$(addprefix $(D.sty_dst)/,$(target_style))

$(D.sty_dst)/%.html: $(D.sty_src)/%.html
	@echo Generate $*
	@cp $< $@
$(D.sty_dst)/%.css: $(D.sty_src)/%.css
	@echo Generate $*
	@cp $< $@

style.build: $(object_style)
style.clean:
	@echo Clean styles
	@rm -f $(object_style)
style.probe:
	@echo Generated styles
	@echo source_style=$(source_style)
	@echo target_style=$(target_style)
	@echo object_style=$(object_style)


build: $(call batch_group,build) $(call batch_image,build) style.build
clean: $(call batch_group,clean) $(call batch_image,clean) style.clean
probe: $(call batch_group,probe) $(call batch_image,probe) style.probe
	@echo lang=$(lang)
	@echo build targets: $(call batch_group,build) $(call batch_image,build)
	@echo clean targets: $(call batch_group,clean) $(call batch_image,clean)
