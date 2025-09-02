# [JRKSJ R1] 异或

## 题目描述

给你 $n,k$ 和序列 $a_{1,2\dots n}$，选出 $k$ 个**不交**区间 $[l_i,r_i]\subseteq[1,n]$，求出
$$\max_{l_i,r_i}\sum_{i=1}^k\bigoplus_{j=l_i}^{r_i}a_j$$

式中 $\oplus$ 表示二进制异或运算。

**保证数据随机。**

## 说明/提示

对于 $100\%$ 的数据，$1\le k\le n\le 3000$，$0\le a_i\le 10^{9}$。**保证数据随机。**

本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $30$ | $k\le3$ | $5$ |
| $2$ | $500$ | $a_i\le10^7$|  $10$ |
| $3$ | $1000$ | 无 |  $10$ |
| $4$ | $1500$ | 无 |  $15$ |
| $5$ | $2000$ | 无 |  $15$ |
| $6$ | $2500$ | 无 | $20$ |
| $7$ | $3000$ |  无|  $25$ |
#### 样例 1 解释
序列的三个区间分别为:
$$2,1,[3,4],[4],[4]$$
所得的三个区间的异或和之和为 $7+4+4=15$.

## 样例 #1

### 输入

```
6 3
2 1 3 4 4 4```

### 输出

```
15```

## 样例 #2

### 输入

```
7 2
3 4 5 6 7 8 9```

### 输出

```
24```

# 题解

## 作者：cyffff (赞：8)

