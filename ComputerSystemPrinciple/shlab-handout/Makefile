# Makefile for the CS:APP Shell Lab

TEAM = NOBODY
VERSION = 1
HANDINDIR = .
DRIVER = ./sdriver.pl
TSH = ./tsh
TSHREF = ./tshref
TSHARGS = "-p"
CC = gcc
CFLAGS = -Wall -O2
FILES = $(TSH) ./myspin ./mysplit ./mystop ./myint

all: $(FILES)

##################
# Handin your work
##################
handin:
	cp tsh.c $(HANDINDIR)/$(TEAM)-$(VERSION)-tsh.c


##################
# Regression tests
##################

# Run tests using the student's shell program
test01:
	$(DRIVER) -t trace01.txt -s $(TSH) -a $(TSHARGS)
test02:
	$(DRIVER) -t trace02.txt -s $(TSH) -a $(TSHARGS)
test03:
	$(DRIVER) -t trace03.txt -s $(TSH) -a $(TSHARGS)
test04:
	$(DRIVER) -t trace04.txt -s $(TSH) -a $(TSHARGS)
test05:
	$(DRIVER) -t trace05.txt -s $(TSH) -a $(TSHARGS)
test06:
	$(DRIVER) -t trace06.txt -s $(TSH) -a $(TSHARGS)
test07:
	$(DRIVER) -t trace07.txt -s $(TSH) -a $(TSHARGS)
test08:
	$(DRIVER) -t trace08.txt -s $(TSH) -a $(TSHARGS)
test09:
	$(DRIVER) -t trace09.txt -s $(TSH) -a $(TSHARGS)
test10:
	$(DRIVER) -t trace10.txt -s $(TSH) -a $(TSHARGS)
test11:
	$(DRIVER) -t trace11.txt -s $(TSH) -a $(TSHARGS)
test12:
	$(DRIVER) -t trace12.txt -s $(TSH) -a $(TSHARGS)
test13:
	$(DRIVER) -t trace13.txt -s $(TSH) -a $(TSHARGS)
test14:
	$(DRIVER) -t trace14.txt -s $(TSH) -a $(TSHARGS)
test15:
	$(DRIVER) -t trace15.txt -s $(TSH) -a $(TSHARGS)
test16:
	$(DRIVER) -t trace16.txt -s $(TSH) -a $(TSHARGS)

# Run the tests using the reference shell program
rtest01:
	$(DRIVER) -t trace01.txt -s $(TSHREF) -a $(TSHARGS)
rtest02:
	$(DRIVER) -t trace02.txt -s $(TSHREF) -a $(TSHARGS)
rtest03:
	$(DRIVER) -t trace03.txt -s $(TSHREF) -a $(TSHARGS)
rtest04:
	$(DRIVER) -t trace04.txt -s $(TSHREF) -a $(TSHARGS)
rtest05:
	$(DRIVER) -t trace05.txt -s $(TSHREF) -a $(TSHARGS)
rtest06:
	$(DRIVER) -t trace06.txt -s $(TSHREF) -a $(TSHARGS)
rtest07:
	$(DRIVER) -t trace07.txt -s $(TSHREF) -a $(TSHARGS)
rtest08:
	$(DRIVER) -t trace08.txt -s $(TSHREF) -a $(TSHARGS)
rtest09:
	$(DRIVER) -t trace09.txt -s $(TSHREF) -a $(TSHARGS)
rtest10:
	$(DRIVER) -t trace10.txt -s $(TSHREF) -a $(TSHARGS)
rtest11:
	$(DRIVER) -t trace11.txt -s $(TSHREF) -a $(TSHARGS)
rtest12:
	$(DRIVER) -t trace12.txt -s $(TSHREF) -a $(TSHARGS)
rtest13:
	$(DRIVER) -t trace13.txt -s $(TSHREF) -a $(TSHARGS)
rtest14:
	$(DRIVER) -t trace14.txt -s $(TSHREF) -a $(TSHARGS)
rtest15:
	$(DRIVER) -t trace15.txt -s $(TSHREF) -a $(TSHARGS)
rtest16:
	$(DRIVER) -t trace16.txt -s $(TSHREF) -a $(TSHARGS)


# clean up
clean:
	rm -f $(FILES) *.o *~

# Run ALL tests (test01 → test16)
test-all:
	$(DRIVER) -t trace01.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace02.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace03.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace04.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace05.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace06.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace07.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace08.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace09.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace10.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace11.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace12.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace13.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace14.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace15.txt -s $(TSH) -a $(TSHARGS)
	$(DRIVER) -t trace16.txt -s $(TSH) -a $(TSHARGS)

# Run ALL tests on reference shell
rtest-all:
	$(DRIVER) -t trace01.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace02.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace03.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace04.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace05.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace06.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace07.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace08.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace09.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace10.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace11.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace12.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace13.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace14.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace15.txt -s $(TSHREF) -a $(TSHARGS)
	$(DRIVER) -t trace16.txt -s $(TSHREF) -a $(TSHARGS)


# ==============================
#  Diff бүх тестүүдийн output
# ==============================

DIFFOUT = diffout

diff-all:
	@mkdir -p $(DIFFOUT)
	@echo "Running all tests and generating diffs..."

	@for t in trace01 trace02 trace03 trace04 trace05 trace06 trace07 trace08 trace09 trace10 trace11 trace12 trace13 trace14 trace15 trace16; do \
		echo "==> Checking $$t"; \
		$(DRIVER) -t $$t.txt -s $(TSH) -a $(TSHARGS) > $(DIFFOUT)/$$t.my; \
		$(DRIVER) -t $$t.txt -s $(TSHREF) -a $(TSHARGS) > $(DIFFOUT)/$$t.ref; \
		diff -u $(DIFFOUT)/$$t.ref $(DIFFOUT)/$$t.my || true; \
	done

	@echo "Done. Check the $(DIFFOUT)/ folder for results."


