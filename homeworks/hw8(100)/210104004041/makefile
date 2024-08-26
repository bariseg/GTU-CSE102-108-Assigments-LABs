all: clean compile run

compile: main.c util.c util.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c util.c

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@echo "STACK LIMIT IS INCREASED TO 64000 FOR YOU"
	@echo "WHICH MEANS YOU MAY SEE AROUND 1M MOVES"
	@echo "GENERALLY IT TAKES MAX 300K MOVES FOR THE COMPUTER TO SOLVE"
	@echo "Baris Eren Gezici 210104004041"
	@ulimit -s 64000 && ./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test