# Omsk Metro (simple version)

## 题目描述

This is the simple version of the problem. The only difference between the simple and hard versions is that in this version $ u = 1 $ .

As is known, Omsk is the capital of Berland. Like any capital, Omsk has a well-developed metro system. The Omsk metro consists of a certain number of stations connected by tunnels, and between any two stations there is exactly one path that passes through each of the tunnels no more than once. In other words, the metro is a tree.

To develop the metro and attract residents, the following system is used in Omsk. Each station has its own weight $ x \in \{-1, 1\} $ . If the station has a weight of $ -1 $ , then when the station is visited by an Omsk resident, a fee of $ 1 $ burle is charged. If the weight of the station is $ 1 $ , then the Omsk resident is rewarded with $ 1 $ burle.

Omsk Metro currently has only one station with number $ 1 $ and weight $ x = 1 $ . Every day, one of the following events occurs:

- A new station with weight $ x $ is added to the station with number $ v_i $ , and it is assigned a number that is one greater than the number of existing stations.
- Alex, who lives in Omsk, wonders: is there a subsegment $ \dagger $ (possibly empty) of the path between vertices $ u $ and $ v $ such that, by traveling along it, exactly $ k $ burles can be earned (if $ k < 0 $ , this means that $ k $ burles will have to be spent on travel). In other words, Alex is interested in whether there is such a subsegment of the path that the sum of the weights of the vertices in it is equal to $ k $ . Note that the subsegment can be empty, and then the sum is equal to $ 0 $ .

You are a friend of Alex, so your task is to answer Alex's questions.

 $ \dagger $ Subsegment — continuous sequence of elements.

## 说明/提示

Explanation of the first sample.

The answer to the second question is "Yes", because there is a path $ 1 $ .

In the fourth question, we can choose the $ 1 $ path again.

In the fifth query, the answer is "Yes", since there is a path $ 1-3 $ .

In the sixth query, we can choose an empty path because the sum of the weights on it is $ 0 $ .

It is not difficult to show that there are no paths satisfying the first and third queries.

## 样例 #1

### 输入

```
1
8
+ 1 -1
? 1 1 2
? 1 2 1
+ 1 1
? 1 3 -1
? 1 1 1
? 1 3 2
? 1 1 0```

### 输出

```
NO
YES
NO
YES
YES
YES```

## 样例 #2

### 输入

```
1
10
+ 1 -1
+ 1 -1
+ 3 1
+ 3 -1
+ 3 1
? 1 6 -1
? 1 6 2
? 1 2 0
? 1 5 -2
? 1 4 3```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：zhicheng (赞：7)

### 思路

**一个比较简单的树上 DP。**

首先观察几个性质。
- 第一，显然可以把询问离线，先把整个树建好了再处理询问（当然在线也可做，但是个人认为这样更模块化）。
- 第二，如果我们处理了两点之间可能取到的最大和最小权值，这两个数之间的所有整数都可以取到。因为考虑加上或减掉一个路径上的点，路径的权值只会 $\pm 1$。所以你从最大权值变为最小权值的过程中一定取到了这之间的每一个整数。

然后我们考虑如何计算两点之间可能取到的最大和最小权值。简单版是从根到某个点，因此我们只需从根开始树上 DP，按照求最大最小子段和的转移方程求解。具体为：
$$
maxx_u=\max(maxx_{fa}+w_u,w_u)
$$
$$
minn_u=\min(minn_{fa}+w_u,w_u)
$$

其中 $w_u$ 是点 $u$ 的权值，$maxx_1=1$，$minn_1=0$。

还需注意的是这样算出来的 $maxx_u$ 和 $minn_u$ 是以 $u$ 点为结束点的最大最小子段和，还要再从根推一遍，推成从根到 $u$ 点的最大最小子段和（$maxx_u=\max(maxx_{fa},maxx_u)$，$minn$ 同理）。

