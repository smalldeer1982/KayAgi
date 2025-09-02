# [ABC216G] 01Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc216/tasks/abc216_g

`0` と `1` のみからなる長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ であって、以下の条件を満たすものを考えます。

> すべての $ i=1,2,\dots,M $ について、$ A_{L_i}, A_{L_i+1},\dots\ ,A_{R_i} $ に `1` が $ X_i $ 個以上含まれる

条件を満たす数列 $ A $ のうち、含まれる `1` の数が**最も少ない**例を $ 1 $ つ出力してください。

なお、制約のもとで条件を満たす数列 $ A $ は必ず存在します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min(2\ \times\ 10^5,\ \frac{N(N+1)}{2}\ ) $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ 1\ \leq\ X_i\ \leq\ R_i-L_i+1 $
- $ i\ \neq\ j $ ならば $ (L_i,R_i)\ \neq\ (L_j,R_j) $
- 入力は全て整数

### Sample Explanation 1

`1 1 0 1 1 0` などの答えも正解です。 `0 1 1 1 1 1` などの答えは含まれる `1` の数が最小化されていないので、不正解です。

## 样例 #1

### 输入

```
6 3
1 4 3
2 2 1
4 6 2```

### 输出

```
0 1 1 1 0 1```

## 样例 #2

### 输入

```
8 2
2 6 1
3 5 3```

### 输出

```
0 0 1 1 1 0 0 0```

# 题解

## 作者：fjy666 (赞：9)

萌萌差分约束题。设 $c_i$ 为 $1\sim i$ 中 $0$ 的个数。  
则建边相当于满足下面两个条件
- $0\le c_i-c_{i-1}\le 1$
- $c_{r_i}-c_{l_i-1}\le r_i-l_i+1-x_i$

