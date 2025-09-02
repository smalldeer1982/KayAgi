# JGTLE - Jalil Got TLE

## 题目描述

Ananta Jalil 是一个多才多艺的人。他可以完成任何对别人来说不可能的任务。最近，他学会了编程基础。在一个问题中，他提交了以下解决方案：

```cpp
#include <stdio.h>

int main()
{
   int t;
   scanf("%d", &t);
   for(int tc = 1; tc <= t; ++tc) {
       int a, b, c;
       scanf("%d %d %d", &a, &b, &c);
       long long result = 0;
       for(int i = 1; i <= a; ++i) {
           for(int j = 1; j <= b; ++j) {
               for(int k = 1; k <= c; ++k) {
                   result += j * k;
               }
           }
       }
       printf("Case %d: %lld\n", tc, result);
   }
   return 0;
}
```

但由于他是编程新手，他得到了 TLE（Time Limit Exceeded，超出时间限制）。因此他的解决方案效率不高。所以，你需要为 Jalil 编写一个优化的解决方案，以获得相同的输出。

## 样例 #1

### 输入

```
3
1 4 3
3 4 2
143 342 777```

### 输出

```
Case 1: 60
Case 2: 90
Case 3: 2535110464887```

# 题解

## 作者：封禁用户 (赞：5)

好久不见啊，我回来啦！

~~为什么题面上代码的马蜂这么难受啊。~~

蒟蒻有强迫症，雷锋叔叔告诉我们，要舍己为人。所以，小萌新把马蜂改了一下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    scanf("%d",&t);
    for(int tc=1;tc<=t;++tc) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        long long resul=0;
        for(int i=1;i<=a;++i) {
            for(int j=1;j<=b;++j) {
                for(int k=1;k<=c;++k) {
                    result+=j*k;
                }
            }
        }
        printf("Case %d: %lld\n",tc,result);
    }
    return 0;
}
```
唔，看起来舒服多了。

~~上面都是废话，这个人脑子有点问题，不要管她。~~

其实这题跟初赛的阅读程序写结果有点像，考的都是你对程序的理解能力。

这……四重循环不炸才怪了呢。

```cpp
for(int i=1; i<=a; ++i) {
    for(int j=1; j<=b; ++j) {
        for(int k=1; k<=c; ++k) {
            result+=j*k;
        }
    }
}
```
这一段代码，实际上就是在求$a\times \sum_{i=1}^b\times \sum_{i=1}^c$ 的值。

读过幼儿园的同学都知道，高斯求和是求等差数列的好方法。

可得出，$\sum_{i=1}^b=\frac{(b+1)b}{2}$。

同理，$\sum_{i=1}^c=\frac{(c+1)c}{2}$。

那么答案就是，$a\times\frac{(b+1)b}{2}\times \frac{(c+1)c}{2}$。


发现一件跟long long有关的玄学事情：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x;
int a,b,c,n;
int main() {
    scanf("%d",&n);
    for(int i=1; i<=n; ++i) {
        scanf("%d%d%d",&a,&b,&c);
        x=a*((1+b)*b/2)*((1+c)*c/2);
        printf("Case %d: %lld\n",i,x);
    }
    return 0;
}
```
这份代码本地测试样例的时候输出：

