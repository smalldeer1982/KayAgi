# Zero Quantity Maximization

## 题目描述

# 零数最大化
给出两个长度为 $n$ 的数组 $a,b$。

你想要创建一个长度为 $n$ 的数组 $c$，且$c_i=d*a_i+b_i,i\in[1, n]$，要求你给 $d$ 赋值，使得数组 $c$ 中的 $0$ 的个数最多并输出最多的 $0$ 的个数。

## 样例 #1

### 输入

```
5
1 2 3 4 5
2 4 7 11 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
13 37 39
1 2 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
0 0 0 0
1 2 3 4
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3
1 2 -1
-6 -12 6
```

### 输出

```
3
```

# 题解

## 作者：andyli (赞：3)

根据题意得出当$c_i$为$0$时：  
1. $a_i\ne 0$时，$d=-\frac{b_i}{a_i}$  
2. $a_i = b_i = 0$时，$d=0$  

所以我们需要统计满足第2种情况的个数以及第1种情况中出现最多的$d$出现的次数。
判断$d$出现的个数可以用$map$来实现，首先用$gcd$约分，然后统一负号出现的位置，把这个分数出现的次数++，并同时计算$ans$，最后把满足第$2$种情况的个数与$ans$相加便是最终的答案。  
代码如下：  
```cpp
#include <cstdio>
#include <map>
#include <numeric>
using namespace std;
const int maxn = 200005;

int A[maxn];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    int sum = 0, ans = 0;
    map<pair<int, int>, int> mp;
    for (int i = 0; i < n; i++) {
        int a = A[i], b;
        scanf("%d", &b);
        if (!a && !b)
            sum++; // 第2种情况
		else if(!a) continue; // a=0时-b/0不合法
		else{
			if (1LL * a * b < 0) // 如果a, b异号，注意使用long long判断
            	a = -abs(a), b = abs(b);
			else // a, b同号
				a = abs(a), b = abs(b);
			int t = gcd(a, b); // C++17中numeric头文件里包含gcd函数，不需要考虑正负
			ans = max(ans, ++mp[pair(b / t, a / t)]);
		}
    }
    printf("%d\n", sum + ans);
    return 0;
}
```

---

## 作者：AndyMo (赞：2)

## map+pair水过
推得要统计 -b[i]/a[i] 相同的个数,但好像与正负无关，只需分别除以gcd(a[i],b[i]),用pair存就好了。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
namespace io{
    #define re register
    #define ll long long
    #define inf 0x3f3f3f3f
    #define il inline 
    #define in1(a) read(a)
    #define in2(a,b) in1(a),in1(b)
    #define in3(a,b,c) in2(a,b),in1(c)
    #define in4(a,b,c,d) in2(a,b),in2(c,d)
    il void readl(ll &x){
        x=0;ll f=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
        while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
        x*=f;
    }
    il void read(int &x){
        x=0;int f=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
        while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
        x*=f;
    }
}using namespace io;
#define N 200005
int n;
int a[N],b[N];
map <pair<int,int>,int> cnt;
int main(){
	int ans=0,res=0;
	read(n);
	for(re int i=1;i<=n;i++) read(a[i]);
	for(re int i=1;i<=n;i++){
		read(b[i]);
		if(a[i]==0){
        //特判：a[i]==0时，无论d取多少c都只与b[i]有关
			if(b[i]==0) res++;
			continue;
		}
		int gcd=__gcd(a[i],b[i]);
		ans=max(ans,++cnt[make_pair(a[i]/gcd,b[i]/gcd)]);
	}
	printf("%d",ans+res);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

考虑暴力。

对于 $i$，若 $c_i=0$，则 $d \times a_i + b_i=0$。移项得：$d=\frac{-b_i}{a_i}(a_i \ne 0)$。有特殊的，$a_i=0
\land b_i=0$ 时，$d$ 可以等于任何数。

这个玩意将 $\frac{-b_i}{a_i}$ 化简到最简分数 $\frac{x}{y}$，记录下来 $x,y$。开个 map 存分子为 $x$ 分母为 $y$ 时 $\frac{x}{y} \times a_i +b_i=0$ 的组数然后求最大值再加上特殊情况即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=2e5+10;
int n,a[N],b[N];
map<pii,int> cnt;

il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i) a[i]=rd;
	for(re int i=1;i<=n;++i) b[i]=rd;
	int mx=0,ans=0;
	for(re int i=1;i<=n;++i){
		if(!a[i]){
			if(!b[i]) ++ans;
			continue;
		}
		int x=-1*b[i];
		int y=a[i];
		int g=gcd(x,y);
		x/=g,y/=g;
		mx=max(mx,++cnt[{x,y}]);
	}
	printf("%lld\n",mx+ans);
	return ;
}

