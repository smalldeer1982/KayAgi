# Gourmet choice

## 题目描述

Mr. Apple, a gourmet, works as editor-in-chief of a gastronomic periodical. He travels around the world, tasting new delights of famous chefs from the most fashionable restaurants. Mr. Apple has his own signature method of review — in each restaurant Mr. Apple orders two sets of dishes on two different days. All the dishes are different, because Mr. Apple doesn't like to eat the same food. For each pair of dishes from different days he remembers exactly which was better, or that they were of the same quality. After this the gourmet evaluates each dish with a positive integer.

Once, during a revision of a restaurant of Celtic medieval cuisine named «Poisson», that serves chestnut soup with fir, warm soda bread, spicy lemon pie and other folk food, Mr. Apple was very pleasantly surprised the gourmet with its variety of menu, and hence ordered too much. Now he's confused about evaluating dishes.

The gourmet tasted a set of $ n $ dishes on the first day and a set of $ m $ dishes on the second day. He made a table $ a $ of size $ n \times m $ , in which he described his impressions. If, according to the expert, dish $ i $ from the first set was better than dish $ j $ from the second set, then $ a_{ij} $ is equal to ">", in the opposite case $ a_{ij} $ is equal to "<". Dishes also may be equally good, in this case $ a_{ij} $ is "=".

Now Mr. Apple wants you to help him to evaluate every dish. Since Mr. Apple is very strict, he will evaluate the dishes so that the maximal number used is as small as possible. But Mr. Apple also is very fair, so he never evaluates the dishes so that it goes against his feelings. In other words, if $ a_{ij} $ is "<", then the number assigned to dish $ i $ from the first set should be less than the number of dish $ j $ from the second set, if $ a_{ij} $ is ">", then it should be greater, and finally if $ a_{ij} $ is "=", then the numbers should be the same.

Help Mr. Apple to evaluate each dish from both sets so that it is consistent with his feelings, or determine that this is impossible.

## 说明/提示

In the first sample, all dishes of the first day are better than dishes of the second day. So, the highest score will be $ 2 $ , for all dishes of the first day.

In the third sample, the table is contradictory — there is no possible evaluation of the dishes that satisfies it.

## 样例 #1

### 输入

```
3 4
>>>>
>>>>
>>>>```

### 输出

```
Yes
2 2 2 
1 1 1 1 
```

## 样例 #2

### 输入

```
3 3
>>>
<<<
>>>```

### 输出

```
Yes
3 1 3 
2 2 2 
```

## 样例 #3

### 输入

```
3 2
==
=<
==```

### 输出

```
No
```

# 题解

## 作者：lenlen (赞：9)

### Problem

题目大意：给你对于任意一个 $a_i$ 与 $b_j$ 的大小关系的判断，让你构造一个 $a,b$ 序列满足条件。

数据范围： $n,m \leq 1000$。

### Solution

这种考并查集的类似题目有很多很多（话说回来我在 CF 2000 左右 DP 里面看到的这个题，可是这个题跟 DP 有什么关系），这个题就是 **并查集+拓扑排序** 就能解决。

首先我们考虑相等的情况，所有相等的编号我们将他们合成一个点就可以了（用并查集维护），对于每一个连通块，我们只需要记录其中的一个编号就好，之后的操作在这个编号上进行。然后对于 $>,<$，我们从小的编号向大的编号连边，然后进行拓扑排序，顺便进行赋值就好。

