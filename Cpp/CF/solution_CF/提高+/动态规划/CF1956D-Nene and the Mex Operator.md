# Nene and the Mex Operator

## 题目描述

Nene gave you an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ .

You can perform the following operation no more than $ 5\cdot 10^5 $ times (possibly zero):

- Choose two integers $ l $ and $ r $ such that $ 1 \le l \le r \le n $ , compute $ x $ as $ \operatorname{MEX}(\{a_l, a_{l+1}, \ldots, a_r\}) $ , and simultaneously set $ a_l:=x, a_{l+1}:=x, \ldots, a_r:=x $ .

Here, $ \operatorname{MEX} $ of a set of integers $ \{c_1, c_2, \ldots, c_k\} $ is defined as the smallest non-negative integer $ m $ which does not occur in the set $ c $ .

Your goal is to maximize the sum of the elements of the array $ a $ . Find the maximum sum and construct a sequence of operations that achieves this sum. Note that you don't need to minimize the number of operations in this sequence, you only should use no more than $ 5\cdot 10^5 $ operations in your solution.

## 说明/提示

In the first example, after the operation with $ l=1 $ and $ r=2 $ the array $ a $ becomes equal to $ [2,2] $ . It can be shown that it is impossible to achieve a larger sum of the elements of $ a $ , so the answer is $ 4 $ .

In the second example, the initial sum of elements is $ 13 $ which can be shown to be the largest.

In the third example, the array $ a $ changes as follows:

- after the first operation ( $ l=3 $ , $ r=3 $ ), the array $ a $ becomes equal to $ [1,100,0,1] $ ;
- after the second operation ( $ l=3 $ , $ r=4 $ ), the array $ a $ becomes equal to $ [1,100,2,2] $ .

It can be shown that it is impossible to achieve a larger sum of the elements of $ a $ , so the answer is $ 105 $ .

## 样例 #1

### 输入

```
2
0 1```

### 输出

```
4 1
1 2```

## 样例 #2

### 输入

```
3
1 3 9```

### 输出

```
13 0```

## 样例 #3

### 输入

```
4
1 100 2 1```

### 输出

```
105 2
3 3
3 4```

## 样例 #4

### 输入

```
1
0```

### 输出

```
1 1
1 1```

# 题解

## 作者：shinzanmono (赞：16)

考虑一个区间通过操作和最多可以变成多少。很显然一定存在一种方式使得整个区间的值都为区间长度 $len$，构造方法显然，将在文末提到。

于是问题转化成给原序列分段，区间 $[l,r]$ 的价值是 $\max(\sum_{i=l}^ra_i,(r-l+1)^2)$，求如何让取件价值最大，这个是裸的区间 dp，我们记录转移点，然后倒退回去即可。

接下来我们讲一讲构造方法。

不管怎么搞，首先我们都要让原区间归零。

首先我们从小考虑：

- 当 $l=2$ 时：

$$[0,0]\rightarrow[1,0]\rightarrow[2,2]$$

- 当 $l=3$ 时：

$$[0,0,0]\rightarrow[1,0,0]\rightarrow[2,2,0]\rightarrow[0,2,0]\rightarrow[1,2,0]\rightarrow[3,3,3]$$

于是我们发现了规律。

如果想要将 $[l,r]$ 全变为 $r-l+1$，那么首先要让 $[l,r-1]$ 全变成 $r-l$，然后在将 $[l,r-2]$ 全变成 $r-l-1$，以此类推，最后再将 $[l,r]$ 整体变为 $\mathrm{mex}(l,r)$。

由于数据范围极小，我们可以直接暴力解决求 $\mathrm{mex}$。分析可知，`solve` 函数的时间调用次数大概为 $O(2^n)$ 次，函数内部是 $O(n^2)$ 的，所以总时间复杂度可以做到 $O(2^nn^2)$，如果使用 $O(n)$ 方法求 $\mathrm{mex}$，可以做到 $O(2^nn)$。

```cpp
#include<iostream>
#include<algorithm>
#include<numeric>
const int sz=20;
long long f[sz][sz],sum[sz];
int g[sz][sz],a[sz],n;
std::basic_string<std::pair<int,int>>s;
int getmex(int l,int r){
    for(int v=0;v<=18;v++){
        bool flag=false;
        for(int i=l;i<=r;i++)
            if(a[i]==v)flag=true;
        if(!flag)return v;
    }
    return 0;
}
void add(int l,int r){
    s+=std::make_pair(l,r);
    std::fill(a+l,a+r+1,getmex(l,r));
}
void get(int l,int r){
    if(l>r)return;
    if(r==l){
        while(a[l]!=1)add(l,r);
        return;
    }
    get(l,r-1),add(l,r),add(l,r-1),get(l,r-1);
}
void solve(int l,int r){
    if(g[l][r]==0){
        if(sum[r]-sum[l-1]<1ll*(r-l+1)*(r-l+1)){
            while(std::accumulate(a+l,a+r+1,0ll)!=0)add(l,r);
            get(l,r-1),add(l,r);
        }
        return;
    }
    solve(l,g[l][r]),solve(g[l][r]+1,r);
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin>>n;
    for(int i=1;i<=n;i++)std::cin>>a[i],f[i][i]=a[i],sum[i]=sum[i-1]+a[i];
    for(int p=1;p<=n;p++){
        for(int l=1,r=p;r<=n;l++,r++){
            f[l][r]=std::max(1ll*p*p,sum[r]-sum[l-1]);
            for(int k=l;k<r;k++){
                if(f[l][k]+f[k+1][r]>f[l][r]){
                    f[l][r]=f[l][k]+f[k+1][r];
                    g[l][r]=k;
                }
            }
        }
    }
    solve(1,n);
    std::cout<<f[1][n]<<" "<<s.size()<<"\n";
    for(auto p:s)std::cout<<p.first<<" "<<p.second<<"\n";
    return 0;
}

```

---

## 作者：Drimpossible (赞：2)

赛时最后 3min 绝杀，结果才知道 E1<<D。

## 思路：
注意到 $5\times 10^5$ 个操作次数很大，而 $n\leq 18$ 很小，这个数据范围提示我们应该是用 $2^n$ 级别左右的操作次数。

再来考虑怎么最大化答案。最终序列的状态肯定是有些段用操作改变，有些段不变。所以我们设前 $i$ 项的最大和是 $f_i$，转移的话就考虑枚举最后一段划分在哪里，暴力 $O(n^2)$ 转移：
$$
f_i
=\max_j f_j+\max\{\sum_{j<k\leq i}a_k,g(j+1,i)\}
$$

其中 $g(l,r)$ 为，使用操作 $[l,r]$ 区间能得到的最大和。

那么现在问题来了，怎么求 $g(l,r)$ 呢？

## 具体做法：

