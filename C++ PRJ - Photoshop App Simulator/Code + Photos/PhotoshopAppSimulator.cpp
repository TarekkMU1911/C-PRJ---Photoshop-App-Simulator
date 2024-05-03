/*
Name         : Tarek Muhammed Abdel-hamid
ID           : 20220170 .
course       : CS213 : Object Oriented Programming (Programming 2)
Instructor   : Dr.Mohammad El-Ramly
Date         : 18/9/2023
Mail         : tarekkmuhammed1911@gmail.com
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include "bmplib.h"

using namespace std;
unsigned char image[SIZE][SIZE];

// A functionn used to load another photo in merge2photos function :
unsigned char image2[SIZE][SIZE];

// A supporter 2d array used in rotation function :
unsigned char rot[SIZE][SIZE];

// A supporter 2d array in DetectEdges function :
unsigned char SupImage[SIZE][SIZE];

// A supporter 2d array in Enlarge function :
unsigned char Sup2Image[SIZE][SIZE];

void loadImage();
void saveImage();
void ChooseEffect();
void KeepEditing();

int main()
{ // the sequence of the functions in main is simulating to photoshop applications :

    // First step :
    loadImage();
    // Second Step ( The main process )
    ChooseEffect();
    // Third step : to check if the user want to keep editing
    KeepEditing () ;

    return 0;
}

//_____________________________________________________________________________________________________________________
// A function to load the image that I am going to edit it :
void loadImage()
{
    char imageFileName[100];

    cout << "Enter the source image file name :  ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_____________________________________________________________________________________________________________________
// A function to load the second image that I am going to merge it with the first one :
void loadImage2()
{
    char image2FileName[100];

    cout << "Enter the source image file name  you want to merge it  with :  ";
    cin >> image2FileName;

    strcat(image2FileName, ".bmp");
    readGSBMP(image2FileName, image2);
}

//_____________________________________________________________________________________________________________________
// A function to save the image after editing :
void saveImage()
{
    char imageFileName[100];

    cout << "Enter the target image file name : ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
//_____________________________________________________________________________________________________________________
// filters:
/* Here w searched for  every pixel by the nested loop and based on its pixles we chose to make it black or white
 if it wase bigger than 120 we will make it white  but if it was less than or equal 120 it turns into black pixels by
 the nested loop */
void BlackandWhite()
{
    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            if (image[i][j] > 120)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
//_____________________________________________________________________________________________________________________
void Invert()
/*
 In invert effect we make the dark and specifically black pixels white , and for the other pixels we make it lighter .
 */
{
    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            image[i][j] = 255 - image[i][j];
        }
        // to make every pixel has its special degree
    }
}
//_____________________________________________________________________________________________________________________
/* In this function we created a function to load the second image , and by the nested loop we added the pixels of
 the first image to the second one and make the sum of thier brightness divided by 2 to make both of them clear in
 the same time */
void Merge2photos()
{
    loadImage2();

    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            image[j][i] = ((image[j][i] + image2[j][i]) / 2);
        }
    }
}
//_____________________________________________________________________________________________________________________
/* based on the tybe of flip if we said it was vertical the number of the row will not change , the only change is
  on the number of the column ( **we used the photo as a matrix 256*256** ) and we used the inner loop to stop
  after 178 columns because the inner loop works on two pixles in the same time the pixel [j][i] and the opposite
  one ( the pixel [j][255-i] ) .
   and the same on the horizontal flip but we change the rows not the columns and make the outer loop to stop after 178
   rows . */
void Flip()
{
    cout << "Choose the type of flip: (1)Vertical   (2) Horizontal\n";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int i = 0; i < SIZE / 2; i++)
            {

                int sub = image[j][i];
                image[j][i] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = sub;
            }
        }
    }
    else
    {
        for (int j = 0; j < SIZE / 2; j++)
        {
            for (int i = 0; i < SIZE; i++)
            {

                int sub = image[j][i];
                image[j][i] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = sub;
            }
        }
    }
}

//_____________________________________________________________________________________________________________________
/*like the same filter we tried to see what changes in the rotating in 180 & 90 degree
 ( **Unfortunately I can't use the same concept in 270 degrees because it was so hard to make it rotate -90
 so I used the traditional idea and used the block of code of rotate 90 degrees three times** )
 and we used a supporter 2d array (rot ) to store the values after rotation ,
 */
