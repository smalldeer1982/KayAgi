# 「WHOI-2」D&D

## 题目背景

有没有发现少了什么？

我们的 miku 决定出门逛街了。但是好巧不巧的就是她家里的装饰物少的可怜，并且只有一些数字可以作为装饰。

但是 miku 发现如果有若干个装饰物组成的数集 $A$，那么 $A$ 的子集 $f(A)$ 是最好看的（尽管不知道为什么）。所以就有了这道题。

但是因为看到了标题，所以聪明的你应该知道 miku 要去哪里了（误）。

## 题目描述

给定**不重**集合 $A$，定义其 _装饰子集_ 

$$f(A)=\{a\in A|\forall b\in A-\{a\},a|b\not= b \}$$

这里的 $\texttt{“|”}$ 表示按位或；这里 $b\in A-\{a\}$ 表示 $b\in A$ 且 $b\not=a$。

miku 有一个长度为 $n$ 的正整数序列 $a_i$。你要给这个序列连续地划分为若干个（至少一个）连续子串。要求这些连续子串元素所组成的**不重集合**的 _装饰子集_ 相同。

求方案数对 $10^9+7$ 取模。

## 说明/提示

**【样例#1解释】** 可以证明，两种方法分别是：
$$[1,2,3,4,5,5,4,3,2,1]$$
$$[1,2,3,4,5],[5,4,3,2,1]$$

这里三个子集所组成的不重集合都是 $\{1,2,3,4,5\}$。它们的装饰子集都是 $\{3,5\}$。具体说明如下：

- $1:1|3=3$，故不属于。
- $2:2|3=3$，故不属于。
- $3:3|1=3,3|2=3,3|4=7,3|5=7$，故属于。
- $4:4|5=5$，故不属于。
- $5:5|1=5,5|2=7,5|3=7,5|4=5$，故属于。

---
**本题采用捆绑测试**

- $\text{subtask1(5pts)}:n\leq10$。
- $\text{subtask2(10pts)}:a_i\leq7$。
- $\text{subtask3(20pts)}:a_i=2^a+2^b$。其中 $a\not = b$。
- $\text{subtask4(20pts)}:a_i=2^a+2^b$。其中不保证 $a\not =b$。
- $\text{subtask5(10pts)}:$ 保证 $a_i$ 随机生成。
- $\text{subtask6(35pts)}:$ 无特殊限制。时限为 $3s$。

对于 $100\%$ 的数据，保证 $1\leq n\leq 3\times10^6,0\leq a_i\leq2\times 10^6$。

## 样例 #1

### 输入

```
10
1 2 3 4 5 5 4 3 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
9
1 2 2 1 1 1 2 2 1```

### 输出

```
16```

# 题解

## 作者：Alex_Wei (赞：5)

