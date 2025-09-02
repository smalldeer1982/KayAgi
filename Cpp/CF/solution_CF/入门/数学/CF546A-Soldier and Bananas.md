# Soldier and Bananas

## 题目描述

A soldier wants to buy $ w $ bananas in the shop. He has to pay $ k $ dollars for the first banana, $ 2k $ dollars for the second one and so on (in other words, he has to pay $ i·k $ dollars for the $ i $ -th banana).

He has $ n $ dollars. How many dollars does he have to borrow from his friend soldier to buy $ w $ bananas?

## 样例 #1

### 输入

```
3 17 4
```

### 输出

```
13```

# 题解

## 作者：귀엽다 (赞：4)

我们来分析一下样例.    

```
3 17 4                     
第一个香蕉:3元   //这时一共要付3元             
第二个香蕉:6元   //这时一共要付9元             
第三个香蕉:9元   //这时一共要付18元           
第四个香蕉:12元  //这时一共要付30元               
30-17=4  
```
                  
其实,这一题是可以用for循环解决的
因为第几根香蕉的价钱就是k的几倍,因此只需要遍历1~w,用一个数累加1~w所有数*k的得数,然后输出k-这个数.
```cpp
for(int i=1;i<=w;i++){
		s+=k*i;
	}
```
接下来先别忙着输出,我们来看一组特殊的数据:        
2 10 2
根据样例的分析,再一次把它也分析一下.
```
2 10 2
第一个香蕉:2元   //这时一共要付2元             
第二个香蕉:4元   //这时一共要付6元             
```
可是...最后的结果小于总钱数呀,总不至于要找朋友士兵借负数的dollar吧~                            
遇到这种情况,我们的结果就是——0.                 
所以要加一个判断啦~
```cpp
if(s>n)cout<<s-n;
	else cout<<0;
```
好啦,放代码吧!
```cpp
int k,n,w,s=0;
	cin>>k>>n>>w;
	for(int i=1;i<=w;i++){
		s+=k*i;
	}
	if(s>n)cout<<s-n;
	else cout<<0;
    //return 0;的话,根据需要加吧.
```

---

## 作者：OdtreePrince (赞：3)

# -EASY-

只需求1~w的和乘k再减去n即为所求答案。

IMPORTANT:答案输出max(sum*k-n,0)！！！！！

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    int k,n,w,sum=0;
    scanf("%d%d%d",&k,&n,&w);
    for(int i=1;i<=w;i++){
        sum+=i;
    }
    cout<<max(sum*k-n,0);
    return 0;
}~~~

---

## 作者：meyi (赞：2)

#### 等差数列就是下面这样的：

$a_n=a_1+(n-1)*d$

$S_n=n*a_1+\frac{n*(n-1)}{2}*d$

#### 公式描述：式一为等差数列通项公式，式二为等差数列求和公式。其中等差数列的首项为$a_1$，末项为$a_n$，项数为$n$，公差为$d$，前$n$项和为$S_n$。
#### 所以，通过等差数列求和公式，我们可以轻松地AC本题。
#### 但本题有两个坑点：
#### 1.当自己的钱大于等于香蕉的钱时，不需要向朋友借钱，应该输出0。
#### 2.float类型存在精度问题，需要开long double。
#### 话不多说，上代码：
```cpp
#include<cstdio>
int k,n,w;
inline double max(double a,int b){return a>b?a:b;}
main(){
	scanf("%d%d%d",&k,&n,&w);
	printf("%.0lf",max(double(w+1)*w*0.5*k-n,0));
}
```

---

## 作者：Bronya18C (赞：2)

## 题意翻译
- 一个士兵想在商店里买W个香蕉。他必须为第一个香蕉支付K美元，第n个香蕉需要K*n美元
- 他有N元。他从他的朋友士兵那里借了多少美元去买W香蕉？
---
## 做法
- 首先，用FOR计算买N根香蕉的总价。

- 然后，用总价减去他带的钱即是答案。
---
# **注意**
## **注意**
### **注意**

- 要判断他的钱是否**大于等于总钱数**，如果是，则输出零。
- 记得回车（~~手动滑稽~~）

---

```
#include<bits/stdc++.h>

using namespace std;
long long K,N,W,yuan,ling=0;
int main()
{
  cin>>K>>N>>W;
  for(int i=1;i<=W;i++)yuan+=K*i;
  cout<<max(yuan-N,ling)<<endl;
}
```

---

## 作者：引领天下 (赞：2)

这题很简单啊，怎么没人做？

直接模拟，从第1根买到第m根。

然后用价格减去n即可。

代码太简单就不写注释了：

```cpp
#include <cstdio>
int k,n,w,ans;
int main(void){
    scanf ("%d%d%d",&k,&n,&w);
    while (w)ans+=k*(w--);
    printf ("%d",ans-n>0?ans-n:0);
}
```

---

## 作者：丁丁の丁丁 (赞：1)

本蒟蒻又来上传题解了
~~~~
#include<bits/stdc++.h>//万能头
using namespace std;
int main()
{
	long long n,m,k,l=0,i;
	cin>>n>>m>>k;//输入
	for(i=1;i<=k;i++)
	{
		l=l+i*n;//统计买香蕉君的money
	}
	if(l>=m) cout<<l-m;//需要借的钱
	else cout<<0;//如果钱已经够了，输出0；
	return 0; //养成return 0 的好习惯
}
~~~~

