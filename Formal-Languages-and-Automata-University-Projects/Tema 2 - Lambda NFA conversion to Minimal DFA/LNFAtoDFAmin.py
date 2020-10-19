from copy import deepcopy
from queue import Queue


alf = ['$']


class Automat:
    def __init__(self, states, n, q0, alf, fin, delta):
        self.delta = deepcopy(delta)
        self.states = deepcopy(states)
        self.q0 = q0
        self.alf = deepcopy(alf)
        self.n = n
        self.fin = deepcopy(fin)


# Accepters
def LNFA_Check(automat, word, i, state):  # Functioneaza ca un DFS recursiv
    global accepted
    if accepted:
        return

    if automat.delta[state]['$'] != [-1]:       # Verificam mai intai daca putem sa ne ducem undeva din starea curenta cu lambda
        for st in automat.delta[state]['$']:
            LNFA_Check(automat, word, i, st)

    if i == len(word):
        if state in automat.fin:
            accepted = 1
        return

    if automat.delta[state][word[i]] == [-1]:
        return
    for st in automat.delta[state][word[i]]:
        LNFA_Check(automat, word, i + 1, st)


def NFA_Check(automat, word, i, state):  # Functioneaza ca un DFS recursiv
    global accepted
    if accepted:
        return

    if i == len(word):
        if state in automat.fin:
            accepted = 1
        return

    if automat.delta[state][word[i]] == [-1]:
        return
    for st in automat.delta[state][word[i]]:
        NFA_Check(automat, word, i + 1, st)


def DFA_Check(automat, word, state):  # Functioneaza ca un DFS recursiv
    current = state
    for i in range(len(word)):
        current = automat.delta[current][word[i]]
        if (current == -1):
            return False
    if current in automat.fin:
        return True
    return False



# Pentru LNFA to NFA
def lambda_closure(delta, n):
    closure = {str(x) : [str(x)] for x in range(n)}
    q = Queue()
    for key in closure.keys():
        ans = []
        q.put(key)
        while not q.empty():
            current = q.get()
            if delta[current]['$'] == [-1]:
                pass
            else:
                for st in delta[current]['$']:
                    if st not in ans:
                        ans.append(st)
                        q.put(st)
        closure[key].extend(ans)
        if closure[key].count(key) > 1:
            closure[key].remove(key)
        closure[key].sort()
    #print(closure)
    return closure


