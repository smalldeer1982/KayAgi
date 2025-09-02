# [BalticOI 2020] 图 (Day2)

## 题目描述

你有一个无向图，每条边都有一种颜色：红或者黑。

你要做的就是为每个节点配一个实数点权，使得：

- 对于每条黑色边，两个端点的点权之和为 $1$
- 对于每条红色边，两个端点的点权之和为 $2$
- 所有点权的绝对值之和是最小的

求一种点权的分配方案。

## 说明/提示

#### 评测方式

您的输出被评判为正确，当且仅当：

- 每条边所连两点的点权和与该边要求的点权间的误差不超过 $10^{-6}$。
- 所有点权的绝对值之和与标准答案误差不超过 $10^{-6}$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$N \le 5$，$M \le 14$。     
- Subtask 2（12 pts）：$N \le 100$。
- Subtask 3（17 pts）：$N \le 1000$。
- Subtask 4（24 pts）：$N \le 10^4$。
- Subtask 5（42 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N \le 10^5$，$0 \le M \le 2 \times 10^5$。

**本题使用 Special Judge。**

## 样例 #1

### 输入

```
4 4
1 2 1
2 3 2
1 3 2
3 4 1```

### 输出

```
YES
0.5 0.5 1.5 -0.5
```

## 样例 #2

### 输入

```
2 1
1 2 1
```

### 输出

```
YES
0.3 0.7```

## 样例 #3

### 输入

```
3 2
1 2 2
2 3 2
```

### 输出

```
YES
0 2 0```

## 样例 #4

### 输入

```
3 4
1 2 2
2 2 1
2 1 1
1 2 2
```

### 输出

```
NO```

# 题解

## 作者：Purslane (赞：3)

## Solution

图论 ( ? ) 

考虑一个联通块里 , 如果确定一个数 , 那可以推导出其他所有的数 .

类似染色 , 这一个块中的第一个数设为 $x$ , 其他数推导出 $\pm x+k_i$ . 

当然我们会访问到一个已经确定过的点 , 设为 $k_1 x + b_1$ , 而现在应该是 $k_2 x + b_2$ . 分类讨论 .

- $k_1 = k_2$ 且 $b_1 = b_2$ . 没有用是不是 . 直接 return .
- $k_1 = k_2$ 且 $b_1 \neq b_2$ . 显然无解 . 输出 `NO` .
- $k_1 \neq k_2$ . 可以解出 $x = -\frac{b_1 - b_2}{k_1-k_2}$ .

但我们有可能解不出来 $x$ . 然后化简就可以发现要求 $\sum |x-c_i|$ 的最小值 . 小学奥数题 , $x$ 为 $\{c\}$ 的中位数 .

注意 , 我们解出的 $x$ 可能不是合法解 . 回带的过程中看一下有没有矛盾 .

