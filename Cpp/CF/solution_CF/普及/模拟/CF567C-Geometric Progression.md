# Geometric Progression

## 题目描述

Polycarp 只有三岁，他只喜欢长度为 $3$ 的序列。他还有一个最喜欢的整数 $k$ 和一个序列 $a$，$a$ 是由 $n$ 个整数组成的。

他想知道从 $a$ 中可以选择多少个长度为 $3$ 的子序列，使得这个子序列形成一个公比 $k$ 的几何级数。

长度为 $3$ 的子序列是指在序列中找到 $3$ 个元素。如果这 $3$ 个元素的下标依次为 $i_1,i_2,i_3$，那么需要满足 $1 \le i_1 < i_2 < i_3 \le n $。也就是说，这些元素在序列中不一定连续，但它们的下标应当是递增的。

公比 $k$ 的几何级数形式为 $b \times k^0,b \times k^1,\cdots,b \times k^{r-1}$。

## 样例 #1

### 输入

```
5 2
1 1 2 2 4
```

### 输出

```
4```

## 样例 #2

### 输入

```
3 1
1 1 1
```

### 输出

```
1```

## 样例 #3

### 输入

```
10 3
1 2 6 2 3 6 9 18 3 9
```

### 输出

```
6```

# 题解

## 作者：wanggk (赞：6)

