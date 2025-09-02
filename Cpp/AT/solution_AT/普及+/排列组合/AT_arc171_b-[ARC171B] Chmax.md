# [ARC171B] Chmax

## 题目描述

对于一个 $1$ 到 $N$ 的排列 $P=(P_1,P_2,\cdots,P_N)$，如下定义 $F(P)$：

- 初始序列 $B=(1,2,\cdots,N)$。只要有一个整数 $i$ 令 $B_i<P_{B_i}$ 存在，就进行下面的操作：
    - 找到最小的满足 $B_j<P_{B_j}$ 的整数 $j$，则将 $B_j$ 替换为 $P_{B_j}$。
  
  将 $F(P)$ 定义为这一过程结束时的 $B$（可以证明这个过程会在有限步数后终止）。

给你一个长度为 $N$ 的序列 $A=(A_1,A_2,\cdots,A_N)$，请问有多少个 $1$ 到 $N$ 的排列 $P$ 满足 $F(P) = A$？答案对 $998244353$ 取模。

## 说明/提示

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq N$
- 所有的输入都是整数。

## 样例 #1

### 输入

```
4
3 3 3 4```

### 输出

```
1```

## 样例 #2

### 输入

```
4
2 2 4 3```

### 输出

```
0```

## 样例 #3

### 输入

```
8
6 6 8 4 5 6 8 8```

### 输出

```
18```

# 题解

## 作者：rui_er (赞：5)

考察题面中的操作究竟做了什么，不难发现其实是将所有满足 $P_i > i$ 的 $i\to P_i$ 连边，得到若干条链，然后 $B_i$ 即为 $i$ 所在链的最后一个节点。

显然，存在 $A_i < i$ 时无解，存在 $A_i\ne i$ 但 $A_j = i$ 时也无解。

否则，每个 $A_i\ne i$ 的位置填的数都唯一确定了（必须是下一个满足 $A_j=A_i$ 的 $j$），只需计算将剩下的数填入 $P$ 中，且满足 $P_i < i$ 的方案数。这个是十分容易的。具体来说就是从小到大枚举 $i$，统计有多少个不超过 $i$ 的数还没有用过，然后如果当前位置需要填一个数，就从这些数中选择一个填入，乘法原理统计即可。

