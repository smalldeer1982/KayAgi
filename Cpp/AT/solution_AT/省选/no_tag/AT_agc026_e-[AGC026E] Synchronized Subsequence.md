# [AGC026E] Synchronized Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc026/tasks/agc026_e

$ N $ 個の `a` と $ N $ 個の `b` からなる，長さ $ 2N $ の文字列 $ S $ が与えられます。

あなたは $ S $ からいくつかの文字を選びます。ただし各 $ i\ =\ 1,2,...,N $ について，$ S $ で $ i $ 番目に出現する `a` と $ i $ 番目に出現する `b` から片方だけ選ぶことは出来ません。 そして選んだ文字たちを( $ S $ での順番通りに)結合します。

こうして得られる文字列のうち，辞書順で最大のものを求めて下さい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ S $ は $ N $ 個の `a` と `b` からなる，長さ $ 2N $ の文字列である。

### Sample Explanation 1

$ S $ の $ 1,\ 3,\ 4,\ 6 $ 番目の文字からなる部分列 $ T $ は，条件を満たします。

### Sample Explanation 2

全ての文字を選ぶことも可能です。

## 样例 #1

### 输入

```
3
aababb```

### 输出

```
abab```

## 样例 #2

### 输入

```
3
bbabaa```

### 输出

```
bbabaa```

## 样例 #3

### 输入

```
6
bbbaabbabaaa```

### 输出

```
bbbabaaa```

## 样例 #4

### 输入

```
9
abbbaababaababbaba```

### 输出

```
bbaababababa```

# 题解

## 作者：小粉兔 (赞：32)

令 $a_i$ 表示第 $i$ 个 $\mathtt{a}$ 的位置，$b_i$ 表示第 $i$ 个 $\mathtt{b}$ 的位置。

考虑如何比较两个字符串的字典序，可以发现当某个前缀相同时应该比较后缀，所以考虑从后往前 DP：

令 $dp(i)$ 表示只考虑所有的 $a_{i \sim N}$ 和 $b_{i \sim N}$，也就是第 $i$ 对以及之后的 $\mathtt{a}, \mathtt{b}$ 的情况下的字典序最大的串。

注意**不是**第 $i$ 对 $\mathtt{a}, \mathtt{b}$ 以及它们之后的所有字符都一定选择，而是一对一对的选择的。

那么答案就为 $dp(1)$。而 $dp(i)$ 可以从两个方向转移，也就是 $a_i$ 和 $b_i$ 保留或者删掉。

如果删掉，就直接从 $dp(i + 1)$ 转移而来。

否则考虑如果保留第 $i$ 对 $\mathtt{a}, \mathtt{b}$ 的话会怎么样，根据先后顺序分成两类讨论：

1. $a_i < b_i$：也就是形如 $\cdots \mathtt{{\color{red}a}{\color{blue}a}{\color{green}b}{\color{blue}a}{\color{blue}a}{\color{green}b}{\color{red}b}} \cdots$ 的情况。  
   红色的字符就是第 $i$ 对 $\mathtt{a}, \mathtt{b}$，绿色的字符表示第 $i$ 对之前的字符，蓝色的字符表示第 $i$ 对之后的字符。  
   注意绿色的字符只可能是 $\mathtt{b}$，而蓝色的字符只可能是 $\mathtt{a}$。因为绿色的字符不会被保留，之后忽略它们。  
   既然已经确定了必须选取 $a_i, b_i$，因为要让字典序尽量大，所以 $a_i$ 到 $b_i$ 之间所有的 $\mathtt{a}$ 都应该被删掉。  
   也就是说，$dp(i)$ 就应该等于 $\mathtt{ab} + dp(k)$，其中 $k$ 为完全在 $b_i$ 之后的第一对 $a_k, b_k$ 的编号。
