# Depression

## 题目描述

在地下室深处躺着数字时钟，显示时间格式为HH：MM。

现在城堡的居民面临着艰巨的任务,**Cogsworth的最初时间是12:00**，他们需要**向右转动**Cogsworth的时针和分针，直到Cogsworth显示正确的时间。**所以，他们需要找到时针和分针顺时针旋转的角度。**

Cogsworth的时针和分针均匀且连续地移动。时针和分针独立移动，所以当转动另一只针时另一只针仍然静止不动。

22：00与10：00旋转角度是相同的

## 样例 #1

### 输入

```
12:00
```

### 输出

```
0 0```

## 样例 #2

### 输入

```
04:30
```

### 输出

```
135 180```

## 样例 #3

### 输入

```
08:17
```

### 输出

```
248.5 102```

# 题解

## 作者：maomao233 (赞：1)

### 题意
给定一个时间，求从 $12:00$ 到这个时间时针和分针都分别转了多少度。

### 分析

- 由于这题输入时会带有冒号，所以推荐大家熟用格式化输入。在使用 `scanf` 时这样表达： `"%d:%d"` ，这样系统在输入的时候就会忽略这个字符，省的我们再去新建一个变量输入了。

- 考虑到钟表只会表示 $12$ 个小时，所以输入 $12:00$ 和 $00:00$ 的结果是一样的。我们要按照 $00:00$ 的答案考虑，所以在输入的时候要判断如果小时大于 $12$ 就 $\bmod 12$ 。或者直接取余也行。

- 接下来推导结果：

  由于按照小时来算太麻烦，我们按照分钟来算。那距离 $12:00$ 过的时间就是 $h \times 60 + m$ 。当时针在钟上转了一整圈时已经过去了 $60 \times 12 = 720$ 分钟，而整个钟是 $360^\circ$ ，所以时针 $1$ 分钟就可以转 $360 \div 720 = 0.5^\circ$ ，所以最后再乘上 $0.5$ 即可。
  
  分针的角度就简单了，一小时 $60$ 分钟，那第 $m$ 分钟就占了整个钟的 $\dfrac{m}{60}$ ，整个钟 $360^\circ$ ，那么公式就是 $360^\circ \times \dfrac{m}{60}$ 。再把 $360$ 和 $60$ 一约分，答案就变成了 $6m$ 。
  
  所以最终的答案为 $( h \times 60 + m ) \times 0.5$ 和 $m \times 6$ 。


------------

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int HH,MM;
    scanf("%d:%d",&HH,&MM);
    HH%=12;
    cout<<(double)(HH*60+MM)*0.5<<" "<<MM*6<<endl;
    return 0;
}
```


---

## 作者：708151_qwq (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/CF80B)

***

前置芝士：

很多人保留小数位数输出的时候都会用 `printf`，就像这样：

```cpp
printf("%.5lf", a);
```

但其实 `cout` 也可以，~~就是有点麻烦~~，具体用法：

```cpp
cout << fixed << setprecision(位数) << a;
```

头文件 `#include <iomanip>`。

***

简要题意：

给定时间 `HH:MM`，求出时针和分针从初始时间 $12:00$ 转到给定时间各自要转多少度，保留一位小数输出。

***

题目分析与解法：

此题坑点：以十二个小时（时针转一圈）为周期计算，即 $13:00$ 和 $1:00$ 是一样的。

首先，时针要转的度数就是总共与 $12:00$ 相差的分钟数取模时针转一圈的分钟数**的结果**乘以一分钟时针转的度数，即 $(h \cdot 60+m)\bmod (60 \times 12) \times [360 \div (60 \times 12)]$ 度，化简之后为 $[(h \cdot 60+m) \bmod 720] \times 0.5$ 度。

然后，分针要转的度数就是 $m \times (360 \div 60)$，即 $m \times 6$ 度。

算好之后，保留一位小数输出就行了。

***

$\text{Coding Time}$！

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int h, m;
	char c;
	cin >> h >> c >> m;
	cout << fixed << setprecision(1) << (((h*60)+m)%720)*0.5 << " ";//防止意外，多加几层括号
	cout << m*6 << endl;
	return 0;
}
```

劝君切莫抄题解，棕名封号两行泪。

---

## 作者：Level_Down (赞：1)

### 题意简述：

给定一个时间，求时钟上分针和时针距 $00:00$ 走过的度数。

### 方法：

首先求时针转过的度数，可以分为大格 $(30\degree)$ 的度数和小格 $(6\degree)$ 的度数。

众所周知，$00:00$ 后每过一个完整的一小时时针走一大格，除此之外每十二分钟走一小格，所以如果设现在的时间为 $n:m$，我们可以得知时针走过的角度为 $(n \bmod 12) \times 30 + m / 2$。

另外上面这个式子中 $n \bmod 12$ 是因为 $12:00$ 时也是 $00:00$ 。

我们还可以知道，每过一分钟分针会走一小格，所以分针走过的角度为 $m \times 60$。

代码：

```cpp
#include <bits/stdc++.h>  
using namespace std; 
int a,b;
char t; 
int main()
{
	cin >> a >> t >> b;
	cout << (double)((a % 12) * 30 + (b / 2.0)) << " " << b * 6;
	return 0;	
} 
```


---

## 作者：monstersqwq (赞：1)

写篇和之前几篇不一样的吧~~

输入 $h,m$（记得最好使用 scanf 吞字符），然后换算成 $s$ 分钟，$s \gets 60*h+m$。

分针：60分钟360度，即1分钟6度，$y \gets (s \bmod 60) \times 6$。（其实 $s \bmod 60$ 和 $m$ 也没区别）

时针：$60 \times 12=720$分钟转360度，即1分钟0.5度，$x \gets (s \bmod 720) \times 0.5$。（使用 double 类型保留一位小数）

输出 $x,y$ 即可。

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
int main()
{
	int h,m,s;
	scanf("%d:%d",&h,&m);
	s=60*h+m;
	int y=(s%60)*6;
	double x=((s%720)*1.0)*0.5;
	printf("%.1lf %d\n",x,y);
	return 0;
}
```



