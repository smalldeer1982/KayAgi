# [CCO 2022] Rainy Markets

## 题目背景

## 由于数据包过大，本题无法上传全部数据。

## 题目描述

有 $N$ 个公交车站，标号为 $1, \ldots, N$。第 $i$ 个公交车站可以容纳 $B_{i}$ 个人。

对于每个 $i \in\{1, \ldots, N-1\}$，有一条人行道连接公交车站 $i$ 和公交车站 $i+1$，中间有一个露天市场。第 $i$ 个市场有 $U_{i}$ 把雨伞出售，每把雨伞的价格为 $1$。

现在，有 $P_{i}$ 个人在第 $i$ 个市场里面，所有的公交车站都是空的。

突然，天开始下雨，市场 $i$ 的每个人都必须在三种方案中选择一种：

- 去公交车站 $i$；
- 去公交车站 $i+1$；
- 留下来买一把雨伞。

如果一个人无法在某个公交车站下或者买一把雨伞，他们就会淋湿。

你需要回答如果在最优的安排方案下，能否确保每个人都能不被雨淋湿。如果是的话，你需要给出他们需要花费的最少的钱，以及每个人应该移动到哪个公交车站。

## 说明/提示

## 样例 1 解释

公交车站有 $35$ 个空位，没有雨伞出售，但市场有 $40$ 个人，所以答案是 `NO`。

## 样例 2 解释

市场 $1$ 中的 $10$ 个人会去公交车站 $1$，没有人会买雨伞，$10$ 个人会去公交车站 $2$。

市场 $2$ 中的 $5$ 个人会去公交车站 $2$，$5$ 个人会留下来买雨伞，$10$ 个人会移动到公交车站 $3$。

总共购买了 $5$ 把雨伞，花费了 $5$。

## 数据范围

对于所有的数据，有 $2 \leq N \leq 10^{6}$，$0 \leq B_{i} \leq 2 \cdot 10^{9}$，$0 \leq P_{i},U_{i} \leq 10^{9}$。

子任务编号|分值|	$N$|	$B$|	$P$|	$U$
:-:|:-:|:-:|:-:|:-:|:-:
|$1$|	$20$|	$2 \leq N \leq 10^{6}$|	$0 \leq B_{i} \leq 2 \cdot 10^{9}	$|$0 \leq P_{i} \leq 10^{9}$	|$U_{i}=0$
$2$|$20$|$2 \leq N \leq 2000$|	$0 \leq B_{i} \leq 400$|$	0 \leq P_{i} \leq 200$|	$0 \leq U_{i} \leq 200$
$3$|	$24$|	$2 \leq N \leq 4000$	|$0 \leq B_{i} \leq 4000$|	$0 \leq P_{i} \leq 2000$|	$0 \leq U_{i} \leq 2000$
$4$|	$36$|	$2 \leq N \leq 10^{6}$	|$0 \leq B_{i} \leq 2 \cdot 10^{9}$|	$0 \leq P_{i} \leq 10^{9}$|	$0 \leq U_{i} \leq 10^{9}$

## 样例 #1

### 输入

```
3
10 15 10
20 20
0 0```

### 输出

```
NO```

## 样例 #2

### 输入

```
3
10 15 10
20 20
0 11```

### 输出

```
YES
5
10 0 10
5 5 10```

# 题解

## 作者：ny_jerry2 (赞：6)

思维难度较大，感觉有个蓝题？  
首先判断一个无解情况：$u_i+b_i+b_{i+1}<p_i$。很好理解，最优情况都无法满足，那就一定无法满足了。

鉴于要输出方案，我们最好开数组来记录。

先设 $f_i$ 表示在第 $i$ 个车站至多留下多少个人，显然可以推出递推式：

$$
f_i = \max(0,b_i - \max(p_{i-1}-f_{i-1},0))
$$

大概就是要除去在第 $i-1$ 个车站实在没法挤的人数，并于 $0$ 取最大值，即最坏也是不容纳人。

设 $l_i,buy_i,r_i$ 分别为在第 $i$ 个市场中呆着不懂，去买伞与到 $i+1$ 车站的人数。

我们可以**从右向左**贪心（具体待会简单解释以下）。

显然，**向右侧多分配人**是更优的（毕竟右边已经尽量优的处理过了）。

分配完之后，因为要使得买伞的人的数量少，就尽量多的原地不动，这样就用上了 $f_i$，也说明了为什么要从右向左贪心。

实在不行的话，只能让剩余的人买伞了。

还是不行的话，就要让剩下的原地不动了（因为没法再分配了）。若剩下的人数大于了容量，便无解。

### 代码
```cpp
#include<iostream>
using namespace std;
#define int long long 
const int N=1e6+10;
int n;
int b[N],p[N],u[N];
int f[N];
int l[N],r[N],buy[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	for(int i=1;i<n;i++){
		scanf("%lld",&p[i]);
	}
	for(int i=1;i<n;i++){
		scanf("%lld",&u[i]);
		if(u[i]+b[i]+b[i+1]<p[i]){
			cout<<"NO";
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		f[i]=max(0ll,b[i]-max(p[i-1]-f[i-1],0ll));
	}
	long long res=0;
	for(int i=n-1;i;i--){
		r[i]=min(p[i],b[i+1]-l[i+1]);
		p[i]-=r[i];
		l[i]=min(p[i],f[i]);
		p[i]-=l[i];
		buy[i]=min(p[i],u[i]);
		p[i]-=buy[i];
		l[i]+=p[i];
		res+=buy[i];
		if(l[i]>b[i]){
			cout<<"NO";
			return 0;
		}
	}
	printf("YES\n%lld\n",res);
	for(int i=1;i<n;i++){
		printf("%lld %lld %lld\n",l[i],buy[i],r[i]);
	}
}
```

---

## 作者：Arson1st (赞：5)

## [[CCO2022] Rainy Markets](https://www.luogu.com.cn/problem/P10055) 题解

