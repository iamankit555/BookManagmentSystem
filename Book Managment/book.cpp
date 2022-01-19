#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;
#include<string.h>
#include<conio.h>
#include<stdlib.h>

class book
{
private:
    int bookid;
    char title[20];
    float price;
public:
    book()
    {
        bookid=0;
        strcpy(title,"no title");
        price=0;
    }
    void getBookData()
    {
        cout<<"Enter bookid "<<endl;
        cin>>bookid;
        cin.ignore();
        cout<<"Enter title "<<endl;
        cin.getline(title,19);
        cout<<"Enter price "<<endl;
        cin>>price;
    }
    void showBookData()
    {
        cout<<"\n"<<bookid<<" "<<title<<" "<<price<<endl;
    }
    int storeData();
    void viewAllBook();
    void searchBook(char *);
    void deleteBook(char *);
    void updateBook(char *);
};



int book::storeData()
{
    if(price==0&&bookid==0)
    {
       cout<<"Data is not in initialized"<<endl;
       return 0;
    }
    ofstream fout;
    fout.open("book.dat",ios::app | ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
    cout<<"\n Data added succesfully "<<endl;
    return 1;

}




void book::searchBook(char *t)
{
    ifstream fin;
    int counter=0;
    fin.open("book.dat",ios::in|ios::binary);
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        if(!strcmp(t,title))
        {
            showBookData();
            counter=1;
        }
        fin.read((char*)this,sizeof(*this));
    }
    if(counter==0)
        cout<<"Record not found"<<endl;
    else
    { }


}




void book:: viewAllBook()
{
    ifstream fin;
    fin.open("book.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"file not found"<<endl;
    }
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
           showBookData();
           fin.read((char*)this,sizeof(*this));
        }
        fin.close();

    }

}


void book::deleteBook(char *t)
{
    ifstream fin;
    ofstream fout;
    fin.open("book.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"file not opened "<<endl;
    else
    {
        fout.open("temp.dat",ios::out|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(t,title))
          {
            fout.write((char*)this,sizeof(*this));
          }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("book.dat");
        rename("temp.dat","book.dat");
        cout<<"Data deleted\n";


    }

}
void book::updateBook(char *t)
{
    fstream file;
    file.open("book.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(!strcmp(t,title))
        {
          getBookData();
          file.seekp(file.tellp()-sizeof(*this));
          file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));

    }
    file.close();
    cout<<"\n\t New Data updated "<<endl;

}

int menu()
{
    int choice;
    cout<<"\t\tBook Managment\n"<<endl;
    cout<<"\n1.Insert Book Data\n";
    cout<<"\n2.Show All Book Record\n";
    cout<<"\n3.Delete Book Data\n";
    cout<<"\n4.Update Book Data\n";
    cout<<"\n5.Search Book Data\n";
    cout<<"\n6.Exit\n";
    cout<<"\n\nEnter your choice : ";
    cin>>choice;
    return choice;

}


 main()
{
    book b1;
    char title[20];
    while(1)
    {
        system("cls");
       switch(menu())
      {
    case 1:
          b1.getBookData();
          b1.storeData();
          break;
    case 2:
        b1.viewAllBook();
        break;
    case 3:
        cout<<"Enter title of book for deletion :";
        cin.ignore();
        cin.getline(title,19);
        b1.deleteBook(title);
        break;

    case 4:
        cout<<"Enter title of book for updation :";
        cin.ignore();
        cin.getline(title,19);
        b1.updateBook(title);
        break;

    case 5:
        cout<<"Enter title of book for searching :";
        cin.ignore();
        cin.getline(title,19);
        b1.searchBook(title);
        break;
    case 6:
        cout<<"\n\n\t Thanks for using our Application "<<endl;
        cout<<"Press any key to Exit";
        exit(0);
    }

    getch();
    }






}
