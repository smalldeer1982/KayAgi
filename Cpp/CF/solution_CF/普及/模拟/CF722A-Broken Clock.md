# Broken Clock

## 题目描述

You are given a broken clock. You know, that it is supposed to show time in 12- or 24-hours HH:MM format. In 12-hours format hours change from $ 1 $ to $ 12 $ , while in 24-hours it changes from $ 0 $ to $ 23 $ . In both formats minutes change from $ 0 $ to $ 59 $ .

You are given a time in format HH:MM that is currently displayed on the broken clock. Your goal is to change minimum number of digits in order to make clocks display the correct time in the given format.

For example, if 00:99 is displayed, it is enough to replace the second 9 with 3 in order to get 00:39 that is a correct time in 24-hours format. However, to make 00:99 correct in 12-hours format, one has to change at least two digits. Additionally to the first change one can replace the second 0 with 1 and obtain 01:39.

## 样例 #1

### 输入

```
24
17:30
```

### 输出

```
17:30
```

## 样例 #2

### 输入

```
12
17:30
```

### 输出

```
07:30
```

## 样例 #3

### 输入

```
24
99:99
```

### 输出

```
09:09
```

# 题解

## 作者：ivyjiao (赞：2)

### 这道题非常重要的一点是 $12$ 小时制和 $24$ 小时制的定义。

$12$ 小时制：$01:00$ 至 $12:59$。

$24$ 小时制：$00:00$ 至 $23:59$。

依照这个定义写代码即可。

特别注意：$24$ 小时制下是没有 $24$ 时的，$12$ 小时制下是没有 $0$ 时的。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a,b,c,d,m;
int n;
int main(){
    cin>>n;//输入12小时制或24小时制
    cin>>a>>b>>m>>c>>d;//输入时间
    //12小时制或24小时制只影响小时部分，所以分钟部分容易处理
    if(c>='6'){//修正分钟部分
        c='0';
    }
    //开始处理小时部分
    if(n==12){//12小时制
        if(a=='0'&&b=='0'){//12小时中不允许有0时
            b='1';
        }
        else if(10*(a-'0')+(b-'0')>12&&b>'0'){//如果小时部分超过12但b不是0
            a='0';
        }
        else if(10*(a-'0')+(b-'0')>12&&b=='0'){//如果小时部分超过12且b是0
            a='1';//改成10点
        }
    }
    if(n==24){//24小时制
        if(10*(a-'0')+(b-'0')>=24){//如果小时部分超过24
            a='0';
        }
    }
    cout<<a<<b<<m<<c<<d;//输出
}
```


---

## 作者：Colead (赞：1)

看到这个题目就觉得不太对劲。果然，不难，但是很烦。

首先你得确定一下两个进制的范围：

$12$ 进制： $1-12$

$24$ 进制： $0-23$

所以注意： $24$ 进制下是没有 $24$ 时的， $12$ 进制下是没有 $0$ 时的。（这个挺坑人的请注意）

那么首先分钟很好判断，是否大于 $60$ 。

小时呢？

 $24$ 进制下十分好判，小时大于  $24$ 就直接改十位。
 
 但是  $12$ 进制下应注意，虽然可以与上一种情况以相同原理处理，但是请注意： **没有 $0$ 时** ，所以小时个位为 $0$ 时，十位只能改成 $1$ 。
 
 细节挺多的，调起来麻烦，这里给个条例比较清晰的代码。
 
 ```
