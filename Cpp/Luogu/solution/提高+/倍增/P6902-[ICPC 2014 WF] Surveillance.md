# [ICPC 2014 WF] Surveillance

## 题目描述

给定一个长度为 $n$ 的环，有 $k$ 个区域被覆盖，求最小的满足环被完全覆盖的区域数量。

## 说明/提示

$3\leq n\leq 10^6,1\leq k\leq 10^6.$

## 样例 #1

### 输入

```
100 7
1 50
50 70
70 90
90 40
20 60
60 80
80 20
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8 2
8 3
5 7
```

### 输出

```
impossible
```

## 样例 #3

### 输入

```
8 2
8 4
5 7
```

### 输出

```
2
```

# 题解

## 作者：鏡音リン (赞：15)

简要题意：一个环上有 $n$ 个点，给定了 $k$ 个环上区间，求在这些区间中最少选择多少个可以覆盖环上所有的点，或判断无解。只输出最小值。

考虑一个弱化版的问题：把环改为链，应该怎么做。可以使用贪心算法：假如当前选择的区间已经覆盖了前 $x$ 个点，为了覆盖第 $x+1$ 个点，一定要再选择一个左端点小于等于 $x+1$ 的区间。那么我们加入一个左端点小于等于 $x+1$，且右端点位置最大的区间，这样能尽可能覆盖最多的点，一定是最优的。此时把 $x$ 更新为这个右端点的位置。初始时令 $x\leftarrow 0$，不断重复这个过程选择加入的区间，直到 $x=n$ 时终止循环。若某一次选择区间后 $x$ 仍不变，说明第 $x+1$ 个点不可能被覆盖，无解。对每个 $1\le i\le n$ 预处理出左端点小于等于 $i$ 的所有区间中最大的右端点位置，就可以用 $O(n+k)$ 的时间预处理，$O(n)$ 选择区间，总时间复杂度 $O(n+k)$ 解决这个问题。

扩展一下上面的问题：仍然是链，有多次询问，每次给定一个区间 $[l,r]$，询问覆盖区间中所有点的答案。上面的算法可以很自然地扩展到询问一个区间的情况：把 $x$ 的初始值改为 $l-1$，终止条件改为 $x\ge r$ 即可。为了优化多次询问的时间复杂度，可以使用倍增：用 $f(x,y)$ 表示已经覆盖了前 $x$ 个点，按照上述方法再选择 $2^y$ 个区间，能够覆盖前多少个点。对所有 $0\le x< n,~0\le y\le \lfloor\log_2(n) \rfloor$ 预处理出 $f(x,y)$。然后倍增二分，从 $\lfloor\log_2(n) \rfloor$ 到 $0$ 枚举 $y$，如果当前 $f(x,y)<r$ 就选择这 $2^y$ 个区间，并令 $x\leftarrow f(x,y)$。最后若 $x<r$ 则再选择一个区间，过程中判断无解的情况。时间复杂度可以做到 $O(k+n\log n)$ 预处理，$O(\log n)$ 处理单次询问。

回到环上的问题来。在任意两个相邻点之间破环成链，不妨选择方便实现的点 $1$ 和点 $n$ 之间。对于所有经过这一分割点的区间，设这个区间是 $[l,n]\cup [1,r]$，把它们记录下来，然后添加 $[l,n]$ 和 $[1,r]$ 两个区间。添加这两个区间并不会使答案发生变化。添加之后，一定有一组最优解包含至多一个经过分割点的区间。证明如下：如果一组最优解包含两个经过分割点的区间 $[l_A,n]\cup [1,r_A]$ 和 $[l_B,n]\cup [1,r_B]$，把这两个区间改为后添加的 $[\min(r_A,r_B),n]$ 和 $[1,\max(l_A,l_B)]$ 两个区间，仍然能覆盖所有的点，这仍然是一组最优解。如果还有超过一个经过分割点的区间，就继续这样做，最终一定能得到一组包含至多一个经过分割点的区间的最优解。

那么，我们可以枚举选择的经过分割点的区间是哪个，若为 $[l,n]\cup [1,r]$，用上面的算法求出链上覆盖 $[r+1,l-1]$ 中的点需要选择多少区间，并更新最小值。注意也可以不选择经过分割点的区间。总体时间复杂度 $O((n+k)\log n)$。

---

## 作者：water_tomato (赞：14)

