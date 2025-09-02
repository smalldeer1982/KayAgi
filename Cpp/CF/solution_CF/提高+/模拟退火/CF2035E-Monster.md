# Monster

## 题目描述

这个原神 Boss 太难打了。幸好他们有 $6$ 个金币只需 $4.99$ 美元的充值包。我得小心点，花的钱不能太多，不然我妈会发现……

你正在用一把伤害为 $d$ 的武器与一个生命值为 $z$ 的怪物战斗。初始时，$d=0$。你可以进行以下两种操作：

- 将武器的伤害 $d$ 增加 $1$，花费 $x$ 个金币。
- 攻击怪物，造成 $d$ 点伤害，花费 $y$ 个金币。

你不能连续进行第一种操作超过 $k$ 次。

请你计算，至少需要多少金币才能通过造成至少 $z$ 点伤害击败怪物。

## 说明/提示

在第一个测试用例中，$x=2$，$y=3$，$z=5$，$k=5$。以下是一种能达到最低花费 $12$ 金币的策略：

- 将伤害提升 $1$，花费 $2$ 金币。
- 将伤害提升 $1$，花费 $2$ 金币。
- 将伤害提升 $1$，花费 $2$ 金币。
- 攻击怪物，造成 $3$ 点伤害，花费 $3$ 金币。
- 再次攻击怪物，造成 $3$ 点伤害，花费 $3$ 金币。

你总共造成了 $3+3=6$ 点伤害，击败了生命值为 $5$ 的怪物。总共花费了 $2+2+2+3+3=12$ 金币。

在第二个测试用例中，$x=10$，$y=20$，$z=40$，$k=5$。以下是一种能达到最低花费 $190$ 金币的策略：

- 将伤害提升 $5$，花费 $5\cdot x=50$ 金币。
- 攻击怪物一次，造成 $5$ 点伤害，花费 $20$ 金币。
- 将伤害提升 $2$，花费 $2\cdot x=20$ 金币。
- 攻击怪物 $5$ 次，每次造成 $7$ 点伤害，共造成 $5\cdot 7=35$ 点伤害，花费 $5\cdot y=100$ 金币。