```cpp
Case 1: 60
Case 2: 90
Case 3: 1079760247
```
改成这样就AC了：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,a,b,c,n;
int main() {
    scanf("%d",&n);
    for(int i=1; i<=n; ++i) {
        scanf("%d%d%d",&a,&b,&c);
        x=a*((1+b)*b/2)*((1+c)*c/2);
        printf("Case %d: %lld\n",i,x);
    }
    return 0;
}
```

什么情况？！

>十年OI一场空，不开long long见祖宗。

---

## 作者：Lucky__E (赞：2)

  不得不说这题太水了，真不知道怎么到蓝题的。
  不多废话，直接讲。显而易见，原代码是一个四重循环的大暴力，
所以只要我们只要把时间复杂度降下来即可。

  先看a，这一层的存在很明显是多余的，只要在最后乘一下（result*a)就可以优化掉了。
  
  接下来是b和c，这两层要找一下规律，拿出你的纸和笔算一算，很快可以发现result=a*[b+(b-1)+......+1]*[c+(c-1)+......+1]
  
  做出来了！（听不懂的退了吧————cjq）现在上代码
  ```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; ++tc) 
	{
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        long long result=0,x=0,y=0;
        for(int j=1;j<=b;j++) 
		{
            x+=j; 
        }
        for(int j=1;j<=c;j++)
        {
        	y+=j;
		}
        result=a*x*y;
        printf("Case %d: %lld\n", tc, result);
    }
    return 0;
}
```

---

## 作者：yuyc (赞：1)

这道题是让你优化程序，防止TLE。So我们先看题中TIE的代码，其中最不顺眼的就是三重嵌套for循环：
```cpp
for(int i = 1; i <= a; ++i) {
       for(int j = 1; j <= b; ++j) {
           for(int k = 1; k <= c; ++k) {
               result += j * k;
           }
       }
   }
```
所以我们要改的就是这里，先来看它求的是啥，代入样例的第一个得：
$$result=1\times(1\times1+1\times2+1\times3)+(2\times1+2\times2+2\times3)+(3\times1+3\times2+3\times3)+(4\times1+4\times2+4\times3)$$
简化后得到这个公式：
$$result=a\times((1+2+3+4+...b)\times(1+2+3+4+...c))$$

也就是：
$$result=a\times\sum_{i=1}^{b}\times\sum_{i=1}^{c}$$
知道了这些就可以开始改代码了：
```cpp
#include <stdio.h>
long long jiejia(int n){//定义一个阶加的函数，注意！不开long long见祖宗
	if(n==1) return 1;
	return jiejia(n-1)+n;//简单的递归算法
}
int main()
{
   int t=0;//初始化是个好习惯
   scanf("%d", &t);
   for(int tc = 1; tc <= t; ++tc) {
       int a=0, b=0, c=0;
       scanf("%d %d %d", &a, &b, &c);
       long long result = 0;
       result=a*jiejia(b)*jiejia(c);//用上了我们得出的公式和函数
       printf("Case %d: %lld\n", tc, result);
   }
   return 0;
}
```
所以说，这种题只要知道它要求的是什么，就很好解了。


---

## 作者：agicy (赞：1)

# 思路

## 理论依据

等差数列求和公式：$\sum^n_{i=1}i=\frac{n(n+1)}{2}$

## 推理过程

下面观察题目的源代码。

```cpp
#include <stdio.h>

int main()
{
    int t;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; ++tc) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        long long result = 0;
        for(int i = 1; i <= a; ++i) {
            for(int j = 1; j <= b; ++j) {
                for(int k = 1; k <= c; ++k) {
                    result += j * k;
                }
            }
        }
        printf("Case %d: %lld\n", tc, result);
    }
    return 0;
}
```

很明显，得出以下三个结论。

- 一

	```cpp
	for(int j = 1; j <= b; ++j) {
		for(int k = 1; k <= c; ++k) {
			result += j * k;
		}
	}
    ```
    
    这条`for`循环语句相当于：
    
    ```cpp
    for(int j = 1; j <= b; ++j) {
		result += j*c*(c+1)/2;
	}
    ```
    
- 二

	根据结论一，进一步推广可得。
    
	```cpp
    for(int i = 1; i <= a; ++i) {
        for(int j = 1; j <= b; ++j) {
            for(int k = 1; k <= c; ++k) {
                result += j * k;
            }
        }
    }
    ```
    
    等价于：
    
    ```cpp
    for(int i = 1; i <= a; ++i) {
        result+=b*(b+1)/2*c*(c+1)/2;
	}
    ```
    
- 三
	
    很明显，上面得出的优化代码可以省去最后一个循环，得到最终结论，即：
    
    $result=a×\frac{b(b+1)}{2}×\frac{c(c+1)}{2}$
    
## 插曲

你以为得出上面那个结论就结束了？

不，这题太毒瘤了，如果先乘$a$再进行运算，结果（在`long long`下）会溢出（当然你可以用`unsigned long long`），正确答案是：

$result=\frac{b(b+1)}{2}×\frac{c(c+1)}{2}×a$

# 代码

代码如下。

```cpp
#include<cstdio>

