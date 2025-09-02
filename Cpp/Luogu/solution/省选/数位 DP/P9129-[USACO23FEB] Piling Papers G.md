# [USACO23FEB] Piling Papers G

## 题目描述

农夫约翰在纸片上写下了 $N (1 \le N \le 300)$ 个数字。对于每个 $i \in [1,N]$，第 $i$ 张纸片上写着数字 $a_i (1 \le a_i \le 9)$。

奶牛们有两个最喜欢的整数 $A$ 和 $B(1 \le A \le B<10^{18})$，希望你回答 $Q (1 \le Q \le 5 \times 10^4)$ 个查询。对于第 $i$ 个查询，奶牛们将从左到右移动穿过纸片 $l_i \cdots r_i (1 \le l_i \le r_i \le N)$，保持一个最初为空的纸片堆。对于每张纸片，它们可以选择将其添加到堆的顶部、底部，或者不添加。最后，它们将从顶部到底部读取堆中的纸片，形成一个整数。在奶牛们在此过程中做选择的所有 $3 ^ {r_i-l_i+1}$ 种方式中，计算出结果在 $[A,B]$ 范围内的方式数量，并输出这个数量对 $10^9+7$ 取模的结果。

## 说明/提示

### 示例 1 的解释

对于第一个查询，Bessie 在读取区间 $[1,2]$ 时有九种方式堆叠纸片：

- Bessie 可以忽略 $1$ 然后忽略 $2$，得到 $0$。
- Bessie 可以忽略 $1$ 然后将 $2$ 添加到堆的顶部，得到 $2$。
- Bessie 可以忽略 $1$ 然后将 $2$ 添加到堆的底部，得到 $2$。
- Bessie 可以将 $1$ 添加到堆的顶部然后忽略 $2$，得到 $1$。
- Bessie 可以将 $1$ 添加到堆的顶部然后将 $2$ 添加到堆的顶部，得到 $21$。
- Bessie 可以将 $1$ 添加到堆的顶部然后将 $2$ 添加到堆的底部，得到 $12$。
- Bessie 可以将 $1$ 添加到堆的底部然后忽略 $2$，得到 $1$。
- Bessie 可以将 $1$ 添加到堆的底部然后将 $2$ 添加到堆的顶部，得到 $21$。
- Bessie 可以将 $1$ 添加到堆的底部然后将 $2$ 添加到堆的底部，得到 $12$。

只有 $2$ 种方式得到的数字在 $13$ 和 $327$ 之间，所以答案是 $2$。

### 评分

