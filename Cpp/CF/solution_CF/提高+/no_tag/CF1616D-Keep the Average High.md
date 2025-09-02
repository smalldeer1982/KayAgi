# Keep the Average High

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ and an integer $ x $ .

You need to select the maximum number of elements in the array, such that for every subsegment $ a_l, a_{l + 1}, \ldots, a_r $ containing strictly more than one element $ (l < r) $ , either:

- At least one element on this subsegment is not selected, or
- $ a_l + a_{l+1} + \ldots + a_r \geq x \cdot (r - l + 1) $ .

## 说明/提示

In the first example, one valid way to select the elements is $ [\underline{1}, 2, \underline{3}, \underline{4}, \underline{5}] $ . All subsegments satisfy at least one of the criteria. For example, for the subsegment $ l = 1 $ , $ r = 2 $ we have that the element $ 2 $ is not selected, satisfying the first criterion. For the subsegment $ l = 3 $ , $ r = 5 $ we have $ 3 + 4 + 5 = 12 \ge 2 \cdot 3 $ , satisfying the second criterion.

We can't select all elements, because in this case for $ l = 1 $ , $ r = 2 $ all elements are selected and we have $ a_1 + a_2 = 3 < 2 \cdot 2 $ . Thus, the maximum number of selected elements is $ 4 $ .

In the second example, one valid solution is $ [\underline{2}, \underline{4}, 2, \underline{4}, \underline{2}, \underline{4}, 2, \underline{4}, \underline{2}, \underline{4}] $ .

In the third example, one valid solution is $ [\underline{-10}, -5, \underline{-10}] $ .

In the fourth example, one valid solution is $ [\underline{9}, \underline{9}, -3] $ .

## 样例 #1

### 输入

```
4
5
1 2 3 4 5
2
10
2 4 2 4 2 4 2 4 2 4
3
3
-10 -5 -10
-8
3
9 9 -3
5```

### 输出

```
4
8
2
2```

# 题解

## 作者：activeO (赞：20)

## 题目大意

给一个数组，让你选择数组中的最大元素数，使得任意一段区间 $ [l,r] $ 满足：

$ a_l + a_{l+1} + ... + a_{r-1} + a_r \geq x \cdot (r - l + 1) $

## 思路

将 $ a_i \gets a_i-x (i \in [1,n]) $，这样就只要满足 $ a_l + a_{l+1} + ... + a_{r} \geq 0 $。

对于 $ a_i (i \in [2,n]) $ ，如果 $ a_i+a_{i-1}+a_{i-2} < 0 \&\& a_i+a_{i-1} < 0 $ ，显然就不会选 $ a_i $ 了，那么我们就 $ a_i \gets +\infty $。

代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=5e4+10;
const int inf=0x3f3f3f3f;
int a[maxn];

