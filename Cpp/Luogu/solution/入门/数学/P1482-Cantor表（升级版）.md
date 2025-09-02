# Cantor表（升级版）

## 题目描述

现代数学的著名证明之一是 Georg Cantor 证明了有理数是可枚举的。他是用下面这一张表来证明这一命题的：

$$\begin{matrix}
1/1 & 1/2 & 1/3 & 1/4 & 1/5 & \cdots \cr
2/1 & 2/2 & 2/3 & 2/4 &  \cdots \cr
3/1 & 3/2 & 3/3 &  \cdots \cr
4/1 & 4/2 &  \cdots \cr
5/1 &  \cdots \cr
\end{matrix}
$$

这次与 NOIp1999 第一题不同的是：这次需输入两个分数（不一定是最简分数），算出这两个分数的积（注意需要约分至最简分数），输出积在原表的第几列第几行（若积形如 $a$（即结果为整数）或者 $1/a$，则看作表内的 $a/1$ 或 $1/a$ 结算）。


## 说明/提示

### 数据范围

对于全部数据，两个分数的分母和分子均小于 $10^4$。

## 样例 #1

### 输入

```
4/5
5/4```

### 输出

```
1 1```

# 题解

## 作者：Jack_Homes_Huang (赞：75)

#### 写这篇题解,我只想告诉大家,

#### 有一个东西叫做,


## \_\_gcd(x,y);

干什么用的呢？

gcd认识吧，这玩意儿就是求x,y的最大公约数的~

有没有觉得逼格满满！

用于这种约分题目异常简单！


``` cpp
#include<iostream>
#include<cstdio>
#include<algorithm> //就我所知，__gcd()应该在这里面
#include<string>
#include<cstring>

using namespace std;

int a1,a2,b1,b2;
char spc;

int main()
{
    scanf("%d",&a1); spc=getchar(); scanf("%d",&b1); 
    //spc用于读掉除号
    scanf("%d",&a2); spc=getchar(); scanf("%d",&b2);
    int c1=a1*a2,c2=b2*b1;
    printf("%d %d\n",c2 / __gcd(c1,c2),c1 / __gcd(c1,c2)); 
    //约分
    return 0;
}

```

---

## 作者：引领天下 (赞：34)

首先，你要知道：

约分后的分母是行，分子是列。

于是问题来了：

怎么约分？

很简单：用辗转相除法求最大公约数，然后约分。

然后输出。

代码：


```cpp
#include<bits/stdc++.h>//包含所有头文件的头文件
using namespace std;
int gcd(int a,int b){//辗转相除法求最大公约数
    if (!b)return a;//如果b=0，a是最大公约数
    else return gcd(b,a%b);//不然继续
}//提示：现在也可以使用__gcd(a,b)直接求。
int main(){
    ios::sync_with_stdio(false);//流优化
    int a,b,c,d,t;
    char hh;//这家伙对付‘/’号
    cin>>a>>hh>>b>>c>>hh>>d;//读入，不解释
    a*=c;b*=d;//乘一下
    t=gcd(a,b);//求最大公约数
    a/=t,b/=t;//约分
    cout<<b<<" "<<a;//输出
    return 0;
}

```

---

## 作者：凌空の猫 (赞：11)

这题真好，刚好可以用来练习**重定义运算符**

~~所以我们要做出最大行数~~  所以我们要认真做题

本题目思想很简单：定义一下分数，然后
~~本题就没什么难度了~~
本题可以简单很多


------------

