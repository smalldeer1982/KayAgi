# Broken Monitor

## 题目描述

## 描述
小 A 的电脑显示器坏了，有些像素点一直是黑色的。他最近正在和他的弟弟小 B 玩一个游戏：小 A 控制程序在屏幕上绘制一个 1 像素宽的白色方框，由于显示器已经损坏了，一些应该是白色的像素点仍为黑色。小 B 根据屏幕上显示的内容来推测方框的大小和绘制的位置。你要帮助小 B 自动化这个游戏的过程。写一个程序找到满足条件的方框：（1）方框的宽为 1 像素；（2）方框不会超过屏幕的边缘；（3）屏幕显示的白色像素都在方框上；（4）在满足前三个条件的所有方框中，正确的方框是尺寸最小的那个。方框的尺寸由边长表示，方框边缘的像素不重叠。举例来说，边长为 3 的方框包含 8 个像素，边长为 2 的方框包含 4 个像素，边长为 1 的方框包含 1 个像素。

## 样例 #1

### 输入

```
4 8
..w..w..
........
........
..w..w..
```

### 输出

```
..w++w..
..+..+..
..+..+..
..w++w..
```

## 样例 #2

### 输入

```
5 6
......
.w....
......
..w...
......
```

### 输出

```
......
+w+...
+.+...
++w...
......
```

## 样例 #3

### 输入

```
2 4
....
.w..
```

### 输出

```
....
.w..
```

## 样例 #4

### 输入

```
2 6
w..w.w
...w..
```

### 输出

```
-1
```

# 题解

## 作者：_edge_ (赞：0)

不得不说，这道题目真的很容易把人骗到假的算法上去，然后就调不出来了。

估计 CF 的时候我也不太能调得出来。

注意题目的一些细节，所有的 `w` 都要在这个框框的边界上，同时这个框框要最小。

这种题乍一看可以二分，但是发现它其实不具有单调性，大的框框不包含小的。

然后就要考虑比较贪心的去思考这道题目，考虑这个框框的下界是啥？就是纵坐标差横坐标差中最大的那个。

取出这个之后我们去枚举这个框的左上角，然后用前缀和来判断。

这里我用的前缀和稍微有点小细节，即把右边的忽略右下角，上面的忽略左上角，左边忽略右上角，下面忽略左下角，这种建议自己手推一下。

时间复杂度 $O(n^2)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=2e3+5; 
int n,m,sum[INF][INF],ansx,ansy,ansz,suml[INF][INF],sumr[INF][INF];
char Map[INF][INF];
int Get(int l,int r,int ll,int rr) {
//	cout<<l<<" "<<r<<" "<<ll<<" "<<rr<<" fad?\n";
	if (rr-r+1==1) return Map[ll][rr]=='w';
	int sum1=sumr[ll-1][rr]-sumr[l-1][rr];
	int sum2=suml[l][rr-1]-suml[l][r-1];
	int sum3=sumr[ll][r]-sumr[l][r];
	int sum4=suml[ll][rr]-suml[ll][r];
	return sum1+sum2+sum3+sum4;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;int L=1e9,R=1e9,LL=0,RR=0; 
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			cin>>Map[i][j];
			if (Map[i][j]=='w') 
				L=min(L,i),R=min(R,j),LL=max(LL,i),RR=max(RR,j);
			
			suml[i][j]=suml[i][j-1]+(Map[i][j]=='w');
			sumr[i][j]=sumr[i-1][j]+(Map[i][j]=='w');
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(Map[i][j]=='w');
	int cnt=sum[n][m];ansz=1e9;
	if (!cnt) {
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=m;j++)
				cout<<Map[i][j];
			cout<<"\n";
		}
		return 0;
	}
//	if (!cnt && n==2000 && m==2000) cout<<"bomb\n";
//	cout<<Get(1,3,4,6)<<" "<<cnt<<" ?\n";
//	cout<<L<<" "<<R<<" fad?\n";
	RR-=R;LL-=L;RR++;LL++;
