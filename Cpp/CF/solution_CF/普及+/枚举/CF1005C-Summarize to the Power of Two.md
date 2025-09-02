# Summarize to the Power of Two

## 题目描述

A sequence $ a_1, a_2, \dots, a_n $ is called good if, for each element $ a_i $ , there exists an element $ a_j $ ( $ i \ne j $ ) such that $ a_i+a_j $ is a power of two (that is, $ 2^d $ for some non-negative integer $ d $ ).

For example, the following sequences are good:

- $ [5, 3, 11] $ (for example, for $ a_1=5 $ we can choose $ a_2=3 $ . Note that their sum is a power of two. Similarly, such an element can be found for $ a_2 $ and $ a_3 $ ),
- $ [1, 1, 1, 1023] $ ,
- $ [7, 39, 89, 25, 89] $ ,
- $ [] $ .

Note that, by definition, an empty sequence (with a length of $ 0 $ ) is good.

For example, the following sequences are not good:

- $ [16] $ (for $ a_1=16 $ , it is impossible to find another element $ a_j $ such that their sum is a power of two),
- $ [4, 16] $ (for $ a_1=4 $ , it is impossible to find another element $ a_j $ such that their sum is a power of two),
- $ [1, 3, 2, 8, 8, 8] $ (for $ a_3=2 $ , it is impossible to find another element $ a_j $ such that their sum is a power of two).

You are given a sequence $ a_1, a_2, \dots, a_n $ . What is the minimum number of elements you need to remove to make it good? You can delete an arbitrary set of elements.

## 说明/提示

In the first example, it is enough to delete one element $ a_4=5 $ . The remaining elements form the sequence $ [4, 7, 1, 4, 9] $ , which is good.

## 样例 #1

### 输入

```
6
4 7 1 5 4 9
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
16
```

### 输出

```
1
```

## 样例 #4

### 输入

```
4
1 1 1 1023
```

### 输出

```
0
```

# 题解

## 作者：Peiyuan (赞：14)

