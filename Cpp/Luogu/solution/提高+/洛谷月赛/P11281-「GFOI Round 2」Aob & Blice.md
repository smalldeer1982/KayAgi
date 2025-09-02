# 「GFOI Round 2」Aob & Blice

## 题目描述

Aob 和 Blice 在玩游戏。

现在有一个长为 $n$ 的排列 $p$，且 Aob 和 Blice 手里分别有一个初始为空的**不可重**集合 $S_A,S_B$。定义一轮游戏过程如下：

- 首先 Aob 会**随机**选取两个满足 $1 \leq x < y \leq n$ 且 $p_x>p_y$ 的数 $x,y$ ，然后从 $(x,y)$ 和 $(p_x,p_y)$ 这两个**有序二元组**中**随机选取一个**放入自己的集合 $S_A$ 中。

- 在这之后，Blice 会从 $(y,x)$ 和 $(p_y,p_x)$ 中选择一个放入自己的集合 $S_B$ 中。**注意这里的 $x,y$ 均为上一步中 Aob 选择的**。

在无限轮游戏之后 $^{\dagger}$，Aob 和 Blice 会比较他们手里的集合。虽然 Aob 只会随机，Blice 看起来更聪明些，但是 Blice 想要最终他们两个的集合完全相等，这样平局就不会有任何一个人伤心啦！

不幸的是，这个排列中的某些数消失了，于是 Blice 找到了你，想知道有多少种可能的原排列，使得他们两个人能够在无限轮后达成平局。为了方便，你只需要求出答案对 $998244353$ 取模的值。

$^{\dagger}$ 在“无限轮”之后 Blice 能达到平局，定义为对于任意 $\varepsilon>0$，存在一个正整数 $N$，使得对于任意 $n>N$，Blice 存在一种策略使得他在 $n$ 轮结束之后**不**平局的概率 $<\varepsilon$。

## 说明/提示

#### 【样例解释 #1】

两种排列都是合法的：$\{1,2,3\},\{3,2,1\}$。

#### 【数据范围】

**本题采用捆绑测试。**

| 子任务编号 | $n \leq$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | $9$ | 无 | $20$ |
| 2 | $2000$ | A | $15$ |
| 3 | $2000$ | 无 | $10$ |
| 4 | $10^6$ | A | $15$ |
| 5 | $10^6$ | B | $10$ |
| 6 | $10^6$ | 无 | $30$ |

- 特殊性质 A：$p_i \ne 0$。
- 特殊性质 B：$p_i = 0$。

对于所有数据，满足：

- $1 \le n \le 10^6$；
- $0 \le p_i \le n$；
- 对于任意 $1 \le i < j \le n$，若 $p_i \ne 0$ 且 $p_j \ne 0$，则 $p_i \ne p_j$。

## 样例 #1

### 输入

```
3
0 2 0```

### 输出

```
2```

## 样例 #2

### 输入

```
7
0 3 2 0 5 7 0```

### 输出

```
2```

# 题解

## 作者：Drifty (赞：60)

### Preface

神秘的好题。

虽然棕名但求过，之前公开赛大小号交同一份代码棕了。本人并不存在抄袭。

### Solution

我们直接考虑在游戏轮数趋于无穷时的情况。

此时，我们注意到所有的 $(x,y)$ 和 $(p_x, p_y)$ 都会被 Aob 加入 $S_{A}$，那么为了让 $S_{A}=S_{B}$，因此所有的 $(x,y)$ 和 $(p_x, p_y)$ 都必须能够通过 Blice 的两种选择产生。

我们看一下 Blice 基于 Aob 能产生的三种数对，分别是 $(y,x),(p_y,p_x),(p_{p_y},p_{p_x})$，那么形式化的，我们就可以把在游戏轮数趋于无穷时的的 $S_{A}$，$S_{B}$ 写出来。

$$
S_A =\left \{(x,y),(p_x,p_y)\mid 1\le x < y\le n,p_x > p_y \right \}
$$

$$
S_B =\left \{(y,x),(p_y,p_x),(p_{p_y},p_{p_x})\mid 1\le x < y\le n,p_x > p_y \right \}
$$

然后我们会注意到，$S_A=S_B$ 的充分必要条件$^†$是 $\forall 1\le i\le n$ 都有 $p_{p_i} = i$。这样也就解决掉了性质 A，即利用结论判定一下 $p$ 是否满足所述条件即可。

接下来我们考虑如何统计方案。

首先为了满足条件，有一些 $0$ 上必须填上固定的数。对于满足 $p_{p_i} = 0$ 的 $i$，为了满足条件 $p_{p_i}$ 必须填上 $i$。那么在这样填完之后，我们还会剩下若干个 $0$，那么我们可以把这些 $0$ 单独拿出来求方案数，设剩下 $k$ 个 $0$，那么方案数显然等价于对于所有的 $1\sim k$ 的排列 $q$ 中，满足 $\forall 1\le i\le n$ 都有 $p_{p_i} = i$ 的 $q$ 的个数。

