# すべては1になる

## 题目描述

[problemUrl]: https://atcoder.jp/contests/fuka5/tasks/fuka_insider



# 题解

## 作者：chl090410 (赞：5)

## The Solution to AT_fuka_insider すべては1になる

### Description

给出现在的时间，以及以二进制表示的经过的秒数，计算经过这么多秒后的准确时间。

### Solution

本题就是一个大模拟。

我们可以先输入年，若其为 $0$，则退出循环。否则输入其余部分。

tips：输入可以使用 ```		scanf("/%lld/%lld%lld:%lld:%lld",&b,&c,&d,&e,&f)```，这样就不用处理字符串了，而是可以直接将数字存储在变量中。

接下来就是把代表经过的秒数的二进制数转为十进制，因为最多只有 $30$ 位，所以十进制数最大也就 $2^{30}-1$，不需要高精度。

这部分代码想必不用我过多说明了吧。

```
int qsort(int a,int b){
	int ans=1;
	while(b>0){
		if(b%2==1){
			ans=ans*a;
		}
		a=a*a;
		b/=2;
	}
	return ans;
}
int zyass(int x,int b){
	return qsort(2,b)*x;
}
int fqmm(string s){
	int l=s.size(),ans=0;
	for(int i=0;i<l;i++){
		ans+=zyass(s[l-i-1]-'0',i);
	}
	return ans;
}

```
然后，我们来处理时、分、秒。

我们将经过的秒数加在秒上，再用秒对 $60$ 做带余除法，余数为之后的秒，商加在分上，再对时、分做同样处理（时对 $24$ 做带余除法，商加在日上。）

这部分代码如下：

```
int p=fqmm(s);
f+=p%60;
p/=60;
if(f>=60){
	f-=60;
	e++;
}
e+=p%60;
if(e>=60){
	e-=60;
	d++;
}
p/=60;
d+=p%24;
p/=24;
if(d>=24){
	d-=24;
	c++;
}
c+=p;

```
接下来就是对年、月、日的处理了，我们把每月日数存在一个数组中，然后使用循环从日中依次减掉每月日数，再加上一月，直到日数不足时即可。注意闰年 $2$ 月有 $29$ 日、月数大于 $12$ 时要对 $12$ 取模，再加上一年。

这部分代码如下：

```
while(c>k[b]){
  if(a%4!=0||(a%100==0&&a%400!=0)){
      c-=k[b];
      b++;
  }else{
      if(b==2){
          if(c==29){
              break;
          }else{
              c-=29;
              b++;
          }
      }else{
          c-=k[b];
          b++;
      }
  }
  if(b>12){
      a++;b%=12;
  }
}

```
最后就是输出了，注意月、日、时、分、秒若小于 $10$ 需用 $0$ 填充十位即可。

### 完整代码如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int a,b,c,d,e,f,k[55]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int qsort(int a,int b){
	int ans=1;
	while(b>0){
		if(b%2==1){
			ans=ans*a;
		}
		a=a*a;
		b/=2;
	}
	return ans;
}
int zyass(int x,int b){
	return qsort(2,b)*x;
}
int fqmm(string s){
	int l=s.size(),ans=0;
	for(int i=0;i<l;i++){
		ans+=zyass(s[l-i-1]-'0',i);
	}
	return ans;
}
signed main(){
	while(1){
		cin>>a;
		if(a==0) break;
		scanf("/%lld/%lld %lld:%lld:%lld",&b,&c,&d,&e,&f);
		cin>>s;
		int p=fqmm(s);
		f+=p%60;
		p/=60;
		if(f>=60){
			f-=60;
			e++;
		}
		e+=p%60;
		if(e>=60){
			e-=60;
			d++;
		}
		p/=60;
		d+=p%24;
		p/=24;
		if(d>=24){
			d-=24;
			c++;
		}
		c+=p;
		while(c>k[b]){
			if(a%4!=0||(a%100==0&&a%400!=0)){
				c-=k[b];
				b++;
			}else{
				if(b==2){
					if(c==29){
						break;
					}else{
						c-=29;
						b++;
					}
				}else{
					c-=k[b];
					b++;
				}
			}
			if(b>12){
				a++;b%=12;
			}
		}
		cout<<a<<'/';
		if(b<10){
			cout<<0<<b<<'/';
		}else{
			cout<<b<<'/';
		}
		if(c<10){
			cout<<0<<c<<' ';
		}else{
			cout<<c<<' ';
		}
		if(d<10){
			cout<<0<<d<<':';
		}else{
			cout<<d<<':';
		}
		if(e<10){
			cout<<0<<e<<':';
		}else{
			cout<<e<<':';
		}
		if(f<10){
			cout<<0<<f<<endl;
		}else{
			cout<<f<<endl;
		}
	}
	return 0;
}

