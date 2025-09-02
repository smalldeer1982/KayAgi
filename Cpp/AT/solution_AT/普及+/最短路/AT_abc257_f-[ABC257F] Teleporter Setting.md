# [ABC257F] Teleporter Setting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc257/tasks/abc257_f

$ N $ 個の町と $ M $ 個のテレポーターがあり、 町は町 $ 1 $, 町 $ 2 $, $ \ldots $, 町$ N $ と番号づけられています。  
 それぞれのテレポーターは $ 2 $ つの町を双方向に結んでおり、テレポーターを使用する事によってその $ 2 $ つの町の間を $ 1 $ 分で移動することができます。

$ i $ 番目のテレポーターは町 $ U_i $ と町 $ V_i $ を双方向に結んでいますが、 いくつかのテレポーターについては結ぶ町の片方が決まっておらず、 $ U_i=0 $ のときそのテレポーターが結ぶ町の片方は町 $ V_i $ であるが、 もう片方が未定であることを意味します。

$ i=1,2,\ldots,N $ それぞれについて、次の問題を解いてください。

> 結ぶ町の片方が未定となっているテレポーターの結ぶ先をすべて町 $ i $ とする。 この時に町 $ 1 $ から町 $ N $ まで移動するのに最小で何分かかるか求めよ。 町 $ 1 $ から町 $ N $ までテレポーターのみを使って移動するのが不可能な場合は $ -1 $ を出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\times\ 10^5 $
- $ 1\leq\ M\leq\ 3\times\ 10^5 $
- $ 0\leq\ U_i\ <\ V_i\leq\ N $
- $ i\ \neq\ j $ ならば $ (U_i,V_i)\neq\ (U_j,V_j) $
- 入力は全て整数

### Sample Explanation 1

結ぶ先が未定となっているテレポーターの結び先を町 $ 1 $ としたとき、 $ 1 $ 番目と $ 2 $ 番目のテレポーターはともに町 $ 1 $ と町 $ 2 $ を結びます。 このとき、町 $ 1 $ から町 $ 3 $ への移動はできません。 結ぶ先が未定となっているテレポーターの結び先を町 $ 2 $ としたとき、 $ 1 $ 番目のテレポーターは町 $ 2 $ 同士を、 $ 2 $ 番目のテレポーターは町 $ 1 $ と町 $ 2 $ を結びます。 このときもやはり、町 $ 1 $ から町 $ 3 $ への移動はできません。 結ぶ先が未定となっているテレポーターの結び先を町 $ 3 $ としたとき、 $ 1 $ 番目のテレポーターは町 $ 3 $ と町 $ 2 $ を、 $ 2 $ 番目のテレポーターは町 $ 1 $ と町 $ 2 $ を結びます。 この時、次のようにして町 $ 1 $ から町 $ 3 $ へ $ 2 $ 分で移動できます。 - $ 2 $ 番目のテレポーターを使用し、町 $ 1 $ から町 $ 2 $ まで移動する。 - $ 1 $ 番目のテレポーターを使用し、町 $ 2 $ から町 $ 3 $ まで移動する。 よって、$ -1,-1,2 $ をこの順に出力します。 結ぶ先が未定となっているテレポーターの結び先によっては、 同じ町同士を結ぶテレポーターが存在する可能性や、 ある $ 2 $ つの町を結ぶテレポーターが複数存在する可能性がある事に注意してください。

## 样例 #1

### 输入

```
3 2
0 2
1 2```

### 输出

```
-1 -1 2```

## 样例 #2

### 输入

```
5 5
1 2
1 3
3 4
4 5
0 2```

### 输出

```
3 3 3 3 2```

# 题解

## 作者：mz2022 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc257_f)

思路：
--------
首先考虑暴力枚举不确定的点，跑 $n$ 遍 dijkstra，由于 $ n \leq 3 \times 10^5 $，显然不行。

正解，建一个超级源点 ${S_0}$ 点，对于每个不确定的点连一条到 ${S_0}$ 的边，易发现对于每个 ${S_i}$ 答案只有以下 $3$ 种情况。

$1$：${S_i}$ 为最短路上的点，则答案为 $1$ 到 $n$ 的最短路。

$2$：$1$ 到 ${S_i}$ 到 ${S_0}$ 到 $n$ 的最短路。

$3$：$1$ 到 ${S_0}$ 到 ${S_i}$ 到 $n$ 的最短路。

这样我们只需要维护 $1$ 与 $n$ 的单源最短路径，时间复杂度可以接受。

