#pragma once

namespace neu
{
	struct MemoryAllocation
	{
		void* address;
		size_t size;
		MemoryAllocation* next;
	};

	class MemoryTracker
	{
	public:
		void Add(void* address, size_t size);
		void Remove(void* address, size_t size);

		void displayInfo();

	private:
		size_t m_bytesAllocated = 0;
		size_t m_numAllocations = 0;

	};

	extern MemoryTracker g_MemoryTracker;
}