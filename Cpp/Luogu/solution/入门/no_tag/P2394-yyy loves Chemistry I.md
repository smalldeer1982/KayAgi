# yyy loves Chemistry I

## 题目背景

从前，有个人叫 yyy，他特别喜欢化学，尤其是一些很危（zuo）险（si）的实验。

这一天，他开始研究起了一个神奇又有趣的方程式：

$\text{2Na + 2H}_{2}\text{O == 2NaOH + H}_2\uparrow$

## 题目描述

现在 yyy 将一块质量为 $x\ \text{g}$ 的钠投入很多（过量）的水中，然后开始收集氢气。

最终，我们知道，这块钠在水中游动着消失了。而 yyy 很厉害，把氢气全收集起来了。

**已知每投入 $\bm{23}$ 克的钠，就会生成 $\bm1$ 克的氢气。**

那么现在 yyy 收集了多少克氢气呢？

**形式化题意：输入一个实数 $\bm x$，输出 $\bm{\frac{x}{23}}$ 的前 $\bm8$ 位小数值，要求四舍五入。**

## 说明/提示

### 数据规模与约定

对于 $100\%$ 的数据，满足 $0<x\le1$。

### 提示

你想知道 $x$ 有几位小数吗？才不给你呢>\_<  
kkksc：没有数据范围怎么行！输入文件不超过 $5\text M$！  
出题人：怎么能这样！差评！我不好挖坑了！

### 警告

**请注意，题目中描述的实验具有很大风险，请勿轻易尝试：活泼金属 $\bold{Na}$ 存在安全隐患、$\bold{NaOH}$ 具有强烈的腐蚀性、$\bold{NaOH}$ 溶解于水时会放出大量热量。**

## 样例 #1

### 输入

```
0.23```

### 输出

```
0.01000000```

# 题解

## 作者：Red_Alert_star (赞：163)

重要的事情说三遍，小数的精度！小数的精度！小数的精度！
------------
这道题用cin的话你就凉了，long double也回天乏力。
用cin，80分，上代码：
```
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	long double s;//确保精度 
	cin>>s;
	s=s/23; 
	printf("%.8Lf",s);//"%.8Lf"意思是将一个long double变量s保留8位后输出 
}

```
输入文件不超过5M......![QQ截图20190806132708.png](C:\Users\Administrator\Desktop\QQ截图20190806132708.png)
很明显，**精度**不够

正当本蒟蒻不出来问题的时候，本蒟蒻突然想起scanf可以强制提高精度，于是......
```
#include<cstdio>
int main()
{
	long double s;
	scanf("%15Lf",&s);
    s=s/23;
	printf("%.8Lf",s);
}
```
AC了
点个赞再走啊~~~

---

## 作者：Heartlessly (赞：93)

第一次看此题时觉得十分简单，就用 long double 读入，结果只有 80 分。后来才发现这题 long double 的精度是完全不够的，所以可以采用c语言的读入使精度变高。

- ### 各种类型浮点数的精度：

- float:6~7位;

- double:15~16位;

- long double:18~19位。

当然也可以采用字符串的读入，但是不能够全部读完，楼下也有解释。

## 附上AC代码：

```cpp
#include <cstdio>
int main(){
    long double x;
    scanf ( "%15Lf", &x );//强制提高精度
    printf ( "%.8Lf", x / 23 );//输出保留8位小数
    return 0;
}
```

---

## 作者：樱初音斗橡皮 (赞：23)

为什么各位大佬都喜欢用普通的scanf和printf几行解决呢？QWQ

本蒟蒻认为，由于在试炼场快读里面，似乎用快读更好~~其实因为我不太会使用scanf QWQ~~看见题解没有快读就来写一个

和yyy loves maths II一样，不要把东西放到小数部分里面；为了四舍五入，最好取8位读（第九位以后的对于计算结果没有帮助）（本蒟蒻保险取了九位）。对1进行特判。

很简单，但是坑挺多，某些部分具体见代码，代码如下：