## 模拟+反悔贪心

本人太蒻了，拿着数据调了两三遍才过T_T。稍显啰嗦，大佬可以直接参照代码实现。

既然要给出方案，我们可以用 $L_i,M_i,R_i$ 分别表示市场 $i$ 的人去车站 $i$、留下买伞、去车站 $i+1$ 的人数。显然，如果存在 $U_i+B_i+B_{i+1}<P_i$，那无论如何安排都会有人淋湿，先在读入时判掉这种非法情况。

首先有个基本的贪心思路：从左到右依次考虑每个市场，市场 $i$ 的人尽量先把车站 $i$ 的空余填满，然后再去填车站 $i+1$。还有多的人才留下买伞。模拟到左右车站空余容量加上伞的数量仍小于人数时便返回非法。

直接这么做当然是错误的。考虑按这种方式模拟贪心会遇到的问题：

```cpp
4
8 8 8 8
16 9 9
8 0 0
```

对于上组数据，如果我们一开始将市场 $1$ 的人分散到车站 $1$ 和 $2$，那么会发现到市场 $2$ 时报告非法。但我们可以让市场 $1$ 的部分人去买伞，模拟到市场 $3$ 时同理。事实上，这组数据可以用 $2$ 元钱的代价保证方案合法。

观察后性质后不难发现，在一些 $U_i\not=0$ 的市场，我们可以通过增加该市场买伞的人数，使得去车站 $i+1$ 的人数减少，从而产生连锁反应，为后面腾出空间。于是可以到每个市场时考虑维护这个最大左移量 $mn$ 进行以便反悔贪心，这将成为今后模拟时的关键。

先另存 $B$ 数组为 $D$ 数组，下文所称的 $B$ 数组表示每个车站 **剩余** 的空位，而非总容量，注意区分。现在对于模拟简单分讨一下：

1. $B_i\ge P_i$：此时市场 $i$ 的人会全部去到车站 $i$，对后面不再产生影响，记录 $L_i=P_i$ 并清零 $mn$。

2. 1. $B_{i+1}\ge P_i-B_i$：此时 $L_i=B_i,R_i=P_i-B_i,B_{i+1}=B_{i+1}-R_i$。

		因为伞太多没有用，所以我们最多为去下一车站的人保留 $R_i$ 把伞——$U_i=\min(U_i,R_i)$。

		因为只有车站 $i+1$ 被市场 $i,i+1$ 共享，所以加上这一市场“可回收”的人数后，对于下一市场而言，可偏移量也最多能用 $R_i$——$mn=\min(mn+U_i,R_i)$。

	2. 显然 $L_i=B_i,R_i=B_{i+1}$。求出此时必须要买伞的人数 $P_i:=P_i-L_i-R_i$。自然，既然都是买，肯定先尽量就地买伞。

		- $U_i\ge P_i$：参照上面进行更新，并有 $M_i=P_i$。

		- $U_i<P_i$：现在不得不使用偏移量了。先判掉非法情况 $P_i>mn$。

			自然，合法时我们会让人填到左移出的空位里——$L_i:=L_i+P_i-U_i$。

			$mn$ 对下一市场的贡献依然不会超过 $B_{i+1}$，并要减去现在使用掉的部分——$mn=\min\{mn-(P_i-U_i),B_{i+1}\}$。

**tips**：使用偏移量时会导致人顺位左移到前一个坑位并填满它，我们自然不能每次更新时都暴力更新一遍（参照之前的那种例子，暴力更新会被卡成 $O(n^2)$，喜提 $64pts$），考虑这样一个性质：如果每次都不更新，那么最后存在 $R_{i-1}+L_i>D_i$ 就说明两者之间存在偏移量未更新。对于一个偏移操作连通块的右端起点，其 $L_i,M_i,R_i$ 是确定的。根据贪心，$R_{i-1}$ 一定是 $D_i-L_i$，然后偏移量会填入 $U_{i-1}$，使 $M_{i-1}$ 加上 $\min(U_{i-1},D_i-L_i)$。剩余的偏移量会继续使 $L_{i-1}$ 更新，以此类推直至影响结束。这可以在最后倒序遍历一遍 $O(n)$ 实现。

于是总复杂度是 $O(n)$ 的模拟，带有小常数，加了快读快写，发题解时是最优解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;

int n, b[N], d[N], p[N], q[N], u[N];
int l[N], r[N], m[N], mn;
long long sum;

