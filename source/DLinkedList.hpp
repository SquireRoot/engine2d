
namespace engine2d {
	template <class T>
	class DLinkedList {
	private:
		struct dllbucket {
			dllbucket* prev = NULL;
			dllbucket* next = NULL;
			T* data;
		};

		dllbucket* first = NULL;
		dllbucket* last = NULL;

		dllbucket* listPosition = NULL;

	public:
		uint32 size = 0;

		T* next() {
			if (listPosition->next != NULL && size > 1) {
				listPosition = listPosition->next;
				return listPosition->data;
			}
			return NULL;
		}

		T* current() {
			if (size > 0) {
				return listPosition->data;
			}
			return NULL;
		}

		T* previous() {
			if (listPosition->prev != NULL && size > 1) {
				listPosition = listPosition->prev;
				return listPosition->data;
			}
			return NULL;
		}

		void setItBegin() { // resets the list position to the first index
			listPosition = first; 
		}

		void setItEnd() {
			listPosition = last;
		}

		void add(T* element) {
			dllbucket* bucket = new dllbucket();
			bucket->data = element;

			if (size == 0) {
				first = bucket;
				last = bucket;
				listPosition = bucket;
			} else {
				last->next = bucket;
				bucket->prev = last;
				last = bucket;
			}

			size++;
		}

		T* remove() {
			if (size > 0) {
				T* returnval = listPosition->data;

				if (size >= 1) {
					if (listPosition == first) {
						first = listPosition->next;
						listPosition->next->prev = NULL;
					} else {
						listPosition->prev->next = listPosition->next;
					}

					if (listPosition == last) {
						last = listPosition->prev;
						listPosition->prev->next = NULL;
					} else {
						listPosition->next->prev = listPosition->prev;
					}

					T* returnval = listPosition->data;
					delete listPosition;
					size--;

				} else if (size == 1) {
					delete listPosition;
					listPosition = NULL;
					first = NULL;
					last = NULL;
					size = 0;
				}

				setItBegin();
				return returnval;
			}
			return NULL;
		}

		void insert(T* element) { // element will be inserted before the current bucket and listpos is set to the inserted value
			dllbucket* newBucket = new dllbucket();
			newBucket->data = element;

			if (size == 0) {
				add(element);
				size++;
				return;
			}

			if (listPosition == first) {
				first = newBucket;
			} else {
				listPosition->prev->next = newBucket;
				newBucket->prev = listPosition->prev;
			}

			listPosition->prev = newBucket;
			newBucket->next = listPosition;
			size++;
		}

		void swap(dllbucket* bucket1, dllbucket* bucket2) {
			T* temp = bucket1->data;
			bucket1->data = bucket2->data;
			bucket2->data = temp;
		}
	};
}