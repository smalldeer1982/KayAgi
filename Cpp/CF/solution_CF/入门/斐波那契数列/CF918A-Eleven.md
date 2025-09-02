# Eleven

## 题目描述

Eleven wants to choose a new name for herself. As a bunch of geeks, her friends suggested an algorithm to choose a name for her. Eleven wants her name to have exactly $ n $ characters.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF918A/bbc452c49c868a8765bf80560e629f0cebfdfc80.png)Her friend suggested that her name should only consist of uppercase and lowercase letters 'O'. More precisely, they suggested that the $ i $ -th letter of her name should be 'O' (uppercase) if $ i $ is a member of Fibonacci sequence, and 'o' (lowercase) otherwise. The letters in the name are numbered from $ 1 $ to $ n $ . Fibonacci sequence is the sequence $ f $ where

- $ f_{1}=1 $ ,
- $ f_{2}=1 $ ,
- $ f_{n}=f_{n-2}+f_{n-1} $ ( $ n>2 $ ).

As her friends are too young to know what Fibonacci sequence is, they asked you to help Eleven determine her new name.

## 样例 #1

### 输入

```
8
```

### 输出

```
OOOoOooO
```

## 样例 #2

### 输入

```
15
```

### 输出

```
OOOoOooOooooOoo
```

# 题解

## 作者：sxyugao (赞：6)

**题意**


翻译说的很明白，都已经告诉你做法了（雾）


**做法**


暴力枚举每个数，判断是不是斐波那契数，如果是输出“O”，否则输出“o”。


但是这道题之所以是普及-而不是入门难度，是因为需要掌握一个技巧：估计数据范围。


我一开始看是普及-，直接算前n个斐波那契数，于是光荣的炸int了，后来仔细看了看数据范围——n=1000？！只有30个斐波那契数在这个范围内！！所以也不需要高精度了。


下面上代码：



```cpp
#include<cstdio>
int n,f[3000]={0,1,1};
bool v[1000000]={0,1};
int main(){
    scanf("%d",&n);
    for(int i=3;i<=30;i++){
        f[i]=f[i-1]+f[i-2];
        v[f[i]]=1;
    }
    for(int i=1;i<=n;i++)
        if(v[i])putchar('O');else putchar('o');
}
```

---

## 作者：empty (赞：3)

斐波那契数＜1000的也就1,2,3,5,8,13,21,34,55,89,144,233,377,610,987这么几个数，打表即可
```cpp
#include<iostream>
using namespace std;
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<=n;i++) if(i==1 || i==2 || i==3 || i==5 || i==8 || i==13 || i==21 || i==34 || i==55 || i==89 || i==144 || i==233 || i==377 || i==610 || i==987) cout<<'O'; //打表打表
                                                                                                                                                          else cout<<'o';
 return 0;
}
```

---

## 作者：Light_Cone (赞：1)

#### **~~一看这道题没有用字符串的，我就知道我的机会来了~~**

由题意，我们要在斐波那契数列的数位上输出"O",
其它的位置输出"o"
，那么我们可以用一个now来存放当且斐波那契数列的未被走过的位置，若当前走的位置不等于斐波那契数列第一位未走过的，就输出"o"，若等于，则输出"O",再令now++。

**注意：now是从2开始的，因为f[1]=f[2]=1，为了避免重复，所以这里从2开始.**

放一下**递推式： f[n]=f[n-1]+f[n-2]**

由于第20位左右的斐波那契数已超过1000，递推只需进行到20位就可以了 ~~懒得算具体位数~~。

据此，我们可以得出一份代码:

## Code:
```cpp
#include <cstdio>
int f[10010],now=2,n;
int main()
{
//	freopen("test.txt","w",stdout);
   scanf("%d",&n);
	f[1]=1,f[2]=1;
	for(int i=3;i<=30;i++)
	f[i]=f[i-1]+f[i-2];
	for(int i=1;i<=n;i++)
	{
		if(f[now]==i)
		printf("O"),now++;
		else
		printf("o");
	}
	return 0;
}
```

正解到这里就结束了。


------------

## ~~下面是歪解~~

这道题都没有人使用字符串，所以...-->**打表**!

