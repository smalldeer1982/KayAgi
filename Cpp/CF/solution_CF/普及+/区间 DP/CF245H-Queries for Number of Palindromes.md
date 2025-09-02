# Queries for Number of Palindromes

## 题目描述

题目给定一个仅由小写字母组成的字符串 $s$，下标从 $1$ 开始。

有 $Q$ 次询问，每组询问给定两个数 $l$ 和 $r$，表示询问 $s_l \sim s_r$ 这段区间中包含了多少个[回文串](https://baike.baidu.com/item/%E5%9B%9E%E6%96%87%E4%B8%B2/1274921)。注意单独一个字符也算回文串。

## 样例 #1

### 输入

```
caaaba
5
1 1
1 4
2 3
4 6
4 5
```

### 输出

```
1
7
3
4
2
```

# 题解

## 作者：Fuko_Ibuki (赞：18)

这题是个好题,当然做法也不止区间$dp$一种.  
首先用中点向外扩散法预处理哪些区间是回文串,这个的复杂度是$O(n^2)$.  
如果你不知道怎么中点向外扩散,我来说明一下.  
假设$dp[l][r]$表示$[l,r]$区间的子串是否是回文串.  
显然$dp[i][i]$肯定为$1$.  
如果$s[i-1]=s[i+1]$,那么$dp[i-1][i+1]$也是$1$.  
这样子每次设两个指针$j,k$,一个往左,一个往右,直到到头或者$s[j]$和$s[k]$不相同`break`.  
注意回文串有奇数长度和偶数长度两种情况,$j,k$的初值有所不同,都要处理.  
接下来把$dp$数组输出来观察,并感性理解.
对于$[l,r]$的所有子串,它的左右端点都在$[l,r]$之间.  
如果反映在$dp$数组上,就是$(l,l)$和$(r,r)$这个子矩阵了.  
那么这个区间内回文串的个数就是$dp$数组这个子矩阵的和.
这样只要对$dp$数组求一个二维前缀和就可以过了.
```cpp
#include<bits/stdc++.h> //Ithea Myse Valgulious
using namespace std;
const int aoi=5038;
char s[aoi]; 
int dp[aoi][aoi];
int main() {
scanf("%s",s+1);
int i,j,k,q=read(),n=strlen(s+1);
for (i=1;i<=n;++i) {
  for (j=k=i;j&&k<=n&&s[j]==s[k];--j,++k) ++dp[j][k];
  for (j=i,k=i+1;j&&k<=n&&s[j]==s[k];--j,++k) ++dp[j][k];
  }
for (i=1;i<=n;++i)
  for (j=1;j<=n;++j)
    dp[i][j]+=dp[i][j-1]+dp[i-1][j]-dp[i-1][j-1];
for (int l,r;q--;) {
  read(l),read(r);
  write(dp[r][r]-dp[l-1][r]-dp[r][l-1]+dp[l-1][l-1]),pl;
  }
}
```
谢谢大家.

---

## 作者：王熙文 (赞：13)

这道题是区间 dp 的好题。

## 题意

给出一个字符串 $S$，有 $q$ 次询问，每次求出区间 $[l,r]$ 内有多少个回文子串。

$|S| \le 5000,q \le 10^6$

## 思路

看到数据范围，显然是用 $O(|S|^2)$ 预处理出每个区间的回文子串个数，$O(1)$ 查询。

看到区间，可以想到区间 dp。

状态表示：$dp_{i,j}$ 表示在区间 $[i,j]$ 里回文子串的个数。

定义 $\text{endCnt}_{i,j}$ 表示左端点大于等于 $i$，右端点为 $j$ 是有多少个回文子串。

那么状态转移方程为：`dp[i][j]=dp[i][j-1]+endCnt[i][j]`。

现在的问题就转化成了如何 $O(n^2)$ 求出 $\text{endCnt}$。

想要求出来这个，就先要预处理出来某段字串是否为回文子串。

定义 $f_{i,j}$ 表示左端点为 $i$，右端点为 $j$ 的子串是否为回文子串。

区间 dp 的思想是已求出了一个长度短的区间，转移到更长的区间。

当这个区间的左右两个端点相同，并且 $f_{i+1,j-1}$ 为回文子串，那么 $f_{i,j}$ 即时回文子串。

每一次转移都必须已经求出了小的区间，那么如何用 $i,j$ 枚举区间呢？

考虑将 $i$ 从 $l$（$l$ 为 $|S|$）到 $1$ 遍历，将 $j$ 从 $i$ 到 $l$ 遍历。这样遍历，之前的 $i$ 已经处理出来了 $f_{i+1,j-1}$。

当区间长度为 $1$ 或 $2$ 的时候，$f_{i+1,j-1}$ 都需要赋 $1$，所以最开始就把 $f$ 数组都赋成 $1$。

这是预处理 $f$ 数组的代码（我的字符串数组是从 $1 \sim l$ 的）：

```cpp
memset(f,1,sizeof(f));
for(int i=l; i>=1; --i)
{
	for(int j=i; j<=l; ++j)
	{
		f[i][j]=(f[i+1][j-1]&(s[i]==s[j]));
	}
}
```

接下来就考虑如何求 $\text{endCnt}$ 数组。

这回我们先枚举 $j$，因为 $j$ 是固定的（右端点固定），而 $i$ 不是。对于每一个 $j$（右端点），枚举 $i$ 的时候从 $j$ 到 $1$ 枚举，我们已知 $\text{endCnt}_{i+1,j}$，$\text{endCnt}_{i,j}$ 就是 $\text{endCnt}_{i+1,j}$ 再加上左端点为 $i$ 右端点为 $j$ 的情况是否为回文子串。那么这个的转移就是 `endCnt[i][j]=endCnt[i+1][j]+f[i][j]`。

这是预处理 $\text{endCnt}$ 的代码：

```cpp
for(int j=1; j<=l; ++j)
{
	for(int i=j; i>=1; --i)
	{
		endCnt[i][j]=endCnt[i+1][j]+f[i][j];
	}
}
```

最后，就是求出 $dp$ 数组了，上文已给出状态转移方程，这里只给出代码：

```cpp
for(int i=1; i<=l; ++i)
{
	for(int j=i; j<=l; ++j)
	{
		dp[i][j]=dp[i][j-1]+endCnt[i][j];
	}
}
```

最后的最后，对于每一次查询输出 $dp_{l,r}$ 即可。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

char s[5010];

bool f[5010][5010];

int endCnt[5010][5010];

int dp[5010][5010];

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>(s+1);
	int l=strlen(s+1);
	memset(f,1,sizeof(f));
	for(int i=l; i>=1; --i)
	{
		for(int j=i; j<=l; ++j)
		{
			f[i][j]=(f[i+1][j-1]&(s[i]==s[j]));
		}
	}
	for(int j=1; j<=l; ++j)
	{
		for(int i=j; i>=1; --i)
		{
			endCnt[i][j]=endCnt[i+1][j]+f[i][j];
		}
	}
	for(int i=1; i<=l; ++i)
	{
		for(int j=i; j<=l; ++j)
		{
			dp[i][j]=dp[i][j-1]+endCnt[i][j];
		}
	}
	int q,x,y;
	cin>>q;
	while(q--)
	{
		cin>>x>>y;
		cout<<dp[x][y]<<'\n';
	}
	return 0;
}
```

---

## 作者：SSHhh (赞：11)

这道题的思路就是区间 dp ，用 dp[i][j] 表示在 i 到 j 的这个区间内的回文串数量，~~这应该十分好想。~~ 不过在推导状态转移方程时可能会出问题：

一般想到的应该是 dp[i][j]=dp[i][k]+dp[k+1][j]+(i 到 j 这一段是不是一个回文串)。但是这样做的话你会忽略 (i 到 k 之间的某个字符) 到 (k 到 j 之间的某个字符) 这样的某一段也是回文串的情况。这个问题如果要解决的话需要再在 i 到 k 之间和 k 到 j 之间 重新计算，但是个人感觉会写挂，且三重循环复杂度是 O(n³)，会TLE ，所以这个方法是不可行的。

那么 dp[i][j] 还有一种转移方法。记得小学的容斥原理吧，两边分别包括的之和减去中间重复算的位置就是总体的数量。这个方法放在 dp 中同样可行： dp[i][j]=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1]; 这样中间所有组成的回文串都会被包括在内，不会出现像第一种方法的 (i 到 k 之间) ~ (k 到 j 之间)的情况，被忽略掉的只有 i 到 j 这个字符串，那么加一个特判即可。

这样 dp 方程就变成了：dp[i][j]=(dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1]+(*i 到 j 这一段是不是一个回文串*)?1:0);

不过必须提一下的是，判断 i 到 j 是不是一个回文串时，不能用传统 O(n/2) 判断，那样仍然会超时，需要用到记忆化搜索，才能AC。记忆化搜索 sigma(复杂度)=n²(加法复杂度，总复杂度 O
(2n²)。

```cpp
#include<iostream>
#include<string.h>
using namespace std;
string a;
int n,q,dp[5005][5005],OK[5005][5005]/*判断是不是一个回文串*/;
bool is_palindrome(int l,int r) //判断 i 到 j 是不是一个回文串
{
	if(OK[l][r]!=-1)	return OK[l][r];
	if(l==r)	return OK[l][r]=1;
	else if(l==r-1)	return OK[l][r]=a[l]==a[r]?1:0;
	if(a[l]!=a[r])	return OK[l][r]=0;
	return OK[l][r]=is_palindrome(l+1,r-1);	//记忆化搜索
}
int main()
{
	memset(OK,-1,sizeof(OK));
	int x,y;
	cin>>a>>q;
	n=a.size(),a=" "+a;	//把字符串下标转成从 1 开始
	for(int i=1;i<=n;i++)	dp[i][i]=1;						
	for(int i=1;i<=n-1;i++)	dp[i][i+1]=(a[i]==a[i+1]?3:2);	//初始化就不用说了
	for(int i=n-2;i>=1;i--)
		for(int j=i+2;j<=n;j++)	//因为初始化过了，只枚举区间长度大于等于 3 的区间
			dp[i][j]=(dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1]+(is_palindrome(i,j)?1:0));
	while(q--)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",dp[x][y]);
	}
	return 0;
}

