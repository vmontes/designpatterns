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
#include "../exercises/command.h"
#include "../exercises/interpreter.h"
#include "../exercises/iterator.h"
#include "../exercises/mediator.h"
#include "../exercises/memento.h"
#include "../exercises/observer.h"
#include "../exercises/state.h"
#include "../exercises/strategy.h"
#include "../exercises/template_method.h"

#include "builder_test_helper.h"

#define ASSERT_EQ(x,y) Assert::AreEqual(x,y)
#define ASSERT_TRUE(x) Assert::IsTrue(x)
#define ASSERT_FALSE(x) Assert::IsFalse(x)

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

		TEST_METHOD(TestCommand)
		{
			using namespace command;
			{
				Account ac;
				Command dep;
				dep.action = Command::deposit;
				dep.amount = 100;
				Command wit;
				wit.action = Command::withdraw;
				wit.amount = 60;

				ac.process(dep);
				ac.process(wit);
				ASSERT_EQ(40, ac.balance);
			}
			{
				Account a;
				Command command{ Command::deposit, 100 };
				a.process(command);

				ASSERT_EQ(100, a.balance);
				ASSERT_TRUE(command.success);

				command = Command{ Command::withdraw, 50 };
				a.process(command);

				ASSERT_EQ(50, a.balance);
				ASSERT_TRUE(command.success);

				command = Command{ Command::withdraw, 150 };
				a.process(command);

				ASSERT_EQ(50, a.balance);
				ASSERT_FALSE(command.success);
			}
		}

		TEST_METHOD(TestInterpreter)
		{
			using namespace interpreter;
			{
				ExpressionProcessor ep;
				int value = ep.calculate("1+2+3");
				ASSERT_EQ(6, value);
				ep.variables['x'] = 10;
				ASSERT_EQ(14, ep.calculate("1+x+3"));
			}
			{
				ExpressionProcessor ep;
				ep.variables['x'] = 5;
				ASSERT_EQ(1, ep.calculate("1"));
				ASSERT_EQ(3, ep.calculate("1+2"));
				ASSERT_EQ(6, ep.calculate("1+x"));
				ASSERT_EQ(0, ep.calculate("1+xy"));
			}
		}

		TEST_METHOD(TestIterator)
		{
			using namespace iterator;
			Node<char> c{ 'c' };
			Node<char> d{ 'd' };
			Node<char> e{ 'e' };
			Node<char> b{ 'b', &c, &d };
			Node<char> a{ 'a', &b, &e };

			vector<Node<char>*> result;
			a.preorder_traversal(result);

			ostringstream oss;
			for (auto n : result)
				oss << n->value;
			ASSERT_EQ(0, oss.str().compare("abcde"));
		}

		TEST_METHOD(TestMediator)
		{
			using namespace mediator;
			Mediator m;
			Participant p1{ m }, p2{ m };

			ASSERT_EQ(0, p1.value);
			ASSERT_EQ(0, p2.value);

			p1.say(2);

			ASSERT_EQ(0, p1.value);
			ASSERT_EQ(2, p2.value);

			p2.say(4);

			ASSERT_EQ(4, p1.value);
			ASSERT_EQ(2, p2.value);
		}

		TEST_METHOD(TestMemento)
		{
			using namespace memento;
			{
				TokenMachine tm;
				auto m = tm.add_token(123);
				tm.add_token(456);
				tm.revert(m);
				ASSERT_EQ(1, (int)tm.tokens.size());
				ASSERT_EQ(123, tm.tokens[0]->value);
			}
			{
				TokenMachine tm;
				tm.add_token(1);
				auto m = tm.add_token(2);
				tm.add_token(3);
				tm.revert(m);
				ASSERT_EQ(2, (int)tm.tokens.size());
				ASSERT_EQ(1, tm.tokens[0]->value);
				ASSERT_EQ(2, tm.tokens[1]->value);
			}
			{
				TokenMachine tm;
				cout << "Made a token with value=111 and kept a reference\n";
				auto token = make_shared<Token>(111);
				cout << "Added this token to the list\n";
				tm.add_token(token);
				auto m = tm.add_token(222);
				cout << "Changed this token's value to 333 :)\n";
				token->value = 333;
				tm.revert(m);
				ASSERT_EQ(2, (int)tm.tokens.size());
				ASSERT_EQ(111, tm.tokens[0]->value);
			}	
		}

		TEST_METHOD(TestObserver)
		{
			using namespace observer;			
			{
				Game game;
				Rat rat{ game };
				ASSERT_EQ(1, rat.GetAttack());
			}
			{
				Game game;
				Rat rat{ game };
				Rat rat2{ game };
				ASSERT_EQ(2, rat.GetAttack());
				ASSERT_EQ(2, rat2.GetAttack());
			}
			{
				Game game;
				Rat rat{ game };
				ASSERT_EQ(1, rat.GetAttack());

				Rat rat2{ game };
				ASSERT_EQ(2, rat.GetAttack());
				ASSERT_EQ(2, rat2.GetAttack());

				{
					Rat rat3{ game };

					ASSERT_EQ(3, rat.GetAttack());
					ASSERT_EQ(3, rat2.GetAttack());
					ASSERT_EQ(3, rat3.GetAttack());
				}
			}
		}

		TEST_METHOD(TestState)
		{
			using namespace state;
			{
				CombinationLock cl({ 1,2,3 });
				ASSERT_EQ(0, cl.status.compare("LOCKED"));

				cl.enter_digit(1);
				ASSERT_EQ(0, cl.status.compare("1"));

				cl.enter_digit(2);
				ASSERT_EQ(0, cl.status.compare("12"));

				cl.enter_digit(3);
				ASSERT_EQ(0, cl.status.compare("OPEN"));
			}

			{
				CombinationLock cl({ 1,2,3 });
				ASSERT_EQ(0, cl.status.compare("LOCKED"));

				cl.enter_digit(1);
				ASSERT_EQ(0, cl.status.compare("1"));

				cl.enter_digit(2);
				ASSERT_EQ(0, cl.status.compare("12"));

				cl.enter_digit(5);
				ASSERT_EQ(0, cl.status.compare("ERROR"));
			}
		}

		bool compare_complex(complex<double> tmpl, complex<double> tmpr)
		{
			auto templ = tmpl;
			auto tempr = tmpr;
			return (tmpl == tmpr);
		}
		TEST_METHOD(TestStrategy)
		{
			using namespace strategy;
			{
				{
					OrdinaryDiscriminantStrategy strategy;
					QuadraticEquationSolver solver{ strategy };
					auto results = solver.solve(1, 10, 16);
					
					ASSERT_EQ(true, compare_complex(complex<double>(-2, 0), get<0>(results)));
					ASSERT_EQ(true, compare_complex(complex<double>(-8, 0), get<1>(results)));
				}

				{
					RealDiscriminantStrategy strategy;
					QuadraticEquationSolver solver{ strategy };
					auto results = solver.solve(1, 10, 16);
					ASSERT_EQ(true, compare_complex(complex<double>(-2, 0), get<0>(results)));
					ASSERT_EQ(true, compare_complex(complex<double>(-8, 0), get<1>(results)));
				}

				{
					OrdinaryDiscriminantStrategy strategy;
					QuadraticEquationSolver solver{ strategy };
					auto results = solver.solve(1, 4, 5);
					ASSERT_EQ(true, compare_complex(complex<double>(-2, 1), get<0>(results)));
					ASSERT_EQ(true, compare_complex(complex<double>(-2, -1), get<1>(results)));
				}

				{
					RealDiscriminantStrategy strategy;
					QuadraticEquationSolver solver{ strategy };
					auto results = solver.solve(1, 4, 5);
					auto x1 = get<0>(results);
					auto x2 = get<1>(results);
					ASSERT_TRUE(isnan(x1.real()));
					ASSERT_TRUE(isnan(x2.real()));
					ASSERT_TRUE(isnan(x1.imag()));
					ASSERT_TRUE(isnan(x2.imag()));
				}
			}
		}

		TEST_METHOD(TestTemplateMethod)
		{
			using namespace template_method;
			{
				{
					Creature c1{ 1,2 };
					Creature c2{ 1,2 };
					TemporaryCardDamageGame game({ c1,c2 });
					ASSERT_EQ(-1, game.combat(0, 1));
					ASSERT_EQ(-1, game.combat(0, 1));
				}

				{
					Creature c1{ 1,1 };
					Creature c2{ 2,2 };
					TemporaryCardDamageGame game({ c1,c2 });
					ASSERT_EQ(1, game.combat(0, 1));
				}

				{
					Creature c1{ 2,2 };
					Creature c2{ 2,2 };
					TemporaryCardDamageGame game({ c1,c2 });
					ASSERT_EQ(-1, game.combat(0, 1));
				}

				{
					Creature c1{ 1,2 };
					Creature c2{ 1,3 };
					PermanentCardDamageGame game({ c1, c2 });
					ASSERT_EQ(-1, game.combat(0, 1));
					ASSERT_EQ(1, game.combat(0, 1));
				}
			}
		}
	};
}
