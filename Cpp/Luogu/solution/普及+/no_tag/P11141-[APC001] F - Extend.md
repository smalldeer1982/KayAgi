# [APC001] F - Extend

## 题目背景

~~**本题输入输出量较大，请酌情使用较快的输入输出方式**~~。已扩大时限从 $1s\to 1.5s$。

## 题目描述

对于一棵有 $n$ 个节点，根为 $k$ 的树，最开始有且仅有一个“可扩展的”节点 $z$，我们有两种扩展形式：

- $\text{I}$ 类扩展：从一个“可扩展的”节点 $u$ 开始扩展，把 $u$ 的子树中所有节点和所有满足与 $u$ 距离 $\leq p$ 且是 $u$ 祖先的节点标记为“可扩展的”。
- $\text{II}$ 类扩展：从一个“可扩展的”节点 $u$ 开始扩展，把所有与 $u$ 深度相等的节点标记为“可扩展的”。

你需要将所有结点都标记为“可扩展的”，求最小进行扩展的次数。

## 说明/提示

样例 $1$ 解释：两次询问都可以先对 $2$ 节点进行 $\text{II}$ 类扩展，然后对 $3$ 进行 $\text{I}$ 类扩展。可以保证对于两次询问，这样操作都是最优的。

对于所有数据，$1\leq z,k,u,v\leq n\leq 10^5,1\leq t\leq 2\times 10^6,0\leq p\leq 10^{18}$。

## 样例 #1

### 输入

```
3 1
1 2
1 3
2
2 6
2 1```

### 输出

```
2
2```

## 样例 #2

### 输入

```
4 1
2 1
3 2
4 3
3
2 2
2 5
4 2```

### 输出

```
1
1
2```

## 样例 #3

### 输入

```
20 11
2 8
16 4
6 7
11 8
10 13
7 10
17 7
15 13
10 14
18 19
1 2
6 3
12 1
1 5
1 4
2 3
9 5
14 20
5 18
15
9 269
1 522
6 327
13 726
14 8
17 2
18 4
15 64
9 5
13 3
18 1
19 664
5 3
20 5
6 4```

### 输出

```
2
2
2
2
2
3
2
2
2
3
5
2
2
3
2```

# 题解

## 作者：ycy1124 (赞：2)

前言：论操作 $2$ 存在的意义。
### 题意
在一棵有 $n$ 个节点并且以 $k$ 为根的树上，进行 $t$ 次询问，每次给出一个初始可以被访问的节点 $z$ 和一个参数 $p$，求最少要几次操作可以使所有节点可以被直接访问。操作分为两种，首先选择一个当前可以被访问的节点 $x$，操作一可以让 $x$ 子树内的节点与距离 $x$ 节点小于等于 $p$ 的**祖先**可以被访问，操作二可以使所有与 $x$ 节点深度相同的节点可以被访问。
### 思考
首先观察两个操作的性质，不难发现只有操作一可以使能被访问的节点的深度减小，并且只和当前操作节点的**深度**与 $p$ 有关。此时我们不难想到，要想访问到根节点的**最小**操作步数一定是与操作二无关的，并且操作二全部放在操作一后面一定是**不劣**的。

此时我们得到了一个操作的大致顺序，首先一直执行一操作并每次选择深度最小的可访问点进行操作，到达根节点后在考虑是进行二操作还是一操作。此时既然我们已经可以访问根节点，那么只要在根节点进行一次一操作就一定可以覆盖全部节点，因此这种方案一定是比继续进行二操作更优的。

这时方案的最优操作数很好求，只需要提前预处理出每个节点的深度就行了。但此时我们发现过不了第三个样例。

