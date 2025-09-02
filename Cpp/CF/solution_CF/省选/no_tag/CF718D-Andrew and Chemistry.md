# Andrew and Chemistry

## 题目描述

During the chemistry lesson Andrew learned that the saturated hydrocarbons (alkanes) enter into radical chlorination reaction. Andrew is a very curious boy, so he wondered how many different products of the reaction may be forms for a given alkane. He managed to solve the task for small molecules, but for large ones he faced some difficulties and asks you to help.

Formally, you are given a tree consisting of $ n $ vertices, such that the degree of each vertex doesn't exceed $ 4 $ . You have to count the number of distinct non-isomorphic trees that can be obtained by adding to this tree one new vertex and one new edge, such that the graph is still the tree and the degree of each vertex doesn't exceed $ 4 $ .

Two trees are isomorphic if there exists a bijection $ f(v) $ such that vertices $ u $ and $ v $ are connected by an edge if and only if vertices $ f(v) $ and $ f(u) $ are connected by an edge.

## 说明/提示

In the first sample, one can add new vertex to any existing vertex, but the trees we obtain by adding a new vertex to vertices $ 1 $ , $ 3 $ and $ 4 $ are isomorphic, thus the answer is $ 2 $ .

In the second sample, one can't add new vertex to the first vertex, as its degree is already equal to four. Trees, obtained by adding a new vertex to vertices $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ are isomorphic, thus the answer is $ 1 $ .

## 样例 #1

### 输入

```
4
1 2
2 3
2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
1 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
2 5
5 3
4 3
4 1
```

### 输出

```
3
```

# 题解

## 作者：太阳起晚了呢 (赞：2)

# CF718D Andrew and Chemistry

## 题意

给你一个有 n 个点的树。当每一个点的度不超过 4 时这棵树是合法的。现在让你再添加一个点，在树仍然合法的情况下，一共有多少种树。

当两棵树同构时视作同一种。

保证输入的树是合法的。

## 思路

很显然，如果我们对于一个节点 A 再连接一个新的节点 B，如果以节点 A 作为根时哈希值与已经求出的其他节点哈希值相同，那么在 A 上连接一个 B 和在相同哈希值的节点上连接一个 B 显然是同构的，所以现在的问题转换为，对于原图中度数小于 4 的节点，让这些节点作为树的根求出的哈希值的值的数量。

于是这个问题成功地转换为树哈希模板题

看了一下其他题解的哈希做法，都是记忆化搜索做法，感觉没有我的优（毕竟去掉记忆化就是平方复杂度了），这里提供一种哈希方法，在线性复杂度内求出所有点的哈希值，使用了换根 DP。

哈希式子如下  


 $\large f_u=1 + \sum_{v\in son_u} f_v \times prime_{size_v}$
 

至于换根的话看代码吧，比较简单。

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
inline int read()
{
    int ret=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret;
}
const int maxn=1e5+10;
struct node
{
    int v,next;
}e[maxn<<1];
int cnt,head[maxn];
int n;
void add(int u,int v)
{
    e[++cnt].next=head[u];
    e[cnt].v=v;
    head[u]=cnt;
}
bool vis[maxn*15];
int p[maxn];
void prework(int n)
{
    int tot=0;
    for(int i=2;tot<=n;i++)
    {
        if(!vis[i]) p[++tot]=i;
        for(int j=1;j<=tot && i*p[j]<=maxn*15;j++)
        {
            vis[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}
ull f[maxn];
int sz[maxn];
void dfs(int u,int fa)
{
    sz[u]=f[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,u);
        f[u]+=f[v]*p[sz[v]];
        sz[u]+=sz[v];
    }
}
void dfs1(int u,int fa)
{
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].v;
        if(v==fa) continue;
        f[v]+=(f[u]-f[v]*p[sz[v]])*p[n-sz[v]];
        dfs1(v,u);
    }
}
int d[maxn];
set<ull> s;
int main()
{
    n=read();
    prework(n+1);
    for(int i=1,x,y;i<n;i++)
    {
        x=read();y=read();
        add(x,y);add(y,x);
        d[x]+=1;d[y]+=1;
    }
    dfs(1,0);dfs1(1,0);
    for(int i=1;i<=n;i++)
    {
        if(d[i]>=4) continue;
        s.insert(f[i]);
    }
    cout<<s.size()<<endl;
    return 0;
}
```

注意这种方法需要使用筛法求质数，需要点数个质数，在预处理的时候控制好范围。



---

## 作者：Zekrom (赞：2)

~~蓝题好像有些低了（树同构模板都紫题）~~    
## 记忆化搜索+树同构hash   
遍历每个度数小于4的节点，以子节点的hash值放在一个vector里作为自己的hash值，然后遍历子树记忆化搜索，将结果放在set里去重，输出即可    
上代码（码风应该还可以接受）    
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define inf 0x3f3f3f3f
#define N 100010
using namespace std;
int n,cnt,head[N],tot,d[N];
map<vector<int>,int>Hash;
map<int,int>mp[N];
set<int>ans;
struct Edge{
	int v,next;
}edge[N*2];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
inline void add(int x,int y){edge[++tot].v=y;edge[tot].next=head[x];head[x]=tot;d[x]++;}
int dp(int x,int fa){
	if(mp[x][fa])return mp[x][fa];
	vector<int>tmp;
	for(int i=head[x];i;i=edge[i].next){
		int v=edge[i].v;if(v==fa)continue;
		tmp.push_back(dp(v,x));
	}
	sort(tmp.begin(),tmp.end());
	if(!Hash[tmp])Hash[tmp]=++cnt;
	return mp[x][fa]=Hash[tmp];
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;i++){
		if(d[i]<4)
			ans.insert(dp(i,0));
	}
	printf("%d\n",ans.size());
	return 0;
}

```



