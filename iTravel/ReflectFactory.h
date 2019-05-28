#pragma once
#ifndef REFLECT_FACTORY
#define REFLECT_FACTORY
#include "pch.h"
/*											������
											(�ο��˵�������Nebula�����ʵ�֣���������һ���ּ�)
	---------------------------------------------------------------------------------------
	��Ҫ���ܣ�ģ�ⷴ�䣬ͨ���ַ�����̬������Ӧ���ࣻע�⣬���ǵķ��䲻֧�ֹ��캯������.

	ʹ�÷�ʽ���������ռ�Reflect����������Reflect��DynamicCreator�������ע��.
	---------------------------------------------------------------------------------------
	ע������ԭ��C++û�з���Ĺ��ܣ��������ʹ��std::unordered_map������һ��������������һ��ӳ��.

	���ǵķ���������C++11��std::unordered_map��RTTI(RunTime-Type-Identification)�Լ��ɱ����ģ��.
	���⣬���ǻ�ʹ��������ת��(Perfect Forwarding),�������������չ��������ʱ����ԭ��������/��ֵ����.

	ʹ��ʱ����Ҫ�Ƚ����������ע���unordered_map�����ǵ�������û�ע��ᵼ�¸���һ�����鷳������ʹ����
	һЩ��̬��������������ڵ��Զ�ע��.ͬʱ��Ϊ�˱��ⲻ��Ҫ��ʵ����������Ϊע��ӿڽ����˹�����.

	��һ���棬��̬����DynamicCreator::Register�Ĺ��캯������������е�ע�Ṥ��.�����Ȼ�õ�ǰע�������
	����������ͨ��RTTIʵ��.ʵ���ϣ����ڲ�ͬ����������RTTI��ʵ�ַ�ʽ��ͬ����˷��ص���������Ҳ��ͬ.���磬
	gnu gcc��RTTI���ص������Ǳ����ι��ģ����ʹ��ʱ��Ҫͨ��__cxa_demangle()���������ε��ַ�����MSVC����
	������ֱ�Ӿ���demangled�ģ����ﲻ��Ҫ̫�����Ĵ���.

	���ǵ����ǵ���Ŀ������Ҫ��ƽ̨֧�֣�������ǽ������MSVC����������˴���.
	
	���⣬���Ƕ�DynamicCreator::Register�����һ���յĳ�Ա�������������������������Ż���.
	---------------------------------------------------------------------------------------
	ʹ������
	
	namespace Reflect{

	class TestClass :public ReflectBase, DynamicCreator<TestClass,long long> {
	public:
		//TestClass() {}
		TestClass(long long a){
			cout << a << endl;
		}
		virtual void Work(){
			::console << "�������" << endl;
		}
	};
	Reflect::Worker ReflectWorker;
	Reflect::ReflectBase *p = ReflectWorker.Create("Reflect::TestClass",static_cast<long long>(x));
	p->Work();
};

*/
namespace Reflect {
	//������Ļ��ࣻ���еķ�������Ҫ�����������
	class ReflectBase {
	public:
		ReflectBase() {}
		virtual ~ReflectBase() {}
		virtual void Test(){}
		virtual void Work(){}
	};
	template<typename... Targs>
	class ReflectFactory {
	public:
		//���ڻ�ù�����ʵ��
		static ReflectFactory* Instance() {
			if (!pReflectFactory)
				pReflectFactory = new ReflectFactory();
			return pReflectFactory;
		}
		//��ĳ�����Ӧ��ReflectCreatorע�ᵽmap��
		bool Regist(const std::string& strTypeName, std::function<ReflectBase*(Targs&&...args)>ReflectCreator) {
			if (!ReflectCreator)
				return false;
			std::string sTypename = strTypeName;
			return map_func.insert(std::make_pair(sTypename, ReflectCreator)).second;
		}
		//�������ʵ����ͬʱ���������Ĺ��캯��
		ReflectBase* Create(const std::string& strTypeName, Targs&&...args) {
			auto
				iter = map_func.find(strTypeName);
			if (iter == map_func.end())
				return nullptr;
			return iter->second(std::forward<Targs>(args)...);
		}
	private:
		//ֻ��ͨ��Instance()�����Ψһ��ʵ������Ҳ�ͽ�ֹ���ⲿ��ʵ����
		ReflectFactory(){}
		//�������ָ��
		static ReflectFactory<Targs...>* pReflectFactory;
		//map
		std::unordered_map<std::string, std::function<ReflectBase*(Targs&&...)>>map_func;
	};

	template<typename... Targs>
	ReflectFactory<Targs...>* ReflectFactory<Targs...>::pReflectFactory=nullptr;

	template<typename T, typename...Args>
	class DynamicCreator {
	public:
		//���ش����Ķ���
		static T* CreateObject(Args&&...args) {
			return new T(std::forward<Args>(args)...);
		}
		//ע��ӿ�
		struct Register {
			Register() {
				const char* TypeName = typeid(T).name();
				std::string typeName = TypeName;
				//ȥ��"class "ǰ׺�����MSVC�����Ż�
				typeName = typeName.substr(6);
				ReflectFactory<Args...>::Instance()->Regist(typeName, CreateObject);
			}
			void do_nothing(){}
		};
		DynamicCreator() {
			//��ֹע�ắ�����Ż���
			mRegister.do_nothing();
		}
		virtual ~DynamicCreator() { mRegister.do_nothing(); };
		//virtual ~DynamicCreator() {}
		static Register mRegister;
	};
	template<typename T, typename...Args>
	typename DynamicCreator<T,Args...>::Register 
		DynamicCreator<T, Args...>::mRegister;

	//Worker���ڻ��ע��Ķ��󣬼��ⲿʹ���������Ľӿ�
	class Worker {
	public:
		template<typename...args>
		ReflectBase* Create(const std::string& Typename, args&&...arg) {
			return ReflectFactory<args...>::Instance()->Create(Typename, std::forward<args>(arg)...);
		}
	};

	
};
#endif