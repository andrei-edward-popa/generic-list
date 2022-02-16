#pragma once

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>

#include <linked_list.h>

typedef	long double	f80;

DEFINE_PRIM_LIST(f80)

typedef	List(f80)*	list_f80;

DEFINE_LIST(list_f80)

bool equal_list_f80(list_f80 data1, list_f80 data2) {
	if (data1->size != data2->size) {
		return false;
	}
	struct Node_f80* tmp1 = data1->first;
	struct Node_f80* tmp2 = data2->first;
	while (tmp1 != NULL) {
		if (tmp1->data != tmp2->data) {
			return false;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return true;
}

void list_print_list_f80(struct List_list_f80* list) {
	for (struct Node_list_f80* it1 = list->first; it1 != NULL; it1 = it1->next) {
		list_f80 sublist = it1->data;
		for (struct Node_f80* it2 = sublist->first; it2 != NULL; it2 = it2->next) {
			printf("%.2Lf ", it2->data);
		}
		printf("\n");
	}
}

void test_create_list_f80() {
	create(list, list_f80);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);
	
	destroy(list);
}

void test_destroy_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	
	push_back(sublist1, 8.2L);
	push_back(sublist1, 11.3L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);
	
	push_back(list, sublist1);
	push_back(list, sublist2);

	destroy(sublist1);
	destroy(sublist2);
	destroy(list);
	
	CU_ASSERT_PTR_NULL(list);
}

void test_recreate_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	
	push_back(sublist1, 8.2L);
	push_back(sublist1, 11.3L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);
	
	push_back(list, sublist1);
	push_back(list, sublist2);

	recreate(list, list_f80);

	uint32_t length = size(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_EQUAL(length, 0);

	destroy(sublist1);
	destroy(sublist2);
	destroy(list);
}

void test_push_back_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	create(sublist3, f80);
	
	push_back(sublist1, 8.2L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);

	push_back(sublist3, -1.312L);
	push_back(sublist3, -2.11L);
	push_back(sublist3, 3.312L);
	
	push_back(list, sublist1);
	push_back(list, sublist2);
	push_back(list, sublist3);

	CU_ASSERT_EQUAL(list->first->data->first->data, 8.2L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -9.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -55.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -1.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -2.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, 3.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(sublist1);
	destroy(sublist2);
	destroy(sublist3);
	destroy(list);
}

void test_push_front_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	create(sublist3, f80);

	push_back(sublist1, 8.2L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);

	push_back(sublist3, -1.312L);
	push_back(sublist3, -2.11L);
	push_back(sublist3, 3.312L);
	
	push_front(list, sublist1);
	push_front(list, sublist2);
	push_back(list, sublist3);

	CU_ASSERT_EQUAL(list->first->data->first->data, -9.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -55.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, 8.2L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -1.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -2.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, 3.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(sublist1);
	destroy(sublist2);
	destroy(sublist3);
	destroy(list);
}

void test_pop_back_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	create(sublist3, f80);
	
	push_back(sublist1, 8.2L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);

	push_back(sublist3, -1.312L);
	push_back(sublist3, -2.11L);
	push_back(sublist3, 3.312L);

	push_front(list, sublist2);
	push_back(list, sublist3);
	push_front(list, sublist1);
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data->first->data, 8.2L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -9.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -55.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(sublist1);
	destroy(sublist2);
	destroy(sublist3);
	destroy(list);
}

void test_pop_front_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	create(sublist3, f80);

	push_back(sublist1, 8.2L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);

	push_back(sublist3, -1.312L);
	push_back(sublist3, -2.11L);
	push_back(sublist3, 3.312L);

	push_front(list, sublist1);
	push_front(list, sublist3);
	push_back(list, sublist2);
	pop_front(list);

	CU_ASSERT_EQUAL(list->first->data->first->data, 8.2L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -9.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -55.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(sublist1);
	destroy(sublist2);
	destroy(sublist3);
	destroy(list);
}

void test_insert_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	create(sublist3, f80);
	create(sublist4, f80);
	create(sublist5, f80);
	create(sublist6, f80);
	
	push_back(sublist1, 8.2L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);

	push_back(sublist3, -1.312L);
	push_back(sublist3, -2.11L);
	push_back(sublist3, 3.312L);

	push_back(list, sublist1);
	push_back(list, sublist4);
	insert(list, 1, sublist3);
	insert(list, 100, sublist5);
	insert(list, 0, sublist2);
	insert(list, 3, sublist6);
	pop_back(list);
	pop_back(list);

	CU_ASSERT_EQUAL(list->first->data->first->data, -9.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -55.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, 8.2L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -1.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -2.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, 3.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(sublist1);
	destroy(sublist2);
	destroy(sublist3);
	destroy(sublist4);
	destroy(sublist5);
	destroy(sublist6);
	destroy(list);
}

