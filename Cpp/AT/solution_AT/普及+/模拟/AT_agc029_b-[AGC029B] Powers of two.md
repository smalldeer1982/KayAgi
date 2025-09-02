# [AGC029B] Powers of two

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc029/tasks/agc029_b

高橋君は正整数が書かれたボールを $ N $ 個持っています。$ i $ 番目のボールに書かれている正整数は $ A_i $ です。 高橋君は $ N $ 個のボールからいくつかのペアを作って、それぞれのペアのボールに書かれた数の和が $ 2 $ べきとなるようにしたいです。 ただし、同じボールが複数のペアに属することはできません。 最大でいくつのペアが作れるか求めてください。

ただし、正整数が $ 2 $ べきであるとは、ある非負整数 $ t $ を用いて $ 2^t $ と書けることを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ A_i $ は整数

### Sample Explanation 1

$ 1 $ 番目のボールと $ 3 $ 番目のボールをペアにすることで、書かれた数の和が $ 4 $ となるペアを $ 1 $ つ作ることができます。 $ 2 $ 番目のボール同士をペアにできないことに注意してください。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
5
3 11 14 5 13```

### 输出

```
2```

# 题解

## 作者：noone___ (赞：7)

~~大佬的题解看起来好麻烦，蒟蒻来给一个更蒟蒻的做法。~~

首先能想到一个结论：**尽可能消去更大的数时最优**。

形式化的表达是：对于数 $a_j$ ，显然至多有一个 $i$ 满足 $i<j$ 且 $a_i+a_j=2^k$ ，如果不消去数对 $(a_i,a_j)$ ，则 $a_j$ 不可能被消去，最终答案不会更优。

再考虑题目中的 $2^t$ 以及 $A_i\leq 10^9$ ，则有 $a_i+a_j\leq 2^{30}$ 。

那么枚举范围内的所有 $2^t$ ，尺取法取当前符合条件的数对出来即可。


```cpp
#include <bits/stdc++.h>
#define rei register int
using namespace std;

const int N=2e5+100;
int a[N],n,ans;

