# Tokitsukaze and Permutations

## 题目描述

有一个长度为 $n$ 的排列 $p$，将执行 $k$ 次操作。

操作过程：对于 $1\sim n$ 中，当 $p_i>p_{i+1}$，则交换 $p_{i},p_{i+1}$。

经过 $k$ 次操作之后，得到了一个新数组 $a$，再定义数组 $v$ 表示在 $1\sim i-1$ 中比 $a_i$ 大的个数。

现在给定 $v$，但是有可能其中的值为 $-1$，这表示它的值并不确定。求有多少种 $p$ 满足在 $k$ 次操作后得到的 $v$ 和给定确定值一致，结果对 $998244353$ 取模。

## 样例 #1

### 输入

```
3
5 0
0 1 2 3 4
5 2
-1 1 2 0 0
5 2
0 1 1 0 0```

### 输出

```
1
6
6```

# 题解

## 作者：FjswYuzu (赞：13)

半个出题人随便写点。

首先给出两个简单结论:

1. 一次操作相当于将 $v$ 数组整体左移一位（高位补零），然后 $v_i \gets \min(v_i-1,0)$；   
2. 一个合法的 $v$ 数组唯一对应一个合法的 $p$ 序列。

那么先看给出来的 $v$ 能不能构造一个合法的序列。在判断 $v$ 合法的时候我们一概不考虑 $-1$。

首先 $v$ 的后面 $k$ 位是 $0$，如果不是 $0$ 显然无解。

然后，如果 $v_i \geq i$，显然也无解，因为根本没有这么多位置。

那么判断完无解，因为 $v$ 唯一对应 $p$，考虑对 $v$ 计数。

我们先将操作前的 $p$ 数组对应的 $v'$ 数组还原。那么就是前 $k$ 位是 $-1$，后面的 $n-k$ 位取 $v$ 的前 $k$ 位并调整，调整方法是：

-  $v_i = -1$：不动就好了，   
-  $v_i = 0$：显然 $v'_i \leq k$，   
-  $v_i > 0$：$v'_i = v_i +k$。

那么我们还原了 $v'$，考虑计数。如果：

- $v_i$ 是 $-1$：因为 $v_i \in [0,i-1]$，那么乘上 $i$；    
- $v_i$ 唯一确定（也即调整方法中第三种方法）：唯一确定，贡献为 $1$；   
- $v_i$ 在 $[0,p]$ 内取值：有 $p+1$ 种取值，乘上就好了。

```cpp
void Solve()
{
	n=read(),k=read();
	for(int i=1;i<=n;++i)	a[i]=read();
	for(int i=1;i<=n;++i)
	{
		if(a[i]==-1)	continue;
		if(a[i]>i-1)
		{
			puts("0");
			return ;
		}
	}
	for(int i=n;i>=n-k+1;--i)
	{
		if(a[i]!=-1 && a[i])
		{
			puts("0");
			return ;
		}
	}
	int ans=1;
	for(int i=1;i<=k;++i)	ans=Mul(ans,i);
	for(int i=1;i<=n-k;++i)
	{
		if(a[i]==-1)	ans=Mul(ans,i+k);
		else if(a[i]==0)	ans=Mul(ans,k+1);
	}
	write(ans),puts("");
}
```

---

## 作者：Aleph_Drawer (赞：4)

我是 `*2500` 都不会的傻子。这题还是挺套路的题。

首先很容易注意到一个 $v$ 能够唯一确定一个 $a$。具体证明可以考虑从后往前一位一位的确定。接下来就和 $a$ 没有任何关系了。

首先注意到必须满足 $v_i < i$。否则 $v$ 不合法。

考虑题目描述的流程在做什么事情。本质上就是一次“冒泡”的过程。简单观察一下，考虑一个数 $a_i$，每次一定会有一个比 $a_i$ 大的数越过这个位置，并挪到后面的位置。这个表现在 $v$ 上就是，$v_i$ 往左边挪了一个位置，值变成了 $v_i - 1$。第 $n$ 个位置空了出来，显然是相对的最值，应当补一个 $0$。

有了这个就相当好做了。首先检查 $v$ 的合法性。注意到除了要满足 $v_i < i$ 之外，还要满足后 $k$ 个位置必须是 $0$。如果这两个条件有一个不满足答案就是 $0$。

