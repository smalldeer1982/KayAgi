# [COCI 2008/2009 #2] KORNISLAV

## 题目描述

乌龟 Kornislav 从来没有什么有趣的事。 由于他将生活三百年，他一直在努力寻找消磨时间的方法。 这个周末，他开始玩“面积最大的矩形”这个游戏。
首先，Kornislav 需要四个正整数。他通过向一个方向移动，旋转 $90°$ ，在新方向上行走等方式来形成一个图案。Kornislav 总共进行了三个 $90°$ 旋转，并走过了四条线段。
当朝某个方向行走时，他的步数必须等于四个所选整数中的一个，并且每个整数只能成为一条线段的长度。根据 Kornislav 使用这四个整数的顺序，他的步行将形成各种形状，其中也包括一些未封闭的图案。
编写一个程序，计算出乌龟的行进轨迹可以形成的最大矩形面积。

## 说明/提示

#### 数据规模与约定
对于 $100\%$ 的数据，有 $1<a,b,c,d<100$。
#### 说明
#### 题目译自 [COCI2008-2009](https://hsin.hr/coci/archive/2008_2009/) [CONTEST #2](https://hsin.hr/coci/archive/2008_2009/contest2_tasks.pdf) KORNISLAV，译者 @[mnesia](https://www.luogu.com.cn/user/115711)。

## 样例 #1

### 输入

```
1 2 3 4```

### 输出

```
3```

## 样例 #2

### 输入

```
4 4 3 4```

### 输出

```
12```

# 题解

## 作者：MZY666 (赞：34)

[原题传送门](https://www.luogu.com.cn/problem/P6420)。[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-p6420)。

### 【 题意概括 】

给定四个线段的长度 $a$，$b$，$c$，$d$，求用它们围组成的长方形最大面积为多少。

### 【 思路 】

与第一篇题解相同，这里再讲详细一点：

$S_{\text{长方形}}=$ 长 $\times$ 宽。

既然要最大面积，那就尽量要最大的长以及最大的宽。

宽肯定是比长要小（或等）的。

想一想：这里的长方形中每一组对边的较小的那一条肯定是使得较长的那一段有一段发挥不到增大（也就浪费了）。

所以就得尽量使“浪费”减小。

那么可以让最小的那条线段作为一条宽，第二小的作为其对边（相比另外两条长的损耗小）；

第二大的作为一条长，最大的作为长的对边。

代码实现见下。

### 【 代码实现 + 注释 】

```cpp
#include<bits/stdc++.h>//万能头文件可好 
using namespace std;
int a[5];//数组定义在外面方便一些
int main(){
	for(int i=1;i<=4;i++)cin>>a[i];//输入a,b,c,d
	sort(a+1,a+1+4);//排序
	cout<<a[1]*a[3]<<endl;//输出长*宽的和。
	return 0;//over
}
```

来点花样，挑战本题最短C++代码（不喜勿喷）：
```cpp
#include<bits/stdc++.h>
int a[5],i=1;int main(){for(;i<=4;)std::cin>>a[i++];std::sort(a+1,a+1+4);std::cout<<a[1]*a[3];}
```


最后，由于作者自愿禁言了，如果有建议请私信。否则将**无法**回复您哦！

完结撒花~（疯狂暗示 AOA

---

## 作者：JamesQin (赞：7)

已知四个数，求以这四条边围成的矩形（可以有多余，即凸出来的部分）面积的最大值。

不妨设$a \leq b \leq c \leq d$ 。

可以以 $a$ 和 $b$ 为对边，$c$ 和 $d$ 为对边，面积的最大值为 $a \times c$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a[4];
	for(int i=0;i<=3;i++){
		cin>>a[i];
	}
	sort(a,a+4);
	cout<<a[0]*a[2]<<endl;
	return 0;
} 
```


---

## 作者：半笙、凡尘 (赞：3)

#【[COCI2008-2009#2] KORNISLAV】
 
 -------
 
~~序:无聊来做做水题~~

----------

- 啥也不说，直接上图好吧，这是样例 $1$ 的所做的最大面积的矩形，其实大家只要去尝试画图就可以发现规律了，**能构成最大矩形面积的边就是最小的边以及次大的边**

- 从图上我们可以看出吗，构成最大面积矩形的边是 $3$ 和 $1$。 

![](https://i.loli.net/2020/05/18/QrovchdgCNJly8O.png)

- 所以我们只要给四个数排个序即可（易得,证毕

- 接下来就是一点也不激动人心的代码了

```cpp
#include<bits/stdc++.h>
#define RT register
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0)putchar('-'),write(-x);
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}
template<class t> inline void writeln(t x){
	write(x);putchar('\n');
	return;
}
template<class t> inline void write_blank(t x){
	write(x);putchar(' ');
	return;
}
int a[5];
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	for(int i=1;i<=4;i++){
		read(a[i]);
	}
	sort(a+1,a+1+4);
	write(a[1]*a[3]);
	return 0;
}
```

---

## 作者：SisconHL (赞：1)

> 被删了一次稿，好气哦……

不妨设边长为 $a_i(i\in [0,3])$，$\forall i,j$，有 $a_i\le a_j$。并设长 $=x$，宽 $=y$，$x\ge y$。

易发现 $x=a_2,y=a_0$ 最优，证明：

- $x=a_2$ 最优：

若 $x=a_3$，则显然 $\nexists a_i(i\in[0,2])> x$（不取等是因为取等则可调换）

若 $x=a_1$，则 $y_{max}=a_0$，$a_1*a_0\leq a_2*a_0$

若 $x=a_0$，则 $\nexists y,s.t.y\leq x$。

故 $x=a_2$ 最优。

而 $y$ 不能为 $a_1$，因为没有两个数分别满足它们标号各比长宽大。

证毕。

下证可行性：

容易找到一个次序：$a_1-a_2-a_0-a_3$，可成立，且封闭。

故 $x=a_2,y=a_0$。

代码：

```cpp
#include<iostream>
#include<algorithm>

using std::cin;
using std::cout;
using std::sort;

const int maxn = 4 + 5;

int a[ maxn ];

int main( void )
{
	for( register int i = 0 ; i < 4 ; i++ )
		cin >> a[ i ];
	sort( a , a + 4 );
	cout << ( a[ 0 ] * a[ 2 ] );
} 
```

---

