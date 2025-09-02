# Diverse Segments

## 题目描述

给定长度为 $n$ 的序列 $a$，以及 $m$ 个数对 $(l_i,r_i)$。  
你可以进行下列操作至多一次：

- 选择序列 $a$ 的一个子段，并将其中的每个元素的值都改成任意整数。

你需要保证执行完操作之后，对于每个整数 $i(1\leq i\leq m)$，都有 $a[l_i,r_i]$ 中所有元素互不相同。  
你需要最小化操作时选择的子段的长度，并求出这个长度的最小值。  
特别的如果没有必要进行操作，答案为 $0$。

## 样例 #1

### 输入

```
5
7 3
1 1 2 1 3 3 5
1 4
4 5
2 4
5 2
10 1 6 14 1
4 5
2 4
4 5
5 7 5 6
2 2
1 3
2 4
3 3
3 4
7 3
2 2 2 7 8 2 2
4 4
4 4
5 5
1 1
123
1 1```

### 输出

```
2
0
1
0
0```

# 题解

## 作者：lndjy (赞：7)

~~没看懂题解只能自己口胡~~

这种多个区间都要满足不是很好处理，考虑 P6773 的套路，预处理出来 $limit_i$ 表示包含 $i$ 的区间，最前面到哪里，这样就将 $m$ 个区间满足条件转化为对于每个 $i$，$limit_i$ 到 $i$ 之间颜色不能有相同的，同时，**$limit_i$ 是随着 $i$ 单调不下降的。**

不难发现答案合法的一个**必要**条件，就是对于任意 $i$，$a_{[limit_i,i-1]}$ 不能有和 $a_i$ 相同的颜色。而单调不下降这个性质告诉我们，对于 $i$ 的限制，它本身的 $limit$ 的限制是严格不劣于 $limit_j(j>i)$ 对 $i$ 的限制。也就是说，**之前说的必要条件是充要的。**

现在需要满足的条件变为任意 $i$，$a_{[limit_i,i-1]}$ 不能有和 $a_i$ 相同的颜色。这个就很套路了，每个颜色开一个 `vector`，维护它出现的所有位置，然后对于每个 $i$ 求出来 $[l_i,r_i]$ 表示如果 $i$ 没被子段选择，那么 $[l_i,r_i]$ 都需要被子段选择，你需要求最短子段满足所有 $i$ 的限制。

考虑双指针统计答案，每次移动相当于是取消/加入 $i$ 的限制，需要查询的是当前区间是否满足所有限制，线段树维护所有限制的 $l$ 的最小值和 $r$ 的最大值，然后和当前区间比较即可。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<set>
#include<vector>
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=2e5+5;
struct tree
{
	int l,r,minn,maxx;
}t[N*4];
int n,L[N],R[N],a[N],limit[N],m;
void pushup(int k)
{
	t[k].minn=min(t[k*2].minn,t[k*2+1].minn);
	t[k].maxx=max(t[k*2].maxx,t[k*2+1].maxx);
}
void build(int k,int l,int r)
{
	t[k].l=l;t[k].r=r;
	if(l==r)
	{
		t[k].minn=L[l];
		t[k].maxx=R[l];
		return;
	}
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	pushup(k);
}
void change(int k,int x,int v)
{
	if(t[k].l==t[k].r)
	{
		if(v) t[k].minn=n+1,t[k].maxx=0;
		else t[k].minn=L[x],t[k].maxx=R[x];
		return;
	}
	if(x<=t[k*2].r) change(k*2,x,v);
	else change(k*2+1,x,v);
	pushup(k);
}
multiset<int> s;
map<int,int> mp;
int tot;
int getid(int x)
{
	if(!mp[x]) mp[x]=++tot;
	return mp[x];
}
vector<int> v[N],v2[N];
bool check(int l,int r)
{
//	cout<<"chk"<<l<<' '<<r<<" "<<t[1].minn<<" "<<t[1].maxx<<endl; 
	return l<=t[1].minn&&t[1].maxx<=r;
}
void solve()
{
	tot=0;
	mp.clear();
	s.clear();
	n=read();m=read();
	for(int i=1;i<=n;i++)
	v[i].clear(),v2[i].clear();
	for(int i=1;i<=n;i++)
	a[i]=read(),a[i]=getid(a[i]),v2[a[i]].push_back(i);
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		v[x].push_back(x);
		v[y+1].push_back(-x);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<v[i].size();j++)
		if(v[i][j]>0) s.insert(v[i][j]);
		else s.erase(s.find(-v[i][j]));
		if(s.empty()) limit[i]=0,L[i]=n+1,R[i]=0;
		else limit[i]=(*s.begin());
	}
	for(int i=1;i<=n;i++)
	{
		if(limit[i]==0)
		{
//			 cout<<i<<' '<<L[i]<<" "<<R[i]<<endl;
			continue;
		}
		if(limit[i]==i)
		{
			L[i]=n+1;
			R[i]=0;		
		}
		else
		{
			int l=0,r=v2[a[i]].size()-1;
			L[i]=n+1,R[i]=0;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(v2[a[i]][mid]>=limit[i]) L[i]=v2[a[i]][mid],r=mid-1;
				else l=mid+1;
			}
			if(L[i]>=i) L[i]=n+1;
			l=0,r=v2[a[i]].size()-1;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(v2[a[i]][mid]<i) R[i]=v2[a[i]][mid],l=mid+1;
				else r=mid-1;
			}
			if(R[i]<limit[i]) R[i]=0;
		}
//		 cout<<i<<' '<<L[i]<<" "<<R[i]<<endl;
	}
	build(1,1,n);
	int ans=n;
	for(int l=1,r=0;l<=n;l++)
	{
		while(r<n&&!check(l,r)) r++,change(1,r,1);
		if(check(l,r)) ans=min(ans,max(0,r-l+1));
//		 cout<<l<<' '<<r<<endl;
		change(1,l,0);
	}
	cout<<ans<<endl;
}
int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout); 
	int T=read();
	while(T--) solve();
 	return 0;
}

