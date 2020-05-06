import numpy as np

MAGIC = 9

class Sudoku:

    def __init__(self):
        self._init_values = np.zeros((MAGIC, MAGIC), dtype=np.int8)
        self._values = np.zeros((MAGIC, MAGIC), dtype=np.int8)
        self._complete = np.arange(1, 10, dtype=np.int8)


    def set_element(self, row, column, value):
        self._set_element(row, column, value)


    def _set_element(self, row, column, value, init = False):
        self._check_index(row, column)
        if value < 0 or value > MAGIC:
            raise NameError('InvalidValue')
        if init:
            self._init_values[row, column] = value
        elif self._init_values[row - 1, column - 1] != 0:
            raise NameError('CannotSetThisPlace')
        self._values[row, column] = value


    def get_element(self, row, column):
        self._check_index(row, column)
        return self._values[row, column]

   
    def is_init(self, row, column):
        self._check_index(row, column)
        return self._init_values[row, column] != 0


    def _check_index(self, row, column):
        if row < 0 or row > 8:
            raise NameError('InvalidRowNumber')
        if column < 0 or column > 8:
            raise NameError('InvalidColumnNumber')


    def print(self):
        for i in range(MAGIC):
            row = self._values[i]
            print(' '.join(map(str, row)))


    def validate(self):
        return self._loop_sudoku(self._is_row_invalid)


    def complete(self):
        return self._loop_sudoku(self._is_row_incomplete)


    def _loop_sudoku(self, predicate):
        for i in range(MAGIC):
            if predicate(self._values[i]):
                return False
        for i in range(MAGIC):
            if predicate(self._values[:, i]):
                return False
        for i in range(MAGIC):
            row_index = int((i / 3))  * 3
            col_index = (i % 3) * 3
            row = self._values[
                row_index : (row_index + 3), 
                col_index : (col_index + 3)
            ].reshape(MAGIC)
            if predicate(row):
                return False
        return True


    def _is_row_incomplete(self, row):
        row = np.sort(row)
        return not np.array_equal(self._complete, row)


    def _is_row_invalid(self, row):
        for i in range(MAGIC):
            value = row[i]
            if value == 0:
                continue
            for j in range(i + 1, MAGIC):
                if value == row[j]:
                    return True
        return False


def read(relative_path):
    f = open(relative_path, "r")
    index = 0
    sudoku = Sudoku()
    for line in f:
        values = line.split(' ')
        for value in values:
            sudoku._set_element(int(index / MAGIC), index % MAGIC, int(value), True)
            index = index + 1
    f.close()
    return sudoku


if __name__ == '__main__':
    sudoku = read('../data/easy-1.txt')
    sudoku.print()
    print(sudoku.validate())
    print(sudoku.complete())
    sudoku = read('../data/complete.txt')
    sudoku.print()
    print(sudoku.validate())
    print(sudoku.complete())