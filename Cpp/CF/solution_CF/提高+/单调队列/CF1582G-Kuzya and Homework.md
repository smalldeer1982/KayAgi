# Kuzya and Homework

## 题目描述

Kuzya started going to school. He was given math homework in which he was given an array $ a $ of length $ n $ and an array of symbols $ b $ of length $ n $ , consisting of symbols '\*' and '/'.

Let's denote a path of calculations for a segment $ [l; r] $ ( $ 1 \le l \le r \le n $ ) in the following way:

- Let $ x=1 $ initially. For every $ i $ from $ l $ to $ r $ we will consequently do the following: if $ b_i= $ '\*', $ x=x*a_i $ , and if $ b_i= $ '/', then $ x=\frac{x}{a_i} $ . Let's call a path of calculations for the segment $ [l; r] $ a list of all $ x $ that we got during the calculations (the number of them is exactly $ r - l + 1 $ ).

For example, let $ a=[7, $ $ 12, $ $ 3, $ $ 5, $ $ 4, $ $ 10, $ $ 9] $ , $ b=[/, $ $ *, $ $ /, $ $ /, $ $ /, $ $ *, $ $ *] $ , $ l=2 $ , $ r=6 $ , then the path of calculations for that segment is $ [12, $ $ 4, $ $ 0.8, $ $ 0.2, $ $ 2] $ .

Let's call a segment $ [l;r] $ simple if the path of calculations for it contains only integer numbers.

Kuzya needs to find the number of simple segments $ [l;r] $ ( $ 1 \le l \le r \le n $ ). Since he obviously has no time and no interest to do the calculations for each option, he asked you to write a program to get to find that number!

## 样例 #1

### 输入

```
3
1 2 3
*/*```

### 输出

```
2```

## 样例 #2

### 输入

```
7
6 4 10 1 2 15 1
*/*/*//```

### 输出

```
8```

# 题解

## 作者：泥土笨笨 (赞：11)

## 题目大意

给我们一个长度为 $n$ 的数组 $a$ ，里面都是整数。再给我们一个长度为 $n$ 的数组 $b$ ，里面都是乘号和除号。问有多少个子序列 $[l,r]$ ，满足以下条件：初始给出一个数字 $x=1$ ，然后遍历 $[l,r]$ 区间的每个数字 $i$ ，如果 $b[i]$ 是乘号，就 $x=x \times a[i]$ ，如果 $b[i]$ 是除号，就 $x=x / a[i]$ ，要求计算过程中 $x$ 必须一直是整数。

## 思路

首先我们想到，对于每个数字，应该要先分解质因数，每个质因子互相没有影响，可以单独计算。那么对于同一个质因子，我们发现问题可以转化为合法括号序列的问题。如果对应的位置是乘号，我们就写一个左括号，如果对应位置是除号，我们就写一个右括号，那么这个问题特别类似于在一个左右括号的字符串中，找有多少个括号合法的子串。

定义数组 $l[i]$ 表示对于以第 $i$ 个数字结尾的时候，对于所有左端点 $x>=l[i]$ 的 $x$ ， $x$ 到 $i$ 都可以构成合法区间。考虑一下这个数组怎么求。

我们开一个栈的数组 `stack<int> pp[1e6+5];` ，用这个数组的每个位置，记录每个质因子出现的位置有哪些。比如 `pp[2]` 就存质因子 $2$ 出现过的位置。

依次遍历 $1$ 到 $n$ ，对于每个数字 $a[i]$ ，分解出当前的质因子 $p$ ，如果 $b[i]$ 是乘号，那么 $l[i]$ 是不受影响的，赋值为 $i$ ，这时候把质因子 $p$ 放到一个 $pp[p]$ 里面。如果 $b[i]$ 是除号，就到 $pp[p]$ 里面去 `pop` 掉一个位置，表示这个位置的乘要抵消现在的除，这时候 $l[i]$ 就要更新成刚才 `pop` 出来的位置，表示这个位置以前（包括这个位置）开头是可以的。

