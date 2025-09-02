# Fixed Points

## 题目描述

A permutation of length $ n $ is an integer sequence such that each integer from 0 to $ (n-1) $ appears exactly once in it. For example, sequence $ [0,2,1] $ is a permutation of length 3 while both $ [0,2,2] $ and $ [1,2,3] $ are not.

A fixed point of a function is a point that is mapped to itself by the function. A permutation can be regarded as a bijective function. We'll get a definition of a fixed point in a permutation. An integer $ i $ is a fixed point of permutation $ a_{0},a_{1},...,a_{n-1} $ if and only if $ a_{i}=i $ . For example, permutation $ [0,2,1] $ has $ 1 $ fixed point and permutation $ [0,1,2] $ has $ 3 $ fixed points.

You are given permutation $ a $ . You are allowed to swap two elements of the permutation at most once. Your task is to maximize the number of fixed points in the resulting permutation. Note that you are allowed to make at most one swap operation.

## 样例 #1

### 输入

```
5
0 1 3 4 2
```

### 输出

```
3
```

# 题解

## 作者：Yaixy (赞：14)

# 题意及注意点

- 给一个 $0$ 到 $n-1$ 的全排列，只能将任两个数交换 **$1$** 次位置，求有多少个数能与自己所在的位置对应。

-    **是 $0$ 到 $n-1$ 的全排列而不是 $1$ 到 $n$！**

- **只能**交换 $1$ 次。

- 直接暴力模拟一遍**会T飞**。

# 思路

**P.S.**   如果拿到题时没有思路，可以先画图整理一下思路qwq

我们可以先画出 $3$ 种可能的情况

![](https://cdn.luogu.com.cn/upload/image_hosting/h4ljpw6i.png)

如上图，在第 $2$ 列中，黄色圆中的数字在正确的位置，蓝色圆中则是不在正确位置的数字。

那么，假设在正确位置上的数字个数为 $sum$，我们可以总结出 $3$ 种情况：

- 第一种：所有数字都在正确的位置上，可以直接输出 $n$。

- 第二种：有 $2$ 个数字**互换**了位置，可以用**仅有的**一次交换两数位置的机会将这两个数字交换位置，所以答案为 $sum+2$。

- 第三种：~~数字排的乱糟糟的，~~ **没有任何两个数能够在交换后全部变为正确位置。** 这时候，由于只能交换 $1$ 次位置，所以最好的方案是让其中 $1$ 个数回到正确位置。因此，答案为 $sum+1$。


那么现在，我们就可以“对症下药”，对仅有的 $3$ 种情况分别判断输出啦qwq

# 珂爱的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005],sum,n;
int main()
{
    cin>>n;
    for(int i=0;i<n;++i) cin>>a[i];//输入
    for(int i=0;i<n;++i) if(a[i]==i) sum++;//记录在正确位置上的数字个数
    if(sum==n)
     {
         cout<<n;
         return 0;//第一种情况
     }
    for(int i=0;i<n;i++)
     if(a[a[i]]==i&&i!=a[i])
      {
          cout<<sum+2;
          return 0;//第二种情况
      }
    cout<<sum+1;//第三种情况
    return 0;
}
```

完结撒花awa

---

## 作者：tryrtj (赞：6)

没有人发题解唉，赶紧来一发。其实这题我想了半天，怎么想都会TLE，后来才想到了一遍枚举来找出其应该在的位置上的数，如果正好相反，则就是这俩翻过来

顺便吐槽一下评测机显示Login Error（登录错误？）也是没啥说的了。

代码如下

```
#include<iostream>
using namespace std;
int a[100005];
int main(){
	int n;
	cin>>n;
	int zong=0;
	for(int i=0;i<n;i++){
		cin>>a[i];//读入
		if(i==a[i])zong++;//找已经对应的个数
	}
	if(zong==n){
		cout<<n;//特判
		return 0;
	}
	for(int i=0;i<n;i++){
		if(i==a[a[i]]&&i!=a[i]){//找所对应的是否就是
			cout<<zong+2;//直接出来
			return 0;
		}
	}
	cout<<zong+1;//否则只能+1
	return 0;
}
```


---

## 作者：梦理乾坤 (赞：3)

显然已经排好的就别动了

那么只剩下两种情况

1. 换一下可以让两个都到自己的位子上
2. 换一下只可以让一个到自己的位子上


```cpp
#include <iostream>

using namespace std;

const int N = 100010;

int a[N], ans, n;

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];// 输入

        if (a[i] == i)
            ans++;//看默认有几个是可以的
    }

    if (ans == n)
    {
        cout << ans << endl;
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (a[a[i]] == i && a[i] != i)//若可以一下子换，就可以变两个岂不美哉，hh
        {
            cout << ans + 2 << endl;
            return 0;
        }
    }

    cout << ans + 1 << endl;//否则只能加一个
    return 0;
}
```

求管理员过，谢谢

---

## 作者：FatOldEight (赞：2)

第一种方法：

>### 暴力枚举

dai码
----
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,l;
int a[100000],s[100000],d[100000],ans;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if(i==a[i])
		{
			s[i]=1;
			ans++;
		}
	}
	int q=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1+i;j<=n;j++)
		{
			if(!s[i]&&!s[j])
			{
				if(a[i]==j)
				{
					q=max(q,1);
				}
				if(a[j]==i)
				{
					q=max(q,1);
				}
				if(a[j]==i&&a[i]==j)q=2;
			} 
		} 
	}
	ans+=q;
	cout<<ans;
    return 0;
}
```
然后你会发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/yo8ugkpa.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

