#include "pch.h"
#include "LineContainer.h"

lines::LINECONTAINER::LINECONTAINER(size_t lenght) :max_size{ lenght }, m_array_ptr{ new LINE[lenght]{} }
{
	end_position = max_size - 1;
}
lines::LINECONTAINER::~LINECONTAINER()
{
	if (m_array_ptr)delete[]m_array_ptr;
}

size_t lines::LINECONTAINER::size()const
{
	return max_size;
}
size_t lines::LINECONTAINER::end_pos()const
{
	return end_position;
}

bool lines::LINECONTAINER::empty_data() const
{
	bool filled = false;
	for (int i = 0; i < max_size; i++)
	{
		LINE Line_to_check{ *(m_array_ptr + i) };
		
		if (!(Line_to_check.x == 0 && Line_to_check.y == 0 && Line_to_check.ex == 0 && Line_to_check.ey == 0))
		{
			filled = true;
			break;
		}
	}
	return filled;
}
bool lines::LINECONTAINER::push_back(LINE element)
{
	array_current_pos = next_push_back_pos;
	if (array_current_pos + 1 > end_position)return false;
	*(m_array_ptr + array_current_pos) = element;
	++next_push_back_pos;
	array_current_pos = 0;
	return true;
}
void lines::LINECONTAINER::push_front(LINE element)
{
	*m_array_ptr = element;
}
lines::LINE& lines::LINECONTAINER::operator[](size_t index) const
{
	if (index > end_position)return *(m_array_ptr + end_position);
	return *(m_array_ptr + index);
}
bool lines::LINECONTAINER::operator()(size_t index, LINE element)
{
	if (index > end_position || index < 0)return false;

	*(m_array_ptr + index) = element;
	return true;
}

bool lines::LINECONTAINER::delete_data(size_t index)
{
	if (index<0 || index > end_position)return false;
	*(m_array_ptr + index) = { 0, 0, 0, 0 };
	return true;
}
void lines::LINECONTAINER::shrink()
{
	int index = -1;
	for (int i = 0; i <= end_position; i++)
	{
		LINE current(*(m_array_ptr + i));
		if (current.x == 0 && current.y == 0 && current.ex == 0 && current.ey == 0)
		{
			index = i;
			break;
		}
	}
	
	if (index < 0 || index == end_position)return;
	
	for (int i = index; i < end_position; i++)
	{
		bool not_finished = true;

		while (not_finished)
		{
			LINE current(*(m_array_ptr + i));
			LINE next(*(m_array_ptr + i + 1));
			not_finished = false;

			if ((current.x == 0 && current.y == 0 && current.ex == 0 && current.ey == 0)
				&& (next.x != 0 || next.y != 0 || next.ex != 0 || next.ey != 0))
			{
				current = next;
				next.x = 0;
				next.y = 0;
				next.ex = 0;
				next.ey = 0;

				next_push_back_pos = index + i;
				
				not_finished = true;
			}
		}
	}
}
