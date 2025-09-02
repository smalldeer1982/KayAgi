# [ARC002B] 割り切れる日付

## 题目描述

高桥君很喜欢“整除日”。

“整除日”就是指日期中，年÷月÷日的值是整数的日期。

比如说2012年5月2日这一天，因为2012÷5÷2=201.2，结果不是整数，所以这天不是“整除日”。

因为高桥君实在太喜欢“整除日”了，总是盼着下一个“整除日”，所以他每天都要查一下今天是不是“整除日”。

他还很想知道下一个“整除日”什么时候到来。

输入一个日期，他希望输出这个日期之后最近的“整除日”。特别地，如果输入就是“整除日”，那么就输出输入的这个日期。

## 说明/提示

输入日期在1000/01/01和2999/12/31之间。


感谢@Disconsolate 提供的翻译

# 题解

## 作者：Chen_cntj (赞：38)

### 水题
~~但是被卡了很久~~

------------
### 提要
找出离输入时间最近的整除日。一天一天枚举就行了。另外还要判断新月和新年。

已有的四篇题解都是用for来循环，外加月份输出特判；其实没必要那么深奥：
### 创新之处
1.使用while循环，专为喜爱暴力枚举的你打造。

2.全新输出方法,再也不用为特判烦恼啦！ 
```cpp
cout<<y<<'/'<<m/10<<m%10<<'/'<<d/10<<d%10<<endl;
```
#### 我们以1000年10月1日为例：

输出y：1000

输出/：1000/

输出m/10，10/10=1：1000/1

输出m%10，10%10=0：1000/10

输出/：1000/10/

输出d/10，1/10=0：1000/10/0

输出d%10，1%10=1：1000/10/01

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int y,m,d,t;
int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//前面没开数组结果被整到怀疑人生，在此提醒各位，数组还是要开的。
char ch;
bool leap(int year)//闰年
{
	return (!(year%4)&&year%100||!(year%400));
}
int main()
{
	cin>>y>>ch>>m>>ch>>d;
	if (leap(y))
	  a[2]++;
	while (y%(d*m))//如果不是整除日，就继续枚举
	{
		++d;
		if (d>a[m])
		{
			m++;
			d=1;
		}
		if (m>12)
		{
			++y;
			m=1;
		}	
    }
    cout<<y<<'/'<<m/10<<m%10<<'/'<<d/10<<d%10<<endl;//输出别忘换行
	return 0;
}
```
熬了三天才AC啊，体谅一下我的辛苦吧！

---

## 作者：Soyilieber (赞：4)

这道题，十分简单，字符串+循环

分析题目，循环找到满足条件的日期就ok，但是要判断闰年（[点击查看如何判断](https://marshalken.blog.luogu.org/solution-at53)），还有区分大小二月。
### 注意！ 如果这一年都没有满足条件的日期，则输出次年1月1日。

### 代码如下
```pascal
var
    j,k,days,y,m,d:longint;//j,k月日循环变量 days月份天数上限，y m d日期
    s:string;
    rn:boolean;//判断闰年
begin
    readln(s);//输入
    val(copy(s,1,4),y);
    val(copy(s,6,2),m);
    val(copy(s,9,2),d);//拆分
    if ((y mod 4=0)and(y mod 400<>0)and(y mod 100<>0))or((y mod 4=0)and(y mod 400=0)) then rn:=true;
    for j:=m to 12 do//月份循环
        begin
            //判断月份，赋予月份天数上限----------------------------
            case j of
                1,3,5,7,8,10,12:days:=31;
                4,6,9,11:days:=30;
                2:days:=28;
            end;
            if (j=2)and(rn) then days:=29;
            //----------------------------------------------------
            for k:=d to days do//日期循环
                if (y mod j=0)and(y div j mod k=0) then//满足条件
                    begin
                        write(y,'/');
                        if j<10 then write(0);//补0
                        write(j,'/');
                        if k<10 then write(0);
                        write(k);
                        writeln;//换行，满足题目要求
                        halt;//退出
                    end;
            d:=1;//下个月的日期循环从1号开始
        end;
    writeln(y+1,'/01/01');//如果这一年没有一天满足条件则输出下一年1月1日
