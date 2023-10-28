#ifndef LIST_GUARD_HEADER
#define LIST_GUARD_HEADER

// std::swap
#include <algorithm>
// std::usize and NULL
#include <cstddef>
// std::ostream operator<< overloading
#include <ostream>
// std::istream operator>> overloading
#include <istream>
// std::out_of_range exception
#include <stdexcept>
// std::memmove
#include <cstring>

namespace own {

    /**
     * @brief Typedef for an unsigned integer representing size.
     *
     * This typedef is used to define an alias `usize` for `std::size_t`.
     * It is commonly used to represent the size of objects or arrays.
     */
    typedef std::size_t usize;

    /**
     * @brief Typedef for a signed long integer representing size.
     *
     * This typedef is used to define an alias `isize` for `signed long`.
     * It is commonly used to represent the size of objects or arrays, but in signed
     * form.
     */
    typedef signed long isize;

    /**
     * @brief Constant representing the absence of a valid position.
     *
     * This constant `NO_POS` is defined with a value of -1.
     * It is commonly used to indicate the absence of a valid position or index.
     */
    const usize NO_POS = -1;

    namespace details {

        /**
         * @brief A class representing a node in a linked list.
         *
         * @tparam T The type of the value stored in the node.
         */
        template <typename T>
        class Node {
          public:
            /**
             * @brief Constructs a new node with the given value, previous node, and next
             * node.
             *
             * Complexity: O(1)
             *
             * @param value The value to be stored in the node.
             * @param back  The previous node in the linked list.
             * @param next  The next node in the linked list.
             */
            Node(T value, Node<T>* back, Node<T>* next) {
                this->_value = value;
                this->_back = back;
                this->_next = next;
            }

            /**
             * @brief Constructs a new node with the given value and sets previous and
             * next nodes to NULL.
             *
             * Complexity: O(1)
             *
             * @param value The value to be stored in the node.
             */
            Node(T value) {
                this->_value = value;
                this->_back = NULL;
                this->_next = NULL;
            }

            /**
             * @brief Returns the value stored in the node.
             *
             * Complexity: O(1)
             *
             * @return A constant reference to the value stored in the node.
             */
            inline const T& value() const { return this->_value; }

            /**
             * @brief Returns the value stored in the node.
             *
             * Complexity: O(1)
             *
             * @return A reference to the value stored in the node.
             */
            inline T& value() { return this->_value; }

            /**
             * @brief Returns the previous node in the linked list.
             *
             * Complexity: O(1)
             *
             * @return A constant pointer to the previous node.
             */
            inline const Node<T>* back() const { return this->_back; }

            /**
             * @brief Returns the previous node in the linked list.
             *
             * Complexity: O(1)
             *
             * @return A pointer to the previous node.
             */

            inline Node<T>* back() { return this->_back; }
            /**
             * @brief Sets the previous node in the linked list.
             *
             * Complexity: O(1)
             *
             * @param node A pointer to the node to be set as the previous node.
             */
            inline void setBack(Node<T>* node) { this->_back = node; }

            /**
             * @brief Returns the next node in the linked list.
             *
             * Complexity: O(1)
             *
             * @return A constant pointer to the next node.
             */
            inline const Node<T>* next() const { return this->_next; }

            /**
             * @brief Returns the next node in the linked list.
             *
             * Complexity: O(1)
             *
             * @return A pointer to the next node.
             */
            inline Node<T>* next() { return this->_next; }

            /**
             * @brief Sets the next node in the linked list.
             *
             * Complexity: O(1)
             *
             * @param node A pointer to the node to be set as the next node.
             */
            inline void setNext(Node<T>* node) { this->_next = node; }

            /**
             * @brief Reverse the direction of the linked nodes.
             *
             * Complexity: O(1)
             */
            inline void reverse() { std::swap(this->_next, this->_back); }

            /**
             * @brief Link the current node to the given node as the next node.
             *
             * Complexity: O(1)
             *
             * ------------------------------------------------
             *
             * Before linking next:
             *
             *                 other
             *                  |
             * ... <=> [A] <=> [B] <=> [C] <=> ...
             *
             *                 this
             *                  |
             * ... <=> [D] <=> [E] <=> [F] <=> ...
             *
             * After unlinking other node:
             *
             *      ... <=> [A] <=> [C] <=> ...
             *
             *                 other
             *                  |
             *                 [B]
             *
             *                 this
             *                  |
             * ... <=> [D] <=> [E] <=> [F] <=> ...
             *
             * After linking next:
             *
             *             ... <=> [A] <=> [C] <=> ...
             *
             *                 this   other
             *                  |       |
             * ... <=> [D] <=> [E] <=> [B] <=> [F] <=> ...
             *
             * ------------------------------------------------
             *
             * @param next The node to be linked as the next node.
             */
            void linkNext(Node<T>* next) {
                if (next == NULL || next == this) {
                    return;
                }

                next->unlink();

                if (this->_next) {
                    next->_next = this->_next;
                    this->_next->_back = next;
                }

                next->_back = this;
                this->_next = next;
            }

