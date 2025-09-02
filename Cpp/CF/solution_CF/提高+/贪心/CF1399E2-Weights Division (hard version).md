# Weights Division (hard version)

## 题目描述

Easy and hard versions are actually different problems, so we advise you to read both statements carefully.

You are given a weighted rooted tree, vertex $ 1 $ is the root of this tree. Also, each edge has its own cost.

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. A parent of a vertex $ v $ is the last different from $ v $ vertex on the path from the root to the vertex $ v $ . Children of vertex $ v $ are all vertices for which $ v $ is the parent. A vertex is a leaf if it has no children. The weighted tree is such a tree that each edge of this tree has some weight.

The weight of the path is the sum of edges weights on this path. The weight of the path from the vertex to itself is $ 0 $ .

You can make a sequence of zero or more moves. On each move, you select an edge and divide its weight by $ 2 $ rounding down. More formally, during one move, you choose some edge $ i $ and divide its weight by $ 2 $ rounding down ( $ w_i := \left\lfloor\frac{w_i}{2}\right\rfloor $ ).

Each edge $ i $ has an associated cost $ c_i $ which is either $ 1 $ or $ 2 $ coins. Each move with edge $ i $ costs $ c_i $ coins.

Your task is to find the minimum total cost to make the sum of weights of paths from the root to each leaf at most $ S $ . In other words, if $ w(i,       j) $ is the weight of the path from the vertex $ i $ to the vertex $ j $ , then you have to make $ \sum\limits_{v \in       leaves} w(root, v) \le S $ , where $ leaves $ is the list of all leaves.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
4 18
2 1 9 2
3 2 4 1
4 1 1 2
3 20
2 1 8 1
3 1 7 2
5 50
1 3 100 1
1 5 10 2
2 3 123 2
5 4 55 1
2 100
1 2 409 2```

### 输出

```
0
0
11
6```

# 题解

## 作者：dead_X (赞：5)

## 题意 
给定一棵树，边带权，每一次可以将一条边的权值除以 $2$ 并向下取整并花费 $1$ 或 $2$ 硬币，问要使所有叶子到根的距离和不超过 $S$ 的最小花费硬币。
## 思路
注意到操作次数不会超过 $nlogw$ 次，即每条边最多 $logw$ 次后就会变成 $0$ 。

所以我们可以暴力用 $set$ 维护最优决策。

~~先 $dfs$ 出每条边经过了几遍，然后全部放入 $set$ 里，$set$ 根据将这条边除以 $2$ 再除以 $coin$ 后距离和减小的值排序，每次取出最优解，执行操作后再放回 $set$ 中，当满足要求时退出并输出答案。~~

~~记得开 $multiset$ 避免两个优先级相同的解被吞了一个。~~

~~恭喜你，喜提 $\red{\text{Wrong answer on pretest 21}}$~~

这个贪心显然是错的！比如这组数据
```
1
3 10099
1 2 10000 2 
1 3 100 1
```
虽然将第一条边除以 $2$ 收益更大，但是第二条边除以 $2$ 已经满足要求了。

不过有了 $E1$ 的铺垫，解决这题并不是很难。

考虑答案，一定是取了一些最优的 $coin=1$ 和一些最优的 $coin=2$d 的决策。那么我们考虑将 $coin=1$ 和 $coin=2$ 分别放入两个 $set$ ，然后分别算出只用 $x$ 个 $coin=1$ 或 $coin=2$ 能减小的 $S$ 。然后枚举一边，并二分确定另一边的答案即可。

时间复杂度：$O(n(dfs)+nlognlogw(set)+nlogw^2(bs))$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline long long readll(){
   long long s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int to[1000003],nxt[1000003],head[1000003],val[1000003],f[1000003],t[1000003],cnt=0;
int d[1000003];
struct cmp  
{  
    bool operator ()(const pair<int,int> &a, const pair<int,int> &b)  
    {  
        if(1LL*(a.first-(a.first/2))*a.second!=1LL*(b.first-(b.first/2))*b.second) return 1LL*(a.first-(a.first/2))*a.second>1LL*(b.first-(b.first/2))*b.second; 
		return a.first>b.first; 
    }  
};  
void dfs(int x,int fa,int from)
{
	if(d[x]==1 && x!=1) 
	{
		t[from]=1;
		return ;
	}
	for(int i=head[x]; i; i=nxt[i]) if(to[i]!=fa)
	{
		dfs(to[i],x,i);
		t[from]+=t[i];
	}
	return ;
}
multiset<pair<int,int>,cmp> s1,s2;
long long ans1[5000003],ans2[5000003];
int cnt1,cnt2,n,m,ans;
int bs(long long k)
{
	int res=cnt2,l=0,r=cnt2;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(ans2[mid]>=k) res=mid,r=mid-1; else l=mid+1;
	}
	return res;
}
int main()
{
	int T=read(); while(T--)
	{
		s1.clear(),s2.clear(),cnt=cnt1=cnt2=0;
		n=read(),ans=1000000007,m=(n-1)<<1;
		for(int i=1; i<=n; i++) head[i]=0,d[i]=0;
		for(int i=1; i<=m; i++) t[i]=0;
		long long S=-readll(); 
		for(int i=1; i<n; i++) 
		{
			int u=read(),v=read(),w=read(),qwq=read();
			to[++cnt]=v,val[cnt]=w,f[cnt]=qwq,nxt[cnt]=head[u],head[u]=cnt;
			to[++cnt]=u,val[cnt]=w,f[cnt]=qwq,nxt[cnt]=head[v],head[v]=cnt;
			d[u]++,d[v]++;
		}
		dfs(1,1,0);
		for(int i=1; i<=m; i++) if(t[i]) {
			S+=1LL*val[i]*t[i];
			if(f[i]==1) s1.insert(make_pair(val[i],t[i]));
			else s2.insert(make_pair(val[i],t[i]));
		}
		long long tS=0;
		while(tS<=S)
		{
			if(s1.empty()) break;
			pair<int,int> tmp=*s1.begin();
			s1.erase(s1.begin());
			tS+=1LL*(tmp.first-(tmp.first/2))*tmp.second;
			tmp.first/=2;
			if(tmp.first) s1.insert(tmp);
			ans1[++cnt1]=tS;
		}
		tS=0;
		while(tS<=S)
		{
			if(s2.empty()) break;
			pair<int,int> tmp=*s2.begin();
			s2.erase(s2.begin());
			tS+=1LL*(tmp.first-(tmp.first/2))*tmp.second;
			tmp.first/=2;
			if(tmp.first) s2.insert(tmp);
			ans2[++cnt2]=tS;
		}
		for(int i=0; i<=cnt1; i++) 
		{
			if(ans1[i]+ans2[cnt2]<S) continue;
			if(ans1[i]>=S) { ans=min(ans,i); break; }
			ans=min(ans,i+2*bs(S-ans1[i]));
		}
		printf("%d\n",ans);
	}
    return 0;
}
//By dead_X
```

