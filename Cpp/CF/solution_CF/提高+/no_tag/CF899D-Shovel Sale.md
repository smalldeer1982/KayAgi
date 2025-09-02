# Shovel Sale

## 题目描述

There are $ n $ shovels in Polycarp's shop. The $ i $ -th shovel costs $ i $ burles, that is, the first shovel costs $ 1 $ burle, the second shovel costs $ 2 $ burles, the third shovel costs $ 3 $ burles, and so on. Polycarps wants to sell shovels in pairs.

Visitors are more likely to buy a pair of shovels if their total cost ends with several $ 9 $ s. Because of this, Polycarp wants to choose a pair of shovels to sell in such a way that the sum of their costs ends with maximum possible number of nines. For example, if he chooses shovels with costs $ 12345 $ and $ 37454 $ , their total cost is $ 49799 $ , it ends with two nines.

You are to compute the number of pairs of shovels such that their total cost ends with maximum possible number of nines. Two pairs are considered different if there is a shovel presented in one pair, but not in the other.

## 说明/提示

In the first example the maximum possible number of nines at the end is one. Polycarp cah choose the following pairs of shovels for that purpose:

- $ 2 $ and $ 7 $ ;
- $ 3 $ and $ 6 $ ;
- $ 4 $ and $ 5 $ .

In the second example the maximum number of nines at the end of total cost of two shovels is one. The following pairs of shovels suit Polycarp:

- $ 1 $ and $ 8 $ ;
- $ 2 $ and $ 7 $ ;
- $ 3 $ and $ 6 $ ;
- $ 4 $ and $ 5 $ ;
- $ 5 $ and $ 14 $ ;
- $ 6 $ and $ 13 $ ;
- $ 7 $ and $ 12 $ ;
- $ 8 $ and $ 11 $ ;
- $ 9 $ and $ 10 $ .

In the third example it is necessary to choose shovels $ 49 $ and $ 50 $ , because the sum of their cost is $ 99 $ , that means that the total number of nines is equal to two, which is maximum possible for $ n=50 $ .

## 样例 #1

### 输入

```
7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
14
```

### 输出

```
9
```

## 样例 #3

### 输入

```
50
```

### 输出

```
1
```

# 题解

## 作者：Register_int (赞：2)

只有最高位能影响方案数。所以首先算出最多能算出几个 $9$，再枚举最高位计算方案数即可。主意，如果最高位 $\ge5$，则还要加上一个 $9$，即最高位取 $4+5$。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, ans, t = 1;

ll x, l, r;

int main() {
	scanf("%lld", &n);
	while (t * 5 <= n) t *= 10;
	for (int i = 1; i <= 9; i++) {
		x = i * t - 1, l = max(1ll, x - n), r = min(n, x - 1);
		if (l < r) ans += (r - l + 1) >> 1;
	}
	printf("%lld", ans);
}
```

---

## 作者：A_zjzj (赞：1)

### 一道找规律题

直接找一下规律就可以了。

先算出来后面可以有多少个9，然后枚举第一位是什么，算出有多少答案就可以了。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
ll n,pow10[11];
int main(){
	pow10[0]=1;
	for(int i=1;i<=10;i++)pow10[i]=pow10[i-1]*10;
	scanf("%lld",&n);
	if(n<=4)return printf("%lld",n*(n-1)/2),0;
	ll now=5,pos=0,ans=0;
	while(n>=now){
		pos++;
		now*=10;
	}
	for(int i=0;i<9;i++){
		ll cnt=(i+1ll)*pow10[pos]-1,l=max(1ll,cnt-n),r=min(n,cnt-1);
		if(l<r)ans+=(r-l+1)/2;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

# CF899D Shovel Sale
## 题意概括
给定一个正整数 $n$，求用小于等于 $n$ 的两个正整数相加，末尾 $9$ 最多的方案数。
## 思路分析
~~天哪喵，这么复杂喵，好帕帕喵。~~   

首先，瞪眼法发现，如果两数都小于 $5 \times 10^{p}$，那么两数之和末尾 $9$ 的数量一定不超过 $p$。  
证明：$2 \times (5 \times 10^{p}-1) = 10^{p+1}-2 < 10^{p+1} -1$。  
（本人是一只蒟蒻，所以证明有点乱，可能不好理解，大家可以结合具体数据自己验证，有不严谨的地方欢迎指出。） 

回到正题，由于在已知能算出几个 $9$ 的情况下，只有最高位可以影响方案数，所以我们先计算出末尾 $9$ 数量的最大值，然后就到了本蒟蒻最喜欢的无脑暴力环节，枚举所有的最高位，同时累加方案数，最后输出即可。
## AC Code
本人是一只蒟蒻，代码有点丑，请谅解。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,s=1,a,b,e;  //int可能会炸
int main(){
    std::ios::sync_with_stdio(0);  //优化
    cin>>n;
    while (5*s<=n) s=s*10;  //5*10^s
    for (int i=1;i<=9;i++){  //枚举
        a=i*s-1;  //以i为最高位的数
        b=max(1ll,a-n); //加数较小值
        e=min(n,a-1);  //加数较大值
        if (b<e) ans+=(e-b+1)/2;  //计数  一定不要漏掉前边的if语句，这只蒟蒻因为这个卡了半天
    }
    cout<<ans;  //输出方案数
    return 0;  //完结撒花！
}
```
最后，祝大家快乐AC！  

