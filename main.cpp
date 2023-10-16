#include <SFML/Graphics.hpp>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 600;
const sf::Color BACKGROUND_COLOR(0, 0, 0);
const double CubeSize = 150.0;
const double HalfCubeSize = CubeSize / 2.0;
const double RotationSpeed = 0.0001;
const double K1 = WIDTH / 2;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Rotating Cube");

struct Point {
    double x, y, z;
};

Point vertices[8] = {
        {-HalfCubeSize, -HalfCubeSize, -HalfCubeSize},
        {HalfCubeSize, -HalfCubeSize, -HalfCubeSize},
        {HalfCubeSize, HalfCubeSize, -HalfCubeSize},
        {-HalfCubeSize, HalfCubeSize, -HalfCubeSize},
        {-HalfCubeSize, -HalfCubeSize, HalfCubeSize},
        {HalfCubeSize, -HalfCubeSize, HalfCubeSize},
        {HalfCubeSize, HalfCubeSize, HalfCubeSize},
        {-HalfCubeSize, HalfCubeSize, HalfCubeSize}
};

int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

void rotate(Point& p, double angleX, double angleY) {
    double cosX = std::cos(angleX);
    double sinX = std::sin(angleX);
    double cosY = std::cos(angleY);
    double sinY = std::sin(angleY);

    double tempX = p.x;
    p.x = cosY * p.x - sinY * p.z;
    p.z = sinY * tempX + cosY * p.z;

    tempX = p.x;
    p.x = cosX * p.x - sinX * p.y;
    p.y = sinX * tempX + cosX * p.y;
}

void drawCube(sf::RenderWindow& window, const Point vertices[8], const int edges[12][2]) {
    for (int i = 0; i < 12; i++) {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(vertices[edges[i][0]].x + WIDTH / 2, vertices[edges[i][0]].y + HEIGHT / 2), sf::Color::White),
                sf::Vertex(sf::Vector2f(vertices[edges[i][1]].x + WIDTH / 2, vertices[edges[i][1]].y + HEIGHT / 2), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
    }
}

int main() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(BACKGROUND_COLOR);

        for (int i = 0; i < 8; i++) {
            rotate(vertices[i], RotationSpeed, RotationSpeed);
        }

        drawCube(window, vertices, edges);

        window.display();
    }

    return 0;
}
