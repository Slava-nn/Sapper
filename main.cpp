#include "field.h"

int main()
{
    std::cout << "Welcome to the game!\n\n";

    uint16_t rows, cols, bombsNumber;
    std::cout << "Let's setup your game field\n";

    while (true)
    {
        std::cout << "Enter the number of rows: ";
        std::cin >> rows;

        std::cout << "Enter the number of columns: ";
        std::cin >> cols;

        std::cout << "Enter the number of bombs: ";
        std::cin >> bombsNumber;

        if (bombsNumber < rows * cols)
        {
            break;
        }
        else
        {
            std::cout << "\nInvalid number of bombs for the field of such size, please try again!\n\n";
        }
    }

    Field* field = new Field(rows, cols, bombsNumber);

    field->play();

    delete field;
    return 0;
}