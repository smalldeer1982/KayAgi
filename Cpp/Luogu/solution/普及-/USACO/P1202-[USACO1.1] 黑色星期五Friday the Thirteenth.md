# [USACO1.1] 黑色星期五Friday the Thirteenth

## 题目描述

$13$ 号又是一个星期五，那么 $13$号在星期五比在其他日子少吗？  

为了回答这个问题，写一个程序，要求计算每个月的十三号落在周一到周日的次数。给出 $n$ 年的一个周期，要求计算 $1900$ 年 $1$ 月 $1$ 日至 $1900+n-1$ 年 $12$ 月 $31$ 日中十三号落在周一到周日的次数。

这里有一些你要知道的:

1. $1900$ 年 $1$ 月 $1$ 日是星期一。
2. $4,6,11$ 和 $9$ 月有 $30$ 天，其他月份除了 $2$ 月都有 $31$ 天，闰年 $2$ 月有 $29$ 天，平年 $2$ 月有 $28$ 天。
3. 年份可以被 $4$ 整除的为闰年（$1992=4\times 498$ 所以 $1992$ 年是闰年，但是 $1990$ 年不是闰年）。
4. 以上规则不适合于世纪年。可以被 $400$ 整除的世纪年为闰年，否则为平年。所以，$1700,1800,1900,2100$ 年是平年，而 $2000$ 年是闰年。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 400$。

题目翻译来自NOCOW。

USACO Training Section 1.1


## 样例 #1

### 输入

```
20
```

### 输出

```
36 33 34 33 35 35 34
```

# 题解

## 作者：封禁用户 (赞：670)

```cpp
真~模拟

很耿直的想法

写一个函数判断是否闰年

主方法里开一个n次的for循环，然后再开24个for循环，每12个分别对应平（闰）年的每一个月

巨长：600+行（比我用Java模拟BigInteger类还长）

#include<cstdio>

using namespace std;

bool isLeapYear(int year){
    if(year == 1900 || year == 2000 || year == 2100 || year == 2200 || year == 2300 || year == 2400 || year == 2500){
        if(year % 400 == 0){
            return true;
        }
    }else if(year % 4 == 0){
        return true;
    }
    
    return false;
}

int main(){
    int n;
    scanf("%d",&n);
    
    int ans[7] = {};
    
    int day = 1;
    for(int i = 1900;i < 1900 + n;i++){
        if(isLeapYear(i) == false){
            for(int j = 0;j < 31;j++){//平年1月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
            
            for(int j = 0;j < 28;j++){//平年2月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//平年3月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 30;j++){//平年4月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//平年5月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 30;j++){//平年6月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//平年7月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//平年8月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 30;j++){//平年9月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//平年10月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 30;j++){//平年11月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//平年12月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        }else{
            for(int j = 0;j < 31;j++){//闰年1月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
            
            for(int j = 0;j < 29;j++){//闰年2月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//闰年3月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 30;j++){//闰年4月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//闰年5月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 30;j++){//闰年6月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//闰年7月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//闰年8月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 30;j++){//闰年9月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//闰年10月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 30;j++){//闰年11月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        
            for(int j = 0;j < 31;j++){//闰年12月 
                if(j == 13){
                    if(day == 1){
                        ans[day - 1]++;
                    }else if(day == 2){
                        ans[day - 1]++;
                    }else if(day == 3){
                        ans[day - 1]++;
                    }else if(day == 4){
                        ans[day - 1]++;
                    }else if(day == 5){
                        ans[day - 1]++;
                    }else if(day == 6){
                        ans[day - 1]++;
                    }else if(day == 7){
                        ans[day - 1]++;
                    }
                }
                
                day++;
            
                if(day > 7){
                    day = 1;
                }
            }
        }
    }

    printf("%d ",ans[6]);
    printf("%d ",ans[0]);
    printf("%d ",ans[1]);
    printf("%d ",ans[2]);
    printf("%d ",ans[3]);
    printf("%d ",ans[4]);
    printf("%d ",ans[5]);
    
    return 0;
}
```

---

## 作者：早右昕 (赞：173)

###坑
其实。样例的部分是从周六~周五输出的，习惯不同吧。。这里考虑到从这个月的13号到下一个月的13号所花天数为这个月的天数，然后愉快的判断一下闰年即可。这里的周一~周日编号为0~6，一月到十二月的编号为0~11（方便计算）。。而且1900/1/13是周六

代码：~~知道我写得垃圾~~

```cpp
#include<cstdio>
struct date {int yy,mm,ww;};
bool operator<(const date &a,const date &b) { 
    if(a.yy!=b.yy) return a.yy<b.yy;//日期比较 
    if(a.mm!=b.mm) return a.mm<b.mm;
    return 0;
}
int d[2][13]= {31,28,31,30,31,30,31,31,30,31,30,31,0,31,29,31,30,31,30,31,31,30,31,30,31,0};
void operator++(date &a) {
    bool spl=0;//是否闰年 
    if(!(a.yy%400)) spl=1;
    if((a.yy%100)&&!(a.yy%4)) spl=1;
    a.ww+=d[spl][a.mm++],a.ww%=7;
    if(a.mm==12) a.yy++,a.mm=0;
}
int main() {
    int n,t[7]={0};
    scanf("%d",&n);
    date a=(date) {1900,0,5};//起始时间 
    date b=(date) {1900+n-1,11,-1};//终止时间 
    while(!(b<a)) t[a.ww]++,++a;//过程 
    for(int i=5; i<12; i++) printf("%d ",t[i%7]);//输出 
    return 0;
}
```

---

## 作者：HEIGE (赞：80)

# 基姆拉尔森计算公式秒解法
不知道为什么大家都写了这么暴力的代码，这里提供一个更容易的基于数学的方法。
## 题意分析
题目要求我们计算从$1900$年$1$月$1$日至$1990+n-1$年$12$月$31$日中$13$号落在周一到周日的次数。非常简单而又朴素的想法是枚举各年各月的$13$号，并通过一个函数$week\_day(year, month, day)$将该日期转换成星期，并用一个数组$count[7]$进行储存。

## 关键日期转星期函数的编写

