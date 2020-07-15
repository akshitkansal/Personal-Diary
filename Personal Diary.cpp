#include<windows.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<ctime>
#include<sstream>
using namespace std;

class diary {
    char place[100],note[500000],note1[500000],time[20],time1[20];
    char date[11],date1[11];
public:
    void input() {                          //To input information
        cout<<"\n\n\n\n\t\t\t Enter the Date in this format only dd.mm.yyyy : ";
        fflush(stdin);
        cin.getline(date,11);
        fflush(stdin);
        cout<<"\n\n\t\t\t Enter time in this format hh:mm : ";
        cin.getline(time,20);
        fflush(stdin);
        cout<<"\n\n\t\t\t Enter place : ";
        cin.getline(place,100);
        fflush(stdin);
        cout<<"\n\n\t\t\t Write your note in diary : ";
        cin.getline(note,500000);
        fflush(stdin);
    }

    void display() { //To display particular information
        cout<<"\n\n\t Date : "<<date;
        cout<<"\n\n\t Time : "<<time;
        cout<<"\n\n\t Place: "<<place;
        cout<<"\n\n\t Note : "<<note;
        cout<<"\n\t--------------------------------------------------------------------------------------------------\n";
        cout<<"\n\t--------------------------------------------------------------------------------------------------\n";
        cout<<"\n\tPress any key to continue..\n\n";
        getch();
    }

    void complete_display() {   //To display complete information
        cout<<"\n\n\t Date : "<<date;
        cout<<"\n\n\t Time : "<<time;
        cout<<"\n\n\t Place: "<<place;
        cout<<"\n\n\t Note : "<<note;
        cout<<"\n\t--------------------------------------------------------------------------------------------------\n";
        cout<<"\n\t--------------------------------------------------------------------------------------------------\n";
        cout<<"\n\tPress any key to continue..\n\n";
        getch();
    }

    void modify() {      //To input information for modification in daily diary
        cout<<"\n\n\n\n\t\t\t Enter the Date in this format only dd.mm.yyyy : ";
        fflush(stdin);
        cin.getline(date,11);
        fflush(stdin);
        cout<<"\n\n\t\t\t Enter modified time in this format hh.mm : ";
        cin.getline(time,20);
        fflush(stdin);
        cout<<"\n\n\t\t\t Enter modified place : ";
        cin.getline(place,100);
        fflush(stdin);
        cout<<"\n\n\t\t\t Write your modified note in diary : ";
        cin.getline(note,500000);
        fflush(stdin);
    }

    void reminder() {
        cout<<"\n\n\n\n\t\t\t Enter the Date in this format only dd.mm.yyyy : ";
        fflush(stdin);
        cin.getline(date1,11);
        fflush(stdin);
        cout<<"\n\n\t\t\t Enter time in this format hh.mm : ";
        cin.getline(time1,20);
        fflush(stdin);
        cout<<"\n\n\t\t\t Add Reminder : ";
        cin.getline(note1,500000);
        fflush(stdin);
    }

    void rem_show() {
        cout<<"\n\n";
        cout<<"\t\t\t ..........REMINDER..........\n\n\n\n";
        cout<<"\t\t\t Date : "<<date1<<"\n";
        cout<<"\t\t\t Time : "<<time1<<"\n";
        cout<<"\t\t\t Note : "<<note1<<"\n\n";
        cout<<"\n----------------------------------------------------------------------------------------------------\n";
        cout<<"\n----------------------------------------------------------------------------------------------------\n";
        cout<<"Press any key to continue..\n\n";
        getch();
    }

    char* return_date() {   // It returns the date which is entered.
        return date;
    }

    char* return_date1() {
        return date1;
    }
};

//function declarations.

void enter_info();             //function declared for information
void view_comp();              //function declared for seeing complete information of diary
void diary_information();      //function declared to show the information about diary.
void add_reminder();           //function declared to add content in reminder
void show_reminder();          //function to show reminder

string convertToString(char* a,int sizey) {
    int i;
    string s=" ";
    for (i=0;i<sizey;i++) {
        s=s+a[i];
    }
    return s;
}

