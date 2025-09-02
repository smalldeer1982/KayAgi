# Accounting

## 题目描述

A long time ago in some far country lived king Copa. After the recent king's reform, he got so large powers that started to keep the books by himself.

The total income $ A $ of his kingdom during $ 0 $ -th year is known, as well as the total income $ B $ during $ n $ -th year (these numbers can be negative — it means that there was a loss in the correspondent year).

King wants to show financial stability. To do this, he needs to find common coefficient $ X $ — the coefficient of income growth during one year. This coefficient should satisfy the equation:

 $ A·X^{n}=B. $ Surely, the king is not going to do this job by himself, and demands you to find such number $ X $ .

It is necessary to point out that the fractional numbers are not used in kingdom's economy. That's why all input numbers as well as coefficient $ X $ must be integers. The number $ X $ may be zero or negative.

## 样例 #1

### 输入

```
2 18 2
```

### 输出

```
3```

## 样例 #2

### 输入

```
-1 8 3
```

### 输出

```
-2```

## 样例 #3

### 输入

```
0 0 10
```

### 输出

```
5```

## 样例 #4

### 输入

```
1 16 5
```

### 输出

```
No solution```

# 题解

## 作者：Alex_Wei (赞：7)

注意到 $b$ 的范围很小，$abs(b)\leq10^3$

又因为

$$a*x^{n}=b$$

且 $x$ 为整数

所以 $x$ 满足

$$-abs(b)\leq abs(b)$$

枚举即可

注意用 $double$ ~~用不用无所谓~~

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c,n; 
int main()
{
	cin>>a>>b>>n;
	for(double i=-abs(b);i<=abs(b);i++)//枚举
		if(a*pow(i,n)==b)cout<<i,exit(0);//找到解就退出
	cout<<"No solution";
	return 0;
}
```


---

## 作者：lxgw (赞：2)

## [传送门](https://www.luogu.com.cn/problem/CF30A)
## 题意
求出满足 $a \times x^n=b$ 的 任一 x 值，如果没有，输出```No solution```。
## 思路
因为题目要求满足 $a \times x^n=b$ 的 x 值，加上 $|a|,|b|<=1000$ ，所以只用在 -1000~1000 之间爆搜一遍，如果有满足的 x  就输出就好了。

- ```abs()``` 取绝对值
- ```pow(a,b)``` 求出$a^b$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,n; 
int main()
{
	cin>>a>>b>>n;//输入
	for(int i=-1000;i<=1000;i++)//从-1000开始爆搜
		if(a*pow(i,n)==b)//如果满足a*i^n=b
		{
			cout<<i;return 0;//就直接输出
		}
	puts("No solution");//如果没有满足条件的就输出No solution
	return 0;
}
```

完结撒花~

谢谢 qwq

---

## 作者：qzhwmjb (赞：2)

### 思路
本题不是很难，把可能的 $x$ 的值判断一下即可，但坑很多：  
1. $A$,$B$ 的绝对值。需要使用 $abs$。
2. 有多个解则输出任意一个。这里就要注意样例的问题了，有可能是有多种答案，具体是否真确就要自行验算了。  

做题过程中使用到的两个函数，$abs$ 及 $pow$。   
$abs(x)$:求绝对值函数，注意 $abs$ 是针对于 $int$ 类型的。  
$pow(x,y)$:求 $x$ 的 $y$ 次方的值。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n,i;
int main() {
	cin>>a>>b>>n;
	for(i=-abs(b);i<=abs(b);i++){
		if(a*pow(i,n)==b){
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<"No solution"<<endl;
	return 0;
}
//请使用C++17
```


---

## 作者：tryrtj (赞：1)

这道题我提交了9次QAQ，原因就是0这个地方坑太多

代码只需要从-abs(b)到abs(b)枚举，求解析式结果，然后判断输出，（刚开始以为是1000^10，差点当成高精度）；

**这里是高能区**：

1. 当a=0，b=0时,x可取任意值，因为0乘以任何数都为0；

2. 当a=0，b≠0时，x无解，原因同上；

3. 当a≠0，b=0时，x只能取0，因为只有0的n次方（n≠0）才为0。

然后代码就很容易了

```
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	int a,b,n;
	cin>>a>>b>>n;
	if(a==0&&b==0){//第一种（此处省略第二种，因为通过枚举可以排除这种情况）
		cout<<1;
		return 0;
	}
	if(a!=0&&b==0){//第三种
		cout<<0;
		return 0;
	}
	for(int i=-abs(b);i<=abs(b);i++){
		if(i!=0){//记得加上i≠0，不信的话试试1 1 1这组数据
		int r=1;//初始为1，也是上面要求≠0的原因
		for(int j=0;j<n;j++){
			r*=i;//求积
		}
		if(r*a==b){//判断
			cout<<i<<endl;
			return 0;//直接结束
		}
		}
	}
	cout<<"No solution"<<endl;//输出否定
	return 0;
}
```

---

## 作者：orange166 (赞：0)

## 题面：  
[传送门](https://www.luogu.com.cn/problem/CF30A)  
## 思路：  
注意到 $a,b$ 的范围很小（$|a|,|b|≤1000$），我们可以直接爆搜 $x$ 的值。另外可以用 $pow$ 函数避免双重循环。  
注意有几个坑点：  
  1. 因为是 $a,b$ 的绝对值小于等于 $1000$ ，所以要用 $abs$。
  2. 要从  $-abs(b)$ 搜起
  3. 多个解输出一个即可  
## 代码（python 3）：  
```python
import math   #头文件
import sys
a,b,c=input().split(' ')  #空格分开输入
a=int(a); b=int(b); c=int(c)  #转换成整型
for i in range( -abs(b), abs(b)+1):  #爆搜
    if a*pow(i, c)==b:  #用pow函数判断
        print(i,end='')
        sys.exit(0)  #找到解就结束运行
print("No solution",end='')  #有解的话已结束运行

```  

[AC](https://www.luogu.com.cn/record/40271387)
  

---

## 作者：long_long (赞：0)

# 题目大意：

给定三个整数A,B,n，试求满足A*X^n=B的X值（若无解则输出“No solution"，有多个解则输出任意一个）

A,B的绝对值不超过1000，1<=n<=10

# 思路：

n的范围很小，可以枚举答案。需要从-abs(b)到abs(b)。

还有两个特判：

1。A=0，B=0,因为0*任何数=0。

2. A!=0,b=0，不成立，0^n=0。

这样就很简单了，我们康康代码。

# 代码：

```
#include<cstdio>
#include<cmath>
int main(){
    int a,b,n;
    scanf("%d%d%d",&a,&b,&n);
    if(a==0&&b==0){ printf("1\n");return 0;}
    if(a!=0&&b==0){ printf("0\n");return 0;}
    for(int i=-abs(b);i<=abs(b);i++) if(a*pow(i,n)==b){ printf("%d\n",i);return 0;}
    printf("No solution\n");
    return 0;
}
```




---