建好边之后由于边权都为正数可以直接跑 dij。  
[submission](https://atcoder.jp/contests/abc216/submissions/36664745)

---

## 作者：ivyjiao (赞：6)

upd on 2024-10-7：修正了一处事实错误：将 SPFA 转化为 dijkstra 时的式子应为小于号；对于为什么跑最短路的解释也有错误，已修正。

---

七倍经验：P1250，P1645，P1986，P10934，SP116，UVA1723，AT_abc216_g。

差分约束是一种特殊的 $n$ 元一次不等式，包含 $n$ 个变量及 $m$ 个约束式子，每个约束式子由两个变量作差构成，每个式子形如 $a_i-a_j\geq k$，$k$ 是常数，$1\leq i,j\leq n$。

而我们看本题，我们先对我们选完的数列进行一个前缀和 $s_i=\sum_{j=1}^{j\leq i} d_j$，$d$ 中 $1$ 表示选了，$0$ 表示没选，那么本题对于每个限制，很明显有个式子 $s_{b_i}-s_{a_i-1}\geq c_i$，我们把每个 $i$ 抽象成一个节点，那么这就是一个差分约束了，跑一遍 SPFA 求最长路来求解。

然而这样是错的，由于前缀和的性质，$s_i \geq s_{i-1}$，因为每个数只能选一次，所以 $s_i-s_{i-1}$ 要么为 $0$，要么为 $1$，由此我们得到：$s_i-s_{i-1}\geq 0,s_{i-1}-s_i\geq -1$。

为了防止下标出现负数，我们把下标统一 $+1$。

最后输出所有 $dis_i-dis_{i-1}$ 就行。

但是，在前六倍经验中，我们是这样写的：

> 在一次 SPFA 的松弛操作后，$dis_v-dis_u\geq w$，与不等式 $s_{b_i}-s_{a_i-1}\geq c_i$ 性质一样，所以 SPFA 可以求出最小值，又因为解不等式同大取大原则，所以要求出最长路。

然而这题 SPFA 被卡得 SPFA 了，我们考虑能不能转化成 dijkstra 的形式？

直接转肯定是不行的，我们发现式子中有一个 $s_{i-1}-s_i\geq -1$，而 dijkstra 的边权不能为负数。

我们考虑把这个东西原来是统计 $1$ 的，改成统计 $0$，那么本题的式子就变成了：$s_{b_i}-s_{a_i-1}\leq b_i-a_i+1-c_i,s_i-s_{i-1}\leq 1,s_{i-1}-s_i\leq 0$，由于解不等式同小取小原则，所以改成统计 $0$ 之后要求最短路，最后输出方案的时候把答案取反就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,u,v,w,dis[200002],maxn;
bool vis[200002];
vector<PII>G[200002];
priority_queue<PII,vector<PII>,greater<PII> >q;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        G[u].push_back({v-u+1-w,v+1});
    }
    for(int i=0;i<=n;i++){
        G[i+1].push_back({0,i});
        G[i].push_back({1,i+1});
    }
    memset(dis,0x3f,sizeof dis);
    dis[0]=0;
    q.push({0,0});
    while(q.size()){
        int u=q.top().se;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=0;i<G[u].size();i++){
            if(dis[G[u][i].se]>dis[u]+G[u][i].fi){
                dis[G[u][i].se]=dis[u]+G[u][i].fi;
                q.push({dis[G[u][i].se],G[u][i].se});
            }
        }
    }
    for(int i=2;i<=n+1;i++) cout<<!(dis[i]-dis[i-1])<<" ";
}
```

---

## 作者：CrTsIr400 (赞：3)

之前写过一篇 [P1250 最优时间复杂度做法](https://www.luogu.com.cn/blog/SmallTualatin/P1250-sol)，现在一看，不就是种树的加强版吗。

首先，确定算法流程：（之前贪心正确性之类的证明就不讲了）

+ 把所有要求按照右端点从小到大排序。
+ 查询该要求所属的区间内被填的数数量。
+ 如果不够，就从右往左寻找空位，给这些空位填数。因为从右往左肯定更优。

具体而言，使用平衡树维护一个集合，这个集合代表还能没被填的位置。

查询区间 $[l,r]$ 的时候，我们就查询 $r$ 的排名和 $l-1$ 的排名之差，维护这段区间 $0$ 的个数，就可以求得 $1$ 的个数了；

从某个位置开始，从右往左寻找第一个空位，我们就寻找这个位置的前驱即可。

把 $0$ 变成 $1$ 就只需要删除即可。

时间复杂度：$O((n+m)\log n)$，因为每个数最多只会被删除一次。

采用 `__gnu_pbds::tree` 实现，常数略大。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i=a;i<=b;++i)
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;using I=int;
using namespace __gnu_pbds;tree<I,null_type,less<I>,rb_tree_tag,tree_order_statistics_node_update>s;
const I N=200010;
I n,m,l[N],r[N],w[N],id[N],ans;
bool bz[N];
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	fo(i,1,n)s.insert(i);
	fo(i,1,m)cin>>l[i]>>r[i]>>w[i],id[i]=i;
	sort(id+1,id+m+1,[=](I a,I b){return r[a]<r[b];});
	fo(i,1,m){I L=l[id[i]],R=r[id[i]],W=w[id[i]],
		t=(R-L+1)-(s.order_of_key(R+1)-s.order_of_key(L));
		auto it=s.upper_bound(R);
		if(it==s.begin())continue;
		--it;
		while(t<W){
			++t;++ans;
			if(it==s.begin()){s.erase(it);break;}
			--it;s.erase(next(it));
		}
	}for(I i:s)bz[i]=1;
	fo(i,1,n)printf("%d ",!bz[i]);
	return 0;
}
```



---

## 作者：CQ_Bob (赞：3)

## 分析

一道差分约束题。

我们令 $\mathit{sum}_{i}$ 表示 $1$ 到 $i$ 中，$1$ 的数量，根据题意可得：

1. $\mathit{sum}_{l_i-1}+x_i \le \mathit{sum}_{r_i}$
2. $\mathit{sum}_{l+1} +(-1)\le \mathit{sum}_{l}$
3. $\mathit{sum}_{l}+0 \le \mathit{sum}_{l+1}$

因为我们要尽可能地使 $1$ 的数量少，所以这是求不等式最小解。又因为边权有负，所以我们要跑 spfa 来求解，代码如下：

