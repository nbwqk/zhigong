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
        cout << "*********  欢迎使用职工管理系统！ **********" << endl;
        cout << "*************  0.退出管理程序  *************" << endl;
        cout << "*************  1.增加职工信息  *************" << endl;
        cout << "*************  2.显示职工信息  *************" << endl;
        cout << "*************  3.删除离职职工  *************" << endl;
        cout << "*************  4.修改职工信息  *************" << endl;
        cout << "*************  5.查找职工信息  *************" << endl;
        cout << "*************  6.按照编号排序  *************" << endl;
        cout << "*************  7.清空所有文档  *************" << endl;
        cout << "********************************************" << endl;
        cout << endl;
    }

    void exitsystem()
    {
        cout<<"欢迎下次再来。"<<endl;
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
        cout<<"职工编号："<<this->m_Id
            <<"\t职工姓名："<<this->m_Name
            <<"\t岗位："<<this->getDeptName()
            <<"\t岗位职责：完成经理交给的任务"<<endl;
    }

    string getDeptName()
    {
        return string("员工");
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
        cout<<"职工编号："<<this->m_Id
            <<"\t职工姓名："<<this->m_Name
            <<"\t岗位："<<this->getDeptName()
            <<"\t岗位职责：完成老板交给的任务，并且下发任务给员工"<<endl;
    }

    string getDeptName()
    {
        return string("经理");
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
        cout<<"职工编号："<<this->m_Id
            <<"\t职工姓名："<<this->m_Name
            <<"\t岗位："<<this->getDeptName()
            <<"\t岗位职责：全面管理公司"<<endl;
    }

    string getDeptName()
    {
        return string("总裁");
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
        WorkManager wm;  // 实例化管理者对象
        wm.show_menu();  // 调用成员函数
        cout<<"请输入您的选择："<<endl;
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
