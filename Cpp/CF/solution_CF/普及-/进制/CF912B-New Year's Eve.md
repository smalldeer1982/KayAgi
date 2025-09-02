# New Year's Eve

## 题目描述

Since Grisha behaved well last year, at New Year's Eve he was visited by Ded Moroz who brought an enormous bag of gifts with him! The bag contains $ n $ sweet candies from the good ol' bakery, each labeled from $ 1 $ to $ n $ corresponding to its tastiness. No two candies have the same tastiness.

The choice of candies has a direct effect on Grisha's happiness. One can assume that he should take the tastiest ones — but no, the holiday magic turns things upside down. It is the xor-sum of tastinesses that matters, not the ordinary sum!

A xor-sum of a sequence of integers $ a_{1},a_{2},...,a_{m} $ is defined as the bitwise XOR of all its elements: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/475d3a054d8c211f23a68d652dd85385e5ab9fc9.png), here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operation; more about bitwise XOR can be found [here.](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

Ded Moroz warned Grisha he has more houses to visit, so Grisha can take no more than $ k $  candies from the bag. Help Grisha determine the largest xor-sum (largest xor-sum means maximum happiness!) he can obtain.

## 说明/提示

In the first sample case, one optimal answer is $ 1 $ , $ 2 $ and $ 4 $ , giving the xor-sum of $ 7 $ .

In the second sample case, one can, for example, take all six candies and obtain the xor-sum of $ 7 $ .

## 样例 #1

### 输入

```
4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
7
```

# 题解

## 作者：BB2655 (赞：6)

此题数据还是很大的（$ 1<=k<=n<=10^{18} $）

~~注意开long long~~

以下转载于[https://www.cnblogs.com/siuginhung/p/8207658.html](https://www.cnblogs.com/siuginhung/p/8207658.html)

```
  给定两个整数n、k：在1~n中选择至多k个整数，使得其异或和最大。求解这个最大值。

  显然，当k=1时，只选择一个整数n，于是答案为n；

  当k>1时，可以考虑异或和可能达到的最大值：将n的所有可改变的二进制位（即最高的‘1’位以下的二进制位）均变为‘1’，这个值就是异或和可能达到的最大值。

  设S=2b-1，则对于任意自然数a，若a<S，则一定有aÅ(S-a)=S。由于S的二进制位，0~b-1位均为‘1’，于是根据位运算的基本规则，等式显然成立。

  于是，当k>1时，设n的最高‘1’位为b-1位，S=2b-1，则可选择两个整数：n和S-n（注意，这里n≥2b-1，于是S-n<2b-1≤n）；特别地，当n=S时，只选择一个整数n。于是答案为S。
```

通俗地说，就是尽量凑成二进制为111111...的数

附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long int n,k;
    cin>>n>>k;
    if(k==1)  //特判
    {
        cout<<n;
        return 0;
    }
    long long int b=0;
    for(;n>>b;b++)  //b为(n)2的位数（防抄袭）
    cout<<(1LL<<b)-1;  //1LL意为long long的1
    return 0;
}
```

---

## 作者：Porsche (赞：3)

发现此题数据有问题

只用特盘一下k=1的情况，其余情况直接把n分解掉就好了

时间复杂度：$\Theta(\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,k;
	scanf("%lld%lld",&n,&k);
	if(k==1)
	{
		cout<<n<<endl;
		return 0;
	}
	long long ans=0;
	for(long long i=0;n>>i;i++)
		ans+=(1LL<<i);
	cout<<ans<<endl;
	return 0;
}
```
rp++

---

## 作者：SoyTony (赞：2)

一个结论：
$$ans=\begin{cases} n,&k=1\\2^{\left\lceil\log_{2}n\right\rceil}-1,&k>1\end{cases}$$

给出证明：

如果 $k=1$，选取最大的 $n$ 为答案；

如果 $k>1$，同样先选取 $n$，记 $cnt=\left\lceil\log_{2}n\right\rceil$，因为最大的 $n$ 二进制共 $cnt+1$ 位，且最高位上为 $1$，所以在 $[1,n-1]$ 中一定存在一个 $i$，使得 $i \oplus n=2^{\left\lceil\log_{2}n\right\rceil}-1$，原因是 $i$ 的第 $cnt+1$ 位为 $0$，所以  $1\le i\le2^{cnt}-1 \le n-1$。

可以这样理解：设 $n$ 的二进制最高位 $p$，那么我们选取 $n$，设 $m=n \oplus (2^p-1)$，因为 $n$ 的第 $p$ 位为 $1$，所以实际上去掉最高位后 $m=n \oplus (2^p-1) = (n-2^p) \oplus (2^{p-1}-1)$，而 $m$ 一定在 $[1,2^{p-1}-1]$ 中，一定可以选取，所以答案为 $2^{p}-1$。

# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read(){
    ll x=0,w=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
    while(c<='9'&&c>='0'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*w;
}
ll n,k;
inline ll q_pow(ll x,ll p){
    ll ans=1;
    while(p){
        if(p&1){
            ans*=x;
        }
        x*=x;
        p>>=1;
    }
    return ans;
}
int main(){
    n=read(),k=read();
    if(k==1) printf("%lld\n",n);
    else{
        ll cnt=0,num=1;
        while(1){
            num<<=1;
            cnt++;
            if(num>n){
                break;
            }
        }
        printf("%lld\n",q_pow(2,cnt)-1);
    }
    return 0;
}
```

---

## 作者：小坦克 (赞：2)

#### [CF912B New Year's Eve](https://www.luogu.com.cn/problem/CF912B)


------------
- 分析：这道题非常的水啊，只用特判一下 $k=1$ 的情况，其余情况直接把 $n$ 分解掉就好了.


------------
- 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,k,ans=0;
	cin>>n>>k; 
	if(k==1){
		cout<<n<<endl;
		return 0;
	}
	for(long long i=0;n>>i;i++) ans+=(1LL<<i);
	cout<<ans<<endl;
	return 0;
}
```


------------
完结撒花！

---

## 作者：fisheep (赞：2)

## 题意：

在`1 ~ n`中选不超过$m$个数，求其异或最大值 

## 题解：
经过找规律发现如果$m$为$1$，输出$n$，不然输出最小的不超过$n$的$2^k-1$

## Code
```cpp
#include<cstdio>
#include<cstring>  
using namespace std; 
inline long long read() {
	long long x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
 
long long n,k,ans=1;  
int main(){  
    n=read(),k=read();
    if(k==1){
		printf("%lld\n",n);
    }else{
    	while(n>>=1) ans<<=1;
	    printf("%lld\n",(ans<<1)-1);  
	}
    return 0;  
}
```

---

## 作者：Daniel_yao (赞：1)

## 题目大意

给定两个整数 $n$，$k$，在 1 到 $n$ 中选择至多 $k$ 个整数，使得其异或和最大，求解这个最大值。

### 具体思路

- 如果 $k$ 的值为 1，那么其异或和最大的数就是 $n$ 本身；

- 如果 $k$ 的值不为 1，那么就尽量把数凑成二进制的 111111。就可以保证其异或和最大；

上代码：

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, k, num = 1;//不开 long long 见祖宗
int main(){
	cin >> n >> k;
	if(k == 1){
		cout << n << endl;
	} else {
		while(n){//分解
			num = num << 1;
			n = n >> 1;
		}
		cout << (num * 1ll) - 1 << endl;//取最大值
	}
	return 0;
}
```
$O(logn)$ 的时间复杂度，直接切掉！！

---

## 作者：GZY007 (赞：1)

这题是一道大水题。

首先考虑一下 $k=1$ 的情况，因为只能选一个数，最大的就是 $n$ ,直接输出即可。

再考虑一下 $k<1$ 的情况，因为这个异或和最多只能为 $n$ 的二进制位数里最大的，即为二进制全为一的情况，然后我们会发现，可以和 $n$ 异或成最大值的数一定比 $n$ 小，则它一定会在范围之内，可以选。所以我们只需要选两个数即可得出最大值。

代码如下：
```cpp
#include <bits/stdc++.h> 
using namespace std;
long long n,k;
int main(){
	cin>>n>>k;
	if(k==1) cout<<n;
	else{
		long long ans=1;
		for( ;n;ans*=2,n>>=1);
		cout<<ans-1;
	}
}
```


---