```

---

## 作者：LCat90 (赞：4)

区间 ``dp`` 的简单题。

首先，我们可以预处理出每个区间是否是回文，这很简单。

$f_{i,j}=f_{i+1,j-1}(s_i=s_j)$ 

我们再利用 $f$ 数组去更新 $dp$。定义 $dp_{i,j}$ 表示区间 $[i,j]$ 中回文串的数量，则有：

$dp_{i,j}=dp_{i+1,j}+dp_{i,j-1}-dp_{i+1,j-1}+f_{i,j}$

解释一下，其中减去 $dp_{i+1,j-1}$ 这是转移式中前面两个区间中重复计算的部分，$f_{i,j}$ 是判断自己是否是回文串。

```cpp
#include <bits/stdc++.h>
#define sf scanf
#define pf printf
using namespace std;
const int Maxn = 5e3 + 5;
char c[Maxn];
int n, q, a, b;
long long dp[Maxn][Maxn];
bool f[Maxn][Maxn];
int main() {
    sf("%s", c + 1);
    n = strlen(c + 1);
    for(int i = 1;i <= n; ++i) {
    	dp[i][i] = f[i][i] = 1;
    	if(c[i] == c[i - 1]) f[i - 1][i] = 1;
	}
	for(int l = 3;l <= n; ++l)
    	for(int i = 1;i <= n - l + 1; ++i) {
    		int j = i + l - 1;
    		if(c[i] == c[j]) f[i][j] = f[i + 1][j - 1];
		}
    for(int l = 2;l <= n; ++l)
    	for(int i = 1;i <= n - l + 1; ++i) {
    		int j = i + l - 1;
    		dp[i][j] = -dp[i + 1][j - 1] + dp[i + 1][j] + dp[i][j - 1] + f[i][j];
		}
	sf("%d", &q);
	while(q--) {
		sf("%d %d", &a, &b);
		pf("%lld\n", dp[a][b]);
	}
    return 0;
}
```


---

## 作者：Durant_Lee (赞：4)

$n$很小，那么我们枚举字符串的左端点，用回文自动机求出每个右端点对应的答案即可。

复杂度$O(n^2+Q)$

这里用的是基于势能分析的写法。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5005;
int Q,m,res,ans[N][N];
char s[N];

namespace IO
{
	int read()
	{
		int ret=0;char c=getchar();
		while(!isdigit(c)) c=getchar();
		while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
		return ret;
	}
	void write(int x){if(x>9)write(x/10);putchar(x%10^48);}
	void writeln(int x){write(x);putchar('\n');}
}

struct PAM
{
	char a[N];
	int n,las,sz,fa[N],len[N],dep[N],ch[N][26];
	void init()
	{
		memset(a,'\0',sizeof(a));memset(fa,0,sizeof(fa));memset(len,0,sizeof(len));
		memset(dep,0,sizeof(dep));memset(ch,0,sizeof(ch));
		las=n=0;fa[0]=sz=1;len[1]=-1;
	}
	void extend(int x)
	{
		a[++n]=x^'a';int p=las,q,now;
		while(a[n-len[p]-1]^a[n]) p=fa[p];
		if(!ch[p][x])
		{
			q=++sz;len[q]=len[p]+2;now=fa[p];
			while(a[n-len[now]-1]^a[n]) now=fa[now];
			fa[q]=ch[now][x];dep[q]=dep[fa[q]]+1;ch[p][x]=q;
		} 
		las=ch[p][x];res+=dep[las];
	}
}S;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF245H.in","r",stdin);
	freopen("CF245H.out","w",stdout);
#endif
	scanf("%s",s+1);m=strlen(s+1);
	for(int i=1;i<=m;++i)
	{
		S.init();res=0;
		for(int j=i;j<=m;++j) S.extend(s[j]^48),ans[i][j]=res;
	}
	Q=IO::read();
	while(Q--)
	{
		int l=IO::read(),r=IO::read();
		IO::writeln(ans[l][r]);
	}
	return 0;
}

```

