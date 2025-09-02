# [ABC390F] Double Sum 3

## 题目描述

给定一个长度为 $N$ 的整数序列 $A = (A_1, A_2, \ldots, A_N)$。

对于满足 $1 \leq L \leq R \leq N$ 的整数对 $(L, R)$，定义 $f(L, R)$ 如下：

- 初始时，在黑板上按顺序写下 $R-L+1$ 个整数 $A_L, A_{L+1}, \ldots, A_R$。
- 重复以下操作直到黑板上所有整数被清除：
  - 选择两个整数 $l, r$，需满足 $l \leq r$ 且黑板上当前存在的所有 $[l, r]$ 范围内的整数至少各出现一次。随后清除黑板上所有 $[l, r]$ 范围内的整数。
- $f(L, R)$ 定义为清除所有整数所需的最小操作次数。

请计算 $\displaystyle \sum_{L=1}^N \sum_{R=L}^N f(L, R)$ 的值。


## 说明/提示

### 约束条件

- $1 \leq N \leq 3 \times 10^5$
- $1 \leq A_i \leq N$
- 输入的所有值均为整数

### 样例解释 1

以 $(L, R) = (1, 4)$ 为例，计算 $f(L, R)$ 的过程如下：  
- 黑板上初始有 $1, 3, 1, 4$。  
- 选择 $(l, r) = (1, 1)$，清除所有 $1$，此时黑板上剩余 $3, 4$。  
- 选择 $(l, r) = (3, 4)$，清除 $3, 4$。  
- 无法在少于 $2$ 次操作内完成清除，因此 $f(1, 4) = 2$。  

类似地，可得 $f(2, 4) = 2$，$f(1, 1) = 1$ 等。  
总和 $\displaystyle \sum_{L=1}^N \sum_{R=L}^N f(L, R) = 16$，因此输出 $16$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1 3 1 4```

### 输出

```
16```

## 样例 #2

### 输入

```
5
3 1 4 2 4```

### 输出

```
23```

## 样例 #3

### 输入

```
10
5 1 10 9 2 5 6 9 1 6```

### 输出

```
129```

# 题解

## 作者：rui_er (赞：15)

题面中进行的三个操作相当于：

- 将集合 $S=\{a_i\mid L\le i\le R\}$ 划分为尽量少的集合的并集，其中每个集合包含一段连续整数。

注意到，一个连续整数段结束的标志是 $x\in S$ 且 $(x+1)\notin S$。这意味着，无论 $x$ 属于什么连续整数段，它的后继 $y$ 一定属于一个新的段。因此，我们只需要统计每个整数 $x$ 对多少个区间有贡献即可，即对于每个整数 $x$，统计有多少个区间中有 $x$ 而没有 $x+1$。

但这样依然不是很好统计，因为一个区间可能包含多个 $x$，容易数重或数漏。我们规定，每个符合要求的区间在其中包含的第一个 $x$ 处被统计。

设 $pre_i$ 为最大的 $j<i$ 使得 $A_j=x$ 或 $A_j=x+1$，$nxt_i$ 为最小的 $j>i$ 使得 $A_j=x+1$。那么，任取 $pre_i < L\le i$ 和 $i\le R < nxt_i$，都满足 $A_i$ 是区间 $[L,R]$ 包含的第一个 $x$，且区间 $[L,R]$ 不包含 $x+1$。这样的区间共有 $(i-pre_i)(nxt_i-i)$ 个。

将每个 $A_i$ 处的区间个数相加，答案即为 $\sum\limits_{i=1}^n(i-pre_i)(nxt_i-i)$。

核心代码：

```cpp
#define rep(x, y, z) for(ll x = (y); x <= (z); ++x)
#define per(x, y, z) for(ll x = (y); x >= (z); --x)

ll n, a[N], pos[N], pre[N], nxt[N], ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n + 1) pos[i] = 0;
    rep(i, 1, n) {
        pre[i] = max(pos[a[i]], pos[a[i] + 1]);
        pos[a[i]] = i;
    }
    rep(i, 1, n + 1) pos[i] = n + 1;
    per(i, n, 1) {
        nxt[i] = pos[a[i] + 1];
        pos[a[i]] = i;
    }
    rep(i, 1, n) ans += (nxt[i] - i) * (i - pre[i]);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Zi_Gao (赞：8)

首先我们了解一下点边容斥，目标是数一个树上的联通块个数，我们知道一棵树有 $n$ 个点，那么就有 $n-1$ 条边，所以只需要数所有的点个数减去所有的边个数就行。

那么这道题实际上是一条链数联通块，那么同样这样数就行，从左到右扫描线，记录每个点 $a_i$ 上一次出现的位置 $p_{a_i}$，那么固定 $R$ 到 $i$，对于所有的 $L$，会贡献 $i-p_{a_i}$ 个点。

现在来看边，会影响的只有两条边，到 $a_i-1$ 和 $a_i+1$，分析一下到 $a_i-1$，那么需要算出 $L\in(p_{a_i},i]$ 贡献多少条边，那么就是 $\max(p_{a_{i}-1}-p_{a_i},0)$，到 $a_i+1$ 同理。

代码很简洁，轻松最优解：

```cpp
#include<bits/stdc++.h>

int pre[300010];

int main(){
    int i,j,a,n;
    long long res=0,cnt=0;
	scanf("%d",&n);
    for(i=1;i<=n;++i) scanf("%d",&a),res+=(cnt+=i-pre[a]-std::max(pre[a-1]-pre[a],0)-std::max(pre[a+1]-pre[a],0)),pre[a]=i;

    printf("%lld",res);

    return 0;
}
```

---

## 作者：Inzaghi_Luo (赞：7)

首先要看出来 $f(L,R)$ 的值就是这中间值域连续段的个数。然后我们再考虑，如果对于一个 $f(L,R)$ 左端点向右移动会产生什么贡献。

来分讨一下，设删掉的数是 $a_L$，如果剩下的数中有等于 $a_L$ 的，那么就不会产生贡献，如果没有，我们来看 $a_L-1$ 和 $a_L+1$ 是否存在。如果两个都存在，会使 $f$ 的值加一，如果存在一个就不变，如果都不存在就会减一。分别对应删掉一个连续段，不变和一个连续段变两个。

