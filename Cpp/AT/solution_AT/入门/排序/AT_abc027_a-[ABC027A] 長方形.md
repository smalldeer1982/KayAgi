# [ABC027A] 長方形

## 题目描述

给定一个长方形的 $3$ 条边的长度。请你求出剩下的 $1$ 条边的长度。

## 说明/提示

### 样例解释 1

这是一个 $1 \times 2$ 的长方形。

### 样例解释 2

输入的顺序是任意的。

### 样例解释 3

正方形也是长方形。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3 4```

### 输出

```
3```

## 样例 #3

### 输入

```
5 5 5```

### 输出

```
5```

# 题解

## 作者：_Andy_Lin_ (赞：7)

[博客传送门](https://www.luogu.com.cn/blog/linguosheng/)

------------
题目说明，这里面必定有两个相同的数，他们的异或值肯定为0。所以，我们可以将三个数异或起来，相同的数肯定抵消了，就可以输出剩下的这一个数啦！

---------------
AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
	scanf("%d%d%d",&a,&b,&c);
	printf("%d\n",a^b^c);
	return 0;
}
```

---

## 作者：不到前10不改名 (赞：2)

```
//原题意思一直被误解
正确翻译：是给定一个长方形的三条边，求其余的那条边（保证两个相等也就是因为长方形对边相等，三个相等输出另一个就是考虑到正方形）
废话不多说，上代码！
#include<stdio.h>
int srx,sry,lhy;//防伪标志
int main()
{
    scanf("%d%d%d",&srx,&sry,&lhy);
    if(srx==sry&&srx==lhy)
    {printf("%d\n",srx);//为什么这样做翻译中已经有讲了
    return 0;}
    if(srx==sry)
    printf("%d\n",lhy);
    else if(srx==lhy)//关于判断，它只要四个就可以了~（几位大佬的都多了）
    printf("%d\n",sry);
    else if(sry==lhy)
    printf("%d\n",srx);//回车
    return 0;
}
```

---

## 作者：⚡进击_蒟蒻⚡ (赞：1)

### 这道题讲了什么，简单的来说就是，

### 给你三个数，相等则任意输出一个数

### 反之则输出不同的那个数

### 需要注意的是，数据有空格

# 思路：

### 因为数据中并没有考虑到全不相等的情况，

### 所以我们在判断时可以忽略。