void Rotate()
{
    cout << "Choose the degree of rotation\n "
            " 90  -  180  -  270 \n"
            "The degree I want for rotation is :  ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 90:
    {

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                rot[i][j] = image[SIZE - j - 1][i];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = rot[i][j];
            }
        }
        break;
    }

    case 180:
    {

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                // Both of number of rows and columns are changing in every loop
                rot[i][j] = image[SIZE - i - 1][SIZE - j - 1];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = rot[i][j];
            }
        }
        break;
    }

    case 270:
    {
        //(for loop) to repeat the 90 degree rotation 3 times :
        for (int x = 0; x <= 2; x++)
        {

            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    rot[i][j] = image[SIZE - j - 1][i];
                }
            }
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j] = rot[i][j];
                }
            }
        }
        break;
    }

    default:
    {
        cout << "The choice is not available , please choose the degree you want to rotate the by : \n";
        Rotate();
    }
    }
}
//_____________________________________________________________________________________________________________________
/* To mange or change the brightness we have to know , we want to make it darker or lighter :
 to make it darker :
 we have to divide the value that the pixel carry by 2 .
 but to make it lighter :
 we have a small problem , it is if the pixel after add the was bigger than 255?
 so we make it by the relation on the line ( in the inner for loop in else )
 to make the high brightness pixels raie its value to 255 not more .
 */
void Brightness()
{
    cout << "Do you want to make it : (1) Darker      (2) Lighter .";
    int choice;
    cout << "Your choice is number : ";
    cin >> choice;
    if (choice == 1)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int i = 0; i < SIZE; i++)
            {
                image[j][i] -= (image[j][i] / 2);
            }
        }
    }
    else
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int i = 0; i < SIZE; i++)
            {
                // to limit the value of each pixel :
                image[j][i] += abs(image[j][i] - 255) / 2;
            }
        }
    }
}
//_____________________________________________________________________________________________________________________
/*
 This function detect the edges of the contents of the photo by  checking the enquality between the pixel
 and the next pixel in the row an in the column and if one condition from the past 2 conditions was true
 the second loop make this pixel black in the supImage ( full white image ) then the last two make image
 contains the image after editing .
 */
void DetectEdges()
{
    BlackandWhite();
    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0 ; i < SIZE; i++)
        {
          SupImage[j][i]=255;
        }
    }



        for (int j = 0; j < SIZE; j++)
        {
            for (int i = 0; i < SIZE; i++)
            {

                if (image[j][i + 1] != image[j][i] || image[j+1][i] != image[j][i] )
                {
                    SupImage[j][i] = 0;
                }
            }
        }

            for (int j = 0; j < SIZE; j++) {
                for (int i = 0; i < SIZE; i++) {
                    image[j][i] = SupImage[j][i];
                }
            }


}

//_____________________________________________________________________________________________________________________

/*
 This function enlarges a selected quadrant of the image.
 The user chooses a quadrant (upper left, upper right, lower right, or lower left), 
 the pixels in that quadrant are replicated to fill the corresponding area.
*/

void Enlarge()
{
    cout<<"Which part you want to enlarge : \n";
    cout<<" 1-Upper left    2-Upper right   3-Lower right   4-Lower left \n"
          " I choose : ";
    int choice ;
    cin >> choice ;

    switch (choice)
    {
        case 1:
        {

            for (int i = 0; i < SIZE / 2; i++)
            {

                for (int j = 0; j < SIZE / 2; j++)
                {

                    SupImage[i * 2][j * 2] = image[i][j];
                    SupImage[i * 2][j * 2 + 1] = image[i][j];
                    SupImage[i * 2 + 1][j * 2] = image[i][j];
                    SupImage[i * 2 + 1][j * 2 + 1] = image[i][j];
                }
            }


            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j] = SupImage[i][j];
                }
            }

            break;
        }

        case 2:
        {

            for (int i = 0; i < SIZE / 2; i++)
            {

                for (int j = SIZE / 2; j < SIZE; j++)
                {

                    SupImage[i * 2][j * 2 - SIZE] = image[i][j];
                    SupImage[i * 2][j * 2 + 1 - SIZE] = image[i][j];
                    SupImage[i * 2 + 1][j * 2 - SIZE] = image[i][j];
                    SupImage[i * 2 + 1][j * 2 + 1 - SIZE] = image[i][j];
                }
            }


            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j] = SupImage[i][j];
                }
            }

            break;
        }

        case 3:
        {

            for (int i = SIZE / 2; i < SIZE; i++)
            {

                for (int j = SIZE / 2; j < SIZE; j++)
                {

                    SupImage[i * 2 - SIZE][j * 2 - SIZE] = image[i][j];
                    SupImage[i * 2 - SIZE][j * 2 + 1 - SIZE] = image[i][j];
                    SupImage[i * 2 + 1 - SIZE][j * 2 - SIZE] = image[i][j];
                    SupImage[i * 2 + 1 - SIZE][j * 2 + 1 - SIZE] = image[i][j];
                }
            }


            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j] = SupImage[i][j];
                }
            }

            break;
        }

        case 4:
        {

            for (int i = SIZE / 2; i < SIZE; i++)
            {

                for (int j = 0; j < SIZE / 2; j++)
                {

                    SupImage[i * 2 - SIZE][j * 2] = image[i][j];
                    SupImage[i * 2 - SIZE][j * 2 + 1] = image[i][j];
                    SupImage[i * 2 + 1 - SIZE][j * 2] = image[i][j];
                    SupImage[i * 2 + 1 - SIZE][j * 2 + 1] = image[i][j];
                }
            }


            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j] = SupImage[i][j];
                }
            }

            break;
        }

        default:
            cout << "Invalid choice. Please choose between 1 to 4.\n";
    }
}
//_____________________________________________________________________________________________________________________
/*
 This function applies a blur effect to the image by averaging the pixel values in a 3x3 neighborhood.
 It creates a new image array to avoid overwriting original pixel values during computation.
*/

