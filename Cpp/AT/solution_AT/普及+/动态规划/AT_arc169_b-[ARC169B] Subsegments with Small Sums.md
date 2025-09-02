# [ARC169B] Subsegments with Small Sums

## 题目描述

给定一个正整数 $S$。对于正整数序列 $x$ ，我们定义函数 $f(x)$ 如下:

- 将 $x$ 分解为几个连续的子序列。对于每个连续子序列，其元素之和最多为 $S$。$f(x)$ 是在这样的要求下分解成的连续子序列的最小数目。

现在给定一个长度为 $N$ 的正整数序列 $A=(A_1,A_2,\cdots,A_N)$，请求出 $\sum_{1 \leq l \leq r \leq N} f((A_l,A_{l+1},\cdots,A_r))$。

## 说明/提示

$1 \leq N \leq 250000$，$1 \leq S \leq 10^{15}$，$1 \leq A_i \leq \min(S,10^9)$，所有输入都是整数。

样例一解释：

样例中 $x=(1,2,3)$。分解方案 $(1,2),(3)$ 满足条件，可以证明没有分解成少于两个连续子序列的方案满足条件，所以 $f((1,2,3))=2$。

下面显示的是可能的 $l,r$ 和对应的 $f$ 值:

-  $(l,r)=(1,1)$：$f((1))=1$
-  $(l,r)=(1,2)$：$f((1,2))=1$
-  $(l,r)=(1,3)$：$f((1,2,3))=2$
-  $(l,r)=(2,2)$：$f((2))=1$
-  $(l,r)=(2,3)$：$f((2,3))=2$
-  $(l,r)=(3,3)$：$f((3))=1$

因此，答案是$1+1+2+1+2+1=8$。

## 样例 #1

### 输入

```
3 3
1 2 3```

### 输出

```
8```

## 样例 #2

### 输入

```
5 1
1 1 1 1 1```

### 输出

```
35```

## 样例 #3

### 输入

```
5 15
5 4 3 2 1```

### 输出

```
15```

## 样例 #4

### 输入

```
20 1625597454
786820955 250480341 710671229 946667801 19271059 404902145 251317818 22712439 520643153 344670307 274195604 561032101 140039457 543856068 521915711 857077284 499774361 419370025 744280520 249168130```

### 输出

```
588```

# 题解

## 作者：2huk (赞：8)

## Description

给定一个长度为 $n$ 的序列 $a_1 \dots a_n$ 和一个正整数 $s$。

对于一个序列 $x$，定义 $f(x)$：

- 将 $x$ 划分成若干个连续子序列，使得每个子序列的和小于等于 $s$。$f(x)$ 即为最小的划分的连续子序列的个数。

求 $\sum_{1 \le l \le r \le n}f((a_l, a_{l + 1}, \dots, a_r))$ 的值。

## Solution

正解 DP，或者说递推。

令 $F(l) = \sum_{r = l}^n f((a_l, a_{l + 1}, \dots, a_r))$，即以 $l$ 为左端点的区间对答案的贡献。那么显然答案就为 $\sum _{i = 1}^n F(i)$。

首先找到最小的满足 $f((a_l, a_{l + 1}, \dots, a_r)) = 1$ 的 $r$，也就是说 $[l, r]$ 这段区间只需要划分成**一个**连续子序列（也可以认为不划分），那么显然有 $\sum_{i = l}^r a_i \le s$。发现这个东西是具有二段性的，所以有 $\sum_{i = l}^{r + 1} a_i > s$。所以我们可以二分找到这个位置 $r$，然后分类计算 $F(l)$ 的值。

