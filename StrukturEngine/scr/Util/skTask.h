#pragma once
#include <future>
#include <thread>
#include <chrono>
#include <functional>

namespace Struktur
{
	namespace Util
	{
		using namespace std::chrono_literals;

		template <typename... Args>
		class skTask
		{
		public:
			skTask(std::function<void(Args...)> func)
				: m_task(std::packaged_task<void(Args...)>(func)), m_t(), m_completed(false)
			{
				m_future = m_task.get_future();
			}
			~skTask()
			{
				if (m_t.joinable())
				{
					m_t.join();
				}
			}

			void Join()
			{
				if (m_t.joinable())
				{
					m_t.join();
				}
			}

			void Launch(Args&&... args)
			{
				m_t = std::thread(std::move(m_task), std::forward<Args>(args)...);
			}

			bool complete() 
			{
				if (m_completed)
				{
					return true;
				}
				//m_future._Is_ready();
				std::future_status status = m_future.wait_for(0ms);
				if (status == std::future_status::ready)
				{
					m_t.join();
					m_completed = true;
					return true;
				}
				return false;
			}
		public:
			std::packaged_task<void(Args...)> m_task;
			std::future<void> m_future;
			std::thread m_t;
			bool m_completed;
		};
	};
};