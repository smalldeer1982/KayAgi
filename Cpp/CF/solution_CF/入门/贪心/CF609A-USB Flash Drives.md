# USB Flash Drives

## 题目描述

Sean正在把一个大文件考到n个U盘里。这个文件足有m MB那么大。第i个U盘的容量是a[i]。
假设Sean能把文件分装到多个U盘中，请求出他最少需要用多少个U盘来考这个文件。

## 样例 #1

### 输入

```
3
5
2
1
3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
6
2
3
2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
5
5
10
```

### 输出

```
1
```

# 题解

## 作者：Priori_Incantatem (赞：5)

很简单的贪心$+$模拟$+$排序

按U盘大小从大到小排序，优先选空间大的

每次如果文件还没存完，就挑一个剩下的空间最大的U盘来存  
如果已经存完了(m<=0)就输出已用U盘的数量

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MaxN=105;
int n,m,a[MaxN],ans;
bool cmp(int p1,int p2)
{
    return p1>p2;//从大到小排序
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    scanf("%d",&a[i]);
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;++i)
    {
        m-=a[i];
        ans++;//记录已用U盘的数量
        if(m<=0)break;//如果已经存完了就退出循环
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：lyclyc_NSP (赞：4)

本人@lyclyc 是第一个做出这一道题的，我就发布一篇题解，这一题只需要模拟就可以解决，先从大到小排序，再慢慢的模拟要用多少个U盘。
程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[10005],c;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    sort(a+1,a+n+1);//快速排序
    for(int i=n;i>=1;i--)//懒得从大到小排，就直接反过来循环。
    {
    	if(k-a[i]>0)k-=a[i],c++;//这里是判断如果装了一个还没装满的就增加一个U盘。
        else 
		if(k-a[i]<=0)
		{cout<<c+1<<endl;return 0;}//如果已经装完了，就加上这个U盘输出结果。
    }
    return 0;
}
```

---

## 作者：_cmh (赞：3)

~~淹死我了（在水中挣扎）~~

这题特别简单

其实本题做法就是

读入n，m，读入U盘容量，排序，从最大的开始加，看看最少几个超过m

上代码：

```cpp
#include<iostream>//头文件 
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int n,a[101],m,ans,tot;//定义U盘数量，U盘容量，文件的大小，最少需要几个U盘，目前容量 
int main(){
    cin>>n>>m;//读入U盘数量，文件的大小
    for(int i=1;i<=n;i++) cin>>a[i];//读入U盘容量 
    sort(a+1,a+n+1);//排序 
    for(int i=n;i>=1;i--){//从最大的开始加 
    	ans++;//用掉一个U盘 
    	tot+=a[i];//加上容量 
    	if(tot>=m){//如果容量够了 
    		cout<<ans;//输出最少需要几个U盘
    		return 0;//直接结束 
		}
	}
}
```

## 求赞！！！

~~(蒟蒻已经逃跑了，没法和泥萌说再见了)~~

---

## 作者：gzw2005 (赞：2)

这道题就是说，在一个 $N$ 个数数组中，选尽可能少的数，使得这几个数的和大于或等于 $M$。

明显就是贪心——先选大的数。那为什么这种贪心策略是对的呢？下面是一个粗略的证明（临时想出来的）：

首先，为了方便，我们把这个长度为 $N$ 的数组定义成 $a[]$

定义一个函数 $f(M)$ ，这个函数就是在 $a[]$ 中，选尽可能少的数，使得这几个数的和大于或等于 $M$，这个至少数量就是 $f(M)$。

去求 $f(M)$ 时，可以分类讨论：

1. 假设我们选了 $a[i]$，接下来就变成了求 $f(M-a[i])+1$ 的问题；

2. 再假设我们选了 $a[j]$（$i\neq j$），但 $a[i]>a[j]$，那么接下来就变成了求 $f(M-a[j])+1$ 的问题。

但如何比较 $f(M-a[i])+1$ 和 $f(M-a[j])+1$ 的大小（也就是两种方案的优劣）呢？

容易知道在函数 $f(M)$ 中，当 $M$ 越大，$f(M)$ 也越大，**所以 $f(m)$ 是一个增函数**。

因为 $a[i]>a[j]$

所以 $M-a[i]<M-a[j]$

根据增函数的定义，$f(M-a[i])<f(M-a[j])$

即 $f(M-a[i])+1<f(M-a[j])+1$

所以，选第一种方案，也就是优先选更大的数更优。

如果看不懂就算了。现在，你就只需知道这种贪心策略是正确的。（fstqwq：主要是你谷上有老下有小我也很难过呀

程序：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[102];
bool cmp(int num1,int num2){
	return num1>num2;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n,cmp);//从大到小排序 
	for(int i=1;i<=n;i++){
		if(a[i]>=m){
			cout<<i;//输出个数 
			return 0;
		}
		m-=a[i];
	}
	return 0;
}
```

