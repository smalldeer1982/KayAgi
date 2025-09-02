# A-Z Graph

## 题目描述

You are given a directed graph consisting of $ n $ vertices. Each directed edge (or arc) labeled with a single character. Initially, the graph is empty.

You should process $ m $ queries with it. Each query is one of three types:

- " $ + $ $ u $ $ v $ $ c $ " — add arc from $ u $ to $ v $ with label $ c $ . It's guaranteed that there is no arc $ (u, v) $ in the graph at this moment;
- " $ - $ $ u $ $ v $ " — erase arc from $ u $ to $ v $ . It's guaranteed that the graph contains arc $ (u, v) $ at this moment;
- " $ ? $ $ k $ " — find the sequence of $ k $ vertices $ v_1, v_2, \dots, v_k $ such that there exist both routes $ v_1 \to v_2 \to \dots \to v_k $ and $ v_k \to v_{k - 1} \to \dots \to v_1 $ and if you write down characters along both routes you'll get the same string. You can visit the same vertices any number of times.

## 说明/提示

In the first query of the third type $ k = 3 $ , we can, for example, choose a sequence $ [1, 2, 3] $ , since $ 1 \xrightarrow{\text{a}} 2 \xrightarrow{\text{b}} 3 $ and $ 3 \xrightarrow{\text{a}} 2 \xrightarrow{\text{b}} 1 $ .

In the second query of the third type $ k = 2 $ , and we can't find sequence $ p_1, p_2 $ such that arcs $ (p_1, p_2) $ and $ (p_2, p_1) $ have the same characters.

In the third query of the third type, we can, for example, choose a sequence $ [1, 2, 3, 2, 1] $ , where $ 1 \xrightarrow{\text{a}} 2 \xrightarrow{\text{b}} 3 \xrightarrow{\text{d}} 2 \xrightarrow{\text{c}} 1 $ .

## 样例 #1

### 输入

```
3 11
+ 1 2 a
+ 2 3 b
+ 3 2 a
+ 2 1 b
? 3
? 2
- 2 1
- 3 2
+ 2 1 c
+ 3 2 d
? 5```

### 输出

```
YES
NO
YES```

# 题解

## 作者：Warriors_Cat (赞：2)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1494E) & [CF 题面传送门](http://codeforces.com/problemset/problem/1494/E)。

题意：

- 给 $n$ 个点和 $m$ 次操作
- 每次操作要么加一条有类型的边，要么删去一条边，要么查询是否存在 $k$ 个点（可重复）满足连接这 $k$ 个点的路径上所有边都是双向的，且所写下的字符串是回文的。
- $n, m \le 2\times 10^5$。

第一次独立做出一道难度 *2400 的题，故写题解记之。

~~不得不说这题真的不难（~~

---

### $Solution:$

在草稿纸上手玩一下就会发现，当 $k$ 是奇数时，只要有一对点对 $(u, v)$ 满足存在边 $(u, v)$ 和 $(v, u)$ 就可以，否则不行。

证明很简单，如果存在这样的点对 $(u, v)$ 的话，直接 $u\rightarrow v \rightarrow u \rightarrow v \rightarrow\cdots\rightarrow u$ 这样交替的走即可，很显然其所写下的字符串是回文的。否则都没有一条双向边，显然就不存在路径。

那么，类比 $k$ 是奇数的时候，当 $k$ 是偶数时，我们也想要像奇数时那样构造，即 $u \rightarrow v \rightarrow u \rightarrow v\rightarrow\cdots\rightarrow u\rightarrow v$ 这样走。此时我们会发现，当且仅当边 $(u, v)$ 和边 $(v, u)$ 时同一个类型的边时满足条件，否则不满足条件。

那么，我们就需要存储点对 $(u, v)$ 间是否存在一条边，以及如果存在的话这样的边是什么类型，这个可以直接用一个 `map` 搞定。然后我们在加边和删边的时候维护有多少组双向边和同类双向边，查询答案的时候判断一下即可。

over，时间复杂度为 $O(m\log n)$。