---

## 作者：A_grasser (赞：3)

## 题意简化

求过了若干秒后的时间。

## 需要注意的地方

1. 时、分、秒、年、月、日处理

1. 输出前导零要加

## 解法分析

先把二进制化成正常十进制会好做很多，亲测过转成的十进制不会太大。

想必这部分代码不用过多解释吧：

```cpp
int to_ten(string x/*传入二进制*/){
	int sum=0,j=0;
	for(int i=x.size()-1;i>=0;i--){
		sum=sum+(x[i]-'0')*pow(2,j);//加和
		j++;
	}
	return sum;
}
```

之后要把这段秒数加上去，加上去后，对时、分、秒整除取模就能搞定。

```cpp
ps=to_ten(t);//加上秒数 
s+=ps;
if(s>=60) mm+=s/60,s%=60;
if(mm>=60) h+=mm/60,mm%=60;
if(h>=24) day=h/24,h%=24;
```
最后就是化掉剩余加上的天数了，这个就只要一天天加就可以了，注意二月份的判别。

```cpp
while(day!=0){
	day--;
	d++;
	if(full(d)){//日进月 
		m++;
		d=1;
	}
	if(m==13){//月进年 
		y++;
		m=1;
	}
}
```
其中日进月判断这么写：

```cpp
bool full(int d){
	if(d>31/*肯定进*/ || ((m==4 || m==6 || m==9 || m==11) && d>30/*小月30日满了*/) || (m==2 && d>29/*二月29日满了，肯定进*/) || (m==2 && d>28 && (y%4 || (y%100==0 && y%400))/*非闰年二月28日满了*/)) return 1;
	else return 0;
}
```

最后搞定一下输入输出，就做完了。


最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int y,m,d,h,mm,s;
string t;
int ps; 
int to_ten(string x/*传入二进制*/){
	int sum=0,j=0;
	for(int i=x.size()-1;i>=0;i--){
		sum=sum+(x[i]-'0')*pow(2,j);//加和
		j++;
	}
	return sum;
}
bool full(int d){
	if(d>31/*肯定进*/ || ((m==4 || m==6 || m==9 || m==11) && d>30/*小月30日满了*/) || (m==2 && d>29/*二月29日满了，肯定进*/) || (m==2 && d>28 && (y%4 || (y%100==0 && y%400))/*非闰年二月28日满了*/)) return 1;
	else return 0;
}
void out(int x,string last){//输出补前导零加后缀 
	if(x<10) printf("0%d",x);
	else printf("%d",x);
	cout<<last;
}
int main(){
	while(1){
		int day=0;
		scanf("%d",&y);
		if(y==0) return 0;//结束 
		scanf("/%d/%d %d:%d:%d",&m,&d,&h,&mm,&s);
		cin>>t;
		ps=to_ten(t);//加上秒数 
		s+=ps;
		if(s>=60) mm+=s/60,s%=60;
		if(mm>=60) h+=mm/60,mm%=60;
		if(h>=24) day=h/24,h%=24;
		while(day!=0){
			day--;
			d++;
			if(full(d)){//日进月 
				m++;
				d=1;
			}
			if(m==13){//月进年 
				y++;
				m=1;
			}
		}
		//输出 
		cout<<y<<"/";
		out(m,"/");
		out(d," ");
		out(h,":");
		out(mm,":");
		out(s,"\n");
	}
	return 0;
}

