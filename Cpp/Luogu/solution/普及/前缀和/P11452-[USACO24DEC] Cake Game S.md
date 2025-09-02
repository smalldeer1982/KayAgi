# [USACO24DEC] Cake Game S

## 题目描述

Bessie 和 Elsie 发现了一行 $N$ 个蛋糕（$2≤N≤5⋅10^5$
，$N$ 为偶数），大小依次为 $a_1,a_2,\cdots,a_N$（$1≤a_i≤10^9$）。

两头奶牛都想吃到尽可能多的蛋糕。但是，作为非常文明的奶牛，她们决定玩一个游戏来分割蛋糕！游戏在两头奶牛之间轮流进行回合。每个回合进行以下两者之一：

1. Bessie 选择两个相邻的蛋糕并将它们堆叠起来，制造大小为两者大小之和的一个新蛋糕。
2. Elsie 选择最左边或最右边的蛋糕藏起来。

当只剩下一个蛋糕时，Bessie 吃掉它，而 Elsie 吃掉她藏起来的所有蛋糕。如果两头奶牛都采取最优策略以最大化她们吃到的蛋糕量，并且 Bessie 先进行回合，那么每头奶牛将会吃到多少蛋糕？

## 说明/提示

### 样例解释

对于第一个测试用例，在最优策略下，

Bessie 将堆叠中间两个蛋糕。现在蛋糕的大小为 $[40,50,10]$。

Elsie 将吃掉最左边的蛋糕。现在剩余的蛋糕的大小为 $[50,10]$。

Bessie 堆叠剩余的两个蛋糕。

Bessie 将吃到 $30+20+10=60$ 的蛋糕，而 Elsie 将吃到 $40$ 的蛋糕。

第二个测试用例是第一个测试用例反转的情况，因此答案相同。

### 测试点性质

- 测试点 1：样例。
- 测试点 2：所有 $a_i$ 相等。
- 测试点 3：$N≤10$。
- 测试点 4-7：$N≤5000$。
- 测试点 8-11：没有额外限制。

## 样例 #1

### 输入

```
2
4
40 30 20 10
4
10 20 30 40```

### 输出

```
60 40
60 40```

# 题解

## 作者：orpg (赞：8)

## 思路
不难发现，其实 Bessie 是没有选择的空间的，她只能合并最中间的两个蛋糕，不然的话 Elsie 就可以把 Bessie 合成的蛋糕藏起来。


---


举个例子。

如果有以下的蛋糕 ：

$[80,40,50,10,70,20]$。

Bessie 如果不合成中间两个蛋糕而选择合成 $[40,50]$。

第一步后：$[80,90,10,70,20]$。

对于 Elsie 最优选择是把 $80$ 藏起来。

第二步后：$[90,10,70,20]$。 

所以不管 Bessie 之后怎么合 Elsie 都可以轻松的取走 Bessie 之前合成的东西。


---


所以，实际上整个游戏实际上是 Elsie 的主动权。整个题目就被简化成求 Elsie 的最大值。

在这之前我们先看一下两个人各能取多少个蛋糕。观察可得 Bessie 会在一开始拿走两个蛋糕，随后跟 Elsie 一样，一次取一个（因为 Bessie 只能合成最中间的两个）。所以不难发现 Bessie 一次可以取 $\frac{N}{2}+1$ 个，而 Elsie 一次可以取 $\frac{N}{2}-1$ 个（题目保证 $N$ 为偶数）。

对于 Elsie 不难发现，其实它是在不停的取左边或者右边。我们把该数列首尾拼接，则 Elsie 可以取到的蛋糕就是一个滑动的区间。

