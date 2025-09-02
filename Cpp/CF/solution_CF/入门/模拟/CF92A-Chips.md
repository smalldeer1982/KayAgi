# Chips

## 题目描述

现在有n个海狮坐成一个圆圈玩♂游♂戏。所有海狮都被顺时针的被编上号码了：2号海狮在1号海狮的左边坐着，3号海狮在2号海狮的左边坐着，……，1号海狮在n号海狮的左边坐着。


我们还有一位慷慨的来自某薯片公司的员工。他为了宣传他的薯片有多好吃，带来了m片薯片来到海狮群做宣传。他站在海狮圈的中间并顺时针转动。第i号海狮可以分到i个薯片。如果这位员工没有足够的薯片，这个黑心的员工就带着剩下的薯片跑了。现在给你n和m，让你求这个员工最后会拿多少薯片。

## 样例 #1

### 输入

```
4 11
```

### 输出

```
0
```

## 样例 #2

### 输入

```
17 107
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 8
```

### 输出

```
1
```

# 题解

## 作者：gzw2005 (赞：4)

一道简单模拟题，活生生变成了一道数学题。

首先，这个~~黑心~~员工给海狮薯片的时候是轮着来的，那么每一轮这个员工就会付出 $S=\dfrac{n(n+1)}{2}$ 个薯片。

到了最后一轮，这个员工还剩下 $M\ mod\ S$ 个薯片。接下来，这个员工先给第 $1$ 个海狮，付出 $1$ 个薯片；给第 $2$ 个海狮，共付出 $1+2$ 个薯片...给第 $i\ (1\le i <N)$ 个海狮，共付出 $\dfrac{i(i+1)}{2}$ 个薯片。题目说了，如果员工剩下的薯片不够下一个海狮了，就会逃走。因此，我们要找到 $\dfrac{i(i+1)}{2}\le M\ mod\ S$ 的最大值。解一下这个不等式，过程如下：

$$i(i+1)\le 2(M\ mod\ S)$$
$$i^2+i-2(M\ mod\ S)\le 0$$

$$\Delta=b^2-4ac\qquad\qquad\qquad\quad$$
$$=1^2-4[-2(M\ mod\ S)]$$
$$=1+8(M\ mod\ S)\qquad\,$$

$$\dfrac{-1-\sqrt{\Delta}}{2}\le i \le \dfrac{-1+\sqrt{\Delta}}{2}$$

$$\dfrac{-1-\sqrt{1+8(M\ mod\ S)}}{2}\le i \le \dfrac{-1+\sqrt{1+8(M\ mod\ S)}}{2}$$

那么 $i_{max}=\left\lfloor{\dfrac{-1+\sqrt{1+8(M\ mod\ S)}}{2}}\right\rfloor$.（当然`C++`是默认向下取整的）

最后输出 $M\ mod\ S-\dfrac{i_{max}(i_{max}+1)}{2}$ 即可。

```
#include<bits/stdc++.h>
using namespace std;
int N,M;
int main(){
	cin>>N>>M;
	int S=N*(N+1)/2;
	int Imax=(-1.0+sqrt(1+8*(M%S)))/2.0;
	cout<<M%S-Imax*(Imax+1)/2;
	return 0;
}
```

---

## 作者：monstersqwq (赞：3)

一道蛮好玩的题，这里给出3种做法。

做法1：

看到这个“围成一圈”的说法，立马就能想到 STL 中的队列，就直接先把所有的数字全部进队，然后按照题意模拟即可。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
queue<int> q;
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		q.push(i);
	}//把队列初始化（海狮们排好圈）
	while(1)
	{
		if(q.front() >m)
		{
			cout<<m<<endl;
			break;
		}
		else
		{
			m-=q.front() ;
		}
		q.push(q.front() ); 
		q.pop() ;
	}
    return 0;
}
```
做法2：

直接暴力模拟每一圈分薯片的情况，分到不能分的时候就输出并结束。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	while(1)
	{
		for(int i=1;i<=n;i++)
		{
			if(i<=m) m-=i;
			else
			{
				cout<<m<<endl;
				return 0;//注意这里不能break，因为如果只break就只能跳出一层循环 
			}
		}
	}
    return 0;
}
```
做法3：

前两个做法在 $n,m$ 的数据过大，甚至超过了 int 范围时，可能就会超时，于是我们要考虑 $\Theta(1)$ 的数学做法。

前置芝士：

1.小学求和公式（高斯搞的那个）：$1$ 到 $a$ 的和是 $\dfrac{a(a+1)}{2}$。
2.一元高次不等式解法（此题只需要一元二次方程的解法+“穿针法”）。

首先我们先把 $m \gets m \bmod \dfrac{n(n+1)}{2}$，即先把所有的整圈干掉。（注，待会所用的 $m$ 全部是已经处理过的 $m$，不再提示）

处理完后，我们要解一个不等式：
$$\dfrac{a(a+1)}{2} \le m$$

化为：
$$a^2+a-2 \times m \le 0$$

先解：
$$a^2+a-2\times m=0$$

解得：
$$a_1=\dfrac{-1- \sqrt{1+8\times m}}{2},a_2=\dfrac{-1+ \sqrt{1+8\times m}}{2}$$

