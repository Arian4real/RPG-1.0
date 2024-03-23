#include <iostream>

using namespace std;

void displayHealthBar() {
    const int barWidth = 20;
    cout << "HP: ";
    int pos = barWidth * current_hp / max_hp;
    for (int i = 0; i < barWidth; i++) {
        if (i < pos) {
            cout << "|";
        } else if (i == pos) {
            cout << "|";
        } else {
            cout << " ";
        }
    }
    cout << " " << current_hp << "/" << max_hp << "\n";
}

int main()
{
    displayHealthBar();
}