没错它T了。

于是第二种方法诞生了：
----
暴力枚举的复杂度是$O(n^2)$，明显行不通。

那么我们为什么要去找$j$呢？

我们直接用$a_i$去找$a_{a_i}$不就好了？

正确的代码
----
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,l;
int a[100000],s[100000],d[100000],ans;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)//因为是从零开始数，所以下标是0
	{
		cin>>a[i];
		if(i==a[i])//如果i=a[i]，则标记并ans+1
		{
			s[i]=1;
			ans++;
		}
	}
	int q=0;
	for(int i=1;i<=n;i++)
	{
		if(!s[i]&&!s[a[i]])//如果第i和第a[i]个数没被标记
		{
			if(a[a[i]]==i)q=2;//如果第a[i]个数的值等于i则代表互换ans+2，否则ans+1
			else q=max(q,1);//防止q=2被覆盖
		}
	}
	ans+=q;\\因为只能换一次所以取q最大值
	cout<<ans;
   return 0;
}
```

---

## 作者：zqwzqwzqw (赞：1)

 - ### 首先，$Fixed$ $Points$就是固定点的意思。
 
 读题可知此题是要求在一次交换后，统计这个数字位于数组以这个数字为下标的位置上的个数 ( 即统计$a_i=i$的数字个数 (数组为$a$) )。
 
 - ### 其次，考虑如何代码实现。
 
 $\because$ 只能交换一次，
 
 $\therefore$ 我们可以先统计一下交换前$Fixed$ $Points$的个数 (用$cnt$表示) ，再将剩余的点交换位置，一一对应各个情况。经整理，我们发现有$3$种情况。以$3$个数字为例，情况如下：

$\begin{cases}First&[0,1,2]\\ Second&[2,1,0]\\ Third&[1,2,0] \end{cases}$

 $\color{grey}First.$ 全部为$Fixed$ $Points$，不需交换，直接输出$cnt$或$n$即可。
```cpp
	if(cnt==n){
		cout<<cnt;//cout<<n;也一样 
		return 0; 
	}
```

 $\color{grey}Secoond.$ $2$和$0$的位置交换了，并且满足$a_{a_0}=0$ && $0 \ne a_0$，一次交换就可得到$cnt+2$个$Fixed$ $Points$,先枚举一边，再输出$cnt+2$即可。
```cpp
	for(int i=0;i<n;i++)
		if(a[a[i]]==i && i!=a[i]){
			cout<<cnt+2;
			return 0;
		}
```

 $\color{grey}Third.$ 无论怎么交换，都只能得到$cnt+1$个$Fixed$ $Points$，直接输出$cnt_1$即可。
```cpp
	cout<<cnt+1;
```

- ### 然后，上代码。
```cpp
	#include<bits/stdc++.h>
	using namespace std;
	int n,a[100005],cnt;
	int main(){
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>a[i];
			if(a[i]==i)
				cnt++;
		}
		//输入、计数
		if(cnt==n){
			cout<<cnt;//cout<<n;也一样 
			return 0; 
		}
		//同First
		for(int i=0;i<n;i++)
			if(a[a[i]]==i && i!=a[i]){
				cout<<cnt+2;
				return 0;
			}
		//同Second
		cout<<cnt+1;
		return 0;
		//同Third
	}