void Blur() {
    unsigned char newImage[SIZE][SIZE];

    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            int sum = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    sum += image[i + x][j + y];
                }
            }
            newImage[i][j] = sum / 9;
        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}
//____________________________________________________________________________________________________________________
/*
 A summary to to this long code , I stored each qurtile from the main image in 127 * 127 image
 then I made the user enter 4 variables by the sequence he want to make the image with , then
 I store each qurtile in his new place by switch cases .
 */
void Shuffle() {
    int n1,n2,n3,n4;
    cout <<"Please , enter the sequence of the parts  : \n";
    cin>>n1>>n2>>n3>>n4;
    if (n1 > 4 || n2 > 4 || n3 > 4 || n3 > 4){
        cout << "invalid values Please , enter the sequence of the parts  ";

                cin >>
            n1 >> n2 >> n3 >> n4;
    }else{

    unsigned char upleft[SIZE / 2][SIZE / 2];
    unsigned char upright[SIZE/2][SIZE/2];
    unsigned char downleft[SIZE/2][SIZE/2];
    unsigned char downright[SIZE/2][SIZE/2];


    // Copy parts of the image into corresponding arrays 

        for (int i = 0; i < SIZE / 2; i++)
    {
            for (int j = 0; j < SIZE / 2; j++)
            {
                upleft[i][j] = image[i][j];
                upright[i][j] = image[i][j + SIZE / 2];
                downleft[i][j] = image[i + SIZE / 2][j];
                downright[i][j] = image[i + SIZE / 2][j + SIZE / 2];
            }
    }

     switch(n1)
     {
         case 1: {
             for (int i = 0; i < SIZE / 2; i++) {
                 for (int j = 0;  j<SIZE / 2; j++) {
                     image[i][j] = upleft[i][j];
                 }
             }
             break;
         }
         case 2 :
         {
             for (int i = 0; i < SIZE / 2; i++) {
                 for (int j = 0;  j<SIZE / 2; j++) {
                     image[i][j] = upright[i][j];
                 }
             }
             break;

         }

         case 3 :
         {
             for (int i = 0; i < SIZE / 2; i++) {
                 for (int j = 0;  j<SIZE / 2; j++) {
                     image[i][j] = downleft[i][j];
                 }
             }
             break;

         }
         case 4 :
         {
             for (int i = 0; i < SIZE / 2; i++) {
                 for (int j = 0;  j<SIZE / 2; j++) {
                     image[i][j] = downright[i][j];
                 }
             }
             break;

         }
     }


    switch(n2)
    {
        case 1: {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j+SIZE/2] = upleft[i][j];
                }
            }
            break;
        }
        case 2 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j+SIZE/2] = upright[i][j];
                }
            }
            break;

        }

        case 3 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j+SIZE/2] = downleft[i][j];
                }
            }
            break;

        }
        case 4 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j+SIZE/2] = downright[i][j];
                }
            }
            break;

        }
    }


    switch(n3)
    {
        case 1: {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j] = upleft[i][j];
                }
            }
            break;
        }
        case 2 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j] = upright[i][j];
                }
            }
            break;

        }

        case 3 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j] = downleft[i][j];
                }
            }
            break;

        }
        case 4 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j] = downright[i][j];
                }
            }
            break;

        }
    }




    switch(n4)
    {
        case 1: {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j+SIZE/2] = upleft[i][j];
                }
            }
            break;
        }
        case 2 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j+SIZE/2] = upright[i][j];
                }
            }
            break;

        }

        case 3 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j+SIZE/2] = downleft[i][j];
                }
            }
            break;

        }
        case 4 :
        {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j<SIZE / 2; j++) {
                    image[i+SIZE/2][j+SIZE/2] = downright[i][j];
                }
            }
            break;

        }
      
    }



}
}

