# 「FSLOI Round I」山峦

## 题目背景

山峦是造物主弃的酒杯。

## 题目描述

如果一个长度至少为三的序列 $a$ 满足以下条件，则称其为一个**山峰**：

- 设其长度为 $m$。存在一个 $x$，满足 $2\leq x \leq m-1$，并且使得 $a_1,a_2,\cdots,a_x$ 严格单调递增，$a_x,a_{x+1},\cdots,a_m$ 严格单调递减。

特别地，称 $a_x$ 为这个山峰的高度。

如果一个序列 $b$ 满足以下任一条件，则称其为一个**山峦**：

- $b$ 序列是一个**山峰**。

- 可以拆成至少两个连续的子序列，使得每个子序列都是**山峰**，且从左到右**山峰的高度**严格单调递增。

比如，序列 $\lbrace 2,4,3,1,5,2,1 \rbrace$ 是山峦，因为其可以拆分为 $\lbrace 2,4,3 \rbrace,\lbrace 1,5,2,1 \rbrace$ 两个山峰，且山峰高度严格递增。而序列 $\lbrace 2,4,3,5,2,1 \rbrace$ 不是山峦，因为其无法拆分成至少两个连续的子序列，使得每个子序列都是山峰。

现在给定一个长度为 $n$ 的序列 $a$，小 F 想知道，在 $a$ 的所有子序列中，有多少个是**山峦**。由于答案可能很大，请输出其对 $998244353$ 取余后的结果。

请注意，在本题中，即使子序列的元素相同，只要子序列的元素在 $a$ 中的位置不同，仍算作不同的子序列。

## 说明/提示

**【样例 1 解释】**

由 $a_1,a_2,a_4$ 构成的子序列是山峦，由 $a_1,a_3,a_4$ 构成的子序列是山峦。

**【数据规模与约定】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，保证：
- $1 \leq n \leq 500$
- $1 \leq a_i \leq 10^6$

|子任务|分值|特殊性质|
|:-----:|:-----:|:-----:|
|$1$|$10$|$n \leq 18$|
|$2$|$15$|$n \leq 80$|
|$3$|$15$|$A$|
|$4$|$20$|$B$|
|$5$|$40$|无|

特殊性质 $A$：序列 $a$ 是山峰。

特殊性质 $B$：序列 $a$ 中的元素互不相同。

## 样例 #1

### 输入

```
4
1 2 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
7
2 4 3 1 5 2 1```

### 输出

```
35```

## 样例 #3

### 输入

```
20
2 3 5 6 8 7 6 5 6 7 8 8 8 8 4 3 5 6 7 4```

### 输出

```
15085```

# 题解

## 作者：Register_int (赞：17)

先对 $a$ 离散化。思路当然是 $dp_{i,j}$ 算以 $i$ 结尾最高峰为 $j$ 的子序列有多少个。但是有些问题：

- 每个山峰至少要有一个上坡。
- 若出现了 V 字形的峡谷，那么同一个子序列会对应两种划分成山峦的方案。

解决方法是添加一个起始点来区分。设 $dp_{i,j,0/1/2/3}$ 表示以 $i$ 结尾，最高峰为 $j$，当前刚开始上坡/正在上坡/刚开始下坡/正在下坡的方案数，那么答案为 $\sum dp_{i,j,2}+dp_{i,j,3}$。考虑转移：

- $0$ 可以在 $2$ 后面任意接，也可以在 $3$ 后面的下方接。
- $1$ 可以在 $0/1$ 后面的上方接。
- $2$ 可以在 $1$ 后面的下方接，同时更新最高峰。
- $3$ 可以在 $2/3$ 后面的下方接。

