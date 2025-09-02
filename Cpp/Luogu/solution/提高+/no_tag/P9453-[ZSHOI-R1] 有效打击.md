# [ZSHOI-R1] 有效打击

## 题目背景

打腻了原版的 Boss，FyFive 决定做一个 Hollow Knight Mod Boss，名字叫“成功冠军”。

## 题目描述

和原本的失败冠军类似，成功冠军也有一个不能回魂的大盔甲。但是成功冠军更难的地方在于：它的盔甲需要以特定的打击方式才能造成伤害，可以造成伤害的打击序列被称作“有效打击”。

作为 Mod Boss 的设计者，FyFive 设置了一个可以造成有效打击的“标准序列”。为了降低操作难度，当打击顺序与标准序列“相似”时，即可造成有效打击。在这里“相似”的定义是，对于一个打击序列，将所有相同打击的连续段的长度同时进行放缩，可以得到另一个序列，则称这两个序列是“相似”的。

例如：
- ``112244`` 和 ``111222444`` 是相似的，
- ``111333`` 和 ``13`` 也是相似的，
- ``226`` 和 ``226`` 也是相似的，
- ``33889`` 和 ``33388899`` 则不是相似的。

由于 Boss 还处在调整标准序列的阶段，所以 FyFive 将 Boss 的血量调到了无穷大，但这样他就没办法通过比较初始血量和最终血量来计算他的打击序列在当前标准序列下能造成多少次有效打击，所以请万能的你来帮帮 FyFive 吧！

**注意**：对于可能出现的同时造成多次有效打击的情况，会造成多次有效打击，比如当打击序列为 ``11`` 时，若标准序列为 ``1``，则这个打击序列会造成 $3$ 次有效打击，因为第一个 ``1`` 和第二个 ``1`` 均与标准序列相似，同时 ``11`` 也与标准序列相似。若标准序列为 ``11``则也有 $3$ 次有效打击。若标准序列为 ``12``，则不会造成有效打击。同理，当打击序列为 ``6666``，标准序列为 ``66`` 时，则一共会造成 $10$ 次有效打击。

#### 形式化的，
>定义：若序列 $\Alpha$ 为 
> $$\underbrace{AA...A}_{a_1个}\underbrace{BB...B}_{a_2个}\underbrace{CC...C}_{a_3个}...$$
> 序列 $\Beta$ 为 
> $$\underbrace{AA...A}_{b_1个}\underbrace{BB...B}_{b_2个}\underbrace{CC...C}_{b_3个}...$$
> 其中 $A,B,C,a_1,a_2,a_3,...,b_1,b_2,b_3,...\in N_+$。
>
> 若有 $\frac{a_1}{b_1}=\frac{a_2}{b_2}=\frac{a_3}{b_3}=...=k\ , k>0$，则称 $\Alpha$ 与 $\Beta$ 互为相似序列。
>
> 特别的，长度为 $0$ 的序列不与任何序列成相似序列。
>
> 不难证明此定义下序列间的相似具有传递性。

求给定的序列 $A$ 中有多少个子串与给定序列 $B$ 互为相似序列。

## 说明/提示

数据范围：

| 数据点 | n | m | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| 1~2 | $\leq 20000$ | $\leq 20000$ | 无 |
| 3~4 | $\leq 5 \times 10^6$ | $\leq 5 \times 10^6$ | A |
| 5~6 | $\leq 5 \times 10^6$ | $\leq 5 \times 10^6$ | B |
| 7~10 | $\leq 5 \times 10^6$ | $\leq 5 \times 10^6$ | C |

对于 $100\%$ 的数据，保证有 $\forall\ i\in[1,n]$，$1\leq A_i \leq 7$；$\forall\ i\in[1,m]$，$1\leq B_i\leq 7$。

对于 $100\%$ 的数据，保证 $1\leq n,m\leq 5 \times 10^6$。

特殊性质 A：保证 $\forall\ i,j\in [1,m]，B_i=B_j$。

特殊性质 B：保证有且仅有一个 $k\in[1,m-1]$，使得 $\forall \ i,j\in[1,k]$，$B_i=B_j$；$\forall \ i,j\in[k+1,m]$，$B_i=B_j$。

