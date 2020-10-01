#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

class Song {
    friend std::ostream &operator<<(std::ostream &os, const Song &s);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name, std::string artist, int rating)
        : name{name}, artist{artist}, rating{rating} {}
    std::string get_name() const {
        return name;
    }
    std::string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }

    bool operator<(const Song &rhs) const {
        return this->name < rhs.name;
    }

    bool operator==(const Song &rhs) const {
        return this->name == rhs.name;
    }
};

std::ostream &operator<<(std::ostream &os, const Song &s) {
    os << std::setw(20) << std::left << s.name
        << std::setw(30) << std::left << s.artist
        << std::setw(2) << std::left << s.rating;
    return os;
}

void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song &song) {
    std::cout << "Currently Playing:" << std::endl;
    std::cout << song << std::endl;
}

void display_playlist(const std::list<Song> &playlist, const Song &current_song) {
    for (const Song &song : playlist) {
        std::cout << song << std::endl;
    }
}

// list
std::list<Song> playlist{
        {"God's Plan",        "Drake",                     5},
        {"Never Be The Same", "Camila Cabello",            5},
        {"Pray For Me",       "The Weekend and K. Lamar",  4},
        {"The Middle",        "Zedd, Maren Morris & Grey", 5},
        {"Wait",              "Maroone 5",                 4},
        {"Whatever It Takes", "Imagine Dragons",           3}
};

std::list<Song>::iterator current_song = playlist.begin();

// functions for menu
void first_song() {
    std::cout << "Playing First Song" << std::endl;
    current_song = playlist.begin();
    play_current_song(*current_song);
}

void next_song() {
    std::cout << "Playing Next Song" << std::endl;
    current_song++;
    if (current_song == playlist.end()) {
        std::cout << "Restarting playlist" << std::endl;
        current_song = playlist.begin();
    }
    play_current_song(*current_song);
}

void previous_song() {
    std::cout << "Playing Previous Song" << std::endl;
    if (current_song == playlist.begin()) {
        std::cout << "Wrapping to end of playlist." << std::endl;
        current_song = playlist.end();
    }
    current_song--;
    play_current_song(*current_song);
}

void add_song() {
    std::string name, artist;
    int rating;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Adding and Playing new Song" << std::endl;

    std::cout << "Enter Song Name: ";
    std::cin >> name;

    std::cout << "Enter Artist/Band Name: ";
    std::cin >> artist;

    std::cout << "Enter your Song Rating (1-5): ";
    std::cin >> rating;

    playlist.insert(current_song, Song{name, artist, rating});
    std::cout << std::endl;
    current_song--;
    play_current_song(*current_song);
}

void view_list() {
    std::cout << std::endl;
    display_playlist(playlist, *current_song);
}

int main() {

    char selection{};

    do {
        display_menu();

        std::cin >> selection;
        selection = std::toupper(selection);
        std::cout << std::endl;

        switch (selection) {
            case 'F':
                first_song();
                break;
            case 'N':
                next_song();
                break;
            case 'P':
                previous_song();
                break;
            case 'A':
                add_song();
                break;
            case 'L':
                view_list();
                break;
            case 'Q':
                std::cout << "Godbye! Thanks for listening!!" << std::endl;
                break;
            default:
                std::cout << "Invalid Option" << std::endl;
                break;
        }
    } while (selection != 'Q');

    return 0;
}
