# Wrong Subtraction

## 题目描述

Little girl Tanya is learning how to decrease a number by one, but she does it wrong with a number consisting of two or more digits. Tanya subtracts one from a number by the following algorithm:

- if the last digit of the number is non-zero, she decreases the number by one;
- if the last digit of the number is zero, she divides the number by 10 (i.e. removes the last digit).

You are given an integer number $ n $ . Tanya will subtract one from it $ k $ times. Your task is to print the result after all $ k $ subtractions.

It is guaranteed that the result will be positive integer number.

## 说明/提示

The first example corresponds to the following sequence: $ 512 \rightarrow 511 \rightarrow 510 \rightarrow 51 \rightarrow 50 $ .

## 样例 #1

### 输入

```
512 4
```

### 输出

```
50
```

## 样例 #2

### 输入

```
1000000000 9
```

### 输出

```
1
```

# 题解

## 作者：引领天下 (赞：7)

这题很简单啊怎么没人做？

直接按题目说的模拟就行了。

代码：

```cpp
#include <cstdio>
long long n,k;
int main(void){    
    scanf ("%d%d",&n,&k);   
    while (k--)if (n%10)n--;else n/=10;//模拟  
    printf ("%lld",n);//输出
}
```

---

## 作者：666yuchen (赞：5)

### 一道水题，二话不说上代码:
```cpp
//666yuchen
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>//文件头
#define ss string
#define ii int
using namespace std;
ss st;
ii n;//定义
int main()
{
  cin>>st>>n;//输入
  for(int i=1;i<=n;i++)
  {
  	if(st[st.size()-1]=='0')st.erase(st.size()-1,1);
      //依照题目所说，这个数最后一位为0，则删去最后一位。
  	else st[st.size()-1]--;
      //依照题目所说，这个数最后一位不是0，则把最后一位上的数-1。
  }
  cout<<st;//输出
  return 0;//程序拜拜
}
```
### 为了营造美好的洛谷，请不要抄袭!!!

---

## 作者：thename (赞：3)

水水的一道题（本题解适合萌新食用，大佬勿喷）

本题讲了题意，非常清楚，在这里本人就不做特殊说明了

我分为三部分来做此题：

**一、输入部分，输入计算所需值（~~废话，各位大佬可以无视~~）**

```
	cin>>n>>k;//输入计算所需值 
```

**二、遍历计算部分，从k开始计算**

```
	for(;k>0;k--)//从k到0开始遍历 
	{
		if(n%10==0)//如果个位数是零 
		{
			n/=10;//原数除以十 
			continue;//跳过本层循环，避免走下条语句 
		}
		n--;//如果不为零，n-1 
	}
```

**三、输出部分，输出最后得数（~~废话，各位大佬可以无视~~）**

```
	cout<<n<<endl;//输出最后结果 
```

最后贴上本人代码

```
#include<iostream>
using namespace std;
int a,n,k;
int main()
{
	cin>>n>>k;//输入计算所需值 
	for(;k>0;k--)//从k到0开始遍历 
	{
		if(n%10==0)//如果个位数是零 
		{
			n/=10;//原数除以十 
			continue;//跳过本层循环，避免走下条语句 
		}
		n--;//如果不为零，n-1 
	}
	cout<<n<<endl;//输出最后结果 
	return 0;
}
```


---

## 作者：RKcer21 (赞：1)

大佬的翻译

```
已知一个数 $n$ ，你要对它进行 $k$ 次操作。对于每一次操作，如果 $n$ 的最后一位数字不为零，则将它减1，否则将它除以10（即删除最后一位数字）。

给出初始时的数 $n$ 和操作次数 $k$ ，求操作 $k$ 次后的结果。

保证结果是正整数。
```
模拟技术哪家强？
中国洛谷找科辰
```
#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
int n,k,i,j,t;
cin>>n>>k;
for (i=1; i<=k; i++)//用for执行（楼下用了while）
{
if (n%10!=0) n-=1;//按照题意模拟即可
  else n/=10;
}
cout<<n<<endl;//输出
}
```

