import java.util.*;

class Main {
    public static void main(String[] argh) {

        Scanner sc = new Scanner(System.in);
        
        // System.out.print("Enter the number of nested array in the array: ");
        // int numberOfNestedArray = sc.nextInt();
        // sc.nextLine(); // to consume the next line character

        // System.out.print("Enter the number of elements in the nested array: ");
        // int numberOfElementsInNestedArray = sc.nextInt();
        // sc.nextLine(); // to consume the next line character    

        // int[][] arr = new int[numberOfNestedArray][numberOfElementsInNestedArray];

        // for (int i = 0; i < numberOfNestedArray; i++) {
        //     for (int j = 0; j < numberOfElementsInNestedArray; j++) {
        //         System.out.print("Enter the element at index " + i + " " + j + ": ");
        //         arr[i][j] = sc.nextInt();
        //         sc.nextLine(); // to consume the next line character
        //     }
        // }

        // System.out.println("The array is : ");
        // for (int i = 0; i < numberOfNestedArray; i++) {
        //     for (int j = 0; j < numberOfElementsInNestedArray; j++) {
        //         System.out.print(arr[i][j] + " ");
        //     }
        //     System.out.println();
        // }

        // create a 2D array
        System.out.print("Enter the number of rows in the array: ");
        int numberOfRows = sc.nextInt();
        sc.nextLine(); // to consume the next line character

        System.out.print("Enter the number of columns in the array: ");
        int numberOfColumns = sc.nextInt();
        sc.nextLine(); // to consume the next line character

        int[][] arr = new int[numberOfRows][numberOfColumns];

        // get elements from the user
        for (int i = 0; i < numberOfRows; i++) {
            System.out.print("Enter the elements of row " + i + " seperated by spaces: ");
            for (int j = 0; j < numberOfColumns; j++) {
                arr[i][j] = sc.nextInt();
            }
            sc.nextLine(); // to consume the next line character
        }

        // print the array
        System.out.println("The array is : ");
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }

        // System.out.print("Enter number of rows: ");
        // int rows = sc.nextInt();

        // System.out.print("Enter number of columns: ");
        // int columns = sc.nextInt();

        // int[][] array = new int[rows][columns];

        // System.out.println("Enter the elements of the array: ");
        // for ( int i = 0; i < rows; i++) {
        //     for (int j = 0; j < columns; j++) {
        //         System.out.print("Enter element at position [" + i + "][" + j + "]: ");
        //         array[i][j] = sc.nextInt();
        //     }
        // }
        // System.out.println("Updated 2D Arrray: ");
        // for (int i = 0; i < rows; i++) {
        //     for (int j = 0; j < columns; j++) {
        //         System.out.print(array[i][j] + "\t");
        //     }
        //     System.out.println();
        // }

    }
}
