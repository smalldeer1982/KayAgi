# Perfect Squares

## 题目描述

Given an array $ a_{1},a_{2},...,a_{n} $ of $ n $ integers, find the largest number in the array that is not a perfect square.

A number $ x $ is said to be a perfect square if there exists an integer $ y $ such that $ x=y^{2} $ .

## 说明/提示

In the first sample case, $ 4 $ is a perfect square, so the largest number in the array that is not a perfect square is $ 2 $ .

## 样例 #1

### 输入

```
2
4 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
1 2 4 8 16 32 64 576
```

### 输出

```
32
```

# 题解

## 作者：rui_er (赞：6)

根据题意，我们要求序列中的最大的非完全平方数。

求最大，有两种思路：

1. sort从大到小
2. max函数取最大

这里采用第二种思路。

----------------------

>头文件部分：

```cpp
#include <iostream>
#include <limits.h>
#include <math.h>
using namespace std;
```

iostream，C++基础头文件。
limits.h，为了后面的```INT_MIN```。
math.h，为了开方。

>判断不是完全平方数

```cpp
if(int(sqrt(a))*int(sqrt(a)) != a)
```

原理：int自动向下取整，平方根的平方就是数本身。

>取最大

```cpp
MAX = INT_MIN;
//中间代码
MAX = max(MAX, a);
```

INT_MIN是limits.h里面存储int的下界的常量，见：```#define INT_MIN (-2147483647-1)```

max函数是取前后的最大值的函数。

>把以上部分整合，得到完整代码：

```cpp
#include <iostream>
#include <limits.h>
#include <math.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int a;
	int MAX = INT_MIN;
	for(int i=0;i<n;i++)
	{
		cin>>a;
		if(int(sqrt(a)) * int(sqrt(a)) != a)
			MAX = max(MAX, a);
	}
	cout<<MAX<<endl;
	return 0;
}
```

---

## 作者：zhuchenzhang (赞：3)

暴力出奇迹。。。

了解一个事实：负数不可能是完全平方数。~~假装不知道虚数。~~

所以遇到复数直接特判就行了。

题面说-$10^6$<=$a_i$<=$10^6$，所以直接枚举$1$~$10^3$，再判等。

最后再用一个变量记录最大值，记住变量一定要小！非完全平方数大部分是复数

放AC代码：（输出注释是我自己本地测试时用的。~~防抄袭~~）

```cpp
#include <bits/stdc++.h>//万能库，很方便
using namespace std;//启动命名空间，防止重名
struct number //开一个结构体，方便记录数据
{
    int num;//记录数字
    bool is_w;//记录是否是完全平方数
}a[100001];//定义数组，注意有分号
int n;//数字总量
inline void find(int x)//自定义判定函数x是a数组的编号
{
    a[x].is_w=false;//把a x中的标记变量赋值为假
    if(a[x].num<0){//小于0就返回，一定不是完全平方数
    	//cout<<"lllll\n";
        return;//void型，不加其他参数
    }
    if(a[x].num==0)//如果为0，特判
    {
    	//cout<<"OOOOO\n";
        a[x].is_w=true;//标记是完全平方数
        return;
    }
    for(int i=1;i<=1000;++i)//枚举1~1000
    {
        if(i>a[x].num&&i*i!=a[x].num){//如果i已经比a x 大，并且i的平方不是a x的数值，返回
        	//cout<<"BACK!\n";
        	return;
        }
        if(i*i==a[x].num)//找打i的平方是a x的数值
        {
        	//cout<<i<<endl;
            a[x].is_w=true;//标记是完全平方数
            return;//返回
        }
    }
    //cout<<"_-_-_\n";
    return;//没找到，返回
}
int main()
{
    scanf("%d",&n);//c式读入，注意&符号取用地址
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i].num)/*,cout<<a[i].num<<' '*/;//循环读入数字
    //puts("");
    for(int i=1;i<=n;++i)
        /*cout<<"GO!\n",*/find(i);//判定每一个数
    int maxn=-112233445566;//注意赋一个很小的值，不爆int
    //puts("");
    //for(int i=1;i<=n;++i)
    //	cout<<a[i].is_w<<' ';
    //puts("");
    for(int i=1;i<=n;++i)
        if(!a[i].is_w)//不是完全平方数
            maxn=max(maxn,a[i].num);//找最大值
    printf("%d",maxn);//C式输出
    return 0;//养成好习惯，从我做起
}//主程序愉快地结束了OVO！
```

感谢大佬批评指正。

$\color{red}\texttt{洛谷万岁！}$

---

## 作者：Register (赞：2)

经过我的压行，这大概够短了，我也不是故意压的，这是我的码风

	言归正传：只要两个转化为int类型的sqrt()乘起来
    和原本的数一样
    那就是完全平方数（至少本题是这样的）
