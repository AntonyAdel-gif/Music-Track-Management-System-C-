

#ifndef MUSICTRACK_H
#define MUSICTRACK_H
#include <iostream>
#include "song.h"
using namespace std;



class MusicTrack {
    private:
          song *playlist;
          int playlist_size;
          int playlist_capacity;
          static int playlistCount;
          static song longsong;
          string name;
    public:
        MusicTrack(); //default constractor
        MusicTrack(const MusicTrack &);  //copy constractor

        void setname(const string &NAME) {    //setting the playlist name
            this->name = NAME;                //using inline declaration
        }

        string getname() {
            return this->name;
        }


        int getplaylistsize() {
            return this->playlist_size;
        }


        void AddNewSong (const song &);


        static int totalPlaylistsCreated() {
            return playlistCount;
        }


        static string longestSong() {
            return longsong.title;
        }


        friend bool operator>=(const MusicTrack &, const MusicTrack &);


        song operator[](const int &index) const {
            return playlist[index];
        }


        //MusicTrack operator=(const MusicTrack &);  //for assigning object when adding
        MusicTrack operator+(const MusicTrack &) const;


        MusicTrack operator-(const MusicTrack &) const;


        MusicTrack operator--(int);


        friend ostream & operator<<(ostream &COUT, const MusicTrack &);


        ~MusicTrack();                                      //destractor

};

#endif MUSICTRACK_H