code :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+20;
int n,m,flg,vis[MAXN],Vis[MAXN],k[MAXN],b[MAXN];
long double x,val[MAXN];
vector<pair<int,int>> G[MAXN];
vector<int> tmp;
void calc(int u,int K,int B) { //u:val=Kx+B
	if(vis[u]) {
		if(K==k[u]&&B!=b[u]) {cout<<"NO";exit(0);}
		if(K==k[u]&&B==b[u]) return ;
		flg=1,x=(b[u]-B)*1.0/(K-k[u]);
		return ;
	}
	vis[u]=1,k[u]=K,b[u]=B,tmp.push_back(-b[u]*k[u]);
	for(auto t:G[u]) {
		int to=t.first,w=t.second;
		calc(to,-K,w-B);
	}
	return ;
}
void fill(int u,long double x) {
	if(Vis[u]&&abs(x-val[u])>1e-7) {cout<<"NO";exit(0);}
	if(Vis[u]) return;
	val[u]=x,Vis[u]=1;
	for(auto t:G[u]) {
		int to=t.first,w=t.second;
		fill(to,w-x);
	}
	return ;
} 
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {
		int a,b,c;cin>>a>>b>>c;
		G[a].push_back({b,c}),G[b].push_back({a,c});
	} 
	ffor(i,1,n) if(vis[i]==0) {
		flg=0,k[i]=1,b[i]=0,tmp.clear();
		calc(i,1,0);
		if(!flg) {
			sort(tmp.begin(),tmp.end());
			x=tmp[tmp.size()/2];
		}
		fill(i,x);
	}
	cout<<"YES\n";
	ffor(i,1,n) cout<<fixed<<setprecision(15)<<val[i]<<' ';
	return 0;
}
```

PKUSC RP++ ! ( 垫底去喽 )

---

## 作者：Fuyuki (赞：3)

假定原图是个连通图，如果不是，则对每个连通块分别处理即可。

如果有一个点的权值被确定了，那么可以通过这个点的权值可以推出其他所有点的权值。

换言之，设其中一个点的权值为 $x$，其他所有点都可以表示成以 $x$ 为自变量的一个一次函数，并且一次项的系数为 $\pm1$。

如果原图存在奇环，那么必定会存在一条边使得该边的两个端点的一次函数相加之后一次项系数不为 $0$，这时就可以计算出 $x$ 的值，并以此计算出每个点的权值。

如果不存在奇环，那么所有 $x$ 的取值都是合法的，问题转化成需要找一个 $x$ 使得这些一次函数的绝对值 $\sum |x-c_i|$ 最小，~~（保序回归）~~ 找到 $c$ 的中位数即可。

根据找中位数的方法不同可以在 $O(n+m)$ 或 $O(nlogn+m)$ 的时间内解决本题。

这里给出的是 $O(nlogn+m)$ 的实现。

~~把 sort 换成 nth_element 可以去掉 log，但我懒得改了）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ld double
#define I inline int
#define V inline void
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define REP(u) for(int i=h[u],v;v=e[i].t,i;i=e[i].n)
const int N=2e5+1;
ld now,ans[N];
int n,m,tot,flag;
int h[N],tmp[N],dfn[N];
struct edge{int t,n,w;}e[N<<1];
struct node{
	int x,v;
	ld val(){return now*x+v;}
	node operator+(const node&u)const{return(node){x+u.x,v+u.v};}
	node operator-(const node&u)const{return(node){x-u.x,v-u.v};}
}f[N],val[3];
V test(int x){if(!x)printf("NO\n"),exit(0);}
V add_edge(int x,int y,int w){
	e[++tot]=(edge){y,h[x],w},h[x]=tot;
	e[++tot]=(edge){x,h[y],w},h[y]=tot;
}
V input(){
	scanf("%d%d",&n,&m);
	for(int x,y,w;m--;add_edge(x,y,w))scanf("%d%d%d",&x,&y,&w);
}
V init(){FOR(i,1,2)val[i].v=i;}
V dfs1(int u){
	dfn[u]=1;
	REP(u)
		if(dfn[v]==0)f[v]=val[e[i].w]-f[u],dfs1(v);
		else if(f[u].x+f[v].x==0)test(f[u].v+f[v].v==e[i].w);
		else{
			ld x=1.*(e[i].w-f[u].v-f[v].v)/(f[u].x+f[v].x);
			if(flag)test(abs(x-now)<=1e-6);
			else now=x,flag=1;
		}
	tmp[++tot]=-f[u].x*f[u].v;
}
V dfs2(int u){
	dfn[u]=2,ans[u]=f[u].val();
	REP(u)if(dfn[v]==1)dfs2(v);
}
V work(){
	FOR(i,1,n)if(!dfn[i]){
		flag=tot=0,dfn[i]=1,f[i].x=1,dfs1(i);
		if(!flag)sort(tmp+1,tmp+1+tot),now=tmp[tot+1>>1];
		dfs2(i);
	}
	printf("YES\n");
	FOR(i,1,n)printf("%.2lf ",ans[i]);
}
int main(){
	input();
	init();
	work();
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

## 题意回顾

$ n $ 个点 $ m $ 条边的边带权无向图，要求每条边的边权等于两点点权的和且点权绝对值的和最小，请设计一种赋权方案。

**开启 SPJ**，$ 1 \le n \le 10^5 $，$ 0 \le m \le 2 \times 10^5 $。

## 分析

对于不同的连通块，显然这些点的取值无关，即我们只需要独立求解每个连通块即可。

对于每个未被访问的连通块，我们设一个结点的值为 $ x $，则由这些数量关系可以表示出每个连通块内结点为 $ k_ix+b_i $（$ k \in  \{-1,1\} $）的形式，即这个连通块答案可以表示为 $ \sum_{u \in \text{BLOCK}} |x-\frac{b_u}{-k_u}| $，用绝对值的几何意义求出 $ x $ 取 $ \frac{b_u}{-k_u} $ 的中位数的情况下答案最小。

注意特殊情况：

* 如果一个点可以被表示为不同的形式的话，因为图不是森林这种情况有可能发生，解方程解出 $ x $ 的值直接返回即可。
* 如果方程无解，输出 `NO`。
* 连通块填数的时候注意再次检查结果是否正确。

为了方便实现减少浮点数的使用，可以考虑将边权 $ \times 2 $ 之后用整形储存，因为绝对值方程参数的中位数和解方程得到的 $ x $ 值都是 $ \frac{k}{2}(k \in \mathbb{Z}) $ 的形式。

## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define wzj pair<int, int>
using namespace std;
const int N = 1e5 + 5;
const int inf = 1e9 + 5;
int n, m;
vector<wzj> g[N];
vector<int> blo;
struct node {
    int opt;
    int val;
} d[N];
int lwhzkj[N];
node operator-(int p1, node p2) {
    return (node){-p2.opt, p1 - p2.val};
}
bool ok = true;
int tp = -inf;
void solve(int u) {
    blo.push_back(-d[u].val / d[u].opt);
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        int w = g[u][i].second;
        if(d[v].opt == 0) {
            d[v] = w - d[u];
            solve(v);
        } else {
            node dv = w - d[u];
            if(dv.opt != d[v].opt) tp = (d[v].val - dv.val) / (dv.opt - d[v].opt);
            else if(dv.val != d[v].val) ok = false;
        }
    }
}
void color(int u) {
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        int w = g[u][i].second;
        if(lwhzkj[v] == inf) {
            lwhzkj[v] = w - lwhzkj[u];
            color(v);
        } else {
            if(w - lwhzkj[u] != lwhzkj[v]) ok = false;
        }
    }
}
void output_num(int x) {
    if(x < 0) printf("-"), x = -x;
    if(x % 2 == 0) printf("%d", x / 2);
    else printf("%d.5", x / 2);
}
int main() {
    scanf("%d%d", &n, &m);
    int u, v, w;
    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        w *= 2;
        g[u].push_back((wzj){v, w});
        g[v].push_back((wzj){u, w});
    }
    for(int i = 1; i <= n; i++) lwhzkj[i] = inf;
    for(int i = 1; i <= n; i++) {
        if(d[i].opt == 0) {
            tp = inf;
            blo.clear();
            d[i].opt = 1, d[i].val = 0;
            solve(i);
            if(ok) {
                if(tp == inf) {
                    sort(blo.begin(), blo.end());
                    int mididt = (int)blo.size() / 2;
                    tp = blo[mididt];
                }
                lwhzkj[i] = tp;
                color(i);
            }
        }
    }
    if(!ok) puts("NO");
    else {
        puts("YES");
        for(int i = 1; i <= n; i++) output_num(lwhzkj[i]), printf(" ");
        puts("");
    }
    return 0;
}
```

