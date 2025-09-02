# Powers of Two

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Find the number of pairs of indexes $ i,j $ ( $ i&lt;j $ ) that $ a_{i}+a_{j} $ is a power of $ 2 $ (i. e. some integer $ x $ exists so that $ a_{i}+a_{j}=2^{x} $ ).

## 说明/提示

In the first example the following pairs of indexes include in answer: $ (1,4) $ and $ (2,4) $ .

In the second example all pairs of indexes $ (i,j) $ (where $ i&lt;j $ ) include in answer.

## 样例 #1

### 输入

```
4
7 3 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
3
```

# 题解

## 作者：IntrepidStrayer (赞：4)

由于 $a_i\le10^9$，数列中两个数的和不超过 $2\times 10^9$。而 $2^{31}=2147483648>2\times 10^9$，所以我们可以枚举 $x$。对于每个 $a_i$，其实就是找满足 $2^x-a_i=a_j$ 且 $i<j\le n$ 的 $j$ 的个数，这个可以从后往前扫一遍，用 `map` 统计即可。

时间复杂度 $\operatorname{O}(n\log\max\{a_i\}\log n)$。

```cpp
const int N = 1e5 + 15;

int a[N], n;
ll ans;
map <int, int> m;//m 的每个元素代表这个数在 i 后面出现过多少次
map <int, int> :: iterator it;

signed main() {
	n = read();
	rep(i, 1, n) a[i] = read();
	for(register ll x = 2; x <= 2e9; x <<= 1, m.clear())//注意每次都要清空
		per(i, n, 1) {
			it = m.find(x - a[i]);
			if(it != m.end()) ans += m[x - a[i]];
			m[a[i]] ++;
		}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Siteyava_145 (赞：2)

### 题意：

在一个序列里选两个位置不同的数，使他们的和为 $2^x$ 的选法有多少种？

一眼可用 `map`（对 `map` 的依赖过重。。。），存每个数的出现次数。然后枚举所有在 $1\sim10^9$ 范围内的 $2^x$。每次枚举后，将此数的出现次数减 $1$，避免重复。

时间复杂度：$O(n\log 10^9\log n)$，结合 $n\le10^5$，可过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>mp;//出现次数
int a[100005];
long long ans=0;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
	    cin>>a[i];
	    mp[a[i]]++;
	}
	for(int i=1;i<n;i++){
		mp[a[i]]--;//选了第1,3个数后，避免再选到3,1个数造成重复。
	    for(int j=0;j<=30;j++){//扫一遍2^x
	        ans+=mp[(1<<j)-a[i]];//数字出现的次数
	    }
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：_NTT_ (赞：2)

# 思路
使用桶排序，但数据太大，考虑离散化， ~~（但是我太弱了只会STL）~~ ，使用STL中的 `map<int, int>` 可以达到效果，其中 `first` 表示某数 $n$， `second` 表示 $n$ 出现的次数。

之后遍历 `map` ，将当前遍历的 `first` 表示为 $x_1$ ， `second` 表示为 $y_1$ ，查找 `map` 中的 $x_2$ ， $y_2$ ，使得 $x_2 = 2^k - x_1$ $(k < 32)$。
之后执行：

```cpp
if(x_1 == x_2) res += y1 * (y2 - 1) / 2;
else res += y1 * y2;
```
即可。

# 细节

- 数很大，需要开 `long long`
- 由于每个 `map` 中的元素会遍历两次，所以答案要除以2.
- 但是两个相等的元素只会计算一次，所以代码要这么写：
```
if(x_1 == x_2) res += y1 * (y2 - 1);//除以2去掉了
else res += y1 * y2;
```

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x;
}

int n, e = 2e9;
long long res;
map<int, int> mp;

int main() {
    n = read();
    for(int i = 0 ;i < n ;++i) ++mp[read()];

    for(auto i : mp) {
        int a = i.first, b = i.second;

        for(long long x = 1 ;x <= e ;x <<= 1) {
            auto j = mp.find(x - a);
            if(j != mp.end()) {
                int a1 = j->first, b1 = j->second;
                if(a1 != a) res += (long long)b * b1;
                else res += (long long)b * (b - 1);
            }
        }
    }

    cout << res / 2 << endl;

    return 0;
}
```

时间复杂度： $O(nlogn)$ 
。可以通过本题


