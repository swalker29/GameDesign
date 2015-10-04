#include <KeyMap.hpp>

class KeyMap::KeyMap(){
    private:
        std::map<char[], int> map;

    public:
        int getKeyValue(char[] input);
        KeyMap();
        void createMap();
}

KeyMap::KeyMap(){

}

void KeyMap::createMap(){
    //maps input char[] to relevant int to be used in SFML enum
    map = { {'0', 26}, {'1', 27}, {'2', 28}, {'3', 29}, {'4', 30}, {'5', 31}, {'6', 32},
            {'7', 33}, {'8', 34}, {'9', 35}, {"escape", 36}, {"lcontrol", 37}, {"lshift", 38}, 
            {"lalt", 39}, {"rcontrol", 41}, {"rshift", 42}, {"ralt", 43}, {"left", 71}, 
            {"right", 72}, {"up", 73}, {"down", 74}, {"numpad1", 75}, {"numpad2", 76},
            {"numpad3", 77}, {"numpad4", 78}, {"numpad5", 79}, {"numpad6", 80},
            {"numpad7", 81}, {"numpad8", 82}, {"numpad9", 83}, {"tab", 60}, {"space", 57)} };

}

int getKeyValue(char[] input){
    return map[input];
}