理论最大值显然是 $(r-l+1)^2$，要达到这个值首先要把所有数变成 $0,1,2,\cdots r-l$，再用一次操作全部变成 $r-l+1$。而要达到这种情况，首先要有 $0,1,2,\cdots r-l-1$，全部变成 $r-l$ 之后再把前面变回去……可以发现，这就是一个递归的过程，不断使用比当前小 $1$ 的情况来操作（也可以用递推实现）。

因为这里的操作只跟区间长度和下标有关系，所以我们可以先预处理出对于不同长度的操作方案，DP 转移的时候再记一个操作序列就 ok 了。细节处理看代码吧。

## Code:
```cpp
void init(){
	/*这里预处理的ff意义是初始值全为0，变成0~i-1*/
	for(int i=2;i<=n;i++){
		for(auto op:ff[i-1])
			ff[i].emplace_back(op);
		ff[i].emplace_back(mkp(0,i-1));
		ff[i].emplace_back(mkp(0,i-2));
		for(auto op:ff[i-1])
			ff[i].emplace_back(op);
	}
}
 
void solve(int l,int r){
	int k=r-l+1;
	for(int i=l;i<=r;i++)
		if(a[i])g[r].emplace_back(mkp(i,i));
 	/*先把不为0的变成0*/
	for(auto op:ff[k])
		g[r].emplace_back(mkp(op.fi+l,op.se+l));
	g[r].emplace_back(mkp(l,r));//记得加上最后一步
}
 
void solution(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],s[i]=s[i-1]+a[i];
	init();
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			int t=f[i];
			f[i]=max(f[i],f[j]+max(s[i]-s[j],(i-j)*(i-j)));
			if(f[i]==t)continue;
			g[i].clear();
			for(auto op:g[j])
				g[i].emplace_back(op);
			if(s[i]-s[j]<(i-j)*(i-j))
				solve(j+1,i);
		}
	}
	cout<<f[n]<<' '<<g[n].size()<<endl;
	for(auto op:g[n])
		cout<<op.fi<<' '<<op.se<<endl;
}
```

---

## 作者：Halberd_Cease (赞：1)

观察，发现选择一段区间 $(l,r)$，若干次操作过后，可以把这个区间的数全部变成 $r-l+1$。

首先考虑 $l=r$，如果这一位是 $0$，那么 $\text{MEX}=1$，可以一次操作使得区间变成 $1$；如果不是 $0$，需要对其操作两次，使该值变成 $0$ 再变成 $1$。

考虑 $r-l=1$，要使 $\text{MEX}=2$，必然会有一个 $1$ 和一个 $0$。考虑如何将后面的数变成 $1$，先将前面的数变成 $0$，如果后面是 $1$ 则不管，否则操作 $(l,r)$ 使两个数都变成 $1$。这是再把第一位变成 $0$ 是容易的。

考虑 $r-l=k$，我们需要构造一个有 $k$ 个 $k-1$ 的数列，假设我们通过某种操作可以获得任意有 $x$ 个 $x-1$ 的数列（$x<k$），我们考虑如下构造：从 $k-1$ 到 $1$ 枚举 $i$，将序列前 $i$ 项全部变成 $i-1$，则操作完之后，序列呈 $0,1,2,\dots,k-2$（前 $k-1$ 项），如果最后一项不是 $k-1$，对整个序列操作一次，否则对序列前 $k-1$ 项操作一次，然后整个序列变成 $k-1$。这个构造方法在 $k=1$ 的时候直接特判就可以了，其余时候递归使用。

剩下的就很简单了，对于需要操作的 $(l,r)$，通过上面操作将序列变成 $0,1,2,\dots,k-1$，然后一次操作全部变成 $k$。

至于哪些地方需要操作，$O(n^3)$ 的区间 DP 可以直接做。

操作一个区间的最坏复杂度是 $O(2^n)$ 在 $n=18$ 时最多操作 $262,144$ 次，符合题目要求，总复杂度是 $O(2^n+n^3)$ 的。

