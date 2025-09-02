# [ABC396C] Buy Balls

## 题目描述

现有 $N$ 个黑色球和 $M$ 个白色球。  
每个球都有一个价值：第 $i$ 个（$1 \leq i \leq N$）黑色球的价值为 $B_i$，第 $j$ 个（$1 \leq j \leq M$）白色球的价值为 $W_j$。

请选择 **零个或多个** 球，使得所选黑色球的数量 **不少于** 白色球的数量。求所选球的价值总和的最大可能值。

## 说明/提示

### 约束条件

- $1 \leq N, M \leq 2 \times 10^5$
- $-10^9 \leq B_i, W_j \leq 10^9$
- 输入中的所有值均为整数

### 样例解释 1

选择第 $1,2,4$ 个黑色球和第 $1$ 个白色球时，总价值为 $8 + 5 + 3 + 3 = 19$，这是最大值。

### 样例解释 2

选择第 $1,3$ 个黑色球和第 $1,3$ 个白色球时，总价值为 $5 + (-2) + 8 + 4 = 15$，这是最大值。

### 样例解释 3

允许不选择任何球，此时总价值为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4 3
8 5 -1 3
3 -2 -4```

### 输出

```
19```

## 样例 #2

### 输入

```
4 3
5 -10 -2 -5
8 1 4```

### 输出

```
15```

## 样例 #3

### 输入

```
3 5
-36 -33 -31
12 12 28 24 27```

### 输出

```
0```

# 题解

## 作者：wyyinput (赞：3)

贪心。首先对 $B$ 和 $W$ 从大到小排序，如果上下同一位置 $B_i$ 和 $W_i$ 的元素相加大于等于零，就加上。否则就一直加 $B_i$ 直到 $B_i$ 小于等于零。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200001],b[200001],ans,i;
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	for(int i=1;i<=m;i++)
		scanf("%lld",b+i);
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+m+1,cmp);
	for(i=1;i<=min(n,m);i++){
		if(a[i]>=0&&b[i]>=0)
			ans+=a[i]+b[i];
		else
			break;
	}
	if(b[i]<=0){
		for(;i<=n;i++){
			if(a[i]>=0)
				ans+=a[i];
			else
				break;
		}
		printf("%lld",ans);
		return 0;
	}
	else if(a[i]<=0){
		for(;i<=min(n,m);i++){
			if(a[i]+b[i]>=0)
				ans+=a[i]+b[i];
			else
				break;
		}
		printf("%lld",ans);
		return 0;
	}
	else if(n>m){
		for(;i<=n;i++){
			if(a[i]>=0)
				ans+=a[i];
			else
				break;
		}
		printf("%lld",ans);
		return 0;
	}
	return 0;
}
```

---

## 作者：FlowerAccepted (赞：2)

## 解题思路

考虑贪心。

显然，选相同数量的球，肯定选尽量大的。

为了做到这点，可以先给两个数组**降序**排序。可以将 `std::sort` 配合着 `std::greater<int>` 使用。

```cpp
sort(b + 1, b + n + 1, greater<int>());
sort(w + 1, w + m + 1, greater<int>());
```

设 $ansn$、$ansm$ 分别为选出的白球、黑球数量。

首先正数能选的都选，只要增加就是好。注意 $ansm$ 不能超过 $n$ 也不能超过 $m$。

然后如果 $ansn < ansm$ 且 $W_{ansn} + B_{ansm}$ 是正数（写非负数也行，因为在价值和相同的情况下拿多少球不重要）就将 $ansn$ 增加 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hsidsr14.png)

$$
\footnotesize
\text{图 S-AT\_abc396\_b-1} \\
\text{样例解释，鸣谢 M28 的 Heavy 贴图}
$$

最后求和即可。

具体细节见代码。

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring> // 不用万能头
using namespace std;

const int MAXN = 2e5 + 5; // 开大数组防越界
int b[MAXN], w[MAXN];

int main() {
    int n, m, ansn = 0, ansm = 0;
    long long sum = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> b[i];
    }
    for (int i = 1; i <= m; i ++) {
        cin >> w[i];
    }
    sort(b + 1, b + n + 1, greater<int>());
    sort(w + 1, w + m + 1, greater<int>());
    for (int i = 1; i <= n && b[i] >= 0; i ++) {
        ansn = i;
    }
    for (int i = 1; i <= min(n, m) && w[i] >= 0; i ++) {
        ansm = i;
    }
    while (ansm > ansn && b[ansn + 1] + w[ansn + 1] > 0) {
        ansn ++;
    }
    ansm = min(ansn, ansm);
    for (int i = 1; i <= ansn; i ++) {
        sum += b[i];
    }
    for (int i = 1; i <= ansm; i ++) {
        sum += w[i];
    }
    cout << sum;
    return 0;
}

