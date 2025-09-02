# Words on Tree

## 题目描述

You are given a tree consisting of $ n $ vertices, and $ q $ triples $ (x_i, y_i, s_i) $ , where $ x_i $ and $ y_i $ are integers from $ 1 $ to $ n $ , and $ s_i $ is a string with length equal to the number of vertices on the simple path from $ x_i $ to $ y_i $ .

You want to write a lowercase Latin letter on each vertex in such a way that, for each of $ q $ given triples, at least one of the following conditions holds:

- if you write out the letters on the vertices on the simple path from $ x_i $ to $ y_i $ in the order they appear on this path, you get the string $ s_i $ ;
- if you write out the letters on the vertices on the simple path from $ y_i $ to $ x_i $ in the order they appear on this path, you get the string $ s_i $ .

Find any possible way to write a letter on each vertex to meet these constraints, or report that it is impossible.

## 样例 #1

### 输入

```
3 2
2 3
2 1
2 1 ab
2 3 bc```

### 输出

```
YES
abc```

## 样例 #2

### 输入

```
3 2
2 3
2 1
2 1 ab
2 3 cd```

### 输出

```
NO```

## 样例 #3

### 输入

```
10 10
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 2 ab
1 3 ab
1 4 ab
1 5 ab
1 6 ab
1 7 ab
1 8 ab
1 9 ab
1 10 ab
10 2 aba```

### 输出

```
YES
baaaaaaaaa```

## 样例 #4

### 输入

```
10 10
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 2 ab
1 3 ab
1 4 aa
1 5 ab
1 6 ab
1 7 ab
1 8 ab
1 9 ab
1 10 ab
10 2 aba```

### 输出

```
NO```

# 题解

## 作者：GaryH (赞：3)

## CF1657F 题解
~~`whk` 人回来混一个社贡分~~


一个想法是暴力 `2-SAT`，即对限制 $i$，记布尔变量 $X_i$ 代表树上是 $x\rightarrow y$ 的字符串等于 $s_i$，

还是 $y\rightarrow x$ 的字符串等于 $s_i$，考虑一种暴力的连边，即枚举两个限制并哈希来判断两者是否能同时成立。

显然，这样建边会爆，但注意到，对每个点 $u$，若没有任何限制的路径包含 $u$，则 $u$ 显然可以随便选，

否则存在限制的路径包含 $u$，则此时 $u$ 至多有两种字符可选。

那么，我们再记布尔变量 $Y_u$ 代表，$u$ 究竟选两种可选字符中的哪种，

则我们每个限制 $i$ 与每个点 $u$，若 $X_i$ 和 $Y_u$ 满足某些关系，当且仅当 $i$ 对应的路径包含点 $u$，

此时我们就用 `2-SAT` 来处理这些关系，我们发现，这样连的边数就是 $O(N)$ 的了，

因为所有限制的路径包含的总点数是 $O(N)$ 的。

还有一种不用 `2-SAT` 的做法，就是我们发现，如果对于限制 $i$ 和被限制 $i$ 的路径包含的点 $u$，

我们连一条无向边 $i\leftrightarrow u$，则这张图的所有连通块的填字符方案独立，而对于每个连通块，

只要确定了其中一个点的方案，则整个连通块的方案就都确定了，故用 `dfs` 处理连通块即可。

