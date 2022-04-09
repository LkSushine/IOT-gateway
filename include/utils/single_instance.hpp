#pragma once
#include <string>

#if defined(__linux__)
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdexcept>
#include <unistd.h>
#elif defined(_WIN32)
#include <Windows.h>

#endif

namespace gateway
{
	namespace utils
	{
		class SigleInstance
		{
		public:
			SigleInstance() :
				wasCreated_(false)
			{
			}
#if defined(__linux__)
		public:
			bool Init(const std::string &instanceName)
			{
				instanceName_ = instanceName;
				shmFd_ = shm_open(instanceName_.c_str(), O_RDWR, 0660);
				if (shmFd_ < 0)
				{
					if (errno == ENOENT)
					{
						wasCreated_ = true;
						shmFd_ = shm_open(instanceName_.c_str(), O_RDWR | O_CREAT, 0660);
					}
				}

				if (shmFd_ < 0)
				{
					return false;
				}

				if (ftruncate(shmFd_, sizeof(pthread_mutex_t)) != 0)
				{
					return false;
				}

				auto *mappedMutex = mmap(nullptr, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd_, 0);
				if (mappedMutex == reinterpret_cast<void *>(-1) /*MAP_FAILED*/)
				{
					return false;
				}

				mutex_ = reinterpret_cast<pthread_mutex_t *>(mappedMutex);

				if (wasCreated_)
				{
					pthread_mutexattr_t attr;
					if (pthread_mutexattr_init(&attr) != 0)
					{
						return false;
					}
					if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) != 0)
					{
						return false;
					}
					if (pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST) != 0)
					{
						return false;
					}
					if (pthread_mutex_init(mutex_, &attr))
					{
						return false;
					}
				}
			}

			void Reset()
			{
				wasCreated_ = true;
			}

			bool IsAnotherRunning()
			{
				auto lockResult = pthread_mutex_trylock(mutex_);

				if (lockResult == EOWNERDEAD)
				{
					lockResult = pthread_mutex_consistent(mutex_);
					if (lockResult != 0)
					{
						wasCreated_ = true;
						return true;
					}
				}
				else if (lockResult != 0)
				{
					return true;
				}

				return false;
			}

			void Clear()
			{
				if (wasCreated_)
				{
					pthread_mutex_destroy(mutex_);
					munmap(reinterpret_cast<void *>(mutex_), sizeof(pthread_mutex_t));

					close(shmFd_);
					shm_unlink(instanceName_.c_str());
				}
				else
				{
					munmap(reinterpret_cast<void *>(mutex_), sizeof(pthread_mutex_t));
					close(shmFd_);
				}
			}
		private:
			std::int32_t shmFd_;
			pthread_mutex_t *mutex_;
			std::string instanceName_;
			bool wasCreated_;
#elif defined(_WIN32)
		public:
			bool Init(const std::string &instanceName)
			{
				instanceName_ = instanceName;
				mutexHandle_ = CreateMutex(nullptr, false, instanceName_.c_str());
				if (!mutexHandle_)
				{
					return false;
				}

				if (GetLastError() != ERROR_ALREADY_EXISTS)
				{
					wasCreated_ = true;
				}
				return true;
			}
			
			void Reset()
			{
				wasCreated_ = true;
			}
			
			bool IsAnotherRunning()
			{
				auto status = WaitForSingleObject(mutexHandle_, 0);

				if (status == WAIT_ABANDONED)
				{
					wasCreated_ = true;
					return false;
				}

				return status != WAIT_OBJECT_0;
			}

			void Clear()
			{
				ReleaseMutex(mutexHandle_);

				if (wasCreated_)
				{
					CloseHandle(mutexHandle_);
				}
			}
		private:
			std::string instanceName_;
			HANDLE mutexHandle_;
			bool wasCreated_;
#endif
		};
		
	}//utils
	
}//gateway