- 输入 $2-3$：$B<100$
- 输入 $4-5$：$A=B$
- 输入 $6-13$：无额外约束。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 13 327
1 2 3 4 5
3
1 2
1 3
2 5```

### 输出

```
2
18
34```

# 题解

## 作者：Elma_ (赞：16)

先考虑一次询问怎么做。首先容斥成 $\leq B$ 的答案减去 $\leq A-1$ 的答案，因此我们只考虑 $\leq t$ 的答案怎么求。

一个朴素的想法是设 $f_{i,j,0/1/2}$ 表示前 $i$ 个数，从低位开始填了 $j$ 位，此时和 $t$ 的最低 $j$ 位的大小关系是小于，等于或大于的方案数。但你发现，虽然在做 $x\rightarrow\overline{x+a_i}$ 的时候我们可以 $\mathcal{O}(1)$ 地得到大小关系，但是在 $x\rightarrow\overline{a_i+x}$ 时并没有办法靠谱地确定，除非我们直接记录下当前填出的 $x$，但这样状态就爆炸了。

这给我们一些启示：在设计状态的时候，我们不能让 $x$ 在 $t$ 上对应的区间移动。自然想到设 $f_{i,l,r,0/1/2}$ 表示前 $i$ 个数，形成的 $r - l +1$ 位的数字 $x$，和 $t$ 从高到低的第 $l$ 位到第 $r$ 位形成的数字 $t'$ 的大小关系是小于，等于或大于的方案数，转移只需要考虑往哪个方向扩展。此时我们就可以只通过当前位确定出整个区间的大小关系了，于是可以 $\mathcal{O}(1)$ 完成转移。

设 $t$ 的位数为 $d$，那么最后的答案是 $f_{n,1,d,0} + f_{n,1,d,1} + \sum \limits_{j=2}^d \sum \limits_{k=0}^2 f_{n,j,d,k}$，其中最后一项计算的是位数 $<d$ 的方案数。

于是我们得到了一个 $\mathcal{O}(qn \log^2 B)$ 的做法。但我们发现，每次 DP 的时候我们其实都计算出了每个前缀的答案，因此我们对于每个后缀做一次 DP，查询的时候用前缀和 $\mathcal{O}(1)$ 查询，总时间复杂度就变成了 $\mathcal{O}(n^2 \log^2 B + q)$，足以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 3e2 + 5, M = 20, mod = 1e9 + 7;
int n, m, q, a[N], lim[M], ansL[N][N], ansR[N][N], f[M][M][3]; LL L, R;
void getlim(LL x) {
	m = 0;
	while (x > 0) lim[++m] = x % 10, x = x / 10;
	reverse(lim + 1, lim + m + 1);
}
int chk(int a, int b) {
	if (a < b) return 0;
	else if (a == b) return 1;
	else return 2;
}
int main() { 
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> L >> R;
    for (int i = 1; i <= n; i++) cin >> a[i];
	getlim(L - 1);
	for (int i = 1; i <= n; i++) {
		memset(f, 0, sizeof(f));
		for (int j = i; j <= n; j++) {
			for (int x = 1; x <= m; x++) {
				for (int y = m; y > x; y--) {
					if (a[j] > lim[x]) {
						for (int k = 0; k <= 2; k++) f[x][y][2] = (f[x][y][2] + f[x + 1][y][k]) % mod;
					} else if (a[j] == lim[x]) {
						for (int k = 0; k <= 2; k++) f[x][y][k] = (f[x][y][k] + f[x + 1][y][k]) % mod;
					} else {
						for (int k = 0; k <= 2; k++) f[x][y][0] = (f[x][y][0] + f[x + 1][y][k]) % mod;
					}
					f[x][y][2] = (f[x][y][2] + f[x][y - 1][2]) % mod;
					f[x][y][chk(a[j], lim[y])] = (f[x][y][chk(a[j], lim[y])] + f[x][y - 1][1]) % mod;
					f[x][y][0] = (f[x][y][0] + f[x][y - 1][0]) % mod;
				}
			}
			for (int x = 1; x <= m; x++) f[x][x][chk(a[j], lim[x])] = (f[x][x][chk(a[j], lim[x])] + 2) % mod;
			for (int x = 1; x <= m; x++) {
				ansL[i][j] = (ansL[i][j] + f[x][m][1]) % mod;
				ansL[i][j] = (ansL[i][j] + f[x][m][0]) % mod;
				if (x > 1) ansL[i][j] = (ansL[i][j] + f[x][m][2]) % mod; 
			}
		}
	}
	getlim(R);
	for (int i = 1; i <= n; i++) {
		memset(f, 0, sizeof(f));
		for (int j = i; j <= n; j++) {
			for (int x = 1; x <= m; x++) {
				for (int y = m; y > x; y--) {
					if (a[j] > lim[x]) {
						for (int k = 0; k <= 2; k++) f[x][y][2] = (f[x][y][2] + f[x + 1][y][k]) % mod;
					} else if (a[j] == lim[x]) {
						for (int k = 0; k <= 2; k++) f[x][y][k] = (f[x][y][k] + f[x + 1][y][k]) % mod;
					} else {
						for (int k = 0; k <= 2; k++) f[x][y][0] = (f[x][y][0] + f[x + 1][y][k]) % mod;
					}
					f[x][y][2] = (f[x][y][2] + f[x][y - 1][2]) % mod;
					f[x][y][chk(a[j], lim[y])] = (f[x][y][chk(a[j], lim[y])] + f[x][y - 1][1]) % mod;
					f[x][y][0] = (f[x][y][0] + f[x][y - 1][0]) % mod;
				}
			}
			for (int x = 1; x <= m; x++) f[x][x][chk(a[j], lim[x])] = (f[x][x][chk(a[j], lim[x])] + 2) % mod;
			for (int x = 1; x <= m; x++) {
				ansR[i][j] = (ansR[i][j] + f[x][m][1]) % mod;
				ansR[i][j] = (ansR[i][j] + f[x][m][0]) % mod;
				if (x > 1) ansR[i][j] = (ansR[i][j] + f[x][m][2]) % mod; 
			}
		}
	}
	cin >> q;
	while (q--) {
		int l, r; cin >> l >> r;
		int ans = (ansR[l][r] - ansL[l][r] + mod) % mod;
		cout << ans << "\n";
	}
    return 0;
}
```

---

## 作者：学委 (赞：5)

- 题意：给出 $1 \sim 9$ 数组 $a$，并给出 $A$ 和 $B$，和 $q$ 个询问，求 $l_i$ 到 $r_i$ 之间的数从左往右依次三选一操作（放到队首，放到队尾，忽略）有几种方案可以拼出 $A$ 到 $B$ 之间的数。

首先题意转化为求拼出的数小于等于 $A - 1$ 和小于等于 $B$ 的方案数，两个方案数相减得到答案。

接下来考虑如何拼出相邻的数字小于等于 $B$ 的数。显然长度小于 $B$ 的长度的方案均可行。下面考虑长度与 $B$ 一致的方案。

对每个询问，从 $a_{l_i}$ 开始取数，令 $f_{t, i, j}$ 表示取到第 $a_t$（可不取），拼成 $B_i \sim B_j$ 的方案数（这里将 $B$ 视为一个字符数组）。这是一个区间动态规划，$i$ 到 $j$ 可由 $i \sim j - 1$ 或 $i - 1 \sim j$ 转移而来。转移方程为：

$$\begin{aligned}
& f_{t, i, j} = f_{t, i, j} + f_{t - 1, i + 1, j}, \text{if } a_t = B_i \\
& f_{t, i, j} = f_{t, i, j} +  f_{t - 1, i, j - 1}, \text{if } a_t = B_j
\end{aligned}$$

