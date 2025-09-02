# [ARC169A] Please Sign

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc169/tasks/arc169_a

長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $，および長さ $ N-1 $ の整数列 $ P=(P_2,\cdots,P_N) $ が与えられます． $ P $ の添字が $ 2 $ から始まることに注意してください． また，$ 1\ \leq\ P_i\ <\ i $ が保証されます．

あなたは今から以下の操作を $ 10^{100} $ 回繰り返します．

- 各 $ i=2,\cdots,N $ について，この順に，$ A_{P_i} $ の値を $ A_{P_i}+A_{i} $ で置き換える．
 
すべての操作が終了したときの $ A_1 $ が 正, 負, $ 0 $ のいずれになるかを求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 250000 $
- $ -10^9\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ P_i\ <\ i $
- 入力される値はすべて整数．
 
### Sample Explanation 1

最初の数回の操作の結果を以下に示します． - $ 1 $ 回目の操作 - 操作前: $ A=(1,-2,3,-4) $ - $ i=2 $ について処理: $ A_1 $ の値を $ A_1+A_2=1+(-2)=-1 $ で置き換える． - $ i=3 $ について処理: $ A_2 $ の値を $ A_2+A_3=-2+3=1 $ で置き換える． - $ i=4 $ について処理: $ A_3 $ の値を $ A_3+A_4=3+(-4)=-1 $ で置き換える． - 操作後: $ A=(-1,1,-1,-4) $ - $ 2 $ 回目の操作後，$ A=(0,0,-5,-4) $ となる． - $ 3 $ 回目の操作後，$ A=(0,-5,-9,-4) $ となる． - $ 4 $ 回目の操作後，$ A=(-5,-14,-13,-4) $ となる． - $ \vdots $ 操作を $ 10^{100} $ 回行うと，$ A_1 $ は負になります． よって `-` を出力すべきです．

## 样例 #1

### 输入

```
4
1 -2 3 -4
1 2 3```

### 输出

```
-```

## 样例 #2

### 输入

```
3
0 1 -1
1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
5
1 -1 1 -1 1
1 1 2 2```

### 输出

```
+```

## 样例 #4

### 输入

```
20
568273618 939017124 -32990462 -906026662 403558381 -811698210 56805591 0 436005733 -303345804 96409976 179069924 0 0 0 -626752087 569946496 0 0 0
1 1 1 4 4 6 7 2 2 3 3 8 13 14 9 9 15 18 19```

### 输出

```
+```

# 题解

## 作者：Guizy (赞：7)

## 思路

不难想到，因为次数有 $10^{100}$，深度越深，对答案的影响越大。因为深度深的会改变深度浅的，深度浅的又会改变深度更浅的，所以我们只需要统计出每个深度的点的权值和，在按深度从深到浅，看看答案的正负，如果是正的，就输出 `+`，负的就输出 `-`，否则继续枚举。如果枚举还不能得到答案，就证明所有的点都是 `0`，输出 `0`。

## 实现

```cpp
#include<bits/stdc++.h>
#define Max 250010
#define inf 1000000000
using namespace std;

long long n,a[Max],p[Max];
long long sum[Max],dis[Max];
int flag;

signed main(){
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		dis[i]=inf;//初始化
	}
	dis[1]=0;
	for(int i=2;i<=n;i++){
		scanf("%lld",&p[i]);
		dis[p[i]]=i+1;//预处理深度
	}
	
	for(int i=1;i<=n;i++)
		if(dis[i]<inf)
			sum[dis[i]]+=a[i];
		
	for(int i=n;~i;i--){
		if(sum[i]>0) return printf("+"),0;
		if(sum[i]<0) return printf("-"),0;
	}
	printf("0");
	
	return 0;
}
```

---

## 作者：mgcjade (赞：4)

 _~~关于我在赛场上一题都没有切，后面自己推出来正解这件事\~~~_ 
 

## 题面翻译

给定一个长度为 $N$ 的整数序列 $A=( A_1, A_2,\cdots,A_N)$ 和另一个长度为 $N-1$ 的整数序列 $P=(P_2,\cdots,P_N)$。注意 $P$ 的索引从 $2$ 开始。对于每个 $i$，保证 $1 \leq P_i < i$。

现在您将重复下面的操作 $10^{100}$ 次。
- 为每一个 $i=2,\cdots,N$ 的值，$A_{P_i}=A_{P_i}+A_i$

确定当所有操作完成时，$A_1$ 是正的、负的还是零。


## 题目想让你求什么

给你一棵以 $1$ 为根的树，$i$ 号点的父亲是 $P_i$，点权是 $A_i$，重复 $10^{100}$ 次，从 $1\sim N$ 分别将 $i$ 号点的点权加进其父亲的点权。请判断 $1$ 号点点权的正负性。

## 题目思路

我们发现，深度最深的点起决定性作用，因为无限次之后如果深度最深的点是负的，那么肯定能把深度较浅的点减成负的。如果深度最深的点是正的，那么肯定能把深度较浅的点加成正的。

所以，我们可以想到使用拓扑进行图的分层，求出每一层的和，在从下向上比较，当最底下一层的和为 $0$ 时，该层对答案无影响，再看上面一层（可以把 $1$ 号节点设为根）。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void read(ll &s)
{
	s = 0;
	char ch = getchar(), lst = ' ' ;
	while (ch < '0' || ch > '9')
		lst = ch, ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	if (lst == '-')
		s = -s;
}

