#include <iostream>
#include <vector>
#include <conio.h>
#include <string>

#define sizeArray 9
#define icon_player '0'
#define icon_tower '@'

using namespace std;

class gameField
{
    private:

        vector<vector<char>> field;

    public:


        void setField(vector<vector<char>> field)
        {
            this->field = field;
        }

        vector<vector<char>> getField()
        {
            return field;
        }

        void output()
        {
            for (size_t i = 0; i < sizeArray; i++)
            {
                for (size_t j = 0; j < sizeArray; j++)
                {
                    cout << field[i][j] << "\t";
                }
                cout << "\n";
            }
        }
};

class player {
    public:
        int x, y;
        char icon;

        void setX(int x)
        {
            this->x = x;
        }

        int getX()
        {
            return x;
        }

        void setY(int y)
        {
            this->y = y;
        }

        int getY()
        {
            return y;
        }

        player() {
            x = 1;
            y = 1;
            icon = icon_player;
        }
};

class tower {
    private:
        int x;
        int y;
        int range;
        char icon;

    public:

        void setX(int x)
        {
            this->x = x;
        }

        int getX()
        {
            return x;
        }

        void setY(int y)
        {
            this->y = y;
        }

        int getY()
        {
            return y;
        }

        void setRange(int range)
        {
            this->range = range;
        }

        int getRange()
        {
            return range;
        }

        char getIcon() {
            return icon;
        }

        tower() {
            icon = icon_tower;
            x = 4;
            y = 4;
            range = 1;
        }

};

void run();
void creationField(gameField &gField, player &gamer, tower &dire);

int main(){

    run();

}

void towerVision(gameField &gField, player &gamer, tower &dire) {
    for (int i = -dire.getRange(); i <= dire.getRange(); i++) {
        for (int j = -dire.getRange(); j <= dire.getRange(); j++) {
            if (gField.getField()[dire.getY() + j][dire.getX() + i] == gamer.icon) {
                cout << "Gotcha!" << endl;
            }
        }
    }
}

void creationField(gameField &gField, player &gamer, tower &dire)
{
    vector<vector<char>> FieldArr(sizeArray, vector<char>(sizeArray));

    for (size_t i = 0; i < sizeArray; i++)
    {
        for (size_t j = 0; j < sizeArray; j++)
        {
            if (i == 0 or i == sizeArray - 1 or j == 0 or j == sizeArray - 1)
            {
                FieldArr[i][j] = '#';
            }
            else
            {
                FieldArr[i][j] = ' ';
            }
        }
    }

    FieldArr[gamer.y][gamer.x] = gamer.icon;

    FieldArr[dire.getY()][dire.getX()] = dire.getIcon();

    gField.setField(FieldArr);
}

void movement(gameField &gField, player &gamer, char key)
{
    switch (key)
    {
    case 'w':
        if (gField.getField()[gamer.getY()-1][gamer.getX()] != '#')
        {
            gamer.setY(gamer.getY()-1);
        }
        break;

    case 's':
        if (gField.getField()[gamer.getY()+1][gamer.getX()] != '#')
        {
            gamer.setY(gamer.getY()+1);
        }
        break;

    case 'a':
        if (gField.getField()[gamer.getY()][gamer.getX()-1] != '#')
        {
            gamer.setX(gamer.getX()-1);
        }
        break;

    case 'd':
        if (gField.getField()[gamer.getY()][gamer.getX()+1] != '#')
        {
            gamer.setX(gamer.getX()+1);
        }
        break;
    
    default:
        break;
    }
    
}


void run() {
    bool start = true;

    gameField FieldArr;
    player gamer;
    tower dire;

    while (start) {
        system("cls");

        creationField(FieldArr, gamer, dire);
        FieldArr.output();

        towerVision(FieldArr, gamer, dire);

        if (_kbhit)
        {
            char key = _getch();

            if (key == 'q')
            {
                start = false;
            } 
            else
            {
                movement(FieldArr, gamer, key);
            }
        }

    }
}