一言不合贴代码
```cpp
#include<stdio.h>
#include<string.h>
#include<math.h>
typedef struct fraction{
    long first,last;//first是分子，last是分母
} f;
inline long gcd(long a,long b)
{
    return b==0?a:gcd(b,a%b);//欧几里得函数
}
f reduce(f old){
    long i=gcd(old.first,old.last);
    old.first/=i;
    old.last/=i;
    return old;
}//你需要约分！
f operator+(f a,f b){
    if(a.last==b.last){
        a.first+=b.first;
        return a;
    }
    else{
        a.last*=b.last;
        a.first+=b.first;
        a=reduce(a);
        return a;
    }
}
f operator-(f a,f b){
    if(a．last==b．last){
        a.first==b.first;
        return a;
    }
    else{
        a.last*=b.last;
        a.first-=b.first;
        a=reduce(a);
        return a;
    }
}
f operator*(f a,f b){
    a.last*=b.last;
    a.first*=b.first;
    a=reduce(a);
    return a;
}
f operator／(f a,f b){
    a.last*=b.first;
    a.first*=b.last;
    a=reduce(a);
    return a;
}
f toFractionOf(char* in){
    long a=0,b=0,count=0,ocount;
    char iinF=' ';
    f ainF;
    do {
        iinF=in[count];
        a*=10;
        a+=iinF-'0';
        count+=1;
    } while (in[count]!='/'&&count<strlen(in));
    if(count==strlen(in)){
        ainF.first=a;
        ainF.last=1;
        return ainF;
    }
    ocount=count+1;
    count=0;
    do {
        iinF=in[ocount];
        b*=10;
        b+=iinF-'0';
        count+=1;
        ocount+=1;
    } while (ocount<strlen(in));
    ainF.first=a;
    ainF.last=b;
    return ainF;
}
//把字符串转换为分数
double toFloatOf(f in){
    return in.last!=0 ? double(in.first)/in.last : (static_cast<void>(perror("0 CAN NOT BE DIVISOR\n\n\n\n\n\n\n\n\n\n")),0 );
}
//把分数转化为Double
int main(){
    char a[998],b[998];
    f n1,n2;
    scanf("%s%s",a,b);
    n1=toFractionOf(a);
    n2=toFractionOf(b);
    n1=n1*n2;
    printf("%ld %ld",n1.last,n1.first);
    return 0;
}
//华丽丽のMain
//简洁的利用
```

---

## 作者：n0000000000o (赞：9)

#本题其实就是一个化简题。。

关键是乘了之后的约分，


然而小学数学告诉我们，约分只需要两步：

###1.求出分母分子的最大公因数（最大公约数）

###2.然后分母分子同时除以这个数。

可以用[辗转相除法](https://baike.baidu.com/item/%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4%E6%B3%95/4625352?fr=aladdin "辗转相除法")或[更相减损法](https://baike.baidu.com/item/%E6%9B%B4%E7%9B%B8%E5%87%8F%E6%8D%9F%E6%B3%95 "更相减损法")


在此送上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c,d;
    char x;
    cin>>a>>x>>b >>c>>x>>d;//x防止“/”的输入
    a*=c;b*=d;
    //之后c和d就没用了
    c=a;d=b;
    //更相减损法
    while(c!=d)
    {
        if(c>d)
            c-=d;
        else
            d-=c;
    }
    
    int ww=d;//此时ww为最大公因数
    a/=ww;b/=ww;
    cout<<b<<" "<<a<<endl;//注意是先列再行
}
```

---

## 作者：北北北北 (赞：8)

这个题有两种做法，第一种做法就是一点一点的去对所算出来的积进行

约分，约到最简为止，然后将分子和分母倒序输出就可以了，虽然这种

方法是可以，但是它消耗时间是很多的，所以不推荐，第二种做法就是

用辗转相除法来求出分子和分母的最大公约数，然后让分子和分母分别

去和最大公约数相除，然后倒序输出结果即可，这种方法相比第一种

要快很多。

第二种方法的实现代码：

------------
```c
#include <stdio.h>

int GCD(int fz,int fm)
{
	if(fz%fm == 0)
	{
		return fm;
	}
	GCD(fm,fz%fm);
}

