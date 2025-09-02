# [OOI 2025] The arithmetic exercise

## 题目背景

[试题来源](https://inf-open.ru/2024-25/final-materials/)。

## 题目描述

Oleg 和 Dasha 参加了一场团队竞赛，但不幸的是，他们未能解决任何问题。Oleg 立刻意识到他们的队伍训练不足。然后，他们共同的朋友提出了一个有趣的练习。这个练习相当简单，要解决它，只需要知道整数加减法的规则。

给定一个长度为 $n$ 的数组 $a$，初始时所有值均为零。同时给定 $m$ 个数 $x_1, x_2, \ldots, x_m$。然后，对于从 $1$ 到 $m$ 的每个 $i$，你需要选择某个下标 $j_i$，并执行更改 $a_{j_i} = x_i - a_{j_i}$。

请帮助 Oleg 和 Dasha 确定，如果每次选择都最优，那么在所有更改完成之后，数组 $a$ 的元素之和的最大值可能为多少。

## 说明/提示

**样例解释**

在第一个数据集中，所有操作都应用于数组 $a$ 的第一个元素。它依次变为 $1 - 0 = 1$，$2 - 1 = 1$，$3 - 1 = 2$，$4 - 2 = 2$，所以答案是 $2$。

在第二个数据集中，可以执行以下更改序列：

1.  将更改应用于第一个元素：$a_1 = 10 - a_1 = 10 - 0 = 10$，此时 $a = [10, 0]$。
2.  将更改应用于第一个元素：$a_1 = 3 - a_1 = 3 - 10 = -7$，此时 $a = [-7, 0]$。
3.  将更改应用于第一个元素：$a_1 = 7 - a_1 = 7 - (-7) = 14$，此时 $a = [14, 0]$。
4.  将更改应用于第一个元素：$a_1 = 1 - a_1 = 1 - 14 = -13$，此时 $a = [-13, 0]$。
5.  将更改应用于第二个元素：$a_2 = 4 - a_2 = 4 - 0 = 4$，此时 $a = [-13, 4]$。
6.  将更改应用于第一个元素：$a_1 = 6 - a_1 = 6 - (-13) = 19$，此时 $a = [19, 4]$。
7.  将更改应用于第二个元素：$a_2 = 3 - a_2 = 3 - 4 = -1$，此时 $a = [19, -1]$。

最后，我们得到 $a = [19, -1]$，所以最终的和是 $18$。

可以证明不可能得到更好的结果。

**评分**

本题的测试点包含十个分组。每个分组的分数只有在该分组的所有测试点以及所有依赖分组的测试点都通过时才能获得。请注意，通过样例测试点对于某些分组不是必需的。**Offline-evaluation** 表示该分组的测试结果将在比赛结束后才可查看。

| Subtask | 分数 | 额外限制：$n, N$ | 额外限制：$m, M$ | 额外限制：$x_i$ | 依赖组别 | 说明                                                 |
| :--- | :--- | :--------------- | :--------------- | :--------------- | :------- | :--------------------------------------------------- |
| 0    | 0    | --               | --               | --               | --       | 样例。                                               |
| 1    | 4    | --               | --               | $0 \le x_i$      | --       | 所有 $x_i$ 都相同。                                  |
| 2    | 8    | $n=2$            | $M \le 30$，$m \le 18$ | --               | --       |                                                      |
| 3    | 11   | $n=2$            | $M \le 50$       | $-10 \le x_i \le 10$ | --       |                                                      |
| 4    | 9    | $n=2$            | $M \le 400$      | $-400 \le x_i \le 400$ | 3        |                                                      |
| 5    | 8    | $N \le 30$，$n \le 18$ | $M \le 30$，$m \le 18$ | --               | 0        |                                                      |
| 6    | 10   | $N \le 2000$     | $M \le 2000$     | $0 \le x_i$      | --       |                                                      |
| 7    | 12   | $N \le 2000$     | $M \le 2000$     | --               | 0, 2 -- 6 |                                                      |
| 8    | 10   | --               | --               | $0 \le x_i$      | 1        | $x_i$ 中最多只有两个不同的值。                       |
| 9    | 17   | --               | --               | $0 \le x_i$      | 1, 6, 8  |                                                      |
| 10   | 11   | --               | --               | --               | 0 -- 9   | **Offline-evaluation**。                             |

## 样例 #1

### 输入

```
4
1 4
1 2 3 4
2 7
10 3 7 1 4 6 3
4 10
103 354 1 227 179 189 142 201 165 140
5 3
-10 11 -4```

### 输出

```
2
18
1085
17```

# 题解

## 作者：FFTotoro (赞：6)

在阅读题解的过程中，你可能需要用到[该云剪贴板](https://www.luogu.me/paste/9f3l4i8w)中的部分代码辅助理解。

观察到每个元素 $x$ 对最终答案的贡献必然是 $x$ 或 $-x$，所以考虑给每个元素赋一个符号（$+$ 或 $-$，表示贡献系数为 $1$ 或 $-1$）；考察怎样的贡献系数赋值方法可以对应一个操作序列：对于一个系数序列 $k_1,k_2,\ldots,k_n(k_i\in\{1,-1\})$，能对应一个操作序列当且仅当 $\forall i,0\le\sum\limits_{j=1}^i k_j\le n$。

据此可以设计一个 $O(n^2)$ DP，$f_{i,j}$ 表示考虑了前 $i$ 个系数，系数和为 $j$ 能得到的最大答案，初始值为 $f_{0,0}=0$。有以下转移：

- $f_{i,j}\gets f_{i-1,j-1}+x_i(0\le j-1<j\le n)$；
- $f_{i,j}\gets f_{i-1,j+1}-x_i(0\le j<j+1\le n)$。

*上面的暴力 DP 实现可以参考云剪贴板中的 Code 1。*

观察到这种“平移”的形式很像 [slope trick](https://usaco.guide/adv/slope-trick?lang=cpp) 能做的东西，但是现在看起来还有一点麻烦。事实上，我们只需要对它做两个小修改即可：

- 令答案初始值为 $-\sum\limits_{i=1}^m x_i$，在第 $i$ 轮 DP 时，对于上面第二个转移方程，将该轮的 DP 数组平移一位使其与上一轮的相同位置对齐，这样第一个转移方程变为 $f_{i,j}\gets f_{i-1,j-2}+2x_i$，第二个转移方程就可以忽略掉；*（见云剪贴板中的 Code 2）*
- 观察到事实上每一轮的 $j-2\to j$ 可以改为 $j-1\to j$，因为在第奇数轮偶数的位置显然不会有值，反之亦然。当然这个时候数组下标的范围也需要进行一些修改。*（见云剪贴板中的 Code 3）*

于是该问题被转化成了一个经典的 slope trick 问题，可以使用 `multiset` 维护。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin>>t;
  while(t--){
    int n,m; cin>>n>>m;
    vector<int> a(m);
    for(auto &i:a)cin>>i;
    reverse(a.begin(),a.end());
    long long w=-accumulate(a.begin(),a.end(),0ll);
    multiset<int,greater<> > s;
    for(int i=0,p=0;i<m;i++){
      int l=i+2>>1,r=i+n+1>>1;
      // 当前能够参与转移的下标的范围
      s.emplace(a[i]<<1);
      while(p<l)w+=*s.begin(),s.erase(s.begin()),p++;
      while(p+s.size()>r)s.erase(prev(s.end()));
    } // DP 过程
    for(int i:s)if(i>0)w+=i;
    cout<<w<<'\n';
  }
  return 0;
}
```

---

## 作者：NOI_Winner (赞：4)

我们先来讨论 $N \le 2000, M \le 2000$ 的做法。我们可以将原问题看成一个如下的过程：有 $n$ 个栈，依次按顺序处理 $m$ 个数，对于每个数我们可以任选一个栈把栈里所有的数符号取反，并把当前数压入栈中。但是这个过程中涉及对之前的数符号的更改，难以直接处理。我们发现，将整个过程按从 $m$ 到 $1$ 的相反方向处理，就不再涉及符号的更改，我们只要考虑当前数符号是否改变，并始终保持未取反的数个数减去取反的数的个数在 $[0,n]$ 范围内即可。我们很容易涉及出一个 dp，设 $dp_{i,j}$ 表示后 $i$ 个数中，取反个数减去未取反个数为 $j$，那么转移方程式为：
$$
dp_{i,j} = \begin{cases} dp_{i-1,j+1} - a_i, & j = 0 \\
max\{dp_{i-1,j-1} + a_i, dp_{i-1,j+1} - a_i\}, & 0 \lt j \lt n \\
dp_{i-1,j-1} + a_i, & j = n
\end{cases}
$$
边界情况：
$$
dp_{0,j} = \begin{cases} 0, & j = 0 \\
-\infty, & 0 \lt j \le n
\end{cases}
$$
再考虑正解，我们考虑优化这个 dp，这看起来很像 slope trick。当 $i$ 固定时，我们可以发现 $dp_{i,j}$ 是一个关于 $j$ 的上凸包，动态规划的转移实际上就是这个凸包与一个点数为 $2$ 的凸包作闵可夫斯基和。我们便可以使用一个 `multiset` 维护相邻节点的差值，并用另一个变量维护第一个点的具体数值是多少，最后对所有点取最大值就可以了。

代码示例：
```cpp
#include <iostream>
#include <functional>
#include <iterator>
#include <set>

using namespace std;

using ll = long long;
constexpr int maxn = 300000;
int a[maxn + 5];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    while (t--)
    {
        int n, m; cin >> n >> m;
        for (int i = 1; i <= m; i++)
            cin >> a[m - i + 1];
        
        ll val = 0;       //  维护第一个点的值
        multiset<int, greater<int>> st;
        for (int i = 1; i <= m; i++)
        {
            st.insert(2 * a[i]);
            val -= a[i];
            if (i & 1)
            {
                val += *st.begin();
                st.erase(st.begin());
            }
            while (st.size() >= (i & 1 ? (n + 1) >> 1 : (n + 2) >> 1))
                st.erase(prev(st.end()));
        }
        
        ll ans = val;
        for (int i : st)
        {
            val += i;
            ans = max(ans, val);
        }
        cout << ans << endl;
    }
    
    return 0;
}
```

---

## 作者：123456xwd (赞：3)

比较神秘的题目。

考虑既然 $x_i$ 之间是独立的，且若从前往后考虑的话，每次都要乘上一个 $-1$，不妨**将其翻转，倒着考虑**，这样子第一次贡献一定是正，第二次一定为负，...，这样就方便储存信息。

设 $f_{i,j}$ 表示考虑了搞了前 $i$ 个，目前 $j$ 个若得到贡献会为负数（即 $j$ 个接受了奇数次贡献）的最大值。

则 $f_{0,0}=0$，且 $f_{i,j}=\max(f_{i-1,j-1}+x_i,f_{i-1,j+1}-x_i)$。

那么一个加，一个减，不好看，变化为：$f_{i,j}=\max(f_{i-1,j-1}+2x_i,f_{i-1,j+1})-x_i$，那么最后减去 $\sum x_i$，式子变为：$f_{i,j}=\max(f_{i-1,j-1}+2x_i,f_{i-1,j+1})$。

那么发现一个非常有趣的性质，由于 $j-1,j+1$ 的奇偶性相同，根据我们的初始状态，那么当 $i,j$ 奇偶性相同的时候，$f_{i,j}$ 才有实际意义。

那么不妨把 $2j,2j+1(j\ge 0)$ 视作一个东东，那么有：

1. $i$ 为奇数：$f_{i,j}=\max(f_{i-1,j}+2x_i,f_{i-1,j+1})$。
2. $i$ 为偶数：$f_{i,j}=\max(f_{i-1,j},f_{i-1,j-1}+2x_i)$。

一眼丁真，鉴定为 slope trick。

凸性如何证明，设 $\Delta_{i,j}=f_{i,j}-f_{i,j-1}$，实际上我们可以证明其是单调递减的，即是一个上凸包。

1. 若 $i$ 为偶数，那么 $f_{i,j}=f_{i-1,j-1}+\max(\Delta_{i-1,j},2x_i)$。

   那么前面一段会选择 $\Delta$，后面一段会选择 $2x_i$。

   考虑取到 $\Delta$ 的那一段，有：$\Delta_{i,j}=f_{i,j}-f_{i,j-1}=(f_{i-1,j-1}+\Delta_{i-1,j})-(f_{i-1,j-2}+\Delta_{i-1,j-1})=\Delta_{i-1,j}$

   对于取到 $2x_i$ 那一段，更简单，$\Delta_{i,j}=\Delta_{i-1,j-1}$。

   对于分界点，$\Delta_{i,k}=(f_{i-1,k-1}+2x_i)-(f_{i-1,k-2}+\Delta_{i-1,k-1})=2x_i$

   由于有 $2x_i\ge \Delta_{i-1,k}=\Delta_{i,k+1}$，那么显然 $\Delta$ 继续单调递增。

   ****

3. 若 $i$ 为奇数，那么 $f_{i,j}=f_{i-1,j}+\max(2x_i,\Delta_{i-1,j+1})$。

   那么前面一段会选择 $\Delta$，后面一段会选择 $2x_i$。

   考虑取到 $\Delta$ 的那一段，有：$\Delta_{i,j}=f_{i,j}-f_{i,j-1}=(f_{i-1,j}+\Delta_{i-1,j+1})-(f_{i-1,j-1}+\Delta_{i-1,j})=\Delta_{i-1,j+1}$

   对于取到 $2x_i$ 那一段，更简单，$\Delta_{i,j}=\Delta_{i-1,j}$。

   对于分界点，$\Delta_{i,j}=(f_{i-1,j}+2x_i)-(f_{i-1,j-1}+\Delta_{i-1,j})=2x_i$

   $\Delta$ 递减的证明同上，不再赘述。

那么直接用 `multiset` 维护这个 $\Delta$ 即可。

细节：

1. $i$ 为奇数的时候，由上面，可知我们要把 $\Delta_{1}$ 计入答案并在 `multiset` 中删除。
2. $i$ 奇偶性不同的时候，$j$ 的上界不同。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
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
const int N=3e5+5,INF=0x3f3f3f3f3f3f3f3f;
int n,m,a[N],ans,val;
multiset<int,greater<int> > s;
void solve(){
	n=rd();m=rd();for(int i=1;i<=m;i++)a[i]=rd(),val-=a[i];
	reverse(a+1,a+1+m);
	for(int i=1;i<=m;i++){
		s.insert((a[i]<<1ll));
		if(i&1) val+=(*s.begin()),s.erase(s.begin());
		int lim=(n+2-(i&1))>>1;
		while(s.size()>=lim) s.erase(prev(s.end()));
	}
	ans=val;
	for(auto u : s) val+=u,ans=max(ans,val);
	printf("%lld\n",ans);
}
void clean(){
	ans=val=0;
	s.clear();
}
signed main(){
	int T=rd();while(T--)solve(),clean();
    return 0;
}
```

---

## 作者：Asedwai (赞：2)

不会 DP 直接贪。  
  感觉难度不到黑。
## 思路
  注意到每个 $x$ 对于答案的贡献要么是 $x$ 要么是 $-x$。考虑将每个 $x$ 选择一个符号，记 $+$ 为 $+1$，$-$ 为 $-1$。容易发现，符号序列最后合法，当且仅当任意后缀和都属于 $[0,n]$。  

  于是我们考虑从后往前枚举，贪心地钦定每个 $x$ 的符号。具体来说：若 $x\ge 0$，则让 $x$ 的符号为正；否则让其符号为负。仅仅这样做无法保证正确性，若当前后缀和脱离了 $[0,n]$ 的范围，则其不合法。  

  考虑维护这一过程。当前后缀和 $>n$ 和 $<0$ 实际上对称，故只对当前后缀和 $>n$ 的部分讨论，此时枚举的 $x_i\ge 0$。这意味着，我们需要找到一个之前钦定符号为 $+1$ 的位置 $j$，将其符号变为 $-1$。此操作会在原先基础上使 $[1,j]$ 的后缀和全部减去 $2$。因为我们要保持序列合法，所以位置 $j$ 必须满足所有 $[i,j]$ 的后缀和都 $\ge 0$。记位置 $k$ 上后缀和为 $s_k$，则该限制等价于 $\min_{k=i}^js_k\ge 2$。显然所有符合此条件的位置 $j$ 为一段连续的区间，则我们可以线段树维护 $s$ 使用二分找出这段区间的两端，记为 $l$ 和 $r$。  

  我们要在 $[l,r]$ 中将某个正的贡献变为负的，于是贪心地选择 $x$ 最小的位置进行变化；若有多个最小值，则任选其一，不会对我们后续的贪心造成负影响。随后将其符号钦定为负。  

  上述过程容易使用线段树维护。最后还原符号序列，统计答案是 $+$ 则加 $x$，是 $-$ 则减 $x$ 即可。时间复杂度 $O(\sum m\log_2^2m)$。  
## 代码
  - 实现略微不同于思路，仅供参考；
  - 实现很长，但大部分代码作用类似，相差无几。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define LOCAL
#ifdef LOCAL
#define debug(format, args...) fprintf(stderr,\
"[\tLOG](Func:%s(), Line:%d): "   \
, __FUNCTION__, __LINE__);       \
fprintf(stderr, format"\r\n", ##args)
#else
#define debug(format, args...)  do {} while (0)
#endif
//#define endl "\n"
#define LL long long
#define fer(i, a, b, args...) for(int i = (a), ##args; i <= (b); i ++)
#define fel(i, a, b, args...) for(int i = (a), ##args; i >= (b); i --)
const int N = 3e5 + 10; 
#define INF 0x3f3f3f3f
int T; 
int n, m; 
int a[N]; 
struct tree_Segment {
	struct Tree_node {
		int l, r; 
		int mxp, mnp; //分别存储当前位置的后缀和的最大值与最小值
		pair<int, int> mx, mn; //分别存储当前位置负数的最大值及位置和正数的最小值及位置
		int lz; 
	} s[N * 4]; 
#define Ls(i) (i << 1)
#define Rs(i) ((i << 1) | 1)
	inline void push_up(int i) {
		s[i].mxp = max(s[Ls(i)].mxp, s[Rs(i)].mxp); 
		s[i].mnp = min(s[Ls(i)].mnp, s[Rs(i)].mnp); 
		s[i].mx = max(s[Ls(i)].mx, s[Rs(i)].mx); 
		s[i].mn = min(s[Ls(i)].mn, s[Rs(i)].mn); 
	}
	inline void a_lazy(int i, int lz) {
		s[i].mxp += lz; 
		s[i].mnp += lz; 
		s[i].lz += lz; 
	}
	inline void push_down(int i) {
		if(s[i].lz) {
			a_lazy(Ls(i), s[i].lz); 
			a_lazy(Rs(i), s[i].lz); 
			s[i].lz = 0; 
		}
	}
	inline void build(int i, int l, int r) {
		s[i].l = l, s[i].r = r; 
		s[i].mxp = s[i].mnp = 0; 
		s[i].mx = {-INF, i}; s[i].mn = {INF, i}; 
		s[i].lz = 0; 
		if(l == r) 
			return ; 
		int mid = l + r >> 1; 
		build(Ls(i), l, mid); 
		build(Rs(i), mid + 1, r); 
		push_up(i); 
	}
	inline int querymxp(int i, int l, int r) {
		if(s[i].l >= l && s[i].r <= r) 
			return s[i].mxp; 
		push_down(i); 
		int ans = -INF; 
		if(s[Ls(i)].r >= l) ans = max(ans, querymxp(Ls(i), l, r)); 
		if(s[Rs(i)].l <= r) ans = max(ans, querymxp(Rs(i), l, r)); 
		return ans; 
	}
	inline int querymnp(int i, int l, int r) {
		if(s[i].l >= l && s[i].r <= r) 
			return s[i].mnp; 
		push_down(i); 
		int ans = INF; 
		if(s[Ls(i)].r >= l) ans = min(ans, querymnp(Ls(i), l, r)); 
		if(s[Rs(i)].l <= r) ans = min(ans, querymnp(Rs(i), l, r)); 
		return ans; 
	}
	inline pair<int, int> querymxval(int i, int l, int r) {
		if(s[i].l >= l && s[i].r <= r) 
			return s[i].mx; 
		push_down(i); 
		pair<int, int> ans = {-INF, -INF}; 
		if(s[Ls(i)].r >= l) ans = max(ans, querymxval(Ls(i), l, r)); 
		if(s[Rs(i)].l <= r) ans = max(ans, querymxval(Rs(i), l, r)); 
		return ans; 
	}
	inline pair<int, int> querymnval(int i, int l, int r) {
		if(s[i].l >= l && s[i].r <= r) 
			return s[i].mn; 
		push_down(i); 
		pair<int, int> ans = {INF, INF}; 
		if(s[Ls(i)].r >= l) ans = min(ans, querymnval(Ls(i), l, r)); 
		if(s[Rs(i)].l <= r) ans = min(ans, querymnval(Rs(i), l, r)); 
		return ans; 
	}
	inline void add(int i, int l, int r, int v) {
		if(s[i].l >= l && s[i].r <= r) {
			a_lazy(i, v); 
			return ; 
		}
		push_down(i); 
		if(s[Ls(i)].r >= l) add(Ls(i), l, r, v); 
		if(s[Rs(i)].l <= r) add(Rs(i), l, r, v); 
		push_up(i); 
	}
	inline void change(int i, int x, int c, int v) {
		if(s[i].l == s[i].r) {
			if(c < 0) {//opt:-
				s[i].mx = {v, x}; 
				s[i].mn = {INF, x}; 
			} else {//opt:+
				s[i].mx = {-INF, x}; 
				s[i].mn = {v, x}; 
			}
			return ; 
		}
		push_down(i); 
		if(s[Ls(i)].r >= x) change(Ls(i), x, c, v); 
		else change(Rs(i), x, c, v); 
		push_up(i); 
	}
#undef Ls
#undef Rs
} s; 
signed main() { 
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr); 
	cin >> T; 
	while(T --) {
		cin >> n >> m; 
		fer(i, 1, m) cin >> a[i]; 
		int cs = 0; 
		LL ans = 0; 
		s.build(1, 1, m); 
		fel(i, m, 1) {
			if(a[i] >= 0) {
				ans += a[i]; 
				cs ++; 
				s.add(1, 1, i, 1); 
				s.change(1, i, 1, a[i]); 
				if(cs <= n) continue; 
				cs -= 2; 
				int l = i, r = m, mid, cl = -1, cr = -1; 
				while(l <= r) {
					mid = l + r >> 1; 
					if(s.querymnp(1, i, mid) >= 2) {
						cr = mid; 
						l = mid + 1; 
					} else r = mid - 1; 
				}
				l = i, r = cr; 
				while(l <= r) {
					mid = l + r >> 1; 
					if(s.querymnp(1, i, mid) >= 2) {
						cl = mid; 
						r = mid - 1; 
					} else l = mid + 1; 
				}
				int t = s.querymnval(1, cl, cr).second; 
				s.add(1, 1, t, -2); 
				s.change(1, t, -1, a[t]); 
				ans -= 2 * a[t]; 
			} else {
				ans -= a[i]; 
				cs --; 
				s.add(1, 1, i, -1); 
				s.change(1, i, -1, a[i]); 
				if(cs >= 0) continue; 
				cs += 2; 
				int l = i, r = m, mid, cl = -1, cr = -1; 
				while(l <= r) {
					mid = l + r >> 1; 
					if(s.querymxp(1, i, mid) <= n - 2) {
						cr = mid; 
						l = mid + 1; 
					} else r = mid - 1; 
				}
				l = i, r = cr; 
				while(l <= r) {
					mid = l + r >> 1; 
					if(s.querymxp(1, i, mid) <= n - 2) {
						cl = mid; 
						r = mid - 1; 
					} else l = mid + 1; 
				}
				int t = s.querymxval(1, cl, cr).second; 
				s.add(1, 1, t, 2); 
				s.change(1, t, 1, a[t]); 
				ans += 2 * a[t]; 
			}
		}
		cout << ans << endl; 
	}
	return 0; 
}
```

---

## 作者：Erine (赞：1)

终于自己做出一个 slope trick 题了。

发现等价于给每个数赋正负号求和。而合法正负分配方法的充要条件是把正看成 $+1$，负看成 $-1$，所有后缀和都在 $[0,n]$ 之间。

于是翻转序列并设计 dp：$f_{i,j}$ 表示前 $i$ 个，和为 $j$ 的最大总和。

$$f_{i,j}=\max\{f_{i-1,j-1}+a_i,f_{i-1,j+1}-a_i\}$$

画画图发现其实 $f_i$ 是关于 $j$ 上凸的。

![](https://cdn.luogu.com.cn/upload/image_hosting/mtpemy9f.png)

并且结合图像发现其实对于 $j$ 的一段前缀是采取了后者的转移，而剩余的后缀是前者转移。

列出方程发现我们只需要在间距为 $2$ 的差分上二分出一个位置，前半部分 $\ge 2a_i$，后半部分 $\lt 2a_i$ 即可。然后可以选一个你喜欢的数据结构维护这个差分。

$\Theta(n\log n)$。~~纯口胡代码还没写。~~ 写完了，800B。

```cpp
void solve() {
	cin >> n >> m;
	rep(i, 1, m) cin >> a[i];
	reverse(a + 1, a + 1 + m);
	multiset<int> s; int now = 0;
	rep(i, 1, m) {
		if (i & 1) now += max(a[i], (s.size() ? *prev(s.end()) : (int) -1e18) - a[i]);
		else now -= a[i];
		int dc = min((n - (i - 1 & 1)) / 2, (i - 1) / 2), nc = min((n - (i & 1)) / 2, i / 2);
		s.insert(a[i] * 2);
		if (nc == dc) {
			if (i & 1) s.erase(prev(s.end()));
			else s.erase(s.begin());
		} else if (nc < dc) {
			s.erase(s.begin());
			s.erase(prev(s.end()));
		}
	}
	for (int i : s) if (i > 0) now += i; 
	cout << now << endl;
}
```

---

## 作者：lhc0707 (赞：0)

正着做会导致前面定了符号的 $x_i$ 被取反这很不好维护，反着做就没有这样的问题所以把序列取反后缀改前缀，假设符号序列为 $\{k_n\}$，那么这个序列合法当且仅当 $\forall i\in [1,n],0\leq\sum_{j=1}^ik_i\leq n$，于是枚举这个值，设 $f_{i,j}$ 表示考虑到 $x_i$，$k_i$ 的前缀和为 $j$ 的答案，有转移 
$$dp_{i,j}=\max\{dp_{i-1,j-1}+x_i,dp_{i-1,j+1}-x_i\}$$
发现这相当于关于 $j$ 的函数 $dp_{i,j}$ 和 ${-x_i,x_i}$ 做 $(\max,+)$ 卷积（钦定 $-x_i$ 的下标为 -1，$x_i$ 下标是 1），考虑归纳证明 $f_i(j)=dp_{i,j}$ 的凸性。

对于 $f_0$ 凸性显然，对于 $i-1\rightarrow i$ 的转移由 Minkowski 和经典结论可知如果 $f_{i-1}$ 是凸的那么 $f_i$ 也是凸的，由归纳原理凸性得证。

用闵和的方式维护差分的形式是不可行的，考虑 slope-trick 地维护拐点，考虑一次转移 $i-1\rightarrow i$ 的影响，发现这种两边向中间的平移不好维护，考虑先把答案减去 $\sum x_i$，这样先把 $f_{i-1}$ 平移，然后 $dp_{i,j}=\max\{dp_{i,j},dp_{i-1,j-2}+2x_i\}$，又发现 $dp_{i,j}$ 有值当且仅当 $i,j$ 奇偶性相同，于是 $j-2\rightarrow j$ 可以改成 $j-1\rightarrow j$，改一下范围即可，弄明白这些就可以 multiset 维护拐点做了。

代码：

```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define eps 1e-8
#define fi first
#define se second
#define pn putchar(10)
#define pp putchar(' ')
#define pii pair<int, int>
#define pdi pair<ll, ll>
#define mem(aa, bb) memset(aa, bb, sizeof(aa))
#define fo(i, a, b) for (int i = (a); i <= (b); ++i)
#define Fo(i, a, b) for (int i = (a); i >= (b); --i)
#define pb push_back
#define reg register
#define eb emplace_back
#define bct __builtin_popcount
#define mk make_pair
#define IT iterator
#define all(x) x.begin(), x.end()
#define lbd lower_bound
#define ubd upper_bound
#define lowbit(x) ((x) & (-(x)))
#define gb(x, i) ((x >> i) & 1)
#define IOS cin.tie(0)->sync_with_stdio(false), cout.tie(0)
#define FILE(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)
using namespace std;

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128 i128;
typedef __uint128_t u128;
typedef double db;
typedef long long ll;

