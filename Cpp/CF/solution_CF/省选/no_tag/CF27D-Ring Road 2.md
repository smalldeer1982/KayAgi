# Ring Road 2

## 题目描述

It is well known that Berland has $ n $ cities, which form the Silver ring — cities $ i $ and $ i+1 $ ( $ 1<=i&lt;n $ ) are connected by a road, as well as the cities $ n $ and $ 1 $ . The goverment have decided to build $ m $ new roads. The list of the roads to build was prepared. Each road will connect two cities. Each road should be a curve which lies inside or outside the ring. New roads will have no common points with the ring (except the endpoints of the road).

Now the designers of the constructing plan wonder if it is possible to build the roads in such a way that no two roads intersect (note that the roads may intersect at their endpoints). If it is possible to do, which roads should be inside the ring, and which should be outside?

## 样例 #1

### 输入

```
4 2
1 3
2 4
```

### 输出

```
io
```

## 样例 #2

### 输入

```
6 3
1 3
3 5
5 1
```

### 输出

```
ooo
```

# 题解

## 作者：BqtMtsZDnlpsT (赞：6)

题解区的神仙们用的都是 2-sat /kel。

于是我这个菜鸡就用黑白染色过了。

$\large\text{Solution}$

1. 假设所有边都在环内侧，枚举两条边 $(a,b),(c,d)$ 是否相交。若相交，则说明这两条边要放在异侧（放在同侧必定相交），否则放同侧。

关于判断两条线段 $(a,b),(c,d)$ 是否相交：

