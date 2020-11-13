/*
1. 종이 한 장을 꺼낸다.
2. 우리의 목표를 정한다. (1~2시간 안에 완료 할 수 있는 내용)
3. Brainstorming(브레인스토밍)을 통해 그 목표에 맞게 여러 task로 쪼갠다. (몇 분 안에 완료할 수 있는 내용)
4. 어떤 task를 먼저 할지, 어떤 식으로 접근할지에 대해 얘기한다.
5. 알람을 맞추고 일정 간격으로 ‘Driver-Navigator’가 되어 진행한다.
6. Task를 완료하면 목록에서 지우고 필요한 task를 추가/수정 하고 다음 Task를 선택 하여 진행한다.
7. 5~6번 과정을 반복한다.


- 목표 : 실습1~3 완료 (decorator pattern 이해 및 구현)
	실습 1) java코드를 분석하여 decorator pattern에 대해 이해한다.
	실습 2) java코드를 c++ 코드로 변경하여 decorator pattern을 구현한다.
	실습 3) 음료수 size를 추가하고, size에 따라 cost를 다르게 계산하는 기능을 구현한다.


- task
1. 실습1) 코드분석 진행
2. 실습2) Java코드를 C++ 코드로 변경하여 Decorator Pattern을 구현
3. 실습3) 음료수 size를 추가하고 size에 따라 cost를 다르게 계산

1. 실습1) 코드분석
Beverage는 추상 클래스로 선언되며, cost() 메소드는 추상메소드로 선언됨.

Beverage를 상속받는 클래스 : DarkRoast, Decaf, Espresso, HouseBlend, CondimentDecorator
CondimentDecorator를 상속받는 클래스:  Milk, Mocha, Soy, Whip

Beverage 클래스와 CondimentDecorator는 추상 클래스이다.

이후 Beverage를 다른 클래스가 상속받음.
CondimentDecorator와 음료와 관련한 클래스들로 나뉘며,
decorator에 관련한 클래스의 경우 CondimentDecorator를 상속받는다.
상속받는 각 클래스의 경우 description으로 음료의 이름을 나타내며,
각각의 가격에 맞게 cost()를 설정하고
Decorator의 경우 beverage를 추가적으로 설정하게 된다.

2. Java 코드를 C++ 코드로 변경하여 구현 / 3. 음료수 Size를 추가하고 Size에 따라 Cost를 다르게 계산
 1) 음료 구현		Driver: 김태완
 2) Decorator 구현	Driver: 임선구
 3) Size 구현		Driver: 곽현준

*/


#include <iostream>
#include <string>

enum BeverageSize{
	TALL,
	GRANDE,
	VENTI,
};

class Beverage {
protected:
	std::string description = "Unknown Beverage";
	BeverageSize size;
public:
	virtual std::string getDescription() {
		return description;
	};
	virtual double cost() = 0;
	
	void displayDescription() {
		std::cout << getDescription() << std::endl;
		std::cout << cost() << std::endl;
	}
	BeverageSize getSize() {
		return size;
	}
	void setSize(BeverageSize size) {
		this->size = size;
	}

	virtual ~Beverage() {}
};

class DarkRoast : public Beverage {
public:
	DarkRoast(BeverageSize size) {
		description = "DarkRoast";
		setSize(size);
	}
	double cost() {
		if (getSize() == TALL)
			return .89;
		else if (getSize() == GRANDE)
			return .99;
		else if (getSize() == VENTI)
			return 1.09;
	}
};

class Decaf : public Beverage {
public:
	Decaf(BeverageSize size) {
		description = "Decaf Coffee";
		setSize(size);
	}
	double cost() {
		if (getSize() == TALL)
			return .95;
		else if (getSize() == GRANDE)
			return 1.05;
		else if (getSize() == VENTI)
			return 1.15;
	}
};

class Espresso : public Beverage {
public:
	Espresso(BeverageSize size) {
		description = "Espresso";
		setSize(size);
	}
	double cost() {
		if (getSize() == TALL)
			return 1.89;
		else if (getSize() == GRANDE)
			return 1.99;
		else if (getSize() == VENTI)
			return 2.09;
	}
};

class HouseBlend : public Beverage {
public:
	HouseBlend(BeverageSize size) {
		description = "House Blend Coffee";
		setSize(size);
	}
	double cost() {
		if (getSize() == TALL)
			return .79;
		else if (getSize() == GRANDE)
			return .89;
		else if (getSize() == VENTI)
			return .99;
	}
};


class CondimentDecorator : public Beverage {
protected:
	Beverage* beverage;
public:
	CondimentDecorator(Beverage* beverage) {
		this->beverage = beverage;
	}
	~CondimentDecorator()
	{
		delete beverage;
	}
};

class Milk : public CondimentDecorator {
public:
	Milk(Beverage* beverage) : CondimentDecorator (beverage) {}
	std::string getDescription() {
		return beverage->getDescription() + ", Milk";
	}
	double cost() {
		if (getSize() == TALL)
			return beverage->cost() +.05;
		else if (getSize() == GRANDE)
			return beverage->cost() + .10;
		else if (getSize() == VENTI)
			return beverage->cost() + .15;
	}
};

class Mocha : public CondimentDecorator {
public:
	Mocha(Beverage* beverage) : CondimentDecorator (beverage) {}
	std::string getDescription() {
		return beverage->getDescription() + ", Mocha";
	}
	double cost() {
		if (getSize() == TALL)
			return beverage->cost() + .15;
		else if (getSize() == GRANDE)
			return beverage->cost() + .20;
		else if (getSize() == VENTI)
			return beverage->cost() + .25;
	}
};

class Soy : public CondimentDecorator {
public:
	Soy(Beverage* beverage) : CondimentDecorator (beverage) {}
	std::string getDescription() {
		return beverage->getDescription() + ", Soy";
	}
	double cost() {
		if (getSize() == TALL)
			return beverage->cost() + .10;
		else if (getSize() == GRANDE)
			return beverage->cost() + .15;
		else if (getSize() == VENTI)
			return beverage->cost() + .20;
	}
};

class Whip : public CondimentDecorator {
public:
	Whip(Beverage* beverage) : CondimentDecorator (beverage) {}
	std::string getDescription() {
		return beverage->getDescription() + ", Whip";
	}
	double cost() {
		if (getSize() == TALL)
			return beverage->cost() + .05;
		else if (getSize() == GRANDE)
			return beverage->cost() + .10;
		else if (getSize() == VENTI)
			return beverage->cost() + .15;
	}
};


int main() {
	Beverage* bever1 = new DarkRoast(TALL); // .89
	bever1 = new Milk(bever1); // 0.05
	bever1 = new Mocha(bever1); // 0.15
	bever1 = new Milk(bever1); // 0.05
	bever1->displayDescription(); //1.14

	Beverage* bever2 = new Espresso(GRANDE); // 1.99
	bever2 = new Milk(bever2); // 0.05
	bever2 = new Milk(bever2); // 0.05
	bever2 = new Milk(bever2); // 0.05
	bever2->displayDescription(); // 2.14

	Beverage* bever3 = new HouseBlend(VENTI); // .99
	bever3 = new Whip(bever3); // 0.15
	bever3 = new Milk(bever3); // 0.15
	bever3 = new Soy(bever3); // 0.20
	bever3 = new Mocha(bever3); // 0.25
	bever3->displayDescription(); // 1.74

	return 0;
}