ll n;
ll a[250005];
struct node
{
	ll to, nxt;
};
node edge[250005];
ll hd[250005], cnt;
ll flr, sum[250005];
ll h, r, q[250005];
void add(ll x, ll y)
{
	cnt++;
	edge[cnt].to = y;
	edge[cnt].nxt = hd[x];
	hd[x] = cnt;
}

int main()
{
	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 2; i <= n; i++)
	{
		read(a[0]);
		add(a[0], i);
	}
	q[r++] = 1;
	sum[++flr] = a[1];
	while (h < r)
	{
		flr++;
		ll t = r;
		while (h < t)
		{
			for (int i = hd[q[h]]; i; i = edge[i].nxt)
				q[r++] = edge[i].to;
			sum[flr] += a[q[h]];
			h++;
		}
	}
	int flag = 0;
	for (int i = flr; i; i--)
		if (sum[i] > 0)
		{
			flag = 1;
			break;
		}
		else if (sum[i] < 0)
		{
			flag = -1;
			break;
		}
	if (flag > 0)
		printf("+");
	else if (flag == 0)
		printf("0");
	else
		printf("-");
	return 0;
}
```

## 尾声

感谢以为大佬告诉我这题可以用拓扑的思想，同时感谢[martian148](https://www.cnblogs.com/martian148/p/17892223.html)大佬为本篇题解提供写法上的参考。

---

## 作者：fcy20180201 (赞：4)

## 题意
给定长度为 $N$ 的序列 $A$ 和长度为 $N-1$ 的序列 $P$。$P$ 从 $2$ 开始编号。现在执行 $10^{100}$ 次操作，每次操作对于 $2\le i \le N$ **依次**将 $A_{p_i}$ 加上 $A_i$。问最后 $A_1$ 的正负情况。

## 思路
显然是计算数组中的每一项对 $A_1$ 的贡献和的正负（~~废话~~）。首先我们要清楚每一项到第几次操作才会对 $A_1$ 产生贡献。这个显然用拓扑排序解决。

接下来，我们先判断 $A_1$ 是否为 $0$。但不难发现，每一项对 $A_1$ 产生贡献后，产生的贡献增长快，总量越大，$A$ 中任意两项的最大差 $2\times 10^9$ 在其面前可以说微不足道。因此，开始对 $A_1$ 产生贡献时间不同的几项是几乎不可能抵消的，所以我们只需要看对开始 $A_1$ 产生贡献时间相同的项是否能完全抵消即可。

如果 $A_1$ 不为 $0$，显然对 $A_1$ 产生贡献最大的是贡献最晚的几项（因为贡献增长很快），所以只要看这几项的和的正负就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,p[250005],dis[250005];
ll a[250005],sum[250005];
vector<int>con[250005];
queue<int>q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=2;i<=n;i++)scanf("%d",&p[i]),dis[i]=1e9,con[p[i]].push_back(i);
	q.push(1);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int y:con[x])dis[y]=dis[x]+1,q.push(y);
	}//拓扑排序
	bool flag=true;
	for(int i=1;i<=n;i++)if(dis[i]<1e9)sum[dis[i]]+=a[i];//记录距离相等的项的值和
	for(int i=0;i<=n;i++)
		if(sum[i]){//判断是否抵消
			flag=false;
			break;
		}
	if(flag){
		putchar('0');
		return 0;
	}
	for(int i=n;~i;i--)
		if(sum[i]){//找贡献最晚的几项
			putchar(sum[i]>0?'+':'-');
			break;
		}
	return 0;
}
```

---

## 作者：Hope888 (赞：3)

# 思路
可以发现 $a_1$ 的变化是由 $p_i=1$ 的 $i$ 造成的，而这些 $i$ 又是由 $p_{p_i}=1$ 造成的，再加上 $p_i<i$ 的条件，这些关系显然构成一个以 $1$ 为根的**树**。

因为变化次数可以看作无限，显然只需**模拟一次**观察它与原始数的关系即可。

