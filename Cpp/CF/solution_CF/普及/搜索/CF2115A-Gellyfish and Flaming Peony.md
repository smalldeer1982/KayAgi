# Gellyfish and Flaming Peony

## 题目描述

Gellyfish hates math problems, but she has to finish her math homework:

Gellyfish is given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ .

She needs to do the following two-step operation until all elements of $ a $ are equal:

1. Select two indexes $ i $ , $ j $ satisfying $ 1 \leq i, j \leq n $ and $ i \neq j $ .
2. Replace $ a_i $ with $ \gcd(a_i, a_j) $ .

Now, Gellyfish asks you for the minimum number of operations to achieve her goal.

It can be proven that Gellyfish can always achieve her goal.

## 说明/提示

In the first test case, the following is a way that minimizes the number of operations:

1. Choose $ i = 3 $ and $ j=2 $ and replace $ a_3 $ with $ \gcd(a_3,a_2) = \gcd(30, 20) = 10 $ , then $ a $ becomes $ [12, 20, 10] $ .
2. Choose $ i=1 $ and $ j=3 $ and replace $ a_1 $ with $ \gcd(a_1,a_3) = \gcd(12, 10) = 2 $ , then $ a $ becomes $ [2, 20, 10] $ .
3. Choose $ i=2 $ and $ j=1 $ and replace $ a_2 $ with $ \gcd(a_2,a_1) = \gcd(20, 2) = 2 $ , then $ a $ becomes $ [2, 2, 10] $ .
4. Choose $ i=3 $ and $ j=1 $ and replace $ a_3 $ with $ \gcd(a_3,a_1) = \gcd(10, 2) = 2 $ , then $ a $ becomes $ [2, 2, 2] $ .

## 样例 #1

### 输入

```
3
3
12 20 30
6
1 9 1 9 8 1
3
6 14 15```

### 输出

```
4
3
3```

# 题解

## 作者：ax_by_c (赞：1)

训练赛考了加强版，自己推出来了，来写一下。

首先对于这个题最后肯定是变成全局的 $\gcd$，那么大可直接把所有数全部除以全局 $\gcd$。那么出现 $1$ 之后就可以把所有不是 $1$ 的都变了。特判已经存在 $1$ 的情况，只需要求出最小的集合使得其内部的数的 $\gcd$ 为 $1$。

考虑 DP，设 $f_i$ 为最小的集合使得其内部的数的 $\gcd$ 为 $i$ 的方案数，答案即为 $f_1$。

考虑判断能否 $f_i\leftarrow f_j+1$，即要存在 $a_x$ 使得 $\gcd(j,a_x)=i$。

枚举 $i$ 后只考虑 $i$ 的倍数，尝试直接算 $\sum[\gcd(\frac{j}{i},\frac{a_x}{i})=1]$，直接上莫反可得 $\sum_{d\mid \frac{j}{i},d\mid\frac{a_x}{i}}\mu(d)$。

算出 $\sum_{d\mid\frac{a_x}{i}}\mu(d)$ 直接枚举因数即可，时间复杂度 $O(\sum_{i=1}^{V}\lfloor\frac{V}{i}\rfloor\log \lfloor\frac{V}{i}\rfloor)=O(V\log^2V)$。

---

## 作者：convie (赞：1)

这道题可以用 dp 来写，但我用的是 BFS，题目的问题就是对于一个给定的数组，如何用最小的次数使得整个数组变为整个数组的最大公约数 $cn$，显然，当数组中存在 $ans$ 个数是最大公约数时，整个数组的修改次数为 $n-ans$。

