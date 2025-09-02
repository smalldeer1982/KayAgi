# Memory and Crow

## 题目描述

There are $ n $ integers $ b_{1},b_{2},...,b_{n} $ written in a row. For all $ i $ from $ 1 $ to $ n $ , values $ a_{i} $ are defined by the crows performing the following procedure:

- The crow sets $ a_{i} $ initially $ 0 $ .
- The crow then adds $ b_{i} $ to $ a_{i} $ , subtracts $ b_{i+1} $ , adds the $ b_{i+2} $ number, and so on until the $ n $ 'th number. Thus, $ a_{i}=b_{i}-b_{i+1}+b_{i+2}-b_{i+3}... $ .

Memory gives you the values $ a_{1},a_{2},...,a_{n} $ , and he now wants you to find the initial numbers $ b_{1},b_{2},...,b_{n} $ written in the row? Can you do it?

## 说明/提示

In the first sample test, the crows report the numbers $ 6 $ , $ -4 $ , $ 8 $ , $ -2 $ , and $ 3 $ when he starts at indices $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ respectively. It is easy to check that the sequence $ 2 $ $ 4 $ $ 6 $ $ 1 $ $ 3 $ satisfies the reports. For example, $ 6=2-4+6-1+3 $ , and $ -4=4-6+1-3 $ .

In the second sample test, the sequence $ 1 $ , $ -3 $ , $ 4 $ , $ 11 $ , $ 6 $ satisfies the reports. For example, $ 5=11-6 $ and $ 6=6 $ .

## 样例 #1

### 输入

```
5
6 -4 8 -2 3
```

### 输出

```
2 4 6 1 3 
```

## 样例 #2

### 输入

```
5
3 -2 -1 5 6
```

### 输出

```
1 -3 4 11 6 
```

# 题解

## 作者：k3v1n070828 (赞：5)

这道题看上去像一个推理题，但如果在草稿纸上进行一些计算，就能发现此题是一道红题，计算过程如下：

### 我们从样例1来分析：


对比两个a数组的数

$6=b[1]-b[2]+b[3]-b[4]+b[5]$

$-4=b[2]-b[3]+b[4]-b[5]$

进行推导：$6=4×(-1)+b[1]$

这不就是个方程吗：很明显$b[1]=2$

接着用同样的方法推导$8×(-1)+b[2]=4$

$∴b[2]=4$

接着开始尝试找规律：$b[3]=6=8+(-2)$,$b[4]=1=(-2)+3$

归纳出：$b[i]=a[i]+a[i+1]$

**注意：$b[n]=a[n]$**

找出规律，然后就可以简简单单的AC了：

```cpp
#include<cstdio>//头文件
using namespace std;
int n,a[100010];//定义变量
int main(){
	scanf("%d",&n);//输入数组长度
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);//循环输入数组
	for(int i=1;i<=n;i++)
		printf("%d ",a[i]+a[i+1]);//用归纳出来的公式
	return 0;//结束程序
}
```

很多同学可能会奇怪我为什么没有判断$b[n]=a[n]$。

这里普及一下关于全局变量的一些特性：定义时全部默认赋值$0$，∴$a[n]+a[n+1]=a[n]+0=a[n]$，不用进行特判。

感谢阅读，Bye~

---

## 作者：_Felix (赞：2)

看代码
建议先找找规律，推推公式哦~
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
	int n;
	int k=0,x;//用k表示ai-1,用x表示ai ；
	cin>>n;//读入
	for(int i=1;i<=n;i++)
	{
		cin>>x;//读入
		if(i!=1)
			cout<<x+k<<" ";//根据题目给我们的公式，可以推出bi = ai + ai-1 ;
		k=x;//更新
	 } 
	 cout<<x<<endl;//就是输出n啦
	return 0；
 } 
 ```
   **By 你们最可爱的czy** 

---

## 作者：REAL_曼巴 (赞：1)

此题为纯模拟。先看样例，发现输出的数依次是其输入本项加下一项。

![](https://cdn.luogu.com.cn/upload/image_hosting/fxjhuxh1.png)

输入后用循环模拟方法即可。

```cpp
#include<iostream>
using namespace std;
int n,a[100010];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        cout<<a[i]+a[i+1]<<" ";
    return 0;
}