![](https://z3.ax1x.com/2021/12/02/oYsPRf.png)

容易发现，若 $a,b$ 分别在 $(c,d)$ 构成的两段弧上，那么这两条线段相交。

具体的，我们保证 $a<b,c<d$，若 $c<a<d,b>d$ 或 $c<b<d,a<c$（因为在其中一个节点上相交不算，所以不是 $\le$），时两条线段相交。

2. 对于两条相交线段加边。

考虑对连出来的图黑白染色，黑色代表在环外加边，白色反之。

若原图不是二分图（无法黑白染色），说明必有两条相交线段在同侧，所以 `Impossible`。

否则成功。

代码：

```cpp
int n,m,hd[105],cnt,x[105],y[105];
int c[105];
struct E{
	int nxt,to;
}e[100005];
void add(int u,int v){
	e[++cnt]=(E){hd[u],v};
	hd[u]=cnt;
}
void dfs(int u,int fa){
	c[u]=c[fa]^1;
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			if(c[u]==c[v]){puts("Impossible");exit(0);}
			else if(c[v]!=0x3f3f3f3f)continue;
			dfs(v,u);
		}
	}
}
signed main(){
	memset(c,0x3f3f3f3f,sizeof c);//先把c设为没染过色的状态
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		x[i]=read(),y[i]=read();
		if(x[i]>y[i])swap(x[i],y[i]);
	}
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			if((x[i]>x[j]&&x[i]<y[j]&&y[i]>y[j])||(y[i]>x[j]&&y[i]<y[j]&&x[i]<x[j]))add(i,j),add(j,i);//判断相交
	c[0]=0;
	for(int i=1;i<=m;i++)
		if(c[i]==0x3f3f3f3f)dfs(i,0);//黑白染色
	for(int i=1;i<=m;i++)putchar(c[i]?'o':'i');//按定义输出
}

```

---

## 作者：jdsb (赞：3)

## 题意
- 给定 $n$ 个点，围成了一个环，又有 $m$ 条路径，路径可以建在环内或环外，求出一种合法方案，使得路径两两不相交（端点不算），如果无解输出 `Impossible`。
- $1\le n \le 100, 1\le m \le 100$

## 分析
- 如果两条路径对应区间为包含关系或者不相交，那么两条路径就互不影响，也就是说两条路径会影响，当且仅当两条路径有交且不是包含关系，我们就可以根据这个性质来建立约束关系。

- 考虑用 $2-SAT$ 算法来解决这个问题，如果还不知道这个算法可以先去做[P4782](https://www.luogu.com.cn/problem/P4782)。对于每条边，考虑只有两种情况，在环内和在环外，我们不妨将第 $i$ 条边的情况看成是变量 $X_i$ 的取值， $X_i=0$ 则说明在环内，$X_i=1$ 说明在环外。那么当任意两条边 $i$，$j$ 相交且不是包含关系时，我们就将 $X_i$ 与 $\lnot X_j$ 连边，$X_j$ 与 $\lnot X_i$ 连边（$\lnot$ 是逻辑符号非），第一句话含义就是当第 $i$ 条边在一侧时，则第 $j$ 条边一定在另一侧，这个命题的逆否命题也成立，即第二句话。

- 根据上面分析，我们就可以将图建出来，然后我们对这个图跑 $Tarjan$，求一下每个点所属的强连通分量，如果 $X_i$ 与 $\lnot X_i$ 在同一强联通分量中，那就不合法，输出 `Impossible`。简单证明一下，对于图中的一条边 $(x,y)$ 表示选 $x$ 则必选 $y$，那么处于同一个强联通分量的点则要么都选，要么都不选，如果 $X_i$ 和 $\lnot X_i$ 处于同一个强联通分量，那么肯定没有解。

- 对于输出方案，设 $bel[]$ 表示所属强连通分量标号，如果 $bel[X_i]<bel[\lnot X_i]$ ，就让这条边在环内，否则在环外，反着来也可以，因为边的情况全反是不影响的，这样一定能构造出合法方案。

## 代码
```cpp
#include<bits/stdc++.h>
#define fre(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
#define ll long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') { if(c=='-') f=-1;c=getchar(); }
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return x*f;
}
const int N=1e5+5;
vector<int>e[N];
struct node{
	int x,y;
}a[N];
int n,m;
inline void add(int x,int y) { e[x].push_back(y); }
inline int check(int x,int y){
	int l1=a[x].x,r1=a[x].y,l2=a[y].x,r2=a[y].y;
	return l1<l2&&r1>l2&&r1<r2||r1>r2&&l1>l2&&l1<r2;
}
int dfn[N],low[N],tim,st[N],top,ins[N],bel[N],B;
void tarjan(int x){
	dfn[x]=low[x]=++tim;
	ins[st[++top]=x]=1;
	for(auto y:e[x]){
		if(!dfn[y]) tarjan(y),low[x]=min(low[x],low[y]);
		else if(ins[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int y;B++;
		do{
			ins[y=st[top--]]=0;
			bel[y]=B;
		}while(x^y);
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		a[i]={read(),read()};
		if(a[i].y<a[i].x) swap(a[i].x,a[i].y);
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			if(check(i,j))
				add(i,j+m),add(i+m,j);
	for(int i=1;i<=m;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=m;i++) if(bel[i]==bel[i+m]) return puts("Impossible"),0;
	for(int i=1;i<=m;i++) (bel[i]<bel[i+m])?putchar('i'):putchar('o');
	return 0;
}
```


---

## 作者：registerGen (赞：3)

2-SAT 水题。

[可能更好的阅读体验](https://registergen.github.io/post/solution-cf27d/)

**Upd on 2020/09/15** 修改一处 typo。

# Solution

每条新边要么在环内，要么在环外，考虑 2-SAT。

于是，问题来了，**如何建图？**

首先不妨设 $a_i<b_i$。

考虑每对线段 $(i,j),1\le i\lt j\le n$。

- 若线段 $i,j$ 的四个端点有两个端点重合，则 $(i,j)$ 没有依赖关系（即随便选择）。
- 若线段 $i,j$ 分离或者 $i$ 包含 $j$ 或者 $j$ 包含 $i$，则 $(i,j)$ 没有依赖关系。
- 否则 $(i,j)$ 有依赖关系（即 $i$ 在环内 $\Rightarrow$ $j$ 在环外，$j$ 在环内 $\Rightarrow$ $i$ 在环外），此时 $i,j$ 相交。

以上部分如有不理解的地方，可以尝试画图去理解。

# Code

核心部分：

```cpp
inline bool check(int i,int j){
	int a1=a[i],b1=b[i],a2=a[j],b2=b[j];
	if(a1==a2||b1==b2||a2==b1||b2==a1)return 0; // 有两个端点重合
	if(b1<a2||b2<a1)return 0; // 线段 i,j 分离
	if(a1<a2&&b2<b1)return 0; // i 包含 j
	if(a2<a1&&b1<b2)return 0; // j 包含 i
	return 1;
}

// main()
scanf("%d%d",&n,&m);
for(int i=1;i<=m;i++){
    scanf("%d%d",a+i,b+i);
    if(a[i]>b[i])std::swap(a[i],b[i]);
}
```

---

## 作者：CQ_Bab (赞：2)

# 前言
其实这道题是可以不用 2-SAT 的但是我是从 2-SAT 题单中进来的所以还是使用了 2-SAT。
# 思路
其实可以发现对于一条边只可能出现两种情况在圈内和在圈外所以我们只需要想如何连边即可，首先判断出矛盾的情况，再连边最后跑一遍 Tarjan 即可。这里重点就在于如何判断矛盾情况，如下图就是矛盾情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/z3kbn5hv.png)

那么我们能得出结论如果两条边 $i$ 和 $j$ 矛盾，那么一定有 $x_i<x_j<y_i<y_j$ 或者 $x_j<x_i<y_j<y_i$ 这里只需要遍历 $i$ 和 $j$ 一遍和 $j$ 和 $i$ 一遍即可。

然后代码也就呼之欲出了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define pb push_back
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
pair<int,int>p[222];
/*
1~m 选
m+1~2*m 不选 
*/
int n,m;
vector<int>v[222];
int dfn[201],low[201],is[210];
stack<int>s;
int idx,val[210],cnt;
void tarjan(int x) {
	low[x]=dfn[x]=++idx;
	s.push(x);
	is[x]=1;
	for(auto to:v[x]) {
		if(!dfn[to]) tarjan(to),low[x]=min(low[x],low[to]);
		else if(is[to]) low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x]) {
		int p;
		cnt++;
		do{
			p=s.top();
			s.pop();
			is[p]=false;
			val[p]=cnt;
		} while(p!=x);
	} 
}
fire main() {
	in(n),in(m);
	rep(i,1,m) in(p[i].first),in(p[i].second);
	rep(i,1,m) if(p[i].first>p[i].second) swap(p[i].first,p[i].second);
	rep(i,1,m) {
		rep(j,1,m) {
			if(p[i].first<p[j].first&&p[i].second>p[j].first&&p[i].second<p[j].second&&p[j].first<p[i].second) {
				v[i].push_back(j+m);
				v[i+m].push_back(j);
				v[j].push_back(i+m);
				v[j+m].push_back(i);
			}
		}
	}
	rep(i,1,2*m) if(!dfn[i]) tarjan(i);
	rep(i,1,m) {
		if(val[i]==val[i+m]) {
			puts("Impossible");
			return false;
		}
	}
	rep(i,1,m) {
		if(val[i]<val[i+m]) cout<<'o';
		else cout<<'i';
	}
	return false;
}
/*
5 3
4 2
1 3
5 2
*/
```

---

## 作者：tZEROちゃん (赞：2)

你注意到你要加一条边，要么在外面，要么在里面。

那你考虑 2-SAT。考虑什么时候两条边会有约束。

你注意到，如果一个边完全覆盖了另一条，那不会有影响；如果两条边完全没有交集，那也没有影响。

显然，只有一种可能会产生约束，就是两条边恰好相交。

比如下面这个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/pvcod6w7.png)



你看，这个时候两条边是相交的，那显然 $X_i<X_j<Y_i<Y_j$，你把 $i, j$ 交换一下也同理。

那就是 2-SAT 板子了。无解要输出 `Impossible`，翻译没给。代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define _rep(i, l, r) for(auto i = (l); i < (r); ++i)

#define pb push_back
#define fi first
#define se second

#define i64 long long

const int N = 2e6 + 10;
vector<int> G[N];
int scc[N], dfn[N], low[N], DFN, SCC;
stack<int> stk; bool vi[N];

void tarjan(int u) {
  dfn[u] = low[u] = ++DFN;
  stk.push(u); vi[u] = 1;
  for (auto v : G[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (vi[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++SCC;
    while (stk.top() != u) {
      scc[stk.top()] = SCC; vi[stk.top()] = 0;
      stk.pop();
    }
    scc[stk.top()] = SCC, vi[stk.top()] = 0;
    stk.pop();
  }
}

int x[N], y[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m; cin >> n >> m;
  rep (i, 1, m) {
    cin >> x[i] >> y[i];
    if (x[i] > y[i]) swap(x[i], y[i]);
  }
  rep (i, 1, m) rep (j, 1, m) {
    bool ok = 0;
    if (x[i] < x[j] && x[j] < y[i] && y[i] < y[j]) ok = 1;
    if (x[j] < x[i] && x[i] < y[j] && y[j] < y[i]) ok = 1;
    if (ok) {
      G[i].pb(j + m); G[i + m].pb(j);
    }
  }  
  rep (i, 1, 2 * m) {
    if (!dfn[i]) tarjan(i);
  }
  rep (i, 1, m) if (scc[i] == scc[i + m]) {
    cout << "Impossible\n"; return 0;
  }
  rep (i, 1, m) {
    if (scc[i] > scc[i + m]) cout << 'i' ; else cout << 'o' ;
  }

  return ~~(0 ^ 0);
}
```

---

## 作者：漠寒 (赞：2)

## 什么是 SAT 问题

k-SAT：k-satisfiability，中文名叫“k-适应性问题”，它描述的是这样一类问题。


给你 $n$ 个变量 $a_i$，每个变量有 $a_i$ 种取值，称变量 $a_i$ 的取值集合为 $a_i$ 的值域。同时还有一些约束，例如当 $a_i$ 取它的值域里某个值时，$a_j$ 的值就不能为 $a_j$ 值域里的某个值。

问是否有一种取值方式满足所有的约束。

顾名思义，本题的 2-SAT 问题即为 k 为 $2$ 的情况。

## 分析

本题就是要找出哪些状态互相影响，如果两条路同向会相交，则设为冲突，每条边对应两个值，奇数为内圈，偶数为外圈，冲突则将内圈和另一边的外圈相连，视为必须同时存在。

判断好后就用 2-SAT 的最基本，最暴力的做法 dfs。

对于未选中的一边，先选上内圈，进行 dfs 观察是否矛盾，如果不矛盾就可以选它，否则，就换外圈再次尝试，如果二者皆矛盾，便说明无解。

矛盾指无法避免内圈外圈同时被选中，因为我们边的意思为“必须”。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,head[160001],xuan[160001],tot,timec,vis[160001];
struct node{
	int to,next;
}a[40001];
inline void read(int& res){
	res=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+c-48,c=getchar();}
}
inline void add(int qq,int mm){
	a[++tot].to=mm,a[tot].next=head[qq],head[qq]=tot;
}
bool dfs(int x){
	xuan[x]=1;
	vis[x]=timec;//当次访问到，timec为时间戳 
	int xx=x-1;
	if(x&1)xx+=2;//你当前要考虑选的这个边的这个方向的另一方向有无被选 
	if(xuan[xx]){
		xuan[x]=0;
		return false;
	}
	for(register int i=head[x];i;i=a[i].next){
		if(vis[a[i].to]!=timec){
			if(!dfs(a[i].to)){//它选后必须要选这个，但是它却回答你不可以，所以就失败 
				for(register int j=head[x];j!=i;j=a[j].next)xuan[a[j].to]=0;
				xuan[a[i].to]=0;
				return false;
			}
		}
	}
	return true;
}
struct noe{
	int l,r;
}c[105];
bool check(int i,int j){
	int a1=c[i].l,b1=c[i].r,a2=c[j].l,b2=c[j].r;
	if(a1==a2||b1==b2||a2==b1||b2==a1)return 0;//端点相重合 
	if(b1<a2||b2<a1)return 0;//碰都碰不到 
	if(a1<a2&&b2<b1)return 0;
	if(a2<a1&&b1<b2)return 0;//包含关系 
	return 1;//冲突 
}
int main()
{
	read(n);
	read(m);
	int x,y;
	for(register int i=1;i<=m;++i){
		read(c[i].l);read(c[i].r);
		if(c[i].l>c[i].r)swap(c[i].l,c[i].r);
	}
	for(int i=1;i<=m;i++){
		for(int j=i+1;j<=m;j++){
			if(check(i,j)){//互异的方向相连 
				add(i*2,j*2-1);
				add(i*2-1,j*2);
				add(j*2,i*2-1);
				add(j*2-1,i*2);
			}
			
		}
	}
	for(register int i=1;i<=m;++i){
		timec++;
		if(xuan[i*2-1]&&xuan[i*2]){//内外都被前面的被迫选了 
			cout<<"Impossible"<<endl;
			return 0;
		}
		int bo=0;
		if(xuan[i*2-1]||xuan[i*2]){//已经有只选了一个方向 
			bo=1;
		}
		if(bo==0){
			if(dfs(i*2-1))bo=1;//先跑内圈 
			if(bo==0){//内圈不行 
				timec++;
				xuan[i*2-1]=0;
				if(!dfs(i*2)){
					cout<<"Impossible"<<endl;//内外都不行 
					return 0;
				}
			}
		}
	}
	for(register int i=1;i<=m*2;++i){
		if(xuan[i]){
			if(i&1)cout<<'o';//好像o是外圈？不过这并不影响做题 
			else cout<<'i';
		}
	}
}
```


---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/CF27D)

挺经典的题，是 [P3209 [HNOI2010] 平面图判定](https://www.luogu.com.cn/problem/P3209) 的无限弱化版。

考虑连边只会有两种情况，一种是连接的边在环内，一种是连接的边在环外，不妨定义在环内取 $1$，在环外取 $0$。

如果两条边同时连在环内或者同时在环外有相交的话，这时候就出现矛盾了，很显然，如果其中任意一条边取 $1$ 的话，那么剩下那条边就必须取 $0$。

这就是一个很经典的 $a \oplus b$ 的格式了吧，对于这个我们当然可以考虑用 2-SAT 直接解决。

但是对于这种格式，我们同样可以通过二分图染色的方式进行解决，对于有矛盾的两条边直接对他们的编号连无向边，边的含义就是两端点不能同时颜色相同，钦定开始为 $1$ 进行二分图染色，如果矛盾则无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e5+10;
vector<int> g[N<<1];
int n,m,c[N],vis[N],U[N],V[N],cal[N],flag;
bool vis1[N][3];
stack<int> sta;
void Add(int u,int v){
	g[u].push_back(v),g[v].push_back(u);
}
void color(int u,int col){
	vis[u]=1,c[u]=col;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(c[v]!=0&&c[v]!=-col)	flag=false;
		if(c[v]==0)	color(v,-col);
	}
}
int main()
{
	flag=true;
	cin>>n>>m;
	for(int i=1;i<=m;i++)	cin>>U[i]>>V[i];
	for(int i=1;i<=m;i++)	if(U[i]>V[i])	swap(U[i],V[i]);
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++){
			if(i==j)	continue;
			if(U[i]==U[j]||V[i]==V[j])	continue;
			if((U[i]<U[j]&&V[i]>U[j]&&V[i]<V[j])||(U[i]>U[j]&&U[i]<V[j]&&V[i]>V[j]))	Add(i,j);
		}
	for(int i=1;i<=2*m-1;i++)	if(!vis[i])	color(i,1);
	if(flag==false)	cout<<"Impossible"<<endl;
	else{
		for(int i=1;i<=m;i++)	cout<<((c[i]==1)?"o":"i");
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：1)

历时 1h 才做出来的水题。

一条边有两种状态，在环外连或者在环内连，想到 2-SAT。

设 $i$ 为第 $i$ 条边连在环内，$i + m$ 为第 $i$ 条边连在环外。

数据范围很小，考虑 $m^2$ 枚举边判断两条边选同一种连接的方案是否会相交。

分为以下几种情况：

**下面所说的区间都是开区间（~~当然如果你先判的第一种情况就无所谓了~~）。**

* 当前 $j$ 的两个端点有其中一个与 $i$ 的其中一个端点重合，不难看出选同一种连接方案的时候，两条边可以不相交。

* 当前 $j$ 的一个端点包含在 $i$ 的两个端点的区间内，若另一个端点不在 $i$ 的区间内，那么这两条边选同一种方案一定是会相交的，所以两个其中一个确定了连接方案，另一个就要强制选另一种： $i\to j',j' \to i, i' \to j, j \to i'$。

* 当前 $j$ 的一个端点包含在 $i$ 的两个端点的区间外，若另一个端点在 $i$ 的区间内，那么这两条边选同一种方案也会相交，所以我们和上面那种情况一样连边。

对了这题无解要输出 `Impossible`。

```cpp