[submission](https://codeforces.com/contest/1956/submission/256740910)

---

## 作者：AtomAlpaca (赞：1)

## 题意
给定一个长度为 $n$ 的序列，你可以进行若干次操作，一次操作可以将一个区间内的数全都变成这个区间内所有数的 $\operatorname{mex}$。

要求构造一种方案，使得操作之后序列和最大。

$n \le 18$。

## 题解
不难发现，如果一个长度为 $n$ 的区间内出现了从 $0$ 到 $n - 1$ 的所有数字，操作后这个区间全都变成了 $n$——这也是通过操作能达到的上界。

我们考虑如何把一个长度为 $n$ 的区间变成$0$ 到 $n - 1$ 的一个排列。考虑递归下去，对前 $n - 1$ 个数，让其成为一个 $0$ 到 $n - 2$ 的排列，这时如果最后一个数恰好是 $n - 1$ 就做完了，否则整体做一次操作可以使得区间全部变成 $n - 1$，再对前 $n - 1$ 个数做操作即可。并且 $n = 1$ 的情况是显然的，于是就做完了。不难发现 $n$ 每增加 $1$ 操作数最多变为原来的两部加一，操作数是 $O(2^n)$ 的。

然后我们考虑求出哪些区间应当被做以上操作。当然可以进行 dp 记下转移点，但出题人只给了 $n \le 18$，因此无脑暴力枚举也是可行的。至此，我们在 $O(n2^n)$ 的复杂度内完成此题。

## 代码
``` c++
#include <bits/stdc++.h>

const int MAX = 25;

std::vector <std::pair <int, int>> res, g;
int n, sum, mx; bool b[MAX];
int a[MAX];

void f(int l, int r)
{
	if (l == r) { if (a[l] != 0) { a[l] = 0; res.push_back({l, l}); } return ; }
	if (a[r] == r - l) { f(l, r - 1); return ; }
	f(l, r - 1);
	res.push_back({l, r}); for (int i = l; i <= r; ++i) { a[i] = r - l; }
	f(l, r - 1);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) { scanf("%d", &a[i]); }
	for (int S = 0; S < (1 << n); ++S)
	{
		for (int i = 1; i <= n; ++i) { b[i] = (S >> (i - 1)) & 1; }
		int l = 0, r = -1, sm = 0; std::vector <std::pair <int, int>> p;
		for (int i = 1; i <= n; ++i)
		{
			if (b[i]) { if (b[i - 1]) { r = i; } else { l = r = i; } }
			else
			{
				sm += (r - l + 1) * (r - l + 1);
				if (l != 0) { p.push_back({l, r}); }
				l = 0; r = -1; sm += a[i];
			}
		}
		if (b[n] == 1 and l != 0) { p.push_back({l, r}); sm += (r - l + 1) * (r - l + 1); }
		if (sm > mx) { mx = sm; g = p; }
	}
	for (auto [l, r] : g) { f(l, r); res.push_back({l, r}); }
	printf("%d %ld\n", mx, res.size());
	for (auto [l, r] : res) { printf("%d %d\n", l, r); }
}
```

---

## 作者：Iniaugoty (赞：1)

好题。

$n \le 18$ 的范围是极小的，这启示我们可以使用一些指数级别的做法。

同时 $m \le 5 \times 10 ^ 5$ 的限制相对非常宽松，大概不需要考虑减小次数，能构造出来就行。

每个数显然有两种状态：有或没有被修改过。我们枚举每个数的这两种状态，在每一种情况下求得最大值取最优，这部分复杂度 $O (2 ^ n)$。

```cpp
// Solve() 是求解一种情况下的最大值和操作
// sum 和 ans 是最终的答案
// tmp 和 qu 是一种情况下的答案
cin >> n; F(i, 1, n) cin >> a[i];
F(i, 0, (1 << n) - 1) {
	F(j, 1, n) if (i & 1 << j - 1) b[j] = 1;
	// b[j] = 1 则没有被修改
	LL tmp = Solve();
	if (tmp > sum) sum = tmp, swap(qu, ans);
	qu.clear(); F(j, 1, n) b[j] = 0;
} cout << sum << " " << (int) ans.size() << "\n";
for (auto it : ans) cout << it.l << " " << it.r << "\n";
```

接下来，我们需要求，每个数是否要修改 的状态确定的情况下 的最大值和操作，即完成 `Solve()` 函数。

有被修改过的数会被划分为若干个连续段，由于是区间修改，我们只对每个连续段进行考虑。

注意 $\operatorname{mex}$ 有一个性质，只有当 $0 \dots n - 1$ 全在连续段出现过时，才能将整个连续段赋值为 $n$。

思路就很显然了，对于长度为 $n$ 的连续段，先清零（这是为了便于构造，对每个非零的数单独操作就可），然后试着构造出 $n - 1, n - 2, \dots, 1, 0$，将其全赋值为 $n$。

```cpp
// Clac(x, y) 是从 x 开始，构造 y - 1, y - 2, ..., 1, 0
LL Solve() { LL res = 0; // res 是最大值
	F(i, 1, n) if (b[i]) res += a[i];
	F(i, 1, n) { if (b[i]) continue;
		int j = i; while (j < n && !b[j + 1]) ++j;
		res += 1ll * (j - i + 1) * (j - i + 1);
		F(k, i, j) if (a[k]) qu.push_back({k, k});
		Calc(i, j - i + 1), qu.push_back({i, j}), i = j + 1;
	} return res;
}
```

考虑递归构造以完成 `Calc(x, y)` 函数，利用 $y - 1$ 的构造方法得到 $y$ 的构造。

边界条件是当 $y = 1$ 显然什么都不用做。

首先我们需要得到一个 $y - 1$，为了的得到 $y - 1$ 我们需要 $0, \dots y - 2$，所以先从 $x$ 开始构造出 $y - 2, y - 3, \dots, 1, 0$，递归完成。

接下来对 $[x, x + y - 1]$ 进行操作，就能得到一大堆 $y - 1$。

然而后面多出来的 $y - 1$ 不是我们想要的，所以再将 $x + 1$ 后面的都清零，直接对 $[x + 1, x + y - 1]$ 进行操作就行，因为他们只有 $y - 1$。

这时我们有一个 $y - 1$ 和一串 $0$，我们还需要从 $x + 1$ 开始的 $y - 2, y - 3, \dots, 1, 0$，递归完成。

```cpp
void Calc(int x, int y) {
	if (y == 1) return ;
	Calc(x, y - 1);
	qu.push_back({x, x + y - 1});
	qu.push_back({x + 1, x + y - 1});
	Calc(x + 1, y - 1);
}
```

不难发现这个函数的时间复杂度是 $O (n ^ 2)$。

总的时间复杂度是 $O (2 ^ n n ^ 2)$，答案的操作次数在 $n ^ 2$ 级别，绰绰有余。

全文完。

---

## 作者：lfxxx (赞：0)

首先一个结论：对于一段区间，假若至少进行一次操作，那么区间最大权值和为区间长度的平方，也就是说可以通过构造使得每个数都是区间长度。

考虑证明，首先假若原本存在大于区间长度的数，那么不可能再构造一个 $0$ 到其减 $1$ 的排列，故操作一次后必定不大于区间长度，也就是说这段区间的所有数至少操作一次后不可能出现大于区间长度的数。

然后考虑怎么构造使得区间内所有数都等于区间长度。

不妨定义操作过程 $solve(l,r)$ 为将区间 $[l,r]$ 内的数变为一个 $0$ 到 $r-l$ 的排列。

显然有 $solve(l,r)$ 为先进行 $solve(l+1,r)$ 然后对区间 $[l+1,r]$ 进行一次操作使得其中所有数变成 $r-l$，然后再做一次 $solve(l,r-1)$ 后就完成了构造。边界条件是 $l$ 与 $r$ 相等时只要不是 $0$ 就做一次操作即可。

最后再对整个区间进行一次操作即可使得所有数变成 $r-l+1$。

考虑怎么最大化答案，直接 $O(2^n)$ 枚举每一位是否操作，然后将极长连续段权值认为是长度的平方最后选出最优方案即可。

构造方案可以按照证明中的方法构造，定义 $\max(solve(l,r)) = f(r-l+1)$，由于 $f(len) = 2 \times f(len-1) + 1$ 所以需要的操作次数是 $O(2^n)$ 级别的，由于限制比较宽松，所以可以通过。

时间复杂度是 $O(n \times 2^n)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 20;
int a[maxn],b[maxn],n;
int ans;
vector< pair<int,int> > opt;
int calc(int v){
    for(int i=0;i<n;i++) b[i+1]=((1ll<<i)&v);
    int val=0,lst=0;
    for(int i=1;i<=n;i++){
        if(b[i]==0){
            val+=a[i];
            val+=(i-1-lst)*(i-1-lst);
            lst=i;
        }
    }
    val+=(n-lst)*(n-lst);
    return val;
}
//0 1 2
void solve(int l,int r){//0 \to r-l
    if(l==r){
        if(a[l]!=0) opt.push_back(make_pair(l,r));
        a[l]=0;
        return ;
    }
    if(l>r) return ;
    solve(l+1,r);
    opt.push_back(make_pair(l+1,r));
    for(int i=l+1;i<=r;i++) a[i]=(r-l);
    solve(l,r-1);
    for(int i=l;i<=r;i++) a[i]=(r-l+1);
    return ;
}
void build(int v){
    for(int i=0;i<n;i++) b[i+1]=((1ll<<i)&v);
    int lst=0;
    for(int i=1;i<=n;i++){
        if(b[i]==0){
            solve(lst+1,i-1);
            if(lst+1<=i-1) opt.push_back(make_pair(lst+1,i-1));
            lst=i;
        }
    }  
    if(lst+1<=n){
        solve(lst+1,n);
        opt.push_back(make_pair(lst+1,n));
    }
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int p=0;
    for(int i=0;i<(1ll<<n);i++){
        if(calc(i)>ans){
            ans=calc(i);
            p=i;
        }
    }
    build(p);
    cout<<ans<<' '<<opt.size()<<'\n';
    for(pair<int,int> op:opt) cout<<op.first<<' '<<op.second<<'\n';
    return 0;
}
```

---

## 作者：JuRuoOIer (赞：0)

# 题解 CF1956D Nene and the Mex Operator

前排提示：本题是结论题。本题解使用 **DFS** 求最大值和方案。

Update on 2024/4/19：将题意部分的省略号改成了 `\dots` 并重新检查了全文格式。

### 题意

给定长度为 $n$ 的数组 $a_1,a_2,\dots,a_n$，现在可以执行如下操作：
- 选择 $1 \le l,r \le n$，并将 $a_l,a_{l+1},\dots,a_r$ 修改为 $\text{mex}(a_l,a_{l+1},\dots,a_r)$。

求执行若干次操作后数组元素之和的最大值，并构造一种包含不超过 $5\times10^5$ 次操作的方案达到这个最大值。

数据范围：$n \le 18,a_i \le 10^7$。

### 做法

首先有一个很重要的性质：**一个区间的元素经过若干次操作后，可以使整个区间的元素全部变成区间长度。**我们先证明它，并给出构造方案。

注：证明中所有修改均只考虑修改前修改的位置的值不是目标值的情况。

- 对于长度为 $1$ 的区间，显然可以操作一次使其变成 $0$，再操作一次变成 $1$。
- 对于长度为 $2$ 的区间，可以将第一个元素操作一次变成 $0$，第二个元素两次变成 $1$，然后整体操作一次变成 $2$。
- 对于长度为 $3$ 的区间，前两个元素共操作三次变成 $0,1$（对长度为 $2$ 的区间进行操作，但不操作最后一步），然后整体操作使三个元素都变成 $2$，然后再三次操作将前两个元素变成 $0,1$，然后再整体操作使它们都变成 $3$。
- 以此类推，对于长度为 $k$ 的区间，先进行 $2^{k-1}-1$ 次操作把前 $k-1$ 个元素变成 $0,1,\dots,k-2$（对长度为 $k-1$ 的区间进行操作，但不操作最后一步），然后一次操作使所有元素都变成 $k-1$，再进行 $2^{k-1}-1$ 次操作把前 $k-1$ 个元素变成 $0,1,\dots,k-2$，最后整体操作使所有元素变成 $k$。这样一共需要 $(2^{k-1}-1)+1+(2^{k-1}-1)+1=2^k$ 次操作。

由于 $n\le 18$，所以即使整个序列都进行操作，我们仍然只需要 $2^{18}=262144$ 次操作，符合要求。以上的过程只需要一个递归函数就可以实现。

但是我们不一定需要整个序列都操作，比如这个数据：

```
6
1 1 1 10000 1 1
```

显然我们空过中间的 $10000$，把前 $3$ 个和后 $2$ 个分别进行操作，可以得到序列 $[3,3,3,10000,2,2]$，其和为 $10013$，大于整体操作（$[6,6,6,6,6,6]$）的和 $36$。

所以现在我们需要求出哪些元素是需要被操作的。

观察到 $n$ 很小，我们考虑直接暴力搜每个元素是否修改，最后统计答案和方案即可，复杂度仅 $O(n2^n)$（前面那个 $n$ 是复制方案的复杂度）。然后按刚才的方法求出每个连续段操作步骤。

**请注意操作时输出操作步骤后一定要真实地修改原数组。**

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll n,a[20],b[20],tmp[20],mx,mxi[20],tot;
void dfs(ll now,ll tot,ll l){
	if(now==n){
		if(l!=now){
			tot+=(now-l)*(now-l);//别忘了统计最后一段的贡献
		}
		if(tot>mx){
			mx=tot;//更新最大值及方案
			for(int i=0;i<n;i++){
				mxi[i]=tmp[i];
			}
		}
		return ;
	}
	tmp[now]=1;
	dfs(now+1,tot+a[now]+(now-l)*(now-l),now+1);//当前位置不操作，截断一个区间，注意贡献是长度的平方
	tmp[now]=0;
	dfs(now+1,tot,l);
} 
void work(ll l,ll r,ll op){
	//将 [l,r] 改为 0,...,r-l+1，op=1 输出方案，op=0 统计操作次数
	for(int i=l;i<=r;i++){
		if(a[i]!=i-l){
			if(op)cout<<l+1<<' '<<i+1<<endl;
			else tot++;
			for(int j=l;j<=i;j++)a[j]=i-l;//别忘了改 a 数组
			if(i>l)work(l,i-1,op);
		}
	}
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	dfs(0,0,0);//计算最大值和方案
	cout<<mx<<' ';
	mxi[n]=1;
	ll l=0;
	for(int i=0;i<=n;i++){
		if(mxi[i]){//当前位置不操作
			if(i!=l){//结束了一段需要操作的区间
				work(l,i-1,0);//区间变成 0~长度-1
				tot++;//再操作一次，全变成区间长度
			}
			l=i+1;
		}
	}
	cout<<tot<<endl;//输出操作次数
	for(int i=0;i<n;i++)a[i]=b[i];//重置 a 数组
	l=0;
	for(int i=0;i<=n;i++){//除了记录 tot 改为输出之外与前面统计 tot 部分相同
		if(mxi[i]){
			if(i!=l){
				work(l,i-1,1);
				cout<<l+1<<' '<<i<<endl;
			}
			l=i+1;
		}
	}
	return 0;
}
```

---

## 作者：ZhongYuLin (赞：0)

我们首先会注意到，一个长度为 $n$ 的全为 $0$ 的区间，可以通过操作使他的和为 $n^2$。具体地，对于序列 $[l,r]$，使 $\forall i \in[l,r-1],a_i=i-l$，然后对整个区间进行一次取 mex；接下来再次使 $\forall i \in[l,r-1],a_i=i-l$，便使得 $\forall i \in[l,r],a_i=i-l$，从而可以推至 $[l,r+1]$。

我们现在尝试分析复杂度。设 $T(n)$ 表示长度为 $n$ 的全 $0$ 序列转化为 $0$ 至 $n-1$ 的等差数列所需次数。显然 $T(1)=1$；同时对构造过程分析，发现 $T(n)=2T(n-1)+1$。于是 $T(n)=2^n-1$。$n=18$ 时，略小于限制。

而最优答案的找出在这个复杂度下是简单的。搜索即可。本文给出枚举的写法。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20,M=1e7+10;
int a[N];
int n,ans,id;
vector<pair<int,int>>out;
int calc(int x){
    int lst=0,ans=0;
    for(int i=0;x>=1<<i;++i)
        if(x&(1<<i))ans+=a[i]+(i-lst)*(i-lst),lst=i+1;
    return ans+(n-lst)*(n-lst);
}
void work(int l,int r){//使得区间变为0,1,2,3...n-1
    if(l==r){
        if(a[l])out.push_back({l,l});
        return;
    }
    work(l,r-1);
    out.push_back({l,r});
    for(int i=l;i<=r;++i)a[i]=1;
    work(l,r-1);
}
void solve(int l,int r){
    if(l>r)return;
    if(l==r){
        if(!a[l])out.push_back({l,l});
        return;
    }
    //将区间全赋0
    for(int i=l;i<=r;++i)if(a[i])out.push_back({i,i}),a[i]=0;
    //将区间全赋n
    work(l,r);
    out.push_back({l,r});
}
int main(){
    ios::sync_with_stdio(cin.tie(cout.tie(0)));
    cin>>n;
    for(int i=0;i<n;++i)cin>>a[i];
    //找出最优情况
    for(int i=0;i<1<<n;++i){
        int res=calc(i);
        if(ans<res)ans=res,id=i;
    }
    //构造最优情况
    int lst=0;
    for(int i=0;id>=1<<i;++i)
        if(id&(1<<i))solve(lst,i-1),lst=i+1;
    solve(lst,n-1);
    //输出
    printf("%d %d\n",ans,out.size());
    for(auto x:out)printf("%d %d\n",x.first+1,x.second+1);
    return 0;
}
```

---

## 作者：Luzhuoyuan (赞：0)

Links: [[Codeforces]](https://codeforces.com/contest/1956/problem/D) [[Luogu]](https://www.luogu.com.cn/problem/CF1956D)

已经习惯完赛前十分钟想出做法来不及写遗憾离场了。

### 题意简述

给定一个长为 $n$ 的非负整数序列 $a$，定义一次操作为：选择正整数 $l,r$ 满足 $1\le l\le r\le n$，令 $x$ 为 $a_l,a_{l+1},\dots,a_r$ 的 MEX 值，将 $a_l,a_{l+1},\dots,a_r$ 都赋值为 $x$。求长度不超过 $5\cdot 10^5$ 的操作序列使得 $a$ 序列元素总和最大。可以证明 $a$ 序列元素的总和可以在不超过 $5\cdot 10^5$ 次操作后达到最大值。

- $1\le n\le 18;$
- $0\le a_i\le 10^7$。

### 思路

首先我们考虑对一个序列的每个位置都做操作能构造出怎样的结果。显然最终每个元素不会超过该序列的长度，因为要构造出 $x$ 的 MEX 值至少要出现 $0,1,\dots,x-1$ 总共 $x$ 个元素。

然后思考能否构造出每个元素都等于序列长度的情况。如果要构造这种情况，我们可以使得 $a_i=n-i(1\le i\le n)$，然后进行一次 $(1,n)$ 的操作。接下来的问题是如何让 $a_1=n-1$，我们可以先让 $a_i=n-i(2\le i\le n)$，然后做一次 $(1,n)$，这样 $a_1$ 就为 $n-1$ 了，然后再让 $a_i=n-i(2\le i\le n)$，这样就满足 $a_i=n-i(1\le i\le n)$ 了。

我们发现这是一个递归的过程，对于处理 $[i,n]$ 的区间就可以这样做（为了方便，假设最初 $\forall 1\le j\le n,a_j>0$）：

- 进行 $(i,i)$（使得 $a_i=0$）；
- 如果 $i=n$，停止操作；
- 递归操作 $[i+1,n]$；
- 进行 $(i,n)$（使得 $a_i=n-i$）；
- 递归操作 $[i+1,n]$。

设 $f(n)$ 表示长为 $n$ 的序列所需操作数，则有 $f(1)=1,f(n)=2f(n-1)+2$，即 $f(n)=1+3\cdot(2^{n-1}-1)$，得到 $f(18)<4\cdot 10^5$。

当然，原序列中可能存在一些很大的数，我们不应该对于这些位置操作，否则答案会变小。所以我们要处理的是一段一段的位置。我们可以用一个简单的区间 DP 算出来每个区间的最大元素总和。令 $f_{i,j}$ 表示区间 $[i,j]$ 的最大总和，那么可以从三种方法转移：

- 这个区间整个都不操作，$f_{i,j}\gets s_j-s_{i-1}$；
- 这个区间整个都操作，$f_{i,j}\gets (j-i+1)^2$；
- 这个区间分成几个小区间，$\displaystyle f_{i,j}\gets\max_{k=i}^{j-1}\{f_{i,k}+f_{k+1,j}\}$。

其中 $s$ 是 $a$ 的前缀和数组。

之后构造操作序列，我们可以考虑当前的 $f_{i,j}$ 是怎么来的（~~DP 的时候要想清楚自己为什么姓王，为什么姓张~~），对应地进行操作即可。为了方便，可以把每个要整个操作的区间中的等于 $0$ 的位置进行一次操作变成 $1$，以满足上面 $a_j>0$ 的条件。

然后就做完了。复杂度 $O(n^3+2^n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=20;
int n,a[N],s[N],f[N][N];
struct node{int l,r;};
vector<node> ans;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
inline void dfs1(int l,int r){ans.pb({l,l});if(l==r)return;dfs1(l+1,r);ans.pb({l,r});dfs1(l+1,r);}
//递归处理操作序列
void dfs(int l,int r){
	if(f[l][r]==s[r]-s[l-1])return;
	if(f[l][r]==(r-l+1)*(r-l+1)){for(int i=l;i<=r;i++)if(!a[i])ans.pb({i,i});dfs1(l,r),ans.pb({l,r});return;}
	for(int i=l;i<r;i++)if(f[l][r]==f[l][i]+f[i+1][r])return dfs(l,i),dfs(i+1,r);
}//递归找当初是怎么转移的
signed main(){
	n=read();for(int i=1;i<=n;i++)s[i]=s[i-1]+(a[i]=read());
	for(int i=1;i<=n;i++)for(int j=1;j<=n-i+1;j++){
		int k=j+i-1;f[j][k]=max(s[k]-s[j-1],i*i);
		for(int l=j;l<k;l++)f[j][k]=max(f[j][k],f[j][l]+f[l+1][k]);
	}
	dfs(1,n);printf("%d %d\n",f[1][n],(int)ans.size());
	for(node v:ans)printf("%d %d\n",v.l,v.r);
	return 0;
}
```

（逃

---

## 作者：紊莫 (赞：0)

非常好 Weak Pretest。

---

贪心做法。

首先我们通过构造可得一个长度为 $n$ 的区间，一定可以变成 $n^2$。

以长度为 $4$ 的全 $0$ 序列为例。

$$\begin{aligned}
\\
[0,0,0,0]
\\
[1,0,0,0]
\\
[2,2,0,0]
\\
[2,0,0,0]
\\
[2,1,0,0]
\\
[3,3,3,0]
\\
[3,0,3,0]
\\
[3,0,0,0]
\\
[3,1,0,0]
\\
[3,2,2,0]
\\
[3,2,0,0]
\\
[3,2,1,0]
\\
[4,4,4,4]
\end{aligned}$$

容易发现，我们需要递归地进行操作，这是经典的。

然后问题就在于选择合适的区间操作，在这里我直接选择贡献最大的进行操作，因为操作之间不相交，这样显然是对的。

其余细节见代码。

```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
inline int rd(){
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9'){
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

typedef long long ll;
typedef pair<int, int> Pair;

const int N = 25, M = (N << 1), inf = 1e16, mod = 1e9 + 7;
int n, ans, a[N], v[N];
vector<Pair> vec, way;

void work (int l, int r) {
    if (l > r) return ;
    F(i, l, r) {
        if (a[i] != 0) {
            way.emplace_back(i, i);
            a[i] = 0;
        }
    }
    way.emplace_back(l, l);
    F(i, 1, r - l) {
        F(j, l + 1, l + i - 1)  
            work(j, l + i - 1);
        way.emplace_back(l, l + i);
        F(j, l, l + i) a[j] = i;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n; F(i, 1, n) cin >> a[i];
    int cnt = 0;
    for (int i = 1; i <= n; i ++) {
        F(j, i, n) {
            int sum = 0;
            F(k, i, j) {
                sum += a[k];
            }   
            if (sum < (j - i + 1) * (j - i + 1)) {
                vec.emplace_back(i, j);
            }
        }
    }

    sort(vec.begin(), vec.end(), [](Pair x, Pair y) {
        int sum1 = (x.second - x.first + 1) * (x.second - x.first + 1), sum2 = (y.second - y.first + 1) * (y.second - y.first + 1);
        F(i, 1, n) {
            if (i < x.first || i > x.second) sum1 += a[i];
            if (i < y.first || i > y.second) sum2 += a[i];
        }
        return sum1 > sum2;
    });
    auto check = [&](int l, int r) {
        F(i, l, r) if (v[i]) return 0;
        return 1;
    } ;
    for (auto i : vec) {
        if (!check(i.first, i.second)) continue ;
        work(i.first, i.second);
        F(j, i.first, i.second) {
            a[j] = i.second - i.first + 1, v[j] = 1;
        }
    }
    F(i, 1, n) {
        ans += a[i];
    }

    cout << ans << ' ' << way.size() << endl;
    for (auto i : way) {
        cout << i.first << ' ' << i.second << '\n';
    }
    return 0;
}

```

---

## 作者：int08 (赞：0)

## 前言
众所周知，一篇题解需要一张头图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ofd1y7zx.png)

