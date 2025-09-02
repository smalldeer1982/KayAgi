# [ABC302D] Impartial Gift

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc302/tasks/abc302_d

高橋君は青木君とすぬけ君に **$ 1 $ つずつ**贈り物を送ることにしました。  
 青木君への贈り物の候補は $ N $ 個あり、 それぞれの価値は $ A_1,\ A_2,\ \ldots,A_N $ です。  
 すぬけ君への贈り物の候補は $ M $ 個あり、 それぞれの価値は $ B_1,\ B_2,\ \ldots,B_M $ です。

高橋君は $ 2 $ 人への贈り物の価値の差が $ D $ 以下になるようにしたいと考えています。

条件をみたすように贈り物を選ぶことが可能か判定し、可能な場合はそのような選び方における贈り物の価値の和の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N,M\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\leq\ 10^{18} $
- $ 0\leq\ D\ \leq\ 10^{18} $
- 入力はすべて整数
 
### Sample Explanation 1

高橋君は贈り物の価値の差を $ 2 $ 以下にする必要があります。 青木君に価値 $ 3 $, すぬけ君に価値 $ 5 $ の贈り物を渡すと条件をみたし、価値の和としてはこのときが最大となります。 よって、$ 3+5=8 $ を出力します。

### Sample Explanation 2

条件をみたすように贈り物を選ぶことは不可能です。 また、同一人物に対して、同じ価値の贈り物が複数存在することもあります。

### Sample Explanation 3

答えが $ 32 $ bit整数型の範囲に収まらないことがあることに注意してください。

## 样例 #1

### 输入

```
2 3 2
3 10
2 5 15```

### 输出

```
8```

## 样例 #2

### 输入

```
3 3 0
1 3 3
6 2 7```

### 输出

```
-1```

## 样例 #3

### 输入

```
1 1 1000000000000000000
1000000000000000000
1000000000000000000```

### 输出

```
2000000000000000000```

## 样例 #4

### 输入

```
8 6 1
2 5 6 5 2 1 7 9
7 2 5 5 2 4```

### 输出

```
14```

# 题解

## 作者：FreedomKing (赞：3)

### 题目大意

给出两个分别长 $n$ 和 $m$ 的序列 $A$ 和 $B$ 以及一个数 $D$，要从两个序列中分别选出两个数使得 $\left|A_i-B_{j}\right|\le D$，问这两个数和的最大值。

------------

### 思路

一眼数据范围 $N\le 2\times 10^5$，$O(nm)$ 的暴力明显是过不了的，考虑使用二分优化查找 $B$ 中的取值，判断 $B_i$ 是否合法，取 $\max$。

二分这里给出使用 STL 中的 `lower_bound` 的解法：

假设 $B_{ans}$ 是与 $A_i$ 合法的最优解。

- 首先要知道 $\left|A_i-B_{ans}\right|\le D$ 是必然的。

- 且有 $B_i$ 越大 $A_i+B_i$ 的值就越大，所以更大的 $B_i$ 必然是更接近最优解的。

此时便可以试图找到第一个 $>A_i+D$ 的 $B_i$ 的前一个元素 $B_{i-1}$，它既满足题目条件也是能取到的最大值，所以这个 $B_{i-1}$ 必然就是合法且最优的解 $B_{ans}$。不过由于 `lower_bound` 寻找的是第一个大于等于的值，需要注意把 $>A_i+D$ 改成 $\ge A_i+D+1$。

综上，核心代码为 `lower_bound(b+1,b+m+1,a[i]+D+1)-b-1`。

------------

