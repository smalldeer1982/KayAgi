# 『STA - R7』Divide and Merge Game

## 题目描述

给定两个正整数 $n, k(2 \le k \le n)$，Alice 和 Bob 将进行如下游戏：

- Alice 需要给出一个长度为 $k$ 的**正整数**序列 $a$，满足 $\sum\limits_{i = 1}^{k} a_i = n$。

- Bob 需要尝试给出一个不小于 $2$ 的正整数 $m$，满足可以将 Alice 给出的正整数序列 $a$ 划分为 $m$ 个**非空可重**集合，且其元素之和均相同。若 Bob 可以给出一个符合条件的正整数则 Bob 胜利，反之 Alice 胜利。

在两人均采取最优策略的情况下，问谁可以获胜。你需要回答 $T$ 次询问。

## 说明/提示

**【样例解释】**

对于第一组测试数据，Alice 只能给出正整数序列 $\left\{1,1,1,1\right\}$，那么此时 Bob 给出 $m = 4$，并将这个正整数序列划分为 $\left\{\left\{1\right\},\left\{1\right\},\left\{1\right\},\left\{1\right\}\right\}$。Bob 也可以给出 $m = 2$，并将正整数序列划分为 $\left\{\left\{1, 1\right\}, \left\{1, 1\right\}\right\}$ 进而得到两个元素之和均为 $2$ 的集合， 同样满足要求。

对于第二组测试数据，Alice 可以给出正整数序列 $\left\{3, 2, 3\right\}$，可以证明此时 Bob 不存在符合要求的划分方案，因此 Alice 胜利。

**【数据范围】**

**本题采用捆绑测试。**

对于 $100\%$ 的数据：

- $1 \le T \le 2 \times 10^5$；
- $2 \le k \le n \le 10^8$。

具体部分分分配如下：

|Subtask 编号|数据范围|分值|
|:--------:|:--------:|:--------:|
|1|$n \le 10$|$16$|
|2|$k^2 \le n$|$27$|
|3|$2 \nmid n$|$27$|
|4|无特殊限制|$30$|


## 样例 #1

### 输入

```
2
4 4
8 3
```

### 输出

```
Bob
Alice```

# 题解

## 作者：_Kenma_ (赞：10)

# P11010 解题报告

## 前言

很好猜的结论题。

这是篇和官解证明思路略有出入的题解。

## 思路分析

~~结论题当然要手玩数据了~~

设 $p$ 表示 $n$ 的最大真因子，即不等于自身的最大因子。特别地，当 $n$ 为质数时，$p=1$。

**结论：Alice 获胜当且仅当 $n-k+1 > p$。**
 
考虑怎样证明。

（注：为方便表述，下述集合 $A$ 等价于 序列 $a$）

### 充分性

即 $n-k+1 > p \Rightarrow $ Alice 获胜。 

考虑构造这样一个集合 $A = \left \{ n-k+1,1,1,…,1  \right \} $。

不难发现，Bob 想要划分的非空集合，其元素之和至大为 $p$。当 $n-k+1 > p$ 时，集合 $A$ 中元素 $n-k+1$ 无法被划分至任何一个集合。

### 必要性

即 $n-k+1 \le p \Rightarrow$  Alice 失败。

考虑构造一种合法的划分方式。设 $p$ 为所划分的集合的元素和。将集合 $A$ 分为 $1$ 和 非 $1$ 元素。不难发现，Bob 获胜当且仅当非 $1$ 元素之和可被划分为 $m$ 个集合，且每个集合的元素和不超过 $\ \lfloor \frac{n}{m} \rfloor$。

弱化条件：限定 Bob 所划分的集合元素和为 $p$。

当 $p=2$ 时，Bob 只需要构造一个和恰好为 $p$ 的集合即可。不妨将集合 $A$ 中极大元素和与所有 $1$ 划分至同一集合。其中，极大元素和定义为不大于 $p$ 的最大可能的元素和。

因为集合 $A$ 中最大的元素不大于 $p$，所以只需要保证极大元素和与所有 $1$ 的和不小于 $p$ 即可。

不难发现，极大元素和是一个 01 背包问题，这启发我们打表验证（在 IOI 赛制中，其实可以交一发来验证）。

打表验证可知，当 $p=2$ 时，在题目限定的数据范围内，结论成立。

