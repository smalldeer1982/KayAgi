# [ARC155D] Avoid Coprime Game

## 题目描述

对于两个非负整数 $x, y$，$\gcd(x, y)$ 表示 $x$ 和 $y$ 的最大公约数（其中，当 $x=0$ 时，$\gcd(x, y)=\gcd(y, x)=y$）。

黑板上写有 $N$ 个整数，第 $i$ 个整数为 $A_i$。这 $N$ 个整数的最大公约数为 $1$。

高桥君和青木君进行一场对战游戏。初始时整数 $G=0$，两人轮流操作，高桥君先手。每次操作如下：

- 从黑板上选择一个满足 $\gcd(G, a) \neq 1$ 的数 $a$，将其擦去，并用 $\gcd(G, a)$ 替换 $G$。

无法进行操作的一方判负。

对于每个 $i\ (1\leq i \leq N)$，请判断如果高桥君在第一回合选择第 $i$ 个整数，之后双方都采取最优策略，最终谁会获胜。

## 说明/提示

### 限制条件

- $2 \leq N \leq 2 \times 10^5$
- $2 \leq A_i \leq 2 \times 10^5$
- $N$ 个整数 $A_i\ (1\leq i \leq N)$ 的最大公约数为 $1$
- 输入均为整数

### 样例解释 1

例如，如果高桥君在第一回合选择第 $4$ 个整数 $A_4=6$，青木君可以选择第 $2$ 个整数 $A_2=3$，此时 $G=3$。之后高桥君无法再选择任何整数，因此青木君获胜。所以第 $4$ 行应输出 `Aoki`。

### 样例解释 2

黑板上可能会有多个相同的整数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2 3 4 6```

### 输出

```
Takahashi
Aoki
Takahashi
Aoki```

## 样例 #2

### 输入

```
4
2 155 155 155```

### 输出

```
Takahashi
Takahashi
Takahashi
Takahashi```

## 样例 #3

### 输入

```
20
2579 25823 32197 55685 73127 73393 74033 95252 104289 114619 139903 144912 147663 149390 155806 169494 175264 181477 189686 196663```

### 输出

```
Takahashi
Aoki
Takahashi
Aoki
Takahashi
Takahashi
Takahashi
Takahashi
Aoki
Takahashi
Takahashi
Aoki
Aoki
Aoki
Aoki
Aoki
Takahashi
Takahashi
Aoki
Takahashi```

# 题解

## 作者：Leasier (赞：16)

每次操作完后 $G$ 可以不变比较难以处理，考虑先解决**每轮结束后强制 $G$ 必须变小**的情况。

设 $SG(i)$ 表示 $G = i$ 时先手还是后手获胜。这里我们需要枚举一个初始的 $G$。

初值：$SG(1) = \operatorname{false}$。

转移：$SG(i) = \operatorname{or}_{j < i, j \mid i} [\exists 1 \leq k \leq n, \gcd(i, a_k) = j] (\operatorname{not} SG(j))$。这里判断存不存在一个 $k$ 可以容斥预处理。

但事实上 $G$ 不一定必须变小，所以说我们实际上可以考虑**拖时间**。

具体地，若合法后继局面只有 $\operatorname{true}$，先后手都会选择拖时间。

进而我们会关心到目前为止只操作了几次——因为 $G = i$ 时，之前操作的一定都是 $i$ 的倍数。

于是我们可以进而设 $SG(i, 0/1)$ 表示到 $G = i$ 时已经操作了偶数 / 奇数次。

转移：基本与前述相同，但在所有合法后继状态均为 $\operatorname{true}$ 时，$SG(i, cnt_i \bmod 2) = \operatorname{true}$。

时间复杂度为 $O(n + N \log^2 N)$。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 2e5, M = 1 + 7;
int a[N + 7], cnt1[N + 7], cnt2[N + 7], sg[N + 7][M];
vector<int> v[N + 7];

int main(){
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		cnt1[a[i]]++;
	}
	for (int i = 2; i <= N; i++){
		for (int j = i; j <= N; j += i){
			v[j].push_back(i);
			if (i < j) cnt1[i] += cnt1[j];
		}
	}
	for (int i = 2; i <= N; i++){
		int size1 = v[i].size();
		bool flag = false;
		for (int j = 0; j < size1; j++){
			cnt2[v[i][j]] = cnt1[v[i][j]];
		}
		for (int j = size1 - 1; j >= 0; j--){
			int x = v[i][j], size2 = v[x].size() - 1;
			if (j < size1 - 1 && cnt2[x] != 0){
				if (!sg[x][1]) sg[i][0] = flag = true;
				if (!sg[x][0]) sg[i][1] = flag = true;
			}
			for (int k = 0; k < size2; k++){
				cnt2[v[x][k]] -= cnt2[x];
			}
		}
		if (!flag) sg[i][cnt1[i] % 2] = true;
	}
	for (int i = 1; i <= n; i++){
		if (sg[a[i]][0]){
			cout << "Aoki" << endl;
		} else {
			cout << "Takahashi" << endl;
		}
	}
	return 0;
}
```

