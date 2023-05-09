

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

public:
    Pixel(unsigned char r, unsigned char green, unsigned char blue);
};

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) {
    red = r;
    green = g;
    blue = b;
}