然后改变弱化条件：限定 Bob 所划分的集合元素和为 $\frac{n}{p}$。

当 $p = 3$ 时，构造如下：将非 $1$ 元素升序排序，找到一个位置 $pos$，使得 $\sum_{i=1}^{pos} a_i \le \frac{n}{p},a_{pos} \le \frac{n}{p},\sum_{i=pos+1}^{n} a_i \le \frac{n}{p}$。因为 $n-k+1 \le p$，所以 $pos$ 一定存在。

当 $p >3$ 时，将 $p=3$ 中所构造的集合拆分，结果一定不劣。

## 代码实现

我采用了线性筛 $O(V)$ 预处理 $p$ 和 $O(1)$ 回答询问的实现方式，总体复杂度为 $O(V+T)$。但是可能有点卡空间。

AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
bool not_prime[100000005];
int prime[50000005],maxn[100000005],cnt;
void seive(int n){
	for(int i=2;i<=n;i++){
		if(!not_prime[i]) prime[++cnt]=i,maxn[i]=1;
		for(int j=1;j<=cnt && i*prime[j]<=n;j++){
			not_prime[i*prime[j]]=1;
			maxn[i*prime[j]]=i;
			if(i%prime[j]==0) break;
		}
	}
}
int main(){
	seive(100000000);
	cin>>t;
	while(t--){
		cin>>n>>k;
		if(n-k+1>maxn[n]) cout<<"Alice"<<'\n';
		else cout<<"Bob"<<'\n';
	}
}
```

## 后记

在考场上，证明结论可以采用证明与打表验证结合的做法，可能会有奇效。

祝点赞的各位 $CSP / NOIP$ $rp++$ 。

---

## 作者：kbzcz (赞：7)

纪念第一次场切的 div2 D。

----
### 思路

首先 $m$ 肯定得是 $n$ 的因数，不然不可能分成和相等的段，所以考虑枚举 $m$。$n=k$ 的时候所有的因数都是可以的，进一步，$n>k$ 时，先将所有数都设为 $1$，然后考虑剩下的 $n-k$ 该怎么分。    
感性理解，将 $n-k$ 全部放到一个数上最能让 $\text{Bob}$ 输，因为这样两数之间的差最大,更难让和相等。设和为 $s=\frac{n}{m}$，则当 $s<n-k+1$ 的时候，这个 $m$ 是不合法的，否则一定能找到一种分法使和相等。   


然后就完了。


实现上，正序枚举 $m$，因为 $s$ 单调，所以只用枚举前一半因数，遇到合法的直接结束，注意 $m\le k$。

时间复杂度 $O(T\sqrt{n})$，但是能过。

-----

### 代码



```cpp
bool _Start;
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
Tp il void read(T& x) {
	x=0;bool f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}Ts il void read(T& x,_T&... y) {read(x),read(y...);}
