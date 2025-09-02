# Drinks

## 题目描述

Little Vasya loves orange juice very much. That's why any food and drink in his kitchen necessarily contains orange juice. There are $ n $ drinks in his fridge, the volume fraction of orange juice in the $ i $ -th drink equals $ p_{i} $ percent.

One day Vasya decided to make himself an orange cocktail. He took equal proportions of each of the $ n $ drinks and mixed them. Then he wondered, how much orange juice the cocktail has.

Find the volume fraction of orange juice in the final drink.

## 说明/提示

Note to the first sample: let's assume that Vasya takes $ x $ milliliters of each drink from the fridge. Then the volume of pure juice in the cocktail will equal ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF200B/7c2a6a8bbcdbfef1f9a32c2eb1f7549c3c17c619.png) milliliters. The total cocktail's volume equals $ 3·x $ milliliters, so the volume fraction of the juice in the cocktail equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF200B/cc3d21395b67607dff0b7baa3b0b870221e3352d.png), that is, $ 66.(6) $ percent.

## 样例 #1

### 输入

```
3
50 50 100
```

### 输出

```
66.666666666667
```

## 样例 #2

### 输入

```
4
0 25 50 75
```

### 输出

```
37.500000000000
```

# 题解

## 作者：RBI_GL (赞：3)

~~这题真的水。~~

**思路：**

读入数据后计算总和，再求出平均数输出（其实就是求平均数的过程）

唯一坑点就是要多保留几位小数，且要用double或float。

Code：
-
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[105];
int ans=0; 
int main()
{
    cin>>n; //输入n
    
    for(int i=1;i<=n;i++) {
    	cin>>a[i]; //输入数据
    }
    
    for (int i=1;i<=n;i++) {
    	ans+=a[i]; //计和 
    }
    
    cout<<fixed<<setprecision(10)<<(double)ans/n;  //输出,多保留几位小数，类型用double 
    return 0;
}
```


---

## 作者：codemap (赞：2)

~~话说这种难度也是橙题？~~

只需要算一下几个数的平均数就可以了

## 和楼上不同,这里重点介绍一种c++的控制小数点后位数的函数：

# setprecision！！！

~~终于不需要用printf了！！！~~

## 用法：

```c
cout<<fixed<<setprecision(x)<<y;表示输出y的小数点后x//注意,y必须是double类型


```
## 注意需要加头文件
```c
#include<iomanip>
```
## 例如：cout<<fixed<<setprecision(5)<<1.0;

## 输出：0.10000

最后上代码
```
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
    int n,t,i,s=0;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>t;
        s+=t;//计算和
    }
    cout<<fixed<<setprecision(12)<<1.0*s/n;//样例保存了12位小数
    return 0;
}
```
# 不要抄袭

---

## 作者：TRZ_2007 (赞：1)

### 题解 [CF200B 【Drinks】](https://www.luogu.com.cn/problem/CF200B)  
# Solution  
这题需要一点求和的知识，我们在求和中有这么一个约定：  
$$\sum\limits_{i=0}^nV.p_i=V.\sum\limits_{i=0}^np_i$$  
证明：  
$\sum\limits_{i=0}^nV.p_i=V.p_1+V.p_2+\dots+V.p_n=V.\sum\limits_{i=0}^np_i(p_1+p_2+\dots+p_n)=V.\sum\limits_{i=0}^np_i$  
证毕。  
现在我们来计算混合的浓度，它等于溶质除以溶液，所以可得：  
$$P=\dfrac{\sum\limits_{i=1}^nV.p_i}{Vn}=\dfrac{V.\sum\limits_{i=1}^np_i}{Vn}=\dfrac{\sum\limits_{i=1}^np_i}{n}$$  
惊不惊喜意不意外？其实这道题目就是让你**求平均数**！！  
现在应该可以写代码了吧……  

# Code  
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

int n,x;
double cnt;

int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%d",&x);
		cnt = cnt + x * 1.0;
	}
	printf("%.5lf",cnt / n);//这个你保留超过4位小数就可以了
	return 0;
}
```

---

## 作者：rfsfreffr (赞：1)

~~AT水题刷完了来刷CF的~~

