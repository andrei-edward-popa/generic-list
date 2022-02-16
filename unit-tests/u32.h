#pragma once

#include <errno.h>
#include <stdint.h>
#include <CUnit/CUnit.h>

#include <linked_list.h>

typedef	uint32_t	u32;

DEFINE_PRIM_LIST(u32)

void test_create_u32() {
	create(list, u32);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);
	
	destroy(list);
}

void test_destroy_u32() {
	create(list, u32);

	push_back(list, 8);
	push_back(list, 1);

	destroy(list);
	
	CU_ASSERT_PTR_NULL(list);
}

void test_recreate_u32() {
	create(list, u32);

	push_back(list, 8);
	push_back(list, 1);

	recreate(list, u32);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);

	destroy(list);
}

void test_push_back_u32() {
	create(list, u32);

	push_back(list, 8);
	push_back(list, 1);
	push_back(list, 2);

	CU_ASSERT_EQUAL(list->first->data, 8);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 1);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 2);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_push_front_u32() {
	create(list, u32);

	push_front(list, 8);
	push_front(list, 1);
	push_back(list, 2);

	CU_ASSERT_EQUAL(list->first->data, 1);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 8);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 2);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_pop_back_u32() {
	create(list, u32);

	push_front(list, 8);
	push_back(list, 1);
	push_front(list, 2);
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data, 2);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 8);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_pop_front_u32() {
	create(list, u32);

	push_front(list, 8);
	push_front(list, 2);
	push_back(list, 1);
	pop_front(list);

	CU_ASSERT_EQUAL(list->first->data, 8);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 1);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_insert_u32() {
	create(list, u32);

	push_back(list, 10);
	push_back(list, 11);
	insert(list, 1, 8);
	insert(list, 100, 2);
	insert(list, 0, 1);
	insert(list, 3, 6);
	pop_back(list);
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data, 1);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 10);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 8);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_erase_u32() {
	create(list, u32);

	push_back(list, 10);
	push_back(list, 11);
	insert(list, 1, 8);
	insert(list, 100, 2);
	insert(list, 0, 1);
	insert(list, 3, 6);
	erase(list, 2);
	erase(list, 4);
	erase(list, 100);
	erase(list, 0);

	CU_ASSERT_EQUAL(list->first->data, 10);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 6);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 11);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_size_u32() {
	create(list, u32);

	push_back(list, 10);
	push_back(list, 11);
	push_front(list, 100);
	push_front(list, 200);
	pop_front(list);
	pop_back(list);
	insert(list, 1, 8);
	insert(list, 100, 2);
	insert(list, 0, 1);
	erase(list, 2);
	erase(list, 100);
	
	uint32_t length = size(list);
	CU_ASSERT_EQUAL(length, 3);

	destroy(list);
}

void test_search_u32() {
	create(list, u32);

	push_back(list, 10);
	push_back(list, 11);
	push_front(list, 100);
	push_front(list, 200);
	insert(list, 1, 8);
	insert(list, 0, 1);

	int index = search(list, 200);
	CU_ASSERT_TRUE(index >= 0);
	index = search(list, 999);
	CU_ASSERT_FALSE(index >= 0);

	destroy(list);
}

void* register_u32() {
	CU_pSuite pSuite = NULL;

	pSuite = CU_add_suite("uint32_t", NULL, NULL);
	if (NULL == pSuite) {
		return NULL;
	}

	if (NULL == CU_add_test(pSuite, "create", test_create_u32)			||
	    NULL == CU_add_test(pSuite, "destroy", test_destroy_u32)		||
	    NULL == CU_add_test(pSuite, "recreate", test_recreate_u32)		||
	    NULL == CU_add_test(pSuite, "push_back", test_push_back_u32)	||
	    NULL == CU_add_test(pSuite, "push_front", test_push_front_u32)	||
	    NULL == CU_add_test(pSuite, "pop_back", test_pop_back_u32)		||
	    NULL == CU_add_test(pSuite, "pop_front", test_pop_front_u32)	||
	    NULL == CU_add_test(pSuite, "insert", test_insert_u32)			||
	    NULL == CU_add_test(pSuite, "erase", test_erase_u32)			||
	    NULL == CU_add_test(pSuite, "size", test_size_u32)				||
	    NULL == CU_add_test(pSuite, "search", test_search_u32))
	{
		return NULL;
	}
	
	return "SUCCESS";
}