2. $a_i > b_i$：也就是形如 $\cdots \mathtt{{\color{red}b}{\color{blue}b}{\color{green}a}{\color{blue}b}{\color{blue}b}{\color{green}a}{\color{red}a}} \cdots$ 的情况。  
   红色的字符就是第 $i$ 对 $\mathtt{a}, \mathtt{b}$，绿色的字符表示第 $i$ 对之前的字符，蓝色的字符表示第 $i$ 对之后的字符。  
   注意绿色的字符只可能是 $\mathtt{a}$，而蓝色的字符只可能是 $\mathtt{b}$。因为绿色的字符不会被保留，之后忽略它们。  
   既然已经确定了必须选取 $a_i, b_i$，因为要让字典序尽量大，所以 $a_i$ 到 $b_i$ 之间所有的 $\mathtt{b}$ 都应该被保留。  
   而确定要保留这些 $\mathtt{b}$，又会导致往后包含了更多的 $\mathtt{b}$，同理被包含的 $\mathtt{b}$ 也应该被保留，连锁反应会一直进行下去，直到某一次不包含了更多的 $\mathtt{b}$ 为止。举个例子：  
   考虑 $\mathtt{{\color{blue}b}b{\color{blue}a}babbbabaaaabbabaaaabb}$，  
   选取 $\mathtt{{\color{red}b}{\color{blue}b}{\color{red}a}b{\color{blue}a}bbbabaaaabbabaaaabb}$，  
   选取 $\mathtt{{\color{red}{bba}}{\color{blue}b}{\color{red}a}bbb{\color{blue}a}baaaabbabaaaabb}$，  
   选取 $\mathtt{{\color{red}{bbaba}}{\color{blue}{bbb}}{\color{red}a}b{\color{blue}{aaa}}abbabaaaabb}$，  
   选取 $\mathtt{{\color{red}{bbababbba}}{\color{blue}b}{\color{red}{aaa}}{\color{blue}a}bbabaaaabb}$，  
   选取 $\mathtt{{\color{red}{bbababbbabaaaa}}bbabaaaabb}$。  
   在这种情况下，$dp(i) = \mathtt{bbababbbabaaaa} + dp(k)$，其中 $k$ 为后面部分的第一对 $a_k, b_k$ 的编号。

所以只要求出以上两类的结果就行，第 1 类可以预处理，第 2 类的开头的字符串，可以直接扫一遍判断。

