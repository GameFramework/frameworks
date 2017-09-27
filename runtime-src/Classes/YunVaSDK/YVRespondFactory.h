#ifndef YVRespondFactory_h__
#define YVRespondFactory_h__

#include <map>
namespace YVSDK
{
	struct YaYaRespondBase;
	typedef YaYaRespondBase* (*RespondCreator)();

#define AutoRegisterRespond(cmd, T)  \
	YaYaRespondBase* T##Creator(){ return new T(); } \
	struct T##_S  \
	{ \
	T##_S() \
	{ \
	YVRespondFactory::getSingletonPtr()->addCreator(cmd, T##Creator); \
	} \
	}; \
	T##_S T##r;

	class YVRespondFactory
	{
	public:
		~YVRespondFactory()
		{
			m_respondFactoryPtr = NULL;
			m_creatorList.clear();
		}

		static YVRespondFactory* getSingletonPtr()
		{
			if (m_respondFactoryPtr == NULL)
			{
				m_respondFactoryPtr = new YVRespondFactory();
			}
			return m_respondFactoryPtr;
		}

		void addCreator(unsigned int cmd, RespondCreator creator)
		{
			std::map<unsigned int, RespondCreator>::iterator it = m_creatorList.find(cmd);
			if (it == m_creatorList.end())
			{
				m_creatorList.insert(std::make_pair(cmd, creator));
			}
		}

		YaYaRespondBase* getRepsond(unsigned int cmd)
		{
			std::map<unsigned int, RespondCreator>::iterator it = m_creatorList.find(cmd);
			if (it == m_creatorList.end())
			{
				return NULL;
			}
			return (*(it->second))();
		}

	private:
		static YVRespondFactory* m_respondFactoryPtr;
		std::map<unsigned int, RespondCreator> m_creatorList;
	};
}
#endif // YVResponseFactory_h__

