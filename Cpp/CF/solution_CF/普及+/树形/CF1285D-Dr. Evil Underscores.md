# Dr. Evil Underscores

## 题目描述

Today, as a friendship gift, Bakry gave Badawy $ n $ integers $ a_1, a_2, \dots, a_n $ and challenged him to choose an integer $ X $ such that the value $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ is minimum possible, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

As always, Badawy is too lazy, so you decided to help him and find the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 说明/提示

In the first sample, we can choose $ X = 3 $ .

In the second sample, we can choose $ X = 5 $ .

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 5```

### 输出

```
4```

# 题解

## 作者：基地A_I (赞：13)

[博客园食用地址](https://www.cnblogs.com/BaseAI/p/12181934.html)

## Problem

[Codeforces 题目地址](http://codeforces.com/contest/1285/problem/D)

[洛谷 题目地址](https://www.luogu.com.cn/problem/CF1285D)

## Solution

这个题目的一种解法 ———— Tire上树形dp。 （第一次听说这种做法） 相信听到这个做法后，你大概就知道怎么做了。

首先先把所有数字建成一棵 Tire，根节点的儿子表示第 30 位，然后依次类推（从高位往低位建）。

假设**点 $u$ 的儿子**表示的是第 $k$ 位，那么点 $u$ 的儿子的意义就是：左儿子这边的数第 $k$ 位上是 $1$，反之，右儿子这边的数第 $k$ 位上是 $0$。

如果点 $u$ 只有一个儿子，那么我们需要构造的数 $x$ 的第 $k$ 位就选这个儿子代表的数 ($0/1$)，因为这样异或后就可以抵消。

如果点 $u$ 有两个儿子，那么我们需要构造的数 $x$ 的第 $k$ 位选什么都会有 $(1<<k)$ 的影响，这时我们要使总答案最小就要取 $\min\{ls(),rs()\}$

实际做的时候并不要把树建出来。

## Code

Talk is cheap.Show me the code.

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
int n;
vector<int> a;
int Solve(vector<int> p,int K) {
	if(p.size()==0 || K<0) return 0;
	vector<int> p1,p2;
	for(int i=0;i<p.size();++i) {
		if(p[i] & (1<<K)) p1.push_back(p[i]);
		else p2.push_back(p[i]);
	}
	if(p1.size() == 0) return Solve(p2,K-1);
	else if(p2.size() == 0) return Solve(p1,K-1);
	else return (1<<K) + min(Solve(p1,K-1),Solve(p2,K-1));
}
int main()
{
	n = read();
	for(int i=1,x;i<=n;++i) {
		x = read();
		a.push_back(x);
	}
	printf("%d\n",Solve(a,30));
	return 0;
}
```

## Summary

Trie上树形dp，经典题。

## Thanks

