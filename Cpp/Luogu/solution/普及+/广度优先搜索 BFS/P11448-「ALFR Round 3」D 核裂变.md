# 「ALFR Round 3」D 核裂变

## 题目背景

可爱的松鼠跑去学 PhO 啦。

## 题目描述

有 $n$ 个放射性原子要进行 $k$ 秒的裂变反应。如果在第 $t$ 秒开始时原子 $i$ 被 $b\ (b>0)$ 个中子轰击了，那它就会在第 $t$ 秒内释放 $a_i + b$ 单位能量，并向编号为 $x_{i,1},x_{i,2},\dots,x_{i,a_i}$ 的所有原子各释放 $1$ 个中子。这样，在第 $t+1$ 秒开始时分别击中的 $x_{i,1},x_{i,2},\dots,x_{i,a_i}$ 的中子数量都将**增加** $1$（**如果 $t=k$，即这是最后一秒，那么被轰击的原子不会释放中子**）。如果在这一秒开始时某个原子没被中子击中，则其不会释放能量与中子。

每一秒开始时，编号为 $v_1,v_2,\dots,v_m$ 的原子都会被 $1$ 个中子轰击。那么，从第 $1$ 秒开始，到第 $k$ 秒的终止时刻为止，每个原子会释放多少能量？

**答案对 $998244353$ 取模！**

## 说明/提示

### 样例 #1 解释：

- 第一秒，原子 $1$ 被 $1$ 个中子轰击，释放 $1$ 中子到原子 $2$，释放 $2$ 能量。
- 第二秒，原子 $1$ 被 $1$ 个中子轰击，释放 $1$ 中子到原子 $2$，释放 $2$ 能量。同时原子 $2$ 被 $1$ 个中子轰击，释放 $1$ 个中子到原子 $3$，释放 $2$ 能量。
- 第三秒，原子 $1$ 被 $1$ 个中子轰击，释放 $2$ 能量。同时原子 $2$ 被 $1$ 个中子轰击，释放 $2$ 能量。同时原子 $3$ 被 $1$ 个中子轰击，释放 $2$ 能量。

所以原子 $1$ 共释放了 $6$ 能量，原子 $2$ 释放了 $4$ 能量，原子 $3$ 释放了 $2$ 能量。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $5$ | $m=n,v_i=i,a_i=1,x_{i,1}=1$ |
| $1$ | $10$ | $m=1,v_1=1,a_i=1,x_{i,1}=(i\bmod n)+1$ |
| $2$ | $20$ | $n,\sum a_i\le10^3$，$1\le k\le10^6$ |
| $3$ | $30$ | $1\le k\le10^6$ |
| $4$ | $35$ | - |

对于所有数据，$1\le m\le n\le 5\times10^5,1\le \sum a_i\le5\times10^5$，$1\le k\le10^{18}$，$0 \leq a_i \leq 5 \times 10^5$，且 $v_1,v_2,\dots,v_m$ 互不相同且是 $[1,n]$ 内的整数，$x_{i,1},x_{i,2},\dots,x_{i,a_i}$ 互不相同且是 $[1,n]$ 内的整数。

**本题输入量较大，请使用较快的 I/O 方式。**

## 样例 #1

### 输入

```
3 3 1
1
1 2
1 3
1 1```

### 输出

```
6 4 2
```

## 样例 #2

### 输入

```
3 1000000000000000000 1
1
1 2
1 3
1 1```

### 输出

```
151723985 433897441 433897439
```

# 题解

## 作者：Moya_Rao (赞：16)

可以想到建图，按照 $x$ 数组的释放情况来建一张图，其中 $u$ 指向 $v$ 的边表示每一秒，如果 $u$ 会释放能量，则会释放 $1$ 中子到 $v$ 身上。

可那种自动有中子打击的，怎么办呢？简单，用一个 $0$ 节点连接，就当 $0$ 节点是这个自动的嘛。

不过，每个放射性原子并不是一开始就启动的，如果它还没有启动，那么就不能释放能量，这怎么处理呢？很简单，跑一次洪水填充，把每个节点的启动时间弄出来，就能知道它是什么时候启动的了。至于 $0$ 节点，反正是从它开始跑，它的启动时间就可以被设置成 $0$ 嘛。

但是要特殊处理一个东西：如果 $k$ 过于小，使得某些原子并没有在 $k$ 秒内启动呢？这简单，我选择在一开始赋上一个初值，最后统计答案的时候判断一下即可。

现在就是想如何统计答案了，其实上很简单，可以把答案拆成两部分来算，一部分是题面中所说的 $a_i$，另一部分就是题面中所说的 $b$。

那个什么 $a_i$ 很好算，利用自己的启动时间算出自己会在这 $k$ 秒内活跃多久，拿这个时间乘上 $a_i$ 即可。

$b$ 就相对麻烦一些，它要找到所有连向它的边，依次加上。其实上可以反过来考虑，每遇到一个点 $i$，可以把 $i$ 连向的所有边的答案加到对应节点里去，把这 $n$ 个点遍历完，其实上就行了。

这两个玩意儿，说是说分开算，其实也不然，可以放在一个大的循环里，遍历 $i$ 从 $1$ 到 $n$，每个每个去算就行了。

$0$ 呢？$0$ 也连向了一些点，这些点是无法在刚刚所说的那个循环里计算到的，没什么，多加一个关于 $0$ 的小循环就可以了，看看 $0$ 连向了哪些边，一开始就给它加进去，没什么大碍。

这下，就可以在 $O(n+m)$ 左右的时间内完成，非常快速。不过，千万千万要记得，对 $998244353$ 取模！还有就是，最好写一下快读，否则可能会大大降低其效率！

