#include <iostream>
using namespace std;

template <typename T>

class myVector {
  private:
    T *p;
    int capacity;
    int size;

  public:
    // 无参构造初始化
    myVector() {
        this->capacity = 20;
        this->size = 0;
        this->p = new T[capacity];
    }

    // 有参构造初始化
    myVector(int size, T data) {
        this->capacity = 20 + size;
        this->size = size;
        this->p = new T[capacity];
        for (int i = 0; i < this->size; i++) {
            this->p[i] = data;
        }
    }

    // 析构函数
    ~myVector() {
        if (p != nullptr) {
            delete[] p;
        }
    }

    // 拷贝构造函数
    myVector(const myVector &v) {
        this->capacity = v.capacity;
        this->size = v.size;
        this->p = new T[this->capacity];
        memcpy(this->p, v.p, this->size * sizeof(T));
    }

    // 打印容器内容
    void print() {
        for (int i = 0; i < this->size; i++) {
            cout << this->p[i] << " ";
        }
        cout << endl;
    }

    // 插入
    void push_back(T data) {
        // 如果原始的空间满了，拓展容量至原来的两倍
        if (this->size == this->capacity) {
            T *new_p = new T[this->capacity * 2];
            memcpy(new_p, p, this->size * sizeof(T));
            this->capacity *= 2;
            delete[] p;
            p = new_p;
        }
        // 在末尾插入
        this->p[this->size] = data;
        this->size++;
    }

    // 删除最后一个元素
    void pop_back() {
        if (this->size >= 1) {
            this->p[this->size - 1] = 0;
            this->size--;
        }
    }

    // 插入
    void inset(int pos, T data) {
        if (pos >= 0 && pos <= this->size) {
            // 超出空间后 进行扩容
            if (this->size == this->capacity) {
                T *new_p = new T[this->capacity * 2];
                memcpy(new_p, p, this->size * sizeof(T));
                this->capacity *= 2;
                delete[] p;
                p = new_p;
            }
            // 插入
            for (int i = this->size; i > pos; i--) {
                this->p[i] = this->p[i - 1];
            }
            this->p[pos] = data;
            this->size++;
        }
    }

    // 清除
    void clear() {
        if (this->p != nullptr) {
            delete[] this->p;
        }
        this->size = 0;
        this->capacity = 20;
        this->p = new T[capacity];
    }

    // 重载[]运算符
    T &operator[](int index) {
        if (index >= 0 && index < this->size) {
            return this->p[index];
        }
    }

    // 重载=运算符
    void operator=(const myVector &v) {
        if (this->p != nullptr) {
            delete[] this->p;
        }
        this->capacity = v.capacity;
        this->size = v.size;
        this->p = new T[this->capacity];
        memcpy(this->p, v.p, this->size * sizeof(T));
    }
};

void test() {
    // 初始化
    myVector<int> v(3, 10);
    v.print();

    // 末尾插入
    for (int i = 0; i < 20; i++) {
        v.push_back(i);
    }
    v.print();

    // 删除
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.print();

    // 复制拷贝
    myVector<int> v2(v);
    v2.print();
    myVector<int> v3 = v;
    v3.print();

    // 中间插入
    v.inset(5, 22222);
    v.inset(0, 11111);
    v.print();

    // 输出某一个值
    cout << "v[0]: " << v[0] << endl;

    // 修改某一个值
    v[0] = 33333;
    v.print();

    // 清除
    v.clear();
    cout << "clear: ";
    v.print();
}

int main() {
    test();
    return 0;
}