int T;
long long a,b,c,ans;

int main(void){
	register int i;
	scanf("%d",&T);
	for(i=1;i<=T;++i){
		scanf("%lld%lld%lld",&a,&b,&c);
		ans=b*(b+1)/2*c*(c+1)/2*a;//一定要这样防止溢出
		printf("Case %d: %lld\n",i,ans);
	}
	return 0;
}
```

## [我的评测记录](https://www.luogu.org/record/show?rid=11446153)


---

## 作者：_Qer (赞：1)

这不是数学题吗？！

首先题目中的循环$a$次求和可以直接用后两个循环乘$a$来代替  
然后看后两个循环

```cpp
	for(int j = 1; j <= b; ++j) {
    	...
    }
```

这一个循环可以用高斯求和变成

$$\frac{(1+b)b}{2}$$

同理第三个循环就变成

$$\frac{(1+c)c}{2}$$

那么这两个循环嵌套起来就是

$$\frac{(1+b)(1+c)bc}{4}$$

然后三个循环搞到一起就是

$$\frac{(1+b)(1+c)abc}{4}$$

最后注意一点，运算过程要用$\text{unsigned~long~long}$防止溢出（~~两次WA血的教训~~）

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
unsigned long long a, b, c;//直接开就行
int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        scanf("%lld%lld%lld", &a, &b, &c);//输入会强制转换
        printf("Case %d: %lld\n", tc, a * (1 + c) * c / 2 * (1 + b) * b / 2);
        //强制转换
    }
    return 0;
}
```

---

## 作者：Kevin_Zhen (赞：0)

