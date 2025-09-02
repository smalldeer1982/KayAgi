# Cat, Fox and Swaps

## 题目描述

Fox has found an array $ p_1, p_2, \ldots, p_n $ , that is a permutation of length $ n^\dagger $ of the numbers $ 1, 2, \ldots, n $ . She wants to sort the elements in increasing order. Cat wants to help her — he is able to swap any two numbers $ x $ and $ y $ in the array, but only if $ l \leq x + y \leq r $ (note that the constraint is imposed on the values of the elements, not their positions). He can make such swaps any number of times.

They don't know the numbers $ l $ , $ r $ yet, they only know that it's true that $ 1 \leq l \leq r \leq 2 \cdot n $ .

You are given the number $ n $ and the array $ p_1, p_2, \ldots, p_n $ . Determine how many pairs $ (l, r) $ satisfying the conditions are there such that you can sort the permutation if you can only swap two number $ (x, y) $ such that $ l \leq x + y \leq r $ (arbitrary number of times, possibly $ 0 $ ).

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first example, we need to be able to swap $ 1 $ and $ 2 $ , so we must be able to swap numbers with sum $ 3 $ . There are exactly $ 6 $ pairs satisfying the condition: $ (1, 3), (2, 3), (3, 3), (1, 4), (2, 4) $ and $ (3, 4) $ , so the answer is $ 6 $ .

In the second example, the $ 11 $ pairs satisfying the condition are $ (1, 4), (1, 5), (1, 6), (2, 4), (2, 5), (2, 6), (3, 4), (3, 5), (3, 6), (4, 5) $ and $ (4, 6) $ . For example, if we pick the pair $ (3, 4) $ we can first swap the numbers $ 1 $ and $ 2 $ and then the numbers $ 1 $ and $ 3 $ , after this, the permutation is sorted.

## 样例 #1

### 输入

```
7
2
2 1
3
3 1 2
4
3 2 1 4
5
5 3 1 2 4
5
1 2 3 4 5
6
3 2 1 5 4 6
6
1 3 2 4 5 6```

### 输出

```
6
11
23
29
55
46
58```

# 题解

## 作者：g1ove (赞：4)

先放结论：

定义 $f(l,r)$ 表示选择 $[l,r]$ 的操作区间。这个区间内的数可以任意交换。

$$f(l,r) \begin{cases}
l=r & Others.\\
l\le n,r\le n & [1,r-1] \\
l\le n,r>n & [1,n]\\
l>n,r>n & [l-n,n]
\end{cases}
$$

证明：

首先，我们知道，如果对于三个数 $A,B,C$，如果 $A,B$ 可以互相交换，$B,C$ 可以互相交换，那么 $A,C$ 可以交换。

构造一种方案：$(A,B,C)\to (B,A,C)\to (C,A,B)\to (C,B,A)$

所以我们可以得到上面的结论。

有了这个，我们画个图，发现除了 $l=r$ 这种特殊情况，其它情况通过画图可以自己手推，只需要一对相邻的数 $(x,x+1)$ 就可以把所有数连起来。

注意边界。讨论完可以得到上面的结论。

最后是 $l=r$ 的情况，这个把所有要操作交换的和记下来，如果只有一种和，那就是合法的。

上面的都懂了，统计答案就不难了，记两个极值，使用等差数列公式求和即可。因为最小值以上的和最大值以下的都需要交换。