由因为可以构成一个树的结构，树的每一**层**都会影响到它们的父亲，就这样一直到根节点 $1$，所以**分别**只需计算出每层的变化，判断后就可以得到答案，因为底层的数不受其他数影响，所以**从最低层开始判断**。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[250005],b[250005],p[250005],num[250005],num2[250005],maxn;
vector<int>v[250005];
void dfs(int now,int deep)
{
	maxn=max(maxn,deep);
	num[deep]+=b[now];//变化一次后的
	num2[deep]+=a[now];//原始的
	for(int i=0;i<v[now].size();i++)dfs(v[now][i],deep+1);
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	for(int i=2;i<=n;i++)
	{
		cin>>p[i];
		v[p[i]].push_back(i);
	}
	for(int i=2;i<=n;i++)b[p[i]]+=b[i];
	dfs(1,1);
	for(int i=maxn;i>=1;i--)
	{
		if(num[i]<num2[i])
		{
			cout<<"-";
			return 0;
		}
		if(num[i]>num2[i])
		{
			cout<<"+";
			return 0;
		}
	}
	if(num[1]>0)cout<<"+";
	else if(num[1]<0)cout<<"-";
	else cout<<0;
}
```

---

## 作者：2huk (赞：2)

## Description

给定一个长度为 $n$ 的序列 $(a_1, a_2, \dots , a_n)$ 和长度为 $n - 1$ 的序列 $(p_2, p_3, \dots ,p_n)$。你需要以下操作 $10^{100}$ 次：

- 对于每个 $i \in [2, n]$，依次修改 $a_{p_i} \gets a_{p_i} + a_i$。

求最终 $a_1$ 的正负。

$2 \le n \le 2.5 \times 10^5$，$-10^0 \le a_i \le 10^9$，$1 \le p_i < i$。

## Solution

可以发现，如果把 $p_i \to i$ 连边，那么这张图会形成一颗树。显然共有 $n - 1$ 条边且无环。

例如样例三的树：

![](https://cdn.luogu.com.cn/upload/image_hosting/xuusia5r.png)

可以发现，$10^{100}$ 次操作后，$a_4$ 和 $a_5$ 对 $a_1$ 的影响最大，因为 $a_4, a_5$ 是这颗树中**深度最大**的点。那么，如果 $a_4 + a_5$ 是正数，那么由于操作次数过多，那么最终 $a_1$ 也将变为正数；如果 $a_4 + a_5$ 是负数，那么由于操作次数过多，那么最终 $a_1$ 也将变为负数。

问题是当 $a_4 + a_5 = 0$ 时，树上的这一层相当于对 $a_1$ 没有任何影响。那么我们就找到**深度第二大**的点，也就是 $a_2, a_3$，仍然根据上面的计算方式，若 $a_2 + a_3 > 0$ 则 $a_1$ 为正，若 $a_2 + a_3 < 0$ 则 $a_1$ 为负。否则找深度第三大的点，以此类推。

于是就只需要预处理出树上每个节点的深度，和每个深度上所有节点之和即可。

## Code

[Submission #48325755 - estie Programming Contest 2023 (AtCoder Regular Contest 169)](https://atcoder.jp/contests/arc169/submissions/48325755)

---

## 作者：incra (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc169_a)
### 题解
考虑将同一层的点缩成一个点，毕竟总要往上加到根。

分析一下题目的操作，就是把每一个节点的值加到父节点上，并且**从上到下**执行。

设第 $1$ 层的节点（即根）和为 $a_1$，第 $\textbf{3}$ 层的节点和为 $a_2$，一次类推。考虑每一次操作后每一个结点的数：

第 $1$ 次：$a_1 + a_2,a_2+a_3,\dots$。

第 $2$ 次：$a_1 + 2a_2+a_3,a_2+2a_3+a_4,\dots$。

第 $3$ 次：$a_1 + 3a_2+3a_3+a_4,a_2+3a_3 + 3a_4 + a_5,\dots$。

第 $4$ 次：$a_1 + 4a_2+6a_3+4a_4+a_5,a_2+4a_3 + 6a_4 + 4a_5+a_6,\dots$。

令 $t=10^{100}$，不难想到，所有操作进行完以后，根节点的值 $=C_t^0a_1+C_t^1a_2+\dots+C_t^ da_d$，其中 $d$ 为树的深度。

显然 $C_t^d>>C_t^{d-1}>>\dots>>C_t^0$，故序列 $\{a\}$ 中，最后一个非零的数的符号即为根节点的数的符号，若序列 $\{a\}$ 中的数都是 $0$，那么根节点的数也就是 $0$。

~~最恶心的题目力。~~
### 代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
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
const int N = 250010;
int n;
int a[N];
vector <int> g[N];
int dep[N];
void DFS (int u) {
	for (int v : g[u]) {
		dep[v] = dep[u] + 1;
		DFS (v);
	}
}
LL s[N];
int main () {
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i];
	for (int i = 2;i <= n;i++) {
		int p;
		cin >> p;
		g[p].pb (i);
	}
	dep[1] = 1;
	DFS (1);
	for (int i = 1;i <= n;i++) s[dep[i]] += a[i];
	int ans = n;
	while (ans > 1 && !s[ans]) ans--;
	if (s[ans] > 0) puts ("+");
	else if (!s[ans]) puts ("0");
	else puts ("-");
	return 0;
}
```

---

## 作者：ZnPdCo (赞：1)

发现把赋值的 $P_i$ 与 $i$ 连边，就会形成一个以 $1$ 为根节点的树。也就是每个儿子会把值赋给父亲。

其实发现一个父亲就相当于加上它所有儿子的值之和，第 $d$ 层的父亲的和相当于加上深度为 $d+1$ 的儿子的所有值之和。

我们把第 $d$ 层的所有 $A_i$ 累加到 $f_d$ 中。原本的让 $A_{P_i}$ 累加 $A_i$ 的值就会变成让 $f_{d-1}$ 累加入 $d_i$ 的值。

容易发现循环执行 $10^{100}$ 次赋值其实只与一项有关，就像滚雪球一样，如果最关键的那一项能使前面的数不断变大，那么结果是正数，如果最关键的那一项能使前面的数不断变小，结果就是负数。

那么怎么找到这一项呢？其实这就是 $f$ 最后一个有值的项。

那么我们只需要深搜一遍，然后判断正负情况即可。

