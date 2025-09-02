# Cherry

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ . Find the maximum value of $ max(a_l, a_{l + 1}, \ldots, a_r) \cdot min(a_l, a_{l + 1}, \ldots, a_r) $ over all pairs $ (l, r) $ of integers for which $ 1 \le l < r \le n $ .

## 说明/提示

Let $ f(l, r) = max(a_l, a_{l + 1}, \ldots, a_r) \cdot min(a_l, a_{l + 1}, \ldots, a_r) $ .

In the first test case,

- $ f(1, 2) = max(a_1, a_2) \cdot min(a_1, a_2) = max(2, 4) \cdot min(2, 4) = 4 \cdot 2 = 8 $ .
- $ f(1, 3) = max(a_1, a_2, a_3) \cdot min(a_1, a_2, a_3) = max(2, 4, 3) \cdot min(2, 4, 3) = 4 \cdot 2 = 8 $ .
- $ f(2, 3) = max(a_2, a_3) \cdot min(a_2, a_3) = max(4, 3) \cdot min(4, 3) = 4 \cdot 3 = 12 $ .

So the maximum is $ f(2, 3) = 12 $ .

In the second test case, the maximum is $ f(1, 2) = f(1, 3) = f(2, 3) = 6 $ .

## 样例 #1

### 输入

```
4
3
2 4 3
4
3 2 3 1
2
69 69
6
719313 273225 402638 473783 804745 323328```

### 输出

```
12
6
4761
381274500335```

# 题解

## 作者：Fido_Puppy (赞：3)

首先，我们可以考虑设 $a_i$ 为我们选的最优序列里的最大值。

接下来要确定最小值。

每次加进一个数，只能使最小值不变或者令它更小。

所以，我们考虑只加入它的相邻的一个。

也就是说，最优序列肯定是由两个相邻的数组成的。

所以我们就可以 $O(N)$ 过了这道题辣！

别忘记要开 long long。

### 代码君

```cpp
%:include"bits/stdc++.h"
using namespace std;
#define Max(a,b) (a>b? a:b)
int T,n,a[100001];
long long ans;
signed main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>T;
	while (T--) {
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		ans=0;
		for(int i=2;i<=n;i++) ans=Max(ans,1ll*a[i]*a[i-1]);
		cout<<ans<<endl;
	}
	return 0;
}
```

完结撒花！ ^.^

---

## 作者：MikeC (赞：2)

## 分析

假设我们有两个相邻的数 $a,b\,(a\lt b)$，显然对于这个长度为 $2$ 的序列的解是 $a\cdot b$。现在我们向 $b$ 后面添加一个数 $c$，对于这个序列的解改变当且仅当两种情况：

- 第一种情况，当 $b\lt c$ 时，解为 $a\cdot c$。
- 第二种情况，当 $a\gt c$ 时，解为 $b\cdot c$。

对于第一种情况，显然 $b\cdot c\gt a\cdot c$，所以我们将 $a$ 移出序列可以得到更优解；对于第二种情况，显然解与 $a$ 无关。综上，我们只需要考虑序列长度为 $2$ 的情况，因此我们只需要对所有数依次判断更新答案即可。

记得开```long long``` ，时间复杂度  $O(n)$。

## 代码

``````cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int ans;
int a[100001];
signed main(){
	scanf("%lld",&t);
	while(t--){
		memset(a,0,sizeof(a));
		ans=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++){
			ans=max(ans,a[i]*a[i+1]);
		}
		printf("%lld\n",ans);
	}
}
``````



---

## 作者：NXYorz (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1554A)

---------
### 题目大意
给定序列 $a_n$,且 $1\le l < r \le n$,最大化 $\max{(a_l,a_{l+1},...,a_r)}\times \min{(a_l,a_{l+1},...,a_r)}$。

--------
### 分析

假设我们此时已经有了一组 $(l,r)$, 如果将 $r$ 扩大， 那么一个新的元素 $a_{r+1}$ 将加入， 假设 $a_{r+1}$ 比 $a_l,a_{l+1},...,a_r$ 都要小，那么只会使答案变小。 如果 $a_{r+1}$ 不是最大的也不是最小的，那么不会对答案产生任何影响。 如果 $a_{r+1}$ 比 $a_l,a_{l+1},...,a_r$ 都要大，那么就类似于将 $(l + 1,r+ 1)$ 向左扩增元素。且新的元素 $a_l$符合前两种情况。