            /**
             * @brief Link the current node to the given node as the previous node.
             *
             * Complexity: O(1)
             *
             * ------------------------------------------------
             *
             * Before linking back:
             *
             *                 other
             *                  |
             * ... <=> [A] <=> [B] <=> [C] <=> ...
             *
             *                 this
             *                  |
             * ... <=> [D] <=> [E] <=> [F] <=> ...
             *
             * After unlinking other node:
             *
             *      ... <=> [A] <=> [C] <=> ...
             *
             *                 other
             *                  |
             *                 [B]
             *
             *                 this
             *                  |
             * ... <=> [D] <=> [E] <=> [F] <=> ...
             *
             * After linking back:
             *
             *      ... <=> [A] <=> [C] <=> ...
             *
             *                 other   this
             *                  |       |
             * ... <=> [D] <=> [B] <=> [E] <=> [F] <=> ...
             *
             * ------------------------------------------------
             *
             */
            void linkBack(Node<T>* back) {
                if (back == NULL || back == this) {
                    return;
                }

                back->unlink();

                if (this->_back) {
                    back->_back = this->_back;
                    this->_back->_next = back;
                }

                back->_next = this;
                this->_back = back;
            }

            /**
             * @brief Unlink the current node from its neighbors.
             *
             * Complexity: O(1)
             *
             * ------------------------------------------------
             *
             * Before unlinking:
             *
             *                 this
             *                  |
             * ... <=> [A] <=> [B] <=> [C] <=> ...
             *
             * After unlinking:
             *
             *             this
             *              |
             *             [B]
             *
             * ... <=> [A] <=> [C] <=> ...
             *
             * ------------------------------------------------
             *
             */
            inline void unlink() {
                if (this->_back) {
                    this->_back->_next = this->_next;
                }
                if (this->_next) {
                    this->_next->_back = this->_back;
                }

                this->_back = NULL;
                this->_next = NULL;
            }

            /**
             * @brief Retrieves the value of the node at a given index in a linked list.
             *
             * Complexity: O(n)
             *
             * @param at The index of the node to retrieve.
             * @return A reference to the value of the node.
             *
             * @note If at is out of range, it'll be undefined behavior.
             */
            const T& operator[](isize at) const {
                if (at >= 0) {
                    const Node<T> node = this + at;
                    return node->value();
                } else {
                    const Node<T> node = this - (-at);
                    return node->value;
                }
            }

            /**
             * @brief Retrieves the value of the node at a given index in a linked list.
             *
             * Complexity: O(n)
             *
             * @param at The index of the node to retrieve.
             * @return A reference to the value of the node.
             *
             * @note If at is out of range, it'll be undefined behavior.
             */
            T& operator[](isize at) {
                if (at >= 0) {
                    const Node<T> node = this + at;
                    return node->value();
                } else {
                    const Node<T> node = this - (-at);
                    return node->value();
                }
            }

            /**
             * @brief Advances the current node pointer by a given number of steps.
             *
             * Complexity: O(n)
             *
             * @param at The number of steps to advance the pointer.
             * @return A pointer to the node after advancing.
             *
             * @note If at is out of range, it'll be undefined behavior.
             */
            const Node<T>* operator+(usize at) const {
                const Node<T>* it = this;
                for (; at > 0; at--) {
                    it = it->_next;
                }
                return it;
            }

            /**
             * @brief Advances the current node pointer by a given number of steps.
             *
             * Complexity: O(n)
             *
             * @param at The number of steps to advance the pointer.
             * @return A pointer to the node after advancing.
             *
             * @note If at is out of range, it'll be undefined behavior.
             */
            Node<T>* operator+(usize at) {
                Node<T>* it = this;
                for (; at > 0; at--) {
                    it = it->_next;
                }
                return it;
            }

            /**
             * @brief Moves the current node pointer backwards by a given number of steps.
             *
             * Complexity: O(n)
             *
             * @param at The number of steps to move the pointer backwards.
             * @return A pointer to the node after moving backwards.
             *
             * @note If at is out of range, it'll be undefined behavior.
             */
            const Node<T>* operator-(usize at) const {
                const Node<T>* it = this;
                for (; at > 0; at--) {
                    it = it->_back;
                }
                return it;
            }

            /**
             * @brief Moves the current node pointer backwards by a given number of steps.
             *
             * Complexity: O(n)
             *
             * @param at The number of steps to move the pointer backwards.
             * @return A pointer to the node after moving backwards.
             *
             * @note If at is out of range, it'll be undefined behavior.
             */
            Node<T>* operator-(usize at) {
                Node<T>* it = this;
                for (; at > 0; at--) {
                    it = it->_back;
                }
                return it;
            }