/*
 * @Author: Aisaka_Taiga
 * @Date: 2023-09-29 08:10:40
 * @LastEditTime: 2023-09-29 08:30:25
 * @LastEditors: Aisaka_Taiga
 * @FilePath: \Desktop\CF27D.cpp
 * The heart is higher than the sky, and life is thinner than paper.
 */
#include <bits/stdc++.h>

#define int long long
#define N 1000100

using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char s = getchar();
    while(s < '0' || s > '9'){if(s == '-') f = -1; s = getchar();}
    while(s <= '9' && s >= '0') x = (x << 1) + (x << 3) + (s ^ 48), s = getchar();
    return x * f;
}

int n, m, cnt, head[N], low[N], dfn[N], sd[N], stk[N], top, tim, scc, U[N], V[N], vis[N];
struct node{int u, v, next;}e[N << 1];

inline void add(int u, int v){e[++ cnt] = (node){u, v, head[u]}; head[u] = cnt;}

inline void Add(int u, int v)
{
    // cout << u << "   " << v << endl;
    add(u, v + m);
    add(v + m, u);
    add(u + m, v);
    add(v, u + m);
    return ;
}

inline int pd(int x, int y)
{
    if(U[y] > U[x] && U[y] < V[x])
    {
        if(V[y] >= U[x] && V[y] <= V[x]) return 0;
        else return 1;
    }
    else if(U[y] == U[x] || U[y] == V[x]) return 0;
    else if(V[y] == U[x] || V[y] == V[x]) return 0;
    else
    {
        if(V[y] > U[x] && V[y] < V[x]) return 1;
        else return 0;
    }
}

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ top] = u;
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if(vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        int y; scc++;
        while(1)
        {
            y = stk[top --];
            sd[y] = scc;
            vis[y] = 0;
            if(u == y) break;
        }
    }
    return ;
}

