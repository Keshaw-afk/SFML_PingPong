#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>


#define WIDTH 800
#define HEIGHT 600

class Game
{
    public:
             Game();
        void run();
    private:
        void update(sf::Time deltaTime);
        void processEvents();
        void render();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    private:
        sf::RectangleShape rectangle;
        sf::RenderWindow window;
        bool isMovingUp;
        bool isMovingDown;
        bool isMovingLeft;
        bool isMovingRight;
        const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
        const float rectangleSpeed = 100.0f; 
};

Game::Game():window(sf::VideoMode({WIDTH, HEIGHT}), "Ping Pong"), 
    rectangle(),
    isMovingRight(false),
    isMovingLeft(false),
    isMovingUp(false),
    isMovingDown(false)
{

    rectangle.setSize(sf::Vector2f(100, 50));
    rectangle.setPosition({10, 20});
    rectangle.setFillColor(sf::Color::Magenta);

}


void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                window.close();
                break;

        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
    {
        isMovingUp = isPressed;
    }
    else if (key == sf::Keyboard::S)
    {
        isMovingDown = isPressed;
    }
    else if (key == sf::Keyboard::A)
    {
        isMovingLeft = isPressed;
    }
    else if (key == sf::Keyboard::D)
    {
        isMovingRight = isPressed;
    }
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);

    if (isMovingUp)
    {
        movement.y = movement.y - rectangleSpeed;
    }
    if (isMovingDown)
    {
        movement.y = movement.y + rectangleSpeed;
    }
    if (isMovingLeft)
    {
        movement.x = movement.x - rectangleSpeed;
    }
    if (isMovingRight)
    {
        movement.x = movement.x + rectangleSpeed;
    }

    rectangle.move(movement*deltaTime.asSeconds());
}

void Game::render()
{
    window.clear(sf::Color::White);
    window.draw(rectangle);
    window.display();
}

int main()
{
    Game game;
    game.run();
}
