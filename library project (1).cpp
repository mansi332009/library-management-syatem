
//                   HEADER FILE USED IN PROJECT
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<windows.h>
#include<stdlib.h>
using namespace std;
void gotoxy(short x,short y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}


class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
        cout<<"\nNEW BOOK ENTRY...\n";
        cout<<"\nEnter The book no.";
        cin>>bno;
        cout<<"\nEnter The Name of The Book ";
        cin>>bname;
        cout<<"\nEnter The Author's Name ";
        cin>>aname;
      
        cout<<"\nBook Created..";
    }

    void show_book()
    {
        cout<<"\nBook no. : "<<bno;
        cout<<"\nBook Name : ";
        cout<<bname;
        cout<<"\nAuthor Name : ";
        cout<<aname;
    }

    void modify_book()
    {
        cout<<"\nBook no. : "<<bno;
        cout<<"\nModify Book Name : ";
        cin>>bname;
        cout<<"\nModify Author's Name of Book : ";
        cin>>aname;
    }

    char* retbno()
    {
        return bno;
    }

    void report()
    {
	cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
	}

};         


class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
public:
    void create_student()
    {
        
         cout<<"\nNEW STUDENT ENTRY...\n";
        cout<<"\nEnter The admission no. ";
        cin>>admno;
        cout<<"\nEnter The Name of The Student ";
        cin>>name;
        token=0;
        stbno[0]='/0';
        cout<<"\nStudent Record Created..";
    }

    void show_student()
    {
        cout<<"\nAdmission no. : "<<admno;
        cout<<"\nStudent Name : ";
        cout<<name;
        cout<<"\nNo of Book issued : "<<token;
        if(token==1)
            cout<<"\nBook No "<<stbno;
    }

    void modify_student()
    {
        cout<<"\nAdmission no. : "<<admno;
        cout<<"\nModify Student Name : ";
    	cin>>name;
    }

    char* retadmno()
    {
        return admno;
    }

    char* retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
	token=1;
	}

    void resettoken()
    {
	token=0;
	}

    void getstbno(char t[])
    {
        strcpy(stbno,t);
    }

    void report()
    {
	cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;
	}

};         


//global declaration for stream object, object
fstream fp,fp1;
book bk;
student st;
//function to write in file
void write_book()
{
    char ch;
    fp.open("book.txt",ios::out|ios::app);
    do
    {
        
        bk.create_book();
        fp.write((char*)&bk,sizeof(book));
        cout<<"\nDo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}
void write_student()
{
    char ch;
    fp.open("student.txt",ios::out|ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st,sizeof(student));
        cout<<"\ndo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

//        function to read specific record from file
void display_spb(char n[])
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.txt",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
             flag=1;
        }
    }
    
    fp.close();
    if(flag==0)
        cout<<"\nBook does not exist";
    getch();
}

void display_sps(char n[])
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.txt",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmpi(st.retadmno(),n)==0))
        {
            st.show_student();
            flag=1;
        }
    }
    
    fp.close();
    if(flag==0)
            cout<<"\nStudent does not exist";
     getch();
}


//        function to modify record of file
void modify_book()
{
    char n[6];
    int found=0;
    
    cout<<"\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\tEnter The book no. of The book";
    cin>>n;
    fp.open("book.txt",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
            cout<<"\nEnter The New Details of book"<<endl;
            bk.modify_book();
            int pos=-1*sizeof(bk);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&bk,sizeof(book));
                cout<<"\n\t Record Updated";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n Record Not Found ";
        getch();
}


void modify_student()
{
    char n[6];
    int found=0;
    
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\tEnter The admission no. of The student";
    cin>>n;
    fp.open("student.txt",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),n)==0)
        {
            st.show_student();
            cout<<"\nEnter The New Details of student"<<endl;
            st.modify_student();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\t Record Updated";
            found=1;
        }
    }
    
    fp.close();
    if(found==0)
        cout<<"\n Record Not Found ";
    getch();
}

//        function to delete record of file
void delete_student()
{
    char n[6];
    int flag=0;    
  
        cout<<"\n\n\tDELETE STUDENT...";
        cout<<"\nEnter The admission no. of the Student You Want To Delete : ";
        cin>>n;
        fp.open("student.txt",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.txt",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n)!=0)
                 fp2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }
        
    fp2.close();
        fp.close();
        remove("student.txt");
        rename("Temp.txt","student.txt");
        if(flag==1)
             cout<<"\n\tRecord Deleted ..";
        else
             cout<<"\nRecord not found";
        getch();
}


void delete_book()
{
    char n[6];
    
    cout<<"\n\n\tDELETE BOOK ...";
    cout<<"\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.txt",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.txt",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)!=0)  
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }
        
    fp2.close();
        fp.close();
        remove("book.txt");
        rename("Temp.txt","book.txt");
        cout<<"\n\tRecord Deleted ..";
        getch();
}




