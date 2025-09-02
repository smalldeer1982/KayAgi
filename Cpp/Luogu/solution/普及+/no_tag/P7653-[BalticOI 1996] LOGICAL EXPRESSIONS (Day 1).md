# [BalticOI 1996] LOGICAL EXPRESSIONS (Day 1)

## 题目描述

有五个逻辑表达式，称为 R1、R2、R3、R4、R5。只有逻辑变量 $a、b、c、d、e、f、g、h$，逻辑运算  
`#（not）`  
`&（and）`  
`+（or）`  
和圆括号可以在表达式中使用。操作的优先级如上所述。可以使用圆括号定义执行操作的不同顺序。  
操作由这样的表定义  
![Biao](https://cdn.luogu.com.cn/upload/image_hosting/ilfi8gbz.png)  
假设有一些表达式可以通过带有一个或两个参数的单个逻辑运算来表达：  
- $R_i = R_j$（$R_i$ 等价于 $R_j$，即对于每组变量值，$R_i$ 给出与 $R_j$ 相同的值）；  
- $R_i =$ # $R_j$（$R_i$ 等价于 $R_j$ 的否定）；  
- $R_i = R_j $ &  $R_k  $（结合）;  
- $R_i = R_j + R_k$（分离）；其中（$i≠k，i≠j$）。  

一组基本的表达式是通过它可以表示（表达）未包含在该组中的任何其他表达式，如上定义。  
编写一个程序来查找：   
1. 任何最不基本的表达式集；   
1. 每个表达式的任何表示（表达）（不属于表达式的基本集合）。应该使用带有一个或两个参数的任何单个逻辑运算来获得表示，即来自基本集合的表达式。

## 说明/提示

#### 分值说明  
本题分值按 BOI 原题设置，**满分** $30$ 。
#### 题目说明  
来源于 Baltic Olympiad in Informatics 1996 的 [Day 1:LOGICAL EXPRESSIONS](https://boi.cses.fi/files/boi1996_day1.pdf) 。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
a&(b&b) 
c+c
a&b+c
#a
a&b ```

### 输出

```
R1
R2
R4
R3=R1+R2
R5=R1 ```

# 题解

## 作者：steambird (赞：0)

## 思路

设 $m$ 是变量个数，$n$ 是表达式个数，$L$ 是表达式的平均长度，则根据题意恒有 $m \le 8, n = 5, L \le 256$。

注意到只有有限个逻辑变量，同时它们的值只可能为真或假，所以判断等式是否成立完全可以枚举所有可能的逻辑变量状态并判断它们是否在这些状态下都相等，总状态数为 $2^m$。

根据题目输出解的要求，需要枚举哪些式子是基本表达式。每个式子只有是基本表达式和不是基本表达式两种状态，总状态数为 $2^n$。判断一种状态是否能成立时，只需要判断所有不是基本表达式的式子 $i$ 能否都存在对应的基本表达式 $j$ 和 $k$ 使得某一种等式成立，需要枚举 $n^3$ 次。

根据题目，只有四种等式：

- $R_i = R_j$ 
- $R_i =$ # $R_j$
- $R_i = R_j $ &  $R_k  $
- $R_i = R_j + R_k$

对这四种情况分别考虑即可。

接下来是计算表达式的值的问题。可以用两个栈分别记录运算符与数值，遇到数值时进数值栈，遇到运算符时弹出并计算（即弹出运算符并弹出相应数量的数值，再将计算结果压入数值栈）优先级较高的运算符，遇到左括号则入栈，遇到右括号则弹出并计算运算符直到左括号，则最终数值栈中的唯一元素即为结果。

总时间复杂度为 $O(2^m \times 2^n \times n^3 \times L)$，且由于其中存在大量剪枝，代码不会超时。

## 代码

```c++
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
using namespace std;

constexpr int R = 5;
string rs[R];

inline void train() {
	   ios::sync_with_stdio(false);
	   cin.tie(0);
	   cout.tie(0);
}

int priority(char i) {
	switch (i) {
		case ')':
			return 4;
			break;
		case '#':
			return 3;
			break;
		case '&':
			return 2;
			break;
		case '+':
			return 1;
			break;
		case '(':
			return 0;
			break;
		default:	// -1 priority is usually for special uses
			return -1;
			break;
	}
}

inline void autopop(char i, stack<char> &op, stack<bool> &val) {
	bool res1, res2, res;
	while ((!op.empty()) && (priority(op.top()) >= priority(i))) {
		char t = op.top();
		switch (t) {
			case ')':
				break;
			case '(':
				if (i == ')') {
					op.pop();
					return;
				}
				break;	// Do nothing
			case '#':
				res = val.top();
				val.pop();
				val.push(!res);
				break;
			case '&':
				res2 = val.top();
				val.pop();
				res1 = val.top();
				val.pop();
				val.push(res1 && res2);
				break;
			case '+':
				res2 = val.top();
				val.pop();
				res1 = val.top();
				val.pop();
				val.push(res1 || res2);
				break;
		}
		op.pop();
	}
}

bool evaluate(string expr, map<char, bool> vals) {
	stack<char> op;
	stack<bool> val;
	for (auto &i : expr) {
		if (i >= 'a' && i <= 'h') {
			// Variable.
			val.push(vals[i]);
		} else {
			switch (i) {
				case '(':
					op.push('(');
					break;
				default:
					autopop(i, op, val);
					op.push(i);
			}
		}
	}
	autopop(' ', op, val);
	return val.top();
}

bool is_sames(string as, string bs, char op = '=', string cs = "") {
	for (int a = 0; a <= 1; a++) {
		for (int b = 0; b <= 1; b++) {
			for (int c = 0; c <= 1; c++) {
				for (int d = 0; d <= 1; d++) {
					for (int e = 0; e <= 1; e++) {
						for (int f = 0; f <= 1; f++) {
							for (int g = 0; g <= 1; g++) {
								for (int h = 0; h <= 1; h++) {
									map<char, bool> mp = {{'a', a}, {'b', b}, {'c', c}, {'d', d}, {'e', e}, {'f', f}, {'g', g}, {'h', h}};
									bool aexpr = evaluate(as, mp);
									bool bexpr = evaluate(bs, mp);
									bool cexpr;
									switch (op) {
										case '=':
											if (aexpr != bexpr) return false;
											break;
										case '#':
											if (aexpr == bexpr) return false;
											break;
										case '&':
											cexpr = evaluate(cs, mp);
											if (aexpr != (bexpr && cexpr)) return false;
											break;
										case '+':
											cexpr = evaluate(cs, mp);
											if (aexpr != (bexpr || cexpr)) return false;
											break;
									}
//									if (aexpr != bexpr) return false;
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}

int stdmin = 114514, solu = -1;
vector<string> stdans;

int main() {

	train();
	
	for (int i = 0; i < 5; i++) cin>>rs[i];
	for (int i = 0; i < (1<<5); i++) {	// i bit 1: as stanard. i bit 0: not as stanard
		// You expect the smallest 1 counter
		
		vector<string> advanced;
		int stdcnt = 0;
		bool ok = true;
		for (int j = 0; j < 5; j++) {
			if ((1<<j) & i) {
				stdcnt++;
			} else {
				bool success = false;
				for (int s1 = 0; s1 < 5; s1++) {
					if ((1<<s1) & i) {
						if (is_sames(rs[j], rs[s1])) {
							advanced.push_back(string("R")+to_string(j+1)+string("=R")+to_string(s1+1));
							success = true;
							break;
						}
						if (is_sames(rs[j], rs[s1], '#')) {
							advanced.push_back(string("R")+to_string(j+1)+string("=#R")+to_string(s1+1));
							success = true;
							break;
						}
						bool flag = false;
						for (int s2 = 0; s2 < 5; s2++) {
							if ((1<<s2) & i) {
								if (is_sames(rs[j], rs[s1], '&', rs[s2])) {
									advanced.push_back(string("R")+to_string(j+1)+"=R"+to_string(s1+1)+"&R"+to_string(s2+1));
									flag = true;
									break;
								}
								if (is_sames(rs[j], rs[s1], '+', rs[s2])) {
									advanced.push_back(string("R")+to_string(j+1)+"=R"+to_string(s1+1)+"+R"+to_string(s2+1));
									flag = true;
									break;
								}
							}
						}
						if (flag) {
							success = true;
							break;
						}
					}
				}
				if (!success) {
					ok = false;
					break;
				}
			}
		}
		if (ok) {
			if (stdcnt < stdmin) {
				stdmin = stdcnt;
				solu = i;
				stdans = advanced;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (solu & (1<<i)) cout<<"R"<<(i+1)<<"\n";
	}
	for (auto &i : stdans) cout<<i<<"\n";
	
	cout<<flush;

	return 0;
}
```

---