参考了 [qscqesze大佬的 b站视频讲解](https://www.bilibili.com/video/av83037564?p=4)

---

## 作者：Composite_Function (赞：8)

**"如果不能让烦恼更少，还不如先处理好眼前的事。"——按位贪心**

------------

看那一个个 $a_i \oplus x$ 如同一个个丝缕纠缠的线球，比起慢慢解开，不如挥刀斩乱麻。

让我们用 $B_t(x)$ 表示 $x$ 在二进制表示下的第 $t$ 位的值。挥刀砍去，将那 $\min(\max_{i=1}^n(a_i \oplus x))$ 拆作 $\min(\sum_{i=0}^{+\infty}\max_{i=1}^n(B_i(a_i \oplus x)))=\min(\sum_{i=0}^{+\infty}\max_{i=1}^n(B_i(a_i) \oplus B_i(x)))$。

看那更多的大大小小的线团犯了愁，悄然间，发现这一个个线的大小颇有规律，大大小小成倍增加。

这样，岂不是那小线团永远不能超过大线团。既然这样，不如先解决大线团。

又发现可调整的只有自己 $B_i(x)$，就意味着 $B_i(a_i)$ 只要有两种，这就没有解决的方法。相反地，只要 $B_i(a_i)$ 只有一种，这线团便露出了一段线头。

该用什么找这有几种呢？心中早已浮现出一个选择——**字典树**。

------------

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1.5e5 + 10, M = 4.5e6 + 10, L = 30;
int n, a[N];
int trie[M][2], cnt[M], tot = 1;
void insert(int x)
{
	int p = 1;
	for (int i = L; i >= 0; --i) {
		int X = (x >> i) & 1;
		if (trie[p][X] == 0) trie[p][X] = ++tot, ++cnt[p];
		p = trie[p][X];
	}
	return;
}
int ask(int p, int x)
{
	if (x < 0 || cnt[p] == 0) return 0;
	if (cnt[p] == 2) return (1 << x) + min(ask(trie[p][0], x - 1), ask(trie[p][1], x - 1));
	else return ask((trie[p][0] == 0? trie[p][1] : trie[p][0]), x - 1);
}
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i], insert(a[i]);
	cout << ask(1, 30) << endl;
	return 0;
}
```

------------

咦，世上还真有如此相似的线团——AT_abc281_f。

---

## 作者：Pengzt (赞：5)

[CF1285D](https://www.luogu.com.cn/problem/CF1285D)

先将每一个 $a_i$ 二进制拆分。

因为每一位的 $\text{xor}$ 运算是互不影响的，于是可以考虑每一位。

从高位到低位考虑，因为 $a_i \le 2^{30}-1$，所以二进制状态下的 $a_i$ 的长度是 $\le 29$ 的。

假设在考虑 $bit$ 位，则有 $2$ 种情况：

1. 当前考虑的所有数的第 $bit$ 位都是 $0$ 或 $1$。

1. 当前考虑的所有数的第 $bit$ 位 $0$ 和 $1$ 都有。

第 $1$ 种情况显然可以使最后答案第 $bit$ 位变为 $0$。

第 $2$ 种情况：数组 $c$ 存储第 $bit$ 位为 $0$ 的数，数组 $d$ 存储第 $bit$ 位为 $1$ 的数。

此时最后答案的第 $bit$ 位肯定为 $1$。

但是如果 $x$ 的第 $bit$ 位为 $0$，便只需考虑 $d$ 数组了。同理，若 $x$ 的第 $bit$ 位为 $1$，便只需考虑 $c$ 数组了。

分别搜索 $x$ 的 $bit$ 位为 $1$ 和 $0$ 即可。

直接搜索的话，参数需要传递数组，跑得很慢。
可以先排序，传递的参数变为下标。

时间复杂度：$\mathcal{O}(2^{\log_2n}+n\log n)=\mathcal{O}(n\log n)$

双倍经验：ABC281F

[评测记录](https://www.luogu.com.cn/record/97514702)

---

## 作者：EternalHeart1314 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF1285D)

### [双倍经验](https://www.luogu.com.cn/problem/AT_abc281_f)

# 思路

看到位运算，我首先就想到了位之间相互独立。

因为 $a_i\le 2^{30}-1$，所以 $a_i$ 最多有 $30$ 位（二进制下），从高到低每一位考虑。

设当前位是 $bit$ 位，则：

+ 如果 $bit$ 位全为 $1$ 或 $0$，则可以使得当前位全部变成 $0$。

+ 如果 $bit$ 位有 $1$ 也有 $0$，那么可以选择异或 $1$ 和异或 $0$ 两种情况。

> + 异或 $1$：则 $bit$ 位 $0$ 变成 $1$，$1$ 变成 $0$，可以将**原来**为 $0$ 的放在一起，继续搜索。
>
> + 异或 $0$：则 $bit$ 位 $0$ 还是 $0$，$1$ 还是 $1$，可以将**原来**为 $1$ 的放在一起，继续搜索。
>
> 由于 $bit$ 位**肯定**有 $1$，所以要加上 $2^{bit}$。
>
> 最后取 $\min$。

# Code
```
#include<bits/stdc++.h>
#define VI vector<int>
using namespace std;

int n;

