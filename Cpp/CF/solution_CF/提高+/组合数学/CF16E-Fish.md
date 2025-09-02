# Fish

## 题目描述

 $ n $ fish, numbered from $ 1 $ to $ n $ , live in a lake. Every day right one pair of fish meet, and the probability of each other pair meeting is the same. If two fish with indexes i and j meet, the first will eat up the second with the probability $ a_{ij} $ , and the second will eat up the first with the probability $ a_{ji}=1-a_{ij} $ . The described process goes on until there are at least two fish in the lake. For each fish find out the probability that it will survive to be the last in the lake.

## 样例 #1

### 输入

```
2
0 0.5
0.5 0
```

### 输出

```
0.500000 0.500000 ```

## 样例 #2

### 输入

```
5
0 1 1 1 1
0 0 0.5 0.5 0.5
0 0.5 0 0.5 0.5
0 0.5 0.5 0 0.5
0 0.5 0.5 0.5 0
```

### 输出

```
1.000000 0.000000 0.000000 0.000000 0.000000 ```

# 题解

## 作者：crescentic (赞：19)

[Fish](https://www.luogu.com.cn/problem/CF16E)

可以去看我整理的[学习笔记](https://www.luogu.com.cn/blog/140643/zhuang-ya-dp-xue-xi-bi-ji)鸭~

**题意简述**：有 $n$ 条鱼，编号从 $1$ 到 $n$。每对鱼相遇的概率是一样的。如果两条标号为 $i$ 和 $j$ 的鱼见面，第一只吃了第二只的概率为 $p[i][j]$，则第二只吃掉第一只的概率为 $1 - p[i][j]$。求每只鱼最后存活在湖里的可能性。

**思路**：

概率 + 状压 $dp$


先看题目范围，明显**状压**，因为题目求每只鱼最后存活的状态，所以把鱼的存活状态压进状态里，因此定义 $dp[i]$ 为出现 $i$ 的局面时的概率（第 $i$ 位为 $0$ 表示第 $i$ 条鱼**死亡**，反之为**存活**）

- 因为顺序递推会因为概率的不确定因素影响结果，所以考虑逆推。

- 先枚举整体状态 $i$，在确定该轮被吃的鱼的编号 $j$，判断是否满足已经被吃的条件(即状态中第 $j$ 位为 $0$)

- 满足上条件后，再枚举吃掉 $j$ 的鱼的编号 $k$，判断是否满足依然存在的条件（即状态中第 $k$ 位为 $1$）

因为任意两条鱼之间的存活概率已经得知，然后任意在存活中的鱼里选择两条鱼的概率为 $(cnt +１) * cnt / 2 $。($cnt$ 为 $i$ 状态下 $1$ 的数量)，因为是倒退，所以前一状态下，鱼 $j$ 是活着的，因此实在 $cnt + 1$ 条雨中选两条鱼。

就可以得出递推式，$i$ 状态的概率加（即前一状态的概率） $*$ （$k$ 吃掉 $j$ 的概率）$*$ (选出 $j$、$k$ 的概率)

所以：
$$ 

dp[i] += dp[i | (1 << (j - 1))] * p[k][j] / (1.0 * (cnt + 1) * cnt / 2.0);
$$

其他讲解都在代码里啦~

**完整代码**：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
double p[25][25],dp[1 << 20];//dp[i],出现i状态的概率（1:这条鱼活着/0:它被吃啦） 
int c(int x) {//计算1的个数 
	int res = 0;
	while(x) {
		res += (x & 1);
		x >>= 1;
	}
	return res;
}
int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			scanf("%lf",&p[i][j]);
	int num = (1 << n) - 1;
	dp[num] = 1;//初始状态，全部鱼都活着的概率为1
	for(int i = num - 1; i; i --) {//倒序枚举状态，鱼越吃越少，1的数量也越来越少……这残忍的现实！ 
		int cnt = c(i);//活着的鱼的数量 
		for(int j = 1; j <= n; j ++) {//枚举这一轮被吃到的鱼的序号 
			if((i & (1 << (j - 1)))) continue;//如果在当前状态下，j为1（鱼没有被吃了），跳过
			for(int k = 1; k <= n; k ++) {//枚举k条鱼吃掉的鱼的编号 
				if(!(i & (1 << (k - 1)))) continue;//如果在当前状态下，k为0（鱼已经被吃了,k吃不到j），跳过
				dp[i] += dp[i | (1 << (j - 1))] * p[k][j] / (1.0 * (cnt + 1) * cnt / 2.0);
				//否则，概率为 当前概率 加上 j位存活时的概率 * k条鱼吃掉j条鱼的概率 * 在所有活着的鱼中恰好选到j,k的概率。 
			}
		}
	}
	for(int i = 0; i < n; i ++) printf("%.6lf ",dp[1 << i]);//只有当前位为1的状态 
	return 0;
}
```



---

## 作者：Fading (赞：8)

状压+概率$dp$。

不过走了弯路。。。

这不是期望，所以用加法原理的时候还要乘上一堆概率才可以。

我一开始设$f[i]$为剩下的鱼状态为$i$的概率。

然后枚举$j
\not\in i$的鱼$j$,$k\in i$的鱼$k$，

$$f[i]=\sum f[i|(1<<j-1)]\times a[k][j]$$

为什么呢？因为**原来鱼群**里少了一条鱼说明这条鱼被**现在鱼群**中的一条鱼吃掉了。

很可惜这是**错**的。

这又为什么呢？因为**原来鱼群**不一定是这两条鱼对战啊！所以这两条鱼对战的概率还需要计算！

由于两条鱼对战的概率是一样的，都为

$$P=\frac 1{[\frac {cnt*(cnt-1)} 2]}$$

其中$cnt$原来鱼群中有多少条鱼。

所以状态转移方程式要这么改：

$$f[i]=\sum f[i|(1<<j-1)]\times a[k][j]\times P$$

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int MAX,n;
double a[21][21],f[530000];
int main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			scanf("%lf",&a[i][j]);
		}
	}
	MAX=(1<<n)-1;f[MAX]=1;
	for (int i=MAX-1;i;i--){
		int cnt=0,tmp=i;
		while (tmp){
			cnt+=(tmp&1);tmp>>=1;//计算现在有多少鱼
		}
		for (int j=1;j<=n;j++){
			if ((1<<j-1)&i) continue;
			for (int k=1;k<=n;k++){
				if (!((1<<k-1)&i)) continue;
				f[i]+=(double)f[i|(1<<j-1)]*a[k][j]/(cnt*(cnt+1)/2);
           //原来的鱼数是现在的cnt+1
			}
		}
	}
	for (int i=1;i<=n;i++){
		printf("%.6lf ",f[1<<i-1]);
	}
}
```


---

## 作者：lotus_grow (赞：6)

题意就是题面，不在赘述。

首先，对于 $n$ 条鱼，它们两两相遇（不重复）的方案数显然为 $n*(n-1)/2$ 。

接着，对于鱼 $i$ 吃掉 鱼 $j$ ，可以分为三个步骤：

1. 鱼 $i$ 与 鱼 $j$ 都在湖里。

1. 鱼 $i$ 与 鱼 $j$ 相遇。

1. 鱼 $i$ 战胜 鱼 $j$ 。

所以鱼 $i$ 吃掉 鱼 $j$ 的概率为 $P=$ $P($鱼 $i$ 与 鱼 $j$ 都在湖里$)$ $*$ $P($鱼 $i$ 与 鱼 $j$ 相遇$)$ $*$ $P($鱼 $i$ 战胜 鱼 $j$ $)$

设 $f[S]$ 为湖中鱼状态为 $S$ 的概率，那么方程就是
 
 $f[S$ ^ $(1<<j)]$ $+=$ $f[S]$ $*$ $a[i][j]$ $/$ $(n*(n-1)/2)$
 
 $(i$ ∈ $S$ && $j$ ∈ $S)$ $(n$ 为 $S$ 二进制下 $1$ 的个数 $)$
 
** 代码**

```cpp
#include<cstdio>

using namespace std;

double f[1<<19];
double a[19][19];
int n,cnt;

int count(int s)
{
	int cnt=0;
	while(s)
	{
		cnt++;s^=s & (-s);
	}
	return cnt;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	scanf("%lf",&a[i][j]);
	f[(1<<n)-1]=1;
	for(int s=(1<<n)-1;s>0;s--)
	if(f[s])
		for(int i=0;i<n;i++)
		if( (1<<i)&s )
			for(int j=0;j<n;j++)
			if(i!=j && ( (1<<j)&s ))
			{
				cnt=count(s);
				if(cnt>1)
				f[s^(1<<j)]+=f[s]*2*a[i][j]/cnt/(cnt-1);
			}
	for(int i=0;i<n;i++)
	printf("%.6lf ",f[1<<i]);
	return 0;
}
```


------------

~~后记（真题面）~~

[![timg.jpg](https://s22.postimg.cc/u39xlhb29/timg.jpg)](https://postimg.cc/image/o2c8oeofx/)
  [![cc9015ef76c6a7efa56cf50df7faaf51f2de66d0.jpg](https://s22.postimg.cc/jhq29iugx/cc9015ef76c6a7efa56cf50df7faaf51f2de66d0.jpg)](https://postimg.cc/image/vjlg3o3p9/)

---

## 作者：Tzs_yousa (赞：4)

### 解题
首先是可以看出为状压 $dp$ ，又发现 $n$ 很小，所以可以状压，压得状态就是鱼此时存活的概率。
```cpp
for (int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> a[i][j];
	dp[(1 << n) - 1] = 1;//千万别写成1<<n,不然只有一位是1其它全是0，这样相当于从第零位到第n-1位都是1 
```

然后对于概率的计算则是需要枚举三重循环，剩余 1 的数量，所有鱼的序号 $j$ ，以及第 $k$ 条对第 $j$ 条产生的贡献。

动态转移方程即表示：$j$ 位存活时的概率 * $k$ 条鱼吃掉 $j$ 条鱼的概率 * 在所有活着的鱼中恰好选到 $j$ ，$k$ 的概率。
```cpp
for (int j = 1; j <= n; j++) //鱼的序号 
		{
			if(!(i & (1 << (j - 1))))//已经被吃掉了 
				for(int k = 1; k <= n; k++) //枚举第k条鱼对这条鱼产生的贡献 
				{
					if(i & (1 << (k - 1)))//没被吃可以用来计算 
						dp[i] += dp[i | (1 << (j - 1))] * a[k][j] * 2.0 / (cnt + 1) / cnt;
				}
		}
```

最后注意是从零输出 $dp_i$ 表示每一条鱼的存活概率。

全套代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
double a[20][20], dp[1 << 20];//状压dp基本操作 
signed main() 
{
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> a[i][j];
	dp[(1 << n) - 1] = 1;//千万别写成1<<n,不然只有一位是1其它全是0，这样相当于从第零位到第n-1位都是1 
	for (int i = (1 << n) - 1; i >= 0; i--) // i是指剩余1的数量 
	{
		int q = i;
		double cnt = 0;
		while(q) 
		{
			cnt += (q & 1);
			q >>= 1;
		}//剩余的个数 
		for (int j = 1; j <= n; j++) //鱼的序号 
		{
			if(!(i & (1 << (j - 1))))//已经被吃掉了 
				for(int k = 1; k <= n; k++) //枚举第k条鱼对这条鱼产生的贡献 
				{
					if(i & (1 << (k - 1)))//没被吃可以用来计算 
						dp[i] += dp[i | (1 << (j - 1))] * a[k][j] * 2.0 / (cnt + 1) / cnt;
				}
		}
	}
	for (int i = 0; i < n; i++) printf("%.6lf ", dp[1 << i]);
	return 0;
}
```

完结撒花！

---

## 作者：fanypcd (赞：2)

简单的状压 DP。

设 $f_S$ 表示当前存活的鱼的集合为 $S$ 的概率。

每次模拟鱼之间战斗的过程，$f_S$ 转移到 $f_{S'}$ 其中 $S'$ 是第 $i$ 条鱼和第 $j$ 条鱼之间战斗，$j$ 出局的集合，设集合中鱼的个数为 $t$。

那么 $f_{S'} = \frac{f_S \times a_{i,j}}{t \times (t-1) \div 2}$。

复杂度 $O(2^n\times n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + (ch - 48);
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define N 18
int n, lg[N];
double a[N][N];
double f[1 << N];
inline int lowbit(int x)
{
	return x & -x;
}
vector<int> tmp;
signed main()
{
	read(n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			scanf("%lf", &a[i][j]);
		}
	}
	f[0] = 1.0;
	for(int state = 0; state < (1 << n); state++)
	{
		tmp.clear();
		for(int i = 0; i < n; i++)
		{
			if(!(state & (1 << i)))
			{
				tmp.emplace_back(i);
			}
		}
		for(auto i : tmp)
		{
			for(auto j : tmp)
			{
				f[state | (1 << j)] += f[state] * a[i][j] / (tmp.size() * (tmp.size() - 1) / 2);
			}
		}
	}
	for(int i = 0; i < n; i++)
	{
		printf("%0.6lf ", f[((1 << n) - 1) ^ (1 << i)]);
	}
	return 0;
}
```

---

## 作者：C锥 (赞：2)

# CF16E Fish

​	状压DP;

​	由于 $ n <= 18 $ ,我们可以状态压缩.

​	一个二进制数第 $ i $ 位为1表示当前第 $ i $ 条鱼还活着.$ f[x] $ 表示当前局面为 $ x $ 的概率是多少.

​	所以我们可以得出初始状态 $ f[1 << n - 1] = 1 $ ,因为刚刚开始所有鱼都活着,概率肯定为1.我们要求的状态是 $ f[x] $, $ x $ 中只有一个1的局面,因为只剩下一条鱼.

​	然后我们开始转移: $ f[x] $  要从 $ f[x | (1 << i)] $ 转移过来, $ x $ 中第$i$为位0,表示第$i$条鱼这次被吃掉了.然后我们需要乘上发生这个事件的概率是多少,注意这里有一个坑点:我一开始只是将$x$中1的个数( $ num $ )统计了出来,然后自然地想到这条鱼被吃的概率就是 $ \frac{1}{num} $ .结果一直不对,后来仔细一想,其实每两条鱼之间都会发生吃或被吃,所以这条鱼被吃的概率应该是 $ \frac{1}{(num + 1){num} / 2} $ .



```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
double f[300005], a[20][20];

int main() {

    cin >> n;
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= n; j++) cin >> a[i][j];
    f[(1 << n) - 1] = 1;
    for(int i = (1 << n) - 1;i >= 1; i--) {
        for(int j = 0;j < n; j++) {
            if(!(i & (1 << j))) {
                int k = i | (1 << j), num = 0; double tmp = 0; 
                for(int l = 0;l < n; l++) {
                    if(k & (1 << l)) tmp += a[l + 1][j + 1], num ++;
                }
                f[i] += f[k] * tmp * 1.0 / (num * (num - 1) / 2); 
                //上面的num是x中1的个数,这里的num是x | (1 << j)里面1的个数,所以稍微有点区别
            }
        }
    }
    for(int i = 0;i < n; i++) printf("%.6lf ", f[(1 << i)]);

    return 0;
}
```



---

## 作者：Arghariza (赞：2)

茫茫大海中两只鱼相遇并相残需要两步：相遇、相残

如果剩下 $k$ 只鱼，那么相遇的几率就是$\frac{1}{C_{k}^{2}}=\frac{2}{k(k-1)}$

相残的概率已经给出，如果输入的矩阵为$s$，两只鱼$u,\,v$相遇了，相残中$v$吃掉$u$的概率为$s_{v,u}$ 

数据范围：$1\le n\le 18$ ~~，理想的状态压缩~~。

不过听说神仙 sinsop90 用深搜过了。

设$dp_q$为状态为$q$的概率，$u$是长度为$n$的二进制数，第$k$位表示第$k$只鱼是否活着，总鱼数就是 $q$ 中 $1$ 的个数。

接下来遍历每只活下来的鱼$q_p$，状态可以转移为$v=u-(1<< p-1)$，即让这只鱼$(i)$死掉的状态，由前面的推导，转移方程为：

$$dp_v=dp_u\cdot\frac{2}{k(k-1)}\cdot s_{j,i}$$

$j$为所有可以吃掉$i$的鱼，显然所有鱼活着的时候$dp_{(1<<n)-1}=1$ 

最后剩下鱼$k$的概率就是$dp_{1<<k-1}$

```cpp
#include <bits/stdc++.h>
#define maxn 19
using namespace std;

int n;
double s[maxn][maxn], dp[1 << maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%lf", &s[i][j]);
		}
	}
	dp[(1 << n) - 1] = 1;// 初始化
	for (int u = (1 << n) - 1; u >= 1; u--) {// 枚举每一种状态
		int tot = 0;// 数活着的鱼的个数
		for (int i = 1; i <= n; i++) {
			tot += u >> i - 1 & 1;// 如果这个鱼活着就统计
		}
		for (int i = 1; i <= n; i++) {
			if (u >> i - 1 & 1) {// 如果这个鱼还活着
				int v = u - (1 << i - 1);// 让这个鱼死掉的状态
				for (int j = 1; j <= n; j++) {// 遍历让这个鱼死掉的鱼
					if (u >> j - 1 & 1 && i != j) {// 如果让这个鱼死掉的鱼还在并且不是同一只鱼
						dp[v] += 2 * dp[u] * s[j][i] / tot / (tot - 1);// 状态转移
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%.6f ", dp[1 << i - 1]);// 输出
	}
	return 0;
}
```

---

## 作者：xukuan (赞：1)

概率期望dp的状态一般设置成：当前状态为i，到最终状态的期望或概率

一看数据范围，$1 \leq n \leq 18$，果断状压

用$f_i$表示当前状态为i，到只剩一条鱼的概率

我们看i吃j的概率是多少：

1. i和j都在鱼群里
2. i遇上了j（估计很多人会漏掉这个问题）
3. i吃掉了j

所以概率是$\frac{1}{\frac{1}{2}count(s)count(s-1)}*a_{i,j}$

直接上代码。

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=20;
ll n;
double a[N][N],f[1<<N];

inline ll lowbit(ll x){
	return x&(-x);
}

inline ll count(ll x){
	ll ans=0;
	for(ll i=x; i; i-=lowbit(i)) ans++;
	return ans;	
}

int main(){
	scanf("%lld",&n);
	for(ll i=0; i<n; i++){
		for(ll j=0; j<n; j++) scanf("%lf",&a[i][j]);
	}
	f[(1<<n)-1]=1;
	for(ll i=(1<<n)-1; i; i--){
		ll sum=count(i);
		for(ll j=0; j<n; j++){
			if(i&(1<<j)){
				for(ll k=0; k<n; k++){
					if(i==j) continue;
					if(i&(1<<k)) f[i-(1<<j)]+=f[i]*(2.0/sum/(sum-1))*a[k][j];
				}
			}
		}
	}
	for(ll i=0; i<n; i++) printf("%.6lf ",f[1<<i]);
	return 0;
}
```

---

## 作者：kouylan (赞：1)

## 题解 CF16E 【Fish】

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF16E)

[CF题面传送门](https://codeforces.com/contest/16/problem/E)

$n\leq18$！果断状压dp。

我们很容易设出状态。设 $f[s]$ 表示状态为 $s$ 的概率。其中 $s$ 是一个 $n$ 位二进制，每一位代表一条鱼的状态。$0$ 表示已经死了，$1$ 表示还活着。接下来我们来想状态如何转移。

很显然，如果鱼 $i$ 被鱼 $j$ 吃掉，这个过程可分为 $2$ 步：

1. 两条鱼相遇
2. 鱼 $i$ 被鱼 $j$ 吃掉

设当前有 $fis$ 条鱼，则第一步的概率就是 
$$\frac{1}{C_{fis}^2}\ =\ \frac{2}{fis\cdot (fis-1)}$$

第二步的概率就是 $p[j][i]$（注意是鱼 $i$ **被** 鱼 $j$ 吃掉）

所以，状态转移方程就是

设 $s$ 为当前状态，$t$ 为目标状态， $t=s-(1<<i-1)$

$$f[t]=\sum f[s]\cdot\frac{2}{fis\cdot (fis-1)}\cdot p[j][i]$$

其中要枚举 $i$ 和 $j$。

那么，初始状态就是所有鱼都活着，即

$$f[(1<<n)-1]=1$$

最后按要求输出答案即可。

下面是 AC 代码
```cpp
/*
luogu CF16E
*/
#include <bits/stdc++.h>
using namespace std;

int n;
double p[20][20],f[1<<19];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>p[i][j];
	f[(1<<n)-1] = 1;
	for(int s=(1<<n)-1;s>=1;s--)
	{
		int fis=0;
		for(int i=1;i<=n;i++)
			fis += s>>i-1&1;
		double met=2.0/fis/(fis-1.0);
		for(int i=1;i<=n;i++)
			if(s>>i-1&1)
			{
				int t=s-(1<<i-1);
				for(int j=1;j<=n;j++)
					if(s>>j-1&1 && j!=i)
						f[t] += f[s]*met*p[j][i];
			}
	}
	for(int i=1,s=1;i<=n;i++)
		printf("%.6lf ",f[s<<i-1]);
	
	return puts(""), 0;
}
```

祝大家 AC 愉快！

---

## 作者：Dzhao (赞：0)

这是一道状压 DP 和概率 DP 的综合题，难度还是比较低的，可以用来做为概率 DP 的入门题。

看到 $1\le n\le18$ 的数据范围，下意识会想到状压。

我们令 $F[cur]$ 表示当前还活着的鱼的状态为 $cur$ 的概率为多。

我们要从 $F[cur]$ 往其他的答案扩展。我们每次枚举 $i$ 和 $j$，表示某一天第 $i$ 和第 $j$ 条鱼相遇了。他们都有一定的概率会吃掉对方，且每对 $i$ 和 $j$ 相遇的概率都为 $\binom{t}{2}$，t 表示当前还活着的鱼的数量，则状态转移方程就为：
$$F[cur-2^i]=\sum \dfrac{F[cur]\times a_{j,i}}{\binom{t}{2}}$$
$$F[cur-2^j]=\sum \dfrac{F[cur]\times a_{i,j}}{\binom{t}{2}}$$

然后将 $cur$ 从大到小进行转移，最后将每个 $F[2^i]$ 输出就行了。

$\mathcal{View\ Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20,M=(1<<18)+5;
int n;double a[N][N],dp[M];
inline int cal(int x) {int res=0;while(x) res+=(x&1),x>>=1;return res;}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%lf",&a[i][j]);
	dp[(1<<n)-1]=1;
	for(int cur=(1<<n)-1;cur>=0;cur--)
	{
		int t=cal(cur);
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++) 
				if((cur&(1<<j)) && (cur&(1<<i))) 
				{
					dp[cur-(1<<j)]+=dp[cur]*a[i][j]/(t*(t-1)/2);
					dp[cur-(1<<i)]+=dp[cur]*a[j][i]/(t*(t-1)/2);
				}
	}
	for(int i=0;i<n;i++)
		printf("%lf ",dp[1<<i]);
	return 0;
} 
```


---

## 作者：KSToki (赞：0)

这道题的意思很明确，我们直接进入正题。

首先本蒟蒻设$f[i][j]$表示第$i$条鱼在状态$j$下最终存活的概率，这里的$j$表示了已经互相打过的鱼，然后我们就有了基本的状态转移方程式：$f[i][j]+=f[k][j xor (1<<(k-1))]\times a[i][k]$，最后~~瞎搞~~把它的和弄成$1$。

但是提交上去后，发现它WA了，经过~~二十分钟的~~挣扎，发现这种方法会漏算一些情况。所以蒟蒻~~打开题解~~逆向思考，状态代表现在湖中还省的鱼，比如状态$5=101$表示第一条和第三条鱼还活着。状态转移方程式也清晰了，并且我们发现只用以为表示即可：$f[i]+=f[i|(1<<(j-1))]\times a[1...(j-1),(j+1)...n][j]$

此时两条鱼对战的概率也很明确，用$cnt$表示当前状态$i$中$1$的个数，每次$f[i]$计算完毕后$f[i]=f[i]/cnt/(cnt+1)\times2$即可。

当然还有另一种方法解决两条鱼对战的问题。我们不管这么多细枝末节，只需在最后输出答案时变成这样：
```cpp
double s=0;
for(register int i=1;i<=n;++i)
	s+=f[i][(1<<n)-1];
for(register int i=1;i<=n;++i)
	printf("%lf ",f[i][(1<<n)-1]/s);
```
不需要解释吧。~~蒟蒻专用~~

最后就是上代码阶段啦：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double a[19][19],f[262144];
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
	    for(register int j=1;j<=n;++j)
	        scanf("%lf",&a[i][j]);
	int S=(1<<n)-1;
	f[S]=1;
	for(register int i=S-1;i;--i)
	{
		double cnt=0;
		int tmp=i;
		while(tmp)
		{
			cnt+=tmp&1;
			tmp>>=1;
		}
		for(register int j=1;j<=n;++j)
		    if(!((1<<(j-1))&i))
		        for(register int k=1;k<=n;++k)
		            if((1<<(k-1))&i)
		                f[i]+=f[i|(1<<(j-1))]*a[k][j]/cnt/(cnt+1)*2;
	}
	for(register int i=1;i<=n;++i)
	    printf("%lf ",f[1<<(i-1)]);
	return 0;
}
```
就像上面说的，我们的代码也可以写成这样：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double a[19][19],f[262144];
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
	    for(register int j=1;j<=n;++j)
	        scanf("%lf",&a[i][j]);
	int S=(1<<n)-1;
	f[S]=1;
	for(register int i=S-1;i;--i)
		for(register int j=1;j<=n;++j)
		    if(!((1<<(j-1))&i))
		        for(register int k=1;k<=n;++k)
		            if((1<<(k-1))&i)
		                f[i]+=f[i|(1<<(j-1))]*a[k][j];
	double s=0;
   for(register int i=1;i<=n;++i)
      s+=f[i][(1<<n)-1];
   for(register int i=1;i<=n;++i)
      printf("%lf ",f[i][(1<<n)-1]/s);
	return 0;
}
```
完啦！

---

## 作者：Strelitzia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF16E)

---

前置知识：状压

其实这道题与[这道](https://www.luogu.com.cn/problem/CF540D)，有异曲同工之妙啊，做完本题可以看看。

我们定义 $dp_i$ 为对应鱼存活的概率，初始条件为 $dp_{(111...111)2} = 1$，有 $n$ 个 $\text{1}$。

然后枚举每种可能，枚举哪两个????相遇，重点是计算两条鱼相遇的概率，其它没什么难点。


```cpp
#include <map>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename T>void read(T &x) {
	T f = 1;x = 0;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n;
double p[20][20],dp[1 << 18];

int count(int x) {			//这个只是计算x这个数在二进制下有多少个1，可以不这样。
	x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
	x = (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
	x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
	return x;
}

int main () {
	read(n);
	for (int i = 0 ; i < n ; ++ i) {
		for (int j = 0 ; j < n ; ++ j) {
			scanf("%lf",&p[i][j]);
		}
	}
	int maxx = 1 << n;
	maxx --;
	dp[maxx] = 1;
	for (int i = maxx ; i >= 0 ; -- i) {
		int tot = count(i);
		for (int j = 0 ; j < n ; ++ j) if (i & (1 << j)) {
			for (int k = 0 ; k < n ; ++ k) if ((i & (1 << k)) && (k != j)) {
				dp[i ^ (1 << k)] += dp[i] * p[j][k] * 2.0 / tot / (tot - 1);
			}
		}
	}
	for (int i = 0 ; i < n ; ++ i) {
		printf("%.6lf ",dp[1 << i]);
	}
	return 0;
}
```

---