```

## 复杂度分析

其实瓶颈在排序，是 $O(n\log n)$ 的规模。

---

## 作者：MaiJingYao666 (赞：2)

# AT_abc396_c [ABC396C] Buy Balls 题解  
明显的贪心题。
### 题目翻译  
选 $x$ 个黑球和 $y$ 个白球，$x \ge y$，令这几个球值之和最大。
***
### 解题思路  
首先，对于两个数组 $B$ 和 $W$，先把球从大到小排序。  
贪心策略可分几种情况讨论：  
1.    $B_i,W_i > 0$，显然 2 个球都选。
2.    $B_i+W_i > 0$ 且 $W_i > 0$。首先由题不能只选 $W_i$ 而不选另一个 $B_j$，选择任意的 $j>i$ 显然劣于选 $B_i$，不选也劣，所以也都选。
3.    $B_i > 0$ 且 $W_i \le 0$。显然只选 $B_i$ 会更好。
4.    $B_i,W_i < 0$，显然全都不选。

综上所述，对于空位置先赋值 $-\infty$，然后枚举到 $\max(n,m)$ 就可以了。  
记得开 `long long`。

---

## 作者：Tomwsc (赞：2)

# AT_abc396_c [ABC396C] Buy Balls 题解

## 题意

给定两个数列，可以在这两个数列中选一些数。其中在第一个数列中选的数的个数必须要大于在第二个数列中选的数的个数。问通过选数可得到的最大值。

## 思路

贪心好题。

首先可以想到对于这两个数列，如果都选择非负数肯定可以得到最优解，于是不妨先在输入时计算所有的非负数的和。
- 如果此时选择的数的个数满足题目的条件，即在第一个数列中选的数的个数大于在第二个数列中选的数的个数，那直接输出答案即可。
  
- 否则，进行贪心动态调整：

  设 $num_1$ 表示在第一个数列中选的数的个数，$num_2$ 表示在第二个数列中选的数的个数。可以发现，要想要 $num1\ge num_2$，要么让 $num_1+1$ 要么让 $num_2-1$。其中：

  - $num_1+1$ 是令原本的答案加上一个未选的数，所以这个数要尽量大。
  - $num_2-1$ 是令原本的答案减去一个选了的数，所以这个数要尽可能小。

  于是便可以把在第一个数列中的负数存到一个数组中，把在第二个数列中的正数存到一个数组中。然后第一个数组按从大到小排序，第二个数组按从小到大排序。接着用双指针维护在这两个数列中要选的数，若加上一个数比减去一个数更优，就加上这个数然后让第一个指针往后移，否则减去一个数，第二个指针往后移。直至满足 $num_1\ge num_2$。

## 代码

注意判一下两个指针是否越界，否则会错两个点。

```cpp
#include<bits/stdc++.h>
#define int long long
#define regint register int
using namespace std;
const int MAXN = 2e5 + 10;
int n , m;
int cnt1 , cnt;
int a[MAXN] , b[MAXN];