### AC Code

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+5;
int a[N],b[N],n,m,t,k;
signed main(){
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(b+1,b+m+1);
	int maxn=-1;
	for(int i=1;i<=n;i++){
		int id=lower_bound(b+1,b+m+1,a[i]+t+1)-b-1;
		if(abs(b[id]-a[i])<=t) maxn=max(maxn,b[id]+a[i]);
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：_7Mr (赞：3)

# 题意
有 $2$ 个序列，现在要从这两个序列中，各选出 $1$ 个数字，使得这两个数字的差值 $\le d$ 并且这 $2$ 个数字的和要最大。
# 思路
首先我们先给它排个序，使它变为有序的，接下来我们就可以用两种做法来做。
> 一种是二分，这显然是有单调性的。

> 一种是用栈的思想，建立双指针来做。
## 二分
我们将第二个序列枚举一遍，在每次枚举中二分一下第一个序列，看看能不能有符合的，然后更新答案。

现在讲一下，具体的二分过程。

如果当前二分到的值与我枚举到的值的差值 $\le d$ 那么将左指针移动到中间值 $+1$ 并且更新答案。如果不是，而且二分到的值大于我枚举到的值那么将右指针移动到中间值 $-1$，都不是将左指针移动到中间值 $+1$。最后更新总的答案。

说的有点绕，认真理解再看代码。
## 栈
排个序后，从大到小枚举，去找相差为 $d$ 的两个数据输出,怎么找呢？将第一个序列最大那个值的下标设为 $top1$，第二个序列同理，设为 $top2$。如果当前 $top1$ 和 $top2$ 所对应的值 $\le d$ 那么直接输出，否则就将比较大的那个数出栈，如果 $top1$ 或者 $top2$ 有一个为 $0$ 了，说明没有找到答案，那么直接输出 $-1$。
# ACcode
**二分的做法。**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m;
long long d,anss=-1;
long long a[maxn],b[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+1+n);//排序 
	sort(b+1,b+1+m);
	for(int i=1; i<=m; i++) {
		int l=1,r=n;
		long long ans=-1;
		while(l<=r) {//开始二分 
			int mid=(l+r)/2;
			//分三种情况 
			if(abs(a[mid]-b[i])<=d) {
				ans=max(ans,a[mid]);//更新答案 
				l=mid+1;
			}
			else if(a[mid]>b[i]) r=mid-1;
			else l=mid+1;
		}
		if(ans!=-1) anss=max(anss,ans+b[i]);//更新答案 
	}
	cout<<anss;
	return 0;
}
```
**栈的做法。**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m;
long long d;
long long a[maxn],b[maxn];
int main(){
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+1+n);//排序 
	sort(b+1,b+1+m);
	int top1=n,top2=m;
    while(true){
    	//四种情况 
    	if(abs(a[top1]-b[top2])<=d){
    		cout<<a[top1]+b[top2];
    		return 0;
		}
		else{
			//哪个大哪个出栈 
			if(a[top1]>b[top2]) top1--;
			else top2--;
		}
		if(top1<=0 || top2<=0){
			cout<<-1;//都不行，输出-1 
			return 0;
		}
	}
	cout<<-1;
	return 0;
}

```
拒绝抄袭，从我做起。

---

## 作者：ran_qwq (赞：2)

因为 $N,M\leq2\times10^5$，所以不能枚举两个礼物，如果价值差不超过 $D$ 计算最大值。

可以先把 $A$ 从小到大排序。接着枚举 $B$ 数组中的礼物 $B_i$，在 $A$ 数组中取的那个礼物的价值就必须在 $[B_i-D,B_i+D]$ 的范围内。因为要求最大值，所以要尽量接近 $B_i+D$。可以用**二分答案**找到第一个大于 $B_i+D$ 的数的位置。然后分类讨论：

1. 第一个大于 $B_i+D$ 的礼物位置是 $1$，则 $A$ 中没有小于等于 $B_i+D$ 的礼物。换句话说，如果取了 $B_i$，在 $A$ 中无法再取一个礼物和它配对。

2. 第一个大于 $B_i+D$ 的礼物位置不是 $1$，则 $A$ 中有小于等于 $B_i+D$ 的礼物。

- 如果最大的小于等于 $B_i+D$ 的礼物小于 $B_i-D$，则 $A$ 中的所有礼物价值要么小于 $B_i-D$，要么大于 $B_i+D$，无法在取一个和它配对。

- 否则就取最大的小于等于 $B_i+D$ 的礼物。

注意如果不能满足题意地取礼物，输出 $-1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,m,k,ans=-1,a[N];
void solve()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read();sort(a+1,a+1+n);
	while(m--)
	{
		int x=read(),pos=upper_bound(a+1,a+1+n,x+k)-a-1;
		if(abs(a[pos]-x)<=k) ans=max(ans,x+a[pos]);
	}
	write(ans,"");
}
signed main()
{
	int T=1;
	while(T--) solve();
}

