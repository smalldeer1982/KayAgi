# Interesting drink

## 题目描述

Vasiliy likes to rest after a hard work, so you may often meet him in some bar nearby. As all programmers do, he loves the famous drink "Beecola", which can be bought in $ n $ different shops in the city. It's known that the price of one bottle in the shop $ i $ is equal to $ x_{i} $ coins.

Vasiliy plans to buy his favorite drink for $ q $ consecutive days. He knows, that on the $ i $ -th day he will be able to spent $ m_{i} $ coins. Now, for each of the days he want to know in how many different shops he can buy a bottle of "Beecola".

## 说明/提示

On the first day, Vasiliy won't be able to buy a drink in any of the shops.

On the second day, Vasiliy can buy a drink in the shops $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ .

On the third day, Vasiliy can buy a drink only in the shop number $ 1 $ .

Finally, on the last day Vasiliy can buy a drink in any shop.

## 样例 #1

### 输入

```
5
3 10 8 6 11
4
1
10
3
11
```

### 输出

```
0
4
1
5
```

# 题解

## 作者：CYOI官方账号 (赞：5)

### 这题没有用桶排的，我就用一下
**用 $t$ 数组维护 $a$ 数组中出现的数，再用 $tt$ 数组维护 $\sum_{k=1}^it_k$**

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,m,a[100001],t[100001],tt[100001],lem,Max=-1e6;
int mmax(int a,int b){
	if (a>=b) return a;
	return b;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],t[a[i]]++,Max=mmax(a[i],Max);
	for(int i=1;i<=Max;i++) tt[i]=tt[i-1]+t[i];
	cin>>m;
	for(int i=1;i<=m;i++) {
		cin>>lem;
		if (lem<=Max) cout<<tt[lem]<<endl;
		else cout<<tt[Max]<<endl;
	}
	return 0;
}
```


---

## 作者：一只大龙猫 (赞：4)

这里提供一种略为暴力的方法。

在输入完每家商铺中饮料的价格后，我们将其按升序排序。

但是在输入每次最多能花多少钱时，我们**并不在线处理，而是存到数组 $q$ 中，再按升序排序。**

这是干什么呢？

不难看出，**当数组 $q$ 按升序排序时，数组 $ans$ 单调不递减。**（设 $ans_i$ 用来存放按升序排序后 $q_i$ 的答案。）也就是说，若 $1 \le i < j \le m$ ，则 $ans_i \le ans_j$。

这有什么用呢？

我们之所以暴力会超时，是因为我们处理每一个查询都需要遍历数组一遍。但是，当我们将数组 $a$ 和 $q$ 都排序好后，**我们就可以从上一次查询遍历到的地方开始**，这样就可以节省很多时间！

先来看看代码。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,a[100001],now=1,ans[100001];
struct node{//由于输出需要按照原来的顺序输出，所以这里使用了结构体
	int num;//排序后第i次查询的内容
	int id;//排序前q[i]的下标
}q[100001];
bool cmp(node a,node b){
	return a.num<b.num;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>q[i].num;
		q[i].id=i;
	}
	sort(a+1,a+n+1);
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(q[i].num>=a[n]){
			ans[q[i].id]=n;
			continue;
		}
		while(q[i].num>=a[now]){
			now++;
		}
		ans[q[i].id]=now-1;
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

为了简洁，后文所有的`q[i].num`都用 $q_i$ 表示。

$ans$ 数组所表示的意思有所变化，$ans_i$ 表示的意思是排序前第 $i$ 次查询的答案。

这里的变量 $now$ 用于存放上一次查询遍历到的位置。

```cpp
if(q[i].num>=a[n]){
		ans[q[i].id]=n;
		continue;
}
while(q[i].num>=a[now]){
	now++;
}
ans[q[i].id]=now-1;
```

这一段代码的意思是：

如果 $q_i \ge a_n$，意味着去每一家店铺都能买到饮料，这时答案为 $n$。

否则意味着至少有一家店我们买不到饮料，这时我们就可以往后枚举，直到出现 $q_i < a_{now}$ 的情况。这时，$now-1$ 就是我们的答案。

由于 $1 \le n \le 10^5$，我们最多只需遍历 $10^5$ 次，所以是可以通过的。

---

## 作者：Toclhu (赞：4)

来一发二分题解。

### 题目大意

给出一个长度为 $n$ 的数组，进行 $T$ 次询问，每次询问给出一个数 $x$ ，求数组中小于等于 $x$ 的数有几个。

### 思路
暴力是肯定过不了的，可以用快排保证数组的单调性，然后二分。

### code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005],n,t,x;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>x;
        int l=0,r=n,mid;
        while(l<=r){
            mid=(l+r)/2;
            if(x<a[mid]) r=mid-1;
            else if(x>=a[mid]) l=mid+1;
        }//二分板子，找到第一个大于x的数
        cout<<l-1<<endl;//因为数组是单调不减的，所以直接输出就好
    }
    return 0;
}
```

