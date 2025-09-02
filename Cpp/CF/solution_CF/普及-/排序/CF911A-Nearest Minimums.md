# Nearest Minimums

## 题目描述

You are given an array of $ n $ integer numbers $ a_{0},a_{1},...,a_{n-1} $ . Find the distance between two closest (nearest) minimums in it. It is guaranteed that in the array a minimum occurs at least two times.
找到一个长度为n的序列中，距离最短的最小值的距离。

## 样例 #1

### 输入

```
2
3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
5 6 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
9
2 1 3 5 4 1 2 3 1
```

### 输出

```
3
```

# 题解

## 作者：归褯雾嵊 (赞：4)

大水题
额，题意在这里就不做阐述了
简述一下我的做法
就是简单的枚举，找到最小值以后，记录它的位置，再枚举一遍就ok啦。。。。。。
```
#include<bits/stdc++.h>//个人比较喜欢用万能库
using namespace std;
int a[100001];//这个数组用来输入数据。。。
int wz[100001];//记录最小值所在位置（数组貌似开大了点，反正数据水，不会有问题）
int main()
{
	int n,total=1;
	int zx=1000000000;
	int jl=100000;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(zx>a[i])
		zx=a[i];//把最小值搞出来
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==zx)
		wz[total++]=i;//是时候动用伟大的wz（位置）~》汉语拼音无敌《~数组
	}
	for(int i=2;i<total;i++)
	{
		if(jl>wz[i]-wz[i-1])
		jl=wz[i]-wz[i-1];//这是不是可以按位枚举，直接找最小距离拉~~
	}
	cout<<jl;
}
```
![](C:\Documents and Settings\yz\桌面)

---

## 作者：da32s1da (赞：3)

不用数组的做法。

读入一个数$x$，若比当前最小值小，更新最小值，答案清空，记录位置。

若与当前最小值相同，更新答案，记录位置。

```
#include<cstdio>
const int inf=1e9+7;
int minn,wz,n,x,ans;
int main(){
	scanf("%d",&n);
	minn=inf;ans=n;//初始化最小值和答案
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(minn==x&&ans>i-wz)ans=i-wz;//与最小值相同，更新答案
		if(minn==x)wz=i;//记录位置
		if(minn>x)minn=x,wz=i,ans=n;//小于最小值，更新最小值，答案清空，记录位置
	}
	printf("%d\n",ans);
}
```

---

## 作者：vectorwyx (赞：2)

这道题真的好水啊


------------
思路很简单：

先扫一遍数组，找出最小值

再扫一遍数组，**不断和最小值比对**

**找到最小值就更新一下距离**，看看它是不是目前的最短距离

然后呢？没有然后了。

没错，这道题就是这么水

------------
轻松AC后，我们就琢磨一下高端点的做法

当然是**用vector存距离**啊！

第一步操作还是找最小值

但第二步，我们每发现一个最小值，就把它的下标压进vector里

然后扫一遍vector，找出相邻两元素的最小差值

输出，搞定！

思路大体不变，但顿时高端了许多有木有？


------------
代码来了~
```cpp
#include<iostream>
#include<vector>
#include<cstdio>
#define maxn 100001//近乎万能的宏定义，这是数组大小
#define maxx 0x7fffffff//这是int类的最大值
using namespace std;
int a[maxn];
vector<int> wyx;//定义vector（有没有发现是我的名字！）
int main(){
	int n,mn=maxx,l,ans=maxx;
    //mn是数组元素的最小值，ans是距离的最小值
	cin>>n;
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);//照样scanf加快速度
		if(a[i]<mn) mn=a[i];//更新最小值
	}
	for(int i=1;i<=n;++i){
		if(a[i]==mn){//快看！是最小值！
			wyx.push_back(i);//赶紧压进去入伍
		}
	}
	l=wyx.size();//取大小
	for(int i=1;i<l;++i){//要从下标1开始与前一个比较
		if(wyx[i]-wyx[i-1]<ans){//更新距离的最小值
			ans=wyx[i]-wyx[i-1];
		}
	}
	cout<<ans;//出来吧！距离的最小值！
	return 0;
} 
```


------------

（话说这道题有140个测试点啊！~~还让人活吗？~~）

---

## 作者：引领天下 (赞：2)

其实此题只用一个排序和一个id就能解决问题

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans=INT_MAX;
struct ${
    int s,id;
}a[100005];//结构体
inline bool cmp($ p,$ q){
    if (p.s!=q.s)return p.s<q.s;
    return p.id<q.id;
}//排序
int main(void){
    scanf ("%d",&n);
    for (int i=0;i<n;i++)scanf ("%d",&a[i].s),a[i].id=i;
    sort (a,a+n,cmp);
    for (int i=0;i<n&&a[i].s==a[i+1].s;i++)ans=min(ans,a[i+1].id-a[i].id);//找最小值
    printf ("%d",ans);
}
```

---

## 作者：ian_ian (赞：1)

这个是c++的代码,允许抄袭、复制,但是要担心成为作弊者,学术诚信最重要!!!
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];//待会输入要用cin>>a[i];因为之前一直用这个,所以继续使用,方便我做题; 
int b[100001];//b=这些重复的最小值的位置;
int n;//长度为n; 
int c=1;//总计; 
int k=1000000000;//10的9次方;
int ans=100000;//10的5次方;
int main()
{
    cin>>n;//输入; 
    for(int i=1;i<=n;i++)//桶排; 
    {
        cin>>a[i];
        if(k>a[i])
        k=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]==k)
        b[c++]=i;
    }
    for(int i=2;i<c;i++)//前面是1,现在从2开始; 
    {
        if(ans>b[i]-b[i-1])
        ans=b[i]-b[i-1];//距离的算法---最近减最近 
    }
    cout<<ans;//输出 
}
```
//具体的解析已在程序里说了,应该都懂吧?

---

