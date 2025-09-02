# [ARC153C] ± Increasing Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc153/tasks/arc153_c

$ 1 $ と $ -1 $ のみからなる長さ $ N $ の数列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ が与えられます．

以下の条件をすべて満たす整数列 $ x\ =\ (x_1,\ \ldots,\ x_N) $ が存在するか否かを判定し， 存在する場合にはそのような整数列をひとつ答えてください．

- 任意の $ i $ ($ 1\leq\ i\leq\ N $) に対して $ |x_i|\ \leq\ 10^{12} $．
- $ x $ は狭義単調増加である．つまり $ x_1\ <\ \cdots\ <\ x_N $．
- $ \sum_{i=1}^N\ A_ix_i\ =\ 0 $．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ A_i\ \in\ \lbrace\ 1,\ -1\rbrace $
 
### Sample Explanation 1

この出力について $ \sum_{i=1}^NA_ix_i=\ -(-3)\ +\ (-1)\ -\ 4\ -\ 5\ +\ 7\ =\ 0 $ となります．

## 样例 #1

### 输入

```
5
-1 1 -1 -1 1```

### 输出

```
Yes
-3 -1 4 5 7```

## 样例 #2

### 输入

```
1
-1```

### 输出

```
Yes
0```

## 样例 #3

### 输入

```
2
1 -1```

### 输出

```
No```

# 题解

## 作者：adpitacor (赞：16)

由于个人偏好原因，以下将用 $a$ 表示原题的 $A$，$b$ 表示原题的 $x$，$A$ 和 $x$ 失去其原本的含义。

## 题目大意

- 给定 $n$ 和一个长度为 $n$ 的序列 $a$，满足 $a_i \in \{-1,+1\}$。

- 你要尝试求出一个长度为 $n$ 的序列 $b$，满足以下限制：

    - $|b_i| \leq 2 \times 10^{12}$；
    
    - 序列严格递增，即 $\forall 1 \leq i < n$，$b_i < b_{i+1}$；
    
    - 将 $a$ 中的正负号带入 $b$ 中后，$b$ 的和为 $0$，即 $\sum\limits_{i=1}^n{a_ib_i} = 0$。

- 如果存在这样的序列，输出 `Yes` 和一个满足条件的序列 $b$；如果不存在，则输出 `No`。

- $n \leq 2 \times 10^5$。

## 题解

记 $s = \sum\limits_{i=1}^n{a_ib_i}$。

发现样例 1 的输出没有规律，由于题目要求 $b$ 递增，考虑先填入 $1 \dots n$，如果此时 $s \neq 0$，想办法修改 $b$，把和调整到 $0$。

由于填入的数两两相邻，无法直接修改 $b_{2 \dots n-1}$，考虑调整 $b_1$（将其减小）或 $b_n$（将其增大）。

于是可以得出结论：如果 $a_1 = a_n$，则必然有解。以 $a_1 = a_n = 1$ 为例，调整方法如下：如果 $s > 0$，令 $b_1$ 减去 $|s|$；如果 $s < 0$，令 $b_n$ 加上 $|s|$。$a_1 = a_n = -1$ 的情况只需把判断条件交换即可。

> 等等，会不会只改一个数超出数值大小限制了？是否会有把调整分摊到两个数的需要？

一方面，即使在 $a_i$ 全部相等的情况下，填完 $1 \dots n$ 之后仍有 $|s| < (2 \cdot 10^5)^2 = 4 \cdot 10^{10} < 2 \cdot 10^{12}$。

另一方面，这也引出了另一个突破口：在调整了 $b_1$ 之后，是可以接着调整 $b_2$ 的；依此类推可知，事实上，可以同时调整一个**前缀**或者**后缀**（也就是对 $b$ 进行前缀减或者后缀加）。

以前缀为例，对于 $1 \leq x \leq n$，如果将 $b_{1 \dots x}$ 全部减去 $d_b$，则这次调整会使 $s$ 减去 $\sum\limits_{i=1}^x{(a_i \cdot d_b)} = (\sum\limits_{i=1}^x{a_i})d_b$（记为 $d_a \cdot d_b$）。后缀类似，只不过 $\lbrack 1,x \rbrack$ 变为 $\lbrack x,n \rbrack$，减去变为加上。

在这里，$d_b$ 一定是正数（一如前面的 $|s|$ 用了绝对值），但是 $d_a$ 的正负性与我们取的前后缀有关。如果存在 $d_a$ 为**正**的**前缀**或者 $d_a$ 为**负**的**后缀**，那么我们可以通过调整这个区间使 $s$ **减小**；能使 $s$ 增大的情况与之相对。

那怎么控制改变的数值大小呢？以 $d_a$ 为正的前缀为例，可以发现，只要存在 $d_a = 1$ 的前缀，就可以通过令 $d_b = |s|$ 进行调整来消去**任意**正 $s$。那会不会只存在 $d_a > 1$，却不存在 $d_a = 1$ 的前缀呢？不会，因为一定可以从 $d_a > 1$ 的前缀中拆出 $d_a = 1$ 的前缀。所以，只需要找 $|d_a| = 1$ 的前、后缀用于调整即可。

（如果还不清楚做法可以结合后面的代码理解）

说了这么多，让我们来手模一组数据吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/n8jl6bk3.png)

一开始填入 $1 \dots n$ 后，$s = -1+2+3+4 = 8$；在此例中，有两种调整策略：既可以将 $d_a = 1$ 的前缀 $\lbrack 1,3 \rbrack$ 整体减 $8$，也可以将 $d_a = 2$ 的前缀 $\lbrack 1,4 \rbrack$ 整体减 $4$。需要强调的是，并不是说 $|d_a| > 1$ 不行，只是 $|d_a| = 1$ 适用范围更广（比如此处使用 $d_a = 2$ 的前缀调整要求 $|s|$ 被 $2$ 整除）。

显然，如果通过调整同时能使 $s$ 减小或增大，就一定可以按如上方法得到一组答案。这是**充分性**。那是否有**必要性**呢？

考虑一个以 $-1$ 开头的序列 $a$，它已经能够通过 $d_a=1$ 的区间 $\lbrack 1,1 \rbrack$ 使 $s$ 增大了。我们尝试构造它，使得无论怎么调整，$s$ 只能增大：

- 记 $\{\underbrace{-1, \dots, -1}_{x\text{个}-1},\underbrace{+1, \dots, +1}_{x\text{个}+1}\}$ 为 $U$；

- $\{U,+1,\dots\}$，则已经同时能使 $s$ 增大或减小，失败；

