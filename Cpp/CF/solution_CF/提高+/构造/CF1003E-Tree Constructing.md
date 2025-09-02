# Tree Constructing

## 题目描述

给定三个整数 $n$、$d$ 和 $k$。

你的任务是构造一棵有 $n$ 个顶点的无向树，使其直径为 $d$，且每个顶点的度数不超过 $k$，或者判断这是不可能的。

无向树是一个连通的无向图，包含 $n-1$ 条边。

树的直径是该树中所有点对之间简单路径（即每个顶点最多出现一次的路径）的最大长度。

顶点的度数是与该顶点相连的边的数量（即对于顶点 $u$，是属于树的所有边 $(u, v)$ 的数量，其中 $v$ 是树中的任意其他顶点）。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 3 3
```

### 输出

```
YES
3 1
4 1
1 2
5 2
2 6
```

## 样例 #2

### 输入

```
6 2 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
10 4 3
```

### 输出

```
YES
2 9
2 10
10 3
3 1
6 10
8 2
4 3
5 6
6 7
```

## 样例 #4

### 输入

```
8 5 3
```

### 输出

```
YES
2 5
7 2
3 7
3 1
1 6
8 7
4 3
```

# 题解

## 作者：dalao_see_me (赞：7)

题目大意：构造一棵 $n$ 个节点的树，这棵树的直径 $\le d$ ，且每个节点的度数 $\le k$ 。

这题非常显然可以用贪心来解决。

首先我们先构造一条长度为 $d$ 的链，然后在上面“塞”点，并且满足题目所给的条件，再然后……就没有然后了。

具体怎么“塞”点呢？

我们可以用dfs来解决。~~dfs大法好。~~

对于每个点，如果把它加进去后可以满足条件，那么和之前的大连通块连一条边。如果不行的话，~~拜拜了您嘞。~~

然后我们就做完了。

## Code time

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+6;
int n,d,k,cnt,number;
int dgr[N],O[N];
struct lines{
	int x,to;
}e[N];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
inline void dfs(int x,int dad){
	if(number>n)return;
	if(dad!=0){
		dgr[x]++;
		O[x]=O[dad]-1;
		e[++cnt].x=x;
		e[cnt].to=dad;
	}
	if(!O[x])return;
	while(dgr[x]<k){
		dgr[x]++;
		dfs(++number,x);
	}
}
int main(){
	n=read();d=read();k=read();
	if(d>=n){//记得加特判，不然死的惨
		puts("NO");
		return 0;
	}
	if(k==1&&n>2){
		puts("NO");
		return 0;
	}
	for(int i=1;i<=d;i++){
		dgr[i]++;
		dgr[i+1]++;
		e[++cnt].x=i;
		e[cnt].to=i+1;
		O[i]=min(i-1,d-i+1);
	}
	number=d+1;
	for(int i=2;i<=d;i++)
		dfs(i,0);
	if(number<n)puts("NO");
	else{
		puts("YES");
		for(int i=1;i<=cnt;i++)printf("%d %d\n",e[i].x,e[i].to);
	}
	return 0;
}
```


---

## 作者：Diaоsi (赞：3)

## 题意：

构造一棵 $n$ 个节点的树，使得这棵树的直径小于等于 $d$ ，且每个节点的度数小于等于 $k$ 。

## 思路：

贪心构造，首先构造出该树的最长链，即一条长度为 $d$ 的链。

为了使构造的树的最长链不超过 $d$ ，对于当前最长链上的任意一个节点，该节点所能连接的最长链的长度是确定的。

举个例子：

