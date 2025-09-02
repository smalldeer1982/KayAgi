# Nikita and string

## 题目描述

One day Nikita found the string containing letters "a" and "b" only.

Nikita thinks that string is beautiful if it can be cut into $ 3 $ strings (possibly empty) without changing the order of the letters, where the $ 1 $ -st and the $ 3 $ -rd one contain only letters "a" and the $ 2 $ -nd contains only letters "b".

Nikita wants to make the string beautiful by removing some (possibly none) of its characters, but without changing their order. What is the maximum length of the string he can get?

## 说明/提示

It the first sample the string is already beautiful.

In the second sample he needs to delete one of "b" to make it beautiful.

## 样例 #1

### 输入

```
abba
```

### 输出

```
4```

## 样例 #2

### 输入

```
bab
```

### 输出

```
2```

# 题解

## 作者：18lxxrz (赞：12)

#### 首先，这道题的题意……~~复制粘贴~~
一个字符串删除一些字符，使得可以分割成3个字符串，第1，3个全是a，第3个全是b，求删完的字符串最长多少？ 

------------
#### 思路
先遍历字符串，如果当前字符为a，可以构成a或aba串，如果是b的话，那就是可以构成ab串的，然后每次遍历之后要转移，因为发现当前是a的话，是可以继续构成a或者ab串，ab的我们可以构成aba或者ab串，所以我们对于ab就取ab和a的max，aba就取ab或者aba的max即可。

------------