```
#include <iostream>
#include <cstdio>
using std::scanf;
using std::printf;
int x;
char c;
int len(int a) //返回数的长度
{
	if (a==0)
		return 1;
	int ans=0;
	while (a)
	{
		++ans;
		a/=10;
	}
	return ans;
}
int main()
{
    if ((c=getchar())=='1') //特判
    {
    	long double y=1;
		printf("%.8Lf", y/23);
    	return 0;
    }
    getchar();
    bool flg=false;
    for (int i=1; i<=9; ++i)
	{
		if (!flg)
			c=getchar();
		if (c>'9'||c<'0')
			x*=10, flg=true;
		else
			x=(x<<3)+(x<<1)+c-'0';
	}
	x=(x/23+5)/10; //四舍五入
	putchar('0');
	putchar('.');
	int length=len(x);
	for (int i=1; i<=8-len(x); ++i) //补上前导零
		putchar('0');
	printf("%d\n", x);
	return 0;
}

```


---

## 作者：_Int_ (赞：16)

--------------------经历分割线-----------------

N次，输入输出的Lf打成了lf

--------------------思路分割线-----------------

精度！精度！精度！重要的事情说三遍！！！

--------------------废话分割线-----------------

上代码~

别抄，毕竟楼下还有代码~

有木有一种卷轴的感觉~

强迫症请理解

--------------------代码分割线-----------------

```cpp
==========================|
# include < cstdio >      |
# include < iostream >    |
using namespace std;      |
int main(){               |
    long double a;        |
    scanf("%15Lf",&a);    |
    printf("%.8Lf",a/23); |
    return 0;             |
}                         |
==========================|
```
--------------------结束分割线-----------------

---

## 作者：远航之曲 (赞：14)

思路：读到字符串中（读16位，要不存不下），直接用ssanf转成一个long double，除23再输出


```cpp
#include <bits/stdc++.h>
using namespace std;
char s[20];
long double x;
main(){
    for(int i=0;i<15;i++) 
        scanf("%c",s+i);        //读入s表示数字的位数 
    s[15] = '\0';                //将末尾置零
    sscanf(s, "%Lf", &x);        //转为double 
    printf("%.8Lf\n",x/23);       
}
```

---

## 作者：life_w_back (赞：5)

```
注意。。。
精度，精度，精度
#include<iostream>
#include<cstdio>
int main(){
    long double n,x;//long double精度为15~18位
    scanf("%18Lf",&n);//强制提高精度。
    printf("%0.8Lf",n/23);//输出保留八位小数。
    return 0;
}
```

---

## 作者：lqylqylqy (赞：4)

这道题考的是读入,切记要一位一位的读进来然后累加.

注意：

1.数据类型要开double

2.前面两位可忽略,但小数点前是“1”记得特判

3.权变量从第三位起每次自乘0.1


```delphi


var i:longint;
    ans,f:double;
    c:char;
begin
  ans:=0;
  read(c);
  if c='1'then ans:=1;//特判
  read(c);
  f:=1;
  {因为数据范围在0<n<=1,因此最前面的"0"和"."可以忽略}
  for i:=1 to 15 do
    begin
      read(c);
      if(c>='0')and(c<='9')then
        begin
          f:=f*0.1;//当前这一位的权
          ans:=ans+(ord(c)-ord('0'))*f;{权乘数}
          //一位一位累加
        end;
    end;
  writeln(ans/23:0:8);
  readln;
  readln;
end.              


```

---

## 作者：林家三少 (赞：3)

