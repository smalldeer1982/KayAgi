# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# 题解

## 作者：ZYF_B (赞：36)

大家怎么都是$map$做$dp$啊/jk。

题目显然可以转化为求选几个$gcd$为$1$的数的最小代价。

我们可以注意到$10^9$范围内的数最多有$9$个质因数，考虑状压$dp$。

设$f[i][s]$表示第$i$个数必选，质因数集合为$s$的最小代价($s$中第$x$位表示有没有$l[i]$的第$x$小的质因数)。

转移：枚举要选的数$l[j]$，求出$l[j]$的状态$s_j$，$f[i][s\&s_j]=min(f[i][s\&s_j],f[i][s]+c[j])$

$ans=min(f[i][0])$

时间复杂度$O(n^22^9)$。~~这难道不比时间复杂度都算不出来的map做法好？~~

**code**

ps:实际上可以省去$f$数组的第一维。

```c++
#include<bits/stdc++.h>
#define ll long long
#define re register
#define INF 1061109567
using namespace std;

inline int read()
{
	int f=1,x=0;char s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-') f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=x*10+s-48;
		s=getchar();
	}
	return f*x;
}

int a[305],cost[305];
int g[305][10],cnt[305];
int f[1<<9];

int main()
{
	int n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) cost[i]=read();
	for(int i=1;i<=n;i++)
	{
		int x=a[i];
		for(int j=2;j*j<=x;j++)
			if(x%j==0)
			{
				g[i][++cnt[i]]=j;
				while(x%j==0) x/=j;
			}
		if(x>1) g[i][++cnt[i]]=x;
	}
	int ans=INF;
	for(int i=1;i<=n;i++)
	{
		memset(f,0x3f,sizeof(f));
		int M=1<<cnt[i];
		f[M-1]=cost[i];
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			int s=0;
			for(int k=1;k<=cnt[i];k++)
			{
				int flag=0;
				for(int x=1;x<=cnt[j];x++)
					if(g[i][k]==g[j][x])
					{
						flag=1;
						break;
					}
				if(flag) s|=(1<<(k-1));
			}
			for(int k=0;k<M;k++)
				f[k&s]=min(f[k&s],f[k]+cost[j]);
		} 
		ans=min(ans,f[0]);
	}
	if(ans==INF) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Kohakuwu (赞：20)

## 前言
dijkstra 是什么啊/jk/jk/jk

剪枝 是什么啊/jk/jk/jk

状压 是什么啊/jk/jk/jk

一个 map 能搞定的题 为什么要用这么多奇奇怪怪的东西啊
## 思路
考虑怎么样才能遍历所有的格子，其实很简单，能往某个方向走 $1$ 单位长度即可。

考虑怎么走 $1$ 单位长度，根据**裴蜀定理**可知，这需要我们选择的所有 $l_i$ 的最大公因数是 $1$。于是问题转化为了选择若干个数使得 $\gcd$ 是 $1$ 的最小代价。

不难发现这很像背包问题。我们可以列出一个类似的 dp 柿子：设 $\gcd$ 为 $x$ 的最小代价为 $f_x$，则 dp 柿子就是对于 $x=2,3,4,\cdots,l_i$，$f_{\gcd(x,l_i)}=\min(f_{\gcd(x,l_i)},f_x+c_i)$。这里转移的顺序并不影响结果，大家可以感性理解一下。

然而这样的复杂度是 $O(n\sum a_i)$ 的……

我们考虑一个简单的优化：即消去无用状态。

可是我们怎么知道一个状态是有用的还是无用的呢？既然我们不知道，就让 stl 帮我们解决吧，开个 map，每次把访问过的 $x$ 执行转移即可，这样就能轻松过题了。

这样的时间复杂度比较难证明，我们考虑 map 中的节点数量。不难发现 map 中的每一个节点**必然是几个数的 $\gcd$**。这些数的数量大概就是**所有数的因数集合的并集大小**即 $\sum d(x)$。虽然单个数可能有 $1000$ 个因数，然而 $300$ 个数加起来取并集之后这个值其实挺小的，时间复杂度上界是 $O(n\sum d(x))$，理论上也能过，当然实际上离这个上界也挺远的。
## 代码
```
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch && ch<='9') x=x*10+(ch^48),ch=getchar();
    return x*f;
}
map<int,int> mp;
int a[1003],b[1003];
signed main(){
	int n=read();
    for(int i=1; i<=n; i++) a[i]=read();
    for(int i=1; i<=n; i++) b[i]=read();
    for(int i=1; i<=n; i++) 
    {
        for(pair<int,int> x:mp)
        {
            int num=__gcd(a[i],x.first),val=x.second+b[i];
            if(mp[num]==0) mp[num]=val; else mp[num]=min(mp[num],val);
        }
        if(mp[a[i]]==0) mp[a[i]]=b[i];
        else mp[a[i]]=min(mp[a[i]],b[i]);
    }
    if(mp[1]==0) puts("-1");
    else printf("%d\n",mp[1]);
    return 0;
}
```

---

## 作者：fanfansann (赞：8)

**Problem**

给出 $n$ 张卡片，分别有 $l_i$ 和 $c_i$  。在一条无限长的纸带上，你可以选择花 $c_i$ 的钱来购买卡片 $i$，从此以后可以向左或向右跳 $l_i$ 个单位。问你至少花多少元钱才能够跳到纸带上全部位置。若不行，输出 $-1$。$1\le n\le 300,1\le l_i ,c_i\le 10^9$。

**Solution** **（思路较长，比较详细，建议看完）**

首先分析子问题，先考虑两个数的情况，因为纸带是无限长的，没有循环，我们发现，要想能够跳到每一个格子上，就必须使得我们选择的数通过数次加减得到的数的绝对值为 $1$，进而想到了裴蜀定理。

我们知道裴蜀定理的内容是：**设 $a,b$ 是不全为零的整数，则存在整数 $x,y$，使得 $ax+by =  \gcd(a,b)$。** 我们想要解这个二元一次方程得到答案 $1$，也就是使得$\gcd(a,b)=1$，我们可以推出：如果 $a$ 与 $b$ 互质，则一定存在两个整数 $x,y$ ，使得$ax+by=1$。

由此我们想到本题的解题思路：选择最便宜的两个或者多个**互质**的数（多个数互质是指$\gcd(\gcd(\gcd(a,b)c...)=1$）。考虑动态规划。但是我们发现数据的大小达到了$10^9$，动态规划的时间和空间复杂度都会很糟糕。所以考虑有没有其他的做法。

我们知道动态规划问题实际上就是 $\tt DAG$ 上的递推，动态规划对于状态空间的遍历构成了一张有向无环图 $\tt DAG$ ，遍历顺序就是该 $\tt DAG$ 的一个拓扑序。考虑用图论的做法解决这个问题。因为我们想要找到的是最小代价的两个互质的数，从 $0$ 开始出发，选取最小的代价，最后的终点是 $\gcd(a,b)=1$ 或者是  $\gcd(\gcd(\gcd(a,b)c...)=1$ ，我们发现有一点最短路的性质。我们发现多个数互质，实际上就是一步步的 $\gcd$ 最后推到 $1$，就类似我们最短路的一步一步的结点转移。最后考虑从 $0$ 出发会不会对我们求解 $\gcd$ 造成影响呢？由于我们知道 $\gcd(0,x)=x$ ，所以不会有任何的影响。

至此整体的思路已经非常清晰了：我们从 $0$ 号节点开始，每一步走到的结点编号为 $\gcd(x,y)$ ，其中 $x$ 为当前的结点编号，也就是当前已选择的数的总 $\gcd$，$y$ 为我们枚举到的下一个结点 ，也就是下一个待选的数的值 $l[i]$，与此同时更新代价，利用  $\tt dijkstra$ 算法求得最小的总代价。

最后如果能够到达结点 $1$，也就意味着我们能够找到若干个数使得他们的总$\gcd$ 为 $1$ ，输出 $\tt dist[1]$ 即可。反之说明无法得到，即无法遍历所有的格点。

最后的一点小细节：由于我们的最短路过程中，需要使用一个 $\tt vis$ 数组记录每一个结点是否已经被遍历过了，由于数据过大，开不下这么大的数组，但是数据的数量不大，所以我们可以手写一个 $\tt hash$ 或者使用 $\tt STL$ 里自带的 $\tt hash$ 表 `unordered_map` 快速地（$O(1)$）访问每一个元素。

时间复杂度 $O(n^2\log n)$
```cpp
const int N = 50007, M = 500007, INF = 0x3f3f3f3f;
typedef long long ll;
typedef pair<int, int> PII;
unordered_map<int, bool> vis;
unordered_map<int, ll> dist;

