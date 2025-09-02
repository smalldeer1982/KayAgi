# Codeforces World Finals

## 题目描述

## 题意描述
关于 Codeforces 的网站 king Copa 经常被报道，使得它在要使用网站进行训练和比赛的人之间迅速流行开来。最近， Copa 明白，要征服世界，他需要组织世界 Codeforces 锦标赛。他希望在这次比赛之后之后，最聪明的人将成为被挑选出来成为他的下属，然后征服世界最艰难的部分将会完成。

Codeforces 世界总决赛的最后一轮定于 $YY$ 年 $MM$ 月 $DD$ 日举行，其中 $DD$  是当天的日期， $MM$ 是当月的月份， $YY$ 是当年的年份的最后两位。Bob 很幸运地能成为来自 Berland 的一名决赛选手。但有一个问题：根据比赛规则，所有参赛者在决赛时必须年满 $18$ 岁。 Bob 出生于 $BY$ 年， $BM$ 月，$BD$ 日。这个日期记录在他的护照上，他的护照复印件已经寄给了组织者。但是 Bob 了解到，在不同的国家，日期的书写方式是不同的。例如，在美国，先写月份，然后写日期，最后写年份。

鲍勃想知道是否有可能重新排列他出生日期的数字，以便他在 $YY$ 年， $MM$ 月， $DD$ 日那天至少 $18$ 岁。他看出，在他的祖国，日期写的顺序不一样。请帮帮他。
根据另一个奇怪的规则，合格的参赛者必须与决赛日期出生在同一个世纪。如果决赛当天刚好是参赛者的 $18$ 岁生日，则他可以参加。

因为我们只考虑从 $2001$ 年到 $2099$ 年的决赛年份，所以使用以下规则：如果年份的数字可以被 $4$ 整除，那么年份就是闰年。

## 样例 #1

### 输入

```
01.01.98
01.01.80
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
20.10.20
10.02.30
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
28.02.74
28.02.64
```

### 输出

```
NO
```

# 题解

## 作者：huwanpeng (赞：3)