```


---

## 作者：wpy233 (赞：1)

其实一开始，蒟蒻我拿到这题时，还是很懵逼的qaq

然后就发现了这样的一句话：

> 可以交换两个数的位置**一次**

em……我谔谔

那么思路就非常显然了，共有$3$种情况。

> 第一种，每个数都在其位置上。

那就很`happy`了，一次也不用换了，直接输出$n$即可。

> 第二种，有两个数互换了位置。

那也很`happy`啊，就把这两个数换过来就行了。

> 最后一种，数列跟样例差不多。

`over`，那就随便找个不在位置上的数跟它该在的位置上换，由于任意两个数互换至少会有两个数不在其位置上，所以答案就为已在位置上数的个数再$+1$即可。

有了思路，代码还是不难理解吧~

```
#include <bits/stdc++.h> 
using namespace std;
int n;
int a[100005];//定义
int main()
{
	cin>>n;
	int p=0;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if(a[i]==i) p++;//如果这个数在其位置上，就标记一下
	}
	if(p==n)//第一种情况
	{
		cout<<p<<endl;
		exit(0);
	}
	for(int i=0;i<n;i++)
		if(a[a[i]]==i&&(a[i]-i))//第二种情况
		{
			cout<<p+2<<endl;
			exit(0);
		}
	cout<<p+1<<endl;//第三种情况
	return 0;
}

---

## 作者：小恐 (赞：1)

首先说一下翻译问题，可以交换一次，也可以不换。

法一：

暴力枚举交换每两个数后的情况，~~很明显~~超时，不放代码了。

法二：

明显如果已经是全部在自己的位置上，则不交换，答案为n。

如果只有一个不在-----------怎么可能？

剩下情况:

如果一个数已经在自己的位置上，则不让它交换，因为这样只会变少。

交换一次，可以使两个数都归位，当且仅当
```cpp
a[i]==j && a[j]==i
```
这样增加了2个。

如果没有，那么只要还有没归位的，则会增加1个。

所以我们只需枚举每个数，如果有与他成对的，则答案为已经在自己的位子上的+2，如果都没有，则+1。

上代码：
```cpp
#include<stdio.h>
#define MAXN 100005
using namespace std;
int a[MAXN];
int ans;//全局变量自动设为0 
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		scanf("%d",a+i);
		if(a[i]==i)//如果已经在自己位置上 
			++ans;//+1 
	}
	if(ans==n)	//全在自己位置上
	{
		printf("%d",n); 
		return 0;
	}
	for(int i=0;i<n;++i)
		if(a[i]!=i&&a[a[i]]==i)//如果有和他成对的
		{
			printf("%d",ans+2);//+2
			return 0;//程序结束 
		} 
	printf("%d",ans+1);//无对，只能+1
	return 0;
}
```
珍爱生命，远离抄袭！

---

## 作者：wfycsw (赞：0)

- ### 方法
首先，在输入时统计某个数原本就在自己所对应位置的个数。接着，在依题意交换两个错位的数。

- ### 注意点
题目所说的是**可以**交换两个数的位置一次，所以并不是所有情况都要交换。那什么情况不需要交换呢?那就是**没有数错位**。所以需要特判一下。接着再看能不能把两个数一次调到相应的位置，能则答案加二，不能则加一。

现在，上代码！

```cpp
#include<bits/stdc++.h>
#define RI register int
int a[100002];
int main(){
	RI n,ans=0;
	scanf("%d",&n); 
	for(RI i=0;i<n;i=-~i){
		scanf("%d",&a[i]);
		if(a[i]==i) ans=-~ans;
	}
	if(ans==n) printf("%d",n);//特判
	else{
		for(RI i=1;i<=n;i=-~i)
			if(a[i]!=i&&a[a[i]]==i){
				printf("%d",ans+2);
				return 0;
			}
		printf("%d",-~ans);
	}
	return 0;
}
```

---

## 作者：bigju (赞：0)

大体思路：首先因为我们只能换一次，那么我们肯定是要尽量发挥这一次的作用。首先排好的我们肯定不会动，所以我们先将原序列中排好位置的数量 $ans$ 处理出来。显然我们只要好好交换肯定能至少增加一个贡献，那么我们就看看我们能不能在换一次的时候把被交换的两个数的数都弄对应（即是否可以做到贡献为2）就行了。

注意的点：

1. 题目给出的是一个从 $0$ 到 $n-1$ 的全排列，而不是从 $0$ 到 $n$。
2. 数据范围是 $1<=n<=10^5$，这一点翻译中没给出，得上英文题面里找。
3. 需要特判一下输入数列已经排好了的情况，这时直接输出 $n$。

代码如下：
```cpp
```cpp
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
int n;
int a[100001];
int ans=0;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
    	scanf("%d",&a[i]);
    	if(a[i]==i) ans+=1;//处理出原来就在位置上的 
	}
	if(ans==n)
	{
		printf("%d",n);//都在就直接输出 
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		if(a[i]!=i) 
		{
			if(a[a[i]]==i)//如果可以达到一石二鸟的效果，就满足两个 
			{
				printf("%d",ans+2);
				return 0;
			}
		}
	}
	printf("%d",ans+1);//达不到那就只能多满足一个 
	return 0;
}

