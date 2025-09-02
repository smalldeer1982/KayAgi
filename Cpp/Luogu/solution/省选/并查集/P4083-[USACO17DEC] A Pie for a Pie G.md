# [USACO17DEC] A Pie for a Pie G

## 题目描述

Bessie 和 Elsie 各自烤了 $N$ 个派（$1 \leq N \leq 10^5$）。这 $2N$ 个派中的每一个都有一个由 Bessie 评定的美味值和一个（可能不同的）由 Elsie 评定的美味值。

Bessie 正在考虑将她的一只派送给 Elsie。如果 Elsie 收到了 Bessie 的派，她会觉得有义务回赠 Bessie 一只派。为了既不显得吝啬也不显得炫耀，Elsie 会尝试选择一只在她看来至少与收到的派一样美味，但不超过 $D$ 单位更美味的派（$0 \leq D \leq 10^9$）。如果这样的派不存在，Elsie 将采用一个化名并自我流放到日本。

但如果 Elsie 确实回赠了 Bessie 一只派，Bessie 也会类似地尝试送给 Elsie 一只在她看来至少与 Elsie 刚送给她的派一样美味，但不超过 $D$ 单位更美味的派。如果这不可能，Bessie 也会自我流放。否则，她会将她选择的派送给 Elsie。这个循环将继续，直到其中一头奶牛被流放（一个不愉快的结果），或者其中一头奶牛收到一只她评定美味值为 $0$ 的派，在这种情况下，礼物交换将结束，两头奶牛都会感到高兴。

请注意，一只派不能被赠送两次，任何一头奶牛也不能回赠她收到的派。

对于 Bessie 可以选择作为初始礼物送给 Elsie 的每一只派，确定在奶牛们感到高兴之前，可能被赠送的派的最小数量。

## 样例 #1

### 输入

```
2 1
1 1
5 0
4 2
1 4```

### 输出

```
3
1
```

# 题解

## 作者：cccgift (赞：11)

### 看到其它题解都不太完善，都可以被卡成$O(n^2)$，这里给出严格的$O(nlogn)$算法。

首先，我们把$Bessie$做的馅饼按照$Elsie$的看法排序（因为$Bessie$要送什么馅饼取决于$Elsie$对蛋糕的评价），$Elsie$的馅饼同理。

接下来要用到一个非常重要的思想：倒序处理！我们把原题转化成从每一个价值为$0$的馅饼（在另一个人的看法之下）设为起点，送馅饼表示从一个馅饼转化到另一个馅饼。

于是我们发现，只要把每个馅饼向接下来可以送的馅饼（注意！由于我们是反向考虑，于是可送价值区间为$[x-d,x]$，其中$x$表示当前馅饼在别人看来的价值）连边，就转化成了一个最短路问题！

那么本题就做完了……吗？

我们发现，一个点（馅饼）可能会向很多点连边，最多$n$个，这导致空间复杂度可能会达到$O(n^2)$，时间复杂度同样。

但是，我们又可以发现，我们已经把馅饼排序，而可送价值也是一个区间，所以连边肯定是一个区间，那么我们可以通过二分查找，找到区间左端点和右端点。

然后，我们发现单点向区间连边很熟悉，这不就是线段树优化建图弱化版吗？

这里再讲一下具体过程：首先建一棵$2*n$的线段树，对于每一个线段树上的结点，向它的两个子结点连两条$0$边。接下来，倘若有结点$x$向区间$[l,r]$连边，就把$[x,x]$这个结点，向线段树的修改操作那样，连边即可。（具体细节参见代码）。这种算法即使是对于那些没有学真正的线段树优化建图（区间连区间）的同学（比如我）也很好理解。

还有一个细节，我们发现按照上述情况，边权只有$0$和$1$，于是，跑最短路时，我们就不必用优先队列，用双端队列即可。

P.S. 最后我看了一下最优解，发现有一个并查集优化，而且除去排序时间复杂度可以达到$O(n)$，但是我无法证明它的正确性，所以这里就不给出了，有兴趣可以去看看。

#### 以下是代码：

