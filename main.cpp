#include <SFML/Graphics.hpp>

int main() {
    // asagıdaki kod pencere olusturuyo
    sf::RenderWindow pencere(sf::VideoMode(800, 800), "2048", sf::Style::Default);

    while (pencere.isOpen()){
        sf::Event olay;
        while (pencere.pollEvent(olay)){
            if (olay.type == sf::Event::Closed)
                pencere.close();
        }

        pencere.clear(sf::Color::Black); // Arka plan siyah

        // yesil bir kare cizdiriyor
        sf::RectangleShape testKaresi(sf::Vector2f(400.0f, 400.0f));
        testKaresi.setFillColor(sf::Color::Green);
        testKaresi.setPosition(200.0f, 200.0f); // orta
        
        pencere.draw(testKaresi);

        pencere.display();
    }
    return 0;
}