//	cout<<RR<<" "<<LL<<" fad?\n";
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			int len=min(n-i+1,m-j+1),ans=-1;
			if (len<LL || len<RR) continue;
			int Mid=min(len,max(RR,LL));
			if (Get(i,j,i+Mid-1,j+Mid-1)==cnt) ans=Mid;
			if (ans==-1) continue;
			if (ansz>ans) ansz=ans,ansx=i,ansy=j;
		}
	ansx+=ansz-1,ansy+=ansz-1;
	if (ansz==1e9) {cout<<"-1\n";return 0;}
	for (int i=ansx-ansz+1;i<=ansx;i++) {
		if (Map[i][ansy]=='.') Map[i][ansy]='+';
		if (Map[i][ansy-ansz+1]=='.') Map[i][ansy-ansz+1]='+';
	}
	for (int i=ansy-ansz+1;i<=ansy;i++) {
		if (Map[ansx][i]=='.') Map[ansx][i]='+';
		if (Map[ansx-ansz+1][i]=='.') Map[ansx-ansz+1][i]='+';
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++)
			cout<<Map[i][j];
		cout<<"\n";
	}
	return 0;
}
```

感谢阅读。

---

## 作者：_lxy_ (赞：0)

[题面](https://www.luogu.com.cn/problem/CF370D)

### 题意

一个 $n \times m$ 的显示器，有的点是白色的，有的点是黑色的，求一个最小的正方形方框，使所有白点都在方框上。

### 分析

首先确定方框的边长，这个长度就是最左最右白块横坐标的差和最上最下白块纵坐标的差的最大值。如果边长比显示器长、宽的最小值大，那么不可能找到符合要求的方框。确定边长后，我们可以枚举每一个点作为左上角，检查这个方框上的白点数是否和总白点数相等。再加上前缀和优化即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e3+7;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
inline int qmax(const int &x,const int &y){return x>y?x:y;}
inline int qmin(const int &x,const int &y){return x<y?x:y;}
int n,m,sz,col[MAXN][MAXN],row[MAXN][MAXN],t=MAXN,b,l=MAXN,r,cnt;
// col是列的前缀和，row是行的前缀和
char a[MAXN][MAXN];
int main()
{
	qread(n,m);int i,j;for(i=1;i<=n;i++) scanf("%s",a[i]+1);
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) if(a[i][j]=='w') t=qmin(t,i),b=qmax(b,i),l=qmin(l,j),r=qmax(r,j);
	sz=qmax(r-l,b-t); //计算边长
	if(!sz) //只有一个点
	{
		for(i=1;i<=n;i++) printf("%s\n",a[i]+1);
		return 0;
	}
	if(sz>=qmin(n,m)) return printf("-1\n"),0;
	for(i=1;i<=n;i++) 
	{
		for(j=1;j<=m;j++) 
		{
			col[j][i]=col[j][i-1]+(a[i][j]=='w'),row[i][j]=row[i][j-1]+(a[i][j]=='w');
			if(a[i][j]=='w') cnt++;
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(i+sz>n||j+sz>m) continue;
			int t=row[i][j+sz]-row[i][j-1]+row[i+sz][j+sz]-row[i+sz][j-1]+col[j][i+sz-2]-col[j][i]+col[j+sz][i+sz-2]-col[j+sz][i]; //方框上的白点数
			if(t==cnt)
			{
				for(int ii=i;ii<=i+sz;ii++) if(a[ii][j]!='w') a[ii][j]='+'; //左边
				for(int ii=i;ii<=i+sz;ii++) if(a[ii][j+sz]!='w') a[ii][j+sz]='+'; //右边
				for(int jj=j;jj<=j+sz;jj++) if(a[i][jj]!='w') a[i][jj]='+'; //上边
				for(int jj=j;jj<=j+sz;jj++) if(a[i+sz][jj]!='w') a[i+sz][jj]='+'; //下边
				for(i=1;i<=n;i++) printf("%s\n",a[i]+1);
				return 0;
			}
		}
	}
	printf("-1\n");
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：0)

首先找到最上、最下、最左、最右的 $\texttt{w}$ 位置，计算出横纵方向上 $\texttt{w}$ 的最远间隔，二者的最大值就是正方形边框的边长 $\textit{size}$。

我一开始的思路是根据 $\texttt{w}$ 的出现位置来分类讨论的，但这种写法细节有些多，为此贡献了 3 发 WA 以及 1 次 RE。

更简单的写法是枚举正方形边框左上角的坐标。

注意到到左上角横坐标其实只有三种情况：$0$、$X_\textit{min}$ 和 $X_\textit{max}-\textit{size}+1$，纵坐标同理。所以枚举 $9$ 种可能的位置就行了，对于每个位置判断在边框上的 $\texttt{w}$ 的数量是否和全部 $\texttt{w}$ 的数量相同，若相同则找到答案。


AC 代码：(Golang)

```go
package main

import (
	"bufio"
	"bytes"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n, m, i1, j1, cw int
	Fscan(in, &n, &m)
	i0, j0 := -1, m
	a := make([][]byte, n)
	for i := range a {
		Fscan(in, &a[i])
		l, r := bytes.IndexByte(a[i], 'w'), bytes.LastIndexByte(a[i], 'w')
		if l < 0 {
			continue
		}
		if i0 < 0 {
			i0 = i
		}
		i1 = i
		j0 = min(j0, l)
		j1 = max(j1, r)
		cw += bytes.Count(a[i], []byte{'w'})
	}
	sz := max(i1-i0, j1-j0)
	if sz == 0 {
		for _, r := range a {
			Fprintln(out, string(r))
		}
		return
	}
	if sz >= min(n, m) {
		Fprint(out, -1)
		return
	}
	for _, x := range []int{0, i0, i1 - sz} {
		if x < 0 || x+sz >= n {
			continue
		}
		for _, y := range []int{0, j0, j1 - sz} {
			if y < 0 || y+sz >= m {
				continue
			}
			c := 0
			for i := x; i <= x+sz; i++ {
				for j := y; j <= y+sz; {
					if a[i][j] == 'w' {
						c++
					}
					if i == x || i == x+sz {
						j++
					} else {
						j += sz
					}
				}
			}
			if c < cw {
				continue
			}
			for i := x; i <= x+sz; i++ {
				for j := y; j <= y+sz; {
					if a[i][j] == '.' {
						a[i][j] = '+'
					}
					if i == x || i == x+sz {
						j++
					} else {
						j += sz
					}
				}
			}
			for _, r := range a {
				Fprintln(out, string(r))
			}
			return
		}
	}
	Fprint(out, -1)
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
```


---

