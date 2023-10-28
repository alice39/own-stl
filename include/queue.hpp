#ifndef QUEUE_GUARD_HEADER
#define QUEUE_GUARD_HEADER

#include "list.hpp"

namespace own {

    /**
     * @brief A class representing a queue.
     *
     * @tparam T The type of the value stored in the queue.
     */
    template <typename T, typename Container = List<T> >
    class Queue {
      public:
        /**
         * @brief Constructs a Queue object with the given data.
         *
         * Complexity: O(n)
         *
         * @param data The initial data to be stored in the queue.
         */
        Queue(const Container& container) { this->container = container; }

        /**
         * @brief Default constructor for Queue.
         *
         * Complexity: O(1)
         */
        Queue() {}

        /**
         * @brief Copy constructor for Queue.
         *
         * Complexity: O(n)
         *
         * @param other The queue to be copied.
         */
        Queue(const Queue<T>& other) { this->container = other.container; }

        /**
         * @brief Checks if the queue is empty.
         *
         * Complexity: O(1)
         *
         * @return true if the queue is empty, false otherwise.
         */
        inline bool empty() const { return this->container.empty(); }

        /**
         * @brief Returns the number of elements in the queue.
         *
         * Complexity: O(1)
         *
         * @return The length of the queue.
         */
        inline usize len() const { return this->container.len(); }

        /**
         * @brief Returns a reference to the first element in the queue.
         *
         * Complexity: O(1)
         *
         * @return A const reference to the first element.
         *
         * @note It's undefined behavior, if queue is empty.
         */
        const T& front() const { return this->container.front(); }

        /**
         * @brief Returns a reference to the first element in the queue.
         *
         * Complexity: O(1)
         *
         * @return A reference to the first element.
         *
         * @note It's undefined behavior, if queue is empty.
         */
        T& front() { return this->container.front(); }

        /**
         * @brief Returns a reference to the last element in the queue.
         *
         * Complexity: O(1)
         *
         * @return A const reference to the last element.
         *
         * @note It's undefined behavior, if queue is empty.
         */
        const T& back() const { return this->container.back(); }

        /**
         * @brief Returns a reference to the last element in the queue.
         *
         * Complexity: O(1)
         *
         * @return A reference to the last element.
         *
         * @note It's undefined behavior, if queue is empty.
         */
        T& back() { return this->container.back(); }

        /**
         * @brief Adds an element to the end of the queue.
         *
         * Complexity: O(1)
         *
         * @param value The value to be added to the queue.
         */
        void push(T value) { this->container.pushBack(value); }

        /**
         * @brief Removes and returns the first element in the queue.
         *
         * Complexity: O(1)
         *
         * @return The value of the first element.
         *
         * @note It's undefined behavior, if queue is empty.
         */
        T pop() { return this->container.popFront(); }

        /**
         * @brief Appends the elements of another queue to the current queue.
         *
         * Complexity: O(1)
         *
         * @param other The queue to be appended.
         */
        void append(Queue<T>& other) { this->container.append(other.container); }

        /**
         * @brief Reverses the order of elements in the queue.
         *
         * Complexity: O(n)
         */
        void reverse() { this->container.reverse(); }

        /**
         * @brief Removes all elements from the queue.
         *
         * Complexity: O(n)
         */
        void clear() { this->container.clear(); }

        /**
         * @brief Swaps the contents of two queues.
         *
         * Complexity: O(1)
         *
         * @param other The queue to be swapped with.
         */
        void swap(Queue<T>& other) { this->container.swap(other.container); }

        /**
         * @brief Converts the queue into a container.
         *
         * Complexity: O(n)
         *
         * @return A container containing the elements of the queue.
         */
        Container intoContainer() const { return this->container; }

        /**
         * @brief Concatenates two queues and returns a new queue.
         *
         * Complexity: O(n)
         *
         * @param other The queue to be concatenated.
         * @return A new queue containing the elements of both queues.
         */
        Queue<T> operator+(const Queue<T>& other) const {
            return Queue<T>(this->container + other.container);
        }

        /**
         * @brief Appends another queue to the current queue.
         *
         * Complexity: O(n)
         *
         * @param other The queue to be appended.
         * @return A reference to the updated queue.
         */
        Queue<T>& operator+=(const Queue<T>& other) {
            this->container += other.container;
            return *this;
        }

        /**
         * @brief Checks if two queues are equal.
         *
         * Complexity: O(n)
         *
         * @param other The queue to be compared.
         * @return true if the queues are equal, false otherwise.
         */
        bool operator==(const Queue<T>& other) const {
            return this->container == other.container;
        }

        /**
         * @brief Checks if two queues are not equal.
         *
         * Complexity: O(n)
         *
         * @param other The queue to be compared.
         * @return true if the queues are not equal, false otherwise.
         */
        bool operator!=(const Queue<T>& other) const {
            return this->container != other.container;
        }

        /**
         * @brief Assignment operator for Queue.
         *
         * Complexity: O(n)
         *
         * @param other The queue to be assigned.
         * @return A reference to the updated queue.
         */
        bool operator=(const Queue<T>& other) const { this->container = other.container; }

        /**
         * @brief Overloads the << operator for Queue.
         *
         * Complexity: O(n)
         *
         * @param out The output stream.
         * @param queue The queue to be outputted.
         * @return The updated output stream.
         */
        friend std::ostream& operator<<(std::ostream& out, const Queue<T>& queue) {
            return out << queue.container;
        }

        /**
         * @brief Overloads the >> operator for Queue.
         *
         * Complexity: O(n)
         *
         * @param out The input stream.
         * @param queue The queue to be outputted.
         * @return The input stream.
         */
        friend std::istream& operator>>(std::istream& in, const Queue<T>& queue) {
            return in >> queue.container;
        }

      private:
        /**
         * @brief the underlying container
         */
        Container container;
    };

} // namespace own

#endif // QUEUE_GUARD_HEADER
