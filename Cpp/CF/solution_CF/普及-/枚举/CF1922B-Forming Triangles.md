# Forming Triangles

## 题目描述

You have $ n $ sticks, numbered from $ 1 $ to $ n $ . The length of the $ i $ -th stick is $ 2^{a_i} $ .

You want to choose exactly $ 3 $ sticks out of the given $ n $ sticks, and form a non-degenerate triangle out of them, using the sticks as the sides of the triangle. A triangle is called non-degenerate if its area is strictly greater than $ 0 $ .

You have to calculate the number of ways to choose exactly $ 3 $ sticks so that a triangle can be formed out of them. Note that the order of choosing sticks does not matter (for example, choosing the $ 1 $ -st, $ 2 $ -nd and $ 4 $ -th stick is the same as choosing the $ 2 $ -nd, $ 4 $ -th and $ 1 $ -st stick).

## 说明/提示

In the first test case of the example, any three sticks out of the given $ 7 $ can be chosen.

In the second test case of the example, you can choose the $ 1 $ -st, $ 2 $ -nd and $ 4 $ -th stick, or the $ 1 $ -st, $ 3 $ -rd and $ 4 $ -th stick.

In the third test case of the example, you cannot form a triangle out of the given sticks with lengths $ 2 $ , $ 4 $ and $ 8 $ .

## 样例 #1

### 输入

```
4
7
1 1 1 1 1 1 1
4
3 2 1 3
3
1 2 3
1
1```

### 输出

```
35
2
0
0```

# 题解

## 作者：wanglexi (赞：4)

[题目传送门。](https://www.luogu.com.cn/problem/CF1922B)

### 翻译

你有 $n$ 根木棒，第 $i$ 根木棒的长度是 $2^{a_i}$。请问有多少种方案选出其中的 $3$ 根木棒，使其可以组成面积大于 $0$ 的三角形。

每个测试点里有 $T$ 组数据，每组数据先输入 $n$，再输入 $a_i$。

### 解法

假设第 $i,j,k(a_i\le a_j\le a_k)$ 根这三根木棒可以构成三角形，那么有：

$$2^{a_i}+2^{a_j}>2^{a_k}$$

$$2^{a_i}>2^{a_k}-2^{a_j}=(2^{a_j}\cdot2^{a_k-a_j})-2^{a_j}=2^{a_j}\cdot(2^{a_k-a_j}-1)$$

$$\because 2^{a_i}<2^{a_j}$$

$$\therefore (2^{a_k-a_j}-1)=0$$

$$\therefore a_j=a_k$$

所以问题就转换成了求有多少组**无序**三元组 $(i,j,k)$ 满足 $a_i\le a_j=a_k$，其中 $i,j,k$ 是 $1\sim n$ 的正整数且互不相同。

这个时候我们需要两个辅助数组 $cnt$ 和 $s$，$cnt_i$ 表示 $a$ 中 $i$ 的数量，$s_i=\sum_{j=0}^{i}cnt_j$。待会你会知道他们有什么用。

统计的三元组又可以分成两类：

1. $a_i=a_j=a_k$，那么答案就是各种 $a_i$ 分别选 $3$ 个的种类数之和，对于 $a_i$ 就是 $C_{cnt_{a_i}}^3$。因为 $0\le a_i \le n$，所以全加起来就是 $\sum_{i=0}^{n}C_{cnt_{a_i}}^3$

2. $a_i<a_j=a_k$，答案就是各种 $a_j$ 分别选两个在乘上可能的 $a_i$ 种类数之和。全加起来就是 $\sum_{i=1}^n(C_{cnt_{a_i}}^2\cdot s_{i-1})$。

### AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,a[300005];
ll cnt[300005],s[300005],ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		for(int i=0;i<=n;i++)cnt[i]=s[i]=0;
		for(int i=1;i<=n;i++)cin>>a[i],cnt[a[i]]++;
		for(int i=0;i<=n;i++)ans+=cnt[i]*(cnt[i]-1)*(cnt[i]-2)/6,s[i]=(i==0?0:s[i-1])+cnt[i];
		for(int i=1;i<=n;i++)ans+=cnt[i]*(cnt[i]-1)/2*s[i-1];
		cout<<ans<<"\n";
	}
	return 0;
}
```

upd 2024.1.22 $T$ 组数据，每组都 memset，光赋值的次数就是 $Tn$ 次，会 TLE。所以得改用循环赋值，这样总复制次数就是 $\sum n$，不会超时。

---

## 作者：Jerry_heng (赞：3)

（一）

因为 $2^{n}+2^{n}=2^{n+1}$。

设取的三个数为 $2^i$，$2^j$，$2^k$，$i\le j \le k$。

因为 $2^i+2^j>2^k$，所以 $j=k$。（反证法易证）

此时 $i$ 任意取。

注意不要重复取。

将答案分为两类计算，$i=j=k$ 和 $i<j=k$。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,sum[300010],ans,s;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		ans=0,s=0;
		memset(sum,0,sizeof sum);
		for(int i=1;i<=n;i++){
			scanf("%lld",&x);
			sum[x]++;
		}
		for(int i=0;i<=n;i++){
			if(sum[i]>1)ans+=sum[i]*(sum[i]-1)/2*s;
			if(sum[i]>2)ans+=sum[i]*(sum[i]-1)*(sum[i]-2)/6;
			s+=sum[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
} 
```

