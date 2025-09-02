# Phoenix and Puzzle

## 题目描述

Phoenix is playing with a new puzzle, which consists of $ n $ identical puzzle pieces. Each puzzle piece is a right isosceles triangle as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/49a24f982b19e9535d6f30d4c91e443065d9fee9.png)A puzzle pieceThe goal of the puzzle is to create a square using the $ n $ pieces. He is allowed to rotate and move the pieces around, but none of them can overlap and all $ n $ pieces must be used (of course, the square shouldn't contain any holes as well). Can he do it?

## 说明/提示

For $ n=2 $ , Phoenix can create a square like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/0fdfe011cd52355d3ad3123ce3848f97d63a78aa.png)For $ n=4 $ , Phoenix can create a square like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/79f4dda31da05d0a22081f6d24d2a99d26f679bc.png)For $ n=6 $ , it is impossible for Phoenix to create a square.

## 样例 #1

### 输入

```
3
2
4
6```

### 输出

```
YES
YES
NO```

# 题解

## 作者：pitiless0514 (赞：4)

首先判断是否满足 $n \bmod 2=0$ 或 $n \bmod 4=0 $  。因为发现 $2$ 个三角形或者 $4$ 个三角形可以构成一个小正方形，那么只要接下来的  $\frac{n}{2}$ 或 $\frac{n}{4}$ 个正方形可以拼成一个大正方形，那么就可以。也就是判断 $\frac{n}{2}$ 或 $\frac{n}{4}$ 是否为完全平方数。 如果不是那么输出  ```NO``` ，否则 输出 ```YES```


---

## 作者：PPL_ (赞：3)

# 前言

被迫营业。

# 题目

[CF](https://codeforces.com/contest/1515/problem/B)

[洛谷](https://www.luogu.com.cn/problem/CF1515B)

题目大意：

$t$ 组数据，每组数据输入一个整数 $n$，表示给定的相同等腰直角三角形的数量。

询问是否能够用上所有三角形拼出一个**无空洞**的正方形。

能做到输出 $\tt YES$ ，否则输出 $\tt NO$。

$1\le t\le 10^4;1\le n\le 10^9.$



# 讲解

样例已经给我们很大的提示了：我们可以用直角边长的倍数作为正方形边长，也可以用斜边边长的倍数作为边长。

这个正方形必定是由相同的小正方形组成的，虽然很好理解，但是还是简单证明一下。

>   考虑反证。假设这个正方形的边长既有直角边，又有斜边。

>   令三角形直角边长为 $1$，则斜边长 $\sqrt{2}$。令这个正方形的边长为 $a+\sqrt{2}b$，那么面积为 $a^2+2\sqrt{2}ab+2b^2$，是一个无理数。但是每个三角形的面积是 $\frac{1}{2}$，是有理数，$n$ 个拼起来也应该是有理数。与原命题不符。

-   以直角边为边长的小正方形需要 $2$ 个三角形。
-   以斜边为边长的小正方形需要 $4$ 个三角形。

正方形必定边长相等，所以小正方形个数是完全平方数。

因此只需要判断 $\frac{n}{2}$ 和 $\frac{n}{4}$ 是否为完全平方数即可。

# 代码

```cpp
bool check(double x)
{
    int t = sqrt(x);
    if(t * t == x) return 1;
    return 0;
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    for(int T = Read(); T ;-- T)
    {
        n = Read();
        if(check(n/2) || check(n/4)) printf("YES\n");
        else printf("NO\n");
    }
	return 0;
}

```





---

## 作者：rain2021 (赞：0)

##### 一血！

题意：

有$n$个等腰直角三角形，能不能把所有等腰直角三角形都拼成正方形，并且没有剩下的等腰直角三角形。

* * *

我们先看看等腰直角三角形如何拼成正方形。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/0fdfe011cd52355d3ad3123ce3848f97d63a78aa.png)
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/79f4dda31da05d0a22081f6d24d2a99d26f679bc.png)

只有这两种情况，其他的都可以由这两个拼法衍生过来。