#include<bits/stdc++.h>
using namespace std;
long long n;
char a,b,c,d,e;
int main()
{
	cin>>n>>a>>b>>c>>d>>e;
	if(d>='6')d='0';
	if(n==12)
	{
		if(a=='0'&&b=='0')
		{
			b='1';
		}
		else if(10*(a-'0')+(b-'0')>12&&b>'0')a='0';
		else if(10*(a-'0')+(b-'0')>12&&b=='0')a='1';
	}
	if(n==24)
	{
		if(10*(a-'0')+(b-'0')>=24)a='0';
	}
	cout<<a<<b<<c<<d<<e;
	return 0;
}
```

全程使用条件执行结构，应该很易懂了。

祝大家AC快乐！

---

## 作者：hanyuchen2019 (赞：1)

我谔谔，这题有那么复杂吗...

1. 首先，如果分钟不对，直接把十位改成 $0$ 即可（$\mod{10}$，让答案直接 $<10$，先保证分钟在合理范围内，下同）。

2. 对于时钟，需要分类讨论：

$\quad\operatorname{I.}12$ 小时制（$1...12$）：

$\qquad$ a.末位为 $0$ ：直接改成 $10$。（出现 $0$ 点会爆掉）

$\qquad$ b.不为 $0$ ：把十位改成 $0$ 即可（$\mod{10}$）。

$\quad\operatorname{II.}24$ 小时制（$0...23$）：

$\quad$把十位改成 $0$ 即可（$\mod{10}$，因为即使是 $0$ 点也不会炸）。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register int
int a,h,m;
int main()
{
	cin>>a;
	scanf("%d:%d",&h,&m);//注意格式！
	if(m>59)m%=10;//先改分钟
	if(a==12&&(h>12||h<1))//如果是12小时制且不合理
	{
		if(h%10==0)//特判
			h=10;
		else h%=10;//在1~9范围内，安全
	}
	if(a==24&&h>=24)
		h%=10;//直接取模，0点也可以
	printf("%02d:%02d",h,m);
 	return 0;
}
```

---

## 作者：_ZhouYuHan_ (赞：0)

这道题可以利用分类讨论的思想来做，分为两种情况考虑。

1. $12$ 小时制：如果小时数超过 $12$，分钟数超过 $59$，把它们 $\mod 10$，而且需要特判一下，小时数是否等于 $0$，如果是的话，把它改为 $10$。

2. $24$ 小时制：如果小时数超过 $23$ 分钟超过 $59$，就把它们 $\mod 10$。

