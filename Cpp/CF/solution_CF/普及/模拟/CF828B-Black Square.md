# Black Square

## 题目描述

Polycarp has a checkered sheet of paper of size $ n×m $ . Polycarp painted some of cells with black, the others remained white. Inspired by Malevich's "Black Square", Polycarp wants to paint minimum possible number of white cells with black so that all black cells form a square.

You are to determine the minimum possible number of cells needed to be painted black so that the black cells form a black square with sides parallel to the painting's sides. All the cells that do not belong to the square should be white. The square's side should have positive length.

## 说明/提示

In the first example it is needed to paint $ 5 $ cells — $ (2,2) $ , $ (2,3) $ , $ (3,2) $ , $ (3,3) $ and $ (4,2) $ . Then there will be a square with side equal to three, and the upper left corner in $ (2,2) $ .

In the second example all the cells are painted black and form a rectangle, so it's impossible to get a square.

In the third example all cells are colored white, so it's sufficient to color any cell black.

## 样例 #1

### 输入

```
5 4
WWWW
WWWB
WWWB
WWBB
WWWW
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 2
BB
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 3
WWW
WWW
WWW
```

### 输出

```
1
```

# 题解

## 作者：_Starlit__Sky_ (赞：5)

# 洛谷 CF828B 题解

[题目传送门](https://www.luogu.com.cn/problem/CF828B)

## 题目算法

模拟

## 题目思路

题目给出了一张只含有黑色方格 `B` 和 白色方格 `W` 的方格纸，现在需要将最少的黑色方格 `B` 变成白色方格 `W`，从而在方格纸上形成一个只由黑色方格 `B` 组成的正方形，并且在此正方形之外没有黑色方格 `B`，若无解，输出 `-1`。

我们首先需要：

- 构建 $minx$ 和 $maxx$ 变量，分别表示 x 坐标最小和最大的黑色方格的 x 坐标（即 x 轴上位置最靠前和最靠后的黑色方格的 x 坐标）。

- 构建 $miny$ 和 $maxy$ 变量，分别表示 y 坐标最小和最大的黑色方格的 y 坐标（即 y 轴上位置最靠上和最靠下的黑色方格的 y 坐标）。

- 记方格纸中黑色方格的数量为 $cnt$。

此时，$maxx - minx + 1$ 就表示在一行内黑色方块 x 坐标的最大差值，$maxy - miny + 1$ 就表示在一列内黑色方块 y 坐标的最大差值。

我们可以发现，如果正方形的边长小于一行内黑色方块 x 坐标的最大差值或一列内黑色方块 y 坐标的最大差值，就会在此正方形之外仍存留黑色方格 `B`。

所以要想使正方形之外没有黑色方格 `B`，且黑色方格 `B` 变成白色方格 `W` 的数量最少，就得使正方形的边长刚好不小于一行内黑色方块 x 坐标的最大差值或一列内黑色方块 y 坐标的最大差值，即正方形的边长 $a = \max(maxx - minx + 1,maxy - miny + 1)$，且正方形的面积 $S = a^2$。

所以需要涂成黑色的方格的最小数量就等于需要涂成的黑色正方形的面积 $S$ 减去现在方格纸中已有的黑色方格的数量（面积）$cnt$，所以答案为 $S - cnt$。

但是如果 $a > m$ 或 $a > n$，即正方形边长超出了方格纸，则无解，输出 `-1` 即可。

但是如果方格纸中没有黑色的方格，我们就可以只绘制一个黑色方格，从而形成一个边长为一的正方形，输出 `1` 即可。

## 代码

```python
### 变量定义 & 数据读取 ###

n,m = map(int,input().split()) # 行数和列数
lst = [input() for _ in range(n)] # 方格纸
minx = float("inf") # x轴上位置最靠前的黑色方格的x坐标
maxx = -1 # x轴上位置最靠后的黑色方格的x坐标
miny = float("inf") # y轴上位置最靠上的黑色方格的y坐标
maxy = -1 # y轴上位置最靠下的黑色方格的y坐标
cnt = 0 # 黑色方格的个数

### 数据处理 ###

# 循环遍历方格纸
for i in range(n):
    for j in range(m):
        if lst[i][j] == 'B': # 如果当前格子是黑色
            minx = min(minx,j) # 更新x轴上位置最靠前的黑色方格的x坐标
            maxx = max(maxx,j) # 更新x轴上位置最靠后的黑色方格的x坐标
            miny = min(miny,i) # 更新y轴上位置最靠上的黑色方格的y坐标
            maxy = max(maxy,i) # 更新y轴上位置最靠下的黑色方格的y坐标
            cnt += 1 # 黑色方格个数+1
a = max(maxx - minx + 1, maxy - miny + 1) # 正方形边长
S = a * a # 正方形面积

### 输出 ###

if cnt == 0: print(1) # 如果没有黑色方格，就可以只绘制一个黑色方格，从而形成一个边长为一的正方形
elif a > n or a > m: print(-1) # 如果正方形边长超出了方格纸，则无解
else: print(S - cnt) # 输出正方形面积减去已经涂黑的面积（即需要涂成黑色的方格的最小数量）
```


---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF828B)