每更新一个节点我们就让计数器 $num+1$，若最后 $num \not=$ 连通块数（**并非总结点数 $n+m$**，我们可以把一个连通块看作一个点来进行更新与操作），那么显然就矛盾了，不成立。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=7232;
int n,m,fa[N],du[N],num,sum;
long long dis[N];
string s[N];
int getfa(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=getfa(fa[fa[fa[fa[x]]]]);
}
void merge(int u,int v)
{
    int fu=getfa(u),fv=getfa(v);
    fa[fu]=fv;
}
struct hl{
    int v,nxt;
}e[N*N/10];//应该要开到 n*m 大小，因为这个 RE 了好多次
int h[N],cnt;
void add(int u,int v)
{
    du[v]++;
    e[++cnt].v=v;e[cnt].nxt=h[u];h[u]=cnt;
}
long long mx(long long x,long long y)
{
    return x>y?x:y;
}
queue<int> q;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+m;i++) fa[i]=i;
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];s[i]='?'+s[i];
        for(int j=1;j<=m;j++) if(s[i][j]=='=') merge(i,n+j);
    }
    //先用并查集维护出连通块，在进行连边
    for(int i=1;i<=n;i++) 
    for(int j=1;j<=m;j++) 
    {
        if(s[i][j]=='>') add(getfa(j+n),getfa(i));//连边
        else if(s[i][j]=='<') add(getfa(i),getfa(j+n));
    }
    for(int i=1;i<=n+m;i++) 
    if(fa[i]==i) 
    {
        if(!du[i]) dis[i]=1ll,q.push(i);
        ++sum;//记录总连通块数
    }
    while(!q.empty())//拓扑排序
    {
        int tmp=q.front();q.pop();++num;//弹出一个连通块，计数器 sum++
        for(int i=h[tmp];i;i=e[i].nxt)
        {
            dis[e[i].v]=mx(dis[e[i].v],dis[tmp]+1);
            du[e[i].v]--;
            if(!du[e[i].v]) q.push(e[i].v);
        }
    }
    if(num!=sum) printf("No\n");
    else
    {
        printf("Yes\n");
        for(int i=1;i<=n;i++) printf("%lld ",dis[getfa(i)]);
        puts("");
        for(int i=n+1;i<=n+m;i++) printf("%lld ",dis[getfa(i)]);
    }
}
```


---

## 作者：RiverFun (赞：5)

来一波广告：[$\texttt{BLOG}$](https://stevebraveman.github.io/)

# 并查集 + 拓扑排序

那么我们该怎样用并查集和拓扑排序呢

思路很简单，把标有`=`的i和j放在同一个并查集内，然后根据题意连边，如果是`>`，就这么连：i所在集合的标号 -> j所在集合的标号，如果是`>`那么就相反。当然，你也可以和我的意思相反，就是在赋值上有些麻烦。

连完边后，直接跑拓扑就可以了，别忘了在拓扑排序的时候给点赋值

也别忘了判断一下有没有环，如果有环，那么就不存在。

又是~~愉快的~~代码时间：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define MAXN 2000100
char mp[1010][1010];
int n, m, head[MAXN], ecnt, x, y, ent[MAXN], out[MAXN], rank[MAXN], p, deli[MAXN], fa[MAXN], ans, tot;
bool vis[MAXN], ifq[MAXN];
std::queue <int> q;
struct Edge {
	int v, nx;
}e[MAXN];
void add(int f, int t) {
	e[++ecnt] = (Edge) {t, head[f]};
	head[f] = ecnt;
}
int find(int x) {
	if (fa[x] == x) return x;
	else return fa[x] = find(fa[x]);
}
void un(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return;
	if (rank[x] <= rank[y]) {
		fa[x] = y;
		if (rank[x] == rank[y]) {
			rank[x]++;
		}
	}
	else {
		fa[y] = x;
	}
	return;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", mp[i] + 1);
	}
	for (int i = 1; i <= n + m; i++) {
		fa[i] = i;
		rank[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mp[i][j] == '=') {
				un(i, j + n);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			x = find(j + n);
			y = find(i);
			if (mp[i][j] == '>') {
				add(x, y);
				ent[y]++;
			}
			if (mp[i][j] == '<') {
				add(y, x);
				ent[x]++;
			}
		}
	}
	tot = n + m;
	for (int i = 1; i <= n + m; i++) {
		p = find(i);
		if (!ent[p] && !ifq[p]) {
			q.push(p);
			ifq[p] = 1;
			deli[p] = 1;
			deli[i] = 1;
		}
	}
	ans = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].nx) {
			int to = e[i].v;
			if (vis[to]) continue;
			ent[to]--;
			if (!ent[to]) {
				deli[to] = deli[u] + 1;
				q.push(to);
			}
		}
	}
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n + m; i++) {
		if (!ent[find(i)]) ans++;
	}
	// for (int i = 1; i <= n + m; i++) {
	// 	printf("%d ", ent[find(i)]);
	// }
	// puts("");
	if (tot != ans) {
		// printf("%d %d\n", tot, ans);
		puts("No");
		return 0;
	}
	puts("Yes");
	for (int i = 1; i <= n + m; i++) {
		int p = find(i);
		deli[i] = deli[p];
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", deli[i]);
	}
	puts("");
	for (int i = n + 1; i <= n + m; i++) {
		printf("%d ", deli[i]);
	}
	return 0;
}
```

---

## 作者：LJC00118 (赞：4)

首先将所有 $ = $ 的放在一起，因为相等可以缩成一个点，这个地方可以并查集实现，但是当时比赛的时候我用了 tarjan 缩点实现...

然后根据大于号和小于号来连边，如果 $ a > b $ 且 $ a $ 和 $ b $ 在一个等号联通块内输出无解

然后拓扑排序在 DAG 上 dp，如果这个图不是 DAG 说明出现了一个 $ a_1 > a_2 > a_3 > ... > a_1 $ 的情况，显然无解

题目要求最大的数最小，那转移方程就是 $ f[v] = max(f[v], f[u] + 1) $

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 2005;

vector <int> adj[N], adj2[N];
char c[N][N];
int n, m;

int low[N], dfn[N], col[N], st[N], top, inst[N], f[N], in[N], cnt, color, gs;
void tarjan(int u) {
    low[u] = dfn[u] = ++cnt; st[++top] = u; inst[u] = 1;
    for(register unsigned i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(inst[v]) low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]) {
        ++color;
        while(st[top + 1] != u) {
            int tmp = st[top--];
            col[tmp] = color;
            inst[tmp] = 0;
        }
    }
}

