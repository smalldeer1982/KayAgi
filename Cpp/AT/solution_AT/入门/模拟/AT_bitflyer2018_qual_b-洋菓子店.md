# 洋菓子店

## 题目描述

你经营着一家西式糕点店。今天你准备了 $A$ 个草莓蛋糕和 $B$ 个芝士蛋糕。

已知今天将有 $N$ 位顾客光临你的糕点店。此外，每位顾客的行为可以用一个由 `S`、`C`、`E` 组成的长度为 $N$ 的字符串 $X$ 表示，具体如下：

- 如果 $X$ 的第 $i$ 个字符为 `S`，则第 $i$ 位到来的顾客会购买 $1$ 个草莓蛋糕。如果到达时草莓蛋糕已经售罄，则什么都不买。
- 如果 $X$ 的第 $i$ 个字符为 `C`，则第 $i$ 位到来的顾客会购买 $1$ 个芝士蛋糕。如果到达时芝士蛋糕已经售罄，则什么都不买。
- 如果 $X$ 的第 $i$ 个字符为 `E`，则第 $i$ 位到来的顾客会购买到达时剩余数量较多的那种蛋糕 $1$ 个。如果两种蛋糕都售罄，则什么都不买。如果两种蛋糕都剩余且数量相同，则购买 $1$ 个草莓蛋糕。

所有顾客离开后，请输出草莓蛋糕和芝士蛋糕各剩余多少个。

## 说明/提示

### 限制条件

- $0 \leq A, B \leq 10^5$
- $1 \leq N \leq 10^5$
- $|X| = N$
- $X$ 的每个字符都是 `S`、`C` 或 `E` 之一。

### 样例解释 1

前两位顾客购买了草莓蛋糕，最后一位顾客购买了芝士蛋糕。

### 样例解释 2

第 $3$ 位顾客无法购买任何蛋糕。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 3
SEC```

### 输出

```
1
1```

## 样例 #2

### 输入

```
2 4 6
SSSEEE```

### 输出

```
0
1```

## 样例 #3

### 输入

```
0 3 6
SEECEE```

### 输出

```
0
0```

## 样例 #4

### 输入

```
100 99 9
SSSEEECCC```

### 输出

```
96
94```

# 题解

## 作者：flysfy_LJX (赞：1)

纯纯模拟题，根据题意模拟即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n;
int main()
{
	cin >> a >> b >> n;
	for(int i=1;i<=n;i++)
	{
		char x;
		cin >> x;
		if(x=='S'&&a>0) a--;
		if(x=='C'&&b>0) b--;
		if(x=='E')
			if(a!=b&&a>b) a--;
			else if(a!=b&&a<b) b--;
			else if(a>0) a--;
	}
	cout << a << " " << b;
	return 0;
}
```


---

## 作者：Central_GYM (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_bitflyer2018_qual_b)
### 解题思路：
已知输入 $N$ 个字符，所以我们可以先定义 `char` 变量 $c$ 用来循坏输入，然后进行模拟即可。

### 模拟方法
本题模拟的是在 $N$ 次输入时 $A$ 和 $B$ 的值，对于每一次输入的 $c$ 应有以下三种情况：

1. 当 $c$ 为 `S` 且此时 $A > 0$ 时 $A-1$。
2. 当 $c$ 为 `C` 且此时 $B > 0$ 时 $B-1$。
3. 当 $c$ 为 `E` 时，当 $A \ne B$ 时 $\max(A,B)-1$，如果 $ A>0$ 且 $A=B$ 的话 $A-1$。

整理出所有情况就可以开始按照题目输入格式开始模拟了。
### 代码实现
```cpp:
#include<bits/stdc++.h>
using namespace std;
int main(){
		int a,b,n;
		string s;
		cin>>a>>b>>n;//按照格式输入a,b,n
		char c;
		for(int j=1;j<=n;j++){
			cin>>c;//循环输入字符  
			if(c=='S'&&a>0){
				a--;
			}
			if(c=='C'&&b>0){
				b--;
			}
			if(c=='E'){
				if(a!=b){
					a>b?a--:b--;//判断a,b谁大 
				}
				else{//反之a=b 
				if(a>0){
						a--;
					}
				}
			}
		}
		cout<<a<<endl<<b;//输出 
		return 0;
}


```


---

## 作者：QBY1617 (赞：0)

