# 「EZEC-14」众数 II

## 题目背景

dXqwq 是一个不可爱的男孩子。他在 NOI2022 中的众数一题定义了 $10^6$ 个 ``std::deque`` 并成功 MLE。

## 题目描述

给定一个长度为 $n$ 的序列 $a$，我们通过以下方式构造序列 $b$：

- 初始时 $b$ 为空序列。
- 对于 $i=1,2,\cdots,n$，我们依次向 $b$ 的尾部插入 $1,2,\cdots,a_i$。

dXqwq 定义一个序列的**最小众数**为所有出现次数最大的数的最小值。例如 $[1,1,4,5,1,4]$ 的最小众数为 $1$，而 $[1,14,5,14,19,19,8,10]$ 的最小众数为 $14$。

你需要求出 $b$ 的每个子区间的**最小众数**的和。由于答案可能很大，你只需要输出它对 $998244353$ 取模后的值。

## 说明/提示

**【样例解释】**

在第一个样例中，$b=[1,1,2,1,2,3]$。

有 $15$ 个区间的最小众数为 $1$，$5$ 个区间的最小众数为 $2$，$1$ 个区间的最小众数为 $3$，因此答案为 $15\times 1+5\times 2+1\times 3=28$。

**【提示】**

开 $10^6$ 个 ``std::deque`` 在空间限制为 512MB 时一定会 MLE。

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$\sum a_i\leq 100$。
- Subtask 2（20 pts）：$\sum a_i\leq 10^3$。 
- Subtask 3（20 pts）：$\sum a_i\leq 10^6$。
- Subtask 4（10 pts）：$n\leq 2$。
- Subtask 5（20 pts）：$n\leq 10^3$。
- Subtask 6（10 pts）：$a_i\leq 2$。
- Subtask 7（10 pts）：无特殊限制。 

对于 $100\%$ 的数据，$1\leq n\leq 10^6$，$1\leq a_i\leq 10^6$。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
28```

## 样例 #2

### 输入

```
9
9 9 8 2 4 4 3 5 3```

### 输出

```
1912
```

# 题解

## 作者：larsr (赞：58)

## 题目含义
用 $a$ 生成 $b$，从 $a_1$ 到 $a_n$ 这样遍历，在 $b$ 后面加入 $1, 2, \ldots, a_i$。比如样例 $1$，$a = [1, 2, 3]$。

> + $a_1 = 1$，所以此时 $b = [1]$
> + $a_2 = 2$，所以此时 $b = [1, 1, 2]$
> + $a_3 = 3$，所以此时 $b = [1, 1, 2, 1, 2, 3]$

假设 $b$ 的长度为 $m$，最后输出：

$$\sum_{1 \leq l \leq m} \sum_{l \leq r \leq m} f(l, r)$$

这里的 $f(l, r)$ 是 $b$ 的区间 $[l,r]$，中**最小众数**（所有出现次数最大的数的最小值）。
## 暴力算法
计算出 $b$，再对 $b$ 的每个区间计算最小众数，时间复杂度 $O((\sum a_i)^3)$。

计算 $[l, r + 1]$ 时，其中的 $[l, r]$ 已经算过了，所以算完 $[l, r]$ 把 $r + 1$ 算进去就可以了，时间复杂度 $O((\sum a_i)^2)$，得 $30$ 分。
## 定理 1
**定理**：一个区间 $[l,r]$ 的最小众数为 $i$（$i$ 不为 1）,那么 $b_l$ 一定是 $i$。

用反正法想，加入 $b_l$ 不是 $i$，那么当 $b_j = i$ 时，$b_{j - 1}$ 一定是 $i - 1$。因为 $i$ 不为 1，并且 $b$ 是按照 $1,2,\ldots$ 的顺序加入的。

通过这可以知道当 $b_l$ 不是 $i$ 时，这个区间出现一个 $i$，一定会出现一个 $i - 1$，所以：

$$\sum_{l \leq i \leq r}[b_i = i] \leq \sum_{l \leq i \leq r}[b_i = i - 1]$$

又因为 $i$ 不为 $1$，而且 $i - 1 \le i$，这时 $i - 1$ 就会成为这个区间的最小众数。所以定理成立。
## 定理 2
**定理**：一个区间 $[l,r]$ 的最小众数为 $i$（$i$ 不为 1），那么在这个区间中出现了的每个组中在区间出现了的数一定有一个为 $i$。

为方便讲述，下文对于 $b$ 的表示类似于 $[[1],[1,2],[1,2,3]]$。

**组**的定义如下：
> 对于 $a_i$ 会对 $b$ 加入 $1,2,\ldots,a_i$，是同一个 $a_i$ 加入的为一组，比如 $b = [[1],[1,2],[1,2,3]]$，第一组为 $[1]$，第二组为 $[1,2]$，第三组为 $[1,2,3]$。

这个定理可能有点长，看不懂，先给大家断一个句：在“**这个区间**”中“**出现了的每个组**”中“**在区间出现了的数**”一定有“**一个为 $i$**”。

比如 $b = [[1],[1,2],[1,2,3]]$，区间为 $[3,6]$，这里**出现了的组**有第二组和第三组，第二组中**在区间出现了的数**有 $2$，第三组中**在区间出现了的数**有 $1,2,3$。

第一个**在区间出现了的组**中**在区间出现了的数**中一定没有 $1$，因为定理 $1$($b_l = i)$，而且 1 在每个组的最前面。

**其他在区间出现了的每个组**中**在区间出现了的数**中一定有 $1$，因为 $1$ 是每个组第一个，假如这个组（不是第一个出现的组）在区间出现过，那么这个组一定出现了 $1$。

假设 $p$ 是**在区间出现了的组**的数量，通过上面可以知道，$1$ 在区间里出现的数量为 $p - 1$。要想让 $i$ 成为这个区间的最小众数，就要让 $i$ 出现次数比 $1$ 多，因为一个组不可能出现同一个数，那么 $i$ 出现次数为 $p$，所以定理成立。
## 定理 3
**定理**：一个区间 $[l,r]$ 的最小众数为 $i$（$i$ 不为 1），如果第 $j$ 组在区间出现，那么 $i \leq a_j$。

根据定理 2，每个组要想其中的数 $i$ 在区间里出现，那么首先要保证这个组有 $i$ 这个数。要想有就要保证 $i \leq a_j$。
## 定理 4
**定理**：一个区间 $[l,r]$ 的最小众数为 $i$（$i$ 不为 1），那么 $i \leq b_r$。

根据定理 2，那么最后出现的组中 $i$ 一定出现了。$i$ 出现了，所以 $r$ 必须比这个 $i$ 的位置靠后，又不能靠后到下一个组，所以 $i \leq b_r$。
## 按值查找区间个数
我们可以换个思路，答案可以是：

$$\sum_{1 \leq i \leq \max a_i} P(i) \times i$$

$P(i)$ 表示为最小众数为 $i$ 的区间个数。

一个区间 $[l,r]$ 要满足以上的四个定理，那么 $f(l,r) = i$，所以直接按这四个定理找就行。对于每个 $i$，首先枚举开头在哪个组，在接着枚举结尾在哪个组。时间复杂度 $O(n^2\max a_i)$ 核心代码：
```cpp
ll ans = 0;
for(ll i = 2; i <= 1e6; i++)
{
	ll la = ans;
	for(ll j = 1; j <= n; j++)
	for(ll k = j; k <= n && a[k] >= i; k++)
   	ans = (ans + a[k] - i + 1) % mod;
	if(la != ans)break;
}

