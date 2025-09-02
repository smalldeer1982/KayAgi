# Jeff and Furik

## 题目描述

Jeff has become friends with Furik. Now these two are going to play one quite amusing game.

At the beginning of the game Jeff takes a piece of paper and writes down a permutation consisting of $ n $ numbers: $ p_{1} $ , $ p_{2} $ , $ ... $ , $ p_{n} $ . Then the guys take turns to make moves, Jeff moves first. During his move, Jeff chooses two adjacent permutation elements and then the boy swaps them. During his move, Furic tosses a coin and if the coin shows "heads" he chooses a random pair of adjacent elements with indexes $ i $ and $ i+1 $ , for which an inequality $ p_{i}&gt;p_{i+1} $ holds, and swaps them. But if the coin shows "tails", Furik chooses a random pair of adjacent elements with indexes $ i $ and $ i+1 $ , for which the inequality $ p_{i}&lt;p_{i+1} $ holds, and swaps them. If the coin shows "heads" or "tails" and Furik has multiple ways of adjacent pairs to take, then he uniformly takes one of the pairs. If Furik doesn't have any pair to take, he tosses a coin one more time. The game ends when the permutation is sorted in the increasing order.

Jeff wants the game to finish as quickly as possible (that is, he wants both players to make as few moves as possible). Help Jeff find the minimum mathematical expectation of the number of moves in the game if he moves optimally well.

You can consider that the coin shows the heads (or tails) with the probability of $ 50 $ percent.

## 说明/提示

In the first test the sequence is already sorted, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
0.000000
```

## 样例 #2

### 输入

```
5
3 5 2 4 1
```

### 输出

```
13.000000
```

# 题解

## 作者：Siyuan (赞：13)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io)

---

> 题目链接：[Codeforces 351B](https://codeforces.com/contest/351/problem/B)

给出一个长度为 $n$ 的排列 $p_i$，Jeff 和 Furik 会分别轮流进行操作，Jeff 先手。每次操作时，Jeff 会选择相邻的两个数 $p_i,p_{i+1}$ 交换位置；Furik 会抛一枚硬币，如果硬币正面朝上，那么他会随机选择一对 $i$ 和 $i+1$ 且满足 $p_i>p_{i+1}$ 并交换他们；否则他会随机选择一对 $i$ 和 $i+1$ 且满足 $p_i<p_{i+1}$ 并交换他们。当这个序列递增时，游戏结束。假设 Jeff 希望尽快结束游戏（即他希望两人剩余的操作次数最少），求出一共需要的操作次数的期望。

数据范围：$1\leqslant n\leqslant 3000$

------

## Solution

我们对 Jeff 和 Furik 的操作分开考虑：

- Jeff：每次操作减少 $1$ 个逆序对。
- Furik：每次操作有 $\frac{1}{2}$ 的概率增加 $1$ 个逆序对，有 $\frac{1}{2}$ 的概率减少 $1$ 个逆序对。

根据期望的可加性，我们可以知道每两次操作，有 $\frac{1}{2}$ 的概率增加 $2$ 的逆序对，有 $\frac{1}{2}$ 的概率逆序对数量不变。因此，每两次操作期望减少 $1$ 个逆序对，答案就是 $2\times\texttt{逆序对个数}$。

但是如果根据以上思路，我们会发现样例都过不了。其实这里有一些细节问题：需要对**逆序对的奇偶性**分类讨论！

- 有奇数个逆序对：那么最后 Jeff 进行操作后序列已经递增。操作次数为 $2\times\texttt{逆序对个数}-1$。
- 有偶数个逆序对：没有边界的问题，答案就是 $2\times\texttt{逆序对个数}$。

**时间复杂度**：$O(n\log n)$

------

## Code

```cpp
#include <cstdio>

const int N=3005;
int n,a[N],bit[N],cnt;