def LNFA_to_NFA(automat):
    # Check if it is a NFA already:
    isNFA = 1
    for key in automat.delta.keys():
        if '$' in automat.delta[key]:
            if automat.delta[key]['$'] != [-1]:
                isNFA = 0
                break
    if isNFA:
        new_alf = deepcopy(automat.alf)
        if '$' in new_alf:
            new_alf.remove('$')
        new_delta = deepcopy(automat.delta)
        for key in new_delta.keys():
            if '$' in new_delta[key]:
                del new_delta[key]['$']
        NFA = Automat(automat.states, automat.n, automat.q0, new_alf, automat.fin, new_delta)
        return NFA

    # Calcularea lamba-closure
    closure = lambda_closure(automat.delta, automat.n)
    #print(closure)

    # Crearea noilor componente pentru NFA
    new_alf = deepcopy(automat.alf)
    new_alf.remove('$')
    new_delta = {str(i): {x: [-1] for x in new_alf} for i in range(automat.n)}
    new_fin = []

    # Calcularea noului delta pentru NFA
    for key in new_delta.keys():
        key_closure = deepcopy(closure[key])
        for letter in new_alf:
            ans_letter = set()
            for state in key_closure:
                if automat.delta[state][letter] != [-1]:
                    ans_letter = ans_letter.union(set(automat.delta[state][letter]))
            ans_letter = sorted(list(ans_letter))
            ans = set()
            for st in ans_letter:
                ans = ans.union(set(closure[st]))

            ans = sorted(list(ans))
            if ans != []:
                new_delta[key][letter] = ans
    #print(new_delta)

    # Determinarea noilor stari finale
    for key in closure.keys():
        for st in automat.fin:
            if st in closure[key]:
                new_fin.append(key)
                break
    #print(new_fin)

    # Eliminarea starilor echivalente
    states = [str(key) for key in range(n)]
    to_change = {key: None for key in states}
    to_remove = []
    for i in range(len(states)):
        if new_delta[states[i]] == None:
            continue
        for j in range(i + 1, len(states)):
            # Verific daca ambele au aceeasi stare (daca sunt ambele finale sau nu)
            if (states[i] in new_fin and states[j] not in new_fin) or (states[i] not in new_fin and states[j] in new_fin):
                continue
            # Verific daca ambele au aceleasi tranzitii
            if new_delta[states[i]] == new_delta[states[j]]:
                #print(states[i], states[j])
                to_change[states[j]] = states[i]
                new_delta[states[j]] = None
                to_remove.append(states[j])
    # Sterg starile echivalente din new_delta
    for x in to_remove:
        del new_delta[x]
    # Schimb starile deja sterse din new_delta in starea corespunzatoare
    for key in new_delta.keys():
        for letter in new_alf:
            for rem in to_remove:
                if rem in new_delta[key][letter]:
                    new_delta[key][letter].remove(rem)
                    if to_change[rem] not in new_delta[key][letter]:
                        new_delta[key][letter].append(to_change[rem])
                    new_delta[key][letter].sort()
    new_n = n - len(to_remove)
    # Update al starilor finale dupa stergerea echivalentelor
    for st in to_remove:
        if st in new_fin:
            new_fin.remove(st)
    #print(to_change)
    #print(to_remove)
    #print(new_delta)
    #print(new_fin)

    # Redenumesc starile in 0, 1, ... new_n - 1
    new_states = [str(i) for i in range(new_n)]
    old_states = sorted(list(set(states).difference(to_remove)), key=int)
    #to_change = {old_states[i]: new_states[i] for i in range(new_n)}
    #print(to_change)
    #for key in new_delta.keys():
    #    for letter in new_alf:
    #        for rem in to_remove:
    #            if rem in new_delta[key][letter]:
    #                new_delta[key][letter].remove(rem)
    #                if to_change[rem] not in new_delta[key][letter]:
    #                    new_delta[key][letter].append(to_change[rem])
    #                new_delta[key][letter].sort()

    NFA = Automat(old_states, new_n, automat.q0, new_alf, sorted(new_fin, key=int), new_delta)
    return NFA


# Pentru NFA to DFA
def NFA_to_DFA(automat):
    new_states = [automat.q0]
    new_delta = {}
    q = Queue()
    q.put(automat.q0)
    while not q.empty():
        current = q.get()
        new_delta[current] = {}
        # Aflam noile tranzitii pentru nodul curent cu fiecare litera
        for letter in automat.alf:
            ans = set()
            for x in current:
                ans = ans.union(set(automat.delta[x][letter]))
            if -1 in ans and len(ans) > 1:
                ans.remove(-1)
            ans = sorted(list(ans))
            if ans == [-1]:
                new_delta[current][letter] = -1
            else:
                if len(ans) == 1:
                    new_delta[current][letter] = ans[0]
                else:
                    new_delta[current][letter] = ''.join(ans)
                if new_delta[current][letter] not in new_states:
                    new_states.append(new_delta[current][letter])
                    q.put(new_delta[current][letter])

    #print(new_delta)

    # Calculam noile stari finale
    new_fin = []
    for sf in automat.fin:
        for ns in new_states:
            if sf in ns and ns not in new_fin:
                new_fin.append(ns)
    #print(new_fin)

    # Redenumim starile compuse
    to_change = {x: None for x in new_states if len(x) > 1}
    min_new = str(int(max(automat.states)) + 1)         # Numerotam incepand cu primul cel mai mic numar mai mare decat cea mai mare stare din starile NFA-ului
    for st in to_change.keys():
        to_change[st] = min_new
        min_new = str(int(min_new) + 1)
    #print(to_change)
        # Redenumim in starile finale
    for i in range(len(new_fin)):
        if new_fin[i] in to_change.keys():
            new_fin[i] = to_change[new_fin[i]]
    #print(new_fin)
        # Redenumim in new_states si in new_delta
    for i in range(len(new_states)):
        if new_states[i] in to_change.keys():
            new_states[i] = to_change[new_states[i]]
    new_states.sort()
    for state in new_delta.keys():
        for letter in automat.alf:
            if new_delta[state][letter] in to_change.keys():
                new_delta[state][letter] = to_change[new_delta[state][letter]]
    for state in new_delta.keys():
        if state in to_change.keys():
            new_delta[to_change[state]] = new_delta[state]
            del new_delta[state]

    #print(new_states, new_delta)

    DFA = Automat(sorted(new_states, key = int), len(new_states), automat.q0, automat.alf, sorted(new_fin, key = int), new_delta)
    return DFA


