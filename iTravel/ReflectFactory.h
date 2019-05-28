#pragma once
#ifndef REFLECT_FACTORY
#define REFLECT_FACTORY
#include "pch.h"
/*											反射类
											(参考了第三方库Nebula反射的实现，这里做了一部分简化)
	---------------------------------------------------------------------------------------
	主要功能：模拟反射，通过字符串动态创建对应的类；注意，我们的反射不支持构造函数重载.

	使用方式：在命名空间Reflect中派生基类Reflect和DynamicCreator类来完成注册.
	---------------------------------------------------------------------------------------
	注：由于原生C++没有反射的功能，因此我们使用std::unordered_map来建立一个类名到类对象的一个映射.

	我们的反射依赖于C++11的std::unordered_map和RTTI(RunTime-Type-Identification)以及可变参数模板.
	另外，我们还使用了完美转发(Perfect Forwarding),它被用来解决在展开参数包时保留原参数的左/右值问题.

	使用时，需要先将被反射的类注册进unordered_map，考虑到如果让用户注册会导致更进一步的麻烦，我们使用了
	一些静态对象来完成运行期的自动注册.同时，为了避免不必要的实例化，我们为注册接口建立了工厂类.

	另一方面，静态对象DynamicCreator::Register的构造函数用于完成所有的注册工作.它首先获得当前注册类的类
	型名，这里通过RTTI实现.实际上，由于不同编译器对于RTTI的实现方式不同，因此返回的类型名称也不同.例如，
	gnu gcc的RTTI返回的名称是被修饰过的，因此使用时需要通过__cxa_demangle()来解析修饰的字符；而MSVC返回
	的名称直接就是demangled的，这里不需要太繁琐的处理.

	考虑到我们的项目并不需要跨平台支持，因此我们仅仅针对MSVC的情况进行了处理.
	
	另外，我们对DynamicCreator::Register添加了一个空的成员函数，用来避免它被编译器优化掉.
	---------------------------------------------------------------------------------------
	使用例：
	
	namespace Reflect{

	class TestClass :public ReflectBase, DynamicCreator<TestClass,long long> {
	public:
		//TestClass() {}
		TestClass(long long a){
			cout << a << endl;
		}
		virtual void Work(){
			::console << "反射测试" << endl;
		}
	};
	Reflect::Worker ReflectWorker;
	Reflect::ReflectBase *p = ReflectWorker.Create("Reflect::TestClass",static_cast<long long>(x));
	p->Work();
};

*/
namespace Reflect {
	//反射类的基类；所有的反射类需要从这个类派生
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
		//用于获得工厂的实例
		static ReflectFactory* Instance() {
			if (!pReflectFactory)
				pReflectFactory = new ReflectFactory();
			return pReflectFactory;
		}
		//将某个类对应的ReflectCreator注册到map中
		bool Regist(const std::string& strTypeName, std::function<ReflectBase*(Targs&&...args)>ReflectCreator) {
			if (!ReflectCreator)
				return false;
			std::string sTypename = strTypeName;
			return map_func.insert(std::make_pair(sTypename, ReflectCreator)).second;
		}
		//创建类的实例；同时调用这个类的构造函数
		ReflectBase* Create(const std::string& strTypeName, Targs&&...args) {
			auto
				iter = map_func.find(strTypeName);
			if (iter == map_func.end())
				return nullptr;
			return iter->second(std::forward<Targs>(args)...);
		}
	private:
		//只能通过Instance()来获得唯一的实例；这也就禁止了外部的实例化
		ReflectFactory(){}
		//工厂类的指针
		static ReflectFactory<Targs...>* pReflectFactory;
		//map
		std::unordered_map<std::string, std::function<ReflectBase*(Targs&&...)>>map_func;
	};

	template<typename... Targs>
	ReflectFactory<Targs...>* ReflectFactory<Targs...>::pReflectFactory=nullptr;

	template<typename T, typename...Args>
	class DynamicCreator {
	public:
		//返回创建的对象
		static T* CreateObject(Args&&...args) {
			return new T(std::forward<Args>(args)...);
		}
		//注册接口
		struct Register {
			Register() {
				const char* TypeName = typeid(T).name();
				std::string typeName = TypeName;
				//去掉"class "前缀，针对MSVC特殊优化
				typeName = typeName.substr(6);
				ReflectFactory<Args...>::Instance()->Regist(typeName, CreateObject);
			}
			void do_nothing(){}
		};
		DynamicCreator() {
			//防止注册函数被优化掉
			mRegister.do_nothing();
		}
		virtual ~DynamicCreator() { mRegister.do_nothing(); };
		//virtual ~DynamicCreator() {}
		static Register mRegister;
	};
	template<typename T, typename...Args>
	typename DynamicCreator<T,Args...>::Register 
		DynamicCreator<T, Args...>::mRegister;

	//Worker用于获得注册的对象，即外部使用这个反射的接口
	class Worker {
	public:
		template<typename...args>
		ReflectBase* Create(const std::string& Typename, args&&...arg) {
			return ReflectFactory<args...>::Instance()->Create(Typename, std::forward<args>(arg)...);
		}
	};

	
};
#endif