```c++
#include <cstdio>
#define ll long long
#define N 250010
ll n, a[N], p[N];

ll head[N];
ll nxt[N];
ll to[N], cnt;

ll dep[N];
ll f[N];

void addEdge(ll u, ll v) {
	++cnt;
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
void dfs(ll u) {
	for(ll i = head[u]; i; i = nxt[i]) {
		ll v = to[i];
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}
int main() {
	scanf("%lld", &n);
	for(ll i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	for(ll i = 2; i <= n; i++) {
		scanf("%lld", &p[i]);
		addEdge(p[i], i);
	}
	dfs(1);
	for(ll i = 1; i <= n; i++) f[dep[i]] += a[i];
	for(ll i = n; i >= 1; i--) {
		if(f[i]) {
			if(f[i] > 0 && a[1] > 0) printf("+");
			if(f[i] == 0 && a[1] > 0) printf("+");
			if(f[i] < 0 && a[1] > 0) printf("-");
			if(f[i] > 0 && a[1] == 0) printf("+");
			if(f[i] == 0 && a[1] == 0) printf("0");
			if(f[i] < 0 && a[1] == 0) printf("-");
			if(f[i] > 0 && a[1] < 0) printf("+");
			if(f[i] == 0 && a[1] < 0) printf("-");
			if(f[i] < 0 && a[1] < 0) printf("-");
			return 0;
		}
	}
	if(a[1] > 0) printf("+");
	if(a[1] == 0) printf("0");
	if(a[1] < 0) printf("-");
}
```





---

## 作者：DDF_ (赞：0)

## 题面

有一棵以 $1$ 为根，$n$ 个点的树，每次操作让一个节点的点权加上它儿子的点权，重复 $10^{100}$ 次操作，然后判断最终根节点点权正负性。

## 思路

因为每一个点的点权都会加上它儿子的点权，如果它儿子点权之和为正，那么这个点的点权就有一个往上加的趋势，反之则有一个往下减的趋势。

所以最后它的点权正负性是由它儿子点权之和的正负性来决定的。

同理，如果一个深度的点权之和为正，那么上一个深度的点权之和就有一个往上加的趋势，反之有一个往下减的趋势，然后又往上一个深度加，最终影响到根节点。

由此可得，深度越大的点对答案贡献值越大。

所以可以从深度最大往上枚举，如果此深度点权和不为 $0$，则最终根节点正负性就被此深度点权和正负性直接影响，而如果所有深度点权和都为 $0$，那么根节点最终也为 $0$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,a[250002],fa[250002],dep[250002];
ll sum[250002];
vector<int> son[250002];
void dfs(int x) {
	dep[x]=dep[fa[x]]+1,sum[dep[x]]+=a[x],m=max(m,dep[x]); //计算这一深度的点权之和
	for(int i=0;i<son[x].size();i++) dfs(son[x][i]);
	return;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=2;i<=n;i++) scanf("%d",&fa[i]),son[fa[i]].push_back(i);
	dfs(1);
	for(int i=m;i;i--) { //从深度最大往上枚举，如果此深度点权和不为0，就会影响根节点
		if(sum[i]>0) return puts("+"),0;
		if(sum[i]<0) return puts("-"),0;
	}
	return puts("0"),0; //如果所有深度点权和都为0，那么根节点最终也为0
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

由于每次把子节点的权值加到父节点中，深度越深影响越大。

将 $1$ 号节点视作父节点，不难发现，同一深度的节点对其贡献度相等，都为 $1\times now\ val$。

因为 $10^{100}$ 极大，所以统计每层权值和，从深往浅扫。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,val[250010],dep[250010],sum[250010],mx;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&val[i]);
	dep[1]=1;
	sum[1]=val[1];
	for(int i=2;i<=n;i++){
		int fa;
		scanf("%lld",&fa);
		dep[i]=dep[fa]+1;
		sum[dep[i]]+=val[i];
		mx=max(mx,dep[i]);
	}
	for(int i=mx;i>=1;i--){
		if(sum[i]<0){
			puts("-");
			return 0;
		}
		if(sum[i]>0){
			puts("+");
			return 0;
		}
	}
	puts("0");
	return 0; 
} 
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc169_a)

非常简单，但我吃了 $2$ 罚时。

其实题目翻译已经给出了这道题一半的做法了，否则得多想一步。

可以利用杨辉三角来证明，经过 $10^{100}$ 次操作后，一定是深度最深的节点对答案有影响，答案。如果深度最深的节点有相同的，那么就把它们的值相加，因为对于节点 $1$ 的贡献当中它们系数相同。

不过如果把深度最深的节点的和求出来后为 $0$，那么就说明这一层节点的贡献全废了，就得再去找上一层，如果上一层的和还是 $0$，那么就再找上一层的上一层，直到节点 $1$。

如果节点 $1$ 还是为 $0$，那么就输出 `0`。否则如果深度最深且产生有效贡献的那一层的节点的和为正数，则说明它能带动节点 $1$ 最后变为正数，输出 `+`，否则输出 `-`。

我使用 dfs 遍历树并用数组来统计每一层节点的和的。

# CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[250010];
long long a[250010];
vector<int> g[250010];
long long fc[250010]={0};
int zcm=0;
inline void dfs(int k,int cd)
{
	fc[cd]+=a[k],zcm=max(zcm,cd);
	if(!g[k].size()) return;
	for(register int i=0;i<g[k].size();i++)
	{
		int x=g[k][i];
		dfs(x,cd+1);
	}
}
int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(register int i=2;i<=n;i++) scanf("%d",&p[i]),g[p[i]].push_back(i);
    dfs(1,1);
    for(register int i=zcm;i>=1;i--)
	{
		if(fc[i]>0){printf("+");return 0;}
		if(fc[i]<0){printf("-");return 0;}
	}
	printf("0");
	return 0;
}
```

---

## 作者：N_Position (赞：0)

# AT_arc169_a 题解

## 题目大意

给定一个长度为 $N$ 的数列 $A=(A_1,\dots,A_N)$ 和长度为 $N-1$ 的数列 $P=(P2,\dots,P_N)$，每次操作，将 $A_{P_i}$ 的值修改为 $A_{P_i} + A_i$。

问 $10^{100}$ 次操作后 $A_1$ 的正负。

$1\leq P_i\leq i-1$。

## 题目分析

数据范围中，最有意思的是 $1\leq P_i\leq i-1$。

我们可以发现，操作恰好为一棵树。

我们可以先分析为一条链的情况（例如样例 1），进而推广到树。我们可以统计一下 $A_1$ 这个数在原来的基础上，又加了几个数。

下表中每个值 $cnt_{i,j}$ 表示每个数 $A_i$ 增加其他的数的个数。所以此时 $A_i$ 的值为 $A_i=\sum A_{0j}\times cnt_{i,j}$。

初始值：

|      | 1    | 2    | 3    | 4    | 5    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 1    | 1    | 0    | 0    | 0    | 0    |
| 2    | 0    | 1    | 0    | 0    | 0    |
| 3    | 0    | 0    | 1    | 0    | 0    |
| 4    | 0    | 0    | 0    | 1    | 0    |
| 5    | 0    | 0    | 0    | 0    | 1    |

第一次操作：

|      | 1    | 2    | 3    | 4    | 5    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 1    | 1    | 1    | 0    | 0    | 0    |
| 2    | 0    | 1    | 1    | 0    | 0    |
| 3    | 0    | 0    | 1    | 1    | 0    |
| 4    | 0    | 0    | 0    | 1    | 1    |
| 5    | 0    | 0    | 0    | 0    | 1    |

第二次操作：

|      | 1    | 2    | 3    | 4    | 5    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 1    | 1    | 2    | 1    | 0    | 0    |
| 2    | 0    | 1    | 2    | 1    | 0    |
| 3    | 0    | 0    | 1    | 2    | 1    |
| 4    | 0    | 0    | 0    | 1    | 2    |
| 5    | 0    | 0    | 0    | 0    | 1    |

第三次操作：

|      | 1    | 2    | 3    | 4    | 5    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 1    | 1    | 3    | 3    | 1    | 0    |
| 2    | 0    | 1    | 3    | 3    | 1    |
| 3    | 0    | 0    | 1    | 3    | 3    |
| 4    | 0    | 0    | 0    | 1    | 3    |
| 5    | 0    | 0    | 0    | 0    | 1    |

第四次操作：

|      | 1    | 2    | 3    | 4    | 5    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 1    | 1    | 4    | 6    | 4    | 1    |
| 2    | 0    | 1    | 4    | 6    | 4    |
| 3    | 0    | 0    | 1    | 4    | 6    |
| 4    | 0    | 0    | 0    | 1    | 4    |
| 5    | 0    | 0    | 0    | 0    | 1    |

我们单独将 $A_1$ 的变化拿出来，纵向表示操作次数：

|      | 1    | 2    | 3    | 4    | 5    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 1    | 1    | 0    | 0    | 0    | 0    |
| 2    | 1    | 1    | 0    | 0    | 0    |
| 3    | 1    | 2    | 1    | 0    | 0    |
| 4    | 1    | 3    | 3    | 1    | 0    |
| 5    | 1    | 4    | 6    | 4    | 1    |

次数恰好是杨辉三角，所有当次数达到 $10^{100}$ 次时，每一层的深度越深，加的次数越多，而且要多很多很多。

知道这个性质后，我们就已将将问题转化为了求这棵树深度最深的一层之和的正负，若这一层为零，则再看比这一层更浅的一层的和。

一遍深搜求深度，再在 $O(N)$ 时间复杂度下统计一下每一层之和，时间复杂度 $O(N)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5+5;
int a[N],p[N],dep[N],max_d = -1;
ll sum[N];
vector<int> v[N];
void add(int x,int y){
	v[x].push_back(y);
}
void dfs(int p,int d){
	dep[p] = d;
	max_d = max(max_d,d);
	for(int i=0;i<v[p].size();i++){
		dfs(v[p][i],d+1);
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=2;i<=n;i++){
		scanf("%d",&p[i]);
		// p[i] <- i;
		add(p[i],i);
	}
	dfs(1,1);
	for(int i=1;i<=n;i++){
		sum[dep[i]] += a[i];
	}
	for(int i=max_d;i>=1;i--){
		if(sum[i] > 0ll){
			puts("+");
			return 0;
		}else if(sum[i] < 0ll){
			puts("-");
			return 0;
		}
	}
	puts("0");
}
```



---

## 作者：MoyunAllgorithm (赞：0)

**题意**

在数列 $a$ 中，对于每个 $i \in [2,N]$，有 $p_i \in [1,i)$。执行 $10^{100}$ 次操作：

- 对于每个 $i$，$a_{p_i}:=a_{p_i}+a_i$。

求最后 $a_1$ 的正负性。

**思路**

容易想到建树，$p_i$ 是 $i$ 的父亲。

如果这是一条链那是好做的：答案只跟 $a_N$ 的正负性有关。因为，这种不断加后面的数的操作，会导致最后一项的贡献就像滚雪球一般快速加大。事实上，经过组合数学推导，你会发现最后的 $a_1$ 是