时间复杂度为 $\mathcal O (N^2)$，[评测链接](https://atcoder.jp/contests/agc026/submissions/10364906)。

---

## 作者：w4p3r (赞：22)

略加分析可以发现，若我们把 $b_i$ 设为 $+1$ ， $a_i$ 设为 $-1$ ，则对于一段前缀和为 $0$ 的前缀，这段前缀的决策和后缀是独立的。

换句话说，我们可以从前往后把序列分为尽量多的若干段，每段末的前缀和都是$0$，然后段与段的决策是独立的。

那么我们对这样的每一段进行考虑。

可以发现，在同一段中，对于所有 $i$ ，第 $i$ 个 $a$ 和第 $i$ 个 $b$ 的相对位置关系存在，要么都是 $a$ 在 $b$ 前（设这种情况为 $ab$ 情况），要么都是 $b$ 在 $a$ 前（设这种情况为 $ba$ 情况），然后对两种情况分别讨论。

为了方便，下面用 $A_i$ 表示第 $i$ 个 $a$ 的位置，$B_i$表示第 $i$ 个 $b$ 的位置，下列说的删除某个 $a/b$ 同时也表示把它对应的 $b/a$ 删除了。

$1.$ $ab$ 情况：

首先，最终序列首字母一定是 $a$ ，这是无法改变的。

然后，若第一个 $a$ 后面还是 $a$ ，那我们肯定会选择将这些 $a$ 删除，直到第 $1$ 个 $b$ 出现（因为 $ab...$ 的字典序一定比 $aa...$ 大）。

然后将这个问题递归下去即可。

可以发现，我们最后的串一定是一个 $abababab...ab$ 的循环，且尽量长（因为所有这样的串前缀一定相同，越长字典序越大）。

假设选出的序列为 $p$ ，我们需要满足 $B_{p_i}<A_{p_{i+1}}$ ，且序列尽量长，这个问题直接扫一遍即可。

$2.$ $ba$ 情况：

最终序列的开始一定是一段 $b$ ，而我们肯定想这段 $b$ 尽量长。

还是假设 $a$ 是一个 $-1$ ， $b$ 是一个 $+1$ ，那么我们把序列的最大前缀和找到，假设这个值为 $maxn$ ，那么最终序列开头一定是 $maxn$ 个 $b$ 。

但是问题在于可能有多个位置的前缀和都为 $maxn$ ，而我们应该选哪一个呢？

首先假设我们最后选的是 $x$ ，可以发现我们把 $x$ 前面的 $a$ 删除后不会再进行删除操作了，证明：

若进行完删除的序列为一个 $bbb...bbbaaa...aaa$ （ $maxn$ 个 $b,a$ ），结论显然。

否则在后面 $maxn$ 个 $a$ 中一定有一些 $b$ ，这些 $b$ 一定不会删除（因为删除后字典序会变小），那么其对应的 $a$ 也不会被删除，这样递归推导下去显然所有字母都不会被删除。

（其实大概意思就是因为开头的 $b$ 不会删除，其对应的 $a$ 也不会删除。这些 $a$ 中间的 $b$ 也不会删除，其对应的 $a$ 也不会删除。这样套娃下去就能推出所有字母都不应该被删除）

有了这个结论之后结论就清晰朗然了，假设 $x_1$ ， $x_2$ 其前缀和为$maxn$，那显然我们应该选择 $[x_1+1,n]$ ， $[x_2+1,n]$ （ $n$ 为序列长度）这两段后缀中字典序更大的一个（因为后面的字符都不能删除），有多个位置一一比较取max即可。

现在我们可以把每段序列的最终序列求出了，但我们发现，似乎并不是所有序列我们都需要。

如样例$4$可以分为$5$段： $ab,bbaa,baba,abab,baba$ ，每段的最终序列就是原序列，但我们的答案 $bbaababababa$ 只保留了 $2,3,5$ 段。

我们可以维护一个类似于单调栈的东西，每次从前往后加入一个字符串 $s$ ，若 $s>st[top]+s$ （注意这个 $+s$ ），则应该弹出栈顶。

然后问题就顺利的结束了，如果不理解，可以结合代码看一下，代码有详细的注释。

因为要比较后缀大小，所以时间复杂度 $O(n^2)$ ，当然如果你闲得没事可以用后缀排序做到 $O(n \log n)$ 或者 $O(n)$ 。



```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register int
#define fr first
#define sd second
#define pa pair<int,int>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define N 6010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline int lowbit(int x){return x&(-x);}
char s[N];
string st[N];int top;
int n;
pa p[N];int tot;
inline string str(int l,int r){string S="";FOR(i,l,r)S+=s[i];return S;}//求出一个区间的串 
string Solve(int l,int r)
{
	string ans="";
	if(s[l]=='a')//ab情况 
	{
		tot=(r-l+1)/2;int sa=0,sb=0;
		FOR(i,l,r)
		{
			if(s[i]=='a')p[++sa].fr=i;
			if(s[i]=='b')p[++sb].sd=i;
		}
		int t=0,nowr=0;
		FOR(i,1,tot)if(p[i].fr>nowr)t++,nowr=p[i].sd;//按顺序扫，找出尽量多的ab 
		while(t--)ans+="ab";return ans;
	}
	else//ba情况 
	{
		int sum=0,maxn=0;
		FOR(i,l,r)
		{
			if(s[i]=='a')sum--;
			if(s[i]=='b')sum++;
			maxn=max(maxn,sum);//找出最多的前缀b 
		}
		int pos=0;sum=0;
		FOR(i,l,r)
		{
			if(s[i]=='a')sum--;
			if(s[i]=='b')sum++;
			if(sum==maxn)if(!pos||(str(i,r)>str(pos,r)))pos=i;//对于所有的x求一个后缀最大的，因为这样的x满足s[x]='b' ，所以比较[x,r]还是[x+1,r]没有区别 
		}
		while(maxn--)ans+='b';//maxn个b
		FOR(i,pos+1,r)ans+=s[i];//后面的字母不会删除 
		return ans;
	}
}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();scanf("%s",s+1);int nows=0,lst=1;
	FOR(i,1,(n<<1))
	{
		nows+=(s[i]=='b'?1:-1);
		if(nows==0)
		{
			string h=Solve(lst,i);lst=i+1;
			while(top&&h>st[top]+h)top--;st[++top]=h;//维护一个单调栈 
		}
	}
	FOR(i,1,top)cout<<st[i];cout<<'\n';
	return 0;
}
//gl

```

**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**


---

## 作者：5k_sync_closer (赞：4)

设 $f_i$ 表示只用第 $[i,n]$ 对 $\texttt{a,b}$ 能组成的字典序最大串，考虑选不选第 $i$ 对 $\texttt{a,b}$。

若不选第 $i$ 对 $\texttt{a,b}$，能组成的字典序最大串为 $f_{i+1}$。

若选了第 $i$ 对 $\texttt{a,b}$，分讨这对 $\texttt{a,b}$ 的位置 $a_i,b_i$：

- 若 $a_i<b_i$，$(a_i,b_i)$ 间的 $\texttt{b}$ 都不属于第 $[i,n]$ 对 $\texttt{a,b}$，不能用，

为了保证字典序最大，$(a_i,b_i)$ 间的 $\texttt{a}$ 也都不能用，

则能组成的字典序最大串为 $\texttt{ab}+f_k$，其中 $k$ 为第一个完全在 $b_i$ 右侧的对的编号。

- 若 $a_i>b_i$，$(b_i,a_i)$ 间的 $\texttt{a}$ 都不属于第 $[i,n]$ 对 $\texttt{a,b}$，不能用，

为了保证字典序最大，$(b_i,a_i)$ 间的 $\texttt{b}$ 都要用，

而选择这些 $\texttt{b}$ 所在的 $(b_j,a_j)$ 后，$(b_j,a_j)$ 间的 $\texttt{b}$ 也都要用，

所以一直往后扫到不需要用新的 $\texttt{b}$ 为止，则能组成的字典序最大串为 $T+f_k$，

其中 $T$ 为扫描过程中选择的所有字符，$f_k$ 为第一个完全在停止位置右侧的对的编号。

```cpp
#include <string>
#include <vector>
#include <iostream>
using namespace std;
string s, f[100050];
int n, u, v, b[100050], x[100050], y[100050];
int main()
{
    cin >> n >> s;
    s = ' ' + s;
    for (int i = 1; i < s.length(); ++i)
        if (s[i] == 'a')
            ++u, b[x[u] = i] = u;
        else
            ++v, b[y[v] = i] = v;
    for (int i = n, j; i; --i)
    {
        if (x[i] < y[i])
        {
            for (j = i + 1; j <= n; ++j)
                if (min(x[j], y[j]) > y[i])
                    break;
            f[i] = "ab" + f[j];
        }
        else
        {
            for (j = y[i]; y[b[j]] < x[b[j]] && (b[j] <= i || y[b[j]] < x[b[j] - 1]); ++j)
                if (b[j] >= i)
                    f[i] += s[j];
            f[i] += f[b[j]];
        }
        f[i] = max(f[i], f[i + 1]);
    }
    cout << f[1];
    return 0;
}
```


---

## 作者：zhylj (赞：3)

先讨论只有 ``ab`` 的情况（即所有 ``a`` 都在其对应的 ``b`` 前面），注意到若序列中出现超过连续两个 ``a``，我们总能把这两个 ``a`` 后面的部分删成 ``ab``，使得字典序更大，故最后的序列必然形如 ``ababab...ab``（若干个 ``ab``），我们需要最长的这样的串，贪心取第一个即可。

再讨论只有 ``ba`` 的情况，我们令 ``b`` 为 $1$，``a`` 为 $-1$，可以发现，如果把序列划分成若干段和为 $0$ 的区间，因为每段区间的影响是独立的，我们考虑先求出每段区间的答案再合并。

下面假定我们划分的区间是极小的，也就是它除了开头和结尾的前缀和均 $\gt 0$。考虑这段区间的开头会是一段连续的 ``a`` 和一段连续的 ``b``（形如 ``bbb...aaabb...aa...``），并且 ``a`` 的个数不会多于 ``b`` 的个数。我们注意到，如果删除第一段中的 ``a``，那么必然需要将所有 ``a`` 都删除。如果不删除，那么意味着前面的 ``b`` 一个都不能删除，否则不删除的 ``a`` 会往前，使得字典序更小，但如果这端 ``a`` 之后还有新的一段 ``b`` 和 ``a``，那新的一段中的 ``a`` 实际上是会和这一段的 ``b`` 匹配的（由于前缀和 $\gt 0$），但由于 ``b`` 不能删，那么新一段的 ``a`` 也不能删。以此类推，我们发现，如果某一段 ``a`` 不删了，那么这一段往后的所有 ``a`` 都不能删。我们发现我们删的 ``a`` 只可能是一个前缀，可能的情况只有 $\mathcal O(n)$ 种，可以暴力枚举。

对于区间的合并，我们考虑如果一段最大的字典序都比后面小，那还不如整段全部删掉。于是最终的字典序一定是递减的，就可以用一个单调栈维护了。

然后对于 ``ab``，``ba`` 都有的情况，注意到 ``ab`` 如果后面有一个 ``ba``，我们起码可以把这个后缀变成 ``ba``，于是 ``ba`` 前面的 ``ab`` 全部丢掉，然后后缀的 ``ab`` 按只有的情况处理就好了。

---

## 作者：xht (赞：1)

## [Synchronized Subsequence](https://atcoder.jp/contests/agc026/tasks/agc026_e)

### 题意

- 给定一个包含 $n$ 个 `a` 和 $n$ 个 `b` 的字符串。
- 你要从中选出一个子序列，要求对于每个 $i \in [1,n]$，该子序列要么同时包含第 $i$ 个 `a` 和第 $i$ 个 `b`，要么同时不含第 $i$ 个 `a` 和第 $i$ 个 `b`。
- 你还要最大化这个子序列的字典序。
- $n \le 3 \times 10^3$。

### 题解

令 $a_i$ 表示第 $i$ 个 `a` 的位置，$b_i$ 表示第 $i$ 个 `b` 的位置。

考虑从后往前 DP，设 $f_i$ 表示只考虑所有的 $a_{i \dots n}$ 和 $b_{i \dots n}$ 的情况下的字典序最大的串，那么答案就为 $f_1$。

考虑转移，$f_i$ 会从 $a_i$ 和 $b_i$ 都保留或者都删掉两个方向转移来。

如果都删掉，就直接从 $f_{i+1}$ 转移来；如果都保留，分类讨论：

- $a_i < b_i$：
  由于要让字典序尽量大，所以 $a_i$ 到 $b_i$ 之间所有的 `a` 都应该被删掉，而所有的 `b` 因为都在第 $i$ 个 `b` 之前所以不用考虑。
  即 $f_i = \mathtt{ab} + f_k$，其中 $k$ 为完全在 $b_i$ 之后的第一对 $a_k, b_k$ 的 $k$，可以预处理出来。

- $a_i > b_i$：
  由于要让字典序尽量大，所以 $a_i$ 到 $b_i$ 之间所有的 `b` 都应该被保留，而所有的 `a` 都不用考虑。
  而要保留这些 `b`，又会导致往后包含了更多的 `b`，同理被包含的 `b` 也应该被保留，连锁反应会一直进行下去，直到某一次不包含了更多的 `b` 为止。
  即 $f_i = s + f_k$，其中 $s$ 为上述连锁反应所涉及到的所有字符，而 $k$ 为这之后的第一对 $a_k,b_k$ 的 $k$，可以暴力找。

时间复杂度 $\mathcal O (n^2)$。

### 代码

```cpp
const int N = 6e3 + 7;
int n, a[N], b[N], d[N], p[N];
char s[N];
string f[N];

int main() {
	rd(n), rds(s, n);
	for (int i = 1, j = 0, k = 0; i <= n; i++)
		if (s[i] == 'a') a[d[i]=++j] = i;
		else b[d[i]=++k] = i;
	a[n+1] = b[n+1] = n + 1, d[n+1] = (n >> 1) + 1, n >>= 1;
	for (int i = 1, j = 0; i <= n + 1; i++)
		while (j < min(a[i], b[i])) p[++j] = i;
	for (int i = n; i; i--) {
		if (a[i] > b[i]) {
			int j = b[i];
			while (b[d[j]] < a[d[j]] && (d[j] <= i || b[d[j]] < a[d[j]-1])) {
				if (d[j] >= i) f[i] += s[j];
				++j;
			}
			f[i] += f[d[j]];
		} else f[i] = "ab" + f[p[b[i]+1]];
		f[i] = max(f[i], f[i + 1]);
	}
	prints(f[1]);
	return 0;
}
```

---

## 作者：Hanzelic (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_agc026_e)
这道题求的是字典序最小，也就是让剩下来的字符串前面的 $b$ 尽可能多，我们选择 dp。   

为了降低删除操作对前面的影响，我们可以考虑从后面往前进行转移，令 $dp_i$ 表示对第 $i$ 对到第 $n$ 对字符串进行操作后所能得到的字典序最大的字符串，我们要考虑一些情况：
 - 首先是不选择，直接 $dp_i=dp_{i+1}$，最后比较大小一下即可。
 - 如果 $a_i<b_i$，那么 $a_i$ 到 $b_i$ 之间的 $a$ 我们是肯定不会选的，无法保证字典序最小，但同时 $b$ 我们也是无法选择的，因为中间的 $b$ 都是属于第 $1$ 对到第 $i-1$ 对的。  
 所以我们在这一对里只有选择 $ab$ 是最优的，也就是 $dp_i=ab+dp_k$，其中 $dp_k$ 是左端点大于第 $i$ 组的右端点的 dp 中距离第 $i$ 组最近的一组。
 - 如果 $a_i>b_i$，我们可以选择的就多了起来，为了符合贪心的需求，这其中所有的 $b$ 我们都是要选择的。  
 考虑 $a$ 的选择，我们可以简单得出一个性质：  
 **对于所有的可以选择的 $a_i$，一定满足 $b_i<a_i$**。    
 因为如果 $a_i<b_i$，你选择肯定是会让字典序变小的。既然知道这个了，我们就对所有满足 $a_i>b_i$ 的 $a_i$ 进行操作。  
 若 $i$ 小于当前你所转移到的对数，那么这个 $a$ 是一定要选的，此时与 $a$ 配对的 $b$ 一定是在前面的，那么为了我们转移到前面时选择 $b$ 不会出现差错，我们要选择这个 $a$ 实现最优。  
 同理，当你循环到一个 $a$，与之配对的 $b$ 在 $b_i$ 之间时，这个 $a$ 我们也是要选择的，原因与上面相同。
 
时间复杂度为 $O(n^2)$，可以通过。
### 代码
```cpp
#include<bits/stdc++.h>
#define M 6060
using namespace std;
string s,dp[M];
int n;
int now[M],a[M],b[M];
int main(){
	scanf("%d",&n);
	cin>>s;
	s=' '+s;
	for(int q=1;q<=2*n;q++){
		if(s[q]=='a')now[q]=++a[0],a[a[0]]=q;
		else now[q]=++b[0],b[b[0]]=q;
	}
	for(int q=n;q;q--){
		if(a[q]<b[q]){
			int i;
			for(i=q+1;i<=n;i++){
				if(min(a[i],b[i])>b[q])break;
			}
			dp[q]="ab"+dp[i];
		}
		else{
			int i;
			for(i=b[q];b[now[i]]<a[now[i]]&&(now[i]<=q||b[now[i]]<a[now[i]-1]);i++){
				if(now[i]>=q){
					dp[q]+=s[i];
				}
			}
			dp[q]+=dp[now[i]];
		}
		dp[q]=max(dp[q],dp[q+1]);
	}
	cout<<dp[1]<<endl;
	return 0;
}
```


---

## 作者：zifanwang (赞：0)

考虑 dp，记 $f_i$ 表示第 $i\sim n$ 个 `a` 和 `b` 得到的字典序最大的字符串。记 $a_i,b_i$ 表示第 $i$ 个 `a` 或 `b` 的位置。不取直接从 $f_{i+1}$ 转移即可，接下来考虑取的情况：

- 若 $a_i<b_i$，则 $(a_i,b_i)$ 中只存在 $<i$ 的 `b` 和 $>i$ 的 `a`，显然后者删除更优。考虑找到最小的 $j$ 满足 $a_j>b_i$，在前面添上 `ab` 转移。
- 若 $a_i>b_i$，则 $(b_i,a_i)$ 中只存在 $<i$ 的 `a` 和 $>i$ 的 `b`，显然后者保留更优。考虑不断往后扫把当前区间能覆盖到的 `ba` 对全都取了，直到 $(b_j,a_j)$ 中不存在 `b`，再拼上 $f_{j+1}$ 转移。

时间复杂度 $\mathcal O(n^2)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define mxn 3003
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int n,t1,t2,d[mxn<<1],a[mxn],b[mxn];
char s[mxn<<1];
string f[mxn];
signed main(){
	scanf("%d%s",&n,s+1);
	rep(i,1,n<<1){
		if(s[i]=='a')a[d[i]=++t1]=i;
		else b[d[i]=++t2]=i;
	}
	drep(i,n,1){
		if(a[i]<b[i]){
			int j=i+1;
			for(;j<=n&&a[j]<b[i];++j);
			f[i]=max(f[i+1],"ab"+f[j]);
		}else{
			int j=b[i];
			for(;j<=n<<1&&a[d[j]]>b[d[j]]&&(d[j]<=i||b[d[j]]<a[d[j]-1]);++j){
				if(d[j]>=i)f[i]+=s[j];
			}
			f[i]=max(f[i]+f[d[j]],f[i+1]);
		}
	}
	cout<<f[1];
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc026_e)

**题目大意**

> 给定 $n$ 个 `a,b` 构成的字符串，每次可以把从左往右的第 $i$ 个 `a` 和 `b` 同时删除，求能得到的字典序最大的串。
>
> 数据范围：$n\le 3000$。

**思路分析**

考虑从后往前 dp，设 $f_i$ 表仅考虑第 $i\sim n$ 个 `a` 和 `b` 得到的最大字典序串。

设 $a_i,b_i$ 表示第 $i$ 个 `a` 或 `b` 的位置。

很显然可以直接删除 $a_i,b_i$ 得到 $f_{i+1}$。

否则如果保留了 $a_i,b_i$，如果 $a_i<b_i$，那么 $(a_i,b_i)$ 范围内的字符都是 $<i$ 的 `b` 和 $>i$ 的 `a`。

那么我们肯定不会保留这部分的 `a`，直接找到第一个 $\min(a_j,b_j)>b_i$ 的位置并得到 $\texttt{ba}+f_j$。

否则 $(b_i,a_i)$ 范围内的是 $>i$ 的 `b` 和 $<i$ 的 `a`，很显然这些 `b` 一定是选择了更优，然后我们又会选若干 $b_j<a_j$ 的字符对，把这部分的 `b` 继续选上，不断递归直到 $(b_j,a_j)$ 中没有 `a`，从 $f_{j+1}$ 转移。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=6005;
int n,id[MAXN],a[MAXN],b[MAXN];
char s[MAXN];
string f[MAXN];
signed main() {
	scanf("%d%s",&n,s+1);
	for(int i=1,x=0,y=0;i<=n*2;++i) {
		if(s[i]=='a') a[id[i]=++x]=i;
		else b[id[i]=++y]=i;
	}
	for(int i=n;i>=1;--i) {
		if(a[i]<b[i]) {
			int j=i+1;
			for(;j<=n&&min(a[j],b[j])<=b[i];++j);
			f[i]=max("ab"+f[j],f[i+1]);
		} else {
			int j=b[i];
			for(;j<=n*2&&b[id[j]]<a[id[j]]&&(id[j]<=i||b[id[j]]<a[id[j]-1]);++j) {
				if(id[j]>=i) f[i]+=s[j];
			}
			f[i]=max(f[i]+f[id[j]],f[i+1]);
		}
	}
	printf("%s\n",f[1].c_str());
	return 0;
}
```

---