          private:
            /**
             * @brief Value stored in the node.
             */
            T _value;
            /**
             * @brief Pointer to the previous node.
             */
            Node<T>* _back;
            /**
             * @brief Pointer to the next node.
             */
            Node<T>* _next;
        };
    } // namespace details

    /**
     * @brief A template class for a double-linked list implementation.
     *
     * @tparam T The type of elements stored in the list.
     */
    template <typename T>
    class List {
      public:
        /**
         * @brief Default constructor.
         *
         * Initializes an empty list with head and tail set to NULL and length set to
         * 0.
         *
         * Complexity: O(1)
         */
        List() {
            this->head = NULL;
            this->tail = NULL;
            this->_len = 0;
        }

        /**
         * @brief Copy constructor.
         *
         * Creates a new list by copying the contents of another list.
         *
         * Complexity: O(n)
         *
         * @param other The list to be copied.
         */
        List(const List<T>& other) {
            this->head = NULL;
            this->tail = NULL;
            this->_len = 0;

            *this = other;
        }

        /**
         * @brief Destructor.
         *
         * Frees the memory occupied by the list and clears its contents.
         *
         * Complexity: O(n)
         */
        ~List() { this->clear(); }

        /**
         * @brief Checks if the list is empty.
         *
         * Complexity: O(1)
         *
         * @return True if the list is empty, false otherwise.
         */
        inline bool empty() const { return this->_len == 0; }

        /**
         * @brief Returns the length of the list.
         *
         * Complexity: O(1)
         *
         * @return The length of the list.
         */
        inline usize len() const { return this->_len; }

        /**
         * @brief Get the value of the front element of the list.
         *
         * Complexity: O(1)
         *
         * @return A reference to the value of the front element.
         *
         * @note it's undefined behavior if list is empty.
         */
        inline const T& front() const { return this->head->value(); }

        /**
         * @brief Get the value of the front element of the list.
         *
         * Complexity: O(1)
         *
         * @return A reference to the value of the front element.
         *
         * @note it's undefined behavior if list is empty.
         */
        inline T& front() { return this->head->value(); }

        /**
         * @brief Get the value of the element at the specified position.
         *
         * Complexity: O(1), if at = 0 or at = len - 1
         * Complexity: O(n), if 0 < at < len - 1
         *
         * @param at The position of the element.
         * @return A reference to the value of the element at the specified position.
         * @throws std::out_of_range if the specified position is out of range.
         */
        const T& at(usize at) const {
            if (at >= this->_len) {
                throw std::out_of_range("List::at out of range");
            }

            return this->atNode(at)->value();
        }

        /**
         * @brief Get the value of the element at the specified position.
         *
         * Complexity: O(1), if at = 0 or at = len - 1
         * Complexity: O(n), if 0 < at < len - 1
         *
         * @param at The position of the element.
         * @return A reference to the value of the element at the specified position.
         * @throws std::out_of_range if the specified position is out of range.
         */
        T& at(usize at) {
            if (at >= this->_len) {
                throw std::out_of_range("List::at out of range");
            }

            return this->atNode(at)->value();
        }

        /**
         * @brief Get the value of the back element of the list.
         *
         * Complexity: O(1)
         *
         * @return A reference to the value of the back element.
         *
         * @note it's undefined behavior if list is empty.
         */
        inline const T& back() const { return this->tail->value(); }

        /**
         * @brief Get the value of the back element of the list.
         *
         * Complexity: O(1)
         *
         * @return A reference to the value of the back element.
         *
         * @note it's undefined behavior if list is empty.
         */
        inline T& back() { return this->tail->value(); }

        /**
         * @brief Insert a new element at the front of the list.
         *
         * Complexity: O(1)
         *
         * @param value The value of the new element.
         */
        void pushFront(T value) {
            details::Node<T>* node = new details::Node<T>(value, NULL, this->head);

            if (this->head) {
                this->head->setBack(node);
            } else {
                this->tail = node;
            }

            this->head = node;
            this->_len++;
        }

        /**
         * @brief Removes and returns the first element of the list.
         *
         * Complexity: O(1)
         *
         * @return The value of the removed element.
         *
         * @note it's undefined behavior if list is empty.
         */
        T popFront() {
            details::Node<T>* node = this->head;
            T value = node->value();

            this->_len--;

            this->head = node->next();
            if (this->head == NULL) {
                this->tail = NULL;
            }

            node->unlink();
            delete node;

            return value;
        }

        /**
         * @brief Adds an element to the end of the list.
         *
         * Complexity: O(1)
         *
         * @param value The value to be added.
         */
        void pushBack(T value) {
            details::Node<T>* node = new details::Node<T>(value, this->tail, NULL);

            if (this->tail) {
                this->tail->setNext(node);
            } else {
                this->head = node;
            }

            this->tail = node;
            this->_len++;
        }