$1 \times a_1 + C_{10^{100}}^{1} \times a_2 + C_{10^{100}}^{2} \times a_3 + \cdots$

这时显然 $a_N$ 的系数远远大于前面的任何系数。

但是如果 $a_N=0$ 时就不是了，这时 $a_{N-1}$ 才是贡献最大的。准确地说，**最深的非 $0$ 位置** 的贡献是最大的。不妨设该位置的 $a$ 为 $A$。那么：

- 当 $A>0$，则答案 $>0$；

- 当 $A<0$，则答案 $<0$。

- 否则答案为 $a_1$ 的正负性。

不过只要 $a$ 不是全 $0$ 序列似乎第三条不会出现。

这时我们发现：**当 $a$ 是一棵普通树时，所有深度相同的结点可以被合并成同一个结点！** 因为这里的操作是加法操作，而加法具有结合律，不会影响结果。那么我们把树转化成了链。

于是套用上述分讨即可。需要注意的是，此时 $A$ 可能等于 $0$。例如在样例中，最深的两个节点的值为 $1$ 和 $-1$，那转化为链后该点的值为 $0$，但由于在原本的树中这两个点依旧造成贡献，因此应当把 $A$ 赋值为 $0$。

[code](https://atcoder.jp/contests/arc169/submissions/48315392)

---

## 作者：0x3F (赞：0)

转化后的题意：给一棵带点权的有根树，进行 $10^{100}$ 次下列操作：

> 自上而下，将每一个点的权值加上其所有儿子的权值。

问树根在操作以后的权值的符号。

发现每一个点的贡献是独立的，考虑分别计算。我们记点 $i$ 的 $k$ 级祖先为 $f_k$，那么对于点 $i$，我们不妨设初始时 $A_i=1$，其他 $A$ 的值均为 $0$，那么：

0. 初始时，$A_{i}=1$。

1. 第一次操作后，$A_{i}=1,A_{f_1}=1$。

2. 第二次操作后，$A_{i}=1,A_{f_1}=2,A_{f_2}=1$。

3. 第三次操作后，$A_{i}=1,A_{f_1}=3,A_{f_2}=3,A_{f_3}=1$。

4. 第四次操作后，$A_{i}=1,A_{f_1}=4,A_{f_2}=6,A_{f_3}=4,A_{f_4}=1$。

容易证明，第 $T$ 次操作以后，$A_{f_{k}}$ 的值为 $\binom{T}{k}$。

因此，一个深度为 $d$ 的节点对答案的贡献为 $\binom{10^{100}}{d}$。

我们发现，数列 $\binom{10^{100}}{d}$ 以非常快的速度增长，相邻两项比值远大于 $\sum \lvert A_{i}\rvert$。

因此，只需要统计每一个深度的数之和，并且从大到小枚举，如果先出现正数，那么答案就是 `+`，如果先出现负数，那么答案就是 `-`，如果所有数均为 $0$，那么答案就是 `0`。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 2.5e5 + 10;
int n, a[_], p[_], d[_];
long long s[_];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 2; i <= n; i++) {
		cin >> p[i];
	}
	d[1] = 1;
	for (int i = 2; i <= n; i++) {
		d[i] = d[p[i]] + 1;
	}
	for (int i = 1; i <= n; i++) {
		s[d[i]] += a[i];
	}
	for (int i = n; i >= 1; i--) {
		if (s[i]) {
			if (s[i] > 0) {
				cout << "+" << endl;
			} else {
				cout << "-" << endl;
			}
			return 0;
		}
	}
	cout << "0" << endl;
	return 0;
}
```

---

## 作者：Iceturky (赞：0)

赛场上因为漏了条件没想出来。

观察转移式。

$A_{P_i} \leftarrow A_{P_i}+A_i$ 且 $1 \leq P_i<i$

发现每一个数只会向下标靠前的唯一一个数转移。

整体构成了一个 $1$ 为根，儿子指向父亲，**深度浅的节点先转移**的转移树。

发现对于 $u$ 的儿子 $v$，$v$ 自身值（即 $A_v$）每一轮对 $u$ 的贡献的权重只有 $1$，也即每轮操作只会对 $u$ 做 $A_v \times 1$ 的贡献。

设 $v$ 所有儿子每一轮操作对 $v$ 的贡献为 $w$，则发现 $w$ 对 $u$ 做贡献的权重是远大于 $v$ 的。（也即通过 $v$ 间接对 $u$ 做的贡献）

（第一轮操作对 $u$ 无贡献，第二轮贡献权重为 $1$，第三轮权重为 $2$，第四轮权重为 $3$，第五轮权重为 $4$，以此类推）

对 $u$ 的正负性进行探讨，发现其在无限次操作后与 $w$ 的正负性一致。（若无比 $w$ 这一层更深的层）（若 $w$ 为 $0$ 则相当于不存在这一层）

思考若 $v$ 子树内有更深的孩子的话，则此孩子为权重最高的节点。

发现在这一棵转移树上，深度越大的点所占的权重越大，深度相同的点所占权重相同。

因此只需要考虑深度最大的点的权值总和的正负性即可，若为 $0$ 则继续往上找次大。

（若是注意到 $P_i<i$ 不会产生环且转移从下标小的开始就一眼了）

代码很好实现。

```cpp
const int N=2.5e5+5;

