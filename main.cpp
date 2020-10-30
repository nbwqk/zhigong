#include <iostream>
#include <fstream>
using namespace std;

class WorkManager
{
public:
    WorkManager()
    {

    }

    ~WorkManager()
    {

    }

    void show_menu()
    {
        cout << "********************************************" << endl;
        cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
        cout << "*************  0.�˳��������  *************" << endl;
        cout << "*************  1.����ְ����Ϣ  *************" << endl;
        cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
        cout << "*************  3.ɾ����ְְ��  *************" << endl;
        cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
        cout << "*************  5.����ְ����Ϣ  *************" << endl;
        cout << "*************  6.���ձ������  *************" << endl;
        cout << "*************  7.��������ĵ�  *************" << endl;
        cout << "********************************************" << endl;
        cout << endl;
    }

    void exitsystem()
    {
        cout<<"��ӭ�´�������"<<endl;
        system("pause");
        exit(0);
    }
};

class Worker
{
public:
    int m_Id;
    string m_Name;
    int m_DeptId;

    virtual void showInfo()=0;

    virtual string getDeptName()=0;
};

class Employee: public Worker
{
public:
    Employee(int id,string name,int dId)
    {
        this->m_Id=id;
        this->m_Name=name;
        this->m_DeptId=dId;
    }
    void showInfo()
    {
        cout<<"ְ����ţ�"<<this->m_Id
            <<"\tְ��������"<<this->m_Name
            <<"\t��λ��"<<this->getDeptName()
            <<"\t��λְ����ɾ�����������"<<endl;
    }

    string getDeptName()
    {
        return string("Ա��");
    }
};

class Manager: public Worker
{
public:
    Manager(int id,string name,int dId)
    {
        this->m_Id=id;
        this->m_Name=name;
        this->m_DeptId=dId;
    }

    void showInfo()
    {
        cout<<"ְ����ţ�"<<this->m_Id
            <<"\tְ��������"<<this->m_Name
            <<"\t��λ��"<<this->getDeptName()
            <<"\t��λְ������ϰ彻�������񣬲����·������Ա��"<<endl;
    }

    string getDeptName()
    {
        return string("����");
    }
};

class Boss: public Worker
{
public:
    Boss(int id,string name,int dId)
    {
        this->m_Id=id;
        this->m_Name=name;
        this->m_DeptId=dId;
    }

    void showInfo()
    {
        cout<<"ְ����ţ�"<<this->m_Id
            <<"\tְ��������"<<this->m_Name
            <<"\t��λ��"<<this->getDeptName()
            <<"\t��λְ��ȫ�����˾"<<endl;
    }

    string getDeptName()
    {
        return string("�ܲ�");
    }
};
int main() {
    Worker * worker = new Employee(1,"jack",1);
    worker->showInfo();
    delete worker;

    worker=new Manager(2,"wqk",2);
    worker->showInfo();
    delete worker;

    worker=new Boss(3,"lhj",3);
    worker->showInfo();
    delete worker;

    int choice=0;
    while (true)
    {
        WorkManager wm;  // ʵ���������߶���
        wm.show_menu();  // ���ó�Ա����
        cout<<"����������ѡ��"<<endl;
        cin>>choice;
        switch (choice) {
        case 0:
            wm.exitsystem();
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            system("cls");
            break;
        }
    }
    system("pause");
    return 0;
}