贴以下代码

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[10000];//存储这个ab串 
int main ()
{
    int a=0,ab=0,aba=0;//存储啊，a，ab，aba串
    scanf("%s",c);
    for(register int i=0;i<strlen(c);++i)
    {
        if(c[i]=='a')//如果当前字符为a，可以构成a或aba串
        {
            a++;
			aba++;
        }
        if(c[i]=='b')//如果是b的话，可以构成ab串
            ab++;
        aba=max(aba,ab);
        ab=max(ab,a);
    }
    printf("%d\n",aba);  //aba的数量就是answer     
    return 0;
}
```


---

## 作者：Harry_Hedwig (赞：3)

# 0x00 思路
首先，我们先来看一下题目描述来理清思路。
>Nikita发现了一个**只含 ' $a$ ' 与 ' $b$ ' 的字符串**。Nikita认为，如果一个字符串可以分为三段，**第 $1$ 、$3$ 段只含' $a$ '，第 $2$ 段只含' $b$ '（每段都能为空）**，则这个字符串是美丽的。Nikita想删除（**不是改变**）某些字符，把输入的字符串变成美丽的。（可以不改变原串）

我们可以发现每两个字符中间都可以成为第一、二个或第二、三个字符串分开的地方。又因为前面所做的决定(将前一个字符分在哪一个字符串里)不会影响到后一个的决策，因此我们可以想到思路：dp。

# 0x01 定义状态
很明显，因为三个串都可以为空，因此当前字符可以放在任意字符串里，所以我们需要定义一个二维数组 `dp[i][j]` 来表示将第 `i` 个字符放在第 `j` 个字符串中**最多**能留下的字符。

# 0x02 状态转移方程
状态定义完毕就应该转移状态了。那么如何转移呢？情况有三：

**1. 字符 `i` 在第一个字符串**

如果这个字符在第 $1$ 个字符串，那么它的前一个字符**一定**在第 $1$ 个字符串(除非它是第 $1$ 个字符或者前一个被删了。但是不用管，因为被删了的话 `dp[i][1] = dp[i-1][1]`,所以不需要考虑）。

**2. 字符 `i` 在第二个字符串**

如果这个字符在第 $2$ 个字符串，那么前一个字符可能放在第 $1$ 个或第 $2$ 个字符串。又因为我们保存的是第 `i` 个字符放在第 `j` 个字符串中前 `i` 个字符**最多**有多少个能留下来。所以直接取 `dp[i-1][1]` 和 `dp[i-1][2]` 的最大值。

**3.字符 `i` 在第三个字符串**

与第 $2$ 点基本同理，所以这里就不再过多赘述了，只是相较第 $2$ 点而言三又多了前一个字符在第三个字符串的情况，仍取最大值。

# 0x03 注意细节！

>第 $1$ 、$3$ 段只含' $a$ '，第 $2$ 段只含' $b$ '（每段都能为空）。

所以一个字符在一或三字符串保留下来的条件是它是 ' $a$ '，在第二个字符串保留下来的条件是它是 ' $b$ '。

所以在三个字符串中保存下来的条件是这样：
```c
'b'-a[i]//在第1、3个字符串中
a[i]-'a'//在第2个字符串中
```

**Code:**

```c
#include<bits/stdc++.h>
using namespace std;
int d[5005][5];
char a[5005];
int main()
{
	int n,m,t,i,j;
	cin>>a;
	n=strlen(a);
	for(i=1;i<=n;i++)
	{
		d[i][1]=d[i-1][1]+'b'-a[i-1];//更新第i-1个字符在第1个字符的情况
        d[i][2]=max(d[i-1][1],d[i-1][2])+a[i-1]-'a';//更新第i-1个字符在第2个字符的情况
        d[i][3]=max(d[i-1][1],max(d[i-1][2],d[i-1][3]))+'b'-a[i-1];//更新第i-1个字符在第3个字符的情况
	}
	printf("%d",max(d[n][1],max(d[n][2],d[n][3])));
	return 0; 
}
```
# 0x04 优化
这道题的时间复杂度和空间复杂度分别是 $O(n)$ 、$O(3n)$，由于这道题我们只用了一重循环，而且数据范围也保证没有（~~谁知道有没有超~~）超过 $5000$，所以时间复杂度肯定优化不了了，那么看空间：由于此题只用到了前一个字符（即 `i-1`），所以我们不需要保留物品的编号。

代码如下:
```c
#include<bits/stdc++.h>
using namespace std;
int d[5];//比较:d[5005][5],d[5]
char a[5005];
int main()
{
	int n,m,t,i,j;
	cin>>a;
	n=strlen(a);
	for(i=1;i<=n;i++)
	{
		d[1]=d[1]+'b'-a[i-1];
		d[2]=max(d[1],d[2])+a[i-1]-'a';
		d[3]=max(d[1],max(d[2],d[3]))+'b'-a[i-1];
	}
	printf("%d",max(d[1],max(d[2],d[3])));
	return 0; 
}
```
但是这是错误代码！

接着我请出了我们机房的同学来帮我查错。我们发现 `d[2]` 需要用到 `d[1]` 未更新的值， `d[3]` 需要用到 `d[1]` 和 `d[2]` 未更新的值。

所以需要把顺序反一下。

**code:**
```c
#include<bits/stdc++.h>
using namespace std;
int d[5];
char a[5005];
int main()
{
	int n,m,t,i,j;
	cin>>a;
	n=strlen(a);
	for(i=1;i<=n;i++)
	{
	   	d[3]=max(d[1],max(d[2],d[3]))+'b'-a[i-1];
		d[2]=max(d[1],d[2])+a[i-1]-'a';
		d[1]=d[1]+'b'-a[i-1];
	}
	printf("%d",max(d[1],max(d[2],d[3])));
	return 0; 
}
```
这是优化后的代码，时间复杂度 $O(n)$ ,空间复杂度 $O(3)$ 。

---

## 作者：Super_Cube (赞：2)

# Solution

比较明显的 dp。

$dp_{i,0}$ 表示前 $i$ 个字符形如 `aaa...` 的字符串的最大长度。

$dp_{i,1}$ 表示前 $i$ 个字符形如 `a...ab...b` 的字符串的最大长度。

$dp_{i,2}$ 表示前 $i$ 个字符形如 `a...ab...ba...a` 的字符串的最大长度。

当第 $i$ 个字符为 `a` 时，有转移式：

+ $dp_{i,0}=dp_{i-1,0}+1$

长度直接 + 1。

+ $dp_{i,1}=dp_{i-1,1}$

长度加不了。

+ $dp_{i,2}=\max\{dp_{i-1,0},dp_{i-1,1},dp_{i-1,2}\}+1$

都能拼接上，取三者最大值 + 1。

当第 $i$ 个字符为 `b` 时，有转移式：

+ $dp_{i,0}=dp_{i-1,0}$

长度加不了。

+ $dp_{i,1}=\max\{dp_{i-1,0},dp_{i-1,1}\}+1$

都能在 `aaa...` 串和 `a...ab...b` 串后拼接，取最大值再 + 1。

+ $dp_{i,2}=\max\{dp_{i-1,0},dp_{i-1,2}\}$

拼接不上，直接取 `aaa` 串与 `aba` 串的最大值。

最后输出时取三种串的最大值即可。

# Code

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
int dp[5005][3];
char s[5005];
int n;
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;++i){
		if(s[i]=='a'){
			dp[i][0]=dp[i-1][0]+1;
			dp[i][1]=dp[i-1][1];
			dp[i][2]=std::max(dp[i-1][0],std::max(dp[i-1][1],dp[i-1][2]))+1;
		}else{
			dp[i][0]=dp[i-1][0];
			dp[i][1]=std::max(dp[i-1][0],dp[i-1][1])+1;
			dp[i][2]=std::max(dp[i-1][0],dp[i-1][2]);
		}
	}
	printf("%d",std::max(dp[n][0],std::max(dp[n][1],dp[n][2])));
	return 0;
}
```