```



---

## 作者：2132B (赞：0)

### 题意解释
一开始我拿到这道题也是懵啊，“所对应的位置是”指什么呢？

$A$: 如数列$0,3,2,5,4,1$s所对应的就是数列的升序排序（其实就是$0,1,2,3,4,5$

### 思路剖析
对于每一个数，只有两种状态

1.在他本来的位置上

2.不在他本来的位置上

所以交换两个数就选第2种数交换（~~废话~~

对于交换来说，就只可能出现使第1种数多$2,1,0$个

因为要让第1种数尽可能多，所以尽量选$2,1$个

多两个：交换后使得两个数都在自己位置上，条件： _$a[[i]]==i$_

多一个：把一个位置上该有的数换过来，无条件

所以，我们便可以写出$Code$

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n, a[100100], ans;//题中1<=n<=10^5
int main()
{
	cin >> n;
	for (int i = 0;i < n;i++)//注意！！！从零开始！！题中是0~n-1的全排列
	{
		cin >> a[i];
		if (a[i] == i)
			ans++;
		if (ans == n)//一定要特判！否则当每个数都在自己位置上时，程序会输出n+1
		{
			cout << n;
			return 0;
		}
	}
	for (int i = 0;i < n;i++)//再次注意！！
	{
		if (a[a[i]] == i && a[i] != i)//要加上&&a[i] != i否则会将本在自己位置上的数算进去
		{
			cout << ans + 2;//多两个的情况
			return 0;
		}
	}
	cout << ans + 1;//无满足多两个的，只能多一个
	return 0;
}//完结！！！
```


---

## 作者：sinsop90 (赞：0)

这道题只能做一次交换两个数的位置的操作,所以我们找到最优交换方案即可

交换两个数,有两种能够增加答案的情况:

1.两个数都变回了原来的位置上,答案加上$2$

2.只有一个数都变回了原来的位置上,答案加上$1$

所以我们肯定是希望找到第一种,如果找不到便可以输出答案加$1$

于是有了以下代码:

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,mps[100005],ans=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&mps[i]);
		if(mps[i]==i){
			ans++;
		}
	}
	if(ans==n){
		cout<<ans<<endl;
		return 0;
	}
	for(int i=0;i<n;i++){
		if(mps[i]!=i && mps[mps[i]]==i){
			cout<<ans+2<<endl;
			return 0;
		}
	}
	cout<<ans+1<<endl;
}
```


---

## 作者：李至擎 (赞：0)

求管理员手下留情(╥﹏╥...)！！！

[点我看题](https://www.luogu.com.cn/problem/CF347B)

思路一：暴力枚举位置

时间复杂度： $O(n^2)$ 。

再一看数据范围： $1\le n \le 10^5$ ，肯定会TLE。

~~果不其然~~

![](https://cdn.luogu.com.cn/upload/image_hosting/yo8ugkpa.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么，暴力很明显是行不通了，还有什么办法呢？

思路二：转化为数论题

经过画图分析总结，我们可以发现原排列一共有 $3$ 种情况：

- $1.$ 当所有的数都在自己的位置上时：

	例如： $0$ $1$ $2$ $3$ $4$ $5$
    
	方法：直接输出 $n$ 就行了（不需要变动）；

- $2.$ 有两个数互相交换了位置：

	例如： $5$ $4$ $2$ $0$ $1$ $3$（ $1$ 和 $4$ 互换了位置）

	方法：只要把这两个数交换回来就行了（让归位数 $+2$ ）；

- $3.$ 都没有（其他情况）：

	例如： $5$ $4$ $0$ $2$ $3$ $1$

	方法：任意交换两个数，让其中一个归位（让归位数 $+1$ ，比如 $4$ 和 $3$）。
    
细节：数列是从 $0$ 开始的（~~我就在这里栽了一回~~）

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans;//n，a如题意，ans用来统计原本就在自己位置上的数的个数
int main()
{
	cin>>n;//输入
	for(int i=0;i<n;i++)//从0开始
	{
		cin>>a[i];
		if(a[i]==i)//如果原本就在自己位置上
		{
			ans++;//统计数++
		}
	}
	if(ans==n)//全部都在自己的位置上（第一种情况）
	{
		cout<<n;//直接输出
		return 0;//结束程序
	}
	for(int i=0;i<n;i++)
	{
		if(a[a[i]]==i&&a[i]!=i)//如果这两个数刚好交换了位置（第二种情况）
		{
			cout<<ans+2;//当这两个数交换后，在自己位置上的数的个数会+2，所以输出ans+2
			return 0;//结束程序
		}
	}
	cout<<ans+1;//都不是（第三种情况），输出个数+1
	return 0;//结束程序
}
```

修改记录：

$2020.8.10$ ：修改了一部分 $\LaTeX$ ，增加了注释并精简了一部分语言。

$2020.12.20$ ：增加了一部分 $\LaTeX$ ，增加了注释并精简了一部分语言。

---

