# Attribute Checks

## 题目描述

Imagine a game where you play as a character that has two attributes: "Strength" and "Intelligence", that are at zero level initially.

During the game, you'll acquire $ m $ attribute points that allow you to increase your attribute levels — one point will increase one of the attributes by one level. But sometimes, you'll encounter a so-called "Attribute Checks": if your corresponding attribute is high enough, you'll pass it; otherwise, you'll fail it.

Spending some time, you finally prepared a list which contains records of all points you got and all checks you've met. And now you're wondering: what is the maximum number of attribute checks you can pass in a single run if you'd spend points wisely?

Note that you can't change the order of records.

## 说明/提示

In the first test, it's optimal to spend each point in Strength, so you'll fail $ 2 $ Intelligence checks but pass $ 3 $ Strength checks.

In the second test, you'll fail both checks, since the first point you get comes after the checks.

In the third test, one of the optimal strategies is:

1. spend the first point on Intelligence;
2. spend the second point on Strength;
3. spend the third point on Strength;

 As a result, you'll pass $ 2 $ Intelligence checks $ r_3 $ and $ r_9 $ and $ 2 $ Strength checks $ r_7 $ and $ r_8 $ .

## 样例 #1

### 输入

```
10 5
0 1 0 2 0 -3 0 -4 0 -5```

### 输出

```
3```

## 样例 #2

### 输入

```
3 1
1 -1 0```

### 输出

```
0```

## 样例 #3

### 输入

```
9 3
0 0 1 0 2 -3 -2 -2 1```

### 输出

```
4```

# 题解

## 作者：Phrvth (赞：11)

# CF2025D

这题只要想到 dp，就简单了。

很容易发现，智力值+体力值等于总值，所以我们只需要把一维写进 dp，考虑记 $f_{i,j}$ 表示当前考虑到前 $i$ 个点，智力值为 $j$，体力值为 $cnt-j$ 时的最大答案，其中 $cnt$ 是当前的总值。

那我们分类考虑一下。

+ 当 $r_i=0$ 的时候。

那我们就会有两种选择，增加体力值或者增加智力值。容易写出他们的转移方程。

如果增加体力值的话，就是从 $f_{i-1,j}$ 转移过来，否则就是从 $f_{i-1,j-1}$ 转移过来，两者取个 $\max$ 即可，即 $f_{i,j}=\max \{f_{i-1,j},f_{i-1,j-1}\}$。

+ 当 $r_i > 0$ 的时候。

这是一个智力检查，直接考虑所有 $x\ge r_i$，将 $f_{i,x}=f_{i-1,x} + 1$ 即可。

+ 当 $r_i<0$ 的时间。

这是一个体力检查，考虑当前的体力值为 $cnt-x$，即当 $cnt-x\ge |r_i|$ 的时候 $x$ 有贡献，化简一下就是 $x\le cnt - |r_i|$。所以把这些 $x$ 的 $f_{i,x}=f_{i-1,x} + 1$ 即可。

这样的话就是 $\mathcal{O}(nm)$ 的，无法通过。

考虑到只有 $m$ 个位置 $r_i=0$ 的，又观察到 $m$ 很小，所以我们可以 $\mathcal{O}(m^2)$ 的转移，也就是保持一开始的做法不变，但是其他的位置就必须 $\mathcal{O}(1)$ 或者 $\mathcal{O}(\log n)$ 了。

很容易观察到修改的是一段区间，我们可以使用线段树进行修改，但是太麻烦了，考虑直接差分。

但是当我们遇到 $r_i=0$ 的时候我们需要原数组而不是差分数组，这个时候直接把差分数组推平即可，转移完了清零即可。

所以时间复杂度降到了 $\mathcal{O}(m^2+n)$。考虑空间限制。

容易发现修改操作之和 $i-1$ 的值有关，$r_i=0$ 时的操作也只从 $i-1$ 转移过来，所以可以直接滚动数组，不过记得 $r_i=0$ 时的操作的第二维需要倒序遍历。

---

## 作者：Super_Cube (赞：10)

# Solution

设 $dp_i$ 表示第一维数值为 $i$ 能得到的最大值，$s$ 当前 $r_i$ 为 $0$ 的数量。

若 $r>0$，有转移：$\forall i\in[r,s],dp_i\gets dp_i+1$。

若 $r<0$，有转移：$\forall i\in[0,s+r],dp_i\gets dp_i+1$。

若 $r=0$，有转移：$\forall i\in[1,s],dp_i\gets\max(dp_i,dp_{i-1})$。

区间加用差分维护，$r=0$ 暴力修改。

时间复杂度：$O(n+m^2)$。