//enter information
void enter_info() {
    diary obj;
    ofstream write_file;
    char choice ='y';
    write_file.open("DiaryData.dat",ios::binary|ios::app);
    while(choice=='y'|| choice=='Y') {
        obj.input();
        write_file.write((char*)(&obj), sizeof(diary));
        cout<<"\n\n\n\t\t\t Do you want to add another(y/n)  ";
        cin>>choice;
    }
    write_file.close();
}

//view particular information
void view_info(char *dat) {
    system("color 4f");
    diary obj;
    bool flag=false;
    ifstream read_file;
    read_file.open("DiaryData.dat",ios::binary);
    if(!read_file) {
        cout<<"File could not be open.";
        getch();
        return;
    }
    while(read_file.read((char *)(&obj),sizeof(diary))) {
        if(strcmp(obj.return_date(),dat)==0) {
            obj.display();
            flag=true;
        }
    }
    read_file.close();
    if(flag==false) {
            cout<<"\n\n\t\t\t Information does not exist";
    }
    getch();
}

//modify information
void modify(char *dat) {
    bool f=false;
    char ans;
    diary obj;
    fstream m_file;
    m_file.open("DiaryData.dat",ios::binary|ios::in|ios::out);
    if(!m_file) {
        cout<<"file can not be open.";
        getch();
        return;
    }
    while(!m_file.eof() && f==false) {
        m_file.read((char *) (&obj), sizeof(diary));
        if(strcmp(obj.return_date(),dat)==0) {
            obj.complete_display();
            cout<<"do you want to modify this record (y/n)?";
            fflush(stdin);
            cin>>ans;
            if (ans=='n')
            continue;
            else
            {
                cout<<"\n\n\n\t\t\t Make Changes in your Diary\n\n";
                obj.modify();
                double pos=(-1)*static_cast<double>(sizeof (diary));  // style cast to make it signed so that
                m_file.seekg(pos,ios::cur);
                m_file.write((char *) (&obj), sizeof(diary));
                cout<<"\n\n\n\t\t\t Content changed successfully..\n";
                f=true;
                getch();
            }
        }
    }
    m_file.close();
    if(f==false) {
        cout<<"\n\n\n\t\t\t Record does not exist.\n";
    }
        getch();
}

//remove information
void remove(char *dat) {
    int present=0;
    char ans;
    system("color 4f");
    diary obj;
    ifstream read_file;
    ofstream write_file;
    read_file.open("DiaryData.dat",ios::binary);
    if(!read_file) {
        cout<<"File could not be open ";
        getch();
        return;
    }
    write_file.open("copy.dat",ios::binary);
    read_file.seekg(0,ios::beg);
    while(read_file.read((char *) (&obj), sizeof(diary))) {
        if(strcmp(obj.return_date(),dat)!=0) {
                write_file.write((char *) (&obj), sizeof(diary));
        }
        else {
            obj.complete_display();
            cout<<"do you want to remove this record (y/n)?";
            fflush(stdin);
            cin>>ans;
            if (ans=='n')
                {write_file.write((char *) (&obj), sizeof(diary));
                continue;
                }
            else
            present=1;
        }
    }
    read_file.close();
    write_file.close();
    remove("DiaryData.dat");
    rename("copy.dat","DiaryData.dat");
    if (present==1) {
        cout<<"\n\n\tRecord Removed ..";
    }
    else {
        cout<<"\n\n\tRecord not Present..";
    }
        getch();
}

//view complete information
void view_comp() {
    system("color 4f");
    diary obj;
    ifstream read_file;
    read_file.open("DiaryData.dat",ios::binary);
    if(!read_file) {
        cout<<"File could not be open ";
        getch();
        return;
    }
    while(read_file.read((char *) (&obj), sizeof(diary))) {
        obj.complete_display();
    }
        read_file.close();
}

