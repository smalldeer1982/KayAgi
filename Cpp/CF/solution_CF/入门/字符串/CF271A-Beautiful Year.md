# Beautiful Year

## 题目描述

It seems like the year of 2013 came only yesterday. Do you know a curious fact? The year of 2013 is the first year after the old 1987 with only distinct digits.

Now you are suggested to solve the following problem: given a year number, find the minimum year number which is strictly larger than the given one and has only distinct digits.

## 样例 #1

### 输入

```
1987
```

### 输出

```
2013
```

## 样例 #2

### 输入

```
2013
```

### 输出

```
2014
```

# 题解

## 作者：HikariForever (赞：7)

这道题使用stringstream超级简单的，每次将年份n++，然后再把各位数字提取出来进行判断就可以了。下面是代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    while(1)
    {
        n++;
        stringstream box;//存储年份
        box<<n;//将n放入stringstream中
        char n1[5];
        box>>n1;//取出stringstream中的值
        if(n1[0]!=n1[1]&&n1[0]!=n1[2]&&n1[0]!=n1[3]&&n1[1]!=n1[2]&&n1[1]!=n1[3]&&n1[2]!=n1[3])//对各位数字进行判断是否相同
        {
            cout<<n<<endl;//如果相同就输出
            return 0;
        }
    }
    return 0;
}
```
下面再附上一个不用stringstream的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    while(1)
    {
        n++;
        char a,b,c,d;
        a=n%10;
        b=n/10%10;
        c=n/100%10;
        d=n/1000%10;//分离位数
        if(a!=b&&a!=c&&a!=d&&b!=c&&b!=d&&c!=d)//进行判断
        {
            cout<<n<<endl;输出
            return 0;
        }
    }
    return 0;
}
```
是不是很简单？

---

## 作者：醉梦未苏 (赞：3)

从$n+1$开始，一位一位**枚举**（别担心，不会TLE）

将枚举的数转化为字符串，单个单个比较

~~暴力AK~~

```python
#输入
n=int(input())
n=n+1
#开始枚举
while 1==1:
	#将n转化为字符串更方便
    s=str(n)
    #各位是否相等
    if(s[0]!=s[1] 
       and s[2]!=s[3] 
       and s[0]!=s[2] 	   
       and s[0]!=s[3] 
       and s[1]!=s[2] 
       and s[1]!=s[3]):
       #满足条件，输出，并退出循环
        print (n)
        break
    else:
    	#否则继续枚举
        n=n+1

```

---

## 作者：未来miss (赞：1)

看了大佬自称“简单”的程序，我想说简单个*啊！！！
---
真的看不懂大佬的程序
---
程序简单粗暴，大家look look
--
```pascal
var n,i,j:longint;
s:string;
begin
read(n);
for i:=n+1 to n+1000 do//暴力，我就不信一千年以后还找不到。
begin
str(i,s);//数字转字符
if (s[1]<>s[2])and(s[2]<>s[3])and(s[3]<>s[4])and(s[1]<>s[3])and(s[1]<>s[4])and(s[2]<>s[4]) then begin write(i); halt; end;//很长的判断
end;
end.
```
一提交看到了只有一个测试点？？？
---
我打了一大段的程序你就让我看这个？？？
--
好，简化程序
---
```pascal
begin
write(2013);//简单＆粗暴
end;
```
宝宝的代码写完了，各位努力努力。
--
加油！！ＡＣ，不灭的信仰！！　
--



---

## 作者：ShineEternal (赞：1)

```cpp
#include<cstdio>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);//输入
	for(int i=n+1;;i++)//从下一年开始循环，一直+1，直到找到答案
	{
		int j=i;
		int a=j%10;
		j=j/10;
		int b=j%10;
		j=j/10;
		int c=j%10;
		j=j/10;
		int d=j%10;//abcd分别代表了从个位到千位
		if(a!=b&&b!=c&&c!=d&&b!=d&&a!=d&&a!=c)
		{
			printf("%d\n",i);
			return 0;
		}//判断各个数位都不相同，输出返回
	}
	return 0;
}
```

---

## 作者：Palind_Rome (赞：1)

本蒟蒻直接暴力对数据扒皮。
```cpp
#include<bits/stdc++.h>
using namespace std;
int book[10];//不写10初始化似乎过不去
int main(){
	int n,i,t;
	bool f;
	cin>>n;
	while(n++){
		t=n;
		f=0;
		memset(book,0,sizeof(book));//均为初始化
		while(t!=0){//《水浒传》中的扒皮岗
			book[t%10]++;
			t/=10;
		}
		for(i=0;i<=9;i++)
			if(book[i]>1)f=1;//大于1的就重复了
		if(f)continue;
		break;
	}
	cout<<n;
    return 0;
}
```

---

## 作者：wky32768 (赞：1)