signed main() {
	n = read();
	for (int i = 1; i <= n; i ++) d[i] = b[i] = read();
	for (int i = 1; i < n; i ++) q[i] = p[i] = read();
	for (int i = 1; i < n; i ++) {u[i] = read();
		if ((long long) u[i] + b[i] + b[i+1] < p[i])
			{printf("NO"); return 0;}
	}
	for (int i = 1; i <= n; i ++) {
		l[i] = min(b[i], p[i]);
		if (b[i] >= p[i]) {mn = 0; continue;}
		else {
			p[i] -= b[i]; r[i] = min(p[i], b[i+1]);
			if (b[i+1] >= p[i]) {
				u[i] = min(u[i], p[i]);
				mn = min(mn+u[i], p[i]); b[i+1] -= p[i];
			}
			else {
				p[i] -= b[i+1]; m[i] += min(u[i], p[i]);
				if (u[i] < p[i]) {
					p[i] -= u[i]; u[i] = 0;
					if (p[i] > mn) {puts("NO"); return 0;}
					l[i] += p[i]; mn = min(mn - p[i], b[i+1]);
				}
				else {
					u[i] -= p[i]; u[i] = min(u[i], b[i+1]);
					mn = min(mn + u[i], b[i+1]);
				}
				b[i+1] = 0;
			}
		}
	}
	puts("YES");
	for (int j = n-1; j >= 1; j --) {
		sum += m[j];
		if (r[j-1] + l[j] > d[j]) {
			int der = r[j-1] + l[j] - d[j]; m[j-1] += min(der, u[j-1]);
			r[j-1] -= der; der = max(0, der - u[j-1]); l[j-1] += der;
		}
	}
	r[1] = q[1] - m[1] - l[1];
	write(sum, '\n');
	for (int i = 1; i < n; i ++)
		write(l[i], ' '), write(m[i], ' '), write(r[i], '\n');
}
```





---

## 作者：rui_er (赞：5)

首先尽量把所有人放在左边的车站，然后再尽量放在右边的车站，求出此时 $i$ 位置车站有多少空位留给 $i+0.5$ 位置的人，记为 $f_i$。也就是：

$$
f_i\gets\max\{b_i-\max\{p_{i-1}-f_{i-1},0\},0\}
$$

然后从右向左贪心。对于第 $i+0.5$ 位置的人，设去左边、不动买伞、去右边的人数分别为 $l_i,m_i,r_i$。由于右侧都已经尽量优地分配过，令这个位置的人优先去右边不会使得情况变得更劣，因此先贪心把右边填满，也就是：

$$
\begin{aligned}
r_i&\gets\min\{b_{i+1}-l_{i+1},p_i\}\\
p_i&\stackrel{-}{\gets}r_i
\end{aligned}
$$

之后为了使总花费尽量小，肯定是在不影响左侧的情况下尽量都去左边，这时候计算过的 $f_i$ 就派上了用场，$f_i$ 就代表着左边有多少地方一定可以给 $i+0.5$ 位置的人，且不会影响左侧的决策，也就是：

$$
\begin{aligned}
l_i&\gets\min\{f_i,p_i\}\\
p_i&\stackrel{-}{\gets}l_i
\end{aligned}
$$

剩下的人一定需要买伞，因为即使在这里不买伞，去到左边也会使得左边的一些人需要买伞。我们让他们直接就地买伞：

$$
\begin{aligned}
m_i&\gets\min\{u_i,p_i\}\\
p_i&\stackrel{-}{\gets}m_i\\
ans&\stackrel{+}{\gets}m_i
\end{aligned}
$$

如果还有剩下的人，就不得不让他们去左边挤一挤了：

$$
l_i\stackrel{+}{\gets}p_i
$$

如果 $l_i > b_i$ 即为无解，所有 $l_i\le b_i$ 即求得了最优解及其构造。

时间复杂度 $O(n)$。

所有关键都在上文给出了，代码就不放了。

---

## 作者：船酱魔王 (赞：2)

## 题意回顾

$ n $ 个站点，每个站点有容量，两个站点间亦有容量，两个站点间有人员，要把所有人员迁移到相邻的两个站点之一或放在中间，代价为放在站点中间的人数，判断是否有解，若有解，最小化代价并输出每个站点的人员迁移方案。

$ 2 \le n \le 10^6 $。

## 分析

考虑站点间无容量的简单情况，显然贪心地从左往右考虑，人尽量靠左更优，因为左面的站点对以后的处理毫无影响，在模拟过程中需要记录 $ lst $ 表示上一个站点的空位。

站点间有容量时依然沿用以上的贪心方案，发现可能会出现如果上一个站点一些人进入上一个站点与上两个站点之间的容量的话这个站点和上一个站点之间的人就有地方安放了，我们记录 $ rem $ 表示如果让一些人进入站点之间可以为后面的站点节约出来的席位数，转移过程中要注意和当前站点的容量取最小值。相当于在上 $ i $ 个站点前一些人选择进入与上 $ i+1 $ 个站点之间的容量，上 $ i-1 $ 个站点同样的人数进入上 $ i $ 个站点......直到这么多席位被空出来在上一个站点使得这些人可以进入上一个站点。每次要注意更新 $ rem,lst $，且 $ rem+lst $ 的值不超过当前站点的容量。为了输出方案要记录这个站点上有多少个人（含这个站点与上一个站点的间隔及若干个站点前进入间隔留出席位的人）需要进入间隔。

我们发现，从右往左处理进入间隔的人然后能在这个位置处理进入间隔的人就处理是可行的，因为一个人在更靠右的位置进入间隔更有可能为右面的位置留出席位，而不是被两者中间的存在站点容量的瓶颈区域卡住。

转移细节见代码，时间复杂度为 $ O(n) $，建议进行快速读入以提升代码运行效率。

## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1e6 + 5;
ll n;
ll b[N], p[N], u[N];
ll wzj[N];
inline void read(ll &x) {
    x = 0;
    char ch = '#';
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
}
int main() {
    read(n);
    for(int i = 1; i <= n; i++) read(b[i]);
    for(int i = 1; i < n; i++) read(p[i]);
    for(int i = 1; i < n; i++) read(u[i]);
    ll rem = 0;
    ll lst = b[1];
    ll lwhzkj = 0;
    for(int i = 1; i < n; i++) {
        if(lst + b[i + 1] >= p[i]) lst = min(b[i + 1], lst + b[i + 1] - p[i]), rem = min((long long)b[i + 1] - lst, rem + u[i]);
        else if(lst + b[i + 1] + u[i] >= p[i]) wzj[i] = p[i] - lst - b[i + 1], rem = min(b[i + 1], rem + u[i] - wzj[i]), lst = 0;
        else {
            if(lst + b[i + 1] + u[i] + rem < p[i]) {
                lwhzkj = (ll)1e18 + 5;
                break;
            }
            wzj[i] = p[i] - (lst + b[i + 1]);
            rem = min(rem - wzj[i] + u[i], b[i + 1]);
            lst = 0;
        }
        lwhzkj += wzj[i];
    }
    if(lwhzkj == (ll)1e18 + 5) {
        puts("NO");
        return 0;
    }
    puts("YES");
    printf("%lld\n", lwhzkj);
    lst = 0;
    for(int i = n - 1; i >= 1; i--) {
        lst += wzj[i];
        wzj[i] = min(u[i], lst);
        lst -= min(u[i], lst);
    }
    lst = b[1];
    for(int i = 1; i < n; i++) {
        ll tl, tr;
        ll pi = p[i] - wzj[i];
        if(lst >= pi) tl = pi, tr = 0;
        else tl = lst, tr = pi - lst;
        lst = b[i + 1] - tr;
        printf("%lld %lld %lld\n", tl, wzj[i], tr);
    }
    return 0;
}
```

