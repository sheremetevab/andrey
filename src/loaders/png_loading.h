#ifndef LOADERS_PNG_LOADING_H_
#define LOADERS_PNG_LOADING_H_
#include <string>

class Texture;

extern Texture* load_texture(std::string filename);  // загрузка текстуры png 


#endif