时间复杂度是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
int g;
int n,a[N];
ll res;
int pos;
int maxx,minn;
int main()
{
	scanf("%d",&g);
	while(g--)
	{
		res=0;
		scanf("%d",&n);
		pos=-1;
		maxx=0;minn=1e9;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(i==a[i]) continue;
			if(pos==-1) pos=a[i]+i;
			else if(pos^(a[i]+i)) pos=-2;
			maxx=max(maxx,a[i]);
			minn=min(minn,a[i]);
		}
		if(minn==1e9)
		{
			printf("%lld\n",1ll*n*(n*2+1));
			continue;
		}
		if(pos>0) res=1;
		// Case 1:
		res+=1ll*(maxx+n-1)*(n-maxx)/2;
		// Case 2:
		res+=1ll*n*n;
		// Case 3:
		res+=1ll*n*minn-1ll*(minn+1)*(minn)/2;
		printf("%lld\n",res);
	}
	return 0;
}
```

---

## 作者：Eraine (赞：3)

编号：CF1973E

tag：贪心

难度：*2602（$\texttt{Clist}$ 数据）

这道题目诈骗得有些意思。

特判掉已经排好序的排列，所有区间对于排列都是合法的。

合法区间必然满足区间包含单调性，即若区间 $[l,r]$ 合法，则区间 $[l-1,r]$ 和区间 $[l,r+1]$ 均合法。所以只需要求出左端点固定时右端点的最小值即可。

对于不在对应位置上的数所构成的集合记为 $S$，$\min S$ 和 $\max S$ 即为 $S$ 中的最小元素和最大元素。

定义最简区间为合法区间 $[l,r]$ 使得不存在 $[l,r]$ 的子区间 $[l^\prime,r^\prime](l\le l^\prime\le r^\prime\le r)$ 为合法区间。

最简区间长度 $=1$ 的时候很好判断，区间直接判断即可，直接判断图中是否都为二元置换环（自环就不考虑了）且二元置换环 $(u,v)$ 是否都满足 $u+v=k$，其中 $k$ 为定值，若存在则 $[k,k]$ 就是唯一合法的长度为 $1$ 的最简区间。

现在问题是如何求出这些最简区间。

我们可以构造如下方案使得当要交换 $(a,b)$ 且直接交换 $(a,b)$ 较劣时，有更优的方案。引进 $c$，假设原数组位置为 $a\ b\ c$，交换 $(a,c)$ 得 $c\ b\ a$，交换 $(b,c)$ 得 $b\ c\ a$，交换 $(a,c)$ 得 $b\ a\ c$，这样我们就在不移动 $c$ 的前提下交换了 $(a,b)$。此时 $c$ 可以为任何数，包括 $a,b$ 本身，因为代价不会更劣。

很容易发现对于序列中 $[\min S,\max S]$ 中的所有数，可以通过只交换 $(i,i+1)$ 的形式而使之有序。对于交换 $(i,i+1)$ 和 $(i+1,i+2)$，我们对应的 $j$ 最优状态为 $j_1=j_2+1$，也就是随着 $i$ 的递增，$j$ 递减。

这样当我们不考虑 $j$ 只能取 $[1,n]$ 这一限制条件，我们便对任意的 $j_0$（交换 $(i,i+1)$ 对应的 $j$）找到了合法的长度为 $2$ 的最简区间。

接下来就是考虑 $j$ 只能取 $[1,n]$ 这一限制条件。令 $len=\max S-\min S+1$。则 $c_{i}=c_0-i$,也就是只要 $c$ 中的极值 $c_0$ 和 $c_{len-2}$ 满足条件即可。这是好解决的。

但是有个问题，$c_0$ 或 $c_{len-2}$ 取不到的值一定没有最简区间吗？是的。我们这里只讨论 $c_0$ 的情况。当 $c_0>n$ 时，即 $\max S+n$ 时大小为 $2$ 的区间（可视为二元组）的较小值，此时较大值已经没用（若被操作则是无用操作，会使区间更劣），所以当 $c_0>n$ 时无法取到最简区间。

$\Theta(n)$。

[submission](https://codeforces.com/contest/1973/submission/261954460)

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：Engulf (赞：2)

思路参考官方题解，但其中对官方题解的思路和略过的部分进行了详细补充，证明了所有题解草草略过的部分，希望读者能认真阅读超链接部分的文字。

开始前，先判断排列是否已经有序，若有序，答案为 $\sum\limits_{l=1}^{n}\sum\limits_{r = l}^{n} 1 = \dfrac{2n (2n + 1)}{2} = 2n^2+n$，不进行过多讨论。

首先考虑 $l = r$ 的对子，若 $i \neq p_i$，此时 $l = r = i + p_i$，找出所有这样的 $i$，数量记作 $c$，讨论：
- 不存在 $c = 0$ 的情况，否则排列有序。
- $c = 1$，存在唯一的一个 $l = r$ 的对子。
- $c \ge 2$，不存在 $l = r$ 的对子。

观察到若要交换 $x, y$，可以借助第三个数 $z$ 使得不直接交换 $x, y$，而是交换 $x,z$ 和 $y, z$ 达到同样的效果（$z$ 位置不变，$x, y$ 交换），[证明](https://www.luogu.com.cn/paste/dikbfi62)。其实如果 $x = z$ 或者 $y = z$，相当于直接交换了 $x, y$，下文不区分这个了。

设 $L$ 是最小的使得 $L \neq p_L$ 的 $L$，$R$ 是最大的使得 $R \neq p_R$ 的 $R$。

注意到 $L \neq n, R \neq 1$，否则排序有序。那么我们可以得到使 $L, R$ 至少与一个其他数交换来使排列有序的必要条件：$l \in [1, L + n], r \in [R + 1, 2n]$。

事实上这是充分的。

先把不等式摆上来：$l \le L + n$，$r \ge R + 1$。

注意现在统计的数对是 $l < r$ 的，虽然 $L + n \ge R + 1$ 有可能成立。下面的讨论默认 $l < r$。

引理：对于任意的 $X \in [L, R - 1]$，一定存在一个 $x \in [l, r]$，使得 $1 \le x - X \le n$，[证明](https://www.luogu.com.cn/paste/fb232iut)。

这样，$X \in [L, R - 1]$ 的数可以借助数 $x - X$ 两两相互交换了。进一步地，$X\in[L, R - 1]$ 的数可以和 $X + 1$ 交换，具体步骤：
- 交换 $X, x - X$
- 交换 $x - X, X + 1$，[这一步的合法性证明](https://www.luogu.com.cn/paste/5nbx5zuq)
- 交换 $X, x - X$

这样，$[L, R]$ 中的所有数可以相互随意合法交换且不影响其他数，可以完成排序，充分性证毕。

最后统计答案，答案是 $l \in [1, L + n], r \in [R + 1, n]$ 中，$l < r$ 的 $(l, r)$ 数量（$L + n \ge R + 1$ 可能成立），我居然没想到 $O(1)$ 的数学做法，有无大佬教教。

从 $R + 1$ 到 $2n$ 枚举右端点 $r$，那么合法的 $l \in [1, \min(L + n, r - 1)]$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> p(n);
        set<int> st;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            if (i + 1 != p[i])
                st.insert(p[i] + i + 1);
        }
        if (is_sorted(p.begin(), p.end())) {
            cout << 2ll * n * (2 * n + 1) / 2 << "\n";
            continue;
        }

        ll ans = st.size() == 1;

        int L = n, R = 1;
        for (int i = 0; i < n; i++) {
            if (p[i] != i + 1) {
                L = min(L, i + 1);
                R = max(R, i + 1);
            }
        }

        for (int i = R + 1; i <= 2 * n; i++)
            ans += min(L + n, i - 1);

        cout << ans << "\n";
    }
    return 0;
}
```

