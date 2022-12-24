import random as r

files = ["data_1.txt", "data.txt", "test_10.txt", "test_100.txt", "test_500.txt", "test_1000.txt", "test_1500.txt"]
num = [5, 50, 10, 100, 500, 1000, 1500]

for i in range(len(files)):
    print(files[i])
    file = open(files[i], 'w')

    STREETS = ["Mira", "Lenina", "Naberezhnaya", "New", "Begovaya", "Sadovaya", "Soviet", "Arbatskaya", "Kuncevskaya", "Central"]

    totals = []
    k = 0

    while k < num[i]:

        string = r.choice(STREETS) + '\n'
        string += str(r.randint(1, 50)) + '\n' # house
        string += str(r.randint(1, 20)) + '\n'  #floor
        string += str(r.randint(1, 100)) + '\n' #flat
        string += str(float(r.randint(40, 150))) + "\n" # whole sq meter
        string += str(r.randint(1, 4)) + "\n"   # rooms
        string += str(float(r.randint(1000, 15000))) + "\n"  #cost of sq meter

        kind = r.choice(["primary", "secondry"])

        if (kind == "primary"):
            string += "primary\n"
            trim = r.choice(["y\n", "n\n"])
            string += trim

        else:
            string += "secondary\n"
            string += str(r.randint(1900, 2020)) + "\n"
            string += str(r.randint(1, 10)) + "\n"
            string += str(r.randint(1, 20)) + "\n"
            animals = r.choice(["y\n", "n\n"])
            string += animals

        if (string not in totals):
            totals.append(string)
            file.write(string)
            k += 1

    file.close()
        