![](https://cdn.luogu.com.cn/upload/image_hosting/bjxetc4q.png)

由上面的推理，不难得出 Elsie 只能拿 $\frac{N}{2}-1$ 个，在这里也就是 2 个，又因为 Elsie 只能从两边开始拿，所以它能拿的区间就是上图中的三个区间，最大值就显而易见了。

## 代码实现
我们可以把输入的数组重新存在原数组后面（以达到连接首尾的效果），然后对该数组求一个前缀和，这样可以快速的求出 Elsie 的最大值。然后把总其与总数相减，就是 Bessie 的答案了。
## code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e6+5;
int t,n;
int a[maxn];
ll sum[maxn];
ll all=0;
ll ans=0; 
void init(){
	memset(sum,0,sizeof sum);
	ans=0;
	all=0;
}
int main(){
	cin>>t;
	while(t--){
		init();
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],all+=a[i],a[i+n]=a[i];
		int bessie=(n/2)+1,elsie=(n/2)-1;
		for(int i=(n/2)+2;i<=(3*n/2)-1;i++) sum[i]=sum[i-1]+a[i];
		for(int i=n;i<=(3*n/2)-1;i++){
			ans=max(ans,sum[i]-sum[i-elsie]);
		}
		cout<<all-ans<<" "<<ans<<'\n';
	}
}
```

---

## 作者：封禁用户 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P11452)

又被银组硬控了啊啊啊。又是赛后做出来的。

---

一道博弈题，不难发现每个人的选择是受之前的选择的控制的，所以这题的核心是哪些蛋糕容易被哪一头牛控制。容易看出越靠边上的蛋糕越容易被 Elsie 控制，所以 Bessie 所合并的蛋糕就尽量不能让 Elsie 吃掉，所以 Elsie 最终会吃掉 $\frac{n}{2}-1$ 个蛋糕，Bessie 则会吃掉剩下的 $\frac{n}{2}+1$ 个。最后得出结论 Elsie 会吃掉两端上最大的 $\frac{n}{2}-1$ 个蛋糕，可以用前缀和解决。

备注：前缀和数组不用多测清空，因为这次的前缀和数组的值会覆盖上一次的值。

```cpp
#include <iostream>
using namespace std;

using LL = long long;

const int N = 5e5 + 5;

