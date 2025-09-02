# CYaRon!语

## 题目背景

「千歌です」（我是千歌）、「曜です」（我是曜）、「ルビィです」（我是露比）、「3人合わせて、We are CYaRon！ よろしくね！」（三人在一起，我们是CYaRon！多多指教哦！）


CYaRon!的三人在学习了编程之后，决定发明一种自己的编程语言，她们称为CYaRon!语。



(ltt: 明明是我帮她们发明的。)

可是，因为洛谷评测机这时候突然爆了，ltt没有时间再帮CYaRon!的三位小姐姐写CYaRon!语的解释器了。


于是ltt就出了这样一道题，然后等着有人交了AC程序就偷走给小姐姐们。


## 题目描述

以下是一个典型的CYaRon! 语程序。


```cpp
{ vars
    chika:int
    you:int
    ruby:array[int, 1..2]
    i:int
}
# 以上变量默认值均为0
# 变量名只可是英文字母。

# yosoro语句可以输出一个数字，随后跟一个空格。
:yosoro 2
# 输出2和一个空格(以下不再提到空格)。

# set语句可以为变量赋值。
# 运算符只支持加减号即可。
:set chika, 1
:set you, 2
:yosoro chika + you
# 上一条语句将输出3

# 以下的判断语句均使用以下的格式：
# 操作符，表达式，表达式
# 例如eq, a, 1即C语言中 a==1
# 所有操作符包括: lt: < gt: > le: <= ge: >= eq: == neq: !=

# 日本来的CYaRon三人没法正确地发出if这个音，因此她们就改成了ihu。
{ ihu eq, chika, 1
    :set you, 3
    :yosoro 1
}
# 输出1
# 以上是ihu语句，无需支持else。

# hor语句同理，
# for i=1 to you如下
{ hor i, 1, you
    :yosoro i
}
# 输出1 2 3

# 如下是while和数组的使用方法。
:set i, 1
{ while le, i, 2
    :yosoro i
    :set ruby[i], i+1
    :yosoro ruby[i]
    :set i, i+1
}
# 输出1 2 2 3

# 数组不会出现嵌套，即只会有a[i]、a[i+2]而不会有类似于a[i+b[i]]这样的。

# CYaRon语的最后一行，一定是一个换行。
 
```

你的任务是写一个CYaRon!语的解释器，实现输入CYaRon!语的程序，解释之执行后输出执行结果。


## 说明/提示

对数据做出以下保证：

1. 输入数据一定是合法的CYaRon!语程序，不包含注释，代码、缩进风格 （四个空格）与上述样例相同。**但不保证逗号、运算符前面的空格数量和有无一定相同**。

2. 变量名在10个字符以下，仅包含小写英文，数组最大大小为1000，变量最多50个，所有表达式的运算结果，包括变量的值一定在int范围内。 （但数组可能是类似于[2001..3000]的，下标可能范围为0到1亿）

3. 所有指令小写。

4. 该程序一定能够在合理的时间、内存限制内执行完毕。

5. hor语句执行过程中，循环变量、初始值、结束值不会被循环中的代码改变。

6. **该程序最多500行**

![](https://cdn.luogu.com.cn/upload/pic/4595.png)


## 样例 #1

### 输入

```
{ vars
    a:int
    b:int
}

:set a, 1
:set b, 2
:yosoro a+b
```

### 输出

```
3```

# 题解

## 作者：星野梦美 (赞：53)

**去年这个时候，我还在瞻仰这道题而无从下手，转眼一年又过去了啊，时间过得好快**

写解释器大概有两种动手方法：一种是程序员的思路，每次实现一点功能并调试，逐渐实现全部功能；另一种是OIer的思路，一次性码完所有代码然后开始调试。

显然第一种方法更合理一些。第二种方法虽然写起来很痛快，但是调试起来。。。

然而因为我太懒了，所以选择了第二种。

# 一、 规划结构

首先我们把程序过程分为“**解析代码**”和“**执行代码**”两部分。

解析代码：将源代码翻译成易于分析与执行的内部结构

执行代码：运行、维护内部代码、结构

可见，解析和执行之间，存在一个沟通的桥梁：**内部结构**。那么我们就先规划内部代码

# 二、内部结构

## 1、为什么要有内部结构

直接将源代码字符串完全储存下来然后运行可行吗？当然可行，但是这样做，无论是空间消耗还是时间消耗都完全不合适。将源代码翻译成内部代码（哪怕不设计新代码只是字对字的翻译），一方面压缩了空间，另一方面也便于执行。

## 2、代码结构

代码中存在两种基本的结构：**表达式**和**指令**。指令就是如 “ihu”、“while”、“set”的这些语句，而表达式则是如 “a + 2 - b\[3]” 这样的算式。显然程序是由一条一条指令拼接而成的，而表达式则是某些指令的一部分参数。不过在CYaRon!语中，还有一种特殊的结构，只存在于vars语句当中，用于声明变量。

## 3、变量的储存

CYaRon!语中只有两种变量：整数和整数数组。整数就用int即可，整数数组则需要写一个新的类型：

```cpp
struct arr {	//数组的储存结构
	int *val, start;	//需要有数组空间和起始地址
	arr(int s, int t): start(s) { val = new int[t - s + 5]; }
	void aset(int i, int v) { val[i - start] = v; }	//赋值
	int aget(int i) { return val[i - start]; }	//取值
};
```

上面的代码在实现数组的同时还有两个成员函数aset与aget，意义很好理解。

与 c++ 一样，这个解释器并不会进行数组越界检查（因为我懒）。

所以我们直接把变量储存在map里，需要时直接从map里查：

```cpp
map<std::string, int> inttable;	//储存整数变量
map<std::string, arr*> arrtable;	//储存数组变量
```

注意到我们储存数组变量实际上只存了指向数组的指针，在之后的处理中也应当注意这一点。

用map储存，不仅慢，而且在内部代码中也要处处保存着变量名的字符串。实际上存在一种更优秀也是更通用的做法，就是把变量处理成地址，之后直接在这个地址中搞事，速度快且省空间。但是因为懒，姑且先用map。

## 4、表达式

在传统编程语言中，复杂的表达式往往会被解析成若干个非常简单的运算。在CYaRon!语中，因为表达式只存在“+”、“-”，这无疑给了我们极大的便利：将每个表达式处理成一串“**表达式块**”，每个块只包含一个变量或常数以及一个符号标志，表达式的求值可以被简化成求“这些块的取值的和”。

那么
我们就可以把表达式处理成一个表达式块的链表，这个链表的实现如下：
```cpp
struct Expression {	//表达式储存结构
	int type;	//表达式类型（0为常数，1为整数变量，2为数组变量）
	int symbol;	//正负
	Expression *arre;	//（数组专用）数组下标的表达式
	std::string val;	//表达式的形态（常数为数字串，变量为变量名，常数不需要带符号，数组不需要带下标）
	Expression *nxt;	//下一条表达式（我们使用链表结构储存一整个表达式）
	
	int eget() {	//表达式取值
		int num = 0;
		if(type == 0) {	//如果是常数
			for(int i = 0; i < val.size(); ++i) num = num * 10 + val[i] - '0';	//获取数值
		} else if(type == 1) {	//如果是整数变量
			num = inttable[val];	//从内存中找到变量的值
		} else if(type == 2) {	//如果是数组
			num = arrtable[val]->aget(arre->eget());	//从内存中找数组并根据下标表达式计算出下标并访问
		} else {	//其他情况
			throw("RE");	//是不存在的如果真的存在说明程序出BUG了
		}
		num *= symbol;	//带上符号
		if(nxt != NULL) return num + nxt->eget();	//如果后面还有表达式，计算后面的表达式并加上
		return num;
	}
};
```

在这份代码中还有一些表达式的其他属性，如表达式类型，数组下标表达式，以及表达式形态。

表达式类型描述了这个表达式（块）是常数还是整数变量还是数组，数组下标表达式专为数组服务，用来储存下标。虽然题目描述中数组下标不会嵌套，但是用这种实现方法，完全可以支持嵌套。表达式形态的意义便是储存表达式的“特征值”，实际储存的是变量名或数字串。

作为链表，理应有一个指向下一个块的指针。

这里我们还有一个有趣函数 eget，用来表达式求值，他的工作原理也相当简单，阅读代码及注释便可理解。

## 5、变量声明

与表达式相同的是，我们将一个vars语句中的所有变量声明处理成一个链表。


```
struct Initer {	//变量声明储存结构
	int type;	//变量类型（0为整数，1为数组）
	std::string name;	//变量名
	int begin, end;	//（数组专用）起始值与终止值
	Initer *nxt;	//下一条变量声明（我们使用链表结构储存一整串变量声明）
};
```

## 6、指令

嗯你没猜错，我把指令也处理成链表了。

指令有一些特殊的属性，如仅供vars使用的变量声明表，仅供if、hor、while使用的比较类型以及仅供if、hor、while使用的子指令表。

指令还包含了三个表达式，这三个表达式在不同语句中用途不同（或不使用），在注释中有详细说明。值得注意的是，在CYaRon!中，hor 的三个表达式给出的先后顺序是：循环变量、起始值、终止值，而内部指令中却把起始值放到了exp3，终止值放到了exp1，这实际上是给后面的执行创造了便利。

虽然hor语句没有显式的判断类型，但我们仍需要手动设置成“le”，这也是在为执行创造便利。

```cpp
struct Instruction {	//指令的储存结构
	int type;	//指令类型（0为vars，1为set，2为yosoro，3为ihu，4为hor，5为while）
	Initer *init;	//（var专用）初始化变量列表
	Expression *exp1, *exp2, *exp3;	//exp1：set被赋值项，yosoro被输出表达式，ihu左值，hor循环变量，while左值
									//exp2：ihu右值，hor结束值，while右值
									//exp3：set源赋值表达式，hor初始值
	int judgetype;	//ihu、while、hor专用，比较类型（0为lt，1为gt，2为le，3为ge，4为eq，5为neq），hor需要始终设置为2（le）
	Instruction *subins;	//ihu、hor、while专用，子指令块
	Instruction *nxt;	//下一条指令（我们用链表结构储存一整串指令）
};
```

# 三、执行

从时间顺序来说，应该是先读取解析而后执行，但是执行部分的逻辑更为清晰，地位也更为重要，实现起来却相对简单，所以我先描述执行环节。

## 1、运行指令

一串switch而已，见代码：

```cpp
void Run(Instruction *ins)	//处理指令
{
	while(ins != NULL) //一条一条执行下去下去
	{
		switch(ins->type)	//分清指令类型
		{
		case 0:
			_vars(ins);
			break;
		case 1:
			_set(ins);
			break;
		case 2:
			_yosoro(ins);
			break;
		case 3:
			_ihu(ins);
			break;
		case 4:
			_hor(ins);
			break;
		case 5:
			_while(ins);
			break;
		default:
			throw("RE: Something wrong with the type of a instruction.");
		}
		ins = ins->nxt;	//下一条
	}
}
```

虽然此题保证不会出现错误代码，不过顺便把错误判断写上也不碍事，而且思路更为清晰。之后你会看到此解释器中有无数个CE判断。

分别实现每一种语句：

## vars：

```cpp
void _vars(Instruction *ins)	//处理var语句
{
	for(Initer *i = ins->init; i != NULL; i = i->nxt) //遍历每一条变量声明
	{
		if(i->type == 0) inttable[i->name] = 0;	//如果是整数，直接在整数内存中设置为0
		else if(i->type == 1) {	//如果是数组
			arrtable[i->name] = new arr(i->begin, i->end);	//在数组内存中插入一个新的数组
		} else {	//其他情况
			throw("RE: Something wrong with the type of a Initer.");	//不可能有其他情况如果有就说明程序出BUG了
		}
	}
}
```

## set：

```cpp
void _set(Instruction *ins)	//处理set语句
{
	Expression *exp1 = ins->exp1, *exp3 = ins->exp3;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	if(exp1->type == 1) {	//如果被赋值项是整数变量
		inttable[exp1->val] = exp3->eget();	//直接在内存中改变值
	} else if(exp1->type == 2) {	//如果被赋值项是数组
		arrtable[exp1->val]->aset(exp1->arre->eget(), exp3->eget());	//获取数组下标并根据下标设置数组的值
	} else {	//其他情况
		throw("CE: exp1 is not a variable");	//不可能有其他情况，如果有可能是输入时表达式就不正确
	}
}
```

## yosoro：

```cpp
void _yosoro(Instruction *ins)	//处理yosoro语句
{
	printf("%d ", ins->exp1->eget());	//计算表达式的值并输出，后跟一个空格
}
```

## ihu：

```cpp
bool _ihu(Instruction *ins)	//处理ihu语句
{
	Expression *exp1 = ins->exp1, *exp2 = ins->exp2;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	switch(ins->judgetype)	//对于每一种判断，如果不符合就返回false
	{
	case 0:	//lt
		if(exp1->eget() >= exp2->eget()) return false;
		break;
	case 1:	//gt
		if(exp1->eget() <= exp2->eget()) return false;
		break;
	case 2:	//le
		if(exp1->eget() > exp2->eget()) return false;
		break;
	case 3:	//ge
		if(exp1->eget() < exp2->eget()) return false;
		break;
	case 4:	//eq
		if(exp1->eget() != exp2->eget()) return false;
		break;
	case 5: //neq
		if(exp1->eget() == exp2->eget()) return false;
		break;
	default:
		throw("RE: Something wrong with the type of a judge");
	}
	Run(ins->subins);	//如果符合结果就执行子指令块
	return true;	//返回true
}
```

ihu的实现比较特殊，他要执行子指令，同时还有一个返回值表示判断结果。

## hor：

```cpp
void _hor(Instruction *ins)	//处理hor语句
{
	Expression *exp1 = ins->exp1, *exp2 = ins->exp2, *exp3 = ins->exp3;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	_set(ins);	//把exp3赋值给exp1
	while(_ihu(ins)) {	//利用ihu语句反复执行
		if(exp1->type == 1) {	//+1操作，循环变量如果是整数变量
			++inttable[exp1->val];	//直接加
		} else if(exp1->type == 2) {	//如果是数组
			int i = exp1->arre->eget();	//获得下标
			arrtable[exp1->val]->aset(i, arrtable[exp1->val]->aget(i) + 1); //加上去
		} else {	//如果其他类型
			throw("CE: exp1 is not a variable");	//不可能
		}
	}
}
```

这里我们就可以看出之前把hor的初始值放到exp3而终止值放到exp2的用意了，我们利用_ihu不停的判断兼执行，而ihu判断两个表达式的则是exp1与exp2，初始值在赋值完成后就没用了，所以放到了exp3。

## while:

```cpp
void _while(Instruction *ins)	//处理while语句
{
	while(_ihu(ins));	//利用ihu反复执行
}
```

while实现起来最简单了。

执行部分到这里就没有了，接下来就要写最麻烦的读入解析部分了。

# 四、读入

读入没什么可简介的。

## 1、读入方式

有人喜欢一次读入整个代码文件然后在字符数组里搞事，有人喜欢一行一行的读，有人是一个单词一个单词的读入，但是鉴于本人太过于懒惰不愿意写那么复杂的读入，所以就用getchar了，边读入边处理。每次需要一个字符就读一个字符，读到EOF就算是读完了。

但是还不想直接用getchar，虽然题目中说代码里没有注释，但是由于觉得难受还是加上了注释判断，注释用 “#”开头，此后一直到行末都是注释内容。

我们先写一个可以吞掉注释getchar：

```cpp
char _getc() { //一个可以吞掉注释的getchar()
	char ch = getchar();
	if(ch == '#') while(ch != '\n' && ch != EOF) ch = getchar();
	return ch; 
}
```

我们弄一个全局都在使用的字符变量 “c”，以后每次都把字符读进这里边来：

```cpp
char c;

// 以后就这么读入
c = _getc();
```

## 2、“c” 中到底有什么

我们总是一个字符一个字符的读入，然后处理即可。但是注意到一个问题：当我们读入一个内容的时候，是如何知道它读完了呢？其实有两种情况：

1、当前内容只使用特定的字符，读到别的字符就意味着结束了。例如读入常数时，如果读到不是数字的字符就意味着常数读完了；读入变量名时，遇到不是字母的字符意味着变量名读完了。

2、当前内容的字符比较多，但是有一个特殊的字符，我们称之为**结束标志**，一旦读到结束标志就意味着读完了，没遇到结束标志就一直读下去。如读入数组下标表达式时，读到 “ ] ” 就可以知道下标表达式读完了。

这两种结束方式的区别在于，第一种方法，在结束读入后，c 中保存的是**下一个要读入的内容的第一个字符**，也就意味着读入下一个内容时不必先读入而默认 c 中有内容，对于后一种情况则不然。

可是读入时怎么能知道 c 中到底保存了结束符还是自己的第一个字符？这个判断自己是往往做不了的。虽然我不知道上一个读入是怎么结束的，但是我可以知道自己是怎么结束的。那么我们规定：**以结束标志结束的读入要在结束后再读入一次**，这样就可以保证对于每一次读入，**c 中预先总是保存了他的第一个字符而无须读入了**。

## 3、读入指令

```cpp
void ReadInstruction(char endc, Instruction *ins)
{
	while(c != endc) 
	{
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
		if(c == '{' || c == ':')	//指令
		{
			std::string opt;
			c = _getc();
			while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
			while(c >= 'a' && c <= 'z') { //获取指令名称
				opt.push_back(c);
				c = _getc();
			}
			if(c != ' ' && c != '\t' && c != '\n' && c != '\r') throw("CE: Unexpected character. ");	//不是以空字符结尾的直接CE
			
			if(opt == "vars")
				readvars(ins);
			else if(opt == "set")
				readset(ins);
			else if(opt == "yosoro")
				readyosoro(ins);
			else if(opt == "ihu")
				readihu(ins);
			else if(opt == "hor")
				readhor(ins);
			else if(opt == "while")
				readwhile(ins);
			else	//未定义的指令
				throw("CE: Unknow Instruciton. ");
				
			ins->nxt = new Instruction();
			ins = ins->nxt;
			
			while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
		} else {	//非法字符
			throw("CE: Unexpected character. ");
		}
	}
}
```

两个参数分别为结束标志与要读入指令的指针所在。

结束标志有主程序的 EOF，也有子指令的 “ } ”，这个要看调用者的意思。

指令所在指针**必须事先初始化**。

其他地方比较好理解。

## 读入一些非指令内容

读入变量声明：

```cpp
void readiniter(Initer *init)	//读取变量声明
{
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//吞掉空字符
	if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) throw("CE: Unexpected character. "); //非字母不可以作变量名
	std::string name;
	while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读取变量名
		name.push_back(c);
		c = _getc();
	}
	init->name = name;
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //允许变量名和冒号之间有空字符
	if(c != ':') throw("CE");	//非法字符
	c = _getc();
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许冒号和类型之间有空字符
	name.clear();
	if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) throw("CE: Unexpected character. TT"); //非字母不可以作类型名
	while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		name.push_back(c);
		c = _getc();
	}
	if(name == "int") {	//int
		init->type = 0;
	} else if(name == "array") {	//array
		init->type = 1;
		if(c != '[') throw("CE: Unexpected character. ");	//array后面紧跟的不是"["就不行（我规定的）
		name.clear();
		c = _getc();
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许方括号后面有空字符
		while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读取类型名
			name.push_back(c);
			c = _getc();
		}
		if(name != "int") throw("CE: Unknow type. ");	//不是int肯定不行
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许类型名后面有空字符
		if(c != ',') throw("CE: Unexpected character. ");	//不是"，"也不行
		c = _getc();
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
		int num = 0;
		while(c >= '0' && c <= '9') {	//读取起始下标
			num = num * 10 + c - '0';
			c = _getc();
		}
		init->begin = num;
		if(c == '.') {	//".."必须与两个值紧凑的挨在一起（我规定的）
			c = _getc();
			if(c != '.') throw("CE: Unexpected character. ");
		} else throw("CE");
		c = _getc();
		num = 0;
		while(c >= '0' && c <= '9') { //读取终止下标
			num = num * 10 + c - '0';
			c = _getc();
		}
		init->end = num;
		c = _getc();
	} else throw("CE: Unknow type. ");
}
```

变量声明的参数也是指向该声明的指针，也必须初始化好。

读取表达式：

