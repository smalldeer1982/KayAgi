# Take-off Ramps

## 题目描述

Vasya participates in a ski race along the $ X $ axis. The start is at point $ 0 $ , and the finish is at $ L $ , that is, at a distance $ L $ meters from the start in the positive direction of the axis. Vasya has been training so hard that he can run one meter in exactly one second.

Besides, there are $ n $ take-off ramps on the track, each ramp is characterized by four numbers:

- $ x_{i} $ represents the ramp's coordinate
- $ d_{i} $ represents from how many meters Vasya will land if he goes down this ramp
- $ t_{i} $ represents the flight time in seconds
- $ p_{i} $ is the number, indicating for how many meters Vasya should gather speed to get ready and fly off the ramp. As Vasya gathers speed, he should ski on the snow (that is, he should not be flying), but his speed still equals one meter per second.

Vasya is allowed to move in any direction on the $ X $ axis, but he is prohibited to cross the start line, that is go to the negative semiaxis. Vasya himself chooses which take-off ramps he will use and in what order, that is, he is not obliged to take off from all the ramps he encounters. Specifically, Vasya can skip the ramp. It is guaranteed that $ x_{i}+d_{i}<=L $ , that is, Vasya cannot cross the finish line in flight.

Vasya can jump from the ramp only in the positive direction of $ X $ axis. More formally, when using the $ i $ -th ramp, Vasya starts gathering speed at point $ x_{i}-p_{i} $ , jumps at point $ x_{i} $ , and lands at point $ x_{i}+d_{i} $ . He cannot use the ramp in opposite direction.

Your task is to find the minimum time that Vasya will spend to cover the distance.

## 说明/提示

In the first sample, Vasya cannot use ramp 2, because then he will need to gather speed starting from point -3, which is not permitted by the statement. The optimal option is using ramp 1, the resulting time is: moving to the point of gathering speed + gathering speed until reaching the takeoff ramp + flight time + moving to the finish line $ =0+5+5+5=15 $ .

In the second sample using ramp 1 is not optimal for Vasya as $ t_{1}&gt;d_{1} $ . The optimal option is using ramp 2, the resulting time is: moving to the point of gathering speed + gathering speed until reaching the takeoff ramp + flight time + moving to the finish line $ =14+1+1+0=16 $ .

## 样例 #1

### 输入

```
2 20
5 10 5 5
4 16 1 7
```

### 输出

```
15
1
1 ```

## 样例 #2

### 输入

```
2 20
9 8 12 6
15 5 1 1
```

### 输出

```
16
1
2 ```

# 题解

## 作者：Jur_Cai (赞：2)

给出一种 dp 的做法。

先按 $x_i$ 排个序，设一个 $f_i$ 表示到达第 $i$ 个跳板的 $x_i$ 处且可以使用的情况下，所需的最小时间。

可以发现，能转移到 $i$ 的 $j$，一定满足 $x_j\le x_i$，这是排序的原因。且一定是先从 $x_j+d_j$ 走到 $x_i-p_i$，再到 $x_i$，才能满足能使用的条件，可以自己画图理解一下。

这样子就可以写出 dp 式子（ 进行了一定的简化 ）

$$
f_i=\min\{f_j+t_j+dist(x_j+d_j,x_i-p_i)+p_i\}
$$

$dist$ 为两者作差的绝对值，即为两点间距离