void test_erase_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	create(sublist3, f80);
	create(sublist4, f80);
	create(sublist5, f80);
	create(sublist6, f80);
	
	push_back(sublist1, 8.2L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);

	push_back(sublist3, -1.312L);
	push_back(sublist3, -2.11L);
	push_back(sublist3, 3.312L);

	push_back(list, sublist1);
	push_back(list, sublist3);
	insert(list, 1, sublist4);
	insert(list, 100, sublist5);
	insert(list, 0, sublist6);
	insert(list, 3, sublist2);
	erase(list, 2);
	erase(list, 4);
	erase(list, 100);
	erase(list, 0);

	CU_ASSERT_EQUAL(list->first->data->first->data, 8.2L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -9.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -55.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -1.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, -2.11L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_EQUAL(list->first->data->first->data, 3.312L);
	list->first->data->first = list->first->data->first->next;
	CU_ASSERT_PTR_NULL(list->first->data->first);

	list->first = list->first->next;
	CU_ASSERT_PTR_NULL(list->first);

	destroy(sublist1);
	destroy(sublist2);
	destroy(sublist3);
	destroy(sublist4);
	destroy(sublist5);
	destroy(sublist6);
	destroy(list);
}

void test_size_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	create(sublist3, f80);

	push_back(sublist1, 8.2L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);

	push_back(sublist3, -1.312L);
	push_back(sublist3, -2.11L);
	push_back(sublist3, 3.312L);

	push_back(list, sublist1);
	push_back(list, sublist2);
	push_front(list, sublist3);
	erase(list, 0);

	uint32_t length = size(list);
	CU_ASSERT_EQUAL(length, 2);

	erase(list, 0);
	pop_back(list);

	length = size(list);
	CU_ASSERT_EQUAL(length, 0);

	destroy(sublist1);
	destroy(sublist2);
	destroy(sublist3);
	destroy(list);
}

void test_search_list_f80() {
	create(list, list_f80);
	create(sublist1, f80);
	create(sublist2, f80);
	create(sublist3, f80);
	create(sublist4, f80);
	create(sublist5, f80);
	create(sublist6, f80);

	push_back(sublist1, 8.2L);
	push_back(sublist5, 8.2L);
	
	push_back(sublist2, -9.11L);
	push_back(sublist2, -55.312L);

	push_back(sublist3, -1.312L);
	push_back(sublist3, -2.11L);
	push_back(sublist3, 3.312L);

	push_back(sublist4, -551.312L);

	push_back(list, sublist1);
	push_front(list, sublist2);

	int index = search(list, sublist5);
	CU_ASSERT_TRUE(index >= 0);
	index = search(list, sublist4);
	CU_ASSERT_FALSE(index >= 0);
	index = search(list, sublist3);
	CU_ASSERT_FALSE(index >= 0);
	index = search(list, sublist6);
	CU_ASSERT_FALSE(index >= 0);

	destroy(sublist1);
	destroy(sublist2);
	destroy(sublist3);
	destroy(sublist4);
	destroy(sublist5);
	destroy(sublist6);
	destroy(list);
}

void* register_list_f80() {
	CU_pSuite pSuite = NULL;

	pSuite = CU_add_suite("list of long double", NULL, NULL);
	if (NULL == pSuite) {
		return NULL;
	}

	if (NULL == CU_add_test(pSuite, "create", test_create_list_f80)			||
	    NULL == CU_add_test(pSuite, "destroy", test_destroy_list_f80)		||
	    NULL == CU_add_test(pSuite, "recreate", test_recreate_list_f80)		||
	    NULL == CU_add_test(pSuite, "push_back", test_push_back_list_f80)	||
	    NULL == CU_add_test(pSuite, "push_front", test_push_front_list_f80)	||
	    NULL == CU_add_test(pSuite, "pop_back", test_pop_back_list_f80)		||
	    NULL == CU_add_test(pSuite, "pop_front", test_pop_front_list_f80)	||
	    NULL == CU_add_test(pSuite, "insert", test_insert_list_f80)			||
	    NULL == CU_add_test(pSuite, "erase", test_erase_list_f80)			||
	    NULL == CU_add_test(pSuite, "size", test_size_list_f80)				||
	    NULL == CU_add_test(pSuite, "search", test_search_list_f80))
	{
		return NULL;
	}
	
	return "SUCCESS";
}
