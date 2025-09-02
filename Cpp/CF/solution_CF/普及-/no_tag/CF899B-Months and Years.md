# Months and Years

## 题目描述

Everybody in Russia uses Gregorian calendar. In this calendar there are $ 31 $ days in January, $ 28 $ or $ 29 $ days in February (depending on whether the year is leap or not), $ 31 $ days in March, $ 30 $ days in April, $ 31 $ days in May, $ 30 $ in June, $ 31 $ in July, $ 31 $ in August, $ 30 $ in September, $ 31 $ in October, $ 30 $ in November, $ 31 $ in December.

A year is leap in one of two cases: either its number is divisible by $ 4 $ , but not divisible by $ 100 $ , or is divisible by $ 400 $ . For example, the following years are leap: $ 2000 $ , $ 2004 $ , but years $ 1900 $ and $ 2018 $ are not leap.

In this problem you are given $ n $ ( $ 1<=n<=24 $ ) integers $ a_{1},a_{2},...,a_{n} $ , and you have to check if these integers could be durations in days of $ n $ consecutive months, according to Gregorian calendar. Note that these months could belong to several consecutive years. In other words, check if there is a month in some year, such that its duration is $ a_{1} $ days, duration of the next month is $ a_{2} $ days, and so on.

## 说明/提示

In the first example the integers can denote months July, August, September and October.

In the second example the answer is no, because there are no two consecutive months each having $ 30 $ days.

In the third example the months are: February (leap year) — March — April – May — June.

In the fourth example the number of days in the second month is $ 28 $ , so this is February. March follows February and has $ 31 $ days, but not $ 30 $ , so the answer is NO.

In the fifth example the months are: December — January — February (non-leap year).

## 样例 #1

### 输入

```
4
31 31 30 31
```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
2
30 30
```

### 输出

```
No

```

## 样例 #3

### 输入

```
5
29 31 30 31 30
```

### 输出

```
Yes

```

## 样例 #4

### 输入

```
3
31 28 30
```

### 输出

```
No

```

## 样例 #5

### 输入

```
3
31 31 28
```

### 输出

```
Yes

```

# 题解

## 作者：清小秋ovo (赞：7)

# CF899B Months and Years

[原题传送门](https://codeforces.com/problemset/problem/899/B)

[洛谷传送门](https://www.luogu.com.cn/problem/CF899B)

这可能是目前最暴力的一篇题解了。。

题目其实很简单，给出几个连续月份的天数，判断是否合法

~~好端端的一道模拟题就这么被打表暴力过了~~

不过确实，与其说写一堆复杂的判断和模拟，打表所需的代码量少之又少。

## 思路
首先自己创建好连续几年（需要包含平年和闰年的数据，因为题目中的月份数最多会达到 $24$）每个月天数的数据。

```cpp
"31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 29 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 "
```
随后，我们只需要原封不动的读入字符串，再用 `find()` 函数直接判断是否为我们提前创建好的字符串中的一个子串即可。

其实题目第一行读入的整数并没啥用。

第二行直接全行读入字符串。

完全不需要做任何的处理，直接比对，返回输出。

唯一需要注意的是，使用 `getline()` 的时候需要格外小心数据输入是否有存在回车的情况，需要加上 `cin.ignore()`。

## 前方高能，极其暴力代码
```cpp
#include<bits/stdc++.h>