---

## 作者：Felix72 (赞：2)

设状态 $f_{x, 0 / 1} = 0 / 1$ 表示当前全局 $\gcd$ 为 $x$，且局面中存在的**$x$ 的倍数的个数**是偶数或奇数是，先手的胜负性。

转移是枚举 $y$ 满足 $ky = x$，并分别判断 $f_{y, op_y} \to f_{x, op_x}$ 是否可以转移。判断的依据是是否存在 $a_i$ 使得 $\gcd(a_i, x) = y$。我们要做的就是快速求函数 $G(x, y)$ 表示 $\gcd(a_i, x) = y$ 的 $i$ 个数。

令 $cnt_x = \sum_{i = 1}^{n} [a_i = x]$，常数 $m = 2 \times 10^5$。

$$G(x, y) = \sum_{i = 1}^{n}[\gcd(a_i, x) = y]$$
$$=\sum_{i = 1}^{\lfloor \frac{m}{y} \rfloor} [\gcd(\frac{x}{y}, i) = 1]cnt_{iy}$$

到这就能莫比乌斯反演，得

$$G(x, y) = \sum_{d | \frac{x}{y}} \mu(d) \sum_{d|i} cnt_{iy}$$

$G(x, y) \neq 0$ 的 $(x, y)$ 二元组数量最多 $O(m\log m)$ 个，可以用这个式子预处理出来。

得到 $G$ 的 $O(1)$ 求法之后就可以转移了。

```cpp
 /* NE_Cat 4.3 */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 200010;
int n, m = 200000, a[N], cnt[N], w[N]; bool f[N][2];
vector < int > fact[N], dp[N]; int cur[N], w_cur[N];
inline int Gcd(int x, int y) {return ((y == 0) ? x : Gcd(y, x % y));}

int pri[N], pn, mu[N]; bitset < N > vis;
inline void get_prime()
{
	mu[1] = 1;
	for(int i = 2; i <= m; ++i)
	{
		if(!vis[i]) pri[++pn] = i, mu[i] = -1;
		for(int j = 1; j <= pn && pri[j] * i <= m; ++j)
		{
			mu[pri[j] * i] = mu[i] * -1;
			vis[pri[j] * i] = true;
			if(i % pri[j] == 0)
			{
				mu[pri[j] * i] = 0;
				break;
			}
		}
	}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i], ++cnt[a[i]];
	for(int i = 1; i <= m; ++i)
		for(int j = i; j <= m; j += i)
			fact[j].push_back(i), w[i] += cnt[j];
	for(int i = 1; i <= m; ++i) dp[i].resize(m / i + 5);
	get_prime();
	for(int y = 1; y <= m; ++y)
	{
		int mx = m / y;
		for(int i = 1; i <= mx; ++i) cur[i] = cnt[i * y], w_cur[i] = 0;
		for(int i = 1; i <= mx; ++i)
			for(int j = i; j <= mx; j += i)
				w_cur[i] += cur[j];
		for(int i = 1; i <= mx; ++i)
			for(int d : fact[i])
				dp[y][i] += mu[d] * w_cur[d];
	}
	for(int i = 2; i <= m; ++i)
	{
		for(int op = 0; op <= 1; ++op)
		{
			if(op == 1 && !f[i][0]) f[i][op] = true;
			for(int j : fact[i])
			{
				if(j == i || j == 1) continue;
				if(!dp[j][i / j]) continue;
				if(!f[j][op ^ ((w[j] - w[i] - 1) % 2)]) f[i][op] = true;
			}
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		if(!f[a[i]][(w[a[i]] - 1) % 2])
			cout << "Takahashi" << '\n';
		else cout << "Aoki" << '\n';
	}
	return 0;
}
/*

*/
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc155_d)

**题目大意**

> 给定 $a_1\sim a_n$ 和 $x=0$，A 和 B 轮流选择 $a_i$ 并令 $x\gets\gcd(x,a_i)$，不能重复用 $a_i$，谁把 $x$ 变成 $1$ 就输。
>
> 对于每个 $a_i$，求出 A 第一步操作该数后谁会赢。
>
> 数据范围：$n\le2 \times 10^5$。

**思路分析**

注意到 $x\mid a_i$ 比较麻烦，否则如果每次 $x$ 严格变小，我们可以简单 dp 求胜负态。

设 $f_x$ 表示当前胜负状态，那么 $f_x=\mathrm{OR}\{\overline{f_y}\mid\exists a_i:\gcd(a_i,x)=y\}$，容易证明这一步取的 $a_i$ 不可能被取过。

判断是否存在 $a_i$ 是简单的，先求每个 $x$ 的倍数数量，然后从大到小枚举 $y\mid x$，把 $y$ 的因子中 $a_i$ 作为倍数的数量出现次数减去 $y$ 的倍数的数量。

但是我们现在可能可以不让 $x$ 变小，即拖延时间。

我们发现一个人会拖延时间当且仅当 $f_x=0$，那么两个人会拖延时间直到所有 $x$ 倍数被选完。

那么我们需要记录 $x$ 的倍数已经用了几个，进一步发现只关心 $x$ 倍数被选择个数的奇偶性就行，显然选择 $x$ 的倍数的数量和操作数量相等。

那么跟上面类似 dp 即可，最后处理拖延时间的情况。

时间复杂度 $\mathcal O(n\log^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,a[MAXN],f[MAXN],g[MAXN];
bool sg[MAXN][2];
vector <int> fac[MAXN];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),++f[a[i]];
	for(int i=2;i<MAXN;++i) {
		fac[i].push_back(i),reverse(fac[i].begin(),fac[i].end());
		for(int j=2*i;j<MAXN;j+=i) f[i]+=f[j],fac[j].push_back(i);
	}
	for(int i=2;i<MAXN;++i) {
		for(int j:fac[i]) g[j]=f[j];
		for(int j:fac[i]) for(int k:fac[j]) if(k<j) g[k]-=g[j];
		for(int j:fac[i]) if(g[j]&&j<i) sg[i][0]|=!sg[j][1],sg[i][1]|=!sg[j][0];
		if(!sg[i][0]&&!sg[i][1]) sg[i][(f[i]&1)^1]=true;
	}
	for(int i=1;i<=n;++i) puts(sg[a[i]][1]?"Aoki":"Takahashi");
	return 0;
}
```

