# TestLaunchDay

This C++ program intakes a CSV file containing an unknown amount of days, each containing 6 weather parameter values.

Based on the following criteria, it calculates which day is most eligible for a missile launch:
-Temperature between 2 and 31 degrees Celsius;
-Wind speed no more than 10m/s (the lower the better);
-Humidity less than 60% (the lower the better);
-No precipitation;
-No lightings;
-No cumulus or nimbus clouds

If the criteria is met in multiple days it compare Humidity and Wind to get the best day for a missile launch.

It also calculate the highest, lowest, average and median values seen throughout the given days and store them.

Then it passes the data from a vector into another CSV file called "WeatherReport.csv" and sends it via e-mail using SMTP.

I made this program for a task as a part of an interview for a position.
