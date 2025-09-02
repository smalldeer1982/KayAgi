# [USACO24OPEN] Cowreography G

## 题目描述

奶牛们组了一支舞蹈队，Farmer John 是她们的编舞！舞蹈队最新而最精彩的舞蹈有 $N$ 头奶牛（$2\le N\le 10^6$）排成一行。舞蹈中的每次动作都涉及两头奶牛，至多相距 $K$ 个位置（$1\le K < N$），优雅地跳起并降落在对方的位置上。

队伍中有两种奶牛——更赛牛（Guernsey）和荷斯坦牛（Holstein）。因此，Farmer John 将这一舞蹈记录为一系列**长为 $N$ 的 `01` 字符串**，其中 `0` 代表更赛牛，`1` 代表荷斯坦牛，整个字符串表示奶牛在这一行中是如何排列的。

不幸的是，Farmer Nhoj（对手团队的编舞）蓄意破坏了这一舞蹈，并清除了除第一个和最后一个 `01` 字符串之外的所有内容！由于一场大型比赛即将开始，Farmer John 必须抓紧每一秒重建这一舞蹈。

给定这两个 `01` 字符串，帮助 Farmer John 求出舞蹈中的最小动作数量！ 

## 说明/提示

### 样例解释 1

一个可能的舞蹈：

```plain
0111 -> 1011 -> 1101 -> 1110
```
### 样例解释 2

一个可能的舞蹈：

```plain
11000 -> 01100 -> 00110 -> 00011
```

### 样例解释 3

一个可能的舞蹈：

```plain
11000 -> 10010 -> 00011
```

### 测试点性质

- 测试点 $4-5$：$K=1$。
- 测试点 $6-7$：两个字符串各至多包含 $8$ 个 $1$。
- 测试点 $8-15$：$N\le 5000$。
- 测试点 $16-23$：没有额外限制。


## 样例 #1

### 输入

