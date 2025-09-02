# Swap and Take

## 题目描述

You're given an array consisting of $ n $ integers. You have to perform $ n $ turns.

Initially your score is $ 0 $ .

On the $ i $ -th turn, you are allowed to leave the array as it is or swap any one pair of $ 2 $ adjacent elements in the array and change exactly one of them to $ 0 $ (and leave the value of other element unchanged) after swapping. In either case(whether you swap or not), after this you add $ a_i $ to your score.

What's the maximum possible score you can get?

## 说明/提示

In the first example, to get the maximum score we do as follows. Do nothing on the first turn, add $ 3 $ to the score. Swap the first and the second elements and turn $ 1 $ to $ 0 $ on the second turn, and add $ 3 $ to the score. The final score is $ 6 $ .

## 样例 #1

### 输入

```
2
3 1```

### 输出

```
6```

## 样例 #2

### 输入

```
5
7 3 9 6 12```

### 输出

```
52```

# 题解

## 作者：Miraik (赞：11)

容易发现最终贡献给答案的 $a_i$ 中的下标 $i$ 是不降的，且 $n$ 很小，我们直接设计一个非常暴力的状态： $f_{i,j,k}$ 表示做完第 $i$ 轮，第 $i$ 轮的贡献为 $a_j$，且我们在这轮结束后保留了 $k$ 次交换操作没有使用的最大答案。

（第三维的解释：这里我们并不是每一轮都关心其交换的位置，只需要在这个交换操作产生贡献的时候再计算）

转移：

- $f_{i,j,k} = f_{i-1,j,k}+a_j$

这个转移相当于此时 $a_{i-1}=j$，我们在这次操作交换了当前的 $a_{i-1}$ 与 $a_i$。

- $f_{i,j,k} = f_{i-1,t,k-1+j-i}+a_j (j\ge i,t<j)$

这个转移相当于此时将 $a_j$ 从第 $j$ 个位置一路换到第 $i$ 个位置，需要使用掉 $j-i$ 次操作。

直接暴力转移是 $O(n^4)$ 的，但注意到我们可以在做的时候就维护一下 $g_{i,j,k}$ 表示 $\max\{g_{i,t,k}\}(t\le j)$，这样转移的过程就不需要枚举 $t$ 了，时间复杂度即为 $O(n^3)$，可以通过此题。

初始化直接把 $i=1$ 的情况赋值一下就好。