这里给出一份参考代码，赛时敲的，能 AC，别怀疑。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
const long long mod = 998244353;
long long n,k,m,a[N],t[N],ans[N];
vector<int> g[N];
queue<int> q;
long long read(){
    long long su=0,pp=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')pp=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        su=su*10+ch-'0';
        ch=getchar();
    }
    return su*pp;
}
int main(){
    n=read(),k=read(),m=read();
    for(int i=1;i<=m;i++)g[0].push_back(read());
    for(int i=1;i<=n;i++){
        a[i]=read(),t[i]=k+1;
        for(int j=1;j<=a[i];j++)g[i].push_back(read());
    }
    q.push(0);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(t[u]==k)break;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i];
            if(t[v]<=k)continue;
            t[v]=t[u]+1;q.push(v);
        }
    }
    for(int i=0;i<g[0].size();i++){
        int u=g[0][i];
        ans[u]+=k%mod;ans[u]%=mod;
    }
    for(int i=1;i<=n;i++){
        if(t[i]==k+1)continue;
        ans[i]+=(((k-t[i]+1)%mod)*a[i])%mod;ans[i]%=mod;
        for(int j=0;j<g[i].size();j++){
            int u=g[i][j];
            ans[u]+=(k-t[i])%mod;ans[u]%=mod;
        }
    }
    for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
    return 0;
}
```

如果本篇题解对你有所帮助，请留下一个小小的赞，谢谢！

---

## 作者：Infter (赞：6)

由于这 $m$ 个原子不停地被轰击，所以如果一个原子参与了反应，之后的所有时刻都会参与反应。

所以通过 BFS 预处理出每个点第一次参与反应的时间，记作 $dep$（代码中的是 $dep + 1$）。

对于每个点如果没有参与反应那能量就是 $0$。

否则他的能量就是其自身释放的能量（即它参与反应的时间 $\times a_i$）和其他原子授予的能量之和。

其他原子授予的能量之和就是所有会向他释放中子的原子的参与反应的时间减一（因为中子要跑 $1$ 时间才到），再加起来。

BFS 的时间复杂度为 $O(n+m)$，后续处理的时间复杂度为 $O(n+m)$，总时间复杂度为 $O(n+m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 5e5 + 5;
constexpr int MOD = 998244353;
constexpr int INF = 0x3f3f3f3f;

int n, m;
long long k;
vector<int> G[MAXN], H[MAXN];
int dep[MAXN];
bool vis[MAXN];

void bfs() {
    memset(dep, 0x3f, sizeof dep);
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            q.push(i);
            dep[i] = 0;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : G[u]) {
            if (dep[v] == INF) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++) {
        int v;
        cin >> v;
        vis[v] = true;
    }

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        for (int j = 1; j <= a; j++) {
            int t;
            cin >> t;
            G[i].push_back(t);
            H[t].push_back(i);
        }
    }

    bfs();

    for (int i = 1; i <= n; i++) {
        if (k - dep[i] <= 0) {
            cout << 0 << " ";
            continue;
        }
        long long ans = 0;
        if (vis[i])
            ans += k;
        ans += (k - dep[i]) * G[i].size() % MOD;
        ans %= MOD;
        for (int v : H[i]) {
            if (k - dep[v] <= 0)
                continue;
            ans += k - dep[v] - 1;
            ans %= MOD;
        }
        cout << ans << " ";
    }
    cout << endl;

    return 0;
}
```

---

## 作者：CaiZi (赞：5)

~~赛时找规律+暴力做法仅 TLE on Subtask #1，于是缝合了一下过了这题~~，赛后来写一下正解，感觉这题还是挺简单的。

由于每秒开始时这 $m$ 个原子都会被轰击，所以若一个原子某秒被轰击，之后每秒都会被轰击。先把轰击的传递关系建成图，然后用多源 BFS 求出每个点首次被轰击的时间为第 $s_i$ 秒，注意需要限制 $s_i\le k$。

如果某个点没有被 BFS 拓展到，则可以直接忽视。否则其释放的能量即为 $(k-s_i+1)\times a_i+\sum\limits_{j\to i}(k-s_j)$（$j\to i$ 指 $j$ 有直接连向 $i$ 的边）。后面没有 $+1$ 的原因是因为最后一秒时，原子被轰击不再产生中子。后面一半的式子只要建反图，就可以求了。

