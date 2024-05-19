cc = gcc

src_dir = src
build_dir = build
test_dir = tests

deps := $(wildcard $(src_dir)/*.h)
srcs := $(wildcard $(src_dir)/*.c)
objs := $(srcs:$(src_dir)/%.c=$(build_dir)/%.o)
prog := $(build_dir)/mo2po


.PHONY: _default _prepare all test clean


_default: all

_prepare:
	mkdir -p build


all: _prepare $(prog)

$(prog): $(objs)
	$(cc) $^ -o $@

$(objs): $(build_dir)/%.o: $(src_dir)/%.c $(deps)
	$(cc) -c $< -o $@

test: all
	cd $(test_dir) && ./test.sh ../$(prog)

clean:
	$(RM) -r $(build_dir)