//        function to display all students list
void display_alls()
{
   
         fp.open("student.txt",ios::in);
         if(!fp)
         {
               cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               getch();
               return;
         }

    cout<<"\n\tSTUDENT LIST\n";
    cout<<"==================================================================\n";
    cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }
         
    fp.close();
    getch();
}


//        function to display Books list
void display_allb()
{
   
    fp.open("book.txt",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               getch();
               return;
         }

    cout<<"\n\t\tBook LIST\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
         fp.close();
         getch();
}


//        function to issue book
void book_issue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
   
    cout<<"\nBOOK ISSUE ...";
    cout<<"\n\tEnter The student's id no.";
    cin>>sn;
    fp.open("student.txt",ios::in|ios::out);
        fp1.open("book.txt",ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student)) && found==0)
           {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==0)
            {
                      cout<<"\n\tEnter the book no. ";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                       if(strcmpi(bk.retbno(),bn)==0)
                    {
                        bk.show_book();
                        flag=1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                               int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\t Book issued successfully\nPlease Note: current date is written on backside of book so, submit within 15 days otherwise fine Rs. 1 for each day  after 15 days period"; 
                            
                       
                    }
                    }
                  if(flag==0)
                        cout<<"Book no does not exist";
            }
                else
                  cout<<"You have not returned the last book ";

        }
    }
          if(found==0)
        cout<<"Student record not exist...";
    getch();
      fp.close();
      fp1.close();
}


//        function to deposit book
void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    
    cout<<"\nBOOK DEPOSIT ...";
    cout<<"\n\tEnter The student's id no.";
    cin>>sn;
    fp.open("student.txt",ios::in|ios::out);
    fp1.open("book.txt",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmpi(bk.retbno(),st.retstbno())==0)
            {
                bk.show_book();
                flag=1;
                cout<<"\nBook deposited in no. of days";
                cin>>day;
                if(day>15)
                {
                   fine=(day-15)*1;
                   cout<<"\nFine has to deposited Rs. "<<fine;
                }
                    st.resettoken();
                    int pos=-1*sizeof(st);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\n\t Book deposited successfully";
            }
            }
          if(flag==0)
            cout<<"Book no does not exist";
              }
         else
            cout<<"No book is issued..please check!!";
        }
       }
      if(found==0)
    cout<<"Student record not exist...";
    getch();
  fp.close();
  fp1.close();
  }





//        INTRODUCTION FUNCTION


int intro()
{
    
    gotoxy(35,11);
    cout<<"LIBRARY";
    gotoxy(32,14);
    cout<<"MANAGEMENT";
    gotoxy(36,17);
    cout<<"SYSTEM";
    cout<<"\nMADE BY : MANSI SAXENA";
    
    return 0;
}




//        ADMINISTRATOR MENU FUNCTION


void admin_menu()
{
    
    int ch2;
    cout<<"\n\n\tADMINISTRATOR MENU";
    cout<<"\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout<<"\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout<<"\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\t6.CREATE BOOK ";
    cout<<"\n\t7.DISPLAY ALL BOOKS ";
    cout<<"\n\t8.DISPLAY SPECIFIC BOOK ";
    cout<<"\n\t9.MODIFY BOOK ";
    cout<<"\n\t10.DELETE BOOK ";
    cout<<"\n\t11.BACK TO MAIN MENU";
    cout<<"\n\tPlease Enter Your Choice (1-11) ";
    cin>>ch2;
    switch(ch2)
    {
            case 1: write_student();break;
            case 2: display_alls();break;
            case 3:
                   char num[6];
                   cout<<"\n\n\tPlease Enter The Admission No. ";
                   cin>>num;
                   display_sps(num);
                   break;
              case 4: modify_student();break;
              case 5: delete_student();break;
        case 6: 
            write_book();break;
        case 7: display_allb();break;
        case 8: {
                   char num[6];
                  
                   cout<<"\n\n\tPlease Enter The book No. ";
                   cin>>num;
                   display_spb(num);
                   break;
            }
              case 9: modify_book();break;
              case 10: delete_book();break;
             case 11: return;
              default:cout<<"\a";
       }
       admin_menu();
}



//        THE MAIN FUNCTION OF PROGRAM

int main()
{
    char ch;
    intro();
    do
    {
        
        cout<<"\n\n\tMAIN MENU";
        cout<<"\n\t01. BOOK ISSUE";
        cout<<"\n\t02. BOOK DEPOSIT";
          cout<<"\n\t03. ADMINISTRATOR MENU";
          cout<<"\n\t04. EXIT";
          cout<<"\n\tPlease Select Your Option (1-4) ";
          ch=getche();
          switch(ch)
          {
            case '1':book_issue();
                    break;
              case '2':book_deposit();
                     break;
              case '3':admin_menu();
                 break;
              case '4':exit(0);
              	  default :cout<<"\a";		
            
        }
        }while(ch!='4');
    
}


//                END OF PROJECT