![](https://cdn.luogu.com.cn/upload/image_hosting/aofwarju.png)

- 对于右端点 $j$ 小于等于 $r$ 的区间 $[l, j]$，显然答案为 $1$。而这样的 $j$ 有 $r - l + 1$ 个（因为 $j \in [l, r]$），也就是说 $F((a_l, a_{l + 1}, \dots, a_j)) = 1$ 的区间有 $r - l + 1$ 个，所以它对答案的贡献为 $r - l + 1$。
- 对于右端点 $j$ 大于 $r$ 的区间 $[l, j]$。首先如果把 $[l, r]$ 这一段区间去掉，就变成了「以 $r + 1$ 为左端点的区间对答案的贡献」，显然这个值为 $F(r + 1)$。然后把 $[l, r]$ 这一段区间的贡献加上，而每个右端点 $j \in [r + 1, n]$ 的区间都会受到它 $1$ 的贡献（相当于是把 $[l, r]$ 划成一个连续子序列，所以答案多了 $1$）。而这样的右端点 $j$ 有 $n - r$ 个，所以它对这些区间多加的贡献为 $n - r$。所以总贡献为 $F(r + 1) + n - r$。

综上，可得递推式 $F(l) = r - l + 1 + F(r + 1) + n - r = n - l + 1 + F(r + 1)$。倒序求解或记忆化搜索即可。

加上上面所说的二分找 $r$ 的过程，总时间复杂度为 $\mathcal O(n \log n)$。

## Code

用的记忆化搜索：<https://atcoder.jp/contests/arc169/submissions/48310257>。



---

## 作者：fcy20180201 (赞：4)

## 题意
定义 $f(x,S)$ 为**将序列 $x$ 分成若干段，使得每一段元素的和都不超过 $S$ 的前提下最少分成的段数**。现在给定序列 $A$ 和函数中的第二个参数 $S$，求 $A$ 所有连续子序列的 $f$ 值。

## 思路
~~怎么前两题都考拓扑排序。~~

**注意，下文中 $f$ 中的 $S$ 值都默认给定**。

先把问题简化亿下，如果只求一个序列的 $f$ 值，那肯定是无脑贪心（~~有手就行~~）。模拟一下过程，比如 $S=6$，序列是
$$2\space1\space3\space5\space4\space1$$
首先遍历到 $3$ 时和还没有超过 $6$，但到 $5$ 时和超过了 $6$，因此在 $5$ 前面分一下。以此类推，得到：
$$2\space1\space3|5|4\space1$$
$f$ 值为 $3$。

升级一下，求一个序列的所有前缀的 $f$ 值的和。方法和刚才几乎完全一样，不同的只是每次加进一个数答案就要加上现在的答案。比如：
$$2\space1\space3|5|4\space1$$
它的答案就是 $11=1\times 3+2\times 1+3\times 2$。我们发现可以把答案合并成按“段”来算：每一段的贡献是**它是第几段乘上它的长度**（很简单对吧）。

到了 arc169_b。用刚才的升级版暴力，对于每个后缀算贡献，时间复杂度 $\mathcal{O}(N^2)$。这个暴力慢在哪儿了？我们随便找一个后缀举例，不妨把刚刚的例子搬过来。
$$2\space1\space3|5|4\space1$$ 
这时候我们发现，算完第一段的贡献后，后面的两段合起来又是一个完美的后缀！只不过那个后缀由于少了一段，每个位置的贡献都比这个后缀的后两段少了 $1$，直接加上长度就得到我们要求的后缀的前两段，根本不用继续暴力。

我们把每一段后缀的贡献变成了**第一段的长度**加上**后两段构成的后缀的贡献**加上**后两段的长度**，也就是**后两段构成的后缀的贡献**加上**所求后缀的长度**。不难想到，可以拓扑排序，先算只有一段的后缀，再往前推就行。还剩最后一个问题，我们怎么找一个后缀的第一段在哪儿？**双指针**！！！至此问题完美解决。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;//不开 long long 见祖宗
int n;
ll s,sum,a[250005],ans[250005],aans;
vector<int>ed[250005];//记录第一段以每个位置结尾的后缀，和记录边差不多
queue<int>q;
int main(){
	scanf("%d%lld",&n,&s);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int l=1,r=0;l<=n;l++){//双指针求第一段
		while(r<n && a[r+1]+sum<=s)sum+=a[++r];
		ed[r].push_back(l);//“连边”
		sum-=a[l];
		if(r==n)q.push(l),ans[l]=(n-l+1);//先算只有一段的
	}
	while(!q.empty()){//拓扑排序
		int x=q.front();q.pop();
		aans+=ans[x];//算每一个后缀的贡献
		for(int y:ed[x-1])ans[y]=ans[x]+(n-y+1),q.push(y);//上文提到的递推式
	}
	printf("%lld",aans);
	return 0;
}
```

---

## 作者：gaochunzhen (赞：1)

### 题目描述

**下文记 $A_{l,r}$ 表示序列 $\{A_l,A_{l+1},\cdots,A_r\}$。**

给定一个正整数 $S$。对于一个正整数序列 $x$，定义 $f(x)$ 为：将 $x$ 分为若干**连续段**，并且每一段的数之和都 $\leq S$ 的分割的最小段数。

给定长为 $N$ 的序列 $A$，你需要求出 $\displaystyle \sum_{1\leq l\leq r\leq N}f(A_{l,r})$。

$1\leq N\leq 2.5\times 10^5,\ 1\leq S\leq 10^{15},\ 1\leq A_i\leq \min(S,10^9)$。

### 题解

我是 DS 魔怔人。

首先考虑对于单个序列 $x$，你如何求出 $f(x)$。这是一个贪心的过程，可以从左到右扫一遍，当一段的总和 $>S$ 的时候就截。

然后看着这个式子，考虑对于一个 $r$，求出所有以 $r$ 为右端点的所有序列的 $f$ 值之和。这个值可以考虑从右端为 $r-1$ 的情况推来。记 $b_{i,r}$ 为序列 $A_{i,r}$ 划分后最后一段的数之和，那么就有转移式：$b_{i,r}=\begin{cases}A_r,&b_{i,r-1}>S-A_r\\b_{i,r-1}+A_r,&b_{i,r-1}\leq S-A_r\end{cases}$。

其中，第一种情况会对答案造成 $n-r+1$ 的贡献，因为 $A_{i,r-1}$ 在加入 $A_{r}$ 后会被多分割一次，并且对于 $A_{i,r},A_{i,r+1},\cdots,A_{i,n}$ 来说，这次分割也对它们造成影响。所以它对于答案有 $n-r+1$ 的贡献。

接下来就是考虑如何维护 $b$。首先考虑在没有第一种情况，每次只是全局加的时候怎么做。一个比较简单的方式是记录一个变量 $T$，表示我们已经给全局加了多少。

然后就是第一种情况，我们可以使用 FHQ-Treap 维护。由于我们并不在乎 $b_{i,r-1}$ 真正所处的位置，只在乎它们的值，所以说我们可以将所有 $\geq S-A_r$ 的 $b_{i,r-1}$ 裂出来，然后换成等量的 $A_r$ 即可。这样我们就完成了第一种情况的处理。

将上述两个情况合并后的操作就是：

1. 将 $\geq S-A_r-T$ 的值裂出来（减 $T$ 是因为之前给整体都加了 $T$），假设其中有 $x$ 个数；
2. 让 $T:=T+A_r$；
3. 插入 $x+1$ 个 $A_r-T$。（对于 $A_{r,r}$ 会多插入一个 $A_r$，所以是插入 $x+1$ 个）

最后，由于我们只计算了每个序列在中间断多少次，这对于每个序列是少算了一次，所以答案需要再加 $\dfrac{n(n+1)}{2}$。（因为总共有 $\dfrac{n(n+1)}{2}$ 个序列）

需要注意一些细节：Treap 需要把相同键值的点合并，这样才能保证 $\mathcal O(n)$ 的节点数和插入次数。

时间复杂度 $\mathcal O(n\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define int long long
const int N = 250009;
mt19937 rng(random_device{}());
int n, a[N];
LL s, ans, st;
struct node {
    int val, sum, cnt, ls, rs, rnd;
    node(int aa = 0, int bb = 0) : val(aa), sum(bb), cnt(bb), ls(0), rs(0), rnd(rng()) {}
};
struct Treap {
    node T[N]; int rt, tot;
    Treap() {
        T[0] = node();
        rt = tot = 0;
    }
    void pushup(int u) {
        T[u].sum = T[T[u].ls].sum + T[T[u].rs].sum + T[u].cnt;
    }
    void split(int u, int k, int &x, int &y) {
        if (!u) {x = y = 0; return;}
        if (T[u].val <= k) {
            x = u, split(T[u].rs, k, T[u].rs, y);
        } else {
            y = u, split(T[u].ls, k, x, T[u].ls);
        }
        pushup(u);
    }
    int merge(int x, int y) {
        if (!x || !y) return x ^ y;
        if (T[x].rnd < T[y].rnd) {
            T[x].rs = merge(T[x].rs, y);
            pushup(x); return x;
        } else {
            T[y].ls = merge(x, T[y].ls);
            pushup(y); return y;
        }
    }
    void ins(int k, int cnt) {
        int x, y, z;
        split(rt, k - 1, x, y), split(y, k, y, z);
        if (!y) T[++tot] = node(k, cnt), y = tot;
        else T[y].sum += cnt, T[y].cnt += cnt;
        rt = merge(merge(x, y), z);
    }
    void slv(int i) {
        int x, y; split(rt, s - st - a[i], x, y);
        st += a[i], rt = x, ans += T[y].sum * (n - i + 1);
        ins(a[i] - st, T[y].sum + 1);
    }
} T;
signed main() {
    scanf("%lld%lld", &n, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        T.slv(i);
    }
    printf("%lld\n", ans + 1ll * n * (n + 1) / 2);
    return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
我们可以定义一个自带前缀和的状态 $dp_i$ 表示 $\sum_j^{n}f((a_i, a_{i+1}, \dots,a_j))$，那么最后的答案就是 $\sum_i^{n}dp_i$。那么我们考虑如何转移，首先 $dp_n=1$ 这是显然的，当我们枚举到 $i$ 是可以发现因为要最小那么我们二分出一个 $r$ 使得 $a_l\sim a_r$ 之和小于等于 $s$ 且 $r$ 最大。

然后我们分类讨论。

- 可以发现对于右端点在 $l\sim r$ 之中的都是 $1$，贡献即为 $r-l+1$。
- 右端点在 $r+1\sim n$ 之中，因为我们 $dp_i$ 具有前缀和思想，那么贡献为 $dp_{r+1}+n-r$ 就是由 $dp_{r+1}$ 加上右端点是 $(n-r)\times 1$。

最后可以得到公式 $dp_i=dp_{r+1}+n-i+1$，然后逆序往前推即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n,s;
int a[1001000];
int sum[1001000],f[1001000];
fire main() {
	in(n),in(s);
	rep(i,1,n) in(a[i]),sum[i]=sum[i-1]+a[i];
	f[n]=1;
	rep1(i,n-1,1) {
		int id=upper_bound(sum+1,sum+1+n,sum[i]+s-a[i])-sum-1;//求出r
		f[i]=f[id+1]+n-i+1;//套公式
	}
	int res=0;
	rep(i,1,n) res+=f[i];
	cout<<res<<endl;
	return false;
}

```

