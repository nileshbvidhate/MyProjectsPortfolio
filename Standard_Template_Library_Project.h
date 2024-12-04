#include<iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//          Author        :     Nilesh Balu Vidhate

//          Application   :     This application demonstrates the implementation of various 
//                              data structures such as Linked list, Stack, Queue etc and it 
//                              provides the operations such as insertion, deletion, traversal 
//                              and searching.

//          Date          :     05 Aug 2024
//
//
//
//////////////////////////////////////////////////////////////////////

struct node
{
    int data;
    struct node *next;
};

typedef struct node NODE;
typedef struct node * PNODE;

class SinglyLinearLL
{
    public:
        PNODE Head;
        int iCount;

        SinglyLinearLL();

        void InsertFirst(int);
        void InsertLast(int);
        void InsertAtPos(int,int);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int);

        void Display();

};

class SinglyCircularLL
{
    public:
        PNODE Head = NULL;
        PNODE Tail = NULL;
        int iCount = 0;

        SinglyCircularLL();

        void InsertFirst(int);
        void InsertLast(int);
        void InsertAtPos(int,int);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int);

        void Display();
};

struct nodeDL
{
    struct nodeDL *prev;
    int data;
    struct nodeDL *next;
    
};

typedef struct nodeDL NODEDL;
typedef struct nodeDL * PNODEDL;

class DoublyLinearLL
{
    public:
        PNODEDL Head;
        int iCount;

        DoublyLinearLL();

        void InsertFirst(int);
        void InsertLast(int);
        void InsertAtPos(int,int);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int);

        void Display();

};


class DoublyCircularLL
{
    public:
        PNODEDL Head;
        PNODEDL Tail;
        int iCount;

        DoublyCircularLL();

        void InsertFirst(int);
        void InsertLast(int);
        void InsertAtPos(int,int);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int);

        void Display();

};

SinglyLinearLL :: SinglyLinearLL()
{
    Head = NULL;
    iCount = 0;
}

void SinglyLinearLL :: InsertFirst(int no)
{
    PNODE newn = new NODE();

    newn->data = no;
    newn->next = NULL;

    if(Head == NULL)
    {
        Head = newn; 
        iCount++;
    }
    else
    {
        newn->next = Head;
        Head = newn;
        iCount++;
    }
}

void SinglyLinearLL :: InsertLast(int no)
{
    PNODE newn = new NODE();
    PNODE temp = Head;

    newn->data = no;
    newn->next = NULL;

    if(Head == NULL)
    {
        Head = newn; 
        iCount++;
    }
    else
    {
       while(temp->next != NULL)
       {
            temp = temp->next;
       }
       temp->next = newn;
       iCount++;
    }
}
void SinglyLinearLL :: InsertAtPos(int no, int iPos)
{
    PNODE temp = Head;
    PNODE newn = NULL;
    int iCnt = 0;

    if((iPos < 1) || (iPos > iCount + 1 ) )
    {
        cout<<"Invalid Position"<<"\n";
    }
    else if(iPos == 1)
    {
        InsertFirst(no);
    }
    else if(iPos == iCount + 1)
    {
        InsertLast(no);
    }
    {
        newn = new NODE();

        newn->data = no;
        newn->next = NULL;

        for(iCnt = 1; iCnt < (iPos-1); iCnt++)
        {
            temp = temp->next;
        }

        newn->next = temp->next;
        temp->next = newn;
        iCount++;

    }

}

void SinglyLinearLL :: DeleteFirst()
{
    PNODE temp = Head;

    if(Head == NULL)
    {
        return;
    }
    else if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
        iCount--;
    }
    else
    {
        Head = Head->next;
        delete temp;
        iCount--;
    }
}

void SinglyLinearLL :: DeleteLast()
{
    PNODE temp = Head;

    if(Head == NULL)
    {
        return;
    }
    else if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
        iCount--;
    }
    else
    {
        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }
        
        delete (temp->next);
        temp->next = NULL;
        iCount--;

    }
}