综上发现，区间越大不会使结果更优，反而有更劣的可能，于是可以最小化区间，即令 $r - l = 1$。 然后枚举 $l$ 即可。

复杂度 $O(T\times N)$。

---------
### $\texttt{Code}$
```cpp
#include<cstdio>
#include<cstring>

using namespace std;

const int N = 1e5 + 10;
typedef long long ll;

int t,n;
long long a[N];
long long ans;

inline long long max(long long x , long long y)
{return x > y ? x : y;}

void work()
{
    scanf("%d",&n); int maxn = 0; ans = 0;
    a[n + 1] = 0;
    for(int i = 1; i <= n; i++)
        scanf("%lld",&a[i]);
    
    for(int i = 1; i < n; i++)
        ans = max(ans , a[i] * a[i + 1]);
    printf("%lld\n",ans);
}

int main()
{
   // freopen("aa.in","r",stdin);
    scanf("%d",&t);
    while(t--)
        work();
}
```

---

## 作者：Joshua_He (赞：2)

 [题目在这里](https://codeforces.com/contest/1554/problem/A)  
在[我的博客](https://www.cnblogs.com/joshuahxz210/p/15083735.html)食用更佳哦

## 总体思路

**贪心**

我们要找到整个数列最大的数及其相邻两边最大的数，它们的乘积是答案。

这是因为，我们要保证答案最大，就得保证区间 $\max$ 值和其 $\min$ 值都尽可能最大。  
我们所做的所有操作都是要使 $\max$ 值和 $\min$ 值尽可能的大。  
很容易就发现，只有 $\max$ 值符合我们的预期。无论如何扩展区间，$\min$ 值都只会减少，不会增加。移动区间也是。  
这时我们所做的就是，用区间大小控制 $\min$ 值，同时用区间位置控制 $\max$ 值，这样可以保证答案最大。  
所以我们的区间范围取最小，即 $2$，暴力遍历搜索一遍就好啦。

## AC代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int INF=0x3f3f3f3f;
int n,a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//关闭同步流，加速
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		ll ans=-INF;
		for(int i=1;i<n;i++)
			ans=min(ans,1ll*a[i]*a[i+1]);//max
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1554A)

显然多个数的区间并不会比两个数的区间更优。所以只需要枚举所有长度为 $2$ 的区间即可。

时间复杂度 $O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int
#define ull unsigned long long 
using namespace std;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    back x*f;
}
ll t,n,a[100001];
int main()
{
	cin>>t;
	while(t--)
	{
		ll maxx=-1e9;
		cin>>n;
		for(ri i=1;i<=n;i++)
			a[i]=read();
		for(ri i=1;i<n;i++)
			maxx=max(maxx,a[i]*a[i+1]);
		cout<<maxx<<endl; 
		
	}
    back 0;
}
```

---

## 作者：Microperson (赞：1)

[题目](https://www.luogu.com.cn/problem/CF1554A)

## 题目大意：
给你一个长度为 $n$ 的序列，在所有的 $(l,r)$ 中找到 $\max{(a_l,a_{l+1},...,a_r)}\times \min{(a_l,a_{l+1},...,a_r)}$.
## 腐朽的思路：
我们只需要考虑相邻的两个值的乘积即可。为什么？如果 $l$ 和 $r$ 不相邻，那么 $(l,r)$ 这个区间中所产生的答案一定不会比相邻所产生的结果大。比如说：
```
114514 514 114 1919810 114 514
```
当你想要选择 $(1,4)$ 这个区间时，发现 $114$ 限制了区间的最小值，所以说区间越大，最小值限制越大，所以说相邻的两个数之间定能产生最大值，并且不相邻的区间的最大值一定不会比相邻所产生的结果大。所以这道题就解决了。
## 新鲜出炉的 code:
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define int long long
using namespace std;

int t,n;
int a[100010];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		int ans=-1;
		for(int i=1;i<=n;i++){
 			scanf("%lld",&a[i]);
		}
		for(int i=1;i<n;i++){
				ans=max(ans,a[i]*a[i+1]);
		}
		cout<<ans<<endl;
	}
	return 0;
}

```



---

## 作者：Acc_Robin (赞：0)

