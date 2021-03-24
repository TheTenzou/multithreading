import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Matrix {
    private final List<List<Integer>> matrix;

    public Matrix(int row, int column) {
        matrix = new ArrayList<>(row);

        for (int i = 0; i < row; i++) {
            List<Integer> newRow = new ArrayList<>(column);
            for (int j = 0; j < column; j++) {
                newRow.add(0);
            }
            matrix.add(newRow);
        }

    }

    public void setElement(int i, int j, Integer element) {
        matrix.get(i).set(j, element);
    }

    public Integer getElement(int i, int j) {
        return matrix.get(i).get(j);
    }

    public List<Integer> getRow(int index) {
        return matrix.get(index);
    }

    public int getRowCount() {
        return matrix.size();
    }
}
