# [USACO23JAN] Lights Off G

## 题目描述

给定正整数 $N$，和两个长为 $N$ 的 $01$ 序列 $a$ 和 $b$。定义一次操作为：

1. 将 $b$ 序列中的一个值翻转（即 $0$ 变成 $1$，$1$ 变成 $0$，下同）。
2. 对于 $b$ 序列中每个值为 $1$ 的位置，将 $a$ 序列中对应位置的值翻转。
3. 将 $b$ 序列向右循环移位 $1$ 位。即若当前 $b$ 序列为 $b_1b_2\cdots b_{n}$，则接下来变为 $b_{n}b_1b_2\cdots b_{n-1}$。

有 $T$ 次询问，对每一次询问，你需要回答出至少需要几次操作，才能使 $a$ 序列中每一个位置的值都变为 $0$。

## 样例 #1

### 输入

```
4 3
000 101
101 100
110 000
111 000```

### 输出

```
0
1
3
2```

## 样例 #2

### 输入

```
1 10
1100010000 1000011000```

### 输出

```
2```

# 题解

## 作者：OMG_wc (赞：16)

答案的上限为 $3n$ ——先通过最多 $n$ 次把所有开关关闭，然后每连续两次，分别打开、关闭某个开关来把某个灯关掉。

容易发现，初始开关状态和每次翻转开关对最终状态的影响是可以独立结算的。

若一共操作 $m$ 次，那么第 $i$ 次变换开关对最终灯的影响是翻转了连续的 $m-i+1$ 个灯。也就是说这 $m$ 次操作的总影响，等价于分别翻转了连续的 $1,2,3,\cdots,m$ 个灯。注意本文所有**连续**是指**循环连续**，并且在 $m>n$ 时会越来越短，因为异或抵消了。

而初始开关对灯的影响只需简单模拟，然后希望能 $O(1)$ 判断出剩余的灯能否由 $i$ 次操作来关闭。

虽然是多组数据，但是所有的 $n$ 是相等的，这暗示需要预处理某个东西。

设 $f_{i,j}$ 表示前 $i$ 次操作能否得到状态 $j$，然后从 $f_{i-1,j\oplus x}$  转移过来，其中 $x$ 是取所有长度为  $i$  的连续段，代码如下：

```c++
const int wc = 3 * n;
auto shift = [&](int x) {
    return (x >> 1) + ((x & 1) << n - 1);
};
f[0][0] = 1;
for (int i = 1, z = 0; i <= wc; i++) {
    z ^= 1 << (i - 1) % n;
    for (int j = 0; j < 1 << n; j++) {
        int x = z;
        for (int k = 0; k < n; k++, x = shift(x)) {
            f[i][j] |= f[i - 1][j ^ x];
        }
    }
}
```

 $O(n^2\cdot 2^n)$ 这个复杂度在洛谷是能卡过的，但是 USACO 的机器不一定，考虑把最内层的 $n$ 次循环去掉。

两个状态 $j_1$ 和 $j_2$ 如果是能循环移动达到的，那么显然 $f_{i,j_1}=f_{i,j_2}$，可以用最小的 $j$ 作为代表元素 $p_j$。这样右移 $x$ 的话，相同的 $j$ 只要算一次，循环不同的 $j$ 的个数似乎是 $O(\frac{2^n}{n})$ 级别。或者干脆反过来，固定 $x$ 移动 $j$ ，这样就去掉内层的循环了。

时间复杂度 $O(n\cdot 2^n+nT)$，代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 100005;