当拼出第 $k$ 位小于 $B_k$ 的数，且第 $k$ 位之前与 $B$ 一致的数时，$k$ 之后的数可以任取。因此令 $g_{t, i, k, j}$ 表示取到 $a_t$，拼出 $B_i$ 到 $B_{k - 1}$，第 $k$ 位小于 $B_k$ 且第 $k + 1 \sim j$ 位任意取的方案数。转移方程如下：

$$\begin{aligned}
& g_{t, i, k, j} = g_{t, i, k, j} + C_{t - l_i}^{j - k} \times 2^{j - k} , \text{if } i = k \text{ and } a_t < B_i \\
& g_{t, i, k, j} = g_{t, i, k, j} + g_{t - 1, i + 1, k, j}, \text{if } i \neq k \text{ and } a_t = B_i \\
& g_{t, i, k, j} = g_{t, i, k, j} + f_{t - 1, i, j - 1}, \text{if } j = k \text{ and } a_t < B_j \\
& g_{t, i, k, j} = g_{t, i, k, j} + g_{t - 1, i, k, j - 1}, \text{if } j \neq k\\
\end{aligned}$$

最终答案为 $\sum_{k = 1}^{\textrm{len}(B)}g_{r_i, 1, k, \textrm{len(B)}} + f_{r_i, 1, \textrm{len}(B)}$. 需注意边界条件。

为避免对每一个询问做一次 dp，考虑将所有询问离线，按照左端点排序。同一左端点的询问只需做同一次 dp 即可。

复杂度 $O(n ^ 2 (\log_{10}B) ^ 3)$，常数较小，经测试可以在 0.5s 左右通过最大数据。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 305;
const int Q = 5e4 + 5;
const int P = 1e9 + 7;

struct Que {
    int l, r;
    int id;
};

ll A, B;
int n, q;
int a[N];
Que que[Q];
int ans[Q];
int f[N][20][20];
int g[N][20][20][20];

int C[N][N];
int _2[N];

void calculate_and_contribute(ll key, int coff) {
    int q_ptr = 1;
    int sep[20], cnt = 0;
    {
        ll p = key;
        while (p) {
            sep[++cnt] = p % 10;
            p /= 10;
        }
        std::reverse(sep + 1, sep + cnt + 1);
    }

    for (int q_l = 1; q_l <= n; q_l++) {
        // 统计从 q_l 开始向右选牌的方案数
        // f[t, i, k, j] 选到 t （可以不选）拼成 key i 到 j 的方案数
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int t = q_l; t <= n; t++) {
            for (int len = 1; len <= cnt; len++) {
                for (int i = 1; i + len - 1 <= cnt; i++) {
                    int j = i + len - 1;
                    // 令 $f_{t, i, j}$ 表示取到第 $a_t$（可不取），拼成 $B_i \sim B_j$ 的方案数（这里将 $B$ 视为一个字符数组）。这是一个区间动态规划，$i$ 到 $j$ 可由 $i \sim j - 1$ 或 $i - 1 \sim j$ 转移而来。转移方程为：
                    (f[t][i][j] += f[t - 1][i][j]) %= P;
                    if (len == 1) { // i == j
                        if (a[t] == sep[i]) {
                            // 1 or 2 method
                            (f[t][i][j] += 2) %= P;
                        }
                    } else {
                        // 加前面 ( 1 method )
                        if (a[t] == sep[i]) {
                            (f[t][i][j] += f[t - 1][i + 1][j]) %= P;
                        }
                        // ( 2 method )
                        if (a[t] == sep[j]) {
                            (f[t][i][j] += f[t - 1][i][j - 1]) %= P;
                        }
                    }
                }
            }
        }
        for (int t = q_l; t <= n; t++) {
            for (int len = 1; len <= cnt; len++) {
                for (int i = 1; i + len - 1 <= cnt; i++) {
                    int j = i + len - 1;
                    for (int k = i; k <= j; k++) {
                        // 当拼出第 $k$ 位小于 $B_k$ 的数，且第 $k$ 位之前与 $B$ 一致的数时，$k$ 之后的数可以任取。因此令 $g_{t, i, k, j}$ 表示取到 $a_t$，拼出 $B_i$ 到 $B_{k - 1}$，第 $k$ 位小于 $B_k$ 且第 $k + 1 \sim j$ 位任意取的方案数。转移方程如下：
                        // 1 method, add to i
                        (g[t][i][k][j] += g[t - 1][i][k][j]) %= P;
                        if (i == k) {
                            if (a[t] < sep[i]) {
                                // [at as small] + all-rand way
                                int all_rand_ways = (ll)C[t - q_l][j - k] * _2[j - k] % P;
                                (g[t][i][k][j] += all_rand_ways) %= P;
                            }
                        } else {
                            // [a_t as eq] + something
                            if (a[t] == sep[i])
                                (g[t][i][k][j] += g[t - 1][i + 1][k][j]) %= P;
                        }
                        // 2 method, add to j
                        if (k == j) {
                            if (a[t] < sep[j]) {
                                // all-same way + [a_t as small]
                                int all_same_ways = i == j ? 1 : f[t - 1][i][j - 1];
                                (g[t][i][k][j] += all_same_ways) %= P;
                            }
                        } else {
                            // something + [a_t as rand]
                            (g[t][i][k][j] += g[t - 1][i][k][j - 1]) %= P;
                        }
                    }
                }
            }
        }
        // 最终答案为 $\sum_{k = 1}^{\textrm{len}(B)}g_{r_i, 1, k, \textrm{len(B)}} + f_{r_i, 1, \textrm{len}(B)}$. 需注意边界条件。

        // 为避免对每一个询问做一次 dp，考虑将所有询问离线，按照左端点排序。同一左端点的询问只需做同一次 dp 即可。
        while (que[q_ptr].l == q_l && q_ptr <= q) {
            // 显然长度小于 $B$ 的长度的方案均可行。
            int ran = que[q_ptr].r - q_l + 1;
            for (int len = 0; len <= cnt - 1; len++) {
                // 短 method
                ll short_method = (ll)coff * C[ran][len] % P * _2[len] % P;
                short_method = (short_method + P) % P;
                (ans[que[q_ptr].id] += short_method) %= P;
            }
            for (int k = 1; k <= cnt; k++) {
                ll eq_k_less_rand = (ll)coff * g[que[q_ptr].r][1][k][cnt] % P;
                eq_k_less_rand = (eq_k_less_rand + P) % P;
                (ans[que[q_ptr].id] += eq_k_less_rand) %= P;
            }
            ll eq_method = (ll)coff * f[que[q_ptr].r][1][cnt] % P;
            eq_method = (eq_method + P) % P;
            (ans[que[q_ptr].id] += eq_method) %= P;
            ++q_ptr;
        }
    }
}