---

## 作者：DAMDAM (赞：2)

> 这篇题解仅供参考，不保证给出代码能通过该题目。

考虑网络流。感觉像一个二分图匹配似的。

记源点 $s$ 与汇点 $t$。用一些结点代表原来的市场，用另外一些结点代表公交车站。

从 $s$ 向每个代表市场的结点 $i$ 连接容量为 $P_i$ 的边表示市场原有的人，每一个代表公交车站的结点 $i'$ 向汇点连接容量为 $B_i$ 的边表示该公交车站能容纳人数。从 $i$ 向 $i'$ 与 $(i+1)'$ 连容量为 $\infty$ 的边表示转移的人数可能有无限的人转移。那么这形成了一个类似于二分图匹配的结构。

那如何表示买伞的人呢？我们从每个代表市场的结点 $i$ 直接向汇点连接容量为 $U_i$，费用为 $1$ 的边。之前的边费用都记为 $0$。

构造的正确性感觉挺显然的说。那么这就被转化为了一个最小费用最大流的问题。先判断最大流是否等于市场人数，再输出最小费用即可。方案输出？只需要按市场结点每条出边对应的流量多少输出就可以了。

不过卡不过，总是 T 两个点。服了。有人用费用流过了记得告诉我。下面代码已经是极限了。仅供参考，毕竟似乎数据范围就是卡网络流的？

```cpp
#include <bitset>
#include <cstdio>
#include <cstring>
#include <queue>
#include <ext/pb_ds/priority_queue.hpp>
namespace Use {
using std::deque;
using std::bitset;
using std::min;
using __gnu_pbds ::priority_queue;
}
using namespace Use;
typedef long long ll;
const int maxn = 2e6 + 5, maxm = 5e6 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE + 2], *p1 = buf, *p2 = buf;
char get_char() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? EOF : *p1++;
}
char out[MAXSIZE + 2], *p = out;
void put_char(const char &c) {
    if (p - out == MAXSIZE) fwrite(out + 1, 1, MAXSIZE, stdout), p = out;
    *++p = c;
}
void __PRINTF_NOW() {
    fwrite(out + 1, 1, p - out, stdout), p = out;
}
template <typename T>
T read() {
    T x = 0;
    char c = get_char();
    bool t = 0;
    for (; c < '0' || c > '9'; c = get_char()) ;
    for (; c >= '0' && c <= '9'; c = get_char())
        x = (x << 1) + (x << 3) + c - '0';
    return t ? -x : x;
}
void write(ll x) {
    static int s[25], *t = s;
    do *t++ = x % 10, x /= 10;
    while (x);
    while (s != t) put_char(*(--t) + '0');
}

struct Vertex {
	int num;
	ll dis;
	bool operator <(const Vertex &b) const & {
		return dis > b.dis;
	}
};

int to[maxm << 1], next[maxm << 1], head[maxn], len = 1;
ll dis[maxm << 1], flow[maxm << 1];
inline void insert(const int &u, const int &v, const ll &w, const ll &f) {
    to[++len] = v, dis[len] = w, flow[len] = f, next[len] = head[u], head[u] = len;
}

inline void emplace(const int &u, const int &v, const ll &w, const ll &c) {
    insert(u, v, w, c), insert(v, u, -w, 0);
}

deque<int> d;
int cur[maxn], s, t;
ll w[maxn], reply;
bitset<maxn> vis;
void Bfs() {
    memset(w, 63, sizeof w), w[s] = 0, vis[s] = 1, d.push_front(s);
    for (int u, v; !d.empty(); ) {
        u = d.front(), d.pop_front();
        for (int i = head[u]; i; i = next[i]) 
            if (flow[i] && !vis[v]) 
                w[v] = w[u] + dis[i], dis[i] ? d.push_back(v) : d.push_front(v), vis[v] = 1;        
    }
}

priority_queue<Vertex> h;
ll dist[maxn];
bool Dijkstra() {
	memset(dist, 63, sizeof dist), vis.reset(), h.clear(), h.push({s, dist[s] = 0});
	ll d;
	for (int u, v; !h.empty(); ) {
		u = h.top().num, h.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = next[i]) {
            v = to[i];
			if (flow[i] && dist[v] > (d = dist[u] + dis[i] + w[u] - w[v])) 
				dist[v] = d, h.push({v, d});
		}
	}
    return dist[t] != inf;
}

ll Dfs(const int &u, const ll &f) {
    if (u == t || !f) return f;
    ll ans = 0, d;
    vis[u] = 1;
    for (int &i = cur[u], v; i; i = next[i]) {
        v = to[i];
        if (!vis[v] && dist[v] == dist[u] + dis[i] + w[u] - w[v] && (d = Dfs(v, min(f - ans, flow[i])))) {
            ans += d, flow[i] -= d, flow[i ^ 1] += d, reply += d * dis[i];
            if (ans == f) return vis[u] = 0, ans;
        }
    }
    vis[u] = 0;
    return ans;
}

inline void init() {
    for (int i = 0; i < maxn; ++i) w[i] += dist[i];
}

ll Dinic() {
    ll flow = reply = 0;
    for (Bfs(); Dijkstra(); memcpy(cur, head, sizeof head), vis.reset(), flow += Dfs(s, inf), init()) ;
    return flow;
}

ll B[maxn], sum, a, b, c;
int main() {
    int n = read<int>();
    t = n << 1;
    for (int i = n; i < t; ++i) B[i] = read<ll>(), emplace(i, t, 0, B[i]);
    for (int i = 1; i < n; ++i) sum += (B[i] = read<ll>()), emplace(s, i, 0, B[i]);
    for (int i = 1; i < n; ++i) a = read<ll>(), emplace(i, t, 1, a), emplace(i, i + n - 1, 0, B[i + n - 1]), emplace(i, i + n, 0, B[i + n]);
    if (Dinic() == sum) {
        put_char('Y'), put_char('E'), put_char('S'), put_char(10), write(reply), put_char(10);
        for (int u = 1; u < n; ++u) {
            a = b = c = 0;
            for (int i = head[u], v; i; i = next[i]) 
                if (!(i & 1) && flow[i ^ 1]) {
                    if ((v = to[i]) == u + n - 1) a = flow[i ^ 1];
                    else if (v == t) b = flow[i ^ 1];
                    else if (v == u + n) c = flow[i ^ 1];
                }
            write(a), put_char(32), write(b), put_char(32), write(c), put_char(10);
        }
    } else put_char('N'), put_char('O');
    return __PRINTF_NOW(), 0;
}
```

