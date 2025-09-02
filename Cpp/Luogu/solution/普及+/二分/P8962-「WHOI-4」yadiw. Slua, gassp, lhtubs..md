# 「WHOI-4」yadiw. Slua, gassp, lhtubs.

## 题目背景

> If you know at least 3 of these things and you are not red — you are doing it wrong. Stop learning useless algorithms, go and solve some problems, learn how to use binary search.


## 题目描述

小 F 有一个奇妙的数组 $a$，$a$ 中没有重复的元素，长度为 $n$，他使用`std::sort`将他排序了，认为它是有序的，所以他正在使用这样的方法进行二分查找。显然，能否查到只和数列的离散化结果有关，所以你可以直接把 $a$ 看作 $1\sim n$ 的一个排列。

```cpp
int search(int key) {
  int l = 1, r = n;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (a[mid] < key)
      l = mid + 1;
    else if (a[mid] == key)
      return mid;
    else
      r = mid - 1;
  }
  return -1;
}
```

不幸的是，小 W 为了让他戒掉万能头，在`bits/stdc++.h`中写了`#define sort random_shuffle`，这意味着 $a$ 实际是一个随机的排列。

现在，对于所有在 $1$ 到 $N$ 范围内的 $n$，以及所有在 $1$ 到 $n$ 范围内的 $k$，在 $a$ 数列的所有排列中，有几个可以正确地找到第 $k$ 小的元素 $key$（即返回值非 $-1$）？由于答案可能过大，请输出它对给定模数 $p$ 取模的结果。

## 说明/提示

**数据范围**

**本题采用 Subtask 评测。**

- Subtask 1（$10$ pts）：$N=10$，$ p\ge998244352$；
- Subtask 2（$25$ pts）：$N=100$，$p\ge1009$ **且为素数**；
- Subtask 3（$25$ pts）：$N=400$，$p\ge1009$ **且为素数**；
- Subtask 4（$40$ pts）：$N=400$。

对于所有数据，$10\le N\le 400$，$ 2\le p\le998244353$。

## 样例 #1

### 输入

```
998244353 5
```

### 输出

```
1
1 2
4 4 4
12 12 14 18
48 54 60 66 72```

# 题解

## 作者：Register_int (赞：7)

首先考虑这个二分过程。我们可以发现，只要结果找到的点固定，过程中的所有 $l,r,mid$ 都会固定。所以考虑枚举每个位置 $k$，模拟二分过程判断每个 $mid$ 点的值该小于 $a_k$ 还是大于 $a_k$。设两者的数量分别为妙妙函数 $f(k),g(k)$，枚举 $a_k$ 的值，先选出这些固定大于或小于 $a_k$ 的数。我们就可以通过组合计数得到妙妙公式：

$$ans_i=\sum^n_{i=1}A^{i-1}_{f(k)}A^{n-i}_{f(k)}(n-f(k)-g(k)-1)!$$

剩下的直接枚举即可。有两点要注意的地方：

1. 注意枚举顺序，先枚举位置再枚举填什么数。不然你就会发现你凭空多了个 $\log$ 然后 T 飞。（@TernaryTree）
2. 模数不是素数。可以递推组合数再乘上阶乘得到排列数。（@我自己）

# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 4e2 + 10;

int n, mod;

ll ans[MAXN], fac[MAXN], c[MAXN][MAXN];

