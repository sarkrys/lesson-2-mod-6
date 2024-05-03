#include <iostream>
#include <stdexcept>
#include <memory>

class smart_array {
public:
    explicit smart_array(size_t size) : size_(size), data_(std::make_unique<int[]>(size)) {}

    smart_array(const smart_array& other) : size_(other.size_), count_(other.count_), data_(std::make_unique<int[]>(size_)) {
        for (size_t i = 0; i < count_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    smart_array& operator=(const smart_array& other) {
        if (this != &other) { 
            std::unique_ptr<int[]> new_data(std::make_unique<int[]>(other.size_));

            for (size_t i = 0; i < other.count_; ++i) {
                new_data[i] = other.data_[i];
            }

            data_ = std::move(new_data);
            size_ = other.size_;
            count_ = other.count_;
        }
        return *this;
    }

    ~smart_array() = default;

    void add_element(int element) {
        if (count_ >= size_) {
            throw std::out_of_range("Array is full");
        }
        data_[count_++] = element;
    }

    int get_element(size_t index) const {
        if (index >= count_) {
            throw std::out_of_range("Invalid index");
        }
        return data_[index];
    }

private:
    size_t size_;
    size_t count_ = 0;
    std::unique_ptr<int[]> data_;
};

int main() {
    try {
        smart_array arr(5);

        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);

        std::cout << arr.get_element(1) << std::endl;

        smart_array arr2 = arr;
        smart_array arr3(2);
        arr3 = arr;
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }

    return 0;
}
