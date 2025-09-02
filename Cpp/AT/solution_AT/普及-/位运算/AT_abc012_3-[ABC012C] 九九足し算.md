# [ABC012C] 九九足し算

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc012/tasks/abc012_3

高橋君は、先日、九九の表を全て暗記することに成功しました。

九九で物足りなくなった高橋君は、 $ 1 $ × $ 1 $ から $ 9 $ × $ 9 $ までの値を、全て足してみることにしました。

高橋君は、九九のうちの一つの答えを忘れてしまったので、その計算を後回しにして、残りの和を求めたところ、$ N $ になりました。

しかし、高橋君は、後回しにした問題がどれだか解らなくなってしまいました。

高橋君が後回しにしてしまった問題として、あり得るものを辞書順で全て出力しなさい。

## 说明/提示

### Sample Explanation 1

高橋君の求めた値は、本来の値より $ 12 $ 少ないものです。 よって、答えが $ 12 $ となる、 $ 2 $ × $ 6 $、 $ 3 $ × $ 4 $、 $ 4 $ × $ 3 $、 $ 6 $ × $ 2 $ の $ 4 $ つが答えとなります。

## 样例 #1

### 输入

```
2013```

### 输出

```
2 x 6
3 x 4
4 x 3
6 x 2```

## 样例 #2

### 输入

```
2024```

### 输出

```
1 x 1```

# 题解

## 作者：Reywmp (赞：8)

水题，~~(然而我也没一遍A,我太菜了)~~

思路很简单，二重循环找一遍，找到符合的就输出。

因为a，b<10，所以我们把a从1循环到9，b从9再循环回来，如果符合a*b==N
就输出。

>- 每次都要记得换行！

code如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    n-=2025;
    n=abs(n);//无聊用了abs()，大家都知道a-b其实等价于|b-a|
    for(int i=1;i<=9;i++)
    {
        for(int j=9;j>=1;j--)/*其实j也可以从1循环到9，我原本是想试着这样优化一下的，不过貌似没有提升效率*/
        {
            if(i*j==n){printf("%d x %d",i,j);printf("\n");}
            /*乘号在这题里就是“x”！记得换行！*/
        }
    }
    return 0;
}
```
时间复杂度自然是O(n^2);

一直在想O(n)的思路，AC后才想出来：
其实就相当于百钱百鸡的优化思路，最简单的想法是2重暴力，开始现在只需要用一重循环，然后用乘积除以第一个乘数，就可以得到另一个除数，不过要特判第二个乘数也就是b是否小于等于10，如果是，那就输出。

O(n)算法的代码就不贴了，楼下@RNG_UZI_NB dalao也是这个思路，可以看一下ta的代码。

错了一个字，修改一下，管理员大大帮忙过一下orz谢谢

---

## 作者：_Qer (赞：4)

题目看不太懂，大概意思是给你一个数$N$，让你输出$2025-N$用两个小于10的正整数的乘积表示的形式，按照字典序有多少输出多少，输出用$a$ x $b$（中间那个是小写的$X$）的形式，末尾换行。

我们可以先存下$2025-N$的值，用一个for循环找到它小于10的因子，判断其对应的另一个因子是否也满足小于10的条件，如果可以就输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a;//输入的N
int main(){
    cin>>a;
    a=2025-a;//取2025-N
    for(int i=1;i<=a&&i<10;++i){//因子要满足小于2025-N且小于10
        int j=a/i;//取对应的因子
        if(i*j==a&&j<10){//如果对应因子和这个因子都为小于10的正整数
            cout<<i<<" x "<<j<<endl;//按格式输出
        }
    }
    return 0;
}
```

---

## 作者：Jinyeke (赞：2)

### 前面的p党大佬都来了，咋能少了本小蒟蒻呢?(求过求过），以下放代码（pascal)
```pascal
var
 a,b,n,x:longint;
begin
 read(n);
 x:=2025-n;//题目要求（2025-n的值）
 for a:=0 to 9 do
  for b:=9 downto 0  do  //由于说是〈10，所以。。。暴力出奇迹，骗分过样例（滑稽） 
   if a*b=x then writeln(a,' x ',b); //有坑，乘号两边要有空格
end.
```
### 共建文明洛谷，请勿Ctrl+C！

---

## 作者：liangqiaoshen (赞：1)

好像人们的题解最优时间复杂度也就O(n)了，那我就水一发更优的吧。~~（好像这题的数据根本不用优化）~~

```cpp

#include<bits/stdc++.h>

using namespace std;
int a,l=1;
struct ans{
	int x,y;
}b[10001];
int main()
{
	cin>>a;
	a=2025-a;
	for(int i=1;i<=sqrt(a);i++)
	{
		int j=a/i;
        if(i*j==a&&j<10)
        {
        	cout<<i<<" x "<<j<<endl;
        	b[l].x=j,b[l].y=i;
        	l++;
		}
	}
	if(l%2==1)l--;
	for(;l>0;l--)
	{
		if(b[l].x!=b[l].y&&b[l].y!=0&&b[l].x!=0)
			cout<<b[l].x<<" x "<<b[l].y<<endl;
	}		
	return 0;
}

```