int main() {
    read(n); read(m);
    for(register int i = 1; i <= n; i++) scanf("%s", c[i] + 1);
    for(register int i = 1; i <= n; i++) {
        for(register int j = 1; j <= m; j++) {
            if(c[i][j] == '=') {
                adj[i].push_back(j + n);
                adj[j + n].push_back(i);
            }
        }
    }
    for(register int i = 1; i <= n + m; i++) if(!dfn[i]) tarjan(i);
    for(register int i = 1; i <= n + m; i++) adj[i].clear();
    for(register int i = 1; i <= n; i++) {
        for(register int j = 1; j <= m; j++) {
            if(c[i][j] == '<') {
                if(col[i] == col[j + n]) {
                    cout << "No" << endl;
                    return 0;
                }
                adj[col[i]].push_back(col[j + n]);
                ++in[col[j + n]];
            }
            if(c[i][j] == '>') {
                if(col[i] == col[j + n]) {
                    cout << "No" << endl;
                    return 0;
                }
                adj[col[j + n]].push_back(col[i]);
                ++in[col[i]];
            }
        }
    }
    queue <int> q;
    for(register int i = 1; i <= color; i++) {
        if(!in[i]) {
            q.push(i);
            f[i] = 1;
        }
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        ++gs;
        for(register unsigned i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            --in[v];
            f[v] = max(f[v], f[u] + 1);
            if(!in[v]) q.push(v);
        }
    }
    if(gs != color) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    for(register int i = 1; i <= n; i++) print(f[col[i]], ' ');
    putchar('\n');
    for(register int i = 1; i <= m; i++) print(f[col[i + n]], ' ');
    putchar('\n');
    return 0;
}
```

---

## 作者：CuSO4_and_5H2O (赞：3)


## 建图方式

所以这篇题解思路是 **差分约束 SPFA 写法**。

本题第一次提交[用的 SPFA T飞了](https://www.luogu.com.cn/record/81407688)第二次[还是 SPFA 他过了](https://www.luogu.com.cn/record/81407753)，为什么都是 SPFA 差别这么大？因为存图方式不同。

这里先给各位亲简单的说一下链式前向星和 vector 的区别。

链式前向星存图他的调用快，但是他访问连续路径不如 vector 快，所以稠密图 vector 比链式前向星快，稀疏图链式前向星快，这个题目明显是稠密图啊，所以 vector 时间会比链式前向星快。

## 本题思路

这道题目是差分约束的模板题目，这里推销一下我写差分约束笔记的博客（[适合刚打完模板的亲](https://www.luogu.com.cn/blog/zhuaigezhangzixuan/ri-zhao-zhi-xing-tu-lun)，里边写了如何求出一个范围内的差分约束的最大或最小值）。

之后就是转换差分约束的模型了：

但是这个题目并不是形如 $A_i-B_j \ge C$ 的形式，所以怎么办呢？只需要转换就好了。因为 $A,B$ 都是整数，所以如果 $A_i>B_j$ 的话不就是 $B_j$ 至少加上一就等于 $A_i$ 吗,就可以转换成 $A_i \ge  B_j+1$ 了，其他的同理。

之后根据约束关系建图就行了

$A_i > B_j$ 变成 $A_i \ge  B_j+1$。

$A_i < B_j$ 变成 $B_j \ge A_i  +1$。

$A_i = B_j$ 变成 $B_j \ge A_i$ 和 $A_i \ge  B_j$。

转换成功之后跑 SPFA 就好了。



## 代码

```
#include<bits/stdc++.h>
#define int long long
const int N=100001;
using namespace std;

int vis[N],dis[N],n,m,bj,A,B;
int jis[N];
struct node{
	int qz,to;
};
vector<node> vec[N];
queue<int> q;

void add(int x,int y,int z)
{
	vec[x].push_back(node{z,y});
}

int spfa()
{
	for(int i=1;i<=n+m;i++) dis[i]=1,q.push(i),vis[i]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		vis[x]=0;
		for(int i=0;i<vec[x].size();i++)
		{
			int nxt=vec[x][i].to,qz=vec[x][i].qz;
			if(dis[nxt]<dis[x]+qz)
			{
				dis[nxt]=dis[x]+qz;
				if(!vis[nxt]) q.push(nxt),vis[nxt]=1,jis[nxt]++;
				if(jis[nxt]>n) return 0; 
			}
		}
	}
	return 1;
}
 
signed main(){
	char ch;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			A=i,B=j+n;	
			scanf(" %c",&ch);
			if(ch=='>') add(B,A,1);
			if(ch=='<') add(A,B,1);
			if(ch=='=') add(A,B,0),add(B,A,0);	
		}
	if(spfa()) {
		cout<<"Yes"<<endl;
		for(int i=1;i<=n;i++) printf("%lld ",dis[i]);cout<<endl;
		for(int i=1+n;i<=n+m;i++) printf("%lld ",dis[i]);
	}
	else cout<<"No";
}
```


---

## 作者：yzh_Error404 (赞：2)

#### 差分约束

题目中给了 $n \times m$ 个限制，很容易就可以想到差分约束。

众所周知，差分约束的难点在于将限制转化为类似三角形不等式的式子，需重点考虑。

（在下面默认 $a$ 数组的下标为 $1$ 到 $n$ ， $b$ 数组下标为 $n+1$ 到 $n+m$）

对于一个 '$\lt$' ，可得 $a_i\lt b_j$ ，即为 $b_j-a_i\ge 1$ ，则从 $i$ 向 $j$ 连一条边权为 $1$ 的边。

对于一个 '$\gt$' ，可得 $a_i\gt b_j$ ，即为 $a_i-b_j\ge 1$ ，则从 $j$ 向 $i$ 连一条边权为 $1$ 的边。

对于一个 '$=$' ，可得 $a_i=b_j$ ，即为 $a_i-b_j\ge 0$ 与  $b_j-a_i\ge 0$ ，连两次边权为 $0$ 的边即可。

连完边之后，跑一边最长路（题目要求求最小解），如果有正环（因为是最长路所以不是负环），则无解，反之则输出 $dis$ 数组即可。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e6+5;
struct node
{
	int to,len;
};
vector<node>v[MAXN];//用链式前向星连边就会T飞
int dis[MAXN],sum[MAXN];
bitset<MAXN>vis;
int n,m;
inline bool spfa(int s)//SPFA跑最长路
{
	queue<int>q;
	vis=0;
	memset(dis,-1,sizeof(dis));
	memset(sum,0,sizeof(sum));
	dis[s]=0;
	vis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(register int i=0;i<v[x].size();i++)
		{
			int y=v[x][i].to,z=v[x][i].len;
			if(dis[y]<dis[x]+z)
			{
				dis[y]=dis[x]+z;
				sum[y]=sum[x]+1;
				if(sum[y]>=n+m+1)return true;//找到了正环
				if(!vis[y])
				{
					q.push(y);
					vis[y]=1;
				}
			}
		}
	}
	return false;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
		for(register int j=n+1;j<=n+m;j++)
		{
			char now;
			cin>>now;
			if(now=='<')v[i].push_back((node){j,1});
			if(now=='>')v[j].push_back((node){i,1});//上面说的连边方式
			if(now=='=')v[i].push_back((node){j,0}),v[j].push_back((node){i,0});
		}
	for(register int i=1;i<=n+m;i++)
		v[0].push_back((node){i,1});
	if(spfa(0))puts("No");
	else
	{
		puts("Yes");
		for(register int i=1;i<=n;i++)
			printf("%d ",dis[i]);
		puts("");
		for(register int i=n+1;i<=n+m;i++)
			printf("%d ",dis[i]);
	}
	return 0;
}
```