int dfs(VI a, int bit) {
	if(!bit) {
		return 0;
	}
	-- bit;
	VI b, c;
	for(auto i : a) {
		if(i >> bit & 1) {
			b.push_back(i);
		} else {
			c.push_back(i);
		}
	}	//1 和 0 分别考虑 
	if(b.empty()) {
		return dfs(c, bit);
	} else if(c.empty()) {
		return dfs(b, bit);
	}	//只有 1 或 只有 0 
	return min(dfs(b, bit), dfs(c, bit)) + (1 << bit);
		//有 1 也有 0 
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	VI a;
	for(int i(1), x; i <= n; ++ i) {
		cin >> x;
		a.push_back(x);
	}
	return cout << dfs(a, 30), 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：ix35 (赞：4)

## CF 1285 D：Dr. Evil Underscores

CF 上已测试通过。

题目要求的是 $\max(a_i\oplus x)$ 的最小值，这个可以按位贪心，从高位开始往低位考虑，如果当前位可以取 $0$ 就让它取 $0$，否则只能取 $1$。

先将 $a_i$ 从小到大排序，然后设 $gap_i$ 表示 $a_i$ 与 $a_{i-1}$ 最高的不相同的二进制位。

原问题采用分治法解决，设 $solve(l,r,b)$ 表示找 $\max\limits_{l\leq i\leq r}(a_i\oplus x)$ 的最小值，其中 $a_l,\cdots,a_r$ 的第 $b$ 位之前都相等（即只要考虑最末 $b$ 位），那么：

如果 $gap_{l+1},\cdots,gap_r$ 都小于 $b$，那么就意味着 $[l,r]$ 中所有的 $a_i$ 第 $b$ 位都相同（否则至少有一个 $gap_i\ge b$），此时我们可以使得答案的第 $b$ 位为 $0$（如果这些数的第 $b$ 位都是 $1$ 就异或个 $1$，否则异或个 $0$ 即可做到）。这时候，我们递归计算 $solve(l,r,b-1)$ 得到后续的答案。

如果存在一个 $gap_{i}=b$（这里不会有大于 $b$ 的，因为已经说过 $a_l,\cdots,a_r$ 的第 $b$ 位之前全相等），那么一定只存在一个（因为这一段是排好序的，第 $b$ 位是 $0$ 的一定在 $1$ 前面），设这个位置是 $pos$，那么答案中第 $b$ 位只能是 $1$（因为无论异或多少总有一个 $a_i\oplus x$ 这一位上是 $1$），然后递归下去就是 $\min(solve(l,pos-1,b-1),solve(pos,r,b-1))$，表示枚举我这一位到底是异或 $1$（此时最大值在 $[l,pos-1]$ 中产生） 还是异或 $0$（此时最大值在 $[pos,r]$ 中产生）。

边界是 $l=r$，此时答案显然是 $0$。

发现目前的瓶颈在于求一个 $gap_{pos}=b$，可以被卡到 $O(n^2)$，所以要优化一下，用 ST 表存 $gap_i$ 的区间最值，做到 $O(1)$ 查询，这样时间复杂度就变成 $O(n\log n)$ 了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,a[MAXN],f[MAXN],lg[MAXN],st[MAXN][22],b[MAXN][32];
int query (int l,int r) {
	int k=lg[r-l+1];
	return (f[st[l][k]]>f[st[r-(1<<k)+1][k]]?st[l][k]:st[r-(1<<k)+1][k]);
}
int solve (int l,int r,int b) {
	if (l==r||b==-1) {return 0;}
	int pos=query(l+1,r);
	return (f[pos]==b?(1<<b)+min(solve(l,pos-1,b-1),solve(pos,r,b-1)):solve(l,r,f[pos]));
}
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {scanf("%d",&a[i]);}
	sort(a+1,a+n+1);
	lg[0]=f[1]=-1;
	for (int i=1;i<=n;i++) {
		lg[i]=lg[i/2]+1;
		for (int j=0;j<=29;j++) {
			b[i][j]=((a[i]>>j)&1);
		}
		if (i>1) {
			st[i][0]=i,f[i]=-1;
			for (int j=29;j>=0;j--) {
				if (b[i][j]!=b[i-1][j]) {f[i]=j;break;}
			}
		}
	}
	for (int i=1;i<=20;i++) {
		for (int j=1;j+(1<<i)-1<=n;j++) {
			st[j][i]=(f[st[j][i-1]]>f[st[j+(1<<(i-1))][i-1]]?st[j][i-1]:st[j+(1<<(i-1))][i-1]);
		}
	}
	printf("%d\n",solve(1,n,29));
	return 0;
}
```


---

## 作者：been_apart (赞：2)

这题真心不难。而且题面简洁，便于理解。

$dfs$即可。其实与$trie$有微妙的相似。

思路：先排序，再转二进制（注意0！！），最后$dfs$，从高位到低位遍历。

$dfs$可以用二分优化为$O(klogn)$，加上排序，时间复杂度为$O(nlogn)$。

代码如下，自行理解，十分简单。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int n,a[100005];
int d[35][100005];
int dfs(int i,int l,int r){
	if(i==1){
		if(d[i][r]==0)return 0;
		if(d[i][l]==1)return 0;
		return 1;
	}
	if(d[i][r]==0){
		return dfs(i-1,l,r);
	}
	if(d[i][l]==1){
		return dfs(i-1,l,r);
	}
	int p=upper_bound(d[i]+l,d[i]+r+1,0)-d[i];
	return min(dfs(i-1,l,p-1),dfs(i-1,p,r))+(1<<(i-1));
}
signed main(){
    n=read();int x,y;
    for(re i=1;i<=n;i++)a[i]=read();
    sort(a+1,a+n+1);
    for(re i=1;i<=n;i++){
    	x=a[i];y=!a[i];
    	while(x){
    		d[++y][i]=x%2;x/=2;
    	}
    	d[0][i]=y;
    }
    cout<<dfs(d[0][n],1,n)<<endl;
	return 0;
}


---

## 作者：EXODUS (赞：1)

# Part 1：前言
从 abc281 来的，由于本人 dp 及其垃圾，所以拿分治做的。

# Part 2：正文
我们对原问题做这样一个转化，**令 $c_i$ 表示当在异或上某一个数 $x$ 后，第 $i$ 个数 $a_i\oplus x$ 取得最大值时，$a_i\oplus x$ 的最小值**，答案显然为 $\min\limits_{i=1}^n c_i$。

对其正确性的感性理解是，异或上某一个数后答案的最大值的位置一定是原数列中的一个位置（这好像是个废话），我们对于每个位都求出让该位取到最大值后的最小值，那么一定能够涵盖最优解，其实就是个贪心。

我们在二进制意义下考虑这个问题，对于两个二进制数 $x$，$y$，$x>y$ 的充要条件是 $\exists p\in[1,n],s.t. (\forall i\in[p-1,n],x[i]=y[i]) \land(x[p]>y[p])$，其中我们把一个二进制数的每一位从 $1$ 开始从低到高标号，$x[i]$ 表示二进制数 $x$ 的第 $i$ 位，设 $len_x$ 表示 $x$ 的长度，$n=\max(len_x,len_y)$。

我们试图实现一个函数 `solve(bit,val,S)`，表示只考虑 $S$ 集合中的数，当前考虑到第 $bit$ 位，异或值为 $val$ 时，**自由决定 $val$ 的第 $1$ 到第 $bit$ 位**，集合 $S$ 中的数异或 $val$ 最大值最小是多少。

我们把集合 $S$ 分为 $S_0$ 和 $S_1$，对于一个数 $x\in S$，$x\in S_{x[bit]}$ 的我们考虑钦定 $val$ 的第 $bit$ 位，分为三种情况讨论。

- $S_0=\emptyset$，该位钦定为 $1$ 即可，即答案为 `solve(bit-1,val^(1<<bit),S1)`。
- $S_1=\emptyset$，该位钦定为 $0$ 即可，即答案为 `solve(bit-1,val^,S0)`。
- $S_0\neq \emptyset,S_1\neq \emptyset$，分为两块递归，一份是 `solve(bit-1,val^(1<<bit),S0)`，另外一份是 `solve(bit-1,val,S1)`，分别意味着我们钦定当前最大值到底在 $S_0$ 中还是 $S_1$ 中，答案为上边两个答案取 $\max$。

递归边界是 $bit=-1$，此时 $S$ 集合中的数相同，答案为 $e\oplus val(e\in S)$。不难发现每个递归边界恰好对应了一个 $c$。

最后答案即为 `solve(30,0,A)`，其中 $A$ 表示数列 $a_1,a_2,\dots,a_n$ 构成的集合。
# Part 3：代码
```cpp
const int N=2e5+7;
int n;
vector<int>v;
int a[N];