显然，因为只与上一位状态有关，可以使用滚动数组优化 dp 的空间复杂度。

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
int dp[3];
char s[5005];
int n;
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;++i){
		if(s[i]=='a'){
			dp[2]=std::max(dp[0],std::max(dp[1],dp[2]))+1;
			++dp[0];
		}else{
			dp[1]=std::max(dp[0],dp[1])+1;
			dp[2]=std::max(dp[0],dp[2]);
		}
	}
	printf("%d",std::max(dp[0],std::max(dp[1],dp[2])));
	return 0;
}
```

---

## 作者：staygone (赞：1)

了解了大致题意后我们可以大致知道我们要求整数为切完后 $3$ 部分串长度的总和的最大值。

可以想到定义 dp 数组从数组左到右转移，并且分成题意中的 $3$ 个部分。

首先，在第 $1$ 个部分, $dp_{i, 1}$ 只能由上 $1$ 个部分的转移得来。

加上 ```a[i]=='a'```。

然后，第 $2$ 个部分, $dp_{i, 2}$ 可以由第 $1$ 部分，也可以由第 $2$ 部分转移得到。

按照题意我们取其最大值加上 ```a[i]=='b'``` 。

最后，第 $3$ 个部分, $dp_{i, 3}$ 可以由第 $2$ 部分，也可以由第 $3$ 部分转移得到。

按照题意我们取其最大值加上 ```a[i]=='a'``` 。

**亮核心代码**
 
```cpp
dp[i][1] = dp[i - 1][1] + (a[i] == 'a');
dp[i][2] = max (dp[i - 1][1], dp[i - 1][2]) + (a[i] == 'b');
dp[i][3] = max (dp[i - 1][2], dp[i - 1][3]) + (a[i] == 'a');

