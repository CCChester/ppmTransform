#include <string>
#include <iostream>
using namespace std;

/*********** Pixel **********
     Purpose: Define a Pixel struct, which contains
              3 integer, r represents red color,
              g represents green color,
              b represents blue color.
     Returns: No returns.
***********************************/

struct Pixel {
    unsigned int r;  // value for red
    unsigned int g;  // value or green
    unsigned int b;  // value for blue
};

/*********** PpmArray **********
     Purpose: Define a PpmArray struct, which contains
              size, capacity, width, height, of this 
              PpmArray, and a pointer to a struct Pixel.
     Returns: No returns.
***********************************/

struct PpmArray {
    int size;      // number of pixels the array currently holds
    int capacity;  // number of pixels the array could hold, given current
    // memory allocation to pixels
    int width;     // width of image
    int height;    // height of image
    Pixel *pixels;
};

/*********** flipHorizontal **********
      Purpose: An ppmarray, do the flip function about 
               this array. flip horizontally. 
      Returns: Null.
***********************************/

void flipHorizontal(PpmArray &ppm){
    int tempr = 0;     //initialize a temp to represents red color.
    int tempg = 0;     //initialize a temp to represents green color.
    int tempb = 0;     //initialize a temp to represents blue color.
    int length = ppm.width - 1;
    int first = 0;     //the postion from the first to last.
    int last = length;    //the position from the last to the first.
    while (last < ppm.size){
        //loop to do flip function
        while (last > first){
            //loop to do flip funciton
            tempr = ppm.pixels[first].r;    //let the first pixel put into temp
            tempg = ppm.pixels[first].g;
            tempb = ppm.pixels[first].b;
            ppm.pixels[first].r = ppm.pixels[last].r;  //last pixel put into first
            ppm.pixels[first].g = ppm.pixels[last].g;
            ppm.pixels[first].b = ppm.pixels[last].b;
            ppm.pixels[last].r = tempr;     //last pixel be the temp
            ppm.pixels[last].g = tempg;
            ppm.pixels[last].b = tempb;
            first++;    //increment the first
            last--;     //increment the last
        } //while
        first = length + 1;   //increment the fist
        length = length + ppm.width;   //reset the length
        last = length;   //reset the last
    } //while
}

/*********** rotate **********
      Purpose: An ppmarray, do the rotate function about
               this array. Rotate 90 clockwise.
      Returns: Null.
 ***********************************/

void rotate(PpmArray &ppm){
    int width = ppm.width;    //initialize width equal ppmarray width.
    int height = ppm.height;  //initialize weight equal ppmarray weight.
    Pixel *newone = new Pixel[ppm.capacity];    //allocating menmory
    int i = 0;
    while (i < height){
        //loop to rotate the pixel by algorithm
        int j = 0;
        while (j < width){
            //loop to rotate the pixel by algorith
            newone[j * height + height - 1 - i] = ppm.pixels[width * i + j];
            j++;
        } //while
        i++;
    } //while
    ppm.height = width;
    ppm.width = height;
    delete [ ] ppm.pixels;   //delete the memory from heap
    ppm.pixels = newone;
}

/*********** sepia **********
    Purpose: An ppmarray, do the sepia function about
          this array. give a color of this picture.
    Returns: Null.
***********************************/

void sepia(PpmArray &ppm){
    int index = 0;   //pos
    int red = 0;     //initilaize a new red color
    int green = 0;   //initilaize a new green color
    int blue = 0;    //initilaize a new blue color
    while (index < ppm.size){
        //loop to do the sepia function
        red = ppm.pixels[index].r;        //take the pixels in red
        green = ppm.pixels[index].g;      //take the pixels in green
        blue = ppm.pixels[index].b;       //take the pixels in blue
        ppm.pixels[index].r = red * 0.393 + green * 0.769 + blue * 0.189;
        if (ppm.pixels[index].r > 255){
            ppm.pixels[index].r = 255;
        } //if
        ppm.pixels[index].g = red * 0.349 + green * 0.686 + blue * 0.168;
        if (ppm.pixels[index].g > 255){
            ppm.pixels[index].g = 255;
        } //if
        ppm.pixels[index].b = red * 0.272 + green * 0.534 + blue * 0.131;
        if (ppm.pixels[index].b > 255){
            ppm.pixels[index].b = 255;
        } //if
        index++;    //increment the pos
    } //while
}

