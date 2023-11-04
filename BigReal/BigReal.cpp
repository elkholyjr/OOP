#include <bits/stdc++.h>
#include<fstream>
#include "bmplib.h"
#include "bmplib.cpp"
#define Sykoo cin.tie(0), cout.tie(0), cin.sync_with_stdio(0), cout.sync_with_stdio(0);
#define ll long long
#define ull unsigned long long
using namespace std ;

void option();
void load()  ;
void menu()  ;

unsigned char img_in_color[SIZE][SIZE][3] ;
unsigned char img_out_color[SIZE][SIZE][3];
unsigned char img_in_Gray[SIZE][SIZE]  ;
unsigned char img_out_Gray[SIZE][SIZE] ;
bool colored = false ;


void enlarge( unsigned char img_in_Gray[][SIZE] ){
    cout << "Which quarter to enlarge 1, 2, 3 or 4?\n" ;
    int chc ; cin >> chc ;
    switch (chc) {
        case 1 :
            for ( int i = 0 ; i < SIZE / 2 ; i++ ){
                for ( int j = 0 ; j < SIZE / 2 ; j++ ){
                    char c = img_in_Gray[i][j] ;
                    img_out_Gray[i*2][j*2] = c ;
                    img_out_Gray[i*2 + 1 ][j*2] = c ;
                    img_out_Gray[i*2][j*2 + 1 ] = c ;
                    img_out_Gray[i*2 + 1 ][j*2+ 1] = c ;
                }
            }
            break;
        case 2 :
            for ( int i = 0 ; i < SIZE / 2 ; i++ ){
                for ( int j = 0 ; j < SIZE / 2 ; j++ ){
                    char c = img_in_Gray[i][j + SIZE / 2 ] ;
                    img_out_Gray[i*2][j*2] = c ;
                    img_out_Gray[i*2+1][j*2] = c ;
                    img_out_Gray[i*2][j*2+1] = c ;
                    img_out_Gray[i*2+1][j*2+1] = c ;
                }
            }
            break;
        case 3 :
            for ( int i = 0 ; i < SIZE / 2 ; i++ ){
                for ( int j = 0 ; j < SIZE / 2 ; j++ ){
                    char c = img_in_Gray[i+SIZE / 2][j ] ;
                    img_out_Gray[i*2][j*2] = c ;
                    img_out_Gray[i*2+1][j*2] = c ;
                    img_out_Gray[i*2][j*2+1] = c ;
                    img_out_Gray[i*2+1][j*2+1] = c ;
                }
            }
            break;
        case 4 :
            for ( int i = 0 ; i < SIZE / 2 ; i++ ){
                for ( int j = 0 ; j < SIZE / 2 ; j++ ){
                    char c = img_in_Gray[i+SIZE / 2][j+SIZE / 2] ;
                    img_out_Gray[i*2][j*2] = c ;
                    img_out_Gray[i*2+1][j*2] = c ;
                    img_out_Gray[i*2][j*2+1] = c ;
                    img_out_Gray[i*2+1][j*2+1] = c ;
                }
            }
            break;
    }
    writeGSBMP( "ENLARGED.bmp" , img_out_Gray ) ;
}

void Rot_R( unsigned char img_in_Gray[][SIZE] ){
    cout << "Rotate (90), (180) or (270) degrees?\n" ; int chc ; cin >> chc ;
    switch ( chc ) {
        case 90 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    img_out_Gray[j][SIZE-i-1] = img_in_Gray[i][j] ;
                }
            }
            break ;
        case 180 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    img_out_Gray[SIZE - 1 - i ][SIZE - 1 - j ] = img_in_Gray[i][j] ;
                }
            }
            break ;
        case 270 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    img_out_Gray[SIZE - j - 1 ][i] = img_in_Gray[i][j] ;
                }
            }
            break;
    }
    writeGSBMP( "ROTATED.bmp" , img_out_Gray ) ;
}

void B_W_F( unsigned char img_in_Gray[][SIZE] ) {
    unsigned char mn = 255 , mx = 0 , avg = 0 ;
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            mn = min( img_in_Gray[i][j] , mn ) ;
            mx = max ( img_in_Gray[i][j] , mx ) ;
        }
    }
    avg = ( mn + mx ) / 2 ;
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            ( img_in_Gray[i][j] >= avg ) ? img_out_Gray[i][j] = 255 : img_out_Gray[i][j] = 0 ;
        }
    }
    writeGSBMP( "B_W_F.bmp" , img_out_Gray ) ;
}

