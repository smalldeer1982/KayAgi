# [SEERC 2020] Divisible by 3

## 题目描述

定义一个序列 $b$ 的权重为 $\sum_{i=1}^n \sum_{j=1}^{i-1} b_i \times b_j$。

现在你有一个长度为 $n$ 的数组 $a$，求一共存在多少种 $(l,r)$ 使得 $1 \leq l \leq r \leq n$ 且 $[a_l, a_{l+1},\ldots,a_r]$ 的权重能被 $3$ 整除。

## 说明/提示

对于第一个样例，存在 $[1,1]$、$[2,2]$、$[3,3]$、$[1,3]$ 共 $4$ 种方案。

## 样例 #1

### 输入

```
3
5 23 2021
```

### 输出

```
4```

## 样例 #2

### 输入

```
5
0 0 1 3 3```

### 输出

```
15```

## 样例 #3

### 输入

```
10
0 1 2 3 4 5 6 7 8 9```

### 输出

```
20```

# 题解

## 作者：xiezheyuan (赞：4)

## 思路

记 $f(l,r)$ 表示区间 $[l,r]$ 的权重，即：

$$
F(l,r)=\sum_{i=l}^{r}\sum_{j=l}^{i-1}a_ia_j
$$

发现 $F(l,r)$ 的意义为：对于每一个无序二元组 $(i,j)$，权值为 $a_ia_j$，求对于所有的 $l\leq i\lt j\leq r$，$(i,j)$ 的权值总和。

将无序二元组，转成有序二元组，并且允许 $i=j$，此时的权值总和为：

$$
G(l,r)=\sum_{i=l}^{r}\sum_{j=l}^{r}a_ia_j
$$

令 $f_0=0,f_i=f_{i-1}+a_i$，则可以简化为：

$$
G(l,r)=(f_r-f_{l-1})^2
$$

记 $g_0=0,g_i=g_{i-1}+a_1^2$，则：

$$
\begin{aligned}
&F(l,r)\\
&=\frac{1}{2}(G(l,r)-(g_r-g_{l-1}))\\
&=\frac{1}{2}((f_r-f_{l-1})^2-g_r+g_{l-1})
\end{aligned}
$$

发现决定 $F(l,r)\bmod 3$ 是否为 $0$ 的只有 $f_r\bmod 3, f_{l-1}\bmod 3, g_r\bmod 3,g_{l-1}\bmod 3$。

我们倒序枚举 $l$ 去数 $r$（这样可以保证 $[l,r]$ 构成一个区间），记 $c_{x,y}$ 表示满足 $f_r\bmod 3=x,g_r\bmod 3=y$ 的 $r$ 数量。然后枚举 $x,y$，带入到 $F(l,r)$ 式子中看看对 $3$ 取余后是否为 $0$ 即可。注意由于 $\gcd(2,3)=1$，故 $\frac{1}{2}$ 对本题没有影响，可以删掉。

时间复杂度 $O(np^2)$，其中 $p=3$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 5;
int a[N], n, f[N], g[N], cnt[5][5], ans;

int M(int x) {return (x % 3 + 3) % 3; }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i] = a[i] % 3;
        f[i] = (f[i - 1] + a[i]) % 3;
        g[i] = (g[i - 1] + a[i] * a[i]) % 3;
    }
    for(int l=n;l;l--){
        cnt[f[l]][g[l]]++;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(M((i - f[l - 1]) * (i - f[l - 1]) - j + g[l - 1]) == 0) ans += cnt[i][j];
            }
        }
    }
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：__Sky__Dream__ (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/P10740)

## 题目大意

给出一个长度为 $n$ 的数组，定义一段子数组的重量为其中两两乘积和。例如数组 $b$，对于 $l$ 到 $r$ 的子数组，其重量为对于所有 $l \le i < j \le r$，$b_i,b_j$ 的乘积，求给出数组中重量能被 $3$ 整除的子数组数量。

## 解题思路

数据范围较大，因此不能暴力枚举。

定义数组为 $a$，子数组前缀和为 $sum_i$，子数组的重量为 $p_i$。

