# Inverse Function

## 题目描述

Petya写了一个C++程序以计算一个很有意思的函数 $f(n)$。她给了一个输入值给这个程序，就跑去厨房喝茶了。当Petya回来时，程序已经计算出了结果。

然而她去喝茶时，一个狡猾的病毒把输入文件摧毁了！Petya现在没法知道她给了 $f(n)$ 什么值。所以，这个任务就交给你了！

Petya给你的程序由以下简化了的C++语法构成：

* 函数声明（$\text{function}$）：```int f(int n){operatorSequence}```；

* 语句序列（$\text{operatorSequence}$）：```operator```|```operator operatorSequence```（也就是说，$\text{operatorSequence}$可能是一个操作符，也可能在一个操作符后面还有其他的语句）；

* 操作符（$\text{operator}$）：```return arithmExpr```|```if(logicalExpr)return arithmExpr```；

* 逻辑表达式（$\text{logicalExpr}$）：```arithmExpr``` ```<```|```>```|```==``` ```arithmExpr```（即对两个数学表达式比较值的大小）；

* 数学表达式（$\text{arithmExpr}$）：```sum```；

* 求值结果（$\text{sum}$）：```product```|```sum+product```|```sum-product```；

* 乘积（$\text{product}$）：```multiplier```|```product*multiplier```|```product/multiplier```；

* 因数（$\text{multiplier}$）：
```n```|```number```|```f(arithmExpr)```（对这是一个递归函数。那个```n```就是你给这层调用传的参）

* 数字（$\text{number}$）: $n,n\in[0,2^{15})\cup\N$。（即 $0$ 至 $32767$ 间的任何整数。）

$\text{operatorSequence}$ 中的空白是可自定义的，只要能分开两个不同的东西即可。（和原来的C++一样。）

关于这些 $\text{operator}$（其实就只有```return```和```if```）的用途，和原来的C++一样，我就不再赘述。保证不会出现C++里其他的东西——循环、赋值语句、嵌套表达式，等等。函数声明中，除了参数变量```n```，不会有任何其他的变量。所有整数常量都在 $[0,2^{15})$ 间。

语句是有顺序地执行的。```return```语句被执行后，后面的语句不再执行。所有东西的优先级和标准C++一样。也就是说，先乘除后加减，等等。关系运算符含义与标准C++没有什么两样。

**现在请注意！这个程序使用** $\textbf{15-bit}$ **Berland C++编译器编译。也就是说，所有中间值请模** $\textbf{32768}$。（对于负数，想一想你做P1082时是怎么处理的。）**除法无论何时，都是整数除法，即余数会被忽略。**

一些例子：

$12345+23456=3033,0-1=32767,1024\times1024=0,1000/3=333$。

当然，无论这个函数的参数是多少，这个函数总能成功执行。也就是说：

* 永远不可能除以 $0$。

* 当这个函数被递归调用时，下一层的参数总小于这一层的参数。在这种情况下，函数不可能无限递归。

* 函数总会返回一个值。

还有，值得一提，$f(n)$ 的返回值只依赖于参数。这就是为什么 $f(n)$ 可以被视为数学意义上的函数——

>一般地，在一个变化过程中，如果有两个变量 $x$ 和 $y$，并且对于 $x$ 的每一个值，$y$ 都有一个唯一确定的值与其对应，那么我们就说 $x$ 是自变量（independent variable），$y$ 是 $x$ 的函数（function）。——八年级下册数学书

~~没错真正的题目只有一行，前面都是铺垫：~~

给定 $f(n)$，请求出 $n$。如果有多种可能，请选择最大的一种作为答案。

## 样例 #1

### 输入

```
17
int f(int n)
{
if (n &lt; 100) return 17;
if (n &gt; 99) return 27;
}
```

### 输出

```
99
```

## 样例 #2

### 输入

```
13
int f(int n)
{
if (n == 0) return 0;
return f(n - 1) + 1;
}
```

### 输出

```
13```

## 样例 #3

### 输入

```
144
int f(int n)
{
if (n == 0) return 0;
if (n == 1) return n;
return f(n - 1) + f(n - 2);
}```

### 输出

```
24588
```

# 题解

## 作者：DSCS2009 (赞：1)

# 分析:

显然我们需要制作一个简化版的解释性 $\text{C++}$ 的解释器。

注意到 $n\in[0,2^{15})$ 只有 $32768$ 种输入情况。

加入**记忆化**，记录每种 ``f(n)`` 的结果，就能将平均单次调用函数的复杂度缩减至 $O(1)$ ，

那么我们只需要写一个**大模拟**就能解决问题了。

直接模拟显然是不现实的，所以我们可以**从外往里**一层层模拟。

# 代码重要细节:

