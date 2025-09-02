# [ABC229E] Graph Destruction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc229/tasks/abc229_e

$ N $ 頂点 $ M $ 辺の単純な無向グラフが与えられます。  
 辺 $ i $ は、頂点 $ A_i $ と $ B_i $ を結んでいます。

頂点 $ 1,2,\ldots,N $ を順番に消していきます。  
 なお、頂点 $ i $ を消すとは、頂点 $ i $ と、頂点 $ i $ に接続する全ての辺をグラフから削除することです。

$ i=1,2,\ldots,N $ について、頂点 $ i $ まで消した時にグラフはいくつの連結成分に分かれていますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min(\frac{N(N-1)}{2}\ ,\ 2\ \times\ 10^5\ ) $
- $ 1\ \leq\ A_i\ \lt\ B_i\ \leq\ N $
- $ i\ \neq\ j $ ならば $ (A_i,B_i)\ \neq\ (A_j,B_j) $
- 入力は全て整数である

### Sample Explanation 1

!\[\](https://img.atcoder.jp/ghi/3320212a9093132a80105bf02feeb195.png) グラフは上図のように変化していきます。

### Sample Explanation 2

はじめからグラフが非連結なこともあります。

## 样例 #1

### 输入

```
6 7
1 2
1 4
1 5
2 4
2 3
3 5
3 6```

### 输出

```
1
2
3
2
1
0```

## 样例 #2

### 输入

```
8 7
7 8
3 4
5 6
5 7
5 8
6 7
6 8```

### 输出

```
3
2
2
1
1
1
1
0```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc229_e)

### 思路

可以用**并查集**解决此题。

用并查集求连通块个数，但由于并查集只能加点而不能删点，所以将所有的删点改为加点，并倒着遍历刚好可以满足要求。

### 过程

设计数器为 $c$，初始化为 $0$，答案序列为 $A$。

倒着遍历从 $N$ 到 $1$，设循环变量为 $u$，代表第 $u$ 条边。先将 $A_u$ 答案记为 $c$，增加连通块 $c\gets c+1$。然后遍历与 $u$ 连通的点 $v$，如果 $u$ 与 $v$ 不连通，则会减少一个连通块，即 $c\gets c-1$。

