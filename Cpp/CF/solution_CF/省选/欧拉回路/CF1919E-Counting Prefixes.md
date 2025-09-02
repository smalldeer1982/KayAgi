# Counting Prefixes

## 题目描述

有一个长度为 $n$ 的隐藏数组 $a$，其元素仅为 $1$ 或 $-1$。令 $p$ 为数组 $a$ 的前缀和数组。更正式地，$p$ 是一个长度为 $n$ 的数组，定义为 $p_i = a_1 + a_2 + \ldots + a_i$。随后，将数组 $p$ 按非递减顺序排序。例如，如果 $a = [1, -1, -1, 1, 1]$，则排序前 $p = [1, 0, -1, 0, 1]$，排序后 $p = [-1, 0, 0, 1, 1]$。

现在你得到了排序后的前缀和数组 $p$，但你并不知道原始数组 $a$。你的任务是统计有多少个原始数组 $a$，经过上述过程后能得到给定的排序后前缀和数组 $p$。由于答案可能很大，只需输出对 $998\,244\,353$ 取模的结果。

## 说明/提示

在前两个测试用例中，$n=1$ 时，唯一可能的数组 $a$ 分别为 $a=[1]$ 和 $a=[-1]$。它们对应的排序后前缀和数组分别为 $p=[1]$ 和 $p=[-1]$。因此，没有数组 $a$ 能得到 $p=[0]$，而恰好有 $1$ 个数组 $a$ 能得到 $p=[1]$。

在第三个测试用例中，可以证明没有数组 $a$ 能得到 $p=[-1, 1, 2]$。

在第四个测试用例中，能够得到 $p=[-1, 0, 0, 1, 1]$ 的 $3$ 个数组 $a$ 分别为：

- $a = [1, -1, 1, -1, -1]$，排序前前缀和为 $p = [1, 0, 1, 0, -1]$，排序后为 $p = [-1, 0, 0, 1, 1]$。
- $a = [1, -1, -1, 1, 1]$，排序前前缀和为 $p = [1, 0, -1, 0, 1]$，排序后为 $p = [-1, 0, 0, 1, 1]$。
- $a = [-1, 1, 1, -1, 1]$，排序前前缀和为 $p = [-1, 0, 1, 0, 1]$，排序后为 $p = [-1, 0, 0, 1, 1]$。

对于第五个测试用例，唯一能得到 $p=[-4, -3, -3, -2, -1]$ 的数组 $a$ 是 $a=[-1, -1, -1, -1, 1]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1
0
1
1
3
-1 1 2
5
-1 0 0 1 1
5
-4 -3 -3 -2 -1```

### 输出

```
0
1
0
3
1```

# 题解

## 作者：honglan0301 (赞：21)

## 题目分析

场上做法。

首先可以把题意转化成：“数轴上有若干个整点，你需要计数有多少条从 $1$ 或 $-1$ 出发的有向路径，使得每个点被经过次数与给定的 $cnt$ 数组相同”。

那么我们枚举路径的起终点 $s\in \{-1,1\},t\in[-n,n]$，这样之后每条有向边被经过的次数可以确定，记 $(i,i+1)$ 的边数（经过次数）为 $br_i$，$(i,i-1)$ 的边数（经过次数）为 $bl_i$，于是之后就变成了欧拉路径计数（此处两条路径不同仅取决于经过点的顺序不同，因此视每种重边为一个可重集合，类似多重集计数地处理）问题。

那么可以直接套 $\text{BEST}$ 定理，起终点分别为 $s,t$ 的路径数量就是 $T\times \prod\limits_{i=-n}^n \dfrac{(bl_i+br_i-[i\neq t])!}{bl_i!\times br_i!}$，其中 $T$ 是以 $t$ 为根的内向生成树数量，容易发现其值为 $(\prod\limits_{i=-n}^{t-1}br_i)\times (\prod\limits_{i=t+1}^n bl_i)$，因为整张图是个链。

于是做完了，总时间复杂度 $O(n^2)$，具体实现见代码。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long
#define ull unsigned long long
#define mod 998244353
mt19937 rnd(time(0));
mt19937_64 rndl(time(0));
#define B 5001

int T,n,p[5005],cnt[10005],in[10005],ot[10005],otr[10005],ans,jc[10005],ny[10005],nl,nr;
int br[10005],bl[10005];

int ksm(int x,int k)
{
	int na=1; for(int i=1;i<=k;i<<=1) {if(i&k) na=na*x%mod; x=x*x%mod;} return na;
}
int solve(int s,int t)
{
	for(int i=1;i<=10001;i++) in[i]=cnt[i]-(i==s),ot[i]=cnt[i]-(i==t);
	//cout<<"G "<<s<<" "<<t<<endl;
	for(int i=1;i<=10001;i++)
	{
		br[i]=ot[i]-bl[i];
		if(s<=i&&t>=i+1) bl[i+1]=br[i]-1;
		else if(t<=i&&s>=i+1) bl[i+1]=br[i]+1;
		else bl[i+1]=br[i];
		if(bl[i]<0||br[i]<0) return 0;
	}
	//cout<<"G "<<s<<" "<<t<<endl;
	int na=1;
	for(int i=nl;i<t;i++) na=na*br[i]%mod;
	for(int i=t+1;i<=nr;i++) na=na*bl[i]%mod;
	for(int i=nl;i<=nr;i++) 
	{
		if(i==t) na=na*jc[ot[i]]%mod;
		else if(ot[i]==0) return 0;
		else na=na*jc[ot[i]-1]%mod;
	}
	for(int i=nl;i<=nr;i++) na=na*ny[bl[i]]%mod*ny[br[i]]%mod;
	//cout<<"G "<<s<<" "<<t<<endl;
	//for(int i=B-5;i<=B+5;i++) cout<<i<<" "<<bl[i]<<" "<<br[i]<<endl;
	//cout<<na<<endl;
	return na;
}
int getrd(int l,int r)
{
	return l+(rnd()%(r-l+1));
}

signed main()
{
	cin>>T; jc[0]=1; for(int i=1;i<=10000;i++) jc[i]=jc[i-1]*i%mod;
	for(int i=0;i<=10000;i++) ny[i]=ksm(jc[i],mod-2);
	while(T--)
	{
		memset(cnt,0,sizeof(cnt)); ans=0;
		cin>>n; for(int i=1;i<=n;i++) cin>>p[i],cnt[p[i]+B]++;
		nl=10002,nr=0;
		for(int i=1;i<=10001;i++) if(cnt[i]) nl=min(nl,i),nr=max(nr,i);
		for(int i=1;i<=10001;i++) if(cnt[i]) ans=(ans+solve(B-1,i)+solve(B+1,i))%mod;
		cout<<ans<<endl;
	}
}
```


---

## 作者：EuphoricStar (赞：14)

