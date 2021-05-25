#include <iostream>

using namespace std;

struct NODE {
	int data;
	int type;
	NODE* next;
};
struct Queue {
	NODE* front;
	NODE* rear;
};

void init(Queue& q) {
	q.front = q.rear = nullptr;
}
bool empty(Queue& q) {
	return q.front == nullptr;
}
void enqueue(Queue& q, int val, int type) {
	NODE* tmp;
	tmp = new NODE;
	tmp->data = val;
	tmp->type = type;
	tmp->next = nullptr;
	if (empty(q)) {
		q.front = q.rear = tmp;
		return;
	}
	q.rear->next = tmp;
	q.rear = tmp;
}
void dequeue(Queue& q) {
	NODE* tmp;
	if (empty(q)) return;

	tmp = q.front;
	q.front = q.front->next;
	delete tmp;
	if (q.front == nullptr) q.rear = nullptr;
	return;
}
NODE* front(Queue& q) {
	if (empty(q)) { cerr << "Error" << endl; exit(1); }
	return q.front;
}

NODE* rear(Queue& q) {
	if (empty(q)) { cerr << "Error" << endl; exit(1); }
	return q.rear;
}
int sizeQueue(Queue& q) {
	NODE* cur;
	int c = 0;
	if (empty(q)) return 0;
	cur = q.front;
	while (cur != nullptr) {
		c++;
		cur = cur->next;
	}
	return c;
}
void display(Queue& q) {
	NODE* cur;
	if (empty(q)) {
		cout << "Empty queue" << endl;
		return;
	}
	cur = q.front;
	while (cur != nullptr) {
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}

void initQueueArray(Queue*& q, int N) {
	for (int i = 0; i < N; i++) {
		q[i].front = q[i].rear = nullptr;
	}
}

void dequeuePriority(Queue*& q, int n, int N) {
	int rem = n;
	int i;
	for (i = 0; i < N; i++) {
		if (rem <= 0) {
			return;
		}
		if (sizeQueue(q[i]) == n) {
			for (int j = 0; j < sizeQueue(q[i]); j++) {
				dequeue(q[i]);
				return;
			}
		}
		if (sizeQueue(q[i]) < rem) {
			int s = sizeQueue(q[i]);
			rem = rem - sizeQueue(q[i]);
			for (int j = 0; j < s; j++) {
				dequeue(q[i]);
			}
			continue;
		}
		if (sizeQueue(q[i]) > rem) {
			int s = sizeQueue(q[i]);
			for (int j = 0; j < rem; j++) {
				dequeue(q[i]);
			}
			rem = rem - s;
			continue;
		}
	}
}

int main()
{
	srand(time(0));

	int N = (rand() % 10) + 1; // number of data.
	int n; // number of data that will be served.
	int nb = 3; // number of time the queues will receive and serve.

	float* sumq = new float[N](); // used to calculate the average size.

	int* nn = new int[N]; // array of data that will be enqueued.

	Queue* qa = new Queue[N];
	initQueueArray(qa, N);

	for (int k = 0; k < nb; k++) {
		n = (rand() % 10) + 1;
		cout << "Number of data to be dequeued: " << n << endl;
		cout << "Number of data: " << N << endl;

		for (int i = 0; i < N; i++) { // fill in the array of data with random numbers.
			nn[i] = (rand() % 10) + 1;
		}

		for (int i = 0; i < N; i++) { // enqueue the queues with zeros.
			for (int j = 0; j < nn[i]; j++) {
				enqueue(qa[i], 0, i);
			}
		}

		for (int i = 0; i < N; i++) { // Display each queue before dequeue.
			cout << "q" << i + 1 << " before dequeue: ";
			display(qa[i]);
		}
		
		dequeuePriority(qa, n, N);

		for (int i = 0; i < N; i++) { // Display size of each queue after dequeue.
			sumq[i] = sumq[i] + sizeQueue(qa[i]);
			cout << "Size of q" << i << ": " << sizeQueue(qa[i]);
			cout << endl;
		}
		cout << endl;
	
	}
	
	for (int i = 0; i < N; i++) { // Display the average size of each queue.
		cout << "q" << i + 1 << " average size is: " << sumq[i] / 3 << endl;
	}
}