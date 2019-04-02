#include <iostream>
#include <assert.h>

template<class T>
 class Queue {
 public:
	Queue();
	~Queue();

	// Добавить элемент в очередь
	void Enqueue(const T& data);
	// Извлечь элемент из очереди
	T Dequeue();
	// Получить головной элемент
	const T& GetHead() const;
	// Есть ли элементы
	bool IsEmpty() const;

 private:
	 struct Node {
		 T Data;
		 Node* Next;
		 Node() : Next(nullptr) {}
	 };
	 Node* head;
	 Node* tail;
 };

template<class T>
Queue<T>::Queue() :
	head(nullptr),
	tail(nullptr)
{
}

template<class T>
Queue<T>::~Queue() 
{
	while( !IsEmpty() ) {
		Dequeue();
	}
}

template<class T>
void Queue<T>::Enqueue(const T& data)
{
	Node* node = new Node;
	node->Data = data;
	if( IsEmpty() ) {
		head = tail = node;
	} else {
		tail->Next = node;
		tail = tail->Next;
	}
}

template<class T>
T Queue<T>::Dequeue()
{
	assert( !IsEmpty() );

	T tempData = head->Data;
	Node* tempNode = head;
	head = head->Next;
	if( head == nullptr ) {
		tail = nullptr;
	}
	delete tempNode;
	return tempData;
}

template<class T>
const T& Queue<T>::GetHead() const
{
	assert( !IsEmpty() );
	return head->Data;
}

template<class T>
bool Queue<T>::IsEmpty() const
{
	return head == nullptr;
}

int main() {
	Queue<int> queue;
	int n = 0;
	std::cin >> n;
	bool result = true;
	for( int i = 0; i < n; i++ ) {
		int command = 0;
		int data = 0;
		std::cin >> command >> data;
		switch( command ) {
		case 2:
			if( queue.IsEmpty() ) {
				result = result && data == -1;
			} else {
				result = result && queue.Dequeue() == data;
			}
			break;
		case 3:
			queue.Enqueue(data);
			break;

		}
	}

	std::cout << (result ? "YES" : "NO");
	return 0;
}