# 123-sequence

## 题目描述

There is a given sequence of integers $ a_{1},a_{2},...,a_{n} $ , where every number is from 1 to 3 inclusively. You have to replace the minimum number of numbers in it so that all the numbers in the sequence are equal to each other.

## 说明/提示

In the example all the numbers equal to 1 and 3 should be replaced by 2.

## 样例 #1

### 输入

```
9
1 3 2 2 2 1 1 2 3
```

### 输出

```
5
```

# 题解

## 作者：AubRain (赞：3)

**最短代码**

直接用数组记录每个数字的出现次数，然后把所有数字都变成出现最多的那个数字

这个方法叫：**贪心**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s[4];
int main(){
	scanf("%d",&n);
	for(int x,i=1;i<=n;i++)
		scanf("%d",&x),s[x]++;
	cout<<n-max(s[1],max(s[2],s[3]));
}
```

值得注意的是，~~我用cin读入竟然TLE了~~

换成scanf就行了。

其实还可以用读入优化

附：c++读入优化代码
```cpp
inline int read()
{
    int X=0,w=0;char ch=0;
    while(!isdigit(ch))w|=ch=='-',ch=getchar();
    while(isdigit(ch))X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
```
~~不过为了压行我当然是没用读入优化~~

---

## 作者：夜枭只会舔fufu (赞：2)

da jia hao，ju ruo de di san pian ti jie lai la QWQ

说人话！！！！！

大家好，蒟蒻的第三篇题解来啦 QWQ

保持我一贯的作风——废话少说，上代码 ORZ

```
#include<iostream>//头文件（1~3行）
#include<algorithm>
#include<cstdio>
using namespace std;//命名空间
int a;//每一个1、2或3
int yi=0,er=0,san=0;//记录1,2和3的数目
int main()//主函数
{
    int n;//一共有几个数
    scanf("%d",&n);//输入不讲
    for(int i=0;i<n;i++)//循环不讲
    {
        scanf("%d",&a);//输入不讲
        if(a==1)//a是1
        {
            yi++;//记录一加1
        }
        if(a==2)//a是2
        {
            er++;//记录二加2
        }
        if(a==3)//a是3
        {
            san++;
        }
    }
    cout<<n-max(yi,max(er,san));//判断谁最大
    return 0;//结束不讲
}
```
夜空中最亮的星

能否听清

那仰望的人

心底的孤独和叹息

夜空中最亮的星

能否记起

曾与我同行

消失在风里的身影

我祈祷拥有一颗透明的心灵

和会流泪的眼睛

给我再去相信的勇气

越过谎言去拥抱你

---

## 作者：Andysun06 (赞：2)

## 蛮简单的一道题
#### 只是在三个数中判断的时候有点麻烦。。。
#### pascal题解（代码较长，大神勿喷）：
    var a,b,c,d,i:longint;//b，c，d分别用来作累加

    x,v:array[1..1000000]of integer;//10^6是1000000！
     begin
     readln(a);//输入个数
     for i:=1 to a do//输入
    begin
    read(x[i]);
    if x[i]=1 then b:=b+1//如果有1，就累加
    else
     if x[i]=2 then c:=c+1//如果有2，就累加
      else
       d:=d+1;//如果有3，累加
    end;
     if b>c then//如果b>c
      begin
       if b>d then//如果b>c也>d,b也就是最大的
    begin
     for i:=1 to a do
      if x[i]<>1 then//寻找不是1的个数，也就是要跟改的次数。
       v[1]:=v[1]+1;//累加
    writeln(v[1]);//输出v【1】
    halt;//跳出
    end
    else//否则
    begin
     for i:=1 to a do
      if x[i]<>3 then//寻找不是3的个数，也就是要跟改的次数。
       v[3]:=v[3]+1;//累加
       writeln(v[3]);
    halt;//跳出
    end;
    end
    else//否则
    begin
    if c>d then//如果c>d，c就是最大的
    begin
     for i:=1 to a do
      if x[i]<>2 then//寻找不是2的个数，也就是要跟改的次数。
       v[2]:=v[2]+1;//累加
    writeln(v[2]);//输出v【2】
    halt;//跳出
    end
    else//否则
     begin
     for i:=1 to a do
      if x[i]<>3 then//寻找不是3的个数，也就是要跟改的次数。
       v[3]:=v[3]+1;//累加
     writeln(v[3]);//输出v【3】
     halt;//跳出
     end;
    end;
    end.//结束

---

## 作者：char32_t (赞：2)

# 题解 CF52A 【123-sequence】
------------
因为需要替换尽可能少的元素，所以我们需要找到出现最多的元素，用它去替换其余两种元素。

小技巧：
- 1、统计可以使用`switch()`完成，大大减少代码量，且十分直观。
- 2、判断出现最多的元素时可以使用自定义函数完成（在这里**WA**了4次）

Code：
```cpp
#include<cstdio>
#include<iostream>
int _max(int a, int b, int c){//自定义最大值函数 
	return std::max(std::max(a, b), c);
}
int count_1=0, count_2=0, count_3=0;//三种元素对应的计数器 
int ans;
int main() {
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		int a;
		scanf("%d", &a);
		switch(a) {//使用switch()进行统计 
			case 1://元素为1时 
				count_1++;
				break;
			case 2://元素为2时 
				count_2++;
				break;
			case 3://元素为3时 
				count_3++;
				break;
		}
	}
	ans=n-_max(count_1, count_2, count_3);//需要替换的元素个数为总元素数-出现最多的元素数 
	printf("%d", ans);//输出结果 
	return 0;
}
```

---

## 作者：ljxljxljx (赞：2)

# CF52A 【123-sequence】
###### ~~水题~~
------------
核心思想: 　

一、读入;
  
二、存1,2,3出现的次数;
    
三、比出最多的,输出 (** n- **最多的次数).
      
------------
C++:
```cpp
#include<cstdio>
using namespace std;
int i,t,n,a[3];//a[3]用来存1,2,3出现的次数
int main()
{
    scanf("%d\n",&n);
    for(i=0;i<n;++i)
    {
        scanf("%d",&t);
        a[t-1]++;//逗比的省空间法
    }//读入，顺便存1,2,3出现的次数
    if(a[0]>=a[1])if(a[0]>=a[2]) printf("%d",n-a[0]);
                           else  printf("%d",n-a[2]);
             else if(a[1]>=a[2]) printf("%d",n-a[1]);
                           else  printf("%d",n-a[2]); 
    /*打表判断*/
    return 0;//结束
}
```

------------
Pascal:
```pascal
var
i,t,n:integer;
a:array[1..3]of shortint;{a用来存1,2,3出现的次数}
begin
  readln(n);
  for i:=1 to n do
    begin
      read(t);
      inc(a[t]);
    end;{读入，顺便存1,2,3出现的次数}
  if(a[1]>=a[2]) then if(a[1]>=a[3]) then 
                         begin n:=n-a[1];writeln(n); end
                                     else
                         begin n:=n-a[3];writeln(n); end
                 else if(a[2]>=a[3]) then
                         begin n:=n-a[2];writeln(n); end
                                     else
                         begin n:=n-a[3];writeln(n); end;
  (*打表判断*)
