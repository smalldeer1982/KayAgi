# Our Tanya is Crying Out Loud

## 题目描述

Right now she actually isn't. But she will be, if you don't solve this problem.

You are given integers $ n $ , $ k $ , $ A $ and $ B $ . There is a number $ x $ , which is initially equal to $ n $ . You are allowed to perform two types of operations:

1. Subtract 1 from $ x $ . This operation costs you $ A $ coins.
2. Divide $ x $ by $ k $ . Can be performed only if $ x $ is divisible by $ k $ . This operation costs you $ B $ coins.

 What is the minimum amount of coins you have to pay to make $ x $ equal to $ 1 $ ?

## 说明/提示

In the first testcase, the optimal strategy is as follows:

- Subtract 1 from $ x $ ( $ 9→8 $ ) paying 3 coins.
- Divide $ x $ by 2 ( $ 8→4 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 4→2 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 2→1 $ ) paying 1 coin.

The total cost is $ 6 $ coins.

In the second test case the optimal strategy is to subtract 1 from $ x $ $ 4 $ times paying $ 8 $ coins in total.

## 样例 #1

### 输入

```
9
2
3
1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
5
2
20
```

### 输出

```
8
```

## 样例 #3

### 输入

```
19
3
4
2
```

### 输出

```
12
```

# 题解

## 作者：_xbn (赞：5)

首先如果减法优于除法，那除法就，没用了，直接把这个数减到 $1$ 即可。

