#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

// A pixel is treated as green-screen when green is clearly stronger than
// both red and blue. Transparent foreground pixels are also replaced.
bool isGreenScreen(const Color& pixel) {
    if (pixel.a == 0) {
        return true;
    }

    return pixel.g > 80 &&
           pixel.g > pixel.r * 1.15f &&
           pixel.g > pixel.b * 1.15f;
}

int main() {
    const string backgroundPath = "images1/backgrounds/winter.png";
    const string foregroundPath = "images1/characters/yoda.png";

    Texture backgroundTexture;
    Texture foregroundTexture;

    if (!backgroundTexture.loadFromFile(backgroundPath) ||
        !foregroundTexture.loadFromFile(foregroundPath)) {
        cerr << "Couldn't load one or more images." << endl;
        return 1;
    }

    const Image backgroundImage = backgroundTexture.copyToImage();
    const Image foregroundImage = foregroundTexture.copyToImage();

    if (backgroundImage.getSize() != foregroundImage.getSize()) {
        cerr << "The background and foreground images must be the same size." << endl;
        return 1;
    }

    Image composite = foregroundImage;
    const Vector2u size = backgroundImage.getSize();

    for (unsigned int y = 0; y < size.y; ++y) {
        for (unsigned int x = 0; x < size.x; ++x) {
            const Color foregroundPixel = foregroundImage.getPixel(x, y);

            if (isGreenScreen(foregroundPixel)) {
                composite.setPixel(x, y, backgroundImage.getPixel(x, y));
            }
        }
    }

    Texture compositeTexture;
    compositeTexture.loadFromImage(composite);
    Sprite compositeSprite(compositeTexture);

    RenderWindow window(
        VideoMode(size.x, size.y),
        "CGT 215 Lab 06 - Simple Image Compositing"
    );

    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::Black);
        window.draw(compositeSprite);
        window.display();
    }

    return 0;
}
