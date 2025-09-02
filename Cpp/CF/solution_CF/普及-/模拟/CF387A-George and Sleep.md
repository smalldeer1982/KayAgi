# George and Sleep

## 题目描述

给出一个时间点 $s$ 和一个时间段 $t$，求出从时间点 $s$ 向前回推时间段 $t$ 得到的时间点 $p$。（所有时间用 `HH:MM` 的格式表示）

## 说明/提示

对于 $100\%$ 的数据，$0\le \text{HH}\le 23$，$0\le \text{MM}\le 59$。

时间点 $s$ 和时间点 $p$ 可能不在同一天。

## 样例 #1

### 输入

```
05:50
05:44
```

### 输出

```
00:06
```

## 样例 #2

### 输入

```
00:00
01:00
```

### 输出

```
23:00
```

## 样例 #3

### 输入

```
00:01
00:00
```

### 输出

```
00:01
```

# 题解

## 作者：songxiao (赞：5)

一个**自认为**挺正常的普通易懂题解。

我的主要思路是转换为分钟计算，大于一天的就再加上一天的分钟数（`24*60`）

其中scanf和printf的转换其他大佬也提过了，我稍微讲讲吧。（讲的不明白的话请重学scanf和printf）

`scanf("%d:%d\n%d:%d",&h,&m,&h0,&m0)`如果这样的话输入时会忽略固定位置的`:`

`printf("%02d:%02d",s/60,s%60);`这是控制输出位数的，这样是两位（前面自动补零）:`%02d`


AC代码：（每行都有注释，除了大括号）

```cpp

//注：因为有2个时间，所以其中一个变量后面有0
#include <bits/stdc++.h>	//万能头
int main()	//主函数
{	
  int h,m,h0,m0;	//对应题目h和m
  int t,t0,s;	//s是时间差，t是用来转换为分钟的
  scanf("%d:%d\n%d:%d",&h,&m,&h0,&m0);	//注意scanf的输入方式
  t=h*60+m;	//转换为分钟计算
  t0=h0*60+m0;	//转换为分钟计算
  if(t>t0)	//如果在同一天
  {
    s=t-t0;	//求时差（就是题目中睡觉的时间）
    printf("%02d:%02d",s/60,s%60);	//注意printf的输出方式
  }
  else if(t<t0)	//不在同一天
  {
    s=24*60-t0+t;	//先加上一天的分钟数
    printf("%02d:%02d",s/60,s%60);	//注意printf的输出方式
  }
  else	//如果时差为0(这里的特批其实可以和前面的合并，但我懒得写了)
    printf("00:00");	//输出0分0秒	
  return 0;	//结束
}
```


---

## 作者：t162 (赞：2)

利用强大的**Python**，我们可以使用更少的代码完成此题。  
~~（然而只是分割和转换方面方便一点）~~

```python
fir = input().split(':')        #输入并分割
sec = input().split(':')        #输入并分割

ah = int(fir[0])                #转换
am = int(fir[1])                #转换
bh = int(sec[0])                #转换
bm = int(sec[1])                #转换

if(ah<bh or(ah==bh and am<bm)): #如果第一个时间小于第二个时间，则将第一个时间加上24小时
    ah=ah+24
ah=ah-bh                        #小时相减
am=am-bm                        #分钟相减
if(am<0):                       #退位
    ah=ah-1
    am=60+am
print('%02d:%02d'%(ah,am))      #格式化输出
```

然后：
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：封禁用户 (赞：1)