bool mem2=0;

int solve(int bit,int val,vector<int>&S){
	if(S.empty())return 2e9;
	if(bit==-1){
		int ans=S.back();
		ans^=val;
		return ans;
	}
	vector<int>v0,v1;v0.clear(),v1.clear();
	for(auto i:S){if(i&(1<<bit))v1.pb(i);else v0.pb(i);}
	int ans=2e9;
	if(v1.size())ans=min(ans,solve(bit-1,val^(1<<bit),v0));
	else ans=min(ans,solve(bit-1,val,v0));
	if(v0.size())ans=min(ans,solve(bit-1,val,v1));
	else ans=min(ans,solve(bit-1,val^(1<<bit),v1));
	return ans;
}
void Main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();v.pb(a[i]);
	}
	cout<<solve(30,0,v);
	return;
}
```

---

## 作者：little_sun (赞：1)

### 题目大意

你有一个数组${a_n}$,求一个数$x$ ，满足$\max{a_i \oplus x}$最小，输出这个最小值

### 题目分析

首先看到xor操作我们可以想到01trie, 接下来我们来分析如何用01trie计算答案

容易发现这样一个结论:如果一个节点的两个孩子都存在，那么这一位的异或值只能是$1$

设当前节点为$\texttt{now}$, 当前节点处在第$\texttt{dep}$位， 我们可以考虑这样一个过程

1.递归计算当前节点的孩子$\texttt{ch[now][0], ch[now][1]}$的答案$\texttt{ans[0], ans[1]}$，并求得$ans= \min \{ans[0], ans[1] \}$

2.若当前节点的两个孩子都存在，返回$ans+2^{dep}$，否则返回$ans$

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)

const int MaxN = 5e6 + 10;
const int lim = (1 << 29);

int n, cnt = 1, a[MaxN], num[MaxN], ch[MaxN][2];

inline void insert(int x)
{
    int now = 1;
    for (int i = lim; i; i >>= 1)
    {
        if (ch[now][!!(x & i)])
            now = ch[now][!!(x & i)];
        else
            ++num[now], now = ch[now][!!(x & i)] = ++cnt;
    }
}

int query(int x, int k)
{
    if (!num[x])
        return 0;
    int ans = 1e9;
    if (ch[x][0])
        ans = std::min(ans, query(ch[x][0], k >> 1));
    if (ch[x][1])
        ans = std::min(ans, query(ch[x][1], k >> 1));
    return ((num[x] == 1) ? ans : (ans + k));
}

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read(), insert(a[i]);
    printf("%d\n", query(1, lim));
    return 0;
}
```