当 $l$ 数组预处理完以后，我们要统计答案，设 $f(i,j)$ 表示 $[i,j]$ 范围内所有 $l$ 的最小值，那么答案就是满足 $l<=f(l,r)$ 的 $[l,r]$ 对的个数。统计这个个数的时候，可以倒着枚举 $n$ 到 $1$ 的整数 $i$ ，看看区间右端点是 $r$ 的时候，对每个答案的贡献。这里可以开一个栈，来维护。

## 代码

```
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>

using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 5;

int n, a[MAXN], p[MAXN], pc, fac[MAXN], b[MAXN];
int l[MAXN];//l[i]表示对于以第i个数字结尾的时候，对于左端点x>=l[i]的x，都可以构成合法区间
vector<int> pp[MAXN];//存每个质数出现的位置，如果有一个数字里面出现多个相同的质因子，插入多次
//这里的pp其实是当栈来用的，但是1e6个stack直接MLE，vector空的只占30M空间
char s[MAXN];

//先打质数表
void getPrime() {
    for (int i = 2; i < MAXN; ++i) {
        b[i] = 1;
    }
    for (int i = 2; i < MAXN; ++i) {
        if (b[i]) {
            p[pc++] = i;
            fac[i] = i;
        }
        for (int j = 0; j < pc && p[j] * i < MAXN; ++j) {
            b[p[j] * i] = 0;
            fac[p[j] * i] = p[j];//f数组记录每个数的最小质因子
        }
    }
}

//处理乘号的位置
void add(int x, int pos) {
    l[pos] = pos;
    while (x > 1) {
        pp[fac[x]].push_back(pos);
        x /= fac[x];
    }
}

//处理除号的位置
void del(int x, int pos) {
    l[pos] = pos;
    while (x > 1) {
        if (pp[fac[x]].size()==0) {
            l[pos] = 0;
            return;
        }
        l[pos] = min(l[pos], pp[fac[x]].back());
        pp[fac[x]].pop_back();
        x /= fac[x];
    }
}

struct Node {
    ll l, ans;
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    scanf("%s", (s + 1));
    getPrime();
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '*') {
            add(a[i], i);
        } else {
            del(a[i], i);
        }
    }
    ll ans = 0;
    stack<Node> ss;
    for (int i = n; i >= 1; --i) {
        //枚举i作为右端点的时候，顺便统计所有以i作为l[i]的答案
        ll now = 1;
        //累加前面的答案
        while (!ss.empty() && ss.top().l >= l[i]) {
            now += ss.top().ans;
            ss.pop();
        }
        ss.push(Node{l[i], now});
        if (l[i] == i) ans += now;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Alex_Wei (赞：7)

1582G. [Kuzya and Homework](https://codeforces.com/contest/1582/problem/G)

对于每个位置 $i$ 我们求出 $pre_i$ 表示如果要让以 $i$ 结尾的区间是好区间则左端点至少要在 $pre_i$ 及其左边。若 $s_i=\texttt{*}$ 显然 $pre_i=i$，否则 $s_i=\texttt{/}$，可以这么做：

实际上这个 “不出现分数” 的性质和括号匹配十分类似：对于每个质数 $p$，若把乘看做左括号，除看做右括号，那么不出现 $\dfrac 1 p$ 等价于不存在没有被匹配的右括号。这启发我们对每个质数用一个栈维护其 “括号序列”，若是乘则加入左括号，否则弹出左括号。

对于除法，最后一次被弹出的括号的位置就是 $pre_i$，因为若 $j>pre_i$ 那么 $s_i$ 处的右括号没法被匹配。相反，如果已经没有左括号可以弹了，那么显然任何以 $i$ 结尾的区间都不是好区间，令 $pre_i=0$。 注意**一个位置可能贡献多个左括号或右括号**。

不难发现若 $l=\min_{i=l}^r pre_i$ 则 $[l,r]$ 是好区间。考虑从后往前用单调栈维护从从栈底到栈顶从小到大的 $pre_i$，若当前 $pre_i=i$ 则加上栈顶矩形宽度即 $p-i+1$，其中 $p$ 最大且满足对于任意 $q\in[i,p]$ 都有 $pre_q\geq i$，这是单调栈的过程中顺带维护的信息，可以类比求图中最大矩形的问题。当然，线段树二分维护最小值也可以。

前者若一个位置加入多个左右括号时捆绑在一起看是 $\mathcal{O}(n\omega(a_i))$，拆开来看是 $\mathcal{O}(n\log a_i)$，后者时间复杂度 $\mathcal{O}(n\log a_i)$。

```cpp
const int N = 1e6 + 5;
int vis[N], mp[N], pr[N], cnt;
void sieve() {
	for(int i = 2; i < N; i++) {
		if(!vis[i]) mp[i] = pr[++cnt] = i;
		for(int j = 1; j <= cnt && i * pr[j] < N; j++) {
			vis[i * pr[j]] = 1, mp[i * pr[j]] = pr[j];
			if(i % pr[j] == 0) break;
		}
	}
}