inline bool cmp(int a , int b) {
	return a > b;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int ans = 0 , num1 = 0 , num2 = 0;
	cin >> n >> m;
	for(regint i = 1;i <= n;i ++) {
		int x;
		cin >> x;
		if(x >= 0) {
			ans += x;
			num1 ++;
		} else
			a[++ cnt] = x;
	}
	for(regint i = 1;i <= m;i ++) {
		int x;
		cin >> x;
		if(x >= 0) {
			b[++ cnt1] = x;
			ans += x;
			num2 ++;
		}
	}
	sort(a + 1 , a + 1 + cnt , cmp);
	sort(b + 1 , b + 1 + cnt1);
	if(num1 >= num2)
		cout << ans << '\n';
	else {
		int l = 1 , r = 1;
		while(num1 < num2) {
			if(l <= cnt && ans + a[l] >= ans - b[r]) {
				ans += a[l];
				l ++;
				num1 ++;
			} else if(r <= cnt1) {
				ans -= b[r];
				r ++;
				num2 --;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}

---

## 作者：ryf2011 (赞：2)

# 题目思路
注：本题中所提到的 $N,M$ 是题目中给出的变量。

老规矩，看数据范围，照样是无法暴力，我们考虑优化。

我们考虑先将黑球数组（本文中用 $B$ 表示）和白球数组（本文中用 $W$ 表示）按照大小从大到小排序。排序完成后，遍历两个数组，计算值为非负整数（即一个大于或等于 $0$ 的数）的黑球和白球数量。

在本文中，黑球用 $cntb$ 表示，白球用 $cntw$ 表示。同时用一个答案变量来记录这些球的值之和。

如果 $cntb \ge cntw$，说明黑球满足条件数量比白球要多，正好符合题目所要求的条件，即选择的黑球数量至少等于选择的白球数量。此时，其他未选的值一定都为负数，那么答案已经是最优的，输出即可。

如果 $cntb < cntw$，那么黑球满足条件数量少于白球，不符合要求，我们采用另一种方法。

我们用一个变量 $i$ 同时遍历两个数组（枚举 $1$ 到 $\min(N,M)$ 这个范围），如果 $W[i] + B[i] > 0$，即排序后，当前枚举到的上下对齐的两个数之和大于 $0$，说明此时如果加上这个和，答案将会更优，那么答案加上这个值。

注意一点，满足上述条件时，不能只选择其中一个值相加，因为这是两个值共同对答案的贡献，如果只加其中一个，后续将不能持续跟踪计算黑球和白球已选择的数量，且无法完成下一步具体选择哪种球的规划。

一直这样判断，当枚举到一个位置不满足此条件时，退出循环，且输出答案。

注意（作者被坑）如果你选择了作者上文描述的方法，且用了先输出答案后结束程序的方法，请一定要在循环外部再写一行输出代码，因为在某种特殊情况下，在执行完循环后，仍未输出答案。下面给出一组 $N = 4,M = 3$ 的例子。

||$\bm{1}$|$\bm{2}$|$\bm{3}$|$\bm{4}$|
|:-:|:-:|:-:|:-:|:-:|
|$B$ 数组|$-5$|$-2$|$-1$|$-5$|
|$W$ 数组|$8$|$10$|$7$||

排序完成后，数组将重新排列。

||$\bm{1}$|$\bm{2}$|$\bm{3}$|$\bm{4}$|
|:-:|:-:|:-:|:-:|:-:|
|$B$ 数组|$-1$|$-2$|$-5$|$-5$|
|$W$ 数组|$10$|$8$|$7$||

可以发现，即使遍历完成后，仍然不会输出结果，因为范围内所有的值都满足条件，所以，此时要在循环外再写一行输出代码。

# 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int max_n=2e5+5;
int n,m,b[max_n],w[max_n],ans; //ans：记录答案 
int cntb,cntw; //计数 
bool cmp(int x,int y){ //强制从大到小排序 
	return x>y;
}
signed main(){
	scanf("%lld %lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	sort(b+1,b+n+1,cmp); //排序 
	for(int i=1;i<=m;i++){
		scanf("%lld",&w[i]);
	}
	sort(w+1,w+m+1,cmp); //排序 
	for(int i=1;i<=n;i++){ //计数 
		if(b[i]>=0){
			cntb++;
			ans+=b[i];
		}
	}
	for(int i=1;i<=m;i++){ //计数 
		if(w[i]>=0){
			cntw++;
			ans+=w[i];
		}
	}
	if(cntb>=cntw){ //黑球满足条件数大于或等于白球满足条件数，输出答案 
		printf("%lld\n",ans);
	}
	else{ //否则，重置答案，重新计算 
		ans=0;
		for(int i=1;i<=min(n,m);i++){ //计算 
			if(w[i]+b[i]>=0){ //比答案更优，更新答案 
				ans+=(w[i]+b[i]);
			}
			else{
				break;
			}
		}
		printf("%lld\n",ans); //输出 
	}
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：H_dream (赞：1)

# 考察知识
1. 贪心
2. 分类讨论

# 题目大意
有 $N$ 个黑球和 $M$ 个白球，每个球都有一个值。在黑球的数量大于等于白球的数量的前提下，使所选球的数值和最大。
注意：**数值可能为负数**。

# 思路
考虑贪心。

显然，黑球的所有正数我们都会选，设所选黑球数量为 $n$，白球剩余的正数数量为 $m$，之后会出现两种情况：

- 当 $n \ge m$ 时：显然，应该把这 $m$ 个球都选了，此时即为最优。因为剩余数全为负数，再次选择必然会使总和变小。
- 当 $n < m$ 时：先将最大的 $n$ 个白球计入总和。之后我们先考虑数值最大的白球，设为 $x$，设此时未选择的数值最大的黑球为 $y$，那么如果此时 $x + y > 0$，则加入总和（因为可以增加总和），否则此时总和即为答案。之后按以上方式一直计算其他球。

# 实现
我们可以先对两个数组进行排序，之后按照思路部分模拟即可。

# 代码参考

```cpp
// Problem: C - Buy Balls
// Contest: AtCoder - AtCoder Beginner Contest 396
// URL: https://atcoder.jp/contests/abc396/tasks/abc396_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,m;
int a[N],b[N];
ll ans;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=m;++i) scanf("%d",&b[i]);
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+m+1,cmp);

	int cnt = 1;       //cnt表示当前的白球
	for(int i=1;i<=n;++i){
		if(a[i] >= 0){
			ans += a[i];
			if(b[cnt] >= 0) ans += b[cnt++];
		}
		else {
			if(a[i] + b[cnt] >= 0) ans += a[i] + b[cnt++];
			else break;
		}
		//printf("%lld %d\n",ans,cnt);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：lfxxx_ (赞：1)

我们考虑将 $B$ 和 $W$ 从大到小排序，然后贪心。

首先把所有 $B_i \ge 0$ 都加到答案中。

然后将所有 $B_i+W_j \ge 0$ 的加到答案中。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int a[N],b[N];
signed main()
{
    int n,m,sum=0;
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=1;i<=m;++i)
        cin>>b[i];
    sort(a+1,a+n+1,greater<int>());
    sort(b+1,b+m+1,greater<int>());
    int i=1,j=1,ans=0;
    while(i<=n)
    {
        if(a[i]>=0)
        {
            ans+=a[i];
            ++i;   
        }
        else break;
    }
    while(j<i&&j<=m)
    {
        
        if(b[j]>=0)
        {
            ans+=b[j];
            ++j;
        }
        else break;
    }
    while(i<=n&&j<=m)
    {
        ans+=max(0LL,a[i]+b[j]);
        ++i,++j;
    }
    cout<<ans;
}
```

---

## 作者：Fuxh_18 (赞：1)

[AC 代码。](https://www.luogu.com.cn/record/207653287)

## 题意
有 $N$ 个黑球和 $M$ 个白球，选出一些球（可以不选），黑球数量不少于白球，求所有球值的最大值。
## 分析
本题可以考虑贪心。
## 解法
先将黑与白的值排序，假设选的黑球与白球数量一样，在选到第 $i$ 个时，有以下几种情况不能继续增加白球：

1. $b_i+w_i$ 的值小于等于 $0$。
2. $w_i$ 的值小于等于 $0$，因为可以只去选黑球。
3. $N < i$，黑球数量不够。
4. $M < i$，白球数量不够。

以上操作完成后，判断剩余的黑球是否大于 $0$，即选上能增加总值。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long //不开long long见祖宗 
using namespace std;
const int N=2e5+1;
int n,m,b[N],w[N],ans,mk;
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	sort(b+1,b+1+n,cmp);
	for(int i=1;i<=m;i++){
		cin>>w[i];
	}
	sort(w+1,w+1+m,cmp);
	for(int i=1;;i++){ //假设黑球与白球一样多 
		mk=i;
		if(b[i]+w[i]<=0||w[i]<=0||i>m||i>n){ //判断是否可选 
			break;
		}
		ans+=b[i]+w[i]; //增加总值 
	}
	for(int i=mk;i<=n;i++){ //加上剩余黑球中能拿的 
		if(b[i]<=0) break;
		ans+=b[i];
	}
	cout<<ans<<endl;
	return 0;
}
```

## 谢谢观看

---

## 作者：cjx_AK (赞：1)

我们考虑贪心。

由于黑色选择个数是由白色决定的，所以我们从白色入手。

先排序，确保最值。

然后让白色最值，再在遍历时更新答案，也就是说，白色的正数是最优先考虑的。

code：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2000002],b[3000003],n,m,sum[2000002],sum2[2000002],ans;
stack<int>q;
bool cmp(int a,int b){
	return a>b;
}
void solve(){
	cin>>n>>m;
	int l,r=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+m+1,cmp);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=m;i++){
		sum2[i]=sum2[i-1]+b[i];
	}
	for(int i=0;i<=n;i++){
		if(sum2[i]>sum2[i+1]&&!r){
			l=i;
			r=1;
		}
		if(!r)l=i;
		ans=max(ans,sum[i]+sum2[l]);
	}
	cout<<ans;
}
signed main(){
	int T=1;
	//cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：TheTrash (赞：1)

### 题目大意

有 $n$ 个黑球和 $m$ 个白球。每个黑球都有一个价值 $b_i$，每个白球都有一个价值 $w_i$。你需要选择至少 $0$ 个球，使选择的黑球的数量大于等于选择的白球的数量。找出最大的总价值。

### 思路

贪心题。

先把数组 $b$ 和 $w$ 从大到小排序。每次可以选择一个白球和一个黑球或只选择一个黑球。每次选择的球的总价值可能大于 $0$ 的情况有三种：

- $b_i$ 大于 $0$ 同时 $w_j$ 大于 $0$
- $b_i$ 大于 $0$ 同时 $w_j$ 小于等于 $0$
- $b_i+w_j$ 大于 $0$

当满足第一种情况就让 $ans$ 加上 $b_i$ 和 $w_j$，$i$ 加一，$j$ 加一。否则如果满足第二种情况就让 $ans$ 加上 $b_i$,$i$ 加一。否则如果满足第三种情况就让 $ans$ 加上 $b_i$ 和 $w_j$，$i$ 加一，$j$ 加一。如果三种情况都不满足或者 $i\ge n$（因为 $i$ 一定大于等于 $j$，所以只需判断 $i$）时就结束循环。

### 代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef long long ll;
ll n,m,ans;
ll b[200005],w[200005];
bool cmp(int i,int j){
	return i>j;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>b[i];
	for(int i=0;i<m;i++) cin>>w[i];
	sort(b,b+n,cmp);
	sort(w,w+m,cmp);
	int i=0,j=0;
	while(1){
		if(b[i]>0){
			if(w[j]>0) ans+=b[i++]+w[j++];
			else ans+=b[i++];
		}
		else if(b[i]+w[j]>0) ans+=b[i++]+w[j++];
		else break;
		if(i>=n) break;//越界就结束循环
	}
	cout<<ans;
}
```

---

## 作者：CCY20130127 (赞：0)

## 题目大意：
[题目传送门](https://www.luogu.com.cn/problem/AT_abc396_c)

## 题目思路：
下面均规定黑球为 $a$ 数组，白球为 $b$ 数组。

题目要求黑球数量 $≥$ 白球数量根据贪心的思想，不难想到对 $a,b$ 分别从大到小排序。
贪心要选就选大的，要选就选正的，不然就不选。

## 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, m, ans, mx, a[200005], b[200005];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) cin >> b[i];
	sort(a + 1, a + n + 1, greater<long long>());
	sort(b + 1, b + m + 1, greater<long long>());
	for (int i = 1; i <= n; i++) {
		b[i] += b[i - 1];
		a[i] += a[i - 1];
		mx = max(mx, b[i]);
		ans = max(ans, a[i] + mx);
	}
	cout << ans;
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/207666597)

---

## 作者：yyycj (赞：0)

## [题目传送门](https://atcoder.jp/contests/abc396/tasks/abc396_c)

## 题目简述
给定两个序列 $B$ 和 $W$，从这两个序列里选任意个元素，但从 $B$ 中挑选的元素数必须大于等于从 $W$ 中挑选的元素数。求选择的数的总和的最大值。

## 主要思路
采用贪心的算法，维护两个自动从大到小排列 `priority_queue`，分别记录 $B$ 和 $W$。

本题可以使用两个 `while` 循环来解决。由于从 $B$ 中挑选的元素数必须大于等于从 $W$ 中挑选的元素数，所以第一个循环里先同时从队列头获取元素。当满足以下两个条件时，就可以将答案增加两个队列头的和：

1. $W$ 队列头 $\ge 0$；如果队列头都已经 $<0$，那后面也都 $<0$，所以就都不选，把队列 $B$ 剩下 $\ge 0$ 的元素给答案加上就行了。
2. $B$ 队列头 $+ W$ 队列头 $\ge 0$；当第一个条件满足时，那么 $B$ 队列头 $\ge 0$ 的情况就不必多说了，但 $<0$ 还是有可能需要将答案增加的，就是这一个条件，仍然能使答案处于增大的状态，只不过不需要将队列 $B$ 剩下 $\ge 0$ 的元素给答案加上。如果不满足，则之后两个队列头的和只能更小，所以直接结束循环。

第二个循环第一个条件中已经提到过了，就是队列 $B$ 剩下 $\ge 0$ 的元素给答案加上。

## AC Code
```cpp
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
typedef long double db;
const int INT_INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
// ----------------------------

// ----------------------------
priority_queue<int> q1, q2;
// ----------------------------


int main() {
	int n, m, b, w; cin >> n >> m;
	for (int _ = 1; _ <= n; _++) {
		cin >> b;
		q1.push(b);
	}
	for (int _ = 1; _ <= m; _++) {
		cin >> w;
		q2.push(w);
	}
	// ----------------------------
	ll ans = 0;
	while (!q1.empty() && !q2.empty()) {
		if (q2.top() >= 0 && q1.top() + q2.top() >= 0) {
			ans += q1.top() + q2.top();
			q1.pop();
			q2.pop();
		}
		else break;
	}
	while (!q1.empty() && q1.top() > 0) {
		ans += q1.top();
		q1.pop();
	}
	// ----------------------------
	cout << ans;
	return 0;
}
```

---

## 作者：fengzhaoyu (赞：0)

## 题意
就是两组数据，分别选几个，使总和最大，但第一组选的个数不少于第二组。
## 思路
考虑贪心。

毋庸置疑，先对两个数组分别从大到小排序。我的方法是先求出两个数列正数的个数分别为 `bb` 和 `bw`。
1. 如果 `bb` 大于等于 `bw`，那么只需把两个数列的所有正数加上就好了，你会发现，如果此时你再加任意一个剩下的数都不是最大的了，因为剩下的全为负数。
2. 如果 `bb` 小于 `bw` 怎么办？毋庸置疑，两个数列前 `bb` 个数是都要选的，都为正贡献。那 `bb` 到 `bw` 间的数选不选？首先明确，此区间中第一序列全为负数，第二序列全为正数。此时第一个序列选的数只能等于第二个序列所选的数，因为如果第一序列再多选一个的话，选的数一定是负数，那就没必要了。那到底选到哪里呢？只需判断两序列相同位置上的数是否为正贡献即可。如果为负，那也不会选他，并且由于数列是递减的，后面的贡献就一定为负，就不选了。

其他的详见代码。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//十年OI一场空
int b[200005],w[200005];
bool cmp(int a,int b)
{
	return a>b;
}
signed main()
{
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>w[i];
	}
	sort(b+1,b+1+n,cmp);
	sort(w+1,w+1+m,cmp);//从大到小排序
	int bb=0,bw=0;
	for(int i=1;i<=n;i++)bb+=b[i]>0?1:0;
	for(int i=1;i<=m;i++)bw+=w[i]>0?1:0;
	if(bb>=bw)
	{
		for(int i=1;i<=bb;i++) ans+=b[i];
		for(int i=1;i<=bw;i++) ans+=w[i];
		cout<<ans<<endl;
	}
	else
	{
		for(int i=1;i<=bb;i++) ans+=b[i];
		for(int i=1;i<=bb;i++) ans+=w[i];
		int s=0;
		for(int i=bb+1;i<=min(n,bw);i++)//可能第一序列的个数没有bw多
		{
			if(b[i]+w[i]>=0)
			{
				s+=b[i]+w[i];
			}
		}
		cout<<ans+s<<endl;
	}
	return 0;
}
```

---

## 作者：shiziyu111 (赞：0)

# AT_abc396_c Buy Balls 题解
## 题目大意
你有 $N$ 个黑色的球和 $M$ 个白色的球，第 $i$ 个球的值为 $B_i$，第 $j$ 个球的值为 $W_j$（球的值可能为负数）。

现在让你取出一些球，使取出白球的数量不大于黑球的数量，问取出的最大值是多少？
## 思路
我们将这些球先排个序，然后再进行取球。

首先，我们要尽量取出非负数的黑球，以最大化利益，并且为白球腾出足够的空间。

其次，我们要在取出黑球的同时取出白球，这样就能保证白球小于黑球个数的同时，尽量的取出白球。

在取完了黑球之后，我们要进行分类讨论：

1. 白球只有非正数了，那么此时得出的答案即为最终答案（没法变得更大）
1. 白球还存在正数，那么我们不断将最大的黑球和最大的白球同时取出，看一下能否带来正贡献，能的话计入答案，最后不能再带来正贡献的时候输出答案。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
signed main()
{
	int n,m,black[N],white[N];
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>black[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>white[i];
	}
	sort(black+1,black+1+n);
	sort(white+1,white+1+m);
	int ans=0,q=n,p=m;
	while(black[q]>=0&&q>0)
	{
		ans+=black[q];
		q--;
		if(white[p]>0)
		{
			ans+=white[p];
			p--;
		}
	}
	if(white[p]<=0)
	{
		cout<<ans;
	}
	else
	{
		while(black[q]+white[p]>0&&q>0&&p>0)
		{
			ans+=black[q]+white[p];
			q--;
			p--;
		}
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：hjyowl (赞：0)

### 思路

首先，一个很显然的结论，$a_i$ 中大于等于 $0$ 的数一定要选。

然后，对于 $a_i$ 中的负数，我们要根据选择他后，$a_i+b_i$ 是否大于等于 $0$。

所以思路很明显了，可以直接排序后用双指针做。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 2000010;
long long n,m;
long long a[N],b[N];
bool debug = 0;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for (long long i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
	for (long long i = 1; i <= m; i ++ ){
		cin >> b[i];
	}
	sort(a + 1,a + 1 + n);
	reverse(a + 1,a + 1 + n);
	sort(b + 1,b + 1 + m);
	reverse(b + 1,b + 1 + m);
	long long res = 0,s = 0;
	int j = 1;
	for (long long i = 1; i <= n; i ++ ){
		if (a[i] >= 0){
			s += a[i];
			if (j <= m && b[j] >= 0){
				s += b[j];
				j ++ ;
			}
		}
		else{
			if (j <= m && b[j] + a[i] >= 0){
				s += a[i];
				s += b[j];
				j ++ ;
			}
		}
	}
	cout <<s;
	return 0;
}
```

---

## 作者：zby0501_ (赞：0)

## 思路：
这题感觉比 D 题难，因为 D 会更模板一点。

这题要使用贪心做法。首先要读入两个数组 $a$ 和 $b$，然后升序排列两个数组。接下来，如果 $a_n +  b_n > 0$ 且 $b_n > 0$，那么把答案加上 $a_n + b_n$，并把 $n$ 和 $m$ 都减 $1$。最后把 $a$ 中还未统计过的数加入答案就行了。
## 代码：
```
#import<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],b[200005],ans;
main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=m;++i) cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	while(n && a[n]+b[m]>0 && b[m]>0) ans+=a[n]+b[m],--n,--m;
	while(n && a[n]>0) ans+=a[n],--n;
	cout<<ans;
}
```

---

## 作者：ybclch2026 (赞：0)

### 题目大意
有 $N$ 个黑球和 $M$ 个白球，每个球都有一个值，选择几个球且黑球数量至少等于选择的白球数量，求球的值的最大可能总和。

### 思路
将黑球和白球分别按值降序排列，并计算前缀和数组 $bb$ 和 $ww$。

再用$cur_k$表示选择至少 $k$ 个黑球时的最大可能总和。这样，对于每个可能的白球数量，可以快速获取对应的最大黑球总和。

最后遍历所有可能的白球数量的贡献加上对应的黑球的贡献，取最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,m;
long long b[maxn],w[maxn],bb[maxn],ww[maxn],cur[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=m;i++)cin>>w[i];
    sort(b+1,b+n+1,greater<long long>());
    sort(w+1,w+m+1,greater<long long>());
    for(int i=1;i<=n;i++)bb[i]=bb[i-1]+b[i];
    cur[n]=bb[n];
    for(int i=n-1;i>=0;i--)cur[i]=max(bb[i],cur[i+1]);
    for(int i=1;i<=m;i++)ww[i]=ww[i-1]+w[i];
    int kk=min(m,n);
    long long ans=-1e18;
    for(int k=0;k<=kk;k++)
        ans=max(ans,ww[k]+cur[k]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：__assassin_ (赞：0)

# 题目大意：

有 $n$ 个黑球和 $m$ 个白球，第 $i$ 个黑球的值为 $b_i$，第 $j$ 个白球的值为 $w_j$。从中选择若干个球，问你在黑球数大于或等于白球数的情况下，所有球上的值之和的最大值。

# 思路：

首先，题目要求的是最大值，所以我们先将 $b$ 数组和 $w$ 数组从大到小排个序，然后先用 $bi$ 表示当前准备选的黑球编号，用 $wi$ 表示当前准备选的白球编号，用 $ans$ 表示最终答案。因为黑球的数量要大于或等于白球的数量，所以先将所有值大于或等于 $0$ 的黑球选上，然后将 $ans$ 加上这些黑球的值。

然后我们再来考虑白球，当 $wi>m$ 时，说明所有的白球都取完了，那么退出。否则，如果 $w_{wi}>0$，并且 $bi>wi$ 时，说明当前这个白球可以取，并且是当前最优选择，所以选上当前的白球，$ans\gets ans+w_{wi}$，$wi\gets wi+1$。否则，如果 $w_{wi}<0$，说明之后的黑球的值和白球的值都小于 $0$，只要取了就会亏，所以退出。否则，当前的 $bi$ 是等于 $wi$ 的，所以想选白球就必须先选一个黑球，如果 $bi\le n$，并且 $b_{bi}+w_{wi}\ge0$，说明当前还有黑球可以取，且选一个黑球和一个白球是不亏的，那么就取，$ans\gets ans+b_{bi}+w_{wi}$，$bi\gets bi+1$，$wi\gets wi+1$。否则 $bi>n$ 或者 $b_{bi}+w_{wi}<0$，要么黑球取完了，要么取了会亏，那么退出。最后输出最终答案 $ans$ 即可。

# AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int b[200010],w[200010];
int ans;//最终答案 
int bi=1,wi=1;//bi表示当前准备选的黑球，wi表示当前准备选的白球， 
bool cmp(int x,int y){return x>y;}//从大到小排序 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=m;i++) cin>>w[i];
	sort(b+1,b+n+1,cmp);//排序 
	sort(w+1,w+m+1,cmp);//排序 
	while(true){
		if(b[bi]>=0&&bi<=n) ans+=b[bi++];//如果当前的黑球的值大于或等于0，选上 
		else break;//否则退出 
	}
	while(true){
		if(wi>m) break;//所有白球都取完了，退出 
		else{
			if(w[wi]>=0&&bi>wi){//当前的白球可以选且选了不亏 
				ans+=w[wi++];//选上当前的白球 
			}
			else{
				if(w[wi]<0) break;//当前的黑球和白球的值都小于0，之后只要选了就会亏，所以退出 
				else{//否则bi等于wi 
					if(bi<=n&&b[bi]+w[wi]>=0){//当前的黑球可以选，且选一个黑球和一个白球不亏 
						ans+=b[bi++]+w[wi++];//选上一个黑球和一个白球 
					}
					else break;//否则退出 
				}
			}
		}
	}
	cout<<ans;//输出最终答案 
	return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## 题意

给出 $n$ 个黑球和 $m$ 个白球，每个球都有一个权值（可以为负），要求选出一些球或不选球，使得黑球数量不少于白球，且权值最大。

## 思路

很容易想到将白球与黑球从大到小按照权值排序。因为黑球数量不能少于白球数量，所以每次需要选择一个白球与一个黑球或只选择一个黑球。

因为白球和黑球的权值是从大到小排序的，所以若当前白球权值小于 $0$ 时，之后的白球权值都将小于 $0$，并且只选择黑球一定比选择黑球和白球更优。

所以当白球权值小于 $0$ 时，每次只需选择一个黑球，取该过程的最大权值即可得到答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,b[200005],w[200005],ans;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=1;i<=m;i++)
		cin>>w[i];
	sort(b+1,b+1+n);
	sort(w+1,w+1+m);
	for(int nw=0,j=n,i=m;j>=1;i--,j--){
		if(i>=1&&w[i]>=0)
			nw+=b[j]+w[i];
		else
			nw+=b[j];
		ans=max(ans,nw);
	}
	cout<<ans;
	return 0; 
}
```

---

## 作者：FXLIR (赞：0)

### 思路
贪心题。

观察到取黑球的数量没有限制，于是想到取尽可能多的黑球。

因为白球的数量需要 $\leq$ 黑球的数量，所以考虑在可能的情况下取尽可能多的白球。具体地，尽可能多地取**值为正数**的白球。

然而，这个策略存在漏洞。考虑一种情况，在按照上面的策略取完球之后，剩余黑球的数值分别为 $-1,-5,-9$，而剩余白球的数值分别为 $9,6,1$。此时，取两个值相对较大的黑球，再取两个值相对较大的白球，可以使答案更大。

所以，我们可以在按照上面策略取完后，将剩余的球两两配对——剩余值最大的黑球与值最大的白球配对，第二大的黑球与第二大的白球配对，以此类推。然后，对于每一对，若该对两个值的和 $\ge 0$，则取这一对的两个球。 
### 代码
```
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=2e5+5,INF=1e9;
int n,m,b[N],w[N],ans;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		ans+=(b[i]>=0)*b[i],b[i]=min(b[i],0ll);
	}
	for(int i=1;i<=m;i++){
		cin>>w[i];
	}
	sort(b+1,b+n+1);
	sort(w+1,w+m+1);
    //这里用了一种似乎不太一样的处理方法。
	for(int i=n,j=m;i>0&&j>0&&b[i]+w[j]>0;i--,j--){
		ans+=b[i]+w[j];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：LionBlaze (赞：0)

RMJ/fn/fn。

> 题目大意：有两个序列 $B_{1 \cdots N}$ 和 $W_{1 \cdots M}$，你可以在 $B$ 和 $W$ 中分别选一些数字，使得在 $B$ 中选择的数字数量不小于在 $W$ 中选择的，求所选数字之和的最大值。

一个很简单的 trick。双指针。

首先显然，若在某个序列中选择了 $k$ 个数，则结果一定不比选最大的 $k$ 个优。这样，我们就可以将两个序列分别从大到小排序。

我们发现，排序后两个数组的前缀和是一个单峰函数——因为前几个数字都是正的，此时前缀和上升。后面的数字都是负的，前缀和下降。

这样，我们就可以枚举在 $W$ 中选择几个元素，设选择了 $k$ 个，则在 $B$ 中选择个元素个数必须在 $k$ 和 $M$ 之间（包含）。那么，在 $k$ 和 $M$ 之间，$B$ 的前缀和的最大值是多少？

显然：

- 如果第 $k$ 个是负的：那么让选择个数增加只会让和变小，应当选择最小值 $k$ 个。
- 否则一直往后延伸，直到遇到第一个负值。

直接统计时间复杂度是 $\mathcal O(NM)$ 的（全为正即可达到），有没有更好的方法？

有的兄弟，有的。

第一种方法：注意到第二种情况的下标恒定，可以 $\mathcal O(M)$ 预处理，总时间复杂度 $\mathcal O(N+M)$。

第二种方法：使用二分查找查找第一个小于 $0$ 的数字。时间复杂度 $\mathcal O(M+N \log M)$。

第三种方法：注意到下标永远不减（无论是第一种情况还是第二种情况还是混合），可以使用一个额外变量维护“目前的”，双指针，时间复杂度 $\mathcal O(N+M)$。

---

## 作者：Statax (赞：0)

## 前言

蒟蒻第一次不看题解切掉 ABCDEF，写几篇题解庆祝。

## 思路

C 比 D 难。

因为黑球个数要大于等于白球个数，那我们肯定先要把黑球非负数的都选上，这个个数记作 $c$。

接着将白球从大到小排序，枚举白球个数 $r$，如果 $r \le c$ 就直接加，否则就还要每次从黑球剩下的当中选最大的。当然，剩下的自然都是负数。

答案取最大值即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define db double
#define pb push_back
#define ll long long
#define i128 __int128
#define ull unsigned ll
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

const int MAXN = 1e6 + 5;
const int inf = 2147483627;
const int mod = 19491001;
const db eps = 1e-9;

template <typename T> inline void read (T &x) {
	x = 0; T f = 1; char ch = getchar ();
	while (!isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar ();
	x *= f;
}

template <typename T, typename... Arp> inline void read (T &x, Arp &...arp) {
	read(x), read(arp...);
}

int n, m;
ll B[MAXN], W[MAXN];

signed main () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
    read (n, m);
    for (int i = 1; i <= n; ++i) read (B[i]);
    for (int i = 1; i <= m; ++i) read (W[i]);
    sort (B + 1, B + n + 1, greater <int> ());
    sort (W + 1, W + m + 1, greater <int> ());
    
    ll sumB = 0, lenB = 0;
    for (int i = 1; i <= n; ++i) 
        if (B[i] > 0) sumB += B[i], ++lenB;
    for (int i = 1; i <= n; ++i) B[i] += B[i - 1];
    for (int i = 1; i <= m; ++i) W[i] += W[i - 1];
    
    ll ans = 0;
    for (int i = 0; i <= min (n, m); ++i) {
        if (i <= lenB) 
            ans = max (ans, sumB + W[i]);
        else 
            ans = max (ans, W[i] + B[i]);
    }
    
    printf ("%lld\n", ans);
	return 0;
}
```

---