但当数组中不存在这样的最大公约数时，问题就转换为了如何用最少的元素使得这些元素的最大公约数为 $cn$，可以采用 BFS 的方法，用 vector 容器存储每次更改后的值，为了减少时间复杂度，需要对每次的操作进行元素的去重，因为数据范围比较小，大常数也能过，代码如下。
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
#define ios ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define MAXN 5010
#define x first
#define y second
typedef pair<int,int> PII;
int a[MAXN];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int cn=a[1];
	for(int i=1;i<=n;i++)cn=__gcd(cn,a[i]);
	int ans=0;
	for(int i=1;i<=n;i++)
	if(a[i]==cn)ans++;
	if(ans){
		cout<<n-ans<<endl;
		return ;
}
	vector<int> q;
	ans=0;
	for(int i=1;i<=n;i++)
	if(a[i]!=0)
	q.push_back(a[i]);
	sort(q.begin(),q.end());
	q.erase(unique(q.begin(),q.end()),q.end());
	while(1){
		ans++;
		bool flag=false;
		vector<int> cm;
		for(int i=0;i<q.size();i++)
		for(int j=1;j<=n;j++){
			int cx=__gcd(q[i],a[j]);
			cm.push_back(cx);
			if(cx==cn){
				flag=true;
				break;
			}
		}
		if(flag)break;
		sort(cm.begin(),cm.end());
		cm.erase(unique(cm.begin(),cm.end()),cm.end());
		q=cm;
	}
