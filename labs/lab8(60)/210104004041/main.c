#include <stdio.h>
#include <math.h>

//part1
typedef struct 
{
    double array[3][3];
    double determinant;
}matrix;

void print_matrix(matrix initial_matrix);
void inverse_matrix(matrix* initial_matrix, matrix* inverted_matrix);
void determinant_of_matrix(matrix* initial_matrix);


typedef struct 
{
    double x;
    double y;
    double z;

}vector;

double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec);


typedef struct
{
    double a;
    double b;
    double c;
    double d;

}polynomial;

typedef struct
{
    double a;
    double b;
    double c;
    double d;

}third_order_polynomial;




polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b);



int main(){

    matrix the_matrix;
    matrix inversed_matrix;
    double input;

    for (int i = 0; i < 3; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            printf("enter for the matrix:");
            scanf("%lf",&input);

            the_matrix.array[i][x]=input;
        }   
        
    }
    
    print_matrix(the_matrix);
    inverse_matrix(&the_matrix,&inversed_matrix);
    print_matrix(inversed_matrix);


    vector vect1;
    vect1.x= 1;
    vect1.y= 2;
    vect1.z= 3;

    vector vect2;
    vect2.x= 3;
    vect2.y= 2;
    vect2.z= 1;

    vector outputvec;

    find_orthogonal(vect1,vect2,&outputvec);

    printf("Output_vector:\n");
    printf("%lf %lf %lf \n",outputvec.x,outputvec.y,outputvec.z);

    third_order_polynomial pol1={1,5,2,1};
    third_order_polynomial pol2={1,2,3,4};


    //polynomial new_pol= get_integral(pol1,pol2,2,5);

    return 0;
}


void print_matrix(matrix initial_matrix){

    for (int i = 0; i < 3; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            printf("%12.4lf",initial_matrix.array[i][x]);

        }   
        printf("\n");
    }



}

void inverse_matrix(matrix* initial_matrix, matrix* inverted_matrix){

    determinant_of_matrix(initial_matrix);

    //printf("%lf",initial_matrix->determinant);
    
    if (initial_matrix->determinant!=0)
    {
        printf("Determinant:%lf\n\n",initial_matrix->determinant);

        inverted_matrix->array[0][0] = (initial_matrix->array[1][1] * initial_matrix->array[2][2] - initial_matrix->array[1][2] * initial_matrix->array[2][1]) / initial_matrix->determinant;
        inverted_matrix->array[0][1] = (initial_matrix->array[0][2] * initial_matrix->array[2][1] - initial_matrix->array[0][1] * initial_matrix->array[2][2]) / initial_matrix->determinant;
        inverted_matrix->array[0][2] = (initial_matrix->array[0][1] * initial_matrix->array[1][2] - initial_matrix->array[0][2] * initial_matrix->array[1][1]) / initial_matrix->determinant;
        inverted_matrix->array[1][0] = (initial_matrix->array[1][2] * initial_matrix->array[2][0] - initial_matrix->array[1][0] * initial_matrix->array[2][2]) / initial_matrix->determinant;
        inverted_matrix->array[1][1] = (initial_matrix->array[0][0] * initial_matrix->array[2][2] - initial_matrix->array[0][2] * initial_matrix->array[2][0]) / initial_matrix->determinant;
        inverted_matrix->array[1][2] = (initial_matrix->array[0][2] * initial_matrix->array[1][0] - initial_matrix->array[0][0] * initial_matrix->array[1][2]) / initial_matrix->determinant;
        inverted_matrix->array[2][0] = (initial_matrix->array[1][0] * initial_matrix->array[2][1] - initial_matrix->array[1][1] * initial_matrix->array[2][0]) / initial_matrix->determinant;
        inverted_matrix->array[2][1] = (initial_matrix->array[0][1] * initial_matrix->array[2][0] - initial_matrix->array[0][0] * initial_matrix->array[2][1]) / initial_matrix->determinant;
        inverted_matrix->array[2][2] = (initial_matrix->array[0][0] * initial_matrix->array[1][1] - initial_matrix->array[0][1] * initial_matrix->array[1][0]) / initial_matrix->determinant;
        
    }else{
        printf("Determinant is equal to 0!!\n");
    }

}

void determinant_of_matrix(matrix* initial_matrix){

    double (*local_array)[3]= initial_matrix->array;
    double determinant=0;

    determinant= determinant + (local_array[0][0]* ( (local_array[1][1]*local_array[2][2])-(local_array[1][2]*local_array[2][1])));
    
    determinant= determinant - (local_array[0][1]* ( (local_array[1][0]*local_array[2][2])-(local_array[1][2]*local_array[2][0])));
    
    determinant= determinant + (local_array[0][2]* ( (local_array[1][0]*local_array[2][1])-(local_array[1][1]*local_array[2][0])));
    
    initial_matrix->determinant=determinant;

}


double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec){

    double vec1_mag= sqrt((vec_1.x*vec_1.x) + (vec_1.y*vec_1.y) +(vec_1.z*vec_1.z));
    double vec2_mag= sqrt((vec_2.x*vec_2.x) + (vec_2.y*vec_2.y) +(vec_2.z*vec_2.z));
    
    double dot_product= (vec_1.x*vec_2.x)+(vec_1.y*vec_2.y)+(vec_1.z*vec_2.z);
    
    double angle_payda= vec1_mag*vec2_mag;

    double angle= acosh(1+(dot_product/angle_payda));
    
    double pi= 3.14;

    double degree_angle= angle *(180/pi);

    printf("\n\n%lf degrees\n\n",degree_angle);


    output_vec->x=vec_1.y* vec_2.z-vec_1.z* vec_2.y;
    output_vec->y=vec_1.z* vec_2.x- vec_1.x* vec_2.z;
    output_vec->z=vec_1.x* vec_2.y-vec_1.y* vec_2.x;




}


polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b){

    polynomial polynom;

    polynom.a= p1.a*(p2.a+p2.b+p2.c+p2.d);
    polynom.b= p1.b*(p2.a+p2.b+p2.c+p2.d);
    polynom.c= p1.c*(p2.a+p2.b+p2.c+p2.d);
    polynom.d= p1.d*(p2.a+p2.b+p2.c+p2.d);


    // 3x^3 + 5x^2 + 4x + 9

    polynom.a= polynom.a/4;
    polynom.b= polynom.b/3;
    polynom.c= polynom.c/2;
    polynom.d= 0;

    double integral;

    integral= (polynom.a* b*b*b*b*b*b*b) + (polynom.b* b*b*b) + (polynom.c* b*b) + (polynom.d* b);
    integral= integral- ((polynom.a* a*a*a*a)+(polynom.a* a*a*a)+(polynom.a* a*a)+(polynom.a* a));

    printf("%.4lf integral result.\n",integral);

    return polynom;

}

void coofficient_calculator(third_order_polynomial p1,third_order_polynomial p2,third_order_polynomial *result){

    double a;


}