signed main()
{
    n = read(); m = read();
    for(int i = 1; i <= m; i ++)
    {
        U[i] = read(), V[i] = read();
        if(U[i] > V[i]) swap(U[i], V[i]);
    }
    for(int i = 1; i <= m; i ++)
        for(int j = i + 1; j <= m; j ++)
            if(pd(i, j)) Add(i, j);
    int ff = 0;
    for(int i = 1; i <= 2 * m; i ++)
        if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= m; i ++)
        if(sd[i] == sd[i + m]) ff = 1;
    if(ff == 1) return cout << "Impossible" << endl, 0;
    for(int i = 1; i <= m; i ++)
    {
        if(sd[i] < sd[i + m]) cout << "i";
        else cout << "o";
    }
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

肯定可以用扩展域并查集飞过去。你愿意写 2-SAT 我也不拦着。

如果两条路有交集，那他们肯定不能同时放在里面或外面。因此我们使用扩展与并查集的老套路：$i$ 表示 $i$ 在内，$i+m$ 表示 $i$ 在外。

如果道路 $i,j$ 有交集，就将 $i,j+m$ 和 $i+m,j$ 两对分别合并。最后如果 $i,i+m$ 在同一堆就无解，否则有解。

有解的话可以通过 $find(i)<find(i+m)$ 来人为指定内外圈。

