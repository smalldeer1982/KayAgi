# Marin and Anti-coprime Permutation

## 题目描述

Marin wants you to count number of permutations that are beautiful. A beautiful permutation of length $ n $ is a permutation that has the following property: $ $$$ \gcd (1 \cdot p_1, \, 2 \cdot p_2, \, \dots, \, n \cdot p_n) > 1,  $ $  where  $ \\gcd $  is the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor</a>.</p><p>A permutation is an array consisting of  $ n $  distinct integers from  $ 1 $  to  $ n $  in arbitrary order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation ( $ 2 $  appears twice in the array) and  $ \[1,3, 4\] $  is also not a permutation ( $ n=3 $  but there is  $ 4$$$ in the array).

## 说明/提示

In first test case, we only have one permutation which is $ [1] $ but it is not beautiful because $ \gcd(1 \cdot 1) = 1 $ .

In second test case, we only have one beautiful permutation which is $ [2, 1] $ because $ \gcd(1 \cdot 2, 2 \cdot 1) = 2 $ .

## 样例 #1

### 输入

```
7
1
2
3
4
5
6
1000```

### 输出

```
0
1
0
4
0
36
665702330```

# 题解

## 作者：zyl1543130456 (赞：3)

## 题意
给定整数 $ n $ ，求存在多少个 $ 1 $ 到 $ n $的排列 $ A $ ，使 $ \gcd ( 1 \times A_1 , 2 \times A_2 , ... n \times A_n ) $

## 题目思路

显然，这是一道数学题，但是不会想正解也不怕（主要是我不会推正解），这种只输入一个数字的一般都是找规律题，因此我们只要打个长度较小的表就可以尝试着找规律了。

打完表后即可发现当数列的长度 $ n $ 为单数时，是没有答案的。当数列的长度 $ n $ 为偶数时，答案的数字都是某个数的平方。

打表结果如下

$ 0 \ 1 \ 0 \ 4 \ 0 \ 36 \ 0 \ 576 \ 0 \ 14400 $

可以发现，答案分别是 $ 1 , 2 , 6 , 24 , 120 $ 的平方。

我们此时再针对这串 $ 1 , 2 , 6 , 24 , 120 $ 数字进行找规律，发现每一个数与前一个数的成倍数关系，并且倍数依次加 $ 1 $ 。所以，紧接着我们就可以按照找到的规律写了。

之后发现样例的最下面有一个大样例，把样例输进去，对照一下输出，发现是正确的。因此直接开冲。

这里就放一下打表的代码好了。

```c++
void dabiao(){
	n=10;
		for(int i=1;i<=n;i++){
			a[i]=i;
		}
		for(int i=1;i<=n;i++){
			int ans=0;
			while(next_permutation(a+1,a+1+i)){
				int res=a[1];
				for(int j=2;j<=i;j++){
					res=gcd(res,a[j]*j);
				}
				if(res>1) ans=(ans+1)%998244353;
			}
			printf("%d\n",ans);
	}
}
```


---

## 作者：Jerrlee✅ (赞：1)

## 题意
见原题。
## 思路
需要分类讨论。

我们需要 $i \times p_i$ 的每一个值的奇偶性一样。

分奇偶两类看：

- $n$ 为奇，会发现肯定有一个 $i \times p_i$ 是奇乘偶的形式，但是 $n$ 为奇数，所以一定不可能，输出 $0$。

- $n$ 为偶，尝试让每一个奇数乘以偶数，这样所有的 $i \times p_i$ 的值都是偶数。

