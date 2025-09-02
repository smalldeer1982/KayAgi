# Cracking the Code

## 题目描述

### 题意简述
给出一个五位数

我们设这个这个五位数的各个数位上的数字分别为<first digit><second digit><third digit><fourth digit><fifth digit>
  
现在我们把这个数各个数位上的数字按如下方式排列成新的数：<first digit><third digit><fifth digit><fourth digit><second digit>
  
然后我们要求其五次幂的后五个数字
  
例如对于数字12345，重新排列后得到13542，五次幂为455 422 043 125 550 171 232，输出71232

## 样例 #1

### 输入

```
12345
```

### 输出

```
71232```

# 题解

## 作者：Mine_King (赞：1)

这题直接根据题意模拟就行了。  

首先是要交换各位数字，交换数字的话，用字符多麻烦呀，为什么不能直接用数交换呢？很明显，若要把一个数字 $x$ 放在百位，那么就可以直接 $x \times 100$，其他同理。于是，根据题目要求，我们先定义一个 const 数组：
```cpp
const int a[]={0,10000,1,1000,10,100};
```
然后对于读入的数，我们用 `scanf("%1d")` 可以实现一位位读。所以处理交换的代码就是这样：
```cpp
	for(int i=1;i<=5;i++)
	{
		int num;
		scanf("%1d",&num);
		n+=num*a[i];
	}
```
接下来求幂次方，这个直接模拟或快速幂都可以，但是需要注意的是输出的时候如果不足 $5$ 位是要补 $0$ 的。那么这个我们需要用字符串之类的去搞吗？也不必，只要 `printf("%05d")` 即可。

关于上面说到的两种读入和输出方式：

- `scanf("%xd")` 就是指定读入 $x$ 位。
- `printf("%0xd")` 就是指定输出 $x$ 位，如果不足 $x$ 位则用 $0$ 补齐。

---

## 作者：3a51_ (赞：0)

### 题目大意

将 $5$ 位正整数 $\overline{abcde}$,令 $x= \overline{acedb}$，求 $x^5 \mod 100000$。

### 思路分析

大模拟。就是坑点有点多。

1. 要注意每乘一次就得取模，要不然数太大。

2. 要注意开```long long```，因为 $5$ 位 $\times$ $5$ 位会炸```int```。

3. 注意最后结果含有前导 $0$ 的情况，需要输出```0```。

### code

~~力争本题最短代码~~

```cpp
#include<iostream>
using namespace std;
int main(){
    char c1,c2,c3,c4,c5;
    cin>>c1>>c2>>c3>>c4>>c5;
    long long n,Mod=100000,a1=c1-'0',a2=c3-'0',a3=c5-'0',a4=c4-'0',a5=c2-'0';
    long long ans=a1*10000+a2*1000+a3*100+a4*10+a5,x=ans*ans%Mod*ans%Mod*ans%Mod*ans%Mod,tmp=x;//一定开long long,否则会WA on #3
    while(tmp){tmp/=10;n++;}//n记录位数
    if(x<10000) for(int i=1;i<=5-n;i++) cout<<"0";//特殊判断，否则会WA on #5
    cout<<x;
    return 0;
}
```

---

## 作者：fls233666 (赞：0)

**题目描述中说的操作步骤十分详细啊.....**

所以，**直接模拟**啊！

模拟分为两个部分：数位数字交换和幂运算

对于数字交换，我们可以使用字符串，省去复杂的取数位的运算，直接交换。

对于幂运算，因为题目最后只要输出最后5位，所以可以一边乘一边把结果$mod \ 100000$，最后得到结果

但是，最后5位**可能都是0**！！！

所以要把最后的答案再转换成字符串，然后输出。

下面看看代码：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#define MOD 100000
using namespace std;
int main(){
	string s1,s2="",ans="",tmp;
	cin>>s1;  //读入数字
  
	s1="#"+s1;//把第0位占掉
	s2+=s1[1];
	s2+=s1[3];
	s2+=s1[5];
	s2+=s1[4];
	s2+=s1[2];
  //依照题意暴力交换
  
	long long int num=0,x,i;
	for(i=0;i<s2.size();i++)
		num=num*10+(s2[i]-'0');
   //把字符串转换成数字
	for(x=num,i=1;i<5;i++)
		num=(x*num)%MOD;
  //边乘边MOD，完成幂运算
  
	for(i=1;i<=10000;i*=10){
		x=(num/i)%10;
		tmp=x+'0';
		ans=tmp+ans;
	}//转换成字符串
	cout<<ans;//输出
	return 0;
}
```


---

## 作者：张遇见 (赞：0)

这题还是比较好做的。

先按照题意重新排列一下这个数的各位，然后手动幂运算。

```cpp
#include<cstdio>
using namespace std;
const int M=100000;//模数 
int a,b,c,k=5;//k是当前的位数 
long long p=1;//五位数大了会爆int，不开long long 见祖宗.png
int main(){
	scanf("%d",&a);
	while(a>0){
		c=a%10;
		a/=10;
		switch(k){ //判断当前选的第几位，然后依照题意更换位置 
			case 5:c*=100;break;
			case 4:c*=10;break;
			case 3:c*=1000;break;
			case 1:c*=10000;break;
			default:break;
		}
		b+=c;//累加一下 
		k--;//往高位走 
	}
	for(int i=1;i<=5;i++){
		p*=b;
		p%=M;  // 
	}
	printf("%05d",p);//I'm fine.
	return 0;
}
```
最后输出结果的时候！如果答案小于5位数，一定要把前导零补上！

题目其实有写：
```
输出格式：

一行，5个数字，没有间隔符。
```

于是你需要把缺少的位用0补上，不然你会炸在第五个点上。（亲测）

---

