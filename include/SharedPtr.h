#pragma once

template<class T>
class SharedPtr {
 public:
	explicit SharedPtr(T *ptr = 0) : counter(new int), ptr_(ptr) {
		*counter = 1;
	}

	~SharedPtr() {
		if (*counter == 1) {
			delete ptr_;
			delete counter;
		} else
			(*counter)--;
	}

	SharedPtr(const SharedPtr &shptr_) : counter(0), ptr_(0) {
		*this = shptr_;
	}

	SharedPtr &operator=(const SharedPtr &shptr_) {
		if (this == &shptr_)
			return *this;
		if (counter)
			if (--(*counter) == 0) {
				delete ptr_;
				delete counter;
			}
		*(shptr_.counter) += 1;
		counter = shptr_.counter;
		ptr_ = shptr_.ptr_;
		return *this;
	}

	T *get() const {
		return ptr_;
	}
	T *base() const{
		return ptr_;
	}
	void reset(T *ptr = 0) {
		(*counter)--;
		if (*counter == 0) {
			delete ptr_;
			delete counter;
		}
		counter = new int;
		*counter = 1;
		ptr_ = ptr;
	}

	T &operator*() const {
		return *ptr_;
	}

	T *operator->() const {
		return ptr_;
	}
	bool operator==(const SharedPtr & it) const { return (ptr_ == it.ptr_);}
	bool operator!=(const SharedPtr & it) const { return (ptr_ != it.ptr_);}
	bool operator>=(const SharedPtr & it) const { return (ptr_ >= it.ptr_);}
	bool operator<=(const SharedPtr & it) const { return (ptr_ <= it.ptr_);}
	bool operator>(const SharedPtr & it) const { return (ptr_ > it.ptr_);}
	bool operator<(const SharedPtr & it) const { return (ptr_ < it.ptr_);}
	
 private:
	int *counter;
	T *ptr_;
};

template <typename T>
	bool
	operator==(const SharedPtr<T> lhs,
			const SharedPtr<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T>
	bool
	operator!=(const SharedPtr<T> lhs,
			const SharedPtr<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <typename T>
	bool
	operator<(const SharedPtr<T> lhs,
			const SharedPtr<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}
	 template<typename T_L, typename T_R>
	 bool
	 operator<(const SharedPtr<T_L> lhs,
	 		const SharedPtr<T_R> rhs)
	 {
	 	return (lhs.base() < rhs.base());
	 }
	template <typename T>
	bool
	operator>(const SharedPtr<T> lhs,
			const SharedPtr<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}
	 template<typename T_L,
	 		typename T_R>
	 bool
	 operator>(const SharedPtr<T_L> lhs,
	 		const SharedPtr<T_R> rhs)
	 {
	 	return (lhs.base() > rhs.base());
	 }
	template <typename T>
	bool
	operator<=(const SharedPtr<T> lhs,
			const SharedPtr<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	 template<typename T_L, typename T_R>
	 bool
	 operator<=(const SharedPtr<T_L> lhs,
	 		const SharedPtr<T_R> rhs)
	 {
	 	return (lhs.base() <= rhs.base());
	 }
	template <typename T>
	bool
	operator>=(const SharedPtr<T> lhs,
			const SharedPtr<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	 template<typename T_L,
	 		typename T_R>
	 bool
	 operator>=(const SharedPtr<T_L> lhs,
	 		const SharedPtr<T_R> rhs)
	 {
	 	return (lhs.base() >= rhs.base());
	 }