---

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = x; i >= y; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define mpr make_pair
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 200010;
map < pair <int, int> , int> g; int a, b;
int n, m, x, y; char opt[N], s[N];
inline void mian(){
	n = read(); m = read();
	while(m--){
		scanf("%s", opt); x = read();
		if(opt[0] == '+'){
			y = read(); scanf("%s", s);
			g[mpr(x, y)] = s[0];
			if(g.find(mpr(y, x)) != g.end()){
				++a;
				if(g[mpr(x, y)] == g[mpr(y, x)]) ++b;
			}
		}
		if(opt[0] == '-'){
			y = read();
			if(g.find(mpr(y, x)) != g.end()){
				--a;
				if(g[mpr(x, y)] == g[mpr(y, x)]) --b;
			}
			g.erase(mpr(x, y));
		}
		if(opt[0] == '?'){
			if(x & 1) puts(a ? "YES" : "NO");
			else puts(b ? "YES" : "NO");
		}
	}
}
int main(){ int qwq = 1; while(qwq--) mian(); return 0; }
```


---

## 作者：strcmp (赞：1)

**题目大意：** 有向图上动态加边删边，和询问是否存在起点到终点长度为 $k - 1$ 的路径，和终点到起点长度为 $k - 1$ 的路径，满足经过的边连起来的字符串是相同的。

------------

这题唯一的难点在于明白询问路径不是简单路径，是可以重复的。

那么我们考虑 $k$ 为奇数时，如果同时存在 $(u,\,v)$ 和 $(v,\,u)$，则走 $u \to v \to u \to v \to \dots \to u$，反着走显然也可以做到回文。那么如果存在输出 `YES` 即可。

考虑 $k$ 为偶数，则走的路径形如 $u \to v \to u \to \dots \to v$，反向的路径形如 $v \to u \to v \to \dots \to u$，那么只需要在前一个条件的基础上，判断 $(u,\,v)$ 和 $(v,\,u)$ 的代表字符是否相等即可。

用 `map` 容易做到 $\Theta(m \log n)$。

```cpp
#include <bits/stdc++.h>
#define fr first
#define sc second
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
const int maxn = 4e5 + 10;
map<pii, int>s; int n, m; ll a = 0, b = 0;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		char c, d;
		scanf(" %c", &c);
		if (c == '+') {
			int u, v;
			scanf("%d%d %c", &u, &v, &c);
			s[{u, v}] = c - 'a' + 1;
			if (s.count({ v, u })) {
				++a;
				if (s[{ u, v }] == s[{ v, u }]) ++b;
			}
		}
		else if (c == '-') {
			int u, v;
			scanf("%d%d", &u, &v);
			if (s.count({ v, u })) {
				--a;
				if (s[{ u, v }] == s[{ v, u }]) --b;
			}
			s.erase({ u, v });
		}
		else {
			int k;
			scanf("%d", &k);
			if (k & 1) puts(a ? "YES" : "NO");
			else puts(b ? "YES" : "NO");
		}
	}
	return 0;
}
```

---

## 作者：tai_chi (赞：0)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18564798) 中阅读。

#### 题意

给一个有向图，边权是字母，有三种操作：

- 添加边 $(u,v,c)$；
- 删除边 $(u,v)$；
- 询问是否存在一个长度为 $k$ 的非简单路径满足 $v_1 \leftarrow v_k$ 的路径与 $v_k \leftarrow v_1$ 的路径边权序列相同。

#### 分析

手玩题。顶点数量为偶数的情况容易发现只要有一个二元环就行了。

$$
1 \overset{\texttt{a}}{\underset{\texttt{b}}{\rightleftarrows}} 2
$$

容易发现路径 $[1,2,1]$ 满足题设，同样 $[1,2,1,2,1],[1,2,1,2,1,2,1]$ 也都满足题设，这启示我们将所有奇数的询问归位一类。

必要性也很显然，任意满足题设的路径必然至少包含一个二元环。

顶点数量为奇数的情况是类似的，结论是存在一个二元环且环上的相反边字母相同。

判二元环存在性只需要 `map` 等容器维护所有边就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef pair<int,int> pii;
typedef unsigned long long ull;
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
int n,m;
map<pii,char> mp;
int cnt1,cnt2;
signed main()
{
	IOS;
	cin>>n>>m;
	while(m--)
	{
		char op; cin>>op;
		if(op=='+')
		{
			int x,y; char c;
			cin>>x>>y>>c;
			mp[{x,y}]=c;
			if(mp[{y,x}]) cnt1++;
			if(mp[{y,x}]==c) cnt2++;
		}
		else if(op=='-')
		{
			int x,y; cin>>x>>y;
			if(mp[{x,y}]&&mp[{y,x}]) cnt1--;
			if(mp[{x,y}]==mp[{y,x}]) cnt2--;
			mp.erase({x,y});
		}
		else
		{
			int k; cin>>k;
			if(k&1) cout<<((cnt1!=0)?"YES":"NO")<<"\n";
			else cout<<((cnt2!=0)?"YES":"NO")<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

比较简单的诈骗题。~~不开玩笑这题真配不上 *2400。~~

首先转化要求，其实就是要找一条路径满足走过去和走回来的字符串写出来是一样的，那么可以想到起点 $v_1$ 起码要有一个点 $x$ 满足同时存在边 $v_1\to x$ 和 $x\to v_1$，也就是一个二元环。那么整个图也必须至少有一个二元环，否则一定输出 `NO`。题目又特意加粗告诉我们可以走一个点多次，所以我们可以想到进行一个很离谱的操作：在一个二元环上来回走。

首先很明显，如果存在一个边权相同的二元环，那么无论要走多长的路径都可以通过一直在这个二元环上反复走做到。

否则，如果存在一个边权不同的二元环，手画一下就能发现路径长度为奇数时是一定可以做到的，偶数的时候一定做不到。

很容易证明如果此时偶数长度做不到，那么其他情况偶数也做不到：偶数个点的路径意味着有奇数条边，如果可以做到满足题目要求那么位于路径正中间的那条边一定在来回当中是同边权，并且两端是相同的点所以构成二元环。但是此时我们已经排除了存在一个边权相同二元环的情况，所以原命题得证。

不要忘记没有二元环需要输出 `NO`。

那么我们就可以处理询问了。对于加边和删边，我们只需要根据它的反边是否存在以及反边的边权实时更新边权相同二元环数量和边权不同二元环数量就行了。用 `map` 可以轻易实现。

[AC 记录](https://www.luogu.com.cn/record/128561928)

---

## 作者：JasonL (赞：0)

## CF1494E A-Z Graph

[题目传送门](https://www.luogu.com.cn/problem/CF1494E)

#### 题目解析


入手题目，观察性质。

注意到对于满足要求的点序列 $\{v_i\}$ ，弧 $v_1\rightarrow v_2$ 与弧 $v_2\rightarrow v_1$ 均存在。

如果要求的 $k$ 为奇数，构造合法序列 $u\rightarrow v \rightarrow u\rightarrow \dots \rightarrow u$ 。注意到此时倒过来的序列也是相同的序列，此时只需要满足图上存在两个点之间互相有边即可。

如果要求的 $k$ 为偶数，令 $x=\frac{k}{2}$ 。注意到对于 $v_{x}$ 与 $v_{x+1}$ ，有 $v_{x}\rightarrow v_{x+1}$ 与 $v_{x+1}\rightarrow v_{x}$ 的标号相同。我们像上面一样构造 $u\rightarrow v \rightarrow \dots \rightarrow v$ ，那么需要满足 $u\rightarrow v,v\rightarrow u$ 的标号相同。

因而我们需要考虑两种情况：图中是否存在两点互相有边，以及互相有边的两点边的标号是否相同。这里我使用了 $\mathrm{map} $ 来查询。时间复杂度 $ \mathrm{O(m\log n) } $ 。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const int maxn=201010;
int n,m;
int cnt0,cnt1; //互相有边的点对数，互相有边且边标号相同的点对数
string s;
map <int,int> mp[maxn]; //记录该点向外连的边对应的标号
inline int read(){
	int res=0;
	char ch=getchar(),ch1=ch;
	while(!isdigit(ch))ch1=ch,ch=getchar();
	while(isdigit(ch))res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return ch1=='-'?-res:res;
}
int main(){
	n=read();m=read();
	for(int i=0,u,v,op;i<m;++i){
		cin>>s;
		if(s[0]=='?'){
			u=read();
			if((u-1)&1)puts(cnt1?"YES":"NO");
			else puts(cnt0?"YES":"NO");
		}
		else if(s[0]=='+'){
			u=read();v=read();
			cin>>s;
			mp[u][v]=s[0]-'a'+1;
            		//检查是否存在v->u
			if(mp[v][u]){
				++cnt0;
           			//检查是否v->u同标号
				if(mp[v][u]==mp[u][v])
					++cnt1;
			}
		}
		else{
			u=read();v=read();
			if(mp[v][u]){
				--cnt0;
				if(mp[v][u]==mp[u][v])
					--cnt1;
			}
			mp[u][v]=0;
		}
	}
	return 0;
}
```




---