最后正序输出所有的 $A_u$ 即可。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e5+10;
vector<int>vc[N],a;
int n,m,fa[N];
void _init(){
	for(int i=1;i<=n;++i)
		fa[i]=i;
	return;
}
int _find(int x){
	if(x==fa[x])
		return x;
	fa[x]=_find(fa[x]);
	return fa[x];
}
void _merge(int x,int y){
	int xx=_find(x),yy=_find(y);
	if(xx!=yy)
		fa[xx]=yy;
	return;
}
int main(){
	n=read(),m=read();
	_init();
	while(m--){
		int u=read(),v=read();
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	int ans=0;
	for(int i=n;i>=1;--i){
		a.push_back(ans++);
		for(auto j:vc[i])
			if(i<j){
				if(_find(i)!=_find(j))
					--ans;
				_merge(i,j);
			}
	}
	reverse(a.begin(),a.end());
	for(auto i:a)
		printf("%d\n",i);
	return 0;
}
```

---

## 作者：lqsy002 (赞：1)

## 解题思路

题目要求删点，考虑将删点改成加点，倒着处理询问，同时用并查集维护连通块，每新加一个结点 $v$，连通块个数 $cnt \gets cnt+1$，在连边之前，如果该结点和 $u$ 不属于同一个连通块，那么 $cnt \gets cnt-1$。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
int n,m;
int idx,head[maxn];
int fa[maxn],ans[maxn];
struct edge{
	int to;
	int nxt;
}e[maxn<<1];
void add(int u,int v){
	e[++idx]={v,head[u]};
	head[u]=idx;
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1,u,v;i<=m;++i){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int u=n,cnt=0;u;--u){
		ans[u]=cnt++;
		for(int i=head[u],v;i;i=e[i].nxt){
			v=e[i].to;
			if(find(u)!=find(v)&&u<v){
				fa[fa[v]]=fa[u];
				--cnt;
			}
		}
	}
	for(int i=1;i<=n;++i)
		cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

时光倒流。

顺着删边不好处理，考虑从最后一次删边之后的结果开始从后往前加边。

对于加一个点 $x$ 的所有边，用并查集维护每个联通块。如果与 $x$ 相连的某一个点 $y$，满足：$y$ 在 $x$ 之后被删，$y$ 所在的联通块与 $x$ 的不同。则将这两个联通块合并，联通块数量 $-1$。在这里，$x$ 刚加进来（没有与别的联通块合并）的时候，联通块的数量需要 $+1$。所以加上一个点 $x$，联通块的数量增加 $1-cnt$，其中 $cnt$ 是合并时减少的联通块数量。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

const int N=2e5+10;
int n,m;
int ne[N<<1],e[N<<1],h[N],idx;
int fa[N],ans[N],cnt;

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il int find(int x){return ((fa[x]==x)?x:(fa[x]=find(fa[x])));}
il void get(int x,int y){fa[find(x)]=find(y);}

il void solve(){
	cin>>n>>m;
	for(re int i=1,u,v;i<=m;++i)
		cin>>u>>v,add(u,v),add(v,u);
	for(re int i=1;i<=n;++i) fa[i]=i;
	for(re int s=n;s>=1;--s){
		ans[s]=cnt;int num=0;
		for(re int i=h[s];i;i=ne[i]){
			int j=e[i];if(find(j)==find(s)||j<s) continue;
			get(j,s),++num;
		}
		cnt-=(num-1);
	}
	for(re int i=1;i<=n;++i) cout<<ans[i]<<"\n"; 
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：scp020 (赞：1)

# ABC229E Graph Destruction

一道比较套路的题，没有太多的思维量，也没有考察很难的算法。

## 解法

看到题中有求连通块，我们就可以用并查集来维护连通块。又因为普通并查集只支持添加操作，不支持撤销操作，所以我们思考一个方向的做法。题中让我们正着删点，我们就倒着加点就可以了。现在条件就被我们转化为了如下 $3$ 条：

- 给定 $n$ 个点，$m$ 条边等待被添加，现在拥有一个空图。
- 按照 $n,n-1,\dots,1$ 的顺序添加点及与其相连且另一个点的编号大于该点编号的边。
- 对于每次加点操作，求出现在图中连通块的数量并记录，因为我们最后要正着输出。

### 具体执行

按照如上 $3$ 条，我们可以按照如下思路统计连通块个数：

- 如果在图外加了一个点，则连通块数量加 $1$。
- 加点后我们再加边，如果加完边沟通了两个不同的连通块，则连通块数量减 $1$。

最后代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
#define Putchar(c) p3==p4 and (fwrite(Ouf,1,1<<21,stdout),p3=Ouf),*p3++=c
char Inf[1<<21],Ouf[1<<21],*p1,*p2,*p3=Ouf,*p4=Ouf+(1<<21);
inline void read(int &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
inline void write(int x)
{
	if(x<0) Putchar('-'),x=-x;
	if(x>=10) write(x/10),x%=10;
	Putchar(x^48);
}
int n,m,head[200010],cnt,fa[200010],ans[200010],tot;
struct edge
{
	int to,next;
};
edge e[400010];
inline void add(const int &x,const int &y)
{
	e[++cnt].to=y,e[cnt].next=head[x],head[x]=cnt;
}
inline int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	read(n),read(m);
	for(int i=1,x,y;i<=m;i++) read(x),read(y),add(x,y),add(y,x);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=n;i;i--)
	{
		ans[i]=tot,tot++;
		for(int j=head[i];j;j=e[j].next)
			if(e[j].to>i && find(e[j].to)!=find(i)) fa[fa[e[j].to]]=fa[i],tot--;
	}
	for(int i=1;i<=n;i++) write(ans[i]),Putchar('\n');
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```



---

## 作者：_zzzzzzy_ (赞：1)

# 思路
一个常见的套路题。

把删边的操作倒着还原，把删边变成加边。

我们对于这几个操作，可以用并查集来做。

对于怎么来统计连通块的个数我们可以维护一个 $cnt$ 表示个数，如果加边的时候发现两个点所在的连通分块不是一个，那么只用把 $cnt$ 减一就可以了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000000;
vector<int>e[maxn];
int ans[maxn],f[maxn];
int F(int x){return x==f[x]?x:f[x]=F(f[x]);}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int cnt=0;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=n;i>=1;i--){
		ans[i]=cnt;
		cnt++;
		for(int v:e[i]){
			if(v>i){
				int fx=F(i),fy=F(v);
				if(fx!=fy){
					cnt--;
					f[fx]=fy;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：nytyq (赞：0)

## 分析

考虑到并查集维护集合个数。

题目有删边操作，并查集无法删边，考虑逆向维护并查集。

考虑到逆向的操作，输出结果用 ```stack``` 做存储，进行输出。

## ACcode

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m;

int f[N];

vector<int> g[N];

int find(int x){
	return x==f[x]?x:f[x]=find(f[x]);
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v),g[v].push_back(u);
	}
	for(int i=1;i<N;i++) f[i]=i;
	int Cnt=0;
	
	stack<int> ans;
	
	for(int i=n;i>=1;i--){
		ans.push(Cnt);
		Cnt++;
		for(auto Point:g[i]){
			if(Point>i){
				if(find(Point)!=find(i)) Cnt--;
				f[find(Point)]=find(i); 
			}
		}
	}
	
	while(!ans.empty()){
		cout<<ans.top()<<endl;
		ans.pop();
	}

	return 0;
}

```

---

## 作者：Nahia (赞：0)

### 思路

题目要求删点，不难想到可以将删点改为加点，考虑倒着处理询问，将每一个删点改成加点，加点时用并查集维护连通块即可。

### solution

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n,m;
int idx,hd[N];
int fa[N],a[N];
struct node{
	int to;
	int nxt;
}b[N*2];
void pus(int u,int v){
	b[++idx]={v,hd[u]};
	hd[u]=idx;
}
int fd(int x){
	return fa[x]==x?x:fa[x]=fd(fa[x]);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		pus(u,v);
		pus(v,u);
	}
	for(int u=n,j=0;u!=0;u--){
		a[u]=j++;
		for(int i=hd[u],v;i!=0;i=b[i].nxt){
			v=b[i].to;
			if(fd(u)!=fd(v)&&u<v){
				fa[fa[v]]=fa[u];
				--j;
			}
		}
	}
	for(int i=1;i<=n;++i)
		cout<<a[i]<<'\n';
	return 0;
}
```

---

## 作者：ny_123457 (赞：0)

## Part.1 思路
可以用并查集记录维护连通块，减少点直接整成加一个点，分别处理每一个点，唯一需要注意的就是需要倒着处理。

可以定义一个变量来记录每一次操作后的连通块数量，用栈来存答案，最后正序输出。
## Part.2 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,sum,quchu,f[200005]; 
vector<int>dian[200005]; 
stack<int>ans;
int getfather(int x){ 
	if(x!=f[x])return f[x]=getfather(f[x]);
	return f[x];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		dian[u].push_back(v);
		dian[v].push_back(u);
	}
	for(int i=1;i<=n;i++)f[i]=i; 
	for(int i=n;i>=1;i--){ 
		ans.push(sum);
		sum++;
		for(auto quchu:dian[i]){
			if(quchu>i&&getfather(quchu)!=getfather(i)){
				f[getfather(quchu)]=getfather(i);
				sum--;
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans.top()<<endl;
		ans.pop();
	} 
	return 0;
} 
```

---

## 作者：2020luke (赞：0)

# [[ABC229E] Graph Destruction](https://www.luogu.com.cn/problem/AT_abc229_e) 题解

## 思路解析

题目要求删点，而众所周知删点的代价要大于加点的代价，于是我们考虑倒着处理询问，将每一个删点改成加点，而加点时就用并查集维护连通块即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m, fa[N];
vector<int> g[N];
int find(int x) {
	if(x == fa[x]) return x;
	return (fa[x] = find(fa[x]), fa[x]);
}
int main() {
	cin >> n >> m;
	for(int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 1; i <= n; i++) fa[i] = i;
	int ans = 0;
	stack<int> st;
	for(int i = n; i >= 1; i--) {
		st.push(ans);
		ans ++;
		for(auto it : g[i]) {
			if(it > i) {
				if(find(it) != find(i)) ans --;
				fa[find(it)] = find(i);
			}
		}
	}
	while(!st.empty()) cout << st.top() << '\n', st.pop();
	return 0;
}
```

---

## 作者：asas111 (赞：0)

## 前置知识
[并查集](https://www.luogu.com.cn/problem/solution/P3367)。

## 思路
看到求连通块数量，就想到并查集。删点并不好操作，所以就反过来一个个加点，最后正向输出就行了。

具体的操作是这样的：

- 先记录，因为题目要求的是 $i$ 号点删除后的连通块数量，相当于还没加 $i$ 号点时的连通块数量。

- 再增加连通块数量，因为这时 $i$ 号点还没连边，它自己算一个连通块。

- 最后遍历和 $i$ 号点连通的点，如果这个点比 $i$ 号点大（已经加了的点），而且和 $i$ 号点的祖先不同，就把它们合并，减少一个连通块。

时间复杂度是 $O(n\alpha(n))$，可以通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200009;
int n,m,fa[N],rk[N],cnt=0,ans[N];
vector<int> e[N];
int root(int x){return fa[x]==x?x:fa[x]=root(fa[x]);}//找祖先，路径压缩
void unite(int x,int y){
	int rx=root(x),ry=root(y);
	if(rx==ry)return;
	if(rx!=ry)
		if(rk[rx]<rk[ry])fa[rx]=ry;
		else{ 
			fa[ry]=rx;
			if(rk[rx]==rk[ry])rk[rx]++;
		}
}//秩合并
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);//建边
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++)fa[i]=i;//并查集初始化
	for(int i=n;i>=1;i--){
		ans[i]=cnt++;//记录，并增加连通块数量
		for(int j=0;j<e[i].size();j++)
			if(e[i][j]>i&&root(i)!=root(e[i][j])){//判断祖先是否不同
				cnt--;
				unite(i,e[i][j]);//合并
			}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return 0;
}
```


---

## 作者：flying_man (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc229_e)

------------
**题解部分：**

如果我们直接删边，然后对于每个状态 $O(n)$ 计算连通块，显然会超时。

删边这条路堵死了，我们可以考虑倒着做，进行加边处理。

然后加边和连通块放在一起想到了什么？

**并查集！**

并查集能很好的维护上述两种操作，而且速度飞快。

时间复杂度 $O(n)$。

------------
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200005;
int n,m,x,y,f[N],ans[N];
vector<int> p[N];
void in(int &s){
	char c;s = 0;
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
		s=s*10+c-'0',c = getchar();
}
int find(int x){
	if(f[x] != x) f[x] = find(f[x]);
	return f[x];
}
void unionn(int x,int y){
    x = find(x);y = find(y);
    f[y] = x;
}
int main(){
	in(n);in(m);
	for(int i = 1;i <= n;i++) f[i] = i;
	for(int i = 1;i <= m;i++){
		in(x);in(y);
		p[x].push_back(y);
		p[y].push_back(x);
	}
	ans[n] = 0;
	for(int i = n;i > 1;i--){
		ans[i-1] = ans[i]+1;
		for(int j = 0;j < p[i].size();j++){
			if(p[i][j] < i) continue;
			if(find(i) != find(p[i][j])) ans[i-1]--;
			i = find(i);p[i][j] = find(p[i][j]);
			f[p[i][j]] = i;
		}
	}
	for(int i = 1;i <= n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