//____________________________________________________________________________________________________________________


/*This function performs mirroring on the image based on user's choice,
The user can choose between four types of mirroring{Right, Left, Up, or Down},
The function uses nested loops to iterate over the image pixels and apply the mirroring operation.
*/


void Mirroring () {
    int choice;
    cout << "Please , choose the type of the mirroring type :\n";
    cout << "1-Right   2-Left    3-Up   4-Down \n";
    cin >> choice;

    switch (choice) {
        case 1 : {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    image[i][j] = image[i][SIZE - j - 1];
                }
            }
            break;
        }
        case 2: {
            for (int i = 0; i < SIZE; i++) {
                for (int j = SIZE / 2; j < SIZE; j++) {
                    image[i][j] = image[i][SIZE - j - 1];

                }
            }
            break;
        }

        case 3 : {
            for (int i = SIZE / 2; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image[i][j] = image[SIZE - i - 1][j];

                }
            }
            break;
        }

        case 4 : {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image[i][j] = image[SIZE - i - 1][j];
                }
            }
            break;
        }
        default : {
            cout << "The choice is not available here , Choose again .\n";
            Mirroring();
        }
    }
}
//____________________________________________________________________________________________________________________

/* This function crops a rectangular area from the image defined by coordinate
 with dimensions. It creates a new image with the specified dimensions
 and copies the pixels from the original image that fall within the cropping area,
 If the cropping area exceeds the image boundaries a warning message is displayed.
*/

void Crop(int x, int y, int l, int w)
{
    unsigned char newImage[SIZE][SIZE];
    if (x < 0 || y < 0 || x + l >= SIZE || y + w >= SIZE)
    {

        cout << "the cropped area will exceed image boundaries ." << endl;
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i >= x && i < x + l && j >= y && j < y + w)
            {
                newImage[i][j] = image[i][j];
            } else {
                newImage[i][j] = 255;
            }
        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}
//____________________________________________________________________________________________________________________


/*This function performs shrinking on the image based on user-defined size options,
 The user can choose between half, third, or quarter shrinking.
 It achieves shrinking by sampling pixels from the original image and placing them at intervals in the resulting image.
*/

void Shrink ()
{

    int size;
    cout <<"Please , enter the type of the shrinking : \n"
           "1-Half shrinking   2-Third shrinking   3-Qurtile shrinking \n"
           " My choice is : ";
    cin >> size;
    //I used switch cases too much , Let's make it with if condition to make difference .
    if(size == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image2[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 255;
            }

        }
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = image2[i * 2][j * 2];
            }

        }}
    else if( size ==2){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image2[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 255;
            }

        }
        for (int i = 0; i < SIZE / 3; i++) {
            for (int j = 0; j < SIZE / 3; j++) {
                image[i][j] = image2[i * 3][j * 3];
            }
        }
    }
    else if( size ==3){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image2[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 255;
            }

        }
        for (int i = 0; i < SIZE / 4; i++) {
            for (int j = 0; j < SIZE / 4; j++) {
                image[i][j] = image2[i * 4][j * 4];
            }
        }
    }
}
//____________________________________________________________________________________________________________________
//the skew function includes the both types of skewing ( virtical && Horizontal )

