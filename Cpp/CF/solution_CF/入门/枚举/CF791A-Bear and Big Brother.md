# Bear and Big Brother

## 题目描述

**题意翻译**

给定两个数 $a, b$，每个单位时间中，$a \leftarrow a \times 3,b\leftarrow b\times 2$，求在第多少个单位时间时，$a>b$。

## 说明/提示

对于 $100\%$ 的数据，$1\le a,b\le 10$。

**样例一解释**

第一个单位时间后，$a=4\times 3=12,b=7\times 2=14,a<b$；

第二个单位时间后，$a=12\times 3=36,b=14\times 2=28,a>b$，此时，已满足题目要求，输出 $2$。

**样例二解释**

第一个单位时间后，$a=4\times 3=12,b=9\times 2=18, a<b$；

第二个单位时间后，$a=12\times 3=36,b=18\times 2=36,a=b$；

第三个单位时间后，$a=36\times 3=108,b=36\times 2=72,a<b$，此时，已满足题目要求，输出 $3$。

**样例三解释**

第一个单位时间后，$a=1\times3=3,b=1\times2=2,a<b$，此时，已满足题目要求，输出 $1$。

Translate By @[159号程序员](https://www.luogu.com.cn/user/334586)

## 样例 #1

### 输入

```
4 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 9
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 1
```

### 输出

```
1
```

# 题解

## 作者：珅肐 (赞：9)

#### 来一篇$O(1)$的题解

题目可以转化为求最小的$x$使得下式成立。

$$a*3^x>b*2^x$$

继续转化

$$\frac{3^x}{2^x}>\frac{b}{a}$$

即：

$$(\frac{3}{2})^x>\frac{b}{a}$$

那么如何求最小的$x$呢?

可以先求

$$(\frac{3}{2})^x=\frac{b}{a}$$

这里的$x$就是$log_{\frac 32}\frac ba$

我们只要向下取整再加上$1$就好啦

还有一个问题：$c$++没有$log_{\frac 32}$怎么办?

没关系！换底公式 , 出现！

$$log_n m=\frac{log_a m}{log_a n}$$

这时就可以用$c$++自带的$log$函数啦（应该是以$e$为底的）

在$cmath$库里哦！
### 代码奉上！
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int a,b;cin>>a>>b;
    double n=1.5,m=1.0*b/a;
    cout<<int(log(m)/log(n))+1;//这里就是上面说的啦
    return 0;//好习惯
}//真的很短哦
```


---

## 作者：一滴小水滴 (赞：3)

这个题目很简单的，但是一楼为什么写的那么复杂咱也不知道咱也不敢问呐，这道题的数据范围这么小完全不需要这样写啊。直接每次更新体重就可以啦。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,ans=0;
int main()
{
	cin>>a>>b;
	while(a<=b)
	{
		a*=3;
		b*=2;
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Ca2ng (赞：1)

开始说点什么好呢

# ~~并没有什么~~**思路**
1. 先定义和输入变量 a,b  
1. 跑循环鸭
1. 按照题意跑循环（这题数据足够小不会超的^__^ ）
1. 判断若a>b就输出就完事

好了我人狠话不多  
# 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b;//a,b见题面
	cin>>a>>b;
	for(int i=0;;i++)
	{
		a=a*3;
		b=b*2;
		if(a>b)
		{
			cout<<i+1;//因为循环是从0开始哒
			return 0;//一定要加鸭
		}
	}
	return 0;
}
```



---

## 作者：sunchenyi (赞：0)

又是一篇没有P党题解的题啊！！

为了造福于P党（哈哈哈~突然觉得自己好伟大）

真的不是我吐槽，这道题目是真的好水啊，名副其实的大水题

（管理员别揍我~~）哈哈

题意其实很明白

利马克每年的体重翻三倍

鲍勃每年的体重翻两倍

这样一来，代码就很容易了

```pascal
var a,b,s:longint;
begin
  readln(a,b);//读入初始体重，a代表利马克，b代表鲍勃
  while a<=b do//只要a<b就不停执行
  begin
    inc(s);//累计年数
    a:=a*3;//a翻三倍
    b:=b*2;
  end;
  writeln(s);
end.
```

完工！！

请勿抄袭~

求给过QAQ~


---

## 作者：TCZN (赞：0)

# 蒟蒻的第一篇题解
 一道小水题，上代码：
  ```
  var
  a,b,s,i:longint;
begin
 read(a,b);
  while true do //死循环
   begin
    s:=s+1; //过了几年
     a:=a*3; //Limak的体重
      b:=b*2; //Bob的体重
       if a>b then //如果Limak比Bob重就输出过了几年
        begin
         writeln(s);
         halt; //结束程序
        end;
   end;
end.
```


---

