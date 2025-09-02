# Square

## 题目描述

一张纸上画着一个正方形，正方形的边等于 $n$ 米。约翰·多伊在广场周围画十字。约翰在广场左下角画第一个十字。然后约翰沿着正方形的周长按顺时针方向移动（先向上，然后向右，然后向下，然后向左，依此类推）。每次他走 $n+1$ 米时，他都会画一个十字（详见图片）。

只有当广场左下角有两个十字时，他才会停下来。约翰将画几个十字？

图中显示了约翰为一个 $4$ 边的正方形画十字的顺序。左下角有两个十字架。约翰画了 $17$ 个十字架。

## 说明/提示

对于所有数据，$1\leq t \leq 10^4$，$1 \leq n_i \leq 10^9$。
请不要使用 `%lld` 来读取或输出 C++ 中的64位整数，最好使用`cin`、`cout`或者`%I64d` 说明符。

Translated by Maxwang.

## 样例 #1

### 输入

```
3
4 8 100
```

### 输出

```
17
33
401
```

# 题解

## 作者：囧仙 (赞：1)

## 题目大意

一个边长为$n$的正方形广场。现在沿着广场的边缘，每走$n+1$个单位就会画一个十字，直到在起点处又画了一个十字。询问一共画了多少个十字。

## 题解

一道比较简单的数学题……其实并不需要找规律也能很容易地写出来。

显然，正方形广场的边长为$4\times n$。也就是说，我们要计算出最小的$m$，使得

$$m\times (n+1)\equiv 0\pmod{4\times n}$$

换句话说，假设我们绕着广场走了$k$圈，就有

$$m\times (n+1)=k\times 4\times n$$

经过移项，可得：

$$m=\frac{k\times 4\times n}{n+1}$$

我们就是要求出使得这个分数为正整数的最小的正整数$k$。显然$n$与$n+1$互质。我们可以讨论$n+1$与$4$的关系。若互质，则$k=n+1$；若$4|n+1$，则$k=\frac{n+1}{4}$。若$4$与$n+1$有一个公因数$2$，则$k=\frac{n+1}{2}$。

答案就是$m+1$。

## 参考代码

```
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
int n,k;
int main(){
    dn(qread(),1,T){
        n=qread();
        if((n+1)%4==0) k=(n+1)/4; else
        if((n+1)%2==0) k=(n+1)/2; else
        k=n+1; printf("%lld\n",((LL)k*4*n)/(n+1)+1);
    }
    return 0;
}
```

---

## 作者：xukuan (赞：1)

在杭州学军中学的OJ上刷到过一道一模一样的题，但我这道提还是错了两次

这题直接找规律难度很大，每一个输入输出都只有一个数，所以考虑暴力打标法+瞪眼法找规律

暴力打标的代码我就不放了，纯模拟即可

规律就是对4取余的余数不同导致结果不同

最终代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,x;