---

## 作者：thename (赞：1)

此题略水，本人题解适合萌新食用，大佬勿喷。

```
#include<iostream>
#include<algorithm>
using namespace std;
int ans,a[100010],b,n,m;
int main()
{
	cin>>n>>m;//输入m，n 
	for(int i=0;i<n;i++)//输入各个u盘容量 
		cin>>a[i];
	sort(a,a+n);//从小到大进行排序 
	while(m>0)//循环计数 
	{
		n--;//n为数组下标 
		m-=a[n];//计算还差多少容量 
		ans++;//记录U盘数量 
	}
	cout<<ans;//输出 
	return 0;//结束 
}
```


其实这道题的思路很简单，循环计数就OK啦

本题我分为了四部分来解：

**一、输入部分（~~废话，各位大佬可以无视~~）输入计算所需值**

```
	cin>>n>>m;//输入m，n 
	for(int i=0;i<n;i++)//输入各个u盘容量 
		cin>>a[i];
```
**二、排序部分，由于本人比较懒就没用方法，直接用了algorithm中的sort（~~STL严重依赖~~）**

```
sort(a,a+n);//从小到大进行排序
```

**三、循环计数，依次计算所需个数**

```
	while(m>0)//循环计数 
	{
		n--;//n为数组下标 
		m-=a[n];//计算还差多少容量 
		ans++;//记录U盘数量 
	}
```

**四、输出部分（~~废话，各位大佬可以无视~~），输出所需个数**

```
	cout<<ans;//输出
```


---

## 作者：北雪2009 (赞：0)

~~这道题真的是太暴力了！！！~~   
这道题只需要枚举u盘就行了。   
先sort从大到小排序一次，然后从第一个开始枚举，每次用u盘空间减去文件大小并且记录，直到文件被装完，就输出记录完的变量。   
附上代码：   
```cpp
#include<bits/stdc++.h>   //万能头
#include<stdio.h>
using namespace std;
int n,m,a[100+5],ans;   //定义
bool cmp(int a,int b){return a>b;}    //为后面的sort从小到大排序打好地基
int main(){
	ios::sync_with_stdio(false);  //cin,cout快读快输
    cin>>n;
    cin>>m;   //读入
    for(int i=1;i<=n;i++)   //循环读入
    	cin>>a[i];
    sort(a+1,a+n+1,cmp);   //从小到大排序
    for(int i=0;m>0;)   //循环处理文件
    	m-=a[++i],ans++;   //最最最关键的处理
    cout<<ans;   //输出
    return 0;    //结束
}
```


---

## 作者：封禁用户 (赞：0)

# CF609A USB Flash Drives 题解