```cpp
#include<cstdio>
#include<cctype>
#include<utility>
#include<cstring>
#include<deque>
#include<algorithm>
using namespace std;
#define res register int
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++) //fread优化
char buf[1<<21],*p1=buf,*p2=buf;
template<typename T>
inline void read(T &x) //快读
{
    static char ch;bool f=1;
    for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
    for(;isdigit(ch);x=(x<<1)+(x<<3)+ch-48,ch=getchar());x=f?x:-x;
}
template<typename T> //快输
inline void print(T x,char ch) {
	if(!x) {putchar(48);if(ch) putchar(ch);return;}
	if(x<0) putchar('-'),x=-x;
	static int Stack[sizeof(T)*3],top=-1;
	for(;x;Stack[++top]=x%10,x/=10);
	for(;~top;putchar(Stack[top--]+48));
	if(ch) putchar(ch);
}
template<typename T>
inline T max(T x,T y) {return x>y?x:y;}
template<typename T>
inline T min(T x,T y) {return x<y?x:y;}
template<typename T>
inline void chkmax(T &x,T y) {x=x>y?x:y;}
template<typename T>
inline void chkmin(T &x,T y) {x=x<y?x:y;}
struct node{
	int x,y,id;
} a[200001];
int b[200001],ver[1600001],nxt[1600001],head[1600001],edge[1600001],ans,n,m,d[800001],tot[100001];
inline void add(int x,int y,int z) {ver[++ans]=y,edge[ans]=z,nxt[ans]=head[x],head[x]=ans;}
inline bool cmp1(node x,node y) {return x.x<y.x;}
inline bool cmp2(node x,node y) {return x.y<y.y;}
void build(int q,int l,int r) {
	if(l==r) {b[l]=q;return;}
	int mid=l+r>>1;
	build(q<<1,l,mid),build(q<<1|1,mid+1,r),add(q,q<<1,0),add(q,q<<1|1,0); //向儿子结点连边
} 
void change(int q,int l1,int r1,int l,int r,int k) { //单点向区间连边
	if(r<l1||r1<l) return;
	if(l<=l1&&r1<=r) {add(k,q,1);return;}
	int mid=l1+r1>>1;
	change(q<<1,l1,mid,l,r,k),change(q<<1|1,mid+1,r1,l,r,k);
}
inline int erfen1(int x) {
	int l=n+1,r=n<<1,tot;
	if(a[r].x<x) return -1;
	while(l<=r) {
		int mid=l+r>>1;
		if(a[mid].x>=x) tot=mid,r=mid-1;else l=mid+1;
	}
	return tot;
}
inline int erfen2(int x) {
	int l=n+1,r=n<<1,tot;
	if(a[l].x>x) return -1;
	while(l<=r) {
		int mid=l+r>>1;
		if(a[mid].x<=x) tot=mid,l=mid+1;else r=mid-1;
	}
	return tot;
}
inline int erfen3(int x) {
	int l=1,r=n,tot;
	if(a[r].y<x) return -1;
	while(l<=r) {
		int mid=l+r>>1;
		if(a[mid].y>=x) tot=mid,r=mid-1;else l=mid+1;
	}
	return tot;
}
inline int erfen4(int x) {
	int l=1,r=n,tot;
	if(a[l].y>x) return -1;
	while(l<=r) {
		int mid=l+r>>1;
		if(a[mid].y<=x) tot=mid,l=mid+1;else r=mid-1;
	}
	return tot;
} //四个二分都得注意范围，不要搞错了。
deque<int> q;
inline void dijkstra() { //双端队列优化dijkstra
	for(res i=1;i<=n&&!a[i].y;++i) q.push_back(b[i]),d[b[i]]=1;
	for(res i=n+1;i<=n<<1&&!a[i].x;++i) q.push_back(b[i]),d[b[i]]=1; //这里要特别注意！起点必须是在别人看来价值为0的馅饼。
	while(!q.empty()) {
		int x=q.front();q.pop_front();
		for(res i=head[x];i;i=nxt[i])
		  if(d[ver[i]]>d[x]+edge[i]) d[ver[i]]=d[x]+edge[i],edge[i]?q.push_back(ver[i]):q.push_front(ver[i]);
	}
	for(res i=1;i<=n;++i) tot[a[i].id]=d[b[i]];
}
int main()
{
    read(n),read(m);
    for(res i=1;i<=n<<1;++i) read(a[i].x),read(a[i].y),a[i].id=i;
    sort(a+1,a+1+n,cmp2),sort(a+1+n,a+1+(n<<1),cmp1),build(1,1,n<<1),memset(d,0x3f,sizeof(d));
    for(res i=1;i<=n;++i) {
    	int L=erfen1(a[i].x-m),R=erfen2(a[i].x);
    	if(L<0||R<0) continue;
    	change(1,1,n<<1,L,R,b[i]);
	}
	for(res i=n+1;i<=n<<1;++i) {
		int L=erfen3(a[i].y-m),R=erfen4(a[i].y);
		if(L<0||R<0) continue;
		change(1,1,n<<1,L,R,b[i]);
	}
	dijkstra();
	for(res i=1;i<=n;++i) if(tot[i]>1e9) puts("-1");else printf("%d\n",tot[i]);
    return 0;
}
```

---

## 作者：bessie_goes_moo (赞：4)

1.填楼上巨佬的坑，这是并查集写法