我们已经知道一次“冒泡”操作是 $v'_i \leftarrow \max(v_{i + 1} - 1, 0)$。现在我们想还原回去。

首先我们要整体右移，然后在第一个位置补上一个 $-1$。对于原先已经有的 $-1$ 我们不管它；对于 $v_i > 0$ 的，显然在移动之后的 $v'$ 之中只有一个确定值 $v_i + 1$；对于 $v_i = 0$ 的情况则略微复杂。考虑移动 $k$ 次之后的情况，此时 $v_i = 0$ 的位置的取值可能为 $[0, k]$ 之间的任意一个。

事实上，我们只需要计数，那么我们并不需要模拟上述过程。

我们只需要考虑 $1 \sim n - k$ 位，对于 $v_i = -1$ 的位置，在最初的 $v$ 中可能的取值范围是 $[0, i + k - 1]$；对于 $v_i = 0$，在最初的 $v$ 中可能的取值范围是 $[0, k]$；对于 $v_i > 0$，在最初的 $v$ 中的取值只有一种 $v_i + k$。我们只需要做一做简单的乘法即可。最后别忘了给答案乘上 $k!$，因为最开始前面有 $k$ 个 $-1$。

哎呀，语言表述真是稀碎。看代码得了。

```c++
// Author : Aleph_Drawer

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 105;
const ll MOD = 998244353;

int t;
int n, k;
int v[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> t;
    for(; t; --t) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> v[i];
        ll ans = 1;
        for(int i = 1; i <= n; i++) {
            if(v[i] >= i) ans = 0;
        }
        for(int i = n; i >= n - k + 1; i--)
            if(v[i] != 0 && v[i] != -1) ans = 0;
        if(ans == 0) {
            cout << "0\n"; continue;
        }
        for(int i = 1; i <= k; i++)
            ans *= i, ans %= MOD;
        for(int i = 1; i <= n - k; i++) {
            if(v[i] == -1) ans *= (i + k), ans %= MOD;
            if(v[i] == 0) ans *= (k + 1), ans %= MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Exschawasion (赞：3)

翻译有误：不是一个长度为 $n$ 的**数组** $p$，而是一个长度为 $n$ 的**排列** $p$。

题意就是 $k$ 轮冒泡排序。结论题。为了避免疑惑，这里会说得尽量明白一些。

***

假设 $a_1,a_2,a_3,...,a_n$ 对应 $v_1,v_2,v_3,...,v_n$。现在取任意两个 $i,j$，且 $i<j$。然后交换 $a_i,a_j$。有两种情况：

- $a_j>a_i$，此时因为一个比 $a_i$ 大的数被放到了 $a_i$ 前面，必然 $v_j$（此时的 $j$ 位置上是 $a_i$）会至少增加 $1$，即 $v_i$ 变化。
- $a_j<a_i$，同理。

因此对于一个确定的 $a$，任何对它的操作都必然导致 $p$ 改变。

结论：对于一个确定且合法的 $v$，$p$ 是唯一确定的，反之亦然。

接着分析一轮冒泡排序之后 $v$ 的变化情况。对于第一个 $a_i>a_{i+1}$ 的 $i$，$a_i$ 将会不断往右 swap，这个过程相当于把 $a_i$ 右边的元素拉到左边来，拉到 $v_j=0$ 的 $j$ 的时候就停止。原因显然：$j$ 前面没有比 $a_j$ 大的元素，$a_i$ 也不例外；因此 $a_j>a_i$（且 $j>i$），无法进行交换。这时候 $a_i$ 前面的元素都是比 $a_i$ 小的，所以 $v_i=0$。

另外，交换的一个影响是比 $a_i$ 小的那些元素全都被往左边 swap 了，但是相对顺序没有变，且在它们前面**只有**一个 $a_i$ 消失了，因此 $v$ 变化是：舍弃最左端，**整体左移一位**，然后**整体减一**（与 $0$ 取 $\max$）。在最右边补上 $0$。

所以冒泡 $k$ 次，等价于所有的 $v$ 往左移 $k$ 位，且整体 $-k$，末尾 $k$ 位都是 $0$。

因为 $p$ 与 $v$ 一一对应，所以 $p$ 方案数等于 $v$ 方案数。需要做的就是根据 $v'$ 确定 $v$。讨论 $v'$ 的情况：

- 对于 $i \leq k$，根据上面的结论，$v_i=0$；
- $v'_i$ 不确定，此时可以任意取，$[0,i-1]$；
- $v'_i=0$，因为这里有个与 $0$ 取 $\max$ 的过程，所以不能唯一确定原来的 $v_i$，即原来的 $v_i$ 可能是 $[0,k]$ 之间的任何数；
- $v'_i>0$’，此时 $v_i$ 唯一确定，为 $v'_i+k$。

还要考虑无解：

- $v_i\ge i$。第 $i$ 个数前面不可能有超过 $i-1$ 个数都比 $a_i$ 大。
- 对于 $i \leq k$，$v_i\not =0$。根据上面的结论，末 $k$ 位肯定是 $0$。

代码非常简单，就不放了。

---

## 作者：123456xwd (赞：2)

### [「CF1677D」Tokitsukaze and Permutations](https://www.luogu.com.cn/problem/CF1677D)

首先，若 $v$ 的后 $k$ 个数中有一个 $>0$，或有 $v_i>i-1(i\in[1,n])$，则无解。

我们发现，每次对 $p$ 进行了一次操作后，$v$ 也一定会对应的进行一次变化，所以统计 $p$ 的个数就相当于统计 $v$ 的个数。

我们对于每一次冒泡排序，有两种情况：

1. 若 $\max_{1\le j\le i}\{p_j\}<p_{i+1}$，则 $v_{i+1}=0$，而 $v_i=0$。
2. 若 $\max_{1\le j\le i}\{p_j\}>p_{i+1}$，则 $v_{i+1}>0$，而 $v_i=\max\{0,v_{i+1}-1\}$。

我们现在知道了变化后的 $v$（设其为 $v'$），求出多少个原始的 $v$，就求出来多少个 $p$。

进行了 $k$ 轮冒泡排序，则 $v_{i}=\max\{0,v’_{i-k}-k\}$。

那么，有：

1. $1\le i \le k$：$v_i$ 可以取合法的任意值，也就是 $[0,i-1]$。

2. $k<i\le n$：若 $v'_{i-k}=0$，则 $v_i$ 可能为 $[0,k]$；若 $v'_{i-k}=-1$，则取任意值 $[0,i-1]$；否则的话只有一种情况。

乘法原理一乘即可。

代码：
```c++
#include<bits/stdc++.h>
#define p_b push_back
#define m_p make_pair
#define int long long
using namespace std;

