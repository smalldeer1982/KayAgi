# [AGC015A] A+...+B Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc015/tasks/agc015_a

すぬけ君は、整数を $ N $ 個持っています。このうち最小のものは $ A $、最大のものは $ B $ です。すぬけ君が持っている整数の総和としてありうる値は何通りあるでしょうか。

## 说明/提示

### 制約

- $ 1\ ≦\ N,A,B\ ≦\ 10^9 $
- $ A,B $ は整数である

### Sample Explanation 1

$ 18=4+4+4+6,19=4+4+5+6,20=4+5+5+6,21=4+5+6+6,22=4+6+6+6 $ の $ 5 $ つの値が総和として考えられます。

## 样例 #1

### 输入

```
4 4 6```

### 输出

```
5```

## 样例 #2

### 输入

```
5 4 3```

### 输出

```
0```

## 样例 #3

### 输入

```
1 7 10```

### 输出

```
0```

## 样例 #4

### 输入

```
1 3 3```

### 输出

```
1```

# 题解

## 作者：dblark (赞：10)

这道题目，先来说一下思路。

先求最小值和最大值：

显而易见：$min=b+a\times (n-1)$以及$max=a+b\times (n-1)$。

那么，方案数就是$max-min+1$了。

我们可以整理一下：

$$max-min+1\qquad\qquad\qquad\qquad\ $

$$=a+b\times (n-1)-b-a\times (n-1)+1$$

$$=b\times (n-2)-a\times (n-2)+1\qquad\quad\ $$

$$=(b-a)\times (n-2)+1\qquad\qquad\qquad\ \ \ $$

~~亏我打了一堆LaTeX空格~~

然后题目就简单了。

这道题，说两个坑点：

1.可能会出现$a>b$的情况，需要特判；

2.$n=1$的时候一定要特判，一般情况下输出$0$，然而$a=b$的时候就比较尴尬。

注意到这些就能轻松AC了。

贴上~~丑陋~~的Pascal代码：（这年头几乎没有活人资瓷Pascal了）

```pas
{AT2379}
var
n,a,b:longint;
begin
  read(n,a,b);
  if a>b then             //坑点1
    writeln(0)
  else
    if n=1 then           //此处有坑点2
      writeln(ord(a=b))   //Pascal中布尔可以用ord转数字
    else
      writeln((b-a)*(n-2)+1);
end.
```

---

## 作者：MilkyCoffee (赞：4)

$$\color{red}\boxed{\text{小奥}}$$

$\boxed{\text{思路区}}$

$\text{我们先求最小值和最大值，就可以求出方案数量。}$

最小值 ：$b$ $+$ $a$ $×$ $($ $n$ $−$ $1$ $)$

最大值 ：$a$ $+$ $b$ $×$ $($ $n$ $−$ $1$ $)$

那么，方案数就是 $\text{最大值-最小值+1}$

$\boxed{\text{你肯定会掉进去的坑}}$

1. 不保证 $n > 1$。

2. 不保证 $a<=b$。

3. 不开 $long$ $long$ 见祖宗

我们把完整代码放一下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
	long long n,a,b;
	cin >> n >> a >> b;
	if (n > 1 && b >= a || n == 1 && a == b) cout << (n - 2) * (b - a) + 1 << endl;
	else cout << 0 << endl; 
    return 0;
 } 
```


---

## 作者：Cambridge (赞：2)


蒟蒻又来发题解了！

这道题也就是一道小学奥数题目吧，具体思路如下：

> *  $min=B+A(N-1)$
> *  $max=A+B(N-1)$

### 那么，方案数就是$max-min+1$了！

你以为就这么简单就结束了？当然不了，看下面的坑：

> * 你确定$N>1$?
> * 你确定$A<=B$?
> * 你确定你没看见$1 ≦ N,A,B ≦ 10^9$？

于是，知道思路，知道坑点之后，代码就很简单了，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n,a,b;
int main()
{
	cin>>n>>a>>b;
	if(n==1&&a==b)cout<<1;//如果只有一个数
	else if(n>1&&b>=a)cout<<(n-2)*(b-a)+1;//具体为什么看上方解释
		 else cout<<0;//如果不行
	cout<<endl;//记得换行
    return 0;
 } 
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：杨瀚雄白羊 (赞：2)

这个题已经有一位红名大佬发布了思路版题解

我就在这里接着他的思路打一遍代码（水）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,a,b;//这题范围到了三个10^9,合起来可能有10^18,一定要开long long
	cin>>n>>a>>b;
	if(n>1&&b>=a||n==1&&a==b)//本题精华之特判,n=1的时候最大数和最小数必须一致,因为只有一个数,其他的时候就只要满足a>=b即可
		cout<<(n-2)*(b-a)+1<<endl;//按照(n-2)*(a-b)+1的思路打的代码,其实我也想到了(笑)
	else
		cout<<0<<endl; 
 } 
```

