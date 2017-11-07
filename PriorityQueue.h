#include<iostream>

using namespace std;

struct node
{
    int freq;
    char c;
    node* next;
    node* prev;
    node* left;
    node* right;

    node()
    {
        this->freq=0;
        this->c='\0';
        this->next=NULL;
        this->prev=NULL;
        this->left=NULL;
        this->right=NULL;
    }

    node(int freq,char c)
    {
        this->freq=freq;
        this->c=c;
        this->next=NULL;
        this->prev=NULL;
        this->left=NULL;
        this->right=NULL;
    }

    node(int freq)
    {
        this->freq=freq;
        this->c='\0';
        this->next=NULL;
        this->prev=NULL;
    }
};

class Queue
{
	node* head;
	node* tail;
    int counter;
public:
    Queue()
    {
        head=NULL;
        tail=NULL;
        counter=0;
    }

	void append(int freq,char c)
    {
        if(empty())
        {
            node* n=new node(freq,c);
            head=n;
            tail=n;
            counter++;
        }
        else
        {
            node* n=new node(freq,c);
            tail=n;
            node* temp=head;
            while(temp->next!=NULL)
            {
                temp->next->prev=temp;
                temp=temp->next;
            }
            temp->next=tail;
            tail->prev=temp;
            counter++;
        }
        sort();
    }

    void append(node* freq)
    {
        if(empty())
        {
            node* n=freq;
            head=n;
            tail=n;
            counter++;
        }
        else
        {
            node* n=freq;
            tail=n;
            node* temp=head;
            while(temp->next!=NULL)
            {
                temp->next->prev=temp;
                temp=temp->next;
            }
            temp->next=tail;
            tail->prev=temp;
            counter++;
        }
        sort();
    }

    void sort()
    {
        node* temp=tail;
        while(temp->prev!=NULL && temp->freq < temp->prev->freq)
        {
            if(temp->next!=NULL)
                temp->next->prev=temp->prev;
            temp->prev->next=temp->next;
            temp->next=temp->prev;


            temp->prev=temp->next->prev;
            temp->next->prev=temp;

            if(temp->prev!=NULL)
                temp->prev->next=temp;
            else
                head=temp;

            if(temp->next->next==NULL)
            {
                tail=temp->next;
            }
        }
    }

	node* serve()
    {
        node* min;

        if(empty())
        {
            return NULL;
        }

        else
        {
            min=head;
            head=head->next;
            counter--;
            return min;
        }
    }

    bool empty()
    {
        if(size()==0)
            return true;
        else
            return false;
    }

	void print()
    {
        node* temp=head;
        while(temp!=NULL)
        {
            cout<<temp->freq<<" ";
            temp=temp->next;
        }
        cout<<endl;
        node* temp1=tail;
        while(temp1!=NULL)
        {
            cout<<temp1->freq<<" ";
            temp1=temp1->prev;
        }
    }

	int getValueAt(int position)
    {
        if(position == 1)
        {
            return head->freq;
        }
        else if(position>1 && position<=counter)
        {
            node* temp;
            temp = head;
            for(int i=1; i<position; i++)
            {
                temp = temp->next;
            }
            return temp->freq;
        }
    }

	int size()
    {
        return counter;
    }
};
