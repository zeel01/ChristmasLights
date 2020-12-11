#ifndef ANIM_LIST
#define ANIM_LIST

#include "Animate.hpp"

struct AniNode {
	Animation* animation;
	AniNode* next;
	AniNode(Animation* a, AniNode* n) : animation(a), next(n) { }
	~AniNode() {
		delete animation;
	}
};

struct AnimList {
	AniNode* first;
	int size;
	
	AnimList() : first(nullptr), size(0) { }
	
	AniNode* add(Animation* ani) {
		AniNode* newNode = new AniNode(ani, first);
		first = newNode;
		size++;
	}
	
	void runSequence() {
		AniNode* node = first;
		AniNode* prev = nullptr;
		while(node != nullptr) {
			if (!node->animation->next()) {
				if (prev != nullptr) prev->next = node->next;
				else first = node->next;
				delete node;
				node = prev;
				size--;
			}
			prev = node;
			node = node->next;
		}
	}
};

#endif