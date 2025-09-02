# Lost Arithmetic Progression

## 题目描述

很久以前，你想到了两个有限的[等差级数](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E7%BA%A7%E6%95%B0) $A$ 和 $B$。然后你发现另一个序列 $C$ 包含了 $A$ 和 $B$ 的所有公有元素。不难看出， $C$ 也是一个有限等差数列。

许多年后，你忘记了 $A$ 是什么，但还记得 $B$ 数列和 $C$ 数列。出于某种原因，你决心找到这个丢失的等差数列。在你开始这个永恒搜索之前，你想知道有多少个不同的有限等差数列可以作为你丢失的数列 $A$。

如果两个等差数列的第一项、公差数或项数不同，则认为它们不同。

有可能有无限多这样的数列，在这种情况下，你不需要尝试找到它们！你只要直接输出 $-1$。

即使它们的数量有限，答案也可能非常大。你只需要求对 $10^9+7$ 取模的答案。

## 说明/提示

对于第一个测试用例，$B=\{-3,-2,-1,0,1,2,3\}$、$C=\{-1,1,3,5\}$，不存在等差数列 $A$，因为 $5$ 不存在于 $B$ 中，所以 $5$ 也不应该存在于 $C$ 中。

对于第二个测试用例，$B=\{-9,-6,-3,0,3,6,9,12,15,18,21\}$、$C=\{0,6,12\}$，有 $10$ 个可能的等差数列 $A$：

- $\{0,6,12\}$
- $\{0,2,4,6,8,10,12\}$
- $\{0,2,4,6,8,10,12,14\}$
- $\{0,2,4,6,8,10,12,14,16\}$
- $\{-2,0,2,4,6,8,10,12\}$
- $\{-2,0,2,4,6,8,10,12,14\}$
- $\{-2,0,2,4,6,8,10,12,14,16\}$
- $\{-4,-2,0,2,4,6,8,10,12\}$
- $\{-4,-2,0,2,4,6,8,10,12,14\}$
- $\{-4,-2,0,2,4,6,8,10,12,14,16\}$

对于第三个测试用例，$B=\{2,7,12,17,22\}$、$C=\{7,12,17,22\}$，有无限多个可能的等差数列 $A$：

- $ \{7,12,17,22\} $
- $ \{7,12,17,22,27\} $
- $ \{7,12,17,22,27,32\} $
- $ \{7,12,17,22,27,32,37\} $
- $ \{7,12,17,22,27,32,37,42\} $
- $ \ldots $

## 样例 #1

### 输入

```
8
-3 1 7
-1 2 4
-9 3 11
0 6 3
2 5 5
7 5 4
2 2 11
10 5 3
0 2 9
2 4 3
-11 4 12
1 12 2
-27 4 7
-17 8 2
-8400 420 1000000000
0 4620 10```

### 输出

```
0
10
-1
0
-1
21
0
273000```

# 题解

## 作者：Polaris_Australis_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1673D)

## 题意
$A,B,C$ 三个等差数列，给定 $B$ 和 $C$ 的首项、公差、项数，求有多少种可能的 $A$，满足 $C$ 是 $A$ 与 $B$ 的交。
## 做法
首先，先来判断那些一定无解的情况：

1. $C$ 的公差不是 $B$ 的公差的倍数；

2. $C$ 与 $B$ 根本不相交；

3. $C$ 中元素 $B$ 中没有——即 $C$ 的边界比 $B$ 的边界远

这三种情况容易证明都一定没有解，之后要考虑无穷解：当 A 的某一端可以无限延伸，就是无穷。

对于判定无穷解，本蒟蒻提供一种做法：把 $C$ 的左右端点各扩展一个数，如果这两个数有一个数不在 $B$ 的值域范围内，就代表 $A$ 无穷解，因为这样 $A$ 可以无限延伸。

最后是判断解的数量，容易证明，$A$ 的公差一定是 $C$ 的公差的约数，这样就可以枚举 $C$ 的约数，判断它与 $B$ 是否有其他交点，如果没有就统计答案。

判断是否有其他交点：设此时 $A$ 的公差为 $d_A$，B 的公差为 $d_B$，$C$ 的公差为 $d_C$，若 $\gcd(d_C/d_A,d_C/d_B)=1$ 则没有其他交点。

证明：可以把上边的做法想象成：把长度为 $d_C$ 的线段分成每段长度都是 $d_A$ 的若干段，对 $B$ 同理，这样分割点就是序列中的数，如果段数的最大公约数是 $1$，就代表中间没有分割点相交，也就是没有其他相等的数。

统计答案的个数：多端点有 $d_C/d_A$ 种情况，右端点同理，平方就好了。