---

## 作者：Loser_Syx (赞：2)

将一排公交车站看成一个数轴，$p_i$ 和 $u_i$ 的 $i$ 看作 $b_i$ 的 $i+0.5$。

首先判断无解你肯定得会吧，贪心选择，因为我只要知道是否合法，所以我为了不影响后面的答案肯定是能去买雨伞就去买雨伞，剩下的人再优先去左边的站台，再有剩下就去右边的站台，如果还有剩下就是无解了。

然后你发现剩下情况一定都是有解的，考虑其中 $u_i=0$ 的情况。  
还是贪心考虑，还是能往左边去就往左边去，因为对于当前的 $p_i$，左边已经不会产生影响，而右边还会对 $p_{i+1}$ 影响，剩下的放右边。

再来看看剩下的情况，还是贪心放，因为有了 $u_i$，所以尽管按照 $u_i=0$ 的方式放了 $i$，还会有一些 $p_i$ 剩余，那么就让这些人去买 $u_i$ 把伞。  
发现还会有多的，原因是前面的 $i$ 决策的时候把现在的 $i$ 左边的位置给抢了，应该让他们去买伞把位置留给 $i$ 的。为了避免重复找到某个已经为 $u_j=0$ 的 $j$，我们需要一种数据结构维护序列连通性，容易想到「白雪皑皑」的方式维护并查集维护 $u_j \neq 0$ 的 $j$。  
维护完并查集之后，你可以每下都在 $\log n$ 次内找到一个 $u_j \neq 0$ 的 $j$ 进行更改 $j$ 的状态即可，如果还有多的再找一个 $j$ 即可，因为肯定合法所以不用管其他的。

如此一来可以得到每个 $i$ 让多少个人去买伞了，剩下的除那些买伞的人外的人可以看成一个 $u_i=0$ 的数据直接计算。

复杂度 $O(n \log n)$，瓶颈在小常数并查集。

```cpp
const int N = 1e6+19;
int b[N], p[N], u[N], ans[N][3];
struct DSU {
	int f[N];
	void init(int n) {
		for (int i=0;i<=n;++i) f[i]=i;
	}
	int find(int x) {
		if (x == f[x]) return x;
		return f[x]=find(f[x]);
	}
	void merge(int x) {
		f[x] = find(x-1);
	}
} dsu;
signed main() {
	int n = read();
	dsu.init(n);
	for (int i=1;i<=n;++i) read(b[i]);
	for (int i=1;i<n;++i) read(p[i]);
	for (int i=1;i<n;++i) read(u[i]);
	int more=b[1];
	for (int i=1;i<n;++i) {
		more=b[i+1]+more+u[i]-p[i]>b[i+1]?b[i+1]:b[i+1]+more+u[i]-p[i];
		if (more<0) return puts("NO"),0;
	}
	puts("YES");
	int cnt=0;
	more=b[1];
	for (int i=1;i<=n;++i) {
		more=p[i]<=more?b[i+1]:more-p[i];
		if (more<0) {
			more=-more;
			more=b[i+1]-more;
			if (more<0) {
				more=-more;
				ans[i][1]=more>=u[i]?u[i]:more;
				more=more>=u[i]?more-u[i]:0;
				u[i]-=ans[i][1];
				cnt+=ans[i][1];
				if (more) {
					dsu.merge(i);
					for (int j=dsu.find(i-1);more;j=dsu.find(j-1)) {
						if (more<=u[j]) {
							ans[j][1]+=more;
							u[j]-=more;
							cnt+=more;
							more=0;
						} else {
							ans[j][1]+=u[j];
							more-=u[j];
							cnt+=u[j];
							u[j]=0;
						}
						if (u[j]==0) dsu.merge(j);
					}
				}
			}
		}
	}
	write(cnt, '\n');
	more=b[1];
	for (int i=1;i<n;++i) p[i]-=ans[i][1];
	for (int i=1;i<n;++i) {
		if (more<=p[i]) write(more,' '),p[i]-=more;
		else write(p[i], ' '),p[i]=0;
		write(ans[i][1], ' ');
		write(p[i], '\n');
		more=b[i+1]-p[i];
	}
	return 0;
}
```

---

## 作者：__xxy_free_ioi__ (赞：1)

其实第一眼看上去像反悔贪心，可惜我没想出来怎么反悔。

所以还是老老实实地打了个动态规划。

我们设 $f_i$ 表示车站 $i$ 在市场 $i-1$ 的人不用买伞时最多能收容的人数。那么，可得方程式 $f_i = \max(0,b_i - \max(p_{i-1} - f_{i - 1}, 0))$。即，这个车站的容量减去上一个车站溢出的人数。

