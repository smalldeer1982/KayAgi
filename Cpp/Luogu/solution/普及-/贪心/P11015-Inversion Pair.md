# Inversion Pair

## 题目描述

对于一个序列 $p$，我们定义：$p$ 中的逆序对个数为 $\mathrm{W}(p)$。

注：这里的逆序对即为满足 $p_i>p_j$ 且 $i<j$ 的一对数。

现在，给定一个序列 $a$，其为整数 $1\sim n$ 的排列。也就是说，对于任意的 $1\le i\le  n$，都有 $1\le a_i\le n$，$a_i$ 均为整数且互不相同。

现有一张图，上有 $n$ 个节点，编号为整数 $1\sim n$。对于任意的两个编号为 $i,j(1\le i< j\le n)$ 的节点，我们将在它们之间连一条权值为 $\mathrm{W}([a_i,a_{i+1},\dots,a_{j-1},a_j])$ 的无向边。

现有 $q$ 次询问。每次询问给出两个编号为 $x,y$ 节点，求它们之间的最短路径。


## 说明/提示

对于全部数据，保证：$2\le n\le 3\times 10^5$，$1\le q\le 3\times 10^5$，$1\le x,y\le n$。

| $\text{Subtask}$ | $n\le$ | $q\le$ | 分数 | 特殊性质 |
|:-:|:-:|:-:|:-:|:-:|
| $0$ | $100$ | $100$ | $30$ | 无 |
| $1$ | $3\times 10^5$ | $3\times 10^5$ | $70$ | 无 |


## 样例 #1

### 输入

```
3 2
3 1 2
1 3
2 2```

### 输出

```
1
0```

# 题解

## 作者：Drifty (赞：9)

### Solution

我们注意到对于任意长度为 $k$ 的序列 $p$，都有：

$$
\mathrm{W}(p) \ge \sum^{k - 1}_{i=1}\mathrm{W}(\{p_i,p_{i+1}\})
$$

证明显然。

因此我们对于每一次 $(x, y)$ 的询问，不妨令 $x\le y$，则最短走法即为一步一步走：$x\rightarrow x+1\rightarrow \dots\rightarrow y-1\rightarrow y$。前缀和维护即可。

### AC-Code

以下是 [Drifty](/user/729358) 给出的实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 3e5 + 7;
int a[N], n, q, s[N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> q;
    for (int i=1; i<=n; i++) 
        cin >> a[i], s[i] = s[i - 1] + (a[i] < a[i - 1]);
    for (int x, y; q--; ) {
        cin >> x >> y;
        if (x > y) swap(x, y);
        cout << s[y] - s[x] << '\n';
    }
    return 0;
}
```

---

## 作者：Tracy_Loght (赞：5)

这题是从大唐盛世回来的吧。

## 题目描述：

给你一个序列，这个序列中有 $n$ 个数，在一个图中，其 $l$ 到 $r$ 两点间，有一条权值为序列编号 $l$ 到 $r$ 的数中的**逆序对**的个数，求每次给的 $l$ 和 $r$ 的**全源最短路**。

**全源最短路**：就是使从 $a$ 到 $b$ 的路径上**权值**最小。

## 分析：

有多少人是和我一样，认为要用逆序对和全源最短路的，但是过不了，怎么办？

但是，注意，这不是一棵树，是完全图！及每两个点间有一条路径，那么就简单了啊。

怎么走？逆序对，这个东西的权值在同一个序列中长度越大越多是肯定的，及从序列第一项到第 $a$ 项的逆序对个数小于第一项到第 $b$ 项，当前仅当 $a$ 小于 $b$。

这一点告诉我们每一次只需要递归的走到编号加一的位置。

那么答案不就明显了吗？

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,o[300001],dp[300001];
int main(){
	ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0); 
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>o[i];
		dp[i]=dp[i-1];
		if(o[i-1]>=o[i]) dp[i]++;//每次计算当前位置与前一个是否构成逆序对
	}
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		if(a>=b) swap(a,b);//交换
		cout<<dp[b]-dp[a]<<"\n";//前缀和求解
	}
	return 0;
}
//唐式诈骗题 
```

---

## 作者：Yamchip (赞：4)

