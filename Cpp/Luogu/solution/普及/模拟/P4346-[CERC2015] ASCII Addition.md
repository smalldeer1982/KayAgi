# [CERC2015] ASCII Addition

## 题目描述

# 题目背景

现在，如果你只是用手机的相机对着它们，智能手机应用可以即时翻译文本，甚至解决数学问题。您的工作是实现一个更简单的功能，回忆过去——添加两个作为ASCII艺术的整数。


ASCII艺术是一个字符矩阵，正好是7行高，每个字符都是点或小写字母X。

给出了A +B形式的表达式，其中A和B都是正整数。通过将所有的表达式字符（A和B的数字以及符号）作为7 5个矩阵，将这些矩阵转换成ASCII艺术，并将矩阵与单个字符的单个列串联在连续的各个矩阵之间。对应于数字和+符号的精确矩阵如下：

![](https://cdn.luogu.org/upload/pic/16222.png)

给定一个ASCII艺术来表达A+B的形式，找到加法的结果并用ASCII艺术形式写出。

## 样例 #1

### 输入

```
....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.......xxxxx.xxxxx.xxxxx
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.......xxxxx.xxxxx.xxxxx```

### 输出

```
....x.xxxxx.xxxxx.xxxxx.x...x.xxxxx.xxxxx
....x.....x.....x.x.....x...x.x.........x
....x.....x.....x.x.....x...x.x.........x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x
....x.x.........x.....x.....x.....x.....x
....x.x.........x.....x.....x.....x.....x
....x.xxxxx.xxxxx.xxxxx.....x.xxxxx.....x```

# 题解

## 作者：opened (赞：7)

这道黑题当之无愧，非常考验代码能力（字符串的处理、如何打表、如何在多种数据存储类型间自由转换从而达成题目的要求~~，甚至还有a+b~~），如果你想充分挖掘此题的能量，请做到以下三点：
	
    1.代码长度不超百行，即高效判断
    2.编码时间不超过一小时，即思路清晰、代码可读性较强
    3.一定不要看题解，即自成题解的决心

**Talk is cheap, show me the code.**

~~鄙人代码仅供交流、研讨、学习、Hack~~

```#include<iostream>
#include<cstdio>
using namespace std;
string s[7],sum[7],num[11]={ //打数字表：数字逐行处理,还要打出数字间的间隔 
/*以0为例 
xxxxx.
x...x.
x...x.
x...x.
x...x.
x...x.
xxxxx.
*/ 
"xxxxx.x...x.x...x.x...x.x...x.x...x.xxxxx.",//0
"....x.....x.....x.....x.....x.....x.....x.",//1
"xxxxx.....x.....x.xxxxx.x.....x.....xxxxx.",//2
"xxxxx.....x.....x.xxxxx.....x.....x.xxxxx.",//3
"x...x.x...x.x...x.xxxxx.....x.....x.....x.",//4
"xxxxx.x.....x.....xxxxx.....x.....x.xxxxx.",//5
"xxxxx.x.....x.....xxxxx.x...x.x...x.xxxxx.",//6
"xxxxx.....x.....x.....x.....x.....x.....x.",//7
"xxxxx.x...x.x...x.xxxxx.x...x.x...x.xxxxx.",//8
"xxxxx.x...x.x...x.xxxxx.....x.....x.xxxxx.",//9
"........x.....x...xxxxx...x.....x.........",//+
};
int pos;//一个指针 
stack<int>a;
inline char r(){//原表->单个字符数字
	string ss;
	for(int i=0;i<7;i++) ss+=s[i].substr(pos,6);//逐行取单个数字
	pos+=6;//移动指针,下次使用 
	for(int i=0;i<10;i++)
		if(ss==num[i]) return i+'0'; //匹配数字表 
	return 0;
}
inline int read(){//快读式:字符数字->整型 
	int x=0;char ch=r();
	while(!ch) ch=r();
	for(x=ch&15,ch=r();ch;ch=r()) x=x*10+(ch&15);
	return x;
}
void change(int ans,int end=1/*end可处理掉尾部间隔,否则wa*/){
	if(ans>9) change(ans/10);//递归:实现倒序->正序 
	for(int i=0;i<7;i++)
		sum[i]+=num[ans%10].substr(i*6/*头位置*/,5+end/*长度*/);//字符数字->横行答案表 
				/*substr:字符串函数,复制子字符串*/ 
}
int main(){
	for(int i=0;i<7;i++){
		cin>>s[i];
		s[i]+="."; //补出尾部间隔,方便判断 
	}
	
	int a=read(),b=read(); //原理见题解1001:a+b problem 
	int ans=a+b;
	
	change(ans,0);//int答案->横行答案表
	
	for(int i=0;i<7;i++) cout<<sum[i]<<"\n"; //输出答案表 
	return 0;
}```

---

## 作者：Gu_Ren (赞：6)

萌新刚从$\mathit{Pascal}$转到$\mathit{c++}$（码风不好勿喷），打算做道题试试自己的语法，于是随机跳到了这个$\color{yellow}\colorbox{Purple}{黄题}$，结果调了一上午。。。

我发现这样一种简洁的思路，因为每个点都是$\mathrm{"."}$或$\mathrm{"x"}$，所以可以把它们转化成**二进制**（可以把二维的矩阵**转成一维的**）；

然后把二进制再转回十进制，就可以得到**0$\sim$9**每个数（还有“+”）的$\mathrm{"ASCII"}$矩阵独有的**十进制数**；

最后把读入的**矩阵**分别转成**十进制**，再去找提前**准备好的十进制数**，对应一下得到**0$\sim$9**这些数

最后把这些数拼起来运算一下，把对应的$\mathrm{"ASCII"}$矩阵输出即可。

##### 小问题：一开始我以为会有多个“+”，于是计算总和的写法有点奇怪

------------
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[11];
int a[30][1000],x,num,t,cnt;
char m[30][1000];
int b[30],ans[30],dt[30],d[30];
int c[11]={
	1363481695,272696336,1098712095,276628511,276632657,276566111,1367085151,272696351,1367151711,276632671,75251968
};//提前准备0~9和“+”对应的矩阵转成二进制的值（也是通过这个程序算出的）
string e[10]={
	("xxxxxx...xx...xx...xx...xx...xxxxxx"),
	("....x....x....x....x....x....x....x"),
	("xxxxx....x....xxxxxxx....x....xxxxx"),
	("xxxxx....x....xxxxxx....x....xxxxxx"),
	("x...xx...xx...xxxxxx....x....x....x"),
	("xxxxxx....x....xxxxx....x....xxxxxx"),
	("xxxxxx....x....xxxxxx...xx...xxxxxx"),
	("xxxxx....x....x....x....x....x....x"),
	("xxxxxx...xx...xxxxxxx...xx...xxxxxx"),
	("xxxxxx...xx...xxxxxx....x....xxxxxx"),
};//提前准备0~9对应的ASCII矩阵（长5 宽7）

int main(){
	for (int i=1;i<=7;i++){
		cin>>s[i];
		s[i]=s[i]+'.';
	}//为了确保最后一个数的二进制位数与前面的一样，所以在每行末尾加个“.”
    int n=s[1].length();
    for (int i=1;i<=7;i++)
    for (int j=0;j<n;j++){
    	a[i][j]=(s[i][j]=='x');//转二进制，“x”为1，“.”为0
	}
    t=1;
    for (int i=0;i+6<=n;i+=6){//把矩阵当做一维处理
    	x=1;
    	for (int j=1;j<=7;j++)
    	{//二进制转十进制
    	    for (int k=i;k<i+6;k++)
    	    {
    			b[num]+=x*a[j][k];
    			x=x*2;
    		}
    	}
        for (int j=0;j<10;j++)
        if (b[num]==c[j]){
            ans[t]=ans[t]*10+j;
            break;
        }
        if (b[num]==75251968) t++;//特判加号
        num++;
	}
    for (int i=1;i<=t;i++) ans[t+1]+=ans[i];
    while(ans[t+1]!=0){//取出答案（十进制）的每一位数
        cnt++;
        dt[cnt]=ans[t+1]%10;
        ans[t+1]=ans[t+1]/10;
    }
    for (int i=1;i<=cnt;i++) d[i]=dt[cnt-i+1];
	for (int i=0;i<35;i+=5){//输出参考了大佬的写法
		for (int j=1;j<=cnt;j++)
		{
			for (int k=i;k<=i+4;k++)
			printf("%c",e[d[j]][k]);
			if (j!=cnt) printf(".");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Enstein (赞：3)

# 前言

#### 首先，别被难度(截止写题解前还是黑题)吓到了，仔细分析，你会发现这其实是一道简单字符串水题。

# 解题思路

#### 先分析一波题目，一个简单的加法，但是加数、被加数与加号用字符串表示。

#### 你首先要明白，只有先转换为数字才能加，所以你需要识别这三个东西，因此先开个字符串数组表示数字 $0$ ~ $9$ 和 $+$，这里我考虑的是用$c^{++}$的 $string$ 数组来存储(将样例复制粘贴就可以了，下面都用 $string$ 数组)，就有：

```cpp
string shu[15]={
"xxxxxx...xx...xx...xx...xx...xxxxxx",		//0
"....x....x....x....x....x....x....x",		//1
"xxxxx....x....xxxxxxx....x....xxxxx",		//2		
"xxxxx....x....xxxxxx....x....xxxxxx",		//3			
"x...xx...xx...xxxxxx....x....x....x",		//4
"xxxxxx....x....xxxxx....x....xxxxxx",		//5
"xxxxxx....x....xxxxxx...xx...xxxxxx",		//6
"xxxxx....x....x....x....x....x....x",		//7
"xxxxxx...xx...xxxxxxx...xx...xxxxxx",		//8
"xxxxxx...xx...xxxxxx....x....xxxxxx",		//9
".......x....x..xxxxx..x....x......."		 //+
};

```

#### 然后就是读入：(也简单，总共有 $7$ 行，循环一下就可以了)
```cpp
for(int i=1;i<=7;i++) cin>>ss[i];		//这个ss是string数组
```

#### 下面是转换：(这里注意每个数字(或加号与数字)的中间都有一排点)
##### ①下面这个是将输出转换为上面那个数组一样的形式(我开了个 $string$ 数组 $a$)。
```cpp                         
int ci=0;									   //ci表示第几组字符                                   
for(int i=1;i<=7;i++){
	ci=0;
	int kkk=ss[i].length();
	for(int j=0;j<kkk;j+=6){                    //j+=6表示每隔六位转换，可以处理那个点
		ci++; 								  //因为是五个字符一组，这里要++
		a[ci].sa+=ss[i].substr(j,5);   		 //调用substr函数截取字符，j是其实位置，5是长度，string类型可以+=拼接
	}
}
```
##### 可能上面没怎么说清，下面举个例子：

![](http://wx1.sinaimg.cn/mw690/0060lm7Tly1fw7uyxhdqej30tc06n74t.jpg)

##### 上图用红线覆盖的是一排点，红线将其分为 $11$ 组字符
##### ②下面这个是字符匹配数字或加号：
```cpp
for(int i=1;i<=ci;i++){
	for(int j=0;j<11;j++){
		if(shu[j]==a[i]){                 //string判断相等
			a1[++k1]=j;                   //将对应的数字存到数组中(这里也可以直接算出加数与被加数，只要找到加号即可)
			break;
		}
	}
}
```
##### ③下面是算出加数与被加数：(注意加号的位置)
```cpp
int flag=0;                              		//开标记，flag=0表示为加数，flag=1表示为被加数。
int ans1=0,ans2=0;                       		//存储加数与被加数
for(int i=1;i<=k1;i++){
	if(a1[i]==10) flag=1;                		//这里用10表示加号
	if(a1[i]!=10&&flag==0) ans1=ans1*10+a1[i];   //算加数
	if(flag==1&&a1[i]!=10) ans2=ans2*10+a1[i];   //算被加数
}
```
#### 最后是输出：(也要注意那一排点)
```cpp
while(k){                                   //k为ans1+ans2
	a4[++k4]=k%10;                          //依次存每一位
	k/=10;
}
int ci[80]={0};                             //这个就类似与上面的转换，表示第几组字符的第几个字符
for(int i=1;i<=7;i++){                          
	for(int j=k4;j>=1;j--){
		for(int k=ci[j];k<ci[j]+5;k++) printf("%c",shu[a4[j]][k]);	//一组为5个
		if(j!=1) printf(".");               //注意最后一组后面没有点
		ci[j]+=5;
	}
	printf("\n");
}
```
# 代码实现

ps:下面是我丑陋的代码(注意数组的范围，我的是随便写的)

```cpp
#include<bits/stdc++.h>
using namespace std;
string shu[15]={
"xxxxxx...xx...xx...xx...xx...xxxxxx",
"....x....x....x....x....x....x....x",
"xxxxx....x....xxxxxxx....x....xxxxx",
"xxxxx....x....xxxxxx....x....xxxxxx",
"x...xx...xx...xxxxxx....x....x....x",
"xxxxxx....x....xxxxx....x....xxxxxx",
"xxxxxx....x....xxxxxx...xx...xxxxxx",
"xxxxx....x....x....x....x....x....x",
"xxxxxx...xx...xxxxxxx...xx...xxxxxx",
"xxxxxx...xx...xxxxxx....x....xxxxxx",
".......x....x..xxxxx..x....x......."};
string ss[800];
int a1[1000]={0},a2[1000]={0},a3[1000]={0},a4[1000]={0};
int k1=0,k2=0,k3=0,k4=0;
string a[1000];
void read(){
	for(int i=1;i<=7;i++) cin>>ss[i];
}
void print(int k){
	while(k){
		a4[++k4]=k%10;
		k/=10;
	}
	int ci[80]={0};
	for(int i=1;i<=7;i++){
		for(int j=k4;j>=1;j--){
			for(int k=ci[j];k<ci[j]+5;k++){
				printf("%c",shu[a4[j]][k]);
				
			}
			if(j!=1) printf(".");
			ci[j]+=5;
		}
		printf("\n");
	}
}
void change(){
	int ci=0;
	for(int i=1;i<=7;i++){
		ci=0;
		int kkk=ss[i].length();
		for(int j=0;j<kkk;j+=6){
			ci++;
			a[ci]+=ss[i].substr(j,5);
		}
	}
	for(int i=1;i<=ci;i++){
		for(int j=0;j<11;j++){
			if(shu[j]==a[i]){
				a1[++k1]=j;
				break;
			}
		}
	}
	int flag=0;
	int ans1=0,ans2=0;
	for(int i=1;i<=k1;i++){
    	if(a1[i]==10) flag=1;
		if(a1[i]!=10&&flag==0) ans1=ans1*10+a1[i];
		if(flag==1&&a1[i]!=10) ans2=ans2*10+a1[i];
	}
	print(ans1+ans2);
}
int main(){
	read();
	change();
	return 0;
}
```
# 解题反思
#### 这其实就是暴力，但是要注意一些细节，以理性的角度分析并实现暴力，只是这道题只有两个数字相加，不然可能更难实现，~~string 大法好~~。

---

## 作者：Mr_浓氨 (赞：2)

这道题我一看，哇，省选题，我真的是吓到了，因为我是蒟蒻，然而，我仔细地做了一下这道题，发现特别有意思，就渐渐迷上了他，~~最后嫁给了他~~，QAQ，肯定不是这样的，好吧，我来好好讲一下我的做法，这道题分三个比较重要的部分，解读读入，计算a+b（~~我认为这是最难的部分QAQ~~），最后就是编码输出，这是什么意思，就是把读入的结果转换为两个数字，将这两个数字加在一起，将得到的结果转换为ASCll 码的形式，最后输出。

接下来在代码中解释

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<string>
#define ll long long
using namespace std;
string num[11] = {  ("xxxxxx...xx...xx...xx...xx...xxxxxx"),
					("....x....x....x....x....x....x....x"),
				    ("xxxxx....x....xxxxxxx....x....xxxxx"),
					("xxxxx....x....xxxxxx....x....xxxxxx"),
					("x...xx...xx...xxxxxx....x....x....x"),
					("xxxxxx....x....xxxxx....x....xxxxxx"),
					("xxxxxx....x....xxxxxx...xx...xxxxxx"),
					("xxxxx....x....x....x....x....x....x"),
					("xxxxxx...xx...xxxxxxx...xx...xxxxxx"),
					("xxxxxx...xx...xxxxxx....x....xxxxxx"),
					(".......x....x..xxxxx..x....x......."),
};//首先进行的是打表工作，将0--9与加号进行打表
string dr[8];
int judge(int x)
{
	for (int j = 0;j <= 11;j++)
	{
		ll flag = 0, z = 0;
		for (int k = 1;k <= 7;k++)
		{
			for (int i = x;i <= x + 4;i++)
			{
				if (dr[k][i] == num[j][z])
				{
					z++;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			if (flag == 1)
			{
				break;
			}
		}
		if (flag == 1)
		{
			continue;
		}
		else
		{
			return j;
		}
	}
	return 10;
}//这个函数便是判断一个区间内的是什么符号QAQ有点果仁
inline void change(ll x)
{
	ll na = x / 10, lx = 1, llx = 1;
	while (na > 0)
	{
		lx *= 10;
		na /= 10;
		llx++;
	}
	int numa[100001];
	memset(numa, 0, sizeof(numa));
	na = x;
	for (int u = 1;u <= llx;u++)
	{
		numa[u] = na / lx;
		na %= lx;
		lx /= 10;
	}
	for (int i = 0;i < 35;i += 5)
	{
		for (int nn = 1;nn <= llx;nn++)
		{
			for (int j = i;j <= i + 4;j++)
			{
				int mumu = numa[nn];
				printf("%c", num[mumu][j]);
			}
			if (nn != llx)
			{
				printf(".");
			}
		}
		printf("\n");
	}
}//这个就是讲答案进行编辑加密
ll work(ll x,ll y)
{
	return x+y;
}//这个就是a+b，也就是最难的一步QAQ
int main()
{
	for (int i = 1;i <= 7;i++)
	{
		cin >> dr[i];
	}
	int flag = 0, x = 0, g = 0;
	for (ll i = 0;i < dr[1].length();i+=6)
	{
		int ds = judge(i);
		if (ds == 10)
		{
			flag = 1;
		}
		if (!flag)
		{
			x = x * 10 + ds;
		}
		else
		{
			if (ds != 10)
			{
				g = g * 10 + ds;
			}
		}
	}//判断加号前后的值
	change(work(x,g));//同时进行编码与work；
	system("pause");//然而我用的VS所以要加这个神奇的东西
	return 20030711;//我的质数生日便是我的信仰
}
```

---

## 作者：huwenbo (赞：2)

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[10];
string k[7];
int al[2],oi[20],c;//al[0]为加号前的加数，al[1]为另一个加数

int main(){
    a[0]="xxxxxx...xx...xx...xx...xx...xxxxxx";
    a[1]="....x....x....x....x....x....x....x";
    a[2]="xxxxx....x....xxxxxxx....x....xxxxx";
    a[3]="xxxxx....x....xxxxxx....x....xxxxxx";
    a[4]="x...xx...xx...xxxxxx....x....x....x";
    a[5]="xxxxxx....x....xxxxx....x....xxxxxx";
    a[6]="xxxxxx....x....xxxxxx...xx...xxxxxx";
    a[7]="xxxxx....x....x....x....x....x....x";
    a[8]="xxxxxx...xx...xxxxxxx...xx...xxxxxx";
    a[9]="xxxxxx...xx...xxxxxx....x....xxxxxx";//保存每一个数字所构成的5*7方阵
    for(int i=0;i<7;i++){
        cin>>k[i];
    }
    int u=0;
    for(int i=0;i<k[0].length();i+=6){
        string p;//p为截取每一块的数字
        bool flag=false;
        for(int j=0;j<7;j++){
            p+=k[j].substr(i,5);
        }
        for(int j=0;j<=9;j++){
            if(p==a[j]){
                al[u]*=10;
                al[u]+=j;
                flag=true;
                break;
            }
        }
        if(!flag) u++;//否则为加号
    }
    al[0]=al[0]+al[1];//相加
    for(long long i=10000000000;i>=1;i/=10){//分解每一位
        if(al[0]>=i){
            oi[++c]=al[0]/i%10;
        }
    }
    for(int i=0;i<7;i++){//输出每一个数字
        for(int j=1;j<=c;j++){
            for(int x=i*5;x<(i+1)*5;x++){
                cout<<a[oi[j]][x];
            }
            if(j!=c) cout<<".";
        }
        cout<<endl;
    }
    
    return 0;
}
```

---

## 作者：月がきれい (赞：1)

- 这是作为萌新的笔者第一次写题解，希望予以通过
- 这道题从黑题调到了紫题，可个人还是认为凭难了，此题难度应该和noip2017day1t2差不多难度，详见[时间复杂度](https://www.luogu.org/problemnew/show/P3952)

- ### - 注意，这是一道大模拟，需要持之以恒的优良品质

- ### - 主要思想：将输入字符转化成数字相加再转化为字符输出
- 个人认为笔者代码虽然长，但是通俗易懂，便于初学模拟的oier们理解
- 接下来就是你们最爱的代码,欢迎各位大佬指点，请不要复制题，个人认为这道题十分锻炼写代码能力，笔者写了大约45min
```
#include<bits/stdc++.h>
using namespace std;
string num[15][8],number[15][8],st,ansst[15][8];
int length,ans1,ans2,ans,top;
int main(){

	num[0][1]="xxxxx";
	num[0][2]="x...x";
	num[0][3]="x...x";
	num[0][4]="x...x";
	num[0][5]="x...x";
	num[0][6]="x...x";
	num[0][7]="xxxxx";
	
	num[1][1]="....x";
	num[1][2]="....x";
	num[1][3]="....x";
	num[1][4]="....x";
	num[1][5]="....x";
	num[1][6]="....x";
	num[1][7]="....x";
	
	num[2][1]="xxxxx";
	num[2][2]="....x";
	num[2][3]="....x";
	num[2][4]="xxxxx";
	num[2][5]="x....";
	num[2][6]="x....";
	num[2][7]="xxxxx";
	
	num[3][1]="xxxxx";
	num[3][2]="....x";
	num[3][3]="....x";
	num[3][4]="xxxxx";
	num[3][5]="....x";
	num[3][6]="....x";
	num[3][7]="xxxxx";
	
	num[4][1]="x...x";
	num[4][2]="x...x";
	num[4][3]="x...x";
	num[4][4]="xxxxx";
	num[4][5]="....x";
	num[4][6]="....x";
	num[4][7]="....x";
	
	num[5][1]="xxxxx";
	num[5][2]="x....";
	num[5][3]="x....";
	num[5][4]="xxxxx";
	num[5][5]="....x";
	num[5][6]="....x";
	num[5][7]="xxxxx";
	
	num[6][1]="xxxxx";
	num[6][2]="x....";
	num[6][3]="x....";
	num[6][4]="xxxxx";
	num[6][5]="x...x";
	num[6][6]="x...x";
	num[6][7]="xxxxx";
	
	num[7][1]="xxxxx";
	num[7][2]="....x";
	num[7][3]="....x";
	num[7][4]="....x";
	num[7][5]="....x";
	num[7][6]="....x";
	num[7][7]="....x";
	
	num[8][1]="xxxxx";
	num[8][2]="x...x";
	num[8][3]="x...x";
	num[8][4]="xxxxx";
	num[8][5]="x...x";
	num[8][6]="x...x";
	num[8][7]="xxxxx";
	
	num[9][1]="xxxxx";
	num[9][2]="x...x";
	num[9][3]="x...x";
	num[9][4]="xxxxx";
	num[9][5]="....x";
	num[9][6]="....x";
	num[9][7]="xxxxx";
	
	num[10][1]=".....";
	num[10][2]="..x..";
	num[10][3]="..x..";
	num[10][4]="xxxxx";
	num[10][5]="..x..";
	num[10][6]="..x..";
	num[10][7]=".....";
    
    //将0-9和+存在num里
    
	for(int i=1;i<=7;i++)
	{
		cin>>st;
		length=0;
		for(int j=0;j<st.size();j+=6)
		{
			length++;
			for(int k=j;k<=j+4;k++)
				number[length][i]=number[length][i]+st[k];
		}
	}
    
    //读入并存在number里
    
	bool flag=0;
    //判断+，+前flag=0，记在ans1里，+后flag=1，记在ans2里
	for(int i=1;i<=(st.size()+1)/6;i++)
	{
		for(int j=0;j<=10;j++)
		{
			if (number[i][1]==num[j][1])
			if (number[i][2]==num[j][2])
			if (number[i][3]==num[j][3])
			if (number[i][4]==num[j][4])
			if (number[i][5]==num[j][5])
			if (number[i][6]==num[j][6])
			if (number[i][7]==num[j][7])
            //此处大可以循环优化
			{
				if (j==10) flag=1;
				else 
				{
					if (flag==0) ans1=ans1*10+j;
					else ans2=ans2*10+j; 
				}
			}
		}
	}
	ans=ans1+ans2;
    
    //将输入字符转换为数字并计算答案
    
	while(ans>0)
	{
		top++;
		int x=ans%10;
		ansst[top][1]=num[x][1];
		ansst[top][2]=num[x][2];
		ansst[top][3]=num[x][3];
		ansst[top][4]=num[x][4];
		ansst[top][5]=num[x][5];
		ansst[top][6]=num[x][6];
		ansst[top][7]=num[x][7];
        //此处大可以循环优化
		ans/=10;
	}
    
    //将数字答案转换成字符
    
	for(int k=1;k<=7;k++)
	{
		for(int j=top;j>=1;j--)
		{
			if (j!=top) cout<<'.';
			cout<<ansst[j][k];
		}
		cout<<endl;
	}
    
    //输出答案
    
	return 0;
}
```
- 时间比较快2-3ms
- 希望给予通过，谢谢

---

## 作者：Y_inG (赞：1)

真不知道这题为毛是黑题（现在紫题了）。。。。。（打表那么好打）

~~虽然打了两小时~~

不过毕竟是黑题还是有那么一些坑点的（吧）

像删除前导零，还有每个数字之间的'.'

都比较难处理

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[7][150];
int aa,bb,cc,x,xx,yy;
int v[10];
int print(int);
int zh(int i)
{
    if(a[0][i]=='.'&&a[0][i+1]=='.'&&a[0][i+2]=='.'&&a[0][i+3]=='.'&&a[0][i+4]=='x'&&
       a[1][i]=='.'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='x'&&
       a[2][i]=='.'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='x'&&
       a[3][i]=='.'&&a[3][i+1]=='.'&&a[3][i+2]=='.'&&a[3][i+3]=='.'&&a[3][i+4]=='x'&&
       a[4][i]=='.'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='.'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='.'&&a[6][i+1]=='.'&&a[6][i+2]=='.'&&a[6][i+3]=='.'&&a[6][i+4]=='x'
       )
       return 1;
    else if(a[0][i]=='x'&&a[0][i+1]=='x'&&a[0][i+2]=='x'&&a[0][i+3]=='x'&&a[0][i+4]=='x'&&
       a[1][i]=='.'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='x'&&
       a[2][i]=='.'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='x'&&
       a[3][i]=='x'&&a[3][i+1]=='x'&&a[3][i+2]=='x'&&a[3][i+3]=='x'&&a[3][i+4]=='x'&&
       a[4][i]=='x'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='.'&&
       a[5][i]=='x'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='.'&&
       a[6][i]=='x'&&a[6][i+1]=='x'&&a[6][i+2]=='x'&&a[6][i+3]=='x'&&a[6][i+4]=='x'
       )
       return 2;
    else if(a[0][i]=='x'&&a[0][i+1]=='x'&&a[0][i+2]=='x'&&a[0][i+3]=='x'&&a[0][i+4]=='x'&&
       a[1][i]=='.'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='x'&&
       a[2][i]=='.'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='x'&&
       a[3][i]=='x'&&a[3][i+1]=='x'&&a[3][i+2]=='x'&&a[3][i+3]=='x'&&a[3][i+4]=='x'&&
       a[4][i]=='.'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='.'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='x'&&a[6][i+1]=='x'&&a[6][i+2]=='x'&&a[6][i+3]=='x'&&a[6][i+4]=='x'
       )
       return 3;
    else if(a[0][i]=='x'&&a[0][i+1]=='.'&&a[0][i+2]=='.'&&a[0][i+3]=='.'&&a[0][i+4]=='x'&&
       a[1][i]=='x'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='x'&&
       a[2][i]=='x'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='x'&&
       a[3][i]=='x'&&a[3][i+1]=='x'&&a[3][i+2]=='x'&&a[3][i+3]=='x'&&a[3][i+4]=='x'&&
       a[4][i]=='.'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='.'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='.'&&a[6][i+1]=='.'&&a[6][i+2]=='.'&&a[6][i+3]=='.'&&a[6][i+4]=='x'
       )
       return 4;
    else if(a[0][i]=='x'&&a[0][i+1]=='x'&&a[0][i+2]=='x'&&a[0][i+3]=='x'&&a[0][i+4]=='x'&&
       a[1][i]=='x'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='.'&&
       a[2][i]=='x'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='.'&&
       a[3][i]=='x'&&a[3][i+1]=='x'&&a[3][i+2]=='x'&&a[3][i+3]=='x'&&a[3][i+4]=='x'&&
       a[4][i]=='.'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='.'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='x'&&a[6][i+1]=='x'&&a[6][i+2]=='x'&&a[6][i+3]=='x'&&a[6][i+4]=='x'
       )
       return 5;
    else if(a[0][i]=='x'&&a[0][i+1]=='x'&&a[0][i+2]=='x'&&a[0][i+3]=='x'&&a[0][i+4]=='x'&&
       a[1][i]=='x'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='.'&&
       a[2][i]=='x'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='.'&&
       a[3][i]=='x'&&a[3][i+1]=='x'&&a[3][i+2]=='x'&&a[3][i+3]=='x'&&a[3][i+4]=='x'&&
       a[4][i]=='x'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='x'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='x'&&a[6][i+1]=='x'&&a[6][i+2]=='x'&&a[6][i+3]=='x'&&a[6][i+4]=='x'
       )
       return 6;
    else if(a[0][i]=='x'&&a[0][i+1]=='x'&&a[0][i+2]=='x'&&a[0][i+3]=='x'&&a[0][i+4]=='x'&&
       a[1][i]=='.'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='x'&&
       a[2][i]=='.'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='x'&&
       a[3][i]=='.'&&a[3][i+1]=='.'&&a[3][i+2]=='.'&&a[3][i+3]=='.'&&a[3][i+4]=='x'&&
       a[4][i]=='.'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='.'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='.'&&a[6][i+1]=='.'&&a[6][i+2]=='.'&&a[6][i+3]=='.'&&a[6][i+4]=='x'
       )
       return 7;
    else if(a[0][i]=='x'&&a[0][i+1]=='x'&&a[0][i+2]=='x'&&a[0][i+3]=='x'&&a[0][i+4]=='x'&&
       a[1][i]=='x'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='x'&&
       a[2][i]=='x'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='x'&&
       a[3][i]=='x'&&a[3][i+1]=='x'&&a[3][i+2]=='x'&&a[3][i+3]=='x'&&a[3][i+4]=='x'&&
       a[4][i]=='x'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='x'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='x'&&a[6][i+1]=='x'&&a[6][i+2]=='x'&&a[6][i+3]=='x'&&a[6][i+4]=='x'
       )
       return 8;
    else if(a[0][i]=='x'&&a[0][i+1]=='x'&&a[0][i+2]=='x'&&a[0][i+3]=='x'&&a[0][i+4]=='x'&&
       a[1][i]=='x'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='x'&&
       a[2][i]=='x'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='x'&&
       a[3][i]=='x'&&a[3][i+1]=='x'&&a[3][i+2]=='x'&&a[3][i+3]=='x'&&a[3][i+4]=='x'&&
       a[4][i]=='.'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='.'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='x'&&a[6][i+1]=='x'&&a[6][i+2]=='x'&&a[6][i+3]=='x'&&a[6][i+4]=='x'
       )
       return 9;
    else if(a[0][i]=='x'&&a[0][i+1]=='x'&&a[0][i+2]=='x'&&a[0][i+3]=='x'&&a[0][i+4]=='x'&&
       a[1][i]=='x'&&a[1][i+1]=='.'&&a[1][i+2]=='.'&&a[1][i+3]=='.'&&a[1][i+4]=='x'&&
       a[2][i]=='x'&&a[2][i+1]=='.'&&a[2][i+2]=='.'&&a[2][i+3]=='.'&&a[2][i+4]=='x'&&
       a[3][i]=='x'&&a[3][i+1]=='.'&&a[3][i+2]=='.'&&a[3][i+3]=='.'&&a[3][i+4]=='x'&&
       a[4][i]=='x'&&a[4][i+1]=='.'&&a[4][i+2]=='.'&&a[4][i+3]=='.'&&a[4][i+4]=='x'&&
       a[5][i]=='x'&&a[5][i+1]=='.'&&a[5][i+2]=='.'&&a[5][i+3]=='.'&&a[5][i+4]=='x'&&
       a[6][i]=='x'&&a[6][i+1]=='x'&&a[6][i+2]=='x'&&a[6][i+3]=='x'&&a[6][i+4]=='x'
       )
       return 0;
}//以上打表存数字（别问我为什么不用字符串，因为作为蒟蒻我不会）
int print(int i)
{
    int w=1;
    for(int k=1;k<=7;k++)
    {
        for(int vv=i-1;vv>=0;vv--)
        {
            if(v[vv]!=0)
                w=0;
            if(w==0)
            {
                if(v[vv]==0)
                {
                    if(k==1)
                    cout<<"xxxxx";
                    else if(k==2)
                    cout<<"x...x";
                    else if(k==3)
                    cout<<"x...x";
                    else if(k==4)
                    cout<<"x...x";
                    else if(k==5)
                    cout<<"x...x";
                    else if(k==6)
                    cout<<"x...x";
                    else if(k==7)
                    cout<<"xxxxx";
                }
                else if(v[vv]==1)
                {
                    if(k==1)
                    cout<<"....x";
                    else if(k==2)
                    cout<<"....x";
                    else if(k==3)
                    cout<<"....x";
                    else if(k==4)
                    cout<<"....x";
                    else if(k==5)
                    cout<<"....x";
                    else if(k==6)
                    cout<<"....x";
                    else if(k==7)
                    cout<<"....x";
                }
                else if(v[vv]==2)
                {
                    if(k==1)
                    cout<<"xxxxx";
                    else if(k==2)
                    cout<<"....x";
                    else if(k==3)
                    cout<<"....x";
                    else if(k==4)
                    cout<<"xxxxx";
                    else if(k==5)
                    cout<<"x....";
                    else if(k==6)
                    cout<<"x....";
                    else if(k==7)
                    cout<<"xxxxx";
                }
                else if(v[vv]==3)
                {
                    if(k==1)
                    cout<<"xxxxx";
                    else if(k==2)
                    cout<<"....x";
                    else if(k==3)
                    cout<<"....x";
                    else if(k==4)
                    cout<<"xxxxx";
                    else if(k==5)
                    cout<<"....x";
                    else if(k==6)
                    cout<<"....x";
                    else if(k==7)
                    cout<<"xxxxx";
                }
                else if(v[vv]==4)
                {
                    if(k==1)
                    cout<<"x...x";
                    else if(k==2)
                    cout<<"x...x";
                    else if(k==3)
                    cout<<"x...x";
                    else if(k==4)
                    cout<<"xxxxx";
                    else if(k==5)
                    cout<<"....x";
                    else if(k==6)
                    cout<<"....x";
                    else if(k==7)
                    cout<<"....x";
                }
                else if(v[vv]==5)
                {
                    if(k==1)
                    cout<<"xxxxx";
                    else if(k==2)
                    cout<<"x....";
                    else if(k==3)
                    cout<<"x....";
                    else if(k==4)
                    cout<<"xxxxx";
                    else if(k==5)
                    cout<<"....x";
                    else if(k==6)
                    cout<<"....x";
                    else if(k==7)
                    cout<<"xxxxx";
                }
                else if(v[vv]==6)
                {
                    if(k==1)
                    cout<<"xxxxx";
                    else if(k==2)
                    cout<<"x....";
                    else if(k==3)
                    cout<<"x....";
                    else if(k==4)
                    cout<<"xxxxx";
                    else if(k==5)
                    cout<<"x...x";
                    else if(k==6)
                    cout<<"x...x";
                    else if(k==7)
                    cout<<"xxxxx";
                }
                else if(v[vv]==7)
                {
                    if(k==1)
                    cout<<"xxxxx";
                    else if(k==2)
                    cout<<"....x";
                    else if(k==3)
                    cout<<"....x";
                    else if(k==4)
                    cout<<"....x";
                    else if(k==5)
                    cout<<"....x";
                    else if(k==6)
                    cout<<"....x";
                    else if(k==7)
                    cout<<"....x";
                }
                else if(v[vv]==8)
                {
                    if(k==1)
                    cout<<"xxxxx";
                    else if(k==2)
                    cout<<"x...x";
                    else if(k==3)
                    cout<<"x...x";
                    else if(k==4)
                    cout<<"xxxxx";
                    else if(k==5)
                    cout<<"x...x";
                    else if(k==6)
                    cout<<"x...x";
                    else if(k==7)
                    cout<<"xxxxx";
                }
                else if(v[vv]==9)
                {
                    if(k==1)
                    cout<<"xxxxx";
                    else if(k==2)
                    cout<<"x...x";
                    else if(k==3)
                    cout<<"x...x";
                    else if(k==4)
                    cout<<"xxxxx";
                    else if(k==5)
                    cout<<"....x";
                    else if(k==6)
                    cout<<"....x";
                    else if(k==7)
                    cout<<"xxxxx";
                }
                if(vv!=0)
                    cout<<'.';//这是数字之间的'.'
            }
        }
        cout<<endl;
    }
        
}
int main()
{
    for(int i=0;i<7;i++)
        cin>>a[i];
    for(int i=0;i<strlen(a[0]);i+=6)
    {
        if(a[0][i]=='.'&&a[0][i+4]=='.')
            x=1,i+=6;
        if(x==0)
            aa*=10,aa+=zh(i);
        else if(x==1)
            bb*=10,bb+=zh(i);//跳过加号
    }
    int cc=aa+bb,i=0;
    while(cc>0)
    {
        v[i++]=cc%10;
        cc/=10;
    }//算位数
    print(i);//算完就输出
}
```

---

## 作者：Eason_AC (赞：0)

暴力大法吼！

虽然码量有$4kB$，但思路应该是比较清楚的。

---

首先我们来观察一下这些字符：

```
....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.......xxxxx.xxxxx.xxxxx
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.......xxxxx.xxxxx.xxxxx
```
然后我们把这些数分成5部分：
```
....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.......xxxxx.xxxxx.xxxxx	第1部分
-----------------------------------------------------------------
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x	第2部分
-----------------------------------------------------------------
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx.x...x	第3部分
-----------------------------------------------------------------
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x	第4部分
-----------------------------------------------------------------
....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.......xxxxx.xxxxx.xxxxx	第5部分
```
然后我们便可发现这样的规律（单独放一部分讲算了QAQ）：

---

$1$：第一部分只有右边有阴影，第二部分也只有右边有阴影，第三部分还是只有右边有阴影，第四部分和第五部分同。  
$2$：第一部分所有格子都有阴影，第二部分只有右边有阴影，第三部分所有格子都有阴影，第四部分只有左边有阴影，第五部分所有格子都有阴影。  
$3$：第一部分所有格子都有阴影，第二部分只有右边有阴影，第三部分所有格子都有阴影，第四部分只有右边有阴影，第五部分所有格子都有阴影。  
$4$：第一部分只有左边和右边有阴影，第二部分只有右边有阴影，第三部分所有格子都有阴影，第四部分只有右边有阴影，第五部分只有右边有阴影。  
$5$：第一部分所有格子都有阴影，第二部分只有左边有阴影，第三部分所有格子都有阴影，第四部分只有右边有阴影，第五部分所有格子都有阴影。  
$6$：第一部分所有格子都有阴影，第二部分只有左边有阴影，第三部分所有格子都有阴影，第四部分只有左边和右边有阴影，第五部分所有格子都有阴影。  
$7$：第一部分所有格子都有阴影，第二部分只有右边有阴影，第三部分只有右边有阴影，第四部分和第五部分同。  
$8$：第一部分所有格子都有阴影，第二部分只有左边和右边有阴影，第三部分所有格子都有阴影，第四部分只有左边和右边有阴影，第五部分所有格子都有阴影。  
$9$：第一部分所有格子都有阴影，第二部分只有左边和右边有阴影，第三部分所有格子都有阴影，第四部分只有右边有阴影，第五部分所有格子都有阴影。  
$0$：第一部分所有格子都有阴影，第二部分只有左边和右边有阴影，第三部分只有左边和右边有阴影，第四部分只有左边和右边有阴影，第五部分所有格子都有阴影。  
注意还要考虑一下$+$的情况：第一部分没有阴影，第二部分只有中间有阴影，第三部分所有格子都有阴影，第四部分只有中间有阴影，第五部分没有阴影。

---

然后考虑一下加法的计算。我们先找到这样的关键字符：

设有一个$7*5$的矩阵（对于每个元素的下标$A_{i,j}$，有$i\in[1,7],j\in[1,5]$）。

则其中的关键点有：$A_{1,1},A_{2,1},A_{4.1},A_{5,1},A_{7,1},A_{4,2} ~or~A_{4,4},A_{1,5},A_{2,5},A_{4,5},A_{5,5},A_{7.5}$。如果你理解了上面的内容，这段理解应该是不难的，凡是**满足且仅满足**以下条件的都必定是对应的数：

$1$：$A_{1,5}=A_{2,5}=A_{4,5}=A_{5,5}=A_{7,5}=$'$x$'。   
$2$：$A_{1,1}=A_{4,1}=A_{5,1}=A_{7,1}=A_{4,2}=A_{4,4}=A_{1,5}=A_{2,5}=A_{4,5}=A_{7,5}=$'$x$'。  
$3$：$A_{1,1}=A_{4,1}=A_{7,1}=A_{4,2}=A_{4,4}=A_{1,5}=A_{2,5}=A_{4,5}=A_{5,5}=A_{7,5}=$'$x$'。  
$4$：$A_{1,1}=A_{2,1}=A_{4,1}=A_{4,2}=A_{4,4}=A_{1,5}=A_{2,5}=A_{4,5}=A_{5,5}=A_{7,5}=$'$x$'。  
$5$：$A_{1,1}=A_{2,1}=A_{4,1}=A_{7,1}=A_{4,2}=A_{4,4}=A_{1,5}=A_{4,5}=A_{5,5}=A_{7,5}=$'$x$'。  
$6$：$A_{1,1}=A_{2,1}=A_{4,1}=A_{5,1}=A_{7,1}=A_{4,2}=A_{4,4}=A_{1,5}=A_{4,5}=A_{5,5}=A_{7,5}=$'$x$'。  
$7$：$A_{1,1}=A_{1,5}=A_{2,5}=A_{4,5}=A_{7,5}=$'$x$'。  
$8$：$A_{1,1}=A_{2,1}=A_{4,1}=A_{5,1}=A_{7,1}=A_{4,2}=A_{4,4}=A_{1,5}=A_{2,5}=A_{4,5}=A_{5,5}=A_{7,5}=$'$x$'。
$9$：$A_{1,1}=A_{2,1}=A_{4,1}=A_{7,1}=A_{4,2}=A_{4,4}=A_{1,5}=A_{2,5}=A_{4,5}=A_{5,5}=A_{7,5}=$'$x$'。
$0$：$A_{1,1}=A_{2,1}=A_{4,1}=A_{7,1}=A_{1,5}=A_{2,5}=A_{4,5}=A_{5,5}=A_{7,5}=$'$x$'。  
$+$：$A_{4,1}=A_{4,2}=A_{4,4}=A_{4,5}=$'$x$'。

数字的存储就类似于快读的方法就行，还有，碰到加号要重新计算，再和前面所得的数做加法。

最后输出的时候按照最开始讲的规律来输出就行了，注意应处理每行，在处理每个字符，每行应该换行！

---

讲了这么多，最后贴个代码仅供参考：
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char a[8][307];
int b[3], flag = 1, flg[11], nnn[15];

int main() {
	for(int i = 0; i < 7; ++i)
		scanf("%s", a[i]);
	int len = strlen(a[1]);
	for(int i = 0; i < len; i += 6) {
//		for(int j = 0; j < 7; ++j)
//			printf("%c\n", a[j][i]);
//		for(int j = 0; j < 7; ++j)
//			printf("%c\n", a[j][ i + 2])
//		puts("");
		memset(flg, 0, sizeof(flg));
//		printf("%c %c %c %c %c %c %c %c %c\n", a[0][i], a[1][i], a[3][i], a[4][i], a[6][i], a[1][i + 2], a[1][i + 4], a[4][i + 4], a[3][i + 1]);
		if(a[1][i + 2] == 'x') {
			flag = 2;
			continue;
		}
		if(a[0][i] == '.' && a[1][i] == '.' && a[3][i] == '.' && a[4][i] == '.' && a[6][i] == '.' && a[0][i + 4] == 'x' && a[1][i + 4] == 'x' && a[4][i + 4] == 'x' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 1;
		else if(a[0][i] == 'x' && a[1][i] == '.' && a[3][i] == 'x' && a[4][i] == 'x' && a[6][i] == 'x' && a[0][i + 4] == 'x' && a[1][i + 4] == 'x' && a[4][i + 4] == '.' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 2;
		else if(a[0][i] == 'x' && a[1][i] == '.' && a[3][i] == 'x' && a[4][i] == '.' && a[6][i] == 'x' && a[0][i + 4] == 'x' && a[1][i + 4] == 'x' && a[4][i + 4] == 'x' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 3;
		else if(a[0][i] == 'x' && a[1][i] == 'x' && a[3][i] == 'x' && a[4][i] == '.' && a[6][i] == '.' && a[0][i + 4] == 'x' && a[1][i + 4] == 'x' && a[4][i + 4] == 'x' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 4;
		else if(a[0][i] == 'x' && a[1][i] == 'x' && a[3][i] == 'x' && a[4][i] == '.' && a[6][i] == 'x' && a[0][i + 4] == 'x' && a[1][i + 4] == '.' && a[4][i + 4] == 'x' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 5;
		else if(a[0][i] == 'x' && a[1][i] == 'x' && a[3][i] == 'x' && a[4][i] == 'x' && a[6][i] == 'x' && a[0][i + 4] == 'x' && a[1][i + 4] == '.' && a[4][i + 4] == 'x' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 6;
		else if(a[0][i] == 'x' && a[1][i] == '.' && a[3][i] == '.' && a[4][i] == '.' && a[6][i] == '.' && a[0][i + 4] == 'x' && a[1][i + 4] == 'x' && a[4][i + 4] == 'x' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 7;
		else if(a[0][i] == 'x' && a[1][i] == 'x' && a[3][i + 2] == 'x' && a[3][i] == 'x' && a[4][i] == 'x' && a[6][i] == 'x' && a[0][i + 4] == 'x' && a[1][i + 4] == 'x' && a[4][i + 4] == 'x' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 8;
		else if(a[0][i] == 'x' && a[1][i] == 'x' && a[3][i] == 'x' && a[4][i] == '.' && a[6][i] == 'x' && a[0][i + 4] == 'x' && a[1][i + 4] == 'x' && a[4][i + 4] == 'x' && a[6][i + 4] == 'x')
			b[flag] = b[flag] * 10 + 9;
		else 
			b[flag] = b[flag] * 10;
		
	}
//	printf("%d ", b[1] + b[2]);
	int ans = b[1] + b[2], tmp = ans, cnt = 0;
	while(tmp) {
		nnn[++cnt] = tmp % 10;
		tmp /= 10;
	}
	for(int i = 1; i <= 7; ++i) {
		for(int j = cnt; j >= 1; --j) {
			if(j != cnt)	printf(".");
			if(i == 1) {
				switch(nnn[j]) {
					case 0: case 2: case 3: case 5: case 6: case 7: case 8: case 9: {
						printf("xxxxx");
						break;
					}
					case 1: {
						printf("....x");
						break;
					}
					case 4: {
						printf("x...x");
						break;
					}
				}
			} else if(i == 2 || i == 3) {
				switch(nnn[j]) {
					case 0: case 4: case 8: case 9: {
						printf("x...x");
						break;
					}
					case 1: case 2: case 3: case 7: {
						printf("....x");
						break;
					}
					case 5: case 6: {
						printf("x....");
						break;
					}
				}
			} else if(i == 4) {
				switch(nnn[j]) {
					case 1: case 7: {
						printf("....x");
						break;
					}
					case 2: case 3: case 4: case 5: case 6: case 8: case 9: {
						printf("xxxxx");
						break;
					}
					case 0: {
						printf("x...x");
						break;
					}
				}
			} else if(i == 5 || i == 6) {
				switch(nnn[j]) {
					case 0: case 6: case 8: {
						printf("x...x");
						break;
					}
					case 1: case 3: case 4: case 5: case 7: case 9: {
						printf("....x");
						break;
					}
					case 2: {
						printf("x....");
						break;
					}
				}
			} else {
				switch(nnn[j]) {
					case 0: case 2: case 3: case 5: case 6: case 8: case 9: {
						printf("xxxxx");
						break;
					}
					case 1: case 4: case 7:{
						printf("....x");
						break;
					}
				}
			}
		}
		puts("");
	}
	return 0;
}
//防盗水印：UID=112917
//P.s. 请忽略被注释的调试部分。
```
打本题代码和写本题题解实属不易，若有纰漏，还请大佬多指点！

记得点个赞哦！qwq

$\text{-Eason On 2019.11.9 5.20p.m. to 11.53p.m.}$

---

## 作者：盗梦黑客 (赞：0)

如果我没有记错的话，这道题最近经历了由黑题掉到紫题，再掉到黄题的过程……

由于不会map也不会字典树，所以代码写的比较长，足足破了百行。~~打代码加复制粘贴累得要死。~~

首先将字符转化为数字，+号两边分开处理，第一个for循环如判断到+号就退出，进入到第2个for循环。

其次就是本题要解决问题的核心:
# a+b problem
之后7行1行1行地输出，7个for循环，一大堆if。

具体看代码吧
```
#include<bits/stdc++.h>
using namespace std;
char s[10][1000];
int a,b,num[30];
int main()
{
	for(register int i=1;i<=7;++i) scanf("%s",&s[i]);
	int len=strlen(s[1]);
	int just;
	for(register int i=0;i<=len;i+=6)
	{
		if(s[1][i]=='.'&&s[1][i+1]=='.'&&s[1][i+2]=='.'&&s[1][i+3]=='.'&&s[1][i+4]=='.')
		{
			just=i+6;break;
		}
		else if(s[1][i]=='.'&&s[1][i+2]=='.'&&s[1][i+3]=='.'&&s[1][i+1]=='.'&&s[1][i+4]=='x') a=a*10+1;
		else if(s[1][i]=='x'&&s[1][i+4]=='x'&&s[1][i+1]=='.'&&s[1][i+2]=='.'&&s[1][i+3]=='.') a=a*10+4;
		else if(s[7][i]=='.'&&s[7][i+1]=='.'&&s[7][i+2]=='.'&&s[7][i+3]=='.'&&s[7][i+4]=='x') a=a*10+7;
		else if(s[4][i]=='x'&&s[4][i+4]=='x'&&s[4][i+1]=='.'&&s[4][i+2]=='.'&&s[4][i+3]=='.') a=a*10;
		else if(s[5][i]=='x'&&s[5][i+4]=='x')
		{
			if(s[2][i+4]=='.') a=a*10+6;
			else a=a*10+8;
		}
		else if(s[5][i]=='x') a=a*10+2;
		else if(s[2][i]=='x'&&s[2][i+4]=='x') a=a*10+9;
		else if(s[2][i]=='x') a=a*10+5;
		else a=a*10+3;
	}
	for(register int i=just;i<=len;i+=6)
	{
		if(s[1][i]=='.'&&s[1][i+2]=='.'&&s[1][i+3]=='.'&&s[1][i+1]=='.'&&s[1][i+4]=='x') b=b*10+1;
		else if(s[1][i]=='x'&&s[1][i+4]=='x'&&s[1][i+1]=='.'&&s[1][i+2]=='.'&&s[1][i+3]=='.') b=b*10+4;
		else if(s[7][i]=='.'&&s[7][i+1]=='.'&&s[7][i+2]=='.'&&s[7][i+3]=='.'&&s[7][i+4]=='x') b=b*10+7;
		else if(s[4][i]=='x'&&s[4][i+4]=='x'&&s[4][i+1]=='.'&&s[4][i+2]=='.'&&s[4][i+3]=='.') b=b*10;
		else if(s[5][i]=='x'&&s[5][i+4]=='x')
		{
			if(s[2][i+4]=='.') b=b*10+6;
			else b=b*10+8;
		}
		else if(s[5][i]=='x') b=b*10+2;
		else if(s[2][i]=='x'&&s[2][i+4]=='x') b=b*10+9;
		else if(s[2][i]=='x') b=b*10+5;
		else b=b*10+3;
	}
	int c=a+b,n=0;
	while(c)
	{
		num[++n]=c%10;
		c/=10;
	}
	for(register int i=1;(i<<1)<=n;++i) swap(num[i],num[n-i+1]);
	for(register int i=1;i<=n;++i)
	{
		if(num[i]==1) printf("....x");
		else if(num[i]==4) printf("x...x");
		else printf("xxxxx");
		if(i!=n) printf(".");
	} 
	cout<<endl;
	for(register int i=1;i<=n;++i)
	{
		if(num[i]==1||num[i]==2||num[i]==3||num[i]==7) printf("....x");
		else if(num[i]==5||num[i]==6) printf("x....");
		else printf("x...x");
		if(i!=n) printf(".");
	}
	cout<<endl;
	for(register int i=1;i<=n;++i)
	{
		if(num[i]==1||num[i]==2||num[i]==3||num[i]==7) printf("....x");
		else if(num[i]==5||num[i]==6) printf("x....");
		else printf("x...x");
		if(i!=n) printf(".");
	}
	cout<<endl;
	for(register int i=1;i<=n;++i)
	{
		if(num[i]==1||num[i]==7) printf("....x");
		else if(num[i]==0) printf("x...x");
		else printf("xxxxx");
		if(i!=n) printf(".");
	}
	cout<<endl；
	for(register int i=1;i<=n;++i)
	{
		if(num[i]==1||num[i]==3||num[i]==4||num[i]==5||num[i]==7||num[i]==9) printf("....x");
		else if(num[i]==2) printf("x....");
		else printf("x...x");
		if(i!=n) printf(".");
	}
	cout<<endl;
	for(register int i=1;i<=n;++i)
	{
		if(num[i]==1||num[i]==3||num[i]==4||num[i]==5||num[i]==7||num[i]==9) printf("....x");
		else if(num[i]==2) printf("x....");
		else printf("x...x");
		if(i!=n) printf(".");
	}
	cout<<endl;
	for(register int i=1;i<=n;++i)
	{
		if(num[i]==1||num[i]==4||num[i]==7) printf("....x");
		else printf("xxxxx");
		if(i!=n) printf(".");
	}
	cout<<endl;
	return 0;
}
```
代码丑陋无比，仅供参考。

---

## 作者：Sicanus (赞：0)

又是一道~~超级大模拟~~。看到各位先（仙）人们精简的代码，```200+```行代码的本蒟蒻瑟瑟发抖。

本蒟蒻想法很简单，上来先把所有ASCII巨型数字打表（~~不经过任何压缩~~），以A、B两个数字来存两个加数（**血的教训：开long long，int稳稳的60分**），再通过截取输入中的一个“矩阵”，来获取单个ASCII巨型数字，然后把它拿去和表匹配，取得对应数字后，把它加到A或B里面去（此处使用快读思想），取得和后再用表来输出就 $ {\color{green} AC} $ 了。

附上代码：（请忽略清奇的码风、奇长无比的变量名字(不过很好认)，~~这都是可以代码补全和自(qiáng)动(xíng)格式化代码的IDE的错~~QAQ） 


``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#define SINGLE_NUM_STR_LENGTH 5	// 装逼用，单个数字宽度
#define fro for					// 防敲错
using namespace std;

// 字符打表，0-9表数字，10是加号（有点长别在意，忽略即可）
string nums[11][7] =
{
    {
        "xxxxx",
        "x...x",
        "x...x",
        "x...x",
        "x...x",
        "x...x",
        "xxxxx"
    },
    {
        "....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x"
    },
    {
        "xxxxx",
        "....x",
        "....x",
        "xxxxx",
        "x....",
        "x....",
        "xxxxx"
    },
    {
        "xxxxx",
        "....x",
        "....x",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"
    },
    {
        "x...x",
        "x...x",
        "x...x",
        "xxxxx",
        "....x",
        "....x",
        "....x"
    },
    {
        "xxxxx",
        "x....",
        "x....",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"
    },
    {
        "xxxxx",
        "x....",
        "x....",
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx"
    },
    {
        "xxxxx",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x"
    },
    {
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx"
    },
    {
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"
    },
    {
        ".....",
        "..x..",
        "..x..",
        "xxxxx",
        "..x..",
        "..x..",
        "....."
    }
};

// 暴力比较来获得int值，s是一个剥离出来的ASCII巨型数字
inline short get_ASCII_Num(string s[]) 
{
    bool matched[11]; // 桶
    memset(matched, true, sizeof(matched));
    for (long long i = 0; i < 7; i++)
    {
        fro (long long j = 0; j < 11; j++)
        {
            if (matched[j] == false)
            {
                continue;
            }
            if (s[i] != nums[j][i])
            {
                matched[j] = false;
            }
        }
    }
    fro (long long i = 0; i < 11; i++)
    {
        if (matched[i] == true)
        {
            return i;
        }
    }
}

// 剥离代码（弟弟版，逆序的）
inline string sliceNum(long long a)
{
    string s;
    while (a)
    {
        s += char(a % 10 + '0');
        a /= 10;
    }
    return s;
}

// 把int结果输出为要求的ASCII巨型数字，a为要输出的值
inline void print_ASCII_Num(long long a)
{
	// 这个producedNum是把int转换为string
    string producedNum = sliceNum(a);
    reverse(producedNum.begin(), producedNum.end());
    long long resLen = producedNum.size();
	
    // 存数
    short digits[10] = {0};
    for (long long i = 0; i < resLen; i++)
    {
        digits[i] = producedNum[i] - '0';
    }
    
    // 用打的表来匹配输出
    for (long long j = 0; j < 7; j++)
    {
        fro (long long i = 0; i < resLen; i++)
        {
            if (i == resLen - 1) //防止最后一列多输出"."
            {
                cout << nums[digits[i]][j];
                break;
            }
            cout << nums[digits[i]][j] << ".";
        }
        cout << endl;
    }

}

int main(int argc, char const *argv[])
{
    long long A = 0, B = 0;
    string tempStr[7];	// 存输入的7行string
    for (short T = 0; T < 7; T++)
    {
        cin >> tempStr[T];
    }
    string temp[7]; // 从输入的字符剥离出单个ASCII巨型数字
    short len = strlen(tempStr[0].c_str()), amountOfNums = (len + 1) / 6; // amount是要输入的数字（包括加号）的数量
    
    // 下面一行bound是一个比zeit大5的数字，定义单个ASCII巨型数字右边界
    long long tempMaxBound = 0, tempGottonValue = 0;
    bool haveAlreadyReadAPlusOperator = false; // 存是否读入加号
    register long long zeit = 0; // 其实是flag，单个ASCII巨型数字左边界

    while (amountOfNums--)
    {
        /// get a whole string arr of single num
        fro (long long T = 0; T < 7; T++)
        {
            tempMaxBound = zeit + SINGLE_NUM_STR_LENGTH;
            
            for (short i = zeit; i < tempMaxBound; i++)
            {
                temp[T] += tempStr[T][i];
            }
        }

        zeit += 6; // 把左边界移到下一个ASCII巨型数字

		// 获取当前截取数字的int值
        tempGottonValue = get_ASCII_Num(temp);

		// 清除temp数组
        for (long long i = 0; i < 7; i++)
        {
            temp[i].erase(0);
        }

        //cout << "tgv: " << tempGottonValue << endl << endl;

        if (tempGottonValue == 10) // 加号
        {
            haveAlreadyReadAPlusOperator = true;
            continue;
        }
        // 以下均以快读思想来获取int值
        if (haveAlreadyReadAPlusOperator == false) // A
        {
            A += tempGottonValue;
            A *= 10;
        }
        if (haveAlreadyReadAPlusOperator == true) // B
        {
            B += tempGottonValue;
            B *= 10;
        }
    }
    // 输出
    print_ASCII_Num((A + B) / 10);
    return 0;
}

```

附：本题的```高性能```标签是不是太fake了啊，本蒟蒻这样的不带任何优化和卡常的模拟也能最多3ms过

---

## 作者：KevinYu (赞：0)

~~这道题有一道A+B题目应有的难度。~~         
这一题的体面相信并不难理解，只是输入输出难处理了一点。        
Part1.输入部分:         
首先我们来看看样例:       
```
....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.......xxxxx.xxxxx.xxxxx
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.......xxxxx.xxxxx.xxxxx
```
这个样例还是很良心的，给出了0-9连带上'+'的所有ASCII艺术表示，很适合来调试我们的输入。        
所以我们怎么区分输入的是什么呢?       
看到许多的题解建议我们一行一行地扫，我发现实在是太麻烦了。         
所以我就想到了分辨每一个字符的**特征**。        
为了实现这个，我们先将字符串转换成01串。
```
00001011111011111010001011111011111011111000000011111011111011111
00001000001000001010001010000010000000001000100010001010001010001
00001000001000001010001010000010000000001000100010001010001010001
00001011111011111011111011111011111000001011111011111011111010001
00001010000000001000001000001010001000001000100010001000001010001
00001010000000001000001000001010001000001000100010001000001010001
00001011111011111000001011111011111000001000000011111011111011111
```        
这样我们就可以来看看字符的特点了。       
谈到特点，自然而然地就想到了每一个字符的**大小**(即组成字符的**1**的个数):
```
大小表:
字符'+':9
字符'0':20
字符'1':7
字符'2':19
字符'3':19
字符'4':14
字符'5':19
字符'6':21
字符'7':11
字符'8':23
字符'9':21
```
但是还有一些数字重复了。      
于是我们引入另外两个属性:l,r，代表字符的左右两边的大小。       
下面的l,r表仅给出上面的大小表不能分辨的:
```
l,r表
字符'2':5,5
字符'3':1,7
字符'5':5,5
字符'6':7,5
字符'9':5,7
```
2,5这两个顽固分子该怎么办呢?      
另引入一个属性lu，代表一个数的左下角的大小:
```
lu表
字符'2':2
字符'5':4
```
这样就可以分辨输入了。        
read函数分步解析:       
1.初始化并求出总长度(不要在意奇怪的参数列表):       
```cpp
void read(char *ch0,char *ch1,char* ch2,char *ch3,char *ch4,char *ch5,char *ch6,char *ch7,long long *a0,long long *a1,long long* a2,long long *a3,long long *a4,long long *a5,long long *a6,long long *a7,long long *numa,long long *numb,long long *n,long long *plc)
{
	char *ch[8];
	ch[0]=ch0;ch[1]=ch1;ch[2]=ch2;ch[3]=ch3;
	ch[4]=ch4;ch[5]=ch5;ch[6]=ch6;ch[7]=ch7;
	long long *a[8];
	a[0]=a0;a[1]=a1;a[2]=a2;a[3]=a3;
	a[4]=a4;a[5]=a5;a[6]=a6;a[7]=a7;
	for(long long i=1;i<=7;i++)scanf("%s",&ch[i][1]);
	long long len=strlen(&ch[1][1]);
	*n=len+1;*n/=6;
```
2.全部输入完后，我们求出整个数组的**前缀和**:
```cpp
	for(long long i=1;i<=7;i++){for(long long j=1;j<=len;j++){if(ch[i][j]=='.')a[i][j]=0;else a[i][j]=1;}}
	for(long long i=1;i<=7;i++){for(long long j=1;j<=len;j++){a[i][j]=a[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1];}}
```
3.求出每个数的k(总大小),l(左侧大小),r(右侧大小),lu(左下角大小):
```cpp
	for(long long i=1;i<=*n;i++)
	{
		long long k=a[7][i*6-1]-a[7][(i-1)*6];
		long long l=a[7][(i-1)*6+1]-a[7][(i-1)*6];
		long long r=a[7][i*6-1]-a[7][i*6-2];
		long long lu=l-(a[3][(i-1)*6+1]-a[3][(i-1)*6]);
```
4.判断数字并将其添加到当前数字的末端:
```cpp
		long long dn;
		if(k==9){*plc=i;continue;}
		else if(k==20)dn=0;
		else if(k==7)dn=1;
		else if(k==19&&lu==4)dn=2;
		else if(k==19&&l==3&&r==7)dn=3;
		else if(k==14)dn=4;
		else if(k==19)dn=5;
		else if(k==21&&l==7&&r==5)dn=6;
		else if(k==11)dn=7;
		else if(k==23)dn=8;
		else if(k==21&&l==5&&r==7)dn=9;
		if(!*plc){*numa*=10;*numa+=dn;}
		else {*numb*=10;*numb+=dn;}
	}
}
```
这样整个read函数就完成了。      
read函数代码:
```cpp
void read(char *ch0,char *ch1,char* ch2,char *ch3,char *ch4,char *ch5,char *ch6,char *ch7,long long *a0,long long *a1,long long* a2,long long *a3,long long *a4,long long *a5,long long *a6,long long *a7,long long *numa,long long *numb,long long *n,long long *plc)
{
	char *ch[8];
	ch[0]=ch0;ch[1]=ch1;ch[2]=ch2;ch[3]=ch3;
	ch[4]=ch4;ch[5]=ch5;ch[6]=ch6;ch[7]=ch7;
	long long *a[8];
	a[0]=a0;a[1]=a1;a[2]=a2;a[3]=a3;
	a[4]=a4;a[5]=a5;a[6]=a6;a[7]=a7;
	for(long long i=1;i<=7;i++)scanf("%s",&ch[i][1]);
	long long len=strlen(&ch[1][1]);
	*n=len+1;*n/=6;
	for(long long i=1;i<=7;i++){for(long long j=1;j<=len;j++){if(ch[i][j]=='.')a[i][j]=0;else a[i][j]=1;}}
	for(long long i=1;i<=7;i++){for(long long j=1;j<=len;j++){a[i][j]=a[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1];}}
	for(long long i=1;i<=*n;i++)
	{
		long long k=a[7][i*6-1]-a[7][(i-1)*6];
		long long l=a[7][(i-1)*6+1]-a[7][(i-1)*6];
		long long r=a[7][i*6-1]-a[7][i*6-2];
		long long lu=l-(a[3][(i-1)*6+1]-a[3][(i-1)*6]);
		long long dn;
		if(k==9){*plc=i;continue;}
		else if(k==20)dn=0;
		else if(k==7)dn=1;
		else if(k==19&&lu==4)dn=2;
		else if(k==19&&l==3&&r==7)dn=3;
		else if(k==14)dn=4;
		else if(k==19)dn=5;
		else if(k==21&&l==7&&r==5)dn=6;
		else if(k==11)dn=7;
		else if(k==23)dn=8;
		else if(k==21&&l==5&&r==7)dn=9;
		if(!*plc){*numa*=10;*numa+=dn;}
		else {*numb*=10;*numb+=dn;}
	}
}
```
Part2.输出部分:        
输出相对于输入来说更为简单，只用逐位输出对应的ASCII艺术即可。        

我本来不想靠string的加法做这道题的，但奈何实在是太方便了。      
先定义一个opt数组，方便后面的字符串加法:     
注:opt数组建议直接copy-paste，要是打错了就真的GG了。           
压行前:
```cpp
string opt[11][8]=
{
	{
		"",
		"xxxxx",
		"x...x",
		"x...x",
		"x...x",
		"x...x",
		"x...x",
		"xxxxx"
	},
	{
		"",
		"....x",
		"....x",
		"....x",
		"....x",
		"....x",
		"....x",
		"....x"
	},
	{
		"",
		"xxxxx",
		"....x",
		"....x",
		"xxxxx",
		"x....",
		"x....",
		"xxxxx"
	},
	{
		"",
		"xxxxx",
		"....x",
		"....x",
		"xxxxx",
		"....x",
		"....x",
		"xxxxx"
	},
	{
		"",
		"x...x",
		"x...x",
		"x...x",
		"xxxxx",
		"....x",
		"....x",
		"....x"
	},
	{
		"",
		"xxxxx",
		"x....",
		"x....",
		"xxxxx",
		"....x",
		"....x",
		"xxxxx"
	},
	{
		"",
		"xxxxx",
		"x....",
		"x....",
		"xxxxx",
		"x...x",
		"x...x",
		"xxxxx"
	},
	{
		"",
		"xxxxx",
		"....x",
		"....x",
		"....x",
		"....x",
		"....x",
		"....x"
	},
	{
		"",
		"xxxxx",
		"x...x",
		"x...x",
		"xxxxx",
		"x...x",
		"x...x",
		"xxxxx"
	},
	{
		"",
		"xxxxx",
		"x...x",
		"x...x",
		"xxxxx",
		"....x",
		"....x",
		"xxxxx"
	}
};
```
压行后:      
```cpp
string opt[11][8]={{"","xxxxx","x...x","x...x","x...x","x...x","x...x","xxxxx"},{"","....x","....x","....x","....x","....x","....x","....x"},{"","xxxxx","....x","....x","xxxxx","x....","x....","xxxxx"},{"","xxxxx","....x","....x","xxxxx","....x","....x","xxxxx"},{"","x...x","x...x","x...x","xxxxx","....x","....x","....x"},{"","xxxxx","x....","x....","xxxxx","....x","....x","xxxxx"},{"","xxxxx","x....","x....","xxxxx","x...x","x...x","xxxxx"},{"","xxxxx","....x","....x","....x","....x","....x","....x"},{"","xxxxx","x...x","x...x","xxxxx","x...x","x...x","xxxxx"},{"","xxxxx","x...x","x...x","xxxxx","....x","....x","xxxxx"}};
```
接下来在每一行输出字符串的末尾加上对应数字的每一行即可。          
write函数浅析:        
1.将数字分为每一位:
```cpp
void write(long long ans,long long n)
{
	string s[8];long long ot[11],pwt[11],sot[11];pwt[0]=1;ot[0]=sot[0]=0;
	for(long long i=1;i<=10;i++)pwt[i]=pwt[i-1]*10;
	for(long long i=1;i<=n;i++)ot[i]=sot[i]=ans%pwt[i];
	for(long long i=1;i<=n;i++){ot[i]-=sot[i-1];ot[i]/=pwt[i-1];}
```
2.将每一个字符串记载对应行的末尾:
```cpp
	for(long long i=n;i>=2;i--)for(long long j=1;j<=7;j++)s[j]+=opt[ot[i]][j],s[j]+=".";
	for(long long i=1;i<=7;i++)s[i]+=opt[ot[1]][i];
	for(long long i=1;i<=7;i++)printf("%s\n",&s[i][0]);
}
```
这样write函数就结束了。        
write函数完整代码:
```cpp
void write(long long ans,long long n)
{
	string s[8];long long ot[11],pwt[11],sot[11];pwt[0]=1;ot[0]=sot[0]=0;
	for(long long i=1;i<=10;i++)pwt[i]=pwt[i-1]*10;
	for(long long i=1;i<=n;i++)ot[i]=sot[i]=ans%pwt[i];
	for(long long i=1;i<=n;i++){ot[i]-=sot[i-1];ot[i]/=pwt[i-1];}
	for(long long i=n;i>=2;i--)for(long long j=1;j<=7;j++)s[j]+=opt[ot[i]][j],s[j]+=".";
	for(long long i=1;i<=7;i++)s[i]+=opt[ot[1]][i];
	for(long long i=1;i<=7;i++)printf("%s\n",&s[i][0]);
}
```
本题完整代码:
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<cctype>
#include<cerrno>
#include<cfloat>
#include<ciso646>
#include<climits>
#include<clocale>
#include<cmath>
#include<csetjmp>
#include<csignal>
#include<cstdarg>
#include<cstddef>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cassert>
#include<cwchar>
#include<cwctype>
#include<algorithm>
#include<bitset>
#include<complex>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<typeinfo>
#include<utility>
#include<valarray>
#include<vector>
using namespace std;
string opt[11][8]={{"","xxxxx","x...x","x...x","x...x","x...x","x...x","xxxxx"},{"","....x","....x","....x","....x","....x","....x","....x"},{"","xxxxx","....x","....x","xxxxx","x....","x....","xxxxx"},{"","xxxxx","....x","....x","xxxxx","....x","....x","xxxxx"},{"","x...x","x...x","x...x","xxxxx","....x","....x","....x"},{"","xxxxx","x....","x....","xxxxx","....x","....x","xxxxx"},{"","xxxxx","x....","x....","xxxxx","x...x","x...x","xxxxx"},{"","xxxxx","....x","....x","....x","....x","....x","....x"},{"","xxxxx","x...x","x...x","xxxxx","x...x","x...x","xxxxx"},{"","xxxxx","x...x","x...x","xxxxx","....x","....x","xxxxx"}};
void read(char *ch0,char *ch1,char* ch2,char *ch3,char *ch4,char *ch5,char *ch6,char *ch7,long long *a0,long long *a1,long long* a2,long long *a3,long long *a4,long long *a5,long long *a6,long long *a7,long long *numa,long long *numb,long long *n,long long *plc)
{
	char *ch[8];
	ch[0]=ch0;ch[1]=ch1;ch[2]=ch2;ch[3]=ch3;
	ch[4]=ch4;ch[5]=ch5;ch[6]=ch6;ch[7]=ch7;
	long long *a[8];
	a[0]=a0;a[1]=a1;a[2]=a2;a[3]=a3;
	a[4]=a4;a[5]=a5;a[6]=a6;a[7]=a7;
	for(long long i=1;i<=7;i++)scanf("%s",&ch[i][1]);
	long long len=strlen(&ch[1][1]);
	*n=len+1;*n/=6;
	for(long long i=1;i<=7;i++){for(long long j=1;j<=len;j++){if(ch[i][j]=='.')a[i][j]=0;else a[i][j]=1;}}
	for(long long i=1;i<=7;i++){for(long long j=1;j<=len;j++){a[i][j]=a[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1];}}
	for(long long i=1;i<=*n;i++)
	{
		long long k=a[7][i*6-1]-a[7][(i-1)*6];
		long long l=a[7][(i-1)*6+1]-a[7][(i-1)*6];
		long long r=a[7][i*6-1]-a[7][i*6-2];
		long long lu=l-(a[3][(i-1)*6+1]-a[3][(i-1)*6]);
		long long dn;
		if(k==9){*plc=i;continue;}
		else if(k==20)dn=0;
		else if(k==7)dn=1;
		else if(k==19&&lu==4)dn=2;
		else if(k==19&&l==3&&r==7)dn=3;
		else if(k==14)dn=4;
		else if(k==19)dn=5;
		else if(k==21&&l==7&&r==5)dn=6;
		else if(k==11)dn=7;
		else if(k==23)dn=8;
		else if(k==21&&l==5&&r==7)dn=9;
		if(!*plc){*numa*=10;*numa+=dn;}
		else {*numb*=10;*numb+=dn;}
	}
}
void write(long long ans,long long n)
{
	string s[8];long long ot[11],pwt[11],sot[11];pwt[0]=1;ot[0]=sot[0]=0;
	for(long long i=1;i<=10;i++)pwt[i]=pwt[i-1]*10;
	for(long long i=1;i<=n;i++)ot[i]=sot[i]=ans%pwt[i];
	for(long long i=1;i<=n;i++){ot[i]-=sot[i-1];ot[i]/=pwt[i-1];}
	for(long long i=n;i>=2;i--)for(long long j=1;j<=7;j++)s[j]+=opt[ot[i]][j],s[j]+=".";
	for(long long i=1;i<=7;i++)s[i]+=opt[ot[1]][i];
	for(long long i=1;i<=7;i++)printf("%s\n",&s[i][0]);
}
long long a1[1010];
long long a2[1010];
long long a3[1010];
long long a4[1010];
long long a5[1010];
long long a6[1010];
long long a7[1010];
long long a0[1010];
char ch1[1010];
char ch2[1010];
char ch3[1010];
char ch4[1010];
char ch5[1010];
char ch6[1010];
char ch7[1010];
char ch0[1010];
long long qusa(0),qusb(0);
long long n(0);
long long numa;
long long numb;
long long plc(0);
signed main()
{
	read(ch0,ch1,ch2,ch3,ch4,ch5,ch6,ch7,a0,a1,a2,a3,a4,a5,a6,a7,&numa,&numb,&n,&plc);
	write(numa+numb,log10(numa+numb)+1);
	return 0;
}
```


---