特殊性质 C：保证第 $10$ 个点中 $n,m \leq 5\times 10^5$，且其他点中连续段仅有不超过 $100$ 种不同的长度。

## 样例 #1

### 输入

```
7 3
6 7 6 6 6 5 4
6 6 6```

### 输出

```
7```

## 样例 #2

### 输入

```
8 6
4 4 2 2 4 4 2 2
4 4 4 4 2 2```

### 输出

```
2```

## 样例 #3

### 输入

```
8 7
3 3 3 2 2 2 1 1
3 3 3 2 2 2 1```

### 输出

```
1```

# 题解

## 作者：就决定是你辣 (赞：7)

## P9453 [ZSHOI-R1] 有效打击 题解

### 题目分析

- 提供一种使用 kmp 实现的线性做法。

- 对于此类查询 $A$ 串中 $B$ 串出现了多少次的题目，可以想到使用 kmp 解决。

- 容易发现只有每一段颜色的数量和颜色的顺序是重要的，所以把原串缩写成 $a_1,a_2,a_3,\dots,b_1,b_2,b_3,\dots$ 的形式，其中每一个 $a_i$ 或 $b_i$ 记录每个极长同色连续段的颜色和数量。

- 题目要求有 $\frac{a_1}{b_1}=\frac{a_2}{b_2}=\frac{a_3}{b_3}=\dots=k\ , k>0$，移项发现两序列相似的充分必要条件是 $\sum_{i=2}^{n} \frac{a_i}{a_{i-1}} =\frac{b_i}{b_{i-1}}$ 且每一段 $a_i$ 和 $b_i$ 的颜色相同。按照这个条件判断 kmp 的两字符相等就可以了。

- 需要注意的是这里的相等需要特判 $A$ 和 $B$ 匹配时的起始段和 $B$ 的末尾段，这些段对前后两段之间的数量比并没有要求。

- 同样的，当 $B$ 串缩写后长度为 $1$ 或者 $2$ 时，可能会存在缩写后的段并不是匹配的最小单位的情况，需要分类讨论。当长度为 $1$ 时显然为 $A$ 串与 $b_1$ 颜色相同段的字串个数，长度为 $2$ 时同样找出颜色相同段，计算 $B$ 串最多出现几次即可。

- 子串个数是 $n^2$ 级别的，记得开 long long.
### 代码实现

```
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int maxn=5e6+100;
struct node {
	int x,v;
	double y;
}a[maxn],b[maxn];
double h=1e-6;
int n,m;
bool cal(node e,node f,int ai,int bi){//比较两段是否相等
	if((ai==1||bi==1||bi==m)&&e.x==f.x) return 1;
	else if(e.x==f.x&&abs(e.y-f.y)<=h) return 1; 
	else return 0;
}
int gcd(int a,int b){
	if(a>b)swap(a,b);
	if(!a||!b) return a+b;
	return gcd(b%a,a);
}
int kmp[maxn];
int j;
int ans;
signed main(){
	int nn=read(),mm=read();
	for(int i=1;i<=nn;i++) {
		int p=read();
		if(a[n].x!=p) a[++n].x=p,a[n].v=1;
		else a[n].v++;
	}
	for(int i=1;i<=mm;i++) {
		int p=read();
		if(b[m].x!=p) b[++m].x=p,b[m].v=1;
		else b[m].v++;
		
	}
	if(m==1){
		for(int i=1;i<=n;i++){
			if(a[i].x==b[m].x) ans+=a[i].v*(a[i].v+1)/2;
		}
		cout<<ans<<endl;
	}
	else if(m==2){
		int k=gcd(b[1].v,b[2].v);
		b[1].v=b[1].v/k,b[2].v=b[2].v/k;
		for(int i=1;i<=n;i++){
			if(a[i].x==b[2].x&&a[i-1].x==b[1].x)ans+=min(a[i].v/b[2].v,a[i-1].v/b[1].v);
		}
		cout<<ans<<endl; 
	}
	else {
		for(int i=2;i<=n;i++) a[i].y=double(a[i].v)/double(a[i-1].v);
		for(int i=2;i<=m;i++) b[i].y=double(b[i].v)/double(b[i-1].v);
		int la=n,lb=m;
			for(int i=2;i<=lb;i++){
			while(j&&!cal(b[i],b[j+1],i,j+1)){
				j=kmp[j];
			}
			if(cal(b[i],b[j+1],i,j+1)){
				j++;
				kmp[i]=j;
			}
		}
		j=0;
		for(int i=1;i<=la;i++){
			while(j&&!cal(a[i],b[j+1],i,j+1)){
				j=kmp[j];
			}
			if(cal(a[i],b[j+1],i,j+1)){
				j++;
			}
			if(j==lb){
				ans++;
				j=kmp[j];	
			}
		}
		cout<<ans<<endl;
	}
}
```


