#pragma once
#include <iostream>
#include <vector>

class Field
{
public:
    Field() = delete;
    Field(uint16_t rows, uint16_t cols, uint16_t bombsNumber);

    uint16_t getRowsNumber() const;
    uint16_t getColsNumber() const;
    uint16_t getBombsNumber() const;

    void setBomb(uint16_t row, uint16_t col);
    void openCell(uint16_t row, uint16_t col);
    void incrementCellValue(uint16_t row, uint16_t col);

    bool isBomb(uint16_t row, uint16_t col) const;
    bool isOpened(uint16_t row, uint16_t col) const;
    uint16_t getCellValue(uint16_t row, uint16_t col) const;

    void place_bombs();
    void setCellValues();

    void play();

    void showCurrentField() const;
    void showRealField() const;

private:
    struct Cell
    {
        bool m_isBomb = false;
        bool m_isOpened = false;
        uint16_t m_value = 0;
    };

    const uint16_t m_rows;
    const uint16_t m_cols;
    const uint16_t m_bombsNumber;
    std::vector<std::vector<Cell>> m_matrix;
};