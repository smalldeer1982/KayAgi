# Paint the Tree

## 题目描述

You are given a tree consisting of $ n $ vertices. A tree is an undirected connected acyclic graph.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1244D/0b019d9da08990633b2a6779b2699db8afb883d7.png)Example of a tree.You have to paint each vertex into one of three colors. For each vertex, you know the cost of painting it in every color.

You have to paint the vertices so that any path consisting of exactly three distinct vertices does not contain any vertices with equal colors. In other words, let's consider all triples $ (x, y, z) $ such that $ x \neq y, y \neq z, x \neq z $ , $ x $ is connected by an edge with $ y $ , and $ y $ is connected by an edge with $ z $ . The colours of $ x $ , $ y $ and $ z $ should be pairwise distinct. Let's call a painting which meets this condition good.

You have to calculate the minimum cost of a good painting and find one of the optimal paintings. If there is no good painting, report about it.

## 说明/提示

All vertices should be painted in different colors in the first example. The optimal way to do it is to paint the first vertex into color $ 1 $ , the second vertex — into color $ 3 $ , and the third vertex — into color $ 2 $ . The cost of this painting is $ 3 + 2 + 1 = 6 $ .

## 样例 #1

### 输入

```
3
3 2 3
4 3 2
3 1 3
1 2
2 3
```

### 输出

```
6
1 3 2 
```

## 样例 #2

### 输入

```
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 4
```

### 输出

```
9
1 3 2 1 3 
```

# 题解

## 作者：installb (赞：13)

updated 2019.11.10 之前笔误了  

首先这题的条件就在于 一棵树上任意两个距离$\leq2$的点颜色不同 并且只有三种颜色  

那么如果存一个点$u$ 有三个点与$u$相连 这三个点颜色就必须**两两不同**  
然后这三个点就把三种颜色取完了  
然后$u$就没办法取颜色了 这样就无解  

于是 只要存在任意一个节点的**度数**$\geq3$就无解  

然后我们发现这棵树是条链  

再看这个链 任意三个相连的节点都需要两两颜色不同  
所以任意三个相连的节点只要确定了两个 第三个就确定了 就可以一步一步推下去了  
一开始就随便找一条边 与这条边相连的两个点分别枚举选什么颜色(这两个点颜色不能相同) 然后一步一步往外推 记录下六种情况下答案最小的情况 就可以了  

放个图吧 好理解  

