#include <bits/stdc++.h>
#include <fstream>
#include <bitset>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;
string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}
/////////////////////////////////////////////////////////////////
int binaryToDecimalCipher(string n)                  //
{    string num = n;
   // Stores the decimal value
    int dec_value = 0;

   // Initializing base value to 1
    int base = 1;
   int len = num.length();
    for (int i = len - 1; i >= 0; i--) {

       // If the current bit is 1
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
   // Return answer
    return dec_value;
}///////////////////////////////////////////////
void writeCipherTextToFile(char s[32],string fileOutput)
{
    int counter=1;
    // To store size of s
    string str=convertToString(s,32);

    int N = int(str.size());

    string res = "";

       ofstream myfileout (fileOutput,ios_base::app);
        if (myfileout.is_open()){
          myfileout <<str;
        }
        myfileout.close();
}
void DEsetStringtoASCII(char s[32],string fileOutput)
{
    string str=convertToString(s,32);

    int N = int(str.size());

    string res = "";

    for (int i = 0; i < N; i += 8) {

        int decimal_value= binaryToDecimalCipher((str.substr(i, 8)));

        res += char(decimal_value);
    }

    ofstream myfileout (fileOutput,ios_base::app);
        if (myfileout.is_open()){
          myfileout <<res;
        }
        myfileout.close();
}
///////////////////////////////////////////////////////////////////

void shift_right_once(string &key_chunk){
    string shifted="";

       shifted += key_chunk[31];



       for(int i = 0; i < 31; i++){
            shifted += key_chunk[i];
        }
        key_chunk=shifted;
}
string convertHexToBinary(string hexa){
    string kyBinary="";
   long int i = 0;
   while (hexa[i]){
      switch (hexa[i]){
      case '0':
         kyBinary+="0000";
         break;
      case '1':
         kyBinary+="0001";
         break;
      case '2':
         kyBinary+="0010";
         break;
      case '3':
         kyBinary+="0011";
         break;
      case '4':
         kyBinary+="0100";
         break;
      case '5':
         kyBinary+="0101";
         break;
      case '6':
         kyBinary+="0110";
         break;
      case '7':
         kyBinary+="0111";
         break;
      case '8':
         kyBinary+="1000";
         break;
      case '9':
         kyBinary+="1001";
         break;
      case 'A':
      case 'a':
         kyBinary+="1010";
         break;
      case 'B':
      case 'b':
         kyBinary+="1011";
         break;
      case 'C':
      case 'c':
         kyBinary+="1100";
         break;
      case 'D':
      case 'd':
         kyBinary+="1101";
         break;
      case 'E':
      case 'e':
         kyBinary+="1110";
         break;
      case 'F':
      case 'f':
         kyBinary+="1111";
         break;
      default:
         cout << "\nlease enter valid hexadecimal digit "<< hexa[i];
      }
   i++;
   }
   return kyBinary;
}
int validate_hex(string hex){
    int flag=0;
  for (int i=0; i<hex.length(); i++)
    {
        if (!isxdigit(hex[i]))
        {
            flag = 1;
            break;
        }
    }

  return flag;
}
int convertBinaryToDecimal(string binary)
{
    int decimal = 0;
    int counter = 0;
    int size = binary.length();
    for(int i = size-1; i >= 0; i--)
    {
        if(binary[i] == '1')
        {
            decimal += pow(2, counter);
        }
    counter++;
    }
    return decimal;
}

string convertDecimalToBinary(int decimal)
{
    string binary;
    while(decimal != 0)
    {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal = decimal/2;
    }
    while(binary.length() < 4)
    {
        binary = "0" + binary;
    }
    return binary;
}
////////////////////////////////////////S_Box_Encryption/////////////////////////////
void S_box(char s[4])
{

    string stBlock=convertToString(s,4);
    int index = convertBinaryToDecimal(stBlock);
    int s_box[16] = {9, 10,  11,  12,  13,  14,  15,  0,  1,  2,  3,  4,  5,  6,  7,  8};
    int afterSub= s_box[index];
    stBlock=convertDecimalToBinary(afterSub);
   // cout<<stBlock<<endl;
    for(int i=0; i<4; i++)
    {
        s[i] = stBlock[i];
    }
}
void XOR(char t[], string k)
{
    string stBlock=convertToString(t,32);
    for (int i = 0; i < 32 ; i++)
    {
        if (stBlock[i] == k[i])
        {
            stBlock[i] = '0';
        }
        else
        {
            stBlock[i] = '1';
        }
    }
     for(int i=0; i<32; i++)
    {
        t[i] = stBlock[i];
    }
}
////////////////////////////////////////p_Box_Encryption/////////////////////////////
//Circulr Right Shift by 2 bits
void P_Box(char b[32]){
    string block_chunk=convertToString(b,32);
    string shifted="";

       shifted += block_chunk[30];
       shifted += block_chunk[31];



       for(int i = 0; i < 30; i++){
            shifted+= block_chunk[i];
        }
       reverse(shifted.begin(), shifted.end());
        block_chunk=shifted;
         for(int i=0; i<32; i++)
    {
        b[i] = block_chunk[i];
    }

}
////////////////////////////////////////EncryptionCore////////////////////////////////
void EncryptionCore(char b[],string fileOutput,string key)
{    int toFill=0;

    char SubBlock[4];
    for(int i=0; i<4; i++)
    {
        SubBlock[i] = '0';
    }
    int j=0;//length of file
    int n = 32;//number of bits in file
    //out loop blocks
   // int offset = 32/4 ; //selling
    for(int i=0; i<8 && j!=32; i++)
    {
        for(int k=0; k<4 && j!=32; k++)
        {
            SubBlock[k]=b[j];
            j++;
        }

        S_box(SubBlock);
        //cout<<SubBlock<<endl;//correct

        for(int k=0; k<4&& toFill!=32; k++)
        {
            b[toFill]=SubBlock[k];
            toFill++;
        }
        //clean the block
        for(int i=0; i<4; i++)
        {
            SubBlock[i] = '0';
        }
        }//end s_box for 32 bits

         XOR(b,key);

         P_Box(b);

         writeCipherTextToFile(b,fileOutput);
}
///////////////////////////////////////Ecryption/////////////////////////////////////
void Ecryption(string fileName,string fileOutput,string key){
    //Read the plain text file
    string line;
    ofstream myfileout ("Binary.txt");
    if (myfileout.is_open())
    {
        ifstream myfilein (fileName);

        if (myfilein.is_open())
        {
            while ( getline (myfilein,line) )
            {
                for (size_t i = 0; i < line.size(); i++)
                {
                myfileout << bitset<8>(line[i]);
               // myfileout << myline << '\n';

                }
               myfileout<< bitset<8>('\n');
            }
        }
        myfilein.close();
    }
    myfileout.close();

    //
    string text = "";

    ifstream myfilein ("Binary.txt");
    if (myfilein.is_open())
    {
        while ( getline (myfilein,line) )
        {
            for (size_t i = 0; i < line.size(); i++)
            {
            text += line[i];
            }
        }
    }
   myfilein.close();

    ofstream deleteF ("Binary.txt");
    deleteF<<"";
    deleteF.close();

    //divide the plain text into 32 bits block size
    char block[32];
    for(int i=0; i<32; i++)
    {
        block[i] = '0';
    }

    int j=0;//length of file
    int n = text.length();//number of bits in file
    //out loop blocks
    int offset = ceil(n / 32.0) ; //selling
    for(int i=0; i<offset; i++)
    {
        for(int k=0; k<32 && j!=n; k++)
        {
            block[k]=text[j];
            j++;
        }

     EncryptionCore(block,fileOutput,key);
     for(int i=0; i<32; i++)
    {
        block[i] = '0';
    }

    }
}
////////////////////////////////////////p_Box_Decryption/////////////////////////////
void P_box_Decryption(char b[32]){

       string block_chunk=convertToString(b,32);
       string shifted="";
       reverse(block_chunk.begin(), block_chunk.end());
        for(int i = 2; i < 32; i++){
            shifted += block_chunk[i];
        }

       shifted += block_chunk[0];
       shifted += block_chunk[1];
        block_chunk=shifted;
          for(int i=0; i<32; i++)
    {
        b[i] = block_chunk[i];
    }
}
////////////////////////////////////////s_box_Decryption///////////////////////////////
void s_box_Decryption(char s[4])
{
    string stBlock=convertToString(s,4);
    int value = convertBinaryToDecimal(stBlock);
    int index;
    int s_box[16] = {9, 10,  11,  12,  13,  14,  15,  0,  1,  2,  3,  4,  5,  6,  7,  8};
    for (int i=0; i<16; i++)
    {
        if (s_box[i] == value)
        {
            index = i;
        }
    }
    stBlock=convertDecimalToBinary(index);
    for(int i=0; i<4; i++)
    {
        s[i] = stBlock[i];
    }
}
////////////////////////////////////////DecryptionCore////////////////////////////////
void DecryptionCore(char b[],string fileOutput,string key){

    P_box_Decryption(b);
    XOR(b,key);
    int toFill=0;
    char SubBlock[4];
    for(int i=0; i<32; i++)
    {
        SubBlock[i] = '0';
    }
    int j=0;//length of file
    int n = 32;//number of bits in file
    //out loop blocks
   // int offset = 32/4 ; //selling
    for(int i=0; i<8 && j!=32; i++)
    {
        for(int k=0; k<4 && j!=32; k++)
        {
            SubBlock[k]=b[j];
            j++;
        }

        s_box_Decryption(SubBlock);
        //cout<<SubBlock<<endl;//correct

        for(int k=0; k<4 && toFill!=32; k++)
        {
            b[toFill]=SubBlock[k];
            toFill++;
        }
        //clean the block
            for(int i=0; i<4; i++)
        {

            SubBlock[i] = '0';
        }
        }//end s_box for 32 bits

        DEsetStringtoASCII(b,fileOutput);


}
///////////////////////////////////////Decryption/////////////////////////////////////
void Decryption(string fileName,string fileOutput,string key){
     //Read the plain text file

    string line;

    string text = "";
    ifstream myfilein (fileName);
    if (myfilein.is_open())
    {
        while ( getline (myfilein,line) )
        {
            for (size_t i = 0; i < line.size(); i++)
            {
            text += line[i];
            }
        }
    }
    myfilein.close();


    //divide the plain text into 32 bits block size
    char block[32];
    for(int i=0; i<32; i++)
    {
        block[i] = '0';
    }

    int j=0;//length of file
    int n = text.length();//number of bits in file
    //out loop blocks
    int offset = ceil(n / 32.0) ; //selling

    for(int i=0; i<offset; i++)
    {
        for(int k=0; k<32 && j!=n; k++)
        {
            block[k]=text[j];
            j++;
        }

     DecryptionCore(block,fileOutput,key);


     for(int i=0; i<32; i++)
    {
        block[i] = '0';
    }

    }

}
///////////////////////////////////////////main/////////////////////////////////////

int main(){

    int choice;
    string fileInput;
    string fileOutput;

    string key;
    string keyBin;
    int keyHexValidate;

    while(true){
    cout<<"\n\tWelcome to ERO Encrypt Algorithm Program\t"
       "\n----------------------------------------------------------------------\n"
       "\tEnter \"1\" to Encrypt File\n\tEnter \"2\" to Decrypt File"
       "\n\tEnter \"3\" to Exit from the program\n";

     cout<<"\nEnter the choice: ";
     cin>>choice;
      if(choice !=1 && choice !=2 && choice !=3){

        cout<< "Sorry! wrong input\n Try Again";
        continue;
    }
    else if(choice==3){
         cout<<"Done exit program!\n";
            exit(0);
    }


    cout<<"Enter input file name: ";
    cin>>fileInput;
    cout<<"Enter output file name: ";
    cin>>fileOutput;

    cout << "Enter key (8 character in hexadecimal): ";

    cin>>key;

    keyHexValidate=validate_hex(key);
    while(keyHexValidate==1 ||key.length()!=8)
    {
        if(keyHexValidate==1)
        {
        cout << "Wrong key not in hexadecimal"<<endl;
        }
    else
    cout << "Wrong key length"<<endl;
    cout << "Enter key (8 character in hexadecimal): ";
    cin>>key;
    keyHexValidate=validate_hex(key);
    }

    keyBin= convertHexToBinary(key);
    shift_right_once(keyBin);
    if(choice==1){
    Ecryption(fileInput,fileOutput,keyBin);
    }
    else if (choice==2){
    Decryption(fileInput,fileOutput,keyBin);
    }
    cout<<"Done!\nYou can find the output in "<<fileOutput<<" File\n";
    }
    return 0;
}
