#include <iostream>
#include <fstream>
#define FILENAME "empFile.txt"
using namespace std;

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

class WorkManager
{
public:
    int m_EmpNum;  // 记录职工人数
    Worker ** m_EmpArray;  // 职工数组指针
    bool m_FileIsEmpty;

    WorkManager()
    {
        ifstream ifs;
        ifs.open(FILENAME,ios::in);  //读文件

        if(!ifs.is_open())
        {
            cout<<"文件不存在"<<endl;
            //初始化属性
            //初始化记录人数
            this->m_EmpNum=0;
            //初始化数组指针
            this->m_EmpArray=NULL;
            //初始化文件是否为空
            this->m_FileIsEmpty=true;
            ifs.close();
            return;
        }

        //文件存在，数据为空
        char ch;
        ifs >> ch;
        if(ifs.eof())
        {
            //文件为空
            cout<<"文件为空"<<endl;
            //初始化记录人数
            this->m_EmpNum=0;
            //初始化数组指针
            this->m_EmpArray=NULL;
            //初始化文件是否为空
            this->m_FileIsEmpty=true;
            ifs.close();
            return;
        }

        //文件存在，并且记录数据
        this->m_FileIsEmpty=false;
        int num=this->get_EmpNum();
        cout<<"职工人数为："<<num<<endl;
        this->m_EmpNum=num;

        //开辟空间
        this->m_EmpArray=new Worker*[this->m_EmpNum];
        //将文件中的数据存到数组中
        this->init_Emp();


    }

    ~WorkManager()
    {
        if(this->m_EmpArray!=NULL)
        {
            delete [] this->m_EmpArray;
            this->m_EmpArray=NULL;
        }
    }

    //显示菜单
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

    //添加职工
    void add_Emp()
    {
        cout<<"请输入添加职工数量："<<endl;
        int addNum=0;
        cin >>addNum;

        if(addNum>0) {
            // 计算添加新空间大小
            // 新空间大小=原来记录人数+新增人数
            int newSize = this->m_EmpNum + addNum;

            // 开辟新空间
            Worker **newSpace = new Worker *[newSize];

            // 将原来空间下的数据，拷贝到新空间
            if (this->m_EmpArray != NULL)
            {
                for(int i=0;i<this->m_EmpNum;i++)
                {
                    newSpace[i]=this->m_EmpArray[i];
                }
            }

            // 批量添加新数据
            for(int i=0;i<addNum;i++)
            {
                int id;      // 职工编号
                string name;  // 职工姓名
                int dSelect;  // 部门选择

                cout<<"请输入第"<<i+1<<"个新职工编号："<<endl;
                cin >>id;

                cout<<"请输入第"<<i+1<<"个新职工姓名："<<endl;
                cin >>name;

                cout<<"请选择职工岗位："<<endl;
                cout<<"1.普通职工"<<endl;
                cout<<"2.经理"<<endl;
                cout<<"3.老板"<<endl;
                cin>>dSelect;

                Worker * worker=NULL;
                switch (dSelect)
                {
                    case 1:
                        worker=new Employee(id,name,1);
                        break;
                    case 2:
                        worker=new Manager(id,name,2);
                        break;
                    case 3:
                        worker=new Boss(id,name,3);
                        break;
                    default:
                        break;
                }
                // 将创建的职工保存到数组中
                newSpace[this->m_EmpNum+i]=worker;
            }
            // 释放原有空间
            delete [] this->m_EmpArray;

            //更改新空间指向
            this->m_EmpArray=newSpace;

            //更新新的职工人数
            this->m_EmpNum=newSize;

            //添加添加成功
            cout<<"成功添加了"<<addNum<<"名新职工"<<endl;

            //保存数据到文件中
            this->save();

            //更新职工不为空标志
            this->m_FileIsEmpty=false;

        }else{
            cout<<"输入数据有误"<<endl;
        }

        //按任意键清屏，回到上一级目录
        system("pause");
        system("cls");
    }

    //保存职工
    void save()
    {
        ofstream ofs;
        ofs.open(FILENAME,ios::out); //用输出的方式打开文件 --写文件

        //将每个人的信息写入文件中
        for(int i=0;i<this->m_EmpNum;i++)
        {
            ofs<<this->m_EmpArray[i]->m_Id<<" "
               <<this->m_EmpArray[i]->m_Name<<" "
               <<this->m_EmpArray[i]->m_DeptId<<endl;
        }

        //关闭文件
        ofs.close();
    }

    //获取文件中的职工数
    int get_EmpNum()
    {
        ifstream ifs;
        ifs.open(FILENAME,ios::in); //打开文件 读文件

        int id;
        string name;
        int dId;

        int num=0;
        while (ifs>>id && ifs>>name &&ifs>>dId)
        {
            num++;
        }
        return num;


    }

    //初始化职工
    void init_Emp()
    {
        ifstream ifs;
        ifs.open(FILENAME,ios::in);

        int id;
        string name;
        int dId;

        int index=0;
        while (ifs>>id && ifs>>name && ifs>>dId)
        {
            Worker *worker=NULL;
            if(dId==1)   // 普通职工
            {
                worker=new Employee(id,name,dId);
            } else if(dId==2)  // 经理
            {
                worker=new Manager(id,name,dId);
            } else if(dId==3)
            {
                worker=new Boss(id,name,dId);
            }
            this->m_EmpArray[index]=worker;
            index++;
        }
        ifs.close();
    }

    //显示职工
    void show_Emp()
    {
        if(this->m_FileIsEmpty)
        {
            cout<<"文件不存在或记录为空"<<endl;
        } else{
            for(int i=0;i<this->m_EmpNum;i++)
            {
                this->m_EmpArray[i]->showInfo();
            }
        }
        system("pause");
        system("cls");
    }

    //删除职工
    void Del_Emp()
    {
        if(this->m_FileIsEmpty)
        {
            cout<<"文件不存在或为空"<<endl;
        }
        else{
            // 按照职工的编号删除
            cout<<"请输入要删除的职工编号："<<endl;
            int id=0;
            cin>>id;

            int index=this->IsExist(id);
            if(index!=-1) //说明职工存在，并且要删除掉index位置上的职工
            {
                for(int i=index;i<this->m_EmpNum-1;i++)
                {
                    this->m_EmpArray[i]=this->m_EmpArray[i+1];
                }
                this->m_EmpNum--; //更新数组中记录人员个数
                //数据同步到文件
                this->save();

                cout<<"删除数据成功"<<endl;
            }
            else{
                cout<<"删除失败，未找到该职工。"<<endl;
            }
        }
        //按任意键清屏
        system("pause");
        system("cls");
    }

    //
    int IsExist(int id)
    {
        int index=-1;
        for(int i=0;i<this->m_EmpNum;i++)
        {
            if(this->m_EmpArray[i]->m_Id==id)
            {
                index=i;
                break;
            }
        }
        return index;

    }
    void exitsystem()
    {
        cout<<"欢迎下次再来。"<<endl;
        system("pause");
        exit(0);
    }
};




int main() {
    //Worker * worker = new Employee(1,"jack",1);
    //worker->showInfo();
    //delete worker;

    //worker=new Manager(2,"wqk",2);
    //worker->showInfo();
    //delete worker;

    //worker=new Boss(3,"lhj",3);
    //worker->showInfo();
    //delete worker;

    int choice;
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
            wm.add_Emp();
            break;
        case 2:
            wm.show_Emp();
            break;
        case 3:
            wm.Del_Emp();
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
