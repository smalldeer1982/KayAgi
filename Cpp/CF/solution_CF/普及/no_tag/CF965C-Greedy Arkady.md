# Greedy Arkady

## 题目描述

$k$ 个人想在他们之间分 $n$ 颗糖。每颗糖都应该正好分给其中一个人，否则就扔掉。

这些人的编号从 $1$ 到 $k$，Arkady 是他们中的第一个。为了分割糖果，Arkady 将选择一个整数 $x$，然后把前 $x$ 颗糖果给自己，下一堆 $x$ 颗糖果给第二个人，再下一堆 $x$ 颗糖果给第三个人，如此循环。剩下的部分（不能被 $x$ 整除的剩余部分）将被扔掉。

Arkady 不能选择大于 $M$ 的 $x$，因为这被认为是贪婪的。同时，他也不能选择这么小的 $x$，以至于有些人收到的糖果会超过 $D$ 次，因为这被认为是一种缓慢的分割。

请找出 Arkady 通过选择某个有效的 $x$ 所能得到的最大的糖果数量是多少。

## 样例 #1

### 输入

```
20 4 5 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
30 9 4 1
```

### 输出

```
4
```

# 题解

## 作者：lichenfan (赞：2)

### 贪心思路
从 $1$ 到 $d$ 枚举给人几次，因为最优的值为最后一轮只给男主，这样可以让男主拿的最多所以一共分了 $k*i-k+1$ 次，其中 $k*i$ 为如果这轮全部分完的次数，再减去除了男主的人数，因为不给他们发糖，所以为 $k-1$。     
用总共的糖数整除分的次数算出这一次给每个分几颗糖，但是要判断是否大于 $m$，最后算出男主拿到的糖果数，取最大值。之后代码就容易实现了。   
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long           //不开long long会爆 
int n,k,m,d,ans;
signed main()
{
    cin>>n>>k>>m>>d;
    for(int i=1;i<=d;i++){      //枚举最多分给人几次 
        int x=n/(k*i-k+1);      //计算x的值 
        if(x==0) break;         //如果糖分的次数比人还多， 
        x=min(x,m);             //如果比m大，就只能取m 
        ans=max(ans,x*i);       //算出男主最多拿到的糖果数 
    }
    cout<<ans;
}
```

  

---

## 作者：小恐 (赞：1)

~~咦？木有人写题解？这种好事真是多（$sh\check{a}o$）见！那我就来发一篇吧！~~

考虑到$D$非常小，于是我们可以枚举$1$~$D$，表示发了多少轮。设发了$d$轮糖。灰常明显，最终肯定是1号得到的糖最多，他得到了$d\times x$颗糖。所以对于每个$d$，我们只需要$x$最大就行，这个最大值为$min\text{\textbraceleft}m,\lfloor\dfrac {n}{(d-1)\times k+1}\rfloor\text{\textbraceright}$。

然而，数据范围有点毒瘤，硬来会爆$long~long$所以当$(d-1)\times k+1>n$时，就停止循环。但$(d-1)\times k+1$会爆$long~long$，所以要改成除法，也就是当$\lfloor\dfrac{n-1}k\rfloor<d-1$时，停止枚举。

上代码：
```cpp
#include<stdio.h>
#include<iostream>
using namespace std;
long long ans;
int main()
{
	int d;
	long long n,k,m;
	scanf("%lld%lld%lld%d",&n,&k,&m,&d);
	for(int i=1;i<=d;++i)
	{
		if((n-1)/k<i-1)
			break;
		long long t=k*(i-1)+1;
		ans=max(ans,min(m,n/t)*i);
	}
	printf("%lld",ans);
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/31068894)

---

## 作者：lxgw (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF965C)
## 题意
k 个人去分 n 颗糖，分糖方法为：按编号为 1~k 的人的顺序每次给该编号的人 x 颗糖， $x≤m$ ，同时分糖的轮数不能超过 d 轮，求1号的人最多得到多少糖果。
## 思路
因为最多分 d 轮，所以1号最多得到 $x \times d$ 颗糖，又因 $d≤1000$ ，所以可以直接枚举，每一次 x 只用取最大值就好了，其中最大值为 $x=\text {min}\text{\textbraceleft}m,\lfloor\dfrac {n}{(d-1)\times k+1}\rfloor\text{\textbraceright}$ 。

需要注意的是，由于其他数据很大，所以当 x 爆精度时，就直接结束。
## 代码
```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n,m,k,d,l,ans;
signed main()
{
    cin>>n>>k>>m>>d;
    for(register int i=1;i<=d;++i)//枚举分的次数
	{
        int x=n/(k*i-k+1);//求出x的最大值
        if(!x) cout<<ans,exit(0);//当爆精度时就直接结束。
        x=min(x,m);//x不会大于m
        ans=max(ans,x*i);//把ans取最大值，x*i指最多分i轮，每轮分x颗（即最大值）
    }
    cout<<ans;
    return 0;
}
```

完结撒花~

谢谢 qwq 。


---

## 作者：永远的黑夜 (赞：0)

~~十年OI一场空，不开long long见祖宗~~

贪心的去想 那么最优的状态一定是：小明有$y$次，那么其他人有$y-1$次得到礼品的机会。

记得开long long呦！

上代码：

```cpp
#include <iostream>
 
using namespace std;
typedef long long ll;
 
ll n,m,k,d;
ll l;
ll ans;
 
int main(){
    cin>>n>>k>>m>>d;
    for(int y = 1;y <= d;y++){
        ll x = n/(k*y-k+1);
        if(!x){
            break;
        }
        if(x > m){
            x = m;
        }
        ans = max(ans,x*y);
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：zztqwq (赞：0)

从 $1$ 到 $D$ 枚举共进行了几轮，显然当前这一轮第只分到一号能使一号拿到的糖最多，此时 $x=\lfloor \dfrac{n}{(d-1)k+1}\rfloor$。但这时有可能 $x>M$，令 $x=M$ 即可。

会爆 `long long`，于是就拿 Python 水过去了。

```python
s=list(map(int,input().split()))
n=s[0]
k=s[1]
M=s[2]
D=s[3]
ans=0
for d in range(0,D+1):
    x=n//((d-1)*k+1)
    if x>M:
        x=M
    if x*d>ans:
        ans=x*d
print(ans)
```

---