---

## 作者：Nightingale_OI (赞：4)

这题是一道 $ 2 \times 10^4 $ 的多测题。

给你一棵树，树上每条边有对应的边权 $ w_i $ 和操作代价 $ c_i $ 。

让你对一些边进行操作，使它的边权变成 $ \lfloor \frac{w_i}{2} \rfloor $ 。

问你至少付出多少代价可以使所有叶子结点到根节点的路径权值和不超过 $ S $ 。

一条边显然可以被多个叶子结点计算答案。

 $ n\leq 10^5 $ 
 
 $ \sum n \leq 10^5 $ 
 
------------

观察到只有 $ 2 $ 种代价 $ c_i $ 所以可以先预处理，再枚举操作多少代价为   $ 2 $ 的边。

预处理一种操作代价的边，就可以直接贪心了，毕竟操作代价相等。

可以使用 ` priority_queue ` 进行处理，贪心地选择操作产生贡献（答案变化）最大的边。

记第 $ i $ 条边在 $ d_i $ 个叶子结点到根结点的路径上，贡献就是 $ ( w_i - \lfloor \frac{w_i}{2} \rfloor ) \times d_i $  。

对于一条边计算完答案要记得使 $ w_i = \lfloor \frac{w_i}{2} \rfloor $ ，在重新弹入优先队列。

因为选代价为 $ 2 $ 的边越多，需要选的代价为 $ 1 $ 的边数量单调递减，可以直接用双指针计算答案。

------------

程序每组数据复杂度 $ O( \sum_{i = 1}^{n - 1}{ \log_{2}{w_i} } \times \log_{2}n) $ 。

计算答案的复杂度是 $ O( \sum_{i = 1}^{n - 1}{ \log_{2}{w_i} } ) $ 可以忽略不计。

------------

代码如下 （~~非常的短~~)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
long long now,mst;
//xy在这里有两种意思
//在表示边是x是指向的点，y是边的编号
//在表示贡献时x是边的权值，y是边的覆盖叶节点数量
struct xy{int x,y;};
#define dv(a) (1ll*(a.x-(a.x>>1))*a.y)//计算贡献，如果更改一次则贡献是多少
bool operator < (xy a,xy b){return dv(a)<dv(b);}
xy ls;
long long sum;
int aa[101010],bb[101010],vs[101010];
long long a[2020202],as;
long long b[2020202],bs;
vector<xy>q[101010];
priority_queue<xy>p;
int dfs(int x,int fa){
	int siz=1,sf=0;
	for(register int i=0;i<q[x].size();++i){
		if(q[x][i].x==fa)continue;
		sf=1;
		vs[q[x][i].y]=dfs(q[x][i].x,x);
		siz+=vs[q[x][i].y];
	}
	return siz-sf;//返回叶节点个数
}
void doing(){
	cin>>n>>mst;
	for(register int i=1;i<=n;++i)q[i].clear();
	for(register int i=1;i<n;++i){
		scanf("%d %d %d %d",&s,&l,&aa[i],&bb[i]);
		q[s].push_back((xy){l,i});
		q[l].push_back((xy){s,i});
		vs[i]=0;
	}
	dfs(1,0);
	now=as=sum=0;
	//计算花费为1的所有边操作时能产生的贡献降序
	for(register int i=1;i<n;++i){
		if(bb[i]==2)continue;
		now+=1ll*aa[i]*vs[i];
		p.push((xy){aa[i],vs[i]});
	}
	mst-=now;
	while(now){
		ls=p.top();p.pop();
		sum+=dv(ls);
		a[++as]=dv(ls);
		now-=dv(ls);
		ls.x>>=1;
		p.push(ls);
	}
	while(p.size())p.pop();
	now=bs=0;
	//计算花费为2的所有边操作时能产生的贡献降序
	for(register int i=1;i<n;++i){
		if(bb[i]==1)continue;
		now+=1ll*aa[i]*vs[i];
		p.push((xy){aa[i],vs[i]});
	}
	mst-=now;
	while(now){
		ls=p.top();p.pop();
		b[++bs]=dv(ls);
		now-=dv(ls);
		ls.x>>=1;
		p.push(ls);
	}
	while(p.size())p.pop();
	mst=-mst;
	if(mst<=0ll){printf("0\n");return;}//一开始就符合要求，不用操作，但要判掉
	s=as+bs*2+1;
	//枚举要删多少花费为2的边，并得到答案
	for(register int i=0;i<=bs;++i){
		sum+=b[i];
		while(sum-a[as]>=mst && as)sum-=a[as--];
		if(sum>=mst && as+i*2<s)s=as+i*2;
	}
	if(s==as+bs*2+1)s=-1;
	printf("%d\n",s);
}
int main(){
	int t;
	cin>>t;
	while(t--)doing();
	return 0;
}
```

---

## 作者：lytqwq (赞：3)


本题解已审过，感谢大佬指正时间复杂度


题目链接：[https://www.luogu.com.cn/problem/CF1399E2](https://www.luogu.com.cn/problem/CF1399E2)

我们先计算出每条边对叶子节点的贡献次数，用一遍**DFS**就能解决

然后开个结构体储存边的信息：
1. 对叶子节点贡献次数 **Vis**
1. 当前权值 **Wi**
1. 改变的花费 **Ci**


一个错误的贪心就是按照 **Vis×(Wi-Wi/2)×1.0÷Ci**排，开优先队列，然后从大到小选。因为可能后面有更好的选择

考虑到**Ci<=2**，我们开三个优先队列，一个存所有**Ci**的情况，一个开**Ci=1**的，一个开**Ci=2**的。按照 **Vis×(Wi-Wi/2)×1.0÷Ci**排。

当**Ci=1**的优先队列的队首可以直接完成要求，就选它后**break**。当**Ci=2**的优先队列的队首可以完成要求就选它，然后检查前面**Ci=1**的选过的元素中有没有可以放弃的。

如果不能直接完成要求，我们就直接找**Ci**所有情况的队首。

```
因为一条边在进行一次操作后会减半，随后重新加入优先队列。
因此一条边最坏会加入log次，因此总复杂度最大为O(n*logn*log(nlogn))