考虑一种特殊的情况，当这棵树上面是一条链然后下面连着一堆乱起八糟的子树时，假如我们在执行操作一的时候在这条链上的一个节点进行过一次操作一，那么最后到达根节点后的那个操作一就可以舍掉。对于判断是否在那条链上的节点执行过操作一，我们可以记录那条链的最下面那个节点的深度为 $ma$，假如到达根节点前的那一步的操作节点的深度小于等于 $ma$，就说明可以舍掉根节点的操作一。
### 代码
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
vector<int>a[100005];
int h[100005];
bool bj[100005];
int ma;
inline void dfs(int p,int fa){
    h[p]=h[fa]+1;
    if(h[p]==1){
        bj[p]=1;
    }
    for(auto it:a[p]){
        if(it==fa){
            continue;
        }
        if(a[p].size()+(h[p]==1)==2&&bj[p]){
            bj[it]=1;
            ma=max(ma,h[p]+1);
        }
        dfs(it,p);
    }
}
inline int read(){
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        ch=getchar();
    }
    int x=0;
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
inline void out(int x){
    if(x>9){
        out(x/10);
    }
    putchar(x%10+'0');
}
inline void write(int x){
    out(x);
    putchar('\n');
}
signed main(){
    int n=read(),k=read();
    for(int i(1);i<n;i++){
        int u=read(),v=read();
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(k,0);
    int t=read();
    while(t){
        --t;
        int z=read();
        int p=read();
        if(z==k&&n==1){//特判初始节点在根节点的情况
            write(0);
            continue;
        }
        if(z==k&&n!=1){//特判初始节点在根节点的情况
            write(1);
            continue;
        }
        int ans,w;
        ans=w=ceil(1.00*(h[z]-1)/p);//到达根节点所需的操作一
        --w;//上一步
        if(h[z]-w*p>ma){//上一步是否在链上
            ans++;
        }
        write(ans);
    }
    return 0;
  }
```
[AC 记录。](https://www.luogu.com.cn/record/191283231)

---

## 作者：Redshift_Shine (赞：2)

这场比赛有够难绷的。我的代码依赖 $z\le n$，然后这题目就给我出 $z>n$ 的数据导致我没有赛时切掉。

好了，接下来进入正题。

首先，两个操作太复杂了，考虑简化的可能。

考虑使根节点变为“可操作的”的最小次数。

不难发现，若想使根节点尽快变为“可操作的”，我们必须使用操作 $\text{I}$，因为操作 $\text{II}$ 不会影响“可操作的”节点的最小深度。或者说，我们必须使用 $\text{I}$ 向上推进。

若将节点深度设为 $d_x$，$d_k=0$，使根节点 $k$ 变为“可操作的”的最小操作次数显然是 $\lceil\frac{d_z}{p}\rceil$。

然而，使根节点变为“可操作的”后还有一些事情要处理。比如说，若最后一次 $\text{I}$ 操作推进的子树没有覆盖除 $p$ 级祖先外的所有节点，那么还需要在根节点再次进行一次 $\text{I}$ 操作。

然后我们发现这是最优的，而 $\text{II}$ 操作没用。诈骗。

考虑如何实现。首先不难使用单次 dfs 计算所有节点的深度。而在一个节点上操作单次 $\text{I}$ 操作可以覆盖除祖先节点的整棵树的充要条件是深度**不大于**该节点的所有节点都是其祖先。这里，我们认为一个节点的祖先包括其自身。

不难发现满足上述条件的节点深度是一个下限为 $0$ 的区间。

直接使用模运算判断逼近根节点过程中最后一次 $\text{I}$ 操作的深度随后与阈值比较即可。

时间复杂度 $O(n+q)$。

```c++
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, k, dep[N], q, rst, ck[N];
using ll = long long;
ll z, p;
vector<int> road[N];
void dfs(int x, int f)
{
	dep[x] = dep[f] + 1;
	ck[dep[x]]++;
	for (auto &i : road[x])
	{
		if (i == f)
			continue;
		dfs(i, x);
	}
}
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1, x, y; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		road[x].emplace_back(y);
		road[y].emplace_back(x);
	}
	dep[0] = -1;
	dfs(k, 0);
	while (rst <= n and ck[rst] == 1)
		rst++;
	rst--;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++)
	{
		scanf("%lld%lld", &z, &p);
		if (n == 1)
		{
			puts("0");
			continue;
		}
		if (z == k)
		{
			printf("%d\n", 1);
			continue;
		}
		if (!p)
		{
			printf("%d\n", -1);
			continue;
		}
		printf("%lld\n", (dep[z] + p - 1) / p + ((dep[z] - 1) % p + 1 > rst));
	}
}
```

---

## 作者：ylch (赞：1)

~~经典的 F 比 E 简单。~~ 

看到题目显然发现 $\text{II}$ 类扩展肯定不如 $\text{I}$ 类扩展优。

假设当前结点为 $u$，有一个和它深度相同的兄弟结点记为 $v$，发现在若干 $\text{I}$ 类操作后 $u$ 一定会成为 $v$ 的父亲，此时只需要再来一个 $\text{I}$ 类操作就能把 $v$ 和 $v$ 的子树都变为“可扩展的”。所以显然没必要在之前先来一个 $\text{II}$ 类操作。

发现其实 $\text{II}$ 类扩展根本没用，因为只要利用 $\text{I}$ 类扩展跳到根节点，再 $\text{I}$ 类扩展一次就能覆盖整棵树。题目就是要求从 $z$ 开始，每次向上走 $p$ 步，走多少次能回到根结点。

发现只要预处理出每个结点的深度就能 $O(1)$ 算。

当然答案最后还要加一，因为跳到根节点后还应执行一次 $\text{I}$ 类扩展来把影响扩大到整棵树。

但良心的出题人在样例三中告诉我们一个特殊情况（如图）：当根结点的度为 $1$（只有一棵子树）且**倒数第二次跳跃在从根节点到首次分岔的这条链上**时可以不用加一，因为走到根结点前这棵子树上的所有点也一定已经被标记过了。

```text
    o
    |
    o
    |
    o
  / | \
 o  o  o
