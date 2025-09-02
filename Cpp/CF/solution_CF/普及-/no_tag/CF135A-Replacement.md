# Replacement

## 题目描述

Little Petya very much likes arrays consisting of $ n $ integers, where each of them is in the range from $ 1 $ to $ 10^{9} $ , inclusive. Recently he has received one such array as a gift from his mother. Petya didn't like it at once. He decided to choose exactly one element from the array and replace it with another integer that also lies in the range from $ 1 $ to $ 10^{9} $ , inclusive. It is not allowed to replace a number with itself or to change no number at all.

After the replacement Petya sorted the array by the numbers' non-decreasing. Now he wants to know for each position: what minimum number could occupy it after the replacement and the sorting.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1 1 2 3 4
```

## 样例 #2

### 输入

```
5
2 3 4 5 6
```

### 输出

```
1 2 3 4 5
```

## 样例 #3

### 输入

```
3
2 2 2
```

### 输出

```
1 2 2
```

# 题解

## 作者：封禁用户 (赞：4)

题目传送>>[CF135A](https://www.luogu.com.cn/problem/CF135A)  
### 题意简述：  
- 给定 $n$ 个数，用 $1$~$10^9$ 之间的数（除其本身）替换其中一个数，使得这 $n$ 个数的总和最小，并将这些数按升序输出。  
- $1\le a[i]\le 10^9$，需要使用 long long。  
### 题目分析：  
要想替换其中一个数使其所有数总和最小，那么我们可以把其中最大的数替换得尽可能小（能为 $1$ 即为 $1$ ，不然再增 $1$）。找出其最大值我们可以对输入的数进行排序，但将最大数替换得尽可能小就还需要一个判断，如果其最大数已经为 $1$，那么我们只能将其替换为大于 $1$ 的最小整数 $2$，否则我们就都能将其替换为 $1$。替换完成后，我们再根据题意再次排序，再全部输出即可。  
### 问题解决：  
#### 排序：  
我们可以使用 STL 中的 sort( ) 函数进行简单排序，其包含于 algorithm 库中。  
sort(start,end),第一个参数start是要排序的数组的起始地址,第二个参数是结束的地址(最后一位要排序的地址的下一地址)，默认排序方式为升序。  
例：a[]={$1,3,4,2$},经  
```cpp
	sort(a,a+4);
```
后数组a将变为{$1,2,3,4$}。  
#### 判断：  
我们可以直接使用 if...else... 来：  
```cpp
	if(a[n]==1)
	{
		a[n]=2;
	}
	else
	{
		a[n]=1;
	}
```
当然，我们也可以使用一个小东西 —— 三目运算符 “?:”。  
例 ：a?b:c 的含义是：如果 a 为真，则表达式的值是 b，否则是 c。  
此题可写为：  
```cpp
	a[n-1]=(a[n-1]==1?2:1);
```
### Code:  
```cpp
#include <iostream>
#include<algorithm>   //sort()含于此 
using namespace std;
typedef long long ll;   //类型定义long long 为ll,避免频繁使用long long 时累手 
ll a[100001];   //开数组存数 
int main()
{
	ios::sync_with_stdio(0);   //关同步流，加速cin输入和cout输出 
	ll n;   //定义数的个数 
	cin>>n;
	for(int i=0;i<n;i++)
	{
   	 	cin>>a[i];
	}
	sort(a,a+n);   //对原始数进行排序 
	a[n-1]=(a[n-1]==1?2:1);   //利用三目运算符进行判断赋值替换 
	sort(a,a+n);   //对最终数进行排序 
	for(int i=0;i<n;i++)
	{
        cout<<a[i]<<" "; 
	}
	return 0;    //结束整个程序 
}
```
### 测评结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/l7oobwv6.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：qhztz (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF135A)
## 思路：
显然，输入进来之后直接sort排序，然后将最大的替换为1后再输出即可。

注意：**题目中要求我们不能用本身替换自己**

所以我们需要一个特判。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a[100005];
int main(){;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	sort(a,a+n);//排序
	if(a[n-1]==1) a[n-1]=2;//这里要用一个特判，原因上面已讲
	else a[n-1]=1;//因为a[n-1]是最大的，所以先判断a[n-1]是否是1
	sort(a,a+n);//替换完再次排序
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";//输出
}
```
拜拜qwq

---

## 作者：wkjwkj (赞：1)

[**$\color{coral}\text{更好的阅读体验}$**]( http://mywkj.github.io/2020/06/06/cf135a-replacement-ti-jie/)

题目还是比较简单的，不难就能想到思路。我们可以将原数组排序，然后在将数组中最大值替换为1。

就像这样:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	a[n]=1; 
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
 } 
```

~~结果，你会惊喜的发现，你$\mathtt{WA}$了~~

比如这组数据

```php
input:
3
1 1 1
user output:
1 1 1
test output:
1 1 2
```



题目中要求我们不能用本身替换自己，所以我们稍作修改便能$\mathtt{AC}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	if(a[n]==1)a[n]=2; 
	else a[n]=1;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
 } 
```



---

## 作者：FJ·不觉·莫笑 (赞：0)

### **水**  


------------
### **读题：**  
  给你$n$个数，让你用$1$~$10^9$之间的数 **(除了本身)** 替换其中一个元素后剩下和最小.  
  数据范围：$1$$\le$$n$$\le$$10^5$,$1$$\le$$a_i$$\le$$10^9$  