[CF传送门](https://codeforces.com/problemset/problem/828/B)

[AC记录](https://codeforces.com/contest/828/submission/287218335)

# 题意简述
给定一个大小为 $n\times m$ 的方格纸，其中有黑色和白色格子，问至少将几个白色格子变为黑色格子才能使所有黑色格子组成正方形？
# 题解
大体思路就是**框出一个正方形**，让该正方形中都为黑色格子（当然面积越小越好）  
框的过程大概分成三步：
1. 求出所有黑色格子中的最上端，最下端，最左端，最右端。
2. 用这四端即可框出一个矩形，其中都是黑色格子，且面积最小。
3. 框出一个能够覆盖该矩形的最小正方形（取矩形两边的最大值）。

举个栗子（样例 1）：
![](https://cdn.luogu.com.cn/upload/image_hosting/pg9x6pa7.png)

原本的黑色格子就是黑色部分，其中的四端分别是两个红点的位置。  
此时根据红点画出矩形（白色变黑色的格子是红色部分）。  
再做出包含矩形的最小正方形（边长为 $3$）（白色变黑色的格子是绿色部分）。  
最后**用正方形面积减去原来黑色格子的个数就是题目所求。**
# AC Code
```cpp
#include<iostream>
using namespace std;
#define int long long
int n,m,x1=0x3f3f3f3f,y1=0x3f3f3f3f,x2,y2,cnt;
char a[105][105];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='B'){
				x1=min(x1,i);
				y1=min(y1,j);
				x2=max(x2,i);
				y2=max(y2,j);//记录四端的位置
				cnt++;//记录黑色格子个数
			}
		}
	int l=x2-x1+1,r=y2-y1+1;
	l=max(l,r);//在矩形两边中取最长
	if(cnt==0) cout<<1;//没有黑色格子，仅需随便将一个白色格子变为黑色格子
	else if(l>n||l>m) cout<<-1;//正方形超出网格，无解
	else cout<<l*l-cnt;//用正方形面积减去黑色格子的个数
	return 0;
}
```

---

## 作者：long_long__int (赞：0)

# 题目解法
为了构建正方形，我们要先把正方形的边长算出来。正方形的边长怎么算呢？我们可以记录一下黑色方格的最大和最小 $y$ 坐标和 $x$ 坐标。再把最大和最小的 $x$ 和 $y$ 坐标之差算出来（$maxx-minx$ 和 $maxy-miny$），再取最大值就是边长。如果边长大于 $m$ 或 $n$，就说明正方形边长超出了边界，无解。还有，记得特判没有黑色方格的情况，这时只需把一个白色方格染成黑色即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
bool haveB=false;
int n,m,maxx=INT_MIN,maxy=INT_MIN,minx=INT_MAX,miny=INT_MAX,B;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch;
			cin>>ch;
			if(ch=='B'){
				haveB=true;
				minx=min(minx,i);
				miny=min(miny,j);
				maxx=max(maxx,i);
				maxy=max(maxy,j);
				B++;
			}
		}
	}
	if(haveB==false){//特判没有黑色 
		return printf("1"),0;
	}
//	printf("%d %d %d %d\n",minx,maxx,miny,maxy);
	int bianchang=max(maxx-minx+1,maxy-miny+1);
	if(bianchang>n or bianchang>m) return printf("-1\n"),0;
	printf("%d\n",bianchang*bianchang-B);
	return 0;
}
```

[通过记录。](https://codeforces.com/problemset/submission/828/291312859)

---

## 作者：rain_dew (赞：0)

[原题目链接](https://www.luogu.com.cn/problem/CF828B)

一道简单题目，建议评橙。

### 题意：
将最少的白色方格 `W` 变为黑色方格 `B`，使得**所有**黑色方格形成一个黑色**正方形**。

### 思路：
根据题目，要把**所有**黑色方格拼凑成正方形，需要记录出现黑色方格出现的最先最前位置与最晚最后的位置。

先考虑全是白色的情况（如同样例 $3$），设 $sum$ 记录黑色方格出现数量。显然可见此时没有黑色方格，任意 $1$ 个白色方格均可成为黑色方格后形成最小解，此时输出 $1$ 即可。

我们设 $minx$ 为最早记录的横坐标，$maxx$ 为最晚记录的横坐标，$miny$ 为最早记录纵坐标，$maxy$ 为最晚记录纵坐标。

那么 $maxx-minx+1$ 或 $maxy-miny+1$ 就分别为此正方形的边长，但需要将所有黑色方格利用，所以取最大值（如下图样例所示，绿色为黑色方格记录值，红色为为补充为正方形的白色方格），若此时超界（即无法构成正方形时），输出 $-1$ 并退出。

![](https://cdn.luogu.com.cn/upload/image_hosting/og2jiatu.png)

否则，计算在正方形中一共需要多少个黑色方块（边长与边长的乘积）与之前所记录当前已经出现的方块（即 $sum$）的差即为答案。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,sum,l;
char ch[105][105];
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf(" %c",&ch[i][j]);
	int xmin=101,ymin=101,xmax=0,ymax=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (ch[i][j]=='B')
			{
				sum++;
				xmin=min(xmin,i);
				ymin=min(ymin,j);
				xmax=max(xmax,i);
				ymax=max(ymax,j);
			}
	if (!sum)
	{
		printf("1");
		return 0;
	}
	l=max(xmax-xmin+1,ymax-ymin+1);  //最大正方形边长 
	if (l>n || l>m)
	{
		printf("-1");
		return 0;
	}
	printf("%d",l*l-sum);
	return 0;
}
```