// #define getchar getchar_unlocked
// #define putchar putchar_unlocked

// clang-format off
template <class T> inline void read(T &s)
{
 s = 0; reg int f = 1; reg char c = getchar(); while (!isdigit(c)) f ^= (c == '-'), c = getchar();
 while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar(); s = f ? s : -s;
}
template <class T> inline void wr(T x)
{
 if (x < 0) putchar('-'), x = -x; int buf[21], top = 0; while (x) buf[++top] = x % 10, x /= 10;
 if (!top) buf[++top] = 0; while (top) putchar(buf[top--] ^ '0');
}
template <class T> inline bool ckmn(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <class T> inline bool ckmx(T &a, T b) { return a < b ? a = b, 1 : 0; }
template <class T, class... A> inline void read(T &x, A &...a) { read(x), read(a...); }
template <class T, class... A> inline void ckmn(T &x, T y, A &...a) { return ckmn(x, y) | ckmn(x, a...); }
template <class T, class... A> inline void ckmx(T &x, T y, A &...a) { return ckmx(x, y) | ckmx(x, a...); }

const ll NN = 1e6 + 5, mod = 1e9 + 9;
ll Pre[NN], Inv[NN];
inline ll qpow(ll a, ll b) { return !b ? 1ll : qpow(a * a % mod, b >> 1) * ((b & 1) ? a : 1ll) % mod; }
inline ll C(ll n, ll m) { return (n < m || m < 0) ? 0 : Pre[n] * Inv[m] % mod * Inv[n - m] % mod; }
inline void InitC(int n) { Pre[0] = Inv[0] = 1; fo(i, 1, n) Pre[i] = Pre[i - 1] * i % mod; Inv[n] = qpow(Pre[n], mod - 2); Fo(i, n - 1, 1) Inv[i] = Inv[i + 1] * (i + 1) % mod; }// clang-format on

const int N = 300005;
int n, m, x[N];
signed main()
{
 int T;
 read(T);
 while (T--)
 {
  read(n, m);
  fo(i, 1, m) read(x[m - i + 1]);
  multiset<int, greater<int>> se;
  ll v0 = 0, ans;
  fo(i, 1, m)
  {
   se.insert(2 * x[i]), v0 -= x[i];
   if (i & 1) v0 += *se.begin(), se.erase(se.begin());
   while (se.size() >= (i & 1 ? (n + 1) >> 1 : (n + 2) >> 1)) se.erase(prev(se.end()));
  }
  ans = v0;
  for (int x : se) v0 += x, ckmx(ans, v0);
  wr(ans), pn;
 }
 return 0;
}
```

---

## 作者：tony0530 (赞：0)

先考虑最普通的 dp 设 $f_i(j)$ 表示后 $i$ 个数中，取反个数减去未取反个数为 $j$，那么转移方程式为：

- 如果 $j = 0$，$f_i(j) = f_{i - 1}(j+1) - a_i$。
- 如果 $1 \le j \le n - 1$，$f_i(j) = \max(f_{i-1}(j+1) - a_i, f_{i - 1}(j -1) + a_i)$。
- 如果 $j = n$，$f_i(j) = f_{i -1}(j-1) + a_i$。

边界如下：

- 如果 $i=0$，$f_0(i) = 0$。
- 如果 $i \not= 0$，$f_0(i) = -\infty$。

这很明显，时间复杂度不对呀，那怎么办，slope trick 呀！我们可以发现 $f_i(x)$ 是一个上凸包，我们可以使用一个 multiset 维护相邻的差值，并用另一个维护第一个点的具体数值是多少，最后对所有点取最大值就可以了。

上面搞懂了，代码实现就简单了~~所以就不放了哈~~，代码可以去看别人的。

---