---

## 作者：little_gift (赞：1)

莫名想做化学题.

很显然烷烃会是一棵树.

对于一个碳原子, 与它连接的氢原子都是等价的, 所以相应地取代哪个氢原子形成的一氯代物也都是同构的.

那么我们可以考虑把氯原子所连接的碳原子作为根把这棵无根树转化成有根树.

所以问题就转化为了

**给你一棵树, 分别把它的每个结点作为根, 所形成的不同构的有根树的数量.**

考虑hash.

因为每个碳原子最多连接四个碳原子.

那么可以先求出它的子树的hash值然后排序并拼接起来作为它自己的hash值.

显然这样hash值可能会非常大.

考虑某个初赛中出现过的字典存储方法, 把每个新出现的hash值都扔到map里并给它一个编号.

然后再给hash函数一个记忆化就可以过掉此题了.

~~复杂度? 复杂度不知道啊.~~

好像这个代码也给不了多少注释的样子.

~~第一次用vector存图(好像也是第一次写hash)请各位dalao轻喷~~

```cpp
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define _for(i, a, b) for (register int i = a; i < b; ++i)
#define _rep(i, a, b) for (register int i = a; i <= b; ++i)
const int ri_top = 1e7;
char ri[ri_top + 1], *rich = ri, *rr = ri;
inline void rd() {*(rr = ri + fread(rich = ri, 1, ri_top, stdin)) = 0;}
inline char nch() {if (++rich >= rr) rd(); return *rich;}
inline void read_int(int& x) {while (!isdigit(*rich)) nch(); for (x = *rich - '0'; isdigit(nch()); x = x * 10 + *rich - '0');}
std::vector<int> G[100001];
__gnu_pbds::tree<int, __gnu_pbds::null_type> S;
__gnu_pbds::tree<int, int>dp[100001]; //记忆化
__gnu_pbds::tree<int, int>::iterator it;
__gnu_pbds::tree<std::vector<int>, int>l; //hash映射到id
__gnu_pbds::tree<std::vector<int>, int>::iterator it1;
int cnt;
int dfs(const int& u, const int& fa)
{
    if ((it = dp[u].find(fa)) != dp[u].end()) return it->second; //记忆化
    std::vector<int> V;
    for (auto i : G[u]) if (i != fa) V.push_back(dfs(i, u));
    std::sort(V.begin(), V.end()); //将子树的hash值拼接起来并排序
    return dp[u][fa] = (((it1 = l.find(V)) != l.end()) ? it1->second : (l[V] = ++cnt)); //判断是否需要新建一个映射并返回
}
int n, u, v;
int main()
{
    read_int(n);
    _for(i, 1, n) {read_int(u); read_int(v); G[u].push_back(v); G[v].push_back(u);}
    _rep(i, 1, n) if (G[i].size() < 4) S.insert(dfs(i, 0)); //不能忽略对度数的判断. 只有连有氢原子的碳原子才可以被取代(仿佛不能说碳原子被取代那就是不能作为根)
    printf("%d\n", S.size()); //不同的hash值的个数.
}
```

---

## 作者：Erusel (赞：1)

题目要求我们快速求出加上一个点后树的哈希值

考虑到度数只有4很小，

我们可以用一个 ```vector``` 存下节点 $u$ 的每个儿子的哈希值，

去重前排序保证唯一，然后丢进 ```set``` 去重,

```set``` 的元素个数就是答案

**Code:**

