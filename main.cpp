#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <vector>
#include <cmath>   
#include <iostream>
#include "List.h"

#define PI 3.1415926535898


sf::RenderWindow window(sf::VideoMode(2000, 1000), "SFML works!");

void perimeter(std::vector<std::pair<float, float>> figure);


void ellipse_square(float radius_x, float radius_y)
{
    std::cout << "Square= " << radius_x * radius_y * PI;
}
void ellipse_perimeter(float radius_x, float radius_y)
{
    std::cout << "Perimetre= " << 4.0 * ((PI * radius_x * radius_y) + pow(radius_x - radius_y, 2)) / (radius_x + radius_y);
}
void ellipse_(std::vector<float> ell) {
    float radius_x = ell[0];
    float radius_y = ell[1];
    int X = ell[2];
    int Y = ell[3];
    radius_x *= 50;
    radius_y *= 50;
    unsigned short quality = 70;

    sf::ConvexShape ellipse;
    ellipse.setPointCount(quality);

    for (unsigned short i = 0; i < quality; ++i) {
        float rad = (360 / quality * i) / (360 / PI / 2);
        float x = cos(rad) * radius_x;
        float y = sin(rad) * radius_y;

        ellipse.setPoint(i, sf::Vector2f(x, y));
    };

    ellipse.setPosition(1000 - X * 50, 500 - Y * 50);
    ellipse.setFillColor(sf::Color::Black);
    ellipse.setOutlineColor(sf::Color::White);
    ellipse.setOutlineThickness(2);


    window.draw(ellipse);

    ellipse_perimeter(radius_x / 50, radius_y / 50);
    ellipse_square(radius_x / 50, radius_y / 50);
}


void square(std::vector<std::pair<float, float>> figure)
{
    double A = 0, B = 0;

    for (int i = 0; i < figure.size(); i++) {
        if (i < figure.size() - 1)
            A += std::get<0>(figure[i]) * std::get<1>(figure[i + 1]);
        else {
            A += std::get<0>(figure[i]) * std::get<1>(figure[0]);
        }
    }
    for (int i = 0; i < figure.size(); i++) {
        if (i < figure.size() - 1)
            B += std::get<1>(figure[i]) * std::get<0>(figure[i + 1]);
        else {
            B += std::get<1>(figure[i]) * std::get<0>(figure[0]);
        }
    }

    std::cout << "Square = " << abs((A - B) / 2.0);
}

void create_figure(std::vector<std::pair<float, float>> figure) {

    sf::ConvexShape convex;


    convex.setPointCount(figure.size());

    for (int i = 0; i < figure.size(); i++)
    {
        convex.setPoint(i, sf::Vector2f(1000 + 50 * std::get<0>(figure[i]), 500 + 50 * std::get<1>(figure[i])));
    }
    convex.setOutlineColor(sf::Color::White);
    convex.setOutlineThickness(2);
    convex.setFillColor(sf::Color::Black);

    window.draw(convex);
    perimeter(figure);
    square(figure);
}
double length(std::pair<float, float> pair1, std::pair<float, float> pair2)
{
    return sqrt(double(pow(std::get<0>(pair1) + std::get<0>(pair2), 2) + pow(std::get<1>(pair1) + std::get<1>(pair2), 2)));
}

