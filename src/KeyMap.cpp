#include <KeyMap.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
KeyMap::KeyMap(){

}

void KeyMap::createMap(){
    //maps input string to relevant int to be used in SFML enum
    map = { {"a", 0}, {"b", 1}, {"c", 2}, {"d", 3}, {"e", 4}, {"f", 5}, {"g", 6}, {"h", 7}, {"i", 8}, {"j", 9}, {"k", 10},
            {"l", 11}, {"m", 12}, {"n", 13}, {"o", 14}, {"p", 15}, {"q", 16}, {"r", 17}, {"s", 18}, {"t", 19}, {"u", 20}, 
            {"v", 21}, {"w", 22}, {"x", 23}, {"y", 24}, {"z", 25},
            {"0", 26}, {"1", 27}, {"2", 28}, {"3", 29}, {"4", 30}, {"5", 31}, {"6", 32},
            {"7", 33}, {"8", 34}, {"9", 35}, {"escape", 36}, {"lcontrol", 37}, {"lshift", 38}, 
            {"lalt", 39}, {"rcontrol", 41}, {"rshift", 42}, {"ralt", 43}, {"left", 71}, 
            {"right", 72}, {"up", 73}, {"down", 74}, {"numpad1", 75}, {"numpad2", 76},
            {"numpad3", 77}, {"numpad4", 78}, {"numpad5", 79}, {"numpad6", 80},
            {"numpad7", 81}, {"numpad8", 82}, {"numpad9", 83}, {"tab", 60}, {"space", 57},
            {"joystick1", 1}, {"joystick2", 2}, {"joystick3", 3}, {"joystick4", 4}, 
            {"joystick5", 5}, {"joystick6", 6}, {"joystick7", 7}, {"joystick8", 8}, 
            {"joystick9", 9}, {"joystick10", 10}, {"joystick11", 11}, {"joystick12", 12}, 
            {"joystick13", 13}, {"joystick14", 14}, {"joystick15", 15}, {"joystick16", 16}, 
            {"joystick17", 17}, {"joystick18", 18}, {"joystick19", 19}, {"joystick20", 20}, 
            {"joystick21", 21}, {"joystick22", 22}, {"joystick23", 23}, {"joystick24", 24},
            {"joystick25", 25}, {"joystick26", 26}, {"joystick27", 27}, {"joystick28", 28}, 
            {"joystick29", 29}, {"joystick30", 30}, {"joystick31", 31}, {"joystick32", 32}, 
            {",", 49}, {".", 50}  };

}

int KeyMap::getKeyValue(std::string input){
    int kValue = map[input];
    return map[input];
}