        /**
         * @brief Removes and returns the last element of the list.
         *
         * Complexity: O(1)
         *
         * @return The value of the removed element.
         *
         * @note it's undefined behavior if list is empty.
         */
        T popBack() {
            details::Node<T>* node = this->tail;
            T value = node->value();

            this->_len--;

            this->tail = node->back();
            if (this->tail == NULL) {
                this->head = NULL;
            }

            node->unlink();
            delete node;

            return value;
        }

        /**
         * @brief Inserts an element at the specified index in a forward direction.
         *
         * Complexity: O(1), if at = 0 or at >= len
         * Complexity: O(n), if 0 < at < len
         *
         * @param value The value to be inserted.
         * @param at The index at which the value should be inserted.
         */
        inline void insertForward(T value, usize at) { this->insert(value, at, false); }

        /**
         * @brief Inserts an element at the specified index in a backward direction.
         *
         * Complexity: O(1), if at = 0 or at >= len
         * Complexity: O(n), if 0 < at < len
         *
         * @param value The value to be inserted.
         * @param at The index at which the value should be inserted.
         */
        inline void insertBackward(T value, usize at) { this->insert(value, at, true); }

        /**
         * @brief Checks if the list contains a specific value.
         *
         * Complexity: O(n)
         *
         * @param value The value to be checked.
         * @return True if the list contains the value, false otherwise.
         */
        bool contains(const T& value) const { return this->find(value) != NO_POS; }

        /**
         * @brief Checks if a list is contained in this list.
         *
         * If the other list is empty, then it's trivially true
         *
         * Complexity: O(n^2)
         *
         * @param other The list to be checked.
         * @return True if the list contains all the values, false otherwise.
         */
        bool contains(const List<T>& other) const {
            for (details::Node<T>* it = other.head; it; it = it->next()) {
                if (!this->contains(it->value())) {
                    return false;
                }
            }

            return true;
        }

        /**
         * @brief Finds the first occurrence of a specific value in the list.
         *
         * Complexity: O(n)
         *
         * @param value The value to be found.
         * @param skip How many elements to ignore.
         * @return The index of the first occurrence of the value, or NO_POS if not found.
         */
        usize find(const T& value, usize skip = 0) const {
            if (skip >= this->_len) {
                return NO_POS;
            }

            usize at = skip;

            for (details::Node<T>* it = *this->head + skip; it; it = it->next()) {
                if (it->value() == value) {
                    return at;
                }

                at++;
            }

            return NO_POS;
        }

        /**
         * @brief Finds the last occurrence of a specific value in the list.
         *
         * Complexity: O(n)
         *
         * @param value The value to be found.
         * @param skip How many elements to ignore.
         * @return The index of the last occurrence of the value, or NO_POS if not found.
         */
        usize rfind(const T& value, usize skip = 0) const {
            if (skip >= this->_len) {
                return NO_POS;
            }

            usize at = this->_len - skip - 1;

            for (details::Node<T>* it = this->tail - skip; it; it = it->back()) {
                if (it->value() == value) {
                    return at;
                }

                at--;
            }

            return NO_POS;
        }

        /**
         * @brief Finds all occurrences of a specific value in the list.
         *
         * Complexity: O(n)
         *
         * @param value The value to be found.
         * @return A list of indices where the value is found.
         */
        List<usize> findAll(const T& value) const {
            List<usize> indices;

            usize at = 0;

            for (details::Node<T>* it = this->head; it; it = it->next()) {
                if (it->value() == value) {
                    indices.pushBack(at);
                }

                at++;
            }

            return indices;
        }

        /**
         * @brief Removes the element at the specified index.
         *
         * If the index is 0, the first element is removed.
         * If the index is greater than or equal to the length, the last element is
         * removed.
         *
         * Complexity: O(1), if at = 0 or at = len - 1
         * Complexity: O(n), if 0 < at < len - 1
         *
         * @param at The index of the element to remove.
         * @return The removed element.
         *
         * @note it's undefined behavior if list is empty.
         */
        T remove(usize at) {
            if (at == 0) {
                this->popFront();
                return;
            }
            if (at >= this->_len - 1) {
                this->popBack();
                return;
            }

            details::Node<T>* node = this->atNode(at);
            T value = node->value();

            this->_len--;

            node->unlink();
            delete node;

            return value;
        }

