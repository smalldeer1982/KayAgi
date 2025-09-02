# Kids' Riddle

## 题目描述

Programmers' kids solve this riddle in 5-10 minutes. How fast can you do it?

## 样例 #1

### 输入

```
11
```

### 输出

```
2
```

## 样例 #2

### 输入

```
14
```

### 输出

```
0
```

## 样例 #3

### 输入

```
61441
```

### 输出

```
2
```

## 样例 #4

### 输入

```
571576
```

### 输出

```
10
```

## 样例 #5

### 输入

```
2128506
```

### 输出

```
3
```

# 题解

## 作者：lycx03 (赞：5)

### 我们都知道，C++中有个函数叫 sprintf
### 于是。。。
我们先读入一个十进制整数n；
```cpp
cin>>n;
```
然后定义一个char数组，使用
```cpp
sprintf(s,"%X",n);
```

这就意味着我们将这个十进制数n转化为了大写十六进制数（%x为小写）并存储进了字符数组s，长度
```cpp
i=strlen(s)
```
接下来for循环依据题意数圈圈就可以了^_^
### 完整代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000001];
int main()
{
	int n,v=0;
	cin>>n;
	sprintf(s,"%X",n);
	for(int i=0;i<strlen(s);i++)
	{
		if(s[i]=='0'||s[i]=='4'||s[i]=='6'||s[i]=='9'||s[i]=='A'||s[i]=='D') v++;
		else if(s[i]=='8'||s[i]=='B') v+=2;
	}
	cout<<v<<endl;
	return 0;
}
```


---

## 作者：Rainbow_qwq (赞：3)

~再发一道愚人节题目题解~

[原题](https://www.luogu.org/problem/show?pid=CF784B)

一道进制转换题。
```cpp
//根据题意打表，0-F的圈圈数。
//常量数组可自动计算大小，无需定义。
const int dic[]={1,0,0,0,1,0,1,0,2,1,1,2,0,1,0,0};
```
**接下来我提供两种解法：**

1. while循环

用循环统计16进制下的每一个数位。

注意！！要特判数字0，0单独有一个圈（我就被坑过）。
```cpp
int sum=0,n;
int main()
{
    ios::sync_with_stdio(0);//cin优化
    cin>>n;
    if(n==0)sum=1;		//特判数字0
    while(n)			//0在这里直接跳过循环
    {
        sum+=dic[n%16];//16进制数字末位的圆圈数量
        n/=16;
    }
    cout<<sum;
    return 0;
}
```
2.递归

用函数进行递归,写起来更简便。

这里要特判16。
16=16进制下“10”,有一个圈。

```cpp
int sum(int n)//递归
{
	if(n<16)return dic[n];		//16进制只有一位就返回这一位上的圈数
	if(n==16)return 1;			//特判16
	return dic[n%16]+sum(n/16); //递归下一位
}
```

---

## 作者：Laser_Crystal (赞：1)

### 初中蒟蒻深夜发题解QwQ

这道题是纯模拟题，直接用一个数组a存下n的16进制下的数（不用转字符! 不用转字符!! 不用转字符!!!）

转好了以后可以设一个特判函数，用来判断有几个圈圈（或者是设一个数组）

注：两种方法我都试过，都AC了

函数版：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int f(int x)//特判函数
{
	if(x==0||x==4||x==6||x==9||x==10||x==13) return 1;
	if(x==8||x==11) return 2;
	return 0;
}
int main()
{
	int n,ans=0,w=0;
	cin>>n;
	if(n==0)//我就哇在这里
	{
		cout<<1;
		return 0;
	}
	while(n>0)//转十六进制
	{
		a[w]=n%16;
		n/=16;
		w++;
	}
	for(int i=0;i<w;i++) ans+=f(a[i]);//计算
	cout<<ans;
	return 0;
}
```
数组版：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int k[16]={1,0,0,0,1,0,1,0,2,1,1,2,0,1,0,0};//zhe这就是数组
int main()
{
	int n,ans=0,w=0;
	cin>>n;
	if(n==0)
	{
		cout<<1;
		return 0;
	}
	while(n>0)//转十六进制
	{
		a[w]=n%16;
		n/=16;
		w++;
	}
	for(int i=0;i<w;i++) ans+=k[a[i]];//QwQ只不过计算方式换了换
	cout<<ans;
	return 0;
}
```
管理大大看在《~~未成年保护法~~》的份上让窝过吧QwQ

---

## 作者：wpy233 (赞：1)

果然。果然。。果然是CF的愚人节~~水题~~。。。

__先来说说这题的整体思路:__

__①定义并输入变量，n和计数变量ans；__

__②核心部分，记得加上特判n==0；__
```
一、若n=0,直接输出1，终止程序；

二、若n!=0，while循环，每次/16，除到n<=0为止；
```
__③在核心部分中判断，注意加上字母的坑；__

④提交！

⑤AC！
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int ans;//定义计数变量
int main()
{
    int n;
    cin>>n;//输入
    if(n==0)//特判n=0
    {
    	cout<<1<<endl;
    	exit(0);//输出并终止程序
	}
	while(n>0)//while核心循环
	{
		int s=n%16;
		if(s==0||s==4||s==6||s==9||s==10||s==13)
			ans++;//判断只有一个圈
		else if(s==8||s==11)
			ans+=2;//判断有两个圈
		n/=16;//注意一定要加上n/16
	}
	cout<<ans<<endl;//输出
    return 0;
}
```

---

## 作者：PC_DOS (赞：1)

这题似乎是一道经典坑人题目的变体，原题是:

>已知2634=1、0000=4、8965=4、7963=2、8888=8、2473=0、9588=5、7836=3。

>请问:2489=?