本文同步发表于个人博客：[Link](https://www.watertomato.com/p6902-icpc2014-wfsurveillance-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/P6902)。

给定一个长度为 $n$ 的环，有 $k$ 个区域被覆盖，求最小的满足环被完全覆盖的区域数量。

## 解析

先考虑如果是链的话就是一个朴素的贪心：每次在所有左端点不大于当前位置的点中选取一个右端点最大的跳过去。对于环，容易想到将其断开，在其后面复制一份即可。

问题转化为了一个长度为 $2n$ 的链，求最少数量的区域使其能够覆盖长度至少为 $n$ 的一个区间。

朴素的想法是枚举左端点，一直往右跳直至区间长度 $\ge n$。又发现对于任意一个点，其决策是一定的，即我们可以预处理出每一个点会跳到哪个位置，这样的话朴素的往右跳操作就可以用倍增优化，时间复杂度为 $O(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
const int N=2e6+5;
int n,k,f[N][30],ans=1e9;
pair<int,int> a[N];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++){
		scanf("%d%d",&a[i].fi,&a[i].se);
		if(a[i].fi>a[i].se) a[i].se+=n;
	}
	sort(a+1,a+1+k);
	int now=1,r=0;
	for(int i=1;i<=2*n;i++){
		while(now<=k&&a[now].fi<=i){
			r=max(r,a[now].se+1);
			now++;
		}
		f[i][0]=r;
	}//预处理跳一次跳到哪
	for(int j=1;j<=20;j++){
		for(int i=1;i<=2*n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}//倍增预处理
	for(int i=1;i<=2*n;i++){
		int x=i,ret=0;
		for(int j=20;j>=0;j--){
			if(f[x][j]-i<n){
				x=f[x][j];
				ret+=1<<j;
			}
		}
		x=f[x][0];ret++;
		if(x-i>=n) ans=min(ans,ret);
	}//枚举左端点再跑倍增即可
	if(ans==1e9) printf("impossible\n");
	else printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Lynkcat (赞：11)

简化版题意：给你一个长度为 $n$ 的圆，给你 $k$ 条线段覆盖在这个圆上，你需要在整个圆还是被覆盖的前提下去掉最多的线段。

如果这是一条链的话显然是个贪心。每次找右端点最大的线段作为后继即可。

那我们考虑断环成链，把链复制一份到后面，然后每次枚举线段然后倍增优化往后跳的过程，然后跳啊跳直到最右边减去最左边大于 $n$ 统计答案取 $\max$。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define N 1000005
using namespace std;

inline int read(){
    int x = 0; char ch = getchar(); bool positive = 1;
    for (; !isdigit(ch); ch = getchar())	if (ch == '-')	positive = 0;
    for (; isdigit(ch); ch = getchar())	x = x * 10 + ch - '0';
    return positive ? x : -x;
}
inline void write(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writesp(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
    printf(" ");
}
inline void writeln(int a){
    if(a<0){
    	a=-a; putchar('-');
    }
    write(a); puts("");
}

int n,m,x,y,now,f[N<<1][22],Left,ans,nowans,tot;
struct sxy
{
	int first,second;
	bool operator < (const sxy b)const
	{
        return first<b.first;
    }
}a[N<<1];
multiset<pair<int,int> >S;

signed main()
{
	n=read(),m=read();
	for (int i=1;i<=m;i++)
	{
		x=read(),y=read();
		if (x<=y) a[++tot]={x,y},a[++tot]={x+n,y+n}; else a[++tot]={x,y+n};
	}
	sort(a+1,a+tot+1);
	now=0;
	for (int i=1;i<=tot;i++)
	{
		f[i][0]=i;
		S.insert({a[i].second,i});
		while (S.begin()->first<a[i].first-1)
		{
			f[S.begin()->second][0]=now;
			S.erase(S.begin());
		}
		if (a[i].second>a[now].second) now=i;
	}
//	for (int i=1;i<=tot;i++) cout<<f[i][0]<<endl;
	while (!S.empty())
	{
		f[S.begin()->second][0]=now;
		S.erase(S.begin());
	}
	for (int i=1;i<=21;i++)
	  for (int j=1;j<=tot;j++)
	    f[j][i]=f[f[j][i-1]][i-1];
	ans=INT_MAX;
	for (int i=1;i<=tot;i++)
	{
		Left=a[i].first;nowans=0;
		if (a[i].second-a[i].first+1>=n) ans=min(ans,1);
		x=i;
		for(int i=21;i>=0;i--)
        	if(a[f[x][i]].second-Left+1<n)
           		x=f[x][i],nowans+=1<<i;
        x=f[x][0];
        if (a[x].second-Left+1>=n) ans=min(ans,nowans+2);
    }
	if (ans==INT_MAX) puts("impossible"); else writeln(ans);
}
/*
100 7
1 50
20 60
50 70
60 80
70 90
80 20
90 40
*/
```

---

## 作者：RyexAwl (赞：6)

### 描述

给你一个周长为 $n$ 的圆，用 $k$ 条给定的弧去覆盖这个圆，要求在保证圆被完全覆盖的情况下用最少的弧覆盖。

### 数据范围

$n\in [3,10^6],k \in [1,10^6]$

### $\mathrm{Sol}$

#### 经典贪心模型

一个经典的问题：给 $k$ 条线段，要求用最少的线段去覆盖长度为 $n$ 的区间。

解决这个问题的算法也很简单：

维护线段集合 $S$ ，当前覆盖到的最右端点 $x$ 。

`greedy select:` 每次从线段集合中选取左端点小于等于 $x+1$ 右端点最大的线段去覆盖，若该条线段的右端点为 $y$ ，令 $x\gets y$ 。 

重复上述步骤直到区间全部被覆盖。

#### 经典模型的一个扩展问题与倍增优化

给定 $k$ 条线段，询问 $q$ 次，每次询问最少用多少条覆盖区间 $[l,r]$ 。

一个显然的 `brute force` 是对于每个询问 $x$ 初始为 $l-1$ 之后跑上面经典问题的贪心算法。

定义一轮 `greedy select` 为从线段集合中进行一次上面问题中的贪心选择。

可以发现固定一个起点，进行 $k$ 轮 `greedy select` 之后的 $x$ 是固定的。

那么可以考虑去倍增维护每个起点进行若干轮 `greedy select` 之后的 $x$ ，具体地：

令 $f[i][j]$ 为起点为 $i$ 进行 $2^j$ 轮 `greedy select` 之后的 $x+1$ 。

对于每个询问直接从大到小枚举第二维倍增查询即可。


#### 回归环形问题

首先，我们将题目中给定的所有弧分成两类：

* 对于覆盖点 $n$ 且覆盖 $1$ 的弧称为 “补弧”

* 对于除了 “补弧” 以外的弧称为 “正弧”

我们考虑将问题的状态空间，按选定 “正弧” 的左端点最小值分类。 

具体地，我们当前的问题是所有完全覆盖圆的方案中用弧最少的方案用了多少条弧。

我们将其分成若干个子问题： 所有完全覆盖圆且 **所用　“正弧”　的左端点最小为 $v$** 的方案中用弧最少的方案用了多少条弧。

那么对于这样的问题，我们就可以直接二倍延长，“破换成链”，枚举右端点去处理序列上的问题。

具体地：对于所有的 “补弧”，我们将其看成是一条 $[l,n+r]$ 的线段，其中 $l>r$ 。

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl
#define PII std::pair<int,int>

namespace wxy{

const int N = 3e6 + 10;

int n,k,f[30][N],d[N],s[N];

PII seg[N];

inline int query(int l,int r){
    int ans = 0;
    per(i,25,0)
        if (f[i][l] < r + 1){
            ans += 1 << i;
            l = f[i][l];
        }
    return (ans + 1);
}

inline void solve(){
    int q = 0,r = -1;
    rep(i,1,2*n){
        while (seg[q + 1].fi <= i && q + 1 <= k) {q++; r = std::max(r,seg[q].se);}
        f[0][i] = r + 1;
    }
    rep(i,1,25)
        rep(j,1,2*n)  f[i][j] = f[i-1][f[i-1][j]];
    int ans = k;
    rep(r,n,2*n){
        int l = r - n + 1;
        ans = std::min(ans,query(l,r));
    }
    prt << ans;
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    gin >> n >> k;
    rep(i,1,k){
        int x,y; gin >> x >> y;
        if (x > y) y += n; d[x]++; d[y + 1]--;
        seg[i].fi = x; seg[i].se = y;
    } std::sort(seg + 1,seg + 1 + k);
    rep(i,1,2*n) d[i] += d[i-1];
    rep(i,1,2*n) {
        s[i] = s[i-1];
        if (d[i] > 0) s[i]++;
    }
    bool ck = false;
    rep(r,n,2*n)
        if (s[r] - s[r - n] == n) {
            ck = true; break;
        }
    if (!ck) {prt << "impossible"; return;}
    solve();
}

}signed main(){wxy::main(); return 0;}
```



---

## 作者：meyi (赞：3)

看到环上问题，首先想到断环为链，把线段复制一遍，转化为序列上的问题。本题转化后就是一个经典的线段覆盖问题，一个显然的贪心是每条线段拓展时都拓展到它能到达的右端点最大的线段，因为完全覆盖相当于 $r-l+1\ge n$，而左端点 $l$ 是固定的，那么右端点 $r$ 一定越大越好。于是以这种方式倍增求解即可。

需要注意的就是线段 $i$ 能拓展到线段 $j$ 的条件是 $r_i+1\ge l_j$ 而非 $r_i\ge l_j$。

时间复杂度 $O(n\log n)$。

实现细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=2e6+10;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
int ans=INT_MAX,f[21][maxn],k,m,n,pre[maxn];
typedef pair<int,int> pii;
#define fi first
#define se second
vector<pii>a,v;
#define pb push_back
inline bool cmp(const pii &x,const pii &y){
	return x.fi!=y.fi?x.fi<y.fi:x.se>y.se;
}
inline int half(int k){
	ri l=0,r=a.size()-1,ret=a.size()-1;
	while(l<=r){
		ri mid=l+r>>1;
		if(a[mid].fi<=k)ret=mid,l=mid+1;
		else r=mid-1;
	}
	return ret;
}
int main(){
	scanf("%d%d",&n,&k);
	while(k--){
		ri x,y;
		scanf("%d%d",&x,&y);
		if(x>y)y+=n;
		else v.pb({x+n,y+n});
		v.pb({x,y});
	}
	sort(v.begin(),v.end(),cmp);
	for(ri i=0;i<v.size();++i){
		if(i&&v[i].fi==v[i-1].fi)continue;
		if(v[i].se-v[i].fi+1>=n)return putchar(49),0;
		a.pb(v[i]);
	}
	for(ri i=1;i<a.size();++i)pre[i]=(a[pre[i-1]].se>a[i].se?pre[i-1]:i);
	for(ri i=0;i<a.size();++i)f[0][i]=pre[half(a[i].se+1)];
	ri lg=log2(a.size());
	for(ri i=1;i<=lg;++i)
		for(ri j=0;j<a.size();++j)
			f[i][j]=f[i-1][f[i-1][j]];
	for(ri i=0;i<a.size();++i){
		ri cnt=2,tmp=i;
		for(ri j=lg;~j;--j)
			if(a[f[j][tmp]].se-a[i].fi+1<n)
				cnt+=(1<<j),tmp=f[j][tmp];
		if(a[f[0][tmp]].se-a[i].fi+1>=n)ckmin(ans,cnt);
	}
	if(ans==INT_MAX)puts("impossible");
	else printf("%d",ans);
	return 0;
}
```


---

## 作者：快斗游鹿 (赞：2)

先考虑链的情况。显然是个贪心，每次找到左端点符合条件的、右端点最远的线段覆盖即可。对于环，可以想到断环成链。但如果对于每个长度为 $n$ 的区间都跑一遍贪心，肯定超时。所以想到要使用倍增优化，设 $f_{i,j}$ 表示从点 $i$ 开始，跳 $2^j$ 步能到达的最远的点。则有 $f_{i,j}=f_{f_{i,j-1},j-1}$。这样可以每次枚举起点，并 $O(\log k)$ 查询能覆盖到的最远终点。最后判断并输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
struct Node{
	int l,r;
}a[N];
int n,k,f[N][22],ans=1e9;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(Node xxx,Node yyy){
	return xxx.l<yyy.l;
}
int main(){
	freopen("std.in","r",stdin);
	n=read();k=read();
	for(int i=1;i<=k;i++){
		a[i].l=read();a[i].r=read();
		if(a[i].l>a[i].r)a[i].r+=n;	
	}
	sort(a+1,a+1+k,cmp);
	int now=1,r=0;
	for(int i=1;i<=2*n;i++){
		while(now<=k&&a[now].l<=i){
			r=max(r,a[now].r+1);
			now++;
		}
		f[i][0]=r;
	}
	for(int j=1;j<=20;j++){
		for(int i=1;i<=2*n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		int x=i,sum=0;
		for(int j=20;j>=0;j--){
			if(f[x][j]-i<n){
				//cout<<x<<" "<<j<<" "<<f[x][j]<<endl;
				x=f[x][j];sum+=(1<<j);
			}
		}
		x=f[x][0];sum++;
		//cout<<i<<" "<<x<<endl;
		if(x-i>=n)ans=min(ans,sum);
	}
	if(ans==1e9)puts("impossible");
	else cout<<ans;
	return 0;
}


```


---

## 作者：FangZeLi (赞：2)

## Link

[[ICPC2014 WF]Surveillance](https://www.luogu.com.cn/problem/P6902)

## Solution

好题，挖了挖我们最熟悉的贪心区间覆盖。

铃酱的讲解已经很清楚了，我主要来简单补充一下实现的问题：

首先这个算法的思路是预处理出 $f_{i,j}$ 表示从 $i$ 起再取 $2^j$ 个区间能覆盖到的最右边的点。这样的话，就可以运用倍增算法快速求出覆盖 $(l,r)$ 需要到的区间数。

然后再断环为链，利用另一个结论：最优的覆盖包含最多包含一个包括断点的区间，然后就可以枚举取的那个区间，然后把查询没覆盖到的部分（具体可以看铃酱的讲解）。

我来讲一下实现的时候要注意的细节：

1. 区间用左开右闭。这可以让区间有可合并性，无论是预处理还是查询的时候都可以少一些细节。

2. 注意区间类型的判断，一定要记得把跨过断点的区间拆成两段加入，不能忘了。同时，相应的数组要开两倍，不然会爆。

3. 注意下无解的处理。理论上直接判也可以，我是直接返回了 $\infin$，这样细节会少一点。

其他的细节就看一看代码吧。~~自认为实现的还不错~~

## Code

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>

#define _N 1000010
#define _LOGN 22

#define _INF 0x3f3f3f3f

struct Range {
	int l, r;
	Range() {
		l = r = 0;
	}
	Range(int x, int y) {
		l = x, r = y;
	}
};

bool operator <(const Range& left, const Range& right) {
	return left.l < right.l || (left.l == right.l && left.r < right.r);
}

int ans = 0;

int lgk, n, k;

int ccnt = 0, rcnt = 0;
int cirl[_N], cirr[_N];
Range rgs[_N << 1];

int f[_N][_LOGN];

int query(int l, int r) {
	if (l == r) {
		return 0;
	}
	int res = 0, cur = l;
	for (int i = lgk; i >= 0; i--) {
		if (f[cur][i] < r) {
			cur = f[cur][i];
			res += (1 << i);
		}
	}
	if (cur < r) {
		cur = f[cur][0];
		res++;
	}
	return cur >= r ? res : _INF;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (x <= y) {
			rgs[++rcnt] = Range(x, y + 1);
		} else {
			cirl[++ccnt] = y + 1; 
			cirr[ccnt] = x;
			rgs[++rcnt] = Range(1, y + 1);
			rgs[++rcnt] = Range(x, n + 1);
		}
	}
	lgk = log2(rcnt);
	std::sort(rgs + 1, rgs + rcnt + 1);
	for (int l = 1, mxr = 0, pt = 1; l <= n; l++) {
		while (pt <= rcnt && rgs[pt].l <= l) {
			mxr = std::max(mxr, rgs[pt].r);
			pt++;
		}
		f[l][0] = mxr;
	}
	f[n + 1][0] = n + 1;
	for (int t = 1; t <= lgk; t++) {
		for (int l = 1; l <= n + 1; l++) {
			f[l][t] =  f[f[l][t - 1]][t - 1];
		}
	}
	ans = query(1, n + 1);
	for (int i = 1; i <= ccnt; i++) {
		ans = std::min(ans, query(cirl[i], cirr[i]) + 1);
	}
	if (ans == _INF) {
		puts("impossible");
	} else {
		printf("%d\n", ans);
	}
	return 0;
}
```

## Insipration

我认为这题还是比较巧妙的，尤其是倍增对于原贪心算法的扩展。

核心结论：

1. 倍增可以优化经典的覆盖算法。
2. 区间设左开右闭可以优化很多细节。

---

## 作者：tai_chi (赞：1)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18441961) 中阅读。

考虑弱化版链怎么做，每次选取左端点在当前位置前面的线段，跳到其中最大的右端点，可以维护一个数组表示起点为 $i$ 的目标位置，可以做到 $O(n+k)$。

考虑多次询问一段区间 $[l,r]$ 的答案，这时如果暴力从 $l-1$ 开始跳是 $O(n^2)$ 的，只需要一个倍增数组即可 $O(\log n)$ 完成跳跃动作。

原题的做法也与之类似，一个处理环状问题的经典操作是复制一倍数组。这时对于复制后每个长度为 $n$ 的区间都代表原环上的一个循环置换，那通过上面的区间询问做法，可以对每个长度为 $n$ 的区间做询问，取答案最小值即为答案。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

typedef pair<int,int> pii;

const int N=1e6+5,LG=25;
int n,k;
pii a[N];
int f[N*2][LG];

signed main()
{
	IOS;
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>a[i].first>>a[i].second;
		if(a[i].first>a[i].second) a[i].second+=n;
	} 
	sort(a+1,a+k+1);
	int r=0,tot=0;
	for(int i=1;i<=n*2;i++)
	{
		while(tot+1<=k&&a[tot+1].first<=i)
			r=max(r,a[++tot].second+1);
		f[i][0]=r;
	}
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n*2;i++) 
			f[i][j]=f[f[i][j-1]][j-1];
	int ans=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
	{
		int p=i,res=0;
		for(int j=20;j>=0;j--)
		{
			if(f[p][j]<i+n) 
				p=f[p][j], res+=(1<<j);
		}
		res++, p=f[p][0];
		if(p>=i+n) ans=min(ans,res);
	}
	if(ans>=0x3f3f3f3f) cout<<"impossible"<<endl;
	else cout<<ans<<endl;
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
首先我们考虑定义一个基于贪心的状态为 $f_{i,j}$ 表示所选的区间包含 $i$ 一共选了 $j$ 个区间能到达的最大的右端点，然后我们发现这样是 $n^2$ 的所以考虑用倍增进行优化，$f_{i,j}$ 表示所选的区间包含 $i$ 一共选了 $2^j$ 个区间能到达的最大的右端点，转移与普通的倍增相同 $f_{i,j}=f_{f_{i,j-1},j-1}$。然后我们考虑如何统计答案，发现如果固定必须要包含的区间 $l\sim r$ 就可以求出最少用的区间了，所以我们考虑去枚举左端点 $i$ 然后能算出他需要覆盖到的地方为 $i+n$（因为当区间是左闭右开时会更好转移所以考虑将区间的右端点整体右移一个） 然后我们就可以去暴力跳看是否满足条件，最后我们只需要判断当前到的点 $x$ 完后跳一个区间是否能跳到 $i+n$ 及以后就行了。

又因为这道题有 $l>r$ 的情况所以我们考虑将一天变为两天即可。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,m;
const int N=4e6+10;
int f[N][22],tot;
int s[N],e[N],idx;
vector<pair<int,int>>v;
void solve() {
	in(m),in(n);
	rep(i,1,n) {
		in(s[i]),in(e[i]);
		if(s[i]>e[i]) e[i]+=m,v.pb({s[i],e[i]});
		else {
			v.pb({s[i],e[i]});
		}
	}
	for(auto to:v) {
		f[to.first][0]=max(f[to.first][0],to.second+1);
	}
	idx=2e6;
	int res=INT_MAX;
	rep(i,1,idx) f[i][0]=max(f[i][0],f[i-1][0]);
	rep(j,1,21) {
		rep(i,1,idx) f[i][j]=f[f[i][j-1]][j-1];
	}
	rep(i,1,idx) {
		int r=false,x=i;
		if(idx<i+m) break;
		rep1(j,21,0) {
			if(f[x][j]<i+m) {
				x=f[x][j];
				r+=(1<<j);
			}
		}
		if(f[x][0]>=i+m) r++;
		else continue;
		res=min(res,r); 
	}
	if(res==INT_MAX) puts("impossible");
	else printf("%lld\n",res);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```
还有一道 [双倍经验](https://www.luogu.com.cn/problem/UVA1707)。

---

## 作者：cmrhhh (赞：1)

# [P6902 [ICPC2014 WF] Surveillance](https://www.luogu.com.cn/problem/P6902)
## 题目大意：
给出长度为 $n$ 的环和 $k$ 个线段（连续的点的序列），问要覆盖环最少的线段个数，不存在输出 impossible 。
## 分析：
1.处理环可以使用**断环为链**的手法，即把环断成 $2\times n$ 的链   
2.考虑暴戾，即枚举**左端点**，记录区间长度大于等于 $n$ 时的线段个数，显然复杂度 $O(nk)$ 。  
3.考虑优化，**注意到**每个左端点要到的右端点是一定的，因此可以考虑预处理，这里使用倍增处理 $f[i][j]$ ，表示在 $i$ 位置往后覆盖 $2^j$个线段的最远的点 。复杂度约为一个带常数的 $O(n)$ ，排序 $O(n\log{n})$ 。最后枚举左端点，右端点的寻找需要 $O(\log{n})$ ，最后处理的时间复杂度为 $O(n\log{n})$ ，复杂度瓶颈 $O(n\log{n})$ 。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e6+10;
int n,k;
int f[MAXN][22],ans=INT_MAX;//f[i][j] 在i位置往后覆盖2^j个线段的最远的点 
struct edge{
	int l,r;
}a[MAXN+10];
bool cmp(edge z,edge x){return z.l<x.l;}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=k;++i){
		cin>>a[i].l>>a[i].r;
		if(a[i].l>a[i].r)a[i].r+=n;//断环为链 
	}
	sort(a+1,a+1+k,cmp);//按l排序 
	int nw=1,r=0;
	//预处理f[i][j] 
	for(int i=1;i<=2*n;++i){ 
		while(nw<=k&&a[nw].l<=i)r=max(r,a[nw].r+1),nw++;//+1为自动到下一个线段 
		f[i][0]=r;
	}
	for(int j=1;j<=21;j++)//倍增 
		for(int i=1;i<=2*n;++i)
			f[i][j]=f[f[i][j-1]][j-1];
	
	for(int i=1;i<=n;++i){
		int nw=i,sum=0;
		for(int j=21;j>=0;--j)
			if(f[nw][j]-i<n)//多+1了 此处不加了 
				sum+=(1<<j),nw=f[nw][j];
		nw=f[nw][0];
		++sum;
		if(nw-i>=n)ans=min(ans,sum);
	}
	ans==INT_MAX?cout<<"impossible":cout<<ans;
	return 0;
} 
//参考题解：https://www.luogu.com.cn/article/bbwfcwak 
```

---

## 作者：SunnyYuan (赞：1)

## 思路



首先，它是一个环，不好处理，我们可以断环为链，所有区域也都复制一遍，我们设 $f_{i, j}$ 为从 $i$ 开始走 $2^j$ 个区域可以到达的最大值，那么有 $f_{i, j} = f_{f_{i, j - 1} + 1, j - 1}$，即我们可以先从 $i$ 跳 $2^{j - 1}$ 步到 $f_{i, j - 1}$，然后再从 $f_{i, j - 1} + 1$ 跳 $2^{j - 1}$ 个区域跳到最大值。

然后，我们对于每一个 $i$ 试探其要跳到 $i + n - 1$ 需要的最小步骤 $step$，我们可以像倍增求 $LCA$ 一样不断试探，从大到小枚举 $j$，如果当前位置 $cur$ 再往前走 $2^j$ 个区域没有跨过 $i + n - 1$，即 $f_{cur + 1, j} < i + n - 1$，那么让 $cur \leftarrow f_{cur + 1, j}$，试探完成后再让 $step \leftarrow step + 1$，跨过 $i + n - 1$。

最后，我们要谈一谈怎么初始化，这个问题虽然比较小，但是也还是拿出来说一说，就是我们先将所有的区域按左端点排序，接着我们用 $i$ 从 $1$ 枚举到 $n$，然后所有区域中左端点 $l \le i$ 的区域右端点最大值可以作为 $f_{i, 0}$，表示其走一步可以到达的最大点，因为枚举的 $i$ 和区域的左端点都是单调不减的，所以双指针可以在 $O(n)$ 内完成。

总时间复杂度：$O(n \log n)$。

## 代码

注意：

1. 在程序中，为了提速，我将 $f_{i, j}$ 换成了 $f_{j, i}$。
2. 如果有一个区域 $l > r$，那么将 $r \leftarrow r + n$。

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: P6902 [ICPC2014 WF] Surveillance
| OJ:      Luogu
| URL:     https://www.luogu.com.cn/problem/P6902
| When:    2023-11-01 14:14:05
| 
| Memory:  1 GB
| Time:    4000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;
using PII = pair<int, int>;

const int N = 2000010, INF = 0x3f3f3f3f, K = 22;

int f[K][N];
int n, m;
PII a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int cnt = m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i].first >> a[i].second;
        if (a[i].first > a[i].second) a[i].second += n;
        else a[++cnt] = {a[i].first + n, a[i].second + n};
    }
    sort(a + 1, a + cnt + 1);

    int l = 0, maxx = 0;
    for (int i = 1; i <= (n << 1); i++) {
        while (l + 1 <= cnt && a[l + 1].first <= i) maxx = max(maxx, a[++l].second);
        f[0][i] = maxx;
    }

    for (int j = 1; j < K; j++)
        for (int i = 1; i <= (n << 1); i++)
            if (f[j - 1][i] + 1 <= (n << 1) && f[j - 1][i])
                f[j][i] = f[j - 1][f[j - 1][i] + 1];

    int ans = INF;
    for (int i = 1; i <= n; i++) {
        int k = i - 1, step = 0;
        for (int j = K - 1; j >= 0; j--) {
            if (f[j][k + 1] < i + n - 1 && f[j][k + 1]) {
                k = f[j][k + 1];
                step |= (1 << j);
            }
        }
        if (f[0][k + 1] >= i + n - 1) step++;
        else step = INF;
        ans = min(ans, step);
    }
    if (ans == INF) cout << "impossible\n";
    else cout << ans << '\n';
    return 0;
}

```

---

## 作者：TLE_AK (赞：0)

### 题意
给予一个长度为 $n$ 的环与可选择的 $k$ 个区域，求至少选多少个区域才能覆盖这个环。
## 思路
根据贪心的思路，对于一个区间 $[l,r]$ 相交的所有区间 $[l_i,r_i]$ 一定是选 $r_i$ 最大的。  
证明也很简单：在代价相等的情况下，因为大的区间可以覆盖小的区间，所以选大的区间肯定更赚。

对于环上一个点 $i$ 我们设下个选择最赚的区间标号为 $next_i$，然后在跳到 $[r_{next_i}]$ 继续即可。  
考虑倍增优化过程，这题就做完了。
### 代码
```
#include<bits/stdc++.h>
using namespace std;

namespace acac
{
	struct node
	{
		int l,r;
	}A[1000010];
	int dp[2000010][30];
	
	bool cmp(node a,node b)
	{
		if(a.l==b.l)return a.r>b.r;
		return a.l<b.l;
	} 


	int main()
	{
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=k;i++)
		{
			scanf("%d%d",&A[i].l,&A[i].r);
			if(A[i].l>A[i].r)A[i].r+=n;//断环为链
			
		}
		sort(A+1,A+1+k,cmp);//排序便于处理
		int w=1,maxn=0;//类似双指针处理max
		for(int i=1;i<=2*n;i++)
		{
			while(w<=k&&A[w].l<=i)
			{
				maxn=max(maxn,A[w].r+1);
				w++;
			}
			dp[i][0]=maxn;
		}
      /倍增处理
		for(int j=1;j<=20;j++)
		{
			for(int i=1;i<=2*n;i++)
			{
				dp[i][j]=dp[dp[i][j-1]][j-1];
			}
		}
		long long ans=1e9;
		for(int i=1;i<=2*n;i++)//枚举起点
		{
			long long num=0,u=i;
			for(int j=20;j>=0;j--)
			{
				if(dp[u][j]-i>=n)continue;
				num+=(1<<j);
				u=dp[u][j];
				
			}
			num++;
			u=dp[u][0];
			if(u-i>=n)ans=min(ans,num);
		}
		if(ans==1e9)cout<<"impossible";
		else cout<<ans;
		return 0;
	}
}

int main()
{
	acac::main();
	return 0;
}
```

---

## 作者：int_R (赞：0)

随到的，水一篇。

先把环拉直，把跨过了环原点即 $r_i<l_i$ 的区间的 $r_i\gets r_i+n$，然后再在后面复制出来一个区间 $[l_i+n,r_i+n]$。

先按左端点升序排序，同一左端点只需要取最大右端点，显然如果一个右端点不是前缀最大值就是无意义的，因为被一个更大区间包含了，所以直接去掉，之后右端点也单调递增。

选择一个区间 $i$ 以后下一个选择的区间一定是最大的 $j$ 满足 $l_j\leq r_i+1$，记 $j$ 是 $i$ 的后继区间。由于左右端点都单调递增直接双指针求出每个区间 $i$ 的后继区间即可。

这样就形成了一个森林，每个区间的父亲是这个区间的后继区间。要对于树上每个节点 $i$ 找到深度最大的祖先 $j$ 满足 $r_j\geq l_i+n-1$，树上倍增即可。

要特判答案为 $1$ 的情况，总时间复杂度 $O(n\log n)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=2e6+10,INF=1e9;
int n,k,tot,pre,ans=INF;bool vis[MAXN];
struct node{int l,r;}a[MAXN];vector <int> v[MAXN];
int dep[MAXN],fa[MAXN],f[MAXN][21];
inline bool cmp(node x,node y)
    {return (x.l==y.l)?x.r>y.r:x.l<y.l;}
inline int find(int x,int num)
{
    for(int i=__lg(dep[x]);~i;--i)
        if(a[f[x][i]].r<num) x=f[x][i];
    x=f[x][0];return x?dep[x]:-INF;
}
void dfs(int x)
{
    dep[x]=dep[fa[x]]+1,f[x][0]=fa[x];
    for(int i=1;i<=__lg(dep[x]);++i)
        f[x][i]=f[f[x][i-1]][i-1];
    ans=min(ans,dep[x]-find(x,a[x].l+n-1)+1);
    for(int y:v[x]) dfs(y);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>k;for(int i=1;i<=k;++i)
    {
        cin>>a[i].l>>a[i].r,a[i].r+=(a[i].r<a[i].l)*n;
        if(a[i].r==a[i].l+n-1) ans=1;
    }
    sort(a+1,a+1+k,cmp);
    for(int i=1;i<=k;++i)
        if(a[i].r>pre) pre=a[i].r,a[++tot]=a[i];
    k=tot;for(int i=1;i<=k;++i)
        if(a[i].r+n>pre) pre=a[i].r+n,
            a[++tot]={a[i].l+n,a[i].r+n};
    k=tot;for(int l=1,r=0;l<=k;++l)
    {
        while(r<k&&a[r+1].l<=a[l].r+1) ++r;
        if(r>l) fa[l]=r;v[fa[l]].push_back(l);
    }
    a[0].r=INF;for(int root:v[0]) dfs(root);
    if(ans==INF) cout<<"impossible\n";
    else cout<<ans<<'\n';return 0;
}
```

---

## 作者：Zkl21 (赞：0)

最近在写题的时候刷到两道思路较为相似的题(~~经验题~~)，大体都是倍增+贪心，于是蒟蒻挑着时间来总结一下。

## [P4155 国旗计划](https://www.luogu.com.cn/problem/P4155)

### 题意

借用一下学长讲课时的题目介绍。
>一个 $m$ 个点的环，有 $n$ 条线段，可覆盖在环上 $[c_i,d_i]$ 的部分，保证线段之间不会互相包含，对 $1\le i\le n$问强制选择线段 $i$ 时，最少选择多少条线段可以覆盖整个环。

>数据范围:$n\le 2\times 10^5,m<10^9$。

### 思路

首先，对于环问题，我们可以套路的考虑将原来的环化成二倍长度的链，这样题目就能够转化成区间覆盖问题了。

考虑当选择了一条线段 $i$ 后，对于下一个加入的线段有哪些限制。假设线段 $i$ 的右端点为 $r_i$，那么下一个线段必须要满足：
当前线段要能够与下一个线段覆盖的区间有交集，即 $r_i\ge l_j$。

满足如上条件后，才能保证我们可以选这条线段，但是可能有很多条线段可供选择，到底选哪一条呢?

不难看出，我们贪心的选择合法的所有线段中，能到达的范围最远的，即 $r$ 最大的。这样的话，可以保证我们的决策是最优的。

虽然这样，我们的时间复杂度仍然不足以通过本题，我们可以使用一样东西来优化我们的过程：**倍增**。

我们设 $f_{i,j}$ 表示从第 $j$ 个位置开始跳到往后第 $2^i$ 条线段的最远点，显然可以预处理出来 $f$ 数组，这样我们就可以每次 $\log n$ 求出每次操作的解。

### 实现

信息开一个结构体存储左右边界和线段的编号。

我们可以先根据每条线段的 $l$ 进行升序排序，再用双指针的思想找到合法范围内能跳的更远的线段。

根据 $n\le 2\times 10^5$，可知 $f$ 数组只要开到 $\log_22\times10^5\approx 18$ 即可。

注意边界问题。

貌似还有 $O(n)$ 做法，请移至[FlashHu 大佬的博客](https://www.luogu.com.cn/blog/flashblog/solution-p4155)。

代码就不放了，~~太占地~~。

## [P6902 [ICPC2014 WF] Surveillance](https://www.luogu.com.cn/problem/P6902)

~~严重怀疑 SCOI2015 借鉴 ICPC2014 WF~~。

### 题意

与上一题类似，唯一不同之处就是不保证环能被完全覆盖。

数据范围：$3\le n\le 10^6$，$1\le k\le 10^6$。

### 思路

一个小细节：注意本题的每两条相邻线段可以不相交，但是必须相邻。在本题中，样例 3 是有解的，但是如果在上一题，样例 3 是不合法的数据。

剩下的与上题类似。我们还是破环成链，排序，预处理 $f$ 数组，每个点倍增跳父亲，处理合法结果即可。

时间复杂度应该是 $O(n\log n)$。

### 实现及代码

本题可以考虑使用 pair 存储所有节点，pair 自带比较函数可以不用再手写 cmp 函数，$f$ 数组开到 $20$ 就够了。

注意边界问题。

[参考代码](https://www.luogu.com.cn/paste/hf6zfonb)

后话：

本文是蒟蒻当天集训完后抽时间写的一篇题解。由于学习时间较短，可能内容有待完善，一些错误仅凭蒟蒻难以避免，还望各位大佬指出，蒟蒻不胜感激。

---

