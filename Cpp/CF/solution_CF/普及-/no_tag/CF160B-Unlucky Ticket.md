# Unlucky Ticket

## 题目描述

Each of you probably has your personal experience of riding public transportation and buying tickets. After a person buys a ticket (which traditionally has an even number of digits), he usually checks whether the ticket is lucky. Let us remind you that a ticket is lucky if the sum of digits in its first half matches the sum of digits in its second half.

But of course, not every ticket can be lucky. Far from it! Moreover, sometimes one look at a ticket can be enough to say right away that the ticket is not lucky. So, let's consider the following unluckiness criterion that can definitely determine an unlucky ticket. We'll say that a ticket is definitely unlucky if each digit from the first half corresponds to some digit from the second half so that each digit from the first half is strictly less than the corresponding digit from the second one or each digit from the first half is strictly more than the corresponding digit from the second one. Each digit should be used exactly once in the comparisons. In other words, there is such bijective correspondence between the digits of the first and the second half of the ticket, that either each digit of the first half turns out strictly less than the corresponding digit of the second half or each digit of the first half turns out strictly more than the corresponding digit from the second half.

For example, ticket $ 2421 $ meets the following unluckiness criterion and will not be considered lucky (the sought correspondence is $ 2&gt;1 $ and $ 4&gt;2 $ ), ticket $ 0135 $ also meets the criterion (the sought correspondence is $ 0&lt;3 $ and $ 1&lt;5 $ ), and ticket $ 3754 $ does not meet the criterion.

You have a ticket in your hands, it contains $ 2n $ digits. Your task is to check whether it meets the unluckiness criterion.

## 样例 #1

### 输入

```
2
2421
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
0135
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
2
3754
```

### 输出

```
NO
```

# 题解

## 作者：hmzclimc (赞：1)

## 题意
原题传送门:

