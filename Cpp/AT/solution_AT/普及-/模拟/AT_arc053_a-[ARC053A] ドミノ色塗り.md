# [ARC053A] ドミノ色塗り

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc053/tasks/arc053_a



# 题解

## 作者：Rulu (赞：8)

#### 蒟蒻的第一篇题解！
- - - - - - - - - - 
我们先拿这张2×3图分析:（行为h，列为w）
![](http://arc053.contest.atcoder.jp/img/arc/053/irohachankawaii/domino_1.png)

可以将此矩阵分为2类：
- - - 
第1类：横放的1*2的矩形

每行有(w-1)种放法，有h行  
共(w-1)*h种放法

第2类：竖放的1*2的矩形

每列有(h-1)种放法，有w列  
共(h-1)*w种放法
- - - - - - - - 
让我们再拿这张4*1图验证:

![](http://arc053.contest.atcoder.jp/img/arc/053/irohachankawaii/domino_2.png)

也可以将此矩阵分为2类：
- - - - - - 
第1类：横放的1*2的矩形

这个矩阵只有1列，所以没有放法

第2类：竖放的1*2的矩形

每列有(h-1)种放法，有w列  
共(h-1)*w种放法
- - - - - - - - 
综上，可得出总放法为：

#### (w-1)*h+(h-1)*w
- - - - 
#### 当然，这个h行w列的矩阵不得小于1*2

那么还要加上判断： 

如果(h==1&&w==1)||h==0||w==0，则输出0
- - - - - - - - - - 
代码：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int h,w;//h为行，w为列
	cin>>h>>w;//输入h和w
	if((h==1&&w==1)||h==0||w==0)//判断 
	{
		cout<<0;
		return 0;
	}
	cout<<(w-1)*h+(h-1)*w;//求放法 
    return 0;
} 
```



#### 完结撒花~（疯狂暗示 QwQ

---

## 作者：智子·起源 (赞：2)

### 对于这道题，我啥都没想，直接暴枚，连公式都没推。

### 直接双for枚举横着放的可能性与竖着放的可能性。
```cpp
#include<iostream>
using namespace std;
int ans,n,m;
int main()
{
  cin>>n>>m;
  for(int i=1;i<n;i++)
    for(int j=1;j<=m;j++)
      ans++;
  for(int i=1;i<=n;i++)
    for(int j=1;j<m;j++)
      ans++;
  cout<<ans<<endl;
  return 0;
} 
```
对于比赛或考试，这样做是最保险的。^_^

---

## 作者：ljxljxljx (赞：1)

提供一种   ~~**小学**~~  数学方法



------------

https://cdn.luogu.com.cn/upload/pic/26677.png

拿这张2×3图举例:

第一种 横向1×2；第二种  竖向1×2；

一·在第一横排中有(w-1)个1×2 ，有h个横排，共有h×(w-1)个1×2；

二·在第一竖排中有(h-1)个1×2   ，有w个竖排，共有w×(h-1)个1×2；



------------

综上所述，我们只需输入h与w，输出h×(w-1)+w×(h-1)就可AC。






Code：

    #include<cstdio>
    using namespace std;
    int main()
    {
        int h,w; 
        scanf("%d%d",&h,&w);
        printf("%d\n",2*h*w-h-w);
        return 0;
    }


P党就自己写吧。

由于本人Markdown不会用，且行与列分不清，请多多包涵。

---

## 作者：LZH_LOVE_ZRG (赞：0)

首先来读题面，题目问：

在 $n$ 行 $m$ 列的长方形中有多少种方法放一个 $1\times 2$ 的长方形。

分析题意，

有横与竖 $2$ 种放法，可以分别处理。

由此想出了两种做法：

## Solution $1$
朴素的模拟做法，分别枚举横与竖的方案。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n;
    int m; cin>>m;
    int ans=0;
    for(int i=1;i<n;i++)//横
        for(int j=1;j<=m;j++)
            ans++;
    for(int i=1;i<=n;i++)//竖
        for(int j=1;j<m;j++)
            ans++;
    cout<<ans;
    return 0;
}

```
## Solution $2$
小学数学题：

+ 因为横着放时只能放 $n-1$ 行 $m$ 列，因此贡献是 $(n-1)\times m$
+ 因为竖着放时只能放 $n$ 行 $m-1$ 列，因此贡献是 $n\times (m-1)$

把这两个数相加就能求得答案。

当然，因为这个大长方形必须大于 $1\times 2$，

所以要特判 $n\times m<1\times 2$ 的情况。

别问我怎么知道的！

代码：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n;
    int m; cin>>m; 
    cout<<(n==1||m==1?0:(n-1)*m+n*(m-1));
    return 0;
}
```

## 完结撒花！

---

## 作者：WHJ___ (赞：0)

为了发现结论，我们先将题目特殊化：

在一个 $W*1$ 的矩形（这个矩形是横着的）中，有多少个本质不同的 $1*2$ 矩形。那么很明显，相邻的两个格子可以构成一个这样的小矩形，首尾不能相接，所以在 $W*1$ 的矩形中，应当有 $W-1$ 个这样的矩形。

如果把 $W*1$ 改为 $1*H$（这个矩形是竖着的），那么根据上一段的结论也可以知道在 $1*H$ 的矩形中，应当有 $H-1$ 个这样的矩形。

这样我们可以推广到 $W*H$ 的矩形，每一行都有 $W-1$ 个横着的 $1*2$矩形，所以 $H$ 行共有 $H(W-1)$ 个横着的 $1*2$ 矩形。
同理，每一列都有 $H-1$ 个竖着的 $1*2$ 矩形，所以 $W$ 列共有 $W(H-1)$ 个 $1*2$ 矩形，那么答案就是两者之和：$H(W-1)+W(H-1)$。

代码：

```cpp
#include<bits/stdc++.h>
#define I long long
#define RI register int
#define il inline
#define rt return
using namespace std;
const int N=1e+7;