using ll=long long;
ll n,K;
bool _End;
int main() {
	fprintf(stderr,"Memory: %.4lf Mib\n",abs(&_End-&_Start)/1048576.0);
	int T;read(T);
	while(T--) {
		read(n,K);
		if(K==n) {
			puts("Bob");
			continue;
		}
		int bj=0;
		for(int i=2;i*i<=n&&i<=K&&n/i>n-K;i++) {
			if(n%i==0) {
				bj=1;
				break;
			}
		}
		if(bj) puts("Bob");
		else puts("Alice");
	}
	return 0;
}
```

---

## 作者：arrowpoint (赞：6)

首先一个很显然的观察是 $m$ 必须是 $n$ 的一个约数。接着再考虑如果 $m$ 已经给定该如何判断。

显然，此时每一段的和都应是 $\frac{n}{m}$ 才能使 Bob 获胜。假如 Alice 给出的 $k$ 个数中有一个大于 $\frac{n}{m}$，则 Bob 必不可能给出合法划分，此时 Alice 必赢。这种情况的充要条件是 $k \le n - \frac{n}{m}$。

否则，Alice能给出的最大的数都会小于 $\frac{n}{m}$，不难发现这种情况下必定可以给出合法划分，因为设这个最大的数为 $i$，这种情况下若想要无法划分出一段和为 $\frac{n}{m}$ 的区间，就至少要使其它所有数中有一个大于 $1$。但此时我们完全可以把这个数减一，把 $i$ 加一形成更大的数，因此这个数不是最大数，矛盾。因此此时必定可以划分掉一个合法段，变成 $n = n-\frac{n}{m}$，$m = m-1$ 的子情况，可以证明这种子情况也一定能继续划分。这样通过数学归纳法即可证明此时必定有合法划分。

继续观察发现若一个更小的 $m$ 满足 Alice 获胜的条件，则更大的 $m$ 也必然满足。因此我们只需要验证 $n$ 最小的非 $1$ 约数是否满足 Alice 获胜条件即可。

$n$ 的范围是 $10^8$，需要验证的数有 $10^4$ 个，会超时。但是如果我们预处理出 $10^4$ 内的质数进行检验，则时间复杂度只有 $O(\frac{T\sqrt n}{\ln \sqrt n})$，此时限下可以通过此题。

代码如下。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

const int N = 10005;
int n,m,a[N],k;
bitset<200000> bs;
int prime[N],idx;

signed main(){
	ios::sync_with_stdio(false);
	for(int i=2;i<=100000;i++){
		if(!bs[i]) prime[++idx] = i;
		for(int j=1;j<=idx;j++){
			if(i*prime[j]>100000) break;
			bs[i*prime[j]] = 1;
			if(i%prime[j]==0) break; 
		}
	}
	int t;
	cin>>t;
	while(t--){
		cin>>n>>k;
		bool flag = 0;
		for(int i=1;prime[i]*prime[i]<=n;i++){
			if(n%prime[i]==0){
				if(k<=n-n/prime[i]) cout<<"Alice\n";
				else cout<<"Bob\n";
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		if(n==k) cout<<"Bob\n";
		else cout<<"Alice\n";
	}
	
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：5)

比赛结束前最后几分钟过的 T4。

我们发现，Alice 的最优策略显然为：先构造一个长度为 $k$ 的全 $1$ 序列，再找一个地方加上 $n - k$，这样可以尽量让 $1 + (n - k) > \frac{n}{m}$，从而达到胜利的目的。

而 Bob 的最优策略为：最小化 $m$ 的取值，因为这样可以更好的让 $1 + (n - k)$ 和其他 $1$ 组成 $\frac{n}{m}$。

我们分析完最优策略后，观察上面列出的等式 $1 + (n - k) > \frac{n}{m}$，再移个项就可以转化为 $n - \frac{n}{m} \ge k$，此时 Alice 必胜。再根据 Bob 的最优策略，$\frac{n}{m}$ 就是 $n$ 的最大因子（不含 $n$）。

直接 $O(\sqrt{n})$ 枚举质因数是会超时的，那么我们直接上个 Pollard-Rho 分解质因数就做完了。

奉上代码（赛后修整了一下）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int primes[4] = {2, 3, 11, 97};
inline int gcd(int a, int b) {
    int az = __builtin_ctzll(a);
    int bz = __builtin_ctzll(b);
    int z = min(az, bz);
    b >>= bz;
    while (a) {
        a >>= az;
        int diff = a - b;
        az = __builtin_ctzll(diff);
        b = min(a, b), a = abs(diff);
    }
    return b << z;
}
inline int power(int a, int b, int p) {
    int res = 1;
    a %= p;
    while (b) {
        if (b & 1) {
            res = (int)((long long)res * (long long)a % (long long)p);
        }
        a = (int)((long long)a * (long long)a % (long long)p);
        b >>= 1;
    }
    return res;
}
inline bool pr(int n) {
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    if ((n & 1) ^ 1) return 0;
    int d = n - 1;
    int r = 0;
    while ((d & 1) ^ 1) {
        d >>= 1;
        ++r;
    }
    for (int nums : primes) {
        if (nums >= n) break;
        int x = power(nums, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = 0;
        for (int i = 1; i < r; ++i) {
            x = (int)((long long)x * (long long)x % (long long)n);
            if (x == n - 1) {
                ok = 1;
                break;
            }
        }
        if (ok) continue;
        return 0;
    }
    return 1;
}
inline int getfac(int n) {
    if ((n & 1) ^ 1) return 2;
    int x = rand() % (n - 2) + 2;
    int y = x;
    int c = rand() % (n - 1) + 1;
    int d = 1;
    while (d == 1) {
        x = ((int)((long long)x * (long long)x % (long long)n) + c) % n;
        y = ((int)((long long)y * (long long)y % (long long)n) + c) % n;
        y = ((int)((long long)y * (long long)y % (long long)n) + c) % n;
        d = gcd(abs(x - y), n);
    }
    return d == n ? getfac(n) : d;
}
inline int solve(int n) {
    if (pr(n)) return n;
    int factor = getfac(n);
    return max(solve(factor), solve(n / factor));
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        if (1ll * k * k <= 1ll * n) {
            cout << "Alice\n";
            continue;
        }
        if (n % 2 == 0) {
            if (k >= n / 2 + 1) {
                cout << "Bob\n";
            } else {
                cout << "Alice\n";
            }
        } else {
            long long up = 0;
            int ttt = n;
            int mul = 1;
            while (!pr(ttt)) {
                int x = solve(ttt);
                mul *= x;
                ttt /= x;
            }
            up -= mul - n;
            if (k > up)  {
                cout << "Bob\n";
            } else {
                cout << "Alice\n";
            }
        }
    }
    return 0;
}
```

