# Difference of GCDs

## 题目描述

You are given three integers $ n $ , $ l $ , and $ r $ . You need to construct an array $ a_1,a_2,\dots,a_n $ ( $ l\le a_i\le r $ ) such that $ \gcd(i,a_i) $ are all distinct or report there's no solution.

Here $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

## 说明/提示

In the first test case, $ \gcd(1,a_1),\gcd(2,a_2),\ldots,\gcd(5,a_5) $ are equal to $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , respectively.

## 样例 #1

### 输入

```
4
5 1 5
9 1000 2000
10 30 35
1 1000000000 1000000000```

### 输出

```
YES
1 2 3 4 5
YES
1145 1926 1440 1220 1230 1350 1001 1000 1233
NO
YES
1000000000```

# 题解

## 作者：Hisaishi_Kanade (赞：14)

很有意思。

提供一种和大多数人不一样、和官方题解不同的、易理解的方法。

### 一、题意

给出 $n,l,r$，构造 $a$，使得对于任意 $\gcd(a_i,i)$ 不相同。

明确一点：$a_i$ 不一定不相同，这也是我方法正确的关键之处。

### 二、思路

约定：以下叙述中，$m$ 为正整数。

我们要想到结果必定是 $\gcd(a_i,i)=i$。

证明也很简单，因为 $\gcd(a_i,i)\in[1,i]$，而 $[1,i-1]$ 都被用过了，所以只能是 $i$。

问题转换为如何求 $a_i\in[l,r]$ 为 $i$ 的倍数。


首先，显然 $a_i$ 必定为 $im$，此处先求最大的可能的 $m=\lfloor\dfrac r i\rfloor$。

那么 $\max\left\{a_i\right\}=mi=\lfloor\dfrac r i\rfloor\times i$。

无解更简单，$a_i$ 已经最大了，如果依然小于 $l$，那 $[l,r]$ 中就必定没有合理的 $a_i$ 了。

注意，如果 $a_i$ 互不相同，这个做法就不正确了。

### 三、代码

```cpp
#include <stdio.h>
int ans[100005];
int t,l,r,i,n;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d %d",&n,&l,&r);
		bool ok(true);
		for(i=1;i<=n;++i){
			if(r/i*i<l){//最大都小了，那么必定做不到
				ok=false;
				puts("NO");
				break;
			}
			ans[i]=r/i*i;//求a[i]
		}
		if(ok){//都可以，那么有解
			puts("YES");
			for(i=1;i<=n;++i)
				printf("%d ",ans[i]);
			puts("");
		}
	}
}
```


---

## 作者：Prms_Prmt (赞：2)

### 思路
注：$ ans_i $ 指一组数据输出的第 $ i $ 个数据。

根据观察样例，找到规律，最有可能的情况是 $ \gcd(ans_i,i)=i$，也就是说，$ i\mid ans_i $。