---

## 作者：HHH6666666666 (赞：2)

最原始最暴力的想法：用每个数选没选、当前 $G$ 为多少 ~~（其实可以根据数的状态推出不过不重要）~~ 表示一个状态，递推 $SG$ 函数。

发现一个性质：若当前的 $G=g$，则 $\forall A_i \nmid g$，$A_i$ 一定还在黑板上，已经删除的一定是 $g$ 的倍数，而对于当前状态来讲我们并不关心这些数的值（因为其与 $g$ 的最大公因数均为 $g$）。因此状态可以缩减为当前为第几步、当前 $G$ 的值。

状态还是太多了，原因在于我们记录了当前还剩几个 $G$ 的倍数。但由于是二人博弈，只需知道 $G$ 的倍数个数的奇偶性即可，状态数缩减为 $2 \times V$。

考虑 $SG$ 函数的转移。先用每个点除自己之外的所有后继更新该点状态。令 $f_{i,j=0/1} = 0/1$ 表示 $G = i$， 步数奇偶性为 $j$ 的状态为先手必胜或必败。当剩余的 $G$ 的倍数个数为奇且 $f_{i,0},f_{i,1}$ 均为必败时，当前局面可转为必胜，否则剩余倍数个数无影响。

思路有了，但还存在一个问题：如何对于每个 $1 \leq i \leq V$ 的约数 $j$，求出 $A$ 中是否存在一个数使 $\gcd(A_x,i)=j$？有两种解决方法。

#### 1. 手动容斥

令 $s_i$ 表示 $A$ 中 $i$ 的倍数的个数，$f_{i,j}$ 表示 $A$ 中满足 $\gcd(x,i)=j$ 的 $x$ 的个数。

则 $\forall j \mid i,s_j=\sum\limits_{j \mid k}f_{i,k}$。移项得 $f_{i,j}=s_j-\sum\limits_{j\mid k,k > j} f_{i,k}$。即假如当前数为 $n$，对于它的一个因数 $x$ 我们想求出 $\gcd(n,t)=x$ 的 $t$ 的数量，就用 $x$ 的倍数的个数减去所有满足 $\gcd(n,t)=kx,k \geq 2$ 的 $t$ 的数量即可。那么只要从大到小枚举 $x$，求出 $f_{n,x}$ 即可。

对于一个数 $n$，求出所有因数的结果的复杂度为 $O(d(n)^2)$，$d(n)$ 表示 $n$ 的因子个数。会不会 TLE？实践出真知。

```cpp
int n = 2e5;
vector<int> cnt(n + 1);
for (int i = 1; i <= n; ++i)
    for (int j = i; j <= n; j += i) ++cnt[j];
int ans = 0;
for (int i = 1; i <= n; ++i) ans += cnt[i] * cnt[i];
cout << ans << endl;    // 61136503
```

看来是能过的。