我释怀地似了。

所以为什么 `C>>>>>>>>D` 啊！

# Solution

### 观察结论，暴力枚举求得最大值

观察样例，我们发现一个结论：

一个位置如果从来没被操作过，就会保留原来的值，否则一旦被操作过，原值就无意义了。

对于一段极长而连续的长为 $x$ 的**被操作过的**区间，可以发现每个位置最大只能是 $x$，因为这个区间的 $\text{MEX}$ 必然小于等于 $x$（一共只有 $x$ 个数，最好也就从 $0$ 到 $x-1$），而可以猜测，这个最大值也是一定能构造出来的。

那这下简单了，用状压的方式枚举哪些位置是被操作过的，找到所有的极长被操作区间并加上它们长度的平方和，剩下的加原值，找到最大情况。

其实也可以区间 DP 等方法找到最大情况，但是数据范围在此，杀鸡焉用牛刀。

### 用连续被操作区间构造 $x$ 个 $x$

首先把它们变成全是 $0$ 是简单的，根据区间里有没有零选中整个区间操作一或两次即可。
然后你发现，你可以用长为 $2$ 的区间构造出两个 $1$，再单选一个把它变回 $0$，再全选一次就构造出了两个 $2$，那么当区间长为 $3$ 时，你用这样的方法在另外两个位置构出 $0,1$，就可以构造出 $3$，数学归纳法，可以证明你可以用长为 $n$ 的区间构造出 $n$ 个 $n$。