代码展示：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,k,m,a,b,s[500001];
vector<int>f[500001],g[500001];
queue<int>q;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n>>k>>m;
	for(int i=1;i<=m;i++){
		cin>>a;
		q.push(a);
		s[a]=1;
	}
	for(int i=1;i<=n;i++){
		cin>>a;
		for(int j=1;j<=a;j++){
			cin>>b;
			f[i].push_back(b);
			g[b].push_back(i);
		}
	}
	while(!q.empty()){
		a=q.front();
		q.pop();
		for(int i:f[a]){
			if(s[i]==0&&s[a]+1<=k){
				s[i]=s[a]+1;
				q.push(i);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(s[i]==0){
			cout<<"0 ";
		}
		else{
			a=(k%mod-s[i]+1)*f[i].size()%mod;//注意k要先取模，否则1e18*5e5会炸
			if(s[i]==1){
				a=(a+k)%mod;
			}
			for(int j:g[i]){
				if(s[j]!=0){
					a=(a+k-s[j])%mod;
				}
			}
			cout<<a<<' ';
		}
	}
	return 0;
}
```

---

## 作者：WZWZWZWY (赞：3)

设点 $0$ 每秒开始时都向所有 $v_i$ 输出一个中子。若无特殊说明，以下的“所有的点”不包括点 $0$。

建议画图便于理解。



------------


首先根据题目可以得出的性质有：

1. 一个中子撞到一个点后，那个点会向着所有连出的边发射一个中子。

2. 一个点一秒最多只会向每条边射出一个中子。并不是被多少个点撞到就射出多少中子！

3. 一个中子第 $i$ 秒从 $u$ 到 $v$ 后，$i$ 秒及之后都会有一个中子从 $u$ 到 $v$。

------------

### 子任务 $0$ 

子任务 $0$ 的图为：$1\sim n$ 所有点都有一条边连向点 $1$。点 $0$ 连向所有点。

点 $1$ 的答案即为：第 $1$ 秒开始，每秒释放 $2$ 点能量，共 $2\times k$ 点能量，加上 $(k-1)$ 秒乘以每秒的 $n$ 点能量；其他点的答案是每秒 $2$ 点能量乘以 $k$ 秒。

得到 $5$ 分。

------------

### 子任务 $1$ 

子任务 $1$ 的图为：$1\sim (n-1)$ 所有点都有一条边连向下一个点，第 $n$ 个点连向第一个点，形成一个环。点 $0$ 连向点 $1$。

第 $n$ 秒后，点 $1$ 将每秒都获得一个来自点 $n$ 的中子，这部分释放的总能量为 $(k-n)$，答案为 $1\times (k-n)+2\times k$；对于其他点，点 $i$ 释放的能量为 $2\times (k-i+1)$。

加上子任务 $0$ 共得 $15$ 分。

------------

### 全部分


>如果在第 $t$ 秒开始时原子 $i$ 被 $b\ (b>0)$ 个中子轰击了，那它就会在第 $t$ 秒内释放 $a_i+b$ 单位能量。


考虑一个点答案的构成，$a_i$ 即一个点的出度，这是固定的，$b$ 随着时间是单调不减的，同时前两个子任务启发我们：一个点 $v$ 的答案（分别考虑 $b$ 与 $a_i$）为：



$1 \times$（每个能到点 $v$ 的点 $u$ 的中子，到 $v$ 后剩余可走的步数）$+$ 出度 $\times$（到点 $v$ 的中子最大的剩余可走的步数）。


那么 BFS，同时记录每个中子的步数。最大剩余可走步数一定是第一个撞到它的中子的剩余可走步数。

还有要注意，如果剩余步数小于 $0$ 则停止。

```
#include <bits/stdc++.h>
#define int long long
#define PII pair <int, int>
using namespace std;

const int N = 5e5 + 5, mod = 998244353;

bool vis[N]; // 用来判断是否是第一个撞到 v 的中子 
int ans[N], n, k, a[N];
vector <int> e[N];

void BFS(int s) {
	queue <PII> q; // {点的编号，步数} 
	q.push({s, 0});
	while (q.size()) {
		int u = q.front().first, st = q.front().second; q.pop();
		if (st > k) return ;
		for (int v : e[u]) {
			if (vis[v]) (ans[v] += (k - st) % mod) %= mod;
			else {
				(ans[v] += (a[v] + 1) * ((k - st) % mod) % mod) %= mod; 
				q.push({v, st + 1});
				vis[v] = 1;
			}
		}
	}
}

signed main() {
    cin.tie(0); ios::sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 0; i <= n; i++) {
    	cin >> a[i];
    	for (int j = 1; j <= a[i]; j++) {
    		int x; cin >> x;
    		e[i].push_back(x);
		}
	}

	BFS(0);
	
	for (int i = 1; i <= n; i++) cout << ans[i] << " ";
	return 0;
}
```

还有什么不懂的可以发在评论区。

---

## 作者：MnZnOIer (赞：2)

## 前言
本文虽然比较长，但是详细讲解了两种方法，仔细读完应该会有收获。~~（不是就我一个写暴力的吗？）~~

## 解题思路
### 法一
考场思路：先考虑暴力，令 $v_i$ 表示当前这一秒第 $i$ 个原子产生的能量，$t_i$ 表示下一秒第 $i$ 个原子收到的轰击，然后枚举秒数，直接暴力更新 $t_i$ 和 $v_i$。显然，这样的暴力是一分没有的（~~在此谴责出题人不给暴力分~~），考虑优化，观察样例，发现当过去一定的时间后，$v_i$ 和 $t_i$ 是相同的，这启发了我，如果更新之后没有变化，就直接统计然后退出。

这样就拿到了 90 分的好成绩，发现在图为环时会跑满，每次更新跑满 $n$，更新到不变的情况也要跑 $n$，就会退化成 $n^2$，其他情况都是跑不满的。我们观察样例，然后直接找环的规律，就可以拿到满分。该做法被 hack 的概率较大，所以有了法二，这里贴一下代码。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5, mod = 998244353;
int n, k, m, v[N], t[N], a[N], to[N], c, pre[N], s[N], kk[N];
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n >> k >> m;
	for (int i = 1; i <= m; ++ i)
	{
		cin >> kk[i];
		t[kk[i]] = 1;
	}
	if (m == 1 && kk[1] == 1)//特殊性质。
	{
		cout << ((k % mod * 2) + (max (k - n, 0ll)) % mod) % mod << ' ';
		for (int i = 2; i <= n; ++ i)cout << ((max (0ll, k - i + 1)) % mod * 2) % mod << ' ';
		return 0;
	}
	for (int i = 1; i <= n; ++ i)
	{
		cin >> a[i];
		pre[i] = c + 1;
		for (int j = 0; j < a[i]; ++ j)
		{
			++ c;
			cin >> to[c];
		}
	}
	for (int i = 1; i <= n; ++ i)if (t[i])v[i] = a[i] + 1;
	pre[n + 1] = c + 1;
	for (int tc = 1; tc <= k; ++ tc)
	{
		int vv[N], tt[N];
		for (int i = 1; i <= n; ++ i)vv[i] = v[i], tt[i] = t[i], t[i] = 0;
		for (int i = 1; i <= n; ++ i)if (tt[i])//暴力更新。
		{
			v[i] = a[i] + tt[i];
			for (int j = pre[i]; j < pre[i + 1]; ++ j)++ t[to[j]];
		}
		for (int i = 1; i <= m; ++ i)++ t[kk[i]];
//		print ();
		int f = 1;
		for (int i = 1; i <= n; ++ i)f &= (v[i] == vv[i] && t[i] == tt[i]);
		if (f)
		{
			for (int i = 1; i <= n; ++ i)s[i] = (s[i] + ((k - tc + 1) % mod * v[i]) % mod) % mod;
			break;//没有变化直接退出。
		}
		for (int i = 1; i <= n; ++ i)s[i] = (s[i] + v[i]) % mod;
	}
	for (int i = 1; i <= n; ++ i)cout << s[i] << ' ';
	return 0;
}
```

