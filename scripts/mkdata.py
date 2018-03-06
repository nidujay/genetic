import random
import json

def mkstudent(n):
    levels = ['Q1', 'Q2', 'Q2', 'Q3', 'Q3', 'Q4']
    return {
            'name' : 'Student ' + str(n),
            'from' : random.choice(['2A', '2B', '2C', '2D', '3A', '3B', '3C', '3D']),
            'level' : random.choice(levels)
    }

def filter_from(students, from_class):
    result=[]
    for idx,s in enumerate(students):
        if s['from'] == from_class:
            result.append(idx)
    return result

def make_friends(who, students):
    class_mates=filter_from(students, who['from'])
    random.shuffle(class_mates)
    options=class_mates[0:4]
    friends=[students[f]['name'] for f in options if who['name'] != students[f]['name']]
    return friends

students = [ mkstudent(i)  for i in range(83)]

for s in students:
    s['friends'] = make_friends(s, students);

def to_c_array(l):
    r = '{'
    for i in l:
        r += str(i) + ','

    return r + '}'

def print_student(s):
    print '\t{ ' + str(s['from']) + ', "' + s['name'] + '", ' + s['level'] + ', ' + to_c_array(s['friends']) + '},'

teachers = [ 'Teacher A', 'Teacher B', 'Teacher C', 'Teacher D' ]
 
out = {"teachers" : teachers, "students" : students}

print json.dumps(out, indent=4)