![链](https://cdn.luogu.com.cn/upload/image_hosting/0sc2wac3.png)

括号内的数即为该点能链接的最长的链的长度，若挂更长的链就会使整棵树的最长链超过 $d$ 。

为了尽量挂更多的点，将该链上的每个点都尽可能地挂更多的链，直到该点的度数达到 $k$ 。

将最长链挂满后，对于新接上的节点也可以按照上面的方法去处理，直到挂到 $n$ 个节点为止，具体实现可以使用递归。

可以使用一个栈去维护未使用的点集，当按照上述方法将节点挂满后，栈仍不为空即为无解。

小清新构造题~

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=400010,M=4000010,INF=0x3f3f3f3f;
int head[N],ver[M],Next[M],tot;
int n,m,d,k,deg[N],vis[N],v[N];
stack<int> s;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int &x,int &y){x^=y^=x^=y;}
void add(int x,int y){
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
}
void dfs1(int x,int fa){
	int ind=deg[x];v[x]=1;
	if(vis[x]){
		for(int i=ind;i<=k;i++){
			if(deg[x]==k)break;
			if(!s.size())break;
			int y=s.top();s.pop();
			add(x,y),add(y,x);
			++deg[x],++deg[y];
			vis[y]=vis[x]-1;
		}
		vis[x]=0;
	}
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(v[y])continue;
		dfs1(y,x);
	}
}
void dfs2(int x,int fa){
	v[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(v[y])continue;
		printf("%d %d\n",x,y);
		dfs2(y,x);
	}
}
int main(){
	scanf("%d%d%d",&n,&d,&k);
	for(int i=n;i>=1;i--)s.push(i);
	for(int i=1;i<=d;i++){
		if(i+1>n){puts("NO");return 0;}
		add(i,i+1),add(i+1,i);
		++deg[i],++deg[i+1];
		if(deg[i]>k){puts("NO");return 0;}
		vis[i]=Min(i-1,d-i+1);
		if(s.size())s.pop();
	}
	if(s.size())s.pop();
	int root=d/2+1;
	dfs1(root,0);
	if(s.size())puts("NO");
	else{
		puts("YES");
		memset(v,0,sizeof(v));
		dfs2(root,0);
	}
	return 0;
}
```



---

## 作者：y1朵小寒 (赞：3)

 题意：构建一棵满足以下条件的树,并输出树的边连接关系。
        条件一: 树有n个结点
		条件二：最长路径不超过d
		条件三：每个结点的度数不大于k
		
		
  分类：贪心+dfs
  
  
  题解：先构建一棵深度为d的树K,尽可能的让深度小的结点挂的子树$K_i$结点多，若没有把n个结点挂上
  树又或者某个结点的度数大于k，输出no，否则输出yes
  
  
  坑点:注意一下，把剩下结点(1~n)挂入到树的时候,结点编号一定是在1~n
  
  
  ```
#include <bits/stdc++.h>
using namespace std;
const int mmax = 4*1e5+10;

int id,n,dia,k,dg[mmax],af,pt; //af     ansflag
vector< pair<int,int> > Edge;

void dfs(int u ,int dep, int mxdep){

     if(dep == mxdep ) return;
     for(int i = 0 ; i < k - 1 -(dep == 0)  &&  id <= n ;i++){
            if(id+1 <= n){
                 Edge.push_back(make_pair(u,++id));
                 dg[u]++,dg[id]++;
                 dfs(id,dep+1,mxdep);
            }
            else return ;
     }
}

int main(){
    af = 1;
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> dia >> k;
    pt = dia+1;
    if( pt > n )   cout << "NO" << endl;  //需要的点大于现在拥有的点
    else{
        for(int i = 1 ; i <= dia ; i++)  {  Edge.push_back(make_pair(i,i+1)); dg[i]++,dg[i+1]++; }
        id = pt;
        for(int i = 2 ; i <= pt-1 ; i++ ) { dfs(i,0,min(i-1,pt-i));}
        for(int i = 1 ; i <= pt ; i++)  if(dg[i] > k ) af = 0;
        if(af == 0 || id < n ) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            for(auto i : Edge) {  cout << i.first << " " << i.second << endl; }
        }
    }

}