---

## 作者：Suuon_Kanderu (赞：1)

这题其实很简单（吗） 

翻译

```
瓦西里喜欢喝"Beecola"饮料。

卖这种饮料的商铺有x家。每家的价格是x[i]元。

现在瓦西里 要买这种饮料n次，每次他最多能花n[i]元，

求他每次能在几个商铺买到至少一瓶饮料。

简短版：给出一个长度为x的数组，有n次询问，
输出 第n次询问的数大于等于几个x数组里的元素。

输入：第一行一个正整数x，表示商铺的数量。

第二行x个正整数，x[i]，表示每家商铺中饮料的价格

第三行一个正整数n，表示询问的次数。

之后n行，每行一个正整数n[i],表示最多能花多少钱

输出：n行，每行一个正整数，表示每次能去几家商铺买到饮料
```
所以，这题就是让我们求n[i]大于等于几个商铺里饮料的价钱！！

思路：

定义两个数组，输入不说了，暴力循环每个n[i]大于等于几个x[j];
 
```
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],s,x[100001];
int main() 
{   
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    cin>>s;
    for(int i=1;i<=s;i++)cin>>x[i];
    for(int i=1;i<=s;i++)
    {
    	int ans=0;
    	for(int j=1;j<=n;j++)
    	if(x[i]>=a[j])ans++;
    	cout<<ans<<endl;
	}
	return 0;
}
```
不过，你确定这样不会TLE吗（不然怎么可能是普及-）
窝就TLE了，所以我们需要个更先进的办法

优化：当然能想到排序，快排是最好的，可以直接用sort啊。

然后给大家介绍一个函数upper_bound（a,a+n,x）这个函数从a到a+n搜索不小于x的第一个地址，所以我们用他减去数组首地址就能获得大于等于x的第一个元素的下标。

有什莫用呢？大家想想，sort是从小到大排序，所以所以。

大于等于x的第一个元素的下标就是比x小的所有元素的数量！！
（好像发现了新大陆）

呜，上代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],s,x[100001];
int main() 
{   
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);//sort快排
    //for(int i=1;i<=n;i++)cout<<a[i]<<" ";
    cin>>s;
    for(int i=1;i<=s;i++)cin>>x[i];
    for(int i=1;i<=s;i++)
    {
    	int ans=upper_bound(a+1,a+n+1,x[i])-a-1;
     //别忘记减一，因为下标是从1开始的。
    	cout<<ans<<endl;
	}
	return 0;
}
```






---

## 作者：rzh123 (赞：0)

# CF706B 题解  
题目链接：[CF706B Interesting drink](https://www.luogu.com.cn/problem/CF706B)  

写一种不用二分、不用桶的做法。  

思路：先输入，然后排序，然后预处理出 $[0,\max\{x_i\})$ 之间每个数对应的答案，查询时如果 $n_i\gt\max\{x_i\}$ 就直接输出 $\max\{x_i\}$，否则输出预处理出的答案。  
以样例为例：  
```plain
5
3 10 8 6 11
4
1
10
3
11
```  

对 $x$ 排序后：
```
3 6 8 10 11
```
所有 $[3,6)$ 之间的数对应答案都是 $3$，所有 $[6,8)$ 之间的数对应答案都是 $8$……  
所有 $[11,+\infty)$ 之间的数对应答案都是 $11$。

AC 代码：  
```cpp
#include <cstdio>
#include <algorithm>
#define N 100007
#define X 100007
int n,m,mm,x[N],ans[X];
inline int read(){
	int t=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') t=10*t+(c^48),c=getchar();
	return t;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		x[i]=read();
	}
	std::sort(x+1,x+n+1);
	for(int i=1;i<n;++i){
		for(int j=x[i];j<x[i+1];++j){
			ans[j]=i;
		}
	}
	m=read();
	while(m--){
		mm=read();
		if(mm>=x[n]){
			printf("%d\n",n);
		}
		else{
			printf("%d\n",ans[mm]);
		}
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/61327521)

---