[code1](https://www.luogu.com.cn/paste/wc3j0pwz)

#### 2. 自动容斥？

如果你嫌推容斥太麻烦那就莫反：

对于每个 $n$，已知 $s_i=\sum\limits_{i \mid j}{f_{n,j}}$，则有 $f_{n, i}=\sum\limits_{i \mid j} \mu_{\frac{j}{i}}s_j$，直接算即可。


复杂度与做法 $1$ 相同。

[code2](https://www.luogu.com.cn/paste/96dsu5if)

---

题外话：在看 Um_nik 代码时学会了一种新的莫比乌斯函数递推：

```cpp
mo[1] = 1;
for (int x = 1; x <= N; x++)
    for (int y = 2 * x; y <= N; y += x)
        mo[y] -= mo[x];
```

原理：由 $\sum\limits_{j \mid i} \mu_j = [i=1]$ 移项得 $\mu_i = [i=1] - \sum\limits_{j \mid i,j<i} \mu_j$。

---

## 作者：Caiest_Oier (赞：0)

# [AT_arc155_d](https://www.luogu.com.cn/problem/AT_arc155_d)         

少有的独立做出来的 *3000。         

考虑如何设计状态。当我们确定当前的 $G$ 时，数可以分为两部分，一部分是 $G$ 的倍数，一部分不是，并且可以保证，之前取过的所有数都在第一部分里面。         

容易发现，第一部分中所有数都是等价的，均不会再次对 $G$ 造成影响。于是状态可以表示成 $(G,x)$，即当前取过的数 $\gcd=G$，取了 $x$ 个数。对于每个状态记录先手必胜还是后手必胜，转移时枚举在哪一部分取。于是得到了一个多项式复杂度的做法，状态数最多是 $O(n\times \max_{i\in[1,n]}{d(i)})$，$d(i)$ 指 $i$ 的因数个数，每次转移复杂度 $O(n)$，总复杂度 $O(n^2\max_{i\in [1,n]}{d(i)})$。           

考虑优化，首先，如果某个相同的数出现了过多次，那么是无意义的。当某个数被取过后，再取它唯一的意义就是转换先后手，但是如果剩下的个数大于一个，后手跟着先手取可以保证局势不变，于是如果某个数出现了 $x$ 次，那么将其改为 $(x-1)\mod 2+1$。这样可以将状态数压到 $O(n\log n)$。       

另外再来一个优化，枚举第二部分的数的时候，可以直接枚举 $y=\gcd(G,x)$。判断能否取到一个这样的 $x$ ，可以使用莫反容斥计算。在 $G$ 的因数集合里面对所有因数进行莫反，每个数莫反一次，复杂度是它自己所有因数的因数个数和，即 $O(\sum_{i=1}^{n}\frac{n}{i}\log{\frac{n}{i}})$，低于 $O(n\log^2n)$。     

两个优化结合一下，便可以做到 $O(n\log^2n)$ 了。        

代码：       


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,N,a[500003],b[500003],apr[500003],sum[500003],dp[4000003],pre[500003],v[500003];
vector<int>ys[500003];
signed main(){
    ios::sync_with_stdio(false);
    for(int i=1;i<=200000;i++){
        for(int j=i;j<=200000;j+=i)ys[j].emplace_back(i);
    }
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)b[i]=a[i];
    for(int i=1;i<=n;i++)apr[a[i]]++;
    N=n;
    n=0;
    for(int i=1;i<=500000;i++){
        if(apr[i]==0)continue;
        apr[i]%=2;
        if(apr[i]==0)apr[i]=2;
        while(apr[i]){
            a[++n]=i;
            apr[i]--;
        }
    }
    for(int i=1;i<=n;i++){
        for(auto j:ys[a[i]])sum[j]++;
    }
    for(int i=1;i<=a[n];i++)pre[i]=pre[i-1]+sum[i];
    for(int i=2;i<=a[n];i++){
        if(sum[i]==0)continue;
        for(auto j:ys[i])v[j]=sum[j]-sum[i];
        for(int j=ys[i].size()-1;j>=0;j--){
            int op=ys[i][j];
            for(auto u:ys[i/op])if(u!=1)v[op]=(v[op]-v[u*op]);
        }
        for(int j=sum[i];j;j--){
            for(auto u:ys[i])if(u!=1&&v[u]!=0&&dp[pre[u-1]+j+1]==0)dp[pre[i-1]+j]=1;
            if(j!=sum[i]&&dp[pre[i-1]+j+1]==0)dp[pre[i-1]+j]=1;
        }
    }
    for(int i=1;i<=N;i++){
        if(dp[pre[b[i]-1]+1]==1)cout<<"Aoki\n";
        else cout<<"Takahashi\n";
    }
    return 0;
}
```

写完题解才发现的神奇优化：实际上对于一个状态 $(G,x)$ 来讲，$x$ 只在乎奇偶，所以其实状态可以优化到线性，不过对总复杂度还是没啥帮助就是了（）。

---