---

## 作者：封禁用户 (赞：1)

### ~~一大水题QAQ~~
##### ~~看到楼下大佬们没用函数做，本蒟蒻水一波QAQ~~
### 附上代码qwq
~~华丽的分割线QAQ~~

------------

	#include<cstdio>//这个不说啥了
	#include<iostream>//QAQ
	#include<cstring>//处理字符串
	#include<algorithm>//头文件
	using namespace std;
	int k,n,w,sum,QAQ;//定义变量
	int qwq(){//函数
		for(int i=1;i<=w;i++){//因为题目要求处理要支付的钱数
			sum+=k*i;//RT
		}
		if(sum>n)cout<<sum-n<<endl;//如果要支付的钱数大于自己的钱数 输出借的钱数
		else cout<<0<<endl;//如果小于 一分不借QAQ
        //回车保命
	}
	int main(){//主程序
		cin>>k>>n>>w;//读入
		qwq();//调用函数
		return 0;//结束
	}
    

------------

望管理员通过QAQ

---

## 作者：SKTelecomT1_Faker (赞：0)

这题还较为简单。

先自己笔算，一模拟：发现第一根香蕉到第n跟香蕉所用的钱恰好是1+……+n的值乘上第一根香蕉的单价，但是最后输出之前别忘了有个坑：如果给的钱就够用，那就输出零，作者本人就因此被坑了一次，希望读者注意

Code↓

```cpp
#include<bits/stdc++.h>
using namespace std;
int max(int a,int b)//最好手写函数
{
	return a>b?a:b;//三目运算符
}
int main( )
{
	int k,n,w;
	cin>>k>>n>>w;
	cout<<max(w*(w+1)/2*k-n,0)<<endl;//一定要注意！
	return 0;
}
```

看到这里可能有些读者会问：什么是三目运算符？

三目运算符，又称条件运算符，是计算机语言（c,c++,java等）的重要组成部分。它是唯一有3个操作数的运算符，有时又称为三元运算符。一般来说，三目运算符的结合性是右结合的。————百度百科

用自己的话来说，就是结构为a?b:c的一种算法，如果a判断返回值为true(1)，则执行b，如果返回了false(0)，则执行c，可以使代码更加简短，也可以节省下时间，十分方便。

希望对大家有帮助qwq

---

## 作者：林家三少 (赞：0)

# -VERY EASY-

本蒟蒻只是调用了一个函数...

	公式自己可以推出来：
    3 17 4
    需要输出： 13
    不难发现 13+17=30
    然后我看了这个'4'很久，突然灵机一闪：
    {
      4+3+2+1=10
      10*3=30
      30-17=13
    }
    这公示不就出来了吗

主要代码:
    
```cpp
int Bananas(int i){
  int ans=0;//定义答案变量
  for(int j=i;j>=1;j--){
    ans+=j;
    //利用公式
  }
  return ans;
  //最后才返回
} 
```

最后献上AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
int k,n,w;
//定义
int Bananas(int i){
	int ans=0;
	for(int j=i;j>=1;j--){
		ans+=j;
	}
	return ans;
} 
//主要部分
int main(){
	cin>>k>>n>>w;
	int IOI_AK_ME=Bananas(w)*k;
    //这里要调用函数
	if(IOI_AK_ME>n){
		cout<<IOI_AK_ME-n<<"\n";
        //如果需要借钱就输出
	}
	else{
		cout<<"0\n";
        //不需要就不需要吧
	}
	return 0;
}
```


---

## 作者：LJY_ljy (赞：0)

# 感觉是一道小学数学题，套公式解决。

首先，香蕉个数：c*(c+1)/2 个、等差数列求和公式。

价钱就是a*香蕉个数，输出max(价钱-w，0)，这样如果不需要借钱,就可以直接输出了。


------------

上代码：（没有什么好注释的）

```cpp
#include <iostream>
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    int num=0;
    num=a*(c*(c+1)/2);
    cout<<max(num-b,0)<<endl;
    return 0;
}
```

---

## 作者：ChoHakuNe (赞：0)

这可以理解为一道数学题...
虽然直接统计没问题...
作为另一种方法...
来一发**常数**复杂度吧...

简单来说香蕉的钱就是**等差数列**...求和比较即可
```
#include<cstdio>
int n,k,w;
int main(){
	scanf("%d%d%d",&k,&n,&w);
	printf("%d",w*(k+w*k)/2>n? w*(k+w*k)/2-n :0);
	return 0;
}
```

---

## 作者：rill4474 (赞：0)

# 这题咋没p党的做
## 我来发个题解
超短的代码

------------

```pascal
var
 i,j,k,n,m:longint;
begin
read(n,m,k);//输入
for i:=1 to k do j:=j+i*n;//累加香蕉的钱
if j>=m then write(j-m)//为啥要if，看下面
        else write(0);//注意，如果钱足够是不需要借的
end.
```
### 个人感觉很简单

---

