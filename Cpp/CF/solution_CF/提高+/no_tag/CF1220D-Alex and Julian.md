# Alex and Julian

## 题目描述

男孩 Dima 送给 Julian 一份生日礼物——一个由正整数组成的集合 $B$。然而，他并不知道 Julian 讨厌集合，但却非常喜欢二分图！

Julian 差点因此感到不快，但她的朋友 Alex 说，他可以用这个集合构建一个无向图：令所有整数为顶点，如果 $|i-j|$ 属于 $B$，则连接任意两个 $i$ 和 $j$。

不幸的是，Julian 并不喜欢用 $B$ 构建出来的图。Alex 决定补救，所以他想从 $B$ 中删除一些数，使得用新集合构建的图是二分图。难点在于，这个图有无限多个顶点和边！Alex 无法独自完成这个任务，于是请求你的帮助。请编写程序，从 $B$ 中删除最少数量的元素，使得用新集合构建的图是二分图。

回忆一下，若一个图的所有顶点可以分为两个不相交的集合，使得每条边都连接这两个集合中的顶点，则该图为二分图。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
1
2 ```

## 样例 #2

### 输入

```
2
2 6
```

### 输出

```
0
```

# 题解

## 作者：Crossing (赞：6)

## **题意**

给定一个正整数集合$B$。

让所有整数都为一张无向图中的顶点。$i, j$之间有边，当且仅当$\left| i - j\right|  \in B$。

现在要从B中删去最少的元素，使得这张无向图变成二分图。

$\huge\mathcal{Solution}$

首先，根据二分图的性质可知，**判断这张图是不是二分图，只需判断是否存在奇环**

**我们先考虑只有两个数的情况**

则若存在奇环，当且仅当存在正整数$a,b$, 使得 $ax = by$ 且 $(a + b)  \bmod 2 = 1$。即
$$
\frac{\operatorname{lcm}(x, y)}{x} + \frac{\operatorname{lcm}(x, y)}{y} \equiv 1\pmod{2}
$$
于是就可以开始~~快乐地~~分类讨论了。

- $x, y$ 都为奇数。那么 $\operatorname{lcm}(x, y)$ 肯定是奇数，所以不满足。
- $x, y$ 为一奇一偶。那么 $\operatorname{lcm}(x, y)$ 为偶数，所以满足。
- $x, y$ 都为偶数。可以转化为前面两种情况。

然后，归纳一下就可以得到$:$  

​                   **这张图为二分图，即不存在奇环，当且仅当集合B中所有数在二进制下末尾有相同位数的零**

**拓展到多个数**

假设我们现在找含 $i$ 种单位长度的奇环(即用集合B中 $i$ 个数)，且不存在含 $i$ 种以下单位长度的奇环。

即 $a_1x_1 + a_2x_2 + a_3x_3 + ... a_{i-1}x_{i-1} = 0$ 且 $(a_1+a_2+a_3+...a_{i-1}) \bmod 2 = 0$

现在我们在这个式子中加入 $x_i$。

根据假设，我们还可以得到 $A_1x_1 + B_1x_i = 0, A_2x_2 + B_2x_i = 0 ... A_{i - 1}x_{i-1} + B_{i-1}x_i = 0$ 且 $(A_j + B_j) \bmod 2 = 0$

将这些式子中的一些加入到原式中，均可实现在环中加入 $x_i$ 这个长度，但 $a$ 之和始终为偶数。

**因此，我们只需要判断两个数的情况就行了**

$\huge\mathcal{Code}$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

#define int long long

template <typename Tp>
inline void read(Tp &x) {
    x = 0;
    bool f = true; char ch = getchar();
    for ( ; ch < '0' || ch > '9'; ch = getchar()) f ^= ch == '-';
    for ( ; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    x = f ? x : -x;
}

const int M = 105, N = 2e5 + 7;

int tot[N], a[N], c[M];

signed main() {
    int n;
    read(n);
    int maxx = 0, pos = 0;
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        int x = a[i], cnt = 0;
        for ( ; !(x & 1); x >>= 1, ++cnt);
        tot[i] = cnt;
        ++c[cnt];
        if (c[cnt] > maxx) maxx = c[cnt], pos = cnt;
    }
    printf("%lld\n", n - maxx);
    for (int i = 1; i <= n; ++i) if (tot[i] != pos) printf("%lld ", a[i]);
    return 0;
}
```

---

## 作者：DHT666 (赞：2)

似乎和题解区的思路不大一样。