#### 祝大家都能开开心心地过题

---

## 作者：cyn2006 (赞：2)

为什么又是小奥题？

**~~蛤我红名了也~~**

## 题目数据不全，最好补齐或者直接去原题看

**证明：**

```cpp
Sample Input 1
4 4 6
Sample Output 1
5

There are five possible sums: 18=4+4+4+6, 19=4+4+5+6, 20=4+5+5+6, 21=4+5+6+6 and 22=4+6+6+6.

Sample Input 2
5 4 3
Sample Output 2
0

Sample Input 3
1 7 10
Sample Output 3
0

Sample Input 4
1 3 3
Sample Output 4
1

注意，这里不保证n>1，a<=b

最小为a，则n个数除去a+b的最小和为 a*(n-2) (Min_sum)

最大为b，则n个数除去a+b的最大和为 b*(n-2) (Max_sum)

于是总个数为 (Min_sum-Max_sum+1) (别忘了一些关于n，b，a的特判)

Code就不贴了

namespace AT2379{
	string rp="NOIP rp++";
    string score="NOIP score++";
}using namespace AT2379;
int main(){
	cout<<rp<<'\n'<<score<<'\n';
    return 233;
}
```

---

## 作者：CZQ_King (赞：1)

~~这种题怎么能少了py呢~~

根据红名大佬的思路打一遍$Python3$的题解。


------------
代码：
```
n,a,b=map(int,input().split()) #多个输入，注意不能用多个input，否则会RE
if n>1 and b>=a or n==1 and a==b: #如果符合要求
    print ((n-2)*(b-a)+1); #根据公式输出
else:
    print ("0"); #不符合要求的就直接输出0
```

---

## 作者：naroanah (赞：0)

先说结论：

这 $N$ 个数和的最小值一定是 $A \times (n-1)+B$ （至少有一个最大值）；最大值一定是 $B \times (n-1)+A$ （至少一个最小值）。

因为每一个数可以是 $[A,B]$ 之间的任意一个，所以最后的和也可以是 $[MinSum,MaxSum]$ 之间的任意一个，答案就是 $MaxSum-MinSum+1$。

记得注意一下 $n=1$ 和 long long 就好了。

---

## 作者：梦游的小雪球 (赞：0)

## 梦雪的思路：

1. 最小值：$ n-1 $个A，1个B，即$ minn=(n-1)\times A+B $。

1. 最大值：1个A，$ n-1 $个B，即$ maxn=(n-1)\times B+A $。

1. 结果可以是$ minn $到$ maxn $中的每一个数（含$ minn $,$ maxn $）。

1. 所以结果的数量为 $ maxn-minn+1 $。


## 注意！！！

1. 题目并不能保证$ n>1 $。

1. 题目不能保证$ a \leq b $

1. 不开long long即可免费领取见祖宗一日。

## AC代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,a,b;
int main(){
	cin>>n>>a>>b;
	if((n>1&&b>=a)||(n==1&&a==b))
		cout<<(n-2)*(b-a)+1<<endl;//同思路
	else
		cout<<0<<endl;//其他的情况
	return 0;
}
```
望通过QWQ（这次没有问题了吧）

---

## 作者：Pkixzx (赞：0)

一开始看题时，我还有些看不懂，但多读几遍题后，才发现这是一道小学奥数题。

我们首先求出最小值和最大值。

最小值就是除了一个最大数，其他全为最小数，公式为：min=B+A*（n-1）。

最大值就是除了一个最小数，其他全为最大数，公式为：max=A+B*（n-1）。

那么最后的答案怎么求呢？运用小学奥数的知识，我们可以知道是：最大值-最小值+1。套用到这里，就是max-min+1。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
   long long n,i,j,k,m,x,y,t=0,min,max;
    cin>>n>>x>>y;
    if(x>y) //题目中没有说A<B，所以这里要特判
    {
    	cout<<"0";
    	return 0;
	}
	max=(x+y*(n-1));//求最大值
	min=(y+x*(n-1));//求最小值
	cout<<max-min+1;
    return 0;
}
```


---

## 作者：小咪 (赞：0)

又是一题小学奥数？！

根据前面各位大佬的思路打了一遍C++题解。

比较坑的是这里不保证n>1，a<=b。
--
先求最小值和最大值：

最小值=min=b+a×(n−1);

最大值=max=a+b×(n−1)。

那么，方案数就是max−min+1了。
--

~~你们最爱看的~~代码来了！
==
```c
#include<bits/stdc++.h>//万能头文件
using namespace std;//未命名空间
long long n,a,b;//根据提示开long long
int main()
{
	cin>>n>>a>>b;
	if(n>1 && b>=a || n==1 && a==b)//判断
		cout<<(n-2)*(b-a)+1<<endl;//根据公式输出
	else
		cout<<"0"<<endl; //如果不符合输出0
    return 0;
} 
```

---

