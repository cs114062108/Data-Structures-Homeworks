CXX = g++
WFlags = -Wall -fexec-charset=big5

objdir = objs

# -- Sources --
root_sources = $(wildcard *.cpp)
root_targets = $(patsubst %.cpp, %, $(root_sources))

filter_dirs_names = $(objdir) automake cheat_sheets
to_filter = $(patsubst %, %/, $(filter_dirs_names))

nest_dirs = $(patsubst %/, %, $(filter-out $(to_filter), $(wildcard */)))
nest_objdirs = $(foreach dir, $(nest_dirs), $(dir)/$(objdir))
nest_sources = $(foreach dir, $(nest_dirs), $(wildcard $(dir)/*.cpp))

nest_targets = $(nest_dirs)
all_targets = $(root_targets) $(nest_targets)

nest_exes = $(patsubst %.cpp, %.exe, $(nest_sources))
root_exes = $(patsubst %, %.exe, $(root_targets))
all_exes = $(nest_exes) $(root_exes)

# -- Defined nested build rule --
define NEST_BUILD_RULE

1_sources = $$(wildcard $(1)/*.cpp)
1_cpps = $$(notdir $$(1_sources))
1_exes = $$(patsubst %.cpp, %.exe, $$(1_cpps))
1_targets = $$(patsubst %.cpp, %, $$(1_sources))

$(1)/$(objdir):
	mkdir -p $$@

$(1)/$(objdir)/%.o: $(1)/%.cpp | $(1)/$(objdir)
	$$(CXX) $$(WFlags) -c $$^ -o $$@

$$(1_exes): %.exe: $(1)/$(objdir)/%.o
	$$(CXX) $$^ -o $(1)/$$@

$(1): $$(1_exes)

endef

$(foreach dir, $(nest_dirs), $(eval $(call NEST_BUILD_RULE, $(dir))))

# -- Universal make logic --
$(objdir):
	mkdir -p $@

$(objdir)/%.o: %.cpp | $(objdir)
	$(CXX) $(WFlags) -c $^ -o $@

$(root_targets): %: $(objdir)/%.o
	$(CXX) $^ -o $@

# -- Targets --
# Precious the intermediate object sources
.PRECIOUS: $(objdir)/%.o

.PHONY: all clean

all: $(all_targets)
	@echo Exes: $(all_exes)

list_dirs: $(nest_dirs)
	@echo Nested Dirs: $^
	@echo Nested Dirs Names: $(patsubst %/, %, $^)
	@echo Nested Object Dirs: $(nest_objdirs)
	@echo Nested Sources: $(nest_sources)
	@echo Nested Targets: $(nest_targets)

clean: 
	rm -rf $(objdir) $(nest_objdirs)
	rm -f $(all_exes)
