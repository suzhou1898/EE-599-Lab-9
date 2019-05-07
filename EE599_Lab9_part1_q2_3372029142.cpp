#include<iostream>
#include<fstream>
#include<string>
#include<pthread.h>
#include<algorithm>
#define NUM_THREADS 2

//you can include more files
using namespace std;
string *menu;
int k=0;

/*your code*/
/*...*///you can add more functions here
void initialize_menu(istream & infile,int& k) {
    string s;
    string ::iterator ptr;
    while(getline(infile,s)){
        k++;
    }
    infile.clear();
    infile.seekg(0,ios::beg);
    menu=new string [k];
    for(int i=0;i<k;i++){
        getline(infile,menu[i]);
        for(int j=0;j<menu[i].length();j++){
            ptr=find(menu[i].begin(),menu[i].end(),'\r');
            menu[i].erase(ptr);

        }
    }
}

int find(string s){
    int num1,num2;
    int j;
    string ::iterator ptr;
    ptr=s.begin();
    for ( j = 0; j < s.length()+1; j++) {
        num1 = count(ptr, ptr+j, '[');
        num2 = count(ptr, ptr+j, ']');
        if(num1==num2 && num1!=0){
            break;
        }
    }
    return j-1;
}

string decode(string s){
    int n=0;
    string temp;
    string str1;
    string str2;
    for(int j=0;j<s.length();j++){
        while(s[j]>='0' && s[j]<='9'){
            for(int t=0;t<n;t++){
                str1.append(str2);
            }
            str2.clear();
            n=s[j]-'0';
            j++;
        }
        str2.append(1,s[j]);
    }

    for(int t=0;t<n;t++){
        str1.append(str2);
    }

    return str1;
}

string decodeString(string s) {
    /*Decode operation for string*/
    /*your code*/
    string flag1="[";
    string flag2="]";
    string temp;
    string s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11;
    int pos1;
    int pos2;
    int pos3;
    int pos4;
    int pos5;
    int pos6;
    int pos7;

    pos1=s.find_first_of(flag1);
    if(pos1!=s.npos) {

        pos2 = find(s);
        s1 = s.substr(0, pos2 + 1);
        s2 = s.substr(pos2 + 1);
        pos3 = s1.find_first_of(flag2);
        if (pos3 != pos2) {
            s3=s1.substr(0,pos3);
            pos4=s3.find_last_of(flag1);
            s4=s1.substr(0,pos4);
            pos5=s4.find_last_of(flag1);
            s5=s1.substr(pos5);

            pos6=find(s5);
            s9=s1.substr(0,pos5);
            pos7=pos6+s9.length();

            s6=s5.substr(1,pos6-1);
            s7=decodeString(s6);

            s8=s1.replace(s1.begin()+pos5,s1.begin()+pos7+1,s7);

            s9=decodeString(s8);

            s10.append(s9);
            if(s2.length()!=0){
                s11=decodeString(s2);
                s10.append(s11);
            }

            return s10;

        } else {
            s3 = s1.substr(pos1 + 1, pos2 - pos1 - 1);
            s3 = decode(s3);
            s1 = s1.replace(s1.begin() + pos1 + 1, s1.begin() + pos2, s3);

            s1.erase(s1.find_first_of(flag1), 1);
            s1.erase(s1.find_first_of(flag2), 1);
            s5 = decode(s1);
            s6.append(s5);
            s5.clear();
            if(s2.length()!=0){
                s5=decodeString(s2);
            }
            s6.append(s5);
            return s6;
        }
    }
    else{
        s1=decode(s);
        s6.append(s1);
        return s6;
    }
}

//hint: you may need a function pointer here, void* decodeString(void *arg){/**/}
void print_menu(ofstream & outfile,int& k) {
    /*write menu to output file*/
    /*your code*/
    for(int i=0;i<k;i++){
        outfile<<menu[i]<<endl;
    }

}

void *divide(void *arg){
    int i=(long) arg;
    if(k%2!=0){
        if(i==0){
            for(int j=0;j<(k-1)/2+1;j++){
                menu[j]=decodeString(menu[j]);

            }
        }
        else if(i==1){
            for(int j=(k-1)/2+1;j<k;j++){
                menu[j]=decodeString(menu[j]);
            }
        }
    }
    else{
        if(i==0){
            for(int j=0;j<(k-1)/2+1;j++){
                menu[j]=decodeString(menu[j]);
            }
        }
        else if(i==1){
            for(int j=(k-1)/2+1;j<k;j++){
                menu[j]=decodeString(menu[j]);
            }
        }
    }

}


int main(int argc, char **argv) {
    ifstream infile;
    infile.open("input.txt");
    initialize_menu(infile,k);
    infile.close();

    int start=clock();
    pthread_t tids[NUM_THREADS];
    pthread_create(&tids[0],NULL,divide,(void *)0);
    pthread_create(&tids[1],NULL,divide,(void *)1);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    int end=clock();

    ofstream outfile;
    outfile.open("part1_q2_out.txt");
    print_menu(outfile,k);
    outfile.close();
    cout<<end-start<<endl;
    delete[]menu;
    pthread_exit(NULL);
}