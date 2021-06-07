#include <SFML/Graphics.hpp>
#include <cmath>

const float TH = 1.f; // Thickness of the lines
const float LONG = 150.f; //Length of the lines
const float OFFSET = 100.f;
const float I = 60.f;

float SIZE = 40;
float SCALE = 1;

float PIVX = 0.f;
float PIVY = 0.f;
float ANGLEZ = 1 * (M_PI/180); // THE FIRST NUMBER IS DEGREES, THE MULTIPLICATION IS HERE BCUS I WANT RADIANS INSTEAD

float MOVEX = 0.f;
float MOVEY = 0.f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(600,600), "Square Convex", sf::Style::Titlebar | sf::Style::Close); //Window
    window.setFramerateLimit(30);
    sf::ConvexShape sh(4);
    sh.setOrigin(sf::Vector2f(-300.f, -300.f)); //If shit breaks try commenting  this first, why -300 - because it is relative to the most left point of the object.
    //Okay so for reason this sets it according to the middle of the square, not the upper-left vertex, WTF?

    //set the coordinates of points for the square
    sh.setPoint(0, sf::Vector2f(-I, -I));
    sh.setPoint(1, sf::Vector2f(I, -I));
    sh.setPoint(2, sf::Vector2f(I, I));
    sh.setPoint(3, sf::Vector2f(-I, I));

    //set the parameters for the square
    sh.setOutlineThickness(1.f);
    sh.setOutlineColor(sf::Color::White);
    sh.setFillColor(sf::Color::Transparent);

    //pivot object
    sf::CircleShape pivot_point(5);
    pivot_point.setFillColor(sf::Color::Cyan);
    pivot_point.setOrigin(sf::Vector2f(-300.f+pivot_point.getRadius(), -300.f+pivot_point.getRadius()));
    pivot_point.setPosition(sf::Vector2f(0.f, 0.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            //the code below is setting the controls for the square
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)  MOVEX-=2;
                if (event.key.code == sf::Keyboard::Right)  MOVEX+=2;
                if (event.key.code == sf::Keyboard::Up)  MOVEY-=2;
                if (event.key.code == sf::Keyboard::Down)  MOVEY+=2;

                if (event.key.code == sf::Keyboard::RBracket)  SCALE *= 1.02;
                if (event.key.code == sf::Keyboard::LBracket)  SCALE /= 1.02;

                if (event.key.code == sf::Keyboard::F) PIVX -=2;
                if (event.key.code == sf::Keyboard::H) PIVX +=2;
                if (event.key.code == sf::Keyboard::T) PIVY -=2;
                if (event.key.code == sf::Keyboard::G) PIVY +=2;

                if (event.key.code == sf::Keyboard::Num1) ANGLEZ -= M_PI/180;
                if (event.key.code == sf::Keyboard::Num2) ANGLEZ += M_PI/180;
            }


        }

        for (int i=0; i<4; i++)
        {
            //set the square vertices positions
            float XD = sh.getPoint(i).x - PIVX;
            float YD = sh.getPoint(i).y - PIVY;

            float XROTOFFSET = XD * cos(ANGLEZ) - YD * sin(ANGLEZ) - XD;
            float YROTOFFSET = XD * sin(ANGLEZ) + YD * cos(ANGLEZ) - YD;

            float X = (sh.getPoint(i).x + XROTOFFSET) / SCALE + MOVEX;
            float Y = (sh.getPoint(i).y + YROTOFFSET) / SCALE + MOVEY;

            sh.setPoint(i, sf::Vector2f(X, Y));

            //set the pivot position
            pivot_point.setPosition(sf::Vector2f((PIVX/SCALE)+MOVEX, (PIVY/SCALE)+MOVEY));
            //Draw_Pixel (PIVX/SCALE)+MOVEX+400, (PIVY/SCALE)+MOVEY+300 - WHY +300 and +400???
        }

        //this is my addition, possible bugs
        SCALE = 1.f;
        MOVEX = 0.f;
        MOVEY = 0.f;

        window.clear(sf::Color::Black);
        window.draw(sh);
        window.draw(pivot_point);
        window.display();

    }
}
