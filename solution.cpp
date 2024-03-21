#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node *next = NULL;
};

template<typename T>
struct List
{
    Node<T>* head = NULL;
    int elemcount = 0;

    int length();
    void addFront(T);
    void removeFront();
    void add(T, int);
    void remove(int);
};

template<class T>
int List<T>::length()
    {return this->elemcount;}
template<class T>
void List<T>::remove(int position)
{
    if (position == 0)
    {
        removeFront();
        return;
    }
    else if(position >= elemcount)
        return;

    Node<T>* prev_node = NULL;
    Node<T>* position_pointer = this->head;

    for(int index = 0; index < position ; index++)
    {
        prev_node = position_pointer;
        position_pointer = position_pointer->next;
    }
    Node<T>* old = position_pointer;
    prev_node->next = position_pointer->next;
    delete old;

    elemcount--;
}

template<class T>
void List<T>::add(T new_element, int position)
{
    if (position == 0)
    {
        addFront(new_element);
        return;
    }
    else if (position > elemcount)
        return;

    Node<T>* newnode = new Node<T>;
    newnode->data = new_element;

    Node<T>* prev_node = NULL;
    Node<T>* position_pointer = this->head;

    for(int index = 0; index < position ; index++)
    {
        prev_node = position_pointer;
        position_pointer = position_pointer->next;
    }

    prev_node->next = newnode;
    newnode->next = position_pointer;
    elemcount++;
}

template<class T>
void List<T>::addFront(T new_element) {

    Node<T>* newnode = new Node<T>;
    newnode->data = new_element;
    newnode-> next = this->head;
    this->head = newnode;
    elemcount++;
}

template<class T>
void List<T>::removeFront() {

    if (this->head != NULL)
    {
        Node<T>* old = this->head;
        this->head = this->head->next;
        delete old;
        elemcount--;
    }
}

template <typename T>
struct Stack {
    private:
        List<T> data;
        int elemcount = 0;
    public:
        void push(T& e);
        T pop();
        T& top();
};

template <typename T>
void Stack<T>::push(T& new_element)
{
    data.addFront(new_element);
    elemcount++;
}

template <typename T>
T Stack<T>::pop()
{
    T result = data.head->data;
    data.removeFront();
    elemcount--;
    return result;
}

template <typename T>
T& Stack<T>::top()
{return data.head->data;}

struct LabState{
    char labyrinth[11][11];
    void printLabyrinth();
    void set_current_xy();
    bool checkfinished();
    void fill_with(char [][11]);
    int current_x;
    int current_y;
};

void LabState::fill_with(char from [][11])
{
   for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            this->labyrinth[i][j] = from[i][j];
        }
    }
}


bool LabState::checkfinished()
{
    if(current_y > 0 && labyrinth[current_x][current_y-1] == 'F')
        return 1;
    else if(current_y < 10 && labyrinth[current_x][current_y+1] == 'F')
        return 1;
    if(current_x > 0 && labyrinth[current_x-1][current_y] == 'F')
        return 1;
    if(current_x < 10 && labyrinth[current_x+1][current_y] == 'F')
        return 1;
    else
        return 0;
}


void LabState::printLabyrinth()
{
    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            cout << this->labyrinth[i][j];
        }

        cout << endl;
    }

}

void LabState::set_current_xy()
{
    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            if (this->labyrinth[i][j] == 'O')
            {
                this->current_x = i;
                this->current_y = j;
                return;
            }
            
        }
    }
}


int main() {

    char* filename = "lab1.txt";
    LabState last_state;

    ifstream infile(filename);
    int line_id = 0;
    string line;
    while (true) {
        getline(infile, line);
        if (infile.eof()) {
            break;
        }

        for(int i=0; i<11; i++)
        {
            last_state.labyrinth[line_id][i] = line[i];
        }

        line_id++;
    }

    cout << "Initial Lab." << endl;
    last_state.printLabyrinth();
    last_state.set_current_xy();

    Stack<LabState> mystack;

    while(1)
    {
        if(last_state.checkfinished())
            break;

        bool up=0, down=0, left=0, right=0;

        if(last_state.current_y > 0 && last_state.labyrinth[last_state.current_x][last_state.current_y-1] == ' ')
            left = 1;
        if(last_state.current_y < 10 && last_state.labyrinth[last_state.current_x][last_state.current_y+1] == ' ')
            right = 1;
        if(last_state.current_x > 0 && last_state.labyrinth[last_state.current_x-1][last_state.current_y] == ' ')
            up = 1;
        if(last_state.current_x < 10 && last_state.labyrinth[last_state.current_x+1][last_state.current_y] == ' ')
            down = 1;
        
        if(up)
        {
            LabState up_state;
            up_state.fill_with(last_state.labyrinth);
            up_state.labyrinth[last_state.current_x-1][last_state.current_y] = 'O';
            up_state.labyrinth[last_state.current_x][last_state.current_y] = 'X';
            up_state.set_current_xy();
            
            mystack.push(up_state);
        }
        if(down)
        {
            LabState down_state;
            down_state.fill_with(last_state.labyrinth);
            down_state.labyrinth[last_state.current_x+1][last_state.current_y] = 'O';
            down_state.labyrinth[last_state.current_x][last_state.current_y] = 'X';
            down_state.set_current_xy();
            mystack.push(down_state);
        }
        if(left)
        {
            LabState left_state;
            left_state.fill_with(last_state.labyrinth);
            left_state.labyrinth[last_state.current_x][last_state.current_y-1] = 'O';
            left_state.labyrinth[last_state.current_x][last_state.current_y] = 'X';
            mystack.push(left_state);
        }
        if(right)
        {
            LabState right_state;
            right_state.fill_with(last_state.labyrinth);
            right_state.labyrinth[last_state.current_x][last_state.current_y+1] = 'O';
            right_state.labyrinth[last_state.current_x][last_state.current_y] = 'X';
            mystack.push(right_state);
        }
        last_state = mystack.pop();
        last_state.set_current_xy();

        last_state.printLabyrinth();

    }

    return 0;
}