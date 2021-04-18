import os 
pos = os.getcwd()
for i in range(21):
    try:
        with open(f"HW2101{i:02d}.txt", "x") as file:
            file.close()
    except:
        pass