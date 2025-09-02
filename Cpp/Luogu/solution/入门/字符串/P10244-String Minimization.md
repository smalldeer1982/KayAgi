# String Minimization

## 题目描述

你有四个长 $n$ 的字符串 $a,b,c,d$。你可以执行任意多次如下操作：

- 选择一个 $i$，交换 $a_i,c_i$，然后交换 $b_i,d_i$。

求在 $a$ 的字典序尽量小的前提下，$b$ 字典序最小是什么。

---

如果你不知道什么是字典序，看这里：

对于两个字符串 $p,q$，称 $p$ 的字典序小于 $q$（记为 $p<q$），当且仅当存在**自然数** $k$ 使 $p,q$ 的前 $k$ 个字符相同且 $p_{k+1}$ 的 ASCII 码小于 $q_{k+1}$ 的 ASCII 码。

例如：
- $\texttt{abc}<\texttt{baa}$（当 $k=0$）
- $\texttt{bae}<\texttt{bbb}$（当 $k=1$）

## 说明/提示

【样例解释】

选择 $i$ 为 $1,3,4$ 可以让 $a$ 取到最小的字典序 $\texttt{weablake}$，此时字符串 $b$ 也得到满足题意最小的字典序 $\texttt{auazyqaq}$。

事实上如果 $i=1$ 时不操作 $a$ 的字典序也是最小的，但是此时字符串 $b$ 就是 $\texttt{yuazyqaq}$，不够小。

【数据范围】

本题共 $10$ 个测试点，每个测试点 $10$ 分。

|测试点编号|$n\le$|特殊性质|
|:-:|:-:|:-:|
|$1\sim 2$|$15$||
|$3$|$10^5$|$a_i>c_i$|
|$4\sim 5$|$10^5$|$a_i\ne c_i$|
|$6\sim 7$|$10^5$|$b_i\ge d_i$|
|$8\sim 10$|$10^5$||

对于全体数据，保证 $1\le n\le 10^5$，字符串所有字符都是小写字母。

## 样例 #1

### 输入

```
8
westlake
yummyqaq
weabzzke
azazazaq
```

### 输出

```
auazyqaq```

# 题解

## 作者：yummy (赞：17)

# A. String Minimization

本题涉及的主要知识点：

- 【2】字符串
- 【3】贪心法

### 题意分析

题目要在 $a$ 字典序尽量小的前提下求 $b$ 字典序最小值，所以先考虑 $a$ 什么时候字典序最小。

不难发现 $a$ 的两个不同位置之间没什么关系（$a_i$ 不管是否进行操作都不会产生 $a_j$，如果 $i\ne j$），所以我们只需要把**每个字符**都求出最小值即可。

总而言之：

- 若 $a_i<c_i$，则不能对 $i$ 操作。
- 若 $a_i>c_i$，则必须对 $i$ 操作。
- 若 $a_i=c_i$，则是否操作都可以。

接下来考虑最小化 $b_i$。若 $a_i\ne c_i$ 则是否操作已经确定，只有 $a_i=c_i$ 时，才会考虑“若 $b_i>d_i$ 则交换"。

总之，若 $a_i>c_i$，或者 $a_i=c_i$ 且 $b_i>d_i$，则必须交换 $b_i,d_i$。


### 参考程序

以下为 C++ 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a,b,c,d;
int main(){
	cin>>n>>a>>b>>c>>d;
	for(int i=0;i<n;i++)
		if(a[i]>c[i] || a[i]==c[i] && b[i]>d[i])
			b[i]=d[i];
	cout<<b<<endl;
	return 0;
}
```

以下为 Python 3 参考代码。注意 Python 的字符串不能原地修改，必须转化成列表。

```python
n=int(input())
a=input()
b=list(input())
c=input()
d=input()
for i in range(n):
    if a[i]>c[i] or a[i]==c[i] and b[i]>d[i]:
        b[i]=d[i]