        /**
         * @brief Retains only the elements in the list that match the given filter
         * function.
         *
         * Complexity: O(n)
         *
         * @param filter A filter function that takes an element and returns true if it
         * should be retained, false otherwise.
         * @param ctx The context of filter.
         * @return The number of elements that were removed.
         * @tparam Context The context data-type
         */
        template <typename Context>
        usize retainIf(bool (*filter)(const T&, Context&), Context& ctx) {
            usize oldOld = this->_len;

            details::Node<T>* it = this->head;
            while (it) {
                if (filter(*it, ctx)) {
                    it = it->next();
                } else {
                    this->_len--;
                    details::Node<T>* next = it->next();

                    if (it == this->head) {
                        this->head = next;
                    }
                    if (it == this->tail) {
                        this->tail = next;
                    }

                    it->unlink();
                    delete it;

                    it = next;
                }
            }

            return oldOld - this->_len;
        }

        /**
         * @brief Retains only the elements in the list that match the given filter
         * function.
         *
         * Complexity: O(n)
         *
         * @param filter A filter function that takes an element and returns true if
         * it should be retained, false otherwise.
         * @return The number of elements that were removed.
         */
        usize retainIf(bool (*filter)(const T&)) {
            usize oldLen = this->_len;

            details::Node<T>* it = this->head;
            while (it) {
                if (filter(*it)) {
                    it = it->next();
                } else {
                    this->_len--;
                    details::Node<T>* next = it->next();

                    if (it == this->head) {
                        this->head = next;
                    }
                    if (it == this->tail) {
                        this->tail = next;
                    }

                    it->unlink();
                    delete it;

                    it = next;
                }
            }

            return oldLen - this->_len;
        }

        /**
         * @brief Removes all elements from the list that match the given filter
         * function.
         *
         * Complexity: O(n)
         *
         * @param filter A filter function that takes an element and returns true if it
         * should be removed, false otherwise.
         * @param ctx The context of filter
         * @return The number of elements that were removed.
         * @tparam Context The context data-type
         */
        template <typename Context>
        usize removeIf(bool (*filter)(const T&, Context&), Context& ctx) {
            usize oldLen = this->_len;

            details::Node<T>* it = this->head;
            while (it) {
                if (filter(*it, ctx)) {
                    this->_len--;
                    details::Node<T>* next = it->next();

                    it->unlink();
                    delete it;

                    it = next;
                } else {
                    it = it->next();
                }
            }

            return oldLen - this->_len;
        }

        /**
         * @brief Removes all elements from the list that match the given filter function.
         *
         * Complexity: O(n)
         *
         * @param filter A filter function that takes an element and returns true if it
         * should be removed, false otherwise.
         * @return The number of elements that were removed.
         */
        usize removeIf(bool (*filter)(const T&)) {
            usize oldLen = this->_len;

            details::Node<T>* it = this->head;
            while (it) {
                if (filter(*it)) {
                    this->_len--;
                    details::Node<T>* next = it->next();

                    it->unlink();
                    delete it;

                    it = next;
                } else {
                    it = it->next();
                }
            }

            return oldLen - this->_len;
        }

        /**
         * @brief This function appends the elements in the provided list to the end
         * of the current list.
         *
         * Complexity: O(1)
         *
         * @param other The list to be appended.
         * @tparam T The type of elements in the list.
         */
        void append(List<T>& other) {
            if (other.isEmpty()) {
                return;
            }
            if (this->_len == 0) {
                this->swap(other);
                return;
            }

            this->_len += other._len;

            this->tail->setNext(other.head);
            other.head->setBack(this->tail);

            this->tail = other.tail;

            other._len = 0;
            other.head = NULL;
            other.tail = NULL;
        }

        /**
         * @brief This function slices off a portion of the current list and returns
         * it as a new list.
         *
         * Complexity: O(1), if start = 0 and end = len
         * Complexity: O(n), if start > 0 or end < len
         *
         * @param start The starting index of the slice.
         * @param end The ending index of the slice.
         * @return The sliced portion of the list as a new list.
         * @tparam T The type of elements in the list.
         */
        List<T> sliceOff(usize start, usize end) {
            if (start >= this->_len) {
                start = this->_len;
            }
            if (end > this->_len) {
                end = this->_len;
            }
            if (start >= end) {
                return List<T>();
            }

            details::Node<T>* startNode = this->atNode(start);
            details::Node<T>* endNode = this->atNode(end - 1);

            details::Node<T>* backNode = startNode->back();
            details::Node<T>* nextNode = endNode->next();

            if (backNode) {
                backNode->setNext(nextNode);
            }
            if (nextNode) {
                nextNode->setBack(backNode);
            }

            startNode->setBack(NULL);
            endNode->setNext(NULL);

            List<T> extractedList;

            extractedList._len = end - start;
            extractedList.head = startNode;
            extractedList._end = endNode;

            return extractedList;
        }

        /**
         * @brief This function reverses the order of elements in the current list.
         *
         * Complexity: O(n)
         */
        void reverse() {
            if (this->isEmpty()) {
                return;
            }

            // once reversed node, back is acting as next
            for (details::Node<T>* it = this->head; it; it = it->back()) {
                it->reverse();
            }

            std::swap(this->head, this->tail);
        }

