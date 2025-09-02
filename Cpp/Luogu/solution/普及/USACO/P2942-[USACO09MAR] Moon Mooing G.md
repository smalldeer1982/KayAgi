# [USACO09MAR] Moon Mooing G

## 题目描述

A full moon casts some sort of spell on the cows and, like their cousins the wolves and coyotes, they bay at the moon -- mooing instead of howling, of course.

Each 'moo' lasts a certain amount of time. A short 'moo' might last time 1; a longer one might last time 24 or even 1,000,000,000 or longer (cows can really moo when they want to). No 'moo' will last more than or equal to 2^63.

It should come as no surprise that the cows have a pattern to their moos.  Bessie will choose an integer c (1 <= c <= 100) that is the initial length of a moo.

After Bessie moos for length c, the cows calculate times for

subsequent moos. They apply two formulae to each moo time to yield even more moo times. The two formulae are:

```cpp
f1(c)=a1*c/d1+b1 (integer divide, of course) and 
f2(c)=a2*c/d2+b2. 
They then successively use the two new times created by evaluating f1(c) and f2(c) to create even more mooing times. They keep a sorted list of all the possible mooing times (discarding duplicates). 
They are allowed to moo a total of N times (1 <= N <= 4,000,000). Please determine the length of the longest moo before they must quit. 
The constants in the formulae have these constraints: 1 <= d1 < a1; d1 < a1 <= 20; 0 <= b1 <= 20; 1 <= d2 < a2; d2 < a2 <= 20; 0 <= b2 <= 20. 
Consider an example where c=3 and N=10. The constants are: 
a1=4    b1=3     d1=3 
a2=17   b2=8     d2=2 
```
The first mooing time is 3, given by the value of c. The total list of mooing times is:
```cpp
1. c=3             ->  3       6. f2(3)=17*3/2+8  -> 33 
2. f1(3)=4*3/3+3   ->  7       7. f1(28)=4*28/3+3 -> 40 
3. f1(7)=4*7/3+3   -> 12       8. f1(33)=4*33/3+3 -> 47 
4. f1(12)=4*12/3+3 -> 19       9. f1(40)=4*40/3+3 -> 56 
5. f1(19)=4*19/3+3 -> 28      10. f1(47)=4*47/3+3 -> 65 
The tenth time is 65, which would be the proper answer for this set of inputs. 
```
Partial feedback will be provided on the first 50 submissions.
MEMORY LIMIT: 64MB

满月的时候，和狼一样，牛们也在月光下叫，他们从不嚎叫，而是哞叫。

每次哞叫都有一个时长，可能是 $1$ 秒，可能是 $10^9$ 秒或更久，牛们真的非常能叫.当然，没有哞叫时长会超过或等于 $2^{63}$。

牛们的哞叫可以找到规律，这并不奇怪。贝茜会选择一个整数 $c(c\le100)$ 来作为初始时长之后，牛们根据两条公式确定更多的时长：

$f_1(c)=\lfloor a_1c/d_1\rfloor+b_1$

$f_2(c)=\lfloor a_2c/d_2\rfloor+b_2$ 

牛们用这两条公式不断地迭代、计算，算得大量的时长.然后她们将这些时长排序，剔除重复的时长，最后取前 $N(1<N< 4000000)$ 个整数为她们 $N$ 次哞叫的时长.请你计算，第 $N$ 次哞叫的时长是多少。公式中的常量均为整数，满足下列关系： 

$1 \le d_1 < a_1 \le 20$; $0\le b_1 \le 20$;

$1 \le d_2 < a_2 \le 20$; $0\le b_2\le 20$。


## 样例 #1

### 输入

```
3 10 
4 3 3 
17 8 2 
```

### 输出

```
65 
```

# 题解

## 作者：xzh15960292751 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P2942)

### 题目解析

个人觉得这一题不难，但是需要对题目有一定理解。\
第一次哞叫的时候，以 $c$ 秒作为初始时长。\
之后的时长有两个公式 \
$a_1\times \frac{c}{d_1} + b_1$。\
$a_2\times \frac{c}{d_2} + b_2$。\
每一次选择其中较小的一项放入数组，最后输出数组的第 $n$ 项。