```cpp
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)

typedef Modint<998244353> mint;

int n, a[N], lst[N], vis[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    per(i, n, 1) {
    	if(a[i] < i) {
    		cout << 0 << endl;
    		return 0;
    	}
    	if(lst[a[i]]) vis[lst[a[i]]] = 1;
    	else if(i != a[i]) {
    		cout << 0 << endl;
    		return 0;
    	}
    	lst[a[i]] = i;
    }
    mint cnt = 0, ans = 1;
    rep(i, 1, n) {
	    cnt += !vis[i];
    	if(i == a[i]) {
	    	ans *= cnt;
	    	--cnt;
	    }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：是青白呀 (赞：2)

可爱题。

观察到有“让 $B_i$ 等于 $P_{B_i}$” 一类的操作，考虑对于某个确定的 $P$ 序列可以建图，从 $i$ 连边向 $P_i$，表示序列中一个位置的权值可以从 $i$ 变到 $P_i$。由于 $P$ 是一个排列，则图中每个点必定有一条入边和一条出边，也就是会形成若干多个环。显然一张图与一个排列 $P$ 一一对应。考虑统计不同合法图的数目。

每一个 $B_i$ 在图上的操作是：从 $i$ 号点开始一直走，直到下一个点的编号不大于该点编号时停止。对于任意 $i<j$ 满足 $A_i=A_j$，$i$ 在变化的过程中一定会经过点 $j$，因为所有的变化过程中，点的编号都是单调递增的，并且以同一个点为终点的变化路径只有一条（因为每个点只有一条入边）。

于是对于任意 $i<j<k$ 满足 $A_i=A_j=A_k=k$ 的点 $j$，它的出边和入边都被唯一确定。进而，不被确定的边只有所有满足 $A_k=k$ 的点 $k$ 的出边，要连向编号小于等于 $k$ 的点；以及满足 $A_i$ 在序列中首次出现的点 $i$ 的入边。

不难发现，满足 $A_k=k$ 的点 $k$ 连向任意满足 $i\leq k$ 且 $A_i$ 在序列 $A$ 中首次出现的点 $i$ 均合法。因而从前往后扫一遍，维护还没有入边的点 $i$ 的数量即可。注意点 $k$ 是可以连向它自己的。

此外，对于存在 $A_j=k$ 但 $A_k\neq k$ 的情况，或 $a_i<i$ 的情况均是不合法的，需要提前判断。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) lson[x]
#define rs(x) rson[x]
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
const int N=2e5+5,mo=998244353,inf=1e18+7;
typedef long long ll;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,a[N],nxt[N],ans=1;
bool st[N],endp[N],la[N];
signed main(){
	read(n);
	rep(i,1,n)
	    read(a[i]),endp[a[i]]=1;
	rep(i,1,n){
		if(endp[i]&&a[i]!=i){
			printf("0");
			return 0;
		}
		if(a[i]<i){
			printf("0");
			return 0;
		}
		if(!la[a[i]])la[a[i]]=1,st[i]=1;
	}
	int cnt=0;
	rep(i,1,n){
		if(st[i])cnt++;
		if(a[i]==i)ans=ans*cnt%mo,cnt--;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：GI录像机 (赞：1)

## 猜测结论：

想不清楚怎么转化问题怎么办？打表！

我们给样例三打一个表，满足条件的排列有：

```
2 6 7 1 3 4 8 5
2 6 7 1 3 5 8 4
2 6 7 1 4 3 8 5
2 6 7 1 4 5 8 3
2 6 7 1 5 3 8 4
2 6 7 1 5 4 8 3
2 6 7 3 1 4 8 5
2 6 7 3 1 5 8 4
2 6 7 3 4 1 8 5
2 6 7 3 4 5 8 1
2 6 7 3 5 1 8 4
2 6 7 3 5 4 8 1
2 6 7 4 1 3 8 5
2 6 7 4 1 5 8 3
2 6 7 4 3 1 8 5
2 6 7 4 3 5 8 1
2 6 7 4 5 1 8 3
2 6 7 4 5 3 8 1
```

发现只有几个位置上的数在变动，观察这几个位置在 $A$ 序列上有什么共同点。

它们都满足 $i=A_i$。因此这些数一次都不会进行变化，需要满足 $i\ge P_i$。

于是可以推测 $i\neq A_i$ 的数确定为唯一正确的数，$i=A_i$ 的数满足 $i\ge P_i$ 的排列都是合法的。

事实上确实是这样，那么为什么呢？

## 证明一下：

让所有 $i$ 对 $P_i$ 连边，那么显然所有 $A_i$ 相同的数在同一个环内，让所有数沿环变化。

由于所有数都会在沿环第一个满足 $i\ge P_i$ 的地方停下，所以 $A_i$ 相同的数在环上的位置一定是连续的。

又因为只有满足 $i< P_i$ 才不会停，所以 $A_i$ 相同的数在环上是递增排列的。

于是只有 $A_i= i$ 的数会变化。

## 代码实现：

显然，有 $A_i<i$ 时无解；有 $A_i\neq i$ 且有 $A_j=j$ 时无解。

否则，乘法原理统计。所有 $A_i=i$ 的数相当于一段相同 $A_i$ 的末尾，第一次出现的 $A_i$ 相当于一段相同 $A_i$ 的开头。我们要匹配开头和末尾，就只需要在每个末尾乘上前面出现过的，未被使用的开头个数。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 998244353, INF = 0x3f3f3f3f;
int a[N], n = read(), maxn[N], ans = 1, cnt;
bool vis[N];
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		maxn[a[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		if (maxn[i] && maxn[i] != i) {
			putchar('0');
			return 0;
		}
		if (!vis[a[i]] && maxn[a[i]])cnt++;
		vis[a[i]] = 1;
		if (a[i] == i)ans = (1ll * (cnt--) * ans) % MOD;
	}
	write(ans);
	return 0;
}
```


---

## 作者：_Ch1F4N_ (赞：0)

考虑我们的操作到底是在干啥。

$i \to p_i$ 连出置换环森林，那么 $A_i$ 就是 $i$ 一直跳直到 $p_i \leq i$ 时停下来所在的点。

假设 $a_1 < a_2 < a_3 < \dots < a_k$ 为满足 $A_{a_i}=C$ 的所有点，说明置换环上存在 $a_1 \to a_2 \to a_3 \to \dots \to C$，并且由于在 $C$ 处停止，所以 $A_C=C$ 也就是 $a_k = C$。