---

## 作者：User_Unauthorized (赞：3)

## SubTask 1

可以暴力枚举所有可能的序列 $a$，在枚举所有可能的划分方案。若存在无法划分为若干个和相同的集合的正整数序列则 Alice 获胜，否则 Bob 获胜。

## SubTask 2

考虑按如下方式构造正整数序列 $a$：首先构造一个 $k$ 个 $1$ 的正整数序列，接下来对 $n - k$ 个位置执行 $+1$ 操作。

记 $p$ 表示最小的，满足 $p \mid n$ 的质数，设 $m = \frac{n}{p}$。那么可以发现若正整数序列 $a$ 中存在元素大于 $m$，那么无论 Bob 如何操作均不可能得到合法的划分方案。因此若 $n - k \ge m$，Alice 一定可以构造出使得其获胜的序列。同时可以发现因为我们有 $p \ge 2$ 和 $k \ge 2$，因此 $k \le \frac{n}{k} \le \frac{n}{2} \le m$。

因此在该子任务的限制下 Alice 必胜。

## SubTask 3

继续按 SubTask 2 的分析，可以发现在该子任务中我们有 $p \ge 3$。因此我们考虑此时 Alice 必胜的充要条件。同时我们可以发现若对于某个 $k_0$ 有 Bob 必胜，这意味着对于所有长度为 $k_0$，和为 $n$ 的正整数序列，其均可以划分为若干个和相同的集合。那么对于所有的 $k > k_0$，Bob 均可以通过 $k - k_0$ 次合并操作进而得到一个 $k_0$ 个正整数的情况。因此对于所有 $k \ge k_0$，均有 Bob 必胜，对于所有 $k < k_0$，均有 Alice 必胜。进而我们只需要找到最小的 $k$ 使得 Bob 必胜。

我们已经知道当 $k = n - m$ 时 Alice 必胜，我们猜测当 $k > n - m$ 时 Bob 必胜，我们下面给出当 $p \ge 3$ 时的证明。适用于所有情况证明详见 SubTask 4。

根据上文的分析，我们只需要考虑 $k = n - m + 1$ 时 Bob 是否必胜，设 $x = m - 1$，可以发现 Alice 初始时会有 $n - x$ 个 $1$，并且其需要进行 $x$ 次 +1 操作，那么其操作后至多存在 $x$ 个非 $1$ 的值，并且他们的值均小于 $m$，且和不超过 $2 \cdot x$。

我们考虑令 Bob 将正整数序列 $a$ 划分为 $p$ 个值为 $\frac{n}{p}$ 的元素，不妨进行如下操作：特殊处理所有非 $1$ 值组成的序列，找到一个极长的前缀使得其和不大于 $m$，那么可以将这个序列划分为三段：该极长前缀，这前缀后的一个元素和剩余的全部元素，可以发现其和均不大于 $m$，剩余的位置使用 $1$ 补齐即可。可以发现我们将所有的非 $1$ 值划分为了 $3$ 个和均不大于 $m$ 的集合，同时又有 $p \ge 3$，因此当 $k > n - m$ 时 Bob 必胜，反之 Alice 必胜。

## SubTask 4

我们考虑继续证明 SubTask 3 的结论。

发现当 $p = 2$ 时我们需要将所有元素划分为恰好两个和为 $m$ 的集合，因此 SubTask 3 中的方法在 $p = 2$ 时无效。

