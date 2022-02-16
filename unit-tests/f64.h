#pragma once

#include <errno.h>
#include <stdint.h>
#include <CUnit/CUnit.h>

#include <linked_list.h>

typedef	double	f64;

DEFINE_PRIM_LIST(f64)

void test_create_f64() {
	create(list, f64);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);
	
	destroy(list);
}

void test_destroy_f64() {
	create(list, f64);

	push_back(list, 34.55);
	push_back(list, 99.3);

	destroy(list);
	
	CU_ASSERT_PTR_NULL(list);
}

void test_recreate_f64() {
	create(list, f64);

	push_back(list, 11.2);
	push_back(list, -10.5);

	recreate(list, f64);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);

	destroy(list);
}

void test_push_back_f64() {
	create(list, f64);

	push_back(list, -88.11);
	push_back(list, 100.3);
	push_back(list, 299.333);

	CU_ASSERT_EQUAL(list->first->data, -88.11);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 100.3);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 299.333);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_push_front_f64() {
	create(list, f64);

	push_front(list, 8.11);
	push_front(list, 1.66);
	push_back(list, 2.3456);

	CU_ASSERT_EQUAL(list->first->data, 1.66);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 8.11);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 2.3456);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_pop_back_f64() {
	create(list, f64);

	push_front(list, 0.56);
	push_back(list, -561.01);
	push_front(list, -112.666);
	push_front(list, -22.3);
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data, -22.3);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, -112.666);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 0.56);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_pop_front_f64() {
	create(list, f64);

	push_front(list, 0.1);
	push_back(list, 0.22);
	push_front(list, 0.333);
	push_back(list, 0.4444);
	pop_front(list);

	CU_ASSERT_EQUAL(list->first->data, 0.1);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 0.22);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 0.4444);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_insert_f64() {
	create(list, f64);

	push_back(list, -11.11);
	push_back(list, 22.22);
	insert(list, 1, -33.33);
	insert(list, 2, 44.44);
	pop_back(list);
	pop_front(list);

	CU_ASSERT_EQUAL(list->first->data, -33.33);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 44.44);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_erase_f64() {
	create(list, f64);

	push_back(list, 74893422.432432);
	push_back(list, 42432.4643);
	insert(list, 1, 0.7643545);
	insert(list, 100, 2.2);
	insert(list, 0, 84329480932.43232);
	insert(list, 3, 887545455.32432);
	erase(list, 2);
	erase(list, 4);
	erase(list, 100);
	erase(list, 0);

	CU_ASSERT_EQUAL(list->first->data, 74893422.432432);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 887545455.32432);
	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data, 42432.4643);
	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(list);
}

void test_size_f64() {
	create(list, f64);

	push_back(list, 0.432432);
	push_back(list, 1.4326753);
	push_front(list, 2.589876);
	push_front(list, 3.0);
	pop_front(list);
	pop_back(list);
	insert(list, 1, 4.567543);
	insert(list, 100, 5.3247645645543);
	insert(list, 0, 6.432432);
	erase(list, 2);
	
	uint32_t length = size(list);
	CU_ASSERT_EQUAL(length, 3);

	destroy(list);
}

void test_search_f64() {
	create(list, f64);

	push_back(list, -0.1);
	push_back(list, 234.22);
	push_front(list, -1011.222);
	push_front(list, 92.33);
	insert(list, 1, 100.100);
	insert(list, 0, 1000.1000);

	int index = search(list, 92.33);
	CU_ASSERT_TRUE(index >= 0);
	index = search(list, 1.1);
	CU_ASSERT_FALSE(index >= 0);

	destroy(list);
}

void* register_f64() {
	CU_pSuite pSuite = NULL;

	pSuite = CU_add_suite("double", NULL, NULL);
	if (NULL == pSuite) {
		return NULL;
	}

	if (NULL == CU_add_test(pSuite, "create", test_create_f64)			||
	    NULL == CU_add_test(pSuite, "destroy", test_destroy_f64)		||
	    NULL == CU_add_test(pSuite, "recreate", test_recreate_f64)		||
	    NULL == CU_add_test(pSuite, "push_back", test_push_back_f64)	||
	    NULL == CU_add_test(pSuite, "push_front", test_push_front_f64)	||
	    NULL == CU_add_test(pSuite, "pop_back", test_pop_back_f64)		||
	    NULL == CU_add_test(pSuite, "pop_front", test_pop_front_f64)	||
	    NULL == CU_add_test(pSuite, "insert", test_insert_f64)			||
	    NULL == CU_add_test(pSuite, "erase", test_erase_f64)			||
	    NULL == CU_add_test(pSuite, "size", test_size_f64)				||
	    NULL == CU_add_test(pSuite, "search", test_search_f64))
	{
		return NULL;
	}
	
	return "SUCCESS";
}