### 题意

可以理解成将逆序对分步计算，使得每步之间的答案之和最小。

### 思路

有了这个理解，做题就不难了，显然的一点，只要每段内的元素越少，答案就越小，那这样我们只要求出 $\sum_{i=x+1}^{y} (a_{i-1}>a_i)$ 即可。

这里要用前缀和优化。

### Code

```
#include<bits/stdc++.h>
using namespace std;
int n, q, a[300005], sum[300005];
int main(){
    cin >> n >> q;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 2;i <= n;i++)
    {
        sum[i] = sum[i - 1];
        if(a[i - 1] > a[i])
            sum[i]++;
    }
    while(q--)
    {
        int x, y;
        cin >> x >> y;
        if(x > y) swap(x, y);
        if(x == y)
        {
            cout << "0\n";
            continue;
        }
        cout << sum[y] - sum[x] << "\n";
    }
    return 0;
}
```

---

## 作者：__zyq_666_kpzc__ (赞：3)

### [先看题](https://www.luogu.com.cn/problem/P11015)
### 思路分析
显然，$x$ 与 $y$ 之间的最短路径一定是以下方案：

第一次走到 $x+1$，第二次走到 $x+2$，一直走到 $y$ 。

那么很显然，答案就是 $x$ 到 $y$ 之间的所有 $a_i<a_{i-1}$ 的数量，用前缀和优化输出即可。

**注意：$x$ 可能比 $y$ 大，把答案取个绝对值即可巧妙解决问题！**
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int sum[300005],a[300005];
signed main()
{
	int n,T;
	cin>>n>>T;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1];
		if(i!=1&&a[i-1]>a[i])sum[i]++;
	}
	while(T--){
		int u,v;
		cin>>u>>v;
		cout<<abs(sum[v]-sum[u])<<"\n";
	}
    return  0;
}
```

---

## 作者：JoeZYQ (赞：3)

### [先看题](https://www.luogu.com.cn/problem/P11015)
### 思路分析
很明显，若 $x \le y$，那么 $x$ 与 $y$ 之间的最短路径一定是一直走长度为 $1$ 的路径，要走 $y-x$ 次，即第一次从 $x$ 走到 $x+1$，第二次从 $x+1$ 走到 $x+2$，一直走到 $y$ 即可。

如果 $x>y$ 只需交换 $x$ 和 $y$ 的值后再进行上述操作即可。

但是，如果每次操作时都枚举一遍，定会超时，我们可以考虑用前缀和先将从 $1$ 走到每一个 $i$ 的值都预处理出来，即可保证时间正确。
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int sum[300005],a[300005];
signed main()
{
	int n,T;
	cin>>n>>T;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i!=1)sum[i]=sum[i-1]+(a[i-1]>a[i]);
	}
	while(T--){
		int u,v;
		cin>>u>>v;
		if(u>v)swap(u,v);
		cout<<sum[v]-sum[u]<<"\n";
	}
    return  0;
}
```

---

## 作者：_Supernova (赞：3)

### 一、思路分析。

题目要求 $x$ 和 $y$ 的最短路径。

刚开始，我们往最短路（图论）方向考虑，考虑建图和最短路算法。

复杂度爆炸。

那么，我们就要去发现一些性质优化做法。

不妨设 $x \leq y$。

注意到：

对于 $3$ 个点，$l$，$mid$，$r$。

则：$W(l,r) \geq W(l, mid) + W(mid + 1, r)$。

所以推导出最优路径：$x$ 一步一步往右走，知道到达 $y$。

那对于 $x$ 和 $y$，从 $x$ 遍历到 $y$，统计相邻逆序对个数，输出即可。

复杂度 $O(qn)$。

考虑优化，记前缀和数组 $ar_i$ 表示 $1$ 到 $i$ 的相邻逆序对个数，答案即为 $ar_y - ar_x$。

预处理复杂度 $O(n)$，单次查询复杂度 $O(1)$。

总复杂度 $O(n + q)$。

可以通过。

