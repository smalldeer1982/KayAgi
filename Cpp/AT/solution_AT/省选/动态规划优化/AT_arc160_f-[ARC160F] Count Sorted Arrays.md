# [ARC160F] Count Sorted Arrays

## 题目描述

给定一个整数 $N$ 和 $M$ 个整数对 $(a_1, b_1), (a_2, b_2), \dots, (a_M, b_M)$。每个 $a_i, b_i$ 满足 $1 \leq a_i < b_i \leq N$。

一开始，你拥有 $(1,2,\dots,N)$ 的所有 $N!$ 种排列。  
你将进行 $M$ 次操作。第 $i$ 次操作如下：

- 对你拥有的所有 $N!$ 个排列，进行如下处理：
  - 比较排列中第 $a_i$ 个元素和第 $b_i$ 个元素的值，如果前者更大，则交换两者。

对于 $1 \leq i \leq M$，记第 $i$ 次操作结束后你拥有的排列中，已经按升序排列的序列的个数为 $S_i$。  
请输出 $S_1, S_2, \dots, S_M$。

不过，输入中给出的并不是 $(a_i, b_i)$，而是整数对 $(x_i, y_i)$。  
$(a_i, b_i)$ 的值需要通过 $x_i, y_i, S_{i-1}$ 按如下步骤计算得到（其中 $S_0 = 1$）：

- $c_i = ((x_i + S_{i-1}) \bmod N) + 1$。
- $d_i = ((y_i + S_{i-1} \times 2) \bmod N) + 1$。（保证 $c_i \neq d_i$）
- $a_i = \min(c_i, d_i)$。
- $b_i = \max(c_i, d_i)$。

## 说明/提示

## 数据范围

- $2 \leq N \leq 15$
- $1 \leq M \leq 5 \times 10^5$
- $1 \leq a_i < b_i \leq N$
- $0 \leq x_i, y_i \leq N - 1$

## 样例解释 1

一开始拥有的排列为 $(1, 2)$ 和 $(2, 1)$。$(a_1, b_1) = (1, 2)$。第 $1$ 次操作后拥有的排列为 $(1, 2)$ 共 $2$ 个。因此输出 $2$。

## 样例解释 2

$(a_i, b_i)$ 依次为 $(1, 2), (2, 3), (1, 3), (1, 2)$。

## 样例解释 3

