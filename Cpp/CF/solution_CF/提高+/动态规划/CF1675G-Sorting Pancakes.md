# Sorting Pancakes

## 题目描述

### 题意简述

有 $n$ 个箱子和 $m$ 个小球，初始时第 $i$ 个箱子有 $a_i$ 个小球。每次操作可以将**一个**小球移到相邻的箱子里。求要使得最终数组 $a_i\ge a_{i+1}$ 的最小操作次数。

## 样例 #1

### 输入

```
6 19
5 3 2 3 3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
3 6
3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3 6
2 1 3```

### 输出

```
1```

## 样例 #4

### 输入

```
6 19
3 4 3 3 5 1```

### 输出

```
3```

## 样例 #5

### 输入

```
10 1
0 0 0 0 0 0 0 0 0 1```

### 输出

```
9```

# 题解

## 作者：李34 (赞：14)

首先，可以感性地发现挪馅饼时出现负值不会影响最终答案，只要最终方案是非负的就行了。

所以，我们不妨规定，一个盘子只能从右边一个盘子拿馅饼，或者向右边一个盘子放馅饼。

我们用 $f_{i,j,k}$ 表示前 $i$ 盘放 $j$ 张馅饼，第 $i$ 盘放 $k$ 张馅饼的最小花费。不难发现 $f_{i,j,k}$ 可以转移到 $f_{i+1,j+p,p}$ 。

现在我们记**原来**前 $i$ 个盘子上的馅饼和为 $S_i$ 。

考虑如何从 $f_{i,j,k}$ 转移到 $f_{i+1,j+p,p}$ ：由于我们每次转移馅饼都只和右边一个盘子有关，所以前 $i$ 个盘子定好后的状态中，**前** $i+1$ **个盘子上的馅饼数之和依然是** $S_{i+1}$ 。

所以我们只需从第 $i+2$ 个盘子里拿 $j+p-S_{i+1}$ 个馅饼到第 $i+1$ 个盘子上就行了（若拿负数个馅饼过来，等同于拿出去这么多个）。于是状态转移方程就推出来了：

$$ f_{i+1,j+p,p} = min\{f_{i+1,j+p,p},f_{i,j,k}+\mid j+p-S_{i+1}\mid\}$$

枚举 $i,j,k,p$ ，复杂度 $O(n\times m^3)$ ，会超时。

考虑到 $f_{i+1,j+p,p}$ 会被所有 $f_{i,j,k}(k\geq p)$ 都转移一次，故可以倒着枚举 $k$ ：设当前枚举到 $i,j,k$ ， $minn = min_{h=k}^m f_{i,j,h}$ ，则有转移方程：

$$ f_{i+1,j+k,k} = min\{ minn + \mid j+p-S_{i+1}\mid\}$$

最终答案 $ans$ 为：

$$ ans = min_{k=0}^{m}\{ f_{n,m,k}\}$$

时间复杂度 $O(n\times m^2)$ ，可以通过此题。

