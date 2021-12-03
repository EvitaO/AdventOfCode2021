def     read(filename):
    array = []
    f = open(filename)
    for l in f:
        array.append(int(l))
    return array


def     main():
    # input = read("inputday1")
    input = [int(l)for l in open("inputday1")]
    c = 0
    for i in range(1,len(input)):
        if input[i] > input[i-1]:c+=1
    print(c)


if __name__ == "__main__":
    main()