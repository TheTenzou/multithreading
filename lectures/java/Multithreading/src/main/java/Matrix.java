import java.util.Random;

public class Matrix {
    private int[][] matrix;

    public Matrix(int width, int size) {
        matrix = new int[width][size];
        Random random = new Random();

        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                matrix[i][j] = random.nextInt(2000) - 1000;
            }
        }
    }
    public int[] getRow(int index) {
        return matrix[index];
    }
}
