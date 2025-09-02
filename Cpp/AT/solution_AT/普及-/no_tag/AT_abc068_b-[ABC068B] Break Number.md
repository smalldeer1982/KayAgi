# [ABC068B] Break Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc068/tasks/abc068_b

高橋君は $ 2 $ で割れる数が好きです。

正整数 $ N $ が与えられるので、$ 1 $ 以上 $ N $ 以下の整数のうち、最も $ 2 $ で割れる回数が多いものを求めてください。答えは必ず $ 1 $ つに定まります。

なお、$ 2 $ で割っていき、何回あまりが出ずに割れるかを、$ 2 $ で割れる回数と呼ぶことにします。

例えば

- $ 6 $ ならば、$ 6 $ -&gt; $ 3 $で、$ 1 $ 回 $ 2 $ で割れます。
- $ 8 $ ならば、$ 8 $ -&gt; $ 4 $ -&gt; $ 2 $ -&gt; $ 1 $で、$ 3 $ 回 $ 2 $ で割れます。
- $ 3 $ ならば、$ 0 $ 回 $ 2 $ で割れます。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 100 $

### Sample Explanation 1

$ 4 $ は $ 2 $ 回 $ 2 $ で割ることができ、これは $ 1 $, $ 2 $, ..., $ 7 $ の中で最も多いです。

## 样例 #1

### 输入

```
7```

### 输出

```
4```

## 样例 #2

### 输入

```
32```

### 输出

```
32```

## 样例 #3

### 输入

```
1```

### 输出

```
1```

## 样例 #4

### 输入

```
100```

### 输出

```
64```

# 题解

## 作者：emm··· (赞：3)

C++

怎么没有人暴力呢？数据范围这么小。。。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	if(n==1) printf("1\n");
	if(n>=2 && n<4) printf("2\n");
	if(n<8 && n>=4) printf("4\n");
	if(n<16 && n>=8) printf("8\n");
	if(n<32 && n>=16) printf("16\n");
	if(n<64 && n>=32) printf("32\n");
	if(n<128 && n>=64) printf("64\n");
	return 0;
}
```

---

## 作者：ACE_ZY (赞：2)

为了壮大P党 我来发pascal的题解

题目的意思是输入一个不大于100的正整数，输出小于等于它且最大的二的幂

思路是将100以内的所有2的幂给列出了 一个一个比 找到最大的

代码如下:
```pascal
var
  n,k,i,j:longint;
  a:array[0..1000] of longint;
begin
  readln(n);//那个数
  a[1]:=1;//1也是2的幂 所以将1放入a[1]
  j:=1;//j刚开始为1
  k:=1;//用来记录2的幂 初始值为1
  while k<=100 do//将小于100的2的幂给列举出来
  begin
    j:=j+1;//2的幂在数组的位置的下标
    k:=k*2;//2的幂算出来
    a[j]:=k;//放到数组里
  end;
  for i:=j downto 1 do//从大到小穷举 因为是小于n的的2的幂
  begin
    if a[i]<=n then begin write(a[i]);exit;end;//找到最大的 直接退出
  end;
end.
```

望通过 谢谢

---

## 作者：Stick_With_Mars (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT2659)

显然，这道题让我们输出小于等于n且最大的二的幂

我们不妨设$ans=2^k$

由题$2^k \le n < 2^{k+1}$

同时取对数得到 $k\le \log_{2}n <k+1$

$\therefore k=\lfloor \log_{2}n\rfloor$

因为C++中除了自然对数以外，没有以其他数为底的对数

利用换底公式 $\log_{2}n=\frac{\ln n}{\ln 2}$

$\therefore k=\lfloor \frac{\ln n}{\ln 2}\rfloor$

$ans=2^{\lfloor \frac{\ln n}{\ln 2}\rfloor}$

代码：
```cpp
#include<bits/stdc++.h>
#include<math.h>
using namespace std;
int main()
{
	double n;
	cin>>n;
	cout<<(int)pow(2,floor((log(n))/(log(2)))); 
	return 0;
}


```

---

## 作者：Confused (赞：0)

### 本以为是一道高精的题目，没想到一看数据范围:1<=N<=100,就直接枚举得答案。

### 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,i;
int main()
{
	cin>>n;
	for(i=0;i<=10;i++)
	{
		if(pow(2,i)<=n) ans=pow(2,i);
     		//pow为乘方语句，在cmath库中。
	}
	cout<<ans<<endl;
 } 
```


---

## 作者：I_will (赞：0)

