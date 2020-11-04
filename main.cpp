#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

template <class T>
class MyList
{
    struct node
    {
        T _data;
        node *_next;

        node(T data, node *next = nullptr) : _data(data), _next(next) {}
    } * _header, *_end;

    int _size;

public:
    class MyIterator : public iterator<input_iterator_tag, node>
    {
        friend class MyList;

    public:
        MyIterator(node *ptr = nullptr) { _ptr = ptr; }
        MyIterator &operator=(const MyIterator &iter) { _ptr = iter._ptr; }
        bool operator!=(const MyIterator &iter) { return _ptr != iter._ptr; }
        bool operator==(const MyIterator &iter) { return _ptr == iter._ptr; }
        T &operator*() { return _ptr->_data; }

        //前缀自加
        MyIterator &operator++()
        {
            _ptr = _ptr->_next;
            return *this;
        }

        //后缀自加
        MyIterator operator++(int)
        {
            MyIterator tmp = *this;
            _ptr = _ptr->_next;
            return tmp;
        }

    private:
        node *_ptr;
    };

    MyList() : _header(nullptr), _end(nullptr), _size(0) {}

    MyIterator begin() { return MyIterator(_header); };
    MyIterator end() { return MyIterator(nullptr); };

    T front() { return _header->_data; }
    T back() { return _end->_data; }

    bool empty() { return _header == nullptr || _end == nullptr; }

    void push_back(T element) { add_node_behind(_end, element); }
    void push_front(T element) { add_node_behind(nullptr, element); }
    void pop_front() { delete_node(_header); }
    void pop_back() { delete_node(_end); }

    void clear()
    {
        while (!empty())
            pop_front();
    }

    void insert(MyIterator iter, T element) { add_node_behind(find_element_prev(iter._ptr), element); }
    void erase(MyIterator iter) { delete_node(iter._ptr); }

    void reverse()
    {
        node *ptr = _header;
        _header = _end = nullptr;

        while (ptr != nullptr)
        {
            node *next = ptr->_next;
            push_front(ptr->_data);
            delete ptr;
            ptr = next;
        }
    }

    void print_elements()
    {
        for (auto i : *this)
            cout << i << endl;
    }

    size_t size()
    {
        int count = 0;
        node *ptr = this->_header;

        ptr == nullptr ? return count : count++;

        while (ptr->_next != nullptr)
        {
            count++;
            ptr = ptr->_next;
        }
        return count;
    }

private:
    node *find_element(T element)
    {
        node *ptr = _header;
        while (ptr != nullptr)
        {
            if (ptr->_data == element)
                return ptr;
            ptr = ptr->_next;
        }
        return nullptr;
    }

    node *find_element_prev(node *elem)
    {
        node *ptr = _header;
        while (ptr != nullptr)
        {
            if (ptr->_next == elem)
                return ptr;
            ptr = ptr->_next;
        }
        return nullptr;
    }

    void delete_node(node *elem)
    {
        node *prev = find_element_prev(elem);
        (prev == nullptr ? _header : prev->_next) = elem->_next;
        if (elem->_next == nullptr)
            _end = prev;
        delete elem;
    }

    void add_node_behind(node *pos, T element)
    {
        if (empty())
            _header = _end = new node(element);
        else if (pos == nullptr)
            _header = new node(element, _header);
        else if (pos == _end)
            pos->_next = _end = new node(element);
        else
            pos->_next = new node(element, pos->_next);
    }

protected:
};

void delete_min_until_empty(MyList<int> l)
{
    while (!l.empty())
        l.erase([&l]() {
            MyList<int>::MyIterator it = l.begin(), tmp = l.end();

            for (; it != l.end(); it++)
                if (*it < *tmp)
                    tmp = it;

            return tmp;
        }());
}

int main()
{

    return 0;
}