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

class WorkManager
{
public:
    int m_EmpNum;  // ��¼ְ������
    Worker ** m_EmpArray;  // ְ������ָ��
    bool m_FileIsEmpty;

    WorkManager()
    {
        ifstream ifs;
        ifs.open(FILENAME,ios::in);  //���ļ�

        if(!ifs.is_open())
        {
            cout<<"�ļ�������"<<endl;
            //��ʼ������
            //��ʼ����¼����
            this->m_EmpNum=0;
            //��ʼ������ָ��
            this->m_EmpArray=NULL;
            //��ʼ���ļ��Ƿ�Ϊ��
            this->m_FileIsEmpty=true;
            ifs.close();
            return;
        }

        //�ļ����ڣ�����Ϊ��
        char ch;
        ifs >> ch;
        if(ifs.eof())
        {
            //�ļ�Ϊ��
            cout<<"�ļ�Ϊ��"<<endl;
            //��ʼ����¼����
            this->m_EmpNum=0;
            //��ʼ������ָ��
            this->m_EmpArray=NULL;
            //��ʼ���ļ��Ƿ�Ϊ��
            this->m_FileIsEmpty=true;
            ifs.close();
            return;
        }

        //�ļ����ڣ����Ҽ�¼����
        this->m_FileIsEmpty=false;
        int num=this->get_EmpNum();
        cout<<"ְ������Ϊ��"<<num<<endl;
        this->m_EmpNum=num;

        //���ٿռ�
        this->m_EmpArray=new Worker*[this->m_EmpNum];
        //���ļ��е����ݴ浽������
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

    //��ʾ�˵�
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

    //���ְ��
    void add_Emp()
    {
        cout<<"���������ְ��������"<<endl;
        int addNum=0;
        cin >>addNum;

        if(addNum>0) {
            // ��������¿ռ��С
            // �¿ռ��С=ԭ����¼����+��������
            int newSize = this->m_EmpNum + addNum;

            // �����¿ռ�
            Worker **newSpace = new Worker *[newSize];

            // ��ԭ���ռ��µ����ݣ��������¿ռ�
            if (this->m_EmpArray != NULL)
            {
                for(int i=0;i<this->m_EmpNum;i++)
                {
                    newSpace[i]=this->m_EmpArray[i];
                }
            }

            // �������������
            for(int i=0;i<addNum;i++)
            {
                int id;      // ְ�����
                string name;  // ְ������
                int dSelect;  // ����ѡ��

                cout<<"�������"<<i+1<<"����ְ����ţ�"<<endl;
                cin >>id;

                cout<<"�������"<<i+1<<"����ְ��������"<<endl;
                cin >>name;

                cout<<"��ѡ��ְ����λ��"<<endl;
                cout<<"1.��ְͨ��"<<endl;
                cout<<"2.����"<<endl;
                cout<<"3.�ϰ�"<<endl;
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
                // ��������ְ�����浽������
                newSpace[this->m_EmpNum+i]=worker;
            }
            // �ͷ�ԭ�пռ�
            delete [] this->m_EmpArray;

            //�����¿ռ�ָ��
            this->m_EmpArray=newSpace;

            //�����µ�ְ������
            this->m_EmpNum=newSize;

            //�����ӳɹ�
            cout<<"�ɹ������"<<addNum<<"����ְ��"<<endl;

            //�������ݵ��ļ���
            this->save();

            //����ְ����Ϊ�ձ�־
            this->m_FileIsEmpty=false;

        }else{
            cout<<"������������"<<endl;
        }

        //��������������ص���һ��Ŀ¼
        system("pause");
        system("cls");
    }

    //����ְ��
    void save()
    {
        ofstream ofs;
        ofs.open(FILENAME,ios::out); //������ķ�ʽ���ļ� --д�ļ�

        //��ÿ���˵���Ϣд���ļ���
        for(int i=0;i<this->m_EmpNum;i++)
        {
            ofs<<this->m_EmpArray[i]->m_Id<<" "
               <<this->m_EmpArray[i]->m_Name<<" "
               <<this->m_EmpArray[i]->m_DeptId<<endl;
        }

        //�ر��ļ�
        ofs.close();
    }

    //��ȡ�ļ��е�ְ����
    int get_EmpNum()
    {
        ifstream ifs;
        ifs.open(FILENAME,ios::in); //���ļ� ���ļ�

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

    //��ʼ��ְ��
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
            if(dId==1)   // ��ְͨ��
            {
                worker=new Employee(id,name,dId);
            } else if(dId==2)  // ����
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

    //��ʾְ��
    void show_Emp()
    {
        if(this->m_FileIsEmpty)
        {
            cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
        } else{
            for(int i=0;i<this->m_EmpNum;i++)
            {
                this->m_EmpArray[i]->showInfo();
            }
        }
        system("pause");
        system("cls");
    }

    //ɾ��ְ��
    void Del_Emp()
    {
        if(this->m_FileIsEmpty)
        {
            cout<<"�ļ������ڻ�Ϊ��"<<endl;
        }
        else{
            // ����ְ���ı��ɾ��
            cout<<"������Ҫɾ����ְ����ţ�"<<endl;
            int id=0;
            cin>>id;

            int index=this->IsExist(id);
            if(index!=-1) //˵��ְ�����ڣ�����Ҫɾ����indexλ���ϵ�ְ��
            {
                for(int i=index;i<this->m_EmpNum-1;i++)
                {
                    this->m_EmpArray[i]=this->m_EmpArray[i+1];
                }
                this->m_EmpNum--; //���������м�¼��Ա����
                //����ͬ�����ļ�
                this->save();

                cout<<"ɾ�����ݳɹ�"<<endl;
            }
            else{
                cout<<"ɾ��ʧ�ܣ�δ�ҵ���ְ����"<<endl;
            }
        }
        //�����������
        system("pause");
        system("cls");
    }

    //�޸�ְ��
    void Mod_Emp()
    {
        if(this->m_FileIsEmpty)
        {
            cout<<"�ļ������ڻ����ļ�����Ϊ��"<<endl;
        } else{
            cout<<"�������޸ĵ�ְ����ţ�"<<endl;
            int id;
            cin>>id;

            int ret=this->IsExist(id);
            if(ret!=-1)
            {
                //���ҵ���ŵ�ְ��
                delete this->m_EmpArray[ret];

                int newId;
                string newName;
                int dSelect;

                cout<<"�鵽��"<<id<<"��ְ������������ְ���ţ�"<<endl;
                cin>>newId;

                cout<<"��������������"<<endl;
                cin>>newName;

                cout<<"�������µĸ�λ��ţ�"<<endl;
                cout<<"1.��ְͨ��"<<endl;
                cout<<"2.����"<<endl;
                cout<<"3.�ϰ�"<<endl;
                cin>>dSelect;

                Worker * worker=NULL;
                switch (dSelect) {
                    case 1:
                        worker=new Employee(newId,newName,dSelect);
                        break;
                    case 2:
                        worker=new Manager(newId,newName,dSelect);
                        break;
                    case 3:
                        worker=new Boss(newId,newName,dSelect);
                        break;
                    default:
                        break;
                }
                this->m_EmpArray[ret]=worker;
                this->save();
            } else{
                cout<<"���޴���"<<endl;
            }
        }
        system("pause");
        system("cls");
    }

    void Find_Emp()
    {
        if(this->m_FileIsEmpty)
        {
            cout<<"�ļ�Ϊ�ջ��¼������"<<endl;
        }
        else{
            cout<<"��������ҵķ�ʽ��"<<endl;
            cout<<"1.����ְ���ı�Ų���"<<endl;
            cout<<"2.����ְ������������"<<endl;

            int select;
            cin>>select;

            if(select==1)
            {
                cout<<"��������ҵı�ţ�"<<endl;
                int id;
                cin>>id;

                int ret=this->IsExist(id);
                if(ret!=-1)
                {
                    cout<<"���ҳɹ�����ְ������Ϣ���£�"<<endl;
                    this->m_EmpArray[ret]->showInfo();
                } else{
                    cout<<"����ʧ�ܣ����޴���"<<endl;
                }
            }
            else if(select==2)
            {
                string name;
                cout<<"��������ҵ�������"<<endl;
                cin>>name;

                bool flag=false;
                for(int i=0;i<m_EmpNum;i++)
                {
                    if(this->m_EmpArray[i]->m_Name==name)
                    {
                         cout<<"���ҳɹ�����ְ�����Ϊ��"
                             <<this->m_EmpArray[i]->m_Id
                             <<"��ְ����Ϣ���£�"<<endl;
                         this->m_EmpArray[i]->showInfo();
                         flag=true;
                    }
                }
                if(flag==false)
                {
                    cout<<"����ʧ�ܣ����޴���"<<endl;
                }
            }
            else
            {
              cout<<"�����ѡ������"<<endl;
            }
        }
        system("pause");
        system("cls");
    }

    void Sort_Emp()
    {
        if(this->m_FileIsEmpty)
        {
            cout<<"�ļ������ڻ�����Ϊ��"<<endl;
            system("pause");
            system("cls");
        } else{
            cout<<"��ѡ������ʽ��"<<endl;
            cout<<"1.��ְ������������"<<endl;
            cout<<"2.��ְ���Ž�������"<<endl;

            int select;
            cin>>select;

            for(int i=0;i<m_EmpNum;i++)
            {
                int minOrmax=i; //������Сֵ�����ֵ�±�
                for(int j=i+1;j<m_EmpNum;j++)
                {
                    if(select==1) //����
                    {
                        if(this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id)
                        {
                            minOrmax=j;
                        }
                    } else{
                        if(this->m_EmpArray[minOrmax]->m_Id < this->m_EmpArray[j]->m_Id)
                        {
                            minOrmax=j;
                        }
                    }
                }
                if(i!=minOrmax)
                {
                    Worker *temp=this->m_EmpArray[i];
                    this->m_EmpArray[i]=this->m_EmpArray[minOrmax];
                    this->m_EmpArray[minOrmax]=temp;
                }
            }
            cout<<"����ɹ��������Ľ��Ϊ��"<<endl;
            this->save();
            this->show_Emp();
        }
    }

    void Clean_File()
    {
        cout<<"ȷ�������"<<endl;
        cout<<"1.ȷ��"<<endl;
        cout<<"2.����"<<endl;

        int select;
        cin>>select;

        if(select==1)
        {
            //����ļ�
            ofstream ofs(FILENAME,ios::trunc); // ɾ���ļ������´���
            ofs.close();

            if(this->m_EmpArray!=NULL)
            {
                // ɾ��������ÿ��ְ������
                for(int i=0;i<this->m_EmpNum;i++)
                {
                    delete this->m_EmpArray[i];
                    this->m_EmpArray[i]=NULL;
                }

                // ɾ����������ָ��
                delete [] this->m_EmpArray;
                this->m_EmpArray=NULL;
                this->m_EmpNum=0;
                this->m_FileIsEmpty= true;
            }
            cout<<"��ճɹ�"<<endl;
        }
        system("pause");
        system("cls");
    }

    //�ж�ְ���Ƿ���ڣ����ڷ���id
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
        cout<<"��ӭ�´�������"<<endl;
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
        WorkManager wm;  // ʵ���������߶���
        wm.show_menu();  // ���ó�Ա����
        cout<<"����������ѡ��"<<endl;
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
            wm.Mod_Emp();
            break;
        case 5:
            wm.Find_Emp();
            break;
        case 6:
            wm.Sort_Emp();
            break;
        case 7:
            wm.Clean_File();
            break;
        default:
            system("cls");
            break;
        }
    }
    system("pause");
    return 0;
}
