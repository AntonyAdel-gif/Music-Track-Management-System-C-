// Antony Adel 20246023
// Philopateer Bassem 20245042

#include <iostream>
#include "song.h"
#include "MusicTrack.h"
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

//Functions prototype
void displaymenu();
bool validation();
void listing();
int listchoice();
bool min_2_validation();
bool song_validation(MusicTrack &);



//the operator >= friend function of class MusicTrack
bool operator>=(const MusicTrack &instance1, const MusicTrack &instance2) {
    if (instance1.playlist_size >= instance2.playlist_size) {
        return true;
    }
    else {
        return false;
    }
}



//the operator << friend function of class MusicTrack
ostream & operator<<(ostream &COUT, const MusicTrack &track) {
    if (track.playlist_size == 0) {
        COUT << "(YOUR PLAY IS EMPTY)" << endl;    //double validation as we already validate with-
        return COUT;                               //song_validation(MusicTrack &) function
    }
    for (int i = 0; i < track.playlist_size; i++) {
        COUT << (i + 1) << ". " << track.playlist[i].title << " (" << track.playlist[i].duration << " mins)" << endl;
    }
    return COUT;
}




vector<MusicTrack> allplaylists;  // global intilization


int main() {

    int choice, temp_choice, temp_choice2;
    MusicTrack temp_song;



    cout << "\n          Welcome to The Music Tracks and Playlist Management System " << endl;
    cout << "   allows you to create, copy, compare, and manipulate playlists and the songs" << endl;



    do {
        displaymenu();
        cin >> choice;
        while (choice < 1 || choice > 13) {
            cout << "Please make a choice in range of 1 through 13 " << endl;
            cin >> choice;
        }


        switch (choice) {
            case 1: {
                MusicTrack new_playlist;
                string name;
                cout << "Please Enter a name for this new playlist: ";
                cin.ignore();
                getline(cin, name);
                new_playlist.setname(name);
                allplaylists.push_back(new_playlist);
                cout << "Great you have created a playlist called " << new_playlist.getname() << endl;
                break;
            }


            case 2: {
                if (validation()) {
                    break;
                }
                cout << "Please select the playlist you want to add song to" << endl;
                listing();
                temp_choice = listchoice(); // does not work if i use listchoice() directly

                song newsong;
                cout << "Enter your song name: ";
                cin.ignore();
                getline(cin, newsong.title);
                cout << "Please enter your song duration in minutes: ";
                cin >> newsong.duration;
                allplaylists[temp_choice - 1].AddNewSong(newsong);
                cout << "Great your song " << newsong.title<< " Has been add to " << allplaylists[temp_choice - 1].getname() <<" playlist" << endl;
                break;
            }


            case 3: {
                if (validation()) {
                    break;
                }
                cout << "Please select the playlist you want to delete" << endl;
                listing();
                temp_choice = listchoice();
                string temp_name = allplaylists[temp_choice - 1].getname();
                allplaylists.erase(allplaylists.begin() + (temp_choice - 1));
                cout << "Congrats you have removed " << temp_name <<" playlist " << endl;

                break;
            }


            case 4:{
                if (validation()) {
                    break;
                }
                cout << "Please select the playlist you want to copy(duplicate)" << endl;
                listing();
                temp_choice = listchoice();
                string new_name;
                cout << "Enter the name of the new playlist copy" << endl;
                cin.ignore();
                getline(cin, new_name);
                MusicTrack new_copy = allplaylists[temp_choice - 1];
                new_copy.setname(new_name);
                allplaylists.push_back(new_copy);
                cout << "Congrats you have copied your " << allplaylists[temp_choice - 1].getname() << " playlist" << endl;


                break;
            }

            case 5:
                if (validation()) {
                    break;
                }
                cout <<"You Have created " << allplaylists[0].totalPlaylistsCreated() << " playlists until now" << endl;
                listing();
            break;


            case 6:
                if (validation()) {
                    break;
                }
                cout << "The longest song along all the playlist is " << allplaylists[0].longestSong() << endl;
            break;


            case 7:
                if (validation()) {
                    break;
                }
                if (min_2_validation()) {
                    break;
                }

                cout << "please choose your first playlist for comparison" << endl;
                listing();
                temp_choice = listchoice();
                cout << "please choose your second playlist for comparison" << endl;
                listing();
                temp_choice2 = listchoice();
                if (allplaylists[temp_choice - 1] >= allplaylists[temp_choice2]) {
                    cout << allplaylists[temp_choice - 1].getname() << " playlist has more songs or equal to ";
                    cout << allplaylists[temp_choice2 - 1].getname() << " playlist" << endl;
                }
                else {
                    cout << allplaylists[temp_choice2 - 1].getname() << " playlist has more songs than ";
                    cout << allplaylists[temp_choice -1].getname() << " playlist" << endl;
                }
            break;


            case 8: {
                if (validation()) {
                    break;
                }
                cout << "please choose your playlist for Playing a song in it (by index)" << endl;
                listing();
                temp_choice = listchoice();
                if (song_validation(allplaylists[temp_choice - 1])) {
                    break;
                }
                cout << "Great choice!" << endl;
                cout << "Now please choose one song by index from the playlist" << endl;
                bool flag = false;
                while (flag == false) {
                    cout << allplaylists[temp_choice - 1] << endl;
                    cin >> temp_choice2;
                    if (allplaylists[temp_choice - 1].getplaylistsize() < temp_choice2 || temp_choice2 < 0) {
                        flag = false;
                        cout << "Ops your index choice is out of bounds" << endl;
                        cout << "Please choose a valid song index" << endl;
                    }
                    else {
                        flag = true;
                    }
                }


                cout << "Great now you are listening to " << allplaylists[temp_choice - 1][temp_choice2 - 1].title << endl;
                cout << "Note: this song duration is " << allplaylists[temp_choice - 1][temp_choice2 - 1].duration << " mins" << endl;
                cout << endl;
                string temp;  //have used string instead of char to prevent infinite loop
                bool flag2 = false;
                cout << "Press (s) simulate time and go to main menu" << endl;
                cin.ignore();
                while (flag2 == false) {
                    getline(cin, temp);
                    if (temp == "s" || temp == "S") {
                        break;
                        flag2 = true;
                    }
                    else {
                        flag2 = false;
                    }
                }
                break;
            }


            case 9: {
                if (validation()) {
                    break;
                }
                if (min_2_validation()) {
                    break;
                }

                cout << "please choose your first playlist for comparison" << endl;
                listing();
                temp_choice = listchoice();
                cout << "please choose your second playlist for comparison" << endl;
                listing();
                temp_choice2 = listchoice();
                if (temp_choice == temp_choice2) {
                    cout << "you have chosen the same playlist " << "sorry I cant compare a playlist by itself" << endl;
                    break;
                }
                MusicTrack new_compare = allplaylists[temp_choice - 1] + allplaylists[temp_choice2 - 1];
                if (new_compare.getplaylistsize() == 0) {
                    cout << "There is no common songs between this two playlists " << endl;
                    break;
                }
                cout << "the common songs between " << allplaylists[temp_choice - 1].getname() << " and " << allplaylists[temp_choice2 - 1].getname() << endl;
                cout << "Are" << endl;
                cout << new_compare;
            break;
            }


            case 10: {
                if (validation()) {
                    break;
                }
                if (min_2_validation()) {
                    break;
                }

                cout << "please choose your first playlist for comparison" << endl;
                listing();
                temp_choice = listchoice();
                cout << "please choose your second playlist for comparison" << endl;
                listing();
                temp_choice2 = listchoice();
                if (temp_choice == temp_choice2) {
                    cout << "you have chosen the same playlist " << "sorry i cant compare a playlist by itself" << endl;
                    break;
                }
                MusicTrack new_compare = allplaylists[temp_choice - 1] - allplaylists[temp_choice2 - 1];
                if (new_compare.getplaylistsize() == 0) {
                    cout << "There is no unique songs in the first playlist" << endl;
                    break;
                }
                cout << "the unique songs in the first playlist in " << allplaylists[temp_choice - 1].getname() << " and " << allplaylists[temp_choice2 - 1].getname() << endl;
                cout << "Is/Are" << endl;
                cout << new_compare;
            break;
            }


            case 11:
                if (validation()) {
                    break;
                }
                cout << "Please choose your playlist to remove the song from it "<< endl;
                listing();
                temp_choice = listchoice();
                if (song_validation(allplaylists[temp_choice - 1])) {
                    break;
                }
                temp_song = allplaylists[temp_choice - 1];
                allplaylists[temp_choice - 1]--;
                cout << "Congrats you have remove " << endl ;
                cout << temp_song;
                cout <<" song, from " << allplaylists[temp_choice - 1].getname()<< " playlist" << endl;
            break;


            case 12:
                if (validation()) {
                    break;
                }
                cout << "Please choose your playlist to show all the songs "<< endl;
                listing();
                temp_choice = listchoice();
                if (song_validation(allplaylists[temp_choice - 1])) {
                    break;
                }
                cout << "this is all the songs for " << allplaylists[temp_choice - 1].getname() << " playlist" << endl;
                cout << allplaylists[temp_choice - 1]<< endl;
            break;


            case 13:
                exit(0);  //for this reason we have included <cstdlib> library
        }

    } while (choice != 13);

    return 0;
}