```cpp
//sum[l-1]+x<=sum[r]
//sum[l]<=sum[r]
//sum[r]+(-1)<=sum[l]
#include<bits/stdc++.h>
using namespace std;
#define int long long
#pragma G++ optimize(2)
int n,m;
const int N=1e6+10;
int ne[N],e[N],h[N],w[N],idx;
inline void add(int a,int b,int c){
	e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}
inline void read(int &x) {
	x=0;
	short flag=true;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x*=flag;
}
int l,r,x;
int dis[N],vis[N];
inline void spfa(){
	memset(dis,-0x3f,sizeof(dis));
	queue<int> qu;
	qu.push(0),dis[0]=0,vis[0]=1;
	while(!qu.empty()){
		int now=qu.front();
		qu.pop();
		vis[now]=0;
		for(int i=h[now];~i;i=ne[i]){
			int j=e[i];
			if(dis[j]<dis[now]+w[i]){
				dis[j]=dis[now]+w[i];
				if(!vis[j]){
					vis[j]=1;
					qu.push(j);
				}
			}
		}
	}
}
signed main(){
	memset(h,-1,sizeof(h));
	read(n),read(m);
	for(register int i=1;i<=m;i++){
		read(l),read(r),read(x);
		add(l-1,r,x);
	}
	for(register int i=0;i<n;i++){
		add(i,i+1,0);
		add(i+1,i,-1);
	}
	spfa();
	for(register int i=1;i<=n;i++){
		printf("%lld ",dis[i]-dis[i-1]);//前缀和
	}
	return 0;
}
```
很显然，$1 \le n,m \le 2 \times 10^5$，超时了。