考虑进行优化，将关于 $j$ 的项和 $i$ 分开，绝对值的处理和 [这题](https://www.luogu.com.cn/problem/P2885) 很类似，将其分为 $x_j+d_j\le x_i-p_i$ 和 $x_j+d_j\ge x_i-p_i$ 两种情况，作差的绝对值分别为 $-(x_j+d_j)+(x_i-p_i)$ 和 $(x_j+d_j)-(x_i-p_i)$。

这样就可以将有关 $i$ 和 $j$ 的项分开，然后用前、后缀 min 维护即可。

但是 $L$ 很大，所以还要把点都离散化一下。

时间复杂度瓶颈在排序，所以还是 $O(n\log n)$。

具体实现及细节见代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3fll
using namespace std;
struct node {
    ll x,d,t,p;
    int id;
} a[100005];
inline bool cmpx(node u,node v) {
    if(u.x==v.x) return u.id<v.id;
    return u.x<v.x;
}
ll f[100005];
int pos[100005];
map<ll,int> val;
//这里没有用数组，而是直接用了树状数组维护前后缀min
//但是对整体的时间复杂度并不影响
#define lowbit(x) x&-x
ll cnt,pre[200005],suf[200005];
int prepos[200005],sufpos[200005];
inline void addpre(ll x,ll k,int pos) {
    for(; x<=cnt; x+=lowbit(x))
        if(k<pre[x]) {
            pre[x]=k;
            prepos[x]=pos;
        }
}
inline void addsuf(ll x,ll k,int pos) {
    for(; x<=cnt; x+=lowbit(x))
        if(k<suf[x]) {
            suf[x]=k;
            sufpos[x]=pos;
        }
}
inline pair<ll,int> querypre(ll x) {
    ll res=INF;
    int pos=-1;
    for(; x; x-=lowbit(x))
        if(pre[x]<res) {
            res=pre[x];
            pos=prepos[x];
        }
    return make_pair(res,pos);
}
inline pair<ll,int> querysuf(ll x) {
    ll res=INF;
    int pos=-1;
    for(; x; x-=lowbit(x))
        if(suf[x]<res) {
            res=suf[x];
            pos=sufpos[x];
        }
    return make_pair(res,pos);
}
vector<ll> tmp;
int main() {
    ll n,L;
    scanf("%lld%lld",&n,&L);
    for(int i=1; i<=n; i++) {
        scanf("%lld%lld%lld%lld",&a[i].x,&a[i].d,&a[i].t,&a[i].p),a[i].id=i;
        tmp.push_back(a[i].x+a[i].d);
        tmp.push_back(a[i].x-a[i].p);
    }
    //在终点也建一个跳板，方便直接dp转移算出答案
    sort(a+1,a+n+1,cmpx),n++,a[n].x=L,a[n].p=a[n].d=0,a[n].id=n;

    //对有用的坐标离散化
    tmp.push_back(L),sort(tmp.begin(),tmp.end());
    for(int i=0; i<tmp.size(); i++)
        if(val.find(tmp[i])==val.end()) val[tmp[i]]=++cnt;

    memset(f,0x3f,sizeof(f));
    memset(pre,0x3f,sizeof(pre));
    memset(suf,0x3f,sizeof(suf));
    for(int i=1; i<=n; i++) {
        if(a[i].x>=a[i].p) f[i]=a[i].x;
        else continue;
        //当上个跳板落点在这个点之前
        pair<ll,int> preans=querypre(val[a[i].x-a[i].p]);
        if(preans.first+(a[i].x-a[i].p)+a[i].p<f[i]) {
            f[i]=preans.first+(a[i].x-a[i].p)+a[i].p;
            pos[a[i].id]=preans.second;
        }
        //当上个跳板落点在这个点之后
        pair<ll,int> sufans=querysuf(cnt-val[a[i].x-a[i].p]+1);
        if(sufans.first-(a[i].x-a[i].p)+a[i].p<f[i]) {
            f[i]=sufans.first-(a[i].x-a[i].p)+a[i].p;
            pos[a[i].id]=sufans.second;
        }
        //更新前后缀min
        addpre(val[a[i].x+a[i].d],f[i]+a[i].t-(a[i].x+a[i].d),a[i].id);
        addsuf(cnt-val[a[i].x+a[i].d]+1,f[i]+a[i].t+(a[i].x+a[i].d),a[i].id);
        //注意有关pos的相关值都要用原位置
    }
    cout<<f[a[n].id]<<'\n';
    vector<int> ans;
    int now=n;
    while(pos[now]) {
        ans.push_back(pos[now]);
        now=pos[now];
    }
    cout<<ans.size()<<'\n';
    for(int i=ans.size()-1; i>=0; i--) cout<<ans[i]<<" ";
    return 0;
}
```

---

## 作者：Stay_Hungry (赞：1)

题意很明了，这里就不再详细解释了。   
我们定义“起跳点”为$x_i-p_i$点，“落地点”为$x_i+d_i$，对起跳点和落地点分别排序，然后按下标顺序排序，对于相邻起跳点和起跳点之间、落地点与落地点之间连接一条长度为下标差的双向边，对于每个对应的起跳点和落地点连接一条单向边，边权为$t_i+p_i$，对于每个落地点，与离他向后最近的起跳点连边，然后建立代表$0$和$L$的源点，跑个最短路即可$AC$

为了方便理解，样例二的建图如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/gmtjnclf.png)

---

## 作者：VenusM1nT (赞：1)

考虑第 $i$ 个起跳点构造两个特殊点，其坐标分别为 $x_i-p_i$ 和 $x_i+d_i$，同时将起点终点设为特殊点，最后会得到若干特殊点，考虑以坐标为关键字排序，然后在相邻点之间连正边和反边，对应向左向右走；对于每个起跳点，直接从 $x_i-p_i$ 向 $x_i+d_i$ 连边，权值为 $p_i+t_i$，若走这条边则代表着在第 $i$ 个点起跳，最后跑最短路就可以得到答案。  
然而方案实在是太草了，不知道怎么搞，先放个求最短时间的程序在这吧。
```cpp
#include<bits/stdc++.h>
#define N 500000
#define reg register
#define inl inline
using namespace std;
map <int,int> mp;
map <int,int> f;
int cnt,fst[N+5],nxt[N+5],to[N+5],w[N+5];
int n,L,nod[N+5],tot,x[N+5],d[N+5],t[N+5],p[N+5],S=1,T;
long long dis[N+5];
struct Node
{
	int u;
	long long dis;
	friend bool operator < (const Node &x,const Node &y)
	{
		return x.dis<y.dis;
	}
};
priority_queue <Node> q;
inl void AddEdge(reg int u,reg int v,reg int c)
{
	//printf("   # ( %d ¡ú %d ) : %d\n",u,v,c);
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
	w[cnt]=c;
}
inl void Dijkstra()
{
	memset(dis,60,sizeof(dis));
	dis[S]=0;
	q.push((Node){S,dis[S]});
	while(!q.empty())
	{
		reg Node now=q.top();
		q.pop();
		reg int u=now.u;
		reg long long d=now.dis;
		//printf(" $ : %d\n",u);
		if(d!=dis[u]) continue;
		for(reg int i=fst[u];i;i=nxt[i])
		{
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i])
			{
				dis[v]=dis[u]+w[i];
				q.push((Node){v,dis[v]});
			}
		}
	}
}
int main()
{
	scanf("%d %d",&n,&L);
	nod[++tot]=0; nod[++tot]=L;
	mp[0]=mp[L]=1;
	for(reg int i=1;i<=n;i++)
	{
		scanf("%d %d %d %d",&x[i],&d[i],&t[i],&p[i]);
		reg int n1=x[i]-p[i],n2=x[i]+d[i];
		if(n1>=0 && !mp[n1])
		{
			mp[n1]=1;
			nod[++tot]=n1;
		}
		if(n1>=0 && n2>=0 && !mp[n2])
		{
			mp[n2]=1;
			nod[++tot]=n2;
		}
	}
	sort(nod+1,nod+tot+1);
	for(reg int i=1;i<tot;i++)// i µã±àºÅ   nod [ i ] ×ø±ê 
	{
		reg int d=nod[i+1]-nod[i];
		AddEdge(i,i+1,d); AddEdge(i+1,i,d);
		if(nod[i]==L) T=i;
		mp[nod[i]]=i;
	}
	if(nod[tot]==L) T=tot;
	mp[nod[tot]]=tot;
	//for(reg int i=1;i<=tot;i++) printf(" $ %d -> %d\n",nod[i],mp[nod[i]]);
	for(reg int i=1;i<=n;i++)
	{
		if(x[i]-p[i]<0) continue;
		reg int l=mp[x[i]-p[i]],r=mp[x[i]+d[i]];
		AddEdge(l,r,p[i]+t[i]);
	}
	Dijkstra();
	printf("%lld\n",dis[T]);
	return 0;
}
```

---

## 作者：Yuby (赞：1)

[题面](https://www.luogu.com.cn/problem/CF141D)

点数：2300

#### 标签：

图的建立，最短路

#### 分析：

注意到 $L \leq 10^9$ 说明复杂度与 $L$ 无关（这题明显很图论）。

这题中只有两种方法，走和跳。考虑跳的问题。为方便大佬们思考，下文中将我自己建的点统称虚点。

注意题目中跳只能在连续走了 $p_i$ 步之后向右侧跳 $d_i$ 步，且不能往回跳，不难想到在 $x_i-p_i$ 的地方建一条指向 $x_i+d_i$ 的边，并在这两个位置设置虚点。

为方便处理走的情况我们把所有的 $x_i$ 和 $L$ 还有 $0$ 也加入虚点之中。最后我们把虚点按照 $x$ 升序排序并把相邻的点连在一起，就是走的情况。

#### 注意：

不要直接把建虚点的数组排序。。。不然你前面存在 map 里的编号就乱了。。。（可能只是我太菜了）

把第 $i$ 个点的跳跃起点，即 $x_i-p_i$，直接连到第 $i-1$ 个，即第 $x_{i-1}$ 个虚点是一种典型的错误想法，因为如果 $p_i \geq x_i-x_{i-1}$ 的话 $x_i-p_i$ 应该连第 $i-2$ 虚点而不是第 $i-1$虚点。

注意走的情况应该为双向边，而跳的情况应该为单向边。

因为在走到另一个虚点之前无法进行跳，所以这样建边的正确性是显然的。

为什么要建虚点呢？因为 $L \leq 10^9$ 显然不能使用坐标为点。

方案的话就在 dijkstra 的过程中记录路径即可。

总复杂度：$O(排序复杂度+dijstra的复杂度+map复杂度)$，大致为 $O(m\log m)$，即 $O(能过)$。

代码：

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define pc putchar
using namespace std;
typedef long long ll;
const ll LLINF=ll(1e18+7);
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
const ll MAXN=1e6+7,MAXM=1e6+7;
ll n,L,m;
ll head[MAXM],edgenum;
struct in
{
	ll x,d,t,p,id;
	bool operator<(const in& xx)const
	{
		return x<xx.x;
	}
}a[MAXM],b[MAXM];
map<ll,ll>mp,mp2;
map<ll,bool>mp1;
struct Edge
{
	ll u,v,nxt,w;
}edge[MAXM];
void add_edge(ll u,ll v,ll w)
{
	edge[++edgenum].nxt=head[u];
	edge[edgenum].v=v;
	edge[edgenum].u=u;
	edge[edgenum].w=w;
	head[u]=edgenum;
}
void add(ll u,ll v,ll w){add_edge(u,v,w);add_edge(v,u,w);}
struct node
{
	ll x,num;
}pre[MAXN];
ll dis[MAXM];
bool book[MAXM];
priority_queue<pair<ll,ll> >q;
void dijkstra()
{
	mem(book,0);
	for(ll i=0;i<=m;i++)dis[i]=LLINF;
	dis[mp[0]]=0;
	q.push(make_pair(0,mp[0]));
	while(q.size())
	{
		ll x=q.top().second;q.pop();
		if(book[x])continue;
		book[x]=1;
		for(ll i=head[x];i;i=edge[i].nxt)
		{
			ll tmp=edge[i].v;
			if(dis[tmp]>dis[x]+edge[i].w)
			{
				dis[tmp]=dis[x]+edge[i].w;
				pre[tmp].x=x;
				pre[tmp].num=i;
				q.push(make_pair(-dis[tmp],tmp));
			}
		}
	}
}
stack<ll>ans;
int main()
{
	n=read(),L=read();
	ll cnt=0;
	for(ll i=1;i<=n;i++)
	{
		ll x=read(),d=read(),t=read(),p=read();
		if(!mp[x])
		{
			mp[x]=++m;a[m].x=x;
		}
		if(x-p>=0&&!mp[x-p])
		{
			mp[x-p]=++m;cnt++;
			a[m].x=x-p;mp1[x-p]=1;
		}
		if(!mp[x+d])
		{
			mp[x+d]=++m;cnt++;
			a[m].x=x+d;
			mp1[x+d]=1;
		}
		if(x-p>=0)
			add_edge(mp[x-p],mp[x+d],t+p),mp2[edgenum]=i;//mp2来输出方案
	}
	if(!mp[L])mp[L]=++m,a[m].x=L;//不能忘了
	if(!mp[0])mp[0]=++m,a[m].x=0;
	for(ll i=1;i<=m;i++)//不能对a排序，不然就map就乱了
		b[i].x=a[i].x;
	sort(b+1,b+m+1);
	for(ll i=2;i<=m;i++)
		add(mp[b[i-1].x],mp[b[i].x],b[i].x-b[i-1].x);
	dijkstra();
	write(dis[mp[L]]),pc(10);
	ll x=mp[L];
	while(x)
	{
		if(mp2[pre[x].num])ans.push(mp2[pre[x].num]);
		x=pre[x].x;
	}
	write(ans.size()),pc(10);//STL!
	while(ans.size())
	{
		write(ans.top()),pc(32);
		ans.pop();
	}
	return 0;
}
```



