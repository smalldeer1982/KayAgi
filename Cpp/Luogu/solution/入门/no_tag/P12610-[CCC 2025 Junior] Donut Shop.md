# [CCC 2025 Junior] Donut Shop

## 题目背景

本题满分 15 分。

## 题目描述

一家甜甜圈商店的店主整天都在烘焙和销售甜甜圈。

根据一天中发生的事件，你的任务是计算商店关门时剩余的甜甜圈数量。

![](https://cdn.luogu.com.cn/upload/image_hosting/3n3cysdu.png)

## 说明/提示

**样例输入 1 的输出解释**

商店开门时有 $10$ 个甜甜圈，当天发生了 $3$ 个事件。店主首先烘焙了 $24$ 个甜甜圈，然后售出了 $6$ 个，接着又售出了 $12$ 个。剩余的甜甜圈数量为 $10 + 24 - 6 - 12 = 16$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
10
3
+
24
-
6
-
12```

### 输出

```
16```

# 题解

## 作者：Evan2000 (赞：1)

## 思路

首先我们可以定义一个变量 $flag$，如果遇到加号，$flag$ 变成 $1$，如果遇到减号，$flag$ 变成 $-1$，如果遇到数字，那么用一个变量 $num$ 记录这个数字是什么，然后将 $D$ 加上 $num \times flag$，最后输出 $D$ 即可。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char s[20];
signed main()
{
	int d,q;
	scanf("%lld%lld",&d,&q);
	int flag=1;
	q*=2;
	while(q--)
	{
		scanf("%s",s+1);
		if(s[1]=='+')
		{
			flag=1;
		}
		else if(s[1]=='-')
		{
			flag=-1;
		}
		else
		{
			int len=strlen(s+1);
			int num=0;
			for(int i=1;i<=len;i++)
			{
				num=num*10+s[i]-'0';
			}
			d+=num*flag;
		}
	}
	printf("%lld",d);
	return 0;
}
```

---

## 作者：wangziyang202511036 (赞：1)

# 题解：P12610 [CCC 2025 Junior] Donut Shop  
## 题目大意  
[题目传送门](https://www.luogu.com.cn/problem/P12610)  
给出一个初始值 $D$ 和事件数量 $E$，每次事件给出 $D$ 的变化值及值的符号，求 $D$ 最后的值。
## 思路  
直接模拟即可。每次事件判断符号，如果是则加上正数，否则加上负数，最后输出答案。
## 部分代码
由于题目非常简单，只给出部分代码。  

```cpp
while(E--)
{
        char c;
		int num;
		cin>>c;
		cin>>num;
		d+=c=='+'?num:(-num);
}
cout<<d;
```

---

## 作者：jur10n (赞：1)

## Problem

你有 $D$ 个甜甜圈，共有 $E$ 个甜甜圈的变化事件，每个事件有两种可能的情况：增加或者减少 $Q$ 个甜甜圈。

求剩余的甜甜圈数量。

## Solution

对于每个事件，对甜甜圈的初始数 $D$ 加或减每个对应的 $Q$ 即可。

那么最终 $D$ 的值即为所求结果。

用循环结构简单模拟就可以，每次输入判断是加还是减法，直接对 $D$ 进行运算即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int d, e, q;
char c;
signed main()
{
	cin >> d >> e;
	for (int i = 1; i <= e; i++)
	{
		cin >> c >> q;
		if (c == '+') d += q;
		else d -= q;
	}
	cout << d;
}
```

---

## 作者：GSQ0829 (赞：1)

~~样例的最后一行把 $12$ 打成 $1$ 了。~~

---
### 解题思路：
只要判断每次输入的符号是 `+` 还是 `-` 即可。如果是 `+`，那么总甜甜圈数加上输入的个数。否则就减去输入的个数。这道题目因为样例的问题所以使我想了好久自己代码的问题，最后提交上去是对的，我直接懵了。希望有人能把样例最后一行的 $1$ 改成 $12$。

---
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int d, e, k;
char c;

int main () {
	cin >> d >> e;
	while (e--) {
		cin >> c >> k;
		if (c == '+') d -= k;
		else d += k;
	}
	cout << d;
	return 0;
}
```

---

## 作者：Vct14 (赞：0)

直接模拟即可。对于一个事件，若输入为 `+`，则将当前甜甜圈数量加上 $q$，否则减去 $q$。时间复杂度 $O(e)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int d;cin>>d;
    int e;cin>>e;
    while(e--){
        char c;cin>>c;
        int q;cin>>q;
        if(c=='+') d+=q;
        else d-=q;
    }
    cout<<d;
	return 0;
}
```

---

## 作者：Chase12345 (赞：0)

考察简单输入输出、循环结构、简单字符。

循环 $c$ 次，每次判断字符是哪一个，分别处理即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int d, T;
    cin >> d >> T;
    while (T--) {
        char op;
        int a;
        cin >> op >> a;
        if (op == '+')
            d += a;
        else
            d -= a;
    }
    cout << d << '\n';
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12610)
## 题目分析
希望审核大大给过。

一眼望去，一道模拟题。一次可以输入**一个字符**和**一个整数**，并且判断字符为 `+` 还是 `-`，并在原有 $D$ 中进行操作即可。

以下是代码。
## 题目[代码](https://www.luogu.com.cn/record/218550578)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
int d,e;
signed main() {
	speed
	cin>>d>>e;
	while(e--){
		char c;
		int a;
		cin>>c>>a;
		if(c=='+')d+=a;
		else d-=a;
	}
	cout<<d;
	return 0;
}
```

---

## 作者：pour_demain (赞：0)

还是简单模拟，先输入原有数量，再输入操作数，每次有两种操作，直接在原有的数量上进行更改即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int D;
	cin >> D;
	int E;
	cin >> E;
	while(E--){
		char op;
		cin >> op;
		int q;
		cin >> q;
		D += ((op == '+')?q:(0-q));//减去这个数等于加上它的相反数。
	}
	cout << D << endl;
	return 0;
}
``````

---