$(a_i, b_i)$ 依次为 $(1, 2), (3, 4), (1, 5), (2, 3), (4, 5)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3 4
0 1
2 1
1 1
0 1```

### 输出

```
2
4
4
6```

## 样例 #3

### 输入

```
5 5
4 4
0 4
1 1
2 4
1 2```

### 输出

```
2
4
4
8
16```

# 题解

## 作者：_Cheems (赞：8)

排列个数有足足 $n!$ 个，无法直接做，那么可不可以将信息“压缩”起来，换种方式表示排列呢？

有套路：将排列 $P$ 表示拆成 $n$ 个 01 串 $C_1\dots C_n$，其中 $C_{i,j}=[P_j\ge i]$，那么 $P$ 与 $C$ 构成双射。$C_1\dots C_n$ 实际上可视为按 $i$ 从小到大将 $P_q=i$ 的 $q$ 点亮。

也就是说，考虑二进制数 $S\in \{0\dots 2^n-1\}$，让 $i\in S$ 向 $j$ 连有向边，其中 $j$ 恰好比 $i$ 多一个 $1$，那么一条 $0\to 2^n-1$ 的路径恰好对应一个排列。

而且 $P$ 排好序当且仅当 $C_1\dots C_n$ 都排好序，于是每次统计只经过排好序的点的路径总数，就是排好序的 $P$ 的总数。简单 dp 即可，统计一次复杂度 $O(n2^n)$。

但是本题 $m$ 较大，$O(mn2^n)$ 不足以通过。感性地想，真正有效的操作应该不多，有效操作 $x,y$ 表示存在 01 串满足 $c_x=1$ 且 $c_y=0$，只在有效操作时重新 dp 即可。

那么有效操作是什么量级呢？先记 $(p,q)$ 表示 $p,q$ 是否为有效操作。现在进行有效操作 $x,y$，我们将 01 串分为 $A,B$ 两类，$A$ 类满足 $c_x=1$ 且 $c_y=0$，$B$ 类则不满足。

我们将证明操作前后有效操作数量单调递减：考虑 $A$ 类串中由无效变为有效的操作，显然只能是 $p<x$ 或 $y<p$，考虑前者后者同理。那么必须有 $a_p=1$，容易发现，原本 $(p,y)=1$ 但是操作后 $(p,y)=0$，那么恰好抵消掉了。

证明结束？上述讨论只考虑了 $A$ 类串，那么 $B$ 类串呢？$B$ 产生的影响只可能是存在 $(p,y)=1$，使得操作后 $(p,y)$ 依旧不变，那么证明就错了。可是，若有 $B$ 类串 $(p,y)=1$，那么 $c_y=0$，又因为它是 $B$ 类串所以 $c_x=0$，于是会有 $(p,x)=1$，于是操作后 $(p,x)$ 也跟着不变，那么没有影响。

初始时 $O(n^2)$ 个有效操作，于是 dp 部分复杂度 $O(n^32^n)$。

然后拿个 `vector` 存 $(p,q)=1$ 的 01 串，每次取出修改就好。假如 01 串操作后某些 $(p,q)$ 变为 $0$，不必删掉，只需要每次取出时检查下是不是真的满足条件即可；假如 $(p,q)$ 变为 $1$，扔进去就好。

一个 01 串产生变化的 $(p,q)$ 至少一端为 $x,y$，数量为 $O(n)$，而一次取出 $O(2^n)$ 个串。每次那么该部分复杂度 $O(n^32^n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ADD(a, b) a = (a + b)
#define chk(x) (!(x) || __builtin_ctz(x) == n - __builtin_popcount(x))
#define id(x, p) (((x) >> p) & 1)
#define ID(x, y) ((x) * n + (y))
//x=0时ctz出错 
const int N = 15;
int n, m, x, y, a[1 << N], f[1 << N], ans;
bool vis[1 << N];
vector<int> buc[N * N];

inline void ins(int a, int b, int x) {buc[ID(a, b)].push_back(x);}
inline void upd(){
	memset(f, 0, sizeof f), f[0] = 1;
	for(int i = 1; i < 1 << n; ++i)
		if(vis[i])
			for(int j = 0; j < n; ++j)
				if(id(i, j)) ADD(f[i], f[i ^ (1 << j)]);
	ans = f[(1 << n) - 1];
}
signed main(){
	cin >> n >> m;
	for(int i = 0; i < 1 << n; ++i){
		vis[i] = chk(a[i] = i);
		for(int x = 0; x < n; ++x)
			for(int y = x + 1; y < n; ++y)
				if(id(i, x) && !id(i, y)) ins(x, y, i);
	}
	upd(), ans = 1;
	while(m--){
		scanf("%lld%lld", &x, &y);
		x = (x + ans) % n, y = (y + 2 * ans) % n;
		if(x > y) swap(x, y);  
		bool fl = false;
		for(auto i : buc[ID(x, y)])
			if(id(a[i], x) && !id(a[i], y)){
				a[i] ^= (1 << x) | (1 << y);
				if(chk(a[i])) vis[i] = true, fl = true;
				else{
					for(int p = 0; p < x; ++p) if(id(a[i], p)) ins(p, x, i);
					for(int p = y + 1; p < n; ++p) if(!id(a[i], p)) ins(y, p, i);
				}
 			}
 		buc[ID(x, y)].clear();
 		if(fl) upd();
		printf("%lld\n", ans); 
	}
	return 0;
}
```

---

## 作者：Schi2oid (赞：8)

### 题意简述

现在，你有所有 $N!$ 个长度为 $N$ 的排列。接下来，给出 $M$ 次操作，每次操作给出一个二元组 $(a,b)(a<b)$，将你所有的排列中位于 $a$ 和 $b$ 两个位置上的数进行排序，每次操作后输出你现在有几个排列是排好序的，强制在线。

$N\le15$。

### 思路分析

首先，我们考虑这 $M$ 次操作中会有多少次操作是有效的。我们定义一次操作是有效的，当且仅当我们拥有的排列当中，存在一个排列 $p$，使得 $p_a>p_b$。那么，最开始，所有 $\frac{N(N-1)}{2}$ 种操作是有效的，没有操作是无效的。我们关注无效操作的数量。每当我们进行一次有效的操作 $(a,b)$，会将 $(a,b)$ 本身变为无效，但是有可能会导致某些 $(c,a)$ 或 $(b,c)$ 从无效变得有效。至于有效变为无效，我们暂时不考虑。

