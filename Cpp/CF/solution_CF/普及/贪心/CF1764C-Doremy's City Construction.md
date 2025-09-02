# Doremy's City Construction

## 题目描述

Doremy's new city is under construction! The city can be regarded as a simple undirected graph with $ n $ vertices. The $ i $ -th vertex has altitude $ a_i $ . Now Doremy is deciding which pairs of vertices should be connected with edges.

Due to economic reasons, there should be no self-loops or multiple edges in the graph.

Due to safety reasons, there should not be pairwise distinct vertices $ u $ , $ v $ , and $ w $ such that $ a_u \leq a_v \leq a_w $ and the edges $ (u,v) $ and $ (v,w) $ exist.

Under these constraints, Doremy would like to know the maximum possible number of edges in the graph. Can you help her?

Note that the constructed graph is allowed to be disconnected.

## 说明/提示

In the first test case, there can only be at most $ 3 $ edges in the graph. A possible construction is to connect $ (1,3) $ , $ (2,3) $ , $ (3,4) $ . In the picture below the red number above node $ i $ is $ a_i $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/664da7a7b39c78efe9a85191f05318cb0a9df4d9.png)

The following list shows all such $ u $ , $ v $ , $ w $ that the edges $ (u,v) $ and $ (v,w) $ exist.

- $ u=1 $ , $ v=3 $ , $ w=2 $ ;
- $ u=1 $ , $ v=3 $ , $ w=4 $ ;
- $ u=2 $ , $ v=3 $ , $ w=1 $ ;
- $ u=2 $ , $ v=3 $ , $ w=4 $ ;
- $ u=4 $ , $ v=3 $ , $ w=1 $ ;
- $ u=4 $ , $ v=3 $ , $ w=2 $ .

Another possible construction is to connect $ (1,4) $ , $ (2,4) $ , $ (3,4) $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/7d1fc03a74b1366633e41dc227acef23827c0f69.png)

An unacceptable construction is to connect $ (1,3) $ , $ (2,3) $ , $ (2,4) $ , $ (3,4) $ . Because when $ u=4 $ , $ v=2 $ , $ w=3 $ , $ a_u\le a_v \le a_w $ holds, and the respective edges exist.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/02cccee9e8ea3921ef7338c4d1dd72e83e933cbc.png)

## 样例 #1

### 输入

```
4
4
2 2 3 1
6
5 2 3 1 5 2
12
7 2 4 9 1 4 6 3 7 4 2 3
4
1000000 1000000 1000000 1000000```

### 输出

```
3
9
35
2```

# 题解

## 作者：郑朝曦zzx (赞：7)

### 提示
- 想一想，对于三个数 $a \le b \le c$，把 $a$ 分别和 $b,c$ 连边所构成的解会比 $a$ 和 $b$ 连边，$b$ 和 $c$ 连边所构成的解更差吗？如果是多个数呢？

### 题解

CF 的贪心题还是挺有意思的。

上面那个问题的答案是不，不会更差，因为我们建立起 $b$ 到 $c$ 的连边时，必然就要拆除 $a$ 到 $b$ 的连边或者是 $b$ 到 $c$ 的连边。当数的个数更多的时候，连出像 $a, b, c$ 的这样的链，会出现一系列连锁反应，使得答案不会更优。

我们考略把数分成两组，一组的所有数都比另一组小。那么我们就可以进行跨组的连边，这样就能保证答案是最优的。

枚举每个数，找出小于等于它的个数和严格大于它的个数，依据乘法原理更新答案。

有一种特殊情况没有被包含，当所有数都一样的时候，答案就是 $\lfloor\frac{n}{2}\rfloor$。

- 注意，答案可能爆 int。

