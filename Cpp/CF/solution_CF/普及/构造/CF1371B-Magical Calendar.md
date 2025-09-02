# Magical Calendar

## 题目描述

A competitive eater, Alice is scheduling some practices for an eating contest on a magical calendar. The calendar is unusual because a week contains not necessarily $ 7 $ days!

In detail, she can choose any integer $ k $ which satisfies $ 1 \leq k \leq r $ , and set $ k $ days as the number of days in a week.

Alice is going to paint some $ n $ consecutive days on this calendar. On this calendar, dates are written from the left cell to the right cell in a week. If a date reaches the last day of a week, the next day's cell is the leftmost cell in the next (under) row.

She wants to make all of the painted cells to be connected by side. It means, that for any two painted cells there should exist at least one sequence of painted cells, started in one of these cells, and ended in another, such that any two consecutive cells in this sequence are connected by side.

Alice is considering the shape of the painted cells. Two shapes are the same if there exists a way to make them exactly overlapped using only parallel moves, parallel to the calendar's sides.

For example, in the picture, a week has $ 4 $ days and Alice paints $ 5 $ consecutive days. \[1\] and \[2\] are different shapes, but \[1\] and \[3\] are equal shapes.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1371B/39eae368c2a57a50366d3b4d64699d9970b52d63.png)Alice wants to know how many possible shapes exists if she set how many days a week has and choose consecutive $ n $ days and paints them in calendar started in one of the days of the week. As was said before, she considers only shapes, there all cells are connected by side.

## 说明/提示

In the first test case, Alice can set $ 1,2,3 $ or $ 4 $ days as the number of days in a week.

There are $ 6 $ possible paintings shown in the picture, but there are only $ 4 $ different shapes. So, the answer is $ 4 $ . Notice that the last example in the picture is an invalid painting because all cells are not connected by sides.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1371B/1ff3916b23daa3947041e2801c12887257623fb7.png)In the last test case, be careful with the overflow issue, described in the output format.

## 样例 #1

### 输入

```
5
3 4
3 2
3 1
13 7
1010000 9999999```

### 输出

```
4
3
1
28
510049495001```

# 题解

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1371B)

[CF 传送门](https://codeforces.com/problemset/problem/1371/B)

才想起来还有 RMJ 没坏的时候交的题。

# 题意简述
日历中，一星期有 $k\ (1\le k\le r)$ 天，从中画出连续的 $n$ 天，使得画出的形状连在一起，问一共有几种不同的形状。
# 题解
分类讨论：
1. $n>r$  
   这种情况下画出的满足要求的形状至少有两行，那就是每次有 $k$ 种取值（形状的开头有 $k$ 种），又知 $1\le k\le r$，因此直接 $1\sim r$ 求和公式。
$$\dfrac{r\times (r+1)}{2}$$
3. $n\le r$  
   这种情况有 $n$ 个连成一行的形状，都是一种，只有一周有 $1\sim n-1$ 天时会出现不同的形状，因此还是求和公式，但是还要算上一行的情况，最后再加 $1$。
$$\dfrac{n\times (n-1)}{2}+1$$
# AC Code
```cpp
#include<iostream>
using namespace std;
int t,n,r;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>r;
        if(n>r) cout<<1ll*r*(r+1)/2;
        else cout<<1ll*n*(n-1)/2+1;
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：huayucaiji (赞：1)

我们令 $k$ 为一个星期的天数（$k\leq r$）。

我们可以把问题转化为当 $n\geq k$ 和 $n<k$ 两种情况。

当 $n \geq k$ 时，连续 $n$ 天一定会出现在至少两个星期里。我们会发现以第一行的任意一个位置作为起点都会有一个不同的形状，且一定相连。因为此时 $n\geq k$。所以一周里天数为 $k$ 时的答案就是 $k$，在最后计算答案时可以用等差数列求和公式解决。

当 $n>k$ 时，无论如何不能跨越星期，所以至多一种情况，就是 $n$ 天排列在一个星期里。$ans$ 加一即可。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int n,r;

signed main() {
	int t;
	t=read();
	while(t--) {
		n=read();r=read();
		
		int ans=0;
		if(n<=r) {
			ans+=(n-1)*n/2;//等差数列求和,n<=k
			ans+=1;//n>k
		}
		else {
			ans+=(r+1)*r/2;//等差数列，注意上下比阿奴街
		}
		cout<<ans<<endl;
	} 
	return 0;
}


```

---