**注意**：题目没说 $ ans_i $ 不能重复，~~比赛时就被坑了~~。
### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
 
 
int t,n,l,r,uk;
 
 
int main() {
	scanf("%d",&t);
	while(t--)
	{
		uk=0;
		scanf("%d%d%d",&n,&l,&r);
		for(int i=1;i<=n;i++)
		{
			int dest=((l+i-1)/i)*i;//大于等于l的第一个i的倍数
			if(dest>r) uk=1;//超出r限制
		}
		if(uk)
			{
				puts("NO");
			}
			else
			{
				puts("YES");
				for(int j=1;j<=n;j++)
					printf("%d ",((l+j-1)/j)*j);
				puts("");
			}
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1eB4y1Y7ZV)

### 2 思路

我们可以发现，$1\le\operatorname{gcd}(i,a[i])\le i$。那么 $\operatorname{gcd}(1,a[1])=1$。

并且，$\operatorname{gcd}(i,a[i])$ 互不相同，所以 $\operatorname{gcd}(2,a[2])=2$，以此类推，$\operatorname{gcd}(i,a[i])=i$。

我们可以发现，当且仅当 $a[i]$ 为 $i$ 的倍数时 $\operatorname{gcd}(i,a[i])=i$。

那么当且仅当对于所有 $i(1\le i\le n)$ 都有 $l\le a[i]\le r$ 且 $a[i]$ 为 $i$ 的倍数。

对于每个 $i$，求解出这个 $a[i]$ 即可。

我们可以发现，当且仅当存在 $\lfloor l\div i\rfloor=\lfloor r\div i\rfloor$ 且 $l\bmod i\not=0$ 时无解。

依次解出 $a[i]$ 即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100000
int t;
int n;
long long l;
long long r;
long long x;
bool ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1708B_1.in","r",stdin);
	freopen("CF1708B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%lld%lld",&n,&l,&r);
		if(n==1){
			printf("YES\n%lld\n",l);
			continue;
		}
		ans=true;
		for(int i=1;i<=n;++i){
			if(l/i==r/i&&l%i!=0){
				ans=false;
				break;
			}
		}
		if(!ans)printf("NO\n");
		else{
			printf("YES\n");
			for(int i=1,x;i<=n;++i){
				x=l/i*i;
				if(x<l)x+=i;
				printf("%d ",x);
			}
			printf("\n");
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80119021)

By **dengziyue**

---

## 作者：cachejtt (赞：0)

## 题意
构造一个长度为 $n$ 的序列，使得每一项都满足 $l \le a_i \le r$，同时需要序列的 $\operatorname {gcd}(i,a_i)$ 各不相同。


## 思路
### 性质
注意到我们需要 $\operatorname {gcd}$ 各不相同，而每个 $\operatorname {gcd}$ 仅跟 $i$ 与 $a_i$ 有关，由于我们需要去构造 $a_i$，因此考虑 $i$ 的关系。

由于在一个数列中，$i$ 一定是各不相同的，所以我们构造时需要按照 $i$ 去构造。

注意到 $\operatorname {gcd}(i,k \times i)=i$ 故只需使 $a_i=k \times i$ 即可。

因此我们只需判断在 $l$ 到 $r$ 间是否有 $i$ 的倍数即可。

### 方法
1. 若 $l \bmod i=0$ 则取 $l$ 即可；
1. 否则，令 $re=l \bmod i$，只需取 $l+i-re$ 即可；
1. 在第二点中注意，若该值超过 $r$，则为不可行。

注意除法运算时的错误。
## 代码
```cpp
#include<bits/stdc++.h> 
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define int ll
using namespace std;
int n,l,r,t,flag,ans[100005]; 
signed main(){
  std::ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>l>>r;
    flag=1;
    memset(ans,0,sizeof(ans));
    rep(i,1,n){
      if(l%i==0 || (l/i+1)*i<=r){
        if(l%i==0)ans[i]=l;
        else ans[i]=l+i-l%i;
      }
      else flag=0;
    }
    if(flag==1){
      cout<<"YES"<<endl;
      rep(i,1,n)cout<<ans[i]<<" ";
      cout<<endl;
    }
    else cout<<"NO"<<endl;
  }
  return 0;
}
```

---

## 作者：zhicheng (赞：0)

### 思路

题目中要求所有的 $\gcd(i,a_i)$ 都不同，所以最简单的情况就是它们都为 $i$。这说明 $a_i$ 是 $i$ 的倍数。所以我们就判断 $l$ 到 $r$ 中间有没有 $i$ 的倍数即可。具体见代码。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[100010];
int main(){
	int n,a,l,r,p;
	scanf("%d",&n);
	while(n--){
		p=0;
		scanf("%d%d%d",&a,&l,&r);
		for(int i=1;i<=a;i++){
			ans[i]=int(ceil(l*1.0/i)*i);  //求出最小的倍数
			if(ans[i]>r){  //最小的也大了
				p=1;  //无法实现
				break;
			}
		}
		if(p==1){
			printf("NO");
		}
		else{
			printf("YES\n");
			for(int i=1;i<=a;i++){
				printf("%d ",ans[i]);  //能实现
			}
		}
		printf("\n");
	}
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

显然，两个正整数的最大公因数，最小为 $1$，最大为这两个数中最小的。

再考虑到 $gcd(i,a_i)$ 必须互不相同，我们不难推出，符合题目要求的 $a_i$ 会使 $gcd(i,a_i)=i$。

因此，我们可以发现，$a_i$ 一定是 $i$ 的倍数。

不难发现，如果 $\left \lfloor l\div i \right \rfloor \ne \left \lfloor r\div i \right \rfloor$ 或 $l$ 是 $i$ 的倍数，则 $l$ 和 $r$ 之间一定有数字是 $i$ 的倍数，否则就是没有。

知道了这些，代码就不难写了。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int n,l,r;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		bool flag=true;
		scanf("%d%d%d",&n,&l,&r);
		for(int i=1;i<=n;i++)
		{
			if(l/i==r/i&&l%i!=0)//判断
			{
				flag=false;
				break;
			}
		}
		if(!flag)
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
			for(int i=1;i<=n;i++)//输出，构造i的倍数。
			{
				int a=l/i*i;
				if(a<l)
				{
					a+=i;
				}
				printf("%d ",a);
			}
			printf("\n");
		}
	}
	return 0;
}