### 代码
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int T, n;
inline int read()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
int a[200010];
int main()
{
	T = read();
	while (T--)
	{
		LL ans = 0;
		bool tag = 1;
		n = read();
		for (int i = 1; i <= n; ++i)
		{
			a[i] = read();
			if (a[i] != a[1]) tag = 0;
		}
		a[n + 1] = 1e9;
		if (tag == 1)
		{
			printf("%d\n", n / 2);
			continue;
		}
		sort(a + 1, a + n + 2);
		for (int i = 1; i <= n; ++i)
		{
			int pos = upper_bound(a + 1, a + n + 2, a[i]) - a - 1;
			ans = max(ans, (LL)pos * (LL)(n - pos));	
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：Yuki__S2OO8 (赞：6)

[题目](https://www.luogu.com.cn/problem/CF1764C)。

首先通过题意，可以发现一个点若连了点权比它大的点，那它就不能再连点权不大于它的点。连了比它小的同理。然后就是比它大/小的数之间不能连。

第一种情况，不同的数有多个。

若一个点连和它不相等的点的贡献就是大于它的数和小于它的数中取最大值。

还有一种情况，就是所有点点权都相等，那么能产生的贡献就是 $\lfloor \frac{n}{2} \rfloor$。因为每个点的度最多为 $1$。

至于点权有多个的时候为什么不取每种点权，并两两之间连边呢？

因为这样显然是不优的。

感性理解一下，若一种点权出现的次数很少，它对答案的贡献也很少，少它一个也没关系。

若一种点权出现的次数很多，那么我们完全可以通过取比它大/小的将这种点全取了。

---

## 作者：aimoyudexianyu (赞：3)

# [CF1764C Doremy's City Construction](https://www.luogu.com.cn/problem/CF1764C)

## 题意

测试 $T$ 次。

 给定 $n$ 个点，每个点有点权为 $a_i$，任意连边，使图中不存在有三点 $u,v,w$ 同时存在边 $(u,v),(v,w)$ 和 $a_u \leq a_v \leq a_w$，输出最多连的边数。

数据范围：$2 \leq n \leq 2 \times 10^5$，$\ 1 \leq a_i \leq 1 \times 10^6$，保证每组测试样例中 $n$ 的和不超过 $2 \times 10^5$。

## 思路

一个点不能同时与大于等于和小于等于他的点相连，因此，我们考虑二分图思想。

- 当点权不全部相等时：

将所有点分到两个集合 $S_1,S_2$ 中去。令 $S_1$ 中最大点权小于 $S_2$ 中最小点权，之后使 $S_1$ 中的每一个点与 $S_2$ 中的每一个点相连，则边的个数为集合 $S_1$ 中元素个数与集合 $S_2$ 中元素个数之积，易得这是对于当下集合 $S_1,S_2$ 的最优连边方案。

接下来枚举不同的 $S_1,S_2$ 的分法，取整体最优解，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/erc5a3wa.png)

- 当点权全部相等时：

两两相连最优，答案为点数的一半，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zq23p3zn.png)

这是思路，更多详情请看代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, a[200005], T;
int main() {
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld", &n);
		long long max_ans = 0, S1_num = 1; //S1_num即表示S1中的数量也表示S1末尾元素下标
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		sort(a + 1, a + n + 1); //排序方便分类
		if (a[1] == a[n]) { //判断点权是否全部相等
			cout << n / 2 << endl;
			continue;
		}
		while (S1_num < n) { //S1中点最多为n-1个
			while (S1_num < n && a[S1_num] == a[S1_num + 1]) S1_num++; //使与S1中最大点权一样的点加到S1中,如4,4两个点使捆绑的
			max_ans = max(max_ans, S1_num * (n - S1_num)); //乘法原理计算结果并打擂台
			S1_num++; //向S1中添加一个元素
		}
		cout << max_ans << endl;
	}
	return 0;
}
```

完结撒花！

---

## 作者：bryce (赞：3)

## 题目大意
有一些点，每个点有一个点权 $a_i$，你可以在任意两个点间连边。最终你连成的图需要满足：不存在 $u, v, w$ 点满足 $a_u\le a_v\le a_w$ 且边 $(u,v)$,$(v,w)$ 存在。求最多能连的边数。
## 思路分析
要满足条件，先将点权排序，设一个点 $i$，那么它满足前面的数都小于等于它，后面的数都大于等于它。

那么就会有一个贪心方案，以这个点为分段点，后面的所有点与它连边后再与这个点前面的点连边，这样能够满足题目要求，且方案数也越大，但前提是没有与它相等的点。

所以答案就为 $\max\lbrace i \times (n - i)\rbrace$。

有一点要注意，样例中第 $4$ 个过不去，原因是每个点都与 $i$ 相等，那么方案就是两两相连，答案即为 $\lfloor \frac{n}{2} \rfloor$。
## 代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 2e5 + 10;
int T, n, ans;
int a[N];

void solve(){
	n = read(), ans = 0;
	bool f = 0;
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 2; i <= n; i++) if (a[i] != a[i - 1]) f = 1;
	if (!f){
		cout << n / 2 << endl;
		return;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++){
		int pos = upper_bound(a + 1, a + n + 1, a[i]) - a - 1;
		ans = max(ans, pos * (n - pos));
	}
	cout << ans << endl;
	return;
}

signed main(){
	T = read();
	while (T--){
		solve();
	}
	return 0;
}
```

---

## 作者：LJY_ljy (赞：1)

一道高质量的图论贪心题。

考虑任何一个节点 $u$ 的相邻节点：

1. 和自己权值小的节点相连。

2. 和自己权值大的节点相连。

3. 和自己权值相等的节点相连。

**我们先证明：当且仅当所有节点权值都相等时，才会出现第三种连边。**

显然当所有节点权值都相等时，会出现第三种连边。

如果出现第三种连边，且不是所有节点权值都相等，

则我们假设存在 $u, v$ 使得 $a[u] = a[v]$ 且 $u, v$ 相连。

令 $V' = V \setminus \{u, v\}$.

易得 $\{u, v\}$ 和 $V'$ 之间没有连边，否则假设 $v, u' $ 相连, $u' \in V'$.

则 $a[u] \leq a[v] \leq a[u']$ 或者 $a[u'] \leq a[v] \leq a[u]$ 成立且 $(u, v), (v, u')$ 存在，与题意矛盾！

所以 $\{u, v\}$ 与 $V'$ 之间没有边相连。我们假设 $V'$ 内部的边集为 $E'$，故此时的边数为 $\left| E' \right| + 1$，为边数最大值。

考虑拆去 $u, v$ 之间的一条边，添加上 $(u, u'), (v, u')$, 其中 $u' \in V'$ 且 $a[u'] \neq a[u]$.

则 $E'' = E' \cup \{(u, u'), (v, u')\}$ 依旧满足条件且 $\left| E'' \right| = \left| E' \right| + 1$, 与 $\left| E' \right| + 1$ 最大矛盾！

经过上述讨论，我们将本题数据分为两类讨论：

#### 1. 不是所有节点权值都相等

对于任意一种符合条件的连边方案，我们将权值更大的节点归为 A 类节点，将权值更小的节点归为 B 类节点。

将所有 A 类节点构成的集合记为 $A'$, 将所有 B 类节点构成的集合记为 $B'$, **则可以证明 $(A', B')$ 构成二分图。**

**证明**：不妨假设 $A'$ 之间存在边 $(u, v)$, 则不妨设 $a[u] > a[v]$. 由于 $v$ 是 A 类节点，所以存在 B 类节点 $v'$ 使得 $a[v] > a[v']$ 且 $v, v'$ 相连。此时 $a[u] > a[v] > a[v']$ 且 $(u, v), (v, v')$ 均存在，矛盾！ 故可以证明 $(A', B')$ 构成二分图。

我们接下来考虑边数最大值：

下证：**对于二分图 $(A', B')$, 边数最大值为 $\left| A' \right| \left| B' \right|$.** (容易检验，略）

又由于权值相等的节点无法连边，故权值相等的节点必定属于同一个集合。(其实可以证明，如果把权值相同的节点放到二分图的两边，这种情况得到的边数是小于等于将权值相同节点放到二分图同一边 对应的两种情况的最大值的，原因是一次函数的最大值是取在端点上的。）


故边数的最大值为 $\max {\{\#\{u | a[u] \leq C\} \times \#\{v | a[v] > C\}\}}$, 其中 $C$ 最多有 n 种取法（不同 $a[i]$ 的个数最大为 $n$）。

时间复杂度为 $O(n \log n)$, 排序贡献了主要时间复杂度。

#### 2.所有节点权值均相等

容易得到一个节点的度数最大为1，故总度数最大为 $n$, 总边数最大为 $\lfloor \dfrac{n}{2} \rfloor$.

取等条件比较好构造：编号为 $2i - 1$ 与 $2i$ 的连边，其中 $1 \leq i \leq \lfloor \dfrac{n}{2} \rfloor$.

[AC记录](https://codeforces.com/contest/1764/submission/277857049)


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long MAXN = 2e5 + 10;

inline long long read() {
	register long long x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

long long n, a[MAXN];

int main() {
	long long t = read();
	for (long long u = 1; u <= t; u++) {
		n = read();
		for (long long i = 1; i <= n; i++) {
			a[i] = read();
		}
		bool flag = true;
		for (long long i = 1; i <= n; i++) {
			if (a[i] != a[1]) {
				flag = false;
				break;
			}
		}
		if (flag) printf("%lld\n", n / 2);
		else {
			sort(a + 1, a + 1 + n);
			long long last = -1, ans = -1;
			for (long long i = 1; i <= n; i++) {
				if (a[i] != last) {
					last = a[i];
					ans = max(ans, (i - 1) * (n - i + 1));
				}
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：gdf_yhm (赞：1)

[CF1764C](https://www.luogu.com.cn/problem/CF1764C)

[Doremy's City Construction](https://codeforces.com/contest/1764/problem/C)

### 思路

不存在点 $u,v,w$，满足 $a_u\leq a_v\leq a_w$，且边 $(u,v),(v,w)$ 存在。

考虑先排序。

排序后，如果 $a_i$ 连向 $a_j(i\le j)$，那么 $a_j$ 不能连向从 $a_{j+1}$ 到 $a_n$，但可以连向从 $a_1$ 到 $a_{i-1}$。同时 $a_i$ 不能连向从 $a_1$ 到 $a_{i-1}$，但可以从 $a_{j+1}$ 连到 $a_n$。为了最大化连边，如果 $a_i$ 连向 $a_j$，则从 $a_1$ 到 $a_i$ 中每个点都会连边到从 $a_j$ 到 $a_n$ 的点。

所以在排序后的数组上找到 $i$，满足 $a_i\neq a_{i+1}$，最大化 $i\times (n-i)$。

但是，对于样例 $4$，答案来自同一个数值间的连边。这种情况下，一个数与相等的数间不能有两条连边，注意提面中是 $\leq$。答案再与每种元素个数的一半取最大值。

多测清空。

---

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int T;
int n,ans,a[maxn],z,p,q,t[maxn],cnt;
signed main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+n+1);
		cnt=0;
		memset(t,0,sizeof(t));
		for(int i=1;i<=n;i++){
			if(a[i-1]!=a[i])++cnt;
			t[cnt]++;
			ans=max(ans,t[cnt]/2);
//			cout<<ans<<" "<<t[cnt]<<" "<<cnt<<endl;
		}
//		cout<<ans<<" "<<cnt<<endl;
		p=0;q=n;
		for(int i=1;i<=cnt;i++){
//			cout<<t[i]<<" ";
			p+=t[i];q-=t[i];
			ans=max(ans,p*q);
		}
		printf("%lld\n",ans);
		ans=0;
	}
}

```


---

## 作者：james1BadCreeper (赞：0)

首先，我们发现答案跟数的顺序并没有关系，所以可以先排序。

然后，我们发现一个数要么与比它小的连，要么与比它大的连，要么自己连自己。开个桶，维护每个数的出现次数，初始时每个数都连向自己作为 $ans$ 的初值，之后就是前面一段乘上后面一段更新 $ans$。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n; 
int a[200005], buc[200005]; 

void solve(void) {
    cin >> n; 
    for (int i = 1; i <= n; ++i) cin >> a[i], buc[i] = 0; 
    sort(a + 1, a + n + 1); int m = 0; 
    long long ans = 0; 
    for (int i = 1; i <= n; ++i) {
        if (a[i] != a[i - 1]) ans += buc[m++] / 2; 
        ++buc[m]; 
    } ans += buc[m] / 2; 
    int p = 0, q = n; 
    for (int i = 1; i <= m; ++i) ans = max(ans, 1ll * (p += buc[i]) * (q -= buc[i])); 
    cout << ans << "\n"; 
}

int main(void) {
    ios::sync_with_stdio(0); 
    int T; cin >> T; 
    while (T--) solve(); 
    return 0; 
}
```

---

## 作者：Daniel_yao (赞：0)

## Problem
给定 $n$ 个点，每一个点有一个点权 $a_i$，现在可以在任意两个点之间连边，要求最终连成的图中满足：不存在 $u,v,w$，满足 $a_u\leq a_v\leq a_w$ 且边 $(u,v),(v,w)$ 存在。求最多能连的边数。
## Solve
首先，题面要求不存在 $u,v,w$，满足 $a_u\leq a_v\leq a_w$ 且边 $(u,v),(v,w)$ 存在。考虑没有相同的两个权值 $a_i$，那么先将 $a_i$ 从小到大排序，将 $a_i$ 分成两集合 $A,B$，满足 $\forall x\in A,\forall y\in B,x<y$。由于限制条件，连边关系只能是集合 $A$ 的元素连向集合 $B$ 的元素，不能出现同一个集合元素之间连边的情况，并且在所有连边的可能中不能出现“奇环”的情况。

比如 $1~2~3~4$，将其分为 $1~2$ 和 $3~4$ 两部分，然后 $1~2$ 分别向 $3~4$ 连边。$1$ 不能向 $2$ 连边，如果连了就会出现 $1$ 连向 $2$，$2$ 连向 $3$，$3$ 连向 $1$ 的局面，形成奇环，然后 $1<2<3$。就非法了。

这样的连边关系，显然会形成一个**完全二分图**，而且分集合的时候一定是从中间分开，因为**和一定，差小积大**。

将情况推广，假设存在相同的两个权值 $a_i$，那么必须要保证**两个集合内不能有相同的元素**，不然连边关系就假了。比如 $\{1,2\}$ 和 $\{2,3\}$ ，这样 $2$ 会和 $2$ 连边，这样就不满足限制条件了。

因此，我们希望边数更多，就尽可能两集合的元素要相等。但在有 $a_i$ 相同的情况下，是不能完美的做到的。此时就要找一个次优解。如果 $mid$ 的左右两边的元素相同，那么之间在 $mid$ 处断开。否则二分出第一个等于 $a_{mid}$ 的前一个位置和最后一个等于 $a_{mid}$ 的后一个位置。然后取最有解。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

inline int read() {
  rint x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
  return x*f;
}

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 2e6 + 10;

int n, a[N], t;

signed main() {
  t = read();
  while(t--) {
    n = read(); bool f = 0;
    For(i,1,n) {
      a[i] = read(); if(a[1] != a[i]) f = 1;
    }
    if(!f) {
      cout << (n / 2) << '\n';
      continue;
    }
    sort(a + 1, a + n + 1);
    int mid = (n + 1) >> 1;
    int l = upper_bound(a + 1, a + n + 1, a[mid]-1) - a - 1;
    int r = upper_bound(a + 1, a + n + 1, a[mid]) - a - 1;
    cout << max(l * (n-l), r * (n-r)) << '\n';
  }
  return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：0)

我们考虑一下如何保证不会形成题目中的限制的图。

我们考虑按照点权把点分为两个部分，这样两个部分互相两两连边，就不会有影响了。为什么一定是分成两部分最优呢？你可以想一下，两个点的点权大小肯定是能比出来的，如果一个点 $x$，和一个点 $y$，建边 $x\to y$，$y$ 的点权较大，如果此时向另外一个点连边，我们只能连向一个比 $y$ 小的点，并且 $x$ 与这个点不能直接相连，所以我们得出：图是一个二分图，而且在连边的时候，一个点 $x$ 与比他大的点 $y$ 相连后，就只能连向小于 $y$ 的点了，同理，如果 $x$ 比 $y$ 大，$y$ 就只能向比他大的点连边，所以我们排个序，然后根据乘法原理最大化连边即可。

code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000100
using namespace std;
int t,n,a[N],ans;
inline int cmp(int x,int y){return x<y;}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=n/2;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1,cmp);
		int r=2,l=1;
		while(1)
		{
			while(a[r]<=a[l]){r++;if(r>n)break;}
			if(r>n)break;
			ans=max(ans,(r-1)*(n-r+1));
			l=r;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

一个显然的观察是选两个相同的点肯定是不优的。因为如果加入这条边则这两个点无法连接别的任何点。

于是对于每个点，要么大于其全部邻居的点权，要么小于其全部邻居的点权。

然后将点按照大于或小于邻居分为两类，则显然每条边连接的是不同类型的点，否则两个点互相大于或小于，矛盾。

所以对于一个合法的方案，一定存在一个值，使得一部分点按照是否大于这个值分类之后将两类之间连边即可。

因为如果一个点 $ u $ 属于第一类，一个点 $ v $ 属于第二类，则 $ a_u \geq a_v $，否则交换这两个点答案不会更劣。

于是枚举这个分界点，然后将小于等于这个点的点个数乘大于这个点的点个数取最大值即可。

注意一种特殊情况：所有的点点权相同，每个点最多连接一条边，答案显然为 $ \lfloor \frac{n}{2} \rfloor $。

---

## 作者：Polaris_Australis_ (赞：0)

根据题意，每个点只分为一下三种情况：

1. 和点权比自己大的点连边
2. 和点权比自己小的点连边
3. 和点权跟自己相等的点连边

继续考虑，当且仅当所有点点权都相等时才会取第三种情况，否则一定至少存在一个比它大或小的点，对边数的贡献至少比选择第三种情况多 $1$。

综上，我们先判断是不是所有点权都相等，如果是，则输出 $-1$，否则，将点权排序，枚举一个位置，在这个位置左面的全部为 $1$ 类点，右面为 $2$ 类点，并更新答案。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Std{
	void read(int &x){
		x=0;
		int y=1;
		char c=getchar();
		while(c<'0'||c>'9'){
			if(c=='-')y=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<1)+(x<<3)+(c&15);
			c=getchar();
		}
		x*=y;
	}
	int T,n,a[200010];
	void solve(){
		read(n);
		for(int i(1);i<=n;++i)read(a[i]);
		sort(a+1,a+1+n);
		int r=0;
		a[n+1]=-1;
		int ans=0;
		if(a[n]==a[1]){
			printf("%lld\n",n/2);
			return;
		}
		for(int i(1);i<=n;++i){
			if(i>r){
				for(++r;a[r]==a[i];++r);
				--r;
				ans=max(ans,r*(n-r));
			}
		}
		printf("%lld\n",ans);
	}
	void main(){
		read(T);
		while(T--)solve();
	}
}  // namespace Std
#undef int
int main(){
	Std::main();
	return 0;
}
```


---

## 作者：honglan0301 (赞：0)

## 题意简述
给你 $n$ 个点，每个点有点权 $a_i$, 求最多能在图上连多少条无向边，使得不存在两条边 $(u,v),(v,w)$ 连接了三个点权单调不降的点 $u,v,w$。

## 题目分析
容易发现任意一个点，要么只与比自己点权大的点连边，要么只与点权不大于自己的点连边。于是我们考虑把点按照点权大小分成两类，连的边数就是两类点个数的积。排序后枚举分界线即可。  

注意，答案至少是 $n\over2$（每个点最多连一条边），判断一下就好。

## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int t,n,a[200005],ans;
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
bool cmp(int x,int y)
{
	return x<y;
}
signed main()
{
	t=read();
	while(t--)
	{
		n=read();
		ans=n/2;
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
		}
		sort(a+1,a+n+1,cmp);
		int r=2,l=1;
		while(1)
		{
			while(a[r]<=a[l])
			{
				r++;
				if(r>n)
				{
					break;
				}
			}
			if(r>n)
			{
				break;
			}
			ans=max(ans,(r-1)*(n-r+1));
			l=r;
		}
		cout<<ans<<endl;
	}
}
```

---

