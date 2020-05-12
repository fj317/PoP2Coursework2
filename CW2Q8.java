public class CW2Q8 {
    public static void main(String[] args) {
        // stores all the days within each month
        int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int tuesdayCount = 0;
        // 0 for monday, 1 for tuesday, etc
        int dayCount = 0;
        // count from 1900 to 2000
        for (int year = 1900; year <= 2000; year++) {
            // accounting for leap years & leap centuries
            if (mod(year, 4) == 0) {
                // if the year is a leap year, make a check to see if it is a leap century
                if (mod(year, 100) == 0 && mod(year, 400) != 0) {
                    // if it isn't a leap century then set February to 28 days
                    monthDays[1] = 28;
                } else {
                    // if it is a leap century OR if it is a normal leap year then set February to 29 days
                    monthDays[1] = 29;
                }
            } else {
                // otherwise set February to 28 days
                monthDays[1] = 28;
            }
            // loop through each month of the year
            for (int month = 0; month < 12; month++) {
                // loop through each day of each month
                for (int days = 1; days <= monthDays[month]; days++) {
                    // if the day is a tuesday 1st and the year is not 1900 (as we start counting from 1901) add 1 to the tuesdayCount
                    if (dayCount == 1 && days == 1 && year != 1900) {
                        tuesdayCount++;
                    }
                    // if the dayCount is Sunday then reset it back to Monday, otherwise add another day to the dayCount
                    if (mod(dayCount, 6)== 0 && dayCount != 0) {
                        dayCount = 0;
                    } else {
                        dayCount++;
                    }
                }
            }
        }
        // print to console
        System.out.println("Total Tuesday count: " + tuesdayCount);
    }

    // implementation of the mod function
    public static int mod(int a, int b) {
        int result = a - (a / b) * b;
        return result;
    }
}