const int N=1e6+5,mod=998244353;
int n,k,v[N];
void solve(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&v[i]);
	for(int i=1;i<=n;i++){
		if(v[i]>i-1){
			puts("0");
			return;
		}
	} 
	for(int i=n;i>=n-k+1;i--){
		if(v[i]>0){
			puts("0");
			return;
		}
	} 
	int ans=1;
	for(int i=1;i<=k;i++) ans=(ans*i)%mod;
	for(int i=k+1;i<=n;i++){
		if(v[i-k]==0) ans=(ans*(k+1))%mod;
		if(v[i-k]==-1) ans=(ans*i)%mod;
	} 
	printf("%lld\n",ans);
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--){
		solve();
	} 
	return 0;
} 
```

---

## 作者：Renshey (赞：2)

#### 题意

给定排列 $\{p_n\}$，进行 $k$ 轮冒泡排序，每轮过程如下：

```cpp
for (int i = 1; i < n; i++) if (p[i] > p[i + 1]) std::swap(p[i], p[i + 1]);
```

定义 $v_i = \sum_{j=1}^{i-1} [a_j > a_i]$，给定 $k$ 轮冒泡排序后的 $\{v_i\}$，若干位置可以任意选择，求初始的排列的数量，对 $998244353$ 取模。

#### 数据范围

$n \le 10^6$

#### 题解

**性质一：每轮冒泡排序后，$v'_i = \max\{v_{i+1} - 1,0\}$**。

**性质二：所有合法的 $\{v_n\}$ 与排列 $\{p_n\}$ 构成双射。**

证明从略，但不难感性理解。

由此要求 $v_{n-k+1}=v_{n-k+2}=\dots=v_n=0$，否则无解。

考虑直接初始的 $\{v_n\}$ 计数，记为 $\{a_n\}$。

对于 $1 \le i \le k$，$a_i$ 可以任取 $[0,i)$ 中的数。

对于 $k + 1\le i \le n$，$v_{i - k} = \max\{a_i - k, 0\}$。若 $v_{i-k}$ 任取则有 $i$ 种取法，若 $v_{i-k}$ 为 $0$ 则有 $k+1$ 种取法，否则只有唯一一种。

直接用乘法原理计算答案即可。

时间复杂度和空间复杂度均为 $O(n)$。

#### 代码

```cpp
#include <bits/stdc++.h>
#define Getchar() p1 == p2 and (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++
char buf[1 << 21], *p1, *p2;
inline int read (void)
{
	int x = 0; char c = Getchar(); bool f = (c != '-');
	while (c < '0' or c > '9') c = Getchar(), f &= c != '-';
	while (c >= '0' and c <= '9') x = x * 10 + c - 48, c = Getchar();
	return f ? x : -x;
}
const int mod = 998244353;
int n, k, a[1000010], ans;
inline void solve (void)
{
	n = read(); k = read(); ans = 1;
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = n - k + 1; i <= n; i++) if (a[i] > 0) {puts("0"); return;}
	for (int i = 1; i <= k; i++) ans = 1LL * ans * i % mod;
	for (int i = 1; i <= n - k; i++) if (a[i] == -1) ans = 1LL * ans * (k + i) % mod;
	for (int i = 1; i <= n - k; i++) if (a[i] == 0) ans = 1LL * ans * (k + 1) % mod;
	printf("%d\n", ans);
}
signed main ()
{
	for (int T = read(); T--; ) solve();
	return 0;
}
```

---

## 作者：MatrixCascade (赞：2)

首先，设 $\sum\limits_{j=0}^i[p_j>p_i]=f_i$，那么 $0 \le f_i\le i-1$，并且 $f$ 序列与排列一一对应。

然后对于每一次冒泡操作，相当于 $f_i=\max(f_{i+1}-1,0)$，那么 $k$ 次操作相当于 $f_i=\max(f_{i+k}-k,0)$。然后就很好做了。

具体的，对于 $1\le i\le k$，每个 $i$ 都能选 $[0,i-1]$，共 $i$ 钟选法。剩下的情况，若 $a_{i-k}=0$ 则能选 $[0,k-1]$，共 $k$ 种选法。若 $a_{i-k}=-1$，那么能选 $[0,i-1]$，共 $i$ 种选法。否则的话就是一个定值，共 $1$ 种选法。

注意判一下不合法，就是后 $k$ 个数不能出现 $>0$ 的数，如果出现了答案就是 $0$。

[赛时代码](https://codeforces.com/contest/1677/submission/156345926)，其实挺短的...

---

## 作者：NY2025 (赞：0)

## $\text{Task}$

题目链接：[Tokitsukaze and Permutations](https://codeforces.com/problemset/problem/1677/D)

定义 $1\sim n$ 的排列 $p$ 的权值数组 $\{v_i\}_{i=1}^{n}$，其中 $v_i=\sum_{j=1}^{i-1}[a_i<a_j]$。   
给定排列 $p$ 经过 $k$ 轮冒泡后得到的新的排列 $a$ 的 $v$ 数组，求原排列可能情况数量。

## $\text{Solution}$

考虑对于一个给定的 $v$ 数组，对应的可能的排列 $a$ 的数量。

可以明确的是，如果 $v$ 中所有元素均不为 $-1$，$a$ 可以被唯一确定，因此统计时只用考虑 $-1$ 的影响，而若 $v_i=-1$，实际上等价于 $v_i$ 在 $0\sim i-1$ 中任取，因此 $v$ 对应的排列 $a$ 数量为 $\prod_{i=1}^{n}i^{[v_i=-1]}$。

显然通过 $a$ 的数量统计 $p$ 的个数是不可做的。由于前缀偏序数量与冒泡排序的相关性，可以考虑还原出原排列 $p$ 的权值数组 $v'$。


首先排除掉不合法情况：

1. $v$ 数组后 $k$ 个元素不等于 $0$ 或 $-1$。
2. $v_i\geq i$。

解释：

1. $k$ 轮冒泡后最大的 $k$ 个元素一定处在末尾且呈升序排列。
2. 显然。

对于 $v'$ 的还原，首先考虑冒泡对 $v$ 的影响，显然一轮冒泡后，$v_i\leftarrow \max(v_{i+1}-1,0)$。

根据如上性质，同样可以分情况考虑。$v'$ 的前 $k$ 位元素设为 $-1$，$v'$ 的后 $n-k$ 位元素由 $v$ 的前 $n-k$ 位确定，具体如下：

1. $v_i\geq 1$，$v_i'=v_i+k$。
2. $v_i=-1$，即 $v_i\in[0,i-1]$，因此 $v_i'\in[0,i+k-1]$。
3. $v_i=0$，$v_i'\in[0,k]$。

此时套用最初的方法，根据 $v'$ 数组求出排列 $p$ 的数量即可。

## $\text{Code}$

```c++
#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
const int N = 1e6+10;
const int MOD = 998244353;
 
