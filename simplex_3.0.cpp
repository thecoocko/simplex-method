#include <iostream>
#include <cmath>
#include <vector>

class Simplex{

    private:
        int rows, cols;
        std::vector <std::vector<float> > A;
        std::vector<float> B;
        std::vector<float> C;

        float max_;

        bool isUnbounded;

    public:
        Simplex(std::vector <std::vector<float> > matrix,std::vector<float> b ,std::vector<float> c){
            max_ = 0;
            isUnbounded = false;
            rows = matrix.size();
            cols = matrix[0].size();
            A.resize( rows , vector<float>( cols , 0 ) );
            B.resize(b.size());
            C.resize(c.size());

            for(int i= 0;i<rows;i++){            
                for(int j= 0; j< cols;j++ ){
                    A[i][j] = matrix[i][j];

                }
            }

            for(int i=0; i< c.size() ;i++ ){    
                C[i] = c[i] ;
            }
            for(int i=0; i< b.size();i++ ){      
                B[i] = b[i];
            }
        }

        bool simplexAlgorithmCalculataion(){
            //Перевірка на оптимальність
            if(isOpt()==true){
			    return true;
            }

            //Шукаємо стовпець з дозволяючим елементом
            int EnablingColumn = findEnablingColumn();

            if(isUnbounded == true){
                std::cout<<"Error unbounded"<<std::endl;
			    return true;
            }

            //Шукаємо Рядок з дозволяючим елементом
            int EnablingRow = findEnablingRow(EnablingColumn);

            //Формуємо наступну таблицю
            doEnablingting(EnablingRow,EnablingColumn);

            return false;
        }

        bool isOpt(){
            bool isOptimal = false;
            int positveValueCount = 0;

            //Перевряємо чи є від'ємні елементи
            for(int i=0; i<C.size();i++){
                float value = C[i];
                if(value >= 0){
                    positveValueCount++;
                }
            }
            //Якщо позитивні, тотаблиця оптимальна
            if(positveValueCount == C.size()){
                isOptimal = true;
                print();
            }
            return isOptimal;
        }

        void doEnablingting(int EnablingRow, int EnablingColumn){

            float pivetValue = A[EnablingRow][EnablingColumn];

            float EnablingRowVals[cols];

            float EnablingColVals[rows];

            float rowNew[cols];

            max_ = max_ - (C[EnablingColumn]*(B[EnablingRow]/pivetValue));  
             //Отримуємо рядок с з дозволяючим елементом
             for(int i=0;i<cols;i++){
                EnablingRowVals[i] = A[EnablingRow][i];
             }
             //Отримуємо стовпець с з дозволяючим елементом
             for(int j=0;j<rows;j++){
                EnablingColVals[j] = A[j][EnablingColumn];
            }

            //Розраховуємо значення дозволяючого рядку
             for(int k=0;k<cols;k++){
                rowNew[k] = EnablingRowVals[k]/pivetValue;
             }

            B[EnablingRow] = B[EnablingRow]/pivetValue;


             //Обраховуємо інші значення масиву А
             for(int m=0;m<rows;m++){
                //Ігноруємо дозволяючий рядок
                if(m !=EnablingRow){
                    for(int p=0;p<cols;p++){
                        float multiplyValue = EnablingColVals[m];
                        A[m][p] = A[m][p] - (multiplyValue*rowNew[p]);
                    }

                }
             }

            //Розраховуємо значення для масиву В
            for(int i=0;i<B.size();i++){
                if(i != EnablingRow){

                        float multiplyValue = EnablingColVals[i];
                        B[i] = B[i] - (multiplyValue*B[EnablingRow]);

                }
            }
                //Найшменший коефіцієнт з значеньф-ції
                float multiplyValue = C[EnablingColumn];
                //Розраховуємо значення для коефіцієнту
                 for(int i=0;i<C.size();i++){
                    C[i] = C[i] - (multiplyValue*rowNew[i]);

                }


             //заміняємо рядки обчисленими значеннями
             for(int i=0;i<cols;i++){
                A[EnablingRow][i] = rowNew[i];
             }


        }

