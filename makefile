CXX = g++
WFlags = -Wall

objdir = objs

# -- Sources --
root_sources = $(wildcard *.cpp)
root_targets = $(patsubst %.cpp, %, $(root_sources))

filter_dirs_names = $(objdir) automake
to_filter = $(patsubst %, %/, $(filter_dirs_names))

nest_dirs = $(patsubst %/, %/, $(filter-out $(to_filter), $(wildcard */)))
nest_objdirs = $(foreach dir, $(nest_dirs), $(dir)$(objdir))
nest_sources = $(foreach dir, $(nest_dirs), $(wildcard $(dir)*.cpp))
nest_targets = $(patsubst %.cpp, %, $(nest_sources))

all_targets = $(root_targets) $(nest_targets)

# -- Universal make logic --
$(objdir):
	mkdir -p $@

$(objdir)/%.o: %.cpp | $(objdir)
	$(CXX) $(WFlags) -c $^ -o $@

$(root_targets): %: $(objdir)/%.o
	$(CXX) $^ -o $@

$(nest_targets): %: %.cpp
	$(CXX) $(WFlags) $^ -o $@

# -- Targets --
# Precious the intermediate object sources
.PRECIOUS: $(objdir)/%.o

.PHONY: all clean

all: $(all_targets)
	@echo Targets: $(all_targets)

list_dirs: $(nest_dirs)
	@echo Nested Dirs: $^
	@echo Nested Dirs Names: $(patsubst %/, %, $^)
	@echo Nested Object Dirs: $(nest_objdirs)
	@echo Nested Sources: $(nest_sources)
	@echo Nested Targets: $(nest_targets)

clean: 
	rm -rf $(objdir)
	rm -f $(all_targets)
