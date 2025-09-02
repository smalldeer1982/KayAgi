# Mashmokh and ACM

## 题目描述

Mashmokh's boss, Bimokh, didn't like Mashmokh. So he fired him. Mashmokh decided to go to university and participate in ACM instead of finding a new job. He wants to become a member of Bamokh's team. In order to join he was given some programming tasks and one week to solve them. Mashmokh is not a very experienced programmer. Actually he is not a programmer at all. So he wasn't able to solve them. That's why he asked you to help him with these tasks. One of these tasks is the following.

A sequence of $ l $ integers $ b_{1},b_{2},...,b_{l} $ $ (1<=b_{1}<=b_{2}<=...<=b_{l}<=n) $ is called good if each number divides (without a remainder) by the next number in the sequence. More formally ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF414B/c97c90bdd5f34b7b09ca5088db0c88621395bd9c.png) for all $ i $ $ (1<=i<=l-1) $ .

Given $ n $ and $ k $ find the number of good sequences of length $ k $ . As the answer can be rather large print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample the good sequences are: $ [1,1],[2,2],[3,3],[1,2],[1,3] $ .

## 样例 #1

### 输入

```
3 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 4
```

### 输出

```
39
```

## 样例 #3

### 输入

```
2 1
```

### 输出

```
2
```

# 题解

## 作者：rui_er (赞：29)

一道小清新动规题。

题意：求长度为 $k$ 的、最大数不超过 $n$ 的数列，满足 $a_i=a_{i-1}\times mul$（$2\le i\le n$ 且 $mul$ 为正整数）。

---

思路：

容易想到设计状态 $dp_{i,j}$ 表示长度为 $i$ 时最大数为 $j$ 的方案总数。

转移方程也比较好想，根据数列要求，枚举所有可能的倍数，加上对应方案的 $dp$ 值即可。即：$dp_{i,j}=\displaystyle\sum_{k\ \text{是}\ j\ \text{的因数}}dp_{i-1,k}$。由于因数不好统计，我们根据 $i,k$ 来反推即可。

但是还没有结束，虽然我们可以通过此题，但是作为一个优（du）秀（liu）的 OIer，你不觉得 $dp$ 数组这么大很多余吗？我们对于每一个 $i$，只用到了 $i-1$ 的 $dp$ 值，显然可以压缩空间啊！

考虑将 $dp_j$ 定义为最大数为 $j$ 的方案总数，原本的 $i$ 是没有必要存的。转移方程也没有特别大的变化。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2005, mod = 1e9+7;

ll n, k;
ll dp[N], tmp[N], ans;