---

## 作者：_cpp (赞：0)

~~淼题~~

#### 思路：

枚举每一个 $B$ 所在的坐标，将处于最左上，最左下，最右上，最右下的 $B$ 点的坐标记录下来。坐标两两相减，算出要构建的正方形的边长 $ans$。但当 $ans > n$ 或 $ans > m$ 时，不可能构建出正方形。

##### 配上笔者思路解样例一的手绘插图：
![](https://cdn.luogu.com.cn/upload/image_hosting/xchx5caq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图所示，我们只要找到正方形的四个顶点，就能计算出边长。最后正方形的边长为相邻两点最长的距离。算出面积后，还要减去原来已有的 $B$。
#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x1,x2 = INT_MAX,x3,x4 = INT_MAX,yy1,y2,y3 = INT_MAX,y4 = INT_MAX,ans,s3;
char a[110][110];
int main()  
{ 
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            cin >> a[i][j];
            if(a[i][j] == 'B'){
                s3++;  //计算原有的B
                x1 = max(i,x1);
                yy1 = max(j,yy1);
                x2 = min(x2,i);
                y2 = max(y2,j);
                x3 = max(x3,i);
                y3 = min(y3,j);
                x4 = min(x4,i);
                y4 = min(y4,j); //枚举矩阵的顶点
            }
        }
    ans = max(max(x1 - x2 + 1,x3 - x4 + 1),max(yy1 - y3 + 1,y2 - y4 + 1));  //计算边长
    if(ans == -2147483646) cout << 1;  //当矩阵里没有b时
    else if(ans > n || ans > m) cout << -1; //不可能构建出正方形
    else cout << ans * ans - s3;  
    return 0;  
}
```


---

## 作者：Escapism (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF828B)

简单思维题。建议评橙

# 题意

有一张大小为 $n \times m$ 的方格纸, 一些方格涂成了黑色，其余的为白色。

现在要把一部分的白色方格涂成黑色，使得所有的黑色方格构成一个正方形。

# 思路

根据样例1，我们可以找到思路。

我们可以假设横轴上的坐标最大与最小点的横轴坐标为 $x_1$ 和 $x_2$，纵轴上的坐标最大与最小点的纵轴坐标为 $y_1$ 和 $y_2$。那么我们最后连成的正方形的边长就是 $\max(x_1 - x_2,y_1 - y_2)$。

剩下来的就很简单了，如果长度或宽度不足以满足正方形边长，那么输出 $-1$。如果满足，那么就求出正方形面积并减去原来就有涂色的正方形个数即可。

同时，我们再特判一下，如果原图内本来就涂色的正方形个数为 $0$，输出 $1$。

# 代码

太丑了，不放了。




---

## 作者：封禁用户 (赞：0)

题目让我们把尽可能少的 W 改成 B ，并使得最后的字符 B 组成一个正方形 。

在 n 行字符中 ，设第 i 行第一次出现字符 B ，第 j 行最后一次出现字符 B（若未出现 B 则 i=j=0），为了使这两行中的B包含在正方形中 ，边长 $a\ge j-i+1$ 。同理 ，在m列字符中 ，设第 k 列第一次出现字符B ，第 l 列最后一次出现字符 B（若未出现 B 则 k=l=0），边长 $a\ge l-k+1$ 。

由不等式得 $a\ge max(j-i,l-k)+1$ ，则 a 取值 $max(j-i,l-k)+1$ ，答案就是 $a^2-$B的个数 。注意特判 a 比 n 或 m 大的情况 ，输出-1 。
```cpp
#include <cmath>
#include <iostream>
using namespace std;
int main() {
	int n,m,a[105]= {0},b[105]= {0},ans=0,dn=0,dm=0;
	char x;
	cin>>n>>m;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=m; ++j) {
			cin>>x;
			if(x=='B') {
				a[i]=1;
				b[j]=1;
				ans++;
			}
		}
	}
	for(int i=1; i<=n; ++i) {
		if(a[i]==1) {
			dn=i;
			break;
		}
	}
	for(int i=n; i>=1; --i) {
		if(a[i]==1) {
			dn=i-dn+1;
			break;
		}
	}
	for(int i=1; i<=m; ++i) {
		if(b[i]==1) {
			dm=i;
			break;
		}
	}
	for(int i=m; i>=1; --i) {
		if(b[i]==1) {
			dm=i-dm+1;
			break;
		}
	}
	dn=max(dn,dm);
	if(dn>n || dn>m) cout<<-1;
	else if(dn==0) cout<<1;
	else cout<<dn*dn-ans;
	return 0;
}
```


---

