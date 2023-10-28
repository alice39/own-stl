#ifndef STACK_GUARD_HEADER
#define STACK_GUARD_HEADER

#include "list.hpp"

namespace own {

    /**
     * @brief A class representing a stack.
     *
     * @tparam T The type of the value stored in the stack.
     */
    template <typename T, typename Container = List<T> >
    class Stack {
      public:
        /**
         * @brief Constructs a stack with the given data.
         *
         * Complexity: O(n)
         *
         * @param data The data to initialize the stack.
         */
        Stack(Container container) { this->container = container; }

        /**
         * @brief Default constructor.
         *
         * Complexity: O(1)
         */
        Stack() {}

        /**
         * @brief Copy constructor.
         *
         * Complexity: O(n)
         *
         * @param other The stack to copy from.
         */
        Stack(const Stack<T>& other) { this->container = other.container; }

        /**
         * @brief Checks if the stack is empty.
         *
         * Complexity: O(1)
         *
         * @return True if the stack is empty, otherwise false.
         */
        inline bool empty() const { return this->container.empty(); }

        /**
         * @brief Returns the length of the stack.
         *
         * Complexity: O(1)
         *
         * @return The length of the stack.
         */
        inline usize len() const { return this->container.len(); }

        /**
         * @brief Returns a reference to the top element of the stack.
         *
         * Complexity: O(1)
         *
         * @return A const reference to the top element of the stack.
         *
         * @note It's undefined behavior, if queue is empty.
         */
        const T& top() const { return this->container.back(); }

        /**
         * @brief Returns a reference to the top element of the stack.
         *
         * Complexity: O(1)
         *
         * @return A reference to the top element of the stack.
         *
         * @note It's undefined behavior, if queue is empty.
         */
        T& top() { return this->container.back(); }

        /**
         * @brief Pushes an element onto the top of the stack.
         *
         * Complexity: O(1)
         *
         * @param value The value to be pushed onto the stack.
         */
        void push(T value) { this->container.pushBack(value); }

        /**
         * @brief Removes and returns the top element from the stack.
         *
         * Complexity: O(1)
         *
         * @return The value of the top element of the stack.
         *
         * @note It's undefined behavior, if queue is empty.
         */
        T pop() { return this->container.popBack(); }

        /**
         * @brief Appends another stack to the current stack.
         *
         * Complexity: O(n)
         *
         * @param other The stack to be appended.
         */
        void append(Stack<T>& other) {
            other.reverse();
            this->container.append(other.container);
        }

        /**
         * @brief Reverses the order of elements in the stack.
         *
         * Complexity: O(n)
         */
        void reverse() { this->container.reverse(); }

        /**
         * @brief Clears all elements from the stack.
         *
         * Complexity: O(n)
         */
        void clear() { this->container.clear(); }

        /**
         * @brief Swaps the contents of this stack with another stack.
         *
         * Complexity: O(1)
         *
         * @param other The stack to swap with.
         */
        void swap(Stack<T>& other) { this->container.swap(other.container); }

        /**
         * @brief Converts the stack into a container.
         *
         * Complexity: O(n)
         *
         * @return A container containing the elements of the stack.
         */
        Container intoContainer() const { return this->container; }

        /**
         * @brief Concatenates two stacks.
         *
         * Complexity: O(n)
         *
         * @param other The stack to concatenate with.
         * @return The concatenated stack.
         */
        Stack<T> operator+(const Stack<T>& other) const {
            return Stack<T>(this->container + other.container);
        }

        /**
         * @brief Appends another stack to the current stack.
         *
         * Complexity: O(n)
         *
         * @param other The stack to append.
         * @return The updated stack.
         */
        Stack<T>& operator+=(const Stack<T>& other) {
            this->container += other.container;
            return *this;
        }

        /**
         * @brief Checks if two stacks are equal.
         *
         * Complexity: O(n)
         *
         * @param other The stack to compare with.
         * @return True if the stacks are equal, otherwise false.
         */
        bool operator==(const Stack<T>& other) const {
            return this->container == other.container;
        }

        /**
         * @brief Checks if two stacks are not equal.
         *
         * Complexity: O(n)
         *
         * @param other The stack to compare with.
         * @return True if the stacks are not equal, otherwise false.
         */
        bool operator!=(const Stack<T>& other) const {
            return this->container != other.container;
        }

        /**
         * @brief Assignment operator.
         *
         * Complexity: O(n)
         *
         * @param other The stack to assign from.
         * @return The updated stack.
         */
        bool operator=(const Stack<T>& other) const { this->container = other.container; }

        /**
         * @brief Output stream operator.
         *
         * Complexity: O(n)
         *
         * @param out The output stream.
         * @param queue The stack to output.
         * @return The output stream.
         */
        friend std::ostream& operator<<(std::ostream& out, const Stack<T>& stack) {
            return out << stack.container;
        }

        /**
         * @brief Input stream operator.
         *
         * Complexity: O(n)
         *
         * @param in The input stream.
         * @param queue The stack to output.
         * @return The input stream.
         */
        friend std::istream& operator>>(std::istream& in, const Stack<T>& stack) {
            return in >> stack.container;
        }

      private:
        /**
         * @brief the underlying container
         */
        Container container;
    };

} // namespace own

#endif // STACK_GUARD_HEADER