        /**
         * @brief Clears the list by deleting all nodes and resetting the length and
         * head and tail pointers.
         *
         * Complexity: O(n)
         */
        void clear() {
            details::Node<T>* it = this->head;
            while (it) {
                details::Node<T>* next = it->next();
                delete it;
                it = next;
            }

            this->_len = 0;
            this->head = NULL;
            this->tail = NULL;
        }

        /**
         * @brief Swaps the contents of this list with another list.
         *
         * Complexity: O(1)
         *
         * @param other The list to swap with.
         */
        void swap(List<T>& other) {
            if (this == &other) {
                return;
            }

            std::swap(this->_len, other._len);
            std::swap(this->head, other.head);
            std::swap(this->tail, other.tail);
        }

        /**
         * @brief Applies the given action to each element in the list.
         *
         * The action is a function that takes a const reference to the element.
         *
         * Base Complexity: O(n)
         *
         * @param action The function to apply to each element.
         * @param ctx The context of action
         * @tparam Context the ctx data-type
         */
        template <typename Context>
        void forEach(void (*action)(const T&, Context&), Context& ctx) const {
            for (const details::Node<T>* it = this->head; it; it = it->next()) {
                action(it->value(), ctx);
            }
        }

        /**
         * @brief Applies the given action to each element in the list.
         *
         * The action is a function that takes a const reference to the element.
         *
         * Base Complexity: O(n)
         *
         * @param action The function to apply to each element.
         */
        void forEach(void (*action)(const T&)) const {
            for (const details::Node<T>* it = this->head; it; it = it->next()) {
                action(it->value());
            }
        }

        /**
         * @brief Applies the given action to each element in the list.
         *
         * The action is a function that takes a reference to the element.
         *
         * Base Complexity: O(n)
         *
         * @param action The function to apply to each element.
         * @param ctx The context of action
         * @tparam Context the ctx data-type
         */
        template <typename Context>
        void forEach(void (*action)(T&, Context&), Context& ctx) {
            for (details::Node<T>* it = this->head; it; it = it->next()) {
                action(it->value(), ctx);
            }
        }

        /**
         * @brief Applies the given action to each element in the list.
         *
         * The action is a function that takes a reference to the element.
         *
         * Base Complexity: O(n)
         *
         * @param action The function to apply to each element.
         */
        template <typename Context>
        void forEach(void (*action)(T&)) {
            for (details::Node<T>* it = this->head; it; it = it->next()) {
                action(it->value());
            }
        }

        /**
         * Folds the list by applying an action function to each element.
         * The action function takes three parameters: const T&, B&, Context&.
         *
         * @param action   The action function to be applied to each element.
         * @param initial  The initial value for folding.
         * @param ctx      The context object passed to the action function.
         *
         * @return         The final folded value.
         */
        template <typename B, typename Context>
        B fold(void (*action)(const T&, B&, Context&), B initial, Context& ctx) const {
            for (const details::Node<T>* it = this->head; it; it = it->next()) {
                action(it->value(), initial, ctx);
            }

            return initial;
        }

        /**
         * Folds the list by applying an action function to each element.
         * The action function takes three parameters: const T&, B&, with no context.
         *
         * @param action   The action function to be applied to each element.
         * @param initial  The initial value for folding.
         *
         * @return         The final folded value.
         */
        template <typename B>
        B fold(void (*action)(const T&, B&), B initial) const {
            for (const details::Node<T>* it = this->head; it; it = it->next()) {
                action(it->value(), initial);
            }

            return initial;
        }

        /**
         * Folds the list by applying an action function to each element.
         * The action function takes three parameters: const T&, B&, Context&.
         *
         * @param action   The action function to be applied to each element.
         * @param initial  The initial value for folding.
         * @param ctx      The context object passed to the action function.
         *
         * @return         The final folded value.
         */
        template <typename B, typename Context>
        B fold(void (*action)(T&, B&, Context&), B initial, Context& ctx) {
            for (details::Node<T>* it = this->head; it; it = it->next()) {
                action(it->value(), initial, ctx);
            }

            return initial;
        }

        /**
         * Folds the list by applying an action function to each element.
         * The action function takes three parameters: const T&, B&, with no context.
         *
         * @param action   The action function to be applied to each element.
         * @param initial  The initial value for folding.
         *
         * @return         The final folded value.
         */
        template <typename B>
        B fold(void (*action)(T&, B&), B initial) {
            for (details::Node<T>* it = this->head; it; it = it->next()) {
                action(it->value(), initial);
            }

            return initial;
        }