然后我们考虑递推求解，设方案数为 $f_k$，则不难发现 $f_1 = 1, f_2 = 2$。对于当前的 $q_k$，若 $q_k=k$，这种情况下方案数由 $f_{k-1}$ 直接转移而来，否则必定要选出一个 $1\le j<k$，使得 $q_{q_k} = j$ 然后共有 $n-1$ 种选法，且选出的 $k,j$ 是独立于其他数的，那么对于每一种选法都有 $f_{k-2}$ 的方案，此时总数为 $(k-1)f_{k-2}$。两种情况合并，就得出了递推式 $f_i=f_{i-1}+(i-1)f_{i-2}$，其中 $i>2$。答案就是 $f_k$。

下面给出**对于 $†$ 的证明**：

我们发现命题实际上等价于建立一个有向图 $G\left \langle V,E\right \rangle$，其中：

$$V={x\mid 1\le x\le n,x\in \Z}$$

$$E={(i,p_i)\mid 1\le i\le n, i\in \Z}$$

那么 $S_A=S_B$ 当且仅当 $G$ 中不存在长度超过 $2$ 的环。

- 先证必要性：
  
  你会发现对于所有 $1\le x < y\le n,p_x > p_y$，有 $(x,y) = (p_y, p_x),(p_x, p_y) = (y,x),(p_{p_y}, p_{p_x}) = (y, x)$，证好了。