Code：
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >q;
struct node {
	int w, to, next;
} e[1000005];
int n, m, cnt, head[1000005], dis1[1000005], dis2[1000005], s1, s2, s3;
bool vis[1000005];
void add(int u, int v, int w) {
	e[++cnt].to = v;
	e[cnt].w = w;
	e[cnt].next = head[u];
	head[u] = cnt;
}
void d1() {
	memset(vis, 0, sizeof(vis));
	memset(dis1, 0x3f, sizeof(dis1));
	q.push(make_pair(0, 1));
	dis1[1] = 0;
	while (!q.empty()) {
		int now = q.top().second;
		q.pop();
		if (vis[now])
			continue;
		vis[now] = 1;
		for (int i = head[now]; i; i = e[i].next)
			if (dis1[now] + e[i].w < dis1[e[i].to]) {
				dis1[e[i].to] = dis1[now] + e[i].w;
				q.push(make_pair(dis1[e[i].to], e[i].to));
			}
	}
}
void d2() {
	memset(vis, 0, sizeof(vis));
	memset(dis2, 0x3f, sizeof(dis2));
	q.push(make_pair(0, n));
	dis2[n] = 0;
	while (!q.empty()) {
		int now = q.top().second;
		q.pop();
		if (vis[now])
			continue;
		vis[now] = 1;
		for (int i = head[now]; i; i = e[i].next)
			if (dis2[now] + e[i].w < dis2[e[i].to]) {
				dis2[e[i].to] = dis2[now] + e[i].w;
				q.push(make_pair(dis2[e[i].to], e[i].to));
			}
	}
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		add(u, v, 1);
		add(v, u, 1);
	}
	d1();
	d2();
	for (int i = 1; i <= n; i++) {
		int ans = min({dis1[n], dis1[0] + dis2[i], dis1[i] + dis2[0]});
		if (ans == 0x3f3f3f3f)cout << -1 << " ";
		else cout << ans << " ";
	}
	return 0;
}
```

---

## 作者：qiliu (赞：3)

# 思路

先声明一下，$dis1_i$ 表示不考虑不确定的边时点一到 $i$ 的距离，$disn_i$ 表示同样情况下 $n$ 到 $i$ 的距离。

首先每一次钦定所有不确定的 $u_j$ 为 $i$ 时，新增的边和所相连的点呈现为一个菊花图（下文中的叶子和根都是指这个菊花图的叶子和根），此时我们来考虑最短路是怎么形成的，因为新形成的图是菊花图，所以只能在以下几种情况中产生：

1. 不走新增的边。
2. 从一条新增的边走到 $i$ 上，然后从 $i$ 走原先的边直接走到 $n$。
3. 从原先的边走到 $i$ 上，然后经过一条新增的边走到 $n$。
4. 从一条新增的边走到 $i$ 上，然后经过一条新增的边走到 $n$。

然后我们来讨论每种情况在什么时候出现最小值。根据题意知这个菊花图的叶子结点是固定不变的，所以我们只需要考虑两个点，第一个点 $s$ 表示所有叶子中到点一距离最近的一个，第二个点 $t$ 表示所有叶子中到点 $n$ 距离最近的一个。此时我们就可以重新表示这几个状态了。

1. $dis1_n$。
2. $dis1_s+2+disn_t$。
3. $dis1_i+1+disn_t$。
4. $dis1_s+1+disn_i$。

所以我们只需要预处理出两个 $dis$，就可以 $O(1)$ 的统计答案了。

# Code

有注释，可放心观看。


```cpp
#include<bits/stdc++.h>
#define int long long
//#define DEBUG(x) cerr<<#x<<'='<<x<<endl
#define endl '\n'
using namespace std;
int rd(){
    char t=getchar();int f=1,x=0;
    while(t<'0'||t>'9'){ if(t=='-')f*=-1; t=getchar(); }
    while(t>='0'&&t<='9') x=x*10+t-'0',t=getchar();
    return x*f;
}void wt(int t){
    if(t<0)putchar('-'),t=-t;
    if(t>9)wt(t/10);
    putchar(t%10+'0');
    return;
}
const int N=3e5+100,INF=1e18;
int n,m;
vector<int>a[N];//vector存边
vector<int>leaf;//存储菊花图的叶子
int dis1[N],disn[N];//即题解中提到的dis1和disn
void get_dis(int S,int *dis){//bfs处理出dis
    queue<int>q;
    for(int i=1;i<=n;i++)dis[i]=INF;
    dis[S]=0;q.push(S);
    while(!q.empty()){
        int now=q.front();q.pop();
        for(int i=0,to;i<a[now].size();i++){to=a[now][i];
            if(dis[to]>dis[now]+1)dis[to]=dis[now]+1,q.push(to);
        }
    }return;
}
signed main(){
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=rd(),m=rd();
    for(int i=1;i<=m;i++){
        int u=rd(),v=rd();
        if(u==0)leaf.push_back(v);//存储叶子
        else a[u].push_back(v),a[v].push_back(u);
    }get_dis(1,dis1),get_dis(n,disn);
    int minn_of_dis1=INF,minn_of_disn=INF,dis1_min=-1,disn_min=-1;
    //dis1_min为题解中的s，disn_min为题解中的t
    for(auto x:leaf){
        if(minn_of_dis1>dis1[x])  minn_of_dis1=dis1[x],dis1_min=x;
        if(minn_of_disn>disn[x])  minn_of_disn=disn[x],disn_min=x;
    }for(int i=1;i<=n;i++){
        int ans=min({dis1[n],//情况1
                    (dis1_min==-1||disn_min==-1?INF:dis1[dis1_min]+2+disn[disn_min]),//情况2
                    (disn_min==-1?INF:dis1[i]+1+disn[disn_min]),//情况3
                    (dis1_min==-1?INF:dis1[dis1_min]+1+disn[i])});//情况4
        wt(ans<INF?ans:-1),putchar(' ');//别忘了判无解！！！！！
    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```

 _The End._

---

## 作者：FreedomKing (赞：2)

### 思路

对于有不确定边的最短路，考虑先分别处理出 $\{dis1\},\{disn\}$ 分别表示节点 $1$ 和 $n$ 到某节点的最短路。然后考虑不确定的边对最短路的贡献，设当前不确定的边全部连向 $i$，$\{p\}$ 表示不确定边的确定节点，则存在下面几种情况：

- 不经过点 $i$，答案即为 $dis1_n$；

- 从 $1$ 走到 $p_u$ 经过 $i$ 再从 $p_v$ 出来走到 $n$，答案为 $dis1_{p_u}+2+disn_{p_v}$，显然 $p$ 的元素是确定的而想要此式子最小可以预处理；

- 从 $1$ 直接走到 $i$ 然后经 $p_v$ 走到 $n$，答案是 $dis1_i+1+disn_{p_v}$，$p$ 是确定的同样可以像上面一样预处理出 $disn_{p_v}$ 的最小值；

- 与第三种类似，从 $n$ 直接走到 $i$ 然后经 $p_u$ 走到 $n$，答案是 $dis1_{p_u}+1+disn_i$，同上可以预处理最小值。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,xN=1e8+5,mN=5e3+5,mod=1e9+7;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		mod=(mod?mod:LONG_LONG_MAX);
		x=(p?x:1)%mod;
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
}
int n,dis1[N],disn[N];
vector<int>e[N],p;
inline void bfs(int x,int *dis){
	for(int i=1;i<=n;i++) dis[i]=1e9;
	queue<int>q;
	dis[x]=0;
	q.push(x);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i];
			if(dis[u]+1<dis[v]){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return;
}
signed main(){
	n=qr;int m=qr;
	for(int i=1;i<=m;i++){
		int u=qr,v=qr;
		if(!u) p.push_back(v);
		else{
			e[u].push_back(v);
			e[v].push_back(u);
		}
	}
	bfs(1,dis1);
	bfs(n,disn);
	int min1=1e9,minn=1e9;
	for(int i=0;i<p.size();i++){
		int v=p[i];
		min1=min(min1,dis1[v]);
		minn=min(minn,disn[v]);
	}
	for(int i=1;i<=n;i++){
		int ans=min({dis1[n],min1+2+minn,dis1[i]+1+minn,min1+1+disn[i]});
		if(ans>=1e9) qws(-1);
		else qws(ans);
	}
	return 0;
}
```

---

## 作者：__YSC__ (赞：2)

# 题目描述

一个 $N$ 个点 $M$ 条边的无向简单图。如果一条边的一个端点为 $0$，则这是一个不确定的端点。对于每个 $1 \le i \le N$，求当所有不确定的端点都确定为 $i$，从 $1$ 到 $N$ 的最短距离，若不能到达，输出 $-1$。

# 思路

"对于每个 $1 \le i \le N$，求当所有不确定的端点都确定为 $i$"这句话可以看做是从 $0$ 到 $i$ 有一条长度为 $0$ 的边。所以只需从结点 $1$ 和结点 $N$ 各 `bfs` 一遍，最终答案为 $\min \{dist_{0,N},dist_{0,0} + dist_{1, i},dist_{0,i}+dist_{1,0}\}$，其中 $dist_{0/1,u}$ 表示从 $1$ 或 $N$ 到 $u$ 的距离。

时空复杂度均为 $O(N+M)$。

## 细节

无。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 300001, INF = 300001;

struct Node {
  int u, dis;
};

int n, m, dist[2][MAXN];
bool vis[MAXN];
vector<int> e[MAXN];
queue<Node> que;

void Record(int u, int dis, bool op) {
  if(vis[u]) {
    return;
  }
  vis[u] = 1;
  dist[op][u] = dis;
  que.push({u, dis});
}

void bfs(int x, bool op) {
  fill(vis, vis + n + 1, 0);
  Record(x, 0, op);
  while(!que.empty()) {
    int u = que.front().u, dis = que.front().dis;
    que.pop();
    for(int v : e[u]) {
      Record(v, dis + 1, op);
    }
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  fill(dist[0], dist[1] + n + 1, INF);
  bfs(1, 0);
  bfs(n, 1);
  for(int i = 1; i <= n; ++i) {
    cout << (min({dist[0][n], dist[0][0] + dist[1][i], dist[0][i] + dist[1][0]}) >= INF ? -1 : min({dist[0][n], dist[0][0] + dist[1][i], dist[0][i] + dist[1][0]})) << " ";
  }
  return 0;
}

```

---

## 作者：Frictional (赞：1)

## 题意
给定一个无向图，其中有一些只有一个端点的虚边，对于每个 $i=1,2,3,...,n$ 将这些虚边连向 $i$ ,对于每个 $i$ 求出 $1$ 到 $n$ 的最短路，无法到达输出 $-1$。
## 解法
发现连边后的图与连边前的图只有那几个虚边发生了变化，（先将那个所有虚边连向的点 $i$ 叫做中心点），也就是说变化的只有各个点到 $i$ 的最短距离（也可能没变），可以用到各个虚点距离来更新到中心点的最短距离，而我们只关注 $1$ 和 $n$ 到中心点的距离。这样的话 $1$ 到 $n$ 的最短距离就是（原本的最短距离）与（$1$ 到中心点的最短距离与 $n$ 到中心点的距离的和）的最小值。
## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define db double
#define U unsigned
#define int long long
#define P pair<int,int>
#define pb push_back
#define MP make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define ROF(i,a,b) for(int i=a;i>=b;--i)
#define debug(x) cerr<<#x<<'='<<x<<endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define pcn putchar('\n')
#define pcs putchar(' ');
#define pc putchar
#define File(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#define ClockB clock_t start,end; start = clock();
#define ClockE end = clock(); cerr<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
using namespace std;
int _=1;
inline int rd(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
inline void wr(int x){
    if(x<0) pc('-'),x=(~x)+1;
    if(x>9) wr(x/10);
    pc((x%10)^48);
}
mt19937 mrand(chrono::system_clock::now().time_since_epoch().count()); 
int rnd(int l,int r){
  uniform_int_distribution<>dist(l,r);
  return dist(mrand);
}
double rnd(double l,double r){
  uniform_real_distribution<>dist(l,r);
  return dist(mrand);
}
void dl(vector<int> a){shuffle(all(a),mrand);}
template<const signed _MOD> struct ModInt{
    int x;
    ModInt(){x=0;}
    ModInt(int y){x=y%_MOD;}
    int Int(){return x;}
    int Pow(signed y){
        int ret=1,tmp=x;
        while(y){
            if(y&1)
                ret=((long long)ret*tmp)%_MOD;
            y>>=1;
            tmp=((long long)tmp*tmp)%_MOD;
        }
        return ret;
    }
    void operator = (int y){x=y%_MOD;}
    bool operator == (int y) const{return x==y;}
    bool operator == (ModInt y) const{return x==y.x;}
    bool operator != (int y) const{return x!=y;}
    bool operator != (ModInt y) const{return x!=y.x;}
    bool operator < (int y) const{return x<y;}
    bool operator < (ModInt y) const{return x<y.x;}
    bool operator > (int y) const{return x>y;}
    bool operator > (ModInt y) const{return x>y.x;}
    bool operator <= (int y) const{return x<=y;}
    bool operator <= (ModInt y) const{return x<=y.x;}
    bool operator >= (int y) const{return x>=y;}
    bool operator >= (ModInt y) const{return x>=y.x;}
    ModInt operator + (ModInt y) const{return ((long long)x+y.x)%_MOD;}
    ModInt operator * (ModInt y) const{
        return ((long long)x*y.x)%_MOD;
    }
    ModInt operator - (ModInt y) const{return ((x-y.x)%_MOD+_MOD)%_MOD;}
    ModInt operator + (int y) const{return ((long long)x+y)%_MOD;}
    ModInt operator * (int y) const{return ((long long)x*y)%_MOD;}
    ModInt operator - (int y) const{return ((x-y)%_MOD+_MOD)%_MOD;}
    void operator += (ModInt y){*this=*this+y;}
    void operator *= (ModInt y){*this=*this*y;}
    void operator -= (ModInt y){*this=*this-y;}
    void operator += (int y){x=((long long)x+y)%_MOD;}
    void operator *= (int y){x=((long long)x*y)%_MOD;}
    void operator -= (int y){x=((x-y)%_MOD+_MOD)%_MOD;}
    ModInt operator ^ (int y){
        ModInt ret=Pow(y);
        return ret;
    }
    ModInt operator / (ModInt y) const{
        return ((int)x*(y.Pow(_MOD-2)))%_MOD;
    }
    void operator /= (ModInt y){*this=*this/y;}
    template<class T> friend bool operator == (T y,ModInt t){return y==t.x;}
    template<class T> friend ModInt operator + (T t,ModInt y){return ((long long)t+y.x)%_MOD;}
    template<class T> friend ModInt operator * (T t,ModInt y){return ((long long)t*y.x)%_MOD;}
    template<class T> friend ModInt operator - (T t,ModInt y){return ((t-y.x)%_MOD+_MOD)%_MOD;}
    template<class T> friend ModInt operator / (T t,ModInt y){return ModInt((y/t).Pow(_MOD-2));}
    ModInt operator / (signed y) const{return ((long long)x*(ModInt(y).Pow(_MOD-2)))%_MOD;}
    void operator /= (signed y){*this=*this/y;}
    void operator ++ (){*this=*this+1;}
    void operator -- (){*this=*this-1;}
    void operator ++ (signed k){*this=*this+1;}
    void operator -- (signed k){*this=*this-1;}
};
int n,m;
const int N=32e5+5;
//以下的所有2是和点1有关的，1是和点n有关的
int dis1[N],dis2[N];
int u,v;
vector<int>im;
vector<int>ng[N];
bitset<N>vis;
void bfs(int s){
    FOR(i,1,n) dis1[i]=1e18;
    queue<int>q;
    q.push(s);
    dis1[s]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=1;
        for(auto x:ng[u]){
            dis1[x]=MIN(dis1[x],dis1[u]+1);
            if(!vis[x]) q.push(x);
        }
    }
}
int minn2=1e18,minn1=1e18;
int tmp2,tmp1;
int dis;
signed main(){
    // _=rd();
    while(_--){
        n=rd(),m=rd();
        FOR(i,1,m){
            u=rd(),v=rd();
            if(u) ng[u].pb(v),ng[v].pb(u);
            else im.pb(v);
        }
        bfs(1);
        FOR(i,1,n) dis2[i]=dis1[i];
        vis=0;
        bfs(n);//分别求出1和n到所有点的最短距离
        for(auto i:im) minn2=MIN(minn2,dis2[i]),minn1=MIN(minn1,dis1[i]);//处理1和n到所有虚边端点的最短距离，便于更新中心点的最短距离
        FOR(i,1,n){
            tmp1=dis1[i],tmp2=dis2[i];
            dis1[i]=MIN(dis1[i],minn1+1),dis2[i]=MIN(dis2[i],minn2+1);
            dis=MIN(dis2[n],dis1[i]+dis2[i]);
            cout<<((dis==1e18)?-1:dis)<<' ';
            dis1[i]=tmp1,dis2[i]=tmp2;
        }
    }
    return 0;
}
```

---

## 作者：_ldyex_ (赞：1)

## [题目](https://www.luogu.com.cn/problem/AT_abc257_f)

## ~~闲扯~~
	
 看到楼上几位巨佬用 dijkstra，发现自己太蒟了，于是和同学们一起想了 $2$ 小时，才用 bfs 写出来。
 
 ## 思路
 
 先用 vector 建图，然后我们可以通过一个新的节点（暂定为 $S_0$ ），将不确定的点连到 $S_0$ 上，接着分别从点 $S_1$ 和 点 $S_n$ 开始 bfs，算出各个点到 $S_1,S_n$ 的距离。
 
 到这里不难发现，答案只有 $3$ 种情况：
 1. $S_1 \sim  S_n$。
 2. $S_1 \sim  S_0 + S_i \sim S_n$ ( $i$ 为 $S_{1 \sim n}$ 中的一点)。
 3. $S_1 \sim  S_i + S_0 \sim S_n$ ( $i$ 为 $S_{1 \sim n}$ 中的一点)。

所以，对于第 $i$ 条边，取这三种情况中的最小值即可（注意输出 $-1$ ）。

## Code

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 5, maxv = 1e8;

struct node{
  int cnt, x;
};

int n, m, v[2][maxn]; //v[0][i]指S_1到S_i的距离，v[1][i]指S_n到S_i的距离
vector<int> a[maxn];
queue<node> q;

void record(bool flag, int x, int cnt){
  if(v[flag][x] != maxv){
    return ;
  }
  v[flag][x] = cnt;
  q.push({cnt, x});
}

void bfs(bool flag, int x){
  record(flag, x, 0);
  while(!q.empty()){
    node w = q.front();
    for(int i = 0; i < a[w.x].size(); i++){
      record(flag, a[w.x][i], w.cnt + 1);
    }
    q.pop();
  }
}

int main(){
  cin >> n >> m;
  fill(&v[0][0], &v[1][n + 1], maxv);
  for(int i = 1, u, v; i <= m; i++){
    cin >> u >> v;
    a[u].push_back(v);
    a[v].push_back(u);
  }
  bfs(0, 1), bfs(1, n);   
  for(int i = 1; i <= n; i++){
    cout << (min({v[0][n], v[0][0] + v[1][i], v[0][i] + v[1][0]}) == maxv ? -1 : min({v[0][n], v[0][0] + v[1][i], v[0][i] + v[1][0]})) << ' ';
  }
  return 0;
}
```



---

## 作者：Tsawke (赞：1)

# [[ABC257F] Teleporter Setting](https://www.luogu.com.cn/problem/AT_abc257_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC257F)

## 题面

存在 $ n $ 个小镇，$ m $ 条传送通道，第 $ i $ 条双向连结 $ u_i, v_i $ 两个小镇，经过每个传送通道需要花费 $ 1 $ 分钟。特别地，可能存在 $ u_i = 0 $，表示该条传送通道只规定了一端，另一端待定。存在 $ n $ 个独立询问，对于 $ i = 1, 2, \cdots, n $，钦定所有未确定的 $ u_i $ 均为 $ i $，求从小镇 $ 1 $ 到小镇 $ n $ 最小耗费的时间。若无法到达输出 $ -1 $。

## Solution

算是一道挺好的题。首先我们可以进行如下转化，对于所有 $ u_i = 0 $ 的边，我们将其连结到一个超级源点 $ S $ 上，不失一般性，设 $ S = 0 $，此时对于每次询问，我们仅需要对 $ S \rightarrow i $ 连边即可。当然我们肯定不能每次都算一遍，于是考虑发现，对于 $ 1 \rightarrow n $ 的路径，一共仅可能存在如下几种贡献：$ 1 \rightarrow n $，$ 1 \rightarrow S \rightarrow i \rightarrow n $，$ 1 \rightarrow i \rightarrow S \rightarrow n $，同时注意我们这里的箭头不是表示直接到达，而是表示最短路。所以以此不难发现，我们所需要维护的就只有 $ 1 $ 和 $ n $ 为源点的单源最短路，即可表示出来每次的值。然后每次在这些里取 $ \min $ 即可，记得判一下无解。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[610000];
ROPNEW(ed);
Edge* head[310000];

int N, M;
int dis1[310000], disn[310000];

void bfs1(void){
    memset(dis1, 0x3f, sizeof dis1);
    bitset < 310000 > vis; vis.reset();
    queue < int > cur; cur.push(1), vis[1] = true, dis1[1] = 0;
    while(!cur.empty()){
        int p = cur.front(); cur.pop();
        for(auto i = head[p]; i; i = i->nxt)
            if(!vis[SON])
                vis[SON] = true, dis1[SON] = dis1[p] + 1, cur.push(SON);
    }
}
void bfsn(void){
    memset(disn, 0x3f, sizeof disn);
    bitset < 310000 > vis; vis.reset();
    queue < int > cur; cur.push(N), vis[N] = true, disn[N] = 0;
    while(!cur.empty()){
        int p = cur.front(); cur.pop();
        for(auto i = head[p]; i; i = i->nxt)
            if(!vis[SON])
                vis[SON] = true, disn[SON] = disn[p] + 1, cur.push(SON);
    }
}

int main(){
    N = read(), M = read();
    for(int i = 1; i <= M; ++i){
        int s = read(), t = read();
        head[s] = new Edge{head[s], t};
        head[t] = new Edge{head[t], s};
    }bfs1(), bfsn();
    for(int i = 1; i <= N; ++i){
        int ans = min({dis1[N], dis1[0] + disn[i], dis1[i] + disn[0]});
        printf("%d%c", ans >= 0x3f3f3f3f ? -1 : ans, i == N ? '\n' : ' ');
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_09 初稿

---

## 作者：Robin_kool (赞：0)

大致想一下，发现最终对于每个 $i$，最短路要么不经过它，要么经过某一条未确定的边。

讲一下我一开始的错解：先求 $1$ 和 $n$ 开始的最短路，然后对于每个 $i$，判断是否经过以及先后 $0$ 和 $v$ 的先后顺序。

为啥是错的？因为初始的时候没有把 $0$ 考虑进去，可能会出现类似一条链和单独一个点的情况，这样预处理出来到这个单独的点的最短路会是极大值，而 $i$ 知道后可能会连通，就爆单了。

考虑把 $0$ 当做真实的一个点，那么对于把 $0$ 变成 $i$ 的限制等同于 $0$ 到 $i$ 有一条长度为 $0$ 的边，那么就好做了，简单判断即可。


```cpp
inline void dij(int dis[], int s){
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	for(int i = 0; i <= n + 1; ++ i) dis[i] = 1e9; dis[s] = 0; q.push(make_pair(0, s));
	while(!q.empty()){int u = q.top().second; q.pop(); for(int v : vec[u]) if(dis[v] > dis[u] + 1) dis[v] = dis[u] + 1, q.push(make_pair(dis[v], v));}
}
inline void solve(){
	n = read(), m = read();
	for(int i = 1, u, v; i <= m; ++ i) u = read(), v = read(), vec[u].push_back(v), vec[v].push_back(u); 
	dij(dis1, 1), dij(disn, n);
	for(int i = 1; i <= n; ++ i) write(min(min(dis1[0] + disn[i], dis1[i] + disn[0]), dis1[n]) >= 1e9 ? -1 : min(min(dis1[0] + disn[i], dis1[i] + disn[0]), dis1[n])), putchar(' ');
}
```

---

## 作者：xukehg (赞：0)

考虑建一个编号为 $0$ 的点，将所有不确定的边都连向这个点，而每次查询相当于从 $i$ 到 $0$ 连一条边权为 $0$ 的边。每次查询都跑一遍最短路肯定是不行的，考虑预处理。

对于一次查询，我们有三种选择：

1. 不加边时从 $1$ 到 $n$ 的最短路。 

2. 从 $1$ 到 $0$ 再到 $i$ 再到 $n$。

3. 从 $1$ 到 $i$ 再到 $0$ 再到 $n$。 

对于 $1$，我们可以预处理出单源最短路。

对于 $2$ 和 $3$，$1$ 到 $0$ 的最短路，$1$ 到 $i$ 的最短路，$n$ 到 $0$ 的最短路，$n$ 到 $i$ 的最短路，可以从 $1$ 跑一次单源最短路，再从 $n$ 跑一次单源最短路，而 $0$ 到 $i$ 距离为 $0$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MaxN = 300010,MaxM = 700010;

struct edge {
	int to, dis, next;
}e[MaxM];
int head[MaxN];
ll dis[MaxN],dis2[MaxN],cnt;
bool vis[MaxN],vis2[MaxN];
int n, m, s;
void add_edge( int u, int v, int d ) {
	e[++cnt].dis = d;
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}
struct node {
	int dis,pos;
	bool operator <( const node &x )const {
		return x.dis < dis;
	}
};
priority_queue<node> q;
void dijkstra(){
	dis[s] = 0;
	q.push((node){0,s});
	while(!q.empty()){
		node tmp = q.top();
		q.pop();
		int x = tmp.pos,d = tmp.dis;
		if(vis[x]) continue;
		vis[x] = 1;
		for(int i = head[x];i;i = e[i].next){
			int y = e[i].to;
			if(dis[y] > dis[x] + e[i].dis){
				dis[y] = dis[x] + e[i].dis;
				if(!vis[y])  q.push((node){dis[y],y});
			}
		}
	}
}
priority_queue<node> q2;
void dijkstra2(){
	dis2[s] = 0;
	q2.push((node){0,s});
	while(!q2.empty()){
		node tmp = q2.top();
		q2.pop();
		int x = tmp.pos, d = tmp.dis;
		if(vis2[x]) continue;
		vis2[x] = 1;
		for(int i = head[x];i;i = e[i].next){
			int y = e[i].to;
			if(dis2[y] > dis2[x] + e[i].dis){
				dis2[y] = dis2[x] + e[i].dis;
				if(!vis2[y]) q2.push((node){dis2[y],y});
			}
		}
	}
}
signed main() {
	cin >> n >> m;
	for(int i = 0;i < MaxN;++i) dis[i] = dis2[i] = 1e18;
	for(int i = 1;i <= m;++i) {
		int u,v;
		cin >> u >> v;
		add_edge(u,v,1);
		add_edge(v,u,1);
	}
	s = 1;
	dijkstra();
	s = n;
	dijkstra2();
	for (int i = 1;i <= n;i++){
		ll ans = dis[n];
		ans = min({ans,dis[0] + dis2[i],dis[i] + dis2[0]});
		if (ans >= 1e18) cout << -1 << " ";
		else cout << ans <<  " ";
	}
}

---

## 作者：jjy2023 (赞：0)

# [ABC257F] Teleporter Setting
## 题意：
存在 $ n $ 个小镇，$ m $ 条传送通道，第 $ i $ 条双向连结 $ u_i, v_i $ 两个小镇，经过每个传送通道需要花费 $ 1 $ 分钟。特别地，可能存在 $ u_i = 0 $，表示该条传送通道只规定了一端，另一端待定。存在 $ n $ 个独立询问，对于 $ i = 1, 2, \cdots, n $，钦定所有未确定的 $ u_i $ 均为 $ i $，求从小镇 $ 1 $ 到小镇 $ n $ 最小耗费的时间。若无法到达输出 $ -1 $。
## 思路：
dijkstra $+$ 堆优化，枚举每一轮的单源最短路，最后计算出结果。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,max1,ans;
int fa[300005];
struct node
{
	int u,len;
};
bool operator <(node x,node y)
{
	return x.len>y.len;
}
priority_queue<node> q;
int val[300005][3];
bool flag[300005];
vector<node> v[300005];
void dij(int ks,int k)
{
	for(int i=0;i<=n;i++) val[i][k]=1e9;
	memset(flag,0,sizeof(flag));
	val[ks][k]=0;
	while(q.size()) q.pop();
	q.push({ks,0});
	while(q.size())
	{
		node now=q.top();
		q.pop();
		if(flag[now.u]) continue;
		flag[now.u] = 1;
		for(int i=0;i<v[now.u].size();i++)
			if(!flag[v[now.u][i].u]&&val[now.u][k]+v[now.u][i].len<val[v[now.u][i].u][k])
			{
				val[v[now.u][i].u][k]=val[now.u][k]+v[now.u][i].len;
				q.push({v[now.u][i].u,val[v[now.u][i].u][k]});	
			}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;	
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back({y,1});
		v[y].push_back({x,1});
	}
	dij(1,0);
	dij(n,1);
	for(int i=1;i<=n;i++)
	{
		if((val[0][0]==1e9||val[i][1]==1e9)&&(val[0][1]==1e9||val[i][0]==1e9)&&val[1][1]==1e9) cout<<-1<<" ";
		else cout<<min(min(val[0][0]+val[i][1],val[0][1]+val[i][0]),val[n][0])<<" ";
	}
	return 0;	
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

很显然，对于将所有的 $u_i=0$ 变成 $k$，能影响最短路长度的方式只有经过 $k$。以 $1,n$ 为源点跑一遍单源最短路，如果对于一个节点 $i$ 从 $1$ 出发要通过 $j$ 这条边到达 $k$（第 $j$ 条边的 $u=0,v=i$），则最短路一定是 $dis_{i,0}+1$（$dis_{i,0}$ 表示以 $1$ 为源点，$dis_{i,1}$ 表示以 $n$ 为源点）。

现在就可以乱搞了。必须通过至少 $1$ 条 $u=0$ 的边经过 $k$ 到达 $n$ 有 $3$ 种情况，如：

1. $1$ 到 $x$ 到 $k$ 到 $n$。
2. $1$ 到 $k$ 到 $y$ 到 $n$。
3. $1$ 到 $x$ 到 $k$ 到 $y$ 到 $n$。

其分别的代价为：

1. $dis_{x,0}+1+dis_{k,1}$。
1. $dis_{k,0}+1+dis_{y,1}$。
1. $dis_{x,0}+2+dis_{y,n}$。

然后把这三种情况的最小代价和原本 $1$ 到 $n$ 的最短路取个最小值就是每个 $k$ 的答案。

## 代码

放个链接吧，理解了就能写出来，我写太恶心了。[Link](https://atcoder.jp/contests/abc257/submissions/46735922)

---

## 作者：linbaicheng2022 (赞：0)

## 思路

我们可以把不确定的点当成真实存在的 $0$ 号点，建边的时候就正常连即可。

然后我们来看一个样例：

```cpp
1 - 2 - 0
3 - 4 - 5
```

当我们把 $0$ 号点看成 $3$ 号点时，答案就是 $1$ 号点到 $0$ 号点的距离加上 $3$ 号点到 $5$ 号点的距离。

然后我们再看：

```cpp
1 - 2
0 - 3 - 4 - 5
```

当我们把 $0$ 号点看成 $2$ 号点时，答案就是 $1$ 号点到 $2$ 号点的距离加上 $0$ 号点到 $5$ 号点的距离。

注意还有一种用不到 $0$ 号点的情况：

```cpp
1 - 2 - 5
0 - 3 - 4
```

那么答案就是 $1$ 号点到 $5$ 号点的距离。

综上所述，对于每个将 $0$ 号点当成 $i$ 号点的方案，其答案为以上三种情况结果的最小值。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 1000010;
typedef pair <int, int> PII;

int n, m;
int h[N], e[N], ne[N]; 
int dis1[N], dis2[N], st[N];
int idx;

void add (int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dijkstra1 () { //最短路，求出 1 号点到每个点的距离
	memset (dis1, 0x3f, sizeof dis1);
	dis1[1] = 0;
	
	priority_queue <PII, vector <PII>, greater <PII> > p;
	p.push ({0, 1});
	
	while (!p.empty ()) {
		auto t = p.top ();
		p.pop ();
		
		int ver = t.second, dit = t.first;
		
		if (st[ver]) {
			continue;
		}
		
		st[ver] = true;
		for (int i = h[ver]; i != -1; i = ne[i]) {
			int j = e[i];
			if (dis1[j] > dit + 1) {
				dis1[j] = dit + 1;
				p.push ({dis1[j], j});
			}
		}
	}
}

void dijkstra2 () { //最短路，求出 N 号点到每个点的距离
	memset (dis2, 0x3f, sizeof dis2);
	memset (st, 0, sizeof st); //注意要把判断数组清空
	dis2[n] = 0;
	
	priority_queue <PII, vector <PII>, greater <PII> > p;
	p.push ({0, n});
	
	while (!p.empty ()) {
		auto t = p.top ();
		p.pop ();
		
		int ver = t.second, dit = t.first;
		
		if (st[ver]) {
			continue;
		}
		
		st[ver] = true;
		for (int i = h[ver]; i != -1; i = ne[i]) {
			int j = e[i];
			if (dis2[j] > dit + 1) {
				dis2[j] = dit + 1;
				p.push ({dis2[j], j});
			}
		}
	}
}

int main () {
	cin >> n >> m;
	memset (h, -1, sizeof h);
	
	while (m --) {
		int a, b;
		cin >> a >> b;
		add (a, b); //建边，而且是双向边
		add (b, a);
	}
	
	dijkstra1 ();
	dijkstra2 ();

	int ans = 0;
	for (int i = 1; i <= n; i ++) {
		ans = min ({dis1[n], dis1[0] + dis2[i], dis1[i] + dis2[0]});
      //dis1[i] 存 i 号点到 1 号点的距离
      //dis2[i] 存 i 号点到 N 号点的距离
		if (ans == 0x3f3f3f3f) cout << -1 << ' ';//如果没有答案
		else cout << ans << ' ';
	}
	return 0;
}

```

---