特别的，如果两项为一样的，在随意放入一项的同时 $ans_1,ans_2$ 都要加一。

### 具体做法

首先可以看到，时间 $1 < N < 4 \times 10^6$ 所以，将暴力枚举的方法 pass 掉（当然，不包括打表）。\
但正是这一个数据范围，让我看到了一线生机。\
可以采用模拟的方法，模拟。\
模拟从 $1$ 到 $n$ 次的哞叫时长。\
定义两个变量 $ans_1,ans_2$ 初值为 $1$。\
将数组的第一位数字初值赋值为 $c$ 用 while 循环从 $2$ 到 $n$ 进行遍历。\
如果 $f_1>f_2 \to ans_1+1$ 将 $f_1$ 放入数组。\
如果 $f_2>f_1 \to ans_2+1$ 将 $f_2$ 放入数组。\
如果两数相等，像上文说的 $ans_1+1,ans_2+1$ 将 $f_1,f_2$ 任意一个放入数组。\
在上述操作中，有一点要注意，我们用于存储位数的 $i$ 每一次都要加一，直到 $i = n$ 就可以输出结果。

### AC Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
//定义题目中所给的变量
int n, c;
int timing[5000010];// timing[i] 表示第i次哞叫时长
int f1, f2, ans1, ans2;
int a1, a2, b1, b2, d1, d2;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	// 先按题目要求输入 
	cin >> c >> n;
	cin >> a1 >> b1 >> d1 >> a2 >> b2 >> d2;
	// 初始化 
	memset(timing, 0, sizeof timing);
	// 更改一下首位值 
	timing[1] = c;
	ans1 = ans2 = 1;
	int i = 1;
	while(i != n) {
		// 题目中所给公式
		// timing[ans1] 和 timing[ans2] 为上一次存储的哞叫声长度
		f1 = a1 * timing[ans1] / d1 + b1;
		f2 = a2 * timing[ans2] / d2 + b2;
		if(f1 < f2) timing[++i] = f1, ans1++;
		else if(f1 > f2) timing[++i] = f2, ans2++;
		else timing[++i] = f1, ans1++, ans2++;
//		cout << timing[i] << ' ' << ans1 << ' ' << ans2 << '\n';
	}
	// 据题意排序 
	sort(timing + 1, timing + n + 1);
	cout << timing[n] << '\n';
	return 0;
}
```

---

## 作者：幽界の冥神 (赞：5)

本题类似于（应该就是）一个简单的“归并排序”，但注意要用 long long 类型。

做法很简单：

1.输入（不多说了）

2.将两种运算方法记录到函数中（直接调用）

3.FOR循环，使用双下标技术，分情况讨论（三种）：

(1).tmp1 < tmp2 ———— 将第一种方式归入数组

(2).tmp1 > tmp2 ———— 将第二种方式归入数组

(3).tmp1 = tmp2 ———— 将第一（或第二）种方式归入数组 双下标同时+1 （去重）

4.输出。。。完毕

-----------------------------------一道分割线-------------------------------------------------







```cpp
#include "cstdio"
#include "iostream"
#define LL long long
using namespace std;
const int Size = 4000002;
int f1 = 1, f2 = 1, a1, a2, b1, b2, d1, d2, c, n;//f1=f2=1：双下标同时指向f[1]。
LL f[Size];
LL ff ()//第一种运算
{
    return a1 * f[f1] / d1 + b1; 
}
LL fs ()//第二种运算
{
    return a2 * f[f2] / d2 + b2;
}
void init ()//初始化————输入（不多说了）
{
    scanf ("%d %d", &c, &n);
    scanf ("%d %d %d", &a1, &b1, &d1);
    scanf ("%d %d %d", &a2, &b2, &d2);
    f[1] = c;//f[1]设为c初始值
}
void work ()
{
    for (int i = 2; i <= n; i++)//FOR循环，使用双下标技术，分三种情况讨论
    {
        LL tmp1 = ff (), tmp2 = fs ();//双下标先做运算
        if (tmp1 < tmp2)//较小值归入数组
        {
            f[i] = tmp1;
            ++f1;
        }
        else if (tmp1 > tmp2)//同上。。。
        {
            f[i] = tmp2;
            ++f2;
        }
        else if (tmp1 == tmp2)//相等时去重
        {
            f[i] = tmp1;
            ++f1;
            ++f2;
        }
    }
    cout<<f[n]<<endl;//华丽丽的输出
}
int main ()
{
    init ();
    work ();
    return 0;
}
```
-----------------------------------另一道分割线-------------------------------------------------
PS：如果想练手，那么，“瑞士轮” 是个好选择


---

## 作者：x_faraway_x (赞：4)

这题我一开始使用优先队列（STL中的priority\_queue）来做，结果WA+TLE。其实本题只要用数组进行简单的模拟即可。当然也用到了队列的思想。具体见下面的代码：

```cpp
#include <cstdio>
#include <iostream>
typedef unsigned long long ull; //注意本题要用unsigned long long。
const int N = 4000000; 
ull a[N+5]; //这里我们将a数组看成一个队列
inline ull mn(ull x, ull y) {
    return x < y ? x : y;
}
int main() {
    int c, n, a1, b1, d1, a2, b2, d2, i = 1, f1 = 1, f2 = 1;
    scanf("%d%d%d%d%d%d%d%d", &c, &n, &a1, &b1, &d1, &a2, &b2, &d2);
    a[i++] = c; //初始元素c入队
    while(i <= N) {
        ull x = mn(a1*a[f1]/d1+b1, a2*a[f2]/d2+b2); //取F1()和F2()中的较小值
        a[i++] = x; //将该较小值入队
        if(x == a1*a[f1]/d1+b1) f1++; //如果较小值来自F1()，则将F1()的指针f1+1。
        if(x == a2*a[f2]/d2+b2) f2++; //如果较小值来自F2()，则将F2()的指针f2+1
    } //重点理解while循环的内容。因为算出的F1()或F2()的数据单调递增，所以可以用这样的方式生成整个数列
    std::cout << a[n]; //最后输出即可。
    return 0;
}
//祝各位早日AC此题！
```

---

## 作者：ljc2230 (赞：3)

今天我们来写 P2942 的题解。[题目链接](https://www.luogu.com.cn/problem/P2942)

### 题目解析

满月的时候，牛们会在月光下叫，他们从不嚎叫，而是哞叫。\
第一次哞叫的时候，以 $c$ 秒作为初始时长。\
之后的时长有两个公式：

1.$a_1 \times c\div d_1+b_1$。  
2.$a_2 \times c\div d_2+b_2$。  

### 具体做法

可以采用模拟的方法模拟哞叫时长。\
首先定义两个变量 $ans_1,ans_2$ 初值为 $1$。\
将数组的第一位数字初值赋值为 $c$ 用 `while` 循环从 $2 \sim n$ 进行遍历。\
如果 $f_1>f_2$ 那么 $ans_1\gets ans_1+1$，将 $f_1$ 放入 $a$ 数组。\
如果 $f_2>f_1$ 那么 $ans_2\gets ans_2+1$，将 $f_2$ 放入 $a$ 数组。\
如果两数相等 $ans_1\gets ans_1+1$，$ans_2\gets ans_2+1$，将 $f_1$ 和 $f_2$ 任意一个放入数组。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,c;
int a1,a2,b1,b2,d1,d2;
int ans1,ans2;
long long a[4000005];

int main(){
	cin>>c>>n;
	cin>>a1>>b1>>d1;
	cin>>a2>>b2>>d2;
	a[1]=c;
	ans1=ans2=1;
	int i=1;
	while(i<=n){
		long long f1=a1*a[ans1]/d1+b1;
		long long f2=a2*a[ans2]/d2+b2;
		if(f1<f2){//如果f1<f2
			a[++i]=f1;
			ans1++;
		}
		else if(f1>f2){//如果f1>f2
			a[++i]=f2;
			ans2++;
		}
		else {//如果f1=f2
			a[++i]=f1;
			ans1++;
			ans2++;
		}
	}
	cout<<a[n];
	return 0;
}
```

