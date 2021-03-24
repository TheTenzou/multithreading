import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.*;

public class MaxInMatrix {
    private final ExecutorService threadPoolExecutor;

    public MaxInMatrix( int threadCount) {
        this.threadPoolExecutor = Executors.newFixedThreadPool(threadCount);
    }

    public Integer findMax(Matrix matrix) throws ExecutionException, InterruptedException {
        List<Future<Integer>> futures = new ArrayList<>();

        for (int i = 0; i < matrix.getRowCount(); i++) {
            Callable<Integer> maxInRow = new MaxInRow(matrix.getRow(i));
            Future<Integer> future = threadPoolExecutor.submit(maxInRow);
            futures.add(future);
        }

        List<Integer> results = new ArrayList<>();

        for (Future<Integer> future : futures) {
            results.add(future.get());
        }

        threadPoolExecutor.shutdown();

        return Collections.max(results);
    }
}