### 法二
观察到每一个原子受到中子轰击之后就会保持产生能量的状态，所以跑一遍 bfs，统计每一个点最小深度，即最早产生能量的时间。

然后考虑统计贡献：对于一个点，受到中子轰击后，就可以产生 $a_i+p_{t,i}$ 的能量（$p_{t,i}$ 表示第 $i$ 个原子第 $t$ 秒收到的轰击次数）。但是我们并不需要求每一次的 $p_{t,i}$，考虑拆开 $\sum_{t=1}^kp_t$，可以从向它轰击的中子进行统计，所以就很简单了。

注意细节：一开始就有中子轰击的可以与 $0$ 连边，就不用记录一开始收到轰击的原子了。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5, mod = 998244353;
int n, k, m, h[N], c, t[N], a[N], s[N];
//t[i] 表示第 i 个原子产生能量的最早时间。
//s[i] 统计答案。
struct Edge{int v, nxt;}e[N << 1];
void add (int a, int b)
{
	e[++ c] = Edge{b, h[a]};
	h[a] = c;
}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n >> k >> m;
	memset (h, -1, sizeof (h));
	for (int i = 0, kk; i < m; ++ i)
	{
		cin >> kk;
		add (0, kk);//跟 0 连边。
	}
	for (int i = 1; i <= n; ++ i)
	{
		cin >> a[i];
		for (int j = 0, kk; j < a[i]; ++ j)
		{
			cin >> kk;
			add (i, kk);//正常建边。
		}
	}
	for (int i = 1; i <= n; ++ i)t[i] = k + 1;//初始化 t 数组。
	queue <int> q;
	while (! q.empty ())q.pop ();
	q.push (0);
	while (! q.empty ())//bfs。
	{
		int u = q.front ();
		q.pop ();
		if (t[u] == k)break;//当前时间攻击没有意义。
		for (int i = h[u]; i != -1; i = e[i].nxt)
		{
			int v = e[i].v;
			if (t[v] <= k)continue;//更新过了。
			t[v] = t[u] + 1;//统计最早收到中子轰击。
			q.push (v);
		}
	}
	for (int i = h[0]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		s[v] = (s[v] + k % mod) % mod;//直接被轰击。
	}
	for (int i = 1; i <= n; ++ i)
	{
		if (t[i] == k + 1)continue;
		s[i] = (s[i] + ((k - t[i] + 1) % mod * a[i]) % mod) % mod;//攻击产生的能量。
		for (int j = h[i]; j != -1; j = e[j].nxt)
		{
			int v = e[j].v;
			s[v] = (s[v] + (k - t[i]) % mod) % mod;//被攻击产生的能量。
		}
	}
	for (int i = 1; i <= n; ++ i)cout << s[i] << ' ';
	return 0;
}
```

## 后记
[法一通过记录](https://www.luogu.com.cn/record/195579186)，[法二通过记录](https://www.luogu.com.cn/record/195645248)，可以发现效率相差并不大（大雾）。

---

## 作者：Tomle (赞：2)

阅读理解。

建议先多读几遍题，避免歧义。

容易发现一个性质：如果一个点在第 $t$ 秒被轰击，那么也会在第 $t+1$ 秒被激活。

考虑先 bfs 一遍，求出每个点能否被激活，以及被激活的时间，记为 $T$。

对于每个点的答案，考虑拆贡献。对于一个点，若它不能在 $k$ 秒内被激活（$T_i>k$），则它不释放能量，即答案为 $0$。若它能被激活，则记它的编号为 $p$，第 $i$ 秒它被轰击了 $b_{p,i}$ 次，则这个点总的释放能量为：

$$
\begin{aligned}
\sum_{i=1}^k [b_{p,i}>0](a_p+b_{p,i})
&=\sum_{i=1}^k[b_{p,i}>0]a_p+[b_{p,i}>0]b_{p,i}
\\&=\sum_{i=1}^k[b_{p,i}>0]a_p+b_{p,i}
\\&=(k-T_p+1)a_p+\sum_{i=1}^k b_{p,i}
\end{aligned}
$$

对于 $b_{p,i}$ 的求和，也可以考虑拆贡献。记当前点为 $p$，$F_{i,j}$ 表示第 $i$ 秒编号为 $j$ 的点有没有被轰击，集合 $S_p$ 满足 $\forall i\in S_p,\exists 1\le j\le a_i,x_{i,j}=p$，则：

$$
\begin{aligned}
\sum_{i=1}^k b_{p,i}&=\sum_{i=1}^k([p\in v]+\sum_{j\in S_p}F_{i-1,j})
\\&=[p\in v]k+\sum_{j\in S_p}\sum_{i=1}^{k-1}F_{i,j}
\\&=[p\in v]k+\sum_{i\in S_p}[T_i\le k](k-T_i)
\end{aligned}
$$

综上，一个点释放的能量为：

$$
(k-T_p+1)a_p+[p\in v]k+\sum_{i\in S_p}[T_i\le k](k-T_i)
$$

枚举每个 $p$ 的 $S_p$ 是 $\mathcal{O}(\sum_i a_i)$ 的。

对于代码，注意 $k\le 10^{18}$ 的取模问题。

code
```cpp
#include <bits/stdc++.h>
#define tm goodname
#define int long long
using namespace std;

