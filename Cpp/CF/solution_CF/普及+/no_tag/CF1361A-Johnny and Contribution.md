# Johnny and Contribution

## 题目描述

Today Johnny wants to increase his contribution. His plan assumes writing $ n $ blogs. One blog covers one topic, but one topic can be covered by many blogs. Moreover, some blogs have references to each other. Each pair of blogs that are connected by a reference has to cover different topics because otherwise, the readers can notice that they are split just for more contribution. Set of blogs and bidirectional references between some pairs of them is called blogs network.

There are $ n $ different topics, numbered from $ 1 $ to $ n $ sorted by Johnny's knowledge. The structure of the blogs network is already prepared. Now Johnny has to write the blogs in some order. He is lazy, so each time before writing a blog, he looks at it's already written neighbors (the blogs referenced to current one) and chooses the topic with the smallest number which is not covered by neighbors. It's easy to see that this strategy will always allow him to choose a topic because there are at most $ n - 1 $ neighbors.

For example, if already written neighbors of the current blog have topics number $ 1 $ , $ 3 $ , $ 1 $ , $ 5 $ , and $ 2 $ , Johnny will choose the topic number $ 4 $ for the current blog, because topics number $ 1 $ , $ 2 $ and $ 3 $ are already covered by neighbors and topic number $ 4 $ isn't covered.

As a good friend, you have done some research and predicted the best topic for each blog. Can you tell Johnny, in which order he has to write the blogs, so that his strategy produces the topic assignment chosen by you?

## 说明/提示

In the first example, Johnny starts with writing blog number $ 2 $ , there are no already written neighbors yet, so it receives the first topic. Later he writes blog number $ 1 $ , it has reference to the already written second blog, so it receives the second topic. In the end, he writes blog number $ 3 $ , it has references to blogs number $ 1 $ and $ 2 $ so it receives the third topic.

Second example: There does not exist any permutation fulfilling given conditions.

Third example: First Johnny writes blog $ 2 $ , it receives the topic $ 1 $ . Then he writes blog $ 5 $ , it receives the topic $ 1 $ too because it doesn't have reference to single already written blog $ 2 $ . Then he writes blog number $ 1 $ , it has reference to blog number $ 2 $ with topic $ 1 $ , so it receives the topic $ 2 $ . Then he writes blog number $ 3 $ which has reference to blog $ 2 $ , so it receives the topic $ 2 $ . Then he ends with writing blog number $ 4 $ which has reference to blog $ 5 $ and receives the topic $ 2 $ .

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
2 1 3```

### 输出

```
2 1 3```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
1 1 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 3
1 2
2 3
4 5
2 1 2 2 1```

### 输出

```
2 5 1 3 4```

# 题解

## 作者：Alex_Wei (赞：13)