```

---

## 作者：happybob (赞：1)

容易发现我们可以先对两个序列排序。

依次枚举 $a_i$，那么另一个数应该 $x$ 应该满足 $x \in [a_i - D, a_i + D]$。因此我们可以二分在这个区间的最大值 $p$，那么这个贡献就是 $a_i+p$，最后将所有 $a_i+p$ 取最大值即可。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
using namespace std;

#define ll long long

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t;
long long a[N], b[N], k;
long long ans = -1;

#define mabs(x) ((x) < 0 ? (-(x)) : (x))

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	scanf("%d%d%lld", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%lld", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	for (int i = 1; i <= n; i++)
	{
		if (mabs(b[m] - a[i]) <= k)
		{
			ans = max(ans, b[m] + a[i]);
			continue;
		}
		int x = upper_bound(b + 1, b + m + 1, a[i] + k) - b;
		for (int j = max(1, x - 10); j <= min(m, x + 10); j++)
		{
			if (mabs(b[j] - a[i]) <= k)
			{
				ans = max(ans, b[j] + a[i]);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：2huk (赞：1)

## 题目描述

有两个序列 $a$ 和 $b$，$a$ 长度为 $n$，$b$ 长度为 $m$，需要求出 $\max_{\left| a_i - b_j\right| \le d} a_i + b_j$ 的值。若不存在满足条件的，输出 $-1$。

$1 \le n, m \le 2 \times 10^5$

## 分析

显然我们可以暴力枚举两个元素分别是什么，但是这样的时间复杂度为 $\Theta(nm)$，并不能通过本题。

考虑二分查找。由于二分需要具有单调性，所以计算前输入后需要对两个数组排序。

接下来枚举每一个 $a$ 中的元素，然后找一个满足条件的 $b$ 中的元素，更新最大值。

这里的满足条件是什么呢？小于等于 $a_i + d$ 的元素中最大的。 

这样的时间复杂度是 $\Theta(n \log m)$ 的，可以通过本题。

那么如何找到**小于等于** $a_i + d$ 的最大的 $b_j$ 呢？

考虑这样解决，首先找到第一个**大于** $a_i + d$  的 $b_j$，这里我们可以使用 `STL` 里的 `upper_bound`。然后找到这个位置的上一个位置，那么这个位置就一定是最大的小于等于 $a_i + d$ 的 $b_j$ 了。此时再更新答案即可。

[Code](https://atcoder.jp/contests/abc302/submissions/41581445)

---

## 作者：chlchl (赞：1)

upd on 2023.5.23：经评论区指出，翻译有误（数组长度并非都是 $n$），现已修正。

## 题意
给定两个长度分别为 $n,m$ 的数组 $a,b$。现在要求在两个数组中各选一个数，要求选出来的数之差不超过 $d$。问选出来的数的最大和是多少。

## Solution
看到什么不超过 $d$ 还是选两个数的问题，首先应该想到是二分或者双指针。这里采用二分，因为可以偷懒（有函数）。

先排序，然后对于每一个 $a$，用二分分别找出 $b$ 中与它相差不超过 $d$ 的数，然后取最大值即可。

但是注意，不能只找比它大 $d$ 的数，因为可能无解。你还需要找一找比它小 $d$ 但是又尽量大的数。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N = 2e5 + 10;
int n, m;
ll d, a[N], b[N];
 
int main(){
	scanf("%d%d%lld", &n, &m, &d);
	for(int i=1;i<=n;i++)
		scanf("%lld", &a[i]);
	for(int i=1;i<=m;i++)
		scanf("%lld", &b[i]);
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	ll ans = -1;
	for(int i=n;i>=1;i--){
		int idx1 = upper_bound(b + 1, b + 1 + m, a[i] + d) - b - 1;//比它大 d 的第一个位置 - 1 一定是差小于 d 的最大位置
		int idx2 = lower_bound(b + 1, b + 1 + m, a[i]) - b - 1;//比它自己小的第一个位置肯定是差最小和最大的
		if(idx1 && b[idx1] - a[i] <= d && b[idx1] - a[i] >= 0)//因为下标 -1，所以还需要判断合不合法（跨了两个 d 的情况）
			ans = max(ans, a[i] + b[idx1]);
		if(idx2 && a[i] - b[idx2] <= d && a[i] - b[idx2] >= 0)
			ans = max(ans, a[i] + b[idx2]);
	}
	printf("%lld\n", ans);
	return 0; 
}
```

---

## 作者：hellolin (赞：1)

