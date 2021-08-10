cc = gcc

src_dir = src
build_dir = build

deps := $(wildcard $(src_dir)/*.h)
srcs := $(wildcard $(src_dir)/*.c)
objs := $(srcs:$(src_dir)/%.c=$(build_dir)/%.o)
prog := $(build_dir)/mo2po


.PHONY: _default _prepare clean


_default: all

_prepare:
	mkdir -p build


all: _prepare $(prog)

$(prog): $(objs)
	$(cc) $^ -o $@

$(objs): $(build_dir)/%.o: $(src_dir)/%.c $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(build_dir)