[代码](https://www.luogu.com.cn/paste/a2yph400)

---

## 作者：StillEmpty (赞：9)

难度不大，洛谷和cf评分都虚高。

对于这种问题，先简单看看有没有出现贪心技巧的可能。发现没有。再看看有没有什么似乎必定要做的操作。发现没有。再看数据范围——铁定dp了。

第一位肯定是枚举到第几个盒子。考虑到我们要保证他非严格单调递减，所以记录该个盒子放几个馅饼还是有必要的。然后又发现非严格单调递减性保证小于等于最后一个前面的都不用管了，肯定合法了。自然考虑二位dp。

然后发现有个问题：我们枚举到第 $i$ 个盒子，考虑向前放几个馅饼时，会发现有可能我们向前一个放馅饼导致前一个比前前个馅饼多。所以这件事告诉我们还要加一位表示向后一个盒子放/取几个馅饼，这样就不会向前放馅饼导致问题了。

严谨的说， $f_{i,j,k}$ 表示 $[1,i]$ 号盒子中，盒子中的馅饼数非严格单调递减，并且第 $i$ 个盒子有 $j$ 个馅饼，向第 $i+1$ 号盒子挪动 $k$ 个馅饼的情况下，最小移动次数。如果 $k$ 是负数则表示取走 $|k|$ 个馅饼。

状态转移式自然也很明显：枚举上一个盒子有几个馅饼。
$$
f_{i,j,k}=\min_{h \ge j} f_{i-1,h,j+k-a_i}+|k|
$$

然后你会惊人的发现，这破玩意是 $O(n\times m^3)$ 的，会被卡。然后你猜怎地？改式子？改转移？nonono。别的题解都是这样。我教你：是不是一大堆状态都是无效的？每次会从一大堆 $\infty$ 中选最小值？所以啊，我们将第 $i$ 的情况向 $i+1$ 转移，如果当前状态是 $\infty$ 直接 `continue`。这样就十分的能过了。毕竟想想看，难不成每次都有可能 $j=m$ 或者 $k=m$？

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 250;
int n, m;
int a[N+1];
int f[N+1][N+1][N*2+1];

int main() {
	// freopen("in", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	memset(f, 0x3f, sizeof(f));
	f[0][N][0+N] = 0;
	a[0] = 114514;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j <= N; ++j) {
			for(int k = -N; k <= N; ++k) {
				if(f[i][j][k+N] > 1919810) continue;
				for(int l = 0, q = k+a[i+1]; l <= j && q > -N; ++l, --q) {
					int &tmp = f[i+1][l][q+N];
					tmp = min(tmp, f[i][j][k+N]+abs(q));
				}
			}
		}
	}
	int ans = 1919810;
	for(int i = 0; i <= N; ++i) ans = min(ans, f[n][i][0+N]);
	cout << ans << endl;
  return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

给出一个长度为 $n$ 的序列 $a$，有 $\sum a=m$。

你可以进行任意次操作，每次操作可以选择两个下标 $i,j$，满足 $|i-j|=1$。然后令 $a_i\leftarrow a_i-1,a_j\leftarrow a_j+1$。

你需要把 $a$ 变成一个严格不上升序列。问最小操作次数。

$1 \leq n,m \leq 250,0 \leq a_i \leq m$

## 思路

首先可以想到一个状态 $f(i,k)$ 表示前缀序列 $[1:i]$ 形成严格不上升序列，且 $a_i=k$ 时的最小代价。为什么要设 $a_i$ 呢，因为考虑 $[1:i+1]$ 的决策中 $i+1$ 的改变只与 $i$ 有关。

发现难以确定 $i+1$ 的变化量。

于是再增加一维，设 $f(i,j,k)$ 为前缀 $[1:i]$ 序列形成严格不上升序列，且 $\sum_{l=1}^{i}a_l = j,a_i = k$ 的最小代价。

考虑如何转移，记 $S_i=\sum_{l=1}^{i}a_l$，则原来的 $j$ 应该是 $S_i$。但是变成了 $j$，所以应该从 $i+1$ 哪里抢 / 放 $j-S_i$ 才行。

转移时枚举第 $i-1$ 的取值，即得出动态转移方程：

$$
f(i,j,k)=\min_{l=k}^{m}f(i-1,j-k,l)+|j-S_i|
$$

朴素转移时间复杂度 $O(nm^3)$。难以通过本题（实际上可以？）

先滚动数组滚掉 $i$，然后考虑到转移等价于一个 RMQ 问题：

$$
\min_{l=k}^{m}f(j-k,l)
$$

维护 $f(j)$ 的后缀最小值即可。

时间复杂度 $O(nm^2)$，空间复杂度 $O(nm)$。可以通过本题。

## 关键代码

```cpp
signed main(){
	io>>n>>m;
	for(int i=1;i<=n;i++){
		io>>s[i];s[i]+=s[i-1];
	}
	for(int i=0;i<=m;i++) f[0][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=j;k++) f[j][k]=mi[j-k][k]+abs(s[i]-j);
		}
		for(int j=0;j<=m;j++){
			for(int k=0;k<=(m+1);k++) mi[j][k]=INT_MAX;
			for(int k=j;~k;k--) mi[j][k]=min(mi[j][k+1],f[j][k]);
		}
	}
	int ans=INT_MAX;
	for(int i=0;i<=m;i++) ans=min(ans, f[m][i]);
	io<<ans;
	return 0;
}
```