有关于[Kim larsen calculation formula](https://baike.baidu.com/item/%E5%9F%BA%E5%A7%86%E6%8B%89%E5%B0%94%E6%A3%AE%E8%AE%A1%E7%AE%97%E5%85%AC%E5%BC%8F/713396)的百度百科。该公式可以直接通过年月日求出当天星期。还有一个相似的[Zeller's formular](https://baike.baidu.com/item/%E8%94%A1%E5%8B%92%E5%85%AC%E5%BC%8F)，均为秒杀日期模拟题的利器。

### 基姆拉尔森计算公式：

$week = (day + 2 \times month + [3 \times (month + 1) \div 5] + year + [year \div 4] - [year \div 100] + [year \div 400] + 1) \bmod 7$

其中$[num]$表示取整，实际中直接用int除就完事了QwQ。需要注意的是，该公式将每年的$1$月与$2$月份作为前一年的$13$与$14$月份进行计算，所以需要在代码中进行一个小小的特判即可完成。若详细的证明可以自己尝试一下，或者随手一搜也有一大堆/以后也有可能开另一篇文章讲一下/？
```cpp
int week_day(int year, int month, int day)	//the function which converts date to week *will return 0 for Sunday
{
    if (month == 1 || month == 2) month += 12, year--;	//process the special cases for Jan and Feb
    return (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 1) % 7;	//the Kim larsen calculation formula!
}
```
根据数学原理，以上就是该日期转星期函数在C++中的写法。

## AC代码

```cpp
#include <iostream>	//pure C++ writer!
using namespace std;	//just using it! 
int week_day(int year, int month, int day)	//the function which converts date to week *will return 0 for Sunday
{
    if (month == 1 || month == 2) month += 12, year--;	//process the special cases for Jan and Feb
    return (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 1) % 7;	//the Kim larsen calculation formula!
}
int main()
{
    int year_len = 0;
    cin >> year_len;
    int count[7] = {0};	//what else can I explain/.
    for (int current_year = 1900; current_year < 1900 + year_len; current_year++)
        for (int current_month = 1; current_month <= 12; current_month++)
            count[week_day(current_year, current_month, 13)]++;
    cout << count[6] << " "<<count[0]<< " "<<count[1]<< " "<<count[2]<< " "<<count[3]<< " "<<count[4]<< " "<<count[5];	//remember to pay attention to the cout format
    return 0;
}
```
## 写在最后
不过竞赛环境下也不能指望把这个如此丑陋的公式背下来（所以学习一些~~更加丑的~~暴力算法大概还有一点用/大雾/）。

---

## 作者：tllwtg (赞：49)

##这题貌似没有人用单个日期累加法，那就来一发


###我觉得这题难度是入门难度都太高估了（我已经不会判断难度了）


##不过这题有几个个要注意的点是输出要从星期六开始，这个在题目里好像没有写，好简（坑）单（人）。


#讲一下主要思路：


1.一天天累加


2.超出这个月天数后月加一，日归一


3.超出十二个月后，年加一，月归一


4.日每逢13，就累加


5.到指定年份后停止


具体看注释


上ac代码：


include<iostream>//头文件，不解释（好像这就已经解释了吧╮(￣▽￣)╭）


```cpp
using namespace std;
bool rn(int);//声明判断是否是闰年的函数
int main(){
    int n1;
    cin>>n1;//同题目的n
    int n=1900,y=1,r=1,xq=1;//初始化并声明年月日
    int yue[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};//记录每个月有几天
    int njs;//记录是否是闰年
    int wew[8]={0,0,0,0,0,0,0,0};//初始化周一到周天有多少个在13号
    while(1){//非0为true
        if(n==1900+n1&&y==1&&r==1){//如果到了指定日期就推出循环
            break;
        }
        if(rn(n)){//判断是否为闰年
            njs=1;
        }
        else{
            njs=0;
        }
        r+=1;//日加一
        xq+=1;//星期加一
        if(r>yue[njs][y]){//如果日大于这个月的天数，月加一，日归一
            r=1;
            y+=1;
        }
        if(y>12){//如果月大于12，年加一，月归一
            n+=1;
            y=1;
        }
        if(xq>7){//如果星期大于7,星期归一
            xq=1;
        }
        if(r==13){//如果日等于13，这个星期在13号的次数加一
            wew[xq]+=1;
        }
    }
    cout<<wew[6]<<" "<<wew[7]<<" "<<wew[1]<<" "<<wew[2]<<" "<<wew[3]<<" "<<wew[4]<<" "<<wew[5];//输出
    return 0;//完美无瑕疵结束
}
bool rn(int h){
    if(h%100==0){//判断是否是世纪年
        if(h%400==0){//如能被400整除，就是闰年
            return true;
        }
        else{//否则不是
            return false;
        }
    }
    else{
        if(h%4==0){//能被四整除，就是闰年
            return true;
        }
        else{//否则不是
            return false;
        }
    }
}
```

---

## 作者：KingOfWA (赞：40)

 ```pascal
//发布一篇pascal题解
//楼上的 dalao 都是强模拟，这里提交一种数学方法
//设i年第j-1月的13日为星期d，那么下一个月的13日是(d+getDay(i,j-1)) % 7。
//其中getDay就是获取i年第j月的日期
//特判两点：
//1: d=0 -> d=7
//2：j=1 -> 改为getDay(i-1,12)
var
  a:array[1..7] of longint;
  n,i,j,d:longint;
function getDay(year,month:longint):longint;
begin
  case month of 
    1,3,5,7,8,10,12:exit(31);
    4,6,9,11:exit(30);
    2:if (year mod 4=0)and(year mod 100<>0)or(year mod 400=0) then exit(29)
        else exit(28);
  end;
end; 
//判断天数 year:年 month:月
begin
  fillchar(a,sizeof(a),0);//初始化
  readln(n);
  d:=3; //1899年12月13日为星期3
  for i:=1900 to 1900+n-1 do
    for j:=1 to 12 do
      begin
        //先计算星期
        if j=1 then d:=(d+getDay(i-1,12)) mod 7  //特判2
          else d:=(d+getDay(i,j-1))mod 7;
        if d=0 then d:=7; //特判1
        //星期+1，类似C++的 a[d]++
        inc(a[d]);
      end;
  //懒得打for循环，索性这么输出算了
  writeln(a[6],' ',a[7],' ',a[1],' ',a[2],' ',a[3],' ',a[4],' ',a[5]);
end.
```

---

## 作者：Shan＿Xian (赞：34)

//详细分析：因为1900.1.1是星期一，所以1900.1.13就等于(13-1) mod7+1=星期六。

//这样讲可能不太清楚。那么，我来解释一下：每过7天是一个星期。

//n天后是星期几怎么算呢？现在假设n是7的倍数，如果n为14，那么刚好就过了两个星期，

//所以14天后仍然是星期一。但如果是过了15天，那么推算就得到是星期二。

 
 
 
 
 
 
```cpp
//这样，我们就可以推导出一个公式来计算。
//(n天 mod 7（一个星期的天数）+ 现在日期的代号) mod 7 就等于现在日期的代号。
//当括号内的值为7的倍数时，其代号就为0，那么，此时就应该是星期日,这样，
//我们可以得出题目的算法：
//int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31}
//int b[8]={0} 
//a数组保存一年12个月的天数（因为C语言中数组起始下标为0，所以这里定义为13）。
//b数组保存星期一到星期日出现的天数。
//用date记录目前是星期几的代号，然后用两个循环，依次加上所经过的月份的天数，
//就出那个月是星期几，当然，要注意判断闰年！知道了这个方法，实现起来就很容易了。
//二话不说，代码闪亮登场！
#include<fstream>//文件输入输出，专业防抄袭 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm> 
using namespace std;
int main()
{
    int year,month,i,n,last=3;   
    int dayOfMonth[12]={31,31,28,31,30,31,30,31,31,30,31,30};//初始化 
    int result[7]={0};          
    ifstream fin("friday.in");
    ofstream fout("friday.out");//文件输入输出 
    fin>>n;
    for(year=1900;year<1900+n;++year){
        if(year%400==0||(year%100!=0&&year%4==0)) dayOfMonth[2]=29;//闰年 
        for(month=0;month<12;++month){
            last=(last+dayOfMonth[month])%7;//每周 
            result[last]++;
        }
        dayOfMonth[2]=28;//普通的2月 
    }
    for(i=0;i<6;++i) fout<<result[(i+6)%7]<<' ';//输出 
    fout<<result[5]<<endl;
    fin.close();
    fout.close();
    return 0;
}
```

---

## 作者：Divinitist (赞：26)

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//定义命名空间
int m[13]={0,31,28,31,30,31,30,31,31,30,31,30,31},w[8];//m数组预处理每月天数，w数组存储答案
int main()//主函数
{
    int n,st=0;//n即题目中N，跨年数；st存储从1900年1月1日（计入）开始的总天数
    scanf("%d",&n);//scanf函数属于C++标准库函数，读入速度快于cin，可通过头文件cstdio调用
    for(int i=1900;i<1900+n;i++)//i循环年份
    {
        int f=0;//闰年标记
        if((i%4==0)&&(i%100)||(i%400==0)) f=1;//判断是否为闰年（四年一闰，百年不闰，四百年又闰），若成立则f赋值为真
        for(int j=1;j<=12;j++) //j循环月份
        {
            int e=0;//如果为闰年，2月就要多一天，e在闰年情况下使2月的循环变量增大1
            if(f&&j==2) e=1;
            for(int k=1;k<=m[j]+e;k++)//k循环日期，m[j]即j月的天数
            {
                st++;//st每天增加
                if(k==13) w[st%7]++;//每当天数为13时，满足题目条件，已经过总天数取余7即星期几，因为1900年1月1日是星期一。
            }
            if(e==1) e=0;//2月用过后要清零
        }
    }
    printf("%d %d %d %d %d %d %d",w[6],w[0],w[1],w[2],w[3],w[4],w[5]);//输出顺序是Sat Sun Mon Tue Wed Thu Fri
    return 0;
}
```

---

## 作者：yyy2015c01 (赞：14)

**我洛谷个人空间有我博客网址，最近可能要迁移，访问不了就是迁移了。**

敬请关注。

#[点击这个大大大大大大标题访问写这篇题解时的博客地址](http://iyyy.sinaapp.com/)

注意一个性质：**今天是星期几，7天后还是星期几。**

直接**暴力枚举**。`小心闰年的闰月。。。`

**。。。然后就可以打表了。**


---
#打表代码

```cpp
//打表多好~~~干嘛不让
//打表程序↓
#include<iostream>
#include<cstring>
using namespace std;
int day[8]= {0};
int mon[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
int main()
{
    //freopen("1.txt","w",stdout);
    cout<<"{"0"";
    int n,xq=1;
    for(n=1; n<=400; n++)
    {
        xq=1; 
        memset(day,0,sizeof(day));
        for(int i=1900; i<1900+n; i++)
        {
            if((i%4==0&&i%100!=0)||i%400==0) mon[1]=29;
            else mon[1]=28;
            for(int j=0; j<12; j++)
                for(int c=1; c<=mon[j]; c++)
                {
                    if(c==13) day[xq]++;
                    xq++;
                    if(xq>7) xq=1;
                }
        }
        cout<<","";
        cout<<day[6]<<" "<<day[7]<<" ";
        for(int i=1; i<=5; i++) cout<<day[i]<<" ";
        cout<<""";
    }
    cout<<"};";
    return 0;
}
```

---

## 作者：Eason_AC2 (赞：8)

真·模拟~~水~~题，注意细节。

------------

细节是什么？~~能吃吗？~~

首先最主要的还是处理闰年这个问题，我们先回去看题目，其中的第3、4个`你要知道的`就很好地讲明了处理闰年的规则：

>年份可以被$4$整除的为闰年($1992=4*498$ 所以 $1992$年是闰年,但是$1990$年不是闰年)。

>以上规则不适合于世纪年（即能被$100$整除的年份——作者注）。可以被400整除的世纪年为闰年,否则为平年。所以,$1700,1800,1900$和$2100$年是平年,而$2000$年是闰年。

所以我们可以想出这样一个判断闰年的过程：

$Step~1:$判断是否是世纪年。如果是的话，判断是否能被$400$整除，是则该年份是闰年，否则不是。

$Step~2:$否则，判断完该年份不是世纪年之后，只需要看其是否能被$4$整除，是则该年份是闰年，否则不是。

至此，如下的年份判断程序就很清晰明了了：

```cpp
bool check(int n) {
	if(n % 100 == 0) {
		if(n % 400 == 0)	return 1;
		return 0;
	}
	if(n % 4 == 0)	return 1;
	return 0;
}
```
这段打完之后，另外的问题又扑面而来：如何转换日期呢？

首先，我们知道这道题目给我们的初始日期为$1900$年$1$月$1$日星期一。其次，我们再回看题目：

>$2,4,6,11$和$9$月有30天.其他月份除了$2$月都有$31$天.闰年$2$月有$29$天,平年$2$月有$28$天。

我们都知道，从本月末到下月初，月份要加$1$，天份要归$1$。从今年末到明年初，年份要加$1$，月份和天份都归$1$。星期数到了$7$，下一天也要归$1$。

所以，我们想到了如下的转换日期程序：

$Step~1:$从$1900$年$1$月$1$日星期一开始！

$Step~2:$如果一切正常，天份加$1$，星期数也加$1$。

$Step~3:$如果到了星期末，就要将星期数及时归$1$。

$Step~4:$如果到了月末，月份就要加$1$，天份同时要归$1$。

$Step~5:$在执行$Step~4$的时候，如果还到了年末，年份加$1$，月份和天份同时归$1$。

程序也很明了了吧，自己先打代码，若有困难再看以下代码：

```cpp
while(y <= 1900 + n - 1) {
//		printf("%d/%d/%d %d\n", y, m, d, week);
//		y是年份，m是月份，d是天份，week是星期数
//		ans[i]指对应星期数13日出现的次数
		if(d == 13) ans[week]++;
		week++;
		if(week > 7)	week = 1;
		d++;
		if(d > (m == 2 ? (check(y) ? f[m] + 1 : f[m]) : f[m])) {
			m++;
			d = 1;
		}
		if(m > 12) {
			y++;
			m = 1;
		}	
	}
```

输出就没什么好讲的，可以暴力输出，可以用两个循环输出，还可以用各种奇葩的方法输出。反正随你们便。

下面贴完整代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

inline int read() {
	int f = 1, x = 0;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
const int f[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int y = 1900, m = 1, d = 1, n, week = 1;
int ans[7];

bool check(int n) {
	if(n % 100 == 0) {
		if(n % 400 == 0)	return 1;
		return 0;
	}
	if(n % 4 == 0)	return 1;
	return 0;
}
int main() {
	n = read();
	while(y <= 1900 + n - 1) {
//		printf("%d/%d/%d %d\n", y, m, d, week);
		if(d == 13) ans[week]++;
		week++;
		if(week > 7)	week = 1;
		d++;
		if(d > (m == 2 ? (check(y) ? f[m] + 1 : f[m]) : f[m])) {
			m++;
			d = 1;
		}
		if(m > 12) {
			y++;
			m = 1;
		}	
	}
	for(int i = 6; i <= 7; ++i)
		printf("%d ", ans[i]);
	for(int i = 1; i <= 5; ++i)
		printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：LattleGrass (赞：7)

## 此题相对简单，但是要注意一些问题就是说
## 首先输出第一个数字是周六的个数
## 然后是周日、周一等
## 其次就是可以吧每个月13号和上个月步进的值求出来
## 这样子对后续计算可以进一步简化
## 之后就是流程
- 1得到每个月步进值$a[12]=\{3,3,0,3,2,3,2,3,3,2,3,2\};$
- 2开一个大小为7的数组保存每天出现次数，并全体清空
- 3输入年份
- 4循环计算每个月的13号是周几并保存
- 5如果是闰年对二月特殊计算

## 一个小公式就是说$(day+a[12])\%7$是下一个月13号的天数所在周几
$((((i+1900)\%4==0) \&\& ((i+1900)\%100)) \|\| ((i+1900)\%400==0))$
## 的意思是说保证可被4整除且同时不可被100整除
## 或者可被400整除
## 之后循环输出每周中一天的所轮到的次数
```C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main(int argc,const char *argv[])
{
    int a[12]={3,3,0,3,2,3,2,3,3,2,3,2};//已经减去7的倍数，第一个是12月步进值
    int sum[7];//保存每天出现次数
    int i,j,n,day=4;//为四是保证第一次保存正确，从去年(1989-12-13)开始计算的，第一次保存在sum[0]即周六
    //memset(a,0,sizeof(a));//一定要注释，要不赋值就丢了
    memset(sum,0,sizeof(sum));//保证初始值为零
    scanf("%d",&n);//输入年份
    for(i=0;i<n;i++)
    {
        for(j=0;j<12;j++)
        {
            if(j==2 && ((((i+1900)%4==0) && ((i+1900)%100)) || ((i+1900)%400==0)))//对闰年且二月的判定
            {
                day=(day+a[j]+1)%7;//二月多一天
                sum[day]++;
            }
            else
            {
                day=(day+a[j])%7;
                sum[day]++;
            }
        }
    }
    for(i=0;i<7;i++)
    {
        printf("%d ",sum[i]);
    }
    return 0;
}
```
## 之后修改,想简化，但未实现
```C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main(int argc,const char *argv[])
{
    int fei[7]={2,1,1,3,1,2,2},shi[7]={3,1,1,2,2,1,2};
    int sum[7];
    int i,j,n,day=0;
    memset(sum,0,sizeof(sum));
    //scanf("%d",&n);
    for(n=1;n<=20;n++){
    for(i=0;i<n;i++)
    {
        if((((i+1900)%4==0) && ((i+1900)%100)) || ((i+1900)%400==0))
        {
            for(j=0;j<7;j++)
            {
                sum[j]+=shi[(day+j)%7];
            }
            day=(day-2)%7;
        }
        else
        {
            for(j=0;j<7;j++)
            {
                sum[j]+=fei[(day+j)%7];
            }
            day=(day-1)%7;
        }
    }
    for(i=0;i<7;i++)
    {
        printf("%d ",sum[i]);
        sum[i]=0;
    }
    day=0;
    printf("\n");
    }
    return 0;
}
```
### 打了下表

|星期|6 |7 |1 |2 |3 |4 |5 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|次数|2 |1 |1 |3 |1 |2 |2 |
|次数|4 |3 |2 |4 |4 |3 |4 |
|次数|6 |5 |4 |5 |5 |6 |5 |
|次数|7 |7 |6 |7 |6 |7 |8 |
|次数|9 |9 |7 |9 |9 |8 |9 |
|次数|10|10|10|10|11|10|11|
|次数|12|11|11|13|12|12|13|
|次数|14|13|12|14|15|13|15|
|次数|15|15|15|15|16|15|17|
|次数|18|16|17|17|18|16|18|
|次数|19|19|18|19|20|18|19|
|次数|20|20|21|20|22|20|21|
|次数|23|21|22|22|24|21|23|
|次数|25|23|24|23|25|24|24|
|次数|26|25|26|25|26|25|27|
|次数|29|26|28|27|28|26|28|
|次数|30|28|30|28|30|29|29|
|次数|32|29|31|31|31|31|31|
|次数|34|31|32|32|34|32|33|
|次数|36|33|34|33|35|35|34|

---

## 作者：buickboy (赞：5)

本题关键是求每月13日是星期几，至于星期几各有几天，只要桶计数即可解决。

用day++/week++模拟天数和星期几一天天过去是不必要的，只需要计算与上月13日的间隔天数，即可确定当月13日的星期数。而与上月13日的间隔天数，正是上月的月末最大值。比如：

1900.1.1是周一，那么1900.1.13是(13-1+1)%7=6周六，减1是间隔天数，加1是因为起始日是周一。继续可推断出1900.2.13是(31+6)%7=2周二。由此可知，每月的13日是周几，取决于上月是28、29、30还是31天，因为这关系到前后两个月间隔的天数，这个天数再模7，就可求得当月13日的星期数。

这样，就可以确定基本思路是：外循环遍历年份，从而可确定2月末天数；内循环遍历月份，上月末天数与上月13日星期数求和之后，再模7取余，即是当月13日的星期数。
公式是：当月13日星期数x=(上月末天数+上月13日星期数）%7。

这个思路还需要上月13日的星期数。由于本月13日星期数同时也是下月13日的上月星期数，这正好是变量赋值的特点，所以，以上公式又可简化为：x=(mi+x)%7，mi为当月末天数。

本思路需要上月13日星期数的初始值，因为1900.1.13是与1899.12.13来计算间隔天数的，需要先求出。由(31+x)%7=6，根据同余性质推出(3+x)%7=6，可知x=3，即周三。

现在用两个方法来减少代码量，一是设定每月天数数组，m[13]={0,31,28,31,30,31,30,31,31,30,31,30,31}，下标是月份、元素值是当月天数；二是年份循环用19**，好处是可直接判断当前年份i是不是闰年。

本题注意2月的天数问题，闰年为29平年为28，必须根据当年年份来更新，否则改变为闰年的29天后，会一直保持29这个值。

以下代码只需20行。

```cpp
#include<cstdio>
int b[8],m[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//周几作b桶，1-12月天数列到m数组 
int main()
{
	int n,i,j,x=3;//1899.12.13为周三，作为x初始值 
	scanf("%d",&n);//总计年度数 
	for(i=1900;i<=1900+n-1;++i)//年为外循环
	{
		if((i%4==0&&i%100!=0)||i%400==0) m[2]=29;//直接根据年号判断闰年 
		else m[2]=28;//根据年份确定2月末天数，此步不能省 
		for(j=1;j<=12;++j)//月为内循环 
		{
			if(j==1)//特判1月的上月为12月
				x=(m[12]+x)%7;//与上年12月13日间隔天数+12.13周几 
			else x=(m[j-1]+x)%7;//非1月则取上月间隔天数+上月13日周几 
			b[x]++;//桶计数
		}
	}
	printf("%d",b[6]);//周六数
	for(i=0;i<=5;++i)
		printf(" %d",b[i]);//周日-周五数
	return 0;
}

```

---

## 作者：lrh3321 (赞：2)

首先需要有判断某一年是否闰年。根据闰年的定义:

+ 闰年分为普通闰年和世纪闰年
+ 普通闰年:能被4整除但不能被100整除的年份为普通闰年。（如2004年就是闰年，1999年不是闰年）
+ 世纪闰年:能被400整除的为世纪闰年。（如2000年是闰年，1900年不是闰年）

分析题目：

1. “要求计算1900年1月1日至1900+N-1年12月31日”，$N=1$时，是计算1900年的1至12月。所以统计是以年为单位进行的，并且不会统计到1900+N年。
1. 由于我们只关心每月13号是星期几。我们需要3个变量分别记录 “现在是哪一年”、“现在是几月”、“这个月13是星期几”。
1. 我们使用`while`语句以月为单位进行循环，当月份为`12`时，年份+1，月份重置为1月，当年份为$1900+N$时跳出循环。
1. 循环初始条件，当前年份: `year = 1900`, 终止年份: `endYear = year + N`, 当前月份: `month = 1`, 当月13号是星期几: `week = 13 % 7`(0代表星期天)
1. 根据当前月份以及是否是闰年，判断到下个月的13号需要经过几天。

> Talk is cheap. Show me the code.

代码走起：

```cpp
#include <iostream>

using namespace std;

int N, counter[7] = {0};

// 判断是否是闰年
inline bool isLeapYear(const int& n)
{
    if (n % 400 == 0)
        return true;
    if (n % 100 != 0 && n % 4 == 0)
        return true;

    return false;
}

int main()
{
    cin >> N;
    int year = 1900, endYear = year + N, month = 1, week = 13 % 7;
    while(year < endYear)
    {
        counter[week]++;
        switch(month)
        {
        case 2:
            if (isLeapYear(year))
                week += 29;
            else
                week += 28;
            break;
        case 4:
        case 6:
        case 11:
        case 9:
            week += 30;
            break;
        case 12:
            week += 31;
            ++year;
            month = 0;
            break;
        default:
            week += 31;
        }
        ++month;
        week %= 7;
    }

    cout << counter[6];
    for(int i = 0; i < 6; ++i)
        cout << ' ' << counter[i];
    return 0;
}
```


---

## 作者：转身、已陌路 (赞：2)

这道题目唯一坑的地方就是是从星期六开始输到星期五！！！！！

这题很水   暴力模拟！！！

分别枚举 年份 月份  日子  13号 就记录一下 额外的要判断闰年



```cpp
#include<bits/stdc++.h>//蒟蒻代码 不喜勿喷
using namespace std;
int a[10];//记录次数 
int b[20];
int main()
{
int n;
scanf("%d",&n);
int xiqi=0;
b[1]=31;b[2]=28;b[3]=31;b[4]=30;b[5]=31;b[6]=30;b[7]=31;b[8]=31;b[9]=30;b[10]=31;b[11]=30;b[12]=31;
for (int i=1900;i<=1900+n-1;i++)
for (int j=1;j<=12;j++)
{
     if((i%4==0&&i%100!=0)||i%400==0)
    {
     b[2]=29;
```
}//判断今年是不是闰年
```cpp
     else b[2]=28;
for (int k=1;k<=b[j];k++)
{
 xiqi++;
 if (xiqi>7) xiqi=1;
 if (k==13) a[xiqi]++;
       }
          }
printf("%d %d ",a[6],a[7]);//这题真的坑现输出星期六和星期天题目也没说明！！！ 
for (int i=1;i<=5;i++) 
    printf("%d ",a[i]);
    return 0;
}
```

---

## 作者：JerryC (赞：2)

这道题可以用最原始的方法解决。首先一一枚举从周一到周日的情况，再一一赋值，最后特判一下闰年就可以了。


代码比较长，但思路很清晰，摘如下：


/\*

ID:ba bing ba boom


TASK:friday


LANG:C++


\*/

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int d=0;
int ans[8],day=0;
int main()
{
    //freopen("friday.in","r",stdin);
    //freopen("friday.out","w",stdout);
    int n;
    cin>>n;
    for(int j=0;j<n;j++)//判断年数
    {
        for(int i=1;i<=31;i++)//一月
        {
            day++;
            if(i==13)//判断是不是十三号
            {
               d=day%7;
               if(d==0) ans[7]++;
               else ans[d]++;
            }
        }
        if((1900+j)%4==0&&(1900+j)%100!=0)//特判一下闰年
        {
           for(int i=1;i<=29;i++)//闰年二月
           {
              day++;
              if(i==13)
              {
                 d=day%7;
                 if(d==0) ans[7]++;//加入答案
                 else ans[d]++;
              }
           }
        }
        else if((1900+j)%400==0)//另一种情况
        {
          for(int i=1;i<=29;i++)
          {
              day++;
              if(i==13)
              {
                 d=day%7;
                 if(d==0) ans[7]++;
                 else ans[d]++;
              }
          }
        }
        else
        for(int i=1;i<=28;i++)//平年二月
        {
             day++;
             if(i==13)
             {
                 d=day%7;
                 if(d==0) ans[7]++;
                 else ans[d]++;
             }
        }
        for(int i=1;i<=31;i++)//三月
        {
             day++;
             if(i==13)
             {
                 d=day%7;
                 if(d==0) ans[7]++;
                 else ans[d]++;
             }
        }
        for(int i=1;i<=30;i++)//四月
        {
             day++;
             if(i==13)
             {
                 d=day%7;
                 if(d==0) ans[7]++;
                 else ans[d]++;
             }
        }
        for(int i=1;i<=31;i++)//五月
        {
            day++;
            if(i==13)
            {
            d=day%7;
            if(d==0) ans[7]++;
            else ans[d]++;
            }
        }
        for(int i=1;i<=30;i++)//六月
        {
            day++;
            if(i==13)
            {
            d=day%7;
            if(d==0) ans[7]++;
            else ans[d]++;
            }
        }
        for(int i=1;i<=31;i++)//七月
        {
            day++;
            if(i==13)
            {
            d=day%7;
            if(d==0) ans[7]++;
            else ans[d]++;
            }
        }
        for(int i=1;i<=31;i++)//八月
        {
            day++;
            if(i==13)
            {
            d=day%7;
            if(d==0) ans[7]++;
            else ans[d]++;
            }
        }
        for(int i=1;i<=30;i++)//九月
        {
            day++;
            if(i==13)
            {
            d=day%7;
            if(d==0) ans[7]++;
            else ans[d]++;
            }
        }
        for(int i=1;i<=31;i++)//十月
        {
            day++;
            if(i==13)
            {
            d=day%7;
            if(d==0) ans[7]++;
            else ans[d]++;
            }
        }
        for(int i=1;i<=30;i++)//十一月
        {
            day++;
            if(i==13)
            {
            d=day%7;
            if(d==0) ans[7]++;
            else ans[d]++;
            }
        }
        for(int i=1;i<=31;i++)//十二月
        {
            day++;
            if(i==13)
            {
            d=day%7;
            if(d==0) ans[7]++;
            else ans[d]++;
            }
        }
    } 
    cout<<ans[6]<<" "<<ans[7]<<" "<<ans[1]<<" "<<ans[2]<<" "<<ans[3]<<" "<<ans[4]<<" "<<ans[5]<<endl;//输出
    return 0;
}
//总的来说，这道题在时限内可以用暴力完美解决，至于高级一点的方法，可以用蔡勒公式。
```

---

## 作者：Chenyuanyang0001 (赞：2)

【我是首次发题解，请见谅】

由公式**W = [Y-1] + [(Y-1)/4] - [(Y-1)/100] + [(Y-1)/400] + D**。Y是年份数，D是这一天在这一年中的累积天数，也就是这一天在这一年中是第几天，只取计算结果的整数部分。算出来的W除以7，余数是几就 是星期几。如果余数是0，则为星期日。【此处来自百度】

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int d[8];//用来记录周一到周日之中13号出现的次数
int daysofmonth[13][2] = {{0, 0},{31, 31},{28, 29},{31, 31},{30, 30},{31, 31},{30, 30},{31, 31},{31, 31},{30, 30},{31, 31},{30, 30},{31, 31}}; //当闰年或是平年时的月份日子
bool isYear(int x){  
    if((x % 400 == 0) || (x % 4 == 0 && x % 100 != 0))return 1;//判断是闰年或是平年
    else return 0;  
}   
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int day=0;//记录这一天在这一年中是第几天
        int t=isYear(1900 + i);  
        int n=1900+i;
        for(int j=1;j<=12;j++)//开始枚举月份
        {
            int D=day+13;//开始是第13天，后来再加上月份
            d[((n-1)+(n-1)/4-(n-1)/100+(n-1)/400+D)%7]++;//公式运用
            day+=daysofmonth[j][t];
        }
    }
    cout<<d[6]<<" "<<d[0]<<" "<<d[1]<<" "<<d[2]<<" "<<d[3]<<" "<<d[4]<<" "<<d[5]<<endl; //d[0]也就是d[7]
    return 0;
}
```

---

## 作者：Johnson_sky (赞：2)

模拟即可，注意闰年的2月份，下面代码可以缩减：

/\*
ID:skyzs202

PROG:friday

LANG:C++

\*/


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,year=1900,month=1,day=1,fyear,fday,now=1,a[8];
int main()
{
    scanf("%d",&n);
    fyear=1900+n-1;
    while(year<=fyear)
    {
        while(month<=12)
        {
            switch(month)
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    {
                        fday=31;
                        break;
                    };
                case 4:
                case 6:
                case 9:
                case 11:
                    {
                        fday=30;
                        break;
                    };
                case 2://注意2月份
                    {
                        if((year%400==0)||(year%4==0 && year%100!=0))
                        {
                            fday=29;
                        }
                        else
                        {
                            fday=28;
                        }
                        break;
                    };
            }
            while(day<=fday)
            {
                if(now==8)
                {
                    now=1;//调整星期
                }
                if(day==13)
                {
                    a[now]=a[now]+1;//记录每个月的13日
                }
                now++;
                day++;//叠加
            }
            day=1;
            month++;//处理月份
        }
        month=1;
        year++;//处理年份
    }
    printf("%d %d %d %d %d %d %d\n",a[6],a[7],a[1],a[2],a[3],a[4],a[5]);
    return 0;
}
```

---

## 作者：大魔鬼灿灿 (赞：2)

这题主要是模拟算法，找到寻找的规律就好做了  
我的做法是：开一个大点的数组存每年每月13号的星期日期，再开两个平年闰年每月几天的数组，分这两种情况累加，第1个是6的定下的，然后继续找，直到1900+n+1年的结束，然后星期几统计个数，最后按要求输出就好了
上代码
```
//算法：数论，模拟 
#include<cstdio>
using namespace std;
int n,ans=0,t=0;
int a[7]={0},m=1;//a数组存星期的天数 
int c[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};//闰年一年的各个月天数 
int d[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//平年一年的各个月天数 
int b[100001];//存13号 
int main()
{
	scanf("%d",&n);//输入 
	b[++t]=6;//第一个是星期6 
	for(int i=1900;i<=n+1900-1;i++)//循环 
	{
		m=12;
		if(i%400==0||(i%4==0&&i%100!=0))//闰年 
		{
		    for(int j=1;j<=12;j++)//循环找13号 
		    {
		    	t++;
		    	b[t]=(b[t-1]+c[j])%7;
			}
		}
		else//平年 
		{
			for(int j=1;j<=12;j++)
		    {
		    	t++;
		    	b[t]=(b[t-1]+d[j])%7;
			}
		}
	}
	for(int i=1;i<t;i++) a[b[i]]++;//累计 
	printf("%d ",a[6]);//输出 
	for(int i=0;i<=5;i++) printf("%d ",a[i]);
	return 0;
}
```


---

## 作者：_jimmywang_ (赞：1)

## 23ms, 856KB
#### 真▪纯模拟题，两个月前就想做了，一直没敢下手。

#### 今个儿一言不合从21:12敲到21:16然后一遍过……

#### 开始怀疑自己估计题目难度的能力……

首先，什么是闰年~~~ 呢？

题目说了啊：

```
3、年份可以被4整除的为闰年
(1992=4*498 所以 1992年是闰年,但是1990年不是闰年).

4、以上规则不适合于世纪年。
可以被400整除的世纪年为闰年,否则为平年。
所以,1700,1800,1900和2100年是平年,而2000年是闰年.
```

于是我们愉快地有了这个函数：
```
bool check(int x)
{
    if(x%4==0/*对应3*/&&x%100!=0/*对应4*/)return 1;
    if(x%100==0&&x%400==0/*对应4*/)return 1;
    return 0;//都不是？那就不是啦！
}
```
然后呢？

主要思路：

从1900到1900+n-1(就是1899+n)循环，开个叫b的数组，存每月天数。

每次循环把b[2]赋值为28，是闰年就加1。

接下来如果不是闰年，就@#￥%#%#！##

是闰年，就%@*￥……%*@*￥……%

好了好了，你们一定很想看代码，上面那堆东西就留在代码里好了。

```
#include<bits/stdc++.h>
using namespace std;
int a[8];//存答案
int n,p=1;//p是一个指针，表示循环到星期几。
int b[14]={0,31,28,31,30,31,30,31,31,30,31,30,31};//上面讲了
bool check(int x)//真香
{
	if(x%4==0&&x%100!=0)return 1;
	if(x%100==0&&x%400==0)return 1;
	return 0;
}
int main()
{
    cin>>n;
    for(int i=1900;i<=1899+n;i++)
    {
    	b[2]=28;//赋值为28
    	if(check(i)==0)//这里是@#￥%#%#！##
    	{
    		for(int j=1;j<=12;j++)
    		{
    			for(int k=1;k<=b[j];k++)
    			{
    				if(k==13)a[p]++;//你们应该看得懂……
					p++;
    				if(p!=7)p%=7;
				}
			}
		}
		else//这里是%@*￥……%*@*￥……%
		{
			b[2]=29;
			for(int j=1;j<=12;j++)
    		{
    			for(int k=1;k<=b[j];k++)
    			{
    				if(k==13)a[p]++;//你们还是应该看得懂……
					p++;
    				if(p!=7)p%=7;
				}
			}
		}
	}
	cout<<a[6]<<" "<<a[7]<<" "<<a[1]<<" "<<a[2]<<" "<<a[3]<<" "<<a[4]<<" "<<a[5];//从星期六开始输出
    return 0;//UKE在加了这句话后突然失踪……
}
```

代码丑，不要介意………………………………………………………………


#### 第四篇题解，结束


---

## 作者：MissLXCYu (赞：1)

似乎和题解有一点不一样，看起来貌似简单一点？？

大概就是记录上一个月13号是星期几，加上上一个月日期，取余，得到这个月是星期几




    
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
bool check(int n){//判断闰年 
    if(n%4!=0||(n%100==0&&n%400!=0)) return 0;
    return 1;
}
int main()
{
    int n;
    cin>>n;
    int cnt[7];
    memset(cnt,0,sizeof(cnt));
    int day=3;
    for(int i=0;i<n;++i)//按年循环 
        for(int j=1;j<=12;++j)//按月循环 
            switch(j){//每个月加上一个月的天数再取余就好了，用day做变量记录 
                case 1 :day+=31;day%=7;cnt[day]++;break;
                case 2 :day+=31;day%=7;cnt[day]++;break;
                case 3 :if(check(1900+i)) 
                            day+=29,day%=7;
                        else 
                            day+=28,day%=7;
                        cnt[day]++;break;
                case 4 :day+=31;day%=7;cnt[day]++;break;
                case 5 :day+=30;day%=7;cnt[day]++;break;
                case 6 :day+=31;day%=7;cnt[day]++;break;
                case 7 :day+=30;day%=7;cnt[day]++;break;
                case 8 :day+=31;day%=7;cnt[day]++;break;
                case 9 :day+=31;day%=7;cnt[day]++;break;
                case 10 :day+=30;day%=7;cnt[day]++;break;
                case 11 :day+=31;day%=7;cnt[day]++;break;
                case 12 :day+=30;day%=7;cnt[day]++;break;
            }
    cout<<cnt[6]<<" ";//从周六开始输出 
    for(int i=0;i<=5;++i)//注意周日是cnt[0] 
        cout<<cnt[i]<<" ";
    cout<<endl;
    return 0;
}
```

---

## 作者：DarkStalker (赞：1)

这里提供一种暴力的解法

可能会比较容易理解

如果没有想明白的话可以用这种方法

但是统计本年的第几天 mod 7这种方法会更好一些

代码量有一点多





















```cpp
#include <stdio.h>
typedef struct date
{
    int year; //年
    int month; //月
    int day; //日
    int week;    //星期几，周一到周六为1 - 6，周日为0
} Date;
int is_over(void); //是否到题目给的界限
int get_day(void); //得到现在的月份的天数
void until(int day); //将现在的天数加到day停止
void next_week(void); //累加星期数
void next_month(void); //当到达本月月底时进入下一个月
int n;
int total[10];
Date start;
int main(void)
{
    //freopen("friday.in", "r", stdin);
    //freopen("friday.out", "w", stdout);
    int temp, i;
    start.year = 1900;
    start.month = 1;
    start.day = 1;
    start.week = 1;
    scanf("%d", &n);
    while (!is_over()) //没有结束的话
    {
        until(13); //累加到本月13号
        total[start.week]++; //统计星期几的数量
        until(get_day()); //累加到本月月底
        next_month(); //进入下一个月
    }
    printf("%d %d %d %d %d %d %d", total[6], total[0], total[1], total[2], total[3], total[4], total[5]); //先输出周六周日，在输出周一到周五
    return 0;
}
int is_over(void)
{
    if (start.year == n + 1900 && start.month == 1)
    {
        return 1;
    }
    return 0;
}
int get_day(void)
{
    if (start.month == 4 || start.month == 6 || start.month == 11 || start.month == 9) //大月
    {
        return 30;
    }
    else if (start.month == 2) //平月
    {
        if ((start.year % 4 == 0 && start.year % 100 != 0) || (start.year % 400 == 0)) //闰年
        {
            return 29;
        }
        else //小月
        {
            return 28;
        }
    }
    else
    {
        return 31;
    }
}
void until(int day)
{
    while (start.day < day)
    {
        start.day++;
        next_week(); //每次在累加日期时都要同时累加星期
    }
}
void next_week(void)
{
    if (start.week == 6) //星期六的话就到星期天
    {
        start.week = 0;
    }
    else
    {
        start.week++;
    }
}
void next_month(void)
{
    if (start.month == 12)
    {
        start.year++;
        start.month = 1; //月份归一
        start.day = 1; //日期归一
        next_week(); //同理，处理星期
    }
    else
    {
        start.month++;
        start.day = 1; //日期归一
        next_week(); //处理星期
    }
}
```

---

## 作者：xueliancheng (赞：1)

利用蔡勒公式(ZellerWeek)即可快速求出指定日期是星期几。

蔡勒公式：w=(y+y/4+c/4-2c+13(m+1)/5+d-1)%7


c:世纪数-1的值，如21世纪，则c=20;

m:月数，m的取值是大于等于3，小于等于14.在蔡勒公式中，某年的1月和2月被看成**上一年**的13月和14月，例如2001年2月1日要当成2000年的14月1日计算。

y:月份，取**公元纪年的后**两位****，如1998年，y=98, 2001年，y=1。

d:某月内的日数。


蔡勒公式核心代码：

###
    
    



```cpp
int ZellerWeek(int year,int month,int day)
{
    int m=month;
    int d=day;
    if(month<=2)
    {
        year--;
        m=month+12;            //处理小月份
    } 
    int y=year%100;
    int c=year/100;
    int w=(y+y/4+c/4-2*c+(13*(m+1)/5)+d-1)%7;
    if(w<0)
    {
        w+=7;     //蔡勒公式有时计算出的结果为负数，需要对结果进行+1处理
    }
    return w;
}
```
程序完整代码：
###

    
    

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
int n,day[8];
int ZellerWeek(int year,int month,int day)
{
    int m=month;
    int d=day;
    if(month<=2)
    {
        year--;
        m=month+12;
    } 
    int y=year%100;
    int c=year/100;
    int w=(y+y/4+c/4-2*c+(13*(m+1)/5)+d-1)%7;
    if(w<0)
    {
        w+=7;
    }
    return w;
}
int main()
{
    scanf("%d",&n);
    for(int i=1900;i<=n+1900-1;i++)
    {
        for(int j=1;j<=12;j++)
        {
            int k=ZellerWeek(i,j,13);
            day[k]++;
        }
    }
    printf("%d %d %d %d %d %d %d",day[6],day[0],day[1],day[2],day[3],day[4],day[5]); 
//    printf("%d",ZellerWeek(2016,8,23));
    return 0;
}
```

---

## 作者：fl_334 (赞：1)

```cpp
//不想说，模拟水题。。。
var
        x,m,y,d,i,n,j:longint;
        th:array[1..7]of longint;        //存放各个星期的天数
procedure tt(var m:longint);       //每月月底更新器
begin
        d:=1;
        inc(m);
end;
begin
        readln(n);
        y:=1900;        //初始化大军来袭
        m:=1;
        d:=1;
        x:=1;
        i:=0;
        fillchar(th,sizeof(th),0);
        while (i<n) do     //i为过了多少年
        begin
                inc(x);      //x表示星期几
                if x=8 then x:=1;
                case m of          //m表月份
                1,3,5,7,8,10,12:if d=31 then tt(m)            //天数31的
                else d:=d+1;
                4,6,9,11:if d=30 then tt(m)        //天数30的
                else d:=d+1;
                2:if (y mod 4=0) and (y mod 100<>0) or (y mod 400=0) then if d=29 then tt(m)         //2月特殊处理
                else inc(d)
                else if d=28 then tt(m)
                else inc(d);
                end;
                if m=13 then begin m:=1;inc(y);inc(i);end;       //12月月底特殊处理
                if d=13 then inc(th[x]);        //d表天，到了13号就要+1喔
        end;
                write(th[6],' ',th[7],' ');            //表示伤不起的输出。。。。
                for i:=1 to 5 do
                        write(th[i],' ');
end.

```

---

## 作者：邓晓蓝 (赞：1)

//简单的模拟搞定。一天天加起来，如果是13号就累加。最后输出。不过注意闰年，月的天数等等。

```cpp
var n1,x,n,y,r,i:longint;
    sz:array[1..7] of longint;
begin
  readln(n1);
  x:=1;n:=1900;y:=1;r:=1;
  repeat
    inc(x);
    inc(r);
    if x=8 then x:=1;
    if r=13 then inc(sz[x]);
    if y in [1,3,5,7,8,10,12] then
      if r=32 then begin inc(y);r:=1;end;
    if y in [4,6,9,11] then
      if r=31 then begin inc(y);r:=1;end;
    if y=2 then
      begin
        if ((n mod 4=0) and (n mod 100<>0)) or (n mod 400=0) then
        begin
        if r=30 then begin inc(y);r:=1;end;
        end else if r=29 then begin inc(y);r:=1;end;
      end;
    if y=13 then begin inc(n);y:=1;r:=1;end;
  until n=1900+n1;
  write(sz[6],' ',sz[7],' ');
  for i:=1 to 5 do
    write(sz[i],' ');
end.
```

---

## 作者：YczSS (赞：1)

因为1900.1.1是星期一，所以1900.1.13就等于(13-1) mod7+1=星期六。这样讲可能不太清楚。那么，我来解释一下：每过7天是一个星期。n天后是星期几怎么算呢？现在假设n是7的倍数，如果n为14，那么刚好就过了两个星期，所以14天后仍然是星期一。但如果是过了15天，那么推算就得到是星期二。这样，我们就可以推导出一个公式来计算。(n天 mod 7（一个星期的天数）+ 现在日期的代号) mod 7 就等于现在日期的代号。当括号内的值为7的倍数时，其代号就为0，那么，此时就应该是星期日这样，我们可以得出题目的算法：



int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31}

 int b[8]={0}

a数组保存一年12个月的天数（因为C语言中数组起始下标为0，所以这里定义为13）。

b数组保存星期一到星期日出现的天数。用date记录目前是星期几的代号，然后用两个循环，依次加上所经过的月份的天数，就出那个月是星期几，当然，要注意判断闰年！知道了这个方法，实现起来就很容易了。

注意考虑闰月的情况。

最后注意要换行，否则会错误。


```cpp
var
wk:array[0..6]of Longint;
n,i,j,x,s,days,nk,m:Longint;
begin
 assign(input,'friday.in');reset(input);
  assign(output,'friday.out');rewrite(output);
   readln(n);
    nk:=1;m:=0;x:=13 mod 7;
     for i:= 1900 to 1900+n-1 do
       begin
        for j:= 1 to 12 do
         begin
          case j of
          1,3,5,7,8,10,12 :days:=31;
          4,6,9,11        :days:=30;
          2               :if (i mod 4 = 0)and(i mod 100 <> 0)or(i mod 400 = 0)
                           then days:=29
                           else days:=28;
          end;
          wk[(x+nk-1) mod 7]:=wk[(x+nk-1) mod 7]+1;
          m:=days mod 7;
          s:=nk;
          if s+m=7 then nk:=7;
          nk:=(m+s) mod 7;
         end;
     end;
writeln(wk[6],' ',wk[0],' ',wk[1],' ',wk[2],' ',wk[3],' ',wk[4],' ',wk[5]);
 close(input);close(output);
end.
```

---

## 作者：美利坚共产党 (赞：1)

  
```cpp
var 
 n,x,i,j,k,f,s:longint;  
 a:array[1..7] of longint;  
begin 
 s:=0;  
 read(n);  
 x:=1900;  
 for i:=1 to n do begin 
  for j:=1 to 12 do begin 
   case j of 
    1,3,5,7,8,10,12:f:=31;  //判断闰年
    4,6,9,11:f:=30;  //判断闰年
    2:if (x mod 400=0)or((x mod 4=0)and(x mod 100<>0)) then f:=29 else f:=28; //判断二月天数 
   end;  
   for k:=1 to f do begin 
    inc(s);  
    if s>7 then s:=s mod 7;  //统计星期几
    if k=13 then inc(a[s]);  //处理13号
   end;  
  end;  
  inc(x);  //累积天数
 end;  
 write(a[6],' ',a[7]);for i:=1 to 5 do write(' ',a[i]); //从周六输出
end.  

```

---

## 作者：「QQ红包」 (赞：1)

这题数据很弱，所以一天一天的模拟都可以AC

```delphi

var n,i,j,k,d:longint;
    b:array[1..7] of longint;
    a:array [1..12] of longint
                         =(31,28,31,30,31,30,31,31,30,31,30,31);//每个月的天数
begin
    read(n);
    for i:=1900 to 1900+n-1 do
    begin
        if ((i mod 4=0)and(i mod 100<>0))or(i mod 400=0) then a[2]:=29 else a[2]:=28;//判断今年是不是闰年
    for j:=1 to 12 do//模拟12个月
        for k:=1 to a[j] do //模拟该月的天数
        begin
            inc(d);
            if d=8 then d:=1;
            if k=13 then inc(b[d]);
        end;
    end;
    write(b[6],' ',b[7],' ');
    for i:=1 to 5 do write(b[i],' ');//输出
end.

```

---

## 作者：TopSecret0 (赞：1)

人文+科学=ac！

数学好的公式，不知道公式的模拟也能AC！

这里给个数学的方法 然后此题就水了。。

蔡勒（zeller）公式：随便给一个日期，就能用这个公式推算出是星期几

W =〔 [C/4] - 2C + y + [y/4] + [13 \* (M+1) / 5] + d - 1 〕% 7

（或者是：w= 〔y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1 〕% 7）

若要计算的日期是在1582年10月4日或之前，公式则为

w=y+[y/4]+[c/4]-2c+[13(m+1）/5]+d+2

以1572年9月3日为例：

1572年9月3日后：w = (d + 2\*m+3\*(m+1)/5+y+y/4-y/100+y/400)%7;

1572年9月3日前：w = (d+2\*m+3\*(m+1)/5+y+y/4+5） % 7;

注意：

当年的1,2月要当成上一年的13,14月进行计算

符符号意义


w：星期； w对7取模得：0-星期日，1-星期一，2-星期二，3-星期三，4-星期四，5-星期五，6-星期六

c：世纪减1（年份前两位数）

y：年（后两位数）

m：月（m大于等于3，小于等于14，即在蔡勒公式中，某年的1、2月要看作上一年的13、14月来计算，比如2003年1月1日要看作2002年的13月1日来计算）

d：日

[ ]代表取整，即只要整数部分。

下面以中华人民共和国成立100周年纪念日那天（2049年10月1日）来计算是星期几，过程如下：

```cpp
w=y+[y/4]+[c/4]-2c+[26(m+1）/10]+d-1
=49+[49/4]+[20/4]-2×20+[26×（10+1）/10]+1-1
=49+[12.25]+5-40+[28.6]
=49+12+5-40+28
=54 （除以7余5）
```
即2049年10月1日（100周年国庆）是星期五。
再比如计算2006年4月4日，过程如下：

w=y+[y/4]+[c/4]-2c+[26(m+1）/10]+d-1

=6+[6/4]+[20/4]-2\*20+[26\*（4+1）/10]+4-1

=-12 （除以7余5，注意对负数的取模运算！实际上应该是星期二而不是星期五)

w=（-12%7+7）%7=2；


程序实现神马的就小case了吧 不给标程了


---

## 作者：liaokq (赞：1)

# 好吧，我承认我的代码比较耗时

## 但是比大家的都短（特别是楼下那位）

## 况且本题数据很水

## 本人亲测，n=100000都可以1秒过

```cpp
/*
#include<bits/stdc++.h>
using namespace std;

int daynum[3][13]={{0},{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};//这个数组用来记录闰年和平年的每月日期数
int sum[8],week=1;//sum数组记录星期几有几个13号
int n,i,j,k,flag=1;//flag用来记录这一年是平年还是闰年，当然本人的习惯就是从1开始，其实flag可以开成bool类型
int main()
{
	cin>>n;
    //以下都是模拟
	for(i=1900;i<=1900+n-1;i++)
	{
		if(i%4==0)
		{
			if(i%400==0)flag=2;
			  else if(i%100==0)flag=1;
			      else flag=2;
		}
                   else flag=1;//以上为闰年判断
		for(j=1;j<=12;j++)
		{
			for(k=1;k<=daynum[flag][j];k++)
			{
				if(k==13)sum[week]++;
				week++;
				if(week>7)week=1;//这么写更加简便，一天一天模拟，不用判断13号是星期几
			}
		}
	}
	cout<<sum[6]<<" "<<sum[7]<<" "<<sum[1]<<" "<<sum[2]<<" "<<sum[3]<<" "<<sum[4]<<" "<<sum[5]<<endl;
	return 0;
 } 
 */
```
我们可以算一算数据有多水

以我的代码来看，在数据最大的情况下，时间复杂度为O（400×12×30）=O（144000），水的一匹

##  遵守洛谷规定，切勿Ctrl+C
## （你倒是复制一下看看能不能过啊）

---

## 作者：sxjzycwcy (赞：1)

# 数学是一切自然科学的基础
## ——用数学的方法解决问题
首先，简化问题，就是在问某年某月某日是周几，可以用数学的方法来思考

~~（部分思路来自百度文库）~~

首先假设所有的年份都是平年，那么每年经过365天，到第n-1年共经历了365（n-1）天，然后再认识符号“⌊ ⌋”，专业名称叫做 向下取整符，不做解释，那么在这n-1年中，总共经历了⌊（n-1）/4⌋个可被4整除的闰年，但是还有如1800，1900等年份，所以要再减去⌊（n-1）/100⌋，但是，这时又把能整除400的年份去掉了，所以要再加上⌊（n-1）/400⌋，然后再加上过了某一年的几天days，最后再对7取模。
### ↓整理一下，公式大概是↓
### [(n-1)×365+⌊(n-1)/4⌋-⌊(n-1)/100⌋+⌊(n-1)/400⌋+days]%7
再根绝和余数有关的定理
~~（叫什么我不知道，但感觉是正确的）~~
：
如果a%b=c，那么c%b=c，再返回公式，365%7=1那么1%7=7；所以可以化简为
### [(n-1)+⌊(n-1)/4⌋-⌊(n-1)/100⌋+⌊(n-1)/400⌋+days]%7
所以只需要算出days就可以求出星期了

### 贴AC代码↓
```
#include<bits/stdc++.h>//头文件
using namespace std;//命名空间
int sum[7];//记录每个星期的和
bool year(int y)//判断是否是闰年
{
	if((y%100!=0&&y%4==0)||y%400==0)//根据闰年判断规则，能被4整除而不能被100整除 或 能被400整除
		return 1;//返回是闰年
	return 0;//如果没有返回那么就不是闰年，主要是懒得打else了
}
void func(int n)//一个魔性的函数名
{
	int m[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//1-12月表（其实12月没必要）
	int i,days=0,j;//i和j判断循环，days如其名
	if(year(n)==1)//如果是闰年
		m[2]++;//2月+1
	for(i=1;i<=12;i++)//从1月到12月枚举
	{
		days=0;//注意归零（这里卡了半天）
		for(j=1;j<i;j++)//累加天数是从1月到当前月-1
			days+=m[j];//天数累加
		days+=13;//因为是求13号的，所以最后加13
		sum[(n-1+(n-1)/4-(n-1)/100+(n-1)/400+days)%7]++;//套用公式，注意因为7%7=0，所以sum[0]代表周日
	}
}

int main()//这是主程序
{
	int n,i;//定义变量，i是循环变量，n如题
	memset(sum,0,sizeof(sum));//初始化
	cin>>n;//输入
	n=n+1900-1;//设定循环周期
	for(i=1900;i<=n;i++)//开始循环
	{
		func(i);//调用函数
	}
	for(i=1;i<=7;i++)//循环输出
		cout<<sum[(i+5)%7]<<" ";//输出月份，注意是从周六开始，大概这样就行了就不用特判了
   return 0;//最后结束
 } 
```
我的注释是不是太多了。。。
# **END**

---

## 作者：垣根帝督 (赞：0)

[传送门在此](https://www.luogu.org/problem/P1202)

其实就是一道模拟

# 注意

## 坑在这:

#  ~~**输出请从周六开始~~(逃

解释都在代码里了

~~可能变量名有点问题~~


```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
int n1;//为题目中的n
int n=1900;//初始年
int year=1;//记录年
int day=1;//记录天
int week=1;//记录周
int yon;//标记
int month[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};//两种年:闰年和平年,先把每个月的天数列出来
int wew[8]={0};//答案
bool rn(int h)//判断是否是闰年
{
    if(h%100==0)
	{
        if(h%400==0)return true;
        else return false;
    }
    else
	{
        if(h%4==0)return true;
        else return false;
    }
}
int main()
{
    cin>>n1;
    while(1)
    {  
    	if(n==1900+n1&&year==1&&day==1)break;//如果已经到达规定时间
        if(rn(n))yon=1;//如果是闰年,标记
        else yon=0;
        day+=1;/.天数加一
        week+=1;//星期数加一
        if(day>month[yon][year])//如果天数超过规定月份的天数
        {
            day=1;//清为1
            year+=1;月加一
        }
        if(year>12)//如果月份大于12个
        {
            n+=1;//年加一
            year=1;//清为1
        }
        if(week>7)week=1;//如果天数大于7天,记为一周
        if(day==13)wew[week]+=1;//如果是13号,在星期week的答案加一
    }
    cout<<wew[6]<<" "<<wew[7]<<" "<<wew[1]<<" "<<wew[2]<<" "<<wew[3]<<" "<<wew[4]<<" "<<wew[5];//输出
    return 0;
}
```
管理员大大求过n_n~~~

---

## 作者：松鼠党 (赞：0)

蒟蒻的第二篇题解。  
思路耿直又有些粗暴。  
和别人一样，写一个函数判闰年。  
然后按年算，年的循环中嵌套月循环。  
一言不合上代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,xin=6;
int yue[13]={0,31,28,31,30,31,30,31,31,30,31,30,31}/*记录每月的天数*/,ans[6];
bool run(int nian){//函数判闰年
	if(nian%400==0)
	   return true;
	if(nian%100==0)
	   return false;
	if(nian%4==0)
	   return true;
	return false;
}
int main(){
	cin>>n;
	for(int i=1900;i<=1900+n-1;i++){//按思路循环
		for(int j=1;j<=12;j++){
			xin+=yue[j];
			if(j==2)
			   if(run(i))
				  xin++;
			xin%=7;
			ans[xin]++;
		}
	}
	cout<<ans[6]+1<<" "<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<" "<<ans[3]<<" "<<ans[4]<<" "<<ans[5]<<" "<<endl;//输出，ans[0]即为周日。
	return 0;
}

```
然后你会发现这个代码给你带来的是WA，WA，WA，WA，WA，WA，WA，WA，WA，WA。  
坑点：你多算了1900+n年的1月的13号。  
然后交上修改代码（只给核心）  
```cpp
for(int i=1900;i<=1900+n-2;i++){
		for(int j=1;j<=12;j++){
			xin+=yue[j];
			if(j==2)
			   if(run(i))
				  xin++;
			xin%=7;
			ans[xin]++;
		}
	}
	for(int j=1;j<=11;j++){
		xin+=yue[j];
		if(j==2)
			if(run(1900+n-1))
				xin++;
		xin%=7;
		ans[xin]++;
	}
```
行了，AC，AC，AC，AC，AC，AC，AC，AC，AC，AC。

---

## 作者：n0000000000o (赞：0)

```
//P1202 [USACO1.1]黑色星期五Friday the Thirteenth
#include <iostream>
using namespace std;
int day[8];//记录日期 
//参数：本月 1号为星期？； 返回值：下个月 1号为星期？
int d30 (int date);//一月30天 
int d31 (int date);//一月31天 
int d29 (int date);//闰年二月 
int d28 (int date);//非闰年二月 
//参数：今年 1月1号为星期？； 返回值：明年 1月1号为星期？
int yearR (int date);//闰年  
int yearP (int date);//平年 
int main()
{
	
	int n ;
	cin >> n;
//	cout << "?" << d31(n) << endl;
	int date = 1;//1900.1.1 星期一 
	for (int i = 0; i < n; i++)
	{
		int now = 1900 + i;
		if ( now % 400 == 0 || ( now % 4 == 0 && now % 100 != 0 )) //为闰年 
			date = yearR(date);
		else
			date = yearP(date);
	}
	for (int i = 1; i <= 7; i++)
		cout << day[(i+4)%7+1] << " ";
}
//参数：本月 1号为星期？； 返回值：下个月 1号为星期？
int d30 (int date)//一月30天 
{
	int riqi = 0, xingqi = date - 1;
	while (++riqi <= 30)
	{
		xingqi++;
		if (xingqi == 8)
			xingqi = 1;
		if (riqi == 13)
			day[xingqi]++;
	}
	return xingqi%7 + 1;
}
int d31 (int date)//一月31天 
{
	int riqi = 0, xingqi = date - 1;
	while (++riqi <= 31)
	{
		xingqi++;
		if (xingqi == 8)
			xingqi = 1;
		if (riqi == 13)
			day[xingqi]++;
	}
	return xingqi%7 + 1;
}
int d29 (int date)//闰年二月 
{
	int riqi = 0, xingqi = date - 1;
	while (++riqi <= 29)
	{
		xingqi++;
		if (xingqi == 8)
			xingqi = 1;
		if (riqi == 13)
			day[xingqi]++;
	}
	return xingqi%7 + 1;
}
int d28 (int date)//非闰年二月 
{
	int riqi = 0, xingqi = date - 1;
	while (++riqi <= 28)
	{
		xingqi++;
		if (xingqi == 8)
			xingqi = 1;
		if (riqi == 13)
			day[xingqi]++;
	}
	return xingqi%7 + 1;
}

int yearR (int Jan)//闰年  
{
	int Feb = d31(Jan);
	int Mar = d29(Feb);//注意这里不同哦！！ 
	int Apr = d31(Mar);
	int May = d30(Apr);
	int Jun = d31(May);
	int Jul = d30(Jun);
	int Aug = d31(Jul);
	int Sept = d31(Aug);
	int Oct = d30(Sept);
	int Nov = d31(Oct);
	int Dec = d30(Nov);
	return d31(Dec);
} 
int yearP (int Jan)//平年 
{
	int Feb = d31(Jan);
	int Mar = d28(Feb);//注意这里不同哦！！ 
	int Apr = d31(Mar);
	int May = d30(Apr);
	int Jun = d31(May);
	int Jul = d30(Jun);
	int Aug = d31(Jul);
	int Sept = d31(Aug);
	int Oct = d30(Sept);
	int Nov = d31(Oct);
	int Dec = d30(Nov);
	return d31(Dec);
} 
```

---