int main() {
	scanf("%lld%lld", &n, &k);
	for(ll i=1;i<=n;i++) dp[i] = 1;
	for(ll cnts=2;cnts<=k;cnts++) {
		for(ll i=1;i<=n;i++) tmp[i] = 0;
		for(ll i=1;i<=n;i++) {
			for(ll j=1,_=i*j;_<=n;j++,_=i*j) tmp[_] = (tmp[_] + dp[i]) % mod;
		}
		for(ll i=1;i<=n;i++) dp[i] = tmp[i];
	}
	for(ll i=1;i<=n;i++) ans = (ans + dp[i]) % mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：宁_缺 (赞：22)

吐槽一下楼下的题解…**#不打**算是防抄题解，但是每行的码风还是最好注意一下吧……
### 这道题就是一个DP，f[i][j]表示长度为i，最后一个数为j时，可以达到的最多数量
那么首先就可以得到f[1][x]为1，因为长度为一只有一种

然后f[i][j]就等于(f[i][j]+f[i-1][k])%M,其中k为j的整数倍
#### 最后就统计一下长度为k的好数列的种数就行了
```cpp
#include<bits/stdc++.h>
#define M 1000000007
using namespace std;
long long f[2001][2001],ans;
int main(){
	int n,k;scanf("%d%d",&n,&k);
	for(int i=0;i<=n;i++)f[1][i]=1;
	for(int i=2;i<=k;i++)
		for(int j=1;j<=n;j++)
			for(int _=1;j*_<=n;_++)
				f[i][j]=(f[i][j]+f[i-1][j*_])%M;
	for(int i=1;i<=n;i++)ans=(ans+f[k][i])%M;
	printf("%lld\n",ans),exit(0);
}
```

---

## 作者：龙潜月十五 (赞：11)

## 一、前言

本题是一道较简单的 DP，主要考察思维能力，是一道较好的**线性 DP** 的练手题。

## 二、题意

给出一个数列中的最大元素 $n$（**注意！：题目有误，这里应该是每一种数列中的最大值不能大于** $n$）,和数列的长度 $k$，求满足**后一个数都能被前面的一个数整除**的数列的个数（对 $10^9+7$ 取模）。

## 三、思路

首先看到求方案数的题目，大概率就是 DP 了（~~还有暴搜~~），再看数据范围（$1 \leq n,k \leq 2000$），在 DP 的时间复杂度可接受的范围内。

## 四、动态规划

### （1）状态

首先对于动态规划设计状态，一定要看**题目求什么**以及**什么会影响答案**，将状态设成所求的东西（就好像数学方程中设未知数的原则**求什么设什么**），再将**会影响答案的**写进状态下标。

比如这题，求的是**满足条件的数列种类**，因此我们设 $f(i,j)$ 为**最大元素为 $i$，长度为 $j$ 的满足条件的数列个数**。最大元素、数列长度即为**影响答案的因素**。

### （2）转移

本题转移的关键就在题目的条件：**后一个数都能被前面一个数整除**，显然当我们转移到 $f(i,j)$ 的时候，其方案数一定是由**前一个元素是 $i$ 的因数，长度为 $j-1$ 的方案数累加而成**。即

$$f(i,j)+=f(t,j-1) \ (t \ | \ i)$$

### （3）初始化

我们会发现，最大元素为 $1$ 和数列长度为 $1$ 的数列个数都为 $1$。

## 五、注意点

对于每一个数，我们可以想到预处理出它们所有的因数，转移时直接枚举每一个因数即可。

## 六、代码

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
typedef long long ll;

const int N=2007;
const int mod=1e9+7;
ll n,k,f[N][N],ans;
vector<int>p[N];

//预处理出所有的因数 
inline void pre()
{
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=sqrt(i);j++)
			if(i%j==0)
			{
				p[i].push_back(j);
				if(j!=i/j)
					p[i].push_back(i/j);
}
}

int main()
{
	scanf("%lld%lld",&n,&k);
		
	//初始化 
	for(re int i=1;i<=n;i++)
		f[i][1]=1;
	for(re int i=1;i<=k;i++)
		f[1][i]=1;
	
	pre();

	//转移 
	for(re int i=2;i<=n;i++)
		for(re int j=2;j<=k;j++)
			for(re int t=0;t<p[i].size();t++)
				f[i][j]=(f[i][j]+f[p[i][t]][j-1])%mod;
	
	for(re int i=1;i<=n;i++)
		ans=(ans+f[i][k])%mod;
	
	printf("%lld",ans);
	
	return 0;
}
```


---

## 作者：MuYC (赞：9)

#### 前言

我做过这一道题目的进阶版，那一道我放在结尾留给读者思考（牛客上面的一道题）

这一题难度不大，建议下调难度评分。

#### 思路

+ #### 状态设置

关于这一道题，状态的设置很简单，就是为：

$dp[i][j]$ ： 填到第$i$位，并且第$i$位为$j$的方案数。

+ #### 状态转移

有两种转移方法，其一是假设现在的状态为$dp[i][j]$，我们转移的方程可以写成：

$dp[i][j] += dp[i - 1][k](k | j)$(即$k$为$j$的因数)

这样子不方便转移，因为这样转移要枚举$j$的因子，时间复杂度O($n^2 * k$)显然过不了这一题。

另外一种是与这种转移相反的:

$dp[i + 1][k] += dp[i][j](j | k)$(即$k$为$j$的倍数)

直接枚举当前$dp[i][j]$的倍数进行转移即可。

这样子转移的时间复杂度是多少？

众所周知一个式子：因为$\sum_{i = 1}^{i = k}{\frac{k}{i}}$ ≈ $log(k)$

所以时间复杂度大概是O($n*k$ * Θ$(log(n))$)

过这一道题目还是可以过的，最坏的情况即$n,k = 2000$

需要运行的次数：$2000*2000 * log(2000)$ ≈ $4.4 * 10^7$

+ #### 边界设立

初始化状态：$dp[1][i] = 1(1 <= i <= n)$

这个状态的设立挺显然的。

最后的答案为:$\sum_{i = 1}^{i = n}{dp[k][i]}$

于是放出简短的代码：

#### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005,MAXK = 2005 , Mod = 1000000007; 

int n ,K ,Ans = 0;
int dp[MAXK][MAXN];

signed main()
{
	cin >> n >> K;
	for(int i = 1 ; i <= n ; i ++)dp[1][i] = 1;
	for(int i = 1 ; i <= K - 1 ; i ++)
		for(int j = 1 ; j <= n ; j ++)
			for(int k = j ; k <= n ; k += j)
			dp[i + 1][k] += dp[i][j] , dp[i + 1][k] %= Mod;
	for(int i = 1 ; i <= n ; i ++)
		Ans += dp[K][i] , Ans %= Mod;
	cout << Ans;
	return 0;
}
```