[$\text{Link}$](https://www.luogu.com.cn/problem/P7335)
## 题意

给你 $n,k$ 和序列 $a_{1,2\dots n}$，选出 $k$ 个**不交**区间 $[l_i,r_i]\subset[1,n]$，求出
$$\max_{l_i,r_i}\sum_{i=1}^k\bigoplus_{j=l_i}^{r_i}a_j$$

$1\le k\le n\le 3000,0\le a_i\le 10^9$。

**保证数据随机。**

## 思路
$\text{Update 2022.4.22}$：重构全文。
### $\text{Subtask 1}$
$O(n^{2k})$ 暴力寻找左右端点即可。

### $\text{Subtask }2 \sim4$
我们首先思考怎么处理 $k=1$ 的情况，这是一个经典问题。

设 $p_i=\bigoplus_{j=1}^{i}a_j$，则 $\bigoplus_{j=l}^{r}a_j=p_r\text{ xor }p_{l-1}$，我们考虑对于每个 $r$ 快速找出 $l$ 使得上式最大，对 $p$ 建出 $\text{01Trie}$，在上面贪心地选择不同的儿子即可。

我们设 $f_{l,r}=\displaystyle\max_{l\le i,j\le r}p_i\text{ xor }p_j$，即在 $p_{l,l+1,...,r}$ 中选 $2$ 个数使它们异或和最大。

设处理到第 $i+1\sim n$ 个数，第 $j\sim k$ 个区间的答案为 $dp_{i,j}$，则 $dp_{i,j}=\displaystyle\max_{k=i}^{n-1}(dp_{k,j+1}+f_{i,k+1})$。

暴力处理，时间复杂度 $O(n^3)$。
### $\text{Subtask }5\sim7$
发现上面的状态转移方很难优化，因为 $f_{i,k+1}$ 是变化的，如果 $k=f_{i,k+1}$ 不变的话，$dp_{i,j}=\displaystyle\max_{k=i}^{n-1}(dp_{k,j+1}+f_{i,k+1})=\displaystyle\max_{k=i}^{n-1}(dp_{k,j+1})+k$.

于是我们打一个表观察一下发现 $i$ 固定时，对于 $k\in[i,n]$，$f_{i,k}$ 不同的值很少，于是我们可以想到把相同的 $f_{i,k}$ 压缩起来，对于 $f_{i,k}$ 相同的一段区间 $k\in[l,r]$，我们求出 $f_{i,l}+\displaystyle\max_{i=l}^rdp_{i,j+1}$ 即可。

我们发现 $f$ 数组单调不递减，$dp$ 数组单调不递增，于是上面的式子就等价于 $dp_{i,j}=\displaystyle\max_{l,r}(f_{i,l}+dp_{l,j+1})$。

现在我们来证明这个算法的复杂度正确。

由于数据随机生成，当我们插入一个数时，设此时已经插入 $m$ 个数，这时候一共有 $\dfrac {(m+1)m} 2$ 个异或和，这个数可以贡献 $m$ 个异或和。即有 $\dfrac 2 {m+1} $ 的几率成为 $\max$，这个数贡献了 $\dfrac 2 {m+1} $ 的期望。

所以 $f_{i,k}$ 中的数的个数的期望为 $\sum_{i=1}^{n}\dfrac 2 {i}≈2\times\log n$，所以期望时间复杂度为 $O(n^2\log w+nk\log n)$。

期望得分 $100$ 分。

另外，由于数据随机，暴力转移较少的数的 $\text{dp}$ 也可以过，对策在考虑。

具体实现见以下代码（我很久以前写的，有点丑请见谅）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int maxn;
struct trie{//01-Trie
	int cnt;
	int son[90005][2];
	trie(){
		cnt=1;
	}
	void clear(){
		for(int i=1;i<=cnt;i++){
			son[i][0]=son[i][1]=0;
		}
		cnt=1;
	}
	void insert(int x){
		int rt=1;
		for(int i=29;i>=0;i--) {
			if(!son[rt][(x>>i)&1])
				son[rt][(x>>i)&1]=++cnt;
			rt=son[rt][(x>>i)&1];
		}
	}
	int find(int x){
		int rt=1,ans=0;
		for(int i=29;i>=0;i--){
			if(son[rt][!((x>>i)&1)]) rt=son[rt][!((x>>i)&1)],ans+=1<<i;
			else rt=son[rt][(x>>i)&1];
		}
		return ans;
	}
}t;
struct line{
	int l,r;
	int val;
	line(){
		l=r=val=0;
	}
	line(int a,int b,int c){
		l=a,r=b,val=c;
	}
};
struct array{
	line s[100];
	int len;
	array(){
		len=0;
	}
	int operator[](const int &x){
		return s[x].val;
	}
	inline void init(int i){
		len=1;
		s[1].l=0;
		s[1].r=i;
		s[1].val=0;
	}
	inline void insert(int x,int v){//压缩ans数组
		if(v==s[len].val){
			s[len].r=x;
		}else{
			len++;
			s[len].l=x;
			s[len].r=x;
			s[len].val=v;
		}
	}
	inline int top(){
		return s[len].val;
	}
}ans[3005];
int a[3005];
int n,k;
void init(){//预处理ans
	for(int i=0;i<=n;i++){
		t.clear();
		t.insert(a[i]);
		ans[i].init(i);
		for(int j=i+1;j<=n;j++){
			int now=t.find(a[j]);
			ans[i].insert(j,max(ans[i].top(),t.find(a[j])));
			t.insert(a[j]);
		}
	}	
}
namespace IO{
	//read()
}using namespace IO;
ll dp[3005][2];
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)
		a[i]=read()^a[i-1];
	init();
	for(int i=k-1;i<=n;i++){
		dp[i][k&1]=ans[i].top();
	}
	for(int d=k-1;d;d--){//dp
		int s=d&1;//滚动数组优化
		for(int l=n;l>=0;l--){
			ll mx=0;
			int r=1;
			mx=ans[l][r]+dp[l][!s];
			for(r++;r<=ans[l].len;r++){
				if(dp[ans[l].s[r].l][!s]+ans[l].top()<mx) break;//剪枝
				mx=max(mx,dp[ans[l].s[r].l][!s]+ans[l][r]);
			}
			dp[l][s]=mx;
		}
	}
	cout<<dp[0][1];
}
```
再见 qwq~

---

## 作者：hegm (赞：5)

### [[JRKSJ R1] 异或](https://www.luogu.com.cn/problem/P7335)

考虑暴力 dp。

先把序列上的点变成前缀异或和。

$f_{i,j}$ 表示 $1\sim i$ 选择了 $j$ 个区间，答案最大是多少。

转移：$f_{i,j}=\max\limits_{k=0}^{i} f_{k,j-1}+{mx}_{k,i}$

其中 $mx_{i,j}$ 表示在 $i\sim j$ 区间选择两个点使得 $a\oplus b$ 最大。

考虑如何求出 $mx$，假如现在已经将 $1\sim i$ 的所有区间求出来了，现在要求出 $[1,i]\sim i+1$ 考虑从后向前一个个的加入节点，每次加入的时候求出和 $i+1$ 的最大异或对，然后和 $mx_{k,i}$ 拼起来，就能求出 $mx_{k,i+1}$。

然后考虑优化，跑一个大一点的暴力就会发现 $mx$ 数组有很长的段是同一个值，所以不妨考虑将同一段的 $mx_{k,i}$ 压起来。

那么对于 $mx_{k,i}(l\sim r)$ 相同的转移，容易发现，$f_{r,j-1}$ 一定是最优解，因为 $f$ 数组一维单调不降。

注意，这道题目卡空间的同时又要开 long long（空间复杂度 $n^2$），因此需要对 dp 转移进行滚动数组，具体的，对于 j 那一维，在最外层枚举然后滚掉就好。

总体复杂度是 $n^2 \log n$
 级别的。
### CODE

```c++
#include<bits/stdc++.h>
#define N 3005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,k,a[N],mx[N][N],num[N];
long long f[N][2];
struct len
{
	int l,r,w;
}s[N][N];
signed main()
{
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=(read()^a[i-1]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i-1,p=0;j>=0;j--)
		{
			if((a[i]^a[j])>p)p=(a[i]^a[j]);
			mx[j][i]=max(mx[j][i-1],p);
		}
	}
	for(int i=1;i<=n;i++)
	{
		s[i][1].l=0;s[i][1].r=0;
		s[i][1].w=mx[0][i];num[i]=1;
		for(int j=1;j<i;j++)
		{
			if(mx[j][i]==mx[j-1][i])s[i][num[i]].r++;
			else 
			{
				s[i][++num[i]].l=j;
				s[i][num[i]].r=j;
				s[i][num[i]].w=mx[j][i];
			}
		}
	}
	for(int j=1;j<=k;j++)
	{
		for(int i=1;i<=n;i++)
		{
			f[i][j%2]=0;
			for(int x=1;x<=num[i];x++)
			{
				f[i][j%2]=max(f[i][j%2],f[s[i][x].r][(j%2)^1]+s[i][x].w);
			}
		}
	}
	cout<<f[n][k%2]<<"\n";
	return 0;
}

