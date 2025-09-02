# 「TFOI R1」Tree Home

## 题目背景

阳光开朗大男孩天才 Z 今天要向蕉太狼表白力！

众所周知，蕉太狼是一个很可爱的女孩纸。
从前的天才 Z 总是担心因为自己表白失败而受到别人的嘲笑。但是今天，天才 Z 就要做出自己一生中最重要的一件事，那就是真诚地表白，无论后果如何。

出乎意料，蕉太狼其实也喜欢着天才 Z！

天才 Z 开心得像个 0#。

但是没过多久，天才 Z 就被甩力，原因蕉太狼发现天才 Z 对自己的闺蜜有非分之想。

天才 Z 拿出了自己的树状家谱，问候起了自己的祖宗们。

## 题目描述

有一个由 $n - 1$ 条**带权无向边**连接成的有 $n$ 个节点的树，每个节点都有它对应的**编号**以及**权值** $v_{i}$，整棵树的根节点为编号为 $1$ 的节点。

令 $f(a, b, c) = (a - b) \times \left[a^2 + b^2 + a \times b + 3 \times c \times (a + b + c)\right]$，其中 $a,b,c$ 可以为任意整数。同时用 $d_i$ 表示 $i$ 到根节点的每条边的**边权**之和。

现在天才 Z 要进行 $T$ 次询问，每次询问给定四个正整数 $l_{1},r_{1},l_{2},r_{2}$，你要从**编号**在区间 $[l_{1}, r_{1}]$ 和 $[l_{2}, r_{2}]$ 的点中各选择一个点 $p$ 和 $q$，当然你选择的两个点需要保证 $p \neq q$。用 $r$ 表示 $p$ 和 $q$ 的最近公共祖先，要使得 $|f(d_{p} - d_{r}, d_{q} - d_{r}, d_{r})| + |v_{p} - v_{q}|$ 的值最大，而你需要对每次询问输出这个最大值。

## 说明/提示

#### 样例解释

对于第一次询问，我们在两个区间分别取 $4$ 号点和 $6$ 号点即可得出答案 $19211$。

对于第二次询问，两个区间都只能取一个节点，所以答案为 $3$。


#### 数据范围

**本题采用捆绑测试**。

- Subtask 1（5 points）：$1 \leqslant n, T \leqslant 10$。
- Subtask 2（10 points）：$1 \leqslant n, T \leqslant 100$。
- Subtask 3（30 points）：$1 \leqslant n, T \leqslant 3000$。
- Subtask 4（55 points）：无特殊限制。

对于所有数据，$1 \leqslant n, T \leqslant 2 \times 10^5$，$0 \leqslant |w| \leqslant 25$，$1 \leqslant v_{x} \leqslant 10^9$，$1 \leqslant l_{1} \leqslant r_{1} \leqslant n$，$1 \leqslant l_{2} \leqslant r_{2} \leqslant n$，保证树中最大深度不超过 $100$。

**注意：两个区间 $[l_{1}, r_{1}]$ 和 $[l_{2}, r_{2}]$ 可能有重合部分。**

## 样例 #1

### 输入

```
7 2
5 1 7 12 5 9 6
1 2 5
3 1 1
6 2 9
4 6 14
7 6 4
5 2 10
2 4 5 7
1 1 3 3```

### 输出

```
19211
3```

# 题解

## 作者：Super_Cube (赞：5)

# Solution
这里是验题人题解。

我们先推一波式子。

$$
\begin{aligned}
f(a,b,c)
=& \ (a - b)(a^2+b^2+a \cdot b+3c(a+b+c))
\\
f(d_p-d_r,d_q-d_r,d_r)
=& \ (d_p-d_q)[{d_p}^2-2d_p \cdot d_r+{d_r}^2+{d_q}^2-2d_q\cdot d_r+{d_r}^2
\\
+& \ d_p\cdot d_q-d_p\cdot d_r-d_q\cdot d_r+{d_r}^2+3d_r(d_p+d_q-d_r)]
\\
=& \ (d_p-d_q)({d_p}^2+d_p\cdot d_q+{d_q}^2)
\\
=& \ {d_p}^3-{d_q}^3
\end{aligned}
$$

于是可以把询问的式子改为：

$$\max_{\forall p\in[l_1,r_1] \land \forall q \in  [l_2,r_2]} \left\lbrace \left|{d_p}^3-{d_q}^3\right|+\left|v_p-v_q \right| \right\rbrace$$

我们可以把上式认为是 **曼哈顿距离** 的最值查询。

