import calendar

"""
year = input("Enter year: ")
month = input("Enter month: ")

print(calendar.month(int(year), int(month)))

"""


# calender using functions in python

class CalendarManager:
    def __init__(self):
        self.calendar = calendar.TextCalendar(firstweekday=calendar.SUNDAY)
    
    def get_calendar(self, year, month):
        try:
            year = int(year)
            month = int(month)
            if month < 1 or month > 12:
                return "Invalid month. Please enter a number between 1 and 12."
            if year < 1:
                return "Invalid year. Please enter a positive number."
            return self.calendar.formatmonth(year, month)
        except ValueError:
            return "Invalid input. Please enter numeric values."

def main():
    cal = CalendarManager()
    
    while True:
        try:
            year = input("Enter year (or 'q' to quit): ")
            if year.lower() == 'q':
                break
                
            month = input("Enter month (1-12): ")
            result = cal.get_calendar(year, month)
            print("\n" + result)
            
        except KeyboardInterrupt:
            print("\nProgram terminated by user.")
            break

if __name__ == "__main__":
    main()