// Header Files
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<string>
#include<process.h>
#include<windows.h>
#define max 10
#define datafile "student.txt"
#define indexfile "index.txt"
#define max_retry 3
using namespace std;
fstream stdfile, indfile;
int i,indsize;
char buffer[100];
void StudentLogin();
void AdminLogin();
bool AuthenticateUser();
// User Class
class Student {
char dusn[15],name[20],branch[5],sem[5],fname[20],mname[20],dob[15],telno[15],attend[5];
int total,fsmarks,stmarks,webmarks,ele1marks,ele2marks,stlmarks,fslmarks,madlmarks;
public:
void add();
void tot();
void pack();
int search(char*);
void recDisp(int);
void remove(int);
void dataDisp();
void Segregation();
void unpack();
};
//Index Class
class index{
public:
char iusn[15],addr[5];
void initial();
void write();
}in, id[max];
void index::initial(){
indfile.open(indexfile,ios::in);
if(!indfile)
{
indsize=0;
return;
}
for(indsize=0;;indsize++)
{
indfile.getline(id[indsize].iusn,15,'|');
indfile.getline(id[indsize].addr,5,'\n');
if(indfile.eof())
break;
}
indfile.close();
}
// function to open file
void open(fstream &sfile,char* fn,std::_Ios_Openmode mode){
sfile.open(fn,mode);
if(!sfile)
{
cout<<"Unable to open the file\n";
}
}
// function to write
void index::write(){
open(indfile,indexfile,ios::out);
for(i=0;i<indsize;i++)
indfile<<id[i].iusn<<"|"<<id[i].addr<<"\n";
indfile.close();
}
// function to add
void Student::add()
{
int k;
cout<<"\t\t\t -------------------------------"<<"\n";
cout<<"\t\t\t ENTER THE STUDENT DETAILS"<<"\n";
 cout<<"\t\t\t -------------------------------"<<"\n\n";
cout<<"\t\tENTER THE USN:";
cin>>dusn;
if(search(dusn)>=0)// uses binary search to check the entered dusn value is existing or not
{
    cout<<"USN is already present,we can't add to index file\n";
return;
}
for(i=indsize;i>0;i--)
{
 if(strcmp(dusn,id[i-1].iusn)<0)
id[i]=id[i-1];
 else
break;
}
open(stdfile,datafile,ios::app);
 cout<<"\t\tNAME OF THE STUDENT: ";
 cin.ignore();
 cin.getline(name,20);
 cout<<"\t\tFATHER'S NAME: ";
 cin.getline(fname,20);
 cout<<"\t\tMOTHER'S NAME: ";
 cin.getline(mname,20);
 cout<<"\t\tDATE OF BIRTH(DD/MM/YYYY):";
 cin>>dob;
 cout<<"\t\tTELEPHONE NUMBER: ";cin>>telno;
 cout<<"\t\tBRANCH(ISE): "; cin>>branch;
 cout<<"\t\tSEMESTER(6):";cin>>sem;
 cout<<"\t\tDAYS PRESENT: ";cin>>attend;
 cout<<"\t\t\t -----------------------------"<<"\n";
 cout<<"\t\t\t ENTER THE MARKS"<<"\n";
 cout<<"\t\t\t -----------------------------"<<"\n\n";
 cout<<"\t\t\t FILE STRUCTURES(18IS61):";cin>>fsmarks;
 cout<<"\t\t\t SOFTWARE TESTING(18IS62):";cin>>stmarks;
 cout<<"\t\t\t WEB TECHNOLOGY AND ITS APPLICATIONS (1 8CS63):";cin>>webmarks;
cout<<"\t\t\t DATA MINING AND DATA WAREHOUSE(18CS641) OR CLOUD COMPUTING AND ITS APPLICATIONS(18CS643):";cin>>ele1marks;
 cout<<"\t\t\t ADVANCED LINEAR ALGEBRA(18MAT653) OR SUPPLY CHAIN MANAGEMENT(18ME653):";cin>>ele2marks;
 cout<<"\t\t\t SOFTWARE TESTING LABORATORY(18ISL66):";cin>>stlmarks;
 cout<<"\t\t\t FILE STRUCTURES LABORATORY WITH MINI PROJECT(18ISL67):";cin>>fslmarks;
 cout<<"\t\t\t MOBILE APPLICATION DEVELOPMENT(18CSMP68): ";cin>>madlmarks;
 cout<<"\n\n";
 tot();
 pack();
 stdfile.seekg(0,ios::end);
 k=stdfile.tellg();
 stdfile<<buffer<<endl;
strcpy(id[i].iusn,dusn);
sprintf(id[i].addr,"%d",k);
indsize++;
 }