- 要注意**括号**的判断，

①如果一个 $\text{arithmExpr}$ 为 ``f(n / 2) + 1`` ，那么不判断括号将会得到 $\text{f(n}$ ， $\text{2)+}$ 和 $1$ 三项 $\text{multiplier}$。

②如果一个 $\text{operator}$ 为 ``if(f(f(f(0))) == 0) return 0`` ，那么在查找 $\text{logicalExpr}$ 时，你会得到 ``f(f(f(0)`` 而非 ``f(f(f(0))`` 。

- **负数**处理时并不需要困难的数学方法，

因为 $0-32767=-32767$ 是最小的负数可能情况，所以只需要将所有负数加 $32768$ 然后对 $32768$ 取模即可。

- $\text{product}$ 和 $\text{sum}$ 的运算符要**从后往前**找，否则 $-$ 或 $/$ 运算会出现要计算 $a-b+c-d$ 却计算成了 $a-(b+c-d)$ 的问题

- 大模拟**不太好调**，建议使用 $\text{Objective-C}$ 或**面向对象**的 $\text{C++}$，不要用 $abcd$ 命名变量。

- 枚举**输入参数**要**从小到大**，否则会**递归层数过多**炸栈。

# 代码：

~~不需要判断死循环，但是我没看见~~

```cpp
#include <bits/stdc++.h>

using namespace std;

const int NUM_MAX = 0x7fff, N = 1000005;
const int UNSOLVEABLE = NUM_MAX + 1;

class Interpreter {
	public:
		char code[N];
		int ret[NUM_MAX + 5];
		bool vis[NUM_MAX + 5];

		Interpreter(const char* _code = "\0") {
			memset(ret, -1, sizeof(ret));
			strcpy(code + 1, _code);
		}

		Interpreter operator=(const Interpreter& i) {
			memset(ret, -1, sizeof(ret));
			strcpy(code + 1, i.code + 1);
			return *this;
		}

		void init(const char* _code) {
			*this = Interpreter(_code);
		}

		int explainNumber(int argu, int l, int r) {
			int x;
			sscanf(code + l, "%d", &x);
			return x;
		}

		int explainMultiplier(int argu, int l, int r) {
			for (int i = l; i <= r; i++) {
				if (code[i] == 'n') return argu;
				if (code[i] == 'f') {
					//查找f(n)类的Multiplier的括号中的arithmExpr范围
					int bracLevel = 0, lBracPos = -1, rBracPos;
					for (int j = i + 1; j <= r; j++) {
						if (code[j] == '(' && lBracPos == -1) lBracPos = j;
						if (code[j] == '(') bracLevel++;
						if (code[j] == ')') bracLevel--;
						if (bracLevel == 0) { //判断括号层数
							rBracPos = j;
							break;
						}
					}
					int ariExp = explainArithmExpr(argu, lBracPos + 1, rBracPos - 1);
					if (ariExp == UNSOLVEABLE) return UNSOLVEABLE;
					return explainFunction(ariExp, 1, strlen(code + 1));
				}
			}
			return explainNumber(argu, l, r);
		}

		int explainProduct(int argu, int l, int r) {
			int opPos = -1, opType = 1, bracLevel = 0;
			//查找product中的操作符位置（要从后往前找）
			for (int i = r; i >= l; i--) {
				if (code[i] == ')') bracLevel++;
				if (code[i] == '(') bracLevel--;
				if (bracLevel == 0) {
					if (code[i] == '*') {
						opPos = i, opType = 1;
						break;
					}
					if (code[i] == '/') {
						opPos = i, opType = 2;
						break;
					}
				}
			}
			int product = 1;
			if (opPos != -1) {
				product = explainProduct(argu, l, opPos - 1);
				if (product == UNSOLVEABLE) return UNSOLVEABLE;
			} else opPos = l - 1;
			int mult = explainMultiplier(argu, opPos + 1, r);
			if (mult == UNSOLVEABLE) return UNSOLVEABLE;
			if (opType == 1) return (product * mult + NUM_MAX + 1) % (NUM_MAX + 1);
			return (product / mult + NUM_MAX + 1) % (NUM_MAX + 1);
		}

		int explainSum(int argu, int l, int r) {
			int opPos = -1, opType = 1, bracLevel = 0;
			//查找sum中的操作符位置（要从后往前找）
			for (int i = r; i >= l; i--) {
				if (code[i] == ')') bracLevel++;
				if (code[i] == '(') bracLevel--;
				if (bracLevel == 0) {
					if (code[i] == '+') {
						opPos = i, opType = 1;
						break;
					}
					if (code[i] == '-') {
						opPos = i, opType = 2;
						break;
					}
				}
			}
			int sum = 0;
			if (opPos != -1) {
				sum = explainSum(argu, l, opPos - 1);
				if (sum == UNSOLVEABLE) return UNSOLVEABLE;
			} else opPos = l - 1;
			int product = explainProduct(argu, opPos + 1, r);
			if (product == UNSOLVEABLE) return UNSOLVEABLE;
			if (opType == 1) return (sum + product + NUM_MAX + 1) % (NUM_MAX + 1);
			return (sum - product + NUM_MAX + 1) % (NUM_MAX + 1);
		}

		int explainArithmExpr(int argu, int l, int r) {
			return explainSum(argu, l, r);
		}

		int explainLogicalExpr(int argu, int l, int r) {
			int opBegin, opEnd, opType;
			//查找logicalExpr中的操作符位置
			for (int i = l; i <= r; i++) {
				if (code[i] == '<') {
					opBegin = opEnd = i;
					opType = 1;
					break;
				}
				if (code[i] == '>') {
					opBegin = opEnd = i;
					opType = 2;
					break;
				}
				if (code[i] == '=' && code[i + 1] == '=') {
					opBegin = i, opEnd = i + 1;
					opType = 3;
					break;
				}
			}
			int ari1Result = explainArithmExpr(argu, l, opBegin - 1);
			if (ari1Result == UNSOLVEABLE) return UNSOLVEABLE;
			int ari2Result = explainArithmExpr(argu, opEnd + 1, r);
			if (ari2Result == UNSOLVEABLE) return UNSOLVEABLE;
			if (opType == 1) return ari1Result < ari2Result;
			if (opType == 2) return ari1Result > ari2Result;
			return ari1Result == ari2Result;
		}

		int explainOperator(int argu, int l, int r) {
			for (int i = l; i <= r; i++) {
				if (code[i] == 'i' && code[i + 1] == 'f') { //带if的operator
					int logExpBegin = -1, bracLevel = 0, logExpEnd;
					for (int j = i; j <= r; j++) {
						if (code[j] == '(' && logExpBegin == -1) logExpBegin = j + 1;
						if (code[j] == '(') bracLevel++;
						if (code[j] == ')') bracLevel--;
						if (bracLevel == 0 && logExpBegin != -1) {
							logExpEnd = j - 1;
							break;
						}
					}
					int logResult = explainLogicalExpr(argu, logExpBegin, logExpEnd);
					if (logResult == 0 || logResult == UNSOLVEABLE) return UNSOLVEABLE;
					i = logExpEnd + 2;
				}
				if (code[i] == 'r' && code[i + 1] == 'e') { //带return的operator
					int ariEnd;
					for (int j = i + 6; j <= r; j++) {
						if (code[j] == ';') {
							ariEnd = j - 1;
							break;
						}
					}
					return explainArithmExpr(argu, i + 6, ariEnd);
				}
			}
			return UNSOLVEABLE;
		}

		int explainOperatorSequence(int argu, int l, int r) {
			if (l >= r) return UNSOLVEABLE;
			int opEnd, opResult;
			for (opEnd = l; opEnd <= r; opEnd++) {
				if (code[opEnd] == ';') break; //按;分割operatorSequence
			}
			if ((opResult = explainOperator(argu, l, opEnd)) != UNSOLVEABLE) return opResult;
			return explainOperatorSequence(argu, opEnd + 1, r);
		}

		int explainFunction(int argu, int l, int r) {
			if (vis[argu]) return UNSOLVEABLE;
			if (ret[argu] >= 0) return ret[argu];
			vis[argu] = true;
			int opSeqBegin, opSeqEnd;
			//查找operatorSequence的位置
			for (int i = l; i <= r; i++) {
				if (code[i] == '{') opSeqBegin = i + 1;
				if (code[i] == '}') {
					opSeqEnd = i - 1;
					break;
				}
			}
			return ret[argu] = explainOperatorSequence(argu, opSeqBegin, opSeqEnd);
		}

		int run(int want) {
			int codeLen = strlen(code + 1), ans = -1;
			for (int argu = 0; argu <= NUM_MAX; argu++) { //从前往后枚举输入参数
				memset(vis, 0, sizeof(vis));
				if (explainFunction(argu, 1, codeLen) == want) ans = max(ans, argu);
			}
			return ans;
		}
};

Interpreter intPre;
int want;
string code, s;

int main() {
	scanf("%d\n", &want);
	while (getline(cin, s)) code += s + " ";
	intPre.init(code.c_str());
	printf("%d\n", intPre.run(want));
	return 0;
}
```

Luogu提交记录：[R99706280](https://www.luogu.com.cn/record/99706280)

~~R1e8不远了吧~~

Codeforces提交记录：[submission189160878](https://codeforces.com/contest/39/submission/189160878)

---

