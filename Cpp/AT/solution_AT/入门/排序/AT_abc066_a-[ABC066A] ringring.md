# [ABC066A] ringring

## 题目描述

snuke 君来买自行车了。snuke 君已经决定要买哪辆自行车了，但那辆自行车没有配备铃铛，因此需要另外购买铃铛。

snuke 君非常注重安全，所以他打算在左右两个把手上各装一个铃铛，这样无论用哪只手都能按铃。

店里有 $3$ 种铃铛，价格分别为 $a$ 日元、$b$ 日元、$c$ 日元。在这三种铃铛中，选择两种不同的铃铛购买时，求两只铃铛价格之和的最小值。

## 说明/提示

## 限制条件

- $1 \leq a, b, c \leq 10000$
- $a, b, c$ 均为整数

## 样例解释 1

如果买 $700$ 日元的铃铛和 $600$ 日元的铃铛，总共需要 $1300$ 日元。买 $700$ 日元的铃铛和 $780$ 日元的铃铛，总共需要 $1480$ 日元。买 $600$ 日元的铃铛和 $780$ 日元的铃铛，总共需要 $1380$ 日元。因此，最便宜的是 $1300$ 日元。

## 样例解释 2

无论选择哪两种铃铛，都需要 $20000$ 日元。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
700 600 780```

### 输出

```
1300```

## 样例 #2

### 输入

```
10000 10000 10000```

### 输出

```
20000```

# 题解

## 作者：CZQ_King (赞：2)

# 又一道水题
## 这题好多$dalao$都用快排$(sort)$
### 本蒟蒻就提供一种新思路：
## $all-biggest=smallest+smallest_{second}$
也就是总和-最大值=最小值+次小值
~~（本人英语不好）~~
```cpp
#include<bits/stdc++.h>//头文件
using namesapce std;
int a,b,c;//定义三种价格
int main(){
    cin>>a>>b>>c;//输入价格
    cout<<(a+b+c)-max(a,max(b,c))<<endl;//按照思(tao)路输出
    return 0;//完美结束
}
```

---

## 作者：封禁用户 (赞：2)

### 简要题意
给定三个整数$\texttt{a,b}$和$\texttt{c}$，求其中较小的两者之和。

---
如果这道题用$\texttt{std::sort}$来写，想必是非常轻松的。

但是，还是手写（运行）比较快，顺便还可以锻炼一下代码速度。

注意**准确分类讨论**：
- 因为存在有两个量相同的情况，各处比较都要加上$\texttt{=}$。
- 因为加上了$\texttt{=}$，可能存在同时满足多种情况，所以要用**else if**。

```cpp
#include <cstdio>
int main(){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    if(a<=b&&b<=c)printf("%d\n",a+b);
    else if(a<=b&&c<=b)printf("%d\n",a+c);
    else if(b<=a&&a<=c)printf("%d\n",a+b);
    else if(b<=a&&c<=a)printf("%d\n",b+c);
    else if(c<=a&&a<=b)printf("%d\n",a+c);
    else printf("%d\n",b+c);
}
```

---

## 作者：Kevin_Zhen (赞：1)

# 提供优先队列解法
题目链接 [AT2646](https://www.luogu.com.cn/problem/AT2646)。  
优先队列的解法可以无脑解出一部分较为简单的求最值的题目。  
与此题相似的题目还有 [P5718](https://www.luogu.com.cn/problem/P5718) 和 [P5724](https://www.luogu.com.cn/problem/P5724)。
## 题目大意
给你三个数 $a$、$b$ 和 $c$，输出其升序排列后前两项的和。
## 变量介绍
1. $q$ 是 $STL$ 中的小根堆，在此题中用于实现数列有序。
2. $ans$ 用于统计前两项的和。

## 解题过程
首先注意小根堆的声明。
```cpp
priority_queue<int, vector<int >, greater<int > > q;
```
然后输入三个数字，将其压入小根堆中。
```cpp
for (int i = 1; i <= 3; ++i) {
	int t;
	scanf("%d", &t);
	q.push(t);
}
```
因为小根堆内部已经有序了，所以 $ans$ 加上堆顶元素，然后弹出堆顶元素，再加上现在的堆顶元素即是答案。
```cpp
ans += q.top(); q.pop(); ans += q.top();
```
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

priority_queue<int, vector<int >, greater<int > > q;
int ans = 0;

int main() {
	for (int i = 1; i <= 3; ++i) {
		int t;
		scanf("%d", &t);
		q.push(t);
	}
	ans += q.top(); q.pop(); ans += q.top();
	printf("%d\n", ans);
	return 0;
}
```
## 感谢观赏！

---

## 作者：_Error (赞：1)

## 其实，这一题非常水，只是求两个最小数的和，所以我们只要找出最小的两个数便可以 了；
### 废话不多说，程序如下：
```cpp
//头文件
#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
int s[5];
int main()
{
 //无用的东西
 //freopen(".in","r",stdin);
 //freopen(".out","w",stdout);
 //读入（我用的是数组读入，这样用下面的sort不用打太多的判断条件)
 cin>>s[1]>>s[2]>>s[3];
 //排序
 sort(s+1,s+3+1);
 //输出最小的的两个数的和
 cout<<s[1]+s[2];
 //完美收场
 return 0;
}


```