---

## 作者：cqbzlwz (赞：3)

[题目](https://www.luogu.com.cn/problem/CF245H)

### 分析
1.数据范围中，$n\leq 5000$，因此可以考虑 $O(n^2)$ 的算法。

2.要求回文串的个数，可以先预处理出对于这个字符串的每个子串，它们是不是回文串。代码如下：
```cpp
for (int len = 1; len <= n; ++len) {//枚举子串长度
	for (int i = 1; i <= n - len + 1; ++i) {//枚举左端点
		int j = i + len - 1;//计算右端点，此时判断[i,j]是否是回文串
		if (a[i] != a[j]) continue;//如果左右两边不等，一定不是
		if (j - i <= 1 || b[i + 1][j - 1]) b[i][j] = 1;
		//有以下的情况：
		//1.i=j，此时就是回文串
		//2.i+1=j，此时因为已经去除两端不同的情况，所以此时也是
		//3.b[i+1][j-1]=true,此时因为去掉两边后是回文串，所以两边各
		//加上相同的字符也是回文串。如:bcb是回文串，abcba也是回文串
	}
}
```

3.要求出一段区间内的方案数，很容易想到区间 $dp$，定义 $dp_{ij}$ 表示 $[i,j]$ 这个区间内有多少回文串。但区间 $dp$ 的时间复杂度高达 $O(n^3)$，显然不能通过。区间的两端肯定要枚举，因此可以尝试把断点那一维去掉。怎么不枚举断点呢？先看一个区间 $[i,j]$：

| $[i]\ $ | $[i+1]\ $ |  $[...]\ $  | $[j-1]\ $ | $[j]\ $ |
| :----------: | :----------: | :----------: | :----------: | :----------: |

想要得到 $[i,j]$ 中的回文串个数，我们可以先把 $[i,j-1]$ 的个数加上，再进行推导。此时还缺少区间内包含 $j$ 的回文串个数，再把 $[i+1,j]$ 加上：

| $[i]\ $ | $[i+1]\ $ |  $[...]\ $  | $[j-1]\ $ | $[j]\ $ |
| :----------: | :----------: | :----------: | :----------: | :----------: |

| $[i]\ $ | $[i+1]\ $ |  $[...]\ $  | $[j-1]\ $ | $\ $ |
| :----------: | :----------: | :----------: | :----------: | :----------: |

| $\ \ \ \ $ | $[i+1]\ \ $ |  $[...]\ $  | $[j-1]\ $ | $[j]\ $ |
| :----------: | :----------: | :----------: | :----------: | :----------: |

可以发现，$[i+1,j-1]$ 部分被加了两次，再减去即可。
由于 $[i,j]$ 自身也有可能是回文串，如果 $[i,j]$ 是回文串，还要加 $1$。

那么 $dp$ 的转移方程就是：
$dp_{i,j}=dp_{i+1,j}+dp_{i,j-1}-dp_{i+1,j-1}\ (s_i=s_j,!b_{i,j})$

$dp_{i,j}=dp_{i+1,j}+dp_{i,j-1}-dp_{i+1,j-1} + 1\ (s_i=s_j,b_{i,j})$

($b_{i,j}$ 表示 $[i,j]$ 是否为回文串)

于是，我们成功地预处理出了每个区间内的回文串数量：
```cpp
for (int i = 1; i <= n; ++i) dp[i][i] = 1;//初始化!!!
for (int len = 2; len <= n; ++len) {//枚举长度
	for (int i = 1; i <= n - len + 1; ++i) {//枚举左端点
		int j = i + len - 1;//计算右端点
		dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] 
		+ b[i][j];//转移方程
	}
}
```

4.对于每组询问 $[l,r]$，输出 $dp_{l,r}$：

```cpp
while (q--) {
	scanf("%d%d", &l, &r);
	printf("%d\n", dp[l][r]);
}
```


---

## 作者：0x3F (赞：2)

题意就是输入一个字符串并询问其区间中回文子串的数量。

我们发现 $q$ 很大，于是猜测每一次询问是 $\mathcal{O}(1)$ 的。

又由于 $|s|$ 的范围为 $5000$，可以支持 $\mathcal{O}(n^2)$ 的算法，于是猜测需要 $\mathcal{O}(n^2)$ 预处理所有区间中的回文子串的数量。

首先需要知道每一个串是否回文。

暴力肯定是不行的，我们可以尝试通过已经求出的部分来求没有求出的部分。

如果一个串是回文的，那么显然其首尾字符相同，而将其去掉首尾以后仍为回文。

那么边界条件是怎样的呢？

显然长度为 $1$ 的串必然是回文的，长度为 $2$ 的串如果两个字符相同则为回文。（此处不考虑空串）

于是有递推式：

$$isP_{l, r} = \begin{cases}1&r=l\\ [str_l = str_r]&r=l+1\\ [str_l=str_r\land isP_{l+1,r-1}]&r>l+1\end{cases}$$

其中的 $\land$ 是逻辑与运算。

然后知道了每一个串是否为回文，如何求出区间内回文子串的数量？

可以使用容斥原理。

$[l,r]$ 中的子串的左端点要么是 $l$，要么不是 $l$。

右端点要么是 $r$，要么不是 $r$。

这不废话吗？

把他们合并一下：

1. 左端点为 $l$，右端点为 $r$。
1. 左端点为 $l$，右端点不为 $r$。
1. 左端点不为 $l$，右端点为 $r$。
1. 左端点不为 $l$，右端点不为 $r$。

第一种情况如果 $[l, r]$ 是回文串则为 $1$，否则为 $0$。

第二种情况把左端点定为有一定难度，把他拆成“左端点随意，右端点不为 $r$”减去“左端点不为 $l$，右端点不为 $r$”。

右端点不为 $r$ 就是到 $r-1$ 为止。

左端点随意就是从 $l$ 开始，不为就是从 $l+1$ 开始。

所以第二种情况的答案为 $cnt_{l, r-1}-cnt_{l+1, r-1}$。。

同理第三种情况的答案为 $cnt_{l+1, r}-cnt_{l+1, r-1}$。

第四种显然就是 $cnt_{l+1, r-1}$。

四种情况加一加，得到：

$$cnt_{l,r}=isP_{l,r}+(cnt_{l, r-1}-cnt_{l+1, r-1})+(cnt_{l+1, r}-cnt_{l+1, r-1})+cnt_{l+1, r-1}$$

$$=isP_{l,r}+cnt_{l,r-1}+cnt_{l+1,r}-cnt_{l+1,r-1}$$

如果还不能理解，想想二维前缀和。

加上边界的情况就是：

$$cnt_{l, r}=\begin{cases}1&r=l\\isP_{l,r}+2&r=l+1\\isP_{l,r}+cnt_{l,r-1}+cnt_{l+1,r}-cnt_{l+1,r-1}&r>l+1\end{cases}$$

另外注意枚举时不能先枚举左端点再枚举右端点，应当先枚举区间大小再枚举区间位置，保证递推时所需要的内容已经求过了。

还有由于读入量比较大，请使用 `scanf` 和 `printf` 谢谢。

（我才不会告诉你我不会打快读）

```cpp
#include <bits/stdc++.h>
#define r (l+len-1)
using namespace std;
int T, n, L, R;
char ch[5010];
bool isP[5010][5010];
int cnt[5010][5010];
int main() {
	cin >> (ch+1);
	n = strlen(ch+1);
	for (int i = 1; i <= n; i++) {
		cnt[i][i] = isP[i][i] = 1;
	}
	for (int i = 1; i < n; i++) {
		if (ch[i] == ch[i+1]) {
			isP[i][i+1] = 1;
			cnt[i][i+1] = 3;
		} else {
			isP[i][i+1] = 0;
			cnt[i][i+1] = 2;
		}
	}
	for (int len = 3; len <= n; len++) {
		for (int l = 1; r <= n; l++) {
			if (ch[l] == ch[r] && isP[l+1][r-1]) {
				isP[l][r] = 1;
				cnt[l][r] = cnt[l][r-1] + cnt[l+1][r] - cnt[l+1][r-1] + 1;
			} else {
				isP[l][r] = 0;
				cnt[l][r] = cnt[l][r-1] + cnt[l+1][r] - cnt[l+1][r-1];
			}
		}
	}
	cin >> T;
	while (T--) {
		scanf("%d%d", &L, &R);
		printf("%d\n", cnt[L][R]);
	}
	return 0;
}
```

$$\huge{\texttt{\color{white}{求过，求赞}}}$$

---

## 作者：chenpengjin (赞：0)

**区间 $dp$**
## 思路
看到数据范围就知道这是一道区间 $dp$。我们定义 $dp_{i, j}$ 为区间 $i$ 到 $j$ 区间内的回文串的数量。

转移式一般会想到 $dp_{i, j} = dp_{i, k} + dp_{k + j} + 1$ 但这样不仅中间回文串被拆开了，答案会少统计，而且时间复杂度达到了 $O(n ^ 3)$ 肯定会 TLE。

那我们就想能不能直接用 $i$ 和 $j$ 推导转移式。为了不遗漏我们可以直接用 $dp_{i + 1, j} + dp_{i, j - 1}$ 来推导。这样区间之中的所有字符串都可以被统计到，但这样我们又面临新的问题 $dp_{i + 1, j - 1}$ 的这部分被重复算了一遍，怎么办了？这很好办只需要减去 $dp_{i + 1, j - 1}$就可以。所以最后的转移式是：

> $dp_{i, j} = dp_{i + 1, j} + dp_{i, j - 1} - dp_{i + 1, j - 1}$

就这样完了吗？

没有，如果区间 $i$ 到 $j$ 本身就是一个回文串我们则需将 $dp_{i, j}$ 的答案加一即可。这种情况在后面加一个特判就可以了。
## code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 5e3 + 5;
char s[MAXN];
int n, m;
int dp[MAXN][MAXN];
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
		dp[i][i] = 1;
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
			if (s[i] == s[j] && (dp[i + 1][j - 1] == dp[i + 2][j - 1] + dp[i + 1][j - 2] - dp[i + 2][j - 2] + 1 || l <= 2))
				dp[i][j]++;
		}
	}
	scanf("%d", &m);
	while (m--) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", dp[l][r]);
	}
	return 0;
}
```

---

## 作者：UperFicial (赞：0)

同步发表于我的 [$\text{cnblog}$](https://www.cnblogs.com/UperFicial/p/16352956.html)。

我写完了发现自己是个傻逼。

为啥题解都是区间 DP 啊，提供一个不同的难写做法。

考虑求出 $f_{i,j}$ 表示 $[i,j]$ 的回文串的数量，这样对于询问能做到 $\Theta(1)$。

对于每一个 $f_{i,j-1}$ 可以转移到 $f_{i,j}$，加上“以 $s_j$ 结尾的左端点在 $[i,j]$ 中的回文串的数量”即可。

这个转移的时候直接算不太高明，考虑先求 $g_i$ 表示以 $s_i$ 为结尾的**所有**回文子串开头出现的**位置集合**。

这样我们在转移的时候在 $g_j$ 上二分一个位置即可。$g$ 可以用 vector 来实现。

$g$ 的求法就很简单了。我们直接枚举一个 $j(j\le i)$ 然后判断 $[j,i]$ 是否是回文子串即可。

这个操作用哈希可以实现，对于原串建立反串，两边判断一下就好了。

最后复杂度 $\Theta(n^2\log n+q)$。瓶颈在于二分。

~~竟然比大多数 $\sout{\Theta(n^2)}$ 的做法跑的快。~~

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<climits>
#include<queue>
#include<vector>
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define Inf(a) memset(a,0x3f,sizeof(a))
#define Clear(a) memset(a,0,sizeof(a))
#define gra(i,u) for(register int i=head[u];i;i=edge[i].nxt)
#define rev(i,a,b) for(register int i=a;i>=b;--i)
using namespace std;
typedef long long ll;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' or ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' and ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
const int INF=1e9+10;
template<typename T>
inline T Max(T x,T y){return x>y?x:y;}
template<typename T>
inline T Min(T x,T y){return x<y?x:y;}
template<typename T>
inline void Swap(T&x,T&y){T t=x;x=y;y=t;return;}
template<typename T>
inline T Abs(T x){return x>0?x:-x;}
const int MAXN(5010);
int n,q;
char s[MAXN];
int dp[MAXN][MAXN];
vector<int>g[MAXN];
struct HASH
{
	typedef unsigned long long ull;
	ull h[MAXN],fac[MAXN];
	const ull Base=114514;
	inline void build(char*c)
	{
		fac[0]=1;
		rep(i,1,n) h[i]=h[i-1]*Base+(c[i]-'a'+1),fac[i]=fac[i-1]*Base;
		return;
	}
	inline ull get_hash(int l,int r){return h[r]-h[l-1]*fac[r-l+1];}
};
HASH h1,h2;
inline bool check(int l,int r)
{
	int mid=(l+r)>>1;
	if((l+r)%2==0) return h1.get_hash(l,mid)==h2.get_hash(n-r+1,n-mid+1);
	else return h1.get_hash(l,mid)==h2.get_hash(n-r+1,n-(mid+1)+1);
}
inline int Find(int i,int x)
{
	if(g[i].empty()) return -1;
	int l=0,r=g[i].size()-1,res(-1);
	if(g[i][l]>=x) return l;
	else if(g[i][r]<x) return -1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(g[i][mid]>=x) res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
}
inline int calc(int i,int j)
{
	int p=Find(j,i);
	if(p==-1) return 0;
	return g[j].size()-p; 
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	h1.build(s);
	reverse(s+1,s+1+n);
	h2.build(s);
	
	rep(i,1,n)
	{
		g[i].push_back(i);
		rep(j,i+1,n)
			if(check(i,j)) g[j].push_back(i);
	}
	rep(i,1,n) sort(g[i].begin(),g[i].end());
	rep(i,1,n) dp[i][i]=1;
	rep(i,1,n) rep(j,i+1,n) dp[i][j]=dp[i][j-1]+calc(i,j);
	q=read();
	while(q--)
	{
		int l=read(),r=read();
		printf("%d\n",dp[l][r]);
	}
	return 0;
}
```


