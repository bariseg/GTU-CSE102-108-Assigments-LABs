all: clean compile run

compile: main.c
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@echo "FOR UBUNTU USE, STACK LIMIT MAY NEED TO BE ADJUST TO 16000..."
	@echo "PLEASE READ README.TXT FILE IN SCREENSHOTS FILE"
	@gcc -o test main.c

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