```
细心的你可能发现了没有求 $1$。直接求 $1$ 的区间数量会很麻烦，我们可以用 `ci` 记录其他数的区间数量，最后用总区间数量减去它们就可以。代码如下：
```cpp
ll sum = 0;
for(int i = 1; i <= n; i++)sum = (sum + a[i]) % mod;
if(sum&1)sum = sum % mod * ((sum + 1) / 2) % mod;
else sum = (sum / 2) % mod * (sum + 1) % mod;
ans = (ans + sum - ci + mod) % mod;
```
假如你细心看上面的代码，你会发现每次对 `ans` 的操作都是 `ans = (ans + a[k] - i + 1) % mod;`，只和 `a[k]` 和 `i` 有关。我们可以直接枚举 `a[k]` 要算几次，乘一下就行了，次数是前面和 $a_k$ 连着的 $i \leq a_j$ 有几个。详细看一下解释：

> 比如 $a = [2, 1, 2, 2, 3, 2], i = 2,k = 5$，前面的保证 $i \leq a_j$，为 $a_1,a_3,a_4,a_5$（当然是要包括 $a_k$ 本身的），其中和 $a_k$ 连着的是 $a_3,a_4,a_5$。

时间复杂度为 $o(n\max a_i)$，预期得 70 分，核心代码如下：
```cpp
for(ll i = 2; i <= 1e6; i++)
{
	ll la = ci;
	for(ll j = 1; j <= n; j++)
	{
		if(a[j] < i)continue;
		ll k = j;
		while(a[k + 1] >= i)k++;
		for(ll h = j; h <= k; h++)
		ci = (ci + (a[h] - i + 1) * (h - j + 1)) % mod, ans = (ans + (a[h] - i + 1) * (h - j + 1) % mod * i) % mod;
		j = k;
	}
	if(ci == la)break;
}
```
## 优化
把上面的思路，转换一下。可以把 $i \leq a_k$ 连起来的区间提出来。比如区间 $[l,r]$，对于 $l \leq k \leq r$，保证 $i \leq a_k$，并且 $a_{l - 1},a_{r + 1} < i$。提出到 $h$ 里面，$h_i = a_{i + l - 1}$。这个区间的子区间中最小众数为 $i$ 的数量为：

$$\sum_{1 \leq j \leq r - l + 1} (h_j - i + 1) \times j$$

即

$$\begin{pmatrix} \sum_{1 \leq j \leq r - l + 1} h_j \times j\end{pmatrix} - (i - 1) \frac{(l + r - 1)(l + r)}{2}$$

我们可以让 $i$ 从大往小遍历，在遍历一个数时，就要加入 $a_j = i$ 的数，新加入一个数可能要和之前的区间，假如 $i \leq a_{j - 1}$，那么把 $a_j$ 和 $a_{j - 1}$ 所在的区间合并。$a_{j + 1}$ 的操作也同样。区间合并可以用并查集操作。

确实合并完了，但对答案的贡献还没有更新。对于两个要合并的区间，分别是 $x_1,\ldots,x_{nx}$ 和 $y_1,\ldots,y_{ny}$（$x$ 在左，$y$ 在右），则：

$\sum_{1 \leq j \leq r - l + 1} h_j \times j = \sum_{1 \leq j \leq nx} x_j \times j + \sum_{1 \leq j \leq ny} y_j \times j + nx\sum y_j$

我们用 `now` 记录所有区间 $\sum_{1 \leq j \leq r - l + 1} h_j \times j$ 的和，等式右边前两项不用管了，因为已经记录过了，只需要让 `now` 增加 $nx\sum y_j$ 就可以了。

对于 $(i - 1) \frac{(l + r - 1)(l + r)}{2}$，我们用 `ji` 记录所有区间 $\frac{(l + r - 1)(l + r)}{2}$ 的和，每个区间用 `siz` 记录长度，合并的时候重新算一下就可以。

当 $a_k = i$ 的数加入了，并且和其他区间合并完毕，要对答案计算贡献 `ans = (ans + (now - ji * (i - 1) % mod + mod) % mod * i) % mod;`。时间复杂度 $O(n + \max a_i)$。

## code
```cpp
#include<cstdio>
#include<algorithm>
#define N 1000010
#define mod 998244353 
#define ll long long
using namespace std;
struct node
{
	ll a;
	int id;
}p[N];
int n;
int f[N], v[N];
ll now = 0, ji = 0, sum[N], siz[N], ci = 0, ans = 0;
bool cmp(node x, node y)
{
	return x.a < y.a;
}
int find(int x)
{
	if(f[x] == x)return x;
	return f[x] = find(f[x]);
}
void uni(int x, int y)
{
	if(siz[x] > siz[y])swap(x, y);
	f[x] = y;
	siz[y] += siz[x];
	sum[y] = (sum[y] + sum[x]) % mod;
}
ll lon(ll x)
{
	if(x & 1)return x * ((x + 1) / 2) % mod;
	return (x / 2) * (x + 1) % mod;
}
void hb(int x, int y)
{
	ji = (ji - lon(siz[x]) % mod - lon(siz[y]) % mod + lon(siz[x] + siz[y]) % mod + 2 * mod) % mod;
	now = (now + sum[y] * siz[x]) % mod;
	uni(x, y);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)scanf("%lld", &p[i].a), p[i].id = i;
	for(int i = 1; i <= n; i++)f[i] = i, siz[i] = 1;
	sort(p + 1, p + 1 + n, cmp);
	int j = n;
	for(ll i = 1e6; i > 1; i--)
	{
		while(p[j].a == i)
		{
			v[p[j].id] = 1;
			sum[p[j].id] = p[j].a;
			ji = (ji + 1) % mod;
			now = (now + p[j].a) % mod;
			if(v[p[j].id - 1])hb(find(p[j].id - 1), find(p[j].id));
			if(v[p[j].id + 1])hb(find(p[j].id), find(p[j].id + 1));
			j--;
		}
		ci = (ci + now - ji * (i - 1) % mod + mod) % mod;
		ans = (ans + (now - ji * (i - 1) % mod + mod) % mod * i) % mod;
	}
	ll sum = 0;
	for(int i = 1; i <= n; i++)sum = (sum + p[i].a) % mod;
	sum = lon(sum);
	ans = (ans + sum - ci + mod) % mod;
	printf("%lld\n", ans);
	return 0; \\完结撒花
}
```
## 结语
本人 2021 年开始学 OI，学了两年多，现在是准初二。最开始是在学而思学，2021CSP-J 考砸了，才考了 160。后来我认为培训机构教的太慢，就开始自学。

小升初的时候，父母为了给我一个更好的教育资源，把我送进了 TCMS。我在这个学校是借读，因为这个学校在之前干过教育局不让干的事（上网搜一下就知道了）。去年我 CSP 报的考点在北京，但进考场需要七天一直在京，所以我去年没考成，不然我就不是绿标了，早成蓝标了。

一次没考是不至于难过的，我真正难过的是我的处境。首先我是借读，所以我是没有学籍，在河北和北京报 CSP 好像都要通过学籍所在校，而且要想有学籍，就要把户口转过来，需要很长时间。也就是说假如我继续在这里上的话，今年又不能参加 CSP。

虽然我的 whk 已经不错了，但是父母就像被洗脑了一样，说：“你暑假不弯道，到时候就倒数了”。就这样我学 OI 的时间就这样一点一点被挤没。我是 B 类生，想考衡中，衡二太难了，只能考一个还行的高中。在还行的高中，想拿银牌，金牌太难了。简单来说，在那里上学的话，OI 也没什么用了。

TCMS 已经是一种畸形的教育了。老师只照顾私下收了钱的学生，体罚，打人的情况也有，每天都是死学。这种环境我实在是受不了。

我其实不只有这一条路，我的户口在广东，选择那里肯定比这好，我这次比赛考了第十，虽然和那些大佬比不了，但也不错，我要是有充足的时间，拿个银牌应该可以。

但是父母就是不同意，我和他们说我的想法，他们就训我一顿，后来我也不敢说了。我每天只能活在伤心和迷茫之中。我能有什么办法呀？只能放弃 OI 了……。

---

## 作者：dead_X (赞：30)

## Solution

考虑到一个事实：区间最小众数只能为 $1$ 或者区间的第一个数 $l$。

> 证明：不难发现子区间可以写成 $[l,a_x],[1,a_{x+1}],[1,a_{x+2}],\cdots,[1,a_{y-1}],[1,r]$。
> 
> 如果最小众数 $x$ 在 $[2,l)$ 之间，此时每个 $x$ 的左边都存在一个该段的 $1$，因此 $1$ 的出现次数一定不小于它，因此 $x$ 不是最小众数。
> 
> 如果最小众数 $x$ 比 $l$ 更大，此时每个 $x$ 的左边都存在一个该段的 $l$，因此 $l$ 的出现次数一定不小于它，因此 $x$ 不是最小众数。

进一步发现 $l$ 是区间众数当且仅当每段右端点都 $\geq l$。

考虑对于 $l=2,3,\cdots,\max\{a\}$ 分别计算左端点为 $l$ 且最小众数为 $l$ 的区间数量，用总区间数 $\frac{n(n+1)}{2}$ 减去即可得到最小众数为 $1$ 的区间数量。

对于每个 $l$ 尝试归纳其充分必要的合法条件：从第 $x$ 段的 $l$ 走到第 $y$ 段的 $r$ 合法当且仅当对于 $i\in [x,y]$ 都满足 $a_i\geq l$。因此使用链表维护每个极长的 $\geq l$ 段并更新答案即可。

时间复杂度 $O(n+\max\{a\})$，可以通过离散化做到 $O(n\log n)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353,inv=(p+1)>>1,N=1e6;
vector<int> v[1000003];
int a[1000003],f[1000003],g[1000003];
int l[1000003],r[1000003];
signed main()
{
	int n=read(),ans=0,sf=0,sg=0,s=0;
	for(int i=1,x; i<=n; ++i)
		x=read(),s=(s+x)%p,v[x].push_back(i);
	s=1ll*s*(s+1)%p*inv%p;
	for(int i=N; i>1; --i)
	{
		for(int j:v[i])
		{
			l[j]=r[j]=j,f[j]=i,g[j]=1,
			sf=(sf+i)%p,sg=(sg+1)%p;
			if(l[j-1])
			{
				int x=l[j-1],len=j-x;
				sf=(sf+1ll*len*f[j])%p,
				sg=(sg+1ll*len*g[j])%p,
				r[x]=j,l[j]=x,
				f[x]=(f[x]+f[j])%p,
				g[x]=(g[x]+g[j])%p;
			}
			if(r[j+1])
			{
				int x=l[j],len=j+1-x;
				sf=(sf+1ll*len*f[j+1])%p,
				sg=(sg+1ll*len*g[j+1])%p,
				r[x]=r[j+1],l[r[j+1]]=x,
				f[x]=(f[x]+f[j+1])%p,
				g[x]=(g[x]+g[j+1])%p;
			}
		}
		int t=(sf+p-1ll*sg*(i-1)%p)%p;
		ans=(ans+1ll*t*i)%p,s=(s+p-t)%p;
	}
	ans=(ans+s)%p,	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Lucky_Xiang (赞：12)

# 题目

[P9461](https://www.luogu.com.cn/problem/P9461)

# 思路

假设原序列 $a=[5,3,4,2,3]$，则 $b=[1,2,3,4,5,1,2,3,1,2,3,4,1,2,1,2,3]$。如果要计算最小众数为 $3$ 时的贡献，就子区间一定要以 $3$ 开头，否则一定会出现更小众数。假如以最左边的 $3$ 开头，则可以在以下红色、蓝色和绿色的位置结尾：

$$\color{grey}b=[1,2,\color{red}{3,4,5}\color{grey},1,2,\color{blue}3,\color{grey}1,2,\color{lime}3,4\color{grey},1,2,1,2,\color{orange}3\color{grey}]$$

而在序列中第二个 $3$ 开头也可以在蓝色和绿色的位置结尾，因此蓝色位置要算两遍，同理绿色位置要算三遍，橙色位置只能算一遍。整理 $a$ 序列中各个位置的计算次数得：

$$w=[1,2,3,0,1]$$

因此，最小众数为 $3$ 的子区间共有 $\sum_{i=1}^{n}w_i(a_i-3+1)$ 个，总贡献为 $\sum_{i=1}^{n}3w_i(a_i-3+1)$。

形式化的，最小众数为 $k$ 的总区间数为 $\sum_{i=1}^{n}w_i(a_i-k+1)$，总贡献为 $\sum_{i=1}^{n}kw_i(a_i-k+1)$。

这时如果想求最小众数为 $2$ 的贡献，序列 $w$ 要发生以下变化：

$$w=[1,2,3,\color{red}4,5\color{black}]$$

可以发现红色部分同时加了 $4$，因此可以通过维护 $\sum_{i=1}^{n}w_i$ 和 $\sum_{i=1}^{n}w_ia_i$，从而计算新的贡献（计算顺序为从大数到小数）。

值得注意的是，$1$ 的贡献应该单独计算，因为它不满足必须由 $1$ 开始。它的贡献值为总区间数减去其他数的区间数。

# 代码

代码中 `S` 表示 $\sum_{i=1}^{n}w_ia_i$，`ccnt` 表示 $\sum_{i=1}^{n}w_i$，`cnt` 表示总区间数。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mn=1000010;
const int mod=998244353;
int n;
int x[mn];
vector<int>P[mn];
LL sum[mn],cnt,ccnt;
LL res;
int mx;
int p[mn];
int gf(int x)
{
	if(x==p[x])return x;
	return p[x]=gf(p[x]);
}
LL w[mn];
bool b[mn];
LL S;
void unlock(int k)
{
	b[k]=1;
	if(b[k-1])p[gf(k-1)]=gf(k);
	if(b[k+1])p[gf(k)]=gf(k+1);
	w[gf(k)]+=w[k-1]+1; //一段中只有最右边的 w 会对后续更新产生影响
	S+=(w[k-1]+1)*(sum[gf(k)]-sum[k-1])%mod;
	S%=mod;
	ccnt+=(w[k-1]+1)*(gf(k)-(k-1))%mod;
	ccnt%=mod;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x[i]);
		sum[i]=sum[i-1]+x[i]; sum[i]%=mod;
		P[x[i]].push_back(i);
		mx=max(mx,x[i]);
		p[i]=i;
	}
	for(int i=mx;i>=2;i--) //计算 i 的贡献
	{
		for(int k:P[i])unlock(k); //更新 w
		res+=(S-ccnt*(i-1)%mod)*i%mod;
		cnt+=S-ccnt*(i-1)%mod;
		res%=mod; cnt%=mod;
	}
	//计算 1 的贡献
	cnt=sum[n]*(sum[n]+1)/2-cnt; cnt%=mod;
	res+=cnt;
	res=(res%mod+mod)%mod;
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：4)

考虑一个区间的最小众数能是什么。结论：最小众数只能是 $1$ 或者左端点的值。

对于一个区间 $[l,r]$，考虑两端的值 $x=a_l,y=a_r$，那么区间可以被写成 $[x,a_i],[1,a_{i+1}],[1,a_{i+2}],\cdots,[1,a_j],[a_j,y]$。**最小**是个很重要的性质。在上面的表示形式中，容易发现 $1$ 的出现次数很多，而且也很小。除了 $1$，只有 $x$ 能成为最小众数。容易发现，$x$ 作为最小众数的充要条件是，$\min(a_{i+1},a_{i+2},\cdots,a_{j},y)\ge x$。这样可以保证 $x$ 的出现次数严格大于 $1$ 的出现次数，并且在同样出现次数中值最小。

考虑对最小众数 $=x$ 的区间数量计数，记录为 $cnt_x$，最小众数为 $1$ 的可以直接用总区间个数减去 $\sum_{i=2}^{mx} cnt_i$。答案显然就是 $\sum_{i=1}^{mx} icnt_i$。

求出 $cnt_i$，考虑上面写的，要求后面一些 $a_i$ 以及终点 $y$ 的值都大于 $x$，这样应该被合并成若干个连续段。考虑倒序从 $mx$ 求解到 $2$ 的 $cnt_x$。这样连续段不会被拆分，只会被进一步合并。

对值倒序扫描线时，设当前值为 $x$，那么考虑每个连续段（将 $a_i\ge x$ 的所有位置合并成连续段），每个 $a_i$ 都可以有起点 $x$，终点 $y$ 的位置可以直接从后面 $\ge x$ 的位置中任意选。容易将连续段的贡献写成以下形式：

$$\left (\sum_{i=1}^{len}ia_i\right )-\dfrac{(x-1)len(len+1)}{2}$$

考虑对 $\sum ia_i$ 以及 $\sum\dfrac{len(len+1)}{2}$ 分别维护，直接求即可。连续段容易用并查集解决。

时间复杂度 $O(n+A)$。$A=10^6$ 为值域。

```cpp
// Problem: P9461 「EZEC-14」众数 II
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9461
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Author: nullptr_qwq
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define inf 1e9
#define pii pair<int,int>
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
#define wh(lzm) while(lzm--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int mod=998244353,maxn=1000005;
int qpow(int x,int y){
	if(y<=0) return 1;
	int rt=1;
	for(;y;y>>=1,x=1ll*x*x%mod) if(y&1) rt=1ll*rt*x%mod;
	return rt;
}
void inc(int &x,int y){ x=(x+y>=mod)?(x+y-mod):(x+y); }
void dec(int &x,int y){ x=(x>=y)?(x-y):(x+mod-y); }
void mul(int &x,int y){ x=1ll*x*y%mod; }
int add(int x,int y){ return (x+y>=mod)?(x+y-mod):(x+y); }
int sub(int x,int y){ return (x>=y)?(x-y):(x+mod-y); }
int prod(int x,int y){ return 1ll*x*y%mod; }
void chkmax(int &x,int y){ x=max(x,y); }
void chkmin(int &x,int y){ x=min(x,y); }
int n,a[maxn],num[maxn],mx;
vector<int>g[maxn];
int fa[maxn],sz[maxn],cmh[maxn],sum[maxn];
// cmh = sum i*a[i]
// sum = sum a[i]
int ans,sum1,sum2,tot;
int find(int x){ return fa[x]==x?x:fa[x]=find(fa[x]); }
int S(int x){ return ((1ll*x*(x+1))>>1)%mod;}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;
	dec(sum1,cmh[x]),dec(sum1,cmh[y]);
	dec(sum2,S(sz[x])),dec(sum2,S(sz[y]));
	inc(cmh[x],cmh[y]);
	inc(cmh[x],1ll*sum[y]*sz[x]%mod);
	inc(sum1,cmh[x]);
	inc(sum2,S(sz[x]+sz[y]));
	inc(sum[x],sum[y]);
	fa[y]=x,sz[x]+=sz[y];
}
signed main(){
	n=read();
	F(i,1,n) a[i]=read(),g[a[i]].push_back(i),chkmax(mx,a[i]),inc(tot,a[i]);
	dF(i,mx,2){
		for(int j:g[i]) fa[j]=j,cmh[j]=sum[j]=a[j],sz[j]=1,inc(sum1,a[j]),inc(sum2,1);
		for(int j:g[i]){
			if(j>1&&a[j-1]>=i) merge(j-1,j);
			if(j<n&&a[j+1]>=i) merge(j,j+1);
		}
		num[i]=sub(sum1,1ll*(i-1)*sum2%mod);
	}
	num[1]=((1ll*tot*(tot+1))>>1)%mod;
	F(i,2,mx) dec(num[1],num[i]);
	F(i,1,mx) inc(ans,1ll*i*num[i]%mod);
	cout<<ans;
}
```

---

## 作者：SoundOfDestiny (赞：3)

upd 2023.07.19：多了一个括号，已删掉。

个人感觉这题~~多少沾点~~挺好玩的

题目传送门：[P9461](https://www.luogu.com.cn/problem/P9461)

下文中 $[a_i, a_j]$ 均表示 $a$ 序列的子区间，$[b_{i, l}, b_{j, r}]$ 均表示 $b$ 序列的子区间，若出现小括号内套小括号也请勿喷。

------------

# 分段

首先题目中让我们构造一个序列 $b$，这肯定是不现实的，因为这样 $b$ 中将会至多有 $10^{12}$ 项，显然会 $\text{MLE}$，所以我们考虑直接在 $a$ 中进行操作。

首先我们将 $b$ 序列分段，具体地来说，第 $i$ 段的长度为 $a_i$。则 $b$ 中的每一个项都可以表示为 $b_{i, j}$ 且 $b_{i, j} = j$（其中 $i$ 为这一项所在的段的编号，$j$ 为这一项是所在段中的第几个）。

$$
b: (b_{1, 1}, b_{1, 2} \dots b_{1, a_1}), (b_{2, 1}, b_{2, 2} \dots b_{2, a_2}) \dots (b_{n, 1}, b_{n, 2} \dots b_{n, a_n})
$$

# 贡献

考虑对于一个数 $k$，若 $k$ 成为了 $b$ 的一个子区间的最小众数，则该子区间应满足什么条件。

## 第一类贡献

令该子区间为 $[b_{i, l}, b_{j, r}]$，经过实验可发现当满足如下条件

$$
b_{i, l} = l = k
$$
$$
b_{j, r} = r \geq k
$$
$$
b_{m, a_m} = a_m \geq k \ (\forall \ i \leq m \leq j)
$$

时，$[b_{i, l}, b_{j, r}]$ 这一区间的最小众数为 $k$，记这一类对答案的贡献为“第一类 $k$ 贡献”。

## 第二类贡献

实验发现当 $k=1$ 时，令该子区间为 $[b_{i, l}, b_{j, r}]$，当满足以下条件

$$
b_{i, l} = l > 1
$$
$$
b_{j, r} = r < l
$$
$$
b_{m, a_m} = a_m \geq l \ (\forall \ i \leq m \leq j)
$$

或

$$
b_{i, l} = l > 1
$$
$$
b_{m, a_m} = a_m < l \ (\exists \ i \leq m \leq j)
$$

时，$[b_{i, l}, b_{j, r}]$ 这一区间的最小众数为 $1$，可以再对答案产生额外贡献，记这一类贡献为“第二类贡献”。

# 讨论

考虑一个子区间 $[a_i, a_j]$ 能对答案提供多少贡献。

## 第一类贡献

先考虑第一类贡献。令子区间 $[a_i, a_j]$ 在 $b$ 中的对应子区间为 $[b_{i, l}, b_{j, r}]$，可以发现若 $[b_{i, l}, b_{j, r}]$ 可以对答案产生 $k$ 的贡献，则

$$
k \leq \min_{i \leq m \leq j} a_m \leq \min_{i + 1 \leq m \leq j} a_m
$$

即 $[b_{i + 1, l}, b_{j, r}]$ 也可对答案产生 $k$ 的贡献，同理 $[b_{i, l}, b_{j - 1, r}]$ 也可对答案产生 $k$ 的贡献。

所以 $[a_i, a_j]$ 能产生的第一类 $k$ 贡献一定包括了 $[a_{i + 1}, a_j]$ 和 $[a_i, a_{j - 1}]$ 所产生的第一类 $k$ 贡献。

所以我们只需要对每一个 $k$，枚举每一个 $[a_i, a_j]$，使得

$$
\max \left(\min_{i - 1 \leq m \leq j} a_m \ , \min_{i \leq m \leq j + 1} a_m \right) < k \leq \min_{i \leq m \leq j} a_m
$$

称这些 $[a_i, a_j]$ 为 $k$ 贡献区间。

现在我们来计算 $[a_i, a_j]$ 在作为 $k$ 贡献区间的情况下能为答案提供多少第一类贡献，记为 $SUM1_{i, j, k}$，同时记 $\text{sig}(l, r) = \dfrac{(l + r) \cdot (r - l + 1)}2$（即 $\sum_{l \leq i \leq r} i$）。

我们枚举每一个 $i \leq ib \leq j$，同时枚举每一个 $ib \leq jb \leq j$，则此时的 $[b_{ib, k}, b_{jb, k}], [b_{ib, k}, b_{jb, k + 1}] \dots [b_{ib, k}, b_{jb, a_{jb}}]$ 均可对答案产生 $k$ 的贡献，所以此时 $[a_i, a_j]$ 在作为 $k$ 贡献区间的情况下能提供的第一类贡献就为

$$
\begin{aligned}
SUM1_{i, j, k} &= \left(\sum_{i \leq ib \leq j} \sum_{ib \leq jb \leq j} (a_{jb} - (k - 1))\right)k \\ &= \left(\left(\sum_{i \leq ib \leq j} \sum_{ib \leq jb \leq j} a_{jb}\right) - \left(\sum_{i \leq ib \leq j} \sum_{ib \leq jb \leq j} (k - 1)\right)\right)k \\ &= \left(\left(\sum_{i \leq ib \leq j} (ib - i + 1) \cdot a_{ib}\right) - \text{sig}(1, j - i + 1) \cdot (k - 1)\right)k
\end{aligned}
$$

注意到由于 $a$ 序列是一个固定的序列，所以我们可以对 $\sum_{i \leq ib \leq j} (ib - i + 1) \cdot a_{ib}$ 进行前缀和优化。

具体地来说，令 $sum_i = sum_{i - 1} + a_i$，$pre_i = pre_{i - 1} + i \cdot a_i$，则

$$
\begin{aligned}
SUM1_{i, j, k} &= ((pre_j - pre_{i - 1} - (i - 1) \cdot (sum_j - sum_{i - 1})) - \text{sig}(1, j - i + 1) \cdot (k - 1))k
\end{aligned}
$$

## 第二类贡献

对于这样的一个 $k$ 贡献区间 $[a_i, a_j]$，我们考虑它的第二类贡献。

枚举每一个 $i < ib \leq j$，枚举每一个 $ib \leq jb \leq j$，则此时的 $[b_{ib, k}, b_{jb, 1}], [b_{ib, k}, b_{jb, 2}] \dots [b_{ib, k}, b_{jb, k - 1}]$ 均可对答案产生 $1$ 的贡献。此外，对于每一个 $i \leq ib \leq j$，枚举每一个 $jb > j$，对于每一个 $1 \leq kb \leq a_{jb}$，$[b_{ib, k}, b_{jb, kb}]$ 均可再对答案产生 $1$ 的贡献。

所以此时 $[a_i, a_j]$ 在作为 $k$ 贡献区间的情况下能提供的第二类贡献 $SUM2_{i, j, k}$ 就为

$$
\begin{aligned}
SUM2_{i, j, k} &= \left(\sum_{i < ib \leq j} \sum_{ib \leq jb \leq j} (k - 1)\right) + \left(\sum_{i \leq ib \leq j} \sum_{j < jb \leq n} a_{jb}\right) \\ &= \text{sig}(0, j - i) \cdot (k - 1) + (j - i + 1) \cdot (sum_n - sum_{j})
\end{aligned}
$$

# 优化

考虑使用单调栈优化。

考虑维护一个单调递减的栈 $s$，$s \rightarrow top$ 为 $s$ 的栈顶元素（此处为便于理解 $s$ 存放的是数组下标，实际代码中数组的对应值也应存储在 $s$ 中），$s \rightarrow top2$ 为栈顶元素下的元素（如果没有则为 $0$），在遍历每一个 $a_x$（$1 \leq x \leq n$）的时候，如果 $a_x < a_{s \rightarrow top}$，那么说明 $[a_{s \rightarrow top}, a_{x - 1}]$ 一定是一个 $k$ 贡献区间（$\max(a_{s \rightarrow top2}, a_x) + 1 \leq k \leq a_{s \rightarrow top}$）。记 $l = \max(a_{s \rightarrow top2}, a_x) + 1, r = a_{s \rightarrow top}, i = s \rightarrow top, j = x - 1$，说明 $[a_{s \rightarrow top}, a_{i - 1}]$ 对答案的贡献 $SUM$ 为

$$
\begin{aligned}
SUM &= \sum_{l \leq k \leq r} (SUM1_{i, j, k} + SUM2_{i, j, k}) \\ &= \sum_{l \leq k \leq r}\left(((pre_j - pre_{i - 1} - (i - 1) \cdot (sum_j - sum_{i - 1})) - \text{sig}(1, j - i + 1) \cdot (k - 1))k\right) \\ &\quad + \sum_{l \leq k \leq r} \left(\text{sig}(0, j - i) \cdot (k - 1) + (j - i + 1) \cdot (sum_n - sum_{j})\right) \\ &= \text{sig}(l, r) \cdot (pre_j - pre_{i - 1} - (i - 1) \cdot (sum_j - sum_{i - 1})) \\ &\quad - \text{sig}(1, j - i + 1) \cdot (\sum_{l \leq k \leq r} k \cdot (k - 1)) \\ &\quad + \text{sig}(l - 1, r - 1) \cdot \text{sig}(0, j - i) \\ &\quad + (r - l + 1) \cdot (j - i + 1) \cdot (sum_n - sum_j)
\end{aligned}
$$

注意到可以再对 $\sum_{l \leq k \leq r} k \cdot (k - 1)$ 进行前缀和优化，我们令 $kk_i = kk_{i - 1} + i \cdot (i - 1)$，那么

$$
\begin{aligned}
SUM &= \text{sig}(l, r) \cdot (pre_j - pre_{i - 1} - (i - 1) \cdot (sum_j - sum_{i - 1})) \\ &\quad - \text{sig}(1, j - i + 1) \cdot (kk_r - kk_{l - 1}) \\ &\quad + \text{sig}(l - 1, r - 1) \cdot \text{sig}(0, j - i) \\ &\quad + (r - l + 1) \cdot (j - i + 1) \cdot (sum_n - sum_j)
\end{aligned}
$$

经过优化，可以发现预处理时间复杂度为 $O(n + \max a_i)$，单调栈时间复杂度为 $O(n)$，单次计算 $SUM$ 时间复杂度为 $O(1)$，所以总时间复杂度为 $O(n)$。

# 代码

最后附上 [AC 代码](https://www.luogu.com.cn/paste/medn0w0f)，以及 [AC 记录](https://www.luogu.com.cn/record/116092408)

---

## 作者：Hadtsti (赞：2)

~~昨天比赛由于时间原因只看了一眼，这个题感觉挺有意思，随便写了个暴力，结果拿到了 0pts 的高分就没再看……赛后发现有一种情况的性质想错了……~~


~~以上都是废话~~
### 题意简述
给出序列 $\{a_1,a_2,\cdots,a_n\}(1\le n\le10^6,1\le a_i\le10^6)$，构造序列 $b=\{1,2,\cdots,a_1,1,2,\cdots,a_2,\cdots,1,2,\cdots,a_n\}$。求 $b$ 的所有子区间最小众数之和。

### 题目分析
最基础的暴力很好做，直接构造 $b$ 进行统计就行。

注意到 $a_i$ 并不太大（当然大了离散化后也一样），那么 $b$ 不同区间的最小众数也不会有太多情况。我们自然想到可以统计每个数作为区间最小众数的情况数之和。比赛时我也是想到了类似于出题人大佬的区间最小众数性质：要么是 $1$，要么是区间的左端点。具体的证明我没有特意去写，大家可以直接看[出题人大佬的题解](https://www.luogu.com.cn/blog/111055/solution-p9461)，里面说的很详细。

那么对于每个 $b$ 中的区间内的元素，可以拆成 $[l,a_x],[1,a_{x+1}],[1,a_{x+2}],\cdots,[1,a_{y-1}],[1,r]$。当且仅当 $\forall i\in[x,y-1],a_i\ge l$ 且 $r\ge l$ 时区间最小众数为 $l$，否则为 $1$（比赛时我误认为只要 $r\ge l$ 就行，导致了爆零）。

证明比较简单：

若 $\forall i\in[x,y-1],a_i\ge l$ 且 $r\ge l$，则 $l$ 在所有区间**都**存在，出现了 $y-x+1$ 次；而 $1,2,\cdots,l-1$ 在第一个区间不存在，**至多**出现 $y-x$ 次，不可能为众数；$l+1,l+2,\cdots$ 也**至多**出现 $y-x+1$ 次，即使是众数也不可能是最小众数。因此最小众数必为 $l$。

否则，$\exists i\in[x,y-1],a_i<l$ 或 $r<l$，那么 $l,l+1,l+2,\cdots$ 在 $[1,a_i]$ 或 $[1,r]$ 必然不出现，**至多**出现 $y-x$ 次；$1$ 只在第一个区间不出现，**必然**出现 $y-x$ 次，$2,3,\cdots,l-1$ 则**至多**出现 $y-x$ 次。由此判断 $1$ 必为最小众数。

那么有了以上的结论，我们就可以很简单地统计了。对于每个 $l$，用链表快速统计出 $\ge l$ 的极大连续段进行计算即可。

---

## 作者：MaxBlazeResFire (赞：1)

先膜拜一发 DX ~~，几个月前在一起训练的时候还经常偷偷看他打音游~~。

一个区间的最小众数如果不是 $1$，那么一定是其区间左端点上的数。考虑反证法，假设 $[l,r]$ 的区间最小众数 $a_i(i\neq l)\neq 1$，考察数 $a_{i-1}<a_i$.

$a_i$ 每出现一次，$a_{i-1}$ 必然在其前面出现一次，则其出现次数不小于 $a_i$，矛盾。

对于数 $x>1$，设 $[L,R]$ 是某个满足 $a[L,R]\geq x$ 的极长区间（即 $a_{L-1}<x,a_{R+1}>x,\forall i\in[L,R],a_i\geq x$），那么合法的以 $x$ 为最小众数的区间必然被 $[l_L,r_R]$ 完全包含。因为容易发现，假设包含这个范围外的某个数 $t$，必然有 $t$ 的出现次数不少于 $x$.

记 $s_i$ 为 $a_i$ 的前缀和，$S_i$ 为 $s_i$ 的前缀和。

对于数 $x$ 考察某极长段 $a[L,R]$，该范围内以 $x$ 作为最小众数的 **区间个数** 为：

$\displaystyle \displaystyle\sum_{i=L}^R(s_R-s_{i-1})-(x-1)\times(R-i+1)$.

即枚举作为左端点的 $x$ 出现在哪一段。

该式也即 $\displaystyle s_R\times(R-L+1)-(S_{R-1}-S_{L-2})-(x-1)\times\frac{(R-L+1)(R-L+2)}{2}$.

考虑倒序扫描值域，**暴力动态维护所有极长段。** 扫到一个数 $x$ 时，加入所有 $x$ 所在位置 $p$ 组成的小区间 $[p,p]$，并每次暴力合并能合并的段。比如之前存在一个极长段 $[l_0,p-1]$ 与 $[p+1,r_0]$，加入 $[p,p]$ 后就只剩下了 $[l_0,r_0]$ 这一段。

暴力维护所有极长段的 $\displaystyle A=s_R\times(R-L+1)-(S_{R-1}-S_{L-2})$ 之和。

暴力维护所有极长段的 $\displaystyle B=\frac{(R-L+1)(R-L+2)}{2}$ 之和。

那么对于数 $x$，其作为最小众数出现的 **区间个数** 就是 $A-(x-1)\times B$，其 **对答案的贡献** 就是 $x\times(A-(x-1)\times B)$.

然而以 $1$ 为最小众数的区间比较特殊，无法用上述方法处理。于是我们考虑其个数就是 $\displaystyle \frac{s_n(s_n+1)}{2}$ 减去所有之前的数的 **区间个数之和**。

如果你用 $\rm set$ 维护所有区间，就会得到 $90$ 分的好成绩（[set 暴力维护](https://www.luogu.com.cn/record/115774876)）。

我们考虑所有极长段两两无交，于是直接用区间端点代表区间。对于左右端点，写两个数组和两个存在性判定数组即可。

复杂度 $O(n)$.

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 1000005
#define mod 998244353
#define inv2 499122177

inline int read(){
	int x = 0; char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();
	while( ch >= '0' && ch <= '9' ) x = ( x << 3 ) + ( x << 1 ) + ch - 48,ch = getchar();
	return x;
}

inline int reduce( int x ){ return x += ( x >> 31 & mod ); }

int n,maxw,a[MAXN] = {0},s[MAXN] = {0},S[MAXN] = {0};
int exil[MAXN] = {0},exir[MAXN] = {0};
vector<int> pos[MAXN];

pair<int,int> Ml[MAXN],Mr[MAXN];

int Ssr = 0,Lent = 0,Intercount = 0,Ans = 0;

inline int val( const pair<int,int> &p ){
	int l = p.first,r = p.second;
	return ( s[r] * ( r - l + 1 ) % mod - S[r - 1] + ( ( l >= 2 ) ? S[l - 2] : 0 ) + mod ) % mod;
}

inline int len( const pair<int,int> &p ){
	int l = p.first,r = p.second;
	return ( r - l + 1 ) * ( r - l + 2 ) % mod * inv2 % mod;
}

inline void insert( int p ){
	pair<int,int> itl,itr;
	if( exir[p - 1] ) itl = Mr[p - 1];
	if( exil[p + 1] ) itr = Ml[p + 1];
	int L,R;
	if( exir[p - 1] && exil[p + 1] ){
		Ssr = reduce( Ssr - val( itl ) ),Ssr = reduce( Ssr - val( itr ) );
		Lent = reduce( Lent - len( itl ) ),Lent = reduce( Lent - len( itr ) );
		L = itl.first,R = itr.second;
		exir[p - 1] = exil[p + 1] = 0;
	}
	else if( exir[p - 1] ){
		Ssr = reduce( Ssr - val( itl ) ),Lent = reduce( Lent - len( itl ) );
		L = itl.first,R = p;
		exir[p - 1] = 0;
	}
	else if( exil[p + 1] ){
		Ssr = reduce( Ssr - val( itr ) ),Lent = reduce( Lent - len( itr ) );
		L = p,R = itr.second;
		exil[p + 1] = 0;
	}
	else L = R = p;
	pair<int,int> it = Ml[L] = Mr[R] = make_pair( L , R );
	Ssr = reduce( Ssr + val( it ) - mod ),Lent = reduce( Lent + len( it ) - mod );
	exil[L] = exir[R] = 1;
}

signed main(){
	n = read();
	for( int i = 1 ; i <= n ; i ++ ) a[i] = read(),pos[a[i]].emplace_back( i ),maxw = max( maxw , a[i] );
	for( int i = 1 ; i <= n ; i ++ ) s[i] = reduce( s[i - 1] + a[i] - mod );
	for( int i = 1 ; i <= n ; i ++ ) S[i] = reduce( S[i - 1] + s[i] - mod );
	for( int i = maxw ; i > 1 ; i -- ){
		for( int p : pos[i] ) insert( p );
		int tmp = reduce( Ssr - ( i - 1 ) * Lent % mod );
		Intercount = reduce( Intercount + tmp - mod );
		Ans = reduce( Ans + tmp * i % mod - mod );
	}
	Ans = ( Ans + ( s[n] * ( s[n] + 1 ) % mod * inv2 % mod - Intercount + mod ) % mod ) % mod;
	printf("%lld\n",Ans);
	return 0;
}
```