> [题面传送门](https://www.luogu.com.cn/problem/CF1361A)。

> 题意简述：给定一张 $n$ 个点 $m$ 条边的图。你需要给每个点写上数字，其数字为所有与它相邻且被写上数字的点中没出现过的最小的**正整数**。请求出一种写数字的顺序使得编号为 $i$ 的点上的数字为 $t_i$。无解输出 $\texttt{-1}$。

---

如果题目有解，则一定满足：

1. 对于每个点，与之相邻的所有点的所有目标数字必定包含了 $1\sim t_i-1$ 的所有数字。
   
   说明：显然，如果一个点 $i$ 的所有相邻点的目标数字中没有出现 $v(v<t_i)$，则无论如何点 $i$ 上写的数字不可能超过 $v$，故无解。

2. 对于每个点，与之相邻的所有点的所有目标数字一定不包含 $t_i$。

   说明：显然，如果一个点 $i$ 的某个相邻点 $j$ 满足 $t_i=t_j$，则点 $i,j$ 中必有至少一个点上写的数字不等于 $t_i(t_j)$，故无解。

感性理解一下，如果满足上述条件，则按照 $t_i$ 从小到大写数字就是一个符合条件的顺序。

时间复杂度 $O(n\log n)$。

为更好的阅读体验，代码中的板子已省略。

```cpp
const int N=5e5+5;

int n,m,pd[N];
vector <int> e[N];
struct pos{
	int id,val;
	bool operator < (const pos &v) const {return val<v.val;}
}c[N];

int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){int u=read(),v=read(); e[u].pb(v),e[v].pb(u);}
	for(int i=1;i<=n;i++)c[i].val=read(),c[i].id=i;
	for(int i=1;i<=n;i++){
		map <int,int> mp;
		for(int it:e[i])mp[c[it].val]=1;
		for(int j=1;j<c[i].val;j++)if(!mp[j])puts("-1"),exit(0);
		if(mp[c[i].val])puts("-1"),exit(0);
	}
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++)cout<<c[i].id<<" ";
	return 0;
}
```

---

## 作者：LoserKugua (赞：3)

提供一种好想，还跑得很快的做法。我不卡常随便交了一发就[洛谷最优解第一](https://www.luogu.com.cn/record/list?pid=CF1361A&orderBy=1&status=&page=1)了。

## 思路
我们分析一下题目的限制条件：
1. 对于每个点 $i$，我们要求 $[1,t_i-1]$ 内的所有自然数在所有 $t_{v}$ 中出现，这里的 $v$ 是指所有和 $i$ 直接有边相连的点。
2. 对于原图中每条边 $(u,v)$，如果 $t_u=t_v$，则无解，因为只要 $u$ 或者 $v$ 标上对应的数后另一个就满足不了要求了。否则，一定是 $t$ 值小的那个点比 $t$ 值大的那个点先标数。

有了以上的分析后我们就知道了，这个带点权的图给出的限制就是“某件事必须先于某件事干”（见第二条分析）这样，我们很自然地就可以想到用拓扑排序来干这件事，而且题目要求求出的也是一个给点标数的顺序，很符合。

## 详细实现
新建立一个用于拓扑排序的图，对于原图中每条边 $(u,v)$，若 $t_u<t_v$，在新图中连有向边 $u \to v$ 表示 $u$ 要先于 $v$ 标数，若 $t_u>t_v$ 则把有向边方向反过来即连 $v \to u$，如果 $t_u=t_v$，就可以判定无解了。

然后还有一些特殊情况需要我们处理：
1. 出现“断层”。比如就只有 $1-2$ 这一条边，但是 $t_1 = 1$，$t_2 = 3$。这种情况显然无解，做法就是我们同时维护一下所有点当前标的数 $nw_i$，也就是相连的点中未出现的最小的数，拓扑排序到某个点 $p$ 的时候比较一下 $nw_p$ 与 $t_p$ 的大小，如果不相同就是无解。代码里我偷懒了，没有把 $nw_i$ 全部初始化为 $1$，维护的是 $nw_i - 1$，不过不影响正确性。
2. 出现“孤点”。比如有一个点 $p$，$t_p = 2$ 而且 $p$ 不和任何点相连，这种情况也是无解，拓扑排序记录一下被访问的点数最后跟 $n$ 相等与否就好了。

加上上面的特殊处理跑一遍拓扑排序就好了，时间复杂度 $O(n + m)$。

为什么这样是正确的呢？我们可以这样想：对于一个点 $p$，$t$ 值比他小的点一定在拓扑排序的过程中都被标好数了，满足了标数的先后顺序，再加上我们维护了当前标数值 $nw_i$，无解情况下 $p$ 要么满足不了顺序，要么染色时对不上数字，其他情况下一定是有解的。

这个分析看上去有点长，但是实际上画画样例想一想要不了多久，想到拓扑排序也是比较简单的。

## 代码
简单易懂。
```cpp
#include<cstdio>
using namespace std;
const int maxn = 500005;
int n,m,u[maxn],v[maxn],t[maxn],head[maxn],deg[maxn],tot,q[maxn],qh,qt,ans[maxn],atop;
int nw[maxn];
struct edge {
	int to,next;
}e[maxn << 1];
void addedge(int u1, int v1) {
	e[++tot].to = v1;
	e[tot].next = head[u1];
	head[u1] = tot;
}
int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; ++i) scanf("%d %d", u + i, v + i);
	for(int i = 1; i <= n; ++i) scanf("%d", t + i);
	for(int i = 1; i <= m; ++i) {
		if(t[u[i]] == t[v[i]]) {
			printf("-1");
			return 0;
		}
		if(t[u[i]] < t[v[i]]) {
			addedge(u[i], v[i]);
			++deg[v[i]];
		}
		else {
			addedge(v[i], u[i]);
			++deg[u[i]];
		}
	}
	qh = 1;
	for(int i = 1; i <= n; ++i) 
		if(t[i] == 1) q[++qt] = i;
	while(qt >= qh) {
		int p = q[qh++];
		ans[++atop] = p;
		if(nw[p] + 1 != t[p]) {
			printf("-1");
			return 0;
		}
		for(int i = head[p]; i; i = e[i].next) {
			int v1 = e[i].to;
			if(nw[p] == nw[v1]) ++nw[v1];
			if(--deg[v1] == 0) q[++qt] = v1;
		}
	}
	if(atop != n) printf("-1");
	else for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
} 
```

---

## 作者：Dregen_Yor (赞：2)

# 思路

根据题意，很显然要先所有把 $t_i=1$ 的点 $i$ 全部标上数，之后再标 $t_i=2$ 的点。很显然，标点的顺序是根据 $t_i$ 的大小，从小到大以此标点的。

根据每个操作的性质，我们可以用一个队列来维护进行标点的顺序，先将所有 $t_i=1$ 的点 $i$ 全部压入队列，然后再将所有和他连边且满足标点后的值等于 $t_j$ 的点 $j$ 压入队列。

现在考虑怎样才能判断一个点是否满足题目中的限制条件。我们可以考虑用一个数组记录每个点**当前和他连边的点中点权从 $1$ 开始的连续区间长度**。对于当前枚举的点，在遍历每一条边的时候更新相连的点的连续区间的长度，并判断相连的点的最大值是否满足 $t_i$ 的条件，若满足条件直接压入队列即可。

因为是根据 $t_i$ 的大小从小到大枚举，所以每个点的连续区间不会出现一开始是中断的但某次操作后变成连续的情况，即不会出现相连的点的值域由 $[1,3]\cup[4,5]$ 在某次操作后变为 $[1,5]$ 的情况，只会出现相连的点的值域由 $[1,3]\cup[4,5]$ 在某次操作后变为 $[1,3]\cup[4,6]$ 的情况。

# 代码

```cpp
#include <bits/stdc++.h>
#define N 500010
using namespace std;
int n,m,p[N],top,col[N],t[N];
bool v[N];
vector <int> G[N];
queue <int> q;
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&t[i]);
		if(t[i]==1){
			q.push(i);
			col[i]=1;
			v[i]=1;
		}
	}
	while(!q.empty()){
		int x=q.front();
		q.pop();
		p[++top]=x;
		col[x]=t[x];
		for(auto to:G[x]){
			if (t[to]==t[x]){
				puts("-1");
				exit(0);
			}
			if(col[x]==col[to]+1){
				col[to]++;
			}
			if(col[to]+1==t[to]&&!v[to]){
				q.push(to);
				v[to]=1;
			}
		}
	}
	if(top!=n){
		puts("-1");
		exit(0);
	}
	for(int i=1;i<=n;i++){
		printf("%d ",p[i]);
	}
	return 0;
}

```


---

## 作者：moosssi (赞：2)

弄清题意后，简单想想可以发现：输出的顺序就是给定值 $t_i$ 从小到大后输出编号的结果，所以只需按顺序判断是否无解即可。

判断方法：枚举当前点所连点，标记出现的 $t_j$ ，判断 $1\sim t_i-1$ 的值是否都出先现过，没有则无解；还有一种如果 $t_i=t_j$ 也是无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct nod{
	int t,id;
}p[N];
int n,m,ans[N];
vector<int>ver[N];
bool cmp(nod x,nod y){
	return x.t<y.t;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		ver[a].push_back(b);
		ver[b].push_back(a);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i].t);
		p[i].id=i;
	}
	for(int i=1;i<=n;i++){
		int v=p[i].t,cnt=0;
		map<int,int>vis;
		for(int j=0;j<ver[p[i].id].size();j++){
			int x=ver[p[i].id][j];
			if(p[x].t==v){
				printf("-1");
				return 0;
			}
			if(p[x].t>v)continue;
			if(!vis[p[x].t]){
				vis[p[x].t]=1;
				cnt++;
			}
		}
		if(cnt!=v-1){
			printf("-1");
			return 0;
		}
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++){
		printf("%d ",p[i].id);
	}
	return 0;
}。
```


---

## 作者：bsdsdb (赞：1)

题意：给一个无向图和序列 $\{a_n\}$，提供一个排列 $\{p_n\}$，满足 $\forall i:\operatorname{MEX}\{p_j\mid j<i\land(p_j,p_i)\in E\}=a_{p_i}$，此处 $\operatorname{MEX}$ 是最小未出现正整数。

提示：

1. 怎么排这个 $p$ 从而简化 $\operatorname{MEX}$？
2. ~~如果你像 @[Peck](luogu://user/372974) 一样认为 OI 不需要任何的定理证明的话，跳过这一步~~如何证明这么搞不行就一定不行？

（提示 1 解答）$\forall i<j:a_{p_i}\le a_{p_j}$，即 $p$ 中所有数的 $v$ 单调不降。每次加入一个数的时侯循环每个边检查一下是否符合就行了。（提示 2 解答）我们的构造方法报告不行就相当于 $\exist (u,v)\in E:a_u=a_v$，或者将他和他所有$a$ 比他小的邻点的 $a$ 放在一个序列里，这个序列出现了「断层」（形式化的，$A:=\operatorname{sorted}(\{0\}\cup\{a_j\mid a_j<a_i,(j,i)\in E\}),\exist i:A_i-A_{i-1}\ge 2$），这种情况不管怎么排他的邻点都做不到满足他的要求。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 5e5 + 5;

ll n, m, tp[MAXN];
vector<ll> e[MAXN], pos[MAXN];

int main() {
    read(n), read(m);
    for (ll i = 1; i <= m; ++i) {
        ll u, v;
        read(u), read(v);
        e[u].empb(v), e[v].empb(u);
    }
    for (ll i = 1; i <= n; ++i) {
        read(tp[i]);
        pos[tp[i]].emplace_back(i);
    }
    for (ll i = 1; i <= n; ++i) {
        for (ll j : e[i]) {
            if (tp[i] == tp[j]) {
                puts("-1");
                return 0;
            }
        }
    }
    for (ll i = 1; i <= n; ++i) {
        set<ll> b;
        for (ll j : e[i]) {
            b.emp(tp[j]);
        }
        for (ll j = 1; j < tp[i]; ++j) {
            if (!b.count(j)) {
                puts("-1");
                return 0;
            }
        }
    }
    for (ll i = 1; i <= n; ++i) {
        for (ll j : pos[i]) {
            write(j), space();
        }
    }
    enter();
	return 0;
}

;             ;;;;;;;;;;;         ;
;                      ;         ; ;
;                    ;          ;   ;
;                   ;          ;     ;
;                 ;           ;;;;;;;;;
;               ;            ;         ;
;              ;            ;           ;
;;;;;;;;;;;   ;;;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：Floating_Trees (赞：1)

## 思路
容易想到的是对一个点 $i$ 与他相连的点中必须要有 $1$ 到 $t_i$ 中的所有数，其没有与其相等的 $t_i$，如果不满足的话就肯定是无解的。

若判断好已经有解，则 $t_i$ 较小的肯定得在 $t_i$ 更大的前面，否则会可能出现 $t_i$ 较大的被操作成了较小的数。那么只要将点按照 $t_i$ 排序后输出点的编号即可。

## 代码
```cpp
#include <bits/stdc++.h>
#define i64 long long
#define endl '\n'

