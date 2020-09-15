#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../exercises/decorator.h"
#include "../exercises/adapter.h"
#include "../exercises/bridge.h"
#include "../exercises/composite.h"
#include "../exercises/flyweight.h"
#include "../exercises/proxy.h"
#include "../exercises/chain_of_responsability.h"
#include "../exercises/singleton.h"
#include "../exercises/prototype.h"
#include "../exercises/factories.h"
#include "../exercises/builder.h"
#include "builder_test_helper.h"

#define ASSERT_EQ(x,y) Assert::AreEqual(x,y)

namespace exercisestest
{
	TEST_CLASS(exercisestest)
	{
	public:
		
		TEST_METHOD(TestAdapter)
		{
			using namespace adapter;
			Square sq{ 11 };
			SquareToRectangleAdapter adapter{ sq };
			ASSERT_EQ(121, adapter.area());
		}

		TEST_METHOD(TestBridge)
		{
			using namespace bridge;
			ASSERT_EQ(0, Square{ VectorRenderer{} }.str().compare("Drawing Square as lines"));
		}

		TEST_METHOD(TestComposite)
		{
			using namespace composite;
			SingleValue single_value{ 11 };
			ManyValues other_values;
			other_values.add(22);
			other_values.add(33);
			ASSERT_EQ(66, sum({ &single_value, &other_values }));
		}

		TEST_METHOD(TestFlyweight)
		{
			using namespace flyweight;
			Sentence s{ "alpha beta gamma" };
			s[0].capitalize = s[2].capitalize = false;
			s[1].capitalize = true;
			ASSERT_EQ(0, s.str().compare("alpha BETA gamma"));
		}

		TEST_METHOD(TestProxy)
		{
			using namespace proxy;
			Person p{ 10 };
			ResponsiblePerson rp{ p };

			ASSERT_EQ(0, rp.drive().compare("too young"));
			ASSERT_EQ(0, rp.drink().compare("too young"));
			ASSERT_EQ(0, rp.drink_and_drive().compare("dead"));

			rp.set_age(20);

			ASSERT_EQ(0, rp.drive().compare("driving"));
			ASSERT_EQ(0, rp.drink().compare("drinking"));
			ASSERT_EQ(0, rp.drink_and_drive().compare("dead"));
		}

		TEST_METHOD(TestChainOfResponsability)
		{
			using namespace chain;
			Game game;
			Goblin goblin{ game };
			game.creatures.push_back(&goblin);

			cout << "Checking that a baseline goblin is a 1/1...\n";

			ASSERT_EQ(1, goblin.get_attack());
			ASSERT_EQ(1, goblin.get_defense());

			cout << "Adding a second goblin, now they should be 1/2...\n";
			Goblin goblin2{ game };
			game.creatures.push_back(&goblin2);

			ASSERT_EQ(1, goblin.get_attack());
			ASSERT_EQ(2, goblin.get_defense());

			cout << "Adding a goblin king, now a goblin should be 2/3...\n";
			GoblinKing goblin3{ game };
			game.creatures.push_back(&goblin3);

			ASSERT_EQ(2, goblin.get_attack());
			ASSERT_EQ(3, goblin.get_defense());
		}

		TEST_METHOD(TestDecorator)
		{
			using namespace decorator;
			Rose rose;
			BlueFlower blue_rose{ rose };
			RedFlower red_rose{ rose };
			BlueFlower b_r_rose{ red_rose };
			RedFlower r_b_r_rose{ b_r_rose };
			string tmp = r_b_r_rose.str();
			Assert::AreEqual(0/*==*/, tmp.compare("A rose that is red and blue"));
		}

		TEST_METHOD(TestSingleton)
		{
			using namespace singleton;
			SingletonTester tester;
			Assert::IsTrue(tester.is_singleton<SingletonTester>(
				[&]() -> SingletonTester* { return &tester; }));
			Assert::IsFalse(tester.is_singleton<SingletonTester>([]() { return new SingletonTester{}; }));
		}

		TEST_METHOD(TestPrototype)
		{
			using namespace prototype;
			Line line1{
				new Point{3,3},
				new Point{10,10}
			};

			Line line2 = line1.deep_copy();
			line1.start->x = line1.start->y =
				line1.end->y = line1.end->y = 0;

			ASSERT_EQ(3, line2.start->x);
			ASSERT_EQ(3, line2.start->y);
			ASSERT_EQ(10, line2.end->x);
			ASSERT_EQ(10, line2.end->y);
		}

		TEST_METHOD(TestFactories)
		{
			using namespace factories;
			PersonFactory pf;

			auto p1 = pf.create_person("Chris");
			ASSERT_EQ(0, p1.name.compare("Chris"));

			auto p2 = pf.create_person("Sarah");
			ASSERT_EQ(1, p2.id);
		}

		TEST_METHOD(TestBuilder)
		{
			using namespace builder;
			{
				CodeBuilder cb{ "Foo" };
				ostringstream oss;
				oss << cb;
				auto printed = oss.str();
				trim(printed);
				ASSERT_EQ(0, printed.compare("class Foo\n{\n};"));
			}
			{
				auto cb = CodeBuilder{ "Person" }
					.add_field("name", "string")
					.add_field("age", "int");
				ostringstream oss;
				oss << cb;
				auto printed = oss.str();
				trim(printed);
				ASSERT_EQ(0, printed.compare("class Person\n{\n  string name;\n  int age;\n};"));
			}
		}

	};
}