---

## 作者：Link_Cut_Y (赞：4)

抢个题解。

题意应该都知道了，就不放了。

首先分析一下部分分，排序按照本人思考的顺序。

以下将数字称为颜色，将数字段称为颜色段。默认颜色段连续且最长。

## Substack 2

最简单的部分分。由于 $b$ 两两相等，所以找到 $A$ 序列中的一个与 $b$ 同色的长度为 $k$ 的颜色段，对答案的贡献就是 $C_k^2$。

## Substack 3

在 sub2 上稍微加了点难度。$b$ 的颜色分为两段，设为 $x, y$。找到颜色不同的分界点，然后再 $A$ 序列中也找颜色不同的分界点。如果 $A$ 中某个分界点前后的颜色与 $x, y$ 分别相同，那么累计答案。

## Substack 1

考虑将 $A, B$ 转化为如下两个序列：第一个序列称为 **颜色序列**，维护的是 $A, B$ 中不同颜色段的颜色；第二个序列称为 **长度序列**，维护的是不同颜色段的长度。下文中 $C$ 代表颜色序列，$L$ 代表长度序列。

然后考虑匹配的情况是怎样的。首先考虑放缩倍数为 $1$ 的匹配。显然，就是在 $A$ 中找到一个子串 $s$，使得 $s$ 串的 $C, L$ 串与 $B$ 串的 $C, L$ 串完全相等。然后考虑放缩倍数为 $k$ 的情况。显然 $s$ 的 $C$ 与 $B$ 完全相等，而 $L$ 为 $B$ 的 $k$ 倍。

实现时需要注意一些细节：对于选取子串 $s$ 的首位不一定与 $B$ 匹配。例子如：

$$s = \{1, 1, 1, 2, 2, 3, 3, 3\}$$

$$B = \{1, 1, 2, 2, 3, 3\}$$

所以需要从 $B$ 的 $2 \sim |C| - 1$ 段进行匹配，再对首尾分类讨论。

暴力匹配的复杂度 $O(|C| ^ 2)$。

## Substack 4


显然，匹配过程可以利用哈希实现。对于 $A, B$ 的 $C, L$ 串分别建立哈希。然后发现子串的 $k$ 倍放缩可以体现为其哈希的 $k$ 倍放缩。所以匹配时直接判断其颜色哈希是否相等，长度哈希是否满足倍数关系即可。

由于我们实现时对于放缩比例需要化为最简，所以需要求最大公约数。因此时间复杂度 $O(n \log n)$。

下面是对于 substack 2, 3, 4 的代码实现：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

using ULL = unsigned int;
const int N = 5000010;
const ULL P = 1000000007;

