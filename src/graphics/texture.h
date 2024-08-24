#ifndef GRAPHICS_TEXTURE_H_
#define GRAPHICS_TEXTURE_H_

#include <string>

class Texture {
public:
//  размеры текстуры
    int width;
    int height;

    unsigned int id;  // id обЪекта текстур
    Texture(unsigned int id, int width, int height);  // создание текстуры
    ~Texture();  // удаление текстуры

    void bind();  // привязка текстуры
};

extern Texture* load_texture(std::string filename);  // загрузка текстур


#endif