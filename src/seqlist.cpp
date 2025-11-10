#include <cstddef>

// 顺序表
template <typename T>
class SeqList {
public:
    using size_type = std::size_t;

public:
    //==========迭代器定义==========

    // 前向迭代器
    class Iterator {
    public:
        // 迭代器类型定义
        using difference_type = std::ptrdiff_t;                     // 距离类型
        using value_type = T;                                       // 值类型
        using pointer = T*;                                         // 指针类型
        using reference = T&;                                       // 引用类型
        using iterator_category = std::random_access_iterator_tag;  // 迭代器标签类型

    private:
        // 迭代器属性
        T* ptr;
        friend class SeqList;                // 保证只有SeqList能够创建Ietrator
        explicit Iterator(T* p) : ptr(p) {}  // 确保Ietrator只能被显式构造 无法通过指针类型隐式转换

    public:
        // 默认构造函数 确保Ierator有明确的无效状态
        Iterator() : ptr(nullptr) {}

        // 重载 Iterator 的运算符
        // 解引用
        T& operator*() const { return *ptr; }

        T* operator->() const { return ptr; }

        // NOTE: 思考：为什么 ++ -- 不需要边界检测

        //  前置++
        Iterator operator++() {
            ++ptr;
            return *this;
        }

        // 后置++
        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr;
            return temp;
        }

        // 前置--
        Iterator& operator--() {
            --ptr;
            return *this;
        }

        // 后置--
        Iterator operator--(int) {
            Iterator temp = *this;
            --ptr;
            return temp;
        }

        // 随机访问 +n
        Iterator operator+(difference_type n) { return Iterator(ptr + n); }

        // 随机访问 -n
        Iterator operator-(difference_type n) { return Iterator(ptr - n); }

        //+=
        Iterator& operator+=(difference_type n) {
            ptr += n;
            return *this;
        }

        //-=
        Iterator& operator-=(difference_type n) {
            ptr -= n;
            return *this;
        }

        // 下标访问 []
        // NOTE:SeqList[]提供绝对位置的访问 而Iterator[]提供相对位置的访问能力 能够支持负索引 算法友好
        T& operator[](difference_type n) const { return ptr[n]; }

        // 比较运算符
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }

        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

        bool operator<(const Iterator& other) const { return ptr < other.ptr; }

        bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }

        bool operator>(const Iterator& other) const { return ptr > other.ptr; }

        bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }

        // 距离计算
        difference_type operator-(const Iterator& other) { return ptr - other.ptr; }
    };

    //==========迭代器接口==========
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + length); }

private:
    T* data;
    size_type capacity;
    size_type length;

    // 扩容函数
    void resize() {
        size_type new_capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_data = new T[new_capacity];

        for (size_type i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // 构造函数
    SeqList(size_type init_capacity = 10) : capacity(init_capacity), length(0) { data = new T[capacity]; }

    // 析构函数
    ~SeqList() { delete[] data; }

    // 拷贝构造函数
    SeqList(const SeqList& other) : capacity(other.capacity), length(other.length) {
        data = new T[capacity];
        for (size_type i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    // 拷贝赋值运算符
    SeqList& operator=(const SeqList& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            length = other.capacity;
            data = new T[capacity];
            for (size_type i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // 获取长度
    size_type size() const { return length; }

    // 获取容量
    size_type get_capacity() const { return capacity; }

    // 判断是否为空
    bool empty() const { return length == 0; }

    // 打印全部元素(仅测试用)
    // TODO:支持自定义类型 抽象成通用的工具函数并从类中移除
    void print() const {
        std::cout << "[";
        for (size_type i = 0; i < length; ++i) {
            std::cout << data[i];
            if (i < length - 1) {
                std::cout << ",";
            }
        }
        std::cout << "]" << std::endl;
    }

    // 尾部插入
    void push_back(const T& value) {
        if (length == capacity) {
            resize();
        }
        // 注意 这里只能用length++ 不能用++length
        data[length++] = value;
    }

    // 指定位置插入
    void insert(size_type index, const T& value) {
        if (index > length) {
            throw std::out_of_range("Index out of range");
        }
        if (length == capacity) {
            resize();
        }

        for (size_type i = length; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
    }

    // 删除尾部元素
    void pop_back() {
        if (empty()) {
            throw std::runtime_error("SeqList is empty");
        }
        --length;
    }

    // 删除指定位置元素
    void erase(size_type index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }

        for (size_type i = index; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }

        --length;
    }

    // 清空
    void clear() { length = 0; }

    // 重载[]运算符
    // 非常量版本
    T& operator[](size_type index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    // 常量版本
    const T& operator[](size_type index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 查找元素
    int find(const T& value) const {
        for (size_type i = 0; i < length; ++i) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }
};