# 2月29日

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-quala/tasks/code_festival_qualA_c

高橋君は、西暦 $ A $ 年の元旦に地球で生まれ、 西暦 $ B $ 年の大晦日に地球を去る予定です。

高橋君は、 地球で何回 $ 2 $ 月 $ 29 $ 日を過ごせるかを調べようと思いました。

$ 2 $ 月 $ 29 $ 日があるのはうるう年だけであり、うるう年であるかどうかは、以下のルールで決定されます。

- 西暦年が $ 4 $ で割り切れる年はうるう年である。
- ただし、西暦年が $ 100 $ で割り切れる年はうるう年ではない。
- ただし、西暦年が $ 400 $ で割り切れる年はうるう年である。

高橋君が、 $ 2 $ 月 $ 29 $ 日を過ごせる回数を出力してください。なお、高橋君は非常に長生きであることがあることに注意してください。

## 说明/提示

### 部分点

- $ 1\ ≦\ A\ ≦\ B\ ≦\ 3,000 $ の全てのケースに正解すると、 $ 25 $ 点が与えられる。
- 残りの全てのケースに正解すると、さらに $ 75 $ 点が与えられる。

入力は以下の形式で標準入力から与えられる。

### Sample Explanation 1

高橋君が $ 2 $ 月 $ 29 $ 日を過ごせるのは、$ 1988 $ 年、 $ 1992 $ 年、 $ 1996 $ 年、 $ 2000 $ 年、 $ 2004 $ 年、 $ 2008 $ 年、 $ 2012 $ 年の $ 7 $ 回です。

### Sample Explanation 2

$ 1000 $ 年はうるう年ではないことに注意してください。

### Sample Explanation 3

高橋君は非常に長生きであることに注意してください。

## 样例 #1

### 输入

```
1988 2014```

### 输出

```
7```

## 样例 #2

### 输入

```
997 1003```

### 输出

```
0```

## 样例 #3

### 输入

```
1 2000000000```

### 输出

```
485000000```

# 题解

## 作者：da32s1da (赞：4)

类似前缀和的思路，读入**p,q**，算出**1~q**的，减去**1~(p-1)**的。

现在考虑怎么求**1~n**的，我们发现其中**4**的倍数有**n/4**个，而其中是**100**倍数的有**n/100**个，而其中是**400**倍数的有**n/400**个。

根据容斥原理可得：**1~n**中有**n/4-n/100+n/400**个闰年。

```
#include<cstdio>
int a,b;
inline int countLeapYear(int year){
	return year/4-year/100+year/400;
}
int main(){
	scanf("%d%d",&a,&b);
	printf("%d",countLeapYear(b)-countLeapYear(a-1));
}
```

---

## 作者：FCBM71 (赞：4)

楼下几位神犇都是暴力AC大佬，下面给大家分享一种 **0ms** AC解法:~~小学奥数解法~~

根据闰年的定义我们可以知道：第n年到第m年之间的闰年的个数为：[n,m]中四的倍数的个数 - [n,m]中100的倍数的个数 + [n,m]中400的倍数的个数。

而这三个值其实是非常好知道的。就以[n,m]中四的倍数的个数为例：    

我们只需要知道不小于n的最小的4的倍数(设为p)，以及不大于m的最大的四的倍数(设为q)。再用`((q-p)div 4)+1`（div在c++中就是 / 的意思）就可以得到答案。

--------------------
贴上代码：
```pascal
program hrn;
 var
  a,b,c,n,m:longint;
 begin
  read(n,m);
  m:=4*(m div 4);
  if n mod 4<>0 then n:=4*((n div 4)+1);
  a:=((m-n)div 4)+1;//计算四的倍数个数
  m:=100*(m div 100);
  if n mod 100<>0 then n:=100*((n div 100)+1);
  b:=((m-n)div 100)+1;//计算100的倍数个数
  m:=400*(m div 400);
  if n mod 400<>0 then n:=400*((n div 400)+1);
  c:=((m-n)div 400)+1;//计算400的倍数个数
  writeln(a-b+c);//输出答案
 end.

```

---

## 作者：Reywmp (赞：4)

题目不难，判断闰年+优化练手。

没错，暴力的话大数据会T掉。所以在不开氧气的前提下还是要做一些优化的。

先贴暴力代码...

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
int func(int y)
{
    if(y%4==0&&y%100!=0||y%4==0&&y%400==0)return 1;
    return 0;
}
int main()
{
    int a,b;
    int ans=0;
    scanf("%d%d",&a,&b);
    for(int i=a;i<=b;i++)
    {
    	if(func(i))ans++;
    }
    printf("%d\n",ans);
}
```

暴力代码很好理解，核心知识点就是闰年判断。

闰年的规律是：当前年份为4的倍数且不是100的倍数时是闰年，当前年份为400的倍数时也是闰年。简单的说，4年为闰，100时不闰，而400时复闰。

------------

那么how to optimize(优化) code(我的英语很辣鸡...)呢?

很简单：

>1.我们要先找到第一个闰年。然后将a重新赋值为这第一个闰年，注意：找到后ans要++。

>2.然后我们从第一个闰年的年份+4的那个年份开始找，这样每次i只要+=4了。

>3.然后循环时在用闰年判断函数判断，如果是，ans++

>4.最后输出即可

------------

optimized code：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
int func(int y)
{
    if(y%4==0&&y%100!=0||y%4==0&&y%400==0)return 1;
    return 0;
}
int main()
{
    int a,b;
    int ans=0;
    scanf("%d%d",&a,&b);
    for(int i=a;i<=b;i++)
    {
        if(func(i)){
            a=i+4;
            ans++;
            break;
        }
    }
    for(int i=a;i<=b;i+=4)
    {
        if(func(i)){
            ans++;
        }
    }
    printf("%d\n",ans);
}
```

> ~~继续水题解~~

---

## 作者：LJC00111 (赞：1)


水题，但要不是数据水，枚举算法会TLE


```cpp
#include<bits/stdc++.h>
using namespace std;   
int main()
{
    
    int n,m,ans=0;
    cin>>n>>m;
    for(int i=n;i<=m;i++)
    {
    	if(i%4==0&&i%100!=0||i%4==0&&i%400==0 )
    	ans++;
    }
    cout<<ans<<endl;
    return 0;

}
```

---

## 作者：char32_t (赞：0)

# 题解 AT1059 【2月29日】
------------
~~样例#3跑了12s...~~

就是判断闰年

普通年（不能被100整除的年份）能被4整除的为闰年。（如2004年就是闰年,1999年不是闰年）
世纪年（能被100整除的年份）能被400整除的是闰年。(如2000年是闰年，1900年不是闰年)

总的来说，就是四年一闰，百年不闰，四百年再闰

暴力code：
```cpp
#include<cstdio>
int count;
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i=n; i<=m; i++)
		if(i%4==0&&i%100!=0||i%4==0&&i%400==0) count++;//判断闰年 
	printf("%d\n", count);
	return 0;
}
```

---