//	cout<<ans<<" "<<cn<<endl;
	cout<<n-1+ans<<endl;
}
signed main(){
	ios;
	int t=1;
	cin>>t;
	while(t--)
	solve();
	return 0;
}
```

---

## 作者：lhz2022 (赞：1)

首先一个十分显然的点是最后数组中的数都是 $v=\gcd_{i=1}^na_i$。

有一个比较显然的策略就是将一个数先变成 $v$ , 然后对其他数分别进行操作，这样就全变成 $v$ 了。

我们可以得出 $a$ 中所有的数都是 $v$ 的倍数，所以 $(a_i,v)=v$，所以只需一次操作就可以将任意数变成 $v$，这就能够保证这种操作是最优的。

那么我们的首要任务就是将一个数变成 $v$，这时就有很多方法了，比如我们可以用一种 bfs 的方法。

```cpp
int a[N];
int n;
int vis[N];
int ggcd;
int que[N];
int bfs(){
	int ll=1,rr=0;
	for(int i=1;i<=n;++i){
		if(vis[a[i]]==-1){
			vis[a[i]]=0;
			que[++rr]=a[i];
			if(a[i]==ggcd) return 1;
		}
	}
	while(ll<=rr){
		int u =que[ll++];
		for(int i=1;i<=n;++i){
			int t=__gcd(a[i],u);
			if(vis[t]==-1){
				que[++rr]=t;
				vis[t]=vis[u]+1;
				if(t==ggcd) return vis[t];
			}
		}
	}
	return 0;
}
```

我们来看一下时间复杂度，看上去它是 $O(n^2\log n)$ 的，但是再感性的理解一些，发现根本跑不满（尤其是本题的 $a_i$ 很小）。于是我们就以一种很~~乱搞~~高效的方式知道将一个数字变成 $v$ 最小要花多少步。

然后就完善一些输入输出之类的，就搞定了。

[扔一坨代码](https://www.luogu.com.cn/paste/6yj78hvm)

---

## 作者：chenmingeng (赞：0)

题意：给定一个包含 $n$ 个正整数的数组 $a$。任意次操作：选择两个索引 $i$ 和 $j$，然后将 $a_i$ 的值更新为 $\gcd(a_i, a_j)$。求出让数组中所有元素都相等所需的最少操作次数。

官方题解给出了本题的 Bonus 版本：Try to solve $n, a_i \leq 2 \times 10^5$ with only one test case. 设值域为 $V$，期望复杂度 $\mathcal{O}(V\log V)$。

---

所有元素最终必然会相等，且等于整个初始数组的 GCD。问题的核心就变成了如何求得最小的 GCD。

考虑到求得最小的 GCD 需要的数不会很多，事实上最大只会是 $\max\omega(V)=8$，即 $V$ 以内一个数的最大素因子个数。

我们采用迭代的方式求解：维护迭代 cnt 轮次后可以被凑出来的数。循环 $\max\omega(V)$ 轮次后就找出答案，每轮迭代期望复杂度 $\mathcal{O}(V\log V)$。

设 
- $f(i)$: 初始数组中数字 $i$ 的出现次数，
- $g(i)$: 数字 $i$ 当前是否可以被凑出来。

每一轮迭代需要用 $f$ 来更新 $g$，具体来说是 $g(i)$ 将被赋值为：是否有可能从 $f$ 中选一个数 $x$，再从 $g$ 选一个数 $y$，且其最大公约数 $\gcd(x, y)=i$。

$x$ 和 $y$ 都一定是 $i$ 的倍数，枚举 $i$ 的倍数（两个 log），加上 gcd 的判断（一个 log），复杂度 $\mathcal{O}(V\log^{3} V)$。

总的复杂度 $\mathcal{O}(V\log^{3} V\max\omega(V))$，跑 2e5 的数据还是有点危险的。

---

进一步优化，引入辅助数组
- $h(i)$ 表示：是否有可能从 $f$ 中选一个数 $x$，再从 $g$ 选一个数 $y$，且其最大公约数 $\gcd(x, y)$ 是 $i$ 的倍数。

这样 $x$ 和 $y$ 都一定是 $i$ 的倍数，通过枚举倍数在 $\mathcal{O}(V\log V)$ 的时间就能求出 $h$ 数组。

显然 $\displaystyle h(n)=\sum_{k}g(nk)$，为用 $h$ 表示 $g$ 需要用到莫比乌斯反演：
$$
\begin{aligned}
f(n)=\displaystyle \sum_{d \mid n} g(d)
&\quad\iff\quad 
g(n)=f(n)\ast\mu(n)=\sum_{d \mid n} \mu(d)\cdot f\Big(\frac{n}{d}\Big) 
\\
f(n) = \sum_{d=1}^{\infty} g(n d)
&\quad\iff\quad 
g(n) = \sum_{d=1}^{\infty} \mu(d) \cdot f(n d)
\end{aligned}
$$
其中莫比乌斯函数 $\mu(n) = \begin{cases} 1, & n = 1 \\ 0, & \exists d > 1, d^{2} \mid n \\ (-1)^{\omega(n)}, & \text{otherwise}\end{cases}$ 可以用欧拉筛线性预处理。

这样 $\displaystyle g(n) = \sum_{k}\mu(k) \cdot h(n k)$，在 $\mathcal{O}(V\log V)$ 的时间内通过 $h$ 求出 $g$。

总的复杂度 $\mathcal{O}(V\log V\max\omega(V))$。跑 5e5 甚至 1e6 也是没问题的。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4;
vector<int> prime;
int minp[N];   // 最小素因子
int mu[N];     // 莫比乌斯函数

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    int d = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        d = gcd(d, a[i]);
    }

    int cnt = count(a.begin(), a.end(), d);
    if (cnt) {
        cout << (n - cnt) << endl;
        return;
    }

    const int V = *max_element(a.begin(), a.end()) + 1;

    vector<int> f(V);       // f[i]: 初始数组中数字 i 的出现次数
    vector<int> g(V);       // g[i]: 数字 i 当前是否可以被凑出来

    for (auto x : a) {
        f[x] = 1;
        g[x] = 1;
    }

    for (int cnt = 1; ; cnt++) {
        vector<int> h(V);
        for (int i = 1; i < V; i++) {
            int sumf = 0;
            int sumg = 0;
            for (int j = i; j < V; j += i) {
                sumf += f[j];
                sumg += g[j];
            }
            h[i] = sumf * sumg;
        }
        for (int i = 1; i < V; i++) {
            g[i] = 0;
            for (int k = 1; i * k < V; k++) {
                g[i] += mu[k] * h[i * k];
            }
        }
        if (g[d] > 0) {
            cout << (cnt + n - 1) << endl;
            return;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    minp[1] = 1;
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!minp[i]) {
            minp[i] = i;
            prime.push_back(i);
            mu[i] = -1;
        }
        for (auto p : prime) {
            if (i * p >= N) break;
            minp[i * p] = p;
            if (p == minp[i]) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }

    for (int t = (cin >> t, t); t--; )
        solve();

    return 0;
}
```

---

评注：
1. 数论中很多东西不太大，比如素数距离和素因子个数等，看似有好几层循环实际上很小。
2. 「恰好」不好做，尝试转化为「至少」或「至多」，再反演得到结果。本题是把 GCD 恰好等于某数转化为 GCD 是某数的倍数。

---