---

## 作者：L_shadow (赞：0)

## 思路：
通过**推式子和单调栈**来优化时间复杂度。

令 一个区间的最小众数和为它所有子区间的最小众数之和，
$ch_i=\sum\limits_{j=1}^i (i-1)^2$，$b_i=\sum\limits_{j=1}^i i$。

分情况讨论一下。

### 一个 $a_i$ 所生成的区间的最小众数和。

假设 $a_i=5$。

那么这个 $a_i$ 生成的 $b$ 序列为 $b=\{1,2,3,4,5\}$。

最小众数为 $1$ 的区间有 $\{1\},\{1,2\},\{1,2,3\},\{1,2,3,4\},\{1,2,3,4,5\}$ 共 $5$ 个。

最小众数为 $2$ 的区间有 $\{2\},\{2,3\},\{2,3,4\},\{2,3,4,5\}$ 共 $4$ 个。

最小众数为 $3$ 的区间有 $\{3\},\{3,4\},\{3,4,5\}$ 共 $3$ 个。

最小众数为 $4$ 的区间有 $\{4\},\{4,5\}$ 共 $3$ 个。

最小众数为 $5$ 的区间有 $\{5\}$ 共 $1$ 个。

可以发现 最小众数为 $j$ 的区间有 $a_i-j+1$ 个。