### 接着我们就可以写代码了

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;//输入。
    if(a==b)//判断a、b是否相等
    cout<<c;
    else if(b==c)//如果不相等判断b、c是否相等
    cout<<a;
    else cout<<b;
    puts("");
    return 0;
}
```


---

## 作者：顾z (赞：1)

**题目描述：**

输入三个数,判断三个数是否相等。

如果全部相等,输出任意一个数。

否则输出不相同的数。

(数据保证有两个数相等)


### 广告: [安利blog](https://www.luogu.org/blog/RPdreamer/#)

**分析：**

超级水的一个题,~~看了看前人的题解,好长啊。~~

表现一下**sort**的妙用

对于三个数 sort之后就成为有序的一段。

	如果比较前两个数相同,直接输出第三个数。
    (这样的话可能三个数相同,也可能第三个数比其他数大,直接输出满足题目要求)

	否则,直接输出第一个数。
    (如果前两个数不同,那么后两个数一定相同,则第一个数肯定是不同的一个)

这样是可以保证正确性的。~~(应该是~~

------------------代码------------------

```cpp
#include<bits/stdc++.h>
#define IL inline
#define RI register int
using namespace std;
int a[5];
int main()
{
    cin>>a[1]>>a[2]>>a[3];
    sort(a+1,a+4);//核心
    if(a[1]==a[2])
        std::cout<<a[3]<<std::endl;
    else 
    	cout<<a[1]<<endl;
}
```

---

## 作者：Messi李 (赞：1)

题意：输入三个数，判断三个数是否相等，如相等

输出其中任意一个数，否则输出那个不相等的数

（保证有两个数相等）

直接用判断

上代码

```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int main(){
    int a,b,c;
    cin>>a>>b>>c;//输入三个数
    if(a==b)//判断前两个数是否相等
    {
        if(a==c) cout<<a<<endl;
        //如果相等，继续判断第三个数，
        else cout<<c<<endl;
        //如果都相等，输出其中一个
        //否则输出那个不相等的
        return 0;//直接结束程序啦，避免重复输出
    }
    else if(a==c)//同理
    {
        if(b==c) cout<<a<<endl;
        //同理，就是考虑另一种情况
        else cout<<b<<endl;
        return 0;
    }
    else if(b==c)//同理
    {
        if(a==b) cout<<a<<endl;
        else cout<<a<<endl;
        return 0;
    }
    
}
```

本题判断情况较多，可以慢慢考虑

---

## 作者：lsyx0918 (赞：0)

这道题就是判断最小数，但是基于三个数同样的点，呃……我在if判断中直接加入了“return 0;”，这样可以避免某些东西，呃……（一时表达不出来）

现在发射题解波：
```
#include<iostream>//头文件
using namespace std;
int main()//主函数
{
    int a,b,c;//定义变量
    cin>>a>>b>>c;//输入
    //判断哪个是不同数
    if(a==b)  {cout<<c<<endl;return 0; }
    if(b==c)  {cout<<a<<endl;return 0; }
    if(a==c)  {cout<<b<<endl;return 0; }
    //拜拜了您嘞！
}
```
铃声响起

广播时间到！！！！！

“请大家**一定要换行！！**”

---

## 作者：lv_1977839633 (赞：0)

# 题解 AT1428   [【長方形】](https://www.luogu.org/problem/AT1428)

**开始了，我的强迫症！！！**


------------
**很简单的一道水水水水水......
~~while(1)	cout<<"水";~~
题**


**然鹅**

我还是选择**用一个函数**来展现一下
**代码的**
**建筑美！**

------------
```cpp
#include<iostream>//头文件

using namespace std;

void search(int a, int b , int c) //依次判断
{
	if(a == b)
	{
		cout<<c<<endl;
		exit(0);//结束整个程序（P.S：不是这个函数！！！）
	}
	
	return ;
}

int main(void)
{
	int a,b,c;
	
	cin>>a>>b>>c;
	
    //依次判断
	search(a,b,c);
	search(a,c,b);
	search(b,c,a);
	
	return 0;
}
```

**~~简单易懂！~~**

**~~还是很工整的~~**


------------



*P.S.：~~**少刷水题！！！**~~*

---

## 作者：Happy_Dream (赞：0)

首先讲一讲思路吧：

1，把这三个数放入数组输入

2，把三个数按从小到大排序

3，如果最小的数等于最大的数，就证明三个数都相等，就输出任意一个数

4，判断最小的数和其次小的数是否相等，再判断最大的数和其次大的数是否相等，如果满足就输出另外一个数。

***

注意事项：

1，要sort到第四个元素（要+1）

2，**一定要换行**

3，急时return 0;

代码：

***

```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;//常规
int main()//主函数
{
	int a[4];//定义
	cin>>a[1]>>a[2]>>a[3];//输入
	sort(a+1,a+4);//排序（按从小到大排序）
	if(a[1]==a[3])//判断三个数是否都相等
	{
		cout<<a[1]<<endl;输出随意一个数
		return 0;//结束
	}
	if(a[1]==a[2])//判断有没有两个数是相等
	{
		cout<<a[3]<<endl;//输出另一个数
		return 0;//结束
	}
	if(a[2]==a[3])//判断有没有两个数是相等
	{
		cout<<a[1]<<endl;//输出另一个数
		return 0;//结束
	}
	return 0;//结束
}
```

***

希望大家能从这篇题解中学到知识，谢谢！

---

## 作者：αnonymous (赞：0)

见题解汪洋中竟然没有一篇Python的，细想近日朕的信息老师教了咱们Python，于是写下此题解


------分割线------
其实很简单，三个相等时，输出哪个都可以。那么，只需判断a，b；b，c便可以判定哪一个不一样
```python
a,b,c=map(int,input().split())
if a==b:
    print(c)