---

## 作者：lbh123 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P2942)
## 题意：
给定初始哞叫声音时间 $c$，有两个公式：

- $f_1(c)=\lfloor a_1c/d_1\rfloor+b_1$

- $f_2(c)=\lfloor a_2c/d_2\rfloor+b_2$ 

要求通过这两个公式对 $c$ 进行计算，将得出的得数接着通过这两个公式计算，最后询问整个得数的集合经过排序和去重后第 $n$ 项是什么。
## 思路：
运用模拟算法来模拟计算哞叫时长，具体步骤如下：
1. 根据题目所给出的公式计算出两个公式的结果 $ans1$ 和 $ans2$。
2. 分情况讨论，对答案集合 $ans$ 排序，即：
- 当 $ans1<ans2$ 时，将 $ans1$ 放入答案集合 $ans$ 中，第一个公式计算下一个哞叫时间。
- 当 $ans1>ans2$ 时，将 $ans2$ 放入答案集合 $ans$ 中，第二个公式计算下一个哞叫时间。
- 当 $ans1=ans2$ 时，随便选一个放入答案集合 $ans$ 中，两个公式一起计算下一个哞叫时间，这里相当于去重。
3. 输出答案。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans[4000010];//答案集合
long long c,n,a1,b1,d1,a2,b2,d2;//定义各种变量，名字与题意一样。
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//关闭同步流（其实不关好像也能过）
	cin>>c>>n;
	cin>>a1>>b1>>d1;
	cin>>a2>>b2>>d2;
	long long id1=1,id2=1;//分别标记两个公式计算到哪里。
	ans[1]=c;
	for(int i=2;i<=n;i++){
		long long ans1=a1*ans[id1]/d1+b1;
        long long ans2=a2*ans[id2]/d2+b2;
		if(ans1<ans2){
			ans[i]=ans1;//将ans1放入答案集合中
			id1++;      //标记计算下一个哞叫时间
		}else if(ans1>ans2){
			ans[i]=ans2;//将ans2放入答案集合中
			id2++;      //标记计算下一个哞叫时间
		}else{//去重
			ans[i]=ans1;
			id1++;
			id2++;
		}
	}
	cout<<ans[n]<<"\n";//由于已经去过重，排过序了，直接输出。
	return 0;
}
```
## 后记
十年 OI 一场空，不开 long long 见祖宗。

完结撒花。

---

## 作者：__yiLIUyi__ (赞：1)

# 题解：P2942 [USACO09MAR] Moon Mooing G
[题目传送门](https://www.luogu.com.cn/problem/P2942)
## 简化题意
第一行给出 $c$ 和 $n$，第二行给出 $a_1$ 和 $b_1$ 和 $d_1$ 三个数，第三行给出 $a_2$ 和 $b_2$ 和 $d_2$ 三个数。然后用两条公式不断地迭代、计算，剔除重复的时长，取前 $N$ 个整数为 $N$ 次哞叫的时长。

也就是说，求 $a_n$ 的数值。
## 大致思路
首先定义数组 $a$，长度为 $n$，用来储存每一次的叫声。使得 $a_1$ 的值为 $c$。

然后使用循环迭代，每一次使用两个公式（$f_1=a_1 \times c \div d_1 + b_1$ 和 $f_2=a_2 \times c \div d_2 + b_2$）求出 $f_1$ 和 $f_2$。

```cpp
f1=a1*a[m1]/d1+b1;
f2=a2*a[m2]/d2+b2;
```

然后，在每一次循环中，都对 $f_1$ 和 $f_2$ 进行判断。分为三种情况：
- 如果 $f_1 < f_2$，那么 $a_i$ 赋值为 $f_1$，且 $m_1$ 要加一；
- 如果 $f_1 > f_2$，那么 $a_i$ 赋值为 $f_2$，且 $m_2$ 要加一；
- 如果 $f_1 = f_2$，那么 $a_i$ 赋值为 $f_1$，且 $m_1$ 与 $m_2$ 都要加一。

```cpp
if(f1<f2){
	a[i]=f1;
	m1++;
}else if(f1>f2){
	a[i]=f2;
	m2++;
}else{
	a[i]=f1;
	m1++,m2++;
}
```

可以化简为：
- $a_i$ 等于 $f_1$ 和 $f_2$ 中的较小值；
- 如果 $f_1 \le f_2$，那么 $m_1$ 要加一；
- 如果 $f_1 \ge f_2$，那么 $m_2$ 要加一。

```cpp
a[i]=min(f1,f2);
if(f1<=f2)m1++;
if(f1>=f2)m2++;
```

其它内容放在代码里了。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll a[4000010],c,n,a1,b1,d1,a2,b2,d2,m1=1,m2=1,f1,f2;
int main(){
	cin>>c>>n>>a1>>b1>>d1>>a2>>b2>>d2;
	a[1]=c;
	for(ll i=2;i<=n;i++){
		f1=a1*a[m1]/d1+b1;
		f2=a2*a[m2]/d2+b2;
		a[i]=min(f1,f2);
		if(f1<=f2)m1++;
		if(f1>=f2)m2++;
	}cout<<a[n];
	return 0;
}
```