所以 每一个 $a_i$ 所生成的区间的最小众数和之和为
$\sum\limits_{i=1}^n\sum\limits_{j=1}^{a_i}j\times (a_i-j+1)$。

又 $\sum\limits_{j=1}^{a_i}j=b_{a_i}$。

所以上述式子可以转化为 $\sum\limits_{i=1}^nb_{a_i}\times(a_i+1)-ch_{a_i}$。

### 跨 $a_i$ 的区间。
假设说这个区间从 $a_i$ 跨到了 $a_j$。

#### 先看跨相邻两个 $a_i$ 的区间。

举个例子：$\{1,2,3,4,5,1,2,3,4\}$。

现在只看跨 $a_i$ 的区间。

我们不妨假设这种区间的左端点就是这个区间的最小众数。

验证了几个区间后，好像是对的。

那么左端点为 $l$ 的区间的最小众数和就是 $a_j\times l$。

对于所有 $a_i$ ，这样的区间的最小众数和为 $\sum\limits_{i=1}^n\sum\limits_{k=1}^{a_i}k\times a_{i+1}$。

利用 $b$ 数组优化一下，式子变成 $\sum\limits_{i=1}^nb_{a_i}\times a_{i+1}$。

#### 如果这个区间跨了好多个区间呢？
还是举个例子：$\{1,2,3,1,2,1,2,3,4\}$。