elif a==c:
    print(b)
else:
    print(a)
```


---

## 作者：绝艺 (赞：0)

# 其实这道题有一个很简单的思路:
### 只需判断两个数相等，然后输出第三个数就可以了
**下面上代码：（注释代码里有）**
```cpp
#include <iostream>//就不用万能头 
using namespace std;
int main(){
	int a,b,c;
	cin>>a>>b>>c;
	if(a==b){//如果两个数相等就输出第三个数，下同 
		cout<<c<<endl;//记得换行QAQ 
		return 0;//输出就立刻结束，防止重复输出 
	}
	else if(b==c){
		cout<<a<<endl;
		return 0;
	}
	else if(a==c){
		cout<<b<<endl;
		return 0;
	}
} 
```
~~蒟蒻码字不易，望管理员大佬通过~~~

---

## 作者：初音ミク_Miku (赞：0)

~~好吧我不得不说这题怎么这么简单。。。~~  
# 萌新专用题解，大佬请绕过

咳咳，不说废话了，开始。  
首先，审题。  
简单概括题目，就是三个数如果一样，那么输出三个数之一，否则输出不一样的那个。  
先来，我们先看三个数一样的这个情况。  
根据题目，如果输入`1 1 1`，输出就是`1`，如果输入`3 3 3`，输出就是`3`。  
推出如下代码：  

```
int a,b,c;
if(a==b&&b==c&&a==c)
	cout<<a<<endl;//这里输出a，也可以输出b或者c
```

接着来看，如果有两个数一样，另一个数不一样的情况。  
我们同样举例说明：
输入`1 1 2`，输出`2`。  
输入`2 3 2`，输出`3`。  
输入`4 3 3`，输出`4`。  
不难发现输出的就是不一样的那个数，也就是题目中所说的三个数中不一样的那个数！  
那么就简单了，但是需要注意判断的次数，$a$、$b$、$c$都要判断到：

```
//注：这是接着上面的代码，所以使用else if
else if(a!=b&&b==c)
	cout<<a<<endl;
else if(b!=a&&a==c)
	cout<<b<<endl;
else 
	cout<<c<<endl;
```

既然把每一种情况都考虑到了，这道题目就可以做了。  
Code：

```
#include<bits/stdc++.h>//万能头文件，简称万头，涵盖大部分你知道的头文件，注意是大部分，不是所有
using namespace std;//名字空间
int main()//主函数
{
    int a,b,c;//也就是样例中输入的数据
    cin>>a>>b>>c;//输入
    if(a==b&&b==c&&a==c)cout<<a<<endl;//三个数如果都一样的情况
    else if(a!=b&&b==c)cout<<a<<endl;//a不一样
    else if(b!=a&&a==c)cout<<b<<endl;//b不一样
    else cout<<c<<endl;//c不一样
    return 0;//千万别少掉这句注意，养成良好的编程习惯很重要
}
```

---

## 作者：CZQ_King (赞：0)

蒟蒻在这里发一篇没有代码的题解。

------------
实际的翻译是这样的：一个矩形，给出其三条边，求出另一条边。
### 其实，我们可以这样做
- 首先，我们可以想到，矩形的面积为$S=a\ast b$。
- 如果已知面积和一条边的边长，怎样求另一条边呢，当然是$a=\frac{S}{b}$或$a=\frac{S}{a}$
- 所以，我们可以先求出面积，在除以一条边的边长。就可以得到另一条边了

---

## 作者：Start_13 (赞：0)

这题很简单，一个排序加一个判断就可以了。

下面就是我的程序
```cpp
#include<bits/stdc++.h>//万能
using namespace std;//不讲
int k[4];//定义一个数组，就可以快排
int main()
{
	cin>>k[1]>>k[2]>>k[3];、//输入三个数
	sort(a,a+4);//不讲
	if(a[1]==a[2])//判断第一，二个数是否一样
	cout<<a[3]<<endl;//输出不讲
	else
	cout<<a[1]<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

暴力不解释
题意为：给定3个数字，保证有至少2个数字相同。   
若3个数字相同，输出任意一个。   
否则输出不同的一个。    
友情提示：加回车（P党略过）！！！   
代码如下：
```pascal
var
    a,b,c:longint;//定义
begin
    readln(a,b,c);//输入
    if(a=b)and(b=c)then writeln(a)//优先判断是否全部相同
    else
    begin
        if(a=b)then writeln(c)//暴力的判断
        else if(a=c)then writeln(b)
        else writeln(a); 
    end;
end.//撒❀结束！

```

---

## 作者：Xxzxx (赞：0)

暴力判断 注意当前判断哪个数

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int i,j,k;//三个数
    cin>>i>>j>>k;//输入
    if(i==j&&j==k)cout<<i;//判断全相等
    if(i==k&&i!=j)cout<<j;//判断两个相等
    if(k==j&&k!=i)cout<<i;//判断两个相等
    if(i==j&&i!=k)cout<<k;//判断两个相等
    cout<<endl;//注意换行
    return 0;//结束
}

