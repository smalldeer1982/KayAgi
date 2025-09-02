# Dwarves, Hats and Extrasensory Abilities

## 题目描述

This is an interactive problem.

In good old times dwarves tried to develop extrasensory abilities:

- Exactly $ n $ dwarves entered completely dark cave.
- Each dwarf received a hat — white or black. While in cave, none of the dwarves was able to see either his own hat or hats of other Dwarves.
- Dwarves went out of the cave to the meadow and sat at an arbitrary place one after the other. When a dwarf leaves the cave, he sees the colors of all hats of all dwarves that are seating on the meadow (i.e. left the cave before him). However, he is not able to see the color of his own hat and none of the dwarves can give him this information.
- The task for dwarves was to got diverged into two parts — one with dwarves with white hats and one with black hats.

After many centuries, dwarves finally managed to select the right place on the meadow without error. Will you be able to repeat their success?

You are asked to successively name $ n $ different integer points on the plane. After naming each new point you will be given its color — black or white. Your task is to ensure that the named points can be split by a line in such a way that all points of one color lie on the same side from the line and points of different colors lie on different sides. Moreover, no points can belong to the line. Also, you need to report any such line at the end of the process.

In this problem, the interactor is adaptive — the colors of the points in the tests are not fixed beforehand and the jury program can select them arbitrarily, in particular, depending on your program output.

## 说明/提示

In the sample input and output values are aligned only for simplicity of interpreting them chronologically. In real interaction no "extra" line breaks should appear.

The following picture illustrates the first test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1063C/8b02508632dfd30b29a40bae68412cf975775dd4.png)

## 样例 #1

### 输入

```
5

black

black

white

white

black```

### 输出

```

0 0

3 1

2 3

4 4

0 2

1 3 4 1```

# 题解

## 作者：封禁用户 (赞：3)

## CF1063C Dwarves, Hats and Extrasensory Abilities 题解

### 解题思路

看到交互题优先想**二分**。我们可以将点放在一条线上，并且保持**黑色点全部在左边，白色点全部在右边**。这时，就可以根据对方的输出来确定左右界了。

但是这样会有一些玄学的错误，所以我们把点放在一条对角线上，经过调参，成功通过。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double mid, l , r;
string s , sl = "hello";
bool same = 1;
int main()
{
	cin >> n;
	l = 1;
	r = 999999999;
	while(n--)
	{
		mid = (l + r + 1) / 2.0;
		cout << int(mid) << " " << int(mid) << endl;
		cin >> s;
		if(s == "black")
		{
			l = int(mid + 1);
		}
		else
		{
			r = int(mid - 1);
		}
		if(sl != "hello" && sl != s)
		{
			same = 0;
		}
		sl = s;
	}
	if(same)
	{
		cout << "0 999999999 1 1000000000";
		return 0;
	}
	mid = (l + r) / 2.0;
	cout << int(mid - 0.5) << ' ' << int(mid + 0.5) << ' ' << int(mid + 0.5) << ' ' << int(mid - 0.5);
	return 0;
}
```

---

## 作者：KaguyaH (赞：2)

> [返回题目](https://www.luogu.com.cn/problem/CF1063C) [博客查看](...)

比较经典的二分。

但好像 $10^9$ 的坐标限制在一条直线上二分可能会出问题。

考虑在点阵中二分。

我们可以给所有横纵坐标均为奇数的点（下文称为关键点，即有可能询问的点）编号，然后二分。

代码如下：
```cpp
enum { X = (const uint)1e9, Y = (const uint)1e9 };
static const llu N(1ull * (X / 2) * (Y / 2));
static inline const uint hashx(const llu x) { return x / (Y / 2) * 2 + 1; }
static inline const uint hashy(const llu x) { return x % (Y / 2) * 2 + 1; }
```

这样的话 $\log N$（$N$ 为点集）就大约是 $60$，稳过。

考虑得到边界点后，如何画线。

按照我的编号方法，我们需要画一条斜率为 $-\inf$ 的直线。

假设我们需要令 $(x, y)$ 在这条直线下方，且任何满足 $x' > x \lor (x' = x \land y' > y)$ 的 $(x', y')$ 均在这条直线上方。

考虑令这条直线经过 $(x, y + 1)$（由于所有关键点的纵坐标均为奇数，故 $(x, y + 1)$ 必不为关键点）。

那么，我们输出的另一个点就应该是 $(x - 1, 10^9)$ 或 $(x + 1, 0)$。

选择的话，判断斜率即可。我是通过判断 $y$ 在 $[0, 5 \times 10^8)$ 还是 $(5 \times 10^8, 10^9]$ 来选择的。

代码如下：
```cpp
static inline const void cut(const llu k) {
    const uint x(hashx(k)), y(hashy(k));
    printf("%u %u %u %u\n", x, y + 1, y < Y / 2 ? x - 1 : x + 1, y < Y / 2 ? Y : 0);
}
```

时间复杂度 $O(n)$，空间复杂度 $O(1)$。

核心代码：
```cpp
static inline const void main() {
    scanf("%hu", &n);
    llu l(0), r(N);
    for (hu i(0); i < n; ++i) {
        const llu m((l + r) / 2);
        (check(m) ? l : r) = m;
    }
    cut(l);
}
```

> 纪念第一道交互题。

---

## 作者：白いバラの夜 (赞：2)

想看原题点[这](https://codeforces.com/contest/1064/problem/E)
要看原本题解点[这](https://blog.csdn.net/a670531899/article/details/83053994)(只不过代码改好了而已罢了QAQ)

### 题意：

交互题。
给你一个n，让你每次输出一个点，系统会告诉你这个点是黑还是白，让你观察完n个点之后，找出一条直线，能够把黑白点分开，这条直线通过两个点来表示。


### 思路：
直接二分。
把所有的点都放到一条直线上。

刚开始在（0，1）这个点放一个点（纵坐标之所以为1不能为0是因为你最后要在这条线上面和下面分别找一个点来确定分界线，如果纵坐标是0的话，再往下就是-1了，超出范围。），假如是白色的，这个时候假设（1e9，1）这个点存在一个黑色的点，然后就是二分这个区间了。

二分方法：设l和r分别代表白点的边界点（最靠右的一个白点）和黑点的边界点，在((+r)/2,1)处放置一个点，如果这个点是黑色的话，那么缩右区间，否则缩左区间，这样可以保证所有白点都在左边，黑点都在右边。

因为数据范围是1e9，所以缩30次差不多刚刚好。

最后取白点边界点下面的点即（l,0）和黑边界点上面的点(r,2)，两个点连成的直线就是分界线。

 

（就目前做过的题来看，交互好像都是二分的？？？？）

 

### 代码：
```cpp
#include<cstdio>
#include<string>
#include<iostream>
#include<cmath>
using namespace std;
const double eps=1e-8;
int n,p=0,l=0,r=1e9;
string s,st;
int sgn(double x){
    if(fabs(x)<eps){
    	return 0;
    }
    if(x<0){
    	return -1;
    }
    return 1;
}
int main(){
    scanf("%d",&n);
    printf("0 1\n");
    cin>>st;
    for(int i=1;i<n;i++){
        int mid=(l+r)/2;
        printf("%d 1\n",mid);
        cin>>s;
        if(s==st){
            l=mid;
        }else{
            r=mid;
        }
    }
    printf("%d 0 %d 2",l,r);
}

