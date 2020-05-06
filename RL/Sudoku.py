import numpy as np

class Sudoku:

    def __init__(self):
        self._values = np.zeros((9, 9), dtype=np.int8)
    

    def set_element(self, row, column, value):
        self._check_index(row, column)
        if value < 1 or value > 9:
            raise NameError('InvalidValue')
        self._values[row - 1, column - 1] = value


    def get_element(self, row, column):
        self._check_index(row, column)
        return self._values[row, column]


    def _check_index(self, row, column):
        if row < 1 or row > 9:
            raise NameError('InvalidRowNumber')
        if column < 1 or column > 9:
            raise NameError('InvalidColumnNumber')


    def print(self):
        for i in range(9):
            row = self._values[i]
            print(' '.join(map(str, row)))


    def validate(self):
        for i in range(9):
            if self._is_row_invalid(self._values[i]):
                return False
        for i in range(9):
            if self._is_row_invalid(self._values[:, i]):
                return False
        for i in range(9):
            row_index = int((i / 3) * 3)
            col_index = (i % 3) * 3
            row = self._values[
                row_index: (row_index + 3), 
                col_index: (col_index + 3)
            ].reshape(9)
            if self._is_row_invalid(row):
                return False
        return True


    def _is_row_invalid(self, row):
        for i in range(9):
            value = row[i]
            if value == 0:
                continue
            for j in range(i + 1, 9):
                if value == row[j]:
                    return True
        return False

