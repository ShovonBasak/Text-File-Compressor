#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<bitset>
#include"PriorityQueue.h"

using namespace std;

class Compressor
{
    int arr[256],count,usedChar,countBit;
    char c;
    string encodedString,decodedString,tempString,encoded;
    string varBitCode[256];
public:
    Compressor(char fileName[])
    {
        for(int i=0; i<256; i++)
        {
            arr[i]=0;
        }
        count=0;
        usedChar=0;
        tempString="";
        countBit=0;
        encoded="";
        decodedString="";

        ifstream is(fileName);

        while (is.get(c))
        {
            arr[c]++;
        }

        is.close();
    }

    void readFile(char fileName[])
    {
        ifstream is(fileName);

        while (is.get(c))
        {
            cout << c;
            arr[c]++;
        }
    }

    void print()
    {
        for(int i=0; i<256; i++)
        {
            if(arr[i]!=0)
            {
                printf("\n%c ",i);
                cout<<varBitCode[i];
            }
        }
    }

    node* huffman()
    {
        Queue Q;
        int n=0;
        for(int i=0; i<256; i++)
        {
            if(arr[i]!=0)
                n++;
        }
        for(int i=0; i<256; i++)
        {
            if(arr[i]!=0)
            {
                Q.append(arr[i],char(i));
            }
        }
        for(int i=1; i<n; i++)
        {
            node* z=new node();
            z->left=Q.serve();
            z->right=Q.serve();
            z->freq=z->left->freq + z->right->freq;
            Q.append(z);
        }
        return Q.serve();
    }

    void varBit(node* temp)
    {
        if(temp->c!='\0')
        {
            varBitCode[temp->c]=tempString;
            return;
        }
        tempString.push_back('0');
        varBit(temp->left);
        tempString = tempString.substr (0,tempString.length()-1);

        tempString.push_back('1');
        varBit(temp->right);
        tempString = tempString.substr (0,tempString.length()-1);
        return;
    }

    void encode(char fileName[])
    {
        ifstream is(fileName);
        ofstream myfile;
        myfile.open ("compressed.txt");

        while (is.get(c))
        {
            encodedString+=varBitCode[c];
        }
        bitset<8> foo;

        for(int i=0; i<encodedString.length(); i++)
        {
            countBit++;
            if(encodedString.at(i)=='1')
                foo.set(countBit-1) << '\n';    // 1011
            if(countBit==8)
            {
                char byte =  foo.to_ulong();
                encoded+=byte;
                countBit=0;
                foo.reset();
            }
        }

        myfile << encoded;
        myfile.close();
    }

    void decode(node* huffmanTree)
    {
        node* temp=huffmanTree;

        for(int i=0; i<encodedString.length(); i++)
        {
            if(encodedString.at(i)=='0')
                temp=temp->left;
            else
                temp=temp->right;

            if(temp->c)
            {
                decodedString+=temp->c;
                temp=huffmanTree;
            }
        }
        ofstream is("compressed.txt");
        is<<decodedString;
    }

};

int main()
{
    char fileName[256];
    int x=0;

    cout << "Enter the name of an existing text file: ";
    cin.get (fileName,256);

    Compressor c(fileName);
    node* hTree=c.huffman();
    c.varBit(hTree);

    cout<<"1: Read the file"<<endl;
    cout<<"2: Encode"<<endl;
    cout<<"3: Decode"<<endl;
    cout<<"4: Bit code for each character used in the file"<<endl;
    cout<<"5: Exit"<<endl;

    while(x!=5)
    {
        cout<<endl<<endl;

        cout<<endl<<"Select what you want to do with the file?:";
        cin>>x;

        if(x==1)
        {
            cout<<"Message from the file:"<<endl;
            c.readFile(fileName);
        }
        else if(x==2)
        {
            cout<<endl<<"Message Encoded! ";
            c.encode(fileName);
        }
        else if(x==3)
        {
            cout<<endl<<"Message Decoded! ";
            c.decode(hTree);
        }
        else if(x==4)
        {
            c.print();
        }
    }
    cin.get();

    return 0;
}
