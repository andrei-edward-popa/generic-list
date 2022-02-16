#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include <u32.h>
#include <f64.h>
#include <charptr.h>
#include <list_f80.h>
#include <struct_pair.h>

int main() {

	if (CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	if (NULL == register_u32()		||
	    NULL == register_f64()		||
	    NULL == register_charptr()	||
	    NULL == register_pair()		||
	    NULL == register_list_f80())
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	printf("\n");
	CU_basic_show_failures(CU_get_failure_list());

	return 0;
}