# Pentru DFA to minDFA
def DFA_to_minDFA(automat):
    new_fin = deepcopy(automat.fin)
    new_states = deepcopy(automat.states)

    # Creez matricea de echivalenta si o setam la True
    echiv = {new_states[i]: {new_states[j]: True for j in range(0,i)} for i in range(1,len(new_states))}
    # Marchez cu falses perechile de stari care nu sunt de aceeasi finalitate
    for key1 in echiv.keys():
        for key2 in echiv[key1].keys():
            if (key1 in new_fin and key2 not in new_fin) or (key1 not in new_fin and key2 in new_fin) or key1 == key2:
                echiv[key1][key2] = False
    #print(echiv)

    # Marcam cu false perechile de stari (q, r) pentru care (delta(q, alfa), delta(r, alfa)) sunt False. Repetam pana nu sunt schimbari
    predechiv = {}
    while (predechiv != echiv):
        predechiv = deepcopy(echiv)
        for key1 in echiv.keys():
            for key2 in echiv[key1].keys():
                if echiv[key1][key2] == True:
                    check = set()
                    for letter in automat.alf:
                        dk1 = automat.delta[key1][letter]
                        dk2 = automat.delta[key2][letter]
                        #print(key1, key2, letter, max(dk1, dk2), min(dk2, dk1))
                        if dk1 == dk2:
                            pass
                        elif dk1 == -1 or dk2 == -1:
                            check.add(False)
                        else:
                            check.add(echiv[str(max(int(dk1), int(dk2)))][str(min(int(dk1), int(dk2)))])
                    if False in check:
                        echiv[key1][key2] = False
    #print(echiv)

    #Facem starile noi (echivalentele le grupam)
    comb_set = set()
    combined = []
    for key1 in echiv.keys():
        for key2 in echiv[key1].keys():
            if echiv[key1][key2] == True:
                comb_set.add(key1)
                comb_set.add(key2)
                toAdd = True
                for i in range(len(combined)):
                    if key1 in combined[i]:
                        if key2 not in combined[i]:
                            combined[i].append(key2)
                            combined[i].sort()
                        toAdd = False
                    elif key2 in combined[i]:
                        if key1 not in combined[i]:
                            combined[i].append(key1)
                            combined[i].sort()
                        toAdd = False
                if toAdd:
                    combined.append(sorted([key1, key2]))
    # Facem un dictionar care sa faca map de la ficare noua stare combinata la una din cele care e compusa, si de la fiecare veche la cea combinata
    to_change = {''.join(x): x[0] for x in combined}
    for st in new_states:
        for comb in combined:
            if st in comb:
                to_change[st] = ''.join(comb)
                break
        else:
            to_change[st] = st
    #print(to_change, combined)
    new_states = [''.join(x) for x in combined]
    new_states.extend(list(set(automat.states).difference(comb_set)))
    #print(new_states)

    # Creez delta nou
    new_delta = {x: {letter: (to_change[automat.delta[to_change[x]][letter]] if automat.delta[to_change[x]][letter] != -1 else -1) for letter in automat.alf} for x in new_states}
    #print(new_delta)

    # Noua stare initiala si noile stari finale
    new_q0 = to_change[q0]
    new_fin = sorted(list(set([to_change[x] for x in new_fin])))
    #print(new_q0, new_fin)

    # Eliminarea starilor neaccesibile, facem un BFS din q0 si adaugam fiecare nod intr-o lista:
    accesible = [new_q0]
    q = Queue()
    q.put(new_q0)
    while not q.empty():
        current = q.get()
        for letter in automat.alf:
            if new_delta[current][letter] != -1 and new_delta[current][letter] not in accesible:
                q.put(new_delta[current][letter])
                accesible.append(new_delta[current][letter])

    nonaccesible = list(set(new_states).difference(set(accesible)))
    #print(nonaccesible, accesible)
    for x in nonaccesible:
        new_states.remove(x)
        del new_delta[x]        # in celelalte stari nu poate aparea o stare neaccesibila, pentru ca era sa o "gasim" cu BFS-ul, deci stergem doar entry-ul lui x din dinctionar
        if x in new_fin:
            new_fin.remove(x)

    # Eliminarea starilor dead-end
    nondeadend = []
    # Facem iarasi cate un BFS pentru fiecare nod ramas
    for nod in new_states:
        if nod in new_fin:                      # Bug#32131, good to know, if a node is already a final state, then we can add it into our nondeadend list
            nondeadend.append(nod)
            continue
        viz = []
        q = Queue()
        q.put(nod)
        while not q.empty():
            current = q.get()
            for letter in automat.alf:
                if new_delta[current][letter] != -1 and new_delta[current][letter] not in viz:
                    q.put(new_delta[current][letter])
                    viz.append(new_delta[current][letter])
                    if new_delta[current][letter] in new_fin:
                        nondeadend.append(nod)
                        while not q.empty():
                            trash = q.get()
                        break
    deadend = list(set(new_states).difference(nondeadend))
    #print(deadend, nondeadend)

    for x in deadend:
        new_states.remove(x)
        del new_delta[x]
    for st in new_states:       # Schimbam tranzitiile in starile dead-end in -1
        for letter in automat.alf:
            if new_delta[st][letter] in deadend:
                new_delta[st][letter] = -1
    #print(new_states, new_delta)

    # Returnarea
    new_n = len(new_states)
    minDFA = Automat(sorted(new_states, key = int), new_n, new_q0, automat.alf, sorted(new_fin, key = int), new_delta)
    return minDFA