我们考虑优化方法，可以使用正难则反的思想。如果我们我们令 $\mathit{sum'}_{i}$ 表示 表示 $1$ 到 $i$ 中，$0$ 的数量，那么再次根据题意就可以把上面的式子变成：

1. $\mathit{sum'}_{r_i}\le \mathit{sum'}_{l_i-1}+(r-l+1-x)$
2. $\mathit{sum'}_{l+1} \le \mathit{sum'}_{l} +1$
3. $\mathit{sum'}_{l} \le \mathit{sum'}_{l+1}+0$

很显然，在我们需要 $1$ 的数量最少时，该不等式方程组的解就需要最大，而所有的权值又是非负的，所以可以用 dijkstra 求出最短路。注意，求得的解是关于 $\mathit{sum'}_{i}$ 的，所以我们需要进行取反。

## 代码
```cpp
//sum[r]<=sum[l-1]+r-l+1-x
//sum[l]<=sum[l-1]+1
//sum[l-1]<=sum[l]+0
#include<bits/stdc++.h>
using namespace std;
#define int long long
#pragma G++ optimize(2)
#define PII pair<int,int>
#define x first
#define y second
int n,m;
const int N=1e6+10;
int ne[N],e[N],h[N],w[N],idx;
inline void add(int a,int b,int c){
	e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}
inline void read(int &x) {
	x=0;
	short flag=true;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x*=flag;
}
int l,r,x;
int dis[N],vis[N];
//inline void spfa() TLE
//	memset(dis,-0x3f,sizeof(dis));
//	queue<int> qu;
//	qu.push(0),dis[0]=0,vis[0]=1;
//	while(!qu.empty()){
//		int now=qu.front();
//		qu.pop();
//		vis[now]=0;
//		for(int i=h[now];~i;i=ne[i]){
//			int j=e[i];
//			if(dis[j]<dis[now]+w[i]){
//				dis[j]=dis[now]+w[i];
//				if(!vis[j]){
//					vis[j]=1;
//					qu.push(j);
//				}
//			}
//		}
//	}
//}
void dj(){
	memset(dis,0x3f,sizeof(dis));
	priority_queue<PII,vector<PII>,greater<PII> > qu;
	dis[0]=0,qu.push({dis[0],0});
	while(!qu.empty()){
		PII now=qu.top();qu.pop();
		if(vis[now.y]) continue;
		vis[now.y]=1;
		for(int i=h[now.y];~i;i=ne[i]){
			int j=e[i];
			if(dis[j]>now.x+w[i]){
				dis[j]=now.x+w[i];
				qu.push({dis[j],j});
			}
		}
	}
}
signed main(){
	memset(h,-1,sizeof(h));
	read(n),read(m);
	for(register int i=1;i<=m;i++){
		read(l),read(r),read(x);
        //add(l-1,r,x);
		add(l-1,r,r-l+1-x);
	}
	for(register int i=0;i<n;i++){
		//add(i,i+1,0);
		//add(i+1,i,-1);
        add(i,i+1,1);
		add(i+1,i,0);
	}
    //spfa();
	dj();
	for(register int i=1;i<=n;i++){
		printf("%lld ",(dis[i]-dis[i-1]==1?0:1));//取反，也可以用位运算
	}
	return 0;
}
```


---

## 作者：chenxi2009 (赞：2)

## 思路
贪心。[P1250](https://www.luogu.com.cn/problem/P1250) 加强版。

贪心思路：序列初始全为 0。把所有限制按右端点排序，依次采用选取区间内最靠右的 0 变为 1 的方式满足。这样每次选取的点会尽可能地在多个区间的交集。

考虑使用树状数组维护区间内 1 的个数，这样可以快速得知一个限制内还需要多少个 1。找寻最右端的 0 可以通过 set 维护。时间复杂度 $O((N+M)\log N)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r,x;
	bool friend operator < (const node &a,const node &b){
		return a.r < b.r;
	}
}; 
int n,m,c[200001];
node t[200001];
inline int lowbit(int x){
	return x & -x;
}
inline void upd(int x){
	for(;x <= n;x += lowbit(x)) c[x] ++;
	return;
}
inline int qry(int x){
	int rtn = 0;
	for(;x;x -= lowbit(x)) rtn += c[x];
	return rtn;
}
set<int>s;
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++) s.insert(i);//维护 0 的集合
	for(int i = 1;i <= m;i ++) scanf("%d%d%d",&t[i].l,&t[i].r,&t[i].x);
	sort(t + 1,t + m + 1);//限制排序
	for(int i = 1;i <= m;i ++){
		int num = qry(t[i].r) - qry(t[i].l - 1);//这段区间内已有 1 的个数
		if(num >= t[i].x) continue;
		num = t[i].x - num;//还需要 1 的个数
		for(int j = 1;j <= num;j ++){
			auto it = s.upper_bound(t[i].r);
			upd(*(-- it));//第一个超出范围的 0 左边就是最右边的范围内的 0，把它改为 1
			s.erase(*it);
		}
	}
	for(int i = 1;i <= n;i ++) printf("%d ",!s.count(i));//判断是否在 0 集合中
	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

一眼差分约束。设前 $i$ 个数里面 `1` 的数量为 $pre_i$。

那么限制 $(l,r,x)$ 相当于 $pre_r-pre_{l-1} \ge x$。我们当然想要求 $pre$ 的值，越小越好，因此要求**最长路**。

> 为什么最小解要求最长路？比如以上的式子，你可以写成 $pre_r - x \ge pre_{l-1}$ 然后跑最短路。看似是对的，但是最短路要求每个点都必须有存在一个前驱使得不等式取等。这样肯定构造了一组合法解，但是事实上一个点的 $pre$ 也许可以继续往下压使得没有一个不等式取等。因此最短路不可以。但是如果你写成 $pre_{l-1}+x \le pre_r$ 求最长路，那么这个 $pre_r$ 取到的必定是它能取到的最小值，因为再小一点就可能不满足一个不等式了。而且，每个点都是可能取到的最小值，所以每个点都一定虽最优的（不会出现牺牲后面让前面更小来满足字典序更小的情况）。综上，**求差分约束最小解要用最长路**

还有一些限制，类似 $pre_i \ge pre_{i-1}$ 和 $pre_i \le pre_{i-1}+1$。

你想跑最长路，结果发现有正权边，不能用 Dijkstra，但是这题卡 SPFA（我记得日本人不卡算法来着）。那么想办法把它变为负权边。

考虑设 $pre'_i=pre_i-i$。那么最危险的第一个不等式可以化为 $pre'_r+r-pre'_{l-1}-l+1 \ge x$。也就是 $pre'_{l-1}+x-(r-l+1) \le pre'_r$。因为有解，所以 $r-l+1 \ge x$。所以边权都是负的。可以使用 Dijsktra 了。

[code](https://atcoder.jp/contests/abc216/submissions/43282717)

---

## 作者：SunsetSamsara (赞：1)

## ABC216G 01Sequence

### 题意

你需要构造出一个长度为 $n$ 的 $01$ 序列，满足 $m$ 个限制 $(l_i,r_i,x_i)$：在 $[l_i,r_i]$ 这段区间内，序列上 $1$ 的个数不小于 $x_i$。你需要保证你的方案中包含 $1$ 的个数最小。

### 标签

图论，差分约束 | 思维，贪心

### 做法

#### 差分约束做法

容易把条件转化为 $s_r - s_{l - 1} \le r - l + 1 - x$ 与 $0 \le s_i - s_{i - 1} \le 1$，$s_i$ 表示前缀 $[1, i]$ 中 $0$ 的个数。

注意到建完图后边权都非负，可以直接 dijkstra 跑差分约束。

时间复杂度 $O((n + m)\log n)$。

#### 差分约束代码

```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("avx,avx2")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
typedef long long lld;
using namespace std;
#define log() printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define il inline __attribute__((always_inline))
const int N = 200010;
int n, m;
vector<pair<int, int>> G[N];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int dis[N];
bool vis[N];
inline void dijkstra(int s) {
	for (int i = 0; i <= n; ++ i) dis[i] = 0x3f3f3f3f;
	dis[s] = 0;
	pq.push(make_pair(dis[s], s));
	for (int u; pq.size(); ) {
		u = pq.top().second; pq.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto &[v, w] : G[u])
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push(make_pair(dis[v], v));
			}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		G[i - 1].push_back(make_pair(i, 1));
		G[i].push_back(make_pair(i - 1, 0));
	}
	for (int l, r, x; m --; ) {
		scanf("%d%d%d", &l, &r, &x);
		G[l - 1].push_back(make_pair(r, r - l + 1 - x));
	}
	dijkstra(0);
	for (int i = 1; i <= n; ++ i) printf("%d ", dis[i] == dis[i - 1]);
}
```

#### 贪心做法

贪心很容易想到，具体是把区间按右端点排序，从右到左跳没有填 $1$ 的位置，能填的就填。

至于正确性，考虑每一个填 $1$ 的位置，如果换在一个更靠左的位置上，那么因为已经按右端点排序了，更靠左的位置能对之后的区间的贡献会更少。而在这题里，对于一个在前缀填数的方案，只要对后面的贡献越大就越优，所以这么做是最优的。

并查集维护前一个没有填 $1$ 的位置，树状数组维护填了区间 $1$ 的个数即可。

时间复杂度 $O(m\log n)$。

#### 贪心代码

```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("avx,avx2")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
typedef long long lld;
using namespace std;
#define log() printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define il inline __attribute__((always_inline))
const int N = 200010;
int n, m;
int pre[N];
struct node {
	int l, r, x;
} q[N];
inline bool operator < (const node &x, const node &y) {
	return x.r < y.r;
}
int C[N];
inline void modify(int p, int x) {
	for (; p <= n; p += p & -p) C[p] += x;
}
inline int query(int l, int r) {
	int ret = 0; -- l;
	for (; r; r &= r - 1) ret += C[r];
	for (; l; l &= l - 1) ret -= C[l];
	return ret;
}
int a[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) pre[i] = i;
	for (int i = 1; i <= m; ++ i) scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].x);
	sort(q + 1, q + m + 1);
	int ans = 0;
	for (int i = 1; i <= m; ++ i) {
		int c = query(q[i].l, q[i].r);
		int t = pre[q[i].r];
		for (; c < q[i].x; ) {
			a[t] = 1;
			modify(t, 1);
			++ c, ++ ans;
			t = pre[t] = pre[t - 1];
		}
	}
	printf("%d\n", ans);
}
```

---

## 作者：_HCl_ (赞：1)

非常好的差分约束练手题。

# ABC216G 题解

**题意简述**

构造一个 $01$ 序列，要求满足 $m$ 个形如“在 $[l,r]$ 上有 不少于 $x$ 个 $1$”的约束。

**思路引导**

由约束条件的性质出发，不难想到对前缀和进行差分约束。也就是将题目的限制条件转化为 $pre_{r}-pre_{l-1}\geq x$ 的差分约束。其中 $pre_i$ 是序列前 $i$ 项的前缀和。

又由于前缀和是单调递增的，每一位又只能填 $0$ 或 $1$，所以有 $0\leq pre_i-pre_{i-1}\leq 1$。

这样就构造出了前缀和的差分约束系统：

$\begin{cases}pre_{r_i}-pre_{l_i-1}\geq x_i\\pre_i-pre_{i-1}\geq0\\pre_{i-1}-pre_i\geq-1\end{cases}$

因为题目要求 $1$ 的个数最小，所以要跑最长路。又因为存在负边权，所以使用 SPFA 算法处理。总复杂度为 $\mathcal{O}(nm)$。

显然这个复杂度是跑不过的，所以我们考虑优化。这个算法的~~决速步~~复杂度最大的步骤就是 SPFA，所以我们考虑优化它。不难想到，使用堆优化的 Dijkstra 算法进行替换。然而 Dijkstra 算法只能处理边权为正的最短路，所以接下来我们考虑如何让所有的边权为正。

考虑使用 $0$ 的个数去表达，也就是 $pre_i$ 表示序列前 $i$ 个数中 $0$ 的个数。这样转化后，差分约束系统就变为：

$\begin{cases}pre_{r_i}-pre_{l_i-1}\leq r_i-l_i+1-x_i\\pre_i-pre_{i-1}\leq 1\\pre_{i-1}-pre_i\leq 0\end{cases}$

然后就可以使用堆优化的 Dijkstra 跑最短路了。复杂度 $\mathcal{O}(n\log n)$。

至于输出，序列的第 $i$ 位就是 $1-(pre_i-pre_{i-1})$。

**实现**

没什么好说的。

1. 读入，建图。
1. 跑最短路。
1. 输出。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct edge{
	int to,w;
};
vector<edge> e[200001];
int vis[200001],dis[200001];
priority_queue<edge> q;
bool operator <(edge a,edge b){
	return a.w>b.w;
} 
void dij(){//堆优化的 Dijkstra 
	dis[0]=0;
	q.push(edge{0,0});
	while(!q.empty()){
		int x=q.top().to;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=0;i<e[x].size();++i){
			int y=e[x][i].to,w=e[x][i].w;
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				q.push(edge{y,dis[y]});
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		e[l-1].push_back(edge{r,r-l+1-x});//建图 
	}
	for(int i=1;i<=n;++i){//注意最基本的约束关系 
		e[i-1].push_back(edge{i,1});
		e[i].push_back(edge{i-1,0});
	}
	memset(dis,0x3f,sizeof(dis));
	dij();//跑最短路 
	for(int i=1;i<=n;++i)
		cout<<1-dis[i]+dis[i-1]<<" ";//输出 
}
```

---

## 作者：__stick (赞：1)

# 题意
构造一个 $01$ 序列，要求满足一些限制，每个限制要求 $[l,r]$ 中至少有 $x$ 个 $1$，构造一组 $1$ 的个数最小的解。
# 思路
其实可以直接贪心。

将限制按照右端点排序，依次处理每个限制，用树状数组维护当前序列，每次看当前区间还差多少个 $1$，然后填的时候从右端点向左端点填，这样一定不劣，因为这样一个 $1$ 一定能被最多的区间覆盖，至于按照右端点排序的原因就是处理当前区间以前当前区间中的 $1$ 都要已经确定才能保证贪心正确。

实现的时候需要每次二分出来正确的位置，否则可能会被卡爆。

复杂度是 $O(n\log^2 n+m\log n)$。因为每个位置只会被二分一次。

由于树状数组的小常数，所以跑起来很快。

# code
```cpp
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;cin>>n;
	BIT<int>t(n+1);
	vector<tuple<int,int,int> >v;
	int l,r,x;
	int m;cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>l>>r>>x;
		v.emplace_back(r,l,x);
	}
	sort(v.begin(),v.end());
	vi res(n+1);
	for(auto& p:v)
	{
		tie(r,l,x)=p;
		x-=t.ask(l,r);
		while(x>0)
		{
			int L=l,R=r,ans=r;
			while(L<=R)
			{
				int mid=(L+R)>>1;
				if(t.ask(mid,r)==r-mid+1)R=mid-1;
				else L=mid+1,ans=mid;
			}
			t.add(ans,1);
			res[ans]=1;
			x--;
		}
	}
	for(int i=1;i<=n;i++)cout<<res[i]<<' ';
	return 0;
}
```




---

## 作者：AlicX (赞：1)

## Solution 

怎么全是差分约束题解？贪心很一眼啊。

把一组 $(l,r,x)$ 放在 $r$ 的位置上，把 $r$ 相同的一起处理了。

最优的策略一定是尽可能放在后面，这样可以为 $r$ 在 $i+1$ 的询问做最优的贡献。用线段树维护区间 $1$ 的数量，然后二分找到尽可能最后面的点满足条件，线段树区间覆盖即可。

时间复杂度 $O(n \log^2n)$。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10; 
int n,m; 
struct Node{ 
	int l,r; 
	int w,tag; 
}tr[N<<2]; 
il void pushup(int u){ 
	tr[u].w=tr[u<<1].w+tr[u<<1|1].w; 
} 
il void pushdown(int u){ 
	if(tr[u].tag==-1) return ; 
	tr[u<<1].w=(tr[u<<1].r-tr[u<<1].l+1)*tr[u].tag; 
	tr[u<<1|1].w=(tr[u<<1|1].r-tr[u<<1|1].l+1)*tr[u].tag; 
	tr[u<<1].tag=tr[u].tag,tr[u<<1|1].tag=tr[u].tag,tr[u].tag=-1; 
} 
il void build(int u,int l,int r){ 
	tr[u]={l,r}; tr[u].tag=-1; 
	if(l==r) return ; 
	int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
} 
il void modify(int u,int l,int r,int x){ 
	if(l<=tr[u].l&&tr[u].r<=r){ 
		tr[u].w=(tr[u].r-tr[u].l+1)*x; 
		tr[u].tag=x; return ; 
	} pushdown(u); 
	int mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) modify(u<<1,l,r,x); 
	if(r>mid) modify(u<<1|1,l,r,x); 
	pushup(u); 
} 
il int query(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].w; 
	pushdown(u); int w=0,mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) w=query(u<<1,l,r); 
	if(r>mid) w+=query(u<<1|1,l,r); 
	return w; 
} 
struct Que{ 
	int l,r,x; 
}a[N]; 
vector<int> vec[N]; 
signed main(){ 
	n=read(),m=read(); 
	for(int i=1;i<=m;i++) a[i].l=read(),a[i].r=read(),a[i].x=read(),vec[a[i].r].push_back(i); 
	build(1,1,n); 
	for(int i=1;i<=n;i++){ 
		bool flg=true; 
		for(auto u:vec[i]){ 
			int x=query(1,a[u].l,a[u].r); 
			if(x<a[u].x){ flg=false; break; } 
		} if(flg) continue; 
		int l=1,r=i,res=0; 
		while(l<=r){ 
			int mid=l+r>>1; flg=true; 
			int len=i-mid+1,p=query(1,mid,i); 
			for(auto u:vec[i]){ 
				int x=query(1,a[u].l,a[u].r); 
				if(len-p+x<a[u].x){ flg=false; break; } 
			} if(flg) l=mid+1,res=mid; else r=mid-1; 
		} modify(1,res,i,1); 
	} for(int i=1;i<=n;i++) printf("%d ",query(1,i,i)); puts(""); 
	return 0; 
} //
```