```

---

## 作者：yimuhua (赞：2)

## 题意

构造一棵 $n$ 个节点的树，满足其直径 $\leq d$，每个点的度数 $\leq k$。

## 思路

贪心。

先构造出一条长为 $d$ 的直径，然后从中间折开两边分别加点。若度数 $<k$ 就加一条连向原链上的边，尽可能挂，过程中判无解，边够了就输出。

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> a, v[400005];
int n, d, k, p, m, in[400005], dep[400005];
void add(int x, int y) {
    in[x]++, in[y]++, v[x].push_back(y), dep[y] = dep[x] + 1;
    return;
}
void print() {
    cout << "YES\n";
    for(int i = 1; i <= n; i++)
        for(int j : v[i])
            cout << i << ' ' << j << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> d >> k, p = n + 1, m = d / 2;
    if(d >= n) {
        cout << "NO";
        return 0;
    }
    if(d == 1) {
        if(n ^ 2)
            cout << "NO";
        else
            cout << "YES\n1 2";
        return 0;
    }
    if(k == 1) {
        cout << "NO";
        return 0;
    }
    for(int i = 2; i < m + 2; i++)
        add(i - 1, i);
    add(1, m + 2);
    for(int i = m + 3; i < d + 2; i++)
        add(i - 1, i);
    for(int i = m + 2; i <= d; i++)
        if(in[i] < k)
            a.push_back(i);
    for(int i = d + 2; i <= n; i++) {
        if(a.empty()) {
            p = i;
            break;
        }
        int tmp = a.back();
        add(tmp, i);
        if(in[tmp] == k)
            a.pop_back();
        if(dep[i] < d - m)
            a.push_back(i);
    }
    if(p == n + 1) {
        print();
        return 0;
    }
    for(int i = 1; i < m + 2; i++)
        if(in[i] < k && dep[i] < m)
            a.push_back(i);
    for(int i = p; i <= n; i++) {
        if(a.empty()) {
            cout << "NO";
            return 0;
        }
        int tmp = a.back();
        add(tmp, i);
        if(in[tmp] == k)
            a.pop_back();
        if(dep[i] < m)
            a.push_back(i);
    }
    print();
    return 0;
}
```


---

## 作者：灵茶山艾府 (赞：2)

基本思想是先把直径画出来，然后从直径上的点长出树枝。

对于直径上的点 $v$，记其到直径两端点的最小距离为 $l$，则可以从点 $v$ 上长出长度至多为 $l$ 的树枝。

可以用一个 DFS 来实现长树枝的过程：`dfs(v,l)` 表示从 $v$ 长出树枝，剩余长度为 $l$。DFS 中维护一个全局变量 $cur$ 表示新长出的树枝为 $v-cur$。

那么，对直径上的非端点调用 `dfs(v,l)`，在递归内部调用 `dfs(cur++,l-1)` 即可完成这棵树的构建。

几个需要注意的点：

1. 直径必须小于节点数量；
2. 直径大于 $1$ 时，$k$ 必须大于 $1$；
3. DFS 过程中，直径上的非端点可以添加 $k-2$ 条边，非直径上的点可以添加 $k-1$ 条边；