int main() {
    scanf("%d%lld%lld", &n, &A, &B);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &que[i].l, &que[i].r);
        que[i].id = i;
    }
    sort(que + 1, que + q + 1, [](const Que& a, const Que& b) {
        if (a.l != b.l)
            return a.l < b.l;
        return a.r < b.r;
    });
    _2[0] = 1;
    for (int i = 1; i <= n; i++)
        _2[i] = _2[i - 1] * 2 % P;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i || i == 0) {
                C[i][j] = 1;
                continue;
            }
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
        }
    }
    calculate_and_contribute(B, +1);
    if (A > 1)
        calculate_and_contribute(A - 1, -1);
    for (int i = 1; i <= q; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}

```


---

## 作者：Bluebird_ (赞：4)

@Elma_ 大佬写的题解把想到正解的思路，DP状态设计都讲的很清楚了，这里补充自己对一些细节的理解。

1. 初始状态
	
   初始是空串，往左边加数和往右边加数得到的数均相同，但**操作序列**不一样，所以加 $2$ 不是加 $1$（虽然很容易想到但我就是想了半天。。才意识到）。

2. 枚举顺序

	有点类似背包，如果从小区间往大区间转移的话就会出错，所以要**倒序**枚举（从大区间往小区间转移）。
    
3. 转移方式
	
   这个很好想，在我的代码注释中有描述，核心是分成**加左边**和**加右边**两种情况。
   
3. 答案的统计
	
   形成的数字 $t$ 的位数和限制数 $A-1$ 或 $B$(这里记为 $mx$)的位数相同时，只能计入 $t \le  mx$ 的贡献。 
   
   形成的数字 $t$ 的位数比限制数 $mx$ 的位数小时，无论 $t$ 和对应数列 $S_{l,r}$ 大小关系如何都计入贡献，但是为什么是 $\sum_{1\le p < top} f_{1,p}$ 呢，因为只统计从 $1$ 开始的区间就可以涵盖到所有位数比 $mx$ 小的贡献，如果把 $2$ 开始的区间也加上的话会重复计算，例如 $mx=789$，假设我们形成的数字 $t=12$，这个 $t$ 可以是和 $78$ 对应也可以是和 $89$ 对应，但是没关系他们都小于限制数 $mx$，所以直接统计从 $1$ 开始的即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=303,M=1e9+7;
int n,A,B,f[N][N][3],a[N],top,s[N],ans[2][N][N];
void div(int x)
{
	top=0;
	while(x)
		s[++top]=x%10,x/=10;
	reverse(s+1,s+1+top);
}
void add(int &x,int y){x=(x+y)%M;}
int cmp(int x,int y)
{
	if(x>y)return 2;
	else if(x==y)return 1;
	else return 0;
}
void DP(int T)
{
	for(int i=1;i<=n;++i)
	{
		memset(f,0,sizeof f);
		for(int j=i;j<=n;++j)
		{
			for(int p=1;p<=top;++p)
			{
				for(int q=top;q>p;--q)
				{   //把a[j]加在左边
					if(a[j]>s[p]){//不管右边是大还是小，只要左边最高位大就是大
						add(f[p][q][2],f[p+1][q][0]);
						add(f[p][q][2],f[p+1][q][1]);
						add(f[p][q][2],f[p+1][q][2]);
					}else if(a[j]==s[p]){//最高位相等，看低位谁大
						add(f[p][q][0],f[p+1][q][0]);
						add(f[p][q][1],f[p+1][q][1]);
						add(f[p][q][2],f[p+1][q][2]);
					}else {//不管右边是大还是小，只要左边最高位小就是大
						add(f[p][q][0],f[p+1][q][0]);
						add(f[p][q][0],f[p+1][q][1]);
						add(f[p][q][0],f[p+1][q][2]);
					}
					//把a[j]加在右边
					add(f[p][q][2],f[p][q-1][2]);//左边高位大，右边不管怎么样填都大
					add(f[p][q][0],f[p][q-1][0]);//左边高位小，右边不管怎么样填都小
					add(f[p][q][cmp(a[j],s[q])],f[p][q-1][1]);//左边高位相等，就看当前位填的大还是小
				}
			}
			for(int p=1;p<=top;++p)
				add(f[p][p][cmp(a[j],s[p])],2);//为什么加2？因为初始时串为空，加左边加右边得到的数字一样但是两种方案
			add(ans[T][i][j],(f[1][top][0]+f[1][top][1])%M);//位数相同的贡献，只能小于或者等于
			for(int p=1;p<top;++p)//位数不够，一定较小
				add(ans[T][i][j],f[1][p][0]),
				add(ans[T][i][j],f[1][p][1]),
				add(ans[T][i][j],f[1][p][2]);
		}
	}
}
int main()
{
	cin>>n>>A>>B;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	div(A-1);
	DP(0);
	div(B);
	DP(1);
	int Q;
	cin>>Q;
	while(Q--)
	{
		int l,r;
		cin>>l>>r;
		cout<<(ans[1][l][r]-ans[0][l][r]+M)%M<<"\n";
	}
	return 0;
 } 
```