## 作者：rui_er (赞：0)

这一题是一个模拟算法。

我采用递归的方式解题。

# 头文件

没有什么特殊的。

```cpp
#include <iostream>
```

# 主函数

> 在主函数中只需要以下几件事：

1. 输入
2. 跑一遍递归函数
3. 输出

```cpp
int main()
{
	int a, b;
	cin>>a>>b;
	cout<<f(a, b)<<endl;
	return 0;
}
```

可见递归函数是程序重点。

# 递归函数

首先，声明函数，一定要在main前面！！！```int f(int a, int b);```

其次，在后面写函数。

- 如果已经满足条件（第一个数比第二个数大），则return 0。
- 否则次数加1，模拟下一年。这里次数就是返回值。

```cpp
int f(int a, int b)
{
	if(a > b) return 0;
	else return 1 + f(3*a, 2*b);
}
```

# 汇总

最后，把前面所有的合起来，得到：

```cpp
#include <iostream>
using namespace std;

int f(int a, int b);

int main()
{
	int a, b;
	cin>>a>>b;
	cout<<f(a, b)<<endl;
	return 0;
}

int f(int a, int b)
{
	if(a > b) return 0;
	else return 1 + f(3*a, 2*b);
}

```

---

## 作者：土川崇贺 (赞：0)

    	水题，直接看代码：
```
#include<iostream>
using namespace std;
int main()
{
    long long a,b,c=0;
    cin>>a>>b;
    while(a<=b)
    {
    	a*=3;
    	b*=2;
    	c++;
	}
	cout<<c;
	return 0;
}

```

---

## 作者：不到前10不改名 (赞：0)

```
#include<stdio.h>
int srx,sry,i;//数据还是水啊！（只要是再大一点，到100就会溢出，1000longlong也救不了你）
int main()
{
    scanf("%d%d",&srx,&sry);
    while(srx<=sry)//很明显while循环判断是否越界
    {i++;//几年后Limak会变得比Bob更大(更重)
    srx*=3;
    sry*=2;}//其实也可以看做srx*=1.5，不过这题水
    printf("%d",i);
    return 0;
}
```

---

## 作者：agicy (赞：0)

# 思路

因为是水题，所以纯模拟就可以了。

# 代码

代码如下。

```cpp
#include<stdio.h>//头文件

int a,b;

int main(void){
	register int i;//寄存器更快些
	scanf("%d%d",&a,&b);//读入
	for(i=1;;i++){//暴力模拟
		a*=3,b*=2;
		if(a>b)//如果满足条件
			return printf("%d\n",i),0;//输出并结束
	}
	return 0;
}
```

## [我的测评记录](https://www.luogu.org/recordnew/show/9186972)

### 一件奇怪的事情：

我的程序的耗时/内存：$707ms,0KB$。（$0KB$是为什么？）

---

## 作者：xdc呀 (赞：0)


想法
------------

看见这题，最先想到while语句来做，while的判断条件是Limak比Bob轻或等于的时候就执行.  
再去看体重的变化规律：Limak吃了很多，他的体重在每年之后翻了三倍，而Bob的体重在每年之后翻了一倍。
那再while中完成体重变化规律。再取一个变量，用于统计年份。





AC代码
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,year;
int main()
{
scanf("%d %d",&a,&b);//	输入
while(a<=b)
{
	a*=3;
	b*=2;
	year++;
}
printf("%d",year);
}
```


---

## 作者：emm··· (赞：0)

这道题可以不用while再弄一个ans存储过了的年份。还可以这样：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    for(int i=1;i<=100000;i++)//可以直接用i代表过了的时间
    {
        a=a*3;//翻三倍就是*3
        b=b*2;//翻番就是二倍
        if(a>b)
		{
			printf("%d",i);//直接输出i
			return 0;//也可以打成break
		} 
    }
    return 0;
}
```


---

## 作者：Ace_Radom (赞：0)

## 这题竟然卡了我半个小时……

注意题中范围：
	
    The only line of the input contains two integers a and b 
    ( 1<=a<=b<=10 1<=a<=b<=10 )
    
就是说，a在一开始**不会大于b**！

因此，不用在开始把ans赋1！

Code：【我喜欢模块化的程序，~~凑合着吧~~】

模块化有啥不好？分块查错，调试

```
#include<bits/stdc++.h>
using namespace std;
int ans;  //全局变量默认为0
void Pss( int n , int m ){  //模块
	while ( n <= m )  //等于不要忘，是比Bob肥
	{
		n *= 3;
		m *= 2;
		ans++;
	}
	return;  //这个爱打不打
}
int main(){
	int n,m;
	cin >> n >> m;
	Pss( n , m );
	cout << ans;
	return 0;  //结束
}
```

---