但如果除法更优，那我们在 $k$ 可以整除这个数时肯定肯定先除，所以每次我们只要比较一下除法和减法谁更优即可。

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 1002;
using namespace std;
int n, m, k, p, ans, sum, tot, cnt, a[N], b[N], c[N], d[N], s, q;
signed main()
{
	cin >> n >> k >> p >> q;
	m = n;
	while(m > 1)
	{
		if(m % k > 0)
		{
            int t = m / k;
            t = t * k;
            if(t == 0) t = 1;
            ans = ans + (m - t) * p;
            m = t;
			continue;
		}
		int t = m / k;
		tot = m - t;
		if(tot * p < q)
		{
			ans += (m - 1) * p;
			m = 1;
		}
		else
		{
			m = t;
			ans += q;
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：miraculously (赞：4)

分析：

这题初看时像bfs，但一看到数据范围，这题明显用数学方法做。如果除法比减法更优，也就是说 $b$ 小于 $n$ 减 $n$ 除以 $k$ 的值乘以 $a$ 的值，那么 $n$ 就除以 $k$，否则直接减到 $1$ 就可以了，因为除以 $k$ 不可能比减 $1$ 更优了，这个感性认知一下，当 $n$ 大的时候，除以 $k$ 比当 $n$ 小的时候除以 $k$ 优，所以当 $n$ 大时除以 $k$ 不优，就直接减。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a,b,ans;
signed main()
{
	scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
	if(n<k)
	return printf("%lld",(n-1)*a),0;
	while(n!=1)
	{
		ans+=n%k*a;
		n-=n%k;//使n可以被k整除
		if(b<(n-n/k)*a)
		{
			ans+=b;
			n/=k;
		}
		else
		{
			ans+=(n-1)*a;
			return printf("%lld",ans),0;
		}
	}
	printf("%lld",ans);
}
```


---

## 作者：thomas_zjl (赞：2)

# 题目大意。

给你 $4$ 个数 $n,k,a,b$。

你可以对 $n$ 进行以下二种操作。

1. 花费 $a$ 代价，将 $n$ 减一。
1. 当$n \bmod k = 0$ 时, 花费 $b$ 代价，将 $n/ k$
。

求当 $n$ 经过以上操作变为 $1$ 时。

求花费的最小代价。

# 解题思路。
 
我们可以先把 $n$ 使用一操作变为 $k$ 的倍数。

代价为 $(n \bmod k) \times a$。

接下来判断 $b$ 与 $(n-n/k) \times a$ 的大小关系。

若 $(n-n/k) \times a < b$ 那么就花费 $(n-1) \times a$ 使 $n$ 直接变为 $1$。

因为 $n/k$ 后。 下次 $ [n/k-(n/k)/k]\times a $ 一定小于 $b$。

如果 $(n-n/k) \times a > b$ 就花费 $b$ 使 $n/k$。 并重复上述操作。

# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,k,a,b;//因为数据范围，所以要开long long。
	cin>>n>>k>>a>>b;
	long long ans=0;
	while(n!=1){
		ans+=(n%k)*a;
		n=n-n%k;
		//使n变成k的倍数。
		if(b>(n-n/k)*a){
			ans+=(n-1)*a;
			break;
		}
		else{
			n=n/k;
			ans+=b;
		}
		//进行解题思路中的操作。     
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：cym_233 (赞：2)

# Codeforces 940B Our Tanya is Crying Out Loud 题解

## [题目传送门](https://www.luogu.org/problemnew/show/CF940B)

## 总的来说

这题一看就是个贪心，暴力模拟肯定T飞。贪心的难度不大，可以很自然的想到：
  
## 解题思路
   1.如果n<k 那么直接减到1，花费(n-1)*a,可以用O(1)的复杂度实现。
    
   2.如果n整除于k，那么比较是直接除花费少还是减花费少。
    直接除的花费是b，减的花费是(n-(n/k))*a
    比较二者的大小就可以了；
    
   3.如果n>k&&n不整除于k那就一直减，直到可以整除为止，可以O(1)实现。
    
   这道题的坑点在于要尽量优化代码的细节，能省去的计算一定要省去，否则一些较大的点会被卡~~（窝就被卡了）~~
   
  ##  【warning 坑点】最重要的一点 一定要特判k是1的情况，不然会卡在一个点上，望周知！！！
  
  ## 代码
  ```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,k,a,b,f1,f2,ans;
int kkk,aaa;
int main()
{
	scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
	kkk=(b-1)/a+1;
	if(k==1)
	{
		ans=(n-1)*a;
		printf("%lld",ans);
		return 0;
	}
	while(n!=1)
	{
		if(n%k==0)
		{
			f2=n-(n/k);
			if(f2>=kkk)
			{
				n=n/k;
				ans+=b;
			}
			else
			{
				n=n/k;
				ans+=f2*a;
			}
		}
		else
		{
			aaa=n/k*k;
			if(aaa==0)
			{
				ans+=(n-1)*a;
				break;
			}
			ans+=a*(n-aaa);
			n=aaa;
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：Jerry_heng (赞：1)

（一）

每次先减到不能除为止。

然后比较是除 $k$ 花费少，还是 通过不断减 $1$ 花费少。

当 $n<k$ 时只用减到 $1$ 就行了。

特判 $k=1$。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a,b,ans;
signed main(){
	scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
	if(k==1)printf("%lld",(n-1)*a);
	else if(n==1)printf("0");
	else{
		while(n>1){
			if(n<k){
				ans+=(n-1)*a;
				break;
			}
			int rest=n%k;
			ans+=rest*a;
			n-=rest;
			int nxt=n/k;
			ans+=min(b,(n-nxt)*a);
			n=nxt;
		}
		printf("%lld",ans);
	}
	return 0;
}
```

---

## 作者：kimidonatsu (赞：1)

# CF940B Our Tanya is Crying Out Loud 题解

这里省去题意简述，题意的翻译已经很明显了，我们直接来到下个环节。

## 题目分析

拿到这道题，我其实第一眼是想用 DFS 做枚举元组的，但是看了一眼数据范围 $1 \leq n, k, a, b \leq 2 \times 10^9$。暴力是不可能暴力的。

再次阅读题面后，发现其实这也是一道明显的贪心：我们只能进行减法或者除法操作，每次只要进行考虑这两步操作谁更优即可。

考虑进行优化。进行除法操作时，首先将 $n$ 减去 $n \bmod{k}$ 来保证可被 $k$ 整除，之后继续进行除法操作并输出答案。

还没完，还有一种最为特殊的情形：当 $n < k$ 时，我们只能一直减下去直到 $n = 1$（注意，这里只需要进行 $\mathcal{O}(1)$ 复杂度的直接操作即可）。

总的来说，坑点比较多，而且需要尽可能进行优化避免 T 掉。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, k, a, b;
ll ans;

void work() {
    if (n < k) {    // 特殊情况
        printf("%lld\n", (n - 1) * a);  // 只能减到 n - 1
        exit(0);
    }

    while (n != 1) {
        // 首先要将数字减到能被 k 整除
        ans += n % k * a;
        n -= n % k;

        if (b < (n - n / k) * a) {  // 除法更优
            ans += b;
            n /= k;
        } else {        // 否则减法更优
            ans += (n - 1) * a;
            printf("%lld\n", ans);
            exit(0);
        }
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%lld %lld", &n, &k);
    scanf("%lld %lld", &a, &b);
    work();
    return 0;
}

```


---

## 作者：xuhanxi_dada117 (赞：0)

[题目传送门&题目大意](https://www.luogu.com.cn/problem/CF940B)

[博客食用更佳](https://www.luogu.com.cn/blog/314516/solution-cf940b)

# Solution
首先： $k \nmid n$ 时：直接减到 $n$ 的倍数即可。

这时：

+ 使用除法：费用为 $b$。
+ 使用减：费用为 $(n-\frac{n}{k})\times a$。

进行判断即可。

## 小优化

考虑：
$$f(n)=n-\frac
{k}{n}$$

单调递减，所以只要有 $1$ 次不用除，之后都不可能。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,k,a,b,ans=0;cin>>n>>k>>a>>b;
	if(n<k){//特判
		cout<<(n-1)*a;
		return 0;
	}
	while(n>1){
		ans+=a*(n%k);n-=n%k;//直接减。
		long long j=n-(n/k);j*=a;
		if(b<j) n/=k,ans+=b;//更新
		else{//一个小优化
			cout<<ans+(n-1)*a;
			return 0;
		}
	}cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/112848681)

---

## 作者：SXqwq (赞：0)

一道贪心的好题。
   
首先看数据范围是不可能让你暴力的，考虑贪心。
    
容易发现我们只能进行两种操作，减法和除法，考虑谁更优就执行哪一步操作。
    
操作时先将数字减到可以被 $k$ 整除，然后判断除法和减法谁更优，若除法更优则进行除法操作，否则一直减到底即可。
    
具体的实现代码内有注释，如下。
```cpp

#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
ll n,k,a,b;
ll qwq=0;
int main()
{
	scanf("%lld%lld%lld%lld",&n,&k,&a,&b); 
	if(n < k) //特判，如果n<k,则只能减到底
	{
		printf("%lld\n",(n-1)*a); //注意是n-1，而不是n，下文38行同理
		return 0;
	}
	while(n!=1)
	{
		qwq+=n%k*a; //这两步是将数字减到能被k整除时，并统计答案
		n-=n%k;
		if(b < (n-n/k)*a) //如果除法更优，则进行除法操作
		{
			qwq+=b;
			n/=k;
		}
		else //否则一直减到底，输出即可
		{
			qwq+=(n-1)*a;
			printf("%lld\n",qwq);
			return 0;
		}
	}
	printf("%lld\n",qwq);
	return 0;
}

```


---

## 作者：Aisaka_Taiga (赞：0)

## 基本思路

明显的贪心。

遇到这种情况要分类讨论：

1. 当前的 $n$ 值小于 $k$ 值，只能一直减一到 $1$。

2. 当前的 $n$ 大于 $k$ 值，此时我们有两种选择，一是减一到下一个 $n-n/k$，代价为 $(n/k)\times a$，二是直接除以 $k$，代价为 $b$。

很显然在第二种情况要选花费更少的，但如果直接交上去的话会 TLE。

考虑如何优化。从上面的第二种情况可以看出如果当前的除以 $k$ 的代价 $b$ 一旦大于直接减到 $n=1$ 的花费时，后面无论如何都是减一的策略更优，因为当前的 $n$ 值肯定除以 $k$ 减少的值比后面的 $n$ 值除以 $k$ 减少的值是要多的，如果前面的除以 $k$ 的策略已经不如减一的策略优的话就说明以后也不会比减一的策略要优，所以我们此时可以直接把他给减到一输出花费，这样就不会 TLE 了。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a,b,ans;
signed main()
{
	cin>>n>>k>>a>>b;
	if(n<k)//第一种情况，n不能被k整除 
	{
		cout<<(n-1)*a<<endl;//只能一直减一到1为止 
		return 0;//好习惯 
	}
	while(n!=1)//只要n不等于1就一直循环 
	{
		ans+=n%k*a;//先减到能被k整除的情况 
		n-=n%k;//n减去已经减去的值 
		if(b<(n-n/k)*a)//如果当前整除比之间减去n/k的花费少 
		{
			ans+=b;//那就除以k 
			n/=k;//更新n的值 
		}
		else
		{
			ans+=(n-1)*a;//否则就直接减到1 
			cout<<ans<<endl;//输出答案 
			return 0;//好习惯 
		}
	}
	cout<<ans<<endl;//输出答案 
	return 0;//好习惯 
}

```


---

## 作者：tribool4_in (赞：0)

乍一看，这道题好像是 bfs 暴力，但一看数据范围直接放弃（~~似乎还真有人写暴力还发帖询问~~）。

考虑贪心。对于当前的数，如果此时直接减优于除则直接减完完事。否则考虑除，首先 $n$ 先减去 $(n\bmod k)$ 以保证 $n$ 可以整除 $k$，然后 $n$ 直接除以 $k$ 并继续。最终输出答案即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
    int s=0, w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
int n, k, a, b, ans;
signed main() {
	n = read(), k = read(), a = read(), b = read();
	if (n < k) {
        printf("%lld\n", a * (n - 1));
        return 0;
    }
	while (n ^ 1) {
		ans += a * (n % k);
		n -= (n % k);
		if (a * (n - n / k) > b) ans += b, n /= k;
		else {
            printf("%lld\n", ans + a * (n - 1));
			return 0;
		}
	}
	printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：TLMPEX (赞：0)

这道题简单的模拟一下就可以了。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	unsigned long long x,y,n,k,a,b,t=0,z=0;
	cin>>n>>k>>a>>b;//输入
	if(k==1){//如果k等于1，则直接输出（n-1）*a
		cout<<(n-1)*a;
		return 0;
	}
	while(n!=1){//当n<=1时，退出
		//以下是模拟部分
		if(n<k){
			cout<<z+(n-1)*a;
			return 0;
		}
		else if(n%k!=0){
			t=n-n/k*k;
			z+=t*a;
			n-=t;
		}
		else if(n%k==0){
			x=b,y=(n-n/k)*a;
			z+=min(x,y);
			n/=k;
		}
	}
	cout<<z;//输出
}
```

---

