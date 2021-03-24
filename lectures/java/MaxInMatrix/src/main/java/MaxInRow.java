import java.util.Collection;
import java.util.Collections;
import java.util.concurrent.Callable;

public class MaxInRow implements Callable<Integer> {

    private final Collection<Integer> row;
    public MaxInRow(Collection<Integer> row) {
        this.row = row;
    }

    @Override
    public Integer call() throws Exception {
        return Collections.max(row);
    }
}