[代码](https://codeforces.com/contest/1657/submission/150590657)写的比较拉，仅供参考。

---

## 作者：hater (赞：3)

考虑一条路径会提供怎样的信息。

细分下来有两种情况：

- 一是无论正反读都一样，那么这个点肯定是这个字符。

- 二是正反读不一样，那么这个点就有两种选择。

再考虑把多条路径的信息合并起来。

- 一与一合并，不同即无解。

- 一与二合并，提供信息二的这条路径的方向就是确定的，否则无解。

二与二合并又会有几种小情况：

- 两两选择没有一个相同，无解

- 两两选择相同，没有获取关于这个点的更多信息

- 两两选择是不同的，那么这个点只有一种选择 

当中途确定一个点的选择，那么有些路径的方向就确定了。

我们可以在**两两选择相同**时把路径编号放到这个点上，确定点后方便于确定路径方向。

确定一条路径的方向，就把这条路径全用信息一再次合并即可。

最后你会发现有些点的选择并没有确定。

容易发现**两两选择相同**这种情况下路径与路径的关系是无向边，，我们只需要任意选一个就可以了。

注意最后任选一个也需要把路径覆盖一遍判断无解，有可能会出现两个点的信息相悖的情况。

分析下来我们可以不需要二坐，模拟即可。

```cpp
#include <bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
#define fv( i , x ) for( int i=0; i<v[x].size(); ++i ) 
#define i60 long long 
#define IL inline 
#define ls k<<1 
#define rs k<<1|1 
using namespace std ; 
const int N = 4e5+10 ; 
vector <int> v[N] , ch[N] ;  
int pre[N] , d[N] , n ; string s[N] ; 
struct node { int x , y , z ; } a[N] ; 
void dfs( int x , int fa ) { 
  int y ; 
  pre[x] = fa ; d[x] = d[fa] + 1 ; 
  fv( i , x ) { 
    y = v[x][i] ; 
    if( y == fa ) continue ; 
    dfs( y , x ) ; 
  } 
} 
int lca( int x , int y ) { 
  while( d[x] > d[y] ) x = pre[x] ; 
  while( d[y] > d[x] ) y = pre[y] ; 
  while( x != y ) x = pre[x] , y = pre[y] ; 
  return x ; 
} 
int is[N] , vis[N] ; char ans[N] , c1[N] , c2[N] ; 
void EXI( ) { cout << "NO" << '\n' ; exit(0) ; } 
void cov( int id , int ci ) ; 
void ADD( int x , char c ) { 
  if( is[x] == -1 ) { is[x] = 1 ; ans[x] = c ; return ; } 
  if( is[x] == 1 ) { if( ans[x] != c ) EXI() ; return ; } 
  if( c != c1[x] && c != c2[x] ) EXI() ; 
  is[x] = 1 ; ans[x] = c ; 
  int xci = (c==c1[x] ? 0 :1) , tx , ci ;  
  for( auto i : ch[x] ) tx = abs(i) , ci = (i<0) , cov( tx , xci ^ ci ) ; 
  ch[x].clear() ; 
} // 确定某个点的选择  
void cov( int id , int ci ) { 
  if( vis[id] != -1 ) { if( vis[id] != ci ) EXI() ; return ; }  
  vis[id] = ci ; 
  int x = a[id].x , y = a[id].y , z = a[id].z ;  
  if( ci ) swap( x , y ) ; 
  int p = 0 ; 
  while( x != z ) ADD( x , s[id][p++] ) , x = pre[x] ; 
  ADD( z , s[id][p++] ) ; 
  p = s[id].length() -1 ; 
  while( y != z ) ADD( y , s[id][p--] ) , y = pre[y] ; 
} // 路径覆盖  
void merge( int x , int id , char b1 , char b2 ) { 
  if( b1 == b2 ) { ADD( x , b1 ) ; return ; } 
  if( is[x] == -1 ) { 
    is[x] = 0 ; c1[x] = b1 ; c2[x] = b2 ; 
    ch[x].push_back(id) ; return ; 
  } 
  if( is[x] == 1 ) { 
    if( ans[x] == b1 ) { cov( id , 0 ) ; return ; } 
	else if( ans[x] == b2 ) { cov( id , 1 ) ; return ; } 
	else EXI() ; 
  } 
  if( c1[x] == b1 && c2[x] == b2 ) { ch[x].push_back(id) ; return ; } 
  if( c1[x] == b2 && c2[x] == b1 ) { ch[x].push_back(-id) ; return ; } 
  if( b1 == c1[x] || b1 == c2[x] ) { ADD( x , b1 ) ; cov( id , 0 ) ; return ; } 
  if( b2 == c1[x] || b2 == c2[x] ) { ADD( x , b2 ) ; cov( id , 1 ) ; return ; } EXI() ; 
} // 合并点的信息 
void path( int id ) { 
  int x = a[id].x , y = a[id].y , z = a[id].z ; 
  char b1 , b2 ; int p = 1 , len = s[id].length() ;   
  while( x != z ) { 
    b1 = s[id][p-1] ; b2 = s[id][len-p] ; p ++ ; 
    merge( x , id , b1 , b2 ) ; x = pre[x] ; 
  } 
  b1 = s[id][p-1] ; b2 = s[id][len-p] ; 
  merge( z , id , b1 , b2 ) ; p = len ; 
  while( y != z ) { 
    b1 = s[id][p-1] ; b2 = s[id][len-p] ; p -- ; 
    merge( y , id , b1 , b2 ) ; y = pre[y] ; 
  } 
} // 合并路径信息 
signed main( ) { 
  memset( is , -1 , sizeof(is) ) ; 
  memset( vis , -1 , sizeof(vis) ) ;   
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; int q , x , y ;  
  cin >> n >> q ; 
  fp( i , 1 , n-1 ) { 
    cin >> x >> y ; 
	v[x].push_back(y) ; v[y].push_back(x) ;  
  } 
  dfs( 1 , 0 ) ; 
  fp( i , 1 , q ) { 
    cin >> a[i].x >> a[i].y >> s[i] ; 
    a[i].z = lca( a[i].x , a[i].y ) ; 
	path(i) ; 
  } 
  fp( i , 1 , n ) if( is[i] == 0 ) ADD( i , c1[i] ) ; 
  fp( i , 1 , n ) if( is[i] == -1 ) ans[i] = 'a' ; 
  cout << "YES" << '\n' ; 
  fp( i , 1 , n ) cout << ans[i] ; cout << '\n' ;  
  return 0 ; 
} 
```



---

## 作者：未来姚班zyl (赞：2)

## 题目大意

给定一棵点权为字母的树与 $m$ 个限制条件，每个限制条件形如 $x,y,s$，表示 要么 $x$ 到 $y$ 的路径上的点权构成的字符串为 $s$，要么 $y$ 到 $x$ 的路径上的点权构成的字符串为 $s$。

请你为每个点分配点权，使得满足所有限制。

## 题目分析

考虑 2-sat 算法。

考虑一种朴素的决策建模，对每个点 $x$ 的每个点权 $i$ 建立两个点，分别表示选（称其为 $1$ 号点）或者不选（称其为 $0$ 号点），然后对于每个点，由其每个点权的 $1$ 号点向其他点权的 $0$ 号点连边，表示一个点只能选一个点权，但空间和时间是绝对不够的，即使前缀和优化也会爆炸。

注意到 $\sum |s|$ 是 $O(n)$ 的，故至多会对 $2n$ 个点权做出限制，动态开点即可。

考虑限制如何连边，限制相当于 $a$ 或 $b$。对 $a$ 和 $b$ 各建 $1$ 号点和 $0$ 号点，每个 $0$ 号点向另一个 $1$ 号点连边。然后每个限制的 $1$ 号点向其限制的点权的 $1$ 号点连边，而对限制点的其它点权的 $1$ 号点向限制的 $0$ 号点连边即可。

至于构造，最好先给点权赋初值，然后检查每个限制是否成立，依照成立的限制修改点权，避免因动态开点带来的各种细节。

对于复杂度，考虑点数是 $4m+2n$ 的，而边数至多是 $2\times \frac{2n}{26}\times 26^2=104 n$ 的，所以复杂度 $O(n)$，常数约为 $100$，可以通过此题。其它更加深入的思路不过是在减小常数。

根据具体实现可能会产生各种额外的常数或者 $\log$ 因子（比如用 map），也可能减小边数量级（比如点内前缀和优化建边），不过时间和空间都很宽裕，各种实现应该都可以通过。

这题代码实现还得看个人能力，我的代码仅供参考，在采用了一些非极端的压行后程序只有 $77$ 行。不过有个小技巧可以分享一下，由于动态开点的每个点的 $1$ 号点和 $0$ 号点都成对出现，所以可以类似网络流的思路，让点的编号从 $2$ 开始，异或 $1$ 就能得到另一个点。

```cpp
#include<bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N =4e5+5,M=2.5e6+5;
char S[N];
int w[N],n,m,h[N],to[N<<1],nxt[N<<1],cnt,tot=1,f[N],dep[N],s[M],tp,st[N],t,dfn[M],low[M],Time,bel[M],K,fi[N];
inline void add_(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,to[++cnt]=a,nxt[cnt]=h[b],h[b]=cnt;
}
map<int,int>P[N];
vector<int>p[M],q,pp[N][27];
void dfs(int x,int fa){
	dep[x]=dep[fa]+1,f[x]=fa;
	e(x)if(y^fa)dfs(y,x);
}
int getid(int x,int k){
	if(P[x][k])return P[x][k]^1;
	return P[x][k]=tot+1,tot+=2,tot;
}
vector<Pi>qq[M];
void lca(int x,int y){
	s[++tp]=x,st[++t]=y;
	while(dep[x]>dep[y])s[++tp]=x=f[x];
	while(dep[x]<dep[y])st[++t]=y=f[y];
	while(x^y)s[++tp]=x=f[x],st[++t]=y=f[y];
	while(t)if(st[t--]^s[tp])s[++tp]=st[t+1];
	int id1=++tot,Id1=++tot,id2=++tot,Id2=++tot;
	q.pb(id1),q.pb(id2),p[Id1].pb(id2),p[Id2].pb(id1);
	rep(i,1,tp)w[i]=S[i]-'a'+1;
	rep(i,1,tp)p[id1].pb(getid(s[i],w[i])),qq[id1].pb({s[i],w[i]}),pp[s[i]][w[i]].pb(Id1),p[id2].pb(getid(s[i],w[tp-i+1])),pp[s[i]][w[tp-i+1]].pb(Id2),qq[id2].pb({s[i],w[tp-i+1]});
	tp=0,t=0;
}
bool instac[M];
void tarjan(int x){
	dfn[x]=low[x]=++Time,s[++tp]=x,instac[x]=1;
	E(x)if(!dfn[y])tarjan(y),low[x]=min(low[x],low[y]);
	else if(instac[y])low[x]=min(low[x],dfn[y]);
	if(dfn[x]==low[x]){
		K++;
		for(int y=s[tp--];;y=s[tp--]){
			instac[y]=0,bel[y]=K;
			if(bel[y^1]==bel[y])puts("NO"),exit(0);
			if(y==x)return;
		}
	}
}
signed main(){
	n=read(),m=read();
	rep(i,2,n)add_(read(),read());
	dfs(1,0);
	repm(i){
		int x=read(),y=read();
		scanf("%s",S+1),lca(x,y);
	}
	repn(i){
		for(auto y:P[i])s[++tp]=y.first;
		rep(j,1,tp)rep(k,j+1,tp){
			p[P[i][s[j]]+1].pb(P[i][s[k]]),p[P[i][s[k]]^1].pb(P[i][s[j]]);
			for(auto y:pp[i][s[j]])p[P[i][s[k]]^1].pb(y);
			for(auto y:pp[i][s[k]])p[P[i][s[j]]^1].pb(y);
		}
		tp=0;
	}
	rep(i,1,tot)if(!dfn[i])tarjan(i);
	repn(i)fi[i]=1;
	for(auto y:q)if(bel[y]<bel[y^1])for(auto z:qq[y])fi[z.first]=z.second;
	puts("YES");
	repn(i)putchar('a'+fi[i]-1);
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：2)

~~一眼 2-sat。~~ 用 2-sat 做是因为 $x\to y,y\to x$ 只有两种选法。

我们建立 bool 变量：

* 每一个题目给的路径条件建一个 bool，代表这个字符串正 / 反放。

* 每个树上的节点至多两个 bool：每个她可能取的值。

然后我们建边（记得建这些的对称边）：

* 路径上字符串每个摆放方式连向路径上每个节点的对应字符。

* 接下来对节点的考虑屏蔽没有被路径覆盖过的点。

* 对于字母只有一种选择的点，不可能不选这个字母。

* 对于字母有两种选择的点，不选一个字母连向选另一个，选一个连向不选另一个。

然后跑 Tarjan，通过 Tarjan 的反拓扑序来确定每个节点的最终字母。

注意最后考虑没有被路径覆盖过的点，随便选字母即可。

删减了 $5$ 次还是冗长的屑代码：

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define ckmn(a,b) a=min(a,b)
#define N 400004
int n,q,s[N],dep[N],fa[N],tot=0,dfn[6*N],low[6*N],col[6*N],tim=0,st[6*N],stt=0,ct=0;
vector<int> e[N],g[6*N];
vector<pair<char,int> > pos[2*N];
char c[N];
inline void adde(int x,int y){ g[x].pb(y); if(x!=(y^1)) g[y^1].pb(x^1); }
void nnd(int x,char y,char z){
	if(!pos[x].empty()) return ;
	pos[x].pb(mkp(y,tot+=2));
	if(y!=z){
		pos[x].pb(mkp(z,tot+=2));
		adde(pos[x][0].sec,pos[x][1].sec^1);
		adde(pos[x][0].sec^1,pos[x][1].sec);
	}else if(y!='0'){
		adde(pos[x][0].sec,1);
	}
}
inline int num(int x,char y){ for(auto i:pos[x]) if(i.fir==y) return i.sec; return 0; }
void dfs(int rt,int fat){
	dep[rt]=dep[fat]+1; fa[rt]=fat;
	for(int i:e[rt]) if(i!=fat) dfs(i,rt);
}
void path(int x,int y,int len){
	if(dep[x]<dep[y]) swap(x,y);
	int z=0;
	while(dep[x]>dep[y]) s[z++]=x,x=fa[x];
	while(x!=y) s[--len]=y,s[z++]=x,x=fa[x],y=fa[y];
	s[z]=x;
}
void tar(int x){
	dfn[x]=low[x]=++tim;
	st[++stt]=x;
	for(int i:g[x]){
		if(!dfn[i]) tar(i),ckmn(low[x],low[i]);
		else if(!col[i]) ckmn(low[x],dfn[i]);
	}
	if(dfn[x]==low[x]){
		col[x]=++ct;
		while(st[stt]!=x) col[st[stt--]]=ct;
		stt--;
	}
}
int main(){
	scanf("%d%d",&n,&q);
	int x,y,len;
	For(i,1,n-1){
		scanf("%d%d",&x,&y);
		e[x].pb(y);
		e[y].pb(x);
	}
	dfs(1,0);
	For(i,1,q){
		scanf("%d%d%s",&x,&y,c);
		path(x,y,len=strlen(c));
		For(j,0,(len-1)>>1){
			nnd(s[j],c[j],c[len-1-j]);
			nnd(s[len-1-j],c[j],c[len-1-j]);
			nnd(n+i,'0','0');
			adde(num(n+i,'0')^1,num(s[j],c[j])^1);
			adde(num(n+i,'0'),num(s[j],c[len-1-j])^1);
			adde(num(n+i,'0')^1,num(s[len-1-j],c[len-1-j])^1);
			adde(num(n+i,'0'),num(s[len-1-j],c[j])^1);
		}
	}
	adde(1,0);
	For(i,0,tot+1) if(!dfn[i]) tar(i);
	for(int i=0;i<tot+2;i+=2) if(col[i]==col[i^1]){
		puts("NO");
		return 0;
	}
	puts("YES");
	fill(c+1,c+1+n,'a');
	For(i,1,n)
		for(auto j:pos[i])
			if(col[j.sec]>col[j.sec^1])
				c[i]=j.fir;
	c[n+1]='\0'; 
	printf("%s\n",c+1);
return 0;}
```

---

## 作者：MatrixGroup (赞：0)

- 前置知识

[2-SAT](https://www.luogu.com.cn/problem/P4782)

- 解法

一个字符串有两种可能，我们能想到什么？

没错！2-SAT。

但是如果直接把这些字符串的顺逆扔进去可能不是很好维护。

$\sum\limits_{j=1}^q|s_j|\le4\times10^5$ 有什么作用呢？

我们可以将每一条路径作用于每一个点！

这道题的算法就是这样，接下来将实现方法与细节。

首先对于每一个被遇到的节点，我们维护它在每一条路径上可能字符的并集。这样每个被遇到的节点的可能情况不大于二。

如果有一个节点的可能字符集为空，那么答案显然是 `NO`。

如果某一个节点的可能字符集大小为 $1$，我们随便给它再它加另一个字符，同时加入这样的要求：「$c_i$ 选原来的 或 $c_i$ 选原来的」。

对于某一个要求，我们将其中**所有在只看该字符串有多种选择**的字符连成一个环，就可以用线性复杂度的边数完成这些限制！

具体地，

- 如果（环上）前一个字符已经被确认不可能，忽略这条限制。
- 否则，如果后一个字符已经被确认不可能，则将前一个字符设为不可能。（也就是「$c_i$ 不选它 或 $c_i$ 不选它」）
- 否则，增加条件「$c_i$ 不选当前字符 或 $c_{nxt}$ 选当前字符」。

最后，如果某一个字符被遇到过，在 2-SAT 的模型中找出它的选择。否则，随便输出一个字符。

诶，树上路径是不是还要求 LCA 啊？事实上不用，我们可以根据字符串长度得出它们之间路径的长度，就能求出 LCA 的深度了，不需要再求一遍。

当然最开始还是要 dfs 一次的。2-SAT 不要写错。（我调了好一会儿）

- 代码

实现中，我用的是「如果 $c_i$ 选某一个 那么 $c_j$ 选某一个」形式的加边。

献上我~~从听别人将这题到写完花了四多天的~~代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0,_##i##__end=(n);i<_##i##__end;++i)
#define per(i,n) for(int i=(n)-1;i>=0;--i)
#define rep1(i,n) for(int i=1,_##i##__end=(n);i<=_##i##__end;++i)
#define pb push_back
using namespace std;
const int N=400005;
const int V=800005;
struct two_sat{//2-SAT的结构体,i表示a[i]=0,i+n表示a[i]=1
	void init(int n2)//初始化
	{
		n=n2;
		vc=n<<1;
		rep1(i,vc)
		{
			to[i].clear();
			fr[i].clear();
		}
		cnt=cnt2=cnt3=0;
		rep1(i,vc) vis[i]=0,scc[i]=-1;
	}
	void link_if(int i,int x,int j,int y)//如果 a[i] 是 x 那么 a[j] 是 y
	{
		to[i+x*n].pb(j+y*n);//建原图
		fr[j+y*n].pb(i+x*n);//建反图
		to[j+(y^1)*n].pb(i+(x^1)*n);//逆否命题
		fr[i+(x^1)*n].pb(j+(y^1)*n);
	}
	bool satisfiable()//判断是否可以成立
	{
		before_ask();
		rep1(i,n)
		{
			if(scc[i]==scc[i+n]) return false;//a[i]=0 和 a[i]=1 不能互相推出
		}
		return true;
	}
	void determine(bool* fl)//给出一组解
	{
		rep1(i,n)
		{
			if(scc[i]<scc[i+n]) fl[i]=1;
			else fl[i]=0;
		}
	}
	private:
		int n,vc;//变量个数和要建的节点个数
		vector<int> to[V];//原图
		vector<int> fr[V];//反图
		vector<int> g2[V];//缩点后的图
		int dfn[V],cnt;//dfs序
		bool vis[V];//是否在dfs中遇到过
		int deg[V];//入度
		int scc[V],cnt2;//scc的编号和个数
		queue<int> q;//目前入度为0的点
		int idx[V],cnt3;//某个节点的拓扑序编号和已经有的个数
		void dfs_dfn(int v)//原图搜
		{
    		vis[v]=1;
    		rep(i,to[v].size())
    		{
    			int u=to[v][i];
    			if(!vis[u]) dfs_dfn(u);
			}
			dfn[cnt++]=v;
		}
		void dfs_scc(int v,int c)//反图搜
		{
			scc[v]=c;
			rep(i,fr[v].size())
    		{
    			int u=fr[v][i];
    			if(scc[u]==-1) dfs_scc(u,c);
			}
		}
		void calc_scc()//计算SCC编号，Kosaraju 算法
		{
			rep1(i,vc) if(!vis[i]) dfs_dfn(i);
			per(i,cnt) if(scc[dfn[i]]==-1) dfs_scc(dfn[i],++cnt2); 
		}
		void rebuild()//重建图
		{
			rep1(i,vc) rep(j,to[i].size())
			{
				int u=to[i][j];
				if(scc[i]!=scc[u])
				{
					g2[scc[i]].pb(scc[u]);
				}
			}
			rep1(i,cnt2)
			{
				deg[i]=0;
				sort(g2[i].begin(),g2[i].end());
				int v=unique(g2[i].begin(),g2[i].end())-g2[i].begin();
				g2[i].resize(v);
			}
			rep1(i,cnt2)
			{
				rep(j,g2[i].size())
				{
					++deg[g2[i][j]];
				}
			}
		}
		void topo_sort()//拓扑排序
		{
			rep1(i,cnt2) if(deg[i]==0) q.push(i);
			while(!q.empty())
			{
				int u=q.front();
				idx[u]=cnt3++;
				q.pop();
				rep(i,g2[u].size())
				{
					int v=g2[u][i];
					if(!(--deg[v]))
					{
						q.push(v);
					}
				}
			}
		}
		void before_ask()//预处理
		{
			calc_scc();
			rebuild();
			topo_sort();
			rep1(i,vc) scc[i]=idx[scc[i]];
		}
};
two_sat str;
int n,q,u,v;
int x[N],y[N];//query
string s[N];//query
vector<int> path[N];//路径
string could[N];
bool vis[N];//遇到过
vector<int> tr[N];//树
int dep[N],par[N];//深度 与 父亲
stack<int> xx,yy;
vector<int> choices;//这个环
bool ans[N];
void dfs(int x,int p,int d)//求深度和父亲
{
	dep[x]=d;par[x]=p;
	rep(i,tr[x].size())
	{
		int U=tr[x][i];
		if(U==p) continue;
		dfs(U,x,d+1);
	}
}
void process(int i)
{
	cin>>x[i]>>y[i]>>s[i];
	int dx=dep[x[i]],dy=dep[y[i]];
	int nw=x[i];
	int ld=((dx+dy)-(s[i].size()-1))>>1;//LCA的深度
	while(!xx.empty()) xx.pop(); while(!yy.empty()) yy.pop();
	while(dx!=ld)
	{
		xx.push(nw);nw=par[nw];--dx;
	}
	xx.push(nw);
	nw=y[i];
	while(dy!=ld)
	{
		yy.push(nw);nw=par[nw];--dy;
	}
	while(!yy.empty())
	{
		xx.push(yy.top());yy.pop();
	}
    //使用栈求路径
	int c=0,ver;char c1,c2;
	while(!xx.empty())
	{
		c1=s[i][c];c2=s[i][s[i].size()-(++c)];ver=xx.top();xx.pop();path[i].pb(ver);
		if(!vis[ver])//如果没遇到过
		{
			vis[ver]=1;
			if(c1!=c2) 
			{
				could[ver]+=c1;could[ver]+=c2;
			}
			else
			{
				could[ver]+=c1;
			}
		}
		else
		{
			per(j,could[ver].size())
			if(could[ver][j]!=c1&&could[ver][j]!=c2)//求并
			could[ver].erase(j,1);
		}
	}
}
void resolve()//连边
{
	str.init(n);
	rep1(i,n)
	{
		if(vis[i])
		{
			if(could[i].empty())//如果可能集合为空集
			{
				cout<<"NO"<<endl;
				exit(0);
			}
			else if(could[i].size()==1)//增加一个方便做 2-SAT
			{
				if(could[i]=="a") could[i]+='b';
				else could[i]+='a';
				str.link_if(i,1,i,0);
			}
		}
	}
	rep(i,q)
	{
		choices.clear();
		rep(j,s[i].size())
		{
			if(s[i][j]!=s[i][s[i].size()-1-j])//有多种选择
			{
				choices.pb(j);
			}
		}
		rep(j,choices.size())
		{
			int nx=(j+1)%choices.size();
			int x=choices[j],y=choices[nx];
			int vx=path[i][x],vy=path[i][y];
			char x1=s[i][x],x2=s[i][s[i].size()-1-x],y1=s[i][y],y2=s[i][s[i].size()-1-y];
			string ch1=could[vx],ch2=could[vy];
			int idx1=min(size_t(2),ch1.find(x1)),idx2=min(size_t(2),ch1.find(x2)),idy1=min(size_t(2),ch2.find(y1)),idy2=min(size_t(2),ch2.find(y2));
			if(idx1!=2)
			{
				if(idy1==2)
				{
					str.link_if(vx,idx1,vx,!idx1);
				}
				else
				{
					str.link_if(vx,idx1,vy,idy1);
				}
			}
			if(idx2!=2)
			{
				if(idy2==2)
				{
					str.link_if(vx,idx2,vx,!idx2);
				}
				else
				{
					str.link_if(vx,idx2,vy,idy2);
				}
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin>>n>>q;
	rep(i,n-1)
	{
		cin>>u>>v;
		tr[u].pb(v);
		tr[v].pb(u);
	}
	dfs(1,-1,0);
	rep(i,q)
	{
		process(i);
	}
	resolve();
	if(!str.satisfiable())//无解
	{
		cout<<"NO"<<endl;
	}
	else
	{
		cout<<"YES"<<endl;
		str.determine(ans);
		rep1(i,n) 
		{
			if(vis[i]) cout<<could[i][ans[i]]; else cout<<'a'; //如果没有遇到过随便输出一个
		}
		cout<<endl;
	}
	return 0;
}
```



---