```
4 1
0111
1110```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2
11000
00011```

### 输出

```
3```

## 样例 #3

### 输入

```
5 4
11000
00011```

### 输出

```
2```

# 题解

## 作者：hejianxing (赞：15)

[link](https://www.luogu.com.cn/problem/P10280)

# 题意

给定两个 `01` 串，每次操作可以将距离不超过 $k$ 的两个字符交换，求 $s\to t$ 的最小步数。

$n,k\le 10^6$。

# 题解

考虑交换两个数，步数显然为 $\lceil\frac{y-x}{k}\rceil$。若没有取整，那么直接顺着扫过去，找到前后不一样的贪心选取即可，即每找到一个不一样的就马上与前面的任意一个交换。

容易感受到需要让取整时补出来的距离尽量少，也就是让每次的 $\lceil\frac{y-x}{k}\rceil k-(y-x)$ 尽量小。

当一个位置为 $i$ 的数需要交换时，选取一个 $j\equiv i\pmod k$ 的数是最优的，$j\equiv i+1\pmod k$ 次之，以此类推。

于是用 `set` 维护等待交换的位置，按 $i\bmod k$ 排序。如果无法交换就把当前位置塞进去。如果可以交换，查找最优的位置是简单的，计算答案也是简单的。

时间复杂度 $O(n\log n)$。

# 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000005;
int n, k;
LL ans = 0;
char a[N], b[N];
#define mp make_pair
multiset<pair<int, int>> s[2];
int main() {
    scanf("%d%d%s%s", &n, &k, a + 1, b + 1);
    for (int i = 1; i <= n; i++)
        if (a[i] != b[i]) {
            int x = a[i] - '0';
            if (s[!x].empty()) s[x].insert(mp(i % k, i));
            else {
                auto it = s[!x].lower_bound(mp(i % k, 0));
                if (it == s[!x].end()) it = s[!x].begin();
                ans += (i - (it -> second) - 1) / k + 1, s[!x].erase(it);
            }
        }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：David_Mercury (赞：11)

### Preface

提供一份严谨的数学证明。

感谢 @[lupengheyyds](https://www.luogu.com.cn/user/580608) 帮助证明了部分结论。

---

### 前置数学知识

- 定义 $\{x\} = x - \lfloor x \rfloor$，即 $x$ 的分数部分。它也可以表示为 $\{x\} = x \bmod 1$。

- $[P(x)]$ 为艾弗森括号，当命题 $P(x)$ 为真时值为 $1$，否则为 $0$。

- $\bmod$ 运算满足分配律，即 $c(x \bmod y) = cx \bmod cy$。

- $\lceil -x \rceil = -\lfloor x \rfloor$

---

### Part 1.

可以发现，问题等价于将 $s$ 中的每个 $1$ 与 $t$ 中的每个 $1$ 两两配对，并最小化代价。

这里我们需要先证明一下这个“代价”是什么：

> 引理：将位置 $x, y$ 交换**并保持中间数不改变**的最优移动次数为 $\lceil (y-x)/k \rceil$。（$x, y$ 满足 $x < y, s[x] \ne s[y]$。）

证明：使用数学归纳法。当 $y-x \le k$ 时结论显然成立。当 $y-x > k$ 时，若 $s[x] \ne s[x+k]$，则我们可以直接交换 $x, x+k$，问题转化到 $x+k, y$ 的情形；否则 $s[x] = s[x+k]$，我们则可以先对 $x+k$ 和 $y$ 进行交换操作，这时就有 $s[x] \ne s[x+k]$ 了。

---

### Part 2.

> 引理：如果有 $a, b, c, d$ 四个位置满足 $c > a > b$ 且 $a > d$，则绝对不会出现 $(c, b)$ 配对、$(a, d)$ 配对的情况。
>
> 对于 $c < a < b$ 且 $a < d$ 同理。
>
> 用人话表述，就是对于序列 $s$ 中的所有 $1$，绝对可以分为若干段“全部向右匹配”或者是“全部向左匹配”的段。**绝对不会出现“交叉”的情形**。

证明：

1. $c > a > b > d$

   如果无交叉配对，即 $(c, a)$ 配对、$(b, d)$ 配对，有代价：

   $$\left\lceil \dfrac{c-a}{k} \right\rceil + \left\lceil \dfrac{b-d}{k} \right\rceil$$

   如果有交叉配对，即 $(c, b)$ 配对、$(a, d)$ 配对，有代价：

   $$\left\lceil \dfrac{c-b}{k} \right\rceil + \left\lceil \dfrac{a-d}{k} \right\rceil$$

   显然有：

   $$\left\lceil \dfrac{c-a}{k} \right\rceil \le \left\lceil \dfrac{c-b}{k} \right\rceil, \left\lceil \dfrac{b-d}{k} \right\rceil \le \left\lceil \dfrac{a-d}{k} \right\rceil$$

   结论成立。

3. $c > a > d > b$

   代价式子和上面是一样的。而由于此时有：

   $$\left\lceil \dfrac{c-b}{k} \right\rceil \ge \left\lceil \dfrac{c-a+d-b}{k} \right\rceil \ge \left\lceil \dfrac{c-a}{k} \right\rceil + \left\lceil \dfrac{d-b}{k} \right\rceil - 1$$

   故有：

   $$\begin{aligned} \left\lceil \dfrac{c-b}{k} \right\rceil + \left\lceil \dfrac{a-d}{k} \right\rceil &\ge \left\lceil \dfrac{c-a}{k} \right\rceil + \left\lceil \dfrac{d-b}{k} \right\rceil + \left(\left\lceil \dfrac{a-d}{k} \right\rceil - 1\right) \\ &\ge \left\lceil \dfrac{c-a}{k} \right\rceil + \left\lceil \dfrac{d-b}{k} \right\rceil \end{aligned}$$

    结论成立。

由于该结论成立，我们完全可以将整个序列拆成若干段来处理，每段内有“$t$ 的前缀和 $\ge$ $s$ 的前缀和”或“$s$ 的前缀和 $\ge$ $t$ 的前缀和”。因为二者是对称的，在接下来的推导中我们将以前者为例，即所有 $s$ 中的 $1$ 向右方 $t$ 中的 $1$ 配对。

---

### Part 3.

> 注意：接下来我们就要开始推式子了，请你回顾一下前面的数学前置知识。

设 $n$ 表示该段中 $1$ 的个数，$p(i)$ 为一个 $1 \sim n$ 的排列，$s_i, t_i$ 分别表示 $s, t$ 内该段中第 $i$ 个 $1$ 的下标。则我们可以写出该段的代价表达式：

$$\sum_{i=1}^n \left\lceil \dfrac{t_{p(i)} - s_i}{k} \right\rceil$$

由于我们更喜欢向下取整，我们将其化为如下的形式：

$$\sum_{i=1}^n \left\lceil \dfrac{t_{p(i)} - s_i}{k} \right\rceil = - \sum_{i=1}^n \left\lfloor \dfrac{s_i - t_{p(i)}}{k} \right\rfloor$$

然后我们发现，如果**将分数部分提出，我们将得到一个定值**。令 $x_i = \dfrac{s_i}{k}, y_i = -\dfrac{t_i}{k}$，有：

$$\sum_{i=1}^n \lfloor x_i+y_{p(i)} \rfloor = \sum_{i=1}^n x_i + \sum_{i=1}^n y_i - \sum_{i=1}^n \{x_i + y_{p(i)}\}$$

于是我们需要最小化 $\sum_{i=1}^n \{x_i + y_{p(i)}\}$。

令 $x_i' = \{x_i\}, y_i' = \{y_i\}$，有：

$$\sum_{i=1}^n \{x_i + y_{p(i)}\} = \sum_{i=1}^n x_i' + \sum_{i=1}^n y_i' - \sum_{i=1}^n [x_i' + y_{p(i)}' \ge 1]$$

于是我们需要最大化 $\sum_{i=1}^n [x_i' + y_{p(i)}' \ge 1]$。

$$\begin{aligned}\sum_{i=1}^n [x_i' + y_{p(i)}' \ge 1] &= \sum_{i=1}^n \left[ \dfrac{s_i}{k} \bmod 1 + \left(-\dfrac{t_{p(i)}}{k}\right) \bmod 1 \ge 1 \right] \\ &= \sum_{i=1}^n \left[ s_i \bmod k + (-t_{p(i)}) \bmod k \ge k \right]\end{aligned}$$

于是我们需要最大化余数相加 $\ge k$ 的对数。

不难想到如下贪心：让每个 $(-t_i)$ 匹配最小的能够 $\ge k$ 的 $s_i \bmod k$；如果找不到，那就匹配一个最小的 $s_i \bmod k$ 以减少损失。换句话说，就是匹配第一个 $\ge t_i \bmod k$ 的 $s_i \bmod k$，如果找不到就匹配最小的 $s_i \bmod k$。

用 `set` 维护，能在 $O(n \log n)$ 的时间复杂度内解决本题。

代码嘛，本质上和其他题解是一模一样的，就不放了。

---

## 作者：wYYSZLwSSY (赞：11)

真的太菜了。感觉好难。第一个"显然"就研究了好久。

## 题解
先看一些结论。

**结论1：** 交换 $i,j$，同时保持中间不变的最小步数是 $\lceil \frac{j-i}{k}\rceil$。

假设我们想要把 $a_i$ 推到位置 $j$（$i < j$），假设不考虑维持其他位置不变，显然最小步数是 $\lceil \frac{j-i}{k}\rceil$。

显然当 $a_i\neq a_j$ 时交换才有意义，不妨设交换 $i,j$ 有关的序列（包括两端）一开始左端点有 $b$ 个 $1$，右端有一些 $a$ 个 $0$，利用如下操作可以用 $a+b$ 步递归成规模小 $a+b$ 的问题：

$11111.....00000$->$011111...000001$。

变成了操作 $1...0$ 的问题，规模变小量等于操作数。

递归到最后，利用：$111000$->$011100$->$011001$ 可以用与规模数相同的操作数完成交换。

因此，总的操作数=总的规模=$\lceil \frac{j-i}{k}\rceil$。

**由结论一可知，我们最终的交换其实是所有 $s_i\neq t_i$ 的两两匹配。**

**结论2：** 假设没有向上取整，那么每个 $s_i\neq t_i$ 的 $s_i$  与前面任意一个未匹配过的 $s_j\neq t_j$ 的 $t_j$ 匹配（当然要 $s_i \neq t_j$）一定都是最优秀的（如果没有这样的 $j$，则暂时不匹配）。

这不难证明，可以理解为只要这样选，代价一定等于参与匹配所有 $s$ 的下标和减去参与匹配的 $t$ 的下标和，不可能有更小的结果。

**结论3：** 考虑向上取整，每次选择与前面未匹配过的 $s_j\neq t_j$ 的，$(j-i+k)\bmod k$ 最小的 $t_j$ 匹配（当然要 $s_i \neq s_j$）是最优的。

考虑向上取整，想要答案最小，一定要让总的 $(j-i+k)\bmod k$ 最小，因为这是向上取整的增加量乘上 $k$ 的结果。

那么为什么每次贪心地选最小是最优秀的？

假设两次选择之间没有再加入其他可供选择的没匹配的，考虑将 $(j-i) \bmod k$ 小于 $0$ 的部分加上 $2k$，问题就变成了每次匹配后面的数，和根据结论 2，答案最小即被匹配的 $(j-i)\bmod k (+2k)$ 和最小，显然贪心策略正确。其他情况类似。

**具体做法：**

综上，我们可以从前往后枚举，当遇到 $s_i\neq t_i$ 时，就与前面没有匹配的，$s_i\neq s_j$，$s_j \neq t_j$，$(j-i+k) \bmod k$ 最小的 $j$ 交换。如果没有这样的 $j$，就不交换，等待后面的与它交换。（最终肯定是可以而且要交换的）

找 $(j-i+k) \bmod k$ 最小的 $j$ 其实是一个找后继的过程，可以使用 `set` 解决。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,k;
string s,t;
int ans;
set<pair<int,int> >st[2];
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	//freopen("1.in","r",stdin);
	cin>>n>>k;
	cin>>s>>t;
	for(int i=0;i<n;++i){
		if(s[i]==t[i])continue;
		bool op=s[i]-'0';
		if(st[op].size()){
			auto x=st[op].lower_bound({i%k,-114});
			if(x==st[op].end())x=st[op].begin();
			ans+=ceil((i-(x->second))*1.0/k);
			st[op].erase(x);
		}else st[t[i]-'0'].insert({i%k,i});
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：5)

1.9 小时通关金组，你值得拥有！

考虑交换两个位置 $x,y(x<y)$ 的代价。

首先 $y-x\le K$ 时代价为 $1$。

考虑 $p\in(x,y)$，如果 $a_p=a_x$，则将 $p$ 和 $y$ 交换，再将 $p$ 和 $x$ 交换，反之同理，进而得出最小代价为 $\lceil\frac{y-x}K\rceil$。

从前往后维护始态和终态不同的位置，如果新加入的位置和之前的相同，就插入，否则选取之前的某一个与其匹配。

你会发现，这里无论选最早或最晚的与其匹配都不一定是最优的。

实际上，我们希望上取整时补的数组尽量小，也即模 $K$ 意义下的后继，使用 `std::set` 维护即可。

时间 $O(n\log n)$，空间 $O(n)$：
```cpp
int n,K;
string s,t;
set<pair<int,int> >st[2];
ll ans;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z;ll v1,v2;
    cin>>n>>K>>s>>t;
    for(i=0;i<n;++i)
        if(s[i]!=t[i]){
            r=48^s[i];
            if(st[r].size()){
                auto it=st[r].lower_bound(mkp(i%K,0));
                if(it==st[r].end())it=st[r].begin();
                ans+=(i-it->second-1)/K+1;
                st[r].erase(it);
            }else st[!r].emplace(i%K,i);
        }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：onlycre (赞：3)