- $\{U,-1,\dots\}$，由于开头的 $-1$ 和 $+1$ 在前缀和中抵消了，又剩下 $-1$，所以重新归约到问题本身；

- $\{\underbrace{-1, \dots, -1}_{x\text{个}-1},\underbrace{+1, \dots, +1}_{y\text{个}+1}\}$（满足 $x>y$），则存在 $d_a=-1$ 的后缀能使 $s$ 减小，失败；

- 最后发现符合要求的 $a$ 只能是形如若干个 $U$（$x$ 不一定相等）拼接而成。

证明不够严谨，但可以感性理解这个结论。~~我不会写啊QwQ~~

构造是构造出来了，可惜这样的序列本身就是无解的。由于这样的 $a$ 中 $-1$ 和 $+1$ 的总数相同，$+1$ 又一定出现在至少一个 $-1$ 之后，于是我可以建立对应关系，令每一个 $a_i=+1$ 都对应它前面最近的 $a_j=-1$，对应关系可以覆盖每个位置；又由于 $b$ 单调递增，对于每个这样的对 $(i,j)$，代入符号后，$+b_i-b_j$ 一定为正；每个对的和都为正，那 $s$ 一定也为正，也就不可能为 $0$ 了。

![](https://cdn.luogu.com.cn/upload/image_hosting/a2v8bdbb.png)

$$\tiny{\gray{\text{每个 +1 对应一个 -1，后面的数又得比前面的大（红色是大于号），所以和一定是正的。}}}$$

开头是 $+1$ 的情况同理。

至此可知，如果不是同时能使 $s$ 减小或增大，那就无解了，所以必要性得证。

到这里我们终于可以说：**初始设置的 $b$ 可以任意取一个递增的数列**（只要调整后不超过 $b_i$ 大小限制），因为有解必然能调整出来，调整不不来一定无解。

关于时间复杂度：填入 $1 \dots n$，求出 $s$，找到 $|d_a| = 1$ 的前、后缀位置，进行调整，都是 $O(n)$ 的操作。

## 代码

```cpp
#include<cstdio>
#define ll long long
#define N_ 200010
int n,sgn[N_];
int pre_n1,pre_p1,suf_n1,suf_p1;
//(前/后缀)_(d_a)
//pre(fix), suf(fix)
//n(egative)1, p(ositive)1
ll ans[N_],s;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sgn[i]);
        ans[i]=i,s+=sgn[i]*i;
    }
    for(int i=1,cnt=0;i<=n;i++){
        cnt+=sgn[i];
        //由于变化量为 ±1，cnt 第一次变为正/负时绝对值一定为 1
        if(!pre_n1&&cnt<0)pre_n1=i;
        if(!pre_p1&&cnt>0)pre_p1=i;
        if(pre_n1&&pre_p1)break;
    }
    for(int i=n,cnt=0;i;i--){
        cnt+=sgn[i];
        if(!suf_n1&&cnt<0)suf_n1=i;
        if(!suf_p1&&cnt>0)suf_p1=i;
        if(suf_n1&&suf_p1)break;
    }
    int pre=0,suf=0;
    //根据 s 的正负性选择需要的区间
    if(s<0)s=-s,pre=pre_n1,suf=suf_p1;
    else if(s>0)pre=pre_p1,suf=suf_n1;
    if(s){
        if(pre){
            for(int i=1;i<=pre;i++)ans[i]-=s;
        }
        else if(suf){
            for(int i=suf;i<=n;i++)ans[i]+=s;
        }
        else{
            printf("No"); return 0;
        }
    }
    printf("Yes\n");
    for(int i=1;i<=n;i++){
        printf("%lld ",ans[i]);
    }
    return 0;
}
```

---

## 作者：rui_er (赞：7)

考虑调整。

首先，令 $x=[1,2,\cdots,n]$ 可以计算出所求 $S=\sum\limits_{i=1}^na_ix_i$。如果 $S\ne 0$，则需要对数列 $x$ 进行调整。

调整 $x$ 的方法无外乎前缀减或者后缀加，其他方法都会导致 $x$ 不满足单调递增的要求。

如果 $S > 0$，则需要将所求往小调。如果存在一个 $a$ 的前缀和为正，或者存在一个 $a$ 的后缀和为负，则我们一定可以通过上述两种调整 $x$ 的方法将所求调小。

因为 $a$ 的值域为 $\{-1,1\}$，可以证明如果存在一个 $a$ 的前缀和为正，则一定存在一个 $a$ 的前缀和为 $1$。因此对于前缀减操作，我们找到这个前缀和为 $1$ 的前缀，将每个数减去 $S$ 即可。同理，如果存在一个 $a$ 的后缀和为负，则一定存在一个 $a$ 的后缀和为 $-1$，后缀加操作找到这个后缀，将每个数加上 $S$ 即可。

如果不存在一个 $a$ 的前缀和为正，且不存在一个 $a$ 的后缀和为负，则显然无解。

$S < 0$ 的情况同理。

时间复杂度 $\Theta(n)$。

```cpp
// Problem: C - ± Increasing Sequence
// Contest: AtCoder - AtCoder Regular Contest 153
// URL: https://atcoder.jp/contests/arc153/tasks/arc153_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 2e5+5;

ll n, a[N], x[N], pre[N], suf[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	scanf("%lld", &n);
	rep(i, 1, n) scanf("%lld", &a[i]);
	rep(i, 1, n) x[i] = i;
	ll S = 0;
	rep(i, 1, n) S += a[i] * x[i];
	rep(i, 1, n) pre[i] = pre[i-1] + a[i];
	per(i, n, 1) suf[i] = suf[i+1] + a[i];
	if(S > 0) {
		ll ok = 0;
		rep(i, 1, n) {
			ok |= pre[i] > 0;
			ok |= suf[i] < 0;
		}
		if(!ok) return puts("No")&0;
		ll pos = 0;
		rep(i, 1, n) {
			if(pre[i] == 1) {
				pos = i;
				break;
			}
		}
		if(pos) rep(i, 1, pos) x[i] -= S;
		else {
			per(i, n, 1) {
				if(suf[i] == -1) {
					pos = i;
					break;
				}
			}
			rep(i, pos, n) x[i] += S;
		}
	}
	else if(S < 0) {
		ll ok = 0;
		rep(i, 1, n) {
			ok |= pre[i] < 0;
			ok |= suf[i] > 0;
		}
		if(!ok) return puts("No")&0;
		ll pos = 0;
		rep(i, 1, n) {
			if(pre[i] == -1) {
				pos = i;
				break;
			}
		}
		if(pos) rep(i, 1, pos) x[i] -= -S;
		else {
			per(i, n, 1) {
				if(suf[i] == 1) {
					pos = i;
					break;
				}
			}
			rep(i, pos, n) x[i] += -S;
		}
	}
	puts("Yes");
	rep(i, 1, n) printf("%lld%c", x[i], " \n"[i==n]);
	return 0;
}
```

---

## 作者：王熙文 (赞：3)

## 思路

首先，看到递增可以想到差分。设 $y$ 数组为 $x$ 数组的差分数组，则 $x_i = \sum\limits_{j=1}^i y_i$。此时 $\sum\limits_{i=1}^n a_ix_i=0$ 就转化成了 $\sum\limits_{i=1}^n a_i
\sum\limits_{j=1}^i y_j$。将 $j$ 提出来，变成了 $\sum\limits_{j=1}^n y_j \sum\limits_{i=j}^n a_i$。设 $b_i = \sum_{j=i}^n a_j$，则原要求变成 $\sum_{i=1}^n b_iy_i=0$。

现在的问题便转化成了，构造一个数组 $y$，使得：

* $\forall 1 \le i \le n, y_i \in \mathbb{Z}$
* $-10^{12} \le y_1$
* $\forall 2 \le i \le n,y_i>0$
* $\sum\limits_{i=1}^n y_i \le 10^{12}$
* $\sum_{i=1}^n b_iy_i=0$。

注意到 $b_n=a_n \in \{-1,1\}$，并且 $y_n=\dfrac{-\sum\limits_{i=1}^{n-1}b_i y_i}{b_n}$，所以只需要构造 $\sum_{i=1}^{n-1} b_iy_i$ 与 $b_n$ 异号，就会使 $y_n \in N_{+}$，满足条件。

接下来会考虑 $b_n=1$ 的情况，$b_n=-1$ 与 $b_n=1$ 本质相同。

当 $b_n=1$ 时，我们希望 $\sum_{i=1}^{n-1} b_iy_i<0$。如果有一个位置可以使那个位置的 $b_iy_i$ 变成最小值（比如 $-10^{11}$，但不要设为 $-10^{12}$，加起来会超），则剩下的位置直接填 $1$，就满足要求了（剩下的加起来不可能超过 $10^{11}$，因为 $b_i$ 的值域是 $\mathcal O(n)$ 的，所以加起来值域是 $\mathcal O(n^2)$）。

当 $i=1$ 时，如果 $b_i \not= 0$，因为 $y_1$ 可以是任意数，$b_iy_i$ 就一定可以变成最小值。当 $i \not=1$ 时，如果 $b_i <0$，因为 $y_i$ 可以是任意正整数，$b_iy_i$ 就一定可以变成最小值。

如果存在这样的 $b_i$，有解，上面已经构造出来了；如果不存在这样的 $b_i$，那么显然 $\sum_{i=1}^{n-1} b_iy_i$ 会是非负数，无解。

## 代码

注意：$b_iy_i$ 是最小值的 $y_i$ 不要设为 $-10^{11}$，而是让 $b_i y_i$ 在大约 $-10^{11}$ 处，因为最后的 $y_n$ 是前面的加起来，如果 $y_i=-10^{11}$，那么 $b_iy_i$ 有可能小于 $-10^{12}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n; int a[200010];
int b[200010];
int y[200010];
signed main()
{
	cin>>n;
	for(int i=1; i<=n; ++i) cin>>a[i];
	for(int i=n; i>=1; --i) b[i]=b[i+1]+a[i];
	if(n==1) return cout<<"Yes\n0",0;
	if(b[n]==1)
	{
		bool flag=0;
		for(int i=1; i<=n-1; ++i)
		{
			if(i==1 && b[i])
			{
				y[i]=-1e11/b[i];
				flag=1;
				break;
			}
			if(i!=1 && b[i]<0)
			{
				y[i]=-1e11/b[i];
				flag=1;
				break;
			}
		}
		if(flag)
		{
			int sum=0;
			for(int i=1; i<=n-1; ++i)
			{
				if(!y[i]) y[i]=1;
				sum+=y[i]*b[i];
			}
			assert(sum<=-1);
			y[n]=-sum;
			cout<<"Yes\n";
			int ssum=0;
			for(int i=1; i<=n; ++i) y[i]+=y[i-1],cout<<y[i]<<' ',ssum+=y[i]*a[i],assert(y[i]>=-1e12 && y[i]<=1e12);
			assert(!ssum);
		}
		else cout<<"No";
	}
	else
	{
		bool flag=0;
		for(int i=1; i<=n-1; ++i)
		{
			if(i==1 && b[i])
			{
				y[i]=1e11/b[i];
				flag=1;
				break;
			}
			if(i!=1 && b[i]>0)
			{
				y[i]=1e11/b[i];
				flag=1;
				break;
			}
		}
		if(flag)
		{
			int sum=0;
			for(int i=1; i<=n-1; ++i)
			{
				if(!y[i]) y[i]=1;
				sum+=y[i]*b[i];
			}
			assert(sum>=1);
			y[n]=sum;
			cout<<"Yes\n";
			int ssum=0;
			for(int i=1; i<=n; ++i) y[i]+=y[i-1],cout<<y[i]<<' ',ssum+=y[i]*a[i],assert(y[i]>=-1e12 && y[i]<=1e12);
			assert(!ssum);
		}
		else cout<<"No";
	}
	return 0;
}
```

---

## 作者：Leasier (赞：3)

首先把 $x_i < x_{i + 1}$ 的条件转化为差分，令 $x_i = \displaystyle\sum_{j = 1}^i y_j$，则 $\forall 2 \leq i \leq n, y_i > 0$。

于是 $\displaystyle\sum_{i = 1}^n a_i \sum_{j = 1}^i y_j = \sum_{j = 1}^n y_j \sum_{i = j}^n a_i = 0$。

令 $b$ 为 $a$ 的后缀和，有 $\displaystyle\sum_{j = 1}^n b_j y_j = 0$。

若不考虑整数的限制且 $b_1 \neq 0$，我们可以这样构造：

- $\forall 2 \leq i \leq n$，令 $y_i \leftarrow 1$。
- 令 $y_1 \leftarrow -\dfrac{\displaystyle\sum_{i = 2}^n b_i}{b_1}$。

要是我们加上整数的限制呢？不难发现我们可以将所有 $y_i$ 统一乘上 $b_1$，此时一定满足原等式。不过 $b_1$ 可能 $< 0$，所以我们乘上 $|b_1|$ 即可。

现在考虑 $b_1 = 0$。

此时有什么无解的情况呢？注意到若 $b_i$ 全部非负或全部非正，则把 $0$ 扔掉后只剩下一堆强制 $> 0$ 乘上正 / 负数，则一定非 $0$，此时无解。

否则，我们考虑先构造一堆 $y_i = 1$，然后分两种情况讨论：

- $\displaystyle\sum_{i = 1}^n b_i \geq 0$：此时我们找出一个 $b_{pos} = -1$ 者并令 $y_{pos} \leftarrow y_{pos} + \displaystyle\sum_{i = 1}^n b_i$。
- $\displaystyle\sum_{i = 1}^n b_i < 0$：此时我们找出一个 $b_{pos} = 1$ 者并令 $y_{pos} \leftarrow y_{pos} - \displaystyle\sum_{i = 1}^n b_i$。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;

int a[200007];
ll ans[200007];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for (int i = n; i >= 1; i--){
		a[i] += a[i + 1];
	}
	if (a[1] != 0){
		int val = abs(a[1]);
		for (int i = 2; i <= n; i++){
			ans[i] = val;
			ans[1] -= a[i];
		}
		ans[1] *= val / a[1];
	} else {
		bool flag1 = true, flag2 = true;
		for (int i = 1; i <= n; i++){
			flag1 &= a[i] >= 0;
			flag2 &= a[i] <= 0;
		}
		if (flag1 || flag2){
			printf("No");
			return 0;
		}
		int pos;
		ll sum = 0;
		for (int i = 1; i <= n; i++){
			sum += a[i];
			ans[i] = 1;
		}
		if (sum >= 0){
			for (int i = 1; i <= n; i++){
				if (a[i] == -1){
					pos = i;
					break;
				}
			}
			ans[pos] += sum;
		} else {
			for (int i = 1; i <= n; i++){
				if (a[i] == 1){
					pos = i;
					break;
				}
			}
			ans[pos] -= sum;
		}
	}
	printf("Yes\n");
	for (int i = 1; i <= n; i++){
		ans[i] += ans[i - 1];
		printf("%lld ", ans[i]);
	}
	return 0;
}
```

---

## 作者：spire001 (赞：1)

## AT_arc153_c

### 前言
本来题解已经过了，但是自己复查的时候发现一键替换 `or` 将代码里的 ```for``` 替换成了 `fvee`。  
修改了一下重新提交题解。

其他题解怎么都那么长啊！！！

我来给一个与其他题解思路略有不同但及其好理解的做法。

### 分析

首先从限制入手，看到 $x_i<x_{i+1}$ 这种构造，有一个套路就是令 $y_i=x_i-i$，然后构造 $\{y\}$ 满足 $y_i\le y_{i+1}$ 这是由于在整数域中 $x_i<x_{i+1}$ 等价于 $x_i+1\le x_{i+1}$，这个式子两边再同时加上一个数也不影响。

记常数 $-\sum iA_i$ 为 $B$。

那么原题条件变为：
$$
\sum_{i=1}^nA_i(y_i+i)=\sum_{i=1}^n A_iy_i+iA_i=0\Longrightarrow \sum_{i=1}^nA_iy_i=B
$$
考虑构造 $\{y\}$ 即可。

肯定希望那么多数字相同的比较好构造。

比如说 $B=0$ 时，$A_i=0$ 是最好的选择。

平凡的，如果 $B>0\wedge A_n=1$ 那么直接令 $y_n\leftarrow B$ 即可。

同理还有 $(B>0 \wedge A_1=-1) \vee (B<0\wedge A_1=1) \vee (B<0\wedge A_n=-1)$ 这几种情况。

剩下的情况怎么办？

为了表述方便，记二元谓词 $f(p,q)$ 为 $p,q$ 符号相同（即 $[\frac{|{p}|}{p}=\frac{|{q}|}{q}]$）。

进一步，断言存在解的充分必要条件为 $\exists k,f(\sum_{i=1}^kA_i,B)=0\vee f(\sum_{i=k}^nA_i,B)=1$。

证明比较平凡，具体是利用 $\{y\}$ 的单调性以及 $\{A\}$ 的有界性（$A_i\in \{-1,1\}$），若不满足断言的条件，则根本不存在一个 $\{y\}$ 使得 $f(\sum A_iy_i,B)=1$。

那么假设已经找到了一个 $k$ 满足断言条件。

构造也非常简单，如果满足前缀的限制，则将前缀填上 $-\ |{B}|$，如果满足后缀限制则将后缀填上 $|B|$，不懂就类比上面的特殊情况或看代码。

### 代码

~~对了，记得开 `long long`。。~~

```cpp
#include <iostream>
#include <cstring>
#include <algveeithm>
#include <vectvee>
#include <cassert>
#include <numeric>
#define NO return cout << "No" << endl, 0

using namespace std;

typedef long long LL;
template <typename T1, typename T2> inline void cmax(T1 &A, const T2 &B)  { if (A < B) A = B; return; }
template <typename T1, typename T2> inline void cmin(T1 &A, const T2 &B)  { if (A > B) A = B; return; }
template <typename T1, typename T2, int mod = 998244353> inline void ad(T1 &A, const T2 &B) { A = (A + B) % mod; return; }
template <typename T1, typename T2, int mod = 998244353> inline void sb(T1 &A, const T2 &B) { A = (A + mod - B) % mod; return; }

int n, a[200010], sum[200010]; // 前缀和
LL res[200010]; // 储存构造出的 y, long long 

bool check(LL s)
{
  if (s > 0)
  {
    for (int i = 1; i <= n; i++)
    {
      if (sum[i] == -1) // 如果存在某一个点的 A 前缀和小于 0, 则必然第一个点为 -1
      {
        for (int j = 1; j <= i; j++) res[j] = -s;
        return true;
      }
      else if (sum[n] - sum[i - 1] == 1)
      {
        for (int j = i; j <= n; j++) res[j] = s;
        return true;
      }
    }
    return false;
  }
  else if (s < 0)
  {
    for (int i = 1; i <= n; i++)
    {
      if (sum[i] == 1) 
      {
        for (int j = 1; j <= i; j++) res[j] = s;
        return true;
      }
      else if (sum[n] - sum[i - 1] == -1)
      {
        for (int j = i; j <= n; j++) res[j] = -s;
        return true;
      }
    }
    return false;
  }
  
  return true;
}

int main()
{
  cin >> n;

  for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];

  LL s = 0;

  for (int i = 1; i <= n; i++) s -= a[i] * i;

  if (s > 0)
  {
    if (a[1] == -1) res[1] = -s;
    else if (a[n] == 1) res[n] = s;
    else if (!check(s)) NO; // 否则非法
  }
  else if (s < 0)
  {
    if (a[1] == 1) res[1] = s;
    else if (a[n] == -1) res[n] = -s;
    else if (!check(s)) NO;
  }

  cout << "Yes" << endl; // 找到了合法解
  for (int i = 1; i <= n; i++)
    cout << res[i] + i << ' ';
  
  return 0;
}

/*
begin:  2024年10月5日09:33:53
debug:  2024年10月5日09:39:34
debug:  2024年10月5日10:01:34
finish: 2024年10月5日10:01:59
*/
```

---

## 作者：Laoshan_PLUS (赞：0)

很不错的思维题，考场上想不出来纯属大脑里的明纳尔特共振。（雾

---

下面习惯地将原 $A$ 序列称为 $a$，原 $x$ 序列称为 $b$。（因为模拟赛的题面这么叫的）

我们首先随便构造一个 $b$ 序列，从 $1$ 到 $n$，计算出此时的 $\sum_{i=1}^na_ib_i$，记为 $S$。

- 若 $S=0$，结束了。
- 若 $S\ne0$，我们考虑进行调整。

考虑到题目中有两个限制，一是 **和为 0**，二是 $b$ 序列**严格递增**。我们最开始构造出的序列是满足限制二的，所以我们就在满足限制二的前提下去尝试满足限制一。而能保持限制二的前提无非是**前缀减**或**后缀加**，这样都不会改变单调递增的性质。

当 $S>0$ 时，证明这个序列大了，我们给他调小。易证，若 $a$ 序列存在一个前缀和为正值，或存在一个后缀和为负值，那么一定可以成功调整。

> **口胡证明：**
>
> 假设有一组数 $a,b,c,d,\dots$，满足 $a+b-c+d+\cdots=0$（随便给的，由一般可推所有），那么给 $a,b,c,d,\dots$ 统一加上或减去一个数，这个等式依然成立。
>
> 那么对于 $S>0$ 的情况，如果存在一个前缀和为正值，说明这组数多出了一个数导致它们的和不为 $0$ 了，此时给这组数统一加或减一个数，相当于只给多出来的那一个数加或减，那么一定可以成功调整。
>
> 其余情况同理的。
>
> ~~我的口胡看不懂就自己想想吧，很好想的。~~

所以我们只需暴力求一下前缀和和后缀和，看是否能满足上述的任意一个条件。如果都不满足那就是无解，输出 `No`。反之就是有解。

对于 $S<0$ 的情况同理的，只不过条件变成了存在一个前缀和为负值，或存在一个后缀和为正值。

这题的 $n$ 只有 $2\times10^5$，又是求可行解，复杂度的问题不用考虑。**别忘开 long long 就行。**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 2e5 + 5;
int n, a[MAXN], b[MAXN];

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	iota(b + 1, b + n + 1, 1);
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += a[i] * b[i];
	if (sum == 0) {
		puts("Yes");
		for (int i = 1; i <= n; i++) cout << b[i] << ' ';
		cout << '\n';
	} else if (sum < 0) {
		int sma = 0, i;
		for (i = 1; i <= n && sma >= 0; i++) sma += a[i];
		--i;
		if (sma < 0) {
			puts("Yes");
			for (int j = 1; j <= i; j++) cout << b[j] + sum << ' ';
			for (int j = i + 1; j <= n; j++) cout << b[j] << ' ';
			cout << '\n';
			return 0;
		}
		for (i = n; i >= 1 && sma <= 0; i--) sma += a[i];
		++i;
		if (sma > 0) {
			puts("Yes");
			for (int j = 1; j < i; j++) cout << b[j] << ' ';
			for (int j = i; j <= n; j++) cout << b[j] - sum << ' ';
			cout << '\n';
			return 0;
		}
		puts("No");
	} else {
		int sma = 0, i;
		for (i = 1; i <= n && sma <= 0; i++) sma += a[i];
		--i;
		if (sma > 0) {
			puts("Yes");
			for (int j = 1; j <= i; j++) cout << b[j] - sum << ' ';
			for (int j = i + 1; j <= n; j++) cout << b[j] << ' ';
			cout << '\n';
			return 0;
		}
		for (i = n; i >= 1 && sma >= 0; i--) sma += a[i];
		++i;
		if (sma < 0) {
			puts("Yes");
			for (int j = 1; j < i; j++) cout << b[j] << ' ';
			for (int j = i; j <= n; j++) cout << b[j] + sum << ' ';
			cout << '\n';
			return 0;
		}
		puts("No");
	}

	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

（$A$ 数组的下标从 $0$ 开始）

令 $suf_i=\sum_{j=i}^{n-1}a_i$。我们其实是要找出一个序列 $b_0\cdots b_{n-1}$，满足 $b_1\cdots b_{n-1}$ 都是正整数，且 $\sum b_isuf_i=0$。其实 $b$ 就是题目中 $x$ 的差分数组。

由于b中除了第一个数都要取正数，那就先把 $b_1\cdots b_{n-1}$ 都取 $1$，$b_0$ 取 $0$，后面如果需要可以再加。如果此时 $\sum b_isuf_i$ 已经为 $0$，那就直接输出解。否则，如果 $suf_1\cdots suf_{n-1}$ 中有正有负，那肯定有解，因为 $suf_{n-1}$ 是 $1$ 或 $-1$，如果是 
$1$ 的话就随便找一个 $<0$ 的 $suf_i$，不断给 $b_i$ 加 $1$ 直到 $\sum b_isuf_i\le 0$，然后再用 $suf_{n-1}$ 加回来即可。$suf_{n-1}=-1$ 同理。

剩下的情况，如果 $suf_0=0$ 肯定无解，这是显然的。否则也肯定有解，比如 $suf_{n-1}=1$ 时，可以像上面一样，先用 $suf_0$ 把 $\sum b_isuf_i$ 压到非正数，再用 $suf_{n-1}$ 加回来。
## Code
```cpp
#include <bits/stdc++.h>
 
#define rep(i,n) for(int i=0;i<n;++i)
#define repn(i,n) for(int i=1;i<=n;++i)
#define LL long long
#define pii pair <int,int>
#define fi first
#define se second
#define mpr make_pair
#define pb push_back
 
void fileio()
{
  #ifdef LGS
  freopen("in.txt","r",stdin);
  freopen("out.txt","w",stdout);
  #endif
}
void termin()
{
  #ifdef LGS
  std::cout<<"\n\nEXECUTION TERMINATED";
  #endif
  exit(0);
}
 
using namespace std;
 
LL n,a[200010],ans[200010],sufsum[200010];
 
void print()
{
  puts("Yes");
  rep(i,n)
  {
    printf("%d ",ans[i]);
    ans[i+1]+=ans[i];
  }
  puts("");
  termin();
}
void fuck(){puts("No");termin();}
 
int main()
{
  fileio();
 
  cin>>n;
  rep(i,n) scanf("%lld",&a[i]);
  LL sum=0,cur=0,posi=-1,nega=-1;
  for(int i=n-1;i>0;--i)
  {
    sum+=a[i];sufsum[i]=sum;
    ans[i]=1;cur+=sum;
    if(sum>0) posi=i;else if(sum<0) nega=i;
  }
  if(cur==0) print();
  //if(a[n-1]==1) posi=n-1;else nega=n-1;
  if(posi>-1&&nega>-1)
  {
    if(a[n-1]==1)
    {
      LL usenega=(max(0LL,cur)-sufsum[nega]-1)/(-sufsum[nega]);
      ans[nega]+=usenega;cur+=usenega*sufsum[nega];
      ans[n-1]-=cur;
    }
    else
    {
      LL useposi=(-min(0LL,cur)+sufsum[posi]-1)/sufsum[posi];
      ans[posi]+=useposi;cur+=useposi*sufsum[posi];
      ans[n-1]+=cur;
    }
    print();
  }
  if(sum+a[0]==0) fuck();
  sum+=a[0];
  if(a[n-1]==1)
  {
    LL targ=(cur+llabs(sum)-1)/llabs(sum)*llabs(sum);
    ans[n-1]+=targ-cur;
    ans[0]=-(targ/sum);
  }
  else
  {
    LL targ=(-cur+llabs(sum)-1)/llabs(sum)*llabs(sum);targ=-targ;
    ans[n-1]+=llabs(targ-cur);
    ans[0]=-(targ/sum);
  }
  print();
 
  termin();
}
```

---

## 作者：_ZSR_ (赞：0)

### [[ARC153C] ± Increasing Sequence](https://www.luogu.com.cn/problem/AT_arc153_c)

构造题，并且题目说了可能无解，按照常规思路那就先判断什么时候无解。想了一会发现其实不好判断，那还是先想构造吧。

题目要求 $x$ 序列递增，那先不管和是否为 $0$，直接令 $x_i=i$，然后再来想怎么调整。假设当前和为 $S$，如果 $S>0$，那么我们要把它调小，反之要把它调大。这里就只说 $S>0$ 的情况，$S<0$ 的情况反一下就可以了。

因为要保证序列递增，所以调整中间是不好调整的，考虑调整一段前缀或者后缀。显然，前缀只能减，而后缀只能加，这样才能充分保证 $x$ 序列是递增的。考虑给前缀都减去 $k$ 会发生什么变化。$S'=S-\sum (a_i \times k)=S-(\sum a_i) \times k$。我们发现，当 $\sum a_i=1$ 时，我们只要令 $k=S$ 即可把和变成 $0$，从而满足条件。后缀也差不多，如果有一段后缀和等于 $-1$，那么我们可以加上 $S$ 使得和为 $0$。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int n,sum;
int a[N],x[N],pre[N],suf[N];
signed main()
{
    scanf("%lld",&n);
    for (int i=1;i<=n;++i) 
    {
        scanf("%lld",&a[i]);
        x[i]=i;
        sum+=a[i]*x[i];
    }
    for (int i=1;i<=n;++i) pre[i]=pre[i-1]+a[i];
    for (int i=n;i>=1;--i) suf[i]=suf[i+1]+a[i];
    if (sum>0)
    {
        bool flag=false;
        for (int i=1;i<=n;++i)
        {
            if (pre[i]>0||suf[i]<0) 
            {
                flag=true;
                break;
            }
        }
        if (!flag) 
        {
            puts("No");
            return 0;
        }
        puts("Yes");
        int pos=0;
        for (int i=1;i<=n;++i)
        {
            if (pre[i]==1)
            {
                pos=i;
                break;
            }
        }
        if (pos) 
        {
            for (int i=1;i<=pos;++i) x[i]-=sum;
            for (int i=1;i<=n;++i) printf("%lld ",x[i]);
            return 0;
        }
        for (int i=n;i>=1;--i) 
        {
            if (suf[i]==-1)
            {
                pos=i;
                break;
            }
        }
        if (pos)
        {
            for (int i=pos;i<=n;++i) x[i]+=sum;
            for (int i=1;i<=n;++i) printf("%lld ",x[i]);
            return 0;
        }
    }
    if (sum<0)
    {
        bool flag=false;
        for (int i=1;i<=n;++i)
        {
            if (pre[i]<0||suf[i]>0) 
            {
                flag=true;
                break;
            }
        }
        if (!flag) 
        {
            puts("No");
            return 0;
        }
        puts("Yes");
        int pos=0;
        for (int i=1;i<=n;++i)
        {
            if (pre[i]==-1)
            {
                pos=i;
                break;
            }
        }
        if (pos) 
        {
            for (int i=1;i<=pos;++i) x[i]-=-sum;
            for (int i=1;i<=n;++i) printf("%lld ",x[i]);
            return 0;
        }
        for (int i=n;i>=1;--i) 
        {
            if (suf[i]==1)
            {
                pos=i;
                break;
            }
        }
        if (pos)
        {
            for (int i=pos;i<=n;++i) x[i]+=-sum;
            for (int i=1;i<=n;++i) printf("%lld ",x[i]);
            return 0;
        }
    }
    puts("Yes");
    for (int i=1;i<=n;++i) printf("%lld ",x[i]);
    return 0;
}
```


---

## 作者：FyFive (赞：0)

写给管理：本体的思维难度和思维量我个人认为可以给到蓝/紫，具体可以看题管感觉

---
>简要题意：
>给定一个由 $1/-1$ 组成的长度为 $n$ 序列 $A$，构造一个序列 $x$，满足：
>- $\forall \ i<n,\ x_i<x_{i+1}$。
>- $\displaystyle \sum_{i=1}^n A_i x_i =0$。
>- 若有解，输出 ``Yes`` 并输出构造的序列，否则输出 ``No``。
>- 构造的序列应满足 $\forall \ i\leq n,-10^{12} \leq x_i \leq 10^{12}$。

>数据范围：
>- $1 \leq n \leq 2 \times 10^5$。

---
首先，本题会有数据是无解的，这是毋庸置疑的，但是由于是 AT 上的题，“不可以，总司令” 将一分没有，所以判无解也是需要谨慎思考的一部分。

由于 Fy5 在一开始的时候判无解过于草率，错了 14 个点……

但是先不慌，读懂题目之后，一步步来。

---
#### Step 1
首先当然是初步判无解啦！

要想知道什么情况下无解，那就得想想什么情况是不可能无解的。

不难想到，如果初始时序列里全是 0，那么如果变成全是 1，那么 $\displaystyle \sum_{i=1}^n A_i x_i$ 的值便会变成 $\displaystyle \sum_{i=1}^n A_i$。

推广可知，如果 $\forall \ i \leq n,x_i \rightarrow x_i +1$，那么 $\displaystyle \sum_{i=1}^n A_i x_i$ 的值便会加上 $\displaystyle \sum_{i=1}^n A_i$。

有了这一点，当 $\displaystyle \sum_{i=1}^n A_i$ 的值不等于 0 的时候，便可以设计出一个基础的构造：
- 将序列赋上一个初始值，先求当前的 $\displaystyle \sum_{i=1}^n A_i x_i$ 值，然后根据需要进行全序列增删。
- 为保证一定能构造出正确的序列，可以执行 $\displaystyle \forall \ i \leq n,x_i\rightarrow x_i \cdot \sum_{i=1}^n A_i$
- 如果 $\displaystyle \sum_{i=1}^n A_i =0$，直接判无解。

看上去还挺对的不是吗？计算可得极端情况下任一 $x_i$ 都是满足值域限制的。

此时直接提交，如果足够正确，你可以过 62 个点，并发现整个 07_max_zero 部分的点全是错的，并且 04_small_zero 部分也基本上是错的。
除开这两个部分，刚好 62 个点。

#### Step 2
这个时候，如果你成功造了一组 hack 证实了部分 $\displaystyle \sum_{i=1}^n A_i =0$ 的情况是有解的，那么恭喜你，离正解真的只差 14 个点了。

现在考虑为什么可以构造出解。

不难发现，整体加减的结论对于某一段也是适用的。

那么思考这样一种增删方案：对于序列的前缀或后缀，进行加减。

不难得知，在初始序列是 1 到 n 的情况下，前缀只能减，后缀只能加。

那么，记录 $A$ 的前缀和与后缀和，如果有某个前缀和或后缀和可以满足进行增删后可以消掉 $x_i \rightarrow i$ 带来的偏差，那么就有解，否则无解。

时间复杂度是 O(n) 的。

#### Code
```cpp
signed main()
{
  cin>>n;
  for(int i=1;i<=n;++i)
  {
    cin>>a[i];
    sum+=a[i];
  }
  if(sum==0)
  {
    for(int i=1;i<=n;++i)
    {
      ans[i]=i;
      saa+=ans[i]*a[i];
    }
    if(saa!=0)
    {
      for(int i=1;i<=n;++i)
      {
        qzh[i]=qzh[i-1]+a[i];
        if(qzh[i]*saa>0)
        {
          for(int j=1;j<=i;++j)
          {
            ans[j]-=saa/qzh[i];
          }
          cout<<"Yes"<<endl;
          for(int j=1;j<=n;++j) cout<<ans[j]<<' ';
          return 0;
        }
      }
      for(int i=n;i>=1;--i)
      {
        hzh[i]=hzh[i+1]+a[i];
        if(hzh[i]*saa<0)
        {
          for(int j=n;j>=i;--j)
          {
            ans[j]-=saa/hzh[i];
          }
          cout<<"Yes"<<endl;
          for(int j=1;j<=n;++j) cout<<ans[j]<<' ';
          return 0;
        }
      }
      cout<<"No";
      return 0;
    }
    cout<<"Yes"<<endl;
    for(int i=1;i<=n;++i) cout<<ans[i]<<' ';
    return 0;
  }
  cout<<"Yes"<<endl;
  for(int i=0;i<n;++i)
  {
    ans[i+1]=abs(sum)*i;
    mus+=ans[i+1]*a[i+1];
  }
  mus/=sum;
  for(int i=1;i<=n;++i)
  {
    ans[i]-=mus;
  }
  for(int i=1;i<=n;++i) cout<<ans[i]<<' ';
  return 0;
}
```

---

## 作者：Galex (赞：0)

考虑先随便构造满足要求的 $x_1,x_2,\cdots,x_{n-1}$，然后得到为了满足 $\sum_{i=1}^n a_ix_i=0$，$x_n$ 的值。随后分类讨论。

为方便，钦定 $a_n=1$。若 $a_n=-1$，则将所有 $a_i$ 变成 $-a_i$。

若 $x_{n-1}<x_{n}$，则说明此时是一组合法解，直接输出即可。

否则，若存在一个 $p$ 满足 $(\sum_{i=1}^p a_i)=1$，则将 $x_1,x_2,\cdots,x_p$ 都减去无穷大。这样 $x_n$ 就需要加上无穷大，显然就能满足要求。

最后，若不存在这样的 $p$，则无解。证明比较显然。

一些实现上的细节：一开始 $x_1,x_2,\cdots,x_{n-1}$ 可以设为 $1,2,\cdots,n-1$，无穷大设为差不多 $10^{11}$ 就行。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n;
int a[200005], ans[200005];

signed main() {
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	if (n == 1) {
		printf("Yes\n0");
		return 0;
	}
	if (a[n] == -1) {
		for (int i = 1; i <= n; i++)
			a[i] = -a[i];
	}
	int sum = 0;
	for (int i = 1; i < n; i++)
		ans[i] = i, sum += a[i] * i;
	ans[n] = -sum;
	if (ans[n] > ans[n - 1]) {
		printf("Yes\n");
		for (int i = 1; i <= n; i++)
			printf("%lld ", ans[i]);
		return 0;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		cnt += a[i];
		if (cnt > 0) {
			printf("Yes\n");
			for (int j = 1; j <= i; j++)
				ans[j] -= 300000000000;
			ans[n] += 300000000000;
			for (int j = 1; j <= n; j++)
				printf("%lld ", ans[j]);
			return 0;
		}
	}
	printf("No");
	return 0;
}
```

---

## 作者：Daidly (赞：0)

## 题意

给定长为 $n$ 的序列 $A$，其中 $A_i=1/-1$，判断是否存在长为 $n$ 的序列 $x$ 满足：

1. $|x_i|\leq 10^{12}$；

2. $x_i$ 单调递增；

3. $\sum_{i=1}^nA_ix_i=0$。

输出 `Yes` 或 `No`，若为 `Yes`，还需输出序列 $x$。

$n\leq 2\times 10^5$

## 题解

发现递增，先尝试差分：记序列 $y$ 为序列 $x$ 的差分序列，即 $y_1=x_1,y_i=x_i-x_{i-1}(i>1)$。

则【条件 1】转化为 $\sum_{k=1}^iy_k\leq 10^{12}$，【条件 2】转化为 $y_i>0(i>1)$，【条件 3】转化为 $\sum_{i=1}^nA_i\big(\sum_{k=1}^iy_k\big)=0$。

考虑化简【条件 3】中的式子：

$$
\sum\limits_{i=1}^nA_i\sum\limits_{k=1}^iy_k=\sum_{k=1}^ny_k\sum_{i=k}^nA_i
$$

记 $B_k=\sum\limits_{i=k}^nA_i$，则【条件 3】转化为：

$$
\sum_{i=1}^nB_iy_i=0
$$

发现特殊点：$y_1$ 的正负性不受限制，我们考虑将贡献转移到 $y_1$ 上，取 $y_i=|B_1|(i>1)$，则有：

$$
y_1=\frac{1}{-B_1}\sum_{i=2}^nB_i|B_1|
$$

显然，这需要 $B_1\ne 0$。

若 $B_1=0$ 呢？

把 $y_1$ 的特殊性去掉，要求 $\sum_{i=2}^nB_iy_i=0$，且 $y_i>0$。这个问题看起来很纯净，顺着思路想。

首先判无解，若 $\forall i,B_i\leq 0$ 或 $\forall i,B_i\ge 0$，则一定没有一组 $y_i$ 满足条件（加上等于是因为 $B_2$ 一定不等于 $0$）。

所以此时 $B_i$ 既有 $0$ 又有正负数。又因为 $|B_i-B_{i-1}|=1$，所以一定能找到 $B_p=-1$ 以及 $B_q=1$。

不妨把 $y_i$ 全赋值为 $1$，【条件 1】显然满足。此时多出来的是 $S=\sum_{i=1}^nB_iy_i$，考虑消去 $S$。

若 $S\ge 0$，则找到一个 $B_q=-1$，将其 $y_q$ 增加 $S$ 即可。

若 $S<0$，则找到一个 $B_p=1$，将其 $y_q$ 增加 $-S$ 即可。

最后前缀和还原序列 $x$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=2e5+5;
int n,a[N],b[N],y[N],sum,cnt1,cnt2;

signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=n;i>=1;--i)b[i]=b[i+1]+a[i];
	if(b[1]){
		for(int i=2;i<=n;++i)y[1]+=b[i],y[i]=abs(b[1]);
		if(b[1]>0)y[1]=-y[1];
	}else{
		sum=cnt1=cnt2=0;
		for(int i=2;i<=n;++i)sum+=b[i],cnt1+=(b[i]<=0),cnt2+=(b[i]>=0);
		if(cnt1==n-1||cnt2==n-1){puts("No");return 0;}
		for(int i=1;i<=n;++i)y[i]=1;
		if(sum>=0){
			for(int i=1;i<=n;++i)if(b[i]==-1){y[i]+=sum;break;}
		}else{
			for(int i=1;i<=n;++i)if(b[i]==1){y[i]-=sum;break;}
		}
	}
	sum=0;puts("Yes");
	for(int i=1;i<=n;++i)sum+=y[i],print(sum),putchar(' ');
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：0)

