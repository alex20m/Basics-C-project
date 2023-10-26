This was made as a school project in a basics in C programmin course. The task was to implement a results system for a rally race that consists of several special stages. The system stores the completion time of drivers from different teams.

We got instructions on how the system should work, but we got to implement it however we wanted.


This was the instructions we got:

A driver is represented with the following data:
surname of the driver, which is a string that can have arbitrary length.
team of the driver, which is a string that can have arbitrary length.
hour is the total number of hours the driver has completed the race stages up to this point, which is a non-negative integer.
minute is the driver’s stage completion minutes, which is an integer between 0 and 59 (inclusive).
second is the driver’s stage completion seconds, which is an integer between 0 and 59 (inclusive).

The program should be able to support arbitrary number of drivers.

The system must be able to process the following commands:

Add driver command, which adds a driver to the system.
The command has the following format.
A surname team
where
surname
is the driver’s surname, which is an arbitrary length string.
team
is the name of the team, which is an arbitrary length string.
For example, a valid add character command is as follows.
A Kankkunen Renault
Initially the driver has 0 racing time.
If the character with the specified name is already in the system, the program must print an error message.

Update total time command, which adds the specified time to the driver’s total time.
The command has the following format.
U surname hour minute second
where
surname
is the driver’s surname.
hour
is the number of hours to be added. This must be a non-negative integer.
minute
is the number of minutes to be added. This must be in the valid minutes range.
second
is the number of seconds to be added. This must be in the valid seconds range.
For example, a valid update total time command is as follows.
U Kankkunen 0 52 16
The result of time addition must yield valid minutes and seconds.
If the given driver does not exist in the database, an error message should be printed.

Print race command, which displays the race time table.
The command has the following format.
L
It prints the stored drivers on separate lines as follows.
surname team hour minute second
where the entries are the names of the driver data fields.
For example, print race command output is as follows.
Shipiro Toyota 1 55 08
Kankkunen Renault 2 52 59
SUCCESS
The database entries should be printed in the order of total race time such that the driver with shorter race time will be printed first.
The worth of this command is two points. The worth of printing all the database entries is 1 point. If their order is also correct, you will get another point.

Save to file command, which saves the database to a text file.
The command has the following format.
W filename
where
filename
is the name of the text file.
It writes the stored drivers on separate lines as follows.
surname team hour minute second
where the entries are the names of the driver data fields.
If an error occurs, it must print an error message.

Load from file command, which loads drivers from a text file saved using Save to file command.
The command has the following format.
O filename
where
filename
is the name of the text file.
It assumes the stored drivers are on a separate line in the format specified above.
If an error occurs, it should print an error message.
If the file is valid and loaded correctly, the current system contents must be replaced with the entries loaded from the file.

Quit program command, which releases all allocated memory and exits the program.
The command has the following format.
Q
This operation must be implemented so that you can prevent memory leaks.

Below is an example of possible command sequence.
A Kankkunen Renault
A Latvala Volkswagen
U Kankkunen 0 52 16
U Latvala 1 01 20
U Kankkunen 0 49 50
U Latvala 0 47 15
L
W tulokset
Q

As a result, Kankkunen will have total time of 1 hour, 42 minutes and 6 seconds, while Latvala has 1 hour, 48 minutes and 35 seconds. Kankkunen will be printed before Latvala in the results table. The table will be written to the text file “tulokset”.