/*
1 5 2
0 5 4 9 4 
1 5
3 4
lgsblgsb
*/
```


---

## 作者：一只绝帆 (赞：4)

不带任何 $\log$ 的做法。

目前洛谷最优解（$2023.8.27$，总时间 `78ms`，第二快是 `342ms`）。

首先发现最终的答案区间具有单调性，即以每个点为左端点的最优解随着左端点右移，右端点单调不左移。

于是联想到能否双指针 + $O(1)$ 判断区间是否合法。

题目的限制我们可以转化成对于每个点，找到覆盖它的最右端点 $R_i$，然后在 $[i+1,R_i]$ 中找到最左边与其相等的位置 $l_i$ 和最右边与其相等的位置 $r_i$。

那么区间合法当且仅当：对于每个点，要么本身被覆盖，要么 $[l_i,r_i]$ 被覆盖。

分讨一下可以发现这个条件是充要的。

于是我们这样判断一个区间的合法性：对于区间内的点，本身已经被覆盖，就不需要管了；对于区间外的点，我们要满足这些点中最小的 $l_i$ 与最大的 $r_i$ 均被覆盖。

所以问题又转化成求前缀/后缀的 $\max/\min$，可以平凡解决。

现在我们要低于 $O(n\log n)$ 的做法，主要需要解决的点有这几个：

1. 离散化（后续找 $l_i$ 与 $r_i$ 要用到）。

2. 找 $R_i$。

3. 找 $l_i,r_i$。


我们挨个解决。

首先发现这个离散化是无序离散化，不需要关注数的大小关系，用一个 `std::unordered_map` 来实现即可。

找 $R_i$ 相当于把给定区间挂在右端点上，从右往左扫，每次对一段区间还没有赋过 $R_i$ 的点把 $R_i$ 赋成本身。

可以用并查集来优化这个过程。

找 $l_i$ 和 $r_i$ 怎么办呢。

$l_i$ 肯定就是 $i$ 之后第一个跟 $a_i$ 相等的位置（前提是在 $R_i$ 内）。

找 $r_i$ 可以从左往右扫，扫到 $i$ 的时候将所有 $R_j=i$ 的 $j$ 的 $r_j$ 确定，这个过程可以动态维护一个 $lst_x$ 表示最后一次出现 $x$ 的位置，那么 $r_j=lst_{a_j}$。

复杂度 $O(m+n\alpha)$。

Code：
```cpp
#include<bits/stdc++.h>
#define UF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Zma(x,y) (x<y)&&(x=y)
#define Zmi(x,y) (x>y)&&(x=y)
using namespace std;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
int read() {
	int s=0,w=0;char ch=gc();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
	return w?-s:s;
} const int N=2e5+5;
int n,m,bnt,pmax[N],pmin[N],smax[N],smin[N],bl[N],R[N],l[N],r[N],start[N],Next[N],v[N],f[N],a[N],lst[N],ans;
unordered_map<int,int> mp;int cnt;
int hsh(int x) {x^=913784335;if(mp.find(x)==mp.end()) return mp[x]=++cnt;return mp[x];}
int find(int x) {return x^f[x]?f[x]=find(f[x]):x;}
void add(int x,int y) {v[++bnt]=y;Next[bnt]=start[x];start[x]=bnt;}
bool check(int l,int r) {return l<=min(pmin[l-1],smin[r+1])&&r>=max(pmax[l-1],smax[r+1]);}
int main() {
	F(T,1,read()) {
		n=read();m=read();cnt=bnt=0;mp.clear();ans=n;pmin[0]=smin[n+1]=n+1;pmax[0]=smax[n+1]=0;
		F(i,1,n) a[i]=hsh(read()),bl[i]=pmin[i]=smin[i]=n+1,f[i]=i,R[i]=l[i]=r[i]=lst[i]=start[i]=pmax[i]=smax[i]=0;
		F(i,1,m) {int l=read(),r=read();Zmi(bl[r],l);}
		UF(i,n,1) for(int j=find(i);j>=bl[i];j=f[j]=find(j-1)) R[j]=i,add(i,j);
		F(i,1,n) {
			i<=R[lst[a[i]]]&&(l[lst[a[i]]]=i);lst[a[i]]=i;
			for(int j=start[i];j;j=Next[j]) r[v[j]]=lst[a[v[j]]],l[v[j]]>r[v[j]]&&(l[v[j]]=r[v[j]]=0);
		} 
		F(i,1,n) {
			pmin[i]=pmin[i-1];pmax[i]=pmax[i-1];
			if(l[i]) Zmi(pmin[i],l[i]),Zma(pmax[i],r[i]);
		} 
		UF(i,n,1) {
			smin[i]=smin[i+1];smax[i]=smax[i+1];
			if(l[i]) Zmi(smin[i],l[i]),Zma(smax[i],r[i]);
		} int r=0;F(l,1,n) {while(!check(l,r)&&r<=n) r++;if(r>n) break;ans=min(ans,max(0,r-l+1));}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：zhanghengrui (赞：3)

显然，对子段进行操作可以视为移除了该子段。

考虑一个子段，维护删掉该子段时，序列剩下部分中会被给定区间覆盖到的相等的对数（无序）。

假设我们已知 $[l, r]$ 时的结果：

- 如果要求 $[l, r + 1]$ 的结果，就是减去 $[1, l)$ 和 $(r + 1, n]$ 中能产生贡献（与 $r + 1$ 相等且至少共同被一个区间覆盖）的位置数

- 如果要求 $[l + 1, r]$ 的结果，就是加上 $[1, l)$ 和 $(r, n]$ 中能产生贡献的位置数

考虑 $\mathit{minL}_{i}, \mathit{maxR}_{i}$ 表示 $i$ 位置最左、最右的能共同被至少一个给定区间覆盖的位置，这两个数组都可以用简单的 前缀/后缀 最大/最小值 求出。

再维护若干个数组按顺序存放某个值出现的所有位置，直接在数组上二分就可以求出有多少个在要求的区间（例如上面的第一种情况，就是 $\Big( [1, l) \cup (r + 1, n] \Big) \cap [\mathit{minL}_{r + 1}, \mathit{maxR}_{r + 1}]$）内。

于是就可以愉快地双指针啦：顺序枚举 $r$，$l$ 能往右动就动，判断是否满足题目条件并更新答案。

---

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

// v 中在 [l, r] 范围内的元素个数
long count(const std::vector<long> &v, long l, long r) {
  return l > r ? 0
               : std::upper_bound(v.begin(), v.end(), r) -
                     std::lower_bound(v.begin(), v.end(), l);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<long> a(n), minL(n, n), maxR(n, -1);
    std::map<long, std::vector<long>> positions;
    for (long i = 0; i < n; ++i) {
      std::cin >> a[i];
      positions[a[i]].push_back(i);
    }
    while (m--) {
      long l, r;
      std::cin >> l >> r;
      --l;
      --r;
      if (l < minL[r])
        minL[r] = l;
      if (r > maxR[l])
        maxR[l] = r;
    }
    for (long i = n - 2; i >= 0; --i)
      minL[i] = std::min(minL[i], minL[i + 1]);
    for (long i = 1; i < n; ++i)
      maxR[i] = std::max(maxR[i], maxR[i - 1]);

    long long s = 0;
    for (const auto &[v, p] : positions) {
      for (const auto &pos : p)
        s += count(p, pos + 1, maxR[pos]);
    }
    if (s == 0) {
      std::cout << "0\n";
      continue;
    }

    long l = 0, answer = n;
    for (long i = 0; i < n; ++i) {
      s -= count(positions[a[i]], minL[i], l - 1) +
           count(positions[a[i]], i + 1, maxR[i]);
      while (l < i && s + count(positions[a[l]], minL[l], l - 1) +
                              count(positions[a[l]], i + 1, maxR[l]) ==
                          0)
        ++l;
      if (s == 0)
        answer = std::min(answer, i - l + 1);
    }
    std::cout << answer << '\n';
  }

  return 0;
}
```

---

## 作者：modfisher (赞：2)

## 思路
让我们把所有相同的数单拉出来，以 $t$ 为例，令 $b_i$ 表示所有 $t$ 的下标集合，即 $a_{b_i}=t$。

考虑枚举一个位置 $b_i$。找出最小的 $j$，满足存在 $k$ 满足 $l_k\le b_j<b_i\le r_k$，即 $[b_j,b_i]$ 被某个给出的区间包含。寻找 $j$ 是容易的。令 $mx_i=\max_{l_k\le i}r_k$，那么 $j$ 应满足 $mx_{b_{j}}\ge b_i$。$mx$ 容易处理。因为 $mx$ 单调递增，所以在枚举 $i$ 时动态移动 $j$ 即可。

那么显然，我们修改的区间必须包含 $b_j,b_{j+1},\dots,b_{i-1}$ 或者 $b_{j+1},b_{j+2},\dots,b_i$，也就是说至少修改掉其中的 $i-j$ 个。换句话说，选择的区间 $[L,R]$ 满足：$L\le b_j$ 且 $R\ge b_{i-1}$，或者 $L\le b_{j+1}$ 且 $R\ge b_i$。这看起来令人摸不着头脑，怎么办呢？

考虑维护 $f_i$ 表示：当 $L=i$ 时，$R$ 的最小值为 $f_i$。于是对上面的 $b_j$ 和 $b_i$ 进行讨论：

- 无论如何都有 $R\ge b_{i-1}$，因此 $f_1,\dots,f_n$ 全局对 $b_{i-1}$ 取 $\max$。

- 当 $L>b_j$ 时，必定有 $R\ge b_i$。因此 $f_{b_j+1},\dots,f_n$ 对 $b_i$ 取 $\max$。

- 当 $L>b_{j+1}$ 时，已经不合法了，令 $f_{b_{j+1}+1},\dots,f_n$ 变为 $+\infty$。

所以只需要支持后缀取 $\max$ 操作即可。容易维护。

对于每一种数都进行如上操作。最后枚举 $L$，答案即为 $\min_{i=1}^nf_i-i+1$。

时间复杂度为 $O(n\log n)$。复杂度瓶颈在于离散化。可以使用较快的哈希表优化至 $O(n)$ 左右。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int n, m;
int a[maxn], a1[maxn];
vector<int> V[maxn];

int mx[maxn], minR[maxn];

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i ++){
			scanf("%d", &a[i]);
			a1[i] = a[i];
		}
		sort(a1 + 1, a1 + n + 1);
		int k = unique(a1 + 1, a1 + n + 1) - a1 - 1;
		for(int i = 1; i <= n; i ++){
			a[i] = lower_bound(a1 + 1, a1 + k + 1, a[i]) - a1;
			V[a[i]].push_back(i);
		}
		for(int i = 1; i <= m; i ++){
			int l, r;
			scanf("%d %d", &l, &r);
			mx[l] = max(mx[l], r);
		}
		for(int i = 1; i <= n; i ++) mx[i] = max(mx[i - 1], mx[i]);
		for(int i = 1; i <= k; i ++){
			int l = 0;
			for(int j = 0; j < V[i].size(); j ++){
				while(l < j && mx[V[i][l]] < V[i][j]) l ++;
				if(l == j || mx[V[i][l]] < V[i][j]) continue;
				int x = V[i][l], y = V[i][j], z = V[i][l + 1], w = V[i][j - 1];
				minR[0] = max(minR[0], w);
				minR[x + 1] = max(minR[x + 1], y);
				minR[z + 1] = n + 1;
			}
		}
		int len = n + 1;
		for(int i = 1; i <= n; i ++){
			minR[i] = max(minR[i], max(minR[i - 1], i - 1));
			if(minR[i] > n) break;
			len = min(len, minR[i] - i + 1);
		}
		printf("%d\n", len);
		for(int i = 0; i <= n; i ++) mx[i] = minR[i] = 0, V[i].clear();
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

模拟赛场切了。

区间的限制在区间上不好直接考虑，我们考虑转变考虑限制的主体，在每个点上考虑限制。

对于点 $i$，记 $L_i$ 表示所有覆盖了 $i$ 的区间中，左端点最小的区间的左端点，限制等价于 $[L_i,i]$ 中颜色 $a_i$ 只出现了一次，又因为操作等价于删去一个子段，于是我们找到区间 $[L_i,i]$ 中颜色 $a_i$ 最靠前，次靠前，最靠后，次靠后的出现位置 $p_1,p_2,p_3,p_4$，那么限制等价于删去的区间包含 $[p_1,p_3]$ 或者 $[p_2,p_4]$，我们将这些区间标记为关键区间，考虑二分答案 $mid$ 然后做一个长度为 $mid$ 的滑动窗口，滑动窗口的过程中在左右端点移动时考新加入或者删除完整覆盖的关键区间，再用一个桶维护每个点的区间限制有多少个被满足，即可维护有多少个点的两个区间限制至少有一个被满足。

求解 $L_i$ 可以考虑线段树做区间取 $\min$，求解 $p_1,p_2,p_3,p_4$ 可以 vector 上二分，总时间复杂度 $O((n+m) \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int a[maxn],b[maxn],n,m;
int Lt[maxn],Rt[maxn];
int tr[maxn<<2];
int rk[maxn];
int minL[maxn];
void cover(int cur,int lt,int rt,int l,int r){
    if(r<lt||rt<l) return ;
    if(l<=lt&&rt<=r){
        tr[cur]=min(tr[cur],l);
        return ;
    }
    int mid=(lt+rt)>>1;
    cover(cur<<1,lt,mid,l,r);
    cover(cur<<1|1,mid+1,rt,l,r);
}
void build(int cur,int lt,int rt){
    if(lt==rt){
        minL[lt]=tr[cur];
        return ;
    }
    int mid=(lt+rt)>>1;
    tr[cur<<1]=min(tr[cur<<1],tr[cur]);
    tr[cur<<1|1]=min(tr[cur<<1|1],tr[cur]);
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
}
vector< pair<int,int> > L[maxn];//(r,id)
vector< pair<int,int> > R[maxn];//(l,id)
vector<int> d[maxn];
int tot;
int cnt[maxn];
int sum;
void add(int id){
    cnt[id]++;
    if(cnt[id]==1) sum++;
}
void del(int id){
    cnt[id]--;
    if(cnt[id]==0) sum--;
}
void clear(){
    sum=0;
    memset(cnt,0,sizeof(cnt));
}
bool check(int len){
    int l=1,r=0;
    while(r<l+len-1){
        r++;
        for(pair<int,int> now:R[r]){
            if(now.first>=l) add(now.second);
        }
    }
    if(sum==tot){
        clear();
        return true;
    }
    while(r<n){
        for(pair<int,int> now:L[l]){
            if(now.first<=r) del(now.second);
        }
        l++;
        r++;
        for(pair<int,int> now:R[r]){
            if(now.first>=l) add(now.second);
        }
        if(sum==tot){
            clear();
            return true;
        }
    }
    clear();
    return false;
}
void work(){
    memset(tr,0x3f3f3f3f,sizeof(tr));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        int l=1,r=n+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(a[i]>=b[mid]) l=mid;
            else r=mid;
        }
        a[i]=l;
        d[a[i]].push_back(i);
        rk[i]=d[a[i]].size()-1;
    }
    for(int i=1;i<=m;i++){
        cin>>Lt[i]>>Rt[i];
        cover(1,1,n,Lt[i],Rt[i]);
    }
    build(1,1,n);
    for(int i=1;i<=n;i++){
        if(minL[i]<=i){
            int l=-1,r=rk[i];
            while(l+1<r){
                int mid=(l+r)>>1;
                if(d[a[i]][mid]>=minL[i]) r=mid;
                else l=mid;
            }
            if(d[a[i]][r]!=i){
                //r r+1 rk[i]-1 rk[i]
                tot++;
                L[d[a[i]][r+1]].push_back(make_pair(i,tot));
                R[i].push_back(make_pair(d[a[i]][r+1],tot));
                L[d[a[i]][r]].push_back(make_pair(d[a[i]][rk[i]-1],tot));
                R[d[a[i]][rk[i]-1]].push_back(make_pair(d[a[i]][r],tot));
            }
        }
    }
    int l=-1,r=n;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(check(mid)==true) r=mid;
        else l=mid;
    }
    check(r);
    cout<<r<<'\n';
    for(int i=0;i<maxn;i++) L[i].clear(),R[i].clear(),d[i].clear();
    tot=0;
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--) work();
    return 0;
}
/*
1
5 2
10 1 6 14 1
4 5
2 4
*/
```

---

## 作者：Little09 (赞：1)

vp 的时候写了一个比较愚蠢的做法过了。

首先选择一个区间修改等价于删掉这个区间。那么考虑它给定的 $m$ 个区间会有什么影响。假设给定的某个区间是 $[l,r]$，那么假设颜色 $col$ 在这个区间出现 $k$ 次，下标是 $c_1,c_2,...,c_k$。那么：

- $0\le k\le 1$：没用。
- $k\ge 2$：答案区间必须要覆盖 $c_2,c_3,...,c_{k-1}$，并且要覆盖 $c_1$ 和 $c_k$ 的至少一个。

要是得到了所有 $c$，我们就得到若干个条件形式是下面两者之间一个：

1. 必须覆盖 $x$。
2. 必须覆盖 $x$ 和 $y$ 之一。

很容易贪心去做。具体地，从小到大枚举答案右端点 $r$，维护一个堆，每次用 $r$ 减去堆的最小值更新答案。考虑对于第 $2$ 类条件，我们在左端点的时候加入，到右端点的时候删除左端点，再加入右端点。

但是得到 $c$ 需要的复杂度还是不对。记在 $x$ 后且颜色与 $x$ 相同的第一个位置为 $s(x)$（找不到则为 $n+1$）。我们考虑把左端点从小到大扫过去，对于位置 $l$，找到 $l$ 所在给定区间的最大的 $r$。如果 $s(s(x))\le r$，那么 $s(x)$ 是一定要覆盖的位置（即条件 $1$）。再找到 $r$ 前面第一个和 $l$ 同颜色的位置 $p$，那么需要满足必须覆盖 $l,p$ 之一（即条件 $2$）。容易发现这样就涵盖了所有条件。

这样就做完了。实现的时候有点细节。

下面是场上写的丑陋代码，并不建议阅读。有疑问可以私信我。

```cpp
const int N=500005;
int n,m,sum; 
int a[N],s[N],c[N];
int p[N],h[N];
map<int,int>tmp;
int col;
vector<int>b[N];
int g[N];
vector<int>f[N];
void add(int x,int y)
{
	sum++;
	g[x]++;
	f[y].push_back(x);
}
multiset<int>se;
void work()
{
	cin >> n >> m;
	sum=0;
	tmp.clear();
	col=0;
	for (int i=1;i<=n;i++) cin >> a[i];
	for (int i=1;i<=n;i++)
	{
		g[i]=0;
		f[i].clear();
		if (tmp[a[i]]==0) tmp[a[i]]=++col;
		a[i]=tmp[a[i]];
	}
	for (int i=1;i<=n;i++) c[i]=0,p[i]=0;
	for (int i=n;i>=1;i--)
	{
		if (p[a[i]]==0) s[i]=n+1;
		else s[i]=p[a[i]];
		p[a[i]]=i;
	}
	s[n+1]=n+1;
	for (int i=1;i<=n;i++) b[i].clear();
	for (int i=1;i<=m;i++)
	{
		int l,r;
		cin >> l >> r;
		b[l].push_back(r);
	}
	for (int i=1;i<=n;i++) b[i].push_back(i);
	int mx=0;
	for (int i=1;i<=n;i++)
	{
		for (int j:b[i]) mx=max(mx,j);
		int u=s[i],v=s[u];
		if (v<=mx) c[u]=1;
	}
	int l=n+1,r=0;
	for (int i=1;i<=n;i++)
	{
		if (c[i]==1) r=max(r,i),l=min(l,i);
	}
	for (int i=l;i<=r;i++) c[i]=1;
	// cout << l << " " << r << endl << endl;
	mx=0;
	for (int i=1;i<=n;i++) h[i]=0;
	for (int i=1;i<=n;i++)
	{
		for (int j:b[i])
		{
			while (mx<j)
			{
				mx++;
				h[a[mx]]=mx;
			}
		}
		if (c[i]) continue;
		int u=h[a[i]];
		if (i!=u) add(i,u);
	}
	if (sum==0)
	{
		if (r==0) cout << 0 << endl;
		else cout << r-l+1 << endl;
		return;
	}
	if (r!=0) sum+=r-l+1;
	int ans=n,uu=0;
	se.clear();
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=g[i];j++) se.insert(i),uu++;
		if (c[i]) se.insert(i),uu++;
		for (int j:f[i]) 
		{
			se.erase(se.find(j));
			se.insert(i);
		}
		if (uu==sum) ans=min(ans,i-*se.begin()+1);
		//cout << "11c " << *se.begin() << endl;
	}
	cout << ans << endl;
}

```


---

## 作者：kkxacj (赞：1)

讲一个 $O\left ( n \right ) $ 且不用并查集的做法。

#### 思路

首先求一个区间改里面的数可以想成删去里面的数。

考虑将区间限制转换为对于每个点的限制。

记 $c_j$ 表示每个点 $j$ 求出最小的 $l_i$ 且 $l_i \le j,j \le r_i$，然后记 $b_j$ 表示在 $\left [ c_j,j \right ) $ 中找到一个 $z$ 使得 $j-z$ 最大且 $a_j = a_z$，$last_j$ 表示在 $\left [ c_j,j \right ) $ 中找到一个 $z$ 使得 $j-z$ 最小且 $a_j = a_z$。

显然，对于每一个数，要么这个数被删去，要么 $b_j$ 到 $last_j$ 全被删除，如果没有就不管。

在求答案时可以枚举一个 $l$ 表示左端点，然后求出 $r$ 的最小位置，发现如果一个数的 $b_j$ 没删，那么必须要删掉 $j$ 这个数，所以又记一个数组 $f_j$ 表示不删掉第 $j$ 个数要删掉的数的位置的**最大值**，可以在求 $b_j$ 时顺便就求了。

如果遇到 $b_l$ 有值的情况，在算完这里的贡献后就要结束计算，否则就会不满足条件。

对于 $a_i$ 数组的离散化，可以用 `unordered_map` 存，因为不在乎大小关系，没必要排序。

对于求 $c_i$，考虑记 $mr_i$ 表示左端点为 $i$ 时 $r$ 最大是多少，然后直接扫一遍就行了。

很容易发现，$c_i$ 是单调递增的，可以开 `vector` 并用一个数组表示符合条件的数的第一个位置是哪里。

求答案直接扫一遍就行了。

所以总时间是 $O\left ( n \right ) $ 的。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{
    const int BUF=1<<21;
    char buff[BUF],*p1=buff,*p2=buff;
    #define getchar() (p1==p2&&(p2=((p1=buff)+fread(buff,1,BUF,stdin)),p1==p2)?EOF:*p1++)
    template<typename T>inline void read(T &x){
        char ch=getchar();x=0;
        while(!isdigit(ch)) ch=getchar();
        while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    }
    char obuf[BUF],*p3=obuf;
    inline void putch(char ch){
        if(p3-obuf<BUF) *p3++=ch;
        else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;
    }
    char ch[32],ctop;
    template<typename T>inline void print(T x){
        if(!x) return putch(48);
        while(x) ch[++ctop]=x%10^48,x/=10;
        while(ctop) putch(ch[ctop--]);
    }
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int N = 2e5+10;
int t,n,m,cnt,a[N],b[N],c[N],f[N],ans,l,r,ma,f1[N],fr[N]; 
signed main()
{
	read(t);
	while(t--)
	{
		read(n),read(m);
		cnt = ma = 0;
		vector<int>v[n+1];
		unordered_map<int,int>mp;
		for(int i = 1;i <= n;i++) 
		{
			read(a[i]);
			if(!mp[a[i]]) mp[a[i]] = ++cnt;
			a[i] = mp[a[i]];
			fr[i] = 0,b[i] = n+1;
		}
		cnt = 0;	
		for(int i = 1;i <= m;i++) read(l),read(r),fr[l] = max(fr[l],r);
		l = 0;
		for(int i = 1;i <= n;i++)
			while(l < fr[i]) l++,b[l] = i;
		for(int i = 1;i <= n;i++) c[a[i]] = f[i] = 0,f1[i] = i;
		for(int i = 1;i <= n;i++) 
		{
			while(c[a[i]] < v[a[i]].size() && v[a[i]][c[a[i]]] < b[i]) c[a[i]]++;
			if(c[a[i]] != v[a[i]].size()) f[i] = v[a[i]][v[a[i]].size()-1],ma = max(ma,f[i]),b[i] = v[a[i]][c[a[i]]],f1[v[a[i]][c[a[i]]]] = i;
			else b[i] = 0;
			v[a[i]].push_back(i); 
		}
		ans = n;
		for(int i = 1;i <= n;i++)
		{
			ans = min(ans,ma-i+1);
			ma = max(ma,f1[i]);
			if(b[i]) break;
		}
		print(ans),putch('\n');
	}
	flush();
	return 0;
} 
```

---

## 作者：Yesod (赞：1)

一种很新的做法，将 $ m $ 个数对去掉 $ a[l,r] $ 中的元素都不同的无用数对。然后有一个显然的结论，修改区间的左端点一定在所有有用数对中 $ l_i $ 最小的区间，右端点一定在所有有用数对中 $ r_i $ 最大的区间。同时随着修改区间的左端点的增大，修改区间的右端点一定不减，举个例子，当 $ (l,r_0) $ 到 $ (l+1,r_1) $ 时，那么 $ r_1 $ 就等于 $ r_0 $ 和在包含 $ l+1 $ 的有用数对里与 $ a_{l+1} $ 相同的数字的最右边的位置的最大值，随后从 $ l_i $ 最小的区间递推到左端点第一次出现重复的数字的时候停止，同时统计所有答案的最小区间。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n,m,z,rnf[N][20],p[N],nl,nr,l,r,ans,qwq,qwq1,qwq2,qwq3,po[N],qw[N],qw1[N];
struct node{
	int r,l;
}a[N],b[N];
void rmq()
{
	for(int i=1;i<=n;++i)
		rnf[i][0]=a[i].l;
	for(int i=1;i<=19;++i)
		for(int j=1;j+(1<<i)-1<=n;++j)
			rnf[j][i]=max(rnf[j][i-1],rnf[j+(1<<(i-1))][i-1]);
}
bool cz(int l,int r)
{
	int k=p[r-l+1];
	if(max(rnf[l][k],rnf[r-(1<<k)+1][k])>=l)
		return 1;
	else
		return 0;
}
bool cmp(node i,node j)
{
	if(i.r==j.r) return i.l<j.l;
	return i.r<j.r;
}
map<int,int>q;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int i=1,j=0;i<=N-5;++i)
	{
		if(i>=(1<<(j+1))) ++j;
		p[i]=j;
	}
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;++i)
			a[i].l=a[i].r=0;
		for(int i=1;i<=n;++i)
		{
			cin>>z;
			po[i]=z;
			if(q[z])
				a[i].l=q[z],a[q[z]].r=i;
			q[z]=i;
		}
		rmq();
		l=r=nl=nr=-1;
		for(int i=1;i<=n;++i)
			qw[i]=0,qw1[i]=n;
		for(int i=1;i<=m;++i)
		{
			cin>>b[i].l>>b[i].r;
			if(b[i].l>b[i].r) swap(b[i].l,b[i].r);
			qw[b[i].l]=max(qw[b[i].l],b[i].r);
			qw1[b[i].r]=min(qw1[b[i].r],b[i].l);
			if(cz(b[i].l,b[i].r))//用rmq去掉无用区间
			{
				if(l==-1||b[i].l<l||(b[i].l==l&&b[i].r>r))
					l=b[i].l,r=b[i].r;
				if(nl==-1||b[i].r>nr||(b[i].r==nr&&b[i].l<nl))
					nl=b[i].l,nr=b[i].r;
			}
		}
		for(int i=1;i<n;++i)
			qw[i]=max(qw[i],qw[i-1]);
		for(int i=n-1;i>=1;--i)
			qw1[i]=min(qw1[i],qw1[i+1]);
		if(l==-1)
			cout<<0<<'\n';
		else
		{
			ans=1e8;
			qwq=r;
			for(int i=l;i<=qwq;++i)//求出递推的结束位置
				if(a[i].r!=0)
					qwq=min(qwq,a[i].r);
			if(a[qwq].l>=l)
				--qwq;
			qwq1=nl;
			for(int i=nr;i>=qwq1;--i)
				qwq1=max(qwq1,a[i].l);
			if(a[qwq1].r<=nr)
				++qwq1;
			qwq2=nr-qwq1+1;
			ans=min(nr-l+1-qwq2,nr-l+1-qwq3);
			for(int i=l;i<=qwq;++i)
			{
				if(i>=nl||nr-qwq2+1<=qw[i])
				{
				int k=i;
				while(1)
				{
					if(a[k].r<=qw[i]&&a[k].r!=0) k=a[k].r;
					else break;
				}
				qwq2=min(qwq2,nr-k);
				}
				ans=min(ans,nr-l+1-qwq2-(i-l+1));//统计区间答案
			}
			cout<<ans<<'\n';
		}
		for(int i=1;i<=n;++i)
			q[po[i]]=0;
	}
	return 0;
}

---

## 作者：EuphoricStar (赞：1)

考虑扫描线，扫到 $i$ 时，设包含 $i$ 的区间的最小左端点为 $l$。设 $x = a_i$。

若 $[l, i]$ 之间存在 $\ge 2$ 个 $x$，那么就必须要修改。考虑序列此时的形式形如：

$$[1, \ldots, a_l, \ldots, x, \ldots, x, \ldots, x, \ldots, x, \ldots, n]$$

考虑若修改的区间左端点 $\le l$ 右边第一个 $x$ 的位置，那么修改的区间右端点必须在倒数第二个 $x$ 位置或其之后。若修改的区间左端点 $> l$ 右边第一个 $x$ 的位置但是 $\le l$ 右边第二个 $x$ 的位置，那么修改的区间右端点必须在 $i$ 或其之后。否则修改的区间左端点不可能 $> l$ 右边第二个 $x$ 的位置。

若设 $f_i$ 为修改的区间左端点为 $i$，修改的区间右端点的最小值。那么上面就相当于对 $f$ 的区间取 $\max$。最后我们要求出 $f$ 的每个值，答案即 $\min\limits_{i = 1}^n f_i - i + 1$。可以使用线段树维护 $f$。

总时间复杂度 $O(n \log n)$。

[code](https://codeforces.com/problemset/submission/1684/242982911)

---

## 作者：xiao7_Mr_10_ (赞：1)

好的如你所见，这道题让我们修改原序列的一个区间使得一些给定区间内没有相同的数，并且让修改区间长度最小。

令条件区间 $(l,r)$ 为题目中所要求的区间，虽然是废话。

很显然，我们可以随便乱改，那么修改一个区间 $(l,r)$ 其实就相当于在原序列里丢掉这段区间。

所以说我们就可以考虑维护一个东西，就是我在原序列中丢掉了区间 $(l,r)$ 后，其他位置中所有条件区间中一个数的出现次数超过一的对数，记作 $sum$。

显然我们想让 $sum$ 为 $0$，那么考虑双指针的做法。

如果我当前已经处理了区间 $(l,r)$ 的答案。

移动到 $(l+1,r)$ 中，相当于位置为 $l$ 的数启用了，答案自然加上 $(1,l)$ 与 $(r,n)$ 中的贡献。

移动到 $(l+1,r)$ 中，相当于位置为 $r$ 的数弃用了，答案自然减去 $(1,l)$ 与 $(r+1,n)$ 中的贡献。

然后我们可以记录某一个位置中能够被至少一个区间覆盖，在它最前面还是最后面的位置，然后移动指针的时候查取该区间内对于该颜色的数量，由于是静态的，直接开个向量然后二分即可。

时间复杂度 $O(n \log n)$。

对了，记得清空上次数据，不然就朝如青丝暮成雪，事非成败转头空了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,t,ans,sum,minl[N],maxr[N],l,r,len,b[N],a[N];
vector <int> col[N];
void init(){
	for(int i = 1;i <= n;i++)minl[i]=n,maxr[i]=-1,col[i].clear();
}
inline int query(int id,int l,int r){
	if(l>r)return 0;
	return upper_bound(col[id].begin(),col[id].end(),r)-lower_bound(col[id].begin(),col[id].end(),l);
}
int m;
void work(){
	sum=0;
	cin >> n >> m;
	ans=n;
	init();
	for(int i = 1;i <= n;i++)cin >> a[i],b[i]=a[i];
	sort(b+1,b+1+n);
	int cnt=unique(b+1,b+1+n)-b-1;
	for(int i = 1;i <= n;i++)a[i]=lower_bound(b+1,b+1+cnt,a[i])-b,col[a[i]].push_back(i);
	for(int i = 1;i <= m;i++){
		cin >> l >> r;
		minl[r]=min(minl[r],l),maxr[l]=max(maxr[l],r);
	}
	for(int i = n-1;i >= 1;i--)minl[i]=min(minl[i],minl[i+1]);
	for(int i = 2;i <= n;i++)maxr[i]=max(maxr[i],maxr[i-1]);
	for(int i = 1;i <= cnt;i++){
		for(int j = 0;j < col[i].size();j++){
			int val=col[i][j];
			sum+=query(i,val+1,maxr[val]);	
		}
	}
	if(!sum){
		cout << "0\n";
		return;
	}
	int l = 1;
	for(int i = 1;i <= n;i++){
		sum-=query(a[i],minl[i],l-1)+query(a[i],i+1,maxr[i]);
		while(l < i && sum + query(a[l],minl[l],l-1)+ query(a[l],i+1,maxr[l])==0)++l;
		if(!sum)ans=min(ans,i-l+1);
	}
	cout << ans << "\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)work();
	return 0;
}

```

---

## 作者：chen_hx (赞：0)

>一个和官方题解不大一样的做法，常数略微大一点点，故作文记之。

* 首先第一点，每一个区间都有可能产生若干个冲突对，然后显然我选择的区间一定要覆盖这些冲突。但是不一定要全部覆盖，其实留出每组冲突对的最左边或者最右边都可以。以及可以感性理解一下，假如区间的左端点向右移动，最优答案的右端点也会向右移动。
* 现在就是把这个问题拆成一下几个问题：1、每个区间最多能缩多少 2、枚举开头之后最少需要多少能够满足限制
* 首先如果确定左端点，那么答案的右端点就是每个区间的必要的右端点取 `max` ，因此先分别考虑每一个区间，如果答案的左端点在一个区间的左端点的左边，那么显然对于这个区间而言对答案的右端点的限制是不会变得，只有当答案的左端点越过了这个区间的左端点时，这个区间对答案的右端点的限制就会向右挪
* 因此可以从前往后扫一遍，开一个 `last[i]` 表示扫到某个位置，值 `i` 最后一次出现在哪，然后扫到一个数就用 `last[a[i]]` 来更新 `rmost` ，然后更新 `last[a[i]]` ，然后可以用一个堆来记着区间，边扫边加区间，之后按照右端点排序，每次检查堆顶，每个区间在出堆的时候被 `rmost` 更新，然后就可以跑出每个区间在答案左端点比自身左端点小的时候最少要拓展到哪里，记为 `must[i]`
* 然后再考虑在向右挪答案的左端点的时候，怎么更新右端点。首先先考虑一个性质，假如现在做到第 `i` 位，现在覆盖在上面的有两个区间甲乙，甲右端点比乙的大，那么当我把答案左端点从 `i` 挪到 `i+1` 时，甲对答案右端点产生的限制一定比乙更右边，因为挪到下一位之后我会把答案更新成某个 `last[a[i]]` ，而甲右端点的 `last[a[i]]` 一定比乙的大，因此我只需要在挪答案左端点时记住目前走过的区间中右端点最靠右的是多少即可。
* 代码

```cpp

// Problem: F. Diverse Segments
// Contest: Codeforces - Codeforces Round #792 (Div. 1 + Div. 2)
// URL: https://codeforces.com/problemset/problem/1684/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f^=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?x:-x;
}
const int N=2e5+5;
int a[N],n,m,rks,ans,lmost,now,must[N],last[N];
pair<int,int> b[N],mmt[N];
vector<pair<int,int>> seg[N],rev[N];
priority_queue<pair<int,int>> q;
void qclear(){
	while(q.size())q.pop();
}
void gao1(){
	qclear();
	int need=n+1;
	lmost=need;
	memset(last,0,sizeof(int)*(rks+5));
	for(int i=n;i>=1;--i){
		for(auto x:rev[i]){
			q.push(x);
		}
		if(last[a[i]])need=min(need,last[a[i]]);
		last[a[i]]=i;
		while(q.size()&&(q.top().fi==i)){
			int idx=q.top().se;
			q.pop();
			must[idx]=need;
		}
	}
	for(int i=1;i<=m;++i){
		if(must[i]<=mmt[i].se)lmost=min(lmost,must[i]);
	}
}
void gao2(){
	qclear();
	int need=0;
	memset(last,0,sizeof(int)*(rks+5));
	memset(must,0,sizeof(int)*(rks+5));
	for(int i=1;i<=n;++i){
		for(auto x:seg[i]){
			q.push({-x.fi,x.se});
		}
		if(last[a[i]])need=max(need,last[a[i]]);
		last[a[i]]=i;
		while(q.size()&&(-q.top().fi==i)){
			int idx=q.top().se;
			q.pop();
			must[idx]=need;
		}
	}
}
void extend(int x){
	while(now<=x){
		last[a[now]]=now;
		++now;
	}
}
void gao3(){
	memset(last,0,sizeof(int)*(rks+5));
	int extd=0;
	ans=1e9;
	now=1;
	for(int i=1;i<=m;++i){
		extd=max(extd,must[i]);
	}
	for(int i=1;i<=min(n,lmost);++i){
		if(i>1){
			extd=max(extd,last[a[i-1]]);
		}
		extd=max(extd,i);
		int rf=0;
		for(auto x:seg[i]){
			extd=max(extd,must[x.se]);
			rf=max(rf,x.fi);
		}
		extend(rf);
		ans=min(ans,extd-i+1);
	}
}
void solve(){
	n=read(),m=read(),rks=0;
	for(int i=1;i<=n;++i){
		seg[i].clear();
		rev[i].clear();
		a[i]=read();
		b[i]={a[i],i};
	}
	sort(b+1,b+n+1);
	a[b[1].se]=++rks;
	for(int i=2;i<=n;++i){
		if(b[i].fi==b[i-1].fi)a[b[i].se]=a[b[i-1].se];
		else a[b[i].se]=++rks;
	}
	for(int i=1;i<=m;++i){
		int l=read(),r=read();
		mmt[i]={l,r};
		seg[l].push_back({r,i});
		rev[r].push_back({l,i});
		must[i]=n+1;
	}
	gao1();
	if(lmost==n+1){
		puts("0");
		return;
	}
	gao2();
	gao3();
	printf("%lld\n",ans);
}
signed main(){
	int T=read();
	while(T--)
		solve();
	return 0;
}
```



---

## 作者：AKPC (赞：0)

写篇题解防止忘记。

考虑对于同一个数值 $x$，记这个数值对应的位置下标集合为 $B$。枚举每个 $i=1,2,\dots,|B|$，设 $j$ 为满足 $b_i,b_j$ 在同一给定区间 $[l_t,r_t]$ 内的最小 $j$，则选取的 $L,R$ 必须包含 $B_j,B_{j+1},\dots,B_{i-1}$ 或者 $B_{j+1},B_{j+2},\dots,B_i$。

总而言之，对于每个 $x$，枚举 $i$，找到 $j$，就有约束条件：

- 当 $L\leq b_j$，则 $R\geq b_{i-1}$。
- 当 $L\in(b_j,b_{j+1}]$，则 $R\geq b_i$。
- 当 $L>b_{j+1}$，合法 $R$ 不存在。

考虑设 $f_t$ 表示 $L=t$ 的最小 $R$，维护区间取 $\max$，离线求值即可。

---

## 作者：ifffer_2137 (赞：0)

~~唐诗题害我假了两次~~。/fn/fn
### 题意
给一个序列，可以选一个子段将里面每一个数随意更改，再给出若干个区间，要求修改以后每个区间内不能有重复数字，求最短修改子段。
### 分析
显然修改一个子段可以看成把里面每一个数改成与其他任何数不同的数字，这样可以做到且肯定不劣。

然后我们求最短合法子段，可以考虑扫描线，枚举右端点。容易发现，右端点扫过去的时候左端点有单调性，因为一个合法子段如果包含另一个合法子段那它肯定不优。

于是你 two pointers 扫一下，这样只需要支持修改一个数，还原一个数，以及 check 当前序列是否合法即可。我们考虑没有重复数字的区间有什么 check 方法，参考一些数颜色的经典技巧，维护每个位置前面第一个和它同色的位置 $\text{lst}_i$，则一个区间 $[l,r]$ 满足条件 $\iff \min_{i=l}^r \text{lst}_i<l$。这样子就比较好维护了，我们把所有区间的限制下放到每一个位置上，先做一编扫描线，求 $\text{lst}_i$ 的同时用 `multiset` 维护当前位置需要满足的所有限制，显然我们只要关心 $l$ 最小的那一个，设为 $\text{lim}_i$。

现在考虑扫描线的时候修改一个数，容易发现 $\text{lst}_i$ 会受到影响的只有它和它**除去当前修改区间后**的同色后继，离散化以后给每个颜色开一个位置的 `vector` 然后二分直接求就好了。然后需要动态维护全局每一个位置是否满足 $\text{lst}_i<\text{lim}_i$，我们直接考虑 sgt 维护全局 $\text{lim}_i-\text{lst}_i$，这样只需要单点修改判断全局 $\min$ 是否大于 $0$ 即可，非常好写。时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
int T;
int n,m,ans;
int a[maxn];
int t[maxn],tt;
int bin[maxn],lst[maxn];
vector<int> A[maxn],pos[maxn];
multiset<int> S;
int lim[maxn];
class Segment_Tree{
public:
	int mn[maxn<<2];
	void pushup(int o){mn[o]=min(mn[o*2],mn[o*2+1]);}
	void build(int o,int l,int r){
		mn[o]=0;if(l==r) return;
		int m=(l+r)>>1;
		build(o*2,l,m),build(o*2+1,m+1,r);
	}
	void update(int o,int l,int r,int x,int k){
		if(x<l||x>r) return;
		if(l==r){mn[o]=k;return;}
		int m=(l+r)>>1;
		if(x<=m) update(o*2,l,m,x,k);
		else update(o*2+1,m+1,r,x,k);
		pushup(o);
	}
}sgt;
signed main(){
	#ifndef ONLINE_JUDGE
		assert(freopen("data.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read(),m=read();
		for(int i=1;i<=n;i++){
			t[i]=a[i]=read();
			A[i].clear();
		}
		sort(t+1,t+n+1),tt=unique(t+1,t+n+1)-t-1;
		for(int i=1;i<=tt;i++){
			bin[i]=0;pos[i].clear();
			pos[i].eb(0);
		}
		for(int i=1;i<=n;i++){
			a[i]=lower_bound(t+1,t+tt+1,a[i])-t;
			pos[a[i]].eb(i);
			lst[i]=bin[a[i]],bin[a[i]]=i;
		}
		for(int i=1;i<=tt;i++) pos[i].eb(n+1);
		for(int i=1;i<=m;i++){
			int l=read(),r=read();
			A[l].eb(l),A[r+1].eb(-l);
		}
		sgt.build(1,1,n);S.clear();S.insert(inf);
		for(int i=1;i<=n;i++){
			for(int x:A[i]){
				if(x>0) S.insert(x);
				else S.erase(S.find(-x));
			}
			lim[i]=(*S.begin());
			sgt.update(1,1,n,i,lim[i]-lst[i]);
		}
		if(sgt.mn[1]>0){
			cout<<0<<'\n';
			continue;
		}
		ans=inf;
		for(int r=1,l=1;r<=n;r++){
			sgt.update(1,1,n,r,lim[r]);
			int pre=pos[a[r]][lower_bound(pos[a[r]].begin(),pos[a[r]].end(),l)-pos[a[r]].begin()-1];
			int suf=pos[a[r]][upper_bound(pos[a[r]].begin(),pos[a[r]].end(),r)-pos[a[r]].begin()];
			sgt.update(1,1,n,suf,lim[suf]-pre);
			if(sgt.mn[1]<=0) continue;
			while(l<r&&sgt.mn[1]>0){
				sgt.update(1,1,n,l,lim[l]-lst[l]);
				suf=pos[a[l]][upper_bound(pos[a[l]].begin(),pos[a[l]].end(),r)-pos[a[l]].begin()];
				sgt.update(1,1,n,suf,lim[suf]-l);
				l++;
			}
			if(sgt.mn[1]<=0){
				l--;
				sgt.update(1,1,n,l,lim[l]);
				pre=pos[a[l]][lower_bound(pos[a[l]].begin(),pos[a[l]].end(),l)-pos[a[l]].begin()-1];
				suf=pos[a[l]][upper_bound(pos[a[l]].begin(),pos[a[l]].end(),r)-pos[a[l]].begin()];
				sgt.update(1,1,n,suf,lim[suf]-pre);
			}
			ans=min(ans,r-l+1);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：ballpoint_pen (赞：0)

怎么官解做法这么神仙。

因为数据结构学傻了所以这是一个含有大量 DS 的解法。

我们把条件转化一下，对于每个 $i$ 我们求一个 $le_i$ 表示 $a_{[le_i,i-1]}$ 内的数不能和 $a_i$ 相同。这个可以直接开一颗线段树简单粗暴算，支持区间修改单点查询即可。

然后有了 $le$ 之后我们再求一个区间 $[l_i,r_i]$ 表示如果 $i$ 不改那么 $l_i$ 到 $r_i$ 都要被包含在区间里。求这个东西可以先离散化 $a_i$，然后把 $a_i$ 相同的下标 $i$ 扔到一个 vector 里面去，求 $l_i,r_i$ 相当于在求：

- 和 $a_i$ 相同的位置中 $\ge le_i$ 的最小值

- 和 $a_i$ 相同的位置中 $< i$ 的最大值

这个可以在向量里直接二分。做完之后我们进一步简化了题目：求一个最短的区间满足对于不属于这个区间的所有 $i$，$[l_i,r_i]$ 均被选中。

显然可以双指针求答案。区间的移动操作实质上是在扩展区间时删除一个点的限制，缩短区间时增加一个点的限制，再开一颗线段树维护当前限制中 $l_i$ 的最小值，$r_i$ 的最大值。需要支持单点修改，整体查询最值。

时间 $O(n\log n)$。跑的好像还挺快？

---

## 作者：Yasuraoka_Hanabi (赞：0)

vp 的时候 D E 摆烂了一会儿，然后这题开始想假了就没写完，被一车人吊锤了呜呜。

------------

考虑把一个区间合法转成更可做的约束。设 $pre_i$ 是上一个和 $a_i$ 相同的位置（没有则 $pre_i=-1$），则实际上对于 $i\in [l_j,r_j]$，应该满足 $pre_i\lt l_j$。

从一个区间变成多个区间，我们发现，对于一个 $i$，只要设 $lim_i$ 是所有包含 $i$ 的区间中，$l_j$ 最小的那个（没有则 $lim_i=\infty$），则实质上题目的约束是 $\forall i,pre_i\lt lim_i$。

$pre$ 和 $lim$ 的求解都是经典问题，不再赘述。

把一个数任意重赋值的过程可以看作将它的 $pre$ 置为 $-\infty$，同时将 $pre_{nxt_i}$ 置为 $pre_i$。

另外，设 $f(l)$ 是最小的 $r$ 使得删去 $[l,r]$ 合法（不存在这样的 $r$ 则 $f(l)=\infty$）。显然 $f(l)$ 单调不降。换言之可以考虑双指针。

所以我们需要处理动态地删除/加入一个位置，并维护是否满足所有位置 $pre_i\lt lim_i$ 成立。

设一个计数器 $cur$ 初始为 $0$。每当有一个 $pre_i\ge lim_i$ 则 $cur$ 增加 $1$。则实际上是动态维护 $cur$，合法等价于 $cur=0$。

离散化 $a$ 后用 $set$ 维护每个数的所有出现位置。就可以动态计算每个位置的 $pre$ 和 $nxt$：因为你注意到删除/加入一个位置只会修改 $O(1)$ 个位置的 $pre$ 和 $nxt$。修改一个位置后重新计算其对 $cur$ 的贡献即可。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int MAXN=2e5+10,INF=1e9;
int T,n,m,a[MAXN],l[MAXN],r[MAXN];
int lim[MAXN],pre[MAXN],cur;
set<int>occ[MAXN];
int qry_pre(set<int>& s,int val){
    if(s.empty())return -1;
    auto it=s.lower_bound(val);if(it==s.begin())return -1;
    it--;int ret=*it;if(ret<val)return ret;return -1;
}
int qry_nxt(set<int>& s,int val){
    if(s.empty())return -1;
    auto it=s.upper_bound(val);if(it==s.end())return -1;
    int ret=*it;if(ret>val)return ret;return -1;
}
void add_pos(int pos){
    int pv=qry_pre(occ[a[pos]],pos),nv=qry_nxt(occ[a[pos]],pos);
    pre[pos]=pv;
    if(pre[pos]>=lim[pos])cur++;
    if(nv!=-1){
        if(pre[nv]>=lim[nv])cur--;
        pre[nv]=pos;
        if(pre[nv]>=lim[nv])cur++;
    }
    occ[a[pos]].insert(pos);
}
void del_pos(int pos){
    int pv=qry_pre(occ[a[pos]],pos),nv=qry_nxt(occ[a[pos]],pos);
    if(pre[pos]>=lim[pos])cur--;
    if(nv!=-1){
        if(pre[nv]>=lim[nv])cur--;
        pre[nv]=pv;
        if(pre[nv]>=lim[nv])cur++;
    }
    occ[a[pos]].erase(pos);
}
namespace D{
    int b[MAXN],tot;
    vector<int>add[MAXN],del[MAXN];
    void process(){
        tot=0;rep(i,1,n)b[++tot]=a[i];
        sort(b+1,b+1+tot);tot=unique(b+1,b+1+tot)-b-1;
        rep(i,1,n)a[i]=lower_bound(b+1,b+1+tot,a[i])-b;

        rep(i,1,n)add[i].clear(),del[i].clear();
        rep(i,1,m)add[l[i]].push_back(l[i]),del[r[i]].push_back(l[i]);
        multiset<int>S;
        rep(i,1,n){
            lim[i]=INF;
            for(auto u:add[i])S.insert(u);
            if(S.size())lim[i]=*S.begin();
            for(auto u:del[i])S.erase(S.find(u));
        }

        cur=0;
        rep(i,1,tot)occ[i].clear();
        rep(i,1,n)occ[a[i]].insert(i);
        rep(i,1,n)pre[i]=qry_pre(occ[a[i]],i);
        rep(i,1,n)if(pre[i]>=lim[i])cur++;
        if(!cur){cout<<0<<'\n';return;}
        int ans=n;
        int L=1,R=1;
        while(L<=n){
            if(R<L)R=L;
            while(R<=n && cur){
                del_pos(R);
                R++;    
            }
            if(!cur)ans=min(ans,R-L);
            add_pos(L);L++;
        }
        cout<<ans<<'\n';
    }
};
void solve(){
    cin>>n>>m;
    rep(i,1,n)cin>>a[i];
    rep(i,1,m)cin>>l[i]>>r[i];
    D::process();
}
int main(){
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--)solve();

    return 0;
}
```



---

