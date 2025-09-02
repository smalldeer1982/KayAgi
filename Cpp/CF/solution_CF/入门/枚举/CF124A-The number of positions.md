# The number of positions

## 题目描述

Translated by @隐鬼在侧

## 样例 #1

### 输入

```
3 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2 3
```

### 输出

```
3
```

# 题解

## 作者：FLASH_CM (赞：7)

### 【算法思路】
简单分析可得：

1、这个人的前面不能少于a个人，那么他可以站在 a+1 至 n ，共计 n-a 个位置。

2、这个人的后面不能多于b个人，那么他可以站在 n-b 至 n ，共计 b+1 个位置。

所以我们直接输出两种情况中较小的那个即可。
### 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	long long n,a,b;
	scanf("%lld%lld%lld",&n,&a,&b);
	printf("%lld",min(n-a,b+1));
	return 0;
}
```
### 【问题拓展】
很多人可能会说直接 for 循环跑一遍枚举也能过，但如果数据很大呢？有需要的同学请移步 [数据加强版试题](https://www.luogu.org/recordnew/show/9296201)

---

## 作者：Pkixzx (赞：1)

这题给我的第一感觉就是直接比较（~~事实证明第一感没错~~

首先我画了个图（图为例1解释

![](https://cdn.luogu.com.cn/upload/image_hosting/3k2kq1ix.png)

前面不少于1个人，可得前面的人可以为以下几个位子：

![](https://cdn.luogu.com.cn/upload/image_hosting/i34w27vz.png)

所以这个人可以站第2个和第3个位子。

后面最多1人，可得后面的人可以为下几个位子：

![](https://cdn.luogu.com.cn/upload/image_hosting/cjh9emz6.png)

所以这个人可以站第2个和第3个位子。

不难发现，最终答案是n-a和b+1中的最小值。

用这个公式带入例2，结果也正确。

代码如下：
```
#include <bits/stdc++.h>
using namespace std; 
int main() 
{
    long long n,m,i,j,k,x,y,t=0;
    cin>>n>>x>>y;
    cout<<min((n-x),(y+1));//统计哪个小
    return 0;
}
```




---

## 作者：W_churchill (赞：1)

### Solutions to problem——1：
> 0<a,b<n<=100


#### 数据只有0-100!
我二话不说就上模拟算法，我们只要模拟这个队列即可。  
只要i元素前面有不少于a个人，后面有不多于b个人，那么计数器就加一。     
#### 上代码！！！
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,b,sum=0;//定义变量，sum为计数器
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
		if((i-1)>=a&&(n-i)<=b) sum++;//i从一开始，i就为它在队列中的位置。只要它i-1大于等于a并且从i到队列尾小于等于b的话，就是一种方案。
	cout<<sum<<endl;//输出
	return 0;
} 
```
十分简单的模拟。。。。
### Solutions to problem——2：
其实我们稍一分析即可发现——  
条件一：前面不少于a人，即有n-a个位置。  
条件二：后面不多于b人，即最多有b+1个位置了。  
以样例为说明：  
n=5 a=2   b=3   
1 2 3 4 5,     
先减去a人，发现符合条件一的只有3人。再用b+1为4人，有4人符合条件二。3<4，故为3人。再对照一下样例输出，3=3，正确！
![](https://cdn.luogu.com.cn/upload/image_hosting/saecppp4.png)
#### 上代码！！！
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,b;
	cin>>n>>a>>b;
	int sum=n-a;//先判断满足条件二的
	if(sum>(b+1)) cout<<b+1<<endl;//把满足条件一和满足条件二的人数相比较，取较小的。
	else cout<<sum;
 	return 0;
}
```
#### 最后，告诉大家：  
![](https://cdn.luogu.com.cn/upload/image_hosting/52oi1tsr.png)
## 宇宙很大，但生活更大，我们一定会再次相见的！！！


---

## 作者：sxtm12138 (赞：1)

设所在位置为k，则前面有(k-1)人，后面有(n-k)人，且k在1~n之间。

    解不等式：k-1>=a;        n-k<=b;       1<=k<=n;
    解:      k>=a+1;         k>=n-b;       1<=k<=n;
   将以上三式合并，得max(a+1,n-b)<=k<=n;
   
   故方案数有(n-max(a+1,n-b)+1)种。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int a,n,b;//定义变量
int main()
{cin>>n>>a>>b;//读入
 cout<<n-max(a+1,n-b)+1;//套公式，别忘了加1
 return 0;
}

```