## 题意
定义一个集合是合法的，当且仅当对于集合中的每个数 $x$，把满足 $|i-j|=x$ 的任意整数 $i,j$ 相连，且最终构成的图是二分图。现在给一个大小为 $n$ 的集合 $B$，求删去尽量少的数使集合合法。

## 思路
删去尽量少的数即保留尽可能多的数，那么考虑包括什么样的数的集合合法。

假设集合中存在数 $x$，那么在图中，$0$ 会与 $x$ 相连，$x$ 会与 $2x$ 相连，$2x$ 会与 $3x$ 相连，以此类推（差都是 $x$）。

如果要把这么一条链分成两边（满足二分图），$0$，$2x$，$4x \dots$ 会在一边，$x$，$3x$，$5x \dots$ 会在另一边。

此时如果在集合中加入数 $2x$，那么 $0$ 会和 $2x$ 相连，出现了内部边，则集合不合法，加入数 $4x$，$6x$ 也是同理。

反之，如果加入数 $3x$ 或 $5x$，那么 $0$ 与 $3x$，$5x$ 相连，集合仍合法。

![](https://cdn.luogu.com.cn/upload/image_hosting/dagaruko.png)

如图，边 $(0,2x)$ 是不合法的，而边 $(0,3x)$，$(0,5x)$ 是合法的。

所以说，当集合存在数 $x$ 时，$3x$，$5x$，$7x \dots$ 这些奇数倍的数是可以被加入集合的，而其它数则不行。

那么现在问题转换为：在集合 $B$ 中选出尽量多的数，使这些数可以用一个整数 $x$ 被表示为 $x$，$3x$，$5x\dots$ 的形式。

所以就有了一个暴力的思路：枚举数 $x$，遍历 $B$ 来保留满足条件的数，最多的保留就是答案。

显然过不了，因为 $x$ 的值域达到了 $10^{18}$，考虑减少枚举。

考虑 $x$ 取哪些值是优的：

- $x=1$，则包含了 $3$，$5$，$7 \dots$
- $x=2$，则包含了 $6$，$10$，$14 \dots$
- $x=4$，则包含了 $12$，$20$，$28 \dots$
- $x=8$，$\dots$
- $x=16$，$\dots$

可以发现，当 $x$ 取 $2$ 的幂次时，可以不重不漏的包含每一个正整数，也就是说，$x$ 取 $2$ 的幂次等效替代了 $x$ 取所有数的情况。

那么做法就来了，枚举 $2$ 的幂次作为 $x$，遍历 $B$，取最大的保留作为答案，输出方案的话标记一下就行了。

时间复杂度是 $O(n \log V)$

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const LL N = 2e5 + 10;

LL n;
LL a[N];
bool b[N], p[N];

int main() {
	scanf("%lld", &n);
	for(LL i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	} 
	
	LL res = 0;
	for(LL i = 1; i <= 1e18; i <<= 1) { // 枚举 x 的取值
		LL t = 0;
		for(LL j = 1; j <= n; j++) {	
			b[j] = 0;
			if(a[j] % i == 0 && ((a[j] / i) & 1)) { // 奇数倍
				t++;
				b[j] = 1;
			}
		}
		if(t > res) { // 取最大保留
			res = t;
			for(LL j = 1; j <= n; j++) { // 标记保留的数
				p[j] = b[j];
			}
		}
	}
	
	printf("%lld\n", n - res); // 输出最小删除
	for(LL i = 1; i <= n; i++) {
		if(!p[i]) {
			printf("%lld ", a[i]);
		}
	}
	
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：2)

二分图的充要条件是不存在奇环。由于每多一个数，图中的边只会多不会少，因此奇环出现的概率只会更大，因此我们先考虑集合当中只有两个数 $x,y$。

如果图中存在奇环，那么设 $x$ 跳过了 $a$ 个点，$y$ 跳过了 $b$ 个，那么应该满足：

$$
\begin{cases}
ax=by,\\
a+b \equiv 1 \pmod 2
\end{cases}
$$

最小环所跨过的点的编号应该为 $\operatorname{lcm}(x,y)$，即应满足 $ax=by=\operatorname{lcm}(x,y)$，那么可以表示最小环的长度：

$$
\frac{\operatorname{lcm}(x,y)}{x}+\frac{\operatorname{lcm}(x,y)}{y}\equiv 1 \pmod 2
$$

即 $\dfrac{x+y}{\gcd(x,y)}$ 为奇数。不难看出，若 $x=k_1\times 2^{p_1},y=k_2\times 2^{p_2}$，则当且仅当 $p_1=p_2$ 时，这玩意儿的加法（二进制下）会进位导致除以 $\gcd$ 后是个偶数。

那么扩展到多个数，我们只需要保留 $p$ 相同的最多的那个，删掉剩下的即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64; 

int n, b[200005], res[100]; 
i64 a[200005]; 

int main(void) {
    scanf("%d", &n); 
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i); 
        i64 x = a[i]; int cnt = 0; 
        while (x % 2 == 0) x >>= 1, ++cnt; 
        b[i] = cnt; ++res[cnt]; 
    }
    int mx = 0, p = 0;
    for (int i = 0; i < 64; ++i) if (res[i] > mx) mx = res[i], p = i;  
    printf("%d\n", n - mx); 
    for (int i = 1; i <= n; ++i) if (b[i] != p) printf("%lld ", a[i]); 
    return putchar('\n'), 0;
}
```

---

## 作者：GreenDay (赞：2)

说句闲话 : 因为蒟蒻题意理解错误，卡了一节自习课（逃

## 题目大意：

现有一个大小为n $(1 \le n \le 2 * 10^5 )$集合B , B里的元素$ 1 \le b_i \le 10^{18} $ 。对于任意$ i , j \in Z $**（这两个数不一定在集合B里）** ， 若$ abs(i - j) \in B $ , 则整数i， j之间连一条无向边。

问：至少在B中删掉多少个元素 ， 才能使得连出的边构成一个**二分图**？输出最小值并构造一种方案

## 前置知识：二分图的判定
没奇环。。。。。

## 做法

考虑从0开始 ，$lcm(a , b) (a , b \in B $)$ 构成的环： 因为集合B中的两个点构成了奇数大小的环 ， 则有

$ \frac{lcm(a , b)}{a} + \frac{lcm(a , b)}{b} \equiv 1  (\mod 2) $

即为

$ {\frac {a + b}{gcd(a , b) } \equiv 1 (\mod 2)} $

显然 ， 当且仅当a ， b中2的质因子数相等时 ， a ， b无法构成奇数环（这种情况下$ \frac {a}{gcd(a , b) } $ 和 $ \frac {b}{gcd(a , b) } $都是奇数 ，否则二者必然一奇一偶 , 构成奇环)。

换句话说：保留的数，必然含有相同个数的2的质因子。

所以我们只需要把B集合元素按2进制下末尾0的个数分组，最后只保留某一个大小最大的组，其他的都删掉，就是最优化的。

code:

```cpp
//没有头文件，防抄袭
int n;
vector<long long> group[60]; 