void invert_f( unsigned char img_in_Gray[][SIZE] ) {
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = 255 - img_in_Gray[i][j] ;
        }
    }
    writeGSBMP( "invert_color.bmp" , img_out_Gray ) ;
}
void FLIP_F( unsigned char img_in_Gray[][SIZE] ){
    cout<<"Flip (h)orizontally or (v)ertically ?\n";
    char c;cin>>c;
    if (c=='h'){
        for (int i = 0; i <SIZE ; ++i) {
            for (int j = 0; j <SIZE ; ++j) {
                img_out_Gray[i][j]=img_in_Gray[256-i][j];
            }
        }
    }
    if (c=='v'){
        for (int i = 0; i <SIZE ; ++i) {
            for (int j = 0; j <SIZE ; ++j) {
                img_out_Gray[i][j]=img_in_Gray[i][256-j];
            }
        }
    }
    writeGSBMP( "flip_image.bmp" , img_out_Gray ) ;
}
void M_F(unsigned char img_in_Gray[][SIZE]){
    unsigned char img_in_c[SIZE][SIZE][3] ;
    unsigned char img_in_G[SIZE][SIZE] ;

    cout<<"Please enter name of image file to merge with:"<<"\n";

    char text[1000] = "" ; cin >> text ;
    strcat( text , ".bmp") ;
    ifstream in_file( text , std::ifstream::ate | std::ifstream::binary ) ;
    if ( in_file.tellg() > 196000 ) colored = true ;
    if ( colored ) readRGBBMP( text , img_in_c );
    else readGSBMP( text , img_in_G ) ;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int avg=(img_in_G[i][j]+img_in_Gray[i][j])/2;
                img_out_Gray[i][j]=avg;
            }
        }
        writeGSBMP( "M_F.bmp" , img_out_Gray ) ;
}

void D_L_F(unsigned char img_in_Gray[][SIZE]){
    char c;
    cout<<"Do you want to (d)darken or (l)lighten?"<<"\n";
    cin>>c;
    if(c=='d'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                img_out_Gray[i][j] = img_in_Gray[i][j] / 2;
            }
        }
    }else if (c=='l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                img_out_Gray[i][j] = (img_in_Gray[i][j] + (255)) / 2;
            }
        }
    }
    writeGSBMP( "D_L_F.bmp" , img_out_Gray ) ;
}
void S_I(unsigned char img_in_Gray[][SIZE]){
    cout<<"Shrink to (1/2), (1/3) or (1/4)?"<<"\n";
    string s;
    cin>>s;
    for (int i = 0; i < SIZE; i+=2) {
        for (int j = 0; j < SIZE; j+=2) {
            img_out_Gray[i][j]=0;
        }
    }
    if(s=="1/2"){
        for (int i = 0; i < SIZE; i+=2) {
            for (int j = 0; j < SIZE; j+=2) {
                img_out_Gray[i/2][j/2]=(img_in_Gray[i][j]+img_in_Gray[i+1][j]+img_in_Gray[i][j+1]+img_in_Gray[i+1][j+1])/4;
            }
        }
    }else if(s=="1/3"){
        for (int i = 0; i < SIZE; i+=2) {
            for (int j = 0; j < SIZE; j+=2) {
                img_out_Gray[i/3][j/3]=(img_in_Gray[i][j]+img_in_Gray[i+1][j]+img_in_Gray[i][j+1]+img_in_Gray[i+1][j+1])/4;
            }
        }
    }
    else{
        for (int i = 0; i < SIZE; i+=2) {
            for (int j = 0; j < SIZE; j+=2) {
                img_out_Gray[i/4][j/4]=(img_in_Gray[i][j]+img_in_Gray[i+1][j]+img_in_Gray[i][j+1]+img_in_Gray[i+1][j+1])/4;
            }
        }
    }
    writeGSBMP( "S_I.bmp" , img_out_Gray ) ;
}

void B_I(unsigned char img_in_Gray[][SIZE]){
    for (int i = 0; i < SIZE-1; i++) {
        for (int j = 0; j < SIZE-1; j++) {
            img_out_Gray[i][j]=(img_in_Gray[i-1][j]+
                img_in_Gray[i][j-1]+
                img_in_Gray[i+1][j]+
                img_in_Gray[i][j+1]+
                img_in_Gray[i+1][j+1]+
                img_in_Gray[i-1][j-1]+
                img_in_Gray[i+1][j+1]
                +img_in_Gray[i+1][j-1])/9;
        }
    }
    writeGSBMP( "B_I.bmp" , img_out_Gray ) ;
}