记得取模。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n,ans=1;
		cin>>n;
		if(n%2){cout<<"0\n";continue;}
		for(int i=2;i<=n/2;i++){
			ans*=i*i;
			ans%=998244353;
		}
		cout<<ans<<endl;
	}
}
```
[AC 记录](https://www.luogu.com.cn/record/72730895)

---

## 作者：JS_TZ_ZHR (赞：1)

## 题意:

给定 $n$，问有多少个 $1$ 到 $n$ 的排列 $p$ 满足 $\gcd(p_1,2\times p_2,\dots,n\times p_n)>1$。

## 题解：

对于质数 $p$，$1$ 到 $n$ 中有 $\lfloor\frac{n}{p}\rfloor$ 个 $p$ 的倍数，而若 $p|\gcd(p_1,2\times p_2,\dots,n\times p_n)$，那么剩余的 $n-\lfloor\frac{n}{p}\rfloor$ 个数就要安排在下标为 $p$ 的倍数的位置上，这个数目也是 $\lfloor\frac{n}{p}\rfloor$。故 $n-\lfloor\frac{n}{p}\rfloor\le \lfloor\frac{n}{p}\rfloor$， $n\le 2\lfloor\frac{n}{p}\rfloor$，所以 $\gcd(p_1,2\times p_2,\dots,n\times p_n)$ 只能等于二且 $n$ 为偶数。此时奇数安排下标为偶数的位置，偶数相反，方案数为 $((n/2)!)^2$。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
#define mod 998244353
using namespace std;
int T,n,ans=1,a[N],gcd;
 
signed main() {
	cin>>T;
	while(T--){
		cin>>n;
		if(n&1)cout<<0<<endl;
		else {
			for(int i=2;i<=n;i+=2){
				int tmp=i/2;
				ans=(ans*tmp)%mod;
				ans=(ans*tmp)%mod;
			}
			cout<<ans<<endl;
			ans=1;
		}
	}
}
```


---

## 作者：IvanZhang2009 (赞：1)

## 题意
问

有多少个长度为 $n$ 的全排列 $p_1,p_2,p_3,...,p_n$

使得 $\gcd(1\cdot p_1,2\cdot p_2,3\cdot p_3,...,n\cdot p_n)>1$。

对 998244353 取模。

## 解法
我们可以设 $\gcd(1\cdot p_1,2\cdot p_2,3\cdot p_3,...,n\cdot p_n)=g$。

则 $1\cdot p_1,2\cdot p_2,3\cdot p_3,...,n\cdot p_n$ 都是 $g$ 的倍数。

由于其中只有 $\lfloor\frac{n}{g}\rfloor$ 个数对 $p_i$ 不做要求（前面的系数已经是 $g$ 的倍数），

而且 $p_1,p_2,p_3,...,p_n$ 中也只有 $\lfloor\frac{n}{g}\rfloor$ 个数是 $g$ 的倍数，

所以 $1\cdot p_1,2\cdot p_2,3\cdot p_3,...,n\cdot p_n$ 中最多只有 $2\cdot\lfloor\frac{n}{g}\rfloor$ 个数是 $g$ 的倍数。

很明显我们需要使 $2\cdot\lfloor\frac{n}{g}\rfloor=n$ 才行。

那么很明显只有 $g=2$ 且 $2|n$ 的时候才行。


接下来考虑结果的总数。

将偶数放在奇数位，有 $(\frac{n}{2})!$ 种情况。

同理，将奇数放在偶数位，也有 $(\frac{n}{2})!$ 种情况。

所以答案就是 $[(\frac{n}{2})!]^2$。

## 代码
注意开 ``long long``。

```cpp
  int t;
  cin>>t;
  while(t--){
    int x;
    cin>>x;
    if(x%2){
      cout<<0<<endl;
    }
    else{
      long long ans=1;
      for(int i=1;i<=x/2;i++)
      ans=(ans*i*i)%998244353;
      cout<<ans<<endl;
    }
  }

```

---

## 作者：精神小伙！ (赞：0)

## 思路：
数学题。

我们知道 $gcd(1 \times a[1],2 \times a[2],3 \times a[3] ... n \times a[n])$ 是一定 $\leq 2$ 的。

我们尝试着进行分类讨论。

1. $n$ 为奇数时

一定无解，我们直接输出 $0$ 即可。

2. $n$ 为偶数时

* 在 $i$ 为偶数，$a[i]$ 为奇数时。
* 再 $i$ 为奇数，$a[i]$ 为偶数时。

只有这两种情况可以，其它情况直接输出 $0$。