---

## 作者：zyl1543130456 (赞：2)

## 题目大意

有 $ n $ 个箱子和 $ m $ 个小球，初始时第 $ i $ 个箱子有 $ a_i $ 个小球。每次操作可以将一个小球移到相邻的箱子里。求要使得最终数组 $ a_i \ge a_{i+1} $ 的最小操作次数 $ a_i $ 大于 $ 0 $  。


## 解题思路

看完题解后发现是 dp 。想想如何想到 dp 。

题目特地给了个貌似没用的 $ m $ ，这应该是给了这题要用  dp 的提示。

设 $ dp_{i,j,k} $ 为前 $ i $ 个箱子里一共放 $ j $ 个球，第 $ i $ 个箱子里放 $ k $ 个小球的最小代价。

我们先维护一个前缀和数组 $ s_i $ ，然后再进行操作，例如：

原数组 $ 5 \ 3 \ 2 \ 3 \ 3 \ 3 \ 3 $

前缀和 $ 5 \ 8 \ 10 \ 13 \ 16 \ 19 \ 21 $

显然我们要将第二个盒子的小球放入第三个小球中，更改后：

原数组 $ 5 \ 2 \ 3 \ 3 \ 3 \ 3 \ 3 $

前缀和 $ 5 \ 7 \ 10 \ 13 \ 16 \ 19 \ 21 $

我们可以发现，移动了小球后只有给出小球的一方前缀和会发生变化，其他则不受影响。因此，移动一个小球的代价即为 $ | s_i - j | $（即下标为 $ i $ 的箱子中的小球的前后变化的数量）， $ j $ 的含义与上文相同。

怎么计算代价已经明了了，接下来就可以考虑状态转移方程了。

$$
dp_{i,j,k} = \min_{l=k}^m ( dp_{i,j,k} , dp_{i-1,j-k,l} + | s_i - j |)
$$

由于目的是构建非严格单调递减，所以 $ k \leq l \leq m $  ，这样子的时间复杂度是 $ O(NM^3) $ ，大概是可以过这一题的，但我们还可以进行进一步的优化。

我们可以发现在状态转移方程中有一个不变的量 $ | s_i - j | $ ，唯一变的量是 $ dp_{i-1,k,l} $ ，因为是找最小，所以我们只要提前维护好 $ dp_{i-j,k,l} $ 的最小值即可。时间复杂度为 $ O(NM^2) $

## 代码

```c++
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize(1)
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <math.h>
using namespace std;
const int N=250+10;
int n,m;
int a[N],s[N];
int dp[2][N][N];//滚动数组节省内存
int g[2][N][N];
int ans;
inline int read(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		s[i]=s[i-1]+a[i];
	}
	memset(dp,0x3f,sizeof dp);
	for(int i=0;i<=m;i++)dp[0][0][i]=0;
	for(int i=1;i<=n;i++){
		int id=i&1;
		memset(dp[id],0x3f,sizeof dp[id]);
		memset(g[id],0x3f,sizeof g[id]);
		for(int j=0;j<=m;j++){
			for(int k=0;k<=j;k++){
					dp[id][j][k]=g[id^1][j-k][k]+abs(s[i]-j);
			}
		}
		for(int j=0;j<=m;j++){
			for(int k=j;k>=0;k--){
				g[id][j][k]=min(g[id][j][k+1],dp[id][j][k]);
			}
		}
	}
	ans=0x3f3f3f3f;
	for(int i=0;i<=m;i++){
		ans=min(ans,dp[n&1][m][i]);
	}
	printf("%d",ans);
}
```


---

## 作者：EuphoricStar (赞：2)

首先有一个性质：

对于两个序列 $a_1,a_2,...,a_n$ 和 $b_1,b_2,...,b_n$，若 $a$ 想通过一系列操作变为 $b$，记 $a$ 序列的前缀和为 $suma_i$，$b$ 序列的前缀和为 $sumb_i$，即 $suma_i = \sum\limits_{j=1}^i a_j$，$sumb_i = \sum\limits_{j=1}^i b_j$，则 $a$ 序列变为 $b$ 序列的最小操作次数为：