---

## 作者：Lyrella (赞：2)

# 简要题意

给定长度为 $n(1≤n≤300)$ 的整数序列 $a(1≤a_i≤9)$，和整数区间 $[A,B](1≤A≤B≤10 
^{18}
 )$，有 $q$ 次询问，每次询问给出 $l,r$。每次询问开始，你有一个空串 $x$，你可以正序对 $a_{l∼r}$ 进行操作，操作有三种：$x→\overline{x+a_i}$，$x→\overline{a_i+x}$，或者什么也不做，求 $x$ 的取值在 $[A,B]$ 的不同的操作方案数，对 $10^9+7$ 取模。

# 题解

首先可以转化成两个 $\le x$ 的限制相减。下文 $m$ 表示限制的位数。

看到数据范围可以想到先将每个 $(l,r)$ 的答案做出来。发现不好向左边拓展，于是对于一个固定的 $l$，我们去求所有的 $r$。现在你能想到一个最简单的 dp，设 $f_{l,r}$ 表示区间 $[l,r]$ 的答案，但是显然这没法转移。所以我们考虑增加限制。

这里有个“妙手”，就是我们直接记录当前的一段和限制的一段之间的关系。具体的，就是多加入一点状态，设 $f_{l,r,i,j,0/1/2}$ 表示区间 $[l,r]$ 得到的长度为 $j-i+1$ 数和限制中第 $i$ 位到第 $j$ 位的关系是小于/等于/大于的方案数。此时状态的复杂度是 $O(m^2n^2)$，转移是 $O(1)$ 的，可以接受。

转移时就每次向右拓展一个位置，枚举一段限制，然后分类讨论填数后区间与限制的关系。比如我要把拓展的数填在后面，我就去看填数前区间和限制的关系。如果之前区间不等于限制那么填数后关系不会改变，因为比较数的大小是从高到低比较；但是如果关系是相等，我们就需要看填的这一位了。如果是填在前面也同理。

为了方便大家理解，这里写一下在填在后面的转移式：
$$
\begin{aligned}
f_{l,r,i,j,0}\rightarrow f_{l,r+1,i,j+1,0}\\
f_{l,r,i,j,1}\rightarrow f_{l,r+1,i,j+1,t}\\
f_{l,r,i,j,2}\rightarrow f_{l,r+1,i,j+1,2}\\
\end{aligned}
$$
其中 $t$ 的值由 $a_{r+1}$ 和限制的第 $j+1$ 位决定；填在前面同理。

最后答案是：
$$
f_{l,r,1,m,0}+f_{l,r,1,m,1}+\sum_{i=2}^m\sum_{j=0}^2f_{l,r,i,m,j}
$$
因为如果位数没有限制多肯定可行。

# 代码

```cpp
inline int cmp(int x, int y){return x == y ? 2 : x > y;}

void init(ll x){
    m = 0; while(x)b[++m] = x % 10, x /= 10;
    reverse(b + 1, b + 1 + m);
}

void sol(ll x, bool o){
    init(x);
    for(int l = 1; l <= n; ++l){
        for(int i = 0; i < 20; ++i)for(int j = 0; j < 20; ++j)f[i][j][0] = f[i][j][1] = f[i][j][2] = 0;
        for(int r = l; r <= n; ++r){
            for(int i = 1; i <= m; ++i)for(int j = m; j > i; --j){
                if(a[r] == b[i])for(int k = 0; k < 3; ++k)upd(f[i][j][k], f[i + 1][j][k]);
                else for(int k = 0; k < 3; ++k)upd(f[i][j][a[r] > b[i]], f[i + 1][j][k]);
                upd(f[i][j][0], f[i][j - 1][0]); upd(f[i][j][1], f[i][j - 1][1]);
                upd(f[i][j][cmp(a[r], b[j])], f[i][j - 1][2]);
            }
            for(int i = 1; i <= m; ++i)upd(f[i][i][cmp(a[r], b[i])], 2);
            for(int i = 1; i <= m; ++i){
                upd(ans[l][r][o], f[i][m][0]);
                upd(ans[l][r][o], f[i][m][2]);
                if(i > 1)upd(ans[l][r][o], f[i][m][1]);
            }
        }
    }
}
```