相关题目：[yyy系列](https://www.luogu.org/problem/P2393)(好像没啥意义

注意：

 $$\colorbox{black}{\color{black}精度！！！精度！！！精度！！！} $$ 
 
~~(选中试试~~

代码也是非常的简单易懂，所以我就不多讲了

直接上：

```cpp
#include<cstdio>
using namespace std;
long double Administrators_is_so_cool;//翻译：Administrators是管理员
int main()
{
    scanf("%15Lf",&Administrators_is_so_cool);  //输入
    printf("%.8Lf\n",Administrators_is_so_cool/23);  //然后输出
    return 0;  //再然后一道题就A啦！
}
```
~~(求过~~

---

## 作者：MC方块人 (赞：3)

# 这题是真的坑
## 看我旁边的童鞋（~~这是我和他合力写的题解~~）：
### 第一次看到要保留8位小数，用printf输出，cin输入。
### 结果：不知问题出在哪了，~~一口老血~~
### 我建议他：用scanf
### 第二次用scanf输入，printf输出。
### 结果：忘记调精度，~~又一口老血~~
### 二人面面相觑，~~二脸懵逼~~
### 感谢某大佬的指点，~~使我二人脱离苦海~~
## AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long double x;
	scanf("%15Lf",&x);//注意这里特殊写法
	printf("%.8Lf",x/23.0);//写成23也可以
	return 0;
}
```


---

## 作者：编程萌新or大神 (赞：2)

# ~~此题思路明了~~
## 但是需要注意一些问题--在代码中有···



代码如下··


```
#include <iostream>
#include <cstdio
#include <cstring>
#include <cmath>
#include <algorithm>//头文件要打全 
long double x;//long double精度约18-19位 
using namespace std;
int main()
{
    scanf ( "%15Lf", &x );
    printf ( "%.8Lf", x/23 );//依据题意 （并且大写L） 
    return 0;
}
```


---

## 作者：brealid (赞：2)

精度什么的问题就不细说了，``long double`` + ``%Lf``必备精度利器。

介绍一下 ``sscanf``

``sscanf(const char *buf, const char *format, ...)``

``scanf``从输入缓存读入数据，而``sscanf``从指定的字符数组``buf``（第一个参数）里读取数据，第二个参数及往后跟``scanf``的用法一样。

还有一个高招：用``scanf``从输入缓存里读入一定长度的字符串``%30s``

### code
```cpp
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
    char buf[37];
    scanf("%30s", buf);
    long double a;
    sscanf(buf, "%17Lf", &a);
    printf("%.8Lf", a / 23.0);
}
```

---

## 作者：Isprime (赞：2)

### 重要的事情说三遍
# 精度！
# 精度！！
# 精度！！！


------------
本蒟蒻一看到这题觉得简单到爆！
~~谁乱评分普及+/提高？~~

然后便开始写代码

上~~80分~~代码

------------

```cpp
#include<cstdio>
using namespace std;
int main()
{
	long double a;
    scanf("%Lf",&a);
    printf("%.8Lf\n",a/23);
    return 0;
}
```
------------
~~别抄，因为这是错的~~

这才发现long double精度完全不够

好吧，我记得scanf可以强制提高精度

然后就AC了

### 下附AC代码 ###


------------
```cpp
#include<cstdio>
using namespace std;
int main()
{
	long double a;
    scanf("%15Lf",&a);//强制提高精度
    //long double是Lf!Lf!!Lf!!!
    printf("%.8Lf\n",a/23);//输出保留8位小数
    return 0;
}
```


------------

---

## 作者：Legendword (赞：1)

##### 没有人按位读入+高精度，所以我来写一个～

本苣蒻最开始也是用 double ，80分...

然后我 ~~灵机一动~~ 可以读入到数组里高精度计算啊

没错，就是~~手写竖式进行除法运算~~


------------


需要注意的几点：

- 由于输入是0<x<=1，所以只需要除小数点后的数就行

- 但是需要特判1的情况

- 算结果的时候要多算一位，用于四舍五入

- 四舍五入不要忘记考虑进位的情况！

- 输出的时候不要忘记先输出0.再输出那8位小数

### **这道题并没有说明小数位有多少，所以用高精度是最保险的。即使位数特别多我们也不慌**

##### 以下是完整代码

------------




```cpp
#include<bits/stdc++.h>
using namespace std;
vector<short> a,t;
short d = 0;
int main(){
	char c = getchar(); //读入整数位
	if (c=='1'){ //特判1的情况
		cout<<"0.04347826";
		return 0;
	}
	c = getchar(); //读入小数点
	c = getchar(); //开始读入小数位
	while (c>='0'&&c<='9'){
		a.push_back(short(c-'0')); //将原数存入向量a
		c = getchar();
	}
	vector<short>::iterator i = a.begin();
	bool gozero = false;
	short f = 0; //f为竖式里当前的被除数
	while (d<9){ //d用来记录竖式顶上（算好的）位数
		if (i==a.end()){ //如果原数到头了，开始补0
			gozero = true;
			++i;
			continue;
		}
		f *= 10;
		if (!gozero) f += *i; //如果没有开始补0，就把原数里的当前位加到f里
		if (f<23) { //竖式原理，加位加到能被23除
			t.push_back(0); //竖式顶上加0
			++i; //原数下一位
			d++;
			continue;
		}
		short dv = f/23; //竖式顶上写的那个数
		f -= dv*23;
		t.push_back(dv);
		++i;
		d++;
	}
	cout<<"0."; //别忘输出0和小数点～
    //更别忘四舍五入最后一位（我最开始忘了，50分）
    //之前算9位结果就是因为第9位要用来四舍五入
	short p = t.back(); //取出第9位
	t.pop_back();
	if (p>=5){ //如果需要四舍五入
		p = t.back(); //取出第8位
		t.pop_back();
		p += 1;
		while (p>9){ //如果四舍五入后到10了，则需要进位
			p = t.back();
			t.pop_back();
			p += 1;
		}
		t.push_back(p);
		while (t.size()<8){ //如果进位了就需要补0到第8位
			t.push_back(0);
		}
	}
	for (auto g:t) cout<<g; //输出8位小数，完结散花！
	return 0;
}

```

苣蒻第一次写题解，不到位的地方请大家谅解！

---

## 作者：panyueyang (赞：0)

这道题很~~不~~简单。
##
## 第一次改良
我一看，就立刻打
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
double a;
cin>>a;
printf("%.8lf",a/23);
}
```
##
## 第二次改良
小数精度不够吗？？？
将`cin>>a`改成了`scanf`

![](panyueyang.ueuo.com/pic/book3pic1.png)

 ~~不想告诉你是80分~~
 
这时代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
double a;
scanf("%8lf",&a);
printf("%.8lf",a/23);
}
```
##
## 终级代码 ~~失败~~

原来小数精度还不够~~~~
接着将`double`改成`long double`
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
long double a;
scanf("%50lf",&a);
printf("%.8lf",a/23);
}
```
天算地算不如人算……
居然忘了`long double`应该配`Lf`不是`lf`……