---

## 作者：djh123 (赞：1)

题目大意：

有$n+m$个变量，给出$n$个变量与$m$个变量的大小关系。你现在要给这些变量赋值，在满足大小关系的前提下使最大值最小。若不能满足大小关系，输出No。
若可以满足大小关系，在第一行输出Yes，第二行输出$n$个变量的值，第三行输出$m$个变量的值

~~差分约束水题啊~~

~~Time limit exceeded on pretest 10~~

因为这些变量的所有大小关系都已经给定，我们可以用并查集把所有相等的变量并到一起，以小于关系建边，如果有解，就得到一张有向无环图，那么直接拓扑记录下答案就好，如果图中有环，那么无解。

```cpp 

#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <bitset>
#include <set>
#include <queue>

typedef long long LL;
typedef double D;

const int inf = 0x3f3f3f3f, Minf = 0x7f7f7f7f;

using namespace std;

int head[3005], to[3000005], nxt[3000005], val[3000005], tot, rd[300005], poi[3005], ans[3005];
int tmp[3005], n, m, vis[3005];
void add(int x, int y, int v) {to[++ tot] = y, val[tot] = v, nxt[tot] = head[x], head[x] = tot;}
queue <int> Q;
struct ice_table {
    int fa[3005];
    void init(int n) {for(int i = 1; i <= n; ++ i) fa[i] = i;}
    int find_father(int x) {return fa[x] == x ? x : fa[x] = find_father(fa[x]);}
    bool unit(int x, int y) {
        int fx = find_father(x), fy = find_father(y);
        if(fx == fy) return 0;
		fa[fx] = fy; return 1;
    }
}T;
char c[1050][1050];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    cin >> n >> m;
    T.init(n + m);
    for(int i = 1; i <= n; ++ i) {
    	cin >> c[i] + 1;
    	for(int j = 1; j <= m; ++ j) if(c[i][j] == '=') T.unit(i, j + n);
	}
	for(int i = 1; i <= n; ++ i) {
		for(int j = 1; j <= m; ++ j) {
			if(c[i][j] == '<') add(T.find_father(i), T.find_father(j + n), 1), rd[T.find_father(j + n)] ++;
			else if(c[i][j] == '>') add(T.find_father(j + n), T.find_father(i), 1), rd[T.find_father(i)] ++;
		}
	}
	memset(ans, 0xff, sizeof ans);
    for(int i = 1; i <= n + m; ++ i) poi[i] = T.find_father(i);
    sort(poi + 1, poi + 1 + n + m);
    int tot = unique(poi + 1, poi + 1 + n + m) - poi - 1;
    for(int i = 1; i <= tot; ++ i) if(rd[poi[i]] == 0) Q.push(poi[i]), ans[poi[i]] = 1;
    while(Q.size()) {
    	int now = Q.front(); Q.pop();
    	for(int i = head[now]; i; i = nxt[i]) {
    		rd[to[i]] --;
    		ans[to[i]] = max(ans[now] + 1, ans[to[i]]);
    		if(rd[to[i]] == 0) Q.push(to[i]);
		}
	}
	for(int i = 1; i <= tot; ++ i) if(rd[poi[i]] != 0) {puts("No"); return 0;}
    puts("Yes");
    for(int i = 1; i <= n + m; ++ i) tmp[i] = ans[T.find_father(i)];
    for(int i = 1; i <= n; ++ i) printf("%d ", tmp[i]); puts("");
    for(int i = n + 1; i <= n + m; ++ i) printf("%d ", tmp[i]); puts("");
	return 0;
} 
```

---

## 作者：东灯 (赞：1)

一道很棒的 Tarjan 题！

先把点都划归到一张图上，图上将会有 $n+m$ 个点。

考虑直接把相等的元素划归到一个集合，把大于或者小于转化为从小的元素到大的元素建边，接下来就可以用 Tarjan 缩点的方法解决这个问题。

如何把相等的元素放入一个集合呢？我们可以直接对两个点建立无向边，而 Tarjan 缩点时将会寻找最大环，因此一个等号集合中的元素总是可以被缩进一个点内。

接下来在新图上跑拓扑排序，可以直接从 DP 转移大小：

$$f_v=\max(f_v,f_u+1)$$

这样也能保证构造出最大元素最小的方案。

如何判断无解呢？考虑什么情况下会出现无解：当且仅当出现了多个非等于关系在图上构成的环。

那么我们可以在建等于边时把边权设为 $0$，而建大于或者小于边时把边权设为 $1$，在 Tarjan 建立新图的时候，如果一条边的两个端点都在一个集合里面且这条边的边权不为 $0$，就代表无解。

