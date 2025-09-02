# Seating On Bus

## 题目描述

Consider $ 2n $ rows of the seats in a bus. $ n $ rows of the seats on the left and $ n $ rows of the seats on the right. Each row can be filled by two people. So the total capacity of the bus is $ 4n $ .

Consider that $ m $ ( $ m<=4n $ ) people occupy the seats in the bus. The passengers entering the bus are numbered from $ 1 $ to $ m $ (in the order of their entering the bus). The pattern of the seat occupation is as below:

 $ 1 $ -st row left window seat, $ 1 $ -st row right window seat, $ 2 $ -nd row left window seat, $ 2 $ -nd row right window seat, ... , $ n $ -th row left window seat, $ n $ -th row right window seat.

After occupying all the window seats (for $ m&gt;2n $ ) the non-window seats are occupied:

 $ 1 $ -st row left non-window seat, $ 1 $ -st row right non-window seat, ... , $ n $ -th row left non-window seat, $ n $ -th row right non-window seat.

All the passengers go to a single final destination. In the final destination, the passengers get off in the given order.

 $ 1 $ -st row left non-window seat, $ 1 $ -st row left window seat, $ 1 $ -st row right non-window seat, $ 1 $ -st row right window seat, ... , $ n $ -th row left non-window seat, $ n $ -th row left window seat, $ n $ -th row right non-window seat, $ n $ -th row right window seat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF660B/1bcb7084db323b1a8f04b6bcb377a8cb09279f9d.png)The seating for $ n=9 $ and $ m=36 $ .You are given the values $ n $ and $ m $ . Output $ m $ numbers from $ 1 $ to $ m $ , the order in which the passengers will get off the bus.

## 样例 #1

### 输入

```
2 7
```

### 输出

```
5 1 6 2 7 3 4
```

## 样例 #2

### 输入

```
9 36
```

### 输出

```
19 1 20 2 21 3 22 4 23 5 24 6 25 7 26 8 27 9 28 10 29 11 30 12 31 13 32 14 33 15 34 16 35 17 36 18
```

# 题解

## 作者：cqbztz2 (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF660B)

# 前言：

~~英语题面差点劝退~~

# 题目大意：

有一个公交车，如果人数小于 $ 2n $ 的话，那么这些人就只会坐在边上，是先坐左边，然后坐右边这样的，如果大于等于 $ 2n $ 的话，就会去坐中间，也是先坐左边，再坐右边，走的时候，就先走第二列，然后走第一列，然后走第三列，然后走第四列这样的，依次走一个这样。问你这些人走的样子是什么样子。

# 思路：

先走的奇数，然后再走偶数位置，先走大于 $ 2n $ 的，再走小于 $ 2n $ 的。

# 代码：

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long n,m;
  int main(){
      cin>>n>>m;
      for(int i=1;i<=2*n;i++){
          if(2*n+i<=m){
              cout<<2*n+i<<" ";
          }
          if(i<=m){
              cout<<i<<" ";
          }
      }
      return 0;
  }
```


---

## 作者：Murasoishi (赞：1)

## 题面分析
~~话说刚看到这个题面愣了一会没看懂~~

首先这道题目虽然特别长，但看完提取核心出来画个图还是很好理解的，这是一道找规律的题目，我们先带入一些具体数值找一下规律。

模拟一下 $n=5$ , $m=20$ 的情况，模拟后可以得到这个座位表：
```
9	19		20	10
7	17		18	8
5	15		16	6
3	13		14	4
1	11		12	2

```
而下车顺序是这样的：
```
11 1 12 2 13 3 14 4 15 5 16 6 17 7 18 8 19 9 20 10 
```
通过观察我们可以发现下车数列可以分成奇偶两个部分，偶数部分是   $1,2,\ldots,9,10$ ，而奇数部分是 $11,12,\ldots,19,20$ 。所以我们得出了规律：对于所有长度为四的倍数的m，输出结果为奇偶两部分交错，奇数部分：  $n/2+1,n/2+2,\ldots,n-1,n$ ，偶数部分： $1,2,\ldots,n/2-1,n/2$ 。

为什么是四的倍数呢，接下来讨论非四的倍数的情况。

对于长度非四的倍数的 $m$ ，我们可以将它增大，加到可以被四整除为止，显然是 `len=m+4-m%4` ，处理之后按照上文方法处理，当遇到下车数列中有 $>m$ 的数时，便跳过这个数。
## ACCode
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,len;
int main() {
	cin>>n>>m;
	if(m%4)len=m+4-m%4;
	else len=m;
	for(int i=1;i<=len;i++){
		if(i%2){
			if((len/2+i/2+1)>m)continue;
			cout<<k/2+i/2+1<<' ';
		}
		else {
			if(i/2>m)continue;
			cout<<i/2<<' ';
		}
	}
	return 0;
}
```
完结撒花

---

## 作者：_Agave_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF660B)

## 翻译
给你一个这样的公交车

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF660B/1bcb7084db323b1a8f04b6bcb377a8cb09279f9d.png)

有 $m$ 个人要上车（顺序在途中已经标出）。

有 $n$ 排（图中 $n$ 为 $17$）

这 $m$ 个人下车的顺序是这样的：


| …… | …… | …… | …… |
| :----------- | :----------- | :----------- | :----------- |
| $14$ | $13$ | $15$ | $16$ |
| $10$ | $9$ | $11$ | $12$ |
| $6$ | $5$ | $7$ | $8$ |
| $2$ | $1$ | $3$ | $4$ |

 
## 解法
依据题目，我们可以直接模拟每两个人的上车方式