---

## 作者：wzy2021 (赞：0)

我们来看一下这道题：

区间问题，容易想到区间 $dp$

那么设 $dp_{l, r}$ 表示在区间 $(l, r)$ 内有多少个回文子串。

因为两个回文串组合起来不一定是回文串，例：$aa$ 与 $bb$，

而两个非回文串组合起来有可能是回文串，例：$abc$ 与 $ba$，

所以 $dp_{i, j}$ 无法通过 $dp_{i, k}$ 与 $dp_{k + 1, j}$ 所转移。

那么我们换一个角度想：

首先，区间 $(l + 1, r)$ 里的回文串也是区间 $(l, r)$ 里的回文串，区间 $(l, r - 1)$ 同理。

$$dp_{l, r} = dp_{l + 1, r} + dp_{l, r - 1}$$

但两区间都包含区间 $(l + 1, r - 1)$，我们再减去他：

$$dp_{l, r} = dp_{l + 1, r} + dp_{l, r - 1} - dp_{l + 1, r - 1}$$

上面其实就是用了容斥原理，~~干嘛要说那么具体呢？~~

还考虑到整个区间是否为回文串

$$dp_{l, r} = dp_{l + 1, r} + dp_{l, r - 1} - dp_{l + 1, r - 1} + check (l, r) ? 1 : 0$$