using namespace std;
string b;
int main()
{
   ios::sync_with_stdio(0);
   cin.tie(0);
   int num;
   cin>>num;
   cin.ignore();
   getline(cin,b);
   string month="31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 29 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 ";
    if(month.find(b)!=string::npos){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
}

```




---

## 作者：荷叶下 (赞：3)

##### ~~又是一道带水题~~
#### 蒟蒻の第四篇题解
------------
## 思路
#### 打出每个月份的表
#### 按照平年平年闰年平年平年的顺序
#### 用string中find()函数在表中找输入的月份
------------
## 代码如下
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

namespace Heyexia
{
	typedef long long ll ;
	using std::getchar ;
	using std::putchar ; 
	using std::freopen ;
	
	using std::cin ;
	using std::cout ;
	using std::string ;
	int read_() //快读优化
	{
		int s = 0 , w = 1 ;
		char ch = getchar() ;
		while( ch == ' ' || ch == '\n' )
			ch = getchar() ;
		while( ch < '0' || ch > '9' )
		{
			if( ch == '-' )
				w = -1 ;
			ch = getchar() ;
		}
		while( ch >= '0' && ch <= '9' )
		{
			s = s * 10 + ch - '0' ;
			ch = getchar() ;
		}
		return s * w ;
	} 
	void print_( int x ) //快写优化
	{
		if( x < 0 )
		{
			x = -x ;
			putchar( '-' ) ;
		}
		if( x > 9 )
			print_( x / 10 ) ;
		putchar( x % 10 + '0' ) ;
	}
}
using namespace Heyexia ;

int n ;
string s ;
string mon = "31293130313031313031303131283130313031313031303131283130313031313031303131283130313031313031303131283130313031313031303312931303130313130313031312831303130313130313031312831303130313130313031312831303130313130313031312831303130313130313031312931303130313130313031312831303130313130313031312831303130313130313031312831303130313130313031312831303130313130313031312931303130313130313031" ;
//打表
int main()
{
    n = read_() ;
    for( int i = 1 ; i <= n ; ++i )
    {
        string s1 ;
        cin >> s1 ;
        s += s1 ; //把数入的月份连成一个字符串
    }
    if( mon.find(s) == string::npos ) //find()函数
        printf("NO") ;  //如果找不到就输出NO
    else
        printf("YES") ; //找到就输出YES
    return 0 ;
}
```
##### 共建和谐洛谷，拒绝CV


---

## 作者：artalter (赞：1)

### 题意：

**给出连续的n个月的天数，判断是否合法。**

 
### 思路
 
 首先，一眼看出，这题可以用~~带~~小模拟来做，模拟从24个月中选取n个连续月的情况，依次判断。
 
 可是，这样做代码量太大了~~我太懒了~~ ~~我太弱了~~。
 
 有没有一种好打又好理解的方法呢？
 
   **有的，这时就要用到string中的find函数了** 

 ~~string大法好~~

**我们可以打一个表，把24个月份中每一个月天数的表给打出来，然后用一个find函数判断输入是否在表中出现**。
 

------------

### 代码如下


```cpp
#include<bits/stdc++.h>//万能头大法好
using namespace std;
string a="312831303130313130313031312831303130313130313031312931303130313130313031312831303130313130313031312831303130313130313031";//注意 24个月份的情况可能是 闰平 平闰  平平 连在一起就是 平 平 闰 平 平
int main()
{
    int n;
    cin>>n;
    string b="";
    for(int i=1;i<=n;i++)
    {
        string s;
        cin>>s;
        b+=s;
    }
    if(a.find(b)!=string::npos)//判断是否在表中出现过
    {
        cout<<"Yes";
    }else
    {
        cout<<"No";
    }
    return 0;
}
```

~~蒟蒻的第一篇题解，求过~~

---

## 作者：makerlife (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF899B) | [CF原题传送门](http://codeforces.com/problemset/problem/899/B)

------------

这个题是让求输入的连续几个月份是否合法。

**直接模拟就行了吧**。

**需要注意闰年的情况**。

## 大体思路

先打表确定每个月的天数，因为有 $24$ 个月，所以需要**注意包含平年和闰年的全部情况**。

因为输入是带有空格的，所以预先打表的月份天数之间也要**带有空格**，我们可以按照 _平年、平年、闰年、平年、平年_ 的顺序预打表。

大概是这个样子：

```cpp
//             |平年-------------------------------|平年-------------------------------|闰年-------------------------------|平年--------------------------------|平年-------------------------------
string sample="31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 29 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 ";
```

读入每个月份时，需要用字符串，注意**有空格**，所以要用 `getline` ，但如使用 `scanf` 读入的 $n$，需要用 `getchar();` **吞上一行的回车**。

输入字符串时，无需进行任何操作。读完后，直接使用 `sample.find(s)` 查找。

## 完整代码

```cpp
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
//             |平年-------------------------------|平年-------------------------------|闰年-------------------------------|平年-------------------------------|平年------------------------------
string sample="31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 29 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 ";
int n;
string s;
int main()
{
	scanf("%d",&n);
	getchar();//吞n后面的回车
	getline(cin,s);//读入一整行（包括空格，但不包括回车）
	if(sample.find(s)!=string::npos)//判断是否合法
	{
		cout<<"Yes"<<endl;
	}
	else
	{
		cout<<"No"<<endl;
	}
	return 0;
}
```


---

## 作者：20100202w (赞：0)

这道题是一道**打表题**。

主要需要打表的是月份。

只要再加上暴力和细心，就能过了。

```cpp
#include<iostream>
#include<cstdio>//头文件
using namespace std;
string a="",b,s="312831303130313130313031312831303130313130313031312931303130313130313031312831303130313130313031312831303130313130313031";//平平闰平平
int main()
{
	int n;// n 个月份
	scanf("%d",&n);//输入
	for(int i=1;i<=n;i++)
	{
		cin>>b;
		a+=b; // string 类型可以加减
	}
	if(s.find(a)!=string::npos)//判断是否为子串
   	   printf("YES");
	else printf("NO");//输出
	return 0;//养成好习惯
}

```


---

## 作者：nanatsuhi (赞：0)

这道题我的第一思路，就是打一个月份的区间，然后只要把题目给的月份序列在里面比一比就好了。

很容易就能构造出以下的区间，包括所有的长度为24个月及以内的序列：

-  _平年+平年+闰年+平年+平年_ 

~~但是我不会证明~~

出于人类天性的懒惰，我不愿意打所有的月份日期~~逗号太多~~。

于是我想到了伟大的字符串。字符串可以~~省逗号~~进行查询连续子串是否存在的操作。

方式：

```cpp
//假设要从sol里找s
sol.find(s)==sol.npos
//有，返回 ture ; 无，返回 false
```

然后，目标是把两位数的日期压缩到1个字符。

解决操作：mod 10 ~~太水了~~

综上，上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a;  //  |平         |平         |闰         |平         |平 
string s,sol="181010110101181010110101191010110101181010110101181010110101"; //月份字符串  
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&a);
		s+=a%10+'0'; //将这个月加入到月份序列中 
	}
	puts(sol.find(s)==sol.npos?"No\n":"Yes\n"); // 判断是否存在 
	return 0;
}
```
短小精悍 =)

---

## 作者：䒛夢 (赞：0)


这题我开始的时候真的很崩溃，一点思路也没有
但当看到同学的[南蛮图腾](https://www.luogu
.com.cn/problem/P1498)后，我瞬间觉得我又行
了，这种题你是可以用打表的，虽然不能判断n但
我们知道它的范围才是1~24，这么小的数据不打
表你对得起自己吗？

好了,不废话了，这道题的大概意思就是给你n个月份，让你判断它合不合法。

------------

```
因为四年才有一个leap年，所以把每一种可能都列出来
这还是我看楼上的大佬才想到的方法
const int mon1[] = {0 , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31  , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
const int mon2[] = {0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31  , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
const int mon3[] = {0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31  , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
const int mon4[] = {0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31  , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
```

------------



```
for(int i=1 ; i<=24 ; ++i)//然后因为只有24，所以我们也最后到24
	{
		bool v=true;//判断他是不是合法
		for(int j=1 ; j<=n ; ++j)
		{
			if(a[j]!=mon[+j-1])//这里把每一个数组都来一遍
			v=false;
		}
		if(v==true)
		{
			printf("Yes");
			return 0;
            //合法就直接输出
		}
	}
    
.......

printf("No");
//如果不行就输出No


```


------------

上最后代码
```
#include<iostream>
#include<cstdio>
using namespace std;
int n,a[30];
const int mon1[] = {0 , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31  , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
const int mon2[] = {0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31  , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
const int mon3[] = {0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31  , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
const int mon4[] = {0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31   , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31  , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
int main()
{
	scanf("%d",&n);
	for(int i=1 ; i<=n ; ++i)
		scanf("%d",&a[i]);
	for(int i=1 ; i<=24 ; ++i)
	{
		bool v=true;
		for(int j=1 ; j<=n ; ++j)
		{
			if(a[j]!=mon1[i+j-1])
			v=false;
		}
		if(v==true)
		{
			printf("Yes");
			return 0;
		}
	}
	for(int i=1 ; i<=24 ; ++i)
	{
		bool v=true;
		for(int j=1 ; j<=n ; ++j)
		{
			if(a[j]!=mon2[i+j-1])
			v=false;
		}
		if(v==true)
		{
			printf("Yes");
			return 0;
		}
	}
	for(int i=1 ; i<=24 ; ++i)
	{
		bool v=true;
		for(int j=1 ; j<=n ; ++j)
		{
			if(a[j]!=mon3[i+j-1])
			v=false;
		}
		if(v==true)
		{
			printf("Yes");
			return 0;
		}
	}
	for(int i=1 ; i<=24 ; ++i)
	{
		bool v=true;
		for(int j=1 ; j<=n ; ++j)
		{
			if(a[j]!=mon4[i+j-1])
			v=false;
		}
		if(v==true)
		{
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0;
}


---