代码实现简单，几个 `if` 解决。

**注意事项**：不要忘记取模了，如果取了也过不去，那就能取的都取。

## AC CODE:
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		if(n%2==1)
		{
			cout << 0 << endl;
			continue;
		}
		else
		{
			int ans=1;
			for(int i = 1 ; i <= (n/2) ; i++)
			{
				ans=(((ans*i)%998244353)*i)%998244353;
			}
			cout << ans << endl;
		}
	}
	return 0;
}
```


---

## 作者：CodeMao (赞：0)

这是道好题，需要用到一丢丢数学知识。

**思路**：

- 显然，我们可以知道 $\gcd(p_1,2\cdot p_2,3\cdot p_3,\cdots,n\cdot p_n)\le2$ 。
  
- 证明：
  
  - 在 $1$ 至 $n$ 中最多有 $\lfloor \frac{n}{a}\rfloor$ 个 $a$ 的倍数，在 $1\cdot p_1$ 到 $n \cdot p_n$ 中也只有 $\lfloor \frac{n}{a} \rfloor$ 个 $a$ 的倍数，那么这两个结合起来就一共有 $2\times\lfloor \frac{n}{a} \rfloor$ 个 $a$ 的倍数。
    
  - 如果 $a \gt 2$ ，那么 $2\times \lfloor \frac{n}{a} \rfloor$ 就必然小于 $n$ ，那么也就不存在解。
    
- 注意：当 $n$ 为奇数时，也不存在解。
  
- 当 $n$ 为偶数时，要分两种情况：
  
  - $i$ 为偶数，$a_i$ 为奇数；
    
  - $i$ 为奇数，$a_i$ 为偶数。
    
- 显然要使用到排列组合了，即答案为 $n\div2$ 的全排列的平方，即$(A_{n \div2}^{n \div2})^2$ 。
  

思路懂了之后，下面来看看代码

```cpp
#include <cstdio>
#define mod 998244353 //定义模数
#define int long long //注意开long long,因为在乘的过程中会爆int
int t,n;
inline int factor(int n){ //求n/2的阶乘
    int ans=1;n>>=1;
    for(int i=2;i<=n;++i) ans=ans*i%mod;
    return ans%mod;
}
inline int pow(int a,int b){ //快速幂
    int ans=1;
    for(;b;b>>=1){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
    }
    return ans%mod;
}
inline void in(int &a){ //快速读入
    a=0;char ch=getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9'){
        a=(a<<1)+(a<<3)+(ch^48);
        ch=getchar();
    }
}
inline void op(int a){ //快速输出
    if(a>9) op(a/10);
    putchar(a%10+'0');
}
signed main(){
    in(t);
    while(t--){
        in(n);
        if(n&1){ //看看思路
            puts("0");
            continue;
        }
        op(pow(factor(n),2)%mod),puts("");
    }
    return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题可以使序列的第奇数个数为偶数，第偶数个数为奇数。这样，序列中的每个数乘这个数的序号就一定是偶数，最大公因数一定不小于 $2$，符合题意。

当序列的偶数数量和奇数数量不一致时，无解。

### 二、完整代码

```
#include<cstdio>
using namespace std;
const long long MOD=998244353;
int t;
long long n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld",&n);
		if(n%2)
		{
			printf("0\n");
		}
		else
		{
			long long k=n/2,ans=1;
			for(long long i=1;i<=k;i++)
			{
				ans=(((ans*i)%MOD)*i)%MOD;
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}

```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很显然，$\operatorname{gcd}(1\times a[1],2\times a[2],...,n\times a[n])\le2$。

这是因为，在 $1$ 到 $n$ 中，只有 $\lfloor\dfrac{n}{x}\rfloor$ 个数整除以 $x$，包括 $1$ 到 $n$ 和 $a[1]$ 到 $a[n]$ 中，只有 $2\times\lfloor\dfrac{n}{x}\rfloor$ 个数整除以 $x$。

一旦 $x>2$，$2\times\lfloor\dfrac{n}{x}\rfloor$ 就会小于 $n$，必定不存在解。

但是，当 $n$ 为奇数时，直接判否，因为这也没有解。

那么，当 $n$ 是偶数时，只有在 $i$ 是偶数时 $a[i]$ 是奇数且 $i$ 是奇数时 $a[i]$ 是偶数满足要求。

也就是讲，答案是 $(A^{n\div2}_{n\div2})^2$。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define mod 998244353
int t;
int n;
long long ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1658B_1.in","r",stdin);
	freopen("CF1658B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n&1){
			printf("0\n");
			continue;
		}
		n>>=1;
		ans=1;
		for(int i=1;i<=n;++i)ans=ans*i%mod;
		ans=ans*ans%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/72714216)