int n, m;
int a[N], b[N];
vector<pair<int, int> > A, B;
ULL h1[N], h2[N], h3[N], h4[N], p1[N], p2[N];
long long ans;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i ++ )
		scanf("%d", &b[i]);
	for (int i = 1; i <= m; ) {
		int j = i;
		for (; j <= m and b[j] == b[i]; j ++ );
		B.push_back({b[i], j - i}); i = j;
	}
	for (int i = 1; i <= n; ) {
		int j = i;
		for (; j <= n and a[j] == a[i]; j ++ );
		A.push_back({a[i], j - i}); i = j;
	}
	
	if (B.size() == 1) {
		for (auto i : A) {
			if (i.first == B.front().first)
				ans += 1ll * i.second * (i.second + 1) >> 1;
		}
		cout << ans << endl;
		return 0;
	}
	if (B.size() == 2) {
		int p = B.front().first;
		int q = B.back().first;
		int x = B.front().second;
		int y = B.back().second;
		int d = __gcd(x, y);
		x /= d, y /= d;
		for (int i = 0; i < A.size() - 1; i ++ ) {
			if (A[i].first == p and A[i + 1].first == q) {
				if (1ll * A[i].second * y > 1ll * A[i + 1].second * x)
					ans += A[i + 1].second / y;
				else ans += A[i].second / x;
			}
		}
		cout << ans << endl; return 0;
	}
	else {
		p1[0] = p2[0] = 1;
		for (int i = 1; i <= A.size(); i ++ ) {
			h1[i] = h1[i - 1] * P + A[i - 1].first;
			h2[i] = h2[i - 1] * P + A[i - 1].second;
			p1[i] = p1[i - 1] * P;
		}
		for (int i = 1; i <= B.size(); i ++ ) {
			h3[i] = h3[i - 1] * P + B[i - 1].first;
			h4[i] = h4[i - 1] * P + B[i - 1].second;
			p2[i] = p2[i - 1] * P;
		}
		auto get = [](int l, int r, ULL p[], ULL h[]) -> ULL {
			return ULL(h[r] - h[l - 1] * p[r - l + 1]);
		};
		for (int l = 1; l <= A.size(); l ++ ) {
			int r = l + B.size() - 1;
			if (r > A.size()) break;
			ULL H1 = get(l, r, p1, h1);
			ULL H2 = get(1, B.size(), p2, h3);
			if (H1 != H2) continue;
			ULL H3 = get(l + 1, r - 1, p1, h2);
			ULL H4 = get(2, B.size() - 1, p2, h4);
			ULL p = A[l].second, q = B[1].second;
			ULL d = __gcd(p, q); p /= d, q /= d;
			if (ULL(H3 * q) != ULL(H4 * p)) continue;
			if (1ll * A[l - 1].second * q < 1ll * B.front().second * p) continue;
			if (1ll * A[r - 1].second * q < 1ll * B.back().second * p) continue;
			ans ++ ;
		}
		cout << ans << endl;
		return 0;
	}
	return 0;
}
/*
17 3
1 1 2 2 3 3 3 1 1 2 2 3 1 2 1 2 3
1 2 3
*/
```

## 关于此题的严格线性做法

很显然，复杂度瓶颈卡在求解最大公约数上。对于 $1 \sim 9$ 点，可以直接暴力处理出这些连续段的 $\gcd$。然而对于第十个点，~~需要线性 $\gcd$ 的高级魔法~~。由于赛时没有看到额外奖励，所以没拿到/kk/kk。

严格线性的代码没写，有写的神巨可以私我一下，~~我白嫖挂上~~。

---

## 作者：Lucky_Xiang (赞：3)

# 题目

[P9453](https://www.luogu.com.cn/problem/P9453)

# 思路

首先，将两个序列中相邻的相同数字合并为同一项，并记录每一项的**数字类型**与**数字个数**。再将 $B$ 序列中每一项的**数字个数**除以它们的 $\gcd$，得到 $B$ 序列的最简相似序列 $B'$。

### 性质 A

这种情况下，$B'$ 只有一项，且这一项的数字只有一个。因此，只需计算 $A$ 中**数字类型**与 $B'$ 中**数字类型**相同的项的子串个数即可。

### 性质 B

这种情况下，$B'$ 有且仅有两项。因此，只需枚举 $A$ 中相邻项**数字类型**与 $B'$ 的两项**数字类型**相同的部分，并计算 $B'$ 最大扩大倍数即可。

### 其他情况

这种情况下，$B'$ 不少于三项。如果 $B'$ 的**数字类型**能在 $A$ 中匹配，那么其扩大倍数一定是确定的，因为 $A$ 的某些项必须被完全包含。对于匹配**数字类型**，可以使用 KMP 或者 hash；而对于检查**数字个数**，可以使用 hash（因为扩大倍数是固定的）。

# 代码

```cpp
int N,M;
struct color
{
	int c,x;
};
color a[mn],b[mn];
int n,m;
int x;
LL res;
int str[mn],s[mn],nxt[mn];
ULL B[mn],H[mn];
ULL W;
void init()
{
	for(int i=2;i<m;i++)W=W*base+b[i].x;
	B[0]=1;
	for(int i=1;i<=n;i++)
	{
		B[i]=B[i-1]*base;
		H[i]=H[i-1]*base+a[i].x;
	}
}
ULL HASH(int L,int R)
{
	return H[R]-H[L-1]*B[R-L+1];
}
void check(int L,int R)
{
	if(a[L+1].x%b[2].x)return;
	int k=a[L+1].x/b[2].x;
	if(a[L].x<(LL)b[1].x*k || a[R].x<(LL)b[m].x*k)return;
	if(W*k!=HASH(L+1,R-1))return;
	res++;
}
int main()
{
	N=read(); M=read();
	for(int i=1;i<=N;i++)
	{
		x=read();
		if(a[n].c==x)a[n].x++;
		else a[++n]={x,1};
	}
	for(int i=1;i<=M;i++)
	{
		x=read();
		if(b[m].c==x)b[m].x++;
		else b[++m]={x,1};
	}
	x=0;
	for(int i=1;i<=m;i++)x=__gcd(x,b[i].x);
	for(int i=1;i<=m;i++)b[i].x/=x;
	if(m==1) //性质 A
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i].c==b[1].c)res+=(LL)a[i].x*(a[i].x+1)/2;
		}
		write(res,1);
	}
	else if(m==2) //性质 B
	{
		for(int i=1;i<n;i++)
		{
			if(a[i].c==b[1].c && a[i+1].c==b[2].c)
			{
				res+=min(a[i].x/b[1].x,a[i+1].x/b[2].x);
			}
		}
		write(res,1);
	}
	else //其他情况
	{
		init();
		for(int i=1;i<=n;i++)str[i]=a[i].c;
		for(int i=1;i<=m;i++)s[i]=b[i].c;
		for(int i=2,k=0;i<=m;i++)
		{
			while(k && s[i]!=s[k+1])k=nxt[k];
			if(s[i]==s[k+1])k++;
			nxt[i]=k;
		}
		for(int i=1,k=0;i<=n;i++) //KMP 匹配数字类型
		{
			while(k && str[i]!=s[k+1])k=nxt[k];
			if(str[i]==s[k+1])k++;
			if(k==m)
			{
				check(i-m+1,i); //hash 检查数字个数
				k=nxt[k];
			}
		}
		write(res,1);
	}
	return 0;
}
```

---

## 作者：ckain (赞：2)

首先我们将 $B$ 做成最小形式．

设 $B$ 被分为若干段相同的字符，将它们长度统一除以它们的 $\gcd$，得到串 $B_{min}$． 由于相似的传递性，有与 $B$ 相似等价于与 $B_{min}$ 相似．

与 $B_{min}$ 相似，必须满足其是 $B_{min}$ 放大整数倍的结果．

证明：

考虑反证．设 $X$ 是与 $B_{min}$ 相似的串，有

$$
X=\frac{p}{q}B_{min}\;(\gcd(p,q)=1)
$$

$q$ 是 $B_{min}$ 每一个连续相同字符段长度的因数．这与 $B_{min}$ 的定义矛盾．

---

若 $B_{min}$ 的长度是 $1$，求解答案是容易的．

若 $B_{min}$ 的长度不是 $1$，枚举 $A$ 中可能作为 $B_{min}$ 相似串的右端点．可以发现，当固定右端点时，$B_{min}$ 被放大的倍数是确定的．

考虑字符串哈希．我们先预处理出每种放大倍数下，$B$ 串的哈希值．然后对 $A$ 串做区间哈希即可完成对每个右端点 $O(1)$ 检查．

总时间复杂度 $O(n\log n)$．瓶颈在求 $\gcd$．

code：
```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=5e6+5, P=390831, Mod=1e9+7;

