#include <SFML/Graphics.hpp>
#include <cmath>

const float I = 60.f;

const float MOVE = 300.f;

void rotateX3D(float theta, float (&nodes)[8][3])
{
    //RotateX3D
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    for(int i = 0; i<sizeof(nodes)/sizeof(nodes[0]); i++)
    {
        float x = nodes[i][0];
        float z = nodes[i][2];

        nodes[i][0] = x * cosTheta - z * sinTheta;
        nodes[i][2] = z * cosTheta + x * sinTheta;
    }

}

void rotateY3D(float theta, float (&nodes)[8][3])
{
    //RotateX3D
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    for(int i = 0; i<sizeof(nodes)/sizeof(nodes[0]); i++)
    {
        float y = nodes[i][1];
        float z = nodes[i][2];

        nodes[i][1] = y * cosTheta - z * sinTheta;
        nodes[i][2] = z * cosTheta + y * sinTheta;
    }

}
void rotateZ3D(float theta, float (&nodes)[8][3])
{
    //RotateX3D
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    for(int i = 0; i<sizeof(nodes)/sizeof(nodes[0]); i++)
    {
        float x = nodes[i][0];
        float y= nodes[i][2];

        nodes[i][0] = x * cosTheta - y * sinTheta;
        nodes[i][2] = y * cosTheta + x * sinTheta;
    }

}

double mx=0,my=0,mx0=0,my0=0; //globals with mouse position
int MODE = 2;

int main()
{
    float nodes[8][3] = {
    {-100, -100, -100},  //node 0
    {-100, -100, 100},   //node 1
    {-100, 100, -100},   //node 2
    {-100, 100, 100},    //node 3
    {100, -100, -100},   //node 4
    {100,  -100, 100},   //node 5
    {100,  100,  -100},  //node 6
    {100,  100,  100}   //node 7
    };

    int edges[12][2] =
    {
    {0, 1}, //edge 0
    {1, 3}, //edge 1
    {3, 2}, //edge 2
    {2, 0}, //edge 3
    {4, 5}, //edge 4
    {5, 7}, //edge 5
    {7, 6}, //edge 6
    {6, 4}, //edge 7
    {0, 4}, //edge 8
    {1, 5}, //edge 9
    {2, 6}, //edge 10
    {3, 7}  //edge 11
    };
    sf::RenderWindow window(sf::VideoMode(600,600), "Rotating Cube", sf::Style::Titlebar | sf::Style::Close); //Window
    window.setFramerateLimit(30);
    sf::ConvexShape sh(4);
    sh.setOrigin(sf::Vector2f(-300.f, -300.f)); //If shit breaks try commenting  this first, why -300 - because it is relative to the most left point of the object.
    //Okay so for reason this sets it according to the middle of the square, not the upper-left vertex, WTF?

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num2) MODE = 2;
                if (event.key.code == sf::Keyboard::Num1) MODE = 1;
            }


            //mouse move
            if (MODE == 1)
            {
            mx0=mx; mx = sf::Mouse::getPosition().x;
            my0=my; my = sf::Mouse::getPosition().y;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    rotateX3D((mx-mx0)*M_PI/180, nodes);
                    rotateY3D((my-my0)*M_PI/180, nodes);
                    printf("MOVE X DEGRESS %.2 f MOVE Y DEGRESS %.2 f \n", mx-mx0, my-my0);
                }
            }
        }

        if (MODE == 2)
            {
                rotateX3D(M_PI/180, nodes);
                rotateY3D(M_PI/180, nodes);
                rotateZ3D(M_PI/180, nodes);
            }



        //all the rotation code before drawing code!
        window.clear(sf::Color::Black);
        //draw nodes
        sf::CircleShape node_draw(5);
        node_draw.setFillColor(sf::Color::Green);
        node_draw.setOrigin(-MOVE, -MOVE);
        for(int i = 0; i<sizeof(nodes)/sizeof(nodes[0]); i++)
        {
            node_draw.setPosition(nodes[i][0]-node_draw.getRadius(), nodes[i][1]-node_draw.getRadius());
            window.draw(node_draw);
        }

        //draw edges
        sf::VertexArray edge_draw(sf::Lines, 2);
        for (int i = 0; i<sizeof(edges)/sizeof(edges[0]); i++)
        {
            int e0 = edges[i][0];
            int e1 = edges[i][1];
            edge_draw[0].position = sf::Vector2f(nodes[e0][0]+MOVE, nodes[e0][1]+MOVE);
            edge_draw[1].position = sf::Vector2f(nodes[e1][0]+MOVE, nodes[e1][1]+MOVE);

            window.draw(edge_draw);
        }


        window.display();

    }
}
