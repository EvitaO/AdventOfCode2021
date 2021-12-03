
def     main():
    input = {}
    for l in open("inputdata2"):
        (key, val) = l.split()
        if key in input:
            input[key] = input[key] + int(val)
        else:
            input[key] = int(val)
    print(input["forward"] * (input["down"] - input["up"]))
    

if __name__ == "__main__":
    main()