考虑使用 DP。对于任意一个子数组，如果在其后添加一个新的 $a_i$，那么变化后的重量等于 $(p_{i-1}+sum_{i−1} \times a_i)$，所以其实只要知道 $p_{i−1}$ 和 $sum_{i−1}$，我们就可以进行转移。而且因为这道题只要求我们求被 $3$ 整除的数量，所以就可以在过程中进行对 $3$ 取模，然后在每一位上 $0-3$ 枚举 $p_{i−1}$ 和 $sum_{i−1}$，一共 $9$ 个状态进行转移。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll maxn=5e5;
ll dp[maxn+10][3][3];
ll ans=0;
void dfs()
{
	ll n;
	cin>>n;
	vector<ll>a(n+1);
	for(ll i=1;i<=n;i++)
	{
		cin>>a[i];
		dp[i][0][a[i]%3]++;
	}
	for(ll i=1;i<=n;i++)
		for(ll j=0;j<3;j++)
			for(ll k=0;k<3;k++)
				dp[i][(j+(a[i]*k))%3][(k+a[i])%3]+=dp[i-1][j][k];
	for(ll i=1;i<=n;i++)
		for(ll j=0;j<3;j++)
			ans+=dp[i][0][j];
	cout<<ans<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	dfs();
	return 0;
}
```

**完结撒花！**

---

## 作者：封禁用户 (赞：1)

原式子是 $\displaystyle \sum^n_{i=1}\sum^{i-1}_{j=1}b_i\times b_j$，可以通过引入前缀和来简化这个表达式。

设 $\displaystyle f_k=\sum^k_{i=1}b_i$，$\displaystyle g_k=\sum^k_{i=1}b^2_i$，

然后定义 $F(l,r)$ 与 $G(l,r)$ 如下：
$$F(l,r)= \sum^r_{i=l}\sum^{i-1}_{j=l}b_i\times b_j$$
$$G(l,r)=\sum^r_{i=l}\sum^{i-1}_{j=l}b^2_i$$
然后通过分步求和来推导：

首先，考虑 $G(l,r)$，将其展开为：
$$G(l,r)=\sum^r_{i=l}(i-l)b^2_i$$
接下来，考虑 $F(l,r)$，将其展开为：
$$F(l,r)=\sum^r_{i=l}b_i\sum^{i-1}_{j=l}b_j$$
注意到 $\displaystyle\sum^{i-1}_{j=l}b_j=f_i-f_l$，所以，我们可以将 $F(l,r)$ 进一步展开为：
$$F(l,r)=\sum^r_{i=l}b_if_i-\sum^r_{i=l}b_if_l$$
由于 $f_l$ 是常数，可以提到求和符号外面：
$$F(l,r)=\sum^r_{i=l}b_if_i-f_l\sum^r_{i=l}b_i$$
注意到 $\displaystyle\sum^r_{i=l}b_i=f_r-f_{r-1}$，所以，我们可以将 $G(l,r)$ 进一步展开为：
$$G(l,r)=\sum^r_i=ib^2_i-lg_r+l_{g_{l-1}}$$
最终，我们可以将 $F(l,r)$ 与 $G(l,r)$ 结合起来，得到：
$$F(l,r)=\frac{1}{2}(G(l,r)-(g_r-g_{l-1}))$$
$$F(l,r)=\frac{1}{2}((f_r-f_{l-1})^2-g_r+g_{l-1})$$
这就是我们推导的结果。
#### 时间复杂度优化
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		a[i] %= 3;
	}

	vector<int> f(n + 1, 0);
	vector<int> g(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		f[i] = (f[i - 1] + a[i - 1]) % 3;
		g[i] = (g[i - 1] + a[i - 1] * a[i - 1]) % 3;
	}

	long long result = 0;
	for (int l = 0; l < n; ++l) {
		for (int r = l; r < n; ++r) {
			int f_diff = (f[r + 1] - f[l] + 3) % 3;
			int g_diff = (g[r + 1] - g[l] + 3) % 3;
			int weight = (f_diff * f_diff - g_diff + 3) % 3;
			if (weight == 0) {
				result++;
			}
		}
	}

	cout << result << endl;
	return 0;
}
```
$O(n^2)$，明显超时，考虑优化。

要优化代码至 $O(n)$，我们可以避免嵌套的循环，并利用前缀和的性质来减少计算量。我们可以使用一个二维数组来记录前缀和的组合出现的次数，从而在一次遍历中完成计算（用空间换时间）。

