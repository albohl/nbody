#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "star.h"
#include <math.h>


#define prec float

void update_position(struct star* str, prec time_unit);
void addForce(struct star* star_A, struct star* star_B);

void testUPDATE_POSITION(){
  struct star test_star = makeStar();
  test_star.xpos = 350;
  test_star.ypos = 350;
  test_star.xspeed = -200;
  test_star.yspeed = 200;
  test_star.mass = 3;
  test_star.xforce = 10;
  test_star.yforce = 10;
  update_position(&test_star, 0.3);
  CU_ASSERT(readXPos(&test_star) < 291 && readXPos(&test_star) > 290 && readYPos(&test_star) < 411 && readYPos(&test_star) > 410);
}


void testADDFORCE(){
  struct star test_star1 = makeStar();
  struct star test_star2 = makeStar();
  test_star1.xpos = 350; test_star1.ypos = 350;
  test_star1.xspeed = -200; test_star1.yspeed = 200;
  test_star1.mass = 3;
  test_star1.xforce = 0; test_star1.yforce = 0;

  test_star2.xpos = 375; test_star2.ypos = 375;
  test_star2.xspeed = -200; test_star2.yspeed = 200;
  test_star2.mass = 3;
  test_star2.xforce = 0; test_star2.yforce = 0;

  addForce(&test_star1, &test_star2);
  printf("xf = %f, yf = %f\n", test_star1.xforce, test_star1.yforce);
  CU_ASSERT(fabs(test_star1.xforce - (-0.18) < 0.01) && fabs(test_star1.yforce - (-0.18)) < 0.01);
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int run_test()
{
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_1", NULL, NULL);
  if (NULL == pSuite){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "Test of update_position", testUPDATE_POSITION)) || (NULL == CU_add_test(pSuite, "Test of addForce", testADDFORCE))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

