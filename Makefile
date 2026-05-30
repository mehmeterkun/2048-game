# Derleyici ve bayraklar
CXX = g++
# -Iinclude sayesinde kodun içindeki #include "Board.hpp" kısmını
# include klasöründe otomatik arayacak.
CXXFLAGS = -std=c++17 -Wall -Iinclude
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Hedef dosya
TARGET = 2048

# Kaynak dosyalar (src klasöründekiler)
SOURCES = src/main.cpp src/Board.cpp src/Tile.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Derleme kuralları
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

# src içindeki .cpp dosyalarını derler
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Temizleme
clean:
	rm -f src/*.o 2048.exe