        //Печатаємо наш масив
        void print(){
            for(int i=0; i<rows;i++){
                for(int j=0;j<cols;j++){
                    std::cout<<A[i][j] <<" ";
                }
                std::cout<<""<<std::endl;
            }
            std::cout<<""<<std::endl;
        }

        //Шукаємо мінімум в масиві значень ф-ції
        int findEnablingColumn(){

            int position = 0;
            float minm = C[0];



            for(int i=1;i<C.size();i++){
                if(C[i]<minm){
                    minm = C[i];
                    position = i;
                }
            }

            return position;

        }

        //Шукаємо рядок з дозволяючим елементом
        int findEnablingRow(int EnablingColumn){
            float positiveValues[rows];
            std::vector<float> result(rows,0);
            int negativeValueCount = 0;

            for(int i=0;i<rows;i++){
                if(A[i][EnablingColumn]>0){
                    positiveValues[i] = A[i][EnablingColumn];
                }
                else{
                    positiveValues[i]=0;
                    negativeValueCount+=1;
                }
            }
            //Перевіряємо чи є від'ємні значення
            if(negativeValueCount==rows){
                isUnbounded = true;
            }
            else{
                for(int i=0;i<rows;i++){
                    float value = positiveValues[i];
                    if(value>0){
                        result[i] = B[i]/value;

                    }
                    else{
                        result[i] = 0;
                    }
                }
            }
            //Знаходимо мінімум в масиві В
            float min_ = 99999999;
            int position = 0;
            for(int i=0;i<sizeof(result)/sizeof(result[0]);i++){
                if(result[i]>0){
                    if(result[i]<min_){
                        min_ = result[i];
                        position = i;
                    }
                }
            }
            return position;
        }

        void CalculateSimplex(){
            bool end = false;

            std::cout<<"initial array(Not optimal)"<<std::endl;
            print();

            std::cout<<" "<<std::endl;
            std::cout<<"final array(Optimal solution)"<<std::endl;
            while(!end){

                bool result = simplexAlgorithmCalculataion();

                if(result==true){
                    end = true;
                    }
            }
            std::cout<<"Answers for the Constraints of variables"<<std::endl;

            for(int i=0;i< A.size(); i++){   //Витягуємо з масив В значення змінних
                int count0 = 0;
                int index = 0;
                for(int j=0; j< rows; j++){
                    if(A[j][i]==0.0){
                        count0 += 1;
                    }
                    else if(A[j][i]==1){
                        index = j;
                    }
                }

                if(count0 == rows -1 ){

                    std::cout<<"variable"<<index+1<<": "<<B[index]<<std::endl;  //Витягуємо з масив В значення змінних
                }
                else{
                    std::cout<<"variable"<<index+1<<": "<<0<<std::endl;}
            }
           std::cout<<""<<std::endl;
           std::cout<<"maximum value: "<<max_<<std::endl;  //виводить максимальне значення
        }
};

int main()
{
     
    int colSizeA=6;  //Задаємо кількість стовпців
    int rowSizeA = 4;  //Задаємо кількість рядків
    float C[]= {-1,-1,0,0,0,0};  //Значення ф-ції
    float B[]={1,14,13,12};  // Вільні члени
    float a[4][6] = {{ -3,2,1,0,0,0},{ 1,2,0,1,0,0},{ 3,-1,0,0,0,1}}; //Ініціалізуємо масив
        std::vector <std::vector<float> > vec2D(rowSizeA, std::vector<float>(colSizeA, 0));
        std::vector<float> b(rowSizeA,0);
        std::vector<float> c(colSizeA,0);

       for(int i=0;i<rowSizeA;i++){         //Створюємо вектор для нашого масиву
            for(int j=0; j<colSizeA;j++){
                vec2D[i][j] = a[i][j];
            }
       }

       for(int i=0;i<rowSizeA;i++){
            b[i] = B[i];
       }

        for(int i=0;i<colSizeA;i++){
            c[i] = C[i];
       }
      // Створюємо екземпляри класу 
      Simplex simplex(vec2D,b,c);
      simplex.CalculateSimplex();
    return 0;
}