```

---

## 作者：CrTsIr400 (赞：2)

# 0.前言

~~表示不用像楼下那么麻烦。~~

这道AT的题目虽然简单，但是坑细节，~~尤其是**读入**（~~

时间的处理略微难，但是**稍微想想、改改，还是能做出来的**。

# 1.关于时、分、秒的处理

我们可以把这道题简化成**这样**的一个问题：

给你起始时间（以 $hh:mm:ss$ 的形式来输入），**增加** $k(k\leq 60)$ 秒，求出终止时间（特别的，小时数 $h$ 超出了 $23$ 就会变成 $0$）。

自然想到，给秒数 $s$ 加上 $k$ 。但是 $s$ 有可能**大于等于** $60$ ，所以我们给分钟数 $m$ 加上 $1$ ，$s$ 给它减去 $60$ 。

但是，因为有可能分钟也要**进位**，所以在小时那里再给它**处理一下**。

可惜这只是部分情况下。

比如说我 $m$ 不会只进一位，我进**两位及以上**怎么办？

可以使用`while`循环加位。似乎时间复杂度也不大。

~~不乖的~~小蒟蒻问：我一次性加他个 $10^9$ 秒试试 ？ ~~祝你TLE快乐（滑稽~~

`while`循环加的效率是极低的，常数是**大致 $\frac{n}{30}$ ，$O(n)$ 的复杂度**，多套几个，就可能会超时。怎么 $O(1)$ 找出这个要加的值呢？

~~emm，问题开始深♂入了~~

对了，就是使用**除法。** 

`m=s/60;s%=60;`

其他的东西以此类推。

# 2.关于年、月、日的细节

我们初学`if语句`时都打过这样一个判断：

```cpp
if(month==2&&year%4==0&&((year%100==0&&year%400==0)||(year%100!=0)))
cout<<"yes";
else 
cout<<"no";
```

这个判断大家都会吧。

>判断这个月是否是二月：

>>如果 是

>>判断这一年除以 $4$ 的余数是不是 $0$ 

>>>如果 是

>>>判断这一年是否能够被 $100$ 整除

>>>> 如果 是

>>>> 判断这一年是否能够被 $400$ 整除

>>>>> 输出：是闰年

>>>> 否则 输出 不是

>>>否则 输出 是

>>否则 输出 不是

>否则 输出 不是

~~有scratch的内味了（（（~~

大体意思是这样，再配合百度使用更佳。

编写一个函数计算这个月的天数，然后让未处理的 $d$ （天数）一直减去 这个天数，直到小于为止。

代码放上来了。

# 3.参考代码：

```cpp
s+=sec;//sec是处理出来要增加的秒数；
m+=s/60;s%=60;
h+=m/60;m%=60;
D+=h/24;h%=24;//1提到的东西；
while(D>dayM(M,Y))
{
	D-=dayM(M,Y);//2提到的时间处理；
	++M;
	if(M>12)M=1,++Y;//注意
}
printf("%04d/%02d/%02d %02d:%02d:%02d\n",Y,M,D,h,m,s);
```


---

## 作者：Berd__ (赞：1)

### 题目大意
输入现在的时间，以及以二进制表示的经过的秒数，计算经过这么多秒后的准确时间。

注意到这是一道模拟题，但是我们要把二进制转换为十进制。因为长度较短，所以考虑暴力从高位到低位枚举并加和：
```
int time=0;
string st;
cin>>st;
for(int i=0;i<st.length();i++){
    time+=st[i]==0?0:pow(1,st.length()-i-1);
}
```
接下来就简单了，首先对秒做带余除法，商加在分上，对分做带余除法，商加在时上，以此类推，月份的天数存在数组里然后一次次减。（长难句警告）
```
m+=(s+time)/60;
s=(s+time)%60;
h+=m/60;
m%=60;
day+=h/24;
h%=24;
while(day-mon[month]+((year%4==0&&(year%100!=0||year%400==0)&&month==2)?1:0)>0){
  day-=mon[month]+((year%4==0&&(year%100!=0||year%400==0)&&month==2)?1:0);
  month++;
  if(month>12){
    year++;
    month=1;
  }
 }