void SinglyLinearLL :: DeleteAtPos(int iPos)
{
    PNODE temp1 = Head;
    PNODE temp2 = NULL;
    int iCnt = 0;

    if((iPos < 1) || (iPos > iCount) )
    {
        cout<<"Invalid Position"<<"\n";
    }
    else if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == iCount)
    {
        DeleteLast();
    }
    {
        
        for(iCnt = 1; iCnt < (iPos-1); iCnt++)
        {
            temp1 = temp1->next;
        }
        temp2 = temp1->next;
        temp1->next = temp2->next;
        delete temp2;
        temp2 = NULL;
        
        iCount--;

    }   
}

void SinglyLinearLL :: Display()
{
    PNODE temp = Head;

    cout<<"Elements From LinkedList are : "<<"\n";

    while(temp != NULL)
    {
        cout<<"| "<<temp->data<<" | -> ";
        temp = temp->next;
    }

    cout<<"NULL"<<"\n";

}

DoublyLinearLL :: DoublyLinearLL()
{
    Head = NULL;
    iCount = 0;
}

void DoublyLinearLL :: InsertFirst(int no)
{
    PNODEDL newn = new NODEDL();

    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;

    if(Head == NULL)
    {
        Head = newn;
        iCount++;
    }
    else
    {
        Head->prev = newn;
        newn->next = Head;
        Head = newn;
        iCount++;
    }

}

void DoublyLinearLL :: Display()
{
    PNODEDL temp = Head;

    cout<<"Elements from Doubly LinkedList are : "<<"\n";

    while(temp->next != NULL)
    {
        cout<<"| "<<temp->data<<" | ->";
        temp = temp->next;
    }
    cout<<"| "<<temp->data<<" | ->";
    cout<<" NULL"<<"\n";

    cout<<"Elements from Doubly LinkedList In Reversed Order : "<<"\n";

    while(temp != NULL)
    {
        cout<<"| "<<temp->data<<" | ->";
        temp = temp->prev;
    }
    cout<<" NULL"<<"\n";

}

void DoublyLinearLL :: InsertLast(int no)
{
    PNODEDL newn = new NODEDL();
    PNODEDL temp = Head;

    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;

    if(Head == NULL)
    {
        Head = newn;
        iCount++;
    }
    else
    {
        newn = new NODEDL();

        newn->data = no;
        newn->next = NULL;
        newn->prev = NULL;


        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        newn->prev = temp;
        temp->next = newn;
        iCount++;       
    }

}

void DoublyLinearLL :: DeleteFirst()
{
    if(Head == NULL)
    {
        return;
    }
    else if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
        iCount--;
    }
    else
    {
        Head = Head->next;
        delete (Head->prev);
        Head->prev = NULL;

        iCount--;
    }
}

void DoublyLinearLL :: DeleteLast()
{   
    PNODEDL temp = Head;

    if(Head == NULL)
    {
        return;
    }
    else if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
        iCount--;
    }
    else
    {   
        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }

        delete (temp->next);
        temp->next = NULL;

        iCount--;
    }
}

void DoublyLinearLL :: InsertAtPos(int no, int iPos)
{
    PNODEDL newn = NULL;
    int iCnt = 0;
    PNODEDL temp = Head;

    if((iPos < 1) || (iPos >(iCount+1) ))
    {
        cout<<"Invalid Position"<<"\n";
    }
    else if(iPos == 1)
    {
        InsertFirst(no);
    }
    else if(iPos == (iCount+1))
    {
        InsertLast(no);
    }
    else
    {
        newn = new NODEDL();

        newn->data = no;
        newn->next = NULL;
        newn->prev = NULL;

        for(iCnt = 1; iCnt < (iPos-1); iCnt++)
        {
            temp = temp->next;
        }
        newn->prev = temp;
        newn->next = temp->next;
        newn->next->prev = newn;
        temp->next = newn;
        
        iCount++;
    }
}

void DoublyLinearLL :: DeleteAtPos(int iPos)
{
    int iCnt = 0;
    PNODEDL temp = Head;

    if((iPos < 1) || (iPos > iCount) )
    {
        cout<<"Invalid Position"<<"\n";
    }
    else if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == iCount)
    {
        DeleteLast();
    }
    else
    {
        for(iCnt = 1; iCnt < (iPos-1); iCnt++)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        delete(temp->next->prev);
        temp->next->prev = temp;

        iCount--;

    }
}

SinglyCircularLL :: SinglyCircularLL()
{
    Head = NULL;
    Tail = NULL;
    iCount = 0;
} 