## [[ARC153C] ± Increasing Sequence](https://www.luogu.com.cn/problem/AT_arc153_c)

### 破题点

有这样一个思维套路：

> 两个约束条件很难同时满足，考虑只满足一个比较难的，之后再来慢慢满足一个比较容易的条件。

这题能使大家掌握的：

在保证序列严格递增的条件下，做构造操作，通过前缀减或者后缀加实现是一种利器。

本题就是利用这两种操作，我们可以完美地构造出所需数列。

### 题解

首先序列严格递增这个条件相对而言，**更加难维护**，相比之下，求和等于 $0$ 的情况就较为简单。

所以我们需要在构造过程之中**保证序列严格递增**。

先构造个 $[1,n]$ 的序列，然后答案不太可能满足要求，设之为 $S$。

我们手上有两种操作：一种前缀减，一种后缀加。

---

若 $S>0$，则需要把 $S$ 降到较低的水平，这时候我们考虑 $a_i$ 的前缀和为正数的情况，或者 $a_i$ 的后缀和为负数的情况。

此时若有 $j$ 使得 $a_i$ 的前缀和为 $1$，那么直接对 $[1,j]$ 进行 $S$ 次前缀减。

若有 $j$ 使得 $a_i$ 的后缀和为 $-1$，那么直接对 $[j,n]$ 进行 $S$ 次后缀加。