奉上代码：
```cpp
#include <iostream>
#include <algorithm>//sort库
#include <cmath>//sqrt()库
using namespace std;
int main(){
    int a[1001],n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);//从小到大sort
    n++;
    while(--n)
        if(int(sqrt(a[n]))*int(sqrt(a[n]))!=a[n]) {cout<<a[n]<<endl;return 0;}//强制转换和调用sqrt()
    return 0;
}
```

---

## 作者：OdtreePrince (赞：2)

# -模拟-

我在想，标签中的排序并没啥卵用啊！边读入边判断，边更新答案，不是很简单嘛。

判断分两类，负数直接取较大值；自然数先判断是否为平方数，再取最大值。由于蒟蒻太懒，因此不想做预处理，直接用土方法来判断平方数。

~~~
#include<bits/stdc++.h>
using namespace std;
int n,a,ans=-214748364;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        if(a<0){
            ans=max(ans,a);
        }
        else{
            int p=sqrt(a);
            if(p*p!=a) ans=max(ans,a);
        }
    }
    cout<<ans;
    return 0;
}
~~~

---

## 作者：Sugar0612 (赞：1)

#### 先看题目。
给定一组有n个整数的数组a[1],a[2],…,a[n].找出这组数中的最大非完全平方数。 完全平方数是指有这样的一个数x,存在整数y,使得x=y^2。\
~~一看就知道是一道水题~~~~~~   
###### 首先，要把数从大到小排列。
###### 这就想到优先队列了~
什么是优先队列呢？\
注意队列头文件：
```cpp
#include <queue>
```
它是stl(标准模板库)中的，故要加:
```cpp
using namespace std;
```
优先队列的定义：\
普通的队列是一种先进先出的数据结构，元素在队列尾追加，而从队列头删除。
在优先队列中，元素被赋予优先级。当访问元素时，具有最高优先级的元素最先删除。优先队列具有最高级先出 （first in, largest out）的行为特征。通常采用堆数据结构来实现。\
通常以从大到小排列！\
这就简单了：
```cpp
#include <bits/stdc++.h>//cmath
const int N=1001;
using namespace std;
bool ggg(int x)
{
	if(x<0)
		return false;
	else
	{
		int l=sqrt(x);
		if (l*l==x)
			return true;
		else
			return false;
	}
}
int main()
{
	priority_queue<int> pq；//用中文冒号，防抄题
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		int b;
		cin>>b;
		pq.push(b);
	}
	for (;;)
	{
		if (ggg(pq.top())==true)
			pq.pop();
		else
		{
			cout<<pq.top()<<endl;
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：Randyhoads (赞：1)

这道题大意如下：

给定一组有n个整数的数组a1,a2,…,an.找出这组数中的最大非完全平方数。

完全平方数是指有这样的一个数x,存在整数y,使得x=y^2y 。


那显然一个数如果不是完全平方数，则

```cpp
int h=sqrt(a);
if(a!=h*h)
{
    //a不是完全平方数
}
```
注意一下负数

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;

int a;

int maxs=-1000000;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        if(a>=0)
        {
        int hh = sqrt(a); 
        if(hh*hh!=a)
        {
            maxs=max(maxs,a);
        }
        }
    else
    {
        maxs=max(maxs,a);
    }
    }
    cout<<maxs<<endl; 
} 
```

---

## 作者：我是蒟弱 (赞：0)

### 没人发优先队列题解啊！我来水一发

本题：

> 输入，排大小（优先队列自动解决~愉快QʌQ~）

> 从大到小循环是不是完全平方数

代码【$C++$】：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
priority_queue <int> a;//优先队列
bool perfect_square(int x){//判断是否为完全平方数
	return (int(sqrt(x))*int(sqrt(x))==x)?true:false;//三目运算符判断
}
int main(){
	int n,x;
	scanf("%d",&n);//输入个数
	for(register int i=1;i<=n;i++){
		scanf("%d",&x);//输入那个数
		a.push(x);//推入优先队列
        //队列自动排序（从大到小）
	}
	while(!a.empty()){//队列不为空
		if(!perfect_square(a.top())){//好了，不是完全平方数
			printf("%d",a.top());//输出
			return 0;//结束
		}
		a.pop();//那这个就是完全平方数，弹出
	}
    //不必再return 0，因为一定会找到。
}

```

---

## 作者：empty (赞：0)

我的是否完全平方数的判定方法看来独树一帜       
具体看代码吧
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int n,nsqrt=-2147000000;
int main()
{
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  int x;
  cin>>x;
  if(x>=0) if(sqrt(x) != int(sqrt(x)))/*重点，如果x不是完全平方数，so~sqrt（x）将会是一个浮点类型的数据，自然不会和强制转化后的sqrt（x）相等，那么条件成立*/ nsqrt=max(nsqrt,x);
  if(x<0) nsqrt=max(nsqrt,x);
 }
 cout<<nsqrt;
 return 0;
}
```

---