By **dengziyue**

---

## 作者：LOVE_Ynoi (赞：0)

## CF1658B 题解
#### 题意简述：
  给定整数 $n$,求存在多少个 $1$ 到 $n$ 的排列 $A$，使 $\gcd(A_1,2\cdot A_2,\dots,n\cdot A_n)>1$。  
#### 题目思路
我们令 $x = \gcd(A_1,2\cdot A_2,\dots,n\cdot A_n)$  
首先我们可以证明 ：  
$x \le 2$  
$1$ 到 $n$ 必定有 $\left\lfloor\dfrac{n}{x}\right\rfloor$ 个 $x$ 的倍数  
在 $A$ 中，也会有**同样多**个因为乘积而被制造出的 $x$ 的倍数  
我们贪心地将所有 $x$ 的倍数插入 $A$ 中不是 $x$ 的倍数的位置中  
那么最终有 $2\times \left\lfloor\dfrac{n}{x}\right\rfloor$ 个位置被填上了  
若 $x>2$,明显上面的式子的值小于 $n$  
所以 $x \le 2$  

所以明显，当 $n$ 为奇数时，$2\times \left\lfloor\dfrac{n}{2}\right\rfloor = n-1$，不能将  $A$ 填满，所以答案为 $0$。  

考虑当 $n$ 为偶数时的情况：  
我们可以将 $n$ 个数分为两组:   
能被 $2$ 整除的和不能被 $2$ 整除的。每组各 $\dfrac{n}{2}$ 个数字  
这两组数中的数是可以随意调换位置的。所以一组的数的排列方式就是这组数字的全排列 即 $\dfrac{n}{2}!$  
所以最终的答案就是 $(\dfrac{n}{2}!)^2$  

代码如下：
```c++
#include<bits/stdc++.h>
using namespace std;
long long fac[501];
const long long mod = 998244353;
int main(){
    int t;
    cin>>t;
    fac[1] = 1;
    for(int i = 2;i<=500;i++)
        fac[i] = (fac[i-1]*i)%mod;
    while(t--){
        long long n;
        cin>>n;
        if(n%2==1) cout<<0<<endl;
        else cout<<(fac[n/2]*fac[n/2])%mod<<endl;
    }
    return 0;
}
```



---

## 作者：让风忽悠你 (赞：0)

不难发现，当 $\gcd(1 \cdot p_1,2 \cdot p_2,\cdots,n \cdot p_n)>1$ 时，其结果最大只能为 2，即对于排列中的每一个奇数，都将它和一个偶数相乘，考虑到当 $n$ 是奇数时无法对奇数偶数做到一一对应，所以无解。

排除掉无解情况后，定义 $m=\frac{n}{2}$，即奇偶数各占一半，结果就是 ${A_m^m}^2$。

```cpp
#include<cstdio>
#include<algorithm>
#define mod 998244353
#define ll long long

using namespace std;

int T,n;
ll ans;

int main(){
	scanf("%d",&T);
	while(T--){
		ans=1ll;
		scanf("%d",&n);
		if(n%2){
			printf("0\n");
			continue;
		}
		int x=n/2;
		for(int i=1;i<=x;i++)
			ans=(ans*i)%mod;
		printf("%lld\n",(ans%mod)*(ans%mod)%mod);
	}
	return 0;
}
```


---