using namespace std;

const int N = 5e5 + 10;
int n, m;
vector<int> v[N];
struct node
{
	int id, t;
	bool operator < (const node & cmp) const 
	{
		return t < cmp.t;
	}
} u[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> m;
	while (m--)
	{
		int a, b; cin >> a >> b;
		v[a].push_back(b), v[b].push_back(a);
	}
	for (int i = 1;i <= n;i++)
		cin >> u[i].t, u[i].id = i;
	for (int i = 1;i <= n;i++)
	{
		map<int,int> mp;
		for (auto e : v[i])
			mp[u[e].t] = 1;
		// cout << mp[1] << " " << mp[2] << endl;
		for (int j = 1;j < u[i].t;j++)
			if (!mp[j])
				cout << -1 << endl, exit(0);
		if (mp[u[i].t]) cout << -1 << endl, exit(0);
	}
	sort(u + 1, u + 1 + n);
	for (int i = 1;i <= n;i++)
		cout << u[i].id << " \n"[i == n];

	return 0;
}
```

---

## 作者：BzhH (赞：1)

不难发现，这个操作序列一定是从标数小的到标数大的

我们可以用一个数组来存下每一种标数的点，然后依次枚举每一个数，

枚举的时候需要考虑两种情况

1.这个点能否被标成 $x$

2.这个点是否与另一个标号相同的点相连

对于第一种情况,只需要记录一下有多少种标号小于它的点即可

时间复杂度 $O(n+m)$

```
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstdlib>
using namespace std;
const int N = 5e5 + 5, M = 2 * N;