```
#include<bits/stdc++.h>

#define rd(x) x=read()

#define N 100005

using namespace std;

int n,m;
vector<int>e[N];
map<vector<int>,int>h;
map<int,int>f[N];
set<int>s;
int tot;

inline void addEdge(int u,int v){e[u].push_back(v);}
 
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int dfs(int u,int fa)
{
	vector<int>rec;
	if(f[u][fa])return f[u][fa];
	for(int v:e[u]){if(v==fa)continue;rec.push_back(dfs(v,u));}
	sort(rec.begin(),rec.end());if(!h[rec])h[rec]=++tot;return f[u][fa]=h[rec];
}

int main()
{
	rd(n);for(int i=1,u,v;i<n;i++)rd(u),rd(v),addEdge(u,v),addEdge(v,u);
	for(int i=1;i<=n;i++){if(e[i].size()>=4)continue;s.insert(dfs(i,0));}
	cout<<s.size()<<endl;

    return 0;
}

```

---

## 作者：cannotdp (赞：0)

萌新刚学树哈希。

既然同构树只算一遍，那么很自然地想到判断树同构的树哈希。对于有根树，判断两棵树同构的条件是根的哈希值相同，于是先选定根节点跑一遍 dfs 然后进行一个换根，最后开个 map 记录一下每个节点的哈希值就可以了。

放一个模板链接。

[P5043 【模板】树同构](https://www.luogu.com.cn/problem/P5043)

我的树哈希写法参考了 [https://peehs-moorhsum.blog.uoj.ac/blog/7891](https://peehs-moorhsum.blog.uoj.ac/blog/7891)。

参考代码

```cpp
#include <bits/stdc++.h>
#define ll unsigned long long
#define PII pair<int, int>
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7, INF = 0x3f3f3f3f;
int n, m, tot, k, T, ans;
int head[N], ver[N * 2], nxt[N * 2];
int deg[N];
ll h[N], f[N];
map<ll, bool> mp;

void add(int x, int y) {
	ver[++tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}

ll H(ll x) {
	return x * x * x * 1237123 + 19491001;
}

ll F(ll x) {
	return H(x & ((1 << 31) - 1)) + H(x >> 31);
}

void dfs1(int x, int fa) {
	h[x] = 1;
	for(int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if(y == fa) continue;
		dfs1(y, x);
		h[x] += F(h[y]);
	}
}

void dfs2(int x, int fa, ll cnt) {
	f[x] = 1 + cnt;
	for(int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if(y == fa) continue;
		f[x] += F(h[y]);
	}
	for(int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if(y == fa) continue;
		dfs2(y, x, F(f[x] - F(h[y])));
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		add(x, y); add(y, x);
		deg[x]++, deg[y]++;
	}
	dfs1(1, 0);
	dfs2(1, 0, 0);
	for(int i = 1; i <= n; i++) {
		if(deg[i] >= 4) continue;
		if(!mp[f[i]]) ans++;
		mp[f[i]] = 1;
	}
	printf("%d", ans);
	return 0;
}

```


---

## 作者：JiaY19 (赞：0)

一道树哈希模板题。

由于度数很小，我们考虑直接搜索。

使用记搜，如果当前节点已经访问过就直接返回原来的值。

至于哈希的过程，我们考虑用 $\text{vector}$ 来存储。

每个 $\text{vector}$ 所存储的都是其儿子的哈希值，就可以不断递归向上合并。

为了减少常数，可以不选 $\text{map}$ 采用 $\text{pbds}$ 中 $O(1)$ 的 $\text{hash table}$

#### Code

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

const int maxn = 100010;

int n , cnt , tot , du[maxn] , head[maxn];

set<int> q;
map<vector<int> , int> Hash;
gp_hash_table<int , int> mp[maxn];

struct edge
{
	int to , nxt;
}e[maxn * 2];

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

inline void add(int x , int y)
{
	du[x]++ , du[y]++; 
	e[++cnt] = {y , head[x]} , head[x] = cnt;
	e[++cnt] = {x , head[y]} , head[y] = cnt;
}

inline int dfs(int now , int fa)
{
	if(mp[now][fa]) return mp[now][fa];
	vector<int> tmp;
	for(int i = head[now];i;i = e[i].nxt)
	{
		if(e[i].to == fa) continue;
		tmp.push_back(dfs(e[i].to , now));
	}
	sort(tmp.begin() , tmp.end());
	if(!Hash[tmp]) Hash[tmp] = ++tot;
	return mp[now][fa] = Hash[tmp];
}

int main()
{
    n = read();
    for(int i = 1;i < n;i++)
    {
    	int x = read() , y = read();
    	add(x , y);
	}
	for(int i = 1;i <= n;i++) if(du[i] < 4) q.insert(dfs(i , 0));
	cout << q.size();
    return 0;
}


```


---

