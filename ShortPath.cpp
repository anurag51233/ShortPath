#include <SFML/Graphics.hpp>



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    
    
    sf::Vertex line[2] = {
    sf::Vertex(sf::Vector2f(100, 100)),
    sf::Vertex(sf::Vector2f(400, 300))
    };
    // Set the line color (optional)
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(line, 2, sf::Lines);
        window.display();
    }

    return 0;
}