```

---

## 作者：Qcfff (赞：3)

$O(n^2k)$ dp 是简单的，$dp(i,j)$ 为前 $i$ 个数选出 $j$ 段不相交子段的答案，有 

$$
dp(i,j)=\begin{cases}
\max(dp(i-1,j),\max\limits_{d=1}^i\{dp(d-1,j-1)+\bigoplus\limits_{p=d}^ia_p\}) & j>0
\\
0 & j=0
\end{cases} 
$$

注意到数据随机，那么感性理解，大概要把 $k$ 段平均分布一下，转移时若枚举更大的段就会更不可能成为答案。那么转移时候的 $d$ 只枚举 $\max(0,i-f\times\lfloor\frac{n}{k}\rfloor)\sim i$ 即可，$f$ 是选择的一个常数，复杂度 $O(n^2f)$。实测 $f=5$ 就能通过。

---

## 作者：intel_core (赞：1)

我们先从基本的 $O(n^3)$ 暴力开始：

令 $f_{i,j}$ 表示选到 $a_i$，一共选了 $j$ 个区间，选出区间的最大值。

有两种转移，$f_{i-1,j}\to f_{i,j}$ 和 $f_{k,j-1}\oplus (s_i\oplus s_k)\to f_{i,j}$。

这个 $\text{DP}$ 看上去并没有什么可以优化的方式；注意到只有 $(s_i\oplus s_k)$ 的后缀最大值才有更新 $f_{i,j}$ 的意义。

考虑后缀最大值的出现的概率，注意到 $s_i \oplus s_k$ 成为后缀最大值的概率是 $\frac{1}{i-k+1}$，所以后缀最大值的期望个数就是 $O(\ln n)$。

所以只记录每个 $i$ 的转移点转移即可，复杂度 $O(n^2 \ln n)$。

---

## 作者：xiao7_Mr_10_ (赞：0)

注意到问题具有无后效性，考虑动态规划。

易得设 $f(i,j)$ 为前 $i$ 个数中选取 $j$ 个区间的最大值，显然答案此时为 $f(n,k)$。

注意到每次转移都是一段连续的区间，考虑枚举一点 $k$ 使得 $k<i$ 顾转移为 $f(i,j)=f(k,j)+g(k+1,j)$ 其中 $g(l,r)$ 表示其区间内一段区间的异或和的最大值。

注意到可以前缀异或和，这样就把找区间改为找两个数的异或和的最大值，简单预处理 $g$ 即可。

考虑优化，注意到数据随机，然后就发现 $g$ 有很长一段的值是连续的，考虑直接合并这些连续段。

注意到期望段数为 $\log n$，总的复杂度为 $O(n^2 \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e3+5;
#define int long long
#define mp make_pair
int n,k,a[N],sum[N],f[N][2],g[N][N];
vector <pair<int,int> > e[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 1;i <= n;i++)cin >> a[i];
	for(int i = 1;i <= n;i++)sum[i]=sum[i-1]^a[i];
	for(int i = 1;i <= n;i++){
		int ans=0;
		for(int j = i-1;j >= 0;j--){
			ans=max(ans,sum[i]^sum[j]);
			g[j+1][i]=max(g[j+1][i-1],ans);
		}
	}
	for(int i = 1;i <= n;i++){
		int r=i;
		for(int j = i-1;j >= 1;j--){
			if(g[j][i]!=g[j+1][i]){
				e[i].push_back(mp(j+1,r));
				r=j;
			}
		}
		e[i].push_back(mp(1,r));
	}
	int now=1,last=0;
	for(int i = 1;i <= k;i++){
		for(int j = 1;j <= n;j++)
			for(auto it:e[j])
				f[j][now]=max(f[j][now],f[it.second-1][last]+g[it.second][j]);
		swap(now,last);
	}
	cout << f[n][last];
	return 0;
}
```