你总共造成了 $5+35=40$ 点伤害，刚好击败生命值为 $40$ 的怪物。总共花费了 $50+20+20+100=190$ 金币。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2 3 5 5
10 20 40 5
1 60 100 10
60 1 100 10```

### 输出

```
12
190
280
160```

# 题解

## 作者：MatrixGroup (赞：9)

## 前言 / Foreword

非常好题目。非常好题目背景。

Great problem, great quote.

## 扽西 / Analysis

先考虑最优解长什么样子。如果先攻击再增加，并且可以把增加放到攻击前面，那么造成的伤害可以变多 $1$。因此，一定要尽可能先增加再攻击。故而最优解一定形如，重复 $r(r\ge 0)$ 次“增加 $k$ 次，攻击 $1$ 次”，再增加 $a(1\le a\le k)$ 次，攻击 $b(b\ge 1)$ 次。这样花费了 $rkx+ry+ax+by$ 枚金币，造成了 $\dfrac{r(r+1)}{2}k+(rk+a)b$ 的伤害。

Consider what form the optimal solution can be in. If one firstly attacks the monster then increases $d$, the damage dealt is $1$ less than that if one firstly increases $d$ then attakcs the monster. Therefore, in the optimal solution, the increments must be before attacks as much as possible, which means the optimal solution must be in the following form: repeat "increase $d$ for $k$ times, and attack once" for $r(r\ge 0)$ times, then increase $d$ for $a(1\le a\le k)$ times, then attack $b(b\ge 1)$ times. In this way, damage of  $\dfrac{r(r+1)}{2}k+(rk+a)b$ is dealt by costing $rkx+ry+ax+by$ coins.

$t\le 100,x,y,z,k\le 10^8$，一看就很像根号分治的样子。考虑设立阈值 $B$：

$t\le 100,x,y,z,k\le 10^8$, which is super sqrt-balancing-ish. Consider a threshold $B$:

若 $k\le B$，因为 $k$ 很小，$a$ 的范围为 $1\sim k$ 也很小，可以直接考虑枚举 $a,r$，计算出最小的 $b$ 更新答案。因为一旦 $\dfrac{r(r+1)}{2}k\ge z$ 就可以不用再枚举了，$r$ 的范围是 $O\left(\sqrt{\dfrac zk}\right)$ 的，因此这时的复杂度是 $O(\sqrt {zk})$。

When $k\le B$, since $k$ is small, and the range of $a$ is $1$ to $k$, one can enumerate $a,r$, then calculate the least possible $b$ to update the answer. When $\dfrac{r(r+1)}{2}k$ already reaches $z$, there's no need to continue the enumeration anymore, so $r$ is in a range of $O\left(\sqrt{\dfrac zk}\right)$, which implies a complexity of $O(\sqrt{zk})$.

若 $k\ge B$，此时 $\dfrac{z}{k}$ 很小。此时枚举 $r$，枚举 $b$ 的范围是 $O\left(\dfrac{z}{rk}\right)$ 的，再计算最小的 $a$ 即可。因为调和级数，这部分的复杂度是 $O\left(\dfrac{z}{k}\log z\right)$ 的。$r=0$ 时需要特殊用数论分块处理，因此总复杂度 $O\left(\dfrac{z}{k}\log z+\sqrt z\right)$。

When $k\ge B$, $\dfrac{z}{k}$ is small. Therefore, $b$ is in a range of $O\left(\dfrac{z}{rk}\right)$. By enumerating $r$ and $b$, one can determine the least possible $a$ and then update the answer. Thanks to the harmonic series, The complexity is $O\left(\dfrac{z}{k}\log z\right)$. However, when $r=0$, one needs to use the trick of "$O(\sqrt z)$ different values for $\left\lceil \dfrac zb\right\rceil$" to enumerate $b$ in a clever way. The total complexity is $O\left(\dfrac{z}{k}\log z+\sqrt z\right)$.

取 $B=O(z^{1/3}\log^{2/3}z)$，每组数据的时间复杂度是 $O(z^{2/3}\log^{1/3}z)$，可以通过。

Take $B=O(z^{1/3}\log^{2/3}z)$, the time complexity per test is $O(z^{2/3}\log^{1/3}z)$, which can pass the problem easily.

---

## 作者：sbno333 (赞：6)

考虑贪心。

先连续 $k$ 此升级，然后打一下，重复，最后升级若干次，然后狂打。

我们考虑枚举几轮 $k$ 升级，然后再枚举最后再升几级。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline void _main(){
	int x,y,z,k;
	cin>>x>>y>>z>>k;
	int sum;
	sum=1e16;
		for(int i=0;z>=(1+i)*i*k/2;i++){
			int ss;
			ss=z-(1+i)*i*k/2;
			for(int j=max(i*k,1ll);j<i*k+k;j++){
				sum=min((ss+j-1)/j*y+j*x+i*y,sum);//上取整不用小数类型的技巧
			}
		}
	
	cout<<sum<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

此时复杂度 $O(\sqrt{zk})$。

发现内部循环瓶颈是 $\div j$。

考虑整数分块，这里是上取整。

然后时间复杂度 $O(\sqrt z+\sqrt k)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline void _main(){
	int x,y,z,k;
	cin>>x>>y>>z>>k;
	int sum;
	sum=1e16;
		for(int i=0;z>=(1+i)*i*k/2;i++){
			int ss;
			ss=z-(1+i)*i*k/2;int r;
			for(int j=max(i*k,1ll);j<i*k+k;j=r+1){
			if(ss/j==0){
				sum=min(sum,(ss+j-1)/j*y+j*x+i*y);
				break;
			}
				r=(ss+j-1)/((ss+j-1)/j);
				sum=min((ss+j-1)/j*y+j*x+i*y,sum);
			}
		}
	
	cout<<sum<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：Milmon (赞：5)

## Statement

初始 $d = 0$，你可以进行任意次如下操作：

- 操作 1：令 $d \gets d + 1$，花费为 $x$；
- 操作 2：造成 $d$ 点伤害，花费为 $y$。

但是不能连续进行多于 $k$ 次操作 1。

给定 $x, y, z, k$，求造成 $z$ 点伤害的最小花费。

数据范围：数据组数 $T \leq 100$，$1 \leq x, y, z, k \leq 10^8$。

## Solution

首先有一个暴力的做法。枚举操作 1 的总次数 $a$。此时最优策略是前 $\lfloor \frac{a}{k} \rfloor$ 次操作 2 在 $a$ 次操作 1 之间进行，操作 1 全部结束之后，再不断进行操作 2 直到总伤害达到 $z$。而 $a$ 次操作 1 之间进行的操作 2 的伤害是一个等差数列，总和容易计算，最后需要操作 2 的次数也容易计算。暴力枚举的时间复杂度是 $O(z)$，无法接受。

设操作 1 和操作 2 的总次数分别为 $a, b$。则固定 $a$ 时可以直接计算出 $b$ 的最小值。那么固定 $b$ 时能否确定 $a$ 的最小值呢？答案是肯定的，由于 $a$ 越大，总伤害就越大，所以可以使用二分算法在 $O(\log z)$ 的时间复杂度内计算 $a$ 的最小值。

注意到单次造成的伤害形成等差数列，伤害平均值约为 $\frac{a}{2}$，总伤害约为 $\frac{ab}{2}$。二分出一个最小的 $x$ 满足 $x \geq$ 当 $a = x$ 时 $b$ 的最小值，那么 $x$ 将不超过 $O(\sqrt z)$ 量级。当 $a \leq x$ 时固定 $a$ 计算最小的 $b$，当 $a > x$ 时 $b \leq x$，固定 $b$ 计算最小的 $a$，这样两种情况的时间复杂度均为 $O(x)$ 或者 $O(x \log z)$。总时间复杂度为 $O(\sqrt z \log z)$，可以接受。

## Solution (English)

First, there is a brute-force method. Enumerate the total number of operation 1, denoted as $a$. In this case, the optimal strategy is to perform the first $\lfloor \frac{a}{k} \rfloor$ operations of type 2 between the $a$ operations of type 1. After all operations of type 1 are completed, continue performing operation 2 until the total damage reaches $z$. The damage from the operations of type 2 performed between the $a$ operations of type 1 forms an arithmetic series, and the total sum is easy to calculate. The number of operations of type 2 required is also easy to compute. The time complexity of brute-force enumeration is $O(z)$, which is unacceptable.

Let the total number of operations 1 and 2 be $a$ and $b$, respectively. Then, when $a$ is fixed, we can directly calculate the minimum value of $b$. So, can we determine the minimum value of $a$ when $b$ is fixed? The answer is yes. Since the larger $a$ is, the greater the total damage, we can use a binary search algorithm to compute the minimum value of $a$ in $O(\log z)$ time complexity.

Noticing that the damage caused in a single operation forms an arithmetic series, the average damage is approximately $\frac{a}{2}$, and the total damage is approximately $\frac{ab}{2}$. By performing a binary search, we find a minimum $x$ such that $x \geq$ the minimum value of $b$ when $a = x$. Then, $x$ will not exceed $O(\sqrt z)$ in magnitude. When $a \leq x$, we fix $a$ to calculate the minimum $b$. When $a > x$, we have $b \leq x$, and we fix $b$ to calculate the minimum $a$. Thus, the time complexity for both cases is $O(x)$ or $O(x \log z)$. The total time complexity is $O(\sqrt z \log z)$, which is acceptable.

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int x,y,z,k;

inline ll sum(int p,int q){
    int t=min(p/k,q);
    return 1ll*(1+t)*t/2*k+1ll*(q-t)*p;
}

inline int bestP(int q){
    int l=1,r=z+1;
    while(l<r){
        int mid=(l+r)>>1;
        if(sum(mid,q)>=z)r=mid;
        else l=mid+1;
    }
    return l;
}
inline int bestQ(int p){
    int l=1,r=z+1;
    while(l<r){
        int mid=(l+r)>>1;
        if(sum(p,mid)>=z)r=mid;
        else l=mid+1;
    }
    return l;
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d",&x,&y,&z,&k);
        int l=0,r=z;
        while(l<r){
            int mid=(l+r)>>1;
            if(mid>=bestQ(mid))r=mid;
            else l=mid+1;
        }
        ll answer=1e18;
        for(int i=1;i<=l+1;i++){
            int q=bestQ(i);
            if(sum(i,q)>=z)answer=min(answer,1ll*i*x+1ll*bestQ(i)*y);
        }
        for(int i=1;i<=l+1;i++){
            int p=bestP(i);
            if(sum(p,i)>=z)answer=min(answer,1ll*bestP(i)*x+1ll*i*y);
        }
        printf("%lld\n",answer);
    }
    return 0;
}
```