/* This function applies skewing to the image based on user input: horizontal or vertical skewing,
 It first initializes auxiliary image arrays and prompts the user for skewing degrees,
 The pixels are then rearranged to achieve the desired skewing effect using trigonometric calculations.
*/
    void Skew()
{
    cout << "Please , enter the type of the skewing : 1-Horizontal  2-Virtical \n";
    cout <<"I choose the the choice number : ";
    int choice ; cin >> choice ;
    switch (choice)
    {
        case 1 :
        {
            unsigned char image2[SIZE][SIZE];
            unsigned char image3[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image2[i][j] = 255;
                    image3[i][j] = 255;
                }
            }

            cout << "Please enter degree to skew Up : ";
            double degree;
            cin >> degree;
            double rad = degree * (M_PI / 180.0);
            double tangent = tan(rad);
            int x = 256 / (1 + (1 / tangent));

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image2[(i*x)/SIZE][j] = image[i][j];
                }
            }

            double begin= 256.0 - x;
            double move = begin / 256.0;
            for (int i = 0; i < SIZE; i++) {
                for (int j = int(begin); j < begin+x; j++){
                    image3[j][i]=image2[int(j-begin)][i];
                }
                begin-=move;
            }
            for(int i = 0 ; i < SIZE ;i++)
            {
                for(int  j = 0 ; j < SIZE ; j++)
                {
                    image[i][j] = image3[i][j];
                }
            }
            break ;
        }

        case 2 :
        {

                unsigned char image2[SIZE][SIZE];
                unsigned char image3[SIZE][SIZE];
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        image2[i][j] = 255;
                        image3[i][j] = 255;
                    }
                }

                cout << "Please enter degree to skew Up : ";
                double degree;
                cin >> degree;
                double rad = degree * (M_PI / 180.0);
                double tangent = tan(rad);
                int x = 256 / (1 + (1 / tangent));

                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        image2[i][(j*x)/SIZE] = image[i][j];
                    }
                }

                double begin= 256.0 - x;
                double move = begin / 256.0;
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++){
                        image3[i][j+int(begin)]=image2[i][j];
                    }
                    begin-=move;
                }
                for(int i = 0 ; i < SIZE ;i++)
                {
                    for(int  j = 0 ; j < SIZE ; j++)
                    {
                        image[i][j] = image3[i][j];
                    }
                }
                break ;


        }
        default :
        {
            cout<<"You entered wrong choie , please try again .\n";
            Skew();
        }
    }

}
//____________________________________________________________________________________________________________________
// a function to choose the effect :

void ChooseEffect()
{
    int num;
    cout << "Please , enter the number of the effect you want to apply :\n";
    cout << "1-Black and white .\n2-Invert Image.\n3-Merge two photos.\n4-Flip image .\n5-Rotate .\n6-Brightness ."
            ".\n7-Detect Edges .\n8-Enlarge .\n9-Blur .\n10-Shuffle\n11-Mirroring\n12-Crop\n13-Shrinking\n14-Skewing\n"
            "(In case you want to leave the program enter 15) \n"
            "The effect I want to apply is effect number : \n ";
    cin >> num;

    switch (num)
    {
    case 1:
    {
        BlackandWhite();
        break;
    }

    case 2:
    {
        Invert();
        break;
    }

    case 3:
    {
        Merge2photos();
        break;
    }
    case 4:
    {
        Flip();
        break;
    }
    case 5:
    {
        Rotate();
        break;
    }
    case 6:
    {
        Brightness();
        break;
    }
    case 7 :
    {
        DetectEdges();
        break;
    }
    case 8 :
    {
        Enlarge();
        break;
    }
    case 9 :
    {
        int i{};
      do{ Blur(); i++;}
      while(i<6);

      break;
    }
    case 10:
    {
        Shuffle();
        break;
    }
    case 11 :
    {
        Mirroring();
        break;
    }
    case 12 :
    {

        int x , y , l , w ;
        cout<<"Please , enter the position then the legnth and finally the width .\n";
        cin >> x >> y;
        cout <<"Set the boundries (Length then width ) : \n";
        cin>>l>>w;
        Crop(x,y,l,w);
        break;
    }
    case 13 :
    {
        Shrink();
        break;
    }
    case 14 :
    {
        Skew();
        break;
    }
    case 15:
    {
        break;
    }
    // to force the user to insert numbers from the list not any another options :
    default:
    {
        cout << "The choice is not available , please choose the effect you want from the list .\n";
        ChooseEffect();
    }
    }
}

//_____________________________________________________________________________________________________________________
void KeepEditing ()
{
 cout<<"Do you want to do some thing else in the photo ?\n";
 cout<<"(1) Yes                                  (2) No\n";
 int choice ;
 cout <<"I want the choice number : ";
 cin>>choice ;
 switch(choice)
 {
     case 1 :

     {
         ChooseEffect();
         KeepEditing ();
         break;
     }
     case 2 :
     {
         cout <<"Thank you for your time , Have a Good day !\n " ;
         saveImage();
         break;

     }
     default :
     {
         cout<<"This is unavailable choice , the image is saved !\n";
         saveImage();
         break;
     }
 }


}
//_____________________________________________________________________________________________________________________
                                            /*         Free Palestine 
                                                  >> ELHAMDULELAH FOREVER <<
                                            */