基本思路十分好理解：我们观察题目中的输出，可以发现其中一半的输出是另一半的倒写法，那么，我们只用求出一半，另一半直接就轻而易举地出来了（将前面输出的倒过来），根据我们打过的素数判断，只用循环sqrt(n)次就可以十分简单的A掉。


---

## 作者：meyi (赞：1)

# ~~我的代码大概是最短的了吧（笑）~~
### 思路:枚举n除以每个数字的结果，如果余数为零且商小于10则符合条件，输出。
### 贴代码：
```cpp
#include<cstdio>
main(){
	int n;
	scanf("%d",&n);
	n=2025-n;	//按照题目要求将n变为2025-n
	for(int i=1;i^10;++i)if(n%i==0&&n<i*10)printf("%d x %d\n",i,n/i);
    //i^10其实是个没（yong）有（lai）意（zhaung）义（bi）的位运算，if的条件同思路。
}
```

---

## 作者：Andysun06 (赞：1)

## 这道题并不难，很多人想多了，只要用双重循环查找，然后输出就可以了。
### 上代码：
    var n,m,i,j:integer;//integer就够了
    begin
     readln(n);//输入
      for i:=1 to 9 do//双重循环查找
       for j:=1 to 9 do
       begin
        m:i*j;
        if m=2050-n then//判断
         writeln(i,' x ',j);//输出
       end;  
    end.

---

## 作者：LDXOUN7 (赞：1)

基本思路：二重循环暴力解法
```cpp
#include"iostream"
#include"cstdio"
#include"cstdlib"
#include"algorithm"
#include"string"
#include"cstring"
#include"cmath"
using namespace std;
int main(){
    int n;
    cin>>n;//输入
    for(int a=1;a<10;a++){//由题可得：a,b均为小于10的正整数，且要按字典需输出
        for(int b=1;b<10;b++){//所以从1~9直接暴力
            if(a*b==(2025-n)){
                cout<<a<<" x "<<b<<endl;//满足乘积相等，输出
            }
        }
    }
    return 0;//记得养成好习惯
}
```
PS：本人为初学蒟蒻，不要喷......

---

## 作者：北雪2009 (赞：0)

