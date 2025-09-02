# Calendar

## 题目描述

Calendars in widespread use today include the Gregorian calendar, which is the de facto international standard, and is used almost everywhere in the world for civil purposes. The Gregorian reform modified the Julian calendar's scheme of leap years as follows:

 Every year that is exactly divisible by four is a leap year, except for years that are exactly divisible by 100; the centurial years that are exactly divisible by 400 are still leap years. For example, the year 1900 is not a leap year; the year 2000 is a leap year.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF304B/f8498332105130efe5e68ba02dfcaba5e2afd72f.png)In this problem, you have been given two dates and your task is to calculate how many days are between them. Note, that leap years have unusual number of days in February.

Look at the sample to understand what borders are included in the aswer.

## 样例 #1

### 输入

```
1900:01:01
2038:12:31
```

### 输出

```
50768
```

## 样例 #2

### 输入

```
1996:03:09
1991:11:12
```

### 输出

```
1579
```

# 题解

## 作者：无意识躺枪人 (赞：26)

~~来水一波紫题题解~~

不知道为什么大家都用的模拟，这里给一个数学方法

```c
#include<bits/stdc++.h>
using namespace std;

long long Calculation(int y,int m,int d)
{
	if (m<3) {y-=1;m+=12;}
	return 365*y+y/4-y/100+y/400+(153*m-457)/5+d-306;
}

int main()
{
	int y,m,d;
	scanf("%d:%d:%d",&y,&m,&d); long long a=Calculation(y,m,d);
	scanf("%d:%d:%d",&y,&m,&d); long long b=Calculation(y,m,d);
	printf("%lld\n",abs(b-a));
    return 0;
}
```

${Calculation}$函数可以返回某一日期距0的天数

相减取绝对值就好了

除此之外，P党也可以用 ${datetime.datetime.strptime}$ 水过去

$\color{white}\text{送我上去}$ ←←←

---

## 作者：ygsldr (赞：11)

这不是python水题吗，使用python的datatime包
```
import datetime
t1 = datetime.datetime.strptime(input(),"%Y:%m:%d")
t2 = datetime.datetime.strptime(input(),"%Y:%m:%d")
print(abs((t2-t1).days))
```

还有一种数学一点的解法（来自CF题解）

```
def get(y, m, d):
    if(m < 3):
        y -= 1
        m += 12
    return 365 * y + y // 4 - y //100 + y//400 + (153*m-457)//5+d-306
```

可以返回0年到现在过了多少天，减一下就好了（PS:这个公式可以手推的，很简单的，我就不推了）

---

## 作者：Fractures (赞：8)

# 啊啊啊啊！为什么黑题掉紫了？我本来想水一道黑题啊！

……不过即便如此，这还是我第一次写紫题题解欸，鸡冻~

其实这道题~~很简单~~，思路就是把中间的几年算出来，再把第一年到第二年算出来，再就把第二年算出来就行了

```cpp
#include<cstdio>
#include<iomanip>
using namespace std;
int year1,month1,day1;
int year2,month2,day2;
int date;
int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
bool runnian(int n){//判断闰年
    bool flag=false;
    if((n%4==0&&n%100!=0)||n%400==0)flag=true;
    return flag;
}
int main(){
    scanf("%d:%d:%d",&year1,&month1,&day1);
    scanf("%d:%d:%d",&year2,&month2,&day2);
    if(year1>year2||(year1==year2&&month1>month2)||(year1==year2&&month1==month2&&day1>day2)){//保持year2比year1大
        swap(year1,year2);
        swap(day1,day2);
        swap(month1,month2);
    }
    for(int i=year1+1;i<year2;i++){//算出中间的几年
        date=date+365;
        if(runnian(i)==true){//多加一天
    	    date++;
    	}
    }
    for(int i=1;i<=month2;i++){//算出year2有几天
        for(int j=1;j<=months[i];j++){
            date++;
            if(runnian(year2)==true){
                if(i==2&&j==28)date++;
            }
            if(i==month2&&j==day2)break;
        }
    }
   for(int i=month1;i<=12;i++){//算出year1有几天
        for(int j=1;j<=months[i];j++){
            date++;
            if(runnian(year1)==true){
                if(i==2&&j==28)date++;
            }
        }
    } 
    date=date-day1;
    if(year1==year2){//特判
        date=date-365;
        if(runnian(year1)==true)date--;
    }
    if(year1==year2&&month1==month2&&day1==day2)date=0;//暴力特判(本人很懒)
    printf("%d",date);
    return 0;
}
```

