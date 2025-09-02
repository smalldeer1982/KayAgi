# Tweetuzki 爱序列

## 题目背景

本题为改编题

## 题目描述

Tweetuzki 有一个长度为 $n$ 的序列 $a_1, a_2, \cdots, a_n$。

他希望找出一个最大的 $k$，满足在原序列中存在一些数 $b_1, b_2, \cdots, b_k$（可打散在原序列中的顺序），满足对于任意的 $i(1 \le i < k)$，$b_i \div 3 = b_{i+1}$（这时 $b_i$ 必须能够被 $3$ 整除）或 $b_i \times 2 = b_{i+1}$。并输出这个序列。

## 说明/提示

**_Subtask_ #1 _(20 points)_：$2 \le n \le 8$；**  
**_Subtask_ #2 _(30 points)_：$2 \le n \le 100, 1 \le a_i \le 7 \times 10^8$；**  
**_Subtask_ #3 _(20 points)_：$2 \le n \le 1000, 1 \le a_i \le 1000$；**  
**_Subtask_ #4 _(30 points)_：$2 \le n \le 10^5, 1 \le a_i \le 3 \times 10^{18}$。**

## 样例 #1

### 输入

```
6
4 8 6 3 12 9
```

### 输出

```
6
9 3 6 12 4 8 
```

## 样例 #2

### 输入

```
4
42 28 84 126
```

### 输出

```
4
126 42 84 28 
```

## 样例 #3

### 输入

```
5
4 8 16 12 24```

### 输出

```
4
12 24 8 16```

# 题解

## 作者：Tzs_yousa (赞：6)

正在切数论的我乍一看还以为是数论，结果思考了一下后才发现原来是建图和搜索。
#### 通过将第一个样例画图之后，可以发现输出最后的结果就是图中的最长链，所以肯定是要建图的。
但我们要不要搜索？这数据范围显然是会爆炸，但是搜索可以剪枝啊，而且这个题可以剪大枝，这样就可以优化很多。
# 剪枝
只有一处剪枝，就是把当前位置的最大深度存一下，如果有别的父亲节点走到自己并且自己这个节点的已知最大深度小于当前这个新的路径的自己的当前深度，那就可以直接将这个边跳过。

剪枝如下：
这里是手写了一个栈用来存走过的路径，$v$ 数组存当前节点最大深度，栈顶 $top$ 就是当前路径该节点的深度
最后统计一下即可 
```cpp
void dfs(int x, int fa)
{
	st[++top] = x;
	if(top > v[x])
	{
		v[x] = top;
		for (int i = head[x]; i; i = e[i].next)
		{
			int v = e[i].to;
			dfs(v);
		}
		if(top > maxn) 
		{
			maxn = top;
			for (int i = 1; i <= top; i++)
			{
				ans[i] = st[i];
			}
		}
		top--;
	}
	else top--;
}
```
# 二分建边
如果我们一个一个建边，那会是平方的复杂度，所以可以用二分来降低一个对数级别的复杂度。
建边如下：
```cpp
struct edge{
	int next, to;
}e[MAXN];
```
```cpp
void add(int x, int y)
{
	e[++cnt].to = y;
	e[cnt].next = head[x];
	head[x] = cnt;
}
```
```cpp
for (int i = 1; i <= n; i++)
{
	if(b[i] % 3 == 0) 
	{
		int it = lower_bound(b + 1, b + n + 1, b[i] / 3) - b;
		if(b[it] == b[i] / 3) add(i, it), ru[it]++;
	}
	int it = lower_bound(b + 1, b + n + 1, b[i] * 2) - b;
	if(b[it] == b[i] * 2) add(i, it), ru[it]++;
}
```
此时我们的复杂度已经降得比较低了，直接就可以过啦！
# AC code
```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXN = 2e6 + 10;
using namespace std;
int n, a[MAXN], b[MAXN], ru[MAXN], ans[MAXN], st[MAXN], maxn, top, cnt, head[MAXN];
struct edge{
	int next, to;
}e[MAXN];
void add(int x, int y)
{
	e[++cnt].to = y;
	e[cnt].next = head[x];
	head[x] = cnt;
}
void dfs(int x, int fa)
{
	st[++top] = x;
	if(top > v[x])
	{
		v[x] = top;
		for (int i = head[x]; i; i = e[i].next)
		{
			int v = e[i].to;
			dfs(v);
		}
		if(top > maxn) 
		{
			maxn = top;
			for (int i = 1; i <= top; i++)
			{
				ans[i] = st[i];
			}
		}
		top--;
	}
	else top--;
}
signed main()
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &b[i]);
	}
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
	{
		if(b[i] % 3 == 0) {
			int it = lower_bound(b + 1, b + n + 1, b[i] / 3) - b;
			if(b[it] == b[i] / 3) add(i, it), ru[it]++;
		}
		int it = lower_bound(b + 1, b + n + 1, b[i] * 2) - b;
		if(b[it] == b[i] * 2) add(i, it), ru[it]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if(ru[i] == 0) dfs(i, 0);
	}
	for (int i = 1; i <= n; i++) if(dep[i] > maxn) maxn = dep[i];
	printf("%lld\n", maxn);
	for (int i = 1; i <= maxn; i++) printf("%lld ", b[ans[i]]);
	return 0;
} 
```