int n, m, a[N], b[N];

int pw[N], spw[N], hsha[N], hshb[N];

int len[N], c[N], tot, s;

int now[N];

void init(){
	pw[0]=spw[0]=1;
	for(int i=1; i<=n; i++) pw[i]=pw[i-1]*P%Mod, spw[i]=(spw[i-1]+pw[i])%Mod;
	for(int i=1; i<=n; i++) hsha[i]=(hsha[i-1]*P%Mod+a[i])%Mod;
	
	for(int i=1; i<=m; i++){
		int j=i;
		while(j<m && b[j+1]==b[i]) j++;
		len[++tot]=j-i+1;
		c[tot]=b[i];
		i=j;
	}
	int Gcd=len[1];
	for(int i=2; i<=tot; i++) Gcd=__gcd(Gcd, len[i]);
	for(int i=1; i<=tot; i++) len[i]/=Gcd, s+=len[i];
	
	for(int i=1; s*i<=n; i++){
		for(int j=1; j<=tot; j++){
			now[j]=(now[j-1]*pw[len[j]*i]%Mod+spw[len[j]*i-1]*c[j]%Mod)%Mod;
		}
		hshb[i]=now[tot];
	}
}

int que(int l, int r){
	return (hsha[r]-hsha[l-1]*pw[r-l+1]%Mod+Mod)%Mod;
}