因为是 $\le$，根据“穿针法”可知：
$$a_1\le a\le a_2$$

即：
$$\dfrac{-1- \sqrt{1+8\times m}}{2}\le a\le \dfrac{-1+ \sqrt{1+8\times m}}{2}$$

那么：

$$a_{max}=\left\lfloor\dfrac{-1+ \sqrt{1+8\times m}}{2}\right\rfloor$$

（因为 $a$ 必须是整数，所以向下取整）答案即为：
$$m-\dfrac{\left\lfloor\dfrac{-1+ \sqrt{1+8\times m}}{2}\right\rfloor \times\left\lfloor\dfrac{ \sqrt{1+8\times m}}{2}\right\rfloor}{2}$$

因为有向下取整的原因，化简可能出现玄学错误，就不化简了。

（因为一些 C++ 的自带类型转换或自动取整的精度问题，代码和答案不太一样）代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	m=m%(n*(n+1)/2);
	int maxx=(-1.0+sqrt(1+8*m))/2.0;
	cout<<m-maxx*(maxx+1)/2<<endl; 
    return 0;
}
```


---

## 作者：人间凡人 (赞：0)

题意就不多说了，翻译也有了$...$

方法 $1:$ 模拟 $($ 这不是关键 $)$

方法 $2:$ 数学方法

给完 $n$ 个海马,筹码需要 $n*(n+1)/2$。

所以进行了 $\lfloor \frac{m}{n*(n+1)/2} \rfloor$ 次后，还有筹码 $m$ $mod$ $(n+1)*n/2$

现在假设分完第 $n$ 个海马后没有筹码了

则 $n*(n+1)/2<=m$ 

$n^{2}+n-2m<=0$

配方$!$

$( n+ \frac{1}{2} )^{2}<=2m+\frac{1}{4}$

$ n+ \frac{1}{2} <=\sqrt{2m+\frac{1}{4}}$

$ Max{n} =\lfloor \sqrt{2m+\frac{1}{4}}-\frac{1}{2} \rfloor$

求出来代入 $ans=m-Maxn*(Maxn+1)/2$ 即可

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,z;
double x,y;
int main(){
    scanf("%d%d",&n,&m);
    m=m%(n*(n+1)/2);
    x=(double)(m);
    y=(double)sqrt(2*m+0.25);
    z=floor(y-0.5);
    printf("%d\n",m-(z*(z+1)/2));
    return 0;
}
```





---

## 作者：陈科同 (赞：0)

这是一道~~~~水题~~~~。

先输入n和m。

再一个十分简单的for循环就大功告成了。

代码奉上
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,i=0;
	cin>>n>>m;
	for(;;){
		i++;
		if(i>n)i=1;//木有怎么多海狮，重新发
		if(m>=i)m-=i;//黑心的员工在发薯片
		else{//黑心的员工跑了，留下一脸懵逼的海狮
			cout<<m;
			return 0;
		}
	}
}
```


---

## 作者：blind_L_S_Y (赞：0)

不多说，

上代码！

```c
#include<iostream>
using namespace std;
int main()
{
	int s=0,n,m;//定义变量啦
	/*
	s代表第s个海报(误)
	n代表n个海报(误)
	m代表m个薯片 
	*/ 
	cin>>n>>m;//输入变量啦 
	while(true)//由于我懒，所以。。这个就用for循环模拟啦 
	{
	  s++;
	  if(s>n)
	    s=1;
	  if(m<s)//如果剩下的薯片不够吃啦，就跳出循环 
	    break;
	  m-=s;//如果海豹们还可以吃的话，i%n也就是第i个海豹被分到薯片啦 
	}
	cout<<m<<endl;//输出黑心员工到底带走了多少 
    return 0;//完美结束
//为了和谐洛谷 请勿复制代码 
} 
```
你们知道的。

# 模拟大法！！

---

## 作者：hzx1 (赞：0)

## 模拟题
没那么难，思路很简单~
以前题解里有用while循环的，我就来篇do{}while()的吧~
```cpp
#include<iostream>    //头文件
using namespace std;
int main(){
	int n,m,i=1;     //记得i要初始化为1，因为是从第一只海狮分起
	cin>>n>>m;       //输入
	do{             //do{}while()是先执行后判断
		m-=i;        //模拟发薯片的过程
		i++;         //每发一只i要+1
	    if(i>n)      //当发完一轮后，
	    i=1;         //再次从第一只开始发
	}while(m>=i);    //判断薯片是否足够
	cout<<m<<endl;   //输出最后剩下的薯片
	return 0;        //结束
}
```

---

## 作者：OdtreePrince (赞：0)

# -模拟-

一看题目就知是模拟！用sum统计1~n所有数之和，

m对sum取余，sum清零,再慢慢模拟即可。

注意：while循坏中是 $\color{blue}\texttt{sum<=m}$  哦

~~~
#include<bits/stdc++.h>
using namespace std;
int n,sum,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        sum+=i;
    }
    m%=sum;
    sum=0;
    int j=1;
    while(sum<=m){
        sum+=j;
        j++;
    }
    sum=sum-j+1;
    cout<<m-sum;
    return 0;
}~~~

---