---

## 作者：tribool4_in (赞：0)

首先考虑 dp，设 $dp_{i,j}$ 表示前 $i$ 项中选出 $j$ 个区间的答案，$\displaystyle dp_{i,j}=\max_{l<i}(dp_{l,j-1}+f_{l+1,j})$，其中 $f$ 表示区间内最大的区间异或和。

考虑求 $f$。显然考虑前缀异或和，转化为最大化两数异或值，可以直接插入 Trie 树上做，不过多了个 $\log V$。可以考虑换个枚举顺序，有 $\displaystyle f_{i,j}=\max_{i\le k<j}(f_{i,j-1},a_k\oplus a_j)$，枚举 $j$ 然后倒序枚举 $i$ 即可 $O(n^2)$ 求出。

这个 dp 是 $O(n^2k)$ 的。首先容易不小心想到 wqs 二分，但是这玩意并不是凸函数，炸的很彻底。考虑如何优化，发现难处理的地方在于 $f_{l+1,j}$ 会变化。考虑到数据随机，把 $f_{i,j}$ 固定 $j$ 关于 $i$ 的值打个表，发现其有大量连续相同数值，段数约为 $O(\ln n)$。同时 $dp_{l,j-1}$ 关于 $l$ 是单调递增的。因此可以预处理出 $f$ 的连续段，转移时对于每个连续段直接将 $l$ 取到最右端。总复杂度变为 $O(n^2+nk\ln{n})$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e3 + 10;
int n, k, a[N], s[N], mx[N][N], dp[N][2];
vector<pair<int, int>> v[N];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], s[i] = s[i - 1] ^ a[i];
    for (int i = 1; i <= n; i++) {
        int x = 0;
        for (int j = i - 1; j >= 0; j--) {
            x = max(x, s[i] ^ s[j]);
            mx[j + 1][i] = max(mx[j + 1][i - 1], x);
        }
    }
    for (int i = 1, r; i <= n; i++) {
        r = i;
        for (int j = i - 1; j >= 1; j--)
            if (mx[j][i] != mx[j + 1][i]) v[i].emplace_back(j + 1, r), r = j;
        v[i].emplace_back(1, r);
    }
    for (int p = 1; p <= k; p++) {
        for (int i = 1; i <= n; i++) {
            for (auto [l, r] : v[i]) dp[i][p & 1] = max(dp[i][p & 1], dp[r - 1][p & 1 ^ 1] + mx[r][i]);
        }
    }
    cout << dp[n][k & 1] << '\n';
    return 0;
}
```

---