```
**感谢** [大佬](https://www.luogu.com.cn/user/90610) **指正**

AC情况：[https://www.luogu.com.cn/record/37201605](https://www.luogu.com.cn/record/37201605)

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int t,n;
long long int S,qaq;
int Head[N],cnt,Next[N*2],V[N*2],W[N*2],C[N*2],ovo[N*2],f[N*2];
long long int bef;
struct d{
	long long int Wi,Ci,Vis;
	bool operator < (const d x) const {return ((Wi-Wi/2)*Vis*1.0/Ci)<((x.Wi-x.Wi/2)*x.Vis*1.0/x.Ci);}
}qwq,ouo;
priority_queue<d> Q,Q2,Q3;
void add(int u,int v,int w,int c){
	V[cnt]=v;
	W[cnt]=w;
	C[cnt]=c;
	Next[cnt]=Head[u];
	Head[u]=cnt++;
	return ;
}
int vis[N];
void dfs(int u,int father){
	for(int i=Head[u];i!=-1;i=Next[i]){
		if(V[i]!=father){
			dfs(V[i],u);
			ovo[i]+=vis[V[i]];
			vis[u]+=vis[V[i]];
		}
	}
	if(vis[u]==0)vis[u]=1;
}
int main(){
	scanf("%d",&t);
	while(t--){
		memset(Head,-1,sizeof(Head));
		memset(ovo,0,sizeof(ovo));
		memset(vis,0,sizeof(vis));
		cnt=0;qaq=0;bef=1e18;
		scanf("%d%lld",&n,&S);
		for(int i=1;i<=n-1;i++){
			int u,v,w,c;
			scanf("%d%d%d%d",&u,&v,&w,&c);
			add(u,v,w,c);
			add(v,u,w,c);
		}
		dfs(1,0);
		while(!Q.empty()){
			Q.pop();
		}
		while(!Q2.empty()){
			Q2.pop();
		}
		while(!Q3.empty()){
			Q3.pop();
		}
		for(int i=0;i<=(2*n-3);i++){
			qwq.Wi=W[i];
			qwq.Vis=ovo[i];
			qaq+=qwq.Wi*qwq.Vis;
			qwq.Ci=C[i];
			if(C[i]==1){
				Q2.push(qwq);
			}
			else{
				Q3.push(qwq);
			}
			Q.push(qwq);
		}
		qaq-=S;
		int ans=0;
		while(!Q.empty()&&qaq>0){
			if(!Q2.empty()){
				ouo=Q2.top();
				if(qaq<=ouo.Vis*(ouo.Wi-ouo.Wi/2)){
					ans+=ouo.Ci;
					break;
				}
			}
			if(!Q3.empty()){
				ouo=Q3.top();
				if(qaq+bef<=ouo.Vis*(ouo.Wi-ouo.Wi/2)){
					ans+=1;
					break;
				}
				if(qaq<=ouo.Vis*(ouo.Wi-ouo.Wi/2)){
					ans+=ouo.Ci;
					break;
				}
			}
			qwq=Q.top();
			ans+=qwq.Ci;
			qaq-=(qwq.Wi-qwq.Wi/2)*qwq.Vis;
			bef=min(bef,(qwq.Wi-qwq.Wi/2)*qwq.Vis);
			qwq.Wi=qwq.Wi/2;
			if(qwq.Ci==1){
				Q2.pop();
				Q2.push(qwq);
			}
			else{
				Q3.pop();
				Q3.push(qwq); 
			}
			Q.pop();
			Q.push(qwq);
		}
		printf("%d\n",ans);
	}
}
```




---

## 作者：AbsMatt (赞：3)

### [题目传送器](https://www.luogu.com.cn/problem/CF1399E2)

### [Easy Version](https://www.luogu.com.cn/problem/CF1399E1)

### [更爽的阅读体验](https://www.luogu.com.cn/blog/yaohaoyou/solution-cf1399e2)

### [Easy Version solution](https://www.luogu.com.cn/blog/yaohaoyou/solution-cf1399e1)

### CF 2200

## 题意
翻译讲的很清楚了，这里就不多展开了。