```


---

## 作者：I_have_been_here (赞：1)

#### 这种最值字符串的题首选考虑 DP 啦~~

# 题意分析

对于这道题，看起来三个部分很高深的样子，实际上就是给你一个字符串，问你如何修改删除可以得到分别是 $a$ $b$ $a$ 的形式，也就是一个最优解问题

# 状态定义

那么首先我们需要解决的是基本的状态，这里我们可以考虑二维转移：有 $dp_{i, j}$ 那么第一维我们控制前 $i$ 个字符，第二维我们控制切割到了前 $j$ 个部分，举个例子 $dp_{5, 2}$ 它的实际意义就是说对于给出的这个字符串，前 $5$ 个字符，切割到第 $2$ 个部分我们的最长的长度

# 状态转移

有了上面状态定义的基础，转移就好写多了，那么这里的转移我们需要考虑两种情况，假设我们讨论第二个部分，那么第 $i$ 个字符，它可以是第二个部分的第一个字符，也可以是第二个部分的第若干个字符，再对于这两个部分取最大进行转移，第三个部分同理

# AC CODE

```cpp
#include <bits/stdc++.h>
#define maxn 5005
using namespace std;
char s[maxn];
int dp[maxn][4], len;
int main() {
	cin >> (s + 1);
	len = strlen(s + 1);
	for (int i = 1; i <= len; i++) {
		dp[i][1] = dp[i - 1][1] + (s[i] == 'a');
		dp[i][2] = max(dp[i - 1][1], dp[i - 1][2]) + (s[i] == 'b'); //分别讨论两个部分
		dp[i][3] = max(dp[i - 1][2], dp[i - 1][3]) + (s[i] == 'a');//同上
	}
	cout << max(dp[len][1], max(dp[len][2], dp[len][3])) << endl; //因为可以为空串，所以三个部分取最大
	return 0;
}
```




---

## 作者：XL4453 (赞：1)

### 题目分析：

对于原题数据，枚举两个断点，然后用前缀和优化一下就可以了，复杂度是 $O(n^2)$ 的。

但这道题用这样的暴力解法实在是太 low 了，于是考虑优化。

------------
先考虑一个朴素的 DP，用 $f_{i,j}$（$j$ 为 $1$、$2$ 或 $3$）来分别表示到达第 $i$ 个位置时，只有第一段，有一、二两段，已经取完三段的最长长度。

转移也很显然，第一段只能从前面一个的第一段转移过来，有一二两段的可以从从之前的一二段或者第一段（即把断点放在这一个点），三段都有的可以从只有一段的、一二两段或者是之前的三段都有的转移过来。

更形式化的，有：
$\begin{cases}f_{i,1}=f_{i-1,1}+[s_i=a]\\f_{i,2}=\max(f_{i-1,1},f_{i-1,2})+[s_i=b]\\f_{i,3}=\max(f_{i-1,1},f_{i-1,2},f_{i-1,3})+[s_i=a]\end{cases}$

然后发现每一个字符的结果只和之前一个的结果有关，那么就不用开数组了。

但如果要只用三个变量就实现转移则需要调整三个的转移顺序，一种可行的方案是现转移第三个，然后第二个，最后第一个。

其他的，例如先转移第一个，可能会造成之前的那一个的结果丢失，后续转移是依据这一次的转移结果，显然是会出问题的。


------------
### 代码：
```
#include<cstdio>
#include<algorithm>
using namespace std;
int a,b,c;
char x;
int main(){
	while(1){
		scanf("%c",&x);
		if(x=='\n'||x=='\r')break;
		c=max(max(a,b),c)+(x=='a');
		b=max(a,b)+(x=='b');
		a=a+(x=='a');
	}
	printf("%d\n",max(max(a,b),c));
	return 0;
}
```


---

## 作者：Liynw (赞：1)

### 前言

蒟蒻第一篇题解，在线求审核大大给过 awa。

如果此题解有什么问题的话欢迎各位大巨佬提出。

题目链接：[CF877B](https://www.luogu.com.cn/problem/CF877B)

题目类型：dp，一讲就会，一做就废(；′⌒\`)。

***
### 更新

2021/5/31：因为帮同学调代码添加了新发现的滚动数组问题。

***

### 题意简述

给定一个只含有 “a” 和 “b” 的字符串，求这个字符串中最长的**子序列**，子序列满足以下条件之一：

1. 全为 “a”。

1. 全为 “b”。

1. 开头和结尾是**连续**的 “a”，中间是**连续**的 “b”。

字符串长度 $\leq 5000$。

### 题解

**算法：动态规划**

首先可以发现一个“美丽”的字符串由**三个部分**组成，所以我们可以开一个二维的 $dp$ 数组。其含义如下：

* $dp_{i,1}$ 代表字符串只包含第一部分，从 $1\sim i$ 能取到的最长长度；

* $dp_{i,2}$ 代表字符串包含第一部分和第二部分，从 $1\sim i$ 能取到的最长长度；

* $dp_{i,3}$ 代表字符串包含所有部分，从 $1\sim i$ 能取到的最长长度。

因为**每个部分都可以是空串**，所以最后的答案可以为 $dp_{i,1},dp_{i,2},dp_{i,3}$ 的**任意一种**，取最大值。

然后思考如何转移状态。

首先 $dp_{i,1}$ 是很好求的，我们只需要求解字符串里面有多少个 “a” 就可以了。这个很好想，要求解一个字符串中最长的只包含 “a” 或为空的子序列，只需统计 “a” 的个数，让所有的 “a” 都加入子序列。

当然我们不需要每次都用一个循环求解，可以参照前缀和的方式求解 “a” 的个数：

```cpp
dp[i][1]=dp[i-1][1]+(a[i]=='a');
```

（如果这个字符是 “a” 就 $+1$，反之不加）

接着考虑 $dp_{i,2}$ 的求法。实际上，我们可以用另一种方式理解前面求 $dp_{i,1}$，把它当做**动态转移方程**而并不是一个简单的求**前缀和**的式子：

- 如果这个字符是 “a”，那么一定要选，然后再加上前 $i-1$ 个字符能拿到的最长的长度。

那么，$dp_{i,2}$ 的解法就呼之欲出了：

```cpp
dp[i][1]=max(dp[i][1],dp[i][2])+(a[i]=='b');
```

因为第一部分和第二部分都可以是空串，所以一个全为 “a” 的字符串同样可以作为第二部分的结果，所以需要求最大值。最后的那个 “b” 也是一样的，因为如果这个字符串不是一个全为 “a” 的字符串，就必须以 “b” 结束。所以只有后面是 “b” 才能增加字符串的长度，若答案全是 “a” 那就是 $dp_{i,1}$，与 $dp_{i,2}$ 的求解是无关的。

$dp_{i,3}$ 方法类似，需要考虑空串的情况，考虑 $dp$ 前两维的情况；也需要根据结尾的 “a” 判断不为空的最大值，~~读者自证不难~~。

```cpp
dp[i][3]=max(dp[i][1],dp[i][2],dp[i][3])+(a[i]=='a');
```

最后可以看到：

我们只有 "$1,3$ 不空，$2$ 空"和 "$1,3$ 空，$2$ 不空"的情况没有考虑到。但是由于第一个部分和第三个部分本质上是一样的，所以这两种情况可以分别对应到另外两种我们已经考虑过的情况——全为 “a” 或全为 “b”。

### $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[5005][4],n;
char a[5005];
int main(){
	scanf("%s",a+1);
	n=strlen(a+1);
	for(int i=1;i<=n;i++){
		dp[i][1]=dp[i-1][1]+(a[i]=='a');
		dp[i][2]=max(dp[i-1][1],dp[i-1][2])+(a[i]=='b');
		dp[i][3]=max(dp[i-1][1],max(dp[i-1][2],dp[i-1][3]))+(a[i]=='a');
	}
	printf("%d",max(dp[n][1],max(dp[n][2],dp[n][3])));
	return 0;
}
```

