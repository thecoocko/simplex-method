import numpy as np
import copy as cop


def isOpt(c):
    for i in range(len(c)):
        if c[i] < 0:
            return False
        else:
            return True

def getBasis(a,c,b):
    a = np.array(a)
    return a[:,0]

def getElement(A,c,b):
    bi = [0]*len(A)
    
    

def newTableu(a,c,b):
    tableu = cop.deepcopy(a)
    e = np.zeros(np.shape(tableu)[1]+1)
    n_t = [[0 for i in range(np.shape(tableu)[1]+1)] for j in range(np.shape(tableu)[0])]
    f_values = np.zeros(len(c))


    tableu = np.insert(tableu,np.shape(tableu)[1],b,axis=1)
    enabling_el = tableu[getElement(a,c,b)[1]][getElement(a,c,b)[0]]
    enabling_col = tableu[:,getElement(a,c,b)[0]]

    for k in range(np.shape(tableu)[1]):
        e[k] = tableu[3][k]/enabling_el
        n_t[3][k] = e[k]
          
    for i in range(np.shape(tableu)[0]):
        for j in range(np.shape(tableu)[1]):
            n_t[i][j] = (n_t[3][j]*(-1)*enabling_col[i])+tableu[i][j]
    
    for i in range(np.shape(n_t)[1]):
        n_t[np.shape(n_t)[0]-1][i] = e[i]
    
    for i in range(7):
        f_values[i] = n_t[3][i]*(-1)*c[0]+(c[i])

    return n_t,f_values


    
def main():
    c = [-1, -1, 0, 0, 0,0,0]
    A = [
    [-3,2,1,0,0,0,1],
    [1,2,0,1,0,0,14],
    [2,1,0,0,1,0,13],
    [3,-1,0,0,0,1,12]
    ]
    b = [1,14,13,12]
    print(isOpt(c))
    print(getElement(A,c,b))
    print(newTableu(A,c,b))
    print(np.shape(A))

if __name__=="__main__":
    main()