---

## 作者：xiezheyuan (赞：3)

The English editorial are supplied in this article.

## 简要题意

某游戏中有一个怪物，共 $z$ 点血，你有一把武器，攻击力为 $d$，初始时 $d=0$。你可以进行下面两种操作任意次：

- 花费 $x$ 个金币，令 $d\leftarrow d+1$。
- 花费 $y$ 个金币，令 $z\leftarrow z-1$。

特别地，你不能连续执行 $k$ 次第一种操作。

当 $z\leq 0$ 时通关该游戏。问至少需要多少个金币才能通关本游戏。

$T$ 组数据。$1\leq T\leq 100,1\leq x,y,z,k\leq 10^8$。

## 思路

若 $T=1$，我们不难想到枚举最终的 $d$（显然有 $1\leq d\leq z$），计算出其需要多少个金币 $f(d)$，然后取最小值即可。

现在的问题是如何计算 $f(d)$。考虑到我们一定这样操作：先执行 $k$ 次第一种操作，然后执行第二种操作，重复这两个步骤直至达到 $d$，然后不停执行第二种操作直到 $z\leq 0$。

不妨将 $f(d)$ 分成两部分 $g(d),h(d)$。$g(d)$ 表示将武器强化到 $d$ 花费的金币，$g(d)$ 表示强化后攻击需要花费的金币。那么有：

$$
\begin{aligned}
&g(d)=dx+y\left\lfloor\frac{d}{k}\right\rfloor\\
&h(d)=y\left\lceil\frac{z-\frac{1}{2}\cdot\left\lfloor\frac{d}{k}\right\rfloor(\left\lfloor\frac{d}{k}\right\rfloor k+k)}{d}\right\rceil
\end{aligned}
$$

其中 $\frac{1}{2}\cdot\left\lfloor\frac{d}{k}\right\rfloor(\left\lfloor\frac{d}{k}\right\rfloor k+k)$ 是等差数列求和，因为我们执行 $k$ 次第一种操作后必须执行一个第二种操作，而每次第二种操作的 $d$ 一定形如 $k,2k,3k,\cdots,\left\lfloor\frac{d}{k}\right\rfloor k$。

然后就有 $f(d)=g(d)+h(d)$ 啦！

