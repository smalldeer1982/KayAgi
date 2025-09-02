# Buggy Sorting

## 题目描述

Little boy Valera studies an algorithm of sorting an integer array. After studying the theory, he went on to the practical tasks. As a result, he wrote a program that sorts an array of $ n $ integers $ a_{1},a_{2},...,a_{n} $ in the non-decreasing order. The pseudocode of the program, written by Valera, is given below. The input of the program gets number $ n $ and array $ a $ .

`<br></br>loop integer variable  $ i $  from  $ 1 $  to  $ n-1 $ <br></br>    loop integer variable  $ j $  from  $ i $  to  $ n-1 $ <br></br>        if  $ (a_{j}&gt;a_{j+1}) $ , then swap the values of elements  $ a_{j} $  and  $ a_{j+1} $ <br></br>`But Valera could have made a mistake, because he hasn't yet fully learned the sorting algorithm. If Valera made a mistake in his program, you need to give a counter-example that makes his program work improperly (that is, the example that makes the program sort the array not in the non-decreasing order). If such example for the given value of $ n $ doesn't exist, print -1.

## 样例 #1

### 输入

```
1
```

### 输出

```
-1
```

# 题解

## 作者：Mint_Flipped (赞：1)

路过 没人写题解 我来一发 QAQ

我们直接看他写的升序排序

```c
    for(int i=1;i<n;++i){
        for(int j=i;j<n;++j)
        if(a[j]>a[j+1])
        swap(a[j],a[j+1]);
    }
```

举个例子：33 10000 22

排序后是：33 22 100

每一遍排序使最右边得到最大值，但却从左往右推进。

正确思路：

```c
for(int i=1;i<n;++i){
        for(int j=1;j<=n-i;++j)
        if(a[j]>a[j+1])
        swap(a[j],a[j+1]);
        }
```
好了回到题目，1不排，2交换一次是对的，3就出问题了，接下来就都会出问题。

举反例：99 100 1...即可。

代码如下：
```c
#include <bits/stdc++.h>
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define inf 0x3f3f3f3f
using namespace std;
const int maxn=1e2+5;
const int mod=1e9+7;
int main()
{
    int n;
    cin>>n;
    if(n==1||n==2)
        puts("-1");
    else{
        printf("99 100 ");
        fo2(i,n-2)
        printf("%d ",i);
    }
    return 0;
}
```


---

## 作者：Transparent (赞：1)

### 题目大意：
Valera写了一个排序的算法（伪代码）：
```
loop integer variable i from 1 to n - 1
    loop integer variable j from i to n - 1
        if (a[j] > a[j + 1]), then swap the values of elements a[j] and a[j + 1]
```
显然这是错误的……

给你一个 $n$ 表示数组的长度，
请你构造一组数据，
Hack掉他的算法。

如果无法Hack，就输出"-1"。

### 分析：
显然，一个标准的冒泡排序的第二重循环应该从 $1$ 开始。

那么这个算法就漏掉了第 $i$ 次排序后，
前 $i$ 项中可能出现的逆序对。

而如果长度小于等于 $2$ ，
则这个算法就不会漏掉任何逆序对，
所以 $n \leq 2$ 时，
这个算法时正确的。

为了在其它情况下卡掉它，
就需要构造数据，
使它漏掉一个或一些逆序对，

当 $n=3$ 时，

当且仅当第 $2$ 次循环后前 $2$ 项是逆序的，
这个算法才会出错。
为了让前 $2$ 项在第 $2$ 次循环后逆序，
只有这个数组： $3~2~1$ 
（算法结果： $2~1~3$ ），
即数组原本就有序的情况。

当 $n=4$ 时，

- 输入 $4~3~2~1$ ，
得到的结果是 $3~1~2~4$ 。

- 输入 $3~2~1~4$ ，
输出 $2~1~3~4$ 。

可以看出还有其它的方法可以使它出错,
但是逆序输出是最简单可靠的方法。

### 代码：
```cpp
//从99开始逆序，当然也可以用从其它的数开始
//但是题目限制 1<=a[i]<=100 所以起始的数不能太大，也不能太小 
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	if(n<=2)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d ",100-i);
	}
	return 0;
}
```



---

## 作者：封禁用户 (赞：0)

# 原题：[CF246A Buggy Sorting](https://www.luogu.com.cn/problem/CF246A)

## 一、题目大意

```Valera``` 写了一个排序的算法（伪代码）：

```
loop integer variable i from 1 to n - 1
    loop integer variable j from i to n - 1
        if (a[j] > a[j + 1]), then swap the values of elements a[j] and a[j + 1]
```
等价于