[code](https://codeforces.com/contest/1736/submission/178636468)

---

## 作者：狂风之息 (赞：3)

显然先向右移再向左移是不优的，所以对答案有贡献的数（假设其为 $a_i$）一定是先移若干位至 $L_i$ 再向右移若干位至 $R_i$ 的，然后其对答案有贡献的区间为 $[L_i,R_i]$。注意可能会有 $R_i<L_i$ 也就是对答案没有贡献的 $i$。

因为交换过后另一个数会变为 $0$，所以显然任意两个数是不能相向移动的，也就是 $\forall i<j,R_i<L_j$。

考虑 dp，令 $f_{i,j,k}$ 表示当前考虑到第 $i$ 个数，当前 $R_i=j$，经过了 $k$ 次操作。那么有以下几种转移：

- $L_i=j$ 即第 $i$ 个数移到 $j$，转移的值为 $f_{i-1,j-1,k-|i-j|}+a_i$。
- $L_i<j$ 且 $R_i=j$ 即在已经左移过的基础上右移一次，转移值为 $f_{i,j-1,k-1}+a_i$。
- $R_i<L_i$ 即 $a_i$ 对答案没有贡献，转移值为 $f_{i-1,j,k}$。

于是 $f_{i,j,k}$ 即为三种转移值中的最大值。

因为第二种转移是在第一种转移的基础上的，所以第三种转移需要在完成前两种的计算之后再计入。

边界条件为 $f_{0,0,0}=0,\forall j<k,f_{i,j,k}=-\inf$。

跑一遍 dp 结束。实现很容易，以及这题空间开得很大可以不用滚动数组。

时间复杂度 $O(n^3)$。

---

## 作者：james1BadCreeper (赞：2)

先考虑一下交换的意义。贡献的指针是从左跑到右，且速度为 $1$，而我们的交换也只能一次交换相邻的一对，肯定不能跑过这个指针。也就是说，如果把贡献的数字在原序列中的下标写出来记作序列 $p$，那么一定有 $p_1\le p_2\le\cdots\le p_n$。若枚举这一轮要获得的分数，那么这个交换次数 $k$ 就可以用来简单地判断当前这个分数是否可以拿到。

设 $f_{i,j,k}$ 代表当前为第 $i$ 轮，要获取的贡献是 $a_j$，这一轮之后有 $k$ 次操作没有使用能够获得的最大价值，初始时有 $f_{1,1,1}=a_1,f_{1,2,0}=a_2$。这样我们的交换有两种选择：一种是将 $i$ 前面的交换到 $i$ 来获取其价值，二是在 $i$ 后选择两个数进行交换，为第 $i$ 轮以后做“准备“。因此有转移：

- 将上一轮的 $j$ 转过来，$f_{i,j,k}=f_{i-1,j,k}+a_j$；
- 将 $a_j$ 从 $j$ 换到 $i$，需要消耗 $j-i$ 次操作，那么 $f_{i,j,k}=f_{i-1,t,k-1+j-i}(j\ge i,t<j)$，$t<j$ 的原因是贡献下标单调不降，相等是上一种转移；$j\ge i$ 的原因是我们之前说的“速度”。


这样不难写出 $O(n^4)$ 的暴力：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, a[505], INF;
int f[505][505][505]; // 进行 i 轮，第 i 轮获得的分数是 a[j]，k 次没用

int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    memset(f, 0xbf, sizeof(f)); INF = -f[0][0][0];
    f[1][1][1] = a[1]; f[1][2][0] = a[2];
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 0; k <= n; ++k) {
                if (f[i - 1][j][k] != -INF) f[i][j][k] = f[i - 1][j][k] + a[j];
                if (j >= i && k - 1 + j - i >= 0 && k - 1 + j - i <= n) {
                    for (int t = 1; t < j; ++t)
                        if (f[i - 1][t][k - 1 + j - i] != -INF) f[i][j][k] = max(f[i][j][k], f[i - 1][t][k - 1 + j - i] + a[j]);
                }
            }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            ans = max(ans, f[n][i][j]);
    printf("%d\n", ans);
    return 0;
}
```

现在的问题就成了如何快速找到这个最大的 `f[i-1][t][k-1+j-i]`。我们单独记录一个数组 $g$，用 $g_{i,j,k}$ 代表 $\max\{f_{i,t,k}\mid 1\le t < j\}$ 即可。代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, a[505], INF;
int f[2][505][505]; // 进行 i 轮，第 i 轮获得的分数是 a[j]，k 次没用
int g[2][505][505];

int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    memset(f, 0xbf, sizeof(f)); INF = -f[0][0][0];
    memset(g, 0xbf, sizeof(g));
    f[1][1][1] = a[1]; f[1][2][0] = a[2];
    for (int i = 2; i <= n; ++i) g[1][i][1] = a[1];
    for (int i = 3; i <= n; ++i) g[1][i][0] = a[2];
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 0; k <= n; ++k) {
                int &dp = f[i & 1][j][k]; dp = -INF;
                if (f[(i - 1) & 1][j][k] != -INF) dp = f[(i - 1) & 1][j][k] + a[j];
                if (j >= i && k - 1 + j - i >= 0 && k - 1 + j - i <= n) {
                    if (g[(i - 1) & 1][j][k - 1 + j - i] != -INF) 
                        dp = max(dp, g[(i - 1) & 1][j][k - 1 + j - i] + a[j]);
                }
                g[i & 1][j + 1][k] = max(g[i & 1][j][k], dp);
            }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            ans = max(ans, f[n & 1][i][j]);
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：demonlover923 (赞：2)

我们考虑最终最优的答案中每个位置所加上的值在原序列中的位置, 记其为 $p_i$ , 显然的是 $p_1\leqslant p_2 \leqslant \dots\leqslant p_n$ , 答案即为 $\sum\limits_{i=1}^{n}{a_{p_i}}$ .

注意到 $n$ 很小, 考虑高次方 $dp$ 求解这个问题, 设 $f_{i,lst,k}$ 表示在第 $i$ 轮, $p_i=lst$ , 总共进行了 $k$ 交换的最大得分.

转移分别考虑 $p_{i}=p_{i-1}$ 和 $p_{i}>p_{i-1}$ , 前者 $f_{i,lst,k}=f_{i-1,lst,m-1}+a_{lst}$ , 后者 $f_{i,lst,k}=\max\limits_{j=1}^{lst-1}\{f_{i-1,j,k-(lst-i)}\}+a_{lst}$ .

后面的转移可以预处理前缀最大值, 时间复杂度 $\mathcal{O}(n^3)$ .

```cpp
inline bool main() {
	read(n);
	for (int i = 1;i <= n;++i)read(a[i]);
	memset(f,128,sizeof(f));
	int now = 0;
	for (int i = 1;i <= n;++i) {
		for (int j = 1;j <= n;++j)
			for (int k = 0;k <= i;++k) {
				if (k)f[now][j][k] = f[now^1][j][k-1]+a[j];
				if (j >= i) {
					int need = j-i;
					if (need > k)continue;
					f[now][j][k] = max(f[now][j][k],pre[j-1][k-need]+a[j]);
				}
			}
		for (int j = 1;j <= n;++j)for (int k = 0;k <= i;++k)pre[j][k] = f[now][j][k];
		for (int j = 1;j <= n;++j)for (int k = 0;k <= i;++k) {
			pre[j][k] = max(pre[j][k],pre[j-1][k]);
			ans = max(ans,pre[j][k]);
		}
		now ^= 1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：User_Authorized (赞：1)

设在第 $i$ 次操作后产生贡献的值为初始序列的 $a_{p_i}$，可以发现产生的贡献的指针移动方式为每次向后移动 $1$，而通过交换数字最多可以使得某个数字每次向后移动 $1$，由此可以得出每次产生贡献的位置单调不减，即 $p_1 \le p_2 \le \cdots \le p_n$。

这样若某次操作后的贡献点位置为 $k_0$，那么对于这之后的所有操作的贡献点 $k$，均有 $k_0 \le k$，而在最优策略下，若 $k_0$ 产生贡献一定不会影响到 $k_0$ 之后的位置，因此决策不具有后效性，可以进行 DP。

设 $f_{i, j, k}$ 表示在进行了 $j$ 次操作后 $a_k$ 在第 $i$ 个位置产生了贡献的情况下最大的分数值，转移考虑 $p_i$ 与 $p_{i - 1}$ 之间的关系

- 若 $p_{i - 1} = p_i$，那么有 $f_{i, j, k} \leftarrow f_{i - 1, j - 1, k} + a_k$
- 若 $p_{i - 1} \le p_i$，通过枚举 $p_{i - 1}$ 的值可以实现转移，有 $$f_{i, j, k} = \max\limits_{1 \le k^{\prime} < k} f_{i - 1, j - \left(k - i\right), k^{\prime}} + a_k$$，通过前缀最大值优化即可实现 $\mathcal{O}(1)$ 转移。

总复杂度 $\mathcal{O}(N^3)$，可以通过。

---

## 作者：小木虫 (赞：1)

### Preface  
这个题做完 3 个月后才想起来补一篇题解...  
### Problem  
给定一个长为 $n$ 的正整数序列 $a$。初始你的分数为 $0$，需要进行 $n$ 轮操作。

在第 $i$ 轮，你可以选择交换两个相邻的数并将其中一个变为 $0$，也可以啥都不干。无论是否交换，第 $i$ 轮结束后你的分数会多 $a_i$。

求你最大能得到的分数。  

### Solution  
我们设计出一个 dp 状态使得没有后效性，所以我们设 $f_{i,j,k}$ 代表第 $i$ 次操作，攒下 $j$ 次交换机会，目前位置为 $a_k$。  

为什么这么设计？  
因为你注意到，你可能会在指针扫到 $i$ 的时候交换后面的数字，我们直接钦定影响到这次指针扫到的地方的贡献就是那个时候产生的，也就是说我们必须在那个时候更改这个值。  

然后我们发现，如果你在第 $i$ 个位置，那么只有一些操作是有贡献的，即从前面的邻居转过来和攒出来的从后面转过来的值。  

然后你发现，如果从后面转过来，你钦定这个值，然后消耗的操作次数就是这个值和目前位置的距离，然后转过来的过程必定使得除了你钦定这个值以外的其他值变为 0。  

然后你就可以发现一件事情，即只有 $k\leq i$ 的值可以支持这次不操作可以继承下一个值，否则就只能继承 0。  

然后你也发现了另一个转移，即保留现在这个值，将这次新加的机会把当前值转到下一个。  

然后你发现这个转移是非常好推的，复杂度为 $O(n^4)$。  
具体的转移方程请读者自行思考。  
稍微进行一下前缀和优化便可优化为 $O(n^3)$。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=505;
int n,f[N][N][N],a[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;for(int i=1;i<=n;i++)cin>>a[i];
	memset(f,-0x3f,sizeof(f));f[0][0][0]=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(i==0)break;
			int MAX=-1e9;
			for(int z=0;z<=i;z++)MAX=max(f[i-1][j][z],MAX);
			for(int k=i+1;k<=min(i+j,n)+1;k++){
				//for(int z=0;z<=i;z++)
					f[i][j-(k-i)+1][k]=max(f[i][j-(k-i)+1][k],MAX+a[k]);
			}
		}
		for(int j=1;j<=n;j++){
			for(int k=0;k<=i;k++)
				f[i+1][j][i+1]=max(f[i][j-1][k]+a[i+1],f[i+1][j][i+1]);
			for(int k=i+1;k<=n;k++)
				f[i+1][j][0]=max(f[i][j-1][k],f[i+1][j][0]);
		}
		for(int j=1;j<=n;j++){
			for(int z=0;z<=n;z++)
				f[i+1][j-1][z]=max(f[i+1][j-1][z],f[i][j-1][z]+a[z]);
		}
	}int res=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++)
			res=max(res,f[n][i][j]);
	}
	cout<<res;
	return 0;
}
```


---