print("".join(b))
```

---

## 作者：Trista_ (赞：5)

# 洛谷 P10244 题解

[题目传送门](https://www.luogu.com.cn/problem/P10244)

## 题目算法

模拟

## 题目思路

想 AC 此题需要完成 2 件事情：让 $a$ 字典序最小，让 $b$ 的字典序尽可能小。\
以下是详解。

---
### 让 $a$ 字典序最小

题目中，可以选择一个 $i$，在交换 $a_i$ 和 $c_i$ 的同时 交换 $b_i$ 和 $d_i$。\
又因为我们想让 $a$ 的字典序 **最小**，\
所以我们需要 **在当 $a_i$ 的字典序 $>$ $c_i$ 的字典序 时**，交换 $a_i$ 和 $c_i$。

**代码：**

```python
if ord(a[i]) > ord(c[i]):
	a[i],c[i] = c[i],a[i]
	b[i],d[i] = d[i],b[i]
```
---
### 让 $b$ 的字典序尽可能小

题目中，可以选择一个 $i$，在交换 $a_i$ 和 $c_i$ 的同时 交换 $a_i$ 和 $c_i$，$b_i$ 和 $d_i$。\
因为 $a$ 的字典序要保持最大，\
所以 **要在不让 $a$ 的字典序变小（即 $a_i$ 的字典序 $\ge$ $c_i$ 的字典序）的情况下，让 $b$ 的字典序尽可能大。即 $b_i$ 的字典序 $>$ $d_i$ 的字典序 的情况下**，交换 $a_i$ 和 $c_i$，$b_i$ 和 $d_i$\
由于 $a_i$ 的字典序 $>$ $c_i$ 的字典序 的情况我们之前已经讨论过，\
所以，简而言之，**在$a_i$ 的字典序 $=$ $c_i$ 的字典序 且 $b_i$ 的字典序 $>$ $d_i$ 的字典序 的情况下**，交换 $a_i$ 和 $c_i$，$b_i$ 和 $d_i$\
交换 $b_i$ 和 $d_i$。

**代码：**

```python
if a[i] == c[i] and ord(b[i]) > ord(d[i]):
	b[i],d[i] = d[i],b[i]
```
## 代码
附上我赛时代码，和 [赛时 AC 记录](https://www.luogu.com.cn/record/150210123)，~~代码较丑不喜勿喷~~。

```python
cnt = int(input())
a = list(input())
b = list(input())
c = list(input())
d = list(input())
for i in range(cnt):
    if ord(a[i]) > ord(c[i]):
        a[i],c[i] = c[i],a[i]
        b[i],d[i] = d[i],b[i]
    if a[i] == c[i] and ord(b[i]) > ord(d[i]):
        b[i],d[i] = d[i],b[i]
print(''.join(b))
```

---

## 作者：PR_CYJ (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/P10244)
# 思路
这道题很简单。

因为在 $a$ 的字典序尽量小的前提下，$b$ 的字典序要最小。所以我们遍历字符串 $a$，用贪心的思路，如果 $a_i>c_i$，就交换；如果 $a_i=c_i$，这时交不交换都不会对 $a$ 的字典序产生影响，所以就考虑 $b_i$ 和 $d_i$，如果 $b_i>d_i$ 就交换，否则就不交换；而当 $a_i<c_i$ 时，就不交换。
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	string a,b,c,d;
	cin>>a>>b>>c>>d;
	for(int i=0;i<n;i++)
		if (a[i]>c[i])
		{
			swap(a[i],c[i]);
			swap(b[i],d[i]);
		}
		else if (a[i]==c[i])
			if (b[i]>d[i])
				swap(b[i],d[i]);
	cout<<b<<endl;
}
```

---

## 作者：IGA_Indigo (赞：5)