然后**从右往左**（主要是为了配合 $f$ 计算）遍历每一个市场，**能去右边就去右边**（因为右边已经处理完了），然后按题意模拟即可（具体看代码注释），若出现有人无处可去并且没有雨伞买是，则无解。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define VI vector<int>
#define PII pair<int, int>
#define up(i, s, t) for (int i = s; i <= t; i++)
#define dw(i, s, t) for (int i = s; i >= t; i--)

const int N = 1e6 + 2;

int n;
int b[N], p[N], u[N], f[N], l[N], r[N], t[N];
// l_i 去车站 i 的人数，r_i 去车站 i+1 的人数
// t_i 在市场 i 买雨伞的人数 

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	up(i, 1, n) cin >> b[i];
	up(i, 1, n - 1) cin >> p[i];
	up(i, 1, n - 1) cin >> u[i];
	up(i, 1, n) f[i] = max(0ll, b[i] - max(p[i - 1] - f[i - 1], 0ll));
	int cost = 0;
	dw(i, n - 1, 1) {
		r[i] = min(p[i], b[i + 1] - l[i + 1]); // 能去右边就去右边 
		l[i] = min(f[i], p[i] - r[i]); 
		// 在市场 i-1 的人能不买雨伞时，最多能去多少个到车站 i 
		t[i] = min(p[i] - l[i] - r[i], u[i]);
		l[i] += p[i] - l[i] - r[i] - t[i]; // 实在不行就让市场 i-1 的人买伞吧 
		if (l[i] > b[i]) return cout << "NO\n", 0; // 实在放不下人了 
		cost += t[i];
	}
	cout << "YES\n" << cost << '\n';
	up(i, 1, n - 1) cout << l[i] << ' ' << t[i] << ' ' << r[i] << '\n';
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

$n$ 个车站中间 $n-1$ 个广场，每个广场中有一定数量的雨伞，广场中的人可以选择走向相邻的两个车站之一或者买雨伞。问能否确保每个人都能不被雨淋湿，及买雨伞最少的方案。

### 题目分析

先来考虑怎么判断能否让每个人都不被淋湿。

我们不妨贪心的将所有的人尽可能的往左排，这样可以尽可能的给后面还没被考虑的人留空位。当一个广场上的人在填满了两侧车站和广场后还有人，则会被淋湿。

然后再来考虑买伞最少的方案。

我们发现对于上述安排方法，我们有可能会在中间空处一些车站的一些空位，从而预判后面会有人来填补，但并没有人来。我们考虑从右往左将所有的空位都用旁边广场的人填满，若还有空位则用左侧车站的人填充，这样可以在不会更劣的情况下为左侧申请到更多空位。

特别的我们发现不会有一些广场在第二步调整中广场中的人向左侧车站走，应为在第一步中我们都是尽可能向左填充的。

### code
```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

const int N = 1e6 + 5;
int n, b[N], p[N], u[N], l[N], m[N], r[N], ans;

signed main()
{
    scanf("%lld", &n);
    for(register int i = 1;i <= n;i++)   scanf("%lld", &b[i]);
    for(register int i = 1;i < n;i++)    scanf("%lld", &p[i]);
    for(register int i = 1;i < n;i++)    scanf("%lld", &u[i]);
    for(register int i = 1;i < n;i++)
    {
        l[i] = min(b[i] - r[i-1], p[i]);
        p[i] -= l[i];
        m[i] = min(u[i], p[i]);
        p[i] -= m[i];
        r[i] = p[i];
        if(r[i] > b[i+1])
        {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    for(register int i = 1;i < n;i++)
        b[i] -= l[i], b[i+1] -= r[i];
    for(register int i = n-1;i >= 1;i--)
    {
        register int mov = min(b[i+1], m[i]);
        m[i] -= mov, b[i+1] -= mov, r[i] += mov;
        mov = min(l[i], b[i+1]);
        l[i] -= mov, b[i+1] -= mov, b[i] += mov, r[i] += mov;
    }
    for(register int i = 1;i < n;i++)    ans += m[i];
    printf("%lld\n", ans);
    for(register int i = 1;i < n;i++)
        printf("%lld %lld %lld\n", l[i], m[i], r[i]);
    return 0;
}
```

---

## 作者：_awa_wangjiawen (赞：0)

## [P10051 [CCO2022] Rainy Markets](https://www.luogu.com.cn/problem/P10051)
第一眼反悔贪心，先把所有的人尽量移到车站，然后进行反悔。但是，我们蒟蒻不会反悔贪心，怎么办？

既然这道题反悔的难点是从车站回到商场，那我们就反着推，从商场去车站！

### 简要思路
先让所有人去商场买伞，卖完了再去车站（这里优先去第 $i$ 号车站）。如果左右车站和伞都卖完了还有人，直接输出 `NO`。（这也是一个优点，你不用在反悔的时候判断能否都不淋湿）。然后再让所有买伞的人去车站（这里优先去第 $i+1$ 号车站），再把第 $i$ 号车站的人移到第 $i+1$ 号车站。

## 实现
每个商场总体分 $7$ 步，对于第 $i$ 号商场
1. 在商场买伞。
2. 从商场去第 $i$ 号车站。
3. 从商场去第 $i+1$ 号车站。
4. 判断能否所有人都不淋湿。
5. 从商场去第 $i+1$ 号车站。
6. 从商场去第 $i$ 号车站。
7. 从第 $i$ 号车站去第 $i+1$ 号车站。

时间复杂度 $O(n)$，但是由于有很多 `if else` 所以常数其实很大，加上 $n$ 达到了 $10^6$ 用 `cin cout` 容易炸。建议使用快读快写、`scanf printf` 或关闭流同步。

