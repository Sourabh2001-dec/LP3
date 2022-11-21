
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

class MergeSort {

    private static final int MAX_THREADS = 4;

    private static class SortThreads extends Thread {
        SortThreads(Integer[] array, int begin, int end) {
            super(() -> {
                MergeSort.mergeSort(array, begin, end);
            });
            this.start();
        }
    }

    public static void threadedSort(Integer[] array) {

        long time = System.currentTimeMillis();
        final int length = array.length;

        boolean exact = length % MAX_THREADS == 0;
        int maxlim = exact ? length / MAX_THREADS : length / (MAX_THREADS - 1);

        maxlim = maxlim < MAX_THREADS ? MAX_THREADS : maxlim;

        final ArrayList<SortThreads> threads = new ArrayList<>();

        for (int i = 0; i < length; i += maxlim) {
            int beg = i;
            int remain = (length) - i;
            int end = remain < maxlim ? i + (remain - 1) : i + (maxlim - 1);
            final SortThreads t = new SortThreads(array, beg, end);

            threads.add(t);
        }
        for (Thread t : threads) {
            try {

                t.join();
            } catch (InterruptedException ignored) {
            }
        }

        /*
         * The merge takes 2 parts at a time and merges them into 1,
         * then again merges the resultant into next part and so on...until end
         */
        for (int i = 0; i < length; i += maxlim) {
            int mid = i == 0 ? 0 : i - 1;
            int remain = (length) - i;
            int end = remain < maxlim ? i + (remain - 1) : i + (maxlim - 1);

            merge(array, 0, mid, end);
        }
        time = System.currentTimeMillis() - time;
        System.out.println("Time spent for custom multi-threaded recursive merge_sort(): " + time + "ms");
    }

    public static void mergeSort(Integer[] array, int begin, int end) {
        if (begin < end) {
            int mid = (begin + end) / 2;
            mergeSort(array, begin, mid);
            mergeSort(array, mid + 1, end);
            merge(array, begin, mid, end);
        }
    }

    public static void merge(Integer[] array, int begin, int mid, int end) {
        Integer[] temp = new Integer[(end - begin) + 1];

        int i = begin, j = mid + 1;
        int k = 0;

        while (i <= mid && j <= end) {
            if (array[i] <= array[j]) {
                temp[k] = array[i];
                i += 1;
            } else {
                temp[k] = array[j];
                j += 1;
            }
            k += 1;
        }

        while (i <= mid) {
            temp[k] = array[i];
            i += 1;
            k += 1;
        }

        while (j <= end) {
            temp[k] = array[j];
            j += 1;
            k += 1;
        }

        for (i = begin, k = 0; i <= end; i++, k++) {
            array[i] = temp[k];
        }
    }
}

class App {

    private static Random random = new Random();
    private static final int size = random.nextInt(100);
    private static final Integer list[] = new Integer[size];

    static {
        for (int i = 0; i < size; i++) {

            list[i] = random.nextInt(size + (size - 1)) - (size - 1);
        }
    }

    public static void main(String[] args) {
        System.out.print("Input = [");
        for (Integer each : list)
            System.out.print(each + ", ");
        System.out.print("] \n" + "Input.length = " + list.length + '\n');

        long t;

        Integer[] arr2 = Arrays.copyOf(list, list.length);
        t = System.currentTimeMillis();
        MergeSort.mergeSort(arr2, 0, arr2.length - 1);
        t = System.currentTimeMillis() - t;
        System.out.println("Time spent for custom single threaded recursive merge_sort(): " + t + "ms");

        Integer[] arr = Arrays.copyOf(list, list.length);
        MergeSort.threadedSort(arr);
        System.out.print("Output = [");
        for (Integer each : arr)
            System.out.print(each + ", ");
        System.out.print("]\n");
    }
}