***

### 关于滚动数组

我有个同学一直没过让 me 帮他调代码，然后我发现他用的是滚动数组。

首先要明确这道题是不能在上述代码中直接修改的。因为如果打滚动，例如求 $dp_{i,3}$ 时需要用到 $dp_{i-1,2}$ 的值，但是如果打滚动这个值就已经被更新为 $dp_{i,2}$ 了。

如果要打滚动呢？

很简单，先求 $dp_{i,3}$，再求 $dp_{i,2}$，最后求 $dp_{i,1}$ 就阔以了。

***

最后希望大家文明浏览，否则陶片两行泪 qwq。

---

## 作者：HUTEHE (赞：0)

## 题目大意

给定一个只包含字符 `a` 和 `b` 的字符串，通过删除字符（可以不删除）将其转化为满足以下条件的最长字符串：

1. 字符串可以分为三段。
2. 第一段和第三段仅包含 `a`。
3. 第二段仅包含 `b`。
4. 每一段都可以为空。

## 解决思路

可以使用动态规划解决，$dp_{i,j}$ 表示前 $i$ 个字符，第 $j$ 段时，最长美丽字符串的长度，其中 $j\in\{0,1,2\}$。

可以考虑逐个考虑字符串 $s$ 的每一位：

如果 $s_i$ 是 `a`，那么：