> [P8434 「WHOI-2」D&D](https://www.luogu.com.cn/problem/P8434#submit)

集合 $A$ 的装饰子集即不被其它任何数包含的子集，$a$ 包含 $b$ 当且仅当 $a | b = a$，即 $b$ 为 $1$ 的位 $a$ 也为 $1$。

考虑原序列的装饰子集 $S$，假设 $x\in S$，因为 $x$ 不被任何数包含，所以对于任意子串 $[l, r]$，$x$ 同样不被区间内任何数包含。因此 $x$ 必然作为某个划分子串的装饰子集内的一个元素。所有子串的装饰子集包含 $S$。

考虑 $x\notin S$，假设存在 $y\in a_i$ 包含 $x$。因 $x$ 不可能作为 $y$ 所在子串的装饰子集，故所有子串的装饰子集不包含 $S$ 以外的元素。

这证明了所有子串装饰子集等于 $S$。

令 $l_i$ 表示使得 $[l_i, i]$ 包含所有 $S$ 内元素的最大的 $l_i$，显然可以双指针求出。

容易得到 DP $f_i$ 表示 $[1, i]$ 的答案，$f_1 = 0$。若 $l_i$ 存在，则有转移方程 $f_i = \sum\limits_{j = 0} ^ {l_i - 1} f_j$，表示将 $[j, i](j\leq l_i)$ 划为子串。前缀和优化即可做到 $\mathcal{O}(n)$。

求 $S$ 相当容易，只需对每个数 $a_i$ 检查是否存在 $a_j\neq a_i$ 有 $a_j$ 包含 $a_i$，可以再搞个 DP 算这玩意，也可以直接高维后缀和，相当好写。

时间复杂度 $\mathcal{O}(n + V\log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool Mbe;
constexpr int N = 3e6 + 5;
constexpr int mod = 1e9 + 7;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int n, a[N], f[N], g[N], s[N], cnt, buc[N], exist[N];
bool Med;
int main() {
  fprintf(stderr, "%.4lf\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i], f[a[i]] = exist[a[i]] = 1;
  for(int d = 2, k = 1; k < 1 << 21; d <<= 1, k <<= 1)
    for(int i = 0; i < 1 << 21; i += d)
      for(int j = 0; j < k; j++)
        f[i | j] += f[i | j | k];
  for(int i = 0; i < 1 << 21; i++) cnt += f[i] == 1 && exist[i];
  g[0] = s[0] = 1;
  for(int i = 1, l = 1; i <= n; i++) {
    s[i] = s[i - 1];
    cnt -= !buc[a[i]] && f[a[i]] == 1;
    buc[a[i]]++;
    while(f[a[l]] != 1 || buc[a[l]] > 1) buc[a[l++]]--;
    if(!cnt) g[i] = s[l - 1];
    add(s[i], g[i]);
  }
  cout << g[n] << "\n";
  return cerr << "Time: " << clock() << "\n", 0;
}
```



---

## 作者：Otomachi_Una_ (赞：3)

[隐藏的视频](https://bilibili.com/video/BV1Zi4y1M75s)

标题 $\text{D\&D}$ 的含义是 $\text{Darling Dance}$。

---

简单喵喵题

本题是一道结论题，本题只介绍 $100\%$ 的做法，这里先放上结论

> 划分完以后每一个集合的装饰子集与原数列的装饰子集相同。

一个直观的证明方法就是把每个数化为二进制。下面讲一讲严谨的证明。

我们设原数组的装饰子集为 $F$。

> 结论 1：假设 $x\in F$ 则 $x$ 在划分后的装饰子集中出现。

这个结论是显然的，反证法即可。

> 结论 2：假设 $x\not \in F$ 则 $x$ 不在划分后的装饰子集当中出现。

反之，必然有一个 $y\in F,x|y=y$。由结论 1，必然有 $y$ 在每一个装饰子集当中出现，这与 $x$ 存在于装饰子集当中矛盾。

> 结论 3：对于原数组的子集 $B$，只要 $F\subseteq B$ 那么 $B$ 的可爱子集是 $F$。

这个结论也是显然的。

有了结论，我们现在进一步解决该问题。

1. 快速求出原数组的装饰子集

考虑把 $a$ 从大到小排，丢进去 dfs 里面处理，具体流程如下：

```cpp
void dfs(int x){
	if(flag[x]) return;
	flag[x]=true;
	for(int i=0;i<=20;i++)
		if(x&(1<<i))
			dfs(x-(1<<i));
	return;
}
```

对于 $x$，若丢进去之前其 $\text{flag}$ 为假，那么它就是装饰子集当中的元素。

2. 快速求出划分方案

这里发现只要 $[l,i]$ 能划分为合法的装饰子集，那么 $[l-1,i]$ 也可以划分为合法的装饰子集。那么定义 $L_i$ 为最大的 $x$ 使得 $a[x,l]$ 是合法的装饰子集。那么得到转移公式：

$$f_i=\sum_{j=0}^{L_i-1} f_j$$

用前缀和优化即可。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1e6+5;
const int MOD=1e9+7;
int n;int a[MAXN],b[MAXN];
bool flag[MAXN];int col[MAXN];
int f[MAXN];int s[MAXN];int cnt=0,tmp=0;
int res[MAXN];
int L[MAXN];//L[i]表示最大的x使得[x,i]构成一个装饰子集. 
void dfs(int x){
	if(flag[x]) return;
	flag[x]=true;
	for(int i=0;i<=20;i++)
		if(x&(1<<i))
			dfs(x-(1<<i));
	return;
}
void cute_sub(){
	sort(b+1,b+n+1);
	for(int i=n;i>=1;i--)
		if(!flag[b[i]]){
			col[b[i]]=++cnt;
			dfs(b[i]);
		}
	for(int i=1;i<=n;i++)
		a[i]=col[a[i]];
	return;
}
void find_left(){
	int l=0;
	for(int i=1;i<=n;i++){
		if(a[i]!=0&&res[a[i]]++==0) tmp++;
		if(l==0&&tmp<cnt) L[i]=n+2;
		while(tmp==cnt){
			l++;
			if(a[l]!=0&&--res[a[l]]==0) tmp--;
		}
		if(!L[i]) L[i]=l;
	}
	return;
		
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],b[i]=a[i];
	cute_sub();
	find_left();
	s[0]=1;
	for(int i=1;i<=n;i++)
		s[i]=(s[i-1]+s[L[i]-1])%MOD;
	cout<<(s[n]-s[n-1]+MOD)%MOD;
	return 0;
}
```

---

## 作者：Sol1 (赞：2)

~~想了 1h+，没救了。~~

首先有朴素 $O(n^3)$ DP：设 $f_{i,j}$ 表示最后一段的左右端点是 $i,j$ 的方案数，枚举下一个分段点 $k$ 转移。

然后注意到，如果 $f(S_1)=f(S_2)$，那么 $f(S_1)=f(S_2)=f(S_1\cup S_2)$。同时我们知道 $j$ 前面每一段的装饰子集都一样，从而转移判据 $f(a_{[i,j]})=f(a_{[j+1,k]})$ 等价于 $f(a_{[1,j]})=f(a_{[j+1,k]})$。从而状态中的 $i$ 不需要记，得到状态 $O(n)$ 时间 $O(n^2)$ 的做法。

~~这俩做法为啥没个部分分区分一下，差评 /fn。~~

首先可以注意到 $f_i$ 可以转移到一段连续区间，并且区间左右端点随着 $i$ 移动均有单调性。考虑双指针，但是会发现 $f(a_{[i,j]})$ 难以维护。

尝试进一步简化判据。首先可以发现 $f(a_{[1,i]})=f(a_{[1,j]})$ 可以保证 $f(a_{[i+1,j]})\subset f(a_{[1,i]})$，这个可以扫一遍然后直接维护出来，然后只需要判断反向的包含是否成立即可，即判断是否有 $f(a_{[i+1,j]})\supset f(a_{[1,i]})$。

注意到这等价于 $a_{[i+1,j]}\supset f(a_{[1,i]})$，并且转移到的区间的左端点是 $a_{[i+1,j]}\supset f(a_{[1,i]})$ 成立的最靠左的位置，右端点是 $f(a_{[1,i]})=f(a_{[1,j]})$ 成立的最靠右的位置，于是容易双指针维护。

维护 $f$ 写个记忆化搜索就可以了。总复杂度 $O(n+a\log a)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

const int N = 3000005, LGV = 21, V = 1 << LGV;
const long long mod = 1000000007;
int n, a[N], mrk[V], rbnd[N], ins1[V], ins2[V], difc;
long long f[N];

inline void Read() {
	n = qread();
	for (int i = 1;i <= n;i++) a[i] = qread();
}

inline void addS1(int v) {
	//cout << "adds1 " << v << endl;
	if (!ins1[v] && !ins2[v]) difc++;
	ins1[v]++;
}

inline void delS1(int v) {
	//cout << "dels1 " << v << endl;
	ins1[v]--;
	//cout << "ins1 = " << ins1[v] << endl << "ins2 = " << ins2[v] << endl;
	if (!ins1[v] && !ins2[v]) {
		//cout << "difc -1" << endl;
		difc--;
	}
}

inline void addS2(int v) {
	//cout << "adds2 " << v << endl;
	if (!ins2[v] && ins1[v]) difc--;
	ins2[v]++;
}

inline void delS2(int v) {
	//cout << "dels2 " << v << endl;
	ins2[v]--;
	if (!ins2[v] && ins1[v]) difc++;
}

inline void Dfs(int s, int col) {
	if (mrk[s]) {
		if (mrk[s] == 1 && col == 2) delS1(s);
		mrk[s] = max(mrk[s], col);
		return;
	}
	mrk[s] = col;
	for (int t = s;t;t = t ^ (t & -t)) Dfs(s ^ (t & -t), 2);
}

inline void Prefix() {
	int lstc = 0;
	for (int i = 1;i <= n;i++) {
		if (!mrk[a[i]]) {
			addS1(a[i]);
			Dfs(a[i], 1);
			for (int j = lstc;j < i;j++) rbnd[j] = i - 1;
			lstc = i;
		}
	}
	for (int i = lstc;i <= n;i++) rbnd[i] = n;
	//for (int i = 1;i <= n;i++) cout << rbnd[i] << " ";
	//cout << endl;
}

inline void Solve() {
	//cout << "begin solve()" << endl;
	difc = 0;
	memset(mrk, 0, sizeof(mrk));
	memset(ins1, 0, sizeof(ins1));
	memset(ins2, 0, sizeof(ins2));
	f[0] = 1;
	int lpt = 1;
	addS2(a[1]);
	for (int i = 1;i < n;i++) {
		f[i] = (f[i] + f[i - 1]) % mod;
		//cout << i << " " << f[i] << endl;
		if (!mrk[a[i]]) addS1(a[i]);
		Dfs(a[i], 1);
		delS2(a[i]);
		//cout << "i = " << i << " difc = " << difc << " lpt = " << lpt << endl;
		while (lpt <= rbnd[i] && difc) {
			lpt++;
			addS2(a[lpt]);
			//cout << "i = " << i << " difc = " << difc << " lpt = " << lpt << endl;
		}
		f[lpt] = (f[lpt] + f[i]) % mod;
		f[rbnd[i] + 1] = (f[rbnd[i] + 1] - f[i] + mod) % mod;
	}
	cout << (f[n - 1] + f[n]) % mod << endl;
}

int main() {
	Read();
	Prefix();
	Solve();
	return 0;
}

```

---

## 作者：Graphcity (赞：2)

首先，我们设整个集合的装饰子集为 $P$。因为 $P$ 中的每个元素已经属于整个集合的装饰子集，它在连续子串中必然也属于那一部分的装饰子集。又因为每个连续子串的装饰子集相同，所以，**$P$ 中的每一个元素都应该在连续子串中出现**。

既然 $P$ 已经是全局的装饰子集，那么就不可能会有其它的数二进制位包含它。进一步，**每一个连续子串的装饰子集就是 $P$**。

问题变成了如何找到整个集合的装饰子集。我们猜想这个集合的大小非常小，事实上确是如此。设 $1\le a_i\le 2^k$，对于每一个装饰子集中的数 $p$，它二进制位中 1 的个数为 $q$，那么就会有 $2^q+2^{k-q}$ 个数必然不在装饰子集中。（ $2^q$ 个数被 $p$ 包含，$2^{k-q}$ 个数包含 $p$ ）当 $q=k-q$ 时，这个数最小为 $2^{\frac{k}{2}+1}$。所以装饰子集的大小至多为 $2^k\div2^{\frac{k}{2}+1}=2^{\frac{k}{2}-1}$。

所以当集合去重后，集合的大小乘上装饰子集的大小必然小于 $(2^{\frac{k}{2}})^2=2^{k}$（ 此时集合仅包含 $2^{\frac{k}{2}-1}$ 个装饰子集元素和它们包含的 $2^{\frac{k}{2}-1}$ 个元素 ）

本题中 $k\le 21$，所以这个数至多为 $2^{21}$，可以接受。接下来就是设计一个算法来找到装饰子集。

如果一个数 $a$ 被另外一个不同的数 $b$ 包含，那么一定有 $b>a$。对集合去重后，我们从大到小枚举每个数，并检查是否被当前的装饰子集包含，如果没有就加入装饰子集。时间复杂度为去重后集合的大小乘上装饰子集的大小。

设 $pos_i$ 为满足从它到 $i$ 包含了所有装饰子集的最大数字。对于每个装饰子集中的元素 $p$，设 $lst_p$ 表示它在当前最后出现的位置。那么就有 $pos_i=\min_plst_p$ 。

当 $i$ 每次向右增加 1 时，至多会更新一次 $lst_p$。用小根堆维护它们的最小值即可。

设 $f_i$ 为 $[1,i]$ 范围内的方案数，则有 $f_i=[pos_i\ge 1]+\sum_{j=1}^{pos_i-1}f_j$，可以前缀和优化。

总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e6,Mod=1e9+7;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,val[Maxn+5],num[Maxn+5],pos[Maxn+5];
int vis[Maxn+5],lst[Maxn+5],f[Maxn+5],del[Maxn+5];
int sum[Maxn+5],st[Maxn+5],top;
priority_queue<int,vector<int>,greater<int>> q;

int main()
{
    n=read();
    For(i,1,n) val[i]=num[i]=read();
    sort(num+1,num+n+1),m=unique(num+1,num+n+1)-(num+1); // 排序去重
    Rof(i,m,1) // 找装饰子集
    {
        int kazuha=0;
        For(j,1,top) if((num[i]|st[j])==st[j]) {kazuha=1; break;}
        if(!kazuha) st[++top]=num[i];
    }
    For(i,1,top) vis[st[i]]=i,q.push(0);
    For(i,1,n)
    {
        int now=vis[val[i]],Min=i;
        if(now) del[lst[now]]++,lst[now]=i,q.push(i);
        while(!q.empty())
        {
            int x=q.top();
            if(del[x]) del[x]--,q.pop();
            else {Min=x; break;}
        }
        pos[i]=Min;
    }
    For(i,1,n)
    {
        f[i]=(pos[i]>=1);
        if(pos[i]) f[i]=(f[i]+sum[pos[i]-1])%Mod;
        sum[i]=(sum[i-1]+f[i])%Mod;
    }
    printf("%d\n",f[n]);
    return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

这题我的代码跑了 1.34s，~~应该是全谷最劣解~~。

这里记 $\max(a_i)=V$。

首先，能想到一个暴力做法。

暴力枚举装饰子集是什么，然后使用 DP 对划分计数，复杂度高达 $O(2^nn^3)$，可以得到 5pts。

具体的，记 $f_i$ 表示只考虑 $a_1$ 到 $a_i$ 的答案，每次暴力枚举从哪转移即可。

考虑如何优化，设 $a$ 有两个数 $x,y$ 满足 $x|y=y$，则有 $y$ 的那一段的装饰子集不可能有 $x$，进而可得枚举的装饰子集中不应出现 $x$。

类似的，若 $a$ 不存在 $y$ 满足 $x|y=y$，则必然存在一段的装饰子集有 $x$，进而可得枚举的装饰子集中应出现 $x$。

综上，可以唯一确定装饰子集。

下面考虑优化 DP。

你发现 $x|y=y,y|z=z\Rightarrow x|z=z$。可得如果段 $[l,r]$ 的装饰子集是我们枚举的那个，则 $[l-1,r]$ 和 $[l,r+1]$ 的装饰子集也是我们枚举的那个。

这告诉我们在 DP 中，可以转移到 $i$ 的位置 $j$ 构成一段从 1 开始的区间，直接前缀和优化即可。

求装饰子集可以用高维后缀和，求最靠右的 $j$ 可以用链表维护 $a_i$ 相同的位置，再从后往前扫一遍即可，当然也可以写 set。

代码（用 set 实现，$O(n\log n+V\log V)$）：


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N=3e6+19,mod=1e9+7;
int f[N],g[N];
int t[N*2+1],s[N*2+1];
int a[N];
int n;
bool c[N*2+1];int cnt=0;
int nxt[N],hd[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) t[a[i]]++,s[a[i]]++;
	int V=1<<22;
	for(int i=0;i<22;i++){
		for(int j=0;j<V;j++){
			if((j>>i)&1) s[j-(1<<i)]+=s[j];
		}
	}
	for(int i=0;i<V;i++){
		if(t[i]!=0&&t[i]==s[i]) c[i]=1,cnt++;
	}set<int> q;
	f[0]=1;g[0]=1;
	for(int i=1;i<=n;i++){
		nxt[i]=hd[a[i]];hd[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		//cout<<cnt<<' '<<q.size()<<endl;
		if(c[a[i]]) q.erase(nxt[i]),q.insert(i);
		if(q.size()==cnt){
			f[i]=g[*q.begin()-1];
		}g[i]=(g[i-1]+f[i])%mod;
	}cout<<f[n]; 
    return 0;
}
```

---

## 作者：2017gdgzoi999 (赞：0)

> 第一个完全自己想出来并且一次过还拿了最优解的 dp 紫题 qaq

> 做法大体同其它题解一致，但这里判断左侧指针位置用的方式稍有不同，是根据段的划分位置而非完整装饰子集的构成。也许这样常数稍微小一点？

根据插板法的老套路，将 $n$ 个元素分为若干段，其中有 $n-1$ 处可作为两段的分界，则问题转化为将若干插板放在 $n-1$ 个有序位置。

根据集合原理类比位运算，一个数 $a_i$ 不在“装饰子集”中即存在一个 $j$ 使得 $a_i\neq a_j$ 且 $a_i\&a_j=a_i$，也就是说 $a_i$ 中有的位 $a_j$ 都有，而且 $a_j$ 中还有些 $a_i$ 中没有的位，那么可以感性理解成 $a_i$ 被 $a_j$ 完爆了。。。

现在可以认为装饰子集的元素就是那些没有被别人完爆的大佬。。。相比原来，分段后只是踢出了一些人，没被踢出的大佬一定还是大佬。。。不妨称 **整个数组装饰子集中的元素为优势元素**，所以分段后，**对于每个优势元素，它在分段后一定还在它所在段的装饰子集**。当然，根据每段装饰子集一致的要求，可推出 **对于每个优势元素，它在每一段中至少出现了一次 【条件 A】**。

接下来讨论非优势元素。它们能不能再分段后翻身做大佬呢？假设一个非优势元素翻身成功了，据题意则每个区间它们都加入了装饰子集，那么原来完爆它的大佬就无处安放了 qaq。因此 **对于每个非优势元素，它在分段后中一定仍不在该段的装饰子集中 【条件 B】**。

$a_i$ 比较小，我们可以考虑枚举优势元素。不过在这之前，我们要先找出所有的优势元素。原始的想法是枚举所有 $i\&j=j,i\neq j$，但这样时间复杂度不可接受。考虑到 $j$ 可以通过 $i$ 删去若干位 $1$ 得到，我们将 $i$ 和所有“删去一位 $1$”得到的 $j$ 连边，那么 $i$ 一定能直接或间接走到所有满足条件的 $j$。这样，总边数是 $\max\{a_i\}\log_{\max\{a_i\}}$ 级别的，边总是由大向小连的，拓扑排序就行了。

显然如果条件 A 满足了，条件 B 也自动满足，因此我们只讨论条件 A。对于每个 **优势元素** $x$，找到它在数组中所有出现位置：

![](https://cdn.luogu.com.cn/upload/image_hosting/bh3l8al0.png)

我们根据这些位置设置一些限定条件（见上图）：

$\small\tt\color{#6cf}蓝色区间$：最左侧 $x$ 的左边和最右侧 $x$ 的右边，这区间总是贴着边缘的，直接维护不在蓝色区间的左右端点就行了。（当然，如果存在一个 $x$ 只出现一次，那么就可以直接输出 $1$ 跑路啦）

$\small\tt\color{#39c5bb}绿色区间$：每两个相邻 $x$ 的中间部分。这个范围内最多插一个版，我们把这个区间记下来，作为一个“最多一个”的区间。

我这里的插板位置 $i$ 指的是 $a_i$ 和 $a_{i+1}$ 的间隔，因此左侧 $a_l$，右侧 $a_r$ 的区间对应下来就是 $[l,r-1]$。

接下来，我们将提取所有 **有效的“最多一个区间”**。若 $[l_1,r_1]$ 是“最多一个区间”那么 $[l_2,r_2]\ (l_1\leq l_2\leq r_2\leq r_1)$ 也是“最多一个区间”， 设 $rp_i$ 为满足 $[i,rp_i]$ 为“最多一个区间”的最大值，用以下三步骤得到 $rp_i$：

1. 显然 $[i,i]$ 是“最多一个区间”，$rp_i$ 初值设为 $i$。

2. 对于所有以 $i$ 为左侧的绿色区间 $[i,r]$，将 $rp_i$ 与 $r$ 取最大值。

3. 若 $rp_{i-1}\geq i$，则 $[i,rp_{i-1}]$ 也是“最多一个区间”，将 $rp_i$ 与 $rp_{i-1}$ 取最大值。

因为左端点比较好维护，我们称 **所有 $[i,rp_i]$ 为有效区间**。我们 **设 $dp_i$ 为最后一个版插在 $i$ 处的方案数**。

![](https://cdn.luogu.com.cn/upload/image_hosting/mhy0linb.png)

（见上图）那么，可以得到状态转移方程：

$$dp_i=\begin{cases}1+\sum_{1\leq j<i,rp_j<i}dp_j\small\ (i\ 不在蓝色区间内)\\0\small\ (i\ 在蓝色区间内)\end{cases}$$

我们动态维护一个指针 $p$（初始为 $0$），表示满足 $rp_p<i$ 的最大值。因为 $rp_i$ 是单调不减的，所以 $p$ **也是单调不减的，直接维护双指针+前缀和即可**。

最终答案即为 $1+\sum_{i=1}^{n-1}dp_i$

Code（143 ms，暂时是最优解）:

```cpp
#define lowbit(x) (x&(-x)) // 求 x 最低位的 1
int main() {
	int n=read(), mx=0;
	// pre[i] : 前一个与 a[i] 相同数的位置
	// lst[i] : 最后一个值为 i 的位置
	for (int i=1; i<=n; ++i) {
		int x = read();
		pre[i]=lst[x]; lst[x]=i;
		mark[x]=2; mx=max(mx,x);
		rp[i] = i; // rp 计算的第一步
	}
	// mark[i] : (0:i 未被数组元素完爆，但也未出现; 1:i 被数组元素完爆; 2:i 是优势元素)
	int accl=1, accr=n-1; // 未在蓝色区域的左右边界
	for (int i=mx; i>=0; --i) {
		if (!mark[i]) continue; // 未出现、被直接完爆或间接完爆，无法参与拓扑排序的标记
		if (mark[i]==2) { // 枚举每个优势元素 i
			int pos=lst[i]; accr=min(accr,pos-1); // a[pos] 是最右侧的 i，设置右侧的蓝色区域
			if (!pre[pos]) { // i 只有一个，挡板无处可放
				printf("1"); return 0;
			}
			int nxt=pos; pos=pre[pos];
			while (pos) {
				rp[pos] = max(rp[pos],nxt-1);
				// a[nxt] 和 a[pos] 是两个相邻的 i，在 [nxt,pos-1] 设立绿色区域，rp 计算的第二步
				nxt=pos; pos=pre[pos];
			}
			accl = max(accl,nxt); // a[nxt] 是最左侧的 i，设置左侧的蓝色区域
		}
		if (accl>accr) { // [1,n-1] 已被蓝色区域填满，挡板无处可放
			printf("1"); return 0;
		}
		int pos = i;
		while (pos) {
			int val=lowbit(pos); mark[i^val]=1;
			// val 为 i 中的每一位 1，i^val 即将 i 的一位 1 换成 0 的结果，让它被完爆
			pos ^= val; // 类似树状数组，枚举 i 每位 1 的套路
		}
	}
	--n; for (int i=1; i<=n; ++i) rp[i]=max(rp[i],rp[i-1]); // rp 计算的第三步
	int pos=0, res=1, pre=1; // 别忘了没插挡板的情况
	for (int i=accl; i<=accr; ++i) { // 在蓝色区域的位置已被该循环忽略
		while ((pos<n)&&(rp[pos+1]<i)) { // 因为 i 的增加，p 动态右移
			++pos; pre+=dp[pos]; if (pre>=MOD) pre-=MOD; // 同时统计 dp 前缀和
		}
		dp[i]=pre; res+=pre; if (res>=MOD) res-=MOD;
	}
	printf("%d", res);
	return 0;
}
```

> 这题的确解法非常巧妙，不需要高级的算法和数据结构却能环环相扣，最后柳暗花明又一村，好久没体验到这种 OI 独有的快乐了呢。 （最后一提 miku 赛高!qwq）

---

