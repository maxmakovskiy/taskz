#ifndef UNIQUEPTR
#define UNIQUEPTR

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr 
{
public:
    UniquePtr()
    {
    }

    UniquePtr(T* ptr)
    {
        ptr_ = ptr;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr& operator=(nullptr_t)
    {
        
    }

    UniquePtr& operator=(UniquePtr&& other)
    {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    UniquePtr(UniquePtr&& other)
    {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    ~UniquePtr()
    {
        delete ptr_;
    }

    T& operator*() const
    {
        return *ptr_;
    }

    T* operator->() const
    {
        return ptr_;
    }

    T* Release()
    {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    void Reset(T* ptr)
    {
        delete ptr_;
        ptr_ = ptr;
    }

    void Swap(UniquePtr& other)
    {
        UniquePtr temp = std::move(other);
        other = std::move(*this);
        this->operator=(std::move(temp));
    }

    T* Get() const
    {
        return ptr_;
    }

private:
    T* ptr_ = nullptr;

};

#endif
