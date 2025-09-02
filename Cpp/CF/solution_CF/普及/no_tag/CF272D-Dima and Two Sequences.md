# Dima and Two Sequences

## 题目描述

Little Dima has two sequences of points with integer coordinates: sequence $ (a_{1},1),(a_{2},2),...,(a_{n},n) $ and sequence $ (b_{1},1),(b_{2},2),...,(b_{n},n) $ .

Now Dima wants to count the number of distinct sequences of points of length $ 2·n $ that can be assembled from these sequences, such that the $ x $ -coordinates of points in the assembled sequence will not decrease. Help him with that. Note that each element of the initial sequences should be used exactly once in the assembled sequence.

Dima considers two assembled sequences $ (p_{1},q_{1}),(p_{2},q_{2}),...,(p_{2·n},q_{2·n}) $ and $ (x_{1},y_{1}),(x_{2},y_{2}),...,(x_{2·n},y_{2·n}) $ distinct, if there is such $ i $ $ (1<=i<=2·n) $ , that $ (p_{i},q_{i})≠(x_{i},y_{i}) $ .

As the answer can be rather large, print the remainder from dividing the answer by number $ m $ .

## 说明/提示

In the first sample you can get only one sequence: $ (1,1),(2,1) $ .

In the second sample you can get such sequences : $ (1,1),(2,2),(2,1),(3,2) $ ; $ (1,1),(2,1),(2,2),(3,2) $ . Thus, the answer is $ 2 $ .

## 样例 #1

### 输入

```
1
1
2
7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 2
2 3
11
```

### 输出

```
2
```

# 题解

## 作者：Allanljx (赞：1)

## 思路
设 $mp_i$ 表示对于 $x=i$ 时有多少个相同的 $x$，设 $f_i$ 表示对于 $x=i$ 有多少对相同的 $y$，令 $sum$ 表示所有 $f_i$ 的和。答案就是所有 $mp_i$ 的阶乘的乘积除以 $2^{sum}$。因为所有 $x$ 相同的点顺序都可以进行任意的排序，但是一旦有相等的话他们两个的顺序就不重要了。但是除以二不能用逆元，所以要在求阶乘的同时除以二。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int mod;
int n,ans=1;
int a[100005],b[100005];
map<int,int> mp,mp1,f;
int get_sum(int maxn,int cnt)//cnt表示要除以几个2
{
	int sum=1;
	for(int i=1;i<=maxn;i++)//求阶乘
	{
		if(i%2==0&&cnt) sum=sum*i/2%mod,cnt--;
		else sum=sum*i%mod;
	}
	return sum;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	cin>>mod;
	for(int i=1;i<=n;i++)
	{
		mp[a[i]]++,mp[b[i]]++;//记录有多少个相同的x
		if(b[i]==a[i]) f[a[i]]++;//记录x，y都相等的点有多少组
	}
	for(int i=1;i<=n;i++)
	{
		if(!mp1[a[i]])//没有被统计过
		{
			ans=ans*get_sum(mp[a[i]],f[a[i]]);//
			ans%=mod;
			mp1[a[i]]=1;
		}
		if(!mp1[b[i]])
		{
			ans=ans*get_sum(mp[b[i]],f[b[i]]);
			ans%=mod;
			mp1[b[i]]=1;
		}
	}
	cout<<ans<<endl;
}
```


---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF272D)

## 思路
有两个整数坐标点的序列，你的任务是将两个序列合并为一个长度为 $2n$ 的不同点序列的数量，使得组装的序列中的点的 $x$ 坐标不递减。帮助他完成这个任务。请注意，初始序列的每个元素在组装的序列中应该恰好使用一次。\
我们利用 map 来存储。因为在 C++ 中，map 是一种关联容器，它存储的元素是键值对，其中每个键都是唯一的，并且每个键都映射到其值。map 通常用于需要快速查找、插入和删除键值对的情况，所以非常适合这道题。

## code
```cpp
for(a=1;a<=n;a++)
{
    if(!m[s[a]])z*=f(p[s[a]],f[s[a]])%=mod,m[s[a]]=1;
    if(!m[t[a]])m*=f(p[t[a]],f[t[a]])%=mod,m[t[a]]=1;
}
```

---

## 作者：QWQ_123 (赞：0)

显然数个的数就是在 $x$ 相同的数的排列数。

然后由于有可能 $x$ 相同并且 $y$ 也相同，所以就是可重集排列。

然后就是设有 $k$ 个 $x$ 相同的数，并且有 $c$ 个 $y$ 也相同，那么方案数就是 $\frac{k!}{2^c}$，又因为 $k\ge2c$，所以 $k$ 中至少有 $c$ 个偶数，所以直接在求阶乘时遇到偶数除二再乘即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int long long

int n, m;
ll ans = 1;
pair<int, int> a[200010];

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i].first), a[i].second = i;
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i + n].first), a[i + n].second = i;

	scanf("%lld", &m);

	sort(a + 1, a + 1 + 2 * n);

	for (int i = 1; i <= 2 * n; ++i) {
		int cnt = 1, cc = 0;
		while (a[i + 1].first == a[i].first && i + 1 <= 2 * n) {
			if (a[i].second == a[i + 1].second) ++cc;
			++cnt;
			++i;
		}

		for (int j = 1; j <= cnt; ++j) {
			if (!(j & 1) && cc) {
				int t = j;
				while (t % 2 == 0 && cc) {
					t /= 2ll;
					--cc;
				}

				ans = ans * t % m;
			} else {
				ans = ans * j % m;
			}
		}
	}

	printf("%lld\n", ans);

	return 0;
}
```

---