# 题意：求这n个数的平均数，保留4位小数

**平均数公式:所有数之和/数的个数**

即:

$Ave=\frac{\sum_{i=1}^{n}A_i}{n}$

$A_i$为数列中的第i项，$n$为数列的长度

由于只要4位，用double就够了

空间复杂度$O(1)$

时间复杂度$O(n)$

# 代码:
~~~
#include<bits/stdc++.h>
#define for_int register int//懒得打register
#define endl '\n'
#define ll long long
#define ld long double
using namespace std;
int n,x;
double sum;
int main(){
	cin>>n;
	for(for_int i=1; i<=n; i++){
		cin>>x;
		sum+=x; //累加
	}
	printf("%0.4lf\n",sum/n);//保留4位输出
	return 0;
}
~~~

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 杯饮料，第 $i$ 杯饮料中橙汁占 $a_i\%$。现在请求出这 $n$ 杯饮料混合成一杯饮料后的橙汁所占百分比。

**数据范围：$1\leqslant n\leqslant100,0\leqslant a_i\leqslant100$。**
## Solution
我们设每杯饮料的体积为 $x$，那么橙汁的总体积就是 $\sum\limits_{i=1}^n\dfrac{a_ix}{100}$，然后又因为饮料的总体积为 $nx$。所以，混合后橙汁所占的百分比为 $\dfrac{\sum\limits_{i=1}^n\dfrac{a_ix}{100}}{nx}=\dfrac{\sum\limits_{i=1}^n\dfrac{a_i}{100}}{n}$。

所以，先算出橙汁所占百分比的总和，然后除以 $n$ 就是我们想要的答案了。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, a[100007], s;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)	{
		scanf("%d", &a[i]);
		s += a[i];
	}
	printf("%.10lf", s * 1.0 / n);
}
```

---

## 作者：hensier (赞：0)

由于每一杯橙汁含量相同，所以我们不妨设其为$V$。则$n$杯的总含量为$nV$。对于每一个百分比$p_i$，总的橙汁量为：

$$V·p_1+V·p_2+...+V·p_n=V·\sum_{i=1}^np_i$$

那么橙汁的纯度（百分比）则为：

$$\frac{V·\sum_{i=1}^np_i}{nV}$$

所以最后答案在消去$V$后化简下来就是：

$$\frac{\sum_{i=1}^np_i}{n}$$

也就是说，我们只需要计算$p$数组的各个元素之和即可，最后除以数量得到答案，注意控制小数位数。

$C/CPP$：

```cpp
#include<stdio.h>
int n,x,sum,tot;
int main()
{
    scanf("%d",&n);//输入个数
    sum=n;//暂时保存
    while(n--)//直接while循环输入，n不断减小，这也是要设置sum的原因
    {
        scanf("%d",&x);//输入
        tot+=x;//累加
    }
    printf("%.6f",1.0*tot/sum);//输出
}
```

$Python3$：

```python
n = int(input()) # 输入个数
tot = i = 0 # tot为总和，i用来循环（其实也可以不设i）
num = list(map(int, input().split())) # 可以单行读入整个列表
for i in range(len(num)):
    tot += num[i] # 累加
print(float(tot / n)) # 输出（至少不需要控制位数，所以直接输出float格式）
```

---

## 作者：yzx72424 (赞：0)

题意，求n个数的中位数。

QAQ，简单模拟即可。下文有注释

```
#include<bits/stdc++.h>
using namespace std;
string str[30100];
int a,b,r;
double s=0; //s记录n个数的和
int main(){ 
     cin>>a;//题目里的n
     for(int i=1;i<=a;i++){
     	double x;
     	cin>>x;//读入数据
     	s+=x;//求和
     }
     printf("%.13f",s/(double)a);//用平均数公式算出
}

```



---

## 作者：江山_远方 (赞：0)

蒟蒻又双叒叕来写题解啦！

题目很简单，就是求这N杯混合橙汁倒在一起后橙汁占总液体的百分比

由于与正解的差不能超过0.0001 所以输出要保留4位小数

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int x;
int sum;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		sum+=x; 
	} 
	printf("%.4lf",sum/(n*100.0)*100);
	return 0;
} 
```
AC 100分！

---