---

## 作者：Thaumaturge (赞：1)

把分治方法贴上来吧

还是按位取，但是不贪心。可以发现，如果一位只有1或0，那么我们一定可以在这一位取到0，因为位运算中，位之间是互不干扰的。

但如果1与0都有呢？

我们可以两边都试一下，容易发现，这样会导致序列分成两个部分，一个部分这一位全部为0，另一个部分全部为1。此时，无论这一位取1还是取0，都会导致某部分在该位的异或值上为0。因为是从高位到低位枚举，因此高位的值全部相等，所以异或值为0的部分不再会有影响，且这一位的值为1。

接下来就是启发式？？（不知道该叫什么好）的板子了。从两头同时往中间扫，如果全为0或1就直接进入下一位，否则分治。

如何保证在这一位为0的数，进入下一位之后，为0的与为1的在分裂区间的不同侧？考虑排序。排序后，所有数就能直接分好组。（基数排序的思想）

复杂度不太会算，大概是$O(nlogn)$？（太菜了，$O(n)$都不会）

代码如下，还挺长的：

```
/*************************************************************************
	> File Name: CF1285D.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2020年01月12日 星期日 10时13分52秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 100010

using namespace std;

int a[N],n;

int nowans,fans;

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

void merge(int l,int r,int dep,int nowans){
	if(!(~dep)){fans=min(fans,nowans);return;}
	int i=l,j=r;
	for(;i<=j;++i,--j)
	{
		if((a[i]>>dep&1) || (!(a[j]>>dep&1)))
		break;
	}
	if(i==l || j==r)
	merge(l,r,dep-1,nowans);
	else
	{
		if(a[i]>>dep&1) --i,j=i+1;
		else ++j,i=j-1;
		merge(l,i,dep-1,nowans+(1ll<<dep));
		merge(j,r,dep-1,nowans+(1ll<<dep));
	}
	return;
}

inline void Input(){
	fans=0x7f7f7f7f;
	n=read();
	for(re int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	return;
}

inline void solve(){
	merge(1,n,30,0);
	printf("%d\n",fans);
	return;
}

int main(){
	Input();
	solve();
	return 0;
}
```


---

## 作者：zhfaz123 (赞：0)

非常容易就能想到 01trie 的做法，首先建立一颗字符集只有 $0$ 和 $1$ 的 trie，然后把所有的数按位拆开插入进去。考虑树形 dp，记 $f_i$ 为树上节点 $i$ 子树上的最小异或值最大的数。

记两个儿子节点的编号分别为 $x$，$y$，当前位位权为 $w$，那么转移方程就是：