---

## 作者：xuyuesen (赞：0)

# P6696 图
这道题很奇妙。\
在一个连通图中，从任意一个起点开始，设其点权为 $ x $ ，则其他节点的点权均可以以 $k\times x +b$ 的形式表示。\
则可以从任意起点开始，令起点点权为 $x$，表示出其他节点的点权，由于这个图可能有环，可以在遇到跑过的节点时判断是否成立，可以分讨（设两个表达式分别为 $k_1\times x + b_1$ 和 $k_2\times x + b_2$ ）：
- 若 $k_1 = k_2$ 且 $b_1 = b_2$ ：无穷组解，跳过
- 若 $k_1 = k_2$ 且 $b_1 \ne b_2$ ：无解，结束程序
- 若 $k_1 \ne k_2$ 再判断：
  1. 若之前已经求出 $x$ ，判断 $\frac{ b_2 -b_1 }{ k_1 - k_2 }$ 与 $x$是否相等，不等则结束程序。
  2. 若之前未求出 $x$ ，则直接使 $ x = \frac{ b_2 -b_1 }{ k_1 - k_2 }$
   
最后求出了 $ x $ 之后，将经过的节点的点权算出来，若有矛盾也结束程序。  
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const db eps=1e-7;
int hd[100005],to[400005],nxt[400005],ln[400005],tot;
int u,v,w;
int n,m;
bool vis[100005];
bool vis2[100005];
struct nd{
	db a,b;
}a[100005];
db x;
bool hv;
db ans[100005];
vector<int>vec;
void add(int u,int v,int w){
	nxt[++tot]=hd[u];
	hd[u]=tot;
	to[tot]=v;
	ln[tot]=w;
}
bool get(nd t,nd u,db an){
	if(fabs(u.a-t.a)<eps)return fabs(u.b-t.b)<eps;	
	db an_=(u.b-t.b)/(t.a-u.a);
	return fabs(an-an_)<eps;
}
void dfs(int u,int f){
	vis[u]=1;
	vec.push_back(-a[u].b/a[u].a);
	for(int i=hd[u];i;i=nxt[i]){
		if(to[i]==f)continue;
		if(vis[to[i]]){
			nd t;
			t.a=-a[u].a;
			t.b=ln[i]-a[u].b;
			if(hv){
				if(!get(t,a[to[i]],x)){//unequal
					cout<<"NO";
					exit(0);
				}
			}else{				
				if(a[to[i]].b==t.b&&a[to[i]].a==t.a)continue;//inf
				if(a[to[i]].a==t.a&&a[to[i]].b!=t.b){//none
					cout<<"NO";
					exit(0);
				}	
				x=(a[to[i]].b-t.b)/(t.a-a[to[i]].a);
				hv=1;
			}
		}else{
			a[to[i]]={-a[u].a,1.0*ln[i]-a[u].b};
			dfs(to[i],u);
		}
	}
}
void dfs2(int u,int f,db x){
	vis2[u]=1;
	ans[u]=a[u].a*x+a[u].b;
	for(int i=hd[u];i;i=nxt[i]){
		if(to[i]==f)continue;
		if(vis2[to[i]]){
			if(fabs(a[to[i]].a*x+a[to[i]].b-ans[to[i]])>eps){
				cout<<"NO";
				exit(0);
			}
			continue;
		}		
		dfs2(to[i],u,x);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	x=-1;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vec.clear();
			hv=0;
			a[i].a=1;
			a[i].b=0;
			dfs(i,0);
			if(!hv){
				sort(vec.begin(),vec.end());
				x=vec[vec.size()>>1];
			}
			dfs2(i,0,x);
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
}
```

---