int n, pre[N], a[N];
vint buc[N];

int top, stc[N], w[N];
ll ans;

bool Med;
int main() {
	cin >> n, sieve();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) {
		char s = gc;
		while(s != '*' && s != '/') s = gc;
		if(s == '*') {
			while(a[i] > 1) {
				int p = mp[a[i]];
				buc[p].pb(i), a[i] /= p;
			} pre[i] = i;
		} else {
			pre[i] = i;
			while(a[i] > 1) {
				int p = mp[a[i]];
				if(buc[p].empty()) pre[i] = -1;
				else cmin(pre[i], buc[p].back()), buc[p].pop_back();
				a[i] /= p;
			}
		}
	}
	for(int i = n; i; i--) {
		int nw = 1;
		while(top && pre[i] <= stc[top]) nw += w[top], top--;
		stc[++top] = pre[i], w[top] = nw;
		if(pre[i] == i) ans += nw;
	} cout << ans << endl;
	return 0;
}
```

---

## 作者：Sol1 (赞：5)

~~诶怎么泥土笨笨又发了个题解啊，那我继续抢生意！！！!1~~

乘除运算要求整除的这一形式引诱我们将这个问题里面的数的每一个质因子拆出来考虑。那么就尝试直接把每一个质数在每一个数的唯一分解中的出现次数提取出来。

首先我们考虑如果拆出来的问题解决了，该如何把这些问题的答案拼回去得到原问题的答案。可以观察到每一个数，以它为开头的可行区间的右端点一定分布在从这个点开始的一段前缀里面。于是我们对于每一个点，维护出以它开头的最大可行区间的右端点。这样只要对于每一个质因数分别求解然后取 min 即可。

然后问题变为如下形式：一个长度为 $n$ 的序列 $c$，对于每一个点 $i$，求出最大的 $r_i$，使得 $\forall i\leq j\leq r_i,\text{s.t.} \sum_{k=i}^jc_k\geq 0$。**但是这个序列里面会有非常多的 $0$，而计算答案和把答案拼回去的复杂度都只能与非 $0$ 数个数相关。**

观察不难发现一个非 $0$ 数前面紧邻的一段 $0$ 的答案和这个非 $0$ 数的答案是一样的，那么这个新问题的做法就很明显了：维护一个前缀和，倒着扫，维护一个单调栈，每次直接在单调栈上二分查询答案，最后做一个区间取 $\min$。那么这样问题就变为了若干次区间取 $\min$ 求最终序列。这就是一个经典问题了，可以使用并查集完成。

最终复杂度 $O(n\omega(v)\log n+n\sqrt v)$，可以通过。

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

int n, a[1000005], b[1000005], pri[1005], pcnt, pre[1000005], stktop, f[1000005], res[1000005];
bool vis[1005];
vector <pair <int, int> > v[1000005], opt[1000005];
pair <int, int> stk[1000005];

inline int GetRoot(int v) {
	if (f[v] == v) return v;
	return f[v] = GetRoot(f[v]);
}

inline void Merge(int x, int y) {
	int u = GetRoot(x), v = GetRoot(y);
	if (u != v) {
		f[u] = v;
		return;
	}
}

inline char readchar() {
	char c = getchar();
	while (c != '/' && c != '*') c = getchar();
	return c;
}

inline void Read() {
	n = qread();
	for (int i = 1;i <= n;i++) a[i] = qread();
	for (int i = 1;i <= n;i++) {
		char c = readchar();
		if (c == '*') b[i] = 1;
		else b[i] = -1;
	}
}

inline void Prefix() {
	for (int i = 2;i <= 1000;i++) {
		if (!vis[i]) {
			pri[++pcnt] = i;
			for (int j = i * i;j <= 1000;j += i) vis[j] = 1;
		}
	}
	for (int i = 1;i <= n;i++) {
		int tmp = a[i];
		for (int j = 1;j <= pcnt && pri[j] * pri[j] <= tmp;j++) {
			if (tmp % pri[j] == 0) {
				int cnt = 0;
				while (tmp % pri[j] == 0) {
					tmp /= pri[j];
					cnt++;
				}
				v[pri[j]].push_back(make_pair(i, cnt * b[i]));
			}
		}
		if (tmp > 1) v[tmp].push_back(make_pair(i, b[i]));
	}
}

inline void Solve() {
	for (int i = 1;i <= 1000000;i++) {
		if (v[i].empty()) continue;
		int siz = v[i].size();
		pre[0] = v[i][0].second;
		for (int j = 1;j < siz;j++) pre[j] = pre[j - 1] + v[i][j].second;
		stktop = 1;
		stk[stktop] = make_pair(0xf3f3f3f3, n + 1);
		for (int j = siz - 1;j >= 0;j--) {
			while (stktop && stk[stktop] >= make_pair(pre[j], v[i][j].first)) stktop--;
			stk[++stktop] = make_pair(pre[j], v[i][j].first);
			int idx = upper_bound(stk + 1, stk + stktop + 1, make_pair(pre[j] - v[i][j].second, 0)) - stk - 1;
			int l;
			if (j == 0) l = 1;
			else l = v[i][j - 1].first + 1;
			opt[stk[idx].second - 1].push_back(make_pair(l, v[i][j].first));
		}
	}
	for (int i = 1;i <= n + 1;i++) f[i] = i;
	for (int i = 1;i <= n;i++) res[i] = n;
	for (int i = 0;i <= 1000000;i++) {
		int siz = opt[i].size();
		for (int j = 0;j < siz;j++) {
			int l = opt[i][j].first, r = opt[i][j].second;
			for (int k = GetRoot(l);k <= r;k = GetRoot(k + 1)) {
				res[k] = i;
				Merge(k, k + 1);
			}
		}
	}
	long long ans = 0;
	for (int i = 1;i <= n;i++) ans += res[i] - i + 1;
	cout << ans << endl;
}

int main() {
	Read();
	Prefix();
	Solve();
	return 0;
}
```

