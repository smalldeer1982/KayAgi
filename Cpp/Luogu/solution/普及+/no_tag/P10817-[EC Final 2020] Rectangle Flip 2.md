# [EC Final 2020] Rectangle Flip 2

## 题目描述

庞教授进入了一个地下城的陷阱房间。这个房间可以用一个 $n$ 行 $m$ 列的棋盘来表示。我们用 $(i, j)$ ($1\le i\le n$, $1\le j\le m$) 来表示第 $i$ 行第 $j$ 列的单元格。每秒钟，有一个单元格的地板会破裂（这样庞教授就不能再站在这个单元格上了）。经过 $nm$ 秒后，将没有单元格可供站立，庞教授将跌落到下一个（更深且更危险的）层级。

但庞教授知道冷静是克服任何挑战的关键。因此，他没有惊慌，而是计算了在每秒钟后，所有单元格都完好的矩形的数量（即，每个单元格在矩形中都没有破裂）。一个矩形由四个整数 $a, b, c$ 和 $d$ ($1\le a\le b\le n, 1\le c\le d\le m$) 表示，包含所有 $(i, j)$ 使得 $a\le i\le b, c\le j\le d$。总共有 $
\frac{n(n+1)}{2} \times \frac{m(m+1)}{2}$ 个矩形。

## 说明/提示

在示例中：在第一秒后，有 $3$ 个面积为 $1$ 的矩形和 $2$ 个面积为 $2$ 的矩形满足条件。因此第一行应该输出 $5$。在第二秒后，仅第二列中的单元格保持完好。答案应该是 $3$。在第三秒后，仅一个单元格保持完好。答案应该是 $1$。在第四秒后，所有单元格都破裂，所以答案应该是 $0$。

翻译者：[Immunoglobules](https://www.luogu.com.cn/user/1066251)

## 样例 #1

### 输入

```
2 2
1 1
2 1
1 2
2 2```

### 输出

```
5
3
1
0```

# 题解

## 作者：Ahws_rwhy (赞：4)

感谢我的队友，给了我一定的思路！

队友看了题，说：“用单调栈，$\mathcal O(N ^ 3)$，能过！”我看看了题，发现这做法可行。但是我想到了一种思路（本质一样，没用单调栈），于是，便写了下去 $\dots$ 大约 $50\min$ 切了。

题解：


很简单，对于每个删除的点，看会影响多少新矩形。枚举矩阵的左右每个位置，维护其的上下界 （ 可以外枚举下边界，确定下边界后，内枚举上边界 ），影响的数量是 $(x - l + 1 ) \times (r - x + 1)$（$l,r$ 代表此时上下边界形成公共部分的左边 $l$ 与右边 $r$），固定 $x$，枚举 $y$，就行了。

求完这个点会影响的好的矩形的数量，就在看这个点会对后面的点产生的影响。

这个影响无非就是，对后面的点在求每行能扩的最大边界的产生影响。

时间复杂度 $\mathcal O(N ^ 3)$。

code:


```cpp
void solve(int x, int y) {
	int bb = b[x][y], cc = c[x][y];
	for (int i = y; i >= 1; i--) {
		if (a[x][i] == 1) break;
		int bbb = b[x][y], ccc = c[x][y];
		bb = max(b[x][i], bb), cc = min(c[x][i], cc);
		for (int j = y; j <= m; j++) {
			if (a[x][j] != 0) break;
			bbb = max(b[x][j], bbb), ccc = min(c[x][j], ccc);
			maxx =  max(bb, bbb), minn = min(cc, ccc);
			ans -= (x - maxx + 1 ) * (minn - x + 1);
		}
	}
	a[x][y] = 1;
	for (int i = x - 1; i >= 1; i--) {
		if (a[i][y] == 0 )c[i][y] = x - 1;
		else break;
	}
	for (int i = x + 1; i <= n; i++) {
		if (a[i][y] == 0) b[i][y] = x + 1;
		else break;
	}
}
```

---

## 作者：Milthm (赞：3)

考虑对于每一次删除方格的过程，判断有多少矩形因为它的消失而不存在，用总矩形数量减去它就可以了。

直接模拟显然过不去，考虑维护每个位置上面第一个不存在的位置和下面第一个不存在的位置。对于每次一个方格的消失，我们枚举同行里该位置左边的位置，对于每一个左边的位置，我们再向右枚举右边的位置，利用刚才维护的“第一个不存在的位置”，我们就可以快速的计算出消失矩形的数量，且不会重复。

代码实现是这样的：


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 505
using namespace std;
int n,m,u[N][N],d[N][N],x,y,die[N][N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)d[i][j]=n+1;
	}
	int ans=n*(n+1)/2*m*(m+1)/2;
	for(int i=1;i<=n*m;++i){
		cin>>x>>y;int up=1,down=n;
		for(int l=y;l>=1;--l){
			if(die[x][l])break;
			up=max(up,u[x][l]+1);down=min(down,d[x][l]-1);
			int up2=up,down2=down;
			for(int r=y;r<=m;++r){
				if(die[x][r])break;
				up2=max(up2,u[x][r]+1);down2=min(down2,d[x][r]-1);
				ans-=(down2-x+1)*(x-up2+1);
			}
		}
		cout<<ans<<'\n';die[x][y]=1;
		for(int j=x-1;j>=1;--j)d[j][y]=min(d[j][y],x);
		for(int j=x+1;j<=n;++j)u[j][y]=max(u[j][y],x);
	}
	return 0;
}
```

这个算法表面看起来复杂度为 $O(nm^3)$，无法通过本题。

但是我们对于每一行再分析一下，发现每一次取 $\frac{m}2$ 位置能使两边的乘积最大，然后递归两边的区间，发现每一行最多计算次数的量级是 $\frac{m^2}4+\frac{m^2}8+\frac{m^2}{16}+\dots=O(m^2)$。

所以总时间复杂度为 $O(nm^2)$，可以通过本题。

---

## 作者：Cyx20110930 (赞：0)

# 题意简述

有一个 $n\times m$ 的棋盘，操作 $n\times m$ 次。每次删掉一个方格，询问还剩几个长方形。

# Sol

正难则反，既然数有多少个比较困难，就直接每次查找少了几个长方形，十分简单。

# Code

```
//暴力
//TEAM_NAME:CYX&LSY AK ICPC
//Problem B
//By CYX
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,down[505][505],up[505][505],grid[505][505];
signed main()
{
    cin>>n>>m;
    //预处理
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++){
            up[i][j]=0;
            down[i][j]=n+1;
        }
    }
    int ans=n*(n+1)/2*m*(m+1)/2,q=n*m;
    while(q--){
        int x,y;
        cin>>x>>y;
        int u=0,d=n+1;
        for(int j=y;j>=1;j--){//从1至y找u,d,看对每个格子能影响多大区域
            if(grid[x][j]) break;
            u=max(u,up[x][j]+1);
            d=min(d,down[x][j]-1);
            int a=u,b=d;
            for(int k=y;k<=m;k++){//从y至n找u,d,看对每个格子能影响多大区域
                if(grid[x][k]) break;
                a=max(a,up[x][k]+1);
                b=min(b,down[x][k]-1);
                ans-=abs(x-a+1)*abs(b-x+1);
            }
        }
        cout<<ans<<endl;
        //更新
        grid[x][y]=1;
        for(int j=x;j<=n;j++)up[j][y]=max(up[j][y],x);
        for(int j=x;j>=1;j--)down[j][y]=min(down[j][y],x);
    }
	return 0;
}
```

---