int main(){
	
	int t;
	
	scanf("%d",&t);
	
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int ans=n,x;
		scanf("%d",&x);
		for(int i=1;i<=n;i++) a[i]-=x;
		for(int i=2;i<=n;i++){
			if(a[i]+a[i-1]<0||a[i]+a[i-1]+a[i-2]<0){
				ans--;
				a[i]=inf;
			}
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：9)

一道很可爱的珂爱题。

## 题目简述
- 给一个 $\{a_n\}$，选一些数使得对任意的 $1\leq l<r\leq n$，如果 $a_l,a_{l+1}\dots a_{r}$ 都选中则有 $\sum_l^ra_i\geq(r-l+1)\times x$。
- 求做多能选出多少个数。
- 多组数据，$t\leq10,n\leq5\times 10^4$。

## 题目分析

首先我们把所有的 $a_i\Leftarrow a_i-x$。这样我们只要讨论 $\sum_l^ra_i\geq0$ 即可。

根据裴蜀定理，我们只要长度为 $2,3$ 的子串都满足条件就可以让所有的被选中子串都满足条件。

下面使用 $\text{dp}$。

假设 $f_i,g_i,h_i$ 分别表示在前 $i$ 个数中没有选 $a_i$；选了 $a_i$ 但没选 $a_{i-1}$；选了 $a_i,a_{i-1}$ 时选数的最大值。

显然得到转移方程（$\LaTeX$ 不好表达，看代码罢）
```cpp
f[i]=max(max(f[i-1],g[i-1]),h[i-1]);
g[i]=f[i-1]+1;
if(a[i]+a[i-1]>=0)
	h[i]=max(h[i],g[i-1]+1);
if(i>=2&&a[i]+a[i-1]+a[i-2]>=0&&a[i]+a[i-1]>=0)
	h[i]=max(h[i],h[i-1]+1);
```
这样就完结撒花了。

## 参考代码

[link](https://www.luogu.com.cn/paste/4yeplefd)

---

## 作者：周小涵 (赞：6)

给一个没有脑子的简单做法，直接上数据结构即可。

设 $s_i$ 为 $\sum_{j=1}^{i}a_j-ix$

$\sum_{i=l}^{r}a_i\ge(r-l+1)x$ 可以化成 $s_r \ge s_{l-1}$

设 $f_i$ 表示前 $i$ 个数最多可以取多少个。

我们有 $f_i = \max f_{j-1} + i - j$，

其中 $j$ 满足 $\max_{k=j}^{i-2}to_k \ge i$ 即可。

其中 $to_j$ 表示 $j$ 跳过 $j+1$ 后到比 $s_j$ 大的地方的最远位置。

这个 $to_j$ 可以 二分 + st 表 解决，转移的时候往前二分，再用一个线段树维护 $f_i$ 的最值，二分完后只要查一个区间 $f_i$ 的最值即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,a[N],s[N],t[N],f[N],k,m;
int to[N],st[N][19],st0[N][19],lg[N];
int ask(int l,int r){
    int k=lg[r-l+1];
    return min(st[l][k],st[r-(1<<k)+1][k]);
}
int ask0(int l,int r){
    int ret=0x3f3f3f3f;
    if(l==0&&r==0)return to[0];
    if(l==0)ret=min(ret,to[0]),l++;
    int k=lg[r-l+1];
    return min(ret,min(st0[l][k],st0[r-(1<<k)+1][k]));
}
int mx[N<<2];
void change(int p,int l,int r,int x,int v){
    if(l==r){mx[p]=max(mx[p],v);return;}
    int mid=l+r>>1;
    if(x<=mid)change(p<<1,l,mid,x,v);
    else change(p<<1|1,mid+1,r,x,v);
    mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
int query(int p,int l,int r,int x,int y){
    if(x<=l&&y>=r)return mx[p];
    int mid=l+r>>1,ret=-(0x3f3f3f3f);
    if(x<=mid)ret=max(ret,query(p<<1,l,mid,x,y));
    if(y>mid)ret=max(ret,query(p<<1|1,mid+1,r,x,y));
    return ret;
}
void solve(){
    memset(mx,-0x3f,sizeof(mx));
    memset(to,0,sizeof(to));
    scanf("%lld",&n);
    for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
    scanf("%lld",&k);
    for(int i=1;i<=n;i++)t[i]=s[i]-i*k;t[n+1]=0;
    sort(t+1,t+n+2);
    m=unique(t+1,t+n+2)-t-1;
    for(int i=0;i<=n;i++)s[i]=lower_bound(t+1,t+m+1,s[i]-i*k)-t;
    for(int i=1;i<=n;i++)st[i][0]=s[i];
    for(int j=1;j<=lg[n];j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    for(int i=0;i<=n;i++){
        int l=i+2,r=n,st=l;
        while(l<=r){
            int mid=l+r>>1;
            if(ask(st,mid)>=s[i])l=mid+1;
            else r=mid-1; 
        }to[i]=r;
    }
    for(int i=1;i<=n;i++)st0[i][0]=to[i];
    for(int j=1;j<=lg[n];j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st0[i][j]=min(st0[i][j-1],st0[i+(1<<(j-1))][j-1]);
    f[0]=0;f[1]=1;int ans=1;
    change(1,0,n,0,f[0]);
    for(int i=2;i<=n;i++){
        f[i]=max(f[i-1],f[i-2]+1);
        int l=0,r=i-2;
        while(l<=r){
            int mid=l+r>>1;
            if(ask0(mid,i-2)>=i)r=mid-1;
            else l=mid+1;
        }
        f[i]=max(f[i],query(1,0,n,l,i-2)+i);
        change(1,0,n,i-1,f[i-2]-(i-1));
        ans=max(ans,f[i]);
    }cout<<ans<<endl;
}
signed main(){
    int T;scanf("%lld",&T);
    while(T--)solve();
    return 0;
}
```

---

## 作者：CmsMartin (赞：4)

[更好的阅读体验](http://cmsblog.top/archives/solution-cf1616f)

## 题目描述

[题目传送门](https://codeforces.com/problemset/problem/1616/D)

给定一个长 $n$ 的数列 $a$，再给定一个 $x$。你需要选中其中一些数，使得对于所有连续的被选中的长度至少为 $2$ 的子串 $[l,r] $ 满足：
$$
\sum_{i=l}^ra_i\ge (r-l+1)\times x
$$
求最多能选出多少个数。

## 思路

主要讲一下思考过程。首先肯定是将 $a_i$ 全部减掉 $x$。

接下来往下思考，所有的选中的长度大于等于 $2$ 的子串，这个条件很棘手，考虑找一个等价的简化命题。不难发现，可以转化为**所有长度等于 $2$ 和 $3$ 的子串和大于 $0$**，显然地，所有的长度大于等于 $2$ 的子串都可以分割为若干个长度为 $2$ 或 $3$ 的子串拼接起来。

然后我们发现，**对于一个数字的决策，只跟前两个数字的决策有关**，那么可以考虑**动态规划**。

设 $f_{i},g_{i},h_i$ 分别表示 $a_i$ 不取，$a_i$ 取但是 $a_{i-1}$ 不取，$a_i$ 取 $a_{i-1}$ 也取时的最大价值。

考虑转移。

对于 $f_i$ 和 $g_i$，转移都是很显然的：

$$
f_i = \max\{f_{i-1},g_{i-1},h_{i-1}\}
$$
$$
g_i=f_{i-1} + 1
$$

接下来看 $h_i$ 的转移：

加入第 $i$ 个是最后一段连续段的第 $3$ 个或更多时，当 $a_{i-2}+a_{i-1}+a_{i} \ge 0$ 且 $a_{i-1} + a_i \ge 0$ 时才可以选，此时转移为：

$$
h_i=h_{i-1}+1
$$

加入第 $i$ 个是最后一段连续段的第 $2$ 个时，当  $a_{i-1} + a_i \ge 0$ 时才可以选，此时转移为：

$$
h_i=g_{i-1}+1
$$

然后这道题就做完了，时间复杂度为 $\Theta(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e4 + 10;

int T, A[MAXN], X,  N;
int Dp[3][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> N;
        A[0] = -1114514;
        for (int i = 1; i <= N; i++) {
            cin >> A[i];
        }
        cin >> X;
        for (int i = 1; i <= N; i++) {
            A[i] -= X;
        }
        memset(Dp, 0, sizeof Dp);
        for (int i = 1; i <= N; i++) {
            Dp[0][i & 1] = max({Dp[0][(i - 1) & 1], Dp[1][(i - 1) & 1], Dp[2][(i - 1) & 1]});
            Dp[1][i & 1] = Dp[0][(i - 1) & 1] + 1;
            if (A[i] + A[i - 1] >= 0) {
                Dp[2][i & 1] = Dp[1][(i - 1) & 1] + 1;
                if (i >= 2 && A[i - 2] + A[i - 1] + A[i] >= 0) {
                    Dp[2][i & 1] = max(Dp[2][i & 1], Dp[2][(i - 1) & 1] + 1);
                }
            }
        }
        cout << max({Dp[0][N & 1], Dp[1][N & 1], Dp[2][N & 1]}) << endl;
    }
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

首先设 $b_i=a_i-x$，这样原问题就转化为：给 $\{b\}$ 中 $c$ 个元素染色，使得 $\{b\}$ 中 任意 全染色 且 长度 $>1$ 的子串 中 元素值 之和 $\ge0$，求 $c$ 的最大值。

由于这些子串的定义太长，设全染色且长度 $>1$ 为 A 条件，全染色且长度 $=2$ 或 $3$ 为 B 条件。

**结论：$\{b\}$ 中任意满足 A 条件的子串元素值之和 $\ge0\iff\{b\}$ 中任意满足 B 条件的子串元素值之和 $\ge0$**

**证明：**

正推显然。

逆推。对于 $\{b\}$ 的任意满足 A 条件的子串，由裴蜀定理，总可以划分成多个满足 B 条件的子串，而满足 B 条件的子串元素值的和 $\ge0$，所以整个子串值之和 $\ge0$。

**证毕。**

由此，我们可以用简单的线性 Dp 实现 $O(n)$ 做法。$f(i,j,k)$ 表示当前遍历过到 $\{b\}$ 的前 $i$ 位，第 $i-1$ 位是（$j=1$）否（$j=0$）染色，第 $i$ 位是（$k=1$）否（$k=0$）染色，前 $i$ 位染色数目的最大值。

转移方程请自行思考（简单）。

---

## 作者：_xm_ (赞：1)

## [CF1616D Keep the Average High](https://codeforces.com/problemset/problem/1616/D)（\*2000）

题解区的贪心正确性证明有点跳，没看懂，所以想发一篇自己的思路供大家参考。

> 给定一个长 $n$ 的数列 $a$，再给定一个 $x$。你需要选中其中一些数，使得对于所有**连续的被选中的**长度至少为 $2$ 的子串 $[l,r]$ 满足：
>
> $$
> \sum_{i=l}^ra_i \ge (r-l+1) \times x
> $$
>
> 求最多能选出多少个数。

又是一道 Trick 题。

先做个转换，所有数减去 $x$ 之后判断区间是否 $\ge 0$。

们考虑贪心，能取就取，如果取不了就不管，把 $a_i$ 改成 $\infty$。

根据裴蜀定理，若 $x,y$ 取任意正整数，则 $2x + 3y = z$ 可以覆盖整个 $\mathbb{N}$。我们只要长度为 $2,3$ 的子串都满足条件就可以让所有的子串都满足条件。（注意是连续的被选中的子串需要满足条件，我最开始被绕晕了）

dp 的正确性比较显然，来证明一下贪心的正确性：

考虑相邻元素 $a_x,a_{x+1},a_{x+2}$，若选了 $a_x$ 导致 $a_{x+1}$ 不能选，则 $a_{x}$ 和 $a_{x+1}$ 一定都是负数。如果有其中有一个非负数，则选数的方案是唯一的，另一个负数只有能选或不能选两种情况，不会出现二选一的状态（不理解可以手玩一下）。

不选 $a_{x+1}$ 则一定可以选 $a_{x+2}$（长度为 $1$ 的区间），而选了 $a_{x+1}$ 会使 $a_{x+2}$ 往后的区间和变小，会影响到以后的选择，所以最优的方案是选 $a_{x}$。

---

## 作者：AC_love (赞：1)

我们发现：只要所有长度为 $2$ 和 $3$ 的子串满足条件的话，那么任意一个子串都是满足条件的。

因此我们只需要考虑三位其实就够了。

设 $f(i, 0)$ 表示对于前 $i$ 位，第 $i$ 位不选时最多选几个数。

$f(i, 1)$ 表示对于前 $i$ 位，第 $i$ 位选，第 $i - 1$ 位不选时最多选几个数。

$f(i, 2)$ 表示对于前 $i$ 位，第 $i$ 位与第 $i - 1$ 位都选时最多选几个数。

当第 $i$ 位不选时，前面两位可以随便选，因此 $f(i, 0)$ 的转移十分显然：

$$f(i, 0) = \max(f(i - 1, 0), f(i - 1, 1), f(i - 1, 2))$$

当第 $i$ 位选，第 $i - 1$ 位不选时，此时的最大值其实就是考虑到第 $i - 1$ 位，且第 $i - 1$ 位不选的最大值加 $1$，所以 $f(i, 1)$ 的转移也很好想：

$$f(i, 1) = f(i - 1, 0) + 1$$

然后考虑 $f(i, 2)$ 的转移，发现这个的转移是有条件的。

如果这两位选完之后满足条件，那么可能有转移 $f(i, 2) = f(i - 1, 1) + 1$。

如果这两位选完之后，再选第 $i - 2$ 位也满足条件，那么可以有 $f(i, 2) = f(i - 1, 2) + 1$。

二者取最大值即可。

核心代码：

```c++
		for(int i = 1; i <= n; i = i + 1)
		{
			f[i][0] = max(f[i - 1][0], max(f[i - 1][1], f[i - 1][2]));
			f[i][1] = f[i - 1][0] + 1;
			f[i][2] = 0;
			if(i >= 2 && a[i] + a[i - 1] >= 0)
			{
				f[i][2] = max(f[i][2], f[i - 1][1] + 1);
				if(i >= 3 && a[i] + a[i - 1] + a[i - 2] >= 0)
					f[i][2] = max(f[i][2], f[i - 1][2] + 1);
			}
		}
```

---

## 作者：45dino (赞：1)

题目大意：

给定 $n$ 个数和一个参数 $x$，标记一些数，满足任意大于 $1$ 的，且所有数都被标记的区间的平均数都不小于 $x$。

求最多标记多少数。

$n\le 500000$。

----
贪心地想，一定是尽可能地从前往后，能标记的就标记。因此未标记的数下一个一定要标记。

否则，对于第 $i$ 个数，假如第 $i-1$ 个数被标记，先检查 $a[i-1,i]$ 的平均数。

**假如该区间的平均数符合要求，不代表第 $i$ 个数一定能被标记。** 比如当 $x=4$，$a[i-2,i]$ 分别是 $2,8,2$，分别符合条件，不幸的是，放到一块平均数为 $3$。

因此，还要检查 $a[i-2,i]$ 的平均数是否满足要求。

假如此时满足要求了，那么长度为 $4$ 的段一定符合要求，不必再次检查。因为可以分成两个长度为 $2$，且各自符合条件的段。同理，更长的段也都符合条件。

代码不难写，就不放了。

---

## 作者：苏联小渣 (赞：1)

~~智商不够，数据结构来凑~~

我们把题目的式子转化一下，令 $s_i=a_{1}+...+a_i$，则题目要求 $r>l,$ 

$$s_{r}-s_{l-1} \ge x \cdot (r-l+1)$$

$$s_r-s_{l-1} \ge x \cdot r-x \cdot (l-1)$$

$$s_r-x \cdot r \ge s_{l-1}-x \cdot (l-1)$$

令 $p_i=s_i - x \cdot i$，则题目要求

$$p_r \ge p_{l-1}$$

**下面默认 $i=1$ 的所有答案经过特判。**

我们不妨计算对于每一个右端点 $r$，一个最小的 $l$ 使得 $[l,r]$ 可以被选。很明显首先我们需要知道 $[1,r-2]$ 中最大的 $j$ 使得 $p_r<p_j$，那么区间 $[j+2,r]$ 就是对于 $r$ 的最长的一段区间满足这个区间的平均数 $\ge x$，所以 $l$ 只能在 $[j+2,r]$ 里面选。

那 $l$ 具体怎么确定？这个 $l$ 需要满足 $[l,r]$ 里面的所有数，所以每次我们找到了一个 $j$，开一个线段树，把 $j+2$ 放到 $r$ 这个位置，然后查询区间 $[j+2,r]$ 的最大值就是 $l$。举个例子：当 $i=1,2,3,4,5$ 时，所有 $j+2$ 组成的序列为 $1,1,2,4,3$。那么当 $r=5$ 时，区间 $[3,5]$ 的最大值为 $4$，而手动模拟可以发现，$[4,5]$ 这个区间是对于 $5$ 而言，最长的满足所有数的需求的区间。

我们已经知道了对于 $r$，最小的 $l$ 满足 $[l,r]$ 可以被选，那具体应该如何选？我们设 $f_i$ 表示在 $[1,i]$ 里面选的最大答案。那么有转移方程：

$$f_i=\max(f_{i-1},f_{l_i-2}+(i-l_i+1))$$

原因就是选 $[l_i,i]$ 肯定最优，而选了 $l_i,l_i-1$ 肯定就不能选，所以要从 $f_{l_i-2}$ 转移过来，同时要和 $f_{i-1}$ 取 $\max$，因为可以不选。

综上，我们需要写两个数据结构，分别支持单点修改 & 区间查询最大的下标 $j$ 使得 $p_j>p_r$，单点修改 & 区间查询最大值。开两个线段树，分别维护两个最大值。前者查询的时候在线段树上二分，后者直接查询即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define lc(x) x<<1
#define rc(x) x<<1|1
int t, n, lim, pre, pos, mx, a[50010], p[50010], lst[50010], f[50010], d[200010], ps[200010];
const int minn = -1e10;
struct node{
	int ans, pos;
};
void modifyp(int k, int l, int r, int x, int y){
	if (l == r){
		ps[k] = y;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modifyp(lc(k), l, mid, x, y);
	else modifyp(rc(k), mid+1, r, x, y);
	ps[k] = max(ps[lc(k)], ps[rc(k)]);
}
node get(int k, int l, int r, int cha){
	if (l == r) return (node){ps[k], l};
	int mid = l + r >> 1;
	if (ps[rc(k)] > cha) return get(rc(k), mid+1, r, cha);//优先查询右子树 
	return get(lc(k), l, mid, cha);
}
node queryp(int k, int l, int r, int x, int y, int cha){
	if (x <= l && r <= y){
		if (ps[k] > cha) return get(k, l, r, cha);//刚好满足区间最大值比cha大 
		return (node){minn, -1};
	}
	int mid = l + r >> 1;
	if (y <= mid) return queryp(lc(k), l, mid, x, y, cha);
	if (x > mid) return queryp(rc(k), mid+1, r, x, y, cha);
	node rig = queryp(rc(k), mid+1, r, x, y, cha);//下标最大，优先查询右子树 
	if (rig.ans > cha) return rig;
	node lef = queryp(lc(k), l, mid, x, y, cha);
	if (lef.ans > cha) return lef;
	return (node){minn, -1};
}
void modify(int k, int l, int r, int x, int y){
	if (l == r){
		d[k] = y;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(lc(k), l, mid, x, y);
	else modify(rc(k), mid+1, r, x, y);
	d[k] = max(d[lc(k)], d[rc(k)]);
}
int query(int k, int l, int r, int x, int y){
	if (x <= l && r <= y) return d[k];
	int mid = l + r >> 1, ret = 0;
	if (x <= mid) ret = max(ret, query(lc(k), l, mid, x, y));
	if (y > mid) ret = max(ret, query(rc(k), mid+1, r, x, y));
	return ret;
}
signed main(){
	scanf ("%lld", &t);
	while (t --){
		pre = 0;
		memset(d, 0, sizeof(d));
		memset(ps, 0, sizeof(ps));
		scanf ("%lld", &n);
		for (int i=1; i<=n; i++){
			scanf ("%lld", &a[i]);
			f[i] = p[i] = lst[i] = 0;
		}
		scanf ("%lld", &lim);
		modifyp(1, 0, n, 0, 0);
		for (int i=1; i<=n; i++){
			pre += a[i];
			p[i] = pre - lim * i;
			//需要找到[0, i-2]中第一个比p[i]大的数的位置 
			if (i > 1) pos = queryp(1, 0, n, 0, i-2, p[i]).pos + 2;
			else pos = 1;
			modifyp(1, 0, n, i, p[i]);
			modify(1, 1, n, i, pos);
			lst[i] = query(1, 1, n, pos, i);
		}
		for (int i=1; i<=n; i++){
			if (lst[i] == 1) f[i] = i;
			else{
				f[i] = max(f[i-1], f[lst[i]-2] + i - lst[i] + 1);
			}
		}
		printf ("%lld\n", f[n]);
	}
	return 0;
}
```

---

## 作者：中缀自动机 (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1616D)

先将所有的 $a_i$ 都减掉 $x$，要求变为了所有长度为 $2$ 的区间和 $\ge0$。

注意到，我们只需验证每个长度为 $2$ 或 $3$ 的区间。

那么自然可以考虑 dp，记 $f_{i,0/1,0/1}$ 表示当前考虑了前 $i$ 个数，是否选择 $a_{i−1}$ 和 $a_i$。转移枚举 $a_{i+1}$ 是否选择，并验证是否满足要求即可。

时间复杂度 $O(n)$。

实际上这里可以直接从左到右贪心选取。

---

## 作者：ny_Dacong (赞：0)

# 思路

容易证明，**任意一个不小于 2 的整数均可由若干个 2 和 3 相加得出。**

因此，原题目的要求“长度至少为 2 的连续子串”可以转化为若干个长度为 2 或 3 的子串。

接下来只需要依次枚举每个长度为 2 或 3 的子串即可。每个数能选就尽量选。

第二个条件等价为区间中的每个数的总和必须大于等于 $x \times (r-l+1)$。如果这个区间中的数不满足条件二，那么就舍弃一个数满足条件一。

舍弃一个数可以把这个数设为无穷大，这样枚举其它区间的时候肯定符合条件。

~~其实挺水的~~。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n = 0,x,ans;
int num[50005];
int main(){
	scanf("%d",&t);
	while(t--){
		memset(num,0,n*4);//sizeof 耗时
		scanf("%d",&n);
		for(int i = 1; i <= n; i++){
			scanf("%d",&num[i]);
		}
		scanf("%d",&x);
		for(int i = 1; i <= n; i++){
			num[i] -= x;//减去平均数方便计算
		}
		if(n == 1){//特判
			printf("%d\n",num[1] >= 0);
			continue;
		}
		if(n == 2){
			printf("%d\n",1+(int)(num[1]+num[2] >= 0));
			continue;
		}
		ans = n;//初始选 n 个数
		for(int i = 2; i <= n; i++){
			if(num[i-1]+num[i] < 0 || num[i-2]+num[i-1]+num[i] < 0){//不满足条件二
				num[i] = 0x3f3f3f3f;//不选这个数
				ans--;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：baka24 (赞：0)

考虑贪心。

先做个转换，所有数减去 $x$ 之后判断区间是否 $\ge0$。

由于长度大于 $3$ 的区间都可以被拆开，所以只需要考虑长度为 $3$ 和 $2$ 的区间即可。

发现如果选了 $a_x$ 会导致 $a_y$ 选不了 $(x<y)$，那么不选 $a_y$ 一定可以选 $a_{y+1}$，也就是说选了 $a_x$ 最多只会影响一个点的存活，那么我们取 $a_x$ 还是 $a_y$ 在数量上是一样的，所以能取就取的贪心是正确的。

基于这个想法，我们考虑能取就取，判断 $a_i+a_{i-1}$ 和 $a_i+a_{i-1}+a_{i-2}$ 的正负，如果取不了就不管，把 $a_i$ 改成 $\inf$（因为不选这个点可以使后面的一些点不用考虑一部分区间）。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=300010,inf=10000000000000000;
int n,k,a[MAXN],ans;
void slv(){ans=0;
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();k=read();
    for(int i=1;i<=n;i++)a[i]-=k;
    ans=1;
    for(int i=2;i<=n;i++){
        if(a[i-1]+a[i]<0||a[i-1]+a[i]+a[i-2]<0){
            a[i]=inf;
        }
        else ans++;
    }
    printf("%lld\n",ans);
}
signed main(){
    int _=read();while(_--)
	slv();
    return 0;
} 	
```

---

## 作者：Hisaishi_Kanade (赞：0)

$\sum\limits_{i=l}^ra_i\ge(r-l+1)\times x\to \sum\limits_{i=l}^r (a_i-x)\ge 0$。

所以一个比较显然的转化是将 $c_i\gets a_i-x$。

现在等价于在 $c_i$ 中选出最多的数，使得对于任意一对 $1\le x< y\le n$，若 $c_x,c_{x+1},\cdots,c_y$ 都选过，则 $\sum\limits_{i=x}^r c_i\ge 0$。

考虑如何取搞这么一个玩意，不如从小开始考虑。

你会发现如果已经能够保证每个长度为 $2$ 的全选段都满足条件，那么对于任意偶数长度待选段都合法了！因为任意一个偶数段 $[x,y]$ 肯定可以划分成另外两个偶数段，或者他本身长度为 $2$，最后都会合法。

但是还没考虑到奇数，这时候显然保证一下长度为 $3$ 的全选段即可。

综上，只需要在选的时候考虑到连续两个和连续三个都合法即可。

这样可以设计出一个很简单的 dp，$f(i,0/1/2/3)$ 表示前 $i$ 个，没选 $i$；选了 $i$，没选 $i-1$；或者选了 $i,i-1$。

那么转移也比较好想，$f(i,0)=max\{f(i-1)\}$，$f(i,1)=f(i-1,0)+1$，$f(i,2)$ 判一下长度 $2,3$ 然后转移一下。

```cpp
#include <bits/stdc++.h>
#define per(i, l, r) for(i=l; i<r; ++i)
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=3e5+5, inf=2e9;
const ll illf=1e18;
int a[N], f[N][3], c[N];
int qt, n, i, j, k, x;
int main()
{
	scanf("%d", &qt);
	while(qt--)
	{
		scanf("%d", &n); rep(i, 1, n) scanf("%d", a+i); scanf("%d", &x);
		rep(i, 1, n) c[i]=a[i]-x;
//		rep(i, 1, n) printf("%d\n", c[i]);
		rep(i, 0, n) f[i][0]=f[i][1]=f[i][2]=0;
		rep(i, 1, n)
		{
			f[i][0]=max(f[i-1][0], max(f[i-1][1], f[i-1][2]));
			if(i>=1) f[i][1]=f[i-1][0]+1;
			else f[i][1]=max(f[i-2][0], max(f[i-2][1], f[i-2][2]))+1;
			if(i>1 && c[i]+c[i-1]>=0) f[i][2]=max(f[i][2], f[i-1][1]+1);
			if(i>2 && c[i]+c[i-1]>=0 && c[i]+c[i-1]+c[i-2]>=0) f[i][2]=max(f[i][2], f[i-1][2]+1);
//			printf("%d %d %d(%d)\n", f[i][0], f[i][1], f[i][2], c[i]+c[i-1]);
		}
		printf("%d\n", max(f[n][0], max(f[n][1], f[n][2])));
	}
}

```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1616D - Keep the Average High 题解

## 题目大意

给定一个有 $n$ 个数的序列 $a$，从中选出一个子序列使得这个子序列的每一个长度 $>1$ 子串的平均值都 $\ge x$，青丘处这个子序列最长的长度是多少

数据范围保证：$n\le 5\times 10^4$

## 思路分析

考虑将每个 $a_i$ 变成 $a_i-x$，所以满足条件的序列就变成了使得每个字串的和都 $\ge0$，考虑一下什么情况导致不能选某个数 $a_i$：当且仅当 $a_i$ 和已选序列中的后 $l$ 个之和是负数才不会导致 $a_i$ 不能选，所以考虑采用贪心的思想，从前往后，能选就选

考虑某段长度为 $l$ 的数和为负数（$l>1$），根据裴蜀定理，$l$ 一定能被表示成若干个长度为 $2$ 和 $3$ 的字串之和

所以，如果某个子序列的所有长度为 $2$ 和 $3$ 的字串和都非负，那么这个子序列就是可行的

所以判断 $a_i$ 可不可以选的时候只需要判断一下 $a_i+a_{i-1}$ 和 $a_i+a_{i-1}+a_{i-2}$ 是否非负，特别地，如果 $a_i$ 没有被选，则让 $a_i=+\infty$，使得含 $a_i$ 的和一定是非负的

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MAXN=5e4+1,INF=1e9+7;
int a[MAXN]; 
inline void solve() {
	int n,x,ans=0;
	scanf("%lld",&n);
	for(register int i=1;i<=n;++i) scanf("%lld",&a[i]);
	scanf("%lld",&x);
	ans=n; //不行就减去 
	for(register int i=1;i<=n;++i) a[i]-=x; //都-x先 
	for(register int i=2;i<=n;++i) {
		if(((a[i]+a[i-1])<0)||((a[i]+a[i-1]+a[i-2])<0)) {
			--ans;
			a[i]=INF; //赋值正无穷 
		}
	}
	printf("%lld\n",ans);
	return ;
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve(); //多组数据局 
	return 0;
} 
```





---