回到 $T=100$ 的本题，我们需要快速求出 $\min f(d)$，而这个 $f$ 函数没有什么良好的性质，可以考虑模拟退火，不需要复杂的调参即可在 1 秒内通过本题。

## Editorial (en)

If $T=1$, it is trivial that we can enumerate the final damage $d$, calculate how many coins we need, $f(d)$, then we output the minimum value of it.

The problem now is how to calculate $f(d)$. First, we are supposed to perform operations in this manner: perform the first operation $k$ times, and then perform the second operation. Repeat this until the damage reaches $d$, and then continue applying the second operation for serval times until $z\leq 0$.

It is useful to break $f(d)$ into two parts $g(d),h(d)$ while $g(d)$ represents the coins we need to let the damage equals to $d$ and $h(d)$ represents the coins we need to let $z\leq 0$ after the damage equals to $d$.

We can now deduce the following:

$$
\begin{aligned}
&g(d)=dx+y\left\lfloor\frac{d}{k}\right\rfloor\\
&h(d)=y\left\lceil\frac{z-\frac{1}{2}\cdot\left\lfloor\frac{d}{k}\right\rfloor(\left\lfloor\frac{d}{k}\right\rfloor k+k)}{d}\right\rceil
\end{aligned}
$$

Note that $\frac{1}{2}\cdot\left\lfloor\frac{d}{k}\right\rfloor(\left\lfloor\frac{d}{k}\right\rfloor k+k)$ is derived from Arithmetic Series Summation Formula.

So far, we have already solved the case where $T=1$ in $O(z)$. Now we need to solve the case where $T=100$.

In this case, we CANNOT enumerate $z$, and the function $f(z)$ doesn't exhibit nice properties.

Therefore, we can apply Simulated Annealing Algorithm, which turns out to be quite effective for this problem.

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

using i64 = long long;
i64 x, y, z, k;

i64 ceildiv(i64 a, i64 b){ return (a + b - 1) / b; }

