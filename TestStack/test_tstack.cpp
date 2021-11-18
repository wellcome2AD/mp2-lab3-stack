#include "../mp2-lab3-stack/TStack.h"

#include "gtest.h"
//cannot create stack with negative size
//stack after creating is empty
//can push element to empty stack
//can push element to nonfull stack
//cannot push element to full stack
//cannot pop element from epmty stack
//can push and pop

TEST(TStack, can_create_stack_with_positive_size)
{
  ASSERT_NO_THROW(TStack<double> st(5));
}

TEST(TStack, cannot_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(TStack<double> st(-5));
}

TEST(TStack, stack_after_creating_is_empty)
{
	TStack<double> st(5);
	ASSERT_EQ(st.IsEmpty(), true);
}

TEST(TStack, can_push_element_to_empty_stack)
{
	TStack<double> st(5);
	ASSERT_NO_THROW(st.Push(1));
}

TEST(TStack, can_push_element_to_nonfull_stack)
{
	TStack<double> st(2);
	st.Push(1);
	ASSERT_NO_THROW(st.Push(1));
}

TEST(TStack, cannot_push_element_to_full_stack)
{
	TStack<double> st(1);
	st.Push(1);
	ASSERT_ANY_THROW(st.Push(1));
}

TEST(TStack, cannot_pop_element_from_empty_stack)
{
	TStack<double> st(5);
	ASSERT_ANY_THROW(st.Pop());
}
TEST(TStack, can_push_and_pop)
{
	TStack<double> st(5);
	st.Push(5);
	ASSERT_EQ(st.Pop(), 5);
}