# Code
```cpp
#include<bits/stdc++.h>
int dp[5005];
int d[5005];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	memset(dp+1,192,m<<2);
	for(int i=1,x,s=0;i<=n;++i){
		scanf("%d",&x);
		if(x>0){
			if(x<=s)++d[x],--d[s+1];
		}else if(x){
			if(0<=s+x)++d[0],--d[s+x+1];
		}else{
			++s;dp[0]+=d[0];
			for(int j=1;j<=s;++j)dp[j]+=(d[j]+=d[j-1]);
			for(int j=s;j;--j)dp[j]=std::max(dp[j],dp[j-1]);
			memset(d,0,s+1<<2);
		}
	}
	dp[0]+=d[0];
	for(int j=1;j<=m;++j)dp[j]+=(d[j]+=d[j-1]);
	printf("%d",*std::max_element(dp,dp+m+1));
	return 0;
}
```

---

## 作者：Misaka屮Mikoto (赞：4)

# CF2025D Attribute Checks
### 题目大意

给定两个正整数 $n$ 和 $m$，以及一个长度为 $n$ 的数组 $r$。保证 $-m \le r_i \le m$，并且恰好有 $m$ 个 $r_i$ 为 $0$。

你有两个初始值均为 $0$ 的变量 $I$ 和 $S$，接下来在第 $i$ 秒中（$1 \le i \le n$）将发生如下事件：

* 如果 $r_i > 0$ 并且此时 $I \ge |r_i|$ ，则你获得一分。

* 如果 $r_i < 0$ 并且此时 $S \ge |r_i|$，则你获得一分。

* 如果 $r_i = 0$，则你需要从以下两种决策中选择一种：将 $I$ 的值增加 $1$，或者将 $S$ 的值增加 $1$。

求你最终能获得分数的**最大值**。

##### 数据范围
$0\leq m \leq 5000$
$m < n \leq 2\cdot 10^6$
##### 时空限制
* 2.5 seconds
* 512 megabytes
### 思路
注意到这里 $m$ 的范围和时间限制，明显可以考虑 $O(m^2)$ 时间复杂度的算法。

我们发现，只有当 $r_i = 0$ 的时候才能使 $S,I$ 的值改变，换言之，每次在 $r_i$ 处进行决策。
考虑dp，我们可以建立数组 $dp[i][j]$ 表示 $I=i ,S=j$ 时候的获得分数的最大值，显然，这时候是第 $i+j$ 次决策。

每一次决策我们可以从 $dp[i-1][j]$ 和 $dp[i][j-1]$ 转移而来。

我们将 $0$ 定义为“决策数”
每一次决策过后，会增加一些分数，如果 $I$ 增加为 $I+1$，那么增加的分数将会是在这个“决策数”之后的 $r_i=I+1$ 的数量，因为当上一次对 $I$ 进行增加时，已经将 $r_i=I$ 所获的分数加过了。

对于获得每一次决策后，这个“决策数”后面每一个数字的数量 $m^2$ 打桶即可。

```c++
	#include<bits/stdc++.h>
using namespace std;
#define ll long long
int pot1[5010][5010],pot0[5010][5010];int n,m,cnt;
//pot1[i][j]代表第m-i次决策的r后面大于0的数字j 的个数
//pot1[i][j]代表第m-i次决策的r后面小于0的数字，绝对值j 的个数
ll dp[5010][5010];
int main(){
    //freopen("read.in","r",stdin);
    stack<ll>st;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        ll l;
        scanf("%lld",&l);
        st.push(l);
    }
    while(!st.empty()){
        int l=st.top();
        st.pop();

        if(l==0){
            cnt++;
            for(int i=0;i<=m;++i)pot1[cnt][i]=pot1[cnt-1][i],pot0[cnt][i]=pot0[cnt-1][i];
        }
        if(l<0)pot0[cnt][-l]++;
        if(l>0)pot1[cnt][l]++;
    }
    for(int i=1;i<=m;++i){
        for(int j=0;j<=m;++j){
            if(j-1>=0)dp[j][i-j]=max(dp[j][i-j],dp[j-1][i-j]+pot0[m-i][j]);
            if(i-j-1>=0)dp[j][i-j]=max(dp[j][i-j],dp[j][i-j-1]+pot1[m-i][i-j]);
        }
    }
    ll mxn=0;
    for(int i=0;i<=m;++i)mxn=max(mxn,dp[i][m-i]);
    printf("%lld",mxn);
}

```

---

## 作者：lijunxi20231818 (赞：3)

# 思路

本题最难的部分就是想到用 dp，~~除非你直接看算法标签。~~

## 部分分

### dp 状态

我们发现对于时刻 $i \in [1,n],I+S=\sum\limits_{j=1}^i[r_i=0]$，所以我们可以只在 dp 状态中塞一个值，这里我塞个 $I$。同时记录 $P=I+S=\sum\limits_{j=1}^i[r_i=0]$，就可以得到 $S$ 的值。

