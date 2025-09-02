# Frames

## 题目描述

One day Vasya got hold of a sheet of checkered paper $ n×m $ squares in size. Our Vasya adores geometrical figures, so he painted two rectangles on the paper. The rectangles' sides are parallel to the coordinates' axes, also the length of each side of each rectangle is no less than 3 squares and the sides are painted by the grid lines. The sides can also be part of the sheet of paper's edge. Then Vasya hatched all squares on the rectangles' frames.

Let's define a rectangle's frame as the set of squares inside the rectangle that share at least one side with its border.

A little later Vasya found a sheet of paper of exactly the same size and couldn't guess whether it is the same sheet of paper or a different one. So, he asked you to check whether the sheet of paper he had found contains two painted frames and nothing besides them.

Please note that the frames painted by Vasya can arbitrarily intersect, overlap or even completely coincide.

The coordinates on the sheet of paper are introduced in such a way that the $ X $ axis goes from top to bottom, the $ x $ coordinates of the squares' numbers take values from $ 1 $ to $ n $ and the $ Y $ axis goes from the left to the right and the $ y $ coordinates of the squares' numbers take values from $ 1 $ to $ m $ .

## 说明/提示

In the first sample there are two frames on the picture. The first one is:

`###..<br></br>#.#..<br></br>###..<br></br>.....<br></br>`The second one is:

`#####<br></br>#...#<br></br>#...#<br></br>#####<br></br>`In the second sample the painted figures are not frames. Note that the height and width of valid frames is no less than 3.

## 样例 #1

### 输入

```
4 5
#####
#.#.#
###.#
#####
```

### 输出

```
YES
1 1 3 3
1 1 4 5
```

## 样例 #2

### 输入

```
5 6
...###
...###
#####.
#...#.
#####.
```

### 输出

```
NO
```

# 题解

## 作者：panyf (赞：2)

首先进行一个类似离散化的操作。

先把所有全是点的行和列去掉。

然后对于连续的 $k$ 行或 $k$ 列满足完全相同，可以只保留 $5$ 行或 $5$ 列，其余的去掉。

画几张图枚举矩形相对位置的所有情况，容易发现这样一定不会影响答案。

如果存在方案，最多只剩下 $19$ 行 $19$ 列。

然后随便跑一个复杂度 $19$ 的很多次方的暴力即可。