话不多说，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
void print(int a) {//打印小时数
	if(a<10)
		cout<<0;
	cout<<a;
}
int main() {
	int a,b,c;
	scanf("%d %d:%d",&c,&a,&b);
	if(c==12) {//12小时制
		if(a==0)
			a=10;//特判一下
		if(a>12){
		    if(a%10==0)
		    	a=10;
		    else
				a%=10;
		}
		if(b>=60)
			b%=10;//判断
		print(a);
		cout<<":";
		print(b);
	}
	if(c==24) {//24小时制
		if(a>=24)
			a%=10;
		if(b>=60)
			b%=10;//判断
		print(a);
		cout<<":";
		print(b);
	}
	return 0;
}
```


---

## 作者：_easy_ (赞：0)

# 思路
如果小时不合法，就将小时变成个位数，分钟一样。

这里要注意几个坑点：
1. 小时如果是 $10$ 的倍数并且是 $12$ 小时制，取完模后会出现 $0$，此时不合法，所以要先加 $10$ 再模 $10$。
2. 输入时，需要注意中间的冒号。
2. 输出时，输出个位数需要补零。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c;
int main(){
	scanf("%d%d:%d",&a,&b,&c);
	if(a==12&&(b>12||b<1)){
		if(b%10==0){
			b=10;
		}else{
			b%=10;
		}
	}
	if(a==24&&b>=a){
		b%=10;
	}//小时
	if(c>59){
		c=c%10;
	}//分钟
	printf("%02d:%02d",b,c);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[Codeforces的题目地址](https://codeforces.com/problemset/problem/722/A)


------------

翻译如下:
### 题目描述
你有一个坏了的闹钟.

你知道，它应该显示HH：MM这样格式的时间(无论是12还是24小时制).

在12小时制中,小时数需要在1到12之间，在24小时制中，小时数需要在0到23之间.
在两种格式中,分钟数均需要在0到59之间.

您将得到一个格式为HH:MM的时间,该时间显示在你坏了的时钟上.

您的目标是修正最少的次数,以使时钟以给定的格式(12或24小时制)显示正确的时间.

例如,如果输入的时间为00:99,将第二个9修正为3就可以了,修正后的时间为00:39（24小时格式的正确时间）.

但是，要以12小时格式正确修正00:99，则必须至少修正2次.
除上一次的修改以后，还至少需要将分钟上第二个0替换为1以修正为01:39。
### 输入

输入的第一行包含一个整数12或24,表示12小时或24小时格式.

第二行包含HH:MM格式的时间.
前两个字符代表小时,后两个字符代表分钟.

### 输出

输出的唯一一行应包含格式为HH:MM的时间,这是给定格式(12或24小时制)的正确时间.

它应与输入的时间修正尽可能少的次数.如果存在多种情况,则输出其中任何一种均可.

------------
下面是AC代码

```cpp
/*
https://www.luogu.com.cn/problem/CF722A
CF722A Broken Clock
一些注释
*/
#include<bits/stdc++.h>
using namespace std;
int geshi;
int h,m;
int main(){
	scanf("%d",&geshi);//输入时间格式(12或24小时制)
	scanf("%d:%d",&h,&m);//输入时间
	if(geshi==12){//12小时制
		if(h==0||h%10==0) h=10;//特判
		if(h>=1&&h<=12&&m<=59)/小时和分钟均符合要求时
		    printf("%02d:%02d",h,m);
		if(h>12&&m<=59)//小时不符合要求但分钟符合要求
		    printf("%02d:%02d",h%10,m);
		if(h>=1&&h<=12&&m>59)//小时符合要求但分钟不符合要求
		    printf("%02d:%02d",h,m%10);
		if(h>12&&m>59)//都不符合要求时
		    printf("%02d:%02d",h%10,m%10);
	}
	if(geshi==24){//24小时制
		if(h>=0&&h<=23&&m<=59)//小时和分钟均符合要求时
		    printf("%02d:%02d",h,m);
		if(h>23&&m<=59)//小时不符合要求但分钟符合要求
		    printf("%02d:%02d",h%10,m);
		if(h>=0&&h<=23&&m>59)//小时符合要求但分钟不符合要求
		    printf("%02d:%02d",h,m%10);
		if(h>23&&m>59)//都不符合要求时
		    printf("%02d:%02d",h%10,m%10);
	}
	return 0;
}
```

关于
```cpp
printf("%n",n);//n如下图中的数字
```

![图片.png](https://i.loli.net/2020/10/26/xhwijL9a3P7RJos.png)


5或10这样的数字(没有前置的0),就是空n个字符空间输出

而02或010这样的数字(有前置的0),

如果输出的字符长度大于0后面的数字大小,则直接输出结果

否则在输入的内容前补上缺少的0(比如输入为2,则应该补上10-2=8个0)




---

## 作者：RioBlu (赞：0)

本题翻译：一个坏掉的闹钟，改变最少位置，在12或24小时制内是正确的(12小时制：小时为1~12，24小时制：小时为0~23)
```
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
string ans1,ans2,k;
int main()
{
	cin>>a>>k;
	for(int s=0;s<5;s++)//把字符串k改为，小时和分钟
	{
		if(s<2)
		b=b*10+k[s]-'0';
		else
		if(s>2)c=c*10+k[s]-'0';
	}
	if(c>59)//判断分钟改不改
	{
		ans2="0";ans2=ans2+(char)(c%10+'0');
	}
	else//不用改分钟
	{
		ans2=(char)(c/10+'0');ans2=ans2+(char)(c%10+'0');
	}
	if(a==12)//12小时制
	{
		if(b>12)
		{
			if(b%10!=0)//特判
			{
				ans1="0";ans1=ans1+(char)(b%10+'0');
			}
			else
			{
				ans1="1";ans1=ans1+'0';
			}
		}
		else
		{
			if(b<1)
			ans1="01";//（记住特判！没有00）
			else
			{
				if(b>9)//是否大于等于10(因为小于10位数只有1位)
				{
					ans1=(char)(b/10+'0');ans1=ans1+(char)(b%10+'0');
				}
				else
				{
					ans1="0";ans1=ans1+(char)(b%10+'0');
				}
				
			}
			
		}
	}
	else//24小时制
	{
		if(b>23)//不符合规则
		{
			ans1="0";ans1=ans1+(char)(b%10+'0');
		}
		else//符合规则
		{
			if(b>=10)//是否大于等于10(因为小于10位数只有1位)
			{
				ans1=(char)(b/10+'0');ans1=ans1+(char)(b%10+'0');
			}
			else
			{
				ans1="0";ans1=ans1+(char)(b%10+'0');
			}
			
		} 
	}
	cout<<ans1<<":"<<ans2<<endl;
	return 0;
}
```

---