```


---

## 作者：lihanyang (赞：1)

## 其实答案很简单，直接a[i]+a[i+1]就是b[i]的答案
```cpp
#include<bits/stdc++.h>//万能头文件
#define ll long long  //ll定义long long（偷懒）
using namespace std;
int main()
{
	ios::sync_with_stdio(false);//cin加速
	ll a[1000005];//A数组存数字
	ll b[1000005];//B数组存答案
	ll t;
	cin>>t;
	for(ll i=1;i<=t;i++)
	{
		cin>>a[i]; 
	}
	for(ll i=t;i>=1;i--)
	{
		b[i]=a[i]+a[i+1];//B_i就是A_i加A_i+1
	}
	for(ll i=1;i<=t;i++)
	{
		cout<<b[i]<<" "; //输出答案
	}
}
```

---

## 作者：yf最qhhh (赞：0)

鸽了半年后的第一篇题解。。

------------
这是道找**规律**的题。

直接上样例。

输入：
```latex
5
6 -4 8 -2 3
```
输出：
```latex
2 4 6 1 3
```

经观察可得：

$a_1=b_1+b_2=6+(-4)=2$

$a_2=b_2+b_3=(-4)+8=4$

$a_3=b_3+b_4=8+(-2)=6$

$···$

$a_i=b_i+b_{i+1}$

另一个样例同理。

所以 $Code:$
```cpp
#include<iostream>
using namespace std;
const int N=1e5+5;
int b[N];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        cout<<b[i]+b[i+1]<<" ";//反正最后都要再从头输出一遍a数组，所以干脆直接在计算的时候输出了。
    }
    return 0;
}
```

感谢阅读！！

---

## 作者：YZ_hang (赞：0)

# 找规律呗

此题刚拿到手还蛮慌，但看起来不用什么算法

然后看了样例发现诶怎么好像有规律

**发现b[i]=a[i]+a[i+1]啊！**

当然这个巧合和题目本身也是脱不了关系的，因为题目中说了一个a[i]=……(但窝看不太懂)

但其实b[i]=a[i]+a[i+1]这个公式是可以从题目中的公式推出来的

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[1000001],n;//数组在main外时，自动赋值为0
int main(){
    scanf("%d",&n);//n是数列长度
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);//输入
    for(int i=1;i<=n;i++)
        printf("%d ",a[i]+a[i+1]);//不用再设变量，直接顺次输出该公式就行了
    puts("");//换行好习惯
    return 0;
}
```
但如果还有格式严格要求，末位不能有空格的话，要再来一行特殊处理

---

## 作者：人间凡人 (赞：0)

这题是一道经典的找规律题目，就让我们先从找第一个样例的规律开始。

输入:

$5$ 

$6$  $-4$  $8$  $-2$  $3$

输出:

$2$ $4$ $6$ $1$ $3$

不难发现:
```cpp
6+(-4)=2
(-4)+8=4
8+(-2)=6
(-2)+3=1
3+0=3
```
第二个样例亦是如此。

因此:解这道题的步骤是：

$1$、 将$a[n+1]$赋值为0。（可以省略）

$2$、 循环$i$从$1$ ~ $n$ 依次输出$a[i]+a[i+1]$即可。

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100005];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	a[n+1]=0;
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]+a[i+1]);
	}
	return 0;
}

```



---

## 作者：shenmadongdong (赞：0)

~~既然没有Pascal的题解，那本蒟蒻来水一发~~

这道题很水，只要输出这一项与后一项之和即可。

代码：
```
var n,i:longint;
    a:array [1..100000] of longint;
begin
  read(n);
  for i:=1 to n do read(a[i]);//读入
  for i:=1 to n do write(a[i]+a[i+1],' ');//计算
end.
```

---

## 作者：lhjy666 (赞：0)

## 就是大模拟
### 奉上代码 
```cpp 
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[1000005],b[1000005];
int main()
{
	ll n;
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for (ll i=n;i>=1;i--)
	{
		b[i]=a[i]+a[i+1];
	}
	for (ll i=1;i<=n;i++)
	{
		printf("%lld ",b[i]);
	}
	return 0;
}
```
~~真的没什么好解释的~~

---

