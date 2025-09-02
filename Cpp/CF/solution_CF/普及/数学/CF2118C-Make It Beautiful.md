# Make It Beautiful

## 题目描述

给定一个包含 $ n $ 个整数的数组 $ a $。我们定义一个数字 $ x $ 的**美丽值**为其二进制表示中 $ 1 $ 的个数。我们定义一个数组的美丽值为其所有数字美丽值的总和。

在一次操作中，你可以选择一个下标 $ i $（$ 1 \le i \le n $）并将 $ a_i $ 增加 $ 1 $。

在最多进行 $ k $ 次操作后，求数组可能达到的最大美丽值。

## 说明/提示

在第一个测试用例中，$ a = [0, 1, 7, 2, 4] $。

- 第一次操作选择 $ i = 1 $，新数组为 $ a = [1, 1, 7, 2, 4] $。
- 第二次操作选择 $ i = 4 $，新数组为 $ a = [1, 1, 7, 3, 4] $。

该数组的美丽值为 $ 1 + 1 + 3 + 2 + 1 = 8 $。另一个具有相同美丽值的有效解是 $ [0, 1, 7, 3, 5] $。在第三个测试用例中，$ a = [3] $。由于不要求必须使用恰好 $ k $ 次操作，最优解是不进行任何操作。

## 样例 #1

### 输入

```
5
5 2
0 1 7 2 4
5 3
0 1 7 2 4
1 1
3
3 0
2 0 3
1 100000000000
0```

### 输出

```
8
9
2
3
36```

# 题解

## 作者：DrDuck (赞：5)

首先只有把一个数二进制表示下某一位的 $0$ 补成 $1$ 才对答案有贡献。假设这一位是第 $i$ 位（钦定最低位是第 $0$ 位），那么要把这一位补成 $1$，$k$ 需要减掉 $2^i$。我们贪心地考虑，肯定是先让从低位向高位看，第一个有 $0$ 的位置最低的这个数进行操作才是更优的。根据这个建立一个优先队列，按照每个数最低位的 $0$ 的所在位子升序排序。

考场上看到要求每个数最低位的 $0$ 的所在位子，突然有了一个非常睿智的想法。这不就跟树状数组里的 $\operatorname{lowbit(x)}$ 非常像嘛！

但是 $\operatorname{lowbit(x)}$ 是求每个数最低位的 $1$ 所对应的值诶，怎么办？

