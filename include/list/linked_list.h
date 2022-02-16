#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define PRINT_PRIM_FORMAT(T) _Generic((T),							\
	int8_t		: "%hhd\n",								\
	uint8_t		: "%hhu\n",								\
	int16_t		: "%hd\n",								\
	uint16_t	: "%hu\n",								\
	int32_t		: "%d\n",								\
	uint32_t	: "%u\n",								\
	int64_t		: "%ld\n",								\
	uint64_t	: "%lu\n",								\
	float		: "%f\n",								\
	double		: "%lf\n",								\
	long double	: "%Lf\n",								\
	char		: "%c\n",								\
	default		: "\n"									\
)

#define DEFINE_LIST(T)										\
	struct ListAPI_##T;									\
												\
	struct Node_##T {									\
		T data;										\
		struct Node_##T* next;								\
	};											\
												\
	struct List_##T {									\
		uint32_t size;									\
		struct Node_##T* first;								\
		struct ListAPI_##T* api;							\
	};											\
												\
	struct ListAPI_##T {									\
		void (*print)(struct List_##T*);						\
		uint32_t (*size)(struct List_##T*);						\
		void (*insert)(struct List_##T*, uint32_t, T);					\
		void (*erase)(struct List_##T*, uint32_t);					\
		void (*push_back)(struct List_##T*, T);						\
		void (*push_front)(struct List_##T*, T);					\
		void (*pop_back)(struct List_##T*);						\
		void (*pop_front)(struct List_##T*);						\
		int (*search)(struct List_##T*, T);						\
		void (*destroy)(struct List_##T**);						\
	};											\
												\
	struct Node_##T* create_node_##T(T data) {						\
		struct Node_##T* node = (struct Node_##T*)malloc(sizeof(struct Node_##T));	\
		node->next = NULL;								\
		node->data = data;								\
		return node;									\
	}											\
												\
	void list_print_##T(struct List_##T* list);						\
												\
	uint32_t list_size_##T(struct List_##T* list) {						\
		return list->size;								\
	}											\
												\
	void list_insert_##T(struct List_##T* list, uint32_t index, T data) {			\
		if (index >= list_size_##T(list)) {						\
			return;									\
		}										\
		struct Node_##T* new_node = create_node_##T(data);				\
		struct Node_##T* last = list->first;						\
		struct Node_##T* old;								\
		if (index == 0) {								\
			old = last;								\
			list->first = new_node;							\
			new_node->next = old;							\
		} else {									\
			while (--index){							\
				last = last->next;						\
			}									\
			old = last->next;							\
			last->next = new_node;							\
			new_node->next = old;							\
		}										\
		list->size += 1;								\
	}											\
												\
	void list_erase_##T(struct List_##T* list, uint32_t index) {				\
		uint32_t len = list_size_##T(list);						\
		if (index >= len) {								\
			return;									\
		}										\
		struct Node_##T* last = list->first;						\
		struct Node_##T* old;								\
		struct Node_##T* tmp;								\
		if (index == 0) {								\
			tmp = list->first;							\
			list->first = list->first->next;					\
			free(tmp);								\
		} else {									\
			while (--index) {							\
				last = last->next;						\
			}									\
			tmp = last->next;							\
			old = last->next->next;							\
			last->next = old;							\
			free(tmp);								\
		}										\
		list->size -= 1;								\
	}											\
												\
	void list_push_back_##T(struct List_##T* list, T data) {				\
		struct Node_##T* new_node = create_node_##T(data);				\
		struct Node_##T* last = list->first;						\
		if (list->first == NULL) {							\
		    list->first = new_node;							\
		    list->size += 1;								\
		    return;									\
		}										\
		while (last->next != NULL) {							\
		    last = last->next;								\
		}										\
		last->next = new_node;								\
		list->size += 1;								\
	}											\
												\
	void list_pop_back_##T(struct List_##T* list) {						\
		struct Node_##T* last = list->first;						\
		if (last == NULL) {								\
			return;									\
		}										\
		if (last->next == NULL) {							\
			free(list->first);							\
			list->first = NULL;							\
			list->size -= 1;							\
			return;									\
		}										\
		while (last->next->next != NULL) {						\
		    last = last->next;								\
		}										\
		free(last->next);								\
		last->next = NULL;								\
		list->size -= 1;								\
	}											\
												\
	void list_push_front_##T(struct List_##T* list, T data) {				\
		struct Node_##T* new_node = create_node_##T(data);				\
		struct Node_##T* old_head = list->first;					\
		list->first = new_node;								\
		new_node->next = old_head;							\
		list->size += 1;								\
	}											\
												\
	void list_pop_front_##T(struct List_##T* list) {					\
		struct Node_##T* tmp = list->first;						\
		struct Node_##T* new_head = list->first->next;					\
		list->first = new_head;								\
		list->size -= 1;								\
		free(tmp);									\
	}											\
												\
	bool equal_##T(T data1, T data2);							\
												\
	int list_search_##T(struct List_##T* list, T data) {					\
		int index = 0;									\
		for (struct Node_##T* it = list->first; it != NULL; it = it->next) {		\
			if (equal_##T(it->data, data)) {					\
				return index;							\
			}									\
			index++;								\
		}										\
		return -1;									\
	}											\
												\
	void list_destroy_##T(struct List_##T** list) {						\
		struct Node_##T* tmp;								\
		struct List_##T* list_tmp = *list;						\
		while (list_tmp->first != NULL) {						\
			tmp = list_tmp->first;							\
			list_tmp->first = list_tmp->first->next;				\
			free(tmp);								\
		}										\
		(*list)->first = NULL;								\
		free((*list)->api);								\
		(*list)->api = NULL;								\
		free(*list);									\
		*list = NULL;									\
	}											\
												\
	struct List_##T* list_create_##T() {							\
		struct List_##T* list = (struct List_##T*)malloc(sizeof(struct List_##T));	\
		list->api = (struct ListAPI_##T*)malloc(sizeof(struct ListAPI_##T));		\
		list->api->print = list_print_##T;						\
		list->api->size = list_size_##T;						\
		list->api->insert = list_insert_##T;						\
		list->api->erase = list_erase_##T;						\
		list->api->push_back = list_push_back_##T;					\
		list->api->push_front = list_push_front_##T;					\
		list->api->pop_back = list_pop_back_##T;					\
		list->api->pop_front = list_pop_front_##T;					\
		list->api->search = list_search_##T;						\
		list->api->destroy = list_destroy_##T;						\
		list->size = 0;									\
		list->first = NULL;								\
		return list;									\
	}