int a[N],d[N];//分别表示点权与深度

ll s[N];//表示此深度的点权和

signed main()
{
	int n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	d[1]=1;
	s[1]=a[1];
	for(int i=2;i<=n;i++){
		int x=read();//即为P_i
		d[i]=d[x]+1;//因 P_i<i，所以x的深度一定先被求出
		s[d[i]]+=a[i];//求层上和
	}
	for(int i=n;i>=1;i--)//深度大对1的贡献权重高
		if(s[i]!=0){
			pc(s[i]>0?'+':'-'),pc('\n');
			return 0;
		}
	pc('0'),pc('\n');//全都为0则为0
	return 0;
}
```

---

## 作者：CuteChat (赞：0)

## 题意

给你一棵以 $1$ 为根的树，$i$ 号点的父亲是 $P_i$，点权是 $A_i$，重复 $10^{100}$ 次，从 $1\sim N$ 分别将 $i$ 号点的点权加进其父亲的点权。请判断 $1$ 号点点权的正负性。


## 解题

对于这道题，我们可以想一想这个重复 $10^{100}$ 次的操作是在干什么。

让我们以一条链来举例子，例如 $N=5$，$A_n=1$，其他点的点权都是 $0$，也就是对于以下的输入数据：

```sample
5
0 0 0 0 1
2 3 4 5
```

下面显示的是前几次操作的结果。

- 第一次操作前，$A=(0,0,0,0,1)$。
- 第一次操作后，$A=(0,0,0,1,1)$。
- 第二次操作后，$A=(0,0,1,2,1)$。
- 第三次操作后，$A=(0,1,3,3,1)$。
- 第四次操作后，$A=(1,4,6,4,1)$。
- 第五次操作后，$A=(5,10,10,5,1)$。
- $\vdots$

通过观察，发现这个有点类似杨辉三角，猜测与组合数有关。

但这就是组合数，令 $C_{i,j}$ 表示第 $i$ 次操作第 $j$ 个元素的值，那么 $C_{i,j} = C_{i-1,j} + C_{i-1,j-1}$，符合组合数的递推式。

而把点权转换到 $A_i$ 身上无非就是原来的东西乘上 $A_i$。

那么这个东西就很显然了，如果记 $d_i$ 表示 $i$ 到根所需要经过的边数，那么他对答案的贡献就是 $C_{10^{100}}^{d_i}\times A_i$，所以我们只需要判断 $\displaystyle \sum_{i=1}^{N}C_{10^{100}}^{d_i}\times A_i$ 的正负性即可。

这样我们就得到了一个 $O(N)$ 的算法，但是有 $10^{100}$ 的常数，无法通过此题，考虑优化。

首先，组合数具有对称性，在本题中对称点为 $\frac{10^{100}}{2}$，$[0,\frac{10^{100}}{2}]$ 成递增趋势。而 $d_i$ 一定不会超过 $N$，所以在实际问题中 $d_i$ 越大，对应的组合数越大。

而 $d_i$ 每一次加一，对应的组合数的变化肯定是非常大的，至少是 $10^{100}$，而 $A_i$ 远远达不到这个值。

这说明深度越深的点才是影响答案的关键，一旦不是零，那么不管越浅的点怎么算都不会越过 $0$ 这个分界点。

所以我们深度从大到小枚举，把所有为这个深度的点对应的 $A_i$ 加起来，判断这个数的正负性，如果不是零，那么答案的正负性就是这个数的正负性。如果是零，就继续往上枚举。

直到 $1$ 号节点，还是没有得出答案，则说明答案为 $0$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, fa[250001], d[250001];
long long a[250001], sum;
vector<int> edges[250001], ds[250001];

void dfs(int i) {
	ds[d[i]].push_back(i);
	for (auto j : edges[i]) {
		d[j] = d[i] + 1;
		dfs(j);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	for (int i = 2; i <= n; ++i) {
		scanf("%d", &fa[i]);
		edges[fa[i]].push_back(i);
	} d[1] = 1;
	dfs(1);
	for (int i = 250000; i >= 0; --i) {
		long long sum = 0;
		if (i == 0) {
			return puts("0"), 0;
		}
		for (auto j : ds[i]) {
			sum += a[j];
		}
		if (sum > 0) return puts("+"), 0;
		else if (sum < 0) return puts("-"), 0;
	}
	return 0;
}
```

---

## 作者：Aigony (赞：0)