>答案：这道题应该给幼儿园小朋友做，这是数圈圈题，“6”有1个圈，“8”有2个圈...“2489”共有3个圈，所以等于3。

然后本题将其升级为:输入一个十进制数，将其转化为十六进制之后数圈圈!

注意:

十六进制数字0、4、6、9、A、D各有一个圈。

十六进制数字8、B各有两个圈。

其他十六进制数字没有圈。

原题内容参考自 https://gl.baidu.com/view/4bec7d53240c844768eaee0f

思路参考自 http://www.cnblogs.com/shinianhuanniyijuhaojiubujian/p/7265135.html

代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
string strReverse(string strOrigin){ //字符串反转函数
	long long i;
	string ans;
	for (i = strOrigin.length() - 1; i >= 0; --i) ans += strOrigin[i];
	return ans;
}
string ToRadix(long long iOrig, int iRadixTarget){ //将一个数转化为2~36进制的函数
	if (iRadixTarget == 10)
		return to_string(iOrig);
	if (iRadixTarget <= 1 || iRadixTarget > 36)
		return "";
	string ans("");
	long long i, iTemp;
	char arrSeed[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	i = iOrig%iRadixTarget;
	iTemp = iOrig / iRadixTarget;
	while (iTemp != 0){
		if (i < 10)
			ans += to_string(i);
		else
			ans += arrSeed[i - 10];
		i = iTemp%iRadixTarget;
		iTemp = iTemp / iRadixTarget;
	}
	if (i < 10)
		ans += to_string(i);
	else
		ans += arrSeed[i - 10];
	return strReverse(ans);
}
int main(){
	ios::sync_with_stdio(false);
	long long iNum,i,nCountCircles=0; //iNum-原始的十进制数，i-循环变量，nCountCircles-有多少个圈圈
	string sHex; //存放十六进制数
	cin >> iNum; //输入
	sHex = ToRadix(iNum, 16); //转换为16进制
	for (i = 0; i <= sHex.length() - 1; ++i){ //把转换好的十六进制数从头到尾走一遍，数圈圈
    	/*
    		十六进制数字0、4、6、9、A、D各有一个圈。
			十六进制数字8、B各有两个圈。
			其他十六进制数字没有圈。
    	*/
		switch (sHex[i]){
		case '0':
			nCountCircles += 1;
			break;
		case '4':
			nCountCircles += 1;
			break;
		case '6':
			nCountCircles += 1;
			break;
		case '8':
			nCountCircles += 2;
			break;
		case '9':
			nCountCircles += 1;
			break;
		case 'A':
			nCountCircles += 1;
			break;
		case 'B':
			nCountCircles += 2;
			break;
		case 'D':
			nCountCircles += 1;
			break;
		}
	}
	cout << nCountCircles; //输出圈的个数
	return 0; //告辞
}
```

---

## 作者：konglk (赞：0)

把一个数转换为其他进制可以使用“短除法”，我的方法就是基于这个的。又因为这道题并不要求输出十六进制下的数，所以并不用存下来，只需要数就行了。

特判：当n=0，并不是一位都没有而是有一位“0”，所有需要特判输出0

代码如下：
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,c=0,x;
	cin>>n;//要判断的数
    if(!n)//特判
    {
    cout<<"1\n";
    return 0;
    }
	while(n)
	{
		x=n%16;//除下的余数
		n/=16;//除以十六
		if(x==0||x==4||x==6||x==9||x==10||x==13)c++;
		else if(x==8||x==11)c+=2;
	}
	cout<<c<<endl;
	return 0;
 } 
```


---

## 作者：CZQ_King (赞：0)

这道题不用进制转换啊！

而且还可以练一下位运算

思路：

把$1$到$15(F)$的圈圈个数做成一个表来查询。

然后$while$循环，一直把$n$模$16$后的数的圈圈个数加上（查表）。

然后再除以$16$。

**但是!$0$需要特判。$0$会跳过$while$循环，但$0$应该是$1$，所以应该加个$if$或者预处理$ans$。**

------------
简洁的代码：
```C++
#include<cstdio>
int n,cir[]={1,0,0,0,1,0,1,0,2,1,1,2,0,1,0,0};//表
int main(){
	scanf("%d",&n);
	int ans=!n;//预处理ans，如果n是0那么!n是1，否则是0
	while(n){
		ans+=cir[n&15];//位运算，n&15等价于n%16。
		n>>=4;//等价于n/=16
	}
	printf("%d",ans);
}
```

---

## 作者：B_lhx (赞：0)

[CF784B Kids' Riddle](https://www.luogu.com.cn/problem/CF784B)
==
思路：
--
先输入一个十进制数，再把他转换成十六进制，注意：由于不用输出这个十六进制数，可以用数组。
```
#include<bits/stdc++.h> 
using namespace std;
 
int main() 
{
    long long k,o=0;//一个十进制数k与遍历用的o
    int s[100000],c=0;//十六进制数组s与计数器c
    cin>>k;//输入这个十进制数
    if(k==0){//如果k是0，十六进制也是0，所以输出1（有一个圈）
        cout<<1;
        return 0;//直接退出
    }
    while(k>0){//转换成十六进制
        s[o]=k%16;//计算每一项
        o++;//遍历器++
        k/=16;//下一项
    }
    for(int i=o-1;i>=0;i--){//遍历每一位数
    	if(s[i]==0||s[i]==4||s[i]==6||s[i]==9||s[i]==10||s[i]==13){//如果是‘0’‘4’‘6’‘9’‘A’‘D’
    		c++;//加上1（一个圈）
	}
	if(s[i]==8||s[i]==11){//如果是‘8’或‘B’
    		c+=2;//加上2（两个圈）
	}
    }
    cout<<c;//输出
    return 0;
}
```
不抄题解是洛谷人民的传统美德，请学习思路而不是抄袭

---

