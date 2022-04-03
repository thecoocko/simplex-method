import numpy as np
class DualSimplex(object):
    # Конструктор (функция инициализации)
    def __init__(self,z,B,bound):  
        self.X_count=len(z)          # Количество переменных
        self.b_count=len(bound)      # Количество ограничений
        self.z=z                     # Целевая функция
        self.C=[]                    #Номер чека
        self.B=B                     # Базовые переменные, из-за правил работы, базовые переменные должны быть указаны в порядке
        self.bound=bound             # Ограничения, включая правую константу
        self.flag=0                  # Тип решения, 0 - (временно) нет решения, 1 - единственное оптимальное решение
        self.special=False           # Ограничения Все коэффициенты больше или равны 0, приемлемого решения нет
    #Iteration (), Функция итерации
    def Iteration(self):    	
        lim=100		# Предотвратить бесконечную итерацию
        while(lim>0):
            self.C=[] # Номер проверки очищен
            for j in range(self.X_count):     
                zj=0
                for i in range(self.b_count): # Проследить всю строку коэффициента j-го столбца и вычислить номер теста j-й переменной
                    zj+=self.bound[i][j]*self.z[self.B[i]]# Ограничить порядок базовых переменных B
                self.C.append(self.z[j]-zj) # Проверить номер, 'cj-zj'
            self.Check() # Оценка окончания итерации
            if self.flag>0: # Решение, завершите итерацию
                break
            else: # В противном случае базовая трансформация (вращение)
                self.pivot()
                lim-=1

        # Если есть оптимальное решение, вывести оптимальное решение и экстремальное значение целевой функции
        X=[0]*self.X_count
        count=0
        for i in self.B:
                X[i]=self.bound[count][self.X_count]
                count+=1
        Z=0
        for i in range(self.X_count):
            Z+=self.z[i]*X[i]
        if self.special:
            print("Нет приемлемого решения")
        elif self.flag==1:
            print("Есть единственное оптимальное решение",X,format(Z,'.2f'))  
        elif self.flag==0:
            print("Нет решения")

    #Check (), проверьте, является ли это оптимальным решением
    def Check(self):   	
        self.flag=1
        for i in range(self.b_count):
            if self.bound[i][self.X_count]<0:		# Если есть ограничения на правый конец константы отрицательный, продолжить итерацию
                self.flag=0
                break 

    #pivot (), преобразование базиса (вращение)
    def pivot(self):
        [i,j,main]=self.FindMain()  # Метод простоты: найдите главный элемент
        self.B[i]=j                 # Переменная подкачки в базовой переменной заменяется переменной подкачки
        for x in range(self.X_count+1):	# Преобразовать строку базовой переменной
            self.bound[i][x]=self.bound[i][x]/main
        for k in range(self.b_count):	# Преобразовать другие строки
            if k!=i:
                times=self.bound[k][j]  #несколько
                for t in range(self.X_count+1):
                    temp=self.bound[i][t]*times
                    self.bound[k][t]=self.bound[k][t]-temp

    def FindMain(self):                 # Найдите главный элемент в соответствии с правилом θ и определите заменяемые и заменяемые переменные
        matbound=np.mat(self.bound)
        if np.min(matbound[:,:-1])>=0:
            self.special=True
        bi=[]
        for i in range(self.b_count):
            bi.append(self.bound[i][self.X_count])
        iout=bi.index(min(bi))          #OK для замены переменных  
        Theta=[]                        #θ
        for j in range(self.X_count):
            if self.bound[iout][j]>=0 or self.C[j]==0:      # Дивиденд не равен 0, делитель должен быть меньше 0
                theta=float('inf')      # Дайте положительное бесконечное число, легко устранить
            else:
                theta=self.C[j]/self.bound[iout][j]
            Theta.append(theta)
        jin=Theta.index(min(Theta))      #OK для замены переменных
        main=self.bound[iout][jin]        
        return [iout,jin,main]
m=DualSimplex([0,0,0,0,0,-1,-1])
n=m.Iteration()