i64 f(i64 d){
    i64 upd = d * x + (d / k) * y;
    i64 rem = max(z - ((d / k) * k + k) * (d / k) / 2, 0ll);
    rem = ceildiv(rem, d) * y;
    return upd + rem;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> urd(1, -1);
i64 ans;

inline void SA(){
    double T = z;
    i64 nowx = rnd() % z + 1;
    while(T > 1e-7){
        i64 newx = min(max(nowx + (i64)(T * urd(rnd)), 1ll), z);
        i64 delta = f(newx) - f(nowx);
        if(delta <= 0) nowx = newx;
        else if(exp(-delta / T) > fabs(urd(rnd))) nowx = newx;
        T *= 0.99;
    }
    for(int i=-20;i<=20;i++){
        if((nowx + i) >= 1 && (nowx + i) <= z) ans = min(ans, f(nowx + i));
    }
}

void solve(){
    cin >> x >> y >> z >> k;
    ans = LLONG_MAX;
    for(int i=1;i<=30;i++) SA();
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：xiaruize (赞：3)

~~csp 心态崩了，遂在后一天的 codeforces 中写了个瞎搞，结果一不小心过了。~~

考虑如果已经确定最终要到达的伤害，一定优先用增加伤害操作，可以 $\mathcal{O}(1)$ 的计算出代价。

观察数据范围，发现 $t\leq 100,x,y,z,k\leq 10^8$，导致对于每一组数据，大约可以做 $10^6$ 次计算。

也就是说，只要这 $10^6$ 次中有正确的最终伤害即可。所以，实际上我们希望找到一个答案可能存在的区间。

你可能觉得这个函数单峰，但是实际上不是的，所以三分是错误的。因为这个函数可能具有很多山峰，启发我们用模拟退火。

做 $10$ 次退火，每次在找到一个山峰后，从这个山峰向左右各波动 $10^4$ 个点，即可通过。

注意一下几点：

- 退火的起始位置要随机，不然大概率会停在同一个山峰。
- 可以把错误的三分加上，因为在宏观上这个函数确实先增后减，所以三分在一般数据下任然可以返回一个较为精确的结果。
- 要适当调参，防止 TLE。

具体见代码实现

```cpp
const int INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;
const int N = 2e5 + 10;
 
int rnd()
{
    return rand() % 2;
}
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> unif(0, 1);
int x, y, z, k;
 
int calc(int t)
{
    int p = t / k;
    int cst = x * t + y * p;
    int dpre = (k + p * k) * p / 2;
    return cst + (max(0ll, z - dpre) + t - 1) / t * y;
}
 
void solve()
{
    srand(time(0));
    cin >> x >> y >> z >> k;
    int ans = INF;
    {
        int l = 1, r = z;
        while (l + 2 < r)
        {
            int lmid = (l + l + r) / 3, rmid = (l + r + r) / 3;
            if (calc(lmid) <= calc(rmid))
                r = rmid;
            else
                l = lmid;
        }
        int res = INF;
        rep(i, max(1ll, l - 100000), min(z, l + 100000)) chkmi(res, calc(i));
        chkmi(ans, res);
    }
    int tim = 10;
    while (tim--)
    {
        double t = 1e8;
        int l = rand() % z + 1;
        while (t >= 1)
        {
            int x = l + t * (rnd() * 2 - 1);
            x = max(1ll, min(z, x));
            int del = calc(x) - calc(l);
            if ((double)-del / t > unif(rng))
                l = x;
            t *= 0.98;
        }
        int res = INF;
        rep(i, max(1ll, l - 10000), min(z, l + 10000)) chkmi(res, calc(i));
        chkmi(ans, res);
    }
    cout << ans << endl;
}
```

---

## 作者：Shunpower (赞：2)

这是一篇使用爬山的题解。

This is a solution using the Hill-Climbing algorithm.

---------------------

考虑先写出答案的式子。

Consider representing the answer as an expression first.

容易想到枚举最终武器的攻击力 $d$。此时贪心地发现，假设不存在每 $k$ 次增加就需要攻击的限制，那么我们一定是先增加完再攻击，因为如果把增加放在后面，那么交换顺序就可以使攻击造成的伤害更大，并且花费相等。

It is easy to think of enumerating the final weapon's damage $d$. And we can realise that greedily, assuming there is no restriction on the need to attack every $k$ increase, we must finish increasing before attacking, because if we put the increase after it, just swapping the order allows the attacks to do more damage and cost equally.

即便存在每 $k$ 次就需要攻击的限制，这个想法显然也是正确的，只不过是多了一些强制攻击造成的影响。

Even if there exists a restriction of needing to attack every $k$ times, the idea is clearly correct and can hold on, considering the effects caused by the forced attacks every $k$ times.

显然，我们需要增加攻击力 $d$ 次，产生 $dx$ 的花费。这 $d$ 次增加又会发起强制攻击 $\left\lfloor\frac{d}{k}\right\rfloor$ 次，产生 $\left\lfloor\frac{d}{k}\right\rfloor y$ 的花费，应用等差数列求和可以发现这部分攻击会造成 $r=k+2k+\cdots \left\lfloor\frac{d}{k}\right\rfloor k=\frac{(\left\lfloor\frac{d}{k}\right\rfloor k+k)\left\lfloor\frac{d}{k}\right\rfloor }{2}$ 的伤害，而剩下的 $z-r$ 的部分还需要 $\left\lceil\frac{z-r}{d}\right\rceil$ 次攻击，产生 $\left\lceil\frac{z-r}{d}\right\rceil y$ 的花费。

Obviously, we need to increase the damage of the weapon $d$ times, causing $dx$ cost. This $d$ times increase will lead to the forced attack $\left\lfloor\frac{d}{k}\right\rfloor$ times, causing $\left\lfloor\frac{d}{k}\right\rfloor y$ cost. By calculating the sum of Arithmetic Progression we can realise this portion of attack causes damage $r=k+2k+\cdots \left\lfloor\frac{d}{k}\right\rfloor k=\frac{(\left\lfloor\frac{d}{k}\right\rfloor k+k)\left\lfloor\frac{d}{k}\right\rfloor }{2} $, and the remaining $z-r$ portion also requires $\left\lceil\frac{z-r}{d}\right\rceil$ times, causing $\left\lceil\frac{z-r}{d}\right\rceil y$ cost.

所以，每个 $d$ 对应的最小花费，也就是答案可以用一个公式直接写出：

Therefore, the minimum cost corresponding to each $d$, i.e., the answer, can be expressed directly in a formula:

$$
ans=dx+\left\lfloor\frac{d}{k}\right\rfloor y+\left\lceil\frac{z-\frac{(\left\lfloor\frac{d}{k}\right\rfloor k+k)\left\lfloor\frac{d}{k}\right\rfloor }{2}}{d}\right\rceil\cdot y
$$

我们可以使用一个函数 $f(d)$ 表示 $d$ 对应的答案。那么实际上我们的任务就是计算 $\min\limits_{d=1}^z f(d)$。（$d$ 的上界显然是 $z$）。

We can use a function $f(d)$ to represent the answer corresponding to $d$. Then in fact, our task is to calculate $\min\limits_{d=1}^z f(d)$. (The upper bound on $d$ is obviously $z$).

我们可以注意到，$f(d)$ **大约**是一个单谷函数，这让我们想到尝试随机化算法。

We can notice that $f(d)$ **approximately** is a single-valley function, which makes us think of trying a randomisation algorithm.

考虑直接爬山或者模拟退火。不妨初始时设置答案位于 $d=\frac{z}{2}$ 处，设置温度 $T$ 为 $z$，每次直接将 $d$ 随机向两侧移动随机小于等于 $T$ 的长度，如果可以得到更优秀的 $f(d)$ 则接纳并将答案挪动过去。显然，当 $T<1$ 时将无法产生有效移动，所以设置阈值为 $eps=1$。设置降温系数 $t=0.9999$ 表现较好。

Consider directly applying Hill-Climbing or Simulated Annealing algorithm. It is better to initially set the answer to be located at $d=\frac{z}{2}$, and set the temperature $T$ to $z$. Each time, we directly move $d$ randomly to either side by a length randomly less than or equal to $T$, and then accept and move the $d$ over if a better $f(d)$ can be obtained. Obviously, when $T<1$ no effective move will be produced, so set the threshold to $eps=1$. 

Setting the cooling factor $t=0.9999$ performs fine.

为了让解的质量更好，我们可以一边做一边将答案取 $\min$。最后还可以暴力计算解的左右 $10^5$ 位的答案，避免微小的偏差。

To make the quality of the solution better, we can take $\min$ of the answer while moving $d$. Finally we can also calculate the answer in the left and right $10^5$ of the solution brutally to avoid small deviations.

不知道为啥我写的模拟退火在这题里面表现不如爬山。

I haven't known why my Simulated Annealing algorithm does not perform as well as Hill-Climbing within this problem.

-------------------

下面的代码可以在 $1.4$ 秒的时间通过本题。

The following code will pass the problem in $1.4$ seconds.

```cpp
int tc;
ll x,y,z,k;
ll calc(ll d){
    return d*x+(d/k)*y+(z-(d/k*k+k)*(d/k)/2+(d-1))/d*y;
}
double rd(){
    return (double)rand()/RAND_MAX;
}
void solve(){
    cin>>x>>y>>z>>k;
    ll ans=1e18;
    ll L=1,R=z;
    int x=max(1ll,z/2);
    double T=z,eps=1,t=0.9999;
    while(T>=eps){
        ll del=T*(rd()*2-1);
        ll nx=x+del;
        nx=min(nx,R);
        nx=max(nx,L);
        ans=min(ans,calc(x));
        double delta=calc(nx)-calc(x);
        if(delta<0) x=nx;
       // else if(rd()<=exp(-delta/calc(max(1.0,T)))) x=nx;
        T*=t;
    }
    fr1(i,max(1,x-100000),x+100000) ans=min(ans,calc(i));
    cout<<ans<<'\n';
}
```

---

## 作者：吾爱CC (赞：1)

来一个没有 log 的题解

如果说最后 $d=a$ 那么显然把 $a$ 次操作放最前面是更优的。

考虑一种枚举 $d$ 的朴素暴力，设之前由于 $K$ 的限制可能执行过操作二。设当前怪物血量为 $z$，之前的二操作开销为 $w$。那么此时的代价为 $dx+\lceil \frac{z}{d} \rceil y+w $。

考虑怎么优化，由于我们想让 $d$ 继续增加，如果要让代价变小，那么至少需要 $\lceil \frac{z}{d} \rceil$ 变小。那么考虑整除分块，找到 $d$ 所在的块的结尾 $r$ 满足 $\lceil \frac{z}{d} \rceil=\lceil \frac{z}{r} \rceil$，且 $r$ 最大。那么下次增大 $d$ 为 $r+1$，然后更新血量和开销 $w$。

考虑整除分块复杂度即可。
对于 $d\gt \sqrt z$，此时 $\lceil \frac{z}{d} \rceil\le \sqrt z$，每次变化都会使得 $\lceil \frac{z}{d} \rceil$ 减少 $1$。所以总复杂度为 $O(t\sqrt z)$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read(){
    char ch=getchar();
    while(!isdigit(ch) && ch!='-') ch=getchar();
    int x=0,ff=1; if(ch=='-') ff=-1,ch=getchar();
    while(isdigit(ch)) x=(x<<3) + (x<<1) + (ch^48),ch=getchar();
    return x*ff;
}
const LL inf=1e18;
int a,b,c,K;
void vmain(){
    a=read(); b=read(); c=read(); K=read();
    LL ans=inf,ww=0;
    for(int d=1;d<=c;){
        int ct=(c+d-1)/d; ans=min(ans,1ll*d*a+ww+1ll*ct*b); if(ct==1) break;
        int r=(c-1)/(ct-1);
        int l1=(d+K-1)/K,r1=(r+1+K-1)/K;
        if(l1!=r1){
            ww+=1ll*(r1-l1)*b;
            c-=1ll*(l1+r1-1)*(r1-l1)/2*K;
        }
        d=r+1;
    } printf("%lld\n",ans);
}
int main(){
    int T=read(); while(T--) vmain();
    return 0;
}
```

---

## 作者：六楼溜刘 (赞：1)

# CF2035E Monster

[传送门](https://www.luogu.com.cn/problem/CF2035E)

## 题意

- 有一把武器，初始攻击力为 $0$，还有一个怪物，血量为 $z$。
- 你可以进行以下两个操作若干次：
    - 花费 $x$ 金币，将武器攻击力加 $1$。
    - 花费 $y$ 金币，攻击一次，将怪物血量减去攻击力。
- 你最多连续进行 $1$ 操作 $k$ 次。
- 问将怪物杀死（血量小于等于 $0$）最少需要多少金币。
- $1\le x,y,z,k\le 10^8$，多测，$1\le t\le 100$

## 题解

考虑进行 $i$ 次操作 $1$，$j$ 次操作 $2$ 最多能打多少血量，显然就是先 $k$ 次操作 $1$ 一次操作 $2$ 重复到操作 $1$ 用完，然后用完剩下的操作 $2$，则答案为 $f(i,j)=k\times \frac{p(p+1)}{2}+i(j-p)$，其中 $p=\min(\left\lfloor\frac{i}{k}\right\rfloor,j)$。

不难发现 $f(i,j)$ 大约是 $i\times j$ 级别的，更准确地说，$f(i,j)\ge \frac{ij}{2}$，在 $j=\left\lfloor\frac{i}{k}\right\rfloor$ 时可以取等，因为此时整个贡献就是一个等差数列求和。否则后面的贡献 $i(j-p)$ 显然会更大。

那么显然地，$\min(i,j)$ 不会超过 $\sqrt{2z}$，否则 $\frac{ij}{2}$ 就已经超过 $z$ 了，于是我们枚举其中一个，二分另一个即可，复杂度 $O(t\sqrt{z}\log z)$。

## code

```cpp
#include<bits/stdc++.h>
#define forup(i,s,e) for(i64 i=(s),E123123123=(e);i<=E123123123;++i)
#define fordown(i,s,e) for(i64 i=(s),E123123123=(e);i>=E123123123;--i)
#define mem(a,b) memset(a,b,sizeof(a))
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void();
#endif
using namespace std;
using i64=long long;
using pii=pair<i64,i64>;
#define fi first
#define se second
#define mkp make_pair
#define gc getchar()
i64 read(){
    i64 x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const i64 N=2e5+5,inf=1e18;
i64 x,y,z,k;
i64 calc(i64 i,i64 j){
    i64 p=min(i/k,j);
    i64 res=k*(p*(p+1)/2)+i*(j-p);
    return res;
}
void solve(){
    x=read();y=read();z=read();k=read();
    i64 p=2*(sqrt(z)+5);
    i64 ans=inf;
    forup(i,1,p){
        i64 ll=1,rr=(i/k)+((z+i-1)/i),mm;
        while(ll<rr){
            mm=(ll+rr)>>1;
            if(calc(i,mm)<z) ll=mm+1;
            else rr=mm;
        }
        ans=min(ans,i*x+ll*y);
    }
    forup(i,1,p){
        i64 p=i*k;
        if(calc(p,i)<z) continue;
        i64 ll=1,rr=p,mm;
        while(ll<rr){
            mm=(ll+rr)>>1;
            if(calc(mm,i)<z) ll=mm+1;
            else rr=mm;
        }
        ans=min(ans,ll*x+i*y);
    }
    printf("%lld\n",ans);
}
signed main(){
    i64 t=read();
    while(t--){
        solve();
    }
}
```

---

## 作者：gcx114514 (赞：0)

看题后有两个暴力的想法：

1. 枚举一共进攻几次。
2. 枚举攻击力增加了几次。

但是对于第一种情况是不好考虑 $k$ 这个限制的，于是选择第二种想法。

既然已经知道最后的攻击力了，那么在增加的过程中肯定是先增加 $k$ 次，然后攻击一次，最后攻击若干次。

那么我们设一共增加了 $j$ 次，满足 $j=i\times k+b$ 其中 $i$ 就是增加过程中攻击的次数。

那么有如下代价：
$$
jx+iy+\left\lceil \frac{z-\frac{(1+i)ik}{2}}{j}\right\rceil y
$$
那么我们暴力枚举 $i,j$ 计算答案。发现当 $(1+i)ik>z$  时已经没意义了，所以 $i\leq \sqrt{\frac{z}k}$ 的，由于 $i$ 已经固定，那么 $j$ 一共只有 $k$ 中取值，所以暴力的复杂度是 $O(T\sqrt {zk})$ 的。

考虑优化。

发现对于后面的 $\left\lceil \frac{z-\frac{(1+i)ik}{2}}{j}\right\rceil$ 中分子是定值，那么可以直接数论分块做到 $O(\sqrt k)$ 。虽然前面也处在一项 $jx$ 是含有系数 $j$，但是我们最后求最小值只需要关心最小的 $j$ 就行。

这样我们的复杂度变成了 $O(T\sqrt z)$ 的，可以通过。

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define int long long
#define mk make_pair
#define se second
#define fi first
//#define mid ((l+r)>>1)
//#define rs now<<1|1
//#define ls now<<1
using namespace std;
bool Mst;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e18+10;

inline int read(){
   int res=0,v=1;
   char c=getchar();
   while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
   while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
   return res*v;
}

int ans=0;

int x,y,z,k;

mt19937 rnd(time(NULL));

void work(){
    x=read();y=read();z=read();k=read();
    ans=inf;
    for(int i=0;(1+i)*i*k/2<=z;++i){
        int v=z-(1+i)*i*k/2;
        int r=0;
        for(int j=max(i*k,1ll);j<(i+1)*k;j=r+1){
            if(v/j==0){
                ans=min(ans,(v+j-1)/j*y+i*y+j*x);
                break;
            }else{
                r=(v+j-1)/((v+j-1)/j);
                ans=min(ans,(v+j-1)/j*y+i*y+j*x);
            }
        }
    }
    cout << ans << "\n";
}


bool Med;
signed main(){
    srand(time(NULL));
    int T=read();while(T--)work();

    cerr<< "Time: "<<clock()/1000.0 << "s\n";
    cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
    return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

首先考虑我们的操作序列长什么样子是最优的，如果没有 $k$ 的限制，那么一定是先全部加攻击，然后一直攻击。否则可以把加攻击全部移到攻击前面，总花费不变但是伤害变高。

发现有 $k$ 限制的情况是类似的，具体地，一定是重复“加 $k$ 次攻击，攻击”若干次，然后再加不超过 $k$ 次攻击，最后一直攻击直到击杀。

先考虑 $O(z)$ 的 naive 做法，来枚举加攻击的次数 $d$，记中途为了满足 $k$ 的限制而攻击的次数为 $g(d)$，造成伤害为 $f(d)$，则有：

$$
\begin{aligned}
g(d)&=\lfloor\frac {d-1}k\rfloor\\
f(d)&=k\times \frac{g(d)(g(d)+1)}{2}\\
cost&=y\lceil\frac{z-f(d)}{d}\rceil+xd+y\times g(d)
\end{aligned}
$$

看上去 $g(d)$ 会变化 $\frac{z}{k}$ 次，但实际上并没有这么多，因为 $f(d)$ 需要小于 $z$，所以 $g(d)$ 只有 $sqrt(z)$ 个取值，然后直觉告诉我们 $\lceil\frac{z-f(d)}{d}\rceil$ 的变化次数并不多，那么在 $\lceil\frac{z-f(d)}{d}\rceil$ 和 $g(d)$ 都不变的情况下，$xd$ 越小越优，所以有贡献的地方只有造成变化的 $d$。

为了防止一些诡异细节，我在代码中进行了扰动，也就是算了 $d-1,d,d+1$ 的答案。

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int T,x,y,z,k;

inline int g(int d){return d?(d-1)/k:0;}
inline int f(int d){return k*g(d)*(g(d)+1)/2;}
inline int Up(int x,int y){return (x+y-1)/y;}// x/y 上取整 
inline int Calc(int d){
	if(d==0) return 1e18;
	return Up(z-f(d),d)*y+x*d+y*g(d);
}
inline int calc(int d){
	return min(min(Calc(d-1),Calc(d)),Calc(d+1));
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>x>>y>>z>>k;int now=1,ans=1e18;
		while(f(now)<z&&z-f(now)>=now){
			ans=min(ans,calc(now));
			//g(d) 的分界点
			int to1=((now-1)/k+1)*k+1;
			//Up(z-f(d),d) 的分界点
			int to2=(z-f(now))/((z-f(now))/now)+1;
			now=min(to1,to2);
		}
		cout<<min(ans,calc(now))<<'\n';
	}
	return 0;
}
```

---

## 作者：mango2011 (赞：0)

来一发~~非常无脑的~~正经做法。

首先，看到这个题目，我们发现如果没有 $k$ 的限制的话这题就非常简单。因此，这启发我们在发起“总攻”之前一定是$t_1(t_1\ge0)$ 次下面的循环：

进行 $k$ 次加强，进行 $1$ 次攻击；进行 $k$ 次加强，进行 $1$ 次攻击；进行 $k$ 次加强，进行 $1$ 次攻击，如此不停进行。

一次“总攻”就是先继续进行 $t_2(1\le t_2\le k)$ 次操作，然后用当前的攻击力去打击怪物。

具体而言，我们进行 $t_1(t_1\ge0)$ 轮循环，“总攻”之前进行 $t_2(1\le t_2\le k)$ 次加强所需要的总的能量是：

$$t_1kx+t_2x+t_1y+\lceil\frac{z-\frac{t_1(t_1+1)k}{2}}{t_1k+t_2}\rceil y$$

其中 $z\ge \frac{t_1(t_1+1)k}{2}$。

观察上面计算贡献的式子，我们会发现：

第一种暴力：其实 $t_1$ 是 $O(\sqrt\frac{z}{k})=O(\frac{\sqrt{z}}{\sqrt{k}})$ 的，而单组暴力需要进行 $k$ 次运算，于是这种暴力的复杂度就是 $O(\sqrt{zk})$ 的。

第二种暴力：用整除分块处理掉 $t_1=0$ 的情况；我们可以枚举 $\lceil\frac{z-\frac{t_1(t_1+1)k}{2}}{t_1k+t_2}\rceil$，$O(1)$ 算出最小的 $t_2$，更新答案；这样子第 $i$ 组期望进行 $O(\frac{z}{ik})$ 轮，理论最坏的总复杂度是 $O(\frac{z}{k}\log z+\sqrt{z})$（可以结合一下调和级数）。

于是我们可以取一个 $B$，当 $k\le B$ 时用第一类暴力处理；$k\ge B$ 时可以用第二类处理。

事实上，上面的两种暴力综合起来就已经足够优秀了，笔者取一个 $B=10^4$ 已经可以稳稳通过。

[考场代码](https://codeforces.com/contest/2035/submission/288365521)

---