但是我们可以发现，当 $p = 2$ 时，我们只需要划分出一个和为 $m$ 的集合即可。我们考虑将所有非 $1$ 的值按大小降序排列，后依次执行如下操作：

- 若当前已选数的集合之和再加上当前的元素之和不大于 $m$，则选择这个元素。

不难发现所有的非 $1$ 数之和不小于 $m$，因此若上述操作得到的集合元素之和不为 $m$，那么其值一定大于 $m$ 减去最小的非 $1$ 值，因此我们只需要证明 $1$ 的个数不小于最小的非 $1$ 值减去 $1$ 即可。不妨设非 $1$ 值的个数为 $d$，那么最小的非 $1$ 值的最大值为 $\left\lfloor\frac{x + d}{d}\right\rfloor = \left\lfloor\frac{x}{d}\right\rfloor + 1$，而此时 $1$ 的数量为 $x - d + 2$，那么我们要证明：

$$\begin{aligned}
&&\left\lfloor\frac{x}{d}\right\rfloor &\le x - d + 2 \\
\Leftarrow && \frac{x}{d} &\le x - d + 1 \\
\Leftrightarrow && x &\le x \cdot d - d^2 + d \\
\Leftrightarrow && x (1 - d) &\le d(1 - d) \\
\end{aligned}$$

当 $d = 1$ 时上式显然成立，当 $d > 1$ 时我们有：

$$\begin{aligned}
&& x (1 - d) &\le d(1 - d) \\
\Leftrightarrow && x &\ge d
\end{aligned}$$

不难发现其也一定成立，因此命题得证。

不难发现上述分析也适用于 $p \ge 3$ 的情况，因为其仅将所有非 $1$ 值划分到了两个集合中。

综上，当 $k \le n - m$ 时 Alice 必胜，反之 Bob 必胜。

因此只需要快速的找到符合要求的 $p$ 即可，不妨预处理出不大于 $\sqrt{V}$ 的全部素数后枚举判定，其中 $V = 10^8$。

---

## 作者：KXY_Moon (赞：2)

## 解法

结论+分类讨论。

设答案为 $Ans$，那么对于每个 $n$，有：

 - 当 $n=k$，$Ans=$```Bob```。

 - 当 $n>k$ 时：

   - Alice 的最优方案就是将 $n$ 拆分成如下型式：

    $$1,1,1,1,1,...,n-k+1\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,$$
  
     这样使某个子段之和相等更为困难。

   - Bob 的最优方案就是，枚举 $m$，将 $a$ 划分成每个子段之和都为 $sum$ 的数列，满足：
  
     $$\begin{cases}n-k+1<=sum\\m<=k\\sum=\dfrac{n}{m}\end{cases}\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,$$

    - 这样，枚举 $m$，易得 $m$ 的取值范围:$1\sim\sqrt{n}$ 且 $sum$ 的值**单调递减**。时间：$O(\sqrt n)$。
  
  至此，本题的做法讨论完了。

  思路说得很清楚了，代码就不放了。

  **自己动手，丰衣足食。**

---

## 作者：luogu_starblue (赞：2)

~~对拍最有用的一集~~

首先，一个很显然的结论是当 $n=k$ 时 Bob 是必胜的。

观察发现对于 Bob 来讲，$m$ 取质数肯定是更优的，并且 $m$ 一定为 $n$ 的约数。

然后考虑什么情况对于 Alice 是更优的，首先注意到若 $n-(k-1)>k-1$，那么 Alice 必胜，此时她可以将一个数设置成 $k$ 或更大的数，其余 $k-1$ 个数分配为 $1$ 即可。

赛时做到这里手玩几组数据感觉没思路了，于是特判掉以上特殊情况后枚举所有小于等于 $\sqrt{n}$ 的质数表示 $m$ ，若为 $n$ 的约数则判定为 Bob 赢，否则 Alice 赢，然后与暴力对拍。拍出来发现 $n=9$ $k=6$ 的情况出现了问题。手搓这个数据发现对于 Alice 来讲如果给出 $4$ $1$ $1$ $1$ $1$ $1$ 则 Alice 胜利，并且发现她也只能给出这样的数列才能使自己胜利，于是我们便可以猜测一个结论：对于 Alice 来说，构造一个有 $k-1$ 个 $1$，$1$ 个 $n-(k-1)$ 的数列是最优的，~~本蒟蒻多次尝试严格证明这个结论但都失败了~~。