以一个变为有效的 $(c,a)$ 为例，另一种情况与此对称。此时，原本的 $(c,a,b)$ 大小关系应为 $(1,2,0)$。那么，我们发现原本 $(c,b)$ 也是有效的，而在操作之后，这一对变为无效。所以，每存在一个变为有效的数对，相应地，就会存在一个变为无效的数对，因此无效数对的数量在每次有效操作之后一定单调递增，故总有效操作数不超过 $\frac{N(N+1)}{2}$。如果过程中存在有效变为无效，仍不改变无效数对数量单增，故结论依然成立。

现在，考虑如何描述一个排列，它是排好序的。这等价于，对于每一个 $i$，我们将排列中小于等于它的数改为 $0$，排列中大于它的数改为 $1$，那么所有修改后的序列都应该是排好序的。这样转化的好处是，我们只需要考虑 $01$ 序列，而不是一个排列，那么情况数就从 $O(N!)$ 降低至 $O(2^N)$。在这一转化下，考虑如何求解题目所要求的内容。在每次有效操作之后，我们进行一个 $N$ 维的格路计数，每一维都只有两个位置：$0$ 或 $1$，我们的目标是从 $(0,0,…,0)$ 走到 $(1,1,…,1)$，并且途径的所有 $01$ 状态都可以在执行完所有已经应用的操作后变为有序。事实上，我们走的第 $i$ 步相当于选取了对于位置 $i$ 而言的上述修改后的 $01$ 序列，所以不难发现任何一种格路方案都唯一对应一个排列，且其当前是有序的。这一部分的复杂度是 $O(N^32^N)$，分别来自有效操作数量和单次格路计数复杂度。

那么，我们只需要考虑如何维护有哪些 $01$ 序列经过了这些排列后是有序的，以及哪些操作是有效的。前者只需要暴力维护每个初始 $01$ 序列变成了什么样子即可。至于后者，我们考虑到一次有效操作 $(a,b)$ 只会影响到涉及到 $a,b$ 的操作有效性的改变，即只会更改 $O(N)$ 个操作的有效性，那么其实这一部分的复杂度也是 $O(N^3 2^N)$ 的，可以接受。当然，你也可以直接在每次有效操作后暴力重新处理每一个操作是否有效，那么复杂度变为 $O(N^42^N)$，也可以通过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int become[40005];
bool ok[40005];
bool vis[40005];
bool eff[20][20];
int s[500005];
int dp[40005];
vector<int>vec[20];
int ppcnt(int x){
	int ret=0;
	while(x){
		ret+=x&1;
		x>>=1;
	}
	return ret;
}
int get(int x,int y){return (x>>(y-1))&1;}
int calc(int n){
	memset(dp,0,sizeof dp);
	dp[0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<vec[i].size();j++){
			int st=vec[i][j];
			if(!vis[st]) continue;
			for(int k=1;k<=n;k++){
				if(st&(1<<(k-1))) continue;
				int nst=st^(1<<(k-1));
				if(!vis[nst]) continue;
				dp[nst]+=dp[st];
			}
		}
	}
	return dp[(1<<n)-1];
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=n;i++) ok[((1<<i)-1)<<(n-i)]=1;
	for(int i=0;i<1<<n;i++){
		become[i]=i;
		if(ok[i]) vis[i]=1;
	}
	for(int i=0;i<1<<n;i++) vec[ppcnt(i)].push_back(i);
	s[0]=1;
	for(int i=1;i<n;i++) for(int j=i+1;j<=n;j++) eff[i][j]=1;
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		int c=(x+s[i-1])%n+1;
		int d=(y+s[i-1]*2)%n+1;
		int a=min(c,d);
		int b=max(c,d);
		if(eff[a][b]){
			eff[a][b]=0;
			for(int i=1;i<a;i++) eff[i][a]=0;
			for(int i=b+1;i<=n;i++) eff[b][i]=0;
			for(int i=a+1;i<=n;i++) eff[a][i]=0;
			for(int i=1;i<b;i++) eff[i][b]=0;
			for(int i=0;i<1<<n;i++){
				become[i]=become[i]^((get(become[i],a)>get(become[i],b))*((1<<(a-1))+(1<<(b-1))));
				vis[i]=ok[become[i]];
				for(int j=1;j<a;j++) eff[j][a]|=get(become[i],j)>get(become[i],a);
				for(int j=b+1;j<=n;j++) eff[b][j]|=get(become[i],b)>get(become[i],j);
				for(int j=a+1;j<=n;j++) eff[a][j]|=get(become[i],a)>get(become[i],j);
				for(int j=1;j<b;j++) eff[j][b]|=get(become[i],j)>get(become[i],b);
			}
			s[i]=calc(n);
			printf("%lld\n",s[i]);
		}
		else{
			s[i]=s[i-1];
			printf("%lld\n",s[i]);
		}
	}
	return 0;
}