#### 后话

问满足这个条件的序列有多少个对$10^9 + 7$取模：

+ 长度为n

+ 每一个数都在1到k之间

+ 对于任意连续的两个数A，B，A<=B 与（A % B != 0） 两个条件至少成立一个


大家可以思考这道题。

这一题的题解:[$MYCui's$ $blog$](https://www.cnblogs.com/MYCui/p/13947754.html#ROP_niuniu)

---

## 作者：ctq1999 (赞：7)

## 题解

DP。

一个位置的状态肯定是由上一个位置的状态转移过来的。

设 $f[i][j]$ 表示在 $i$ 位置上填 $j$ ，产生的最大方案数。

那么我们需要枚举当前位置，当前填的数字，上一个位置填的数字。

得出伪代码：

```cpp
for (int i = 2; i <= k; i++) {
	for (int j = 1; j <= n; j++) {
		for (int k = j; k <= n; k++) {
            if (k % j == 0)
			f[i][k] = (f[i][k] + f[i - 1][j]) % mod;
		}
	}
}
```

时间复杂度 $O(n^3)$ 。不能通过此题。

考虑优化。因为当前数应是前一个数的倍数，因为 **$k$循环可以使用倍数** 来减少循环。

```cpp
for (int i = 2; i <= k; i++) {
	for (int j = 1; j <= n; j++) {
		for (int k = 1; k * j <= n; k++) {
			f[i][k * j] = (f[i][k * j] + f[i - 1][j]) % mod;
		}
	}
}
```

注意初始化。

时间复杂度 $O(n^2)$ 。可以通过此题。

## 代码

```cpp
#include <bits/stdc++.h>

#define MAXN 2010
#define mod 1000000007
#define ll long long

using namespace std;

int n, k;

ll f[MAXN][MAXN];

int main() {
	scanf("%d%d", &n, &k);
	
	for (int i = 1; i <= n; i++) {
		f[1][i] = 1;
	}
	
	
	for (int i = 2; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k * j <= n; k++) {
				f[i][k * j] = (f[i][k * j] + f[i - 1][j]) % mod;
			}
		}
	}
	
	int sum = 0;
	for (int i = 1; i <= n; i++) sum = (sum + f[k][i]) % mod;
	cout << sum << endl;
	return 0;
}
```

> 日供一卒，功不唐捐。


---

## 作者：zhangtianhan (赞：3)

本题思路：设 $dp_{i, j}$ 表示共 $i$ 位，以 $j$ 结尾的方案数，由题意可知可以从j的因数转移，总方程为
$$dp_{i, j} = \sum_{k | j} dp_{i - 1, k}$$
由于因数不好枚举，选择使用刷表法枚举倍数，方程变为
$$dp_{i + 1, j * k} += dp_{i, j}$$
看到方程，可以知道 $dp_{i, j}$ 仅与 $dp_{i - 1}$ 中小于 $j$ 的数有关，因此可以想到一个类似 $01$ 背包的优化，倒序枚举 $j$ 即可把本题的空间复杂度从 $O(n \times k)$ 降到 $O(n)$。

还有一点需要注意，数组的$i$维被滚动优化掉以后是有初值的，所以 $k$ 应该从 $2$ 开始枚举。

代码（ $18$ 行，~~题解中目前最短~~）:
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2005, MOD = 1e9 + 7;
int n, k, dp[N], ans;

int main()
{
	cin >> n >> k;
	for(int i = 1;i <= n;++i) dp[i] = 1;
	for(int i = 1;i < k;++i)
		for(int j = n;j > 0;--j)
			for(int k = 2;j * k <= n;++k) dp[j * k] = (dp[j * k] + dp[j]) % MOD;
	for(int i = 1;i <= n;++i) ans = (ans + dp[i]) % MOD;
	cout << ans << endl;
	return 0;
}

```



---

## 作者：Zxsoul (赞：2)

这真的就是一道DP

## 思路

状态设计
$$
f[i][j]
$$
表示最大数是 $i$ 长度为 $j$的方案数

转移我们有
$$
f[i][j]+=f[i\times  k][j-1]
$$

我们只需要知道序列上一个的方案数，最后加和即可

## 告诫

在循环层的设计时，需要将序列长度 $j$ 放在外面，因为 $j$ 列必须是有$j-1$行转移来的，因此必须现有 $j-1$ 的方案数，才可转移，不然答案会遗漏

## Code
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

const int A = 1e7+10;
const int B = 1e6+10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

int n,f[3000][3000],k,ans;

main()
{
    n=read(),k=read();
    for (int i=1;i<=n;i++) f[i][1]=1;
    for (int j=2;j<=k;j++)
        for (int i=1;i<=n;i++)
            for (int k=1;k*i<=n;k++)
                f[i][j]=(f[i][j]+f[k*i][j-1])%mod;
    for (int i=1;i<=n;i++) ans=(ans+f[i][k])%mod;
    printf("%lld", ans);
} 
```

---

## 作者：asdfo123 (赞：2)

## 题解 CF414B 【Mashmokh and ACM】

看到大家都是直接递推的，我来一个记忆化搜索的方法

本题可以看成一个简单的数位dp，对于数位dp，我们一般采用记忆化搜索，这样对于一些复杂的问题能更方便地解决。。

当然了，这道题还是比较基础的，连前导0之类的都不用判断，普通递推也是非常好的

设 $f_{i,j}$ 为当前是第i个位置，这一位数是j的状态数

那么可以推出递推式：

$$f_{i,j} = \sum_{k \ \text{是}\ j\ \text{的因数}} f_{i-1,k} $$



上代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e9+7;
int n,k;
ll f[2005][2005];
ll dfs(int pos,int statu)
{
	if(pos == 0) return 1;
	if(f[pos][statu]) return f[pos][statu];
	ll ans = 0;
	for(int i = statu;i <= n;i+=statu)
	{
		(ans += dfs(pos-1,i))%=mod;
	}
	return f[pos][statu] = ans;
}
int main()
{
	scanf("%d%d",&n,&k);
	ll anss = dfs(k,1);
	printf("%lld",anss);
	return 0;
}
```


---

## 作者：juicyyou (赞：2)

# CF414B Mashmokh and ACM
## 题目大意
如果一个数列$b_k$满足对任意的$i$, 有
$ b_{i - 1} | b_i $, 则我们称数列$b_k$是一个好数列。
求长度为$k$且数列中的最大值小于$n$的好数列的个数对$10^9+7$取余的值。

## 解法
考虑$dp$, 令$dp_{i, j}$表示长度为$i$, 数列中的最大值为$j$的好数列的个数对$10^9+7$取余的值。则有:

$$ \large{dp_{i, j} = \sum\limits_{\scriptsize{d | j}} dp_{i-1, d}}$$

但如果这样单纯暴力的话, 复杂度为$O(n^2k)$。而题目中说$1 \le n,k \le 2000$, 肯定会超时, 所以需要对这个$dp$进行优化。

注意到如果$d | j$, 则必有一个$s$, 使得 $d \cdot s = j$, 又因为$\sqrt{j} \cdot \sqrt{j} = j$, 所以, 必有:

$$ 1 \le \min(d, s) \le \sqrt{j} $$

所以我们只用枚举$d$和$s$中的较小值即可于是, 我们有如下转移方程:

$$dp_{i, j} = \sum\limits_{d | j \land d \le\sqrt{j}} dp_{i - 1, d} + dp_{i - 1, j / d}$$

不过需要注意的是, 如果$d = s$, 在更新$dp_{i, j}$时只能加一次。

最终答案就是:
$$\sum\limits_{i = 1}^n dp_{k, i}$$

复杂度是$O(nk\sqrt{n})$, 可以通过此题。

下面是我的Code:
```cpp
#include<iostream>
using namespace std;
const int maxn = 2e3 + 5;
const int mod = 1e9 + 7;
int n, k, ans;
int dp[maxn][maxn]; // dp数组 
int main(){
	cin >> n >> k; // 输入 
	for(int i = 1;i <= n;i++){
		dp[1][i] = 1; // 初始化 
	}
	for(int i = 2;i <= k;i++){
		for(int j = 1;j <= n;j++){
			int tmp = j;
			for(int k = 1;k * k <= j;k++){
				if(j % k == 0){
					dp[i][j] += dp[i - 1][k]; // 状态转移 
					dp[i][j] %= mod;
					if(k * k != j){ // 如果 k * k != j 则可以用 dp[i - 1][j / k] 更新 dp[i][j] 
						dp[i][j] += dp[i - 1][j / k];
						dp[i][j] %= mod; // 取模 
					}
				}
			}
		}
	}
	for(int i = 1;i <= n;i++){
		ans += dp[k][i]; // 统计答案 
		ans %= mod;
	}
	cout << ans << endl; // 输出 
	return 0;
} 
```

---

## 作者：black_trees (赞：0)

比较简单的一道DP。

---

状态比较好想。直接从题目里找一下要求然后直接设就行了。

即是： 设 $f[i][j]$ 表示最大元素为 $i$ ,长度为 $j$ 的方案数。

但是在转移的时候会稍微麻烦一点。一般的和这种数列有关系的DP。最外层一般都是枚举长度。

所以改变一下状态。 设 $f[i][j]$ 表示最大元素为 $j$ ,长度为 $i$ 的方案数。 

现在还是不好转移。

看题目里的一个词：`整除`

这是这道题目最关键的地方。我们后一个数要从前一个数走过来，肯定是要乘上一个常数的，而方案数的多与少就取决于这个常数可以怎么拿。

所以在循环里加一层，枚举这一个常数。

那我们可以结合状态本身的定义想到：

$$f[i][j]=(f[i][j]+f[i-1][j\times \alpha]) \operatorname{mod} (10^9+7)$$

（ $\alpha$ 为我们枚举的常数。）

然后根据“好数列”的定义，可以发现， $\alpha$ 往后枚举的条件是 $\alpha \times j \le n$ （最大元素不大于 $n$ （因为你的数列中的数是上升的，$\alpha \times j$ 相当于去求这个当前序列里的最大值））

初始化就从长度为 $1$ 的状态初始化就可以了（$f[1][j]$）

最后，我们可以得出这样的代码（转移的时候记得取模）：

```cpp

#include<bits/stdc++.h>
using namespace std;

const int si=2010;
int n,K;//这里的K是大写的，表示题目所给的K
int f[si][si];
const int mod=1e9+7;
int res;

int main(){
	scanf("%d%d",&n,&K);
	for(register int i=0;i<=n;++i){
		f[1][i]=1;
	}	//初始化
	for(register int i=1;i<=K;++i){//枚举长度
		for(register int j=1;j<=n;++j){//枚举元素最大值
			for(register int k=1;k*j<=n;++k){ //这里的k是小写，是枚举的常数
				f[i][j]=(f[i][j]+f[i-1][k*j])%mod;
			}	
		}
	}
	for(register int i=1;i<=n;++i){
		res=(res+f[K][i])%mod;
	}
	cout<<res<<endl;
	return 0;
}
```

----





---

## 作者：金银花露 (赞：0)

[CF414B Mashmokh and ACM](https://www.luogu.com.cn/problem/CF414B)
## 知识
1. 关于简单 DP 的推导与优化。

1. 特殊性质的发现。
## 1.审题
### 1.1关键点
-  是后一个数被前一个数整除。

-  要求的是方案数。

-  要对其取模。

### 1.2简单推导
1. **每一个合格序列都是由小到大递增的。**

证明：

若在一个合格序列中出现了一个 $b_i$ 使 $b_i$ 不在最后且最大。

那么，$b_{i+1}\bmod b_i$ 一定不为0，不符合定义，所以一定不存在。

2. **序列里不含0** 

证明：
   
如果含有0，则会出现除数为0的情况，所以一定不存在。
## 2.解题
### 2.1明确算法

因为求方案数，可以很快确定出应该要用 **DP** 进行求解。

### 2.2状态设计

令 $f_{i,j}$ 为最大元素为 i（**序列一定有 i**）序列长度为 j 的方案数。

由刚刚推导的第1点知，序列中最大值 i 一定在最后。

### 2.3方程推导

由题目中要求序列合法的条件，我们令 k 为 i 前面的第一个数。

则 k 一定满足 $i \bmod k=0$。

因为是求方案数，所以一定是把每一个 $f_{k,j-1}$ 加起来得到 $f_{i,j}$。

### 2.4边界

- $f_{i,1}$ 一定为1。

- $f_{1,j}$ 一定为1。

### 2.5答案

因为状态设计是必须以固定最大结尾，所以答案为 $f_{i,K}$ 的总和。
### 2.6程序基础

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mo=1000000007;
long long f[2005][2005],N,K;
long long ans=0; 
int main()
{
	cin>>N>>K;
	for(int i=1;i<=N;i++)f[i][1]=1;
	for(int j=1;j<=K;j++)f[1][j]=1; 
	for(int i=2;i<=N;i++)
	for(int j=1;j<=K;j++)
	for(int k=1;k<=i;k++)
	{
	if(i%k==0)f[i][j]=(f[i][j]+f[k][j-1])%mo;
	}
	for(int i=1;i<=N;i++)ans=(ans+f[i][K])%mo;
	cout<<ans;
	return 0;
}
```
## 3.优化
### 3.1基础代码分析

- 时间复杂度接近 $O(N^2K)$，会有超时的情况。

- 主要的浪费在于找寻 i 的约数上。

### 3.2优化

优化原理：若 $k^2\ne i$ 且 $i \bmod k=0$，则 $i \bmod i/k=0$。

实现：

- 若 $k^2\ne i$ 且 $i \bmod k=0$，则将 $f_{i,j}$ 加上 $f_{k,j}$ 和 $f_{i/k,j}$。

- 否则加上 $f_{k,j}$。

### 3.3优化代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mo=1000000007;
long long f[2005][2005],N,K;
long long ans=0; 
int main()
{
	cin>>N>>K;
	for(int i=1;i<=N;i++)f[i][1]=1;
	for(int j=1;j<=K;j++)f[1][j]=1; 
	for(int i=2;i<=N;i++)
	for(int j=1;j<=K;j++)
	for(int k=1;k*k<=i;k++)
	{
	if(k*k==i)f[i][j]=(f[i][j]+f[k][j-1])%mo;
	else if(i%k==0)f[i][j]=(f[i][j]+f[k][j-1]+f[i/k][j-1])%mo;
	}
	for(int i=1;i<=N;i++)ans=(ans+f[i][K])%mo;
	cout<<ans;
	return 0;
}
```
## 4.总结

1. 动态规划的推导。

1. 求约数的 $\log$ 级算法。

1. 题意的理解与运用。



---

## 作者：ROBOT233 (赞：0)

首先看看这道题，要输出长度为k的种数，很明显不会影响到k为其他值的情况，所以可以用dp来做。

那么首先设计状态，用f[i][j]来表示长度为i，末位数字为k的情况下，能够达到的最优解。

蒟蒻第一次写题解有什么不足可以指出来。
代码：
```cpp
include<iostream>
include<math.h>
include<cstdio>
define M 1000000007
using namespace std; 
int n,k; 
long long f[2002][2002]={0}; //设计状态，f[i][j]表示长度为i，最后一个数为k时，可以达到的最多数量。
int main() 
{
scanf("%d%d",&n,&k);
for(int i=0;i<=n;i++)f[1][i]=1;//初值，长度为1结尾无论是什么都只有一种 
for(int m=2;m<=k;m++)
for(int i=1;i<=n;i++)
for(int j=i ; j<=n; j+=i)f[m][i]=(f[m][i]+f[m-1][j])%M;
//3层循环（n不大），第一层表示长度，第二层表示结尾数字为几，
//如果这个i整除j，那么在f[m-1][j]的每种情况下后面加上一个i就是f[m][i]的一种解。 
long long sum=0;
for(int i=1;i<=n;i++)sum=(sum+f[k][i])%M;
//把长度为k，末位为i的所有情况相加就是解 
printf("%lld",sum);
return 0;
}
```

---