void add(int x,int val) {
    for(;x<=n;x+=x&-x) bit[x]+=val;
}
int query(int x) {
    int res=0;
    for(;x;x-=x&-x) res+=bit[x];
    return res;
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=n;i>=1;--i) {
        cnt+=query(a[i]-1);
        add(a[i],1);
    }
    printf("%d.000000\n",(cnt<<1)-(cnt&1));
    return 0;
}
```



---

## 作者：blue_tsg (赞：3)

乍一看好像很难，转化完了后简单的离谱，代码就5行。

貌似方法和别的题解不一样。

两人操作的过程实际上就是对原序列进行减少或增加逆序对的个数，Jeff每次操作会减少一个逆序对，Furik每次操作有 $\frac{1}{2}$ 的概率减少一个逆序对，有 $\frac{1}{2}$ 的概率增加一个逆序对。

定义 $dp[i]$ 表示当前还剩 $i$ 个逆序对，距离游戏结束的期望步数为多少，如果此时是先手操作，有转移：
$$
dp[i]=dp[i-1]+1
$$

表示Jeff花了一步减去一个逆序对。

当是后手操作时，有转移：
$$

dp[i]=\frac{1}{2}(dp[i-1]+1)+\frac{1}{2}(dp[i]+2)

$$

相当于花一步增加一个，对方又花一步减回来了。

把上面的式子转一下就变成：
$$
dp[i]=dp[i-1]+3
$$

考虑先后手问题，注意到后手的移动并不会改变二者先后手与逆序对奇偶性的相对关系，二者奇偶性相同时是先手，反之是后手。

短的离谱的代码：
```cpp
#include <bits/stdc++.h>
int dp[3010*3010],a[3010],n,cnt;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(a[i]>a[j]) cnt++;
    for(int i=1;i<=cnt;i++) dp[i]=dp[i-1]+((i%2==cnt%2)?1:3);
    printf("%.6lf\n",(double)dp[cnt]);
    return 0;
}
```


---

## 作者：sSkYy (赞：2)

# [CF351B Jeff and Furik](https://www.luogu.com.cn/problem/CF351B)

> 简单期望

## 题意

题目有点绕，实际上就是第一个人会使逆序对数量 $-1$，第二个人会等概率的使逆序对数量 $-1$ 或 $+1$，求逆序对数量变为 $0$ 的期望次数。

## 题解

设 $f_i$ 为初始逆序对数量是 $i$ 时的期望次数。

显然 $f_i=\frac1 2 f_i +\frac1 2 f_{i-2}$，分别对应第二个人 $+1$ 和 $-1$ 的情况，化简一下就是$f_i=f_{i-2}+4,f_0=0,f_1=1$。

记初始逆序对数量为 $cnt$。

- 当 $cnt$ 是偶数时：$ans=2\times cnt$。

- 当 $cnt$ 是奇数时，最后一次第一个人直接使逆序对数量减一，轮不到第二个人操作，等价于偶数 $cnt-1$ 的情况再额外加一次操作：$ans=f_{cnt-1}+1=2\times cnt-1$。

## 代码

```cpp
#include <iostream>
#define rep(i,a,b) for(int i=a;i<=b;i++)
int main(){
    int n; std::cin>>n; 
    int a[3001]; rep(i,1,n) std::cin>>a[i]; 
    int cnt=0; rep(i,1,n)rep(j,i+1,n) cnt+=a[i]>a[j];
    std::cout<<(cnt<<1)-(cnt&1);
}
```

---

## 作者：smyslenny (赞：1)

## CF351B


**Description**

> 两个人 A，B，一个长为 $n$ 的序列，A 每次选两个相邻元素交换，B 有相等的概率把任意满足 $p_i<p_{i+1}$ 的 $p_i$ 和 $p_{i+1}$ 或 $p_{i}>p_{i+1}$ 的 $p_{i}$ 和 $p_{i+1}$ 交换。
>
> 求将序列变成升序的最小值期望步数。


**Solution**

每一次 A 肯定是交换一个逆序对，而 B 每次有 $50\%$ 的概率减少一个逆序对，有 $50\%$ 增加一个逆序对，设 $f_i$ 表示 $i$ 个逆序对时的最小期望步数，则转移为 $f_i=\frac{1}{2}(f_{(i-1)-1}+2)+\frac{1}{2}(f_{(i-1)+1}+2)$

化简一下：

$f_i=f_{i-2}+4$ 

易知 $f_0=0,f_1=1$ 。

然后我们发现当 $ f_i$ 是偶数的时候，$f_i=f_{\frac{i}{2}}+4=(f_{\frac{i}{4}}+4)+4=\dots=f_0+4\times\frac{i}{2}=2i$

当 $f_i$ 是奇数的时候，$f_i=f_{\frac{i}{2}}+4=(f_{\frac{i}{4}}+4)+4=\dots=f_1+4\times(\lfloor\frac{i}{2}\rfloor-1)=2i-1$

然后求一次逆序对个数，根据奇偶性判断就行了。

**Code**

```c++
/*
* @Author: smyslenny
* @Date:    2021.09.04
* @Title:   CF351B Jeff and Furik
* @Main idea:求逆序对个数，判断奇偶性，Ans=2*odd-1 || 2*even 
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>

#define ll long long
#define INF 0x3f3f3f3f
#define orz cout<<"LKP AK IOI\n"
#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)>(b)?(a):(b)
#define lowbit(x) (x)&(-x)

using namespace std;
const int mod=998244353;
const int M=3e3+5;
int n,Ans;
int read()
{
	int x=0,y=1;
	char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') y=0;c=getchar();}
	while(c>='0' && c<='9') { x=x*10+(c^48);c=getchar();}
	return y?x:-x;
}

struct node{
	int val,id;
}sz[M];

bool cmp(const node &a,const node &b)
{
	return a.val<b.val;
}

int sum[M];
void add(int x,int k)
{
	for(int i=x;i<=n;i+=lowbit(i))
		sum[i]+=k;
}

int query(int x)
{
	int cnt=0;
	for(int i=x;i;i-=lowbit(i))
		cnt+=sum[i];
	return cnt;
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		sz[i].val=read(),sz[i].id=i;
	sort(sz+1,sz+1+n,cmp);
	for(int i=1;i<=n;i++)
		add(sz[i].id,1),Ans+=(i-query(sz[i].id));
	if(Ans&1)
		printf("%lf\n",(double)2*Ans-1);
	else 
		printf("%lf\n",(double)2*Ans); 
	return 0;
}
```



---

## 作者：Stream月 (赞：1)

$Siyuan$的题解好强啊，~~我不大懂~~ orz

显然Jeff的做法选择一个逆序对交换，才会使操作次数最少

先看一个**错误思路**：

这道题我刚开始的想法时，$f[i][0/1]$ 表示到达剩余$i$对逆序对的局面当前轮到Jeff/Furik操作的期望步数，因为Fruik的操作是随机的所以，$f[i]$可以转移到，$f[i +1], f[i - 1]$， Jeff又可以将$f[i + 1]$转移到$f[i]$, 显然这样的转移是存在环的（即有后效性）

正解：

考虑将Jeff和Fruik当成一整轮一起操作，那么一轮操作中又$0.5$的概率减少两个逆序对，$0.5$的概率使逆序对个数不变。

状态表示： $f[i]$ 表示剩余$i$对逆序对的期望步数

初始条件：设求出的逆序对的个数为$num$， $f[num] = 0$

状态转移 : $f[i] = 0.5 * (f[i] + 2) + 0.5*(f[i + 2] + 2)$

到这里，我们会发现$f[i]$的转移还是有自环的，怎么办呢？

**解方程！**~~我是第一次接触这种操作啊~~
$$
f[i] = \frac{f[i] + f[i + 2]}{2} + 2
$$

$$
2*f[i] = f[i] + f[i +2] +4
$$
即
$$
f[i] = f[i + 2] + 4
$$

但是，当你有奇数个逆序对的时候，游戏不能在整轮操作中完成，还需要再由Jeff操作1次，答案要 +1

因为求逆序对，时间复杂度： $O(nlogn)$

喜闻乐见的代码实现：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;

using namespace std;
#define $(i,a,n) for(int i = a; i <= n; ++i)

inline ll read() {
	   ll ans = 0;
	   char last = ' ',ch = getchar();
	   while(ch < '0' || ch > '9') last = ch, ch = getchar();
	   while(ch >= '0' && ch <= '9') ans = (ans << 3) + (ans << 1) + ch - '0', ch = getchar();
	   if(last == '-') ans = -ans;
	   return ans;
}

const int INF = 0x3f3f3f3f;

const int N = 3005;
int n, num = 0;
int f[N * N];
struct BIT{
	int c[N];
	void update(int x, int v) {
		for(int i = x; i <= n; i += i & (-i)) {
			c[i] += v;
		}
	}
	int qry(int x) {
		int ret = 0;
		for(int i = x; i > 0; i -= i & (-i)) {
			ret += c[i];
		}
		return ret;
	}
}b; 

int main(){
	//freopen("testdata.in", "r", stdin);
	//freopen("ans.out", "w", stdout);
	n = read();
	int x;
	$(i, 1, n) {
		x = read();
		b.update(x, 1);
		num += b.qry(n) - b.qry(x);
	}
	if(num == 0) {
		printf("%.6lf\n", 0.0);
		return 0;
	}
	if(num & 1) {
		num--;
		f[num] = 1;
	}
	for(int i = num - 2; i >= 0; i -= 2) {
		f[i] = f[i + 2] + 4;
	}
	printf("%.6lf\n", 1.0 * f[0]);
	return 0;
}


```

话说这题,$O(n^2)$也能过，柿子也可以$O(1)$算出来，但我比较懒，读者自己写写吧qwq

最后祝大家CSP 2019 rp++

---

## 作者：lilong (赞：0)

显然，先手每次一定能减少 $1$ 对逆序对，后手有 $\frac{1}{2}$ 概率减少 $1$，$\frac{1}{2}$ 概率增加 $1$。设 $f_n$ 表示有 $n$ 对逆序对的期望操作次数，则有 $f_n=2+\dfrac{f_{n-2}}{2}+\dfrac{f_n}{2}$，即 $f_n=f_{n-2}+4$。又有 $f_0=0,f_1=1$，故：

- $2 \nmid n$ 时，$ans=2\times n-1$。
- $2 \mid n$ 时，$ans=2\times n$。

直接统计原序列逆序对数量即可。


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,a[10010],ans;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(a[i]>a[j])
                ans++;
    // cout<<ans<<endl;
    if(ans%2==0)cout<<ans*2;
    else cout<<ans*2-1;
    return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

首先这个“保留 $6$ 位小数”就是诈骗。容易证明答案一定是整数。（在下面）

然后考虑计算一次操作对答案的影响。可以发现游戏结束当且仅当逆序对的数量为 $0$。

考虑计算出当前的逆序对数量为 $\text{inv}$，然后计算 Jeff 一次操作一定减少 $1$ 个逆序对，Furik 会在操作 $1$ 和操作 $2$ 中等概率选择一个操作执行。也就是说，连续的两次操作，有 $\frac{1}{2}$ 的概率让逆序对的数目减去 $2$，$\frac{1}{2}$ 的概率让逆序对的数量不变。

然后对 $\text{inv}$ 对 $2$ 取余后的值分类讨论。设 $p\equiv\text{inv}(\bmod\ 2)$，则有：

+ $p=0$。答案为 $2\times\text{inv}$。
+ $p=1$。答案为 $2\times(\text{inv}-1)$。

因为 $n\le 3000$ 所以直接暴力 $O(n^2)$ 求逆序对即可，无需 cdq 分治或者权值 BIT。代码很好写不放了。

---

## 作者：ZJle (赞：0)

## CF351B Jeff and Furik

### 前置芝士  期望
离散型随机变量 $X$ 的取值为 $X_1,X_2,X_3,....X_n$ ，为 $X$ 对应取值的概率为 $P(X_1),P(X_2),P(X_3),...,P(X_n)$ ， $\mathbb{E}(X)=\sum_{i=1}^n P(X_i)\times X_i$ 。

### 解题
#### 题意

* Jeff 每次可以交换一对相邻的 $p_i, p_{i + 1}$。

* Furik 有 $50\%$ 的概率选择一对相邻的 $p_i, p_{i + 1}$ 并且满足 $p_i \ge p_{i + 1}$，然后将其交换。
    

当且仅当 $p_i$ 单调升时游戏结束。他希望两人执行的操作数尽量少 ，请求出两人执行的操作数的期望值。

#### 解题
这是一道概率 DP 题，Jeff 操作一次，对于总体来说是减少一对逆序对，然后 Furik 是有 $50\%$ 的减少一对逆序对，有 $50\%$ 的可能增加一对逆序对。

我们设 $i$ 是当前场上剩余的逆序对个数，设 $dp[i]$ 是解决 $i$ 个逆序对的期望步数。

我们由此可以得出动态规划方程方程，根据期望的定义，$dp[i]=dp[i-2]+0.5\times dp[i]+2$，然后我们进行移项，可以得到 $dp[i]=2\times dp[i-2]+4$，$dp[0]=0,dp[1]=1$。可知长度为 $n$ 的序列，最多有 $\frac{n(n+1)}{2}$ 个逆序对,我们对 $dp[2]$ 到 $dp[\frac{n(n+1)}{2}]$ 进行预处理，用 $O(n^2)$ 对与逆序对个数进行统计为 $cnt$，最后输出 $dp[cnt]$ 即可。

码
``` c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
void file(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
}
int n;
const int N=4501510;
int dp[N];
int a[N];
signed main(){
    dp[0]=0;
    dp[1]=1;
    cin>>n;
    for(int i=2;i<=n*(n-1)/2;i++){
        dp[i]=dp[i-2]+4;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(a[i]>a[j]){
                cnt++;
            }
        }
    }
    printf("%d.000000",dp[cnt]);
}
```

---

## 作者：Yizhixiaoyun (赞：0)

感觉官方题解非常简洁优美。

首先 $\text{Jeff}$ 为了让游戏尽快结束，他的操作一定会让逆序对数量减少 $1$，而 $\text{Furik}$ 的操作则有 $50\%$ 的概率让逆序对数量增加 $1$，$50\%$ 的概率让逆序对数量减少 $1$。

令 $ans_i$ 为剩余 $i$ 个逆序对时的期望步数，则有：

$$ans_i=1+1+ans_{i-1-1} \times 0.5+ans_{i-1+1} \times 0.5$$

简化得：

$$ans_i=ans_{i-2}+4$$

然后扫一遍就行了。

---

