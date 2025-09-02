# [ARC032A] ホリドッグ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc032/tasks/arc032_1

とても賢い犬であるホリドッグ(Holidog)くんは、足し算と素数判定をすることができます。 ホリドッグくんはある正整数についてそれが素数であるか尋ねられたとき、それが素数であるなら `WANWAN`、そうでなければ `BOWWOW` と吠えます。

あなたは、ホリドッグくんに $ 1 $ から $ n $ までの総和 $ 1\ +\ 2\ +\ 3\ +\ …\ +\ n $ が素数であるかどうかを尋ねました。ホリドッグくんがどう吠えたかを出力するプログラムを書いて下さい。

素数とは、$ 1 $ とその数自身以外の正整数で割り切ることが出来ない $ 2 $ 以上の正整数のことを言います。例えば $ 2 $ や $ 3 $ や $ 17 $ は素数です。$ 1 $ や $ 10 $ は素数ではありません。

## 说明/提示

### Sample Explanation 1

$ 1\ +\ 2\ =\ 3 $ であり、$ 3 $ は素数なので `WANWAN` と出力します。

### Sample Explanation 2

$ 1\ +\ 2\ +\ 3\ +\ 4\ +\ 5\ =\ 15 $ であり、$ 15\ =\ 3\ ×\ 5 $ なので、 `BOWWOW` と出力します。

### Sample Explanation 3

$ 1 $ は素数ではありません。

### Sample Explanation 4

$ 1\ +\ 2\ +\ ...\ +\ 999 $ は素数ではありません。

## 样例 #1

### 输入

```
2```

### 输出

```
WANWAN```

## 样例 #2

### 输入

```
5```

### 输出

```
BOWWOW```

## 样例 #3

### 输入

```
1```

### 输出

```
BOWWOW```

## 样例 #4

### 输入

```
999```

### 输出

```
BOWWOW```

# 题解

## 作者：珅肐 (赞：5)

看到有$O(1)$的题解，但是没有说明为什么，也没有证明其正确性

这里简单说一下

大家都知道$1+2+3+...+n=\frac {n*(n+1)}2$

那么这个数一定有$n$和$\frac {(n+1)}2$或者$\frac n2$和$n+1$这两个约数（与$n$的奇偶有关）

只有其中一个约数为$1$时才可能为质数

那$n$就只能为$1$或者$2$

$n=1$时式子结果为$1$，不是质数

那么这道题做法就显而易见

$n=2$时输出"WANWAN"，其他的输出"BOWWOW"

#### 代码奉上：
```cpp
#include<cstdio>
int main(){
	int n;scanf("%d",&n);
	puts(n==2?"WANWAN":"BOWWOW");
	return 0;
}
```

---

## 作者：幻之陨梦 (赞：3)

## 蒟蒻又来写AT题解了
### [$\color{blue}\text{AC证据}$](https://www.luogu.org/recordnew/show/19625211)
题目大概意思：输入一个n，求和1一直加到n，并且判断是不是质数,如果是质数就输出WANWAN，否则输出BOWWOW。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
bool zs(int x){//判断质数的函数
    if(x==1) return 0;//特判如果是1的话也返回假
    for(int i=2;i*i<=x;i++){
    	if(x%i==0){
        	return 0;
        }
    }
    //挨个便利尝试是否是合数，如果是就返回假
    return 1;//如果前面都没有返回，那么就返回真
}
int n,s;//定义，s为求和变量（不用long long因为不会超限）
int main(void){//我就喜欢用void
    scanf("%d",&n);//输入n
    for(int i=1;i<=n;i++) s+=i;//挨个求和
    if(zs(s)) puts("WANWAN");//如果是质数，那么输出WANWAN
    else puts("BOWWOW");//否则输出BOWWOW
    //puts大法好
}
```

---

## 作者：climax (赞：2)

这题不是很难，注释都写在代码里了，上代码：
```
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int main()
{
  int n,i,j,ans=0;
  cin>>n;//输入 
  if(n==1)//不要忘记特判1 
  {
  	cout<<"BOWWOW"<<endl;//记得换行 
  	return 0;
  }	
  for(i=1;i<=n;i++)//计算1+2+3+...+n
    ans+=i;
  for(i=2;i<=sqrt(ans);i++)//判断1+2+3+...+n的和是否为素数 
    if(ans%i==0)//如果不为素数 
	  {
	    cout<<"BOWWOW"<<endl;//输出BOWWOW，记得换行 
		return 0;	
	  }  
  cout<<"WANWAN"<<endl;//如果是素数，输出WANWAN。温馨提示：要换行 
  return 0;//结束程序  
}//做岛国题一定要换行！ 
```
### 最后一个温馨提示：做岛国题输出记得换行！

---

## 作者：Catalan1906 (赞：2)

洛谷的题解区里竟然没有O(1)做法详解……

题面就是要判断$1+2+\dots+n$是不是素数

很容易让人想到上面的式子事实上等于$n(n+1)/2$

根据质数的定义，质数只能被1和自身整除

于是我们看$n(n+1)/2$这个式子

把它拆开，变成$\frac{n}{2}\times (n + 1)$、$\frac{n + 1}{2}\times n$

都变成了乘积的形式对吧

如果和是质数的话，这两个式子中的某一个因子必然是1

于是我们解方程，得到$n=1$或$n=2$

然而$n=1$的时候和为1，不是素数

$n=2$的时候和是质数

综上所述，只有$n=2$的时候和是质数

代码略

---

## 作者：百里亦守约 (赞：0)

看来这道题没有质数表的题（ju）解（luo），我就来水（xie）一篇关于质（ju）数（ruo）表的题解。

## 过程：

### 从1加到n这个算法是高斯提出的，所以根据知识，知道高斯算法就是（1+n）* n / 2 ,所以可以根据这个算法求出了我们要判断的数是什么。然后用素数表来判断这个数是不是质数。

## 程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool x[1000005]; //因为数组有点大，所以我用了布尔类型。
int main()
{
    cin>>n;
    x[1]=x[0]=true; //根据知识可以知道1和0不是质数。
    for(int i=2;i<=1000000;i++) //随便定了一个很大的值
        if(x[i]==false) //因为前面没有筛选出这个数，所以这个数就是质数，所以再用这个质数筛出有关这个数的倍数并记住它们。
            for(int j=2;j<=1000000/i;j++) 
                x[i*j]=true; //标记
    if(x[(1+n)*n/2]==true) cout<<"BOWWOW"<<endl; //如果这个数不是质数，那么输出BOWWOW。
    else cout<<"WANWAN"<<endl; //如果这个数是质数，那么输出WANWAN。
    return 0; //结束程序
}
```