考虑一个很类似的[题](https://www.luogu.com.cn/problem/AT_arc117_e)。我们把正数和负数分开来考虑，最后用 $0$ 连接一些连续段，形如 $0 - \text{正} - 0 - \text{正} - 0 - \text{负}$。

先考虑正数。设 $f_{i, j}$ 为考虑了 $\ge i$ 的正数，形成了 $j$ 个连续段的方案数。设 $i$ 的出现次数为 $c_i$。

那么之前的每个段两端都需要接一个 $i$ 下来，两段之间也可以只用一个 $i$ 连接。

特别地，如果已经考虑到了结尾位置 $n$，右端不用接数。于是我们状态再记一个 $f_{i, j, 0/1}$ 表示包含位置 $n$ 的段是否出现。

那么对于 $f_{i + 1, j, 0}$ 的转移，新的段数 $k = c_i - j$ 可以直接被计算出来。转移系数是 $c_i$ 个数分配给 $j + 1$ 个空的插板。我们有：

$$f_{i, k, 0} \gets f_{i + 1, j, 0} \times \binom{c_i - 1}{j}$$

$$f_{i, k, 1} \gets f_{i + 1, j, 0} \times \binom{c_i - 1}{j}$$

对于 $f_{i + 1, j, 1}$ 的转移，新的段数为 $k = c_i - j + 1$。有转移：

$$f_{i, k, 1} \gets f_{i + 1, j, 1} \times \binom{c_i - 1}{j - 1}$$

同样地考虑负数，设 $g_{i, j}$ 为考虑了 $\le -i$ 的负数，形成了 $j$ 个连续段的方案数。转移类似。

计算答案，只用枚举正数的段数 $i$，如果 $0$ 不为 $n$ 的前缀和，那么负数的段数为 $c_0 - i$，否则为 $c_0 - i - 1$。讨论一下 $n$ 的前缀和是给 $0$，正数还是负数，再乘上给段选择位置的系数。所以：

$$ans = \sum\limits_{i = 0}^{c_0} f_{1, i, 1} \times g_{1, c_0 - i, 0} \times \binom{c_0 - 1}{i - 1} + f_{1, i, 0} \times g_{1, c_0 - i, 1} \times \binom{c_0 - 1}{i} + f_{1, i, 0} \times g_{1, c_0 - i - 1, 0} \times \binom{c_0 - 1}{i}$$

直接计算 $f, g$ 复杂度为 $O(n^2)$。但是注意到 $f, g$ 初值只有 $O(1)$ 个位置有值，每次转移一个位置会转移到固定的另一个位置，最后一维只会进行 $0 \to 1$ 的转移不会进行 $1 \to 0$ 的转移。所以 dp 数组每行有值的位置数是 $\color{red}{O(1)}$ 的。如果我们用 unordered_map 把有值的位置存下来，复杂度将是 $\color{red}{O(n)}$。

[code](https://codeforces.com/problemset/submission/1919/240915314)

---

## 作者：_FL_ (赞：8)

$*2600$  

**常规 dp 做法在后面，此处为 BEST 定理做法。**（BEST 定理做法可能较为简略，建议看后面）  

应该讲过类似的初步转化。相当于从原点开始每次向左或向右走一单位长度，限制每个点的经过次数。  

容易通过求出 $Lx_i,Rx_i$ 分别表示从 $i$ 向左向右走的次数。但是此题有诸多不同：欧拉路径而非欧拉回路、两路径不同当且仅当经过点的顺序不同而非边的顺序不同。  

于是需要魔改 BEST 定理。$(d_x-1)!$ 改为 $\dfrac{(Lx_x+Rx_x-1)!}{Lx_x!\times Rx_x!}$，$d_s!$ 改为 $\dfrac{(Lx_s+Rx_s)!}{Lx_s!\times Rx_s!}$，原因是相当于变成无区别小球，后面 $d_s$ 变出来其实就是一个组合数。  

还是一样要把内向生成树的那条边放最后，所以除以 $d_i$（出度）得到上式。而至于欧拉路径的问题，感性理解一下 BEST 也可用于存在欧拉路径的有向图的欧拉路径计数。  

时间复杂度 $O(\sum n^2)$。然而常规 dp 做法可以做到 $O(\sum n)$。  

[提交记录](https://codeforces.com/contest/1919/submission/241660684)  

---

由 [[ARC146E] Simple Speed](https://www.luogu.com.cn/problem/AT_arc146_e) 来引入常规 dp 做法。  

$\text{Difficulty}:3131$  

这是起点终点无限制，且序列长度变为 $n^2$ 的版本。这种类型的常规处理方法其实并非 BEST。  

考虑到 $\sum A_i$ 达到 $10^{10}$，尝试按值域而非序列下标 dp。具体而言，从小到大填数。那么思考需要什么状态。现在填完了 $[1,i]$，形成若干个连续段。  

那么考虑目前的空段（两端与 $i$ 相邻）数量，其中最靠左右的两端的空段是特殊的，因为它们可以不填，也可以跳出去扩展出很多个空段。除此之外，每个空段都必须填至少一个 $i+1$。  

所以状态是中间空段个数 $j$ 以及两端空段情况。先考虑中间空段。首先要满足 $A_i\ge j$，先全部铺一个 $i+1$ 后剩下 $A_i-j$ 个。而如果一个空段恰好填了一个 $i+1$，它会消失（此时只能是将左右两段序列合并），填两个不变，填三个变两个，以此类推。因此再添 $x$ 个就会使得中间空段数变为 $x$。  

两端的空段情况就是能不能填（边界值是否为 $i$），如果能填则填的第一个必须仅靠 $i$，不会增加空段，往后也是填一个多一个。并且这些多出来的也属于中间的，所以转移并不多。  

即 $f_{i,j,0/1,0/1}$ 表示已填 $[1,i]$，中间有 $j$ 个空段，左端是/否可填，右端是/否可填，插板得到一个组合数系数的转移：  

$$\dbinom{A_{i+1}-1}{j-1}f_{i,j,p,q}\to f_{i+1,A_{i+1}-j,0,0}$$  
$$\dbinom{A_{i+1}-1}{j}f_{i,j,1,p}\to f_{i+1,A_{i+1}-j-1,1,0}$$  
$$\dbinom{A_{i+1}-1}{j}f_{i,j,p,1}\to f_{i+1,A_{i+1}-j-1,0,1}$$  
$$\dbinom{A_{i+1}-1}{j+1}f_{i,j,1,1}\to f_{i+1,A_{i+1}-j-2,1,1}$$  

仔细观察会发现对每个 $i$ 最多仅存在 $3$ 个合法的 $j$，所以状态数 $O(n)$，所以时间复杂度 $O(n)$。为方便可直接使用 `map` 存储，因为其复杂度为 $O(\log_2siz)$ 所以不影响复杂度。  

---

最后：使用常规方法解决此题  

最后的问题在于此题对起点有一个必须为 $0$ 的限制。仔细思考会发现这不难解决。限制在 $0$ 的位置必须向左转移，且 $1$ 位置禁止向左转移即可。  

[提交记录](https://codeforces.com/contest/1919/submission/241928527)  


---

## 作者：User_Unauthorized (赞：7)

考虑枚举序列的和。不妨设序列的和为 $s$，那么为了满足前缀和最大值的要求，我们可以初始构造出一个形如 $1, 1, 1, 1, \cdots, 1, 1, 1, -1, -1, \cdots, -1, -1$ 的序列，其中其有 $p_n$ 个 $1$ 和 $p_n - s$ 个 $-1$。考虑在此基础上对序列进行修改使得其满足其他前缀和的要求。

设 $s_i$ 表示前 $i$ 个元素的和，那么我们可以发现，若在 $a_i$ 后插入两个元素 $-1, 1$，那么 $s_i$ 和 $s_i - 1$ 在前缀和集合中均会多出现一次，这启发我们从大到小依次去在序列中插入 $-1, 1$ 并满足对应的前缀和出现次数的要求。

由于初始序列或为了满足较大的前缀和的要求，当前枚举到的前缀和出现的次数不一定是常数，但是可以通过考虑以上两个因素进行计算。在得到当前前缀和已经出现的次数后，我们便可以得到需要插入的 $-1, 1$ 的个数，并且每次插入必须插入在当前前缀和出现的位置后。设当前前缀和已经出现了 $x$ 次，还需要插入 $y$ 次，那么其方案数为在长度为 $y$ 的序列中插入 $x - 1$ 个隔板的方案数，即 $\dbinom{x + y - 1}{y}$。

这样我们就可以在 $O(n)$ 的时间内枚举序列的和，然后在 $O(n)$ 的时间内计算出对应的方案数，总时间复杂度为 $O(n^2)$。

---

## 作者：cpchenpi (赞：5)

题目链接：https://codeforces.com/problemset/problem/1919/E

### 题意

输入一个单调非减序列 $p$，求问有多少个序列 $a$，使得：

- $|a_i| = 1$；

- 令 $s_i = \sum_{j = 1}^i a_j$，则 $s$ 排序后与 $p$ 相同。

序列长度不超过 $5000$。

### 题解

这题在赛时想错了很多地方，结果赛后调了很长很长时间，竟然得到正解了……

“排序后相同”这个条件等价于每个数的出现次数相同，也就是只要记录每个数的出现次数。为了方便分析，加入 $p_0 = 0$。

```cpp
unordered_map<int, int> cnt;
cnt[0]++;
for (int i = 0; i < n; i++) cin >> p[i], cnt[p[i]]++;
```

首先显然 $p$ 的值域是一段包含 $0$ 的连续区间 $[-a, b]$，可以一开始做完这个检查。

```cpp
for (auto [k, v] : cnt) {
    if (k < 0) {
        if (!cnt.contains(k + 1)) {
            cout << 0 << "\n";
            return;
        }
    } else if (k > 0) {
        if (!cnt.contains(k - 1)) {
            cout << 0 << "\n";
            return;
        }
    }
}
```

$a_i$ 为正负一，就代表 $s$ 相邻两项是相邻数。观察 $s$ 的可能形态，例如 $[0, 1, 2, 1, 2, 1, 0, -1, -2, -1, 0, 1, 2, 1]$。

用 x 轴切开这个序列，则：

- $s$ 被分为几段，其中除最后一段外开头和结尾均为 $0$，而最后一段只需要以 $0$ 开始。我们把前一种叫做“闭区间”，后一种叫做“开区间”。（注意，当结尾为 $0$ 时，没有最后一段开区间）

- 每一段内部要么全部大于 $0$，要么全部小于 $0$。

我们枚举开区间和闭区间各有多少段大于 $0$，有多少段小于 $0$，则可以按照“每一段内部都必须大于 $0$”计算，最终使用组合数合并答案即可。

```cpp
Z ans = 0;
{
    int closed_cnt = cnt[0] - 1;
    for (int i = 0; i <= closed_cnt; i++) {
        for (int c = 0; c <= 1; c++) {
            ans += comb.get(closed_cnt, i) * calc(1, i, c) *
                    calc(-1, closed_cnt - i, 1 - c);
        }
    }
}
```

对 `calc` 这个子问题，考虑如何继续计算。使用一个扫描线从下往上扫描，则又有如下结论：

- 一个闭区间如果填入 $x$ 个数，则会变为 $x - 1$ 个闭区间。（也就是只填入一个数时，开区间在上一层消失；且至少要填入一个数）

- 一个开区间如果填入 $x$ 个数，则会变为 $x - 1$ 个闭区间和一个开区间。另外，如果填入 $0$ 个数，这个开区间消失。

例如例子 $[0, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 1]$：

![image](https://cdn.luogu.com.cn/upload/image_hosting/2cear16t.png)

由于有两个 $0$，一开始有一个开区间和一个闭区间。

- 从 $y = 0$ 向 $y = 1$ 扫描，第一个闭区间内有两个数，仍为一个闭区间；最后一个开区间内也有两个数，变为一个闭区间和一个开区间。

- 从 $y = 1$ 向 $y = 2$ 扫描，第一个闭区间内有三个数，变为两个闭区间；第二个闭区间内有一个数，消失；最后一个开区间内没有数，消失。

- 从 $y = 2$ 向 $y = 3$ 扫描，两个闭区间内均只有一个数，均消失。

- 此时已经不存在任何区间，也不存在任何未使用的数，故这是一种可行的方案。

将状态记作 $(i, closed, open)$，我们已经知道了状态的转移，考虑如何计数。记 $i$ 的出现次数为 $x$，则：

- 若 $open = 0$，也就是所有的数都要填到闭区间中。每个闭区间至少要填入一个数，使用插板法知有 $\binom{x - 1}{open - 1}$ 种方案。由于每个闭区间都使产生的新闭区间会减少一个，转移至的状态一定为 $(i + 1, x - closed, 0)$，即 $calc(i, closed, 0) = \binom{x - 1}{open - 1} \cdot calc(i + 1, x - closed, 0) $。

- 否则，$open = 1$。若这个区间内不填数，则相当于 $open = 0$ 的情况。否则，这个开区间被当做闭区间使用，相当于多出了一个闭区间的 $open = 0$ 的情况，唯一的区别是下一层 $open$ 也要为 $1$。

- 边界情况下 $x = 0$，此时只有 $open = 0$ 且  $closed \le 1$，才是合法方案。

（这个思路其实是一种连续段 DP。）可以使用记忆化搜索实现。

```cpp
unordered_map<i64, Z> cache;
function<Z(int, int, int)> calc = [&](int i, int closed_cnt, int open_cnt) {
    if (closed_cnt < 0) return Z(0);
    if (cnt[i] == 0) { return Z(closed_cnt == 0 && open_cnt <= 1); }
    i64 key = (i64)i * n * 2 + closed_cnt * 2 + open_cnt;
    if (cache.contains(key)) { return cache[key]; }
    Z res = 0;
    auto f = [&](int x, int closed_cnt, int open_cnt) -> Z {
        return comb.get(x - 1, closed_cnt - 1) *
                calc((i < 0) ? i - 1 : i + 1, x - closed_cnt, open_cnt);
    };
    int x = cnt[i];
    if (open_cnt) {
        res += f(x, closed_cnt + 1, 1);
        res += f(x, closed_cnt, 0);
    } else {
        res += f(x, closed_cnt, 0);
    }
    return cache[key] = res;
};
```

但需要注意，我们这样的计算中包含了“开区间一个数都没有”的情况，这样的情况下，开区间会被分为正负各计算一次，因此需要减去这样的重复情况修正。修正后统计答案的代码如下：

```cpp
Z ans = 0;
{
    int closed_cnt = cnt[0] - 1;
    for (int i = 0; i <= closed_cnt; i++) {
        for (int c = 0; c <= 1; c++) {
            ans += comb.get(closed_cnt, i) * calc(1, i, c) *
                    calc(-1, closed_cnt - i, 1 - c);
        }
        ans -= comb.get(closed_cnt, i) * calc(1, i, 0) *
                calc(-1, closed_cnt - i, 0);
    }
}
cout << ans << "\n";
```

### 复杂度分析

状态数是 $O(n^2)$ 的，因此时空复杂度均为 $O(n^2)$。但[我的提交](https://codeforces.com/contest/1919/submission/240659017)的时空表现都很好。

如果仔细分析，实际上这个做法可以做到线性时间复杂度。关键在于 DP 的每一层中，合法的值最多只有两个第二维下标，因此我们从最上层和最下层开始，向中间递推，实时维护不为 $0$ 的所有值即可，这部分甚至可以做到 $O(1)$ 空间复杂度（注意组合数的 $O(n)$ 空间不可避免）。

为什么这个结论成立？考虑从状态 $(1, t, 1)$ 出发，会走到的所有状态。首先考虑向 $open = 1$ 转移的分支：

$$
\begin{aligned}
(1, t, 1)
	&\to (2, x_1 - t - 1, 1) \\
	&\to (3, x_2 - (x_1 - t -1) -1 = x_2 - (x_1 - t), 1) \\
   &\to (4, x_3 - (x_ 2 - (x_1 - t)) - 1, 1) \\
   &\to (5, x_4 - (x_3 - (x_ 2 - (x_1 - t))), 1) \\
   &\to  \cdots
\end{aligned}
$$

可以看到，第二维下标有 $\sum_{i =0} ^{n} (-1)^i x_{n-i} - [n \equiv 0 \mathbin{mod} 2]$ 的形式。而另一条向 $open=0$ 分支是“一条路走到黑”，根据奇偶分类讨论，不难得到每层至多只有两个相差 $1$ 的第二维下标。

从结束点 $(mx+1, 0/1)$ 倒过来分析，也可以更方便地得到类似的结论。

但注意，我们记忆化搜索的代码由于并不知道当前在的状态是否合法，因此还是最坏 $O(n^2)$ 的。

而一份使用递推真正做到线性时间、常数空间的代码如下：

```cpp
using Z = atcoder::modint998244353;
using C = modint::comb<Z>;
C comb{5000 + 7};
using T = array<array<Z, 2>, 2>;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n), cnt(2 * n + 1);
    cnt[n]++;
    for (int i = 0; i < n; i++) { cin >> p[i], cnt[p[i] + n]++; }
    int mn = p[0], mx = p[n - 1];
    T ans1, ansn1;
    int base1 = 0, basen1 = 0;
    auto trans = [](int &base, T &lst, int c) {
        T now;
        base = c - base;
        now[0][0] = comb.get(c - 1, base - 1) * lst[0][0];
        now[0][1] = comb.get(c - 1, base - 1) * lst[0][0] +
                    comb.get(c - 1, base) * lst[1][1];
        now[1][1] = comb.get(c - 1, base - 1) * lst[0][1];
        lst = std::move(now);
    };
    ans1[0] = {1, 1};
    for (int i = mx; i >= 1; i--) trans(base1, ans1, cnt[i + n]);
    ansn1[0] = {1, 1};
    for (int i = mn; i <= -1; i++) trans(basen1, ansn1, cnt[i + n]);
    Z ans = 0;
    int closed_cnt = cnt[n] - 1;
    for (int b0 : {0, 1}) {
        for (int b1 : {0, 1}) {
            if (base1 + basen1 - b0 - b1 == closed_cnt) {
                int i = base1 - b0;
                ans += comb.get(closed_cnt, i) * ans1[b0][0] * ansn1[b1][1];
                ans += comb.get(closed_cnt, i) * ans1[b0][1] * ansn1[b1][0];
                ans -= comb.get(closed_cnt, i) * ans1[b0][0] * ansn1[b1][0];
            }
        }
    }
    cout << ans.val() << "\n";
}
```

请检查 CF 上[提交](https://codeforces.com/contest/1919/submission/240717611)。

### 拓展

[ARC146E](https://atcoder.jp/contests/arc146/tasks/arc146_e?lang=en) 题与这题基本一样，区别是：

- 出现不同数的个数、出现次数均在 $2 \times 10^5$ 级别；

- 出现次数以数组的形式给出（不限制总和），且均大于 $0$；

- 不限制 $s$ 的开头为 $0$，且出现的所有数大于 $0$。

事实上，我们可以以基本相同的方式解决该问题，不同点如下：

- 首先可以只考虑上半平面，不需要对两部分分别计算再合并答案。

- 由于出现次数均大于 $0$，可以从 $1$ 往上扫。

- 由于不限制开头第一个数，左右两边都可以有一个开区间。也就是说需要考虑 $open = 2$ 时的转移。转移应该容易类推得出。

- 不限制出现次数的总和，可以按照 $closed <= \max(cnt)$ 剪枝。

与上面不同，我们只进行了一次搜索，故可以确保时空复杂度均为线性。

观察这题的[官方题解](https://atcoder.jp/contests/arc146/editorial/4678?lang=en)，复杂度分析可能会更清晰，更容易理解。

参考代码：

``` cpp
using Z = atcoder::modint998244353;
using C = modint::comb<Z>;

constexpr int M = 200000 + 233;
C comb{M};

void solve() {
    int n;
    cin >> n;
    vector<int> cnt(n + 3, 0);
    for (int i = 1; i <= n; i++) cin >> cnt[i];
    unordered_map<i64, Z> cache;
    function<Z(int, int, int)> calc = [&](int i, int closed_cnt, int open_cnt) {
        if (closed_cnt < 0 || closed_cnt > M) return Z(0);
        if (cnt[i] == 0) { return Z(closed_cnt == 0); }
        i64 key = (i64)i * M * 3 + closed_cnt * 3 + open_cnt;
        if (cache.contains(key)) { return cache[key]; }
        Z res = 0;
        auto f = [&](int x, int closed_cnt, int open_cnt) -> Z {
            return comb.get(x - 1, closed_cnt - 1) *
                   calc(i + 1, x - closed_cnt, open_cnt);
        };
        int x = cnt[i];
        if (open_cnt == 2) {
            res += f(x, closed_cnt + 2, 2);
            res += 2 * f(x, closed_cnt + 1, 1);
            res += f(x, closed_cnt, 0);
        } else if (open_cnt == 1) {
            res += f(x, closed_cnt + 1, 1);
            res += f(x, closed_cnt, 0);
        } else {
            res += f(x, closed_cnt, 0);
        }
        return cache[key] = res;
    };
    int closed_cnt = cnt[1] - 1;
    cout << calc(2, closed_cnt, 2).val() << "\n";
}
```

---

## 作者：piggy123 (赞：4)

赛时的口胡，感觉比 CD 这种 adhoc 容易。

考虑一个折线图，从原点出发，每次向右向上或向下走一步，要求 $y=a_i$ 与折线有 $b_i$ 个交点。

根据原则：“想不出来的 DP 都是连续段 DP。”可以考虑从上往下连续段 DP。

设计 $dp_{i,j,k,l}$ 表示看到 $i$，有 $j$ 个连续段（显然，每个连续段会贡献两个交点），$k/l$ 为 $0/1$，表示开头结尾是否占据（因为开头结尾段只会贡献一个交点）。

转移可以枚举这一条直线上要加入几个单点，由此可以算出需要合并多少个连续段，直接转移即可。复杂度 $\Theta(n^2)$。

转移细节很多，要注意边界（比如组合数溢出边界时的值）。

AC Code：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

ll a[10005],cnt[10005],dp[2][10005][2][2],fac[10005],inv[10005];
const ll mod=998244353;

ll qkp(ll a,ll k){
	ll ans=1;
	while (k){
		if (k&1)ans*=a,ans%=mod;
		a*=a,a%=mod;
		k>>=1;
	}
	return ans;
}

ll C(ll n,ll m){
	if (n<0||m<0||n<m)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int main() {
	ll t;
	cin >> t;
	fac[0]=1;
	for (ll i=1;i<=10000;i++)fac[i]=fac[i-1]*i%mod;
	inv[10000]=qkp(fac[10000],mod-2);
	for (ll i=9999;i>=0;i--)inv[i]=(inv[i+1]*(i+1))%mod;
	while(t--) {
		ll n;
		cin >> n;
		for (ll i=0; i<=2*n; i++)cnt[i]=0;
		for (ll i=1; i<=n; i++) {
			cin >> a[i];
			cnt[a[i]+n]++;
		}
		cnt[n]++;
		if (n==1&&a[1]!=1&&a[1]!=-1){
			cout<<0<<"\n";
			continue;
		}else if (n==1){
			cout<<1<<"\n";
			continue;
		}
		memset(dp,0,sizeof(dp));
		dp[0][cnt[2*n]][0][0]=1;
		if (cnt[2*n]>0)
		dp[0][cnt[2*n]][0][1]=1;
		for (ll i=2*n-1; i>=0; i--) {
			memset(dp[i&1],0,sizeof(dp[i&1]));
			for (ll j=0; j<=cnt[i+1]+2; j++) {
				for (ll a=0; a<=1; a++) {
					for (ll b=0; b<=1; b++) {
						ll jc=2*j-a-b;
						
						if (!dp[i&1^1][j][a][b])continue;
//						cout<<i+1<<" "<<j<<" "<<a<<" "<<b<<":"<< dp[i&1^1][j][a][b]<< endl;
						for (ll c=0; c<=j; c++) {
							if (j!=0&&c==j)continue;
							if (cnt[i]-jc+c<0)continue;
							ll cp=max(j-c+1-a-b-1,0ll),nd=cnt[i]-jc+c;
							if (nd>0&&j-c+1-a-b==0)continue;
//							if (dp[i&1^1][j][a][b]*C[max(0ll,j-1)][c]%mod*C[nd+cp][cp]%mod)
//							cout<<"-->"<<j-c+nd<<" "<< dp[i&1^1][j][a][b]*C[max(0ll,j-1)][c]%mod*C[nd+cp][cp]%mod<< endl;
							dp[i&1^1][j][a][b]%=mod;
							dp[i&1][j-c+nd][a][b]+=dp[i&1^1][j][a][b]*C(max(0ll,j-1),c)%mod*C(nd+cp,cp)%mod;
							if (a==0&&i==n&&cnt[i]>0) {
								dp[i&1][j-c+nd][1][b]+=dp[i&1^1][j][a][b]*C(max(0ll,j-1),c)%mod*C(nd+cp,cp)%mod;
							}
							if (b==0&&cnt[i]>0) {
								dp[i&1][j-c+nd][a][1]+=dp[i&1^1][j][a][b]*C(max(0ll,j-1),c)%mod*C(nd+cp,cp)%mod;
							}
							if (a==0&&b==0&&i==n&&cnt[i]>1){
								dp[i&1][j-c+nd][1][1]+=dp[i&1^1][j][a][b]*C(max(0ll,j-1),c)%mod*C(nd+cp,cp)%mod;
							}
						}
					}
				}
			}
		}
		cout<< dp[0][1][1][1]%mod<<"\n";
	}
	return 0;
}
```


---

## 作者：MaxBlazeResFire (赞：3)

膜拜 [le0n 小可爱](https://codeforces.com/profile/le0n)。

本题等价于给定 $n$ 个数，可以随意把它们重排，其中 $i\in[-n,n]$ 有 $a_i$ 个，计算满足 $p_1\in\{1,-1\}$，$|p_i-p_{i-1}|=1$ 的数列 $p$ 个数。

值域上做 $\rm DP$，记 $f_{i,j,0/1,0/1}$ 表示考虑 $[-n,i]$ 这些数，当前数列中存在 $j$ 对 $i$ 相邻，最左侧与最右侧的数是否为 $i$ 时的方案数。

考虑每一项分别可以转移到哪里。对于 $f_{i,j,0,0}$，$a_{i+1}$ 个 $i+1$ 必须占掉 $j$ 个已有的位置，并且也只有 $j$ 个位置可以放，$\displaystyle f_{i,j,0,0}\times\binom{a_{i+1}-1}{j-1}\rightarrow f_{i+1,a_{i+1}-j,0,0}$；

对于 $f_{i,j,0,1}$，如果 $a_{i+1}$ 不占最右侧的位置，与上式相同，否则类似地有 $\displaystyle f_{i,j,0,1}\times\binom{a_{i+1}-1}{j}\rightarrow f_{i+1,a_{i+1}-j-1,0,1}$；对于 $f_{i,j,1,0}$ 相同。

对于 $f_{i,j,1,1}$，如果两侧都不占或只占一侧与上述大同小异，对于两侧都占，有 $\displaystyle f_{i,j,0,1}\times\binom{a_{i+1}-1}{j+1}\rightarrow f_{i+1,a_{i+1}-j-2,1,1}$；

注意到 $a_1\in\{-1,1\}$，我们可以考虑在状态中额外加一维表示最左侧是否为 $-1,1$。

考虑该转移的状态数，初始化时仅有 $1$ 种，由转移的形式不妨只考虑第二维下标上附带的常数，我们发现后面两维都为 $1$ 的部分是一条链，常数只有 $\{-2,0,2\}$ 三种，后面两维恰有一维为 $1$ 的部分第二维的常数只有 $\{-1,0,1\}$ 三种，都为 $0$ 的部分常数只有 $\{-2,-1,0,1,2\}$ 五种，总状态数只有 $O(n)$。

用一个 $\rm map$ 存一下，$\log(O(1))$ 的部分忽略不计，整体复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 20005
#define mod 998244353

int n,p[MAXN],a[MAXN],fac[MAXN],inv[MAXN],ifac[MAXN];

map<int,int> f[MAXN][2][2][2];

//考虑值域上的前 i 个数，左侧，右侧是否为 i，最左侧是否为 -1/1。

inline void chkadd( int &x , int k ){ x += k; if( x >= mod ) x -= mod; }

inline int C( int n , int m ){ return n >= m && n >= 0 && m >= 0 ? 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod : 0; }

inline void solve(){
	scanf("%d",&n); int minn = n,maxx = -n,Lim = 0;
	for( int i = 1 ; i <= n ; i ++ ){
		scanf("%d",&p[i]);
		minn = min( minn , p[i] ),maxx = max( maxx , p[i] );
	}
	for( int i = 1 ; i <= n ; i ++ ) a[p[i] - minn + 1] ++;
	f[1][1][1][abs( p[1] ) == 1][a[1] - 1] = 1;
	Lim = maxx - minn + 1;
	for( int i = 1 ; i < Lim ; i ++ ){
		int t = abs( i + minn ) == 1;
		for( int k = 0 ; k < 2 ; k ++ ){
			for( pair<int,int> c : f[i][0][0][k] ){
				int j = c.first,v = c.second;
				if( a[i + 1] >= j ) chkadd( f[i + 1][0][0][k][a[i + 1] - j] , 1ll * v * C( a[i + 1] - 1 , j - 1 ) % mod );
			}
			for( pair<int,int> c : f[i][0][1][k] ){
				int j = c.first,v = c.second;
				if( a[i + 1] >= j ) chkadd( f[i + 1][0][0][k][a[i + 1] - j] , 1ll * v * C( a[i + 1] - 1 , j - 1 ) % mod );
				if( a[i + 1] >= j + 1 ) chkadd( f[i + 1][0][1][k][a[i + 1] - j - 1] , 1ll * v * C( a[i + 1] - 1 , j ) % mod );
			}
			for( pair<int,int> c : f[i][1][0][k] ){
				int j = c.first,v = c.second;
				if( a[i + 1] >= j ) chkadd( f[i + 1][0][0][k][a[i + 1] - j] , 1ll * v * C( a[i + 1] - 1 , j - 1 ) % mod );
				if( a[i + 1] >= j + 1 ) chkadd( f[i + 1][1][0][t][a[i + 1] - j - 1] , 1ll * v * C( a[i + 1] - 1 , j ) % mod );
			}
			for( pair<int,int> c : f[i][1][1][k] ){
				int j = c.first,v = c.second;
				if( a[i + 1] >= j ) chkadd( f[i + 1][0][0][k][a[i + 1] - j] , 1ll * v * C( a[i + 1] - 1 , j - 1 ) % mod );
				if( a[i + 1] >= j + 1 ) chkadd( f[i + 1][0][1][k][a[i + 1] - j - 1] , 1ll * v * C( a[i + 1] - 1 , j ) % mod );
				if( a[i + 1] >= j + 1 ) chkadd( f[i + 1][1][0][t][a[i + 1] - j - 1] , 1ll * v * C( a[i + 1] - 1 , j ) % mod );
				if( a[i + 1] >= j + 2 ) chkadd( f[i + 1][1][1][t][a[i + 1] - j - 2] , 1ll * v * C( a[i + 1] - 1 , j + 1 ) % mod );
			}
		}
	}
	int Ans = 0;
	for( int i = 0 ; i < 2 ; i ++ )
		for( int j = 0 ; j < 2 ; j ++ ) chkadd( Ans , f[Lim][i][j][1][0] );
	printf("%d\n",Ans);
	for( int i = 1 ; i <= Lim ; i ++ ){
		for( int j = 0 ; j < 2 ; j ++ )
			for( int k = 0 ; k < 2 ; k ++ )
				for( int t = 0 ; t < 2 ; t ++ ) f[i][j][k][t].clear();
		a[i] = 0;
	}
}

signed main(){
	fac[0] = inv[1] = ifac[0] = 1;
	for( int i = 1 ; i <= MAXN - 5 ; i ++ ) fac[i] = 1ll * fac[i - 1] * i % mod;
	for( int i = 2 ; i <= MAXN - 5 ; i ++ ) inv[i] = 1ll * ( mod - mod / i ) * inv[mod % i] % mod;
	for( int i = 1 ; i <= MAXN - 5 ; i ++ ) ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：zifanwang (赞：2)

- [洛谷题面](https://www.luogu.com.cn/problem/CF1919E)
- [CF 题面](https://codeforces.com/contest/1919/problem/E)

考虑在 $p$ 中插入一个 $0$。那么题意，即求出满足相邻两项差为 $1$ 且第一个数为 $0$ 的 $p$ 的排列个数。

考虑从小到大插入每一个数。用 $dp_{i,j,x,y}$ 表示插入了前 $i$ 个数，第 $i$ 个数在序列中共有 $j$ 个连通块，开头/结尾的值是否等于这个数（$x/y$）的排列个数。因为是从小到大插入，所以当前插入的每一个数的左/右两边的数要么不存在，要么等于当前数 $-1$。

若当前插入的数为 $0$，则从前面转移过来的状态 $x$ 一定等于 $1$，转移后 $x$ 等于 $0$（即不能再在开头插入）。

若当前数不为 $0$，则考虑是否在开头/结尾插入，直接转移即可。

时间复杂度 $O(tn^2)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 5003
#define md 998244353
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int t,n,a[mxn],c[mxn<<1],f[mxn][mxn],dp[2][mxn][2][2];
bool fl;
signed main(){
	f[0][0]=1;
	rep(i,1,5000){
		f[i][0]=1;
		rep(j,1,i)f[i][j]=(f[i-1][j-1]+f[i-1][j])%md;
	}
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		rep(i,0,n<<1)c[i]=0;
		c[n]=1,fl=0;
		rep(i,1,n){
			scanf("%d",&a[i]),c[a[i]+n]++;
			if(i>1&&a[i]>a[i-1]+1)fl=1;
		}
		a[0]=0;
		sort(a,a+n+1);
		if(fl){
			puts("0");
			continue;
		}
		rep(i,1,n+1)dp[0][i][0][0]=dp[0][i][0][1]=dp[0][i][1][0]=dp[0][i][1][1]=0;
		if(!a[0]){
			dp[0][1][0][1]=1;
		}else dp[0][1][1][1]=1;
		rep(i,a[0]+n+1,a[n]+n){
			fl^=1;
			rep(i,1,n+1)dp[fl][i][0][0]=dp[fl][i][0][1]=dp[fl][i][1][0]=dp[fl][i][1][1]=0;
			rep(j,1,n+1){
				rept(x,0,2)rept(y,0,2)if(dp[fl^1][j][x][y]){
					if(i==n){
						if(!x)continue;
						if(c[i-1]-j+x+y<=c[i])dp[fl][c[i-1]-j+x+y][0][y]=(dp[fl][c[i-1]-j+x+y][0][y]+(ll)dp[fl^1][j][x][y]*f[c[i]-1][c[i-1]-j+x+y-1])%md;
						if(y&&c[i-1]-j+x<=c[i])dp[fl][c[i-1]-j+x][0][0]=(dp[fl][c[i-1]-j+x][0][0]+(ll)dp[fl^1][j][x][y]*f[c[i]-1][c[i-1]-j+x-1])%md;
						continue;
					}
					if(c[i-1]-j+x+y&&c[i-1]-j+x+y<=c[i])dp[fl][c[i-1]-j+x+y][x][y]=(dp[fl][c[i-1]-j+x+y][x][y]+(ll)dp[fl^1][j][x][y]*f[c[i]-1][c[i-1]-j+x+y-1])%md;
					if(x&&c[i-1]-j+y&&c[i-1]-j+y<=c[i])dp[fl][c[i-1]-j+y][0][y]=(dp[fl][c[i-1]-j+y][0][y]+(ll)dp[fl^1][j][x][y]*f[c[i]-1][c[i-1]-j+y-1])%md;
					if(y&&c[i-1]-j+x&&c[i-1]-j+x<=c[i])dp[fl][c[i-1]-j+x][x][0]=(dp[fl][c[i-1]-j+x][x][0]+(ll)dp[fl^1][j][x][y]*f[c[i]-1][c[i-1]-j+x-1])%md;
					if(x&&y&&c[i-1]-j&&c[i-1]-j<=c[i])dp[fl][c[i-1]-j][0][0]=(dp[fl][c[i-1]-j][0][0]+(ll)dp[fl^1][j][x][y]*f[c[i]-1][c[i-1]-j-1])%md;
				}
			}
		}
		printf("%d\n",(dp[fl][c[a[n]+n]][0][0]+dp[fl][c[a[n]+n]][0][1])%md);
	}
	return 0;
}
```

---

## 作者：Error_Yuan (赞：2)

赛时被 D 干爆了，哈哈。

不同的原序列一定对应着不同的 $p$。于是问题转化为对合法的 $p$ 的排列计数。一个 $p$ 的排列合法，当且仅当：

+ $p_1=1$ 或 $-1$，且
+ $|p_{i+1}-p_i|=1$。

数据范围允许平方做法，我们考虑枚举开头和结尾的数 $(l,r)$，然后线性 dp 求出满足上述所有条件的序列个数。

从小到大加入 $p_i$。一个 $p_i$ 要么被插入开头/结尾，要么被插入在连续的两个 $p_i-1$ 中间。于是考虑 $dp_{i,j}$ 表示前 $i$ 个数，且第 $i$ 个数有 $j$ 对相邻。由于此时已经确定最终的开头/结尾的数，我们也能直接确定此时 $i$ 需不需要放在开头/结尾。所以对于 $dp_{i,j}$，$p_i$ 需要被分成 $cnt_{p_i}-j$ 段，对应着 $l=cnt-j-[p_i\le l]-[p_i\le r]$ 个 $p_i-1$ 的连续段。

所以转移方程为 

$$
dp_{i,j}=dp_{i-1,cnt_{p_i}-j-[p_i\le l]-[p_i\le r]}\times{cnt_{p_i}-1\choose cnt_{p_i}-j-1}
$$

对于每组 $(l,r)$，时间复杂度为 $\mathcal{O}(\sum cnt_{p_i})=\mathcal{O}(n)$，总时间复杂度即为 $\mathcal{O}(n^2)$。

更好的实现应该能做到线性，但是平方算法已经足够通过本题。

[submission](https://codeforces.com/contest/1919/submission/240577086)

---

## 作者：_ANIG_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1919E)

转化一下题意：

求有多少个长度为 $n$ 的数组 $a$，使得 $|a_i-a_{i-1}|=1$ 且 $i$ 恰好出现了 $b_i$ 次。

貌似不好做，但是看起来就是 dp，考虑如何把这个问题划分成子问题。

可以发现，相邻两个 $0$ 之间要么全是正的，要么全是负的。

如果我们确定了所有 $0$，就可以数组以这些 $0$ 为分界划分成若干段，相邻两段互不影响。

这样就有点类似子问题了。

考虑重复这个过程，确定完 $0$ 后要确定 $1$ 和 $-1$。

可以枚举以 $0$ 为分界点划分成了多少个正段，多少个负段。

这里以正段为例。可以发现，这些正段对应的 $0$ 后面必须跟一个 $1$。每段内部的剩余的位置，又可以以 $1$ 为分界点划分成若干个子段，递归下去。

这样，dp 的状态大致就可以看出来了。

$f_{n,m}$ 表示当前考虑到数值 $n$，并且数值 $n-1$ 把整个数组划分成了 $m$ 段的方案数。

每段的第一个数必须是 $n$，这样 $n$ 划分成的段数就是 $a_n-m$，乘个插板的系数即可。

注意到，最后一个数不一定是 $0$，所以可以再定义一个 $g_{n,m}$ 表示最后一个数不为 $0$ 的方案数。

注意到 $m\le a_n$，所以总状态数为 $\sum a_i=n$。

时间复杂度貌似只有 $O(n)$，跑得飞快。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5005,mods=998244353;
int pows(int a,int b){
    if(b==0)return 1;
    int res=pows(a,b>>1);
    res=res*res%mods;
    if(b&1)res=res*a%mods;
    return res;
}
int t,n,p[N],sm1[N],sm2[N],jc[N],ny[N],mx;
vector<int>fs[N][2][2];
int C(int a,int b){
    if(a<b)return 0;
    if(a==b)return 1;
    if(a<0||b<0)return 0;
    return jc[a]*ny[b]%mods*ny[a-b]%mods;
}
int f(int n,int m,int*q,int op,int lx){
    if(q[n]<m)return 0;
    if(n>mx)return !op;
    if(fs[n][op][lx][m+1]>=0)return fs[n][op][lx][m+1];
    int res=0;
    if(op)res=C(q[n]-1,m)*(f(n+1,q[n]-m-1,q,1,lx)+f(n+1,q[n]-m-1,q,0,lx))%mods;
    else res=C(q[n]-1,m-1)*f(n+1,q[n]-m,q,0,lx)%mods;
    //cout<<n<<" "<<m<<" "<<op<<" "<<res<<" "<<q[n]<<endl;
    return fs[n][op][lx][m+1]=res;
}
signed main(){
    cin>>t;
    while(t--){
        mx=0;
        cin>>n;
        jc[0]=ny[0]=1;
        for(int i=0;i<=n;i++)sm1[i]=sm2[i]=0;
        for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%mods;
        ny[n]=pows(jc[n],mods-2);
        for(int i=n-1;i>=1;i--)ny[i]=ny[i+1]*(i+1)%mods;
        for(int i=1;i<=n;i++){
            scanf("%lld",&p[i]);
            if(p[i]>=0)sm1[p[i]]++;
            else sm2[-p[i]]++;
            mx=max(mx,abs(p[i]));
        }
        for(int i=0;i<=n;i++){
            int k=max(sm1[i],sm2[i])+2;
            for(int l=0;l<2;l++)for(int r=0;r<2;r++)fs[i][l][r].resize(k);
        }
        for(int i=0;i<=n;i++)for(int j=0;j<=max(sm1[i],sm2[i])+1;j++)fs[i][0][0][j]=fs[i][1][0][j]=fs[i][1][1][j]=fs[i][0][1][j]=-1;
        int res=0;
        for(int i=0;i<=sm1[0];i++){
            res+=C(sm1[0],i)*(f(1,i,sm1,1,0)*f(1,sm1[0]-i,sm2,0,1)%mods+f(1,i,sm1,0,0)*f(1,sm1[0]-i,sm2,1,1)%mods+f(1,i,sm1,0,0)*f(1,sm1[0]-i,sm2,0,1)%mods)%mods;
            res%=mods;
        }
        printf("%lld\n",res);
    }
}
```


---

## 作者：Inui_Sana (赞：0)

@Explodingkonjac 学长讲的做法，题解区有一篇讲这个的，但是感觉细节真的好多……

我们先尝试构造出来一个合法序列。怎么构造呢？先枚举 $\sum a_i=s$，然后先将序列 $a$ 设为 $\max(p_n,0)$ 个 $1$ 后面接 $\max(p_n,0)-s$ 个 $-1$，也就是先到最大值再到最终值。

然后考虑往这个数列中插入若干 $\{-1,1\}$ 这个序列。画到一个折线图上，发现这就相当于增加一块凹陷。不难发现，对于一个有解的 $s$，这样一定能构造出解。

设新前缀和序列为 $p'$ 同时，在一个 $p_i'=k$ 的位置后面插入一个 $\{-1,1\}$ 能使 $k,k-1$ 在 $p'$ 的出现次数增加 $1$。于是在构造的同时就可以计数了！

具体地，从大往小考虑 $x$ 的出现次数。设 $x$ 在 $p$ 中出现 $a_x$ 次，$p'$ 中 $b_x$ 次，则要通过插入 $\{-1,1\}$ 的操作将 $b_X$ 加到 $a$。反过来，一共要将 $a_x$ 个 $x$ 分到 $b_x$ 个集合中，插板法，贡献为 $\binom{a-1}{b-1}$。然后 $b_{x-1}$ 会加上 $a_x-b_x$，继续往下推即可。

细节包括但不限于：

- $p'$ 要考虑一开始的 $0$ 否则一开始下降的情况统计不到。

- $a_x=0$ 的情况要注意一下。

- 等等。

code：

```cpp
int n,m,fac[N],ifac[N],c[N],b[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int binom(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
void Yorushika(){
	scanf("%d",&n);
	int mx=0;
	rep(i,0,n+n)c[i]=0;
	c[n]=1;
	rep(i,1,n){
		int x;scanf("%d",&x);
		c[x+n]++,mx=max(mx,x+n);
	}
	fac[0]=1;
	rep(i,1,n)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	drep(i,n-1,0)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	int ans=0;
	rep(j,0,n+n){
		if(!c[j])continue;
		int x=n,res=1;
		rep(i,0,n+n)b[i]=0;
		b[n]=1;
		rep(i,1,mx-n)b[++x]++;
		rep(i,1,max(mx,n)-j)b[--x]++;
		bool fl=1;
		if(!fl)continue;
		drep(i,n+n,0){
			if(!c[i]){if(b[i]){res=0;break;}continue;}
			res=1ll*res*binom(c[i]-1,b[i]-1)%mod;
			if(i)b[i-1]+=c[i]-b[i];
		}
		ans=Mod(ans,res);
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Acoipp (赞：0)

## 分析

首先每次 $+1$ 和 $-1$ 都可以看做是在数轴上往右走一步，或者往左走一步，要求到达每个点的次数是恰好等于题目中给定的，问有多少种走法。

如果我们把数轴上的点看做图上的点的话，我们就相当于可以枚举起点 $\{1,-1\}$，终点 $[-n,n]$，然后计算起点 $s$ 到终点 $t$ 的走法。

我们可以发现，一旦我们确定了起点和终点，那么从 $i \sim i+1$ 的次数就可以确定，从 $i \sim i-1$ 的次数也可以确定。

于是我们可以先计算出这个结果，设 $l_i$ 表示 $i \to i-1$ 的次数，$r_i$ 表示 $i \to i+1$ 的次数，容易发现，对于 $l$ 和 $r$ 数组有如下关系：

$$
\begin{cases}
r_i=l_{i+1}+1 & (s \le i \le i+1 \le t) \\
r_i=l_{i+1}-1 & (t \le i \le i+1 \le s) \\
r_i=l_{i+1} & \text{Otherwise}
\end{cases}
$$

并且 $l_i+r_i$ 恰好是题目中 $i$ 出现的次数，但是当 $i=t$ 的时候要减 $1$，因为 $t$ 最后没有出边。

对于第一种情况我们可以理解为 $s \to t$ 的每条边都要恰好比反向边多经过一次，第二种情况反之，第三种情况就是一定会正反经过这条边恰好 $k$ 次，所以次数相等。（我们也可以用有向图的欧拉回路的性质来判定）

于是我们就可以知道边经过的次数，这道题就转化为了欧拉回路计数问题，用 BEST 定理计算即可，但是因为重边实际上可以任意选择却不影响方案数量，所以在 BEST 定理证明过程中需要把每个点可以选择的出边条数变成 $\dfrac{(l_i+r_i-1)!}{l_i!+r_i!}$，最后还要乘上从 $t$ 出发的边的数量 $(l_t+r_t)$。

最后还要乘上以 $t$ 为根的内向生成树个数，显然，因为图是一条链，所以答案是 $(\prod_{i=-n}^{t-1} r_i) \times (\prod_{i=t+1}^{n} l_i)$.

## 代码

最后需要判断一下边界情况，这里就不赘述了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define M 200005
#define B 5002
#define mod 998244353
using namespace std;
vector<ll> op[M];
ll T,n,m,i,j,x,y,ans,jc[M],inv[M],ot[M],vis[M],vit,cnt[M],st,ed,tl[M],tr[M],bl,br;
inline ll qmi(ll a,ll b,ll p){
	ll res = 1%p,t=a;
	while(b){
		if(b&1) res=res*t%p;
		t=t*t%p;
		b>>=1;
	}
	return res;
}
inline ll solve(ll s,ll t){
	if(!cnt[s]||!cnt[t]) return 0;
	for(ll i=st;i<=ed;i++) ot[i]=cnt[i]-(i==t);
	for(ll i=st;i<=ed;i++){
		tr[i]=ot[i]-tl[i];
		if(s<=i&&i+1<=t) tl[i+1]=tr[i]-1;
		else if(t<=i&&i+1<=s) tl[i+1]=tr[i]+1;
		else tl[i+1]=tr[i];
		if(tl[i]<0||tr[i]<0) return 0;
	}
	ll res = 1;
	for(ll i=bl;i<=br;i++){
		if(i==t) res=res*jc[ot[i]]%mod;
		else{
			if(ot[i]==0) return 0;
			res=res*jc[ot[i]-1]%mod;
		}
	}
	for(ll i=bl;i<=br;i++) res=res*inv[tl[i]]%mod*inv[tr[i]]%mod;
	for(ll i=bl;i<t;i++) res=res*tr[i]%mod;
	for(ll i=t+1;i<=br;i++) res=res*tl[i]%mod;
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	jc[0] = 1;
	for(i=1;i<=2e5;i++) jc[i]=jc[i-1]*i%mod;
	inv[200000] = qmi(jc[200000],mod-2,mod)%mod;
	for(i=2e5;i>=1;i--) inv[i-1]=inv[i]*i%mod;
	cin>>T;
	while(T--){
		ans=0;
		cin>>n;
		for(i=1;i<=n;i++) cin>>x,cnt[x+B]++;
		st = B-n-1,ed = B+n+1,bl = LLONG_MAX,br = LLONG_MIN;
		for(i=st;i<=ed;i++) if(cnt[i]) bl=min(bl,i),br=max(br,i);
		for(i=bl;i<=br;i++) if(!cnt[i]) break;
		if(i<=br){
			cout<<0<<endl;
			for(i=st-1;i<=ed+1;i++) cnt[i]=0,ot[i]=0,tl[i]=0,tr[i]=0;
			continue;
		}
		for(i=st;i<=ed;i++) ans=(ans+solve(B-1,i)+solve(B+1,i))%mod;
		cout<<ans<<endl;
		for(i=st-1;i<=ed+1;i++) cnt[i]=0,ot[i]=0,tl[i]=0,tr[i]=0;
	}
	return 0;
}
```

---

## 作者：dxbt (赞：0)

+ Update on 2024.1.9：修改了一处语病。


一个序列合法等价于以下两个条件同时满足：
+ 序列的开头的数为 $\pm 1$。
+ 相邻两个数的差的绝对值为 $1$。

我们考虑把数从小到大插入构造前缀和序列。

插入 $x$ 的条件为这个数的前驱后继要么是 $x-1$，要么是 $x$，后续插入 $x+1$ 来满足条件 2。

那么插入完所有的 $x$ 后，序列就会形如 $x-1,x,\dots,x,x-1$，可以发现一段 $x$ 的两边都是 $x-1$，我们考虑维护这种段的数量。

我们钦定这个序列的开头 $head= \pm 1$ 和结尾 $tail$，然后就可以统计了。

我们使用插板法，所有需要插入的相邻两个 $x-1$ 之间和开头结尾都要放入至少一个 $x$，然后新的需要插入的段就变成了 $x$ 的个数 $-$ 插入段的个数。

注意在 $x = head$ 或 $x = tail$ 时要把插入段减 $1$。

```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l,i##end=r;i<=i##end;++i)
#define G(i,l,r) for(int i=l,i##end=r;i>=i##end;--i)
using namespace std;
template<typename T>inline void readmain(T &n){T sum=0,x=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')x=-1;ch=getchar();}while(isdigit(ch)){sum=sum*10+ch-'0';ch=getchar();}n=sum*x;}
template<typename T>inline T& read(T &x){readmain(x);return x;}
template<typename T,typename ...Tr>inline void read(T &x,Tr&... r){readmain(x);read(r...);}
template<typename T>inline void write(T x){if (x<0){putchar('-');x=-x;}if (x>9)write(x/10);putchar(x%10+'0');return;}
template<typename T>inline void writesc(T x){write(x);putchar(' ');}
template<typename T>inline void writeln(T x){write(x);putchar('\n');}
int cnt[10009];
const int mod=998244353;
int minn;
int fac[10009];
int inv[10009];int n;
int qpow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}
int C(int n,int m)
{
	if(n==m)return 1;
	if(n<m) return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int work(int x,int y)
{
	int t=2,num=cnt[minn]-1;int ans=1;
	if(minn>x || minn>y)return 0;
	if(minn==x)t--;
	if(minn==y)t--;
	if(num<0) return 0;
	F(i,minn+1,2*n)
	{
		ans=1ll*ans*C(cnt[i]-1,num+t-1)%mod;
		num=cnt[i]-num-t;
		if(num<0)return 0; 
		if(i==x)t--;
		if(i==y)t--;
	}
	if(num!=0 || t!=0)ans=0;
	return ans;
}
void solve()
{
	memset(cnt,0,sizeof cnt); 
	read(n);bool flag=true;minn=2*n;
	F(i,1,n)
	{
		int x;
		read(x);
		if((x>n)||(x<-n)) flag=false;
		if(flag) cnt[x+n]++;
		minn=min(minn,x+n);
	}
	if(!flag)
	{
		puts("0");
		return ;
	}
	int ans=0;
	F(i,0,2*n) (ans+=work(1+n,i))%=mod;
	F(i,0,2*n) (ans+=work(-1+n,i))%=mod; 
	cout<<ans<<'\n';
}
signed main()
{
	fac[0]=1;
	F(i,1,10000) fac[i]=1ll*fac[i-1]*i%mod;
	inv[10000]=qpow(fac[10000],mod-2);
	G(i,10000,1)inv[i-1]=1ll*inv[i]*i%mod;
    int T=1;
    read(T);
    while(T--)solve();
	return 0;
}

```


---