先预处理出左端点为 $1$ 时所有 $f$ 的值，然后我们就可以从左往右枚举左端点，每次删掉当前的左端点，用线段树维护即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 300005;
int a[MAXN], f[MAXN];
int t[MAXN], nxt[MAXN][3];
struct node{
	int lson, rson, sum, tag;
}seg[MAXN << 2];
int cnt;
void pushup(int x){
	seg[x].sum = seg[seg[x].lson].sum + seg[seg[x].rson].sum;
}
void pushdown(int x, int l, int r, int mid){
	if(!seg[x].tag) return ;
	int ls = seg[x].lson, rs = seg[x].rson;
	seg[ls].tag += seg[x].tag;
	seg[ls].sum += seg[x].tag * (mid - l + 1);
	seg[rs].tag += seg[x].tag;
	seg[rs].sum += seg[x].tag * (r - mid);
	seg[x].tag = 0; 
}
void Build(int &x, int l, int r){
	x = ++cnt;
	if(l == r){
		seg[x].sum = f[l];
		return ;
	}
	int mid = l + r >> 1;
	Build(seg[x].lson, l, mid);
	Build(seg[x].rson, mid + 1, r);
	pushup(x);
}
void change(int x, int l, int r, int L, int R, int v){
	if(L > R) return ;
	if(L <= l && r <= R){
		seg[x].tag += v;
		seg[x].sum += (r - l + 1) * v;
		return ;
	}
	if(l > R || r < L) return ;
	int mid = l + r >> 1;
	pushdown(x, l, r, mid);
	change(seg[x].lson, l, mid, L, R, v);
	change(seg[x].rson, mid + 1, r, L, R, v);
	pushup(x);
}
int query(int x, int l, int r, int L, int R){
	if(L <= l && r <= R) return seg[x].sum;
	if(l > R || r < L) return 0;
	int mid = l + r >> 1;
	pushdown(x, l, r, mid);
	return query(seg[x].lson, l, mid, L, R) + query(seg[x].rson, mid + 1, r, L, R);
}
void print(int x, int l, int r){
	if(l == r){
		printf("%lld ", seg[x].sum);
		return ;
	}
	int mid = l + r >> 1;
	pushdown(x, l, r, mid);
	print(seg[x].lson, l, mid);
	print(seg[x].rson, mid + 1, r);
	pushup(x);
}
signed main(){
	int n;
	scanf("%lld", &n);
	for(int i = 1;i <= n;i++){
		scanf("%lld", &a[i]);
	}
	//先求出以1为l的所有f 
	for(int i = 1;i <= n;i++){
		f[i] = f[i - 1];
		if(!t[a[i]]){
			if(t[a[i] - 1] && t[a[i] + 1]) f[i]--;
			if(!t[a[i] - 1] && !t[a[i] + 1]) f[i]++;
		}
		t[a[i]] = 1;
	}
	//处理nxt
	for(int i = 0;i <= n + 1;i++){
		t[i] = n + 1;
	}
	for(int i = n;i;i--){
		nxt[i][0] = t[a[i] - 1];
		nxt[i][1] = t[a[i]];
		nxt[i][2] = t[a[i] + 1];
		t[a[i]] = i;
	} 
	int rt;
	Build(rt, 1, n);
	int ans = 0;
	for(int i = 1;i <= n;i++){
		ans += query(1, 1, n, i, n);
		int w0 = nxt[i][0], w = nxt[i][1], w1 = nxt[i][2];
		if(w0 > w1) swap(w0, w1);
		w0 = min(w0, w);
		w1 = min(w1, w);
		change(1, 1, n, i + 1, w0 - 1, -1);
		change(1, 1, n, w1, w - 1, 1);
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Ray_yi (赞：5)

### 思路：

读完题后，看一眼 $n$ 的范围，就会发现暴力肯定过不了，我们只能想办法再进行优化。

容易发现，我们如果以当前数的下标为 $R$：
1. 它的相邻两个数都是可以一次擦去的，如果有和它相邻的数，我们简称对于这个数可以与相邻的数合并。
2. 如果有和它相等且下标比它小的数，我们设这个和它相等，且下标更小的数的位置为 $L$，那么 $R$ 有贡献的区间就是 $L$ 的后一个数到 $R$。

那么，我们如果知道了这两点，就只需要一层循环就可以搞定了。我们枚举 $R$，用一个数组来记当前 $i$ 的前一次出现的位置，先假设这一个区间的所有数都要单独擦一次，算出结果后，再减去有相邻可以合并的情况，也就是第一种情况，用一个变量来存储就可以了。

~~代码较短，全是干货。~~

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,now,a[300005],las[300005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		now+=i-las[a[i]];//假设每个数都单独擦一次 
		if(las[a[i]-1]>=las[a[i]]) now-=las[a[i]-1]-las[a[i]];
		if(las[a[i]+1]>=las[a[i]]) now-=las[a[i]+1]-las[a[i]];
		/*第11、12行判断相邻的数，并把可以合并的情况减去*/
		las[a[i]]=i;//记录i最晚出现的下标 
		ans+=now;//记录答案 
	}
	cout<<ans;
	return 0;
}//已AC
```

---

## 作者：luogu_starblue (赞：5)

提供一种 dp 的做法。

看到这道题就想到了[AT_abc371_e](https://www.luogu.com.cn/problem/AT_abc371_e)，考虑设计状态 $f_i$ 表示区间右端点为 $i$ 的那些区间对答案的贡献，即 $f_i=\displaystyle\sum_{l=1}^{i}f(l,i)$，那么答案就是 $\displaystyle\sum_{i=1}^{n}f_i$。

然后考虑如何转移，我们再记录一个 $lst_{a_i}$ 表示 $a_i$ 最后一次出现的位置。

首先考虑如果擦除当前数的时候只取一个数，那么 $f_i=f_{i-1}+i$，然后由于当前的 $a_i$ 只能与 $a_i+1$ 或 $a_i-1$ 进行匹配，若当前的 $a_i$ 还没有出现过，那么能与 $a_i$ 进行匹配的个数就是 $lst_{a_i+1}+lst_{a_i-1}$。

若当前 $a_i$ 已经出现过，那么对于左端点在 $lst_{a_i}$ 以及之前的区间，当前 $a_i$ 的出现并不会影响答案，那么 $f_i=f_{i-1}+i-lst_{a_i}$，若左端点在 $lst_{a_i}$ 之后，那么能与 $a_i$ 匹配的个数就是 $lst_{a_i+1}+lst_{a_i-1}-2\times lst_{a_i}$。当然前提是 $lst_{a_i-1}$ 和 $lst_{a_i+1}$ 大于 $lst_{a_i}$ 转移才合法。
 
具体见代码。
```cpp
for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(!lst[a[i]])
		{
			f[i]=f[i-1]+i-lst[a[i]-1]-lst[a[i]+1];	
		}
		else
		{
			f[i]=f[i-1]+i-lst[a[i]];
			if(lst[a[i]+1]>lst[a[i]])f[i]-=lst[a[i]+1]-lst[a[i]];
			if(lst[a[i]-1]>lst[a[i]])f[i]-=lst[a[i]-1]-lst[a[i]];
		}
		lst[a[i]]=i;
		ans+=f[i];
	}
```

发现如果初始将 $lst_{a_i}$ 全部设成 $0$，那么两种情况本质上是一种。

最后代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=3e5+9;
ll a[maxn],f[maxn],lst[maxn];
int main()
{
	int n;
	cin>>n;
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		f[i]=f[i-1]+i-lst[a[i]];
		if(lst[a[i]+1]>lst[a[i]])f[i]-=lst[a[i]+1]-lst[a[i]];
		if(lst[a[i]-1]>lst[a[i]])f[i]-=lst[a[i]-1]-lst[a[i]];
		lst[a[i]]=i;
		ans+=f[i];
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：__little__Cabbage__ (赞：2)

## Solution

可以看出 $f(L,R)$ 相当于把 $a_{[L,R]}$ 中的数丢到一个数轴上，求连续段个数。

这时候需要有一步转化，连续段个数就相当于满足 $x \in a_{[L,R]},x+1 \notin a_{[L,R]}$ 的 $x$ 个数，然后就能做了，从 $1$ 到 $n$ 这 $n$ 个数分别计个数即可。

计数部分考虑统计一个数 $x$ 可以「控制」的区间，即上一个 $x$（防止重算）或 $x+1$ 到下一个 $x+1$，乘法原理即可。

## Code

```cpp
int n,a[MAXN],pre[MAXN],nxt[MAXN],p[MAXN],last[MAXN];

