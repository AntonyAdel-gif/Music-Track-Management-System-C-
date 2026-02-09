// Antony Adel 20246023
// Philopateer Bassem 20245042
#include<iostream>
#include"MusicTrack.h"
#include"song.h"
using namespace std;

int MusicTrack::playlistCount = 0;                      //static member variable initialization
song MusicTrack::longsong{"null",0};    //static member variable initialization
                                                        // we have use{} because there is no default constructor for song struct


MusicTrack::MusicTrack(){
    playlist_size = 0;
    playlist_capacity = 10;
    playlist = new song[playlist_capacity];
    playlistCount ++;
}



MusicTrack::MusicTrack(const MusicTrack &track) {
    playlist_size = track.playlist_size;
    playlist_capacity = track.playlist_capacity;
    playlist = new song[playlist_capacity];
    for (int i = 0; i < playlist_size; i++) {
        playlist[i] = track.playlist[i];
    }
    name = track.name;
}



void MusicTrack::AddNewSong (const song &newSong) {
    if (playlist_size == playlist_capacity) {
        int new_capacity = playlist_capacity * 2;
        song *temp_playlist = new song[new_capacity];
        for (int i = 0; i < playlist_size; i++) {
            temp_playlist[i] = playlist[i];
        }
        delete [] playlist;
        playlist = temp_playlist;
        playlist_capacity = new_capacity;

    }
    playlist[playlist_size] = newSong;
    playlist_size++;
    if (newSong.duration > longsong.duration) {
        longsong = newSong;
    }
}



/*song& MusicTrack::operator[](int index) {             //have initialized the operator inline
                                                        // and make the validation in the main function
    if (index < 0 || index >= this->playlist_size) {
        cout << "Error: Song index " << index << " is out of bounds." << endl;
        return this->playlist[0];
    }
    return this->playlist[index];
}*/



MusicTrack MusicTrack::operator+(const MusicTrack &instance2) const {  //this function find the common name and duration
    MusicTrack instance3;
    if (*this >= instance2) {  //comparing two objects by the >= overloaded operator
        for (int i = 0; i < this->playlist_size; i++) {
            for (int j = 0; j < instance2.playlist_size; j++) {
                if (this->playlist[i] == instance2.playlist[j]) {
                    instance3.AddNewSong(this->playlist[i]);
                    break;
                }
            }
        }
    }
    else {
        for (int i = 0; i < instance2.playlist_size; i++) {
            for (int j = 0; j < this->playlist_size; j++) {
                if (instance2.playlist[j] == this->playlist[i]) {
                    instance3.AddNewSong(this->playlist[i]);
                    break;
                }
            }
        }
    }
    return instance3;
}




/*MusicTrack MusicTrack::operator=(const MusicTrack &other) {
    if (this == &other) {
        return *this;
    }
}*/




MusicTrack MusicTrack::operator-(const MusicTrack &instance2) const {
    MusicTrack instance3;
        for (int i = 0; i < this->playlist_size; i++) {
            bool flag = false;
            for (int j = 0; j < instance2.playlist_size; j++) {
                if (instance2.playlist[j] == this->playlist[i]) {
                    flag = true;
                    break;
                }
            }
            if (flag == false) {
                instance3.AddNewSong(this->playlist[i]);
            }
        }
    return instance3;
}




MusicTrack MusicTrack :: operator--(int) {
    MusicTrack instance (*this);
    this -> playlist_size--;
    return instance;
}




MusicTrack::~MusicTrack() {
    delete[] playlist;
    playlist = nullptr;
    playlist_size = 0;      //no need to this as it is not static variable just for being safe
}