[Luogu](https://www.luogu.com.cn/problem/CF160B)

[Codeforces](https://codeforces.com/problemset/problem/160/B)

题意@[一锆一](https://www.luogu.com.cn/user/238419)大佬已经[说](https://www.luogu.com.cn/blog/zrgao/solution-cf160b)的很清楚了，我就不多说废话了。
## 思路
模拟。

根据题意，我们要判断对于每一位来说，前 $n$ 位是否大于后 $n$ 位或者前 $n$ 位是否小于后 $n$ 位。

那我们就把字符串拆到两个数组里，然后把两个数组分别排序。

同时比较这两个数组之间满不满足严格大于或严格小于的关系就好了。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<iomanip>
using namespace std;
const int maxn=105;
int n;
int a[maxn],b[maxn];
int main(){
    ios::sync_with_stdio(false);
    string x;
    cin>>n>>x;
    for(int i=0,j=n;i<n;i++,j++){
        a[i]=x[i]-'0'; // 处理到数组里
        b[i]=x[j]-'0';
    }
    sort(a,a+n);// 排序
    sort(b,b+n);
    bool flag1=true,flag2=true;
    // flag1判断是否大于
    // flag2判断是否小于
    for(int i=0;i<n;i++){
        if(a[i]<=b[i]){// 发现不合法情况
            flag1=false;
        }
        if(a[i]>=b[i]){// 同上
            flag2=false;
        }
    }
    if(flag1||flag2){ // 只要满足一种情况
        cout<<"YES";
    }else{
        cout<<"NO";
    }
    return 0;
}
```

---

谢谢观看，本人是菜鸡，如发现有问题，请指出，谢谢。

---

## 作者：Phoenix_chaser (赞：1)

# 本题思路
首先想吐槽一下本题的题意

题目大意：
小明相信玄学，他认为：对于车票号而言，如果前n位的每一位都可以配对到一个在车票号后n位的比其大的没有被用过的数，则这个号码就是不吉利的。

然而，本题的第一个样例

2421

就违反了此规则

输出了“YES”

经过了一些测试发现，其实它指的是前n位要么 _**前n每一位有后n一位大于它**_ 

已经另一种_**前n每一位有后n一位小于它**_

简单来说，就是题意给的少了一种情况

拿样例举例

![](https://cdn.luogu.com.cn/upload/image_hosting/7wkkojhc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

图片上是两种符合情况的样例，正好相反

题意分析完毕

思路其实就是把前n和后n进行排序
 
 _**同时不停比较**_ 

选两个数进行记录

**一个来记录是否前n大于后n**


另一个记录**是否前n小于后n**

两个数在循环过程如果不满足就赋0

如果比较过程中都成为0了， _**那就吉利了**_ 

不为0就不吉利了

上代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
char a[2020],b[2020];
int n,a1[2020],b1[2020],t,ans1=1,ans2=1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i]; 
	for(int i=1;i<=n;i++)
	cin>>b[i];
	for(int i=1;i<=n;i++)
	{
		t=a[i]-'0';
		a1[i]=t;
		//将每一位转换到数组里 
	} 
		for(int i=1;i<=n;i++)
	{
		t=b[i]-'0';
		b1[i]=t;
	 } 
	sort(a1+1,a1+n+1);
	sort(b1+1,b1+n+1);
	for(int i=1;i<=n;i++)
	if(a1[i]>=b1[i]) 
	//进行判断
	//不要忘了等于的情况 
	ans1=0;
	for(int i=1;i<=n;i++)
	if(a1[i]<=b1[i]) 
	ans2=0; 
	if(ans2==1)printf("YES");
	else if(ans1==1)printf("YES");
	else printf("NO");
	//最后判断 
	return 0; 
	
}
```
## 谢谢观看

# THE END



---

## 作者：借我昔日热忱 (赞：0)

本题思路比较简洁：

题目要求：前半部分的数字与后半部分的“ _**某一个数字**_ ”严格满足某一关系才输出“YES”。

------------


**这时候出现了第一个难点：如何尽可能的让所有数字都满足关系？**

机智的你一定发现了“ **某一个数字** ”就是这道题的切入点。

既然是**某一个数字**，那我们就可以大胆的**从后半部分随意挑选数字**使其与前半部分满足某一关系（~~有点类似于小贪心~~）。

通过模拟样例我们又发现，竟然可以直接走捷径！！！ ！！ 于是“ _**sort排序**_ ”应运而生。

------------


在十分激动的将判断等一系列代码打完之后结果编译没过，第二个难题出现了： _**数据是一串数字，如何把这一串数字一个个的保存到数组里然后单独比较呢?**_ 

这里提供1个思路：
读入单个字符然后转成数字存到数组中

------------

```cpp
伪代码
char l;int a[1000];
for(int i=1;i<=n;i++){
		cin>>l;
		a[i]=l-'0';
	}  
```

------------



~~（如果还想看看其他读入方面的思路的可以参考下面的题解，个人感觉这个应该还是比较简单好用的）~~

------------



剩下的就很简单了，排序之后直接前后比较即可。

 详见代码

------------

 ```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
char l;
int a[1000],b[1000];
int k; 
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>l;
		a[i]=l-'0';
	}  
	for(int i=1;i<=n;i++){
		cin>>l;
		b[i]=l-'0';
	}
	sort(a+1,a+1+n);//
	sort(b+1,b+1+n);
	if(a[1]>b[1]) k=1;
	if(a[1]==b[1]) {
		printf("NO\n");
		return 0;
	}
	for(int i=2;i<=n;i++){
		if(k)
			if(a[i]<=b[i]){
				printf("NO\n");
				return 0;
			}
		if(!k)
			if(a[i]>=b[i]){
				printf("NO\n");
				return 0; 
			}
	}
	printf("YES\n"); 
	return 0;
} 

------------

```

------------
谢谢观看!




---

## 作者：yuangq (赞：0)

这道题不是很难，但要注意要用字符的输入

详见代码注释

~~~
#include<bits/stdc++.h>
#define MAXN 10005
#define LL long long
using namespace std;
//int a[MAXN];
char aa[105];
char bb[105];
int a[105];
int b[105];
int main()
{
	//freopen("train.in","r",stdin);
	//freopen("train.out","w",stdout);
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>aa[i];//输入字符数字
		a[i]=aa[i]-'0';//转化为普通数字
	}
	sort(a,a+n);//从小到大排序
	for(int i=0;i<n;i++)
	{
		cin>>bb[i];
		b[i]=bb[i]-'0';
	}
	sort(b,b+n);
	bool alla=1,allb=1;
	for(int i=0;i<n;i++)
	{
		if(a[i]<=b[i])
		{
			alla=0;//有一个a[i]不大于b[i]，就不可能全是a[i]大了
		}
		if(a[i]>=b[i])
		{
			allb=0;//有一个b[i]不大于a[i]，就不可能全是b[i]大了
		}
	}
	if(alla==1 || allb==1)//全是a[i]大或全是b[i]大，输出“YES”
	{
		cout<<"YES";
	}
	else//否则输出“NO”
	{
		cout<<"NO";
	}
	return 0;
}
~~~

---