int c[N], head[N], ver[M], net[M], idx;
vector<int> p[N], ans;
bool vis[N];

void add(int a, int b)
{
    net[++idx] = head[a], ver[idx] = b, head[a] = idx;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
        p[c[i]].push_back(i);//使用vector来存储
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < p[i].size(); j++)
        {
            int u = p[i][j], cnt = 0;
            for (int x = head[u]; x; x = net[x])
            {
                int v = ver[x];
                if (!vis[c[v]] && c[v] < i)
                    cnt++, vis[c[v]] = true;
                if (c[v] == c[u])
                    cnt = -0x3f3f3f3f;
            }
            if (cnt == i - 1)
                ans.push_back(u);
            else
            {
                printf("-1");
                exit(0);
            }
            for (int x = head[u]; x; x = net[x])
                vis[c[ver[x]]] = false;
        }
    }
    for (int i = 0; i < ans.size(); i++)
        printf("%d ", ans[i]);
    return 0;
}
```

---

## 作者：MVP_Harry (赞：1)

提供一个$O(m + nlogn)$的做法，自认为实现还算比较清晰。

首先，算法就如前几位说的一样，是一个贪心策略。主要观察到了两点：

1. 对于每一个顶点，它相邻的不能有同色（及不是同一个topic）
2. 对于每一个顶点，设它的topic为$t$，则邻居们至少得提供$1$ ~ $(t - 1).$

对于满足这两个条件的图，则贪心的从小到大往上考虑。对于实现，我们可以非常暴力的枚举每个顶点的邻居，因为总共只有$m$条边，复杂度为$O(m).$

代码实现如下（含具体注释）：

```
#include<bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
vector<int> G[maxn];
pair<int, int> topic[maxn]; 
int orginal[maxn]; 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0); 
    int N, M;
    cin >> N >> M;
    // 存图
    for (int i = 1; i <= M; i++) {
    	int u, v;
    	cin >> u >> v;
    	G[u].push_back(v), G[v].push_back(u); 
    }
    // topic[i].first 表示第i个的topic，利用orginal存一下，second是这个点的index
    for (int i = 1; i <= N; i++) cin >> topic[i].first, orginal[i] = topic[i].first, topic[i].second = i;
    // 从小大大排一下序
    sort(topic + 1, topic + N + 1);
	vector<int> ans; // 存答案
	int ulti = 1; // 判断是否可行
	for (int i = 1; i <= N; i++) {
		// 对于排好序的第i个顶点
		pair<int, int> cur = topic[i];
		int id = cur.second; 
		int color = cur.first;
		int flag = 1;
		vector<int> all; // 存邻居们
		for (auto v : G[id]) {
			if (orginal[v] == color) flag = 0;  // 考察第一个条件
			all.push_back(orginal[v]); 
		}
		// 考察第二个条件
		vector<int> check(color + 1, 0); 
		for (auto v : all) if (v < color) check[v] = 1; 
		for (int i = 1; i <= color - 1; i++) if (!check[i]) flag = 0;
		// 不满足就退出
		if (!flag) {
			ulti = 0; 
			break; 
		}
		ans.push_back(id); 
	}
	if (!ulti) {
		cout << -1 << "\n"; 
		return 0; 
	}
	for (auto v : ans) cout << v << " "; 
	cout << "\n"; 
	return 0; 
}
```

---

## 作者：墨染琉璃殇 (赞：1)

### 本蒟蒻又来写题解了......

这道题题目稍微有点不好理解（ ~~我英语太菜了~~），我很久才看懂。
## 一个神奇的东西：auto，一会要用，巨佬可以跳过。

[别人的介绍](https://blog.csdn.net/xiaoquantouer/article/details/51647865)

**~~实在不想看就算了，不影响解题。~~**

### 题目大意：

给定一张 $n$ 条边，$m$ 个点的图，要你给每个点填上数字，要求是该数字是已经标注的点中以及其相邻的点中没出现过的最小值，且会给出每个点需要标的数，求注点的顺序。

### 思路：

考虑当前点的赋值是邻居的 $MEX$ 。那么值**比该点大**的邻居都是没有用的。

于是我们可以从小往大加入点。然后就是判断合不合法，存在合法解**当且仅当**：

1.没有两个**数值相同**的点相邻。

2.对于一个点，所有数值**小于它**的数都在**它的邻居**出现过。

所以，我们可以运用**贪心**的思想来写。我们可以看出，只要**从小到大**来填，就可以达到目标。令**初始期望值**为1，那么首先我们把为期望值为1的都填上，然后对每个 $u$ 判断一下相邻结点 $v$ 的期望值是否也为1，如果是， $v$ 的期望值 $++$ 

依次类推，我们可以证明其正确性，因为是**从小**开始填的，所以保证当前比 $u$ 值小的都填了,所以就可以直接判断了。

只要当前结点 $u$ 的期望是**原来的** $i$ 就可以直接返回 $-1$ 了。

### $AC$ $Code:$
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500005
using namespace std;
ll a[N],n,m;
vector<int> e[N];
vector<int> ct;
vector<int> C[N];
inline ll read()
{
   int x=0,f=1;
   char ch=getchar();
   while(ch<'0'||ch>'9')
   {
       if(ch=='-') f=-1;
       ch=getchar();
   }
   while(ch>='0'&&ch<='9')
   {
       x=(x<<1)+(x<<3)+(ch^48);
       ch=getchar();
   }
   return x*f;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		ll u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		ll c=read();
		C[c].push_back(i);
		a[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		  for(auto u:C[i])\\auto是一个神奇的用法，方便声明变量。也可以不用它，直接写变量类型也可以过。主要是因为我懒，所以用的这个。
		  {
		  	 	if(a[u]!=i) puts("-1"),exit(0);
		  	 	for(auto v:e[u])\\同上
		  	 		if(a[v]==i) a[v]++;
		  	 	ct.push_back(u);
		  }
	}
	for(auto i:ct) \\同上
	printf("%d ",i); 
	return 0;
} 
```
$Thanks$