```c
因为最近本蒟蒻的社区狂掉，所以我又来刷题解啦！
```
这道题一看它：“哇！好简单啊！简直就是入门题嘛！~”   
这道题最容易让人想到的就是————
# 暴力枚举出奇迹！！！
在暴力里面，最容易想到的当然就是用i,j两个循环变量枚举每一个数。因为题目说不能大于10，那样的话，最大也就是9\*9=81嘛！这么小，C++都不用几十毫秒就可以轻轻松松搞定它。这样的话，只要在循环里判断i\*j是否等于(2025-n）。不过，为了方便，输入完n后，我们就可以再向C++前台要一个变量sum。他的任务就是吃掉(2025-n)这个东东。   
附上代码：
```cpp
#include<iostream>    //头文件1
#include<stdio.h>     //头文件2
using namespace std;  //使用命名空间std
int n,sum;    //定义我刚刚说的那两个变量n和sum
int main(){     //开启主函数
    scanf("%d",&n);    //输入n
    sum=2025-n;    //让sum吃掉(2025-n)
    for(int i=1;i<10;i++)    //循环枚举i
    	for(int j=1;i<10;j++)    //循环枚举j
    		if(i*j==sum)    //判断相乘是否等于sum
    			printf("%d x %d\n",i,j);    //输出，记得换行
    return 0;   //结束
}   //关闭主函数
```
但是……结果就会这样：全部TLE!（说实话我都不知道怎么错惹……）   
没办法，我只能改啊改，改啊改，改完就提交，改完就提交……改到像下面这样子：
```cpp
#include<iostream>    //头文件1
#include<cstdio>     //头文件2，用于scanf和printf
#include<cmath>     //头文件3，用于abs函数
using namespace std;    //使用命名空间std
int n;     //定义n
int main(){    //开启主函数
    scanf("%d",&n);    //输入n
    n=abs(n-2025);    //求差值
  	//这里我闲来无事，用了abs函数。（谁都知道a-b=|b-a|）
    for(int i=1;i<=9;i++)   //循环枚举i
        for(int j=9;j>=1;j--)    //循环枚举j
            if(i*j==n){printf("%d x %d",i,j);printf("\n");}   //判断i*j是否等于差值。如果等于，就输出。记得换行。
    return 0;   //结束
}   //关闭主函数
```

一测，终于对了！   
当然，上面的程序时间复杂度为O(9\*9)左右。这个时间复杂度已经很低了。不过，我相信有些丧心病狂的人绝对**不满足**于此。行行行，等等哈！等我备好程序资料先……好啦！   
O(9\*9)左右确实不是最优化方法。最优化的时间复杂度仅有O(9)左右之少！不信？我来给你讲一讲：   
首先输入，然后循环。从现在开始，请注意：每次只要判断i|sum是否成立（i|sum=sum%i==0）。然后再判断(sum/i)<10是否也成立。如果两个都成立，就可以输出。   
附上代码：
```
#include<iostream>    //头文件1
#include<stdio.h>    //头文件2
using namespace std;   //使用命名空间std
int n,sum;    //定义变量n和sum
int main(){   //开启主函数
    scanf("%d",&n);   //输入n
    sum=2025-n;   //让sum把（2025-n）吞下去
    for(int i=1;i<10;i++)    //循环枚举i
    	if(sum%i==0&&sum/i<10)   //判断是否成立上述的两个条件
    		printf("%d x %d\n",i,sum/i);   //如果成立就输出
    return 0;   //结束
}   //关闭主函数
```
给个好评呗！

---

## 作者：CZQ_King (赞：0)

居然没有打表题解，蒟蒻来一发。

------------
看到$1944\le N\le2024$之后，我们先减，发现就是求$1$到$81$的数。数据不大，可以打表。

------------
表生成器：
```cpp
#include<bits/stdc++.h>
using namespace std;
main(){
	freopen("1.txt","w",stdout);//输出路径
	cout<<"string s[]={";//先输出前面
	for(int j=1;j<=81;j++){//从1到81
		cout<<"\"";//字符串的双引号
		for(int i=1;i<10;i++)
			if(j%i==0&&j/i<10)cout<<i<<" x "<<j/i<<"\\n";//输出所有可能，记住输出\\n而不是\n，否则会输出回车
		cout<<"\",";//双引号
	}
	cout<<"};";
}
```
然后去同文件夹的``1.txt``复制里面的内容即可，**注意要把最后一个逗号删掉！！**

------------
代码：
```cpp
#include<bits/stdc++.h>
std::string s[]={"1 x 1\n","1 x 2\n2 x 1\n","1 x 3\n3 x 1\n","1 x 4\n2 x 2\n4 x 1\n","1 x 5\n5 x 1\n","1 x 6\n2 x 3\n3 x 2\n6 x 1\n","1 x 7\n7 x 1\n","1 x 8\n2 x 4\n4 x 2\n8 x 1\n","1 x 9\n3 x 3\n9 x 1\n","2 x 5\n5 x 2\n","","2 x 6\n3 x 4\n4 x 3\n6 x 2\n","","2 x 7\n7 x 2\n","3 x 5\n5 x 3\n","2 x 8\n4 x 4\n8 x 2\n","","2 x 9\n3 x 6\n6 x 3\n9 x 2\n","","4 x 5\n5 x 4\n","3 x 7\n7 x 3\n","","","3 x 8\n4 x 6\n6 x 4\n8 x 3\n","5 x 5\n","","3 x 9\n9 x 3\n","4 x 7\n7 x 4\n","","5 x 6\n6 x 5\n","","4 x 8\n8 x 4\n","","","5 x 7\n7 x 5\n","4 x 9\n6 x 6\n9 x 4\n","","","","5 x 8\n8 x 5\n","","6 x 7\n7 x 6\n","","","5 x 9\n9 x 5\n","","","6 x 8\n8 x 6\n","7 x 7\n","","","","","6 x 9\n9 x 6\n","","7 x 8\n8 x 7\n","","","","","","","7 x 9\n9 x 7\n","8 x 8\n","","","","","","","","8 x 9\n9 x 8\n","","","","","","","","","9 x 9\n"};//表
main(int n){scanf("%d",&n);puts(s[2024-n].c_str());}//数组开头为0，所以要减1
```

---

## 作者：代码小白白 (赞：0)

```java
import java.util.*;
public class Main{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        int N=2025-n;
        for(int i=1;i<10;i++){
            for(int j=1;j<10;j++){
                if(i*j==N){
                    System.out.println(i+"x"+j);
                }
            }
        }
    }
}

```
刚开始的零分代码，搞得我有点懵，后来觉得可能是输出格式有问题，所以改了一下，顺利AC。下面是AC代码。
```java
import java.util.*;
public class Main{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        int N=2025-n;
        for(int i=1;i<10;i++){
            for(int j=1;j<10;j++){
                if(i*j==N){
                    System.out.println(i+" "+"x"+" "+j);
                }
            }
        }
    }
}
```
没错，就是多加个空格。大佬们不喜勿喷。

---

## 作者：远山淡影 (赞：0)

这题数据有点水，所以双重循环也能过。
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int main()
{
    scanf("%d",&n);//输入 
    n=2025-n;//因为题目要求将2025-n改写成a x b的形式 
    for(int i=1;i<10;i++)
    {
    	for(int j=1;j<10;j++)//a、b都小于10 
    	{
    		if(i*j==n)//如果两个相乘等于2025-n 
    		{
    			printf("%d x %d\n",i,j);//输出。记得注意格式。 
			}
		}
	}
    return 0;
}
```


---

