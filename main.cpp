#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include "planet.h"
#include "prototypes.h"

int num;

void edit_elem(Planet **pPlanet, int num);

int main(){
    const char* file="/Users/arsenvardumyan/CLionProjects/Lab_2(1)/sunsys.txt";
    num = 0;
    Planet **planets = new Planet*[9];
    while(true){
        switch(menu()){
            case 1:
                read_db(file, planets, num);
                break;
            case 2:
                write_db(file, planets, num);
                break;
            case 3:
                sort_db(planets, num);
                break;
            case 4:
                add(planets, num);
                break;
            case 5:
                cout<<planets;
                break;
            case 6:
                write_pl(file,planets, num);
                break;
            case 7:
                read_pl(file,planets, num);
                break;
            case 8:
                delete_elem(planets, num);
                break;
            case 9:
                edit_elem(planets, num);
                break;
            case 10:
                for (int i=0; i<num; ++i) delete planets[i];
                delete []planets;
                return 0;
            default:
                cout<<"Недопустимый номер операции"<<endl;
                break;
        }
    }
}

void edit_elem(Planet **pPlanet, int num) {
    if(num>0){
        cout<<"Введите номер планеты, которое надо редактировать:"<<endl;
        int i;
        cin>>i;

        cout<<"Введите что надо редактировать:"<<endl
            <<"1 - название"<<endl<<"2 - диаметр"
            <<endl<<"3 - наличие жизни"<<endl
            <<"4 - кол-во спутников"<<endl;

        int buff;
        cin>>buff;
        switch (buff){
            case 1:
                cout<<"Введите новое название планеты:"<<endl;
                char str[20];
                cin>>str;
                pPlanet[i-1]->set_name(str);
                break;
            case 2:
                cout<<"Введите новое значение диаметра:"<<endl;
                unsigned int diam;
                cin>>diam;
                pPlanet[i-1]->set_dim(diam);
                break;
            case 3:
                cout<<"Введите есть ли жизнь на планете:"<<endl;
                bool life;
                cin>>life;
                pPlanet[i-1]->set_life(life);
                break;
            case 4:
                cout<<"Введите новое кол-во спутников:"<<endl;
                unsigned int sp;
                cin>>sp;
                pPlanet[i-1]->set_sp_count(sp);
                break;
        }
    }
    else{
        cout<<"БД пуста..."<<endl;
    }
}

ostream& operator << (ostream& out, Planet** pPlanet){
    if (num>0){
        cout<<endl;
        cout<<left<<setw(5)<<"№"<<setw(22)<<"Планета"<<setw(20)<<"Диаметр"<<setw(15)<<"Жизнь"<<setw(15)<<"Кол-во спутников"<<endl;
        for (int i=0; i<num; ++i) {
            cout<<(i+1)<<") ";
            pPlanet[i]->print();
        }
        cout<<endl;
    }
    else{
        cout<<"БД пуста..."<<endl;
    }
    return out;
}

void write_pl(const char *filename, Planet **pPlanet, int num) {
    ofstream file(filename,ios_base::app);
    if(!file){
        cout<<"Файл не найден..."<<endl;
    }
    else{
        cout<<"Введите название планеты, которое нужно добавить в файл:"<<endl;
        char str[20];
        cin>>str;
        int i;
        for(i=0; i<num; ++i){
            if(strcmp(str, pPlanet[i]->get_name())==0) break;
        }
        if(i!=num){
            file<<pPlanet[i]->get_name()<<" ";
            file<<pPlanet[i]->get_dim()<<" ";
            file<<pPlanet[i]->get_life()<<" ";
            file<<pPlanet[i]->get_sp_count();
            file<<'\n';
        }
        file.close();
    }
}

void read_pl(const char *filename,Planet **pPlanet, int &num) {
    ifstream file(filename);
    if (!file){
        cout<<"Файл не найден..."<< endl;
    }
    else {
        int flag=1;
        char buff[20];
        const char *sep = " ";
        char *ptr;
        cout << "Введите название планеты, информацию о которой нужно импортировать:" << endl;
        char str[20];
        cin >> str;

        for (int i = 0; i < num; ++i) {
            if (strcmp(str, pPlanet[i]->get_name()) == 0) flag = 0;
        }

        if (flag && num<10) {
            while (file.getline(buff, 20)){
                ptr = strtok(buff, sep);
                if (strcmp(ptr,str)==0){
                    pPlanet[num]=new Planet();
                    pPlanet[num]->set_name(ptr);
                    ptr = strtok(0,sep);
                    pPlanet[num]->set_dim(StrToInt(ptr));
                    ptr = strtok(0,sep);
                    pPlanet[num]->set_life(StrToInt(ptr));
                    ptr = strtok(0,sep);
                    pPlanet[num]->set_sp_count(StrToInt(ptr));
                    ++num;
                    break;
                }
            }
            file.close();
        }
    }
}