signed main()
{
    read(n),_::r(a,n);

    rep(i,1,n)
    {
        p[i]=last[a[i]];
        pre[i]=last[a[i]+1];
        last[a[i]]=i;
    }

    rep(i,0,n+1) last[i]=n+1;
    rpe(i,n,1)
    {
        nxt[i]=last[a[i]+1];
        last[a[i]]=i;
    int ans=0;
    rep(i,1,n) ans+=(i-max(p[i],pre[i]))*(nxt[i]-i);
    write(ans,'\n');

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：2huk (赞：2)

显然 $f$ 就是把所有数放到数轴上后，极长连续段的个数。极长连续段个数可以转化成，有多少个数 $x$，使得 $x$ 出现过且 $x-1$ 未出现过。

考虑一个数 $a_i$ 对多少 $f(l, r)$ 产生过贡献，即有多少 $l \le i \le r$ 满足 $a_l \dots a_r$ 中出现过 $a_i$ 但没出现过 $a_i-1$。

令 $p_i$ 表示 $i$ 前第一个等于 $a_i-1$ 的位置，$q_i$ 表示 $i$ 后第一个等于 $a_i-1$ 的位置。那么 $l \in (p_i, i], r \in [i, q_i)$。乘法原理算一下即可。

还有一个问题。例如 $[2,2,3]$，有两个 $2$ 都会算上贡献。所以还要求 $w_i$ 表示 $i$ 前第一个等于 $a_i$ 的位置。那么 $l \in (\min(p_i,w_i), i]$。

```cpp
// Problem: F - Double Sum 3
// Contest: AtCoder - AtCoder Beginner Contest 390
// URL: https://atcoder.jp/contests/abc390/tasks/abc390_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 3e5 + 10;

int n, a[N];
int p[N];			// a[i] 上一次的出现位置
int pre[N], suf[N];		// a[i]-1 的上/下一次出现位置

signed main() {
	cin >> n;
	
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
	}
	
	map<int, int> pos;
	for (int i = 1; i <= n; ++ i ) {
		p[i] = pos[a[i]];
		pre[i] = pos[a[i] - 1];
		pos[a[i]] = i;
	}
	
	pos.clear();
	for (int i = n; i; -- i ) {
		suf[i] = !pos.count(a[i] - 1) ? n + 1 : pos[a[i] - 1];
		pos[a[i]] = i;
	}
	
	int res = 0;
	for (int i = 1; i <= n; ++ i ) {
		res += (i - max(p[i], pre[i])) * (suf[i] - i);
		// cout << (i - max(p[i], pre[i])) << ' ' << (suf[i] - i) << '\n';
	}
	
	cout << res;
	
	return 0;
}
```

---

## 作者：ZepX_D (赞：2)

根据题目描述，可以发现 $f(L,R)$ 其实就是 $A_L,A_{L+1}\dots A_R$ 中的数组成的极长值域连续段数。

我们考虑扫描右端点 $r$，同时维护每个左端点的 $f(l,r)$。

每次左端点右移，那么 $f(l,r)$ 会变成 $f(l,r+1)$，其实就是添加一个数 $A_{r+1}$，那么会造成什么影响呢？

假设 $A_{r+1}$ 之前未出现过，那么添加之后：
* 若 $A_{r+1}-1$ 和 $A_{r+1}+1$ 均未出现，那么极长值域连续段数加一。
* 若出现其一，$A_{r+1}$ 会被相邻的极长值域连续段吸收，那么极长值域连续段数不变。
* 若均出现，那么发生极长值域连续段的合并，极长值域连续段数减一。

那么我们开一个数组 $pre_i$ 代表数字 $i$ 上一次出现的位置，每次加入数字 $x=A_{r}$ 时，记 $a=\min(pre_{x-1},pre_{x+1}),b=\max(pre_{x-1},pre_{x+1})$。
* 对于 $[1,pre_{x}]$，没有任何影响。
* 对于 $[pre_x+1,a]$，会发生 $x-1$ 所在极长值域连续段和 $x+1$ 所在极长值域连续段的合并，使极长值域连续段数减一。
* 对于 $[a+1,b]$，$x$ 会并入$x-1$ 所在极长值域连续段或 $x+1$ 所在极长值域连续段，答案没有变化。
* 对于 $[b+1,r]$，$x$ 不会被吸收，极长值域连续段数加一。

做法已经呼之欲出了，从左向右扫描右端点的同时维护 $sum=\sum\limits_{l=1}^rf(l,r)$ ，同时用 $ans$ 进行累加。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;

inline LL read()
{
	LL x = 0,f = 1;char ch = getchar();
	while(!isdigit(ch)) (ch == '-') && (f = -1),ch = getchar();
	while(isdigit(ch)) x = x*10+ch-48,ch = getchar();
	return x*f;
}

const int N = 3e5+5;
int a[N],pre[N];

int main()
{
	int n = read();
	LL ans = 0,sum = 0;
	for (int i = 1;i <= n;i++)
	{
		a[i] = read();
		int x = max(pre[a[i]-1],pre[a[i]]),y = max(pre[a[i]+1],pre[a[i]]);
		if (x > y) swap(x,y);
		sum = sum+i-y-(x-pre[a[i]]),ans += sum;
		pre[a[i]] = i;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Eric998 (赞：2)

好题！放在 ```F``` 可能水了点。

我们记 $S_{l,r}=\{a_i|i\in[l,r]\}$。对下标进行扫描线，则将 $a_i$ 加入等价于将 $a_i$ 插入 $S_j(j\in[1,i])$。

我们记一个集合的答案 $G(S)$ 为将 $S$ 划分为最少整数区间的个数。考虑 $S$ 中插入一个数 $x$ 对 $G(S)$ 的影响。

- 若 $x\in S$ 则没有影响。
- 若 $x\not\in S$：我们考察连续段的个数。如果 $x-1\in S$，则 $x$ 向下联通了一个连续段。$x+1\in S$ 同理。因此 $G(S\cup x)=G(S)+1-[x-1\in S]-[x+1 \in S]$。

我们定义 $val_i=\displaystyle\sum_{j=1}^iF(i,j),las_{i,x}$ 为 $[1,i)$ 中最靠后的 $x$ 的下标。

则 $val_i=\displaystyle\sum_{j=las_{i,a_i}+1}^{i-1}(1-[x+1\in S_{j,i-1}]-[x-1\in S_{j,i-1}])+val_{i-1}+1$。

这一坨式子看起来很吓人。随便画画图，扫描线实时维护 $las$ 就过了。

```cpp
int ans = 0, cur = 0, n = read();
	for(int i = 1; i <= n; i++) {
		x = read();
		cur += max(0ll, i - max(las[x], max(las[x - 1], las[x + 1])));
		cur -= max(0ll, min(las[x - 1], las[x + 1]) - las[x]);
		ans += cur, las[x] = i;
	}
	cout << ans;

```

---

## 作者：Ybll_ (赞：1)

# 思路：
我们需要一个数组 $b$，存第 $i$ 个数 $a$ **上一次出现**的位置，每次我们研究的区间就是 $a$ 到 $a$ 上一次出现的位置。

首先，这个区间产生的贡献最多为 $i-b_a$。

接下来有两种使**贡献减少**的情况：

1. $a-1$ 在当前研究的区间内；
2. $a+1$ 在当前研究的区间内。

如果出现第一种情况，我们就要减去 $b_a$ 到 $a-1$ 这个区间的长度，即 $b_{a-1}-b_a$。

第二种情况同上，即 $b_{a+1}-b_a$。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define re register
using namespace std;
il int read()
{
	re int x=0,f=1;
	re char c;
	while(!isdigit(c=getchar()))
	{
		if(c=='-')f=-1;
	}
	while(isdigit(c))
	{
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	}
	return x*f;
}
il void write(re int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)write(x/10);
	putchar(x%10+48);
}//以上为快读快写 
int a,b[300006],ans,now,n=read();
signed main()
{
	for(re int i=1;i<=n;b[a]=i++,ans+=now)
	{
		cin>>a;
		now+=i-b[a]-(b[a-1]>=b[a]?b[a-1]-b[a]:0)-(b[a+1]>=b[a]?b[a+1]-b[a]:0);
	}
	write(ans);
	return 0;
}
```

---

## 作者：fzark (赞：1)

看了一圈题解里面好像没有我这个思路，这里提供一个 分讨 $+$ 容斥 $+$ 贡献 的思路，并且因为自己是第一次独立思考做出 $f$ 题，所以会讲的非常详细！

## 题意

设 $f(l,r)$ 为 $a_{[l,r]}$ 中连续段的个数，求：

$$∑_l^n ∑_{r=l}^n f(l,r)$$

## 思路

首先正难则反，我们可以考虑进行一个关键假设，即：**假设最坏情况，即每个 $f(l,r) = r - l + 1 $**。这样答案就是从 $l$ 到 $n$，长度为 $r$ 的等差数列求和。

并且我们需要观察到一个关键性质，即假设有任意集合，一个元素合并到连续段的行为是：**将 $a_i - 1$ 和 $a_i + 1$ 的集合并入自身**。

接下来我们考虑最坏情况的答案，容斥减去元素并入连续段所造成的贡献。首先我们对单个元素的策略进行一个分类讨论：

首先考虑迄今为止 $a_i$ 没有没有在之前的遍历中出现过时，显然有如下分类讨论：

- 当 $a_i - 1$ 在之前已经出现过，显然 $a_i$ 有贡献
- 当 $a_i + 1$ 在之前已经出现过，显然 $a_i$ 有贡献

贡献则为 $a_i - 1$ 或 $a_i + 1$ 最后一次出现的位置（因为题目的统计方式是经典的对每个长度的前缀进行统计，显然该元素会被遍历的次数为自身所处位置）。

现在考虑 $a_i$ 在之前已经出现过，有如下分类讨论（钦定 $a_j$ 为上一次出现的元素。且下面所讨论的位置都是最后一次出现的位置，稍后会有证明）：

- 因为 $a_i$ 已经出现过，所以贡献为 $a_j$ 的位置
- 如果 $a_i - 1$ 在之前已经出现过，并且 $a_j$ 处于 $a_i - 1$ 的位置之前，则显然当 $a_j$ 被遍历完之后，$a_i$ 能继续与 $a_i - 1$ 并入连续段。则贡献为 $a_i-1$ 的位置容斥掉 $a_j$ 的位置。
- 如果 $a_j + 1$ 在之前已经出现过，同理第二点。

并且对于连续段的贡献，我们每遍历一次，都需要减去已有贡献。即总贡献单调非降。下面将给出证明。

## 证明

现在来证明一下为什么要关注最后一次出现的位置，以及为什么每遍历一次，就要减去单调非降的总贡献。

首先为什么要关注最后一次出现的位置：考虑 $a_i$，当 $a_i - 1$ 在之前出现了两次，而我们关注了 $a_i - 1$ 第一次出现的位置，则显然贡献计算会漏掉 $a_i - 1$ 第一次出现的位置到 $a_i - 1$ 最后一次出现的位置这段区间的贡献。

最后讨论一下为什么每一次遍历，即使当前没有产生贡献，也要减去之前的贡献，并且贡献单调非降：很简单，回顾我们之前我们进行的关键假设。也就是说我们到达某一个位置，是一个等差数列的前缀和。等差数列本身即是单调非降。所以我们就算当前没有贡献产生，也有减去之前的贡献。这恰好也是总贡献单调非降的原因（继承之前的贡献）。

*证毕*。

## 代码

```python
n = int(input())
a = list(map(int, input().split()))
ans = 0

# 首先假设最坏情况下的答案
for i in range(1, n + 1):
    ans += ((i + 1) * i) // 2

hs = {}
x = 0

for i in range(n):
    # 进行分讨
    # 当 ai 在之前出现过时
    if a[i] in hs:
        # 贡献1
        x += hs[a[i]]
        # 贡献2
        if a[i] - 1 in hs and hs[a[i]] < hs[a[i] - 1]:
            x += hs[a[i] - 1] - hs[a[i]]
        # 贡献3
        if a[i] + 1 in hs and hs[a[i]] < hs[a[i] + 1]:
            x += hs[a[i] + 1] - hs[a[i]]
    # 当 ai 没有出现过时
    else:
        # 与 ai-1 造成贡献
        if a[i] - 1 in hs: x += hs[a[i] - 1]
        # 与 ai+1 造成贡献
        if a[i] + 1 in hs: x += hs[a[i] + 1]
    # 考虑容斥减掉
    ans -= x
    # 更新最后一次出现的位置
    hs[a[i]] = i + 1

print(ans)
```

## 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

---

## 作者：chenxi2009 (赞：1)

## 思路
$f(l,r)$ 是 $A_{l\cdots r}$ 排序后连续数字段的个数。我们让其中每一个段的最小数字做出贡献。因为可能有相同数字，所以钦定取在原序列位置中最左的一个。

思考一个数字在怎样的串里会做出贡献：串中没有比它小一的值，串中它的左边没有和它相等的数字。

前一个条件我们可以找到它左边和右边最近的比它小一的数字，串的左端点必然在左边那个数字右边，右端点在右边那个数字左边。\
第二个条件可以找到它左边离它最近的相等的数字，串的左端点在这个数字右边。

显然统计这样的串数很便捷，就是左端点可取的位置数乘以右端点可取的位置数。

找最近的数字开值域大小个 set 即可。

时间复杂度 $O(N\log N)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[400000],tmp;
long long ans;
set<int>s[400000];
int main(){
	scanf("%d",&n);
	for(int i = 0;i <= n;i ++) s[i].insert(0),s[i].insert(n + 1);//存个边界防爆
	for(int i = 1;i <= n;i ++){
		scanf("%d",&a[i]);
		s[a[i]].insert(i);//s_i 存数字 i 在序列中出现的位置
	}
	for(int i = 1;i <= n;i ++){
		auto it = s[a[i]].lower_bound(i);
		tmp = i - (*(-- it));//-- it 存储左边最近的相等数字
		it = s[a[i] - 1].lower_bound(i);
		tmp = min(tmp,i - (*(-- it)));//-- it 存储左边最近的小一的数字
		it = s[a[i] - 1].upper_bound(i);//右边最近的小一的数字
		ans += (long long)tmp * ((*it) - i);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

提供一种较为麻烦的做法。

显然地，$f(L, R)$ 为 $A_{L \ldots R}$ 去重后连续区间块数。那么我们记 $k$ 为子数组里出现的不同整数总数，$c$ 为子数组中相邻 $(x, x + 1)(x \in \mathbb N^+)$ 的数量，那么：

$$
f(L, R) = k - c.
$$

为什么这样是对的？因为我们发现，只有 $A_{i + 1} = A_i + 1$ 才能合并为一个段，那么 $f(L, R)$ 为断点数量加 $1$。而断点数量为相邻数对数量减去 $(x, x + 1)$ 的数对数量，即为 $(k - 1) - c$，再加上 $1$ 可得 $k - c$。

所以我们原式可以转变为：

$$
\sum_{1 \le L \le R \le N} k - \sum_{1 \le L \le R \le N} c
$$

第一个部分可以 $O(N)$ 求解，具体见[此题](https://www.luogu.com.cn/problem/AT_abc371_e)，求解式子为：

$$
\sum_{i = 1} ^ N [i - \text{last}_{1 \ldots i}(a_i)] \times (n - i + 1)
$$

接下来考虑求解第二部分。

我们不妨先设 $C(x)$ 为子数组里出现多少对 $(x, x + 1)$，那么原式转变为：

$$
\sum_{x = 1} ^ {N - 1} C(x)
$$

$C(x)$ 怎么求呢？很简单，设 $S_x$ 为「不含 
$x$ 的子数组数量」，$S_{x + 1}$ 为「不含 $x + 1$ 的子数组数量」，$S_{x, x + 1}$ 为「不含 $x$ 也不含 $x+1$ 的子数组数量」，那么根据最基本的容斥原理可得：

$$
C(x) = \frac{N(N+1)}{2} - S_x - S_{x + 1} + S_{x, x + 1} 
$$

- $S_x$ 和 $S_{x + 1}$：很简单。对于 $S_x$ 我们把所有出现 $x$ 的下标作为「分隔点」，这样在这些位置之间的空隙对应的一段长度之内选任何左右端都不会包含 $x$。对于 $S_{x + 1}$ 同理。

- $S_{x, x + 1}$：也同理，我们只需将出现 $x$ 和 $x + 1$ 的下标合并再使用上述做法即可求出。

这样，我们就可以再 $O(N)$ 时间内求出答案。

参考代码如下：

```cpp
#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 6;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &x : a) std::cin >> x;
    std::vector<std::vector<int>> pos(n + 2);
    for (int i = 1; i <= n; ++i) {
        pos[a[i - 1]].push_back(i);
    }
    std::vector<int> lst(n + 2, 0);
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (i - lst[a[i - 1]]) * (n - i + 1);
        lst[a[i - 1]] = i;
    }
    std::vector<int> sx(n + 2, 0);
    for (int x = 1; x <= n; ++x) {
        int s = 0, pre = 0;
        for (auto &p : pos[x]) {
            s += (p - pre - 1) * (p - pre) / 2;
            pre = p;
        }
        sx[x] = (n - pre) * (n - pre + 1) / 2 + s;
    }
    std::vector<int> sx2(n + 2, 0);
    for (int x = 1; x < n; ++x) {
        const std::vector<int> &rp1 = pos[x], &rp2 = pos[x + 1];
        std::vector<int> merged;
        merged.reserve(rp1.size() + rp2.size());
        int p1 = 0, p2 = 0;
        while (p1 < rp1.size() && p2 < rp2.size()) {
            if (rp1[p1] < rp2[p2])
                merged.push_back(rp1[p1++]);
            else
                merged.push_back(rp2[p2++]);
        }
        while (p1 < rp1.size()) merged.push_back(rp1[p1++]);
        while (p2 < rp2.size()) merged.push_back(rp2[p2++]);
        int s = 0, pre = 0;
        for (auto &p : merged) {
            s += (p - pre - 1) * (p - pre) / 2;
            pre = p;
        }
        sx2[x] = (n - pre) * (n - pre + 1) / 2 + s;
    }
    for (int x = 1; x < n; ++x) {
        sum -= (n + 1) * n / 2 - sx[x] - sx[x + 1] + sx2[x];
    }
    std::cout << sum << "\n";
}

int32_t main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0), std::cout.tie(0);

  int t;
  // std::cin >> t;
  t = 1;

  while (t--) {
    solve();
  }

  return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