```

---

## 作者：WSEDSWZD (赞：0)

蒟蒻直接胡乱判断了..

注意每个if前都要加else，不然可能会重复输出不同那个..

匆忙写的可能有很多漏洞..

```cpp
```#include<iostream>
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    if(a==b&&a==c&&b==c)cout<<a<<endl;
    else if(a==c&&a!=b)cout<<b<<endl;
    else if(a==b&&a!=c)cout<<c<<endl;
    else if(b==c&&b!=a)cout<<a<<endl;
    else if(b==a&&b!=c)cout<<c<<endl;
    else if(c==b&&c!=a)cout<<a<<endl;
    else if(c==a&&c!=b)cout<<b<<endl;
    return 0;
}
```
```

---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题十分简单，本蒟蒻先讲一下这道题的思路：1、如果三个数都相等，输出第一个。2、有一个数不同，输出那个数。好了，如果读者还不会，请看下方代码：

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int a[3];
    int main()
    {
    cin>>a[1]>>a[2]>>a[3];//读入三个数
    if(a[1]==a[2]&&a[2]==a[3])cout<<a[1]<<endl;//如果都相同，输出a[1]
    if(a[1]!=a[2]&&a[2]==a[3])cout<<a[1]<<endl;//如果a[1]不一样，输出它
    if(a[1]==a[3]&&a[1]!=a[2])cout<<a[2]<<endl;//如果a[2]不一样，输出它
    if(a[1]==a[2]&&a[1]!=a[3])cout<<a[3]<<endl;//如果a[3]不一样，输出它
    return O;//大家应该明白我的用意
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：Moondevourer (赞：0)

看了前面几位大佬的题解，感觉我这个C++的代码不咋地。 但还是发一下代码，话不多说，

# 上代码：
```c
include<bits/stdc++.h>
using namespace std;
int main() 
{
    int n1,n2,n3; cin>>n1>>n2>>n3;//输入三个数。 	
    if(n1==n2)//如果n1==n2，要嘛n1==n2==n3,要嘛n3不同于n1、n2。
    {
    	cout<<n3<<endl;//注意换行。
        return 0;//避免重复输出。 
    }
    if(n1==n3)//如果n1==n3，n1==n2已经判断过了，因此得出n2不同。 
    {
    	cout<<n2<<endl;
        return 0;//同理。 
    } 
    else//只剩下n2==n3和不等于了，直接输出n1。 
    { 
    	cout<<n1<<endl;
        return 0;//同理。 
    } 
    return 0;
}

---