###  二、代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef unsigned long long ull;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <pii, int> piii;
typedef long double ld;
const int N = 3e5 + 5;
int n, q, a[N], x, y, ar[N];
int main(void) {
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 2; i <= n; ++i) {
		ar[i] = ar[i - 1] + (int)(a[i] < a[i - 1]);
	}
	while (q--) {
		cin >> x >> y;
		if (x > y) swap(x, y);
		cout << ar[y] - ar[x] << '\n';
	}
	return 0;
}
```

###  三、警示后人。

对于每次询问，一定要保证 $x \leq y$，否则交换。不然直接升天。

谢谢！

---

## 作者：xiaoke2021 (赞：1)

你说得对，但是贪心。

---

很显而易见的一个结论：从点 $i$ 到点 $j$（这里不妨默认 $i \le j$）的最短路径，一定是从点 $i$ 到点 $i+1$，接着是点 $i+1$ 到点 $i+2$，再接着是点 $i+2$ 到点 $i+3$，$\dots$，点 $j-1$ 到点 $j$ ，这些路径的权值和。

换句话说，就是从点 $i$“一步步”走到点 $j$，不要“跨步走”。

举个例子，从点 3 到点 6，那就先从点 3 到点 4，再从点 4 到点 5，再从点 5 到点 6；而不要直接从点 3 到点 6，或是从点 3 到点 5 再到点 6 之类的。

这个结论很好证明。注意到如果“跨步走”，那么原本“一步步”走所需的权值都会加进去，反而可能会产生新的逆序对，不会产生更优解。

举例而言：`4 3 5 1 2`。

如果”一步步”走，那么有 2 个逆序对：`4 3` 和 `5 1`；如果”跨步走”，比如直接从第一个点走到最后一个点，会发现上述 2 个逆序对仍存在，反而多加了好几个逆序对，显然不会更优。得证。

所以每次只要判断相邻两数是否为逆序对即可。将结论储存下来，用前缀和优化即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[300000+5];
int sum[300000+5]; //sum[i]表示第一个路径到第 i 个路径中的逆序对的数量
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++) sum[i]=sum[i-1]+(a[i-1]>a[i]);
	while(q--){
		int x,y;
		cin>>x>>y;
		if(x==y) cout<<"0\n";
		else cout<<sum[max(x,y)]-sum[min(x,y)]<<endl; //这个地方注意，与普通前缀和不同，没有减一，可以自己算一下
	}
	return 0;
}
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
第一眼看这道题时，想到的是用线段树求区间逆序对再建边，但 $n$ 较大，这样做光是建边就超时了。  
那这道题肯定是要找巧妙方法了。
## 2. 题目做法
有一个显然的结论是，将一个大区间拆成若干个小区间，那么这个大区间的逆序对数量绝对大于等于那些小区间里的逆序对数量的和。为什么呢，因为大区间里的逆序对一定包含了小区间的所有逆序对，而跨小区间所产生的逆序对则只有大区间才有。  
这样我们便知道，每次都只向相邻的点移动的代价显然最小，所以我们只需要向相邻的点建边就行。  
但是每次询问都跑一遍最短路显然还是会超时。因为我们建的图是一条链，所以我们只需要用前缀和记录点一与每个点的距离，这样就可以 $O(1)$ 查询了。  
总时间复杂度 $O(n)$，可以通过此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300010;
const double eps=1e-7;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int n,m;
int a[N],x,y;
int s[N];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=2;i<=n;i++)
	{
		if(a[i-1]>a[i])
			s[i]=s[i-1]+1;
		else
			s[i]=s[i-1];
	}
	while(m--)
	{
		x=read(),y=read();
		if(x>y)
			swap(x,y);
		printf("%d\n",s[y]-s[x]);
	}
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：1)

首先，我们需要知道一个性质：对于长度为 $n$ 的排列 $a$，$W(a)\ge \sum\limits_{i=1}^{n-1}W({a_i,a_{i+1}})$。

证明很简单：对于排列 $a$ 中相邻的两数，如果前面的大于后面的，那么这也是一个逆序对，也会计入 $W(a)$ 中。所以 $a$ 中的逆序对必然包含了 $a$ 中相邻数的逆序对。

有这个性质，再来看原问题：求 $x$ 到 $y$ 的最短路，如果一次跳了大于一步，那么把这次拆成几个跳一步的一定不劣。所以最优跳法一定是一步一步跳。

所以 $x$ 到 $y$ 的最短路为 $\sum\limits_{i=x}^{y-1}[a_i>a_{i+1}]$，这可以用前缀和简单维护。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[300001],s[300001],q;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+(a[i-1]>a[i]);//前缀和
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		if(x>y)swap(x,y);//特判x>y
		cout<<s[y]-s[x]<<'\n';
	}
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：1)

# P11015 Inversion Pair 题解

## 题意

给出长度为 $n$ 的排列 $p$。

设 $f(l,r)$ 表示取 $p$ 的区间 $[l,r]$，其中逆序对的个数。

有 $n$ 个顶点的无向完全图，对于顶点 $i,j(1 \le i < j \le n)$，有长度为 $f(i,j)$ 的边。

给出 $q$ 次询问，每次询问给出两个顶点 $x,y$，求从 $x$ 到 $y$ 的最短路长度。

## 思路

一眼结论题，以下设 $x < y$。

结论：从 $x$ 到 $y$ 的最短路每次跨越一个点一定不劣。

证明：若存在三个点 $x \to y, y \to z$，且三点相邻。

$f(x,z) = f(x,y) + f(y,z) + [p_x > p_z]$。

显然 $[p_x > p_z] \ge 0$，所以 $f(x,z) \ge f(x,y) + f(y,z)$。

于是可以维护相邻两点逆序对的前缀和，$O(1)$ 计算答案。

总时空复杂度 $O(n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+10;
int n,q,a[N],sum[N];
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=2;i<=n;i++) sum[i]=sum[i-1]+(a[i-1]>a[i]);//前缀和
	while(q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		if(l>r) swap(l,r);//有坑
		printf("%d\n",sum[r]-sum[l]);//这里不是 l-1 了，注意
	}
	return 0;
}
```