---

## 作者：Leaves_xw (赞：0)

**题目大意：**

有一个时钟，显示时间格式为 $HH:MM$。

现在需要求出，自 $00:00$ 时起，时针和分针各转了多少度。

**思路：**

我们知道，时针一小时转 $30$°,分针一小时转 $360$°，时针每分钟转 $0.5$°,分针每分钟转 $6$°。

所以，我们可以得出，在 $HH:MM$ 时，时针走过的度数为：$(HH$ $mod$ $12$$) \times 30+\Large\frac{MM}{2.0}$，分针走过的度数为：$MM \times 6$。

**清晰明了的代码：**

```
#include<bits/stdc++.h>
using namespace std;

int main()
{
   int HH,MM;
   char x;
   cin>>HH>>x>>MM;//输入
   cout<<double((HH%12)*30+MM/2.0)<<" "<<MM*6<<endl;//公式
   return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

（一）

1.读入一个字符串。

2.将“时”和“分”分别提取，定义为 $h$ 和 $m$ 。

3.总分钟数 $time=( h \times 60+m ) \bmod 720$ 。

4.

时针：

时钟上一圈有 $12$ 小时，合 $720$ 分钟。

所以时针的夹角为 $time \div 720 \times 360 = time \div 2$。

分针：

时钟上一圈 $60$ 分钟。

所以分针的夹角为 $m \div 60 \times 360=m\times 6$。

（二）

AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string st;
	cin>>st;
	int h=(st[0]-'0')*10+(st[1]-'0');//小时数
	int m=(st[3]-'0')*10+(st[4]-'0');//分钟数
	int time=(h*60+m)%720;//总分钟数
	cout<<time/2.0<<" "<<m*6;//可以直接输出
	return 0;
}
```



---

## 作者：sto_yyrdxh_orz (赞：0)

### 题目大意：
输入小时 $h$ 中间隔一个字符 `:` 再输入分钟分钟 $m$，问你从凌晨 $0$ 点开始，时针走了多少度？分针走了多少度？

### 题目分析：
其实 $0$ 点就是 $12$ 点，所以我们可以判断一下 $h$ 和 $m$ 是否分别等于 $12$ 和 $0$，如果等于，输出两个 $0$，否则进行如下操作。

1.一个圆有 $360^\circ $，那么每一分钟就是 $360÷6$ 也就是 $60^\circ$，所以第二个数我们只需要乘 $6$ 并输出即可，接下来就剩下第一个数了。

2.钟表上一共有 $12$ 个大格，并且一格是 $60$ 分钟，所以用 $60×12$ 也就是 $720$，接下来我们再用 $360÷720=0.5$，说明 $1$ 分钟可以转 $0.5^\circ $。所以第一个数字就等于 $(60×h+m \bmod 720)×0.5$。

### 具体代码：
```cpp
#include <iostream>
using namespace std;
int h, m;
char c;
int main(){
	cin>>h>>c>>m;
    //输入
	if(h==12&&m==00){
    //特判
		cout<<"0:0";
		return 0;
	}
	int a=(60*h+m%720);
    //分析出来的公式
	cout<<double(a*0.5)<<" "<<m*6;
    //输出
	return 0;
}
```

---

## 作者：小杨小小杨 (赞：0)