        /**
         * Applies a given action on a sliding window of size N over the elements of the
         * current list. The action is a function pointer that takes an array of size N
         * and returns a value of type R.
         *
         * @param action The function pointer to be applied on the sliding window.
         * @return A list containing the results of applying the action on the sliding
         * window.
         * @tparam N The size of the sliding window.
         * @tparam R The return type of the action function.
         */
        template <usize N, typename R>
        List<R> window(R (*action)(T[N])) const {
            T window[N];

            const details::Node<T>* it = this->head;
            usize i = 0;

            List<R> result;

            while (it) {
                if (N > 1) {
                    std::memmove(&window[0], &window[1], sizeof(T) * (N - 1));
                }
                window[N - 1] = it->value();

                if (i + 1 >= N) {
                    result.pushBack(action(window));
                }

                it = it->next();
                i++;
            }

            return result;
        }

        /**
         * Applies a given action on a sliding window of size N over the elements of the
         * current list. The action is a function pointer that takes an array of size N
         * and returns a value of type R.
         *
         * @param action The function pointer to be applied on the sliding window.
         * @return A list containing the results of applying the action on the sliding
         * window.
         * @tparam R The return type of the action function.
         */
        template <typename R>
        List<R> window(R (*action)(T*, usize n), usize n) const {
            T* window = new T[n];

            const details::Node<T>* it = this->head;
            usize i = 0;

            List<R> result;

            while (it) {
                if (n > 1) {
                    std::memmove(&window[0], &window[1], sizeof(T) * (n - 1));
                }
                window[n - 1] = it->value();

                if (i + 1 >= n) {
                    result.pushBack(action(window, n));
                }

                it = it->next();
                i++;
            }

            return result;
        }

        /**
         * @brief Returns a reference to the element at the specified position.
         *
         * Complexity: O(1), if at = 0 or at = len - 1
         * Complexity: O(n), if 0 < at < len - 1
         *
         * @param at The position of the element to access.
         * @return A const reference to the element at the specified position.
         *
         * @note it's undefined behavior if at is out of range.
         */
        const T& operator[](usize at) const { return this->atNode(at)->value(); }

        /**
         * @brief Returns a reference to the element at the specified position.
         *
         * Complexity: O(1), if at = 0 or at = len - 1
         * Complexity: O(n), if 0 < at < len - 1
         *
         * @param at The position of the element to access.
         * @return A reference to the element at the specified position.
         *
         * @note it's undefined behavior if at is out of range.
         */
        T& operator[](usize at) { return this->atNode(at)->value(); }

        /**
         * @brief Concatenates this list with another list and returns a new list.
         *
         * Complexity: O(n)
         *
         * @param other The list to concatenate with.
         * @return A new list that contains elements from both lists.
         */
        List<T> operator+(const List<T>& other) const {
            List<T> newList;

            for (const details::Node<T>* it = this->head; it; it = it->next()) {
                newList.pushBack(it->value());
            }
            for (const details::Node<T>* it = other.head; it; it = it->next()) {
                newList.pushBack(it->value());
            }

            return newList;
        }

        /**
         * @brief Appends the elements of another list to this list.
         *
         * Complexity: O(n)
         *
         * @param other The list to append.
         * @return A reference to this list after the append operation.
         */
        List<T>& operator+=(const List<T>& other) {
            for (const details::Node<T>* it = other.head; it; it = it->next()) {
                this->pushBack(it->value());
            }

            return *this;
        }

        /**
         * @brief Overloads the equality operator to check if two lists are equal.
         *
         * Complexity: O(n)
         *
         * @param other The list to compare with.
         * @return True if the lists are equal, false otherwise.
         */
        bool operator==(const List<T>& other) const {
            if (this == &other) {
                return true;
            }
            if (this->_len != other._len) {
                return false;
            }

            const details::Node<T>* it = this->head;
            const details::Node<T>* otherIt = other.head;

            while (it) {
                if (it->value() != otherIt->value()) {
                    return false;
                }

                it = it->next();
                otherIt = otherIt->next();
            }

            return true;
        }

        /**
         * @brief Overloads the inequality operator to check if two lists are not
         * equal.
         *
         * Complexity: O(n)
         *
         * @param other The list to compare with.
         * @return True if the lists are not equal, false otherwise.
         */
        bool operator!=(const List<T> other) const { return !(this == other); }

        /**
         * @brief Overloads the assignment operator to assign the content of another
         * list to this list.
         *
         * Complexity: O(n)
         *
         * @param other The list to assign from.
         */
        void operator=(const List<T>& other) {
            if (this == &other) {
                return;
            }

            this->clear();

            this->_len = other._len;

            details::Node<T>* previous = NULL;

            for (const details::Node<T>* it = other.head; it; it = it->next()) {
                details::Node<T>* current = new details::Node<T>(it->value());

                if (previous) {
                    current->setBack(previous);
                    previous->setNext(current);
                } else {
                    this->head = current;
                }

                previous = current;
            }

            this->tail = previous;
        }

