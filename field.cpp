#include <random>
#include "field.h"

Field::Field(uint16_t rows, uint16_t cols, uint16_t bombsNumber) :
    m_rows(rows), m_cols(cols), m_bombsNumber(bombsNumber)
{
    for (size_t i = 0; i < m_rows; ++i)
        m_matrix.emplace_back(std::vector<Cell>());

    for (auto &row : m_matrix)
    {
        for (size_t i = 0; i < m_cols; ++i)
            row.emplace_back(Cell());
    }

    place_bombs();
    setCellValues();
}

void Field::setBomb(uint16_t row, uint16_t col)
{
    m_matrix[row][col].m_isBomb = true;
}

void Field::openCell(uint16_t row, uint16_t col)
{
    m_matrix[row][col].m_isOpened = true;
}

void Field::incrementCellValue(uint16_t row, uint16_t col)
{
    m_matrix[row][col].m_value += 1;
}

bool Field::isBomb(uint16_t row, uint16_t col) const
{
    return m_matrix[row][col].m_isBomb;
}

bool Field::isOpened(uint16_t row, uint16_t col) const
{
    return m_matrix[row][col].m_isOpened;
}

uint16_t Field::getCellValue(uint16_t row, uint16_t col) const
{
    return m_matrix[row][col].m_value;
}

void Field::place_bombs()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<uint16_t> uniRows(0, m_rows - 1);
    std::uniform_int_distribution<uint16_t> uniCols(0, m_cols - 1);

    for (uint16_t i = 0; i < m_bombsNumber; ++i)
    {
        while (true)
        {
            uint16_t row = uniRows(rng);
            uint16_t col = uniCols(rng);

            if (!isBomb(row, col))
            {
                setBomb(row, col);
                break;
            }
        }
    }   
}

void Field::setCellValues()
{
    for (uint16_t row = 0; row < m_rows; ++row)
    {
        for (uint16_t col = 0; col < m_cols; ++col)
        {
            for (int i = row - 1; i <= row + 1; ++i)
            {
                if (i < 0 || i >= m_rows)
                    continue;

                for (int j = col - 1; j <= col + 1; ++j)
                {
                    if (j < 0 || j >= m_cols)
                        continue;

                    if (isBomb(i, j))
                        incrementCellValue(row, col);
                }
            }
        }
    }
}

void Field::play()
{
    std::cout << "The game begins!\n\n";
    uint16_t movesMade = 0;

    while(true)
    {
        showCurrentField();
        uint16_t row = 0, col = 0;
        std::cout << "Choose the cell to be opened.\nFor this, enter its row and column numbers: ";
        while (true)
        {
            std::cin >> row >> col;
            if ((row > 0) && (row <= m_rows) && (col > 0) && (col <= m_cols))
                break;

            std::cout << "Incorrect input, please try again: ";
        }
        
        row -= 1;
        col -= 1;
        if (isBomb(row, col))
        {
            std::cout << "You've lost! That was the real field:\n";
            showRealField();
            std::cout << "\nDon't get upset, next time you'll become a better sapper!\n\n";
            break;
        }
        else
        {
            movesMade += 1;
            if (movesMade == m_rows * m_cols - m_bombsNumber)
            {
                showRealField();
                std::cout << "\nCongratulations, you've just won the game! You are a perfect sapper!\n\n";
                break;
            }

            openCell(row, col);
        }
    }
}

void Field::showCurrentField() const
{
    for (uint16_t row = 0; row < m_rows; ++row)
    {
        for (uint16_t col = 0; col < m_cols; ++col)
        {
            if (isOpened(row, col))
                std::cout << getCellValue(row, col) << " ";
            else
                std::cout << "*" << " ";
        }

        std::cout << std::endl;
    }
}

void Field::showRealField() const
{
    for (uint16_t row = 0; row < m_rows; ++row)
    {
        for (uint16_t col = 0; col < m_cols; ++col)
        {
            if (isBomb(row, col))
                std::cout << "b" << " ";
            else
                std::cout << getCellValue(row, col) << " ";
        }

        std::cout << std::endl;
    }
}