如果 $l=3$ 会发现区间 $\{3,1,2,1,2,3\}$ 的最小众数为 $1$，而不是 $3$。

但如果 $l$ 对应的值是 $2$ 时，却不会有这种情况。

复原这个区间的 $a$ 序列：$3,2,4$。

发现，如果 $l$ 对应的值小于等于从 $a_i$ 到 $a_j$ 中的最小值，最小众数仍然是 $l$ ，但如果 $l$ 对应的值大于 $a_i$ 到 $a_j$ 的最小值，最小众数就只能是 $1$。

式子变成 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(b_{minn}+a_i-minn)\times a_j$,其中$minn=\min_{k=1}^{j} a_k$。

但是，有一些区间，例如 $\{2,1\}$，即使 $l$ 对应的值为 $2$，但最小众数仍然为 $1$。

可以发现，当 $l$ 对应的值为 $a$ 时，这种区间的个数为 $a-1$。

那么我们多加的值为 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^nch_{minn}$。

于是正确的式子是$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(b_{minn}+a_i-minn)\times a_j-ch_{minn}$。

这个式子与上一个式子（计算一个 $a_i$ 所生成的区间的最小众数和）一合并，变成了 

$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(b_{minn}+a_i-minn)\times a_j-ch_{minn}+\sum\limits_{i=1}^nb_{a_i}\times a_{i+1}$，其中 $minn=\min_{k=1}^{j} a_k$。