题目大意是让你找出第一个大于n的四位数子各不相同的年份，直接模拟即可。
我用a,b,c,d存这四位数字，比较笨。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,c,d,n;
int main(){
    cin>>n;
    n++;
    for(;;n++){
        a=n/1000;
        b=(n%1000)/100;
        c=(n%100)/10;
        d=n%10;
        if(a!=b&&b!=c&&c!=d&&a!=c&&a!=d&&b!=d) {cout<<n;return 0;}
    }
}
```

---

## 作者：hensier (赞：0)

这题可以建立一个$(n,10000)$循环，因为$n$和最终的数都为四位数。对于每一个数$i$，我们可以进行这样的操作：

```cpp
a=i/1000;
b=i/100%10;
c=i/10%10;
d=i%10;
//a、b、c、d分别表示千位、百位、十位、个位
```

只要$a≠b,a≠c,a≠d,b≠c,b≠d,c≠d$这六个条件同时成立，就直接输出$i$并结束程序。

$AC$代码：
```cpp
#include<cstdio>
int n,i,a,b,c,d;
int main()
{
    scanf("%d",&n);
    for(i=n+1;i<1e5;i++)//(n,1e5)循环
    {
        a=i/1000;
        b=i/100%10;
        c=i/10%10;
        d=i%10;
        if(a-b&&a-c&&a-d&&b-c&&b-d&&c-d)//x-y可以作为条件，只要非0就返回1，否则返回0
        {
            printf("%d",i);
            break;//跳出循环（可以认为直接结束程序）
        }
    }
}
```


---

## 作者：开心的猪 (赞：0)

这道题可以直接使用模拟：从那一年开始，一个一个枚举下去。

下面是代码：

```
#include<bitS/stdc++.h>

using namespace std;

int main()
{
	int y;
	scanf("%d", &y);
	for(int i=y+1; i<10000; i++)
	{
		int a=i/1000, b=i/100%10, c=i/10%10, d=i%10;
		if(a==b||a==c||a==d||b==c||b==d||c==d)
		{
			continue;
		}
		else
		{
			printf("%d", i);
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：FP·荷兰猪 (赞：0)

题意：输入y，输出第一个大于y且各个数位上的数均不相同的数。

由于y在1000到9000之间，故可以将y数位分离。又因为结果肯定是四位数，所以不用分类讨论。这样一来，打码就很简单了。

代码：
```cpp
#include <iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int g,s,b,q;
	while (1)
	{
		n++;//每次年份++
		g=n%10;//分离各位
		s=n/10%10;//分离十位
		b=n/100%10;//分离百位
		q=n/1000;//分离千位
		if (g!=s && g!=b && g!=q && s!=b && s!=q && b!=q)//判断该四位数是否各个数位上的数均不相同
		{
			cout<<n<<endl;
			return 0;//找到合法的年份是跳出while循环的惟一条件
		}
	}
	return 0;
}
```

---

## 作者：米奇奇米 (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{ 
   int n,date;//定义 
   cin>>n;
   int a,b,c,d;
   for(int date=1000;date<=10000;date++)//开始暴力枚举 
    {
    	a=date/1000;
    	b=(date/10)%10;
    	c=(date/100)%10;
    	d=date%10;//分解这个四位数 
    	if(a!=b && a!=c && a!=d && b!=c && b!=d && c!=d && date>n)//暴力判断 
    	{
    		cout<<date;//输出 
    	     break;//以输出就停下来，以输出最小值 
		}
    }
    return 0;
 } 
```
这道题目只要依据题目意思，进行暴力枚举。对这个日期四位数进行分解，按照条件，逐个进行判断。这样就可以AC。具体就看代码。

---

## 作者：meyi (赞：0)

# 一道**~~(水)~~**题
## 本蒟蒻的思路是枚举每一位数字，不过用了很多位运算
## 接下来上代码:
```cpp
#include<cstdio>
main(){
	int a=getchar()^48,b=getchar()^48,c=getchar()^48,d=(getchar()^48)+1;
    //读入每一位数字，d+1是为了从题目中输入的y+1开始枚举。
    //以上的x^y等同于x-y,以下的x^y等同于x!=y。
	for(;a^10;++a){
		for(;b^10;++b){
			for(;c^10;++c){
				for(;d^10;++d)
					if(a^b&&a^c&&a^d&&b^c&&b^d&&c^d)
						return putchar(a|48),putchar(b|48),putchar(c|48),putchar(d|48),0;
                        //这里的x|y等同于x+y
				d=0;
                //为下一次的循环将d初始化为零
			}
			c=0;
            //为下一次的循环将c初始化为零
		}
		b=0;
        //为下一次的循环将b初始化为零
	}
}
```

---

## 作者：灵小沙 (赞：0)

	//这是我见过最谁（水）的一道题 （除P1000，P1001，P1008） 
	#include<bits/stdc++.h>
	#include<string>
	#include<iostream>	
	#include<cmath>
	#include<set>
	#include<stack>
	#include<queue>
	using namespace std;
	int a[10];
	int main()
	{
		int i,n,t,b,k,f;
		cin>>n;//输入 
		i=n+1;//必须要比n大1。 
		while(f==0)//死循环 
		{
			f=1;//开 
			for(k=0;k<10;k++) a[k]=0;
			t=i;//替身变量，要不然会拆散i。 
			while(t!=0)
			{
				b=t%10;//取
				a[b]++;//桶排
				t/=10;	
			}
			for(k=0;k<10;k++) 
			{
				if(a[k]>=2)//如果多，就跳出。 
				{
					f=0;break;//关掉开关 
				}  
			}
			if(f==1) 
			{
				cout<<i<<endl;//输出 
			}
			i++; 
		}
		return 0;
	}


---

