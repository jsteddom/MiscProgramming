import sqlite3

class Student:
    def __init__(self, name, id, grade):
        self.name = name
        self.id = id
        self.grade = grade
    def updateGrade(self, grade):
        self.grade = grade

connection = sqlite3.connect("Student.db")
cur = connection.cursor()
#cur.execute("CREATE TABLE student(name, id, grade)")
res = cur.execute("SELECT name FROM sqlite_master")
print(res.fetchone())
cur.execute(""" 
        INSERT INTO Student VALUES
            ('Mitchell', 101, 'A'),
            ('NEIL', 102, 'C'),
            ('Leland', 103, 'B')
""")
connection.commit()




#s1 = Student("Mitch", 101, "A")
#print(s1.name)