AC 代码 (Golang)：

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	type edge struct{ v, w int }

	var n, d, k int
	Scan(&n, &d, &k)
	if d >= n || d > 1 && k == 1 {
		Fprint(out, "NO")
		return
	}

	es := []edge{}
	cur := d + 2
	var dfs func(v, l int)
	dfs = func(v, l int) {
		i := 1
		if v <= d {
			i = 2
		}
		for ; l > 0 && i < k && len(es) < n-1; i++ {
			w := cur
			cur++
			es = append(es, edge{v, w})
			dfs(w, l-1)
		}
	}
	for i := 1; i <= d; i++ {
		es = append(es, edge{i, i + 1})
	}
	for i := 2; i <= d; i++ {
		dfs(i, min(i-1, d+1-i))
	}
	if len(es) < n-1 {
		Fprint(out, "NO")
		return
	}
	Fprintln(out, "YES")
	for _, e := range es {
		Fprintln(out, e.v, e.w)
	}
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
```


---

## 作者：__Deng_Rui_Song__ (赞：1)

# presafe
一道不错的构造题，值得让我们~~吃葡萄~~ 
# problem
[传送门](https://www.luogu.com.cn/problem/CF1003E)

[题意](https://www.luogu.com.cn/discuss/866383)
# solution
首先构造长度为 $d$ 的一条链，其次给链上的所有点加边，~~这有点像挂葡萄~~，大概长下面这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/bgynw98s.png)

~~问与答~~

q：怎么挂葡萄？

a：带分数（dfs）

# code
```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge {
  int x, y;
} e[400005];
int n, d, k, cur, cnt, maxdep;
void dfs(int fa, int dep) {
  if (dep > maxdep) return;
  for (int i = 1; i < k - (fa <= d + 1); i++) {
    if (cur == n) {
      cout << "YES\n";
      for (int i = 1; i < n; i++) cout << e[i].x << ' ' << e[i].y << '\n';
      exit(0);
    }// 如果挂了 n 个葡萄，就合法，下面同理
    e[++cnt] = {fa, ++cur};
    if (cur == n) {
      cout << "YES\n";
      for (int i = 1; i < n; i++) cout << e[i].x << ' ' << e[i].y << '\n';
      exit(0);
    }
    dfs(cur, dep + 1);
    if (cur == n) {
      cout << "YES\n";
      for (int i = 1; i < n; i++) cout << e[i].x << ' ' << e[i].y << '\n';
      exit(0);
    }
  }
}
int main() {
  cin >> n >> d >> k;
  if (d >= n || (k == 1 && n > 2)) {
    cout << "NO";
    return 0;
  }// 特判
  for (int i = 1; i <= d; i++) e[++cnt] = {i, i + 1};// 建链
  cur = d + 1;
  if (cur == n) {
    cout << "YES\n";
    for (int i = 1; i < n; i++) cout << e[i].x << ' ' << e[i].y << '\n';
    return 0;
  }
  for (int i = 1; i <= d + 1; i++) {
    maxdep = min(i - 1, d + 1 - i);// 限制深度
    dfs(i, 1);
  }
  cout << "NO";// 非法
  return 0;
}
```

[AC 记录](https://vjudge.net/solution/56827868/q9Xpln6NYpkblThBiWre)

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑先将树的直径构造出来，即先构造出一条由 $d+1$ 个点组成的长度为 $d$ 的链，然后在这条链上加点，看能否能将 $n$ 个点都放进去。

一个朴素的贪心是：

- 以 $\lfloor \frac{d}{2} \rfloor + 1$ 为根，这样会使得尽量平衡。

- 若当前点的度数没有达到 $k$ 的限制，则可以一直加点。

- 若当前点的深度到了 $\lfloor \frac{d}{2} \rfloor$ 则不能加点了。

注意一下，当 $d$ 为奇数的时候，$rt$ 的右边的深度较深一层，则对于 $rt \sim d+1$ 号点延伸出来新加的点可以达到 $\lfloor \frac{d}{2} \rfloor +1$。

最后若当前树上的点数没有到达 $n$，且无法再次加点，就无解。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=4e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,d,k,rt,cnt;
ll du[N];
vector<pi> ans;
vector<ll> E[N];
void add(ll u,ll v){
	ans.push_back({u,v});
	E[u].push_back(v);
	E[v].push_back(u);
	du[u]++,du[v]++;
}
void Newadd(ll u){
	while(du[u]<k&&cnt<n){
		++cnt;
		add(u,cnt);
	}
}
void dfs(ll u,ll fa,ll dep,ll low){
	if(dep==low)
	  return ;
	Newadd(u);
	for(auto v:E[u]){
		if(v==fa)
		  continue;
		if(u==rt&&v>u&&(d&1ll)&&v<=d+1)
		  dfs(v,u,dep+1,low+1);
		else
		  dfs(v,u,dep+1,low);
	}
}
bool End;
int main(){
	n=read(),d=cnt=read(),k=read(),rt=d/2+1;
	++cnt;
	for(int i=2;i<=d+1;i++)
	  add(i,i-1);
	dfs(rt,0,0,d/2);
	for(int i=1;i<=n;i++){
		if(du[i]>k){
			puts("NO");
			exit(0);			
		}
	}
	if(cnt!=n){
		puts("NO");
		exit(0);
	}
	puts("YES");
	for(auto t:ans){
		write(t.fi);
		putchar(' ');
		write(t.se);
		putchar('\n');
	}
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

简单构造题，不知道如何评到了 $\orange{2100}$。

首先构造出一条 $d+1$ 个点的链，满足直径的长度为 $d$。

然后在这一条链上放结点。首先两头的结点肯定不能添加结点了。其他的结点都可以再添加最多 $k-2$ 个结点。

对于新添加的结点。其目前的唯一一个与其连接的结点 $D$ 的最多可以添加的深度为 $\min(n-1,d-i)-1$。每一个结点可以衍生出最多 $k-1$ 个结点并满足条件。暴力递归实现即可。注意一下细节很多。

最后还是放一下很抽象的代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500100;
vector<int> z[N];
int deg[N], quan[N], remain, idx, n, d, k;
void dfs(int u, int len) {
    // cout << "dbg " << u << ' ' << len << '\n';
    if (0 >= len) return;
    if (idx == n) return;
    // 这个点可以连 k-1 个新的点
    for (int i = 1; i < k; ++i) {
        ++idx, z[u].emplace_back(idx), z[idx].emplace_back(u), ++deg[u], ++deg[idx];
        dfs(idx, len - 1);
        if (idx == n) break;
    }
}
int id;
int dis[N], vis[N];
void bfs(int st) {
    memset(dis, 0x3f, sizeof dis);
    queue<int> q; q.push(st); vis[st] = 1, dis[st] = 0;
    while (q.size()) {
        int f = q.front(); q.pop(); vis[f] = 0;
        for (auto &v : z[f]) if (dis[v] > dis[f] + 1) {
            dis[v] = dis[f] + 1;
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    id = -233;
    for (int i = 1; i <= n; ++i)
        if (id == -233 || dis[i] > dis[id]) id = i;
}
int f[N][20], yhb[N];
void dfss(int u, int fa) {
    f[u][0] = fa, yhb[u] = yhb[fa] + 1;
    for (auto &v : z[u]) if (v != fa) dfss(v, u);
}
int lca(int u, int v) {
    if (yhb[u] < yhb[v]) swap(u, v);
    int delta = yhb[u] - yhb[v];
    for (int i = 0; i < 20; ++i) if (delta >> i & 1) u = f[u][i];
    if (u == v) return u; for (int i = 19; ~i; --i)
        if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return f[u][0];
}
int qwq(int a, int b) {
    return yhb[a] + yhb[b] - 2 * yhb[lca(a, b)];
}
signed main() {
    scanf("%lld%lld%lld", &n, &d, &k);
    ++d;
    if (k == 1) {
        if (n == 2 && n == d) {
            puts("YES");
            if (n == 2) printf("1 2\n");
        } else puts("NO");
    } else {
        if (n <= d) {
            if (n == d) {
                puts("YES");
                for (int i = 1; i < n; ++i) printf("%lld %lld\n", i, i + 1);
            } else puts("NO");
        } else {
            for (int i = 1; i < d; ++i) z[i].emplace_back(i + 1), z[i + 1].emplace_back(i), ++deg[i], ++deg[i + 1];
            if (k == 2) {
                puts("NO");
                return 0;
            }
            remain = n - d, idx = d;
            for (int i = 2; i < d; ++i) {
                int pcnt = min(i - 1, d - i);
                // 初始结点可以构造 k-2 个结点
                for (int j = 0; j < k - 2; ++j) {
                    ++idx, --remain;
                    deg[idx] = 1, ++deg[i];
                    quan[idx] = pcnt - 1;
                    z[i].emplace_back(idx), z[idx].emplace_back(i);
                    if (!remain) break;
                }
                if (!remain) break;
            }
            if (!remain) {
                bfs(1);
                int st = id;
                bfs(st);
                int st2 = id;
                dfss(1, 0);
                for (int i = 1; i < 20; ++i)
                    for (int j = 1; j <= n; ++j)
                        f[j][i] = f[f[j][i - 1]][i - 1];
                if (qwq(st, st2) == d - 1) {
                    puts("YES");
                    for (int i = 1; i <= n; ++i) {
                        for (auto &j : z[i])
                            if (i < j) printf("%lld %lld\n", i, j);
                    }
                } else puts("NO");
                return 0;
            }
            int tx = idx;
            for (int i = d + 1; i <= tx; ++i)
                if (quan[i]) {
                    dfs(i, quan[i]);
                    // for (int i = 1; i <= n; ++i)
                    //     for (auto &j : z[i])
                    //         if (i < j) cout << i << ' ' << j << '\n';
                    if (idx == n)
                        break;
                }
            if (idx == n) {
                bfs(1);
                int st = id;
                bfs(st);
                int st2 = id;
                dfss(1, 0);
                for (int i = 1; i < 20; ++i)
                    for (int j = 1; j <= n; ++j)
                        f[j][i] = f[f[j][i - 1]][i - 1];
                if (qwq(st, st2) == d - 1) {
                    puts("YES");
                    int qwq = n - 1;
                    for (int i = 1; i <= n; ++i)
                        for (auto &j : z[i]) {
                            if (i < j && i <= n && j <= n) printf("%lld %lld\n", i, j), --qwq;
                            if (!qwq) goto ee;
                        }
                } else puts("NO");
                ee:;
            } else {
                puts("NO");
            }
        }
    }
}
```