---

## 作者：JYX0924 (赞：1)

有一个显而易见的结论：假设当前考虑到 $i$，若 $a_{i+1}>a_{i}$，就跳到 $i+1$，否则继续考虑后面的。

所以求一下前缀和即可。

下面是我的 AC 代码。


```c
#include<bits/stdc++.h>
#define ll long long 
#define maxn 300005 
using namespace std;
ll n,q,x,y,a[maxn],sum[maxn];
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>q; cin>>x; sum[1]=0; a[1]=x;
    for(int i=2;i<=n;i++) {cin>>a[i]; sum[i]=sum[i-1]; if(a[i]<a[i-1]) sum[i]++;}
    while(q--)
    {
        cin>>x>>y; if(x<y) swap(x,y);
        cout<<sum[x]-sum[y]<<"\n";
    }
    return 0;
}
```
谢谢大家！！！

---

## 作者：iyka (赞：0)

### subtask 0：
这 30 分就是暴力的分，只要暴力求出每一条路径的长度再去跑一个 floyd 就可以拿到。

### subtask 1：
我们随意画 n 大于四的一个图，再手模一下答案，可以发现，对于最短路答案产生贡献的就只有那些编号相邻的点之间的边，因为只要是非相邻的边就要加上自己边的权和一些多余的权，是绝对不是最优的，所以我们只要在输入时用前缀和维护相邻的边的权值之和再在最后大减小得出答案可以在  $O(n)$ 的时间复杂度内做完。 

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int sum[N],n,x,y,q;
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		cin>>x, sum[i]=sum[i-1]+(y>x), y=x;
	for(int i=1;i<=q;++i)
		cin>>x>>y, cout<<abs(sum[x]-sum[y])<<"\n";
	return 0;
} 
```

---

## 作者：Dollartree (赞：0)

### 题目思路
只需每次通过相邻结点即可，因为相邻两点权值最大是 $1$，然后根据题意求出最短路径即可。

### 易错点
1. 题目中两个编号为 $x,y$ 节点，$x$ 不一定小于等于 $y$。

2. 为何依次通过相邻结点必定是最优解？答案很简单，看图。![](https://cdn.luogu.com.cn/upload/image_hosting/nhos7k1m.png)

图中大的数字是序列 $a$ 中的数字，下面的数字是其下标，线连接结点并写有权值。例如从下标为 $1$ 的结点到下标为 $3$ 的结点，如果每次通过相邻结点，则总路径为 $1+0=1$。如果直接到达，则在这过程中产生新的逆序对，即下标为 $1$ 的结点和下标为 $3$ 的结点产生的逆序对，不是最短路径。

### 代码


```cpp
#include <bits/stdc++.h>//万能头 
using namespace std;
int a[300010],sum[300010];//a为序列a,sum是相邻结点逆序对的前缀和。 
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
	} 
	//前面是输入序列和询问次数 
	for(int i=2;i<=n;++i)
	{
		int temp=0;
		if(a[i]<a[i-1])
		{
			temp=1;
		}
		sum[i]=sum[i-1]+temp;//计算sum 
	}