end.
```

---

## 作者：⚡YMJcvjk⚡ (赞：3)

## Pascal&C++题解，求过  
```
题目:高桥君很喜欢“整除日”  AT54【割り切れる日付】  
“整除日”就是指日期中，年÷月÷日的值是整数的日期。  
比如说2012年5月2日这一天，因为2012÷5÷2=201.2，结果不是整数，所以这天不是“整除日”。  
因为高桥君实在太喜欢“整除日”了，总是盼着下一个“整除日”，所以他每天都要查一下今天是不是“整除日”。  
他还很想知道下一个“整除日”什么时候到来。  
输入一个日期，他希望输出这个日期之后最近的“整除日”。特别地，如果输入就是“整除日”，那么就输出输入的这个日期。  
输入格式：  
输入格式如下：  
Y/M/D，表示Y年M月D日，Y为4位，M、D为两位，如果不足，会在前面补上0。  
输出格式：  
输出也按输入的格式输出，即XXXX/XX/XX，位数不足则用0补齐。  
最后换行。  
范围：  
输入日期在1000/01/01和2999/12/31之间。  
感谢@Disconsolate 提供的翻译
```
废话不多说，开始做。  
第一眼看了一下，大概想了想，模拟这一个过程，似乎是最好的方法。  
先将月份从开始到12月穷举，再把日期模拟一遍（**注意:开始的月份日期从输入给出的开始，而后面的就必须要从1开始**），你认为似乎没错了，可是，很重要的一点，如果这一年都没有整除年，要输出下一年的1月1日（因为任何数都是1的倍数），如果这一点没想到，只能过大约70个点。  
**先上一份Pascal**
```cpp
# AT54 【割り切れる日付】
# 作者 @YMJcvjk
# 语言 Pascal
# 代码长度 0.78KB
# 时间 0ms
# 空间 0mb
var
 date:ansistring;
 year,month,day,i,j,k:longint;
 count:array[1..12] of 28..31=(31,28,31,30,31,30,31,31,30,31,30,31);  //初始化
function leap_year(year:longint):boolean;
begin
 if (year mod 400=0) or ((year mod 4=0) and (year mod 100<>0)) and (year mod 3600<>0) then exit(true) else exit(false);  //判断是否是闰年，值得注意的一点（虽然这一题不用），但是还是要提的:被3600整除的不是闰年。
end;
begin
 readln(date);
 val(copy(date,1,4),year); // 取出数字
 val(copy(date,6,2),month);
 val(copy(date,9,2),day);
 for i:=month to 12 do
  begin
   if leap_year(year) and (i=2) then count[2]:=29 else count[2]:=28; //确定2月的天数，为啥改28，因为还原是种好习惯
   for j:=day to count[i] do
    if (year mod i=0) and (year div i mod j=0) then
     begin
      write(year);
      if i<10 then write('/0',i) else write('/',i);  //输出要补零
      if j<10 then write('/0',j) else write('/',j);  //同上
      writeln;
      halt;
     end;
     day:=1; //改为1
  end;
  writeln(year+1,'/01/01'); //本题坑点
