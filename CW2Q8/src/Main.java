public class Main {
    public static void main(String[] args) {
        // stores all the days within each month
        int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int tuesdayCount = 0;
        // 0 for monday, 1 for tuesday, etc
        int dayCount = 0;
        // count from 1900 to 2000
        for (int year = 1900; year <= 2000; year++) {
            // accounting for leap years & leap centuries
            if (year % 4 == 0) {
                if (year % 100 == 0 && year % 400 != 0) {
                    monthDays[1] = 28;
                } else {
                    monthDays[1] = 29;
                }
            } else {
                monthDays[1] = 28;
            }
            for (int month = 0; month < 12; month++) {
                for (int days = 1; days <= monthDays[month]; days ++) {
                    if (dayCount == 1 && days == 1 && year != 1900) {
                        tuesdayCount++;
                    }
                    if (dayCount % 6 == 0 && dayCount != 0) {
                        dayCount = 0;
                    }
                    else {
                        dayCount ++;
                    }
                }
            }
        }
        System.out.println("Total Tuesday count: " + tuesdayCount);
    }
}