$$\sum\limits_{i=1}^{n-1} |suma_i - sumb_i|$$

可以这么理解，从前往后遍历，使它们逐个变为相等。首先要让 $a_1 = b_1$ 就要操作 $|a_1 - b_1|$ 次，和 $2$ 操作后 $a_1$ 变成了 $b_1$，$a_2$ 变成了 $a_2 + a_1 - b_1$，那么要让 $a_2 = b_2$ 就要和 $3$ 操作 $|a_2 + a_1 - b_1 - b_2|$ 次。最后一个元素不用操作。这样推下去就可以得到上面的式子。

然后就可以 dp。设 $f_{i,j,k}$ 为前 $i$ 个元素不升，当前枚举的元素变成了 $j$，和为 $k$ 的最小操作次数。转移时再枚举当前的元素 $l$，有转移方程 $f_{i,l,k} \gets \min(f_{i,l,k},f_{i-1,j,k-l} + |l - sum_i|)$，其中 $sum_i = \sum\limits_{j=1}^i a_j$。

注意到最后的序列的第 $i$ 个元素上界为 $\left\lfloor\dfrac{m}{i}\right\rfloor$，所以复杂度实际上大约是 $O(nm^2 \log m)$。

代码很简单，就不放了。

---

## 作者：Fireworks_Rise (赞：1)

# Solution

看问题，会发现这和纸牌均分有点像，那可以尝试同样的方法：每个盘子只会从右边取（正数），或给右边（负数）。

再看一下数据范围 $1 \le n,m \le 250$，大多都是考虑 dp 了，那么定义 $f_{i,j,k}$ 为前 $i$ 个盘子中，共放 $j$ 个馅饼，第 $i$ 个盘子放了 $k$ 个馅饼。

对于第 $i$ 个盘子，我们该如何判断其中的馅饼会想右边取或给呢？一个老套路，维护原序列的前缀和 $sum_i$，枚举当前盘子有 $p$ 个馅饼，后一个盘子有 $k$ 个馅饼，当前需向右边取或给的馅饼个数为 $|j+k-sum_{i+1}|$，那么状态转移方程就为：

$$f_{i+1,j+k,k}=\min{f_{i,j,p}+|j+k-sum_{i+1}|,f_{i+1,j+k,k}}(p \ge k)$$

时间复杂度为 $O(nk^3)$，明显超时了，接下来考虑优化咯！

时刻需记住：

- 对于 dp 的优化其实是等价代换，还是降维，亦或是删除重复或无用的转移...

那么想想有什么是重复在操作的呢，观察转移式子便可以发现在枚举 $k$ 时，$f_{i+1,j+k,k}$ 对 $f_{i,j,p}$ 取了多次无用的最小值，那么如何解决这种情况呢。回过头后发现转移方程是满足 $p \ge k$ 的，那可以考虑倒序枚举 $k$，顺路把最小值 $Minx=\min{f_{i,j,k},Minx}$ 取了即可：

$$f_{i+1,j+k,k}=\min{Minx+|j+k-sum_{i+1}|,f_{i+1,j+k,k}}$$

