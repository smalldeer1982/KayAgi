# [ABC079B] Lucas Number

## 题目描述

给你一个数列 $L$，规定：

$L_0=2$

$L_1=1$

而第 $i$ 个数是：$L_i=L_{i-1}+L_{i-2}$。

现在给出一个正整数 $n$，求这个数组的第 $n$ 项。

## 说明/提示

$1 \leq n \leq 86$，$L_n$ 保证小于 $10^{18}$。

**【样例解释】**

$L_0=2$

$L_1=1$

$L_2=L_0+L_1=3$

$L_3=L_1+L_2=4$

$L_4=L_2+L_3=7$

$L_5=L_3+L_4=11$

## 样例 #1

### 输入

```
5```

### 输出

```
11```

## 样例 #2

### 输入

```
86```

### 输出

```
939587134549734843```

# 题解

## 作者：ShineEternal (赞：7)

# 灌水区：
1、蒟蒻刚刚才知道递推，大佬勿喷。

~~2、然而我不确定我的代码是不是递推。~~

3、求路赞。

4、管理大大求过。


------------

# 算法区：

递归和递推都可以用，但递归遇到大数据就挂了，所以要用递推。递推中因为只涉及到当前、当前-1和当前-2三个状态，所以说用a b c三个变量即可。

###  初始状态：a=2,b=1;

因为第0项和第1项都已经算了，所以从2循环到n。

## 技巧分区：

1、如果问你第0，1项，可以直接输出结果然后跳出程序。

2、a b c循环利用时，赋值的顺序要注意。要不然会改变本意。

3、long long 的范围是19位，题目所述是10^18，所以开long long。

#### 4、输出末尾一定要换行！！！

------------

# 代码区
```
#include<cstdio>
using namespace std;
int n;
long long a,b,c;
int main()
{
    scanf("%d",&n);
    a=2;
    b=1;
    if(n==1)
    {
    	printf("1\n");
    	return 0;
    }
    if(n==0)
    {
    	printf("2\n");
    	return 0;
    }//两个特判
    for(int i=2;i<=n;i++)
    {
    	c=a+b;
    	a=b;
    	b=c;//此处顺序多加注意
    	
    }//核心部分
    printf("%lld\n",c);//别忘换行
    return 0;
}
```


---

## 作者：yuzhechuan (赞：4)

这不就是斐波那契吗？


------------


```cpp
#include<bits/stdc++.h>//万能库
using namespace std;
int n;
long long f[87];//开longlong，防爆
int main()
{
	cin>>n;
	f[0]=2;//初始化
	f[1]=1;
	for(int i=2;i<=n;i++)
		f[i]=f[i-1]+f[i-2];//套用公式
	cout<<f[n];//输出第n个
}

```

---

## 作者：Soyilieber (赞：2)

盗版斐波那契

l0=2

l1=1

l2=l0+l1=2+1=3

……

l[i]=l[i-1]+l[i-2]

以下为pascal代码：
```pascal
var
    i,n:longint;
    l:array[0..86]of int64;
begin
    readln(n);
    l[0]:=2;
    l[1]:=1;
    for i:=2 to n do l[i]:=l[i-1]+l[i-2];//循环
    writeln(l[n]);
end.
```

---