## 题目大意
给你四个字符串，每次可以进行一次操作：选择一个下标 $i$，将 $a_i$ 与 $c_i$ 交换，$b_i$ 和 $d_i$ 交换。求 $a$ 字典序最小时 $b$ 字典序最小的情况。
## 大体思路
因为 $a$ 的最小值只有一种情况，所以我们需要考虑在换了$a_i$ 与 $c_i$ 之后 $a_i$ 字典序不变的情况使 $b_i$ 最小的情况。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	string a,b,c,d;
	cin>>a>>b>>c>>d;//四个字符串 
	for(int i=0;i<n;i++){//注意string从0开始存 
		if(a[i]==c[i]){//如果换了之后a没变化 
			if(b[i]>d[i]){//就考虑b换了之后会不会更小 
				char t=b[i];
				b[i]=d[i];
				d[i]=t;//更小就交换 
			}
		}
		else if(a[i]>c[i]){//换了之后a变小就就必须换 
			char t=a[i];
			a[i]=c[i];
			c[i]=t;
			t=b[i];//连着b和d一起换 
			b[i]=d[i];
			d[i]=t;
		}
	}
	cout<<b;//直接输出答案即可 
	return 0;
}
```

---

## 作者：wangcht (赞：3)

由题意，我们首先要保证 $a$ 的字典序最小，那么可以依次比较 $a_i$ 和 $c_i$ 的大小。

显然：

- 若 $a_i$ 大于 $c_i$，必须进行交换。

- 若 $a_i$ 小于 $c_i$，不能进行交换。

- 若 $a_i$ 等于 $c_i$，此时是否交换不会影响 $a$ 的字典序大小，如果 $b_i$ 小于 $d_i$，那么应当进行交换，这样也保证了 $b$ 的字典序尽可能小。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a,b,c,d,ans;
int main()
{
    ios::sync_with_stdio(0);
    cin>>n;
    cin>>a>>b>>c>>d;
    for(int i=0;i<n;i++)
    {
        if(a[i]>c[i]) 
        {
            a[i]=c[i];
            b[i]=d[i];
        }
        else if(a[i]==c[i] && b[i]>d[i])
        {
            b[i]=d[i];
        }
    }
    cout<<b;
    return 0;
}
```

---

## 作者：Naoxiaoyu (赞：3)

## 题意
给出 $4$ 个字符串 $a,b,c,d$。

对于每个 $a_i,b_i,c_i,d_i$，可以交换 $a_i$ 和 $c_i$，$b_i$ 和 $d_i$，要求在保证字符串 $a$ 字典序最小的情况下使字符串 $b$ 字典序最小。

## 思路
从 $0$ 到 $n-1$ 遍历字符串。\
对于字符串 $a$，每次比较 $a_i$ 与 $c_i$。
- 若 $a_i>c_i$，则交换 $a_i$ 和 $c_i$，$b_i$ 和 $d_i$。
- 若 $a_i=c_i$，则考虑 $b_i$，**在 $b_i>d_i$ 时**交换 $a_i$ 和 $c_i$，$b_i$ 和 $d_i$。
- 若 $a_i>c_i$，则不变。

其实代码中不需要对字符串 $a,b,c$ 进行处理，最后输出字符串 $b$ 即可。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
char a[N],b[N],c[N],d[N];
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s%s%s%s",a,b,c,d);
	for(int i=0;i<=n-1;i++)
	{
		if(a[i]>c[i])
			swap(b[i],d[i]);
		else if(a[i]==c[i] && b[i]>d[i])
			swap(b[i],d[i]);
	}
	printf("%s",b);
	return 0;
}
```

---

## 作者：zhouzihang3 (赞：2)

简简单单的贪心题，**要求 $a$ 的字典序最小**，就把 $a_i$ 和 $c_i$ 对比一下，取字典序最小值。当 $a_i=c_i$ 时，就需要考虑 $b_i$ 和 $d_i$ , $b_i$ 取字典序最小的字符，这样 $b$ 的字典序能够尽可能小。

因为只需要输出 $b$ ，所以可以不改变其他字符串。

```
#include<bits/stdc++.h>
#define ll long long
#define str string
using namespace std;
int read(){
	char c;
	int x=0,f=1;
	c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x*=10;
		x+=c-'0';
		c=getchar();
	}
	return f*x;
}
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return;
}
//缺省源，以下为正文部分
int n;
string a,b,c,d;
char l; 
int main(){
	cin>>n;
	cin>>a>>b>>c>>d;
	for(int i=0;i<n;i++){
		if(a[i]>c[i]){
			b[i]=d[i];
		}else if(a[i]==c[i]){
			if(b[i]>d[i]){
				b[i]=d[i];
			}
		}
	}
	cout<<b;
	return 0;
}