//add reminder to new reminder file
void add_reminder() {
    diary obj;
    ofstream write_file;
    char choice ='y';
    write_file.open("reminder1.dat",ios::binary|ios::app);
    while(choice=='y'|| choice=='Y') {
        obj.reminder();
        write_file.write((char*)(&obj), sizeof(diary));
        cout<<"\n\n\n\t\t\t Do you want to add another(y/n)  ";
        cin>>choice;
    }
    write_file.close();
}

// show reminder
void show_reminder() {
    time_t now =time(0);
    tm *ltm=localtime(&now);
    int yyyy=1900+ltm->tm_year;
    int mm=1+ltm->tm_mon;
    int dd=ltm->tm_mday;

    ostringstream str1,str2,str3;
    char today_date[11];
    str1<<dd;
    string dds=str1.str();
    if ((dd>0)&&(dd<9)) {
        dds="0"+dds;
    }
    str2<<mm;
    string ddm=str2.str();
    if ((mm>0)&&(mm<9)) {
         ddm="0"+ddm;
    }
    str3<<yyyy;
    string ddy=str3.str();

    string td=dds+"."+ddm+"."+ddy;

    strcpy(today_date,td.c_str());//convert to character array
    cout<<"\n\t\t\t\t\t\t TODAY DATE IS "<<today_date;

    diary obj;
    ifstream read_file;
    read_file.open("reminder1.dat",ios::binary);
    if(!read_file) {
        system("color 4f");
        cout<<"\n\n\t\tTHERE ARE NO REMINDERS SET";
        getch();
        return;
    }
    system("color 4f");
    while(read_file.read((char *) (&obj), sizeof(diary))) {
        string objdatestr = convertToString(obj.return_date1(), 11);

        string sdd=objdatestr.substr(1,2);
        string smm=objdatestr.substr(4,2);
        string syy=objdatestr.substr(7,4);

        if(syy<ddy) {
            continue;
        }

        else {
            if(syy>ddy) {
                obj.rem_show();
            }

            else {
                if(syy==ddy) {
                    if (smm>ddm) {
                        obj.rem_show();
                    }
                    else {
                        if (smm==ddm) {
                            if (sdd>dds) {
                                obj.rem_show();
                            }
                        }
                   }
                }
            }
        }

    }
    read_file.close();
    getch();
}

//diary introduction
void diary_information() {
    cout<<"\n\n\n\t\t\t ....PERSONAL DAILY DIARY PROJECT....\n\n\n\n\n";
    cout<<"\t\t\t Submitted By:  \n\n\n";
    cout<<"\t\t\t   Name - Akshit Kansal\t(18070124008)\n\n\n";
	cout<<"\t\t\t   Name - Mayank Arora\t(18070124040) \n\n\n";
    cout<<"\t\t\t   Name - Pranav Sharma\t(18070124051)\n\n\n";
	cout<<"\t\t\t   Name - Roshan Mitra\t(18070124060) \n\n\n";
    cout<<"\t\t\t   College - Symbiosis Institute of Technology, Pune\n\n\n\n\n\n";
    getch();
}

