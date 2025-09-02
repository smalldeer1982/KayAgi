# 题目信息

# Photo of The Sky

## 题目描述

Pavel made a photo of his favourite stars in the sky. His camera takes a photo of all points of the sky that belong to some rectangle with sides parallel to the coordinate axes.

Strictly speaking, it makes a photo of all points with coordinates $ (x, y) $ , such that $ x_1 \leq x \leq x_2 $ and $ y_1 \leq y \leq y_2 $ , where $ (x_1, y_1) $ and $ (x_2, y_2) $ are coordinates of the left bottom and the right top corners of the rectangle being photographed. The area of this rectangle can be zero.

After taking the photo, Pavel wrote down coordinates of $ n $ of his favourite stars which appeared in the photo. These points are not necessarily distinct, there can be multiple stars in the same point of the sky.

Pavel has lost his camera recently and wants to buy a similar one. Specifically, he wants to know the dimensions of the photo he took earlier. Unfortunately, the photo is also lost. His notes are also of not much help; numbers are written in random order all over his notepad, so it's impossible to tell which numbers specify coordinates of which points.

Pavel asked you to help him to determine what are the possible dimensions of the photo according to his notes. As there are multiple possible answers, find the dimensions with the minimal possible area of the rectangle.

## 说明/提示

In the first sample stars in Pavel's records can be $ (1, 3) $ , $ (1, 3) $ , $ (2, 3) $ , $ (2, 4) $ . In this case, the minimal area of the rectangle, which contains all these points is $ 1 $ (rectangle with corners at $ (1, 3) $ and $ (2, 4) $ ).

## 样例 #1

### 输入

```
4
4 1 3 2 3 2 1 3
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
5 8 5 5 7 5
```

### 输出

```
0```

# AI分析结果

### 题目内容翻译

# 天空的照片

## 题目描述

Pavel 为他最喜欢的星星拍了一张天空的照片。他的相机拍摄的是所有属于某个与坐标轴平行的矩形的天空点。

严格来说，它拍摄的是所有坐标为 $ (x, y) $ 的点，使得 $ x_1 \leq x \leq x_2 $ 且 $ y_1 \leq y \leq y_2 $，其中 $ (x_1, y_1) $ 和 $ (x_2, y_2) $ 是被拍摄矩形的左下角和右上角的坐标。这个矩形的面积可以为零。

拍完照片后，Pavel 写下了照片中出现的 $ n $ 颗他最喜欢的星星的坐标。这些点不一定不同，同一个天空点可能有多个星星。

最近 Pavel 丢失了他的相机，他想买一个类似的。具体来说，他想知道他之前拍摄的照片的尺寸。不幸的是，照片也丢失了。他的笔记也没有太大帮助；数字随机地写在他的笔记本上，所以无法确定哪些数字指定了哪些点的坐标。

Pavel 请你帮助他根据他的笔记确定照片的可能尺寸。由于有多个可能的答案，找到矩形面积最小的尺寸。

## 说明/提示

在第一个样例中，Pavel 的记录中的星星可以是 $ (1, 3) $, $ (1, 3) $, $ (2, 3) $, $ (2, 4) $。在这种情况下，包含所有这些点的矩形的最小面积为 $ 1 $（矩形的角在 $ (1, 3) $ 和 $ (2, 4) $）。

## 样例 #1

### 输入

```
4
4 1 3 2 3 2 1 3
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
5 8 5 5 7 5
```

### 输出

```
0```

### 算法分类
贪心

### 题解分析与结论
这道题的核心思路是通过排序和贪心策略来找到最小面积的矩形。所有题解都采用了类似的思路：首先对输入的数组进行排序，然后通过枚举不同的区间组合来找到最小面积的矩形。主要难点在于如何高效地枚举区间并计算最小面积。

### 精选题解

#### 1. 作者：MorsLin (赞：8)
- **星级**: 5
- **关键亮点**: 详细解释了两种情况的分类讨论，代码简洁且高效。
- **个人心得**: 提醒了开 `long long` 的重要性，避免溢出问题。

```cpp
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
int read(){
	int k=0; char c=getchar();
	for(;c<'0'||c>'9';) c=getchar();
	for(;c>='0'&&c<='9';c=getchar())
	  k=(k<<3)+(k<<1)+c-48;
	return k;
}
ll a[100010<<1],ans;
int main(){
	int n=read();
	for(int i=1;i<=n<<1;i++) a[i]=read();
	sort(a+1,a+(n<<1)+1);
	ans=(a[n]-a[1])*(a[n<<1]-a[n+1]); //第二种情况
	for(int i=2;i<=n+1;i++)  //第一种情况
		ans=min((a[n<<1]-a[1])*(a[i+n-1]-a[i]),ans);
	cout<<ans;
	return 0;
}
```

#### 2. 作者：Register (赞：3)
- **星级**: 4
- **关键亮点**: 通过图示直观地解释了题意，代码实现清晰。
- **个人心得**: 强调了 `sort` 的重要性，确保数组有序。

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int n;
ll a[200001],ans;
int main(){
    cin>>n;
    for(int i=1;i<=(n<<1);i++) cin>>a[i];
    sort(a+1,a+(n<<1)+1);
    ans=(a[n]-a[1])*(a[n<<1]-a[n+1]);
    for(int i=1;i<n;i++) ans=min((a[n<<1]-a[1])*(a[n+i]-a[i+1]),ans);
    cout<<ans<<endl;
    return 0;
}
```

#### 3. 作者：yanwh1 (赞：2)
- **星级**: 4
- **关键亮点**: 详细解释了贪心思路，代码实现简洁。
- **个人心得**: 强调了连续区间的重要性，确保最小面积。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define int long long
inline int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-'){y=-1;}c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*y;
}inline void write(int s){
	if(s<0)s=-s,putchar('-');
	if(s>9)write(s/10);
	putchar(s%10+'0');
}const int N=2e5+5;
int s[N];
signed main(){
	int n=read();
	for(rint i=1;i<=2*n;i++)s[i]=read();
	sort(s+1,s+2*n+1);
	int ans=(s[n]-s[1])*(s[2*n]-s[n+1]);
	for(rint i=2;i<=n;i++)
		ans=min(ans,(s[2*n]-s[1])*(s[n+i-1]-s[i]));
	write(ans);
	return 0;
}
```

### 最优关键思路
1. **排序**: 首先对数组进行排序，确保能够高效地枚举区间。
2. **贪心策略**: 通过枚举不同的区间组合，找到最小面积的矩形。
3. **分类讨论**: 考虑两种情况，一种是最大值和最小值在同一个集合中，另一种是它们分别在不同的集合中。

### 拓展思路
类似的问题可以通过排序和贪心策略来解决，例如在给定一组数据中找到最小或最大的某种组合。这类问题通常需要对数据进行预处理（如排序），然后通过枚举或动态规划来找到最优解。

### 推荐题目
1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1966 [NOIP2013 提高组] 火柴排队](https://www.luogu.com.cn/problem/P1966)

---
处理用时：52.50秒