~~把 $x$ 取反就可以了。~~
# CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 5e+3 + 3;
int T, n, k, ans;
int lowbit(int x)
{
    x = ~x;
    return x & -x;
}
struct node
{
    int w;
    friend bool operator < (const node &x, const node &y)
    {
        return lowbit(x.w) > lowbit(y.w);
    }
};
priority_queue<node> q;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--)
    {
        while (q.size())
        {
            q.pop();
        }
        cin >> n >> k;
        ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            ans += __popcount(x);
            q.push({x});
        }
        while (k)
        {
            int now = q.top().w;
            q.pop();
            int nd = lowbit(now);
            if (k < nd)
            {
                break;
            }
            k -= nd;
            ans++;
            now += nd;
            q.push({now});
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Swordmaker (赞：3)

# CF2118C Make It Beautiful

# 思路

不难发现，最终的答案由两部分组成：原先所有数字二进制中 $1$ 的个数之和，以及增加数字大小后增加的 $1$ 的个数。

考虑这样一个显而易见的贪心：对于每个数拆解为二进制，优先满足其低位上由 $0$ 变为 $1$ 的要求，再由低到高进行。

我们定义 $pos_i$ 表示在二进制下所有数中从低位算起第 $i$ 位为 $0$ 的数的数量，这样在统计答案时只要由贪心的原则依次从小到大遍历 $pos$ 数组直至剩下的 $k$ 不够增加即可。

并不需要用到目前所有题解里都需要用到的优先队列。

# code
```cpp
#include <bits/stdc++.h>
#define int long long
#define push_back(x) emplace_back(x)
#define pii pair<int,int>
namespace AyanamiRei
{
	inline int read()
	{
		int x=0,f=1;
		char c=getchar();
		while(c>'9'||c<'0')
		{
			if(c=='-') f=0;
			c=getchar();
		}
		while(c>='0'&&c<='9')
		{
			x=(x<<3)+(x<<1)+(c-'0');
			c=getchar();
		}
		return f?x:-x;
	}
}
namespace SoryuAsukaRangure
{
	inline void write(int x)
	{
		if(x<0) x=-x,putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
		return;
	}
}
namespace IkariYue
{
	inline void output(int x)
	{
		SoryuAsukaRangure::write(x);
		putchar('\n');
		return;
	}
}
namespace IkariShinji
{
	inline int max(int x,int y)
	{
		return x>y?x:y;
	}
}
namespace NagisaKaworu
{
	inline int min(int x,int y)
	{
		return x<y?x:y;
	}
}
namespace MariMakinamiIllustious
{
	inline double MAX(double x,double y)
	{
		return x>y?x:y;
	}
}
namespace ShikinamiAsukaRangure
{
	inline double MIN(double x,double y)
	{
		return x<y?x:y;
	}
}
using namespace std;
using namespace AyanamiRei;
using namespace SoryuAsukaRangure;
using namespace IkariYue;
using namespace IkariShinji;
using namespace NagisaKaworu;
using namespace MariMakinamiIllustious;
using namespace ShikinamiAsukaRangure;
constexpr int the_birthday_of_Asuka=20011204;
mt19937 Asuka(the_birthday_of_Asuka+time(0));
constexpr int N=5e3+5;
constexpr int M=1e2+5;
int t,n,k,ans=0;
int a[N],pos[M];//pos[i]表示从低到高第i位上为0的数有几个 
inline int popcount(int x)//一个数变为二进制后有多少的1 
{
	int res=0;
	while(x)
	{
		if(x&1) res++;
		x>>=1;
	}
	return res;
}
void solve(int x)//更新pos数组 
{
	for(int i=1;i<=70;i++)
	{
		int u=x&1;
		if(!u) pos[i]++;
		if(x>0) x>>=1;
		else x=0;
	} 
	return;
}
signed main()
{
	t=read();
	while(t--)
	{
		memset(pos,0,sizeof(pos));//多测不清空，__ __ 两行泪 
		ans=0;//清空 
		n=read(),k=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			ans+=popcount(a[i]);//第一部分的答案 
			solve(a[i]);//pos数组的处理 
		}
		for(int i=1;i<=70;i++)//依次尝试通过给每个数增加1的个数 
		{
			if(!pos[i]) continue;
			if(k<(1ll<<(i-1))) break;//如果当前的k已经不足以满足更新答案的需求 
			if(k>=pos[i]*(1ll<<(i-1))) ans=ans+pos[i],k=k-pos[i]*(1ll<<(i-1));//如果可以把所有数的这一位0都填成1 
			else ans=ans+k/(1ll<<(i-1)),k=0;//否则，只能填部分 
		} 
		output(ans);
	}
    return 0;
}
```

---

## 作者：CommandSR (赞：2)

## 基本思路

计算每个值 popcount 可以增加 $1$ 的最小值，记作 $calc_i$，即从低到高找到第一个 $0$，变成 $1$。

如 $calc_6 = 7$, $calc_7 = 15$。

被每一个 $calc_i$ 值丢进优先队列，贪心寻找代价最小的计入答案即可。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
using namespace std;
const int N = 5005;
ll n, m, a[N];
struct S {
	ll x, y;
	friend bool operator < (S u, S v) {
		return u.y - u.x > v.y - v.x;
	}
};
priority_queue <S> q;
ll calc(ll x) {
	F(i, 0, 60) {
		if (!(x & (1ll<<i))) {
			ll y = x ^ (1ll<<i);
			return y;
		}
	}
	return 114514; // 不可能返回这个
}
void Solve() {
	while (!q.empty()) q.pop();
	cin >> n >> m;
	ll ans = 0;
	F(i, 1, n) {
		cin >> a[i];
		q.push((S){a[i], calc(a[i])});
		ans += __builtin_popcount(a[i]);
	}
	ll cur = 0;
	while (!q.empty() && cur <= m) {
		S u = q.top(); q.pop();
		ll po = u.y - u.x;
		if (cur + po <= m) {
			cur += po;
			++ans;
			q.push((S){u.y, calc(u.y)});
		} else {
			break;
		}
	}
	cout << ans << '\n';
}
signed main() {
	ll T; cin >> T; 
	while (T--) Solve();
	return 0;
}
```

---

## 作者：残阳如血 (赞：2)

## CF2118C Make It Beautiful

### 题意

给定序列 $\{a_n\}$，定义一个序列的价值为每个数字的 $\operatorname{popcount}$ 之和。

最多进行 $k$ 次操作，每次操作可以给一个数加一。

$n\le5\times10^3$，$a_i\le10^9$，$k\le10^{18}$。

### 解法

首先我们先将所有的偶数 $+1$ 变为奇数。

然后将最后两位为 $01$ 的加两次，使其变为 $11$。

然后将最后三位为 $011$ 的加四次，使其变为 $111$。

然后将最后四位为 $0111$ 的加八次，使其变为 $1111$。

---

以此类推，我们每次将最后 $i$ 位为 $0\underbrace{111\cdots111}_{i\text{ 个 }1}$ 的数加 $2^i$ 次，如果不能达到次数就不进行修改。

那么我们需要高效地判断最后一个 $0$ 的位置。这个可以将原数取反后查询 $\operatorname{lowbit}$ 解决。

从小到大枚举 $i$ 直到 $k$ 耗尽为止。

#### 正确性证明

下面证明为什么要从小到大枚举 $i$。

假设我们有两种选择，第一种 $+2^i$ 使第 $i$ 位变为 $1$；第二种 $+2^j$ 使第 $j$ 位变为 $1$。其中 $j>i$。由于第一种花费更少，留给其它位置操作的可能性更多，所以我们一定会选择第一种。

这样就等价于从小到大枚举 $i$。

#### 时间复杂度

- 枚举 $i$，保险起见枚举 $0\sim62$，$O(\log k)$。
  - 枚举每一个数字，$O(n)$。
    - 修改这个数字，$O(1)$。

时间复杂度 $O(n\log k)$，可以通过。

此外，不优化的时间复杂度 $O(n\log^2k)$，也可以通过。

#### 代码

[Submission #325574515 - Codeforces](https://codeforces.com/contest/2118/submission/325574515)。

```c++
/**
 * Problem: CF2118C Make It Beautiful
 * Author:  OIer_wst
 * Date:    2025-06-22
 */
#include <bits/stdc++.h>
#define lowbit(i) ((i)&(-(i)))
using lint = long long;
const int N = 5e3 + 10;

int T, n;
lint k, ans, a[N];

int main() {
  for (std::cin >> T; T; --T) {
    std::cin >> n >> k, ans = 0;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 0; i < 63; ++i) { // 注意！这里 k 可能很大，可能会使得很多位为 1，所以要枚举到 62，再大一点就会爆 long long
      bool flag = false; // 可以用 flag 加速判断，k 无法使用时直接退出（显然花费在不断增加）
      for (int j = 1; j <= n; ++j) {
        if (lowbit(~a[j]) == 1ll << i) {
          if (k >= 1ll << i) {
            k -= 1ll << i;
            a[j] |= 1ll << i;
          } else {
            flag = true;
            break;
          }
        }
      }
      if (flag) break;
    }
    for (int i = 1; i <= n; ++i)
      ans += __builtin_popcountll(a[i]);
    std::cout << ans << std::endl;
  }
  return 0;
}
```

### 模型归纳

本题是一个**位贡献贪心问题**，常见做法就是拆位考虑。这也是处理二进制问题的常见方法。

### 技巧
- `lowbit(~x)` 可以求出 $x$ 最低位的 $0$ 代表的数。

---

## 作者：Forgive_Me (赞：1)

简单贪心。

题意：给你 $n$ 个数，$k$ 次 $a_i+=1$ 操作可以选用，求操作后的 
$$\max \sum_{i=1}^{n}\operatorname{popcount}(a_i)$$

分析：化简得 
$$\max \sum_{i=0}^{60}\sum_{j=1}^{n} {(1<<i) \& a_j}$$ 
发现 $\operatorname{popcount}$ 这个东西肯定是加低位更划算。比如你最后一位是 $0$ 想变成 $1$ 只需要用一个 $+ 1$，而倒数第二位是 $0$ 想变成 $1$ 需要用两个 $+ 1$。

那我们直接从低位往高位考虑，每次尽量填满，同时减去我们花费的次数，这样就对了。

时间复杂度 $O(n\log V)$。

```cpp
for(int i=0;i<60;i++){
	int now=(1ll<<i);
	for(int j=1;j<=n;j++){
		if(a[j]&now) ans++;
		else if(k>=now) k-=now,ans++;
	}
}	
```

---

## 作者：Mier_Samuelle (赞：1)

不难想到，若要使一个数的贡献增加 $1$，必定将其最低的数位 $0$ 改为 $1$。

于是我们预处理 $c_{i,j}$，表示使 $a_i$ 的贡献变为 $j$ 所需要的最小代价（即操作次数）。这部分可以做到 $O(n \log V)$，其中 $V=10^{18}$。

不难想到，每次操作必定选择一个代价最小的 $a_i$，使其贡献增加 $1$。这部分可以用优先队列做到 $O(n \log n \log V)$。

具体实现见代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 5010, MAXM = 70;
int a[MAXN], cost[MAXN][MAXM];
struct Node{
	int cost, i, j;
};
bool operator > (Node x, Node y){
	return x.cost > y.cost;
}
void solve(){
	int n, k, ans = 0;
	cin >> n >> k;
	for (int i = 1;i <= n;i++) cin >> a[i], ans += __builtin_popcount(a[i]);
	for (int i = 1;i <= n;i++){
		int ind = 0;
		for (int j = 1;j <= 63;j++){
			while (a[i] & (1ll << ind)) ind++;
			int na = a[i] | (1ll << ind);
			cost[i][j] = na - a[i];
			ind++;
		}
	}
	priority_queue <Node, vector<Node>, greater<Node>> q;
	for (int i = 1;i <= n;i++) q.push({cost[i][1], i, 1});
	while (k > 0 && !q.empty()){
		int c = q.top().cost, i = q.top().i, j = q.top().j;
		q.pop();
		if (k >= c){
			k -= c;
			ans++;
			q.push({cost[i][j + 1], i, j + 1});
		}
	}
	cout << ans << endl;
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：违规用户名920406 (赞：1)

本次 C 有点低于之前 Div.2 的难度。

## 题目大意

给你一堆数，定义每个数的美丽度为二进制下 $1$ 的个数。再给你常数 $k$ ，可以重复至多 $k$ 次，每次给某数加一，求最后最大的美丽度之和。

## 分析

先思考用多少代价能把一个数的美丽度增加。先把这个数拆位，贪心地考虑，美丽值加 $1$ 当然是把其中最低的 $0$ 变成 $1$ ，贡献当然是这一位的大小。加 $2$ 就是在此基础上在加 $1$ ，以此类推。

既然每次都只能耗确定的贡献加一，那能不能考虑贪心？第一次先找到其中美丽度加一的代价最小的，加一，再更新这个数的消耗。然后再选最小的，再消耗，直到 $k$ 不够用了，结束。

## 实现

用优先队列实现，先把数字和贡献存入，找到最小的，更新，再放回去。因为每次贡献成倍增长，所以每个数最多更新 $O(\log m)$ 次，共有 $n$ 个数，因为用的是堆，所以每次更新还有 $O(\log n)$ 的代价，所以最终时间复杂度为 $O(n \log n \log m)$，能过。

code:[codeforces.com/contest/2118/submission/324087206](https://codeforces.com/contest/2118/submission/324087206)

---