---

## 作者：_Ponder_ (赞：1)

[01Sequence](https://www.luogu.com.cn/problem/AT_abc216_g)

### 题目大意

构造一个满足 $m$ 个形如 $(l,r,x)$ 的限制条件的 $01$ 序列，其中 $(l,r,x)$ 表示区间 $[l,r]$ 的和不小于 $x$，你需要保证序列中 $1$ 的个数最小。

### 思路分析

贪心的想，如果我们将限制按右端点排序，那么当遍历到一个区间，发现现有的和不满足限制条件时，一定会从右往左放 $1$ 直到满足条件，因为只有这样才能让后面的区间放的 $1$ 更少。

具体过程的实现可以用链表或并查集，也可以用二分套树状数组实现。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N=200100;

int n,m,in1,in2,in3;
int res[N];

struct BIT{
    int a[N];
    #define lowbit(x) ((x)&(-(x)))
    void add(int x,int v){
        for(int i=x;i<=n+1;i+=lowbit(i)) a[i]+=v;
    }
    int ask(int x){
        int ans=0;
        for(int i=x;i;i-=lowbit(i)) ans+=a[i];
        return ans;
    }
}tree;

struct Node{
    int l,r,x;
}a[N];

bool cmp(Node a,Node b){//按右端点从小到大排序
    if(a.r!=b.r) return a.r<b.r;
    return a.l<b.l;
}

int find(int i){//对于当前的区间二分出下一个应该放的位置
    int l=a[i].l,r=a[i].r;
    while(l<r){
        int mid=(l+r+1)>>1;
        if(tree.ask(r)-tree.ask(mid-1)==r-mid+1) r=mid-1;//右半部分放满了
        else l=mid;
    }
    return l;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&in1,&in2,&in3);
        a[i]=Node{in1,in2,in3};
    }
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;i++){
        int num=a[i].x-(tree.ask(a[i].r)-tree.ask(a[i].l-1)),pos;//找到还差多少
        while(num>0){tree.add((pos=find(i)),1);res[pos]=1;num--;}//逐一填充
    }
    for(int i=1;i<=n;i++) cout<<res[i]<<' ';
    return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