~~(上面的正解稍微改改就能打表了~~

------------

### **~~string大法好~~**


### 函数介绍:string的substr
调用string需要使用#include <string>~~废话~~
 
 
  
 用法：
  ```cpp
string s;
s.substr(起始位置，长度);
//用于截取字符串中的一段子串
```
由题意，**任何长度的答案都是从n=1000的答案里面截取的**，所以我们只需要把n=1000的答案打出来，再利用substr对于前n位进行截取，直接输出便为答案了。

## **Code:**
```cpp
#include <iostream>
#include <string>
using namespace std;
string s="表自己打";
int n;
int main()
{
	cin>>n;
	cout<<s.substr(0,n)<<"\n";
	return 0;
}
```
~~再水红题就没脸见人了~~

---

## 作者：nju_zdd (赞：0)

# 很水的一道题
## 要掌握的是斐波拉契递推式：a[i]=a[i-2]+a[i-1]
### 建一个标记数组 b，将满足是斐波拉契数的下标值赋为1.

$\color{red}\text{附AC代码：}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50],b[10000000];
int main(){
	long long int i,n;
	cin>>n; 
	a[1]=1;
	a[2]=1;
	b[1]=1;
	for (i=3;a[i-1]<=n;i++)
	{
		a[i]=a[i-2]+a[i-1];
		b[a[i]]=1;//将满足是斐波拉契数的下标值赋为1.
	}
	
	for (i=1;i<=n;i++)
	{
		if (b[i]==0)
		cout<<'o';//不是斐波拉契数输出'o'
		else
		cout<<'O';//是则输出'O'
	}
	return 0;
}

```
## 祝各位AC愉快

---

## 作者：一滴小水滴 (赞：0)

### ~~这道题一看到数据范围，我立刻就想到了打表~~

但是1000的范围毕竟太大了，所以连long long都装不下，只能用高精度。

然鹅，我发现其实根本不会有1000这个数据，最多也只有30！

所以，1~30的斐波那契数就可以打表出来啦
```cpp
int f[305]={0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,
2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,
                                                   514229,832040};
```

辣么既然表已经打出来了，整个代码就很好打了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
    int f[305]={0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,
    1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,
                                            317811,514229,832040};
                                      //闲着无聊开305[滑稽]
	bool a[1000000]={0,1};  //a用来判断这个数是不是斐波那契数。
	cin>>n;
	for(int i=3;i<=30;i++)
		a[f[i]]=1;  //将所有a中的斐波那契位置改为true。 
	for(int i=1;i<=n;i++)
		if(a[i])cout<<"O";
		else cout<<"o";   //从1~n不断判断，如果a中有这个数，
        				//就输出“O”，不然输出“o”。
	return 0;
}
```

### ~~打表真是个好东西...~~

---

## 作者：Happy_Dream (赞：0)

这道题数据量较小,所以可以用桶去做(用桶去记录每一个数是否是斐波那契数列上的数),具体思路:

1,把斐波那契数列求出来.

2,用桶去记录每一个数是否是斐波那契数列上的数.

3,如果是输出'O',不是输出'o'.

代码如下:
***
```cpp
#include <iostream>
using namespace std;//always
int main()//主函数
{
	int f[35],n,b[1005]={0};//开数组,F表示斐波那契上每个数的值,B是用来存储的桶
	cin>>n;
	f[0]=1;//赋初值
	f[1]=b[1]=1;//题面里已说
	for(int i=2;i<=15;i++)
	{
		f[i]=f[i-1]+f[i-2];//把斐波那契数列求出来
		b[f[i]]++;//统计一下
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i]>=1)//如果是斐波那契数列上的输出'O'
		cout<<"O";
		else//不是输出'o'
		cout<<"o";
	}
	cout<<endl;//换行
	return 0;//华华丽丽的结束	
} 
```
***
剩下就没有什么可说的了...

---

## 作者：judgejudge (赞：0)

