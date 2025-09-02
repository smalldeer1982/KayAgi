# Maximum Number

## 题目描述

Stepan has the newest electronic device with a display. Different digits can be shown on it. Each digit is shown on a seven-section indicator like it is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF774C/7e680319981615bc8164e9951beec5e830c7cca7.png)So, for example, to show the digit $ 3 $ on the display, $ 5 $ sections must be highlighted; and for the digit $ 6 $ , $ 6 $ sections must be highlighted.

The battery of the newest device allows to highlight at most $ n $ sections on the display.

Stepan wants to know the maximum possible integer number which can be shown on the display of his newest device. Your task is to determine this number. Note that this number must not contain leading zeros. Assume that the size of the display is enough to show any integer.

## 样例 #1

### 输入

```
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
7
```

# 题解

## 作者：cbyybccbyybc (赞：4)

# 其实这道题很水 
## 找规律        
~~大家一定知道，位数越多，数值越大~~          
~~且开头数值要大~~             
### 因此要用最少的火柴尽量多的位数（1的火柴最少，其次是7）        
# 于是上代码！！！
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[12]={6,2,5,5,4,5,6,3,7,6};
int main()
{
    int n;
    cin>>n;//输入火柴总数
    if(n%2!=0)//如果不能用1用尽全部火柴，就先输出7（开头越大，总数越大，7要放开头）
    {
        cout<<"7";
        n-=3;//减掉用了的火柴
    }
    while(n>0)//之后一直模拟，知道火柴不够用
    {
        cout<<"1";//输出1
        n-=2;//减掉2
    } 
    return 0;
}
```


---

## 作者：RainFestival (赞：2)

这道题怎么没人做，每人发题解！！！

我来发一篇

 首先我们可以用
 ## 常识
 
判断位数多的一定数大~~只要学过数学，都知道吧~~

而1只需两根火柴棒，所以我们全用1

## 问题 

如果总数是5这样的奇数，怎么办呢？？？？？

最后多余的一根火柴棒会很难过的

没关系，我们可以将它与任意一个1结合，变成7，然后放在首位~~谁都知道117<711~~

下面是代码：

```pascal
var n,i:longint;
begin
readln(n);
if n mod 2=1 then
begin 
write(7); 
n:=n-3;
end;
for i:=1 to n div 2 do
write(1);
writeln;//noiprp++
end.
```
时间1404ms~~pascal读入输出太慢啦~~，空间0kb,代码长度0.14kb

谢谢巨佬们的观赏

---

## 作者：CZQ_King (赞：0)

~~我的代码应该是最短的了~~

------------
思路：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF774C/7e680319981615bc8164e9951beec5e830c7cca7.png)

首先我们看一下这张图，你会发现$7$的性价比是最高的：
- $0,2,3,4,5,6$的火柴棒根数比$7$要多，但他们的数字比$7$要小，所以他们根本用不到。假如你要拼一个$2$，还不如拼一个$7$，他比$2$大而且还能省出$2$根火柴棒做别的事。
- 虽然$8,9$要比$7$大，但是$7$可以``一个顶俩``：假如要拼一个$8$或$9$，还不如拼$77$，**位数多一位是好事**。
- 但不要以为全部拼$7$就是最大，当出现$77$时，我们应该拼$111$，正如上面所说，**位数多一位是好事**

是所以我们的策略是：
1. 如果$n$是奇数，那么总会剩下一个$7$，另外的$77$会变成$111$，也就是$7\underbrace{111\dots111}_{\text{(n-3)/2个1}}$
2. 如果$n$是偶数，那么全部拼$1$

看到大佬们都是用循环语句输出多个$1$的，蒟蒻这里推荐一种方法：

``string(num,char)``

这个函数（也许是函数）输出的是``num``个``char``。

例如``string(5,'1')``就是输出``11111``。

类似的在$Python$中是``print('1'*5)``。

------------
代码：
```cpp
#include<iostream>
using namespace std;main(int n){cin>>n;if(n&1)n-=3,cout<<7;cout<<string(n/2,49);}
```

---

## 作者：槑小杨 (赞：0)

$n$ 是偶数，全拆 $1$。

$n$ 是奇数，拆一个 $7$，剩下的全拆 $1$。

## code:
```
#include<iostream>
using namespace std;
int n; 
int f(int n)
{
    if(n==2)      return 1;
    else if(n==3) return 7;
    else if(n%2==0)
    {
        cout<<"1";
        return f(n-2);
    }
    else 
    {
        cout<<"7"; 
        return f(n-3);
    }
}
int main()
{
    cin>>n;
    cout<<f(n); 
    return 0;
}
```

~~(管理员大大辛苦了，求过！）~~

---