        /**
         * @brief Overloads the output stream operator to print the list as a string
         * representation.
         *
         * Complexity: O(n)
         *
         * @param out The output stream.
         * @param list The list to print.
         * @return The output stream after printing the list.
         */
        friend std::ostream& operator<<(std::ostream& out, const List<T>& list) {
            out << '[';

            if (list.len() > 0) {
                out << list.front();

                for (own::details::Node<T>* it = list.head->next(); it; it = it->next()) {
                    out << ", " << it->value();
                }
            }

            out << ']';
            return out;
        }

        /**
         * @brief Overloads the input stream operator to get the list from a string
         * representation.
         *
         * Complexity: O(n)
         *
         * @param in The input stream.
         * @param list The list to print.
         * @return The input stream.
         */
        friend std::istream& operator>>(std::istream& in, List<T>& list) {
            char ch = 0;
            in >> ch;

            if (in.fail() || ch != '[') {
                in.setstate(std::ios_base::failbit);
                return in;
            }

            in >> ch;
            if (in.fail() || ch == ']') {
                return in;
            }

            for (; ch == ',' && in.good(); in >> ch) {
                T value;
                in >> value;

                if (in.good()) {
                    list.pushBack(value);
                }
            }

            in >> ch;

            if (in.fail() || ch != '[') {
                in.setstate(std::ios_base::failbit);
                return in;
            }

            return in;
        }

      private:
        /**
         * @brief Returns a pointer to the node at the specified index in the list.
         *
         * Complexity: O(1), if at = 0 or at = len - 1
         * Complexity: O(n), if 0 < at < len - 1
         *
         * @param at The index of the node to retrieve.
         * @return A pointer to the node at the specified index.
         *
         * @note it's undefined behavior if at is out of range.
         */
        inline const details::Node<T>* atNode(usize at) const {
            if (at == 0) {
                return this->head;
            }
            if (at == this->_len - 1) {
                return this->tail;
            }

            // choose what's the shortest path
            if (at <= this->_len / 2) {
                return *this->head + at;
            } else {
                return *this->tail - (this->_len - at - 1);
            }
        }

        /**
         * @brief Returns a pointer to the node at the specified index in the list.
         *
         * Complexity: O(1), if at = 0 or at = len - 1
         * Complexity: O(n), if 0 < at < len - 1
         *
         * @param at The index of the node to retrieve.
         * @return A pointer to the node at the specified index.
         *
         * @note it's undefined behavior if at is out of range.
         */
        inline details::Node<T>* atNode(usize at) {
            if (at == 0) {
                return this->head;
            }
            if (at == this->_len - 1) {
                return this->tail;
            }

            // choose what's the shortest path
            if (at <= this->_len / 2) {
                return *this->head + at;
            } else {
                return *this->tail - (this->_len - at - 1);
            }
        }

        /**
         * @brief Inserts a new node with the specified value at the specified index
         in
         * the list.
         *
         * Complexity: O(1), if at = 0 or at = len - 1
         * Complexity: O(n), if 0 < at < len - 1
         *
         * Depending on backwarded option, it may happen the following:
         *
         * ------------------------------------------------
         *
         * The new node to be inserted:
         *
         +                    new
         *                    |
         *                   [D]
         *
         * The list:
         *
         +                    at
         *                    |
         *   ... <=> [A] <=> [B] <=> [C] <=> ...
         *
         * If backwarded is enabled:
         *
         *                    new     at
         *                    |       |
         *   ... <=> [A] <=> [D] <=> [B] <=> [C] <=> ...
         *
         * If backwarded is disabled:
         *
         *                    at     new
         *                    |       |
         *   ... <=> [A] <=> [B] <=> [D] <=> [C] <=> ...
         *
         * ------------------------------------------------
         *
         * @param value The value to insert.
         * @param at The index at which to insert the new node.
         * @param backwarded Determines whether to insert the new node before or after
         the
         * specified index.
         */
        void insert(T value, usize at, bool backwarded) {
            if (at == 0 && backwarded) {
                this->pushFront(value);
                return;
            }
            if (at >= this->_len) {
                this->pushBack(value);
                return;
            }
            if (at == this->_len - 1 && !backwarded) {
                this->pushBack(value);
                return;
            }

            details::Node<T>* node = this->atNode(at);
            if (backwarded) {
                node->linkBack(new details::Node<T>(value));
            } else {
                node->linkNext(new details::Node<T>(value));
            }

            this->_len++;
        }

      private:
        /**
         * @brief The length of the list.
         */
        usize _len;
        /**
         * @brief Pointer to the head node of the list.
         */
        details::Node<T>* head;
        /**
         * @brief Pointer to the tail node of the list.
         */
        details::Node<T>* tail;
    };

} // namespace own

#endif // LIST_GUARD_HEADER
