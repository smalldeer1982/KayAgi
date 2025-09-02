# Segment Tree

## 题目描述

As the name of the task implies, you are asked to do some work with segments and trees.

Recall that a tree is a connected undirected graph such that there is exactly one simple path between every pair of its vertices.

You are given $ n $ segments $ [l_1, r_1], [l_2, r_2], \dots, [l_n, r_n] $ , $ l_i < r_i $ for every $ i $ . It is guaranteed that all segments' endpoints are integers, and all endpoints are unique — there is no pair of segments such that they start in the same point, end in the same point or one starts in the same point the other one ends.

Let's generate a graph with $ n $ vertices from these segments. Vertices $ v $ and $ u $ are connected by an edge if and only if segments $ [l_v, r_v] $ and $ [l_u, r_u] $ intersect and neither of it lies fully inside the other one.

For example, pairs $ ([1, 3], [2, 4]) $ and $ ([5, 10], [3, 7]) $ will induce the edges but pairs $ ([1, 2], [3, 4]) $ and $ ([5, 7], [3, 10]) $ will not.

Determine if the resulting graph is a tree or not.

## 说明/提示

The graph corresponding to the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278D/c6090785de6d8b04e9165be7d77b2baf8a7a274a.png)

The graph corresponding to the second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278D/0f7308cd08a123a72839d915d7fcac16c437d39b.png)

The graph corresponding to the third example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278D/296149228c82b75efc56776e68da72f65a8385a4.png)

## 样例 #1

### 输入

```
6
9 12
2 11
1 3
6 10
5 7
4 8
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
1 3
2 4
5 9
6 8
7 10
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
5 8
3 6
2 9
7 10
1 4
```

### 输出

```
NO
```

# 题解

## 作者：xfrvq (赞：7)