inline int calc(long long x)
{
	int res = 0;
	while(!(x & 1)) x >>= 1 , res ++;
	return res;
}

int main()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
	{
		long long num ;
		cin >> num;
		group[calc(num)].push_back(num);
	}
	int save = 0;
	for(int i = 0 ; i < 60 ; i ++)
		if(group[i].size() > group[save].size())
			save = i;
	
	cout << n - group[save].size() << endl;
	for(int i = 0 ; i < 60 ; i ++)
	{
		if(i == save) continue;
		for(int j = 0 ; j < (int)group[i].size() ; j ++)
			cout << group[i][j] << ' ';
	}
}
```


---

## 作者：sgl654321 (赞：0)

## 题目大意
给定一个长度为 $n$ 的序列 $B$，并以此来构造一张点集为正整数集的图。两个点 $x, y$ 之间有连边当且仅当 $|x-y|\in B$。

问至少删除多少个 $B_i$ 之后，构造出来的图是一张二分图。并给出删除方案。

## 解题思路
### 转化二分图判定
我们知道，一张图是二分图，等价于这张图没有长度为奇数的环。如果 $B$ 中只有一个元素，那么这张图绝对不可能形成环。

$B$ 中如果有两个元素 $x,y$ 那么就肯定会形成环。具体的，$1,1+x,1+2x,1+3x,\cdots$ 形成了一条链，$1,1+y,1+2y,1+3y,\cdots$ 也会形成一条链。

$1+k\text{lcm}(x,y),k\in Z$  肯定同时出现在两条链中，这就形成了一个环。该环的长度为 $\dfrac{\text{lcm}(x,y)}{x}+\dfrac{\text{lcm}(x,y)}{y}$。我们应当保证这个长度不能是奇数。



根据小学数学知识 $\text{lcm}(x,y)\times \gcd(x,y) =xy$，我们可以化简式子为：$\dfrac{x+y}{\gcd(x,y)}$，这个分式不能是奇数。

### 转化该分式不是奇数的判定

这个分式中，$x,y$ 满足什么关系，才能是偶数呢？

奇偶性质只与 $2$ 这个因子有关，因此我们可以提取出 $x,y$ 中 $2$ 这个因子的幂次。具体的，设 $x=2^{q_1}k_1,y=2^{q_2}k_2$，其中 $k_1,k_2$ 都是奇数，$q_1,q_2$ 为整数。

那么 $\gcd(x,y) = \gcd(2^{q_1}k_1,2^{q_2}k_2)=2^{\min(q_1,q_2)}\times \gcd(k_1,k_2)$。

这个分式就变成了：

$\dfrac{2^{q_1}k_1}{2^{\min(q_1,q_2)}\times \gcd(k_1,k_2)}+\dfrac{2^{q_2}k_2}{2^{\min(q_1,q_2)}\times \gcd(k_1,k_2)}$。

如果 $q_1\not=q_2$，那么这两项一定一个是奇数，一个是偶数，因为有一项 $2$ 除不尽。两者相加就变成奇数了，就形成了长度为奇数的环。

因此我们分析出，只有 $q_1=q_2$ 才能使该分式是一个奇数。

### 提取 $2$ 的幂次统计答案
所以，我们就要在 $B$ 中删除一些元素，使得剩下的元素，含有 $2$ 的幂次都相同。我们计算出 $B$ 中每一个元素含有 $2$ 质因子的个数，其中出现次数最多的那个个数就是我们要保留的。通过枚举，可以轻松求出答案。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 200100
using namespace std;
typedef long long ll;


ll n, a[maxn], cnt, b[maxn], now;
ll d[maxn], ma;

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	for(int i = 1; i <= n; i ++){
		cnt = 0; now = a[i];
		while(now % 2 == 0)
			cnt ++, now /= 2;
		b[i] = cnt;
		d[cnt]++;
	}
	ma = 0;
	for(int i = 0; i <= 100; i++)
		if(d[i] > d[ma]) ma = i;
	cout << n - d[ma] << endl;
	for(int i = 1; i <= n; i++)
		if(b[i] != ma) cout << a[i] << ' ';
	cout << endl;	
	return 0; 
}
```

