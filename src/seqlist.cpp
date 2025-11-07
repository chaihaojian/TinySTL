#include <cstddef>

// 顺序表
template <typename T>
class SeqList
{
private:
    T *data;
    size_t capacity;
    size_t length;

public:
    // 构造函数
    SeqList(size_t init_capacity = 10)
        : capacity(init_capacity), length(0)
    {
        data = new T[capacity];
    }

    // 析构函数
    ~SeqList()
    {
        delete[] data;
    }

    // 拷贝构造函数
    SeqList(const SeqList &other)
        : capacity(other.capacity), length(other.length)
    {
        data = new T[capacity];
        for (size_t i = 0; i < length; ++i)
        {
            data[i] = other.data[i];
        }
    }

    // 拷贝赋值运算符
    SeqList &operator=(const SeqList &other)
    {
        if (this != &other)
        {
            delete[] data;
            capacity = other.capacity;
            length = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < length; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // 扩容函数
    void resize()
    {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        T *new_data = new T[new_capacity];

        for (size_t i = 0; i < length; ++i)
        {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    // 获取长度
    size_t size() const
    {
        return length;
    }

    // 获取容量
    size_t get_capacity() const
    {
        return capacity;
    }

    // 判断是否为空
    bool empty() const
    {
        return length == 0;
    }

    // 打印全部元素
    void print() const
    {
        std::cout << "[";
        for (size_t i = 0; i < length; ++i)
        {
            std::cout << data[i];
            if (i < length - 1)
            {
                std::cout << ",";
            }
        }
        std::cout << "]" << std::endl;
    }

    // 尾部插入
    void push_back(const T &value)
    {
        if (length == capacity)
        {
            resize();
        }
        // 注意 这里只能用length++ 不能用++length
        data[length++] = value;
    }

    // 指定位置插入
    void insert(size_t index, const T &value)
    {
        if (index > length)
        {
            throw std::out_of_range("Index out of range");
        }
        if (length == capacity)
        {
            resize();
        }

        for (size_t i = length; i > index; --i)
        {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
    }

    // 删除尾部元素
    void pop_back()
    {
        if (empty())
        {
            throw std::runtime_error("SeqList is empty");
        }
        --length;
    }

    //删除指定位置元素
    void erase(size_t index)
    {
        if (index >= length)
        {
            throw std::out_of_range("Index out of range");
        }

        for (size_t i = index; i < length - 1; ++i)
        {
            data[i] = data[i + 1];
        }

        --length;
    } 

    //清空
    void clear()
    {
        length = 0;
    }

    //重载[]运算符
    //非常量版本
    T& operator[](size_t index)
    {
        if (index >= length)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    //常量版本
    const T& operator[](size_t index) const
    {
        if (index >= length)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    //查找元素
    int find(const T& value) const 
    {
        for (size_t i = 0; i < length; ++i)
        {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }
};