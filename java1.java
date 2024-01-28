import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        String days[] = {
                "Sunday",
                "Monday",
                "Tuesday",
                "Wednesday",
                "Thursday",
                "Friday",
                "Saturday"
        };

        System.out.println("[1] Get day by number");
        System.out.println("[2] Get all days");
        System.out.println("[3] Get day/s by range");
        System.out.print("Enter choice: ");
        int choice = sc.nextInt();

        switch (choice) {
            case 1:
                System.out.print("Enter day number: ");
                int dayNumber = sc.nextInt();
                System.out.println("Day: " + days[dayNumber-1]);
                break;

            case 2:
                for (int i = 0; i < 7; i++) {
                    System.out.println(days[i]);
                }
                break;

            case 3:
                System.out.print("Enter number range: ");
                int range = sc.nextInt();
                for (int i = 0; i < range; i++) {
                    System.out.println(days[i]);
                }
                break;
        
            default:
                break;
        }
        

    }

}