```


---

## 作者：_Andy_Lin_ (赞：0)

有一个结论： $\gcd(i,a_i)=i$

理由如下：

显然， $\gcd(i,a_i)\le i$

因此，所有 $\gcd$ 都不大于 $n$

而 $\gcd$ 也只有 $n$ 个，所以分别为 $1,2,3,\cdots n$

知道这项结论之后，这道题就很简单了，直接对于每一个 $i$ ，找到一个在 $l,r$ 范围内的 $i$ 的倍数即可。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100001
int T,n,l,r,a[N];
bool ok;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&l,&r);ok=0;
		for(int i=1;i<=n;++i){
			int x=r/i;
			if(x*i>=l)a[i]=x*i;
			else ok=1;
		}
		if(ok==1)puts("NO");
		else{
			puts("YES");
			for(int i=1;i<=n;++i)printf("%d ",a[i]);
			putchar('\n');
		}
	}
	return 0;
}

```

---

## 作者：wzy2021 (赞：0)

由最大公因数，$\gcd(i,a_i) \leq i$，即 $\gcd(1, a_1) = 1$，

而 $\gcd(2, a_2) \leq 2$，所以 $\gcd (2, a_2) = 2$，（因为 $1 = \gcd(1, a_1) \ne \gcd (2, a_2)$）。

即可推出：$\gcd (i, a_i) = i$，即 $i \mid a_i$，

所以只需在区间 $[L, R]$ 中找到第一个整除 $i$ 的数即可。

~~~cpp
#include <map>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;

int a[N];
map <int, bool> mp;

int main() {
	int T; scanf ("%d", &T);
	while (T--) {
		int n, l, r; scanf ("%d%d%d", &n, &l, &r);
		bool flag = false;
		for (int i = 1; i <= n; ++i) {
			long long use = ceil (1.0 * l / i) * i;
			if (use > r) {
				flag = true; break;
			}
			a[i] = use;
		}
		if (!flag) {
			printf ("YES\n");
			for (int i = 1; i <= n; ++i) {
				printf ("%d ", a[i]);
			}
			printf("\n");
		} else printf("NO\n");
	}
	return 0;
}
~~~
考场上的我考虑成 $a_i$ 互不相同，挂了好 2 次。

---

## 作者：Unnamed114514 (赞：0)

对于 $\gcd(a,b)=k$ 的条件为 $a\geq k,b\geq k$，那么，为了保证值域最小，选择 $[1,i]$。

对于 $\gcd(a_i,i)=i$ 的情况，只有 $a_i\bmod i=0$，所以 $i\in[l,r]$。

然后输出 $i$ 在 $[l,r]$ 中的倍数即可。

---

