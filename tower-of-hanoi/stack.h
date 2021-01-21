#include <vector>
#include "disc.h"

class Stack {

    struct Node {
        Disc *data;
        Node *pNext;
    };

	public:
		Stack();
        ~Stack();

		void push(Disc* in);
        Disc* pop();
        [[maybe_unused]] [[nodiscard]] Disc* top() const;
        [[maybe_unused]] [[nodiscard]] bool empty() const;
        void display() const;

        Node *pTop;
};
