# 図書館 (Library)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2018/tasks/joisc2018_k

C++ を使用する場合は問題文の指示に従ってください．

このジャッジは C++ 以外にも対応しています．C++ 以外の言語を使用する場合，ジャッジとのやり取りには関数ではなく標準入出力を使用します．以下の指示に従ってください．

#### C++ 以外の言語の実装の詳細

まず，整数 $ N $ が標準入力により与えられます．

Query 関数を呼び出したい場合には，標準出力に `Query` と出力して改行したのち， $ N $ 個の整数を空白区切りで出力して改行してください．flush を忘れないでください．

Answer 関数を呼び出したい場合には，標準出力に `Answer` と出力して改行したのち， $ N $ 個の整数を空白区切りで出力して改行してください．flush を忘れないでください．

不正解 $ 1 $ は TLE ，不正解 $ 2 $ は WA ，不正解 $ 3 $ は WA ，不正解 $ 4 $ は TLE ，不正解 $ 5 $ は WA ，不正解 $ 6 $ は WA ，不正解 $ 8 $ は WA と判定されます．Answer 関数が呼び出されるとジャッジは終了するため， $ N $ 個の整数を出力したのちに余計なものを出力しても判定には影響しません．

# 题解

## 作者：Purslane (赞：0)

# Solution

考虑找出每个数在排列中相邻的数。

有一个很朴素的想法：考虑集合 $S$，和另外一个不在 $S$ 中的元素 $x$。查询 $S$ 和 $S \cup \{x\}$，设结果为 $cnt1$ 和 $cnt2$。那么 $x$ 在 $S$ 中有 $cnt1+1-cnt2$ 个相邻元素。

不妨只找相邻的比他大的数。那么可能有 $0/1/2$ 个相邻。

那你想的就是直接二分，找到 $0$、$1$ 和 $2$ 的分界点，这样就可以找到和哪些数相邻。

但是你发现，二分中判断判断一次要消耗 $2$ 次询问，因此最后操作数是 $4 n \log_2 n$ 左右的，无法通过。

这时候使用整体二分即可，这样二分的过程中询问 $S$ 可以省下来。

总的询问次数变为：$O(n) + 2 n \log_2 n$，可以通过（$O(n)$ 是因为，你再整体二分第一层要询问 $1$ 次，第二层 $2$ 次，第三层 $4$ 次，……，最下面一层 $O(n)$ 次，求和还是 $O(n)$）

特判 $n=1$ 的情况。

```cpp
#include<bits/stdc++.h>
#include "library.h"
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int n,suf[MAXN];
vector<int> G[MAXN];
void solve(int l,int r,vector<pair<int,int>> vc) {
    if(l>r) return ;
    vector<pair<int,int>> legal;
    for(auto pr:vc) if(pr.second) legal.push_back(pr);
    if(l==r) {
        for(auto pr:legal) G[l].push_back(pr.first),G[pr.first].push_back(l);
        return ;
    }
    int mid=l+r>>1,cnt;
    vector<int> qr(n);
    ffor(i,mid+1,r) qr[i-1]=1;
    cnt=Query(qr);
    vector<pair<int,int>> L,R;
    for(auto pr:legal) {
        if(pr.first>=mid+1) R.push_back(pr);
        else {
            auto QR=qr;
            QR[pr.first-1]=1;
            int x=Query(QR);
            R.push_back({pr.first,cnt+1-x});
            L.push_back({pr.first,pr.second-(cnt+1-x)});
        }
    }
    solve(l,mid,L),solve(mid+1,r,R);
    return ;
}
vector<int> ans;
void output(int u,int lst) {
    ans.push_back(u);
    int sum=0;
    for(auto v:G[u]) sum+=v;
    if(sum!=lst) output(sum-lst,u);
    return ;
}
void Solve(int N) {
    n=N;
    if(n==1) return Answer({1}),void();
    vector<int> qr(n);
    ffor(i,1,n) qr[i-1]=1;
    ffor(i,1,n-1) suf[i]=Query(qr),qr[i-1]=0;
    suf[n]=1;
    vector<pair<int,int>> vc;
    ffor(i,1,n-1) vc.push_back({i,suf[i+1]+1-suf[i]});
    solve(1,n,vc);
    ffor(i,1,n) if(G[i].size()==1) return output(i,0),Answer(ans),void();
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2018K 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2018_k)

**题目大意**

> 交互器有一个 $1\sim n$ 的排列 $p$，你每次可以询问 $S$ 里的元素在 $p$ 上构成了几个连续段。
>
> 在 $20000$ 次询问内还原出排列。
>
> 数据范围：$n\le 1000$。

**思路分析**

考虑增量法，注意到询问 $S$ 和 $S\cup \{x\}$ 后连续段数的变化情况。

先用 $2n$ 次询问求出排列的一个端点。

然后动态维护已知前缀 $P$，对于未确定集合 $Q$，二分成两个集合 $(X,Q\text{\\}X)$，询问 $X$ 和 $P\cup X$ 即可知道 $X$ 里有没有前缀的下一个元素，不断操作即可。

交互次数 $2(n+n\log n)$，但事实上后面的 $\log |Q|$ 取不到 $10$，因此可以通过。

时间复杂度 $\mathcal O(n^2\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#include "library.h"
using namespace std;
void Solve(int N) {
	if(N==1) { Answer({1}); return ; }
	int st=-1;
	vector <int> rest;
	auto Adj=[&](int x,vector <int> V) -> int {
		vector <int> q(N,0);
		for(int v:V) q[v]=1;
		int d=Query(q);
		q[x]=1;
		return d-Query(q)+1;
	};
	for(int i=0;i<N;++i) {
		vector <int> V;
		for(int j=0;j<N;++j) if(i!=j) V.push_back(j);
		int t=Adj(i,V);
		if(t==1) { st=i,rest=V; break; }
	}
	vector <int> ans{st};
	while((int)ans.size()<N) {
		auto Ne=[&](int x,vector <int> V) -> int {
			while(V.size()>1) {
				int mid=V.size()>>1;
				vector <int> V0(V.begin(),V.begin()+mid),V1(V.begin()+mid,V.end());
				V=Adj(x,V0)?V0:V1;
			}
			return V[0];
		};
		int u=ans.back(),v=Ne(u,rest);
		rest.erase(lower_bound(rest.begin(),rest.end(),v));
		ans.push_back(v);
	}
	for(int &u:ans) ++u;
	Answer(ans);
}
```