---

## 作者：Apro1066 (赞：0)

~~话说好久没写题解了，那我在开学之前写道题解增加rp。~~

本蒟蒻的主要思想就是，先按照题目要求把$1+2+...+n$的数$s$算出来，然后跑一遍欧拉筛，把$[2,n+1]$的素数筛出来（一定是$n+1$！！！）最后把$s$和筛出来的素数一一对比即可。

下面部分注释（对于欧拉筛的解释）来自于百度。

```cpp
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int n,cnt,a[200001],s;//a存素数，cnt存有（目前）多少个素数，s是1+2+...+n 
bool b[200001];//存不是素数的倍数 
int main()
{
	ios::sync_with_stdio(false);//取消与stdio的同步，会在理论上与scanf一样快
	cin.tie(0);//这也是加速的
	cout.tie(0);//这也是加速的
	register int i,j;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		s=s+i;
	}
	for(i=2;i<=n+1;i++)//到n+1！！！ 
	{
		if(b[i]==0)//如果不是目前找到的素数的倍数 
		{
			a[cnt++]=i;//那么这个就是素数 
		}
		for(j=0;j<cnt && i*a[j]<=n;j++)//i*a[j]<=n的意思是是否越界 
		{
			b[i*a[j]]=1;//这里不是用i的倍数来消去合数，而是把a里面纪录的素数，升序来当做要消去合数的最小素因子
			if(i%a[j]==0)//a[j]是最小素因子，当i=某个数*a[j+1]时会重复，所以才跳出循环
			{
				break;//欧拉筛的原理便是通过最小素因子来消除
			}
		}
	}
	for(i=0;i<n;i++)//逐个判断 
	{
		if(s==a[i])
		{
			cout<<"WANWAN"<<endl;
			return 0;
		}
	}
	cout<<"BOWWOW"<<endl;
	return 0;
}
```

---

## 作者：CZQ_King (赞：0)

## 这题居然有更好的算法

------------
做法：从$2$开始查找是否有数能整除$a(a=1+2+3+...+n=\frac{(n+1)*n}{2})$，如果有，输出$BOWWOW$，否则输出$WANWAN$。$\color{red}\text{一定要特判1}$

------------
```cpp
/*这个算法的速度比RioBlu的速度要快*/
#include<bits/stdc++.h>//头文件
using namespace std;
int n;
int pd(int a){//用个子程序算了
    if(a%2==0)return 0;//偶数就肯定不是质数了
    for(int i=3;i<=sqrt(a);i+=2)//一次加2，循环到a的平方根
        if(a%i==0)return 0;//不是质数
    if(a==1)return 0;//特判1
    return 1;//它是质数
}
int main(){
    cin>>n;
    printf("%s\n",(pd(n*(n+1)/2))?"WANWAN":"BOWWOW");//直接调用+三目运算符+输出
    return 0;//结束
}
```
然而本蒟蒻不推荐这种算法，因为还有更好的算法：
#### 本蒟蒻把$1-1000$的数都试过了$^{orz}$，唯一是质数的只有$n=2$，也就是$a=2*(2+1)/2=3$。
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int n;
int main(){
    cin>>n;
    printf("%s\n",(n==2)?"WANWAN":"BOWWOW");//只有n=2时才是质数
    return 0;//结束
}
```

---

## 作者：RioBlu (赞：0)

暴力AC

题目意思：

输入n

1+2+3+...+n是素数输出 $WANWAN$ 否则输出 $BOWWOW$
```
#include<bits/stdc++.h>
using namespace std;
long long a;
int main()
{
    cin>>a;
    a=(a*a+a)/2;
    if(a==1)
    {
    	cout<<"BOWWOW"<<endl;//这不是素数
    }
    else
    {
    	for(int s=2;s<a/2;s++)//暴力判断素数
    	{
    		if(a%s==0)
    		{
    			cout<<"BOWWOW"<<endl;//这不是素数
    			return 0;
    		}
    	}
    	cout<<"WANWAN"<<endl;//这是素数
    }
}
```

---

