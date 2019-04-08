#include <iostream>
#include <memory>
#include <tuple>
#include <utility>

template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
private:
    std::tuple<T *, Deleter> tdata;
public:
    UniquePtr() : tdata() {}

    UniquePtr(UniquePtr&& other) noexcept {
        tdata = std::make_tuple(nullptr, Deleter());
        swap(other);
    }

    UniquePtr(T * new_data, Deleter d = Deleter()) : tdata(new_data, d) {}

    const Deleter& get_deleter() const {
        return std::get<1>(tdata);
    }

    Deleter& get_deleter() {
        return std::get<1>(tdata);
    }

    ~UniquePtr() {
        if (std::get<0>(tdata) != nullptr)
            get_deleter()(std::get<0>(tdata));
    }

    T * release() noexcept {
        T * tmp = nullptr;
        std::swap(tmp, std::get<0>(tdata));
        return tmp;
    }

    void reset(T * ptr) {
        std::swap(std::get<0>(tdata), ptr);
        if (ptr != nullptr)
            get_deleter()(ptr);
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(tdata, other.tdata);
    }

    UniquePtr& operator = (std::nullptr_t) {
        reset(nullptr);
        return *this;
    }

    UniquePtr& operator = (UniquePtr&& other) noexcept {
        swap(other);
        return *this;
    }

    T& operator * () const {
        return *std::get<0>(tdata);
    }

    T& operator * () {
        return *std::get<0>(tdata);
    }

    T * operator->() const {
        return std::get<0>(tdata);
    }

    T * get() const {
        return std::get<0>(tdata);
    }

    explicit operator bool() const {
        return std::get<0>(tdata);
    }

    UniquePtr(UniquePtr&) = delete;
    UniquePtr& operator = (const UniquePtr&) = delete;
};