int main(){
    while(scanf("%lld",&n)!=EOF){
        while(n--){
            scanf("%lld",&x);
            if(x%2==1){
                ll tmp=x/2;
                if(tmp%2==1) cout<<x+1<<endl;
                else cout<<2*x+1<<endl;
            }
            else cout<<4*x+1<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Mine_King (赞：0)

在我的[博客](https://www.cnblogs.com/mk-oi/p/14032947.html)观看效果更佳。

## Problem

[CF194B Square](https://www.luogu.com.cn/problem/CF194B)

## Solution

这是一道比较有趣的数学题。  
我们设结果为 $x+1$，为什么 $+1$ 呢？为的是后面好计算。这里加的 $1$ 是最开始放的那个。  
容易看出题意就是从 $0$ 开始，每次加 $n+1$ 再对 $4n$ 取模，直到变成 $0$ 为止。问这样的操作要几次。于是可以列出下面这个方程：
$$x(n+1) \equiv 0 \pmod{4n}$$
$$xn+x \equiv 0 \pmod{4n}$$
到这里好像没有头绪了……  
可以想到结果应该是和 $4$ 有关的，于是我们可以分类讨论下。  

（由于题目要求，算出来的都是最小正整数解，所以下面直接用 $=$ 了QAQ）

当 $n \equiv 0 \pmod 4$ 时，显然
$$xn \equiv 0 \pmod{4n}$$
所以 $x \equiv 0 \pmod{4n}$，容易得到
$$x=4n$$

当 $n \equiv 1 \pmod 4$ 时，可以像上面那样算出 $x+x \equiv 0 \pmod{4n}$，所以又可以得到
$$2x=4n$$
$$x=2n$$

当 $n \equiv 2 \pmod 4$ 时，又可以得到 $2x+x \equiv 0 \pmod{4n}$，此时可以得到
$$x=\frac{4}{3}kn$$
显然题目要让 $k$ 尽量小且结果为正整数，所以 $k=3$，于是就能得到
$$x=4n$$

当 $n \equiv 3 \pmod 4$ 时，可以得到
$$3x+x \equiv 0 \pmod{4n}$$
$$x \equiv 0 \pmod n$$
$$x=n$$

整理一下就是：

- 当 $n \bmod 4=0$时，$ans=4n+1$
- 当 $n \bmod 4=1$时，$ans=2n+1$
- 当 $n \bmod 4=2$时，$ans=4n+1$
- 当 $n \bmod 4=3$时，$ans=n+1$

$ans$ 表示题目要求的答案。  

## code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long T,n;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		switch(n%4)
		{
			case 0:printf("%lld\n",4*n+1);break;
			case 1:printf("%lld\n",2*n+1);break;
			case 2:printf("%lld\n",4*n+1);break;
			case 3:printf("%lld\n",n+1);break;
		}
	}
	return 0;
}
```

---

## 作者：btng_smith666 (赞：0)

翻了同学的提交记录，找到了这道题，说实话不知道他是怎么找出这道“宝藏题”的（（（

------------

题意：绕着边长为 $n$ 米的正方形以一定速度（每次 $n+1$ 米）转圈，转到原点就停下，记录次数。

随便手动模拟一下列个表：

| $n$ | $ans$ |
| :----------: | :----------: |
| $1$ | $3$ |
| $2$ | $9$ |
| $3$ | $4$ |
| $4$ | $17$ |
| $5$ | $11$ |
| $6$ | $25$ |
| $7$ | $8$ |
| $8$ | $33$ |

规律很显然，可以通过对 $n$ $\bmod$ $4$ 来找到答案。

再列个表：

| $n\%4$ | $n$ | $\text{规律}$ |
| :----------: | :----------: | :----------: |
| $1$ | $1,5$ | $ans=2n+1$ |
| $2$ | $2,6$ | $ans=4n+1$ |
| $3$ | $3,7$ | $ans=n+1$ |
| $4$ | $4,8$ | $ans=4n+1$ |

然后就可以愉快地水掉这道蓝题了呢~

$\text{Code}$ ：

```cpp
#include<bits/stdc++.h>//Rp++
using namespace std;
long long t,n;
int main()
{
	while(scanf("%lld",&t)!=EOF)
		while(t--)
		{
        	scanf("%lld",&n);
        	switch(n%4)//规律部分 
        	{
        		case 1:printf("%lld\n",2*n+1);break;
        		case 2:printf("%lld\n",4*n+1);break;
        		case 3:printf("%lld\n",n+1);break;
        		case 0:printf("%lld\n",4*n+1);break;
        		//default:break;
			}
		}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 题意-思路
一个边长为 $n$ 的正方形广场。现在沿着广场的边缘，每走 $n+1$ 个单位就会画一个十字，直到在起点处又画了一个十字。询问一共画了多少个十字。
规律题，判断 $n$ 边长的奇偶性，当 $n$ 为偶数时输出 $4\times n+1$ ，当 $n$ 为奇数时，判断 $(n-1)/2$ 的奇偶性，若 $(n-1)/2$ 为奇数，输出 $n+1$ ，若 $(n-1)/2$ 为偶数，输出 $2\times n+1$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        if(n%2==0)cout<<4*n+1;//当n为偶数时输出4*n+1
        else if(n%4==1)cout<<2*n+1;
        else cout<<n+1;//若(n-1)/2为奇数输出 n+1.
    }
  return 0;
}
```


---