既然构造都用的归纳法，那我们实现也就用递归好了。

见代码，非常简洁，在完全不压行的情况下仍是并列最短解。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,i,j,a[1145141],mx,mxzt,l,r;
vector<pair<int,int> > op;
void make(int l,int r)
{
	int x=r-l;
	if(!x) return;
	for(int i=l+1;i<=r;i++) make(i,r); //依次构造 0~x-1
	op.push_back({l,r}),op.push_back({l+1,r}); //构造 x 个 x 并删除多余的
}
int main()
{
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=0;i<(1<<n);i++)
	{
		int cnt=0,ans=0;
		for(j=1;j<=n+1;j++)
		{
			if(i&(1<<(j-1))) cnt++;
			else
			{
				ans+=cnt*cnt;
				ans+=a[j];
				cnt=0;
			}
		}
		if(ans>=mx) mx=ans,mxzt=i;
	}
	cout<<mx;
	int l=1,r,tg;
	for(i=1;i<=n+1;i++)
	if((mxzt&(1<<(i-1)))==0)
	{
		if(l==i)
		{
			l=i+1;
			continue;
		}
		r=i-1,tg=1;
		for(j=l;j<=r;j++) tg=min(tg,a[j]);
		op.push_back({l,r});
		if(!tg) op.push_back({l,r});
		for(j=l;j<=r;j++) make(j,r);
		op.push_back({l,r});
		l=i+1;
	}
	cout<<" "<<op.size()<<endl;
	for(auto v:op)
	cout<<v.first<<" "<<v.second<<endl;
	return 0;
 } 