```

---

## 作者：x1489631649 (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/P10244)
# 输入
1. 一个数 $l(1 \le l \le 10^5)$ 代表下列四个字符串的长度。
1. 长度都相等的四个字符串 $a \sim d$。
# 输出
1. 字符串 $a$ 要尽量小。（第一个要求）
1. 字符串 $b$ 在**满足第一个条件**的情况下尽量小。（第二个要求）
# 题意
用一个变量 $i$ 来枚举每一个字符 $（0 \le i \le l-1）$,按照两个要求来分析每一种情况，且**第一个要求的优先级大于第二个要求**。
1. 当 $a_i < c_i$ 时,选择不交换。
1. 当 $a_i > c_i$ 时,选择交换$a_i$ 和 $c_i$与 $b_i$ 和  $d_i$。
1. 当 $a_i = c_i$ 时,又分为两种情况：
- 当 $b_i \le d_i$ 时,选择不交换。
- 当 $b_i > d_i$ 时,选择交换$a_i$ 和 $c_i$与 $b_i$ 和  $d_i$。

**到这里情况的分析就结束了。**
# $Code$

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int l;
	cin>>l;
	string a,b,c,d;
	cin>>a>>b>>c>>d;
	for(int i=0;i<l;i++)
	{
		if(a[i]>c[i])
		{
			swap(a[i],c[i]);
			swap(b[i],d[i]);
		}
		if(a[i]==c[i]&&b[i]>d[i])
		{
			swap(a[i],c[i]);
			swap(b[i],d[i]);
		}
	}
	cout<<b;
}
```

---

## 作者：RainCQwQ (赞：2)

# P10244 Solution
## 思路整理
可以直接像题目说的一样，先保证 $a$ 的字典序最小，再使 $b$ 当不会对 $a$ 产生影响（即 $a_i = c_i$）时的字典序尽量小。

------------
## AC Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	int n;
	cin>>n;
	string a,b,c,d;
	cin>>a>>b>>c>>d;
	for(int i=0;i<n;i++)
	{
		if(a[i]>c[i]) swap(a[i],c[i]),swap(b[i],d[i]);
		if(a[i]==c[i]) if(b[i]>d[i]) swap(a[i],c[i]),swap(b[i],d[i]);
	}
	cout<<b<<endl;
	return 0;
}
```

---

## 作者：tanzexiaodezhonghao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10244)
## 思路
本题就是让你求 $a$ 字典序最小时的 $b$，毕竟他说在 $a$ 的字典序尽量小的前提下。接下来就做这个判断：

- 如果 $a_i$ < $c_i$,则 $b_i$ 和 $d_i$交换。
- 如果 $a_i$ < $c_i$ 且 $b_i$ > $d_i$,则 $b_i$ 和 $d_i$交换。
- 其余情况不用交换。

注意这里只用输出 $b$，所以只用把 $d_i$ 赋值给 $b_i$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int len;
    string a,b,c,d;
    cin>>len;
    cin>>a>>b>>c>>d;
    for(int i=0;i<len;i++){
        if(a[i]>c[i]){
            b[i]=d[i];
        }else{
            if(a[i]==c[i]&&b[i]>d[i]){
                b[i]=d[i];
            }
        }
    }
    cout<<b;
    return 0;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10244)

## 思路

分两种情况讨论。以下 $1\le i\le n$。

- 如果 $a_i>c_i$，很显然 $a$ 的字典序不是最小的情况，进行操作；

- 如果 $a_i=c_i$ 且 $b_i>d_i$，尽管 $a$ 的字典序最小，但是 $b$ 的字典序不是最小，进行操作。

## AC 代码

以下是部分代码。

```cpp
int n;
string a,b,c,d;
int main(){
	cin>>n>>a>>b>>c>>d;
	for(int i=0;i<a.size();++i){
		if(a[i]>c[i]||a[i]==c[i]&&b[i]>d[i]){
			swap(a[i],c[i]);
			swap(b[i],d[i]);
		}
	}
	cout<<b;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/150293133)

---