/*********** main **********
       Purpose: to read a pixel from standard input. 
                And then print the pixel after do 
                the function sepia, rotate or flip.
       Returns: 0 or 1.
***********************************/

int main(int argc, const char * argv[]){
    string str;     //str
    int counter = 0;
    int index = 0;    //pos
    PpmArray *newone = new PpmArray;    //allcating menmory on heap
    newone->size = 0;   //initialize size
    newone->capacity = 5;   //initialize capacity
    newone->width = 0;  //initialize width
    newone->height = 0;   //initialize height
    newone->pixels = new Pixel[newone->capacity];  //allocating menmory
    int var = 1;     //controller
    int a,b,c;       //int
    while(true){
        //loop to read an int
        cin >> a;
        cin >> b;
        cin >> c;
        if (cin.fail()){
            //if cin is not an int
            cin.ignore();
            cin.clear();
            newone->width = a;   //get the width
            newone->height = b;    //get the height
            break;
        } //if
        if (a < 0 || b < 0 || c < 0){    //if any one an int is less than 0
            return 0;
        } //if
        else if (a > 255 || b > 255 || c > 255){  //if any one an int greater than 255
            return 0;
        } //if
        else{//put this three in an array.
            if(newone->size >= newone->capacity){
                newone->capacity = newone->capacity * 2;  //expand the capacity
                Pixel *one = new Pixel[newone->capacity]; //expand the pixel
                Pixel *temp = newone->pixels;  //make a new temp
                int pos = 0;
                while (pos < newone->size){
                    //loop to put the pixel in it
                    one[pos].r = newone->pixels[pos].r;
                    one[pos].g = newone->pixels[pos].g;
                    one[pos].b = newone->pixels[pos].b;
                    pos++;   //increment pos
                }//while
                newone->pixels = one;
                delete [ ] temp;      //delete menmory
            } //if
            if (counter == 0){  //controller is 0
                newone->pixels[index].r = a;
                counter++;     //increment counter
            } //if
            if (counter == 1){ //controller is 1
                newone->pixels[index].g = b;
                counter++;
            }//if
            if (counter == 2){   //controller is 2
                newone->pixels[index].b = c;
                counter = 0;
                index++;
                newone->size++;
            } //if
        } //if
    } //while
    while (true){
        //loop to read in function
        cin >> str;   //read in a string
        if (cin.fail()){
            // if read no more
            cin.ignore();
            cin.clear();
            break;
        } //if
        if (str == "rotate"){   //rotate
            rotate(*newone);
        } //if
        else if (str == "flip"){  //flip
            flipHorizontal(*newone);
        } //if
        else if (str == "sepia"){  //sepia
            sepia(*newone);
        } //if
        else{var=0;}
    } //while
    if (var == 0){return 0;}   //if controller is 0, then read in invalid function name
    int width = newone->width;
    int height = newone->height;
    if (width == 0 || height == 0){
        return 4;
    } //if
    else if (width <= 0 || height <= 0){
        return 4;
    } //if
    else{
        // to print these on screen
        cout << "P3" << endl;
        cout << newone->width <<  " " << newone->height << endl;
        cout << "255" << endl;
        int pos = 0;
        int i = 0;
        int j = 0;
        while (i < newone->height){ //loop
            while (j < newone->width){  //loop
                cout << newone->pixels[pos].r << " " << newone->pixels[pos].g << " " << newone->pixels[pos].b;
                j++;  //increment
                pos++;   //increment
                if (j <= (newone->width - 1)){
                    cout << " ";
                } //if
            }  //while
            cout << endl;
            j=0;
            i++;
        } //while
        delete [ ] newone->pixels;   //delete menmory
        delete newone;   //delete
    } //if
} //end
