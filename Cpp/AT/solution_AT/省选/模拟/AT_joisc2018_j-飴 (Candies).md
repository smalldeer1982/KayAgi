# 飴 (Candies)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2018/tasks/joisc2018_j

桌子上有从 $1$ 到 $n$ 的糖排列着，每一块糖都有一个美味值 $a_{i}$，不能同时吃相邻的两颗糖，你需要求出当吃 $1,2,3……\left \lceil \frac{n}{2} \right \rceil $ 颗糖时能够得到的美味值的和的最大值。

## 说明/提示

所有数据满足以下限制：

$1\le n\le 2\times 10^{5}$

$1\le a_{i}\le 10^{9}$

其中 $8\%$ 的数据满足：$1\le n\le 2000$

其余测试点无特殊限制。

**【样例解释 \#1】**

只吃一颗糖选第四个美味值为 $7$ 为最大值。

吃两颗糖选第二个和第四个最优，美味值为 $5+7=12$。

吃三颗糖由于不能吃相邻的两颗糖所以只能选第一个，第三个和第五个，美味值为 $3+1+6=10$。

## 样例 #1

### 输入

```
5
3
5
1
7
6```

### 输出

```
7
12
10```

## 样例 #2

### 输入

```
20
623239331
125587558
908010226
866053126
389255266
859393857
596640443
60521559
11284043
930138174
936349374
810093502
521142682
918991183
743833745
739411636
276010057
577098544
551216812
816623724```

### 输出

```
936349374
1855340557
2763350783
3622744640
4439368364
5243250666
5982662302
6605901633
7183000177
7309502029```

# 题解

## 作者：yuanruiqi (赞：4)

猜测答案具有凸性，可以分治，每一个分治区间记录四个状态表示左/右可不可以选。可以分治时进行闵可夫斯基和，并对两个结果，于每个位上取 $\max$。

---

## 作者：Sky_Maths (赞：3)

# 前言

这道题居然没有题解？