……………
```

因为用纯数学方法计算，所以还要特判一些奇奇怪怪的边界情况。

$O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 7;

int n, k, cnt, dep[maxn];
vector<int> T[maxn];

void dfs(int u, int fa){ // 统计深度
	dep[u] = dep[fa] + 1;
	for(int v : T[u]){
		if(v == fa) continue;
		dfs(v, u);
	}
}

void dfs2(int u, int fa){ // 统计（说过的特殊情况）从根节点到首次分岔的这条链的长度
	int child = 0, nxt = -1;
	for(int v : T[u]){
		if(v == fa) continue;
		child ++; nxt = v;
	}
	if(child > 1 || nxt == -1) return ; // 到分岔了 或 到叶子了，返回
	cnt ++;
	dfs2(nxt, u);
}

void solve()
{
	cin >> n >> k;
	for(int i = 1; i <= n - 1; i ++){
		int u, v; cin >> u >> v;
		T[u].push_back(v), T[v].push_back(u);
	}
	dep[0] = -1; // 根节点层为0，这样计算起来会方便一些
	dfs(k, 0);
	dfs2(k, 0);
	int T; cin >> T;
	while(T --){
		int z, p; cin >> z >> p;
		if(n == 1) cout << "0\n";
		else if(p == 0) cout << "-1\n";
		else if(z == k) cout << "1\n";
		else{
			int t = (dep[z] % p == 0? p : dep[z] % p); // 找倒数第二次时距离根结点的距离，注意特判整除
			if(t > cnt) cout << (dep[z] + p - 1) / p + 1 << '\n'; // ceil(dep[z]/p)+1
			else cout << (dep[z] + p - 1) / p << '\n'; // 否则能省一步
		}
	}
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：gcx12012 (赞：1)

#### 前言
赛时写的是正解，但是被错误的数据区分了，幽默。
#### Solution
看到 $t\le2\times 10^6$ 不难想到单 $\log$。

然后我们分析一下题目，手摸一下发现 $\text{II}$ 类操作一定是不优的，因为染色同一深度的节点对整棵树的影响很小。

再考虑 $\text{I}$ 类操作，我们发现当操作的这个点 $u=k$ 时其实就做完了，于是我们得到一个优秀的策略：不断地往上跳 $p$ 层直到整棵树的节点都被染色为止。

然后记得特判和注意细节就做完了，结合树上倍增可以做到 $O(n\log n)$。
#### Code

```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 100010
#define For(i,a,b) for(ll i=a;i<=b;i++)
#define Rof(i,a,b) for(ll i=a;i>=b;i--)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<ll,ll>

using namespace std;
bool st;
vector<int >e[N];
ll dep[N],f[N][20],sz[N];
ll n,rt;
bool ed;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void dfs(int u,int fa){
	sz[u]=1;
	dep[u]=dep[fa]+1;
	f[u][0]=fa;
	For(i,1,19) f[u][i]=f[f[u][i-1]][i-1];
	for(int v:e[u]){
		if(v==fa) continue;
		dfs(v,u);
		sz[u]+=sz[v];
	}
}