设 $dp_{i,I}$ 表示考虑到第 $i$ 个 $r$，此时智力值（变量 $I$）为 $I$ 时的最大得分。

### dp 转移

分类讨论。

- $r=0$ 时，可以随便选一个值（智力/力量）增加 $1$，

  - 增加智力值时，$dp_{i,I}\leftarrow dp_{i-1,I-1}$。
  - 增加力量值时，$dp_{i,I}\leftarrow dp_{i-1,I}$。
    
  所以 $\forall I \in [1,n],dp_{i,I}\leftarrow \max{\{dp_{i-1,I-1},dp_{i-1,I}\}}$。

- $r>0$ 时，得分需要满足 $I \ge r$，即：

  - $\forall I \in [r,P],dp_{i,I} \leftarrow dp_{i-1,I}+1$
  - $\forall I \in [0,r-1],dp_{i,I} \leftarrow dp_{i-1,I}$
  
- $r<0$ 时，得分需要满足 $S=P-I \ge -r \iff I \leq P + r$。

  - $\forall I \in [0,
P+r],dp_{i,I} \leftarrow dp_{i-1,I}+1$
  - $\forall I \in [P+r+1,P],dp_{i,I} \leftarrow dp_{i-1,I}$

这种做法的时间复杂度、空间复杂度都是 $\Omicron(nm)$，会炸掉。

## 正解

考虑优化这个东西，由于每次 $dp_{i,I}$ 只会从第一维下标为 $i-1$ 的东西转移，所以直接滚动数组优化掉第一维。

然后对于 $r \ne 0$ 的情况，都是对于一个区间进行修改，直接差分解决掉。