###### ~~看完这只蒟蒻的第一篇蓝题题解，可以给一个关注吗？（我好不要脸）。~~

---

## 作者：ttq012 (赞：0)

水蓝，建议降黄。直接找规律即可。

具体的。容易发现若两数均严格小于 $5\times 10^p$，则末尾的 $9$ 的数量一定不会超过 $p$。证明：$2\times (5\times 10^p)=10\times 10^p-2<10^p-1=999\ldots99$。

直接暴力枚举即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n;
    cin >> n;
    int tmb = n << 1;
    int usb = 0, dmt = 1;
    while (dmt <= tmb) {
        usb++;
        dmt *= 10;
    }
    usb--;
    int s = 0;
    for (int i = 1; i <= 9; i++) {
        int l = max(i * dmt / 10 - n - 1, 1ll);
        int r = min(i * dmt / 10 - 2, n);
        if (l < r) {
            s += (r - l + 1) / 2;
        }
    }
    cout << s << '\n';
    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
找规律，挺基础的一道。

题意：  
输入一个 $n$ 然后求从中任选两个数，求末尾的 $9$ 的位数最多时的相加方案数。其中，允许存在 $0$ 个 $9$ 的情况。
## 分析。
我们可以稍微讨论一下。

1. 当 $<50=5\times 10^1$ 时，明显尾部最多只有一个 $9$。
2. 当 $<500=5\times 10^2$ 时，尾部最多两个 $9$。
3. 当 $<5000=5\times 10^3$ 时，尾部最多三个 $9$。

以此类推，可以发现，只需要判断当前的数与 $5\times 10^x$ 做比较即可判断尾部最多有多少个 $9$ 即 $x$ 个。

显而易见，我们可以设当前输入 $n$ 的时候，其中一对数尾部最多有 $x$ 个 $9$。设 $res$ 为尾部有 $x$ 个 $9$ 的各个可能取值。

分类讨论即可。当 $n<5$ 时显然无论如何都是 $0$ 个 $9$ 所以特判即可。这里就是个单循环问题，可以套公式。然后去按照上面的方法去推断其它情况即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
long long n;
long long k=5,sum1,sum2,cut,ans;
long long res;
int main(){
    cin>>n;
    if(n<5){
        cout<<n*(n-1)/2<<"\n";
    }
    else{
    	sum1=1;
		sum2=0;
        while(k*10<=n){
		    k*=10;
			cut++;
		}
        for(int i=0;i<=cut;i++){
            sum2=sum2*10+9;
            sum1*=10;
        }
        for(int i=0;i<=8;i++){
            res=i*sum1+sum2;
            if(res>2*n-1){
			    break;//即r>n+(n-1)的情况。
			}
            else if(res<n+1){
			    ans+=res/2;
			}
            else if(res<2*n){
				ans+=(2*n-res+1)/2;
			}
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