如果你用 2-SAT 的话就只需要把平时的单向限制改成双向限制就行了。

扩展域并查集核心代码如下：

```cpp
signed main() {
	ios::sync_with_stdio(0);
	n = io.read(); m = io.read();
	for (int i = 1;i <= m;++i)
		l[i] = io.read(), r[i] = io.read(),
		f[i] = i, f[i + m] = i + m;
	for (int i = 1;i <= m;++i)
		for (int j = 1;j <= m;++j)
			if (inter(l[i], r[i], l[j], r[j]))
				f[find(i)] = find(j + m),
				f[find(j)] = find(i + m);
	for (int i = 1;i <= m;++i)
		if (find(i) == find(i + m))
			return puts("Impossible") & 0;
	for (int i = 1;i <= m;++i)
		io.push(find(i) < find(i + m) ? 'i' : 'o');
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 题意

有一个环，环上有 $n$ 个节点，你可以在环内加一条边，也可以在环外。

请你求出一种方案是的线段都不相交。

无解输出``Impossible``。

## 思路

使用 **2-SAT**，枚举 $i$ 和 $j$，如果 $(x_i,y_i)$ 和 $(x_j,y_j)$ 相交，即:
$$
a_i < a_j < b_i < b_j 
$$
 那么就让 $i \rightarrow j'$，$j \rightarrow i'$，$i' \rightarrow j$，$j'\rightarrow i$。

 然后跑一遍 Tarjan。

 最后判断 $scc_i$ 和 $scc_{i'}$ 是否相同，相同则无解。

 ## 代码

 
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep( i , l , r ) for (int i = (l) ; i <= (r) ; i++)
#define per( i , r , l ) for (int i = (r) ; i >= (l) ; i--)

int n , m ;
int a[110] , b[110] ;
int dfn[16010] ;
int tot ;
int low[16010] ;
struct node{
	int to , nxt;
}g[320010] ;
int head[160010] ;
void add (int u , int v){
	g[++tot] = (node){v , head[u]} ;
	head[u] = tot ;
}
int cnt ;
int stk[16018] ;
int tp ;
int scc[16010] ;
int num ; 
bool instk[16010] ;
void tarjan (int u){
	low[u] = dfn[u] = ++cnt ;
	stk[++tp] = u ;
	instk[u] = 1;
	for (int i = head[u] ; i ; i = g[i].nxt){
		int v = g[i].to ;
		if (!dfn[v]){
			tarjan (v) ;
			low[u] = min (low[u] , low[v]) ;
		}else if (instk[v] == 1){
			low[u] = min (low[u] , dfn[v]) ;
		}
	}
	if (low[u] == dfn[u]){
		++num ;
		int tmp ;
		while (stk[tp] != u){
			tmp = stk[tp--] ;
			scc[tmp] = num ;
			instk[tmp] = 0 ;
		}
		tmp = stk[tp--] ;
		scc[tmp] = num ;
		instk[tmp] = 0 ;
	}
}
void solve (){
	cin >> n >> m ;
	rep (i , 1 , m){
		cin >> a[i] >> b[i] ;
		((a[i] > b[i]) ? swap(a[i] , b[i]) : (swap (a[i] , a[i])) );	
	}
	rep (i , 1 , m){
		rep (j , 1 , m){
			if (a[i] < a[j] && b[i] > a[j] && b[i] < b[j] && a[j] < b[i]){
				add (i , j + m) ;
				add (j , i + m);
				add (j + m , i) ;
				add (i + m , j) ;
			}
		}
	}
	rep (i , 1 ,  2 * m){
		if (!dfn[i]){
			tarjan (i) ;
		}
	}
	rep (i , 1 , m){
		if (scc[i] == scc[i + m]){
			cout << "Impossible" ;
			return ;
		}
	}
	rep (i , 1 , m){
		cout <<( (scc[i] < scc[i + m]) ? 'o' : 'i' );
	}
}
 
signed main (){
	int _ = 1 ;
	//cin >> _ ;
	while ( _-- ){solve () ;}
	return 0 ;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

有一个圆，圆上有着 $n$ 个点，将圆周平均分成了 $n$ 段圆弧；然后给定 $m$ 条边 $(a_i, b_i)$，可以建在圆内（即弦），也可以建在圆外；请构造一种方案使得这些边两两不交（端点除外）。

$n, m \le 100$。

### 思路：

首先容易发现，若两条边同时在圆内是相交的，那么同时放在圆外也是相交的。

那么考虑对于若 $i$ 与 $j$ 这两条边若是相交的，故必须一条边放圆内，一条边放圆外（诶，那这不是二分图染色问题吗，但是这里是 2-SAT 学习日记qwq）。

令 $x_i$ 表示 $i$ 这条边是否放圆外，就可以直接用 2-SAT 做。

现在我们来考虑一下什么情况下 $(x_i, y_i)$ 与 $(x_j, y_j)$ 这两条边是相交的（先钦定 $\forall k, x_k < y_k$），容易得到：

- $x_i < x_j < y_i < y_j$。

- $x_j < x_i < y_j < y_i$。

故时间复杂度为 $O(m^2)$。

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
const int N = 205;
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
int n, m, cnt, top, ccnt;
int a[N], b[N], dfn[N], low[N], stk[N], scc[N];
bool f[N];
vector<int> E[N];
inline void add(int u, int v){
	E[u].push_back(v);
}
inline void tarjan(int u){
	dfn[u] = low[u] = ++cnt;
	stk[++top] = u;
	f[u] = 1;
	for(auto v : E[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(f[v])
		  low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]){
		++ccnt;
		while(1){
			int x = stk[top--];
			scc[x] = ccnt;
			f[x] = 0;
			if(x == u)
			  break;
		}
	}
}
bool End;
int main(){
	n = read(), m = read();
	for(int i = 1; i <= m; ++i){
		a[i] = read(), b[i] = read();
		if(a[i] > b[i])
		  swap(a[i], b[i]);
	}
	for(int i = 1; i <= m; ++i){
		for(int j = 1; j <= m; ++j){
			if(i == j)
			  continue;
			if((a[i] < a[j] && a[j] < b[i] && b[i] < b[j]) || (a[j] < a[i] && a[i] < b[j] && b[j] < b[i])){
				add(i, j + m);
				add(i + m, j);
			}
		}
	}
	for(int i = 1; i <= 2 * m; ++i)
	  if(!dfn[i])
	    tarjan(i);
	for(int i = 1; i <= m; ++i){
		if(scc[i] == scc[i + m]){
			puts("Impossible");
			exit(0);
		}
	}
	
	for(int i = 1; i <= m; ++i){
		if(scc[i] > scc[i + m])
		  putchar('i');
		else
		  putchar('o');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：hlsnqdmz (赞：0)

才学了 [2-SAT](https://www.luogu.com.cn/problem/P4782) 所以拿这道题来练手，感觉其实没有紫题难度？

说一下大概题意（小小吐槽一下翻译，连 `Impossible` 都没翻译出来，不过对比起 $\LaTeX$ 都出错的题干，不知道哪个更离谱），有 $n$ 个点，$m$ 条边，边可以在环内和环外，求有无一种让边都不相交的方式，若有，则输出其中一种，每条边若在环内，输出 `i`，在环外，输出 `o`；若无，输出 `Impossible`。  
看完题干，我们发现，对于每条边有两种选择：在环内和在环外，所以可以尝试使用 2-SAT 来解决。对于相交的边，不能同时在环内或环外（因为都会相交），所以只能一条在环内，一条在环外。

那这样我们只要建图，跑 `tarjan` 再正常输出就行了，但问题在于如何判断要连边。  
我们知道，连的边都是相交的边（废话），那么只要把相交的边找出来就可以连边（大废话），而判断边相交并不算难，我们知道环上点的值可以想象成按顺时针递增直到 $n$ 为止，也可以想象成逆时针（大大废话），那就像下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/v56i521m.png)

我们设第 $i$ 条边的两个端点为 $a_i,b_i(a_i<b_i)$，当然这里要注意，输入的第一个数不一定小于第二个数。我们假设边的编号依次是 $1\to 4,2\to 5,6\to 8,5\to 7$，观察前两条边，我们发现：$a_1<a_2<b_1<b_2$；观察后两条边我们发现：$a_4<a_3<b_4<b_3$。那么对于两条边 $i,j$，我们发现它们相交时满足 $a_i<a_j<b_i<b_j$ 或 $a_j<a_i<b_j<b_i$ 然后我们循环枚举两个边，满足条件就连边，而连的边就是一个代表在环内连向另一个代表在环外的点，反之亦然。

最后贴出丑陋的代码：
```
//Just Sayori
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>
#define ll long long
#define rnt register int
#define gr getchar
#define pr putchar
#define N 500005
#define M 1000000007
using namespace std;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = gr();
    while (ch < '0' || ch > '9')
        ch == '-' ? f = -1, ch = gr() : ch = gr();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch ^ 48), ch = gr();
    return x * f;
}