## AtCoder Beginner Contest 302 - D - Impartial Gift

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc302_d) | [AtCoder 题面](https://atcoder.jp/contests/abc302/tasks/abc302_d) | [AC 记录](https://www.luogu.com.cn/record/111043578) | $\texttt{\color{f2b373}*682}$

说是两人的礼物差不能超过 `d`，要使和最大，那就枚举 $A$，再二分 $B$，就行了，时间复杂度 $O(n\log n)$。

可以用标准库里的 `lower_bound` 和 `upper_bound` 函数来二分。

设当前枚举 $A$ 序列，枚举到元素 $x$，那么在 $B$ 序列中我们要找到第一个大于等于 $x-d$ 值的位置（设它为 $l$），还要找第一个大于 $x+d$ 值的位置（设它为 $r$，注意这里右端点是不合法的值），这样一来，若 $r-l\ge 1$，说明合法值区间存在，要取最大就是 $r-1$ 位置的值加上 $x$ 就行了。

``` cpp
auto l=lower_bound(b.begin(),b.end(),x-d);
auto r=upper_bound(b.begin(),b.end(),x+d);
if(r-l>=1)
    ans=max(ans,x+*--r);
```

如果觉得难以理解，来看个栗子（样例 1）：

$$
n=2,\ m=3,\ d=2\\
A=3,10\\
B=2,5,15
$$

枚举序列 $A$ 的元素，当前是第一个。

此时 $x-d=1,\ x+d=5$，所以二分到的区间如下（青色）所示：

$$
A={\color{red}3},10\\
B={\color{cyan}2,5},{\color{yellow}15}
$$

实际上 $r$ 指向 $15$，但这里我们二分的是大于 $x+d$，说明 $r$ 不合法，所以要退一个位置。

那么第一个答案就是 $3+5=8$。

同理，枚举到第二个元素时：

$$
A=3,{\color{red}10}\\
B=2,5,{\color{yellow}15}
$$

我们发现左端点和右端点都指向 $15$，而实际上 $15$ 对于 $10$ 是个不合法值（因为它是右端点），所以此时不应计入答案。



所以样例 1 的最终答案是 $8$。

附上完整代码：

``` cpp
// 珍爱账号，请勿贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,m,d,ans;
vector<int>a,b;
void solve(){
    cin>>n>>m>>d;
    a.resize(n),b.resize(m);
    for(int&i:a)cin>>i;
    for(int&i:b)cin>>i;
    // 二分前保证区间有序
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    ans=-1;
    for(int x:a){
        auto l=lower_bound(b.begin(),b.end(),x-d);
        auto r=upper_bound(b.begin(),b.end(),x+d);
        if(r-l>=1)
            ans=max(ans,x+*--r);
    }
    cout<<ans<<endl;
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
```


---

## 作者：qwertim (赞：1)

# 题意
有两个长度分别为 $n$ 和 $m$ 的数组 $a$ 和 $b$，在两个数组中任选一个数，要求选出来的数的差不超过 $d$，求两个数的和的最大值。
# 思路
枚举 $a_i$，随后二分查找对应的 $b_i$ 使得 $b_i ∈[a_i-d,a_i+d]$，最后将所有和取最大值即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define fd(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
int n,m;
ll a[200005],b[200005],d,ans=-1;
int main(){
	cin>>n>>m>>d;
	fo(i,1,n)scanf("%lld",&a[i]);
	fo(i,1,m)scanf("%lld",&b[i]);
	sort(b+1,b+1+m);//因为要保持单调性，所以先排序
	fo(i,1,n){
		int l=1,r=m,mid,pos=-1;
		while(l<=r){
			mid=(l+r)>>1;
			if(b[mid]>=a[i]){
				if(b[mid]-d<=a[i])l=mid+1,pos=mid;//满足要求，继续去寻找有没有更大的
				else r=mid-1;//超出右边界，往左移
			}
			else{
				if(b[mid]+d>=a[i])pos=mid;
				l=mid+1;//不管超不超出左边界都要往右寻找
			}
		}
		if(pos!=-1)ans=max(ans,a[i]+b[pos]);//如果有就取最大值
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：small_john (赞：0)

## 思路

其实很简单，建议评黄。

我们知道，想要答案最大，对于每个 $a_i$，要找到符合条件的最大的 $b_p$，那么如果有一个 $a_j>a_i$，那么对于 $a_j$ 最好的 $b_q$ 一定大于等于 $b_p$。

所以就可以对 $a,b$ 按从小到大排序，设当前判断数为 $a_i$，$a_{i-1}$ 的最优答案为 $b_j$，那么对于这次搜答案，遍历 $j\sim m$ 即可，并保证 $b_j\leq a_i+d$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
const int N = 1e6+5;
int n,m,d,a[N],b[N],ans = -1;
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m>>d;
    for(int i = 1;i<=n;i++)
		cin>>a[i];
    for(int i = 1;i<=m;i++)
		cin>>b[i];
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    int j = 1;
    for(int i = 1;i<=n;i++)
    {
        while(j<=m&&b[j]<=a[i]+d)
		{
            if(abs(a[i]-b[j])<=d)
                ans = a[i]+b[j];
            j++;
        }
        j--;//用whlie循环跳出时j为不符合要求的第一个，所以要减一
	}
    cout<<ans;
 	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

二分查找简单题。

我们把 $a$ 全部存进一个 set 里（或者排序），然后对于每个 $b_i$ 查找 $a$ 中第一个大于 $b_i+d$ 的数，那么这个数的前驱必然是小于等于 $b_i+d$ 的最大数，判断其是否大于等于 $b_i-d$，然后计算和并取最大值即可。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=200005;
const ll p=1000000007;
const ll inf=1145141919810ll;
ll n,m,d,a[maxn],b[maxn],ans=-inf;
set<ll> s;
set<ll>::iterator it;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	//cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n>>m>>d;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s.insert(a[i]);
		}
		for(int i=1;i<=m;i++){
			cin>>b[i];
			it=s.upper_bound(b[i]+d);
			if((it==s.begin())||((it!=s.end())&&(*it<b[i]-d))) continue;
			if(b[i]-*prev(it)>d) continue;
			ans=max(ans,b[i]+*prev(it));
		}
		cout<<(ans==-inf?-1:ans);
	}
	return 0;
}
```

---

## 作者：lilong (赞：0)

### 题意

一个人要送礼物给另外两个人，现有 $n$ 件礼物要选一件送给第一个人，价值分别为 $a_1,a_2,\cdots,a_n$，有 $m$ 件礼物要选一件送给第二个人，价值分别为 $b_1,b_2,\cdots,b_m$。求在两件礼物之差不超过 $d$ 的情况下，价值总和的最大值。

### 思路

首先不难想到，要将 $a$ 和 $b$ 分别排序。然后对于每个 $a_i$（$b_i$ 做法同理）,在 $b$ 中二分查找 $ a_i - d $ 和 $ a_i + d $ 的位置，如果前者的位置大于后者，则说明矛盾，排去，否则计算此时的价值，并且更新答案（如果价值更大）。

具体实现见代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long

using namespace std;
int k1,k2,n,m,d,a[1000001],b[1000001],ans = -1 ;

signed main()
{
	cin >> n >> m >> d;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i];
	for( int i = 1 ; i <= m ; i ++ )
		cin >> b[i];
	sort( a + 1 , a + n + 1 );
	sort( b + 1 , b + m + 1 );
	for( int i = 1 ; i <= n ; i ++ )
	{
		k1 = a[i] - d;
		k2 = a[i] + d;
		k1 = lower_bound( b + 1 , b + m + 1 , k1 ) - b;
		k2 = upper_bound( b + 1 , b + m + 1 , k2 ) - b;
		k2 --;
		if( k1 > k2 ) continue;
		k2 = min( k2 , m );
		ans = max( ans , a[i] + b[k2] );
	}
	for( int i = 1 ; i <= m ; i ++ )
	{
		k1 = b[i] - d;
		k2 = b[i] + d;
		k1 = lower_bound( a + 1 , a + n + 1 , k1 ) - a;
		k2 = upper_bound( a + 1 , a + n + 1 , k2 ) - a;
		k2 --;
		if( k1 > k2 ) continue;
		k2 = min( k2 , n );
		ans = max( ans , b[i] + a[k2] );
	}
	cout << ans;
	return 0;
}
```


---

## 作者：guanyf (赞：0)

### 题意
- 给定两个长度分别为 $N,M$ 的序列 $A,B$，要求从中各选一个数，使得俩数的差值不超过 $D$，问俩数和的最大值。当没有符合条件的答案时，输出 $-1$。

- $1 \le N,M \le 2 \times 10^5$

### 导入
直接枚举两个数 $x$ 和 $y$，在判断 $\operatorname{abs}(x-y)$ 是否 $\le D$。

### 分析、思路
看到数据范围，就知道只能线性，顶多再加个 $\log(M)$。由于题目并不考虑顺序，因此可以先排个序，保证序列具有单调性。接着考虑怎么优化掉枚举 $y$。

1. 由于每次 $x$ 是平滑的变化的，真正影响答案的是它的边界 $x-D$ 和 $x+D$。并且序列具有单调性，因此可以双指针去移动这个区间。

2. 双指针太麻烦了怎么办？可以二分查找啊。每次找到最后一个满足 $\le x+D$ 且 $\ge x-D$ 的 $y$，接着 $ans = \max(ans,x+y)$。

#### 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int n, m, a[MAXN], b[MAXN], d, ans = -1;
signed main() {
  ios::sync_with_stdio(0);
  cin >> n >> m >> d;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
  }
  sort(a + 1, a + 1 + n);
  sort(b + 1, b + 1 + m);
  for (int i = 1; i <= n; i++) {
    int x = lower_bound(b + 1, b + 1 + m, a[i] - d) - b;
    int y = upper_bound(b + 1, b + 1 + m, a[i] + d) - b - 1;
    if (x <= m && b[x] <= a[i] + d && b[x] >= a[i] - d) {
      ans = max(ans, a[i] + b[x]);
    }
    if (y >= 1 && b[y] >= a[i] - d && b[y] <= a[i] + d) {
      ans = max(ans, a[i] + b[y]);
    }
  }
  cout << ans;
  return 0;
}