**注：如果你想了解更多的排序算法，请看[这里](https://zyy-txws-noip.blog.luogu.org/p1177-mu-ban-kuai-su-pai-xu-ti-xie)**

题目中给我们的条件就是要尽量少的使用 u盘，我们可以有这样的思路：

- 先给题目中给的U盘的存储量**从大到小**排序，排序之后即可。
- 排完序，去从大容量的U盘开始找，看看要多少个U盘。
- 输出最后算出的答案


代码：
```cpp
#include<bits/stdc++.h>//万能头文件❤
using namespace std;//using不多说
bool cmp(int a,int b)//改变sort的排序方法，从大到小（等下具体说）
{
    return a>b;//返回排序值
}
int main()
{
    int n,m,a[10001];//定义不多说
    cin>>n>>m;//输入不多说
    for(int i=1;i<=n;i++) cin>>a[i];//输入
    sort(a+1,a+n+1,cmp);//这里快排后面有一个参数,cmp表示从大到小
    int tmp=0,cnt=0;//计数器注意置零
    for(int i=1;i<=n;i++)//从最大的开始枚举
    {
        cnt++;//每一次u盘的数量+1
        tmp+=a[i];//这里是一个零时变量，看看这个时候存了多少内容
        if(tmp>=m) break;//如果内容比装的东西多了，退出循环
    }
    cout<<cnt;//直接输出
    return 0;//华丽结束
}
```


------------

# 补充

刚刚我们看代码里面有这一段：
![](https://cdn.luogu.com.cn/upload/image_hosting/6mzmfv8z.png)

有同学会问，这个要怎么用呢？其实，是用在了sort函数里面

![](https://cdn.luogu.com.cn/upload/image_hosting/iadaq1hl.png)

这里的sort允许加上第三个变量，表示从大到小排序，这是可以的，复杂度 $O(nlogn)$ **是一维数组排序最快的算法**。

如果sort里面只有两个参数，就说明自动**从小到大**排序。



------------


学会了吗？

[Thomas_ 的博客](https://zyy-txws-noip.blog.luogu.org/)

原创，侵权必究

---

## 作者：moqizhu2005 (赞：0)

# 贪心思想：先用大的U盘
## 所以，用sort排序后从n开始搜就可以了
### 输出注意：因为前面多了一个k--,所以只要输出n-k即可
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,m,a[101],k;
int main()
{
	cin>>n>>m;
	k=n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	while(m>0)
	{
		m-=a[k];
		k--;
	}
	cout<<n-k;
	return 0;
}
```


---

## 作者：judgejudge (赞：0)

# 贪心算法


------------

其实这就是一道比较简单的**贪心**，我们的大致思路是这样的：

1. 把给的U盘空间进行**排序**，当然从小到大，从大到小均可，只是都要做一些修改。
1. 从最大的开始判断，**如果需要储存的大于0，那么令其为k，k-=U盘空间。**
1. else部分，输出并且**return 0**

下面奉上代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[10000];
int main(){
    int i,j,k,n,sum=0;
    cin>>n>>k;
    for(i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(i=n;i>=1;i--)
    if(k>0){
        k-=a[i];
        sum++;
    }
    else{
        cout<<sum<<endl;
        return 0;
    }
}
```
不知道有没有这样提交上去的？其实这个代码过不了样例2！！

**原因是到最后一次时k仍然大于0，等到k==0时for语句已经执行结束！！**

因此我们只需要**麻烦一点**，在最后输出即可：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[10000];
int main(){
    int i,j,k,n,sum=0;
    cin>>n>>k;
    for(i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(i=n;i>=1;i--)
    if(k>0){
        k-=a[i];
        sum++;
    }
    else{
        cout<<sum<<endl;
        return 0;
    }
    cout<<sum<<endl;
    return 0;
}
```
当然有看官会想了：
### 如果有方法不用重新打会多好？
当然有！！**问题是出在for语句，我们只需要在for语句上修改一个数字！**

```cpp
for(i=n;i>=0;i--)//我们只需要把1改成0，这样因为定义全局变量
//a[0]为0，所以我们不需要担心它会进行题目中储存空间，并且这样就多一次判断
//可以直接输出！！
	if(k>0){
		k-=a[i];
		sum++;
	}
	else{
		cout<<sum<<endl;
		return 0;
	}
```
所以简练的AC代码出来了：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[10000];
int main(){
	int i,j,k,n,sum=0;
	cin>>n>>k;
	for(i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(i=n;i>=0;i--)
	if(k>0){
		k-=a[i];
		sum++;
	}
	else{
		cout<<sum<<endl;
		return 0;
	}
} 
```

---

## 作者：_lyc233 (赞：0)

## P党题解！
------------
要用最少的U盘拷文件，U盘容量自然是越大越好。 —— 由大到小排序

如果最大容量的U盘拷不下，就把容量第二大的U盘拿上来拷，还不行就把第三只拿上来继续拷......以此类推。 —— 循环处理

于是这道题目的代码结构就十分清晰了：
    
      1.输入
      2.由大到小排序
      3.寻找最小要几只U盘并存入i
      4.输出i

------------
代码：
```pascal
var
  a:array[1..100] of longint;
  i,j,k,n,m,s:longint;
  
procedure swap(x,y:longint);  //交换
var
  t:longint;
begin
  t:=x;x:=y;y:=t;
end;

begin
  readln(n);  //Sean有N个U盘
  readln(m);  //Sean要拷一个大文件，文件的大小是m个MB
  for i:=1 to n do readln(a[i]);  //Sean的第i个U盘有a[i]个MB
  for i:=1 to n-1 do
   begin
     k:=i;
     for j:=i+1 to n do
      if a[k]<a[j] then k:=j;  //找一找a[i]后面有没有比a[i]要大的。（注：k=i or k=j）
     if k<>i then swap(a[k],a[i]);  //如果k变了就说明当前的a[i]不是第i大的，第i大的是a[k]，所以要交换
   end;  //改进选排（由大到小）
  i:=0;
  repeat
    i:=i+1;
    s:=s+a[i];
  until s>=m;  //如果前i个U盘容量总和大于等于m就退出
  write(i);  //repeat循环结束后的i就是最少需要U盘的数量
end.
```
------------
文明洛谷，~~珍惜生命~~，勿抄题解。

---

