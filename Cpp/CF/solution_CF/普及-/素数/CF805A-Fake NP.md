# Fake NP

## 题目描述

Tavak and Seyyed are good friends. Seyyed is very funny and he told Tavak to solve the following problem instead of longest-path.

You are given $ l $ and $ r $ . For all integers from $ l $ to $ r $ , inclusive, we wrote down all of their integer divisors except $ 1 $ . Find the integer that we wrote down the maximum number of times.

Solve the problem to show that it's not a NP problem.

## 说明/提示

Definition of a divisor: <https://www.mathsisfun.com/definitions/divisor-of-an-integer-.html>

The first example: from $ 19 $ to $ 29 $ these numbers are divisible by $ 2 $ : $ {20,22,24,26,28} $ .

The second example: from $ 3 $ to $ 6 $ these numbers are divisible by $ 3 $ : $ {3,6} $ .

## 样例 #1

### 输入

```
19 29
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 6
```

### 输出

```
3
```

# 题解

## 作者：Aw顿顿 (赞：12)

[多种语言/推导过程/符合洛谷标准的题解全集。](https://www.luogu.com.cn/blog/AlanWalkerWilson/)


首先注意到一句话：

$$\rm except\ 1$$

也就是说输出的因数不能为 $1$。

那么，这时候通常情况是什么？

除了 $1$ 以外，在一个给定区间内有最多倍数的整数是 $2$。

性感理解一下，举个例子：

$$1,2,3,4,5,6$$

当中 $2$ 的倍数有 $2,4,6$ 总共 $3$ 个，而在理想情况下，$n$ 个数的数列中有 $n\div 2$ 个因数，当然，如果两边都是偶数，是 $n\div 2+1$，反之 $n\div 2-1$。

也就是说，输出 $2$ 就行了。

但是……真的这么简单吗？

我们输出 $2$ 看看、

结果……第一个点就 WA 了。

于是我们来观察样例：诶？怎么有一个 $3$ 出现啊？？

寻思着 $3,4,5,6$ 当中 $2,3$ 的倍数是一样的，再想想特殊情况？

对，如果这个区间只有一个元素，就直接输出这个元素！

那么，简单分支语句即可。

首先是 Python3 版本的：

```python
a,b=map((int),input().split())
if a==b:
    print(a)
else:
    print("2")
```

AC 记录：https://www.luogu.com.cn/record/32581632

C++ 版本：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;
    if(a==b)cout<<a<<endl;
    else puts("2");
    return 0;
}
```

AC 记录：https://www.luogu.com.cn/record/32581763

C语言版本：

```c
#include<stdio.h>
int a,b;
int main(){
    scanf("%d %d",&a,&b);
    if(a==b)printf("%d\n",a);
    else printf("2");
    return 0;
}
```
AC记录：https://www.luogu.com.cn/record/32581849


另外，这个时间还可以卡的更短，详见：[详解常数优化](https://www.luogu.com.cn/blog/AlanWalkerWilson/OI-from-zero-to-AK)

感谢聆听，希望您能一次AC。

---

## 作者：小闸蟹 (赞：3)

```cpp
// 这一题其实特别水，我一开始就是被样例吓到了，其实再仔细读题会发现如果有多个答案，那就随意输出一个
// 我们都知道一个>=2的整数要么是奇数要么是偶数，所以2这个因子占的比例是最高的
// 但是有个例外，就是[质数，质数]的情况，而且区间长度为1，那么就直接输出端点即可，否则就输出2
#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << (a == b ? a : 2) << std::endl;

    return 0;
}
```

---

## 作者：伟大的王夫子 (赞：1)

安利一下[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)

若$l=r$，那么答案显然为$l$

若$l \not =r$, 设这个数为$a$

则能被整除的数有$\dfrac{r-l}{a}$个

我们要让$a$最小，$\therefore a=2$

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int l, r;
	cin >> l >> r;
	if (l == r) cout << l;
	else cout << 2;
	
}
```

---

## 作者：guanchen (赞：0)

这题其实出的不是太好（难道1不是因子吗？？？）

所以强烈建议出题人 @yjjr 完善一下。

好了说正事：

**既然不包括因子为1的数，那么显然，因子为2的数是最多的，所以不管什么情况下我们输出2，都能骗到一部分分
（我试过，骗到了第24个点，第25个点成功WA掉 QAQ）**

然后我们不能忽略另外一种情况，就是**两个数相差为1且第一个数是质数时**一定要进行特判，输出第一个数即可

但是这题我一开始傻乎乎的用质数筛，后来发现给的数越来越大，然后数组爆炸，半个小时没有调出来
附上RE代码
```
#include<iostream>
#include<cstdio>

using namespace std;

bool a[1000010];

int main()
{
    int n;
    int n2;
    scanf("%d%d",&n,&n2);
    for(int i=2;i*i<n2;i++)if(!a[i])
    for(int j=i*2;j<=n;j+=i)if(!a[j])
    a[j]=true; 
    if(!a[n]&&!a[n2]&&n2-n==1)
    {
        printf("%d",n);
        return 0;
    }
    else printf("2");
    return 0;
}
```
一开始测了12个点，到十三个点的时候紫了，死活调不出来（后来发现93个点的那种绝望）

之后mrk大佬指点我直接判断，于是删掉我~~心爱的~~筛法，改用直接判断。

下面是AC代码
```
#include<iostream>
#include<cstdio>

using namespace std;

bool prime(int n)
{
    for(int i=1;i<=n;i++)
    if(n%i==0)return true;
    return false;//老掉牙的质数判断，不过好用
}

int main()
{
    int n;
    int n2;
	scanf("%d%d",&n,&n2);
	if(!prime(n)&&n2-n==1||n2==n)
	{
		printf("%d",n);
		return 0;
	}
	else printf("2");
    return 0;
}
```


---