```


---

## 作者：CheZiHe929 (赞：0)

# AT_abc302_d 题解
## 原题链接
[**洛谷**](https://www.luogu.com.cn/problem/AT_abc302_d)

[**Atcoder**](https://atcoder.jp/contests/abc302/tasks/abc302_d)
## 题目大意
给你一个长度为 $n$ 的 $a$ 数组和一个长度为 $m$ 的 $b$ 数组。问满足 $\left | {a_i - b_j} \right | \leq d$ 的 $a_i + b_j$ 的最大值是多少，如果没有符合条件的就输出 $-1$。

## 思路分析
### 方法一
循环枚举 $a$ 数组中的每个数，然后再循环枚举 $b$ 中的每个数，判断 $\left | {a_i - b_j} \right | $ 是否 $ \leq d$。但是时间复杂度过高，肯定是会超时的。

### 方法二
设立一个 `bool` 数组，初始值为 `false`，循环输入 $a$ 数组的时候把所有与 $a_i$ 相差值 $\leq d$ 的 $b_j$ 更改为 `false`，最后判断 $b$ 数组中有无数字为 `true`。但是由于 $ 1\leq\ A_i,B_i\leq\ 10^{18} $，我们肯定也开不了这么大的数组，所以方法二被舍弃掉

### 方法三
我们可以用**二分**的思路来解决这道题。用 ```upper_bound``` 来查找 $b_j$，如果 $\left | {a_i - b_j} \right | \leq d$ 我们就维护答案 $ans$ 的值，这样的话时间复杂度就降低了很多，可以过。另外要注意一点，因为二分函数针对的是单调性数列，所以我们枚举之前要先排序一下 $a$ 数组和 $b$ 数组。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005],b[200005];
signed main(){
	long long n,m,d;
	cin>>n>>m>>d;
	long long ans=-1;//ans初始值定为-1，因为如果没有符合条件的值，ans也不会改变，就是符合要求的-1 
	for(long long i=1;i<=n;i++)
		cin>>a[i];
	for(long long i=1;i<=m;i++)//n,m不要混淆 
		cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);//排序保证单调性 
	for(long long i=1;i<=n;i++){
		int j=upper_bound(b+1,b+m+1,a[i]+d)-b-1;//不要忘记减去数组的首地址b以及多减1 
		if(abs(a[i]-b[j])>d)
			continue;//不符合条件就跳过 
		ans=max(ans,a[i]+b[j]);//维护答案ans的值 
	}
	cout<<ans<<endl;
	return 0;
}

```

