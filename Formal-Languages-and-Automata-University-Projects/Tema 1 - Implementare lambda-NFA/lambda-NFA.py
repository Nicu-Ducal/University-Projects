fin = [False] * 1010
alf = ['$']


def lambdaNFA(word, i, state):  # Functioneaza ca un DFS recursiv
    global accepted
    if accepted:
        return

    # print(state, word[i]) if i != len(word) else print(state, "test state")
    if i == len(word):
        if fin[state]:
            accepted = 1
        return

    if trans[state]['$'] != [-1]:
        for st in trans[state]['$']:
            lambdaNFA(word, i, st)

    if trans[state][word[i]] == [-1]:
        return
    for st in trans[state][word[i]]:
        lambdaNFA(word, i + 1, st)


with open("lambdaNFA.in") as f:
    n = int(f.readline())

    m = int(f.readline())
    alf.extend(f.readline().split())

    q0 = int(f.readline())

    k = int(f.readline())
    tempF = [int(x) for x in f.readline().split()]
    for state in tempF:
        fin[state] = True
    tempF.clear()

    trans = [{x: [-1] for x in alf} for i in range(0, n)]
    l = int(f.readline())
    for i in range(l):
        temp1, tch, temp2 = f.readline().split()
        if trans[int(temp1)][tch] == [-1]:
            trans[int(temp1)][tch] = [int(temp2)]
        else:
            trans[int(temp1)][tch].append(int(temp2))

    # print(n, m, alf, q0, k, tempF, fin[:n], trans)

    for test in range(7):
        word = f.readline().rstrip()
        accepted = 0
        lambdaNFA(word, 0, q0)
        if accepted:
            print(f"Cuvantul {word} este acceptat!")
        else:
            print(f"Cuvantul {word} nu este acceptat!")