```

---

## 作者：meyi (赞：0)

看到交互首先想到二分。

直接在一条直线上二分分隔点貌似并不一定能通过本题，而且还需要处理细节，考虑更加稳妥的方式。

在前一种做法的基础上，不难发现可以将 $x$ 和 $y$ 坐标分别二分出分隔点，这样能承受的询问次数是 $2 \log_2 10^9 \approx 59$ 的，可以轻松通过本题的限制。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri int
typedef long long ll;
const int maxn=1e5+10;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
template<class T>inline void clear(T *arr,int siz,int val=0){memset(arr,val,sizeof(T)*(siz+1));}
char s[11];
inline bool ask(int x,int y){
	printf("%d %d\n",x,y);
	fflush(stdout);
	scanf("%s",s+1);
	return s[1]=='b';
}
inline int half(int k,bool t){
	ri l=0,r=1e9;
	while(k--){
		ri mid=l+r>>1;
		if(t?ask(mid,0):ask(0,mid))r=mid-1;
		else l=mid+1;
	}
	return l+r>>1;
}
int n;
int main(){
	scanf("%d",&n);
	printf("0 %d %d 0\n",half(n>>1,0),half(n+1>>1,1));
	fflush(stdout);
	return 0;
}
```


---

## 作者：ezoixx130 (赞：0)

有一个梗是这样的：

> There will be an i̶n̶t̶e̶r̶a̶c̶t̶i̶v̶e̶ binary search problem in the round.

所以看到交互题就去想二分吧（适用于99%的交互题）。

尽管说题目允许你选的点不在一条直线上，但是考虑到$log_2(10^9)\approx30$，在一条直线上二分即可。

具体来说，假设你最后左边全是白点，右边全是黑点，那么你只需要每次询问当前区间中间的点是什么颜色，如果是白色则把区间缩减为右半边，是黑色则缩减成左半边即可。

时间复杂度：$O(n)$

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;

char tmp[10];

int ask(int pos)
{
    printf("%d %d\n",pos,1);
    fflush(stdout);
    scanf("%s",tmp);
    return tmp[0]=='b';
}

int main()
{
    scanf("%d",&n);
    int l=0,r=1000000000,c1=ask(0);
    for(int i=1;i<n;++i)
    {
        int mid=(l+r)>>1;
        int now=ask(mid);
        if(c1==now)
        {
            l=mid;
        }
        else
        {
            r=mid;
        }
    }
    printf("%d %d %d %d\n",l,0,l+1,2);
}
```

---