挺有意思一道题，一开始看这题第一反应是双指针/单调栈，我是不是没救了![jk](https://xn--9zr.tk/jk)

#### 题意

给你一个序列 $\{a\}$，找出一对 $(l,r)$ 使得

$$
\max(a_l,a_{l+1},\cdots,a_r)\times \min(a_l,a_{l+1},\cdots,a_r)
$$

最大。

$n\le 10^5$

#### 题解

先说结论：

只需要求出最大的 $\max(a_i,a_{i+1})\times \min(a_i,a_{i+1})$即可。

为什么呢？我们考虑分类讨论一下：

对于三个数 $a_i,a_{i+1},a_{i+2}$

- 如果最大/最小值分别在 $i,i+1$ 处取得，那么 $a_{i+2}$ 对答案没有贡献，不需考虑。

- 如果最大值在 $i$ 或 $i+1$ 处取得，最小值在 $i+2$ 处取得，那么 $(i,i+1)$ 这个对子的答案更优，$a_{i+2}$ 对答案没有贡献。

- 如果最小值在 $i$ 或 $i+1$ 处取得，最大值在 $i+2$ 取得，那么我们在考虑 $(i+1,i+2)$ 这个情况的时候就会计入贡献。

综上所述，结论成立。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N=1e5+9;
	using ll=long long;
	int a[N],n,i;
	ll r;
	void work(){
		for(cin>>n,i=1;i<=n;++i)cin>>a[i];
		for(i=1;i<n;++i)r=max(r,1ll*a[i]*a[i+1]);
		cout<<r<<'\n',r=0;
	}
}
int main(){
	int T;for(cin>>T;T--;)Acc::work(),0;
}
```

---

## 作者：Leasier (赞：0)

考虑钦定 $l$，容易发现，$r$ 向右扩展不一定带来更大的区间最大值，而可能带来更小的区间最小值。所以，只有 $a_r$ 大于此前区间最大值，才可能带来更大的答案；只有 $a_l$ 是区间最小值，$[l + 1, r]$ 的答案才可能会大于 $[l, r]$ 的答案。

但这样貌似还是不可做。考虑答案子序列的长度，例如：有三个可能的答案区间 $[l, l + 1]$、$[l, l + 2]$ 和 $[l + 1, l + 2]$。当 $a_{l + 2}$ 成为了第二个区间的最小值，显然不会比另外两个区间答案的最大值更优；当 $a_{l + 2}$ 成为了第二个区间的最大值，同理。以此类推，我们只需要用长度为 $2$ 的序列更新答案。

代码：
```cpp
#include <stdio.h>
 
typedef long long ll;
 
int a[100007];
 
inline ll max(ll a, ll b){
	return a > b ? a : b;
}
 
