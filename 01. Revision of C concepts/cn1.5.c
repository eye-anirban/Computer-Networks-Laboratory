/******************************************************************************

5. Continue Q3 . Define structure emp_info having data members ename , age. 
   Declare structure variable of emp_info and display all details of 3 employees.

*******************************************************************************/
#include <stdio.h>
struct emp_info{
    char ename[20] ;
    int age ;
};
struct emp{
    struct emp_info info ;
    int empid , basic_sal ;
    double da , hra , gross_sal ;
} ;

int main()
{
    struct emp e1 , e2 , e3 ;
    printf("Enter empid , basic_sal of 3 employees : ") ;
    scanf("%d%d%d%d%d%d", &e1.empid , &e1.basic_sal , &e2.empid , &e2.basic_sal , &e3.empid , &e3.basic_sal) ;
    printf("Enter name , age of 3 employees : ") ;
    scanf("%s%d%s%d%s%d" , &e1.info.ename , &e1.info.age , &e2.info.ename , &e2.info.age , &e3.info.ename , &e3.info.age) ;
    e1.da = e1.hra = 0.05 * e1.basic_sal ;  
    e2.da = e2.hra = 0.05 * e2.basic_sal ;
    e3.da = e3.hra = 0.05 * e3.basic_sal ;
    e1.gross_sal = e1.basic_sal + e1.da + e1.hra ;
    e2.gross_sal = e2.basic_sal + e2.da + e2.hra ;
    e3.gross_sal = e3.basic_sal + e3.da + e3.hra ;
    
    printf("\nEmployee 1 details :\nENAME = %s , AGE = %d , EMPID = %d , BASIC SAL = %d , DA = %lf , HRA = %lf , GROSS SAL = %lf" , e1.info.ename , e1.info.age , e1.empid , e1.basic_sal , e1.da , e1.hra , e1.gross_sal ) ;
    printf("\nEmployee 2 details :\nENAME = %s , AGE = %d , EMPID = %d , BASIC SAL = %d , DA = %lf , HRA = %lf , GROSS SAL = %lf" , e2.info.ename , e2.info.age , e2.empid , e2.basic_sal , e2.da , e2.hra , e2.gross_sal ) ;
    printf("\nEmployee 3 details :\nENAME = %s , AGE = %d , EMPID = %d , BASIC SAL = %d , DA = %lf , HRA = %lf , GROSS SAL = %lf" , e3.info.ename , e3.info.age , e3.empid , e3.basic_sal , e3.da , e3.hra , e3.gross_sal ) ;
    return 0;
}