这题的数据范围我卡了一会，一开始开的 $10^3$ 开到 $2 \times 10^5$ 都 RE，要注意预估极限数据，最坏情况是当 $n=m=10^3$ 时，有 $2 \times 10^3$ 个点，最坏可以存在 $4 \times 10^6$ 条边。但是本题貌似数据比较宽容，边数开到 $2 \times 10^6$ 也可以通过。

数据范围预估程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n=2000,ans=0;
    for(register int i=1;i<=n;++i)
        for(register int j=i+1;j<=n;++j)
            ++ans;
    cout<<(ans<<1)<<endl;
}
```


代码见下:

```cpp
#include<bits/stdc++.h>
#define MAXN 4000005
using namespace std;
int dfn[MAXN],low[MAXN],belong[MAXN],head[MAXN],phead[MAXN],du[MAXN],f[MAXN];
struct mystack{
    int values[MAXN],top=0;
    bitset<MAXN>instack;
    inline void push(int x){
        instack[x]=true;
        values[top++]=x;
    }
    inline int pop(){
        instack[values[--top]]=false;
        return values[top];
    }
}s;
int n,m,ecnt,pcnt,scccnt,nowtime;
char temp;
struct edge{
    int from,to,next,w;
}e[MAXN],points[MAXN];
inline void add(int u,int v,int w){
    e[++ecnt]={u,v,head[u],w};
    head[u]=ecnt;
}
inline void padd(int u,int v){
    ++du[v];
    points[++pcnt]={u,v,phead[u]};
    phead[u]=pcnt;
}
inline void tarjan(int x){
    dfn[x]=low[x]=++nowtime;
    s.push(x);
    for(register int i=head[x];i;i=e[i].next){
        int v(e[i].to);
        if(s.instack[v])low[x]=min(low[x],low[v]);
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
    }
    if(dfn[x]==low[x]){
        ++scccnt;
        int k(0);
        do{
            k=s.pop();
            belong[k]=scccnt;
        }while(k!=x);
    }
}
void toposort(){
    queue<int>q;
    for(register int i=1;i<=scccnt;++i)
        if(du[i]==0){
            q.push(i);
            f[i]=1;
        }
    while(!q.empty()){
        int u(q.front());
        q.pop();
        for(register int i=phead[u];i;i=points[i].next){
            int v(points[i].to);
            f[v]=max(f[v],f[u]+1);
            if(--du[v]==0)q.push(v);
        }
    }
}
int main(){
    cin>>n>>m;
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=m;++j){
            cin>>temp;
            if(temp=='=')add(i,n+j,0),add(n+j,i,0);
            else if(temp=='>')add(n+j,i,1);
            else add(i,n+j,1);
        }
    for(register int i=1;i<=n+m;++i)
        if(!dfn[i])tarjan(i);
    for(register int i=1;i<=ecnt;++i)
        if(belong[e[i].from]!=belong[e[i].to])
            padd(belong[e[i].from],belong[e[i].to]);
        else if(e[i].w){
            cout<<"No"<<endl;
            return 0;
        }
    toposort();
    cout<<"Yes"<<endl;
    for(register int i=1;i<=n;++i)cout<<f[belong[i]]<<" ";
    cout<<endl;
    for(register int j=1;j<=m;++j)cout<<f[belong[n+j]]<<" ";
}
```


---

## 作者：legendgod (赞：1)

[CF1131D Gourmet choice](https://www.luogu.com.cn/problem/CF1131D)

我们考虑对于一个 DAG 的处理是很简单的，我们只需要考虑从拓扑排序入手。如果 $a > b$ 那么我们就让 $b$ 向 $a$ 连边。为什么不反过来呢？容易想到我们最小值肯定是 1，但是我们不确定最大值是多少。

我们考虑在 DAG 上 dp，设 $f_i$ 表示点 $i$ 的最终答案。那么对于更新也就很简单了 $f_{to} = \max(f_u + 1, f_{to})$，我们要在拓扑排序的时候通过前驱进行更新。

发现“等于”这个限制很好处理，我们可以将其缩点，让所有相等的数用一个点来代替。笔者使用的是并查集。

但是我们连接出来的图不一定是合法的，也就是可能产生环。

对于一个有自环的图肯定是不合法的，我们在建图的时候直接判掉即可。

对于存在环的图肯定是不合法的，我们可以在拓扑序的时候记录一下进入队列点的个数，如果其不等于缩点之后的总共点数，那么肯定不合法。

我们还要考虑到不能建重边，不然会导致入度出错。

```cpp
#include <bits/stdc++.h>
using namespace std;

//#define Fread

#ifdef Fread
#define getchar() ((p1 == p2 && p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin)) ? EOF : *p1 ++)
char buf[1 << 21], *p1, *p2;
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c);c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}

const int maxn = 3e3 + 5;
const int maxm = maxn << 1;

typedef int room[maxn];

int n, m;
int fa[maxn];
int getfa(int x) { return x == fa[x] ? x : fa[x] = getfa(fa[x]); }
char a[maxn][maxn];