```
# The End.

---

## 作者：cosf (赞：0)

这道题分两部分。

### 第一部分：如果序列全是 $0$

我们可以通过一定次数内将长度为 $n$ 的，全是 $0$ 的区间变成全是 $n$ 的。举一个 $n=4$ 的例子：

| 操作数 | 结果 |
| -- | -- |
| $0$ | $0000$ |
| $1$ | ${\color{red}1}000$ |
| $2$ | ${\color{red}22}00$ |
| $3$ | $2{\color{red}0}00$ |
| $4$ | $2{\color{red}1}00$ |
| $5$ | ${\color{red}333}0$ |
| $6$ | $3{\color{red}00}0$ |
| $7$ | $3{\color{red}1}00$ |
| $8$ | $3{\color{red}22}0$ |
| $9$ | $32{\color{red}0}0$ |
| $10$ | $32{\color{red}1}0$ |
| $11$ | $\color{red}4444$ |

可以发现，这个过程可以用递归解释。以下步骤是构建长度为 $n$ 的递降数列 $\{n - 1, n - 2, \dots, 0\}$ 的方法：

1. 令循环变量 $i = 1$。
2. 从第 $2$ 位开始构建一个长度为 $i-1$ 的递降数列。
3. 从第 $1$ 位到第 $i$ 位进行操作，此时它们会全部变成 $i$。
4. 从第 $2$ 位到第 $i$ 位进行操作，此时它们会全部变成 $0$。
5. 让 $i \gets i + 1$。
6. 如果 $i \lt n-1$，返回至第 $2$ 步。
7. 从第 $2$ 位开始构建一个长度为 $n-1$ 的递降数列。

一但有了递降数列，我们只要对整个数列操作一下就全部变成数列长度 $n$ 了。

假设 $s_n$ 表示让 $n$ 个 $0$ 全部变成 $n$ 的步数，则可以证明，$s_{n + 1} \gt 2s_n$。当 $n = 18$ 时，步数足够。

### 第二部分：有值了

有值了，我们可以强行把数列“推平”，即全部让它变成 $0$，然后再把它们全部变成长度。

但是，有些情况不行。例如说样例 $[1,100,1,2]$。显然不能把 $100$ 推平。所以我们要想办法判断每一个数是否要“剪断”，即保留它不动，两边各自处理。

显然，如果一个区间的最大值都没有长度那么大，推平就是最优解。

如果不是，则需要测试一下将区间内最大的数剪断是什么情况。如果两边各自处理得出的和加上最大数比长度的平方大，则剪断更优，否则推平。

## 代码

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 20

using ll = long long;

using pii = pair<int, int>;

ll val[MAXN];
bool cut[MAXN]; // whether to cut or not.

int n;

vector<pii> res;

ll dfs1(int l, int r) // decide whether to cut or not.
{
    if (l > r)
    {
        return 0;
    }
    int m = l;
    for (int i = l + 1; i <= r; i++) // since n is really small, we can calculate the max by brute force.
    {
        if (val[i] > val[m])
        {
            m = i;
        }
    }
    ll cu = dfs1(l, m - 1) + val[m] + dfs1(m + 1, r);
    if (cu >= (r - l + 1) * (r - l + 1))
    {
        cut[m] = true;
        return cu;
    }
    else
    {
        return (r - l + 1) * (r - l + 1);
    }
}

void mak(int len, int ofs) // make descending subarray.
{
    for (int i = 1; i <= len; i++)
    {
        res.push_back({ofs + 1, ofs + i});
        if (i > 1)
        {
            res.push_back({ofs + 2, ofs + i});
        }
        mak(i - 1, ofs + 1);
    }
}

void dfs2(int l, int r)
{
    if (l > r)
    {
        return;
    }
    int m = l;
    for (int i = l + 1; i <= r; i++)
    {
        if (val[i] > val[m])
        {
            m = i;
        }
    }
    if (cut[m])
    {
        dfs2(l, m - 1);
        dfs2(m + 1, r);
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            if (val[i] != 0)
            {
                res.push_back({i, i});
            }
        }
        mak(r - l, l - 1);
        res.push_back({l, r});
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }
    cout << dfs1(1, n) << ' ';
    dfs2(1, n);
    cout << res.size() << endl;
    for (pii q : res)
    {
        cout << q.first << ' ' << q.second << endl;
    }
    return 0;
}

```