void operator >>(ifstream& file, Planet** pPlanet){
    int flag;
    char buff[20];
    const char *sep = " ";
    char* ptr;

    while (file.getline(buff, 20)){
        flag=1;
        ptr = strtok(buff, sep);
        for(int i=0; i<num; ++i){
            if (strcmp(ptr,pPlanet[i]->get_name())==0) flag=0;
        }
        if (flag && num<10){
            pPlanet[num]=new Planet();
            pPlanet[num]->set_name(ptr);
            ptr = strtok(0,sep);
            pPlanet[num]->set_dim(StrToInt(ptr));
            ptr = strtok(0,sep);
            pPlanet[num]->set_life(StrToInt(ptr));
            ptr = strtok(0,sep);
            pPlanet[num]->set_sp_count(StrToInt(ptr));
            ++num;
        }
    }
}

void write_db(const char *filename, Planet **pPlanet, int num) {
    ofstream file(filename);
    if(!file){
        cout<<"Файл не найден..."<<endl;
    }
    else{
        for(int i=0; i<num ;++i){
            file<<pPlanet[i]->get_name()<<" ";
            file<<pPlanet[i]->get_dim()<<" ";
            file<<pPlanet[i]->get_life()<<" ";
            file<<pPlanet[i]->get_sp_count();
            file<<'\n';
        }
        file.close();
    }
}

void sort_db(Planet **pPlanet, int num) {
    int flag=0;
    for (int i=0; i<num-1; ++i){
        flag=0;
        for (int j=0; j<num-i-1; ++j){
            if (*pPlanet[j+1] < *pPlanet[j]) {
                swap(pPlanet[j], pPlanet[j + 1]);
                flag = 1;
            }
        }
        if(flag==0) break;
    }
    cout<<"Список отсортирован..."<<endl;
}

int menu(){
    cout<<" ============== ГЛАВНОЕ МЕНЮ ============== \n";
    cout<<"1 - чтение БД  «Солнечная система» из файла"<<endl;
    cout<<"2 - запись БД  «Солнечная система» в файл"<<endl;
    cout<<"3 - сортировка БД"<<endl;
    cout<<"4 - добавить планету в БД"<<endl;
    cout<<"5 - вывод БД на экран"<<endl;
    cout<<"6 - ввод планеты в файл"<<endl;
    cout<<"7 - вывод планеты из файл"<<endl;
    cout<<"8 - удалить планету из БД"<<endl;
    cout<<"9 - редактирование элемента"<<endl;
    cout<<"10 - выход"<<endl;
    cout<<"Для выбора операции введите цифру от 1 до 10"<< endl;
    int resp;
    cin>>resp;
    cin.clear();
    cin.ignore(10,'\n');
    return resp;
}

void delete_elem(Planet **pPlanet, int &num) {
    if(num>0){
        cout<<"Введите имя планеты:"<<endl;
        char buff[20];
        cin>>buff;
        int i;
        for (i=0; i<num; ++i){
            if (strcmp(buff,pPlanet[i]->get_name())==0) {
                for(int j=i; j<num-1; ++j){
                    pPlanet[j]=pPlanet[j+1];
                }
                pPlanet[num-1]= nullptr;
                break;
            }
        }
        if(i==num) cout<<"Планета с таким названием не найдена..."<<endl;
        else{
            cout<<"Планета удалена..."<<endl;
            --num;
        }
    }
    else cout<<"Бд пуста..."<<endl;
}

void read_db(const char* filename, Planet** pPlanet, int& num){
    ifstream file(filename);
    if (!file){
        cout<<"Файл не найден..."<< endl;
    }
    else{
        file>>pPlanet;
        file.close();
    }
}

int StrToInt(char *s){
    int temp = 0; // число
    int i = 0;
    int sign = 0; // знак числа 0- положительное, 1 — отрицательное
    if (s[i] == '-')
    {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39)
    {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return(temp);
}

void add(Planet **pPlanet, int& num){
    char buff[20];
    cout<<"Введите имя планеты: "<<endl;
    cin>>buff;

    int i;
    int flag = 1;

    for (i=0; i<num; ++i) if(strcmp(buff, pPlanet[i]->get_name())==0) flag = 0;

    if (flag == 1 && num<10){
        pPlanet[num] = new Planet();
        pPlanet[num]->set_name(buff);
        cout<<"Введите ее диаметр: "<<endl;
        cin>>buff;
        pPlanet[num]->set_dim(StrToInt(buff));
        cout<<"Введите есть ли жизнь на планете: "<<endl;
        cin>>buff;
        pPlanet[num]->set_life(StrToInt(buff));
        cout<<"Введите кол-во спутников: "<<endl;
        cin>>buff;
        pPlanet[num]->set_sp_count(StrToInt(buff));
        ++num;
    }
    else cout<<"Планета с таким названием уже есть в БД..."<<endl;
}

//Mercury 4878 0 0
//Venus 12104 0 0
//Earth 12774 1 1
//Mars 6786 1 2
//Jupiter 142796 0 16
//Saturn 120000 0 17
//Uranus 51108 0 5
//Neptune 49600 0 2
//Pluto 2280 0 1