//	for(int i=1;i<=n;++i)
//	{
//		cout<<sum[i]<<" ";
//	}
//	cout<<endl;
	int x,y;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);//两个节点的编号 
		printf("%d\n",abs(sum[y]-sum[x]));//绝对值是防止x>y 
	}
}//结束 
```

---

## 作者：Cyx20110930 (赞：0)

# 题意简述

现在，给定一个序列 $a$，其为整数 $1\sim n$ 的排列。

现有一张图，有 $n$ 个节点，编号为整数 $1\sim n$。对于任意的两个编号为 $i,j(1\le i< j\le n)$ 的节点，我们将在它们之间连一条权值为 $\mathrm{W}([a_i,a_{i+1},\dots,a_{j-1},a_j])$ 的无向边，其中 $\mathrm{W}(p)$ 表示序列 $p$ 中的逆序对个数。

$q$ 次询问给出两个编号为 $x,y$ 节点，求它们之间的最短路径。

# Sol

注意到 $x\to x+1\to x+2\to x+3\to \dots\to y$ 优于所有其他方法。

证明：$x\to x+1\to x+2$ 优于 $x\to x+2$。

易得后一个操作可能计算了 $a_x$ 与 $a_{x+2}$ 是否逆序对，所以前一个操作更优。

其余同理。证毕！

那么代码就很好写了，统计前缀相邻逆序对就行。

# Code

```
#include <bits/stdc++.h>
using namespace std;
int a[300005],c[300005];
int main(){
    int n,q;cin>>n>>q;
    for (int i=1;i<=n;i++){
        cin>>a[i];c[i]=c[i-1]+min(1,max(0,a[i-1]-a[i]));
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        if(x>y)swap(x,y);
        cout<<c[y]-c[x]<<endl;
    }
}
```

---

## 作者：_zuoqingyuan (赞：0)

# 思路分析

如果我们想要从点 $u$ 到达点 $v(u<v)$。我们只有两种方法：

1. 直接从 $u$ 到 $v$：代价为 $\text{W}([a_u,a_{u+1},\dots,a_{v-1},a_v])$。

2. 先从点 $u$ 到 $u'$，再从点 $u'$ 到点 $v$：中转点 $u'$ 一定满足 $u<u'<v$，否则必然不优（不如第一种路径），所以代价为 $\text{W}([a_u,a_{u+1},\dots,a_{u'-1},a_{u'}])+\text{W}([a_{u'},a_{u'+1},\dots,a_{v-1},a_v])$。想要走这种路径必须满足 $u+1<v$。

我们思考 $\text{W}([a_u,a_{u+1},\dots,a_{v-1},a_v])$ 的实际意义，可以得到如下结论：

任取 $u<u'<v$，可以将 $\text{W}([a_u,a_{u+1},\dots,a_{v-1},a_v])$ 分为三部分：

- $i\in [u,u'],j\in [u,u']$ 且 $(i,j)$ 为逆序对，这样的逆序对数为 $\text{W}([a_u,a_{u+1},\dots,a_{u'-1},a_{u'}])$。

- $i\in [u',v],j\in [u',v]$ 且 $(i,j)$ 为逆序对，这样的逆序对数为 $\text{W}([a_{u'},a_{u'+1},\dots,a_{v-1},a_v])$。

- $i\in [u,u'],j\in [u',v]$ 且 $(i,j)$ 为逆序对，令这样的逆序对数为 $k$。

可以发现，$k$ 一定不低于 $0$，这说明：

$$\text{W}([a_u,a_{u+1},\dots,a_{v-1},a_v])\ge \text{W}([a_u,a_{u+1},\dots,a_{u'-1},a_{u'}])+\text{W}([a_{u'},a_{u'+1},\dots,a_{v-1},a_v])$$

和单源最短路之间的三角形不等式一样，因此可以得出结论：当 $u+1<v$ 时，从 $[u+1,v-1]$ 中任选一个点作为中转点的消费一定不劣于直接从 $u$ 到 $v$ 的消费。

可以进一步将结论推广，得出从 $u$ 到 $v$ 的一条最短路径一定是 $u\to (u+1)\to \dots\to (v-1)\to v$。可以用前缀和快速计算。

时间复杂度 $O(n)$，注意处理 $x>y$ 的情况。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=1e6+10;
int n,q,a[N],s[N];
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",a+i),s[i]=(a[i]<a[i-1])+s[i-1];
	while(q--){
		int l,r;
		scanf("%d %d",&l,&r);
		if(l>r)swap(l,r);
		printf("%d\n",s[r]-s[l]);
	}
	return 0;
}

```

