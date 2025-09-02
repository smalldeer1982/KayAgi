# Celex Update

## 题目描述

由于本场题面违反互联网相关法律，不予展示原题面。

## 说明/提示

In the first test case there are two possible sums: $ 1+2+5=8 $ and $ 1+3+5=9 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1358C/eda2a626df084219764abcf0fbda9d10b5c5340d.png)

## 样例 #1

### 输入

```
4
1 1 2 2
1 2 2 4
179 1 179 100000
5 7 5 7```

### 输出

```
2
3
1
1```

# 题解

## 作者：LeavingZzz (赞：8)

# Solution For CF1358C  
Upd: $\LaTeX$全都坏了QAQ，换成图片惹，很不好意思/kk  


------------

(~~从whk溜出来打比赛qaq~~)  
看一下数据范围，长得一脸 $O(1)$ 的样子  
这题是个结论题，我们观察一下那个表格： 

![](https://cdn.luogu.com.cn/upload/image_hosting/xncdulqj.png)  

然后你就发现了一件事情：  
从点 $(i,j)$ 前往点 $(i,j+1)$ 格子上的数字会增加 $i+j-1$  
而从点 $(i,j)$ 前往点 $(i+1,j)$ 格子上的数字会增加 $i+j$  
也就是说对于一对给定的坐标，以他们两个为矩形左上角和右下角，构成了一个 $N\times M$的矩形，会这样  
![](https://cdn.luogu.com.cn/upload/image_hosting/bu79mizy.png)  

假设我们把路径上的 $c$ 替换成 $f$（就像把右上角的一个直角扭下来一样）  
![](https://cdn.luogu.com.cn/upload/image_hosting/tayslxrt.png)  

很明显权值比上一个方案大 $1$  
（点 $c$ 权值比 $f$ 小 $1$，参照之前说的  
从点 $(i,j)$ 前往点 $(i,j+1)$ 格子上的数字会增加 $i+j-1$  
而从点 $(i,j)$ 前往点 $(i+1,j)$ 格子上的数字会增加 $i+j$  ）  

那么同理，现在右上角的直角拐点 $b$ 也可以 “扭下来”  
![](https://cdn.luogu.com.cn/upload/image_hosting/zc2w41sa.png)  

权值再次加一  

所以我们就一直这样扭下去，每扭一次路径权值和就会加 $1$，又因为只能向下走或者向右走，对于每一行我们可以扭 $M-1$ 次（$(x_1,y_1)$ 点所在的列不能扭），我们一共可以扭 $N-1$ 行（$(x_2,y_2)$ 点所在的行不能扭），权值最小的路径就是从第一行走到最后一列然后从最后一列下去到终点。  

我们一共可以扭 $(N-1)\times (M-1)$ 次，可以加上 $(N-1)\times (M-1)$ 次 $1$，所以一共有 $(N-1)\times (M-1)+1$ 种不同权值的路径。$O(1)$ 解决/cy  
$\large\mathsf{Code:}$  
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T;
typedef long long LL;
LL N,M;
int main()
{
	scanf("%d",&T);
	int x1,x2,y1,y2;
	while(T--)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		N=y2-y1+1;M=x2-x1+1;
		printf("%lld\n",(N-1)*(M-1)+1);
	}
	return 0;
}
```
~~萌新上分，越上越昏~~   
$\huge\mathcal{The\text{ }End}$  
蟹蟹管理大大审核 ^_^  

---

## 作者：juicyyou (赞：4)

# CF1358C Celex Update
## 解法：
首先我们知道，如果一条路径中有先向左再向右的拐弯的话 ( 如下图 )

![](https://cdn.luogu.com.cn/upload/image_hosting/qxxszu4z.png)

那么，我们把这个拐弯处向下改动为：

![](https://cdn.luogu.com.cn/upload/image_hosting/th4oisfw.png)

之后，这个路径的和会增加 1，也就是说，我们可以在和最小的路径的基础上，通过改变拐弯的方式使其增加 1，所以，我们可以构造出在和最大路径和和最小路径之间的任意一种权值和。

于是，我们只要求出最大路径和 - 最小路径和 + 1就行了。

公式也很好推，答案就是：

令 $n = y_2 - y_1 + 1$，$m = x_2 - x_1 + 1$
$$
\begin{cases}
n \cdot (n-1) + (m - n - 1) \cdot (n - 1)\,\,\,\,n \ge m\\
m \cdot (m-1) + (n - m - 1) \cdot (m - 1)\,\,\,\,n < m
\end{cases}
$$
然后这题就作完了。

下面是Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e6 + 5;
const ll maxm = 1e3 + 5;
inline void qread(){}
template<class T1, class ...T2>
inline void qread(T1 &IEE, T2&... ls){
	register T1 __ = 0, ___ = 1;
	register char ch;
	while(!isdigit(ch = getchar())) ___ = (ch == '-') ? -___ : ___;
	do{
		__ = (__ << 1) + (__ << 3) + (ch ^ 48);
	}while(isdigit(ch = getchar()));
	__ *= ___;
	IEE = __;
	qread(ls...);
	return ;
}
ll x11, x22, y11, y22, n, m, ans;
int main(){
	ll t;
	qread(t);
	while(t--){
		qread(x11, y11, x22, y22);
		m = x22 - x11 + 1;
		n = y22 - y11 + 1;
		if(n >= m){
			ans = n * (n - 1) + (m - n - 1) * (n - 1);
		} else {
			ans = m * (m - 1) + (n - m - 1) * (m - 1);
		}
		cout << ans + 1;
		puts("");
	}
	return 0;
}
```
上述算法的复杂度为 $O(1)$，算上多测复杂度为 $O(t)$。

---

## 作者：lijunxi1 (赞：1)

令左上点为 $(sx,sy)$，右下点为 $(xx,xy)$。

令 $f(x,y)$ 为点 $(x,y)$ 的值。

对于此题，对于任意一个矩阵，形式皆为：

|   $f(sx,sy)$   |  $f(sx,sy+1)$  |  $f(sx,sy+2)$  |    $\cdots$    |   $f(sx,xy)$   |
| :------------: | :------------: | :------------: | :------------: | :------------: |
| $f(sx,sy+1)+1$ | $f(sx,sy+2)+1$ |    $\cdots$    |  $f(sx,xy)+1$  | $f(sx,xy+1)+1$ |
| $f(sx,sy+2)+2$ |    $\cdots$    |  $f(sx,xy)+2$  | $f(sx,xy+1)+2$ | $f(sx,xy+2)+2$ |
|    $\cdots$    |    $\cdots$    | $f(sx,xy+1)+3$ | $f(sx,xy+2)+3$ | $f(sx,xy+3)+3$ |
|    $\cdots$    |    $\cdots$    |    $\cdots$    |    $\cdots$    |    $\cdots$    |
|    $\cdots$    |    $\cdots$    |    $\cdots$    |    $\cdots$    |   $f(xx,xy)$   |

故有最小值为 $f(sx,sy)+f(sx,sy+1)+f(sx,sy+2)+\cdots+f(sx,sy)+f(sx,xy+1)+1+f(sx,sy+2)+2+f(sx,xy+3)+3+\cdots+f(xx,xy)$。

若中途不进过 $(sx,xy)$，途径 $(sx+1,xy-1)$，值变为 $f(sx,sy)+f(sx,sy+1)+f(sx,sy+2)+\cdots+f(sx+1,sy-1)+f(sx,xy+1)+1+f(sx,sy+2)+2+f(sx,xy+3)+3+\cdots+f(xx,xy)$。差为 $f(sx-1,xy+1)-f(sx,sy)=1$。

其他均可形似为此。

一直加到最大值。

故答案为途径最大值减途径最小值加一。

但这样还是太难求。

我们来观察图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2rgcdt5y.png)

每一个颜色的边为一种情况。

发现 在四边形 $(sx,sy+1),(sx,xy),(xx-1,sy),(sx-1,sy)$ 中的点都是使其加一的点。

该四边形底为 $sy-xy$，高为 $xx-sx$，故扫过的点个数为 $(sy-xy)\times(xx-sx)$。

还有一条最大值的边。

故公式为 $ans=1+(xx-sx)\times(sy-xy)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long xx,xy,sx,sy,T;
int main ()
{
	cin>>T;
	while(T--)
	{
		cin>>xx>>xy>>sx>>sy;
		cout<<1ll+(sx-xx)*(sy-xy)<<"\n";
	}
}
```



---

## 作者：ybc2026lhy (赞：0)

很明显，对于此题的数据范围而言，任何的暴力都无法在规定时间内 AC，因此，只能使用 $O(1)$ 的时间复杂度来解决这个问题。那么，很显然，这个题就是一个推结论的题目。

通过观察，我们发现，对于坐标 $(i,j)$ 而言，如果它移动到了坐标 $(i,j+1)$ 的位置，它最终的答案增加了 $i+j-1$，而如果将它移动到坐标 $(i+1,j)$，则答案增加的 $i+j$。

因此，如果我们每一次将图中红色的这样一条线转换为蓝色的这样一条线，总的 $SUM$ 答案值会增加 1。

![](https://www.becoder.com.cn/file/download-share/ad7162ee404eb510392ba8c0e9d9fe890063b74b0980f4584c20ef7c9c40d3339890fc94c3076e3857d215e02256ddf249be3d15fc986a59278569708d638717a5a2026554ea)

因此，我们很容易就可以发现，最终答案的个数就和我们像上图这样进行转换的次数有关。

而这里我们假设，起点和终点的行之差为 $n$，列之差为 $m$，那么，很明显，我们就可以在每一行操作 $m-1$ 次。而对于行而言，一共又有 $n-1$ 行可以操作。因此，最终可以操作的次数就为 $(n-1)\times (m-1)$ 次。再加上最初始先全部往右，再全部往下走的这一种情况，最终可以得到的不同值的种类数就为 $(n-1)\times (m-1)+1$。

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,x,y,n,m,b,v,ans;
int main(){
	//freopen("ak.in","r",stdin);
	//freopen("ak.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>x>>y>>n>>m;
		b=n-x+1;
		v=m-y+1;
		ans=(b-1)*(v-1)+1;
		cout<<ans<<endl;
	}
}

---

## 作者：cqbzhzf (赞：0)

## 题意
不再赘述。
## 分析
- 首先**不能暴力**，考虑 $O(1)$ 做法
- 然后当**特殊情况**时(当横坐标或纵坐标相等时)只有一种走法。![](https://cdn.luogu.com.cn/upload/image_hosting/ugwysdfi.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
- 其次，通过画图可以发现**每一次移动可选择的格子之和**为 $(x-1) \times (y-1)+1$，$1$ 是由于**每次向下再每次向右或每次向右再每次向下**的情况。
- 最后，因为数据范围不太清楚，所以**保险起见**开个 `long long`。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a1,b1,a2,b2;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)//多组数据
	{
		cin>>a1>>b1>>a2>>b2;
		if(a1==a2||b1==b2)
			cout<<1<<endl;//特判
		else
			cout<<1+(a2-a1)*(b2-b1)<<endl;//常规情况
	}
	return 0;
}
```

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://codeforces.com/problemset/problem/1358/C)



## 分析

很明显，对于此题的数据范围而言，任何的暴力都无法在规定时间内得到满分。因此，只能使用 $O(1)$ 的时间复杂度来解决这个问题。那么可以很快看出，这个题就是一道推结论的题目（即数学题）。



## 做法

通过观察，我们发现，对于坐标 $(i,j)$ 而言，如果它移动到了坐标 $(i,j + 1)$ 的位置，它最终的答案增加了 $i + j - 1$，而如果将它移动到坐标 $(i + 1,j)$ 时，则答案增加的是 $i + j$。

因此，如果我们每一次将图中红色的这样一条线转换为蓝色的这样一条线，总个数答案值会增加 $1$。![](https://cdn.luogu.com.cn/upload/image_hosting/ol44qbdc.png)

因此，我们很容易就可以发现，最终答案的个数就和我们像上图这样进行转换的次数有关。

而这里我们假设，起点和终点的行之差为 $n$，列之差为 $m$。那么，很明显，我们就可以在每一行操作 $m - 1$次。而对于行而言，一共又有 $n - 1$ 行可以操作。因此，最终可以操作的次数就为 $(n - 1) \times (m - 1)$ 次。再加上最初始先全部往右，再全部往下走的这一种情况，最终可以得到的不同值的种类数就为 $(n - 1) \times (m - 1) + 1$。



## AC code

```cpp
/*
codeforces 1358C Celex Update
*/
#include <bits/stdc++.h>
using namespace std;
int t;  
long long n1,m1,n2,m2;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n1>>m1>>n2>>m2;
		cout<<(n2 - n1) * (m2 - m1) + 1<<endl;//公式
	}
	return 0;
}
```

---

## 作者：jimmy2021 (赞：0)

首先，比较下面两个路线（一个红色，一个蓝色，设从红线变为蓝线的过程为“扭”）上的数的和的大小（`st`为起点，`ed`为终点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/upyi0azh.png)

容易发现，蓝色路线上的数的和要比红色路线上的数的和要大 $1$。

而对应到原题上，就是：设 $n$ 为两行之间的差值，$m$ 为两列之间的差值，那么对于每一行，可以“扭” $m - 1$ 次，我们可以“扭” $n - 1$ 行，那么最多可以扭 $(n - 1) \times (m - 1)$ 次，不同的值就有 $(n - 1) \times (m - 1) + 1$ 种。时间复杂度：$O(1)$。

代码：
```cpp
#include <cstdio>
using namespace std;

typedef long long LL;

LL t;
LL xa, ya, xb, yb;

int main(){
    scanf("%lld", &t);
    while(t--){
        scanf("%lld%lld%lld%lld", &xa, &ya, &xb, &yb);
        
        LL xdif = xb - xa + 1, ydif = yb - ya + 1;
        printf("%lld\n", (xdif - 1) * (ydif - 1) + 1);
    }
    return 0;
}
```

---

## 作者：SpeedStar (赞：0)

### 算法分析
注意到，起点到终点的所有路径的权值在起点到终点的所有路径的权值的最小值$minL$与最大值$maxL$之间，即$maxL - minL + 1$为起点到终点的不同路径权值的个数，而$max-minL$恰好为起点到终点围成的矩形的面积$(x2-x1) * (y2-y1)$。
![](https://cdn.luogu.com.cn/upload/image_hosting/gx6dl2en.png)

### C++代码
```cpp
#include <iostream>
#define int long long 

using namespace std;

signed main() {
	int t;
	cin >> t;
	
	while (t--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		int n = x2 - x1, m = y2 - y1;
		cout << n * m + 1 << '\n';
	}
	
	return 0;
}
```


---

## 作者：Pecco (赞：0)

从一个点到另一个点，和最少的路径是先一路向右，再一路向下。然后你可以把路径上 ┐ 的小段变成 └ ，这样恰好会使和增加1。例如：

$\begin{matrix}1&\rightarrow&2\\&&\downarrow\\&&5\end{matrix}\quad{\Large\rightarrow}\quad\begin{matrix}1\\\downarrow\\3&\rightarrow&5\end{matrix}$

这样的操作一共可以进行 $nm$ 次（其中$n=x_2-x_1,m=y_2-y_1$），加上最开始的一种，和一共就有$nm+1$种。

代码其实可以不用了吧，记得开long long。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read()
{
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}
int main()
{
    int t = read();
    while (t--)
    {
        ll x1 = read(), y1 = read(), x2 = read(), y2 = read();
        ll n = x2 - x1, m = y2 - y1;
        cout << n * m + 1 << endl;
    }
    return 0;
}
```

---