这一题有 2 种思路。

# 思路1

我们先考虑贪心的思路，我们正序遍历的时候显然填 $1$ 的时候显然是填右边是最好的。

那么我们可以以右端点排一遍序，当然你倒序枚举的时候可以以左端点排序，然后我们可以维护一个能单点修改的数据结构来进行动态加 $1$，因为如果一个区间的 $1$ 选够了就是说这段区间的和是大于等于 $x$，我们还要维护一个并查集，`f[x]` 表示 `x` 左边的可以选的点，然后代码就很简单了。

```cpp
for(int i=1;i<=m;i++){
	int x=bit.sum(a[i].l,a[i].r);
	if(x<a[i].x){
		a[i].x-=x;
		for(int j=F(a[i].r);j>=a[i].l&&a[i].x;j=F(j)){
			bit.add(j,1);
			a[i].x--;
			f[j]=F(j-1);
			ans[j]=1;
		}
	}
}
```

# 思路2
第二种思路是差分约束，思路借鉴 fjy666 的。

考虑怎么建图，我们设 `s[i]` 表示构造的数组的前 $i$ 个数 `0` 的个数。

我们显然能够写出来下面的两个不等式。
- $0\le s_i-s_{i-1}\le 1$
- $s_{r_i}-s_{l_i-1}\le {l_i}-r_i+1-x_i$