$? :$ 是三位运算符，不懂可去网上找一找，

其中 $check (l, r)$ 表示区间 $(l, r)$ 是否为回文串，

在求 $check (l, r)$ 要用到记忆化搜索。

得出了 $dp_{i, j}$ 后，查询可 $O(1)$ 完成。

具体可看程序。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 5010;
char s[maxn];
int n, f[maxn][maxn], dp[maxn][maxn];

bool check (int l, int r) {
    if (f[l][r] != -1) return f[l][r]; // 记忆化搜索
    if (l >= r) return f[l][r] = 1; // 注意判断条件！！！ 
    if (s[l] != s[r]) return f[l][r] = 0;
    return f[l][r] = check (l + 1, r - 1);
}

int main() {
    memset (f, -1, sizeof (f)); // 注意！！！
    scanf ("%s", s + 1); n = strlen (s + 1);
    for (int i = 1; i <= n; ++i) dp[i][i] = 1; // 初始化
    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
            if (check (i, j)) dp[i][j] ++;
        }
    } // 预处理
    int T; scanf ("%d", &T);
    while (T --) {
        int x, y; scanf ("%d%d", &x, &y);
        printf ("%d\n", dp[x][y]); // 输出
    }
    return 0;
}
```


---

## 作者：CGDGAD (赞：0)

## 题解 CF245H 【Queries for Number of Palindromes】

----

### 简化题意

给定一个字符串 $s$，$q$ 次询问 $[l,r]$ 区间内的回文子串个数。

数据规模：$\left|s\right| \le 5\times 10^3$，$q \le 10^6$。

----

### DP 分析

先看一下一个经常遇到的问题：询问区间 $[l,r]$ 是否是回文子串。

设 $f(l,r)$ 为 $[l,r]$ 是否是回文子串。

$$
f(l,r) = 
\begin{cases}
1 & f(l+1,r-1) \text{ and } (s_l=s_r) \\
0 & otherwise.
\end{cases}
$$

如果是双字符的话会导致 $l+1>r-1$，提前处理一下双字符和单字符子串就行了。

由于是从小区间 $[l+1,r-1]$ 推到大区间 $[l,r]$，那么就需要区间 dp 的写法，从区间长度为 $3$ 开始 dp，因为已预处理双字符和单字符。

那么，如何类似地，求解这个区间内回文子串个数的问题呢？

设 $g(l,r)$ 为 $[l,r]$ 内回文子串个数。

$$
g(l,r) = g(l+1, r) + g(l, r-1) - g(l+1, r-1) + f(l, r)
$$

也就是说，分别考虑左边、右边的小区间，减去中间的区间，再加上最终大区间是否是回文串就行了。

区间 dp 的方式计数即可。可以先预处理对于所有的 $i$，$g(i, i) = 1$，剩下的从区间长度为 $2$ 开始 dp。

这里的 $g(l,r)$ 也可以被看作二维前缀和。

### 核心实现

```cpp
int main() {
	scanf("%s", s + 1); // 字符串下标从 1 开始方便 dp。
	int n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) {
		f[i][i] = true, g[i][i] = 1; // 单字符预处理。
		if (i >= 2)
			f[i - 1][i] = (s[i] == s[i - 1]); // 双字符预处理。
	}
	for (int len = 3; len <= n; ++len)
		for (int l = 1; l <= n - len + 1; ++l) {
			const int r = l + len - 1;
			f[l][r] = f[l + 1][r - 1] && (s[l] == s[r]);
		}
	for (int len = 2; len <= n; ++len)
		for (int l = 1; l <= n - len + 1; ++l) {
			const int r = l + len - 1;
			g[l][r] = g[l + 1][r] + g[l][r - 1] - g[l + 1][r - 1] + f[l][r];
		}
	q = read();
	while (q--) {
		int l = read(), r = read();
		printf("%d\n", g[l][r]);
	}
	return 0;
}
```

---

## 作者：StupidSeven (赞：0)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/CF245H)

## Analysis
注意到这题的字符串长度最多只有 $5 \times 10^3$ ，$O(n^2)$ 的算法就足够了。我们可以用 $O(n^2)$ 的复杂度来预处理每一个子串是不是回文串，就是一个递推的思想，如果下标 $L+1$ 到 $R-1$ 的子串是回文串，那么当且仅当 $S[L]=S[R]$ 时，下标 $L$ 到 $R$ 的子串是回文串。边界就是如果一个子串长度只有 $1$ 时，它一定是回文串。如果长度是 $2$ ，就要判断 $S[i]$ 是否等于 $S[i+1]$ 。我们可以开一个二位数组 $val$ 记录状态，如果下标 $L$ 到 $R$ 的字串是回文串，那么 $val[L][R]=1$ ，否则为 $0$ 。

现在考虑设计状态求解，设 $dp[L][R]$ 表示下标 $L$ 到 $R$ 的子串中回文子串的个数，那么根据容斥原理，我们可得转移方程：

- $dp[L][R]=dp[L+1][R]+dp[L][R-1]-dp[L+1][R-1]+val[L][R]$

预处理一下，$dp[i][i]=1$ 。

还得注意一个特判，如果 $S[i]=S[i+1]$ , $dp[i][i+1]=3$ ，否则为 $2$ 。剩下的就是 dp 了

## Code
```cpp
#include<queue>
#include<cmath>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=5e3+10;
const int inf=1e9;
const int Mod=1e9+7;
inline int Read(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;    
}
string str;
int n,m,lson,rson,dp[M][M];
int val[M][M];
signed main(void){
	cin>>str;
	n=str.length();
	str=" "+str;
	m=Read();
	for(int i=1;i<=n;i++) val[i][i]=true,dp[i][i]=1;
	for(int i=1;i<n;i++)
		if(str[i]==str[i+1])
			dp[i][i+1]=3,val[i][i+1]=true;
		else dp[i][i+1]=2;
	for(int len=3;len<=n;len++){
		for(int L=1;L+len-1<=n;L++){
			int R=L+len-1;
			if(str[L]==str[R]&&val[L+1][R-1])
				val[L][R]=true;
		}
	}
	for(int len=3;len<=n;len++){
		for(int L=1;L+len-1<=n;L++){
			int R=L+len-1;
			dp[L][R]=dp[L+1][R]+dp[L][R-1]-dp[L+1][R-1]+val[L][R];
		}
	}
	while(m--){
		lson=Read();rson=Read();
		printf("%d\n",dp[lson][rson]);
	}
	return 0;
}
```

---

## 作者：AC自动机 (赞：0)

### 解题思路

首先一眼就可以看出这是一道区间dp。接着就要思考，如何进行dp和状态转移，首先，用dp[i][j]表示区间i，j之间的回文串的个数，接着我们考虑如何转移，显然，一个区间中的所有回文串可以分为两类：含有j的回文串和不含j的回文串，因此可以利用到之前已经求出来的状态，即dp[i][j]等于dp[i][j-1]加上以j为结尾的，开头在i之后的所有回文串的个数。

而以j为结尾的，开头在i之后的所有回文串的个数，可以在n^2的复杂度内与处理出来，叫做zhi[i][j]表示以j结尾，开头范围在i之后的回文串的个数，由此可以得到dp方程：

#### dp[j][i+j]=dp[j][i+j-1]+zhi[j][i+j];

ps：这里的i指的是区间的长度+1；



#### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<cstring>
using namespace std;
int dp[5005][5005];
bool hui[5005][5005];
int zhi[5005][5005];
string s;
int q;
int main(){
	cin>>s;
	int n=s.size();
	//-------------------------------
	//预处理部分
	for(register int i=0;i<=n;i++){
		hui[i][i]=1;
	}
	for(register int i=0;i<=n-1;i++){
		if(s[i]==s[i+1])hui[i][i+1]=1;
	}
	for(register int l=2;l<=n;l++){
		for(register int ss=0;ss+l<n;ss++){
			if(hui[ss+1][ss+l-1]==1&&s[ss]==s[ss+l])hui[ss][ss+l]=1;  // 先确定i到j是否为回文串，用bool数组记录
		}
	}
	for(register int i=0;i<=n;i++){
		for(register int j=i;j>=0;j--){
			if(hui[j][i]==1)zhi[j][i]=zhi[j+1][i]+1;    //然后进行统计，统计出以j结尾，开头在i之后的回文串个数
			else zhi[j][i]=zhi[j+1][i];
		}
	}
	//---------------------------------
	for(register int i=0;i<n;i++){
		dp[i][i]=1;
	}
	for(register int i=1;i<n;i++){
		for(register int j=0;j<n-i;j++){
			dp[j][i+j]=dp[j][i+j-1]+zhi[j][i+j];   //状态转移
		}
	}
	cin>>q;
	while(q){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",dp[x-1][y-1]);
		q--;
	}
}
```

---