# 洋菓子店题解
## 题目梳理
给定两个自然数 $a$，$b$ 和一个字符串 $s$。让按照以下操作对 $a$ 和 $b$ 的值进行更改：

1. 当 $s_i$ 是 `S` 且 $a>0$，将 $a$ 的值减一
2. 当 $s_i$ 是 `C` 且 $b>0$，将 $b$ 的值减一
3. 当 $s_i$ 是 `E` 且 $a \ne b$，将 $a$ 和 $b$ 中较大的一个数减一；否则，若 $a > 0$，将 $a$ 减一。

所以，直接按照题意解题即可：
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,n;
	cin>>a>>b>>n;
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='S'&&a>0) a--;
		if(s[i]=='C'&&b>0) b--;
		if(s[i]=='E'){
			if(a!=b){
				if(a>b){
					a--;
				}
				else b--;
			}
			else{
				if(a>0) a--;
			}
		}
	}
	cout<<a<<"\n"<<b;
    return 0;
} 
```

---

## 作者：OcTar (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_bitflyer2018_qual_b)

题目大意就不用多说了吧，题面上已经给的很简洁了。

按照题意直接模拟即可，不过要注意两个问题：

- 判断字符 ``E`` 时不能直接用 ``else``，因为 $x$ 中可能有其他字符。（[rt](https://www.luogu.com.cn/record/118261316)）

- 题目中说 $x$ 的下标从 $1$ 开始，其实不用太在意，只要是从左往右依次判断就可以了。

再就是注意好判断时的细节就行了。

完整代码如下：

```cpp
#include <iostream>
#include <string> //头文件
using namespace std;
int a, b, n;
string s;
int main() {
	cin >> a >> b >> n;
	cin >> s;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'S' && a > 0) {
			a--;
		} else if (s[i] == 'C' && b > 0) {
			b--;
		} else if (s[i] == 'E') {
			if (a != b) {
				if (a > b) {
					a--;
				} else {
					b--;
				}
			} else if (a > 0) {
				a--;
			}
		}
	}
  //别忘了要换行输出
	cout << a << endl << b << endl;
	return 0;
}
```


---

## 作者：Flying_Eagle (赞：0)

### 题目思路
这道题只需按照题意模拟即可，重点是如何存储这个字符串。

#### 第一种方法

我们可以用一个字符数组存储，挨个输入即可。

#### 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int a, b, n;
char s[100005];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> a >> b >> n;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	for (int i = 0; i < n; i++) {
		if (s[i] == 'S' && a > 0)
			a--;
		if (s[i] == 'C' && b > 0)
			b--;
		if (s[i] == 'E') {
			if (a != b) {
				if (a >= b)
					a --;
				else
					b --;
			} else {
				if (a > 0) {
					a --;
				}
			}
		}
	}
	cout << a << endl << b;
	return 0;
}
```
#### 第二种方法

我们可以用 `string` 存储，这样我们直接可以用 `cin` 输入了。

#### 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int a, b, n;
string s;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> a >> b >> n;
	cin >> s;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'S' && a > 0)
			a--;
		if (s[i] == 'C' && b > 0)
			b--;
		if (s[i] == 'E') {
			if (a != b) {
				if (a >= b)
					a --;
				else
					b --;
			} else {
				if (a > 0) {
					a --;
				}
			}
		}
	}
	cout << a << endl << b;
	return 0;
}
```


---

## 作者：LYJ_B_O_Creation (赞：0)

题目思路：
-
对于这道题，我们从左往右枚举字符串的每一位，再按照题目要求模拟即可。其中，我们要小心的是，$a$ 和 $b$ 是否为 $0$，因为 $0$ 的情况是不需要操作的。

- 注意，判断 $x_i$ 是否等于 `E` 时不能直接用 `else` 得用 `else if` 判断，因为输入的字符串中有可能包括其他字符。

题目代码：
-
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int a , b , n;
	cin >> a >> b >> n;
	string x;
	cin >> x;
	for(int i = 0;i < x . size();i++)
	{
		if(x[i] == 'S' && a > 0) a -= 1;
		else if(x[i] == 'C' && b > 0) b -= 1;
		else if(x[i] == 'E')
		{
			if(a != b)
			{
				if(a >= b) a -= 1;
				else b -= 1;
			}
			else
			{
				if(a > 0)
				{
					a -= 1;
				}
			}
		}
	}
	cout << a << endl << b;
	return 0;
}
```

---