---

## 作者：一滴小水滴 (赞：0)

这道题很简单的啊，不知道一楼为什么写的那么复杂qwq

直接用while循环暴力最后输出就可以了

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,w=0;
	char ch=0;
	ch=getchar();
	while(isdigit(ch))
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x;
}
inline void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}    //快读快写是本蒟蒻的个人习惯。
int n,k;
int main()
{
	n=read(),k=read();
	while(k--)
	{
		if(n%10)n--;
		else n/=10;
	}
	cout<<n<<endl;
	return 0;
}
```

---

## 作者：百里亦守约 (赞：0)

一篇**while**为主体的**~~（神犇）~~**可以看的懂得题目
       
       
# 题目思路：
用**while**循环，条件是记录自己做了几次，然后用 **%10** 的方法，找出个位，然后判断这个数字是否**大于0**，如果**大于零**的话那么就将这一个数**减去一**，否则就 **/10**。

**废话不多说，上代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,sum;
int main()
{
	cin>>n>>k;
	while(sum<k)
	{
	    int ge=n%10; //找个位
		if(ge>0)
	    {
		    sum++;
		    n--;
		    continue;   //做完一次就退出
		}
		if(ge==0)
		{
			sum++;
			n/=10;
			continue;    //同理
		}
	}
	cout<<n;   //输出
	return 0;
}
```



---

## 作者：moqizhu2005 (赞：0)

# 一道~~简单模拟~~（确实不难）
## 讲解和代码如下
```cpp
#include<iostream>
using namespace std;
long long n,k;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		if(n%10==0) n/=10;//取余10求最后一位
		else n--;//反之n-1
	}
	cout<<n;
	return 0;
}
```
## 像这种题都是基础题，请勿抄袭！

---

## 作者：Jinyeke (赞：0)

### 题目：已知一个数 n ，你要对它进行 k次操作。对于每一次操作，如果 n 的最后一位数字不为零，则将它减1，否则将它除以10（即删除最后一位数字）。给出初始时的数 n 和操作次数 k ，求操作 k 次后的结果。
 #### 这么淼的题竟然没有p党发题解，我这个小蒟蒻忍不住了，以下为代码（pascal）
 ```pascal
var
 n,k,i:longint;
begin
 read(n,k);
 for i:=1 to k do //直接循环，有几次循环几次
  if n mod 10<>0 then n:=n-1//判断，n的末尾如果不是0，n-1
  else n:=n div 10;//不然n除以（整除）10（即删除最后一位）
 write(n);//输出k轮之后的n
end.
```
### 共建文明洛谷，请勿Ctrl+C！



---

## 作者：ComeOver· (赞：0)

~~话说为什么没有用字符串的~~

#### 主要思路是运用类似栈的思维，用一个int变量，保存字符串的有效范围，在最后一位上按题意操作

贴代码：
```cpp
#include <iostream>
using namespace std;

int main(){
	string s;
	int n;//题目中的k
	cin>>s>>n;
	int sum=s.size()-1;//sum为有效范围，注意要-1
	for(int i=0;i<n;i++){
		if(s[sum]!='0') s[sum]=s[sum]-1;//不为零，减一
		else sum--;//为零，只需把有效范围--
	}
	for(int i=0;i<=sum;i++) cout<<s[i];//要按顺序输出
	cout<<endl;//记得换行
	return 0;
}
```

---

## 作者：Leo艾伦 (赞：0)

上代码：

```cpp
#include <bits/stdc++.h>  //万能头文件
using namespace std;
int m10ain() {
	int n, k;  //定义与读入
	cin >> n >> k;
	for (int i = 0; i < k; ++i)//循环 
    {
		if (n % 10 == 0) n /= 10; //如果成立，N=N除10
		else n--; //否则，n--
	}
	cout << n << endl; //输出
	return 0;
}
```




---