---

## 作者：一扶苏一 (赞：5)

## Solution

考虑DP。

设 $f_i$ 是以 $i$ 这个数结尾的最长 ans，于是  $f_i~=~\max(f_{i\div3}~,~f_{i\times2})~+~1$ 。其中若从第一项转移过来则必须 $3|x$，能从一个数转移当且仅当这个数在序列中出现过。

考虑这么做为什么是可以的，会产生可不可以的问题因为一个转移位置比 $i$ 大，一个转移位置比 $i$ 小，为什么转移不会存在环。

反证法，考虑转移图存在环的情况，则有

$$x~\times~(\frac{1}{3})^a~\times~2^b~=~x$$

$$\Rightarrow~(\frac{1}{3})^a~\times~2^b~=~1~,~a,b~\in~Z^+$$

然而这个方程一定是无解的。考虑分母是 $3^a$，恒为一个奇数，分子是 $2^b$，恒为一个偶数。一个偶数和一个奇数约分永不可能得 $1$。于是方程无解，于是转移图不存在环。证毕。

下一个问题是按照什么顺序更新DP，dzy神仙是按照幂次的不降序更新的，rqy神仙是按照幂次分类更新的，反正这俩我都不会，于是怒写一发记忆化搜索乱搞一波，管他什么顺序更新（雾

考虑 $n$ 特别小，$O(n\log n)$挂上一大串常数都没问题，于是直接用map存DP值，再用map存是否出现，最后再用map存转移方向即可。

## Code

```cpp
#include <map>
#include <vector>
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#define putchar(o) \
puts("I am a cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 100010;

int n;
ll ans;
ll MU[maxn];
std::map<ll,int>frog;
std::map<ll,bool>oc;
std::map<ll, ll>pre;

ll dfs(ll);
void print(ll);

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1; i <= n; ++i) qr(MU[i]);
	for (rg int i = 1; i <= n; ++i) oc[MU[i]] = true;
	for (rg int i = 1; i <= n; ++i) {
		frog[MU[i]] = dfs(MU[i]);
		if (frog[ans] < frog[MU[i]]) ans = MU[i];
	}
	qw(frog[ans], '\n', true);
	print(ans);
}

ll dfs(ll x) {
	if (frog[x]) return frog[x];
	ll tp = 1, ttp = 0;
	if (!(x % 3)) {
		if (oc[x / 3]) tp = dfs(x / 3) + 1, ttp = x / 3;
	}
	if (oc[x << 1]) {
		ll qwq = dfs(x << 1) + 1;
		if (tp < qwq) tp = qwq, ttp = x << 1;
	}
	pre[x] = ttp;
	return frog[x] = tp;
}

void print(ll x) {
	if (!x) return;
	qw(x, ' ', true);
	print(pre[x]);
}
```



---

