#pragma once

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>

#include <linked_list.h>

typedef	char*	charptr;

DEFINE_LIST(charptr)

#define STRING_FORMAT(T) _Generic((T),	\
	charptr	: "%s\n",		\
	default	: "\n"			\
)

bool equal_charptr(charptr data1, charptr data2) {
	return strcmp(data1, data2) == 0;
}

void list_print_charptr(struct List_charptr* list) {
	for (struct Node_charptr* it = list->first; it != NULL; it = it->next) {
		printf(STRING_FORMAT(it->data), it->data);
	}
}

void test_create_charptr() {
	create(list, charptr);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);
	
	destroy(list);
}

void test_destroy_charptr() {
	create(list, charptr);

	push_back(list, "str");
	push_back(list, "test");

	destroy(list);
	
	CU_ASSERT_PTR_NULL(list);
}

void test_recreate_charptr() {
	create(list, charptr);

	push_back(list, "str");
	push_back(list, "test");

	recreate(list, charptr);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);

	destroy(list);
}

void test_push_back_charptr() {
	create(list, charptr);

	push_back(list, "chain");
	push_back(list, "sweep");
	push_back(list, "another");

	CU_ASSERT_EQUAL(list->first->data, "chain");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "sweep");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "another");
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_push_front_charptr() {
	create(list, charptr);

	push_front(list, "test1");
	push_front(list, "test2");
	push_back(list, "test3");

	CU_ASSERT_EQUAL(list->first->data, "test2");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "test1");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "test3");
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_pop_back_charptr() {
	create(list, charptr);

	push_front(list, "TV");
	push_back(list, "none");
	push_front(list, "Phone");
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data, "Phone");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "TV");
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_pop_front_charptr() {
	create(list, charptr);

	push_front(list, "grass");
	push_front(list, "nothing");
	push_back(list, "flower");
	pop_front(list);

	CU_ASSERT_EQUAL(list->first->data, "grass");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "flower");
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_insert_charptr() {
	create(list, charptr);

	push_back(list, "apple");
	push_back(list, "blueberry");
	insert(list, 1, "banana");
	insert(list, 17, "crown");
	insert(list, 0, "orange");
	insert(list, 3, "image");
	pop_back(list);
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data, "orange");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "apple");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "banana");
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_erase_charptr() {
	create(list, charptr);

	push_back(list, "home");
	push_back(list, "house");
	insert(list, 1, "chair");
	insert(list, 100, "table");
	insert(list, 0, "chess");
	insert(list, 3, "table");
	erase(list, 2);
	erase(list, 4);
	erase(list, 0);

	CU_ASSERT_EQUAL(list->first->data, "home");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "table");
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, "house");
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_size_charptr() {
	create(list, charptr);

	push_back(list, "first");
	push_back(list, "second");
	push_front(list, "third");
	push_front(list, "fourth");
	pop_front(list);
	pop_back(list);
	insert(list, 1, "fifth");
	insert(list, 100, "sixth");
	insert(list, 0, "seventh");
	erase(list, 2);
	erase(list, 1);
	
	uint32_t length = size(list);
	CU_ASSERT_EQUAL(length, 2);

	destroy(list);
}

void test_search_charptr() {
	create(list, charptr);

	push_back(list, "one");
	push_back(list, "two");
	push_front(list, "three");
	push_front(list, "four");
	insert(list, 1, "five");
	insert(list, 0, "six");

	int index = search(list, "six");
	CU_ASSERT_TRUE(index >= 0);
	index = search(list, "seven");
	CU_ASSERT_FALSE(index >= 0);

	destroy(list);
}

void* register_charptr() {
	CU_pSuite pSuite = NULL;

	pSuite = CU_add_suite("char*", NULL, NULL);
	if (NULL == pSuite) {
		return NULL;
	}

	if (NULL == CU_add_test(pSuite, "create", test_create_charptr)			||
	    NULL == CU_add_test(pSuite, "destroy", test_destroy_charptr)		||
	    NULL == CU_add_test(pSuite, "recreate", test_recreate_charptr)		||
	    NULL == CU_add_test(pSuite, "push_back", test_push_back_charptr)	||
	    NULL == CU_add_test(pSuite, "push_front", test_push_front_charptr)	||
	    NULL == CU_add_test(pSuite, "pop_back", test_pop_back_charptr)		||
	    NULL == CU_add_test(pSuite, "pop_front", test_pop_front_charptr)	||
	    NULL == CU_add_test(pSuite, "insert", test_insert_charptr)			||
	    NULL == CU_add_test(pSuite, "erase", test_erase_charptr)			||
	    NULL == CU_add_test(pSuite, "size", test_size_charptr)				||
	    NULL == CU_add_test(pSuite, "search", test_search_charptr))
	{
		return NULL;
	}
	
	return "SUCCESS";
}