const int mod = 998244353;

int n, k, m, v[500005], tm[500005], a[500005], x;
vector <int> e[500005], f[500005];

void read(int &a, int ch = 0) {
   while (!isdigit(ch = getchar()));
   for (a = 0; isdigit(ch); ch = getchar()) a = (a << 3) + (a << 1) + (ch ^ 48);
}
void write(int x) {
   if (x > 9) write(x / 10);
   putchar(x % 10 ^ 48);
}
void bfs() {
   queue <int> q;
   for (int i = 1; i <= m; i++) tm[v[i]] = 1, q.push(v[i]);
   while (q.size()) {
      int u = q.front(); q.pop();
      for (auto v : e[u]) {
         if (tm[v] == LLONG_MAX) tm[v] = tm[u] + 1, q.push(v);
      }
   }
}
signed main() {
   read(n), read(k), read(m);
   for (int i = 1; i <= n; i++) tm[i] = LLONG_MAX;
   for (int i = 1; i <= m; i++) read(v[i]);
   for (int i = 1; i <= n; i++) {
      read(a[i]);
      for (int j = 1; j <= a[i]; j++) {
         read(x);
         e[i].push_back(x);
         f[x].push_back(i);
      }
   }
   bfs();
   for (int i = 1; i <= n; i++) {
      if (tm[i] > k) { write(0), putchar(32); continue; }
      int ans = (k % mod - tm[i] + 1 + mod) * a[i] % mod;
      if (tm[i] == 1) ans = (ans + k) % mod;
      // tm[i] = 1 说明 i in v
      for (auto v : f[i]) if (tm[v] < k) ans = (ans + k % mod - tm[v] + mod) % mod;
      write(ans), putchar(32);
   }
}
```

---

## 作者：hanchengyi (赞：2)

## 思路

观察到一个原子发射中子击中另一个原子可以转化为图论模型，对于这样的碰撞关系建有向边，然后从图上每秒被外部中子击中的原子开始 BFS 一遍，过程中可以顺带记录每个点在第几秒时撞击它的中子数量增加了 $1$。由于遍历深度递增，每一个点这样记录的序列一定递增。如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/js5fg96c.png)

其中 $2$ 号点在第 $2$ 秒开始同时被 $1$ 号点和 $4$ 号点发射的中子击中。$4$ 号点在第 $1$ 秒开始被外部击中，第 $2$ 秒被 $1$ 号点，第 $4$ 秒被 $3$ 号点击中。

这样，我们通过每个点的这个序列，可以算出它的总能量。例如 $4$ 号点，当 $k \ge 4$ 时，总能量就是 $(2 - 1) \times (1 + 1)+ (4 - 2) \times (2 + 1) + (k - 4 + 1) \times (3 + 1)$。当 $k < 4$ 时类推，找到 $k$ 在序列中应处的位置，后面的不要就行了。注意每次中子数要加上 $a_i$ 的值，总能量最后是包含第 $k$ 秒的。

复杂度 $O(n + m)$。

## 代码


```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define vi vector<int>
#define mii map<int, int>
#define pii pair<int, int>
#define pi priority_queue<int>
#define pib priority_queue<int, vector<int>, greater<int> >
#define ll long long
#define db double
#define ldb long double
#define ull unsigned long long
#define lowbit(x) (x) & (-x)
#define endl '\n'
#define int long long

using namespace std;

const int N = 2e6 + 7;
int p = 998244353;
int n, k, m;
int v[N];
int a[N];

int head[N], ver[N], nxt[N], tot;
void add(int x, int y) {
	ver[++ tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}

int f[N];
struct node{
	int val, dp;
};
queue<node> q;

vector<int> h[N];
bool vis[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> k >> m;
	
	for(int i = 1; i <= m; i ++) {
		cin >> v[i];
		q.push(node{v[i], 1});
		vis[v[i]] = 1;
		h[v[i]].emplace_back(1);
	}
	
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		for(int j = 1, x; j <= a[i]; j ++) {
			cin >> x;
			add(i, x);
		}
	}
	
	while(!q.empty()) {
		node x = q.front();
		q.pop();
		int dep = x.dp;
		
		for(int i = head[x.val], y; i; i = nxt[i]) {
			y = ver[i];
			h[y].emplace_back(dep + 1);
			if(!vis[y]) {
				vis[y] = 1;
				q.push(node{y, dep + 1});
			}
		}
	}
	
	for(int i = 1; i <= n; i ++) {
		int sz = h[i].size();
		
		if(sz == 0) {
			if(vis[sz]) cout << k % p << ' ';
			else cout << 0 << ' ';
			continue;
		}
		
		int ad = 1, sum = 0;
		for(int j = 1; j < sz; j ++) {
			if(k < h[i][j]) {
				sum += (k - h[i][j - 1] + 1) % p * (ad + a[i]) % p;
				sum %= p;
				break;
			}
			sum += (h[i][j] - h[i][j - 1]) % p * (ad + a[i]) % p;
			sum %= p;
			ad ++;
		}
		
		if(k >= h[i][sz - 1]){
			sum += (k - h[i][sz - 1] + 1) % p * (ad + a[i]) % p;
			sum %= p;
		}
		cout << sum << ' ';
	}
	return 0;
}
/*
  4 3 2
  1 4
  2 2 4
  1 3
  1 4
  1 2
 */
