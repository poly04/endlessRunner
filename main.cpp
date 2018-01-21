#include <SFML/Graphics.hpp>

float speed = 5;
float gravity = 7;

bool jumping = false;
int jumpFrame = 0;

bool loser = false;

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Endless Runner");
    window.setFramerateLimit(60);

    sf::View camera;
    camera.setCenter(400, 300);
    camera.setSize(800, 600);

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(20, 100));
    shape.setPosition(400 - (shape.getSize().x / 2), 0);
    shape.setFillColor(sf::Color::Blue);

    sf::RectangleShape ground;
    ground.setSize(sf::Vector2f(1000, 200));
    ground.setPosition(0, 400);
    ground.setFillColor(sf::Color::Green);

    sf::RectangleShape obstacle;
    obstacle.setSize(sf::Vector2f(45, 50));
    obstacle.setPosition(800, 350);
    obstacle.setFillColor(sf::Color::Yellow);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    //jump
                    jumping = true;
                }
            }
        }

        if(jumping)
        {
            shape.move(speed, -gravity);

            jumpFrame++;
            if(jumpFrame >= 30)
            {
                shape.move(0, gravity);
                jumpFrame = 0;
                jumping = false;
            }
        } else {
            shape.move(speed, gravity);
        }

        camera.move(speed, 0);
        ground.move(speed, 0);

        //ground collisions
        if((shape.getGlobalBounds().top + shape.getGlobalBounds().height) > ground.getGlobalBounds().top)
        {
            shape.setPosition(shape.getPosition().x, ground.getPosition().y - shape.getSize().y);
        }

        //obstacle wrap around
        if(obstacle.getPosition().x + obstacle.getSize().x < camera.getCenter().x - (camera.getSize().x / 2))
        {
            obstacle.move(800 + obstacle.getSize().x, 0);
        }

        //obstacle player collisions
        if(shape.getPosition().x > obstacle.getPosition().x &&
           shape.getPosition().y + shape.getSize().y > obstacle.getPosition().y &&
           shape.getPosition().x + shape.getSize().x < obstacle.getPosition().x + obstacle.getSize().x)
        {
            loser = true;
        }

        window.clear();

        window.setView(camera);

        if(loser != true)
        {
            window.draw(ground);
            window.draw(shape);
            window.draw(obstacle);
        }

        window.display();
    }

    return 0;
}