---

## 作者：Graphcity (赞：0)

对于这道题，我们只需要求出 $\min(a,b,c)$ 加上 $\operatorname{mid}(a,b,c)$ 的值即可。

对于求 $\operatorname{mid}(a,b,c)$，可以转化为总和减去最大值和最小值。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c;
	int d,e,f;//d为最大值，e为中间值，f为最小值
	scanf("%d%d%d",&a,&b,&c);
	d=max(a,max(b,c));
	f=min(a,min(b,c));
	e=a+b+c-d-f;
	printf("%d\n",e+f);
    return 0;
}
```


---

## 作者：李之恒 (赞：0)

## 这一题其实只需要用**排序**，找到最小的两项相加即为答案。

下面给大家普及几种常见排序方法：
#### 1.归并排序
```cpp
int a[MM+11],ls[MM+11];
void msort(int l, int r) 
{
	if(l == r) return;
	int mid = (l + r) >> 1;
	msort(l, mid);
	msort(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while(i <= mid && j <= r)
		if(a[i] <= a[j]) ls[k++] = a[i++];
		else ls[k++] = a[j++];
	while(i <= mid) ls[k] = a[i], k++, i++;
	while(j <= r) ls[k] = a[j], k++, j++;
	for(int i = l;i <= r;i++) a[i] = ls[i];
}
```
#### 2.手写快排
```cpp
int a[100005];
void qsort(int l,int r)
{
	int i,j,tmp;
	if(l>=r)
	   return;
	i=l;
	j=r;
	tmp=a[i];
	while(i<j)
	{
		while(a[j]>tmp&&j>i) 
		   j--;
		if(i<j)
		{
		   a[i]=a[j];
		   i++;
		}
		while(a[i]<tmp&&i<j)
		   i++;
		if(i<j)
		{
		   a[j]=a[i];
		   j--;
		}
	}
	a[i]=tmp;
	qsort(l,i-1);
	qsort(i+1,r);
}
```
#### 3.冒泡排序
```cpp
for(int j = 1;j < n; j++)
	for(int i = 1;i <= n - j; i++)
		if(a[i] > a[i + 1])
			swap(a[i], a[i + 1]);
```
#### 4.插入排序
```cpp
for(int i = 2;i <= n;i++) {
	int p = i;
	while(p > 1 && a[p] > a[p - 1]) {
		swap(a[p], a[p - 1]);
		p--;
	}
}
```
#### 5.选择排序
```cpp
for(int i = 1;i < n;i++) {
	int maxx = a[i], p = i;
	for(int j = i + 1;j <= n;j++)
		if(a[j] > maxx) maxx = a[p = j];
	swap(a[i], a[p]);
}
```
### “条条大路通罗马”，排序方法各种各样，但不同的题目，往往是择优。

**这里我用的是STL库中的sort，方便快捷。**

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4];
int main()
{
	for(int i=1;i<=3;i++)
	    scanf("%d",&a[i]);
	sort(a+1,a+4);
	printf("%d\n",a[1]+a[2]);
	return 0;	    
}
```

---

## 作者：Aw顿顿 (赞：0)

一开始我以为是输出最小的两倍，结果 WA 了

然后讲一下三种方法：

1. 手动输入数组排序后输出前两项

sort 代码，可以很清楚的输出前两项：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[3];
	cin>>a[0]>>a[1]>>a[2];
	sort(a,a+3);
	cout<<a[0]+a[1]<<endl;
	return 0;
}
```


然后就是相对复杂一点的 if 版本，通过一些判断，分出三种输出情况，然后分别攻打测试点：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
    cin>>a>>b>>c;
    if((a<=b&&b<=c)||(b<=a&&a<=c))cout<<a+b;
    
    else if((a<=b&&c<=b)||(c<=a&&a<=b))cout<<a+c;
    else cout<<c+b;
    return 0;
}
```

那么我们再来看看求和之后使用 $\min$ 函数的，输出多有可能答案中的最小值：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,s1,s2,s3;
int main()
{
    cin>>a>>b>>c;
    s1=a+b;
    s2=b+c;
    s3=a+c;
    cout<<min(s1,min(s2,s3))<<endl;
    return 0;
}
```

那么今天的讲解就到这里了，谢谢大家！

---

## 作者：封禁用户 (赞：0)

看到每人发题解，我来发一篇   
其实这道题很好做，但是很多人都不理解意思   

大致意思：输入三个数，把最小的两个数加起来   

数组做法：
---   
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[2];//用数组更方便
int main()
{
 scanf("%d%d%d",&a[0],&a[1],&a[2]);//输入三个数
 sort(a,a+3); //直接快排
 printf("%d",a[0]+a[1]);//a[0]最大数，a[1]第二大
 return 0;
}
```
除了数组做法，还有不用数组的做法   
不用数组的做法：
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
 scanf("%d%d%d",&a,&b,&c);
 if(a<c&&b<c)cout<<("%d",a+b);
 if(a<b&&c<b)cout<<("%d",a+c);
 if(b<a&&c<a)printf("%d",b+c);
 return 0;
}
```

---