- 再证充分性：
  
  考虑反证，若不满足条件，此时图中必定存在节点数大于三的一个环，不妨设这个环的节点编号集为 $M=\{u_1, u_2,\dots,u_k\}$，我们记 $M$ 所能产生在 $S_A$ 的 $\{(x,y),(p_x,p_y)\} = T_A$，能在 $S_B$ 中产生的 $\{(y,x),(p_y,p_x),(p_{p_y}, p_{p_x})\} = T_B$，那么我们由定义显然有 $x\in M, y\in M,p_x\in M, p_y\in M$，因此 $T_A$ 和 $T_B$ 是封闭的。所以若 $S_A=S_B$ 那么 $T_A = T_B$。

  我们不妨设 $u_1<u_2<\dots<u_k$，因此 $(u_{k-1},u_{k})\in T_A$，但是由穷举可得，$(u_{k-1},u_{k})$ 一定不属于 $T_B$（由于 $p_{u_i} = u_{i + 1}(1\le i < k),p_{u_k} = u_1$ 因此你只要穷举 $(u_{k-2},u_{k-1}),(u_{k}, u_{k-1}),(u_{k}, u_1)$ 对 $T_B$ 能贡献的数对，这显然是极其有限的，因此可以直接穷举），于是矛盾，证毕。

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int P = 998244353, N = 1e6 + 3;
int n, p[N], x = 1;
i64 res[N] = {0, 1, 2}, ans;
int main() {
    cin.tie(nullptr), cout.tie(nullptr) 
    -> sync_with_stdio(false); cin >> n;
    for (int i = 1; i <= n; i ++) cin >> p[i];
    for (int i = 1; i <= n; i ++) if (p[p[i]] != i) x = 0;
    if (x) return cout << 1, 0;
    for (int i = 1; i <= n; i ++) if (p[i]) {
        if (p[p[i]] == 0) p[p[i]] = i;
        else if (p[p[i]] != i) return cout << 0, 0;
    }
    for (int i = 1; i <= n; i ++) if (!p[i]) ans ++;
    for (int i = 3; i <= n; i ++)
        res[i] = (res[i - 1] + res[i - 2] * (i - 1) % P) % P;
    return cout << res[ans], 0;
}
```

---

## 作者：ran_qwq (赞：6)

题面比较抽象，这里写一个较为好理解的题面。

> 对于一个排列 $p$，以下面的方式定义矩阵 $s$ 与 $t$：
> 
> > 对于任意 $1\le x<y\le n$ 且 $p_x>p_y$，$s_{x,y}=1$，$s_{p_x,p_y}=1$；$t_{y,x}=1$，$t_{p_y,p_x}=1$。
> > 
> > 没被赋 $1$ 的位置为 $0$。
>
> 求使 $s=t$ 的原排列个数。

根据定义知 $s_{x,y}=t_{y,x}$，联立 $s_{y,x}=t_{y,x}$ 得 $s_{x,y}=s_{y,x}$，消去 $t$。

令 $q$ 为 $p$ 的逆排列，则如果 $x<y$，$s_{x,y}=[p_x>p_y]\lor[q_x<q_y]$（分别对应 $s_{x,y}=1$ 和 $s_{p_x,p_y}=1$）；如果 $x>y$，$s_{x,y}=[p_x<p_y]\lor[q_x>q_y]$。

则 $[p_x>p_y]\lor[q_x<q_y]=[p_x<p_y]\lor[q_x>q_y]$。因为 $[p_x>p_y]$ 与 $[p_x<p_y]$ 有且仅有一个为 $1$（$q$ 同理），所以两边等于 $1$。

若 $[p_x>p_y]=1$，则 $[p_x<p_y]=0$，$[q_x>q_y]=1$，$[q_x<q_y]=0$。$[p_x>p_y]=0$ 同理。

换句话说，$[p_x>p_y]=[q_x>q_y]$。

又因为 $p,q$ 均为排列，所以 $p_x=q_x$，即 $p_{p_x}=x$。

把排列视为置换，$x$ 向 $p_x$ 连边，得出来的图没有长度大于 $2$ 的环。

先判掉 $p_{p_x}\ne0$ 且 $p_{p_x}\ne x$ 的情况。剩下有些数没被确定，可以在保证环长 $\le2$ 的情况下随便填。

问题转化为，对于一个长度为 $k$ 的排列，有多少种方案使得所有环长 $\le2$，即 B 性质。

我们从前往后考虑，设 $f_i$ 为长度为 $i$ 的方案数。新加一个数有两种情况：

1. 自己单独成环，$f_i\leftarrow f_{i-1}$。
2. 和之前的某个数成环，$f_i\leftarrow f_{i-2}\cdot(i-1)$。

初值：$f_0=f_1=1$。

```cpp
int n,ans,a[N],b[N],f[N];
void QwQ() {
	n=rd(),f[0]=f[1]=1;
	for(int i=2;i<=n;i++) f[i]=vadd(f[i-1],vmul(i-1,f[i-2]));
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=1;i<=n;i++) if(a[i]) {
		b[i]=b[a[i]]=1;
		if(a[a[i]]&&a[a[i]]!=i) return puts("0"),void();
	}
	wr(f[count(b+1,b+1+n,0)],"\n");
}
```

---

## 作者：FlyPancake (赞：5)

## [P11281 「GFOI Round 2」Aob & Blice 题解](https://www.luogu.com.cn/problem/P11281)

本题解对于结论有**较为**理性的证明。

题目太长~~太抽象~~自己看。

---

因为会随机抽且经过无限轮，所以对某一排列 $p$ 有对于任意的 $1 \le x < y \le n$ 且 $p_x > p_y$，均会产生二元组 $(x, y)$ 和 $(p_x, p_y)$。

$p$ 满足平局条件当且仅当满足 A 能产生二元组 $(y, x)$ 和 $(p_y, p_x)$，这样 B 才能产生二元组 $(x, y)$ 和 $(p_x, p_y)$，使其与 A 的集合相等。

考虑何时才能使 $p$ 满足条件：

- 对于 A 何时能产生二元组 $(y, x)$，因为 $x < y$，所以只能由满足 $p_m=x, p_t=y$ 且 $t<m$ 的情况产生。

- 对于 A 何时能产生二元组 $(p_y, p_x)$，因为 $p_x > p_y$，所以只能由满足 $p_{p_x} < p_{p_y}$ 的情况产生。

对于条件一，此时也满足 $p_{p_t} < p_{p_m}$，于是题意转化成为：

对于一个 $1 \sim n$ 的排列 $p$，$p$ 满足平局条件当且仅当对于任意 $1 \le i < j \le n$ 且 $p_i > p_j$，需满足 $p_{p_i} < p_{p_j}$。

（此处证明放最后）

所以 $p$ 满足平局条件，当且仅当 $p_{p_i} = i$。

接下来考虑如何求出方案数：

若不满足平局条件，则输出 $0$。

已知的数满足平局条件之后，记此时仍可以为 $0$ 的数的个数为 $cnt$。对于 $1 \le i \le cnt$，记 $dp_i$ 为前 $i$ 个数的总方案数。

- 假设 $p_i = i$，则 $dp_i = dp_{i-1}$。

- 假设 $p_i \neq i$，则需从 $1 \sim i-1$ 中选一个数与 $i$ 互相匹配，有 $i-1$ 种可能，剩下的之前确定的方案数为 $dp_{i-2}$，所以 $dp_i = dp_{i-2} \times (i-1)$。

综上，转移方程为 $dp_i = dp_{i-1}+dp_{i-2}\times (i-1)$。显然有 $dp_0 = dp_1 = 1$。

答案即为 $dp_{cnt}$。

---

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
constexpr int N = 1e6+5, mod = 998244353;

int n, p[N];
int dp[N], cnt;

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>p[i];
	for(int i=1; i<=n; i++){
		if(p[i]){
			if(!p[p[i]]) p[p[i]] = i;
			else if(p[p[i]] != i){
				cout<<0;
				return 0;
			}
		}
	}
	for(int i=1; i<=n; i++)
		if(!p[i]) cnt++;
	dp[0] = 1; dp[1] = 1;
	for(int i=2; i<=cnt; i++)
		dp[i] = (dp[i-1]+(ll)dp[i-2]*(i-1)%mod)%mod;
	cout<<dp[cnt];
	return 0;	
}
```

