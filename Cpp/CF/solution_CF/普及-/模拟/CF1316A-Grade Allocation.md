# Grade Allocation

## 题目描述

$ n $ students are taking an exam. The highest possible score at this exam is $ m $ . Let $ a_{i} $ be the score of the $ i $ -th student. You have access to the school database which stores the results of all students.

You can change each student's score as long as the following conditions are satisfied:

- All scores are integers
- $ 0 \leq a_{i} \leq m $
- The average score of the class doesn't change.

You are student $ 1 $ and you would like to maximize your own score.

Find the highest possible score you can assign to yourself such that all conditions are satisfied.

## 说明/提示

In the first case, $ a = [1,2,3,4]  $ , with average of $ 2.5 $ . You can change array $ a $ to $ [10,0,0,0] $ . Average remains $ 2.5 $ , and all conditions are satisfied.

In the second case, $ 0 \leq a_{i} \leq 5 $ . You can change $ a $ to $ [5,1,1,3] $ . You cannot increase $ a_{1} $ further as it will violate condition $ 0\le a_i\le m $ .

## 样例 #1

### 输入

```
2
4 10
1 2 3 4
4 5
1 2 3 4```

### 输出

```
10
5```

# 题解

## 作者：Aw顿顿 (赞：2)

不错的入门题。

----

只要保证总分相等，就能保证平均分相等。

考虑一个贪心策略，即让所有的人都变成 $0$ 分，这样我就能尽可能高了。

这时候，我的分数就是 $\sum\limits_{x=1}^{n}a_i$，也就是大家分数的总和。

那么，这究竟行不行呢？显然是不完善的，由于很可能我的最大分数已经超过 $m$ 了，这时应当取 $m$。

那，取 $m$ 的话，同学们都变成 $0$ 分平均分都不一致了啊？我只要让其中的某些同学再拿一点分数，使得总分等于原来的总分就行了，可行性容易理解。

那么结论就出来了，$\max(\sum\limits_{x=1}^{n}a_i,m)$，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,x;
int main(){
	scanf("%d",&T);
	while(T--){
		int s=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			s+=x;
		}cout<<(s<m?s:m)<<'\n';
	}return 0;
} 
```

求赞。

---

## 作者：_Harrisonwhl_ (赞：1)

## [传送门](https://www.luogu.com.cn/problem/CF1316A)
一道贪心题，如果想要平均分一定，$1$号同学得分高，则其他同学得分应当低，想要其他同学得分尽可能少，就令他们都是$0$分，则$1$号同学的理想化得分是所有人得分和，我们将理想化得分称为 $s$,但是有一个最高分限制 $m$,所以，如果 $s$ 比 $m$ 大，则最高得分为 $m$,如果 $s$ 比 $m$ 小，则最高得分为 $s$,我们将两种情况合并，可以发现最高得分是 $\min(s,m)$,所以，就可得出完整程序了。

完整程序：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,m,s,no;
    cin >> t;
    while (t--)//大佬们都写while循环，我以后也用while循环了。
    {
        s = 0;//每次都要初始化啊！
        cin >> n >> m;
        for (int i = 1;i <= n;i++)
        {
            cin >> no;
            s += no;//计算理想化得分s。
        }
        cout << min(s,m) << endl;
    }
    return 0;
}
```

---

## 作者：Andrewzdm (赞：1)

# [CF1316A Grade Allocaion](https://www.luogu.com.cn/problem/CF1316A)
其实平均数不变的实质就是所有学生的分数总和不变。

由于每个学生的分数最少为0，所以我们只要把除了第1名学生之外的所有学生的分数全部给第1个学生就能使他的分数最大。

不过还有个限制条件：分数最大为m。

加上这个限制条件，代码就出来了。

见下：
```cpp
#include<iostream>
using namespace std;
int a[1005];
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n, m;
		cin >> n >> m;
		int sum = 0;
		for(int i = 1; i <= n; i++)
		{
			cin >> a[i];
			if(i != 1)
				sum += a[i];
		}
		cout << min(m, sum + a[1]) << endl;	
	}
	return 0;
}
```
时间复杂度 $O(n)$

---

## 作者：123456zmy (赞：1)

题意：  
给你一个数列，你可以在保持平均值不变且最大值不高于 $m$ 的情况下修改一些值（非负），问修改后最大的最大值是多少。
___
~~水题~~，输出和与 $m$ 中较小的那个即可。因为非负，那就把其它的都变为 $0$，剩下的一个加尽可能多，如果加完还有多的就分到别的里去。