void SinglyCircularLL :: InsertFirst(int no)
{
    PNODE newn = new NODE();

    newn->data = no;
    newn->next = NULL;

    if((Head == NULL) && (Tail == NULL))
    {
        Head = newn;
        Tail = newn;

        Tail->next = Head;
        iCount++;
        
    }
    else
    {
        newn->next = Head;
        Head = newn;
        Tail->next = Head;

        iCount++;
    }

}

void SinglyCircularLL :: InsertLast(int no)
{
    PNODE newn = new NODE();

    newn->data = no;
    newn->next = NULL;

    if((Head == NULL) && (Tail == NULL))
    {
        Head = newn;
        Tail = newn;

        Tail->next = Head;
        iCount++;
        
    }
    else
    {
        Tail->next = newn;
        Tail = newn;
        Tail->next = Head;

        iCount++;
    }
}

void SinglyCircularLL :: Display()
{
    PNODE temp = Head;

    cout<<"Elements from Singly Circular Linked List : "<<"\n";

    do
    {
        cout<<"| "<<temp->data<<" | -> ";
        temp = temp->next;
    }while(temp != (Head));

    cout<<"\n";
    cout<<"\n";

    cout<<"Elements from Singly Circular Linked List Using Tail : "<<"\n";

    temp = Tail;
    do
    {
        cout<<"| "<<temp->data<<" | -> ";
        temp = temp->next;
    }while(temp != (Tail));

    //for(int iCnt = 0; iCnt < iCount; iCnt++)
    //{
    //    cout<<"| "<<temp->data<<" | -> ";
    //   temp = temp->next;
    //}

    cout<<"\n";
    cout<<"\n";

}

void SinglyCircularLL :: DeleteFirst()
{
    PNODE temp = Head;

    if((Head == NULL) && (Tail == NULL))
    {
        return;
    }
    else if(Head == Tail)
    {
        delete Head;

        Head = NULL;
        Tail = NULL;

        iCount--;
    }
    else
    {
        Head = Head->next;
        delete temp;
        Tail->next = Head;

        iCount--;
    }
}
void SinglyCircularLL :: DeleteLast()
{
    PNODE temp = Head;

    if((Head == NULL) && (Tail == NULL))
    {
        return;
    }
    else if(Head == Tail)
    {
        delete Head;

        Head = NULL;
        Tail = NULL;

        iCount--;
    }
    else
    {
        while(temp->next != Tail)
        {
            temp = temp->next;
        }
        delete Tail;
        Tail = temp;
        Tail->next = Head;
        
        iCount--;
    }
}

void SinglyCircularLL :: InsertAtPos(int no, int iPos)
{
    PNODE temp = Head;
    PNODE newn = NULL;
    int iCnt = 0;

    if((iPos < 1 ) || (iPos > (iCount + 1) ))
    {
        cout<<"Invalid Position"<<"\n";
        return;
    }
    else if(iPos == 1)
    {
        InsertFirst(no);
    }
    else if(iPos == (iCount + 1))
    {
        InsertLast(no);
    }
    else
    {
        newn = new NODE();

        newn->data = no;
        newn->next = NULL;

        for(iCnt = 1; iCnt < (iPos-1); iCnt++)
        {
            temp = temp->next;
        }
        newn->next = temp->next;
        temp->next = newn;

        iCount++;
    }
}

void SinglyCircularLL :: DeleteAtPos(int iPos)
{
    PNODE temp1 = Head;
    PNODE temp2 = NULL;
    int iCnt = 0;

    if((iPos < 1 ) || (iPos > (iCount) ))
    {
        cout<<"Invalid Position"<<"\n";
        return;
    }
    else if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == (iCount + 1))
    {
        DeleteLast();
    }
    else
    {
        for(iCnt = 1; iCnt <(iPos-1); iCnt++)
        {
            temp1 = temp1->next;
        }

        temp2 = temp1->next;
        temp1->next = temp2->next;
        delete temp2;

        iCount--;

    }
}


DoublyCircularLL :: DoublyCircularLL()
{
    Head = NULL;
    Tail = NULL;
    iCount = 0;
}

