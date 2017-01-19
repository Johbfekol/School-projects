
public class isort {
	private int[] numbers;
	
	public void sort(int[] values) {
        if (values ==null || values.length==0){
        	return;
        }
        this.numbers = values;
        insertionSort(numbers);
	}

	private void insertionSort(int[] arr) {
		for (int i = 1; i < arr.length; i++) {
			int valueToSort = arr[i];
			int j = i;
			while (j > 0 && arr[j - 1] > valueToSort) {
				arr[j] = arr[j - 1];
				j--;
			}
			arr[j] = valueToSort;
		}
	}
}