void solve(){
	int ans=0;
	if(tot==1)
	for(int i=1, prelas=-1; i<=n; i++){
		if(a[i]!=c[tot]) prelas=-1;
		else if(prelas==-1) prelas=i;
		
		if(a[i]==c[tot]) ans+=(i-prelas+1);
	}
	else
	for(int i=1, prelas=-1; i<=n; i++){
		if(a[i]!=c[tot]) prelas=-1;
		else if(prelas==-1) prelas=i;
		
		if(a[i]==c[tot]){
			if((i-prelas+1)%len[tot]==0){
				int k=(i-prelas+1)/len[tot];
				if(que(i-k*s+1, i)==hshb[k]) ans++;
			}
		}
	}
	printf("%lld\n", ans);
}

signed main(){
	n=rd(), m=rd();
	for(int i=1; i<=n; i++) a[i]=rd();
	for(int i=1; i<=m; i++) b[i]=rd();
	
	init();
	
	solve();
	return 0;
}
```

---

## 作者：2020kanade (赞：2)

声明：本解法是乱搞出来的歪解，又劣又长跑得慢，还需要大力卡空间才能 AC，但不失为一种思路（大嘘）。

题目中“相似”的定义提示到了连续段，因此我们可以将连续段记录颜色和大小之后缩起来，文本串和模式串都是，下面称缩连续段的串为新串，即新文本串和新模式串。

我们将两个序列构成相似序列的情况称为二者“匹配”，同时定义“强匹配”为若干个整的连续段构成的序列之间的匹配，注意二者的区别，可以理解为前者针对任意序列，后者针对仅由完整连续段构成的序列（不一定是针对新串）。

现在，考虑匹配的构成条件：两个序列连续段数量相同，每个连续段颜色相同，每个连续段大小之比相同，最后一个条件根据小学数学知识等价于两个序列各连续段长度的比值数列完全相同（本解法重要突破口）。根据模式串缩起来之后的新串大小进行讨论：

新模式串大小为 $1$ 时，由于连续段只有一段，一旦颜色匹配上就一定能构成匹配。对于匹配数量的统计，可以发现只要序列长度比值不同一定是不同的匹配，因此可以固定文本串长度枚举模式串长度然后从左到右位移进行匹配，由于颜色一样每次一定能成功匹配，并且令文本串长度为 $s$，当模式串长度为 $k$ 时一定有 $s-k+1$ 种匹配，不难发现当模式串长度由 $1$ 到 $k$ 变化时匹配数量正是由 $k$ 到 $1$ 变化，因此，（针对原题背景下）发生颜色匹配时可以用等差数列求和公式 $O(1)$ 算出贡献。

新模式串大小为 $2$ 时，颜色匹配成为匹配构成的条件之一，此时直接比较两个点的颜色即可。当颜色匹配时，我们注意：此时能够构成匹配的情况不一定是强匹配，因为新文本串的一个子串可以取一个连续段的后缀与它后面的连续段的一个前缀来构成可匹配的序列，因此用 $\gcd$ 等方法求出新模式串两个连续段长度的最简分数比，也就是对二者进行约分，如果新文本串对应位置的连续段大小均大于约分后的新模式串连续段长度，此时可构成合法匹配，分别设新模式串前、后连续段大小在约分后为 $a,b$，新文本串对应子串的前、后位置的连续段大小分别为 $c,d$，则此时匹配数量为 $\min \{ \lfloor \frac{c}{a} \rfloor ,\lfloor \frac{d}{b} \rfloor\}$。

当新模式串大小 $\ge 3$ 时，由于完整连续段的存在，在新串意义下发生匹配时，匹配数量一定只有一种，并且去掉第一个与最后一个连续段后剩下的部分一定是强匹配的。由于强匹配的段连续段大小比值确定，可以在连续段中任意找到一个连续段来计算整个强匹配序列任意连续段与对应新文本串子串对应位置连续段大小的比值，而对于剩下两个连续段可以直接在常数时间内特判，这等价于新模式串大小为 $2$ 时判断是否存在匹配扩展到 $3$ 组的情况。

接下来，我们要解决的问题有：判断两个新串的颜色序列是否相等以及判断两个序列是否强匹配，即：判断两个序列是否完全一致与判断一个序列是否可以通过另一个序列所有数乘上一个数得到。

对于前者，直接把序列看成字符串进行哈希即可；对于后者，在满足条件时，对两序列作商分数列（即后一项除以前一项，注意这一数列元素比原数列少一个），二者的商分数列一定相同，证明很简单，注意商分数列的元素都可以看作分数，如果分子分母有相同的因子会约掉。

考虑到商分数列的元素都是有理数（不一定是整数），我们找一个大质数，如 $998244353$，在它的模意义下算出商分数列之后哈希，注意此时 $seed$ 要找一个更大的质数，比如 $10^9 +7$ 或 $10^9 +9$。注意，模式串只需要存哈希数值，开数组会爆空间。

因此，此时找匹配就变成了：通过哈希确定对应位置是否颜色匹配以及掐头去尾之后是否强匹配，然后特判。

具体的语言可能有点抽象，理解不了可以看 code 的实现。

令 $n,m$ 同阶，时间复杂度 $\Theta(n \log p),p=998244353$，瓶颈在逆元和约分时的 $\gcd$。

这里的实现用的是自然溢出，被叉了不要紧，大质数多得是。

[AC Code.](https://www.luogu.com.cn/paste/x5ktjekn)

顺便一问......题里给的特殊性质 C 有什么用呢，反正这里的做法就算没有特殊性质也能硬冲过去的。

---

## 作者：weizhiyonghu (赞：0)

# C:

## Solution:

​		很显然，这题要分类讨论。分类依据为**不同子段个数**，即标准序列 $B$ 一共被分成了多少个不交的连续段，每个段内只有同种值。记段数为 $t$。

### $t = 1$ 

​		此时不难发现，$A$ 中任何一个所有元素均为 $B_0$ 的字串都满足条件。那么根据排列组合基本知识，假设 $A$ 中一共有 $k$ 个这样的段，第 $i$ 段的长度为 $l_i$，那么答案应为 $\sum_{i=1}^k\frac{l_i(l_i+1)}{2}$。

### $t=2$

​		此时不难发现，若将 $A$ 中满足的串之内元素去重，与去重后的 $B$ 串应完全相等。同时，去重之前的两种元素个数之比也应与 $B$ 中元素之比相同。

​		那么可以设置 $v$ 数组和 $c$ 数组，$v_i $ 记录 $A$ 中第 $i$ 个连通块的元素值，$c_i$ 记录 $A$ 中第 $i$ 个连通块的长度。对于 $B$ 设置 $v'$ 和 $c'$，原理相同。那么若有 $v_i = v'_1,v_{i+1}=v'_2$ 并且 $c_i = c'_1,c_{i+1}=c'_2$，并且 $c_i \ge 2$，那么第 $i$ 个联通块的部分后缀和第 $i + 1$ 个连通块的部分前缀就满足条件。设 $\gcd(c'_1,c'_2) = k$，那么这两个连通块所产生的答案应为 $\min(\frac{c_1}{k\times c'_1},\frac{c_2}{k \times c'_2})$。总时间复杂度为 $\mathcal{O}(n)$。(一开始先把 $c'_1,c'_2$ 处理好再跑循环)

### $t \gt 2$

​		此时不难发现，我们不用再考虑单个位置产生多个答案的情况，因为子串的连续性质，所以中间段的长度必然一一对应。那么可以使用 kmp 算法找到每一个符合条件的地方，但是因为字串长度的不同，所以在判断条件上需要进行修改。

​		首先，我们知道 $\frac{a}{b} = \frac{c}{d}$ 在 $b,d \ne 0$ 时可以等效为 $ad = bc$。那么这里显然可以这么使用，以解决整除问题。

​		其次，对于失配与否的情况，只需要看当前 $A$ 串字串 $i$ 的长度 $c_i$，$A$ 串前一个字串的长度 $c_{i-1}$ 之比是否与 $B$ 串长度 $c'_{i},c'_{i-1}$ 相等即可。

​		最后，对于头尾两部分，我们发现只要这两个字串的长度大于等于同比例下 $B$ 串首尾长度，$B$ 串就被包含在内。所以判别式的符号要换为 $\ge$，即 $j = 0$ 时 $c_i \times c'_{j+2} \ge c_{i+1} \times c'_{j + 1},j = m - 1$ 时 $c_{i + 1} \times c'_{j} \ge c_{i}\times c'_{j + 1}$。 

综上，不难发现总时间复杂度为 $\mathcal{O}(n)$ 大常数，可以通过。

```cpp
#include <bits/stdc++.h>
#define v first
#define c second
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define rep(t,l,r) for(int t = l;t <= r;t++)
#define per(t,l,r) for(int t = r;t >= l;t--)

