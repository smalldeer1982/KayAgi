# The Pleasant Walk

## 题目描述

There are $ n $ houses along the road where Anya lives, each one is painted in one of $ k $ possible colors.

Anya likes walking along this road, but she doesn't like when two adjacent houses at the road have the same color. She wants to select a long segment of the road such that no two adjacent houses have the same color.

Help Anya find the longest segment with this property.

## 说明/提示

In the example, the longest segment without neighboring houses of the same color is from the house 4 to the house 7. The colors of the houses are $ [3, 2, 1, 2] $ and its length is 4 houses.

## 样例 #1

### 输入

```
8 3
1 2 3 3 2 1 2 2
```

### 输出

```
4
```

# 题解

## 作者：DeepSkyBlue__ (赞：2)

这是一道简单的膜你题，要求我们输出最长的一段，使得没有相邻两个数相等。

那么直接存在数组里，扫一遍再打擂台就可以了。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001]={0};//第一次开了1001，然后RE了
int main()
{
	int n,k;
	cin>>n>>k;//k并没有什么用
	int ans=0;
	int ma=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==a[i-1])ans=1;//如果相邻数一样了，ans归1
		else ans++;//否则连续段长度+1
		if(ma<ans)ma=ans;//打擂台记录最大值
	}
	cout<<ma<<endl;//输出最大值
	return 0;
}
```


---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1090M)


------------


### 分析与思路

这道题其实是要你求其中最长的连续一段序列，这段序列中的任意相邻两数必须不同。

我们需要用一个数组，每次输入数组时记录当前数组中的元素是否与前一个数字不同，不同就加一，如果相同的话就重新设置为一，每次循环结束后都要来取最大值。

我们一步一步来实现。



------------
### 代码实现

1. 每次输入数组时，记录当前数组的元素是否与前一个数字不同。

这一部分比较容易操作，我们可以用异或来完成此操作。

异或：如果 ```a``` 、 ```b``` 两个值不相同，则异或结果为一。如果 ```a``` 、 ```b``` 两个值相同，异或结果为零。

```
for(int i=1;i<=n;i++){
    cin>>a[i];
    if(a[i]^a[i-1]){
        
    }else{
    
    }
}
```

2. 不同就加一，否则设为一。

这部分只需要基础的判断一下就好了。

```
if(a[i]^a[i-1])sum++;
else sum=1;
```

3. 每次循环后要取长度的最大值。

```
for(int i=1;i<=n;i++){
    cin>>a[i];
    if(a[i]^a[i-1])sum++;
    else sum=1;
    maxn=max(maxn,sum);
}
```

最后输出，搞定!


------------
### 完整 ```AC``` 代码:

```
#include<iostream>
using namespace std;
int a[100001],n,k,sum,maxn;
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]^a[i-1])sum++;
        else sum=1;
        maxn=max(maxn,sum);
    }
    cout<<maxn<<endl;
    return 0;
}
```


---

## 作者：一只大龙猫 (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1090M)

先来看看题目：

- 有一长度为 $n$ 的数列 $a_{1},a_{2},a_{3},...,a_{n}$，其中每个数的值都小于等于 $k$。

- 现给定 $n$，$k$ 和这个数列，求其中最长连续的一段区间的长度，使区间中任意相邻两数不同。

- 数据范围：$1≤n,k≤100000$。

这题可以用动态规划去做。

设 $f(i)$ 为是以 $a_{i}$ 为结尾的最长区间长度，则易推出转移方程：

- 若 $a_{i}=a_{i-1}$，则 $f(i)=1$；

- 否则 $f(i)=f(i-1)+1$。

而答案即等于 $\max(f(1),f(2),f(3),...,f(n))$。

**综上，便可以写出代码：**

```cpp
#include<iostream>
using namespace std;
int n,k,a[100001],f[100001],ans; 
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i]=1;                          //见下文 
	}
	for(int i=1;i<=n;i++){
		if(a[i]!=a[i-1])f[i]=f[i-1]+1;   //f[i-1]最少是1，所以f[i-1]+1肯定比f[i]的初始值1大 
		ans=max(ans,f[i]);              
	}
	cout<<ans;
	return 0;
}
```

### **Q&A**

Q：```f[i]=1```是什么意思？有什么作用？

A：这一句看似仅将 $f$ 数组初始化为1，实际上还是转移方程的第一条。如果没有这一句，下面的```if```语句本来应该是：

```cpp
if(a[i]!=a[i-1]){
	f[i]=f[i-1]+1;
}else{
	f[i]=1;
}
```

加上这条语句后便可省略```else```语句。

---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的数组 $a_1,a_2,a_3,...,a_n$，并已知有 $k$ 个不相同的元素求最长连续的一段区间，使得这里面的元素互不相同。

**数据范围：$1\leqslant n\leqslant 10^5,1\leqslant a_i\leqslant k\leqslant 10^5$。**
## Solution
我们可以直接记录当前的元素是否和前面的不同，不同答案加 $1$，否则取最大值之后回到初始值。

注意，初始值为 $1$，因为一开始有 $1$ 个元素。
## Code
```cpp
int n, k, a[100007], ans = 1, maxi; 

