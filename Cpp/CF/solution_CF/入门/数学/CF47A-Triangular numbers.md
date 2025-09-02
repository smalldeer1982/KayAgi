# Triangular numbers

## 题目描述

A triangular number is the number of dots in an equilateral triangle uniformly filled with dots. For example, three dots can be arranged in a triangle; thus three is a triangular number. The $ n $ -th triangular number is the number of dots in a triangle with $ n $ dots on a side. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF47A/7344b4fd5acb7c973775cffc0c5a51a81c6ee4d9.png). You can learn more about these numbers from Wikipedia (http://en.wikipedia.org/wiki/Triangular\_number).

Your task is to find out if a given integer is a triangular number.

## 样例 #1

### 输入

```
1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
```

### 输出

```
YES
```

# 题解

## 作者：wpy233 (赞：21)

~~蒟蒻滑稽花式AC红题第二弹~~

咳咳，你敢相信吗，蒟蒻我$AC$甚至没有用到一个循环qaq

**正文开始**

众所周知，$i*(i+1)$这个东东的答案肯定是很靠近$i^2$的……

所以，我自然而然地就想到了用$\sqrt{}$这个神奇的东东来接近这个问题……

让我们来看一下：

$\sqrt{1*2}=\sqrt{2}≈1.41421$

$\sqrt{2*3}=\sqrt{6}≈2.44949$

$\sqrt{3*4}=\sqrt{12}≈3.4641$

$\sqrt{4*5}=\sqrt{20}≈4.47214$

……

$\sqrt{31*32}=\sqrt{992}≈31.496$

有没有发现！小数部分似乎越来越接近$0.5$诶~

那么，我们就很开心了~

输入一个数$a$（注意要用浮点型！），$*2$以后再$sqrt()$一下，判断它的小数部分在不在$0.41$（$\sqrt{2}$的小数部分）和$0.5$（小数部分无限逼近的那个数）之间就行了~

提交……

……$Waiting$

……$Judging$

### WA on #20！！！

QAQ这是怎么回事……

后面手算了一组数据，$like$：$\sqrt{990}≈31.46426$

这种情况下，程序仍然会输出$YES$~~吓死我了~~

那怎么办呢？

作者我先在这手算了一个表：

```
1.41421
2.44949
3.4641
4.47214
5.47723
6.48074
7.48331
8.48528
9.48683
10.4881
11.4891
12.49
13.4907
14.4914
15.4919
16.4924
17.4929
18.4932
19.4936
20.4939
21.4942
22.4944
23.4947
24.4949
25.4951
26.4953
27.4955
28.4956
29.4958
30.4959
31.496
//第i行是sqrt(i*(i+1))的结果
```
发现没有！$\sqrt{2}$的时候还有$0.41$左右，到$\sqrt{6}$的时候就到了$0.44$左右，到了$\sqrt{12}$就只有$0.46$了……

也就是说，一开始两两之间的“空隙”比较大，到后面就越来越“紧密”了……

那我们就可以`分段解决`呀！当$a \leq 1$的时候分一段，$2 \leq a \leq 2$的时候分一段，$4 \leq a \leq 5$的时候分一段……

那就……$AC$了？

```
#include <bits/stdc++.h>
using namespace std;
double akioi(double p)//计算小数部分
{
	while(p>=1) p-=1;
	return p;
}
int main()
{
	double a;
	cin>>a;//输入
	a*=2.0;//*2
    //以下是判断部分
	if(a<=1*2)//分段1
	if(0.5>=akioi(sqrt(a))&&akioi(sqrt(a))>=0.41) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	else if(a>1*2&&a<=2*3)//分段2
	if(0.5>=akioi(sqrt(a))&&akioi(sqrt(a))>=0.44) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	else if(a>2*3&&a<=3*4)//分段3
	if(0.5>=akioi(sqrt(a))&&akioi(sqrt(a))>=0.46) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	else if(a>3*4&&a<=5*6)//分段4
	if(0.5>=akioi(sqrt(a))&&akioi(sqrt(a))>=0.47) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	else if(a>5*6&&a<=9*10)//分段5
	if(0.5>=akioi(sqrt(a))&&akioi(sqrt(a))>=0.48) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	else if(a>9*10)//分段6
	if(0.5>=akioi(sqrt(a))&&akioi(sqrt(a))>=0.49) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;//都不是？？？那就输出NO
	return 0;//完美结束
}
```
分段以后，精度和误差杠杠地，~~妈妈再也不用担心我WA啦~~

通过多次的分段，我们就成功地不用循环解决了这道题qaq

打了这么多字，求给个赞再走~谢谢！

---

## 作者：fangd (赞：8)

### 零、 序言  
题目很简单，数据也很小，我给大家提供一个二分的思路，仅供参考。


------------

### 一、题意
这道题目题意很简单，问的是命题：
$$∃i \subset \mathbb{Z}, T(i)= \dfrac {i (i + 1)}{2} = n $$
的真假。  
考虑到$n \in [1, 500]$，我们可以求出$i$地取值范围。又由于二次方程的性质，我们只需在方程中求出其正根，便可以判断负根。当然，题目只是让我们输出YES或者NO。  
又由于$T(i)$在$[-\dfrac {1}{2}, +∞)$**单调递增**的特性的特性（很重要，二分一般只适用于具有单调性的函数。也正因为其单调递增，我才会往二分上面想），我们可以使用二分的思路求出答案。
![函数图像](https://cdn.luogu.com.cn/upload/pic/57957.png)

------------

### 二、二分与检验
我们设$l$与$r$为左端点和右端点，$mid = (l + r) >> 1$为中间值，很容易就可以得到二分（实际上是upper_bound，查到最后，$l$是不小于$i$的最小整数)的算法：
```cpp
while (l < r)
{
    int mid = (l + r) >> 1;
    if (mid * (mid + 1) < (n << 1))
        l = mid + 1;
    else
        r = mid;
}                              
```
迭代到最后，$l$就是可能的答案。当然，$l$可能不存在，因此，我们要对其进行**检验**。
```cpp
if (l * (l + 1) == (n << 1))
    puts("YES");
else
    puts("NO");
```
加上输入和输出，就可以AC掉这道题啦！


------------

### 三、优化
我们可以在$l$和$r$的初值上做文章。如下面这样：
```cpp
int l = static_cast<int>(std::sqrt(n));
int r = (n << 1) + 1;
```
这是为什么呢？由题目，我们可以知道：  
$$ i ^2 + i = 2n $$
不妨设$i > 1$，进而推出以下两个命题：  
$$ i > \sqrt{n} $$
$$ i < \dfrac{n}{2} + 1 $$
证明留给大家作为思考（~~不会证就直说嘛~~）……


------------

### 四、代码
```cpp
#include <cmath>
#include <cstdio>

int main()
{
    int n;
    scanf("%d", &n);
    int l = static_cast<int>(std::sqrt(n)), r = (n << 1) + 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (mid * (mid + 1) < (n << 1))
            l = mid + 1;
        else
            r = mid;
    }
    if (l * (l + 1) == (n << 1))
        puts("YES");
    else
        puts("NO");
    return 0;
}

```


------------
### 五、其它
本文写于2019年5月3日。本人蒟蒻，如有谬误，请大家不吝指教！

---

## 作者：PC_DOS (赞：2)

其实这道题就是解一个一元二次方程

### i^2+i-2n=0

并判断它的正数解是不是整数就可以了(由于n>0，故Delta=sqrt(1+8n)，必定有实数解)。

代码:
```
#include <iostream>
#include <cmath>
using namespace std; //头文件和命名空间
int main(){
	int iInput, iX; //iInput-输入的数，iX-方程的解
	cin >> iInput; //读入
	iX = (-1 + sqrt(1 + 8 * iInput)) / 2; //直接用求根公式求解(另一根(-1 - sqrt(1 + 8 * iInput)) / 2肯定为负，不符合题意)，并将解赋给整数
	if (iX*(iX + 1) == 2 * iInput) //判断一下求得的整数不是解
		cout << "YES"; //如果是，输出YES
	else //否则
		cout << "NO"; //输出NO
	return 0; //结束
}
```

---

## 作者：a13518354766 (赞：2)

# 这题其实就是高斯求和问题，即1+...+x=x（x+1）/2。
由此，我们就可以用递推的思想来解决问题：
#include<bits/stdc++.h>

using namespace std;

int main()
{

	  //freopen("ask.in","r",stdin);
	  //freopen("ask.out","w",stdout);
	  long long n,r=0;
	  cin>>n;
	  for(int i=1;i<=999;++i)
	  {
		  r+=i;
		  if(r==n)
		  {
			  cout<<"YES";//如果成立
			  return 0;
		  }
		  if(r>n)
		  {
			  cout<<"NO";//如果大于了n，则之后的r也必大于n，所以不成立。
			  return 0;
		  }
	  }
	  return 0;
}



---

## 作者：向日葵小班 (赞：1)

## 这题太water了，建议隐藏（滑稽）

**由于可爱的翻译已经给了公式，而且n<=500，那么我们就直接用for吧！！**

## 放代码：
```cpp
#include<bits/stdc++.h>//万能头文件
int n;//定义n
using namespace std;
int main()
{
     cin>>n;//输入n
	 for(int i=1;i<=250000;i++)//从1-250000循环
	 {
	 	if(i*(i+1)/2==n)//套公式判断
	 	{
	 		cout<<"YES";//如果符合公式输出YES
	 		return 0;//完美结束
	 	}
	 }
	 cout<<"NO";//都不符合，输出NO
    return 0;//完美结束
}
```



---

## 作者：suixiang (赞：1)

由题得 i*(i+1)/2=n

所以i*(i+1)=2*n

```cpp
#include <cstdio>
#include <cstring>
#include<algorithm>
#include <iostream>
#include<cmath>//头文件，sqrt需要 
using namespace std;
int main(){
	int n;
	cin>>n;
	int m=2*n;//2*n  
	for(int i=1;i<=sqrt(m);i++){
    //用sqrt(m)，缩短搜索范围.因为i*(i+1)=2*n，所以i<=sqrt(m) 
		if(i*(i+1)==m)
			 printf("YES");//存在，输出YES 
			 return 0;//返回 
		}
	}
	printf("NO");//搜索完，不存在，输出NO 
	return 0;
}
```

---

## 作者：bym666 (赞：0)

# CF47A 【Triangular numbers】
我们先看公式，i*(i+1)/2=n，怎么感觉好像在哪儿见过的样子？想起来了，是高斯~~小朋友~~的等差数列求和公式（~~实话告诉你吧，我没打算用这个~~）。

由于数据范围很小，所以我直接用枚举法，最多也就从1枚举到500，不多不多。

代码如下：
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
int n;
int main()
{
	cin>>n;//输入 
	for(int i=1;i<=n;i++)//枚举 
	{
		if(i*(i+1)/2==n)//如果符合条件 
		{
			cout<<"YES";//输出YES 
			return 0;//结束程序 
		}
	}
	cout<<"NO";//剩下的都不是，输出NO 
	return 0;//结束程序 
}
```


---

## 作者：MIN__2500 (赞：0)

没错又是我，本蒟蒻又来了。
```
#include <bits/stdc++.h>//习惯操作，万能头
using namespace std;
int main()
{
    int n;//在n的范围之内
    cin>>n;
    for(int k=1;k<=n;k++)//进循环，n次
    {
        if((k*k+k)/2==n)//条件，如果k*k+k/2=n，说明这个数存在。
        {
            cout<<"YES"<<endl;
            return 0;//停程序
        }
    }
    cout<<"NO"<<endl;//如果整个循环结束都没有，就输出NO。
    return 0;
}
```
请为蒟蒻点个赞

---

## 作者：追风少年σχ (赞：0)

### 貌似没什么人写解方程数学做法
 典型的一元二次方程整数根问题 
 
 整理条件式得：
$$  i^2+i-2n=0  $$
 求根判别式：
$$  Δ=8n+1  $$
 下面令p=$ \sqrtΔ$
 
 
 则本题方法如下:
 
 1.枚举p使得 $p^2=8n+1$
 
 2.由于i=$ \frac{p-1}{2} $(负根已舍去）,所以判断p要满足$p\equiv1$ $(mod2)$

代码如下：

```cpp
#include<cstdio>
int main(){
    int n,p,delta;
    scanf("%d",&n);
    delta=8*n+1;//算Δ
    for(p=1;p*p<delta;p++);//枚举p
    if(p*p==delta&&p%2==1)printf("YES");//判断条件
    else printf("NO");
    return 0;
}
```
#### 时间复杂度：O $(\sqrt n)$ ~~轻松~~解决
~~蒟蒻题解求过~~




---

## 作者：开心的猪 (赞：0)

此题由于数据范围太小了，是一道十分难得的打表神题，所以我毫不犹豫地用了打表。打表唯一要注意的就是：**千万别算错了**！！！

以下是代码：

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	if(n==0||n==1||n==3||n==6||n==10||n==15||n==21||n==28||n==36||n==45||n==55||n==66||n==78||n==91||n==105||n==120||n==136||n==153||n==171||n==190||n==210||n==231||n==253||n==276||n==300||n==325||n==351||n==378||n==406||n==435||n==465||n==496)
	{
		printf("YES");
	}
	else
	{
		printf("NO");
	}
	return 0;
}
```


---

## 作者：zzhz (赞：0)

这题不难，直接上代码 （~~已经无力发题解~~）    
代码如下：（~~好像洛谷很久没有审我的题解了~~）
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,i;
bool f=false;
int main(){//主函数
	cin>>n;//输入
	for(i=-3;i<=503;i++){
		if(i*(i+1)/2==n){
			f=true;//判断是否符合条件
		}
	}
	if(f==true)cout<<"YES";//符合，输出YES
	else cout<<"NO";//不符合，输出NO
	return 0;//结束
}

```


---

## 作者：陈灏 (赞：0)

## 写题有五个步骤：
1. 读题，了解题目的意义
1. 在自己的脑海中构思
1. 让代码在电脑上显现
1. 测试自己代码的可靠性
1. 最后，便是令人兴奋地提交了
----------------------------------------------------------------------
### 第一眼看到这道题目，感觉这道题的数据点一定特别大
### 可是……
### 可是等我仔细读完这一道题后
### 发现
### 1<=n<=500
### 原来这么小啊！
### 于是，我们就用一个for循环来解决这一道题吧！
```cpp
for(int i=1;i<=100000;i++)
```
### ~~为了保险，为了	AC   ！~~
### 我们开的大点吧！
-------------------------------------------------------------------------
### 在for循环内我们再加一个判断语句
##  注意：是一个判断语句
```cpp
if(i*(i+1)==n)
{
	cout<<"YES";
	return 0;
}
```
### 这里“return 0”是为了待找到这个数 i 后，
### 直接结束程序！
### 正因如此，
### 不满足时，可以直接在for循环外输出,并结束程序
------------------------------------------------------------------------
--------------------------------------
## 拿出我的 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n;
	long long i=1,o=0;
	cin>>n;
	n=n*2;
	for(int i=1;i<=100000;i++)
	{
		if(i*(i+1)==n)
		{
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
	return 0;
}
```
[**我的博客**](https://www.luogu.org/blog/H-o-r-a-c-e/)

看我题解这么详细，一定要点一个赞！

---

## 作者：pigstd (赞：0)

看到题解很多都是枚举，那我就给一个$O(1)$的方法

对于$n$，若$n*2$=$i*(i+1)$,则令m=$ \sqrt{2*n} $,则i<=m<i+1。如果m$*$(m+1)=n$*$2,那么输出"YES",否则输出"NO"

c++代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;

int main()
{
	cin>>n;
	int m=sqrt(n*2);
	if (m*(m+1)/2==n)
		cout<<"YES";
	else
		cout<<"NO";
	return 0;
}
```

---

## 作者：_Misaka_Mikoto (赞：0)

先写一个验证机，得到i的最大值
```cpp
#include <iostream>
using namespace std;
int main(){
    int n=0,i=0;
    while(n<=500){
        i++;
        n=i*(i+1)/2;
    }
    cout <<i;
    return 0;
}
```
得到i max==32

AC code :[AC](https://www.luogu.org/record/show?rid=14839365)

以下是AC代码
```cpp
#include <iostream>
using namespace std;
int main(){
    int n,num,i;
    bool t=false;
    cin>>n;
    for( i=0;i<35;i++){
        num=i*(i+1)/2;
        if(n==num)t=true; 
    }
    if(t==true)	cout <<"YES";
    else cout<<"NO";
    return 0;
}
```




---

## 作者：Jinyeke (赞：0)

# 第一篇p党大佬的代码可能有点难，所以小蒟蒻送上简单粗暴的代码
###  题目：给定一个数n，问你是否存在一个整数i，满足i*(i+1)/2=n，存在输出"YES",否则输出"NO".### 
   其实就是从i~n一个个枚举下去（不会超时）
然后判断i*(i+1) div 2是否等于n（注意：由于是整数，'/' 应为 'div')

不多说，直接上代码  
```pascal
```pascal

var											 n,i,s:longint；						   
begin
 read(n);  
 for i:=1 to n do 
  if i*(i+1) div 2=n then //判断是否符合条件
     begin
       write('YES');//直接输出
       s:=1;
       break;
     end;//找到就直接退出循环，并标记
  if s=0 then write('NO');//没标记就说明没找到
end.
```


```

---

## 作者：OdtreePrince (赞：0)

# -数论-

对于本题，有很多解法，但本人不喜欢暴枚，因此决定用数论解决该题。

这道题隐藏着高斯求和的数学，只需标记1~i的和，判断n是否在其中即可。

NICER,AK！

~~~
#include<bits/stdc++.h>
using namespace std;
int n,b[5051],sum;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=100;i++){
        sum+=i;
        b[sum]=1;
    }
    if(b[n]) cout<<"YES";
    else cout<<"NO";
    return 0;
}
~~~

---

## 作者：zhuchenzhang (赞：0)

# 其实并不难

[题目连接](https://www.luogu.org/problemnew/show/CF47A)

题面有说n<=500，数字不大，数据很水，直接用for循环枚举就可以了

其实也不用枚举到n的平方根，先~~稍微~~算一下

```cpp
	
    当i等于10时，i*(i+1)/2=55，显然还不够；
    当i等于20时，i*(i+1)/2=210，还少很多；
    当i等于30时，i*(i+1)/2=465，快了；
    当i等于40时，不用算肯定>=500了
    所以，只要枚举i从1~40就可以了
    反正题目没说要浮点型。。。
```
最后附上AC代码：
```cpp
#include <cstdio>//题目不难，用C式读入输出，等同#include <stdio.h>
using namespace std;//启动命名空间。其实也不需要，只有一个头文件，不会出现错误
int main()//主程序不讲了
{
    int n,i;//直接定义要求的数n，和循环变量i，据说可以快一点，避免TLE（超时）
    scanf("%d",&n);//C式读入，注意有&取用n的地址，没有的话会CE（编译错误）
    for(i=0;i<=50;i++)//枚举i的值，从0~50，不过为了以防万一，前面的防超时的方法防止在这里超时
        if(i*(i+1)/2==n)//判定条件，从题面上复制就可以了
        {
            printf("YES");//满足条件，输出答案，C式输出
            return 0;//直接结束整个程序，避免超时和多输出，加快速度
        }
    printf("NO");//不满足条件，输出答案
    return 0;//程序愉快的结束了！！！
}
```

~~本题的71个测试点，AC会被霸屏，绿绿的一大片，就是强迫症会受不了，第7个测试点后面空了一个233~~

$\color{red}\texttt{洛谷万岁！！！}$

---

## 作者：蒟蒻wyx (赞：0)

思路：

i(i+1)/2=n即2n=i^2+2

正数肯定在根号2n前后出现

保险起见，则枚举前后2的范围

考虑sqrt(n*2)-2可能<0 则以三目取之

```cpp
#include<iostream>//上面横清楚了，这里不再叙述
#include<cmath>
using namespace std;
int main(){
    int n;
    cin>>n;
    bool jbk=0;
    for(int i=sqrt(n*2)-2>0?sqrt(n*2)-3:0;i<=sqrt(n*2)+2;i++)//枚举O(5)
        if(i*i+i==n*2)
            jbk=1;
    if(jbk==1)cout<<"YES\n";
    if(jbk==0)cout<<"NO\n";
    return 0;
}
```

---

