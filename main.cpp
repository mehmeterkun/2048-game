#include <SFML/Graphics.hpp>

int main() {
    // siyah bir ekran oluşacak
    sf::RenderWindow window(sf::VideoMode(800, 800), "2048 ");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }
    return 0;
}