[提交记录](https://codeforces.ml/contest/152/submission/127180755)

---

## 作者：int08 (赞：0)

## 前言

_"So, tell your story and make something meaningful."_

_"Because, it takes a long time to make something that can't truly be replaced."_

## 题意
谴责一下原翻译，条件都没翻全。

给出一个 $n\times m$ 字符矩形，每个字符是 `.` 或 `#`，你需要识别出两个边框由 `#` 组成的矩形，且这两个矩形的长和宽都大于 $2$，且**这两个矩形边框包含了图中所有 `#`**，**允许两个矩形重合**。

# Solution

笨办法，不过能过。

考虑枚举一个矩形的右下角，发现位于最下面一列最靠右的那个 `#` 必然是一个矩形的右下角，接着枚举一下这个矩形的长宽。

照理来说这样已经超时了，但是合法的长宽数**不能超过三个**。

考虑观察形状：

```
#.#.#...#
#.#.#...#
#########
```

每一个合法的矩形宽意味着最底下一列上面会伸出一个长为 $2$ 的小枝枝，但是我们实际只使用了
一个，剩下的只好留给第二个矩形，但是第二个矩形最多也只能用两个，说明小枝枝也就是合法的宽数量最多 $3$ 个。

那枚举长宽，现在剩下的每个点都要被包含在第二个矩形里，发现第二个矩形的四条边可选项也不多，具体来说只能在下面 $4$ 个数中选两个：

1. 第一个矩形的横/竖对应位置。
2. 不被第一个举行包含的 `#` 中，横纵坐标的最小/大值。

于是再枚举第二个矩形的四条边，检查答案是否合法可以 $O(n^2)$，于是整个问题就是 $O(n^2)$ 的复杂度并带上 $3^2{\binom{4}{2} }^2=324$ 的常数。

别急，过不了，WA on #15，来看看 #15 是何方神圣。


```
10 10
.....####.
.....####.
.....####.
.....####.
.....####.
.....####.
.....####.
.....####.
..........
..........

answer:
YES
1 6 8 8
1 7 8 9
```

在我们上面的推导中我们认为第一个矩形只要有超过 $3$ 个可行长宽一定无解，看来错了。

改为选最长的三个长宽检验，这次对了。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1005
char c[N][N];
bool o[N][N];
#define frame pair<pair<int,int>,pair<int,int>>
#define fi first
#define se second
int n,m,i,j,cnt;
bool check(frame x,frame y)
{
	if(x.se.fi-x.fi.fi<=1||x.se.se-x.fi.se<=1||y.se.fi-y.fi.fi<=1||y.se.se-y.fi.se<=1) return 0;
	memset(o,0,sizeof(o));
	for(int i=x.fi.se;i<=x.se.se;i++) if(c[x.fi.fi][i]=='.'||c[x.se.fi][i]=='.') return 0;
	for(int i=x.fi.fi;i<=x.se.fi;i++) if(c[i][x.fi.se]=='.'||c[i][x.se.se]=='.') return 0;
	for(int i=y.fi.se;i<=y.se.se;i++) if(c[y.fi.fi][i]=='.'||c[y.se.fi][i]=='.') return 0;
	for(int i=y.fi.fi;i<=y.se.fi;i++) if(c[i][y.fi.se]=='.'||c[i][y.se.se]=='.') return 0;
	
	for(int i=x.fi.se;i<=x.se.se;i++) o[x.fi.fi][i]=o[x.se.fi][i]=1;
	for(int i=x.fi.fi;i<=x.se.fi;i++) o[i][x.fi.se]=o[i][x.se.se]=1;
	for(int i=y.fi.se;i<=y.se.se;i++) o[y.fi.fi][i]=o[y.se.fi][i]=1;
	for(int i=y.fi.fi;i<=y.se.fi;i++) o[i][y.fi.se]=o[i][y.se.se]=1;
	int cn=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(o[i][j]) cn++;
	if(cn==cnt)
	{
		cout<<"YES\n";
		cout<<x.fi.fi<<" "<<x.fi.se<<" "<<x.se.fi<<" "<<x.se.se<<endl;
		cout<<y.fi.fi<<" "<<y.fi.se<<" "<<y.se.fi<<" "<<y.se.se<<endl;
		exit(0);
	}	
}
void solve(frame x)
{
	memset(o,0,sizeof(o));
	for(int i=x.fi.se;i<=x.se.se;i++) if(c[x.fi.fi][i]=='.'||c[x.se.fi][i]=='.') return;
	for(int i=x.fi.fi;i<=x.se.fi;i++) if(c[i][x.fi.se]=='.'||c[i][x.se.se]=='.') return;
	for(int i=x.fi.se;i<=x.se.se;i++) o[x.fi.fi][i]=o[x.se.fi][i]=1;
	for(int i=x.fi.fi;i<=x.se.fi;i++) o[i][x.fi.se]=o[i][x.se.se]=1;
	int in=n+1,xn=0,im=m+1,xm=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(!o[i][j]&&c[i][j]=='#') in=min(in,i),xn=max(xn,i),im=min(im,j),xm=max(xm,j);
	if(!xn)
	{
		cout<<"YES\n";
		cout<<x.fi.fi<<" "<<x.fi.se<<" "<<x.se.fi<<" "<<x.se.se<<endl;
		cout<<x.fi.fi<<" "<<x.fi.se<<" "<<x.se.fi<<" "<<x.se.se<<endl;
		exit(0);
	}
	vector<int> okx={in,xn,x.fi.fi,x.se.fi},oky={im,xm,x.fi.se,x.se.se};
	sort(okx.begin(),okx.end()),sort(oky.begin(),oky.end());
	for(int i=0;i<okx.size();i++)
		for(int j=i+1;j<okx.size();j++)
			for(int k=0;k<oky.size();k++)
				for(int l=k+1;l<oky.size();l++)
					check(x,{{okx[i],oky[k]},{okx[j],oky[l]}});
}
int lx,ly;
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		{
			cin>>c[i][j];
			if(c[i][j]=='#') lx=i,ly=j,cnt++;
		}
	if(lx<3||ly<3) cout<<"NO",exit(0);
	vector<int> okx,oky;
	for(i=1;i<=lx-2;i++) if(c[i][ly-1]=='#'&&c[i][ly-2]=='#') okx.push_back(i);
	for(i=1;i<=ly-2;i++) if(c[lx-1][i]=='#'&&c[lx-2][i]=='#') oky.push_back(i);
	if(lx<3||ly<3) cout<<"NO",exit(0);
	sort(okx.begin(),okx.end());
	sort(oky.begin(),oky.end());
	for(i=0;i<min(int(okx.size()),3);i++)
		for(j=0;j<min(int(oky.size()),3);j++) solve({{okx[i],oky[j]},{lx,ly}});
	cout<<"NO";
	return 0;
}
```
## 后记

_"So after three years, here is my 'data', here is my 'unreplacable'..."_

_"Here is my 'Wireframe'."_
# The End.

---

