# Playing with Paper

## 题目描述

One day Vasya was sitting on a not so interesting Maths lesson and making an origami from a rectangular $ a $ mm $ × $ $ b $ mm sheet of paper ( $ a>b $ ). Usually the first step in making an origami is making a square piece of paper from the rectangular sheet by folding the sheet along the bisector of the right angle, and cutting the excess part.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527A/919759a22ff5597b60d204c65faf22c2233113ef.png)After making a paper ship from the square piece, Vasya looked on the remaining $ (a-b) $ mm $ × $ $ b $ mm strip of paper. He got the idea to use this strip of paper in the same way to make an origami, and then use the remainder (if it exists) and so on. At the moment when he is left with a square piece of paper, he will make the last ship from it and stop.

Can you determine how many ships Vasya will make during the lesson?

## 说明/提示

Pictures to the first and second sample test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527A/8a10deb3e516fda81e76aae552290cb4cf3649c8.png)

## 样例 #1

### 输入

```
2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 7
```

### 输出

```
6
```

## 样例 #3

### 输入

```
1000000000000 1
```

### 输出

```
1000000000000
```

# 题解

## 作者：LW_h_FP (赞：3)

这题开始时想到的是模拟它每次减去的过程就可以了，用一个while循环一直到其中一个为0结束

```
while(a!=0&&b!=0){
		if(a<b) swap(a,b);
		a-=b,ans++;
}
```

代码如上，但是显然不行，就第三个样例就知道了，会有大的那个数会大小的很多倍，所以干脆直接一次减去倍数就可以了


```
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	long long a,b,ans=0; cin>>a>>b;
	while(a!=0&&b!=0){
		if(a<b) swap(a,b);
		ans+=a/b,a-=b*(a/b);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：GusyNight (赞：1)

***本题解由 缘，为何物？ 提供~~~***

**Hi**

**这是我的第12篇题解!**
```
先介绍一个函数，
用来写这道题目，
这个函数就是"PlayingwithPaper";
```
```cpp
int PlayingwithPaper(){
	long long temp=n1/n2;
	ans=ans+temp;
	n1=n1-n2*temp;
}
```
**然后，只要判断有没有使n1,n2有没有都等于0就可以退出**
```
方法一：
while()
```
```cpp
while(1){
		if(n1<n2){
			long long s1=n1,s2=n2;
			n1=s2,n2=s1;
		}
		PlayingwithPaper();
		if(n1==0&&n2==0){
			break;
		}
	}
```
```
方法二:
for(;;)
```
```cpp
for(;n1!=0&&n2!=0;){
		if(n1<n2){
			long long s1=n1,s2=n2;
			n1=s2,n2=s1;
		}
		PlayingwithPaper();
	}
```
AC代码
=
```cpp
#include<bits/stdc++.h>
#define TP int
using namespace std;
inline TP read(){
    char c=getchar();
    TP x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
long long n1=read(),n2=read(),ans=0;
int PlayingwithPaper(){
	long long temp=n1/n2;
	ans=ans+temp;
	n1=n1-n2*temp;
}
int main(){
	for(;n1!=0&&n2!=0;){
		if(n1<n2){
			long long s1=n1,s2=n2;
			n1=s2,n2=s1;
		}
		PlayingwithPaper();
	}
    cout<<ans;
    return 0;
}
```

---

## 作者：Tiago (赞：0)

[博客食用更佳](https://www.luogu.com.cn/blog/Q--w--Q/solution-cf527a)

看到这道题目之后，便想到肯定是模拟，就打出了以下程序：

```
var
 a,b,s,t:longint;
begin
 readln(a,b);
 while not((a=0)or(b=0)) do
  begin
   if a<b then begin t:=a;a:=b;b:=t; end;
   inc(s);
   a:=a-b;
  end;
 write(s);
end.
```
然而RE了
![](https://s1.ax1x.com/2020/04/26/JgBFZ8.md.png)

我又仔细的看了看题目，发现了一个重点：
![](https://s1.ax1x.com/2020/04/26/JgDJ78.png)

于是改了改程序：
```
var
 a,b,s,t:int64;
begin
 readln(a,b);
 while not((a=0)or(b=0)) do
  begin
   if a<b then begin t:=a;a:=b;b:=t; end;
   inc(s);
   a:=a-b;
  end;
 write(s);
end.
```
然而还是错了：
![](https://s1.ax1x.com/2020/04/26/JgD2h4.png)

于是我把程序优化了一下：
```
var
 a,b,s,t:int64;
begin
 readln(a,b);
 while not((a=0)or(b=0)) do
  begin
   s:=s+a div b;
   a:=a-b*(a div b);
   if a<b then begin t:=a;a:=b;b:=t; end;
  end;
 write(s);
end.
```
解释：

while循环里的内容意思分别是

- 把a对折a div b次并累加到s里；

- 把a对折的剪掉；

- 判断并交换（也可以直接交换）。

最后while语句外在输出即可。

## 终于成功的A了：

![](https://s1.ax1x.com/2020/04/26/Jg6nbt.png)

---

## 作者：江山_远方 (赞：0)

看没人发搜索，本蒟蒻来一发搜索题解

注意！

十年OI一场空，~~一道状压~~不开long long见祖宗!!!

开了long long 写搜索，那都不是事儿！

去吧，代码君！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long MIN;
long long n,m;
void bigsort(long long &x,long long &y)//将x,y变为大数在前，小数在后
{
	long long a=max(x,y),b=min(x,y);
	x=a;
	y=b;
}
void dfs(long long x,long long y,long long s)//递归，一次减去他们的倍数差，以防止超时，若是整倍数，则可直接返回
{
	bigsort(x,y);
	if(x%y==0)
	{
		cout<<s+x/y<<endl;
		return ;
	}
	else dfs(y,x%y,s+x/y);
} 
int main()
{
	cin>>n>>m;//读入
	dfs(n,m,0);//调用递归
	return 0;
} 
```
~~AC抱回家~~

---