## AC 记录
[**洛谷**](https://www.luogu.com.cn/record/110987754)

[**Atcoder**](https://atcoder.jp/contests/abc302/submissions/41615686)

**THE END.**

**THANK YOU.**

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
这道题有双指针和二分两种方法，但这里只讲二分法，因为赛时写出来的。

我们可以先对两个数组排一遍序，对于每一个 `a[i]` 我们想要找到一个 `b` 最后一个小于等于 `a[i] + d`，我们可以写出二分函数 `lower_bound(b + 1, b + 1 + m, a[i] + d + 1) - b - 1`。

这里来讲一下为什么用这个函数，先看 `lower_bound`，它的作用是找第一个大于等于的数，我们要找的是最后一个小于等于的数，因为这个序列里面没有浮点数，那么我们找第一个大于等于 `a[i] + d + 1` 的前一个值就是我们要找的。

找到值之后判断一下是否在我们要求的范围就可以了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
// #define int i64
const int maxn = 1000000;
i64 a[maxn];
i64 b[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	i64 n, m, d;
	cin >> n >> m >> d;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
	}
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	i64 ans = -1;
	for (int i = 1; i <= n; i++) {
		int id = lower_bound(b + 1, b + 1 + m, a[i] + d + 1) - b - 1;
		if (abs(a[i] - b[id]) <= d) {
			ans = max(ans, a[i] + b[id]);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：shinzanmono (赞：0)

# [ABC302D] Impartial Gift

### 题目要求：给定长度分别为 $n,m$ 两个数组 $a,b$，求 $\underset{i\in[1,n],j\in[1,m],|a_i-b_j|\leq d}{\max}a_i+b_j$  

对于每个 $a_i$，我们可以在**排好序的** $b$ 中二分查找处于 $[a_i-d,a_i+d]$ 的数所对应的 $b$ 的区间 $[l,r]$，此处可以使用 `std::lower_bound` 和 `std::upper_bound`。

根据函数的定义，当区间内没有满足条件的值的时候，$l>r$，我们特判这种情况。我们知道 $a + b > a + c(b>c)$，所以 $\underset{j\in[l,r]}{\max}a_i+b_j=a_i+b_r$。

所以我们最后只需要求出 $a_i+b_r$ 的最大值或判断无解即可。

```cpp
#include<iostream>
#include<algorithm>
const int sz = 2e5 + 10;
using ll = long long;
ll arr[sz], barr[sz];
int main() {
    int n, m;
    long long d;
    std::cin >> n >> m >> d;
    for (int i = 1; i <= n; i++) std::cin >> arr[i];
    for (int i = 1; i <= m; i++) std::cin >> barr[i];
    std::sort(barr + 1, barr + m + 1);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = std::lower_bound(barr + 1, barr + m + 1, arr[i] - d) - barr;
        int r = std::upper_bound(barr + 1, barr + m + 1, arr[i] + d) - barr - 1;
        if (l > r) continue;
        ans = std::max(ans, arr[i] + barr[r]);
    }
    std::cout << (ans == 0 ? -1 : ans) << "\n";
    return 0;
}
```

---

## 作者：code_hyx (赞：0)

这道题直接枚举两个礼物显然会超时，可以考虑一个礼物暴力枚举，另一个礼物用 $\log_2n$ 的复杂度直接查找。  
因为要让价值最大，所以给 $\text{Snuke}$ 的礼物价值应该是不超过 $a_i+d$ 的价值最大的礼物。  
注意，给 $\text{Snuke}$ 的礼物不一定比给 $\text{Aoki}$ 的礼物价值低，所以当没有符合条件的价值更高的礼物时，还要选择价值不低于 $a_i-d$ 的价值最大的礼物。    
代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a[200005],b[200005],n,m,d;
bool flag=true;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=n;i>=1;i--)
	{
		long long x=upper_bound(b+1,b+m+1,a[i]+d)-b-1;
		//cout<<"upper:"<<" "<<a[i]<<" "<<b[x]<<"\n";
		if(abs(a[i]-b[x])<=d)
		{
			cout<<a[i]+b[x]<<"\n";
			return 0;
		}
		long long y=lower_bound(b+1,b+m+1,a[i]-d)-b;
		//cout<<"lower:"<<" "<<a[i]<<" "<<b[y]<<"\n";
		if(abs(a[i]-b[y])<=d)
		{
			cout<<a[i]+b[y]<<"\n";
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```


---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc302_d#submit)

## Solution

整体思路是对每个 $B_i$ 匹配合适的 $A_j$，下文令 $A_i$ 表示 $A$ 数组中任意元素，令 $B_j$ 表示 $B$ 数组中任意元素。

这一题的数据范围是 $2 \times 10^5$， 明显要用 $O(n \log n)$ 的做法，由于对 $A$ 数组排序无后效性，此处选择对 $A$ 数组进行一个二的分，找到最大的 $A_i$ 且满足 $A_i \leq B_j + D$，也就是满足题目要求的最大 $A_i$，并需要在答案取最大值，即 $A_i + B_j$ 时检查合法性。

此处也可以选择对 $B$ 数组进行二分，过程如上所示。

## Code

```cpp
// 2023/5/23 Accept__

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int kMaxN = 2e5 + 7;

ll n, m, d, a[kMaxN], b[kMaxN], ans = -1, k;

inline ll max (ll a, ll b) {
    return (a > b) ? a : b;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> d;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= m; i++) {
        k = upper_bound(a + 1, a + n + 1, b[i] + d) - a - 1;
        (k != n + 1 && a[k] >= b[i] - d) && (ans = max(a[k] + b[i], ans));
    }
    cout << ans << '\n';
    
    return 0;
}
```


---

## 作者：Escapism (赞：0)

[ATC 原题](https://atcoder.jp/contests/abc302/tasks/abc302_d)

# 题意

给定两个长度分别为 $n,m$ 的序列，要求在两个序列中各找出一个数，两个数之间的差值**小于等于** $k$，现在求这两个数的和的最大值是多少。

# 思路

二分。

首先我们可以将两个序列各排一次序，让其满足二分所需的单调性。然后通过二分找出第对于每一个 $a_i$，与 $a_i$ 差值小于等于 $k$ 的最大值。

时间复杂度 $O(n\log n)$。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N = 2 * 1e5 + 10;
int n,m;
ll d,a[N],b[N];
 
int main(){
	cin>>n>>m>>d;
	for(int i = 1;i <= n;i++) cin>>a[i];
	for(int i = 1;i <= m;i++) cin>>b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	ll ans = -1;
	for(int i = n;i >= 1;i--){
		int tmp1 = upper_bound(b + 1, b + 1 + m, a[i] + d) - b - 1;
		//找出两数之差大于 d 的第一个位置，这个位置的前一个位置显然是差值小于等于 d 的最大位置。
		int tmp2 = lower_bound(b + 1, b + 1 + m, a[i]) - b - 1;
		//在一个数字已经确定的情况下，如果第二个数比第一个数小，第二个数与第一个数差最小时两数之和最大。
		if(tmp1 && b[tmp1] - a[i] <= d && b[tmp1] - a[i] >= 0) ans = max(ans, a[i] + b[tmp1]);
		//判断合法
		if(tmp2 && a[i] - b[tmp2] <= d && a[i] - b[tmp2] >= 0) ans = max(ans, a[i] + b[tmp2]);
	}
	printf("%lld\n", ans);
	return 0; 
}

```

[通过记录](https://atcoder.jp/contests/abc302/submissions/41649619)


---

## 作者：_Ad_Astra_ (赞：0)

二分。

考虑枚举选择的 $a_i$，剩下来就是要找到满足条件的最大 $b_j$ 即可。由于要找的数在 $a_i-d$ 到 $a_i+d$ 之间，因此不难想到二分。先找满足条件的大于 $a_i$ 的最大整数判断，如果不满足则找小于 $a_i$ 的最大整数即可。二分的话可以采用 `std::upper_bound` 与 `std::lower_bound` 实现。时间复杂度 $O(n\log m)$。实现时要注意二分查找的边界问题（可能导致出界）。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,d,ans=-1,a[200010],b[200010];
signed main()
{
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(b+1,b+m+1);
	b[0]=-0x3f3f3f3f3f3f3f3f;
	for(int i=1;i<=n;i++)
	{
		int id=upper_bound(b+1,b+m+1,a[i]+d)-b;
		id--;
		if(abs(a[i]-b[id])<=d)ans=max(ans,a[i]+b[id]);
		id=lower_bound(b+1,b+n+1,a[i])-b;
		id--; 
		if(abs(a[i]-b[id])<=d)ans=max(ans,a[i]+b[id]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：whx2009 (赞：0)

## 本题思路：
这道题看上去要用到 DP 去做，可是数据范围太大了，无法正常存储数据。然后我就往简单的方面想了一下，其实我们只需要给两组输入的数组排一个序，从每组的最后一个数据开始去找相差为 $D$ 的两个数据输出就可以了（因为我们排了序，后面的一定最大，所以在过程中哪个大了找那组的下一个就可以了）。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[2000001],b[2000001];
int main()
{
	long long n,m,d;
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int j=1;j<=m;j++) cin>>b[j];
	sort(a+1,a+1+n);//从小到大排序 
	sort(b+1,b+1+m);
	for(int i=n,j=m;i>0 && j>0;)
	{
		if(abs(a[i]-b[j])<=d)
		{
			cout<<a[i]+b[j];
			return 0;
		}
		else
		{
			if(a[i]>b[j]) i--;//哪边大了减哪边 
			else j--;
		}
	}
	cout<<-1;//如果以上都不行，就输出不行 
	return 0;//完美撒花 
}
```
* 请勿抄袭

---