int main(void)
{
	int fz1,fm1,fz2,fm2,gcd;
	
	scanf("%d/%d %d/%d", &fz1,&fm1,&fz2,&fm2);
	gcd = GCD(fz1*fz2,fm1*fm2); //求分子和分母的最大公约数
	printf("%d %d", fm1*fm2/gcd,fz1*fz2/gcd);
	
	return 0;
}
```


---

## 作者：Dfox (赞：8)

# 题解 P1482 【Cantor表（升级版）】

### 题目描述
现代数学的著名证明之一是Georg Cantor证明了有理数是可枚举的。他是用下面这一张表来证明这一命题的：

1/1 1/2 1/3 1/4 1/5 …

2/1 2/2 2/3 2/4 …

3/1 3/2 3/3 …

4/1 4/2 …

5/1 …

… 这次与NOIp1999第一题不同的是：这次需输入两个分数（不一定是最简分数），算出这两个分数的积（注意该约分的要约分）后输出积在原表的第几列第几行（若积是整数或1/积，则以“积/1”或“1/积”结算）。

### 输入格式
共两行。每行输入一个分数（不一定是最简分数）。

### 输出格式
两个整数，表示输入的两个分数的积在表中的第几列第几行，注意该约分的要约分。
### 输入输出样例
#### 输入 
4/5
5/4
#### 输出
1 1
### 说明/提示
1.所有数据：两个分数的分母和分子均小于10000
2.先求出最大公约数
 
~~不说了，上代码~~

------------
```c
#include <bits/stdc++.h>
using namespace std;
int main(){
    int b,a,c,d;
    char e;
    cin>>b>>e>>a;  //输入分子，“/”，分母
	 cin>>c>>e>>d;  //输入分子，“/”，分母
    b*=c;
	 a*=d;
    c=b;
	 d=a; 
    while(c!=d){
       if(c>d){
  			c-=d;
  		  }
       else{
  			d-=c;
  		  }
    }
	 int ww=d;
    b/=ww;
	 a/=ww;
    cout<<a<<" "<<b<<endl;  //输出积的位置
    return 0;
}
```
~~要来我的博客欧~~
https://www.luogu.org/blog/bangbangdeshanshan/

---

## 作者：111l (赞：5)

本题就是求两分数之积，然后再约分。唯一要注意的是列和行不能搞反。

下面是代码：
```cpp
#include<cstdio>
int l[2],r[2];//个人认为数组表示更直观
inline int gcd(int a,int b){while(b^=a^=b^=a%=b);return a;}//辗转相除求最大公约数。b^=a^=b^=a等价于交换a,b的值
int main(){
	scanf("%d/%d%d/%d",&l[0],&r[0],&l[1],&r[1]);//注意:此处分数线直接当参数处理，非常方便
	printf("%d %d",(r[0]*r[1])/gcd(l[0]*l[1],r[0]*r[1]),(l[0]*l[1])/gcd(l[0]*l[1],r[0]*r[1]));//先输出列再输出行，别搞混了
}
```
结束

---

## 作者：YaliKiWi (赞：5)

#水。。。#

###思路：乘起来，找最大公约数，约分，输出###

```cpp
 ![](https://cdn.luogu.com.cn/upload/pic/4607.png) 
#include<bits/stdc++.h>
using namespace std;
void read(int &x){//字符串写读入优化 
    x=0;char c=getchar();
    while(c<'0' || c>'9')c=getchar();
    while(c>='0' && c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
}
void write(int x){//输出优化 
        int y=10,len=1;
        while(y<=x)  {y*=10;len++;}
        while(len--){y/=10;putchar(x/y+48);x%=y;}
    }
int gcd(int a,int b);//声明最大公约数函数 
int main()
{
    ios::sync_with_stdio(false);//毫无意义的加速 
    int ason,amum,bson,bmum,rson,rmum;//第一个数、第二个数、乘积的分子和分母 
    char hh;//读分数线 “/” 
    cin>>ason>>hh>>amum>>bson>>hh>>bmum;//读入 
    rson=ason*bson;//乘出分子 
    rmum=amum*bmum;//乘出分母 
    int k=gcd(rson,rmum);//找乘后分母分子最大公约数 
    rson/=k;rmum/=k;//约分 
    cout<<rmum<<" "<<rson;//输出 
    return 0;
}
int gcd(int a,int b){
    for(int i=min(a,b);i>=1;i--){
        if(a%i==0&&b%i==0){
            return i;break;//暴力找最大公约数 
        }
    }
}
 ![](https://cdn.luogu.com.cn/upload/pic/4608.png) 
```
蟹蟹~


---

## 作者：Lylighte (赞：4)

*2020/02/14*

升级版？还是入门题？

看下题，就是求一个有理数在 Cantor 表中的位置（**先列数后行数**是唯一的坑点）。分母对应列数，分子对应行数，求出分母分子即可。

先解决约分问题。一些定义：

>把单位「1」平均分成若干份，表示这样的一份或几份的数叫分数。
>
>分子和分母是互质数的分数，叫做最简分数。
>
>把分数化成最简分数的过程就叫约分。

一种约分方法：分子分母同时除以它们的**最大公约数**。

而求最大公约数也有多种方法，这里用**辗转相除法**（欧几里得算法）。

```cpp
int gcd(int x, int y){
	if(x%y==0)
        return y;
   	else
        return gcd(y, x%y);
}	
```

或者

```cpp
int gcd(int x, int y){
	return x%y==0 ? y : gcd(y, x%y);
}	
```

然后解决读入的问题。输入中既包含数字又包含其他字符，中间没有空格。我选择 string。

可以直接用 `cin` 读入 string 类型，即 `string st; cin >> st;`，读入一个字符串（无空格）。

分离出分子和分母：以 `/` 为分隔符，前半部分为分子，后半部分为分母。从头到尾扫一遍字符串，分离出第一个数，过了 `/` 再分离第二个数。分离前半段数字可以用这段代码：

```cpp
while(st[p]!='/'){
    num = num*10+(st[p]-'0');
    p++;
}
a = num;
num = 0;
```

后半段同理。

至此，分离出分子分母，分别相乘并约分，再输出，这题就做完了。

贴代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[4], b[4];		//a 数组存分子，b 数组存分母
string st;

int gcd(int x, int y){
	return x%y==0 ? y : gcd(y, x%y);
}

int main(){
	for(int i=1; i<=2; i++){		//分离分子分母
		cin >> st;
		int num=0, len=st.size(), p=0;
		while(st[p]!='/')
			num = num*10+st[p++]-'0';
		a[i] = num;
		num = 0;
		p++;
		while(p<len)
			num = num*10+st[p++]-'0';
		b[i] = num;
	}
	a[3] = a[1] * a[2];
	b[3] = b[1] * b[2];
	int gcdab = gcd(a[3], b[3]);
	cout << b[3]/gcdab << ' ' << a[3]/gcdab << endl;	//求出目标有理数并输出
	return 0;
} 
```

The end.

---

## 作者：AubRain (赞：3)

蒟蒻的c++12行简短代码，已ac！简单易懂

```cpp
#include<bits/stdc++.h>
using namespace std;
int g(int a,int b){return b==0?a:g(b,a%b);}//自定义一个求最大公因数的函数，用来约分（辗转相除法）（这里用到了一个三目运算符）
int main(){
    int a,b,x,y,s;//s为新分数分子和分母的最大公因数
    char m,n;//m，n为输入的两个“/”
    cin>>a>>m>>b;
    cin>>x>>n>>y;
    x*=a;y*=b;s=g(x,y);//x为新分子，y为新分母，s为最大公因数
    x/=s;y/=s;//约分
    cout<<y<<" "<<x;//输出第y列，第x行（顺序不能写反，否则只有20分）
    return 0;}
```

---

## 作者：杨秦懿 (赞：2)

# （1）做法

这道题目简单分析，我个人认为就是苏教版六年级上册就已经学了的，非常简单的——分数乘法咯！

甚么意思呢？简单分析一下：

1.它说两个数相乘。

2.观察整个Cantor表（难得有耐心把它列举出来）：

1/1 1/2 1/3 1/4 1/5 ……

2/1 2/2 2/3 2/4 ……

3/1 3/2 3/3……

4/1 4/2……

5/1……

可见，分子是行，分母是列。

# （2）提醒
1.分母和分子均小于10000，则答案分子母不会大于100000000。

2.最关键的一点，先输出列再输出行，也就是先输出分母再输出分子就行了。

我的题解：
```cpp
#include<bits/stdc++.h>
using namespace std;
int fza,fzb,fmx,fmy,dfz=1,dfm=1;
int gcd(int x,int y);
int main(){
	scanf("%d/%d",&fza,&fmx);
	scanf("%d/%d",&fzb,&fmy);
	dfz=fza*fzb;
	dfm=fmx*fmy;
	int x=gcd(dfz,dfm);
	cout<<dfm/x<<' '<<dfz/x<<endl;
} 
  int gcd(int x,int y){
	//预防抄袭，供大家自己思考
}
```
谢谢了~

---

## 作者：QianhanOfficial (赞：2)

```cpp
//Cantor表的分数可以看作平面直角坐标系
//这样理解了以后我们就会发现，此题就是为了化简分数
//但是一定要注意输出的时候先输出分母，再输出分子，相当于列和行
//另外一方面，本蒟蒻不会写最大公因数（实际是懒）所以看了看数据范围直接打了枚举
//有一个小小的优化，化简分数的时候是 从相乘得到的分子分母中的最小值 到 2 枚举
//这样只要遇到公因数就跳出循环，获得的一定是最大值
//思路总结:分数化简+枚举公因数
//与之前某篇题解有相似之处 但在循环的方向上有不同 并且代码更清爽一些（Visual Studio格式23333）
#include<cstdio>

int a1, b1, a2, b2, a3, b3;

int main()
{
	scanf("%d/%d", &a1, &b1);
	scanf("%d/%d", &a2, &b2);
	a3 = a1 * a2;
	b3 = b1 * b2;
	int t = a3 < b3 ? a3 : b3;//找出分子分母的最小值
	for(int i = t; i >= 2; i--)
	{
		if(!(a3 % i) && !(b3 % i))
		{
			a3 /= i;
			b3 /= i;
			break;
		}
	}
	printf("%d %d", b3, a3);
	return 0;
}
//求过……真的没有重复QAQ
```

---

## 作者：5ab_juruo (赞：1)

一看到这题，心里就痒痒，非常想~~装逼~~使用数据结构。
但转念一想，又要重载运算符。算了吧，还是用类来玩。
# 前方高能
------
首先我们来定义一个类，描述一个分数需要知道分子和分母，所以在private部分定义两个整数，分别表示分子和分母：
```cpp
	private:
		int fz;
		int fm;
```
定义方法时，为了满足自己的~~欲望~~想法，重载了 * 运算符。方法见下：
```cpp
	public:
		Fraction();
		Fraction(int Fz,int Fm);//构造函数
		~Fraction();           //析构函数
		int showfrac(mode mde);//mode是枚举出来的新类型
		void get_gcd();        //计算最大公约数
		Fraction operator*(Fraction frac1);
```
这样就定义好了类：
```cpp
class Fraction
{
	private:
		int fz;
		int fm;
	public:
		Fraction();
		Fraction(int Fz,int Fm);
		~Fraction();
		int showfrac(mode mde);
		void get_gcd();
		Fraction operator*(Fraction frac1);
};
```
----------
接下来就是函数：首先是构造函数和析构函数：
```cpp
Fraction::Fraction()
{
	fz=1;
	fm=1;
}

Fraction::Fraction(int Fz,int Fm)
{
	if(Fm==0)
		cerr<<"Error : Divided By Zero .\n";//标准错误流，在io-stream里定义
	else
	{
		fz=Fz;
		fm=Fm;
	}
}

Fraction::~Fraction()
{
}
```
然后是输出分子、分母的函数、最大公约数函数以及重载的运算符：
```cpp
int Fraction::showfrac(mode mde)
{
	if(mde==0)
		return this->fz;
	else
		return this->fm;//this是指向自己的指针
}

void Fraction::get_gcd()
{
	int cp1=fz,cp2=fm;
	while(cp1!=0 && cp2!=0)
	{
		if(cp1>cp2)
			cp1%=cp2;
		else
			cp2%=cp1;
	}//辗转相除法
	int gcd=cp1+cp2;//因为其中必有一个0，相加就可以过滤掉
	fz/=gcd;
	fm/=gcd;
}

Fraction Fraction::operator*(Fraction frac1)
{
	Fraction answer(fz*frac1.showfrac(upper),frac1.showfrac(lower)*fm);
	answer.get_gcd();
	return answer;
}
```
最后是主程序：
```cpp
int main()
{
	int a,b;
	scanf("%d/%d",&a,&b);
	Fraction f1(a,b);
	scanf("%d/%d",&a,&b);
	Fraction f2(a,b);
	Fraction f_ans=f1*f2;//使用重载后的*运算符
	cout<<f_ans.showfrac(lower)<<" "<<f_ans.showfrac(upper)<<endl;
	return 0;
}
```
连起来就是传说中的80行代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
enum mode{upper=0,lower=1};
class Fraction
{
	private:
		int fz;
		int fm;
	public:
		Fraction();
		Fraction(int Fz,int Fm);
		~Fraction();
		int showfrac(mode mde);
		void get_gcd();
		Fraction operator*(Fraction frac1);
};

Fraction::Fraction()
{
	fz=1;
	fm=1;
}

Fraction::Fraction(int Fz,int Fm)
{
	if(Fm==0)
		cerr<<"Error : Divided By Zero .\n";
	else
	{
		fz=Fz;
		fm=Fm;
	}
}

Fraction::~Fraction()
{
}

int Fraction::showfrac(mode mde)
{
	if(mde==0)
		return this->fz;
	else
		return this->fm;
}

void Fraction::get_gcd()
{
	int cp1=fz,cp2=fm;
	while(cp1!=0 && cp2!=0)
	{
		if(cp1>cp2)
			cp1%=cp2;
		else
			cp2%=cp1;
	}
	int gcd=cp1+cp2;
	fz/=gcd;
	fm/=gcd;
}

Fraction Fraction::operator*(Fraction frac1)
{
	Fraction answer(fz*frac1.showfrac(upper),frac1.showfrac(lower)*fm);
	answer.get_gcd();
	return answer;
}

int main()
{
	int a,b;
	scanf("%d/%d",&a,&b);
	Fraction f1(a,b);
	scanf("%d/%d",&a,&b);
	Fraction f2(a,b);
	Fraction f_ans=f1*f2;
	cout<<f_ans.showfrac(lower)<<" "<<f_ans.showfrac(upper)<<endl;
	return 0;
}
```
```cpp
/*operator的用法：
operator其实就是一种特殊的函数，只不过它是一种使用符号而非大括号来输入值的函数。
一般如下使用：
Typename operatorop(Variableslist);
提示：operator重载运算符只限于在特定的类里使用哦！

比如说iostream里就重载了>>和<<左/右移运算符，成为了流运算符*/
```

---

## 作者：1jia1 (赞：1)

一开始看难得不得了，后来机智的chen想到了方法。

输入不需要getline，太麻烦了。可以用c库的scanf输入，可以把不同数据结构分别读入。然后核心思路：分子分母各自相乘就是积，然后约分就完美了。

```cpp
#include<cstdio>
-#include<iostream>-
-using namespace std;-
-int a,b,c,d,s=0;-
-char e;-
-int j8(int a,int b)---约分大法
-{-
-    if(b==0)return a;-
-    return j8(b,a%b);-
-}-
-int main()-
-{-
-    scanf("%d%c%d%d%c%d",&a,&e,&b,&c,&e,&d);-
-    s=b*d;-
-    s/=j8(a*c,b*d);-
-    cout<<s<<" ";-
-    s=a*c;-
-    s/=j8(a*c,b*d);-
-    cout<<s;-
-}-
```

---

## 作者：Sinwind (赞：0)

思路：

1. 读取两个分数，并计算出它们的乘积（此时结果未约分）；

2. 用辗转相除法，求得结果的分子与分母的最大公约数，约分，化简分数。

- 辗转相除法：有两个数m,n(必须保证m>=n，否则r=0)，r=m%n。
- r的值不为0，则m=n,n=r;继续r=m%n。（递归公式）
- r的值为0，则n是m,n的最大公约数。（递归边界）
![辗转相除法（图片来自网络）](data:image/jpeg;base64,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)

3. 找规律发现：结果的分子对应着行，分母对应着列，输出行和列。

```c
//辗转相除法，返回x,y的最大公约数
int GCD(int x, int y)
{
	//辗转相除法必须x>y
	if (x < y)
	{
		int temp = x;
		x = y;
		y = temp;
	}
	return (x % y == 0) ? y : GCD(y, x % y);
}

int main(void)
{
	    int a,		//第一个分数的分子
		b,		//第一个分数的分母
		c,		//第二个分数的分子
		d,		//第二个分数的分母
		e,		//结果分数的分子
		f,		//结果分数的分母
		gcd;		//e,f的最大公约数

	scanf_s("%d/%d", &a, &b);
	scanf_s("%d/%d", &c, &d);

	e = a * c;
	f = b * d;
	//求得e,f的最大公约数gcd
	gcd = GCD(e, f);
	//化简为最简分数
	e /= gcd;
	f /= gcd;

	//分子代表行，分母代表列
	printf("%d %d\n", f, e);

	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

```cpp
方法楼下的说的很清楚啦qwq

面向对象的写法
写一个封装分数功能的类
以后直接调用即可
一次编写，到处运（tiao）行（shi）
如果c++提供这个类就好了
咱就不必如此模拟

#include<cstdio>

using namespace std;

class Fraction{
private:
    /*
     * @var:den -> 分母
     * @var:num -> 分子 
     */

    int den;
    int num;

    /*
     * @args:int a,int b
     * @des:求a,b的最大公约数 
     */
    int gcd(int a,int b){
        return b == 0 ? a : gcd(b,a % b);
    } 

    /*
     * @des:将分数化简为最简分数 
     */
    void simplify(){
        int MOD = gcd(this -> getNum(),this -> getDen());//求出最大公约数 

        if((double)this -> getNum() / this -> getDen() == 1){//如果分子等于分母，则为1 
            this -> setNum(1);
            this -> setDen(1);
            return;
        }else if(MOD == 1){//如果最简，直接返回 
            this -> setNum(this -> num);
            this -> setDen(this -> den);
            return;
        }else if(MOD != 1){//如果为非最简，则除以gcd 
            this -> setNum(this -> num / MOD);
            this -> setDen(this -> den / MOD);
        }
    }

public:
    /* 
     * @des: 无参构造方法
     */
    Fraction(){
        this -> num = 0;
        this -> den = 1;
    }

    /* 
     * @var: int num,int den 
     * @des: 有参构造方法 
     */
    Fraction(int num,int den){
        if(den != 0){
            this -> num = num;
            this -> den = den;
            this -> simplify();
        }else{
            printf("Unaccept Fraction,zero den\n");
        }
    }

    /* 
     * @des: getter
     */
    int getNum(){
        return this -> num;
    }

    /* 
     * @des: getter
     */
    int getDen(){
        return this -> den;
    }

    /* 
     * @des: setter
     */
    void setNum(int num){
        this -> num = num;
    }

    /* 
     * @des: setter
     */
    void setDen(int den){
        this -> den = den;
    }

    /* 
     * @des: 显示分数 
     */
    void show(){
        if(this -> getDen() < 0){
            this -> setDen(-this -> getDen());
            this -> setNum(-this -> getNum());
        }

        if(this -> den == 1){
            printf("%d",this -> num);
        }else{
            printf("%d/%d",this -> num,this -> den);
        }
    }

    /* 
     * @des: 加法 
     */
    friend Fraction operator + (Fraction &a,Fraction &b){
        return Fraction(a.getNum() * b.getDen() + a.getDen() * b.getNum(),a.getDen() * b.getDen());
    }

    /* 
     * @des: 减法 
     */
    friend Fraction operator - (Fraction &a,Fraction &b){
        return Fraction(a.getNum() * b.getDen() - a.getDen() * b.getNum(),a.getDen() * b.getDen());
    }

    /* 
     * @des: 乘法 
     */
    friend Fraction operator * (Fraction &a,Fraction &b){
        if(a.getNum() == 0 || b.getNum() == 0){
            return Fraction();
        }

        return Fraction(a.getNum() * b.getNum(),a.getDen() * b.getDen());
    }

    /* 
     * @des: 除法 
     */
    friend Fraction operator / (Fraction &a,Fraction &b){
        if(a.getNum() == 0){
            return Fraction();
        }

        if(b.getNum() == 0){
            return Fraction(1,0);
        }

        return Fraction(a.getNum() * b.getDen(),a.getDen() * b.getDen());
    }
};

int main(){
    int aa,bb,cc,d;
    scanf("%d/%d\n%d/%d",&aa,&bb,&cc,&d);
    
    Fraction a(aa,bb);
    Fraction b(cc,d);
    
    Fraction c = a * b;
    
    printf("%d %d",c.getDen(),c.getNum());
    
    return 0;
}
```

---

## 作者：封弊者—桐子 (赞：0)

```cpp
var a,b,c,d,i,j,l,k:longint;
    s,s1,s2:string;//个人觉得采用字符串读入会好一些，但可能比较麻烦
begin
  readln(s);
  l:=length(s);
  j:=pos('/',s);//找到第一个分数中分数线的位置
  s1:=s; delete(s1,j,l-j+1);//s1储存分数线前的部分（分子）
  val(s1,a);//转数字存入a中
  delete(s,1,j);//将s中的分数线及分数线以前的部分删去（留下的就是分母）
  val(s,b);//转数字存入b中
  readln(s);//下面以同样的方法处理第二个分数（方法一模一样，由c和d来存储）
  l:=length(s);
  j:=pos('/',s);
  s1:=s; delete(s1,j,l-j+1);
  val(s1,c);
  delete(s,1,j);
  val(s,d);
  a:=a*c;//将分子、分母相乘
  b:=b*d;//存入a和b中
  if a>b then//判断a和b哪个大
  begin
    c:=b;
    d:=a;
  end
  else begin
    c:=a;
    d:=b;
  end;
  repeat//运用辗转相除法求出a和b的最大公因数d
    i:=d mod c;
    d:=c;
    c:=i;
  until i=0;
  a:=a div d;//进行约分
  b:=b div d;
  writeln(b,' ',a);//输出（注意：先列后行，先列后行，先列后行，重要的事情说三遍！！！）
end.

```

---

## 作者：zhylj (赞：0)

这题其实比原题还水

由于分子分母分别是行和列

所以……

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a1,a2,b1,b2,c1,c2,r;
    scanf("%d/%d%d/%d",&a1,&a2,&b1,&b2);  //scanf大法好
    c1=a1*b1;c2=a2*b2;  //相乘
    r=__gcd(c1,c2);  //求最大公约数
    c1/=r;c2/=r;  //约分
    printf("%d %d",c2,c1);  //输出
    return 0;
}
```

---

## 作者：courage (赞：0)

说是升级版，实际上比原题还要水

实际上就是两个分数相乘再约分。要注意的是先输出分母再输出分子

另外说一句，这题用scanf读入数据比较方便


```cpp

#include<cstdio>
int a,b,c,d,e;
int gcd(int a,int b){
    if (b==0) return a;
    return gcd(b,a%b);
}
int main(){
    scanf("%d/%d %d/%d",&a,&b,&c,&d);
    a*=c;
    b*=d;
    e=gcd(a,b);
    a/=e;
    b/=e;
    printf("%d %d",b,a);
}

```

---

## 作者：felixwu (赞：0)

scanf可以自动省略'/'
上代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int c1,c2,a1,a2,b1,b2;
int main()
{
    scanf("%d/%d%d/%d",&a1,&b1,&a2,&b2);//////我说的省略
    c1=a1*a2; c2=b1*b2;
    printf("%d %d",c2 / __gcd(c1,c2),c1 / __gcd(c1,c2));
    return 0;
}
```

---