```

---

## 作者：light_searcher (赞：2)

赛时没多久就会思路了，结果代码写挂了，赛后看题解发现想的是正解。ε=(´ο｀*))) 唉。

容易把原问题转化为图论问题，好吧也不叫转化，这明摆着的。

首先，由于每一秒开始时，编号为 $v_1,v_2,\dots,v_m$ 的原子都会被 $1$ 个中子轰击，所以每一个点在一个时刻以后的每一秒都会被中子轰击，我们记这个时刻为 $low_i$，不难发现 $low$ 可以通过在原图上 bfs 一遍求得。

然后考虑如何求答案。

一秒内释放的能量为 $a_i+b$，可以分别对 $a_i$ 和 $b$ 算贡献，然后由于 $a_i$ 是个常量，所以贡献非常好算，直接就是 $(k-low_i)\times a_i$。然后对于后半部分，可以建反图，看有多少点可以在 $k$ 秒之前向它释放中子，每一个符合要求的点的贡献是 $k-low_v-1$。特别注意，如果 $i \in v$，答案还要加上 $k$，因为每秒都会被一个中子轰击。

然后就做完了，复杂度 $\mathcal O(n+m)$。

Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=998244353;
int n,k,m,a[N],low[N],v[N];
vector<int>edge[N],edge_back[N];
void bfs(){
	queue<int>q;
	memset(low,0x3f,sizeof(low));
	for(int i=1;i<=m;i++){
		q.push(a[i]);
		low[a[i]]=0;
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v:edge[u]){
			if(low[v]>low[u]+1){
				low[v]=low[u]+1;
				q.push(v);
			}
		}
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&k,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld",&a[i]);
		v[a[i]]=1;
	}
	for(int i=1,cnt;i<=n;i++){
		scanf("%lld",&cnt);
		for(int j=1,v;j<=cnt;j++){
			scanf("%lld",&v);
			edge[i].push_back(v);
			edge_back[v].push_back(i);
		}
	}
	bfs();
	for(int i=1;i<=n;i++){
		if(k<=low[i]){
			printf("0 ");
			continue;
		}
		int ans=((k-low[i])%mod*edge[i].size())%mod;
		if(v[i]) ans=(ans+k%mod)%mod;
		for(int v:edge_back[i])
			if(k>low[v]) ans=(ans+k-low[v]-1)%mod;
		printf("%lld ",ans);
	}
	return 0;
}

---

## 作者：dci66666 (赞：1)

这个题，比赛时为难了很久。

每一秒开始时，编号为 $v_1,v_2,\dots,v_m$ 的原子都会被 $1$ 个中子轰击。那么，从第 $1$ 秒开始，到第 $k$ 秒的终止时刻为止，每个原子会释放多少能量？（摘自原题）

这一段话是原题的关键。同时注意到起始点 $v_i$ 每一秒都会收到一个电子的转移，所以说只要这个路径一旦被打通（比如在 $t$ 秒被打通），就会从这之后就会一直有电子输送过来。

这个的意义是什么？对于这个点来说可以看做这个点被**激活**，在此之后会不断每秒产生至少 $a_i$ 的贡献。对于这条边来说，这条边被**激活**，这证明这条边会源源不断地产生 $1$ 的贡献。

我们知道一个点的贡献和就是 $\sum_{t = 1}^{k} a_t+b_t$，那么我们可以将答案贡献拆成 $\sum_{t = 1}^{k} a_t+\sum_{t = 1}^{k} b_t$ 的形式。

对于第一部分来说，一旦这个点被激活，那么不论多少电子撞击都只产生 $a_i$ 的贡献。第二部分，也就是有多少个电子撞击，考虑有哪些情况会使电子撞击到这个点上。无非是这个点的**入度**，这个指向这条点的边最多产生一的贡献。前面也讲过，一旦一条边被激活，那么由于每一秒都会有电子从原点出发，**沿着上一秒的路径走**，所以上一秒这条边上产生贡献，下一秒也必然产生贡献。因此，但所有指向这点的边一旦被激活，就会源源不断对这个点产生 $1$ 的贡献。

因此，我们只需要考虑每个点，边何时被激活就行了。

所以，我们可以用最短路，用数组记录需要多少时间到达这个点或边就行了。最后把答案加在对应点上就行了。

复杂度 $O(m\log n)$ 刚好过掉此题（每条边只会访问一次，稀疏图要跑什么不用我说了吧）。

后续：我考场上认为广搜也行，但是过不了，最后只能写最短路了，但是理论可行？

## 代码
建议快读快写。
```cpp
#include<bits/stdc++.h>
using namespace std;//dijkstra
const int N=2e6+50,mod=998244353;
#define ll __int128
#define int __int128
ll dis[(N<<1)],a[N];
int n,m,v[N],tot,ver[N],Next[N],head[N],vis[N],fr[N];
ll val[N],k;
struct node{
	int id,t;
	bool operator<(const node &x)const{
		return t>x.t;
	}
};
priority_queue<node>q;
void add(int x,int y){
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
	fr[tot] = x;
}
inline ll read(){
	ll x=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c<='9'&&c>='0'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x;
}
void write(ll x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
signed main(){
    n=read(),k=read(),m=read();
    //k%=mod;
    
    for(int i=1;i<=m;i++){
    	v[i]=read();
    	add(n+1,v[i]);
	}
	int st = tot+1;
	for(int i=1;i<=n;i++){
		a[i]=read();
		for(int j=1;j<=a[i];j++){
			int q=read();
			add(i,q);
		}
	}
	q.push({n+1,0});
	memset(dis,0x3f,sizeof(dis));dis[n+1]=0;
	while(q.size()){
		int x=q.top().id;q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(dis[y]>dis[x]+1){
				dis[y]=dis[x]+1;
				q.push({y,dis[y]});
			}
		}
	}
	for(int i=st;i<=tot;i++){
		dis[i+n+3]=dis[fr[i]]+1;
	}
	for(int i=1;i<=n;i++){
		//write(las[i]);
		//putchar(' ');
		ll tmp = max((ll)0,k-dis[i]+1)%mod;
		val[i] += tmp*a[i]%mod;
		val[i]%=mod;
	}
	for(int i=st;i<=tot;i++){
		//write(las[i+n]);
		//putchar(' ');
		int tmp=max((ll)0,k-dis[i+n+3]+1)%mod;
		val[ver[i]]+=tmp;
		val[ver[i]]%=mod;
	}
	for(int i=1;i<=m;i++){
		val[v[i]]=(val[v[i]]+k%mod)%mod;
	}
	for(int i=1;i<=n;i++){
		write((val[i]%mod+mod)%mod);
		putchar(' ');
	}
}
```

---

## 作者：xuyifei0302 (赞：1)

我们可以发现，只要一个原子在某一秒被触发，那么后面都会一直被触发。因为我们只在 $m$ 个原子上投放中子，所以可以先把不可能被触发的原子从中删去，并删去它与其它原子相连的边。因为一个原子只要被触发，不管被多少中子激发，都只会发送恒定的一个中子。所以在一定时间后每秒释放的能量是恒定的。所以我们可以用一个数组记录这个原子每秒释放的能量，在它被访问到的时候，也就是每秒释放的能量变化的时候统计这个原子从上一次统计到现在变化之前，释放的总能量。在搜索完后，对每个原子加上现在到未来第 $k$ 秒所释放的能量。若在第 $k$ 秒时，还没有到达恒定值，即还没有搜索完，就直接停止搜索，然后输出答案即可。

接下来是代码环节：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 998244353;
int n, k, m, a[500005], w[500005], num[500005], cnt, ans[500005], ad[500005], la[500005];
vector<pair<int, int>> v[500005];
bool mark[500005], flag[500005];
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k >> m;
	for (int i = 1; i <= m; i ++) {
		cin >> w[i];
		mark[w[i]] = true;
	}
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
		for (int j = 1; j <= a[i]; j ++) {
			int x;
			cin >> x;
			v[i].push_back({x, ++cnt});
			num[x] ++;
		}
	}
	queue<int> q;
	for (int i = 1; i <= n; i ++) {
		if (num[i] == 0 && !mark[i]) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto i : v[u]) {
			num[i.first] --;
			if (num[i.first] == 0 && !mark[i.first]) {
				q.push(i.first);
			}
			flag[i.second] = true;
		}
	}
	queue<pair<int, int>> qq;
	for (int i = 1; i <= m; i ++) {
		qq.push({w[i], 1});
	}
	while (!qq.empty()) {
		int u = qq.front().first, tim = qq.front().second;
		if (tim > k) {
			break;
		}
		if (ad[u] == 0) {
			ad[u] = a[u];
		} else {
			ans[u] += (tim - la[u]) * ad[u] % MOD;
		}
		ad[u] ++;
		la[u] = tim;
		qq.pop();
		for (auto i : v[u]) {
			if (!flag[i.second]) {
				flag[i.second] = true;
				qq.push({i.first, tim + 1});
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		ans[i] += (k - la[i] + 1) % MOD * ad[i] % MOD;
		cout << ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：linjunye (赞：1)

### 暴力思路

考虑简单的暴力怎么写，思路如下：

第一层枚举 $k$。然后我们定义 $a_i$，表示现在这个时刻第 $i$ 颗原子被 $a_i$ 颗中子撞击。那么，在每一秒，$a_{v_1},a_{v_2},\cdots,a_{v_m}$ 均加一。此时，记录贡献。然后开一个辅助数组，表示下一秒的状态。等辅助数组的数都计算好后，在转移到 $a$ 数组上。

时间复杂度 $\Theta(nk)$，可以拿到第 $3$ 档分数，结合前面两档的特判便可以拿到 35 分。

### 正解

好像没有进展了？先别急，此时可以手玩几组大一点的数组，只要看中子的传递过程，不要计算答案。

此时可以发现，当一个原子开始传递中子后，之后的每一秒都不会间断。

同理，当一个原子接收到来自另一个原子的中子后，之后的每一秒都会接收到它传递的中子。

既然如此，我们只要知道这个原子开始接收的时间 $t_i$，便能计算贡献了？！

好像没错，那么就可以用 BFS 求解。

具体操作为：

先把 $v$ 数组中的所有原子加入队列，$ans_{v_i}\leftarrow k\times(a_{v_i}+1)$

开始广搜，假设搜到一个 $v$。首先 $t_v=t_u+1$，然后算贡献。此时贡献会有两种情况，我们分别讨论：

- $v$ 没有搜过：会额外多一个 $a_v$，所以为 $ans_v\leftarrow (k-t_v+1)\times(a_v+1)$，然后将 $v$ 进队列。
- $v$ 搜过了：那么自从 $t_u$ 之后，$v$ 又会多一个贡献，所以为 $ans_v\leftarrow ans_v+(k-t_u)$。

因为每个原子只会进队列 $1$ 次，所以时间复杂度为 $\Theta(\sum a_i)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=500010;
struct Edge{
	int v,next;
}e[N];
int tot,head[N];
void add(int u,int v){
	tot++;
	e[tot].v=v;
	e[tot].next=head[u];
	head[u]=tot;
	return;
}
int n,m,k;
int v[N];
int t[N];
queue<int>q;
bool vis[N];
int ans[N];
int a[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>m;
	for(int i=1;i<=m;i++){
		cin>>v[i];
		q.push(v[i]);
	}
	for(int u=1;u<=n;u++){
		cin>>a[u];
		for(int j=1;j<=a[u];j++){
			int v;
			cin>>v;
			add(u,v);
		}
	}
	for(int i=1;i<=m;i++){
		ans[v[i]]=(ans[v[i]]+((a[v[i]]+1)%mod)*(k%mod)%mod)%mod;
		t[v[i]]=1;
		vis[v[i]]=1;
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		if(t[u]==k)break;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].v;
			if(!vis[v]){//第一种情况
				t[v]=t[u]+1;
				ans[v]=(ans[v]+(a[v]+1)%mod*((k-t[v]+1)%mod)%mod)%mod;
				vis[v]=1;
				q.push(v);
			}
			else ans[v]=(ans[v]+(k-t[u])%mod)%mod;//第二种情况
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P11448 题解

## 思路

首先有一点可以很显然看出，一个原子第一次得到中子轰击的时刻为 $g$，则 $g$ 到 $k$ 即从 $g$ 到反应结束的每一秒它都会接收到一个中子。

一个原子在同时得到多个中子的轰击时，也只会释放一个中子，那么如果一个原子 $u$ 向另外一个原子 $v$ 放出中子的时刻不是 $v$ 第一次接收到中子的时刻，那么这个中子就不会再传递下去了。

因此，跑一遍最短路，求出每一个原子第一次被中子轰击的时刻。由于有多个起点，可以创建一个虚拟源点，向 $v$ 数组每个点连一条边，将虚拟源点作为图的出发点即可。

记点 $u$ 的最短路为 $dis_u$，若干个点 $u$ 直接指向点 $v$，则有 $ans_v = \sum \max(k-dis_u,0)$。

对于点 $u$，每一次释放中子，还会产生 $a_u$ 的能量，则将以上的答案再加上 $\max(k-dis_u+1,0) \times a_u$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
typedef pair<int,int> pii;

const int N=500005;
const int M=1000005;
const int mod=998244353;
const int inf=1e18;

int n,k,m;
int dis[N],a[N];
int e[M],ne[M],h[N],tot;
bool flag[N];
priority_queue<pii,vector<pii>,greater<pii>> q;
int ans[N];

void add(int a,int b) {
    e[tot]=b,ne[tot]=h[a],h[a]=tot++;
}

void dijkstra() {
    _rep(i,0,N-1) dis[i]=inf;
    q.emplace(pii{dis[0]=0,0});
    while (!q.empty()) {
        auto tp=q.top(); q.pop();
        int u=tp.second;
        if (flag[u]) continue;
        flag[u]=true;
        _graph(i,u) if (dis[e[i]]>dis[u]+1) q.emplace(pii{dis[e[i]]=dis[u]+1,e[i]});
    }
}

signed main() {
    memset(h,-1,sizeof(h));
    scanf("%lld %lld %lld",&n,&k,&m);
    _rep(i,1,m) {
        int v;
        scanf("%lld",&v);
        add(0,v);
    }
    _rep(i,1,n) {
        scanf("%lld",&a[i]);
        _rep(j,1,a[i]) {
            int x;
            scanf("%lld",&x);
            add(i,x);
        }
    }
    dijkstra();
    // _rep(u,0,n) printf("dis %lld is %lld\n",u,dis[u]);
    _rep(u,0,n) {
        _graph(i,u) {
            ans[e[i]]=(ans[e[i]]+max(k-dis[u],0LL))%mod;
            // printf("%lld : %lld %lld\n",e[i],max(k-dis[u],0LL),1);
        }
        ans[u]=(ans[u]+max(k-dis[u]+1,0LL)%mod*a[u])%mod;
    }
    _rep(i,1,n) printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：ChenZQ (赞：0)

首先，我们需要意识到一个事情，那就是某个原子产生的能量一定会从某一时刻开始保持不变，一直到时间为 $k$。

这启示我们可以找到这个时刻，并直接计算出相同的贡献，不需要枚举到 $k$。

那么，我们可以跑一个广搜，记录某个原子什么时候开始产生能量。

每秒产生的能量为 $a_i + b$，我们可以分开讨论。

首先 $a_i$，自然是从每个原子最早产生能量的时间开始一直产生 $a_i$ 的能量，答案自然是 $(k - t + 1) \times a_i$，其中 $t$ 表示最早开始产生能量的时间。

然后是 $b$，我们对于每个原子都可以只考虑一个原子所产生的能量贡献，假设从 $t$ 开始（因为原子被撞产生能量就会发射中子，所以这个 $t$ 和我们之前求的 $t$ 是一样的），原子 $v$ 会发射一个中子射向原子 $u$，那么 $v$ 最终会对 $u$ 产生的贡献是 $k - t$（$t$ 时刻是被撞击的时刻，所以发射的中子还没撞向原子，不需要加一）。

于是我们遍历每个原子，找出他会射向的几个原子并统计贡献，就能求出答案了。

注意取模。

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long inf = 998244353;
const int N = 1000010;
long long n,k,m;
long long v[N],t[N],a[N];
long long ans[N];
vector<int> g[N];
queue<int> q;
bool flag[N];
int main()
{
	scanf("%lld%lld%lld",&n,&k,&m);
	for(int i=1;i<=n;i++) t[i]=1e18+2;
	for(int i=1;i<=m;i++) scanf("%lld",&v[i]),q.push(v[i]),t[v[i]]=1,flag[v[i]]=1,ans[v[i]]+=k%inf;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		for(int j=1;j<=a[i];j++)
		{
			int x;scanf("%d",&x);
			g[i].push_back(x);
		}
	} 
	while(!q.empty())
	{
		int f=q.front();
		q.pop();
		int tt=g[f].size();
		for(int i=0;i<tt;i++)
		{
			if(!flag[g[f][i]]) 
			{
				q.push(g[f][i]);
				t[g[f][i]]=t[f]+1;
				flag[g[f][i]]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(t[i]>k) continue;
		ans[i]+=(k-t[i]+1)%inf*a[i]%inf;
		ans[i]%=inf;
		int j=g[i].size();
		for(int kk=0;kk<j;kk++)
		{
			ans[g[i][kk]]+=(k-t[i])%inf;ans[g[i][kk]]%=inf;
		}
	}
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
}
```

---