```cpp
for(int i=1;i<n;++i)
    for(int j=i;j<n;++j)
        if(a[j]>a[j+1])
             swap(a[j],a[j+1]);//这是错的
```
然后给你一个 $n$ 表示数组的长度， 请你构造一组数据， ```hack``` 掉他的算法。

如果无法 ```hack```，就输出 $-1$。

## 二、分析

显然，一个标准的冒泡排序的第二重循环应该从 $1$ 开始。

那么这个算法就漏掉了第 $i$ 次排序后， 前 $i$ 项中可能出现的逆序对。

而如果长度小于等于 $2$ ， 则这个算法就不会漏掉任何逆序对， 所以 $n\leq2$ 时， 这个算法时正确的。

先举两个例子：

当 $n=3$ 时，

- 输入 $3\ 2\ 1$，```Valera``` 的结果是 $2\ 1\ 3$ 而正确答案是 $1\ 2\ 3$。

当 $n=4$ 时，

- 输入 $4\ 3\ 2\ 1$，```Valera``` 的结果是 $3\ 1\ 2\ 4$ 而正确答案是 $1\ 2\ 3\ 4$。

显然当 $a$ 数组的数字是倒序时，都能把 ```Valera``` 的算法 ```hack``` 掉，当然情况不止这一种如：

当 $n=3$ 时，

- 输入 $2\ 3\ 1$，```Valera``` 的结果是 $2\ 1\ 3$ 而正确答案是 $1\ 2\ 3$。

当 $n=4$ 时，

- 输入 $3\ 2\ 1\ 4$，```Valera``` 的结果是 $2\ 1\ 3\ 4$ 而正确答案是 $1\ 2\ 3\ 4$。

也能 ```hack```掉，但是倒序是最简单可靠的方法。

因此很容易写出代码。

## 三、code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	if(n>2)
		while(n--)
			printf("%d ",n+1);
	else printf("-1");
	return 0;
}
```

---

## 作者：BYWYR (赞：0)

## $\texttt{Solution}$

首先来看一下 Valera 写的代码：

```cpp
for(int i=1;i<n;++i)
    for(int j=i;j<n;++j)
        if(a[j]>a[j+1])
             swap(a[j],a[j+1]);//这是错的

```

很明显，这是冒泡排序，但是 Valera 第二层循环中的 $j$ 应该从 $1$ 开始。

那么这个算法也就漏掉了第 $i$ 次排序后可能出现的逆序对。

分类讨论：

- 当 $n \leq 2$ 时，这个算法不会漏掉逆序对，所以这个算法在 $n \leq 2$ 时是正确的；

- 当 $n \geq 3$ 时，使前 $n-1$ 项为逆序，那么序列原本应处于有序状态，也就是倒序。

综上所述，逆序输出可以 hack 掉 Valera 的算法。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
int main(){
    scanf("%d",&n);
    if(n>=3){//第二种情况
    	while(n--) printf("%d ",n+1);//逆序输出
	}
    else printf("-1");//第一种情况
    return 0;
}
```


---

## 作者：Esawkm (赞：0)

题意：让我们构造一组数据， `Hack ` 掉这个不正确的排序。 
~~（话说用 sort 不香吗）~~

众所周知，冒泡排序第 2 层循环应从 `i=1` 开始。

所以，当逆序对很多的时候，会漏掉一些逆序对。

当我们从大到小排列要排序的数组逆序对很多的话，他的代码就一定错了。

经过实验，他的代码只能保证 $n \leq 2$ 时才对。

所以我们构造的数据应从大到小，这样逆序对才多。

那么代码就很容易了，判断一下 $n$ 的值，如果 $n \leq 2$ 输出 `-1`

否则就构造数据 `Hack` 他。

# Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    if(n>=3)//判断
    while(n--)
    cout<<n+1<<" ";//构造数据
    else
    cout<<-1;
    return 0;
}

---

## 作者：ttq012 (赞：0)

**Solution**

构造。

容易发现，这一份代码对于这样的数据是会出错的。

`3 2 1`。

原因：$3$ 在正确的冒泡排序中交换了两次，而在这份代码中只交换了一次。

因此可以推出，当 $n=1$ 或 $n=2$ 的时候，这个排序是正确的，无法 `Hack`。

当 $n\ge 3$ 的时候，构造一组单调递减的序列可以 `Hack` 掉这份代码。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    if (n >= 3)
        for (int i = n; i; i --)
            cout << i << ' ';
    else
        puts("-1");
    return 0;
}

```


---