所以加上，还是很美好
##
## ~~不是~~AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
long double a;
scanf("%50Lf",&a);
printf("%.8Lf",a/23);
}
```

---

## 作者：JimmyF (赞：0)

    
### 这题必须注意小数的精度！如果你用cin就凉得透透的了，自然会 稻花香里说丰年，听取WA声一片。

所以，我们唯有将小数精度提高才能够AC，可以采用c++语言的scanf和printf来提升精度。

以下是关于小数精度的知识：

float:6~7位

double:15~16位

long double:18~19位

### 最后附上最强AC代码：
    
    
    #include<bits/stdc++.h>  //万能文件头(洛谷福利)
    using namespace std;
    long double a;   //尽我最大努力提升小数精度，我的水平也就只到long double了
    int main()
    {
        scanf("%18LF",&a);   //继续尽我最大努力提升小数精度，意思是将a转化成18位小数读入，这里注意加地址符&，否则会CE，在cstdio库里调用，但这里我就只用万能文件头啦，记得Lf不要小写
        printf("%.8LF",a/23);  //还是尽我最大努力提升小数精度，意思是将a/23转化成8位小数输出，这里注意不要加地址符&，否则会CE，在cstdio库里调用，但这里我就只用万能文件头啦，记得Lf不要小写
        return 0;
    } 

AC了，点个赞呗。


---

## 作者：Aw顿顿 (赞：0)

不想在强调了，yyy系列的题目讲究数据精度！！

天真的我以为long double就够了！！

因为这道题难点在于强制提高精度，那我就先说说易错点

1. long double的占位符是Lf不是lf，lf是double！

2. 用printf和scanf都可以，用cincout的可以开O2

3. 注意语法，最好加上return 0；

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long double n;
int main()
{
	scanf("%15Lf",&n);
	printf("%.8Lf",n/23);
	return 0;
}
```

然后呢，其实题目有提示，数据方面的问题

~~~
数据规模

对于100%的数据,0<x<=1

提示

你想知道x有几位小数吗?才不给你呢>_<

我只知道空间限制是4M,时间限制是0.1s,而且如果你把数字全读下来的话可能就MLE咯~
~~~