---

## 作者：Exp10re (赞：0)

好题。

## 解题思路

注意到 $n$ 很小。猜测操作次数是 $O(2^n)$ 级别的。

注意到对于一个长度为 $len$ 的段可以使用 $O(2^{len})$ 规模的操作次数来使得这一段均变成 $len$，此时这一段的权值和为 $len^2$。

具体操作如下：

- 考虑使得这一段变为 $0,1,\cdots,len-1$，然后使用一次操作使其变为全 $len$。

- 不难发现要使得第 $i$ 位变为 $i-1$，就必须保证前 $i-1$ 位为 $0,1,\cdots,i-2$。发现可以递归。

- 记 $\operatorname{work}(i)$ 表示将第 $i$ 位变为 $i-1$，那么构造前 $i-1$ 位为 $0,1,\cdots,i-2$ 就相当按照 $k$ 顺序进行多次 $\operatorname{work}(i-k),k\in[1,i-1]$，然后对 $(1,i)$ 进行一次操作，最后对于前面的位将其变为全 $0$ 即可。

- 考虑用递归表示，边界为 $x=1$。

那么其余的部分用动态规划即可得到最优解：

- 记 $f_i$ 表示不对第 $i$ 位进行任何操作，前 $i$ 位的最大权值和。

- 转移考虑上述做法，不难发现即为 $f_i \leftarrow f_j+(i-j-1)^2,j\in[1,i-1]$。