---

## 作者：Eternity_Yoke (赞：1)

## 题目大意
有 $n$ 根木棒，第 $i$ 根木棒的长度为 $2^{a_i}$。

有多少种方案可以组成任意两边之和大于第三边的三角形。
## 解题思路
显然只有两种有效的组合满足题意，即三根长度相同的组合，以及两根长度相同和一根比前两根短的组合。

所以我们排序后寻找木棒长度相等的块，然后进行组合计算。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+5;
int t,n,j,k,cnt;
ll ans;
int a[N],f[N][2];
ll C(int x,int y)
{	ll sum=1;
	for(int i=1;i<=y;i++)
	sum=sum*(x-y+i)/i;
	return sum;
}
int main()
{	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{	cin>>n;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		sort(a+1,a+n+1);
		cnt=1;ans=0;
		for(int i=1;i<=n;i++)f[i][0]=1,f[i][1]=0;
		for(int i=1;i<=n-1;i++)
		{	if(a[i]!=a[i+1])
			cnt++;
			else f[cnt][0]++;//区块长度相同的个数
		}
		for(int i=1;i<=cnt;i++)
		{	f[i][1]+=f[i-1][1]+f[i-1][0];//比区块i中长度小的个数
			if(i==1)
			{	if(f[i][0]<3)continue;
				else ans+=C(f[i][0],3);
			}
			else 
			{	if(f[i][0]>=3)
				ans+=C(f[i][0],3);//第一种方案
				ans+=1ll*f[i][1]*C(f[i][0],2);//第二种方案
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Crazyouth (赞：1)

## 分析

注意到 $2^0+2^1<2^2$，因此若 $a_i\ne a_j\ne a_k$，这组数就是不合法的，所以题目转化为有多少对三元组 $i,j,k$ 使得 $a_i,a_j,a_k$ 中至少有两个数相等。考虑分类讨论。

第一类，$a_i,a_j,a_k$ 中有两个数相等，不妨设 $a_i=a_j$，那么先开一个 map 维护所有 $a_i$ 的出现次数，即 $mp_i$ 表示 $i$ 在 $a$ 中出现次数。则对于每一个 $mp_i>1$，它对第一类答案的贡献为 $C_{mp_i}^2\times (n-mp_i)$，也就是从 $mp_i$ 个数里面选择 $2$ 个数，再从剩下的数里选择 $1$ 个。

第二类，$a_i=a_j=a_k$，那么不难想到贡献是 $C_{mp_i}^3$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[300010];
map<int,int> mp;
set<int> st;
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		mp.clear();
		st.clear();
		int n,ans=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],mp[a[i]]++,st.insert(a[i]);
		int tp=0;
		for(auto i:st)
		{
			if(mp[i]<2)
			{
				tp+=mp[i];
				continue;
			}
			if(mp[i]==2) ans+=mp[i]*(mp[i]-1)/2*tp;
			else ans+=mp[i]*(mp[i]-1)/2*tp+mp[i]*(mp[i]-1)*(mp[i]-2)/6;
			tp+=mp[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}

---

## 作者：Pyrf_uqcat (赞：1)

### 题意
多组数据，现在有 $n$ 根木棒，告诉你每根木棒长度 $2^{ai}$，求组成的最大三角形面积。
### 思路
首先要知道，一个三角形最长的边长要大于其他两条长度和。我们设三角形的边长分别为 $x,y,z$（$x \ge y \ge z$），则 $x>y+z$。但是 $x,y,z$ 都是 $2$ 的乘方，我们会发现一个问题：当 $x,y,z$ 各不相同时，$y+z$ 根本不可能大于 $x$。举个例子，当 $x=4,y=2,z=1$ 时，$x$ 是大于 $y+z$ 的。那如果 $x,y,z$ 更大呢？可以自己计算一下，会发现差更大了。那就说明，$x,y,z$ 不可能都相同，也就是 $x=y \ne z$ 或 $x=z \ne y$ 或 $x=y=z$。说明白些，就是 $x,y,z$ 三条边中，至少会有两条边相同。那不妨**分类讨论**一番。

我们可以发现两种情况，如果只有两条边相同，那么找到这两个长度一样的木棒，在剩余木棒中选择一个**小于这两根木棒的长度且最大**的木棒。如果三条边都相同，则记录这个等边三角形的面积。
### 代码
在输入木棒长度时，以一个数组记录每个长度出现的次数。紧接着，依次遍历下去，如果数组中记录了两次及以上，记录答案。最后输出答案最大值。
```cpp
输入T
while(T--){
	定义cnt数组，ans=0
	memset(cnt,0,sizeof(cnt))
	for（） {
		输入ai
		cnt[ai]++;
	}
	for（）{
		if（cnt[i]>=2） {
			if(是2) {
				找第三条边
				记录答案
			}
			else {
				记录答案
			}
			ans=max（ans，这轮的答案）
		}
	}
	输出ans换行
}
```

---

## 作者：Vct14 (赞：0)

因为 $2^i+2^j\leqslant2^s+2^{s+1}<2\times2^{s+1}=2^{s+2}$（其中 $i<j\leqslant s+1$），所以选择的三根木棍必须至少有两根是相同的。

1. 恰好有两根长度相等，从当前长度的木棍中选出两根，然后再从其他木棍中选出一根。但是这一根的长度必须小于其余两根的长度，否则因为 $2^i+2^i\leqslant 2\times2^s=2^{s+1}$（其中 $i\leqslant s$）无法构成三角形。设比当前长度的木棍短的木棍共有 $s$ 根，当前长度的木棍有 $c$ 根，则可以构成 $C_c^2\times C_s^1=\frac{sc(c-1)}{2}$ 个三角形。
2. 三根长度都相等。从当前长度的木棍中选出三根即可，可以构成 $C_c^3=\frac{c(c-1)(c-2)}{6}$ 个三角形。

可以用一个桶或者是 `map` 存储每种木板长度出现的次数，下面的代码用的是桶。


```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define c b[i]

int b[300002];

signed main(){
	int t;cin>>t;
    while(t--){
        int n,a;cin>>n;
        memset(b,0,sizeof(b));
        for(int i=1; i<=n; i++){
            cin>>a;
            b[a]++;
        }
        int s=0,ans=0;
        for(int i=0; i<=n; i++){
            ans+=s*c*(c-1)/2+c*(c-1)*(c-2)/6;
            s+=c;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路

显然，有以下两种选择的方法：
- 所有边一样长；
- 两条一样长的边，第三条边小于这两条边。

然后组合数计算即可。

### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include <vector>
#define ll long long
#define N 300005
int n,a[N];
inline ll C3(ll x){
    if(x<3) return 0ll;
    return x*(x-1)*(x-2)/6ll;
}
inline ll C2(ll x){
    if(x<2) return 0ll;
    return x*(x-1)/2ll;
}
inline void work(){
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    std::sort(a+1,a+n+1);
    std::vector<int> cnt(n+1,0);
    for(register int i=1;i<=n;++i)
        ++cnt[a[i]];
    ll ans=0,res=n;
    for(register int i=n;i>=0;--i){
        res-=cnt[i];
        ans+=C3(cnt[i]);
        ans+=C2(cnt[i])*res;
    }printf("%lld\n",ans);
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```

---

## 作者：FeiDing (赞：0)

# 思路

在不考虑能否构成三角形的情况下，三角形有这几种情况：

1. 三条边的长度各不相等；
2. 等腰，其中腰比底长；
3. 等腰，其中底比腰长；
4. 等边三角形。

题目中木棍的长度都是 $2$ 的幂，我们再对上述几种情况作进一步分析：

1. 无法构成三角形。为了构成三角形，我们要让较短的 $2$ 条木棍尽量长，则三个木棍的长度为 $2^x,2^{x+1},2^{x+2}$，明显构不成三角形。
2. 很明显可以构成三角形。
3. 无法构成三角形。两条腰长度之和最大也只能等于底。
4. 很明显可以构成三角形。

---

# 实现

经分析只有下面 $2$ 种三角形：

1. 等腰，其中腰比底长；
2. 等边三角形。

于是这么做：

首先桶排，因为 $a_i \le n$，所以可以桶排。

设长度为 $2^x$ 的木棍有 $b_x$ 根，则上述两种三角形的方案数分别为：

1. $\Large\sum_{x=1}^n (C^2_{b_x}\times \sum_{i=1}^{x-1} b_x)$
2. $\Large\sum_{x=1}^n (C^3_{b_x})$

---

code:

```
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long

using namespace std;

int t,n,ans;
int a[300002],b[300002],c[300002];

//a 是每个木棍的长度
//b 是桶
//c 是 b 的前缀和

signed main(){
	cin>>t;
	while(t--){
		ans=0;
		memset(b,0,sizeof(b));
		cin>>n;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			++b[a[i]];
		}
		c[0]=b[0];
		for(int i=0;i<=n;++i){
			if(i>0)
				c[i]=c[i-1]+b[i];
			if(b[i]>=2&&i>0)
				ans+=b[i]*(b[i]-1)/2*c[i-1];//1 类三角形的方案数
			if(b[i]>=3)
				ans+=b[i]*(b[i]-1)*(b[i]-2)/6;//2 类三角形的方案数
		}
		cout<<ans<<endl;
	}
}
```


---

## 作者：indream (赞：0)

## CF1922B Forming Triangles 题解
[Luogu](https://www.luogu.com.cn/problem/CF1922B) | [CF](http://codeforces.com/problemset/problem/1922/B) | [AC](https://codeforces.com/contest/1922/submission/242328394)

### 思路

显然，$2^i+2^j\le2^k(i,j<k)$，所以任意一个三角形必定是等腰的。

注意到 $a_i\le3\times10^5$，显然是开桶存数据。

接下来遍历整个桶，设 $cnt_i$ 表示有多少个数满足 $a_i=i$，$sum$ 为比 $i$ 小的数的数量。

经过推算，总个数为：
$$
\begin{aligned}
ans &=\sum_{i=0}^n{sum \times C_{cnt_i}^2+C_{cnt_i}^3}\\
    &=\sum_{i=0}^n{sum\times\frac{cnt_i(cnt_i-1)}{2}+\frac{cnt_i(cnt_i-1)(cnt_i-2)}{6}}
\end{aligned}
$$

---

注意：

- 不用特判 $n<3$ 的情况，至少我的代码判了在 $T\ne1$ 时会错（WA）。（我也不知道错哪了）
- 注意多测清空。
- 需要开 `long long`。

### 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 300005
using namespace std;
typedef long long ll;
ll n,t,tmp,sum,ans;
int cnt[MAXN];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>t;
    while(t--){
        sum=0;ans=0;
        cin>>n;
        for(int i=0;i<=n;++i)
            cnt[i]=0;
        for(int i=0;i<n;++i){
            cin>>tmp;
            ++cnt[tmp];
        }
        for(int i=0;i<=n;++i){
            ll t=cnt[i];
            ans+=t*(t-1)/2*sum;
            ans+=t*(t-1)*(t-2)/6;
            sum+=cnt[i];
            //cerr<<ans<<' '<<sum<<' '<<t<<'\n';
        }
        cout<<ans<<'\n';
    }
    return 0;
}

```

---