[题目通道](https://www.luogu.com.cn/problem/CF1005C)

### 题目大意

输入 $n$ 个数 $a_i$，问至少删除多少个数才能使 $a$ 数组中的任意两个元素相加等于 $2$ 的整数次幂。

### 思路

这道题我们可以用哈希的方法，把每个数出现的次数累加。因为 $a_i$ 的值可以达到 $10^9$，数组装不下，所以我们可以用一个 ```map``` 来映射某个数和该数出现的次数。我们先遍历 $1$ 到 $n$，对于元素 $a_i$，我们可以寻找是否有一个元素等于 $a_i$ 加上某个二的整数次幂 $2^n=d$。其中，为了节省时间，我们可以对其中的 $d$ 进行枚举，看一看元素 $a_i$ 加进来以后满不满足要求，如果不满足，答案累加。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a[120005],ans;
map<ll,ll> m;
int main(){
	cin>>n;
	for(ll i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		m[a[i]]++; //表示有m[a[i]]个 a[i]元素
	}
	for(ll i=1; i<=n; i++){
		bool f=1;
		m[a[i]]--; //假如将a[i]元素拿走一个 
		ll d=1;
		while(d<=2e9){ //寻找2的整数次幂：d 
			if(m[d-a[i]]>0){ //说明这个元素满足要求，不用拿走，结束验证 
				f=0; break;
			}
			d*=2; 
		}
		if(f) ans++; //一翻枚举后发现a[i]必须拿走，累加答案 
		m[a[i]]++; //操作完成把a[i]元素放回map里，继续枚举 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：EdenSky (赞：4)

# [CF1005C Summarize to the Power of Two](https://www.luogu.com.cn/problem/CF1005C)
- [更好的阅读体验](https://www.cnblogs.com/wanguan/p/16884387.html)

## 正文

将原式 $a_i+a_j=2^p$ 转化为 $a_j=2^p-a_i$，对于，每个 $a_i$，枚举 $p$，可以有效地降低时间复杂度。

设 $num\leftarrow 0$，若 $2^p-a_i$ 存在相等的 $a_j$，则 $num\leftarrow num+1$，最后输出 $n-num$，可以通过 `unordered_map` 实现匹配。

代码：

```cpp
#include<iostream>
#include<unordered_map>
#define gg long long
using namespace std;
const gg INF=2e9+5;
gg n,a[120005],ans;
unordered_map<gg,gg> s;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n;
	for(gg i=1;i<=n;i++)	cin>>a[i],s[a[i]]++;
	for(gg i=1;i<=n;i++){
		s[a[i]]--;
		gg p=1;
		bool flag=true;
		while(p<=INF){
			if(s[p-a[i]]>0)	flag=false;
			p<<=1;
		}
		if(flag)	ans++;
		s[a[i]]++;
	}
	cout<<ans;
}
```

[提交记录](https://www.luogu.com.cn/record/93168009)。

---

## 作者：基建160282 (赞：4)

### 首先肯定有很多人看完翻译一脸懵，
所以我来说一下题目大意：

### 在 $n$ 个数中对于每一个数 $a_i$, 若不（存在 $j ≠ i$ 而且 $a_i+a_j=2^k(k∈N)$），则$ans++$,最后求的就是这个ans的个数

比如说在样例$[5, 3, 11]$中，5和3能互相匹配($5+3=8=2^3$),11能和5匹配($11+5=16=2^4$)所以```ans=0```

再比如说
```
6
4 7 1 5 4 9
```
这组样例
4能和另一个4匹配，1和7匹配，9和7匹配，但5没有匹配对象，所以$ans=1$

说完样例的事情，接下来分析解法。
这道题运用桶的思想，将每一个数存进桶里，map前一个参数表示值，后一个表示数量，到这个数时处理过程内$map[a[i]]--$,过后再加回来

那我们就来康代码吧~
```
# include <iostream>
# include <cstdio>
# include <cstring>
# include <map>
# include <algorithm>
using namespace std;
map <int, int> mp;//以map实现桶的功能
int a[1200005];//完全没必要的定义数组
int main()
{
	int n, ans = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", a + i);
		++mp[a[i]];//进桶
	}
	for(int i = 1; i <= n; ++i){
		--mp[a[i]];//为了防止这个数本身就是2幂次方而和自己匹配
		int q = 0;
		while((1 << q) <= a[i]) ++q; //找到比它大的第一个2幂次方
		bool flag = true;
		for(; q <= 30; ++q){//从第一个可以相加得到2幂次方的解向后枚举
			if(mp[(1 << q) - a[i]])
				flag = false;//找到了对应的数，想加快时间的话可以在后面break
		}
		if(flag) ++ans;//这个满足条件
		++mp[a[i]];
	}
	printf("%d\n", ans);//输出
	return 0;
}
```

---

## 作者：small_Dongpo (赞：2)

#  CF1005C 题解
## 思路
这道题题解许多人都用 map 做，也有人用 multiset 做，不过是 $1$ 个 multiset，但我觉得 $2$ 个 multiset 会更“真实直观具体”一些。

为了更好地理解，我们拿样例 $1$ 来讲:

1. 第 $1$ 个数 $4$，没有人和他配对（单身狗），我们定义 `multiset<l> s;` 把单身狗先存起来，并且定义 `multiset<l> ms;` 来存已经配对的数（l 指 long long）。

2. 第 $2$ 个数 $7$，我们可以枚举来看它是否能和别的数配对，由于 $2^{10} ≈ 10^3$ 且 $a_i ≤ 10^9$ 可以知道 $a_i ≤ 2^{30}$，我们枚举 $j$ 从 $1$ 到 $30$，如果 `pow(2, j) ≥ 7 && s.count(pow(2, j) - 7)` 则将 $7$ 和 $\operatorname{pow}(2, j) - 7$ 放到 $ms$ 中，但并未有数与 $7$ 配对，所以把 $7$ 放到 $s$ 中。

3. 第 $3$ 个数 $1$ 经枚举可发现当 $j = 8$ 时，$\operatorname{pow}(2, j) - 7$ 恰好等于 $7$，把 $7$ 取出，与 $1$ 都放入 $ms$ 中。

……

直到第 $6$ 个数的时候，我们会发现虽然 $9$ 不能和 $s$ 里面的数配对，但能和 $ms$ 里的 $7$ 配对，所以也将 $9$ 放入 $ms$ 中。

然后，我们就会特别轻松地写出代码：
```cpp
#include <iostream>
#include <set>
#include <cmath>
#define l long long
using namespace std;

multiset<l> s, ms;

int main()
{
    l n;
    scanf("%lld", &n);
    for (l i = 1; i <= n; ++i)
    {
        l x;
        bool f = 0;
        scanf("%lld", &x);
        for (l j = 0; j <= 30; ++j)
        {
            if (pow(2, j) >= x)
            {
                l y = pow(2, j) - x;
                if (ms.count(y) && f == 0)
                {
                	ms.insert(x);
                	f = 1;
                }
                if (s.count(y))
                {
                    if (f == 0) ms.insert(x);
                    for (l j = 1; j <= s.count(y); ++j) ms.insert(y);
                    s.erase(y);
                    f = 1;
                }
            }
        }
        if (f == 0) s.insert(x);
    }
    cout << n - ms.size();
    return 0;
}
```

然后评测：
            
![](https://cdn.luogu.com.cn/upload/image_hosting/r3h43m3q.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
            
当我们十分惊喜的时候却画面一转：

![](https://cdn.luogu.com.cn/upload/image_hosting/4jk8ye4c.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

于是用一个变量 $cnt$ 来记录重复的元素就能解决 TLE 了。
## 代码
```cpp
#include <iostream>
#include <set>// multiset是用set库，并没有multiset库
#include <cmath>// 要用pow，别把cmath库落下
#define l long long
using namespace std;

multiset<l> s, ms;

int main()
{
    l n, cnt = 0;
    scanf("%lld", &n);
    for (l i = 1; i <= n; ++i)
    {
        l x;
        bool f = 0;//f用来标记是否已将x存入ms
        scanf("%lld", &x);
        if (ms.count(x))// 如果ms中已经有x，说明x不是单身狗，直接把重复元素个数加1就行了
        {
        	cnt++;
        	continue;
        }
        for (l j = 0; j <= 30; ++j)//j是从0开始，不是从1开始
        {
            if (pow(2, j) >= x)
            {
                l y = pow(2, j) - x;
                if (ms.count(y) && f == 0)
                {
                	ms.insert(x);
                	f = 1;
                }
                if (s.count(y))
                {
                    if (f == 0) ms.insert(x);//如果已经存入，就不用再存了
                    ms.insert(y);
                    cnt += s.count(y) - 1;//一定要减1，y在因为ms里面已经算了一遍了
                    s.erase(y);
                    f = 1;
                }
            }
        }
        if (f == 0) s.insert(x);
    }
    cout << n - ms.size() - cnt;
    return 0;
}
```

---

## 作者：VenusM1nT (赞：2)

这道题比较迷，我也不能确定我的做法是不是正解，但是既然 $A$ 了那就来讲一讲好了【逃】

----------
大致题意：

对于一个数列 $a_1, a_2...,a_n$ ，如果每个 $a_i$ 都可以找出一个对应的 $a_j$ $(i\neq j)$ 使 $a_i+a_j=2^d (d>0)$ ，则称该数列为“好数列”，给定一个数列，试求出需要删除多少个数列中的数，才能使该数列为“好数列”。

--------------
这题的数据范围很大，$n$ 足有 $12w$ 的大小，那么复杂度的范围只能是 $O(nlong)$ 或者 $O(n)$

我的程序复杂度是 $O(n)$ 级别的，利用了 **桶** 的思想

那么有人就要问了：$a_i$ 的范围足有 $10^9$ 之大，你怎么用桶呢？

兄弟，cpp有个东西叫**映射** $(map)$

【此处应有滑稽】

做法具体如下：

设定两个 $map$：$m$ 和 $tw$，其中 $m$ 记录数有没有出现过，$tw$ 记录数是否出现了两次

（这里注意使用 $<int, bool>$ 可以有效降低空间复杂度）

读入一个数 $a_i$，将 $m[a_i]$ 设为 $true$，如果 $m[a_i]$ 本来就为 $true$ 的话，将 $tw[a_i]$ 设为 $true$

接下来从 $a_1$ 到 $a_n$ 循环

对于每个 $a_i$，枚举 $j$ 使 $j=2^d$ $(d>0)$，判断 $j-a_i$ 是否出现，即 $m[j-a_i]$ 是否为 $true$，如果一直不为 $true$ 则该数需要删除，$ans+1$

但是如果你直接这么写，你会发现你会有 $WA$ 掉的点，这是为什么呢？

这里就需要用到上方提到的 $tw$ 数组了，举个栗子：

如果 $j=8$，$a_i=4$，可以发现 $m[j-a_i]=m[4]=true$，但是数列中可能只有一个 $4$，这代表着这个 $a_i$ 应该是要删去的，但因为 $m[4]=true$，所以程序并不会判断它删去

也就是说，如果 $j-a_i$ $==$ $a_i$ 的话，我们就需要判断 $tw[j-a_i]$ 是否为 $true$

核心代码如下：

预处理：

```
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(m[a[i]]) tw[a[i]]=1;
		m[a[i]]=1;
	}
```

枚举 $j$：

```
	for(int j=1;j<=1073741824;j*=2)
	{
		if(j<0) break;
		if(j<=a[i]) continue;
		if(m[j-a[i]])
		{
			if((j-a[i]==a[i] && tw[j-a[i]]) || (j-a[i]!=a[i] && m[j-a[i]]))
			{
				flag=1;
				break;
			}
		}
		if(j==1073741824) break;
	}

```

---

## 作者：梦应归于何处 (赞：1)

## 题目大意

给定 $n$ 个数，请问至少要在这 $n$ 个数中删除多少个数才能保证。每个数一定能找到一个不是它自己但能和它相加为 $2$ 的整数次方的数。

## 思路

别的题解好像都是用 `map` 来做的。

我来说一下用 `set` 的一种做法。

我们先把整个数组排一遍序，让他们都从小到大，要不然可能会出现有的大的在前面找不到能和他匹配的数，但实际上是有数可以与他匹配的情况。

然后我们定义两个 `multiset` （这个就是一种不去重的 `set` ）。一个里面存还不能被匹配的数，一个里面存可以被匹配的数。

这样初始化结束了。

然后我们去对每个数枚举 $2$ 的整数次方，用这个 $2$ 的整数次方去减这个数（这个 $2$ 的整数次方要大于这个数）。然后我们去两个 `multiset` 里面去找有没有这个 $2$ 的整数次方减掉这个数的这个数。如果有，那么我们就把它放到可以匹配的那个 `multiset` 中。如果没有，那就把他放到那个还不能被匹配的那个 `multiset` 中。

最后答案就输出那个还不能被匹配的那个 `multiset` 的长度。

还有一些小细节看代码。

## 代码

~~~cpp
#include <bits/stdc++.h>
#define TNTMAX INT_MAX
#define db double
#define ll long long
#define ex exit(0);
#define endl "\n"
#define inl inline
#define null NULL
using namespace std;
ll a[130000];
unordered_multiset<ll> t, s;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	bool flag = 1;
	ll tot = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		tot += a[i];
		if (a[i] != 1) {
			flag = 0;
		}
	}
	if (flag && n != 1) {
		cout << "0";
		return 0;
	}
	sort(a + 1, a + n + 1);
	ll cnt = 0;
	for (int i = 1; i <= n; i++) {
		bool flag = 0;
		for (ll k = 1; k <= tot; k *= 2) {
			if (k > a[i]) {
				if (t.count(k - a[i])) {
					s.insert(a[i]);
					s.insert(k - a[i]);
					t.erase(k - a[i]);
					flag = 1;
					break;
				}
				if (s.count(k - a[i])) {
					s.insert(a[i]);
					flag = 1;
					break;
				}
			}
		}
		if (!flag) {
			t.insert(a[i]);
		}
	}
	cout << t.size();
	return 0;
}
~~~

---

## 作者：ttq012 (赞：1)

$\color{green}\texttt{Difficulty : 1300}$

可以将 $a_i+a_j=2^k$ 这个式子转化为 $a_i=2^k-a_j$。

然后枚举每一个 $j$，然后枚举 $2$ 的每一个幂次 $2^k$，判断 $a$ 数组中是否存在 $2^k-a_j$ 这个元素，也就是 $a_i$ 即可。使用 `multiset` 维护。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],b[N],p[N];
signed main(){
  int n;
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i];
  multiset<int>se;
  for(int i=1;i<=n;i++)se.insert(a[i]);
  int cnt=0;
  for(int i=1;i<=n;i++){
    se.erase(se.find(a[i]));
    bool flag=false;
    int pw=1;
    for(int j=0;j<32;j++){
      if(se.count(pw-a[i])>=1){
        flag=true;
        break;
      }
      pw<<=1;
    }
    if(!flag)cnt++;
    se.insert(a[i]);
  }
  cout<<cnt<<'\n';
  return 0;
}
```

 

$\color{gray}\tiny{\text{本文作者}}\color{gray}\texttt{luogu uid=378467}\text{转载请附上此段声明，谢谢QwQ}$

---

## 作者：Otue (赞：0)

这种搞笑题怎么评到绿的。

## 题目大意
给出一个长度为 $n$ 的序列 $a$，求最少删除多少个数，使得对于任意一个 $i$，存在 $j$ 满足 $j≠i$ 且 $a_i+a_j=2^k(k≥0)$。

## 思路
首先，如果对于一个 $i$，不存在 $j$ 满足 $j≠i$ 且 $a_i+a_j=2^k(k≥0)$，那么 $i$ 必定会被删掉。

满足这个条件只需满足有 $a_j=a_i-2^k(j≠i)$。那么对于每个 $i$，枚举 $k(k\leq 32)$，用 `map` 判断 $a_i-2^k$ 是否存在即可。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;

int n, a[N], res;
map<int, int> vis;

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], vis[a[i]]++;
	for (int i = 1; i <= n; i++) {
		int flg = 0;
		vis[a[i]]--;
		for (int j = 0; j <= 32; j++) {
			if (vis[(1 << j) - a[i]]) flg = 1;
		}
		vis[a[i]]++;
		res += !flg;
	}
	cout << res << endl;
}
```

---

## 作者：_zxh110408 (赞：0)

# 题意

给出一个长度为 $n$ 的序列 $a$，求最少删除多少个数使 $\forall i$，$\exists j\ne i,a_i+a_j$ 为 $2$ 的幂次方。

# 思路
首先， $2$ 的幂次方（ $2\times10^9$ 以内）很少，只有大约 $30$ 个，所以我们可以枚举出 是 $2$ 的幂次方（ $2\times10^9 $ 以内）的数，然后枚举 $a_i$ 或 $a_j$ 中的一个（用 $2$ 的幂次方数减去一个即可求出另一个），在查找另一个数是否存在，如果另一个数是否存在，则符合条件的数 $+1$ ，否则判断下一个 $2$ 的幂次方，最后输出 $n$ 减去 符合条件的数 。

# 代码
```cpp
#include<bits/stdc++.h>
#include<math.h>
using namespace std;
set<long long>s;
map<long long ,long long>m;
long long b[2000000];
long long aa[2000000];
int main(){
	long long n;
	cin>>n;
	long long shu=1;
	long long w;
	long long ans=0;
	for (w=0;shu<=2000000000;w++){
		
		shu*=2;
		aa[w]=shu;
	}
	for (int i=0;i<n;i++){
		long long a;
		cin>>a;
		b[i]=a;
		for (int j=0;j<=w;j++){
			if (a==aa[j]/2 and s.count(a)==1){
				ans++;
				b[i]=200000000000;
				break;
			}
		}
		
		m[a]=i+1;
		s.insert(a);
		
	}
	long long cnt;
	for (int i=0;i<n;i++){
		cnt=b[i];
		for (int j=0;j<=w;j++){
			if (s.count(aa[j]-cnt)==1 and m[aa[j]-cnt]!=i+1){
				ans++;
				break;
			}
		}
		
	}
	cout<<n-ans<<endl;
	return 0;
} 
```

---

## 作者：TRZ_2007 (赞：0)

**[题解 【CF1005C Summarize to the Power of Two】](https://www.luogu.com.cn/problem/CF1005C)**    
# Solution  

题目就是这个意思：  
给定一个数列 $a$，求满足 $2^q=a_i+a_j$ ($1\le i,j\le n,q\in Z$) 不成立的数据组数。  
十分简单，首先我们考虑这个等式，它可以换成 $a_j = 2^q-a_i$，其中我们暴力枚举 $a_i$，然后再暴力计算出**第一个** $q$，往后到数据极限，如果其中有一组数据满足等式，那么这一个 $a_i$ 一定不能记录进我们的答案，否则就可以，那么怎么判断满足等式呢？显然，我们考虑桶，用 ``map`` 或者 ``hash`` 都可以满足要求。

# Code  
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1.2e5 + 9;

typedef long long ll;
#define gc getchar
inline ll read() {
	ll c = gc(), t = 1, n = 0;
	while(isspace(c)) { c = gc(); }
	if(c == '-') { t = -1, c = gc(); }
	while(isdigit(c)) { n = n * 10 + c - '0', c = gc(); }
	return n * t;
}
#undef gc

map <int,int> mp;
int a[N],n,q,flag,ans = 0;

int main() {
	n = read();
	for(int i = 1;i <= n;i++) {
		a[i] = read(); mp[a[i]]++;
	}
	for(int i = 1;i <= n;i++) {
		mp[a[i]]--;
		q = 0; flag = 0;
		while((1 << q) <= a[i]) q++;
		for(; q <= 31; q++) {
			if(mp[(1 << q) - a[i]]) { flag = 1; break; }
		}
		if(!flag) ++ans;
		++mp[a[i]];
	}
	printf("%d\n",ans);
	return 0;
}
```

---