具体地，让每一个节点 $\forall i \in [1,n]$，对应平面直角坐标系里的 $\left({d_i}^3,v_i\right)$。

这里放一道曼哈顿距离最值的模板题：[link](/problem/P5098)。

下面，我引用这道题中高赞题解中曼哈顿距离最值的解法：

>由于 $i$ 和 $j$ 是无序的，我们强制 $x_i \ge x_j$，那么我们对 $y$ 进行分类讨论：  

>如果 $y_i\ge y_j$，那么 $|x_i-x_j|+|y_i-y_j|=x_i-x_j+y_i-y_j=(x_i+y_i)-(x_j+y_j)$。

>答案最大为 $\max \{x+y\}-\min \{x+y\}$。

>如果 $y_i < y_j$，那么 $|x_i-x_j|+|y_i-y_j|=x_i-x_j-y_i+y_j=(x_i-y_i)-(x_j-y_j)$。

>答案最大为 $\max \{x-y\}-\min \{x-y\}$。

>所以我们只需要维护 $x+y$ 和 $x-y$ 的最大值和最小值就行了。

回到这道题，我们需要维护 ${d_i}^3 + v_i$ 和 ${d_i}^3 - v_i$ 的区间最大值和区间最小值。

这是一道经典的 rmq 问题，不带修改，可以用 st 表，线段树，树状数组，分块等数据结构维护。

笔者使用的是 st 表用于维护，时空复杂度均为 $O(n\log n)$，其中预处理为 $O(n\log n)$，单次查询为 $O(1)$。

# Code
```cpp
#include<stdio.h>
#include<vector>
#include<algorithm>
struct edge{
	int to,val;
};
std::vector<edge>v[200005];
int dis[200005];
void dfs(const int&p,const int&dad){
	for(const edge&i:v[p]){
		if(i.to==dad)continue;
		dis[i.to]=dis[p]+i.val;
		dfs(i.to,p);
	}
}
int a[200005];
int n,q;
struct ST{
	struct node{
		long long v1,v2,v3,v4;
		inline friend node operator+(const node&x,const node&y){
			node res;
			res.v1=std::max(x.v1,y.v1);
			res.v2=std::min(x.v2,y.v2);
			res.v3=std::max(x.v3,y.v3);
			res.v4=std::min(x.v4,y.v4);
			return res;
		}
	}st[200005][20];
	void init(){
		for(int i=1;i<=n;++i)
			st[i][0].v1=st[i][0].v2=1ll*dis[i]*dis[i]*dis[i]+a[i],
			st[i][0].v3=st[i][0].v4=1ll*dis[i]*dis[i]*dis[i]-a[i];
		for(int j=1;(1<<j)<=n;++j)
			for(int i=1;i+(1<<j)-1<=n;++i)
				st[i][j]=st[i][j-1]+st[i+(1<<j-1)][j-1];
	}
	node ask(int l,int r){
		int k=std::__lg(r-l+1);
		return st[l][k]+st[r-(1<<k)+1][k];
	}
}st;
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;scanf("%d",&a[i++]));
	for(int i=1,x,y,z;i<n;++i){
		scanf("%d%d%d",&x,&y,&z);
		v[x].push_back((edge){y,z});
		v[y].push_back((edge){x,z});
	}
	dfs(1,0);
	st.init();
	for(int l1,r1,l2,r2;q--;){
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		ST::node l=st.ask(l1,r1),r=st.ask(l2,r2);
		printf("%lld\n",std::max(std::max(l.v1-r.v2,l.v3-r.v4),std::max(r.v1-l.v2,r.v3-l.v4)));
	}
	return 0;
}
```

---

## 作者：longlong666 (赞：1)