```
## AC Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
signed main(){
    int year,month,day,h,m,s;
    cin>>year;
    while(year!=0){
        scanf("/%lld/%lld %lld:%lld:%lld",&month,&day,&h,&m,&s);
        int time=0;
        string st;
        cin>>st;
        for(int i=0;i<st.length();i++){
            time+=st[i]==0?0:pow(2,st.length()-i-1);
        }
        m+=(s+time)/60;
        s=(s+time)%60;
        h+=m/60;
        m%=60;
        day+=h/24;
        h%=24;
        //printf("%lld/%s%lld/%s%lld %s%lld:%s%lld:%s%lld\n",year,month>=10?"":"0",month,day>=10?"":"0",day,h>=10?"":"0",h,m>=10?"":"0",m,s>=10?"":"0",s);
        while(day-mon[month]+((year%4==0&&(year%100!=0||year%400==0)&&month==2)?1:0)>0){
            
            day-=mon[month]+((year%4==0&&(year%100!=0||year%400==0)&&month==2)?1:0);
            month++;
            //printf("%lld/%s%lld/%s%lld %s%lld:%s%lld:%s%lld\n",year,month>=10?"":"0",month,day>=10?"":"0",day,h>=10?"":"0",h,m>=10?"":"0",m,s>=10?"":"0",s);

            if(month>12){
                year++;
                month=1;
            }
        }
        printf("%lld/%s%lld/%s%lld %s%lld:%s%lld:%s%lld\n",year,month>=10?"":"0",month,day>=10?"":"0",day,h>=10?"":"0",h,m>=10?"":"0",m,s>=10?"":"0",s);
        cin>>year;
    }   
}
```

---

## 作者：simple_child (赞：1)

简单模拟题~  
**题意简化**：求过了若干秒后的时间。  

---
首先肯定想到进制转化，由于我们~~是十进制人~~平时使用的是十进制，所以这里我们把二进制转化成十进制。

```cpp
int Decimal_System(string Binary_number)
	{
	int sum=0,j=0;
	for(int i=Binary_number.length()-1;i>=0;i--)
	{
		sum=sum+(Binary_number[i]-'0')*pow(2,j);
		j++;
	}
	return sum;
}
```
接着把时间相加不细阐述。  
然后，我们用地球人的思维就可以判断出要处理进位，只需要对时、分、秒的进率取模；每一位添加进位数即可。

```cpp
if(s>=60) min+=s/60,s%=60;
if(min>=60) h+=min/60,min%=60;
if(h>=24) day=h/24,h%=24;
```
最后就是化掉剩余加上的天数判别月份了，注意二月份的判别，在此对此步骤不在多多解释:  
**对于闰年的判别**（也就可以抽象成二月的判别）：https://www.luogu.com.cn/record/95888959  
其它日进月判断只要一天天加就好了，作为人人皆知的大善人，在此给出月份天数表：

```cpp
int day[12+3]={31,NaN/*二月自己算*/,31,30,31,30,31,31,30,31,30,31};
```

---

## 作者：__Segment__ (赞：1)

看到这道题的第一眼，二进制？

二进制转十进制代码。
```cpp
int _zh(int n) {
	int num[10];
    int i = 0, m= 0;
    while(n) {
        num[i] = n % 10;
        i++;
        n = n / 10;
    }
    i--;
    while(i >= 0){
        if(num[i] == 1){
        m +=pow(2.0, i);
        }
        i--;
    }
	return m;
}
```

接着只要判断就可以了。
```cpp
int s, f, m, r;
f += m / 60;
m = m % 60;
s += f / 60;
f %= 60;
r += s / 24;
s %= 24;
```


记得用
```cpp
#include<cmath>
```

---

## 作者：zyc230721hzx (赞：0)

蒟蒻的第二篇题解。