首先考虑没有 $k$ 的限制怎么做，那么我们只需要扫一遍序列，然后记录变量表示 $01$ 的位置的数量或者 $10$ 的位置数量，显然任何时刻这两个至少有一个为 $0$ ，因为当我们碰到 $10$ 的时候，如果手上有 $01$ 就将他们交换，另一种情况也是一样的。

现在加上了 $k$ 的限制，只需要再维护 $01$ 或 $10$ 的位置信息，这样当我们遍历到第 $i$ 的位置时，我们将 第$i-k$ 位置和现在的位置交换，保证距离不超过 $k$。

看一下代码应该就很容易理解。

赛时代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring> 
#include<cmath>
#include<vector>
#include<queue>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define rpe(i,x) for(int i=_he[x];i;i=_ne[i])
using namespace std;
typedef long long LL;
const int N=1e6+10;

int n,k,a[N],b[N],dx[N],dy[N];

int ctx,cty;
int main()
{
	scanf("%d%d",&n,&k);
	rep(i,1,n)scanf("%1d",&a[i]);
	rep(i,1,n)scanf("%1d",&b[i]);
	
	LL ans=0;
	rep(i,1,n)
	{
		if(a[i]!=b[i])
		{
			if(a[i])
			{
				dy[i]++,cty++;
				if(ctx)
				{
					rep(j,max(1,i-k),i-1)
						if(dx[j]){dx[j]--,dy[i]--,ctx--,cty--,ans++;break;}//贪心地拿距离远的换
				}
			}
			else
			{
				dx[i]++,ctx++;
				if(cty)
				{
					rep(j,max(1,i-k),i-1)
						if(dy[j]){dy[j]--,dx[i]--,ctx--,cty--,ans++;break;}				
				}
			}
		}
		if(i-k>=1)
		{
			if(dx[i-k])ans+=dx[i-k],dx[i]+=dx[i-k],dx[i-k]=0;
			if(dy[i-k])ans+=dy[i-k],dy[i]+=dy[i-k],dy[i-k]=0;
		}
	}
	
	printf("%lld\n",ans);
	return 0;
}
```

这一份代码是 $O(n^2)$ 的，但是因为有剪枝所以能直接过，优化到 $O(n\log n)$ 非常的 trival，就不放代码了~~我没写~~。

---

## 作者：block_in_mc (赞：2)

首先有一个结论：若 $s_i\not=s_j$，交换 $s_i$ 和 $s_j$ 且不改变它们中间的字符的代价为 $\lceil\frac{i-j}{k}\rceil$。

首先，答案的下界显然为 $\lceil\frac{i-j}{k}\rceil$，因为即使不管中间字符的顺序，也要进行这么多次操作。现在只需要证明一定能在 $\lceil\frac{i-j}{k}\rceil$ 次操作内完成即可。

对于 $i-j\le k$ 的情况，显然成立；现在考虑 $j-i>k$ 的情况。若 $s_j=s_{j+k}$，我们可以先交换 $s_j$ 和 $s_{j+k}$，再递归地考虑交换 $s_{j+k}$ 和 $s_i$ 即可；否则一定有 $s_{j+k}\not=s_i$，先递归地考虑交换 $s_{j+k}$ 和 $s_i$，再交换 $s_j$ 和 $s_{j+k}$ 即可。

由于每次操作都会将 $i-j$ 减少 $k$，总操作次数即为 $\lceil\frac{i-j}{k}\rceil$。

假如没有上取整，这显然是好做的：对于每一个 $s_i\not=t_i$ 的 $i$，若存在一个还没有被匹配过的 $j$ 满足 $s_j\not=t_j$ 且 $s_i\not=s_j$，任选一个 $j$ 进行匹配即可，容易证明任何选择的答案都是相同且最优的；否则继续往后找，等待后面的数将其匹配。

现在有了上取整，可以发现，如果 $(i-j)\bmod k$ 不为 $0$，其值越小，损失越大，因为同样次数的交换还可以在多走 $k-((i-j)\bmod k)$ 格。既然这样，在上面的过程中，我们不如选 $(i-j)\bmod k$ 较大的 $j$，从而减少损失的值。

实现的时候，记录两个 `set<pair<int, int>>`，分别代表 $s_i=0$ 或 $1$ 时符合条件的还没有被匹配的 $j$ 的 $j\bmod k$ 和下标。使 $(i-j)\bmod k$ 为 $0$ 或尽量大的 $j$ 即为第一个 $j\bmod k$ 大于等于 $i\bmod k$ 的 $j$。若找不到，则为 $j\bmod k$ 最小的一个 $j$。

AC 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
string s, t;
set<pair<int, int>> st[2];
long long ans;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> k >> s >> t;
	for (int i = 0; i < n; i++) {
		if (s[i] == t[i]) continue;
		int vl = s[i] - '0';
		if (st[vl].empty()) { st[!vl].insert({i % k, i}); continue; }
		auto it = st[vl].lower_bound({i % k, 0});
		if (it == st[vl].end()) it = st[vl].begin();
		ans += ceil(1.0 * (i - (it -> second)) / k);
		st[vl].erase(it);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ZnPdCo (赞：2)

提供一种 $O(n)$ 做法。

我们设 $d_i$ 的绝对值表示**最远**能够到达 $i$ 且**未被匹配**的元素个数。若 $d_i>0$，则这些元素都是 $S_x=1,T_x=0$ 的（称为 $1$ 元素）；若 $d_i<0$，则这些元素都是 $S_x=0,T_x=1$ 的（称为 $-1$ 元素）。发现不存在即既有 $1$ 元素又有 $-1$ 的 $i$，因为这样的话 $1$ 元素和 $-1$ 元素可以相互交换以抵消。

考虑将 $i$ 从小到大扫，假设当前考虑到第 $i$ 个元素的匹配问题。

首先对于 $j<i$ 的位置，我们需要花费 $|d_j|$ 的代价，将他们都向右移动 $k$ 位作为新的最远能够到达的位置，因为它们无法与第 $i$ 位及之后的位匹配了。

接下来我们判断 $i$ 能否与距离 $i$ 最近的 $d_j$ 匹配（能被匹配当且仅当元素正负性不同，即一个是 $1$ 元素一个是 $-1$ 元素），如果可以，我们将 $d_j$ 与 $d_i$ 匹配，如果不可以，说明两个元素正负性是相同的，那么元素 $j$ 之所以没有匹配，是因为和它匹配的元素也没有匹配上，以此类推，说明后面的都没有匹配上，那么我们就不需要往下面搜索了，作为未被匹配的元素加入 $d_i$，由后面的元素来匹配。

我们使用双端队列来修改可以做到 $O(n)$ 的复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 2000010
ll n, k, ans;
char s[N], t[N];
deque<pair<ll, ll> > deq;
int main() {
	scanf("%lld %lld %s %s", &n, &k, s + 1, t + 1);
	for(ll i = 1; i <= n; i ++) {
		ll d = s[i] - t[i];
		while(deq.size() && deq.begin()->first < i) {	// 对于最远能够到达距离小于i的元素，我们花费abs的代价将它们向后移动k个单位
			ans += abs(deq.begin()->second);
			deq.push_back(make_pair(deq.begin()->first + k, deq.begin()->second));
			deq.pop_front();
		}
		if(s[i] != t[i]) {
			if(deq.size() && deq.begin()->second * d < 0) {	// 如果能被匹配
				deq.begin()->second += d;
				if(deq.begin()->second == 0) {
					deq.pop_front();
				}
			} else {	// 加入未被匹配队列
				if(deq.size() && deq.begin()->first == i) {
					deq.begin()->second += d;
				} else {
					deq.push_front(make_pair(i, d));
				}
			}
		}
	}
	printf("%lld", ans);
}
```