[题目在这里](https://www.luogu.com.cn/problem/CF30B)

这道题~~很水~~，就是纯枚举，找到一个可行解就输出 YES。

只需要注意几个易错点就可以了。

1. 输入强推 scanf，方便快捷。

1. 枚举时要枚举所有情况。

1. 判断选手是否满18岁时还要判断日期是否越界。

AC Code:

```cpp
#include<cstdio>
using namespace std;
int dd,mm,yy,bd,bm,by;
int day[20]={0,31,28,31,30,31,30,31,31,30,31,30,31};
//所有天数 
bool check(int d,int m,int y)
{
	if(d<1||d>day[m]+(m==2&&y%4==0)||m<1||m>12||y<1||y>99)
	//作越界判断 
	return false;
	return (yy-y>18||(yy-y==18&&m<mm)||(d<=dd&&m==mm&&yy-y==18));
	//满足一个就可以参加比赛 
}
int main()
{
	scanf("%d.%d.%d",&dd,&mm,&yy);
	scanf("%d.%d.%d",&bd,&bm,&by);
	if(check(bd,bm,by)||check(bd,by,bm)||check(bm,bd,by)||check(bm,by,bd)||check(by,bd,bm)||check(by,bm,bd))
	//枚举所有六种情况 
	printf("YES");
	else
	printf("NO");
	return 0;
}
```


---

## 作者：WYFwyf (赞：3)

//列举所有情况后判断是否合法就好了
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int md[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int d,m,y;
int tf(int d1,int m1,int y1)
{
	if(m1<1||m1>12||d1<1||d1>md[m1]+int(m1==2&&y1%4==0)) //不合法情况 
	return 0; 
	return (y1+18<y||y1+18==y&&m1<m||y1+18==y&&m1==m&&d1<=d);//合法情况 
}
int main()
{
	int d1,m1,y1;
	scanf("%d. %d. %d",&d,&m,&y);
	scanf("%d. %d. %d",&d1,&m1,&y1);
	if(tf(d1,m1,y1)||tf(d1,y1,m1)||tf(m1,d1,y1)||tf(m1,y1,d1)||tf(y1,d1,m1)||tf(y1,m1,d1))//列举所有情况 
	cout<<"YES"<<endl;
	else
	cout<<"NO"<<endl;
	return 0;
}
```

---

## 作者：SSWssw (赞：2)

```
//求出最长的时间差距进行判断
//也许暴力更好 
# include<iostream>
# include<cstdio>
# include<algorithm>
using namespace std;
int i,j,birth[10],dd,mm,yy,bd,bm,by,r=0;//r不能是月份的数值的个数 
char s;
int main()
{
	scanf("%d.%d.%d",&dd,&mm,&yy);
	for(i=0;i<3;i++)
	{
		cin>>birth[i];
		if(i!=2) cin>>s;
		if(birth[i]>12)  r++;
	}
	sort(birth+0,birth+3);
	if(r>1)
	{
		bm=birth[0];
		if(birth[2]<31)
		{
			by=birth[1];bd=birth[2];
		}
		else
		{
			by=birth[2];bd=birth[1];
		}
		if(bm==2&&bd==29&&(by+2000)%4!=0)//避免平年2月多一天 
		{
			bd=birth[1];
			by=birth[2];
		}
	}
	else
	{
		if(birth[2]>31)
		{
			by=birth[2];
			bm=birth[0];
			bd=birth[1];
			
		}
		else
		{
			by=birth[0];
			bm=birth[1];
			bd=birth[2];
			if(bm==2&&bd==29&&(by+2000)%4!=0)//避免平年2月多一天 
			{
				bd=birth[0];
				by=birth[2];
			}
		}
	}
	if(yy-by>18)
	  puts("YES");
	else if(yy-by==18&&bm<mm||yy-by==18&&bm==mm&&bd<=dd)
	  puts("YES");
	else
	  puts("NO");
	return 0;
}
```

---

## 作者：20100202w (赞：1)

这道题就是暴力

只要想的全面一些就行了

```cpp
#include<iostream>
#include<cstdio>//头文件
using namespace std;
int dd,mm,yy,bd,bm,by;
int k[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//每年每月的天数
int f(int a,int b,int c)
{
	if(c<1||b<1||b>12||c>k[b]+(b==2&&a%4==0))return 0;//排除不符合常识的
	else return ((c<=dd&&b==mm&&yy-a==18)||yy-a>18||a+18==yy&&b<mm);拍段是否满18岁
}
int main()
{
	scanf("%d.%d.%d",&dd,&mm,&yy);
	scanf("%d.%d.%d",&bd,&bm,&by);
	if(f(bm,bd,by)||f(bm,by,bd)||f(bd,bm,by)||f(bd,by,bm)||f(by,bm,bd)||f(by,bd,bm))//暴力枚举
		cout<<"YES";
	else cout<<"NO"; 
	return 0;//养成好习惯
}

```


---

## 作者：cherubim (赞：0)

~~帮忙补了手翻译，现在看起来舒服多了~~

## 题意描述

鲍勃想知道是否有可能重新排列他出生日期的数字，以便他在 $YY$ 年， $MM$ 月， $DD$ 日那天至少 $18$ 岁。

根据另一个奇怪的规则，合格的参赛者必须与决赛日期出生在同一个世纪。如果决赛当天刚好是参赛者的 $18$ 岁生日，则他可以参加。

只考虑从 $2001$ 年到 $2099$ 年的决赛年份


如果可能通过重新排列出生日期的顺序，是Bob在比赛当天至少18岁，则输出 YES 。如果不能，则输出 NO 。

## 解析

这题乍一看有点像全排列，但再仔细看下题就会发现这题本身只有三种情况，也就是说可以直接手动排列，一共只有六种情况，比较简单。

这题有两部分：判断月份是否越界和是否满足年龄达到 $18$ 岁的要求。

判断月份主要注意判断闰年时二月是否越界，其他直接数组判断大小。

年龄达到到 $18$ 岁要注意怎么判断。~~我开始写的时候甚至把判断写成了大于~~。要注意：**出生年月日越小的年龄越大**。

那么接下来时喜闻乐见的代码环节

```c
#include <bits/stdc++.h>
#define re register
#define INF 0x3fffffff
#define ll long long

using namespace std;

int DD , MM , YY ;
int BD , BM , BY ;
int mouthday[13] = { 0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } ; // 开一个数组存每一个月份的天数 

inline bool vis ( int d , int m , int y ) //判断是否符合条件 
{
	if ( m > 12 || d < 1 || y < 1 || y > 99 || d > 31 || m < 1 ) return false ; //判断是否越界 
	else if ( d > mouthday[m] && (m == 2 && y % 4 != 0 )) return false ;//越界 
	else if( m == 2 && !y%4 && d > 29 )return false; //2月单独计算闰年 
	
	//判断是否符合岁数要求 
	if ( YY - y > 18 ) return true ;
	else if ( YY - y == 18 && m < MM ) return true ;
	else if (  YY - y == 18 && m == MM && d <= DD ) return true ;
	else return false ;
}
int main()
{
	//用scanf省去string读入再提取数的烦恼~ 
	scanf ( "%d.%d.%d" , &DD , &MM , &YY ) ; 	
	scanf ( "%d.%d.%d" , &BD , &BM , &BY ) ; 
	
	//开始枚举 
	if ( vis ( BD , BM , BY ) == true ) printf ( "YES" ) ; 
	else if ( vis ( BD , BY , BM ) == true ) printf ( "YES" ) ; 
	else if ( vis ( BM , BY , BD ) == true ) printf ( "YES" ) ; 
	else if ( vis ( BM , BD , BY ) == true ) printf ( "YES" ) ; 
	else if ( vis ( BY , BM , BD ) == true ) printf ( "YES" ) ; 
	else if ( vis ( BY , BD , BM ) == true ) printf ( "YES" ) ; 
	else printf ( "NO" ) ;
	
	return 0 ;
}


```





---

## 作者：Timon080923 (赞：0)

1.穷举每一种情况  
2.判断日期是否合法  
3.判断选手是否满18岁
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,m,y,day[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//day数组为每个月的天数
bool f(int o,int p,int q){
	if(o<1||o>day[p]+(q%4==0&&p==2)||p<1||p>12)return 0;//判断日期是否合法
	return (q+18<y||(q+18==y&&p<m)||(q+18==y&&p==m&&o<=d));//判断是否有18周岁
}
int main(){
	scanf("%d.%d.%d\n%d.%d.%d",&d,&m,&y,&a,&b,&c);//格式化输入
	if(f(a,b,c)||f(a,c,b)||f(b,a,c)||f(b,c,a)||f(c,a,b)||f(c,b,a))puts("YES");//穷举所有情况
	else puts("NO");
	return 0; 
}
```

---