代码：（~~记得初始化~~）
```cpp
scanf("%d%d",&n,&m);
while(n--)
{
	scanf("%d",&a);
	sum+=a;
}
printf("%d\n",min(sum,m));
```

---

## 作者：Otue (赞：0)

题目中说保证**平均值**不变，也就是**总分**不变，但总分就只有那么多啊，而且最高分也就 $m$ 分啊

所以~~为了自己的分数最高~~通过贪心思想，让其他的人~~都~~尽可能爆零，自己~~AK~~尽可能的最高（可能是总分也可能为 $m$ 分），但是分数不能超过 $m$ 分

也就是说，把总分与 $m$ 比较一下就得
### 代码
```c++\
#include<bits/stdc++.h>
using namespace std;
int T;
int n,m,a[10005];
int s;
int main(){
	cin>>T;
	while(T--){
		s=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s+=a[i];
		}
		if(s<=m){
			cout<<s<<endl;
		} 
		else{
			cout<<m<<endl; 
		}
	}
}
```

---

## 作者：Cym10x (赞：0)

### 题意分析
给定由$n$个整数组成的数组$a_{1...n}$,在保证$0 \leq a_i \leq m$且$\sum_{i=1}^n a_i$不变时（原题上写的是平均值不变。但考察公式：$平均值 = \frac {数据总和} {数据数量}$，因此，数据数量一定，**总和不变，平均值不变**。），让$a_1$最大化。
### 算法简析
这题我们可以使用一个很简单的贪心：**先把全班成绩转移成自己的成绩**，即令$a_1=\sum_{i=1}^n a_i$。考虑每个人的成绩不能超过$m$，
我们就先计算总和，如果大于$m$就取$m$作为答案（最大限制），否则将总和作为答案。

~~毕竟，先让自己得满分才是最重要的，别人到时候再考虑也不迟\~~~

### demo
```cpp
#include<stdio.h>
#define ll long long
#define in(x) scanf("%d",&x)
#define inll(x) scanf("%lld",&x) 
#define out(x) printf("%lld",(ll)x)
#define outn(x) printf("%lld\n",(ll)x)
#define outr(x) printf("%lld ",(ll)x)
/*我的习惯*/
int n,m,ans,x;
int main(){
	int tester;
	in(tester);
	for(int testest=1;testest<=tester;testest++){
		in(n);in(m);
		ans=0;
		/*求和器清零*/
		for(int i=1;i<=n;i++){
			in(x);
			ans+=x;
			/*累加求和*/
		}
		if(ans<m)outn(ans);
		/*如果ans小于m，则取ans作为答案*/
		else outn(m);
		/*否则取m作为答案*/
		/*
		对于每一组测试数据：
		时间复杂度：O(n)  (31ms)
		空间复杂度：O(n)  (8KB)
		*/
	}
	return 0;
}
```

---

## 作者：LLGZ (赞：0)


没错，我又双叒叕来（水）写题解了
### 思路
首先，第二点$0\leq a_i\leq m$非常重要.

既然$a_i$可以是0,而又要1同学的分数最大化，这样的话...

~~暴力不讲理~~把其他同学的分数直接转移到1同学上怎么样？

但还有个限制条件：1同学的分数最大是$m$

那么我们定义一个变量储存所有同学的分数，把所有分数全部转移到1同学上，如果超过$m$,1同学分数就只能是$m$,即

```cpp
   	    if(ans>m)
   	    ans=m;
```
code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;
int main()
{
   int t;
   scanf("%d",&t);//CF的传统，多组数据
   for(int i=1;i<=t;i++)
   {
   	    int n,m;
   	    scanf("%d%d",&n,&m);
   	    
   	    int ans=0;
   	    int a;
   	    for(int j=1;j<=n;j++)
   	    {
   	    	scanf("%d",&a);
   	    	ans+=a;//输入分数，储存到ans，就可以不用了
   	    }
   	    if(ans>m)//全篇关键
   	    ans=m;
   	    printf("%d\n",ans);
   } 
	return 0;
}
```
~~求过~~


---

## 作者：fz20181223 (赞：0)

尽然让我们把第一名学生的分数尽可能地扩大，那么——

我把所有人的分数加到你头上怎么样！

所以，这个程序大概就是这样子：

先把所有人的分数加到一起，如果超出了总分，那么就输出总分，否则就把这个分数输出就行了。

源码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int cas;
	cin>>cas;
	for(int ii=0;ii<cas;ii++){
		int n,m,x,tot=0;
		cin>>n>>m;
		for(int i=0;i<n;i++){
			cin>>x;
			tot+=x;
		}
		if(tot<m) cout<<tot<<endl;
		else cout<<m<<endl;
	}
	return 0;}
```

---

