#pragma once

#ifdef LINECONTAINER_EXPORTS
#define LINE_API __declspec(dllexport)
#else
#define LINE_API __declspec(dllimport)
#endif

namespace lines
{
	struct LINE_API LINE
	{
		float x{};
		float y{};
		float ex{};
		float ey{};
	};
	struct LINE_API POINT
	{
		float x{};
		float y{};
	};

	class LINE_API LINECONTAINER
	{
		private:
			LINE* m_array_ptr{ nullptr };
			size_t max_size{};
			size_t end_position{};
			size_t array_current_pos{}; //for iteration
			size_t next_push_back_pos{};

		public:

			LINECONTAINER(size_t lenght);
			virtual ~LINECONTAINER();

			size_t size() const;
			size_t end_pos() const;

			bool empty_data() const;
			bool push_back(LINE element);
			void push_front(LINE element);
			bool delete_data(size_t index);
			void shrink();
			void distance_sort(POINT MyPoint);

			LINE& operator[] (size_t index) const;
			bool operator()(size_t index, LINE element); //insert element at position
	};

	typedef LINECONTAINER Container;

}