void merge(int x,int y) {
    x = getfa(x), y = getfa(y);
    if(x == y) return ;
    fa[x] = y;
}
int bel[maxn];
/*
if a < b add Edge from a to b
*/
int in[maxn];
int head[maxn], cnt;
struct Edge {
    int to, next;
}edg[maxn * maxn];
void add(int u,int v) {
    edg[++ cnt] = (Edge) {v, head[u]}, head[u] = cnt;
}
/*
2 4
>==>
>=<>
Out:
No
*/
int vis[maxn][maxn];
int f[maxn], c[maxn];
signed main() {
//    freopen("data.in", "r", stdin);
//    freopen("myans.out", "w", stdout);
	int i, j;
    r1(n), r1(m);
    for(i = 1; i <= n + m; ++ i) fa[i] = i;
    for(i = 1; i <= n; ++ i) scanf("%s", a[i] + 1);
    for(i = 1; i <= n; ++ i) for(j = 1; j <= m; ++ j) if(a[i][j] == '=') merge(i, j + n);
    for(i = 1; i <= n + m; ++ i) bel[i] = getfa(i), c[i] = bel[i];
    sort(c + 1, c + n + m + 1); int len = unique(c + 1, c + n + m + 1) - c - 1;
    for(i = 1; i <= n + m; ++ i) bel[i] = lower_bound(c + 1, c + len + 1, bel[i]) - c;
//    for(i = 1; i <= n + m; ++ i) printf("%d ", bel[i]);
//    puts("");
    for(i = 1; i <= n; ++ i) for(j = 1; j <= m; ++ j)
        if(bel[i] != bel[j + n]) {
            if((a[i][j] == '<')) {
                if(vis[bel[i]][bel[j + n]] == 1) continue;
                vis[bel[i]][bel[j + n]] = 1;
                in[bel[j + n]] ++, add(bel[i], bel[j + n]);
            }
            else if((a[i][j] == '>'))  {
                if(vis[bel[j + n]][bel[i]] == 1) continue;
                vis[bel[j + n]][bel[i]] = 1;
                in[bel[i]] ++, add(bel[j + n], bel[i]);
            }
        }
        else if((bel[i] == bel[j + n]) && (a[i][j] != '=')) return puts("No"), 0;
//    for(i = 1; i <= len; ++ i) printf("%d ", in[i]);
    queue<int> q;
    for(i = 1; i <= len; ++ i) if(!in[i]) q.push(i), f[i] = 1;
    int tot(0);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        ++ tot;
        if(tot > len) return puts("No"), 0;
        for(int i = head[u];i;i = edg[i].next) {
            int to = edg[i].to;
            f[to] = max(f[to],f[u] + 1);
            if(!(-- in[to])) q.push(to);
        }
    }
//    printf("len = %d, tot = %d\n", len, tot);
    if(tot != len) puts("No");
    else {
        puts("Yes");
        for(i = 1; i <= n; ++ i) printf("%d ", f[bel[i]]);
        puts("");
        for(i = n + 1; i <= n + m; ++ i) printf("%d ", f[bel[i]]);
        puts("");
    }
	return 0;
}


```



---

## 作者：米奇奇米 (赞：1)

## 题解-CF1131D Gourmet choice

* **题目意思**

** *
	  
   就是给你很多个约束条件,让你求出合法的序列$a,b$满足条件且最大值最小的方案。
** *

* $Solution$

* **
 $tarjan+topu$
 
 对于一开始的那些$=$条件我们先让$i$以及$j+n$放入同一个连通块里。
 第二次再做一遍，如果两个处于同一个联通块的点又有$> or <$的关系显然就只要输出$No$即可。
 
 然后第二次做关于大于小于关系的点的时候：
 
* 若为$<$则：从$jia(i,j+n)$并且统计$j+n$的度加加
* 若为$>$则：从$jia(j+n,i)$并且统计$i$的度加加

这样做完一遍我们就形成了一个$DAG$。于是只要在这张图上跑一下拓扑就可以了，在途中用$f[]$表示答案，因为题目要求求最大值最小，所以$f[v]=\max(f[v],f[u]+1)$
* **

* $Code$
```cpp
#include <bits/stdc++.h>
  using namespace std;

  const int maxn=2005;
  const int maxm=maxn*maxn;

  int n,m,cnt,ans,top,sum,tot,now;
  int head[maxm],col[maxm],stak[maxm];
  int low[maxm],dfn[maxm],gs;
  int f[maxm],du[maxm],vis[maxm];
  char c[maxn][maxn];

  struct nood {
      int nex,to;
  };
  nood e[maxm<<2];//n*m的边

  inline void jia(int u,int v) {
      e[++cnt].nex=head[u];
      head[u]=cnt;
      e[cnt].to=v;
  }

  inline void tarjan(int u) {
      low[u]=dfn[u]=++now;
      stak[++top]=u;
      for ( int i=head[u];i;i=e[i].nex ) {
          int v=e[i].to;
          if(!dfn[v]) {
              tarjan(v);
              low[u]=min(low[u],low[v]);
          }
          else 
              if(!col[v]) 
                  low[u]=min(low[u],dfn[v]);
      }
      if(low[u]==dfn[u]) {
          col[u]=++sum;
          while(u!=stak[top]) {
              col[stak[top]]=sum;
              top--;
          }
          top--;
      }
  }

  inline int read() {
      int sum=0; char ch=getchar();
      while(!isdigit(ch)) ch=getchar();
      while(isdigit(ch)) 
          sum=sum*10+(ch^48),ch=getchar();
      return sum;
  }

  inline void write(int x) {
      if(x<0) {
          putchar('-');
          x=-x;
      }
      if(x>9) 
          write(x/10);
      putchar(x%10+48);
  }

  inline void write_c(int x) {
      write(x);
      putchar(' ');
  }

  inline int max(int a,int b) {
      if(a>b) return a;
      return b;
  }

  int main() {
  //	freopen("da.in","r",stdin);
  //	freopen("da.out","w",stdout); 
      n=read();
      m=read();
      for ( int i=1;i<=n;i++ ) scanf("%s",c[i]+1);
      for ( int i=1;i<=n;i++ ) 
          for ( int j=1;j<=m;j++ ) 
              if(c[i][j]=='=') {
                  jia(i,j+n); 
                  jia(j+n,i);
              }
      for ( int i=1;i<=n+m;i++ ) 
          if(!dfn[i]) tarjan(i);
      memset(head,0,sizeof(head));
      cnt=0;
      for ( int i=1;i<=n;i++ ) 
          for ( int j=1;j<=m;j++ ) {
              if(c[i][j]=='>') {
                  if(col[i]==col[j+n]) 
                      return printf("No\n"),0;
                  jia(col[j+n],col[i]);
                  ++du[col[i]];
              }
              if(c[i][j]=='<') {
                  if(col[i]==col[j+n]) 
                      return printf("No\n"),0;
                  jia(col[i],col[j+n]);
                  ++du[col[j+n]];
              }
          }
      std::queue<int>q;
      for ( int i=1;i<=sum;i++ ) 
          if(!du[i]) {
              f[i]=1;
              q.push(i);
          }
  //	for ( int i=1;i<=sum;i++ ) cout<<du[i]<<" "; cout<<endl;
  //	for ( int i=1;i<=n+m;i++ ) cout<<col[i]<<" "; 
      while(!q.empty()) {
          int u=q.front();
          q.pop();
          ++gs;
          for ( int i=head[u];i;i=e[i].nex ) {
              int v=e[i].to;
              --du[v];
              f[v]=max(f[v],f[u]+1);
              if(!du[v]) q.push(v);
          }
      }
  //	for ( int i=1;i<=sum;i++ ) cout<<f[i]<<" "; 
      if(gs!=sum) 
          return printf("No\n"),0;
      putchar('Y');
      putchar('e');
      putchar('s');
      putchar('\n');
      for ( int i=1;i<=n;i++ ) write_c(f[col[i]]);
      printf("\n");
      for ( int i=1;i<=m;i++ ) write_c(f[col[i+n]]);
      return 0;
  }