```

---

## 作者：Tony2 (赞：6)

考虑如何检查一个排列是否被排序。将一个排列转化成 $n-1$ 个 01 序列，例如 `1324` 转化为 `0001`，`0101` 和 `0111`。

只要这 $n-1$ 个 01 序列在经过操作之后都被排好序了，那原来的排列也会被排好序。

问题变成了如何检测 01 串是否被排好序。众所周知，一个 01 串最多有效的交换次数为其逆序对个数即 $n^2$ 级别，一个有效的交换即为交换 $i$ 和 $j(i<j)$ 且 $s_i=1 \And s_j=0$。 

所以所有 01 串总共的有效交换次数是 $2^n\times n^2$ 级别的，对于每一个 $(i,j)$ 开一个 `vector` 表示所有满足 $s_i=1 \And s_j=0$ 的 01 串，能够通过每次清空 `vector` 来找到被交换的 01 串。

交换完可能要把 01 串放回去，此时注意到新增的逆序对最多为 $n$ 个，不需要重新把 $n^2$ 个逆序对加进去，只需要加新增的逆序对即可。

剩下的问题就是如何统计排列数量。注意到一个排列可以看作若干个 01 串形成的**路径**，例如 `1324` 就是 `0000->0001->0101->0111->1111`。我们会不断地点亮节点（01 串被排好序就被“点亮”），统计亮的路径的数量。每次重新 dp 的复杂度太高，可以考虑只对被影响到的点进行 dp，复杂度为 $O(3^n\times n)$。

下图是 $n=3$ 的所有 01 串构成的 dag。

![](https://cdn.luogu.com.cn/upload/image_hosting/eknzr6k4.png)

显然一个大小为 $n$ 的 dag 共有 $n!$ 条路径，每条路径对应了一个排列。

上述算法总复杂度为 $O(2^n\times n^3+3^n\times n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 15;
int n, q;
ll f[1 << N], g[1 << N];
vector<int> vec[N][N];
int cur[1 << N];
bool vis[1 << N];
bool check(int x){
	return x == 0 || __builtin_popcount(x) + __builtin_ctz(x) == n;
}
void insert(int i){
	for (int j = 0; j < n; j++)
		for (int k = j + 1; k < n; k++)
			if (((cur[i] >> j) & 1) && !((cur[i] >> k) & 1))
				vec[j][k].push_back(i);
}
void upd(int x){
	vis[x] = 1;
	for (int i = 0; i < n; i++)
		if ((x >> i) & 1)
			f[x] += f[x ^ (1 << i)];
	g[x] = f[x];
	int lst = x ^ ((1 << n) - 1);
	for (int j = lst; j; j = (j - 1) & lst){
		int c = ((1 << n) - 1) ^ j;
		for (int k = 0; k < n; k++)
			if (!((c >> k) & 1) && vis[c | (1 << k)]){
				f[c | (1 << k)] += g[c];
				g[c | (1 << k)] += g[c];
			}
	}
	for (int j = lst; ; j = (j - 1) & lst){
		g[((1 << n) - 1) ^ j] = 0;
		if (!j) break;
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	cin >> n >> q;
	f[0] = 1;
	for (int i = 1; i < (1 << n); i++){
		cur[i] = i;
		if (check(i)) upd(i);
		else insert(i);
	}
	while (q--){
		int x, y;
		cin >> x >> y;
		x = (x + f[(1 << n) - 1]) % n;
		y = (y + f[(1 << n) - 1] * 2) % n;
		if (x > y) swap(x, y);
		for (int i : vec[x][y])
			if (((cur[i] >> x) & 1) && !((cur[i] >> y) & 1)){
				cur[i] ^= (1 << x) | (1 << y);
				if (check(cur[i])) upd(i);
				else insert(i);
			}
		vec[x][y].clear();
		cout << f[(1 << n) - 1] << endl;
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc160_f)

**题目大意**

> 给定 $n!$ 个 $n$ 个排列，$q$ 次操作给定 $u,v$，对于每个 $p_u>p_v$ 的排列交换 $p_u,p_v$，求出有多少排列被排好序，强制在线。
>
> 数据范围：$n\le 15,q\le 5\times 10^5$。

**思路分析**

显然可以用经典的 01 序列的技巧，设 $a_i=[p_i\ge x]$，那么暴力维护我们能知道每个 01 序列进行 $q$ 此操作后会变成什么。

一个排列合法当且仅当分成的每个 01 序列最后操作完都是有序的。

考虑把一个排列看成从 $00\dots 0$ 走到 $11\dots 1$ 的路径，每次把一个 $0$ 变成 $1$，要求经过的 01 序列最后都被排序，那么这就是一个路径计数问题，简单 dp 即可。

但此时复杂度为 $\mathcal O(q2^n)$，注意到有至少一出影响的非平凡操作数大概是 $\mathcal O(n^2)$ 级别的，只有存在至少一个 01 排序后还有 $p_u>p_v$ 时 $(u,v)$ 操作才是有必要的。

每次加入非平凡操作时更新所有过 $u/v$ 的操作的必要性状态即可。

时间复杂度 $\mathcal O(n^32^n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,f[1<<15];
ll dp[1<<15],ans=1;
bool g[15][15],q[1<<15];
int R(int s,int x,int y) { return ((s>>x)&1)>((s>>y)&1); }
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<(1<<n);++i) f[i]=i;
	for(int i=0;i<n;++i) for(int j=i+1;j<n;++j) g[i][j]=true;
	for(int i=0;i<=n;++i) q[((1<<i)-1)<<(n-i)]=true;
	for(int u,v;m--;) {
		scanf("%d%d",&u,&v),u=(u+ans)%n,v=(v+ans*2)%n;
		if(u>v) swap(u,v);
		if(!g[u][v]) { printf("%lld\n",ans); continue; }
		for(int i=0;i<n;++i) g[u][i]=g[v][i]=g[i][u]=g[i][v]=false;
		for(int i=0;i<(1<<n);++i) {
			if(R(f[i],u,v)) f[i]^=(1<<u)|(1<<v);
			for(int j=0;j<n;++j) {
				if(j<u) g[j][u]|=R(f[i],j,u);
				else g[u][j]|=R(f[i],u,j);
				if(j<v) g[j][v]|=R(f[i],j,v);
				else g[v][j]|=R(f[i],v,j);
			}
		}
		memset(dp,0,sizeof(dp)),dp[0]=1;
		for(int s=1;s<(1<<n);++s) if(q[f[s]]) {
			for(int i=0;i<n;++i) if(s&(1<<i)) {
				dp[s]+=dp[s^(1<<i)];
			}
		}
		printf("%lld\n",ans=dp[(1<<n)-1]);
	}
	return 0;
}
```