最后枚举最后一个盘子有 $i$ 个馅饼，找所有 $f_{n,m,i}$ 中最小值即为答案。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18;
const int N=251;
int n,m,a[N],sum[N];
int f[N][N][N];
signed main() {
	memset(f,0x7f,sizeof f);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	f[0][0][m]=0;
	for(int i=0;i<n;i++) {
		for(int j=0;j<=m;j++) {
			int Minx=inf;
			for(int k=m;k>=0;k--) {
				Minx=min(f[i][j][k],Minx);
				if(j+k<=m)
					f[i+1][j+k][k]=min(Minx+abs(j+k-sum[i+1]),f[i+1][j+k][k]);
			}
		}
	}
	int ans=inf;
	for(int i=0;i<=m;i++)
		ans=min(f[n][m][i],ans);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

看到这么小的数据范围肯定考虑 DP。

观察到一个性质：如果只操作前 $i$ 个，那么前 $i+1$ 个位置的和依旧不变。

所以考虑 DP：$dp_{i,j,k}$ 表示前 $i$ 个放了 $j$ 个饼，第 $i$ 个放了 $k$ 个饼的方案。

由于前 $i$ 个一共放了 $j$ 个，容易得出第 $i+1$ 个位置应该给第 $i$ 个添加 $j-pre_i$ 个馅饼（如果是负数就是放回去），贡献就是 $|j-pre_i|$。

所以我们求 $dp_{i,j,k}$ 的时候，直接枚举每个 $l$，对对应的 $dp_{i-1,j-k,l}$ 取 $\min$，最后加上这个贡献即可。但是复杂度 $O(nm^3)$，不能接受。

观察到我们在转移的时候做了大量枚举的无用功。所以令 $f_{i,j,k}$ 表示原 DP 的意义上加一个后缀 $\min$，然后就可以变成 $O(nm^2)$ 了。

[Code](https://codeforces.com/contest/1675/submission/201924483)

---

## 作者：RockyYue (赞：0)

#### 1675G

有 $n$ 个箱子和 $m$ 个小球，初始时第 $i$ 个箱子有 $a_i$ 个小球，其线性排列。每次将一个小球移到相邻箱子。求使 $a_i\ge a_{i+1}$ 的最小操作次数，$n,m\le 250$。

#### Sol

- 本题难点在于合法条件和操作过程均需要靠每个箱子，难以定义只考虑一部分箱子的状态。
- 这种左右移动物品的题目，考虑将双向移动转化成单向移动，如本题设每个箱子只向右边相邻箱子移球，或者从中取球。
  - 这样的好处在于可以定义前缀的状态，后续箱子与前缀箱子不再影响，相当于将需要的球提前移到当前箱子和其右侧箱子中，同时有一个性质，即操作到箱子 $i$ 时前 $i+1$ 个箱子内球数总和不变，因为模拟中并未实施“提前”的操作。
  - 这样的坏处就是在模拟操作过程中，可能有箱子内球数为负，但是发现只要最终状态合法，过程中一切问题都是可以通过调整顺序解决的，故忽略。
- 单向移动的策略解决的前面箱子操作依赖后面箱子的问题，其合法条件只需要额外记录当前箱子操作后球数，这依赖于 $m\le 250$。
- 你发现转移需要用到当前箱子此时的球数，想到性质（*），需要知前面箱子目前状态的总球数，记录之，设 $f_{i,j,k}$ 为考虑前 $i$ 个箱子，最终状态下其一共放 $j$ 个球，箱子 $i$ 放 $k$ 个，这样条件下最少步数。
- 转移考虑 $f_{i,j,k}$ 对后面状态的贡献，对于 $p\le k$，更新 $f_{i+1,j+p,p}\stackrel \min\longleftarrow f_{i,j,k}+|(s_{i+1}-j)-p|$。

---

## 作者：C_Pos_Princess (赞：0)

## [Sorting Pancakes](https://www.luogu.com.cn/problem/CF1675G)

### 题意
给定长度为 $n$ 的序列 $a$，每次操作可以使 $a_i-1,a_{i-1}+1$，求最少需要多少次操作可以使的对于每一个 $i\in [1,n-1]$，$a_{i+1}\ge a_i$。

### 数据范围
$1\le n,m \le 250$

## 题解
看到这个范围我们就可以考虑动态规划了。

对于动态规划，我们需要一步一步推。

我们注意到，对于一个区间，最后一个数的值会影响和限制当前答案，那么我们就把这个作为一个枚举。


我们就限制当前枚举到的这个位置只能往后一个位置放，或者后一个位置拿，这个对于最终答案并没有影响。

如此，我们用 $f_{i,j,k}$ 表示前 $i$ 个位置放 $j$ 个，第 $i$ 个盘子放 $k$ 个的时候的答案，那么我们可以发现，$f_{i,j,k}$ 可以转移到 $f_{i+1,j+p,p}$，注意前 $i$ 个位置定好状态后，这些位置的数值之和不变。

状态转移方程：
$$
f_{i+1,j+p,p} = \min{f_{i+1,j+p,p},f_{i,j,k}+|j+p-S_{i+1}|}
$$

注意到这个方程中 $f_{i,j,k}$ 可以预先处理，我们只需要倒着枚举 $k$ 便可以省掉一位枚举。

## 代码
```
int n,m;
int a[N];
int sum[N];
int f[N][N][N];

int main(){
	read(n,m);
	for(int i = 1;i<=n;++i){
		read(a[i]);
		a[i]+=a[i-1];
	} 
	memset(f,0x3f,sizeof f);
	
	f[0][0][m] = 0;
	for(int i =0;i<n;i++){
		for(int j= 0;j<=m;j++){
			int minn = INF;
			for(int k = m;k>=0;k--){
				minn = min(minn,f[i][j][k]);
				if(j+k<=m) f[i+1][j+k][k] = min(f[i+1][j+k][k],minn+abs(j+k-a[i+1]));
			}
		}
	}
	int ans = INF;
	for(int k = 0;k<=m;k++){
		ans = min(ans,f[n][m][k]);
	}
	cout<<ans;

	return 0;
}
```

---

## 作者：LJ07 (赞：0)

简单 dp 题。这里提供一个不太一样的做法。

看到 $m$ 很小，直接顺次将每个 $a_i$ 拆分成 $a_i$ 个 $i$ 形成序列 $b$。

然后考虑 dp，令 $f_{i,j,z}$ 表示第 $i$ 个盒子，放不多于 $j$ 的糖果，一共放置了 $z$ 个糖果。

我们可以先计算出恰好等于 $j$ 的 $f$，然后前缀取 min，求出真正的 $f$。

那么此时有 $f_{i,j,z}=f_{i+1,j,z-j}+\sum_{x=z-j+1}^z|i-b_x|$。计算代价可以移动指针 + 前缀和计算。

状态数事实上是 $n\sum_{i=1}^{n}\frac{m}{i}=nm\log n$ 级别的，时间复杂度为 $O(nm\log n)$，空间复杂度可以做到 $O(nm)$。

~~然而不知道为什么计算代价直接用暴力二分计算的 $O(nm\log n\log m)$ 比上面做法更优。~~

~~复杂度算错不要喷死我。~~

[code](https://www.luogu.com.cn/paste/kf2dbvhr)

---

## 作者：zhou_ziyi (赞：0)

### Solution

我们可以定义状态 $dp_{i, j, k}$ 表示前 $i$ 盘放 $j$ 张馅饼，第 $i$ 盘放 $k$ 张馅饼，如果我们规定一个盘子只能向右边一个盘子拿或放馅饼。不难发现 $dp_{i, j, k}$ 可以转移到 $dp{i + 1, j + p, p}$。

我们可以定义一个前缀和数组 $S_i$。

我们可以开始考虑状态转移方程：因为我们转移时，只和右边一个盘子有关，所以前 $i$ 个的转移的状态中，前 $i + 1$ 个盘子上的馅饼数就是 $S_{i + 1}$。

所以我们只需从后面一个盘子中去 $j - p + S_{i + 1}$ 个馅饼即可。

$$f_{i + 1, j + p, p} = \min{ \{ f_{i, j, k} + \vert j + p - S_{i + 1} \vert \} }$$

但是我们的时间复杂度为 $O(n \times m ^ 3)$，这肯定是不行的，考虑优化。

由于 $f_{i + 1, j + p, p}$ 会被搜有的 $f_{i, j, k}$ 转移，所以，考虑倒着枚举 $k$。

设 $minv = \min_{u = k} ^ m f_{i, j, u}$，此时的状态转移方程就简化为：

$$f_{i + 1, j + p, p} = \min{ \{ minv + \vert j + p - S_{i + 1} \vert \} } $$

### Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 255, INF = 1e9;
int n, m, ans;
int a[MAXN], sum[MAXN];
int dp[MAXN][MAXN][MAXN];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][m] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= m; j++) {
			int minv = INF;
			for (int k = m; k >= 0; k--) {
				minv = min(minv, dp[i][j][k]);
				if (j + k <= m)
					dp[i + 1][j + k][k] = min(dp[i + 1][j + k][k], minv + abs(j + k - sum[i + 1]));
			}
		}
	ans = INF;
	for (int i = 0; i <= m; i++)
		ans = min(ans, dp[n][m][i]);
	printf("%d", ans);
	return 0;
}
```



---