然后处理询问就完了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int tot,first[200010],nnext[400010],to[400010],w[200010],q[200010],r[200010],maxx[200010],minn[200010];
void add(int x,int y){
	nnext[++tot]=first[x];
	first[x]=tot;
	to[tot]=y;
}
void fun(int u,int fa){
	if(u==1){
		maxx[u]=1;
	}
	else{
		maxx[u]=max(w[u],maxx[fa]+w[u]);  //dp核心
		minn[u]=min(w[u],minn[fa]+w[u]);
	}
	for(int e=first[u];e;e=nnext[e]){
		if(to[e]!=fa){
			fun(to[e],u);
		}
	}
}
void fun1(int u,int fa){
	maxx[u]=max(maxx[fa],maxx[u]);
	minn[u]=min(minn[fa],minn[u]);
	for(int e=first[u];e;e=nnext[e]){
		if(to[e]!=fa){
			fun1(to[e],u);
		}
	}
}
int main(){
	int t,sum,sum1,n,a,p;
	char s;
	scanf("%d",&t);
	while(t--){
		memset(first,0,sizeof(first));
		memset(maxx,0,sizeof(maxx));
		memset(minn,0,sizeof(minn));
		sum=1;
		w[1]=1;
		sum1=0;
		scanf("%d",&n);
		while(n--){
			cin>>s;
			if(s=='+'){
				scanf("%d%d",&a,&p);
				add(a,++sum);  //建树
				add(sum,a);
				w[sum]=p;
			}
			else{
				sum1++;
				scanf("%d%d%d",&q[sum1],&q[sum1],&r[sum1]);  //离线
			}
		}
		fun(1,0);  //dp
		fun1(1,0);  //推下来
		for(int i=1;i<=sum1;i++){
			if(r[i]>=minn[q[i]]&&r[i]<=maxx[q[i]]){  //处理询问
				printf("YES\n");
			}
			else{
				printf("NO\n");
			}
		}
	}
}
```

---

## 作者：Prms_Prmt (赞：4)

### 题意

给定树的根节点 $ 1 $ 权值为 $ 1 $ 和 $ q $ 次操作：添加新节点，编号为当前点数加一，给定新权值 $ x \in \{ 1, -1 \} $ 并与指定点建边；查询根到某点的链上是否存在和为 $ k $ 的连续子段。

### 定理

在长度为 $ n $ 的数列 $ a $ 中，如果 $ a_i \in \{ 1, -1 \} $($ 1 \leq i \leq n $) 且 **最小连续子段和** $ \leq k \leq $ **最大连续子段和**，则可构造和为 $ k $ 的连续子段。

+ 证明：子段边界增删一个元素，子段和仅会 $ \pm 1 $。最大子段和变为最小子段和仅需增删边界元素，所以可以构造两者之间的每一个整数和（包括 0）。

### 最大子段和的维护

+ 最小子段和同理

令 $ mxt_i $ 为 $ i $ 结尾的最大子段和 (maxium with tail $ i $).

在 $ i = 1 $ 时，有 $ mxt_1 = \max \{ 0, a_1 \} $

在 $ 2 \leq i \leq n $ 时，有 $ mxt_i = \max \{ mxt_{ i - 1 } + a_i, a_i \} $

维护 $ mxs_i $ 为 $ 1 $ 至 $ i $ 的最大子段和 (maxium summary of $ i $).

在 $ i = 1 $ 时，有 $ mxs_1 = mxt_1 $

在 $ 2 \leq i \leq n $ 时，有 $ mxs_i = \max \{ mxs_{ i - 1 }, mxt_i \} $

### 代码

注意，只需维护树形即可（见代码注释），无需建树。
```cpp
const int N=2e5+5;
int t,n,tot;//tot 为点数
//子段和
int mxt[N],mnt[N];
int mxs[N],mns[N];
main() {
    scanf("%d",&t);
    while(t--) {
        tot=1;
        scanf("%d",&n);
        //初始化
        for(int i=1;i<=n;++i)
            mxt[i]=mxs[i]=mns[i]=mnt[i]=0;
        mxt[tot]=1;
        mxs[tot]=1;
        //读入处理
        for(int i=1;i<=n;++i) {
            char s;
            cin>>s;
            if(s=='+') {
                int f,x;
                scanf("%d%d",&f,&x);
                //维护，注意树上是 tot + 1 和 f 分别对应数列的 i 和 i - 1
                mxt[++tot]=max(mxt[f]+x,x);
                mnt[tot]=min(mnt[f]+x,x);
                mxs[tot]=max(mxt[tot],mxs[f]);
                mns[tot]=min(mnt[tot],mns[f]);
            }
            else
            {
                int u,v,k;
                scanf("%d%d%d",&u,&v,&k);
                //判断
                if(mns[v]<=k&&k<=mxs[v])
                    printf("YES\n");
                else  puts("NO");
            }
        }
    }
}
```
才疏学浅，如有疏漏，恳请指正。

---

## 作者：Auto_Accepted (赞：2)

先考虑 $k > 0$，$k < 0$ 同理（就是乘 $-1$），这里就不再阐述。

有一个比较核心（神奇）的结论：如果一个子段和为 $sum$，则 $[0,sum]$ 之内的数全都可以在这个子段的子段中找到。

我们感性理解一下：

和为 $sum$，则至少有 $sum$ 个值为 $1$ 的节点。反向考虑，增加一个权值为 $1$ 的节点贡献为 $1$，则删除这个节点对答案的的贡献为 $-1$。而在最坏情况下（只有 $sum$ 个值为 $1$ 的节点），最多可以把答案减少 $sum$。所以 $[0,sum]$ 区间内都是可以取到的。

所以只要看最大（$k \ge 0$）和最小（$k < 0$）子段和即可。

维护节点最小值和最大值，通过 dfs 处理即可。

## 代码：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector <int> a[1000005];
int n, x[1000005], maxans[1000005], minans[1000005], u[1000005], v[1000005], w[1000005], m;
inline void dfs(int now, int maxn = 0, int minn = 0) {
	maxn = max(maxn, 0ll);
	minn = min(minn, 0ll);
	maxn += x[now];
	minn += x[now];
	maxn = max(maxn, 0ll);
	minn = min(minn, 0ll);
	maxans[now] = max(maxans[now], maxn);
	minans[now] = min(minans[now], minn);
	for (int i = 0; i < a[now].size(); i++) {
		int v = a[now][i];
		maxans[v] = maxans[now];
		minans[v] = minans[now];
		dfs(v, maxn, minn);
	}
}
signed main() {
	int t;
	cin >> t;
	while (t--) {
		int q;
		cin >> q;
		for (int i = 1; i <= n; i++) {
			x[i] = maxans[i] = minans[i] = 0;
			a[i].clear();
		}
		m = 0;
		n = 1;
		x[1] = 1;
		while (q--) {
			char op;
			cin >> op;
			if (op == '+') {
				int u, data;
				cin >> u >> data;
				x[++n] = data;
				a[u].push_back(n);
			} 
			else {
				m++;
				cin >> u[m] >> v[m] >> w[m];
			}
		}
		dfs(1);
		for (int i = 1; i <= m; i++) {
			if (minans[v[i]] <= w[i] && w[i] <= maxans[v[i]]) {
				puts("Yes");
			} else {
				puts("No");
			}
		}
	}
	return 0;
}
```


