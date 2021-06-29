OBJS=main.o Enemy.o Bonus_Item.o Bullet.o Player.o

EXE=simplegame
LDFLAGS_BASE=-Lexternal/lib -lsfml-system -lsfml-window -lsfml-graphics 
CXXFLAGS_BASE=-std=c++17 -Iexternal/include -Iinclude -DSFML_STATIC -c 

all: $(EXE) 

opt:
	$(MAKE) -B CXXFLAGS=-O3

$(EXE): $(OBJS)
	g++ $^ -o $@ $(LDFLAGS_BASE) $(LDFLAGS)

%.o: library/%.cpp
	g++ $^ -o $@ $(CXXFLAGS_BASE) $(CXXFLAGS)
