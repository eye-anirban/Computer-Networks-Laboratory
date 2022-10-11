/******************************************************************************

3. Define a structure emp having data members empid , basic_sal , da , hra and gross_sal .
   Consider da and hra to be each 5% of basic salary .
   Input details of 3 employees and display all details of each one of them.

*******************************************************************************/
#include <stdio.h>

struct emp{
    int empid , basic_sal ;
    double da , hra , gross_sal ;
} ;

int main()
{
    struct emp e1 , e2 , e3 ;
    printf("Enter empid , basic_sal of 3 employees : ") ;
    scanf("%d%d%d%d%d%d", &e1.empid , &e1.basic_sal , &e2.empid , &e2.basic_sal , &e3.empid , &e3.basic_sal) ;
    e1.da = e1.hra = 0.05 * e1.basic_sal ;  
    e2.da = e2.hra = 0.05 * e2.basic_sal ;
    e3.da = e3.hra = 0.05 * e3.basic_sal ;
    e1.gross_sal = e1.basic_sal + e1.da + e1.hra ;
    e2.gross_sal = e2.basic_sal + e2.da + e2.hra ;
    e3.gross_sal = e3.basic_sal + e3.da + e3.hra ;
    
    printf("\nEmployee 1 details :\nEMPID = %d , BASIC SAL = %d , DA = %lf , HRA = %lf , GROSS SAL = %lf" , e1.empid , e1.basic_sal , e1.da , e1.hra , e1.gross_sal ) ;
    printf("\nEmployee 2 details :\nEMPID = %d , BASIC SAL = %d , DA = %lf , HRA = %lf , GROSS SAL = %lf" , e2.empid , e2.basic_sal , e2.da , e2.hra , e2.gross_sal ) ;
    printf("\nEmployee 3 details :\nEMPID = %d , BASIC SAL = %d , DA = %lf , HRA = %lf , GROSS SAL = %lf" , e3.empid , e3.basic_sal , e3.da , e3.hra , e3.gross_sal ) ;
    return 0;
}