int main()
{
	//fprintf(stderr,"%d",(&ed-&st)/1024/1024);
	n=read(),rt=read();
	dep[0]=-1;
	For(i,1,n-1){
		int u=read(),v=read();
		e[u].pb(v);
		e[v].pb(u);
	}
	dfs(rt,0);
	int q=read();
	while(q--){
		ll x=read(),p=read();
		if(n==1){
			printf("0\n");
			continue;
		}
		if(p==0){
			if(x==rt) printf("1\n");
			else printf("-1\n");
			continue;
		}
		if(x==rt){
			printf("1\n");
			continue;
		}
		ll ans=(dep[x]-1)/p,now=ans*p;
		Rof(i,19,0){
			if(now-(1<<i)>=0){
				x=f[x][i];
				now-=(1<<i);
			}
		}
		if(sz[x]+dep[x]==n) printf("%lld\n",ans+1);
		else printf("%lld\n",ans+2);
	}
	return 0;
}
/*

*/
```

---

## 作者：ivyjiao (赞：1)

首先很容易发现 $\text{II}$ 类扩展一定不比 $\text{I}$ 类扩展更优，因为 $\text{I}$ 类扩展中会扩展所有当前节点的子树的节点，而 $\text{II}$ 类扩展只与深度有关，所以在进行完 $\text{II}$ 类扩展后你需要进行的 $\text{I}$ 类扩展次数并没有变，而你此时再进行 $\text{II}$ 类扩展也不优了。你也可以模拟一下，你一直进行 $\text{I}$ 类扩展，和你先进行一次 $\text{II}$ 类扩展再进行 $\text{I}$ 类扩展的结果比较，会发现那次 $\text{II}$ 类扩展其实是被浪费掉了。

那么考虑计算 $\text{I}$ 类扩展的次数，容易发现次数和节点 $z$ 的深度有关，设 $dep_z$ 为 $z$ 的深度，那么每次向上扩展 $p$ 个节点，扩展到根节点后还要再把所有的节点都扩展到所以还要扩展一次，那么很容易就能得到一个式子：

$$ans=\lceil\dfrac{dep_z}{p}\rceil+1$$

但是这个式子是不对的，如果最后一次向上扩展后所有节点均被扩展，那么无需 $+1$，实现方法见代码。

最后考虑几种边界情况：

1. $n=1$，此时答案为 $0$。
2. 在不满足 $1$ 的情况下，$z=k$，此时答案为 $1$。
3. 在不满足 $2$ 的情况下，$p=0$，此时无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,z,u,v,d[100001],ans,cnt;
bool iakioi;
long long p;
vector<int>G[100001];
void dfs(int rt,int fa,int dep){
    if(G[rt].size()-1==1&&!iakioi) cnt++;
    else iakioi=1;
    d[rt]=dep;
    for(int i=0;i<G[rt].size();i++){
        if(G[rt][i]==fa) continue;
        dfs(G[rt][i],rt,dep+1);
    }
}
int main(){
    cin>>n>>k;
    G[k].push_back(0);
    for(int i=1;i<=n-1;i++){
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(k,0,0);
    cin>>t;
    while(t--){
        cin>>z>>p;
        if(n==1) puts("0");
        else if(z==k) puts("1");
        else if(!p) puts("-1");
        else{
            int q=d[z]%p;
            if(!q) q=p;
            if(q<=cnt) cout<<(d[z]+p-1)/p<<endl;
            else cout<<(d[z]+p-1)/p+1<<endl;
        }
    }
}
```

---

## 作者：huyangmu (赞：1)

不难发现，操作 $2$ 其实是没有什么用的，因为它永远只会覆盖和点 $x$ 同一层的节点，不会覆盖到 $x$ 的祖先和 $x$ 子树内的节点，所以想要覆盖祖先和子树内的节点只能不断进行操作 $1$，但你会发现，在进行操作 $1$ 的时候总会跳到根节点，对根节点再进行一次操作 $1$ 就能覆盖所有节点了，所以如果使用操作 $2$ 只会增加操作次数，故只进行操作 $1$。