![](https://cdn.luogu.com.cn/upload/image_hosting/2wkhbptf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

---

## 作者：mcDinic (赞：2)

见到各位讲的方法大多为枚举幂次数的，且是最暴力的方法，我呢，就讲个稍微不一样的办法。

## 正文

先简单介绍下普遍做法吧。

因为要用 $a_i+a_j=2^x$，即 $2^x\le2\times10^9$，那么我们可以得到 $x\le30$。也就是说，用 map 统计好各个数字出现次数后，一遍扫过来，就能得出答案了。为避免重复，每过到一个数字，map 中就将它减去即可。

代码略。

## 另一种做法

在普通做法的基础上，我们可以发现，只要排序后，对于某数所对应的可能幂次方，在一定范围内，详见代码。

### Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005],ans;
map<int,int>mp;//统计出现次数。
signed main(){
	cin>>n;
	mp.clear();
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		mp[a[i]]++;
	}
	a[0]=0x3f3f3f3f;
	sort(a+1,a+1+n);//排序。
	for(int i=1;i<n;i++){
		mp[a[i]]--;//每进一个数减一次。
		int l=ceil(log2(a[i]+a[i+1])),r=floor(log2(a[i]+a[n]));//即幂次方的取值范围内。
		for(int j=l;j<=r;j++){
			ans+=mp[pow(2,j)-a[i]];
		}
	}
	cout<<ans;
    return 0;	
}
```


---

## 作者：Eason_AC (赞：1)

## Content
给定一个长度为 $n$ 的数组 $a_1,a_2,\dots,a_n$，请找出所有满足如下条件的 $(i,j)$ 的对数：

- $1<i<j<n$。
- $a_i+a_j=2^x(x\in\mathbb N^*)$。

**数据范围：$1\leqslant n\leqslant 10^5$，$1\leqslant a_i\leqslant 10^9$。**
## Solution
$\mathcal O(n^2)$ 的枚举显然跑不过，考虑如何优化时间复杂度。

我们发现，在本题中，$2\leqslant a_i+a_j\leqslant 2\times 10^9$，而在 $[2,2\times 10^9]$ 这个区间内的所有的 $2$ 的次幂是 $2,2^2,\dots,2^{30}$，只有 $30$ 个。因此，我们开一个桶，扫一遍数组，统计每个数出现的次数。设 $x$ 在数组中所有当前扫到的位置中出现的次数为 $c_x$，当前扫到的位置为 $i$。然后，我们再直接枚举每个次幂 $2^j$，根据之前的定义，我们发现只需要将 $c_{2^j-a_i}$ 加入答案中，然后更新 $c_{a_i}$ 的值为 $c_{a_i}+1$，就可以保证不重不漏。

所以按照上述步骤扫一遍数组中的所有元素，就可以做出这道题目了。

实现时，注意到 $a_i+a_j$ 最大可能到 $2\times 10^9$，因此考虑转用 `map` 来统计。
## Code
```cpp
namespace Solution {
	int n, x; ll ans;
	map<int, int> vis;
	
	iv Main() {
		read(n);
		F(int, i, 1, n) {
			read(x);
			F(int, j, 1, 30) ans += vis[(1 << j) - x];
			vis[x]++;
		}
		write(ans);
		return;
	}
}
```

---

## 作者：GWBailang (赞：0)

[**原题传送**](https://www.luogu.com.cn/problem/CF702B)

很暴力，$a_i+a_j$ 如果要是 $2$ 的整数次方的话，最多只能是 $2^{30}$。枚举一下 $a_i+a_j$ 的和，再枚举一下 $a_i$，然后用 map 来找到有几个 $a_j$ 即可。

最终时间复杂度为 $O(n)$。常数可以直接忽略。

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005];
map<long long,long long>ma;
int main(){
	long long n,ecf=1,he=0,cnt=0;
	//ecf为“二的整数次方”的缩写的拼音
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
		ma[a[i]]++;
		he+=a[i];
	}
	//这个计算总和的变量he可有可无
	for(long long x=1;ecf*2<=he;x++){
		ecf*=2;
		for(long long i=1;i<=n;i++){
			if(a[i]<=ecf&&ma[ecf-a[i]]){
				if(ecf-a[i]==a[i])cnt+=ma[ecf-a[i]]-1;
				else cnt+=ma[ecf-a[i]];
			}
		}
	}
	cout<<cnt/2<<endl;//会重复，最后不要忘记除2
	return 0;
}
```

最后，别忘了开 long long。

---

## 作者：InversionShadow (赞：0)

双重循环暴力 $O(n^2)$。 肯定会 $\texttt{TLE}$，那么怎么优化呢？

因为题目要求的是 $a_i+a_j=2^x$，且 $1\le a_i \le 10^9$，那么 $2\le a_i+a_j\le2 \times10^9$，而 $2^{31}$ 就有 $2 \times 10^9$ 次方了，所以我们可以枚举 $2^1 \sim 2^{31}$，开一个 `map` 记录 $2^j-a_i$ 的出现次数。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e5 + 100;

int n, a[MAXN];

map<int, int> mp1;

