# Yet Another Problem About Pairs Satisfying an Inequality

## 题目描述

# Yet Another Problem About Pairs Satisfying an Inequality


给你一个序列$ a_1, a_2, \dots a_n $ 。请计算出满足下面条件的 $(i,j) (1 \leq i, j \leq n) $个数 。

-  $ a_i < i < a_j < j $ .

## 说明/提示

对于第一组测试数据，满足条件的 $ (i, j) $ = $ \{(2, 4), (2, 8), (3, 8)\} $ .

- $ (2, 4) $ 满足条件是因为 $ a_2 = 1 $ , $ a_4 = 3 $ 且$ 1 < 2 < 3 < 4 $ .
-  $ (2, 8) $ 满足条件是因为$ a_2 = 1 $ , $ a_8 = 4 $ 且 $ 1 < 2 < 4 < 8 $ .
-  $ (3, 8) $ 满足条件是因为$ a_3 = 2 $ , $ a_8 = 4 $ 且 $ 2 < 3 < 4 < 8 $ .

## 样例 #1

### 输入

```
5
8
1 1 2 3 8 2 1 4
2
1 2
10
0 2 1 6 3 4 1 2 8 3
2
1 1000000000
3
0 1000000000 2```

### 输出

```
3
0
10
0
1```

# 题解