其实这道题和 [P1484](https://www.luogu.com.cn/problem/P1484) 和 [P1792](https://www.luogu.com.cn/problem/P1792) 是基本一样的，但注意一下转换。（三倍经验？）

我来讲一下反悔贪心的做法。

这就是反悔贪心的模板（貌似），为什么是紫题，其它两道题的代码基本一样，只是蓝题。

# 正文

反悔贪心分为两类（貌似），但我只学了反悔自动机（目前），其实很简单，大家别怕。

对于原题，存在 $n$ 块糖果，不能取相邻的，我们考虑只取一块的取法，发现必定取 $\max$ 。

接下来考虑取两块的取法，发现只有两种取法：取最大值和次大值，或者取最大值两端的糖果。因为如果不考虑限制（即不连续取），一定是最大值和次大值。

如果存在限制，只有在最大次大值相邻时才会改变，于是考虑将答案加上 $\max$ 值，并将 $a_{i-1},a_{i},a_{i+1}$ 合并为一个 $a_{i-1}+a_{i+1}-a_{i}$，其中 $a_i$ 即最大值，如果后续取到这个东西，代表将 $a_i$ 变成了其两边的糖果。

于是原来的问题就变成了一个 $n-1$ 规模的问题，时间复杂度需要均摊一下是 $\operatorname{O}(n\cdot \log(n))$ 的。

# 思考

为什么这样的贪心是可行的，即改变前后维护了哪些性质使得当前最优解变成了当前全局最优解？

反悔贪心有没有让你想到一个曾经学过的算法（如果你没学过网络流，当我没说）?

# 实现

用双端链表维护这种合并操作，再记录一下每个糖果是否被合并过，合并 $a_i$ 周围即将 $pre_{i-1},nxt_{i+1}$ 标为被合并，再使用优先队列维护就好了。

或者 multiset，应该连记录是否被合并过也不用了，直接在可重集中删除就好了。

但是我最开始做的是有环的那道题，所以我将链变成了环，具体方法是在 $1$ 与 $n$ 间插入一块值为 $-\infty$ 的糖果。

# 代码

```cpp
#include<cstdio>
#include<queue>
#define rep(i,l,r) for(int i(l),i##end(r);i<=i##end;++i)
using namespace std;
typedef long long ll;
typedef pair<ll,int> pii;
constexpr int N = 5e5 + 9;
constexpr ll INF = 1e15;
int n,m;
int pre[N],nxt[N];
bool b[N];
ll ans;
ll a[N];
priority_queue<pii> q;
void push(int id) {
	q.push((pii){a[id],id});
}
void del(int id) {
	b[id]=true;
	pre[nxt[id]]=pre[id];
	nxt[pre[id]]=nxt[id];
}
signed main() {
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	scanf("%d",&n);
	rep(i,1,n) scanf("%lld",&a[i]);
	++n;a[n]=-INF;
	rep(i,1,n) {
		pre[i]=i-1;
		nxt[i]=i+1;
	}
	pre[1]=n;
	nxt[n]=1;
	rep(i,1,n) push(i);
	rep(i,1,n>>1) {
		pii top=q.top(); q.pop();
		while(b[top.second]) top=q.top(),q.pop();
		ans=ans+top.first;
		int id=top.second;
		a[id]=a[pre[id]]+a[nxt[id]]-a[id];
		push(id);
		del(pre[id]);
		del(nxt[id]);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# JOISC2018J 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2018_j)

**题目大意**

> 给一个长度为 $n$ 的数轴，每个位置有权值，对于 $k=1\sim \left\lceil\dfrac n2\right\rceil$，求出选 $k$ 个不相邻位置的最大权值和。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

观察解的形态，用 $0/1$ 表示该位置有没有被选，容易发现序列能划分成形如 $0,1$ 交替出现的段且两端为 $0$，每次操作一定是把某个段 $01$ 取反，然后把两边的段合并。

用链表维护合并的过程，堆贪心求最大的一段操作即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5,INF=1e18;
int pre[MAXN],suf[MAXN],inq[MAXN],c[MAXN];
signed main() {
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&c[i]),pre[i]=i-1,suf[i]=i+1,inq[i]=1;
	c[0]=c[n+1]=-INF;
	auto merge=[&](int u) {
		pre[suf[u]]=pre[u];
		suf[pre[u]]=suf[u];
		inq[u]=0;
	};
	priority_queue <array<int,2>> Q;
	for(int i=1;i<=n;++i) Q.push({c[i],i});
	int ans=0;
	for(int i=1;i<=(n+1)/2;++i) {
		while(!inq[Q.top()[1]]) Q.pop();
		int w=Q.top()[0],p=Q.top()[1]; Q.pop();
		printf("%lld\n",ans+=w);
		Q.push({c[p]=c[pre[p]]+c[suf[p]]-w,p});
		merge(pre[p]),merge(suf[p]);
	}
	return 0;
}
```



---

## 作者：cmrhhh (赞：0)

### [AT_joisc2018_j](https://www.luogu.com.cn/problem/AT_joisc2018_j)解题报告

其实是看了题解，先挂（可能的）经验。

[P3620 [APIO/CTSC2007] 数据备份](https://www.luogu.com.cn/problem/P3620)

[BACKUP - Backup Files](https://www.luogu.com.cn/problem/SP1553)

[P1484 种树](https://www.luogu.com.cn/problem/P1484)

[P1792 [国家集训队] 种树](https://www.luogu.com.cn/problem/P1792)

[(Candies)](https://www.luogu.com.cn/problem/AT_joisc2018_j)

$2$ 紫 $3$ 蓝。

随我进入解题，我发现我在去年的 $3$ 月写过其中一个种树，思路挺精妙的，就是用**双向链表**维护子段价值，具体地，$pre[i]$ 表示 $i$ 下标的前驱下标，$nxt[i]$ 表示 $i$ 下标的后继下标，下标 $i$ 可以得到 $val[i]$，考虑现将所有 $val[i]$ 送入大根堆，然后**贪心**取出堆顶，由于有两边不取的限制，这样不一定是最优的，考虑**带悔贪心**，非常奇妙，对于每一个 $val[i]$ 有两种选择，一种是选 $val[i]$ 另一种是选择 $val[pre[i]]+val[nxt[i]]$，为了反悔，若我们取了 $val[i]$，我们将两端 $pre[i]$ 和 $nxt[i]$ 删掉，与中间合并，$\text a[i]=a[pre[i]]+a[nxt[i]]-val[i]$，这样的话选择两边时不用考虑与之前的状态冲突，有了无后效性（确信），优先队列是 $O(\log{n})$ 插入维护，总复杂度 $O(n\log{n})$，某些题要注意边界的情况。

#### 经验 P1484

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,m,a[maxn],pre[maxn],nxt[maxn],cnt=0;
struct Node{
	int id,val;
	bool operator<(Node y)const{
		return val<y.val;
	}
};
priority_queue<Node>q;
bool vis[maxn];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a[i];nxt[i]=i+1;pre[i]=i-1;
		q.push({i,a[i]});
	}
	pre[1]=n;nxt[n]=1;
	int ans=0;
	while(cnt<m){
		while(q.size()&&vis[q.top().id])q.pop();
		if(!q.size())break;
		auto f=q.top();q.pop();
		if(!vis[f.id]&&f.id>0){
			vis[pre[f.id]]=vis[nxt[f.id]]=1;
			ans+=f.val;
			a[f.id]=a[pre[f.id]]+a[nxt[f.id]]-f.val;
			q.push({f.id,a[f.id]});
			pre[f.id]=pre[pre[f.id]];
			nxt[f.id]=nxt[nxt[f.id]];
			nxt[pre[f.id]]=f.id;
			pre[nxt[f.id]]=f.id;
			cnt++;
		}
	}
	if(!(cnt-m))cout<<"Error!";
	else cout<<ans<<"\n";
	return 0;
}
```

#### 经验 ATcode

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,a[maxn],pre[maxn],nxt[maxn],cnt=0;
struct Node{
	int id,val;
	bool operator<(Node y)const{
		return val<y.val;
	}
};
priority_queue<Node>q;
bool vis[maxn];
int nas[maxn];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];nxt[i]=i+1;pre[i]=i-1;
		q.push({i,a[i]});
	}
	pre[n+1]=n;nxt[0]=1;a[0]=-1e18,a[n+1]=-1e18;
	int m=n+1>>1;
	int ans=0;
	while(cnt<m){
		if(!q.size())break;
		auto f=q.top();q.pop();
		if(!vis[f.id]&&f.id>0){
			vis[pre[f.id]]=vis[nxt[f.id]]=1;
			ans+=f.val;
			a[f.id]=a[pre[f.id]]+a[nxt[f.id]]-f.val;
			q.push({f.id,a[f.id]});
			pre[f.id]=pre[pre[f.id]];
			nxt[f.id]=nxt[nxt[f.id]];
			nxt[pre[f.id]]=f.id;
			pre[nxt[f.id]]=f.id;
			cnt++;
		}
		nas[cnt]=max(nas[cnt],ans);;
	}
	for(int i=1;i<=m;++i)cout<<nas[i]<<"\n";
	
	
	return 0;
} 
```

#### 经验 国家集训队

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,m,a[maxn],pre[maxn],nxt[maxn],cnt=0;
struct Node{
	int id,val;
	bool operator<(Node y)const{
		return val<y.val;
	}
};
priority_queue<Node>q;
bool vis[maxn];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	if(m*2>n){cout<<"Error!";exit(0);}
	for(int i=1;i<=n;++i){
		cin>>a[i];nxt[i]=i+1;pre[i]=i-1;
		q.push({i,a[i]});
	}
	pre[1]=n;nxt[n]=1;
	int ans=0;
	while(cnt<m){
		while(q.size()&&vis[q.top().id])q.pop();
		if(!q.size())break;
		auto f=q.top();q.pop();
		if(!vis[f.id]&&f.id>0){
			vis[pre[f.id]]=vis[nxt[f.id]]=1;
			ans+=f.val;
			a[f.id]=a[pre[f.id]]+a[nxt[f.id]]-f.val;
			q.push({f.id,a[f.id]});
			pre[f.id]=pre[pre[f.id]];
			nxt[f.id]=nxt[nxt[f.id]];
			nxt[pre[f.id]]=f.id;
			pre[nxt[f.id]]=f.id;
			cnt++;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

#### 经验 3620

首先以**拉线的长**为贪心对象，首先注意到两端拉线不可能有**交集或包含**，并且**相邻两段**拉线**不能**存在，因为要互异的几对城市，然后就转化成了最初的带悔。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,k,a[maxn],pre[maxn],nxt[maxn],cnt=0;
struct Node{
	int id,val;
	bool operator<(Node y)const{
		return val>y.val;
	}
};
priority_queue<Node>q;
bool vis[maxn];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i];nxt[i]=i+1;pre[i]=i-1;
	}for(int i=n;i>=2;--i){
		a[i]-=a[i-1];//算出第i段的线长 
		q.push({i,a[i]});
	}
	pre[1]=n;nxt[n]=1;a[1]=a[n+1]=1e18;
	int ans=0;
	while(cnt<k){
		while(q.size()&&vis[q.top().id])q.pop();
		if(!q.size())break;
		auto f=q.top();q.pop();
		if(!vis[f.id]&&f.id>1){
			vis[pre[f.id]]=vis[nxt[f.id]]=1;
			ans+=f.val;
			a[f.id]=a[pre[f.id]]+a[nxt[f.id]]-f.val;
			q.push({f.id,a[f.id]});
			pre[f.id]=pre[pre[f.id]];
			nxt[f.id]=nxt[nxt[f.id]];
			nxt[pre[f.id]]=f.id;
			pre[nxt[f.id]]=f.id;
			cnt++;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```



#### 经验 SPOJ

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,k,a[maxn],pre[maxn],nxt[maxn],cnt=0;
struct Node{
	int id,val;
	bool operator<(Node y)const{
		return val>y.val;
	}
};
priority_queue<Node>q;
bool vis[maxn];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;++i){
			vis[i]=0;
			cin>>a[i];nxt[i]=i+1;pre[i]=i-1;
		}for(int i=n;i>=2;--i){
			a[i]-=a[i-1];//算出第i段的线长 
			q.push({i,a[i]});
		}
		pre[1]=n;nxt[n]=1;a[1]=a[n+1]=1e18;
		int ans=0;cnt=0;
		while(cnt<k){
			while(q.size()&&vis[q.top().id])q.pop();
			if(!q.size())break;
			auto f=q.top();q.pop();
			if(!vis[f.id]&&f.id>1){
				vis[pre[f.id]]=vis[nxt[f.id]]=1;
				ans+=f.val;
				a[f.id]=a[pre[f.id]]+a[nxt[f.id]]-f.val;
				q.push({f.id,a[f.id]});
				pre[f.id]=pre[pre[f.id]];
				nxt[f.id]=nxt[nxt[f.id]];
				nxt[pre[f.id]]=f.id;
				pre[nxt[f.id]]=f.id;
				cnt++;
			}
		}
		cout<<ans<<"\n";
		while(q.size())q.pop();
	}
	return 0;
}
```

### 结算

~~感觉经验经爽了~~更加透彻理解带悔贪心和双向链表了。

---

## 作者：xqqQwQ_ (赞：0)

感觉直接观察这样的方法还是太超前了。

考虑其实我们直接有费用流模型。对第 $i$ 和 $i + 1$ 块糖之间的间隙建立虚点 $t_i$，连边 $(t_i, i, 1, 0), (t_i, i + 1, 1, 0)$。源点 $S$ 向所有虚点连边 $(S, t_i, 1, 0)$，所有糖向汇 $T$ 点连边 $(i, T, 1, -a_i)$。每次增广必然使吃的糖数量 $+1$，因此直接跑 EK 就有一个复杂度 $O(n^3)$ 的做法。

考虑使用模拟费用流优化该过程。设当前状态下被选中的糖为 $1$，否则为 $0$。我们发现每次增广一定形如 $S \rightarrow i \rightarrow \cdots \rightarrow j \rightarrow T$ 的形式，也就是把一个两端为 $0$ 且 $01$ 交替的连续段反转。 

有了这个结论，我们就可以直接使用链表维护连续段，每次从 Set 中提取出价值最大的连续段即可。时间复杂度 $O(n \log n)$。

注意如果有一个左端点为 $1$ 或右端点为 $n$ 的连续段被增广那么以后它就不能再被增广了，因此需要一开始把 $0$ 和 $n + 1$ 的价值赋成 $-\infty$。

[code](https://loj.ac/s/2070810)

---