---

关于上文中的证明：

已知有 $1 \sim n$ 的排列 $p$，对于任意 $1 \le i < j \le n$ 且 $p_i > p_j$，均有 $p_{p_i}<p_{p_j}$，才能使 $p$ 符合平局条件。

记 $P_i(x)$ 表示 $i$ 经过 $x$ 次取 $p$ 中的值后得到的值。例如 $P_i(1)=p_i, P_i(2)=p_{p_i}$。

因为 $P_i(1) > P_j(1)$ 且 $P_i(2) < P_j(2)$，所以 $P_i(3) > P_j(3)$。

因为 $P_i(2) < P_j(2)$ 且 $P_i(3) > P_j(3)$，所以 $P_i(4) < P_j(4)$。

以此类推。

将 $P_i(2)=i$ 看作二元环，下面证明对于任意三元环不存在 $p$ 符合条件：

若 $1 \le i < j \le n$ 且 $P_i(1) > P_j(1)$，则 $P_i(4) < P_j(4)$。而根据三元环的性质 $P_i(1) = P_i(4)$，与满足条件矛盾，故不成立。

对于任意奇数环同理可证。

下面证明对于任意四元环不存在 $p$ 符合条件：

若 $1 \le i < j \le n$ 且 $P_i(1) > P_j(1)$，一定存在 $P_i(2)=j, P_j(2)=i$，因为对于任意一个数均有一个位置与之对应而且必定有 $i<j$ 的情况，此时需满足 $P_i(2)<P_j(2)$，即 $j<i$，与已知矛盾。

对于任意偶数环同理可证。

---

## 作者：LinkCatTree (赞：5)

