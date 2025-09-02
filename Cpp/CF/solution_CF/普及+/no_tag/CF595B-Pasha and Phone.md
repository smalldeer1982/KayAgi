# Pasha and Phone

## 题目描述

构造长度为 $n$ 的电话号码，满足将其均分成长度为 $k$ 的段后，第 $i$ 段能被 $a_i$ 整除且开头不为 $b_i$ 的个数总和，答案对 $10^9+7$ 取模。

## 样例 #1

### 输入

```
6 2
38 56 49
7 3 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
8 2
1 22 3 44
5 4 3 2
```

### 输出

```
32400
```

# 题解

## 作者：BF_AlphaShoot (赞：2)

[更好的阅读体验](https://www.cnblogs.com/BFcnblogs/p/15542097.html)

容斥 + 数学

能被 $a_i$ 整除且开头不为 $b_i$ 的个数 = 能被 $a_i$ 整除的个数 - 能被 $a_i$ 整除且开头为 $b_i$ 的个数。

小于 $x$ 且被 $y$ 整除的正整数个数为 $\left\lfloor\dfrac{x-1}y\right\rfloor+1$，自证不难。

设 $mid1=\left\lfloor\dfrac{10^k-1}{a_i}\right\rfloor+1$ 表示能被 $a_i$ 整除的 $k$ 位电话号码。

加上开头为 $b_i$ 这一条件后，我们可以：能被 $a_i$ 整除且开头不大于 $b_i$ 的个数 - 能被 $a_i$ 整除且开头小于 $b_i$ 个数 = 能被 $a_i$ 整除且开头为 $b_i$ 的个数。

设 $mid2=\left\lfloor\dfrac{10^{k-1}×b_i-1}{a_i}\right\rfloor+1$，$mid3=\left\lfloor\dfrac{10^{k-1}×(b_i+1)-1}{a_i}\right\rfloor+1$，分别对应能被 $a_i$  整除且开头不大于 $b_i$ 的个数 - 能被 $a_i$ 整除且开头 小于 $b_i$ 个数。

最后得到对应式 $ans×(mid1-(mid3-mid2))$。

注意到 $b_i=0$ 时 $mid3<0$，因此需要特判，直接 $ans×(mid1-mid3)$。

View code：

```c++
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ri register int
#define il inline

const int INF=0x3f3f3f3f,N=1e5+10,MOD=1e9+7;
int n,k,len=1,ans=1;
int a[N],b[N];

namespace RW{
    il ll read(){
        ll x=0,y=1;
        char c=getchar();
        while(c<'0'||c>'9'){
            if(c=='-')
                y=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9'){
            x=x*10+c-'0';
            c=getchar();
        }
        return x*y;
    }
using namespace RW;

signed main(){
    n=read(),k=read();
    for(ri i=1;i<=n/k;i++)
        a[i]=read();
    for(ri i=1;i<=n/k;i++)
        b[i]=read();
    for(ri i=1;i<=k;i++)
        len*=10;
    for(ri i=1;i<=n/k;i++){
        int mid1=(len-1)/a[i]+1;
        int mid2=(len/10*b[i]-1)/a[i]+1;
        int mid3=(len/10*(b[i]+1)-1)/a[i]+1;
        if(!b[i])
            ans=ans*(mid1-mid3)%MOD;
        else
            ans=ans*(mid1-mid3+mid2)%MOD;
    }
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：三点水一个各 (赞：1)

### 题意：

让你构造长度为 n 的电话号码，满足将其均分成 k 段后，第 i 段能被 $a_i$ 整除且开头不为 $b_i$ 的个数总和，答案对 $10^9+7$ 取模。

### 做法：

膜你题，

电话号码允许前导0，所以 k 位号码的个数为 $10^k-1$。

所以 k 位号码且为 $a_i$ 倍数的个数为 $\lfloor\dfrac{10^k-1}{a_i}\rfloor$。

现在我们要求以 $b_i$ 开头，且能被 $a_i$ 整除的 k 位电话号码：

所以 k 位号码 且以 $b_i$ 开头的个数为 $10^{k-1}-1$。

所以 k 位号码且为 $a_i$ 倍数的个数为 $\lfloor \dfrac{10^{k-1}-1}{a_i}\rfloor$。

但是我们举一个例子：

当 $k=2,a_i=6,b_i=1$ 时，计算可得：

$num_k=\lfloor\dfrac{10^{k-1}-1}{a_i}\rfloor=\lfloor \dfrac{9-1}{6}\rfloor=1$

显然，手算可得12,18都是6的倍数，$num_k$ 应为2，该公式错误。

所以，我们应该通过两数差的形式得到 $num_k$：

$num_k=\lfloor\dfrac{(10^{k-1}\times(b_i+1)-1)}{a_i}\rfloor-\lfloor\dfrac{(10^{k-1}\times b_i-1)}{a_i}\rfloor$

对于令人谔谔的 $b_i=0$，我们还是可以用第一个公式：

$num_k=\lfloor\dfrac{(10^{k-1}-1)}{a_i}\rfloor$

综上：

$num_k=\begin{cases}{\lfloor\dfrac{(10^{k-1}\times(b_i+1)-1)}{a_i}\rfloor-\lfloor\dfrac{(10^{k-1}\times b_i-1)}{a_i}\rfloor}&b_i\ne0\\{\lfloor\dfrac{(10^{k-1}-1)}{a_i}\rfloor}&b_i=0\end{cases}$ 


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,num=1,a[100010],b[100010],Mod=1e9+7,s1,s2,s3,ans=1;
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n/k;i++)
	  scanf("%lld",&a[i]);
	for(int i=1;i<=n/k;i++)
	  scanf("%lld",&b[i]);
	for(int i=1;i<=k;i++)
	  num*=10;      //计算10^k
	for(int i=1;i<=n/k;i++)
	{
	    ll pnum=num/10;    //计算10^k
	    s1=(num-1)/a[i]+1;   //b[i]=0
	    s2=(pnum-1)/a[i]+1;     //numk被a[i]整除。
            s3=(pnum*(b[i]+1)-1)/a[i]-(pnum*b[i]-1)/a[i];   //numk 以b[i]开头且被a[i]整除
            if(b[i]==0) ans=ans*(s2-s1)%Mod; //b[i]=0 
            else ans=ans*(s2-s3)%Mod; //b[i]不等于0
	}
	printf("%lld",ans);
	return 0;
}
```

---