确定过程(枚举$col1$和$col2$ 这里随便找一条边都行 我找了$(4,5)$这条边)  
![](https://cdn.luogu.com.cn/upload/image_hosting/y3xzwi30.png)  
下面是无解情况  
![](https://cdn.luogu.com.cn/upload/image_hosting/4j5kt6gg.png)  

记录下每个点在这种情况下(枚举6种情况)标记成什么颜色 然后直接全部加起来 统计答案  

这是考场代码 我都是直接dfs的 其实不用 ~~但反正复杂度对的 无所谓~~  
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;
typedef long long LL;
 
LL n,m,k;
LL c[4][800005] = {0};
LL ans = 0;
string s;
 
LL ec = 0,to[800005],nxt[800005],hed[200005] = {0};
LL deg[400005] = {0};
void add_edge(LL f,LL t){
	++ ec; to[ec] = t; nxt[ec] = hed[f]; hed[f] = ec;
	deg[t] ++;
}
 
LL col[200005] = {0};
LL rec[200005] = {0};
 
LL chg(LL x,LL y){
	return 6 - x - y; // 小技巧 根据另外两点颜色确定该点颜色
}
 
void dfs(LL u,LL f,LL uc,LL fc){ // 标记颜色
	for(LL i = hed[u];i;i = nxt[i]){
		LL v = to[i];
		if(v == f) continue;
		col[v] = chg(uc,fc);
		dfs(v,u,col[v],uc);
	}
}
 
int main(){
	LL a,b;
	ios::sync_with_stdio(false);
	cin >> n;
	for(LL i = 1;i <= n;i ++) cin >> c[1][i];
	for(LL i = 1;i <= n;i ++) cin >> c[2][i];
	for(LL i = 1;i <= n;i ++) cin >> c[3][i];
	
	for(LL i = 1;i < n;i ++){
		cin >> a >> b;
		add_edge(a,b);
		add_edge(b,a);
	}
	
	for(LL i = 1;i <= n;i ++){
		if(deg[i] >= 3){
			cout << -1 << endl;
			return 0;
		}
	}
	LL ans = 0x3f3f3f3f3f3f3f3f;
	for(LL c1 = 1;c1 <= 3;c1 ++){
		for(LL c2 = 1;c2 <= 3;c2 ++){
			if(c1 == c2) continue;
			col[a] = c1; col[b] = c2; // 随便找一条边 枚举
         // 我在这里直接用了最后输入的那条边
			dfs(a,b,c1,c2);
			dfs(b,a,c2,c1);
        // 注意要从两个点两个方向 都要dfs 
			LL cnt = 0;
			for(LL i = 1;i <= n;i ++) cnt += c[col[i]][i];
			if(cnt < ans){
				ans = cnt;
				for(LL i = 1;i <= n;i ++) rec[i] = col[i]; // 记录答案
			}
		}
	}
	cout << ans << endl;
	for(LL i = 1;i <= n;i ++) cout << rec[i] << (i == n ? '\n' : ' '); 
	return 0;
}
```
顺带一提 这场CF的D比C还简单

---

## 作者：woshishei (赞：7)

题目要求对于任意的三个点$x,y,z$，满足$x$与$y$直接相连，$y$与$z$直接相连，则$x,y,z$的颜色两两不同。

对于任意四个点$a,b,c,d$，满足$a$与$b$直接相连，$a$与$c$直接相连，$a$与$d$直接相连，则$a,b,c$的颜色两两不同，$a,c,d$的颜色两两不同，$a,b,d$的颜色两两不同，则$a,b,c,d$的颜色两两不同。但是一共只有三种颜色，所以只要有四个点满足上述情况，就一定无解。换句话说**只要有一个点的度大于2**（大于2条边与该点相连）**，则一定无解。**

所以，要使题目有解，这棵树**必须是一条链**。

然后，从头到尾重新标记为$1,2,3,...,n$（$1$，$n$为链的断点）。染色情况只有六种（数字代表颜色）：

- $1,2,3,1,2,3,1,2,3,...$
- $1,3,2,1,3,2,1,3,2,...$
- $2,1,3,2,1,3,2,1,3,...$
- $2,3,1,2,3,1,2,3,1,...$
- $3,1,2,3,1,2,3,1,2,...$
- $3,2,1,3,2,1,3,2,1,...$

对于每种情况，记录答案。

时间复杂度$\Theta(n)$。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#define debug printf("\n-------------\n")
using namespace std;
typedef long long ll;
vector<int> adj[100010];//建立邻接表
bool vis[100010];
int n,d[100010],pos,a[100010],p[5]={0,0,1,2},tmp[100010],ans[100010];//p为颜色的排列，d为每个点的度，a为链上的每一个点的编号
ll c[3][100010],sum,mi=(1ll<<62);
int main()
{
	scanf("%d",&n);
	for(int i=0;i<=2;i++)
		for(int j=1;j<=n;j++)
			scanf("%I64d",&c[i][j]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		d[u]++;
		d[v]++;//记录顶点的度，对于每一条边，两个端点的度分别加一
		adj[u].push_back(v);
		adj[v].push_back(u);//连边
	}
	for(int i=1;i<=n;i++)
		if(d[i]>2)//如果点的度大于2，则无解
		{
			printf("-1");
			return 0;
		}
		else if(d[i]==1)//以度为1的点作为端点
			pos=i;
	a[1]=pos;
	vis[pos]=true;
	for(int i=2;i<=n;i++)
		for(int j=0;j<adj[a[i-1]].size();j++)
		{
			int v=adj[a[i-1]][j];
			if(!vis[v])
			{
				vis[v]=true;
				a[i]=v;
			}
		}//构造链
	do
	{
		sum=0;
		for(int i=1;i<=n;i++)
		{
			tmp[a[i]]=p[(i-1)%3+1]+1;//链上的第i个节点（编号为a[i]）标为相应的颜色
			sum+=c[p[(i-1)%3+1]][a[i]];//计入花费
		}
		if(sum<mi)//更新答案
		{
			mi=sum;
			memcpy(ans,tmp,sizeof(tmp));
		}
	}while(next_permutation(p+1,p+4));//枚举颜色的排列
	printf("%I64d\n",mi);
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：AutumnKite (赞：5)

显然，如果要满足题目中的条件，那么一个点的度数一定不能超过 $2$。

所以满足条件的树一定是一条链。

可以发现，只要确定链上前三个点的颜色，就可以确定整条链的颜色。

于是 $3!$ 枚举前三个点的颜色，取最小值即可。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(long long x){
	if (x == 0) return putchar('0'), void(0);
	int cnt = 0, d[25];
	for (x < 0 ? x = -x, putchar('-') : 0; x; x /= 10) d[++cnt] = x % 10;
	while (cnt) putchar(d[cnt] ^ '0'), --cnt;
}
#define N 100005
int n, c[3][N], p[N], id[3], ansid[3], col[N];
std :: vector<int> E[N];
long long ans;
int main(){
	n = read();
	for (register int i = 0; i < 3; ++i)
		for (register int j = 1; j <= n; ++j)
			c[i][j] = read();
	for (register int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	for (register int i = 1; i <= n; ++i)
		if (E[i].size() > 2) return puts("-1"), 0;
	for (register int i = 1; i <= n; ++i)
		if (E[i].size() == 1){ p[1] = i; break; }
	for (register int i = 2; i <= n; ++i)
		for (int v : E[p[i - 1]]) if (v != p[i - 2]) p[i] = v;
	for (register int i = 0; i < 3; ++i) id[i] = i;
	ans = 1e18;
	while (1){
		long long s = 0;
		for (register int i = 1; i <= n; ++i) s += c[id[i % 3]][p[i]];
		if (s < ans) ans = s, memcpy(ansid, id, sizeof ansid);
		if (!std :: next_permutation(id, id + 3)) break;
	}
	for (register int i = 1; i <= n; ++i) col[p[i]] = ansid[i % 3] + 1;
	print(ans), putchar('\n');
	for (register int i = 1; i <= n; ++i) print(col[i]), putchar(' ');
}
```

---

## 作者：__phiu (赞：4)

## Pro
给出一棵树，给每个点染色有一定代价，只有三种颜色，相邻三个节点颜色不能相同。

## Sol

诈骗题。

第一眼以为是个比较困难的题，但想一下会发现一个性质：有解的情况一定是一条链。

证明：当一个点的度数大于等于三的时候，相邻的点把颜色取光，这个点就没有能取的颜色了。

所以可以直接枚举链的前三个或者前两个点的颜色，后面的就全部确定了。

时间复杂度是 $\mathcal{O}(n)$ 的。

## Code

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define For(i,a,b,c) for(int i=a;i<=b;i+=c)
#define Rof(i,a,b,c) for(int i=a;i>=b;i-=c)
#define pb push_back
#define pii pair<int,int>
using namespace std;
inline int read(){
	char c=getchar();
	int x=0,f=1;
	while(c<'0' or c>'9'){
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0' and c<='9')
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N = 1e5 + 5;
int a[N][10] ;
vector<int>v[N] ;
int fa[N] ;
int son[N] ;
int root ;
void dfs(int x,int f) {
	fa[x] = f ;
	for(auto to : v[x]) {
		if(to==f) continue;
		son[x] = to ;
		dfs(to,x) ;
	}
	return ;
}
int col[N];
long long ans=1e18;
int n;
int tmp[N] ;
void calc(){
	int now = son[son[son[root]]] ;
	while(now) {
		col[now] = 6 - col[fa[now]] - col[fa[fa[now]]] ;
		now = son[now] ;
	}
	long long res =  0;
	for(int i=1;i<=n;i++) {
		res += a[i][col[i]] ;
	}
	if(ans > res) 
		for(int i=1;i<=n;i++) tmp[i] = col[i] ;
	ans = min(ans , res) ;
	return ;
}
signed main(){
	n=read();
	for(int i=1;i<=3;i++) for(int j=1;j<=n;j++) a[j][i] = read() ;
	for(int i=1;i<n;i++) {
		int x=read(),y=read();
		v[x].pb(y),v[y].pb(x) ;
	}
//	bool flag = false ;
	root = 0 ;
	for(int i=1;i<=n;i++) {
		if(v[i].size() >=3 ){
			puts("-1");
			return 0;
		}
		if(v[i].size() == 1) root = i ;
	}
	dfs(root,0);
	for(int i=1;i<=3;i++) {
		for(int j=1;j<=3;j++) {
			for(int k=1;k<=3;k++) {
				if(i==j || j==k || i==k) continue ;
				col[root] = i , col[son[root]] = j , col[son[son[root]]] = k;
				calc() ;
			}
		}
	}
	printf("%lld\n",ans) ;
	for(int i=1;i<=n;i++) {
		printf("%d ",tmp[i]) ;
	}
	return 0;
}
```



---

## 作者：SIGSEGV (赞：3)

观察可得如果能够成功染色，那么**任何一个点的度数都不能超过3**

那么，这个树就是一条链......
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n,c[4][N],deg[N];
vector<int> e[N];
long long val[4][4];
int out[N];
long long dfs(int pos,int fa,int l1,int l2) //第一遍搜答案
{
    for (int i = 1;i <= 3;i++)
        if (i != l1 && i != l2)
        {
            if (e[pos].size() == 1) return c[i][pos];
            int nxt = e[pos][0];
            if (nxt == fa) nxt = e[pos][1];
            return c[i][pos] + dfs(nxt,pos,i,l1);
        }
    throw;
}
void print(int pos,int fa,int l1,int l2) //第二遍"打印"答案
{
    for (int i = 1;i <= 3;i++)
        if (i != l1 && i != l2)
        {
            out[pos] = i;
            if (e[pos].size() == 1) return;
            int nxt = e[pos][0];
            if (nxt == fa) nxt = e[pos][1];
            return print(nxt,pos,i,l1);
        }
}
int main ()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1;i <= 3;i++)
        for (int j = 1;j <= n;j++) cin >> c[i][j];
    int t1,t2;
    for (int i = 1;i < n;i++)
    {
        cin >> t1 >> t2;++deg[t1];++deg[t2];
        e[t1].push_back(t2);e[t2].push_back(t1);
    }
    int pos = 0,cnt = 0;
    for (int i = 1;i <= n;i++)
        if (deg[i] == 1) ++cnt,pos = i;
        else if (deg[i] > 2) {cout << -1 << endl;return 0;}
    if (cnt != 2) {cout << -1 << endl;return 0;}
    int nxt = e[pos][0],nn = nxt;
    if (e[nxt][0] == pos) nxt = e[nxt][1];else nxt = e[nxt][0];//获取链上的前2个点
    long long ans = LLONG_MAX;
    for (int i = 1;i <= 3;i++)
        for (int j = 1;j <= 3;j++)
            if (i != j)
                ans = min(ans,
                val[i][j] = dfs(nxt,nn,i,j) + c[j][pos] + c[i][nn]);//枚举前2个染什么，后面的都是确定的
    for (int i = 1;i <= 3 && !out[1];i++)
        for (int j = 1;j <= 3;j++)
            if (i != j && ans == val[i][j])
            {
                cout << ans << endl;
                out[pos] = j;out[nn] = i;
                print(nxt,nn,i,j);
                break;
            }
    for (int i = 1;i <= n;i++) cout << out[i] << ' ';
    return 0;
}
```

---

## 作者：Llf0703 (赞：2)

[更好的阅读体验](https://llf0703.com/p/cf-1244.html#dpaintthetree)

### 题意

用 $3$ 种颜色给一棵 $n(\le 10^5)$ 个点的树染色，每个点染不同的颜色有不同的代价。要求由任意 $3$ 个点组成的链上颜色都不相同，求代价的最小值。

### 题解

可以发现如果不是链就无解。

证明：从树的直径出发，如果染了前两个点，那么直径上后面的颜色都是确定的。如果不是链的话那一定会有分叉，假设形如下图，其中 `a--b--c` 是直径：

```
a--b--c
   |
   d
```

`a` 和 `c` 的颜色一定不同，所以 `d` 不管染什么颜色都不满足题解。

所以就枚举前两个点的颜色，依次遍历链上每一个点即可。

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

inline int read()
{
    char ch=getchar(); int f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

const int N=100005;
struct Edge {
    int next,to;
} edge[N<<1];
vector <int> v;
ll ans=1e18;
int n,a,b,cnt,head[N],c[4][N],deg[N],colRes[N],colAns[N];

inline void add(int u,int v)
{
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}

signed main()
{
    n=read();
    for (int i=1;i<=3;i++) for (int j=1;j<=n;j++) c[i][j]=read();
    for (int i=1;i<n;i++)
    {
        a=read(); b=read();
        add(a,b); add(b,a);
        deg[a]++; deg[b]++;
    }
    for (int i=1;i<=n;i++) if (deg[i]==1) v.push_back(i);
    if (v.size()!=2) return 0&puts("-1"); //不是链则无解
    int x=v[0],y; //链上的一端
    y=edge[head[x]].to; //第二个点
    for (int j=1;j<=3;j++) //第一个点染的颜色
    {
        for (int k=1;k<=3;k++) //第二个点的颜色
        {
            if (j==k) continue;
            colRes[x]=j; colRes[y]=k;
            ll res=c[j][x]+c[k][y]; //当前答案
            int cur=y,fa=x,last1=j,last2=k; //当前点，父节点，前两个点的颜色
            for (int i=3;i<=n;i++)
            {
                int nxt;
                for (int p=head[cur];p;p=edge[p].next) if ((nxt=edge[p].to)!=fa) break; //nxt 是下一个点
                fa=cur; cur=nxt;
                int col=1; for (;col==last1 || col==last2;col++); //找到符合要求的颜色
                res+=c[col][cur];
                colRes[cur]=col;
                last1=last2; last2=col;
            }
            if (res<ans) //更新答案
            {
                ans=res;
                memcpy(colAns,colRes,sizeof(colRes));
            }
        }
    }
    printf("%lld\n",ans);
    for (int i=1;i<=n;i++) printf("%d ",colAns[i]);
    return 0;
}
```

---

## 作者：xukuan (赞：2)

这次比赛的四道可做题（ABDG）之一

我们发现，当且仅当原图是一条链的时候才有解。

如果有解，那么涂色有6种方式，分别计算即可

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
const ll N=100010,INF64 = 0x7f7f7f7f7f7f7f7f;
using namespace std;
 
ll n, colour[N],c[N][4], f[N][4][4];
ll g[N][4][4];
vector<ll> e[N], q;
 
inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}
 
void dfs(ll u, ll before) {
    q.push_back(u);
    for(ll i=0; i<e[u].size(); i++){
    	ll v=e[u][i];
        if (v == before) continue;
        dfs(v, u);
    }
}
int main() {
    n=read();
    for (ll i = 1; i <= 3; i++) {
        for (ll j = 1; j <= n; j++) c[j][i]=read();
    }
    for (ll i = 1; i < n; i++) {
        ll u=read(),v=read();
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (ll i = 1; i <= n; i++) {
        if (e[i].size() > 2u) return printf("-1\n"), 0;
    }
    ll root = 0;
    for (ll i = 1; i <= n; i++) {
        if (e[i].size() == 1u) root = i;
    }
    q.push_back(0);
    dfs(root, 0);
    memset(f, 0x7f, sizeof(f));
    for (ll i = 1; i <= 3; i++) {
        for (ll j = 1; j <= 3; j++) {
            if (i == j) continue;
            f[2][i][j] = c[q[2]][i] + c[q[1]][j];
        }
    }
    for (ll i = 3; i <= n; i++) {
        ll x = q[i];
        for (ll j = 1; j <= 3; j++) {
            for (ll k = 1; k <= 3; k++) {
                if (j == k) continue;
                for (ll l = 1; l <= 3; l++) {
                    if (l == j || l == k) continue;
                    if (f[i - 1][k][l] == INF64) continue;
                    if (f[i - 1][k][l] + c[x][j] < f[i][j][k]) {
                        f[i][j][k] = f[i - 1][k][l] + c[x][j];
                        g[i][j][k] = l;
                    }
                }
            }
        }
    }
    long long ans = INF64;
    ll x = 0, y = 0;
    for (ll i = 1; i <= 3; i++) {
        for (ll j = 1; j <= 3; j++) {
            if (i != j && f[n][i][j] < ans) {
                ans = f[n][i][j];
                x = i, y = j;
            }
        }
    }
    printf("%I64d\n", ans);
    for (ll i = n; i >= 1; i--) {
        colour[q[i]] = x;
        ll z = g[i][x][y];
        x = y, y = z;
    }
    for (ll i = 1; i <= n; i++) printf("%d ", colour[i]);
    return 0;
}
```

---

## 作者：菲斯斯夫斯基 (赞：1)

## CF1244D Paint the Tree 题解

~~一眼 dp。~~

错误的，虽然感觉是 dp，但实际上不是。

**题意**

给你一棵树，给树的每个节点染上 $3$ 种颜色中的 $1$ 种，要求相邻的 $3$ 的节点颜色相同，每个节点涂不同的颜色有不同的花费，求最小花费及任意方案。无解输出 `-1`。

**题意**

不难发现只有当树是一条**链**是才能有解。因为当一个节点有 $3$ 个儿子的时候，必定有 $2$ 个颜色相同。

问题简单了许多。以为是 dp，但发现无法转移。事实上发现把问题想复杂了，只要将前面 $3$ 个节点的颜色确定了，那么后面的节点的颜色就确定了。

将问题转化为一列数。

仔细想想，若当前为 $i$ 节点（$i\ge4$），那么 $i$ 节点的颜色不能与 $i-1$ 号 和 $i-2$ 节点相同，那只能与 $i-3$ 号节点相同了。

于是暴力枚举前 $3$ 个节点的颜色，一次求出每个节点的颜色并取最小值即可。

注意：本题需要使用 `long long`，以及需要注意转化为一列数之后每个节点对应的编号。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,l,ans=1e18;
int c[N][4],id[N],f[N][4],p[N],t[N];
vector<int>v[N];
void dfs(int x,int fa)
{
	id[++l]=x,t[x]=l;
	for(int i=0;i<v[x].size();i++)
	{
		int to=v[x][i];
		if(to==fa)continue;
		dfs(to,x);
	}
}
signed main()
{
	cin>>n;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=n;j++)
			cin>>c[j][i];
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	int st=0;
	for(int i=1;i<=n;i++)
	{
		if(v[i].size()>=3)
		{
			cout<<-1;
			return 0;
		}
		if(v[i].size()==1)
			st=i;
	}
	dfs(st,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=3;j++)
			f[i][j]=c[id[i]][j];
	for(int a=1;a<=3;a++)
	for(int b=1;b<=3;b++)
	for(int c=1;c<=3;c++)
	{
		if(a==b||b==c||a==c)continue;
		int sum=0;
		p[1]=a,p[2]=b,p[3]=c,sum=f[1][a]+f[2][b]+f[3][c];
		for(int j=4;j<=n;j++)
			p[j]=p[j-3],sum+=f[j][p[j]];
		ans=min(ans,sum);
	}
	cout<<ans<<endl;
	for(int a=1;a<=3;a++)
	for(int b=1;b<=3;b++)
	for(int c=1;c<=3;c++)
	{
		if(a==b||b==c||a==c)continue;
		int sum=0;
		p[1]=a,p[2]=b,p[3]=c,sum=f[1][a]+f[2][b]+f[3][c];
		for(int j=4;j<=n;j++)
			p[j]=p[j-3],sum+=f[j][p[j]];
		if(sum==ans)
		{
			for(int j=1;j<=n;j++)
				cout<<p[t[j]]<<' ';
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：zombie462 (赞：1)

显然的，如果一个点的度大于$2$，无解。

证明：

设一个点$a$的度为$3$，连接的三个点分别为$x$，$y$，$z$

则：$a$，$x$，$y$两两异色，$a$，$y$，$z$两两异色，但是只有$3$种颜色，并不存在一种方案满足条件（若满足前者，则满足不了$z$与$a$，$x$，$y$都异色）。

所以整个树就是一条链。

然后就能线性递推了。只要枚举前两个点的颜色就行了。

时间复杂度：$O(n)$

~~话说赛场上这种水题我居然没时间打了~~

清晰短小的代码：
```
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define N 111111
#define INF 1e15
LL ind[N],ansp[N],g[N],f[N],nxt[N],d[N][3],lp[N],rp[N],ans=INF,n;
//ind[i]:第i个点的度
//ansp[]:方案
//g[x]:第x个点的颜色
//f[p]:链上第p个点的颜色
//nxt[i]:链上第i个点的下一个节点
//lp[i],rp[i]:第i个点的两个出边指向的点
//ans:答案
void search(int x,LL cost,int p){ //这是第x个点，当前花费为cost，这也是链上的第p个点
	if (nxt[x]==0){ //如果达到了链的另一个断点，则结束
		for (int i=0;i<3;++i){
			if (i!=f[p-1] && i!=f[p-2]){ //可以被使用的颜色。这里一定只有一个i满足要求
				f[p]=i;g[x]=i; //保存结果
				if (cost+d[x][i]<ans){ //如果方案更优
					ans=cost+d[x][i]; //保存结果和方案
					for (int j=1;j<=n;++j){
						ansp[j]=g[j]+1; //由于保存的时候颜色按照0,1,2保存，所以应该加一
					}
				}
			}
		}
		return;
	}
	if (p==1){ //如果这是链上的第一个点（链顶）
		for (int i=0;i<3;++i){ //分别枚举3种颜色
			f[p]=i;g[x]=i;
			search(nxt[x],cost+d[x][i],p+1);
		}
	}else if (p==2){ //如果这是链上的第二个点
		for (int i=0;i<3;++i){ //分别枚举可用的2种颜色，其中一个将被if语句过滤
			if (i!=f[1]){
				f[p]=i;g[x]=i;
				search(nxt[x],cost+d[x][i],p+1);
			}
		}
	}else{ //如果是其他的点
		for (int i=0;i<3;++i){
			if (i!=f[p-1] && i!=f[p-2]){ //这里一定只有一个i满足要求
				f[p]=i;g[x]=i;
				search(nxt[x],cost+d[x][i],p+1);
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false); //读入优化
	cin>>n;
	for (int i=1;i<=n;++i) cin>>d[i][0];
	for (int i=1;i<=n;++i) cin>>d[i][1];
	for (int i=1;i<=n;++i) cin>>d[i][2];
	for (int i=1;i<n;++i){
		int x,y;cin>>x>>y;
		ind[x]++;ind[y]++; //度
		if (ind[x]>=3 || ind[y]>=3){ //这不是链，输出-1
			puts("-1");return 0;
		}
		if (lp[x]==0) lp[x]=y; else rp[x]=y; //由于度只有2，所以无需使用链向星，只要将两个出边分别指向对应的点即可
		if (lp[y]==0) lp[y]=x; else rp[y]=x; 
	}
	int root; //链的顶端
	for (int i=1;i<=n;++i){ //寻找链顶
		if (ind[i]==1){
			root=i;break; 
		}
	}
	int now=lp[root],pre=root;
	nxt[root]=now; //nxt数组记录每个节点后面的节点
	while (true){ //将lp和rp的信息转化为nxt的信息
		if (ind[now]==1) break;    
		if (lp[now]!=pre) nxt[now]=lp[now]; else nxt[now]=rp[now]; //判定下一个节点是哪个指针指向的
		pre=now;now=nxt[now]; //继续转化
	}
	search(root,0,1); //运行
	cout<<ans<<endl; //输出答案
	for (int i=1;i<n;++i){ //输出方案
		cout<<ansp[i]<<" ";
	}
	cout<<ansp[n]<<endl;
	return 0;
}
```

$389ms$

---

## 作者：lrj124 (赞：1)

打的时候像个 zz 一样没写完，，，

这个题一眼发现给出的树不是链答案就是 -1

然后就做完了，算一算 6 种情况的答案就行了。。。

我代码丑的一批

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n,s,a[100001],b[100001],c[100001],deg[100001],p[100001],ans[100001];
vector<int> eg[100001];
ll ansx = 99999999999999999ll;
inline void dfs(int now,int fa,ll tot,ll A,ll B) {
	ll to = -1;
	for (size_t i = 0;i < eg[now].size();i++) if (eg[now][i] ^ fa) to = eg[now][i];
	if (to == -1) {
		if ((A == 1 || A == 2) && (B == 1 || B == 2)) tot += c[now],p[now] = 3;
		if ((A == 3 || A == 2) && (B == 3 || B == 2)) tot += a[now],p[now] = 1;
		if ((A == 1 || A == 3) && (B == 1 || B == 3)) tot += b[now],p[now] = 2;
		if (tot < ansx) {
			ansx = tot;
			for (int i = 1;i <= n;i++) ans[i] = p[i];
		}
		return;
	}
	if (!A && !B) {
		p[now] = 1;
		dfs(to,now,tot+a[now],1,0);
		p[now] = 2;
		dfs(to,now,tot+b[now],2,0);
		p[now] = 3;
		dfs(to,now,tot+c[now],3,0);
	}
	if (A && !B) {
		if (A == 1) {
			p[now] = 2;
			dfs(to,now,tot+b[now],A,2);
			p[now] = 3;
			dfs(to,now,tot+c[now],A,3);
		}
		if (A == 2) {
			p[now] = 1;
			dfs(to,now,tot+a[now],A,1);
			p[now] = 3;
			dfs(to,now,tot+c[now],A,3);
		}
		if (A == 3) {
			p[now] = 2;
			dfs(to,now,tot+b[now],A,2);
			p[now] = 1;
			dfs(to,now,tot+a[now],A,1);
		}
	}
	if (A && B)	{
		if ((A == 1 || A == 2) && (B == 1 || B == 2)) p[now] = 3,dfs(to,now,tot+c[now],B,3);
		if ((A == 3 || A == 2) && (B == 3 || B == 2)) p[now] = 1,dfs(to,now,tot+a[now],B,1);
		if ((A == 1 || A == 3) && (B == 1 || B == 3)) p[now] = 2,dfs(to,now,tot+b[now],B,2);
	}
}
int main() {
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i];
	for (int i = 1;i <= n;i++) cin >> b[i];
	for (int i = 1;i <= n;i++) cin >> c[i];
	for (int i = 1,u,v;i < n;i++) {
		cin >> u >> v;
		eg[u].push_back(v);
		eg[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}
	for (int i = 1;i <= n;i++) if (deg[i] > 2) return 0*printf("-1");
	for (int i = 1;i <= n;i++)
		if (deg[i] == 1) s = i;
	dfs(s,-1,0,0,0);
	cout << ansx<<endl;
	for (int i  = 1;i  <= n;i++) cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

没脑子题。

注意到颜色只有 $3$ 种且任意相邻三个节点颜色需要不同。不难发现只有树的所有节点的度不大于 $2$ 的时候才能满足，即为链。

因为是链，所以可以直接把树看作序列来求解。枚举前 $3$ 个点的颜色情况，则可以推出剩下的点的颜色，这是唯一的。在所有的 $9$ 种情况里面取个最小代价就是答案。

注：在把链转移到序列时，需要先找到链头在铺下去。

## 代码

[Link](https://codeforces.com/contest/1244/submission/232185762)

---

## 作者：WLHW (赞：0)

- 一开始想写树形dp，后来发现。。？！！
- 就是一道大水题
- 先判-1，若一个点的度大于2，则必定不能满足题意。
- 然后再暴力dfs，判断哪几个点是必须涂一种颜色的。（这里我用的是set）
- 再讨论，这3个集合分别涂什么颜色。
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[5][100010],pos[1000010],ok=0,f[1000010];
int o[10];
vector<int> h[100010];
set<int> s[5];
set<int>::iterator it;
long long d[5][5];
void dfs(int u,int fa)
{
	f[u]=fa;
	if(ok==-1) return ;
	if(h[u].size()>2)
	{
		ok=-1;
		return ;
	}
	int k=0;
	for(int i=0; i<h[u].size(); i++)
	{
		int v=h[u][i];
		if(v==fa) continue;
		k++;
		while(pos[f[u]]==k||k==pos[u]) k++;
		pos[v]=k;
		s[k].insert(v);
		dfs(v,u);
	}
}
int main()
{
	int n,i,j,x,y;
	scanf("%d",&n);
	for(i=1; i<=3; i++)
		for(j=1; j<=n; j++) scanf("%d",&a[i][j]);
	for(i=1; i<n; i++)
	{
		scanf("%d%d",&x,&y);
		h[x].push_back(y);
		h[y].push_back(x);
	}
	s[1].insert(1);
	pos[1]=1;
	dfs(1,0);
	if(ok==-1) return puts("-1"),0;
	for(i=1; i<=3; i++)
		for(it=s[i].begin(); it!=s[i].end(); it++)
		{
			d[i][1]+=a[1][*it];
			d[i][2]+=a[2][*it];
			d[i][3]+=a[3][*it];
		}
	long long mmin;
	mmin=d[1][1]+d[2][2]+d[3][3];
	mmin=min(mmin,d[1][1]+d[2][3]+d[3][2]);
	mmin=min(mmin,d[1][2]+d[2][1]+d[3][3]);
	mmin=min(mmin,d[1][2]+d[2][3]+d[3][1]);
	mmin=min(mmin,d[1][3]+d[2][2]+d[3][1]);
	mmin=min(mmin,d[1][3]+d[2][1]+d[3][2]);
	printf("%lld\n",mmin);
	if(mmin==d[1][1]+d[2][2]+d[3][3]) o[1]=1,o[2]=2,o[3]=3;
	else if(mmin==d[1][1]+d[2][3]+d[3][2]) o[1]=1,o[2]=3,o[3]=2;
	else if(mmin==d[1][2]+d[2][1]+d[3][3]) o[1]=2,o[2]=1,o[3]=3;
	else if(mmin==d[1][2]+d[2][3]+d[3][1]) o[1]=2,o[2]=3,o[3]=1;
	else if(mmin==d[1][3]+d[2][2]+d[3][1]) o[1]=3,o[2]=2,o[3]=1;
	else if(mmin==d[1][3]+d[2][1]+d[3][2]) o[1]=3,o[2]=1,o[3]=2;
	for(i=1;i<=n;i++) printf("%d ",o[pos[i]]);
	return 0;
}
```


---

## 作者：caidzh (赞：0)

~~这么水的D，上分场我竟然没报名~~

对于这道题而言，我们可以发现对于一棵树不为链的情况绝对不可能满足，这个很好理解，实在不能理解可以画个图

因此我们找到链的起点，并钦定起点与它的儿子的颜色，这样就可以确定整颗树的颜色分布，做几遍搜索就可以了
```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=100010;
int n,head[maxn],d[maxn],rt,cnt,flag,c[maxn],val[maxn][3];LL ans=LLINF,ansc[maxn];
struct Edge{int nxt,to;}edge[maxn<<1];
void add_edge(int x,int y){edge[++cnt].nxt=head[x];edge[cnt].to=y;head[x]=cnt;}
void dfs(int x,LL sum,int fa){
	if(d[x]==1){
		if(ans>sum){
			ans=sum;for(int i=1;i<=n;i++)ansc[i]=c[i];
		}return;
	}
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa)continue;int used[4];
		memset(used,0,sizeof(used));used[c[x]]=1;used[c[fa]]=1;int color;
		for(int j=1;j<=3;j++)if(!used[j])color=j;c[v]=color;
		dfs(v,sum+val[v][color],x);
	}
}
int main()
{
	n=read();
	for(int i=1;i<=3;i++)for(int j=1;j<=n;j++)val[j][i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add_edge(u,v);add_edge(v,u);d[u]++;d[v]++;
	}
	for(int i=1;i<=n;i++){
		if(d[i]==1){rt=i;}
		else if(d[i]>2){if(!flag)printf("-1");flag=1;break;}
	}if(flag)return 0;if(!rt){printf("-1");return 0;}
	for(int i=1;i<=3;i++)for(int j=1;j<=3;j++)if(i!=j)c[rt]=i,c[edge[head[rt]].to]=j,dfs(edge[head[rt]].to,val[rt][i]+val[edge[head[rt]].to][j],rt);
	cout<<ans<<endl;for(int i=1;i<=n;i++)printf("%d ",ansc[i]);return 0;
}
```


---