end.
```
------------
注意　Pascal if格式:
             
                    if()then if()then begin end
                                 else begin end
                        else if()then begin end
                                 else begin end;
------------
       C++ if格式:
                    
                    if()  if(){}
                          else{}
                    else  if(){}
                          else{}                      
------------

------------
对比可知　C++真的简洁。

###   完
                 

---

## 作者：FCBM71 (赞：1)

这题其实就是判断这个序列中1,2,3的个数哪个最多而已。明显是把两个相对来说数量较少的数字转化成数量更多的那个数字。

假设这之中出现次数最多的那个数字A出现了a次，第二多的B出现了b次，最少C的出现了c次。(也就是说a>=b>=c)那么如果全部转化成A,则需转换b+c次。如果全部转化成B，则需转换a+c次。如果全部转换成C,则需转换a+b次。很明显b+c<=a+c<=a+b。因此应该把两个出现次数较少的数转化成出现次数较多的数。

以样例为例。2出现了4次，1出现了3次，3出现了两次。所以答案就是2+3=5.
```pascal
program hrn;
 var
  a1,a2,a3,n,i,m:longint;
 begin
  read(n);
  for i:=1 to n do begin
   read(m);                //读入
   case m of
    1:inc(a1);
    2:inc(a2);
    3:inc(a3);              //判断是1还是2还是3，并计数
   end;
  end;
  m:=a1;
  if a2>m then m:=a2;
  if a3>m then m:=a3; //判断那个数字出现次数最多，用m存储
  write(n-m);
           //输出（用总和减去最大的m，等价于两个小的的和）
 end.