int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n;
		ll ans = 0;
		scanf("%d", &n);
		for (int j = 1; j <= n; j++){
			scanf("%d", &a[j]);
		}
		for (int j = 1; j < n; j++){
			ans = max(ans, (ll)a[j] * a[j + 1]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：张晟轩 (赞：0)

## 题目分析：
先证一个引理：  
若已经考虑数列 $\{a_i,a_{i+1},\dots,a_j\}$, 则加入元素 $a_{j+1}$ 后，若 $\{a_i,\dots,a_j,a_{j+1}\}$ 的最大值与最小值之积更大，则 $a_{j+1}=max(a_i,\dots,a_j,a_{j+1})$. 此时， $\{a_{i+1},\dots,a_{j+1}\}$ 的最大值与最小值之积显然更大。所以只需考虑 $\{a_i,\dots,a_j\}$ 与 $\{a_{i+1},\dots,a_{j+1}\}$.  
由引理易得只需要考虑 $\{a_i,a_{i+1}\},1\leq i<n$, 枚举即可。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
long long ans,a[200005];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        ans=0;
        scanf("%lld",&a[1]);
        for(int i=2;i<=n;++i){
            scanf("%lld",&a[i]);
            ans=max(ans,a[i]*a[i-1]);
        } 
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：black_trees (赞：0)

题目大意：
问你一个序列的所有长度不小于 $2$ 的子区间的最大值和最小值**乘积的最大值**。

从数据范围就能发现，一定是个 $\text{O}(T\times n)$ 的算法。

所以想到了单调队列或者单调栈维护。

但是仔细想想，这个子区间的长度只能为 $2$。

为何？

我们就先从长度为 $2$ 的区间开始考虑。

那么很明显权值就是 $a[l] \times a[r]$ 。

考虑一个长度为 $3$ 的区间，且里面的元素是 $\{a,b,c\}$ （按顺序）。

+ 假设 $b$ 是最大的，那么它就会和 $\min(a,c)$ 结合，那么就和长度为 $2$ 的没有任何区别。

+ 假设 $a$ 是最大的，那么有如下两种情况。

	1. $b$ 比 $c$ 小，那么这个区间的权值一定是 $a \times b$ ，转化成了长度为 $2$ 的情况。
    2. $b$ 比 $c$ 大，那么这个区间的权值就是 $a \times c$ ，但是很明显， $a\times b $ 也就是长度为  $2$ 的时候绝对比这个 $a\times c$ 更优（因为我们最终要求的是最大值）

反过来同理，然后把这个结论扩展到 $n=4,5,6...$ 就能证明结论正确。

所以现在只需要读入的时候让相邻的元素两两相乘，求乘积的最大值，这个最大值就是答案。

---

## 作者：Doubeecat (赞：0)

> 给定一个长度为 $n$ 的序列，找到最大的 $\max(a_l, a_{l + 1}, \ldots, a_r) \cdot \min(a_l, a_{l + 1}, \ldots, a_r)$ $(1 \le l < r \le n)$
>
> $n \leq 3 \times 10^5$​

## 思路

贪心。

实际上我们并不需要查询所有子序列，我们考虑一个数 $a_{j+1}$ 加入到 $a_i,a_{i+1},\dots,a_j$ 里时发生的变化。

若 $a_{j+1} \leq \max(a_i, a_{i + 1}, \ldots, a_j)$ 时，答案不会变得更优秀。因为当 $a_{j+1} < \min(a_i, a_{i + 1}, \ldots, a_j)$ 时，会让答案变得更差，其他情况也不会让答案变得更好。

所以实际上当且仅当 $a_{j+1} > \max(a_i, a_{i + 1}, \ldots, a_j)$ 时，才对我们的答案有贡献。

但是如果仅仅是这一点的话，远不用我们考虑所有子序列，我们只需要考虑一部分更小的子序列即可。

证明：若 $a_{j+1} > \max(a_i, a_{i + 1}, \ldots, a_j)$ 且 $a_i \not= \min(a_i, a_{i + 1}, \ldots, a_j)$，实际上是与子序列 $a_{i+1},\dots,a_{j-1}$ ​的答案相同的。

所以，我们实际上并不需要查找所有长度 $>2$ 的子序列，我们对于每个 $a_i$ 与 $a_{i+1}$ 暴力算一遍最大值即可。

时间复杂度 $O(n)$

## Code

```cpp
void solve() {
    int n;read(n);
    ll las;read(las);
    ll ans = 0;
    for (int i = 1;i < n;++i) {
        ll x;read(x);
        ans = max(x * las,ans);
        las = x;
    }
    printf("%lld\n",ans);
}
```

# 

---

## 作者：BF_AlphaShoot (赞：0)

是一道有显然的**贪心**策略的题，建议难度评为**普及-**。

简化题意，即为求 $\max(a_l,a_{l+1},\cdots,a_r)\times\min(a_l,a_{l+1},\cdots,a_r)$。

不妨从特殊的 $a_i$​​​ 考虑。如果 $a_i$​ 就是最大值，那么 $a_{i+1}\geqslant\min(a_l,a_{l+1},\cdots,a_r)$​​​​​​​​​​，则删去其余所有元素对结果不会有更劣的影响，$a_{i+1}$​​ 为最大值时同理。

如果最小值在 $a_i$​​​ 或 $a_{i+1}$​​ 处取得，最大值在 $a_{i+2}$​​ 取得，那么我们在考虑 $a_{i+1}$​ 与 $a_{i+2}$​ 这个情况的时候不会对答案有更劣影响。

所以逐步比较 $\max(a_i\times a_{i+1})\times\min(a_i\times a_{i+1})$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define ri register int
#define il inline

const int INF=0x7fffffff,N=1e5+10;
int T,n,ans;
int a[N];

il ll read(){
    ll x=0,y=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}

signed main(){
    T=read();
    while(T--){
        n=read();
        ans=-INF;
        for(ri i=1;i<=n;i++){
            a[i]=read();
            ans=max(ans,a[i]*a[i-1]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```



---

