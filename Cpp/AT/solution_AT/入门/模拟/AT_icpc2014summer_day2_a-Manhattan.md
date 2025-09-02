# Manhattan

## 题目描述

## 题目大意

输入一个实数n，输出max(sqrt(2)*n,floor(n)+1)

# 题解

## 作者：CZQ_King (赞：2)

### 楼下那个代码有一些繁琐，应该可以不用那么复杂。

------------
~~做法：按照题意模拟即可~~

------------
~~最短~~代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a;//有毒
int main(){
    cin>>a;
    cout<<fixed<<setprecision(10)<<max(sqrt(2)*a,floor(a)+1)<<endl;//输出更大的+10位小数
    return 0;//结束
}
```

---

## 作者：陈洋琛 (赞：2)

一道水题，直接模拟就好了，程序中有注释

献上代码：
~~~
#include <cmath>
#include <cstdio>
using namespace std;

double a; //定义变量

double max(double a,double b) {
	return a>b?a:b;      //比较大小的函数
}

int main()
{
	scanf("%lf",&a); //输入
	printf("%.10lf\n",max(sqrt(2)*a,floor(a)+1)); 
    //输出根号2*a与floor(a)+1中的最大值
	return 0; //结束程序
}
~~~

---

## 作者：UnyieldingTrilobite (赞：1)

有毒······

题目里有一个隐藏条件，保留 $10$ 位小数······

~~要不是看了题解还真不知道。~~

其他的么，就是膜你了。

上代码（python 3）：
```
import math#math 库
n=float(input())#输入n
print("%.10f"%max(math.sqrt(2)*n,math.floor(n)+1))
#按题目说的输出罢，没什么说的，就是膜你，注意一下输出格式的使用
```
这题就没了······

---

## 作者：hhrq (赞：0)

按题意模拟即可。

由于需要保留10位小数，所以要定义double:``` double n, ans;```

然后输入$n$（很明显，cin或scanf均可）:```scanf("%llf", &n);```或```cin >> n;```

赋值$ans$ :``` ans = max(sqrt(2)*n,floor(n)+1);```

然后输出（记得保留10位小数）（AT一定要换行。AT不换行，爆零两行泪）```printf("%.10lf\n", ans);``` 或 ``` cout << fixed << setprecision(10) << ans << endl;```

于是就结束了。

code
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;

double n, ans;//定义

int main()
{
	scanf("%llf", &n);//输入n
	ans = max(sqrt(2)*n,floor(n)+1);//按题意赋值
	printf("%.10lf\n", ans);//保留十位小数并且换行，输出
 	return 0;//结束
}

```

---

## 作者：银银银 (赞：0)

原题目链接  [Manhattan](https://www.luogu.com.cn/problem/AT1037)

不要看没有题目就不做

最重要的还是**翻译**



看看翻译
**输入一个实数n，输出max(sqrt(2)\*n,floor(n)+1)**

那么这题答案不就出来了吗

**直接模拟**

那么，直接模拟不就有代码了吗

于是乎，第一次代码就出来了

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    double N;//要用double，保证不错
    cin>>N;
    cout<<max(sqrt(2)*N,floor(N)+1)<<endl;//模拟就好了呀
    return 0;
}
```
一看，[咋没过呢](https://www.luogu.com.cn/record/31571263)

反反复复看题目

突然绝望

**日本人坑人啊**

题目上说
| 输入一个实数n，输出max(sqrt(2)\*n,floor(n)+1) |
| -----------: |

其实还要
| 保留10位小数|
| -----------: |

就是这个原因我才没有AC

于是乎，上正确代码

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    double N;//要用double，保证不会错
    cin>>N;
    cout<<fixed<<setprecision(10)/*这个是我们老师教我们的不用printf的妙招*/<<max(sqrt(2)*N,floor(N)+1)<<endl;//模拟
    return 0;
}
```

由于自身原因，代码中的变量全是原题变量，所以，**不要copy**

[AC在此，证明代码是对的](https://www.luogu.com.cn/record/31571590)

希望对大家有帮助

---

## 作者：lsyx0918 (赞：0)

这道题已经把答案给出来了，就是**max(sqrt(2)*n，floor(n)+1)***，所以说这道题连还只会输入输出的蒟蒻都会做了

话不多说，贴代码喽：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<iomanip>
//这里用万能头也可以
using namespace std;
double n;//定义全局变量，刚刚进入页面时发现有位大佬把变量定义成int类型的了，题目上说是实数了，应该用double类型
int main()//主函数
{
	cin>>n;//输入
	cout<<fixed<<setprecision(10)<<max(sqrt(2)*n,floor(n)+1)<<endl;//按照题目给的公式输出
	return 0;//结束
}
```
看完之前，在提醒一下：

**AT不换行，暴零两行泪**

---

## 作者：Kaedeuim (赞：0)

题记：第二次吃日本题解

![](https://cdn.luogu.com.cn/upload/pic/60836.png)

这道题唯一的坑点就是并没有告诉你它要输出几位小

数，所以养成好习惯，还是输出10位吧......

那么这里注意了：

一定一定要用double。

一定一定要用double。

一定一定要用double。

~~重要的事情说三遍~~

# AC Code

```cpp
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
	double n;
	cin>>n;
	cout<<fixed<<setprecision(10)<<max(sqrt(2)*n,floor(n)+1)<<endl;
	return 0;
 }
 ```
 

---

## 作者：I_will (赞：0)

这道题其实很简单，题目已经写了：

	输入一个实数n，输出max(sqrt(2)*n,floor(n)+1)

所以，我想把它分开来求。

x=sqrt(2);//1.4142135624

floor(n);//(n).0000000000

再用max判断就OK了。

这是程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	double n,x,y;
	cin>>n;
	x=sqrt(2);
	y=floor(n);
	cout<<fixed<<setprecision(10)<<max(x*n,y+1);
	cout<<endl;
	return 0;
}
```

---

## 作者：勘探员·引魂人 (赞：0)

**前言：今天在刷AT的题是，许多都是字符串的入门题，这是我今天刷的唯一一道非字符串的题。**

**思路：直接输出题目给的“max(sqrt(2)*n,floor(n)+1)”（但是我用了某些小技巧）***

**代码：**
```
#include<bits/stdc++.h>//我终于会打万能文件头了！（其实是不打都不行）
using namespace std;
int hs(int x)//让我教你们写写函数
{
	return max(sqrt(2)*x,floor(x)+1);//函数里直接写题目给的max(sqrt(2)*n,floor(n)+1)
}
double n;//定义这个数字（必须用double）
int main()
{
	cin>>n;//输入要执行命令的这个数
	cout<<fixed<<setprecision(10)<<hs(n)<<endl;//取10位小数，调用函数并输出
	
	return 0;
}
```

---