$$f_i=\begin{cases}
1 &i \text{ 无子结点}\\
f_x &i \text{ 只有 } 0 \text{ 节点}\\
f_y &i \text{ 只有 } 1 \text{ 节点}\\
\min\{f_x+f_y\}+w &i \text{ 两节点均有}
\end{cases}
$$

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
constexpr long long N=1e6,M=30;
ull n,m,k,son[8*N+5][2],
w[N+5],ans=0,dp[N+5],cnt=1;
void ins(ull v)
{
    ull tmp=1;
    for(long long i=M;i>=0;i--)
    {
        ull to=!!(v&(1ull<<i));//!!强转为bool
        if(!son[tmp][to])
        {
            son[tmp][to]=++cnt;
        }
        tmp=son[tmp][to];
    }
}
void dfs(ull rt,ull dep=1)
{
    ull x=(!!son[rt][1])+2*(!!son[rt][0]),y=1ull<<(M-dep+1);
    // cout<<bitset<2>(x)<<endl;
    if(!x) 
    {
        dp[rt]=0;
        return;
    }
    else dp[rt]=INT_MAX+1e5;
    if(x==3)
    {
        dfs(son[rt][1],dep+1);dfs(son[rt][0],dep+1);
        dp[rt]=min(dp[son[rt][0]]+y,dp[son[rt][1]]+y);
    }
    else if(x==2) dfs(son[rt][0],dep+1),dp[rt]=dp[son[rt][0]];
    else if(x==1) dfs(son[rt][1],dep+1),dp[rt]=dp[son[rt][1]];
    return ;
}
int main()
{
    // freopen("asdfjaisd.in","r",stdin);
    // freopen("asdfjaisd.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>w[i];
        ins(w[i]);
    }
    dfs(1);
    cout<<dp[1];
    return 0;
}
```

记得空间开大一点

---

## 作者：slzx2022YuYihan (赞：0)

[CF1285D	Dr. Evil Underscores](https://www.luogu.com.cn/problem/CF1285D)

# Solution
根据题意，首先想到字典树。然后这样去遍历字典树：

*	如果当前节点有两个儿子，说明无论这一位的 $x$ 取 $\mathbb 0$ 还是 $\mathbb 1$，答案必须加上去，并且左右两个儿子都对其进行这样的遍历，加上两个儿子遍历结果的最小值。
*	如果当前节点只有一个儿子，说明这一位的对答案的贡献可以为 $\mathbb 0$，对其儿子进行遍历。
*	如果当前节点没有儿子，说明已经到了边界，直接返回。

代码非常容易实现，就是又又又 UKE 两次。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>inline void read(T& x){
    x = 0; T w = 1; char ch = getchar();
    while (!isdigit(ch)){if (ch == '-')	w = -1; ch = getchar();}
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x *= w;
}
template<typename T>inline void write(T x){
    if (x < 0)	putchar('-'), x = ~(x - 1);
    if (x > 9)	write(x / 10);
    putchar(x % 10 ^ 48);
}

const int N = 1e5 + 5;

int n;
ll x;

vector<int> G[N << 5];
int ch[N << 5][2], tot = 1;
void ins(ll x){
    int p = 1;
    for (register int i = 29; i >= 0; --i){
        if (!ch[p][(x >> i) & 1])   ch[p][(x >> i) & 1] = ++tot, G[p].push_back(tot);
        p = ch[p][(x >> i) & 1];
    }
}

ll dfs(int u, int k){
    if (k < 0 || G[u].size() == 0)  return 0;
    if (G[u].size() == 2){
        return (1 << (k - 1)) + min(dfs(G[u][0], k - 1), dfs(G[u][1], k - 1));
    }
    else{
        return dfs(G[u][0], k - 1);
    }
}

int main(){
    //ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    read(n);
    for (register int i = 1; i <= n; ++i)
        read(x), ins(x);
    return write(dfs(1, 30)), putchar('\n'), 0;
}
```

---

## 作者：syksykCCC (赞：0)

看到异或，很自然想到从高位到低位贪心。如果较高的位置是能设为 $0$ 的，那一定将它设为 $0$，这样的答案一定最优。

我们可以对数集建 01-trie，为了适应从高位到低位的贪心，我们将第一层（也就是根节点所在的那一层）的 $dep$ 设为 $30$，从上到下依次 $-1$，得到一个总深度为 $30$ 的 trie，$dep = i$ 的层表示的是 $i$ 位的数字，位数从 $0$ 开始计算，最高到 $29$ 位，可以满足题目中 $a_i < 2^{30}$ 的要求。