## 作者：_O_v_O_ (赞：0)

很显然当某个数为 $\gcd_{i=1}^n a_i$ 时，那么我们可以用 $n-1$ 次操作即可达成目标。

那么我们就考虑要咋把某个数变成 $x=\gcd_{i=1}^n a_i$。

假设我们要把 $a_1$ 变成 $x$，那么题目就等价于选择一个大小最小的集合 $S$ 满足 $\gcd\{\gcd_{x\in S} a_x,a_1\}=\gcd_{i=1}^n a_i$。

那么我们考虑 dp，设 $dp_{i,j}$ 为前 $i$ 个数，$\gcd=j$ 时最最小集合，那么很显然有 $dp_{i,\gcd_{a_i,j}}=\max\{dp_{i,\gcd_{a_i,j}},dp_{i-1,\gcd_{a_i,j}},dp_{i-1,j}+1\}$。

预处理 gcd，时间复杂度 $O(nV\log V)$，常数小所以确实能过。

[code](https://codeforces.com/contest/2116/submission/322229627)

---

## 作者：chaojidashuaitong (赞：0)

题目翻译：给定一个 $N$ 个元素的数组 $A$。你可以进行以下操作若干次：
- 选择两个正整数 $i,j(1\le i,j\le N)$。
- 将 $A_i$ 变成 $\gcd(A_i,A_j)$，其中 $\gcd(x,y)$ 表示 $x,y$ 的最大公约数。

求把 $A$ 数组的元素都相同的操作最小次数。$1\le N,A_i\le 5\times 10^3$。

---

显然最后的数组 $A$ 里面的元素为 $A$ 所有元素的最大公约数。所以我们把题目变一下：
先把 $A$ 里所有元素都除以一个 $A$ 数组的所有最大公约数，然后就把问题转换成了把 $A$ 数组元素全变成 $1$ 的最小次数了。

手玩几个样例可以发现：
- 如果 $A$ 数组存在为 $1$ 的元素，则答案就为 $A$ 中不为 $1$ 的元素数量，因为每个不为 $1$ 的元素只需要对 $1$ 进行一次操作就行。
- 如果不存在，则求出把 $A$ 数组中任意一个元素变为 $1$ 的最小次数 $X$，然后再按上面的办法，操作次数为 $X+N-1$。

如何求出呢？
考虑分解质因子。显然 $\gcd(A_i,A_j)$ 的结果的质因子集合为 $A_i$ 的质因子集合与 $A_j$ 的质因子集合的**交集**。
所以只要 $A_j$ 没有 $A_i$ 的某个质因子，$\gcd$ 操作后 $A_i$ 的这个质因子也会消失。
我们可以求出所有 $A_i$ 有的而 $A_j$ 没有的质因子集合，然后想办法凑出个和 $A_i$ 质因子集合相同的集合（就是每个元素都得有）。
不难想到 DP。DP 代码也很好写，枚举每一个 $A_j$ 选还是不选即可。

[代码](https://www.luogu.com.cn/paste/f9l8msg6)。

我们看看时间复杂度：
显然 $5000$ 范围内，一个数顶多有 $5$ 个质因子。所以质因子集合大小不超过 $5$。
所以总时间复杂度为 $O(\sum n^2\times 2^k)$，其中 $k=5$。
最大计算次数为 $8\times 10^8$，会超时。
思考一下怎么优化。

#### 优化 1

我们发现总共的状态总数也不超过 $2^k$ 个，而重复的状态是无效的，只需保留一个即可。
所以我们可以用这种方法大大减小 DP 的状态数。
时间复杂度降低为 $O(\sum (n^2\times k+n\times (2^k)^2))$。

#### 优化 2
注意到有 $5$ 个不同质因子的只有 $7$ 个数，有 $4$ 个的只有 $336$ 个数。
而且显然重复的 $A_i$ 对降到 $1$ 没有任何作用，所以我们去重一下，就可以把实际的 $k$ 降到 $3$ 左右了。

[代码在这](https://www.luogu.com.cn/paste/l3hrgvqe)。

测了一下，202ms。[提交记录](https://codeforces.com/contest/2116/submission/322463607)

---