signed main(){
	int t=1;while(t--)
	solve();
	return 0;
}

```


---

## 作者：Eason_cyx (赞：0)

不难的题。

首先考虑转换式子：

$$d\times a_i+b_i=0$$

$$d\times a_i=-b_i$$

$$d=-\dfrac{b_i}{a_i}$$

那么接下来分类讨论：

1. $a_i=0$，此时如果 $b_i=0$，那么 $d$ 可以取任意值，将这种情况的数量单独记录，和后面的答案相加即可。

2. $a_i \not = 0,b_i \not = 0$，此时将所有这种情况的 $d$ 存入 `map` 中（因为会产生精度误差，所以需要使用分数形式存储，注意 $a_i$ 和 $b_i$ 的正负性，可以通过判断，取相反数来保证 $a_i$ 非负，具体见代码），最后找到出现最多的一个就是答案。

3. $a_i \not = 0,b_i=0$，此时与第二种情况相同，但是你会发现 $a_i=1,b_i=0$ 和 $a_i=2,b_i=0$ 答案相同，都是 $d=0$，所以此时统一令 $a_i=1$ 就可以了。

时间复杂度 $O(n\log n)$，其中 $\log n$ 为 `map` 时间复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005], b[200005];
map<pair<int, int>, int> mp;
int main() {
	int n, ans = 0, cnt = 0; cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++) cin >> b[i];
	for(int i = 1;i <= n;i++) {
		if(a[i] == 0) {
			if(b[i] == 0) ans++;
		} else {
			int GCD = __gcd(abs(a[i]), abs(b[i]));
			int na = a[i] / GCD, nb = b[i] / GCD;
			if(na < 0 && nb < 0) na = -na, nb = -nb;
			if(nb > 0 && na < 0) na = -na, nb = -nb;
			if(nb == 0) na = 1;
			mp[{na, nb}]++;
		}
	} int maxn = 0; for(auto i : mp) maxn = max(maxn, i.second);
	cout << ans + maxn << endl;
	return 0;
}
```

---

## 作者：GJX_Algorithm (赞：0)

# CF1133D题解
## 题目描述
- 给定两个长度为 $n$ 的数组 $a,b$。

- 现在你可以选定任意一个数 $d$ 来创造一个数组 $c$，使得 $c_i = d \times a_i + b_i$。

- 请你输出含 0 最多的 $c$ 数组。

## 解题思路
- ~~其实我想不通这题是咋绿题的~~，首先这题是可以 long double 过的，[具体看这位大佬的题解](https://www.luogu.com.cn/article/h6l9bmwi)。

- 根据题意可以知道，当 $c_i = 0$ 时，可分为三种情况：

  1. $a_i = b_i = 0$，$d$ 可以是任何数。
 
  2. $a_i = 0,b_i \neq 0$，无解。
 
  3. $a_i \neq 0$，$d = \frac{-b_i}{a_i}$。
 
- 做到这里就很明显了，答案即为情况 1 的个数与情况 3 中所有 $d$ 的最多个数的和。

- 由于会有精度问题，所以这里计算 $d$ 笔者采用分数来解决。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N], b[N], d[N];
map<pair<int, int>, int> mp;
int n, maxi;
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	int ans = 0, sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 0)
		{
			if (a[i] == b[i]) ans++;
			continue;
		}
		int k = __gcd(b[i], a[i]);	
        int x = a[i] / k, y = b[i] / k;
        sum = max(sum, ++mp[make_pair(x, y)]);
    }
	cout << ans + sum;
	return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

给定 $n$ 个数的序列 $a$ 和 $b$，你需要计算出 $c$ 序列，其中 $c_i = d \cdot a_i + b_i(1 \leq i \leq n)$，你可以指定任意 $d$，最大化 $c$ 序列 $0$ 的数量。

## 解法

考虑若 $c_i=0$，那么 $d = \dfrac{-b_i}{a_i}$。若 $a_i=0$，那么 $d$ 取任意数均可。考虑将 $\dfrac{-b_i}{a_i}$ 存入 `map` 统计出现次数。

但是这样做用 `double` 存精度不够，实测 WA on test 37，可以考虑用分数，但其实 `long double` 可过。

```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 2e5 + 5;

int n, a[N], b[N], c = 0, ans = 0;

map<long double, int> mp;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 0)
		{
			c += (b[i] == 0);
		}
		else
		{
			mp[(long double)-b[i] / a[i]]++;
		}
	}
	for (auto i : mp)
	{
		ans = max(ans, i.second);
	}
	printf("%d\n", ans + c);
	return 0;
}
```


---