inline void write(ll x)
{
    static int sta[39], top = 0;
    if (x < 0)
        pr('-'), x = -x;
    do
        sta[++top] = x % 10, x /= 10;
    while (x);
    while (top)
        pr(sta[top--] ^ 48);
}

struct edge
{
    int v, next;
} e[N];
int head[N], cnt;

inline void add(int u, int v)
{
    e[++cnt] = {v, head[u]}, head[u] = cnt;
}

int n, m, c, k, x, y, bcc, top;
int a[N], b[N], dfn[N], low[N], num[N], sum[N], vis[N], stack[N];

void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    vis[u] = 1, stack[++top] = u;
    for (rnt i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        bcc++;
        while (stack[top + 1] != u)
            num[stack[top]] = bcc, vis[stack[top--]] = 0;
    }
}

int main()
{
    int n = read(), m = read();
    for (rnt i = 1; i <= m; i++)
        a[i] = read(), b[i] = read(), a[i] > b[i] ? swap(a[i], b[i]) : void();
    for (rnt i = 2; i <= m; i++)
        for (rnt j = 1; j < i; j++)
            if ((a[i] < a[j] && a[j] < b[i] && b[i] < b[j]) || (a[j] < a[i] && a[i] < b[j] && b[j] < b[i]))
                add(i, j + m), add(i + m, j), add(j, i + m), add(j + m, i);//这里不会重复枚举，所以建四条边。
    for (rnt i = 1; i <= 2 * m; i++)
        if (!dfn[i])
            tarjan(i);
    for (rnt i = 1; i <= m; i++)
        if (num[i] == num[i + m])
            return puts("Impossible"), 0;
    for (rnt i = 1; i <= m; i++)
        cout << (num[i] < num[i + m] ? 'i' : 'o');
    return 0;
}
```
### 感谢您的观看！

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：

将边建立成点，然后对于所有的不能同时放到一边（内侧或者外侧）的点（也就是建图前的边，下同）连一条边。

可以发现，所有的有边连接的点都是不可以在同一侧的，那么就是一个黑白染色的基本模型，直接做就好了。

如果出现了无法染色的情况，那么无解，否则将随便将黑白中的一色设置为内侧，另一色设置为外侧就行了。

---
从另一个角度考虑，将放在外侧设置为 $1$，内侧为 $0$，“如果一个点选择了 $1$，那么另一个点就必须选择 $0$”这样的建模其实也可以转换为 $\text{2-SET}$ 问题来求解，不过似乎要比前一种复杂一点。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2000005;
int n,m,x[MAXN],y[MAXN],head[MAXN],nxt[MAXN],num[MAXN],tot,col[MAXN],flag;
void add(int x,int y){
	nxt[++tot]=head[x];head[x]=tot;num[tot]=y;
}
void dfs(int now,int colour){
	col[now]=colour;
	for(int i=head[now];i;i=nxt[i]){
		if(col[num[i]]==0)dfs(num[i],-1*colour);
		if(col[num[i]]==colour)flag=1;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++)
		if(i!=j){
			if(min(x[i],y[i])<min(x[j],y[j])
			&&min(x[j],y[j])<max(x[i],y[i])&&
			min(x[j],y[j])<max(x[i],y[i])&&
			max(x[i],y[i])<max(x[j],y[j]))
			add(i,j),add(j,i);
		}
	}
	for(int i=1;i<=m;i++)
	if(col[i]==0)dfs(i,1);
	if(flag){
		printf("Impossible\n");
		return 0;
	}
	for(int i=1;i<=m;i++){
		if(col[i]==1)printf("o");
		else printf("i");
	}
	printf("\n");
	return 0;
}
```


