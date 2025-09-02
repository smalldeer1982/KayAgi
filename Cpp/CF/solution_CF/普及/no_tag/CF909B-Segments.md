# Segments

## 题目描述

You are given an integer $ N $ . Consider all possible segments on the coordinate axis with endpoints at integer points with coordinates between 0 and $ N $ , inclusive; there will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF909B/150441d31156a32e0b2da63844d600138a543898.png) of them.

You want to draw these segments in several layers so that in each layer the segments don't overlap (they might touch at the endpoints though). You can not move the segments to a different location on the coordinate axis.

Find the minimal number of layers you have to use for the given $ N $ .

## 说明/提示

As an example, here are the segments and their optimal arrangement into layers for $ N=4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF909B/d28bd213a6c0995aff826b2bebd914bef9ec9fa5.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
4
```

### 输出

```
6
```

# 题解

## 作者：FP·荷兰猪 (赞：8)

**找规律：第n项为2\*第n-1项-2\*第n-3项+第n-4项。**

前四项为1，2，4，6。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans[105];
int main()
{
    int n;
    cin>>n;
    int i;
    ans[0]=0;//打表，前四项
    ans[1]=1;
    ans[2]=2;
    ans[3]=4;
    ans[4]=6;
    for(i=5;i<=100;i++)
    {
        ans[i]=2*ans[i-1]-2*ans[i-3]+ans[i-4];//神奇的公式（如上）
    }
    cout<<ans[n]<<endl;
    return 0;
}
```

---

## 作者：Dry_ice (赞：3)

好长时间没水红题题解了，现在来水一发 ~~（好不容易发现了一题~~。

这道题直接算一算，就可以找到如下的公式：
$$A_1=0$$
$$A_2=1$$
$$A_3=2$$
$$A_4=4$$
$$A_4=6$$
$$A_i=2*A_{i-1}-2*A_{i-3}+A_{i-4}(i\geq5)$$

所以，直接递推就行了。

## CODE
```cpp
#include<stdio.h>
int main(void) {
	int n;
	scanf("%d", &n);
	int a[101] = {0, 1, 2, 4, 6};
	for(int i = 5; i <= n; ++i)
		a[i] = (a[i-1] << 1/*左移更快*/) - (a[i-3] << 1) + a[i-4];
	printf("%d\n", a[n]);
	return 0;
}
```

## The end. Thanks.

~~（走过路过一定要赞过啊~~

---

## 作者：超级玛丽王子 (赞：2)

一道神奇的找规律，果然 CF 都是结论题。

这道题目直接 $O(1)$ 解决完事。然而我不是如爬行者巨佬一样打表生看，而是~~严谨~~证明这个规律。

首先将所有可能的线段按左端点排序，再按右端点排序。（注：均为从小到大）。贪心地枚举 $i$：如果 $[i,i+1]$ 这个线段在某一层是空闲的（即未被占据的），那么就在那里放下这一条线段。否则建一个新的层。显然，最优的情况是这些线段向中点靠拢。故此，答案为 $(\lfloor \dfrac N 2\rfloor+1)\times\lceil\dfrac N 2\rceil$。当然你也可以盲猜中点是最优结果（很多情况都是这样的）。

## 完结撒花~ 求赞求互关QAQ

---

## 作者：Lithium_Chestnut (赞：2)

又是一道神奇的找规律题。

开始推规律：

先写几项看看：

$a_1=1$，$a_2=2$，$a_3=4$，$a_4=6$。

emmm...好像没找到什么规律。

没事，继续往下看。

$a_5=9$，$a_6=12$。

貌似找到了规律。

在 $a \geq 5$ 的情况下，$a_i=a_{i-1} \times 2-a_{i-3} \times 2+a_{i-4}$。

那么这道题目的正解就出来了。

