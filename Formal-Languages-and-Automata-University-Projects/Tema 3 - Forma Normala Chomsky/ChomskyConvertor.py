from queue import Queue
from copy import deepcopy
import re
trans = {}
# new_NT = list("ABCDEFGHIJKLMNOPQRSTUVWYZ")
new_NT = 'M'


# Functie ajutatoare de replacement al celui de-al n-lea caracter din string:
def replacement(string, sub, wanted, n):
    where = [m.start() for m in re.finditer(sub, string)][n - 1]
    before = string[:where]
    after = string[where:]
    after = after.replace(sub, wanted, 1)
    newString = before + after
    return newString


class CFG:
    def __init__(self, nonterminals, terminals, S, trans):
        self.nonterminals = deepcopy(nonterminals)
        self.terminals = deepcopy(terminals)
        self.S = S
        self.trans = deepcopy(trans)


# I. Eliminarea lambda productiilor
def removeLambda(grammar):
    # Eliminam startile neterminale care nu dau productii
    good = [N for N in grammar.trans.keys()]
    bad = [N for N in grammar.nonterminals if N not in good]
    grammar.nonterminals = deepcopy(good)
    for nonterminal in grammar.trans.keys():
        for i in range(len(grammar.trans[nonterminal])):
            for badN in bad:
                if badN in grammar.trans[nonterminal][i]:
                    grammar.trans[nonterminal][i] = grammar.trans[nonterminal][i].replace(badN, '')
        grammar.trans[nonterminal] = list(filter(lambda a: a != '', grammar.trans[nonterminal]))

    # Daca nu are lambda tranzitii, revenim
    if '$' not in grammar.terminals:
        return grammar

    good = False            # Ne oprim cand new_trans va fi gol
    while not good:
        new_trans = {}
        for nonterminal in grammar.trans.keys():
            if '$' in grammar.trans[nonterminal] and len(grammar.trans[nonterminal]) == 1:
                for nt in grammar.trans.keys():
                    if nt != nonterminal:
                        new_trans[nt] = deepcopy(grammar.trans[nt])
                        for i in range(len(new_trans[nt])):
                            if nonterminal in new_trans[nt][i]:
                                if new_trans[nt][i] == nonterminal:
                                    new_trans[nt][i] = '$'
                                else:
                                    new_trans[nt][i] = new_trans[nt][i].replace(nonterminal, '')
                                    if new_trans[nt][i] == '':
                                        new_trans[nt][i] = "$"
                grammar.trans = deepcopy(new_trans)
                # print(grammar.trans)
                break
            elif '$' in grammar.trans[nonterminal] and len(grammar.trans[nonterminal]) > 1:
                for nt in grammar.trans.keys():
                    if nt == nonterminal:
                        new_trans[nt] = deepcopy(grammar.trans[nt])
                        new_trans[nt].remove('$')
                        to_add = []
                        for i in range(len(grammar.trans[nt])):
                            if nt in grammar.trans[nt][i]:
                                # Trebuie sa verific de cate ori apare neterminalul in tranzitia aceasta
                                q = Queue()
                                q.put(grammar.trans[nt][i])
                                while not q.empty():
                                    curr = q.get()
                                    temp_num = curr.count(nonterminal)
                                    if temp_num > 0:
                                        for i in range(1, temp_num + 1):
                                            check = replacement(curr, nonterminal, '', i)
                                            if check == '':
                                                check = '$'
                                            if check not in to_add and check not in grammar.trans[nt]:
                                                to_add.append(check)
                                                q.put(check)
                        new_trans[nt].extend(to_add)
                    else:
                        new_trans[nt] = deepcopy(grammar.trans[nt])
                        to_add = []
                        for i in range(len(new_trans[nt])):
                            if new_trans[nt][i] == nonterminal:
                                if '$' not in new_trans[nt]:
                                    new_trans[nt].append('$')
                            elif nonterminal in new_trans[nt][i]:
                                # Trebuie sa verific de cate ori apare neterminalul in tranzitia aceasta
                                q = Queue()
                                q.put(new_trans[nt][i])
                                while not q.empty():
                                    curr = q.get()
                                    temp_num = curr.count(nonterminal)
                                    if temp_num > 0:
                                        for i in range(1, temp_num + 1):
                                            check = replacement(curr, nonterminal, '', i)
                                            if check == '':
                                                check = '$'
                                            if check not in to_add and check not in new_trans[nt]:
                                                to_add.append(check)
                                                q.put(check)
                        new_trans[nt].extend(to_add)
                grammar.trans = deepcopy(new_trans)
                # print(grammar.trans)
                break
        if new_trans == {}:
            good = True

    return CFG


# 2. Eliminarea redenumirilor
def removeRenames(grammar):
    # Stergem starile X -> X
    for state in grammar.trans.keys():
        if state in grammar.trans[state]:
            grammar.trans[state].remove(state)

    # Inlocuim starile X -> Y
    good = False
    while not good:
        new_trans = deepcopy(grammar.trans)
        for nonterminal in grammar.trans.keys():
            for state in grammar.trans[nonterminal]:
                if state in grammar.nonterminals:
                    new_trans[nonterminal].remove(state)
                    new_trans[nonterminal] = list(set(new_trans[nonterminal]).union(set(grammar.trans[state])))
        if new_trans == grammar.trans:
            good = True
        else:
            grammar.trans = deepcopy(new_trans)

    return grammar