---

## 作者：快斗游鹿 (赞：0)

## 思路

考虑设 $c_l$ 表示 $\sum_{r=l}^nf((a_l,a_{l+1},\dots,a_r))$。然后考虑枚举左端点，并对每个 $l$ 找出一个最大的 $r$，满足 $\sum_{i=l}^ra_i\le s$，那么显然，当右端点在 $l$ 到 $r$ 内时，答案是 $1$，共有 $r-l+1$ 种情况。如果不在呢？显然，可以拆成 $[l,r]$ 和 $[r+1,n]$ 两段区间考虑，即对于这样的右端点 $p$，答案为 $f((a_l,a_{l+1},\dots,a_r))+f((f_{r+1},f_{r+2},\dots,f_p))$。前一项是 $1$，而后一项之和就等于 $c_{r+1}$。所以可得 $c_l=r-l+1+c_{r+1}+n-r$。倒着推即可，最终答案为所有 $c_i$ 之和。找 $r$ 用二分即可。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,c,a[N],sum[N],f[N],ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	n=read();c=read();
	for(int i=1;i<=n;i++)a[i]=read(),sum[i]=sum[i-1]+a[i];
	f[n]=1;
	for(int i=n-1;i>=1;i--){
		int r=lower_bound(sum+1,sum+1+n,sum[i-1]+c+1)-sum-1;
		f[i]=r-i+1+f[r+1]+n-r;
	}
	for(int i=1;i<=n;i++)ans+=f[i];
	cout<<ans;
	return 0;
}

