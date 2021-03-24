public class Main {

    public static void main(String[] args) {
        Matrix matrix = new Matrix(10, 100);

        MyThread[] myThreads = new MyThread[10];

        for (int i = 0; i < myThreads.length; i++) {
            myThreads[i] = new MyThread(matrix.getRow(i), i);
        }

        for (MyThread myThread : myThreads) {
            try {
                myThread.getThread().join();
                System.out.println(myThread.getMaxInt());
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