~~部分思路借鉴老师。~~



---

## 作者：AK_400 (赞：0)

首先，若存在两点颜色相同且存在一条边连接这两点，那么无解。

然后 bfs 即可。具体地，记 $S_i$ 为结点 $i$ 的已选邻居的颜色集合，$mx_i$ 表示 $S_i$ 中最小的没出现的正整数，每搜到一个点，枚举它的邻居，将未访问的结点的颜色集合加入当前点的颜色，暴力更新 $mx_i$ 即可，如果 $t_x=mx_x$，那么加入队列。如果无法每个点都访问到就无解。

复杂度：$\mathcal O(\sum_{i=1}^{n}(|S_i|\log|S_i| )+n+m)=\mathcal O(n+m\log m)$，因为每条边的两个端点会向对方的颜色集合中贡献一个集合，所以颜色集合的大小和和边数同阶。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,t[500005];
vector<int>e[500005],ans;
void read(int &x){
    x=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+(c^48),c=getchar();
}
set<int>in[500005];
int mx[500005];
bool vis[500005];
void bfs(){
    queue<int>q;
    for(int i=1;i<=n;i++){
        mx[i]=1;
        if(t[i]==1)q.push(i);
    }
    while(q.size()){
        int p=q.front();
        q.pop();
        if(vis[p])continue;
        vis[p]=1;
        ans.push_back(p);
        for(int x:e[p]){
            in[x].insert(t[p]);
            while(in[x].count(mx[x]))mx[x]++;
            if(mx[x]==t[x])q.push(x);
        }
    }
}
void slv(){
    read(n),read(m);
    for(int i=1;i<=m;i++){
        int u,v;
        read(u),read(v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        read(t[i]);
    }
    for(int i=1;i<=n;i++){
        for(int x:e[i]){
            if(t[i]==t[x]){
                cout<<-1<<endl;
                return ;
            }
        }
    }
    bfs();
    if(ans.size()!=n)cout<<-1<<endl;
    else for(int x:ans)printf("%lld ",x);
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：Shirο (赞：0)

### 题意
给定一个无向图，给其染色为已染色的相邻点的 $Mex$ ，求染成 $t_i$ 的方案
### 做法
观察到，一个点若要染色成 $co$ ，其相邻点必须包括 $[1,co-1]$ ，同时不能出现另一个点的 $t_i = co$ 。判断完毕合法性后，我们可以通过从小到大对颜色进行排序，染色即可
### 代码
```cpp
vector<int> g[maxn];
vector<int> ans[maxn];
void add(int x,int y){g[x].push_back(y);}
int n,m,t[maxn];
bool check(int x)
{
	int val=t[x];
	set<int> cur;
	for(auto to:g[x])
		cur.insert(t[to]);
	if(cur.count(val))return 0;
	for(int i=1;i<val;++i)
		if(!cur.count(i))
			return 0;
	return 1;
}
int main()
{
	n=__,m=__;
	for(int i=1;i<=m;++i)
	{
		int u=__,v=__;
		add(u,v);add(v,u);
	}
	int maxx=0;
	for(int i=1;i<=n;++i)t[i]=__,maxx=max(maxx,t[i]);
	int sol=1;
	for(int i=1;i<=n;++i)
		sol&=check(i);
	if(!sol)return puts("-1"),0;
	for(int i=1;i<=n;++i)
		ans[t[i]].push_back(i);
	for(int i=1;i<=maxx;++i)
	{
		for(auto j:ans[i])
			cout<<j<<' ';
	}
}


```


---

## 作者：流绪 (赞：0)

每次选的都是邻居没选过的主题，那肯定从所需主题最小的开始往大的填！这样子最优。

证明：如果按上述方法填，较小的邻居已经符合题意的填好了，较大的邻居还没填，那么可以就可以找到最小的可填数啦。如果这个数偏小，则这个位置应该过会填，可是他的还没填的邻居都是比他大的，无法实现这个可能；如果这个数偏大或等于，那更不可能了，因为这种情况的话这个位置应该之前就填过了！所以现在这个位置最小可填数不等于其所需的事，肯定没有其他方法填啦。

画外音：比赛时不知道脑子怎么想的，以为是找到一个起点然后从这个点向外填。自闭了。

下面是 $AC$ 代码。
```cpp
#include<bits/stdc++.h>
#define int int
#define ld long double
#define ri register int
#define il inline
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define pii pair<int,int>
#define vi vector<int>
#define vii vector<pii>
#define all(x) x.begin(),x.end() 
#define rep(i,a,b) for(ri i=(a);i<=(b);++i)
#define per(i,a,b) for(ri i=(a);i>=(b);--i)
#define ls (x<<1)
#define rs (x<<1|1)
#define mid (l+r>>1)
#define db(x) cout << "#x:" << x << endl
#define dd() cout << "Out put!\n"
const int mod=1e6+7,eps=1e-6,pi=acos(-1.0),maxn=5*1e5+100;
using namespace std;
int val[maxn];
vi e[maxn];
vii v;
int check(int x)//查找该位置可填的最小数
{
	set<int>s;
	for(auto i:e[x])
		s.insert(val[i]);
	val[x] = 1;
	while(s.count(val[x]))
		val[x]++;
	return val[x];
}
signed main()
{
	ios::sync_with_stdio(0);
	int n,m;
	cin >> n >> m;
	rep(i,1,m)
	{
		int u,v;
		cin >> u >> v;
		e[u].pb(v);
		e[v].pb(u);
	}
	rep(i,1,n)
	{
		int x;
		cin >> x;
		v.pb(mk(x,i));
	}
	sort(all(v));//对要填的数大小进行排序
	vi ans;
	for(auto i:v)
	{
		if(check(i.se)!= i.fi)//若该位置可填的最小值和所需的不同
		{					//即没有其他方法可以填了
			puts("-1");
			return 0;
		}
		ans.pb(i.se);//否则压入答案数组
	}
	for(auto i:ans)
		cout << i <<" "; 
	return 0;
}

```


---