对于 $r=0$ 的情况，直接暴力解决（这种情况次数只有 $m$ 次），注意要把差分给同步到 $dp$ 上，最后将差分数组归零。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {int x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
const int maxn = 2e6;
const int maxm = 5005;
int n, m;
int dp[maxn];
int d[maxn];
int p;//p->i+s
signed main(){
	n = read(), m = read();
	for(int i = 1, r; i <= n; i++){
		r = read();
		if(r > 0){
			if(r <= p){
				d[r]++;
				d[p + 1]--;
			}
		}
		if(r < 0){
			if(r + p >= 0){
				d[0]++;
				d[r + p + 1]--;
			}
		}
		if(r == 0){
			p++;
			for(int j = 0; j <= p; j++){//先对差分作前缀和，同步到dp
				if(j) d[j] += d[j - 1];
				dp[j] += d[j];
			}
			for(int j = p; j >= 1; j--){//暴力max
				dp[j] = max(dp[j], dp[j - 1]);
			}
			for(int j = 0; j <= p; j++){//将差分归零
				d[j] = 0;
			}
		}
	}
	int mx = -1;
	for(int j = 0; j <= p; j++){
		if(j) d[j] += d[j - 1];
		dp[j] += d[j];
		mx = max(mx, dp[j]);
	}
	cout << mx;
	return 0;
}
```

---

## 作者：MightZero (赞：1)

### Solution

首先我们可以发现 $n$ 的范围并不十分重要，因为两种属性点数只会在 $r_i = 0$ 的位置改变，这样的位置至多只有 $m$ 个，下文将其称为**关键点**；第 $i$ 个关键点的位置设为 $p_i$。

考虑 `DP`，设 $dp_{i,j}$ 表示在第 $i$ 个关键点**前**将 $j$ 个属性点分配给智力的情况下能通过检查点的最大数量；可以知道对于 $dp_{i,j}$，分配给力量的属性点数量为 $i-1-j$。

转移方程如下：
$$dp_{i,j}=\max(dp_{i-1,j},dp_{i-1,j-1})+\sum_{k=p_{i-1}+1}^{p_i-1}({[r_k>0]\times[r_k\geq j]}+{[r_k<0]\times[-r_k\geq i-1-j]})$$

具体实现上可以用桶或者二分查找确定满足约束条件的检查点数量。

时间复杂度 $O(n+m^2\log n)$ 或 $O(n+m^2)$。

**注意 $n$ 的范围，数组大小要开够！** ~~某人数组开小炸了6发还没发现~~

### Code

``` cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = long long;
inline ll read()
{
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
	return x*f;
}
inline void write(ll x)
{
	if(x<0){putchar('-');x=-x;}
	if(x%10==x){putchar(x+'0');return;}
	write(x/10);putchar(x%10+'0');
}
const ll N=2e6+5,M=5e3+5;
ll n,m,r[N],dp[M][M],ans=0;
vector<ll> t1,t2;
signed main()
{
	n=read(),m=read(),ans=0;
	t1.clear(),t2.clear();
	loop(i,1,n)r[i]=read();
	ll pm=1;
	loop(i,1,n)
	{
		if(r[i]==0)
		{
			sort(t1.begin(),t1.end());sort(t2.begin(),t2.end());
			loop(j,0,pm-1)	
			{
				dp[pm][j]=max(dp[pm][j],max(dp[pm-1][j],dp[pm-1][max(0ll,j-1)])+
				(t1.end()-lower_bound(t1.begin(),t1.end(),-j))+
				(t2.end()-lower_bound(t2.begin(),t2.end(),j-pm+1)));
			}
			t1.clear();t2.clear();
			pm++;
		}
		else if(r[i]>0)t1.push_back(-r[i]);
		else if(r[i]<0)t2.push_back(r[i]);
	}
	sort(t1.begin(),t1.end());sort(t2.begin(),t2.end());
	loop(j,0,pm-1)	
	{
		dp[pm][j]=max(dp[pm-1][j],dp[pm-1][max(0ll,j-1)])+
		(t1.end()-lower_bound(t1.begin(),t1.end(),-j))+
		(t2.end()-lower_bound(t2.begin(),t2.end(),j-pm+1));
	}
	loop(i,0,m)ans=max(ans,dp[pm][i]);
	write(ans);
	return 0;
}
```

---

## 作者：litjohn (赞：0)

声明：本题解中认为各个变量及 `dp` 数组属于代码片段，所以用代码块包裹且不使用 latex。

好的。首先我们应该先看题。

### 题意
对题意可能会出现的一个误解是：认为一次检查失败，整个过程立刻停止，然后使用贪心。手摸样例就可以发现这个错误。

正确的题意是：任意检查失败之后依然可以继续获取后面的点数和进行检查，仅仅是这一次检查不计入通过的检查总数。

然后，想想怎么做。
### 思路 && 算法选择
对于这种题，我们一时难以想到一个最优的分配点数的策略，无法使用贪心。

对于这种复杂的多阶段决策，一般可以考虑动态规划。

一个简单的想法是，设 `dp[i][j]` 为现在已经进行了前 `i` 个操作，将 `j` 个点数分配在智力（也可以是力量，但是这里以智力为例）上通过的最多测试数目。

考虑状态转移方程。

显然的，对于一次获得点数的操作，立刻分配点数一定不劣于之后分配点数。而分配点数可以分到智力或力量上，我们可以取最大值。

于是就有这个转移方程：
```plaintext
dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]);
//when r[i] == 0
```

而当操作是一次检测时，分配了足够点数的状态通过的检测次数会加一。

方程是这个：（以智力检测为例，力量检测同理）
```plaintext
//cnt 是之前获得的总点数
for (int j = r[i]; j <= cnt; ++j) {
  dp[i][j] = dp[i - 1][j] + 1;
}
//when r[i] > 0
```
上面的做法显然是无法通过的，时间和空间都会超限，我们需要优化。

### 空间优化
空间的优化是平凡的。用滚动数组或降维优化可以轻易地优化到 $O(m)$。

注意降维优化时 `r[i] == 0` 的操作 `j` 的枚举要反向（类似于 01 背包），否则前面的转移会改掉后面转移依赖的数据，就会 WA 掉。

然后，我们就要考虑优化时间。

### 经典错解一则
如果你像我一样没有完全想明白状态转移方程就动手，容易忽略获得点数时也要进行状态转移，然后就会想到用树状数组优化。

但是这是错的。树状数组无法简单的维护 chechmax 操作。~~吉司机线段树属于山本~~

### 真正的优化
注意到 `m` 的数据范围很小。所以获得点数的操作数量也很少。对于这种操作，我们可以使用 $O(m)$ 的暴力做法。

对于另外两种操作，使用差分维护即可。在获得点数的操作时，先将差分推平算出原数组，然后暴力做即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int dp[5005], d[5005], n, m;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	fill(dp + 1, dp + m + 1, -1e9);
	
	for(int i = 1, s = 0; i <= n; ++i) {
		int x;
		cin >> x;
		if (x > 0) {
			if (x <= s) {
				++d[x], --d[s + 1];
			}
		} else if(x < 0) {
			if (0 <= s + x) {
				++d[0], --d[s + x + 1];
			}
		} else {
			++s;
			dp[0] += d[0];
			for (int j = 1; j <= s; ++j) {
				d[j] += d[j - 1];
				dp[j] += d[j];
			}

			for (int j = s; j; --j) {
				dp[j] = max(dp[j], dp[j - 1]);
			}
			
			fill(d, d + s + 2, 0);
		}
	}

	dp[0] += d[0];
	for(int j = 1; j <= m; ++j) {
		d[j] += d[j - 1];
		dp[j] += d[j];
	}
	cout << *max_element(dp, dp + m + 1);
	return 0;
}
```

---

