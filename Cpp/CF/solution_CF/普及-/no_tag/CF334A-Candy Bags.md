# Candy Bags

## 题目描述

Gerald has $ n $ younger brothers and their number happens to be even. One day he bought $ n^{2} $ candy bags. One bag has one candy, one bag has two candies, one bag has three candies and so on. In fact, for each integer $ k $ from $ 1 $ to $ n^{2} $ he has exactly one bag with $ k $ candies.

Help him give $ n $ bags of candies to each brother so that all brothers got the same number of candies.

## 说明/提示

The sample shows Gerald's actions if he has two brothers. In this case, his bags contain 1, 2, 3 and 4 candies. He can give the bags with 1 and 4 candies to one brother and the bags with 2 and 3 to the other brother.

## 样例 #1

### 输入

```
2
```

### 输出

```
1 4
2 3
```

# 题解

## 作者：Ggsddu_zzy (赞：8)

 [题目传送门](https://www.luogu.com.cn/problem/CF334A)

### 题目大意：

给你 $n^2$ 颗糖，分给 $n$ 人，使每个人的权值相等（第 $i$ 块的权值为 $i$ ），输出第 $i$ 个人选的糖果集合，注意题目中说 $n$ 为偶数。


### 解题思路：

根据 $1+2+\ldots+n-1+n= \dfrac{n}{2}(n+1)$ 的规律，总结出每组的权值的和其实都是 $n^2+1$。

从 $\ 1$ 和 $n^2$ 之间找出每一组相加为 $n^2+1$ 的组合，这两个数是相对应的，如当 $n\ =4$ 时，这 $n$ 个人的权值可为 $\ 1$ 和 $\ 16$，$\ 2$ 和 $\ 15$，$\ 3$ 和 $\ 14$ 等；再把每一种组合都输出出来即可。

如何找出每一种组合？

把 $n^2$ 分为两节，分别是从 $1$ 到 $\dfrac{n^2}{2}$，和从 $n^2$ 到 $  \dfrac{n^2}{2}$，当第一节中的数字 $i$ 与第二节中的数字 $j$ 是一组时，$i+j==n^2+1$；

所以只需要判断 $i+j$ 是否与 $n^2+1$ 相等。

当然，也可以直接从 $1$ 到 $\frac{n^2}{2}$ 找，先把每一个数都输出，再输出 $n^2-i+1$（ $\ 1$ 也可以加在 $i$ 上）。

为什么要加 $\ 1$ 呢？

因为第一组为 $\ 1$ 和 $n^2$，而不是 $\ 0$ 和 $n^2$。



#### 代码1：

```cpp
#include<iostream> 
using namespace std;
int n,b,c; 
int main()
{ 
   cin>>n;
   b=n*n; 
   c=b/2;
   for(int i=1;i<=c;i++) {              //第一节查找 
   		for(int j=b;j>=c;j--){           //第二节查找
   			if(i+j==b+1)               //判断是否为一组
   				cout<<i<<' '<<j<<"\n";
		}    
   }
   return 0; 
}
```

#### 代码2：

```cpp
#include<iostream> 
using namespace std;
int n,b,c; 
int main()
{ 
   cin>>n;
   b=n*n; 
   c=b/2; 
   for(int i=1;i<=c;i++) {                
       cout<<i<<' '<<b-i+1<<"\n";         
   }
   return 0; 
}
```

---

## 作者：Sincerin (赞：3)


[题目传送门](https://www.luogu.com.cn/problem/CF334A)


## 题意
给你 $n^2$ 块糖果，第 $i$ 块的权值为 $i$，分给 $n$ 个人，使得每个人分到的权值相等。


------------
### 题目描述（翻译没有啊，害我想了好久）
   Gerald 有 $n$ 个弟弟，他们的数目恰好是偶数。

- 也就是说 $n$ 为偶数，我们就没有必要像前两篇题解一样分类讨论 $n$ 的奇偶性。


------------
## 思路
- 在小学四年级的时候，我们就已经见识过一个公式（~~等差数列和公式~~）。


没错，就是著名的 $ 1+2+3+\cdots+100$ 问题，而著名的大数学家高斯先生很小时便推出了这个柿子：
$$ \sum_{i=1}^n i = \frac {n(n+1)}{2}$$
其实质就是 $( $ 首项 $+$ 末项 $)$  $\times$ 项数 /2 。

- 应为 $n$ 为偶数，所以 $n^2 $ 一定为偶数，我们可以得到序列 $A$ $ [1 , n^2]$:


当 $n=2$ 时，为 $[1,2,3,4]$。
我们发现首项 $A[1]+$ 末项 $A[n^2]=1+4=5$；
次首项 $A[2]+$ 次末项 $A[n^2-1]=2+3=5$。

以此类推，我们只需要分别从 $1$ 和 $n^2$ 向中间查找，输出每一对对应项 $A[i]$ 和 $A[j]$ 即可。当 $i=j$ 时，方案全部找完。

（关于 $n$ 种方案的问题 ，大家可以自行思考下。）
 
 

---------------------------
# _AC Code_ 
```cpp
#include<iostream> 
using namespace std;
int a,b; 
int main()
{ 
   cin>>a;
   b=a*a/2; 
   for(int i=0;i<b;i++) //查找
   {
       cout<<1+i<<' '<<a*a-i<<"\n";
   }
   return 0; //完结撒花
}


```

#### 审核大大辛苦了，求过啊！
初学 Markdown，有什么地方写的不好也请多多包涵。


---

## 作者：Zq_water (赞：1)

思路很简单，我们把这个序列从两边去分配，就可以保证每组的权值相等

```cpp
#include <bits/stdc++.h>
using namespace std;
int a;
int main(){
	scanf("%d",&a);
	for(int i=1;i<=a*a/2;i++) cout<<i<<" "<<a*a-i+1<<endl;
	return 0;
}
```

---

## 作者：XBaiC (赞：0)

这么水的一道题题解竟然这么少，对本蒟蒻等只会刷水题的人写题解产生了莫大的鼓励，希望能帮到像我一样的广大蒟蒻们。

言归正传。作为一名 czs，一看到这道题就有一种熟悉感扑面而来。想必大家在小学时一定做过这样的题目，例如从 $1$ 加到 $100$ 的这种高斯求和的问题，一开始，数学老师们都会让我们这样去做：把 $1$ 和 $100$配对，$2$ 和 $99$ 配对，$3$ 和 $98$ 配对，$4$ 和 $97$ 配对，以此类推。这种经（hao）典（sha）的方法也能运用到这道题中。因为文中说“第 $i$ 块的权值为 $i$”，所以我们就能把它看作一个从 $1$ 到 $n$ 的平方的等差数列，这里分两种情况讨论：

1.$n$ 的平方为偶数

直接按照刚才配对的方法，把每组数挨个输出（记得要换行！），直接退出主程序就行了。

2.$n$ 的平方为奇数

整体思路和偶数的一样，但是要在输出时的最后一行输出中间的数。

好了，思路说完了，下面上 $AC$ 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main ()
{
    int n;
    scanf("%d",&n);  //标准输入
    if(n*n%2==0){  //判断是否为偶数
        for(int i=1,j=n*n;i<=j,j>=i;i++,j--)   //设i和j为循环变量
            cout<<i<<" "<<j<<"\n";  //输出
        return 0;  //完美结束
    }
    else {   //判断是否为奇数
        for(int i=1,j=n*n;i<j,j>i;i++,j--)  //设i和j为循环变量
            cout<<i<<" "<<j<<"\n";  //输出
        cout<<n*n/2+1<<"\n";  //输出中间的数
        return 0;  //完美结束
    }
}
```


---

## 作者：zwy__ (赞：0)

### 题目大意
PS：翻译有一些不清楚，从原题目中可以看出 $n$ 一定是偶数，所以，只用考虑 $n$ 为偶数的情况即可。

有 $n \times n$ 块糖果，第 $i$ 块糖果的价值为 $i$，并有 $n$ 个人，请输出让这 $n$ 个人分到的糖果价值平均的情况。
### 题目思路
我们仔细想一想，有 $n \times n$ 块糖果，并有 $n$ 个人，那么，每个人理应会被分到 $2$ 块糖果。现在我们就要进行思考：如何让每个人的两块糖价值相等。

想起题目的一个条件了吗，第 $i$ 块糖果的价值为 $i$，所以每一块糖果的价值是每一次都比前一颗糖价值要加 $1$，这时，我们的问题就可以转化为简单的分配问题了。我们只要定义两个指针，先从糖果的头和尾开始，每一次都将里面推进一次，到达终点时结束循环。这道题就迎刃而解了。
### 上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
int main()
{
    cin>>n;//输入 
    //由于n只可能为偶数，因此无须考虑其他情况
	//根据思路，定义两个指针，每次想里面缩进并输出答案即可 
    for(int i=1,j=n*n; i<=j,j>=i; i++,j--)
        cout<<i<<" "<<j<<endl;
    return 0;//完结撒花 
}
```

---

## 作者：二叉苹果树 (赞：0)

已通过的四篇题解，均审题不清，还有的过于复杂，这里指出错误并给出正解。



------------


### 误区

题面中的第一句话指出。

Gerald has $n$ younger brothers and their number happens to be even. 

也就是说，给出的 $n$ 都是偶数。

但是，已给出的题解中，大部分都分类讨论了。对于奇数部分，甚至有的给出了这部分错误的代码。



------------


### 正解

首先给出代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n*n/2;i++)
        cout<<i<<" "<<n*n-i+1<<endl;
    return 0;
}
```
题意就是让我们逐对输出两数 $a,b$ ，满足 $a+b=n^2+1$ 且 $a<b$ 即可，直接按照题意输出，没有任何冗余部分。

---

## 作者：DiDi123 (赞：0)

感觉这题最多红
# 题意
从 $n^2$ 个数（$1 \sim n^2$）中选择 $n$ 次，每次选择 $n$ 个数，问怎么选（$n$ 为偶数）。
# 分析
1.如果让我们每次只选两个数的话，其实非常好选，只需第 $i$ 次选择第 $i$ 个和第 $n^2-i+1$ 个即可。示图（以 $n=4$ 为例）：
![示图](https://cdn.luogu.com.cn/upload/image_hosting/vs6mcwu2.png)

**代码1：**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n * n / 2; i++)
		cout << i << ' ' << n*n - i + 1 << endl;
}
```

2.现在题目让一次选出 $n$ 个，注意到 $n$ 是偶数，所以可以每次选的时候，分为 $\frac{n}{2}$ 组，每组按照上面方法选择。由于评测机空格和换行不分，所以代码1也能侥幸水过。

3.（此部分可以跳过） 为了好看些，我们可以先每次选的时候按顺序输出（即第 $i$ 个人选的时候输出集合： $[\frac{n}{2}(i-1)+1 , \frac{n}{2} i] \cup [\frac{n}{2}(2n-i)+1,\frac{n}{2}(2n-i+1)]$ ）。

**代码2：**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = n * (i - 1) / 2 + 1; j <= n * i / 2; j++)
			cout << j << ' ';
		for (int j = n * (2 * n - i) / 2 + 1; j <= (2 * n - i + 1)*n / 2; j++)
			cout << j << ' ';
		cout << endl;
	}
}
```


---