int main() {
	getint(n), getint(k);
	_for(i, 1, n) {
		getint(a[i]);
		if(i != 1 && a[i] != a[i - 1])	ans++;
		else {maxi = max(maxi, ans); ans = 1;}
	}
	maxi = max(maxi, ans); 
	writeint(maxi);
	return 0;
}
```

---

## 作者：happybob (赞：0)

STL大法好，~~数组不也能用吗……~~

模拟题目，我使用的是vector，跑的还挺快的，772ms，目前最优解！

代码里有注释

```cpp
#include <cstdio>
#include <vector>//vector头文件
using namespace std;

vector <int> vec;//定义vector

int main()
{
	int n, ans = 0, x = 0, k;
	scanf("%d %d", &n, &k);//读入
	vec.resize(n);//将vec的元素大小设为n
	for(vector <int>::iterator it = vec.begin(); it != vec.end(); ++it)//迭代器访问
	{
		scanf("%d", &*it);//通过*迭代器名访问
		if(*it == *(it - 1))//如果相邻两个元素一样
		{
			x = 1;//x变为1，不是0
		}
		else
		{
			x++;//否则x自增1
		}
		ans = x > ans ? x : ans;//三目运算符，如果x比ans大，ans等于x，否则ans不变，相当于打擂台
	}
	printf("%d\n", ans);
	return 0;//养成好习惯哦
}
```

求过

---

## 作者：lu_run_ting (赞：0)

题意：

有一个序列，求最长不相等子序列。

分析：

很简单的模拟，我们需要维护变量cnt，它代表当前这个不相等子序列的长度，分两种情况：
+ 当与上一个不相等时，cnt+1
+ 当遇上一个相等的时候，先更新一下（与目前最长的比较长度），然后cnt=1，因为当前这个数他本身就是个序列，因该算进去。

易错点：我和其他两位大佬的题解差不多，只是来补这个易错点的。我一开始用的是只有当整个序列结束之后再更新，然而错了一个点，因为当最后一个序列延伸到序列尾部的时候，就会不更新，所以当最后一个带尾子序列最大的时候，我们就没有算进去。   
如果想要不犯这个错误，有两种方法：   
1.  要在循环结束之后在判断一遍，是不是最后一个才是最大的；
2.  直接换一种方法，每次都统计一下，不一定要到结尾的时候。（推荐b(￣▽￣)d）

代码版本1（结束之后再更新）：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,a,b,cnt,ans;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a!=b) cnt++,ans=max(ans,cnt);
		else cnt=1;
		b=a;
	}
	ans=max(ans,cnt);
	cout<<ans<<endl;
	return 0; 
}  
```


代码版本2（每次都更新）：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,a,b,cnt,ans;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a!=b) cnt++;
		else cnt=1;
		b=a;
		if(cnt>ans) ans=cnt;
	}
	cout<<ans<<endl;
	return 0; 
}  
```

---

## 作者：da32s1da (赞：0)

按题意模拟即可。

从前往后扫一遍，遇到相邻颜色相同的房子就重新统计答案。

```
#include<cstdio>
int n,k,x,y,ans;
int main(){
	scanf("%d%d",&n,&k);k=0;//颜色数量没用。。
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(x!=y)++k;//颜色不同，可以选
		else k=1;//颜色相同，可选后面的
		y=x;
		if(ans<k)ans=k;//更新答案
	}
	printf("%d\n",ans);
}
```

---

