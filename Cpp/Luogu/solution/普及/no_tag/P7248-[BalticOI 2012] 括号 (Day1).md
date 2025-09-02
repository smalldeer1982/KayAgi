# [BalticOI 2012] 括号 (Day1)

## 题目描述

一个合法括号序列的定义如下：

- () 和 [] 是合法括号序列
- 若 A 是合法括号序列，则 (A) 和 [A] 也是合法括号序列
- 若 A 和 B 都是合法括号序列，则 AB 也是合法括号序列

在包含至少一对方括号的合法括号序列中，我们可以将 [ 和 ] 都用 ( 代替，这样就能够得到一个不合法括号序列。

例如 (( 和 ((((())) 都是不合法括号序列，前者可以由合法括号序列 \[] 转化而来，后者可以通过 \[]((()))，(\[](()))，((\[]())) 和 (((\[]))) 这四种合法括号序列转化而来。

现在给出一个不合法括号序列，求有多少种合法括号序列，在将其中的方括号用 ( 代替后，可以得到给定的括号序列。

## 说明/提示

**【样例解释#1】** 

满足条件的合法括号序列有两种：\[]() 和 ([])。

**【数据范围】**

- 对于 20% 的数据，满足 $n \leq 50$
- 对于 50% 的数据，满足 $n \leq 1000$
- 对于 100% 的数据，满足 $2\leq n \leq 30000$

**【说明】**

译自 [BalticOI 2012 Day1 T1. Brackets](http://www.boi2012.lv/data/day1/eng/brackets.pdf)

## 样例 #1

### 输入

```
4
((()```

### 输出

```
2```

## 样例 #2

### 输入

```
8
((((((((```

### 输出

```
14```

# 题解

## 作者：quest_2 (赞：7)

写在最前：推一下蒟蒻 [$\color{limegreen}{blog}$](https://www.luogu.com.cn/blog/quest233/#) 

-----

首先，膜拜搬题人 [$\color{black}\texttt{s}\color{red}\texttt{henmadongdong}$](https://www.luogu.com.cn/user/71491) ，他是我们的红太阳！

其次，强烈谴责出题人自己卡常的恶劣行径。

本文阐（fan）述（yi）官方 std 做法，你会发现它的复杂度是假的，具体一会再说。

-----

题意不用表述了，很清楚。

以下论述中，我们把不合法括号串归为一类，即 **左括号数目多于右括号** 的括号串。

（若在某一时刻，右括号多于左括号，那么之后无论怎么加括号，这整个串都 **救不回来** 了，没有统计意义）

接下来，我们需要证明一个氡西：

『所有 **夹杂着方括号**（至少有一对）的合法括号串与 **纯圆括号** 的合法括号串一一对应』

尝试胡乱证明：

- 对于一个 **夹杂着方括号** 的合法括号串 $s$ ，我们将里面所有左方括号换成左圆括号，所有右方括号换成右圆括号，最终的结果一定是一个 **纯圆括号** 的合法括号串。我们设这个新串为 $t$ 。目前只是单向的对应，我们需要建立 **双向** 。

$$\texttt{s:(()\red{[]})}\Rightarrow\texttt{t:(()\red{()})}$$

- 对于这个 **纯圆括号** 的合法括号串 $t$ 。 我们将 $s$ 里，所有匹配上的 **圆括号** ，在 $t$ 中相应位置标记出来。

$$\begin{matrix}\texttt{s:\blue{(()}[]\blue{)}}\\\texttt{t:\blue{(()}()\blue{)}}\end{matrix}$$

- 在 $t$ 的其它部分中，所有左圆括号换成左方括号，所有右圆括号换成右方括号。最终我们又得到了一个 **夹杂着方括号** 的合法括号串，显然这个新串就是 $s$ 。

$$\texttt{t:(()\red{()})}\Rightarrow\texttt{s:(()\red{[]})}$$

$Q.E.D.$ （这个证明看上去稀奇古怪的）

题目要求我们求 **夹杂着方括号** 的合法括号串，我们欣欣然把它转化成了 **纯圆括号** 的合法括号串计数。

之后就是普及- $dp$ 了，根据括号串dp的基本套路（~~基本法~~），我们设 $dp_{i,j}$ 表示：决策到第 $i$ 个位置，当前左括号比右括号 **多**  $j$ 个的 **括号串数目** 。（为什么只考虑 $j$ 为正数在文章开头有说）

那么我们就有简单转移柿子（设给定串为 $s$ ）：

$$\begin{cases}dp_{i,j}=dp_{i-1,j+1}\qquad(s[i]=')')\\dp_{i,j}=dp_{i-1,j+1}+dp_{i-1,j-1}\qquad(s[i]='(')\end{cases}$$

结合状态定义很好理解（或许？）。

初始化是 $dp_{0,0}=0$ （显然） 。

但是我们意识到这样空间开不下，所以可以 **滚一滚** 。

这样我们就获得了 $\mathcal{O}(n^2)$ 时间复杂度的优秀做法。按理说应该是过不了题的，而要优化起码得从 **状态定义** 上开刀。

写到这里我横竖想不到更好方法，在极度愤怒的情况下去看了官方题解，结果：

> The  correct  solution  is  still  O(N^2),  but  we  should  speed  it  up  by  some  constant factor.

你在教我做事？

于是打了个 $n$ 方，果然过了，需要手动卡常，不需要吸氧。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 3e5 + 7;
const int MOD = 1e9 + 9;
#define lst (i + 1) & 1//用以滚动数组
int dp[2][MAX], N, p;
int main()
{
	ios::sync_with_stdio(0);
	cin >> N;
	dp[0][0] = 1;
	for (register int i = 1; i <= N; i++)
	{
		char c;
		cin >> c;
		int M = min(i, N - i);
		//上界，对答案有贡献的 j 需要小于 N-i ，而考虑合理性，j 还需要小于 i 
		for (register int j = 0; j <= M; j++)
		{
			//转移
			if (!j || c == ')')
			{
				dp[i & 1][j] = dp[lst][j + 1];
			}
			else
			{
				dp[i & 1][j] = (dp[lst][j + 1] + dp[lst][j - 1]) % MOD;
			}
		}
	}
	cout << dp[N & 1][0] << '\n';
	return 0;
}
```

---

## 作者：xw_qwq (赞：2)

## P7248 [BalticOI 2012] 括号 (Day1)

[题目传送门](https://www.luogu.com.cn/problem/P7248)

### 题目思路
简单 dp 题。

设 $dp_{i,j}$ 表示到第 $i$ 个位置有 $j$ 个未匹配括号时的方案数，则易推出状态转移方程。

- 当当前遍历到的字符不是左括号：$dp_{i,j} = dp_{i-1,j+1}$。
- 当当前遍历到的字符是左括号：$dp_{i,j} = dp_{i-1,j+1} + dp_{i-1,j-1}$。

**记得取余 $10^9 + 9$！**

由于数据范围大，所以要使用滚动数组优化，防 MLE。

此外，吸氧也要卡常！
### code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 9;
int dp[2][30005];
signed main()
{
	dp[0][0] = 1;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		char a;
		cin >> a;
		for (int j = 0; j <= min(n - i, i); j++)
		{
			if (a == ')' || j == 0)
				dp[i & 1][j] = dp[i + 1 & 1][j + 1] % mod;
			else
				dp[i & 1][j] = (dp[i + 1 & 1][j + 1] + dp[i + 1 & 1][j - 1]) % mod;
		}
	}
	cout << dp[n & 1][0];
	return 0;
}
```

---

## 作者：wanghx (赞：2)

# [题目链接](https://www.luogu.com.cn/problem/P7248)
题意：

给定一个括号序列，可以用方括号代替小括号，求有多少种方法，可以得到匹配的括号序列。

这道题其实只是一道括号匹配问题，已经完成匹配的括号可以不用管，只需要记录没有匹配的 $($ 的数量，将所有 $($ 都换为匹配的中括号的可能数。

可能数计算起来并不难，考虑搜索，设 $f_{x,y}$
表示 第 $x$ 个位置有 $y$ 个不匹配括号，每个不匹配括号可以和上一个不匹配括号组成一组，也可以等待下一个不匹配括号，时间复杂度  $O(n^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define min(a,b) ((a)<(b)?(a):(b))
const int maxn=3e5+5,mod=1e9+9;
int dp[2][maxn]={1},n,p;
int main(){
	cin>>n;
	char c;
	for(register int i=1;i<=n;++i){
		cin>>c;
		if(c=='\n'||c=='\r'){break;--i;}
		int m=min(i,n-i);
		for(register int j=0;j<=m;++j)
			if(!j||c== ')') dp[i&1][j]=dp[(i+1)&1][j+1];
			else dp[i&1][j]=(dp[(i+1)&1][j+1]+dp[(i+1)&1][j-1])%mod;
	}
	printf("%d",dp[n&1][0]);
	return 0;
}
```

---

## 作者：a202401006 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P7248)

## 解析
### 题意
有一个字符串，里面有小括号和中括号且这两种字符可互相转换，求所有括号匹配，即合法，的序列总数，并取模。
### 考察知识
此题考查动态规划，同时由于使用普通的动态规划会报内存，需加上滚动数组，不了解的可以去查一下。
### 思路
输入数据组数，然后循环，每组数据搞一遍，再加上判断，如下。

设一个动态规划数组为 $dp[i][j]$，表示到第 $i$ 个位置不合法的括号有 $j$ 个。

可以列出表达式如下。


```cpp
dp[i][j]=dp[i+1][j+1](j=0,dp[i][j]=')')
dp[i][j]=dp[i+1][j+1]+dp[i+1][j-1](dp[i][j]='(')
```


具体解释还是看代码里面比较清晰吧。

## 代码
### 带注释版本
~~相信大家都不喜欢空白的无注释的代码。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+86,mod=1e9+9;//这里N要用const int，否则爆掉，卡住；mod就是题目中的取余 
int dp[10][N]={1},innum;//dp【i】【j】就是表示到第i处有j个不合法的（即不匹配的）括号 
char ls;//创建一个临时数据，到时候每步输入判断 
int main()
{
	cin>>innum;//输入 
	for(int i=1;i<=innum;i++)
	{
		cin>>ls;//每步输入判断
		for(int j=0;j<=min(i,innum-i);j++)//为什么是0到min(i,innum-i)？因为我们需要在目前有0至min(i,innum-i)个括号不合法间看看能不能满足。为什么只到min(i,innum-i)就行了？因为我们去掉的那i个括号已经检查过了且我们只考虑剩余的括号（就好比说现在输入了1个括号，那么我们只需要求其余的位置上有没有和它匹配的括号即可） 
		{
			if(!j||ls== ')')//如果要所有括号匹配或出现了右括号 
			{
				dp[i%2][j]=dp[(i+1)%2][j+1];//dp[(i+1)%2][j+1]是因为出现了没法消除的括号 
			}
			else
			{
				dp[i%2][j]=(dp[(i+1)%2][j+1]+dp[(i+1)%2][j-1])%mod;//dp[(i+1)%2][j+1]是因为出现了没法消除的括号，所以加1；dp[(i+1)%2][j-1]是因为我们可以用右括号匹配上，所以减一。顺便取模 
			}
		}
	}
	//只要在剩余的位置出现了无法匹配的右括号，那么就一定无法匹配，因为无论怎么在右边填括号，都无法匹配 
	//备注：%2是滚动数组的套路，&1就是%2 
	printf("%d",dp[innum%2][0]);//输出，过程中取过模了，此处输出即可 
}
```

### 无注释版本
~~无障碍阅读。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+86,mod=1e9+9;
int dp[10][N]={1},innum;
char ls;
int main()
{
	cin>>innum; 
	for(int i=1;i<=innum;i++)
	{
		cin>>ls;
		for(int j=0;j<=min(i,innum-i);j++)
			if(!j||ls== ')')
			{
				dp[i%2][j]=dp[(i+1)%2][j+1];
			}
			else
			{
				dp[i%2][j]=(dp[(i+1)%2][j+1]+dp[(i+1)%2][j-1])%mod; 
			}
		}
	} 
	printf("%d",dp[innum%2][0]); 
}
```
~~恳求管理员大大通过！~~

---

## 作者：chenyizhen (赞：1)

### 思路

本题是括号匹配和动态规划，还是比较简单。

已经匹配的括号我们不用管，只需要处理没有匹配的左括号即可。但是考虑到数据范围，普通的二维动态规划空间会炸，需要滚动数组来解决。

$f_{i,j}$ 表示第到 $i$ 个位置，未匹配的左括号个数为 $j$，那么就有如下状态转移方程。

不是左括号：$f_{i,j}=f_{i-1,j}$。

是左括号：$f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}$。

别忘了取模！！！

---

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,mod=1e9+9;
void read(int &a){
	char ch;int f=1,k=0;ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){k=k*10+ch-'0';ch=getchar();}
	a=k*f;
}
int n,f[2][N];
char ch;
signed main(){
	read(n);
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		cin>>ch;
		int minn=min(i,n-i);
		for(int j=0;j<=minn;j++){
			if(j==0||ch==')') f[i%2][j]=f[(i+1)%2][j+1];
			else f[i%2][j]=(f[(i+1)%2][j+1]+f[(i+1)%2][j-1])%mod;
		}
	}
	cout<<f[n%2][0];
	return 0;
}
```

---

## 作者：船酱魔王 (赞：1)

## 题意回顾

括号序列中把左小括号可以替换为左右中括号，求替换成匹配的括号序列的方案数。

括号序列长度不超过 $ 3 \times 10^4 $。

## 分析

考虑合法括号序列的本质：匹配关系元组的集合。

如果我们确定了所有括号的匹配的括号的话，显然如果第一个括号的位置初始为右小括号是不能通过替换匹配的；如果第一个括号的位置初始为左小括号且第二个为右小括号，那么只能不变第一个位置；如果均为左小括号只能替换成左右中括号以能匹配。

故如果我们确定了所有括号的匹配关系的话，我们可以发现符合要求的括号序列不多于 $ 1 $ 个，且存在符合要求的括号序列的充要条件是每对匹配左侧初始为左小括号。

则设计 $ dp_{i,j} $ 为前 $ i $ 个位置还剩 $ j $ 个左小括号没有匹配，此时的匹配方案数。转移方程可以设计为 $ dp_{i,j}=dp_{i-1,j+1} $ 右括号情况和 $ dp_{i,j}=dp_{i-1,j+1}+dp_{i-1,j-1} $ 左括号情况。时间复杂度为 $ O(n^2) $。

考虑怎么优化，首先把 DP 数组边界多开一点来避免浪费时间的边界特判；发现左括号最多有 $ \frac{n}{2} $ 个维匹配否则必然对答案没有贡献。故在优化 $ 4 $ 倍左右的常数后程序以 O2 优化下最慢点 0.5s 左右的效率通过本题。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
const int N = 3e4 + 5;
const int mod = 1e9 + 9;
int n;
string s;
int dp[2][N];
int main() {
    cin >> n;
    cin >> s;
    s = " " + s;
    int cnt = 0;
    for(int i = 1; i <= n; i++) cnt += s[i] == '(';
    int fg = 1;
    dp[0][1] = 1;
    int opt = 1 + n / 2;
    for(int i = 1; i <= n; i++) {
        if(s[i] == ')') {
            for(int j = 1; j <= opt; j++) dp[fg][j] = dp[fg ^ 1][j + 1];
        } else {
            for(int j = 1; j <= opt; j++) dp[fg][j] = (dp[fg ^ 1][j - 1] + dp[fg ^ 1][j + 1]) % mod;
        }
        fg ^= 1;
    }
    printf("%d\n", dp[fg ^ 1][1]);
    return 0;
}
```

## 总结与评价

卡常差不多得了，强烈谴责不给纯指数做法部分分。

这启示我们评测机的速度远大于 $ 10^8 $，考场上要勇于相信自己的做法跑得过去，而不是怕跑不过去而不敢去写。

---

## 作者：yuantc (赞：1)

# 思路
分析一下题目，一眼就能看出是动态规划的经典题。

已经合法的括号不包括在寻找范围内，不需要管。

令 $f(i,j)$ 为第 $i$ 个括号有 $j$ 个不合法的情况的数量。分类讨论左右括号，是左括号，那么便有 $f(i,j)=f(i-1,j-1)+f(i-1,j+1)$ 。

右括号的话就是 $f(i,j)=f(i-1,j)$ 。

为了防止 MLE 所以要模二。
# 代码

```cpp
#include<bits/stdc++.h>
const int YUANTC=(int)1e9+9;
typedef char yuantc
using namespace std;
int dp[2][114514];
yuantc s[114514];
int main()
{
	int n,a=1;
	scanf("%d%s",&n,&s[a++]);
	dp[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=min(i,n-i);j++)
		{
			if (j==0||s[i]==')')
			{
				dp[i&1][j]=dp[(i-1)&1][j+1];
			}
			else
				dp[i&1][j]=(dp[(i-1)&1][j+1]+dp[(i-1)&1][j-1])%YUANTC;
		}
	}
	printf("%d",dp[n&1][0]%YUANTC);
}
```

---

## 作者：lzh301 (赞：1)

## Solution
题目给出可以将 $($ 替换为 $[$ 或 $]$，但是原序列是由圆括号组成的，所以考虑方括号和圆括号之间能否转换。

由于最终要求的是含方括号的合法序列，而成对的方括号是可以被成对的圆括号替换的，所以问题就转变为求合法的圆括号序列数，只需简单 dp 即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rg register
const int N=30010;
const int mod=1e9+9;
int n;
char c[N];
int dp[2][N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	dp[0][0]=1;
	for(rg int i=1;i<=n;i++){
		int m=min(i,n-i);
		int cnt=((i&1)+1)%2;
		for(rg int j=0;j<=m;j++){
			if(j==0||c[i]==')'){
				dp[i&1][j]=dp[cnt][j+1];
			}else{
				dp[i&1][j]=dp[cnt][j+1]+dp[cnt][j-1];
				dp[i&1][j]%=mod;
			}
		}
	}
	cout<<dp[n&1][0];
} 
```

---

## 作者：D_xbang (赞：0)

# 题意：
有一个长度为 $n$ 的不合法括号序列 $s$，其中 $\texttt{(}$ 可以替换成 $\texttt{)}$，求组成不同的合法括号序列的方案数并取模。

---

# 思路：
- 考虑使用动态规划，已经合法的括号不用管，所以寻找未匹配的括号即可。
- 定义 $$dp_{i,j}$$ 为方案数，$i$ 为当前括号的位置，$j$ 为不合法括号的数量。
- 初始化 $dp_{0,0}=1$，扫描一遍 $s$，若 $$s_{i}$$ 为 $\texttt{)}$，那么 $$dp_{i,j}=dp_{i-1,j}$$。否则 $$dp_{i,j}=dp_{i-1,j-1}+dp_{i-1,j+1}$$。
- 最后输出 $dp_{n,0}$ 并取模即可。
- 但空间会爆，采用滚动数组的形式，以此来优化。

---
# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9+9;
const int N = 30010;
int n, dp[2][N];
char s[N];
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i];
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= min(i, n - i ); j++) {
			if (s[i] == '(' && j) {
				dp[i % 2][j] = (dp[(i - 1) % 2][j + 1] + dp[(i - 1) % 2][j - 1]) % mod;
			} else {
				dp[i % 2][j] = dp[(i - 1) % 2][j + 1];
			}
		}
	}
	cout << dp[n % 2][0] % mod;
	return 0;
}
```

---

## 作者：RAY091016 (赞：0)

### 1. 题目解释

给出一个由 `(` 和 `)` 组成的字符序列，可以用 `[` 或 `]` 替换 `(`，问有多少种合法的序列。

### 2. 思路

典型 DP 题。

不难发现所有已匹配的括号是不用管的，只需要关注还未匹配的 `(`。

我们记 $f_{i,j}$ 为处理到第 $i$ 个括号，有 $j$ 个未匹配的括号的方案数。

我们分情况讨论左括号和右括号。

假如是左括号，那么方案数为 $f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}$。

否则为 $f_{i,j}=f_{i-1,j}$。

注意到空间会炸，所以我们采用模二的方式优化数组。

### 3. 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+9;
int f[2][30030],n; 
char s[30030];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=min(i,n-i);j++){
			if(j==0||s[i]==')')f[i%2][j]=f[(i-1)%2][j+1];
			else f[i%2][j]=(f[(i-1)%2][j+1]+f[(i-1)%2][j-1])%mod;
		}
	}
	cout<<f[n%2][0]%mod;
	return 0;
}
```

---

## 作者：zhangmuning1016 (赞：0)

# 题意
$\texttt{[}$ 和 $\texttt{]}$ 都可以被 $\texttt{(}$ 代替，给你一个替换后的字符串，问有多少个是合法括号序列的原字符串。

## 思路
- 这题使用动态规划。不用管已经匹配的括号，只需处理不匹配的括号。

- 令 $dp_{i, j}$ 表示处理到 $i$ 位置，左括号比右括号多 $j$ 个的方案数。

- $j$ 是不会小于 $0$ 的，因为方括号只会变成左圆括号，如果右括号更多，那么肯定是无解的，不需要统计。

## 代码：
```
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+1;
int dp[2][30001];
char s[30001];
int main() {
	int n;
	cin>>n>>s[1];
	dp[0][0]=1;
	for (int i=1; i<=n; i++) {
		int w=min(i, n-i);
		for (int j = 0; j <= w; j++) {
			if (j == 0 || s[i] == ')') {
				dp[i%2][j]=dp[(i-1)%2][j+1];
			} else {
				dp[i%2][j]=(dp[(i-1)%2][j+1]+dp[(i-1)%2][j-1])%mod;
			}
		}

	}
	cout<<dp[n%2][0]%mod;
	return 0;
}
```

---

## 作者：ZettaByte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7248)

### 题意

`[` 和 `]` 都可以被 `(` 代替，给你一个替换后的字符串，问有多少个是合法括号序列的原字符串。

### 解法

这题使用动态规划。不用管已经匹配的括号，只需要处理不匹配的括号就行了。

令 $dp_{i, j}$ 表示处理到 $i$ 位置时，左括号比右括号多 $j$ 个的方案数。

这里 $j$ 是不会小于 $0$ 的，因为方括号只会变成左圆括号，如果右括号更多，那么肯定是无解的，不需要统计。

转移方程：

- 当 $s_i$ 为 `(` 时，$dp_{i, j}=dp_{i-1, j+1}+dp_{i-1, j-1}$；

- 当 $s_i$ 为 `)` 时，$dp_{i, j}=dp_{i-1, j+1}$。

为了节省空间，我们可以使用滚动数组。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9 + 9;
int dp[2][30010]; char s[30010];

int main()
{
	int n; scanf("%d%s", &n, s + 1), dp[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= min(i, n - i); j++)
			if (j == 0 || s[i] == ')') dp[i & 1][j] = dp[(i-1)&1][j + 1];
			else dp[i & 1][j] = (dp[(i-1)&1][j + 1] + dp[(i-1)&1][j - 1]) % mod;
	printf("%d\n", dp[n & 1][0] % mod);
	return 0;
}
```

---

## 作者：lidagua1004 (赞：0)

这道题如果 `(` 已经和后面的 `)` 匹配了那么不用管了。

对于不匹配括号的处理就 $2$ 种，要么与上一个不匹配的括号组成一对，要么等待下一个不匹配括号，用 dp 处理，时间复杂度 $O(n^2)$。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[2][100500]={1};
signed main(){
	int n,sum=0;cin>>n;
	char c;
	for(int i=1;i<=n;i++){
		cin>>c;
		for(int j=0;j<=min(i,n-i);j++)
			if(!j||c==')') dp[i&1][j]=dp[i+1&1][j+1];
			else dp[i&1][j]=(dp[i+1&1][j+1]+dp[i+1&1][j-1])%1000000009;
	}
	cout<<dp[n&1][0];
	return 0;
}
```

---

## 作者：gzqlbx666 (赞：0)

[$\color{blue} \text{P7248 题目传送门}$](https://www.luogu.com.cn/problem/P7248)

# 题意
给出一个不合法括号序列，求有多少种合法括号序列，在将其中的方括号用 ( 代替后，可以得到给定的括号序列。
# 思路

**45分思路**

我们定义 $f_{l,r}$ 表示区间 $l,r$ 中的方案数，枚举 $k∈l+1,r$ 表示和第 $l$ 个括号匹配的位置，可得到以下式子：
$$ f_{l,r}=f_{l+1,k-1}*f_{k+1,r} $$
$O(N^3)$ ，注意一下常数可以拿 $45$ 分。

**AC思路**

观察一下发现我们的式子，等价于用一个 "("  和  ")" 匹配，或者和 “)” 匹配。所以我们只用记录前面有多少个 “(” 没有匹配即可。

定义状态 $f_{i,j}$ 表示前面 $i$ 个位置，还有 $j$ 个左括号没有匹配的方案，$O(N^2)$ 转移一下即可。本来以为有什么离大谱神奇做法，没想到 $N^2$ 直接过了……

### 不给代码了，自己写吧（

---