优化后的代码：
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= 3;
    }

    vector<int> f(n + 1, 0);
    vector<int> g(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        f[i] = (f[i - 1] + a[i - 1]) % 3;
        g[i] = (g[i - 1] + a[i - 1] * a[i - 1]) % 3;
    }

    vector<vector<int>> cnt(3, vector<int>(3, 0));
    cnt[0][0] = 1; 
    long long result = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                int f_diff = (f[i] - j + 3) % 3;
                int g_diff = (g[i] - k + 3) % 3;
                int weight = (f_diff * f_diff - g_diff + 3) % 3;
                if (weight == 0) {
                    result += cnt[j][k];
                }
            }
        }
        cnt[f[i]][g[i]]++;
    }

    cout << result << endl;
    return 0;
}
```

---

## 作者：Hadtsti (赞：1)

### 题意简述

给定长为 $n(1\le n\le 5\times 10^5)$ 的序列 $b_i$，问有多少个区间 $[l,r]$ 满足 $1\le l\le r\le n$，且 $\displaystyle 3|(\sum_{i=l}^r\sum_{j=l}^{i-1}b_ib_j)$。

### 题目分析

~~这个题显然不到蓝吧，建议降黄~~

注意到能被 $3$ 整除的 $b_i$ 对区间是否满足条件没有贡献，我们可以不管它们。设 $cnt1_i,cnt2_i$ 分别代表 $b_1,b_2,\cdots,b_i$ 中模 $3$ 余 $1$ 和余 $2$ 的 $b_i$ 数量，那么区间 $[l,r]$ 中模 $3$ 余 $1$ 和余 $2$ 的 $b_i$ 数量分别为 $cnt1_r-cnt1_{l-1}$ 和 $cnt2_r-cnt2_{l-1}$。若令 $A=cnt1_r-cnt1_{l-1},B=cnt2_r-cnt2_{l-1}$，则当且仅当 $3|(2AB+\frac{A(A-1)}2+\frac{B(B-1)}2)$ 时 $[l,r]$ 满足条件。

不妨将合法区间在其右端点统计。那么对于固定的 $cnt1_r,cnt2_r$，我们只需要求出有多少个 $l\in[1,r-1]$ 可以使 $cnt1_{l-1},cnt2_{l-1}$ 与 $cnt1_r,cnt2_r$ 能够满足上述条件即可。由于 $cnt1$ 和 $cnt2$ 模 $3$ 之后是等价的，我们只需要统计 $cnt1$ 和 $cnt2$ 模 $3$ 之后的情况对应的 $l$ 分别有多少个就好了。然后对每一个 $r$ 直接枚举 $cnt1$ 和 $cnt2$ 不同取值的 $9$ 种情况判断是否合法后统计即可。时间复杂度 $O(n)$，空间复杂度 $O(1)$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,ct[3][3],s1,s2;
long long ans;
int main()
{
	scanf("%d",&n);
	ct[0][0]++;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		x%=3;
		(s1+=(x==1))%=3;
		(s2+=(x==2))%=3;
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
			{
				int a=(s1-j)%3,b=(s2-k)%3;
				if((2*a*b+a*(a-1)/2+b*(b-1)/2)%3==0)
					ans+=ct[j][k];
			}
		ct[s1][s2]++;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：AAA404 (赞：0)

建议先做 [P9753 [CSP-S 2023] 消消乐](https://www.luogu.com.cn/problem/P9753)。

对序列 $\{b\}$ 的权重进行化简：

$$\sum_{i=l}^{r} \sum_{j=l}^{i-1} b_i \times b_j=\sum_{i=l}^{r} b_i\sum_{j=l}^{i-1}b_j$$

令 $s_i=\sum_{k=1}^i b_i$，有：

$$\sum_{i=l}^{r} b_i \times (s_{i-1}-s_{l-1})$$

最终化简得到：

$$(\sum_{i=l}^{r} b_i \times s_{i-1})-s_{l-1}\times s_r+s_{l-1}^2$$

建议读者自行化简，接着令 $u_i=\sum_{k=1}^i b_k \times s_{k-1}$。

于是最终化为：$u_r-u_{l-1}-s_{l-1}\times s_r+s_{l-1}^2$。

该贡献可以被 $3$ 整除，因此：

$$u_r \equiv u_{l-1}+s_{l-1} \times s_r -s_{l-1}^2 \pmod 3$$

令 $l$ 代 $l-1$，最后统计答案时改变边界。

方便起见，下面将只与 $l$ 有关的 $u_l-s_{l}^2$ 记为 $x_l$。

发现上式化为：$u_r \equiv s_l \times s_r +x_l \pmod 3$，从小到大遍历，可以开桶统计答案。但是 $s_l$ 的系数为 $s_r$，与 $l$ 无关，无法确定其在模 $3$ 意义下的值，因此考虑对于 $s_r$ 在模 $3$ 意义下的每个可能值（只有 $0,1,2$），每种情况单独开桶记录。

具体实现见代码注释。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a[N],s[N],u[N],ans,t[10][10],x[N];
signed main()
{
	clock_t c1=clock();
#ifdef LOCAL
 	freopen("1.in","r",stdin);
 	freopen("1.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
 	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		s[i]=(s[i-1]+a[i])%3;
		u[i]=(u[i-1]+a[i]*s[i-1])%3;
		x[i]=((u[i]-s[i]*s[i])%3+3)%3;//预处理
	}
	for(int i=0;i<=n;i++)
	{
		ans+=t[u[i]][s[i]];//第一维是容易理解的，第二维则是通过 s[r] 除以 3 的余数查询答案
  //下面对应 s[r]不同情况更新桶，第二维是 s[r] 除以 3 的余数
		t[x[i]][0]++;
		t[(s[i]+x[i])%3][1]++;
		t[(s[i]*2+x[i])%3][2]++;
	}
	cout<<ans;
#ifdef LOCAL
	cerr<<"Time used:"<<clock()-c1<<"ms";
#endif
 	return 0;
}
```

---