[CF567C 题目](https://www.luogu.com.cn/problem/CF567C)

### 题意简化：
~~没看题的回去看题~~ 有一个长度为 $n$ 的数组，选取长度为三，公比为 $k$ 的子序列，求方案数。

方法一：暴力dp（TLE）
-

一个求方案数的动态规划。

状态： $dp[i][j]$ 表示 $a[j]$ 作为子序列第 $i$ 项是的方案数（$1≤i≤3$，$1≤j≤n$ ）.

初值：`dp[1][i]=1;` 即当 $a[i]$ 作为子序列第一项时，方案数为 $1$.

转移：`if(a[k]*kk==a[j]) dp[i][j]+=dp[i-1][k];` 其中 $i$ 指 $a[j]$ 作子序列的第 $i$ 项，$kk$ 是公比，枚举 $j$ 即枚举前一个数。

终值：`ans+=dp[3][i];`

这个代码呢，第七个点就T了：

```
#include<iostream>
#include<cstdio>
using namespace std;
int n,kk;
int ans=0;
int a[200005];
int dp[5][200005];
int main()
{
	scanf("%d%d",&n,&kk);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) dp[1][i]=1;
    for(int i=2;i<=3;i++)
		for(int j=i;j<=n;j++)
			for(int k=i-1;k<j;k++)
				if(a[k]*kk==a[j])
					dp[i][j]+=dp[i-1][k];
	for(int i=3;i<=n;i++) ans+=dp[3][i];
	printf("%d\n",ans);
	return 0;
}
```

方法二：加map（AC）
------
核心思想还是和前一个方法一样的。

之前TLE了，寻求 $O(n)$ 的做法 ~~，在瞄了几秒题解之后~~，原来可以用map一维做。

其实这里还是 $dp$ ,只不过 $dp[i]$ 中的 $i$ 存的是数值。那么至于为什么要用map，取决于恶心的数据范围，映射可以解决下标问题。

还有就是要开 $ll$ ，否则辛辛苦苦写代码却仍然会WA。

也可以参考楼下2019年的那篇题解，更清晰些。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#define int long long
using namespace std;
int n,kk;
int ans=0;
int a[200005];
map<int,int> dp,dp2;
signed main()
{
	scanf("%lld%lld",&n,&kk);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
    {
		dp2[a[i]]++;
    	if(a[i]%kk==0)
    	{
    		ans+=dp[a[i]/kk];
    		dp[a[i]]+=dp2[a[i]/kk];//一样的，用map的形式写转移方程
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

-----------------------

附上提交记录：

[https://cdn.luogu.com.cn/upload/image_hosting/4qdf0nvc.png](https://cdn.luogu.com.cn/upload/image_hosting/4qdf0nvc.png)

---

## 作者：VitrelosTia (赞：3)

upd 2022.10.28:修正 $\LaTeX$, 对于思路进行补充，感谢管理员大大的审核。

题链：[CF](https://codeforces.com/contest/567/problem/C)/[Luogu](https://www.luogu.com.cn/problem/CF567C)

### 题意
对于一个长度为 $n$ 的数列 $a$，找出 $a$ 中有多少个递增的三元组 $(i,j,k)$ 能使 $a_i$, $a_j$, $a_k$ 组成一个公比为 $q$ 的等比数列。

### 思路

#### 枚举第二项，使用两个map记录等比数列中的第一项和第三项。

从数列的第二个数开始查找，将查找的数当做等比数列的中项，前面的数存进 $mp1$, 后面的数存进 $mp2$，并每次询问 查询的数是否是 $q$ 的倍数，$mp1$ 中是否存有 $a \div q$， $mp2$ 中是否存有 $a \times q$, 假如有，那么将答案加上 $mp1$ 中 $a \div q$ 的数量乘 $mp2$ 中 $a \times q$ 的个数（乘法原理）。

这种做法只要把数列查询一遍即可，时间复杂度 $O(n)$。

### code

```
#include<bits/stdc++.h>
using namespace std;
#define LL long long
map<LL,LL> mp1,mp2;
LL n,q,a[200005],cnt;
int main(){
    scanf("%lld%lld",&n,&q);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
    }
    mp1[a[1]]=1;//前面的数的数量存进mp1
    for(int i=3;i<=n;i++){
    	mp2[a[i]]++;//后面的数的数量存进mp2
    }
	for(int i=2;i<=n;i++){//开始查找
		if(a[i]%q==0&&mp1.count(a[i]/q)&&mp2.count(a[i]*q)){//如果满足等比数列
			cnt+=1ll*mp1[a[i]/q]*mp2[a[i]*q];//结果加上所有一样的等比数列的数量
		}
		mp1[a[i]]++;mp2[a[i+1]]--;//位置后移一位
	}
	cout<<cnt;
}
```




---

## 作者：nb_jzy (赞：1)

#### 想法
如果确定第一个数的编号 $i$，我们需要维护出 $i+1$ 至 $n$ 有多少个 $a_j = a_i\times k$ 多少个 $a_z = a_i\times k^2$ 但是，我们无法确定 $z$ 是否大于 $j$，所以不能满足正确性。若确定后一个数的编号 $z$ 则同理。

#### 思路
不难想到，如果确定中间的数的编号 $j$，那么我们只需要在 $j$ 的前面找到有多少个满足条件的 $a_i$ 以及在 $j$ 的后面有多少个 $a_z$ 满足条件，因为满足 $i<j<z$，所以选当前 $j$ 的方案数即为 $a_i$ 的个数与 $a_z$ 的个数相乘。

#### 代码实现
看到很多人统计 $j$ 前面 $a_i$ 的个数和后面 $a_z$ 的个数使用 `map`，但是，如果不会使用 STL，也是可以实现的，由于 $a_i$ 范围过大，我们没法开数组直接统计，但是，$n$ 的范围只有 $2\times 10^5$，意味着只会出现 $n$ 个不同的值，我们可以将这 $n$ 个值编一个号，便可以实现了。

其实，就是**离散化**！

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
int n,id[maxn];
long long k,a[maxn],c[maxn],d[maxn],x[maxn],ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],x[i]=a[i];
	sort(x+1,x+n+1);
	int len=unique(x+1,x+n+1)-x-1;
	for(int i=1;i<=n;i++){
		id[i]=lower_bound(x+1,x+len+1,a[i])-x;
	}
	c[id[1]]++;
	for(int i=2;i<=n;i++){
		d[id[i]]++;
	}
	for(int i=2;i<n;i++){
		d[id[i]]--;
		if(a[i]%k==0){
			int l=lower_bound(x+1,x+len+1,a[i]/k)-x;
			int r=lower_bound(x+1,x+len+1,a[i]*k)-x;
			if(x[l]==a[i]/k&&x[r]==a[i]*k){
				ans+=c[l]*d[r];
			}
		}
		c[id[i]]++;
	}
	cout<<ans<<endl;
	return 0;
}
```

其实，这种写法比 `map` 要快一些，虽然时间复杂度都为 $O(n\log n)$，但 STL 的常数较大，将代码中的 `lower_bound` 手写二分，还会更快。

---

## 作者：RioFutaba (赞：0)

# 思路

考虑使用一种简单粗暴的 dp。

设 $f(i,j,x)$ 表示 $a$ 中前 $i$ 个数，以 $x$ 作为子序列第 $j$ 个数的方案数。$j \in \{ 1,2,3 \}$。

当 $j=1$ 时，$f(i,j,x)=f(i-1,j,x)$。

当 $j>1$ 且 $k \mid x$ 时，$f(i,j,x)=f(i-1,j-1,\frac{x}{k})$。

最终的答案为 $\displaystyle \sum_{i=1}^n f(n,3,a_i)$。

因为只需要用到 $i-1$，所以 $i$ 这一维可以优化掉。

答案最大是 ${{200000} \choose {3}}=1333313333400000$，需要开 long long。并且 $a_i \le 10^9$，$f$ 数组要用 map。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long 
const int maxn=2e5+5;
int n,k,a[maxn];
map<int,int> cnt[4];
int ans;
signed main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		if(a[i]%k==0){
			cnt[3][a[i]]+=cnt[2][a[i]/k];
			cnt[2][a[i]]+=cnt[1][a[i]/k];
		}
		cnt[1][a[i]]++;
	}
	map<int,int>::iterator it;
	for(it=cnt[3].begin();it!=cnt[3].end();it++)
		ans+=(*it).second;//记过答案的都加一遍 map可以避免重复加同一个数
	cout << ans << endl;
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

从 $a$ 中选择长度为 $3$ 的子序列 $b_1,b_2,b_3$，那么显然有 $\frac{b2}{b1}=k,\frac{b_3}{b_2}=k$。

可以发现每一级都是有关系的（即 $k$ 倍），那也就说明可以用一个桶来统计每个阶级（此处 $a_i$ 范围较大，故用 ```map```），则每次答案取最上面层级除以 $k$ 所形成的中间层级的桶即可。

注意第一、二层级的桶需要同时更新。
#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,k,ans;
map<int,int>p1,p2;
signed main(){
	cin >> n >> k;
	for(int i=1;i<=n;++i){
		int x;cin >> x;
		if(x%k==0){
			ans+=p1[x/k];
			p1[x]+=p2[x/k];
		}
		p2[x]++;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Mirasycle (赞：0)

考虑第 $i$ 项 $a_i$，显然它可以作为所求序列第 $1$ 或 $2$ 或 $3$ 项。统计它作为每一项对于答案的贡献。设 $dp(i,j)$ 表示数 $j$ 作为序列的第 $i$ 项的时候的方案数。

1. 第一项，则有 $dp(1,j) \gets dp(1,j)+1$。

1. 第二项，此时需满足 $j \bmod k=0$，有 $dp(2,j) \gets dp(2,j)+dp(1,j)$。

1. 第三项，此时需满足 $j \bmod k=0$，有 $ans \gets ans+dp(2,j)$。

注意数字很大，所以可以用 map 保存。

---

## 作者：过氧化氢_syq0057 (赞：0)

好题。

本以为是 $dp$，结果是 $O(n)$ 线性小算法（可能带 log /yiw，但是快 /gz）。

题意就是求长度为 $3$ 且公比为 $q=k$ 的等比数列个数（有前后顺序）。

长度为 $3$ 的话可以发现打两个标记就行了。

然后直接就赢了。

由于 $a_i \in [-10^9,10^9]$，所以直接上 map。

### Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 100005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
ll n, k;
ll ans;
map<ll, ll> mp, t;
int main() {
	scanf("%lld%lld", &n, &k);
	ll a;
	for (int i=1; i<=n; i++) {
		scanf("%lld", &a);
		if (a % k == 0) {//出现级数
			ans += mp[a / k];//上一个级数也出现过，累加答案
			mp[a] += t[a / k];//此级数+上一个级数a/k
		}
		t[a]++;//出现过，标记
	}
	printf("%lld\n", ans);
	return 0;
}
```

感觉这种方法很强，很多题都适用，输入数据有顺序，输入的时候就直接统计出答案，很强。

完结散花 qaq

---

## 作者：MVP_Harry (赞：0)

第一篇题解感觉没讲什么实质性的东西，这里补充一下。首先，肯定考虑dp，对$i$来说，$l[i]$表示在$1 \le k \le (i - 1)$有多少$a[k] = a[i] / K.$相似地定义$r[i]$，只是改成右边有多少$a[i] = a[i] \cdot K.$ 朴素的做法肯定是$O(n^2)$的，因为无序所以也无法用```lower_bound```，此时便想到了```multiset```优化，正反各跑一遍。然后就T了。。。其实案例$O(nlogn)$是对的，但是估计常数太大，换成```map```便可以过。详细写法可以参考代码：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, m, n) for (ll i = m; i <= n; i++)
#define per(i, m, n) for (ll i = m; i >= n; i--) 

const ll maxn = 2e5 + 5;
ll a[maxn], Left[maxn], Right[maxn]; 
map<ll, ll> s; 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0); 
    ll N, K; 
	cin >> N >> K;
	rep(i, 1, N) cin >> a[i];
	rep(i, 1, N) {
		Left[i] = s[a[i]]; 
		if (!s.count(a[i] * K)) s[a[i] * K] = 1;
		else s[a[i] * K]++; 
	}
	s.clear(); 
	per(i, N, 1) {
		Right[i] = s[a[i] * K]; 
		if (!s.count(a[i])) s[a[i]] = 1;
		else s[a[i]]++; 
	}
	ll ans = 0; 
	rep(i, 1, N) {
		ans += (ll) Left[i] * Right[i]; 
	}
	cout << ans << "\n"; 
	return 0; 
}
```

---

## 作者：xiaozeyu (赞：0)

**这道题中是要将一些树连在一起，可以用map**

**关于map一些知识，我摘除出一些**

**可以看[C++STL之map（）](https://zhuanlan.zhihu.com/p/35667739)这篇文章**

1.为什么要学习map（）？

答：Map是STL的一个关联容器，

关联容器的优点是：它提供了对元素的快速访问。例如（最大匹配分词时，查字典效率更高）

map内部自建一颗红黑树(一 种非严格意义上的平衡二叉树)，这颗树具有对数据自动排序的功能，所以在map内部所有的数据都是有序的。

2.map的简介

map把值与键关联在一起，可以使用键来查找词。例如：键可以表示学号，而值 可以对应姓名。

3.map的使用

使用map得包含map类所在的头文件 #include <map> //注意，STL头文件没有扩展名.h

4.map的建立

map<int, string> t;

5.map数据插入：

t[int]=字符串）（map内部对[]进行了重载）

6.map的大小

Int nSize = mapStudent.size();

7.数据的遍历

先定义一个迭代器（广义指针）：

map<int,string>::iterator iter;

然后输出map的键和值。

iter->first 值的是键，

iter->second指的是值。
  
上代码

------------

  

------------


```c
#include<iostream>
#include<map>//别忘了
using namespace std;
long long n,ans,k,a,b,i;
map <long long, long long> m,m1;//定义
int main ()
{
	cin>>n>>k;//输入
	for(i=0;i<n;i++)
	{
		cin>>a;
		if(a%k==0)//为级数
		{
			ans=ans+m[a/k]; //加上总数
			m[a]=m[a]+m1[a/k];//计入
		}
		m1[a]++;//记录个数
	}
	cout<<ans;//输出
}
```


---

