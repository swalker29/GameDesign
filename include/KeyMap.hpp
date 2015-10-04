#ifndef KEYMAP_HPP
#define KEYMAP_HPP
#include <stdlib.h>
#include <string.h>

class KeyMap::KeyMap(){
    private:
        std::map<char[], int> map;

    public:
        int getKeyValue(char[] input);
        KeyMap();
        void createMap();
}


#endif