[题目](https://www.luogu.com.cn/problem/P9704)

## Solution

先推式子。

注意，为简化式子，将大部分 $\times$ 用 $\cdot$ 代替或不写。

$$
\because f(a,b,c)=(a-b) \times (a^2+b^2+a \cdot b+3 c (a+b+c)) \\
\begin{aligned}
\therefore f(d_p-d_r,d_q-d_r,d_r) &= [(d_p-d_r)-(d_q-d_r)] \times \{ (d_p-d_r)^2+(d_q-d_r)^2+(d_p-d_r) \cdot (d_q-d_r)+3 d_r [(d_p-d_r)+(d_q-d_r)+d_r] \} \\
&= (d_p-d_q) \times [{d_p}^2 - 2 d_p \cdot d_r + {d_r}^2+ {d_q}^2 - 2 d_q \cdot d_r + {d_r}^2 + d_p \cdot d_q - d_p \cdot d_r - d_r \cdot d_q + {d_r}^2 + 3 d_r(d_p+d_q-d_r)] \\
&= (d_p-d_q) \times ({d_p}^2 + {d_q}^2 + 3 {d_r}^2 -3 d_p \cdot d_r -3 d_q \cdot d_r + d_p \cdot d_q + 3 d_r \cdot d_p+3 d_r \cdot d_q-3{d_r}^2)\\
&= (d_p-d_q) \times ({d_p}^2 + {d_q}^2 + d_p \cdot d_q) \\
&= {d_p}^3 + d_p \cdot {d_q}^2 +{d_p}^2 \cdot d_q - d_q \cdot {d_p}^2 - {d_q}^3 - {d_q}^2 \cdot d_p\\
&= {d_p}^3 -{d_q}^3 \\
\end{aligned}
$$

所以可以把询问的式子转化为 $\displaystyle \max_{\forall p \in [l1,r1] \forall q \in [l2,r2]} \{ |{d_p}^3-{d_q}^3|+|v_p-v_q| \}$。

此问题可看为区间**曼哈顿距离**最大值，有此题[板子](https://www.luogu.com.cn/problem/P5098)，下文为阐释此题原理。

先令 ${d_p}^3 \ge {d_q}^3$。具体地，若 ${d_p}^3 < {d_q}^3$ 则交换 $p,q$，后做分类讨论如下：

- 若 $v_p \ge v_q$，即求 $\displaystyle \max_{\forall p \in [l1,r1] \forall q \in [l2,r2]} \{({d_p}^3+v_p)-({d_q}^3+v_q)\}$。

- 若 $v_p < v_q$，即求 $\displaystyle \max_{\forall p \in [l1,r1] \forall q \in [l2,r2]} \{({d_p}^3-v_p)-({d_q}^3-v_q)\}$。

当 $v_p \ge v_q$ 时，要使 $({d_p}^3+v_p)-({d_q}^3+v_q)$ 最大即使 $({d_p}^3+v_p)$ 最大使 $({d_q}^3+v_q)$ 最小。故原式即为 $\displaystyle \max_{\forall p [l1,r1]} ({d_p}^3+v_p) -\displaystyle \min_{\forall q [l2,r2]} ({d_q}^3+v_q)$，维护区间 $({d_p}^3+v_p)$ 最大值和最小值即可。

当 $v_p < v_q$ 时，要使 $({d_p}^3-v_p)-({d_q}^3-v_q)$ 最大即使 $({d_p}^3-v_p)$ 最大使 $({d_q}^3-v_q)$ 最小。故原式即为 $\displaystyle \max_{\forall p [l1,r1]} ({d_p}^3-v_p) -\displaystyle \min_{\forall q [l2,r2]} ({d_q}^3-v_q)$，维护区间 $({d_p}^3-v_p)$ 最大值和最小值即可。

维护区间最大最小值有多种方法，推荐使用 st 表维护。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define lid tr[id].lc
#define rid tr[id].rc
using namespace std;
const int maxn=1e6+10;
int n,m;
int val[maxn];//题目中的 v 数组
int dis[maxn];//题目中的 d 数组
struct node{int to,w;};
vector<node>vt[maxn];
int st[5][maxn][20];//4 个 st 表
inline void dfs(int u,int f){//求出 dis 数组
	for(auto no:vt[u]){
		int v=no.to;
		int w=no.w;
		if(v==f) continue;
		dis[v]=dis[u]+w; dfs(v,u);
	}
}
inline void init(){//初始化 st 表
	for(int xb=1;xb<=4;xb++){
		for(int i=1;i<=n;i++){
			if(xb==1) st[xb][i][0]=dis[i]*dis[i]*dis[i]+val[i];//表 1 维护相加最大值
			else if(xb==2) st[xb][i][0]=dis[i]*dis[i]*dis[i]-val[i];//表 2 维护相减最大值
			else if(xb==3) st[xb][i][0]=dis[i]*dis[i]*dis[i]+val[i];//表 3 维护相加最小值
			else if(xb==4) st[xb][i][0]=dis[i]*dis[i]*dis[i]-val[i];//表 4 维护相减最小值
		}
		for(int j=1;j<=log2(n)+1;j++){
			for(int i=1;i+(1<<j)-1<=n;i++){
				if(xb==1||xb==2) st[xb][i][j]=max(st[xb][i][j-1],st[xb][i+(1<<(j-1))][j-1]);
				else st[xb][i][j]=min(st[xb][i][j-1],st[xb][i+(1<<(j-1))][j-1]);
			}
		}
	}
}
inline int ask(int xb,int L,int R){//查询 [L,R] 区间内最大/最小值
	int k=log2(R-L+1);
	if(xb==1||xb==2) return max(st[xb][L][k],st[xb][R-(1<<k)+1][k]);
	else return min(st[xb][L][k],st[xb][R-(1<<k)+1][k]);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>val[i];
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		vt[u].push_back({v,w});
		vt[v].push_back({u,w});
	}dfs(1,1); init();//建图，求 dis 数组并初始化 st 表
	for(int i=1,l1,l2,r1,r2;i<=m;i++){
		cin>>l1>>r1>>l2>>r2;
		cout<<max({ask(1,l1,r1)-ask(3,l2,r2),ask(2,l1,r1)-ask(4,l2,r2)
		,ask(1,l2,r2)-ask(3,l1,r1),ask(2,l2,r2)-ask(4,l1,r1)})<<endl;//相加最大减最小和相减最大减最小取最小值
	}
	return 0;
}
```

---

## 作者：MrSWdAxiv (赞：1)


[题目传送门](https://www.luogu.com.cn/problem/P9704)

[更好的阅读体验](https://www.cnblogs.com/MithrilSwordXIV/p/17976241)

## 思路

首先我们需要依据输入来建立一棵树并将 $d$ 数组求出来，此操作我们可以用链式前向星来存树，然后 dfs 算出 $d$ 数组。

接着我们需要把题目上给我们的式子推出来：

$$
\operatorname{f}\left(a, b, c \right) = \left(a - b \right)\left[a^2 + b^2 + a \times b + 3 \times c \times \left(a + b + c\right)\right]
$$

$$
\operatorname{f}\left( d_p - d_r,d_q - d_r ,d_r\right) = \left( d_p - d_q \right)\left[ {d_p}^2 - 2d_p\times d_r  +{d_r}^2 + {d_q}^2 - 2d_q\times d_r  +{d_r}^2 + d_p\times d_q - d_p\times d_r -d_q\times d_r + {d_r}^2 +3d_r\left( d_p + d_q - d_r \right)\right] = {d_p}^3-{d_q}^3
$$

所以题中询问的式子：

$$
|\operatorname{f}(d_{p} - d_{r}, d_{q} - d_{r}, d_{r})| + |v_{p} - v_{q}| = |{d_p}^3 - {d_q}^3| + |v_{p} - v_{q}|
$$

这样就化到最简了。此时我们需要把绝对值拆开，有四种情况：

1. $v_p \ge v_q$ 且 ${d_p}^3 \ge {d_q}^3$，那么式子就是 ${d_p}^3 - {d_q}^3 + v_p - v_q$

2. $v_p \ge v_q$ 且 ${d_p}^3 < {d_q}^3$，那么式子就是 ${d_q}^3 - {d_p}^3 + v_p - v_q$

3. $v_p < v_q$ 且 ${d_p}^3 \ge {d_q}^3$，那么式子就是 ${d_p}^3 - {d_q}^3 + v_q - v_p$

4. $v_p < v_q$ 且 ${d_p}^3 < {d_q}^3$，那么式子就是 ${d_q}^3 - {d_p}^3 + v_q - v_p$

我们再令 $a_i = v_i + {d_i}^3$，$b_i = v_i - {d_i}^3$，以上四种情况就可以化简为：

1. $a_p - a_q$

2. $b_p - b_q$

3. $b_q - b_p$

4. $b_q - a_p$

题目要求是让结果最大，那么就相当于我们让最大值减去最小值即能让答案最大，这里我们用两颗线段树 $tree1$ 和 $tree2$ 来维护 $a$ 序列与 $b$ 序列的最大值和最小值，时间复杂度为 $\mathcal{O}\left(n\ \log\ n\right)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define MAX 200005
using namespace std;
struct Tree{
    int l,r,minn,maxn;
}tree1[MAX*4],tree2[MAX*4];//两棵树
int n,T,A[MAX],cnt,head[MAX],a[MAX],b[MAX],dis[MAX],ans;
void pushup1(int k){
    tree1[k].l=tree1[k*2].l;
    tree1[k].r=tree1[k*2+1].r;
    tree1[k].minn=min(tree1[k*2].minn,tree1[k*2+1].minn);
    tree1[k].maxn=max(tree1[k*2].maxn,tree1[k*2+1].maxn);
}
void pushup2(int k){
    tree2[k].l=tree2[k*2].l;
    tree2[k].r=tree2[k*2+1].r;
    tree2[k].minn=min(tree2[k*2].minn,tree2[k*2+1].minn);
    tree2[k].maxn=max(tree2[k*2].maxn,tree2[k*2+1].maxn);
}
void build1(int k,int l,int r){//第一棵树，用来存a数组
    tree1[k].l=l,tree1[k].r=r;
    if(l==r){
        tree1[k].minn=tree1[k].maxn=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build1(k*2,l,mid);
    build1(k*2+1,mid+1,r);
    pushup1(k);
}
void build2(int k,int l,int r){//第二棵树，用来存b数组
    tree2[k].l=l,tree2[k].r=r;
    if(l==r){
        tree2[k].minn=tree2[k].maxn=b[l];
        return;
    }
    int mid=(l+r)>>1;
    build2(k*2,l,mid);
    build2(k*2+1,mid+1,r);
    pushup2(k);
}
Tree merge(Tree Left,Tree Right){
    Tree x;
    x.l=Left.l,x.r=Right.r;
    x.minn=min(Left.minn,Right.minn);
    x.maxn=max(Left.maxn,Right.maxn);
    return x;
}
Tree query1(int k,int l,int r){
    if(tree1[k].l>=l&&tree1[k].r<=r){
        return tree1[k];
    }
    if(r<=tree1[k*2].r)return query1(k*2,l,r);
    if(l>=tree1[k*2+1].l)return query1(k*2+1,l,r);
    return merge(query1(k*2,l,r),query1(k*2+1,l,r));
}
Tree query2(int k,int l,int r){
    if(tree2[k].l>=l&&tree2[k].r<=r){
        return tree2[k];
    }
    if(r<=tree2[k*2].r)return query2(k*2,l,r);
    if(l>=tree2[k*2+1].l)return query2(k*2+1,l,r);
    return merge(query2(k*2,l,r),query2(k*2+1,l,r));
}
struct Edge{
    int to,next,val;
}edge[MAX*2];
void add(int u,int v,int w){//链式前向星
    edge[++cnt].to=v;
    edge[cnt].val=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
void dfs(int x,int fa){//深搜
    for(int i=head[x];i;i=edge[i].next){
        int v=edge[i].to,w=edge[i].val;
        if(v==fa)continue;
        dis[v]=dis[x]+w;
        dfs(v,x);
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>T;
    for(int i=1;i<=n;i++){
        cin>>A[i];
    }
    int u,v,w,l1,r1,l2,r2;
    for(int i=1;i<=n-1;i++){
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        a[i]=A[i]+(dis[i]*dis[i]*dis[i]);
        b[i]=A[i]-(dis[i]*dis[i]*dis[i]);
    }
    build1(1,1,n);
    build2(1,1,n);
    while(T--){
        cin>>l1>>r1>>l2>>r2;
        ans=0;
        Tree a1=query1(1,l1,r1),a2=query1(1,l2,r2),b1=query2(1,l1,r1),b2=query2(1,l2,r2);
        ans=max({ans,a1.maxn-a2.minn,a2.maxn-a1.minn,b1.maxn-b2.minn,b2.maxn-b1.minn});//四种情况
        cout<<ans<<'\n';
    }
    return 0;
}
```


---

## 作者：ccxswl (赞：1)

# P9704 「TFOI R1」Tree Home 题解

推下式子（$p$ 和 $q$ 太难区分，索性换成 $x$ 和 $y$）：

$f(d_x - d_r,d_y-d_r,d_r)$

$=(d_x-d_y)\times [(d_x^2-2d_xd_r+d_r^2)+(d_y^2-2d_yd_r+d_r^2)+(d_xd_y-d_xd_r-d_yd_r+d_r^2)+(3d_xd_r+3d_yd_r+3d_r^2)]$

$=(d_x-d_y)\times (d_x^2+d_y^2+d_xd_y)$

$=d_x^3+d_y^3$

所以：
$$
|f(d_x-d_r,d_y-d_r,d_r)|+|v_x-v_y|=|v_x-v_y|+|d_x^3-d_y^3|
$$
分情况讨论：

- $v_x\geq v_y\ 且\ d_x^3\geq d_y^3$ 时，令 $s1=原式=v_x-v_y+d_x^3-d_y^3=(v_x+d_x^3)-(v_y+d_y^3)$

- $v_x\geq v_y\ 且\ d_x^3<d_y^3$ 时，令 $s2=原式=v_x-v_y+d_y^3-d_x^3=(v_x-d_x^3)-(v_y-d_y^3)$

- $v_x<v_y\ 且\ d_x^3\geq d_y^3$ 时，令 $s3=原式=v_y-v_x+d_x^3-d_y^3=(v_y-d_y^3)-(v_x-d_x^3)$

- $v_x<v_y\ 且\ d_x^3<d_y^3$ 时，令 $s4=原式=v_y-v_x+d_y^3-d_x^3=(v_y+d_y^3)-(v_x+d_x^3)$

令 $a_i=v_i+d_i^3$，$b_i=v_i-d_i^3$，则：

- $s1=a_x-a_y$
- $s2=b_x-b_y$
- $s3=b_y-b_x$
- $s4=a_y-a_x$

$s1$ 的最大值肯定是最大的 $a_x$ 减最小的 $a_y$，其余情况同理。答案就是这四种情况的最大值。

维护 $a_i$ 和 $b_i$ 的区间最值就行了。

代码用线段树实现，复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int read();

const int maxN = 2e5 + 7;

struct Seg {
    struct Tree {
        int l, r;
        int mn, mx;
    } t[maxN << 2];
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    Tree merge(Tree L, Tree R) {
        Tree tmp;
        tmp.l = L.l, tmp.r = R.r;
        tmp.mn = min(L.mn, R.mn);
        tmp.mx = max(L.mx, R.mx);
        return tmp;
    }
    void upd(int p) {
        t[p] = merge(t[ls], t[rs]);
    }
    void build(int L, int R, int p, int B[]) {
        t[p].l = L, t[p].r = R;
        if (L == R) t[p].mn = t[p].mx = B[L];
        else {
            int mid = (L + R) >> 1;
            build(L, mid, ls, B);
            build(mid + 1, R, rs, B);
            upd(p);
        }
    }
    Tree ask(int L, int R, int p) {
        if (L <= t[p].l && t[p].r <= R) return t[p];
        if (R <= t[ls].r) return ask(L, R, ls);
        if (t[rs].l <= L) return ask(L, R, rs);
        return merge(ask(L, R, ls), ask(L, R, rs));
    }
} A, B;//线段树

int n, Q, v[maxN], d[maxN];

struct edge {
    int t, w;
};
vector<edge> E[maxN];
void dfs(int x, int fa) {
    for (auto to : E[x]) {
        if (to.t == fa) continue;
        d[to.t] = d[x] + to.w;//处理d数组
        dfs(to.t, x);
    }
}

int a[maxN], b[maxN];
int pow(int x) {
    return x * x * x;
}

int main() {
    n = read(), Q = read();
    for (int i = 1; i <= n; i++)
        v[i] = read();
    for (int i = 1; i < n; i++) {
        int x = read(), y = read(), z = read();
        E[x].push_back({y, z});
        E[y].push_back({x, z});
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        a[i] = v[i] + pow(d[i]),
        b[i] = v[i] - pow(d[i]);
    A.build(1, n, 1, a);
    B.build(1, n, 1, b);
    while (Q--) {
        int l = read(), r = read(),
            x = read(), y = read();
        int ans = 0;
        auto tal = A.ask(l, r, 1), tax = A.ask(x, y, 1);
        auto tbl = B.ask(l, r, 1), tbx = B.ask(x, y, 1);
        ans = max(ans, tal.mx - tax.mn);//四种情况
        ans = max(ans, tbl.mx - tbx.mn);
        ans = max(ans, tbx.mx - tbl.mn);
        ans = max(ans, tax.mx - tal.mn);
        cout << ans << '\n';
    }
}

int read() {
    int s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        s = s * 10 + c - 48;
        c = getchar();
    }
    return s * w;
}
```





---

## 作者：Genius_Star (赞：0)

### 思路：

首先带入爆推式子：

$$\begin{aligned} 原式 & = (d_p - d_q) ((d_p - d_r)^2 + (d_q - d_r)^2 + (d_p - d_r)(d_q - d_r) + 3d_r(d_p + d_q - d_r)) \\ & = (d_p - d_q)(d_p^2 + d_r^2 + d_q^2 + d_r^2 - 2dr(d_p + d_q) + d_p d_q - d_r(d_p + d_q) + d_r^2 + 3dr(d_p + d_q) - 3d_r^2) \\ & = (d_p - d_q)(d_p^2 + d_p d_q + d_q^2) \\ &= d_p^3 - d_q^3 \end{aligned}$$

故我们要求的是：

$$|d_p^3 - d_q^3| + |v_p - v_q|$$

的最大值；那么令 $x_{i, 1} = d_p^3, x_{i, 2} = v_p$。

考虑状压 $T_{i, S}$，其中 $S$ 表示状态，第 $j$ 位为 $1$ 则是 $-x_{i,j}$，否则是 $x_{i, j}$。

则最大值是：

$\max\limits_{S = 0}^3 Tmax(l_1, r_1)_S + Tmax(l_2, r_2)_{S \operatorname{xor} 3}$

即等价于枚举每个绝对值取到的情况，其中 $Tmax(l, r)_S$ 表示 $\max\limits_{i = l}^r T_{i, S}$。

使用线段树或者 ST 表维护区间最大值即可，时间复杂度为 $O(n \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
const ll INF = 1e18;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll n, q, u, v, w, l1, r1, l2, r2, ans;
ll d[N], a[N], A[N], B[N];
vector<pair<int, int>> E[N];
inline void add(int u, int v, int w){
	E[u].push_back({v, w});
	E[v].push_back({u, w});
}
inline void dfs(int u, int fa){
	for(auto t : E[u]){
		int v = t.fi, w = t.se;
		if(v == fa)
		  continue;
		d[v] = d[u] + w;
		dfs(v, u);
	}
}
class Tree{
public:
	struct Node{
		int l, r;
		ll Max;
	}X[N << 2];
	inline void pushup(int k){
		X[k].Max = max(X[k << 1].Max, X[k << 1 | 1].Max);
	}
	inline void build(int k, int l, int r){
		X[k].l = l, X[k].r = r;
		if(l == r){
			X[k].Max = -INF;
			return ;
		}
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		pushup(k);
	}
	inline void update(int k, int i, ll v){
		if(X[k].l == i && i == X[k].r){
			X[k].Max = v;
			return ;
		}
		int mid = (X[k].l + X[k].r) >> 1;
		if(i <= mid)
		  update(k << 1, i, v);
		else
		  update(k << 1 | 1, i, v);
		pushup(k);
	}
	inline ll Askmax(int k, int l, int r){
		if(X[k].l == l && r == X[k].r)
		  return X[k].Max;
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  return Askmax(k << 1, l, r);
		else if(l > mid)
		  return Askmax(k << 1 | 1, l, r);
		else
		  return max(Askmax(k << 1, l, mid), Askmax(k << 1 | 1, mid + 1, r));
	}
}T[4];
bool End;
int main(){
	n = read(), q = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	for(int i = 1; i < n; ++i){
		u = read(), v = read(), w = read();
		add(u, v, w);
	}
	dfs(1, 0);
	T[0].build(1, 1, n), T[1].build(1, 1, n), T[2].build(1, 1, n), T[3].build(1, 1, n);
	for(int i = 1; i <= n; ++i){
		A[i] = d[i] * d[i] * d[i];
		B[i] = a[i];
		T[0].update(1, i, A[i] + B[i]);
		T[1].update(1, i, -A[i] + B[i]);
		T[2].update(1, i, A[i] - B[i]);
		T[3].update(1, i, -A[i] - B[i]);
	}
	while(q--){
		ans = 0;
		l1 = read(), r1 = read(), l2 = read(), r2 = read();
		for(int S = 0; S < 4; ++S)
		  ans = max(ans, T[S].Askmax(1, l1, r1) + T[S ^ 3].Askmax(1, l2, r2));
		write(ans);
		putchar('\n'); 
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：a1a2a3a4a5 (赞：0)

# P9704 Tree Home 


## 题意

1.  求一个式子的最大值，两个未知数可以在区间 $[l_{1}, r_{1}]$ 和 $[l_{2}, r_{2}]$ 的点中各选择一个点 $p$ 和 $q$。

## 思路
1. $d $ 数组明显可以跑 dfs 预处理出来，这个树在整个题中就毫无用处了。
2. 一看这个函数并且给了字母，我们不妨直接给他展开。

   $f(a, b, c) $

   $= (a - b) \times \left[a^2 + b^2 + a \times b + 3 \times c \times (a + b + c)\right]$

   $=\left(d_{p}-d_{q}\right)\left[d_{p}^{2}+d_{r}^{2}-2d_{p}d_{r}+d_{q}^{2}+d_{r}^{2}-2d_{q}d_{r}+d_{p}d_{q}-d_{r}d_{q}+d_{r}^{2}+3d_{r}\left(d_{p}+d_{q}+d_{r}^{2}\right)\right] $

   $=\left( d_{p}-d_{q}\right)\left( d_{p}^{2}+d_{q}^{2}+d_{p}d_{q}\right)  $

   $=d_{p}^{3}+d_{q}^{2}d_{p}-d_{q}d_{p}^{2}-d_{q}^{3}-d_{p}d_{q}^{2}$

   $=d_{p}^{3}-d_{q}^{3}$
   
   整个函数就表达了这一点东西，这个式子都是迷惑你的。
3. $v $ 数组输入时就给了，这时候我们可以已经把式子化为了最简：

   $\left| d_{p}^{3}-d_{q}^{3}\right|+ |v_{p} - v_{q}|$
   
   这时我们无法化简了，任何巧妙的方法都用不了了，所以直接开始分类讨论把绝对值去掉：

| $d_p^3 $ 与 $ d_q^3$ | $v_p $ 与 $ v_q$ | 式子 | 整理 |
| :----------: | :----------: | :----------: | :----------: |
| $ > $ | $ > $ | $d_p^3-d_q^3+v_p-v_q$ | $jia_p-jia_q$ |
| $ < $ | $ > $ | $d_q^3-d_p^3+v_p-v_q$ | $jian_q-jian_p$ |
| $ > $ | $ < $ | $d_p^3-d_q^3+v_q-v_p$ | $jian_p-jian_q$ |
| $ < $ | $ < $ | $d_q^3-d_p^3+v_q-v_p$ | $jia_q-jia_p$ |

看完这个表格你的表情是这样的：>.< 这是什么意思？式子太长了，我们定义两个函数简化一下：

$ jia_i=d_i^3+v_i $

$ jian_i=d_i^3-v_i $

然后通过整理可以得出表格的第四列，很明显的是我们要这个数最大，所以可以用 st 表 预处理这两个函数的区间最大值和最小值，用最大值减最小值就可以让答案最大了，在这四个情况里取最大值。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,v[210000],d[210000],jiama[210000][32],jiami[210000][32],jianmi[210000][32],jianma[210000][32],lo[210000];
vector<int> dian[210000],bian[210000];
void dfs(int x,int f,int he)
{
	d[x]=he;
	int chang=dian[x].size();
	for(int i=0,zou;i<chang;i++)
	{
		zou=dian[x][i];
		if(zou==f) continue;
		dfs(zou,x,he+bian[x][i]);
	}
}
int chajiama(int l,int r)//查询函数。
{
	int s=lo[r-l+1];
	return max(jiama[l][s],jiama[r-(1<<s)+1][s]);
}
int chajiami(int l,int r)
{
	int s=lo[r-l+1];
	return min(jiami[l][s],jiami[r-(1<<s)+1][s]);
}
int chajianma(int l,int r)
{
	int s=lo[r-l+1];
	return max(jianma[l][s],jianma[r-(1<<s)+1][s]);
}
int chajianmi(int l,int r)
{
	int s=lo[r-l+1];
	return min(jianmi[l][s],jianmi[r-(1<<s)+1][s]);
}
signed main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1,u,v,w;i<n;i++)
		cin>>u>>v>>w,
		dian[u].push_back(v),dian[v].push_back(u),
		bian[u].push_back(w),bian[v].push_back(w);
	dfs(1,0,0);//预处理 d 数组。
	for(int i=1;i<=n;i++)
		jiama[i][0]=d[i]*d[i]*d[i]+v[i],
		jiami[i][0]=d[i]*d[i]*d[i]+v[i],
		jianma[i][0]=d[i]*d[i]*d[i]-v[i],
		jianmi[i][0]=d[i]*d[i]*d[i]-v[i];
	for(int i=2;i<=200001;i++) lo[i]=lo[i/2]+1;//预处理 log 数组。
	for(int j=1;j<=30;j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)//st表基本预处理。
		{
			jiama[i][j]=max(jiama[i][j-1],jiama[i+(1<<(j-1))][j-1]);
			jianma[i][j]=max(jianma[i][j-1],jianma[i+(1<<(j-1))][j-1]);
			jiami[i][j]=min(jiami[i][j-1],jiami[i+(1<<(j-1))][j-1]);
			jianmi[i][j]=min(jianmi[i][j-1],jianmi[i+(1<<(j-1))][j-1]);
		}
	}
	for(int i=1,o1,o2,l,r,da;i<=t;i++)
	{
		cin>>o1>>o2>>l>>r,da=0;
		da=max(da,chajiama(o1,o2)-chajiami(l,r));
		da=max(da,chajianma(l,r)-chajianmi(o1,o2));
		da=max(da,chajianma(o1,o2)-chajianmi(l,r));
		da=max(da,chajiama(l,r)-chajiami(o1,o2));
		cout<<da<<"\n";//根据推的公式写出的代码。
	}
	return 0;
}
```

---

