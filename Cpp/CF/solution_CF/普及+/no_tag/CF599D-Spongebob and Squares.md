# Spongebob and Squares

## 题目描述

Spongebob is already tired trying to reason his weird actions and calculations, so he simply asked you to find all pairs of n and m, such that there are exactly $ x $ distinct squares in the table consisting of $ n $ rows and $ m $ columns. For example, in a $ 3×5 $ table there are $ 15 $ squares with side one, $ 8 $ squares with side two and $ 3 $ squares with side three. The total number of distinct squares in a $ 3×5 $ table is $ 15+8+3=26 $ .

## 说明/提示

In a $ 1×2 $ table there are $ 2 $ $ 1×1 $ squares. So, $ 2 $ distinct squares in total.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599D/9dab69eaea2bb36c546e77be3f4ad4f8dd6c533d.png)In a $ 2×3 $ table there are $ 6 $ $ 1×1 $ squares and $ 2 $ $ 2×2 $ squares. That is equal to $ 8 $ squares in total.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599D/35201b8105ae1bfeef67a0a4652f36b51fa0b01f.png)

## 样例 #1

### 输入

```
26
```

### 输出

```
6
1 26
2 9
3 5
5 3
9 2
26 1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2
1 2
2 1
```

## 样例 #3

### 输入

```
8
```

### 输出

```
4
1 8
2 3
3 2
8 1
```

# 题解

## 作者：lgx57 (赞：1)

搞笑推式子题。

下文用 $x$ 和 $y$ 来代替 $n$ 和 $m$。

不妨设 $x \le y$，根据 [小学奥数题](https://www.luogu.com.cn/problem/P2241) 的结论，正方形的个数为：

$$xy+(x-1)(y-1)+(x-2)(y-2)+\cdots = x^2 y-\frac{x(x-1)}{2}(x+y)+\frac{x(x-1)(2x-1)}{6}$$。

然后把 $y$ 当作主元，可以解出 

$$y=\frac{2n-\frac{x(x-1)(2x-1)}{3}-x^2+x^3}{x^2+x}$$

最后只需要枚举 $x$ 就能得出答案。

注意输出时需要将 $x$ 从小到大排序。

---

## 作者：minecraft_herobrine (赞：1)

我们可以从一个 $i*i$ 的正方形开始枚举，则这个正方形中边长为 $i*i$ 的正方形有 $1$ 个，边长是 $(i-1)*(i-1)$ 的正方形有 $2$ 个，以此类推，边长为 $1$ 的正方形有 $1^2+2^2+3^2+……+i^2= \dfrac{i*(i+1)*(2i+1)}6=s$

可以用数学归纳法证明。

当 $n=1时$，$1^2=\dfrac{1*(1+1)*(2*1+1)}6=1$ 显然成立

假设当 $n=t-1$ 时成立，即有 $1^2+2^2+……+n^2=\dfrac{(t-1)*t*(2t-1)}6$

则当 $n=t$ 时，有

$1^2+2^2+3^2+……+n^2$

$=(1^2+2^2+3^2+……+(t-1)^2)+t^2$

$=\dfrac{(t-1)*t*(2t-1)}6+t^2$

$=\dfrac{(t-1)*t*(2t-1)+6t^2}6$

$=\dfrac{t*[(t-1)*(2t-1)+6t]}6$

$=\dfrac{t*(t^2+3t+1)}6$

$=\dfrac{t*(t+1)*(2t+1)}6$

证毕

如果上面的那个式子的值小于k，说明当前的正方形不够。

考虑我们在这个正方形上加新的列，则每增加一列，正方形的个数增加 $\dfrac{i*(i+1)}2$ ,这个应该就不难理解了。

如果出现了，$(k-s)\mod(i*(i+1)/2)=0$ 
说明正好有 $(k-s)/(i*(i+1)/2)$ 个新增列。此时记录答案即可。注意矩形长宽不同时算两个不同答案。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5e6+10;
struct node
{
    ll x,y;
}res[MAXN];

int main()
{
    ll i,k,sum=0;
    scanf("%lld",&k);
    int flag=0;
    ll p=(ll)sqrt(k);
    i=1;
    for(i=1;i<=min(2000000ll,p);i++)
    {
        ll tot=i*(i+1)*(2*i+1)/6;
        ll add=i*(i+1)/2;
        if(k>=tot && (k-tot)%add==0)
        {
			res[sum].x=i;
			res[sum++].y=(k-tot)/add+i;
        }
    }
    if(res[sum-1].y==res[sum-2].x && res[sum-1].x==res[sum-2].y)
    {
        printf("%lld\n",(sum-1)*2);
        for(i=0;i<sum;i++) printf("%lld %lld\n",res[i].x,res[i].y);
        for(i=sum-3;i>=0;i--) printf("%lld %lld\n",res[i].y,res[i].x);
    }
    else
    {
        if(res[sum-1].x==res[sum-1].y)
        {
        	printf("%d\n",sum*2-1);
        	for(i=0;i<sum-1;i++) printf("%lld %lld\n",res[i].x,res[i].y);
        	for(i=sum-1;i>=0;i--) printf("%lld %lld\n",res[i].y,res[i].x);
        }
        else
        {
			printf("%lld\n",sum*2);
			for(i=0;i<sum;i++) printf("%lld %lld\n",res[i].x,res[i].y);
			for(i=sum-1;i>=0;i--) printf("%lld %lld\n",res[i].y,res[i].x);
        }
	}
    return 0;
}
```


---

## 作者：sunkuangzheng (赞：0)

显然对于固定的 $n,m$，答案是 $f(n,m) = \sum \limits_{k=1}^{\min(n,m)} (n-k+1)(m-k+1)$。这个东西显然可以 $\mathcal O(1)$ 算：$f(n-1,m-1) = \sum nm - (n+m)k+k^2 = nmk-(n+m)\dfrac{k(k+1)}{2}+\dfrac{k(k+1)(2k+1)}{6}$。

注意到 $\min(n,m) \ge 3 \times 10^6$ 时，答案已经大于 $10^{18}$，故我们可以考虑枚举 $\min(n,m)$，二分 $\max(n,m)$ 的值即可。常数很大，因此加一点剪枝：如果 $f(i,i) > x$ 或者 $f(i,10^{18}) < x$，这个 $i$ 肯定无解，就不要二分了。 

复杂度 $\mathcal O(n \log n)$，其中 $n = 3 \times 10^6$。

---