end.
```
看过了Pascal，来一份C++
```cpp
# AT54 【編集】割り切れる日付
# 作者 @YMJcvjk
# 语言 C++
# 代码长度 0.75KB
# 时间 125ms
# 空间 256mb
#include<bits/stdc++.h>
 using namespace std;
  char ch1,ch2;
  int year,month,day,i,j;
  int Count[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  bool leap_year(int year)
  {
    return (year%400==0||year%4==0&&year%100!=0)&&year%3600!=0;
  }
  int main()
  {
      cin>>year>>ch1>>month>>ch2>>day;
      for(i=month;i<=12;++i)
      {
          if(i==2&&leap_year(year)) Count[2]=29; else Count[2]=28;
          for(j=day;j<=Count[i];++j)
          if(year%i==0&&year/i%j==0)
          {
              cout<<year;
              if(i<10) cout<<"/0"<<i; else cout<<"/"<<i;
              if(j<10) cout<<"/0"<<j; else cout<<"/"<<j;
              cout<<endl;
              return 0;
          }
          day=1;
      }
      cout<<year+1<<"/01/01"<<endl;
      return 0;
  }
```
 _**AT大坑，输出换行**_ 

---

## 作者：TRZ_2007 (赞：2)

## Remarks
这题居然有100+数据！%%%  
## Solution
这题目看着简单，其实做起来还是很麻烦的，不知道是不是我想复杂了，因为这题首先要依次枚举每个日期，输出还要带补全，最重要的是，还要判断闰年！  
让我们把这题分解开来讲：  
- 1：判断是否为整除日：

这个应该还是挺好判断的，只需要判断年是否能被月乘日给整除即可。由于后面还需要判断，所以我们写个函数。

```
bool Judge(int a,int b,int c)
{
	return !(a%(b*c));
}
```

- 2：枚举年月日：

这个有点麻烦，因为我们需要做好多的进位（日->月，月->年），所以我们也需要好多的特判。

- 3：补全：

这个可能会有一些简单的方法，但是位数较小，暴力即可。


接下来就是代码的实现了。

## $code$

```
#include <bits/stdc++.h>
using namespace std;

int year,month,day;
int flag;

bool Judge(int a,int b,int c)
{
	return !(a%(b*c));
}

int main()
{
	scanf("%d/%d/%d",&year,&month,&day);
	if(Judge(year,month,day))
	{
		if(year<1000)//暴力补全
		{
			if(year<10) cout<<"000";
			else if(year<100) cout<<"00";
			else cout<<"0";
		}
		cout<<year<<"/";
		if(month<10) cout<<"0";
		cout<<month<<"/";
		if(day<10) cout<<"0";
		cout<<day<<"\n";
		return 0;
	}
	while(1)//枚举最近的整除日
	{//处理进位
		if((year%4==0)&&(year%100!=0)||(year%400==0)) flag = 1;
		day++;
		if(!flag&&month==2&&day>28) month++,day = 1;
		else if((month<=6)&&(month%2)&&(day>31)) month++,day = 1;
		else if((month<=6)&&!(month%2)&&(day>30)) month++,day = 1;
		else if((month>6)&&(month!=7)&&(month%2)&&(day>30)) month++,day = 1;
		else if((month>6)&&(!(month%2)||(month==7))&&(day>31)) month++,day = 1;
		else if((flag)&&(month==2)&&(day>29)) month++,day = 1;
		if(month>12) year++,month = 1;
		if(Judge(year,month,day))//补全
		{
			if(year<1000)
			{
				if(year<10) cout<<"000";
				else if(year<100) cout<<"00";
				else cout<<"0";
			}
			cout<<year<<"/";
			if(month<10) cout<<"0";
			cout<<month<<"/";
			if(day<10) cout<<"0";
			cout<<day<<"\n";
			return 0;
		}
	}
}
```

---

## 作者：climax (赞：1)

这道题其实很简单，首先依次输入年/月/日，然后再进行月份和日期的循环,找到满足条件的日期就可以了。
但是如果这一年都没有满足要求的，就输出下一年的1月1日。
上AC代码：
```c
#include<bits/stdc++.h>
using namespace std;
int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//对每一个月的天数赋值。
int main()
{
  int x,i,j,d,z,q,k,l,n,m;//不要问我为什么定义这么多没用的变量。
  char c;//定义一个字符。
  cin>>i>>c>>j>>c>>d;//输入。
 if(i%4==0&&i%100!=0&&i%400!=0||i%400==0&&i%4==0)//判断闰年，如果这一年是闰年。
   a[2]=29;//2月就变成29天。
  for(n=j;n<=12;n++)//月份循环。
  {
  	for(m=d;m<=a[n];m++)//天数循环。
  	{
  	if(i%n==0&&(i/n)%m==0)//判断是否为整除日。
	  {//如果是，就输出。
	  	cout<<i<<'/';//先输出年份
	  	 if(n<10)//判断，如果月份不足两位就在n前面补零。
	       cout<<0<<n<<'/';
	     else//否则，就直接输出月份。
	      cout<<n<<'/';
	     if(m<10)//判断，如果天数不足两位就在m前面补零。
	       cout<<0<<m<<endl;
         else//否则，就直接输出天数。
	      cout<<m<<endl;	
		return 0;//结束。		
	  }	
  }  
  if(n==12)//如果这一年都没有满足要求的日期。
  {
  	 i++;
    cout<<i<<'/'<<0<<1<<'/'<<0<<1<<endl;//就输出下一年的1月1日。
   return 0;//结束。
  }
	 d=1;//下一个月的天数从1开始。
   }
   return 0;//完美结束。
}//so easy!
```

---

## 作者：Yo_haor (赞：1)

楼下的dalao都写的很好，下面看看我的qwq

其实方法都很简单：

#   $\color{red}\text{暴 力 枚 举}$

方法：枚举天数，直到找到为止和年月日的变换

楼下那位dalao虽然很方便，但我觉得ta讲得不是很清楚，接下来我再来解释解释：

$\color{blue}\text{1、年只会4位数，无需判断。}$ 

$\color{blue}\text{2、月其实只有两种情况：大于9和小于10。所以只用除以10就可以是输出月的第一位，剩下的求余数即可。}$

$\color{blue}\text{3、日和月一样，有两种情况大于9和小于10。所以和月的方法一样。。}$

这是输出要特判的语句：
```cpp
cout<<year<<"/";
if(month<10) cout<<"0";
	cout<<month<<"/";
if(day<10) cout<<"0";
	cout<<day<<"\n";
```

这是输出不用特判的语句：
	
  ```cpp
 cout<<year<<'/'<<month/10<<month%10<<'/'<<day/10<<day%10;
```

    
是不是很简洁呢？qwq
    
好了方法说完了，上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;//大家都懂就不说了
int year,month,day;//定义年月日
int y[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//将每月的天数存起来
string st;
int main()
{
	cin>>st;
	year=int((st[0]-48)*1000+(st[1]-48)*100+(st[2]-48)*10+st[3]-48);
	month=int((st[5]-48)*10+st[6]-48);
	day=int((st[8]-48)*10+st[9]-48);
    //将字符串转成数字，可能有点麻烦，如有不好请各位dalao指出qwq
	while(year%(month*day)!=0)//停止条件
	{   
        if(year%4==0&&year%100!=0||year%400==0)y[2]=29;//判断是否是闰年
		day++;//将日++
		if(day>y[month])//判断日是否大于当前月份的数量
		{
			day=1;//将日变成1
			month++;//月份++
			if(month>12)month=1,year++;//判断月份是否大于12，如果是年++
		}
	}
	cout<<year<<'/'<<month/10<<month%10<<'/'<<day/10<<day%10;//输出
	cout<<'\n';//记得换行！！！
	return 0;
}
```

---

## 作者：不到前10不改名 (赞：1)

//本题已经加上防伪标识以及改动
```
#include<stdio.h>
int srx,sry,lhy,mzy,zjq,lgx[13]={31,27,31,30,31,30,31,31,30,31,30,31};//每月天数的储存
char t;//吃/的
int main()
{
   scanf("%d%c%d%c%d",&srx,&t,&sry,&t,&lhy);
   if(srx%4==0&&srx%100!=0&&srx%400!=0||srx%400==0&&srx%4==0)
   lgx[2]=29;//闰年的话2月29天
   for(mzy=sry;mzy<=12;mzy++)
   {for(zjq=lhy;zjq<=lgx[mzy];zjq++)
   if(srx%mzy==0&&(srx/mzy)%zjq==0)//整除日判断,暴力模拟
   {if(mzy>9&&zjq>9)//不用补零的情况
   {printf("%d/%d/%d\n",srx,mzy,zjq);
   return 0;}
   else if(mzy<10&&zjq<10)//233一开始写的9，怎么也过不去~这里是都要补零的情况
   {printf("%d/0%d/0%d\n",srx,mzy,zjq);
   return 0;}
   else if(zjq<10)//只补日
   {printf("%d/%d/0%d\n",srx,mzy,zjq);
   return 0;}
   else if(mzy<10)//只补月
   {printf("%d/0%d/%d\n",srx,mzy,zjq);//回车补零不能忘
   return 0;}}
   lhy=1;}//天数要清零，不直接从1的原因是前面还用到它一次
   printf("%d/01/01\n",srx+1);//隐藏条件：若一年内没有，就输出明年一月一日，因为前面如果符合已经return了，所以无需再次判断了QAQ
   return 0;
}
```

---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题我先枚举年份，再枚举月份最后枚举天数，找到一个就退出程序。具体思路，请看下方代码······

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int n,y,r;//年月日定义
    int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    //月份的天数数组，方便后面枚举天数
    int main()
    {
    scanf("%d/%d/%d",&n,&y,&r);//读入年月日
    for(int i=n; ; i++)//枚举年
    {
        int j;
        if(i==n)j=y;//如果i是当前这一年，j为当前月份
        else j=1;//否则为1
        if(i%4==0&&i%100!=0||i%400==0)month[2]=29;//如果是闰年二月份天数变29
        else month[2]=28;//否则仍然是28
        for(;j<=12; j++)//枚举月
        {
            int k;
            if(i==n&&j==y)k=r;//如果i为当前年份、j为当前月份，就从初始年月日开始枚举
            else k=1;//否则从这个月的第一天开始枚举
            for(; k<=month[j]; k++)//枚举天
            {
                if(i%(j*k)==0)//如果是“整除日”，进行以下操作：
                {
                    cout<<i<<'/';//输出当前年份
                    if(j>=1&&j<=9)cout<<0;//如果月份小于10，前面还有个0
                    cout<<j<<'/';//输出月份
                    if(k>=1&&k<=9)cout<<0;//如果当前天数小于10，前面还有个0
                    cout<<k<<endl;//输出天数，记得换行
                    return 0;//退出程序
                }
            }
        }
    }
    return 0;//要有好习惯
    }
    
好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