还有 [AC 记录](https://www.luogu.com.cn/record/166484028)。

---

## 作者：mango2011 (赞：0)

贡献一发递归构造的题解。

注意特判 $k=1$ 和 $d\ge n$ 的情形。

看到这个题目，我们首先可以想到把这条直径用 $1\sim d+1$ 连接出来（第 $i$ 个点连向第 $i+1$ 个点）。

对于第 $i$ 个点（$2\le i\le d$），我们考虑将其价值最大化：

现在设以 $i$ 为根，那么我们可以在原本的直径之外，新构造一棵树，显然，这棵树的深度不超过 $\min(i-1,d+i-1)$（不改变直径长短），根节点最多有 $k-2$ 个儿子；非根节点最多有 $k-1$ 个儿子，我们尝试取满，利用递归的方法，贪心构造即可。

这道题目就做完啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> >v;
int now=0,n;
void go(int u,int deg,int o,bool mark){
    if(!o){
        return;
    }
    if(now>=n){
        return;
    }
    for(int i=1;i<=deg;i++){
        if(now<n){
            now++;
            v.push_back({u,now});
            go(now,deg+mark,o-1,0);
        }
        else{
            break;
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
    int d,k;
    cin>>n>>d>>k;
    if(d>=n){
        cout<<"NO"<<endl;
        return 0;
    }
    if(k==1){
        if(n<=2){
            cout<<"YES"<<endl;
            if(n==2){
                cout<<"1 2"<<endl;
            }
        }
        else{
            cout<<"NO"<<endl;
        }
        return 0;
    }
    for(int i=1;i<=d;i++){
        v.push_back({i,i+1});
    }
    now=d+1;
    for(int i=2;i<=d;i++){
        go(i,k-2,min(i-1,d+1-i),1);
    }
    if(now==n){
        cout<<"YES"<<endl;
        for(auto e:v){
            cout<<e.first<<' '<<e.second<<endl;
        }
    }
    else{
        cout<<"NO"<<endl;
    }
    return 0;
}

```

---

## 作者：ifffer_2137 (赞：0)

小清新图论构造题捏~
### 题意
给定点数 $n$，直径长度 $d$ 和度数上限 $k$，构造一棵合法的树。
### 分析
直径为 $d$，先连出一条长度为 $d$ 的链，再考虑把剩下的点挂上去，同时注意控制直径不改变。

设最初连好的链编号为 $1$ 到 $d+1$，$1$ 和 $d+1$ 这两个点肯定是不能再挂点上去了。那么对于上面其他的一个点 $i$，为了使直径长度不变，往外延申的新点深度最多不能超过 $\min(i-1,d+1-i)$。这个可以画图理解一下，往外延申太多就会超过直径了。

然后我们控制最大深度，只要贪心地尽量挂上更多的的点，到 $n$ 的时候停止就行了，可以直接暴力搜一下，每个点度数挂满就可以了。

具体可以看一下代码，去掉了一些头。
### 代码
```cpp
int n,d,k;
int cnt;
vector<pii> tr;
void print(){
	puts("YES");
	for(pii e:tr) cout<<e.fir<<" "<<e.sec<<endl;
	exit(0);
}
void dfs(int u,int x){
	if(x<=0) return;
	for(int i=1;i<k;i++){
		tr.eb(mkpr(u,++cnt));
		if(cnt==n) print();
		dfs(cnt,x-1);
	}
}
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),d=read(),k=read();
	if(n<=d||(k==1&&d>1)){ puts("NO"); return 0; }
	for(int i=1;i<=d;i++) tr.eb(mkpr(i,i+1));
	cnt=d+1;
	if(cnt==n) print();
	for(int i=2;i<=d;i++){
		int mx=min(i-1,d+1-i);
		for(int j=1;j<=k-2;j++){
			tr.eb(mkpr(i,++cnt));
			if(cnt==n) print();
			dfs(cnt,mx-1);
		}
	}
	puts("NO");
	return 0;
}
```

---

## 作者：tidongCrazy (赞：0)

在对于这一类条件与直径长度，点的度数的构造图问题，我们可以采用贪心的策略。

以此题为例，我们先构造出一条长度为 $d$ 的直径，然后考虑对非直径端点的点挂点。

一个显然的结论是非直径端点的点上挂点的最大层数为其距离两直径端点距离的最小值。

这点显然不挂白不挂，所以我们对于每一个点尽量把它的层数挂满。

我们可以开一个 vector 维护第 $i$ 层的点，然后处理第 $i+1$ 层的点，对于每一个第 $i$ 层的点，我们可以挂 $k-1$ 个点给它。特殊地，对于给直径上的点挂点，我们只能挂 $k-2$ 个点给它。

我们只需要挂满 $n$ 个点就能直接结束，所以时间复杂度完全没有问题。

当我们进行完操作还挂不够 $n$ 个点的话则无解。

$k=1$ 或 $k=2$ 的情况可以特判一下。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ins insert
#define pb push_back
#define IT set<int>::iterator
#define RIT set<int>::reverse_iterator

inline int read() {
	
	int w = 1, s = 0; char c;
	while(!isdigit(c = getchar())) if(c == '-') w = -1;
	while(isdigit(c)) s = (s << 1) + (s << 3) + (c & 15), c = getchar();
	return s * w;
}

void write(int x) {
	
	if(x < 0) x = -x, putchar('-');
	if(x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

inline void writeln(int x) { write(x); putchar('\n'); }
inline void writel(int x) { write(x); putchar(' '); }

inline int chkmax(int x, int y) { return x > y ? x : y; }
inline int chkmin(int x, int y) { return x < y ? x : y; }
inline void Swap(int &x, int &y) { x ^= y ^= x ^= y; }

const int N = 4e5 + 10;

int n, d, k;

vector<pair<int, int> > ans;
vector<int> qwq;

inline void work() {
	
	n = read(); d = read() + 1; k = read();
	if(k == 1 && n > 2) return printf("NO\n"), void();
	if(n < d) return printf("NO\n"), void();
	for(int i = 1; i < d; i ++ ) ans.pb(make_pair(i, i + 1));
	int st = d;
	if(st == n) {
		printf("YES\n");
		for(pair<int, int> qwq : ans) writel(qwq.first), writeln(qwq.second);
		return ;
	} for(int i = 2; i <= d - 1; i ++ ) {
		int minn = chkmin(i - 1, d - i);
		int res = k - 2; qwq.clear();
		if(res <= 0) continue;
		qwq.pb(i);
		for(int j = 1; j <= minn; j ++ ) {
			int lst = st + 1;
			for(int v : qwq) {
				int tot = res;
				while(tot -- ) {
					ans.pb(make_pair(v, ++ st));
					if(st == n) break;
				} if(st == n) break;
			} if(st == n) break;
			res = k - 1; qwq.clear();
			for(int t = lst; t <= st; t ++ ) qwq.pb(t);
		} if(st == n) break;
	} if(st < n) return printf("NO\n"), void();
	printf("YES\n");
	for(pair<int, int> qwq : ans) writel(qwq.first), writeln(qwq.second);
	return ;
}

signed main() {
	
	int T = 1;
	while(T -- ) work();
	return 0;
}
```

这里还有一道题，和这道题的贪心策略很像。

[CF1082D](https://www.luogu.com.cn/problem/CF1082D)

---

## 作者：Nightingale_OI (赞：0)

让你构造一棵 $ n $ 个节点，直径为 $ d $ ，每个点的度最打为 $ k $ 的树。

------------

首先我们可以尝试构造一条长度为 $ d $ 的链，再在上面挂节点。

具体可以记录每个节点的度数和以它为起点的最长链。

看再加入一个节点连向它是否符合要求。

每个可能的节点可以用任意数据结构维护，这里用的是队列。

------------

代码如下 （~~非常简单~~)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
int ds[404040];
int de[404040];
int fa[404040];
queue<int>q;
int main(){
    cin>>n>>m>>s;
    if(n==1){
        if(m)printf("NO\n");
        else printf("YES\n");
        return 0;
    }
    if(n<=m){
        printf("NO\n");
        return 0;
    }
    if(s==1){
        if(n==2 && m==1)printf("YES\n1 2\n");
        else printf("NO\n");
        return 0;
    }
    l=0;
    for(register int i=0;i<=m;++i){
        ++l;--n;
        if(i*2<=m)de[l]=(m>>1)-i;
        else de[l]=i-((m+1)>>1);
        if(i==0 || i==m)ds[l]=1;
        else ds[l]=2;
        if(i)fa[l]=l-1;
        else fa[l]=l;
        if(de[l]<de[1])q.push(l);
    }
    while(n--){
        while(q.size() && ds[q.front()]==s)q.pop();
        if(!q.size()){
            printf("NO\n");
            return 0;
        }
        ds[++l]=1;
        ++ds[q.front()];
        fa[l]=q.front();
        de[l]=de[q.front()]+1;
        if(de[l]<de[1])q.push(l);
    }
    printf("YES\n");
    for(register int i=2;i<=l;++i)printf("%d %d\n",i,fa[i]);
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：0)

## CF1003E Tree Constructing

### 题意

给定整数 $n,d,k$，你需要构造一棵 $n$ 个节点的树，满足直径长（边数）为 $d$，每个点度数不超过 $k$。

### 题解

直接构造 ~~题目名称都明说了~~。

首先如果 $d\ge n$，直接无解。

否则我们可以先搞出一条点数为 $d+1$ 的链，然后在上面加点。

对于里面中间的点，可以在上面加点。

加的时候要注意度数和直径长度限制。

当加到 $n$ 个点的时候，输出就可以了。如果怎么加也加不到，当然也就无解了。

### Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=400005;
int n,d,k;
vector<pair<int,int> >E;
int nc;
void calc(int maxd,int dep,int fa)
{
	E.push_back(make_pair(fa,++nc));
	if(nc==n)
	{
		puts("YES");
		for(pair<int,int>i:E)printf("%d %d\n",i.first,i.second);
		exit(0);
	}
	if(dep==maxd)return;
	int nnc=nc;
	for(int i=1;i<=k-1;i++)calc(maxd,dep+1,nnc);
}
int main()
{
	cin>>n>>d>>k;
	if(d>=n)return puts("NO"),0;
	if(d==1||k==1)
	{
		if(n>2)return puts("NO"),0;
		else if(d==1)return puts("YES\n1 2"),0;
	}
	nc=d+1;
	for(int i=1;i<=d;i++)E.push_back(make_pair(i,i+1));
	if(nc==n)
	{
		puts("YES");
		for(pair<int,int>i:E)printf("%d %d\n",i.first,i.second);
		exit(0);
	}
	for(int i=2;i<=d;i++)
		for(int j=3;j<=k;j++)calc(min(d-i+1,i-1),1,i);
	return 0;
}
```

---

