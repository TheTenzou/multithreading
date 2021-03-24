import java.util.Random;
import java.util.concurrent.ExecutionException;

public class Main {
    public static void main(String[] args) throws ExecutionException, InterruptedException {
        int column = 10;
        int row = 100;

        Matrix matrix = new Matrix(column, row);

        Random random = new Random();

        for (int i = 0; i < column; i++ ) {
            for (int j = 0; j < row; j++ ) {
                matrix.setElement(i,j, random.nextInt(100));
            }
        }

        MaxInMatrix maxInMatrix = new MaxInMatrix(5);
        System.out.println(maxInMatrix.findMax(matrix));

    }
}