---

## 作者：ifffer_2137 (赞：0)

小清新最短路入门题。
### 题意
给你一条数轴，你的速度是 $1$，可以左右走，目标是从 $0$ 到 $L$。还有若干个跳板 $x_i$，可以通过从 $x_i-p_i$ 开始向右助跑（速度也是 $1$）一段接起跳，然后向右跳跃到 $x_i+d_i$，跳跃时花费 $t_i$ 单位时间。求最短用时。
### 分析
一眼盯针。容易抿出最短路，所以考虑建图。

建图的关键在于减少点数和边数到一个合理范围内。

发现 $L$ 非常大，但跳板数量很少，所以需要特殊决策的点的数量是可以被接受的，我们只要把这些点拿出来看就行了。容易发现只有起点，终点，和各个跳板的起跑点和落点有用，其他点都没有什么特殊性，那么点数降到 $O(n)$ 了。

然后是连边，有走路和跳两种。点与点两两之间都可以走路互通，边数非常大，考虑优化。显然的可以把这些点扔到数轴上排序，然后相邻的点连双向边即可（因为可以左右走）。然后每个跳板的起跑点再向落点连单向边，边权就是 $p_i+t_i$，即助跑用时加跳跃用时。这样总共的边数也是 $O(n)$ 的。

于是直接跑 dij 就做完了。时间复杂度 $O(n\log n)$。注意要输出方案，所以要额外维护一个松弛的决策点。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
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
const int maxn=4e5+5;
int n,L;
struct node{int x,d,t,p;}a[maxn];
int t[maxn],tt;
struct edge{
	edge(){}
	edge(int V,int W,int Id){v=V,w=W,id=Id;}
	int v,w,id;
};
vector<edge> G[maxn];
int dis[maxn],vis[maxn];
int tran[maxn],us[maxn];
struct mem{
	int u,x;
	bool operator < (const mem &b) const{return x>b.x;}
};
priority_queue<mem> q;
void dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;q.push((mem){1,0});
	while(!q.empty()){
		int u=q.top().u;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(edge e:G[u]){
			int v=e.v,w=e.w,id=e.id;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				tran[v]=u,us[v]=id;
				if(!vis[v]) q.push((mem){v,dis[v]});
			}
		}
	}
}
vector<int> ans;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),L=read();
	t[++tt]=0,t[++tt]=L;
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].d=read(),a[i].t=read(),a[i].p=read();
		if(a[i].x-a[i].p<0) continue;
		t[++tt]=a[i].x-a[i].p,t[++tt]=a[i].x+a[i].d;
	}
	sort(t+1,t+tt+1),tt=unique(t+1,t+tt+1)-t-1;
	for(int i=1;i<tt;i++){
		G[i].eb(edge(i+1,t[i+1]-t[i],0));
		G[i+1].eb(edge(i,t[i+1]-t[i],0));
	}
	for(int i=1;i<=n;i++){
		if(a[i].x-a[i].p<0) continue;
		int u=lower_bound(t+1,t+tt+1,a[i].x-a[i].p)-t,v=lower_bound(t+1,t+tt+1,a[i].x+a[i].d)-t;
		G[u].eb(edge(v,a[i].p+a[i].t,i));
	}
	dijkstra();
	cout<<dis[tt]<<'\n';
	int u=tt;
	while(u){
		if(us[u]) ans.eb(us[u]);
		u=tran[u];
	}
	reverse(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(int x:ans) cout<<x<<' ';
	cout<<'\n';
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较好想但是巨难写的 dp 题，折磨死了。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
不难想到 dp，设计 $f_i$ 表示走到第 $i$ 个跳跃点**并且可以起跳**的最短时间。

这样就可以得到转移方程式：
$$f_i=\min(f_j+t_j+|(x_j+d_j)-(x_i-p_i)|+p_i)$$

想到用数据结构维护 $x_j+d_j$ 的插入找最小值。

发现带个绝对值，貌似很难弄。

考虑一条数轴，每插入一个点 $x$，那么距离最小的点要么就是在 $x$ 左边第一个，要么就是 $x$ 右边第一个。

把左右两边分开维护，也就相当于以 $x$ 为断点把数轴断为两段。

左边用一个 BIT 维护最小值，右边用一个 BIT 维护最小值，尝试下左边还是右边转移更优即可。

欸好像做完了？

是这样的，下面说点细节。

首先排序部分推荐用结构体，但是我降智人没用结构体。

可以插入一个跳跃点在 $l$ 这个位置方便得到答案。

因为要输出经过的点，所以要保留转移过程多存个 $g$ 把 $j$ 存下来即可。

但是记得输出的时候要**从前到后**输出。

BIT 数组和离散化存进去的数组记得两倍空间，不然挂飞。

剩下就是转移式和插入/查询点的细节了，照抄方程式即可，虽然代码会更长，但是不容易挂。

喜提最优解了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,V=1e5+10,M=1e5+10,INF=0x3f3f3f3f3f3f3f3f;
struct BIT//binary_indexed_tree
{
    int c[N<<1],p[N<<1],n;BIT(){memset(c,0x3f,sizeof c);}
    void modify(int x,int v,int id){for(;x<=n&&x;x+=x&-x) if(v<c[x]) c[x]=v,p[x]=id;}
    pair<int,int> query(int x){int res=INF,k=0;for(;x;x-=x&-x) if(c[x]<res) res=c[x],k=p[x];return {res,k};}
}tt[2];vector<int>ans;
int n,l,tot,a[N<<1],x[N],d[N],p[N],t[N],b[N],c[N],f[N],g[N],id[N],e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='.'||c=='#'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline bool cmp(int xx,int y){return x[xx]<x[y];}
inline void get(int a[])
{
    for(int i=1;i<=n;i++) e[i]=a[i];
    for(int i=1;i<=n;i++) a[i]=e[id[i]];
}
signed main()
{
    n=read(),l=read();for(int i=1;i<=n;i++) x[i]=read(),d[i]=read(),t[i]=read(),p[i]=read(),a[++tot]=x[i]+d[i],a[++tot]=x[i]-p[i],id[i]=i;
    sort(a+1,a+1+tot);sort(id+1,id+1+n,cmp);sort(x+1,x+1+n);tot=unique(a+1,a+1+tot)-a-1;get(d),get(t),get(p);
    for(int i=1;i<=n;i++) b[i]=lower_bound(a+1,a+1+tot,x[i]+d[i])-a,c[i]=lower_bound(a+1,a+1+tot,x[i]-p[i])-a;a[tot+1]=l;
    x[++n]=l,d[n]=0,t[n]=0,p[n]=0;b[n]=tot+1,c[n]=tot+1,id[n]=n;memset(f,0x3f,sizeof f);tt[0].n=tt[1].n=tot+10;
    for(int i=1;i<=n;i++)
    {
        if(x[i]>=p[i]) f[i]=x[i];else continue;
        auto res=tt[0].query(c[i]);
        if(res.first+x[i]<f[i]) f[i]=res.first+x[i],g[id[i]]=res.second;
        res=tt[1].query(tot-c[i]+1);
        if(res.first-x[i]+2*p[i]<f[i]) f[i]=res.first-x[i]+2*p[i],g[id[i]]=res.second;
        tt[0].modify(b[i],f[i]+t[i]-(x[i]+d[i]),id[i]);
        tt[1].modify(tot-b[i]+1,f[i]+t[i]+(x[i]+d[i]),id[i]);
    }int cur=n;print(f[cur]);put('\n');while(g[cur]) ans.emplace_back(g[cur]),cur=g[cur];
    print(ans.size());put('\n');reverse(ans.begin(),ans.end());for(auto i:ans) print(i),put(' ');
    genshin:;flush();return 0;
}
```

---

## 作者：WRuperD (赞：0)

浪费了我一个晚上。

显然的，我们可以设 $f_i$ 表示到达第 $i$ 个起跳点且可以起飞的最小时间。

于是 $f_i = \min\limits_{j = 1}^{i-1}{f_j + t_j + |(x_i - x_p) - (x_j + d_j)| + p_i}$

有一个绝对值，不好转移。考虑拆成 $x_j + d_j \leq x_i - x_p$ 和 $x_j + d_j > x_i - x_p$ 两部分分别计算。

即 $f_i = \begin{cases}
\min\limits_{j = 1}^{i-1}{f_j + t_j + (x_i - x_p) - (x_j + d_j) + p_i}(x_j + d_j \leq x_i - x_p) 
\\ \min\limits_{j = 1}^{i-1}{f_j + t_j - (x_i - x_p) + (x_j + d_j) + p_i}(x_j + d_j > x_i - x_p) 
\end{cases}$

这个柿子看着就很好优化。直接考虑离散化值域后用线段树优化维护转移即可。

时间复杂度 $O(n \log n)$

输出方案就把编号放进线段树应该就可以了吧，但是我一直没写对。

代码就不贴了

---