## 代码
~~又臭又长的代码，码疯不咋地，凑合看看吧。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long fromthis,fromup;
	long long maxx,sum;
}sta[1000001];
struct node1{
	long long nump,numu;
}mar[1000001];
long long n,ans;
int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>sta[i].maxx;
		sta[i].sum=sta[i].maxx;
	}
	for(int i=1;i<n;i++)
		cin>>mar[i].nump;
	for(int i=1;i<n;i++)
	{
		cin>>mar[i].numu;
		if(mar[i].nump>mar[i].numu)
			mar[i].nump-=mar[i].numu;
		else
		{
			mar[i].numu=mar[i].nump;mar[i].nump=0;
		}
	}
	for(int i=1;i<n;i++)
	{
		if(mar[i].nump<=sta[i].sum)
		{
			sta[i].fromthis=mar[i].nump;
			sta[i].sum-=mar[i].nump;
			mar[i].nump=0;
			continue;
		}
		sta[i].fromthis=sta[i].sum;
		mar[i].nump-=sta[i].sum;
		sta[i].sum=0;
		if(mar[i].nump>sta[i+1].sum)
		{
			cout<<"NO";return 0;
		}
		sta[i+1].fromup=mar[i].nump;
		sta[i+1].sum-=mar[i].nump;
		mar[i].nump=0;
	}
	for(int i=n-1;i>=1;i--)
	{
		if(mar[i].numu>=sta[i+1].sum)
		{
			mar[i].numu-=sta[i+1].sum;
			sta[i+1].fromup+=sta[i+1].sum;
			sta[i+1].sum=0;
			if(mar[i].numu>sta[i].sum)
			{
				mar[i].numu-=sta[i].sum;
				sta[i].fromthis+=sta[i].sum;
				sta[i].sum=0;
			}
			else
			{
				sta[i].fromthis+=mar[i].numu;
				sta[i].sum-=mar[i].numu;
				mar[i].numu=0;
			}
		}
		else
		{
			sta[i+1].sum-=mar[i].numu;
			sta[i+1].fromup+=mar[i].numu;
			mar[i].numu=0;
			if(sta[i].fromthis<sta[i+1].sum)
			{
				sta[i].sum+=sta[i].fromthis;
				sta[i+1].sum-=sta[i].fromthis;
				sta[i+1].fromup+=sta[i].fromthis;
				sta[i].fromthis=0;
			}
			else
			{
				sta[i].sum+=sta[i+1].sum;
				sta[i].fromthis-=sta[i+1].sum;
				sta[i+1].fromup+=sta[i+1].sum;
				sta[i+1].sum=0;
			}
		}
	}
	for(int i=1;i<n;i++)
		ans+=mar[i].numu;
	cout<<"YES\n"<<ans<<endl;
	for(int i=1;i<n;i++)
		cout<<sta[i].fromthis<<" "<<mar[i].numu<<" "<<sta[i+1].fromup<<endl;
	return 0;
}
```

---

## 作者：ruik (赞：0)

#### 题意
题意其实十分显著，在一条笔直的道路上有多个集市与公交车站。此时下起了雨，而在集市上的人需要避雨，他们可以去相邻的公交车站或买伞避雨，你需要求出是否能让所有人都能避雨。若能，则求出总买伞数最少的方案。
#### 难点
由于我们要求出买伞数最少的方案，所以我们要让集市中的人尽可能到车站躲雨。从这里可以看出本题是一道贪心题。其难点无非于如何合理分配到个车站的人数才能利益最大化。
#### 思路
我们可以先将一种可行，但不是最优的方案算出，再来进行调整。在第一遍时，只需要判断是否能让所有人都能避雨，在第二遍再将买伞的人分配到有空余的车站中。
#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,c,f,umb,b[1002000],s[1002000],r[1002000],p[1002000],u[1002000],x[1002000],y[1002000];
bool wa;
int main(){
    scanf("%d",&n); 
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]); 
	for(int i=1;i<n;i++)scanf("%lld",&p[i]); 
	for(int i=1;i<n;i++)scanf("%lld",&u[i]);
	for(int i=1;i<n;i++){                                                                       //第一遍 
		p[i]>=(b[i]-y[i-1])?(p[i]-=(b[i]-y[i-1]),x[i]=(b[i]-y[i-1])):(x[i]=p[i],p[i]=0);        //尽可能多地能放到 i-1 个车站 
		p[i]>=u[i]?(p[i]-=u[i],r[i]=u[i]):(r[i]=p[i],p[i]=0);                                   //尽剩下的可能多地能放到本集市 
		p[i]>b[i+1]?wa=1:(y[i]=p[i],p[i]=0);                                                    //剩下的都放入 i+1 个车站，如果还有剩余，输出NO 
	}
	if(wa==1)cout<<"NO";
	else {
		puts("YES");
		for(int i=n;i>1;i--){                                                                    //第二遍 
			int xz=b[i]-y[i-1]-x[i];
			xz<=r[i-1]?(r[i-1]-=xz,y[i-1]+=xz,xz=0):(xz-=r[i-1],y[i-1]+=r[i-1],r[i-1]=0);        //尽量消本集市的买伞人数 
			xz<=x[i-1]?(x[i-1]-=xz,y[i-1]+=xz):(y[i-1]+=x[i-1],x[i-1]=0);                        //如果还有空余，将 i-1 车站的人也拉过来 
		}
		for(int i=1;i<n;i++)umb+=r[i];
		cout<<umb<<endl;
		for(int i=1;i<n;i++)printf("%lld %lld %lld\n",x[i],r[i],y[i]);
	}
    return 0;
}
```

---

## 作者：songzhixin (赞：0)

### 题目大意

有 $n$ 个车站，$n-1$ 个市场，每个车站可以让 $B_i$ 个人躲雨，每一个市场有 $P_i$ 个人，可以买 $U_i$ 把雨伞。每个集市的人可以到车站 $i$ 或者车站 $i+1$ 或者卖伞来躲雨。

最后求的是是否可以让所有人躲雨，若可以，尽可能少的买伞，求一种最优策略。

### 解题思路