如果等腰直角三角形的个数$÷2$或$÷4$是完全平方数，就可以拼成大正方形。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool check(int x)
{
	int sqrtx = sqrt(x);
	if(sqrtx * sqrtx == x)
		return true;
	return false;
}
int main()
{
	int T, x;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &x);
		if(x % 2 == 1)
			puts("NO");
		else
		{
			int x2 = x / 2;
			if(check(x2))
				puts("YES");
			else
			{
				if(x % 4 == 0)
				{
					int x3 = x / 4;
					if(check(x3))
						puts("YES");
					else
						puts("NO");
				}
				else
					puts("NO");
			}
		}
	}
	return 0;
}
```

---

## 作者：BorisDimitri (赞：0)

# 题意
$t$ 组数据，每组数据包含一个数字 $n$ ，问能否用 $n$ 个全等的等腰RT三角形拼凑成一个正方形。

# 分析
我们把这个问题转换一下，即 

> **能否把一个正方形划分成 $n$ 个全等的等腰RT三角形**。


来看边长为 $1$ 时的情况，即可以分为 $1^2 \times 2^1 ,1^2\times2^2...$ 个等腰直角三角形。
![](https://cdn.luogu.com.cn/upload/image_hosting/5sr6b7ib.png)

来看边长为 $2$ 时的情况，即可以分为 $2^2 \times 2^1 ,2^2\times2^2...$ 个等腰直角三角形。

![](https://cdn.luogu.com.cn/upload/image_hosting/szqgyc8o.png)


来看边长为 $3$ 时的情况，即可以分为 $3^2 \times 2^1 ,3^2\times2^2...$ 个等腰直角三角形。

![](https://cdn.luogu.com.cn/upload/image_hosting/yvf5cu9u.png)

于是，我们可以得出结论：**当 $n$ 可以表示为 $q^2 \times 2^p (1 \le p,q)$ 时，则可以划分成功。(特别的，$1$ 是不合法的情况，要特判)**

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        long long n;
        cin >> n;

        if (n == 1 || (n % 2 == 1)) cout << "NO\n";
        else
        {
            while (n % 2  == 0) n /= 2; //除去2的整数次幂因数，这一步之后n从 q^2 * 2^p 变为 q^2

            if (n == 1) cout << "YES\n";
            else //判断n是否可以表示为q^2
            {
                int q = sqrt(n); 
                if (q * q == n) cout << "YES\n";
                else cout << "NO\n";
            }
        }
    }

    return 0;
}
```

---

## 作者：LinkZelda (赞：0)

- **题意**：给定 $n$ 个全等的等腰三角形，询问是否可以刚好将这些等腰三角形拼成一个正方形。

- $Solution$:

观察样例可以发现，每 $2$ 或 $4$ 个等腰三角形可以拼成一个正方形。那么我们问题就转化为了：给定 $n/2$ 或 $n/4$ 个全等的正方形，问是否可以拼成一个正方形。（这里要求 $2\mid n$ 或 $4\mid n$）。

我们发现，一个正方形只能由 $k^2$（$k$ 为正整数）个正方形构成。具体证明可以设正方形边长为 $x$ 面积为 $x^2$，则拼出来的正方形边长为 $k\times x$，总面积为 $k^2\times x^2$，也就是由 $k^2$ 个正方形拼出来的。

所以只需要判断正方形个数是否为**完全平方数**即可。

- [代码](https://www.luogu.com.cn/paste/8bcfs8zd)

---

## 作者：oimaster (赞：0)

容易发现用这种三角形搭出的正方形一定是由这两种形态中任意一种重复得来的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/0fdfe011cd52355d3ad3123ce3848f97d63a78aa.png?x-oss-process=image/resize,m_lfit,h_100,w_100)
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/79f4dda31da05d0a22081f6d24d2a99d26f679bc.png?x-oss-process=image/resize,m_lfit,h_100,w_100)

那么我们可以让程序看看哪种情况是可行的。如果我们的三角形数量是 $2$ 的倍数，我们就先让个数除以 $2$ 得到 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/0fdfe011cd52355d3ad3123ce3848f97d63a78aa.png?x-oss-process=image/resize,m_lfit,h_20,w_20) 的个数，然后检查这个数是不是完全平方数即可。

如果这个数量是 $4$ 的倍数，与上面同理。

不难写出代码：

```cpp
int p;
cin>>p;
if(p%2==0){
	int p2=p/2;
	double pp=sqrt(p2);
	if(pp==int(pp)){
		cout<<"YES"<<endl;
		return 0;
	}
}
if(p%4==0){
	int p2=p/4;
	double pp=sqrt(p2);
	if(pp==int(pp)){
		cout<<"YES"<<endl;
		return 0;
	}
}
cout<<"NO"<<endl;
```

---

