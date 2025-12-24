#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H //контейнер по типу вектора, для храения клеток карты пещеры 


template <typename T>
class PixelBuffer {
private:
    T* dataPointer;  //указатель на динамический массив
    int bufferSize;   

    PixelBuffer(const PixelBuffer&) = delete;
    PixelBuffer& operator=(const PixelBuffer&) = delete; 

public:
    PixelBuffer() : dataPointer(nullptr), bufferSize(0) {} 

    ~PixelBuffer() {
        clearMemory();
    }
    void resize(int newSize) {
        clearMemory();
        if (newSize > 0) {
            bufferSize = newSize;
            dataPointer = new T[newSize];
        }
    }

    //освобождаем выделенную память
    void clearMemory() {
        if (dataPointer != nullptr) {
            delete[] dataPointer;
            dataPointer = nullptr;
        }
        bufferSize = 0;
    }

    T& operator[](int index) {  
        return dataPointer[index]; 
    }
    const T& operator[](int index) const {  //только для чтения
        return dataPointer[index]; 
    }

    T* begin() {  
        return dataPointer; 
    }
    T* end() { 
        return dataPointer + bufferSize; 
    }
    const T* begin() const { 
        return dataPointer; 
    }
    const T* end() const { 
        return dataPointer + bufferSize;
    }
    int getSize() const {
        return bufferSize; //размер массива (буфера)
    }
};

#endif 