## 作者：lizhous (赞：10)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1703F)  
[本家传送门](https://codeforces.com/contest/1703/problem/F)
# 分析
### 朴素的算法
对于每个 $i(1 \le i \le n)$，如果 $a_i<i$，我们可以从 $i$ 往后寻找合适的 $j$ 使得 $a_j>i$，累加答案即可。时间复杂度 $O(n^2)$，显然超时了。
### 优化算法
枚举 $i$ 是必然的，所以我们考虑压缩寻找 $j$ 的过程。我们可以开一个记录数组 $cnt$，$cnt_i$ 表示 $i$ 以后有多少个 $j$ 满足要求。$cnt$ 满足单调性，因为显然在更后面的 $i$，满足条件的 $j$ 会更少，想到预处理。对于每个数 $k(1 \le k \le n,a_k<k)$，我们将 $cnt_{a_k}$ 增加 $1$ 来累积答案。这之前的任意 $i$ 寻找时都能找到当前 $k$，所以要使用后缀和。
# code
```
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<map>
#define int long long //记得开long long
using namespace std;
int t, n, a[200001], cnt[200001], ans;
char ch;
signed main() {
	scanf("%lld", &t);
	while (t--) {
		memset(cnt, 0, sizeof(cnt));
		ans = 0;
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[i] < i) {
				cnt[a[i]]++; //预处理
			}
		}
		for (int i = n; i >= 1; i--) {
			cnt[i] += cnt[i + 1]; //后缀和
		}
		for (int i = 1; i <= n; i++) {
			if (a[i] < i) {
				ans += cnt[i + 1]; //调用预处理数组
			}
		}
		cout << ans << endl; //输出答案
	}
}

```

---

## 作者：mcqueen (赞：4)

**一步一步来**

我们先观察到题目的要求 $a_i<i<a_j<j$

首先很容易就会想到暴力的 $O(n^2)$ 做法，枚举 $i,j$ 判断可行的个数。

对这个暴力稍微优化一下那就是每次的 $j$ 都从 $i+1$ 开始枚举，当然这只能优化一些常数

考虑到数据范围 $n$ 在 $10^5$ 左右，所以可以考虑 $O(n)$ 或 $O(n \log n)$的做法

那么我们就要想办法把 $O(n^2)$ 的方法里优化掉一个循环

面对处理序列的问题，我们会尝试观察题目条件中的单调性来优化

那我们来观察一下：$a_i<i<a_j<j$

哎嘿，好像真的有单调性：如果我们枚举 $i$，那么 $i$ 就是单调递增的，随着 $i$ 的增大，满足条件的 $a_j$ 个数便越来越少了。

那我们拆分一下条件，先枚举 $j$ ，把所有满足 $a_j<j$ 的 $a_j$ 扔到一个数组 $b$ 里。然后对 $b$ 从小到大排序

记录 $b$ 的长度为 $m$ 

注意 $a,b$ 的下标都从 1 开始

然后我们留一个变量 $p$，$p$ 一开始等于 1

然后从1开始枚举 $i$

如果 $i$ 满足 $a_i<i$，我们就看看 $i$ 是否小于 $b_p$ ：

- 如果 $i<b_p$ ，那么 $b_p$ 到 $b_m$ 都满足大于 $i$ （因为数组 $b$ 已经排序过了），那么对于这个 $i$，他对答案的贡献就是 $m-p+1$。

- 否则，我们就让 `p++`，直到 $i<b_p$，注意判断边界条件。

读到这里，可能你就对这题大概有思路了。

而我们在实现的时候需要注意一些小细节：我们在编程的时候一般习惯让数组下标从 0 开始，而题目中的 $i,j$ 都是从1开始的。所以我们在写比较条件的时候可能就要写 `i+1`，`j+1` 而不是 `i`，`j`。

OK，思路就讲到这里。

（碎碎念）：笔者是退役 OIer，准大一新生，目前处于复建状态。看到其他题解里的树状数组，甚至二分，我都有些不太熟悉了，令人感慨。此外，受到学长推荐，最近我在自学 python，所以最近我都尝试用 python 写题目，但我 python 的代码风格不可避免的受到了 C++ 的影响，望海涵。

啊，时光荏苒……

#### Code:
```python
T = int(input())
while T:

    T -= 1
    n = int(input())
    a = list(map(int, input().split()))
    b = []
    cnt = 0
    ans = 0
    for i in range(n):
        if a[i] < i+1:
            b.append(a[i])
            cnt += 1
    b.sort()
    j = 0
    for i in range(n):
        if a[i] < i+1:
            while j < cnt and b[j] <= i+1:
                j += 1
            ans += cnt - j
    print(ans)

```





---

## 作者：linyuhuai (赞：4)

### 题目大意：

给定一个序列 $a$，求一共有多少种 $i,j(1\le i<j\le n)$，满足 $a_i<i<a_j<j$。

### 思路

本题一共有 $2$ 种做法可以通过，时间复杂度分别为 $\mathcal{O}(n\log n)$（[cf 官方题解](https://codeforces.com/blog/entry/104786)）和 $\mathcal{O}(n)$。~~像极了lg月赛部分用户提交吊打std。~~

$\mathcal{O}(n)$ 解法：

我们找到任意的 $j$ 满足 $a_j<j$，显而易见只需找到有多少个不同的 $i$ 满足 $a_i<i<a_j$ 加入答案更新即可。那么找出 $1\le i\le a_j-1$ 满足 $a_i<i$ 的数的数量。前缀和求出即可。
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],sum[200005];
void solve() {
	int n;
	scanf("%lld",&n);
	for(int i=1; i<=n; i++)sum[i]=0;
	for(int i=1; i<=n; i++)scanf("%lld",&a[i]);
	int ans=0;
	for(int i=1; i<=n; i++) {
		if(a[i]<i)sum[i]=sum[i-1]+1;
		else sum[i]=sum[i-1];
		if(a[i]>0&&a[i]<i)ans+=sum[a[i]-1];
	}
	printf("%lld\n",ans);
}

signed main() {
	int t;
	scanf("%lld",&t);
	while(t--)solve();
}
```


---

## 作者：zsseg (赞：3)

### 题意：
给定一个长为 $n$ 的序列 $a$，求其中满足 $a_i<i<a_j<j$ 的 $(i,j)$ 点对数量。

### 解答：

考虑对于 $a_i<i$ 进行处理，当我们读入一个 $a_i$ 时，若其小于 $i$，我们便将其标记。由于满足 $i<j$，我们可以向前扫一遍被标记的数，满足一个被标记的数的下标 $j<a_i$ 就将答案加一。

不难发现，对于一个 $a_i<i$，它的贡献就是 $1$ 到 $a_i-1$ 内被标记的数的数量。考虑使用前缀和优化，设前 $i$ 个数中满足 $a_i<i$ 的数量为 $s_i$，那么对于一个 $a_j<j$，其贡献就为 $s_{a_j-1}$。这样，便能在 $\mathcal{O}(n)$ 复杂度下解决本题。
### 代码：
```cpp
#include <bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<=b;i++)
#define ll long long
#define prf(i) printf("%lld\n",i)//记得开long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int t=read(),n;
ll ans,qzh[200010];//前缀和数组
int main(){
	while(t--){
		n=read();
		ans=0;
		f(i,1,n){
			int u=read();
			qzh[i]=qzh[i-1];//前缀和优化
			if(i>u)qzh[i]++,ans+=qzh[u-1];//如果a[i]<i,更新前缀和，并将答案加上s[ai-1]
		}
		prf(ans);
	}
	return 0;
}

```


---

## 作者：苏联小渣 (赞：2)

提供一个 $O(n \log n)$ 的无脑做法。

看到 $a_i <i<a_j<j$ 这个式子，很容易想到权值树状数组之类的东西。虽然这个式子是四元的，但我们可以把它化简成二元式。发现 $a_i<i$ 都是对于 $i$ 而言的，所以我们用一个数组 $f$，若 $a_i<i$ 即 $f_i=1$，反之亦然。这个时候我们只要枚举满足 $f_i=1,f_j=1,i<a_j,i<j$ 的 $(i,j)$。前面两个约束条件只要用个 if 判断即可；最后两个我们用权值树状数组维护。具体实现方式为，从 $n$ 到 $1$ 枚举，如果 $f_i=0$ 则跳过；否则，首先做一个前缀和，求出权值树状数组内大于 $i$ 的数的个数，然后，将 $a_i$ 放入权值树状数组内。实现方式和逆序对什么的类似。

然而 $0 \le a_i \le 10^9$，这启示我们要离散化。这题的离散化不太一般，因为我们要关注的是下标和权值的关系，而非一般的下标和下标、权值和权值的关系。然而下标的最大值为 $n$，所以，如果 $a_i \le n$，那么就令它离散化后的 rank 值为它本身；否则就让 rank 值从 $n$ 开始一个一个往上涨，具体实现可以看代码。然后我们就可以解决下标和权值的问题了。注意，这样离散化树状数组的大小要开两倍，虽然开一倍也能过。

注意要特判掉 $a_i=0$ 的情况。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, ans, cnt, a[200010], vis[200010], d[400010];
void add(int p, int x){
	for (; p<=cnt; p+=p&-p) d[p] += x;
}
int query(int p){
	int ret = 0;
	for (; p; p-=p&-p) ret += d[p];
	return ret;
}
map <int, int> mp;
map <int, int> :: iterator p;
signed main(){
	scanf ("%lld", &t);
	while (t --){
		mp.clear(); cnt = ans = 0;
		scanf ("%lld", &n);
		for (int i=1; i<=n; i++){
			scanf ("%lld", &a[i]);
			mp[a[i]] = 1;
			if (a[i] < i) vis[i] = 1;
			else vis[i] = 0;
		}
		cnt = n;
		for (p=mp.begin(); p!=mp.end(); p++){
			if (p->first <= n) mp[p->first] = p->first;
			else mp[p->first] = ++cnt;
		}
		for (int i=1; i<=cnt; i++){
			d[i] = 0;
		}
		for (int i=n; i>=1; i--){
			if (vis[i]) ans += query(cnt) - query(i);
			if (vis[i] && mp[a[i]]) add(mp[a[i]], 1);
		}
		printf ("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：xiaomuyun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1703F)

## 题目分析

如果两个数满足条件成对，两个数的值一定小于两个数的下标。所以我们可以用前缀和来记录 $1$ 到 $a_i$ 之间有多少个数满足上面的条件。

具体就是弄一个前缀和，$sum_i$ 表示每个数前面有多少个数满足 $a_i<i$，然后对于每个 $1\leq j\leq n$，如果 $a_j<j$，那就让答案增加正整数 $k<j$ 时所有满足 $a_k<k$ 的情况（即 $sum_{a_j-1}$），最后输出即可。

## 代码实现

```cpp
#include<algorithm>
#include<cstdio>
#define int long long
using namespace std;
const int maxn=2e5+1;
int t,n,a[maxn],sum[maxn],res=0;
signed main(){
	scanf("%lld",&t);
	while(t--){
		res=0;
		scanf("%lld",&n);
		sum[0]=0;
		for(int i=1;i<=n;++i){
			scanf("%lld",&a[i]);
			sum[i]=sum[i-1];
			if(a[i]<i) ++sum[i];//更新前缀和
		}
		for(int i=1;i<=n;++i){
			if(a[i]<i) res+=sum[a[i]-1];//更新答案
		}
		printf("%lld\n",res);
	}
	return 0;
}
```

---

## 作者：_Ad_Astra_ (赞：1)

我们可以先找出所有的 $a_{i_1},a_{i_2},\cdots,a_{i_m}$，使得对于每一个 $a_{i_j}$，都有 $a_{i_j}<i_j$。换句话说，就是找出所有满足 $a_i \lt i$ 的 $a_i$，记作 $b_1,b_2,\cdots,b_m$，同时记录 $id_1,id_2,\cdots,id_m$，也就是他们在 $a$ 中的下标。

那么我们相当于只要找出对于所有的 $i,j$，$id_i \lt b_j$ 的方案数即可。我们可以使用值域树状数组解决。由于 $1 \le a_i \le 10^9$，如果直接开长度为 $10^9$ 的树状数组会爆，所以还需要使用离散化。

时间复杂度 $O(n \log n)$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long 
int disc(int l,int r,int *a)
{
	sort(a+l,a+r+1);
	return unique(a+l,a+r+1)-a-l;
}//离散化 
int lowbit(int x)
{
	return x&(-x);
}
const int bit_maxn=2e5;
struct BIT
{
	int n,c[bit_maxn+10],mod;
	BIT(){}
	BIT(int _n,int _mod)
	{
		n=_n,mod=_mod;
		for(int i=1;i<=n;i++)c[i]=0;
	}
	int query(int x)
	{
		int ans=0;
		while(x>0)
		{
			ans+=c[x];
			if(mod)ans%=mod;
			x-=lowbit(x);
		}
		return ans;
	}
	void update(int x,int v)
	{
		while(x<=n)
		{
			c[x]+=v;
			if(mod)c[x]%=mod;
			x+=lowbit(x);
		}
	}
};//树状数组 

int n,a[200010],b[200010],id[200010],ans,m,a2[200010];
BIT bit;
void solve(int test_id)
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	m=ans=0;
	for(int i=1;i<=n;i++)if(a[i]<i){a[++m]=a[i];id[m]=i;}
	for(int i=1;i<=m;i++)a2[i]=a[i];
	int m2=disc(1,m,a2);
	bit=BIT(m2+1,0);
	for(int i=m;i>=1;i--)
	{
		int lb=upper_bound(a2+1,a2+m2+1,id[i])-a2;
		if(lb!=m2+1)lb--;
		ans+=m-i-bit.query(lb);
		lb=lower_bound(a2+1,a2+m2+1,a[i])-a2;
		bit.update(lb,1);
	}
	cout<<ans<<endl;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)solve(t);
	return 0;
}
```

---

## 作者：tzyt (赞：0)

题目链接[（CF](https://codeforces.com/problemset/problem/1703/F)，[洛谷）](https://www.luogu.com.cn/problem/CF1703F) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1703/)中观看。

## 思路（来源于官方题解）

观察题目中的不等式 $a_i < i < a_j < j$。可以发现，对于数组中的任意元素，只要不符合 $a_x < x$，那就绝对不会和任何的元素组成一个合法的数对。所以我们可以直接跳过不符合 $a_x < x$ 的元素。

我们可以把这个不等式拆成三个部分 $a_i < i, i < a_j$ 和 $a_j < j$。 

那对于所有符合 $a_x < x$ 的元素，第一个和最后一个不等式已经满足了，只要找到满足 $i < a_j$ 的元素，就可以构成一个合法数对了。

我们设 $a$ 去掉不满足 $a_x < x$ 的数组为 $b$ （听起来有点奇怪，但是 $b$ 中的每个元素的下标是跟 $a$ 一样的）。

比如我们说数组中的一个元素有值和下标两个属性，并且用 $(val, id)$ 这样的方式标记，那么如果 $a$ 数组是：

$$
a = (1, 1) \ (1, 2)\ (2, 3)\ (3, 4)\ (8, 5)\ (2, 6)\ (1, 7)\ (4, 8)
$$

去掉所有 $val \ge id$ 的，就能得到 $b$:
$$
b = (1, 2)\ (2, 3)\ (3, 4)\ (2, 6)\ (1, 7)\ (4, 8)
$$

那只要我们对于每个 $b_j$ 找到所有符合的 $i$，就可以解决本题。

其中不难发现 $i$ 是单调递增的，所以可以使用二分来找最大的，小于 $b_j$ 的 $i$。那么 $b$ 中所有 $id$ 小于 $i$ 的元素（以及 $i$ 自身）都可以跟 $a_j$ 构成一个合法数对。

除了二分法，我们还可以用树状数组来找到 $b$ 中所有 $id$ 小于一个特定值的元素的数量。

具体来说，我们可以用树状数组维护一个前缀和数组，然后遍历 $b$ 中的元素，每次都做 `upd(id)` 的操作。也就是使查询所有大于等于 $id$ 的数时，查到的值都增加 $1$。

这样，在树状数组中查询某个 $b_j - 1$ 的时候，就会返回比 $b_j$ 小的所有 $i$ 了。

当然，用差分的方法，也可以得到和树状数组相同的前缀和数组。而且本题不需要我们在得到这个前缀和数组后做别的更新，所以差分可以用 $\operatorname{O}(n)$ 的复杂度解决本题。

## 代码 

复杂度：$\operatorname{O}(n \log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
// author: ttzytt (ttzytt.com)
// ref: https://codeforces.com/blog/entry/104786
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin>>n;
        int a[n + 1];
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        ll ans = 0;
        vector<int> valid; // 前文所说的 b 数组，但是只储存了下标
                           // 因为我们只需要找最大的，小于 b_i 的下标 j
        for (int i = 1; i <= n; i++) {
            if (a[i] >= i) continue; // 不符合就直接跳过
            
            // 这里可能算是一个优化吧，可以发现 valid 中的下标 i 都是小于 j 的
            // 我们并没有把全部的 b 的下标都塞进 valid 中，因为 a[i] < i < a[j] < j
            // 所以只有 i < j 才可能符合。
            ans += (ll)(lower_bound(valid.begin(), valid.end(), a[i]) -
                        valid.begin());
            // lower_bound 会找到 valid 中第一个大于等于 a[i] 的元素。
            // 那么这个元素**之前**的全部是可用的。一个区间的长度为 r - l + 1
            // 因为只有这个元素之前的才是可用的，所以这个 1 我们就不加了
            valid.push_back(i);
        }
        cout << ans << '\n';
    }
}
```

---