---

## 作者：chenzida (赞：5)

感觉这题思路比较有启发性，还是要好好写一篇题解

首先，我们发现质因子是独立的，于是考虑拆质因子，然后对于每个质因子做一下，之后再整合答案。（1）

然后我们分析一下复杂度发现，对于每个质因子我们的复杂度限制是 $O(\text{关键点个数})$，这样问题就变成了，给定 $n$ 个数，对于每个左端点，求出最大的右端点使得中间没有 $<0$ 的数，这个可以考虑啥时候一段区间的和是小于 $0$ 的，也就是说，我们可以维护一下前缀和，对于每个点找到第一个前缀和比它小的点，这个倒着扫一遍，用单调找维护答案。（2）

现在我们的问题变成了，给定 $n\log n$ 个区间对定值取 $\min$，以及最后对每个点查询。这里直接上线段树复杂度就会退化了。考虑一个nb做法，把 ST 表倒过来做，对于一个修改操 $[l,r]$，我用 ST 表查询的方法分为两个区间，然后我倒置做一遍 ST 表即可。（3）

这道题有两个 $\text{trick}$ 和一个思维点。其中（1）（3）一般只能通过多做题积累来学会，而（2）就考验思维的能力了，比如区间和转化为前缀和，以及用单调找来维护等等。

---

## 作者：zhangxy__hp (赞：0)

要求结果为整数，我们将所有 $a_i$ 分解质因数，对于每个质数分别考虑。

考虑对于一个左端点 $l$，能满足要求的右端点一定在从 $l$ 开始的一段连续区间中。于是我们得对于每个 $l$ 求出 $ans_l$ 表示那个最远的右端点。