---

## 作者：Lame_Joke (赞：2)

- ### 大体思路

这道题是一个贪心的思想，我们可以在当前点需要换时尽可能地与当前点距离远的，并且有需要与当前点换的交换，这里可以暴力枚举前 $K$ 个，可这样会很慢，所以建议用一个队列存需要换的点。我们发现有时前面的点还没处理完，但是到下一个点时就处理不了了，我们就不能管贪不贪心了，把下一个点就处理不了的直接换到前面，所以不难想到用两个数组分别储存每个点前面有多少个未交换的点。

- ### 具体实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1000005],b[1000005],x[1000005],y[1000005],nx[1000005],st=1,ny[1000005],st1=1;
int ctx,cty;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) while(a[i]!='0'&&a[i]!='1') a[i]=getchar();
	for(int i=1;i<=n;i++) while(b[i]!='0'&&b[i]!='1') b[i]=getchar();
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		while(nx[st]<i-k&&st<=ctx) st++;
		while(ny[st1]<i-k&&st1<=cty) st1++;  //判断队列队首是否可用 
		if(a[i]!=b[i])
		{
			if(a[i]=='1')
			{
				y[i]++;                      //当前点要换 
				ny[++cty]=i;                 //加入队列 
				if(st<=ctx)                  //说明有可以与之换的，换 
				{
					x[nx[st]]--;
					y[i]--;
					cty--;
					if(x[nx[st]]<=0) st++;
					ans++;
				}
			}
			else
			{
				x[i]++;
				nx[++ctx]=i;
				if(st1<=cty)                //同上 
				{
					y[ny[st1]]--;
					x[i]--;
					ctx--;
					if(y[ny[st1]]<=0) st1++;
					ans++;
				}
			}
		}
		if(i-k>=1)
		{
			if(x[i-k]!=0)                  //有未处理完且下个点处理不了的 
			{
				ans+=x[i-k];
				x[i]+=x[i-k];
				if(nx[ctx]!=i) nx[++ctx]=i;
				x[i-k]=0;
			}
			if(y[i-k]!=0)                  //同上 
			{
				ans+=y[i-k];
				y[i]+=y[i-k];
				if(y[cty]!=i) ny[++cty]=i;
				y[i-k]=0;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}

---

## 作者：Wei_Han (赞：1)

假设交换两位置的距离为 $m$，那么交换次数为 $\left \lceil \frac{m}{k} \right \rceil$，考虑到这点，显然，取上整有时会带来多余的一次，那么我们就要尽量让这一次多余的跳的最近。

那么贪心思路就让 $\left \lceil \frac{m}{k} \right \rceil$ 最小，且找到一个位置 $j$ 使得 $\left \lceil \frac{i-j}{k} \right \rceil \times k - (i-j)$ 最小,推一下可以发现，最优的时候为 $i\equiv j~(mod~k)$，注意到这个问题可以二分处理，但是带删除，用```set```维护即可。

注意实现时按照取模后的值插入```set```，假如当前```set```不为空，二分找到最优位置即可。

时间复杂度 $O(n\log n)$。
### Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
#define min(a,b) (a>b?b:a)
#define bug(x,y) (x<1||y<1||x>15||y>15)
using namespace std;
typedef long long ll;
typedef double db;
const int N=2e6+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll n,k;
string s1,s2;
set<pii> s[2];// 01 10 
signed main(){
	read(n),read(k);
	cin>>s1>>s2;
	s1=" "+s1;s2=" "+s2;
	ll sum=0;
	fo(1,i,n){
		if(s1[i]!=s2[i]){
			ll op1=s1[i]-'0';
			if(s[op1].empty()) s[!op1].insert({i%k,i});
			else{
				auto it=s[op1].lower_bound({i%k,0});
				if(it==s[op1].end()) it=s[op1].begin();
				sum+=(i-((*it).second)-1)/k+1,s[op1].erase(it);
			}
		}
	}
	wr(sum);
	return 0;
}
``````

---

## 作者：_H17_ (赞：0)

## 前言

非常好，肥肠有意思的神秘贪心题！！！

## 题目分析

我们假设两个字符串分别是 $a,b$。

我们把点分成 $3$ 类：对于 $i$，如果 $a_i=\texttt{0},b_i=\texttt{1}$，这是第 $1$ 类点；如果 $a_i=\texttt{1},b_i=\texttt{0}$，这是第 $0$ 类点；其他点是 $2$ 类点。

我们需要把一个 $0$ 类点和一个 $1$ 类点匹配，使得步数最小。对于 $2$ 类点，显然不动最优。

考虑两个点分别为 $i,j(i<j)$，两者是不同类型的非 $2$ 类点。通过交换把他们换成 $2$ 类点的步数是 $\lceil\frac{j-i}{k}\rceil$（每次只能换 $k$，所以现需要这么多步）。

对于 $0\le a,b\le 1,a\ne b$ 的 $a,b$，假设当前有 $x$ 个 $a$ 类点没有匹配，遇到了一个 $b$ 类点。如果不考虑向上取整那选哪一个 $a$ 类点答案都一样，因为之后（包括当前）的 $x$ 个 $b$ 类点都会和 $a$ 匹配，顺序和答案无关，答案是这些 $b$ 的下标和减去 $a$ 的下标和。而且同时此时不选取前面的 $a$ 类点一定不优，因为会多算两次这个点和后面一个 $a$ 类点之间的距离。

由于有向上取整，我们尽量选取这些 $a$ 中差是 $k$ 倍数的，如果没有的话选择的余数最大的，因为我们希望浪费的步数尽量小。

为什么加入向上取整之后不会影响一开始的策略？违反一开始的策略至少会多走 $2$，而这里的取整影响一定更少。

可以使用 `set` 维护这里的点。

时间复杂度 $O(n\log n)$。

---

## 作者：Istruggle (赞：0)

如果交换 $a_i$ 与 $a_j$ 那么贡献为 $\left \lceil \frac{j-i}{k} \right \rceil$，同时我们有一个结论：如果没有向上取整则 $i$ 与前面任意一个数交换都是最优的，可以理解为答案是 $\frac{1}{k} {\textstyle \sum_{i=1}^{n}} \left ( j-i \right ) [s_i\ne s_j] [t_j = s_i]$ , 这个数值一定是固定的。而有了向上取整后，多出来的贡献其实就是 $k\left \lceil \frac{j-i}{k} \right \rceil - j+i$ , 如果我们想让这个数小就需要在匹配 $i$ 时尽量让 $j-i$ 为 $k$ 的整倍数，因此当 $i$ 需要进行匹配时，就需要在待匹配的数里找到在模 $k$ 下与 $i$ 差最小的 $j$。这个过程可以用 set 维护。

---

## 作者：hnczy (赞：0)

这题有点性质题的意思了（刚好是我不擅长的）。

首先我们分析题意，它给我们两个 01 字符串，并给一个 $k$ 表示一步交换的最长距离，求最少步数。

我们经过分析可以知道对于一个点，移动到另一个点，所需的代价是 $\lceil\frac{\mid x-y\mid}{k} \rceil$ 这里的 $x,y$ 指的是两点的坐标。

假设 $y>x$  代价就是 $\lceil \frac{y-x}{k}\rceil $。

这里我们假设没有向上取整的符号，他们求和的值就是定值（就是第一个部分分的值），那对于每次选择的两个点，可以算出这次选择比不向上取整亏了多少。

有点难理解？假设 $\frac{y-x}{k} = \frac{1}{3},\lceil \frac{y-x}{k}\rceil=1$ 那我们就亏了 $\frac{2}{3}$ 步，我们就是要求这个亏的步数的最小值。

容易知道 $(y-x)\bmod k$ 如果越大，亏的最小，当然相等的时候就不亏了。

即 $((y\bmod k) -(x\bmod k ))\bmod k$ 越大越好，那么假设 $y$ 已知，那么我们应该选 $x\bmod k$ 中大于 $y\bmod k$ 的最大的，反之取一个最小的即可。

代码和其他的题解没什么差别，这里就不放了。

---

## 作者：123456xwd (赞：0)

题意：`01` 字符串 $s,t$，每次可以交换距离 $\left|i-j\right|\le k$ 的两个字符，问把 $s$ 操作成为 $t$ 的最小步数。

考虑一下，我们若想要交换两个数 $i<j$，在不考虑其他点的情况下，我们显然需要 $\lceil\frac{j-i}{k}\rceil$ 步，实际上若想要保持其他点不变，操作次数也是 $\lceil\frac{j-i}{k}\rceil$，证明如下：

1. 若 $j-i\le k$，显然。
2. 若 $j-i>k$，先把我们不考虑其他点的交换 $i,j$ 时候，经过的点拿出来（包括其本身），应该是有 $\lceil\frac{j-i}{k}\rceil+1$ 个，那么相邻两个数之间可以交换，考虑他们一定是形如 `111000111000111000` 的，我们可以将其划分为若干个形如 `10001110` 的子问题 1 和两端的形如 `1110` 的子问题 2，分别想让其变为 `00001111` 和 `0111` 的样子。对于子问题 1，先操作最左边的 `1`，变为 `00011110`，再操作最右边的 `0`，变为 `00001111`；对于子问题 2，直接移动唯一的 `0` 即可，这样子每两个相邻的数都要交换一次，就是 $\lceil\frac{j-i}{k}\rceil$ 的。

那么我们从左往右扫描两个数组，遇到了 $s_i\neq t_i$ 的时候考虑同前面满足 $s_i\neq s_j$ 且 $ s_j\neq t_j$ 的点交换。

但是具体交换哪一个点呢？我们考虑我们交换 $i>j$ 造成的浪费（即可以利用但没有跳到的部分）为 $\lceil\frac{i-j}{k}\rceil k-(i-j)$，那么设 $j\equiv i+x\pmod k$，我们希望这个 $x$ 越小越好。

那么考虑用 `set` 维护一下 $i\bmod k$，然后每次在上面二分即可。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=1e6+5;
int n,k;ll ans;
char s[N],t[N];
set<pii> S[2];
void calc(ll x){
    ans+=x/k+(x%k!=0);
}
int main(){
    scanf("%d%d%s%s",&n,&k,s+1,t+1);
    for(int i=1;i<=n;i++){
        if(s[i]!=t[i]){
            int op=s[i]-'0';
            if(S[!op].empty()) S[op].insert(m_p(i%k,i));
            else{
                auto it=S[!op].lower_bound(m_p(i%k,0));
                if(it==S[!op].end())it=S[!op].begin();
                calc(i-(*it).se);S[!op].erase(it);
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

简要题意：给定两个 `01` 字符串 $a,b$，每次可以选择下标 $i,j$，其中 $|i-j|\le k$，交换 $a[i],a[j]$，求从 $a$ 变成 $b$ 的最小步数。

如果 $a[i]=b[i]$，直接跳过。否则有两种情况：$a[i]=0, b[i]=1$ 或 $a[i]=1, b[i]=0$。

如果有 $i,j$ 满足 $a[i]=0, b[i]=1, a[j]=1, b[j]=0$，则交换 $i,j$。这样的 $i,j$ 分别放在二分图的两边，构造出了二分图模型。考虑如何加速二分图匹配。

交换下标 $i,j(i<j)$ 的代价是 $\lceil \frac{j-i}{k} \rceil$，不考虑向上取整，那么最小的 $i$ 匹配最小的 $j$，次小的 $i$ 匹配次小的 $j$，以此类推，一定是最优策略。

再考虑有向上取整怎么办。一个显然的贪心策略是，使“浪费”尽量少，也就是说 $j\equiv i$ 是最优的，$j\equiv i+1$ 次优，等等。

考虑使用两个 `set` 维护二分图的两边，使用二分查找寻找最不“浪费”的匹配点。

```cpp
// Title:  Cowreography
// Source: USACO24OPEN Gold
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=1000010;
using namespace std;

int n, k, a[N], b[N]; ll res;
set<pair<int, int>> S[2];
int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	scanf("%d%d", &n, &k);
	rep(i, 1, n) scanf("%1d", a+i);
	rep(i, 1, n) scanf("%1d", b+i);
	rep(i, 1, n) if(a[i]!=b[i])
	{
		auto &S1=S[a[i]], &S2=S[b[i]];
		if(S1.empty())
		{
			S2.insert({i%k, i}); continue;
		}
		auto it=S1.lower_bound({i%k, 0});
		if(it==S1.end()) it=S1.begin();
		int j=it->second;
		res+=(i-j+k-1)/k; S1.erase(it);
	}
	printf("%lld", res);
	
	return 0;
}
```

---

