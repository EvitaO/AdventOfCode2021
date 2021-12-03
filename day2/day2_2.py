def     getresult(input):
    x,y,aim = 0,0,0
    for i in input:
        if i[0] == "forward":
            x += int(i[1])
            y += aim * int(i[1])
        elif i[0] == "up":
            aim -= int(i[1])
        else:
            aim += int(i[1])
    print(x*y)

def     main():
    input = []
    for l in open("inputdata2"):
        (key, val) = l.split()
        input.append((key, val))
    getresult(input)
    
if __name__ == "__main__":
    main()