先预处理出所有节点的深度，我们把节点 $x$ 的深度记作 $dep_{x}$，对于每次询问的点 $z$，我们很容易会有一个初步的思路，就是直接输出 $\lceil \frac{dep_{z}}{p} \rceil$，但这样过不了样例，因为有可能还要对根节点进行一次操作，因为如果有一个节点同时拥有两个及以上的儿子，并且深度在根节点到上一次跳到的点之间，那么它的另外几棵子树不会被覆盖，所以需要对根节点再进行一次操作 $1$。

发现深度大于 $p$ 且有两个儿子的节点在之前的操作中肯定会被跳到，如果有多个深度在根节点和上一次跳到的点之间的节点，在根节点进行一次操作 $1$ 就可以全部覆盖，所以我们考虑记录深度最浅且有至少两个儿子的节点即可。

最后感谢 @[ycy1124](https://www.luogu.com/user/1199534) 给我调试代码。

蓝勾后的第一篇题解，希望能过。

### Code


```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e5 + 5;
int n, k, x, y, t, z, p, dep[N], maxn = -1, pos;
vector<int> G[N];
void dfs (int x, int fa){
	dep[x] = dep[fa] + 1;
	if (x == k && G[x].size() > 1){
		maxn = 0;
		pos = k;
	}
	if (x != k && G[x].size() > 2 && maxn == -1){
		maxn = dep[x];
		pos = x;
	}
	for (int i = 0; i < G[x].size(); ++i){
		int nxt = G[x][i];
		if (nxt == fa) continue;
		dfs(nxt, x);
	}
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i < n; ++i){
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dep[0] = -1;
	dfs(k, 0);
	if (maxn == -1){
		for (int i = 1; i <= n; ++i){
			if (i != k && G[i].size() == 1){
				maxn = dep[i];
				pos = i;
				break;
			}
		}
	}
	cin >> t;
	while (t --){
		cin >> z >> p;
		if (z == k && n == 1){
			cout << 0 << '\n';
			continue;
		}
		if (z == k && n > 1){
			cout << 1 << '\n';
			continue;
		}
		if (dep[z] % p == 0){
			if (maxn < p && maxn < dep[z]) cout << dep[z] / p + 1 << '\n';
			else cout << dep[z] / p << '\n';
		} 
		else{
			if (dep[z] - dep[z] / p * p > maxn) cout << dep[z] / p + 2 << '\n';
			else cout << dep[z] / p + 1 << '\n';
		} 
	}
	return 0;
}`

---

## 作者：zwxadz (赞：0)

这道题其实还比较好想的。

首先，我们观察两个操作。

* 第一种操作，能够将其子树和一定范围内的祖先节点覆盖，我将其称为向上跳。

* 第二种操作，能够将相同深度的节点覆盖。

我们发现，根节点的性质较为特殊，它一定没有与其深度相等的节点，并且，只需要它进行一次操作一，那么整棵树都可以被覆盖到。

所以我们必须要进行一定次数的操作一，使得根节点被覆盖。此时我们发现，操作二没用了，因为执行操作二不优于在根节点执行一次操作一。

~~于是我们就可以直接用深度除以 $p$ 向上取整再加一算答案了。~~

发现错了，注意到到达根节点后不一定需要再进行一次操作，此时可能所有节点已经被覆盖了。接下来再考虑什么情况才会这样。

假设我们跳到了节点 $u$，接下来我们需要再向上跳一次，于是 $u$ 的子树被覆盖。假设 $u$ 有一兄弟节点，那么兄弟节点是覆盖不到的，只能由其祖先覆盖。$u$ 的祖先有兄弟节点也是同理。也就是说，在跳的任意时刻，如果该点或该点的祖先有兄弟节点，那么在后续必须要经过此点的祖先或者那个有兄弟节点的祖先的祖先，否则必须要在根节点进行一次操作。

在跳的所有过程中，假设最后一次跳之前的点为 $u$，那么此前的所有经过的点和经过的点的祖先都被包含在 $u$ 的子树内（除去 $u$ 的祖先），那么我们只需判定 $u$ 和它的祖先是否有兄弟。

这个较好维护，我们在进行求深度的 DFS 时可以求出最深的满足条件（其本身和其祖先没有兄弟）的节点。

求答案时再判定最后一步之前的点深度是否小于等于它即可。

空间复杂度：$O(n)$，单词询问时间复杂度：$O(1)$。

记得特判查询的点本身是根节点以及只有一个点的情况。

 **Code**：
 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,T;
vector<int>g[100005];
int dep[100005];
int depmax;
int num;
void dfs(int u,int fa,bool t)
{
	if(t&&(g[u].size()-(u!=k))<=1)depmax=max(depmax,dep[u]);
	for(int v:g[u])
	{
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u,t&&(g[u].size()-(u!=k))<=1);
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}//建图
	num=g[k].size();
	depmax=-1;//表示与根之间只有一条链的最深的点（等价于前文所说的条件）
	//我的代码实际上求的深度要比实际少一（好求一些），所以后面才要加一，初始赋值为-1
	dfs(k,0,1);//搜索，求出深度和depmax
	cin>>T;
	while(T--)
	{
		int z;
		long long p;//记得在这里开long long
		cin>>z>>p;
		if(n<=1)
		{
			cout<<0<<"\n";//只有一个节点，特判，答案为0
		}
		else if(z!=k)
		{
			int stp=(dep[z]+p-1)/p;//向上跳到根节点需要的步数，向上取整
			int t=dep[z]-(stp-1)*p;//向上跳stp-1步时的位置
			cout<<stp+(t>depmax+1)<<"\n";//向上跳到根节点所需的步数+是否需要再进行一次I操作
		}
		else cout<<1<<"\n";//根节点，特判答案为1
	}
	return 0;
}
```

---

## 作者：時空 (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/P11141)

**这是一篇单次查询 $\mathcal{O(\log\ n)}$ 的题解**，因为笔者不会 $\mathcal{O(1)}$。

水绿，思路很好想，但是细节有点多。

$t \le 2 \times 10^6$，启发我们单 $\log$ 做。

注意到 $\text{II}$ 类扩展不优，因为 $\text{II}$ 类扩展只与深度有关，进行完 $\text{II}$ 类扩展后，再进行 $\text{I}$ 类扩展的次数不变。所以只考虑 $\text{I}$ 类扩展。

记 $depth_x$ 表示点 $x$ 的深度。特别地，$depth_k = 0$。

很容易可以想到从 $z$ 开始，不断往上跳 $p$ 层，直到整棵树被覆盖。这样的话答案是 $\displaystyle \frac{depth_z - 1}{p} + 1$ 的。

但是有一个问题。就是这样子可能覆盖不到整棵树。（这里请读者认真思考，这道题的关键就在此了）。

怎么解决这个问题呢？可以判断跳的过程中，所覆盖的子树大小是否为整棵树的大小。

找到最后跳的一个点 $q$，即满足 $(depth_z - depth_q) \bmod p = 0$，且最接近根节点 $k$ 的点。 那么 $q$ 的子树大小与 $q$ 到根节点 $k$ 的路径长度（其实就是 $depth_q$）之和就是跳的过程中所覆盖子树的大小。判断是否为整棵树的大小 $n$ 即可。

找 $q$ 的过程可以用倍增实现。 注意特判有点多。

```cpp
cin >> t;
	while (t -- )
	{
		ll z, p; cin >> z >> p;
		
		if (!n || (z == k && n == 1)) { cout << "0\n"; continue; }
		if (z == k) { cout << "1\n"; continue; }
		if (!p) { cout << "-1\n"; continue; }
		
		ll c = depth[z], t;
		t = (c - 1) / p;
		
		ll f = t * p; ++ t;
        // f 为 depth_q 
		
		while (f)
		{
            // 找 q
			for (ll i = 30; ~i; -- i )
			{
				if (f >= (1 << i) && jp[z][i])
				{
					f -= (1 << i);
					z = jp[z][i];
				}
				
			}
		}
        // 此时的 z 即为 q 点
		if (siz[z] + depth[z] == n) cout << t << '\n'; 
		else cout << (++ t) << '\n';
	}
```

---

## 作者：AKPC (赞：0)

容易发现，你可以从 $z$ 开始不断使用 $\text{I}$ 操作向上跳到根节点 $k$，跳的步数取决于 $z$ 的深度。如果跳的过程中没有覆盖全部节点，那么除了跳根的答案还需要对 $k$ 用一次 $\text{I}$ 操作覆盖全部节点。

不过注意以下三种情况：
- $n=1$ 答案为 $0$。
- $n\neq1,z=k$ 答案为 $1$。
- 当 $n\neq1,z\neq k$ 时，当且仅当 $p=0$ 才会无解。

---

