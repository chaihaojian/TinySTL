#include <cstddef>
// 前置声明单链表类
template <typename T>
class LinkList;

// 声明单链表节点类
template <typename T>
class LinkListNode {
private:
    T data;
    LinkListNode<T>* next;

    friend class LinkList<T>;

    // 私有构造函数 配合友元声明 确保只有LinkList能够构造LinkListNode
    LinkListNode(const T& value) : data(value), next(nullptr) {}

public:
    // 获取节点值
    T getData() const { return data; }

    // 获取下一个节点
    LinkListNode<T>* getNext() const { return next; }
};

// 声明单链表类
template <typename T>
class LinkList {
public:
    using Node = LinkListNode<T>;
    using size_type = std::size_t;

private:
    Node* head;
    Node* tail;
    size_type size;

public:
    // 构造函数
    LinkList() : head(nullptr), tail(nullptr), size(0) {}

    // 拷贝构造
    LinkList(const LinkList<T>& other) : head(nullptr), tail(nullptr), size(0) {
        Node* currentNode = other.head;
        while (currentNode != nullptr) {
            push_back(currentNode->getData());
            currentNode = currentNode->getNext();
        }
    }

    // 析构函数
    ~LinkList() { clear(); }

    // 重载[]
    T& operator[](size_type pos) { return get(pos); }

    // 是否是空链表
    bool empty() const { return head == nullptr; }

    // 尾部插入
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    // 头部插入
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        ++size;
    }

    // 在指定位置插入
    void insert(size_type pos, const T& value) {
        if (pos > size) {
            throw std::runtime_error("can not insert at a position beyond the length of the list ");
        }
        Node* newNode = new Node(value);
        if (pos == 0) {
            push_front(value);
        } else if (pos == size) {
            push_back(value);
        } else {
            Node* current = head;
            for (size_type i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            ++size;
        }
    }

    // 删除尾部节点
    void pop_back() {
        if (empty()) {
            throw std::runtime_error("can not pop from empty list");
        }
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        --size;
    }

    // 删除头部节点
    void pop_front() {
        if (empty()) {
            throw std::runtime_error("can not pop from empty list");
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        --size;
    }

    // 删除指定位置节点
    void remove(size_type pos) {
        if (empty() || pos >= size) {
            throw std::runtime_error("position out of range");
        }
        if (pos == 0) {
            pop_front();
        } else if (pos == size - 1) {
            pop_back();
        } else {
            Node* current = head;
            for (size_type i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            Node* nodeToDelete = current->next;
            current->next = nodeToDelete->next;
            delete nodeToDelete;
            --size;
        }
    }

    // 删除第一个匹配的元素
    bool remove_value(const T& value) {
        if (empty()) {
            return false;
        }
        Node* current = head;
        for (size_type i = 0; i < size; ++i) {
            if (current->data == value) {
                remove(i);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // 获取指定位置的元素
    T& get(size_type pos) const {
        if (empty() || pos >= size) {
            throw std::runtime_error("position out of range");
        }
        Node* current = head;
        for (size_type i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // 查找第一个匹配的元素
    int find(const T& value) const {
        int index = 0;
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            ++index;
            current = current->next;
        }
        return -1;
    }

    // 清空链表
    void clear() {
        while (!empty()) {
            pop_back();
        }
    }

    // 打印全部元素
    void print() const {
        std::cout << "[";
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->getData();
            if (current != tail) {
                std::cout << ", ";
            }
            current = current->getNext();
        }
        std::cout << "]" << std::endl;
    }
};