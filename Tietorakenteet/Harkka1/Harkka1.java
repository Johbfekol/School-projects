import java.util.Arrays;
import java.util.Calendar;
import java.util.Random;


public class Harkka1 {

	public static void main(String[] args) {
		int A[] = new int[1000000];
		populateArray(A);
		//System.out.println("Before Sorting: ");   	// Testauksessa tarvittava taulukon tulostus
		//printArray(A);				// ennen järjestämistä
		Calendar aika1 = Calendar.getInstance();
		long alkuaika = aika1.getTimeInMillis();
		//isort sortattu = new isort();   	// Lisäysjärjestämisellä järjestäminen
		//sortattu.sort(A);               	// Kommentoinnilla voidaan valita kahdesta menetelmästä
		qsort sortattu = new qsort(); 	// Pikajärjestämisellä järjestetään
		sortattu.sort(A);					// Kommentit pois jos haluaa käyttää
		Calendar aika2 = Calendar.getInstance();
		long loppuaika = aika2.getTimeInMillis();
		long aikaa = loppuaika - alkuaika;
		System.out.println("\nAfter Sorting: ");
		printArray(A);
		System.out.println("\nAikaa kului:" );
		System.out.println(aikaa);
	}

	public static void printArray(int[] B) {
		System.out.println(Arrays.toString(B));
	}

	public static void populateArray(int[] B) {
		Random randomi = new Random ();
		for (int i = 0; i < B.length; i++) {
			B[i] = randomi.nextInt(300000);
		}
	}
}