我有一种与众不同（2B星球）的方法：
直接纯手打：
``
int a[129]={0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

``
接下来的你懂的。

~~本人懒得写思路，膨胀！~~

程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[129]={0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
int x;
int main()
{
	cin>>x;
	for(int i=x;i>=1;i--)
	if(a[i]==1){cout<<i<<endl;break;
	}
	
	
	return 0;
}
```


---

## 作者：青蛙王子 (赞：0)

# C++

首先设一个$i$，然后让$i$一直乘$2$（就是$2^i$），一旦$i$超出了$n$的范围，就代表$2^{i-1}$是问题的解。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,i,f;//f是标记
int main()
{
	cin>>n;
	for(i=1;i<=n;i*=2)//列举2^i
	  if(i==n)  {f=1;break;}//如果n恰好是2的i次方，就做个标记
	if(!f)
	  cout<<i/2<<endl;//这个就是2^(i-1)
	else  cout<<i<<endl;//这个就是有标记的输出
	return 0;
}
```


---

## 作者：A_Plus_Gu (赞：0)

# 方法：打表

**我为什么会想到用打表呀？**

**看数据范围！**

$ 1<=n<=100 $

### 思路：

1.先打一个100以内二的幂的表

2.输入n

3.找到并输出小于等于它且最大的二的幂

```
#include<iostream>
using namespace std;
int main(){
	long long a[8]={0,1,2,4,8,16,32,64};//打表
	long long n;
	cin>>n;//输入
	for(int i=7;i;i--){找到并输出小于等于它且最大的二的幂
		if(a[i]<=n){
			cout<<a[i]<<endl;
			return 0;//直接结束程序
		}
	}
}
```


---

## 作者：打表大蒟蒻 (赞：0)

~~众所周知，AT题库水题多~~

（拍桌子）这道题数据也太小了，起码也得到十万啊，这样才方便打表啊，100的数据范围心算就行了，简直有辱~~只会打表的~~本蒟蒻的打表水平啊！

还是算一下吧(感觉样例中已经给出了大部分)
```cpp
2^0=1;   //千万要考虑到0次方的情况！！！
2^1=2;
2^2=4;
2^3=8;
2^4=16;
2^5=32;
2^6=64;
```

接下来就可以直接写代码啦（请勿抄袭）
```cpp
#include <bits/stdc++.h>  //万能库，考试必备的大杀器
using namespace std;
int a[8]={1,2,4,8,16,32,64,101};  //把我们刚才算出的数据全部存到一个数组里去，还要再放一个101到数组里去，这样在for循环里方便比较
int main ()
{
	int n;   //定义变量
	cin>>n;   //标准蒟蒻式读入
	for(int i=0;i<7;i++)  //开始循环
		if(a[i]<=n&&a[i+1]>n)  //比较
		{
			cout<<a[i]<<"\n";  //标准蒟蒻式输出
			return 0;  //如果找到了，直接结束
		}	
}
```
顺便安利一下自己的博客（全是水题题解）  https://zhah.blog.luogu.org/#

---

## 作者：qiukaichen (赞：0)

本题就是在判断小于输入数的最大的2的次幂。那就只要用一个循环累乘2，再判断是否大于输入数就行了。代码如下：
```
#include<bits/stdc++.h>//万能库
using namespace std;
int main()
{
	long long i,sum=1,n;
	cin>>n;//输入
	for(i=1;i<=n;i++)
	{
		while(sum<=n)//判断是否小于输入数
		{
			sum=2*sum;//累乘2
			if(sum>n)
			{
				cout<<sum/2<<endl;//如果超出输入数再除回去
				return 0;//结束
			}
		}
	}
	return 0;
}
```


---

## 作者：Raw_Aya9285 (赞：0)

大水题，我用while解的（为了应付输入是int类型的所有数）：

```cpp
#include<iostream>
using namespace std;
int main(){
    int a,nd=1; //nd用来保存输出的数字
    cin>>a; //输入
    while(nd<=a){ //当2的幂不大于给出的数
        nd*=2; //就乘2
    }
    cout<<nd/2<<endl; //由于最后多乘了一次，所以除以2，记得换行
    return 0; //好习惯
}
```

完美AC。

---

## 作者：CZQ_King (赞：0)

## 怎么没有人发题解$??$
此题枚举$\le{A}$的最大二次幂即可。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
short a;//作死用short
int main(){
    cin>>a;
    for(int i=6;i>=0;i--)
        if(pow(2,i)<=a){//如果小于2的i次幂
            cout<<pow(2,i)<<endl;//输出
            return 0;//输出完就结束
        }
}
```

---