## 作者：nightwatch.ryan (赞：1)

### 思路
为了使 $a$ 的字典序尽量小，我们从左到右遍历字符串的每一个位置 $i$。如果此时 $a_i > c_i$，那么交换 $a_i$ 和 $c_i$。这样我们就可以确保 $a$ 的字典序最小。

接下来看 $b$，有两种情况：
- $a_i \neq c_i$：不能交换 $b_i$ 和 $d_i$，因为这样 $a$ 的字典序就会改变，所以不能交换。
- $a_i = c_i$ 并且 $b_i > d_i$：可以交换 $b_i$ 和 $d_i$，因为这样 $a$ 的字典序不会改变（因为 $a_i= c_i$）而且 $b$ 的字典序也更小了，所以可以交换。

### 代码
```cpp
#include<iostream>
int main(){
	int n;std::cin>>n;
	std::string a,b,c,d;
	std::cin>>a>>b>>c>>d;
	for(int i=0;i<n;i++)
		if(a[i]>c[i])
			std::swap(a[i],c[i]),std::swap(b[i],d[i]);
	for(int i=0;i<n;i++)
		if(a[i]==c[i] and b[i]>d[i])
			std::swap(b[i],d[i]);
	std::cout<<b;
}
```

---

## 作者：CaiZi (赞：1)

## String Minimization 题解
**[题目链接](https://www.luogu.com.cn/problem/P10244)**
### 题意理解
给定 $4$ 个字符串 $a,b,c,d$，每次选择 $i$ 交换 $a_i,c_i$ 并交换 $b_i,d_i$。求在 $a$ 的字典序最小的情况下，$b$ 最小的字典序。
### 题目分析
定义字符的比较为按照 ASCII 码比较。若 $a_i>c_i$，则必须交换；若 $a_i=c_i$，则是否交换无影响；若 $a_i<c_i$，则不可以交换。而在 $a_i=c_i$ 时，若 $b_i>d_i$ 那么选择交换，使 $b$ 字典序更小，否则不换。
### 代码展示
时间复杂度 $O(n)$，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a,b,c,d;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>a>>b>>c>>d;
	for(int i=0;i<n;i++){
		if(a[i]>c[i]){
			swap(b[i],d[i]);
		}
		else if(a[i]==c[i]&&b[i]>d[i]){
			swap(b[i],d[i]);
		}
	}
	cout<<b;
	return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/150289937)**

---

## 作者：DFM_O (赞：0)

## [P10244 题解](https://www.luogu.com.cn/problem/P10244)

### 解体思路
很明显，若 $a_i>c_i$，则交换，无论 $b$ 的字典序是否变大，都必须交换。

若 $a_i=c_i$，此时若选择交换，对于 $a$ 没有任何影响，那么如果 $b_i>d_i$，就可以交换。

### Code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	string a,b,c,d;
	cin>>a>>b>>c>>d;
	for(int i=0;i<n;i++)
	{
		if(a[i]-'a'>c[i]-'a')
			swap(a[i],c[i]),swap(b[i],d[i]);
		if(a[i]==c[i]&&b[i]-'a'>d[i]-'a')
			swap(b[i],d[i]);
	}
	cout<<b;
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：0)

这道题考虑用贪心策略。

不难发现，对于每个 $a_i$ 和 $c_i$，都会有以下三种情况：

- $a_i>c_i$
- $a_i=c_i$
- $a_i<c_i$

但是题目让我们使 $a$ 的字典序最小，那么我们忽略 $a_i<c_i$，去考虑另外两种情况：

- 当 $a_i>c_i$，直接交换 $a_i$ 和 $c_i$；
- 当 $a_i=c_i$ 时，可以换或不换。但是考虑到要使 $b$ 的字典序尽量小，我们还得去看 $b_i$ 和 $d_i$ 的大小关系。如果 $b_i>d_i$，那么说明可以让 $b$ 的字典序更小，于是交换 $b_i$ 和 $d_i$；否则不交换，直接跳过。