如有错误，请指出。

---

## 作者：jjy2023 (赞：0)

# P11015 Inversion Pair
这个题有一个很坑的地方，~~足足坑了我半个小时~~。
## Description：
给你有 $n$ 个点的序列 $p$，对于任一 $(i,j)$，若 $i<j$ 且 $p_i>p_j$，则称 $(i,j)$ 为逆序对。对于一个序列 $p$，定义 $p$ 中的逆序对个数为 $\mathrm{W}(p)$ 。对于每一 $(i,j)$，于 $i,j$ 间连接长度为 $\mathrm{W}([a_i,a_{i+1},\dots,a_{j-1},a_j])$ 的边。现有 $q$ 此询问，每次给你两个节点 $x,y$，求 $x$ 到 $y$ 的最短路径。
## Solution：
考虑到 $O(n^2)$ 的 dijkstra 算法会超时，于是思考是否有最优策略。我们发现，每一 $(i,i+1)$ 之间的边权要么为 $1$ 要么为 $0$，而 $\mathrm{W}(p)$ 的值必然 $\ge\sum_{i=1}^{k-1}\mathrm{W}(p_i,p_{i+1})$，所以最优策略即为一步一步走（即 $i\rightarrow i+1\rightarrow\dots\rightarrow j$）。所以可以用前缀和来维护。
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[300005],b[300005],ans=0;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
		if(a[i]<a[i-1]) ans++;
		b[i]=ans;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		cout<<abs(b[y]-b[x])<<endl;//这是一个很大坑点，若不开abs会出现负数
	}
	return 0;
}
```

---

## 作者：_xdd_ (赞：0)

You can't view the English version of this solution.

最短路径容易看出是一步一步走，维护一个前缀和数组 $pre$，$pre_i \leftarrow pre_i+pre_{i-1}+x$，其中如果 $a_i$ 与 $a_{i-1}$ 是逆序对则 $x\leftarrow1$，否则为 $x\leftarrow0$。

时间复杂度是线性的，可以通过此题。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define maxn 300000+5
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int n,t;
int a[maxn],pre[maxn];
int main(){
    cin >> n >> t >> a[1];
    for(int i=2;i<=n;i++){
        cin >> a[i];
        int x=0;
        if(a[i]<a[i-1]){x=1;}
        pre[i]=pre[i-1]+x;
    }
    while(t--){
        int x,y;
        cin >> x >> y;
        if(y<x){swap(x,y);}//一定要交换！
        cout << pre[y]-pre[x] << endl;
    }
    return 0;
}
```

---

## 作者：dlzlj_2010 (赞：0)