我一看到题，兴冲冲的写了经典的贪心，也就是先去左边，再去右边，最后买伞，保证买的伞最少，若最后还不够就输出 `NO`。

结果可想而知，只能得第一个捆绑测试的分。错误的地方在哪里呢?

我们如果把第二个样例的 $11$ 和 $0$ 交换，我们都知道这样子是有解的，但是程序却会输出无解。这是因为第一个集市的人的人把右边的位置给占了一块，但是第二个集市没有雨伞卖，导致不能全部避雨。但如果我们让第一个集市卖 $5$ 把伞，是不是就可以让所有人避雨了？

因此我们先从后往前遍历一遍，策略为先去右边，在卖伞，最后往左边，这样可以保证留给左边的尽可能的多。这样可以判断有无解。但是记录去左边的人数的数组不要清空，后面还要用。

我们再从前往后遍历一遍，我们的策略为先去左边，因为没人跟它争了，再去右边，去的人数为上回我们判断有误解时留给这一个集市的人数，最后再去卖伞。

为何这样是最优的呢？因为第一你这样子是一定有解的，因为你第一次遍历证明了。第二，你假设右边可以多去一些，这里可以少买一些伞，但是你在下一个集市一定会又把这些伞卖回来，所以这样一定可以得到最优解。

### 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=1e6+5;
long long a[N];
long long b[N],c[N]; 
long long d[N];
long long e[N];
long long l[N],y[N],r[N];
int main() {
	long long n;
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(long long i=1;i<n;i++){
		scanf("%lld",&b[i]);
	}
	for(long long i=1;i<n;i++){
		scanf("%lld",&c[i]);
	}
	d[n]=a[n];
	for(long long i=n-1;i>=1;i--){//第一次遍历看是否可行
		long long x=b[i];
		x-=d[i+1];
		if(x<=0){
			d[i]=a[i];
			continue;
		}
		x-=c[i];
		if(x<=0){
			d[i]=a[i];
			continue;
		}
		if(a[i]<x){
			printf("NO\n");
			return 0;
		}
		d[i]=a[i]-x;
	}
	long long ans=0;
	for(long long i=1;i<=n-1;i++){//第二次遍历求最优解
		long long x=b[i];
		if(x<=a[i]-r[i-1]){
			l[i]=x;
			y[i]=0;
			r[i]=0;
			continue;
		}
		l[i]=a[i]-r[i-1];
		x-=l[i];
		if(x<=d[i+1]){
			r[i]=x;
			y[i]=0;
			continue;
		}
		r[i]=d[i+1];
		x-=r[i];
		y[i]=x;
		ans+=x;
	}
	printf("YES\n%lld\n",ans);
	for(int i=1;i<=n-1;i++){
		printf("%lld %lld %lld\n",l[i],y[i],r[i]);
	}
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10055)。


solution
------------
首先先搞清楚每个数组的含义：

- $b_i$，公交车站 $i$ 的容量。

- $p_i$，市场 $i$ 的人数。

- $u_i$，市场 $i$ 出售的雨伞的数量。

解决 $\texttt{Subtask}\ 1$
------------

观察这类数据，对于所有 $u_i$，满足 $u_i = 0$，也就是说没有市场有雨伞。所以考虑贪心。

我们尽量将市场 $i$ 的人尽量往车站 $i$（这里**从左往右贪心**，让右边的车站**腾出更多的空位给右边的市场**）。这是分三种情况：

- $p_i > b_i + b_{i+1}$，两边的车站都放不满人，直接输出 $\texttt{NO}$。

- 否则，如果 $p_i > b_i$，那么将剩下的 $p_i - b_i$ 人分配到第 ${i+1}$ 个车站里。

- 再否则，$p_i < b_i$，将 $p_i$ 个人直接分配到第 $i$ 个车站即可。


代码实现很简单，就不展示了~~（我也没打）~~。


合并解决 $\texttt{Subtask}\ 1,2,3,4$
------------
将 $\texttt{Subtask}\ 1$ 的 $u_i = 0$ 的思路转移到解决 $\texttt{Subtask}\ 1,2,3,4$ 里来。

然后**从右往左贪心**（让没有贪心过的先来），这是我们会尽量把人分配到第 $i+1$ 个车站。

设 $dp_i$ 表示按照 $u_i=0$ 的贪心跑完第 $1$ 到 $i-1$ 个车站后，车站 $i$ 还可以容纳的人数。

则不难转移出如下方程：

$$dp_i = \max ({b_i - \max({p_{i-1}-dp_{i-1},0}),0})$$

也就是说，我们至多往第 $i$ 个车站分配 $dp_i$ 人。

用 $l_i$，$r_i$，$rainy_i$ 表示第 $i$ 个市场去左边、右边及卖雨伞的人数。

若还不够分配人，我们则考虑买伞（因为 $u_i > 0$）：分配到右边的车站可以保证尽量有解。

如果不够则往第 $i$ 个车站分配人。这是如果还是不够则输出 $\texttt{NO}$。

时间复杂度为 $\Theta(n)$。

核心代码如下：

```cpp
FOR(i,1,n-1)
    dp[i]=max(B[i]-max(P[i-1]-dp[i-1],0ll),0ll);
DOR(i,n-1,1){
    r[i]=min(P[i],B[i+1]-l[i+1]);//算去右边的人数。
    P[i]-=r[i];//减一减。
    l[i]=min(P[i],dp[i]);//算可以去左边的人数。
    P[i]-=l[i];//减一减。
    rainy[i]=min(P[i],U[i]);//取最小值，算买雨伞的数量。
    P[i]-=rainy[i];//减一减。
    sum+=rainy[i];
    l[i]+=P[i];//计算去左边的人数。
    if(l[i]>B[i]){//如果超过，则误解。
        printf("NO\n");
        exit(0);
    }
}
```

注：部分参考于[这里](https://www.luogu.com.cn/blog/Leasier/solution-QOJ4269)。

---