#define List(T)											\
	struct List_##T

#define create(list, T)										\
	List(T)* list = list_create_##T()

#define recreate(list, T)									\
	if (list != NULL && list->api != NULL) {						\
		destroy(list);									\
	}											\
	list = list_create_##T()

#define print(list)										\
	list->api->print(list)

#define size(list)										\
	list->api->size(list)

#define insert(list, index, value)								\
	list->api->insert(list, index, value)

#define erase(list, index)									\
	list->api->erase(list, index)

#define push_back(list, value)									\
	list->api->push_back(list, value)

#define push_front(list, value)									\
	list->api->push_front(list, value)

#define pop_back(list)										\
	list->api->pop_back(list)

#define pop_front(list)										\
	list->api->pop_front(list)

#define search(list, value)									\
	list->api->search(list, value)

#define destroy(list)										\
	list->api->destroy(&list)
	
#define DEFINE_EQUALITY(T)									\
	bool equal_##T(T data1, T data2) {							\
		return data1 == data2;								\
	}
	
#define DEFINE_PRINT(T)										\
	void list_print_##T(struct List_##T* list) {						\
		for (struct Node_##T* it = list->first; it != NULL; it = it->next) {		\
			printf(PRINT_PRIM_FORMAT(it->data), it->data);				\
		}										\
	}

#define DEFINE_PRIM_LIST(T)									\
	 DEFINE_LIST(T)										\
	 DEFINE_EQUALITY(T)									\
	 DEFINE_PRINT(T)