做本题前，建议先练习 [B4000 [GESP202406 一级] 休息时间](https://www.luogu.com.cn/problem/B4000) 和 [P5716 【深基3.例9】月份天数](https://www.luogu.com.cn/problem/P5716)。

[题目传送门](https://www.luogu.com.cn/problem/AT_fuka_insider)

### 题意：
输入现在的时间，以及以二进制表示的经过的秒数，计算经过这么多秒后的准确时间。



### 考点：

模拟。

### 思路：
**第一步** 读入数据（建议采用格式化输入）：

```cpp
	while(true){
		scanf("%lld",&year);
    	if(!year&1)break;					//检测到0时退出循环
		scanf("/%lld/%lld %lld:%lld:%lld\n",&month,&day,&hh,&mm,&ss);
        getline(cin,ttime);
｝
```

**第二步** 将输入的秒数转化为十进制：

```cpp
inline long long mi_2(long long i){
	return (long long)1<<i;
}
long long twototen(string two){
	long long ten=0,len=two.size();  
	reverse(two.begin(),two.end());
	for(long long i=0;i<len;i++){
		ten+=(two[i]-'0')*mi_2(i);
	}return ten;
}
```

**第三步** 加上秒数并处理**一月内**超出的秒数。


```cpp
mm+=ss/60;
ss%=60;
hh+=mm/60;
mm%=60;
day+=hh/24;
hh%=24;
```

**第四步** 处理超出的天数。


```cpp
long long daily[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
inline long long ts(long long year,long long month){
	return (month==2&&(year%4==0&&year%100!=0||year%400==0))?29:daily[month];
}
```

```cpp
long long hu=ts(year,month);
	while(day>hu){
	month++;
	day-=hu;
	if(month>12){
		month-=12;
		year++;
	}
	hu=ts(year,month);
｝
```
**第五步** 输出（建议采用格式化输出）。


```cpp
printf("%lld/%02lld/%02lld %02lld:%02lld:%02lld\n",year,month,day,hh,mm,ss);
```

其中，`%02lld` 可以将输出的数字转化为两位数（即补上前导0）。

### 完整 AC 代码（C++ 版）：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long year,month,day,hh,mm,ss;
string ttime;
long long daily[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
inline long long mi_2(long long i){
	return (long long)1<<i;
}
long long twototen(string two){
	long long ten=0,len=two.size();  
	reverse(two.begin(),two.end());
	for(long long i=0;i<len;i++){
		ten+=(two[i]-'0')*mi_2(i);
	}return ten;
}
inline long long ts(long long year,long long month){
	return (month==2&&(year%4==0&&year%100!=0||year%400==0))?29:daily[month];
}
int main(){
	while(true){
		scanf("%lld",&year);
		if(!year&1)break;
		scanf("/%lld/%lld %lld:%lld:%lld\n",&month,&day,&hh,&mm,&ss);getline(cin,ttime);
		ss+=twototen(ttime);
		mm+=ss/60;
		ss%=60;
		hh+=mm/60;
		mm%=60;
		day+=hh/24;
		hh%=24;
		long long hu=ts(year,month);
		while(day>hu){
			month++;
			day-=hu;
			if(month>12){
				month-=12;
				year++;
			}
			hu=ts(year,month);
		}printf("%lld/%02lld/%02lld %02lld:%02lld:%02lld\n",year,month,day,hh,mm,ss);
	} 
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/179195940)

**预祝 AC!**

---

## 作者：wangziwenhk (赞：0)

求过。
- [题目传送门](https://www.luogu.com.cn/problem/AT_fuka_insider)
- [博客地址](https://www.luogu.com.cn/article/b7486ola)

## 大致题意
给你一个开始时间，格式为：
```
year/month/day hh:mm:ss
time
```
以及一个二进制的经过秒数，要求你求出**最后的时间**。
## 获取时间
这是一道字符串模拟题，也是**匹配问题**和**时间问题**。

对于如何获取字符串中的年月日关系，我们可以使用 `sscanf` 函数。用法如下：
```c++
sscanf(source,format,...);
```
这个函数和 `scanf` 很像，唯一不同的就是 `scanf` 是从标准输入流 `stdin` 来匹配数据的，而 `sscanf` 是从一个 char 数组中匹配数据的。

因此，我们可以**很方便**的得到一行中的时间数据：
```c++
string startTime;
getline(cin, startTime); 
if (startTime == "0")break;
string time;
getline(cin, time);
//不开 long long 见祖宗
long long addTime = stoi(time, nullptr, 2);

long long year, month, day, hh, mm, ss;
sscanf(startTime.c_str(), "%lld/%lld/%lld %lld:%lld:%lld", &year, &month, &day, &hh, &mm, &ss);//匹配字符串中的年月日
```
细心的朋友可能注意到了，在**转换二进制**的过程中我使用了一个 `stoi(str,idx,base)` 函数，这个函数可以更方便的转换 $2\sim 16$ 以内的进制，可以~~偷懒~~让代码更简洁。

## 更新时间
现在我们就可以到更新时间这一步了。时分秒只需要类似高精度加法一样进位就可以了，真正困难的是关于天数的处理。

我们设置一个 while 循环，当天数大于 $28$ 时就**有可能**超出一个月的**最大天数**限制，所以我们将条件设为 `day>28`。

然后我们要获取每一个月的具体天数，用一个数组存下一月到十二月的天数，当获取二月的具体天数时还要判断一次是否是闰月。如果当前的 day **小于**这个月的天数，则不需要更新了，直接跳出循环。否则，就让 `month++` 并让 `day-=max_day`，当 `month>12` 时还要**更新年份**。
```c++
while (day > 28) {
  int max_day = f[month];
  if(month==2 && check(year))max_day++;
  if(day<=max_day)break;
  month++;
  day-=max_day;
  if(month>12)year++,month=1;
}	
```

## 代码附上
到这里为止，代码就全部写完了，以下附上全部代码。
```c++
#include <bits/stdc++.h>

using namespace std;
int f[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
bool check(int x){
    if(x%4==0 && x%100!=0)return true;
    else if(x%400==0)return true;
    return false;
}
int main() {
    while (1) {
        string startTime;
        getline(cin, startTime);
        if (startTime == "0")break;
        string time;
        getline(cin, time);

        long long addTime = stoi(time, nullptr, 2);

        long long year, month, day, hh, mm, ss;
        sscanf(startTime.c_str(), "%lld/%lld/%lld %lld:%lld:%lld", &year, &month, &day, &hh, &mm, &ss);

        ss += addTime;
        if (ss >= 60)mm += ss / 60, ss %= 60;
        if (mm >= 60)hh += mm / 60, mm %= 60;
        if (hh >= 24)day += hh / 24, hh %= 24;
        while (day > 28) {
            int max_day = f[month];
            if(month==2 && check(year))max_day++;
            if(day<=max_day)break;
            month++;
            day-=max_day;
            if(month>12)year++,month=1;
        }

        printf("%lld/",year);
        if(month<10)printf("0");
        printf("%lld/",month);
        if(day<10)printf("0");
        printf("%lld ",day);
        if(hh<10)printf("0");
        printf("%lld:",hh);
        if(mm<10)printf("0");
        printf("%lld:",mm);
        if(ss<10)printf("0");
        printf("%lld\n",ss);
    }
    return 0;
}

```

---

## 作者：Brute_Force (赞：0)

### 题意
给出现在的时间，求经过一个二进制时间后，又是几年几天几时几分几秒。
### 注意事项
本题再新增一个注意事项，不同于其他题，当输入最后一行为 $000$ 时，终止程序。
### 代码
伪代码的实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a;
    string b;
    do
    {
        cin>>b;
        if(b=="000") return 0;//预处理
        cin>>a;
        将a转化为二进制;
        处理b;
        计算b经过a后的时间;//这样做是因为b是字符串
        cout<<b;
    }
    while(a==000)
}
```

---

## 作者：Gaoyx (赞：0)

一个大模拟。
## 思路
二进制转十进制，很基础的一个写法。
```
void zhuan(string s)
{//s为二进制下的字符串
	int tot = 0;
	for(int i=s.size()-1;i>=0;i--)
	{
		tim += (s[i] - '0') * pow(2,tot);
		tot++;
	}
}
```
闰年判断，可以被四百整除，或可以被四除尽且不能被一百除尽（代码中的判断写在题内了）。
```
if((a%4==0&&a%100!=0)||a%400==0)
{//a为年份	
	cout << "1"; 
}else
{
	cout << "0";
}

```


总体思路：将二进制转换成十进制按时间依次累加，累计时判断是否是闰年，建议看代码理解。


## 代码
```
#include<bits/stdc++.h>
using namespace std;
long long tim = 0;
void zhuan(string s)
{
	int tot = 0;
	for(int i=s.size()-1;i>=0;i--)
	{
		tim += (s[i] - '0') * pow(2,tot);
		tot++;
	}
}
int main()
{
	while(1)
	{
		int nian, yue, day, hh, ff, mm;
		char b;
		string a; 
		cin >> nian;
		if(nian == 0) break;
		cin >> b >> yue >> b >> day;
		cin >> hh >> b >> ff >> b >> mm;
		cin >> a;
		zhuan(a);
		mm += tim;
		ff += (mm / 60), mm %= 60;
		hh += (ff / 60), ff %= 60;
		day += (hh / 24), hh %= 24;
		int d = 0;
		while(day!=0)//特殊判断年月日
		{
			
			
			day--;
			d++;
			if(d>31 || ((yue==4 || yue==6 || yue==9 || yue==11) && d>30) || (yue==2 && d>29) || (yue==2 && d>28 && (nian%4 || (nian%100==0 && nian%400)))) yue++, d=1;
			if(yue == 13) nian++, yue = 1;
		}
		cout << nian << "/";
		if(yue < 10) cout << "0" << yue << "/";
		else cout << yue << "/";
		if(d < 10) cout << "0" << d << " ";
		else cout << d << " ";
		if(hh < 10) cout << "0" << hh << ":";
		else cout << hh << ":";
		if(ff < 10) cout << "0" << ff << ":";
		else cout << ff << ":";
		if(mm < 10) cout << "0" << mm << "\n";
		else cout << mm << "\n";
		tim = 0;
	}
	return 0;
}

```


---

## 作者：neil021110 (赞：0)

```cpp
#include<cstdio>
using namespace std;
int main(){
	int y,m,d,h,min,s;
	char tim[31];
	int time;
	while(1){
		
	time=0;//秒钟数设为0
	scanf("%d",&y);//输入年份并检查是否为0
	if(y==0)break;//若是0，则结束
	scanf("/%d/%d %d:%d:%d",&m,&d,&h,&min,&s);//输入其余部分
	scanf("%s",&tim);//输入二进制数
	for(int i=0;i<30;i++){
		if(tim[i]==0)break;//以“\0”结束
		time*=2;//检测到“0”则秒钟数乘2
		if(tim[i]=='1')time++;检测到“1”则秒钟数乘2并加1
	} 
	int day=time/86400;//计算天数
	time=time%86400;//计算时分秒
	s+=time%60;//计算秒
	if(s>=60){//进位
		min++;
		s-=60;
	}
	min+=(time/60)%60;//计算分
	if(min>=60){//进位
		h++;
		min-=60;
	}
	h+=(time/3600)%24;//计算小时
	if(h>=24){//进位
		day++;
		h-=24;
	}
	while(day){
		day--;
		d++;
		if(d>31||((m==4||m==6||m==9||m==11)&&d>30)||(m==2&&d>29)||(m==2&&d>28&&(y%4||(y%100==0&&y%400)))){
			m++;//月份进位
			d=1;
		}
		if(m==13){
			y++;//年份进位
			m=1;
		}
	
	}printf("%04d/%02d/%02d %02d:%02d:%02d\n",y,m,d,h,min,s);//输出
	}
	
}
```


---