也就是说根据 $A$ 数组可以得到置换环上存在若干段形如 $x \to y$ 的链，我们需要将这些链拼回去，并计数。

考虑转换回排列，将 $m$ 条链拼为置换环视作合法的 $1,2,3,\dots,m$ 的排列 $q$ 计数，$q_i=z$ 说明链 $i$ 的尾巴大于链 $z$ 的开头，按照限制大小（也就是链的尾巴大小）从小到大排序后让这些链依次选择对应的 $q$ 的值即可，时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 2e5+114;
int a[maxn];
int l[maxn],r[maxn],n;
int pre[maxn];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) l[i]=r[i]=i;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]<i){
            cout<<0<<"\n";
            return 0;
        }
        l[a[i]]=min(l[a[i]],i);
    }
    for(int i=1;i<=n;i++){
        if(a[a[i]]!=a[i]){
            cout<<0<<"\n";
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i]==i) pre[l[i]]++;
    }
    for(int i=1;i<=n;i++) pre[i]+=pre[i-1];
    int ct=0;
    int res=1;
    for(int i=1;i<=n;i++){
        if(a[i]==i){
            res=res*max(0*1ll,pre[i]-ct)%mod;
            ct++;
        }
    }
    cout<<res<<"\n";
    return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 思路
观察一下发现排列之间有关系，往图论想，发现最终可以构造出一张图，所有 $a_i>i$ 的位置沿着图走一定会到达 $a_i=i$ 的位置，并且只能走向下一个 $a_j=a_i$ 的位置 $j$，因为不能回头，而最后那些 $a_i=i$ 的位置则可以指向所有还没有入度的位置，而每个没有入度的位置一定是一块的开头，于是记录一下到现在位置有多少个块的开头可以被选择，每次碰到一个终点位置算一下贡献即可。

坑点：如果 $a_i<i$ 必不可能，则 $a_i\ne a_{a_i}$ 必不可能，因为你既然你可以到 $a_i$，那你的 $a$ 肯定至少有 $a_{a_i}$，结合上一个条件就是不等号。
## 代码
```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
// #define int long long
using namespace std;
const int N = 2e5 + 10, mod = 998244353;

int n, a[N];
bool st[N], in[N], out[N];

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i ++) {
        cin >> a[i];
        if(!st[a[i]]) in[i] = 1, st[a[i]] = 1;
    }
    for(int i = 1; i <= n; i ++) {
        if(a[i] < i || (a[i] != a[a[i]])) {
            cout << 0 << '\n';
            return 0;
        }
    }
    memset(st, 0, sizeof st);
    for(int i = n; i; i --)
        if(!st[a[i]]) out[i] = 1, st[a[i]] = 1;
    int ans = 1;
    for(int i = 1, cnt = 0; i <= n; i ++) {
        cnt += in[i];
        if(out[i]) ans = 1ll * ans * cnt % mod, cnt --;
    }
    cout << ans << '\n';

    return 0;
}
```

---

## 作者：cosf (赞：0)

我们先来看看什么情况无解。

- 如果存在 $a_i \lt i$，显然不行。
- 如果存在 $a_{a_i} \not= a_i$，显然也不行。

然后就可行了。

假设有一组链 $\{i_1, i_2, \dots, i_k\} (i_j \lt i_{j + 1}, 1 \le j \lt k)$。满足 $a_{i_j} = i_k (1 \le j \le k)$，则 $p_{i_j}$ 必定等于 $p_{i_{j + 1}}$。手玩一下即可知道正确性。那么，“自由”的点只有那些 $a_i = i$ 的点，它们的 $p_i$ 值不比自己大。显然，这些值只能是链头（最小值）。

因此，本题可以转化为：求将 $\{b_1, \dots, b_k\}$ 赋值给 $\{c_1, \dots, c_k\}$，满足 $c_i \ge d_i$ 的方案数。扫一遍即可。

复杂度 $O(n)$。

```cpp
#include <iostream>
using namespace std;

#define MAXN 200005
#define MOD 998244353ll

using ll = long long;

int n;

int a[MAXN], b[MAXN], c[MAXN];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] < i)
        {
            cout << 0 << endl;
            return 0;
        }
        if (!b[a[i]])
        {
            c[i] = 1; // 是否是链头
            b[a[i]] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[a[i]] != a[i])
        {
            cout << 0 << endl;
            return 0;
        }
    }
    ll res = 1, s = 0;
    for (int i = 1; i <= n; i++)
    {
        if (c[i])
        {
            s++;
        }
        if (a[i] == i)
        {
            res = res * s % MOD;
            s--;
        }
    }
    cout << res << endl;
    return 0;
}

```