I h,m;

il I d(){
	I x=0,f=1;
	char c=0;
	while(!isdigit(c=getchar()))f-=(c=='-')*2;
	while(isdigit(c)){x=(x<<1)+(x<<3)+f*(c-48);c=getchar();}
	rt x;
}

signed main()
{
	RI i,j;
	h=d();m=d();
	cout<<(h-1)*m+(m-1)*h;
	rt 0;
}

```


---

## 作者：梦游的小雪球 (赞：0)

## 梦雪的思路：
- ### 分成横的和竖的两部分计算（注a为行，b为列）
	1. 横：（a-1）*b
   2. 竖：（b-1）*a
   3. 最后加起来：(a-1)*b+(b-1)*a
   
## AC代码

```
#include<bits/stdc++.h>
using namespace std;
int a,b,s;
int main(){
	cin>>a>>b;
	cout<<(a-1)*b+(b-1)*a<<endl;
	return 0;
}
```
~~我已经很努力地凑字数了QWQ~~

---

## 作者：きりと (赞：0)

## 经典推公式题

先上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int h,w;
	cin>>h>>w;
	cout<<(h-1)*w+(w-1)*h<<endl;
}
```

这题yysy就是给入门的萌新练习如何快速，准确地推出数学公式。

先讲一下此题的公式推法：

首先，考虑每行，将$1×2$的方格填入$1×W$的方块中，易得能填$w-1$个（可见样例2）

因为有N列,so，$N×(W-1)$即可。

但不要忘记，$1×2$的方格可横放和竖放，所以要再加上$W×(N-1)$

接下来我们总结一下简单数学问题（红橙黄）的主要步骤：

- 分析题意，观察样例

- 从样例中寻找规律，较难题则需要自己在草稿纸上演算，找出解题公式or方法

- 利用公式或方法，实现相对应的程序

- 造数据，验证自己的数学猜想

---

## 作者：empty (赞：0)

~~讲真，我在我弟的小学奥数书上见过类似的题目，而且那题比这个难，那题不止要找1×2的长方形……~~   
咳咳……直接上代码吧，楼下已经详细的分析过了。
```pascal
var h,w:integer;
begin
 read(h,w);
 write(2*h*w-h-w);
end.
```

---

## 作者：Forward_Star (赞：0)

超级大水题。
求出每个格子相邻格子数的总和，最后除以二即可。
博客：https://blog.csdn.net/weixin_39872717/article/details/81145384

---