前四项打表，数据范围写了最大值是 $100$，那么就从 $5$ 到 $100$ 开始暴力枚举。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[101]={0,1,2,4,6};
int main()
{
	cin>>n;
	for(int i=5;i<=100;i++) a[i]=a[i-1]*2-a[i-3]*2+a[i-4];
	cout<<a[n];
	return 0;
}
```


---

## 作者：yf最qhhh (赞：1)

根据样例可以得到:

a[0]=0

a[1]=1

a[2]=2

a[3]=4

a[4]=6

所以规律为:

a[i]=2 * a[i-1]-2 * a[i-3] + a[i-4]

好了，所以代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int arr[1000000]={0,1,2,4,6};
main(void){
	int n;
	scanf("%lld",&n);
	for(int i=5;i<=n;i++){
		arr[i]=2*arr[i-1]-2*arr[i-3]+arr[i-4];
   	}
	printf("%lld",arr[n]);
   	return 0;
}

```
AC！

---

## 作者：Franka (赞：1)

### **题目**
和翻译一样。
### **思路**
找规律的题，规律如下：


$\quad\begin{cases}a[1]=1\\a[2]=2\\a[3]=4\\a[4]=6\\a[n]=a[n-1]×2-a[n-3]×2+a[n-4]\end{cases}$

### **代码**
```pascal
var
 n,i:longint;//定义n和i
 a:array[0..101] of longint;//定义a数组
begin
 readln(n);//读入n
 a[1]:=1;a[2]:=2;a[3]:=4;a[4]:=6;//初始值
 for i:=5 to n do a[i]:=a[i-1]*2-a[i-3]*2+a[i-4];//套公式
 writeln(a[n]);//为啥这里大家都用单判啊？
end.//华丽结束
```

---

## 作者：南橙未熟k (赞：1)

惊奇的发现这道题只有5篇题解
## ~~尽管pascal的人很多~~
作为一个只会pascal的蒟蒻，只能讲一下我的思路

### 看标签——入门（水题）
所以我们尝试找规律

根据样例，得到
### a[1]:=1;a[2]:=2;a[3]:=4;a[4]:=6;

然后玄玄的算法 推理得出
#  a[i]:=2*a[i-1]-2*a[i-3]+a[i-4];
就这样，题目就解决了

供上~~码风巨丑~~的代码
QAQ

```pascal
var a:array[1..105] of longint;
    i,n:longint;
begin
        readln(n);
        a[1]:=1;
        a[2]:=2;
        a[3]:=4;
        a[4]:=6;//上文已述
        for i:=5 to n do
                a[i]:=2*a[i-1]-2*a[i-3]+a[i-4];//递推
        writeln(a[n]);
end.
```

是不是很~~简单~~