LL s[N];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            LL x;
            cin >> x;
            s[i] = s[i - 1] + x;
        }
        LL ans = 0;
        for (int i = 0; i <= n / 2 - 1; i++)
        {
            int pos = n / 2 - i - 1;
            ans = max(ans, s[i] + s[n] - s[n - pos]);
        }
        cout << s[n] - ans << " " << ans << "\n";
    }
    return 0;
}
```

---

## 作者：ZHR100102 (赞：5)

# 观察

本题有三个重要的结论，我们依次进行观察。

不难发现，第二个牛一定会拿 $\frac{n}{2}-1$ 个蛋糕走。同时**它拿走的蛋糕一定是左边一段、右边一段**。如果它要使自己的分数最大化，那么显然就是要将左边和右边的和最大化。

那么第一头牛有啥用呢，其实根本没用。一个很显然的结论，**第一头牛不可能让第二头牛的分数更小，只能让它大于等于原来的分数**。证明也很显然，因为这些蛋糕的分数都是正数，合并任何两个蛋糕只会徒增这两个蛋糕的分数，让第二头牛吃到更多的分。

那么第一头牛能不能不让第二头牛多吃任何蛋糕呢？因为第二头牛最多吃 $\frac{n}{2}-1$ 个，所以**在博弈过程中我们一定可以取一个中点，然后在中点附近合并，防止它吃到合并后的蛋糕**。这个可以自行画图理解。

# 实现

枚举前一段取了多少，前缀和后缀和计算一下取个最大值就好了。

时间复杂度 $O(n)$。

赛时忘记取蛋糕有后效性，直接优先队列取两边最大值了。我纯唐。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
int n;
ll a[500005],pre[500005],suf[500005],ans=0;
void solve()
{
    ans=0;
    memset(pre,0,sizeof(pre));
    memset(suf,0,sizeof(suf));
    memset(a,0,sizeof(a));
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)pre[i]=pre[i-1]+a[i];
    for(int i=n;i>=1;i--)suf[i]=suf[i+1]+a[i];
    for(int i=0;i<=n/2-1;i++)
    {
        int l=i,r=n-(n/2-1-i)+1;
        ans=max(ans,pre[l]+suf[r]);
    }
    cout<<pre[n]-ans<<" "<<ans<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Mr_Az (赞：5)

# P11452 [USACO24DEC] Cake Game S

### Algorithm:

贪心。

### Solution:

看上去十分困难的博弈题，实际上是唐氏题。

我们自行模拟会发现，Bessie 最后的蛋糕是一个长度为 $\frac{n}{2}+1$ 区间，但选择这个区间的主动权在 Elsie。也就是说，Bessie 合并的蛋糕是由 Elsie 决定的，所以我们只需要枚举 Elsie 在左边选择了多少个蛋糕并且价值取 max。

### Code:

```cpp
int T,n,ans1,ans2;
int a[N],sum[N];
inline int s(int l,int r){return sum[r]-sum[l-1];}
inline void solve(){
	read(n);
	ans1=0;
	for(rint i=1;i<=n;i++) read(a[i]),sum[i]=sum[i-1]+a[i];
	for(rint i=0;i<=n/2-1;i++) ans1=max(ans1,s(1,i)+s(n/2+2+i,n));
	printf("%lld %lld\n",s(1,n)-ans1,ans1);
}
signed main(){
	read(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：chenxi2009 (赞：3)

## 思路
~~13 行代码挑战最短。~~\
Elsie 可以吃到 $\left \lfloor \frac{n-1}{2} \right \rfloor $ 个蛋糕。Bessie 肯定不会帮 Elsie 合并蛋糕，Elsie 也自然知道这一点，讨论一下会发现它们俩会达成一种“协议”，就是 Elsie 会从两边取 $\left \lfloor \frac{n-1}{2} \right \rfloor $ 个蛋糕使得这些蛋糕大小之和最大，剩下的蛋糕归 Bessie 所有。

**为什么这样是对的？**

Bessie 从正中开始合并。这样 Elsie 才绝无可能夺取 Bessie 的合并成果。而游戏每经过一轮，Bessie 又可以合并最中间的两个蛋糕，直到最后。每一轮开始前 Elsie 都拿不到当前蛋糕数一半的蛋糕，也就不能夺到 Bessie 合并出来的蛋糕。

看上去这个游戏的主导权在 Bessie？其实不然。看似 Bessie 是无所顾忌的实际上它只能通过合并中间来规避 Elsie，而中间位置的改变实际上取决于 Elsie 拿取哪一边的蛋糕。

所以这个游戏的主导权完全在 Elsie，枚举它在左边取多少个蛋糕（令其为 $x$），在右边就拿 $\left \lfloor \frac{n-1}{2} \right \rfloor-x$ 个蛋糕，取最大值就是 Elsie 最终采用的方案。时间复杂度 $O(\sum N)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,a[500001],s[500001],ans;
int main(){
	scanf("%lld",&T);
	while(T --){
		scanf("%lld",&n),ans = 0ll;
		for(int i = 1;i <= n;i ++) scanf("%lld",&a[i]),s[i] = s[i - 1] + a[i];//前缀和
		for(int i = 0;i <= n - 1 >> 1;i ++) ans = max(ans,s[i] + s[n] - s[n - (n - 1 >> 1) + i]);//枚举 Elsie 在左边取多少个蛋糕
		printf("%lld %lld\n",s[n] - ans,ans);
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：2)

## 思路分析

给出结论：Bessie 只能吃到最小的连续的 $\frac{n}{2}+1$ 的蛋糕。

其实很显然，不管 Bessie 从哪里开始叠蛋糕，Elsie 都可以逼着她选择最劣的那一堆。而如果 Bessie 从中间开始叠的话，那么 Elsie 无论如何都无法保证吃到 Bessie 叠的蛋糕。因此，最小的连续的 $\frac{n}{2}+1$ 的蛋糕是对于双方而言的最优解。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, a[500005], ans;
signed main() {
	ios::sync_with_stdio(0);
	for (cin >> t; t; t--) {
		cin >> n; ans = 1e18;
		for (int i = 1; i <= n; ++i)
			cin >> a[i], a[i] += a[i - 1];
		int ln = n / 2;
		for (int i = 1; i + ln <= n; ++i)
			ans = min(ans, a[i + ln] - a[i - 1]);
		cout << ans << " " << a[n] - ans << endl;
	}
}
```

---

## 作者：Statax (赞：2)

## 前言

由于题解占不到优势，所以我会把所有部分分讲清楚 qwq。

## 分析

（以下分析 B 代表 Bessie，E 代表 Elsie。）

### 数据点 1

这个还用讲吗…

### 数据点 2

由于 $a_i$ 全部相等，那么此时我们的侧重点就不是吃了哪些蛋糕，而是 B 和 E 最多可吃多少个蛋糕。

很明显，B 先手，最多吃 $\frac{n}{2} + 1$ 个，E 后手，会吃 $\frac{n}{2} - 1$ 个，最终答案便迎刃而解了。

### 数据点 3

暴搜即可，不过注意答案是 E 为第一关键字取最大值，再关注 B 的最大值。

### 数据点 4 \~ 7

这是就要真正开始思考了：

其实要先理清楚，B 将蛋糕合并利益是为了谁？肯定是为了自己最后吃到的更多。为什么？因为 $a_i > 0$。

而且总共会有 $\frac{n}{2} + 1$ 回合。

所以说 B 第一步只能合并 $a_{\frac{n}{2}}$ 和 $a_{\frac{n}{2} + 1}$，才能保证自己合并的不会被 E 吃掉。

此时，游戏的主导权就交到了 E 手中，E 藏哪一边的蛋糕，那么 B 就要合并当前扩展范围的反方向的下一个数。比如如果当前 E 藏最左边的，那 B 就要合并右边的，目的同样是保证自己合并的蛋糕不会被 E 吃掉。

所以现在要求的就是 E 会怎么吃蛋糕。

对于此数据，令 $f_{i,j}$ 表示前 $i$ 次藏蛋糕，有 $j$ 次藏左边的的最大收益。

那么转移方程就很好写了，这里就不过多赘述了，总之时间复杂度 $O(T \cdot N^2)$。

### 正解

而其实，由于我们分析出 B 最优策略就是不被 E 所干扰，所以其实 B 的最大值和 E 的最大值的和就是 $\sum a$，所以前后缀和算 E 的答案自然就算出 B 的答案了，时间复杂度 $O(\sum N)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) x & (-x)

using namespace std;
constexpr int MAXN = 5e5 + 5;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;

int t;
int n, a[MAXN], s[MAXN];

signed main()
{
    cin >> t;
    for (; t; --t) {
        cin >> n;
        memset(a, 0, sizeof a);
        memset(s, 0, sizeof s);
        for (int i = 1; i <= n; ++i)
            cin >> a[i], s[i] = s[i - 1] + a[i];
        int ans = 0;
        for (int i = 0; i < (n >> 1); ++i)
            ans = max(ans, s[i] + s[n] - s[(n >> 1) + 1 + i]);
        cout << s[n] - ans << " " << ans << endl;
    }
    return 0;
}

```

---

## 作者：船酱魔王 (赞：1)

## 题意回顾

长度为 $ n $ 的（$ n $ 为偶数）双端队列，先手和后手依次执行操作，若一方操作前只剩下一个元素时先手得分为这个元素的值：

* 先手的操作为：选择一个不是最靠左的元素，将这个元素删除并将它左面的元素增加它的数值。
* 后手的操作为：`pop_front` 或 `pop_back`。

双方的目标为（先手）最大化自己的得分或（后手）最小化对方的得分，请求出双方按照最优策略后的先手的得分。

## 知识点及评析

* 【3】贪心法

考察基础的最优化策略分析及数组前缀和的使用，是一道考察分析能力和基础算法的好题。

## 分析

> 观察 1：如果一个元素经过先手的合并，但是又被后手删除，那么不进行这次合并操作一定更优。

论证：先手的合并操作相当于加快了后手删除的速度。

> 观察 2：先手获得的得分等价于区间 $ [l,r] $ 的和 $ \sum_{i=l}^ra_i $，且区间满足 $ r-l+1=\frac{n}{2}+1 $。

论证：先手会尽量使得自己的操作元素不被后手删除，假设先手一开始操作的元素的原始编号为 $ x $，那么按照观察 1 的结论，存在事实：先手的合并本质上相当于将 $ x $ 与周围的元素合并（因为合并尽可能靠里的元素显然更优）。而 $ x $ 周围两边剩下的元素个数当 $ x $ 取 $ \frac{n}{2} $ 或 $ \frac{n}{2}+1 $ 时，最小值会不小于 $ \frac{n}{2}-1 $，而先手的操作就是当后手让一边少一个元素后，让另一边减少一个元素，此时最小值一定每回合最多减少 $ 1 $，显然后手无法吞噬掉 $ x $ 的合并范围。

> 观察 3：后手可以任意塑造 $ [l,r] $ 的范围。

论证：区间 $ [l,r] $ 有 $ \frac{n}{2}-1 $ 个元素在外面，而正好是后手的操作数。

> 最终结论：先手的得分为 $ \min_{1 \le l \le r \le n,r-l+1=\frac{n}{2}+1}\sum_{i=l}^ra_i $。

实现：利用前缀和暴力打擂台求出最小值即可。

## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5;
int T, n;
int a[N];
long long sum[N];
inline void read(int &x) {
	x = 0;
	char ch = '#';
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
}
inline void write(long long x) {
	if(x == 0) {
		putchar('0');
		return;
	} 
	char wri[25];
	int lt = 0;
	while(x) {
		wri[++lt] = x % 10;
		x /= 10;
	}
	while(lt) {
		putchar(wri[lt--] + '0');
	}
}
int main() {
	read(T);
	for(int ti = 1; ti <= T; ti++) {
		read(n);
		for(int i = 1; i <= n; i++) read(a[i]), sum[i] = sum[i - 1] + a[i];
		long long ans = (long long)1e18 + 5;
		for(int i = 1; i + n / 2 <= n; i++) {
			ans = min(ans, sum[i + n / 2] - sum[i - 1]);
		}
		write(ans);
		printf(" ");
		write(sum[n] - ans);
		puts("");
	}
	return 0;
}
```

---

## 作者：wzhm54nr (赞：1)

更正：发现一些笔误，现更正。
~~赛场上唯一做出来的题。。。~~
# 思路
观察可知，**Bessie 一定可以吃掉 $\frac{n}{2}+1$ 个蛋糕，Elsie 则可以吃掉 $\frac{n}{2}-1$ 个蛋糕**。然后，**Bessie 无法让 Elsie 获得更劣的结果**，因为合并蛋糕增加蛋糕大小，而不能改变蛋糕对于左右两端点的相对位置。但是，**Bessie 也一定有策略使得 Elsie 不因为自己的行为而获得更优的解**，因为每一轮都有两个蛋糕是接下来 Elsie 不可能吃到的，合并之即可。所以，Bessie 就是个摆设，只需考虑 Elsie 即可。同时，因为 Elsie 只能吃掉两边的蛋糕，所以 Elsie 的策略被转化为**寻找一个区间，使区间内的数和最小（没吃到的最少），吃掉剩下的**。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
int n,a[N];
ll sum[N];
int main(){
int T;scanf("%d",&T);
while(T--){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)  sum[i]=sum[i-1]+a[i];
	ll ans=1e18;
	for(int r=n/2+1;r<=n;r++)  ans=min(ans,sum[r]-sum[r-n/2-1]);
	printf("%lld %lld\n",ans,sum[n]-ans);
}
	return 0;
}
```

---

## 作者：违规用户名720023 (赞：1)

# P11452 [USACO24DEC] Cake Game S  (蛋糕游戏)

[原题](https://www.luogu.com.cn/problem/P11452)

## 题目描述

原题已经很清晰了，不再加以描述。

## 部分分

第一个到第三个点是好做的。第二个点输出 $k \times n \div 2$ 和 $k \times n \div 2 - 1$ 即可。第三个点暴力枚举每个点被谁吃掉，最后判断可行性然后计算即可。

第四个到第七个点，不使用前缀和优化分析部分的算法即可。

## 分析

$n$ 是偶数。Bessie 和 Elsie 每次都会使得蛋糕总数减少 $1$ 个。而最后只剩下一个蛋糕。说明操作了 $n - 1$ 次。因为 Bessie 先操作，而且 $n - 1$ 是奇数，所以可以得出 Bessie 操作了 $n \div 2$ 次，Elsie 操作了 $n \div 2 - 1$ 次。

这时我们发现一个性质：Elsie 每次只能吃到两头的。我们就知道 Elsie 一共可以吃到左边 $k$ 个和右边 $n \div 2 - 1 - k$ 个（为什么是这样呢？因为 Bessie 如果把合成完成的大蛋糕给她吃掉，那么她仍然能够吃到先前预备吃的所有蛋糕，最后结果肯定更差）。

这样就很清楚了。Bessie 吃掉中间连续 $n \div 2 + 1$ 段蛋糕中总数最小的，Elsie 吃掉剩下的（为什么是这样呢？稍加思考就可以发现 Bessie 不能阻止 Elsie 吃掉她要吃的蛋糕）。

使用单调队列或者前缀和优化，复杂度 $O(nT)$。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <cstdio>
#define int __int128
#define rd() read128()
#define pr(a) print128(a)
#define pc(b) putchar(b)
#define pel(c) pr(c), pc('\n')
#define psp(d) pr(d), pc(' ')
using namespace std;

int read128()
{
	int ttpttp = 0, flgflg = 1;
	char chrchr = getchar();
	if(chrchr == '-') flgflg = -1;
	while((chrchr < '0' || chrchr > '9') && chrchr != '-') chrchr = getchar();
	if(chrchr == '-') flgflg = -1, chrchr = getchar();
	while(chrchr >= '0' && chrchr <= '9') ttpttp = ttpttp * 10 + chrchr - '0', chrchr = getchar();
	return ttpttp * flgflg;
}

void print128(int ttpttp)
{
	char char_inserted_list[38];
	if(ttpttp < 0) putchar('-'), ttpttp *= -1;
	int iiiiii = 0;
	while(ttpttp > 0)
	{
		char_inserted_list[++iiiiii] = (char)(ttpttp % 10 + '0');
		ttpttp /= 10;
	}
    if(iiiiii == 0) putchar('0');
    else
    {
    	for(int i = iiiiii; i >= 1; i--) putchar(char_inserted_list[i]);
	}
}//快读
int a[500010], s[500010];

signed main()
{
	int t = rd();
	while(t--)
	{
		int n = rd();// n - 1 times  bessie n / 2 --> bessie n / 2 + 1 cakes
		for(int i = 1; i <= n; i++) a[i] = rd(), s[i] = s[i - 1] + a[i];
		int minn = 1e18;
		for(int i = 1; i <= n / 2; i++)
		{
			minn = min(minn, s[i + n / 2] - s[i - 1]);
		}
		psp(minn);
		pel(s[n] - minn);
	}
	return 0;
}

---

## 作者：Modulus998244353 (赞：1)

**解题思路**

---

不难发现，Elsie 选择的蛋糕为 $[1,i]$ 和 $[n,n+i-\frac{n-1} 2]$ 这两个区间。（不考虑 Bessie 的操作）

则如果 Bessie 在这两个区间内合并，则此操作只会让 Elsie 最终吃掉的蛋糕更多，因为合并一下等价于 Elsie 两次操作。

则 Bessie 肯定会对 $[i+1,n+i-\frac{n-1} 2]$ 这个区间内进行合并。而 Elsie 肯定会选择 $\sum_{k=1}^ia_k\,+\,\sum_{k=n+i-(n-1)/2}^n a_k$ 最大的 $i$。

用个前、后缀和维护一下就可以了。

**代码**

---

```c++
int n;
scanf("%d",&n);
ll tot=0;
for(int i=1;i<=n;i++) scanf("%d",&a[i]),tot+=a[i];
for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
for(int i=n;i>=1;i--) suf[i]=suf[i+1]+a[i];
ll E=-1,Es=(n-1)/2;
for(int i=0;i<=Es;i++) E=max(E,pre[i]+suf[n-(Es-i)+1]);
ll B=tot-E;
printf("%lld %lld\n",B,E);
```

---

## 作者：masonxiong (赞：1)

# 题目分析

首先我们知道，E 最终会吃到左右加起来共 $\frac n 2 - 1$ 个蛋糕。那么中间的那两个蛋糕她无论怎么吃都是吃不到的。

我们考虑若 B 合并了 E 进食范围内的两个蛋糕会发生什么。这个时候 E 就会不顾一切地往那个方向吃，直到下一步就可以吃掉这个蛋糕为止。

因为她最终肯定能吃到这个蛋糕，而且所有的蛋糕最后肯定会合并成一个，当这一个大蛋糕即将合成时，她直接将这一整个全部吃掉，让 B 亏的渣都不剩。

那么 B 的策略就是：一直合并 B 进食范围以外的蛋糕。

既然 E 吃不到 B 的蛋糕，那她的策略就是：吃左端右端最大的连续 $\frac n 2 - 1$ 个蛋糕。

然后我们预处理前缀和，枚举端点算出 E 的最大答案，然后用总和减去这个就获得了 B 的答案。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long integer;
const int Maxn = 5e5 + 5;
int t, n;
int A[Maxn];
integer pSum[Maxn], sSum[Maxn];

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	for (cin >> t; t--; ) {
		cin >> n;
		integer suma = 0, sume = 0;
		sSum[n + 1] = 0;
		for (int i = 1; i <= n; i++) {
			cin >> A[i];
			suma += A[i];
		}
		for (int i = 1; i <= n; i++) {
			pSum[i] = pSum[i - 1] + A[i];
			sSum[n - i + 1] = sSum[n - i + 2] + A[n - i + 1];
		}
		for (int i = 0, cnt = (n >> 1) - 1; i <= cnt; i++)
			sume = max(sume, pSum[i] + sSum[n - cnt + i + 1]);
		cout << suma - sume << ' ' << sume << '\n';
	}
	return 0;
}
```

---

## 作者：greater_than (赞：0)

### 思路
我们可以知道 Bessie 只能合成中间的，不然会被抢走的。所以 Elsie 取左边，那么 Bessie 就只能往右边合成，所以主动权在 Elsie 手里。

经观察发现 Elsie 最终取的是左边一段 $ 1 \sim k $ 和右边取一段 $ n-p \sim n $，由于 Elsie 会选最优情况，所以枚举个数取 $ \max $ 即可。还有 Elsie 可以取 $ \frac{n-2}{2} $ 个数，用前缀和和后缀和存好，然后枚举即可。

**记住：多测不清空，亲人两行泪。**
### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,a[500005],num=0,b[500005],c[500005];
signed main(){
    cin>>T;
    while(T--){
        num=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            b[i]=b[i-1]+a[i];
            num+=a[i];
        }
        c[n+1]=0;
        for(int i=n;i>=1;i--)c[i]=c[i+1]+a[i];
        int g=n/2-1,maxn=0;
        for(register int i=0;i<=g;i=-~i){
            int kk=b[i]+c[n-(g-i)+1];
            // cout<<i<<" "<<kk<<'\n';
            maxn=max(maxn,kk);
        }
        cout<<num-maxn<<" "<<maxn<<endl;
    }
}

```

---

## 作者：linjunye (赞：0)

### 思路

首先，我们要注意到这一句话：

**Elsie 选择最左边或最右边的蛋糕藏起来。**

那么，似乎 Bessie 堆叠的蛋糕只能是一段连续区间，证明如下：

反证法，假设 Bessie 堆叠的蛋糕不是一段连续区间，那么两个区间之间的那些“孤立点”就只能为 Elsie 所有，但 Elsie **只能选择最左边或最右边的蛋糕藏起来**，与假设矛盾，所以 Bessie 堆叠的蛋糕只能是一段连续区间，证毕。

然后注意道**两头奶牛都像最大化吃到的蛋糕量**，所以 Elsie 会不断使 Bessie 做出最劣的选择以达到自己利益最大化。

然后手玩几组数据，发现 Bessie 吃 $\lfloor\frac{n}{2}\rfloor+1$ 个蛋糕，Elsie 吃 $\lfloor\frac{n}{2}\rfloor-1$ 个蛋糕，所以问题变成：

找到一个长度为 $\lfloor\frac{n}{2}\rfloor+1$ 且总和最小的区间。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500010;
int n,a[N];
int sum[N];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	int len=n/2+1;
	int mx=1e18;
	for(int i=len;i<=n;i++)mx=min(mx,sum[i]-sum[i-len]);
	cout<<mx<<" "<<sum[n]-mx<<"\n";
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
//	T=1;
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：hyk2019 (赞：0)

容易发现，Bessie 吃掉的蛋糕一定是一个连续区间里的蛋糕。因为新的蛋糕是由相邻两个蛋糕合并而来的，一定是一段连续的区间；Elsie 藏起来的蛋糕只能是最左侧的连续一段和最右侧的连续一段，剩下的部分就是连续的一段。

Bessie 为了不让 Elsie 吃到更多蛋糕，一定会选择最小化 Elsie 得到的蛋糕数，而 Elsie 一共会进行 $\frac N2-1$ 次操作，因此至少会得到 $\frac N2-1$ 个蛋糕。那么 Bessie 最多会得到 $\frac N2+1$ 个蛋糕。

由于 Elsie 先藏蛋糕，所以认为 Elsie 占据主动权，可以选择吃掉哪些蛋糕，因此在双方都采取最优策略的情况下，Elsie 能够最大化他吃掉的蛋糕的总和 $E_{\max}$，Bessie 吃掉的蛋糕的总和是所有蛋糕的总和减去 $E_{\max}$。

可以转化一下，改成统计每一个长度为 $\frac N2+1$ 的区间内蛋糕的总和的最小值，这样剩下的 $\frac N2-1$ 个蛋糕的总和就被最大化了。

```py
T = int(input())
for i in range(T):
  N = int(input())
  a = list(map(int, input().split()))
  n = N // 2 + 1
  p = [a[0]]
  for j in range(1, N):
    p += [p[-1] + a[j]]
  st = min(p[x + n - 1] - (0 if x == 0 else p[x - 1]) for x in range(N - n + 1))
  print(st, p[-1] - st)
```

---

## 作者：Your_Name (赞：0)

## 题解
我们发现，当后手（即藏蛋糕的人）想要哪个蛋糕时一定可以取到，所以我们直接看他取哪 $n\div 2-1$ 个即可。

但他也不是随便选，而是只能选序列两端连续的两端或一段，所以我们直接把数组复制一遍然后前缀和算哪段最大即可。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL T, n, a[N], ans, sum;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T --){
		cin >> n;
		ans = sum = 0;
		for(int i = 1; i <= n; i ++){
			cin >> a[i];
			sum += a[i];
			a[i + n] = a[i];
		}
		for(int i = 1; i <= n * 2; i ++){
			a[i] += a[i - 1];
		}
		int len = n / 2 - 1;
		for(int i = n ; i <= n + len; i ++){//注意不能取中间
			ans = max(ans, a[i] - a[i - len]);
		}
		cout << sum - ans << ' ' << ans << '\n';
	}
	return 0;
}
```
 _完结撒花。_

---

## 作者：Milky_Cat (赞：0)

显然两只奶牛每一轮都可以让蛋糕减少一块，手玩发现最后 Bessie 可以获得 $\dfrac{n}{2}+1$ 块，Elsie 吃到 $\dfrac{n}{2}-1$ 块，所以 Elsie 一定会采取最优策略，选两边最优的 $\dfrac{n}{2}-1$ 块，写一个前缀和一个后缀和处理即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, a[1000005], pre[1000005], suf[1000005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while (t--){
		cin >> n;
		int sum = 0;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
			sum += a[i];
		}
		for (int i = 1; i <= n; i++)
			pre[i] = pre[i - 1] + a[i];
		for (int i = n; i >= 1; i--)
			suf[n - i + 1] = suf[n - i] + a[i];
		int ans = 0;
		for (int i = 0; i <= n / 2 - 1; i++)
			ans = max(ans, pre[i] + suf[n / 2 - 1 - i]);
		cout << sum - ans << " " << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

首先 Bessie 选择的一定是一个区间。

尽管 Bessie 先手，但是它的选择是受 Elsie 牵制的——一旦选择的不是可选区间的中间区间，那么 Elsie 一定可以吃到 Bessie 的蛋糕。

那么我们只要最大化 Elsie 的代价即可。答案即为 $\max\left\{\sum\limits_{i=1}^{\frac n2+1}a_i,\sum\limits_{i=\frac n2}^na_i,\max\limits_{p=1}^{\frac n2}\left\{\sum\limits_{i=1}^pa_i+\sum\limits_{i=\frac n2+p}^na_i\right\}\right\}$。

---

## 作者：_Jocularly_ (赞：0)

博弈题。首先观察题面，有一个显然的结论，就是藏起来的蛋糕一定是 $\frac{n}{2} - 1$ 个。因为如果假设我取走了 $x$ 个，每取走一个少一个，那么此时的数量为 $n - x$，此时第一个人也行动了 $x$ 次，每次合并两个变成一个，总数减少一个，那么加上第一种情况，此时的数量为 $n - 2x$。最后的时候剩了两个，因为合并一下变成一个就结束了，那么满足等式 $n - 2x = 2$，那么 $2x = n - 2$，得到 $x = \frac{n}{2} - 1$。

那么此时我们显然知道第二个人藏起来的蛋糕一定是从两边拿的，那么直接枚举从前面拿走的数量 $i$，此时在后面拿的就是 $\frac{n}{2} - i - 1$，当总和最大时为最优策略。因为要求区间和，考虑维护前缀和。单次询问复杂度线性，总复杂度为 $O(tn)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n;
int a[500005];
int sum[500005];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    //B合并i次就消失i-1个,那么每合并一次就会被E吃掉一个,也就是说n-2i=2,那么B合并了n/2-1个,即E吃了n/2-1个
    //E一定从两边吃,那么根据贪心我们直接选
    cin >> t;
    while(t --){
        cin >> n;
        int ans = 0;
        int need = n / 2 - 1;
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            cin >> a[i];
            sum[i] = sum[i-1] + a[i];
            //cout << sum[i] << " ";
        }
        for(int i=0;i<=need;i++){
            //cout << i << " " << need - i << endl;
            int cnt = 0;
            cnt += sum[i];
            cnt += sum[n] - sum[n-need+i];
            ans = max(ans,cnt);
        }
        cout << sum[n] - ans << " " << ans << endl;
    }
    return 0;
}
/*
1
4
40 30 20 10

60 40
*/
```

---

## 作者：complete_binary_tree (赞：0)

## 题目大意

两个人取 $N$（$N$ 是偶数）个蛋糕，先手可以把任意两个相邻蛋糕合并成一个，后手可以取前或后的一个蛋糕。只剩一个蛋糕时先手拿走。问最优策略下它们分别能拿到多少个蛋糕。

## 题解

发现这题答案只与后手有关。因为先手在任何时候都不能让自己合并后的蛋糕在左右两侧，否则辛辛苦苦合并的蛋糕全都功亏一篑，所以后手可以取前缀一段和后缀一段蛋糕，总数为 $\frac{N}{2}-1$。

所以弄一个前缀和和后缀和，然后暴力枚举前缀算答案即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,a[500005];
long long sum[500005];

int main() {
    ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 );
    for(cin>>t;t--;){
        cin>>n;
        long long ans=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            sum[i]=a[i]+sum[i-1];
            //cerr<<sum[i]<<' ';
        }
        for(int j=0;j<(n>>1);++j){
            ans=max(ans,sum[j]+sum[n]-sum[n-(n>>1)+j+1]);
        }
        cout<<sum[n]-ans<<' '<<ans<<'\n';
    }
    return 0;
}
```

---