这个式子的时间复杂度为 $\Theta(n^2)$，瓶颈在于 $minn$ 的计算。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,mod=998244353;
long long n,a[N],ans,ch[N],b[N];
int main(){
	scanf("%lld",&n);
	for(long long i=1;i<=1e6+1;i++) {
		ch[i]=(ch[i-1]+((i-1)*(i-1))%mod)%mod;
		b[i]=(b[i-1]+i)%mod;
	}
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		ans=(ans+(b[a[i]]*(a[i]+1))%mod-ch[a[i]+1]+mod)%mod;
	}
	for(int i=1;i<=n;i++){
		long long minn=a[i];
		for(int j=i+1;j<=n;j++){
			minn=min(a[j],minn);
			ans=(ans+((b[minn]+a[i]-minn)%mod)*a[j]%mod-ch[minn]+mod)%mod;
		}
	}
	printf("%lld",ans);
	return 0;
} 
```

### 单调栈优化。
发现 $minn$ 可以用单调栈优化。

用 $pos_i$ 记录比 $a_i$ 小的第一个数的位置，用 $it$ 记录当前位置。

发现都有 $a_i\times a_j$，用前缀和优化。

令 $aa_i=\sum\limits_{j=1}^i a_i$。

先 $ans+=(aa_n-aa_i)\times a_i$。

如果 $it=i$ 时 $ans+=(b_{minn}-minn)\times (aa_{pos_i-1}-aa_{it})-ch_{minn}\times (pos_{it}-1-it)$。

否则 $ans+=(b_{minn}-minn)\times (aa_{pos_i-1}-aa_{it-1})-ch_{minn}\times (pos_{it}-it)$。

$minn=a_{it}$，$it=pos_{it}$。

## AC代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N=1e6+5;
const long long mod=998244353;
int n,a[N],pos[N];
long long ans;
__int128 aa[N],ch[N],b[N];
int main() {
	scanf("%lld", &n);
	for(long long i=1; i<=1000002; i++) {
		ch[i]=(ch[i-1]+((i-1)*(i-1))%mod)%mod;
		b[i]=b[i-1]+i;
	}
	stack<pair<int, int> > s;
	for(int i=1;i<=n;i++) {
		scanf("%lld", a+i);
		aa[i]=aa[i-1]+a[i];
	}
	for(int i=n; i; i--) {
		while(s.size()&&s.top().first>=a[i]) {
			s.pop();
		}
		if(s.empty()) pos[i]=n+1;
		else pos[i]=s.top().second;
		s.push(make_pair(a[i], i));
	}
	for(int i=1; i<=n; i++) {
		ans=(ans+(b[a[i]]*(a[i]+1))%mod-ch[a[i]+1]+mod)%mod;
	}
	for(int i=1; i<n; i++) {
		int it=i;
		ans=(ans+(aa[n]-aa[i])*a[i])%mod;
		do { 
			if(i==it) ans=(ans+(b[a[it]]-a[it])*(aa[pos[it]-1]-aa[it])-(ch[a[it]]*(pos[it]-it-1)+mod)%mod)%mod;
			else ans=(ans+(b[a[it]]-a[it])*(aa[pos[it]-1]-aa[it-1])-(ch[a[it]]*(pos[it]-it)+mod)%mod)%mod;
			it=pos[it];
		} while(it<=n);
	}
	printf("%lld",ans);
	return 0;
} 
```
单调栈的复杂度：最优 $\Theta(n)$,最差 $\Theta(n^2)$。

---