---

## 作者：一座城·守一人 (赞：4)

# 我个人做这种题的方法(不喜勿喷)
## 给了你两个日期，让你求出这两个日期的差值
** 直接把这两个日期换算成距离某一天的时间的日期数，这个某一天可以随便选择，只要是小于等于题目给的数据范围$(1900:01:01)$就可以。**
** 最后直接让两个天数一相减，输出这个数字的绝对值，就是所求的(两个日期天数之差)。**
### 注意判断闰年！！！

$P.s$ 你们也可以把输入的日期先后排一下序，**~~然鹅我还是太懒~~** **有时间给你们写一下**

```
#include<bits/stdc++.h>
using namespace std;
int da1,da2,month[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};//直接保存每个月的天数
bool checkrun(int yy) {//判断闰年
	if(yy%4)return false;
	if(yy%400==0)return true;
	if(yy%100==0)return false;
	return true;
}
int main() {
	ios::sync_with_stdio(false);//关闭cin与stdin的同步，提高读入速度(然并卵)
    //(我知道cz大佬又要说我对新人不友好，那么新人就不要看这行了)
	int y1,m1,d1,y2,m2,d2;
	char s;
	cin>>y1>>s>>m1>>s>>d1;//把冒号枪毙掉
	cin>>y2>>s>>m2>>s>>d2;
	for(int i=1900; i<y1; i++) {//从1900年到给定年的前一年的每一年的天数相加(注意是给定年的前一年！！！)
		if(checkrun(i))da1+=366;//闰年就要加366天
		else da1+=365;
	}
	for(int i=1900; i<y2; i++) {
		if(checkrun(i))da2+=366;
		else da2+=365;
	}
	for(int i=1; i<m1; i++) {//从1月到给定月的前一个月的每个月的月数相加(还用我说注意吗QwQ)
		if(i==2&&checkrun(y1))da1+=29;
		else da1+=month[i];
	}
	for(int i=1; i<m2; i++) {
		if(i==2&&checkrun(y2))da2+=29;
		else da2+=month[i];
	}
	da1+=d1;da2+=d2;//从……(不不不只是在开玩笑)
	cout<<abs(da1-da2);//输出绝对值
	return 0;
}
```

---

## 作者：Chiaro (赞：2)

## 一道模拟

#### emmmmmm....黑...黑题... $ QAQ$ ?

我的做法就是分别讨论两个起始点:

> 1.年份不相同

> 2.月份不相同,年份相同

> 3.月份年份都相同