```cpp
void readexpression(char endc, Expression *&expr)	//读取表达式，endc为表达式终止的标志
{
	expr = new Expression();
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //先把前面的空字符吞了
	if(c == '-') {	//如果是"-"，那就是负的
		expr->symbol = -1; 
		c = _getc(); while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//因为读到了符号，所以主体还在后面
	}
	else if(c == '+') {	//如果是"+"，那就是正的
		expr->symbol = 1;
		c = _getc(); while(c == ' ' || c == '\n' || c == '\t' || c == '\r')	c = _getc();	//理由同上
	} else {
		expr->symbol = 1;	//没指明正负也是正的，只是不用继续往下读了
	}
	
	if(c >= '0' && c <= '9') {	//如果是常数
		expr->type = 0;
		std::string num;	//直接把数字读成字符串，解析扔给执行那边，读入这里就不管了
		while(c >= '0' && c <= '9') {
			num.push_back(c);
			c = _getc();
		}
		expr->val = num;
	} else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//如果是变量
		std::string name;
		while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读完变量名
			name.push_back(c);
			c = _getc();
		}
		expr->val = name;
		if(c == '[') {	//如果是array
			expr->type = 2;
			c = _getc();
			readexpression(']', expr->arre);	//以"]"为终止标志读取数组下标表达式
		} else expr->type = 1;
	}
	while(c != endc && (c == ' ' || c == '\n' || c == '\t' || c == '\r')) c = _getc();	//一直吞空字符，直到读到结束标志或其他字符为止（这里结束标志也可能是四大空字符之一）
	if(c == '+' || c == '-') readexpression(endc, expr->nxt);	//如果是正负（加减）号就读下一个表达式
	else if(c == endc) c = _getc();	//终止符就再读一个字符走人
	else throw("CE: Unexpected character. ");	//不可能是别的字符，如果是就CE
}
```

表达式也有结束标志，例如逗号，换行，“]”，这些要看调用者的意愿。

读入表达式传入的是**指向表达式的指针的引用**，读入表达式时会自行初始化，无须提前初始化。

读入比较判断：

```cpp
int readjudge()
{
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
	if(c == 'l') {	//读取比教的类型，不符合6个类型之一的CE掉
		c = _getc();
		if(c == 't') {
			return 0;	//lt
		} else if(c == 'e') {
			return 2;	//le
		} else throw("CE: Unexpected character. ");
	} else if(c == 'g') {
		c = _getc();
		if(c == 't') {
			return 1;	//gt
		} else if(c == 'e') {
			return 3;	//ge
		} else throw("CE: Unexpected character. ");
	} else if(c == 'e') {
		c = _getc();
		if(c == 'q') {
			return 4;	//eq
		} else throw("CE: Unexpected character. ");
	} else if(c == 'n') {
		if(c == 'e') {
			c = _getc();
			if(c == 'q') {
				return 5;	//neq
			} else throw("CE: Unexpected character. ");
		} else throw("CE: Unexpected character. ");
	} else throw("CE: Unexpected character. ");
}
```

这个没什么可说的。

## readvars：

```cpp
void readvars(Instruction *ins)	//读取vars
{
	ins->init = new Initer();
	Initer *init = ins->init;
	while(c != '}') {
		readiniter(init);
		init->nxt = new Initer();
		init = init->nxt;
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
	}
	ins->type = 0;
	c = _getc();
}
```

先给指令的变量声明表初始化好。每次读取完换成下一条接着读取。


## readset：

```cpp
void readset(Instruction *ins)	//读取set
{
	ins->type = 1;
	readexpression(',', ins->exp1);	//以逗号为结束标志读取exp1
	readexpression('\n', ins->exp3); //以换行为结束标志读取exp2
}

```

## readyosoro：

```cpp
void readyosoro(Instruction *ins)	//读取yosoro
{
	ins->type = 2;
	readexpression('\n', ins->exp1);	//以换行为结束标志读取exp1
}
```

## readihu：

```cpp
void readihu(Instruction *ins)	//读取ihu
{
	ins->type = 3;
	ins->judgetype = readjudge();	//读取比较类型
	readexpression(',', ins->exp1);	//以逗号为结束标志读取exp1
	readexpression('\n', ins->exp2);	//以换行为结束标志读取exp2
	ins->subins = new Instruction();
	ReadInstruction('}', ins->subins);	//以有括号为结束标志读取subins
}
```

从 ihu 开始出现了子指令的读入。

## readhor：

```cpp
void readhor(Instruction *ins)	//读取hor
{
	ins->type = 4;
	ins->judgetype = 2;	//比较类型天然为le
	readexpression(',', ins->exp1);	//以=为结束标志读取循环变量
	readexpression(',', ins->exp3);	//以t为结束标志读取初值
	readexpression('\n', ins->exp2);	//以换行为结束标志读取终止值
	ins->subins = new Instruction();
	ReadInstruction('}', ins->subins);
}
```

## readwhile：

```cpp
void readwhile(Instruction *ins)	//读取while
{
	readihu(ins);	//因为内部是相同的直接很赖皮的用ihu读入
	ins->type = 5;	//然后把类型改过来就行了
}
```

while 和 ihu 在表示上实在是太像了。

至此读入部分也完成了。

# 五、收尾

```cpp
Instruction *Main;	//主指令串

int main()
{
	c = _getc();	//先读一个字符
	Main = new Instruction();
	try {
		ReadInstruction(EOF, Main);	//以EOF为结束标志读取Main
		Run(Main);
        printf("\n");
	} catch (const char* e) {
		cerr << e << endl;
	}
	return 0;
}
```

在提交的时候为了保证效率可以把异常处理删掉。

# 六、测试

写是写完了，正确性还得不到保证。我们写一些CYaRon!程序测试一下：

## test1.cyr 三连击直接输出：

既然题目描述中第一个测试点是三连击直接输出。

```python
# test1.cyr

:yosoro 192
:yosoro 384
:yosoro 576
:yosoro 219
:yosoro 438
:yosoro 657
:yosoro 273
:yosoro 546
:yosoro 819
:yosoro 327
:yosoro 654
:yosoro 981

```

输出结果：

```
192 384 576 219 438 657 273 546 819 327 654 981 

```

通过。

## test2.cyr A+B Problem：

```python
# test2.cyr

{ vars
	a:int
	b:int
}

:set a, 1
:set b, 2

:yosoro a + b

```

输出结果：

```
3
```

通过。

## test3.cyr 把三连击放入数组

题目描述不说就自己编一个。

与 test1 不同，test3 先把三连击的答案存入数组，而后输出。

```python
# test3.cyr

{ vars 
	myarr:array[int, 100..150]
}

:set myarr[100], 192
:set myarr[101], 384
:set myarr[102], 576
:set myarr[103], 219
:set myarr[104], 438
:set myarr[105], 657
:set myarr[106], 273
:set myarr[107], 546
:set myarr[108], 819
:set myarr[109], 327
:set myarr[110], 654
:set myarr[111], 981

:yosoro myarr[100]
:yosoro myarr[101]
:yosoro myarr[102]
:yosoro myarr[103]
:yosoro myarr[104]
:yosoro myarr[105]
:yosoro myarr[106]
:yosoro myarr[107]
:yosoro myarr[108]
:yosoro myarr[109]
:yosoro myarr[110]
:yosoro myarr[111]

```

输出结果：

```
192 384 576 219 438 657 273 546 819 327 654 981
```

通过。

## test4.cyr 数组翻转

再自己编一个程序。

```python
# test4.cyr

{ vars
	myarr:array[int, 1..6]
	tmp:int
}

:set myarr[1], 1
:set myarr[2], 2
:set myarr[3], 3
:set myarr[4], 4
:set myarr[5], 5
:set myarr[6], 6

:set tmp, myarr[1]
:set myarr[1], myarr[6]
:set myarr[6], tmp

:set tmp, myarr[2]
:set myarr[2], myarr[5]
:set myarr[5], tmp

:set tmp, myarr[3]
:set myarr[3], myarr[4]
:set myarr[4], tmp

:yosoro myarr[1]
:yosoro myarr[2]
:yosoro myarr[3]
:yosoro myarr[4]
:yosoro myarr[5]
:yosoro myarr[6]

```

输出结果：

```
6 5 4 3 2 1
```

通过。

## test5.cyr - test10.cyr

因为过于复杂并且我想要睡觉以及明天月考还有现在晚上12:30等种种原因实在懒得写了。

不过先把没测试过的语句测试一遍。

## testihu.cyr

```python
# testihu.cyr

{ vars
	a:int
	b:array[int, 1..1]
}

:set a, 233
:set b[1], 233

{ ihu eq, a, b[1] # 这里其他判断类型都试一下
	:yosoro 1
}

```

输出结果：

```
1
```

通过。

## testhor.cyr

```python
# testhor.cyr

{ vars 
	myarr:array[int, 100..150]
	i:int
}

:set myarr[100], 192
:set myarr[101], 384
:set myarr[102], 576
:set myarr[103], 219
:set myarr[104], 438
:set myarr[105], 657
:set myarr[106], 273
:set myarr[107], 546
:set myarr[108], 819
:set myarr[109], 327
:set myarr[110], 654
:set myarr[111], 981

{ hor i = 100 to 111
	:yosoro myarr[i]
}

```

输出结果：

```
192 384 576 219 438 657 273 546 819 327 654 981 
```

通过。

## testwhile.cyr

```python
# testwhile.cyr

{ vars 
	myarr:array[int, 100..150]
	i:int
}

:set myarr[100], 192
:set myarr[101], 384
:set myarr[102], 576
:set myarr[103], 219
:set myarr[104], 438
:set myarr[105], 657
:set myarr[106], 273
:set myarr[107], 546
:set myarr[108], 819
:set myarr[109], 327
:set myarr[110], 654
:set myarr[111], 981

:set i, 111

{ while ge, i, 100
	:yosoro myarr[i]
	:set i, i - 1
}
```

输出结果：

```
981 654 327 819 546 273 657 438 219 576 384 192
```

通过。

# 七、结束了

到现在CYaRon!语解释器已经写完了，该测试的也测试过了，可以交了。不过，这个程序有两个已知BUG：

1、set语句被赋值表达式可以是很长一串，因为我们只判断处理了第一项，虽然不会引发错误，但还是不合理的

2、题目保证最后一行一定是空行，而此解释器也必须保证这一点否则会出错，虽然不影响评测，但还是不完美

如果有其他BUG的存在，请务必指出！感激不尽

在最后贴一下完整代码吧：

```cpp
#include<bits/stdc++.h>

using namespace std;

char _getc() { //一个可以吞掉注释的getchar()
	char ch = getchar();
	if(ch == '#') while(ch != '\n' && ch != EOF) ch = getchar();
	return ch; 
}

struct arr {	//数组的储存结构
	int *val, start;	//需要有数组空间和起始地址
	arr(int s, int t): start(s) { val = new int[t - s + 5]; }
	void aset(int i, int v) { val[i - start] = v; }	//赋值
	int aget(int i) { return val[i - start]; }	//取值
};

map<std::string, int> inttable;	//储存整数变量
map<std::string, arr*> arrtable;	//储存数组变量

struct Initer {	//变量声明储存结构
	int type;	//变量类型（0为整数，1为数组）
	std::string name;	//变量名
	int begin, end;	//（数组专用）起始值与终止值
	Initer *nxt;	//下一条变量声明（我们使用链表结构储存一整串变量声明）
};

struct Expression {	//表达式储存结构
	int type;	//表达式类型（0为常数，1为整数变量，2为数组变量）
	int symbol;	//正负
	Expression *arre;	//（数组专用）数组下标的表达式
	std::string val;	//表达式的形态（常数为数字串，变量为变量名，常数不需要带符号，数组不需要带下标）
	Expression *nxt;	//下一条表达式（我们使用链表结构储存一整个表达式）
	
	int eget() {	//表达式取值
		int num = 0;
		if(type == 0) {	//如果是常数
			for(int i = 0; i < val.size(); ++i) num = num * 10 + val[i] - '0';	//获取数值
		} else if(type == 1) {	//如果是整数变量
			num = inttable[val];	//从内存中找到变量的值
		} else if(type == 2) {	//如果是数组
			num = arrtable[val]->aget(arre->eget());	//从内存中找数组并根据下标表达式计算出下标并访问
		} else {	//其他情况
			throw("RE");	//是不存在的如果真的存在说明程序出BUG了
		}
		num *= symbol;	//带上符号
		if(nxt != NULL) return num + nxt->eget();	//如果后面还有表达式，计算后面的表达式并加上
		return num;
	}
};

struct Instruction {	//指令的储存结构
	int type;	//指令类型（0为var，1为set，2为yosoro，3为ihu，4为hor，5为while）
	Initer *init;	//（var专用）初始化变量列表
	Expression *exp1, *exp2, *exp3;	//exp1：set被赋值项，yosoro被输出表达式，ihu左值，hor循环变量，while左值
									//exp2：ihu右值，hor结束值，while右值
									//exp3：set源赋值表达式，hor初始值
	int judgetype;	//ihu、while、hor专用，比较类型（0为lt，1为gt，2为le，3为ge，4为eq，5为neq），hor需要始终设置为2（le）
	Instruction *subins;	//ihu、hor、while专用，子指令块
	Instruction *nxt;	//下一条指令（我们用链表结构储存一整串指令）
};

void Run(Instruction *ins);

void _vars(Instruction *ins)	//处理var语句
{
	for(Initer *i = ins->init; i != NULL; i = i->nxt) //遍历每一条变量声明
	{
		if(i->type == 0) inttable[i->name] = 0;	//如果是整数，直接在整数内存中设置为0
		else if(i->type == 1) {	//如果是数组
			arrtable[i->name] = new arr(i->begin, i->end);	//在数组内存中插入一个新的数组
		} else {	//其他情况
			throw("RE: Something wrong with the type of a Initer.");	//不可能有其他情况如果有就说明程序出BUG了
		}
	}
}

void _set(Instruction *ins)	//处理set语句
{
	Expression *exp1 = ins->exp1, *exp3 = ins->exp3;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	if(exp1->type == 1) {	//如果被赋值项是整数变量
		inttable[exp1->val] = exp3->eget();	//直接在内存中改变值
	} else if(exp1->type == 2) {	//如果被赋值项是数组
		arrtable[exp1->val]->aset(exp1->arre->eget(), exp3->eget());	//获取数组下标并根据下标设置数组的值
	} else {	//其他情况
		throw("CE: exp1 is not a variable");	//不可能有其他情况，如果有可能是输入时表达式就不正确
	}
}

void _yosoro(Instruction *ins)	//处理yosoro语句
{
	printf("%d ", ins->exp1->eget());	//计算表达式的值并输出，后跟一个空格
}

bool _ihu(Instruction *ins)	//处理ihu语句
{
	Expression *exp1 = ins->exp1, *exp2 = ins->exp2;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	switch(ins->judgetype)	//对于每一种判断，如果不符合就返回false
	{
	case 0:	//lt
		if(exp1->eget() >= exp2->eget()) return false;
		break;
	case 1:	//gt
		if(exp1->eget() <= exp2->eget()) return false;
		break;
	case 2:	//le
		if(exp1->eget() > exp2->eget()) return false;
		break;
	case 3:	//ge
		if(exp1->eget() < exp2->eget()) return false;
		break;
	case 4:	//eq
		if(exp1->eget() != exp2->eget()) return false;
		break;
	case 5: //neq
		if(exp1->eget() == exp2->eget()) return false;
		break;
	default:
		throw("RE: Something wrong with the type of a judge");
	}
	Run(ins->subins);	//如果符合结果就执行子指令块
	return true;	//返回true
}

void _hor(Instruction *ins)	//处理hor语句
{
	Expression *exp1 = ins->exp1, *exp2 = ins->exp2, *exp3 = ins->exp3;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	_set(ins);	//把exp3赋值给exp1
	while(_ihu(ins)) {	//利用ihu语句反复执行
		if(exp1->type == 1) {	//+1操作，循环变量如果是整数变量
			++inttable[exp1->val];	//直接加
		} else if(exp1->type == 2) {	//如果是数组
			int i = exp1->arre->eget();	//获得下标
			arrtable[exp1->val]->aset(i, arrtable[exp1->val]->aget(i) + 1); //加上去
		} else {	//如果其他类型
			throw("CE: exp1 is not a variable");	//不可能
		}
	}
}

void _while(Instruction *ins)	//处理while语句
{
	while(_ihu(ins));	//利用ihu反复执行
}

void Run(Instruction *ins)	//处理指令
{
	while(ins != NULL) //一条一条执行下去下去
	{
		switch(ins->type)	//分清指令类型
		{
		case 0:
			_vars(ins);
			break;
		case 1:
			_set(ins);
			break;
		case 2:
			_yosoro(ins);
			break;
		case 3:
			_ihu(ins);
			break;
		case 4:
			_hor(ins);
			break;
		case 5:
			_while(ins);
			break;
		default:
			throw("RE: Something wrong with the type of a instruction.");
		}
		ins = ins->nxt;	//下一条
	}
}

Instruction *Main;	//主指令串
char c;	//用来保存当前字符

void ReadInstruction(char endc, Instruction *ins);

void readiniter(Initer *init)	//读取变量声明
{
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//吞掉空字符
	if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) throw("CE: Unexpected character. "); //非字母不可以作变量名
	std::string name;
	while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读取变量名
		name.push_back(c);
		c = _getc();
	}
	init->name = name;
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //允许变量名和冒号之间有空字符
	if(c != ':') throw("CE");	//非法字符
	c = _getc();
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许冒号和类型之间有空字符
	name.clear();
	if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) throw("CE: Unexpected character. TT"); //非字母不可以作类型名
	while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		name.push_back(c);
		c = _getc();
	}
	if(name == "int") {	//int
		init->type = 0;
	} else if(name == "array") {	//array
		init->type = 1;
		if(c != '[') throw("CE: Unexpected character. ");	//array后面紧跟的不是"["就不行（我规定的）
		name.clear();
		c = _getc();
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许方括号后面有空字符
		while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读取类型名
			name.push_back(c);
			c = _getc();
		}
		if(name != "int") throw("CE: Unknow type. ");	//不是int肯定不行
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许类型名后面有空字符
		if(c != ',') throw("CE: Unexpected character. ");	//不是"，"也不行
		c = _getc();
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
		int num = 0;
		while(c >= '0' && c <= '9') {	//读取起始下标
			num = num * 10 + c - '0';
			c = _getc();
		}
		init->begin = num;
		if(c == '.') {	//".."必须与两个值紧凑的挨在一起（我规定的）
			c = _getc();
			if(c != '.') throw("CE: Unexpected character. ");
		} else throw("CE");
		c = _getc();
		num = 0;
		while(c >= '0' && c <= '9') { //读取终止下标
			num = num * 10 + c - '0';
			c = _getc();
		}
		init->end = num;
		c = _getc();
	} else throw("CE: Unknow type. ");
}

void readexpression(char endc, Expression *&expr)	//读取表达式，endc为表达式终止的标志
{
	expr = new Expression();
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //先把前面的空字符吞了
	if(c == '-') {	//如果是"-"，那就是负的
		expr->symbol = -1; 
		c = _getc(); while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//因为读到了符号，所以主体还在后面
	}
	else if(c == '+') {	//如果是"+"，那就是正的
		expr->symbol = 1;
		c = _getc(); while(c == ' ' || c == '\n' || c == '\t' || c == '\r')	c = _getc();	//理由同上
	} else {
		expr->symbol = 1;	//没指明正负也是正的，只是不用继续往下读了
	}
	
	if(c >= '0' && c <= '9') {	//如果是常数
		expr->type = 0;
		std::string num;	//直接把数字读成字符串，解析扔给执行那边，读入这里就不管了
		while(c >= '0' && c <= '9') {
			num.push_back(c);
			c = _getc();
		}
		expr->val = num;
	} else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//如果是变量
		std::string name;
		while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读完变量名
			name.push_back(c);
			c = _getc();
		}
		expr->val = name;
		if(c == '[') {	//如果是array
			expr->type = 2;
			c = _getc();
			readexpression(']', expr->arre);	//以"]"为终止标志读取数组下标表达式
		} else expr->type = 1;
	}
	while(c != endc && (c == ' ' || c == '\n' || c == '\t' || c == '\r')) c = _getc();	//一直吞空字符，直到读到结束标志或其他字符为止（这里结束标志也可能是四大空字符之一）
	if(c == '+' || c == '-') readexpression(endc, expr->nxt);	//如果是正负（加减）号就读下一个表达式
	else if(c == endc) c = _getc();	//终止符就再读一个字符走人
	else throw("CE: Unexpected character. ");	//不可能是别的字符，如果是就CE
}

int readjudge()
{
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
	if(c == 'l') {	//读取比教的类型，不符合6个类型之一的CE掉
		c = _getc();
		if(c == 't') {
			c = _getc();
			return 0;	//lt
		} else if(c == 'e') {
			c = _getc();
			return 2;	//le
		} else throw("CE: Unexpected character. ");
	} else if(c == 'g') {
		c = _getc();
		if(c == 't') {
			c = _getc();
			return 1;	//gt
		} else if(c == 'e') {
			c = _getc();
			return 3;	//ge
		} else throw("CE: Unexpected character. ");
	} else if(c == 'e') {
		c = _getc();
		if(c == 'q') {
			c = _getc();
			return 4;	//eq
		} else throw("CE: Unexpected character. ");
	} else if(c == 'n') {
		c = _getc();
		if(c == 'e') {
			c = _getc();
			if(c == 'q') {
				c = _getc();
				return 5;	//neq
			} else throw("CE: Unexpected character. ");
		} else throw("CE: Unexpected character. ");
	} else throw("CE: Unexpected character. ");
	c = _getc();
}

void readvars(Instruction *ins)	//读取vars
{
	ins->init = new Initer();
	Initer *init = ins->init;
	while(c != '}') {
		readiniter(init);
		init->nxt = new Initer();
		init = init->nxt;
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
	}
	ins->type = 0;
	c = _getc();
}

void readset(Instruction *ins)	//读取set
{
	ins->type = 1;
	readexpression(',', ins->exp1);	//以逗号为结束标志读取exp1
	readexpression('\n', ins->exp3); //以换行为结束标志读取exp2
}

void readyosoro(Instruction *ins)	//读取yosoro
{
	ins->type = 2;
	readexpression('\n', ins->exp1);	//以换行为结束标志读取exp1
}

void readihu(Instruction *ins)	//读取ihu
{
	ins->type = 3;
	ins->judgetype = readjudge();	//读取比较类型
	c = _getc();
	readexpression(',', ins->exp1);	//以逗号为结束标志读取exp1
	readexpression('\n', ins->exp2);	//以换行为结束标志读取exp2
	ins->subins = new Instruction();
	ReadInstruction('}', ins->subins);	//以有括号为结束标志读取subins 
}

void readhor(Instruction *ins)	//读取hor
{
	ins->type = 4;
	ins->judgetype = 2;	//比较类型天然为le
	readexpression(',', ins->exp1);	//以=为结束标志读取循环变量
	readexpression(',', ins->exp3);	//以t为结束标志读取初值
	readexpression('\n', ins->exp2);	//以换行为结束标志读取终止值
	ins->subins = new Instruction();
	ReadInstruction('}', ins->subins);
}

void readwhile(Instruction *ins)	//读取while
{
	readihu(ins);	//因为内部是相同的直接很赖皮的用ihu读入
	ins->type = 5;	//然后把类型改过来就行了
}

void ReadInstruction(char endc, Instruction *ins)
{
	while(c != endc) 
	{
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
		if(c == '{' || c == ':')	//指令
		{
			std::string opt;
			c = _getc();
			while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
			while(c >= 'a' && c <= 'z') { //获取指令名称
				opt.push_back(c);
				c = _getc();
			}
			if(c != ' ' && c != '\t' && c != '\n' && c != '\r') throw("CE: Unexpected character. ");	//不是以空字符结尾的直接CE
			
			if(opt == "vars")
				readvars(ins);
			else if(opt == "set")
				readset(ins);
			else if(opt == "yosoro")
				readyosoro(ins);
			else if(opt == "ihu")
				readihu(ins);
			else if(opt == "hor")
				readhor(ins);
			else if(opt == "while")
				readwhile(ins);
			else	//未定义的指令
				throw("CE: Unknow Instruciton. ");
				
			ins->nxt = new Instruction();
			ins = ins->nxt;
			
			while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
		} else {	//非法字符
			throw("CE: Unexpected character. ");
		}
	}
	c = _getc();
}

int main()
{
	c = _getc();	//先读一个字符
	Main = new Instruction();
	try {
		ReadInstruction(EOF, Main);	//以EOF为结束标志读取Main
		Run(Main);
		printf("\n");
	} catch (const char* e) {
		cerr << e << endl;
	}
	return 0;
}
```