时间复杂度为 $O(2^n)$，没有[另一篇题解](https://www.luogu.com.cn/article/kprvvjlf)的 $n$ 的系数原因为初始设置全 $0$ 可以免去考虑 $\operatorname{MEX}$ 的值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=100,MAXP=500100;
long long n,m,a[MAXN],vis,f[MAXN],rec[MAXN][MAXN],mmov[MAXP][3];
void mov(long long l,long long r)
{
	m++;
	mmov[m][1]=l;
	mmov[m][2]=r;
	return;
}
void clr(long long l,long long r)
{
	long long i;
	for(i=l;i<=r;i++)
	{
		mov(i,i);
	}
	return;
}
void work(long long l,long long r)
{
	if(l==r)
	{
		return;
	}
	long long i;
	for(i=r-1;i>=l;i--)
	{
		work(l,i);
	}
	mov(l,r);
	clr(l,r-1);
	return;
}
int main()
{
	memset(f,-0x3f,sizeof(f));
	long long i,j,rrec,ccnt=0,trec,flag;
	f[0]=0;
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	a[n+1]=0;
	a[0]=0;
	rec[0][0]=1;
	for(i=1;i<=n+1;i++)
	{
		rrec=0;
		for(j=0;j<i;j++)
		{
			if(f[j]+a[i]+(i-j-1)*(i-j-1)>f[i])
			{
				f[i]=f[j]+a[i]+(i-j-1)*(i-j-1);
				rrec=j;
			}
		}
		for(j=0;j<=i-1;j++)
		{
			rec[i][j]=rec[rrec][j];
		}
		rec[i][i]=1;
	}
	printf("%lld ",f[n+1]);
	flag=0;
	trec=1;
	for(i=1;i<=n+1;i++)
	{
		if(rec[n+1][i])
		{
			if(!rec[n+1][i-1])
			{
				for(j=trec;j<=i-1;j++)
				{
					if(a[j]!=0)
					{
						mov(j,j);
						a[j]=0;
					}
				}
				for(j=i-1;j>=trec;j--)
				{
					work(trec,j);
				}
				mov(trec,i-1);
			}
			trec=i+1;
		}
	}
	printf("%lld\n",m);
	trec=1;
	flag=0;
	for(i=1;i<=m;i++)
	{
		printf("%lld %lld\n",mmov[i][1],mmov[i][2]);
	}
	return 0;
}
```

---

## 作者：_lgh_ (赞：0)

*2000.

考虑一段区间 $[l,r]$ 一定可以被全部推平成 $r-l+1$，构造类似 $0,1,2,\dots,r-l$ 即可。

又因为 $n\le 18$，可以 $2^n$ 枚举所有位是否被推平，找出最大值。

因此考虑如何输出。考虑构造出形如 $0,1,\dots,x$ 的形式必定是对 $0,1,\dots,x-1,t$ 做一次区间推平，然后再把前面一段改回 $0,1,\dots,x-1$。

因此可以递归地进行处理，处理 $[l,r]$ 时先递归 $[l,r-1]$，然后更改 $[l,r]$，再更改 $[l,r-1]$。需要注意，在每次操作之前先把每一位归零，区间覆盖完 $[l,r]$ 之后先把 $[l,r-1]$ 清零。

贴一个输出方案的代码：

```cpp
// vector<pair<int,int> >Oper;
	auto Out=[&](auto self,int l,int r)->void {
		if(l==r) return;
		self(self,l,r-1);
		oper.pb(mk(l,r));
		for(int i=l; i<r; i++) oper.pb(mk(i,i));
		self(self,l,r-1);
	};
	auto out=[&](int l,int r) {
		for(int i=l; i<=r; i++) if(a[i]!=0) oper.pb(mk(i,i));
		Out(Out,l,r);
		oper.pb(mk(l,r));
	};
```

---

## 作者：arrow_king (赞：0)

# 题意

给定一个长度为 $n$ 的数列 $a_1,a_2,\dots,a_n$。

你可以执行以下操作不超过 $5\times10^5$ 次（可能为 $0$）：

- 选择一个区间 $[l,r]$，并将区间内所有数换成这个区间的 MEX。

MEX 的定义是没有出现过的最小非负整数。

你要最大化操作后整个数组的和，并且给出一个操作方案，不需要最小化操作次数。

$n\le18,0\le a_i\le10^7$

# 分析

看到 $n\le18$，瞬间感到手足无策……

$n$ 实在太小了，$2^n$ 的做法很轻松就能过去。于是联想到状压 dp。但是又不知道怎么设计状态。哎，还是换个思路吧。

首先考虑一下：如果我就是想将整个区间推成 $\text{length}$ 该怎么做。

假设这个区间内的数全都大于 $0$，那么显然，我需要将第一个数变成 $0$、第二个数变成 $1$，……第 $n-1$ 个数变成 $n-1$，才能最后将第 $n$ 个数增加进来，一起合体成为 $n$。

考虑这个过程会花费多少操作。设 $T_i$ 表示将长度为 $i$ 的区间整体变成 $i$ 的代价，那么显然有

$$T_0=0,T_i=\sum_{j=0}^{i-1}T_j+1$$

解这个递推式得到 $T_i=2^i-1$。这启示我们：就算将整个区间推平成长度，那么花费的总操作数也是 $O(2^n)$ 量级的，$5\times10^5$ 次操作根本用不完。

那么开始 dp。设 $dp_{l,r}$ 表示对 $[l,r]$ 区间实施操作后的最大价值，同时再记一个辅助数组 $e_{l,r,i}$ 表示在对 $[l,r]$ 取最优操作过后、这个区间下标为 $i$ 的元素是什么，这个数组能够方便构造答案。

接下来考虑转移。类似区间 dp，先枚举区间并且设区间 $e$ 数组的值为原数组值、$dp$ 值为原数组值的和（不进行任何操作）。接下来枚举断点 $k$，进行鲁莽合并：$dp_{i,j}=\max\{dp_{i,k}+dp_{k+1,j}\}$。最后再进行推平。注意到推平后的结果肯定不能大于区间长度，因此最优选择就是不管原来是什么直接推到区间长度。转移之后不要忘记更新辅助数组。答案就是 $dp_{1,n}$。

最后考虑构造答案。首先开始的时候有一个假设是所有的数都大于 $0$。如果有 $0$ 就先对它取一个 MEX 让它变成 $1$。接下来递归地构造，从 $[1,n]$ 区间开始构造。当枚举到一个区间时，首先判定这个区间有没有进行操作，进而判断它是有哪一种操作转移过来的。如果是由子区间合并方式，那么递归构造；如果是推平区间过来的，那么按照推平的方式构造答案。

时间复杂度：dp 的复杂度显然是 $O(n^4)$，而由于操作最多有 $O(2^n)$ 个所以总时间复杂度为 $O(2^n)$。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,a[20],sum[20];
int li[25][25][25],dp[25][25];
vector<pair<int,int> > ans;
il void insert(int l,int r) {
	if(l==r) {
		ans.push_back(make_pair(l,l));ans.push_back(make_pair(l,l));
		return;
	}
	for(int i=r-1;i>=l;i--) insert(l,i);
	ans.push_back(make_pair(r,r)),ans.push_back(make_pair(l,r));
}
il void gouzao(int i,int j) {
	if(dp[i][j]==sum[j]-sum[i-1]) return;
	int ok=1;
	for(int k=i+1;k<=j;k++) if(li[i][j][k]!=li[i][j][k-1]) ok=0;
	if(ok) {
		insert(i,j);
		return;
	}
	for(int k=i;k<j;k++) {
		bool ok=1;
		for(int l=i;l<=k;l++) if(li[i][j][l]!=li[i][k][l]) ok=0;
		for(int l=k+1;l<=j;l++) if(li[k+1][j][l]!=li[k+1][j][l]) ok=0;
		if(ok) {
			gouzao(i,k),gouzao(k+1,j);
			return;
		}
	}
}
int main() {
	n=read();
	for(int i=1;i<=n;i++) {
		a[i]=read();
		if(a[i]==0) ans.push_back(make_pair(i,i)),a[i]=1;
		sum[i]=sum[i-1]+a[i];
	}
	for(int l=1;l<=n;l++) {
		for(int i=1;i+l-1<=n;i++) {
			int j=i+l-1;
			dp[i][j]=sum[j]-sum[i-1];
			for(int k=i;k<j;k++) {
				if(dp[i][k]+dp[k+1][j]>dp[i][j]) {
					dp[i][j]=dp[i][k]+dp[k+1][j];
					for(int m=i;m<=k;m++) li[i][j][m]=li[i][k][m];
					for(int m=k+1;m<=j;m++) li[i][j][m]=li[k+1][j][m];
				}
			}
			int minn=l;
			if(minn*l<=dp[i][j]) continue;
			else {
				dp[i][j]=minn*l;
				for(int m=i;m<=j;m++) li[i][j][m]=minn;
			}
		}
	}
	printf("%d ",dp[1][n]);
	gouzao(1,n);
	printf("%d\n",ans.size());
	for(auto p:ans) printf("%d %d\n",p.first,p.second);
	return 0;
}

```

---