------------
### **思路：**  
 1. 先将数组从小到大排序（$sort$即可）  
 2. 再将最大的数换成1即可，但有一种情况除外，**除了本身**，在上面也加粗了，若最大的数为1，则要将1换成2.  
 3. 将换好后的数组重新排序，然后输出。  


------------
### **上代码：**  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100000];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);//第一次排序 
	if(a[n]==1)//特判处理最大值 
		a[n]=2;
	else
		a[n]=1;//否则换成一 
	sort(a+1,a+n+1);//再次排序 
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个数 $a_1,a_2,a_3,...,a_n$，试用 $1$ ~ $10^9$ 之间的数（除了本身）代替其中的一个数，使得这 $n$ 个数的总和最小，并将数组按照非降序输出。

**数据范围：$1\leqslant n\leqslant 10^5,1\leqslant a_i\leqslant 10^9$。**
## Solution
首先我们排序一遍之后就可以找到最大的数，然后很显然，修改得要从最大的数入手。

然后我们需要分类讨论一下：

1. 当最大的数为 $1$，此时需要将这个最大的数修改为 $2$ 才能符合要求。
2. 否则，直接将最大的数修改为 $1$ 即可。

修改完之后再排序一遍即可得到我们需要的数组。
## Code
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n, a[100007];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	a[n] = (a[n] == 1 ? 2 : 1);
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; printf(" "), ++i)
		printf("%d", a[i]);
}
```

---

## 作者：loc_equinox (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF135A)

题意：将 $n$ 个**正整数**中任意一个替换成**除本身之外**的，$1$ 至 $10^9$ 之间的整数（含 $1$ 和 $10^9$）。求替换后第 $k$ （$k=1\cdots n$）小的数的最小值。

假定原来的 $n$ 个数已经**排好序**，存在数组 $a$ 中（$a_1,a_2,\cdots a_n$）。排序是为了便于判断更改之后，第 $k$ 小的数是什么。

考虑将第 $x$ 小的数 $a_x$ 更改为 $y$ 。那么我们分类讨论：

1. $a_{x-1}<y<a_{x+1}$ 且 $y\neq a_x$。那么此时第 $x$ 小的数是 $y$。
1. $y\leq a_{x-1}$。那么此时第 $x$ 小的数是 $a_{x-1}$。
1. $y\geq a_{x+1}$。那么此时第 $x$ 小的数是 $a_{x+1}$。

又因为 $a_{x-1}\leq a_{x+1}$，所以情况 $2$ 显然是最优的，即 $a_{x-1}$ 是最小的 $y$。

那么当 $a_x=a_{x-1}=1$ 的时候怎么办呢？$a_x$ 不能改成它自己，也不能比 $1$ 还小。对于这种情况，将 $a_{x+1}$ 改成一个大于 $1$ 的数即可，还是能保证 $a_{x-1}$ 是最小的 $y$。

针对上面情况，还有一点要注意：当$a_x=a_{x-1}=1$ 且 $x=n$ 时 $a_{x+1}$ 不存在，因为必须改一个数，所以只能把 $a_n$改成 $2$。

因为全 $1$ 数列的特殊性，所以代码中分成 $n>1$ 和 $n=1$ 两种情况:
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,i,a[100002];
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    if(n>1)
    {
        cout<<1<<" ";//易得最小数一定是1
        for(i=1;i<n-1;i++)cout<<a[i]<<" ";
        if(a[n]==a[n-1]&&a[n]==1)cout<<2;
        else cout<<a[n-1];
    }
    else
    {
        if(a[n]==1)cout<<2;
        else cout<<1;
    }
    return 0;
}

```

---

## 作者：dk——又哇红题 (赞：0)

我的解题思路：因为要使和最小，又因为这之中之只能改一个数，所以要把最大的数替换，输入时同时找到最大的数，并记下下标。

再判断如果最大的数为1，那么就要把它改为2（因为不能替换成自己，又不能不改数），否则改为1。最后排序并输出。

# c++我核心代码如下：
```cpp
for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>maxn)
		{
			maxn=a[i];
			maxi=i;
		}
	}
	if(maxn!=1)
		a[maxi]=1;
	else
		a[maxi]=2;
	sort(a+1,a+1+n);
```
仅供参考，谢谢。

---

## 作者：Arvin2018 (赞：0)

这道题是灰常简单的**纯**模拟题

# 然而我UKE了不知道多少遍
里面从2019-5-24 21:28 ~ 2019-5-24 21:50都是我的提交记录，除了第9个是wa，其他都是UKE（我加了注释还是uke。。）

# 行，进入正题

这题被我搞出了勉强算两种解法（解释见注释）：

### ①
```
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	int a[n];
	int max_num = 0, max_place = 0;//max_num 是最大数字，max_place 是最大数字的位置
	for(int i = 0; i < n; i++){
		cin >> a[i];
		if(a[i] >= max_num){//输入同时找最大
			max_num = a[i];
			max_place = i;
		}
	}
	if(a[max_place] != 1){//由于不能自己替换自己，要先判断这个位置是不是1
		a[max_place] = 1;
	}
	else a[max_place] = 2;//是1就用2替换  
	stable_sort(a, a+n);//排序
	for(int i = 0; i < n; i++){
		cout << a[i] << " "; 
	}
	return 0;
}
```
### ②

```
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}//输入
	sort(a, a+n);//排序
	a[n-1] = a[n-1]==1?2:1;//a[n-1]是最大的，后面的用来判断是否是1的函数
	sort(a, a+n);//替换完再次排序
	for(int i = 0; i < n; i++){
		cout << a[i] << " "; 
	}
	return 0;
}

```
## UKE了千万不要放弃，加点注释继续提交

---

