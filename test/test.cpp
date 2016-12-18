#include <gtest/gtest.h>
#include "PolishFromInfix.h"

TEST(ConvertMathEXpression, Example_0_to_can_convert_correct_exp_right)
{
  char d[] = "c+a-|5-t*2+p/3|";
  char resalt[] = "c a +5 t 2 *-p 3 /+|-";
  int i = 0;
  PolishFromInfix rt(d);
  char* res = rt.ConvertMathEXpression();

  while (res[i] != 0) {
    EXPECT_EQ(res[i], resalt[i]);
    i++;
  }

}

TEST(ConvertMathEXpression, Example_1_to_can_convert_correct_exp_right)
{
  char d[] = "-(5*(3-10)/5-18)";
  char resalt[] = "5 3 10 -*5 /18 -_";
  int i = 0;
  PolishFromInfix rt(d);
  char* res = rt.ConvertMathEXpression();

  while (res[i] != 0) {
    EXPECT_EQ(res[i], resalt[i]);
    i++;
  }

}

TEST(ConvertMathEXpression, Example_3_to_can_convert_correct_exp_right)
{
  char d[] = "(-7)*3-15/(1.5*2-(18/3*0))";
  char resalt[] = "7 _3 *15 1.5 2 *18 3 /0 *-/-";
  int i = 0;
  PolishFromInfix rt(d);
  char* res = rt.ConvertMathEXpression();

  while (res[i] != 0) {
    EXPECT_EQ(res[i], resalt[i]);
    i++;
  }

}

TEST(ConvertMathEXpression, Example_4_to_can_convert_correct_exp_right)
{
  char d[] = "21-20-44/(3*3+2)-2^2";
  char resalt[] = "21 20 -44 3 3 *2 +/-2 2 ^-";
  int i = 0;
  PolishFromInfix rt(d);
  char* res = rt.ConvertMathEXpression();

  while (res[i] != 0) {
    EXPECT_EQ(res[i], resalt[i]);
    i++;
  }

}


TEST(ConvertMathEXpression, Example_5_to_can_convert_correct_exp_right)
{
  char d[] = "(-(a+8))-b*3+8.3-c/(8-1)";
  char resalt[] = "a 8 +_b 3 *-8.3 +c 8 1 -/-";
  int i = 0;
  PolishFromInfix rt(d);
  char* res = rt.ConvertMathEXpression();

  while (res[i] != 0) {
    EXPECT_EQ(res[i], resalt[i]);
    i++;
  }

}
TEST(ConvertMathEXpression, Exemple_6_to_can_convert_correct_exp_right)
{
  char d[] = "|-3|^3";
  char resalt[] = "3 _|3 ^";
  int i = 0;
  PolishFromInfix rt(d);
  char* res = rt.ConvertMathEXpression();

  while (res[i] != 0) {
    EXPECT_EQ(res[i], resalt[i]);
    i++;
  }

}


TEST(ValueExpression, can_right_calculate_value_of_exp_0)
{
  char d[] = "|-3|-3";
  double resalt = 0;
  PolishFromInfix rt(d);
  rt.ConvertMathEXpression();
  Variable* a = NULL;
  rt.ValueExpression(a);

  EXPECT_EQ(resalt, rt.GetValue());

}

TEST(ValueExpression, can_right_calculate_value_of_exp_1)
{
  char d[] = "|x-10*3/5|-a*(2-3)";

  double resalt = 18;

  PolishFromInfix rt(d);
  rt.ConvertMathEXpression();

  Variable* a = NULL;
  a = ListOfValues(a, 'a', 15);
  a = ListOfValues(a, 'x', 3);
  rt.ValueExpression(a);

  EXPECT_EQ(resalt, rt.GetValue());

}

TEST(ValueExpression, can_right_calculate_value_of_exp_2)
{
  char d[] = "|s-c+(e/5)*|f-g^3||";

  double resalt = 5;

  PolishFromInfix rt(d);
  rt.ConvertMathEXpression();

  Variable* a = NULL;
  a = ListOfValues(a, 's', 15);
  a = ListOfValues(a, 'c', 20);
  a = ListOfValues(a, 'e', 25.5);
  a = ListOfValues(a, 'f', 8);
  a = ListOfValues(a, 'g', 2);
  rt.ValueExpression(a);

  EXPECT_EQ(resalt, rt.GetValue());

}

TEST(ValueExpression, can_right_calculate_value_of_exp_3)
{
  char d[] = "|-(a^3-(4.125+1.875)/1.2)|^|-2|";

  double resalt = 9;

  PolishFromInfix rt(d);
  rt.ConvertMathEXpression();

  Variable* a = NULL;
  a = ListOfValues(a, 'a', 2);

  rt.ValueExpression(a);

  EXPECT_EQ(resalt, rt.GetValue());

}
TEST(ValueExpression, can_right_calculate_value_of_exp_4)
{
  char d[] = "|a+1|-3^(4/2)";

  double resalt = -6;

  PolishFromInfix rt(d);
  rt.ConvertMathEXpression();

  Variable* a = NULL;
  a = ListOfValues(a, 'a', 2);

  rt.ValueExpression(a);

  EXPECT_EQ(resalt, rt.GetValue());

}
TEST(ValueExpression, can_right_calculate_value_of_exp_5)
{
  char d[] = "a^(-|14-81/3^2-14|/9)";

  double resalt = 0.5;

  PolishFromInfix rt(d);
  rt.ConvertMathEXpression();

  Variable* a = NULL;
  a = ListOfValues(a, 'a', 2);

  rt.ValueExpression(a);

  EXPECT_EQ(resalt, rt.GetValue());

}
TEST(ValueExpression, can_right_calculate_value_of_exp_6)
{
  char d[] = "-(|s^(-c)-e*(0.2)|^2)";

  double resalt = -0.25;

  PolishFromInfix rt(d);
  rt.ConvertMathEXpression();

  Variable* a = NULL;
  a = ListOfValues(a, 's', 4);
  a = ListOfValues(a, 'c', 0.5);
  a = ListOfValues(a, 'e', 5);
  rt.ValueExpression(a);

  EXPECT_EQ(resalt, rt.GetValue());

}

TEST(CheckOnCorrect, throw_when_expression_is_not_correct0)
{
  char d[] = "(|2+3)|";
  PolishFromInfix s(d);

  ASSERT_ANY_THROW(s.ConvertMathEXpression());


}
TEST(CheckOnCorrect, throw_when_expression_is_not_correct1)
{
  char d[] = "|2-6+4+*35|";
  PolishFromInfix s(d);

  ASSERT_ANY_THROW(s.ConvertMathEXpression());


}
TEST(CheckOnCorrect, throw_when_expression_is_not_correct2)
{
  char d[] = "(45-1(((-(56/3)-12^23)*|43*(-3)";
  PolishFromInfix s(d);

  ASSERT_ANY_THROW(s.ConvertMathEXpression());


}
TEST(CheckOnCorrect, throw_when_expression_is_not_correct3)
{
  char d[] = "c+a-|5-t*2+p/3|*%";
  PolishFromInfix s(d);

  ASSERT_ANY_THROW(s.ConvertMathEXpression());


}


int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}