---

## 作者：Rosaya (赞：0)

### 题意

你需要实现函数 ```void Solve(int N)``` 来还原一个排列。

你可以使用 ```int Query(const std::vector<int>& M)``` 操作获取 $M$ 中所有点的导出子图的连通块数量。

你可以最多进行 $20000$ 次 ```Query``` 操作来还原整个序列。

### 思路

比较简单的题，对于 $i$ 来说，我们只需要求出与 $i$ 相连的所有点即可。

具体的，我们希望定位 $i<j$ 的边 $(i,j)$。

考虑分治，记 $f(i,l,r,k)$ 表示 $i$ 与 $[l,r]$ 中的 $k$ 个点相邻，其中 $k \in [0,2],i \le l \le r$。

若 $k=0$，则没有相邻点，可以直接退出。

若 $l=r$，则存在边 $(i,l)$。

否则记 $mid= \left\lfloor \dfrac{l+r}{2} \right\rfloor,S=[l,mid]$，先询问 $S$ 的连通块数量，再询问 $S \cup \{i\}$ 的连通块数量，就可以计算出 $i$ 与 $[l,mid]$ 中有几个点相邻，递归处理即可。

询问数量 $O(n \log n)$，常数比较小。

### 代码

```cpp
#include<bits/stdc++.h>
#include"library.h"
using namespace std;

int n;
vector<int> que,res,adj[1005];

inline void dfs(int u,int fa)
{
	res.push_back(u);

	for(int i=0;i<adj[u].size();i++)
	{
		int v=adj[u][i];

		if(v==fa)
			continue;

		dfs(v,u);
	}
}

inline void getstring(int l,int r)
{
	que.clear();

	for(int i=1;i<=n;i++)
	{
		if(l<=i&&i<=r)
			que.push_back(1);
		else
			que.push_back(0);
	}
}

inline void getans(int pos,int l,int r,int cnt)
{
	if(!cnt)
		return;

	if(l==r)
	{
		adj[pos].push_back(l);
		adj[l].push_back(pos);
		return;
	}

	int mid=(l+r)>>1;
	getstring(l,mid);
	int k=Query(que);
	que[pos-1]=1;
	int sum=k+1-Query(que);
	getans(pos,l,mid,sum);
	getans(pos,mid+1,r,cnt-sum);
}

inline void sol(int pos)
{
	getstring(pos+1,n);
	int k=Query(que);
	que[pos-1]=1;
	int sum=k+1-Query(que);
	getans(pos,pos+1,n,sum);
}

void Solve(int N)
{
	n=N;

	for(int i=1;i<n;i++)
		sol(i);

	for(int i=1;i<=n;i++)
	{
		if(adj[i].size()<2)
		{
			dfs(i,0);
			Answer(res);
			return;
		}
	}
}

```

---