## 作者：冷却心 (赞：2)

首先如果我们将每个数 $x$ 对 $\frac{x}{3},2x$ 连边，然后发现答案就是这张图的最长链。但是边数有点爆炸，考虑删去一些不必要的边。

首先证明这个不会成环：

> 证：反证法，如果他成环了，表示有一个数 $A$ 能经过若干次除以 $3$ 或乘以 $2$ 变成 $B$，而 $B$ 也可以经过若干次操作变成 $A$，我们不妨设 $A$ 除以 $a$ 次 $3$，乘以 $b$ 次 $2$ 变成 $B$，$B$ 除以 $c$ 次 $3$，乘以 $d$ 次 $2$ 变成 $A$。列出方程组为：
>
> $$\left\{\begin{aligned}\frac{A\times2^b}{3^a}=B,\\ \frac{B\times 2^d}{3^c}=A.\end{aligned}\right.\Rightarrow B=\frac{A\times3^c}{2^d}=\frac{A\times2^b}{3^a}\Rightarrow 3^{a+c}=2^{b+d}.$$
>
> 由于 $a,b,c,d$ 都是整数，显然这个方程恒不等，不存在满足成环条件的 $A,B$。所以不会成环。

并且根据这个性质，既然没有环，$b$ 数组内的数不会相同，所以重复的数可以算一个，直接去重。

所以这张图是有向无环图，可以直接跑拓扑最长链。时间复杂度是 $O(n\log V)$，主要复杂度在排序去重以及寻找值为 $2x,\frac{x}{3}$ 的数对应的编号上，这里使用了 `map`，而拓扑是 $O(n)$ 的，因为边是 $O(n)$ 条，去重后每个点至多有两条出边。

输出方案就直接记录一个当前点的最长链的上一个点即可。

代码很短。
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
int n, f[N], opt[N], in[N]; LL A[N], Ans[N];
map<LL, int> mp; vector<int> G[N];
int main() {
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) { cin >> A[i]; }
	sort(A + 1, A + 1 + n); n = unique(A + 1, A + 1 + n) - A - 1;
	for (int i = 1; i <= n; i ++) mp[A[i]] = i;
	for (int i = 1; i <= n; i ++) { f[i] = 1;
		if (A[i] % 3 == 0 && mp.count(A[i] / 3)) {
			int v = mp[A[i] / 3]; G[i].emplace_back(v); in[v] ++;
		} if (mp.count(A[i] * 2)) {
			int v = mp[A[i] * 2]; G[i].emplace_back(v); in[v] ++;
		}
	}
	queue<int> q; // Topo
	for (int i = 1; i <= n; i ++) if (!in[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : G[u]) {
			if (f[u] + 1 > f[v]) { f[v] = f[u] + 1, opt[v] = u; } in[v] --;
			if (!in[v]) q.push(v);
		}
	}
	int cur = 0;
	for (int i = 1; i <= n; i ++) {
		if (f[i] > f[cur]) cur = i;
	} int tot = f[cur];
	cout << tot << "\n";
	for (int i = tot; i >= 1; cur = opt[cur], i --) Ans[i] = A[cur];
	for (int i = 1; i <= tot; i ++) cout << Ans[i] << " \n"[i == tot];
	return 0;
}
```

---

## 作者：Limit (赞：2)

# 题目大意

给出一些数,需要求出 $\frac{a_{i+1}}{3}=a_i$ 或 $a_{i+1}=2 \times a_i$ 时最长的序列 $a$.

# 分析

可以发现符合条件的序列 $a$ 中不会出现重复的数字,而且对于一个数它的下一个位置最多只有两种情况,于是问题就变成了无环有向图最长链,这样就可以想到记忆化搜索,$f_i$ 表示 $i$ 为起点时的最长链长度,为了记录下路径,所以还需要用一个 $nxt_i$ 表示 $i$ 的下一个位置时什么,最后直接输出就好了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=1e6+7;
int N;
struct Edge//链式前向星
{
	int to,next;
}edge[MAXN*2];
int edge_head[MAXN];
int edge_cnt=0;
#define TO_POINT(now) for(int edge_i=edge_head[now];edge_i;edge_i=edge[edge_i].next)
#define TO edge[edge_i].to
void AddEdge(int f,int t)
{
	edge[++edge_cnt].to=t;
	edge[edge_cnt].next=edge_head[f];
	edge_head[f]=edge_cnt;
}
bool visit[MAXN];
long long arr[MAXN];//原数组
long long a[MAXN];//去重以后的数组
int f[MAXN];//记录每个位置的最长链长度
int Find(long long num)//二分查找是否存在这个数
{
	int left=1,right=N,middle;
	while(left<=right)
	{
		middle=(left+right)>>1;
		if(a[middle]>=num)
		{
			right=middle-1;
			if(a[middle]==num)
			{
				return middle;
			}
		}
		else
		{
			left=middle+1;
		}
	}
	return 0;
}
int nxt[MAXN];//记录下一个位置
void DFS(int now)//DFS
{
	if(f[now])//如果搜索过就不需要搜索了
	{
		return;
	}
	f[now]=1;//开始的长度为1
	TO_POINT(now)
	{
		DFS(TO);
		if(f[TO]+1>f[now])//找到在自己连出的边中的最长链长度
		{
			f[now]=f[TO]+1;
			nxt[now]=TO;//记录下一个位置
		}
	}
}
int main()
{
	scanf("%d",&N);
	REP(i,1,N)
	{
		scanf("%lld",&arr[i]);
	}
	sort(arr+1,arr+1+N);
	arr[0]=arr[1]-1;
	int cnt=0;
	REP(i,1,N)//去重
	{
		if(arr[i]!=arr[i-1])
		{
			a[++cnt]=arr[i];
		}
	}
	N=cnt;
	int l;
	REP(i,1,N)//对于每一个点连边
	{
		if(a[i]%3==0)//需要判断整除
		{
			l=Find(a[i]/3);
			if(l)
			{
				AddEdge(i,l);
			}
		}
		l=Find(a[i]*2);
		if(l)
		{
			AddEdge(i,l);
		}
	}
	int answer=0,st;
	REP(i,1,N)//如果没有访问过就DFS这个位置
	{
		if(!f[i])
		{
			DFS(i);
		}
		if(f[i]>answer)//记录下最长链的开头
		{
			answer=f[i];
			st=i;
		}
	}
	printf("%d\n",answer);//输出答案
	int now=st;
	while(now)
	{
		printf("%lld ",a[now]);
		now=nxt[now];
	}
	return 0;
}

```