[更好的阅读体验 qwq](https://www.cnblogs.com/ying-xue/p/arc169.html)

考虑 $i$ 位置上的数，下次它被加到 $P_i$，再下次被加到 $P_{P_i}$，因为这个序列有性质 $P_i<i$，这样加若干轮一定会到达 $1$。  
令所有的 $i$ 向 $P_i$ 连边，则这是一棵以 $1$ 为根的树。

设 $f_i=\sum\limits_{j=1}^n [dep_j=i] a_j$。其中 $dep_1=0$。  
那么 $A_1=f_0$，一次操作相当于令所有 $f_i\gets f_i+f_{i+1}$。

首先如果 $f$ 数组全都是 $0$，$A_1$ 操作很多次后显然还是 $0$。  
考虑 $f$ 最后一个不为 $0$ 的位置的符号，设这个数为 $f_x$。若 $f_x>0$，由于每次令 $f_{x-1}\gets f_{x-1}+f_x$，$f_{x-1}$ 一定会在若干次操作后变为正数。这可以类似地推广到 $f_{x-2},f_{x-3},\dots$。因此操作次数足够多时，有 $f_0>0$，即 $A_1>0$。 

$f_x<0$ 同理。综上，我们得到结论：$A_1$ 最后的符号与 $f$ 数组最后一个不为 $0$ 的位置符号相同。

```cpp
#define int long long
const int N=2.5e5+5,inf=2e9;
int n,a[N],p[N],f[N],dep[N],mx;
vector<int> e[N];
void dfs(int u)
{
    mx=max(mx,dep[u]);
    for(auto v:e[u]) 
    {
        dep[v]=dep[u]+1;
        dfs(v);
    }
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=2;i<=n;i++) p[i]=read(),e[p[i]].push_back(i);
    dfs(1);
    for(int i=2;i<=n;i++) f[dep[i]]+=a[i];
    int flag=0;
    for(int i=n;i;i--)
        if(f[i]) {flag=f[i]>0?1:-1;break;}
    a[1]=flag*inf+a[1];
    if(a[1]>0) cout<<"+";
    else if(a[1]==0) cout<<"0";
    else cout<<"-";
    return 0;
}
```

---

## 作者：roger_yrj (赞：0)

## 题解

我们可以把题目中描述的关系看成一棵根为 $A_1$ 的树。每个时刻，每个点将这个点的父亲加上自己的值。

通过观察发现，其实我们可以把每一层并在一起考虑。反正最后都是到 $A_1$，所以每个点我们只关心深度。

然后，我们发现最深层的点的值都是不变的，因为他们没有儿子。所以，只要最深层不是零，那么通过无限的时间，一定能决定次深层的正负。以此类推，只要最深层不是零，那么一定能决定根，也就是 $A_1$ 的正负。

如果最深层是零，那么就忽略最深层，考虑次深层，以此类推。

时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=250010; 
int n,a[N];
ll sum[N];
vector<int>son[N];
void dfs(int x,int y){
	sum[y]+=a[x];
	for(int v:son[x])dfs(v,y+1);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=2,x;i<=n;i++)scanf("%d",&x),son[x].push_back(i);
	dfs(1,1);
	ll ans=0;
	for(int i=n;i;i--){
		if(sum[i]){
			cout<<(sum[i]>0?"+":"-");
			return 0;
		}
	}
	cout<<"0";
}
```

---

## 作者：Xiphi (赞：0)

考虑建图，$i$ 与 $p_i$ 连边，$i$ 点的点权为 $a_i$。从 $1$ 节点跑 bfs 求出每个点的深度，在由大到小枚举深度，若这个深度所有点权之和不为 $0$，输出正负性，否则一直做下去，直到枚举到深度为 $1$ 的时候，输出 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
long long n,a[250006],p[250005];
vector<int> Adj[250005];
int vis[250005];
int dep[250005],sum[255505];
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=2;i<=n;++i) cin>>p[i];
	for(int i=2;i<=n;++i) Adj[i].push_back(p[i]),Adj[p[i]].push_back(i);
	queue<int> q;
	q.push(1);
	sum[1]+=a[1];
	dep[1]=1;
	while(!q.empty()){
		int top=q.front();
		q.pop();
		if(!vis[top]){
			for(int i=0;i<Adj[top].size();++i){
				if(Adj[top][i]==top) continue;
				if(vis[Adj[top][i]]) continue;
				dep[Adj[top][i]]=dep[top]+1;
				sum[dep[Adj[top][i]]]+=a[Adj[top][i]];
				q.push(Adj[top][i]);
			}
			vis[top]=1;
		}
	}
	for(int i=n;i>=1;--i){
		if(sum[i]!=0){
			if(sum[i]>0){
				cout<<'+';exit(0);
			}else cout<<'-',exit(0);
		}
	}
	cout<<0;
	return 0;
}




```

---

## 作者：Saint_ying_xtf (赞：0)

洛谷翻译很友善，原本抽象的 AT 原题面数轴问题变成一棵形象的树了。想到这一步基本已经做完一半了。会发现，深度越深会影响到深度浅的地方，于是我们先广搜一遍，处理深度，然后 $i$ 点所对应的深度的贡献进行累加。然后从最深的往前遍历，如果有一个累加是大于 $0$ 的，意味着可以将他上面的点都改成正的（于是输出 ```+```），小于 $0$ 同理，如果到最后还没有处理出答案，那么输出 ```0```。好笑的事情，黄题看题解。

```cpp
int n;
int a[N],fa[N];
int dep[N],sum[N];
vector<int> mp[N];
void solve(){
	memset(dep,0,sizeof dep);
	cin >> n;
	for(int i = 1;i <= n;i++) cin>>a[i];
	for(int i = 2;i <= n;i++){
		cin >> fa[i];
		mp[fa[i]].pb(i);
	}dep[1]=1;
	queue<int> q;q.push(1);while(!q.empty()){
		int x=q.front();q.pop();
		for(auto it:mp[x]){
			dep[it]=dep[x]+1;
			q.push(it);
		}
	}
	
	for(int i=1;i<=n;i++)if(dep[i]<linf)sum[dep[i]]+=a[i];
	
	for(int i = n;i >= 1;i--){
		if(sum[i]){
			if(sum[i]>0)cout<<'+';
			else cout<<'-';
			exit(0);
		}
	}
	cout<<0;
}
```

---