## 做法
[Easy Version](https://www.luogu.com.cn/problem/CF1399E1) 保证了边权的花费为 $1$，所以直接丢进大根堆然后贪心就行了。但是本题的边权花费为 $1$ 或 $2$，如果直接将边权为 $2$ 的贡献 $\times 2$ 会 Wrong answer on test 21，给一个 Hack。
```
input：
1
3 10099
1 2 10000 2 
1 3 100 1

ans：
1

Hack by dead_X
```
此时还想贪心就变得非常困难，所以可以思考将答案划分成选择边权花费为 $1$ 的答案 $+$ 选择边权花费为 $2$ 的答案。当只选择边权花费为 $1$ 的答案时，可以确定操作的顺序（即 Easy Version），同理，只选择边权花费为 $2$ 的答案也可以提前处理操作顺序。

然后只要枚举要操作花费为 $1$ 的次数，并计算花费为 $2$ 的次数即可。此时的时间复杂度为 $O(n^2\times \log n)$，无法通过此题。只需将计算花费为 $2$ 的次数用双指针优化掉即可，时间复杂度为 $O(n \times \log n)$，记得处理操作全是花费为 $1$ 和 $2$ 的答案，开 long long。

### [AC Code](https://codeforces.com/contest/1399/submission/239459263)

---

## 作者：wangjiajian (赞：2)

### 思路

**考虑 $\forall c_i = 1$ 的 easy version**

既然处理每条边的代价都一样，那么就要优先选择处理对 $\sum_{v\in leaves} w(root, v)$ 贡献大的边，贪心处理即可。

按贡献贪心：dfs一次得到 $edge\_son_i$，表示根节点通过第 $i$ 条边能到达几个叶子节点。那么该点的贡献即为 $edge\_son_i \times (w_i - \left \lfloor \frac{w_i}{2} \right \rfloor )$。把每条边的贡献放入优先队列中，每次处理一条边，就弹出它并把它的 $w_i$ 除以 $2$，然后把它新的贡献再次加入优先队列即可。

**考虑 $\forall c_i \in {1, 2}$**

此时已经不能贪心（不能将贡献除以 $c_i$。举个例子，删除两条边的贡献都满足条件，此时不应当取贡献大的，而应该取花费小的。）

考虑将 $c_i = 1$ 的情况与 $c_i = 2$ 的情况分开处理。仿照上面 easy version 的方案，用优先队列分别贪心选择，并分别处理出 $c_i = 1$ 和 $c_i = 2$ 的边的按贡献排序的序列。

注意到，每多选一个 $c_i = 2$ 的操作，$c_i = 1$ 的操作次数就会减少。因此，先尝试全选 $c_i = 1$ 的情况，再逐个减少贡献小的 $c_i = 1$ 的操作，并随之增加贡献大的 $c_i = 2$ 的操作。最后，尝试全选 $c_i = 2$ 的操作。把这个过程中每一个满足条件的花费取最小值即可。

### AC代码（代码具体解释见注释）

```cpp
#include <bits/stdc++.h>
#define N (int)(1e5+2)
#define ll long long
using namespace std;

int n, x, y, z, zz, edge_son[N<<1];  // edge_son[i] 为根节点通过第 i 条边能到达几个叶子节点
int cnt_star, head[N], nxt[N<<1], to[N<<1], w[N<<1], c[N<<1];
ll S, sum, ans, cost;  // sum 为当前整棵树的 Sigma:w(1, v) (v is leaf), cost 为当前花费, ans 为答案
priority_queue<pair<ll, int> > cost1_edge, cost2_edge;  // 贪心选择最大贡献大优先队列
vector<pair<ll, int> > cost1_range, cost2_range;  // 记录下按贡献排序的操作排列

inline void add(int u, int v, int wei, int cst) {
    nxt[++cnt_star] = head[u];
    to[cnt_star] = v;
    w[cnt_star] = wei;
    c[cnt_star] = cst;
    head[u] = cnt_star;
}

inline void init() {  // 初始化
    ans = INT_MAX;
    sum = cnt_star = cost = 0;
    for(register int i=1; i<=n; i++)
        head[i] = 0;
    cost1_range.clear(), cost2_range.clear();
    while(!cost1_edge.empty())
        cost1_edge.pop();
    while(!cost2_edge.empty())
        cost2_edge.pop();
}

inline void input() {  // 输入
    scanf("%d%lld", &n, &S);
    for(int i=1; i<n; i++) {
        scanf("%d%d%d%d", &x, &y, &z, &zz);
        add(x, y, z, zz), add(y, x, z, zz);
    }
}

inline int dfs(int u, int fa) {  // dfs 查找每条边的 edge_son
    int tmp, ret = 0;
    for(int i=head[u]; i; i=nxt[i]) {
        if(to[i] == fa)
            continue;
        tmp = dfs(to[i], u);
        if(tmp != 0)
            edge_son[i] = tmp;  // 该边连向的点之下的叶子节点
        else  
            edge_son[i] = 1;  // 该边连向叶子节点
        ret += edge_son[i];
    	if(i & 1)  
    		edge_son[i+1] = edge_son[i];  // 因为建图是建双边，因此需要把另一条赋相同的值
    	else
			edge_son[i-1] = edge_son[i];	
    }
    return ret;
}

inline void build_range() {
    for(int i=1; i<=cnt_star; i+=2) {  // 将每条边的贡献都放进优先队列
        sum = sum+(ll)edge_son[i]*w[i];
        if(c[i] == 1)
            cost1_edge.push(make_pair((ll)edge_son[i]*(w[i]-w[i]/2), i));
        else
            cost2_edge.push(make_pair((ll)edge_son[i]*(w[i]-w[i]/2), i));
    }
    pair<ll, int> tmp;
    while(!cost1_edge.empty()) {  // 处理出按贡献大小排序的操作排列
        tmp = cost1_edge.top();
        cost1_edge.pop();
        if(tmp.first == 0)
            continue;
        w[tmp.second] /= 2;  // 对该边进行操作，即除以二
        cost1_range.emplace_back(tmp);  // 放入排列中
        cost1_edge.push(make_pair((ll)edge_son[tmp.second]*(w[tmp.second]-w[tmp.second]/2), tmp.second));  // 将处理后的边再次放入优先队列
    }
    while(!cost2_edge.empty()) {  // 同上
        tmp = cost2_edge.top();
        cost2_edge.pop();
        if(tmp.first == 0)
            continue;
        w[tmp.second] /= 2;
        cost2_range.emplace_back(tmp);
        cost2_edge.push(make_pair((ll)edge_son[tmp.second]*(w[tmp.second]-w[tmp.second]/2), tmp.second));
    }
}

inline void update_ans() {  // 如果满足条件，更新答案
    if(sum <= S)
        ans = min(ans, cost);
}

inline void two_points() {
    ll l = 0, r = 0, tmp = sum;
    // 尝试全选花费为 1
    while(sum > S && l < cost1_range.size()) {
        sum -= cost1_range[l].first;
        l++, cost++;
    }
    l--;
    update_ans();
    // 逐个减少贡献小的花费为 1 的操作，随之增加贡献大的花费为 2 的操作
    while(l != -1) {
        while(sum > S && r < cost2_range.size()) {
            sum -= cost2_range[r].first;
            cost += 2, r++;
        }
        update_ans();
        sum += cost1_range[l].first;
        cost--, l--;
    }
    // 尝试全选花费为 2
    sum = tmp, r = cost = 0;
    while(sum > S && r < cost2_range.size()) {
        sum -= cost2_range[r].first;
        r++, cost += 2;
    }
    update_ans();
    printf("%lld\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        init();
        input();
        dfs(1, 0);
        build_range();
        two_points();
    }
    return 0;
}

```

AC记录：https://codeforces.com/contest/1399/submission/276403804

---

## 作者：pocafup (赞：1)

注意一下当除法为向下取整，每条边最多被除 logw 次就会变成 0。

然后还有一个性质：当一条边权值被除了 2，这条边下面的所有叶节点的贡献都会减少相应的数量。

可以用一个 dfs 求出每条边被多少个叶节点走过，这个不讲。

然后注意到费用为 1，2，我们可以开两个优先队列。如果只用费用 1就能解决，那么我们肯定选择用费用 1 的。否则，我们分类讨论：

- 当用前两大的费用 1 的边的贡献大于用费用 2 的边的贡献，我们选择 **一条费用为 1** 的边累计贡献。
- 否则使用费用 2 的边累计贡献。

**注意排序不能直接用 $siz \times val$ 进行排序，只能以消除一次的贡献进行排序**
```cpp
struct Node{
  int siz, val;
  bool operator < (const Node &oth) const{
    return ceil(val/2.0)*siz<ceil(oth.val/2.0)*oth.siz;
  }
};
inline void init(){
  tot = cnt = ans = 0;
  memset(head,0,sizeof(head));
  memset(sz,0,sizeof(sz));
}
inline int dfs(int u, int fa){
  int cnt = 0; dep[u] = dep[fa]+1;
  for(int i=head[u];i;i=edge[i].nxt){
    int v = edge[i].v;
    if (v==fa) continue;
    cnt++;
    sz[u] += dfs(v,u);
  }
  if (!cnt) sz[u] = 1;
  return sz[u];
}
Node qt1,qt2,qs1,premin;
inline void solve(){
  n=read(), m = read();
  init();
  pq<Node> q1,q2;
  For(i,1,n-1) a = read(), b = read(), c = read(), d = read(), add(a,b,c,d), add(b,a,c,d);
  dfs(1,1);
  For(i,1,tot){
    int u = edge[i].u, v = edge[i].v, d = edge[i].d, c = edge[i].cn;
    if (dep[u]>dep[v]) continue;
    ans += sz[v]*d;
    if (c==1) q1.push((Node){sz[v],d});
    else q2.push((Node){sz[v],d});
  }
  while(ans>m){
    if (q1.size() && ans-q1.top().siz*ceil(q1.top().val/2.0) <= m) {cnt++; break;}
    qt1 = qt2 = qs1 = (Node){0,0};
    if (q1.size()) qt1 = q1.top(), q1.pop();
    if (q1.size()) qt2 = q1.top();
    if (q2.size()) qs1 = q2.top();
    if (qt1.val/2*qt1.siz>=qt2.val*qt2.siz){
      if (qt1.siz*ceil(qt1.val/2.0) + qt1.siz*ceil((qt1.val/2)/2.0)<=qs1.siz*ceil(qs1.val/2.0)){
        ans -= qs1.siz*ceil(qs1.val/2.0);
        q1.push(qt1);
        q2.pop();

        if (qs1.val/2!=0) q2.push((Node){qs1.siz,qs1.val/2});
        cnt+=2;
      }else{
        ans -= qt1.siz*ceil(qt1.val/2.0);
        if (qt1.val/2!=0)q1.push((Node){qt1.siz,qt1.val/2});
        cnt++;
      }
    }else{
      if (qt1.siz*ceil(qt1.val/2.0)+qt2.siz*ceil(qt2.val/2.0)<=qs1.siz*ceil(qs1.val/2.0)){
        ans -= qs1.siz*ceil(qs1.val/2.0);
        q1.push(qt1);
        q2.pop();
        if (qs1.val/2!=0)q2.push((Node){qs1.siz,qs1.val/2});
        cnt+=2;
      }else{
        ans -= qt1.siz*ceil(qt1.val/2.0);
        if (qt1.val/2!=0)q1.push((Node){qt1.siz,qt1.val/2});
        cnt++;
      }
    }
  }
  writeln(cnt);
}
```

---

## 作者：vanueber (赞：0)

[EASY_VER](https://codeforces.com/contest/1399/problem/E1)

[HARD_VER](https://codeforces.com/contest/1399/problem/E2)

# 题目大意

给定一棵树，可以使一些边的权值减半向下取整，使得最终根到所有叶子的路径的权值和 $\le S$。

在普通版中，减少权值的代价都为 $1$；加强版中，一些边的代价为 $1$，一些边的代价为 $2$，同时要满足代价最小。

# 题目分析

先看普通版怎么做。

首先统计从根到所有叶子节点的路径上一些边被经过了多少次，这是一个经典的树上差分问题，将点权赋回边上即可。

然后考虑如何选择边减半，很明显的贪心是每次都选择减少的值更多的边，这显然是一个多路归并优先队列的问题，因为对于每一条边，它的经过次数 $cnt$ 是一个定值，由于 $w+\lfloor \frac{w}{2} \rfloor > \lfloor \frac{w}{2} \rfloor + \lfloor \frac{w}{4} \rfloor$ 说明决策具有单调性，用优先队列维护最优决策即可。

然后考虑加强版。

由于边被分成了 $c=1$ 与 $c=2$ 的不好一起处理，可以先预处理出相关信息然后合并答案。

由于关于边的选择使完全独立的问题，减少一条边的权值带来的影响不会干扰其他边，故预处理出 $cost1_k$ 表示使用第 $k$ 大且代价为 $1$ 的边减少的值，$cost2_k$ 表示使用第 $k$ 大且代价为 $1$ 的边减少的值，这样就可以枚举减少代价为 $1$ 的边的数量，二分或双指针求得使用的代价 $2$ 的边的数量，最后更新答案。

预处理同样是可以用多路归并优先队列维护的，注意细节：由于可能没有代价为 $1$ 或代价为 $2$ 的边，需要令 $cost1_0=0,cost2_0=0$ 枚举是从 $0$ 开始。

# Code_Ez


```cpp
#include <bits/stdc++.h>
#define int long long
#define umap unordered_map
#define vint vector<int>
#define ll long long
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define uint unsigned int
#define rg register
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define sqr(x) ((x)*(x))
using namespace std;
const int INF=0x3f3f3f3f;
inline int read()
{
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        w=(w<<1)+(w<<3)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

const int N=1e6+10,M=1e6+10;
int T,n,S,now_w;
struct edge
{
    int u,v,w,c,nxt;
    edge(int u=0,int v=0,int w=0,int c=0,int nxt=0):u(u),v(v),w(w),c(c),nxt(nxt){}
}e[M<<1];
int cnt[M<<1];
int idx,head[N];
void add(int u,int v,int w,int c)
{
    e[++idx]=edge(u,v,w,c,head[u]);
    head[u]=idx;
}
vint c1,c2;
int cost1[M<<2],cost2[M<<1],pre[M<<1];//操作k条c=1/c=2的边得到的最大的delta
int cnt1,cnt2;
bool vis1[M<<1],vis2[M<<1];
pii prevv[N];
int cf[N];
void dfs(int u,int fa)
{
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].v,c=e[i].c;
        if(v==fa) continue;
        dfs(v,u);
        if(c==1) c1.push_back(i);
        else c2.push_back(i);
        prevv[v]=make_pair(u,i);
    }
}
void dfs2(int u,int fa)
{
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==fa) continue;
        dfs2(v,u);
        cnt[prevv[v].second]=cf[v];
        cf[u]+=cf[v];
    }
}
struct state
{
    int w,id,delta;
    bool operator <(const state &b)const
    {
        return delta<b.delta;
    }
};
priority_queue<state> Q1,Q2;
void init()
{
    rep(i,1,idx) e[i]=edge(),cnt[i]=0,vis1[i]=0,vis2[i]=0;
    rep(i,1,n) head[i]=0,prevv[i]=make_pair(0,0),cf[i]=0;
    idx=0;
    now_w=0;
    c1.clear(),c2.clear();
    while(!Q1.empty()) Q1.pop();
    while(!Q2.empty()) Q2.pop();
    rep(i,0,cnt1) cost1[i]=0;
    rep(i,0,cnt2) cost2[i]=0,pre[i]=0;
    cnt1=cnt2=0; 
}

signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    T=read();
    while(T--)
    {
        n=read(),S=read();
        init();
        for(int i=1,u,v,w,c;i<n;++i)
        {
            u=read(),v=read(),w=read(),c=1;
            add(u,v,w,c),add(v,u,w,c);
        }
        dfs(1,0);
        rep(i,1,n) if(!e[head[i]].nxt) cf[i]=1;
        dfs2(1,0);
        rep(i,1,idx) now_w+=cnt[i]*e[i].w;
        if(now_w<=S)
        {
            puts("0");continue;
        }
        else
        {
            for(auto i:c1)
            {
                Q1.push({e[i].w/2,i,cnt[i]*(e[i].w-(e[i].w/2))});
            }
            for(auto i:c2)
            {
                Q2.push({e[i].w/2,i,cnt[i]*(e[i].w-(e[i].w/2))});
            }
            int pre_1=0,pre_2=0,res=LONG_LONG_MAX;
            int needs=now_w-S;
            while(!Q1.empty())
            {
                auto [w,id,delta]=Q1.top();
                Q1.pop();
                if(delta<=0) break;
                cost1[++cnt1]=delta;
                pre_1+=delta;
                if(pre_1>=needs) break;
                Q1.push({w/2,id,cnt[id]*(w-w/2)});
            }
            while(!Q2.empty())
            {
                auto [w,id,delta]=Q2.top();
                Q2.pop();
                if(delta<=0) break;
                cost2[++cnt2]=delta;
                pre_2+=delta;
                if(pre_2>=needs) break;
                Q2.push({w/2,id,cnt[id]*(w-w/2)});
            }
            pre_1=0;
            
            rep(i,1,cnt2) pre[i]=pre[i-1]+cost2[i];
            cost1[0]=0;
            pre[0]=0;
            for(int i=0;i<=cnt1;++i)
            {
                pre_1+=cost1[i];
                int need=needs-pre_1;//找到第一个>=
                int pos=lower_bound(pre,pre+cnt2+1,need)-pre;
                if(pos==cnt2+1)
                {
                    continue;
                }
                res=min(i+2*pos,res);
            }
            write(res);
            puts("");
        }
    }
    #ifndef ONLINE_JUDGE
    fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
    #endif
    return 0;
}
```


# Code_Hd


```cpp
#include <bits/stdc++.h>
#define int long long
#define umap unordered_map
#define vint vector<int>
#define ll long long
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define uint unsigned int
#define rg register
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define sqr(x) ((x)*(x))
using namespace std;
const int INF=0x3f3f3f3f;
inline int read()
{
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        w=(w<<1)+(w<<3)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

const int N=1e6+10,M=1e6+10;
int T,n,S,now_w;
struct edge
{
    int u,v,w,c,nxt;
    edge(int u=0,int v=0,int w=0,int c=0,int nxt=0):u(u),v(v),w(w),c(c),nxt(nxt){}
}e[M<<1];
int cnt[M<<1];
int idx,head[N];
void add(int u,int v,int w,int c)
{
    e[++idx]=edge(u,v,w,c,head[u]);
    head[u]=idx;
}
vint c1,c2;
int cost1[M<<2],cost2[M<<1],pre[M<<1];//操作k条c=1/c=2的边得到的最大的delta
int cnt1,cnt2;
bool vis1[M<<1],vis2[M<<1];
pii prevv[N];
int cf[N];
void dfs(int u,int fa)
{
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].v,c=e[i].c;
        if(v==fa) continue;
        dfs(v,u);
        if(c==1) c1.push_back(i);
        else c2.push_back(i);
        prevv[v]=make_pair(u,i);
    }
}
void dfs2(int u,int fa)
{
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==fa) continue;
        dfs2(v,u);
        cnt[prevv[v].second]=cf[v];
        cf[u]+=cf[v];
    }
}
struct state
{
    int w,id,delta;
    bool operator <(const state &b)const
    {
        return delta<b.delta;
    }
};
priority_queue<state> Q1,Q2;
void init()
{
    rep(i,1,idx) e[i]=edge(),cnt[i]=0,vis1[i]=0,vis2[i]=0;
    rep(i,1,n) head[i]=0,prevv[i]=make_pair(0,0),cf[i]=0;
    idx=0;
    now_w=0;
    c1.clear(),c2.clear();
    while(!Q1.empty()) Q1.pop();
    while(!Q2.empty()) Q2.pop();
    rep(i,0,cnt1) cost1[i]=0;
    rep(i,0,cnt2) cost2[i]=0,pre[i]=0;
    cnt1=cnt2=0; 
}

signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    T=read();
    while(T--)
    {
        n=read(),S=read();
        init();
        for(int i=1,u,v,w,c;i<n;++i)
        {
            u=read(),v=read(),w=read(),c=read();
            add(u,v,w,c),add(v,u,w,c);
        }
        dfs(1,0);
        rep(i,1,n) if(!e[head[i]].nxt) cf[i]=1;
        dfs2(1,0);
        rep(i,1,idx) now_w+=cnt[i]*e[i].w;
        // rep(i,1,n) cout<<cf[i]<<" ";
        // cout<<endl;
        // cout<<c1.size()<<" "<<c2.size()<<endl;
        // cout<<now_w<<endl;
        if(now_w<=S)
        {
            puts("0");continue;
        }
        else
        {
            for(auto i:c1)
            {
                Q1.push({e[i].w/2,i,cnt[i]*(e[i].w-(e[i].w/2))});
            }
            for(auto i:c2)
            {
                Q2.push({e[i].w/2,i,cnt[i]*(e[i].w-(e[i].w/2))});
            }
            int pre_1=0,pre_2=0,res=LONG_LONG_MAX;
            int needs=now_w-S;
            while(!Q1.empty())
            {
                auto [w,id,delta]=Q1.top();
                Q1.pop();
                if(delta<=0) break;
                cost1[++cnt1]=delta;
                pre_1+=delta;
                if(pre_1>=needs) break;
                Q1.push({w/2,id,cnt[id]*(w-w/2)});
            }
            while(!Q2.empty())
            {
                auto [w,id,delta]=Q2.top();
                Q2.pop();
                if(delta<=0) break;
                cost2[++cnt2]=delta;
                pre_2+=delta;
                if(pre_2>=needs) break;
                Q2.push({w/2,id,cnt[id]*(w-w/2)});
            }
            pre_1=0;
            
            rep(i,1,cnt2) pre[i]=pre[i-1]+cost2[i];
            cost1[0]=0;
            pre[0]=0;
            for(int i=0;i<=cnt1;++i)
            {
                pre_1+=cost1[i];
                // cout<<pre_1<<endl;
                int need=needs-pre_1;//找到第一个>=
                int pos=lower_bound(pre,pre+cnt2+1,need)-pre;
                if(pos==cnt2+1)
                {
                    continue;
                }
                res=min(i+2*pos,res);
            }
            write(res);
            puts("");
            // cout<<res<<endl;
        }
    }
    #ifndef ONLINE_JUDGE
    fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
    #endif
    return 0;
}
/*
4
4 18
2 1 9 2
3 2 4 1
4 1 1 2
3 20
2 1 8 1
3 1 7 2
5 50
1 3 100 1
1 5 10 2
2 3 123 2
5 4 55 1
2 100
1 2 409 2
*/
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 分析

把每条边的 $val$，$w$，$sum$ 求出来放进优先队列，$c=1$ 的维护一个，$c=2$ 的维护一个，$val$ 为这条边操作一次能减少多少值，$sum$ 为这条边经过的叶子数量，$w$ 为当前边权。

那么我们肯定取大的好，$d1=q_1$ 的栈顶元素，$q_1$ 将栈顶元素弹出，$d12$ 为了消除了 $d1$ 后，$c1=1$ 中能拿出的最大的，所以要把剩下的 $q_1$ 的栈顶元素和再次操作 $d1$ 比较一下取较大，$d2=q_2$ 的栈顶元素。 

然后如果 $d1$ 操作一次直接 $\le S$ 了，那么直接 gogogo，否则比较一下 $d1+d12<d2$，那么说明 $d2$ 消 $1$ 次比 $d1$ 和 $d12$ 消两次还多，那么就消 $d2$，否则消 $d1$。

## 代码启动

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int maxl=3e5+10;
ll n,m,cas,k,cnt,ans;
ll s,tot;
ll son[maxl];
struct ed{ll to,w,c;};
vector<ed> e[maxl];
bool in[maxl]; 
struct edg{
	ll val;ll w,sum;
	bool operator < (const edg &b)const{
		return val<b.val;
	}
};
priority_queue<edg> q[3];
inline void dfs(int u,int fa){
	int v;son[u]=0;bool flag=false;
	for(ed ee:e[u]){
		v=ee.to;
		if(v==fa) continue;
		dfs(v,u);flag=true;
		son[u]+=son[v];
		q[ee.c].push(edg{1ll*(ee.w-(ee.w/2))*son[v],ee.w,son[v]});
		tot+=1ll*ee.w*son[v];
	}
	if(!flag) son[u]=1;
}
inline void prework(){
	scanf("%lld%lld",&n,&s);
	for(int i=1;i<=n;i++)
		e[i].clear();
	ll u,v,w,c;
	for(int i=1;i<=n-1;i++){
		scanf("%lld%lld%lld%lld",&u,&v,&w,&c);
		e[u].push_back(ed{v,w,c});
		e[v].push_back(ed{u,w,c});
	}
	while(!q[1].empty()) q[1].pop();
	while(!q[2].empty()) q[2].pop();
	tot=0;dfs(1,0);
} 
 
inline void mainwork(){
	edg d11,d12,nd1,d2,nd2;ans=0;
	while(tot>s){
		d11.sum=0;d12.sum=0;d2.sum=0;
		if(!q[1].empty()){
			d11=q[1].top();q[1].pop();
			d12.val=0;
			if(!q[1].empty())
				d12=q[1].top();
			nd1.w=d11.w/2;nd1.sum=d11.sum;
			nd1.val=1ll*(nd1.w-(nd1.w/2))*d11.sum;
			if(nd1.val>d12.val)
				d12=nd1;
		}
		if(!q[2].empty()){
			d2=q[2].top(),q[2].pop();
			nd2.w=d2.w/2;nd2.sum=d2.sum;
			nd2.val=1ll*(nd2.w-(nd2.w/2))*d2.sum;
		}
		if(tot-d11.val<=s && d11.sum>0){
			++ans;
			return;
		}
		if(d11.sum!=0 && d2.sum!=0){
			if(d11.val+d12.val>=d2.val){
				ans++;tot-=d11.val;
				q[1].push(nd1);
				q[2].push(d2);
			}
			else{
				ans+=2;tot-=d2.val;
				q[1].push(d11);
				q[2].push(nd2);
			}
		}
		else if(d11.sum!=0 && d2.sum==0){
			ans++;tot-=d11.val;
			q[1].push(nd1);
		}
		else {
			ans+=2;tot-=d2.val;
			q[2].push(nd2);
		}
	}
}
inline void print(){
	printf("%lld\n",ans);
}
int main(){
	int t=1;
	scanf("%d",&t);
	for(cas=1;cas<=t;cas++){
		prework();
		mainwork();
		print();
	}
	return 0;
}
```

---

## 作者：zsyyyy (赞：0)

## CF1399E2 2200

### 题目描述

给出一个结点数量为 $n$ 的边带权的有根树，树的根结点为 $1$。你可以进行以下操作。

* 选定任意一条权值为 $w_i$ 的边，使 $w_i \gets \lfloor \frac{w_i}{2} \rfloor$，花费为 $c_i$ 且 $c_i \in \{1, 2\}$。

定义 $w(i,j)$ 为结点 $i$ 到结点 $j$ 的路径边权和。对于每组测试数据，你需要回答最小的花费，使得 $\sum\limits_{v\in leaves}w(root,v)\leq S$，其中 $leaves$ 为叶子结点编号的集合。



### 思路

可以统计出每一条边被经过的次数，对于一条被经过了 $cnt$ 次、权值为 $w$ 的边来说，操作一次相当于使总边权和减少了 $(w-\lfloor w/2 \rfloor) * cnt$，可以用 pq 维护对每一条操作的价值，完成一次操作后更新 $w$ 值。但是，并不能直接选择能使总边权减少更多的边进行操作，因为不同的边的操作代价也不同。所以，统计出对代价为 $1$ 的边操作了 $i$ 次后和对代价为 $2$ 的边操作了 $i$ 次后分别的最小边权和，然后用双指针统计最小代价即可。


### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e6+10;
int T,n,S,u[MAXN],v[MAXN],w[MAXN],c[MAXN],cnt[MAXN];
int fa[MAXN],ans,alls,tmpw,ts[3][MAXN],l,r,maxx[MAXN];
struct node1
{
	int v,w,c;
};
struct node2
{
	int v,w,cnt;
	bool operator <(const node2 &xx)const
	{
		return xx.v>v;
	}
}tmp,tmpp;
vector<node1> a[MAXN];
priority_queue<node2> pq[3];
void dfs(int x,int f)
{
	if(a[x].size()==1&&a[x][0].v==f)  cnt[x]=1;
	for(int i=0;i<a[x].size();i++)
	{
		if(a[x][i].v!=f)
		{
			fa[a[x][i].v]=x;
			dfs(a[x][i].v,x);
			cnt[x]+=cnt[a[x][i].v];
		}
	}
}
int solve(int ty)
{
	int cntt=0;
	while(pq[ty].size()&&pq[ty].top().v!=0)
	{
		tmp=pq[ty].top();
		pq[ty].pop();
		cntt++;
		if(cntt!=0)  ts[ty][cntt]=ts[ty][cntt-1]+tmp.v;
		maxx[ty]=cntt;
		tmpw=tmp.w/2;
		pq[ty].push((node2){(tmpw-tmpw/2)*tmp.cnt,tmpw,tmp.cnt});
	}
}
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		alls=0;
		scanf("%lld%lld",&n,&S);
		for(int i=1;i<=n-1;i++)
		{
			scanf("%lld%lld%lld%lld",&u[i],&v[i],&w[i],&c[i]);
			a[u[i]].push_back((node1){v[i],w[i],c[i]});
			a[v[i]].push_back((node1){u[i],w[i],c[i]});
		}
		dfs(1,0);
		while(pq[1].size())  pq[1].pop();
		while(pq[2].size())  pq[2].pop();
		for(int i=1;i<=n-1;i++)
		{
			if(fa[u[i]]==v[i])  swap(u[i],v[i]);
			alls+=cnt[v[i]]*w[i];
			pq[c[i]].push((node2){(w[i]-w[i]/2)*cnt[v[i]],w[i],cnt[v[i]]});
		}
		if(alls<=S)
		{
			for(int i=0;i<=n;i++)
			{
				maxx[1]=maxx[2]=fa[i]=ts[1][i]=ts[2][i]=cnt[i]=0;
				a[i].clear();
			}
			puts("0");
			continue;
		}
		solve(1);
		solve(2);
		ans=LONG_LONG_MAX;
		r=0;
		for(int l=maxx[1];l>=0;l--)
		{
			while(alls-ts[1][l]-ts[2][r]<S&&r>0)  r--;
			while(alls-ts[1][l]-ts[2][r]>S&&r<maxx[2])  r++;
			if(alls-ts[1][l]-ts[2][r]<=S)  ans=min(ans,l+2*r);
		}
		printf("%lld\n",ans);
		for(int i=0;i<=n;i++)
		{
			maxx[1]=maxx[2]=fa[i]=ts[1][i]=ts[2][i]=cnt[i]=0;
			a[i].clear();
		}
	}
	return 0;
}
```



---