[引流](https://linkcattree.github.io/posts/1435751271/)。

本人数学不好，语言可能不严谨，望大佬指出 QwQ

这道题看起来很复杂，但其实是**诈骗题**。

首先不难发现 $p_x,p_y$ 是一个逆序对。接着，为了确保无论 Aob 怎么选，Blice 都可以使最终自己选的数集与 Aob **完全一致**，我们发现：对于所有逆序对 $p_x,p_y(x<y)$，都有：$p_x=y,p_y=x$。这样，无论 Aob 选了 $(x,y)$ 还是 $(p_x,p_y)$，Blice 都可以做到与 Aob 选的一致。

为什么呢？我们不妨用反证法进行证明：

如果一个逆序对 $p_x,p_y(x<y)$ 其中 $p_x=a,p_y=b$ 满足 $a \neq y$ 或 $b \neq x$，那么只要 Aob 一直选择这一对中的 $(a,b)$，Blice 就**肯定**无法做到与 Aob 完全一致。

根据题目中“无限轮”后平局的定义，当逆序对数为 $x$、轮数为 $n$ 时，易构造出 $\varepsilon=(2x)^{-n}$，根据上述不平局的策略，我们发现不平局的出现概率**至少**为 $(2x)^{-n}$（即 Aob 每次都选择 $(a,b)$），与题目中对“无限轮”后平局的定义矛盾。

所以能够使 Aob 和 Blice “无限轮”后平局，$p_i$ 必须满足：

1. $p_i=i$。

2. $p_i=j$ 同时 $p_j=i$（$i \neq j$）

知道这个后，我们就可以开始考虑代码实现了。

首先显然可以记录下每个数 $x$ 在 $p$ 中出现的位置 $r_x$，如果出现 $r_x \neq p_x$，说明**不可能**平局，输出 $0$ 即可。否则我们可以统计剩下有多少个数能填，对这些数我们求出满足上述两条规则的数列个数即可。

统计剩下有多少个数能填时要注意分类和细节：

1. 若 $p_x=x$，则能填的数少一。

2. 若 $p_x=0$ 但 $r_x \neq 0$，说明 $p_{r_x}=x$ 那么此时 $p_x$ 只能填 $r_x$，那么 $p_x$ 不能填，能填的数少一。

3. 若 $p_x \neq 0$，由于已经判断过无解，那么 $p_x$ 不能填，能填的数少一。

接下来看如何计算答案。假设还能填的数有 $cnt$ 个，考虑递推求出答案。设 $f_x$ 表示前 $x$ 个数有多少种合法的填法，易发现：对于第 $x+1$ 个数，如果它满足条件一（$p_x=x$），则有 $f_x$ 中可行的填法；如果它满足条件二（$p_x=y,p_y=x$），那么它必须从前 $x$ 个数中再选一个，再填剩下的数，即有 $x \cdot f_{x-1}$ 种。有次我们你可以得出：

$$f_{x+1}=f_x+x \cdot f_{x-1}$$

判断无解是 $\mathcal{O}(n)$ 的，计算 $cnt$ 是 $\mathcal{O}(n)$ 的，递推求 $f_{cnt}$ 也是 $\mathcal{O}(n)$ 的，总时间复杂度 $\mathcal{O}(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e6+5;
const ll mod=998244353;
const ll inv=499122177;
int n,a[N],r[N];
ll f[N];

int main() {
	scanf("%d",&n);
	int cnt=n;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		if(!a[i]) continue ;
		r[a[i]]=i;
	}
	for(int i=1;i<=n;i++) {
		if(r[i]&&(r[i]!=a[i]&&a[i])) return printf("0\n"),0;
		else if(r[i]) cnt--;
		else if(r[a[i]]) cnt--;
	}
	f[0]=f[1]=1LL;
	for(int i=2;i<=cnt;i++) {
		ll x=i;
		f[i]=(f[i-1]+f[i-2]*(x-1LL)%mod)%mod;
	}
	printf("%lld\n",f[cnt]);
	return 0;
}
```

---

## 作者：Lysea (赞：5)

## Solution

形式化题意：

给定序列 $a$，若 $a_i=0$ 则代表未知。

问有多少种排列 $p$ 满足 $\forall i,p_{p_i}=i$。

为什么可以转化为以上题意呢？

因为 $x<y$ 且 $p_x>p_y$，若要满足题意必须对于任意 $x,y$ 满足 $x=p_y$ 且 $y=p_x$。

而满足上述要求的无非两种情况：

- $p_i=i$

- $p_i=j$ 且 $p_j=i$

形式化一点说就是 $p_{p_i}=i$。

转换完题目后再看本题，记 $cnt=\sum[a_i=0]$，我们先从确定的位置入手：

- 若 $a_{a_i}=i$，满足要求。

- 否则若 $a_{a_i}=0$，那么为了满足题意，$a_{a_i}$ 就一定要赋值为 $i$，$cnt\leftarrow cnt-1$。

- 否则一定不满足题意，输出 $0$ 即可。

接下来的问题就变为了，对于一个长为 $cnt$ 的排列 $p$，有多少种赋值方案能够满足 $\forall i,p_{p_i}=i$。

至于这些数是否能与原 $a$ 序列构成排列已不重要了，毕竟我们只在乎数与数之间的关系。

明显的计数 dp，令 $dp_{i,0/1}$ 表示前 $i$ 个位置的总方案数。其中 $op=0$ 表示此时 $p_i=i$，$op=1$ 代表 $p_i<i$ 且 $p_{p_i}=i$。

$$dp_{i,0}=dp_{i-1,0}+dp_{i-1,1}$$

$$dp_{i,1}=(i-1)dp_{i-1,0}$$

最终答案：$dp_{cnt,0}+dp_{cnt,1}$。

有个坑点，注意特殊性质 A 中 $cnt=0$，此时需要特判答案为 $1$（假设有解）或是将 $dp_{0,0}\leftarrow 1$ 即可解决。

## Code


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
#define INF 1e18
using namespace std;
const int M=998244353;
int n,a[N],ans=1,cnt,dp[N][2];
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(!a[i]) cnt++;
	}
	for(int i=1;i<=n;i++){
		if(!a[i]) continue;
		if(i!=a[a[i]]){
			if(a[a[i]]){
				cout<<0;
				return 0;
			}	
			cnt--;
		}
	}
	dp[0][0]=dp[1][0]=dp[2][0]=dp[2][1]=1;
	for(int i=3;i<=cnt;i++){
		dp[i][0]=(dp[i-1][0]+dp[i-1][1])%M;
		dp[i][1]=(i-1)*dp[i-1][0]%M;
	}
	cout<<(dp[cnt][0]+dp[cnt][1])%M;
	return 0;
}
```

---

## 作者：Justin0779 (赞：4)

我十分支持出题人改人名的行为（~~因为省选真的很难~~

# Solution

入手之后看题，不难发现这个**随机**是没有用的，在**无限轮**的加持下，Aob 会选完所有可能的逆序对或逆序对下标，即 $(p_x,p_y)$ 或 $(x,y)$，同样 Blice 会**跟随** Aob 选完所有的 $(y,x)$ 或 $(p_y,p_x)$。这里的能选就选很容易说明，Blice 不选完会导致 $|S_B| < |S_A|$，所以 Blice 也是能选就选。

这样我们稍微知道了我们需要求的是什么，但进入计算还是很遥远不好想，我们从样例入手：

```
3
0 2 0
```
它的答案是 $2$。
```
7
0 3 2 0 5 7 0
```
它的答案是 $2$，而且满足的情况必有 $p_7=6$。

同时，我们自己构造一个数据
```
3
2 1 3
```
他的答案是 $0$。

然后观察三组数据（也可以结合 $n=4$ 的情况进一步探讨），我们发现：有这样的序列必然有：
> 对于位置 $x$，要么有 $x=p_x$，要么有 $p_{p_x}=x$

这就是我们所发现的性质，即两两必然配对（相等的情况算广义）。然后我们从 $n=3$ 的所有不成立情况结合数学归纳法，稍微理解一下就能证明一般的 $n$ 同样有这样的性质。这里笔者只是简单的推了一下，因为笔者的数学功底很差并没有极度严格的证明，有兴趣的话可以尝试自己证一下。

有了这个性质，我们的前路豁然开朗。剩下的工作便只有判无解和推出有 $k$ 个不确定排列元素（要求两两配对）的总方案数了。判无解很简单，寻找是否有 $x=p_x$ 或 $p_{p_x} = x$ 即可，当 $p_{p_x} = 0$ 时令 $p_{p_x} \gets x$ 即可，否则直接输出 $0$。

剩下就是考虑推出有解的答案。令 $dp_k$ 为有 $k$ 个不确定元素时的方案数。打表一下发现有 $dp_0=1,dp_1=1,dp_2=2,dp_3=3$ 似乎像是可以递推的样子，那么就直接上动态规划。

考虑 DP，尝试写出转移方程，我们要由 $dp_1 \sim dp_{n-1}$ 推出 $dp_n$，分情况讨论：

1. $n=p_n$ 这时候跟前面无影响，方案数为 $dp_{n-1}$ 
2. $n\ne p_n$ 这时候 $n$ 必然和前面 。$n-1$ 个元素的某一个 $i$ 配对，所以从里面随机选一个，剩下 $n-2$ 个元素，方案数为 ${{n-1}\choose 1} \times dp_{n-2} = (n-1)\times dp_{n-2}$。

转移方程即为：
$$
dp_n=dp_{n-1}+(n-1)\times dp_{n-2}
$$

这道题到这里就做完了，时间复杂度 $O(n)$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e6 + 514;
constexpr ll mod = 998244353;

namespace Otakus
{
    int n, a[N], A[N], cnt = 0;
    ll dp[N];

    void init()
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        for (int i = 1; i <= n; i++)
        {
            if (i != a[i] && a[i] != 0)
            {
                if (!a[a[i]])
                    a[a[i]] = i;
                else if (a[a[i]] != i)
                {
                    cout << 0;
                    return;
                }
            }
        }

        for (int i = 1; i <= n; i++)
            if (!a[i])
                cnt++;

        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= cnt; i++)
            dp[i] = (dp[i - 1] + (i - 1) * dp[i - 2]) % mod;

        cout << dp[cnt];
    }
} // namespace Otakus