void detect_edges(unsigned char img_in_Gray[][SIZE]){
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = img_in_Gray[i][j] ;
        }
    }
    for (int i = 0; i < SIZE-1; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (abs(img_out_Gray[i][j]-img_out_Gray[i][j+1]>17))img_out_Gray[i][j]=0;
            else img_out_Gray[i][j]=255;
        }
    }
    writeGSBMP( "detect_edges.bmp" , img_out_Gray ) ;
}
void miror(unsigned char img_in_Gray[][SIZE]){
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = img_in_Gray[i][j] ;
        }
    }
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?"<<endl;
    char want; cin>>want;
    if(want=='r'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE/2; ++j) {
                img_out_Gray[i][j]=img_out_Gray[i][SIZE-j];
            }
        }
    }
    else if (want=='l'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE/2; ++j) {
                img_out_Gray[i][SIZE-j]=img_out_Gray[i][j];
            }
        }
    }
    else if (want=='d'){
        for (int i = 0; i < SIZE/2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                img_out_Gray[i][j]=img_out_Gray[SIZE-i][j];
            }
        }
    }
    else if (want=='u'){
        for (int i = 0; i < SIZE/2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                img_out_Gray[SIZE-i][j]=img_out_Gray[i][j];
            }
        }
    }
    writeGSBMP( "miror.bmp" , img_out_Gray ) ;
}
void crop(unsigned char img_in_Gray[][SIZE]){
    int x,y,l,w;
    cout<<"Please enter x y l w \n";
    cin>>x>>y>>l>>w;
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = 255 ;
        }
    }
    for (int i = x; i <l ; ++i) {
        for (int j = y; j <w ; ++j) {
            img_out_Gray[i][j]=img_in_Gray[i][j];
        }
    }
    writeGSBMP( "crop.bmp" , img_out_Gray ) ;
}
void skew(unsigned char img_in_Gray[][SIZE]){
int up,right;
char direction;
cout<<"Please enter direction (h) Horizontally , (v) Vertically : ";
cin>>direction;
if(direction=='h') {
    cout << "Please enter degree to skew right : ";
    cin >> right;
    int temp=1;
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            if(img_in_Gray[i][j]* tan(right)>temp){
                img_out_Gray[i][j]=img_in_Gray[i][j];
                temp=tan(right)*img_in_Gray[i][j];
            }
        }
    }
}else{
    cout << "Please enter degree to skew Up : ";
    cin >> up;
    int temp=1;
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            if(img_in_Gray[j][i]* tan(up)>temp){
                img_out_Gray[j][i]=img_in_Gray[j][i];
                temp=tan(up)*img_in_Gray[j][i];
            }
        }
    }

}
    writeGSBMP( "skew.bmp" , img_out_Gray ) ;
}

void load(){
    char text[1000] = "" ; cin >> text ;
    strcat( text , ".bmp") ;
    ifstream in_file( text , std::ifstream::ate | std::ifstream::binary ) ;
    if ( in_file.tellg() > 196000 ) colored = true ;
    if ( colored ) readRGBBMP( text , img_in_color );
    else readGSBMP( text , img_in_Gray ) ;
}
void menu(){
    cout<<"Please select a filter to apply or 0 to exit:"<<'\n';
    cout<<"1 Black & White Filter\n"
          "2 Invert Filter\n"
          "3 Merge Filter \n"
          "4 Flip Image\n"
          "5 Darken and Lighten Image \n"
          "6 Rotate Image\n"
          "7 Detect Image Edges \n"
          "8 Enlarge Image\n"
          "9 Shrink Image\n"
          "10 Mirror 1/2 Image\n"
          "a Shuffle Image\n"
          "b Blur Image\n"
          "c Crop Image\n"
          "d Skew Image Right  \n"
          "e Skew Image Up  \n"
          "s- Save the img to a file \n"
          "0 Exit"<<'\n';
    option() ;
}

void option(){
    string chc ; cin >> chc ;
    if ( chc == "1" ) {
        if (colored) { cout << "ITS_COLORED\n"; } else { B_W_F(img_in_Gray); }
    } else if ( chc == "2" ) {
        if ( colored ) { cout << "ITS_COLORED\n " ; } else { invert_f( img_in_Gray ) ; }
    } else if ( chc == "3" ) {
        if ( colored ) { cout << "ITS_COLORED\n " ; } else { M_F( img_in_Gray ) ; }
    } else if ( chc == "4" ) {
        if ( colored ) { cout << "ITS_COLORED\n " ;} else {FLIP_F(img_in_Gray);}
    } else if ( chc == "5" ) {
        if (colored) { cout << "ITS_COLORED\n "; } else { D_L_F(img_in_Gray); }
    } else if ( chc == "6" ) {
        if (colored) { cout << "ITS_COLORED\n "; } else { Rot_R(img_in_Gray); }
    } else if ( chc == "7" ) {
        if (colored) { cout << "ITS_COLORED\n "; } else { detect_edges(img_in_Gray); }
    } else if ( chc == "8" ) {
        if (colored) { cout << "ITS_COLORED\n "; } else { enlarge(img_in_Gray); }
    } else if ( chc == "9" ) {
        if (colored) { cout << "ITS_COLORED\n"; } else { S_I(img_in_Gray); }
    } else if ( chc == "10") {
    } else if ( chc == "0" ) {
    } else if ( chc == "a" ) {
        if ( colored ) { cout << "ITS_COLORED\n " ; } else { miror( img_in_Gray ) ; }
    } else if ( chc == "b" ) {
        if ( colored ) { cout << "ITS_COLORED\n " ; } else { B_I( img_in_Gray ) ; }
    } else if ( chc == "c" ) {if (colored) { cout << "ITS_COLORED\n "; } else { crop(img_in_Gray) ; }
    } else if ( chc == "d" ) {
    } else if ( chc == "e" ) {if (colored) { cout << "ITS_COLORED\n "; } else { skew(img_in_Gray) ; }
    } else if ( chc == "s" ) {
    }
}

int main(){
    cout<<"Ahlan ya user ya habibi \nPlease enter file name of the img to process:"<<'\n';
    load() ;
    menu() ;
    return 0 ;
}
