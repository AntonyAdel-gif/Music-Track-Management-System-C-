// Antony Adel 20246023
// Philopateer Bassem 20245042

#ifndef SONG_H
#define SONG_H
#include <string>
using namespace std;

struct song{
    string title;
    double duration;

    bool operator==(const song &other) {
        return title == other.title && duration == other.duration;
        //return title == other.title;     //if we want to only find the common name regardless the duration
    }
};

#endif //SONG_H