using namespace std;
typedef pair<int,int> pii;
const int N = 5e6 + 10;
int n,m,a[N],b[N];
pii bka[N],bkb[N];// block,first=v=value,second=c=cnt
int idxa,idxb; // index of blocks
int nxt[N];

inline bool check1(int i,int j)
{return bkb[i].v == bkb[j].v;}

inline bool check2(int i,int j)
{
	j++;
	if(bka[i].v != bkb[j].v) return false;
	int v1 = bka[i - 1].c;
	int v2 = bka[i].c;
	int c1 = bkb[j - 1].c;
	int c2 = bkb[j].c;
	return v1 * c2 == v2 * c1;
}

inline bool checkL(int i,int j)
{
	j++;
	int v1 = bka[i].c;
	int v2 = bka[i + 1].c;
	int c1 = bkb[j].c;
	int c2 = bkb[j + 1].c;
	return v1 * c2 >= v2 * c1;
}

inline bool checkR(int i,int j)
{
	int v1 = bka[i + 1].c;
	int v2 = bka[i].c;
	int c1 = bkb[j + 1].c;
	int c2 = bkb[j].c;
	return v1 * c2 >= v2 * c1;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	rep(i,1,n) cin >> a[i];
	rep(i,1,m) cin >> b[i];
	rep(i,1,n)
		if(bka[idxa].v == a[i]) bka[idxa].c++;
		else bka[++idxa] = {a[i],1};
	rep(i,1,m)
		if(bkb[idxb].v == b[i]) bkb[idxb].c++;
		else bkb[++idxb] = {b[i],1};
	if(idxb == 1)
	{
		int ans = 0;
		rep(i,1,idxa)
			if(bka[i].v == bkb[1].v)
			{
				int c = bka[i].c;
				ans += ((c + 1) * c) >> 1;
			}
		cout << ans << endl;
		return 0;
	}
	else if(idxb == 2)
	{
		int ans = 0;
        int tb1 = bkb[1].c;
		int tb2 = bkb[2].c;
		int g = __gcd(tb1,tb2);
		if(g > 1) tb1 /= g,tb2 /= g;
		rep(i,1,idxa - 1)
			if(bka[i].v == bkb[1].v)
				if(bkb[2].v == bka[i + 1].v)
				{
					int vi = bka[i].c;
					int vii = bka[i + 1].c;
					ans += min(vi / tb1,vii / tb2);
				}
		cout << ans << endl;
	}
	else if(idxb >= 3) // useless words...
	{
		int ans = 0;
		for(int i = 2,j = 0;i <= idxb;i++) // kmp-get_next
		{
			while(j && !check1(i,j + 1)) j = nxt[j];
			if(check1(i,j + 1)) j++;
			nxt[i] = j;
		}
		
		for(int i = 1,j = 0;i <= idxa;i++) // kmp-find
		{
			while(j && !check2(i,j)) j = nxt[j];
			if(j == 0 && checkL(i,j)) j++;
			if(j != 0 && check2(i,j)) j++;
			if(j == idxb - 1)
			{
				if(checkR(i,j)) ans++;
				j = nxt[j];
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