---

## 作者：Zvelig1205 (赞：18)

# P3695 CYaRon！语

## 开始之前

本篇题解同步于我的个人博客。

[可能更好的阅读体验](https://www.cnblogs.com/adm-1223/p/16333702.html)

上次水了些小模拟之后感觉不能再颓废了，于是就来大模拟。

然后这个题花了我一个多星期 ![](//图.tk/h)

还是[最差解](https://www.luogu.com.cn/record/list?pid=P3695&user=&orderBy=1&status=&page=2) ![](//图.tk/h)

不过，为了纪念我的第 20 道紫题，纪念我这一周的努力，我还是想写篇题解，记录我的一点一滴。

## 大致思路

模拟题，都是根据题意直接模拟的（雾。

这个题呢，就适合分步完成。

## 关于变量

用的变量大都是汉语拼音或者缩写或者半缩写（比较好调）。

有些地方没加注释就可以直接读拼音理解含义。

## 成长过程

### 一 . 输出，变量，赋值

刚开始我是这么想的：

先把变量、数组和赋值、输出打完。

1. 输出

	直接将表达式的值计算出来输出即可。

1. 变量和数组

	用到了两个 map，用来映射 string 和 int 或者 array 之间的关系。

1. 赋值

	和输出差不多，将变量名储存下来，计算出后边表达式的值即可。

具体看[代码](https://www.luogu.com.cn/paste/s62a709y)。

显然这个 `js` 是不对的，没有判断减法，`:yosoro 2-1` 都是错的。

数组的处理也有些错误。

得了 20 分。

但我当时没在意，就去打 `ihu` 了。

### 二 .ihu

我对 `ihu` 想的很简单，没考虑循环的情况。

如果 `ihu` 合法，就顺序执行；否则，就将更深层数的读入，跳过。

层数的定义大概就是每遇到一个 `{` 层数 +1，遇到 `}` 层数 -1。

然后又小改了一下 `js`，完善了减法的维护。

[代码](https://www.luogu.com.cn/paste/ubt32mfe)

事实证明，我的 `ihu` 思路上没什么大错误。

30 分。

### 三 . 数组

之后我看了数据那张图。

就这个：

![](https://cdn.luogu.com.cn/upload/pic/4595.png)

“不对啊，应该是 50 吗？”

然后就开始调试数组。

我就发现 `js` 用递归的话，`ls` 是个全局变量，会被清空。

然后我就直接当数字计算了……

没考虑数组下标是变量的情况。

不过，50 分就这么到手了……

[代码](https://www.luogu.com.cn/paste/ywynn6dt)

### 四 .hor

从这开始，就开始有些恶心了。

因为要重复操作，顺序操作可能不好弄，所以这里选择了递归。

用了一个 `zhixing` 函数，将更深层数的操作储存下来。用循环递归处理。

但是因为是一些奇奇怪怪的原因，`main` 函数中的 `zhixing` 是以读入的形式执行的，而递归时则是以储存的形式执行的。

所以要有一些判断，将读入或是储存的代码统一起来。

[代码](https://www.luogu.com.cn/paste/lr0iznb1)


但这样只能执行单层循环，不能嵌套（不管是嵌套循环还是 ihu）。

而原因呢，就是因为如果循环之中嵌套循环，递归执行到下一次循环时，又会执行 `getline` 函数。

那么加一个判断条件，如果是第一次循环（严格来说是最外层循环），就将更深层次的存下来；否则就从之前储存的代码中找到要执行的语句。

[代码](https://www.luogu.com.cn/paste/ke154uvr)

关于 `duiy` 的用处，举一个简单的例子：

```CYaRon!
{ vars
	a:int
	b:int
}

{ hor a, 1, 2
	{ hor b, 1, 2
		:yosoro b
	}
}
```

不加 `duiy` 的输出：

```
1 2 0 1 2 0 
```

加 `duiy` 的输出：

```
1 2 1 2 
```

如果将循环执行的语句 **顺序** 输出的话，那么不加 `duiy` 的应该是这样的（仅 `hor` 循环）：

```
{ hor a, 1, 2
{ hor b, 1, 2
:yosoro b
}
{ hor b, 1, 2
:yosoro b
}
:yosoro b
{ hor b, 1, 2
:yosoro b
}
{ hor b, 1, 2
:yosoro b
}
:yosoro b
}
```

也就是说，循环结束之后又顺序执行了一遍循环体。

应该……不难理解吧。

感性理解一下吧。

然后就 60 分了。

这里的 `duiy` 统计比较浅显，没有考虑 `ihu` 的不成立时跳过和 `while` 语句。

### 五 .while

`ihu` 和 `hor` 打完之后，`while` 就很好打了。

因为 `while` 完全就是 `ihu` 和 `hor` 的结合体。

顺便又修改了一下 `js` 函数。

修复了之前说的数组下标是变量时的错误。

还完善了对于循环中的 `ihu` 的跳过处理。

[代码](https://www.luogu.com.cn/paste/otx0x5de)

可以发现，这时的 `zhixing` 函数有了返回值。

这是为了判断 `ihu` 是否需要跳过。

而且此时的 `duiy` 函数的统计方式也变成了由大括号直接统计，而不是通过 `hor` 统计。

交上之后，80 分了，两个 TLE。

### 六 .set

通过下载数据，可以发现，#6 的 `set` 的变量和数值之间没有空格，这就导致了我的处理出现奇奇怪怪的错误（我的处理是按照空格划分的）。

既然这样，反正 `set` 中的 `,` 是绝对有的，那么就根据这个 `,` 划分变量。

[AC Code](https://www.luogu.com.cn/paste/zq3qn1xp)

### 七 . 数组

“你的 `vector` 怎么实现的？”

“就直接用啊。”

“那它如果直接是一个 9？”

“嗯？哦，我先 `push_back` 了 1000 个 0。”

“那你？”

“好像是哦。”

虽然这个对话有些奇怪，但我们两个都 get 到了对方的意思。

于是我就把 `vector` 换成了 `int` 数组。

其实差不多（反正都是最差解）。

[AC Code](https://www.luogu.com.cn/paste/5kg1xp4p)

[含调试过程的代码](https://www.luogu.com.cn/paste/yh42ed75)

## 总结

个人感觉这种紫色的大模拟对于代码能力的锻炼还是很有用的。

除了过程有点折磨外，A 掉之后还是很开心的。

如果对于我的代码疑问，可以私信问我。

2022 年 noip 后就要退役了。退役前还是能回复的。

大学之后可能会是不是上洛谷或博客园看看。

如果觉得这篇题解写的还可以，请不要吝啬您的点赞。

## 广告

[博客园](https://www.cnblogs.com/adm-1223/)

---

## 作者：jyi2ya (赞：15)

这不是重复的做法。洛咕审题解好像判错了。

思路：CyaRon 转 Perl 后再运行。

这个题，好像是要我们设计一个新语言。所以我们可以写 23 行 Perl 程序完成这个任务。因为正则用的不是很熟练，所以不确定是是不是更短的实现。

```perl
$/ = undef;
my $code = <>;
$code = $code =~
s/#.*?\n/\n/gsr =~ s/{[^}]*vars.*?}//gsr =~
s/:yosoro(.*?)\n/print $1\nprint ' '\n/gsr =~ s/:set(.*?),(.*?)\n/$1 = $2\n/gsr;
$code = $code =~
s/([^a-z])lt([^a-z])/$1<$2/gsr =~ s/([^a-z])gt([^a-z])/$1>$2/gsr =~
s/([^a-z])le([^a-z])/$1<=$2/gsr =~ s/([^a-z])ge([^a-z])/$1>=$2/gsr =~
s/([^a-z])eq([^a-z])/$1==$2/gsr =~ s/([^a-z])neq([^a-z])/$1!=$2/gsr;
my $magic = '([^,\{\}]*),([^,\{\}]*),([^,\{\}\n]*)\n([^\}\{]*?)\}';
while ($code =~ m/ihu/ or $code =~ m/hor/ or $code =~ /while/) {
	$code =~ s/\{[^\{\}]*?ihu$magic/IF ($2 $1 $3) <%\n $4 %>\n/gs;
	$code =~ s/\{[^\{\}]*?hor$magic/FOR $1 ( $2 .. $3 ) <%\n $4 %>\n/gs;
	$code =~ s/\{[^\{\}]*?while$magic/WHILE ($2 $1 $3) <%\n $4 %>\n/gs;}
$code = $code =~ s/<%/{/gsr =~ s/%>/}/gsr;
for my $keyword (qw/print/) {
	$code =~ s/([^a-z])${keyword}([^a-z])/$1\U$keyword\E$2/gs; }
$code = $code =~
s/([^a-z\$])([a-z])/$1\$$2/gsr =~ s/([^0-9\'])([0-9]+)/$1'$2'/gsr;
for my $keyword (qw/if for while print while if for/) {
	$code =~ s/([^a-z])\U$keyword\E([^a-z])/$1$keyword$2/gs; }
$code = $code =~ s/\[/{/gsr =~ s/\]/}/gsr =~ s/\n/;\n/gsr;
eval $code;
```

这一坨代码看不得。把代码打散之后还是有一点可读性的。

基本思路是把 CYaRon 语言转成 Perl，然后再 eval 一下。

代码逻辑写在注释里了。如果有疑问，欢迎私信。

```perl

#!/usr/bin/perl

$/ = undef;
my $code = <>;

# 去掉注释
$code =~ s/#.*?\n/\n/gs;

# 去掉 vars 标签
$code =~ s/{[^}]*vars.*?}//gs;

# 处理 yosoro
$code =~ s/:yosoro(.*?)\n/print $1\nprint ' '\n/gs;

# 处理 set
$code =~ s/:set(.*?),(.*?)\n/$1 = $2\n/g;

# 转换逻辑操作符
$code =~ s/([^a-z])lt([^a-z])/$1<$2/gs;
$code =~ s/([^a-z])gt([^a-z])/$1>$2/gs;
$code =~ s/([^a-z])le([^a-z])/$1<=$2/gs;
$code =~ s/([^a-z])ge([^a-z])/$1>=$2/gs;
$code =~ s/([^a-z])eq([^a-z])/$1==$2/gs;
$code =~ s/([^a-z])neq([^a-z])/$1!=$2/gs;

# 代码块嵌套
while ($code =~ m/ihu/ or $code =~ m/hor/ or $code =~ /while/) {
	$code =~ s/\{[^\{\}]*?ihu([^,\{\}]*),([^,\{\}]*),([^,\{\}\n]*)\n([^\}\{]*?)\}/IF ($2 $1 $3) <%\n $4 %>\n/gs;
	$code =~ s/\{[^\{\}]*?hor([^,\{\}]*),([^,\{\}]*),([^,\{\}\n]*)\n([^\}\{]*?)\}/FOR $1 ( $2 .. $3 ) <%\n $4 %>\n/gs;
	$code =~ s/\{[^\{\}]*?while([^,\{\}]*),([^,\{\}]*),([^,\{\}\n]*)\n([^\}\{]*?)\}/WHILE ($2 $1 $3) <%\n $4 %>\n/gs;
}

$code =~ s/<%/{/g;
$code =~ s/%>/}/g;

# 保护关键字
for my $keyword (qw/print/) {
	$code =~ s/([^a-z])${keyword}([^a-z])/$1\U$keyword\E$2/gs;
}

# 给变量加上魔法
$code =~ s/([^a-z\$])([a-z])/$1\$$2/gs;

# 给数字加上魔法
$code =~ s/([^0-9\'])([0-9]+)/$1'$2'/gs;

# 转回关键字
for my $keyword (qw/if for while print while if for/) {
	$code =~ s/([^a-z])\U$keyword\E([^a-z])/$1$keyword$2/gs;
}

# 使用哈希，防止数组越界
$code =~ s/\[/{/gs;
$code =~ s/\]/}/gs;

# 加上分号
$code =~ s/\n/;\n/gs;

# --L-i-v-e--（bushi） 运行！
eval $code;

```

---

## 作者：159号程序员 (赞：14)

CyaRon!语，语言大模拟界的一颗明珠。

前置知识：

1. [解释执行与编译执行](https://www.luogu.com.cn/paste/ktllgem8)
2. [离线与在线](https://www.luogu.com.cn/paste/u3gl9jc2)

在此之前，我们需要画出流程图来梳理分析此题：

![](https://cdn.luogu.com.cn/upload/image_hosting/bjay7fng.png)

画好流程图后（我的可能不太标准），就可以一步步的编程了。

大事化小，小事化了，我们把问题拆分来看：

1. 初始化
2. 读入
3. 各种指令
4. 输出

初始化：

```cpp
int expression();
int statements();
void skip_statements();
int var_declarations();
void if_statement();
int for_statement();
void while_statement();
/* 提前定义函数 */

enum tk_type {TK_WRONG, TK_END, TK_ID, TK_NUM, TK_LF_BRACE, TK_RT_BRACE, TK_COLON, TK_COMMENT, TK_LF_BRACKET, TK_RT_BRACKET, TK_COMMA, TK_RANGE, TK_NL, TK_OP_PLUS, TK_OP_MINUS};
enum op_type {OP_PLUS, OP_MINUS};
enum st_type {ST_DECL, ST_ASSIGN, ST_OUTPUT, ST_IF, ST_FOR, ST_WHILE};
/* 枚举类型方便理解 */

string in;                          // 源程序
int cur;                            // 当前位置
string strToken;                    // 用于保存函数get_token()的结果（标识符）
long numToken;                      // 用于保存函数get_token()的结果（常数） 
st_type curStType;                  // 当前处理的语句类型

vector< pair <string, int> > vars;  // 保存所有变量的值
                                    // 数组变量被看成为多个变量
```

这里需要注意的是 `enum`，`enum` 是枚举类型，比如 `TK_WRONG` 为 0，想更深入了解的同学请看[link](https://baike.baidu.com/item/%E6%9E%9A%E4%B8%BE%E7%B1%BB%E5%9E%8B/2978296?fr=aladdin)。

我们把 `in` 作为输入的字符串，将其的Token找出来后存到 `strToken` 和 `numToken` 里，如果为定义变量的话，把变量存到 `vars` 里。

输入：

```cpp
// 读入程序
    char c;
    while ((c = getchar()) != EOF) //离线读入直到EOF
    {
        in.push_back(c);
    }

    cur = 0;
    statements(); //进行语句列表的识别
```

读入需要用 `getchar()`，方便判断EOF，在win系统中打出EOF可以用  、`Ctrl+Z`，Linux下需要用 `Ctrl+D`。

执行指令：

```cpp
/* 读入并执行语句序列 */
int statements()
{
    tk_type t = get_token();

    while(t != TK_END && t != TK_RT_BRACE) 
    {
        if (t == TK_LF_BRACE) // 复合语句
        {                  
            if ((t = get_token()) != TK_ID)
            {
                cout << "Parse error!\n";
                return 0;
            }

            if (strToken == "vars")            // 变量声明语句 {vars x:type y:type ...}
            {
                curStType = ST_DECL;
                var_declarations();
            }
            else if (strToken == "ihu")            // if语句 {ihu cond statements}
            {
                curStType = ST_IF;
                if_statement();
            }
            else if (strToken == "hor")            // for语句 {hor i, lb, ub statements}
            {
                curStType = ST_FOR;
                for_statement();
            }
            else if (strToken == "while")          // while语句 {while cond statements}
            {
                curStType = ST_WHILE;
                while_statement();
            }
            else 
            {                                   // otherwise
                cout << "Parse error!\n";
                return 0;
            }
        }
        else if (t == TK_COLON) // 简单语句
        {                     
            assert((t = get_token()) == TK_ID);

            if (strToken == "set") // :set varname, varvalue
            { 
                curStType = ST_ASSIGN;
                // varname
                t = get_token();
                int idx = find_by_name(strToken);
                if (idx == -1) 
                {
                    cout << "Variable not found!\n"; 
                    return 0;
                }
                // comma
                assert( (t = get_token()) == TK_COMMA);
                // expression
                int value = expression();
                vars[idx].second = value; 
            }
            else if (strToken == "yosoro" ) // :yosoro statement
            {
                curStType = ST_OUTPUT;
                int value = expression(); 
                cout << value << " "; 
            }
            else 
            {
                cout << "Parse error!\n";
                return 0;
            } 
        }
        else if (t == TK_NL);        // 空语句           
        else if (t == TK_COMMENT) // 注释
        {     
            while ( (t = get_token()) != TK_NL) {}
        }
        else 
        {
            cout << "Parse error!\n" ;
            return 0;
        }

        t = get_token();
    }

    return 0;
}
```

`statements` 就像是一个中央处理器，读入并识别指令后去寻找相应的函数。

我们把指令分为简单指令和复合指令，复合指令（如 `vars`）需要去相应的函数，简单指令（如 `yosoro`）可以直接执行。（详情见代码）

```cpp
tk_type get_token()
{
    char c;
    tk_type type;

    // 初始化
    strToken.clear();
    numToken = 0;

    // 去掉左边的空格
    while (cur < in.length()) 
    {
        if(in.at(cur) == ' ') ++cur;
        else break;
    }

    // EOF
    if (cur == in.length()) 
    {
        type = TK_END;                      // end of file
        return type;
    } 

    c = in.at(cur);
    if (is_numeric(c)) 
    {                    // 常数TOKEN
        type = TK_NUM;
        numToken = (int) (c - '0'); 
        c = in.at(++cur);
        while (is_numeric(c)) 
        {
            numToken *= 10; 
            numToken += (int) (c-'0'); 
            c = in.at(++cur);
        } 

        if (is_letter(c)) // 111a 是非法标识符
        {                 
            type = TK_WRONG;
            cout << "Parse error!\n";
            exit(0);
        }
    }
    else if (is_letter(c)) // 标识符TOKEN
    {                
        type = TK_ID;
        strToken.push_back(c);
        c = in.at(++cur);
        while (is_letter(c)) {
            strToken.push_back(c);
            c = in.at(++cur);
        }
        if (is_numeric(c)) // 标识符只包含英文字符
        {                
            type = TK_WRONG;
            cout << "Parse error!\n";
            exit(0);
        }

        /* 数组读 */
        if(curStType != ST_DECL && c == '[')
        {
            string ref = strToken;
            ref.push_back('['), ++cur;
            ref.append(m_to_string(expression()) );     
            // 注意：expression() 函数中会更新 cur, strToken 等全局变量
            ref.push_back(']'); 
            strToken = ref;
        } 
    }
    else // 特殊TOKEN
    {                                  
        switch (c)
        {
        case ',':                           // 逗号
            type = TK_COMMA;
            break;
        case '.':                           // 范围符号
            if ((c = in.at(++cur)) != '.') {
                type = TK_WRONG;
                cout << "Parse error!\n";
                exit(0);
            }
            type = TK_RANGE;
            break;
        case ':':                           // 冒号
            type = TK_COLON;
            break;
        case '#':
            type = TK_COMMENT;
            break;
        case '{':
            type = TK_LF_BRACE;
            break;
        case '}':
            type = TK_RT_BRACE;
            break; 
        case '[':
            type = TK_LF_BRACKET;
            break;
        case ']':
            type = TK_RT_BRACKET;
            break; 
        case '+':
            type = TK_OP_PLUS;
            break;
        case '-':
            type = TK_OP_MINUS;
            break;
        case '\n':
            type = TK_NL;
            break;
        default:
            break;
        }

        ++cur;                                  // 指针往前挪动一格位置
    }

    return type;
}
```

`get_token` 函数会识别每一个token，并且做出返回，token有：

`vars`，`ihu`，`hor`，`while`，`常量`，`变量名（字符串）`，`符号（如+号）`，`换行符（\n）`，`EOF`，`ERROR`。

在读取token时，需要把前面的空格去掉，如 `[space]:` 需要变成 `:`等。

去掉空格后，我们可以把token分成4个部分：

常数、字符、符号、ERROR。

常数token需要把该常数进行数位拆分后压入字符串，字符同理。

特别的，如果读完字符token后出现了`[`，且该token不为 `vars`，那么就代表出现了 `a[i]` 这样的数组读，需要进行特殊的压入处理。（详情见代码）

如果为符号，利用 `switch` 给符号token分类。

如果非以上三种情况，就报错。（即使输入保证正确，但是仍需要进行CE处理）

还有，如果在数字token中读入到了字符，或在字符token中读到了数字，则全部报错。

```cpp
int var_declarations()
{
    tk_type t;
    string varname, array_varname; 
    pair<long, long> range;                          // array range
    long i;                          

    while ((t = get_token()) != TK_RT_BRACE) 
    {
        if (t == TK_NL) continue; 

        assert(t == TK_ID);                         // var name
        varname = strToken;

        assert( (t = get_token()) == TK_COLON);      // :

        assert( (t = get_token()) == TK_ID);         // var type
        if (strToken == "array") 
        {
            assert((t = get_token()) == TK_LF_BRACKET);

            assert((t = get_token()) == TK_ID);
            if (strToken != "int") 
            {
                cout << "Parse error!\n";
                return 0;
            }

            assert((t = get_token()) == TK_COMMA);

            range = get_array_range();
            for (i=range.first; i<=range.second; i++)
            {
                array_varname = varname;
                array_varname += "[" + m_to_string(i) + "]";
                vars.push_back(make_pair(array_varname, 0));
            }

            assert( (t = get_token()) == TK_RT_BRACKET);
        }
        else if (strToken == "int") 
        {
            vars.push_back(make_pair(varname, 0));
        }
        else 
        {
            cout << "Only integer type supported!\n";
            return 0; 
        }

    }

    return 0; 
} 
```

定义变量时，首先我们需要过滤空行，避免不必要的CE。

我们还可以利用 `assert` 函数进行判断（`assert(x)`，如果`x`为假，抛出错误。想拓展知识面的同学点击[lilnk](https://baike.baidu.com/item/assert/10931289?fr=aladdin)），虽然数据保证不会出错，但是为了保险起见。

如果定义的是一个数组，我们需要得到上下界，可以写一个 `get_array_range()` 函数，由于比较简单，故不放出来了。

如果定义的是普通变量，直接压入向量 `vars` 即可。

如果以上均不是，则报错。

```cpp
void if_statement()
{    
    tk_type t;
    bool cond;
    
    // 读入条件表达式并赋值
    cond = condition();

    // 根据条件赋值选择是否执行后面的语句
    if (cond) 
    {
        statements(); 
    }
    else 
    {
        skip_statements();
    }
}
```

ihu语句比较简单，我们得到表达式的值（函数简单，不放出来了），再去执行，如果为假，直接 `skip` 到下一个指令。

```cpp
int for_statement()
{
    tk_type t;
    string iter_name;                   // 循环变量名
    int iter;                           // 循环变量在vars的存储位置
    int lb, ub;
    int loop_head;

    // 读入循环变量名
    assert((t = get_token()) == TK_ID);
    iter_name = strToken;
    assert(( t = get_token() ) == TK_COMMA);
    iter = find_by_name(iter_name);
    if (iter == -1) 
    {
        cout << "Variable not found!\n"; 
        return 0;
    }

    // 读入循环变量初始值，以逗号结束
    lb = expression();

    // 读入循环变量结束值，以换行结束
    ub = expression();

    // 记录循环头位置
    loop_head = cur;

    for (int i=lb; i<=ub; i++) 
    {
        vars[iter].second = i; 
        cur = loop_head;
        statements();
    }

    return 0;
}
```

hor语句也比较简单，从变量向量里找到循环变量，模拟for即可。

但是我们需要记录下循环头，方便后面持续的跳转循环。

```cpp
void while_statement()
{
    tk_type t;
    bool cond;
    int loop_head; 
    
    // 记录循环头位置
    loop_head = cur;

    // 根据条件赋值选择是否执行后面的语句
    while (condition()) 
    {
        statements(); 
        cur = loop_head;
    }

    // 跳转到循环结束的位置
    skip_statements();

    return;
}
```

while和hor差不多，只是循环头的位置发生了改变，同时需要判断表达式是否成立。

完整程序比较长（515行），故不放出来了，需要的同学来[link](https://www.luogu.com.cn/paste/b4honglk)，同时希望大家有自己的思考。

题外话：大模拟其实并不难，只需要认真分析，大事化小，小事化了！

---

## 作者：Hope2075 (赞：10)

# 我偏不写解释器

# 下面是CYaRon!语“编译”器

这题真的很duliu，超过了"猪国杀"

用了我一星期时间，当然是断断续续完成的

最后提交开始得70分(2RE+1WA,RE原因见下面)，然后下载了3次数据就A了 ~~（雾~~

我的思路比较特殊：把程序“编译”成伪汇编命令，然后执行

一共用到4个数据寄存器，编号从A到D

由于某些原因，建议将程序全部读入再处理

注意区分下面关于栈的操作对哪个栈进行处理

## 第一步：“汇编”命令表

每条命令有两个参数type(含3个子参数)和num（可以为0）

第一个参数表示操作的寄存器，从最高有效位开始排序

比如0x123就是对B和C操作，结果存到D中

除了移动操作，下面给出描述

这是我定义的命令列表：
```
nul
	空指令
add
	将寄存器1与2相加放在3里
arc
	将寄存器1取相反数后放在3里
jif
	如果寄存器1不是0，就跳转到num行
jmp
	跳转到第num行
mov
	根据type的最高有效位决定具体操作
    	0:将寄存器1的数复制到寄存器2中
    	1:将寄存器1所指向内存地址中的数复制到寄存器2中
        即:读取内存
        2:将寄存器1的数复制到寄存器2所指向的内存地址中
        即:写入内存
        3:将寄存器2设为num
        type形式应类似0x301,中间一位无影响
put
	输出寄存器1中的数字
geq
leq
grt
les
equ
neq
	对寄存器1和2进行比较，结果存到寄存器3中
push
	将ABC压入栈，对D不执行操作
pop
	从栈顶弹出ABC，对D不执行操作
hlt
	结束程序
```

然后就可以开始写编译器了

## 第二步：变量

首先处理变量的地址，其中loadvar只处理定义内容，由variable的构造函数分配内存

注意：不一定有变量定义

对于单个变量，只需要在内存中分配最靠后的一个地址就行

对于数组，我先计算出下标为0对应的内存地址p（可能越界），然后在内存中分配相应大小的内存，在使用时只要取出p，加上下标，然后取出内存就可以

为了省事，我将字符串转成了数字

根据题目数据范围，可以用long long存，而且能保证不同变量对应不同的数字

## 第三步：表达式

题目中需要大量处理表达式（包括赋值操作的被操作数）

所以先弄表达式读取

对于表达式，我分为两类：传值和传址

区别就是，最后一步操作是否执行取内存操作

我写的calc::build(type)会从当前行开始，编译获得表达式内容的一段命令，保证只会改变寄存器D，最后数值或地址在寄存器D中

我的实现是先建表达式树，然后dfs一遍，dfs时根据情况编译出相应命令

这题只有加减，所以不需要考虑优先级问题

然后对于取下标操作，可以看做特殊的运算，处理时把```'['```当作运算符后面跟括号，```']'```当做普通括号

具体进行时的操作可能略有区别

建表达式树的时候，维护一个栈，每当能够合并栈顶的时候，就把运算符作为临时根节点，两边数作为左右儿子，然后把运算符对应的树压栈

遇到括号就把括号扔掉，两个括号中间部分取出，压栈

如果遇到作为负号的```'-'```，特点是前面是负号或者没有任何东西，就把影响到的点打相反数标记

结束建树条件是出现了非法字符，比如逗号和大括号

dfs时，每当进入一个节点，先编译压栈命令

如果是数字，则编译一条赋值命令

如果是变量，根据是否取地址讨论

如果是运算，则递归处理左右儿子，每处理完一半就把得到的结果移到另一个寄存器中，然后对两个寄存器执行相应操作。如果有翻转标记，就在最后编译一条取相反数命令

将要离开节点时，编译一条弹栈命令

然后就可以继续了

## 第四步：yosoro&set

只要把后面的表达式对应命令编译出来，然后编译几条移动或输出命令就可以了

## 第五步：条件语句

这里需要用到条件转移命令，但是命令转移到的位置在开始并不知道，下面有处理方法

首先记录操作类型

然后把被比较的两个表达式命令编译出来，再编译一条比较命令和条件转移命令（转移到的行数留空），把条件转移命令所在行数压栈

当遇到条件语句终止时，把刚才被压入栈的那个行数取出，转移行数就可以设置了

我的代码中命令和要求的操作是反着的，原因请根据命令列表自行思考

## 第六步：for循环语句

如果你写的是解释型代码的话，可能这个操作比while简单

但是如果编译就复杂了

理一下思路，执行这种循环的顺序：

```
取出i的地址
取出a的数值
将i设为对应数值（一条命令）
取出i的数值 #1
取出b的数值
比较i和b的值并转移(#2)（若干条命令）
（循环体）
取出i的地址
将i加1（若干条命令）
转移到#1
#2（跳出循环）
```
在处理时，需要多次取出同一表达式，只要记录表达式代码开始的位置，然后重新编译就行

压栈时，把语句终止段处理所需信息也一并压栈

## 第六步：while循环语句

和if语句有相似之处

还是需要理清思路
```
取出a和b的值 #1
比较并转移(#2)
（循环体）
转移到#1
#2（跳出循环）
```
然后就和上面类似了
## 第七步：运行

记录当前行，根据每种命令的规定执行相应操作，这一步就很简单了

## 代码

包含一些调试信息，把debug设为true就能看到

也有一些调试操作被注释掉了，可以参考一下

**一定要完成一部分并确认正确后再进行下一部分**

CE函数主要也是调试用的，如果出现问题，会RE而不是WA


```cpp
#include<cstdio>
#include<iostream>
//取出"type"的对应位置
#define low(x) (x&0x00f)
#define mid(x) ((x&0x0f0)>>4)
#define high(x) ((x&0xf00)>>8)
using namespace std;
const bool debug=false;
namespace cst{
//记录关键字的哈希值
	#define cst(x,y) const long long x=y;
	cst(vars,434260);
	cst(val,6959);
	cst(arr,898909);
	cst(yosoro,367079703);
	cst(set,14006);
	cst(iho,6798);
	cst(lt,344);
	cst(gt,209);
	cst(le,329);
	cst(ge,194);
	cst(_eq,152);
	cst(_neq,10358);
	cst(hor,6255);
	cst(loop,12387497);
	#undef cst
}

namespace com{
//在编译时直接调用
//下面的注释不一定对，请无视
#define nul 0
//nothing
#define add 1
//c=a+b
#define arc 2
//c=-a
#define jif 3
//if a!=0 goto c
#define jmp 4
//goto c
#define mov 5
//1: reg=*mem
//2: reg=const
//3: *mem(A)=reg
//4: reg=reg
#define put 6
//print a
#define geq 7
//c=a>=b
#define leq 8
//c=a<=b
#define grt 9
//c=a>b
#define les 11
//c=a<b
#define equ 12
//c=a==b
#define neq 13
//c=a!=b
#define push 14
//push a,b,c
#define pop 15
//pop c,b,a
#define hlt 16
//stop
}
//存源程序
char cpp[500000];
int lst;
//这些是一些简单函数
long long hash(char *c){
	long long ans=0;
	while(*c){
		ans*=27;
		ans+=(*c-'a'+1);
	}
	return ans;
}
inline bool isletter(char c){
	return c>='a'&&c<='z';
}
inline bool isdigit(char c){
	return c>='0'&&c<='9';
}


void CE(const char *res){
	printf("Complie Error\n%s\nAt char %d\n",res,lst);
	throw(1);
}

void pass(){
	
	while(1){
		while(cpp[lst]==' '||cpp[lst]=='\n'||cpp[lst]=='\r'||cpp[lst]=='\t')lst++;
		if(cpp[lst]=='#'){
			while(cpp[lst]!='\n')lst++;
			lst++;
		}else{
			break;
		}
	}
	
}
long long getword(){
	pass();
	long long ans=0;
	if(!isletter(cpp[lst]))CE("Invailed letter");
	while(isletter(cpp[lst])){
		ans*=27;
		ans+=(cpp[lst]-'a'+1);
		lst++;
	}
	return ans;
}
long long getnum(){
	pass();
	long long ans=0;
	int f=1;
	if(cpp[lst]=='-')f=-1,lst++;
	if(!isdigit(cpp[lst]))CE("Invailed number");
	while(isdigit(cpp[lst])){
		ans*=10;
		ans+=(cpp[lst]-'0');
		lst++;
	}
	return ans*f;
}

//命令
struct command{
	char com;
	int type,num;
};
int reg[4],cur;//registers
command exe[10000];
int last;
//这个是编译一条命令
int comm(int opt,int type,int num){
	exe[last]=(command){(char)opt,type,num};
	last++;
	return last-1;
}
int mem[60000];
int memsz;

//处理变量
struct variable{
	long long name;
	int beg,end;
	int p;
	variable(long long _name,int _beg,int _end){
		if(debug){cout<<"define "<<_name<<" at mem "<<memsz
			<<" to "<<memsz+_end-_beg<<endl;
			cout<<"array from "<<_beg<<" to "<<_end<<endl;
			
		}
		name=_name;
		beg=_beg;
		end=_end;
		p=memsz-_beg;
		memsz+=(_end-_beg+1);
	}
	variable(long long _name){
		if(debug)cout<<"define "<<_name<<" at mem "<<memsz<<endl;
		name=_name;
		beg=0;
		end=0;
		p=memsz;
		memsz++;
	}
	variable(){}
};
variable vlist[100];
int vcnt;
void loadvar(){
	long long name,type,beg,end;
	pass();
	if(cpp[lst]!='{'){
		lst++;
		pass();
		name=getword();
		if(name!=cst::vars){
			lst=0;
			return;
		}else{
			CE("Unknown Error");
		}
	}
	lst++;
	pass();
	
	name=getword();
	if(name!=cst::vars)CE("Invailed variable define begin");
	pass();
	while(1){
		if(cpp[lst]=='}'){
			lst++;
			break;
		}
		
		name=getword();
		pass();
		
		if(cpp[lst]!=':')CE("Invailed variable define begin");
		lst++;
		pass();
		
		type=getword();
		pass();
		
		if(type==cst::val){
			vlist[vcnt++]=variable(name);
		}else if(type==cst::arr){
			
			if(cpp[lst]!='[')CE("Invailed array begin");
			lst++;
			pass();
			
			type=getword();
			if(type!=cst::val)CE("Invailed array type");
			pass();
			
			if(cpp[lst]!=',')CE("Invailed array define");
			lst++;
			pass();
			
			beg=getnum();
			pass();
			
			if(cpp[lst]!='.')CE("Invailed array range");
			lst++;
			if(cpp[lst]!='.')CE("Invailed array range");
			lst++;
			pass();
			
			end=getnum();
			pass();
			
			if(cpp[lst]!=']')CE("Invailed array end");
			lst++;
			pass();
			
			vlist[vcnt++]=variable(name,beg,end);
		}else{
			CE("Invailed variable type");
		}
	}
		
}


//这部分是编译过程
int stack[60000],top;
int getmem(long long name){
//获得某个变量的地址
	for(int i=0;i<vcnt;i++){
		if(name==vlist[i].name)return vlist[i].p;
	}
	CE("Variable not found");
	return -1;
}
//建表达式树
namespace calc{
	struct node{
		node *lcd,*rcd;
		node *pa;
		char type;
		long long num;
		bool rev;
        //dfs并编译命令
		void dfs(bool addr){
			if(type=='d')CE("Invailed operator");
			if(type=='p')CE("Invailed parter");
			if(type=='n'){
				if(addr)CE("Attemt to index a number");
				comm(mov,0x303,num);
				if(rev){
					comm(arc,0x33,0);
				}
				return;
			}
			if(type=='v'){
				if(addr){
					comm(mov,0x303,getmem(num));
				}else{
					comm(mov,0x303,getmem(num));
					comm(mov,0x133,0);
				}
				if(rev){
					comm(arc,0x33,0);
				}
				return;
			}
			if(type=='o'){
				if(addr&&num=='['){
					comm(push,0,0);
					lcd->dfs(1);
					comm(mov,0x030,0);
					rcd->dfs(0);
					comm(mov,0x031,0);
					comm(add,0x013,0);
					comm(pop,0,0);
					return;
					//comm(mov,0x303,0);
				}
				if(addr)CE("Attemt to index a number");
				comm(push,0,0);
				if(num=='['){
					lcd->dfs(1);
					comm(mov,0x030,0);
					rcd->dfs(0);
					comm(mov,0x031,0);
					comm(add,0x013,0);
					comm(mov,0x133,0);
				}else if(num=='+'){
					lcd->dfs(0);
					comm(mov,0x030,0);
					rcd->dfs(0);
					comm(mov,0x031,0);
					comm(add,0x013,0);
				}else if(num=='-'){
					lcd->dfs(0);
					comm(mov,0x030,0);
					rcd->dfs(0);
					comm(mov,0x031,0);
					comm(arc,0x11,0);
					comm(add,0x013,0);
				}
				if(rev){
					comm(arc,0x33,0);
				}
				comm(pop,0,0);
			}
		}
	};
	node mem[4000];int cnt;
	node *get(){
		return mem+(++cnt);
	}
	node *st[4000];int top;
    //将栈顶能处理部分处理掉
	void calc(){
		node *l,*m,*r;
		while(1){
			if(top==0)CE("Unknown Error");
			else if(top==1)break;
			else if(top==2){
				if(st[top-1]->type=='p'){
					if(st[top-1]->num!='['&&st[top-1]->num!='(')CE("Dup parter");
					break;
				}
				if(st[top-1]->type=='d')break;
				r=st[--top];
				if(st[top-1]->type=='d'){
					m=st[--top];
					if(m->num=='-')r->rev=!r->rev;
					st[top++]=r;
					break;
				}
				if(st[top-1]->type=='p'){
					st[top++]=r;
					break;
				}
				CE("Invailed number or variable");
			}else{
				if(st[top-1]->type=='d')break;
				if(st[top-1]->type=='p'){
					if(st[top-1]->num==']'){
						r=st[--top];
						if(st[top-1]->type=='d')CE("Invailed operator");
						if(st[top-1]->type=='p')CE("Invailed parter");
						m=st[--top];
						if(st[top-1]->type=='d'){
							CE("Invailed operator");
						}
						if(st[top-1]->type=='p'){
							if(st[top-1]->num!='[')CE("Invailed parter");
							l=st[--top];
							r=m;m=l;
							if(top==0)CE("Invailed index of NULL");
							if(st[top-1]->type!='v'){
								if(st[top-1]->type=='d')CE("Invailed operator");
								if(st[top-1]->type=='p')CE("Invailed parter");
								CE("Invailed number or variable");
							}
							l=st[--top];
							l->pa=m;
							r->pa=m;
							m->lcd=l;
							m->rcd=r;
							m->type='o';
							st[top++]=m;
							continue;
						}
						CE("Invailed number or variable");
					}
					if(st[top-1]->num==')'){
						r=st[--top];
						if(st[top-1]->type=='d')CE("Invailed operator");
						if(st[top-1]->type=='p')CE("Invailed parter");
						m=st[--top];
						if(st[top-1]->type=='d'){
							CE("Invailed operator");
						}
						if(st[top-1]->type=='p'){
							if(st[top-1]->num!='(')CE("Invailed parter");
							l=st[--top];
							st[top++]=m;
							continue;
						}
						CE("Invailed number or variable");
					}
					break;
				}
			}
			r=st[--top];
			if(st[top-1]->type=='p'){
				if(st[top-1]->num!='['&&st[top-1]->num!='(')CE("Dup parter");
				st[top++]=r;
				break;
			}
			if(st[top-1]->type=='d'){
				m=st[--top];
				if(st[top-1]->type=='d'||st[top-1]->type=='p'){
					if(m->num=='-'){
						r->rev=!r->rev;
					}
					st[top++]=r;
					continue;
				}
				l=st[--top];
				l->pa=m;
				r->pa=m;
				m->lcd=l;
				m->rcd=r;
				m->type='o';
				st[top++]=m;
				continue;
			}
			CE("Invailed number or variable");
		}
	}
    //主过程
	void build(bool addr){
		top=0;
		long long p;
		node *cur;
		while(1){
			pass();
			if(cpp[lst]=='{'||cpp[lst]=='}'||cpp[lst]==':'||cpp[lst]==','||cpp[lst]==0||cpp[lst]=='#')break;
			else if(isdigit(cpp[lst])){
				p=getnum();
				cur=get();
				cur->type='n';
				cur->num=p;
				st[top++]=cur;
			}else if(isletter(cpp[lst])){
				p=getword();
				cur=get();
				cur->type='v';
				cur->num=p;
				st[top++]=cur;
				pass();
				if(cpp[lst]=='['){
					lst++;
					cur=get();
					cur->type='p';
					cur->num='[';
					st[top++]=cur;
				}
			}else if(cpp[lst]=='+'||cpp[lst]=='-'){
				cur=get();
				cur->type='d';
				cur->num=cpp[lst];
				st[top++]=cur;
				lst++;
			}else if(cpp[lst]=='('||cpp[lst]=='['||cpp[lst]==')'||cpp[lst]==']'){
				cur=get();
				cur->type='p';
				cur->num=cpp[lst];
				st[top++]=cur;
				lst++;
			}else{
				CE("Invailed symbol");
			}
			calc();
		}
		if(top!=1)CE("Unknown Error");
		if(st[0]->type=='p')CE("Invailed parter");
		if(st[0]->type=='d')CE("Invailed operator");
		st[0]->dfs(addr);
	}
}
//正式编译
void complie(){
	int p1,p2,p3,p4;
	long long com;
	while(cpp[lst]){
		pass();
		if(cpp[lst]==':'){
        //如果是命令
			lst++;
			pass();
			com=getword();
			switch(com){
				case cst::yosoro:
					pass();
					calc::build(0);
					comm(put,0x3,0);
					break;
				case cst::set:
					pass();
					calc::build(1);
					comm(mov,0x030,0);
					pass();
					lst++;
					pass();
					calc::build(0);
					comm(mov,0x031,0);
					comm(mov,0x210,0);
					break;
					
			}
		}else if(cpp[lst]=='{'){
        //否则是控制语句
			lst++;
			com=getword();
			
			switch(com){
				case cst::iho:
					pass();
					com=getword();
					pass();
					if(cpp[lst]!=',')CE("Invailed symbol");
					lst++;
					pass();
					calc::build(0);
					comm(mov,0x030,0);
					pass();
					if(cpp[lst]!=',')CE("Invailed symbol");
					lst++;
					pass();
					calc::build(0);
					comm(mov,0x031,0);
					
					switch(com){
						case cst::ge:
							comm(les,0x013,0);
							break;
						case cst::le:
							comm(grt,0x013,0);
							break;
						case cst::_eq:
							comm(neq,0x013,0);
							break;
						case cst::_neq:
							comm(equ,0x013,0);
							break;
						case cst::gt:
							comm(leq,0x013,0);
							break;
						case cst::lt:
							comm(geq,0x013,0);
							break;
					}
					stack[top++]=comm(jif,0x3,-1);
					stack[top++]=0;
					break;
				case cst::hor:
					
					
					pass();
					p1=lst;
					calc::build(1);
					comm(mov,0x030,0);
					
					pass();
					if(cpp[lst]!=',')CE("Invailed symbol");
					lst++;
					pass();
					calc::build(0);
					comm(mov,0x230,0);
					
					stack[top++]=last;
					
					pass();
					if(cpp[lst]!=',')CE("Invailed symbol");
					lst++;
					pass();
					p2=lst;
					
					lst=p1;
					calc::build(0);
					comm(mov,0x030,0);
					
					lst=p2;
					calc::build(0);
					comm(grt,0x031,0);
					stack[top++]=comm(jif,0x1,-1);
					
					stack[top++]=p1;
					stack[top++]=1;
					break;
				case cst::loop:
					
					pass();
					com=getword();
					pass();
					if(cpp[lst]!=',')CE("Invailed symbol");
					lst++;
					
					pass();
					stack[top++]=last;
					calc::build(0);
					comm(mov,0x030,0);
					pass();
					if(cpp[lst]!=',')CE("Invailed symbol");
					lst++;
					
					pass();
					calc::build(0);
					comm(mov,0x031,0);
					switch(com){
						case cst::ge:
							comm(les,0x013,0);
							break;
						case cst::le:
							comm(grt,0x013,0);
							break;
						case cst::_eq:
							comm(neq,0x013,0);
							break;
						case cst::_neq:
							comm(equ,0x013,0);
							break;
						case cst::gt:
							comm(leq,0x013,0);
							break;
						case cst::lt:
							comm(geq,0x013,0);
							break;
					}
					stack[top++]=comm(jif,0x3,-1);
					stack[top++]=2;
					break;
			}
			pass();
			
		}else if(cpp[lst]=='}'){
        //控制语句结束
			lst++;
			com=stack[--top];
			switch(com){
				case 0:
					com=stack[--top];
					exe[com].num=last;
					break;
				case 1:
					p1=lst;
					lst=stack[--top];
					p2=stack[--top];
					p3=stack[--top];
					calc::build(1);
					comm(mov,0x300,1);
					comm(mov,0x131,0);
					comm(add,0x101,0);
					comm(mov,0x213,0);
					comm(jmp,0x0,p3);
					exe[p2].num=last;
					lst=p1;
					break;
				case 2:
					p1=stack[--top];
					p2=stack[--top];
					comm(jmp,0x0,p2);
					exe[p1].num=last;
					break;
			}
			pass();
		}else{
			CE("Invailed command");
		}
	}
	comm(hlt,0,0);
}
//可以运行了
void run(){
	cur=0;
	command c;
	int tmp;
	while(1){
		c=exe[cur];
		switch(c.com){
        //只要把命令对应操作敲出来就可以
			case nul:
				cur++;
				break;
			case add:
				if(debug)cout<<"add "<<(char)('A'+high(c.type))<<"+"
					<<(char)('A'+mid(c.type))
					<<" to "<<(char)('A'+low(c.type))<<endl;
				tmp=reg[high(c.type)];
				tmp+=reg[mid(c.type)];
				reg[low(c.type)]=tmp;
				cur++;
				break;
			case equ:
				tmp=reg[high(c.type)]==reg[mid(c.type)];
				reg[low(c.type)]=tmp;
				cur++;
				break;
			case neq:
				tmp=reg[high(c.type)]!=reg[mid(c.type)];
				reg[low(c.type)]=tmp;
				cur++;
				break;
			case geq:
				tmp=reg[high(c.type)]>=reg[mid(c.type)];
				reg[low(c.type)]=tmp;
				cur++;
				break;
			case leq:
				tmp=reg[high(c.type)]<=reg[mid(c.type)];
				reg[low(c.type)]=tmp;
				cur++;
				break;
			case grt:
				tmp=reg[high(c.type)]>reg[mid(c.type)];
				reg[low(c.type)]=tmp;
				cur++;
				break;
			case les:
				tmp=reg[high(c.type)]<reg[mid(c.type)];
				reg[low(c.type)]=tmp;
				cur++;
				break;
			case jif:
				tmp=reg[low(c.type)];
				if(tmp)cur=c.num;
				else cur++;
				break;
			case jmp:
				cur=c.num;
				break;
			case arc:
				tmp=reg[mid(c.type)];
				reg[low(c.type)]=-tmp;
				cur++;
				break;
			case mov:
				switch(high(c.type)){
					case 0:
						if(debug)cout<<"mov "<<(char)('A'+mid(c.type))<<" to "
							<<(char)('A'+low(c.type))<<endl;
						tmp=reg[mid(c.type)];
						reg[low(c.type)]=tmp;
						
						break;
					case 1:
						tmp=mem[reg[mid(c.type)]];
						if(debug)cout<<"mov &"<<(char)('A'+mid(c.type))<<":"<<tmp<<" to "
							<<(char)('A'+low(c.type))<<endl;
						
						reg[low(c.type)]=tmp;
						
						break;
					case 2:
						tmp=reg[mid(c.type)];
						if(debug)cout<<"mov "<<(char)('A'+mid(c.type))<<" to &"
							<<(char)('A'+low(c.type))<<":"<<reg[low(c.type)]<<endl;
						
						mem[reg[low(c.type)]]=tmp;
						
						break;
					case 3:
						tmp=c.num;
						if(debug)cout<<"mov "<<tmp<<" to "
							<<(char)('A'+low(c.type))<<endl;
						reg[low(c.type)]=tmp;
						break;
				}
				cur++;
				break;
			case put:
				if(debug)cout<<"put "<<(char)('A'+low(c.type))<<endl;
				cout<<reg[low(c.type)]<<" ";
				cur++;
				break;
			case push:
				stack[top++]=reg[0];
				stack[top++]=reg[1];
				stack[top++]=reg[2];
				if(debug)cout<<"push ABC"<<endl;
				cur++;
				break;
			case pop:
				reg[2]=stack[--top];
				reg[1]=stack[--top];
				reg[0]=stack[--top];
				if(debug)cout<<"pop ABC"<<endl;
				cur++;
				break;
			case hlt:
				return;
				break;
		}
		if(debug){
			cout<<"A:"<<reg[0]<<" ";
			cout<<"B:"<<reg[1]<<" ";
			cout<<"C:"<<reg[2]<<" ";
			cout<<"D:"<<reg[3]<<" ";
			cout<<endl;
		}
	}
}
//然后是简洁的主程序
int main(){
	char *p=cpp;
	char c=getchar();
	while(c!=-1){
		*p=c;
		p++;
		c=getchar();
	}
	//calc::build();
	loadvar();
	complie();
	run();
}
```
~~如果感兴趣，可以试着把编译后的程序输出，然后处理成可执行文件~~

然后我出现的三处错误：

不保证有变量定义(#1)

变量名较长时会爆int(#3)

在表达式树上dfs时，单个数字或变量有相反数标记时，没有编译对应命令(#5)

---

## 作者：Ciyang (赞：6)

[BLOG中查看](https://xciyang.github.io/2020-01/11-luogu3695/)体验更佳。

### 前言

给出解释器的相关内容，[国外文献](https://ruslanspivak.com/lsbasi-part1/)及[国内翻译](https://my.oschina.net/shawnplaying/blog/661998)，文献所用语言是Python，并且国内只有计算器的部分（加减乘除，相反数）。

所以我写代码的时候更加注重工程风格，在保证无BUG前提下尽量严格，并且不依赖于其他库（STL）。

*如果在代码中调用了我没有讲的函数，那么请看最后的完整代码，因为函数实在太多了。类中必要的public函数基本都已省略。代码中`...`表示省略*

### 解释器概述

建议先编写一个表达式求值，不过这道题需要处理的中缀表达式中只有加减运算，所以比较简单。

写一下的解释器通用的逻辑。

#### TOKEN

翻译为令牌、标记，我理解为单词，包括单关键字、变量名、符号等。

主要是将一段字符串转换为计算机可以理解的东西，通常是数字。每个TOKEN都有它自己的类型，并且存储原有的内容。TOKEN通常是解释器的最小单元。

具体实现可以用define、const、enum之一，我使用了enum。这些都是程序员自己定义的。例如此题（部分）：
```cpp
enum TOKEN_TYPE {
	INTEGER = 1,    // 整形（数字）
	OPERATOR_PLUS,  // 操作符 '+'
	...,
	T_COLON,        // 符号 ':'
	T_COMMA         // 符号 ','
};
// TOKEN 类型
```
存储时即使用类或者结构体，代码（部分）：
```cpp
class TOKEN {
	private:
	TOKEN_TYPE _typ;    // TOKEN类型
	const char *_val;   // 原有的值
	unsigned int _len;  // 值长度
    // 注：使用 const char* 是为了方便
    ...
};
```

#### LEXER

翻译为词法分析器。简单来说，输入一堆字符（本题是整个程序），经过LEXER的处理，输出一系列的TOKEN（按顺序）。

对于大部分OIER来说，都写过暴力模拟的表达式求值。两者想似，但是LEXER分析一段字符串后输出TOKEN并不直接让LEXER来处理。所以它还有个别名为scanner。

存储时依然是使用类或者结构体，代码（部分）：

```cpp
class LEXER {
	private:
	const char *_text;  // 一堆字符（本题是整个程序）
	unsigned int _len;  // 字符长度
	unsigned int _pos;  // 处理到第_pos个字符（从 0 开始）
	char _ch;           // 当前字符为_ch
    ...
}
```

然后要在类中写几个函数，分别是扫描下一个字符、跳过间隔符、跳过数字等。扫描下一个字符时要判断是否已到字符串结尾，代码：

```cpp
void nextChar() {
    this->_ch = (this->_pos >= this->_len ? 0 : this->_text[++this->_pos]);
    return;
}
unsigned int skipNumber() {
    unsigned int res = 0;
    while(this->_ch != 0 && isNumber(this->_ch)) ++res, nextChar();
    // isNumber(x) 表示 x 是否为数字
    return res;
}
```

LEXER最重要的作用还是获取TOKEN，对于本题的代码（部分）：

```cpp
TOKEN getNextToken() {
    while(this->_ch != 0) {
        if(isSpacer(this->_ch)) {
        // isSpacer(x) 表示 x 是否为间隔符
            skipSpace();
        // skipSpace() 跳过间隔符
            continue;
        }
        if(isNumber(this->_ch)) {
        // isNumber(x) 表示 x 是否为数字
            const char *pos = getPosString();
            return TOKEN(INTEGER, pos, skipNumber());
        }
        if(this->_ch == '+') {
            nextChar();
            return TOKEN(OPERATOR_PLUS);
        }
        ...
        if(this->_ch == ',') {
            nextChar();
            return TOKEN(T_COMMA);
        }
        if(this->_ch == ':') {
            nextChar();
            return TOKEN(T_COLON);
        }
        return TOKEN(T_NULL);
        // 无法处理
    }
    return TOKEN(T_EOF);
    // 结尾
}
```

#### NODE

NODE是我起的名字，因为它代表语法树的一个节点。获得程序根节点的返回值意味着运行整个程序。

每个NODE存储一个TOKEN，TOKEN的类型表示NODE的任务类型，TOKEN的值表示NODE可用的参数。NODE还有它的子节点，每个NODE运作时都会用指定方式使它的子节点运作。

它的类在此题如下：
```cpp
class NODE {
	private:
	TOKEN _token;               // 必需的
	NODE **_list;               // 子节点指针数组
	bool _multi;
	unsigned int _siz, _msiz;
	bool _flag;
}
```

_multi、_msiz、_flag是我的实现，可能有更好的方法。至于它们的作用会在下面再讲。

NODE的两个核心方法为getValue和setValue，但对于本题来说，前置更复杂一些。

#### PARSER

翻译为语法分析器。输入TOKEN，生成语法树，输出根节点。因为此题不涉及运算符先后顺序，所以只需实现判断。循环等语法即可。

PARSER类的代码（部分）：
```cpp
class PARSER {
	private:
	LEXER _lexer;   // 绑定的LEXER
	TOKEN _tok;     // 当前处理的TOKEN
    ...
};
```
同样在类中有获得下一个TOKEN的函数，代码：
```cpp
void nextToken(TOKEN_TYPE typ) {
    if(this->_tok.getType() == typ) this->_tok = this->_lexer.getNextToken();
    return;
}
```
有方法parser用来生成语法树，内部由多个函数递归实现，因语言而异。

#### CALCULATOR

推荐先写一个加减乘除相反数的计算器来练手，[此处](https://github.com/Xciyang/OI-Workspace/blob/ed0e1c1457e8a5263177cc5c4b0a1db971b1e02e/calc.cpp)为我的代码。

### 本题分析

计算器和本题差别还是很大的，对比发现，本题多了变量、判断、循环、数组、输出、比较，少了乘除。再进一步发现，少了运算优先级的问题。

#### TOKEN

我定义本题有30个TOKEN，可以说是非常多了，所以请对照完整代码。然后只讲一些本题的核心语法和逻辑。

如果不知道某个TOKEN_TYPE的含义，那么请看在代码里的LEXER中TOKEN是如何产生的。

#### VARIABLE

至于为什么先讲这个，因为程序一上来就要定义变量。我是针对本题只有int来解决的，解释器文献的这部分在C++中出入较大。

本着不用STL的原则，因此无法使用map。我并不想也不会写红黑树，而本题只有10个变量，所以就链表查询变量了。代码（部分）：

```cpp
class VAR {
	private:
	const char *_name;  // 变量名
	unsigned int _len;  // 变量名长度
	VAR *_nxt;          // 链表下一个
	int *_mem;          // 内存
	int _s, _t;         // 数组下标起始和终止，非数组中分别为0、1
    ...
};
```

然后定义一个链表首节点var_first，写两个函数分别为getVar、setVar，前置是根据名称获得VAR指针，后者实际上是注册一个VAR。

#### BLOCK

BLOCK是一个TOKEN类型，目的表示代码块。一个`{}`所包含的内容即是一个代码块，特别的，整个程序也是一个代码块。

根据语言的特性，代码块的第一行通常为控制语句，比如判断、循环、vars等。如果没有控制语句，设置BLOCK为默认控制语句，代表只运行一次，vars也是如此。

我们将根据第0个子节点的返回值是否为true循环运行BLOCK中的内容。

#### NODE

所以问题又来了，如何存储子节点列表。我们并不想使用vector，只好自己实现。

根据vector的思想，只需要在列表已满时将空间扩大一倍（变为两倍），效率比较高。

为了方便使用，特化出自运算、一元运算和二元运算，以~~提高代码复杂度~~便于编写。

按照规则，BLOCK表示代码块时是多元运算。如果BLOCK表示控制语句时是自运算。

因此在代码中用_multi表示是否为多元运算，_siz记录子节点数，_msiz记录分配内存大小。

#### VARIABLE_DEFINE

首先知道格式为`name:type/array[type, s..t]`，即`名称:类型/数组[类型, 起始下标..终止下标]`。

那么组成它的TOKEN包括VARIABLE_NAME、VARIABLE_TYPE、BRACKET_LEFT、BRACKET_RIGHT、INTEGER、T_DOT。

语法树构建时，我把T_COLON设为多元运算符，VARIABLE_NAME设为第0子节点，省去了VARIABLE_TYPE，如果为数组再新建两个INTEGER节点当做T_COLON的子节点。

此为parserVar函数。

运作时判断子节点数，VAR中的_s为第1个子节点的值，_t为第2个子节点的值，无子节点视为0、1。

#### EXPRESSION

表达式已经是老生常谈的问题了，所以不再细说。

遇到表达式调用parserSecond，内部调用parserThird，分析出常量、变量、加减运算符，遇到括号（然而此题没有，才发现）就递归调用parserSecond。

#### VARIABLE

读取变量的值时先读入VARIABLE_NAME，再判断是否有BRACKET_LEFT（左中括号），之后再调用parserSecond读取内部表达式，再读入BRACKET_RIGHT，然而本题内部表达式并不会很复杂。

所以此处我把VARIABLE_NAME设为一元运算符，仅有的一个子节点为下标（不是数组则为0）。

#### YOSORO | ASSIGN(SET)

先分析输出和赋值语句，因为它们逻辑最简单且作用相反（似乎并不相反）。

当PARSER遇到类型为T_COLON的TOKEN时，那么就视为要执行函数了，进入parserCall函数。

YOSORO为一元运算符，仅有一个子节点为表达式。ASSIGN为二元运算符，左儿子为变量名，右儿子为表达式。

#### IF(IHU) | WHILE

之所以它们放在一块，是因为语法相同。当遇到对应的TOKEN时，依次读取比较操作符、逗号、表达式、逗号、表达式，函数为parserIhu和parserWhile。

IF和WHILE为一元运算符，仅有一个子节点为比较操作符的返回值。众所周知比较操作符是二元运算符，这个非常简单。

为了判断一个节点是否第一次运作，所以在NODE中加入了变量_flag。

IF和WHILE的差别在于IF后需要将_flag设为true。

#### BLOCK 1

在BLOCK运作结束后还需要重置子节点的状态信息（如_flag），以让下次进入BLOCK节点时所有的子节点是新的。

#### FOR(HOR)

FOR应该是比较麻烦的一个，我将它设为多元运算符。

函数为parserHor，依次读取表达式、逗号、表达式、逗号、表达式。三个表达式依次为它的三个子节点。

运作时先判断_flag，第一次需要给第0个子节点赋值为第1个子节点的值。然后再通过判断第0个子节点是否小于等于第2个子节点。

还需要让FOR节点也要有一个赋值的方法，为了在循环结束时给第0个子节点加1。

#### BLOCK 2

所以BLOCK结束时还要调用控制语句（第0个子节点）的赋值操作，当然值就不必设置了。

#### GLOBAL FUNCTION

运行程序使用calc，参数为整个程序和字符串长度。

```cpp
int calc(const char *exp, unsigned int len) {
	char *_exp = new char[len]();
	for(unsigned int i = 0; i < len; i++) _exp[i] = exp[i];
    // 改为用户不可变内存，安全起见
	int res = PARSER(LEXER(_exp, len)).parser()->getValue();
	delete[] _exp;
	return res;
}
```

并未使用strcmp，手写了equalString用来判断字符串是否相等。

剩下的方法都比较简单，自行理解即可。

### 图例

如果还不懂可以看图例，纯手工良心制作。

![P3695](https://xciyang.github.io/images/P3695.jpg)

### 代码

无O2用时37ms内存820KB

```cpp
#include <stdio.h>
namespace CALCULATOR {
enum TOKEN_TYPE {
	INTEGER = 1,
	OPERATOR_PLUS,
	OPERATOR_MINUS,
	OPERATOR_LT,
	OPERATOR_GT,
	OPERATOR_LE,
	OPERATOR_GE,
	OPERATOR_EQ,
	OPERATOR_NEQ,
	PAR_LEFT,
	PAR_RIGHT,
	BRACKET_LEFT,
	BRACKET_RIGHT,
	BLOCK_LEFT,
	BLOCK_RIGHT,
	PROGRAM,
	BLOCK,
	VARIABLE_NAME,
	VARIABLE_TYPE,
	VARS,
	YOSORO,
	OPERATOR_ASSIGN,
	IHU,
	HOR,
	WHILE,
	T_DOT,
	T_EOF,
	T_NULL,
	T_COLON,
	T_COMMA
};

bool equalString(const char *a, const char *b, unsigned int len) {
	for(unsigned int i = 0; i < len; i++)
		if(a[i] != b[i]) return 0;
	return 1;
}
class VAR {
	private:
	const char *_name;
	unsigned int _len;
	VAR *_nxt;
	int *_mem;
	int _s, _t;

	public:
	VAR() : _name(), _len(), _nxt(), _mem(), _t(), _s() {}
	VAR(const char *name, unsigned int len) : _name(name), _len(len), _nxt(), _mem(), _t(), _s() {}
	VAR(const char *name, unsigned int len, int s, int t) : _name(name), _len(len), _nxt(), _mem(), _t(t), _s(s) {
		this->_mem = new int[this->_t - this->_s]();
	}
	unsigned int getLen() const {
		return this->_len;
	}
	void setValue(int x, int v) {
		this->_mem[x - this->_s] = v;
		return;
	}
	const char *getName() const {
		return this->_name;
	}
	VAR *getNext() const {
		return this->_nxt;
	}
	void setNext(VAR *v) {
		this->_nxt = v;
	}
	int getValue(int x) {
		return this->_mem[x - this->_s];
	}
} var_first;
VAR *getVar(const char *name, unsigned int len) {
	VAR *p = &var_first;
	while(p) {
		if(p->getLen() == len && equalString(p->getName(), name, len)) return p;
		p = p->getNext();
	}
	return 0;
}
void setVar(VAR *nxt) {
	VAR *p = &var_first;
	while(p->getNext()) p = p->getNext();
	p->setNext(nxt);
	return;
}
class TOKEN {
	private:
	TOKEN_TYPE _typ;
	const char *_val;
	unsigned int _len;

	public:
	TOKEN(TOKEN_TYPE typ = T_NULL) : _typ(typ), _val(), _len() {}
	TOKEN(TOKEN_TYPE type, const char *val, unsigned int len) : _val(val), _typ(type), _len(len) {}
	TOKEN_TYPE getType() const {
		return this->_typ;
	}
	const char *getValue() const {
		return this->_val;
	}
	unsigned int getLength() const {
		return this->_len;
	}
	~TOKEN() {}
};
int toInteger(const char *val, unsigned int len) {
	int res = 0;
	for(unsigned int i = 0; i < len; i++) res = res * 10 + val[i] - '0';
	return res;
}

unsigned int toString(int val, char *res) {
	unsigned int len = 0;
	int val2 = val;
	while(val2) ++len, val2 /= 10;
	unsigned int len2 = len;
	while(val) res[--len2] = '0' + val % 10, val /= 10;
	if(len == 0) res[len = 1] = '0';
	return len;
}

bool isNumber(char ch) {
	return ch >= '0' && ch <= '9';
}

bool isLetter(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool isSpacer(char ch) {
	return ch == ' ' || ch == '\n' || ch == '\t';
}

class LEXER {
	private:
	const char *_text;
	unsigned int _len;
	unsigned int _pos;
	char _ch;
	void nextChar() {
		this->_ch = (this->_pos >= this->_len ? 0 : this->_text[++this->_pos]);
		return;
	}
	void skipSpace() {
		while(this->_ch != 0 && isSpacer(this->_ch)) nextChar();
		return;
	}
	unsigned int skipNumber() {
		unsigned int res = 0;
		while(this->_ch != 0 && isNumber(this->_ch)) ++res, nextChar();
		return res;
	}
	unsigned int skipWord() {
		unsigned int res = 0;
		while(this->_ch != 0 && isLetter(this->_ch)) ++res, nextChar();
		return res;
	}
	const char *getPosString() const {
		return _text + _pos;
	}

	public:
	LEXER(const char *text, unsigned int len) : _text(text), _len(len), _pos() {
		this->_ch = (this->_pos >= this->_len ? 0 : this->_text[this->_pos]);
	}
	~LEXER() {}
	TOKEN getNextToken() {
		while(this->_ch != 0) {
			if(isSpacer(this->_ch)) {
				skipSpace();
				continue;
			}
			if(isNumber(this->_ch)) {
				const char *pos = getPosString();
				return TOKEN(INTEGER, pos, skipNumber());
			}
			if(isLetter(this->_ch)) {
				const char *pos = getPosString();
				unsigned int len = skipWord();
				if(len == 2 && equalString("lt", pos, len)) return TOKEN(OPERATOR_LT);
				if(len == 2 && equalString("gt", pos, len)) return TOKEN(OPERATOR_GT);
				if(len == 2 && equalString("le", pos, len)) return TOKEN(OPERATOR_LE);
				if(len == 2 && equalString("ge", pos, len)) return TOKEN(OPERATOR_GE);
				if(len == 2 && equalString("eq", pos, len)) return TOKEN(OPERATOR_EQ);
				if(len == 3 && equalString("neq", pos, len)) return TOKEN(OPERATOR_NEQ);
				if(len == 3 && equalString("set", pos, len)) return TOKEN(OPERATOR_ASSIGN);
				if(len == 3 && equalString("ihu", pos, len)) return TOKEN(IHU);
				if(len == 3 && equalString("hor", pos, len)) return TOKEN(HOR);
				if(len == 3 && equalString("int", pos, len)) return TOKEN(VARIABLE_TYPE, pos, len);
				if(len == 4 && equalString("vars", pos, len)) return TOKEN(VARS);
				if(len == 5 && equalString("while", pos, len)) return TOKEN(WHILE);
				if(len == 5 && equalString("array", pos, len)) return TOKEN(VARIABLE_TYPE, pos, len);
				if(len == 6 && equalString("yosoro", pos, len)) return TOKEN(YOSORO);
				return TOKEN(VARIABLE_NAME, pos, len);
			}
			if(this->_ch == '+') {
				nextChar();
				return TOKEN(OPERATOR_PLUS);
			}
			if(this->_ch == '-') {
				nextChar();
				return TOKEN(OPERATOR_MINUS);
			}
			if(this->_ch == '(') {
				nextChar();
				return TOKEN(PAR_LEFT);
			}
			if(this->_ch == ')') {
				nextChar();
				return TOKEN(PAR_RIGHT);
			}
			if(this->_ch == '.') {
				nextChar();
				nextChar();
				return TOKEN(T_DOT);
			}
			if(this->_ch == ',') {
				nextChar();
				return TOKEN(T_COMMA);
			}
			if(this->_ch == ':') {
				nextChar();
				return TOKEN(T_COLON);
			}
			if(this->_ch == '[') {
				nextChar();
				return TOKEN(BRACKET_LEFT);
			}
			if(this->_ch == ']') {
				nextChar();
				return TOKEN(BRACKET_RIGHT);
			}
			if(this->_ch == '{') {
				nextChar();
				return TOKEN(BLOCK_LEFT);
			}
			if(this->_ch == '}') {
				nextChar();
				return TOKEN(BLOCK_RIGHT);
			}
			return TOKEN(T_NULL);
		}
		return TOKEN(T_EOF);
	}
};

class NODE {
	private:
	TOKEN _token;
	NODE **_list;
	bool _multi;
	unsigned int _siz, _msiz;
	bool _flag;
	int getConstantValue() {
		if(this->_token.getType() == INTEGER) return toInteger(this->_token.getValue(), this->_token.getLength());
		if(this->_token.getType() == VARS && this->_flag == 0) return this->_flag = 1;
		if(this->_token.getType() == BLOCK && this->_flag == 0) return this->_flag = 1;
		return 0;
	}
	int getUnaryValue() {
		if(this->_token.getType() == OPERATOR_PLUS) return +this->_list[0]->getValue();
		if(this->_token.getType() == OPERATOR_MINUS) return -this->_list[0]->getValue();
		if(this->_token.getType() == YOSORO) return printf("%d ", this->_list[0]->getValue()), 0;
		if(this->_token.getType() == VARIABLE_NAME) return getVar(this->_token.getValue(), this->_token.getLength())->getValue(this->_list[0]->getValue());
		if(this->_token.getType() == IHU && this->_flag == 0) return this->_flag = 1, this->_list[0]->getValue();
		if(this->_token.getType() == WHILE) return this->_list[0]->getValue();
		return 0;
	}
	int getBinValue() {
		if(this->_token.getType() == OPERATOR_PLUS) return this->_list[0]->getValue() + this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_MINUS) return this->_list[0]->getValue() - this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_LT) return this->_list[0]->getValue() < this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_GT) return this->_list[0]->getValue() > this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_LE) return this->_list[0]->getValue() <= this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_GE) return this->_list[0]->getValue() >= this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_EQ) return this->_list[0]->getValue() == this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_NEQ) return this->_list[0]->getValue() != this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_ASSIGN) return this->_list[0]->setValue(this->_list[1]->getValue());
		return 0;
	}
	int getMultiValue() {
		if(this->_token.getType() == T_COLON) {
			if(this->_siz == 1) {
				this->_list[0]->registerVar(0, 1);
			}
			else {
				this->_list[0]->registerVar(this->_list[1]->getValue(), this->_list[2]->getValue());
			}
			return 0;
		}
		if(this->_token.getType() == BLOCK) {
			while(this->_list[0]->getValue()) {
				for(unsigned int i = 1; i < this->_siz; i++) {
					this->_list[i]->getValue();
				}
				this->_list[0]->setValue(0);
			}
			this->clearST();
		}
		if(this->_token.getType() == HOR) {
			if(this->_flag == 0) {
				this->_list[0]->setValue(this->_list[1]->getValue());
				this->_flag = 1;
			}
			return this->_list[0]->getValue() <= this->_list[2]->getValue();
		}
		return 0;
	}
	int registerVar(int s, int t) {
		VAR *p = new VAR(this->_token.getValue(), this->_token.getLength(), s, t);
		setVar(p);
		return 0;
	}
	int setValue(int v) {
		if(this->_token.getType() == VARIABLE_NAME) {
			VAR *p = getVar(this->_token.getValue(), this->_token.getLength());
			p->setValue(this->_list[0]->getValue(), v);
		}
		if(this->_token.getType() == HOR) {
			this->_list[0]->setValue(this->_list[0]->getValue() + 1);
		}
		return 0;
	}
	void clearST() {
		if(this->_siz == -1) return;
		for(unsigned int i = 0; i < this->_siz; i++) this->_list[i]->_flag = 0, this->_list[i]->clearST();
	}

	public:
	NODE(bool multi = 0) : _token(T_NULL), _list(), _siz(-1), _multi(multi), _msiz(), _flag() {
		if(this->_multi) this->_siz = 0;
	}
	NODE(TOKEN token) : _token(token), _list(), _siz(), _multi(), _msiz(), _flag() {}
	NODE(TOKEN token, NODE *expr0) : _token(token), _siz(1), _multi(), _msiz(1), _flag() {
		this->_list = new NODE *[this->_siz]();
		this->_list[0] = expr0;
	}
	NODE(TOKEN token, NODE *expr0, NODE *expr1) : _token(token), _siz(2), _multi(), _msiz(2), _flag() {
		this->_list = new NODE *[this->_siz]();
		this->_list[0] = expr0;
		this->_list[1] = expr1;
	}
	~NODE() {
		if(this->_list)
			for(unsigned int i = 0; i < this->_siz; i++) delete this->_list[i];
	}
	int getValue() {
		if(this->_multi) return getMultiValue();
		switch(_siz) {
			case 0: return getConstantValue();
			case 1: return getUnaryValue();
			case 2: return getBinValue();
			default: break;
		}
		return 0;
	}
	void setToken(const TOKEN &token) {
		this->_token = token;
		return;
	}
	void push(NODE *expr0) {
		if(this->_siz >= this->_msiz) {
			unsigned int lmsiz = this->_msiz;
			this->_msiz = (this->_siz + 1) * 2;
			NODE **list = new NODE *[this->_msiz]();
			for(unsigned int i = 0; i < this->_siz; i++) list[i] = this->_list[i];
			if(this->_list) {
				delete[] this->_list;
			}
			this->_list = list;
		}
		this->_list[this->_siz++] = expr0;
		return;
	}
	int getSize() const {
		return this->_siz;
	}
};
class PARSER {
	private:
	LEXER _lexer;
	TOKEN _tok;
	void nextToken(TOKEN_TYPE typ) {
		if(this->_tok.getType() == typ) this->_tok = this->_lexer.getNextToken();
		return;
	}
	NODE *parserThird() {
		TOKEN token = this->_tok;
		if(token.getType() == INTEGER) {
			nextToken(INTEGER);
			return new NODE(token);
		}
		if(token.getType() == PAR_LEFT) {
			nextToken(PAR_LEFT);
			NODE *res = parserSecond();
			nextToken(PAR_RIGHT);
			return res;
		}
		if(token.getType() == VARIABLE_NAME) {
			nextToken(VARIABLE_NAME);
			NODE *res;
			if(this->_tok.getType() == BRACKET_LEFT) {
				nextToken(BRACKET_LEFT);
				res = parserSecond();
				nextToken(BRACKET_RIGHT);
			}
			else {
				res = new NODE();
			}
			return new NODE(token, res);
		}
		if(token.getType() == OPERATOR_PLUS || token.getType() == OPERATOR_MINUS) {
			nextToken(token.getType());
			return new NODE(token, parserThird());
		}

		return new NODE();
	}
	NODE *parserSecond() {
		NODE *res = parserThird();
		while(this->_tok.getType() != T_EOF) {
			TOKEN token = this->_tok;
			if(token.getType() == OPERATOR_PLUS || token.getType() == OPERATOR_MINUS) {
				nextToken(token.getType());
				res = new NODE(token, res, parserThird());
			}
			else {
				break;
			}
		}
		return res;
	}
	NODE *parserCall() {
		TOKEN token = this->_tok;
		if(token.getType() == YOSORO) {
			nextToken(YOSORO);
			return new NODE(token, parserSecond());
		}
		if(token.getType() == OPERATOR_ASSIGN) {
			nextToken(OPERATOR_ASSIGN);
			NODE *res = parserThird();
			nextToken(T_COMMA);
			return new NODE(token, res, parserSecond());
		}
		return new NODE();
	}
	NODE *parserVar() {
		NODE *res = new NODE(1);
		res->push(new NODE(this->_tok));
		nextToken(VARIABLE_NAME);
		res->setToken(this->_tok);
		nextToken(T_COLON);
		if(this->_tok.getLength() == 5) {
			nextToken(VARIABLE_TYPE);
			nextToken(BRACKET_LEFT);
			nextToken(VARIABLE_TYPE);
			nextToken(T_COMMA);
			res->push(new NODE(this->_tok));
			nextToken(INTEGER);
			nextToken(T_DOT);
			nextToken(T_DOT);
			res->push(new NODE(this->_tok));
			nextToken(INTEGER);
			nextToken(BRACKET_RIGHT);
		}
		else {
			nextToken(VARIABLE_TYPE);
		}
		return res;
	}
	NODE *parserIhu() {
		NODE *res;
		nextToken(IHU);
		TOKEN token = this->_tok;
		if(token.getType() == OPERATOR_LT || token.getType() == OPERATOR_GT || token.getType() == OPERATOR_LE || this->_tok.getType() == OPERATOR_GE || this->_tok.getType() == OPERATOR_EQ || token.getType() == OPERATOR_NEQ) {
			nextToken(token.getType());
			nextToken(T_COMMA);
			NODE *res1 = parserSecond();
			nextToken(T_COMMA);
			NODE *res2 = parserSecond();
			res = new NODE(token, res1, res2);
		}
		else {
			res = new NODE();
		}
		return new NODE(TOKEN(IHU), res);
	}
	NODE *parserHor() {
		NODE *res = new NODE(1);
		res->setToken(this->_tok);
		nextToken(HOR);
		res->push(parserSecond());
		nextToken(T_COMMA);
		res->push(parserSecond());
		nextToken(T_COMMA);
		res->push(parserSecond());
		return res;
	}
	NODE *parserWhile() {
		NODE *res;
		nextToken(WHILE);
		TOKEN token = this->_tok;
		if(token.getType() == OPERATOR_LT || token.getType() == OPERATOR_GT || token.getType() == OPERATOR_LE || this->_tok.getType() == OPERATOR_GE || this->_tok.getType() == OPERATOR_EQ || token.getType() == OPERATOR_NEQ) {
			nextToken(token.getType());
			nextToken(T_COMMA);
			NODE *res1 = parserSecond();
			nextToken(T_COMMA);
			NODE *res2 = parserSecond();
			res = new NODE(token, res1, res2);
		}
		else {
			res = new NODE();
		}
		return new NODE(TOKEN(WHILE), res);
	}
	NODE *parserFirst() {
		NODE *res = new NODE(1);
		res->setToken(TOKEN(BLOCK));
		while(this->_tok.getType() != T_EOF) {
			TOKEN token = this->_tok;
			if(token.getType() == VARS) {
				nextToken(VARS);
				res->push(new NODE(TOKEN(VARS)));
			}
			else if(token.getType() == IHU) {
				res->push(parserIhu());
			}
			else if(token.getType() == HOR) {
				res->push(parserHor());
			}
			else if(token.getType() == WHILE) {
				res->push(parserWhile());
			}
			else if(token.getType() == VARIABLE_NAME) {
				if(res->getSize() == 0) res->push(new NODE(TOKEN(BLOCK)));
				res->push(parserVar());
			}
			else if(token.getType() == T_COLON) {
				if(res->getSize() == 0) res->push(new NODE(TOKEN(BLOCK)));
				nextToken(T_COLON);
				res->push(parserCall());
			}
			else if(token.getType() == BLOCK_LEFT) {
				if(res->getSize() == 0) res->push(new NODE(TOKEN(BLOCK)));
				nextToken(BLOCK_LEFT);
				res->push(parserFirst());
				nextToken(BLOCK_RIGHT);
			}
			else {
				break;
			}
		}
		return res;
	}

	public:
	PARSER(LEXER lexer) : _lexer(lexer) {
		this->_tok = this->_lexer.getNextToken();
	}
	NODE *parser() {
		return parserFirst();
	}

	~PARSER() {}
};

int calc(const char *exp, unsigned int len) {
	char *_exp = new char[len]();
	for(unsigned int i = 0; i < len; i++) _exp[i] = exp[i];
	int res = PARSER(LEXER(_exp, len)).parser()->getValue();
	delete[] _exp;
	return res;
}

}  // namespace CALCULATOR

#include <stdio.h>
#include <iostream>
using namespace std;
string str, str2;

int main() {
	while(getline(cin, str2)) {
		str += str2;
	}
	CALCULATOR::calc(str.c_str(), str.size());
	return 0;
}
```

### 后记

题解写了半个下午，继续学习变量类型去了。

---

## 作者：wjyyy (赞：4)

## 题解：

模拟即可。

---

再有其他内容就是字符串的读入了吧。

下了三组数据才AC，不得不说#10很强。

在这个题中，函数思想很重要。因为有很多地方会调用相同的内容，甚至有时候有大篇幅相似的两部分可以合在一个函数里再加`if`判断。

循环的嵌套是最麻烦的内容，其次是变量求值。还好没有数组套数组（大不了多几个递归），字符串长度开得比较小。变量可以用`std::map`映射，然后用编号统一存起来。

对于变量求值而言，一个是**单项式求值**，一个是**多项式(仅加减)求值**，其中又要考虑是否是数组的情况。我写了一个`getnext(int &i)`函数，用来获取从$i$开始的第一个**可求的**式子。如果`a`是一个数组，那么`a[7]`是一个可求的式子而`a`不是。然后用字符串处理依次考虑正负即可。

如果经常使用gdb或某些IDE的自带debug器的话，循环嵌套的思路比较容易联想，实现起来比较麻烦~~废话~~。使用一个变量tot存储当前做到**循环的**第几行了，带入内层循环tot不变，循环结束时置tot为en+2（en指循环结束的}字符所在行的前一行）。

还有一个地方是**循环中**语句会被使用多遍，这时不能直接通过标准读入，而要把这些语句全部存起来。读一行（空格也读）用到的是`gets(char *s)`，当读到EOF时返回NULL。

注意这个题的缩进和空格都不确定。所以需要写一个`jump()`，就是使$i$跳过前面所有的连续空格。还有其他字符的跳过额外写一点也不怎么麻烦。

感谢自己的坚持。

## Code：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
#define jump() do{while(s[i]==' ')++i;}while(0)
using namespace std;
map<string,int> mp;
int a[55][1010];
int cnt;
int st[55],len[55];
char s[1000];
int getnext(int &i)//获得从i开始接下来一段式子的值 i被置为最后一个下标+1
{
    jump();
    int x=0;
    if(s[i]>='0'&&s[i]<='9')
    {
        for(;s[i]>='0'&&s[i]<='9';++i)
            x=x*10+s[i]-'0';
        return x;
    }
    string ss="";
    for(;s[i]>='a'&&s[i]<='z';++i)
        ss+=s[i];
    int t=mp[ss];
    if(len[t]==1)
        return a[t][0];
    jump();
    ++i;
    int ans=a[t][getnext(i)-st[t]];
    ++i;
    return ans;
}
int getstring(int &i)//获得从i开始的一个多项式的值
{
    int ans=0,flag=1;
    jump();
    while((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||s[i]=='+'||s[i]=='-')
    {
        flag=(s[i]=='-')?-1:1;
        while(s[i]==' '||s[i]=='+'||s[i]=='-')
            ++i;
        ans+=flag*getnext(i);
        jump();
    }
    return ans;
}
void Set()//赋值
{
    int i=0;
    jump();
    i+=4;
    jump();
    string ss="";
    for(;s[i]>='a'&&s[i]<='z';++i)
        ss+=s[i];
    int t=mp[ss],u=0,v=0;
    if(len[t]==1)
    {
        while(s[i]==' '||s[i]==',')
            ++i;
        a[t][0]=getstring(i);
    }
    else
    {
        ++i;
        u=getstring(i);
        //i是']'
        ++i;
        while(s[i]==' '||s[i]==',')
            ++i;
        a[t][u-st[t]]=getstring(i);
    }
}
void print()
{
    int i=0;
    jump();
    i+=7;
    jump();
    while(s[i]==' '||s[i]==',')
        ++i;
    printf("%d ",getstring(i));
}

void qaq();
bool ihu(int ty);
void hor();
void whi();

char F[500][100];
int tot=0;

bool isend()//是否结尾 判断ihu、hor和while是否结束
{
    if(!tot)
        gets(s);
    else
    {
        int i=0;
        for(;F[tot][i]!='\0';++i)
            s[i]=F[tot][i];
        s[i]='\0';
        ++tot;
    }
    int i=0;
    jump();
    return (s[i]=='}');
}

int main()
{
    gets(s);
    int i=1,flag=0;
    jump();
    if(s[i]=='v')//如果没有定义就要跳过
{
    gets(s);
    while(s[0]!='}')
    {
        string ss="";
        int i=0;
        jump();
        for(;s[i]>='a'&&s[i]<='z';++i)
            ss+=s[i];
        mp[ss]=++cnt;
        jump();
        if(s[i+1]=='i')
            st[cnt]=len[cnt]=1;
        else
        {
            i+=10;
            while(s[i]==' '||s[i]==',')
                ++i;
            //逗号前后的空格
            st[cnt]=getnext(i);
            while(s[i]==' '||s[i]=='.')
                ++i;
            len[cnt]=getnext(i);
            len[cnt]-=st[cnt]-1;
        }
        gets(s);
    }
}
    else
        flag=1;
    
    while(flag||gets(s)!=NULL)
    {
        flag=0;
        if(!strlen(s))
            continue;
        qaq();
        tot=0;
    }
    return 0;
}
void qaq()//执行语句
{
    int i=0;
    jump();
    if(s[i]=='{')
    {
        ++i;
        jump();
        if(s[i]=='i')
            ihu(0);
        else if(s[i]=='w')
            whi();
        else
            hor();
    }
    else if(s[i+1]=='s')
        Set();
    else
        print();
}

bool ihu(int ty)
{
    int i=0;
    jump();
    ++i;
    jump();
    i+=3+ty*2;
    jump();
    char tmp[2]={s[i],s[i+1]};
    i+=2;
    if(tmp[0]=='n')
        ++i;
    while(s[i]==' '||s[i]==',')
        ++i;
    int x=getstring(i);
    while(s[i]==' '||s[i]==',')
        ++i;
    int y=getstring(i);
    bool sat;
    if(tmp[0]=='e')
        sat=(x==y);
    else if(tmp[0]=='l')
    {
        if(tmp[1]=='t')
            sat=(x<y);
        else
            sat=(x<=y);
    }
    else if(tmp[0]=='n')
        sat=(x!=y);
    else
    {
        if(tmp[1]=='t')
            sat=(x>y);
        else
            sat=(x>=y);
    }
    if(ty)
        return sat;
    int br=1;
    if(!sat)
        while(1)
        {
            if(isend()&&br==1)
                return 0;
            i=0;
            jump();
            if(s[i]=='{')
                ++br;
            if(s[i]=='}')
                --br;
        }
    else
    {
        while(1)
        {
            if(isend()&&br==1)
                return 0;
            if(!strlen(s))
                continue;
            qaq();
        }
    }
}
void hor()
{
    int i=0;
    jump();
    ++i;
    jump();
    i+=3;
    jump();
    string ss="";
    for(;s[i]>='a'&&s[i]<='z';++i)
        ss+=s[i];
    int t=mp[ss];
    int *ii,u;//用指针引用值更加方便
    if(len[t]==1)
        ii=&a[t][0];
    else
    {
        ++i;
        u=getstring(i);
        ii=&a[t][u-st[t]];
    }
    while(s[i]==' '||s[i]==',')
        ++i;
    int from=getstring(i);
    while(s[i]==' '||s[i]==',')
        ++i;
    int to=getstring(i);
    int st=1,en=0,l=0;
    if(tot)
        st=tot;
    int br=1;
    while(1)
    {
        if(isend()&&br==1)//注意不要找到别人的右括号了 下同
        {
            if(tot)
                en=tot-2;//en是右括号上面一行相对st(1)的编号
            else
                en=l;
            break;
        }
        if(!strlen(s))//注意空串如果跳过会方便一些
            continue;
        ++l;
        i=0;
        jump();
        if(s[i]=='{')
            ++br;
        if(s[i]=='}')
            --br;
        if(!tot)
        {
            i=0;
            for(;s[i]!='\0';++i)
                F[l][i]=s[i];
            F[l][i]='\0';
        }
    }
    for(*ii=from;*ii<=to;++(*ii))
    {
        tot=st;
        while(tot<=en)
        {
            i=0;
            for(;F[tot][i]!='\0';++i)
                s[i]=F[tot][i];
            s[i]='\0';
            ++tot;
            qaq();
        }
    }
    tot=en+2;
}


void whi()
{
    int i=0;
    char p[1000];
    for(;s[i]!='\0';++i)
        p[i]=s[i];
    p[i]='\0';
    int st=0,en=0,l=0;
    if(tot)//最外层不需要处理这里
    {
        st=tot-1;
        ++tot;
    }

    int br=1;
    while(1)
    {
        if(isend()&&br==1)
        {
            if(tot)
                en=tot-2;
            else
                en=l;
            break;
        }
        if(!strlen(s))
            continue;

        i=0;
        ++l;
        jump();
        if(s[i]=='{')
            ++br;
        if(s[i]=='}')
            --br;
        if(!tot)
        {
            i=0;
            for(;s[i]!='\0';++i)
                F[l][i]=s[i];
            F[l][i]='\0';
        }
    }

    while(1)
    {
        tot=st+1;
        i=0;
        for(;p[i]!='\0';++i)
            s[i]=p[i];
        s[i]='\0';
        if(!ihu(1))
        {
            tot=en+2;
            return;
        }

        while(tot<=en)
        {
            i=0;
            for(;F[tot][i]!='\0';++i)
                s[i]=F[tot][i];
            s[i]='\0';
            ++tot;
            qaq();
        }
    }
}
```

---

## 作者：Untitled10032 (赞：3)

~~NOIP 临近，据之前模拟赛的经验来看，正解我大概的确是想不出来了，但是暴力还老是写挂。所以想做一道大模拟练练手。结果脑子一抽做了这道题，差点死在 VS code 里。~~

------------


__我采用的是类似编译器的方法。先把所有语句都解析之后存起来之后再运行。__

------------


## 语句的存储

- （先给每种命令设置一个“ID”）：

```cpp
enum Opt {
    YOSORO, SET, IHU, JMP, HOR, WHILE, VARS, DEC
    //JMP: 跳到指定指令，最终处理结果中不含有 while。
    //DEC：自减运算。
};

enum Operator {
    LT, GT, LE, GE, EQ, NEQ, ERR    //ERR: 错误的符号
};
```

- 整个程序中的语句用 vector 存起来，语句中的参数可能是在解析输入的时候不能确定的值，所以用链表存储一个表达式，里面是需要引用的变量的地址、偏移量（数组下标有时也不能在解析的时候确定）。

```cpp
struct Arg {
    int *addr;
    Arg *addrShift; //偏移量（因为需要考虑变量做下标）
    bool positive;  //true:+, false:-
    Arg *nxt;   //需要保证链表尾项nxt为NULL
};
class Statement {
public:
    Opt opt;
    Arg *args[mxStatArg];
    Statement(Opt option) {
        opt = option;
    }
};
vector<Statement> program;
```
### 常量的存储

存储语句时肯定会遇到一些常量。我采取的方法是开一个专门存储常量的数组，遇到常量就放进数组里，然后拿出指针。

```cpp
int constPool[constPoolSize], cntConst = 0;
```

_什么？你说可以直接在存储语句的类里面开几个 int 的空间或者存的时候直接用 `new` 分配一个地址？	我后来才想到这些的，懒得改了。反正就这样也不错。_

### 变量的存储

分数和数组两个 `map` 存储。

```cpp
map<string, int> integers;
struct Array {
    int delta;
    int arr[mxArraySize];
    Array(int bg, int en) {
        memset(arr, 0, (en - bg + 3) * sizeof(int));
        delta = bg;
    }
    int& operator [] (int pos) {
        return arr[pos - delta];
    }
};
map<string, Array> arrays;
```

数组需注意下标问题。这里我直接将对整个 struct 的下标运算符重载成了访问偏移后的下标。

## 解析输入

将解析输入部分封装成了一个类（`Processer`）：

```cpp
class Processer {
    char inputBuf[inBufSize];
    char *cursor;
    
    inline string getNextWord();    //提取下一个词（需保证词在本行内）
    inline bool endOfLine();        //光标后换行前没有有意义的东西
    inline bool eof();              //光标已经跑到了没有数据的荒原
    inline void nextCommandLine();  //跳到下一个有意义的行
    inline void skipSpace();        //跳过空格
    inline void skipChar(char);     //跳过任意多个空格和任意多个指定字符的任意排列
    inline int readNum();           //读取下一个数
    inline int readNum(string);     //从string读取数
    inline Operator judgeOper(string);  //判断不等式（判断式）的符号
    inline Arg* judgeVar(string);       //返回变量的地址
    inline Arg* analyzeFormula();       //解析算式（返回解析后的链表首指针）
    inline void error(const char *);    //报告错误
public:
    Processer();
    inline void getInput(); //将输入全部读入
    inline void proc();     //处理
}processer;

```
（函数的定义请看文末源代码）

**为了运行时好处理，新定义了两个指令：**

- `jmp`：跳到指定指令。
- `dec`：自减运算。

给每种类型规定了参数的存储顺序：

- `ihu`: 不等式符号，不等式左，不等式右，若表达式不成立则跳到哪行
- `hor`: 循环变量，循环变量的最大值，若表达式不成立则跳到哪行
- `set`: 被赋值的变量, 赋过去的值
- `jmp`: 指令序号
- `dec`: 对象

### 划分“词”：

将输入分解成许多便于处理的“词”。（这玩意好像流行叫 Token，但我就叫它 word，懒得改了）

`getNextWord` 函数如果遇到一个括号或其它有用的符号就直接返回这个符号，其它情况则返回下一个由数组和字母组成的字符串。这样可以方便地判断下标、算式符号等。

```cpp
inline string Processer::getNextWord() {
    while (*cursor == ' ')  cursor++;
    string ret = "";
    if (*cursor == '{' || *cursor == '}' || *cursor == '+' || *cursor == '-' ||
        *cursor == '[' || *cursor == ']' || *cursor == ':' || *cursor == ',')
        ret.push_back(*(cursor++));
    else
        while ((*cursor >= 'a' && *cursor <= 'z') || (*cursor >= 'A' && *cursor <= 'Z') ||
            (*cursor >= '0' && *cursor <= '9'))
            ret.push_back(*(cursor++));
    return ret;
}
```

### 将 `hor` 和 `while` 拆分。

- `hor`

将 `hor` 拆分成 `set` 与 `hor`，拆分后的 `hor` 中只是将循环变量自增，只有判断循环是否应该停止。并在循环结束时 `jmp` 回循环开始。

`hor` 伪代码（存储时语句的参数与参数表对应）：

```
原格式：
{	hor var, bg, en
	...
}

存储格式：
:set var, bg - 1
hor bg, en, jmp的下一行
...
jmp hor那一行

```
- `while`

将 `while` 转换成 `ihu`，并在循环结束时 `jmp` 回循环开始。

`while` 伪代码：
```
原格式：
{	while oper, left, right
	...
}

存储格式：
ihu oper, left, right, jmp的下一行
...
jmp ihu那一行
```

### 大括号问题

使用了一个栈来存储大括号。

```cpp
struct Brace {
    Opt opt;    //前大括号是什么指令
    int bg;     //前大括号在第几个指令
};
stack<Brace> braces;
```

遇到前括号压栈（`vars` 除外，处理 `vars` 时会顺便把后括号吃掉），遇到后括号取栈顶、弹栈并填入响应语句与参数。

#### 注意：输入数据最后可能没有换行。

## 运行

将运行部分封装成了一个类（`Runner`）：
```cpp
class Runner {
    int calc(Arg *);
    inline bool judge(int, int, int);
    inline void error(const char *, int);
public:
    inline void run();
}runner;
```
（函数的定义请看文末源代码）

~~封装了个寂寞~~

运行就比较简单了。

写了一个递归函数（calc）去计算每个表达式的值。

```cpp
int Runner::calc(Arg *a) {
    if (a == NULL)
        return 0;
    const int res = *(a->addr + calc(a->addrShift));
    if (a->positive)
        return calc(a->nxt) + res;
    else
        return calc(a->nxt) - res;
}
```


之后将语句一个一个往下执行，把对应的参数拿出来参与运算，如果需要跳转就跳到对应的行，否则执行下一个语句。如果执行完了就停。就行了。

# [源代码](/paste/o3smwhta)

------------

__附录 单词表__

| 单词 | 释义 |
| :----------- | :----------- |
| statement | 这里指单个语句（这个用法好像不常见）。 |
| brace | 大括号。 |
| word | 就是大佬们说的 token，即将字符串划分成的便于处理的子串。 |
| formula | 这里指算式、表达式。（这个词好像一般指公式，建议不要像我这样用） |

__以下是较常见/简单的单词：__

| 单词 | 释义 |
| :----------- | :----------- |
| cursor | 指光标。 |
| opt | 为 option 的简写。选项，选择。 |
| calc | 为 calculate 或 calculation 的简写。计算。 |
| analyze | 分析，解析。|
| arg | 为 argument 的简写。指实际参数。~~精氨酸~~ |
| positive | 这里指一个数为正数。

---

## 作者：zesqwq (赞：2)

# P3695 CYaRon!语 题解

说实话这道模拟题并不难，~~而且代码量只有 [3.30k](https://www.luogu.com.cn/record/86095503)(%%% 1.95k 带师)~~。

在正式做这道题目之前，我们发现所有的空格和注释都是 **不必要** 的，因此可以直接不读入空格和注释。

但是请注意，在 $\texttt{CYaRon}$ 中换行很重要，因为任何指令都独占一行，它可以帮助我们更便捷地分析一个个指令。

以下就是一个基础的读入代码。
```cpp
inline char getc() {
    char ch = getchar();
    if (ch == '#')
        while (ch != '\n' && ch != EOF) ch = getchar();
    return ch;
}
int n;
void readin() {
    char tmp;
    while ((tmp = getc()) != EOF) {
        if (tmp == ' ' || tmp == '\t') continue;
        if (tmp == '\n')
            n++;
        else
            c[n][len[n]++] = tmp;
    }
    n++;
}
```
建立一些关于字符串使用的函数（用 STL 也是可以的），具体包括判断一个字符串的某个子串和另一个字符串是否相同，以及找到一个子串中某字符第一次出现的位置：
```cpp
inline bool same(char str[], int l, int r, const char p[]) {
    int len = strlen(p);
    if (len != (r - l)) return 0;
    for (int i = l; i < r; i++)
        if (str[i] != p[i - l]) return 0;
    return 1;
}
inline int find(int x, int l, int r, char v) {
    for (int i = l; i < r; i++)
        if (c[x][i] == v) return i;
    return -1;
}
```
然后就码一个简单的处理框架：解决 $x$ 行开头的语句块的指令，并跳至语句块末尾。
```cpp
inline void solve(int& x) { //解决x行开头的语句块的指令，并跳至语句块末尾
    if (len[x] == 0) return;
    if (same(c[x], 0, 7, ":yosoro"))
        printf("%d ", getExpression(x, 7, len[x]));
    else if (same(c[x], 0, 5, "{vars"))
        solvevar(x);
    else if (same(c[x], 0, 4, ":set")) {
        int f1 = find(x, 4, len[x], ',');  //,的位置
        getVariable(x, 4, f1) = getExpression(x, f1 + 1, len[x]);
    }
    else if (same(c[x], 0, 4, "{ihu"))
        solveihu(x);
    else if (same(c[x], 0, 4, "{hor"))
        solvehor(x);
    else if (same(c[x], 0, 6, "{while"))
        solvewhile(x);
}
int main() {
    readin();
    for (int i = 0; i < n; i++)
        solve(i);
    return 0;
}
```

这样所有有关读入的+处理就完成了，下面就是分析一个一个指令。

实际上，`set`， `yosoro`， `vars` 本身处理难度并不大，只要暴力执行指令即可, 这道题处理的核心问题在于以下2个：

- 表达式的求值 (重中之重)；
- 分支和循环结构的处理。

## 表达式

一开始你可能以为表达式处理很简单，“不就是一步一步算出来吗”。

实际上你会遇到一个大问题：数组访问。

数组下标中也是表达式，这就很讨厌。虽然题目中说没有嵌套数组访问，但是可以在下标中嵌套一个表达式。

而且数组访问的时候它就和变量必须分开来做，所以你很难用一个类去代表2种类型的数据来简化这个问题。

所以这东西就很棘手。

我对表达式的处理方法是这样的：

找到不在数组的方括号中的减号和加号，分成一个一个数。

对这些数进行单独的处理：

如果分出的数是数组，则继续递归处理数组下标中的表达式，否则直接返回变量值或常量。

程序中 $x,l,r$ 表示计算第 $i$ 行去空格后第 $l$ 至 $r$ 个字符构成的表达式的和，其中 $\texttt{tablearr}$ 和 $\texttt{tableint}$ 分别存整形和数组。

这种方法的时间复杂度是 $O(n^2)$ 的（利用在数组下标中不断迭代数组访问），是可以优化的，但是本题目并没此情况，因为保证下标不会嵌套。

实现和下面差不多。
```cpp
inline int stoint(int x, int l, int r) {
    int num = 0, flag = 1;
    for (int i = l; i < r; i++) num = (num << 1) + (num << 3) + (c[x][i] ^ 48);
    return num * flag;
}
inline string getstr(int x, int l, int r) {
    string ans = "";
    for (int i = l; i < r; i++) ans.push_back(c[x][i]);
    return ans;
}
inline int& getVariable(int x, int l, int r) {
    if (c[x][r - 1] != ']') return tableint[getstr(x, l, r)];
    int ll = find(x, l, r, '[');
    return tablearr[getstr(x, l, ll)][getExpression(x, ll + 1, r - 1)];
}
inline int getnum(int x, int l, int r) {
    if (isdigit(c[x][l])) return stoint(x, l, r);
    return getVariable(x, l, r);
}
inline int getExpression(int x, int l, int r) {
    int ans = 0, ll = l, flag = 1, lf = 0;
    for (int i = l; i < r; i++) {
        if (c[x][i] == '[') ++lf;
        if (c[x][i] == ']') --lf;
        if (!lf && c[x][i] == '+') ans += flag * getnum(x, ll, i), flag = 1, ll = i + 1;
        if (!lf && c[x][i] == '-') ans += flag * getnum(x, ll, i), flag = -1, ll = i + 1;
    }
    ans += flag * getnum(x, ll, r);
    return ans;
}
```
## 分支和循环结构

首先是 `ihu` 语句：直接找到逗号的位置，然后判断两个表达式的关系即可。如果他们的关系符合要求，则一行一行执行，直到现在的行头是右花括号。如果不符合要求，就一直扫到左括号与右括号一样多即可。

```cpp
inline bool checkOp(string s, int x, int y) {
    if (s == "lt") return x < y;
    if (s == "gt") return x > y;
    if (s == "le") return x <= y;
    if (s == "ge") return x >= y;
    if (s == "eq") return x == y;
    if (s == "neq") return x != y;
    return 0;
}
void solveihu(int& x) {
    int f1 = find(x, 4, len[x], ','), f2 = find(x, f1 + 1, len[x], ','); // f1表示第一个','f2表示第二个','
    string s1 = getstr(x, 4, f1);
    int x1 = getExpression(x, f1 + 1, f2), x2 = getExpression(x, f2 + 1, len[x]);
    if (checkOp(s1, x1, x2)) {
        ++x;
        while (c[x][0] != '}') solve(x), ++x;
    } else {
        int lfsum = 1;
        ++x;
        while (lfsum) {
            if (c[x][0] == '{') ++lfsum;
            if (c[x][0] == '}') --lfsum;
            ++x;
        }
        --x;
    }
}
```
`while` 的处理看似肯麻烦，实则就是在 `ihu` 的处理最后再重新递调用一下自己就可以了。因为 `while` 语句的格式几乎和 `ihu` 一模一样，因此直接复制下来即可（实际上你可以给 `if` 加一个返回值表示是否执行，然后在 `while` 中调用 `if` 也是可以的）。

有一点值得注意：`while` 语句的2个表达式的值都是可能改变的。
```cpp
void solvewhile(int& x) {
    int tmp = x, f1, f2;  // f1表示第一个','f2表示第二个','
    f1 = find(x, 6, len[x], ','), f2 = find(x, f1 + 1, len[x], ',');
    string s1 = getstr(x, 6, f1);
    int x1 = getExpression(x, f1 + 1, f2), x2 = getExpression(x, f2 + 1, len[x]);
    if (checkOp(s1, x1, x2)) {
        ++x;
        while (c[x][0] != '}') solve(x), ++x;
        solvewhile(tmp);
    } else {
        int lfsum = 1;
        ++x;
        while (lfsum) {
            if (c[x][0] == '{') ++lfsum;
            if (c[x][0] == '}') --lfsum;
            ++x;
        }
        --x;
    }
}
```
`hor` 实际上就是在 `while` 的基础上加了个初始值和不断自增而已。
```cpp
void runhor(int& x, int& v, int fl, int fr) {
    int tmp = x, f = getExpression(x, fl, fr);
    if (v <= f) {
        ++x;
        while (c[x][0] != '}') solve(x), ++x;
        ++v;
        runhor(tmp, v, fl, fr);
    } else {
        int lfsum = 1;
        ++x;
        while (lfsum) {
            if (c[x][0] == '{') ++lfsum;
            if (c[x][0] == '}') --lfsum;
            ++x;
        }
        --x;
    }
}
inline void solvehor(int& x) {
    int f1 = find(x, 4, len[x], ','), f2 = find(x, f1 + 1, len[x], ',');  // f1表示第一个','，f2表示第二个','
    int& num1 = getVariable(x, 4, f1) = getExpression(x, f1 + 1, f2);
    return runhor(x, num1, f2 + 1, len[x]);
}
```
## 其他

`vars` 语句就一行一行扫，然后看最后是不是 `]` 来确定是数组还是整形。
```cpp
inline void solvevar(int& pos) {
    ++pos;
    int f1, f2, f3;  //:的位置 ,的位置 .的位置
    string name;
    while (c[pos][0] != '}') {
        f1 = find(pos, 0, len[pos], ':');
        if (c[pos][len[pos] - 1] != ']') {
            tableint[getstr(pos, 0, f1)] = 0;
        } else
            f2 = find(pos, f1 + 1, len[pos], ','), f3 = find(pos, f2 + 1, len[pos], '.'), name = getstr(pos, 0, f1), tablearr[name].fir = stoint(pos, f2 + 1, f3), tablearr[name].pos = ++tot, tablearr[name].clear();
        ++pos;
    }
}
```
怎么样，是不是感觉只要一步一步把问题分解出来，难度也不大呢？

---

## 作者：a___ (赞：1)

首先，这个题看似复杂，其实本来没有多少内容，以我的声明部分为例：   
```cpp
namespace CYaRon
{
	void Error(const char *s){std::cerr<<s<<std::endl;exit(EXIT_FAILURE);}
	
	using siz_type=unsigned;
	using index_type=long long;
	using val_type=int;
	//读入输出
	class Input;
	class Output;
	//变量存储
	class Variable;
	class VarList;
	//语句块的读取与执行
	val_type read_expression(char);  //读取中缀表达式
	val_type& read_variable(char);   //读取变量（引用）
	bool read_con();                 //读取条件表达式
	bool read_vars();                //读取变量声明
	bool read_instruction();         //读取一条指令
	//读取与跳过指令
	void jump();
	void run();
}
```   
可以看到，整个程序实际需要实现的东西其实不多。   

_____

先整理一下题意：  
读入一个 $\texttt{CYaRon!}$ 语程序，输出其运行结果。    

需要实现的表达式：   
仅含 + - 的中缀表达式；   
条件表达式；   

需要实现的变量：   
仅含 `int` 的变量/数组；    

需要实现的指令：   
输出；   
赋值；    
判断；    
循环；   

需要注意的问题：   
变量；   
表达式；   
代码块。    
_____

首先讨论一下变量存储的问题。    
读进来的变量，要将其存储起来，并且能够修改和查询，我们需要通过某种东西来存储它们。    
存储器分两个：**变量**和**变量列表**。   
变量：一个长度为 $r-l+1$ 的**数组**（可用 `std::vector` 实现）。单个变量可以认为是长度为 $1$ 的数组。   
```cpp
class Variable:public std::vector<val_type>
{
	private:
    	int L,R;
	public:
    	Variable(){}
        Variable(index_type __minimum_index,index_type __maximun_index):
        	std::vector<val_type>(__maximun_index-__minimum_index+1,0),L(__minimum_index),R(__maximun_index){}
        val_type& operator[] (const index_type &x){if(x<L||x>R)throw "数组越界";return *(this->begin()+(x-L));}
};
```   
初始化函数为给定一个数组下标区间，生成一个相应的初值为 $0$ 的数组。     
重载操作符 `[]` 为返回变量引用，方便之后修改。    

由于本人刚开始脑子没转过来，以下是一个等价的动态分配内存实现：   
```cpp
class Variable
{
	private:
		val_type *data;
		siz_type len;
		index_type L,R;
	public:
		Variable(){data=NULL;}
		Variable(siz_type __len):len(__len),L(0),R(0){data=new val_type[1]();}
		Variable(index_type __minimum_index,index_type __maximun_index):
			len(__maximun_index-__minimum_index+1),L(__minimum_index),R(__maximun_index){data=new val_type[len]();}
		void set(index_type __minimum_index,index_type __maximun_index)
			{L=__minimum_index;R=__maximun_index;len=__maximun_index-__minimum_index+1;data=new val_type[len]();}
		~Variable(){if(data)delete[] data;}
		val_type& operator[] (const index_type &x){if(x<L||x>R)throw "数组越界";return data[x-L];}
};
```

变量列表：用来处理**变量名**与**变量**的对应关系（可用 `std::unordered_map` 实现）。     
```cpp
class VarList:public std::unordered_map<std::string,Variable>
{
	public:
		Variable& operator[] (const std::string &x)
		{
			auto it=this->find(x);
			if(it!=this->end())return it->second;
			throw "未定义变量";
		}
}varlist;
```    
同样，重载 `[]` 为返回引用便于修改。   
______
读入输出：     
这里是先把整个代码读进来再处理的方式，我就顺便用 `fread` `fwrite` 写了个快读快输。    
这里我们讲一下如何处理代码块嵌套的问题。我看有些大佬选择先得到代码块结尾位置或者建代码树，不过我选择回溯读取位置，递归实现的方式。   
考虑每个代码块的结尾一定是 `}` 或 `EOF` 。于是我们选择执行指令时一旦读到这两个字符就结束执行。如果读到当前指令需要新开代码块，那么就递归进入新代码块执行指令。     
简单来说，看伪代码：   
```
read_instruction()
	ch=该行第一个可视字符
    if ch=='}'||ch==EOF:return false
    if ch==':':执行指令
    if ch=='{':
    	在某种条件下:run()
    return true
run()
	while read_instruction()==true;
```  
碰到循环，我们需要回溯光标。所以我们要记一个光标。   
```cpp
class Input
{
	private:
		char buf[1000010];int t;//光标
	public:
		Input(){buf[fread(buf,1,1000000,stdin)]=EOF;t=0;}
		char get(){return buf[t++];}
		int getpos(){return t;}
		void setpos(int _t){t=_t;}//移动光标
}In;
class Output
{
	private:
		char buf[1000010];int t;
	public:
		Output():t(){}
		~Output(){if(t)fwrite(buf,1,t,stdout);}
        void putc(char c){buf[t++]=c;}
		void put(int a)//快写
		{
			char buf[20],len=0;
            if(a<0)putc('-'),a=-a;
            do buf[len++]=a%10+'0',a/=10; while(a);
            while(len)putc(buf[--len]);putc(' ');
		}
}Out;
``` 
____
表达式求值：   
我们以 `+` `-` 为分隔符，将整个表达式分为若干部分，每部分仅包含一个常数或一个变量。分类读取。读到分隔符就向下递归。    
```cpp
val_type read_expression(char end='\n')
{
	char ch=In.get();
	val_type sum=0;
	bool vis=false,type=false,typ1=false;
	std::string s;
	while(ch!=end)
	{
		if(ch==EOF)throw "非法字符";
		if(isgraph(ch)&&!isdigit(ch)&&!isalpha(ch)&&ch!='['&&ch!='+'&&ch!='-')throw "非法字符";
		if(typ1&&isgraph(ch)&&ch!='+'&&ch!='-')throw "非法字符";
		if(isgraph(ch)&&!vis)
			vis=true,type=isalpha(ch);//第一个字符判断类型
		if(isdigit(ch))
			if(!type)sum=sum*10+ch-'0';
			else s+=ch;
		else if(isalpha(ch))
			if(!type)throw "非法字符";
			else s+=ch;
		else if(ch=='[')
			if(!type)throw "非法字符";
			else sum=read_expression(']'),typ1=true;//递归读取下标
		else if(ch=='+')
			return (type?varlist[s][sum]:sum)+read_expression(end);//递归读取表达式下一部分（+）
		else if(ch=='-')
			return (type?varlist[s][sum]:sum)-read_expression(end);//同上（-）
		ch=In.get();
	}
	return type?varlist[s][sum]:sum;//变量/值
}
```
____
变量读取同理，就是记得要把返回值改为引用。   
```cpp
val_type& read_variable(char end)
{
	char ch=In.get();
	std::string s;int x=0;
	bool type=false;
	while(ch!=end)
	{
		if(ch==EOF)throw "非法字符";
		if(isgraph(ch)&&!isdigit(ch)&&!isalpha(ch)&&ch!='[')throw "非法字符";
		if(type&&isgraph(ch))throw "非法字符";
		if(isgraph(ch)&&ch!='[')
			s+=ch;
		else if(ch=='[')
			x=read_expression(']'),type=true;
		ch=In.get();
	}
	return varlist[s][x];
}
``` 
______
变量声明读取：     
直接按照 变量名：变量类型[左端点..右端点] 的格式读取。   
记得按照我们前面提到的，读到结束符返回 `false`。    
```cpp
bool read_vars()
{
	char ch;
	do ch=In.get(); while(!isgraph(ch));
	if(ch=='}')return false;
	std::string s,s1;
	int l=0,r=0;
	do s+=ch,ch=In.get(); while(isalpha(ch));//变量名
	while(ch!=':')ch=In.get();
	do ch=In.get(); while(!isgraph(ch));
	do s1+=ch,ch=In.get(); while(isalpha(ch));//类型
	if(s1[0]=='a')
	{
		while(ch!=',')ch=In.get();
		l=read_expression('.');
		ch=In.get();
		r=read_expression(']');
	}
	varlist.emplace(s,Variable());
	varlist[s].set(l,r);
    //如果是用的vector，这里直接emplace(s,Variable(l,r))就可以了
	return true;
}
``` 
_____
条件表达式：同上  
```cpp
bool read_con()
{
	std::string s;char ch;
	do ch=In.get(); while(!isgraph(ch));
	do s+=ch,ch=In.get(); while(isgraph(ch)&&ch!=',');
	while(ch!=',')ch=In.get();
	int x=read_expression(','),y=read_expression();
	switch(s[0]*200+s[1])
	{
		case 'l'*200+'t':return x<y;break;
		case 'g'*200+'t':return x>y;break;
		case 'l'*200+'e':return x<=y;break;
		case 'g'*200+'e':return x>=y;break;
		case 'e'*200+'q':return x==y;break;
		case 'n'*200+'e':return x!=y;break;
		default: throw "someting wrong";
	}
}
``` 
______
读取指令：同上（`return false`；递归执行；吃掉`'#'`）    
```cpp
bool read_instruction()
{
	char ch;
	do ch=In.get(); while((~ch)&&!isgraph(ch));
	if(ch==EOF||ch=='}')return false;//
	if(ch=='#'){while(ch!='\n')ch=In.get();return true;}//
	std::string s;
	do ch=In.get(); while(!isgraph(ch));
	do s+=ch,ch=In.get(); while(isgraph(ch));
	switch(s[0])
	{
		case 'v':while(read_vars());break;//vars
		case 'y':Out.put(read_expression());break;//yosoro
		case 's':{int &x=read_variable(',');x=read_expression();break;}//set
		case 'i':if(read_con())run();else jump();break;//ihu
		case 'h'://hor
		{
			int &x=read_variable(','),l=read_expression(','),r=read_expression(),pos=In.getpos();//获取循环变量即光标
			bool flg=false;
			for(x=l;x<=r;x++)//直接把循环变量从l到r自增
            In.setpos(pos),run(),flg=true;//回溯光标
			if(!flg)jump();
			break;
		}
		case 'w':{int pos=In.getpos();while(read_con())run(),In.setpos(pos);jump();break;}//while
		default:throw "错误语句";
	}
	return true;
}
```
______
跳过当前代码块：   
模拟括号匹配即可。    
```cpp
void jump(){int x=1;char ch;while(x){ch=In.get();if(ch=='{')++x;else if(ch=='}')--x;}}
```
_____
执行指令：
如上所述。     
```cpp
void run(){while(read_instruction());}
```
______
主函数：    
```cpp
int main()
{
	try
    {
        CYaRon::run();
    }
    catch(const char *e)
    {
        CYaRon::Error(e);//异常处理（写到后面写烦了，所以没怎么写异常处理，，，见谅）
    }
	return 0;
}
```
______
[完整代码（约 5KB）](https://www.luogu.com.cn/paste/rn8he6s7)     
_____
后记：    
~~A了这道题，祝你成功~~

---