[闲话](https://www.luogu.com.cn/paste/9ooqxx9t)

---

## 作者：Creeper_l (赞：2)

> 题意：对于一个长度为 $n$ 的排列，求有多少对 $(l,r)$ 满足 $1 \le l,r \le 2n$，且可以通过交换任意次 $x,y(l \le x+y \le r)$ 使得原排列升序。

首先我们可以找到 $i \ne a_i$ 的最小和最大的 $i$，假设为 $L$ 和 $R$。若不存在则说明已经升序。

会发现满足条件的必要条件是：$l \le L + n,r \ge R + 1$。

神奇的是若除开 $l=r$ 的情况，上述条件也是充分条件，证明如下：

对于一个数 $L \le x \le R-1$，我们先找到一个 $y$ 满足 $l \le y < r$ 且 $1 \le y-x \le n$，这个 $y$ 一定存在的。那么我们可以通过交换 $(x,y-x),(y-x,x+1),(x,y-x)$ 达到交换 $(x,x+1)$ 的目的。即对于任意的 $L \le x \le R$，我们都能做到交换 $(x,x+1)$（并且其它数的位置不变），显然这一定能使原序列排序。

注意当 $l=r$ 的情况时上述条件不一定成立，需要特殊考虑一下。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5 + 10;
int n,T,a[MAXN];
signed main() {
	for(cin >> T;T;T--) {
		cin >> n;
		int l = -1,r = -1,ans = 0,flag = 0;
		for(int i = 1;i <= n;i++) cin >> a[i];
		for(int i = 1;i <= n;i++) 
			if(a[i] != i) {
				if(flag == -1) break;
				if(flag == 0) flag = a[i] + i;
				else if(flag != a[i] + i) flag = -1;
			} 
		for(int i = 1;i <= n;i++) if(a[i] != i) r = i;
		for(int i = n;i >= 1;i--) if(a[i] != i) l = i;
		if(l == -1) l = 2 * n,r = 1;
		else l = l + n,r = r + 1;
		for(int i = r;i <= 2 * n;i++)
			ans += min(i - 1,l);
		if(flag == 0) ans += 2 * n;
		if(flag > 0) ans += 1;
		cout << ans << endl; 
	}
	return 0;
}
```

---

## 作者：oh_my_shy (赞：1)

[Cat, Fox and Swaps - 洛谷 | 计算机科学教育新生态](https://www.luogu.com.cn/problem/CF1973E)

对于 $x$，能和他交换的 $y$ 满足 $y\in [l-x,r-x]$。

交换不限次数，对于两个在 $[l-x,r-x]$ 中的 $y_1,y_2$，可以通过 $x$ 实现交换 $y_1,y_2$。

进一步的，若 $a,b$ 的集合 $[l-a,r-a]$ 和 $[l-b,r-b]$ 之间有交，两个集合中的元素便可以利用交中的元素做跳板，实现任意交换，也就是说可以任意交换的是两集合的并。

不难发现这个东西是有传递性的，可以一直嵌套，因为这样的交换结束后不会改变外界的位置。

在 $l\ne r$ 时，$x\in[1,n]$，所有 $[l-x,r-x]$ 的并就是 $[l-n,r-1]$，所以只要这个集合包括了所有需要交换的 $a_i$，$l,r$ 就合法。

形式化的，最靠左/靠右的 $a_i\ne i$ 的 $i$ 设为 $L,R$，合法的 $l,r$ 要满足 $[L,R]\subseteq [l-n,r-1]$，这个容易计算，枚举 $l$，合法的 $r\in[\max(R+1,l+1),2n]$。

还没有考虑 $l=r$ 的情况，这个时候任意集合都没有交，$x$ 只能和 $l-x$ 交换。

对于 $a_i\ne i$ 的 $a_i$，需要和 $a[a[i]]$ 交换，也就是 $l-a[i]=a[a[i]]$，这是等式，只会存在一个答案。若 $\forall i,i\ne a_i,\,a[a[i]]+a[i]$ 均相等，答案 $+1$ 即可。

当然需要特判一下初始就有序的情况，答案为 $\frac12 2n(2n+1)$。

```cpp
const int N = 1e5 + 5;
int n, a[N];
void Main()
{
    cin >> n;
    re(i, n) cin >> a[i];
    int L = 1e9, R = -1e9, flg = 0;
    re(i, n)
    {
        if (a[i] != i)
            L = min(L, a[i]), R = max(R, a[i]), flg = 1;
    }
    if (!flg)
    {
        cout << 1ll * 2 * n * (2 * n + 1) / 2 << '\n';
        return;
    }
    ll ans = 0;
    re(i, 2 * n)
    {
        if (i - n > L)
            break;
        ans += 2 * n - max(R + 1, i + 1) + 1;
    }
    int t = 0;
    re(i, n)
    {
        if (a[i] == i)
            continue;
        if (t == 0)
        {
            t = a[i] + a[a[i]];
        }
        else if (t != a[i] + a[a[i]])
        {
            t = -1;
            break;
        }
    }
    if (t != -1)
        ans++;
    cout << ans << '\n';
}
int main()
{
    int T = 0;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
```

---

## 作者：daduoli (赞：0)

好题。

显然本身就排好序的情况可以直接判掉。

首先我们先考虑 $l=r$ 的情况，当且仅当所有的满足 $a_i\not=i$ 的 $i$ 与他的目标都是一个二元置换环，且加起来都是相同的数，如果这种情况存在，仅会有一个和是合法的。

接下来考虑 $l\not=r$ 的情况。

我们先记最左边 $a_i\not=i$ 的为 $L$，最右边 $a_i\not=i$ 的为 $R$。

那么首先显然有必要条件，$l\le L+n,r\ge R+1$，因为至少要满足这个 $l,r$ 才可能进行交换。

然后我们现在思考这个东西能不能是充分的。

答案是可以的，考虑证明。

我们考虑对于任意 $X\in[L,R-1]$ 中的一个数，我们一定能从 $[l,r]$ 中找到一个 $x$，满足 $1\le x-X\le n$，那么我们交换 $X,x-X$，然后同时我们再交换 $X+1,x-X$，这样我们就可以做到交换相邻两个数字，而不影响序列中其他元素了。

考虑上面的操作我们有可能需要的最大的 $x$ 为 $x-R\ge 1\Rightarrow x\ge R+1$，而我们需要的最小的 $x$ 为 $x-L\le n\Rightarrow x\le L+n$，所以只要满足 $l\le L+n\cap r\ge R+1\cap l\not=r$ 的话，我们就一定能构造出一组解，这是充要的。

时间复杂度 $O(n)$。

```
#include<bits/stdc++.h>
typedef long long LL;

using namespace std;
const int MAXN=1e5+10;
int n;
int a[MAXN];
void vmain() {
	scanf("%d",&n);
	int L=n+1,R=0;
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		if(a[i]!=i) L=min(L,i),R=max(R,i);
	}
	if(L==n+1) {
		printf("%lld\n",(LL)(1+n*2)*(n*2)/2);
		return ;
	}
	int flag=0;
	for(int i=1;i<=n;++i) {
		if(a[i]!=i) {
			if(a[a[i]]==i) {
				if(!flag) flag=i+a[i];
				else {
					if(i+a[i]!=flag) flag=-1;
				}
			}
			else {
				flag=-1;
			}
		}
	}
	LL ans=0;
	if(flag!=-1) ++ans;
	for(int l=1;l<=L+n;++l) {
		int r=R+1;
		r=max(r,l+1);
		ans+=(2*n-r+1);
	}
	printf("%lld\n",ans);
}
int main () {
	int T;
	scanf("%d",&T);
	while(T--) vmain();
	return 0;
}
```

---