---

## 作者：_anll_ (赞：0)

## 题目大意
给你 $n$ 个点，本身已成环，你要连 $m$ 条边，可以连在环内或环外，问你是否有连法让任意两条线之间不相交。如果没有，请输出 ` Impossible`。否则请输出任意一种连边方案。

## 大体思路
~~既然本蒟蒻都可以不看题解切出来，那思路一定是很简单的。~~

首先，先分析一下这道题在考什么。对于 $i$ 和 $j$ 两条边来说，如果相交，我们肯定要让它俩在异侧。即如果 $i$ 在内侧，$j$ 就在外侧，反之亦然。从 $i$ 的状态推到 $j$ 的状态是不是很熟悉？是的，这是 2-SAT 问题。

如果你不知道 2-SAT 是什么，可以去[P4782 【模板】2-SAT](https://www.luogu.com.cn/problem/P4782)，也可以查看这篇蒟蒻写的[学习笔记](https://www.luogu.com.cn/blog/is-saliang-awa/post-2-sat)。

知道了它在考察什么，剩下的就好办得多了。首先，对于相交的处理，先看一眼 $m$ 的范围，很小，我们大可以暴力枚举。我们知道，对于一条边 $i$，它会把圆分成两块。不妨先对这两块进行染色，之后枚举剩下的边 $j$，如果它的两个端点对应的颜色不同且不是 $i$ 的端点，那就说明会相交，需要去用 2-SAT 的思想为 $i$ 和 $j$ 建边。

剩下的内容就是很板的 2-SAT 了，不在此赘述。

## 代码演示
大体思路就是这样，如果还有不清楚的地方，可以结合代码理解。
```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
struct Edge{
    int l,nxt;
}edges[2005];
int n,m,tt=1,head[205],vu[205];
int tot,dfn[205],low[205];
int top,instk[205],stk[205];
int cnt,scc[205];
pair<int,int> po[205];
string s;
void add_edge(int f,int l){
    tt+=1;
    edges[tt]={l,head[f]};
    head[f]=tt;
}
void tarjian(int x){
    tot+=1,top+=1;
    dfn[x]=low[x]=tot;
    stk[top]=x,instk[x]=1;
    for(int i=head[x];i;i=edges[i].nxt){
        int l=edges[i].l;
        if(!low[l]){
            tarjian(l);
            low[x]=min(low[x],low[l]);
        }
        else if(instk[l]) low[x]=min(low[x],dfn[l]);
    }
    if(dfn[x]==low[x]){
        int y;cnt+=1;
        do{
            y=stk[top],top-=1,instk[y]=0;
            scc[y]=cnt;
        }while(y!=x);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>po[i].first>>po[i].second;
    for(int i=1;i<=m;i++){
        memset(vu,0,sizeof(vu));
        int a=po[i].first,b=po[i].second;
        for(int i=min(a,b);i<=max(a,b);i++) //进行染色
            vu[i]=1;
        for(int j=i+1;j<=m;j++){
            if(i==j) continue;
            int c=po[j].first,d=po[j].second;
            if(vu[c]!=vu[d]&&c!=a&&d!=a&&c!=b&&d!=b){ //如果相交
                add_edge(i,j+m);add_edge(j,i+m);
                add_edge(i+m,j);add_edge(j+m,i); //分别枚举i/j在内/外侧的情况
            }
        }
    }
    for(int i=1;i<=m*2;i++) if(!low[i]) tarjian(i);
    for(int i=1;i<=m;i++){
        if(scc[i]==scc[i+m]){
            cout<<"Impossible"<<endl;
            return 0;
        }
        else if(scc[i]<scc[i+m]) s+='i';
        else s+='o';
    }
    cout<<s;
    return 0;
}
```


---