若两者都没有，那么直接输出 `No`。

---

$S<0$ 的情况也类似。只不过执行的是 $-S$ 次前缀减（因为要保证操作次数非负）。

---

### 细节

实在不懂细节就看代码吧。代码很清爽。

代码实现上，采用前缀减/后缀加函数，简化代码实现。

另外，要开 LL 的就开 LL。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(auto i(a),_ei(b);i<=_ei;++i)
#define gch(w) for(;w(CH);CH=getchar())
using I=int;using V=void;using LL=long long;I FL,CH;LL in(){LL a(0);FL=1;gch(!isdigit)FL=(CH=='-')?-1:1;gch(isdigit)a=a*10+CH-'0';return a*FL; }using namespace std;
const I N=2e5+10;
I n,a[N],pv[N],sf[N],b[N];
LL s;
V ad(I st,LL x,I op){//前缀减或者后缀加，注意 x 不为负。
	puts("Yes");
	if(op)fo(i,1,n){
		if(i>=st)printf("%lld ",i+x);//后缀加 
		else printf("%d ",i);}
	else{
		fo(i,1,n){
			if(i<=st)printf("%lld ",i-x);//前缀减
			else printf("%d ",i);}
	}exit(0);} 
I main(){n=in();
	fo(i,1,n)a[i]=in(),s+=a[i]*i;
	fo(i,1,n)pv[i]=pv[i-1]+a[i];
	fo(i,1,n)sf[n-i+1]=sf[n-i+2]+a[n-i+1];
	if(s==0)ad(1,0,0);
	if(s>0){I fpv=0,fsf=0;//找符合条件的前缀和后缀
		fo(i,1,n){if(pv[i]==1)fpv=i;
		if(sf[i]==-1)fsf=i;}
		if(!fpv&&!fsf)return puts("No"),0;
		if(fpv)ad(fpv,s,0);
		if(fsf)ad(fsf,s,1);} 
	if(s<0){I fpv=0,fsf=0;
		fo(i,1,n){if(pv[i]==-1)fpv=i;
		if(sf[i]==1)fsf=i;}
		if(!fpv&&!fsf)return puts("No"),0;
		if(fpv)ad(fpv,-s,0);
		if(fsf)ad(fsf,-s,1);}
	return 0;
}

```



---