```


---

## 作者：harmis_yz (赞：0)

## 分析

考虑建图。

按照大小关系建立有向图，若图上有环，则无解。然后跑个拓扑就行了。将最小的 $a_i$ 或 $b_i$（入度为 $0$）设为 $1$，有转移式：$ans_i=\max\{ans_j|j \to i\}+1$。

对于 $a_i=b_j$ 的情况，仿照[这道题](https://www.luogu.com.cn/problem/AT_abc335_e)的思路，建立并查集缩点即可。判断有向图是否有环，直接看有没有点没被遍历过。

复杂度 $O(n\times m)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=1e6+10,M=1005;
int ne[N],e[N],h[N],idx;
int n,m,ans[N];
char c[M][M];
int f[M+M],d[M+M],vis[M+M];

il int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void tuopu(){
	queue<int> qu;
	for(re int i=1;i<=n+m;++i) if(find(i)==i&&!d[i]) ans[i]=vis[i]=1,qu.push(i);
	while(!qu.empty()){
		int now=qu.front();qu.pop();
		for(re int i=h[now];i;i=ne[i]){
			int j=e[i];ans[j]=max(ans[j],ans[now]+1);
			if(--d[j]==0) vis[j]=1,qu.push(j);
		}
	}
	return ;
}
il void solve(){
	n=rd,m=rd;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j) 
		cin>>c[i][j];
	for(re int i=1;i<=n+m;++i) f[i]=i;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j) 
		if(c[i][j]=='=') f[find(i)]=find(n+j);
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		if(c[i][j]=='>') ++d[find(i)],add(find(n+j),find(i));
		else if(c[i][j]=='<') ++d[find(n+j)],add(find(i),find(n+j));
	tuopu();
	for(re int i=1;i<=n+m;++i) 
		if(find(i)==i&&!vis[i]) return printf("No\n"),void(0);
	printf("Yes\n");
	for(re int i=1;i<=n;++i) printf("%lld ",ans[find(i)]);
	printf("\n");
	for(re int i=1;i<=m;++i) printf("%lld ",ans[find(n+i)]);
	return ;
}

signed main(){
	int t=1;while(t--)
	solve();
	return 0;
}

```


---

## 作者：tmp_get_zip_diff (赞：0)

题目意思其它题解已经讲的很清楚了，重点讲一下思路。

首先这是一道差分约束，这里求最小值，跑最长路，所以它可以表示成下面的形式。

$\begin{cases}
a_1 - b_1 \ge w_{1,1} \\
a_2 - b_2 \ge w_{2,2} \\
... \\
a_n - b_m \ge w_{n,m}
\end{cases}$

$a_i$ 和 $b_j$ 有 $3$ 种关系式，可以将他们转化：

- $a_i > b_j \to i - j \ge 1$
- $a_i < b_j \to j - i \ge 1$
- $a_i = b_j \to i - j \ge 0 , j - i \ge 0$

**注意**：这里的 $i$ 和 $j$ 指的是不同的下标，因此 $j$ 要多 $n$，避免重复，数组也要开大 $1$ 倍。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=5005+5;
struct Node
{
	int to,w;
};
int n,m,dis[N],cnt[N];
vector<Node>nbr[N];
bool vis[N];