int n, k, v[N];
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			if (v[i] >= i) flag = false;
			if (i >= n-k+1 && v[i] && (v[i] != -1)) flag = false;
		}
		if (!flag) printf("%d\n", 0);
		else {
			LL rst = 1;
			for (int i = 1; i <= n-k; i++) {
				if (v[i] == -1) rst = (LL)rst*(i+k)%MOD;
				else if (v[i] == 0) rst = (LL)rst*(k+1)%MOD;
			}
			for (int i = 1; i <= k; i++) rst = (LL)rst*i%MOD;
			printf("%lld\n", rst);
		}
	}
	return 0;
}
```

---

## 作者：TankYu (赞：0)

先考虑是否合法。

每轮冒泡排序必然使乱序部分的最大值到正确的位置上。

所以 $k$ 轮冒泡排序必然使数列中最大的 $k$ 个数归位，也就是说，$v$ 最后 $k$ 个数是 $0$ 或 $-1$。

然后，显然 $v_i \ge i$ 是不合法的。

下面考虑构造这个 $a$。

思考每次冒泡对 $v$ 有什么贡献。

考虑这个移动的过程，这个等价于每次将 $v$ 左移一位，高位补 $0$，接下来每个 $v_i = \max(v_i - 1,0)$。

然后另有一个结论：不考虑 $-1$ 的情况下，$v$ 和 $a$ 构成双射。

显然每一个 $a$ 对应唯一的 $v$，只需证明每一个 $v$ 描述一个 $a$。

考虑倒着构造，具体地，将所有仍未出现的 $i$ 排序后所成数列记作 $b$，则 $a_{i} = b_{i - v_i}$，然后把 $b_{i - v_i}$ 从 $b$ 中删去。

综上，双射成立。

所以问题就是对所有可能的 $v$ 计数。

由那个移位操作，只需考虑前 $n - k$ 项和后面 $k$ 个 $-1$ 的贡献。

若 $v_i > 0$ 则最开始的 $v_i$ 是定值。否则若 $v_i = 0$，则最开始的 $v_i - k \le 0$，其取值在 $[0,k]$ 中，共 $k + 1$ 个。若 $v_i = -1$，只需令其有解，其取值范围在 $[0,i+k-1]$ 中，共 $i+k$ 个。

乘起来得到答案。

```cpp
int v[2000010];
int n, k;
const LL mod = 998244353;
bool check()
{
    for (int i = n - k + 1; i <= n; i++)
    {
        if (v[i] > 0 || v[i] >= i)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
        {
            cin >> v[i];
        }
        if (!check())
        {
            cout << "0\n";
        }
        else
        {
            LL ans = 1;
            for (int i = 1; i <= n - k; i++)
            {
                if (v[i] == -1)
                {
                    ans *= (i + k);
                    ans %= mod;
                }
                else if (v[i] == 0)
                {
                    ans *= (k + 1);
                    ans %= mod;
                }
            }
            for (int i = 1; i <= k; i++)
            {
                ans *= i;
                ans %= mod;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
```

---

