cc = gcc
prog = cells-mo-fucker
objs = $(subst .c,.o,$(wildcard *.c))
deps = ExtractPO.h

$(prog): $(objs)
	$(cc) $(objs) -o $(prog) 

%.o: %.c $(deps)
	$(cc) -c $< -o $@ 

clean:
	rm -rf *.o $(prog)