---

## 作者：Graphcity (赞：1)

首先将整数区间 $[A,B]$ 差分为 $(A-1,\infty)-(B,\infty)$ 两部分计算答案。

如果一个数的位数 $> x$ 的位数，显然是大于 $x$ 本身的。这个可以直接组合数计算。重点考虑位数与 $x$ 相同的情况。

我们需要判断此时加数的操作是否合法。根据队头和队尾的插入方式，我们可以把这个串分成左右两个部分。我们用两个指针 $a,b$ 表示左半部分扫描到了 $A$ 的第 $a$ 位，右半部分扫描到了 $B$ 的第 $b$ 位。显然，如果这个数要 $> x$，就必须得满足一段前缀与 $x$ 相同，然后下一位大于 $x$ 的下一位。

设四个状态 $0\sim 3$ 依次表示：目前与 $x$ 相同；已经合法；暂未合法，左半部分最前面的数 $>x$；暂未合法，左半部分最前面的数 $\le x$。显然这四个状态能够囊括所有的情况。判定的过程就是直接模拟。

接下来的部分类似于 DP 套 DP。枚举左端点 $l$，设 $f_{i,j,k,l}$ 为到达位置 $i$，两个指针分别为 $j,k$，状态为 $l$ 的方案数。直接枚举下一个数填在左半还是右半部分，或者是不填就行了。

时间复杂度 $O(n^2k^2)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=300,Maxk=5e4,Mod=1e9+7;

int n,m,a[Maxn+5],ans[Maxk+5];
int C[Maxn+5][Maxn+5],pw[Maxn+5];
int f[Maxn+5][20][20][4],w[20],s;
vector<pair<int,int>> v[Maxn+5];

