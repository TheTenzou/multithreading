public class MyThread implements Runnable{
    private final Thread thread;
    private int[] array;
    private int maxInt;

    public MyThread(int[] array, int num) {
        this.array = array;
        thread = new Thread(this, "thread " + num);
        thread.start();
        System.out.println(thread.getName() + " started");
    }

    @Override
    public void run() {
         maxInt = array[0];

         for (int i = 1; i < array.length; i++) {
             maxInt = Math.max(maxInt, array[i]);
         }
    }

    public int getMaxInt() {
        return maxInt;
    }

    public Thread getThread() {
        return thread;
    }
}