int qpow(int x, int y) {
  if (!y) {
    return 1;
  }
  int tmp = qpow(x, y / 2);
  if (y & 1) {
    return tmp * tmp * x;
  }
  return tmp * tmp;
}

signed main() {
  cin >> n;
  int ans = 0;
  for (int k = 1; k <= n; k++) {
    cin >> a[k];
    for (int i = 1; i <= 32; i++) {
      if (mp1[qpow(2, i) - a[k]]) {
        ans += mp1[qpow(2, i) - a[k]];
      }
    }
    mp1[a[k]]++;
  }
  cout << ans;
  return 0;
}

```

---

## 作者：ACtheQ (赞：0)

## CF702B Powers of Two

本题比较水为 ```STL``` 大水题！

前置知识：[map](https://www.cnblogs.com/fnlingnzb-learner/p/5833051.html)。

### 本题思路

可以去枚举答案是 $2$ 的几次方。

由于和 $\le 10^9$ 所以只用枚举为 $2$ 的 $0 \sim 30$ 次方了。

先定义一个 `map`。

对于当前输入的 $a_i$,枚举 $x (0 \le x \le 30)$。

定义一个变量 $a_j$ 为 $2^x-a_i$。

如果当前 $a_j$ 在 `map` 中出现过，答案增加 $map[a_j]$。

再让 $map[a_i]$ 增加 $1$。

最后输出答案。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int a[N];
unordered_map<int,int> cnt;
int main()
{
	int n;
	cin>>n;
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		for(int x=0;x<31;x++)
		{
			int aj=(1<<x)-a[i];
			auto itr=cnt.find(aj);
			if(itr==cnt.end()) continue;
			ans+=(*itr).second;
		}
		cnt[a[i]]++;
	}
	cout<<ans;
    return 0;
}

```

---

## 作者：HoshiuZ (赞：0)

枚举和的$O(n^2)$算法很好想，但肯定会超时。

不妨反过来想，即求$a_i=2^x-a_j$，那么便可以枚举$2^x$。

首先对序列从小到大排个序，去个重，并令原序列中中数$i$的个数为$js[i]$，那么

当$a_i<2^{x-1}$时，根据乘法原理，对数即为$js[a_i]*js[2^x-a_i]$。

当$a_i=2^{x-1}$时，则对数为$C_{js[a_i]}^2$，即为$\frac{js[a_i]*(js[a_i]-1)}{2}$。

当$a_i>2^{x-1}$无须考虑，与第一种情况重复。

范围$10^9$，则只需要到$2^{30}$，时间复杂度约为$O(30n)$。

## 代码
练练STL。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll ans=0;
int n,t[50];
set <int> a;
map <int,ll> js;

void work(int maxn) {
	for(set<int>::iterator it=a.begin();it!=a.end();it++) {
		if(*it>maxn) break;
		if(maxn==*it) ans+=(js[*it]*(js[*it]-1))/2;
		else ans+=js[*it]*js[maxn*2-*it];
	}
}
		
int main() {
	t[0]=1;
	for(int i=1;i<=30;i++) t[i]=t[i-1]*2;
	cin>>n;
	for(int i=1;i<=n;i++) {
		int x;
		cin>>x;
		a.insert(x);
		js[x]++;
	}
	
	for(int i=1;i<=30;i++) work(t[i]/2);
		
	cout<<ans<<endl;
	
	return 0;
}
```


---

## 作者：yijan (赞：0)

题目大意： 给定一个长度为n的数列然后求里面有多少组数字加起来是2的幂（被禁言了提交不了QAQ）

非常裸的hash题，主要思路不说了说下细节：
1. 对于每一个数字找比它小的最好，因为比它小的+这个数字只可能达到比这个数字大的第一个2的幂，因此排序后不需要枚举哪一个2的幂
2. 不要直接用unordered_multiset会卡T，考虑对于每个数字建立一个映射关系（或者说。。。离散化？）

代码

```cpp
/* Accepted. */
#pragma GCC optimize(3)
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<unordered_map>
using namespace std;
typedef long long ll;
#define MAXN 100006
ll A[MAXN];
unordered_map<ll,ll> to,bac;
ll num[MAXN] , p;
int main() {
	freopen("input","r",stdin);
    ll n , ans = 0;
    cin >> n;
    for( ll i = 0 ; i < n ; ++ i ) 
        scanf("%d",&A[i]);
    sort( A , A + n );
    for( ll i = 0 ; i < n ; ++ i ){
        ans += num[to[(1LL<<(ll)log2(A[i])+1LL) - A[i]]];
		if(!to[A[i]]) to[A[i]] = ++p ;
		++num[to[A[i]]];
    }       
    cout << ans;
}//qwq


```

---