（ $1$ 、$4$ 列有地方就上到 $1$ 、$4$ 列，否则上到 $2$ 、$3$ 列）

下车的方法也可以用上车的方法模拟

（将每一行都按顺序输出）

$r$ 表示上车时这个人的编号

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int seat[10][205],n,m,r=1; 
//模拟上车
void push(){
	//1、4列
	for(int i=1;i<=n;i++){
		if(r==m+1)return ;
		seat[1][i]=r;
		r++;
		if(r==m+1)return ;
		seat[4][i]=r;
		r++;
	}
   //2、3列
	for(int i=1;i<=n;i++){
		if(r==m+1)return ;
		seat[2][i]=r;
		r++;
		if(r==m+1)return ;
		seat[3][i]=r;
		r++;
	}
}
//模拟下车
void out(){
	for(int i=1;i<=n;i++){
		//模拟每一行
		if(seat[2][i]!=0)printf("%d ",seat[2][i]);
		if(seat[1][i]!=0)printf("%d ",seat[1][i]);
		if(seat[3][i]!=0)printf("%d ",seat[3][i]);
		if(seat[4][i]!=0)printf("%d ",seat[4][i]);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	push();
	out();
	return 0;
}

```


---

## 作者：Xdl_rp (赞：0)

~~这就是一道数学题~~

进入正题：
------------

- 首先，最先出的就是第 $2 \times n + 1$ 个人（如果人数大于 $2 \times n + 1$ 的话），然后出 $1$；又输出第 $2 \times n + 2$ 个人，又输出 $2$，一直推下去。

说明当 $2 \times n + i$ 存在的话，肯定这个人会在这个时候下车，所以就输出 $2 \times n + i$；有如果 $i$ 存在的话，也会在紧跟着 $2 \times n + i$ 后面下车，也输出 $i$。

```cpp
int k = n * 2;//方便一点
for (int i = 1; i <= k; i++) {
	if (k + i <= m) cout << k + i << " ";//如果这个人是存在这辆车上的，就把他输出了。
	if (i <= m) cout << i << " ";//紧跟着把他旁边的人（如果有的话）输出了
}
```
到这里就不给完整代码了，这个思路已经够清晰了。

---

## 作者：dbodb (赞：0)

这道题我们读懂题意即可
#### 题意

给你公交车的排数n,和乘客的数量m
让你求出乘客的下车顺序
#### 思路
在上车选座的时候乘客遵循这样的一种规则
即：先坐左侧靠窗，再坐右侧靠窗，依次坐下去，当左侧和右侧的那列都坐满的时候，我们再开始从左边不靠窗的位置，右侧不靠窗的位置，依次坐下去，我们定义
一个数组$a[i][j]$,用来保存上车的人的编号
在模拟的时候，我们要时刻满足剩余的人数$>=0$，

根据题意，乘客在下车的时候换了一种方式，即：先左不靠窗，再左靠窗，再右不靠窗，再右靠窗

最后一行，难免会坐不满，这个时候我们加一个**判断**$if(a[i][j]>0)$就行了。

#### 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int a[105][5];
int main()
{
	int n,m;
	cin>>n>>m;
	int shun=0;
	for(int i=1;m>=0&&i<=n;i++)
{
	if(m-1>=0)
		a[i][1]=++shun,m--;
	if(m-1>=0)
		a[i][4]=++shun,m--;
}
for(int i=1;m>=0&&i<=n;i++)
{
	if(m-1>=0)
		a[i][2]=++shun,m--;
	if(m-1>=0)
		a[i][3]=++shun,m--;
}
	for(int i=1;i<=n;i++)
	{   if(a[i][2])
			cout<<a[i][2]<<" ";
		if(a[i][1])
			cout<<a[i][1]<<" ";
		if(a[i][3])
			cout<<a[i][3]<<" ";
		if(a[i][4])
			cout<<a[i][4]<<" ";
	}
	return 0;
}
```
完结撒花

#### 最后
这道题的评分有点虚高，评分普及-应该差不多了


---

## 作者：世末OIer (赞：0)

题目大意：

有一个公交车，n行4列。坐车方式比较特别：
7 15  16 8
5 13  14 6
3 11  12 4
1 9    10 2

出车顺序:
9 1 10 2 11 3 12 4 5 13 14 6 7 15 16 8

7          
5           6
3           4
1           2

出车顺序:
1 2 3 4 5 6 7 


问你假设有m个人，问你这m个人的出车顺序。

题解:
暴力模拟。
goto :直接跳到最后输出

g():跳过空位置

```cpp
using namespace std;
int a[5][111];
inline void g(int x){
	if(x) cout<<x<<' ';
}
int main(){
	int i,j,n,m,t=1;
	cin>>n>>m;
	for(i=0;i<n;++i){                                       //靠窗
		if(m==t){
			a[0][i]=t;
			goto G;
		}
		if(m-t==1){
			a[0][i]=t;
			a[3][i]=t+1;
			goto G;
		}
		a[0][i]=t;
		a[3][i]=t+1;
		t+=2;
	}
	for(i=0;i<n;++i){                                     //不靠窗
		if(m==t){
			a[1][i]=t;
			goto G;
		}
		if(m-t==1){
			a[1][i]=t;
			a[2][i]=t+1;
			goto G;
		}
		a[1][i]=t;
		a[2][i]=t+1;
		t+=2;
	}
	G:{
//		for(i=0;i<n;++i,cout<<endl) for(j=0;j<4;++j) cout<<a[j][i]<<' ';
//		cout<<endl;
	};
	for(i=0;i<n;++i) g(a[1][i]),g(a[0][i]),g(a[2][i]),g(a[3][i]);
	return 0;
}
```

---