int n, m;
int head[N], ver[N], nex[N], edge[M], tot;
int a[N], l[N], c[N];

int gcd(int a, int b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}
//gcd(0,x) = x;
void dijkstra()
{
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push({0, 0});
    dist[0] = 0;

    while(q.size()) {
        int x = q.top().second;
        q.pop();
        if(x == 1) break;

        if(vis.find(x) != vis.end()) continue;
        vis[x] = true;
        for(int i = 1; i <= n; ++ i) {
            int y = __gcd(x, l[i]), z = c[i];
            if(dist.find(y) == dist.end()) dist[y] = INF;
            if(dist[y] > dist[x] + z) {
                dist[y] = dist[x] + z;
                q.push({dist[y], y});
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i)
        scanf("%d", &l[i]);

    for(int i = 1; i <= n; ++ i)
        scanf("%d", &c[i]);
    dijkstra();

    if(dist.find(1) == dist.end()) puts("-1");
    else printf("%lld\n", dist[1]);
    return 0;
}
```


---

## 作者：inexistent (赞：5)

详见我的[博客](https://www.cnblogs.com/qixingzhi/p/9305782.html)

思路分析：

   题意：给出n张卡片，分别有l[i]和c[i]。在一条无限长的纸带上，你可以选择花c[i]的钱来购买卡片i，从此以后可以向左或向右条l[i]个单位。购买其他卡片后，可以获得更多的跳跃单位。先要求至少花多少元钱才能够任意跳到纸带上任意一个位置。若不行，输出-1.

　　首先分析如果只有两个技能的情况。若这两个技能的跳跃长度有最大公约数\(x\)，且满足\(x > 1\)，则一定能跳到任意一个位置。比如\(x = 2\)，那么所有奇数的格子都是跳不到的。如果\(x = 3\)，那么所有非3的倍数都是跳不到的。因此我们可以得到结论，当且仅当\(x = 1\)时才能够跳到所有的地方。

　　联系到多种技能的情况，若所有技能的跳跃长度的最大公约数大于1，那么就像刚才那样一定有格子跳不到。因此要求所选技能的最大公约数必须为1。因此题目可以转化为从n个技能中选取几个，使得其最大公约数为1，并且要让花费尽量小。

　　这就可以联系到dp了。令f[i]表示选择一些数并且最大公约数为i时的最小花费。很明显答案就是f[1]。转移也很简单，先扫描1~n，在扫描所有可能的最大公约数j。求出j与l[i]的最小公约数tmp。利用f[j]就可以转移f[tmp]了。（用与不用f[i]）

　　然而第9个点RE了。

　　回想一下过程，由于\(l[i] <= 10^9\)，所以f数组很明显装不下了。可以n只有300,300个卡片能有多少个最大公约数啊。于是我们联想到了map，把f改成一个map就解决问题了。

代码注意点：

　　注意f数组的初始化，f[0]=0，不然就永远进不去循环了……

---

## 作者：xiezheyuan (赞：4)

## 简要题意

> 给出 $n$ 张卡片，分别有 $l_i$ 和 $c_i$。在一条无限长的纸带上，你可以选择花 $c_i$ 的钱来购买卡片 $i$，从此以后可以向左或向右跳 $l_i$ 个单位。问你至少花多少元钱才能够跳到纸带上全部位置。若不可能，输出 $-1$。
> $1 \leq n \leq 300,1 \leq l_i \leq 10^{9},1 \leq c_i \leq 10^{5}$

## 思路

首先，如果我们可以选出一些个卡片 $(l_i,c_i)$，使得全部的 $c_i$ 互质（我的意思是 $(c_i,(c_{i+1},(c_{i+2},\cdots))) = 1$）。因为裴蜀定理 $c_ix+c_jy=1$ 有解，所以一定可以从位置 $x$ 跳到 $x \pm 1$。

一开始，我的思路是能选择 $c = 1$ 就选择，否则选择两个不同的。Hack 数据：

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

答案应该是 $6$（选择前 $6$ 个）。

然后我们考虑 DP，设 $f_{i,j}$ 为选择前 $i$ 个，选择的数的 $\gcd$ 是 $j$ 的最小代价。显然，最后答案是 $f_{n,1}$。动态转移方程：

$$
f_{i,(j,l_i)} = \left\{
\begin{aligned}
& \min(f_{i,(j,l_i)},f_{i-1,j} + c_i) & (j \neq l_i) \\
& \min(f_{i-1,(j,l_i)},c_i) & (j = l_i)
\end{aligned}
\right.
$$

无法通过本题，考虑优化。发现这个动态转移方程很像三角形不等式 $\operatorname{dis}_{u}=\min(\operatorname{dis}_{u},\operatorname{dis}_{v}+W_{u,v})$，想到用最短路优化。

使用堆优化 Dijkstra 算法可以做到 $O(n^{3})$，可以通过本题。

## 代码

```cpp
```cpp
#include <bits/stdc++.h>
#define int long long
#define gcd __gcd
using namespace std;

unordered_map<int, int> dis;
unordered_set<int> vis;
priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
int n,l[305],c[305];

void dijkstra(){
	pq.push({0,0});
	dis[0]=0;
	while(!pq.empty()){
		int x = pq.top().second;
		pq.pop();
		if(x==1){
			break;
		}
		if(vis.find(x) != vis.end()){
			continue;
		}
		vis.insert(x);
		for(int j=1;j<=n;j++){
			int y = gcd(x,l[j]);
			if(dis.find(y) == dis.end()){
				dis[y] = INT_MAX;
			}
			if(dis[y]>dis[x]+c[j]){
				dis[y]=dis[x]+c[j];
				pq.push(make_pair(dis[y],y));
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i];
	}
	for(int j=1;j<=n;j++){
		cin>>c[j];
	}
	dijkstra();
	if(dis.find(1)==dis.end()){
		// Impossible
		cout<<-1;
	}
	else{
		cout<<dis[1];
	}
	return 0;
}
```

[AC Record](https://codeforces.com/contest/510/submission/174510117)
```

---

## 作者：dks0311 (赞：2)

### 题意
给出 $n$ 张卡片，分别有 $l_i$ 和 $c_i$。在一条无限长的纸带上，你可以选择花 $c_i$ 的钱来购买卡片 $i$，从此以后可以向左或向右跳 $l_i$ 个单位。问你至少花多少元钱才能够跳到纸带上全部位置。若不行，输出 $-1$。

### Solution
如果想要跳到纸带上全部位置，由于纸带无限长，那么就只有使买完卡片后可以经过某种组合的跳跳到当前位置 $+1$ 或 $-1$ 的位置，由裴蜀定理得，需要使买的所有卡片的 $l_i$ 的最大公约数为 $1$。将问题再转化一下，变成从 $0$ 开始，当走到 $u$ 时买一张卡片，相当于走到 $\gcd(u, l_i)$ 的位置。最后使走到 $1$ 的代价最小，走不到就输出 $-1$。这样的话可以直接跑堆优化 Dijkstra。中间有一个细节是记录走过的点和每个点代价的时候不可能开到 $10^9$，所以可以用 `unordered_map`，就能过。

### Code
```cpp
#include<bits/stdc++.h>
#define PII std::pair<int, int>
const int N = 305;
inline int read(){
	int s = 0, f = 0;
	char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
	while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
	return f ? ~s + 1 : s;
}
int n, l[N], c[N];
std::unordered_map<int, int> dist;
std::unordered_map<int, bool> vis;
std::priority_queue<PII, std::vector<PII>, std::greater<PII> > q;
int gcd(int x, int y){
	if(y == 0) return x;
	return gcd(y, x % y);
}
int dijkstra(){
	dist[0] = 0;
	q.push({0, 0});
	while(!q.empty()){
		PII tmp = q.top(); q.pop();
		int u = tmp.second;
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = 1; i <= n; ++ i){
			int v = gcd(u, l[i]);
			if(u == v || vis[v] == true) continue;
			if(dist.count(v) && dist[v] <= dist[u] + c[i]) continue;
			dist[v] = dist[u] + c[i];
			q.push({dist[v], v});
		}
	}
	return dist.count(1) ? dist[1] : -1;
}
int main(){
	n = read();
	for(int i = 1; i <= n; ++ i) l[i] = read();
	for(int i = 1; i <= n; ++ i) c[i] = read();
	printf("%d", dijkstra());
	return 0;
}
```
代码**仅供参考**

---

## 作者：Gaode_Sean (赞：2)

根据裴蜀定理，对于我们选择的纸片，如果他们的长度的最大公因数为 $1$，意味着我们可以跳到纸上的任何位置。

由此我们可以设 $f_i$ 表示选择其中的一些纸片使得它们长度的最大公因数为 $i$，所需要花费的最小代价。不难得到转移方程 $f_{\gcd(i,l_j)}=\min(f_{\gcd(i,l_j)},f_i+c_j)$。具体转移可以用 map 来实现，这里参考了前面几篇题解的做法。

时间复杂度 $O($能过$)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> mp;
const int N=301;
int n,l[N],c[N];
int gcd(int a,int b)
{
	if(!b) return a;
    return gcd(b,a%b);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&l[i]);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	for(int i=1;i<=n;i++)
	{
		for(pair<int,int> x:mp)
		{
			int nxt=gcd(l[i],x.first);
			if(!mp[nxt]) mp[nxt]=c[i]+x.second;
			else mp[nxt]=min(mp[nxt],c[i]+x.second);
		}
		if(!mp[l[i]]) mp[l[i]]=c[i];
		else mp[l[i]]=min(mp[l[i]],c[i]);
	}
	if(!mp[1]) mp[1]=-1;
	printf("%d",mp[1]);
	return 0;
}
```

---

## 作者：gyyyyx (赞：2)

题目意思很明显，就是要取若干个数，使得每个数的最大公因数为 $1$，求最小花费。

发现和背包很像，考虑用 $dp$ 来做。

设 $dp_{i,j}$ 表示处理前 $i$ 个数，最大公因数为 $j$ 的最小花费。

则有转移方程：

$$
dp_{i,\gcd(j,l_i)}\left\{
\begin{array}{lr}
\min(dp_{i-1,j},dp_{i-1,j}+c_i)\ \ \ \ &j\neq l_i\\
\min(dp_{i-1,j},c_i)&j=l_i\\
\end{array}
\right.
$$

但是，这样不仅会超时，还会爆空间。

怎么办？

一个很好的办法就是将无用的状态去掉。

因为最多只有 $300$ 个数，所以理论上没有出现的状态应该很多，可以用一个 map 来做充当数组（如果不会 map 可以看[这里](https://blog.csdn.net/weixin_41501074/article/details/114532738)）。

还有什么问题看代码就懂了：

```cpp
#include<bits/stdc++.h>
#define N 305
using namespace std;
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
inline int min(int a,int b){return !a?b:a<b?a:b;}
map <int,int> mp;
int n,l[N],c[N];
int main(){
    scanf("%d",&n);
    for(int i(1);i<=n;++i) scanf("%d",l+i);
    for(int i(1);i<=n;++i) scanf("%d",c+i);
    for(int i(1);i<=n;++i){
        for(map <int,int>::iterator it(mp.begin());it!=mp.end();++it){
            int g(gcd(it->first,l[i]));
            mp[g]=min(mp[g],it->second+c[i]);
        }
        mp[l[i]]=min(mp[l[i]],c[i]);
    }
    if(mp[1]) printf("%d\n",mp[1]);
    else puts("-1");
    return 0;
}
```

---

## 作者：_edge_ (赞：1)

来补充一下离散化的 DP。

考虑这道题目，如果两个 $l$ 的话就是经典的 $ax+by=1$。

然后可以尝试推广至多个，这个我也不太会证，反正就是多个 $\gcd$ 如果为 $1$ 即为可行。

然后问题就转化成了，给定一些数，每个数有权值，然后求他们的子集，使得价值小并且 $\gcd=1$，这个问题就把约数都搞出来，然后 dp，设 $f_{i,j}$ 表示前 $i$ 个数，目前的最大公约数为 $j$，转移用刷表即可。

这里发现 $j$ 非常大，可以考虑直接把约数除出来，然后扔到一个离散化数组。

最后 dp 的时候稍微注意一下即可。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define pb push_back
#define int long long 
using namespace std;
const int INF=305;
const int INFN=5e5+5;
int n,f[5][INFN],c[INF],l[INF];
vector <int> v;
int Get(int x) {return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
int gcd(int x,int y) {return !y?x:gcd(y,x%y);}
signed main()
{
	memset(f,63,sizeof f);
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>l[i];int xx=l[i];
		for (int j=1;j*j<=xx;j++) {
			if (xx%j==0) {
				v.pb(j);
				if (xx/j!=j) v.pb(xx/j);
			}
		}
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for (int i=1;i<=n;i++) cin>>c[i];
	int len=v.size();
	for (int i=1;i<=n;i++) {
		int u=i&1,vv=u^1;
		memset(f[u],63,sizeof f[u]);
		f[u][Get(l[i])]=c[i];
		for (int j=1;j<=len;j++) {
			int P=Get(gcd(v[j-1],l[i]));
			f[u][P]=min(f[u][P],f[vv][j]+c[i]);
			f[u][j]=min(f[u][j],f[vv][j]);
		}
	}
//	cout<<v[0]<<" \n";
	if (f[n&1][1]<1e18) 
		cout<<f[n&1][1]<<"\n";
	else cout<<"-1\n";
	return 0;
}
```


---

## 作者：hzoi_liuchang (赞：1)

### 分析
我们先只考虑购买了两个卡片的情况

我们设这两个卡片跳跃的距离分别为$a,b$

其中第一张卡片使用了$x$次，第二张卡片使用了$y$次

那么跳跃的距离$l=ax+by$

要使方程有解，则必有$l mod \gcd(a,b)=0$

要使$l$取到任意整数，则$\gcd(a,b)=1$

因此，原题就变成了在$n$个数中选取几个数，使得这些数的最大公因数为$1$

求所有方案中花费最小的方案

一种可行的做法是设$f[i]$表示选择一些数并且最大公约数为$i$时的最小花费

利用$map$进行转移

但是现在我们考虑怎么用暴搜过掉这个题

最初始的暴搜应该比较好定义

我们传四个参数，分别是当前已经选到了第几个数、当前已经选了几个数、当前选择的所有数的价值之和、当前所有数的最大公因数

这样的暴搜不加任何剪枝会$T$到飞起

因此我们考虑怎么去优化

**剪枝一、如果当前价值已经大于所选价值，那么就没有必要继续向下选**

**剪枝二、如果当前选择的数量大于9，那么就没有必要继续向下选**

因为如果有$10$个不同的质因子，此时数会很大，已经超过了$l[i]$的最大值

**剪枝三、提前将-1的情况预处理出来**

**剪枝四、如果当前枚举的$l[i]$是之前枚举的公因数的倍数，那么当前的$l[i]$一定不会使之后的公因数变小，选$l[i]$无意义**

有了上述四个剪枝，我们已经可以跑过$64$个点，但是在最后一个点$T$了

因此，我们再加最后一个信仰剪枝，即如果当前运行次数过多，直接输出当前最优解，同时杀死程序

### 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005,maxk=21;
int s[maxn],l[maxn],n;
int gcd(int aa,int bb){
	if(bb==0) return aa;
	return gcd(bb,aa%bb);
}
int ans=0x3f3f3f3f;
int tim=0;
void dfs(int now,int cnt,int tot,int gys){
	tim++;
	if(tim>2e7){
		if(ans==0x3f3f3f3f) printf("-1\n");
		else printf("%d\n",ans);
		exit(0);
	}
	if(gys==1) ans=min(ans,tot);
	if(tot>=ans || cnt>9 || now>n) return;
	for(int i=now;i<=n;i++){
		if(gys==0) dfs(i+1,cnt+1,tot+s[i],l[i]);
		else if(l[i]%gys!=0) dfs(i+1,cnt+1,tot+s[i],gcd(gys,l[i]));
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&l[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&s[i]);
	}
	int jud=l[1];
	for(int i=2;i<=n;i++){
		jud=gcd(jud,l[i]);
	}
	if(jud!=1){
		printf("-1\n");
		return 0;
	}
	dfs(1,0,0,0);
	if(ans!=0x3f3f3f3f)printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}

```

---

## 作者：AC自动机 (赞：0)

### 算法

背包问题 map

### 思路
开始的时候，可以先思考两个数的情况，那么这两个数可以通过加减得到1或-1，此时可以跳到所有的格子，对此性质再进行研究，可以联想到裴蜀定理，因此这两个数一定是互质的，因此可以转化为找两个数，使它们互质，且代价和最小。

而这道题中不一定选择两个，有可能是多个，且可能多个数互质的代价更小，此时，题意就变成了选择k种卡片，使这k种卡片的l的最大公因数为1，且使c的和最小。

然后，然后懵逼。

直接做dp，复杂度太大，一开始还只能想到2维的dp，并且肯定会TLE，空间都不够/(ㄒoㄒ)/~~

后来查了查题解，发现可以用map优化qwq

基本上是抄这篇的【捂脸】：[http://blog.csdn.net/winddreams/article/details/44042883](http://blog.csdn.net/winddreams/article/details/44042883)

但是看懂了就可以了╮(╯▽╰)╭


用map[i]表示当最大公因数为i时的最小代价，然后使用迭代器来枚举，首先要去重，是最基本的优化，当两个卡片的l相同时，当然使用c最小的卡片，这样可以减小枚举的复杂度，然后枚举每一个卡片，然后再枚举每一个最大公因数，当当前的卡片的值和当前最大公因数的最大公因数为x时，可以通过比较来更新map[x]的值，如果没有map[x]就新建一个map[x]。

最后的答案就是map[1],如果map[1]不存在，输出-1。否则，输出map[1]。

#### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<map>
#define rint register int
using namespace std;
map<int,int>m;
map<int,int>::iterator iter;   //定义迭代器 
int l[305],c[305];
int gcd(int a,int b){
	if(a==0)return b;
	else return gcd(b%a,a);
}
int main(){
	int n,temp,su;
	cin>>n;
	for(rint i=1;i<=n;i++)cin>>l[i];   
	for(rint i=1;i<=n;i++)cin>>c[i];
	for(rint i=1;i<=n;i++){   //枚举每张卡片 
		temp=m[l[i]];       //temp为最大公因数为l[i]时的最小代价 
		if(temp)m[l[i]]=min(temp,c[i]);     //如果存在temp，比较一下，保留最优解，减小枚举复杂度 
		else m[l[i]]=c[i];                  //如果不存在temp，就新建一个m[l[i]] 
		for(iter=m.begin();iter!=m.end();iter++){      //枚举map中的每个值，状态转移 
			su=gcd(l[i],iter->first);                  //su是l[i]和当前迭代器所指的key的最大公因数 
			temp=m[su];                                //temp为su为最大公因数时的最小代价 
			if(temp)m[su]=min(temp,iter->second+c[i]);       //如果temp存在，那么比较大小，然后更新
			//因为l[i]和当前key的最大公因数为su，所以m[key]和l[i]一起选的最大公因数就是su，和原先的比较一下大小 
			else  m[su]=iter->second+c[i];   //如果temp不存在，新建一个 
		}
	}
	int ans=m[1];   //处理答案 
	if(ans)cout<<ans<<endl;
	else cout<<-1<<endl;
} 
```

---