最后~~不要脸的~~附上我的博客[内敛的龙猫](https://www.luogu.org/blog/chky2/#)


---

## 作者：BADFIVE (赞：0)

这道题很像那个斐波那契数列，也是先把前面几项先打表出来，再用公式就直接完事
```cpp
#include <bits/stdc++.h>
using namespace std;
int arr[1000001];
int main(){
    int n;
    cin>>n;
    arr[0]=0,arr[1]=1,arr[2]=2,arr[3]=4,arr[4]=6;//把前面几项列出来 
    for(int i=5;i<=100;i++){//一定要注意从5开始，因为前面4项都打表了 
        arr[i]=2*arr[i-1]-2*arr[i-3]+arr[i-4];//用公式直接算出 
    }
    cout<<arr[n]<<endl;
}
```


---

## 作者：daniEl_lElE (赞：0)

此题共有两种解法：

都是找规律QWQ

## 1.f(n)=2f(n-1)-2f(n-3)+f(n-4)。

这个规律列一列就知道了：
```
1 2 4 6 9 12 16 20 25 30 36
```

简单公式，直接套，前四项是1，2，4，6.

直接上代码：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f[105];
signed main(){
    int n;
    cin>>n;
    f[0]=0,f[1]=1,f[2]=2,f[3]=4,f[4]=6;
    for(int i=5;i<=100;i++){
        f[i]=2*f[i-1]-2*f[i-3]+f[i-4];
    }
    cout<<f[n]<<endl;
    return 0;
}
```
## 2.若n为奇数，f(n)=((n+1)/2)^2，若n为偶数，f(n)=n/2*(n/2+1)

这是一个更简单的公式。

也是通过把列出来的数字分开：
```
1 4 9 16 25 36
2 6 12 20 30
```
看出来没有？

上面是完全平方数。

下面是相邻两个数相乘

也是直接上代码：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int n;
    cin>>n;
    if(n%2==1){
    	cout<<((n+1)/2)*((n+1)/2);
    }
    else{
    	cout<<(n/2)*(n/2+1);
    }
    return 0;
}
```

---

## 作者：houpingze (赞：0)

此题很简单

通过打表，前4项分别是：

$$a[1]=1;$$


$$a[2]=2;$$

$$a[3]=4;$$

$$a[4]=6;$$


我们得出一个公式




 $$a[i]=2a[i-1]-2a[i-3]+a[i-4];$$

~~嗯，得出这个结论应该不会还做不出来了吧~~

## AC CODE：


```cpp
#include<iostream>
int n,cnt,m;
int a[1000000]{0,1,2,4,6};//打表
int main(){
	scanf("%d",&n);//输入
	for(int i=5;i<=n;i++){//循环算出数值
		a[i]=2*a[i-1]-2*a[i-3]+a[i-4];//套公式
   	}
	printf("%d",a[n]);//输出a[n]的值
   	return 0;//华丽的结束
}

```

~~暴力出奇迹，打表进省一~~


---

## 作者：人间凡人 (赞：0)

这道题是一道**找规律**题,不需要打表呀。

我们先列出前$10$项的值:$1\ \ 2\ \ 4\ \ 6\ \ 9\ \ 12\ \ 16\ \ 20\ \ 25\ \ 30$ 

我们可以发现:

$9=6*2-2*2+1$

$16=12*2-6*2+4$

$30=25*2-16*2+12$

因此我们可以总结出：$a[i]=a[i-1]*2-a[i-3]*2+a[i-4]$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105];
int main(){
    scanf("%d",&n);
    a[1]=1;a[2]=2;a[3]=4;a[4]=6;
    for(int i=5;i<=n;i++)
        a[i]=2*a[i-1]-2*a[i-3]+a[i-4];
    printf("%d\n",a[n]);
    return 0;
}
```


---

## 作者：Andysun06 (赞：0)

#  CF909B pascal题解
## 这一题只要一个公式就解决了：
    x[i]=2*x[i-1]-2*x[i-3]+x[i-4]
## 可是0到4要打表，不信你试试
### 我第一次是这样的：
    var a,b:longint;//b要循环，不能用int64和Qword。
     x:array[0..10000]of longint;
    begin
    x[0]:=0;//打表
    x[1]:=1;
    x[2]:=2;
    x[3]:=4;
    x[4]:=6;
    readln(a);//输入a
    if a<=4 then//如果<=4直接输出
     writeln(x[a])//输出
     else//否则
     begin
     if a<=100 then//如果<=100
       begin
        for b:=5 to 100 do//循环计算
         x[b]:=2*x[b-1]-2*x[b-3]+x[b-4];//公式
        writeln(x[a]);//输出
       end
       else//如果>100
        writeln('0');//直接输出0
     end;
     end.
### 后来看了｛伏轩彤666 ｝的题解（虽然我不学C++，可是看得懂）就简化了一下：
    var a,b:longint;//b要循环，不能用int64和Qword。
        x:array[0..10000]of longint;
    begin
     x[0]:=0;//打表
     x[1]:=1;
     x[2]:=2;
     x[3]:=4;
     x[4]:=6;
     readln(a);//输入
      for b:=5 to 100 do//循环计算(因为只会更改5到100所以不用判断<=4)
       x[b]:=2*x[b-1]-2*x[b-3]+x[b-4];//公式
      writeln(x[a]);//输出
     end.
### ~~看我写题解多认真，给我过吧。~~       







---