对于一个质数 $p$，假设 $a_i$ 中有 $k$ 个 $p$，如果 $b_i$ 为乘号就在 $i$ 这里记一个 $k$，否则记一个 $-k$。然后再做一个前缀和 $pre$。那么对于 $l$，我们要求的就是最大的 $r$，满足 $\forall k\in[l,r],pre_k-pre_{l-1}\ge 0$。可以倒着扫，维护一个单调栈，每次在单调栈上二分。但是这样的时间复杂度是无法承受的。我们考虑如果 $a_i$ 中没有 $p$，那么 $i$ 这个位置的答案就是等于 $i+1$ 的答案的。于是我们只用存储那些包括了 $p$ 的位置。于是就成了若干次区间的取 $\min$。再用并查集扫一遍即可。

先将所有质数都筛出来，时间复杂度可以承受。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define lwrb lower_bound
using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=1e6+5,inf=0x3f3f3f3f;
int n,prn,a[maxn];
int prm[maxn],pre[maxn];
int zh1[maxn],zh2[maxn];
int fa[maxn],ans[maxn];
bool npr[maxn];
string b;
vector<pii> wei[maxn],cun[maxn];
il void init(int x){
	for(int i=2;i<=x;i++){
		if(!npr[i]){
			prm[++prn]=i;
		}
		for(int j=i*i;j<=x;j+=i){
			npr[j]=1;
		}
	}
}
il int find(int x){
	return x!=fa[x]?fa[x]=find(fa[x]):x;
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cin>>b;
	b=" "+b;
	init(1e3);
	for(int i=1,tmp;i<=n;i++){
		tmp=a[i];
		for(int j=1,cnt;j<=prn&&prm[j]<=tmp/prm[j];j++){
			if(tmp%prm[j]==0){
				cnt=0;
				while(tmp%prm[j]==0){
					tmp/=prm[j],cnt++;
				}
				wei[prm[j]].pb(mp(i,b[i]=='*'?cnt:-cnt));
			}
		}
		if(tmp>1){
			wei[tmp].pb(mp(i,b[i]=='*'?1:-1));
		}
	}
	for(int i=1,top;i<=1e6;i++){
		if(wei[i].empty()){
			continue;
		}
		pre[0]=wei[i][0].sec;
		for(int j=1;j<wei[i].size();j++){
			pre[j]=pre[j-1]+wei[i][j].sec;
		}
		top=1;
		zh1[1]=-inf,zh2[1]=n+1;
		for(int j=wei[i].size()-1,k;~j;j--){
			while(top&&zh1[top]>pre[j]){
				top--;
			}
			zh1[++top]=pre[j],zh2[top]=wei[i][j].fir;
			k=lwrb(zh1+1,zh1+top+1,pre[j]-wei[i][j].sec)-zh1-1;
			cun[zh2[k]-1].pb(mp(j?wei[i][j-1].fir+1:1,wei[i][j].fir));
		}
	}
	for(int i=1;i<=n+1;i++){
		fa[i]=i,ans[i]=n;
	}
	for(int i=0;i<=n;i++){
		for(pii j:cun[i]){
			for(int k=find(j.fir);k<=j.sec;k=find(k+1)){
				ans[k]=i;
				fa[find(k)]=find(k+1);
			}
		}
	}
//	for(int i=1;i<=n;i++){
//		cout<<ans[i]<<" ";
//	}
//	puts("");
	ll Ans=0;
	for(int i=1;i<=n;i++){
		Ans+=ans[i]-i+1;
	}
	cout<<Ans;
	return 0;
}
}
int main(){return asbt::main();}
```

---

## 作者：Laoshan_PLUS (赞：0)

# [CF1582G Kuzya and Homework](https://www.luogu.com.cn/problem/CF1582G)

首先容易知道的是 “仅含整数” 要想到分解质因数，然后 `*` 和 `/` 两种运算容易想到对每个质因数的出现次数进行 $+1$ 和 $-1$ 的操作。于是一个区间合法当且仅当所有质因数在这个区间内所有位置的出现次数大于等于 $0$。

然后考虑求一个数组 $l_i$，表示如果以第 $i$ 个位置作为区间右端点，那么区间左端点至少要 $\le l_i$。先假设我们已经求出了这个数组，现在要统计答案，那么一个区间 $[L,R]$ 符合要求当且仅当 $\forall i\in[L,R],L\le l_i$，即 $L\le\min\limits_{L\le i\le R}l_i$。要统计这个东西最简单的方法应该是单调栈，从大到小枚举 $i$，统计其作为**左端点**时的答案。保持单调栈内只包含使得 $l_j<i$ 的所有 $j$，对于所有 $l_j\ge i$ 的 $j$ 都是合法的，应当计入答案。但 $j$ 合法不一定代表 $i$ 能真正地作为左端点，只有 $l_i=i$ 的 $i$ 才能作为左端点，并把刚才统计的答案算入总答案。具体实现不难，可以参考代码。

现在的问题是求 $l$ 数组。其实这是容易的，先对所有 $a_i$ 分解质因数，对每一个质数维护其出现的位置。如果遇到 `*` 就把当前位置加入 $a_i$ 所有质因数的集合，如果遇到 `/` 就统计 $a_i$ 的所有质因数最后一次出现位置的最小值。考虑这样做的复杂度，显然时间和空间都不超过 $O(n\log n)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN=2e6+5;
int n,a[MAXN],l[MAXN],mp[MAXN];
string s;
bool isp[MAXN];
vector<int>pri;
vector<int>pos[MAXN];
long long ans;
pair<int,int>stk[MAXN];
int top;

void prime(){
	for(int i=2;i<MAXN;i++){
		if(!isp[i]) pri.emplace_back(i),mp[i]=i;
		for(long long j:pri){
			if(i*j>=MAXN) break;
			isp[i*j]=1;
			mp[i*j]=j;
			if(i%j==0) break;
		}
	}
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n;
	prime();
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		l[i]=i;
		if(s[i]=='*'){
			int now=a[i];
			while(now>1){
				pos[mp[now]].emplace_back(i);
				now/=mp[now];
			}
		}else{
			int now=a[i];
			while(now>1){
				if(pos[mp[now]].empty()){
					l[i]=-1;
					break;
				}
				l[i]=min(l[i],pos[mp[now]].back());
				pos[mp[now]].pop_back();
				now/=mp[now];
			}
		}
	}
    for(int i=n;i;i--){
    	long long res=1;
    	while(top&&l[stk[top].first]>=l[i]) res+=stk[top--].second;
    	if(l[i]==i) ans+=res;
    	stk[++top]={i,res};
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Engulf (赞：0)

*2600 评蓝是不是低了。

对每个数分解质因数，质因数直接互不影响，一个一个考虑。

现在考虑质因数 $q$，设 $a_i$ 有 $k$ 个 $q$，如果 $b_i = \tt{*}$，那么设 $v_i = +k$，如果 $b_i = \tt{/}$，$v_i = -k$，那么一个合法的区间 $[l, r]$ 一定满足任意前缀和都 $\ge 0$，即 $\forall r' \in [l, r],\sum\limits_{i = l}^{r'} v_i \ge 0$。

不可能每个 $q$ 都管所有 $n$ 个数的，只把要用的存下来。这个数组记作 $w$ 吧。

设 $s_i = \sum\limits_{j = 1}^i v_j$（前缀和，这个 $j$ 是 $w$ 中的下标，这些东西容易搞乱，仔细区分），$p_j$ 表示第 $j$ 个含有 $q$ 的数在原数组中的位置。

对于一个 $l \in [1, n]$ 来说，合法的 $r$ 一定是从 $l$ 开始连续的一段，因为若 $[l, r]$ 非法，$[l, r + 1]$ 也是非法。

所以考虑枚举 $w$ 中的下标 $l$，找到 $l$ 右边第一个 $r$ 使得 $s_r < s_{l - 1}$，即，$\sum\limits_{i = l}^rv_i < 0$，那么分类讨论一下：
- $v_l < 0$，一开始就结束了。那么 $[p_{l - 1} + 1, p_l]$ 的合法右端点设为 $p_l - 1$，这样的好处是，对于 $[p_{l - 1} + 1, p_l)$ 的数来说，它们原本没有 $q$ 这个质因子，到 $p_l$ 要除去一个就非法了。对于 $p_l$，计算答案时会使区间长度为 $0$，不影响答案。
- 存在这样的 $r$，那么 $[p_{l - 1} + 1, p_l]$ 的最大合法右端点就是 $p_r - 1$。
- 不存在这样的 $r$，那么 $[p_{l - 1} + 1, p_l]$ 的最大合法右端点就是 $n$。

对于每个 $q$ 我们都这么做，那么 $i \in [1, n]$ 的最大合法右端点就是每个 $q$ 在 $i$ 这个位置合法右端点的最小值。

设算出的每个 $i \in [1, n]$ 的合法右端点是 $t_i$，答案就是 $\sum\limits_{i = 1}^n t_i - i + 1$。

剩下的就是实现部分了，这个部分要提一下。
- 分解质因数可以先线性筛筛出所有质数去分解。
- 找 $l$ 右边第一个 $r$ 使得 $s_r < s_{l - 1}$ 可以单调栈维护，倒着做。
- 最后需要一个区间取 $\min$ 的数据结构，使用线段树加标记永久化。

时间复杂度 $O(n\log n + n\sqrt a_i)$。实际上跑不满。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e6 + 5;

int n;
int a[N];
int b[N];

int primes[N], cnt;
bool st[N];

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] * i <= n; j++) {
            st[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

vector<pii> v[N];

void decompose(int idx, int n) {
    for (int i = 0; i < cnt && primes[i] * primes[i] <= n; i++) {
        if (n % primes[i]) continue;
        int c = 0;
        while (n % primes[i] == 0) {
            c++;
            n /= primes[i];
        }
        v[primes[i]].emplace_back(idx, c * b[idx]);
    }
    if (n > 1) v[n].emplace_back(idx, b[idx]);
}

int pre[N];

int mn[N << 2];

void build(int p, int l, int r) {
    mn[p] = n;
    if (l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void update(int p, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) {
        mn[p] = min(mn[p], v);
        return;
    }
    int mid = l + r >> 1;
    if (L <= mid) update(p << 1, l, mid, L, R, v);
    if (mid < R) update(p << 1 | 1, mid + 1, r, L, R, v);
}
int query(int p, int l, int r, int x) {
    if (l == r) return mn[p];
    int mid = l + r >> 1;
    return min(mn[p], x <= mid ? query(p << 1, l, mid, x) : query(p << 1 | 1, mid + 1, r, x));
}

int res[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve(N - 1);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        char op; cin >> op;
        b[i] = op == '*' ? 1 : -1;
    }

    for (int i = 1; i <= n; i++) decompose(i, a[i]);

    build(1, 1, n);

    for (int i = 2; i < N; i++) {
        if (!v[i].size()) continue;

        // debug("%d: ", i);
        // for (auto [x, y]: v[i])
        //     debug("(%d, %d) ", x, y);
        // debug("\n");

        pre[0] = v[i][0].second;
        for (int j = 1; j < v[i].size(); j++)
            pre[j] = pre[j - 1] + v[i][j].second;

        // debug("for primes divisor %d: ", i);
        // for (int j = 0; j < v[i].size(); j++)
        //     debug("%d ", pre[j]);
        // debug("\n");

        vector<int> stk;
        for (int j = v[i].size() - 1; ~j; j--) {
            while (stk.size() && pre[stk.back()] >= (!j ? 0 : pre[j - 1])) stk.pop_back();

            if (v[i][j].second < 0)
                update(1, 1, n, !j ? 1 : v[i][j - 1].first + 1, v[i][j].first, v[i][j].first - 1);
            else {
                if (stk.size())
                    update(1, 1, n, !j ? 1 : v[i][j - 1].first + 1, v[i][j].first, v[i][stk.back()].first - 1);
                else
                    update(1, 1, n, !j ? 1 : v[i][j - 1].first + 1, v[i][j].first, n);
            }

            stk.emplace_back(j);
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += query(1, 1, n, i) - i + 1;

    cout << ans << "\n";

    return 0;
}
```

---

