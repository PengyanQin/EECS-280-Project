checkpoint-tests: Card_tests Pack_tests Player_tests

# Build Card unit test executable
Card_tests: Card_tests.cpp Card.cpp Card.h
	g++ -pedantic -Wall -Werror -O1 Card_tests.cpp Card.cpp -o Card_tests

# Build Pack unit test executable
Pack_tests: Pack_tests.cpp Pack.cpp Pack.h Card.cpp Card.h
	g++ -pedantic -Wall -Werror -O1 Pack_tests.cpp Pack.cpp Card.cpp -o Pack_tests

# Build Player unit test executable
Player_tests: Player_tests.cpp Player.cpp Player.h Card.cpp Card.h
	g++ -pedantic -Wall -Werror -O1 Player_tests.cpp Player.cpp Card.cpp -o Player_tests

# Build the top-level euchre executable
euchre: euchre.cpp Game.cpp Game.h Player.cpp Player.h Pack.cpp Pack.h Card.cpp Card.h
	g++ -pedantic -Wall -Werror -O1 euchre.cpp Game.cpp Player.cpp Pack.cpp Card.cpp -o euchre

# Run regression test and check output
test: Card_tests Pack_tests Player_tests euchre
	./Card_tests > Card_tests.out
	./Pack_tests > Pack_tests.out
	./Player_tests > Player_tests.out
	./euchre pack.in noshuffle 1 Alice Bob Cathy Drew > euchre_test00.out
	diff -q euchre_test00.out euchre_test00.out.correct
	./euchre pack.in shuffle 10 Alice Bob Cathy Drew > euchre_test01.out
	diff -q euchre_test01.out euchre_test01.out.correct

checkpoint-tar: Card_tests.cpp Card.cpp Pack_tests.cpp Pack.cpp \
	            Player_tests.cpp Player.cpp group.txt
	tar -czvf checkpoint-submit.tar.gz $^

final-tar: Card_tests.cpp Card.cpp Pack_tests.cpp Pack.cpp \
	       Player_tests.cpp Player.cpp euchre.cpp Game.cpp group.txt
	tar -czvf final-submit.tar.gz $^

# type "make clean" to delete executables and temporary files
clean :
	rm -vf *.out euchre Card_tests Pack_tests Player_tests
