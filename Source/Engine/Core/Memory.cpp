#include "Memory.h"
#include <iostream>

using namespace std;
neu::MemoryTracker neu::g_MemoryTracker;

void* operator new (size_t size)
{
	void* ptr = malloc(size);
	neu::g_MemoryTracker.Add(ptr, size);
	return ptr;
}

void operator delete (void* address, size_t size)
{
	neu::g_MemoryTracker.Remove(address, size);
	free(address);
}

namespace neu
{
	void MemoryTracker::Add(void* address, size_t size)
	{
		m_bytesAllocated += size;
		m_numAllocations++;
	}

	void MemoryTracker::Remove(void* address, size_t size)
	{
		m_bytesAllocated -= size;
		m_numAllocations--;
	}

	void MemoryTracker::displayInfo()
	{
		cout << "Currently Allocated Bytes: " << m_bytesAllocated << endl;
		cout << "Currently Number of Allocations: " << m_numAllocations << endl;
	}
}