bool spfa(int st)
{
	memset(dis,0xcf,sizeof dis);
	vis[st]=1;
	dis[st]=0;
	queue<int>q;
	q.push(st);
	while(q.empty()==false)
	{
		int cur=q.front();
		q.pop();
		vis[cur]=false;
		for(int i=0;i<nbr[cur].size();i++)
		{
			int nxt=nbr[cur][i].to,w=nbr[cur][i].w;
			if(dis[cur]+w>dis[nxt])
			{
				dis[nxt]=dis[cur]+w;
				if(vis[nxt]==false)
				{
					q.push(nxt);
					vis[nxt]=true;
					cnt[nxt]++; 
				}
				if(cnt[nxt]>=n+5)
					return true;
			}
		}
	}
	return false;
}

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char c;
			cin>>c;
			if(c=='>')
				nbr[j+n].push_back((Node){i,1});
			else if(c=='<')
				nbr[i].push_back((Node){j+n,1});
			else
			{
				nbr[i].push_back((Node){j+n,0});
				nbr[j+n].push_back((Node){i,0});
			}
		}
	for(int i=1;i<=n+m;i++)
		nbr[0].push_back((Node){i,1});
	if(spfa(0)==true)
	{
		cout<<"No";
		return 0;
	}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++)
		cout<<dis[i]<<" ";
	cout<<"\n";
	for(int i=1;i<=m;i++)
		cout<<dis[i+n]<<" ";
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

WC 前了这种sb题都做不来，可能是打铁预定？

关于等于，我们直接并查集（DSU）缩点即可。

然后对于大于小于，我们建边（小$\to$大），然后拓扑一下。有环肯定不行。然后题目中要最大元素最小，我们贪心赋值即可。

一开始想到了差分约束，但实际上没有必要，因为没有边权，直接拓扑判环即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=2009;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,m,d[N],f[N],cnt;
char c[N][N];
vector<int>e[N];
void add(int u,int v) {e[u].push_back(v); d[v]++;}

int id[N]; //dsu
int find(int i) {return i==id[i]?i:id[i]=find(id[i]);}

void topo() {
	queue<int>q;
	rep(i,1,n+m) if(i==find(i)&&!d[i]) q.push(i),f[i]=1;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(auto v:e[u]) {
			f[v]=max(f[v],f[u]), d[v]--;
			if(d[v]==0) f[v]++, q.push(v);
		}
	}
}

int main() {
	n=read(), m=read();
	rep(i,1,n) scanf("%s",c[i]+1);
	rep(i,1,n+m) id[i]=i;
	bool flag=0;
	rep(i,1,n) rep(j,1,m) {
		int u=find(i), v=find(j+n);
		if(c[i][j]!='='&&u==v) {flag=1; break;}
		else if(c[i][j]=='=') id[u]=v;
	}
	if(flag==1) return puts("No"), 0;
	rep(i,1,n+m) if(find(i)==i) cnt++;
	rep(i,1,n) rep(j,1,m) {
		int u=find(i), v=find(j+n);
		if(c[i][j]=='<') add(u,v);
		else if(c[i][j]=='>') add(v,u);
	}
	topo();
	rep(i,1,n+m) if(i==find(i)&&d[i]) {flag=1; break;}
	if(flag==1) return puts("No"), 0;
	puts("Yes");
	rep(i,1,n) printf("%d ",f[find(i)]); puts("");
	rep(i,1,m) printf("%d ",f[find(i+n)]); puts("");
	return 0;
}
```

---

## 作者：SGColin (赞：0)

首先考虑什么情况不合法：一个相等的集合内部出现了不等号，或不等号出现了一个有向环。

对于第一种情况，我们首先建立一个 $|A| + |B|$ 大小的并查集，先处理所有的 "=" 情况把并查集合并，然后逐个判断不等号即可。

对于不等号，因为每个元素的取值是由小于它的元素的取值决定的，因此由小的元素连向大的元素（并查集的祖先）。

对于后一种不合法的情况直接在这张图上拓扑排序看是否有环就好了。对于最小化取值，拓扑之前进队的点权值显然都设为 1，然后其他点的权值就取前驱节点权值的 max + 1 就可以了。

注意最后每个点的点权是并查集祖先的点权。

```C++
#include <bits/stdc++.h>
#define N 2005
#define gc getchar
using namespace std;

inline int rd() {
  int x = 0;
  char c = gc();
  while (!isdigit(c)) c = gc();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48);c = gc();
  }
  return x;
}

char a[N][N];

int n, m, f[N], tot, hd[N], deg[N];

int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}

inline void merge(int x, int y) {f[find(x)] = find(y);}

struct edge{int to, nxt;} e[N * N];

inline void add(int u, int v) {
  e[++tot].to = v; ++deg[v];
  e[tot].nxt = hd[u]; hd[u] = tot;
}

int cnt, mn[N];

queue<int> q;

inline void toposort() {
  for (int i = 1; i <= n + m; ++i) if (deg[i] == 0) q.push(i);
  while (!q.empty()) {
    ++cnt;
    int u = q.front(); q.pop();
    for (int i = hd[u], v; i; i = e[i].nxt) {
      --deg[v = e[i].to];
      mn[v] = max(mn[v], mn[u] + 1);
      if (!deg[v]) q.push(v);
    }
  }
}

int main() {
  n = rd(); m = rd();
  for (int i = 1; i <= n + m; ++i) f[i] = i;
  char c;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      c = gc();
      while (c != '>' && c != '<' && c != '=') c = gc();
      a[i][j] = c;
      if (c == '=') merge(i, j + n);
    }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (a[i][j] != '=') {
        if (find(i) == find(j + n)) {puts("No"); return 0;}
        if (a[i][j] == '<') add(find(i), find(j + n));
        else add(find(j + n), find(i));
      }
  toposort();
  if (cnt != n + m) {puts("No"); return 0;}
  puts("Yes");
  for (int i = 1; i <= n; ++i) printf("%d ", mn[find(i)] + 1);
  puts("");
  for (int i = 1; i <= m; ++i) printf("%d ", mn[find(i + n)] + 1);
  return 0;
}
```

---