inline void Init()
{
    C[0][0]=pw[0]=1; For(i,1,Maxn) pw[i]=2*pw[i-1]%Mod;
    For(i,1,Maxn) {C[i][0]=1; For(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;}
}
inline void Get(ll x)
{
    while(x) w[++s]=x%10,x/=10;
    reverse(w+1,w+s+1);
}
inline void add(int &x,int y) {x=(x+y)%Mod;}
inline void Solve(ll K,int tp)
{
    s=0,Get(K);
    For(l,1,n)
    {
        memset(f,0,sizeof(f));
        For(i,0,s) f[l-1][i][i+1][0]=f[l-1][i][i+1][3]=1;
        For(i,l,n)
        {
            memcpy(f[i],f[i-1],sizeof(f[i-1]));
            For(x,0,s) For(y,x+1,s+1)
            {
                if(x)
                {
                    if(a[i]<=w[x]) add(f[i][x-1][y][3],f[i-1][x][y][2]),
                                   add(f[i][x-1][y][3],f[i-1][x][y][3]);
                    if(a[i]==w[x]) add(f[i][x-1][y][1],f[i-1][x][y][2]),
                                   add(f[i][x-1][y][1],f[i-1][x][y][1]),
                                   add(f[i][x-1][y][0],f[i-1][x][y][0]);
                    if(a[i]>w[x])  add(f[i][x-1][y][2],f[i-1][x][y][2]),
                                   add(f[i][x-1][y][2],f[i-1][x][y][3]);
                }
                if(y<=s)
                {
                    add(f[i][x][y+1][2],f[i-1][x][y][2]);
                    add(f[i][x][y+1][3],f[i-1][x][y][3]);
                    add(f[i][x][y+1][1],f[i-1][x][y][1]);
                    if(a[i]==w[y]) add(f[i][x][y+1][0],f[i-1][x][y][0]);
                    if(a[i]>w[y])  add(f[i][x][y+1][1],f[i-1][x][y][0]);
                }
            }
        }
        for(auto [r,id]:v[l])
        {
            int res=(1ll*f[r][0][s+1][0]+f[r][0][s+1][1]+f[r][0][s+1][2])%Mod;
            For(i,s+1,r-l+1) res=(res+1ll*C[r-l+1][i]*pw[i])%Mod;
            ans[id]=(ans[id]+1ll*tp*res)%Mod;
        }
    }
}

int main()
{
    ll A,B; cin>>n>>A>>B; Init();
    For(i,1,n) cin>>a[i];
    cin>>m;
    For(i,1,m) {int l,r; cin>>l>>r; v[l].emplace_back(r,i);}
    Solve(A,1),Solve(B+1,Mod-1);
    For(i,1,m) cout<<ans[i]<<endl;
    return 0;
}
```



---

## 作者：ningago (赞：1)

简单容斥 $[A,B]=[1,B]/[1,A)$。

数位 DP 的关键点在于对是否抵上限的判定，以决策当前可以填哪些数。

容易发现 $Q$ 是假的，只需要对每个 $l,r$ 预处理答案即可。

如果考虑固定 $l$，向右增量 $r$，那么需要钦定堆顶与堆底的分界点，然后从中间两边填数，那么是不方便确定是否抵上限的。（可能可以做，因为我太笨了 QAQ）。

于是考虑倒着做，即固定 $r$，向左增量 $l$，那么此时需要钦定总共取的个数。每次增量即为在左侧或右侧填数。考虑这样的 dp 设计：

$dp_{l,r,0/1,0/1}$ 表示当前左指针在第 $l$ 位，右指针在第 $r$ 位，左侧是否在右侧抵上限（取 $1$）时会不合法，右侧是否抵上限。

其中“指针在第 $i$ 位”表示还未填第 $i$ 位。

不难对每个状态 $O(1)$ 转移。

最终答案状态即为 $dp_{i+1,i,p,q}(p\land q\ne true)$。

复杂度 $O(n^2 \log^2 B)$。

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctype.h>
#include <algorithm>
#include <vector>

char ST;

#define ll long long
//#define inf 0x3f3f3f3f
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f

#define debug(...) fprintf(stderr, __VA_ARGS__)
#define gline debug("now is #%d\n", __LINE__)
#define pii std::pair <int, int>
#define mkp std::make_pair
#define fi first
#define se second

int read()
{
	int x = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(;  isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

void ckmax(int &x, int y) { x = x > y ? x : y; }
void ckmin(int &x, int y) { x = x < y ? x : y; }

//#define mod 998244353
#define mod 1000000007
void plus_(int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
void mul_(int &x, int y) { x = 1ll * x * y % mod; }
int ksm(int a, int b)
{
	int res = 1;
	for(; b; b >>= 1, mul_(a, a)) if(b & 1) mul_(res, a);
	return res;
}

#define N 310
#define M 50010

int n, m, L, R;
int a[N];
int l_[M], r_[M], ans[M];
int dp[2][22][22][2][2];
std::vector <int> vecl[N];
std::vector <int> vecr[N];
int b[N][N];
int w[20];

void solve(int B, int op)
{
	for(int i = 1; i <= 18; i++, B /= 10)
		w[i] = B % 10;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			b[i][j] = 0;
	for(int r = n; r; r--)
	{
		for(int i = 1; i <= 19; i++)
			for(int j = 0; j <= 18; j++)
				for(int p = 0; p < 2; p++)
					for(int q = 0; q < 2; q++)
						dp[0][i][j][p][q] = 0;
		int suf = 1;
		for(int i = 18; ~i; i--)
		{
			dp[0][1][i][0][suf] = 1;
			if(w[i]) suf = 0;
		}
		int now = 0;
		for(int l = r; l; l--)
		{
			now ^= 1;
			for(int i = 1; i <= 19; i++)
				for(int j = 0; j <= 18; j++)
					for(int p = 0; p < 2; p++)
						for(int q = 0; q < 2; q++)
							dp[now][i][j][p][q] = 0;
			for(int i = 1; i <= 19; i++)
			{
				for(int j = i - 1; j <= 18; j++)
				{
					for(int p = 0; p < 2; p++)
					{
						for(int q = 0; q < 2; q++)
						{
							if(!dp[now ^ 1][i][j][p][q]) continue;
							plus_(dp[now][i][j][p][q], dp[now ^ 1][i][j][p][q]);
							if(i > j)
								continue;
							int p_;
							if(a[l] < w[i])      p_ = 0;
							else if(a[l] > w[i]) p_ = 1;
							else p_ = p;
							int q_ = q & (a[l] == w[j]);
							if(!q || a[l] <= w[j])
							{
								plus_(dp[now][i][j - 1][p][q_], dp[now ^ 1][i][j][p][q]);
							}
							plus_(dp[now][i + 1][j][p_][q], dp[now ^ 1][i][j][p][q]);
						}
					}
				}
			}
			for(int i = 1; i <= 19; i++)
			{
				plus_(b[l][r], dp[now][i][i - 1][0][0]);
				plus_(b[l][r], dp[now][i][i - 1][0][1]);
				plus_(b[l][r], dp[now][i][i - 1][1][0]);
			}
		}
	}
	for(int i = 1; i <= m; i++)
		plus_(ans[i], 1ll * op * b[l_[i]][r_[i]] % mod);
}

char ED;
signed main()
{
	n = read(), L = read(), R = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	m = read();
	for(int i = 1; i <= m; i++) 
		l_[i] = read(), r_[i] = read();
	solve(R, 1);
	if(L - 1)
		solve(L - 1, mod - 1); 
	for(int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：1)

不会数位 $\text{dp}$ 的小盆友请先学习数位 $\text{dp}$。

感觉不难。但最近降智严重。

首先先把答案差分一下，转化为求值域在 $[0, A]$ 的方案数。

因为 $q$ 是 $n^2$ 级别，最坏情况下所有可能的 $(l,r)$  都可能被问到，所以考虑预处理每一对 $(l,r)$ 的答案。

起初我想的是：先枚举左端点 $l$，然后枚举第一个数字与 $A$ 所对应的位置 $w$（第 $w$ 位），然后不断右移右端点进行数位 $\text{dp}$。这样的话，在枚举 $l,w$ 之后，状态应该是 $f_{r,a,b,c,d}$ 表示考虑 $a_l,a_{l+1}\cdots a_r$，从 $w$ 往左边填了 $a$ 位，往右边填了 $b$ 位，且当前左半部分是 $\leq$ 还是 $>$ $A$ 的对应位置，当前右半部分是 $<$ 还是 $=$ 还是 $>$ $A$ 的对应位置。按照数位 $\text{dp}$ 的套路讨论一下转移就行。

但这样的复杂度是 $\mathcal{O}(n^2w^3),w=18$ 且带有不太小的常数，可能无法通过。

思索之后可以注意到一件事：假设 $A$ 的位数是 $w_a$，若最终填出来的数的位数 $w_x<w_a$ 则肯定可行，且这种情况是容易计数的；若 $w_x>w_a$ 肯定不可行。

因此，只需要对 $w_x=w_a$ 的情况 $\text{dp}$ 就行了。虽然不知道第一个数的位置填在哪里。但知道左右两边填的最后一个数一定是 $A$ 的第 $1$ 位和第 $w_a$ 位！这启发了我倒着 $\text{dp}$，即枚举右端点 $r$，左移左端点 $l$ 来做。这样的好处是不需要枚举第一个填的数的位置 $w$，复杂度去掉了一个 $w$。状态设计部分与上述 $f_{,,,,}$ 是类似的。

贴一下代码：

```cpp
#include <bits/stdc++.h>
const int mod = 1e9 + 7;
inline int mul(int x, int y){
	return (int)(1ll * x * y % (1ll * mod));
}
inline int add(int x, int y){
	return x + y >= mod ? x + y - mod : x + y;
}
inline int minus(int x, int y){
	return x < y ? x - y + mod : x - y;
}
inline int Qpow(int x, int y){
	int r = 1;
	while(y){
		if(y & 1) r = mul(r, x);
		x = mul(x, x);
		y >>= 1;
	}
	return r;
}
inline void Add(int &x, int y){
	x = add(x, y);
	return ;
}
inline int read(){
	char c = getchar();
	int x = 0;
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}
int ans[305][305], n, q, C[305][305], pw[305], p[305];
char s1[22], s2[22];
int l1, l2;
int f[305][20][20][2][2];
inline void work(char *ss, int len, int contri){
	int s[22];
	for(int i = 1; i <= len; ++i) s[i] = ss[i] - '0';
	for(int l = 1; l <= n; ++l)
		for(int r = l; r <= n; ++r)
			for(int num = 0; num <= len - 1; ++num)
				ans[l][r] = add(ans[l][r], mul(mul(contri, C[r - l + 1][num]), pw[num]));
	for(int r = n; r >= 1; --r){
		memset(f, 0, sizeof f); // = : 0 / < : 1 // <= : 0 / > : 1
		f[r + 1][0][0][0][0] = 1;
		for(int l = r; l >= 1; --l)
			for(int a = 0; a <= len; ++a)
				for(int b = 0; b <= len && a + b <= len; ++b)
					for(int c = 0; c <= 1; ++c)
						for(int d = 0; d <= 1; ++d){
							Add(f[l][a][b][c][d], f[l + 1][a][b][c][d]);
							if(a + b < len){
								if(c == 1 || p[l] <= s[a + 1]){
									int nc;
									if(c == 1 || p[l] < s[a + 1]) nc = 1;
									else nc = 0;
									Add(f[l][a + 1][b][nc][d], f[l + 1][a][b][c][d]);
								} 
								int nd;
								if(p[l] > s[len - b] || (p[l] == s[len - b] && d == 1)) nd = 1;
								else nd = 0;
								Add(f[l][a][b + 1][c][nd], f[l + 1][a][b][c][d]);
							}
						}
		for(int l = 1; l <= r; ++l)
			for(int a = 0; a <= len; ++a){
				int t = add(add(f[l][a][len - a][0][0], f[l][a][len - a][1][0]), f[l][a][len - a][1][1]);
				ans[l][r] = add(ans[l][r], mul(contri, t));
			}
	}
	return ;
}
void solve(){
	for(int i = 0; i <= 300; ++i){
		C[i][0] = 1;
		for(int j = 1; j <= i; ++j)
			C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
	}
	pw[0] = 1;
	for(int i = 1; i <= 300; ++i) pw[i] = mul(2, pw[i - 1]);
	scanf("%d%s%s", &n, s1 + 1, s2 + 1);
	l1 = strlen(s1 + 1);
	l2 = strlen(s2 + 1); int sp;
	for(int i = l1; i >= 1; --i) 
		if(s1[i] != '0'){
			sp = i;
			break;
		}
	for(int i = l1; i >= sp + 1; --i) s1[i] = '9';
	--s1[sp];
	if(s1[1] == '0'){
		for(int i = 1; i <= l1 - 1; ++i) s1[i] = s1[i + 1];
		--l1;
	}
	for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
	work(s2, l2, 1);
	work(s1, l1, mod - 1);
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i){
		int l = read(), r = read();
		printf("%d\n", ans[l][r]); 
	} 
	return ;
}
int main(){
	int T = 1;
	while(T--) solve();
	return 0;
}



```


---

