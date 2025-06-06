clear:
	rm -rf *.o *.a *_test integral quadratic_equations linked_list stack

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

quadratic_equations.o: lab1/quadratic_equations.c lab1/quadratic_equations.h
	gcc -g -c lab1/quadratic_equations.c -o quadratic_equations.o -lm

quadratic_equations.a: quadratic_equations.o
	ar rc quadratic_equations.a quadratic_equations.o -lm

integral.o: lab1/integral.c lab1/integral.h
	gcc -g -c lab1/integral.c -o integral.o -lm

integral.a: integral.o
	ar rc integral.a integral.o -lm

linked_list.o: lab1/linked_list.c lab1/linked_list.h
	gcc -g -c lab1/linked_list.c -o linked_list.o

linked_list.a: linked_list.o
	ar rc linked_list.a linked_list.o

stack.o: lab1/stack.c lab1/stack.h
	gcc -g -c lab1/stack.c -o stack.o

stack.a: stack.o
	ar rc stack.a stack.o

arraylist.o: lab2/arraylist.c lab2/arraylist.h
	gcc -g -c lab2/arraylist.c -o arraylist.o

arraylist.a: arraylist.o
	ar rc arraylist.a arraylist.o

hashtable.o: lab2/hashtable.c lab2/hashtable.h
	gcc -g -c lab2/hashtable.c -o hashtable.o

hashtable.a: hashtable.o
	ar rc hashtable.a hashtable.o

linear_allocator.o: lab2/linear_allocator.c lab2/linear_allocator.h
	gcc -g -c lab2/linear_allocator.c -o linear_allocator.o

linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o

pool_allocator.o: lab2/pool_allocator.c lab2/pool_allocator.h
	gcc -g -c lab2/pool_allocator.c -o pool_allocator.o

pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o

quadratic_equations_test.o: lab1/tests/quadratic_equations_test.c lab1/quadratic_equations.h
	gcc -g -c lab1/tests/quadratic_equations_test.c -o quadratic_equations_test.o -lm

quadratic_equations_test: quadratic_equations_test.o quadratic_equations.a
	gcc -g -static -o quadratic_equations_test quadratic_equations_test.o quadratic_equations.a -lm

integral_test.o: lab1/tests/integral_test.c lab1/integral.h
	gcc -g -c lab1/tests/integral_test.c -o integral_test.o -lm

integral_test: integral_test.o integral.a
	gcc -g -static -o integral_test integral_test.o integral.a -lm

linked_list_test.o: lab1/tests/linked_list_test.c lab1/linked_list.h
	gcc -g -c lab1/tests/linked_list_test.c -o linked_list_test.o

linked_list_test: linked_list_test.o linked_list.a
	gcc -g -static -o linked_list_test linked_list_test.o linked_list.a 

stack_test.o: lab1/tests/stack_test.c lab1/stack.h
	gcc -g -c lab1/tests/stack_test.c -o stack_test.o

stack_test: stack_test.o stack.a
	gcc -g -static -o stack_test stack_test.o stack.a 

arraylist_test.o: lab2/tests/arraylist_test.c lab2/arraylist.h
	gcc -g -c lab2/tests/arraylist_test.c -o arraylist_test.o

arraylist_test: arraylist_test.o arraylist.a
	gcc -g -static -o arraylist_test arraylist_test.o arraylist.a 

hashtable_test.o: lab2/tests/hashtable_test.c lab2/hashtable.h
	gcc -g -c lab2/tests/hashtable_test.c -o hashtable_test.o

hashtable_test: hashtable_test.o hashtable.a pool_allocator.a
	gcc -g -static -o hashtable_test hashtable_test.o hashtable.a  pool_allocator.a

linear_allocator_test.o: lab2/tests/linear_allocator_test.c lab2/linear_allocator.h
	gcc -g -c lab2/tests/linear_allocator_test.c -o linear_allocator_test.o

linear_allocator_test: linear_allocator_test.o linear_allocator.a
	gcc -g -static -o linear_allocator_test linear_allocator_test.o linear_allocator.a 

pool_allocator_test.o: lab2/tests/pool_allocator_test.c lab2/pool_allocator.h
	gcc -g -c lab2/tests/pool_allocator_test.c -o pool_allocator_test.o

pool_allocator_test: pool_allocator_test.o pool_allocator.a
	gcc -g -static -o pool_allocator_test pool_allocator_test.o pool_allocator.a 

integral: integral.o integral.a
	gcc -g -static -o integral integral.o integral.a -lm
	./integral

quadratic_equations: quadratic_equations.o quadratic_equations.a
	gcc -g -static -o quadratic_equations quadratic_equations.o quadratic_equations.a -lm
	./quadratic_equations

linked_list: linked_list.o linked_list.a
	gcc -g -static -o linked_list linked_list.o linked_list.a
	./linked_list

stack: stack.o stack.a
	gcc -g -static -o stack stack.o stack.a
	./stack

run_tests: quadratic_equations_test integral_test linked_list_test stack_test arraylist_test hashtable_test linear_allocator_test pool_allocator_test
	./quadratic_equations_test
	./integral_test
	./linked_list_test
	./stack_test
	./arraylist_test
	./hashtable_test
	./linear_allocator_test
	./pool_allocator_test