这题是真妙，我之前是根本没见过这个 trick，也是看官方题解学到的。

最关键的思路就是：设 $g(i)$ 表示一共会用到的 $l=i$ 的操作的次数，然后答案就是 $\sum\limits_{i=1}^ng(i)$。

想到这一步接下来就容易了。一个区间中会用到一次 $l=i$ 的操作，当且仅当 $i$ 在区间中出现了，并且 $i-1$ 在区间中没出现。

所以统计的时候，先将所有数字出现的位置存进 vector，然后枚举每一个数值 $a_j=i$，二分查找两边最靠近的 $i-1$ 的位置在哪里，分别设为 $pl,pr$，这两个位置不能取到。然后左边最靠近的 $i$ 的位置也不能取到，设为 $p$，不然会造成统计重复。最后由乘法原理得到这个位置造成的贡献为 $(j-\max\{p,pl\})\times(pr-j)$。

```cpp
#include<iostream>
#include<vector>
#define int long long
using namespace std;
int n,a[300010],ans;
vector<int>v[300010];
signed main()
{
    cin>>n;
    for(int i=0;i<=n;i++)v[i].push_back(0);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        v[a[i]].push_back(i);
    }
    for(int i=0;i<=n;i++)v[i].push_back(n+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<v[i].size()-1;j++)
        {
            int pr=lower_bound(v[i-1].begin(),v[i-1].end(),v[i][j])-v[i-1].begin();
            int pl=pr-1;
            ans+=(v[i-1][pr]-v[i][j])*(v[i][j]-max(v[i][j-1],v[i-1][pl]));
        }
    cout<<ans<<endl;
    return 0;
}
```