void displaymenu(){
    cout << "\n***************************************************\n";
    cout << "1- Create a new playlist \n";
    cout << "2- Add new songs to a playlist \n";
    cout << "3- Remove a playlist \n";
    cout << "4- Copy a playlist \n";
    cout << "5- Display total playlists created \n";
    cout << "6- Show the longest song among all playlists \n";
    cout << "7- Compare two playlists \n";
    cout << "8- Play a song by index \n";
    cout << "9- Display common songs \n";
    cout << "10- Display unique songs \n";
    cout << "11- Remove last song \n";
    cout << "12- Print all songs \n";
    cout << "13- Exit The Program\n";
    cout << "****************************************************\n";
    cout << "ENTER YOUR CHOICE\n";
}



bool validation() {
    if (allplaylists.size() == 0) {
        cout << "Ops you have not created any playlist yet" << endl;
        cout << "choose option (1) and creates yours now!" << endl;
        return true;
    }
    return false;
}



void listing() {
    for (int i = 0; i < allplaylists.size(); i++) {
        cout << i+1 <<"- "<<allplaylists[i].getname() << endl;
    }
}



int listchoice() {
    int temp_choice;
    bool flag = false;
    while (flag == false) {
        cin >> temp_choice;
        if (temp_choice < 1 || temp_choice > allplaylists.size()) {
            cout << "Please enter a valid playlist index" << endl;
            flag = false;
        }
        else {
            flag = true;
        }
    }
    return temp_choice;
}



bool min_2_validation() {
    if (allplaylists.size() == 1) {
        cout << "Ops you have just one playlist, you need to create at least two" << endl;
        cout << "choose option (1) and creates yours now!" << endl;
        return true;
    }
    return false;
}



bool song_validation(MusicTrack &instance) {
    if (instance.getplaylistsize() == 0) {
        cout << "Ops Your playlist does not have any songs" << endl;
        cout << "choose option (2) and creates yours now!" << endl;
        return true;
    }
    return false;

}