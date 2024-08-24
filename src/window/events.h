#ifndef WINDOW_EVENTS_H_
#define WINDOW_EVENTS_H_
#include "window.h"

typedef unsigned int uint;

class Events {
public:
    static bool* _keys;  // массив клавиш клавиатуры и кнопок мыши
    static uint* _frames;  // массив с изменениями состояния клавиш и кнопок мыши
    static uint _current;  // текущее изменение состояния клавиш и кнопок мыши

//  расстояние на которое сдвинулся курсор мыши
    static float deltaX; 
    static float deltaY;

//  координаты курсора мыши
    static float x;
    static float y;

//  заблокирован ли курсор
    static bool _cursor_locked;
    static bool _cursor_started;

    static int initialize();  // метод инициализации
    static void pullEvents();  // метод получения событий

    static bool isPressed(int keycode);  // нажата ли клавиша
    static bool justPressed(int keycode);  // нажата ли клавиша только что

    static bool isclicked(int button);  // нажата ли кнопка мыши
    static bool justclicked(int button);  // нажата ли кнопка мыши только что

    static void toogleCursor();  // захват курсора
};

#endif