转移需要枚举上一个，复杂度为 $O(n)$，总时间复杂度为 $O(n^3)$。发现转移时对于同个 $j$ 求的是所有 $<a_i$ 或 $>a_i$ 的位置之和，可以用树状数组优化到 $O(n^2\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e2 + 10;
const int mod = 998244353;

inline void add(int &x, int y) { x += y, x < mod || (x -= mod); }

int n, m, a[MAXN], b[MAXN], dp[MAXN][MAXN][4], ans;

// dp_i,j,0:新开一个向上单点（只能从下坡转移） 
// dp_i,j,1:上坡
// dp_i,j,2:新开一个向下单点 
// dp_i,j,3:下坡 

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1), m = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	for (int i = 1; i <= n; i++) {
		dp[i][0][0] = 1;
		for (int j = 1; j < i; j++) {
			for (int k = 0; k <= m; k++) {
				add(dp[i][k][0], dp[j][k][2]);
				if (a[i] <= a[j]) add(dp[i][k][0], dp[j][k][3]);
			}
		}
		for (int j = 1; j < i; j++) {
			if (a[j] >= a[i]) continue;
			for (int k = 0; k <= m; k++) {
				add(dp[i][k][1], dp[j][k][0]);
				add(dp[i][k][1], dp[j][k][1]);
			}
		}
		for (int j = 1; j < i; j++) {
			if (a[j] <= a[i]) continue;
			for (int k = 0; k < a[j]; k++) {
				add(dp[i][a[j]][2], dp[j][k][1]);
			}
		}
		for (int j = 1; j < i; j++) {
			if (a[j] <= a[i]) continue;
			for (int k = 0; k <= m; k++) {
				add(dp[i][k][3], dp[j][k][2]);
				add(dp[i][k][3], dp[j][k][3]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			add(ans, dp[i][j][2]);
			add(ans, dp[i][j][3]);
		}
	}
	printf("%d", ans);
}
```

---

## 作者：FL_sleake (赞：12)

### 解题思路

#### Subtask 1

$n \leq 18$，考虑暴力枚举所有子序列，再验证是否是山峦。验证比较繁琐，我采取的方法是找到最长连续上升段，再找最长连续下降段，重复此过程进行判断。以下给出 Subtask 1 的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[510],ans=0;
int b[510],cnt=0;
int c[510],ct=0;
bool check(){
	ct=0;
	if(cnt<3) return 0;//长度不到3
	if(b[1]>=b[2]) return 0;//开头不满足
	if(b[cnt]>=b[cnt-1]) return 0;//结尾不满足
	for(int i=1;i+2<=cnt;i++){
      //如果有连续三个数相同，必定不满足
		if(b[i]==b[i+1]&&b[i+1]==b[i+2]) return 0;
	}
	int id=1;
	while(id<cnt){
		while(id+1<=cnt&&b[id+1]>b[id]) id++;//找上升段
		c[++ct]=id;//记录
		if(b[id+1]==b[id]) return 0;
      //注意上升段的后一位不严格小于当前位则不满足
      //比如 1,2,3,3,2
		while(id+1<=cnt&&b[id+1]<b[id]) id++;//找下降段
		if(b[id]==b[id+1]) id++;
      //注意此时相等需要手动往后走一位
      //比如 2,4,2,2,5,2
	}
  //山峰高度不递增则不满足
	for(int i=1;i<ct;i++) if(b[c[i]]>=b[c[i+1]]) return 0;
  //间隔小于2则不能拆分成山峰
	for(int i=1;i<ct;i++) if(c[i+1]-c[i]<=2) return 0;
	return 1;
}
signed main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	int num=0;
	for(int i=0;i<(1ll<<n);i++){
      //枚举所有子序列
		cnt=0;
		for(int j=0;j<n;j++) if((i>>j)&1) b[++cnt]=a[j];
		if(check()) ans++;
	}
	cout<<ans<<endl;
	return 0;
} 
```

#### Subtask 2 & 3 & 4 & 5

考虑 dp。我们考虑先去掉山峦的最后一段连续下降段。比如对于 $1,2,3,4,3,2,1$，我们暂且认为 $1,2,3,4$ 是合法的一段。再记山峰的高度所在位置为**山顶**。记 $dp_i$ 表示以 $i$ 为最后一个**山顶**，前 $i$ 位有多少合法子序列。

考虑预处理出两个二维数组 $f1,f2$。

$f1_{i,j}$ 表示以 $i$ 为山顶，以 $j$ 为结尾的下降段的数量。

$f2_{i,j}$ 表示以 $i$ 为山顶，以 $j$ 为开头的上升段的数量。

这样的话 $f1,f2$ 都可以在 $\Theta(n^3)$ 复杂度内预处理出来。代码如下：

```cpp
for(int i=1;i<=n;i++){
	f1[i][i]=1;
	for(int j=i+1;j<=n;j++){
		for(int k=i;k<=j-1;k++){
			if(a[k]>a[j]) f1[i][j]=(f1[i][j]+f1[i][k])%mod;
		}
	}
}
for(int i=n;i>=1;i--){
	f2[i][i]=1;
	for(int j=i-1;j>=1;j--){
		for(int k=j+1;k<=i;k++){
			if(a[k]>a[j]) f2[i][j]=(f2[i][j]+f2[i][k])%mod;
		}
	}
}
```

接下来就可以对 $dp$ 数组进行初始化了： 

$$dp_i=\sum_{j=1}^{i-1}f2_{i,j}$$

然后考虑转移。枚举两个山顶 $i,j$，不妨 $i>j$，那么 $dp_i=dp_i+dp_j\times num$，其中 $num$ 表示 $j$ 到 $i$ 这一段中有多少个子序列满足如果 $1$ 到 $j$ 合法，则 $1$ 到 $i$ 合法。感性理解一下就是求 $j$ 到 $i$ 之间有多少个“山谷”。此处“山谷”表示先下降后上升的子序列。

那么如何求 $num$ 呢？考虑枚举“谷底”。因为山谷满足先单调递减再单调递增，那么不同的“谷底”一定对应不同的山谷（先不考虑数字相同的情况）。假设当前枚举的谷底下标为 $k$，则合法的山谷有 $f1_{j,k}\times f2_{i,k}-1$ 个。其实就是 $j$ 到 $k$ 需要下降，$k$ 到 $i$ 需要上升。那么减一是什么呢？减一是形如 $\cdots,3,2,4$ 这种情况，其中 $3,4$ 为当前枚举的山顶，$2$ 为当前枚举的谷底。也就是说，不能单独地只选择一个谷底。

接下来我们再考虑相等的数。比如 $\cdots,3,2,2,4$ 是合法的。此时产生的山谷应该是 $f1_{j,k_1}\times f2_{i,k_2}$ 个，其中 $k_1,k_2$ 满足 $a_{k_1}=a_{k_2}$ 且 $k_1 < k_2$。我们发现暴力枚举 $k_1,k_2$ 算的话复杂度是 $\Theta(n^2)$，但是外面已经有了一个 $\Theta(n^2)$ 了，所以需要优化掉一个 $n$。当然 Subtask 2 此时可以过了。

上述中 $k_2$ 产生的贡献应该是与前面一堆 $k_1$ 相乘之和，那不就是与前面一堆 $k_1$ 之和相乘吗！于是开一个数组 $sum$ 记录 $f1_{j,k_1}$ 之和即可。到此为止，我们就求出来了 $num$，代码如下：

```cpp
int solve(int l,int r){
	int ans=0;
	for(int i=l+1;i<=r-1;i++){
		if(f1[l][i]&&f2[r][i]) ans=(ans+f1[l][i]*f2[r][i]%mod-1+mod)%mod;
		ans=(ans+sum[a[i]]*f2[r][i]%mod)%mod;
		sum[a[i]]=(sum[a[i]]+f1[l][i])%mod;
	}
	for(int i=l+1;i<=r-1;i++) sum[a[i]]=0;
	return ans;
}
```

到此为止，$dp_i$ 就可以求出来了。注意开头所说的 $dp_i$ 的定义，我们应该在 $i$ 后面再接上一段下降段，才是真正的山峦。这里再用一步乘法原理就可以统计出最终答案了：

```cpp
int ans=0;
for(int i=1;i<=n;i++){
	int Sum=0;
	for(int j=i+1;j<=n;j++) Sum=(Sum+f1[i][j])%mod;
	ans=(ans+Sum*dp[i]%mod)%mod;
}
cout<<ans<<endl;
```

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int n,a[510],f1[510][510]={0},f2[510][510]={0},dp[510]={0};
int sum[1000010];
int solve(int l,int r){
	int ans=0;
	for(int i=l+1;i<=r-1;i++){
		if(f1[l][i]&&f2[r][i]) ans=(ans+f1[l][i]*f2[r][i]%mod-1+mod)%mod;
		ans=(ans+sum[a[i]]*f2[r][i]%mod)%mod;
		sum[a[i]]=(sum[a[i]]+f1[l][i])%mod;
	}
	for(int i=l+1;i<=r-1;i++) sum[a[i]]=0;
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		f1[i][i]=1;
		for(int j=i+1;j<=n;j++){
			for(int k=i;k<=j-1;k++){
				if(a[k]>a[j]) f1[i][j]=(f1[i][j]+f1[i][k])%mod;
			}
		}
	}
	for(int i=n;i>=1;i--){
		f2[i][i]=1;
		for(int j=i-1;j>=1;j--){
			for(int k=j+1;k<=i;k++){
				if(a[k]>a[j]) f2[i][j]=(f2[i][j]+f2[i][k])%mod;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i-1;j++) dp[i]=(dp[i]+f2[i][j])%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i-3;j++){
			if(a[j]>=a[i]) continue;
			dp[i]=(dp[i]+dp[j]*solve(j,i)%mod)%mod;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		int Sum=0;
		for(int j=i+1;j<=n;j++) Sum=(Sum+f1[i][j])%mod;
		ans=(ans+Sum*dp[i]%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_Kenma_ (赞：4)

# P11079 解题报告

## 前言

大家好，我是 30min 切 T3，到结束也不会 T4 选手。

来写一篇题解加深印象。

~~出神秘 DP 的出题人能不能少一点~~、

PS：看你有没有认真读题：

以下序列中，哪一个是****山峦****：

$A:1,2,3,2,1,1,2,3,4,1$

$B:1,2,3,3,2,1,1,2,3,1$

$C:1,2,3,2,1,4,1,2,3,4,1$

$D:1,2,1,1,2,1,1,2,1,1,2$

## 思路分析

首先一眼 DP，考虑 DP 的设计。

经过一段时间的尝试，发现直接 DP 出答案很困难。因为题目对山峦的限制很多（具体详见上文的选择题），所以很难将序列合并处理。

赛时我想了一个有 $O(n^3)$ 个状态的 DP，但是加上转移 $O(n^2)$，这个思路和暴力同分。

考虑弱化条件，如果将山峦最后一段上升和下降的部分分开，问题会变得简单一些。

具体地，设 $f_i$ 表示以 $i$ 为山顶的山峦总数，$f1_{l,r}$ 表示区间 $[l,r]$ 中单调下降的子序列个数，$f2_{l,r}$ 表示区间 $[l,r]$ 中单调上升的子序列个数，答案为 $ans$。则有：

$$ans = \sum_{i=1}^{n} \sum_{j=i+1}^{n} dp_i \cdot f1_{i,j}$$

解释一下，就是将最后一段的上升部分和下降部分拼在一起，因为求方案数，所以乘法原理。

考虑怎样求解这个柿子。

注意到 $f1$ 和 $f2$ 的求解是平凡的，具体形如 LCS 的 DP 过程。

瓶颈在于对 $dp$ 序列的求解。

为了简化问题，设 $num_{l,r}$ 表示在区间 $[l,r]$ 中，如果区间 $[1,l]$ 的子序列合法，加上这个子序列依然合法，这样的子序列个数。

易得转移：$dp_i= \sum_{j=1}^{i-3} num_{j,i} \cdot dp_j$，其中 $a_j<a_i$。

考虑怎样求解 $num_{l,r}$。

首先考虑什么样的子序列是被计算在 $num$ 之中的。

首先因为序列的左右端点 $l$ 和 $r$ 都被钦定为山顶，所以一个序列是合法的，当且仅当它是：

1. 山谷，即形如 $3,2,1,2,3$ 的序列，但 $3,2,3$ 是不合法的；
2. 盆地，即形如 $3,2,1,1,2,3$ 的序列，但 $3,2,1,1,1,2,3$ 是不合法的。

其实山谷和盆地的区别就在于最底部的元素是否相等。

无论是山谷还是盆地，都可以被视为一段单调上升的序列和一段单调下降的序列相接。这样我们前面求的 $f1$ 和 $f2$ 就有用了。

考虑怎样计算这样的序列个数。

对于情况 $1$，枚举谷底即可。

形如：$num_{l,r}=\sum_{i=l+1}^{r-1} f1_{l,i} \cdot f2_{i,r}-1$。其中减 $1$ 去掉的是不合法情况。

对于情况 $2$，同理，我们需要枚举两个相等的元素作为低谷。

形如 $num_{l,r}=\sum_{i=l+1}^{r-1} \sum_{j=i+1}^{r-1} f1_{l,i} \cdot f2_{j,r}$，其中 $a_i=a_j$。

注意到情况 $2$ 的复杂度是 $O(n^2)$ 的，整体复杂度变为 $O(n^4)$，无法接受。观察发现，因为转移是连续的，用前缀和优化，将 $a_i$ 相同的合并计算前缀和即可优化到 $O(n)$。

这样，我们就在 $O(n^3)$ 的复杂度内解决了这个问题。

总结一下所有转移柿子，$f1$ 和 $f2$ 因为平凡就不列出了。

- $ num_{l,r}=\sum_{i=l+1}^{r-1} f1_{l,i} \cdot f2_{i,r}-1 $；
- $ num_{l,r}=\sum_{i=l+1}^{r-1} \sum_{j=i+1}^{r-1} f1_{l,i} \cdot f2_{j,r}$，其中 $a_i=a_i$；
- $dp_i= \sum_{j=1}^{i-3} num_{j,i} \cdot dp_j$，其中 $a_j<a_i$；
- $ans = \sum_{i=1}^{n} \sum_{j=i+1}^{n} dp_i \cdot f1_{i,j}$。

## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,a[505],b[505],f1[505][505],f2[505][505],dp[505],sum[1000005],cnt,num,ans;
int get(int l,int r){
	int ans=0;
	for(int i=l+1;i<r;i++){
		if(f1[l][i] && f2[i][r]) ans=(ans+f1[l][i]*f2[i][r]%mod-1+mod)%mod;
		ans=(ans+sum[a[i]]*f2[i][r]%mod)%mod;
		sum[a[i]]=(sum[a[i]]+f1[l][i])%mod;
	}
	for(int i=1;i<=n;i++){
		sum[a[i]]=0;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]; 
	}
	for(int i=1;i<=n;i++){
		f1[i][i]=1;
		for(int j=i+1;j<=n;j++){
			for(int k=i;k<j;k++){
				if(a[k]>a[j]) f1[i][j]=(f1[i][j]+f1[i][k])%mod;
			}
		}
	}
	for(int i=n;i>=1;i--){
		f2[i][i]=1;
		for(int j=i-1;j>=1;j--){
			for(int k=j+1;k<=i;k++){
				if(a[k]>a[j]) f2[j][i]=(f2[j][i]+f2[k][i])%mod;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			dp[i]=(dp[i]+f2[j][i])%mod;
		}
		for(int j=1;j<=i-3;j++){
			num=get(j,i);
			if(a[i]>a[j]) dp[i]=(dp[i]+dp[j]*num%mod)%mod;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ans=(ans+f1[i][j]*dp[i]%mod)%mod;
		}
	}
	cout<<ans;
	return 0;
}
```

## 后记

什么时候才能切这种难度的 DP 啊，我是 DP 超级低手。

---

## 作者：Lele_Programmer (赞：2)

# P11079 题解

## 思路

考虑 DP，设 $f_{i,j,k}$ 为在第 $i$ 个点结束的山峦子序列，其中最右边的一座山峰的山顶高度是 $j$，现在构成的形状形如 $k$ 的，方案数量。其中 $k \in [0,5]$，对应的形状如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/vjv9lczp.png)

这里解释一下以上 6 种情况。

第 0 种，由山顶向下走了一格，然后往上走一格。

第 1 种，由山顶向下走了一格，然后向上走了两格以上。

第 2 种，由山顶向下走了两格以上，然后向上走了两格以上。

第 3 种，由山顶向下走了一格，

第 4 种，由山顶向下走了两格以上。

第 5 种，平着走了一格。

接下来考虑状态之间如何转移。

第 0 种，只能由第 3 种向上走一格，因此 $f_{i,k,0}=\sum\limits_{j=1}^{i-1}f_{j,k,3}$。

第 1 种，可以由第 0 种向上走一格，也可以由第 1 种向上走一格，因此 $f_{i,k,1}=\sum\limits_{j=1}^{i-1}(f_{j,k,0}+f_{j,k,1})$。

第 2 种，可以由第 2 种第 4 种得到，把第 5 种也归到这里来，因此 $f_{i,k,2}=\sum\limits_{j=1}^{i-1}(f_{j,k,2}+f_{j,k,4}+f_{j,k,5})$。

第 3 种，向下走以形成一座山峰，必须保证山峰的顶端严格递增，所以在 $k<a_j$ 的情况下，有 $f_{i,a_j,3}=\sum\limits_{j=1}^{i-1}(f_{j,k,1}+f_{j,k,2})$。

第 4 种，由第 3 第 4 两种情况得到，因此 $f_{i,k,4}=\sum\limits_{j=1}^{i-1}(f_{j,k,3}+f_{j,k,4})$。

第 5 种，由第 3 第 4 两种情况得到，因此 $f_{i,k,5}=\sum\limits_{j=1}^{i-1}(f_{j,k,3}+f_{j,k,4})$。

因为从山顶往下走一格之后往上走，若再往下走一格，就不能形成两座并列的山峰了，因为这样它们的一个端点会重合，所以第 0 种情况后，只能往上走。

第 5 种情况也一样，山峰右边是严格递减，左边严格递增，出现两个相邻的相等的数，那一定是一个属于左边那座山的右端点，一个属于右边那座山的左端点。

发现第二维的值域达到了 $10^6$，考虑离散化，于是降到 $5 \times 10^2$。

最后考虑统计答案，为了形成山峦，序列最右边一定是一座山峰的下降部分，因此 $ans = \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{p}(f_{i,j,3}+f_{i,j,4})$，其中 $p$ 表示离散化后的值域。

设值域 $p$ 与 $n$ 同阶，则时间复杂度为 $\mathcal{O}(n^3)$。

## 代码

状态转移充分推导之后，代码就不难写了。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
typedef pair<int,int> pii;

const int N=505;
const int mod=998244353;

int n;
int arr[N];
int f[N][N][6];
vector<int> nums;
int p;

bool cmp(const int& a,const int& b) {
    return a<b;
}

signed main() {
    scanf("%lld",&n);
    _rep(i,1,n) scanf("%lld",&arr[i]);
    _rep(i,1,n) nums.emplace_back(arr[i]);
    sort(nums.begin(),nums.end(),cmp);
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    p=nums.size()-1;
    _rep(i,1,n) arr[i]=lower_bound(nums.begin(),nums.end(),arr[i])-nums.begin();
    // printf("ARR: ");
    // _rep(i,1,n) printf("%lld ",arr[i]);
    // putchar(10);
    _rep(i,1,n) {
        f[i][0][0]=1;
        _rep(j,1,i-1) {
            if (arr[j]<arr[i]) {
                _rep(k,0,p) {
                    f[i][k][0]=(f[i][k][0]+f[j][k][3])%mod;
                    f[i][k][1]=(f[i][k][1]+f[j][k][0]+f[j][k][1])%mod;
                    f[i][k][2]=(f[i][k][2]+f[j][k][2]+f[j][k][4]+f[j][k][5])%mod;
                }
            } else if (arr[j]>arr[i]) {
                _rep(k,0,p) {
                    if (k<arr[j]) {
                        f[i][arr[j]][3]=(f[i][arr[j]][3]+f[j][k][1]+f[j][k][2])%mod;
                    }
                    f[i][k][4]=(f[i][k][4]+f[j][k][3]+f[j][k][4])%mod;
                }
            } else {
                _rep(k,0,p) {
                    f[i][k][5]=(f[i][k][5]+f[j][k][3]+f[j][k][4])%mod;
                }
            }
        }
    }
    // _rep(i,1,n) {
    //     _rep(j,0,p) {
    //         _rep(k,0,4) {
    //             printf("f[%lld][%lld][%lld] = %lld\n",i,j,k,f[i][j][k]);
    //         }
    //     }
    // }
    int ans=0;
    _rep(i,1,n) {
        _rep(j,0,p) {
            ans=(ans+f[i][j][3]+f[i][j][4])%mod;
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Silence_water (赞：2)

由于题目限制从左到右山峰高度严格单调递增，设计 $f_i$ 表示 $i$ 为最后一座山峰的山顶时的子序列种类数。为了方便转移，先不考虑 $i$ 之后的下坡问题。

对于山顶 $j$ 与山顶 $i$ 之间的转移，可以考虑枚举中间点 $k,l$ 作为两个山脚，即选取一个以 $j$ 为起点 $k$ 为终点的单调递减序列，再选取一个以 $l$ 为起点 $i$ 为终点的单调递增序列。

但这样会算重，譬如 `5 4 3 4 5` 的一个山谷，存在 `5 4|3 4 5` 和 `5 4 3|4 5` 两种划分，但实际上是一个序列。因此只需考虑 $a_k\le a_l$ 时的划分情况，保证不重。

记 $dn(i,j)$ 表示以 $i,j$ 为端点的单调递减子序列种类数，$up(i,j)$ 表示单增。则该部分的贡献为 $f(j)\times dn(j,k)\times up(l,i)$。

考虑未被计入的部分，即 $a_k > a_l$ 时，此时上坡部分只会有 $l$ 和 $i$。该部分的贡献为 $f(j)\times dn(j,k)$。

根据上述不难写出 $O(n^4)$ 的代码。

```cpp
for(int i=1;i<=n;i++)
{
    for(int j=1;j<i;j++)// 最后一个下坡 j 为山顶 i 为山脚
        if(a[j]>a[i])ADD(ans,f[j]*dn[j][i]%P);
    for(int j=1;j<i;j++)// 第一个上坡 j 为山脚 i 为山顶
        if(a[j]<a[i])ADD(f[i],up[j][i]);
    for(int j=1;j<i;j++)
        if(a[j]<a[i])
            for(int k=j+1;k+2<=i;k++)
                for(int l=k+1;l<i;l++)
                {
                    if(a[j]>a[k]&&a[k]<=a[l]&&a[l]<a[i])
                        ADD(f[i],f[j]*dn[j][k]%P*up[l][i]%P);
                    else if(a[j]>a[k]&&a[k]>a[l]&&a[l]<a[i])
                        ADD(f[i],f[j]*dn[j][k]%P);
                }
}
```

下面对两部分分别进行优化。

对于第一个转移，考虑压缩 $a_k\le a_l < a_i$ 的情况，即预处理出以 $k$ 为前一座山的山脚，拼接上一个山脚高度 $\ge a_k$ 的上坡，记为 $mo(k,i)$，则贡献为 $f(j)\times dn(j,k)\times mo(k,i)$。

对于第二个转移，可以直接将 $k$ 包含在下坡内，那么等价于选取以 $j$ 和 $l$ 为端点且长度 $\ge 3$ 的下坡，并保证 $a_l\le a_i$。贡献为 $f(j)\times (dn(j,l)-1)$。（即删去长度为 $2$ 的情况）

根据上述可以写出 $O(n^3)$ 的代码。

```cpp
for(int i=1;i<=n;i++)
{
    for(int j=1;j<i;j++)
        if(a[j]>a[i])
            ADD(ans,f[j]*dn[j][i]%P);
    for(int j=1;j<i;j++)
        if(a[j]<a[i])ADD(f[i],up[j][i]);
    for(int j=1;j<i;j++)
        if(a[j]<a[i])
        {
            for(int k=j+1;k<i;k++)
                ADD(f[i],f[j]*dn[j][k]%P*mo[k][i]%P);
            for(int k=j+1;k<i;k++)
                if(a[j]>a[k]&&a[k]<a[i])ADD(f[i],(dn[j][k]-1+P)%P*f[j]%P);
        }
}
printf("%lld",ans);
```

---

## 作者：zichen3004 (赞：0)

本篇题解将**不会**给出代码。

读题，很容易发现这是一个子序列问题。可能会想到考虑连续的两个峰，发现不太可做，考虑相邻的峰和谷，发现可做：

预处理相邻两个点的上升或下降子序列数量，这个数量乘上上一个峰/谷的 dp 值就是当前点的 dp 值。

以上是思路一，和官方题解的思路大致相同。

另外一个 dp 思路只考虑上一个点，并不考虑是否是峰或谷。

利用 $dp[i][j][k]$ 来表示以第 $i$ 个点结尾，上一个高峰的值为 $j$ 目前状态为 $k$ 的方案数量。

对于 $k$ 有三种状态：一个峰的第一项（状态 $1$）；一个峰正在上升但非第一项（状态 $2$）；一个峰已经开始下降（状态 $3$）。

对于 $3$ 可以接在 $2$ 或 $3$ 后面；对于 $2$ 可以接在 $2$ 或 $1$ 后面；对于 $1$ 可以接在 $3$ 后面（此处有 update，在文末查看）。

特别地，只有当上一个的高度大于 $j$，当前点才可以进入状态 $3$，并将最高高度设置为上一个点的高度。

这是第二个思路，比第一个难写点，是本人一开始的想法，一开始以为可以做到平方复杂度，最后发现一开始的思路假了。

最后吐槽下，本题最大难度在于读题。


---

update 2024.9.24

感谢 Register_int 大神的指出。

上面的 trick 有一个 bug，就是在上升超过两项以后，有两项可以是整个数列的第一项，这会导致有的方案会被计算两次。

解决的方法也很简单，除非前面的一个峰为第一次下降，否则强制后面的峰比前面的最后一个高，然后多设一种状态，表示下降且已经超过一项，具体的在下面。

对于 $k$ 有**四**种状态：一个峰的第一项（状态 $1$）；一个峰正在上升但非第一项（状态 $2$）；一个峰已经开始下降且为第一项（状态 $3$）；一个峰正在下降且至少为第二项（状态 $4$）。

对于 $4$ 可以接在 $3$ 或 $4$ 后面，对于 $3$ 可以接在 $2$ 后面；对于 $2$ 可以接在 $1$ 或 $2$ 后面；对于 $1$ 可以接在 $3$ 后面，特别地，如果比前面的高，$1$ 可以接在 $4$ 后面。

---