题目链接 [$\mathfrak{SP34011}$](https://www.luogu.com.cn/problem/SP34011)。

### 解题思路
最外层循环一共累加了 $a$ 次，每一次加上 $\sum\limits_{i=1}^bi\times \sum\limits_{j=1}^c=\sum\limits_{i=1}^b\times \sum\limits_{j=1}^c$。  
故输出答案为 $a\times \sum\limits_{i=1}^b\times \sum\limits_{j=1}^c$。

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

int T;

int main() {
	scanf("%d", &T);
	for (int i = 1; i <= T; ++i) {
		ll a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
		printf("Case %d: %lld\n", i, (b + 1) * b / 2 * (c + 1) * c / 2 * a);
	}
	return 0;
}
```

### 感谢观赏！

---

## 作者：CrTsIr400 (赞：0)


这道题目的暴力可以一直优化。

首先我们来看题目的代码， $3$ 重循环的哪一重**的循环变量**与**答案无关？**

明显可以看出，第一层 $i$ 循环没有任何必要，仅需在最后的答案里**乘上一个 $a$ 即可。**

所以时间复杂度从 $O(tabc)$ 降至 $O(tbc)$ ，但是还是会`TLE`。怎么办呢？

我们又可以发现，第三层循还可以简化成等差数列公式，$\sum^{c} _{1}=(1+2+...+c-1+c)=(c+1)\times c/2$。

再来看看第二重循环，哟，这不也是个等差数列吗？

发现这个` result += j * k; `可以转化成`result+=j*(1+c)*c/2`。

我们惊喜地发现，这个`j`也是递增的，而且可以根据**乘法分配律**得知：

$(a+b)c=ac+bc$

倒过来：

$ac+bc=(a+b)c$

实际上，我们求出前面所有 $j$ 变量的和即可。

于是，因为等差数列公式得知，前面所有 $j$ 变量之和可以变成 $(1+j)\times j \div 2$

然后就变成了这样：

`result=((1+b)*b/2)*((1+c)*c/2)`。

于是最后时间复杂度一直简化，从$O(tabc)$ 到 $O(t)$。

答案就是 $a \sum^{1} _{b}  \sum^{1} _{c}$，即 $a \times [(1+b)*b\div 2] \times [(1+c)*c\div 2]$ 。

细节：注意`long long`，末尾**不要忘记乘上最后的 $a$！**

没了。

---

## 作者：bovine__kebi (赞：0)

其实这题真正的目的是让我们化简式子，那我们就来搞一下     
题目实际上让我们求：
$res=\sum\limits_{i=1}^a\sum\limits_{j=1}^b\sum\limits_{k=1}^cj*k$  

我们将最后一个求和展开，提出因数j，可以发现，最后一个关于k的求和是一个等差数列公式，因此式子即可化简成：
$res=\sum\limits_{i=1}^a\sum\limits_{j=1}^bj*\dfrac{c(c+1)}{2}$   

同样的，我们也可以展开j，那么式子就变成了：$res=\sum\limits_{i=1}^a\dfrac{b(b+1)*c(c+1)}{2}$     

前面的求和可以直接认为是乘上一个a，因为内部的变量是没有变的，最后这个式子就是这个样子：
$res=a*\dfrac{b(b+1)*c(c+1)}{2}$   

然后直接模拟编写就好了，代码如下  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
    {
        long long a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        printf("Case %d: %lld\n",i,a*(b*(b+1)/2)*(c*(c+1)/2));
    }
    return 0;
}
```
这题比较简单，希望大家有所收获。

对不起上一次$Latex$炸了，再来提交一次

---

## 作者：Komorebi_shine (赞：0)

## 这就是道数学题……
解：很容易看出最外层的a的循环只要改成在结果处乘a就可以了。接下来看里面b，c的循环，这两个循环的意思就是求[1..b][1..c]两个序列的各项乘积。通过计算，可得：
```
1*1+1*2+1*3+……+1*c+2*1+……+b*c
=1*(1+2+3+……+c)+2*(1+2+3+……+c)+……+b*(1+2+3+……+c)
(乘法分配律)
=(1+2+3+……+b)*(1+2+3+……+c)(乘法分配律)
=((1+b)*b/2)*((1+c)*c/2)(等差数列项数公式，求和公式)
```
综上所述，可得~~这就是道入门题~~以下代码（c++）
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long t,ii,a,b,c;
int main()
{ 
    cin>>t;
    for (ii=1;ii<=t;ii++)
    {
        cin>>a>>b>>c;
        cout<<"Case "<<ii<<": "<<a*((1+b)*b/2)*((1+c)*c/2)<<endl;
    }
    return 0;
}
```

---

## 作者：hero_brine (赞：0)

首先我们来证明一个定理：$\Sigma_{i=1}^n=n*(n+1)/2$  
证明如下：对于$n=1$结论显然成立，不妨设当$n=k$时结论成立，则$\Sigma_{i=1}^k=k*(k+1)/2$,则当$n=k+1$时，$\Sigma_{i=1}^{k+1}=\Sigma_{i=1}^k+(k+1)=(k+1)*(k+2)/2$,那么由**数学归纳法**原理，结论成立。

通过分析题干中的代码，~~显然~~题意可以简化为已知a,b,c，求$a*(b*(b+1)/2)*(c*(c+1)/2)$ 的值，代码如下：
```java
import java.io.*;
import java.util.Scanner;//导入Scanner类
public class Main
{
    static long a,b,c,t;//记得使用static
    public static void main(final String[] args) {
        final Scanner sc = new Scanner(System.in);
        t = sc.nextInt();
        for (int i=1;i<=t;i++)
        {
            a = sc.nextInt();b = sc.nextInt();c = sc.nextInt();//读入
            //println换行，print不换行
            System.out.print("Case ");
            System.out.print(i);
            System.out.print(": ");
            System.out.println((b*(b+1)/2)*(c*(c+1)/2)*a);
        }
        sc.close();//记得释放内存
    }
}
```
注意事项：均在代码注释里面


---

