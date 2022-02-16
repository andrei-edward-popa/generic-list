#pragma once

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>

#include <linked_list.h>

struct Pair {
	int32_t first;
	float second;
};

typedef	struct Pair	pair;

DEFINE_LIST(pair)

#define PAIR_FORMAT(T) _Generic((T),	\
	pair	: "%d %f\n",		\
	default	: "\n"			\
)

bool equal_pair(pair data1, pair data2) {
	return data1.first == data2.first && data1.second == data2.second;
}

void list_print_pair(struct List_pair* list) {
	for (struct Node_pair* it = list->first; it != NULL; it = it->next) {
		printf(PAIR_FORMAT(it->data), it->data.first, it->data.second);
	}
}

pair create_pair(int32_t val1, float val2) {
	pair data;
	data.first = val1;
	data.second = val2;
	return data;
}

void test_create_pair() {
	create(list, pair);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);
	
	destroy(list);
}

void test_destroy_pair() {
	create(list, pair);
	
	push_back(list, create_pair(-1, 4.2f));
	push_back(list, create_pair(4, -1.1f));

	destroy(list);
	
	CU_ASSERT_PTR_NULL(list);
}

void test_recreate_pair() {
	create(list, pair);

	push_back(list, create_pair(-1, 4.2f));
	push_back(list, create_pair(4, -1.1f));

	recreate(list, pair);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);

	destroy(list);
}

void test_push_back_pair() {
	create(list, pair);

	push_back(list, create_pair(3, 4.66f));
	push_back(list, create_pair(0, -3.3f));
	push_back(list, create_pair(9, 11.99f));

	CU_ASSERT_EQUAL(list->first->data.first, 3);
	CU_ASSERT_EQUAL(list->first->data.second, 4.66f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 0);
	CU_ASSERT_EQUAL(list->first->data.second, -3.3f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 9);
	CU_ASSERT_EQUAL(list->first->data.second, 11.99f);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_push_front_pair() {
	create(list, pair);

	push_front(list, create_pair(3, 4.66f));
	push_front(list, create_pair(0, -3.3f));
	push_back(list, create_pair(9, 11.99f));

	CU_ASSERT_EQUAL(list->first->data.first, 0);
	CU_ASSERT_EQUAL(list->first->data.second, -3.3f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 3);
	CU_ASSERT_EQUAL(list->first->data.second, 4.66f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 9);
	CU_ASSERT_EQUAL(list->first->data.second, 11.99f);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_pop_back_pair() {
	create(list, pair);

	push_front(list, create_pair(1, 1.1f));
	push_back(list, create_pair(2, 2.2f));
	push_front(list, create_pair(3, 3.3f));
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data.first, 3);
	CU_ASSERT_EQUAL(list->first->data.second, 3.3f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 1);
	CU_ASSERT_EQUAL(list->first->data.second, 1.1f);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_pop_front_pair() {
	create(list, pair);

	push_front(list, create_pair(1, 1.1f));
	push_front(list, create_pair(2, 2.2f));
	push_back(list, create_pair(3, 3.3f));
	pop_front(list);

	CU_ASSERT_EQUAL(list->first->data.first, 1);
	CU_ASSERT_EQUAL(list->first->data.second, 1.1f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 3);
	CU_ASSERT_EQUAL(list->first->data.second, 3.3f);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_insert_pair() {
	create(list, pair);

	push_back(list, create_pair(12, -4.67f));
	push_back(list, create_pair(17, -5.2234f));
	insert(list, 1, create_pair(0, 0.01f));
	insert(list, 100, create_pair(-44, -44444.4444f));
	insert(list, 0, create_pair(-99, -23.3f));
	insert(list, 3, create_pair(-999, 999.01f));
	pop_back(list);
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data.first, -99);
	CU_ASSERT_EQUAL(list->first->data.second, -23.3f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 12);
	CU_ASSERT_EQUAL(list->first->data.second, -4.67f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 0);
	CU_ASSERT_EQUAL(list->first->data.second, 0.01f);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_erase_pair() {
	create(list, pair);

	push_back(list, create_pair(3, 15.12f));
	push_back(list, create_pair(0, 999.0f));
	insert(list, 1, create_pair(4, -15.12f));
	insert(list, 100, create_pair(30, 125.1222f));
	insert(list, 0, create_pair(-333, -10.22f));
	insert(list, 3, create_pair(-6, 423.667f));
	erase(list, 2);
	erase(list, 4);
	erase(list, 100);
	erase(list, 0);

	CU_ASSERT_EQUAL(list->first->data.first, 3);
	CU_ASSERT_EQUAL(list->first->data.second, 15.12f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, -6);
	CU_ASSERT_EQUAL(list->first->data.second, 423.667f);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data.first, 0);
	CU_ASSERT_EQUAL(list->first->data.second, 999.0f);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_size_pair() {
	create(list, pair);

	push_back(list, create_pair(1, 1.0f));
	push_back(list, create_pair(2, 2.0f));
	push_front(list, create_pair(3, 3.0f));
	push_front(list, create_pair(4, 4.0f));
	pop_front(list);
	pop_back(list);
	insert(list, 1, create_pair(5, 5.0f));
	insert(list, 0, create_pair(6, 6.0f));
	erase(list, 2);
	
	uint32_t length = size(list);
	CU_ASSERT_EQUAL(length, 3);

	destroy(list);
}

void test_search_pair() {
	create(list, pair);

	push_back(list, create_pair(99, 32.44f));
	push_back(list, create_pair(-22, -232.11f));
	push_front(list, create_pair(8, 12.12f));
	push_front(list, create_pair(-4, -0.33f));
	insert(list, 1, create_pair(2, 17.44f));
	insert(list, 0, create_pair(99, 0.0001f));

	int index = search(list, create_pair(99, 32.44f));
	CU_ASSERT_TRUE(index >= 0);
	index = search(list, create_pair(99, 32.42f));
	CU_ASSERT_FALSE(index >= 0);

	destroy(list);
}

void* register_pair() {
	CU_pSuite pSuite = NULL;

	pSuite = CU_add_suite("struct pair", NULL, NULL);
	if (NULL == pSuite) {
		return NULL;
	}

	if (NULL == CU_add_test(pSuite, "create", test_create_pair)		||
	    NULL == CU_add_test(pSuite, "destroy", test_destroy_pair)		||
	    NULL == CU_add_test(pSuite, "recreate", test_recreate_pair)		||
	    NULL == CU_add_test(pSuite, "push_back", test_push_back_pair)	||
	    NULL == CU_add_test(pSuite, "push_front", test_push_front_pair)	||
	    NULL == CU_add_test(pSuite, "pop_back", test_pop_back_pair)		||
	    NULL == CU_add_test(pSuite, "pop_front", test_pop_front_pair)	||
	    NULL == CU_add_test(pSuite, "insert", test_insert_pair)		||
	    NULL == CU_add_test(pSuite, "erase", test_erase_pair)		||
	    NULL == CU_add_test(pSuite, "size", test_size_pair)			||
	    NULL == CU_add_test(pSuite, "search", test_search_pair))
	{
		return NULL;
	}
	
	return "SUCCESS";
}