void DoublyCircularLL :: InsertFirst(int no)
{
    PNODEDL newn = new NODEDL();

    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;

    if((Head == NULL) && (Tail == NULL))
    {
        Head = Tail = newn;
        Tail->next = Head;
        Head->prev = Tail;

        iCount++;
    }
    else
    {
        Head->prev = newn;
        newn->next = Head;
        Head = newn;
        Head->prev = Tail;
        Tail->next = Head;

        iCount++; 
    }
}

void DoublyCircularLL :: Display()
{
    PNODEDL temp = Head;

    cout<<"Elements From Doubly Circular Linked list Using Head in Linear Order : "<<"\n";

    do
    {
        cout<<"| "<<temp->data<<" |<=>";
        temp = temp->next;
    }while(temp != (Tail->next));
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";

    temp = Tail;

    cout<<"Elements From Doubly Circular Linked list Using Tail in Reverse Order : "<<"\n";

    do
    {
        cout<<"| "<<temp->data<<" |<=>";
        temp = temp->prev;
    }while(temp != (Head->prev));
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";

    temp = Head;

    cout<<"Elements From Doubly Circular Linked list Using Head in Circular Order : "<<"\n";

    do
    {
        cout<<"| "<<temp->data<<" |<=>";
        temp = temp->prev;
    }while(temp != (Tail->next));
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";

    temp = Tail;

    cout<<"Elements From Doubly Circular Linked list Using Tail in Circular Order : "<<"\n";

    do
    {
        cout<<"| "<<temp->data<<" |<=>";
        temp = temp->next;
    }while(temp != (Head->prev));
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";

}

void DoublyCircularLL :: InsertLast(int no)
{
    PNODEDL newn = new NODEDL();

    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;

    if((Head == NULL) && (Tail == NULL))
    {
        Head = Tail = newn;
        Tail->next = Head;
        Head->prev = Tail;
        iCount++;
    }
    else
    {
        (Tail)->next =newn;
        newn->prev = Tail;
        Tail = newn;
        (Tail)->next = Head;
        (Head)->prev = Tail;

        iCount++;
    }
}

void DoublyCircularLL :: DeleteFirst()
{
    if((Head == NULL) && (Tail == NULL))
    {
        return;
    }
    else if(Head == NULL)
    {
        delete Head;
        Head = NULL;
        Tail = NULL;

        iCount--;
    }
    else
    {
        Head = Head->next;
        delete (Tail->next); // delete(Head->prev)
        Tail->next = Head;
        Head->prev = Tail;
        
        iCount--;
    }
}

void DoublyCircularLL :: DeleteLast()
{
    if((Head == NULL) && (Tail == NULL))
    {
        return;
    }
    else if(Head == NULL)
    {
        delete Head;
        Head = NULL;
        Tail = NULL;

        iCount--;
    }
    else
    {
        Tail = Tail->prev;
        delete(Tail->next);
        Tail->next = Head;
        Head->prev = Tail;

        iCount--;
    }
}

void DoublyCircularLL :: InsertAtPos(int no, int iPos)
{
    PNODEDL temp = Head;
    int iCnt = 0;
    PNODEDL newn = NULL;

    if((iPos < 1) || (iPos > (iCount+1) ))
    {
        cout<<"Invalid Position"<<"\n";
    }
    else if(iPos == 1)
    {
        InsertFirst(no);
    }
    else if(iPos == (iCount+1))
    {
        InsertLast(no);
    }
    else
    {
        newn = new NODEDL();

        newn->data = no;
        newn->prev = NULL;
        newn->next = NULL;

        for(iCnt = 1; iCnt < (iPos-1); iCnt++)
        {
            temp = temp->next;
        }
        newn->next = temp->next;
        temp->next->prev = newn;
        newn->prev = temp;
        temp->next = newn;

        iCount++; 
    }
}

void DoublyCircularLL :: DeleteAtPos(int iPos)
{
    PNODEDL temp = Head;
    int iCnt = 0;

    if((iPos < 1) || (iPos > iCount))
    {
        cout<<"Invalid Position"<<"\n";
    }
    else if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == iCount)
    {
        DeleteLast();
    }
    else
    {
        for(iCnt = 1; iCnt < (iPos-1); iCnt++)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        delete (temp->next->prev);
        temp->next->prev = temp;

        iCount--;
    }

}