---

## 作者：xxxxxzy (赞：2)

设 $f(x)_i = [a_i \ge x]$。

一个排列是排好序的，当且仅当每个 $f(x)$ 都排好序。

考虑把问题转化成一个 $n$ 维的网格计数，从 $(0,...,0)$ 走到 $(1,...,1)$，然后要求路过的所有状态都可以经过已有的操作排好序。

记操作是有效的，即操作后有 01 串状态发生转变，考虑一次操作 $(a,b)$，交换逆序对会让逆序对总数减少，逆序对总数是 $O(n^2)$ 级别的。

时间 $O(n^32^n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vec vector <int>
#define fv inline void
#define fn inline static
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i16 = short; using i32 = ll; using i64 = ll; using i128 = __int128_t;
using namespace std;
const i32 N = 15;
i64 lst = 1, dp[(1 << N) + 5], f[(1 << N) + 5];
i32 n, m, u, v, g[N][N], flg[(1 << N) + 5];
fn bool qry(i32 s, i32 x, i32 y) { return ((s >> x) & 1) > ((s >> y) & 1); }
fv sol() {
  cin >> n >> m;
  rep (i, 0, (1 << n) - 1) f[i] = i;
  rep (i, 0, n - 1) rep (j, i + 1, n - 1) g[i][j] = 1;
  rep (i, 0, n) flg[((1 << i) - 1) << (n - i)] = 1;
  rep (i, 1, m) {
    cin >> u >> v, u = (u + lst) % n, v = (v + lst * 2) % n;
    if (u > v) swap(u, v);
    if (!g[u][v]) {
      cout << lst << "\n";
      continue;
    }
    rep (i, 0, n - 1) g[u][i] = g[v][i] = g[i][u] = g[i][v] = 0;
    rep (i, 0, (1 << n) - 1) {
      if (qry(f[i], u, v)) f[i] ^= (1 << u) | (1 << v);
      rep (j, 0, n - 1) {
        if (j < u) g[j][u] |= qry(f[i], j, u);
        else g[u][j] |= qry(f[i], u, j);
        if (j < v) g[j][v] |= qry(f[i], j, v);
        else g[v][j] |= qry(f[i], v, j);
      }
    }
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    rep (S, 1, (1 << n) - 1) {
      if (flg[f[S]]) {
        rep (i, 0, n - 1) {
          if ((S >> i) & 1) dp[S] += dp[S ^ (1 << i)];
        }
      }
    }
    cout << (lst = dp[(1 << n) - 1]) << "\n";
    
  }
}
int main() {
  i32 T = 1;
//  cin >> T;
  while (T--) sol();
}
```

---

## 作者：赵悦岑 (赞：2)

[My Blog](https://zyc.pond.ink/post/ARC160-solution/)

### 题意

给定一个 $n$，初始有 $n!$ 个 $n$ 的排列 $S_1,S_2,\dots,S_{n!}$。给出 $m$ 次询问，每次两个数 $a$ 和 $b$（$1 \leq a < b \leq n$），对于任意一个序列 $S_i$，如果 $S_{i,a} > S_{i,b}$，那么交换 $S_{i,a}$ 和 $S_{i,b}$，操作结束后输出此时已经排好序的序列个数。强制在线。

### 解法

数据范围 $n \leq 15$，考虑 $2^n$。对于 $x \in [0,n]$，设 $\leq x$ 为 $0$，$> x$ 的为 $1$，我们可以把一个排列 $T$ 转换为 $n+1$ 个 01 串，记为 $t_{T,0 \sim m}$，显然如果这 $n+1$ 个 01 串均有序，那么也排列也有序。显然有 $\text{popcount}(t_{T,i}) = i$（$\text{popcount}(i)$ 表示 $i$ 中 $1$ 的个数），且 $t_{T,i}$ 与 $t_{T,i+1}$ 只有一位从 $0$ 变成了 $1$，本质上变化的这一位就表示这一位上的数是 $i+1$，这意味着一个包含 $n+1$ 个 01 串的合法的 01 串序列 $p$ 可以唯一对应一个排列，其中合法指 $\forall i \in [0,n-1]$，$p_{i}$ 与 $p_{i+1}$ 只有一位不同，且 $p_0 = \{0,0,\dots,0\}$，$p_n = \{1,1,\dots,1\}$。

假设我们已经处理出所有 01 串 $i$ 经过前 $k$ 个操作得到的序列 $f_i$，显然可以得到 01 串 $i$ 是否经过操作后有序，也就是排列转换出来的 01 串能否包含 $i$。我们可以考虑对 01 串序列 $p$ 计数，
设 $dp_i$ 表示确定了 $p$ 前 $\text{popcount}(i)$ 个 01 串，最后一个 01 串为 $i$ 的合法方案数，可以枚举 $p_{i-1}$ 和 $p_i$ 不同的是哪一位来转移，即：$dp_i=\sum\limits_{j \in i}^n dp_{i \oplus 2^j}$。注意去掉不合法的情况，也就是如果 $i$ 操作后不有序，$dp_i = 0$。

现在我们得到了 $O(nm2^n)$ 的算法，还不能通过。由于这个操作是把顺序不对的两个数交换，猜测这会让整体 “变得越来越有序”，使得经过很少的操作所有排列全部有序。我们把操作后交换了至少一对数的操作叫做有效的找错，单独考虑一个排列 $T$，显然只有操作排列中的逆序对才是有效的操作。而交换逆序对中的两个元素是一定会让逆序对个数减少的，所以可以有效操作的数对会越来越少。对于所有排列同理，可以有效操作的数对也单调递减。所以 $m$ 个操作中最多存在 $\frac{n(n-1)}{2}$ 个有效操作，如果我们只关心有效的操作，复杂度就变为 $O(n^32^n)$，可以通过。

用 $g_{i,j}$ 表示操作数对 $(i,j)$ 是否有效。由于操作 $(x,y)$ 只会使得形如 $(x,i)$ 或 $(y,i)$ 的 $g$ 值变化，每次操作只会有 $O(n)$ 个，暴力单次复杂度为 $n2^n$，显然只有有效的操作才会产生更新，所以总复杂度 $O(n^32^n)$，可以通过此题。

### code

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001,M=101;
int n,m,f[N];
ll b[N];
bool g[M][M],h[N];
bool check(int x,int x1,int x2)
{
    return ((x&(1<<(min(x1,x2)-1)))!=0)&&((x&(1<<(max(x1,x2)-1)))==0);
}
ll solve()
{
    for(int i=0;i<=(1<<n)-1;++i) b[i]=0;
    b[0]=1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        if(h[f[i]]==false) continue;
        for(int j=1;j<=n;++j)
        {
            if(i&(1<<(j-1))) continue;
            b[i|(1<<(j-1))]+=b[i];
        }
    }
    return b[(1<<n)-1];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;++i) h[((1<<i)-1)<<(n-i)]=true;
    for(int i=0;i<=(1<<n)-1;++i) f[i]=i;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) g[i][j]=true;
    }
    ll w=1;
    for(int i=1;i<=m;++i)
    {
        int z1,z2;
        scanf("%d%d",&z1,&z2);
        int x=(z1+w)%n+1,y=(z2+w*2)%n+1;
        if(x>y) swap(x,y);
        if(g[x][y]==true)
        {
            for(int j=1;j<=n;++j) g[x][j]=g[j][x]=g[y][j]=g[j][y]=0;
            for(int j=0;j<=(1<<n)-1;++j)
            {
                if(check(f[j],x,y)) f[j]^=(1<<(x-1))^(1<<(y-1));
                for(int k=1;k<=n;++k)
                {
                    if(check(f[j],x,k)) g[x][k]=g[k][x]=true;
                    if(check(f[j],y,k)) g[y][k]=g[k][y]=true;
                }
            }
            w=solve();
        }
        printf("%lld\n",w);
    }
    return 0;
}
```

---

## 作者：small_john (赞：1)

## 思路

首先直接枚举每个排列肯定是不可行的，考虑先降低我们需要维护的序列数量。

对于每个排列 $p$，将其拆分为 $n$ 个 01 序列，第 $i$ 个序列中小于 $i$ 的位置为 $1$，其余为 $0$（比如 $(2,1,3)$ 拆分成 $(0,1,0),(1,1,0),(1,1,1)$），此时每个排列排好序的充要条件为其对应的 01 序列都排好序。

考虑对 01 序列建图，每个 01 序列 $x$ 到 $y$ 有边当且仅当 $y$ 比 $x$ 多一位为 $1$。那么一个排列和图上的路径一一对应，我们就只需要每个点都排好序的路径的个数，可以通过 $O(2^nn)$ 的 DP 轻松解决。

每次修改都重新做一次 DP 的时间复杂度还是太大了，考虑一些剪枝。

定义操作 $(x,y)$ 有效为存在 $a_x>a_y$ 的 01 序列 $a$，我们尝试分析最多有多少次操作时有效的。

初始时每个操作都是有效的，个数为 $\frac{n\times(n-1)}{2}$。每进行一次有效操作 $(x,y)$，那么 $(x,y)$ 一定变为无效操作。而如果存在一个 $(z,x)$ 变为有效操作，那么原来的 $(z,y)$ 一定由有效变为无效。所以有效操作的次数一定单调递减，最多操作 $\frac{n\times(n-1)}{2}$ 次。

那么我们就可以在一个操作有效时才重新进行 DP，问题在于如何维护那些操作是有效的。

而这个是简单的，对每个操作 $(x,y)$ 记录当前那些 01 序列满足 $a_x>a_y$，交换时新增的有效操作一定有一位是 $x,y$，暴力维护一下即可。

时间复杂度 $O(n^32^n)$，轻松通过。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[1<<15],ok[1<<15],f[1<<15]; 
vector<int> vec[15][15];
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i = 0;i<=n;i++) ok[((1<<i)-1)<<(n-i)] = 1;
	for(int z = 0;z<(1<<n);z++)
	{
		a[z] = z;
		for(int i = 0;i<n;i++)
			if((z>>i)&1)
				for(int j = i+1;j<n;j++)
					if(((z>>j)&1)==0) vec[i][j].push_back(z);		
	}
	int las = 1;
	while(m--)
	{
		int x,y;
		cin>>x>>y;
		x = (x+las)%n+1;
		y = (y+2*las)%n+1; 
		if(x>y) swap(x,y);
		x--,y--;
		bool fl = 0;
		for(auto z:vec[x][y])
		{
			if(((a[z]>>x)&1)&&((a[z]>>y)&1)==0)
			{
				a[z]-=(1<<x);
				a[z]+=(1<<y);
				if(ok[a[z]]) fl = 1;
				else
				{
					for(int i = 0;i<x;i++)
						if(((a[z]>>i)&1)) vec[i][x].push_back(z);
					for(int i = y+1;i<n;i++)
						if(((a[z]>>i)&1)==0) vec[y][i].push_back(z);
				}
			}
		}
		vec[x][y].clear();
		if(fl)
		{
			f[0] = 1;
			for(int z = 1;z<(1<<n);z++)
			{
				f[z] = 0;
				if(!ok[a[z]]) continue;
				for(int i = 0;i<n;i++)
					if((z>>i)&1) f[z]+=f[z^(1<<i)];
			}
			las = f[(1<<n)-1];
		}
		cout<<las<<'\n';
	}
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [AT_arc160_f](https://www.luogu.com.cn/problem/AT_arc160_f)     

这为啥 *3200 啊，有点简单了。       

考虑如何刻画一个排列 $p$ 是有序的。给出 $x$ 从 $0$ 到 $n$，然后记 $b_i=p_i> x$，这是若干个成子集关系的 01 序列，并且后一项 1 的个数比前一项多 1。    

对于 01 序列，这样的操作是好维护的。总共有 $2^n$ 种不同的 01 序列，对每个对 $(i,j)$ 维护一个队列记录有多少 01 序列 a 满足 $a_i=1,a_j=0$，然后进行一次操作就把对应的队列里的 01 序列修改，然后每个序列新增 $O(n)$ 个可操作对。由于操作一次逆序对数至少减少 1，所以这样的复杂度是 $O(2^n\times n^3)$ 的。      

维护完了 01 序列，考虑其如何在排列上计数。dp 记录从当前集合出发，每次加一个 1，有多少种方式加到全 1，总状态数 $2^n$。一个排列合法的条件是其对应的所有 01 序列均合法，一个 01 序列合法后，我们将其看成将其激活，每激活一个 01 序列，其子集的 dp 值都会改变，一次转移是 $O(n)$ 的，总复杂度 $O(3^n\times n+2^n\times n^3)$。     

代码：     


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9,f[(1<<16)],zt[(1<<16)],gg[53];
queue<int>q[15][15];
ll dp[(1<<16)];
int stk[(1<<17)],tots;
void upd(int X){
	if(!f[X])return;
	dp[X]=0;
	for(int i=0;i<n;i++)if(!((X>>i)&1))dp[X]=dp[X]+dp[X+(1<<i)];
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<(1<<n);i++){
		zt[i]=i;
		for(int j=0;j<n;j++){
			if(!((i>>j)&1))continue;
			for(int u=j+1;u<n;u++){
				if((i>>u)&1)continue;
				q[j][u].push(i);
			}
		}
	}
	for(int i=0;i<=n;i++)gg[i]=(((1<<i)-1)<<(n-i));
	for(int i=0;i<=n;i++)f[gg[i]]=dp[gg[i]]=1;
	while(m--){
		cin>>k1>>k2;
		k1=((k1+(dp[0]%n))%n);
		k2=((k2+(dp[0]%n)*2)%n);
		if(k1>k2)swap(k1,k2);
		tots=0;
		while(!q[k1][k2].empty()){
			stk[++tots]=q[k1][k2].front();
			q[k1][k2].pop();
		}
		for(int i=1;i<=tots;i++){
			if(((zt[stk[i]]>>k1)&1)&&(!((zt[stk[i]]>>k2)&1))){
				zt[stk[i]]+=(1<<k2)-(1<<k1);
				for(int j=k2+1;j<n;j++){
					if(!((zt[stk[i]]>>j)&1))q[k2][j].push(stk[i]);
				}
				for(int j=0;j<k1;j++){
					if((zt[stk[i]]>>j)&1)q[j][k1].push(stk[i]);
				}
				if(zt[stk[i]]==gg[__builtin_popcount(stk[i])]){
					f[stk[i]]=1;
					for(int j=stk[i];;j=((j-1)&stk[i])){
						upd(j);
						if(!j)break;
					}
				}
			}
		}
		cout<<dp[0]<<'\n';
	}
	return 0;
}
```

---