## 代码
```cpp
#include<bits/stdc++.h>
//#define ll long long
#define mod 1000000007
#ifndef ll
#define int long long
#endif
#define db double
#define eps (1e-11)
using namespace std;
namespace Std
{
    template<typename tp>
    void read(tp &x)
    {
        x=0;
        tp nev=1;
        char c=getchar();
        while(c<'0'||c>'9')
        {
            if(c=='-')nev=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')
        {
            x=(x<<1)+(x<<3)+(c^48);
            c=getchar();
        }
        x*=nev;
    }
    template<typename tp>
    void write(tp x)
    {
        if(x<0)
        {
            putchar('-');
            write(-x);
            return;
        }
        if(x/10)write(x/10);
        putchar((x%10)^48);
    }
    int n,a1,b1,c1,a2,b2,c2;
    int gcd(int x,int y)
    {
        return (!y)?x:gcd(y,x%y);
    }
    int main()
    {
        read(n);
        while(n--)
        {
            read(a1);
            read(b1);
            read(c1);
            read(a2);
            read(b2);
            read(c2);
            if(b2%b1!=0||a2<a1||a1+b1*(c1-1)<a2+b2*(c2-1)||(a2-a1)%b1!=0)//无解
            {
                puts("0");
                continue;
            }
            if(a1+b1*(c1-1)-a2-b2*(c2-1)<b2||a2-a1<b2)//无穷解
            {
                puts("-1");
                continue;
            }
            int ans=0;
            for(int i=1;i*i<=b2;++i)
            {
                if(b2%i==0)
                {
                    int j=b2/i;
                    if(gcd(b2/b1,j)==1)
                    {
                        ans+=j*j;
                        ans%=mod;
                    }
                    if(gcd(b2/b1,i)==1)
                    {
                        ans+=i*i;
                        ans%=mod;
                    }
                    if(j==i&&gcd(b2/b1,i)==1)
                    {
                        ans-=i*i;
                        ans%=mod;
                        ans+=mod;
                        ans%=mod;
                    }
                }
            }
            printf("%lld\n",ans);
        }
        return 0;
    }
}
#ifdef int
#undef int
#endif
int main()
{
    return Std::main();
}
```


---

## 作者：Argon_Cube (赞：2)

* **【题目链接】**

[Link:CF1673D](https://www.luogu.com.cn/problem/CF1673D)

* **【解题思路】**

以下称某个等差数列 $a$ 的首项为 $a_0$，公差为 $a_d$，项数为 $a_c$，第 $i$ 项为 $a_i=a_0+ia_d(i\in \mathbb Z)$，如第 $-1$ 项为 $a_{-1}=a_0-a_d$。注意，这里的项数，指的是题目中给出的项数，也即我们认为等差数列中**真实存在**的项的数量，也就是说 $a_{-1}$ 与 $a_{a_c}$ 并不存在，但是 $a_{a_c-1}$ 与 $a_0$ 存在。

首先判掉两类特殊情况：$0$ 和 $-1$。

首先判 $0$，即 $C$ 有元素不在 $B$ 中。有 $4$ 种情况（对应代码）：

* $C_0$ 不在 $B$ 中
* $C_0<B_0$
* $C_1$ 不在 $B$ 中
* $C_{C_c-1}>B_{B_c-1}$

再判 $-1$，如果满足下面的两个条件则 $A$ 可以向某一段无限延长：

* $C_{-1}<B_0$
* $C_{C_c}>B_{B_c-1}$

接下来就能计算答案了。显然，$C$ 为一个等差数列，而又显然，$C_d=\operatorname{lcm}(A_d,B_d)$。枚举 $d|B_d$，显然所有满足条件的 $A_d$ 均能表示为 $\dfrac{dC_d}{B_d}$，**但是不是每个 $d$ 都能满足 $\operatorname{lcm}\left(\dfrac{dC_d}{B_d},B_d\right)=C_d$**，所以要检查这个枚举到的 $d$ 是否合法。

有了 $A_d$，显然 $C_0\leq A_i\leq C_{C_c-1}$ 的那一部分已经定下来了，主要就是看两边能延长多少。注意到，除了 $C_0\leq A_i\leq C_{C_c-1}$ 的部分，两边延长的长度都可以为 $0\sim \dfrac{C_{d}}{A_d}$，即有 $\left(\dfrac{C_{d}}{A_d}\right)^2$ 种选择。

于是答案即为 

$$\sum_{\operatorname{lcm}(A_d,B_d)=C_d}\left(\frac{C_{d}}{A_d}\right)^2$$

复杂度 $\mathrm O(T\sqrt{B_d}\log C_d)$。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

const long long moder=1000000007;

template<typename type>
type gcd(type a,type b)
{
    return b?gcd(b,a%b):a;
}

template<typename type>
type lcm(type a,type b)
{
    return a*b/gcd(a,b);
}

int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		long long B_0,B_d,B_c,C_0,C_d,C_c;
		cin>>B_0>>B_d>>B_c>>C_0>>C_d>>C_c;
		if((C_0-B_0)%B_d||C_0<B_0||(C_0+C_d-B_0)%B_d||C_0+(C_c-1)*C_d>B_0+(B_c-1)*B_d)
		{
			cout<<"0\n";
			continue;
		}
		if(C_0-C_d<B_0||C_0+C_c*C_d>B_0+(B_c-1)*B_d)
		{
			cout<<"-1\n";
			continue;
		}
		long long lcm_extra=C_d/B_d,answer=0;
		for(long long i=1;i*i<=B_d;i++)
		{
			if(B_d%i)
				continue;
			long long A_d=lcm_extra*i;
			if(lcm(A_d,B_d)==C_d)
				answer=((C_d/A_d)*(C_d/A_d)+answer)%moder;
			if(i*i!=B_d)
				A_d=lcm_extra*(B_d/i),lcm(A_d,B_d)==C_d&&(answer=((C_d/A_d)*(C_d/A_d)+answer)%moder);
		}
		cout<<answer<<'\n';
	}
 	return 0;
}
```

---