int main()
{

    Otakus::init();
    return 0;
}
```

---

## 作者：H2ptimize_AFO (赞：3)

让我们思考一下“无限轮”。

不难发现，根据 Aob 的行动方式，经过足够次随机后，最终集合 $S_A=\set{(i,j),(p_i,p_j)|1\le i<j\le n,p_i>p_j}$，即排列 $\set{p_n}$ 中所有逆序对及其对应下标。

因此只需要考虑 $S_B$ 即可。

对于一组满足 $1\le i<j\le n,p_i>p_j$ 的 $(i,j)$，显然 $(j,i)\neq(i,j)$。为了使 $S_B=S_A$，$S_B$ 中应当存在 $(p_j,p_i)=(i,j)$；同时，$S_A$ 中也应当有 $(p_{p_i},p_{p_j})=(p_j,p_i)$。将两式合并，得到 $p_{p_i}=i$。

这样我们已经完成了性质 A，只需要统计对于每个 $p_i$ 是否满足 $p_{p_i}=i$ 即可，若不满足直接输出 $0$。接下来考虑排列 $\set{p_n}$ 有缺失的情况。

我们先将能填充的缺失部分填好。对于 $p_i\neq0$ 的项，若 $p_{p_i}=0$，那我们可以直接将 $p_{p_i}$ 填上 $i$。

当所有能填的空填完后，问题就转化为了性质 B。记排列 $\set{p_n}$ 中有 $cnt$ 项为 $0$，我们需要求出对这些空格填空的总方案数。对于第 $i$ 个空，我们要么填入 $i$，要么填入 $k$ 同时在第 $k$ 个空填入 $i$。

这个是问题相当于求数列 [A000085](https://oeis.org/A000085)，记 $dp(i)$ 为有 $i$ 个空时的总方案数，则 $dp(i)=dp(i-1)+dp(i-2)\times(i-1)$，边界为 $dp(0)=dp(1)=1$，答案为 $dp(cnt)$。~~场上查到 oeis 之后把递推式打成了 `dp[i]=dp[i-1]-(cnt-1)*dp[i-2]` 怒挂 70 分，唐！~~

至此，此题得解。

---
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6+10,P=998244353;

int n,p[MAXN],dp[MAXN];

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n;i++)
	{
		if(p[i]&&!p[p[i]])p[p[i]]=i;
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(p[i]==0)cnt++;
		else if(p[p[i]]==i)continue;
		else
		{
			cout<<0;
			return 0;
		}
	}
	dp[0]=dp[1]=1;
	for(int i=2;i<=cnt;i++)dp[i]=(dp[i-1]+dp[i-2]*(i-1))%P;
	cout<<dp[cnt];
	return 0;
}
```