这样时间复杂度为 $O(n\log n)$。可以将二分换成双指针来优化到 $O(n)$。

---

## 作者：_Weslie_ (赞：1)

upd 2025.1.27：修正一处笔误。

今天去成都省四川市了，回来一看题解差点无了。

## Solution AT_abc390_f

### Idea

这种求各个区间贡献和的题目，我们看到 $n\le 3\times 10^5$ 且 $a_i\le n$，便知道这个必须要按数来计算。

下面引出一个显然的结论：如果 $[l,r]$ 区间中，有一个可以被连续删除的段为 $[x,y]$，则一定有：在 $[l,r]$ 区间中没有 $x-1$。原因显然：假如有 $x-1$，那么被连续删除的段显然是 $[x-1,y]$ 更优。

我们先假设序列中除了当前枚举到的 $a_i$ 以外没有重复的 $a_i$。那么我们可以设 $pre_i$ 为 $i$ 前最后一个 $a_i-1$，$nxt_i$ 为 $i$ 后第一个 $a_i-1$。那么以 $a_i$ 为开头的可以被连续删除的段可以被 $(nxt_i-i)\times (i-pre_i)$ 个区间利用，答案加上这个数。

但是如果有重复的 $a_i$ 怎么办？也好说。我们发现重复的只需要计算一次即可，直接假定区间中第一个计算就可以。因此，我们计算 $pre_i$ 的时候，需要令 $pre_i$ 为 $i$ 前最后一个 $a_i-1$ 和 $i$ 前最后一个 $a_i$ 中位置更靠后的一个，这样我们就可以保证 $a_i$ 一定是所计算的区间中的第一个 $a_i$。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=300005;
int n,a[N],pre[N],nxt[N],lst[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pre[i]=max(lst[a[i]],lst[a[i]-1]);
		lst[a[i]]=i;
	}
	for(int i=0;i<=n+1;i++){
		lst[i]=n+1;
	}
	for(int i=n;i>=1;i--){
		nxt[i]=lst[a[i]-1];
		lst[a[i]]=i;
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans=ans+1ll*(i-pre[i])*(nxt[i]-i);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：lzyqwq (赞：1)

$f(L,R)$ 即为 $a_L,\dots,a_R$ 构成的极长值域连续段个数。考虑为每个极长值域连续段钦定代表元为其最小元素。那么考虑每个代表元的贡献即可。

对于一个代表元 $u$，枚举她在序列中出现的位置 $p$。由于子区间中 $u$ 可能出现多次。钦定贡献来自最左边的 $u$。记 $p$ 的前驱为 $x$，$p$ 左边最右边的 $u-1$ 的位置为 $y$，$p$ 右边的最左边的 $u-1$ 位置为 $z$。那么有 $p$ 位置贡献的区间满足 $x,y<L\le p$ 且 $p\le R<z$。乘法原理一下即可。

时空复杂度为 $\mathcal{O}(n)$。


```cpp
// LUOGU_RID: 200737451
#include <bits/stdc++.h>
#define int long long
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; c < 48 || c > 57; c = getchar()) if (c == 45) f = -1;
    for (; c >= 48 && c <= 57; c = getchar()) x = (x << 3) + (x << 1) + c - 48;
    x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
using namespace std; const int N = 300005;
int n, a[N], pre1[N], pre2[N], pos[N], nxt[N], ans;
signed main() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        pre1[i] = pos[a[i]];
        pre2[i] = pos[a[i] - 1];
        pos[a[i]] = i;
    }
    for (int i = 0; i <= n; ++i) pos[i] = n + 1;
    for (int i = n; i >= 1; --i) {
        nxt[i] = pos[a[i] - 1]; pos[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        ans += (i - max(pre1[i], pre2[i])) * (nxt[i] - i);
    }
    print(ans);
    return 0;
}
```

---

## 作者：GY程袁浩 (赞：1)

## 思路

仔细入手这题，我们其实可以发现题目中擦出的最小次数其实就是所有数组成的连段的数量。

举个例子，$1,2,7,9,3$ 这些数，最少需要我们擦除三次。

再来，对于这种 $\displaystyle \sum_{L=1}^N \sum_{R=L}^N f(L,R)$ 式子，我们一般采取挂点统计的方法。

具体的挂点统计，就是有顺序地枚举一个左端点或者一个右端点，然后在较快的时间复杂度内计算出当前点固定时，另一个点在所有位置时对答案的贡献。再把枚举的那个端点的所有贡献加起来就得到了答案。

我们可以使用继承贡献再修改等方法实现快速计算一点固定时的贡献。

在这题中我们的动机（Motivation）便是挂点统计。

考虑右端点固定时，我们怎么计算贡献。这时，我们便可以继承贡献再修改。

具体的，我们从大到小的枚举右端点，然后继承上一个右端点的贡献，然后考虑修改，也就是在原来所有序列的基础上再增加一个当前点，贡献的变化。首先如果这个点连接了两个连续段，那么对于这个序列，我们的贡献减少一。如果这个不能连在任何一个点上，并且之前也没出先过它，那么贡献加一。除了这两种情况，我们的贡献不变。

注意减少的情况不能算重了，我们需要比上一个当前数更后面的两个段，使得连上当前数之后可以连续。

比如 $4,3,5,4$ 当右端点在第二个 $4$ 的时候，我们只能视为有一个连接段，$3,5,4$ 是一个，但是 $4,3,5,4$ 不是，因为它在之前就已经考虑过了。

方便读者理解，给出一个例子：

我们的序列是 $4,3,5,4$。

- 右端点枚举到 $1$ 位置

  上一个贡献是零，前边没有出现过 $3,5,4$。单个数贡献加一，贡献为一，计入。

- 右端点枚举到 $2$ 位置

  上一个贡献是一，前面出现过 $4$，位置为 $1$，原先的所有序列在后面加上一个数 $3$ 后最少操作数依然不变，原先左端点位置大于 $1$ 的所有序列在后面加上一个数 $3$ 后最少操作数加一，单个数贡献一，加上上一个贡献，原来所有序列操作数不变，贡献为二，计入。

- 右端点枚举到 $3$ 位置

  上一个贡献是二，前面出现过 $4$，位置为 $1$，原先左端点位置小于等于 $1$ 的所有序列在后面加上一个数 $3$ 后最少操作数依然不变，原先左端点位置大于 $1$ 的所有序列在后面加上一个数 $3$ 后最少操作数加一。单个数贡献一，加上上一个贡献，加上原序列操作数的增加 $2-1=1$，贡献为四，计入。

- 右端点枚举到 $4$ 位置

  上一个贡献是三，前面出现过 $5,3,4$，位置分别为 $3,2,1$，原先左端点大于 $1$，小于等于 $\min(3,2)$ 所有序列有 $\min(3,2)-1$ 个，这些序列贡献减一，原先左端点位置大于 $\max(3,2)$ 的所有序列在后面加上一个数 $3$ 后最少操作数加一，并没有。加上单个数的贡献一。总贡献是 $4$。

答案是 $11$。

## Code

```cpp
// Problem: F - Double Sum 3
// Contest: AtCoder - AtCoder Beginner Contest 390
// URL: https://atcoder.jp/contests/abc390/tasks/abc390_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
map<int, int> pl;
const int N = 3e5 + 10;
int n, a[N], ans;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	upp(i, 1, n) cin >> a[i];
	int last = 0;
	upp(i, 1, n) {
		last += i - max(pl[a[i]], max(pl[a[i] - 1], pl[a[i] + 1]));
		if (pl[a[i] - 1] && pl[a[i] + 1] &&
			pl[a[i]] < min(pl[a[i] - 1], pl[a[i] + 1]))
			last -= min(pl[a[i] - 1], pl[a[i] + 1]) - pl[a[i]];
		ans += last;
		pl[a[i]] = max(pl[a[i]], i);
	}
	cout << ans << endl;
	return 0;
}
```

不懂可以私信问我。

---

## 作者：ZHR100102 (赞：1)

简单计数题。

# 思路

首先考虑单个区间的 $f$ 值如何计算，显然等于值域上连续段的个数。那么我们进一步观察值域上连续段的性质，发现**一个连续段的开头一定满足比开头小 $1$ 的数字不存在于区间中**的特点。

于是我们就可以考虑对每一个数字计算贡献了。同样，一个数字 $a$ 的贡献**只有当区间包含 $a$ 且不包含 $a-1$ 的时候才为 $1$，其他都是 $0$**。因为只有这样才能组成一个连续段的开头，而我们的贡献就是以开头来计数的。当然这里以连续段结尾来计数也没有问题。

因此只需要对每个数计算包含 $a$ 且不包含 $a-1$ 的区间个数即可。具体实现上，我们可以前后扫一遍，维护一个桶，**包含 $a$ 的区间我们钦定让最后面的那个 $a$ 计算贡献**，然后排除掉包含 $a-1$ 的区间即可。假设 $a$ 前面的最后一个 $a-1$ 在 $pre_{a-1}$ 处，后面的第一个 $a$ 在 $suf_a$ 处，后面的第一个 $a-1$ 在 $suf_{a-1}$ 处，则贡献即为 $(i-pre_{a-1})\times (\min(suf_a,suf_{a-1})-i)$。其他细节详见代码。

时间复杂度 $O(n)$。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
int n,a[300005],tot[300005],pre[300005];
ll ans=0;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    memset(tot,0,sizeof(tot));
    for(int i=1;i<=n;i++)
    {
        tot[a[i]]=i;
        pre[i]=tot[a[i]-1];
    }
    fill(tot,tot+n+1,n+1);
    for(int i=n;i>=1;i--)
    {
        int suf=min(tot[a[i]],tot[a[i]-1]);
        ans+=1ll*(i-pre[i])*(suf-i);
        tot[a[i]]=i;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Aurie (赞：0)

设 $dp_i$ 为考虑所有以 $i$ 为结尾的区间的答案，则最终答案为 $\sum\limits_{i=1}^{n}{dp_i}$。

观察如何转移出 $dp_i$，首先计算区间 $[i,i]$ 的答案为 $1$，然后考虑从 $dp_{i - 1}$ 转移出 $dp_i$。找到最后一个 $j$ 使得 $a_j=a_i$ 且 $j<i$，显然这些区间 $[k,i],(1\leq k\leq j)$ 已经有 $a_i$ 了，加上 $a_i$ 这个数后答案不变，在剩下的区间中找到即有 $a_i-1$ 又有 $a_i+1$ 的区间，这些区间加上 $a_i$ 后答案减一，只有 $a_i-1$ 或 $a_i+1$ 的区间加上 $a_i$ 后答案不变，都没的区间加上 $a_i$ 之后答案加一，只需要算出各种类型的区间各有多少个，对应给 $dp_{i-1}$ 加或减相应的贡献，即可得到 $dp_i$，可以使用一个桶维护每个数出现的最大下标，即可 $ O(1)$ 计算每个区间各有多少个。总复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10, INF = 0x3f3f3f3f;

int a[N], n, mp[N];
long long dp[N];

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    mp[a[1]] = 1;
    dp[1] = 1;
    for (int i = 2;i <= n; i++) {
        dp[i] = dp[i - 1] + 1;
        int low = -INF, up = -INF, now = mp[a[i]];
        if (mp[a[i] - 1]) low = mp[a[i] - 1];
        if (mp[a[i] + 1]) up = mp[a[i] + 1];
        dp[i] += i - max({up + 1, low + 1, now + 1});
        dp[i] -= max(min(up, low) - now, 0); // 下面四则分讨本质和上面两个转移式无异。
        // if(up != -INF && low != -INF){ // a[i] - 1, a[i] + 1 都有。
        //     dp[i] += i - max({up + 1, low + 1, now + 1});
        //     dp[i] -= max(min(up, low) - now, 0);
        // } else if (up == -INF && low == -INF) { // 都没有。
        //     dp[i] += i - now - 1;
        // } else if (up != -INF) { // 只有 a[i] + 1。
        //     dp[i] += i - max(up + 1, now + 1);
        // } else { // 只有 a[i] - 1。
        //     dp[i] += i - max(low + 1, now + 1);
        // }
        mp[a[i]] = max(mp[a[i]], i);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dp[i];
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：rqliushuangyu (赞：0)

### 题目大意

找每一个区间，有多少个“连通” 的。$f(l,r)$ 指 $l$ 到 $r$ 之间有多少个连通。所谓连通，指数与数之间是连续的（可以有重复），如：$1$ $5$ $4$ $1$ $4$ $5$ $1$，$f(1,7)=2$（$1$ $1$ $1$ 为连通，$5$ $4$ $5$ $4$ 一个连通）。

### 思路

我们可以遍历每一个值，用 $las_{a_i}$ 来记录上一次 $a_i$ 出现的下标，然后算上这个区间的“答案”（一个区间一个区间的算）。

首先先加设答案就是这个区间的所有值，然后再减。如果 $las_{a_{i-1}}$ 和 $las_{a_{i+1}}$ 在 $las_{a_{i}}$ 之后，
那么 $las_{a_{i}}$ 到 $las_{a_{i-1}}$ 和 $las_{a_{i}}$ 到 $las_{a_{i+1}}$ 是被 $las_{a_{i-1}}$ 和 $las_{a_{i+1}}$ 算过的，它们**没有贡献**，删掉这两个区间（**重复的也算**）。

**注意**：，每次的答案要**累加**，上次算的在这里也要做**贡献**。

### 代码

有详细解释

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a[300006],las[300006],ans;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];//输入
	long long now=0;//这是本点的“答案”
	for(int i=1;i<=n;i++)
	{
		now+=i-las[a[i]];//假设答案就是此点到上个点的区间(一定是+=，上次的答案有贡献，这次要算（包含）)
//重点
		if(las[a[i]-1]>=las[a[i]]) now-=las[a[i]-1]-las[a[i]];//如果las[a[i]-1]>=las[a[i]],就说明las[a[i]]到las[a[i]-1]这段区间已经被las[a[i]-1]算过了，没有贡献，舍去
		if(las[a[i]+1]>=las[a[i]]) now-=las[a[i]+1]-las[a[i]];//如果las[a[i]+1]>=las[a[i]],就说明las[a[i]]到las[a[i+1]]这段区间已经被las[a[i]+1]算过了，没有贡献，舍去
		las[a[i]]=i;//更新
		ans+=now;//加上这次的答案

	}
	cout<<ans;
	return 0;
}

```

---

## 作者：player_1_Z (赞：0)

### 先来理解题目

[atcoder 原题](https://atcoder.jp/contests/abc390/tasks/abc390_f)

### 思路

这题可以从暴力推过来，首先想到**枚举每个区间**并计算贡献，但是时间复杂度最低也是 $O(n^2)$，在这题会超时。

所以想到可以先**枚举每个元素**，计算它到这个数**上一次出现**的位置（如果是第一次出现就是到第一个元素的距离）的区间。那么贡献最多为**这个区间的元素个数**。

但是这样计算的答案**会多**。因为题目中提到，可以一次擦除**区间中连续的数**（如区间若为 `1 4 2 9 3` 则可以一次擦掉除 $9$ 外的所有数字）。

所以看这个区间中有没有这个数加一和减一，如果有，就减去这个数加一（建议）到当前这个数上次出现的位置的距离。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[300005],ln[300005],now,ans;
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
		now+=i-ln[a[i]];//计算当前区间的贡献 
		if(ln[a[i]-1]>=ln[a[i]]) now-=ln[a[i]-1]-ln[a[i]];
		//减去这个数-1的数到左端点的距离 
		if(ln[a[i]+1]>=ln[a[i]]) now-=ln[a[i]+1]-ln[a[i]];
		//减去这个数+1的数到左端点的距离
		ans+=now;
		ln[a[i]]=i;
		//a[i]上次出现的位置 (对于下一个a[i]，i就是上一次出现的位置，所以更新)
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
一起来看几个例子，可以先不看原题目，自己根据以下样例猜测。

~~主要是原题目意思太误导人了。~~
![](https://cdn.luogu.com.cn/upload/image_hosting/v512m822.png)

一共需要 $2$ 次。
![](https://cdn.luogu.com.cn/upload/image_hosting/u3le63xo.png)

一共需要 $2$ 次。

不难发现，题目意思是，需要几次才能擦除黑板上的数，连续的可以一次擦除，相同的数只用擦一次。

### 现在大家可以去看一下原题目最后要求什么。

[题目链接](https://www.luogu.com.cn/problem/AT_abc390_f)

# 思路
如果按照上方的求样例的思路来暴力枚举每一个区间显然是会超时的，我们考虑一位一位算贡献。

我们用 $last$ 数组来记录当前数字在数组中上一次出现的位置。

设当前数字为 $a_i$。

1. 假设加入 $a_i$ 对答案没有任何有利贡献，累加到 $now$ 中。
2. 若取消了 $a_i$ 减 $1$ 的独立性，是有利的贡献，把加多了的减掉。
3. 与 $2$ 相似，具体看代码。

# 代码
前面没理解的看代码注释哈。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std; 
int n,a[300005],last[300005],ans,now; 
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		now+=i-last[a[i]]; //假设没有任何贡献，为何这么算，因为last[a[i]]已经计算了它前面的，这段距离还没算 
		if(last[a[i]-1]>=last[a[i]])now-=last[a[i]-1]-last[a[i]];
		//是否取消了a[i]-1的独立性了，把多算的减掉 
		if(last[a[i]+1]>=last[a[i]])now-=last[a[i]+1]-last[a[i]];
		//是否取消了a[i]+1的独立性
		//如果不能理解，看这个 5 2 3 1 5 2 ，当前a[i]是后面那个2，自己模拟 
		last[a[i]]=i;	//更新 
		ans+=now;	//累加答案 
	}
	cout<<ans;
 	return 0;
}

```
### 谢谢！

---

## 作者：Inv_day_in_R (赞：0)

这道题直接算的话肯定是不行的，不妨计算每一个 $A_i$ 对总答案的贡献。显然，$f(L,R)$ 其实就是求 $A_L\dots A_R$ 中排序后连续整数段的个数。比如 $(1,2),(4,5,5),(8)$ 就含有 $3$ 个连续整数段。而这又可以转化为其中左端点的个数，如以上的 $1,4,8$ 三个左端点。观察左端点性质，很容易看出只要 $A_i-1$ 不在区间中，那么 $A_i$ 就是一个左端点。

这时就不难想到，对于每一个 $A_i$，找出不含有 $A_i-1$ 的个数就是答案。但其实这样是有漏洞的，因为 $A$ 数组可能有重复数字，这样的区间可能会被两个相同的数各算一次，所以对于 $A_i=A_j$，强行让前面的数 $A_i$ 往后算到第一个 $A_i-1$ 之前（**可能包含** $A_j$），而后面的数 $A_j$ 往前算到第一个 $A_j-1$ **或** $A_j$ 之后（**不包含** $A_i$）。

考虑具体实现，用 $pre_i$ 表示 $A_i$ 往前第一个 $A_i-1$ **或** $A_i$。用 $nxt_i$ 表示 $A_i$ 往后第一个 $A_i-1$（这里没有 $A_i$）。那么每一个 $A_i$ 左端点 $i-pre_i$ 种选法，右端点 $nxt_i-i$ 种选法，根据乘法原理，贡献为 $(i-pre_i)(nxt_i-i)$。

那么怎样算出 $pre_i$ 和 $nxt_i$ 呢？以复杂一点的 $pre_i$ 为例，从左往右扫一遍 $A$，用一个数组 $last_x$ 表示到现在为止扫到 $A_i$ 之前，最后一个值为 $x$ 的数在 $A_i$ 中的下标，那么此时 $pre_i=\max\{last_{A_i-1},last_{A_i}\}$，$nxt_i$ 从右往左扫一遍数组也能解决。

代码：
```cpp
void solve(){
	int n;
	cin>>n;
	vector<int>a(n);
	cin>>a;
	vector<int>lst(n+1,-1),pre(n),nxt(n);
	for(int i=0;i<n;i++){
		pre[i]=max(lst[a[i]],lst[a[i]-1]);
		lst[a[i]]=i;
	}
	lst=vector<int>(n+1,n);
	for(int i=n-1;i>=0;i--){
		nxt[i]=lst[a[i]-1];
		lst[a[i]]=i;
	}
	int ans=0;
	for(int i=0;i<n;i++)ans+=(i-pre[i])*(nxt[i]-i);
	cout<<ans;
}
```

---

## 作者：Wei_Han (赞：0)

能够发现 $f(L,R)$ 就是值域上的连续块个数，整个来数数不好做，我们考虑每一个位置的贡献。

在值域上，假设这个位置左右都没有数，那么他此时有 $1$ 的贡献，如果只有右边有数，那它就是这个连续块的开头，我们认定他此时有 $1$ 的贡献，假设这个数只有左边有数，那么他所在的这个连通块的价值已经被计算过了，左右都有数同理。所以，我们只需要计算一个数左边没有数的区间数量，就是这一个数的贡献了。

找这个区间数量就很简单了，令这个位置为 $i$，扩展的最左端就是上一个 $a_{i}-1$ 的位置，最右端就是 $a_i-1$ 出现的下一个位置，注意为了不重复统计，上一个 $a_i$ 的时候可能已经计算过同一个 $a_i-1$ 位置的贡献了，所以拓展的最左端应该是 $\max(d_{a_i},d_{a_i-1})$，$d_i$ 为 $i$ 上一次出现位置，最后把两边长度相乘就好了，每个数这样做一遍再加起来。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
//typedef int ll;
typedef long long ll;
//typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=1e6+5,M=2e4+5,mod=1e9+7;
ll n,a[N],sum,vis[N],pre[N],lst[N];
vector<ll> g[N];
signed main(){
	read(n);fo(1,i,n) read(a[i]),g[a[i]].pb(i);
	fo(1,i,n){
		// sum+=(i-max(vis[a[i]],vis[a[i]-1]))*(n-i+1);
		vis[a[i]]=i;
		pre[i]=vis[a[i]-1];
	}
	fo(0,i,n) vis[i]=n+1;
	Fo(n,i,1)
	{
		// wr(vis[2]),pr;
		vis[a[i]]=i;
		lst[i]=vis[a[i]-1];
		
	}
	fo(0,i,n) vis[i]=0;
	fo(1,i,n)
	{
		// wr(pre[i]),pp,wr(lst[i]),pr;
		sum+=(i-max(vis[a[i]],pre[i]))*(lst[i]-i);
		vis[a[i]]=i;
	}
	wr(sum),pr;//
    return 0;//
} 
``````

---

## 作者：SamHJD (赞：0)

首先可以观察到，$f(L,R)$ 等于 $[L,R]$ 中值域连续段的个数，因为每次肯定删一段极长的连续值域中的数。

让一段值域中「值最大且下标最大」的位置产生贡献，于是只需求每个位置可以作为几个询问中一段值域的该位置。那么 $i$ 可以产生贡献的区间即为 $i$ 前第一个等于 $a_i$ 或 $a_i+1$ 的位置 $pre_i$ 到 $i$ 后第一个等于 $a_i+1$ 的位置 $nxt_i$，$i$ 的贡献为 $(nxt_i-i)\times(i-pre_i)$。

$pre_i$ 和 $nxt_i$ 可以预处理每个数的出现位置后二分求出。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
    x=0;int f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
    x*=f;
}
template<typename T,typename ...Args>
inline void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=3e5+10;
int n,a[N],nxt[N],pre[N];
vector<int> pos[N];
signed main(){
    // freopen("data.in","r",stdin);
    read(n);
    rep(i,1,n) read(a[i]),pos[a[i]].push_back(i);
    rep(i,1,n){
        nxt[i]=n+1;pre[i]=0;

        auto res1=lower_bound(pos[a[i]+1].begin(),pos[a[i]+1].end(),i);
        if(res1!=pos[a[i]+1].end()) nxt[i]=min(nxt[i],pos[a[i]+1][res1-pos[a[i]+1].begin()]);

        auto res2=lower_bound(pos[a[i]+1].begin(),pos[a[i]+1].end(),i);
        if(res2!=pos[a[i]+1].begin()){
            res2--;
            pre[i]=max(pre[i],pos[a[i]+1][res2-pos[a[i]+1].begin()]);
        }
        
        auto res3=lower_bound(pos[a[i]].begin(),pos[a[i]].end(),i);
        if(res3!=pos[a[i]].begin()){
            res3--;
            pre[i]=max(pre[i],pos[a[i]][res3-pos[a[i]].begin()]);
        }
    }
    ll ans=0;
    rep(i,1,n) ans+=(i-pre[i])*(nxt[i]-i);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：zhangzheng2026 (赞：0)

很显然，当我们确定一对 $(L,R)$ 时，每次操作的 $(l,r)$ 必须满足 $l-1$ 与 $r+1$ 都没在黑板上出现。  
那么我们设一个数 $x$ 如果满足黑板上没有 $x+1$ 且左侧不含 $x$ 就能对答案产生 $1$ 的贡献。  
于是我们枚举每一个数对答案产生的贡献。我们可以开一个数组记录 $x$ 上次出现的位置，左右分别算一次，记为 $mapl$ 和 $mapr$。设 $l_i$ 和 $r_i$ 分别表示 $i$ 向左和向右扩展到的最远位置，那么有：
$$l_i=\max(mapl_{a_i},mapl_{a_{i+1}})+1$$
$$r_i=mapr_{a_{i+1}}-1$$
于是 $i$ 对答案的贡献就为 $(i-l_i+1)\times(r_i-i+1)$。  
这道题就做完了。  
代码：  

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,a[N],l[N],r[N],mp[N],ans;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) l[i]=max(mp[a[i]],mp[a[i]+1]),mp[a[i]]=i;
	for(int i=1;i<=n+1;i++) mp[i]=n+1;
	for(int i=n;i;i--) r[i]=mp[a[i]+1],mp[a[i]]=i;
	for(int i=1;i<=n;i++) ans+=(i-l[i])*(r[i]-i);
	cout<<ans;
	return 0;
}
```

---

## 作者：_wsq_ (赞：0)

我们考虑若已知 $f(l,r-1)$，求 $f(l,r)$。

显然：

- 若 $A_l$ 到 $A_{r-1}$ 中并未出现 $A_r-1$，$A_r$，$A_r+1$ 这三个数，则 $f(l,r-1)=f(l,r-1)+1$；
- 若 $A_l$ 到 $A_{r-1}$ 中出现了 $A_r-1$ 和 $A_r+1$，且并未出现 $A_r$，则 $f(l,r-1)=f(l,r-1)-1$；
- 若以上两种情况均不满足，则 $f(l,r-1)=f(l,r-1)$。

那么就可以开个数组记录当前所有数字是否出现，然后暴力枚举就是 $O(n^2)$ 的。

考虑进一步优化：我们可以一次性的根据 $\sum^{N}_{r=l}f(l,r)$ 推出 $\sum^{N}_{r=l-1}f(l-1,r)$ 的值，只需要知道 $A_r-1$，$A_r$，$A_r+1$ 第一次出现的位置，就能只要有多少个区间的答案会加 $1$，有多少个区间的答案会减 $1$ 了。

~~可能没太说明白~~，细节看代码。

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxn 300005
#define int long long
int n,a[maxn],cnt,ans,m[maxn];
signed main(){
    memset(m,0x3f,sizeof(m));
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=n;i;i--){
        cnt+=min(min(min(m[a[i]-1],m[a[i]+1])-1,m[a[i]]-1),n)-i;
        if(max(m[a[i]-1],m[a[i]+1])<m[a[i]]){
            cnt-=min(m[a[i]]-1,n)-min(max(m[a[i]-1],m[a[i]+1]),n)+1;
        }
        cnt++;
        ans+=cnt;
        m[a[i]]=i;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Yuexingfei_qwq (赞：0)

第一次深刻地见识到我为什么以前抢不到题解了。你们写得太快了吧……  
声明：**[本思路参照此题解](https://atcoder.jp/contests/abc390/editorial/12056)**。
## 思路  
对于每个 $l \le r$，将 $f(l,r)$ 表示为与 $f(l,r-1)$ 的差，则函数 $f(l,r)$ 可以表示为以下情况：  
- 当 $a_l,a_{l+1},...,a_{r-2},a_{r-1}$ 里包含 $a_{r}-1$ 和 $a_{r}+1$ 但不包含 $a_{r}$ 时，$\displaystyle f(l,r)=f(l,r-1)-1$。
- 当 $a_l,a_{l+1},...,a_{r-2},a_{r-1}$ 里不包含 $a_{r}-1,a_{r}$ 和 $a_{r}+1$ 时，$\displaystyle f(l,r)=f(l,r-1)+1$。
- 其他情况，$\displaystyle f(l,r)=f(l,r-1)$。


令 $\operatorname{g(r)}$ 为上面第一条的答案（$1 \le l < r$），$\operatorname{h(r)}$ 为上面第二条的答案（$1 \le l < r$），则对于 $\displaystyle \operatorname{t(r)}=\sum^{r}_{l=1} f(l,r)$，有：  
$$
\operatorname{t(r)}=\sum^{r-1}_{l=1} f(l,r)+f(r,r)=\operatorname{t(r-1)}-\operatorname{g(r)}+\operatorname{h(r)}+1
$$

接下来的问题转化为了如何求 $\operatorname{g(r)}$ 和 $\operatorname{h(r)}$。
再设 $\operatorname{q_r(x)}$ 为最大的使得 $l < r$ 且 $a_l = x$ 的 $l$（如果没有就设为 $0$），则有：  
$$
\operatorname{g(r)}=\max\{\min\{\operatorname{q_{r}(a_r-1)}, \operatorname{q_{r}(a_r+1)}\} - \operatorname{q_{r}(a_r)}, 0\}  
$$
$$
\operatorname{h(r)}=r-\max\{\operatorname{q_{r}(a_r-1)},\operatorname{q_{r}(a_r)},\operatorname{q_{r}(a_r+1)\}}-1
$$

由于 $q_r$ 不需要单独计算，只需要把 $\operatorname{g(r),h(r)}$ 和 $\operatorname{t(r)}$ 计算出来即可。
## AC CODE
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int n;
int a[310000];
int f[310000];
int ans = 0, tot = 0;

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> n;
	F(i, 1, n, 1) {
		cin >> a[i];
	}
	F(i, 1, n, 1) {
		int x = a[i];
		int j = std::max({f[x - 1], f[x], f[x + 1]});
		int d = std::max(std::min(f[x - 1], f[x + 1]) - f[x], 0LL);
		tot += (i - j - 1) - d + 1;
		ans += tot;
		f[x] = i;
	}
	cout << ans << el;
	r0;
}
```

[AC 记录](https://atcoder.jp/contests/abc390/submissions/62118173)

--- 
完结~~不~~散花。

---

