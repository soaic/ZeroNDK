//
// Created by soaic on 2021/8/25.
//



#ifndef ZERONDK_ARRAYLIST_HPP
#define ZERONDK_ARRAYLIST_HPP


template<class E>
class ArrayList {
private:
    E* elementData = NULL;
    int len = 0;   // 数组的大小
    int index = 0;  // 数组的长度

public:
    ArrayList();
    ArrayList(int len);
    bool add(E e);
    E remove(int index);
    E get(int index);
    ~ArrayList();
    int size();

private:
    void ensureCapacityInternal(int capacity);
    void grow(int capacity);

};

template<class E>
ArrayList<E>::ArrayList() {

}

template<class E>
ArrayList<E>::ArrayList(int initialCapacity) {
    if (initialCapacity > 0) {
        this->elementData = (E*)malloc(sizeof(E)*initialCapacity);
        this->len = initialCapacity;
    }
}

template<class E>
bool ArrayList<E>::add(E e) {
    ensureCapacityInternal(this->index + 1);  // Increments modCount!!
    this->elementData[this->index++] = e;
    return true;
}

template<class E>
void ArrayList<E>::ensureCapacityInternal(int capacity) {
    if (this->elementData == NULL) {
        capacity = 10;
    }
    // overflow-conscious code
    if (capacity - this->len > 0)
        grow(capacity);
}

template<class E>
void ArrayList<E>::grow(int capacity) {
    // 每次扩容本身大小的一半
    int newCapacity = this->len + (this->len >> 1);
    if (newCapacity - capacity < 0)
        newCapacity = capacity;

    // 创建新的数组指针
    E* new_arr = (E*)malloc(sizeof(E)*newCapacity);

    if(this->elementData) {
        // 拷贝以前的数据到 new_arr 数组中
        memcpy(new_arr, this->elementData, sizeof(E)*index);
        free(this->elementData);
    }
    // 再把新的数组 赋值到elementData变量
    this->elementData = new_arr;
    this->len = capacity;
}

template<class E>
E ArrayList<E>::get(int i) {
    return this->elementData[i];
}

template<class E>
E ArrayList<E>::remove(int i) {
    if(i > len){
        return NULL;
    }
    E oldValue = elementData[i];
    // 索引i 之前的数据不需要动，之后的数据都往前移动一位
    int numMoved = this->index - i - 1;
    for (int j = 0; j<numMoved; j++) {
        this->elementData[j+i] = this->elementData[j+i+1];
    }
    // 最后一位置为NULL len-1
    elementData[--this->index] = NULL; // clear to let GC do its work
    return oldValue;
 }

template<class E>
ArrayList<E>::~ArrayList<E>()  {
    if(this->elementData) {
        free(this->elementData);
        this->elementData = NULL;
    }
}

template<class E>
int ArrayList<E>::size() {
    return this->index;
}


#endif //ZERONDK_ARRAYLIST_HPP