---

## 作者：_Kenma_ (赞：1)

# P11281 解题报告

## 前言

偏 ad-hoc 的计数题。可能需要灵光一现。

## 思路分析

首先题面就别看了，非常难以读懂。

这里给一个形式化题意：给定一个排列 $p$ 的若干项，对于任何满足 $a<b,p_a>p_b$ 有序二元组 $(a,b)$ 和 $(p_a,p_b)$，都有满足 $c>d,p_c<p_d$ 的有序二元组 $(c,d)$ 或 $(p_c,p_d)$ 与之对应相等，对合法的排列计数。

首先构造一个排列 $b$，令 $b_{p_i}=i$，这样 $c>d,p_c<p_d \Longleftrightarrow  x<y,b_x>b_y$。

这样，我们得到了两个相同形式的排列 $p$ 和 $b$。发现排列 $p$ 合法，当且仅当排列 $p$ 和 排列 $b$ 相同。

也就是说：

$$\forall i\in[1,n],p_i=b_i$$

变化一下：

$$\forall i\in[1,n],p_i=p_{p_i}$$

这样问题变得十分单纯了。

我们只需要对满足上面条件的排列 $p$ 计数就行了。

首先对一些可以确定值的位置赋值，如果出现矛盾，说明不存在合法的排列。

现在问题退化为 $p_i=0$ 的情况了。

如果 $i \to p_i$，那么 $p_i$ 合法当且仅当图上只有环长为 $1$ 或 $2$ 的简单环。

所以我们可以枚举有几个位置是自环，将剩下的位置两两配对。

这样做肯定是不重不漏的。

也就是说：

$$ans=\sum_{i=1}^{2i\le n} \binom{2i}{n} \frac{(2i)!}{2^i i!}$$

解释一下组合意义。

首先选出 $2i$ 个数两两配对，然后给每一对配对的数一种相同的颜色，这一步可以直接算多重集排列数，最后因为不区分颜色，所以要把颜色的排列数从答案中消去。

