#ifndef KEYMAP_HPP
#define KEYMAP_HPP
#include <stdlib.h>
#include <string>
#include <map>

class KeyMap {
    private:
        std::map <std::string, int> map;

    public:
        int getKeyValue(std::string input);
        KeyMap();
        void createMap();
};


#endif