我们可以通过构造的数组的定义理解第一个不等式。

第二个不等式理解为 $l$ 到 $r$ 的 `1`的个数是大于等于 $x_i$ 那么剩下的就是 `0`。

最后因为这个图不会出现负边权所以直接跑一边迪杰就行了。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace way1{//并查集 贪心 树状数组
	const int maxn=10000000;
template<typename T>
	struct BIT{
		vector<T>a;
		int n;
		BIT(int n=0){
			init(n);
		}
		inline void init(int n){
			this->n=n;
			a.assign(n,T());
		}
		inline void add(int x,T v){
			for(int i=x;i<=n;i+=i&-i){
				a[i-1]+=v;
			}
		}
		inline T s(int x){
			auto ans=T();
			for(int i=x;i>0;i-=i&-i){
				ans+=a[i-1];
			}
			return ans;
		}
		inline T sum(int l,int r){
			return s(r)-s(l-1);
		}
	};
	int f[maxn];
	int F(int x){return x==f[x]?x:f[x]=F(f[x]);}
	struct node{
		int l,r,x;
	}a[maxn];
	int ans[maxn];
	void solve(){
		int n,m;
		cin>>n>>m;
		BIT<int>bit(maxn);
		for(int i=1;i<=m;i++){
			cin>>a[i].l>>a[i].r>>a[i].x;
		}
		sort(a+1,a+1+m,[&](node a,node b){
			return a.r<b.r;
		});
		for(int i=1;i<=n;i++)f[i]=i;
		for(int i=1;i<=m;i++){
			int x=bit.sum(a[i].l,a[i].r);
			if(x<a[i].x){
				a[i].x-=x;
				for(int j=F(a[i].r);j>=a[i].l&&a[i].x;j=F(j)){
					bit.add(j,1);
					a[i].x--;
					f[j]=F(j-1);
					ans[j]=1;
				}
			}
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	}
}
namespace way2{//差分约束
	const int maxn=1000000;
	struct edge{
		int to,w,nxt;
	}e[maxn];
	int h[maxn],tot;
	inline void add(int u,int v,int w=0){
		e[++tot].to=v;
		e[tot].nxt=h[u];
		e[tot].w=w;
		h[u]=tot;
	}
	int n,m;
	priority_queue<pair<int,int>> qp;
	int dis[maxn], vis[maxn];
	void dij(int s){
		memset(dis,0x3f,sizeof dis);
		dis[s]=0;
		qp.push({0,s});
		while(qp.size()){
			auto t=qp.top(); qp.pop();
			int u=t.second;
			if(vis[u])continue;
			vis[u]=1;
			for(int i=h[u];i;i=e[i].nxt){
				int v=e[i].to,w=e[i].w;
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					qp.push({-dis[v],v});
				}
			}
		}
	}
	void solve(){
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			int l,r,x;
			cin>>l>>r>>x;
			add(l-1,r,r-l+1-x);
		}
		for(int i=1;i<=n;i++)
			add(i,i-1,0),add(i-1,i,1);
		dij(0);
		for(int i=1;i<=n;i++)
			cout<<((dis[i]-dis[i-1])^1)<<" ";
	}
}
signed main(){
	way1::solve();
	// way2::solve();
	return 0;
}
```

---