这样，我们的题目就做好了，时间复杂度 $O(n)$。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int n;
	cin >> n;
	string a, b, c, d;
	cin >> a >> b >> c >> d;
	for (int i = 0; i < n; i++) {
		if (a[i] > c[i]) {
			// cerr << i + 1 << " ";
			swap(b[i], d[i]);
		}
		if (a[i] == c[i]) {
			if (b[i] >= d[i]) swap(b[i], d[i]);
		}
	}
	cout << b;
}
```

---

## 作者：_weishiqi66_ (赞：0)

本题主要考察贪心。要求使 $a$ 字典序最小，那么对于每个 $i$ 如果 $a_i < c_i$ 则必定要进行交换操作。如果 $a_i = c_i$ 则需要考虑此次操作是否会使 $b$ 的字典序最小。

根据上述思路可以解决此题。

```
#include<bits/stdc++.h>
using namespace std;

string a,b,c,d;
int main() {
	int n;cin>>n;
	cin>>a>>b>>c>>d;
	
	for(int i=0;i<n;i++) {
		if(a[i]==c[i]) {
			if(d[i]<=b[i]) swap(b[i],d[i]);
		}
		else if(a[i]>=c[i]) {
			swap(a[i],c[i]);
			swap(b[i],d[i]);
		}
	}
	
	cout<<b;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

因为要保证 $a$ 的字典序最小，所以当 $c_i<a_i$ 的时候，是肯定要进行一次交换的。

只有当 $c_i=a_i$ 时，考虑 $b_i$ 和 $d_i$ 的关系，判断是否需要交换。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n;
string a,b,c,d;
int main(){
	n=read();
	cin>>a>>b>>c>>d;
	for(int i=0;i<n;i++){
		if(c[i]<a[i]){
			swap(c[i],a[i]);
			swap(b[i],d[i]);
		}
		else if(c[i]==a[i]){
			if(d[i]<b[i])
			  swap(d[i],b[i]);
		}
	}
	cout<<b<<'\n';
	return 0;
}

```

---

## 作者：tder (赞：0)

依次枚举 $a_i$ 与 $c_i$，为了使 $a$ 的字典序尽可能小，即 $a_i$ 的字典序尽可能小，则最终的 $a_i$ 应为 $\min(a_i,c_i)$，也就是说：

- 当 $a_i>c_i$ 时，交换；
- 当 $a_i<c_i$ 时，不交换；
- 当 $a_i=c_i$ 时，此时考虑使 $b_i$ 尽可能小，于是同理若 $b_i>d_i$ 则交换，反之不交换。

模拟即可。

时间复杂度 $O(n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
int n; string a, b, c, d;
signed main() {
    cin>>n>>a>>b>>c>>d;
    for(int i = 0; i < n; i++) 
        if(a[i] > c[i] || (a[i] == c[i] && b[i] > d[i])) swap(b[i], d[i]);
    cout<<b<<endl;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

简单贪心题。

优先考虑 $a,c$ 的关系，当 $a,c$ 关系得到满足时考虑 $b,d$。

字符串等长，考虑遍历字符串（四个字符串一起遍历）。


如果 $a_i>c_i$，必须操作；

如果 $a_i=c_i$，如果 $b_i\ge d_i$ 操作（其实 $b_i=d_i$ 的时候都行）；

如果 $a_i<c_i$，必须不操作。

## 实现方面

其实对于 $a,c$ 操作和不操作其实对答案贡献是没区别的，因为题目只让求解了 $b$，而且 $a,c$ 无后效性（不会影响后面遍历的结果），所以下面代码省略了 $a,c$ 的修改。

省略后如下：

如果 $a_i>c_i$，交换 $b_i,d_i$；

如果 $a_i=c_i$，判断 $b_i,d_i$，**只交换** $b_i,d_i$；

否则忽略（因为对 $b_i,d_i$ 一定没有影响）。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a,b,c,d;
int main(){
    cin>>n>>a>>b>>c>>d;
    for(int i=0;i<n;i++){
        if(a[i]>c[i])//必须操作
            swap(b[i],d[i]);
        if(a[i]==c[i])//可以选择
            if(b[i]>d[i])
                swap(b[i],d[i]);
    }
    cout<<b;
    return 0;
}
```

---

## 作者：_little_Cabbage_ (赞：0)

# P10244 String Minimization 题解
这是一道贪心题。

要使 $a$ 的字典序最小，我们可以把 $c_i$ 比 $a_i$ 小的字符交换，同时把 $b_i$ 和 $d_i$ 交换。

但是，当 $c_i=a_i$，又因为我们要使 $b$ 的字典序也最小，我们就可以在 $d_i$ 比 $b_i$ 小的字符交换。

又又因为是输出 $b$，所以我们不用交换 $a$ 和 $c$。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main()
{
	int len;
	cin>>len;
	string a,b,c,d;
	cin>>a>>b>>c>>d;
	for(int i=0;i<len;i++)
	{
		if(a[i]>c[i]||(a[i]==c[i]&&b[i]>d[i]))
		{
			b[i]=d[i];
		}
	}
	cout<<b;
}
```

---

## 作者：xd244 (赞：0)

### P10244 String Minimization 题解

一道很简单的**贪心**，每次判断字符串 $b_i$ 是否比 $d_i$ 大，如果 $b_i>d_i$ 就将 $b_i$ 和 $d_i$ 交换。如果 $a_i>c_i$ 就交换 $a_i$ 和 $c_i$。

注意要先让字符串 $a$ 尽可能小,然后才判断字符串 $b$ 和 $d$ 哪个更大（坑点）

代码非常简单：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;
    string a,b,c,d;cin>>a>>b>>c>>d;
    for(int _c=0;_c<n;_c++){
        if(b[_c]>d[_c]&&a[_c]>=c[_c]){
            swap(b[_c],d[_c]);swap(a[_c],c[_c]);
        }
    }for(int _c=0;_c<n;_c++){
        if(a[_c]>c[_c]){
            swap(a[_c],c[_c]);swap(b[_c],d[_c]);
        }
    }cout<<b;
}
```

这道题作为签到题还是很简单的！属于一个小模拟。

---

## 作者：2021zjhs005 (赞：0)

Despriction
------------------
给定字符串 $a$，$b$，$c$，$d$，每次可以进行如下交换：

- 交换 $a_i$，$c_i$；交换 $b_i$，$d_i$。

求在字符串 $a$ 的字典序最小的情况下，字符串 $b$ 的值（字典序最小）。


Solution
------------
考虑贪心，这题第一关键字还是字符串 $a$ 的字典序最小。而 $a$ 只能和 $c$ 交换，因此，当 $a_i > c_i$ 时，应当交换 $a_i$，$c_i$。

考虑另外一种情况，$a_i = c_i$，这是可以选择**换或者不换**，对于字符串 $a$ 并没有影响。但是，如果此时 $b_i > d_i$，则一定要进行一次交换，使得 $a$ 的字典序最小的情况下，$b$ 的字典序也最小。

最后输出字符串 $b$ 即可。


Code
------------
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
#define endline pr("\n")
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int n;
string a,b,c,d;

signed main(){
  n=read();
  cin>>a>>b>>c>>d;
  rep(i,0,n-1){
  	if(a[i]>c[i]||(a[i]==c[i]&&b[i]>d[i])){//满足交换条件。
	  	swap(a[i],c[i]);swap(b[i],d[i]);
	  }
  }
  cout<<b<<endl;
  return 0;
}
```

---

## 作者：Vitamin_B (赞：0)

贪心题。首先为了保证 $a$ 的字典序小，当 $a_i<c_i$ 时要交换，$a_i>c_i$ 时不交换。在 $a_i=c_i$ 时，为了使 $b$ 的字典序尽可能小，则当 $b_i>d_i$ 时不交换，否则交换。
# 代码
```cpp
# include <bits/stdc++.h>
# define ffor(i,name) \
	for (auto i = name.begin (); i != name.end (); ++ i)
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n;
string a, b, c, d;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> a >> b >> c >> d;
	for (int i = 0; i < n; ++ i)
		if (a[i] > c[i])
			b[i] = d[i];
		else if (a[i] >= c[i])
			b[i] = min (b[i], d[i]);
	cout << b;
	return 0;
}
```

---