---

## 作者：hhhyyyfff (赞：2)

## 算法

- 暴力枚举+剪枝

## 思路

- 虽然正解是DP，但暴力枚举剪枝后居然也能过！！！

 ### 预处理
 
 - 按要求输入数据
 
 - 排序
 
 ### 枚举

 - **循环枚举**选择的**第一个数**，**递归枚举**选择的**其余数**。
 
 ### 优化
 
 - 用**二分查找**寻找序列下一个数的位置
 
 - 当选择的序列**不能再增长时**统计答案
 
 ### 输出
 
 - 按要求输出答案

## 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
//含义见题目
int n,k;
//a含义见题目，ans储存答案序列，now储存当前枚举的序列
unsigned long long a[100010],ans[100010],now[100010];
//用于标记
bool b[100010];
//二分查找x再原序列中的位置
int findx(unsigned long long x){
    int l=1,r=n,mid;
    while(l<r){
        mid=(l+r)>>1;
        if(a[mid]==x)
            return mid;
        if(a[mid]<x)
            l=mid+1; else
            r=mid;
    }
    if(a[l]==x)
        return l;
    return -1;
}
//递归枚举答案
void dfs(int len,int pos){
    //标记
    b[pos]=1;
    //记录
    now[len]=a[pos];
    //枚举下一个数为当前的数*2
    bool flag=0;
    //查找下一位位置
    int tmp=findx(a[pos]*2);
    if(tmp!=-1 && !b[tmp]){
        flag=1;
        dfs(len+1,tmp);
    }
    //枚举下一个数为当前的数/3
    if(a[pos]%3==0){
        //查找下一位位置
        tmp=findx(a[pos]/3);
        if(tmp!=-1 && !b[tmp]){
            flag=1;
            dfs(len+1,tmp);
        }
    }
    //如果序列不在增长，统计答案
    if(!flag && len>k){
        k=len;
        for(int i=1;i<=len;++i)
            ans[i]=now[i];
    }
    //取消标记
    b[pos]=0;
}
int main(){
    //预处理
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%llu",&a[i]);
    sort(a+1,a+n+1);
    //枚举
    for(int i=1;i<=n;++i)
        dfs(1,i);
    //输出
    printf("%d\n",k);
    for(int i=1;i<=k;++i)
        printf("%llu ",ans[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：Liang_9 (赞：1)

## 题意分析：
在给定序列 $a$ 中，重新排列顺序，找出一个最长序列，使得序列中的每个元素 $b_{i} $ 满足 $b_{i} = b_{i-1} \div 3 $ 或者 $b_{i} = b_{i-1} \times 2$。

## 关键结论和证明：
- **结论**：当一个数 $x$ 经过多次变换（除以$3$ 或乘以 $2$ ）后，不可能回到 $x$，即不会产生环。  
- **证明**：假设 $x$ 经过 $p$ 次 $\div 3$，$q$ 次 $\times 2 $，此时的 $x'= \frac { 2^{q} }{ 3 ^ {p} } \cdot x $，因为 $2$ 与 $3$ 互质，所以可以得到 $x'\neq x$。

## 解题思路
- 将所有 $a_{i}$ 向 $a_{i} \times 2$ 和 $a_{i}\div 3$ 连边，即可得到一张有向无环图。此时的最长数列就是图上的最长链。  
- 利用拓扑的原理，BFS 找到最长链，并在更新的时候记录前序结点，来输出结果。  
- 总时间复杂度 $O(n)$。

## 代码实现  

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int n,res;
vector<int> e[N];//建图
int din[N],dis[N];
int ans[N],pre[N];
int a[N];
//记录a对应的位置
map<int,int> s;

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],s[a[i]]=i;
    
    for(int i=1;i<=n;i++)
    {
        //建图并记录入边数
        if(s.find(a[i]*2)!=s.end()) e[i].push_back(s[a[i]*2]),din[s[a[i]*2]]++;
        if(a[i]%3==0&&s.find(a[i]/3)!=s.end()) e[i].push_back(s[a[i]/3]),din[s[a[i]/3]]++;
    }
    queue<int> q;
    //没有入边，是起点
    for(int i=1;i<=n;i++) if(!din[i])  q.push(i),dis[i]=1,pre[i]=0;
    
    //bfs
    while(q.size())
    {
        int u=q.front();
        q.pop();
        
        //更新答案
        if(dis[u]>dis[res]) res=u;
        
        for(auto v:e[u])
        {
            if(dis[v]<dis[u]+1)
            {
                //dis记录路径上点数
                dis[v]=dis[u]+1;
                //pre记录前序结点
                pre[v]=u;
                q.push(v);
            }
        }
    }
    
    //方便输出答案
    for(int i=dis[res],k=res;i&&k;i--,k=pre[k])
    ans[i]=k;
    
    cout<<dis[res]<<'\n';
    for(int i=1;i<=dis[res];i++)
    cout<<a[ans[i]]<<' ';
}
```

---

## 作者：SSerxhs (赞：1)

一个数的后继只能是*2和/3，这意味着一个数字不可能同时出现两次，即数字出现次数是没有意义的。可以视为不重复

由于数字不重复，可以抽象为点，*2和/3可以抽象为有向边，则合法序列必定是这张图上的一条链。spfa判最长路即可，也可以根据图的dag性拓扑排序。

spfa略卡常，卡常头文件已去

```cpp
#include <stdio.h>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
typedef long long ll;
const int N=1e5+2;
map<ll,int> jl;
map<ll,bool> ed;
map<ll,ll> pre;
ll dl[N*500],st[N];
ll x,ans2;
int tou,wei,n,i,j,ans1=1,tp,c,y;
inline void read(ll &x)
{
    c=getchar();
    while ((c<48)||(c>57)) c=getchar();
    x=c^48;c=getchar();
    while ((c>=48)&&(c<=57))
    {
        x=x*10+(c^48);
        c=getchar();
    }
}
inline void read(int &x)
{
    c=getchar();
    while ((c<48)||(c>57)) c=getchar();
    x=c^48;c=getchar();
    while ((c>=48)&&(c<=57))
    {
        x=x*10+(c^48);
        c=getchar();
    }
}
int main()
{
    read(n);
    tou=1;
    for (i=1;i<=n;i++)
    {
        read(x);jl[x]=1;
        dl[++wei]=ans2=x;
    }
    while (tou<=wei)
    {
        ed[x=dl[tou++]]=0;
        if (x%3==0) y=jl[x/3];
        if ((x%3==0)&&(y<jl[x]+1)&&(y))
        {
            y=jl[x/3]=jl[x]+1;
            if (!ed[x/3]) ed[dl[++wei]=x/3]=1;
            pre[x/3]=x;
            if (ans1<y)
            {
                ans1=y;
                ans2=x/3;
            }
        }
        y=jl[x<<1];
        if ((y)&&(y<jl[x]+1))
        {
            y=jl[x<<1]=jl[x]+1;
            if (!ed[x<<1]) ed[dl[++wei]=x<<1]=1;
            pre[x<<1]=x;
            if (ans1<y)
            {
                ans1=y;
                ans2=x<<1;
            }
        }
    }
    printf("%d\n",ans1);
    st[tp=1]=ans2;
    while (ans2) st[++tp]=ans2=pre[ans2];
    --tp;
    while (tp) printf("%lld ",st[tp--]);
}
```

---

## 作者：xukehg (赞：0)

简单题。

首先有一个很明显的性质：构造出来的序列不存在重复的数，证明是显然的，$2$ 与 $3$ 的最大公约数是 $1$。

然后考虑图论建模，把 $a_i$ 可能的上一位与下一位连边，由于上述性质，原图无环，直接大力记忆化搜索就可以得到第一问的答案。第二问也很好做：沿着记忆化搜索的记录搜集即可。注意数组稍微开大一点。

code:
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;

int n,tot;
int a[N];
unordered_map<int,int> mp;
int temp[N * 5],temp2[N * 5];
vector<int> e[N * 5];
int dp[N * 5];
int dfs(int u){
	if (dp[u]) return dp[u];
	dp[u] = 1;
	for (int v : e[u]) dp[u] = max(dp[u],1 + dfs(v));
	return dp[u];
}
void dfs2(int u,int cnt){
	cout << temp2[u] << " ";cnt--;
	for (int v : e[u]){
		if (dp[v] == cnt){
			dfs2(v,cnt);
			return;
		}
	}
}
signed main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for (int i = 1;i <= n;i++){
		cin >> a[i];
		if (mp[a[i]] == 0) mp[a[i]] = ++tot;temp[mp[a[i]]]++,temp2[mp[a[i]]] = a[i];
		if (a[i] % 2 == 0 && mp[a[i] / 2] == 0) mp[a[i] / 2] = ++tot;
		if (a[i] % 3 == 0 && mp[a[i] / 3] == 0) mp[a[i] / 3] = ++tot;
		if (mp[a[i] * 3] == 0) mp[a[i] * 3] = ++tot;
		if (mp[a[i] * 2] == 0) mp[a[i] * 2] = ++tot;
	}
	for (int i = 1;i <= n;i++){
		int num1 = mp[a[i]],num2 = mp[a[i] / 2],num3 = mp[a[i] / 3],num4 = mp[a[i] * 2],num5 = mp[a[i] * 3];
		if (a[i] % 2 == 0 && temp[num2]) e[num2].push_back(num1);
		if (a[i] % 3 == 0 && temp[num3]) e[num1].push_back(num3);
		if (temp[num4]) e[num1].push_back(num4);
		if (temp[num5]) e[num5].push_back(num1);
	}
	int ans = 0;
	for (int i = 1;i <= n;i++) ans = max(ans,dfs(mp[a[i]]));
	cout << ans << "\n";
	for (int i = 1;i <= n;i++){
		if (dp[mp[a[i]]] == ans){
			dfs2(mp[a[i]],ans);
			return 0;
		}
	}
}
```

---

## 作者：_yolanda_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5080)

[更好地阅读体验](https://www.cnblogs.com/yolanda-yxr/p/16597229.html)


## 解题思路

有个很明显的性质：每个数只会出现一次。（大概是因为 $2$ 和 $3$ 互质）

可以感性理解一下：每次除以 $3$ 或乘以 $2$ 之后，得到的因子 $2$ 永远不可能再失去，失去的 $3$ 也不可能再回来。

所以可以考虑建边，对于每个 $x$ 向 $x \div 3(x\bmod 3=0)$ 和 $2x$ 连边有向边，前提是这两个目标数存在。

这样很明显就构成了一个 DAG。要求的就是最长链，考虑拓扑排序和 DP（很基础的）。

还有一点就是要记录每个点转移来的点是谁，最后 dfs 输出路径。

具体细节看代码吧。

```cpp
#include<bits/stdc++.h>
#define Code using
#define from namespace
#define yolanda std
Code from yolanda;
#define int long long
inline int read(){
	int sum=0,f=1;char a=getchar();
	while(a<'0' || a>'9'){if(a=='-') 	f=-1;a=getchar();}
	while(a>='0' && a<='9') 	sum=sum*10+a-'0',a=getchar();
	return sum*f;
}

unordered_map<int,int> pre,d,f;//直接用map就不用离散化了
//f[x]就是到当前点的最长长度
int n,ma,ans;
int a[100005];

void topo(){//拓扑排序
	queue<int> q;
	for(int i=1;i<=n;++i)
		if(!d[a[i]])	q.push(a[i]);
	while(q.size()){
		int x=q.front();q.pop();
		if(f[x]>ma)	ma=f[x],ans=x;//ma是最大值，ans是终止点
		if(f[x*2]){
			--d[x*2];
			if(f[x]+1>f[x*2])	f[x*2]=f[x]+1,pre[x*2]=x;
			if(!d[x*2])	q.push(x*2);
		} 
		if(x%3==0 && f[x/3]){
			--d[x/3];
			if(f[x]+1>f[x/3])	f[x/3]=f[x]+1,pre[x/3]=x;
			if(!d[x/3])	q.push(x/3);
		} 
	}
}
void print(int x){//输出
	if(!x)	return;
	print(pre[x]);
	printf("%lld ",x);
}

signed main(){
	
	cin>>n;
	for(int i=1;i<=n;++i)
		a[i]=read(),f[a[i]]=1;
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=n;++i){//建边
		if(f[a[i]*2])	++d[a[i]*2];
		if(a[i]%3==0 && f[a[i]/3])	++d[a[i]/3];
	}
	topo();
	printf("%lld\n",ma);
	print(ans);
	
	return 0;
}
```

---

## 作者：荣耀南冥 (赞：0)

# P5080 Tweetuzki 爱序列
[原题传送门](https://www.luogu.com.cn/problem/P5080)

## 题意
给出一个序列，选出k个数，满足$i (1≤i<k)$，$b_i \div 3 = b_{i+1} $（这时$ b_i$ 必须能够被 $ 3 $ 整除）或 $ b_i \times 2 = b_{i+1}$。求 $ k $ 最大值并输出方案
## solution
题中特别标注最后可打散在原序列中的顺序，并且最后要求数列是只有除 $ 3 $ 和乘 $2$ ，所以每一个重复的数是没有作用的，所以排序然后去重方便最后处理。然后一个很重要的~~正解~~(骗分)考虑方向就出来了，那就是强行把这种类似数论的题转成图论(~~好像已经有dalao写了类似的，但我还是发了这个题解~~)。比如[P3940分组](https://www.luogu.com.cn/problem/P3940)，不会正解，强行转成图论跑tarjan也可以拿四十多分。我本题想的是排完序后二分查找建图，然后拓扑排序+DP，定义dp[i][0]表示以i结尾，由上一个$ \div 3 $转移过来的最长长度，dp[i][1]表示以i结尾又由上一个 $\times 2$ 转移过来的最长长度，然后拓扑排序，统计答案即可。

想到最后统计结果的时候和上一位到底是怎么转移过来的并没有任何关系，所以第二维可以直接删掉，直接定义 dp[i] 表示以 i 结尾的最长长度，统计答案时，考虑到 dp[i] 长度都是合法的，所以 DFS 时只需要关心这个点和你要回溯的点有没有连边以及 $ dp[u] = dp[v] - 1 $ 即可。

$ Code $
```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc getchar()
#define v edge[i].to
#define vv e[i].to
int n,tot,ans,ansv,cnt;
long long a[1000000+10];
struct Edge{
	int to,next;
}edge[1000000+10],e[1000000+10];
int head[1000000+10],he[1000000+10],d[1000000+10];
queue<int> q;
int dp[1000000+10],num[1000000+10];

inline long long read(){//快读一定要用long long ，不要a数组用long long然后快读还是int，别问怎么知道的，刚因为这个交了一页
	long long r = 0,l = 1;char ch = gc;
	while(!isdigit(ch)){if(ch == '-')l = -1;ch = gc;}
	while(isdigit(ch)){r = (r << 3) + (r << 1) + ch - '0';ch = gc;}
	return r * l;
}

inline void add(register const int x,register const int y){//建单向边
	edge[++ tot]=(Edge){y,head[x]};
	head[x] = tot;d[y] ++;
}

inline void add2(register const int x,register const int y){//反边另存，只用来回溯
	e[++ cnt] = (Edge){y,he[x]};
	he[x] = cnt;
}

inline int lowerbound(register int l,register int len,register const long long x,register int half=0){//抄的 stl 的 lower_bound ，因为在namespace std里，所以 std 不会出错，抄就完了
	while(len>0){
		half = len>>1;
		if(a[l+half]<x)l += half+1,len -= half+1;
		else len = half;
	}
	return l;
}

int p;
void DFS(register const int u){//回溯统计答案，虽然是spj，但是不确定最后要求是不是要输出满足条件的顺序还是无序即可，保险起见按条件顺序输出
	if(!dp[u])return;
	for(int i = he[u];i;i = e[i].next){
		if(dp[vv] == dp[u] - 1){
			num[++ p] = vv;
			DFS(vv);
			return;
		}
	}
}

int main(){
	n = read();
	for(int i = 1;i <= n;++ i)a[i] = read();
	sort(a + 1,a + n + 1);n = unique(a + 1,a + n + 1) - a - 1;
	for(register int i = 1,p;i <= n;++ i){
		p = lowerbound(1 ,n ,a[i] * 2);
		if(a[p] == a[i]*2ll) add(i,p), add2(p,i);//建图
		if(a[i]%3!=0)continue;
		p = lowerbound(1,n,a[i]/3ll);
		if(a[p] == a[i]/3ll) add(i,p), add2(p,i);
	}
	for(int i = 1;i <= n; ++ i)
		if(!d[i]) q.push(i) , dp[i] = 1;
	while(!q.empty()){//拓扑排序
		register const int u = q.front(); q.pop();
		for(int i = head[u];i ;i = edge[i].next){
			dp[v] = max(dp[v], dp[u] + 1);
			d[v] --;
			if(!d[v]) q.push(v);
		}
		if(dp[u] >= ans){
			ans = dp[u];
			ansv = u;
		}
	}
	printf("%d\n" ,ans);
	DFS(ansv);
	for(int i = ans - 1;i >= 1;-- i)printf("%lld " ,a[num[i]]);
	printf("%lld " ,a[ansv]);
	return 0;
}
```
写完之后发现大佬都用 spfa 求最长路输出路径，好像要简单，~~苣蒻瑟瑟发抖~~

---