int main() {
	scanf("%d%d", &mod, &n), *fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	for (int i = 0; i <= n; i++) c[i][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	}
	for (int m = 1; m <= n; m++) {
		for (int i = 1; i <= m; i++) ans[i] = 0;
		for (int k = 1, l, r, mid, x, y, t; k <= m; k++) {
			l = 1, r = m, x = y = 0;
			while (l <= r) {
				mid = l + r >> 1;
				if (mid == k) break;
				k < mid ? (r = mid - 1, y++) : (l = mid + 1, x++);
			}
			t = fac[m - x - y - 1] % mod * fac[x] % mod * fac[y] % mod;
			for (int i = x + 1; i <= m - y; i++) {
				ans[i] = (ans[i] + c[i - 1][x] * c[m - i][y] % mod * t % mod) % mod;
			}
		}
		for (int i = 1; i <= m; i++) printf("%lld ", ans[i]); puts("");
	}
}
```

---

## 作者：OIer_Eternity (赞：6)

$\mathrm{Upd~2023.2.3}$：优化了排列数的预处理，并且对 $cnt_1,cnt_2$ 进行了预处理，复杂度由 $O(n^3\log n)$ 降低至 $O(n^3)$，速度快了近一倍。感谢大佬 @[0x3b800001](https://www.luogu.com.cn/user/306090) 提出的意见~

### 题意简述

- 对于长度为 $i\in[1,n]$ 的一个 $[1,i]$ 的无序排列，求能够通过二分的方法查询到第 $k\in[1,i]$ 小的元素的序列个数。
- $10\le n\le400$，答案对给定的 $2\le p\le998244353$ 取模（$p$ 不一定为质数）。

### 题目分析

首先我们考虑，若需要正确地找到第 $k$ 小的元素（我们称之为 $x$），则对于每一个 $Mid$，$a_{Mid}$ 与 $x$ 的大小关系是确定的。

换言之，若 $x$ 位于位置 $p$，我们可以模拟二分的过程：

对于当前的 $Mid$，若 $p<Mid$ 则必然 $a_{Mid}>x$，若 $p>Mid$ 则必然 $a_{Mid}<x$，否则已经找到了 $x$。

那么我们就能求出 $a$ 数列中，必须小于 $x$ 以及必须大于 $x$ 的数的个数，分别记作 $cnt_1$ 和 $cnt_2$，则大小关系与 $x$ 不确定的个数为 $n-cnt_1-cnt_2-1$（总数减小于减大于减等于的个数），其中 $n$ 为数列长度。则满足此大小关系的数列的个数为：$A_{x-1}^{cnt_1}\times A_{n-x}^{cnt_2}\times A_{n-cnt_1-cnt_2-1}^{n-cnt_1-cnt_2-1}\bmod p$。

则我们可以设立三层循环：第一层循环 $i\in[1,n]$ 表示数列长度，第二层循环 $j\in[1,i]$ 表示需要找到第 $j$ 大的元素，第三层循环 $k\in[1,i]$ 表示第 $j$ 大元素位于位置 $k$ 时的方案数。若设 $ans_{(i,j)}$ 为输出中第 $i$ 行第 $j$ 列，则
$$
ans_{(i,j)}=\Big(\sum_{k=1}^iA_{j-1}^{cnt_1}\times A_{i-j}^{cnt_2}\times A_{i-cnt_1-cnt_2-1}^{i-cnt_1-cnt_2-1}\Big)\bmod p
$$
若我们暴力求$ A$，那么复杂度会达到 $O(n^4\log n)$，显然不行；那么我们可以 $O(n^2)$ 预处理出 $\forall i\in[1,n],j\in[1,i]$，$C_i^j$ 的值，$O(n)$ 预处理出 $\forall i\in[1,n]$，$i!$ 的值，再结合排列数和阶乘 $O(n^2)$ 预处理出 $A_i^j=C_i^j\times j!$ 降低复杂度即可。并且可以$O(n^2\log n)$ 预处理出 $cnt_1,cnt_2$ ，最终复杂度为 $O(n^3)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int p,n,C[500][500],frac[500]={1},A[500][500],cnt1[500][500],cnt2[500][500]; // cnt1表示<的个数 cnt2表示>的个数
int main(){
    scanf("%d%d",&p,&n);
    for (int i=1;i<=n;i++) frac[i]=1ll*frac[i-1]*i%p; // 预处理阶乘 
    for (int i=0;i<=n;i++) C[i][0]=C[i][i]=1;
    for (int i=1;i<=n;i++) for (int j=1;j<i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%p; // 预处理组合数 
    for (int i=0;i<=n;i++) for (int j=0;j<=i;j++) A[i][j]=1ll*C[i][j]*frac[j]%p; // 组合数*阶乘=排列数 
    for (int i=1;i<=n;i++) // 预处理 cnt1,cnt2
    	for (int k=1;k<=i;k++){
    		int L=1,R=i;
			while (L<R){
				int Mid=(L+R)>>1;
				if (k==Mid) break;
				if (k<Mid) cnt2[i][k]++,R=Mid-1;
				else cnt1[i][k]++,L=Mid+1;
            }
		}
    for (int i=1;i<=n;i++){
        for (int j=1;j<=i;j++){
            int cnt=0;
			// i个元素中,j位于k时能够找到j的方案数
            for (int k=1;k<=i;k++) cnt=(cnt+1ll*A[j-1][cnt1[i][k]]*A[i-j][cnt2[i][k]]%p*A[i-cnt1[i][k]-cnt2[i][k]-1][i-cnt1[i][k]-cnt2[i][k]-1]%p)%p;
            printf("%d ",cnt);
        }
        puts("");
    }
    return 0;
}
```

---