void perimeter(std::vector<std::pair<float, float>> figure)
{
    double P = 0;
    for (int i = 0; i < figure.size(); i++)
    {
        if (i < figure.size() - 1) {
            P += length(figure[i], figure[i + 1]);
        }
        else {
            P += length(figure[i], figure[0]);
        }
    }
    std::cout << "perimeter: " << P << "\n";
}
void net()
{
    sf::Font font;
    sf::Text text;
    if (!font.loadFromFile("font/OpenSans-Bold.ttf"))
    {
        window.display();
    }
    text.setFont(font);
    text.setCharacterSize(15);

    text.setFillColor(sf::Color::White);

    sf::RectangleShape line1(sf::Vector2f(2000, 2));
    line1.setPosition(0, 500);

    sf::RectangleShape line2(sf::Vector2f(1000, 2));
    line2.setPosition(1000, 0);
    line2.rotate(90);

    window.draw(line1);
    window.draw(line2);

    line1.setSize(sf::Vector2f(2000, 1));
    line2.setSize(sf::Vector2f(1000, 1));

    line1.setFillColor(sf::Color(36, 36, 36));
    line2.setFillColor(sf::Color(36, 36, 36));
    sf::RectangleShape line3(sf::Vector2f(10, 2));
    for (int y = 0; y < 1000; y += 50)
    {
        line3.setPosition(1000 - 6, y);
        line1.setPosition(0, y);
        window.draw(line3);
        if (y / 50 - 10 != 0) {
            text.setString(std::to_string(y / 50 - 10));
            text.setPosition(1005, y - 4);
            window.draw(line1);
            window.draw(text);
        }

    }
    line3.rotate(90);
    for (int x = 0; x < 2000; x += 50)
    {
        line3.setPosition(x, 500 - 4);
        line2.setPosition(x, 0);
        window.draw(line3);
        if (x / 50 - 20 != 0) {
            text.setString(std::to_string(x / 50 - 20));
            text.setPosition(x - 6, 505);
            window.draw(line2);
            window.draw(text);
        }

    }

}
int right_engle(std::vector<std::pair<float, float>> figure)
{
    if (figure.size() == 4) {
        if (length(figure[0], figure[1]) == length(figure[2], figure[3]) && length(figure[1], figure[2]) == length(figure[3], figure[0]))
        {
            if (pow(length(figure[0], figure[1]), 2) + pow(length(figure[1], figure[2]), 2) == pow(length(figure[0], figure[2]), 2))
            {
                std::cout << "right.\n";
                return 0;
            }
        }
    }
    std::cout << "not right.\n";
    return 1;
}

int isosceles_triangle(std::vector<std::pair<float, float>> figure) {
    if (figure.size() == 3) {
        double f = length(figure[0], figure[1]);
        double s = length(figure[1], figure[2]);
        double t = length(figure[2], figure[0]);

        if (f == s || f == t || s == t) {
            std::cout << "isosceles.\n";
            return 0;
        }
    }
    std::cout << "not isosceles.\n";
    return 1;
}

int regular(std::vector<std::pair<float, float>> figure)
{
    double len = length(figure[0], figure[1]);
    for (int i = 0; i < figure.size(); i++)
    {
        if (i < figure.size() - 1) {
            if (length(figure[i], figure[i + 1]) != len)
            {
                std::cout << "not regular figure.\n";
                return 1;
            }
        }
        else {
            if (length(figure[i], figure[0]) != len)
            {
                std::cout << "not regular figure.\n";
                return 1;
            }
        }
    }
    std::cout << "regular figure.\n";
    return 0;
}
int main()
{


    List<std::vector<std::pair<float, float>>> figure;
    List<std::vector<float>> ell;
    std::vector<std::pair<float, float>> fig_buf;
    std::vector<float> ell_buf;
    sf::Font font;
    sf::Text text;
    if (!font.loadFromFile("font/OpenSans-Bold.ttf"))
    {
        window.display();
    }

        text.setFont(font);
        text.setCharacterSize(20);
        text.setString("geometrick figures");
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);

        sf::CircleShape tr(100, 3);

        tr.setFillColor(sf::Color::White);

        tr.setPosition(1000, 500);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::EventType::Closed:
                    window.close();
                    break;

                }


            }

            std::cout << "\n1.add figure\n"
                << "2.add ellipse\n"
                << "3.right_engle\n"
                << "4.regular\n"
                << "5.isosceles_triangle\n";
            window.clear();

            window.draw(text);
            float N, X, Y, R1, R2;
            int ans;
            std::cin >> ans;
            switch (ans) {
            case 1:
                std::cout << "N = ";
                std::cin >> N;
                for (int i = 0; i < N; i++)
                {
                    std::cout << i << "X Y:";
                    std::cin >> X;
                    std::cin >> Y;
                    fig_buf.push_back(std::make_pair(X, Y));
                    figure.push_back(fig_buf);
                }
                create_figure(figure[figure.size() - 1]);
                break;
            case 2:
                std::cout << "Radius1 = ";
                std::cin >> R1;
                std::cout << "Radius2 = ";
                std::cin >> R2;
                std::cout << " X Y:";
                std::cin >> X;
                std::cin >> Y;
                ell_buf.push_back(R1);
                ell_buf.push_back(R2);
                ell_buf.push_back(X);
                ell_buf.push_back(Y);
                ell.push_back(ell_buf);

                ellipse_(ell[ell.size() - 1]);
                break;
            case 3:
                if (figure.size() != 0)
                    right_engle(figure[figure.size() - 1]);
                break;
            case 4:
                if (figure.size() != 0)
                    regular(figure[figure.size() - 1]);
                break;
            case 5:
                if (figure.size() != 0)
                    isosceles_triangle(figure[figure.size() - 1]);
                break;

            }

            net();
            window.display();
        }

        return 0;
    }