---

## 作者：yangshengyu0719 (赞：0)

注：此种做法亦为 hard version 的正解

## 思路
这道题其实就是一个树剖裸题，我们只用知道一段路径的最大子段和与最小子段和，若询问的值在两者间，那么存在；否则不存在。

原因是也很简单，因为每个位置的权值要么使一段的总和加 $1$，要么使它减 $1$，因此和在最大子段和与最小子段和的子段一定会存在。这里是我个人认为本题唯一需要动一点脑子的地方，可以自己多感悟一下。

问题至此就很简单了只需要会 [P4513 小白逛公园](https://www.luogu.com.cn/problem/P4513)（求最大子段和）和 [P3384 【模板】重链剖分/树链剖分](https://www.luogu.com.cn/problem/P3384) 这俩模板题就行了。

或许有人会问：题目中动态添加结点这一操作不好搞呀！其实这也很好避免，我们只要离线，先根据操作建好整棵树，再一次一次回答问题即可。

然后就没有然后了。时间复杂度 $O(n\log^2 n)$ 。

## 代码
```cpp
#include <bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=2e5+5;
int n,w[N],val[N];
int h[N],e[N],nx[N],idx;
int sz[N],son[N],prt[N],dep[N];
int tot,tid[N],top[N];
struct Query{int u,v,k;};
queue<Query> Q;
struct node{
	int l,r;
	int sum,lmax,rmax,maxn;
	int lmin,rmin,minn;
}T[N<<2];
node Empty={0,0,0,0,0,0,0,0,0};
void init(){
	for(int i=0;i<=tot;i++) h[i]=son[i]=0;
	for(int i=1;i<=(tot<<2);i++) T[i]=Empty;
	idx=0;w[tot=1]=1;
}
void AddEdge(int a,int b){e[++idx]=b;nx[idx]=h[a];h[a]=idx;}
void dfs1(int fa,int u,int deep){
	dep[u]=deep;
	prt[u]=fa;
	sz[u]=1;
	for(int i=h[u];i;i=nx[i]){
		int v=e[i];
		if(v!=prt[u]){
			dfs1(u,v,deep+1);
			sz[u]+=sz[v];
			if(sz[v]>=sz[son[u]]) son[u]=v;
		}
	}
}
void dfs2(int u,int t){
	tid[u]=++tot;
	top[u]=t;
	if(son[u]) dfs2(son[u],t);
	for(int i=h[u];i;i=nx[i]){
		int v=e[i];
		if(v!=prt[u]&&v!=son[u]) dfs2(v,v);
	}
}
node merge(node L,node R){
	node res=Empty;
	res.sum=L.sum+R.sum;
	res.lmax=max(L.lmax,L.sum+R.lmax);
	res.rmax=max(R.rmax,R.sum+L.rmax);
	res.maxn=max(max(L.maxn,R.maxn),L.rmax+R.lmax);
	res.lmin=min(L.lmin,L.sum+R.lmin);
	res.rmin=min(R.rmin,R.sum+L.rmin);
	res.minn=min(min(L.minn,R.minn),L.rmin+R.lmin);
	return res;
}
void build(int k,int l,int r){
	if(l==r){
		T[k].l=T[k].r=l;T[k].sum=val[l];
		T[k].lmax=T[k].rmax=T[k].maxn=max(val[l],0);
		T[k].lmin=T[k].rmin=T[k].minn=min(val[l],0);
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	T[k]=merge(T[ls],T[rs]);
	T[k].l=l,T[k].r=r;
}
node Get(int k,int L,int R){
	int l=T[k].l,r=T[k].r;
	if(L<=l&&r<=R) return T[k];
	int mid=(l+r)>>1;
	if(R<=mid) return Get(ls,L,R);
	else if(L>mid) return Get(rs,L,R);
	else return merge(Get(ls,L,R),Get(rs,L,R));
}
bool query(int u,int v,int k){
	if(!k) return true;
	node f1=Empty,f2=Empty;
	while(top[u]!=top[v]){
		int tu=top[u],tv=top[v];
		if(dep[tu]>dep[tv]) f1=merge(Get(1,tid[tu],tid[u]),f1),u=prt[tu];
		else f2=merge(Get(1,tid[tv],tid[v]),f2),v=prt[tv];
	}
	if(dep[u]>dep[v]) f1=merge(Get(1,tid[v],tid[u]),f1);
	else f2=merge(Get(1,tid[u],tid[v]),f2);
	swap(f1.lmax,f1.rmax);
	swap(f1.lmin,f1.rmin);
	f1=merge(f1,f2);
	return k>0?k<=f1.maxn:k>=f1.minn;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--){
		init();
		cin>>n;
		char op;int u,v,x;
		while(n--){
			cin>>op;
			if(op=='+'){cin>>u>>x;tot++;AddEdge(u,tot);w[tot]=x;}
			else{cin>>u>>v>>x;Q.push({u,v,x});}
		}
		dfs1(0,1,1);tot=0;dfs2(1,1);
		for(int i=1;i<=tot;i++) val[tid[i]]=w[i];
		build(1,1,tot);
		while(!Q.empty()){
			Query q=Q.front();Q.pop();
			cout<<(query(q.u,q.v,q.k)?"YES":"NO")<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1843F1)

&nbsp;

### 题目大意：
初始有一个编号为 $1$，点权为 $1$ 的结点，后续进行 $m$ 次操作，操作分为两种：

- 添加一个点权为 $w_i (w_i \in \{-1,1\})$ 的节点，并使其与点 $u_i$ 连边，编号为添加后点的总数。

- 询问点 $1$ 到 $v_i$ 的最短路径上是否存在一个子路径使得其所过点点权和为 $k_i$，子路径可为空，此时点权和为 $0$。

&nbsp;

### 解题思路：
从 $w_i \in \{-1,1\}$ 入手，不难发现对于点 $u$ 到点 $v$，设两人路径上最小子路径上点权和为 $mn$，最大子路径上点权和为 $mx$，则对于 $k \in [mn,mx]$，一定能在 $u$ 到 $v$ 之间的路径上找到一子路径使其点权和为 $k$，首先可以得知的是 $mn\leq 0$，$mx\geq 0$，同时对于 $mx$，将路径上的 $-1$ 点与 $1$ 点抵消掉后，剩下的一定是 $mx$ 个做出贡献的 $1$ 点，那么显然可以构造出路径上点权和为 $k$ $(k\in[0,mx])$,对于 $mn$ 同理。

因此，我们只需要维护 $1$ 到所有点的 $mx$ 和 $mn$ 即可。为此，我们可以维护一下以每个点为子路径结尾时到最大子路径上点权和，这里称为 $pmx_i$，和最小子路径上点权和，这里称为 $pmn_i$，即可。而点 $1$ 到点 $v$ 的 $mx$ 和 $mn$ 即为路径上经过的所有点的 $pmx$ 最大值和 $pmn$ 最小值。

不过暴力维护的话时间复杂度显然会炸，于是考虑优化。这时我们可以发现，在操作1中，新添加的点的所有需要维护的信息显然可以快速通过父亲 $u_i$ 快速得到，公式如下：
$$pmn=\min(pmn_{u_i}+w_i,w_i)$$
$$pmx=\max(pmx_{u_i}+w_i,w_i)$$
$$mn=\min(mn_{u_i},pmn)$$
$$mx=\max(mx_{u_i},pmx)$$

于是便可以 $O(N)$ 的复杂度进行维护，询问时直接判断即可。

代码如下：
```cpp
int main(){
	scanf("%d",&t);
	
	while(t--){
		scanf("%d",&n);

		int tot=1;
        mx[1]=mxsum[1]=1;//初始化点1信息
        mn[1]=mnsum[1]=0;//mx为前文pmx，mn为pmn，mxsum为mx，mnsum为mn
		for(int i=1;i<=n;i++){
			char c[10];
			scanf("%s",c+1);
			if(c[1]=='+'){
				int x,y;
				scanf("%d%d",&x,&y);
				mx[++tot]=max(y,mx[x]+y);
				mn[tot]=min(y,mn[x]+y);
				mxsum[tot]=max(mx[tot],mxsum[x]);
				mnsum[tot]=min(mn[tot],mnsum[x]);
			}
			else{
				int u,v,x;
				scanf("%d%d%d",&u,&v,&x);
                //cout<<mnsum[v]<<" "<<mxsum[v]<<" "<<x<<endl;
				if(mnsum[v]<=x&&mxsum[v]>=x) printf("YES\n");//判断是否在范围内
				else printf("NO\n");
			}
		}
	}
}
```
完结撒花 OvO！！！

---

