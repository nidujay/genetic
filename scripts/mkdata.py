import random

names = [
    "Brice Rubio", 
    "Heidy Manning", 
    "Camryn Swanson", 
    "Yael Washington", 
    "Karsyn Osborne", 
    "Bradyn Ali", 
    "Skye Hood", 
    "Halle Drake", 
    "Destinee Morton", 
    "Jamir Schneider", 
    "Emma Hogan", 
    "Christine Sanders", 
    "Salma Horn", 
    "Clay Shelton", 
    "Peyton Mays", 
    "Miles Chambers", 
    "Pamela Yoder", 
    "Jayvion Hopkins", 
    "Carlie Galvan", 
    "Messiah Hobbs", 
    "Daniela Rosales", 
    "Jordan Arroyo", 
    "Jensen Robles", 
    "Savanah Lam", 
    "Darwin Middleton", 
    "Nyasia Randall", 
    "Marc Nixon", 
    "Abigayle Downs", 
    "Sullivan Skinner", 
    "Hallie Morrison", 
    "Ethen Howe", 
    "Kristina Montoya", 
    "Cali Archer", 
    "Rebekah Hawkins", 
    "Taniyah Kerr", 
    "Janiyah Ball", 
    "Maverick Peck", 
    "Karina Mitchell", 
    "Ronnie Schmitt", 
    "Bernard Welch", 
    "Edith Montes", 
    "Ashlee Stephenson", 
    "Danna Yu", 
    "Izayah Oliver", 
    "Livia Barnett", 
    "Davion Benton", 
    "Yuliana Garrison", 
    "Serena Ho", 
    "Quintin Ortega", 
    "Sawyer Arellano", 
]

culture_mix=[0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3]
class_size=10

def random_prefs(student_id):
    class_id = student_id / class_size;
    start = class_id * class_size;
    end = start + class_size;

    choices = range(start, end)
    random.shuffle(choices)

    rv = '{'
    for i in choices[0:4]:
        if (i != student_id):
            rv += str(i) + ','

    rv += '}'
    return rv

def academic_level():
    levels=['high', 'mid', 'mid', 'mid', 'mid', 'mid', 'mid', 'low']
    return random.choice(levels)

for i in range(len(names)):
    class_id = i / class_size;
    print '\t{ ', class_id, ', "' + names[i] + '",', random_prefs(i) + ',', academic_level(), '},'