我好菜啊...代码写的有点麻烦,大佬不要打我... $ QWQ $

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define sc scanf//偷懒(
using namespace std;
int yyy,ddd,mmm;//起始点
int yy,dd,mm;//终止点
int ans;
short d[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
short D[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
//对应的是闰年与非闰年每个月的天数...emmm...好像有点麻烦
inline bool r(int x){//判断他是不是闰年
	if(x%100==0){
		if(x%400==0)return 1;
		return 0;
	}
	if(x%4==0)return 1;
	return 0;
}
inline void start(){
	if(yyy>yy||(yyy==yy&&mmm>mm)|(yyy==yy&&mmm==mm&&ddd>dd){
		swap(yyy,yy);//如果起始点比终止点时间还要靠后
		swap(mmm,mm);//就要交换
		swap(ddd,dd);
	}
}
inline void WORK(){//如果年份相同,那只考虑月份和日
	for(int i=mmm+1;i<mm;i++){//将起点与终点之间的日加起来
		if(r(yyy))ans+=D[i];
		else ans+=d[i];
	}
	if(r(yyy)){//考虑起点与终点
		ans+=D[mmm]-ddd;
		ans+=dd;
	}
	else {
		ans+=d[mmm]-ddd;
		ans+=dd;
	}
	return;
}
inline void work(){//全不同,思路同月份一样
	for(int i=yyy+1;i<yy;i++){//年
		if(r(i))ans+=366;
		else ans+=365;
	}
	for(int i=mmm+1;i<=12;i++){//月
		if(r(yyy))ans+=D[i];
		else ans+=d[i];
	}
	for(int i=1;i<mm;i++){
		if(r(yy))ans+=D[i];
		else ans+=d[i];
	}
	if(r(yyy))ans+=D[mmm]-ddd;//日
	else ans+=d[mmm]-ddd;
	if(r(yy))ans+=dd;
	else ans+=dd;
	return;
}
inline void Work(){//只有日不相同
	ans+=dd-ddd;
	return;
}
int main(){
	sc("%d:%d:%d%d:%d:%d",&yyy,&mmm,&ddd,&yy,&mm,&dd);
    //嘛...scanf输入方便一点吧...
	start();
	if(yyy==yy&&mmm!=mm)WORK();//对于年份相同
	else if(yyy==yy&&mmm==mm)Work();//对于年份月份都相同
	else work();//都不同
	cout<<ans<<'\n';
	return 0;
} 
```

---

## 作者：_Spectator_ (赞：0)


[可能更好的食用体验](https://www.luogu.com.cn/blog/523641/CF304B) $|$ 
[题目传送门](https://www.luogu.com.cn/problem/CF304B) $|$ 
[我的其他题解](https://www.luogu.com.cn/blog/523641/#type=题解)

------------

### ${\color{#00CD00}\text{主要思路}}$

由于数据并不大，所以只需要模拟其中的每一天即可。

具体实现方式：

1. 将日增加 $1$。
2. 判断当前的日是否大于当前月份的天数。若是，将日变成 $1$ 并增加月。
3. 判断月数是否大于 $12$ 。若是，将月变成 $1$ 并增加年。
4. 判断当前年份是否为闰年。若是，改变 $2$ 月的天数。

------------

### ${\color{#00CD00}\text{完整代码}}$

```cpp
#pragma G++ optimize(2)　
#include<bits/stdc++.h>　
using namespace std;　
long long y,m,d,y2,m2,d2,ans;　
int s[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};　
int main()　
{　
	scanf("%lld:%lld:%lld",&y,&m,&d);//使用scanf格式化输入可以很方便地读入数据 
	scanf("%lld:%lld:%lld",&y2,&m2,&d2);　
	if(y>y2||y==y2&&m>m2||y==y2&&m==m2&&d>d2)//判断日期1是否比日期2大 
		swap(y,y2),swap(m,m2),swap(d,d2);　
	while(y!=y2||m!=m2||d!=d2)　
	{　
		if(y%4==0&&y%100!=0||y%400==0)s[2]=29;　
		else s[2]=28;//判断闰年并改变二月的天数 
		d++,ans++;　
		if(d>s[m])d=1,m++;　
		if(m>12)m=1,y++;　
	}　
	cout<<ans;　
	return 0;　
}　
```

**[${\color{Black}\text{xt\_\_}}$](https://www.luogu.com.cn/user/523641) 温馨提示：**

${\color{White}\colorbox{#AD8800} {题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：xtr169 (赞：0)

**题目大意**

给两个日期，输出两个日期中隔了多少天

**题目分析**

这道题可以用**模拟或计算**

其中计算方法时间复杂度比较低

这篇题解发计算方法

**具体实现**

首先用
```cpp
scanf("%d:%d:%d",&y,&m,&d);
```

的方式输入，具体如下
```cpp
scanf("%d:%d:%d",&y,&m,&d);//输入第一个日期
scanf("%d:%d:%d",&yy,&mm,&dd); //第二个

```
然后定义一个函数解决计算，最后输出，下面是计算的函数

```cpp
int dimd(int yyy,int mmm,int ddd)
{
	int ans;
	if (mmm<3)
	{
		mmm+=12;
		yyy--; 
	}
	ans=365*yyy+yyy/4-yyy/100+yyy/400+(153*mmm-457)/5+ddd-306;
	return ans;
}
```
具体的代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int y,m,d,yy,mm,dd,t1,t2;
int dimd(int yyy,int mmm,int ddd)
{
	int ans;
	if (mmm<3)
	{
		mmm+=12;
		yyy--; 
	}
	ans=365*yyy+yyy/4-yyy/100+yyy/400+(153*mmm-457)/5+ddd-306;
	return ans;
}
int main()
{
	scanf("%d:%d:%d",&y,&m,&d); 
	t1=dimd(y,m,d);
	scanf("%d:%d:%d",&yy,&mm,&dd); 
	t2=dimd(yy,mm,dd);
	cout<<(t1>t2?t1-t2:t2-t1);
    return 0;
}
```

完美撒花

---

## 作者：灵光一闪 (赞：0)

~~这个题绝对是恶评题~~

我才拿到这个题时莫名感觉很难，一看数据范围，emming……，暴力轻松水过……

没啥好讲的，直接看代码吧：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<string>
using namespace std;
int tep=0;
int y,m,d;
int Y,M,D;
int ans;
const int big[]={1,3,5,7,8,10,12};//大月
const int small[]={4,6,9,11};//小月
int rn(int y){//基础知识：判闰年
    if(y%100==0){
        if(y%400==0){
            return 1;
        }
        else{
            return 0;
        }
    }
    if(y%4==0){
        return 1;
    }
    return 0;
}
int main(){
    scanf("%d:%d:%d",&y,&m,&d);
    scanf("%d:%d:%d",&Y,&M,&D);
    if(y>Y){//这题有点坑，数据不一定是后面大于前面
        int tep=y;
        y=Y;
        Y=tep;
        tep=m;
        m=M;
        M=tep;
        tep=d;
        d=D;
        D=tep;
    }
    else if(y==Y){
        if(m>M){
            int tep=y;
            y=Y;
            Y=tep;
            tep=m;
            m=M;
            M=tep;
            tep=d;
            d=D;
            D=tep;
        }
        else if(m==M){
            if(d>D){
                int tep=y;
                y=Y;
                Y=tep;
                tep=m;
                m=M;
                M=tep;
                tep=d;
                d=D;
                D=tep;
            }
            else if(d==D){
                puts("0");
                return 0;
            }
        }
    }
    for(int i=0;i<7;i++){//先判断这年的天数
        if(big[i]==m){//m是大月
            tep=31;//这个月31天
            goto ok;//开始循环
        }
    }
    for(int i=0;i<4;i++){//小月
        if(small[i]==m){//m是小月
            tep=30;//这个月30天
            goto ok;//开始循环
        }
    }
    tep=28+rn(y);//如果都不是就确定是2月
ok:
    while(1){
//        cout<<y<<" "<<m<<" "<<d<<endl;
        if(y==Y&&m==M&&d==D){//当循环到了后就break
            break;
        }
        if(d==tep){//这个月跑完了
            d=0;
            if(m==12){//如果这个月是12月
                y++;//新的一年
                m=1;//赋值为1月
            }
            else{
                m++;//月份++
            }
            for(int i=0;i<7;i++){//上文有提到，这里不讲了
                if(big[i]==m){
                    tep=31;
                    goto work;//相当于一个跳过
                }
            }
            for(int i=0;i<4;i++){
                if(small[i]==m){
                    tep=30;
                    goto work;
                }
            }
            tep=28+rn(y);
        }
    work:
        d++;//向前走一天
        ans++;//过了一天
    }
    printf("%d",ans);//输出
    return 0;//结束
}
```
The End.

---

## 作者：ykkz000 (赞：0)

这也是紫题。。。

可以通过计算距离公历元年的天数来相减。

年和日都好处理，(year-1)*365+day即可

月可以打表

闰年用公式可求出应当多多少天

注意，若year为闰年要到3月才加一，故应当特判是否把多加的减去

代码中没有太多注释
```cpp
#include<cstdio>
#include<cstdlib>
const int m[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int year,month,day;
int ans[3],rest[3];
int main(){
    scanf("%d:%d:%d",&year,&month,&day);
    ans[1]=(year-1)*365+day;
    for(register int i=1;i<month;i++) ans[1]+=m[i];
    rest[1]=year/400-year/100+year/4; //闰年
    if((month<2||month==2)&&((year%400==0)||((year%4==0)&&(year%100)!=0))) rest[1]-=1;  //没过2月19日，应把多加的减去
    ans[1]+=rest[1];
    scanf("%d:%d:%d",&year,&month,&day);
    ans[2]=(year-1)*365+day;
    for(register int i=1;i<month;i++) ans[2]+=m[i];
    rest[2]=year/400-year/100+year/4; //道理同上
    if((month<2||month==2)&&((year%400==0)||((year%4==0)&&(year%100)!=0))) rest[2]-=1;
    ans[2]+=rest[2];
    printf("%d",abs(ans[1]-ans[2]));
    return 0;
}
```

---

## 作者：不到前10不改名 (赞：0)

//老套路，已经加上防伪标识以及改动
```
#include<stdio.h>
int n,srx,sry,i,lhy,mzy,zjq,lgx,t,qaq;
char t;
int main()
{
     scanf("%d%c%d%c%d",&srx,&c,&sry,&c,&lhy);
     scanf("%d%c%d%c%d",&mzy,&c,&lgx,&c,&zjq);
     if(srx>mzy||srx==mzy&&sry>lgx||srx==mzy&&sry==lgx&&lhy>zjq)
     {t=srx;
     srx=mzy;
     mzy=t;
     t=sry;
     sry=lgx;
     lgx=t;
     t=lhy;
     lhy=zjq;
     zjq=t;}//这里是一个判断，因为相差，没说是谁大谁小，所以判断交换
     qwq=qwq-lhy+zjq;//先把不是整年的日和月做掉
     while(sry)
     {sry--;
     if(sry==1||sry==3||sry==5||sry==7||sry==8||sry==10||sry==12)
     qwq-=31;//大月
     else if(sry==2&&(srx%4==0&&srx%100||srx%400==0))
     qwq-=29;//闰年2月
     else if(sry==2)
     qwq-=28;//平年2月
     else
     qwq-=30;}//小月
     while(lgx)
     {lgx--;
     if(lgx==1||lgx==3||lgx==5||lgx==7||lgx==8||lgx==10||lgx==12)
     qwq+=31;
     else if(lgx==2&&(mzy%4==0&&mzy%100||mzy%400==0))
     qwq+=29;
     else if(lgx==2)
     qwq+=28;
     else
     qwq+=30;}
     for(i=srx;i<=mzy-1;i++)
     {if(i%4==0&&i%100||i%400==0)//注意2000年也是闰年
     qwq+=366;//闰年
     else
     qwq+=365;}//平年
     printf("%d",qwq);
     return 0;
     }
```

---

## 作者：BADFIVE (赞：0)

**思路**：给你两个日期 $(x,y)$ ,求 $x,y$ 相差多少。   
一开始，我看到这里就直接想到贪心，但是题目后面给到需要注意闰年 
   
那我们这样就需要麻烦几步，我们可以直接写一个判断闰年的函数:   
```cpp
int runnian(int y){
    if(y%4==0&&y%100!=0||y%400==0){
    	return 1;
	}
    return 0;
}
```
然后，我们就算出 $x,y$ 分别是多少天，然后相减得到结果，这样我们就可以直接根据模拟打出来   

参考代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//打表出每月的天数 
int runnian(int y){
    if(y%4==0&&y%100!=0||y%400==0){
    	return 1;
	}
    return 0;
}
int y,m,d;
int f(){//相差多少天的函数 
    int sum=0;
    for(int i=1;i<y;i++){
        sum+=365;
        if(runnian(i)){
        	sum++;
		}
    }
    for(int i=1;i<m;i++){
    	sum+=a[i];
	} 
    if(runnian(y)&&m>2){
    	sum+=1;
	}   
    sum+=d;
    return sum;
}
int main(){
    scanf("%d:%d:%d",&y,&m,&d);//输入的时候主要要用scanf，每个%d之间都要加: 
    int ans1=f();
    scanf("%d:%d:%d",&y,&m,&d);
    //cin>>y>>m>>d;
    int ans2=f();
    cout<<abs(ans1-ans2);//有可能ans1<ans2，所以需要abs() 
}
```


---

## 作者：良初_ (赞：0)

第一次发题解，本蒟蒻的拙见。


[P1424 小鱼的航程(改进版)](https://www.luogu.org/problemnew/show/P1424)
这个比较简单，思路应该是相同的，中间换年月麻烦而已


代码如下：

	#include<bits/stdc++.h>
	using namespace std;
	int main()
    {	
    int n1,n2,y1,y2,r1,r2,d=0;
	char a;//干掉冒号，强行读入；
	cin>>n1>>a>>y1>>a>>r1;
	cin>>n2>>a>>y2>>a>>r2;
	// 输入；
	if(n1>n2||(n2==n1&&y2<y1)||(n2==n1&&y2==y1&&r1>r2))
	{
    swap(n1,n2);
    swap(y1,y2);
    swap(r1,r2);
	}//这个地方发现没有说明两个日期的大小，交换一下；
	while(n1!=n2||y1!=y2||r1!=r2)//循环d++数天数；
	{
		r1++;
		if(n1%4==0&&n1%100!=0||n1%400==0)//闰年情况
		{
   		 if((y1==1||y1==3||y1==5||y1==7||y1==8||y1==10||y1==12)&&r1==32)//r1等于32，则为下月一号，处理
    		{
            r1=1;
            y1++;
        	if(y1==13)  //月数等于13就是下一年一月，年加1，月等于1    
       	 	{
            		y1=1;                     
            		n1++;
        		}       
    	    }
   		 if((y1==4||y1==6||y1==9||y1==11)&&r1==31)//r1等于31，下月一号，处理
    		{
            	r1=1;
            	y1++；
   		 }
    		if(y1==2&&r1==30)//二月，r1等于30，下月一号，处理
    		{
            	r1=1;
            	y1++;
  		  }
	}
	else//平年情况，同样处理
	{
       	 if((y1==1||y1==3||y1==5||y1==7||y1==8||y1==10||y1==12)&&r1==32)
   		 {
         	   r1=1;
          	  y1++;
          	  if(y1==13)  //同样处理。 
       	 	{
         	  	 y1=1;                     
        	   	 n1++;
       		 }
     		}

   		 if((y1==4||y1==6||y1==9||y1==11)&&r1==31)
   	 	{
           	 r1=1;
           	 y1++;
 	  	 }
    		if(y1==2&&r1==29)
  	  	{
            	r1=1;
           	 y1++;
   	 	}   
	}   
   		 d++;
	}
		cout<<d<<endl;
		return 0;
	}



---