虽然本题代码不长，但是思维量也并不大。中规中矩的一道 CF *1900。

---

## 作者：Pelom (赞：0)

[更好的阅读体验](https://pelom.top/archives/16/)

### 题意

给出一个$n$个元素的集合$B$，以及节点为所有整数组成的图，对于两个整数$i,j$如果满足$|i-j| \in B$，那么$i,j$之间有一条无向边。

问至少删去$B$中多少个数，使得该图是一个二分图

**数据范围：**$1 \le n \le 200000,1 \le b_i \le 10^8$

### 题解

对于任意一个节点$u$，及$B$中的任意两个元素$x,y$，向后连边，会在节点$u+lcm(x,y)$处形成一个环，环的边数为
$$\frac{lcm(x,y)}{x}+\frac{lcm(x,y)}{y}=\frac{x}{gcd(x,y)}+\frac{y}{gcd(x,y)}$$

而我们知道，判定二分图的条件为图中不存在奇环

若上式为奇数，则$x,y$不能同时存在；反之，若上式为偶数，则$x,y$能同时存在

我们将$x,y$的公约数中的$2$全部提出来，这时$gcd(x,y)$中没有约数$2$，$x'+y'$与原式奇偶性相同

这时$x'$与$y'$中至少有一个为奇数，若另一个也为奇数，则其和为偶数；否则其和为奇数，不能同时存在；而这在二进制上表示为$x,y$最低非零位相同

确定算法为在$B$中统计最低非零位相同的数的个数，取最大值，其余的需全部删去

**代码：**

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
typedef vector<LL>::iterator it;
const int N=200000+10;
int n;
LL b[N];
vector<LL> s[64];
int t;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&b[i]);
        int j=0;
        for(;!(b[i]>>j&1);j++);
        s[j].push_back(b[i]);
    }
    for(int i=1;i<64;i++)
        if(s[i].size()>s[t].size())
            t=i;
    printf("%d\n",n-s[t].size());
    s[t].clear();
    for(int i=0;i<64;i++)
        for(it j=s[i].begin();j!=s[i].end();j++)
            printf("%lld ",*j);
    return 0;
}
```

---