---

## 作者：_Qer (赞：1)

这题可以当做数学题来做，但数据范围完全可以暴力过。

暴力的就不说了，枚举每个位置，满足条件答案+1

这里主要讲讲找规律的做法，可以适应很大的数据

------------

分析一下题目：

**前面有不少于$a$个人，后面有不多于$b$个人**

假设第$i$个位置坐标为$i$

根据前半句我们可以知道，可能的坐标 $i>=a$，也就是说可能的位置是队伍的后$n - a$个

再看后半句，可以看出可能的坐标 $i>=b$，在队伍的后$b+1$个位置

可以看做是一个不等式

$\{^{i>=a}_{i>=b}$

解得

$i>=min(a, b)$

也就是有$min(n-a,b+1)$个解

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a, b;
int main() {
    cin >> n >> a >> b;
    cout << min(n - a, b + 1) << endl;
    return 0;
}
```

---

## 作者：DreamShadow (赞：1)

    emming……
    这个题目…… 
    【敲黑板】
    首先，我们可以定义一个min函数用来找n-1和b+1里面的较小数 
    问：（如果一样怎么办？）
    答：（开心就好）
    


------------

    我觉得为了你能看懂我的代码，先瞧瞧这个
    math库：
    Program Ex_Math; 
```
Uses Math; 
Begin 
Writeln(hypot(3,4)); 
End. 
函数介绍： 
? hypot 
原型：function hypot(x:float;y:float):float 
功能：返回直角三角形中较长边的长度，也就是sqrt(sqr(x)+sqr(y)) 
? ceil 
原型：function ceil(x:float):Integer 
功能：返回比参数大的最小整数 
引发错误：在x超出Integer的范围时会引发溢出错误 
? floor 
原型：function floor(x:float):Integer 
功能：返回参数小的最大整数 
引发错误：在x超出Integer的范围时会引发溢出错误 
? power 
原型：function power(base:float;exponent:float):float 
功能：返回base的exponent次方 
引发错误：在base为负数且exponent为小数时 
? intpower 
原型：function intpower(base:float;const exponent:Integer):float 
功能：返回base的exponent次方 
? ldexp 
原型：function ldexp(x:float;const p:Integer):float 
功能：返回2的p次方乘以x 
? log10 
原型：function log10(x:float):float 
功能：返回x的常用对数 
? log2 
原型：function log2(x:float):float 
功能：返回x以2为底的对数 
? logn 
原型：function logn(n:float;x:float):float 
功能：返回x以n为底的对数 
? Max 
原型：function Max(a:Integer;b:Integer):Integer 
function Max(a:Int64;b:Int64):Int64 
function Max(a:Extended;b:Extended):Extended 
功能：返回a与b中较大的一个 
? Min 
原型：function Min(a:Integer;b:Integer):Integer 
function Min(a:Int64;b:Int64):Int64 
function Min(a:Extended;b:Extended):Extended 
功能：返回a与b中较小的一个 
? arcsin 
原型：function arcsin(x:float):float 
功能：返回x的反正弦值，返回的是弧度指单位 
? arccos 
原型：function arccos(x:float):float 
功能：返回x的反余弦值，返回的是弧度指单位 
? tan 
原型：function tan(x:float):float 
功能：返回x的正切值，x以弧度为单位 
? cotan 
原型：function cotan(x:float):float 
功能：返回x的余切值，x以弧度为单位 
? arcsinh 
原型：function arcsinh(x:float):float 
功能：返回双曲线的反正弦 
? arccosh 
原型：function arccosh(x:float):float 
功能：返回双曲线的反余弦 
? arctanh 
原型：function arctanh(x:float):float 
功能：返回双曲线的反正切 
? sinh 
原型：function sinh(x:float):float 
功能：返回双曲线的正弦 
? cosh 
原型：function sinh(x:float):float 
功能：返回双曲线的正弦 
? tanh 
原型：function sinh(x:float):float 
功能：返回双曲线的正切 
? cycletorad 
原型：function cycletorad(cycle:float):float 
功能：返回圆的份数转换成弧度之后的值 
? degtorad 
原型：function degtorad(deg:float):float 
功能：返回角度转换成弧度之后的值 
? radtocycle 
原型：function radtocycle(rad:float):float 
功能：返回弧度转换成圆的份数之后的值 
? radtodeg 
原型：function radtodeg(rad:float):float 
功能：返回弧度转换成角度之后的值 
? MaxValue 
原型：function maxvalue(const data:Array[] of float):float 
function maxvalue(const data:Array[] of Integer):Integer 
function maxvalue(const data:PFloat;const N:Integer):float 
function maxvalue(const data:PInteger;const N:Integer):Integer 
功能：返回数组中的最大值 
? MinValue 
原型：function minvalue(const data:Array[] of float):float 
function minvalue(const data:Array[] of Integer):Integer 
function minvalue(const data:PFloat;const N:Integer):float 
function MinValue(const Data:PInteger;const N:Integer):Integer 
功能：返回数组中的最小值 
? sum 
原型：function sum(const data:Array[] of float):float 
function sum(const data:PFloat;const N:LongInt):float 
功能：求数组中所有数之和 
? sumsandsquares 
原型：procedure sumsandsquares(const data:Array[] of float;var sum:float; 
var sumofsquares:float) 
procedure sumsandsquares(const data:PFloat;const N:Integer; 
var sum:float;var sumofsquares:float) 
功能：将数组中的数求和放入num中，求平方和放入sumofsquares中 
? ** 
原型：function operator **(float,float):float(bas:float;expo:float):float 
function operator **(Int64,Int64):Int64(bas:Int64;expo:Int64):Int64 
功能：同等于Power，这是乘方的操作符 
```  


------------

#### 切记，别问我两个一样怎么办
#### 算了我心软了，告诉你吧：
```pascal
uses math; //别告诉我你还是看不懂╮(￣▽￣")╭捏把汗
var
  n,a,b,i,s:longint;
 begin
   readln(n,a,b);//输入
   writeln(min(n-a,b+1));//比大小
 end.

```

---

## 作者：FR_qwq (赞：0)

### 暴力出奇迹

没错，就是暴力。我们从 1 到 $n$ 开始枚举每个人的前面是否不少于 $a$ 个，后面是否不多于 $b$ 个（反正也就 100，不珂能 $\texttt{TLE}$），如果符合要求，那么它就是我们要找的那些人里面的一个，累加器 +1，最后输出结果，$\color{green}\texttt{AC}$。

$\text{CODE}$：
```pascal
var n,a,b,i,sum:longint;//定义
begin
readln(n,a,b);//读入
for i:=1 to n do//开始暴力枚举
  if(i-1>=a)and(n-i<=b)then//判断那个人前面是否不少于 a 个，后面是否不多于 b 个
    inc(sum);//如果条件正确，累加器 +1
writeln(sum);//输出
end.//完美结束
```

$\texttt{C}$ 党看这：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>//头文件
using namespace std;
int i,n,sum,a,b;//定义，也可以定在主函数里（
int main(){
	scanf("%d%d%d",&n,&a,&b);//读入，这里等同于 cin>>n>>a>>b
	for(i=1;i<=n;i++)//开始暴力枚举
		if(i-1>=a&&n-i<=b)//判断那个人前面是否不少于 a 个，后面是否不多于 b 个
			sum++;//如果是，累加器 +1
	printf("%d\n",sum);//输出，这里等同于 cout<<sum<<endl
	return 0;//完美结束
}
```

---

## 作者：GossWandering (赞：0)

为什么题解区没有人选择$dp/$递推呢？

$dp:$

设 $f(i)$ 表示前 $i$ 个座位满足条件的有多少个。

递推方程：

$f(i)=\begin{cases}f(i-1)+1&i\text{满足条件}\\f(i-1)&Otherwise\end{cases}$ 

初值：$f(0)=0$

最终答案：$f(n)$

复杂度：时空复杂度均是 $O(n)$

---

## 作者：pascalfans (赞：0)

**他前面不少于a个人，后面不多于b个人**这句话是重点，要记牢！[敲黑板]

**(0<=a,b,n<=100)**这说明数据不大，~~所以能用**模拟**~~

模拟部分：
```pascal
for i:=1 to n do //循环(来自某人：废话。)
 if (i>=a)__(i<=n-b) then inc(s);//横线上自己补全，看你理解了没(抄不了了吧)
```
其他部分请自己解决。。。(作者：呵呵)

---

