# Домашнее задание к лекции №2

## Написать аллокатор со стратегией линейного выделения памяти

Класс устроен следующим образом
```c++
class Allocator {
private:
    size_t maxSize;
    size_t currentSize;
    char *initialPosition;
    char *offset;
public:
    Allocator();

    void makeAllocator(size_t size);

    char *alloc(size_t size);

    void reset();

    ~Allocator();
}
```
При вызове `makeAllocator()` аллоцируется указанный размер, который запоминается в `maxSize`. 
Вызов `alloc()` возвращает указатель `offset`, если `maxSize - currentSize > size`, иначе `nullptr`.  
Вызов `reset()` возвращает `offset` в начало и делает `currentSize = 0`.
