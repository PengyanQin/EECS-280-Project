CXX     := g++
CXXFLAGS := -Wall -Werror -pedantic -O1

deck_test_src = $(wildcard Deck_test[0-9][0-9].cpp)
deck_test_exes = $(deck_test_src:.cpp=)

player_test_src = $(wildcard Player_test[0-9][0-9].cpp)
player_test_exes = $(player_test_src:.cpp=)

all: Card_test00 Player_factory_test Deck_tests Player_tests blackjack

Card_test00: Card_test00.cpp Card.cpp
	$(CXX) $(CXXFLAGS) Card_test00.cpp Card.cpp -o Card_test00

Player_factory_test: Player_factory_test.cpp Card.cpp Hand.cpp Player.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

blackjack:  Card.cpp rand.cpp Hand.cpp Deck.cpp Player.cpp blackjack.cpp
	$(CXX) $(CXXFLAGS) Card.cpp rand.cpp Hand.cpp Deck.cpp Player.cpp blackjack.cpp -o blackjack

public_tests: Card_test00 Player_factory_test blackjack
	./Card_test00
	./Player_factory_test
	./blackjack 100 3 simple > blackjack.out
	diff -q blackjack_test00.out.correct blackjack.out

Deck_tests: $(deck_test_exes)
Player_tests: $(player_test_exes)

.PHONY: public_tests my_tests clean

my_tests: Deck_tests Player_tests
	@python run_my_tests.py

Deck_test%: Deck_test%.cpp Deck.cpp Card.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Player_test%: Player_test%.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

tar: group.txt Card.cpp Hand.cpp Deck.cpp Player.cpp blackjack.cpp \
	           Deck_test[0-9][0-9].cpp Player_test[0-9][0-9].cpp
	tar -czvf submit.tar.gz $^

clean:
	rm -vf blackjack *.out \
         Card_test[0-9][0-9] \
         Deck_test[0-9][0-9] \
         Player_test[0-9][0-9] \
         Player_factory_test