![](https://img-blog.csdnimg.cn/bb696b40a0d34202874dc03f68607e44.png)

让我们考虑两条线段 $[l_i,r_i],[l_j,r_j]$，他们在树上怎样才会有连边？

+ $l_i\lt l_j$
+ $l_j\le r_i\le r_j$

我们对这个东西做二维数点，可以算出树上有几条边，如果不是 $n-1$ 就免谈。

然后这时可以套上二维数点的代码，使用 `set` 代替值域树状数组，可以找到每一条边。

并查集连起来，判连通性。

TLE 96 就开 `long long`，因为 #96 会使得你的所有边数加起来 `int` 溢出后等于 $n-1$（我真的很惊讶）。

```cpp
const int N = 5e5 + 5;
const int M = N << 1;
 
int n,sl[N],sr[N],a[M],fi,ls,fa[N];
vector<pair<int,int>> P[M],Q[M];
gragh G[N];
set<pair<int,int>> s,t;
 
int fnd(int x){ return x == fa[x] ? x : fa[x] = fnd(fa[x]); }
 
struct BIT{
	int T[M];
	
	void add(int p,int x){
		for(;p <= ls;p += p & -p) T[p] += x;
	}
	
	int qry(int l,int r){
		int s = 0; --l;
		for(;r;r -= r & -r) s += T[r];
		for(;l;l -= l & -l) s -= T[l];
		return s;
	}
} t1,t2;
 
bool solve(){
	fi = M,ls = -M;
	int sum = 0;
	rep(i,1,n) chkmin(fi,sl[i]),chkmax(ls,sr[i]);
	rep(i,1,n) P[sl[i]].pb(sr[i],i);
	rep(x,fi,ls){
		for(auto[y,i] : P[x]) sum += t1.qry(x,y);
		for(auto[y,i] : P[x]) t1.add(y,1);
	}
	if(sum != n - 1) return false;
	rep(i,1,n) fa[i] = i;
	rep(x,fi,ls){
		for(auto[y,i] : P[x]){
			auto p = s.lower_bound({x,0}),q = s.lower_bound({y + 1,0});
			if(p == s.end()) continue;
			for(auto j = p;j != q;++j) fa[fnd(i)] = fnd(j->second);
		}
		for(auto[y,i] : P[x]) s.emplace(y,i);
	}
	rep(i,2,n) if(fnd(i) != fnd(1)) return false;
	return true;
}
 
signed main(){
	read(n);
	rep(i,1,n) read(sl[i],sr[i]);
	print(n == 1 || solve() ? "YES" : "NO");
	return 0;
}
```

---

## 作者：caidzh (赞：5)

扫描线+并查集判一下树就好

边数超过点数-1就退出
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<set>
#define db double
#define INF 2147483647
#define LLINF 9223372036854775807
#define LL long long
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=500010;
int n,cnt,fa[maxn],tot,flag,L[maxn],R[maxn],map[maxn<<1];
struct Node{int op,pos,id;}A[maxn<<1];
set<int>S;set<int>::iterator it;
bool cmp(Node x,Node y){return x.pos<y.pos;}
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
int main()
{
	n=read();
	for(int i=1;i<=n;i++){
		int l=read(),r=read();R[i]=r;
		A[++cnt].op=1;A[cnt].pos=l;A[cnt].id=i;
		A[++cnt].op=0;A[cnt].pos=r;A[cnt].id=i;map[l]=i;map[r]=i;
	}sort(A+1,A+cnt+1,cmp);for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=cnt;i++){
		if(A[i].op==1){
			for(set<int>::iterator it=S.begin();it!=S.end()&&*it<=R[A[i].id];it++){
				tot++;if(tot>=n)break;
				int u=getfa(A[i].id),v=getfa(map[*it]);if(u==v)flag=1;else fa[u]=v;
			}S.insert(R[A[i].id]);
		}
		if(A[i].op==0){it=S.find(A[i].pos);S.erase(it);}
	}if(tot<n-1||tot>n-1)cout<<"NO";
	else{if(flag)cout<<"NO";else cout<<"YES";}return 0;
}
```


---

## 作者：_edge_ (赞：2)

没有人来发题解么？

那我来说一下我的做法，首先考虑当前这个东西，要构成一颗树，显然只能有 $n-1$ 条边。

如果你是暴力连的话是 $O(n^2)$ 的时间复杂度，但实际上只需要连出 $n$ 条合法的边之后就可以直接判掉它是无解的。

利用这个非常有用的性质，问题就转化成了，给定几个区间，求出合法的区间有交且区间不包含。

考虑对于左端点排个序，这个可以保证它的左端点都是上升的，然后再把右端点塞到一个 set 里面，因为保证了左端点都是上升的，所以只要保证左端点小于前面的区间的右端点即可，这个东西可以直接 lower_bound 二分查找。

当然，如果有一个区间是包含的，这意味着后面的区间都要被包含，显然是具有单调性的。

最后的最后，注意判断它这个图是否联通，因为可能存在多个环的情况。

时间复杂度 $O(n \log n)$。

另外，难度 $2100$ 是不是有点虚高？

```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
const int INF=5e5+5;
struct _node_data{
	int l,r;
}aa[INF];
int n;
struct _set{
	int v,id;
	bool operator < (const _set &x) const {
		return x.v>v;	
	}
};
multiset <_set> s;
bool cmp(_node_data xx,_node_data yy) {
	return xx.l<yy.l;
}
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int head[INF],tot,vis[INF];
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ;
}
void DFS(int x) {
	if (vis[x]) return ;
	vis[x]=1;
//	cout<<x<<" end\n";
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		DFS(v);
	}
	return ;
}
int check() {
	DFS(1);
	for (int i=1;i<=n;i++)
		if (!vis[i]) return false;
	return true;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>aa[i].l>>aa[i].r; 
	sort(aa+1,aa+1+n,cmp);
	int cnt=0;
	s.insert((_set){aa[1].r,1});
	for (int i=2;i<=n;i++) {
		set<_set>::iterator it=s.lower_bound((_set){aa[i].l,-1});
		for (;it!=s.end();it++) {
			if (it->v>=aa[i].r) break;
			cnt++;
//			cout<<i<<" "<<(it->id)<<" over\n";
			if (cnt==n) {
				cout<<"NO\n";
				return 0;
			}
			
			add_edge(i,it->id);
			add_edge(it->id,i);
		}
		s.insert((_set){aa[i].r,i });
	}
//	cout<<cnt<</"\n";
	if (cnt!=n-1) {
		cout<<"NO\n";
		return 0;
	}
	if (!check()) {
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	return 0;
}
```


---

