import java.util.Scanner;

class isPrime {
    int range; // Declare range

    // Constructor
    public isPrime(int range) {
        this.range = range;
    }

    // Get prime numbers
    public void getPrimeNumbers() {
        // Loop through the range
        for (int i = 2; i <= range; i++) {
            boolean isPrime = true; // Assume i is prime

            // Check if i is prime
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break; 
                }
            }

            // Print prime numbers
            if (isPrime) {
                System.out.println(i);
            }
        }
    }
}

public class BSIT1B_OJEDA {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        do {
            int range = 0;
            do {
                System.out.print("Enter range: ");

                try {
                    range = sc.nextInt(); // Get range
                    sc.nextLine(); // Consume characters after spaces
                    break;
                } catch (Exception e) {
                    System.out.println("Invalid input! Please try again.");
                    sc.next();
                }
            } while (true);

            isPrime prime = new isPrime(range);
            prime.getPrimeNumbers(); // Display prime numbers

            // Ask user if they want to get prime numbers again
            System.out.println("Do you want to try again?");
            System.out.print("Type 'y' to continue:");
            String choice = sc.nextLine();
            if (choice.equals("y")) {
                continue;
            }
            break;
        } while (true);

        sc.close();
    }
}