做完了，总体复杂度 $O(n\log n)$。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,s,x,y,k,ans,cnt,p[1000005];
const int mod=998244353;
int fac[2000005];
int binpow(int a,int b){
	if(b==0) return 1;
	int res=binpow(a,b/2);
	if(b&1) return res*res%mod*a%mod;
	else return res*res%mod;
}
int C(int n,int m){
	return fac[n]*binpow(fac[n-m],mod-2)%mod*binpow(fac[m],mod-2)%mod;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	for(int i=1;i<=n;i++){
		if(p[i]){
			if(p[p[i]] && p[p[i]]!=i){
				cout<<0;
				return 0;
			}else{
				p[p[i]]=i;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!p[i]) cnt++;
	}
	for(int i=0;i<=cnt;i++){
		if((cnt-i)&1) continue;
		ans=(ans+C(cnt,i)*fac[cnt-i]%mod*binpow(binpow(fac[2],(cnt-i)/2),mod-2)%mod*binpow(fac[(cnt-i)/2],mod-2)%mod)%mod;
	}
	cout<<ans;
	return 0;
}

```

## 后记

为什么这种人类智慧题能有一车人切啊。

---

## 作者：summ1t (赞：1)

题面真的很抽象，但读懂后思路并不难想。

我们要明确什么时候能够平局，因为要求无限轮后之后能够达到平局，所以无论 Aob 选 $(x,y)$ 还是 $(p_x,p_y)$，Blice 都应该能在 $(y,x),(p_y,p_x)$ 中找出与 Aob 相等的数对。

由于 $x\ne y,p_x\ne p_y$，所以唯一可能平局的情况就是 $x=p_y,y=p_x$。

所以若 $x<y,p_x>p_y$，则应满足 $p_x=y,p_y=x$，否则 $p_x=x$。如果不是这两种情况就不合法。

由此某些位置的值可以唯一确定，接下来设有 $n$ 个位置的值未确定，考虑 dp。

设 $f_i$ 表示前 $i$ 个位置合法的方案数。对于第 $i$ 个数，我们可以将其放到 $i$，方案数即为 $f_{i-1}$，也可以选择一个数进行交换，方案数即为 $(i-1)\times f_{i-2}$。

所以转移方程为 $f_i=f_{i-1}+(i-1)\times f_{i-2}$，初始化 $f_0=f_1=1$。

答案即为 $f_n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rd read()
#define gc getchar()
#define dg(ch) isdigit(ch)
#define _mul(x) ((x<<3)+(x<<1))
#define ll long long
#define PII pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pq priority_queue
#define em(q) q.empty()
#define FOR(i,j,k) for(int i=j;i<=k;i++)
#define ROF(i,j,k) for(int i=j;i>=k;i--)
int read(){int x=0,f=1;char ch=gc;while(!dg(ch)){if(ch=='-')f=-1;ch=gc;}while(dg(ch)){x=_mul(x)+(ch^48),ch=gc;}return x*f;}
const int N=1e6+10,mod=998244353;
int n,p[N],pos[N],f[N];
int main(){
	n=rd;FOR(i,1,n) p[i]=rd,pos[p[i]]=i;
	FOR(x,1,n){
		if(!pos[x]) continue;
		int y=pos[x];
		if(pos[y]&&pos[y]!=x){printf("%d\n",0);return 0;}
	}
	FOR(x,1,n){if(!pos[x])continue;int y=pos[x];p[x]=y;}
	int cnt=0;
	FOR(i,1,n) if(p[i]==0) cnt++;
	if(cnt==0||cnt==1){printf("%d\n",1);return 0;}
	f[0]=f[1]=1;
	FOR(i,2,cnt) f[i]=(f[i-1]+1ll*(i-1)*f[i-2]%mod)%mod;
	printf("%d\n",f[cnt]);
	return 0;
}
```

---

## 作者：wxzzzz (赞：0)

### 思路

题意等价于二人可操作集合相等。

发现 $S_A$ 中的一组 $\{(i,j),(a_i,a_j)\}$ 只能由 $S_B$ 中的一组 $\{(a_{j'},a_{i'}),(j',i')\}$ 对应，因此必须有 $i'=a_{a_i},j'=a_{a_j}$，这等价于每个 $i$ 要么有 $a_i=i$，要么有且仅有一个 $j$ 满足 $a_i=j,a_j=i$。

因此先利用现有的 $a_i$ 确定所有能确定的 $a_i$，同时判无解，然后就转化为了全 $0$ 的情况，记剩余 $0$ 有 $tot$ 个。

考虑全 $0$ 怎么做。

令 $f_i$ 表示 $i$ 个有序下标，建立两两匹配的方案数（注意这不等价于括号序列数，场上因为这个卡了好久），答案为 $\displaystyle\sum_{i=0}^{tot}[(tot-i)\bmod 2=0]\dbinom{tot}{i}f_{tot-i}$。

$f_i$ 可简单 DP 求得。考虑 $i$ 可以和前面 $i-1$ 个点匹配，剩余 $i-2$ 个待匹配点，故有 $f_i=f_{i-2}(i-1)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
int mod(long long x) {
    return x % MOD;
}
int qpow(int x, int k) {
    int ret = 1, base = x;
    while (k) {
        if (k & 1)
            ret = mod(1ll * ret * base);
        base = mod(1ll * base * base);
        k >>= 1;
    }
    return ret;
}
int fac[1000005], ifac[1000005];
int C(int x, int y) {
    if (x < y || y < 0)
        return 0;
    return mod(1ll * fac[x] * mod(1ll * ifac[y] * ifac[x - y]));
}
int n, a[1000005], f[1000005];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (!a[i])
            continue;
        if (!a[a[i]])
            a[a[i]] = i;
        else if (a[a[i]] != i) {
            puts("0");
            return 0;
        }
    }
    int tot = 0, ans = 0;
    for (int i = 1; i <= n; i++)
        tot += (!a[i]);
    fac[0] = 1;
    for (int i = 1; i <= tot; i++)
        fac[i] = mod(1ll * fac[i - 1] * i);
    ifac[tot] = qpow(fac[tot], MOD - 2);
    for (int i = tot - 1; i >= 0; i--)
        ifac[i] = mod(1ll * ifac[i + 1] * (i + 1));
    f[0] = 1;
    for (int i = 2; i <= tot; i += 2)
        f[i] = mod(1ll * f[i - 2] * (i - 1));
    for (int i = 0; i <= tot; i++)
        if (tot - i & 1 ^ 1)
            ans = mod(1ll * ans + 1ll * C(tot, i) * f[tot - i]);
    cout << ans;
    return 0;
}
```

---