# 3. Eliminam productiile inutile
def removeUseless(grammar):
    # Eliminam mai intai starile inaccesibile
    q = Queue()
    q.put(grammar.S)
    checked = [grammar.S]
    while not q.empty():
        curr = q.get()
        for prod in grammar.trans[curr]:
            for state in prod:
                if state in grammar.nonterminals and state not in checked:
                    q.put(state)
                    checked.append(state)
    useless = list(set(grammar.nonterminals).difference(set(checked)))
    for nonterminal in useless:
        grammar.nonterminals.remove(nonterminal)
        del grammar.trans[nonterminal]
    # print("Here: ", grammar.terminals, grammar.nonterminals, grammar.S, grammar.trans)

    # Eliminam starile care sunt infinite
    toRemove = []
    for nonterminal in grammar.trans.keys():
        for prod in grammar.trans[nonterminal]:
            if nonterminal not in prod:
                break
        else:
            toRemove.append(nonterminal)

    for nonterminal in toRemove:
        del grammar.trans[nonterminal]
    for nonterminal in grammar.trans.keys():
        removeStates = []
        for nt in toRemove:
            for prod in grammar.trans[nonterminal]:
                if nt in prod and prod not in removeStates:
                    removeStates.append(prod)
        grammar.trans[nonterminal] = list(set(grammar.trans[nonterminal]).difference(set(removeStates)))

    return grammar


# 4. Adaugare neterminale noi pentru productii ab sau aU
def addNonterminals(grammar):
    global new_NT
    term_map = {}
    new_transitions = {}
    for nonterminal in grammar.trans.keys():
        for i in range(len(grammar.trans[nonterminal])):
            terms = list(set(grammar.trans[nonterminal][i]).intersection(set(grammar.terminals)))
            nonterms = list(set(grammar.trans[nonterminal][i]).intersection(set(grammar.nonterminals)))
            if (terms != [] and  nonterms != []) or (nonterms == [] and len(terms) > 1) or (nonterms == [] and len(terms) == 1 and len(grammar.trans[nonterminal][i]) > 1):
                for t in terms:
                    if t not in term_map:
                        term_map[t] = new_NT
                        new_transitions[new_NT] = [t]
                        grammar.nonterminals.append(new_NT)
                        new_NT = chr(ord(new_NT) + 1)
                    grammar.trans[nonterminal][i] = grammar.trans[nonterminal][i].replace(t, term_map[t])
    grammar.trans.update(new_transitions)

    return grammar


# 5. Adaugam neterminale pentru productiile cu mai mult de 2 neterminale
def splitProductions(grammar):
    global new_NT
    nt_map = {}
    good = False
    while not good:
        new_trans = {}
        for nonterminal in grammar.trans.keys():
            for i in range(len(grammar.trans[nonterminal])):
                if grammar.trans[nonterminal][i] not in grammar.terminals and len(grammar.trans[nonterminal][i]) > 2:
                    new_prod = grammar.trans[nonterminal][i][1:]
                    if new_prod not in nt_map.keys():
                        nt_map[new_prod] = new_NT
                        new_trans[new_NT] = [new_prod]
                        grammar.nonterminals.append(new_NT)
                        new_NT = chr(ord(new_NT) + 1)
                    grammar.trans[nonterminal][i] = grammar.trans[nonterminal][i].replace(new_prod, nt_map[new_prod])
        if new_trans != {}:
            grammar.trans.update(new_trans)
        else:
            good = True

    return grammar


with open("input7.in") as file:
    # Terminalele
    terminals_num = int(file.readline())
    terminals = file.readline().rstrip().split()

    # Starea de start
    start = file.readline().rstrip()

    # Neterminalele
    nonterminals_num = int(file.readline())
    nonterminals = file.readline().rstrip().split()

    # Nr. de tranzitii
    k = int(file.readline())
    for i in range(k):
        state = file.readline().rstrip()
        transitions = file.readline().rstrip().split()
        trans[state] = transitions

CFG = CFG(nonterminals, terminals, start, trans)
print("Initial:", CFG.terminals, CFG.nonterminals, CFG.S, CFG.trans)

# 1. Eliminam lambda tranzitiile
CFG = removeLambda(CFG)
print("Pasul 1:", CFG.terminals, CFG.nonterminals, CFG.S, CFG.trans)

# 2. Eliminam redenumirile
CFG = removeRenames(CFG)
print("Pasul 2:", CFG.terminals, CFG.nonterminals, CFG.S, CFG.trans)

# 3. Eliminam productiile inutile
CFG = removeUseless(CFG)
print("Pasul 3:", CFG.terminals, CFG.nonterminals, CFG.S, CFG.trans)

# 4. Adaugare neterminale noi
CFG = addNonterminals(CFG)
print("Pasul 4:", CFG.terminals, CFG.nonterminals, CFG.S, CFG.trans)

# 5. Adaugare neterminale noi pentru productiile cu mai mult de 2 neterminali
CFG = splitProductions(CFG)
print("Pasul 5:", CFG.terminals, CFG.nonterminals, CFG.S, CFG.trans)