这道水题虽然简单，但却卡了我20多分钟！~~（当然咯，不是紫题吗）~~  
注意，用scanf读入，如果遇到引号内的内容就会置之不理，这样就会方便很多  
放上弱弱的代码……
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a, b, c, d;
inline string tera(int k) {//将4改为"04"，将23改为"23"
	string s = "00";
	s[0] = k / 10 + '0';
	s[1] = k % 10 + '0';
	return s;
}
int main() {
	scanf("%0d:%0d\n%0d:\n%0d", &a, &b, &c, &d);//scanf的一个功能
	if (a * 100 + b >= c * 100 + d) {
		if (b >= d) {
			cout << tera(a - c);
			putchar(':');
			cout << tera(b - d);
		} else {
			cout << tera(a - c - 1);
			putchar(':');
			cout << tera(b - d + 60);
		}
	} else {
		if (b >= d) {
			cout << tera(a - c + 24);
			putchar(':');
			cout << tera(b - d);
		} else {
			cout << tera(a - c + 23);
			putchar(':');
			cout << tera(b - d + 60);
		}
	}//这么多判断看来还是我太弱了
	return 0;
}//程序拜拜qaq
```

---

## 作者：shenzuxin (赞：0)

这道题是算两个时间的差，但是如果第一个小就要给第一个加上1天（1440分），比较简单。（~~为什么是紫题，不应该是红/橙题吗~~）
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string sj1,sj2;int t,s1,s2,s,f;
	getline(cin,sj1);
	getline(cin,sj2);//输入
	s1=((sj1[0]-'0')*10+sj1[1]-'0')*60+(sj1[3]-'0')*10+sj1[4]-'0';
	s2=((sj2[0]-'0')*10+sj2[1]-'0')*60+(sj2[3]-'0')*10+sj2[4]-'0';//计算分钟数
	if(s1>=s2) t=s1-s2;else t=s1+1440-s2;//补时间，相减（‘=’一定要加）
	f=t%60;s=t/60;//24小时计时法
	if (s<10)cout<<0;cout<<s<<':';
	if (f<10)cout<<0;cout<<f;//补0，输出
    return 0;
} 
```

---

## 作者：CZQ_King (赞：0)

为什么大佬们的题解都那么长啊

这题应该不用判断语句就可以过了吧

------------
做法：

1. 这个在其他大佬的题解里有说，就是分开分钟数和秒数。
2. 把他们统一转成分钟，公式应该很简单：$\text{总分钟}=\text{小时数}\times60+\text{分钟数}$
3. 相减（分类讨论）：
   - 若第一个比第二个大，直接相减就行。（而且相减后一定小于$24$小时即$1440$分钟）
   - 若第二个比第一个大，先相减再加上$24$小时即$1440$分钟。
4. 将相减的结果$\mod1440$，再转成时和分，再利用``printf``在前面补零即可。

这里我推导出了公式：
$$ans=(h1\times60+m1-h2\times60-m2+1440)\mod1440$$

------------
代码（极度舒适）：
```cpp
#include<cstdio>
int a,b,c,d;
int main(){
	scanf("%d:%d%d:%d",&a,&b,&c,&d);//输入
	int k=(a*60+b-c*60-d+1440)%1440;//套用公式
	printf("%02d:%02d\n",k/60,k%60);//转成时和分再输出
}
```

---

## 作者：恨穹不是妹 (赞：0)

~~来来来，大家做紫题啦~~~
好的，
这道题
### 应该
非常简单吧

因为他只是需要用前一个时间减去后一个时间在特判一下特殊情况就可以得出答案了，主要是输入的时候可以不用字符输入，可以节省很大分量的代码，

~~看着一群大佬字符读入瑟瑟发抖~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c,d;
	scanf("%d:%d",&a,&b);//输入的时候忽略“：”
	scanf("%d:%d",&c,&d);//输入的时候忽略“：”
	if(a<c)//如果是前一天的就加上24个小时
	{
		a+=24;
	}
	else
	{
		if(b<d)
		{
			a+=24;
		}
	}
	if(b<d){
	if((a-c-1)%24<10)
	cout<<0;//不用字符串输出的
	cout<<(a-c-1)%24<<":";
	if(b+60-d<10)
	cout<<0;//不用字符串输出的，可特判是否小于10
	cout<<b+60-d;
	}
	else
	{
	if((a-c)%24<10)//一定要记得%24，不然答案会大于24
	cout<<0;
	cout<<(a-c)%24<<":";
	if(b-d<10)
	cout<<0;
	cout<<b-d;
	}
}
```

---

## 作者：CobaltChloride (赞：0)

```
//本题求出两个时间的差(上减下)
#include<bits/stdc++.h>
using namespace std;
int s,t,p;
string strs,strt,strp;
int main(){
    cin>>strt>>strs;
    s=600*(strs[0]-48)+60*(strs[1]-48)+10*(strs[3]-48)+strs[4]-48;
    t=600*(strt[0]-48)+60*(strt[1]-48)+10*(strt[3]-48)+strt[4]-48;
    //把读入的时间转化成分钟数
    p=t-s;
    if(p<0) p+=1440;
    //算出睡觉的分钟数,注意若睡了一夜要加上一天(1440分钟)
    printf("%c",p/600+48);
    p%=600;
    printf("%c",p/60+48);
    p%=60;
    printf(":");
    printf("%c",p/10+48);
    p%=10;
    printf("%c",p+48);
    //输出时间
    return 0;
}
```

---

