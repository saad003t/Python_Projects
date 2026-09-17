#Count the Number of Student

numofStudents = int(input("Enter Total Students:"))


#Data Storage

studentData = []
used_roll_numbers = set()

#inserting data

for i in range(numofStudents):
    print(f"Enter the Data of Student {i+1}")
    name = input("Name: ")
    roll_no = int(input("Roll Number: "))
    while roll_no in used_roll_numbers:
        print("That roll number is already assigned. Please enter a unique roll number.")
        roll_no = int(input("Roll Number: "))
    used_roll_numbers.add(roll_no)
    marks = int(input("Marks: "))

    if marks > 95:
        grades = "A+"
    elif marks >= 90:
        grades = "A"
    elif marks > 85:
        grades = "B+"
    elif marks >= 80:
        grades = "B"
    elif marks >= 70:
        grades = "C+"
    elif marks >= 60:   
        grades = "C"
    elif marks >= 33:
        grades = "D"
    else:
        grades = "F"

    students = {
        "name": name,
        "roll_no": roll_no,
        "marks": marks,
        "grades": grades
    }

    studentData.append(students)

#Data Printing
print("\n All Students Data: ")

for s in studentData:
    print(f"{s['name']} - Roll Number: {s['roll_no']}- Marks: {s['marks']} - Grades: {s['grades']}")


#Passed Students
print("\n Student Who are Passed: ")

for s in studentData:
    if s['marks'] >= 33:
        print(f"{s['name']} - Marks: {s['marks']}") 