* $dp[i][0]=dp[i-1][0]+1$，即第一段延长；
* $dp[i][1]=dp[i-1][1]$，即第二段不变；
* $dp[i][2]=\max(dp[i-1][1],dp[i-1][2])+1$，即第三段开始或延长。

如果 $s_i$ 是 `b`，那么：

* $dp[i][0]=dp[i-1][0]$，即第一段不变；
* $dp[i][1]=\max(dp[i-1][0],dp[i-1][1])+1$，即第二段开始或延长；
* $dp[i][2]=dp[i-1][2]$，即第三段不变。

则最终答案是 $\max(dp[n][0],\max(dp[n][1],dp[n][2]))$，其中，$n$ 为字符串 $s$ 的长度。

## 代码

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define int long long
#define tem template
#define sizet size_t
#define il inline
#define uni union
#define endl "\n"
const int INF=0xfffffff;
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
int dp[5005][3];
signed main()
{
	char a;
	a=getchar();
	dp[0][0]=dp[0][2]=(a=='a')?1:0;//初始化
	dp[0][1]=1-dp[0][0];
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='a')//状态转移
		{
			dp[i+1][0]=dp[i][0]+1;
			dp[i+1][1]=dp[i][1];
			dp[i+1][2]=max(dp[i][1],dp[i][2])+1;
		}
		else
		{
			dp[i+1][0]=dp[i][0];
			dp[i+1][1]=max(dp[i][0],dp[i][1])+1;
			dp[i+1][2]=dp[i][2];
		}
	}
	cout<<max(dp[s.size()][0],max(dp[s.size()][1],dp[s.size()][2]))<<endl;
	return 0;
}
```

### 时间复杂度

$O(|s|)$，其中 $|s|$ 是字符串 $s$ 的长度。

### 空间复杂度

$O(|s|)$。

---

## 作者：rexmqy (赞：0)

## 思路：

通过读题可以发现题目是让我们求 aba 的最长长度。

可直接循环遍历字符串，如果当前字符为 `a`，可以构成 `a` 或 `aba` 串；如果是 `b` 的话，那就是可以构成 `ab` 串，然后每次遍历之后要转移，因为发现当前是 `a` 的话，是可以继续构成 `a` 或者 `ab` 串，`ab` 的可以构成 `aba` 或者 `ab` 串，所以对于 `ab` 就取 `ab` 和 `a` 的最大值，`aba` 就取 `ab` 或者 `aba` 的最大值即可。

---

可能会有一些啰嗦，具体看代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;//定义字符串
signed main()
{
    cin>>s;//输入
	int a=0,ab=0,aba=0,len=s.size();//定义
    for(int i=0;i<len;++i)
    {
        if(s[i]=='a') a++,aba++;
        if(s[i]=='b') ab++;
        aba=max(aba,ab);//取最大值
		ab=max(ab,a);取最大值
    }
    cout<<aba;//输出答案    
    return 0;
}
```

求管理员通过。

---

## 作者：_QyGyQ_ (赞：0)

