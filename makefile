CC = g++
WFlags = -Wall

objdir = objs

$(objdir):
	mkdir -p $@

root_sources = $(wildcard *.cpp)
root_targets = $(patsubst %.cpp, %, $(root_sources))
all_targets = $(root_targets)

$(objdir)/%.o: %.cpp | $(objdir)
	$(CC) $(WFlags) -c $^ -o $@

$(root_targets): %: $(objdir)/%.o
	$(CC) $(WFlags) $^ -o $@

# Precious the intermediate object sources
.PRECIOUS: $(objdir)/%.o

.PHONY: all clean

all: $(all_targets)
	@echo Targets: $(all_targets)

clean: 
	rm -rf $(objdir)
	rm -f $(all_targets)
