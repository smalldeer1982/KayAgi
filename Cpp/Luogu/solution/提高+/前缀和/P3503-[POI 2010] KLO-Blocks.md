# [POI 2010] KLO-Blocks

## 题目描述

Bytie 在生日时收到了一套木块。这些木块彼此无法区分，因为它们都是相同大小的立方体。Bytie 通过将一个木块放在另一个木块上形成了堆。不久，他就有了一整排这样的堆，一个接一个地排成一条直线。当然，这些堆的高度可以不同。Bytie 的父亲 Byteasar 给了他一个谜题。他给了他一个数字 $k$，并要求重新排列这些木块，使得高度至少为 $k$ 的连续堆的数量最大化。然而，Bytie 只能从严格高于 $k$ 的堆中取出顶部的木块，并将其放在相邻的堆上。此外，Bytie 不允许形成新的堆，他只能在已经存在的堆之间移动木块。

## 说明/提示

$1 \le n \le 10^6$，$1 \le m \le 50$，$1 \le a_i, k \le 10^9$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 6
1 2 1 1 5
1 2 3 4 5 6```

### 输出

```
5 5 2 1 1 0```

# 题解

## 作者：K8He (赞：25)

# P3503 Blocks 题解
[更好的阅读体验](https://www.cnblogs.com/Keven-He/p/15826462.html)

[原题传送门](https://www.luogu.com.cn/problem/P3503)

## 思路

首先我们可以发现，若 $a_l \sim a_r$ 的平均值大于等于 $k$，则这个区间一定可以转化为都大于等于 $k$ 的。我们就把这个问题化简成了“求最长的平均值大于等于 $k$ 的子序列”。

再去化简，可以发现，如果我们把序列中的每一项都减去 $k$，再求前缀和 $s$，若 $s_i-s_j\ge 0$，则区间 $[j,i]$ 一定满足条件。

那么我们考虑如何求这种区间。

不难发现，**若 $i<j$ 且 $s_i<s_j$，则选 $i$ 当左端点比 $j$ 更优，则选 $j$ 当右端点比 $i$ 更优。**

那么我们去维护一个单调栈存可能最优的左端点，栈中的元素都满足：在栈中 $j$ 在 $i$ 之上且 $s_i>s_j$。（这里自己好好思考一下）

根据我们维护的单调栈的性质，我们可以发现：

- 一个元素越靠栈顶，可以和它在一起的右端点越多，但产生的区间越短。
- 如果一个右端点与栈里的一个元素产生的区间合法，则该右端点与该元素之上的元素一定也能构成合法区间。

那么我们再从最右边开始枚举右端点，去找最大区间。如果一个右端点与栈顶的左端点可以构成合法区间那就更新答案，并把栈顶弹出（因为再靠左的右端点就算满足条件也没有这个长了），继续看浮出来的新栈顶是否合法。

记得判断 $s_i\ge 0$ 的情况。

## 代码

```cpp
#include <bits/stdc++.h>
#define _for(i,a,b) for(int i=a;i<=b;++i)
#define for_(i,a,b) for(int i=a;i>=b;--i)
#define ll long long
using namespace std;
const int N=1e5+10,inf=0x3f3f3f3f;
ll n,q,a[N],b[N],k,ans;
stack<ll>s1,s2;
int main(){
	scanf("%lld%lld",&n,&q);
	_for(i,1,n)scanf("%lld",&a[i]);
	while(q--){
		scanf("%lld",&k);
		ans=0;
		_for(i,1,n){
			b[i]=b[i-1]+a[i]-k;
			if(b[i]>=0)ans=max(ans,(ll)(i));
			if(s1.empty()||b[i]<b[s1.top()])s1.push(i);
		}for_(i,n,1){
			while(!s1.empty()&&b[i]-b[s1.top()]>=0){
				ans=max(ans,i-s1.top()),s1.pop();
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：kczno1 (赞：20)

答案是一段连续的区间，而且这个区间满足平均数>=k。

将所有数减去k，则这个区间和>=0。

再求个前缀和，则s[r]>=s[l-1]。

也就是对每个s[r],我们要求满足s[l]<=s[r]的最小的l。

如果s[r]>=s[l],那么r永远不会是右边的选择，所以可以扔掉。

维护一个单调递减的栈。

查询时二分最左的<=s[r]的s[l]。

时间nlogn。

这个建栈和查询是可以分开的。

如果s[r]>=s[l]，l的选择永远可以被r选择，而且会更优，所以l永远不用查询了。

所以可查询的数也可以建一个单调递减的栈。

随着s[r]递增，l是单调左移的，于是就可以O(n)了。

(t了一个点也是醉)

```cpp
#include<bits/stdc++.h>

void chmax(int &x,int y) { if(x<y)x=y; }
#define ll long long
#define N 1000100
int a[N],n;
ll s[N],now;
int q1[N],t1,q2[N],t2;

int main()
{
    freopen("1.in","r",stdin);
    int m,k,i;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;++i) scanf("%d",a+i);
    s[q1[0]=q2[0]=N-1]=1e18;//单调栈的哨点 
    while (m--)
    {
        scanf("%d",&k);
        for (i=1;i<=n;++i) s[i]=s[i-1]+a[i]-k;
        t1=1;t2=0;
        for (i=1;i<=n;++i)
        {
            now=s[i];
            if (now<s[q1[t1]]) q1[++t1]=i;
            while (now>=s[q2[t2]]) --t2;
            q2[++t2]=i;
        }
        int ans=0;
        for (;t2;--t2) 
        {
            now=s[i=q2[t2]];
            if (now<s[q1[t1]]) continue;
            while (now>=s[q1[t1]]) --t1;
            chmax(ans,i-q1[t1+1]);
        }
        printf("%d ",ans);
    }
}
```

---

## 作者：NashChen (赞：15)

## 题意

给定一条长为 $N$ 的正整数序列 $A[i]$ 和一个正整数 $K$ ，每次可以将序列中一个大于 $K$ 的数减去 $1$ ,再给它其中一个相邻的数加上 $1$ 。问若干次操作后，能够出现的最长区间，使得每一个数都 $\geq K$ 的长度是多少。$M$ 组询问。

$$N\leq 10^6,M\leq 50$$

## 题解

一道很好的思维题。

首先很容易想到的是，每个数都一定会将它大于 $K$ 的部分转移到相邻的数上，最后让一段区间内的数都等于 $K$，这样是最优的。

那么，经过操作之后每个数都等于 $K$ ，就直接等价于这段数的**平均值** $\geq K$ 。

因为平均值带除法，不好处理，所以我们将序列中的每个数减去 $K$ ，将问题转化为求**最大的**使得**区间和非负**的区间。

计算出处理后的序列的前缀和 $S[i]$ ，问题又进一步转化为

$$\text{最大化}(r-l),\text{使得}0 \leq l < r,S[l] \leq S[r]$$

$O(N^2)$ 枚举区间肯定是过不了这题的，我们寻找一些性质来优化算法。显然 $S[l] \leq S[r]$ 的条件限制了区间的扩大。这个问题非常简洁地体现出了答案的**合法性**和**最优化**之间的矛盾。

注意到在区间端点的选取时，若 $i < j,S[i] \leq S[j]$ ，$j$ **不可能被选作答案的左端点**。因为若 $S[j]\leq S[r]$ ，也会有 $S[i]\leq S[r]$ ，并且选取 $i$ 作为左端点区间更大。同理，$i$ 永远**不可能被选作右端点**。

于是，考虑维护一个 $S[i]$ 递减的单调栈。从 $1$ 到 $N$ ，每次只将小于栈顶的数压入栈中，这些就是所有可能的左端点。

同理，从 $N$ 到 $1$ ，每次只大于栈顶的数压入栈中，这些就是所有可能的右端点。

我们发现，可能作为答案的左端点或右端点都是单调的，这个性质非常漂亮。

我们只需要维护一个栈，另外一个端点直接枚举即可。具体操作如下

* 用单调栈维护所有可能的左端点。这些数是递减的

* 从 $N$ 到 $1$ ，每次只讨论**大于上一次讨论过的数**的数，这样可以讨论完所有可能的右端点。

* 因为每次讨论的右端点是递增的，所以 $S[l]\leq S[r]$ 的合法性也是单调的。也就是说，当 $S[r]$ 增加，原来合法的左端点仍然合法。而 $l$ 增加虽然仍然合法，但不可能使答案更优，所以在每次讨论右端点时，在保持栈顶元素合法的情况下不断弹出栈顶并更新答案，就可以计算出结果。

时间复杂度 $O(N)$ 。这道题的解法还是非常巧妙的。

## 代码

代码非常简单，价值在于挖掘题目性质的过程。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN= 1000005;
long long K,A[MAXN],S[MAXN];
int N,M,stac[MAXN],st,maxi,ans;

void solve(){
	ans= st= 0;
	for(int i=1;i<=N;++i) S[i]= A[i]-K;
	for(int i=1;i<=N;++i) S[i]+= S[i-1];
	for(int i=1;i<=N;++i) if(!st || S[stac[st]]>S[i]) stac[++st]= i;
	for(int i=N,j=N;i>=1;--i){
		if(S[i]>=0) ans= max(ans,i);
		if(i==N || S[i]>S[j]){
			while(st && S[i]>=S[stac[st]]){
				ans= max(ans,i-stac[st]);
				st--;
			}
			j= i;
		}
	}
	return;
}

void Input(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;++i)
		scanf("%lld",&A[i]);
	return;
}

int main(){
	Input();
	while(M--){
		scanf("%lld",&K);
		solve();
		printf("%d ",ans);
	}
	return 0;
}
```

---

## 作者：huangwenlong (赞：11)

合法的区间~~显然~~是一段区间平均值≥K的区间。因为操作次数是无限的，可以把这个区间每个数都变成平均值。


为了方便，可以把原来的序列的每个数减去k再计算前缀和sum，区间和≥0即合法。


直接枚举区间肯定会TLE。


很多求符合条件的区间的问题都可以用单调队列 or 单调栈优化决策，于是想想怎么优化。


-----

要求一段合法的区间，就是要找一个满足的$sum[i]-sum[j] \geq 0$的数对i,j。


稍加思考，发现若$k < j$且$sum[k] \leq sum[j]$，则对于一个右端点i来说，$sum[i]-sum[k] \geq sum[i]-sum[j]$，且$i-k > i-j$，故选k永远比选j优。


用单调栈维护这样的决策，整个栈是单调递减的。


先判断下要不要把i压进栈里，之后二分找到一个满足$sum[i]-sum[j] \geq 0$且最小的j，更新下答案ans=max(ans,i-j)就好了。


时间复杂度为$O(m \cdot n\;log\,n)$，还是过不了。


-----

再稍加思考，发现若$i > j$且$sum[i] \geq sum[j]$，则对于一个左端点k来说，$sum[i]-sum[k] \geq sum[i]-sum[j]$，且$i-k > j-k$，故选i永远比选j优。于是我们只需对其中的某些右端点做决策就好了。


这些右端点i的sum[i]肯定是单调递减的，所以不需要再二分了，直接把当前栈中满足$sum[i]-sum[j] \geq 0$的都弹走，最后一个被弹走的就是最优的j，更新下答案。因为被弹走的这些j都不会被更靠前的i用到了。


直觉告诉我们再搞一个单调栈维护就好，但是对于我这样的自带超大常数选手，这样会被卡。


事实上并不需要再搞一个单调栈。从后往前做决策，只有当前的sum[i]比后面的都大就做一下决策就好。


时间复杂度$O(m \cdot n)$


-----

还有一个小优化，读入的时候先算好序列的平均值，对于不大于平均值的k，答案肯定是n。


```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 1000005
using namespace std;
int n, m, a[maxn];
long long avar, sum[maxn];
int sta[maxn];
int solve(int k)
{
    int top = 0;
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + a[i] - k;
        if (!top || sum[sta[top]] > sum[i])
            sta[++top] = i;
    }

    long long ans = 0, maxi = -0x7fffffffffffffff;
    for (int i = n; i >= 1; i--)
    {
        if (sum[i] >= 0)
            ans = max(ans, (long long)i);
        if (sum[i] > maxi)
        {
            for (; top && sum[i] - sum[sta[top]] >= 0; top--)
                ans = max(ans, (long long)i - sta[top]);
            maxi = sum[i];
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        avar += a[i];
    }
    avar /= n;

    int k;
    while (m--)
    {
        cin >> k;
        if (k <= avar)
            cout << n << ' ';
        else
            cout << solve(k) << ' ';
    }
    return 0;
}
```

---

## 作者：ysy20021208 (赞：5)

# [bzoj2086][Poi2010]Blocks

### Description

　　给出N个正整数a[1..N]，再给出一个正整数k，现在可以进行如下操作：每次选择一个大于k的正整数a[i]，将a[i]减去1，选择a[i-1]或a[i+1]中的一个加上1。经过一定次数的操作后，问最大能够选出多长的一个连续子序列，使得这个子序列的每个数都不小于k。

　　总共给出M次询问，每次询问给出的k不同，你需要分别回答。

### Input

　　第一行两个正整数N (N <= 1,000,000)和M (M <= 50)。

　　第二行N个正整数，第i个正整数表示a[i] (a[i] <= 10^9)。

　　第三行M个正整数，第i个正整数表示第i次询问的k (k <= 10^9)。

### Output

　　共一行，输出M个正整数，第i个数表示第i次询问的答案。

### Sample Input

5 6
1 2 1 1 5
1 2 3 4 5 6

### Sample Output

5 5 2 1 1 0

### 思路

 　　首先我们看一看题，发现在题目中只是问最长的一段子序列的长度，并且没有限制操作多少次，所以我们能发现一个性质，当且仅当这个序列的平均数大于等于k时，这个序列为合法序列。所以我们可以将每一个数都减去k，再找出最长的子序列和大于零。由于是寻找连续数字的和，我们就可以想到运用前缀和，这样求一段区间就可以实现$O(1)$查询。我们再看，由于是求最长，所以我们要找到距离尽可能远的两个前缀和，且后者减去前者大于等于零，我们想到$n^2$算法，但分析时间复杂度明显不对，所以······

　　经过思考，我们可以发现一个性质，就是如果已经遍历到$i$，现在有$j \lt k$&&$sum[j] \lt sum[k]$，显然选取$j$作为做左端点明显比$k$作为左端点要更优，所以我们可以根据这个性质发现维护栈时只有当当前$sum[i] \lt sum[sta[top]]$时才能压入栈内，所以我们发现这是一个单调递减的栈。由于我们是从$1~n$找出的单调栈，所以我们更新答案应该从$n   ~ 1$，我们发现如果当$sum[i]-sum[sta[top]] \ge 0$时，应该将栈顶弹出，这样不会是答案变小，但是有人会问，如果下一个的$sum$比现在这个的$sum$小，并且比栈顶的$sum$小，那不就更新不出答案了吗？但是我们仔细画一画，如果真的是那样，以下一个为右端点远没有以现在这个为右端点更优。

### 代码

```c++
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1000001
int n,m,k,ans;
int number[N];
long long sum[N];
int f[N],idx,queue[N];
void push(int ord)
{
    while(idx&&sum[queue[idx]]>sum[ord]) idx--;
    queue[++idx]=ord;
}
void play()
{
    idx=ans=0;
    queue[++idx]=0;
    for(int i=1;i<=n;i++)
    {
        sum[i]=sum[i-1]+number[i]-k;
        if(sum[i]<sum[queue[idx]]) queue[++idx]=i;
    }
    for(int i=n;i;i--)
    {
        while(sum[i]-sum[queue[idx]]>=0&&idx) idx--;
        ans=max(ans,i-queue[idx+1]);
    }
    printf("%d ",ans);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&number[i]);
    for(int j=1;j<=m;j++) scanf("%d",&k),play();
}
```

---

## 作者：Alex_Wei (赞：4)

> **[P3503 [POI2010]KLO-Blocks](https://www.luogu.com.cn/problem/P3503)*
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

多组询问要求我们必须使用线性做法，而一个区间满足条件等价于其平均值 $\geq k$，即令 $s$ 表示 $a - k$ 的前缀和，则 $s_{l - 1} \leq s_r$ 是区间合法的充要条件。

乍一看没啥思路，似乎要数据结构维护，因为我们需要查询 $\leq s_i$ 的所有数的最小下标（$i$ 之后的位置没有贡献，可以不管）。但就算这样也得排序。

观察性质，注意到若 $s_i < s_j$ 且 $i < j$，那么 $j + 1$ 不会作为区间 **左端点** 出现，因为 $i + 1$ 更优。同理，若 $i$ 不会作为区间 **右端点** 出现，因为 $j$ 更优。换句话说，只有 **前缀最小值** 的位置才会作为区间左端点，**后缀最大值** 的位置才会作为区间右端点。

因此，两遍单调栈求出前缀最小值和后缀最大值对应的位置，根据单调性只需用两个指针维护。具体地，从左到右遍历每个前缀最小值，找到最右边的一个后缀最大值使得该最大值不小于当前的前缀最小值。由于前缀最小值在不断减小，故其对应的后缀最大值的下标也单调不降，用指针维护即可。时间复杂度 $\mathcal{O}(mn)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0; char s = getchar();
	while(!isdigit(s)) s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return x;
}
const int N = 1e6 + 5;
long long n, k, m, a[N], s[N], smx[N], t1, pmn[N], t2;
void solve() {
	long long ans = 0, l = 0; t1 = t2 = 0;
	for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i] - k;
	for(int i = 1; i <= n; smx[++t1] = i++) while(t1 && s[i] >= s[smx[t1]]) t1--;
	for(int i = n - 1; ~i; pmn[++t2] = i--) while(t2 && s[i] <= s[pmn[t2]]) t2--;
	while(t2) {
		while(l < t1 && s[smx[l + 1]] >= s[pmn[t2]]) l++;
		ans = max(ans, smx[l] - pmn[t2--]);
	} cout << ans << " ";
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= m; i++) k = read(), solve();
	return 0;
}
```

---

## 作者：小塘空明 (赞：4)

首先看下复杂度。m*n50000000………，毫无疑问要用线性算法。

首先我们可以发现，因为加减操作一定能让区间内所有数都为该区间的平均数。

所以我们只要求一个最长的区间，这个区间的平均数大于等于k。

首先我们可以做一个转换，将所有数减去k后求前缀和数组s。

问题转换成了关于一个i，求一个最小的j满足s[i]-s[j]>=0

我们维护可能作为i，和可能作为j的候选集合。

假设j1<j2,s[j1]<s[j2],那么对于任意一个i，j1都比j2更优。

假设i1<i2,s[i1]<s[i2],对于任意一个j，i2都比i1更优。

所以我们用两个单调栈维护即可，在实际操作中可以在计算答案时顺便维护i的单调栈。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const ll size=1e6+10,inf=1e18;
ll n,m,a[size];ll ave,top,sta[size],s[size];
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
inline ll solve(ll x){
    ll ans=0,maxn=-inf;top=0;
    for(ll i=1;i<=n;i++){
        s[i]=s[i-1]+a[i]-x;
        if(s[i]<s[sta[top]]) sta[++top]=i;
    }
    for(ll i=n;i>=1;i--){
        if(s[i]>=0) ans=max(ans,i);
        if(s[i]>maxn){
            for(;top&&s[i]-s[sta[top]]>=0;top--) ans=max(ans,i-sta[top]);
            maxn=max(maxn,s[i]);
        }
    }
    return ans;
}
int main(){
    n=read();m=read();
    for(ll i=1;i<=n;i++) a[i]=read(),ave+=a[i];
    for(ll i=1;i<=m;i++){
        ll x=read();
        if(n*x<=ave){if(i!=m) printf("%lld ",n);else printf("%lld",n);continue;}
        ll res=solve(x);
        if(i!=m) printf("%lld ",res);
        else printf("%lld",res);
    }
    return 0;
}
```


---

## 作者：chihik (赞：3)


首先可以知道一个区间满足条件的必要条件是该区间的平均数大于等于 $k$ 。

进一步可以发现这是一个充要条件。因为大于 $k$ 的数一定能填补到小于 $k$ 的数。

记一个合法的区间为 $[l,r]$ ，$sum$ 为 $a$ 的前缀和。

$$sum[r]-sum[l-1] \ge k \times (r-l+1)$$

$$sum[r]- k \times r \ge sum[l-1] - k \times (l-1)$$

记$s_i=sum[i]-k \times i$

则有 $s_r-s_{l-1} \ge 0$

我们可以$\Theta(n)$处理出$s$ ，然后就可以用单调栈求解了。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 1000000;
int n , m , k , a[ MAXN + 5 ] , Top , Stk[ MAXN + 5 ]; 
long long sum[ MAXN + 5 ];

int main( ) {
//  freopen("blocks.in","r",stdin);
//  freopen("blocks.out","w",stdout);
	
	scanf("%d %d",&n,&m);
	for( int i = 1 ; i <= n ; i ++ )
		scanf("%d",&a[ i ]);
	while( m -- ) {
		scanf("%d",&k);
        for( int i = 1 ; i <= n ; i ++ )
            sum[ i ] = sum[ i - 1 ] + a[ i ] - k;
        
        int Ans = 0;
        Top = 0; Stk[ ++ Top ] = 0;
        for( int i = 1 ; i <= n ; i ++ )
            if( sum[ i ] < sum[ Stk[ Top ] ] ) Stk[ ++ Top ] = i;
        for( int i = n ; i >= 1 ; i -- ) {
            while( Top && sum[ i ] - sum[ Stk[ Top ] ] >= 0 ) Top --;
            Ans = max( Ans , i - Stk[ Top + 1 ] );
        }
        printf("%d ",Ans);
	} 
	return 0;
}
```


---

## 作者：Flynewcat (赞：2)

### 思路
假如我们先给每个位置减 $k$，然后再求前缀和 $sum_i$，那么我们就可以发现**如果对于一个区间 $(i,j]$（注意是左开右闭区间）满足 $sum_j−sum_i≥0$，那么这个区间就一定可以满足条件**。
很显然，若 $i<j$ 且 $sum_i<sum_j$，那么让 $i$ 作区间左端点显然更优，因为它减得更小，上面的不等式也就更可能大于零。因此我们可以先从左往右维护一个单调递减的栈，然后再从右往左遍历，如果满足上述不等式，就更新答案，然后再弹出栈顶，看看新栈顶是否满足条件。
### 代码
```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,m;
	cin >> n >> m;
	int a[n+5]={};
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	for(int j = 1;j <= m;j++){
		int k,maxn = -0x3f3f3f3f;
		cin >> k;
		int sum[n+5]={};
		for(int i = 1;i <= n;i++)
			sum[i] = sum[i-1]+a[i]-k;
		stack<int> s;
		for(int i = 1;i <= n;i++){
			if(sum[i] >= 0)maxn = max(maxn,i);
			if(s.empty() || sum[s.top()] > sum[i])
				s.push(i);
		}
		for(int i = n;i >= 1;i--)
			while(!s.empty() && sum[i] - sum[s.top()] >= 0){
				maxn = max(maxn,i-s.top());
				s.pop();
			}
		cout << maxn << ' ';
	}
	return 0;
}
```

---

## 作者：bmatrix (赞：1)

$m$ 很小，考虑单次询问 $O(n)$ 求解。

首先注意到，一个区间合法（可以通过操作使得每个数都 $\ge k$）等效于这个区间平均值 $\ge k$。

感性理解，这个操作相当于一个元素把自己的值送给了与它相邻的元素，总和不变。如果平均值 $\ge k$ 且存在一个 $<k$ 的元素，根据抽屉原理必然存在一个 $>k$ 的元素，这个大数一定可以把自己多余的部分转移到那个小数上，所以合法。

问题转化为找到最大的 $r-l+1$ 使得 $\sum_{i=l}^ra_i\ge (r-l+1)k$，变形得到 $\sum_{i=l}^r(a_i-k)\ge 0$。

令 $a_i\leftarrow a_i-k,l\leftarrow l-1$，构造前缀和序列 $s$，式子化为 $s_r-s_l\ge 0$。

平衡树能做，但是多一个大常数 $\log$，数据范围这么大显然过不去。

考虑什么样的 $l$ 和 $r$ 是没用的。

显然如果 $i<j\land s_i\le s_j$，则 $j$ 不可能作为 $l$，同理 $i$ 也不能作为 $r$。

于是我们发现合法的 $l$ 和 $r$ 都满足对应的 $s$ 值递减。求合法的 $l$ 要从左到右枚举，求合法的 $r$ 要从右到左枚举。

在枚举 $r$ 的过程中，$s$ 是增大的，因此之前合法的 $l$ 现在依旧合法，所以考虑先处理出合法的 $l$，维护一个 $l$ 的指针即可做到线性。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
#define int ll
#define gmin(x, y) (x = min(x, y))
#define gmax(x, y) (x = max(x, y))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double f128;
typedef pair<int, int> pii;
constexpr int N = 1e6 + 5;
int n, m, a[N], s[N];
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    while(m--) {
        int k; cin >> k;
        rep(i, 1, n) s[i] = s[i - 1] + a[i] - k;
        stack<int, vector<int>> stk;
        stk.push(0);
        rep(i, 1, n) if(s[i] < s[stk.top()]) stk.push(i);
        int ans = 0, las = -1e18;
        per(i, n, 1) {
            if(s[i] <= las) continue;
            while(!stk.empty() && s[i] >= s[stk.top()]) {
                gmax(ans, i - stk.top());
                stk.pop();
            }
            las = s[i];
        }
        cout << ans << ' ';
    }
    return 0;
}
```



---

## 作者：ZZ作者 (赞：1)

首先明确，这题的答案就是找一个最长的区间，使$avg \geq k$。

可以把所有元素-=$k$，然后就变成了找最长的$sum \geq 0$的区间

如何找？想到维护个前缀和，那么所有$i,j$满足$pre_i \leq pre_j$都是合法答案

发现最优的答案只要使左端点尽量靠左，右端点尽量靠右

所以先给左端点弄成单减的（因为尽量靠左，所以这里是$<S[top]$的都直接压在栈顶）

然后从最右边开始，一个一个把数往里丢，找到比这个数小的数中最靠左（也就是最大）的一个，更新答案，因为找到的这个点和新枚举的点组成的答案不会更优，所以这个过程中直接$top$--就行。

代码很简单，重在思考。
```cpp
#include<bits/stdc++.h>
#define MAXN 1000005
#define ll long long
using namespace std;

ll a[MAXN]={0};
ll p[MAXN]={0};
ll n,m,t,ans;

struct STA
{
	ll v,id;
}S[MAXN]={0};
ll top=0;

int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);	
	while(m--)
	{
		scanf("%lld",&t);
		for(int i=1;i<=n;i++)p[i]=a[i]+p[i-1]-t;
		top=0;
		ans=0;
		for(int i=1;i<=n;i++)
		{
			if(top==0||p[i]<S[top].v)
			{
				S[++top].v=p[i];
				S[top].id=i;
			}
		}
		for(ll i=n;i>=1;i--)
		{
			if(p[i]>=0)
			{
				ans=max(ans,i);
				continue;
			}
			while(top&&p[i]>=S[top].v)
			{
				ans=max(ans,i-S[top].id);
				top--;
			}
		}
		printf("%lld ",ans);
	}
	return 0;
}
```

---

## 作者：破忆 (赞：0)

## 【题意】

找到一个平均值>=k的区间，使得区间长度最大，求最大的区间

## 【分析】

构造$a[i]$的前缀和$s[i]$

对于每个$i$，要找到一个最小的j

使得$s[i]-s[j-1]>=(i-j+1)*k$

即$s[i]-i*k>=s[j-1]*(j-1)*k$

注意到和某个下标有关的量都在同一边

~~这个式子非常漂亮~~

记$s'[i]=s'[i-1]+a[i]-k$

对于每个$i$，求最小的$j$

使得$s'[i]>=s'[j]$即可

对于求最小的$j$，可以用单调队列维护

## 【算法】

单调队列
## 【代码】
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#define LL long long
#define RE register
#define IN inline
using namespace std;
const int maxn=1e6+5;
int n,m;
int a[maxn],stk[maxn],top,ans;
LL s[maxn];
IN int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
// 	freopen("P3503.in","r",stdin);
// 	freopen("P3503.out","w",stdout);
	n=read(),m=read();
	for(RE int i=1;i<=n;i++) a[i]=read();
	for(RE int i=1;i<=m;i++){
		RE int k=read();
		for(RE int j=1;j<=n;j++) s[j]=s[j-1]+a[j]-k;
		stk[top=1]=0;
		ans=0;
		for(RE int j=1;j<=n;j++) if(s[j]<s[stk[top]]) stk[++top]=j;
		for(RE int j=n;j;j--){
			while(top&&s[j]-s[stk[top]]>=0) top--;
			ans=max(ans,j-stk[top+1]);
		}
		printf("%d%c",ans,i==m?'\n':' ');
	}
	return 0;
}
```


---

