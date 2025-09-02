# [ABC144C] Walk on Multiplication Table

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc144/tasks/abc144_c

高橋君は無限に広い掛け算表の上にいます。

掛け算表のマス $ (i,j) $ には整数 $ i\ \times\ j $ が書かれており、高橋君は最初 $ (1,1) $ にいます。

高橋君は $ 1 $ 回の移動で $ (i,j) $ から $ (i+1,j) $ か $ (i,j+1) $ のどちらかにのみ移ることができます。

整数 $ N $ が与えられるので、$ N $ が書かれているマスに到達するまでに必要な移動回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{12} $
- $ N $ は整数である。

### Sample Explanation 1

$ 5 $ 回の移動で $ (2,5) $ に到達することができます。$ 5 $ 回未満の移動では $ 10 $ が書かれたマスに到達することは出来ません。

### Sample Explanation 2

$ 13 $ 回の移動で $ (5,10) $ に到達できます。

### Sample Explanation 3

入出力とも非常に大きな値になる可能性があります。

## 样例 #1

### 输入

```
10```

### 输出

```
5```

## 样例 #2

### 输入

```
50```

### 输出

```
13```

## 样例 #3

### 输入

```
10000000019```

### 输出

```
10000000018```

# 题解

## 作者：_IcyFire (赞：2)

### 题意简述
------------

给定一个平面直角坐标系和一个整数 $n$，你在 $(1,1)$，且每次都能向上或向左移动一格。

求你到达 $(x,y)(x \cdot y = n)$ 所要的次数。

### 解题思路
------------

注意起点是 $(1,1)$。

无论如何走，步数都是 $(x-1)+(y-1)$ 即 $x+y-2$。

又因为 $x \cdot y = n$。

所以 $x,y$ 都是 $n$ 的因数。

所以从 $1 \to  \sqrt{n}$ 枚举 $n$ 的因数即可，时间复杂度 $\Theta (\sqrt{n})$。

要开 `long long`。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
ll n,ans=inf;
int main() {
	scanf("%lld",&n);
	for(int i=1;i<=sqrt(n);i++)
		if(n%i==0) ans=min(n/i+i-2,ans);
	printf("%lld",ans);
	return 0;
}
//code by _IcyFire
```

---

## 作者：shenmadongdong (赞：2)

## 题意：
有一个平面直角坐标系，你在点 $(1,1)$ ,每次可以向上走一步或向右走一步，求你走到横纵坐标之积为 $N\ (2 \leq N \leq 10^{12})$ 的点的最小步数

## 解法：
有一个显然的结论：设走到的点为 $(x,y)$ ,则当 $|y-x|$ 最小时所需步数最小

下面进行简单的证明 ~~(这不是积一定，差小和小吗)~~：

不妨设两个点 $(x,x+a)$ 与 $(x-b,x+c)$ ,它们的积相等，且 $x,a,b,c>0$

则有 $x(x+a)=(x-b)(x+c)$

展开得 $x^2+ax=x^2+(c-b)x-bc$

化简得 $bc=(c-b-a)x$

$\because bc>0,x>0$

$\therefore\ c-b-a>0$

$\therefore\ x+(x+a)<(x-b)+(x+c)$

显然$(x+a)-x<(x+c)-(x-b)$

$\square$

不妨令$x<y$，显然$x \leq \sqrt{n}$，那我们就可以从 $\sqrt {n}$ 开始往下暴力枚举 $x$，如果 $x|n$ 就停下来即可

最后算出 $y$，计算 $(1,1)$ 到 $(x,y)$ 的欧几里得距离即为答案

```
#include<bits/stdc++.h>
using namespace std;
long long n,x,y;
int main()
{
	cin>>n;
    x=floor(sqrt(n));//x的上界
    while(n%x!=0&&x>0) x--;//暴力计算出x
	y=n/x;//计算出y
    cout<<(x-1)+(y-1)<<'\n';//计算出距离
    return 0;
}
```

---

## 作者：xiaoPanda (赞：0)

### Problem
问从点 $(1,1)$ 到点 $(i,j)$ 并且 $i* j=n$ 的最小步数是多少。
 
每次可以向上走一步或向右走一步。
 
### Solution
首先先来解决从 $(1,1)$ 到任意点 $(x,y)$ 的步数，一种方法是先向上移动 $x-1$ 步，在向右移动 $y-1$ 步，总步数为 $x+y-2$。

对于其他方法，将向上的线段向右平移，向右的线段向上平移，就会发现与上一种情况一样，所以从 $(1,1)$ 到任意点 $(x,y)$ 的步数是 $x+y-2$。

那么当 $i* j=n$ 时，答案就是 $i+j-2$，直接枚举 $n$ 的约数即可，再找一遍最小值，时间复杂度为 $O(\sqrt n)$。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
main()
{
	int n,ans=LONG_LONG_MAX;/*答案可能超过int，所以使用long long*/
	cin>>n;
	for(int i=1;i*i<=n;i++)
	{
		if(n%i==0)/*如果i是n的约数，那另一个点j就是n/i，答案是i+n/i-2*/
		ans=min(ans,i+n/i-2);
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：LucasXu80 (赞：0)

来一篇 Python 题解。

先宣传我的博客 [Python 快速上手](https://www.luogu.com.cn/blog/HuayuLucas/python-kuai-su-shang-shou) ，想了解好玩的 Python 的 C 党们可以去看看。

这题思路比较简单，暴力枚举终点的横坐标即可。

如果终点是 $(i,j)$，那么不难知道 $i$ 的上界是 $\sqrt n$，不断减小 $i$ 直到找到 $\dfrac n i =j$ 是整数为止。这一做法的正确性可由“和一定，差小积大”证明。

注意我们要输出的是 $i+j-2$，因为起点是 $(1,1)$ 而非 $(0,0)$。

在 Python 中，开根号直接用 $0.5$ 次方即可。

上代码。

```python
import sys # 用于提前结束程序
n=int(input())
m=int(n**0.5) # 开平方根
for i in range(m,0,-1): # 从 m 循环到 0
    j=n//i # 整数除法，自动向下取整
    if (i*j==n): # 恰好整除
        print(i+j-2) # 输出结果
        sys.exit() # 直接结束程序
```
【声明】这份代码由于洛谷提交 AT Python 好像有点问题（无法提交），是在 AT 上直接提交的，因此本地并没有这份代码的 AC 记录，但在我的 AT 账号上有。

这篇题解就到这里了。感谢大家的阅读，如果对 Python 有问题可以移步我的博客。

---