比如样例，有三个数 $1, 2, 3$，我们的 01-trie 是这个样子的：

* 插入 $1$：

![image.png](https://i.loli.net/2020/01/12/OYUMHxcfvnlKSBL.png)

* 插入 $2$：

![image.png](https://i.loli.net/2020/01/12/AZYTdlbhp1xR7wB.png)

* 插入 $3$：

![image.png](https://i.loli.net/2020/01/12/lc7uN3VBPCEyIUb.png)

插入的代码不难写出：

```cpp
void insert(LL rt, LL val, LL dep)
{
	o[rt].dep = dep;
	if(!dep) return;
	if(!o[rt].ch[val >> dep - 1 & 1]) o[rt].ch[val >> dep - 1 & 1] = ++siz;
	insert(o[rt].ch[val >> dep - 1 & 1], val, dep - 1);
}
```

然后就可以在 01-trie 上 DP，在每个结点维护一个 $res$，表示以它为根的树的答案。比如现在要求 $res_{rt}$ 根据树形 DP 的基本操作，当然是先递归它的儿子，然后分类讨论一下：

* 如果 $rt$ 只有一个儿子，那么如果是 $ch_0$，$X$ 的这位就设成 $0$（保持不变），否则就设为 $1$（取反），总有办法使得这个位置的答案是 $0$，所以直接返回该儿子的 $res$ 即可

* 如果 $rt$ 两个儿子都有，那么如果 $X$ 这位设成 $0$，$ch_1$ 的该位就依然是 $1$；如果设为 $1$，$ch_0$ 的该位就变成了 $1$，既然 $2^{dep_{rt} - 1}$（$-1$ 因为是儿子那位的答案，写成 $2 ^{dep_{son}}$ 也行）逃不掉了，在此基础上加上 $\min(res_{ch_0}, res_{ch_1})$ 再返回即可

DP 的代码：

```cpp
void solve(LL rt)
{
	if(o[rt].ch[0]) solve(o[rt].ch[0]);
	if(o[rt].ch[1]) solve(o[rt].ch[1]);
	if(o[rt].ch[0] && o[rt].ch[1])
		o[rt].res = min(o[o[rt].ch[0]].res, o[o[rt].ch[1]].res) + (1LL << o[rt].dep - 1);
	else o[rt].res = o[o[rt].ch[0]].res + o[o[rt].ch[1]].res;
}
```

最后根节点 $1$ 的 $res$ 就是答案，完整的代码给出，供参考。

```cpp
#include <bits/stdc++.h>
#define ROOT 1
using namespace std;
typedef long long LL;
const int N = 2e5 + 5;
struct node
{
	LL res, dep, ch[2];
	node() { res = dep = ch[0] = ch[1] = 0; } 
} o[N * 20];
LL a[N], n, siz = 1;
void insert(LL rt, LL val, LL dep)
{
	o[rt].dep = dep;
	if(!dep) return;
	if(!o[rt].ch[val >> dep - 1 & 1]) o[rt].ch[val >> dep - 1 & 1] = ++siz;
	insert(o[rt].ch[val >> dep - 1 & 1], val, dep - 1);
}
void solve(LL rt)
{
	if(o[rt].ch[0]) solve(o[rt].ch[0]);
	if(o[rt].ch[1]) solve(o[rt].ch[1]);
	if(o[rt].ch[0] && o[rt].ch[1])
		o[rt].res = min(o[o[rt].ch[0]].res, o[o[rt].ch[1]].res) + (1LL << o[rt].dep - 1);
	else o[rt].res = o[o[rt].ch[0]].res + o[o[rt].ch[1]].res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		insert(ROOT, a[i], 30);
	}
	solve(ROOT);
	cout << o[ROOT].res << endl;
	return 0;
}
```

---

## 作者：skydogli (赞：0)

比赛的时候看到这题，想起了上次被[这题](https://www.luogu.com.cn/problem/CF1270C)支配的恐惧，不断提醒自己绝对不能想复杂，这是CFdiv2，不会考数据结构！代码一定很短！

然后yy出分治之后以为时间复杂度是错的。。。于是就又浪费了十分钟想到了01tire的做法。

思路：首先，我们可以通过构造$X$使任意的$a_i$成为整个序列中最大的$a_i \ \text{xor}\  X$,那么我们可以尝试对于每个$a_i$都构造出满足条件的$X$，并保证$a_i \  \text{xor} \ X$最小，最后我们取所有答案的最小值即可。

那么怎么保证$a_i\ \text{xor}\ X$是序列中最大的同时尽量最小呢？假设我们处理到第j-1位，那么我们必须保证$a_i\ \text{xor}\ X$是当前最大的，而这一位，如果有前j-1位与$a_i$相同，且第j位与$a_i$不同，那么我们就需要使$a_i \ \text{xor} X$的这一位为1，否则$a_i \ \text{xor} X$就不是序列最大的了。

什么东西能满足是否存在查询前j-1位相同第j位不相同的数呢？把所有$a_i$的01trie建出来即可。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define MN 100005
int n,a[MN],cnt,nex[MN<<5|1][2],ans[MN],X[MN];
int main(){
	scanf("%d",&n);
	cnt=1;
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		int add=1;
		for(int j=30;j>=0;--j){
			bool op=(a[i]>>j)&1;
			if(!nex[add][op])nex[add][op]=++cnt;
			add=nex[add][op];
		}
	}//建tire
	int p=1;
	for(int i=1;i<=n;++i){
		int now=1;
		for(int j=30;j>=0;--j){
			int op=(a[i]>>j)&1;
			if(!nex[now][!op]){X[i]|=(((LL)op)<<j);}
			else X[i]|=(((LL)!op)<<j),ans[i]|=(1<<j);//如果有另一位，那么这一位的答案必须为1
			now=nex[now][op];
		}
		if(ans[i]<ans[p])p=i;
	}
	printf("%d\n",ans[p]);

	return 0;
}
```


---

## 作者：OIer_ACMer (赞：0)

~~为啥 Trie 树会和 DP 结合在一起？~~

------------
注意：本题由于过于简单，因此笔者不会赘述证明以及原理，望各位悉知！

------------
## 大致思路：
本题在看到时，觉得不难，但是想一想发现如果不用 DP 做好像也没别的法子，于是，一个~~恐怖~~新奇的想法在我的脑海里浮现出来了：假如**我把这个序列变成一颗字典树然后在上庙跑 DP 会发生什么呢？**

首先，我们在每次输入一个数的时候就将其加入到字典树中去，**从而利用字典树优秀的时间复杂度来快速查找一个个数**，至于加入的细节笔者在这里不多赘述（因为如果你连这都不知道建议你回炉重造）。

接着，就到了很重要的一步——树上 DP 了。我们先定义一个变量 $ans$ 表示最大异或和的最小值，接着我们会发现：假设我们当前来到了第 $x$ 位，**无论它的哪个儿子是 $1$，进行异或后这一位都会出现 $1$**。因此由于异或以后这一位一定是 $1$，所以计入答案。同时用 $ans$ 记录下递归找出之后位所形成的最小值，转移方程如下（就是接着往儿子节点找）：

$ans=ans + \min(\operatorname{dfs}(son[p][0],pos+1),\operatorname{dfs}(son[p][1],pos+1))$。

如果当前位置的儿子就只有 $0$，我们可以取 $y$ 的当前位为 $1$，再递归找出之后位所形成的最小值，方程如下：

$ans=ans + \operatorname{dfs}(son[p][0],pos+1)$。

反之，如果当前位置的儿子就只有 $1$，我们可以取 $y$ 的当前位为 $0$，再递归找出之后位所形成的最小值，方程如下（说真的这方程已经简单得我都不想证明啥了）：

$ans = ans + \operatorname{dfs}(son[p][1],pos+1)$。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 4e6 + 10;
int son[N][2], cnt;
void build(int x)
{
    int p = 0;
    for (int i = 31; i >= 0; i--)
    {
        int u = x >> i & 1;
        if (!son[p][u])
        {
            son[p][u] = ++cnt;
        }
        p = son[p][u];
    }
}
int dfs(int p, int pos)
{
    int ans = 0;                
    if (son[p][0] && son[p][1]) 
    {
        ans += 1 << (31 - pos);                                       
        ans += min(dfs(son[p][0], pos + 1), dfs(son[p][1], pos + 1)); 
    }
    else if (son[p][0])
    {
        ans += dfs(son[p][0], pos + 1);
    }
    else if (son[p][1])
    {
        ans += dfs(son[p][1], pos + 1);
    }
    return ans;
}
int main()
{
    int n, a;
    n = read();
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        build(a);
    }
    cout << dfs(1, 1);
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122395758)

---

