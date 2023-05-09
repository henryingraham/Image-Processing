

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

public:
    Header(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength, char colorMapDepth, short xOrigin, short yOrigin, short width, short height, char  bitsPerPixel, char  imageDescriptor);
};

Header::Header(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength,
               char colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel,
               char imageDescriptor) {
    this->idLength = idLength;
    this->colorMapType = colorMapType;
    this->dataTypeCode = dataTypeCode;
    this->colorMapOrigin = colorMapOrigin;
    this->colorMapLength = colorMapLength;
    this->colorMapDepth = colorMapDepth;
    this->xOrigin = xOrigin;
    this->yOrigin = yOrigin;
    this->width = width;
    this->height = height;
    this->bitsPerPixel = bitsPerPixel;
    this->imageDescriptor = imageDescriptor;
}