## 题意
给以一个时钟，问你从 $0$ 时开始，到现在的时间，时针走了多少度，分针走了多少度？（独立旋转）
## 思路
陷阱：当时间大于 $12:00$ 时，比如 $13:00$，其实是和 $1:00$ 一样的。    
### 思路一：    
暴力出奇迹。    
一分钟一分钟地累加，每一分钟分针会旋转 $30 \div 5 = 6$ 度，时针会旋转 $30 \div 60 = 0.5$ 度。当时针一圈转完时，时针要走的距离归零。   
### 思路二：
数学方法。   
因为时针每小时旋转 $30$ 度，每分钟旋转 $30 \div 60 = 0.5$ 度，所以时针一共旋转了每小时的度数加上零散的分钟的度数。而分针每分钟旋转 $30 \div 5 = 6$ 度，所以就直接乘一下就行了。
## Code
### Code 1
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,minute,hour;
double degree_hour,degree_minute;
int main(){
	scanf("%d:%d",&n,&m);//读入
	if (n>=12) n-=12;//特判
	hour=0;minute=0;//初始化
	while (hour<n||minute<m){
		minute++;degree_hour+=0.5;degree_minute+=6.0;//暴力
		if (minute>=60) hour++,minute=0,degree_minute=0;//归零
	}
	cout<<degree_hour<<' '<<degree_minute;//输出

```

### Code 2
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main{
	scanf("%d:%d",&n,&m);//读入
	if (n>=12) n-=12;//特判
	double minute=m*6.0;//分针角度
	double hour=n*30.0+m*0.5;//时针角度
	cout<<hour<<' '<<minute;//输出
	return 0;
}
```



---

## 作者：Eason_AC (赞：0)

## Content
有一个时针，给定时间为 $\text{HH}$ 时 $\text{MM}$ 分，求图中 $\alpha$ 和 $\beta$ 角的值。

![](https://cdn.luogu.com.cn/upload/image_hosting/3ksc1q99.png)

手画勿喷/kk

**数据范围：$0\leqslant\text{HH}\leqslant23,0\leqslant\text{MM}\leqslant59$。**
## Solution
答案很明显可以手推出来。

首先，小时数 $\geqslant12$ 的要减去 $12$，因为这样才是对于时钟上面显示的样子。不过在代码中也可以用 $\text{HH}\leftarrow\text{HH}\mod12$ 来表示。

又我们知道，一小时内，时针转 $30$ 度，一分钟内，时针转 $0.5$ 度，分针转 $6$ 度。

所以，答案就是 $30\times(\text{HH}\mod12+\dfrac{\text{MM}}{60}),6\times\text{MM}$。
## Code
别试了，不和样例一模一样，但答案保证是对的。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int h, m;

int main() {
	scanf("%d:%d", &h, &m);
	printf("%.1lf %d\n", ((h % 12) + m / 60.0) * 30, m * 6);
}
```

---

## 作者：xiaohuang (赞：0)

### 分析

首先我们可以确定分针的偏转角度为$m \times 6$（它不受时针影响）。

时针的话可以先算出自己因整小时影响的偏转角度为$n \times 30$，然后再加上分针的影响为$m \times 0.5$，即偏转角度为$n \times 30 + m \times 0.5$。

当时间超过半天（`12:00`）时，要把小时数减去$12$（也就是时针已经转了一圈，角度从$0$开始）。

输出的时候注意一下就好了。

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

int n, m;
int main() {
    scanf("%d:%d", &n, &m);
    if (n >= 12) n -= 12;
    double ans1 = n * 30 + m * 0.5;//计算时针偏转角度
    int ans2 = m * 6;//计算分针偏转角度
    if ((int)ans1 == ans1) printf("%.0lf %d\n", ans1, ans2); else printf("%.1lf %d\n", ans1, ans2);//注意输出
    return 0;
}
```

---

## 作者：lby2006 (赞：0)

首先我们要知道分针转一格是6度，同时时针转0.5度，每过1小时时针转30度。

所以时针共转30*h+0.5*m度，分针共转6*m度。

下面是代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
double ans1,ans2;
double h,m;
const int SIZE=1<<20;
inline char getch()
{
    static char buf[SIZE],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++;
}//手动getchar()
inline int rd()
{
	int x=0,f=1;
    char ch=getch();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getch();}
    while(ch<='0'&&ch>='9'){x=x*10-48+ch;ch=getch();}
    return x*f;
}//快读(可以避免中间的：的读入错误)
int main()
{
    h=rd();
    m=rd();
    if(h>=12)h=h-12;//因为若两时间相差12小时，则他们其实是一样的。
    ans2=6.0*m;//和上面文字解释一样
    ans1=30.0*h+0.5*m;//同上
    printf("%lf %lf\n",ans1,ans2);//输出
    return 0;//好习惯
}
```



---

## 作者：　　　吾皇 (赞：0)

### 题目分析
```
由于本题是从12:00开始顺时针旋转时针和分针，所以22：00与10:00是近似相等的，如果小时数大于等于12则减去，在读入时可以用scanf略去多余的‘：’，也可以cin>>a>>x>>b，x为char变量。在计算时直接计算时针和分针对应的角度即可。
```
### 时钟上针角度的计算
```
因为一个钟有360°，分针60分钟走一圈，所以一分钟对应6°；同时时针12小时走一圈，一小时对应30°，所以对于一个时间a:b，a的前面会有30a°，而一小时的30°同样对应60分钟，所以时针走的度数为（30a+b/2）。注意在c++中计算时应为b/2.0，不能直接整除
``` 
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int a,b;
char x;
int main(){
	cin>>a>>x>>b;//方便的读入
	if(a>=12) a-=12;//因为a:b与(a+12):b是对等的，在下面a太大会增大答案，所以要减去（a<=12）
	cout<<(b/2.0+a*30)<<" "<<6*b;//这里除以2.0是为了保留小数位防止整除导致答案有偏离
}
```


---

