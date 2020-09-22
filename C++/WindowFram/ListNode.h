#pragma once

#include "Global.h"

// 템플릿 링크드 리스트

// 노드 클래스

template <typename T>
class Node {
private:
	T data;	// 정해지지 않는 자료형이 노드의 데이터이다.
	Node<T>* next;	// 노드의 링크
public:
	// 변수 초기화
	Node<T>() {
		memset(&data, 0, sizeof(data));
		next = nullptr;
	}
	// 생성자 오버로딩
	Node<T>(T _data) {
		data = _data;
		next = nullptr;
	}

	~Node<T>() {

	}

	// 쓰기 접근자
	void SetData(T _data) {
		data = _data;
	}
	void SetNext(Node<T>* _next) {
		next = _next;
	}

	// 읽기 접근자
	T GetData() { return data; }
	Node<T>* GetNext() { return next; }
};

// 링크드 리스트

template <typename T>
class ListNode {
private:
	Node<T>* head;	// 첫 노드
	Node<T>* Tail;	// 마지막 노드
public:
	ListNode<T>();
	~ListNode<T>();

	bool Insert(T _data);	 // 삽입
	bool Delete(T _data);	// 삭제 (노드만)
	bool Remove(T _data);	// 삭제 (데이터까지)

	// 파일 입출력에 혹여나 사용될까 싶어 만들어둔 메소드
	//void SaveList(FILE* fp, Node<T>* p);
	//Node<T>* LoadList(FILE* fp);

	// 읽기 접근자
	Node<T>* GetHead() { return head; }
	Node<T>* GetTail() { return Tail; }
};


// 초기화
template <typename T>
ListNode<T>::ListNode() {
	head = new Node<T>();	// 첫 노드 동적 할당
	Tail = head;			// 마지막 노드 위치 초기화
}

template <typename T>
ListNode<T>::~ListNode() {
	Node<T>* ptr = head->GetNext();	// 첫 노드의 다음 노드 위치를 저장
	delete head;	// 첫 노드 삭제

	while (ptr != nullptr) {	// 만약 노드가 두 개 이상이라면
		head = ptr;	// 헤드 노드에 현재 노드 포인터의 위치 저장
		ptr = ptr->GetNext(); // 노드 포인터는 다음 노드로
		delete head;	// 헤드 노드 위치의 노드 삭제
	} // 결국 포인터 노드가 nullptr 를 만날때까지(마지막 노드) 순회하면서 모든 노드를 삭제한다.
}

// 삽입
template <typename T>
bool ListNode<T>::Insert(T _data) {
	Node<T>* ptr = new Node<T>(_data); // 노드 객체 생성 및 매개 변수로 받은 데이터를 노드 데이터에 저장
	Tail->SetNext(ptr);	// 마지막 노드의 링크를 새로 생성된 노드로 연결
	Tail = ptr;	// 새로 생성된 노드와 마지막 노드를 연결
	return true;
}


// 삭제 (노드만)
template <typename T>
bool ListNode<T>::Delete(T _data) {
	Node<T>* pre = head; // 임시 노드에 첫 노드 저장
	Node<T>* ptr = pre->GetNext();	// 임시 노드2 는 첫 노드의 다음 노드로
	bool flug = false;

	while (ptr != nullptr) { // 임시 노드2 는 데이터를 찾지 못하면 마지막까지 순회함
		if (ptr->GetData() == _data) {	// 일치하는 데이터를 찾았다면
			flug = true;
			pre->SetNext(ptr->GetNext());	 // 임시 노드의 링크를 임시 노드2 의 다음 노드에 연결
			if (ptr->GetNext() == nullptr) {	 // 만약 임시 노드2 의 다음 노드가 마지막이라면
				Tail = pre;	// 마지막 노드에 임시 노드2를 저장
			}
			delete ptr;	// 임시 노드 2 위치의 노드 삭제
			break; // 순회 중단
		}
		pre = ptr;	// 임시 노드 한 칸 앞으로 이동
		ptr = ptr->GetNext();	// 임시 노드2 이동
	}

	if (flug) {	// 데이터를 삭제했다면
		return true;
	}
	return false;
}

// 삭제 (데이터까지)
template <typename T>
bool ListNode<T>::Remove(T _data) {
	Node<T>* pre = head;
	Node<T>* ptr = pre->GetNext();
	bool flug = false;

	while (ptr != nullptr) {
		if (ptr->GetData() == _data) {
			flug = true;
			pre->SetNext(ptr->GetNext());
			if (ptr->GetNext() == nullptr) {
				Tail = pre;
			}
			delete ptr->GetData();	// Delete 와 동일하지만 이 부분에 노드 내에 데이터까지 삭제한다는 차이점이 있다.
			delete ptr;
			break;
		}
		pre = ptr;
		ptr = ptr->GetNext();
	}

	if (flug) {
		return true;
	}
	return false;
}

// 아래는 파일 입출력 때 혹시나 쓸까 싶어 만든 메소드

//template <typename T>
//void ListNode<T>::SaveList(FILE* fp, Node<T>* p) {
//	while (p != nullptr) {
//		fwrite(p, sizeof(p), 1, fp);
//		p = p->GetNext();
//	}
//}
//
//template <typename T>
//Node<T>* ListNode<T>::LoadList(FILE* fp) {
//	Node<T>* p = nullptr;
//
//	while (1) {
//		Node<T>* ptr = new Node<T>*();
//		int isRead = fread(ptr, sizeof(ptr), 1, fp);
//
//		if (isRead) {
//			break;
//		}
//
//		if (head == nullptr) {
//			head = ptr;
//			p = ptr;
//		}
//		else {
//			p->GetNext() = ptr;
//			p = p->GetNext();
//		}
//	}
//
//	p->GetNext() = nullptr;
//	return head;
//}