---

## 作者：xw_qwq (赞：1)

## P2942 [USACO09MAR] Moon Mooing G
[题目传送门](https://www.luogu.com.cn/problem/P2942)

### 题目思路
其实这就是一道简单的模拟题。

以 $c$ 作为第一次的初始时长，然后从 $2$ 遍历到 $n$，套入公式 $f_1(c)=\lfloor a_1 \times c \div d_1\rfloor+b_1$ 和 $f_2(c)=\lfloor a_2 \times c \div d_2\rfloor+b_2$。

用双指针维护两个公式中的 $c$，每次判断两个式子的结果 $ans_1$ 和 $ans_2$，选择其中较小的那个加入数组，并将对应的指针加一，模拟完成后输出 $a_n$ 即可。

### 注意点
数据范围大！！不开 $long long$ 见祖宗！！！

### 代码

```cpp
#include <iostream>
#define int long long
using namespace std;
int a[4000005];
signed main()
{
	int c, n, a1, b1, d1, a2, b2, d2;
	int p1 = 1, p2 = 1;
	cin >> c >> n >> a1 >> b1 >> d1 >> a2 >> b2 >> d2;
	a[1] = c;
	for (int i = 2; i <= n; i++)
	{
		int ans1 = a1 * a[p1] / d1 + b1, ans2 = a2 * a[p2] / d2 + b2;
		if (ans1 < ans2)
			p1++, a[i] = ans1;
		else if (ans2 < ans1)
			p2++, a[i] = ans2;
		else
			p1++, p2++, a[i] = ans1;
	}
	cout << a[n];
	return 0;
}

```

---

## 作者：furina_yyds (赞：0)

这题并不难，只是难理解。

## 思路

一共有两个公式：

- $a_1 \times c \div d_1 + b_1$
- $a_2 \times c \div d_2 + b_2$

采用模拟的方法模拟哞叫时长即可。

1. 根据公式，计算时长
2. 对存储时长的容器进行排序，可以使用 `std::sort` 函数。
3. 去重操作，可以使用 `std::unique` 函数，该函数将重复元素移到容器末尾，并返回指向第一个重复元素的迭代器，然后使用 `erase` 函数将这些重复元素删除。

## 注意

多测不清空，爆零两行泪。

## 代码

```cpp
#include <iostream>
#include <vector>

int main() {
    // 输入的初始值和参数
    int initialValue, numIterations;
    int coefficient1, offset1, divisor1;
    int coefficient2, offset2, divisor2;
    // 存储结果的向量
    std::vector<long long> resultVector;
    // 用于迭代的索引
    int index1 = 0, index2 = 0;

    // 输入部分
    if (!(std::cin >> initialValue >> numIterations >> coefficient1 >> offset1 >> divisor1 >> coefficient2 >> offset2 >> divisor2)) {
        std::cerr << "输入错误，请输入有效的整数数据。" << std::endl;//防伪标识
        return 1;
    }

    resultVector.push_back(initialValue);
    for (int i = 1; i < numIterations; ++i) {
        long long value1 = static_cast<long long>(coefficient1) * resultVector[index1] / divisor1 + offset1;
        long long value2 = static_cast<long long>(coefficient2) * resultVector[index2] / divisor2 + offset2;
        if (value1 < value2) {
            resultVector.push_back(value1);
            ++index1;
        } else if (value1 > value2) {
            resultVector.push_back(value2);
            ++index2;
        } else {
            resultVector.push_back(value1);
            ++index1;
            ++index2;
        }
    }

    if (numIterations > 0) {
        std::cout << resultVector[numIterations - 1] << std::endl;
    } else {
        std::cerr << "迭代次数应为正数。" << std::endl;//防伪标识
        return 1;
    }

    return 0;
}
```

---

## 作者：Gcc_Gdb_7_8_1 (赞：0)

我们上来一看，马上可以想到先求出 $N$ 项 $f_1$ 和 $N$ 项 $f_2$，然后排序。复杂度 $O(N \log N)$，但 $N \le 4 \times 10^6$，超时。

稍加思考，我们可以想到这样的算法：  
1. 建立队列 $q_1$，$q_2$，$num$。
2. 将 $c$ 加入 $q_1$，$q_2$ 和 $num$。
3. 比较 $f_1$（$q_1$ 的队头）和 $f_2$（$q_2$ 的队头），谁小把谁加入 $num$，并移出对应队列的队头。
4. 如果 $num$ 的长度小于 $N$，那么回到第三步，否则输出 $num$ 的第 $N$ 项。

我们发现 $q_1$ 和 $q_2$ 一直包含于 $num$，所以可以共用一个数组以节省空间。

核心代码：

```cpp
int c, N;
cin >> c >> N;
int a1, b1, d1;
int a2, b2, d2;
cin >> a1 >> b1 >> d1;
cin >> a2 >> b2 >> d2;
num[++tail] = c;
while (tail < N) {
	if (f1(num[q1head]) > f2(num[q2head])) {
		num[++tail] = f2(num[q2head]);
		++q2head;
	} else if (f1(num[q1head]) < f2(num[q2head])) {
		num[++tail] = f1(num[q1head]);
		++q1head;
	} else {
		num[++tail] = f1(num[q1head]);
		++q1head;
		++q2head;
	}
}
cout << num[N] << endl;
```

---

## 作者：4041nofoundGeoge (赞：0)

这道题~~很毒瘤~~不难用到了归并算法的思想。

## 前置知识

分治（Divide and Conquer），字面上的解释是“分而治之”，就是把一个复杂的问题分成两个或更多的相同或相似的子问题，直到最后子问题可以简单的直接求解，原问题的解即子问题的解的合并。

### 过程

分治算法的核心思想就是“分而治之”。大概的流程可以分为三步：分解到解决再到合并。

1. 分解原问题为结构相同的子问题。
2. 分解到某个容易求解的边界之后，进行递归求解。
3. 将子问题的解合并成原问题的解。

分治法能解决的问题一般有如下特征：

1. 该问题的规模缩小到一定的程度就可以容易地解决。
2. 该问题可以分解为若干个规模较小的相同问题，即该问题具有最优子结构性质，利用该问题分解出的子问题的解可以合并为该问题的解。
3. 该问题所分解出的各个子问题是相互独立的，即子问题之间不包含公共的子问题。

更多信息请自行查阅 [OI WIKI](https://oi-wiki.org/basic/divide-and-conquer/#%E5%AE%9A%E4%B9%89_1)。

## 思路

题目中描述：

> 牛们用这两条公式不断地迭代、计算，算得大量的时长。然后她们将这些时长排序，剔除重复的时长，最后取前 $N(1<N< 4000000)$ 个整数为她们 $N$ 次哞叫的时长。请你计算，第 $N$ 次哞叫的时长是多少。

依据题意可以想到我们就是把两个数分别做 $F1$ 和 $F2$ 两种操作，得到的两个数，较小的一个存进归并数组，如果一样则双指针同时指向下一个数，也就是相当于去重（当然可以用堆做）。形式化思路：

若设有两个函数 $F1(x)=⌊\frac{a_1c}{d_1}⌋+b_1$ 和 $F2(x)=⌊\frac{a_2c}{d_2}⌋+b_2$，设每一次进行计算出的值为 $t_1=F1(c),t_2=F2(c)$，进行 $f(t_1,t_2)$ 的操作。其中：

$$
f(t_1,t_2) = \begin{cases}
 g(t_1) & t_1<t_2 \\
 g(t_2) & t_2<t_1 \\
 去重 & t_1=t_2
\end{cases}
$$

$g(x)$ 代表将 $x$ 加入到数组里。

有了以上的分析，五分钟~~小时~~即可写出代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int f1 = 1, f2 = 1, a1, a2, b1, b2, c, d1, d2;
long long f[4000005];
int main()
{
    int n;
    cin >> c >> n;
    cin >> a1 >> b1 >> d1 >> a2 >> b2 >> d2;
    f[1] = c;
    for (int i = 2; i <= n; i++) {
        long long s1 = a1 * f[f1] / d1 + b1,
                  s2 = a2 * f[f2] / d2 + b2;
        if (s1 < s2)
            f[i] = s1, f1++;
        else if (s1 > s2)
            f[i] = s2, f2++;
        else
            f[i] = s1, f1++, f2++;
    }
    cout << f[n];
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

# 题目分析

简单题意分析：给定一个数 $c$，对 $c$ 进行 $a_1\times c/d_1+b_1$ 的操作和 $a_2\times c/d_2+b_2$ 的操作，每次选取较小值并放入数组，下一次操作的输入为前一次操作的结果。最后输出数组的第 $n$ 项。

具体实施：使用双指针 $i$ 和 $j$，$i$ 指向操作 $1$ 的输入， $j$ 指向操作 $2$ 的输入。可以循环 $n$ 次，每次计算出相应的各操作的值，比较两值。这里令操作 $1$ 的值为 $f1$，操作 $2$ 的值为 $f2$（按题目中所给）。比较过程可以分类讨论：

- 若 $f1<f2$，则选取 $f1$ 放入数组，将指针 $i$ 加一。
- 若 $f2<f1$，则选取 $f2$ 放进数组，将指针 $j$ 加一。
- 若两值相等，那么将任意一值放入数组。两个指针都加一，因为要保证去重。

执行完上述操作后，输出数组第 $n$ 项即可。
# AC 代码

```cpp
#include<iostream>
using namespace std;
int main(){
	long long n,k,a1,a2,a3,b1,b2,b3,h=1;
	cin>>n>>k>>a1>>a2>>a3>>b1>>b2>>b3;
	long long t=1,temp[4000001]={0},i=0,j=0;
	temp[0]=n;
	while(h<k){
		long long f1=a1*temp[i]/a3+a2;
		long long f2=b1*temp[j]/b3+b2;
		if(f1<f2){
			temp[h++]=f1;
			i++;
			continue;
		}
		else if(f2<f1){
			temp[h++]=f2;
			j++;
			continue;
		}
		else{
			temp[h++]=f1;
			i++;
			j++;
		}
		continue;
		
	}
	cout<<temp[k-1];
	return 0;
}
```


---

## 作者：MaLX (赞：0)

~~水篇题解再整点活。~~

### 简要题意

给定两种计算方式和数列第 $1$ 项，求第 $n$ 项。

### 解法

因为 $a_i \le d_i$ 且 $b_i \ge 0$ 所以每种计算方式都会使序列非严格单调递增。

有没有发现像极了[这个题](http://ybt.ssoier.cn:8088/problem_show.php?pid=1333)。

开两个队列每次取生成的最小结果，操作 $n$ 次，搞定。

### 上代码

~~码风诡异~~。

``` c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int main(){return 0;}
#include<queue>
queue<long long>a,b;
int c,n,a1,a2,b1,b2,d1,d2;
struct solve{solve(){
	scanf("%d%d%d%d%d%d%d%d",&c,&n,&a1,&b1,&d1,&a2,&b2,&d2);
	a.push(c);b.push(c);
	for(int i=1;i<n;i++){
		long long ai=a1*a.front()/d1+b1,bi=a2*b.front()/d2+b2,maxn=min(ai,bi);
		a.push(maxn),b.push(maxn);if(ai==maxn)a.pop();if(bi==maxn)b.pop();
	}
	printf("%lld",a.back());
}}mal_solve;
```

---