bool f[61][1 << 20];
int p[1 << 20];
int main() {
    int _, n;
    scanf("%d%d", &_, &n);
    const int wc = 3 * n;
    auto shift = [&](int x) {
        return (x >> 1) + ((x & 1) << n - 1);
    };
    memset(p, -1, sizeof p);
    for (int i = 0; i < 1 << n; i++) {
        int x = i;
        while (p[x] == -1) p[x] = i, x = shift(x);
    }
    f[0][0] = 1;
    for (int i = 1, z = 0; i <= wc; i++) {
        z ^= 1 << (i - 1) % n;
        for (int j = 0; j < 1 << n; j++) {
            f[i][p[j]] |= f[i - 1][p[j ^ z]];
        }
    }
    while (_--) {
        int A = 0, B = 0;
        for (int i = n - 1, x; i >= 0; i--) {
            scanf("%1d", &x);
            A |= x << i;
        }
        for (int i = n - 1, x; i >= 0; i--) {
            scanf("%1d", &x);
            B |= x << i;
        }
        if (A == 0) {
            puts("0");
            continue;
        }
        for (int i = 1;; i++, B = shift(B)) {
            A ^= B;
            if (f[i][p[A]]) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
```



---

## 作者：Xy_top (赞：15)

[更好的阅读体验](https://www.cnblogs.com/Xy-top/p/17093107.html)

第一篇蓝题题解

### 题意简化
有 $n$ 个开关分别对应 $n$ 盏灯，开关的状态有两种：激活，失活。灯的状态也有两种：开，关。现在你想要进行多轮操作后把灯全部关掉，你的操作如下：先选择一个开关的位置，将它取反（原先激活变成失活，原先失活变成激活）。选择完开关位置后将所有激活的开关按下，取反它对应的灯。取反灯之后所有开关进入旋转，最后一个开关到第一个。（原先开关假设为 $S_1$，$S_2\cdots S_n$，旋转后变成 $S_n$，$S_1$，$S_2\cdots S_{n-1}$）
### 思考算法
先来看数据范围 $T \leq 2\cdot 10^5$，$n\leq 20$，看到灯的 $01$ 状态，差不多就是状压啦。再一看 $T\leq 2\cdot 10^5$，那肯定是预处理啦！

如果选择预处理灯的所有状态以及开关的所有状态，总状态数就是 $O(2^{40})$ 爆炸，并且大部分的还用不到，那么我们就考虑只预处理其中一个。

问题来了：我们预处理灯的状态还是开关的状态呢？很显然是灯的状态，因为最后要求把灯都关掉，开关关不关无所谓。
### 深度分析
可是不难发现开关的状态对最少步数也有影响，我们考虑把开关的影响消去。并且，预处理灯的状态时需要设定一个开关的状态才可以，姑且先把开关的状态全部设成 $0$。把这个开关叫做我的开关。

我们发现操作二和操作三是自动的，即不需要选择的。为了消除影响，要把我的开关和实际开关联系起来。

于是把 $1$，$2$ 和 $3$ 操作分开来处理。我的开关用来做 $1$ 操作（它也会改变灯的状态，也会旋转。），实际开关每一轮自动做 $2$，$3$ 操作。

但是我们仍然需要认识到对我的开关进行单点修改相当于对实际开关进行单点修改。（理解不了看完后面的再来看可能更好理解，不懂的话先忽略）
### 具体操作
每一轮先用实际开关，$2$ 操作改变灯。然后再看我的开关，通过 $2$ 操作再改变灯，每一轮开始时我们都可以改变我的开关的一个位置的状态。此时发现我的开关初始时全为 $0$ 是对的，无法对灯进行任何操作（因为我们还没做 $1$ 操作），每一轮结束后进行旋转操作。

可是这样每一轮还是很棘手，我们发现对我的开关进行单点修改操作可以留着想做的时候一起做就行了，预处理一下就完事儿，预处理的东西就是灯的状态为 $i$ 时，开关状态为全 0 时能否在 $j$ 步之内关掉灯。时间复杂度 $O(n^2\times 2^n + T\times n^2)$。没看懂？没事儿，确实有点难理解。
### For example：
#### Example 1：
```
000
101
```
初始时我们先看灯的状态为 ``000``，开关的状态为 ``000`` 时，能否 $0$ 步搞定（注意：步数必须要全部用完，不能少用），发现可以，答案为当前轮数减一，$0$。
#### Example 2：
```
101
100
```
先看灯的状态为 ``101``，开关的状态还是 ``000`` 时（下文省略不写），能否用 $0$ 步搞定，不可以。先用实际开关操作灯，此时灯变成 ``001``，开关变成了 ``010``。第一轮的操作我们就留着了。

第二轮时我们先看把之前的操作都用上能否关掉。即灯为 ``001`` 时能不能一步关掉，发现可以，那么就把当初的单点修改做了。答案为轮数减一，$1$。

（注：此时若想一步用 ``000`` 开关关掉 ``001`` 仅需要给第三个开关做单点修改。那么就相当于给实际开关第三个地方做单点修改啦！就是在第一步时把实际开关变成 ``101``）

如果你觉得有一点理解了，那么再来看最后这个：
#### Example 3：
```
1000
1011
```

可以自己先模拟一下，再来看我的过程。

首先看灯的状态为 ``1000`` 能否 $0$ 步搞定？不可以，那么用实际开关对灯进行操作，变成 ``0011``，实际开关旋转后变成 ``1101``，进行第二轮。

第二轮开始前看一下灯的状态为 ``0011`` 能否 $1$ 步搞定，发现还是不行，继续操作然后旋转。灯变成 ``1110``，实际开关旋转后变成 ``1110``。

第三轮之前再看下灯为 ``1110``，能否 $2$ 步搞定，可以。答案为轮数减一，$2$。

补充：方法是先单点修改第一个开关，然后灯变成 ``0110``，开关旋转变成 ``0100``，再单点修改第三个就行。把对我的开关的操作移动到实际开关上看一看？第一轮单点修改第一个，变成 ``0011``，灯变成 ``1011``，开关旋转后变成 ``1001``，接着第二轮修改第三个，变成 ``1011``，正好搞定，我们的方法是对的。

``talk is cheap, show me the code：``
```cpp
#include <iostream>
using namespace std;
string s,t;
int T, n;
int g[45][22], mask[22];
bool f[45][1 << 21];
int calc (int s, int t) {
    if (s == 0) return 0;
    for (int i = 1; i <= 2 * n; i ++) {
        int vis = s;
        for (int j = 0; j < n; j ++) if (t & (1 << j) ) vis = vis ^ g[i][j];
        if (f[i][vis]) return i;
    }
}
int main() {
    f[0][0] = 1;
    cin >> T >> n;
    for (int i = 0; i <= n; i ++) mask[i] = 1 << i;
    int N = 1 << n;
    for (int k = 0; k < n; k ++)
        for (int i = 1; i <= 2 * n; i ++)
            for (int j = 0; j < i; j ++) g[i][k] ^= mask[(k + j) % n];
    for (int i = 1; i <= 2 * n; i ++) for (int j = 0; j < N; j ++) {
            if (!f[i - 1][j]) continue;
            for (int k = 0; k < n; k ++){
                int vis = j;
                vis ^= g[i][k];
                f[i][vis] = 1;
            }
        }
    while (T --){
        cin >> s >> t;
        int S = 0, T = 0;
        for (int i = 0; i < n; i ++) {
            if (s[i] == '1') S ^= (1 << i);
            if (t[i] == '1') T ^= (1 << i);
        }
        cout << calc(S, T) << "\n";
    }
    return 0;
}
```


---

## 作者：2017gdgzoi999 (赞：9)

从让 $d$ 从 $0$ 开始逐步递增，每次判定 **恰好** $d$ 步操作是否能得到目标状态。

将二序列的状态看作二进制数，设 $c_i(s)$ 为状态 $s$ 循环移动 $i$ 位的结果。

首先忽略每次的反转 $b$ 序列操作，若初始 $a$ 序列状态为 $s$、$b$ 序列状态为 $t$，则 $d$ 步后 $a$ 序列的状态为 $r_d'=s\oplus(\oplus_{i=0}^{d-1}c_i(t))$。（$\oplus$ 表示二进制按位异或）

接下来考虑反转 $b$ 序列的操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/xs03a2i1.png)

由上图可发现规律：第 $i$ 次反转相当于让最终结果连续的 $d-i+1$ 位反转（注意序列是首尾相接的），则问题转化为：

使最终结果 $r$ 初值为 $r_d'$，共 $d$ 次操作，第 $i$ 次操作反转 $r$ 循环序列上的连续 $i$ 位，问是否有一种操作方案使得 $r$ 在所有反转完成后值为 $0$。

设 $f_{i,j}$ 表示 $j$ 状态是否可用 **恰好** $i$ 次操作得到 $0$。要询问恰好 $d$ 步操作能否得到目标状态，只用判断 $f_{d,r_d'}$ 的值即可。

经程序验证，对于所有状态 $j$，都有 $f_{n,j}=\operatorname{true}$，则 **最小步数一定不超过** $n$。因为所有询问中 $n$ 相等，只用在询问前预处理出所有的 $f_{i,j}$ 即可。因为 $i$ 次反转操作实质上是 $i-1$ 次的操作基础上反转长为 $i$ 的段得到的，因此预处理时时间复杂度为 $\Theta(2^nn^2)$，每次询问时间复杂度 $\Theta(n)$。

```cpp
main() {
	int m, q; scanf("%d%d",&q,&m);
	int n=(1<<m); f[0][0]=true;
	sum[0]=1; for (int i=1; i<=m; ++i) sum[i]=sum[i-1]|(1<<i);
	for (int i=1; i<=m; ++i) { // 预处理 f 数组
		for (int j=0; j<m; ++j) {
			int r=j+i-1, sta=sum[min(m-1,r)];
			// i-1 次操作结果异或长 i 的连续段即为 i 次操作结果
			if (j) sta^=sum[j-1];
			if (r>=m) sta|=sum[r-m]; // 考虑从末尾循环到开头的部分
			for (int k=0; k<n; ++k) f[i][k^sta]|=f[i-1][k];
		}
	}
	int mm = m-1;
	while (q--) {
		int x=read(), t=read();
		for (int i=0; i<=m; ++i) { // 枚举判定答案是否为 i
			if (f[i][x]) { // 此时 x = r_i'
				printf("%d\n",i); break;
			}
			x ^= t; // r_{i+1}' 在 r_i' 的基础上多异或了一次 b 的循环移位
			t = (t>>1)|((t&1)<<mm); // 将 b 的状态循环移位
		}
	}
	return 0;
}
```

---

## 作者：luoguhandongheng (赞：6)

(2024NOV6th,MAGA!!!!)

金组难度巅峰了。

### 题意

给定 $T$ 对长度为 $n$ 的 $01$ 序列 $a$ 和 $b$。定义一次操作为：

1. 选择 $b$ 中一个元素，并取反。
2. $a \oplus b \to a$（$\oplus$ 表示按位异或）。
3. 将 $b$ 右旋一位。

问最少多少次操作能使 $a$ 全部变成 $0$。

### 心路历程

看错好几次题......需要注意一次操作是指完整执行三个步骤。

一开始想建图。考虑所有可能的 $2^n$ 种 $01$ 序列 $s$，$t$ 为 $s$ 挑一个位置取反并右旋一位的可能序列（显然有 $n$ 个），每个 $s$ 都向 $t$ 建有向边。所求的是一条长度最短且途径序列异或和为 $a$ 的路径。然后就发现好像只是给爆搜加了个好听的名字，这个图不怎么特殊，也没有发现什么性质，至此本题思考方向可以说完全跑偏。

好啦看题解。

### 正解

先形式化地写一下题目的条件。设总共做了 $k$ 次操作，记 $b^x$ 为做了 $x$ 次操作后的 $b$ 序列。

则题目条件为：$(\oplus_{x=1}^{k} b^x) \oplus a =0$。

写完了之后就发现，由于 $a$ 是给定的，实际上只需要关注 $(\oplus_{x=1}^{k} b^x)$ 即可，因此以下分析均忽略步骤二。

> 观察一：只有第一个步骤是不确定的。

这给我们启发：可以将第一个步骤与第三个步骤分开处理。第三个步骤很简单，做了 $i$ 次操作就直接把 $b$ 右旋 $i$ 次即可。所以考虑步骤一对最终结果的贡献。

> 观察二：步数的上限是 $3 \times n$。

先把 $b$ 全部变成 $0$（最多 $n$ 次），再对于现在 $a$ 中每个为 $1$ 的位置，对对应的 $b$ 中位置取反（这样 $b$ 中就有且仅有了一个 $1$），再将 $b$ 变为全 $0$（最多 $n$ 轮，每轮要 $2$ 次操作）。故上限为 $3\times n$。

> 观察三：记将 $b$ 右旋 $d$ 次的结果为 $d(b)$，第 $i$ 次操作选择取反的位置为 $pos_i$。若总共进行 $k$ 次操作，则 $(\oplus_{x=1}^{k} b^x)$ 等于 $\oplus_{x=1}^{k} x(b)$ 对以下区间（旋转意义下，以下分析均是）取反的结果。
>
> $$
> [pos_1,pos_1+k-1] \\
> [pos_2,pos_2+k-2] \\
> \dots \\
> [pos_i,pos_i,+k-i]\\
> [pos_k,pos_k]
> $$

本题最重要的一个观察，下图很直观的说明了这一事实。（来自 @2017gdgzoi999）

![](https://cdn.luogu.com.cn/upload/image_hosting/qqz1ve2h.png) 

所以我们实际上只需要维护 $i$ 步之后，哪些区间可能会被取反即可。对 $\oplus_{x=1}^{k} x(b)$ 进行取反后可能的结果就可以覆盖所有的结果。

接下来就到了 dp 的部分，考虑状压 dp。记 $f_{i,j}$ 表示 $j$ 状态能不能**恰好**在第 $i$ 次操作出现。$j$ 的二进制数的第 $x$ 位表示位置 $x$ 有/没有被取反。

感觉我说的不是很清楚。给个例子： $f_{1,(110)_2}=0$ 就表示第一次操作后，不可能让第一位取反，第二位取反，第三位不取反的状态出现。

初始：$f_{0,0}\gets 1$

转移：$f_{i,j}\gets\lor f_{i-1,k}$，其中 $k$ 表示对 $j$ 的第 $[pos,pos+i-1](1\le pos\le n)$ 位取反的结果。

这个转移就是每次都去补第一次操作，相当于第一次选择对 $pos$ 取反。由观察三，这对第 $i$ 次操作的影响相当于在第 $2$ 至第 $i$ 次的结果上（即 $k$），再对 $[pos,pos+i-1]$ 取反（即 $j$ ）。

由于步数的上限为 $O(n)$ 级别的，这样就有了一个 $O(n^2 \times 2^n)$ 的 dp。实际上，这个复杂度仍有优化空间。

> 观察四：若状态 $x$ 是状态 $x'$ 右旋一位的结果，那么 $f_{i,x}=f_{i,x'}$。进一步地，如果 $x$ 能由 $y$ 右旋达到，则 $f_{i,x}=f_{i,y}$。

我们只需要将每一次操作取反的位置全部向右移一位，这样所有对应的区间也都会右移一位。由于初始状态为全 $0$，所以区间右移就等同于将最终结果右移一位。下图直观地说明了这一事实。

![](https://cdn.luogu.com.cn/upload/image_hosting/kdpnub1o.png)

而且可以发现，这一结论是等价关系。即若 $x$ 与 $y$ 能右旋达到，$f_{i,x}=1 \iff f_{i,y}=1,f_{i,x}=0 \iff f_{i,y}=0$。

这样的话，对于 $2^n$ 种总状态，我们可以把每 $n$ 个右旋能互相达到的状态分为一类，这样就会得到 $\frac{2^n}{n}$ 个等价类。对于每个等价类，随意选取其中一个代表状态 $j$ 进行完整转移（代码实现中选取的是最小的一个），等价类中其余的项直接从 $j$ 转移过来即可。形式化地写一下，记对 $x$ 的第 $[s,t]$ 位取反的结果为 $\operatorname{rev}(x,s,t)$。如果将 $j$ 所在等价类选取的代表状态记为 $rep_j$，有：

$$
\begin{cases} f_{i,j} \gets \lor_{k=1}^{k\le n }f_{i-1,\operatorname{rev}(j,k,k+i-1)} & j= rep_j \\ f_{i,j} \gets f_{i,rep_j} & j\ne rep_j \end{cases}
$$

这样我们就得到了一个 $3 \times n \times ({2^n\over n} \times n + {(n-1)2^n\over n})=O(n\times 2^n)$ 复杂度的 dp。

接下来考虑如何查询答案，有了以上的分析，这是很简单的。记步数为 $d$，记 $b$ 右旋 $d$ 次的结果为 $d(b)$。由题目条件 $(\oplus_{x=1}^{k} b^x) \oplus a =0$ 与观察三，实际上有 $\oplus_{x=1}^{d} x(b)\oplus j\oplus a=0$，其中 $j$ 表示对某些位置取反。化简一下，$j=\oplus_{x=1}^{d} x(b) \oplus a$。我们的 dp 就派上用场了。如果说 $f_{d,j}=1$ ，就说明可行。从小到大枚举步数 $d$ ，找到的最小的可行 $d$ 就是答案。由于步数为 $O(n)$ 级别的，则每次询问时间为 $O(n) $。

综合以上，加上 dp 预处理的时间。总时间复杂度 $O(n\times 2^n + n \times T)$ 可以通过本题。

（状压 dp 好题啊，藏得很深，并不套路。）

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;!isdigit(c);c=getchar())if(c=='-')f=1;
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
const int N=25,K=(1<<20);
bool f[N*4][K];
int n,rp[K];
int _rotate(int x){//右旋一位
    return ((x&1)<<(n-1))|(x>>1);
}
vector <int> rps,oth;
void init(){
    int D=(1<<n);//2^n中状态 
    memset(rp,-1,sizeof rp);
    for(int i=0;i<D;++i){//划分等价类
        if(rp[i]!=-1){
            oth.push_back(i);
            continue;
        }
        rp[i]=i;
        rps.push_back(i);
        int x=_rotate(i);
        while(x!=i){
            rp[x]=i,x=_rotate(x);
        }
    }
    f[0][0]=1;
    for(int i=1,x=0;i<=3*n;++i){//dp转移
    	x^=1<<(i-1)%n; 
        for(int j:rps){
            for(int k=0;k<n;++k,x=_rotate(x)){
                f[i][j]|=f[i-1][j^x];
            }
        }
        for(int j:oth){
            f[i][j]=f[i][rp[j]];
        }
    }
}
void rdbit(int &a){
    char c;
    while((c=getchar())<'0' || c>'1');
    a=c-'0';
    while((c=getchar())>='0' && c<='1'){
        a=(a<<1)|(c-'0');
    }
}
int solve(){
    int a,b;
    rdbit(a),rdbit(b);
    if(a==0) return 0;
    int tmp=b;
    for(int i=1;i<=3*n;++i){
        if(f[i][tmp^a])
            return i;
        b=_rotate(b);
        tmp^=b;
    }
    return -1;
}
int main(){
    int T;
    read(T,n);
    init();//dp
    while(T--)
        cout<<solve()<<'\n';
    return 0;
}

```

---

## 作者：迟暮天复明 (赞：2)

假设某一组询问的答案为 $k$，那么我们可以预先把 $b$ 中每个 `1` 可以改变的 $k$ 个位置先全部反转了，然后第 $i$ 次操作就相当于改变了它之后 $k-i+1$ 位的状态。所以问题转化为给一个二进制串，问是否能 $k$ 次操作给他变成全零。这个东西明显可以 $O(n^2\times 2^n) $ 状压 DP 的预处理。完了之后对于每一组询问枚举 $k$ 判断即可。总时间复杂度 $O((T+2^n)n^2) $。

---

## 作者：Creeper_l (赞：2)

一次操作相当于把 $a$ 异或上 $b$，修改开关的一位相当于将这一位异或上 $1$。

会发现一个很神奇的性质：初始开关对灯的影响和改变开关状态对灯的影响是独立的。而前者的影响是固定的，所以我们可以只考虑改变开关状态对灯的影响。假设一共需要 $k$ 次操作能使所有灯关闭，如果我们在第 $i$ 次操作的时候改变了开关 $p$ 的状态，那么第 $i+1$ 次的时候这个开关会影响到 $p+1$（因为要循环右移一位），第 $i+2$ 次操作会影响到 $p+2$。所以如果在第 $i$ 次操作改变一个开关的状态，那么相当于将长度为 $m-i+1$ 的一段区间全部影响了（异或上 $1$）。那么如果我们一共需要 $k$ 次操作，那么我们可以分别修改长度为 $1$ 到 $k$ 的区间各一次。注意这里的区间指的不一定是连续的，也有可能是一段前缀加一段后缀（因为可能循环右移）。并且如果一个点被修改（异或）两次的话相当于不修改。

设 $dp_{i,j}$ 表示 $i$ 次操作（第 $i$ 次操作指的是将一段长度为 $i$ 的区间异或上 $1$）之后能否达到 $j$ 状态。那么转移方程为 $dp_{i,j}=dp_{i,j} \vee  dp_{i-1,j \oplus k}$，其中 $k$ 是长度为 $i$ 的区间。时间复杂度 $O(2^n\times n^2)$，可以通过。

还可以优化。如果一个状态是另一个状态通过循环右移得到的，那么这两个状态的 dp 值一定相同，可以只用记录一次。时间复杂度 $O(2^n \times n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
int f[45][N],t,n,p[N];
char a[N],b[N];
int g(int x){return (x >> 1) + ((x & 1) << n - 1);}
signed main()
{
	cin >> t >> n;
	memset(p,-1,sizeof p);
	for(int i = 0;i < (1 << n);i++)
	{
		int x = i;
		while(p[x] == -1) p[x] = i,x = g(x); 
	}
	f[0][0] = 1;
	for(int i = 1,s = 0;i <= 2 * n;i++)
	{
		s ^= (1 << ((i - 1) % n));
		for(int j = 0;j < (1 << n);j++)
			f[i][p[j]] |= f[i - 1][p[j ^ s]];
	}
	while(t--)
	{
		cin >> a >> b;
		int A = 0,B = 0;
		for(int i = 0;i < n;i++)
			A |= ((a[i] - '0') << (n - i - 1)),
			B |= ((b[i] - '0') << (n - i - 1));
		if(A == 0){puts("0");continue;}
		for(int i = 1;;i++)
		{
			A ^= B,B = g(B);
			if(f[i][p[A]]){cout << i << endl;break;}
		}
	}
	return 0;
}

```


---

## 作者：Rushroom (赞：1)

# 题意

有两个二进制数 $a$，$b$，每次操作，先将 $b$ 的一位取反，然后将 $a$ 异或上 $b$，最后将 $b$ 在二进制下循环右移一位。问至少几次操作让 $a=0$。

多测，数据组数 $\le 2\cdot 10^5$，所有测试点中 $a$，$b$ 在二进制下位数相同且 $\le 20$。

# 题解

考虑将一位反转会对结果造成什么影响，发现一定是异或上连续的一串 $1$，而由于每次操作内只能反转一次，所以每种长度的一串 $1$ 有且仅有一个。于是可以预处理一个背包 $f_{i,j}$ 表示长度为 $1\dots i$ 的串异或起来能否得到 $j$。询问时枚举答案即可。

不太清楚是怎么证明答案 $\le n$ 的。

# Code

```cpp
int T_ = 1, case_;
int n;
bool dp[21][1 << 21];
int shift(int x) {
    int y = x % 2;
    return y * (1 << (n - 1)) + x / 2;
}
string s, t;
int a, b;
void solve() {
    cin >> s >> t;
    a = b = 0;
    rep(i, n)a = a * 2 + s[i] - '0', b = b * 2 + t[i] - '0';
    int now = 0;
    rep(i, n + 1) {
        if (dp[i][(a ^ now)]) {
            cout << i << endl;
            return;
        }
        now = shift(now) ^ b;
    }
}
int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0), cout.tie(0);
    cin >> T_ >> n;
    dp[0][0] = 1;
    int p[21];
    init(p, 0);
    rep(i, n) {
        rep(j, n)p[j] = shift(p[j]) ^ (1 << j);
        rep(msk, (1 << n)) {
            if (!dp[i][msk])continue;
            rep(j, n)dp[i + 1][(msk ^ p[j])] = 1;
        }
    }
    for (case_ = 1; case_ <= T_; case_++)solve();
    return 0;
}
```

---

## 作者：hh__hh (赞：1)

操作 $1$ 相当于第 $x$ 位异或上 $1$，随着操作 $3$ 的循环右移，$x$ 不断 $-1$，当继续经过 $y$ 论操作时，相当于给连续 $y$ 为异或 $1$。

操作 $2$ 等同于异或。已过满足结合律，我们把 $a \oplus b$ 看做 $b$ 异或上所有循环右移，就变成了求最少的操作数是的 $b=a$。

虽然没办法线性 $O\left(n \right)$ 出来，但我们可以用 $dp$ 预处理。

状态：$dp_{i,j}$ 表示分别让长度为 $\left[1,i \right]$ 的循环连续异或上 $1$ 能否让 $0$ 变成 $j$。

状态转移方程：$dp_{i,j}=dp_{i,j} \vee dp_{i-1,j \oplus x}$，$x$ 为所有二进制下连续 $i$ 位为 $1$ 的数。

边界：$dp_{0,0}=1$。

我们暴力枚举操作次数，操作 $m$ 次时，我们把 $b$ 所有循环右移的异或和异或上 $a$ 得到 $c$，直接查询 $dp_{i,c}$ 是否为 $1$。

操作次数拥有一个上界 $3n$，我们可以前 $n$ 次把 $b$ 变成 $0$，然后利用 $1$ 操作，每两次操作把 $a$ 的一位 $1$ 变成 $0$。

---

## 作者：tony0530 (赞：0)

若某一答案为 $k$，我们可以先把 $b$ 中每个 $1$ 可以改变的 $k$ 个位置反转，然后第 $i$ 次操作就只改变了它后的 $k−i+1$ 位的状态。所以问题转化为给一个二进制串，问是否能 $k$ 次操作给他变成全零。用状压 DP $O(n^2 \times 2^n)$ 预处理，之后对于每一组询问枚举判断就好了，总时间复杂度 $O(T \times n^2 \times 2^n)$。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int T, n;
int g[45][22], mask[22];
bool f[45][1 << 21];
string s, t;

int calc(int s, int t)
{
    if(s == 0) return 0;
    for(int i = 1 ; i <= 2 * n ; i ++ )
    {
        int vis = s;
        for(int j = 0 ; j < n ; j ++ )
            if(t & (1 << j))
                vis = vis ^ g[i][j];
        if(f[i][vis]) return i;
    }
}

signed main() 
{
    f[0][0] = 1;
    cin >> T >> n;
    for (int i = 0 ; i <= n ; i ++ ) mask[i] = 1 << i;
    int N = 1 << n;
    for(int k = 0 ; k < n ; k ++ )
        for(int i = 1; i <= 2 * n ; i ++ )
            for(int j = 0; j < i ; j ++ ) 
                g[i][k] ^= mask[(k + j) % n];
    for(int i = 1 ; i <= 2 * n ; i ++ ) 
        for(int j = 0 ; j < N ; j ++ ) 
        {
            if(!f[i - 1][j]) continue;
            for(int k = 0 ; k < n ; k ++ )
            {
                int vis = j;
                vis ^= g[i][k];
                f[i][vis] = 1;
            }
        }
    while (T --)
    {
        cin >> s >> t;
        int S = 0, T = 0;
        for(int i = 0 ; i < n ; i ++ )
        {
            if (s[i] == '1') S ^= (1 << i);
            if (t[i] == '1') T ^= (1 << i);
        }
        cout << calc(S, T) << endl;
    }
    return 0;
}
```

---

## 作者：Egg_laying_master (赞：0)

## Description

给定正整数 $N$，和两个长为 $N$ 的 $01$ 序列 $a$ 和 $b$。定义一次操作为：

1. 将 $b$ 序列中的一个值翻转（即 $0$ 变成 $1$，$1$ 变成 $0$，下同）。
2. 对于 $b$ 序列中每个值为 $1$ 的位置，将 $a$ 序列中对应位置的值翻转。
3. 将 $b$ 序列向右循环移位 $1$ 位。即若当前 $b$ 序列为 $b_1b_2\cdots b_{n}$，则接下来变为 $b_{n}b_1b_2\cdots b_{n-1}$。

有 $T$ 次询问，对每一次询问，你需要回答出至少需要几次操作，才能使 $a$ 序列中每一个位置的值都变为 $0$。

[link](https://www.luogu.com.cn/problem/P9017)

## Solution

显然可以把 $a,b$ 数组看成两个数，操作一就是对 $b$ 的某一位取反，操作二就是让 $a$ 异或 $b$，操作三是让 $b\leftarrow \left\lfloor \frac{b}{2} \right\rfloor$。

容易发现操作数不超过 $3n$，因为可以先用至多 $n$ 次操作把 $b$ 变成 $0$。然后每连续两次操作就让 $b$ 的某一位变成 $1$，把 $a$ 的这一位消掉，然后 $b$ 清空。

然而这样做是 $O(T\cdot n^n)$ 的，过不了且没法优化。

---

观察可知，如果第 $i$ 次操作将第 $j$ 位异或 $1$，总共进行 $s$ 次操作，那么这次操作对最终 $a$ 的贡献就是 $j\sim j+s-i$ 这些位取反（在模 $n$ 意义下）。

这样就可以 dp 了。

设 $f_{i,j}$ 表示进行恰好 $i$ 次操作，能否让 $a$ 变成 $j$，设 $x$ 为任意一个模 $n$ 意义下连续的长度为 $1$ 的数组所对应的状态，那么就让 $f_{i,j}\leftarrow f_{i-1,j\oplus x\oplus b}$。

初始 $f_{0,a}=1$，时间复杂度：$O(T\cdot n\cdot 2^{n})$，过不了。

---

考虑把操作一的贡献和操作二、三的贡献拆开算。操作一所做的贡献就相当于初始 $b=0$ 进行若干次操作对 $a$ 的贡献，显然可以预处理，即设 $f_{i,j}$ 表示 $b$ 初始值为 $0$，对 $a$ 能否做出 $j$ 的贡献。

设 $x$ 为任意一个模 $n$ 意义下连续的长度为 $1$ 的数组所对应的状态，那么就让 $f_{i,j}\leftarrow f_{i-1,j\oplus x}$。

而操作二、三就是对 $b$ 进行这么多操作的异或和，枚举操作次数即可求得。

时间复杂度：$O(n^2\cdot 2^n+Tn)$。

具体实现细节见代码

## Code

```cpp
#include <cstdio>
#include <iostream>
#include <map>

// #define int int64_t

int n, a, b;
int f[100][1 << 20];

int shift(int x) {
  return (x >> 1) + (1 << n - 1) * (x & 1);
}

int tonum(std::string s) {
  int ret = 0;
  for (int i = 0; i < static_cast<int>(s.size()); ++i)
    ret = (ret << 1) + s[i] - '0';
  return ret;
}

int calc(int a, int b) {
  for (int i = 0; i <= 3 * n; ++i, b = shift(b)) {
    if (f[i][a]) return i;
    a ^= b;
  }
  return -1;
}

void prework() {
  f[0][0] = 1;
  for (int i = 1; i <= 3 * n; ++i) {
    int s = (1 << ((i - 1) % n + 1)) - 1;
    for (int j = 0; j < n; ++j, s = shift(s)) {
      for (int k = 0; k < (1 << n); ++k)
        f[i][k] |= f[i - 1][k ^ s];
    }
  }
}

void dickdreamer() {
  int t;
  std::cin >> t >> n;
  prework();
  for (; t; --t) {
    std::string s, t;
    std::cin >> s >> t;
    a = tonum(s), b = tonum(t);
    std::cout << calc(a, b) << '\n';
  }
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
  int T = 1;
  // std::cin >> T;
  while (T--) dickdreamer();
  // std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << "s\n";
  return 0;
}
```

---