int main(){
    scanf("%d",&n);
    for(rei i=1;i<=n;++i) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(rei k=1<<30;k;k>>=1){
        rei l=1,r=n;
        while(l<r){
            if(a[l]==-1 || (~a[r] && a[l]+a[r]<k)) ++l;
            else if(a[r]==-1 || a[l]+a[r]>k) --r;
            else ++ans,a[l]=a[r]=-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Jerrlee✅ (赞：2)

[AT 传送门](https://atcoder.jp/contests/agc029/tasks/agc029_b)

[洛谷传送门](https://www.luogu.com.cn/problem/AT4501)

这题就说下思路好了……
## 思路
这题思维难度蛮大的，乍一看看不出什么规律。

但如果我们把它排序看看？

`sort(a+1,a+n+1);`

看最后一个数，也就是 `a[n+1]`，能和它组成 $2$ 的非负整数次幂的数不可能比它大，所以只要看**大于**它（题目说了不能只有一个数）的幂即可。

比如样例二的 $14$，只有 $2$ 与它组成的 $16=2^4$ 才可能出现。

因为找不出一个数（例如 $18$ 组成的 $32$ 和 $50$ 组成的 $64$）与它组成更大的幂（如果有，$14$ 就不是最大值了）。

所以往后只需要按照如此的方法推下去，寻找组成的最大值即可。

代码也不难写，可以使用 `map<long long,int>`（前面是数，后面是出现的次数），`vector<long long>` 等 $\texttt{STL}$ 实现。

---

## 作者：Felix72 (赞：0)

带点权一般图匹配，虽然每个点的度数不大，但是还是不太好做的，尝试挖掘一点性质。

首先，图不会成环。否则必定存在 $x < y < z$ 满足 $(x, z), (y, z)$ 都合法。不妨设 $x + z = 2^a$，$y + z = 2^b$ 且 $a \neq b$，那么 $2^b - 2^a \geq 2^a$，即 $y - x \geq 2^a$，$y$ 比 $z$ 还大，这是不可能的。

其次，匹配关系形成的树的其中一个拓扑序是按点从大到小。这是因为上面已经证明了不存在一个数满足同时存在两个比它小的数可以匹配，那么不妨把可能存在的比自己小且能匹配的节点看作父亲，按照拓扑序跑树上贪心匹配就行了。

---

## 作者：Fading (赞：0)

这题太阴了，我一直 WA WA WA，拍了 30 分钟才出错...如果是现场我已经心态爆炸了。

这场 C 的细节也恶心的要死，感觉 D 比 BC 好 A 多了...

第一反应当然是图的匹配问题，肯定不是，我们要找性质。

因为我比较菜，初中数学都忘光了，所以我自闭了 15 分钟才发现：如果把权值相同的点缩成一个点，那么这是一棵树。证明还是比较简单的，因为一个数 $x$ 最多只能和前面的一个数拼成 $2$ 的幂。

那么树的匹配就是从叶子开始贪心，结束了？

不不不，$2^i$ 还可以和自己匹配，怎么办？

手玩一个数据“$2\ 2\ 2\ 6\ 6\ 6$”就可以发现，$2$ 个数的贡献最多是 $1$，那么能和其他数匹配一定更优。那么先匹配，剩下来的再两两匹配即可。

结束了？

大多数人的 dfs 直接以最小的节点为根开始，这样就~~歪打正着地~~ AC 了。然而我当时偷懒直接按照输入顺序开始，然后就 WA 了，？？？这是为什么？

冷静了 1 个小时，我找到了 hack 数据...$34\ 30\ 2\ 2$。如果从 $34$ 开始 dfs 那么就出事了...意会一下发现必须要以可以自己匹配的特殊点为根...所以就以最小的为根即可......

~~这个故事告诉我们比赛其实是很靠运气的。~~

时间复杂度 $O(n\log_2 n)$，因为还要离散化。



------------


事实上如果从无脑贪心而不是匹配入手你就不需要想这么多了。显然一个数 $x$ 最多只能和前面的一个数拼成 $2$ 的幂，所以就...

这是因为树匹配的本质就 tm 是贪心，想树匹配反而更麻烦了...

---

## 作者：ModestCoder_ (赞：0)

手玩数据

> 以5为例

> 00000101

> 比5大的最小的能和5匹配的是11（00001011）

> 再大，就是

> 00011011

> 00111011

> 01111011

> 11111011

> ……



>再假如10

>00001010


>与之匹配可以是
>00010110（22）

>00110110（54）

>01110110

>11110110

>……

结论，对于一个数$x$，另一个数$y>=x$

$x+y=2^p$

$y$一定是$x$最后一位1不动，之前全部取反，然后最高位想补多少1就补多少

发现一个数可以有很多比自己大的与之匹配的数

**但是一个数只有一个比自己小的与之匹配的数**（显然）

然后就可以用这个结论进行贪心

先把重复的数合并，再从大到小枚举

对于当前的数$x$，若存在一个数$y>x，x和y匹配$，且没有被用掉，那么这个$y$只可能跟$x$匹配了，不会再有更小的的数与$y$匹配，所以直接把$x和y$匹配一定是最优的

因为一个$x$存在很多匹配的$y$，这样的$y$也要从最大开始枚举才是正确的
然后判断是否存在可以用二分

位运算复杂度是$O(logn)$

二分也是$O(logn)$

所以总复杂度是$O(nlog^2n)$

Code ：

```cpp
#include <bits/stdc++.h>
#define maxn 200010
#define LL long long
using namespace std;
struct data{
	LL val;
	int cnt;
}b[maxn];
LL a[maxn], ans, power[50];
int n, m;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int find(LL basis, int pos){
	int l = pos, r = m, ans = 0;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (b[mid].val >= basis) r = mid - 1; else l = mid + 1;
		if (b[mid].val == basis) return ans = mid;
	}
	return ans;
}

int main(){
	freopen("Miyako.in", "r", stdin);
	freopen("Miyako.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++i){
		if (a[i] != a[i - 1]) b[++m].val = a[i], b[m].cnt = 1;
		else ++b[m].cnt;
	}
	power[0] = 1;
	for (int i = 1; i <= 32; ++i) power[i] = power[i - 1] << 1;
	b[0].val = -1;
	
//	for (int i = 1; i <= m; ++i) printf("%d %d\n", b[i].val, b[i].cnt);
	
	for (int i = m; i; --i){
		LL x = b[i].val;
		LL y = 0, flag = 0;
		int k = 0;
		for (; ; ++k){
			if (power[k] > x) break;
			if (x & power[k]){
				if (!flag) y += power[k];
				flag = 1;
			} else
			if (flag) y += power[k];
		}
		
//		printf("%lld\n", y);

		if (k > 30) continue;
//		if (y < x) y += power[k++];
		
		while (y + power[k] <= b[m].val) y += power[k++];
		while (y >= x && b[i].cnt > 0){
//			printf("   %lld\n", y);
			int p = find(y, i);
			if (b[p].val == y){
				if (x == y){
					ans += b[i].cnt / 2;
					b[i].cnt &= 1;
				} else{
					int sum = min(b[p].cnt, b[i].cnt);
					b[i].cnt -= sum, b[p].cnt -= sum;
					ans += sum;
				}
			}
			if (b[i].cnt == 0) break;
			y -= power[--k];
		}
	}
	printf("%d\n", ans);
	return 0;
}
```


---