显然，有 $\sum\limits^{r-1}_{i=l}W([a_i,a_{i+1}])\le W([a_l,a_{l+1},\dots,a_r])$，所以 $x$ 到 $y$ 的最短路就是 $x\rightarrow x+1\rightarrow\dots\rightarrow y$，最短路长度为 $\sum\limits^{y-1}_{i=x}W([a_i,a_{i+1}])$。  
那么我们只需要维护前缀和数组 $s_i=\sum\limits_{j=1}^{i}W([a_j,a_{j+1}])=\sum\limits_{j=1}^{i}[a_j>a_{j+1}]$，最终结果就是 $s_{y-1}-s_{x-1}$。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define re register
//#define int ll
typedef pair<int,int>pii;
typedef pair<pii,int>piii;
const int N=3e5+5;
int n,q;
int s[N],a[N];
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++){
		s[i]=s[i-1]+(a[i]>a[i+1]);
	}
	while(q--){
		int x,y;
		cin>>x>>y;
		if(x>y)swap(x,y);//因为是无向边，所以大小关系不影响结果，我们不妨设x<=y
		cout<<s[y-1]-s[x-1]<<'\n';
	}
	return 0;
}

```

---

## 作者：cff_0102 (赞：0)

显然的，若 $i<j<k$，选择从 $i$ 跳到 $j$，再从 $j$ 跳到 $k$，最终的路径长度肯定比直接从 $i$ 跳到 $k$ 要短。因为 $i$ 到 $k$ 的逆序对数量为 $i$ 到 $j$ 的逆序对数量加上 $j$ 到 $k$ 的逆序对数量，再加上一个在 $i$ 和 $j$ 之间，一个在 $j$ 和 $k$ 之间的逆序对数量。

所以实际上每次只用向后跳一个，就能做到答案最小。

用前缀和预处理，每次判断相邻数字是否是逆序对，如果是就加上。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[542457];
int s[542457];
int main(){
	int n,q;cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		s[i]=s[i-1];
		if(a[i]<a[i-1])s[i]++;
	}
	while(q--){
		int x,y;cin>>x>>y;
		if(y<x)swap(x,y);
		cout<<s[y]-s[x]<<endl;
	}
	return 0;
}
```

---

## 作者：王逸辰 (赞：0)

# P11015 Inversion Pair 题解
## 思路
一道非常简单的题，用前缀和维护。

因为是逆序对，所以我们只需考虑当前遍历的数的前一个数是否比它大。

如果是，则前缀和数组当前元素加一。

这样，我们求出来的便是原序列从 $x$ 到 $y$ 中的逆序对。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[300001],f[300001],x,y;
int main(){
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		cin>>a[i],f[i]=f[i-1]+(a[i-1]>=a[i]);
	for(int i=1; i<=m; i++){
		cin>>x>>y;
		cout<<abs(f[x]-f[y])<<'\n';
	}
	return 0;
}
```

---

## 作者：Danny_chan (赞：0)

因为一条路越短逆数对就越少，所以我们只需要用到第二个点的逆数对减去到第一个点的逆数对就好了，可以用前缀和来优化一下。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
int a[300010],s[300010];
signed main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1];
		if(a[i-1]>=a[i]){
			s[i]++;
		}
	}
	while(t--){
		int l,r;
		cin>>l>>r;
		if(l>r) swap(l,r);
		cout<<s[r]-s[l]<<endl;
	}
	return 0;
}
```

---

## 作者：suyi1111 (赞：0)

显然，如果要从 $i$ 走到 $j$，则以下路径最优：$i→i+1→i+2→\cdots→j-1→j$。

证明：首先，因为每次只走一格，所以路径长度必然是 $0$ 或者 $1$，如果 $x→x+1$ 的路径长度是 $1$，则说明不管怎么走必定有一个包含 $x$ 和 $x+1(i\le x<j)$ 的区间，则这里必定产生贡献。

所以直接比较相邻的两个地方判断是否前一个比后一个大就得到了一个 $O(qn)$ 做法。无法通过本题。

进一步的：我们发现这个区间问题可以使用前缀和来维护，这样就有了 $O(q)$ 做法。注意起点可能比终点后面。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300001],n,q;
int s[300001]; 
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(i==1)continue;
		else 
		s[i]=s[i-1]+(a[i]<a[i-1]);
	}
	while(q--){
		int x,y,sum=0;
		cin>>x>>y;
		if(y<x)swap(x,y);
		cout<<s[y]-s[x]<<endl;
	}
	return 0;
}

```

---