// main of class
main() {
    char c='1';
    int choice;
    int counter=0;
    int p,i=0;
    char dat[11];
    char password[20]="12345";
    char pass[20];
    int remi=1;    //It is for reminder
    system("cls");
    system("color 4f");
    system("cls");
    fstream object1("pass1.txt",ios::app);
    ifstream object2("pass1.txt");
    cout<<"\n\n\n";
    cout<<"\t\t\t\tDAILY DIARY";
    cout<<"\n\n\n\n\n\n\n\n";
    cout<<"\t\t\tENTER PASSWORD TO OPEN DIARY ";
    object1<<"12345"<<endl;     // default password //
    cout<<"\n\n\n\n\t\t\tPassword- ";
    while(1) {
        char a=getch();
        if(a==13)
            break;
        else if(a==8) {
            if(i!=0) {
                printf("\b \b");
                i--;
            }
            else {
                printf("\a");
            }
        }
        else {
            cout<<"*";
            pass[i]=a;
            i++;
        }
        pass[i]='\0';
    }
    object2.seekg(0);
    object2>>password;
    object1.close();
    object2.close();
    if(strcmp(pass,password)==0) {
        system("cls");
        if(remi==1) {
            diary_information();
            system("cls");
            show_reminder();
        }
        remi=0;
        while(1) {
			system("cls");
            switch(c) {
                case '1':
                    system("cls");
                    system("color 30");
                    cout<<"\n\n\n\n";
                    cout<<"\t\t\t\t DAILY DIARY";
                    cout<<"\n\n\n\n\n\n";
                    cout<<"\t\t\t 1 - Enter Information\n\n";
                    cout<<"\t\t\t 2 - View  particular page\n\n";
                    cout<<"\t\t\t 3 - Modify Information\n\n";
                    cout<<"\t\t\t 4 - Remove Information of page\n\n";
                    cout<<"\t\t\t 5 - Change password\n\n";
                    cout<<"\t\t\t 6 - View complete pages\n\n";
                    cout<<"\t\t\t 7 - Add Reminder\n\n";
                    cout<<"\t\t\t 8 - Exit\n\n\n\n";
                    cout<<"\t\t\t Enter Your Choice... ";
                    cin>>choice;
                    system("cls");//Clear screen
                    switch(choice) {
                        case 1:
                            system("cls");
                            cout<<"\n\n\n\t\t\t Enter Information\n";
                            system("color 1f");
                            enter_info();
                            break;//break case 1
                        case  2:
                            system("cls");
                            system("color 2f");
                            cout<<"\n\n\n\t\t\t Enter date in this format only dd.mm.yyyy  ";
                            fflush(stdin);
                            cin.getline(dat,11);
                            view_info(dat);
                            break;//break case 2
                        case 3:
                            system("cls");
                            system("color 5f");
                            cout<<"\n\n\n\t\t\t Enter date in this format only dd.mm.yyyy  ";
                            fflush(stdin);
                            cin.getline(dat,11);
                            modify(dat);
                            break;//break case 3
                        case 4:
                            system("cls");
                            system("color 6f");
                            cout<<"\n\n\n\t\t\t Enter date in this format only dd.mm.yyyy  ";
                            fflush(stdin);
                            cin.getline(dat,11);
                            remove(dat);
                            break;//break exit
                        case 5:
                            {
                                int j=0;
                                system("cls");
                                system("color 7f");
                                cout<<"\n\n\n\t\t\t Change password\n\n";
                                ofstream object("pass1.txt");
                                cout<<"\t\t\tEnter new password: ";
                                while(1) {
                                    char a=getch();
                                    if(a==13) {
                                        break;
                                    }
                                    else if(a==8) {
                                        if(j!=0) {
                                            printf("\b \b");
                                            j--;
                                        }
                                        else {
                                            printf("\a");
                                        }
                                    }
                                    else {
                                        cout<<"*";
                                        password[j]=a;
                                        j++;
                                    }
                                    password[j]='\0';
                                }
                                object<<password<<endl;
                                object.close();
                                cout<<"\nPassword changed successfully\n";
                                getch();
                            }
                            break;
                        case 6:
                            system("cls");
                            system("color 2f");
                            view_comp();
                            break;//break case 6
                        case 7:
                            system("cls");
                            cout<<"\n\n\n\t\t\t Add Reminder\n";
                            system("color 1f");
                            add_reminder();
                            break;//break case 1
                        case 8:
                            system("cls");
                            system("color 9f");
                            cout<<"\n\n\n\n\n\n";
                            cout<<"\t\t\t Good Bye\n";
                            cout<<"\n\n\n";
                            cout<<"\t\t\t See You Soon";
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                            exit(0);
						}
						break;
					}

				}
    }
    else {
        if(counter==3) {
            exit(1);
	    }
	    else {
            ++counter;
	    }
		cout<<"\n\n\n\t\t\t WRONG PASSWORD "<<endl;
		cout<<"\n\n\t\t\t PRESS ANY KEY TO RE-ENTER PASSWORD ";
		getch();
	}
return 0;
}