因此，我们在枚举质数 $m$ 的时候 Bob 胜利还需要满足 $n-(k-1)\le \frac{n}{m}$，因为此时只要这个序列的最大的数小于等于每个集合的值（即 $\frac{n}{m}$），那么 Bob 一定就可以给出合法的划分。

时间复杂度$O(S+T\pi(\sqrt{n}))$，$S$ 表示求小于等于 $\sqrt{n}$ 的所有质数的复杂度，$\pi(x)$表示小于等于 $x$ 的质数的个数，这个值接近 $\frac{x}{\operatorname{ln}x}$，可以通过本题。

最后，我认为题目中对于划分的定义不清楚，划分前可否将序列 $a$ 重排，例如当 $n=4,k=3$ 的时候，$1$ $2$ $1$ 和 $1$ $1$ $2$ 是否被视作不同的方案，实测二种其实被看成了同一种方案，如果是这样的话建议将序列改为集合，因为集合是无序的，而序列是有序的。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+9;
vector<int> pri;
bool not_prime[N];
void pre(int n) 
{
	not_prime[1]=true;
	for(int i=2;i<=n;i++)
	{
		if(!not_prime[i])
		{
			pri.push_back(i);
		}
		for(int j:pri)
		{
			if(i*j>n)break;
			not_prime[i*j]=true;
			if(i%j==0)break;
		}
	}
}
void solve()
{
	int n,k;
	cin>>n>>k;
	if(n==k)
	{
		cout<<"Bob\n";
		return ;
	}
	else
	{
		for(auto i:pri)
		{
			if(i*i>n)break;
			if(n%i==0&&n-(k-1)<=n/i)
			{
				cout<<"Bob\n";	
				return ;
			}		
		}
		cout<<"Alice\n";
	}
}
int main()
{
//	freopen("std.in","r",stdin);
//  freopen("ans1.out","w",stdout);
	pre(int(1e4));
	int t;
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：Acheron_RBM (赞：2)

还是一个逆天结论题。

首先我们可以得到，对于 Alice 她的最优策略显然是把序列分成如下图所示的样子。

![](https://cdn.luogu.com.cn/upload/image_hosting/lnc2cy6x.png)

此时 Bob 的最优策略显然是将 $m$ 设为 $2$。

如果 $n$ 除自己外的最大因数比 $n-k+1$ 小，那么 Bob 显然不能找到合法的 $m$。

这个时候有个问题，我们如何找的这个 $n$ 除自己外的最大因数。

我们可以反着考虑，我们直接去找 $n$ 的最小因数。

这个时候引出一个结论，一个数最小的因数一定是质数。

证明：唯一分解定理。

接下来就简单了，看看实现吧：

```cpp
int main()
{
    init();
	int t=read();
	while(t--)
	{
		int n=read(),k=read();
		if(n-k+1>getnum(n))
		{
			cout<<"Alice\n";
		}
		else
		{
			cout<<"Bob\n";
		}
	}
	return 0;
}
```

---

## 作者：DYYqwq (赞：1)

$n$ 平均分 $m$ 份，每份的和应当是 $\frac{n}{m}$。显然这里要求 $n$ 是 $m$ 的倍数。

考虑到如果有任意一个数是 $> \frac{n}{m}$ 的，那 Bob 无论如何也无法取到 $= \frac{n}{m}$ 的集合。

为了尽量构造出 $> \frac{n}{m}$ 的数，Alice 会选择填 $k-1$ 个 $1$，以及剩下的她期望 $> \frac{n}{m}$ 的数。

于是得，在 $n - (k - 1) > \frac{n}{m}$ 时，Alice 一定能赢。（这里显然 $m$ 默认取 $n$ 的最小真因子）

然后考虑如果 Alice 无法做到上面那种情况，那就是说所有数都会 $\leq \frac{n}{m}$，怎么办。

考虑设当前最大数为 $x$，自然不会有其他数 $>  1$。因为如果有非 $1$ 的数那为什么不加在 $x$ 身上呢（以利于卡死 Bob）？

但是经过之前的分析发现，只要 Bob 取到最小的 $m$，我们就卡不死。

于是得，在 $n - (k - 1) \leq \frac{n}{m}$ 时，Bob 一定能赢。（这里 $m$ 取值同上）

于是预处理一下 $10^5$ 以内的质数，每次找一下最小的能整除的就可以。

简单想一下应该比 $O(T\sqrt{n})$ 小很多，于是就能过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int prime[100010] , tot; bool flag[100000010];
void solve()
{
	int n , k; scanf("%d%d" , &n , &k);
	bool qwq = 0;
	for(int i = 1 ; prime[i] * prime[i] <= n ; i ++)
	{
		if(n % prime[i] == 0)
		{
			int x = n / prime[i];
			if(n - (k - 1) > x) printf("Alice\n");
			else printf("Bob\n");
			qwq = 1;
			break;
		}
	}
	if(!qwq) printf(n == k ? "Bob\n" : "Alice\n"); // 一个细节，n=k 时应当 Bob 赢，因为是全 1。 
}
int main()
{
	for(int i = 2 ; i <= 100000 ; i ++)
	{
		if(!flag[i]) prime[++ tot] = i;
		for(int j = 1 ; j <= tot ; j ++)
		{
			int nxt = i * prime[j];
			if(nxt > 100000) break;
			flag[nxt] = 1;
			if(i % prime[j] == 0) break; 
		}
	}
	int T; scanf("%d" , &T);
	while(T --) solve(); 
	return 0;
}
```

---

## 作者：liangyanbang (赞：1)

[P11010 『STA - R7』Divide and Merge Game](https://www.luogu.com.cn/problem/P11010)

#### 分析

首先有一个结论：当 $n$ 一定时，$k$ 越大，对 Bob 越有利。因为此时对正整数序列的划分方法更多，并且 Bob 可以将若干元素划分为一个集合，变成 $k$ 较小的情况。同理可得当 $n$ 一定时，$k$ 越小，对 Alice 越有利。

因此引入一个**临界值**：当 $k$ 小于这个临界值时，Alice获胜；反之 Bob 获胜。记 $n$ 的临界值为 $f(n)$。

- 当 $n$ 为质数时，有 $f(n)=n$。因为 Bob 获胜就必须划分出 $n$ 个集合，也就是说仅当 $k=n$ 时 Bob 获胜。
- 当 $n$ 为合数时，设 $n$ 除本身外的最大因子为 $p_n$。有 $f(n)=n-p_n+1$。

证明：当 $k<f(n)$ 时，Alice 必胜，因为 Alice 可令序列为一个 $n-k+1$ 和 $k-1$ 个 1。此时 $n-k+1>f(n)$，所以 Bob 无法划分出 n 个满足条件的集合。

当 $k\ge f(n)$ 时，考虑 $k=f(n)$ 的清况，假设 Alice 构造的序列中 $x$ 为最大的不能划分在一个和为 $p_n$ 的集合的数，那么 $x\ge \frac{p_n}{2}$，否则会有比 $x$ 大且满足条件的数。那么序列中 1 的个数不少于 $n-2p_n+x$。而 $n-2p_n+2x\ge n-p_n\ge p_n$，因此 $x$ 和 $p_n-x$ 个 1 划分为一个集合可以满足条件，与之前假设矛盾！因此命题得证。

#### 代码
方法1：预处理 $\sqrt{N}$ 内的所有质数后枚举求 $p_n$，时间复杂度为 $O(\sqrt{N}+\frac{T\sqrt{N}}{logN})$。


```cpp
#include <iostream>
using namespace std;
const int N=1e4+1,M=2e3+1;
int p[M],cnt;bool v[N];
void init(){
	for (int i=2;i<N;++i){
		if (!v[i])p[++cnt]=i;
		for (int j=1;j<=cnt;++j){
			if (i*p[j]>N)break;
			v[i*p[j]]=p[j];
			if (i%p[j]==0)break;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	init();
	int T,n,k;cin>>T;
	while (T--){
		cin>>n>>k;
		int x=0;
		for (int i=1;i<=cnt;++i)
			if (n%p[i]==0){
				x=p[i];break;
			}
		if (x==0)x=n;
		else x=n-n/x+1;
		if (x>k)cout<<"Alice\n";
		else cout<<"Bob\n";
	}
	return 0;
} 
```

方法2：线性筛出所有数的最小质因子，时间复杂度为 $O(N+T)$。


```cpp
#include <iostream>
using namespace std;
const int N=1e8+1,M=2e7+1;
int f[N],p[M],cnt;
void init(){
	for (int i=2;i<N;++i){
		if (!f[i])p[++cnt]=i;
		for (int j=1;j<=cnt;++j){
			if (i*p[j]>N)break;
			f[i*p[j]]=p[j];
			if (i%p[j]==0)break;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	init();
	int T,n,k;cin>>T;
	while (T--){
		cin>>n>>k;
		int x=n;
		if (f[n])x=n-n/f[n]+1;
		if (x>k)cout<<"Alice\n";
		else cout<<"Bob\n";
	}
	return 0;
} 
```

---

## 作者：I_will_AKIOI (赞：1)

根据题意，Bob 想要获胜，需要保证划分出的可重集和相等，因此这些可重集的和都是 $n$ 的真因子。容易发现 Bob 把 $a$ 划分成的每个集合的值都控制为 $n$ 的最大真因子肯定不劣，因此 Alice 的最优构造方案就是令 $a_1=n-k+1,a_2\sim a_k=1$。此时如果 $a_1$ 大于 $n$ 的最大真因子，那么 $a_1$ 就没地方放了，此时 Alice 获胜，否则 Bob 获胜。

求 $n$ 的最大因子，一种方法是枚举，复杂度 $O(t\sqrt{n})$ 会炸。由于 $n$ 的最大真因子等于 $n$ 除以 $n$ 的最小因子（不包括 $1$）。显然这个最小因子是个质数，所以我们可以用欧拉筛求出每个数的最小质因子，复杂度为 $O(t+n)$。

注意这里数组开 $10^8$ 空间卡的比较紧，存质数只需要开到 $6\times10^6$，至于判断质数的数组，由于只有 $0$ 和 $1$，所以可以使用 bitset 来存。

```cpp
#include<bits/stdc++.h>
#define N 100000000
#define M 6000000
using namespace std;
int n,k,s,p[M],low[N+5];//low[i]表示i的最小质因子
bitset<N+5>a;//不用bitset空间就炸了
void solve()
{
  cin>>n>>k;
  int maxx=n/low[n];//最大质因子
  if(n-k+1>maxx) cout<<"Alice\n";
  else cout<<"Bob\n";
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  for(int i=2;i<=N;i++)
  {
    if(a[i]==0) p[++s]=i,low[i]=i;
    for(int j=1;j<=s&&i*p[j]<=N;j++)
    {
      a[i*p[j]]=1;
      low[i*p[j]]=p[j];
      if(i%p[j]==0) break;
    }
  }
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：0)

当 $n=k$ 时，Bob 显然获胜。

当 $n>k$ 时：先考虑 Alice 的决策。最好的方案应该是将 $n$ 拆成若干个 $1$ 和一个 $n-k+1$，因为此时数与数之间相差更大，更难让各子段的和相等。

下面考虑 Bob 的决策。枚举 $n$ 的因数作为 $m$。

设 Bob 划分后各子段的和都为 $s$，有：

$$s=n/m$$

并且 $m$ 要满足：

$$s \ge n-k+1$$

$$m \le k$$

考虑到剩余的数都是 $1$，所以此时一定可以找到划分方案。

正序枚举 $m$，易得 $s$ 递减，所以只需要验证 $n$ 的最小因数即可。

为了优化遇到质数时的情况，$m$ 只需要枚举到 $\sqrt n$。

时间复杂度：$O(T\sqrt n)$，需要卡常通过。

```cpp
//Divide and Merge Game
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define pll pair<int,int>
#define IL inline

int q,sum,l;

IL int read() {
	int re=0;
	char in=getchar();

	while (in<'0'||in>'9') in=getchar();

	while (in>='0'&&in<='9') {
		re=re*10+in-48;
		in=getchar();
	}

	return re;
}

int main() {
	q=read();

	while(q--) {
		sum=read();
		l=read();

		if(sum==l) {
			putchar('B');
			putchar('o');
			putchar('b');
			putchar('\n');
			continue;
		}

		bool f=0;

		rep(i,2,min(l,int(sqrt(sum)))) {
			int s=sum/i;
			
			if(s<sum-l+1){
				break;
			}
			
			if(sum%i) {
				continue;
			}

			if(s>=sum-l+1) {
				putchar('B');
				putchar('o');
				putchar('b');
				f=1;
			}

			break;
		}

		if(f==0) {
			putchar('A');
			putchar('l');
			putchar('i');
			putchar('c');
			putchar('e');
		}

		putchar('\n');
	}
}
```

---