### CITIREA DATELOR DIN FISIER
with open("input.in") as f:
    n = int(f.readline())

    m = int(f.readline())
    alf.extend(f.readline().split())

    q0 = f.readline().rstrip()

    k = int(f.readline())
    fin = f.readline().split()

    states = [str(i) for i in range(n)]
    delta = {key: {x: [-1] for x in alf} for key in states}
    l = int(f.readline())
    for i in range(l):
        st1, ch, st2 = f.readline().rstrip().split()
        if delta[st1][ch] == [-1]:
            delta[st1][ch] = [st2]
        else:
            delta[st1][ch].append(st2)

    words = []
    wn = int(f.readline())
    for i in range(wn):
        words.append(f.readline().rstrip())
    #print(n, m, alf, states, q0, k, fin, trans)






# Definesc Lambda-NFA-ul initial
LNFA = Automat(states, n, q0, alf, fin, delta)

#Verificarea corectitudinei
print('L-NFA:')
print(LNFA.states, LNFA.n, LNFA.q0, LNFA.alf, LNFA.fin, LNFA.delta)
print('Verificare input-uri: ')
for w in words:
    accepted = 0
    LNFA_Check(LNFA, w, 0, LNFA.q0)
    print(f'\t{w}: ', end='')
    if accepted:
        print('Accepted')
    else:
        print('Not accepted')


NFA = LNFA_to_NFA(LNFA)
print('NFA:')
print(NFA.states, NFA.n, NFA.q0, NFA.alf, NFA.fin, NFA.delta)
print('Verificare input-uri: ')
for w in words:
    accepted = 0
    NFA_Check(NFA, w, 0, NFA.q0)
    print(f'\t{w}: ', end='')
    if accepted:
        print('Accepted')
    else:
        print('Not accepted')


DFA = NFA_to_DFA(NFA)
print('DFA:')
print(DFA.states, DFA.n, DFA.q0, DFA.alf, DFA.fin, DFA.delta)
print('Verificare input-uri: ')
for w in words:
    accepted = DFA_Check(DFA, w, DFA.q0)
    print(f'\t{w}: ', end='')
    if accepted:
        print('Accepted')
    else:
        print('Not accepted')


minDFA = DFA_to_minDFA(DFA)
print('Minimal DFA:')
print(minDFA.states, minDFA.n, minDFA.q0, minDFA.alf, minDFA.fin, minDFA.delta)
print('Verificare input-uri: ')
for w in words:
    accepted = DFA_Check(minDFA, w, minDFA.q0)
    print(f'\t{w}: ', end='')
    if accepted:
        print('Accepted')
    else:
        print('Not accepted')