这道题还有字符串，快读等多种写法，如果你是蒟蒻，还是用这种比较容易看懂的方法吧，越简单的题目方法越多，也没人说高精除不行啊QAQ~~~


---

## 作者：你锡白大爷 (赞：0)

# 这题看似简单其实一点都不！！注意精度！！！差点就崩了
**咳咳，标题极度激动。。。**

**需要注意的是纯long double是不够的，所以用cin绝对80分**

**好消息是scanf可以强制提高精度**

==========================分割线======================================

## 精度表:

### 各种类型浮点数的精度：

- float:6~7位;

- double:15~16位;

- long double:18~19位。

===============================代码在此==============================
```cpp
#include <bits/stdc++.h>//万能头
int main ()
{
    long double x,s;
    scanf ( "%15Lf", &x );//scanf强行加精度
    s=x/23;//求答案
    printf ( "%.8Lf", s );//简单的输出(然而用cout+fix也是可以的)
    return 0;//完结撒花花~~
}
```


---

## 作者：Wh_Xcjm (赞：0)

出题者应该是想卡一卡的，结果被`long double`虐了。

然而我电脑上的`long double`会输出`0`，同份代码提交AC了，看前几篇题解都是用的`long double`所以就写了个字符串处理的模拟。

代码：
```cpp
#include<stdio.h>
using namespace std;
char ans[11]="0.04347826";\\0<x<=1,所以就特别处理了1,其他的数字都是以"0.xxxxxxxxx"的形式
int main(){
    char c=getchar();
    while(c!='.'&&c!='1')c=getchar();
    if(c=='1')puts(ans);
    else{
        int k=0;
        for(int i=0;i<9;i++){//要求保留8位精度，所以算到第九位就够了，这一段写过高精度除法的都会。
            c=getchar();
            if(c<32)c='0';
            k=k*10-48+c;
            ans[2+i]=k/23+48;
            k%=23;
        }
        if(ans[2+8]>='5'){
            int kk=9;
            while(ans[kk]=='9')ans[kk--]='0';
            ans[kk]++;
        }
        ans[10]='\000';
        printf("%s",ans);
    }
    return 0;
}
```
入门级字符串处理一道挺好的题

---

## 作者：zumgze (赞：0)

看来是一个船新的方法

用getchar读入的方法好多其他大佬都有介绍，这里就不再赘述

重点就讲一下固定小数位数的条件下，可以将数据转化为长整型运算

这里额外需要注意的是四舍五入需要加上除数的一半（这里因为23不是2的倍数，整体做了×10处理）

最后，是输出的时候用cout也可以控制8位小数的哦

代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long double x=0,y=0.1;
    char c;
    c=getchar();
    getchar();
    x+=(c-'0');
    for(int i=0;i<15;i++)
    {
    	c=getchar();
    	if(c>'9'||c<'0')break;
    	x+=(y*(c-'0'));
    	y*=0.1;
	}
    long long help=x*1000000000;//转化为长整型
    help=(help+115)/230;//控制四舍五入
    cout<<"0."<<setw(8)<<setfill('0')<<help;//setw()控制8位长，setfill()意味着高位补0
    return 0;
}
```


---

## 作者：yuyc (赞：0)

emm 这道题就是坑你精度的问题，可作为一个c++党，谈到精度看题解，竟然没有用
```
#include <iomanip>
```
里的函数解的。那我就来一个：

1.setiosflags(ios::fixed);

是用定点方式表示实数，参数改成ios::scientific的话就是用指数方式表示实数。

2.setprecision(8)

控制输出精度，常与上一个函数配套食用；参数表示小数位数。

当然，你用cout成员函数是一样的，就变成
```cpp
  cout.flags(ios::fixed);
  cout.precision(8);
```
上代码！
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>//一定要包
using namespace std;
int main()
{
  long double x=0.0;
  scanf("%15Lf",&x);//输入还是用c版
  cout<<setiosflags(ios::fixed);//c++党专属
  cout<<setprecision(8)<<x/23;
  return 0;
}

```
虽说iomanip里的函数可以控制精度，但我还是倾向于用c版。因为~~我是个伪c++党~~能少打点代码（逃


---