```


---

## 作者：DDF_ (赞：0)

## 思路
由 $n \leq 250000$ 可知时间复杂度不能达到 $2$ 次方级，考虑递推求解。

由此想到 DP 算法，设 $f_{i}$ 为所有以 $i$ 为结尾的连续子序列对答案的贡献值之和，则可得答案为 $\sum^{n}_{i=1} f_{i}$。

然后从两种情况考虑。

若 $\sum^{i}_{j=1} a_{j} \le s$，那么所有以 $i$ 为结尾的连续子序列都不用被分割，所以 $f_{i} = i$。

若 $\sum^{i}_{j=1} a_{j} > s$，那么以 $i$ 为结尾的连续子序列需要被分割，则需要找到一个在 $i$ 之前的下标 $x$，使得在 $\sum^{i}_{j=x+1} a_{j} \le s$ 时，$\sum^{i}_{j=x+1} a_{j}$ 最大，则此时 $(x,i]$ 的分割是最优的。

此时所有 $[t,i]~(1 \le t \le x)$ 的序列被分成了两部分，一部分为 $(x,i]$，还有后面的 $[t,x]$，而这段区间可能还需要分割，那么此时有子问题为求所有以 $x$ 为结尾的连续子序列对答案的贡献值之和，即为 $f_{x}$。

综上可得，状态转移方程为 $f_{i} = i + f_{x}$。

但我们不能用 $O(n)$ 的效率求 $x$，考虑进行优化。

注意到先前的求和，可以想到用前缀和的方法求 $x$，我们知道前缀和是有单调性的，所以可以二分，设 $sum_{i} = \sum^{i}_{j=1} a_{j}$。

则有 $sum_{i} - sum_{x} \le s$。

可解得 $sum_{x} \ge sum_{i} - s$。

则可以以此进行二分。

时间复杂度为 $O(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,x;
ll s,a[250002],f[250002],ans;
int main() {
	scanf("%d%lld",&n,&s);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		a[i]+=a[i-1]; //前缀和
		x=lower_bound(a,a+i+1,a[i]-s)-a; //二分
		f[i]=i+f[x],ans+=f[i];
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：0x3F (赞：0)

当 $l,r$ 为定值时，我们显然使用贪心，即从左端点开始，每次取一个尽可能长的区间，最后答案必然是最小的。

我们记最小的满足 $\sum_{i=l}^{r}A_{i}>S$ 的 $r$ 为 $P_{l}$（不存在为 $N+1$），这容易使用双指针求出。

我们记 $F_{l}=\sum_{i=l}^{N}f(l,i)$，那么 $F_{n+1}=0,F_{i}=F_{P_{i}}+N-i+1$。

答案即为 $\sum_{i=1}^{n}F_{i}$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 2.5e5 + 10;
long long n, s, p[_], a[_], f[_], ans;
int main() {
	cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] += a[i-1];
	}
	for (int i = 1; i <= n; i++) {
		p[i] = p[i-1];
		while (p[i] != n+1 && a[p[i]] <= a[i-1] + s) p[i]++;
	}
	for (int i = n; i >= 1; i--) {
		f[i] = f[p[i]] + n - i + 1;
	}
	for (int i = 1; i <= n; i++) {
		ans += f[i];
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：fantastic_dream (赞：0)

### 解答
令 $F(i,j)=f((A_i,A_{i+1}, \dots,A_j))$，令 $b(i)=\sum_{j=1}^iF(j,i)$。对于 $i$，我们找最小的位置 $k$，使得 $\sum_{j=k}^iA_j\leq S$，也就是找最大的合法区间，可知：对于任意的 $1\leq l_1 <k$，有 $F(l_1,i)=F(l_1,k-1)+1$；对任意的 $k\leq l_2 <i$，有 $F(l_2,i)=1$。

则有 $b(i)=b(k-1)+k-1+i-k+1=b(k-1)+i$，答案则为 $\sum_{i=1}^nb(i)$。
### 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
const int ma=250005;
int n,s,sz[ma],sum[ma],f[ma],ans;
main(){
	ios::sync_with_stdio(0);
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>sz[i];
		sum[i]=sum[i-1]+sz[i];
	}
	f[1]=ans=1;
	for(int i=2;i<=n;i++){
		int cl=sum[i]-s,pos;
		pos=lower_bound(sum,sum+i,cl)-sum;
		f[i]=i+f[pos],ans+=f[i];
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：OldDriverTree (赞：0)

这场的 A 怎么比 B 还难啊/jk。

# Solution

设 $f_i$ 表示 $\sum\limits_{j=1}^i f(j,i)$ 的值。

考虑预处理出一个数组 $b$，$b_i$ 表示使得 $(\sum\limits_{k=j}^i a_i)> m$ 的离 $i$ 最近的 $j$ 的位置，双指针处理即可。

可以发现 $j\le b_i$ 时倒数第二段一定是以 $b_i$ 结尾，那么就可以得出 $f$ 数组的转移方程：$f_i=f_{b_i}+i$。

答案就为 $\sum\limits_{i=1}^n f_i$。

时间复杂度 $O(N)$。

# Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=25e4+1;
int n,m,a[N],b[N];
int ans,s[N],f[N];

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c^'-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read(),s[i]=s[i-1]+a[i];
	for (int i=n,pos=n+1,sum=0;i;i--) {
		while (pos&&sum<=m) sum+=a[--pos];
		b[i]=pos,sum-=a[i];
	}
	for (int i=1;i<=n;i++) f[i]=f[b[i] ]+i;
	for (int i=1;i<=n;i++) ans+=f[i];
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Aigony (赞：0)

[更好的阅读体验 qwq](https://www.cnblogs.com/ying-xue/p/arc169.html)

先考虑一个确定的区间怎么求答案。

直接贪心，从左往右考虑这个序列，如果上一段能放下就放进上一段，否则新开一段。正确性比较显然。  
那这个题就能做了：考虑左端点相同时每个右端点的答案，设这个和为 $f_l$。分为两种情况：
- 只有一段，对答案的贡献为 $1$；
- 有至少两段，但根据上面的贪心，它们第一段结束的位置均相同。设这个位置是 $x$。

那么 $r\ge x$ 的区间可以看作 $[x,r]$ 的答案加 $1$，即有转移 $f_l\gets f_x+(n-l+1)$，答案为 $ans=\sum\limits_{i=1}^n f_i$。  
找 $x$ 的过程双指针或二分均可。

```cpp
#define int long long
const int N=2.5e5+5;
int n,s,sum[N],a[N];
int f[N];
signed main()
{
    n=read(),s=read();
    for(int i=1;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]+a[i];
    for(int i=n;i;i--)
    {
        int nxt=lower_bound(sum+1,sum+n+1,sum[i-1]+s+1)-sum;
        f[i]=f[nxt]+(n-i+1);
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans+=f[i];
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Xiphi (赞：0)

考虑 dp。类似 2023S T2，设 $dp_i$ 表示以 $i$ 为左端点的所有区间的函数值之和，也即 $dp_i = \sum_{l \le i} f(a_i,a_{i+1}...,a_r)$。考虑如何转移。对于每个 $i$，让 $p _ i$ 成为 满足条件中的最大的  $j$，条件是：$a _ j + \cdots + a _ i > S$(如果不存在这样的 $j$，则设为 $p _ i = n+1$)。此处参考官方题解。然后 $p_i$ 显然可以双指针维护。

具体地，我们尝试分类讨论，若右端点大于 $p_i$，则就是 $f_{p_i}$，再加上多出来的 $[p_i,i]$ 这一段；若右端点小于等于 $p_i$，则最少分出一段来。综上，转移是 $dp_i=dp_{p_i}+i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
long long n,s,a[250005],sum[250005],l=1;
int dp[250005];
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>s;
	for(int i=1;i<=n;++i){
		cin>>a[i];sum[i]=sum[i-1]+a[i];
	}
	int l=1,Sum=0;
	for(int i=1;i<=n;++i){
		int flag=0;
		while(sum[i]-sum[l-1]>s&&l<i) l++,flag=1;
        if(sum[i]-sum[l-1]<=s&&l!=0) l--;
		dp[i]=dp[l]+i;
		Sum+=dp[i];
	}
	cout<<Sum;
	return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：0)

**纪念自己在 ARC 中第一次写出两道题qwq**，感觉本题有很多做法，分享一下我的考场做法，是一种非常有趣的树上 dp 做法。

## 题意

对于**正数**数组 $a$，定义 $f(a)$ 代表将该数组分为若干个连续段，使得每段段和 $\le S$，最少的可能段数。

给你一个正整数数组 $a$，长度为 $N$，请你求出 $a$ 的所有子区间的 $f$ 之和。$N \le 250000$。

## 分析

$a$ 数组是正的——这是一个重要的性质。这意味着：对于一个 $i$，在最优方案中，以 $i$ 开头的连续段必定越长越好。

我们定义 $\text{next}(i)$ 表示：假设有一个连续段从 $i$ 开始，那下一个连续段以哪里开始。特别地，若 $i$ 的连续段可以到达末尾，则 $\text{next}(i)=N+1$。例如样例 $S=3,a=\{1,2,3\}$ 中，$\text{next}(1)= \text{next}(2)= 3$，而 $\text{next}(3)=4$。

如何求出 $\text{next}$？这是简单的，对于每个 $i$，二分出第一个 $>S$ 的 $i$ 开头的区间即可。这是 $O(N \log N)$ 的。可以使用双指针做到 $O(N)$。

接下来有一步非常好的转化：我们建立一棵有根树，$\text{next}(i)$ 是 $i$ 的父亲，根是 $N+1$。我们不妨称这棵树为**连续段树**。发现连续段树具有这个性质：

- 对于 $i<j\le N$，找到最小的连续段树上的 $\ge j$ 的 $i$ 的祖先 $k$。则 $i,k$ 的树上路径长度就是 $f(a_{i \sim j})$ 的值。


因此借助连续段树，我们有一种 $O(N^2)$ 的求解方法：

枚举起点 $i$。不断跳到它的父亲。假如从 $i$ 的某个祖先 $fa^{j}$ 跳到了下一级祖先 $fa^{j+1}$，则此时所有原序列上左端点 $i$、右端点 $[fa^{j},fa^{j+1})$ 的区间的答案计入贡献，每个的贡献为 $\text{dis}(i,fa^{j+1})$。

（大家可以把连续段树画出来辅助理解）

我们考虑优化该算法。我们发现：对于连续段树的点 $u$ 和它的儿子 $v$，这条边会产生贡献。所有 $v$ 子树的结点 $v_1$ 作为左端点、右端点在 $[v,u)$ 范围内的区间，造成贡献，贡献是 $\text{dis}(v_1,u)$。也就是 $v$ 的子树内儿子到 $v$ 的距离和 $+1$。（可以结合你画的连续段树理解）

用树上 dp 维护子树距离和。可以 $O(N)$ 求解。如果你不会树上 dp，你可以查看 [此题。](https://www.luogu.com.cn/problem/P1352)

```cpp
#include <bits/stdc++.h>
#define LL long long
#define DB double
using namespace std;
const int MAXN=250005;
int N,a[MAXN];
vector<int>gra[MAXN];
int siz[MAXN];
LL dp[MAXN];//dp[u]表示u子树内所有点到u的距离之和
LL S,ans=0;
LL sum[MAXN];
void dpfs(int u,int fa)
{
	siz[u]=1;
	dp[u]=0;
	for(int v:gra[u])
	{
		if(v==fa) continue;
		dpfs(v,u);
		ans+=1ll*(u-v)*(dp[v]+siz[v]);
		siz[u]+=siz[v];
		dp[u]+=dp[v]+siz[v];
	}
	return;
}
int main()
{
	scanf("%d %lld",&N,&S);
	for(int i=1;i<=N;i++) scanf("%d",&a[i]);
	for(int i=1;i<=N;i++) sum[i]=sum[i-1]+a[i];
	sum[N+1]=sum[N]+S*2;
	for(int i=1;i<=N;i++)
	{
		int fa=0,l=i+1,r=N+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(sum[mid]-sum[i-1]>S) fa=mid,r=mid-1;
			else l=mid+1;
		}
		gra[fa].push_back(i);
	}
	dpfs(N+1,0);
	printf("%lld\n",ans);
	return 0;
}
```

时间复杂度可以达到 $O(N)$。当然我没有使用双指针维护因此是 $O(N \log N)$。



---