## 思路
遍历整个字符串，如果当前字符为 `a`，那么它就可能构成 `a`，`ba` 或 `aba` 字符串。如果是 `b`，就可能构成 `b`,`ab` 字符串。我们把 `aba` 串与三种可行串 `ab`，`ba`，`aba` 比较，取最大的，再把 `ab` 串与可能构成可行串的 `a`，`ab`，`ba` 比较，取最大的。最后 `aba` 串的个数就是答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
struct node{
	int a,b,ab,ba,aba;
};
node str;
signed main(){
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='a'){
			str.a++,str.aba++,str.ba++;
		}
		else{
			str.b++,str.ab++;
		}
		str.aba=max(str.aba,max(str.ab,str.ba));
		str.ab=max(str.a,max(str.ab,str.ba));
	}
	cout<<str.aba;
	return 0;
} 
```


---

## 作者：封禁用户 (赞：0)

# Solution
**题目大意**：Nikita 发现了一个只含 $\texttt a$ 与 $\texttt b$ 的字符串。Nikita 认为，如果一个字符串可以分为三段，第 $1$、$3$ 段只含 $\texttt a$，第 $2$ 段只含 $\texttt b$（每段都能为空），则这个字符串是美丽的。Nikita 想删除（不是改变）某些字符，把输入的字符串变成美丽的（可以不改变原串）。

**思路：** 我们可以定义一个变量 len 用来表示美丽字符串的长度，再定义一个 maxb 表示连续出现的 $\texttt b$ 的最大个数，然后用 k 来表示当前连续出现的 $\texttt b$ 的个数。我们在遍历时输入字符串，统计出现的 $\texttt a$ 的个数，并同时记录连续出现的 $\texttt b$ 的最大个数（即变量 maxb），最后将两者相加得到最大美丽字符串长度。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int len, maxb , k;
char c;
int main() {
	while((c = getchar()) >= 'a'){
		if (c =='a') {
			ans ++;
			if (k > 0) 
				k --;
		} 
		else maxb = max(++k, maxb);
	} 
	cout<<len+maxb<<endl;
	return 0;
}
```


---

## 作者：kn_wlq (赞：0)



[CF 传送门。](https://codeforces.com/problemset/problem/877/B)

[洛谷传送门。](https://www.luogu.com.cn/problem/CF877B)

首先，先理解提示的意思：



------------

 
如果是第一个样品（样例），弦（字符串）已经很漂亮（为标准字符串）了。

#### 在第二个样本（样例）中，他需要**删除一个 $b$** 以使其美观（变为标准字符串）。

想法：

通过遍历输入字符串，统计出现的 $a$ 的个数，并同时记录连续出现的 $b$ 的最大个数。然后将两者相加得到最大美丽字符串长度。

附上 $ O(n)$ 的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans, d , k;//表示美丽字符串的长度、连续出现的'b'的最大个数和当前连续出现的'b'的个数。
int main() {
	char c;
	while((c = getchar()) >= 'a'){
		if (c =='a') {
			ans ++;
			if (k > 0) k --;
		} else {
			d = max(++k, d);
		}
	} 
	printf("%d",ans + d);//输出美丽字符串的长度，即ans+d。
}
```

~~应该比 $dp$ 简单吧。~~



---

## 作者：TLMPEX (赞：0)

思路：枚举加动态规划。具体思路见代码。

```c
#include<bits/stdc++.h>
using namespace std;
string k;
int dp1[5001],dp2[5001],dp3[5001];//dp1为第一段，dp2为第二段，dp3为第三段
int main(){
	int i,j,n,z=0;//z表示美丽的字符串最长长度
	getline(cin,k);
	k=' '+k;//把第一个置为空格，方便一些
	n=k.size();
	for(i=1;i<n;i++){
		if(k[i]=='a'){//如果这个字母是‘a’
			dp1[i]=dp1[i-1]+1;//第一段长度加一
			dp2[i]=dp2[i-1];//第二段长度没变
			dp3[i]=max(dp1[i-1],max(dp2[i-1],dp3[i-1]))+1;//第三段长度为三段长度的最大值并加上新来长度一
		}
		else{//否则为‘b’
			dp1[i]=dp1[i-1];//第一段长度不变
			dp2[i]=max(dp1[i-1],dp2[i-1])+1;//第二段长度为第一段与第二段长度的最大值并加上新来长度一
			dp3[i]=max(dp1[i-1],dp3[i-1]);//在第一段和第三段中取最大值
		}
	}
	z=max(dp1[n-1],dp2[n-1]);
	z=max(z,dp3[n-1]);//在这三个值中取最大值
	cout<<z;//输出
}
```


---