2.具体和不同代码里有（~~你们看不出来这是水贴的吧~~）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=200005;
int N,D,INF,fa[M],dis[M],Q[M],ans[M];
struct node{
    int A,B,id;
}a[M];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-')f=-f;ch=getchar();}
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
bool cmp1(const node &a, const node &b){return a.B<b.B;}
bool cmp2(const node &a, const node &b){return a.A<b.A;}
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
int bin1(int L,int R,int x){
    if (a[R].A<x) return -1;
    while (L<=R){
        int mid=(R-L>>1)+L;
        if (a[mid].A<x) L=mid+1;else R=mid-1;
    }
    return L;
}
int bin2(int L,int R,int x){
    if (a[L].A>x) return -1;
    while (L<=R){
        int mid=(R-L>>1)+L;
        if (a[mid].A>x) R=mid-1;else L=mid+1;
    }
    return R;
}
int bin3(int L,int R,int x){
    if (a[R].B<x) return -1;
    while (L<=R){
        int mid=(R-L>>1)+L;
        if (a[mid].B<x) L=mid+1;else R=mid-1;
    }
    return L;
}
int bin4(int L,int R,int x){
    if (a[L].B>x) return -1;
    while (L<=R){
        int mid=(R-L>>1)+L;
        if (a[mid].B>x) R=mid-1;else L=mid+1;
    }
    return R;
}
void BFS(){//倒刷最短路，借助于并查集进行合并，否则单推太慢 
	sort(a+1,a+1+N,cmp1),sort(a+1+N,a+1+2*N,cmp2);
	memset(dis,63,sizeof dis);INF=dis[0];
	int hed=0,til=0;
    for (int i=1;i<=N&&!a[i].B;i++) Q[++til]=i,dis[i]=1;
    for (int i=N+1;i<=2*N&&!a[i].A;i++) Q[++til]=i,dis[i]=1;
    while (hed!=til){
        int u=Q[++hed],L,R;
        if (u<=N){//实质是Elsie收到了Bessie送来的一个饼u，那么前一步就是Elsie的饼中(Bessie看)在[a[u].A-D,a[u].A]寻找一个合适的饼 
            L=bin1(N+1,2*N,a[u].A-D);
            R=bin2(N+1,2*N,a[u].A);
        }
        else{//到Beesie的饼中(Elsie看)在[a[u].B-D,a[u].B]寻找一个合适的饼 
            L=bin3(1,N,a[u].B-D);
            R=bin4(1,N,a[u].B);
        }
        if (L==-1 || R==-1) continue;
        for (int i=L,father;i<=R;i=father+1){
            fa[father=get(i)]=get(R);
            if (dis[u]+1<dis[i]) dis[i]=dis[u]+1,Q[++til]=i;
        }
    }
    for (int i=1;i<=N;i++) ans[a[i].id]=dis[i];
}
int main(){
    N=read(),D=read();
    for (int i=1;i<=2*N;i++) a[i].A=read(),a[i].B=read(),a[i].id=i,fa[i]=i;
    BFS();
    for (int i=1;i<=N;i++)
      if (ans[i]<INF) printf("%d\n",ans[i]);else printf("-1\n");
    return 0;
}
```


---

## 作者：白鲟 (赞：3)

## 前言
纪念我逝去的 80 pts。

## 题目分析
容易想到转化问题为最短路，将一个礼物向它可以回应的礼物连边权为 $1$ 的边，以赠送后可直接形成 Happy End 的礼物作为源点 bfs 即可。可以发现每一个点的出边连向的是一个连续的区间，其左右端点可通过二分查找得到。

通常可以使用线段树优化建图解决。但此题由于边权为 $1$，每个点事实上只会被 bfs 时搜索到它的首条入边松弛。这意味着可以不显式添加边，而是使用 `multiset` 维护还没有访问过的点集，每次用 bfs 队首松弛并删去点集中可达的点即可。

每个点只会在 `multiset` 被松弛一次。容易得知时间复杂度为 $\operatorname{O}(n\log n)$。

## 代码
考场忘了判断 Bad End……

```cpp
#include<cctype>
#include<cstdio>
#include<cstring>
#include<queue>
#include<set> 
using namespace std;
const int maxn=1e5;
int n,d,score[maxn<<1|1][2],f[maxn<<1|1];
queue<int> que;
multiset<pair<int,int> > rest[2];
void read(int &x)
{
	x=0;
	char t=getchar();
	while(!isdigit(t))
		t=getchar();
	while(isdigit(t))
	{
		x=x*10+t-'0';
		t=getchar();
	}
	return;
}
int main()
{
	memset(f,0x3f,sizeof f);
	read(n);
    read(d);
	for(int i=1;i<=(n<<1);++i)
    {
        read(score[i][0]);
        read(score[i][1]);
    }
	for(int i=1;i<=(n<<1);++i)
		if(!score[i][i<=n])
		{
			f[i]=1;
			que.push(i);
		}
		else rest[i>n].insert(make_pair(score[i][i<=n],i));
	while(!que.empty())
	{
		int front=que.front();
		que.pop();
		int opt=(front>n);
		multiset<pair<int,int> >::iterator iter1=rest[opt^1].lower_bound(make_pair(score[front][opt]-d,-0x3f3f3f3f)),
										   iter2=rest[opt^1].upper_bound(make_pair(score[front][opt],0x3f3f3f3f));
		if(iter1==rest[opt^1].end())
			continue;
		for(multiset<pair<int,int> >::iterator iter=iter1;iter!=iter2;)
		{
			f[iter->second]=f[front]+1;
			que.push(iter->second);
			rest[opt^1].erase(iter++);
		}
	}
	for(int i=1;i<=n;++i)
		printf("%d\n",f[i]>=0x3f3f3f3f?-1:f[i]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：物灵 (赞：2)

## 只用 STL 做到 $\mathrm O(n\log n)$

建图方式可以参考其他题解。由于每张饼只能用一次（BFS 中第一次遍历到一张饼时深度最小，在本题中即为最优），我们将所有饼存进 `std::set`。遍历过一张饼，就删除之，因为 `std::set` 中查找和迭代器累加都是 $\mathrm O(\log n)$，一共 $2n$ 张饼，就是 $\mathrm O(n\log n)$。

```c++
#include <cstring>
#include <iostream>
#include <set>
#include <queue>
#define F(var, start, end) for\
	(int var = (start), var##_done = (end); var <= var##_done; ++var)

const int oxis = 200003;

int score_self[oxis], // 制作饼的一方认为的美味度
	score_other[oxis], // 对方认为的美味度
	ans[oxis]; // 最小深度，即答案

// 使 std::set 中按对方认为的美味度排序，从而可以查找
struct compare {
	bool operator()(const int &u, const int &v) const {
		return  score_other[u] != score_other[v] ?
			score_other[u] <  score_other[v] : u < v;
	}
};

int main()
{
	std::ios::sync_with_stdio(false);
	int n, d;
	std::cin >> n >> d;
	memset(ans, 127, sizeof(ans));
	std::set<int, compare> bessie, elsie; // bessie 存 bessie 收到的饼
	std::queue<int> bfs;
	F (i, 1, n) {
		std::cin >> score_self[i] >> score_other[i];
		elsie.insert(i);
	}
	F (i, 1 + n, 2 * n) {
		std::cin >> score_other[i] >> score_self[i];
		bessie.insert(i);
	}
	F (i, 1, 2 * n)
		if (score_other[i] == 0) {
			bfs.push(i);
			ans[i] = 1;
			std::set<int, compare> &cow = i > n ? bessie : elsie;
			cow.erase(i);
		}
	while (!bfs.empty()) {
		int now = bfs.front();
		bfs.pop();
		int tastiness = score_self[now], depth = 1 + ans[now];
		std::set<int, compare> &cow = now > n ? elsie : bessie;
// 收到饼的美味度 >= 给出饼的美味度 - d
// 将下界放到 score_other[0] 以利用 lower_bound
		*score_other = tastiness - d;
		for (auto i = cow.lower_bound(0);
				i != cow.end() && score_other[*i] <= tastiness;
				cow.erase(i++)) {
			int received = *i;
			bfs.push(received);
			ans[received] = depth;
		}
	}
	F (i, 1, n)
		if (ans[i] == 2139062143)
			std::cout << "-1\n";
		else
			std::cout << ans[i] << '\n';
}

```

---

## 作者：KarL05 (赞：2)

### 主要纠正一下楼上的题解

这道题的思路明显是从$Bessie$的饼干中$Elsie$觉得美味度为$0$的饼干和$Elsie$的饼干中$Bessie$觉得美味度为$0$的饼干入手。

因此我们可以得到一个建图手段，即从$0$的点开始入手反向建图，寻找可以从哪些点走到这个点即$Good End$。具体来讲，就是将原本$Bessie$给$Elsie$某个饼干，$Elsie$可以选择给出的饼干的建图方式，变成$Elsie$给出这个饼干，他可能收到什么饼干即可。

由于数据范围是 $1e5$，$n^2$的枚举不可取，我们可以将$Bessie$的饼干根据$Elsie$的美味度来排序。二分查找即可。建图后$BFS$即可。

由于有$D$的限制，时间复杂度应在$nlogn$左右。若数据不善良，可能会被卡到接近$n^2$，由于我不会证明所以证明略过。但是我的猜想是没有被卡到$n^2$的可能性，因为数据只能满足一部分的点很满，而应该可以保证平均下来是$nlogn$的。

解释变量名称: 

$in$ 读入的记录

$in$ $B[]$ Bessie的饼干

$in$ $E[]$ Elsie的饼干

$cmp$ 排序

$cop$ 二分查找

$edges$ 图

$vis$ & $dis$ 距离和走过的记录

Note: 楼上建图建错了

可能和楼上的代码有相似之处，主要指出问题所在指出。

```cpp
#include<iostream>
#include<cstring>
#include<climits>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<vector>
typedef long long ll;
using namespace std;

void prepare() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

int n,m;
const int maxn = 1e5+5;
struct in {
    int B, E;
    int id;
};
vector<int> edges[maxn*2];
in B[maxn];
in E[maxn];

bool cmp1(const in &a,const in &b){
    return a.B<b.B;
}
bool cmp2(const in &a,const in &b){
    return a.E<b.E;
}
struct BB {
    bool operator() (const in &a,const in &b) {
        return a.B < b.B;
    }
};
struct EE {
    bool operator()(const in &a,const in &b) {
        return a.E < b.E;
    }
};

queue<int> q;
int vis[2*maxn];
int dis[2*maxn];

int main () {
    prepare();
    cin>>n>>m;
    memset(dis,-1,sizeof(dis));
    for (int i=1;i<=n;i++) {
        cin>>B[i].B>>B[i].E;
        B[i].id = i;
        if (!B[i].E) {
            q.push(i);
            vis[i] = true;
            dis[i] = 1;
        }
    }    
    for (int i=1;i<=n;i++) {
        cin>>E[i].B>>E[i].E;
        E[i].id = i;
        if (!E[i].B) {
            q.push(i+n);
            vis[i+n] = true;
            dis[i+n] = 1;
        }
    }
    sort(E+1,E+1+n,cmp1);
    sort(B+1,B+1+n,cmp2);
    for (int i=1;i<=n;i++) {
        in cur = B[i];
        cur.B = B[i].B-m;
        int s = lower_bound(E+1,E+n+1,cur,BB())-E;
        for (int j=s;j<=n;j++) {
            if (E[j].B>B[i].B) break;
            edges[B[i].id].push_back(E[j].id+n);
        }
    }
    for (int i=1;i<=n;i++) {
        in cur = E[i];
        cur.E = E[i].E-m;
        int s = lower_bound(B+1,B+n+1,cur,EE())-B;
        for (int j=s;j<=n;j++) {
            if (B[j].E>E[i].E) break;
            edges[E[i].id+n].push_back(B[j].id);
        }
    }
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int i=0;i<edges[t].size();i++) {
            int cur = edges[t][i];
            if (vis[cur]) continue;
            vis[cur] = 1;
            dis[cur] = dis[t]+1;
            q.push(cur);
        }
    }
    for (int i=1;i<=n;i++) cout<<dis[i]<<"\n";
    return 0;
}
```


---

## 作者：C1R1A1E1F1 (赞：1)

一个不算严格的 $O(nlog n)$ 算法

## 方法一：40pts

首先这道题很明显是一个图论题，最朴素的想法就是对任意两个派进行 $O(n^2)$ 的匹配，如果A的派 $a$ 可以被当做派 $b$ 的回礼，则从 $a$ 向 $b$ 连一条 **有向边** ，建出一个二分图，然后再从左边后权值为 $0$ 的点和右边前权值为 $0$ 的点开始跑最短路，从而求出答案。

时间复杂度：建图 $O(n^2)$ +最短路 $O(n)$ （这里因为边权为1所以可以广搜跑一遍，如果这个点进过队就用不着了）

## 方法二：100pts (O2)

我们可以思考一下对于一个左侧的点 $a$ 来说它能够连接的点 $b$ 必然有 $b$ 的前权值是在 $a$ 的前权值到 $a$ 的前权值减 $d$ 这个区间中，右侧点同理，所以我们自然可以想到可以对左侧的点按后权值排序，右侧的点按前权值排序，然后二分查找。

(理论)时间复杂度：排序 $O(nlogn)$ +建图二分 $O(nlogn+n^2)$ +最短路  $O(n)$

## 方法三：100pts

很明显在建图过程中我们是向 $(l,r)$ 的一个区间连边的，而且在广搜过程中我们还会发现一个性质：如果一个点被访问过，那么它就不会再次做出贡献了，从而我们可以不在最开始建图，而是等到搜到第 $i$ 个点时再进行连边建图。

从而我们可以发现这题的建图本质上就是一个区间覆盖问题，从而我们自然可以用并查集进行快速查询和连边

（理论）时间复杂度：排序 $O(nlogn)$ +建图 $O(nlogn+n)$ +最短路 $O(n)$

### AC Code

```cpp
#include <bits/stdc++.h>
#define mn 100005
using namespace std;
struct it
{
	int af,bf,id;
}e[mn*2];
int n,d,dis[mn*2],fa[mn*2],ans[mn];
bool cm1(it a,it b)
{
	return a.af<b.af;
}
bool cm2(it a,it b)
{
	return a.bf<b.bf;
}
queue<int>q;
int er1(int num)
{
	int l=n+1,r=2*n;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(e[mid].af<=num)
			l=mid;
		else
			r=mid-1;
	}
	if(e[l].af<=num)
		return l;
	return -1;
}
int er2(int num)
{
	int l=n+1,r=2*n;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(e[mid].af>=num)
			r=mid;
		else
			l=mid+1;
	}
	if(e[l].af>=num)
		return l;
	return -1;
}
int er3(int num)
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(e[mid].bf<=num)
			l=mid;
		else
			r=mid-1;
	}
	if(e[l].bf<=num)
		return l;
	return -1;
}
int er4(int num)
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(e[mid].bf>=num)
			r=mid;
		else
			l=mid+1;
	}
	if(e[l].bf>=num)
		return l;
	return -1;
}
int gf(int x)
{
	if(x==fa[x])
		return x;
	return fa[x]=gf(fa[x]);
}
int main()
{
	cin>>n>>d;
	for(int i=1;i<=2*n;i++)
		cin>>e[i].af>>e[i].bf,e[i].id=i,fa[i]=i,dis[i]=-1;
	fa[2*n+1]=2*n+1;
	sort(e+1,e+1+n,cm2);
	sort(e+1+n,e+1+2*n,cm1);
	for(int i=1;i<=n&&e[i].bf==0;i++)
		q.push(i),dis[i]=1,fa[i]=i+1;
	for(int i=n+1;i<=2*n&&e[i].af==0;i++)
		q.push(i),dis[i]=1,fa[i]=i+1;
	while(!q.empty())
	{
		int temp=q.front();
		q.pop();
		if(temp<=n)
		{
			int r=er1(e[temp].af),l=er2(e[temp].af-d);
			if(l==-1||r==-1)
				continue;
			for(int i=gf(l);i<=r;i=gf(i))
			{
				dis[i]=dis[temp]+1;
				fa[i]=i+1;
				q.push(i);
				if(i==2*n)
					fa[i]=2*n+1;
				i=gf(i);
			}
		}
		else
		{
			int r=er3(e[temp].bf),l=er4(e[temp].bf-d);
			if(l==-1||r==-1)
				continue;
			for(int i=gf(l);i<=r;i=gf(i))
			{
				dis[i]=dis[temp]+1;
				fa[i]=i+1;
				q.push(i);
				if(i==n)
					fa[i]=2*n+1;
				i=gf(i);
			}
		}
	}
	for(int i=1;i<=n;i++)
		ans[e[i].id]=dis[i];
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<endl;
}
```


---

## 作者：CodyTheWolf (赞：0)

提供一个用平衡树来优化单点向区间连边的做法。

以下把Bessie简称B，Elsie简称E。

------------
不过还是先讲一下大致思路，如果已经清楚可以跳过：


可以把数据分成“四个象限”（每个象限都是竖着的$n$个数字）。

|  |B的评分  | E的评分 |
| :----------: | :----------: | :----------: |
| B做的 | 第二象限 | 第一象限 |
|  E做的| 第三象限 | 第四象限 |

很显然，要拿评价为0的饼往前倒推，并且这个评价为0的饼肯定不是自己做的，所以**一三象限**的0数据才是末状态。

如果是第一象限：

- 这个饼最后是送到E手里，且评分为0（第一象限）。
- 但在B看来，这个饼的评分是$x$（第二象限）。
- 所以之前E送B的饼，在B看来，评分区间在$[x-d,x]$（第三象限）

到此我们就找到这个饼的上一个状态在第三象限。
换句话说，
- 我们要拿评分为0（第一象限）的饼$A$，
- 去对应$x$(第二象限），
- 找到评分为$[x-d,x]$（第三象限）的饼$B$（可能有多个，所以是一个区间），把饼$A$向每个饼$B$连边

对于其他不是0的饼，其实链接方法也是一样的。
如果不是第一象限，是第三象限做法也类似，不赘述。

对于最后的图，我们从在第一第三象限评价为0的点为起点，跑最短路就可以知道每个饼的答案了。

因为边的长度都是1，且饼不能重复送，如果直接连最坏会连出$n^2$条边。所以我们考虑用BFS跑最短路，并且动态“连边”（其实就是丢进队列嘛）。	所谓动态就是连边的时候**只连还没有访问过的**饼。

这就引出了问题：那么怎么快速访问这些访问的饼？


------------

第一种：用FHQ Treap维护区间。

熟悉FHQ Treap的朋友很快就能想到，直接裂出一个$[x,x-d]$的区间，把这个区间（树）DFS，一个一个和待连点链接就可以了，最后这个区间就不合并回去（相当于删掉）。

对于这道题，只需要分别对B和E开一颗平衡树，第一关键字记**另一个人对自己饼的评分**，第二关键字才是自己对自己饼的评分，并且还要记录饼的编号（第三关键字）。

具体实现方法看代码会更清楚。

因为每个点只会被访问一次，并且每次裂开平衡树只需要花费$log(n)$的复杂度，最多连$n$次边，显然时间复杂度$O(nlogn)$，~~而且还不需要排序什么的~~。

------------

第二种：用带权并查集维护区间（可能是另外一篇题解的做法？没有仔细看）

如果一个点被访问过了，直接和前一个点的集合合并。

每次访问一个点的时候，不是当前标记$+1$跳到下一个点，而是$+$该点**集合的总点数**。因此每个集合的初始总点数就是1。抽象理解一点就是把一堆数绑在一起形成一个区间，只有第一个数是有效的，可访问的，其他都是访问过的。

对于这道题，只需要lower_bound找出第一个符合要求的点，再找到该点的祖先（因为这个点可能已经被访问过了）$+$**集合的总点数**到没有访问过的点（注意这个点也有可能超出范围了）。

蒟蒻之前做过一道用这种方法做的题，但是实在想不起来是哪道了。这种使用的数据结构很简单，但是其实会比平衡树的方法麻烦许多，还是不太推荐。~~(那道题记得调了不少，而用平衡树这题1A了）~~

------------

第三种用线段树维护其他题解有，就不再赘述了。~~（其实是不会）~~


------------

只有第一种的代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN=2e5+5;
int ans[MAXN];//最终答案
int n,d;
struct Node{int x,id,cnt;};
queue<Node> Q;//BFS求最短路的队列

struct FHQ_Treap//可爱的平衡树
{
	int val[MAXN],self[MAXN],id[MAXN],heap[MAXN],lt[MAXN],rt[MAXN],sz[MAXN];
		
	inline void PushUp(int x){sz[x]=sz[lt[x]]+sz[rt[x]]+1;}
	inline int Merge(int x,int y)
	{
		if(!x||!y) return x|y;
		if(heap[x]<heap[y]) return rt[x]=Merge(rt[x],y),PushUp(x),x;
		else return lt[y]=Merge(x,lt[y]),PushUp(y),y;
	}
	inline void Split(int x,int k,int &u,int &v)
	{
		if(!x) {u=v=0;return;}
		if(val[x]<=k) u=x,Split(rt[x],k,rt[u],v),PushUp(x);
		else v=x,Split(lt[x],k,u,lt[v]),PushUp(x);
	}
	
	int root,x,y,z,tot;
	inline int New(int a,int b,int c){return val[++tot]=a,self[tot]=b,heap[tot]=rand(),sz[tot]=1,id[tot]=c,tot;}
	inline void Insert(int a,int b,int c){Split(root,a,x,y),root=Merge(x,Merge(New(a,b,c),y));}
	
	inline void DFS(int p,Node t){if(p) Q.push({self[p],id[p],t.cnt+1}),DFS(lt[p],t),DFS(rt[p],t);}
	//直接遍历整棵树并且“连边”（就丢进队列而已）
	
	inline void Modify(Node t){Split(root,t.x-d-1,x,y),Split(y,t.x,y,z),root=Merge(x,z),DFS(y,t);}
	//裂出[x-d,x]这个区间
	
}B,E;

signed main(void)
{
	cin>>n>>d;
	for(int i=1,b,e;i<=n;i++)
	{
		scanf("%d %d",&b,&e);
		if(e==0) Q.push({b,i,1});//如果评价为0就可以直接当起点了，不放入平衡树
		else B.Insert(e,b,i);
	}
	for(int i=1,b,e;i<=n;i++)
	{
		scanf("%d %d",&b,&e);
		if(b==0) Q.push({e,i+n,1});//如果评价为0就可以直接当起点了，不放入平衡树
		else E.Insert(b,e,i+n);
	}
	//id<=n是Bessie的饼
	while(!Q.empty())
	{
		Node t=Q.front();Q.pop();
		if(t.id<=n) E.Modify(t),ans[t.id]=t.cnt;//要去对方的平衡树内找，上个饼可能的评价
		else B.Modify(t);
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]?ans[i]:-1);
	return 0;
}

```


---

## 作者：zjjws (赞：0)

将每个饼视作一个二元组，表示如下：

$$(x_1,y_1),(x_2,y_2)\dots(x_n,y_n)$$

$$(x_{n+1},y_{n+1}),(x_{n+2},y_{n+2})\dots(x_{2n},y_{2n})$$

设每次选择的饼的序列为 $a_1,a_2,a_3\dots a_p$，满足：

$$y_{a_1}<y_{a_2}\le y_{a_1}+d$$

$$x_{a_2}<x_{a_3}\le x_{a_2}+d$$

$$y_{a_3}<y_{a_4}\le y_{a_3}+d$$


$$\dots\dots$$

根据这个特征就可以建边，但是 $n\le 10^5$。

这个图在极度愤怒的情况下可以给你塞 $10^{10}$ 条边。

可这个性质并不会因此而无用，先换个角度考虑。

设饼 $i,x$，满足：$x\in Z,i\in Z,i\in[1,n],x\in[n+1,2n]$

如果把下面的二元组按 $y$ 从小到大排序过，对于每一个饼 $i\le n$，所有满足 $i\to x$ 的 $x$ 在排序后是连续的一段。

相同的，对于 $x\to i$ 也是可以一样求出对应的区间的。

对于任意的 $i\le n$，$(x_i,0)$ 和 $(0,y_{i+n})$ 都可以作为结束。

那么所有和结束标志相连的饼也可以达到 Happy End，易证明，在一轮来回送礼中，只有终点才可能是终止节点。

也就是说，所有可以达到 Happy End 的饼，都可以通过找到自己对应的那一段区间去继续更新答案，因为每条边权为 $1$，所以可以直接 Dijkstra 跑最短路，在所有 Bessie 的饼都更新过权值以后就可以直接跳出去了。

~~因为数据过水就直接跑过去了~~

然后因为翻译的锅害我调了好久，回礼是需要**大于等于**而不是**大于**。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAX=1e5+3;
struct milk
{
    int x,y;
    int l,r;
};
milk a[MAX];
milk b[MAX];
int d[MAX<<1];
int ans[MAX<<1];
int n_a[MAX];
int n_b[MAX];
int n,D;
inline bool myru_n_a(int x,int y){return a[x].y<a[y].y;}
inline bool myru_n_b(int x,int y){return b[x].x<b[y].x;}
LL rin()
{
    LL s=0;
    char c=getchar();
    bool bj=0;
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')c=getchar(),bj=true;
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
int main()
{
    n=rin();D=rin();
    for(int i=1;i<=n;i++)a[i].x=rin(),a[i].y=rin();
    for(int i=1;i<=n;i++)b[i].x=rin(),b[i].y=rin();
    for(int i=1;i<=n;i++)n_a[i]=n_b[i]=i;
    sort(n_a+1,n_a+n+1,myru_n_a);
    sort(n_b+1,n_b+n+1,myru_n_b);

    int head=1,tail=0;
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i].y==0)d[++tail]=i,ans[i]=1,sum++;
        int l,r;
        a[i].l=n+1;a[i].r=0;
        l=1;r=n;
        for(;l<=r;)
        {
            int mid=(l+r)>>1;
            if(b[n_b[mid]].x<=a[i].x)a[i].r=mid,l=mid+1;
            else r=mid-1;
        }
        int now=a[i].x-D;
        l=1;r=n;
        for(;l<=r;)
        {
            int mid=(l+r)>>1;
            if(b[n_b[mid]].x>=now)a[i].l=mid,r=mid-1;
            else l=mid+1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(b[i].x==0)d[++tail]=i+n,ans[i+n]=1;
        int l,r;
        b[i].l=n+1;b[i].r=0;
        for(l=1,r=n;l<=r;)
        {
            int mid=(l+r)>>1;
            if(a[n_a[mid]].y<=b[i].y)b[i].r=mid,l=mid+1;
            else r=mid-1;
        }
        int now=b[i].y-D;
        for(l=1,r=n;l<=r;)
        {
            int mid=(l+r)>>1;
            if(a[n_a[mid]].y>=now)b[i].l=mid,r=mid-1;
            else l=mid+1;
        }
    }
    for(;head<=tail;)
    {
        int x=d[head++];
        int y=ans[x];
        if(x>n)
        {
            x-=n;
            int l=b[x].l,r=b[x].r;
            for(int i=l;i<=r;i++)if(!ans[n_a[i]])ans[n_a[i]]=y+1,d[++tail]=n_a[i],sum++;
        }
        else
        {
            int l=a[x].l,r=a[x].r;
            for(int i=l;i<=r;i++)if(!ans[n_b[i]+n])ans[n_b[i]+n]=y+1,d[++tail]=n_b[i]+n;
        }
        if(sum==n)break;
    }
    for(int i=1;i<=n;i++)if(!ans[i])printf("-1\n");else printf("%d\n",ans[i]);
    return 0;
}
```
如果需要正确的复杂度，那肯定就是线段树维护区间连边，然后跑最短路，这个是可以证明最多只有 $2n\ \log n$ 条边的。

前面的暴力是完全可以卡到 $\operatorname O(n^2)$ 的，只是在数据水的情况下甚至可以碾标算，毕竟线段树自带常数。

---

