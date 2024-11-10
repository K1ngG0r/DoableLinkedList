#include <iostream>

template <typename T>
class DoableLinkedList {
private:
    class Node {
    public:
        T value;//значение
        Node* next;//ссылка на след. элемент
        Node* prev;//ссылка на пред. элемент
        Node(T value)
            : value{ value }, next{ nullptr }, prev{ nullptr } {}

    };
    Node* first;
    Node* last;
public:
    DoableLinkedList() :first{ nullptr }, last{ nullptr } {}
    ~DoableLinkedList() {
        if (!IsEmpty()) {
            Node* current = first->next;

            while (current != nullptr) {
                delete current->prev;
                current = current->next;
            }
            delete last;

            first = nullptr;
            last = nullptr;
        }
    }

    bool IsEmpty() const{
        return first == nullptr;
    }
    
    DoableLinkedList& AddToTail(T value) {
        Node* node = new Node(value);
        if (IsEmpty()) {
            first = node;
            last = node;
            return *this;
        }
        last->next = node;
        node->prev = last;
        last = node;
        return *this;
    }


    DoableLinkedList& AddToHead(T value) {
        Node* node = new Node(value);
        if (IsEmpty()) {
            first = node;
            last = node;
            return *this;
        }

        node->next = first;
        first = node;
        return *this;
    }

    DoableLinkedList& DeleteFromHead() {
        if (IsEmpty()) {
            std::cout << "List is empty!" << std::endl;
            return *this;
        }

        Node* current = first;
        first = current->next;
        delete current;

        return *this;
    }

    DoableLinkedList& DeleteFromTail() {
        if (IsEmpty()) {
            std::cout << "List is empty!" << std::endl;
            return *this;
        }

        Node* current = last;
        last = current->prev;
        last->next = nullptr;
        delete current;

        return *this;
    }

    DoableLinkedList& DeleteAll() {
        Node* current = first->next;
        while (current != nullptr) {
            delete first;
            first = current;
            current = current->next;
        }
        delete first;
        first = nullptr;
        last = nullptr;
        return *this;
    }

    friend std::ostream& operator <<(std::ostream& out, const DoableLinkedList& list) {
        if (!list.IsEmpty()) {
            Node* current = list.first;
            while (current != nullptr) {
                out << current->value << '\t';
                current = current->next;
            }
        }
        else
            std::cout << "List is empty" << std::endl;
        return out;
    }

    int Size() {
        int count = 0;
        Node* current = first;
        while (current != nullptr) {
            current = current->next;
            count++;
        }
        return count;
    }


    DoableLinkedList& AddInPozition(T element, unsigned int pozinion) {
        if (pozinion < Size())
        {
            Node* current = first;
            for (size_t i = 0; i < pozinion; i++)
                current = current->next;
            Node* tmp = new Node(element);
            tmp->next = current;
            tmp->prev = current->prev;
            current->prev->next = tmp;
            current->prev = tmp;
            
        }
        else
            std::cout << "Out of range" << std::endl;
        return *this;
    }

    DoableLinkedList& DeleteInPozition(unsigned int pozinion) {
        if (pozinion < Size())
        {
            if (pozinion == 0) {
                DeleteFromHead();
                return *this;
            }
            Node* current = first;
            for (size_t i = 0; i < pozinion; i++)
                current = current->next;
            Node* tmp = current;
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;

            delete tmp;
        }
        else
            std::cout << "Out of range" << std::endl;
        return *this;
    }

    int SearchElement(T element) {
        Node* node = first;
        for (size_t i = 0; i < Size(); i++) {
            if (node->value == element)
                return i;
            node = node->next;
        }
        return NULL;
    }

    int ReversElement(T element, T new_element) {
        Node* node = first;
        int count = 0;
        for (size_t i = 0; i < Size(); i++)
        {
            if (node->value == element) {
                node->value = new_element;
                count++;
            }
            node = node->next;
        }
        return count == 0 ? -1 : count;
    }

    T operator[](int index) {
        Node* current = first;
        for (size_t i = 0; i < index; i++)
            current = current->next;
        return current->value;
    }


};

int main()
{
    DoableLinkedList<int> list{};
    list.AddToTail(10);
    list.AddToTail(5);
    list.AddToTail(0);
    list.AddToTail(3);
    list.AddToTail(5);
    list.AddToTail(7);
    /*std::cout << list << std::endl;
    list.AddInPozition(1, 2);
    std::cout << list << std::endl;
    list.DeleteInPozition(0);
    std::cout << list << std::endl;
    std::cout << list.SearchElement(50) << std::endl;
    std::cout << list.ReversElement(5, 50) << std::endl;*/
    std::cout << list << std::endl;
    list.ReversList();
    return 0;
}