// function to calculate total
void Student::tot()
{
 
total=fsmarks+stmarks+webmarks+ele1marks+ele2marks+stlmarks+fslmarks+madlmarks;
}
// function to pack
void Student::pack()
{
strcpy(buffer,dusn); strcat(buffer,"|");
strcat(buffer,name); strcat(buffer,"|");
strcat(buffer,fname); strcat(buffer,"|");
strcat(buffer,mname); strcat(buffer,"|");
strcat(buffer,dob); strcat(buffer,"|");
strcat(buffer,telno); strcat(buffer,"|");
strcat(buffer,branch); strcat(buffer,"|");
strcat(buffer,sem); strcat(buffer,"|");
strcat(buffer,attend);strcat(buffer,"|");
char num_char[20 + sizeof(char)];
std::sprintf(num_char,"%d",fsmarks);
strcat(buffer,num_char);strcat(buffer,"|");
std::sprintf(num_char,"%d",stmarks);
strcat(buffer,num_char);strcat(buffer,"|");
std::sprintf(num_char,"%d",webmarks);
strcat(buffer,num_char);strcat(buffer,"|");
std::sprintf(num_char,"%d",ele1marks);
strcat(buffer,num_char);strcat(buffer,"|");
std::sprintf(num_char,"%d",ele2marks);
strcat(buffer,num_char);strcat(buffer,"|");
std::sprintf(num_char,"%d",fslmarks);
strcat(buffer,num_char);strcat(buffer,"|");
std::sprintf(num_char,"%d",stlmarks);
strcat(buffer,num_char);strcat(buffer,"|");
std::sprintf(num_char,"%d",madlmarks);
strcat(buffer,num_char);strcat(buffer,"|");
 std::sprintf(num_char, "%d", total);
strcat(buffer,num_char);strcat(buffer,"|");
}
// binary search algorithm
int Student:: search(char* fusn)
{
int low=0,high=indsize-1;
int mid;
while(low<=high)
{
mid=(low+high)/2;
if(strcmp(fusn,id[mid].iusn)==0)
return mid;
else if(strcmp(fusn,id[mid].iusn)>0)
low=mid+1;
else
high=mid-1;
}
return -1;
}
// function to record display
void Student::recDisp(int pos)
{
open(stdfile,datafile,ios::in);
stdfile.seekg(atoi(id[pos].addr),ios::beg);   //atoi is a pre defined func its used to convert a string value to int value
cout<<"The searched record details are:\n";
 cout<<"USN"<<"\t "<<"NAME"<<"\t "<<" FATHER'S NAME" <<"\t "<<" MOTHER'S NAME"<<"\t "<<"DOB"<<"\t "<<" PHONE NO"<<"\t "<<"BRANCH"<<"\t "<<" SEM"<<"\t"<<"ATTENDANCE"<<" FS"<<" ST"<<" WEB"<<" ELE1"<<" ELE2"<<" STL"<<" FSL"<<" MADL"<<" TOTAL"<<endl;
unpack();cout<<"\n";
}
// function to remove
void Student::remove(int pos)
{
open(stdfile,datafile,ios::in|ios::out);
stdfile.seekg(atoi(id[pos].addr),ios::beg);
stdfile.put('$');
for(i=pos;i<indsize;i++)
id[i]=id[i+1];
indsize--; 
cout<<"Record removed Successfully";
}
// function to data display
void Student::dataDisp()
{
cout<<setiosflags(ios::left);
 cout<<"USN"<<"\t "<<" NAME"<<"\t "<<" FATHER'S NAME" <<"\t "<<" MOTHER'S NAME"<<"\t "<<"DOB"<<"\t "<<" PHONE NO"<<"\t "<<"BRANCH"<<"\t "<<" SEM"<<"\t"<<"ATTENDANCE"<<" FS"<<" ST"<<" WEB"<<" ELE1"<<" ELE2"<<" STL"<<" FSL"<<" MADL"<<" TOTAL"<<endl;
while(1)
{
unpack();
if(stdfile.eof())
break;
}
cout<<"\n";
}
// function to unpack
void Student::unpack()
{
stdfile.getline(buffer,400,'\n');
i=0;
if(buffer[i]!='$')
{
cout<<"\n";
while(buffer[i]!='\0')
{
if(buffer[i]=='|')
cout<<"\t ";
cout<<buffer[i];
i++;
}
}
}
// function of introduction
void Intro()
{
 for(int i=1;i<=100;++i)
 {
 Sleep(5);
 system("cls");
 cout<<"\n\n\n\n\n\n\n\n\n\n\t\tLOADING "<<i<<"%";
 if(i==100)
 {
 Sleep(1000);
 }
 }
system("cls");
cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\tREPORT CARD MANAGEMENT SYSTEM";
cout<<"\n\n\n\n\n\n\t\tBy:\tSTHUTI J (1GA19IS053)\n\t\t\tRAKSHAK G D (1GA19IS044)";
 Sleep(2000);
 system("cls");
}
// function of main menu
void Segregation()
{
 int authChoice;
 cout<<"\n\n\n\n\n";
 cout<<"\t\t\t ---------------"<<"\n";
cout<<"\t\t\t MAIN MENU"<<"\n";
 cout<<"\t\t\t ---------------"<<"\n\n\n";
 cout<<"\t\t\t AUTHENTICATE AS"<<"\n\n";
 cout<<"\t\t ----------------------------------------"<<"\n";
 cout<<"\t\t 1. TEACHER\t2. STUDENT\t"<<"\n";
 cout<<"\t\t ----------------------------------------"<<"\n";
 cout<<"\t\t (PRESS 3 TO EXIT)"<<"\n\n\n";
 cout<<"\t\t ENTER AN OPTION: ";
 cin>>authChoice;
 switch(authChoice)
{
 case 1:
 AdminLogin();
 break;
 case 2:
 StudentLogin();
 break;
 case 3: exit(0);
 break;
 default: cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tWRONG OPTION!";
 cout<<"\n\n\n\n\n\n\n\n";
 system("PAUSE");
 }
 getch();
}
// main function
int main()
{
in.initial();
system("title REPORT CARD MANAGEMENT SYSTEM");
 system("COLOR 0B");
Intro();
 Segregation();
 getch();
 return 0;
}
// function of student login
void StudentLogin()
{
 while(true){
 int ch,flag;
 Student student;
 char susn[15], a[8];
 cout<<"\n\n\n\n\n\n\n";
 cout<<"\t\t\t\t ------------"<<"\n";
 cout<<"\t\t\t\t MENU"<<"\n";
 cout<<"\t\t\t\t ------------"<<"\n";
 cout<<"\t\t\t 1. SEARCH FOR YOUR RECORD"<<"\n";
 cout<<"\t\t\t 2. DISPLAY CLASS RESULT"<<"\n";
 cout<<"\t\t\t 3. GO TO MAIN MENU"<<"\n\n";
 cout<<"\t\t\t ENTER YOUR OPTION: ";
cin>>ch;
switch(ch)
{
 case 1: cout<<"Enter the USN to be searched: \n";
cin>>susn;
flag=student.search(susn);
if(flag==-1)
cout<<"Record Not found\n";
else
student.recDisp(flag);
break;
case 2:open(stdfile,datafile,ios::in);
cout<<endl<<"LIST OF RECORDS: \n\n";
student.dataDisp();
break;
 case 3: Segregation();break;
 default: cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tWRONG OPTION!";
 cout<<"\n\n\n\n\n\n\n\n";
 system("PAUSE");
}
stdfile.close();
 }
}
// function of admin login (teacher’s Login)
void AdminLogin()
{
 int ch,pos,flag,retryCounter=0;
char susn[15];
Student student;
in.initial();
 while(true){
 if(!AuthenticateUser()){
 cout<<"\n\n\t\t\t\t\tAuthentication failed"<<endl;
 retryCounter++;
 if(retryCounter>=max_retry){
 cout<<"Maxium retry reached!!! "<<endl;
 exit(0);
 }
 continue;
 }
 break;
 }
while(true){
 cout<<"\n\n\n\n\n\n";
 cout<<"\t\t\t\t ------------"<<"\n";
 cout<<"\t\t\t\t MENU"<<"\n";
 cout<<"\t\t\t\t ------------"<<"\n";
 cout<<"\t\t\t 1. ADD A NEW RECORD"<<"\n";
 cout<<"\t\t\t 2. DISPLAY ALL THE RECORDS"<<"\n";
 cout<<"\t\t\t 3. SEARCH A RECORD"<<"\n";
 cout<<"\t\t\t 4. DELETE A RECORD"<<"\n";
 cout<<"\t\t\t 5. EXIT"<<"\n";
 cout<<"\t\t\t 6. GO TO MAIN MENU"<<"\n\n";
 cout<<"\t\t\t ENTER YOUR OPTION: ";
cin>>ch;
switch(ch)
{
case 1: student.add();
in.write();
break;
case 2: open(stdfile,datafile,ios::in);
cout<<endl<<" STUDENT DETAILS:\n\n";
student.dataDisp();
break;
case 3: cout<<"Enter the USN to be searched: \n";
cin>>susn;
flag=student.search(susn);
if(flag==-1)
cout<<"Record Not found\n";
else
student.recDisp(flag);
break;
case 4: cout<<"Enter the USN to delete from the record: \n";
cin>>susn;
pos=student.search(susn);
if(pos==-1)
cout<<"USN not found\n";
else
{
student.remove(pos);
in.write();
}
break;
case 5: exit(0);break;
case 6: Segregation();break;
default: cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tWRONG OPTION!";
 cout<<"\n\n\n\n\n\n\n\n";
 system("PAUSE");
}
stdfile.close();
 }
}
bool AuthenticateUser()
{
 char o_username[20];
string pass = "";
char ch;
cout.width(25);
cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t\tENTER THE USERNAME: ";cin>>o_username;
cout<<"\n\n\t\t\t\t\tENTER THE PASSWORD: ";
ch = _getch();
while (ch != 13) {
pass.push_back(ch);
cout << '*';
ch = _getch();
}
 if (pass == "global") 
return true;
 return false;
}
