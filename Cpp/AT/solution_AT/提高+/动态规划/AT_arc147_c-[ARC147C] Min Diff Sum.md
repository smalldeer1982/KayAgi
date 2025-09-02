# [ARC147C] Min Diff Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc147/tasks/arc147_c

$ 1,2,\ldots\ ,N $ の番号のついた $ N $ 人の人を数直線上に並べます。人 $ i\,(1\ \leq\ i\ \leq\ N) $ がいる地点の座標を $ x_i $ としたとき、 $ x_i $ は $ L_i $ 以上 $ R_i $ 以下の整数である必要があります。複数の人が同じ座標にいても構いません。

ここで、並べ方の**不満度**を以下の式で定義します。

> $ \displaystyle\sum_{i=1}^{N-1}\sum_{j=i+1}^{N}|x_j-x_i| $

不満度としてあり得る値の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ 10^7\ \,(1\ \leq\ i\ \leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

$ x_1=3,x_2=4,x_3=5 $ とすると、不満度は $ 4 $ です。不満度を $ 3 $ 以下にすることはできないので、$ 4 $ を出力します。

## 样例 #1

### 输入

```
3
1 3
2 4
5 6```

### 输出

```
4```

## 样例 #2

### 输入

```
3
1 1
1 1
1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
6
1 5
2 4
1 1
4 4
3 6
3 3```

### 输出

```
15```

# 题解

## 作者：灵茶山艾府 (赞：3)

以下描述，下标从 $0$ 开始。

### 提示 1

设答案为 $s$。

假设 $x$ 是个有序数组（递增），那么绝对值符号可以去掉，从而化简公式：

$$
\begin{aligned}
s =\ &(n-1)(x[n-1]-x[0]) + (n-3)(x[n-2]-x[1]) + \cdots\\
=\ &\sum_{i=0}^{\lfloor n/2 \rfloor-1}  (n-1-2i)(x[n-1-i]-x[i])
\end{aligned}
$$

### 提示 2

既然 $x$ 有序很有用，那么怎样可以「把 $x$ 排序」呢？

或者想一想，$x[0]$ 在哪个区间？$x[n-1]$ 在哪个区间？

如果把这些闭区间粗略地排序，那么 $R[i]$ 越小的区间应该越靠左排，$L[i]$ 越大的区间应该越靠右排。

### 提示 3

为了让 $s$ 尽量小，$x[0]$ 要尽量大，$x[n-1]$ 要尽量小。

$x[0]$ 最大是多少？$x[n-1]$ 最小是多少？

最小的 $R[i]$ 即为最大的 $x[0]$。

最大的 $L[i]$ 即为最小的 $x[n-1]$。

如果 $x[0] < x[n-1]$，那么去掉这两个数（区间），问题变成一个规模更小（$n-2$）的子问题。

否则，这些区间的交集不为空，所有 $x[i]$ 都可以取到同一个数。

```go
package main
import("bufio";."fmt";"os";"sort")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, ans int
	Fscan(in, &n)
	l := make([]int, n)
	r := make([]int, n)
	for i := range l {
		Fscan(in, &l[i], &r[i])
	}
	sort.Sort(sort.Reverse(sort.IntSlice(l))) // 从大到小排
	sort.Ints(r) // 从小到大排
	for i := 0; l[i] > r[i]; i++ {
		ans += (n - 1 - i*2) * (l[i] - r[i])
	}
	Print(ans)
}
```

时间复杂度：$\mathcal{O}(n\log n)$。瓶颈在排序上。


---

## 作者：dyc2022 (赞：2)

一个妙的题。

首先，式子里面有一个很烦的绝对值。考虑将绝对值去掉，这样就可以用一个多项式来表达它，从而也好求每个元素的贡献。

我们注意到，当我们得到 $a$ 序列后，答案是和其顺序无关的。因此，我们令 $\{b_1,b_2,\dots,b_n\}$ 为将序列 $\{a_1,a_2,\dots,a_n\}$ 升序排序得到的序列。则我们可以把绝对值去掉：

$$\sum_{i=1}^{n}\sum_{j=i+1}^{n} \left| a_i - a_j \right| = \sum_{i=2}^{n}\sum_{j=1}^{i-1} (b_i - b_j)$$

进一步化开，观察每一个 $b_i$ 的贡献（即其系数），得：

$$\sum_{i=1}^{\frac{n}{2}}(n-i \times 2 + 1)(b_{n-i+1} - b_i)$$

那么我们就可以贪心地赋值了。我们想要让 $b_{n-i+1}$ 尽可能小，$b_i$ 尽可能大。所以，我们可以将题目给的区间进行排序，按左端点降序，右端点升序分别排一次。然后直接选端点就能得到最小的代价。

那么这题就做完了，代码奇短：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 300006
using namespace std;
int n,l[N],r[N],ans;
main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&l[i],&r[i]);
	sort(l+1,l+1+n,[](int x,int y){return x>y;}),sort(r+1,r+1+n);
	for(int i=1;i<=n&&l[i]>r[i];i++)ans+=(n-2*i+1)*(l[i]-r[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Getaway_Car (赞：1)

本文提供一种另类做法。~~虽然我的代码从实现以及常数上都更劣一些。~~

考虑原式的几何意义，即在数轴上的 $n$ 个区间内各选一个点使得这 $n$ 个点两两距离之和最小。

考虑什么时候距离之和最小，显然是所有点都尽量向某一个位置靠拢时。所以钦定中心点，让其它所有点都尽量向这个点靠拢，再暴力计算贡献。时间复杂度 $O(n^2V)$。

注意到，中心点取在非端点显然时不会更优，所以可以离散化。时间复杂度 $O(n^3)$ 。

现在考虑优化计算原式的过程。考虑拆贡献。$n$ 个点把数轴分成 $n - 1$ 条线段（以及两条射线）,那么第 $i$ 条线段就会被计算 $i \cdot (n - i)$ 次。这是显然的。那么我们可以现将这 $n$ 个点排序，再按上述过程计算。时间复杂度 $O(n^2 \log n)$。

容易发现，在中心点移动的过程中，有许多点的位置并不会随着中心点位置的改变而改变，所以考虑动态维护每个点的位置以及贡献。设当前中心点位置为 $pos$，可以把 $n$ 个点分成 $3$ 段：

- $r_i \lt pos$，这些点的位置固定在了 $r_i$，不会再改变。

- $l_i \le pos \le r_i$，这些点的位置会随着中心点位置的改变而改变，且它们的位置都是 $pos$。

- $pos \lt l_i$，这些点的位置暂时固定在了 $l_i$。

那么我们可以动态维护这三段的端点。当 $pos$ 遇到了一个左端点时，相当于将一个点从第三段移到第二段；当 $pos$ 遇到了一个右端点时，相当于把一个点从第二段移到了第一段。

在此同时，动态维护每段内部的贡献。第一三段的贡献只需要在遇到端点时更新，第二段内部显然没有贡献。$总贡献 = 第一段的贡献 + 一二段交界处贡献 + 二三段交界处贡献 + 第三段的贡献$。

于是这道题就做完了。

[提交记录](https://atcoder.jp/contests/arc147/submissions/66184899)。

---

## 作者：analysis (赞：1)

好久没打 ARC 了，谁便选了一道题写了一下，还是比较好想的。

显然：

$$
ans = \sum_{i=2}^{n}\sum_{j=1}^{i-1}a_i-a_j
$$

$A\{a_i\}$ 是 $X\{x_i\}$ 排序后的序列。

然后观察一下，发现：

$$
ans = (n-1)(a_n - a_1) + (n-3)(a_{n-1}-a_{2}) + \cdots
$$

所以左边贪心的取能取得的最大值，右边贪心的取能取得最小值一定最优。

然后特殊的，左边取到的值如果不比右边取到的值小，剩下位置都可以取到一起，此时贡献为 $0$。

记得开 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
bool vis[300005];
priority_queue<pii> ql;
priority_queue<pii,vector<pii>,greater<pii> > qr;
int n;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int l,r;
        cin>>l>>r;
        qr.push(pii(r,i));
        ql.push(pii(l,i));
    }
    int ans = 0;
    while(1)
    {
        while(!qr.empty() && vis[qr.top().second])qr.pop();
        while(!ql.empty() && vis[ql.top().second])ql.pop();
        if(qr.top().first >= ql.top().first)break;
        int x = qr.top().second,y = ql.top().second;
        vis[x] = vis[y] = 1;
        ans += (n-1) * (ql.top().first - qr.top().first);
        n -= 2;
        ql.pop();
        qr.pop();
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Phartial (赞：1)

考虑最终答案中，最左端和最右端的两个数，这两个数应该尽量往中间走，因为这样肯定能使答案更优。

最左端最大只能取到最小的右端点，因为再往右的话最小的右端点对应的区间对应的数就肯定会落在最左端的左边，这是不可以的。

同理，最右端最小只能取到最大的左端点。

可以发现定下这两个点后，剩下的点对答案的贡献就是这两个点的距离。所以把这一部分加上后问题就变成了一个 $n'=n-2$ 的子问题，递归处理即可。

细节：如果最右端小于最左端，那么说明所有区间都有交，直接在交区间里选一个点，让所有数都等于这个点即可，贡献为 $0$。

实现时可以把左端点和右端点单独排序，循环扫一遍即可。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;
using Pii = pair<int, int>;

const int kN = 3e5 + 1;

int n;
Pii a[kN], b[kN];
LL ans;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].first >> a[i].second;
    b[i] = a[i];
  }
  sort(a + 1, a + n + 1, [](Pii i, Pii j) { return i.first > j.first; });
  sort(b + 1, b + n + 1, [](Pii i, Pii j) { return i.second < j.second; });
  for (int i = 1; i <= n && a[i].first > b[i].second; ++i) {
    ans += 1LL * (a[i].first - b[i].second) * (n - i - i + 1);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# ARC147C 题解

## 思路分析

考虑最大的 $L$ 值所属的线段 $x$ 和最小的 $R$ 值所属的线段 $y$

- 如果 $L_x\le R_y$

显然，所有点都可以塞到中间的某一个点去，此时答案为 $0$

- 如果 $L_x>R_y$

此时考虑区间 $[R_y,L_x]$，假设区间 $i$ 选择的点为 $p_i$

注意到 $p_y\le R_y<L_x\le p_x$，因此所有区间都可以放到 $[p_y,p_x]$ 中，故此时的答案为，其中 $f$ 为剩下 $n-2$ 条线段的答案：

$$
\begin{aligned}
f+|p_x-p_y|+\sum_{i=1}^{n,i\neq l,r} |p_i-p_x|+|p_i-p_y|
&=f+(p_x-p_y)(n-1)\\
&\ge f+(L_x-R_y)(n-1)
\end{aligned}
$$

因此每次递归求解剩下的线段即可，分别对 $L,R$ 降序和升序排序，则第 $i$ 组对答案的贡献是 $f_i=(l_i-r_i)(n-i\times 2+1)$

$$
\text{Answer}=\sum_{i=1}^{n} [f_i>0]\times f_i
$$

直接计算，时间复杂度 $\Theta(n\log n)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=3e5+1;
int l[MAXN],r[MAXN];
signed main() {
	int n,res=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld%lld",&l[i],&r[i]);
	sort(l+1,l+n+1,greater<int>());
	sort(r+1,r+n+1,less<int>());
	for(int i=1;i<=n&&n-i*2+1>0&&l[i]-r[i]>0;++i) res+=(l[i]-r[i])*(n-i*2+1);
	printf("%lld\n",res);
	return 0;
} 
```



---

## 作者：jiayixuan1205 (赞：0)

## 题解：AT_arc147_c [ARC147C] Min Diff Sum
### 算法
贪心
### 分析
考虑绝对值这个东西是不好处理的，因此我们把他它拆开。
在什么情况下是可以没有绝对值的呢？我们思考这个式子实质上在两两之间都会发生，因此直接从小到大排序后直接选取即可。
接下来我们需要对这个求和式子进行转化使其有更明显的特征，我们可以把它转化为：
$$ \sum\limits_{i=1}^{\left\lfloor\frac{n}{2}\right\rfloor}(n-2\times i+1)(a_{n-i+1}-a_i)$$
那么我们只需要前者小后者大就可以获取到最小值了。只需要把存左端点和右端点的数分别贪心选取即可。如果当前的两个点前者的左端点比后者的右端点小呢？这说明两个区间存在交点，于是最优的方法就是他俩重合，不产生贡献，否则前者选左端点后者选右端点直接计算即可。
有没有可能排序完之后选到了同一个区间呢？考虑右端点小的左端点只会更小，左端点大的左端点只会更大，因此可以保证选取的一定不相同。
### 代码展示
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 3e5+10;
int n;
int l[N],r[N];

inline bool cmp(int x,int y)
{
    return x>y;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
    sort(r+1,r+n+1);
    sort(l+1,l+n+1,cmp);
    int ans=0;
    for(int i=1;i<=n/2;i++)
    {
        if(l[i]<r[i]) continue;
        else ans+=(n-i*2+1)*(l[i]-r[i]);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