```

---

## 作者：谷民 (赞：0)

####  CF52A 【123-sequence】

本题记录1,2,3每个数的个数，输出总数n减去1,2,3数量最多的即为答案。

```
#include<bits/stdc++.h>//万能头
using namespace std;
int n,s[4];//s为记录1,2,3数量的数组
int main(){
    cin>>n;//读入
    for(int x,i=1;i<=n;i++){//记录每个数个数
        cin>>x;
        s[x]++;
    }
    cout<<n-max(s[1],max(s[2],s[3]));//输出总数n减去1,2,3数量最多的
}
```


---

## 作者：bym666 (赞：0)

# CF52A 【123-sequence】
这道题要求我们替换尽可能少的元素，如果我们要替换的尽量少，那么不替换的就要尽量多，那我们这道题就要找出最多的元素的个数。

代码如下：
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
int n,a,x,y,z,ans;
int main()
{
	cin>>n;//输入 
	for(int i=1;i<=n;i++)
	{
		cin>>a;//输入 
		if(a==1) x++;//如果输入的是1，1的个数加1 
		else if(a==2) y++;//如果输入的是2，2的个数加1 
		else z++;//如果输入的是3，3的个数加1 
	}
	ans=max(x,max(y,z));//找3个数的个数中最大的 
	ans=n-ans;//剩下的就是需要替换的个数的最小值 
	cout<<ans;//输出
	return 0;//结束程序 
}
```


---

## 作者：追风少年σχ (赞：0)

### 大家的做法还是有些啰嗦了
### 我的思路是和大家一样的，用桶记数字出现个数
```cpp
#include<cstdio>
int n,a[4],s,x,number;
int main(){
    scanf("%d",&n);
    number=n;
    while(number--){
        scanf("%d",&x);
        a[x]++;//桶
        if(a[x]>s)
           s=a[x];//每次用桶记的时候同时记录最大值。
    }
    printf("%d",n-s);//输出n减去最大值
    return 0;
}
```
### 妹子的O(n)算法题解求过啊！！！！

---

## 作者：yuangq (赞：0)

这题只需要进行累加计算即可，具体注释请看代码

说明：改的最少就是那个数最多
~~~
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,s1=0,s2=0,s3=0;//定义n和三个计数器，（记得清零记得清零记得清零）重要的事情说三遍！
	cin>>n;//输入
	for(int i=0;i<n;i++)
	{
		int a;//定义一个临时变量，用来输入
		cin>>a;//输入
		if(a==1) s1++;//如果为1,s1++
		if(a==2) s2++;//如果为2,s2++
		if(a==3) s3++;//如果为3,s3++
	}
	int k=max(max(s1,s2),s3);//因为不能将三个数直接取最大,所以要用一个简单的嵌套max进行取最大值的操作
	cout<<n-k;//只需用总数减去最大值即可
	return 0;//QwQ
}

~~~

---

## 作者：Playnext (赞：0)

这道算是数学题吧...

我们假设$1$出现$C1$次，$2$出现$C2$次，$3$出现$C3$次。

那么，把所有的数字用$1$替换需要$n-C1$次，用$2$替换需要$n-C2$次，用$3$替换需要$n-C3$次。

不难得出，替换次数最小就是要求出现次数最大的数字。

统计后取最大值即可。

------------

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;	//BY Playnext
#define REG register
#define FOR(X,Y,Z) for (REG int X=Y; X<Z; X++)

int n, C1, C2, C3, T1;

int main () {
	scanf (" %d",&n);
	FOR (i,0,n) {
		scanf (" %d", &T1);				//统计次数
				if (T1 == 1)	C1++;
		else	if (T1 == 2)	C2++;
		else					C3++;		
	}
	
	REG int Ans = C1;		//求出现最多的数字
	Ans = max (Ans, C2);
	Ans = max (Ans, C3);
		
	printf ("%d\n", n -Ans);	//输出
    return 0;
}
```

---