---

## 作者：huangrenheluogu (赞：0)

图论建模一下，发现一张合法的图和 $p$ 序列一一对应。在这个 $p$ 上操作相当于一直走这个有向图，直到出度为 $0$。

对应关系就是：$E=\{\forall i,i<p_i,(i,p_i)\}$。

考虑什么图是合法的。

- 每一个点出度/入度不超过 $1$。

- 对于一条有向边 $(x,y)$，满足 $x<y$。

- 这张图是若干条链和若干个孤点构成的。

所以，问题转化为对这种有向图计数。

首先，一个 $A$ 序列必须是合法的，及 $A_i>i$。

对于一个 $i$，考虑在图上的意义，就是 $i$ 可以走到 $A_i$，并且 $A_i$ 出度为 $0$。

对于 $x_1<x_2<\cdots<x_k,s.t.A_{x_1}=A_{x_2}=\cdots=A_{x_k}=x_k$，那么图上的连边必然是 $x_1\rightarrow x_2\rightarrow \cdots \rightarrow x_k$。

那么，我们有一些出度为 $0$ 的点 $\{a_m\}$，和一些没有入度的点 $\{b_m\}$，考虑进行配对。需要满足 $a_i>b_j$，$i$ 和 $j$ 才可以进行配对。这个东西是简单的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
int n, a[N], minn[N], aa[N], bb[N], t, j, ans = 1;
bool vis[N];
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) vis[a[i]] = 1;
	for(int i = 1; i <= n; i++){
		if((a[i] != i && vis[i]) || a[i] < i){
			puts("0");
			return 0;
		}
	}
	for(int i = 1; i <= n; i++) minn[i] = i;
	for(int i = 1; i <= n; i++){
		minn[a[i]] = min(minn[a[i]], i);
	}
	for(int i = 1; i <= n; i++){
		if(a[i] == i){
			bb[++t] = i;
			aa[t] = minn[i];
		}
	}
	sort(aa + 1, aa + t + 1);
	sort(bb + 1, bb + t + 1);
	j = 1;
	for(int i = 1; i <= t; i++){
		while(j < t && aa[j + 1] <= bb[i]) j++;
		ans = ans * (j - i + 1) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution

把 $A_i$ 相同的 $i$ 放到同一个块内，不难发现，对于 $A_i$ 都等于 $x$ 的块，如果块内存在大于 $x$ 的数，那么必然不合法，否则块内除了点 $x$，其他的点的 $P$ 必然是固定的，一定为块内第一个编号大于这个点的点。

对答案有贡献的点就只有 $A_i=i$ 的点，由于 $P$ 为排列，那么 $P_i$ 就只能为前面 $P$ 没出现过的小于等于 $i$ 的块内最小值，对块内最小值维护一下前缀和，再从小到大枚举 $A_i=i$ 的点 $i$，这个点的对答案的贡献就为 $i$ 点的前缀和减去前面 $A_j=j$ 的个数，答案就为所有点的贡献的乘积，时间复杂度 $O(n)$。

注意还要特判一下 $A$ 为 $2,3,3$ 这种情况：如果存在 $A_{A_i}>A_i$ 的情况，那么必然不合法，赛时因为没特判这种情况罚了 $11$ 发还没调出来 /kel。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=2e6+1;
int n,a[N],s[N];
bool st[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x; 
}
int main()
{
	n=read(); int ans=1;
	for (int i=1;i<=n;i++) {
		a[i]=read();
		if (!st[a[i] ] ) s[i]++,st[a[i] ]=true;
		if (i>a[i]) return putchar('0'),0;
	}
	for (int i=1;i<=n;i++) if (a[a[i] ]>a[i]) return !putchar('0');
	for (int i=1;i<=n;i++) s[i]+=s[i-1];
	for (int i=1,cnt=0;i<=n;i++) if (a[i]==i)
	ans=1ll*ans*(s[i]-cnt)%mod,cnt++;
	return !printf("%d",ans);
}
```

---

## 作者：carefree_Zhuang (赞：0)

分析题目操作的实质，如果现在数字是 $i$，那么**可能**会跳转到 $P_i$。把跳转关系看作是边，数字看作点，则可以得到一个图 $G$，有 $n$ 个点，$n$ 条边。可证这个图由若干个环组成。

一个点有且仅有一个入边，设这个点为 $u$。因为 $P$ 是一个排列，所以 $u$ 只出现一次。同理一个点只有一条出边。使用归纳法，对于 $n=1$ 是自环显然成立。考虑 $n+1$ 的情况，新点自环成立，不是自环，一定有另一个环的点断了出边，连到新点。那么那个断掉的环中一定少了一条入边，那么他要么向第三个环去要，但是仍然少一条入边。此时新点多一条出边，所以一定会练到新点。而断掉的环是链，链首尾相接是环（画图理解下）。所以 $n+1$ 的情况成立，进而对所有情况都成立。

这个叫 [cycle decomposition](https://atcoder.jp/contests/arc171/editorial/9227)

然后把图中不符合题意的边断掉，则有若干条链，即路径。然后可以进行重构。那么路径中非尾的点的 $P_i$ 是确定的，只有尾部的点 $u$，要求 $P_u\leq u$。

将尾部的点的集合记作 $S$，把没有匹配的点，即无入边的点记作 $T$。两者数量相同（证明类似上方，留给读者作为练习）。

答案即为把 $S$ 和 $T$ 中点匹配，满足 $S_i \geq T_i$。

```
//不必使用组合数，乘法原理即可 
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
const int N=2e5+10;
int n;
int a[N],b[N];//序列 
int vis[N],last[N];//权值 
int c[N];//贪心 
long long jc[N];
long ksm(long long a,int b){
	long long res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
long long C(int x,int y){
	if(y==0)return 1;
	long long res=jc[x];
	res = res*ksm(jc[x-y],mod-2)%mod;
	res = res*ksm(jc[y],mod-2)%mod;
	return res;
}
int main(){
	jc[0] = 1;
	for(int i=1;i<=2e5;++i)jc[i]=jc[i-1]*i%mod;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(a[i]<i){
			puts("0");
			return 0;
		}
		if(last[a[i]]){
			b[last[a[i]]] = i;
			vis[i] = 1;
		}
		last[a[i]]=i;
	}
	for(int i=1;i<=n;++i)
		if(last[i]){
			if(i>last[i]&&b[i]){
				if(b[i]>i){
					puts("0");
					return 0;
				}
			}
			c[a[last[i]]] += 1;
		}
	int sum=0;
	long long ans=1;
	for(int i=1;i<=n;++i){
		if(!vis[i])sum++;
		if(sum<c[i]){
			puts("0");
			return 0;
		}
		if(c[i]){
			ans = ans*C(sum,c[i])%mod;
			sum -= c[i];
		}
	}
	printf("%lld\n",ans);
	return 0;
}


```

改掉多余的空格了，求通过

---

## 作者：white_carton (赞：0)

[更好的阅读体验](https://starback24.github.io)

[题目链接](https://atcoder.jp/contests/arc171/tasks/arc171_b)

### 分析

下文中提到的 $B,P,A$ 均为题目中的意思。

首先可以发现，从 $B$ 变为 $A$ 的过程中，每个位置上的数只能变大不能变小，我们现在从右向左看 $A$，合法情况下每个数第一次出现下标必然是这个数，接下来我将以第三个样例为例子阐述这一点。

```
8
1 2 3 4 5 6 7 8（B数组）
6 6 8 4 5 6 8 8（A数组）
```

我们先以 $A_5$ 作例子，由于 $A$ 变为 $B$ 的过程中每个数只能变大，所以 $A_5$ 右边不可能出现 $5$（这样会变小）。如果 $P$ 数组上 $5$ 的位置是个比 $5$ 大的数 $a$，$A_5$ 上就不会是 $5$，左边也更不可能是 $5$ 了，一定都是 $a$，因此，$A$ 数组中每个数第一次出现下标都是这个数。

接下来说每个数第二次出现，这里用 $A_7$ 作例子。

由于 $A_7$（第二次出现）与 $A_8$（第一次出现）之间没有别的等于 $8$ 的点，又因为 $A$ 变为 $B$ 的过程中每个数只能变大（$A_7$ 不能先变小再变大），所以 $A_7$ 没有可中转的点（并不是因为 $7,8$ 之间没有别的数），这时 $P_7$ 填入的数字只能是 $8$。以此类推，第 $3$ 次出现 $P$ 填入的是第 $2$ 次的下标，第 $4$ 次出现填入的是第 $3$ 次的下标……最终我们发现，最后 $P$ 数组中是若干条根据 $A$ 数组的相等关系形成的链。

这时 $P$ 数组中还会剩下一些位置没填，统计一下即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Dor(i,a,b) for(int i=a;i>=b;i--)
#define int long long
int n;
const int mod=998244353;
int a[1000100],lst[1000100],b[1001000],flag,book[1001000],vis[1001000];
signed main(){
	cin>>n;
	For(i,1,n){
		cin>>a[i];
		if(a[i]<i){
			flag=1;
		}
		lst[i]=i;
	}
	if(flag){
		cout<<0<<endl;
		return 0;
	}
	Dor(i,n,1){
		b[i]=lst[a[i]];
		if(i!=a[i]){
			book[lst[a[i]]]=1;
		}
		lst[a[i]]=i;
	}
	For(i,1,n){
		if(b[i]==i){
			continue;
		}
		if(vis[i]){
			continue;
		}
		int j=i,minn=a[i];
		while(b[j]!=j){
			vis[j]=1;
			if(b[j]>minn){
				cout<<0<<endl;
				return 0;
			}
			j=b[j];
		}
	}
	int sum=0,ans=1;
	For(i,1,n){
		if(book[i]){
			sum--;
		}
		sum++;
		if(b[i]==i){
			ans=ans*sum%mod;
			sum--;
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc171_b)
### 题解
观察题目，发现题目中涉及到 $P_x,P_{P_x},P_{P_{P_x}}\cdots$，故考虑建立有向图，每条边为 $<i,P_i>$。

由于 $P$ 是长为 $n$ 的排列，所以每个点入度和出度都是 $1$，显然这个图是由一个个环组成的。

思考可以发现：

1. $a_i$ 相同的点一定在同一个环内。
1. 如果 $a_i<i$ 那么显然无解。
1. 对于任意 $k$，找到最大的下标 $j$ 满足 $a_j=k$，如果 $j\neq k$，那么也显然无解（想一想为什么）。
1. 设满足 $a_i=k$ 的所有下标的集合为 $v_k$，设 $v_{k,u}$ 为集合中第 $u$ 小的下标，那么建图时一定有以下边：
	- $<v_{k,1},v_{k,2}>$
    - $<v_{k,2},v_{k,3}>$
    - $\cdots$
    - $<v_{k,\left|v_k\right|-1},v_{k,\left|v_k\right|}>$
   
由 $4$ 可知一个颜色中下标最小的点没有入边（指按照上面方式建图），下标最大的点没有出边。

那么再设没有入度的点为 $vec_1$，没有出度的点为 $vec_2$。

由于大编号连向小编号的点必然不影响结果，所以我们只需要给每一个 $vec_2$ 的节点找到一个小于等于自己编号的点 $vec_1$ 并连边，同时满足 $vec_1$ 中的点不被重复计算，这个东西可以用双指针搞定。

### 代码
```
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 200010,MOD = 998244353;
int n;
int a[N];
vector <int> v[N];
int main () {
	cin >> n;
	for (int i = 1;i <= n;i++) {
		cin >> a[i],v[a[i]].pb (i);
		if (a[i] < i) {
			puts ("0");
			return 0;
		}
	}
	vector <int> v1,v2;	// in;out
	for (int i = 1;i <= n;i++) {
		if (!v[i].size ()) continue;
		if (a[i] != i) {
			puts ("0");
			return 0;
		}
		v1.pb (v[i][0]),v2.pb (v[i].back ());
	}
	sort (v1.begin (),v1.end ());
	sort (v2.begin (),v2.end ());
//	for (int x : v1) cout << x << ' ';
//	cout << endl;
//	for (int x : v2) cout << x << ' ';
//	cout << endl;
	LL ans = 1;
	for (int i = 0,j = 0;i < v2.size ();i++) {
		while (j < v1.size () && v1[j] <= v2[i]) j++;
		ans = ans * max (j - i,0) % MOD;
        // 当前选走了 i 个 v1 中的点，且目前有 j 个 v1 中的点满足编号小于等于 i，目前还有 j-i 个 v1 中的点
	}
	cout << ans << endl;
	return 0;
}
```

---