# 近似于指针的解法
首先这是斐波那契数列，那么我们可以马上得到公式：
![](https://cdn.luogu.com.cn/upload/pic/53227.png)
而且这道题不用考虑n==0的情况，所以我想到了一种方法：

我们都知道，**斐波那契数列由前两个斐波那契数相加而成**，那么我们可以**保存两个斐波那契数**，一旦查找到一个斐波那契数，输出O且替换，不是则输出o。

重点是：**这个代码可以边判断边输出，时间复杂度挺低的！！！**

所以我们可以把它理解成下面的数组和指针：
| 1 | 2 | 3 | 4 | 5 |6  | 7 | 8 | 9 | 10 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 1 | ？ |？  | ？ |？  |？  |？  |？  | ？ |
| a | b |  |  |  |  |  |  |  |  |

当循环数组运行到3时,根据算法可以变成:
| 1 |  2| 3 |4  | 5 |6  | 7 |  8|9  | 10 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 1 |1  | ？ |？  |？  |？  |？  |？  |？  |
|  | b |a  |  |  |  |  |  |  |  |
**所以此处a和b可以理解成指针！！！**


那么就有了代码：
```cpp
#include <iostream>
using namespace std;
int main(){
	int i,j,k,n;
	int a=1,b=2;//此处我保留1和2，因为n>=2以后就可以按照规律，且比较指针数越小越好
	cin>>n;
	for(i=1;i<=n;i++){
		if(i==1||i==2)cout<<"O";//1，2可以跳过判断
		else{
			if(a+b==i){//如果是斐波那契数
				cout<<"O";
				if(a<b)a=i;
				else b=i;//判断谁小一点，小的变大的
			}
			else cout<<"o";//不是斐波那契数，输出
		}
	}
	return 0;//程序结束
}
```


---

## 作者：wushuang0828 (赞：0)

这道题先要把斐波那契数列中的数求出来，
然后做个记号，输出数输出时判断一下。
斐波那契公式
 ```pascal
  a[i]:=a[i-1]+a[i-2];
```

### **但是有坑**
具体看代码吧
```pascal
var
 n,i:longint;
 a:array[0..1001] of int64;//要用int64，要不然就会爆
 b:array[0..1001] of boolean;
begin
 readln(n);//输入n
 a[1]:=1; a[2]:=2;//斐波那契的赋初值
 b[1]:=true; b[2]:=true;//1、2做记号
 for i:=3 to n do//切记从3开始
  begin
   a[i]:=a[i-1]+a[i-2];//斐波那契公式
   b[a[i]]:=true;//做标记
   if a[i]>=n then break;//如果当前求出来的数已经大于n了，就没有必要继续求了，退出循环
  end;
 for i:=1 to n do
  if b[i] then write('O')
          else write('o');//判断是否是斐波那契中的数
end.
```

---

## 作者：Andysun06 (赞：0)

# 题解 CF918A 
------------------------------
## 思路：
### 本以为只要算出1000位斐波那契数列就可以了，可没想到光荣的RE了，上百度一查第一千位是<4.3*10^208也就是第1000个数是个209位数。>pascal就算是Qword也只有24位，最后发现斐波那契数列只有15个数小于1000。

## 做法：
### 算出斐波那契数列前十个，再循环输出就A了。

## 代码：
    var i,j,n,m:longint;
    x,z:array[1..1000]of Qword;//有1000个！
    begin
    readln(n);
     x[1]:=1;//x【1】和x【2】一定是1
     x[2]:=1;
     z[1]:=1;//x【1】和x【2】都是1，所以z【1】:=1。
     for i:=3 to 15 do//一和二都赋值过了，从3开始
      begin
       x[i]:=x[i-1]+x[i-2];//公式
       z[x[i]]:=1;
      end;
     for i:=1 to n do
      if z[i]=1 then//如果是斐波那契数
       write('O')//输出O
       else
       write('o');//输出o
    end.
## 如果有疑问在右侧留言（^_^）    

---

## 作者：Dream_It_Possible (赞：0)

此题并不需要向楼下两位一样，不需要估测大小，打表等。


**可将n开在外面，斐波拉契数列>n则停止。**

 
然后用**桶**记录一下即可，最后判断第i个数是否在**桶**中为true，是true，就输出"O",否则，输出"o"。


主程序

```cpp
long long f[10005],n;//long long ,int 无所谓
bool b[1000005];
void find()
{
    f[1]=1;
    f[2]=1;
    b[f[1]]=1;
    b[f[2]]=1;
    int i;
    for (i=3;;i++)
    {
        f[i]=f[i-1]+f[i-2];//斐波拉契数列递推公式
        b[f[i]]=1;
        if (f[i]>n)//值已经>n，停止
        break;
    }
}
int main()
{
    int i;
    cin>>n;
    find();
    for (i=1;i<=n;i++)
    {
        if (b[i]==1)//判断是不是斐波拉契数列
        cout<<"O";
        else
        cout<<"o";
    }
    return 0;
}
```

---

## 作者：Playnext (赞：0)

一道模拟题。


手算斐波那契数列，可以发现$F[16] = 987 < 1000$。


直接开个bool数组标记那些属于斐波那契数列的数。


没标记就输出o，反之输出O。


代码：


```cpp
#include <bits/stdc++.h>
using namespace std;    //BY Playnext
#define REG register
#define For(X,Y,Z) for (REG int X=Y; X<=Z; X++)
#define FOR(X,Y,Z) for (REG int X=Y; X<Z; X++)
const int MAXN=1e3+1,INF=2147483647, MOD=1000000007;

int F[] = {1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987};        //由于数据小就直接手算了
bool U[MAXN];

int main () {
//    freopen ("Input.txt", "r", stdin);
//    freopen ("Output.txt", "w",stdout);
    REG int n;    scanf ("%d",&n);
    FOR (i,0,16)    U[F[i]] = 1;    //标记
    For (i,1,n)
        putchar ((U[i] ? 'O' : 'o'));    //若U[i]为真，输出'O'
    putchar ('\n');        //换行
    return 0;
}
```

---

## 作者：追风少年σχ (赞：0)

#### 更巧妙和精妙的做法
### 看代码就知道了
```cpp
#include<cstdio>
int f[46],t[1001];//桶
int main(){
    int n;
    scanf("%d",&n);
    f[0]=f[1]=1;
    t[1]=(int)('o'-'O');
    for(int i=2;f[i-1]<=n;i++){
       f[i]=f[i-1]+f[i-2];
       t[f[i]]=t[1];
    }
    for(int i=1;i<=n;i++)
        putchar('o'-t[i]);//直接减
    return 0;
}
```
O(N)
是不是很巧妙啊？？
妹子初写题解求过啊!!!!!


---

