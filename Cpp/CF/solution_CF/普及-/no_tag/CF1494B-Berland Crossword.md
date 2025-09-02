# Berland Crossword

## 题目描述

Berland crossword is a puzzle that is solved on a square grid with $ n $ rows and $ n $ columns. Initially all the cells are white.

To solve the puzzle one has to color some cells on the border of the grid black in such a way that:

- exactly $ U $ cells in the top row are black;
- exactly $ R $ cells in the rightmost column are black;
- exactly $ D $ cells in the bottom row are black;
- exactly $ L $ cells in the leftmost column are black.

Note that you can color zero cells black and leave every cell white.

Your task is to check if there exists a solution to the given puzzle.

## 说明/提示

Here are possible solutions to testcases $ 1 $ , $ 2 $ and $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1494B/d621c171f085bccb3662990f2929812003bf6b92.png)

## 样例 #1

### 输入

```
4
5 2 5 3 1
3 0 0 0 0
4 4 1 4 0
2 1 1 1 1```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：Eason_AC (赞：3)

## Content
有一种叫做 Berland crossword 的拼图游戏。这个拼图由 $n$ 行 $n$ 列组成，你可以将里面的一些格子涂成黑色。现在给出 $T$ 个这样的拼图，每个拼图都含有如下限制：

- 第一行最多有 $u$ 个黑色格子。
- 第 $n$ 列最多有 $r$ 个黑色格子。
- 第 $n$ 行最多有 $d$ 个黑色格子。
- 第一列做多有 $l$ 个黑色格子。

问是否有满足如上限制的拼图（不需要输出方案）。

**数据范围：$2\leqslant n\leqslant 100$，$0\leqslant u,r,d,l\leqslant n$，$1\leqslant T\leqslant 10^3$。**
## Solution
第二题还是一样的暴力，只不过可能和其他那些直接暴力枚举 $16$ 种情况的不太一样，这里讲讲。

首先，我们可以想到，如果 $u=n$，那么第一列和第 $n$ 列都至少有 $1$ 个黑色格子，$d=n$ 同理；如果 $r=n$，那么第一行和第 $n$ 行都至少有一个黑色格子，$l=n$ 同理。

另外还有一种比较特殊的情况，就是当上面的四个数中的某些数 $=n-1$。如果 $u=n-1$，那么第一列和第 $n$ 列中的一列至少会有 $1$ 个黑色格子，$d=n-1$ 同理；如果 $r=n-1$，那么第一行和第 $n$ 行中的一行至少会有 $1$ 个黑色格子，$l=n-1$ 同理。

于是，我们不妨先设出所有的 $u,r,d,l$ 所在的行列在输入限制下的最小黑色格子数。先把所有的 $=n$ 的情况所影响的行列的最小黑色格子数加 $1$，然后对于 $=n-1$ 的情况，我们看当前还有那些行列的最小黑色格子数小于输入限制，就把那个行列的最小黑色格子数加 $1$（如果两个行或者两个列当前的最小黑色格子数都小于输入限制，随便加进去哪一个行列都行）。最后再来判断是否超过了输入限制即可。

如果上面的文字你并没有听懂，可以参考一下下面的代码实现。
## Code
```cpp
int n, u, r, d, l, limit[7], num[7];
 
int main() {
	MT {
		memset(limit, 0, sizeof(limit));
		memset(num, 0, sizeof(num));
		n = Rint, u = Rint, r = Rint, d = Rint, l = Rint;
		if(u >= n - 1) limit[1] = u - (n - 2);
		if(r >= n - 1) limit[2] = r - (n - 2);
		if(d >= n - 1) limit[3] = d - (n - 2);
		if(l >= n - 1) limit[4] = l - (n - 2);
		num[1] += (limit[2] == 2) + (limit[4] == 2), num[2] += (limit[1] == 2) + (limit[3] == 2), num[3] += (limit[2] == 2) + (limit[4] == 2), num[4] += (limit[1] == 2) + (limit[3] == 2);
		if(limit[1] == 1) {(num[2] < r ? num[2] : num[4])++;}
		if(limit[2] == 1) {(num[1] < u ? num[1] : num[3])++;}
		if(limit[3] == 1) {(num[2] < r ? num[2] : num[4])++;}
		if(limit[4] == 1) {(num[1] < u ? num[1] : num[3])++;}
		puts((u >= num[1] && r >= num[2] && d >= num[3] && l >= num[4]) ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：_Violet_Evergarden (赞：2)

看到题解有些空缺，来发一发。

# 思路：
由于题目只给了我们一个矩形边缘的数据且不需要输出方案，所以我们只需要让它尽可能成立即可，然后我们发现只需要让那些超过 $n-2$ 的行和列的数量储存下来，然后逐一判断是否是违法情况即可。见代码易懂。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a,b,c,d;
int flag1,flag2,flag3,flag4;
int m;
int main()
{
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>n;
		cin>>a>>b>>c>>d;
		flag1=max(0,a-n+2);
		flag2=max(0,b-n+2);
		flag3=max(0,c-n+2);
		flag4=max(0,d-n+2);
		if((a+c)<(flag2+flag4)||(b+d)<(flag1+flag3)||a<(flag2/2+flag4/2)||c<(flag2/2+flag4/2)||b<(flag1/2+flag3/2)||d<(flag1/2+flag3/2)){
			cout<<"NO"<<endl;
		}
		else{
			cout<<"YES"<<endl;
		}
	}
	return 0;
} 
```


---

## 作者：Booksnow (赞：2)

# Berland Crossword

## 题目大意

给出有一个 $n\times n$ 的矩阵，最开始矩阵里每个坐标的颜色都为白色，你可以将里面的一些各自涂成黑色，判断如下这样的矩阵是否存在：

- 第一行有 $u$ 个黑色格子

- 第 $n$ 行有 $d$ 个黑色格子

- 第一列有 $l$ 个黑色格子

- 第 $n$ 列有 $r$ 个黑色格子

## 分析

我们发现，此题让人很烦躁的地方在于，他的四个角落**不仅会影响行的黑格个数，还会影响列的黑格个数**，而其他的点则丝毫不会影响我们将要进行的这件事情。

再看数据范围，我们发现数据范围其实是很小的，所以我们把这四个点给拿掉，**直接讨论**着个点是否变黑即可，讨论完成后只需要判断其他点是否能够将剩下的黑格填满，如果不行，则排除这种情况，知道讨论完成所有情况或找到一组正确解答。

而此时我们的时间复杂度前也只是多了一个常数 $16$ ，完全不用担心超时的问题。整体的时间复杂度即为 $O(16T)$ 。
## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline bool check(int n,int u,int r,int d,int l)
{
	if(u>n-2||r>n-2||d>n-2||l>n-2) return false;
	return true;
}
int main()
{
	T=read();
	while(T--){
		int N=read(),U=read(),R=read(),D=read(),L=read();
		bool flag=false;
		int u=U,r=R,d=D,l=L;
		for(register int i=0;i<=1;i++){
			for(register int j=0;j<=1;j++){
				for(register int k=0;k<=1;k++){
					for(register int p=0;p<=1;p++){
						u=U,r=R,d=D,l=L;
						if(i==1) u--,l--;
						if(j==1) u--,r--;
						if(k==1) d--,l--;
						if(p==1) d--,r--;
						if(u<0||d<0||l<0||r<0) continue;
						if(check(N,u,r,d,l)) { flag=true; break; }
					}
					if(flag) break;
				}
				if(flag) break;
			}
			if(flag) break;
		}
		if(flag) puts("YES");
		else puts("NO");
	}
	return 0;
} 
```


---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1494B)

---

# 思路：

容易发现除了四个角以外，每条边上的格子不会相互影响，所以关键是四个角的状态。穷举所有四个角的情况，然后逐一判断。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,u,r,d,l; 
bool judge(int x,int y,int z,int w){
	if(x+y+n-2<u||x+y>u){
		return 0;
	}
	if(y+z+n-2<r||y+z>r){
		return 0;
	}
	if(z+w+n-2<d||z+w>d){
		return 0;
	}
	if(x+w+n-2<l||x+w>l){
		return 0;
	}
	return 1;
}
bool solve(){
	for(int x=0;x<=1;x++){
		for(int y=0;y<=1;y++){
			for(int z=0;z<=1;z++){
				for(int w=0;w<=1;w++){
					if(judge(x,y,z,w)){
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>u>>r>>d>>l;
		if(solve()){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

完结撒花~

---

## 作者：_Michael0727_ (赞：0)

# 题解：CF1494B Berland Crossword

[文章食用效果更佳](https://www.luogu.com.cn/article/8tv59ccl)

---

## 审题

[题目传送门](https://www.luogu.com.cn/problem/CF1494B)

### 题意

有一种叫做 Berland crossword 的拼图游戏。这个拼图由 $n$ 行 $n$ 列组成，你可以将里面的一些格子涂成黑色。现在给出 $T$ 个这样的拼图，每个拼图都含有如下限制：

- 第 $1$ 行恰好有 $u$ 个黑色格子。
- 第 $n$ 列恰好有 $r$ 个黑色格子。
- 第 $n$ 行恰好有 $d$ 个黑色格子。
- 第 $1$ 列恰好有 $l$ 个黑色格子。

问是否有满足如上限制的拼图（不需要输出方案）。

---

## 思路

由于只需要考虑边缘的格子数量，所以可以用暴力。

由于角上的格子对两条边都有影响，所以可以对它进行分类讨论。

总共有以下 16 种情况：

- 角上全不放

- 放右上

- 放右下

- 放左下

- 放左上

- 放右上右下

- 放右下左下

- 放左上左下

- 放左上右上

- 放左上右下或右上左下

- 放左上右上右下

- 放右上右下左下

- 放右上右下左下

- 放右下左下左上

- 放左下左上右上

- 角上全放

每种情况对放在边上的剩余格子数量进行判断是否不大于 $n$。

为了缩短代码，我还编了一个判断函数进行判断。

---

**AC 代码**

```cpp
# include <bits/stdc++.h>
using namespace std ;
int n , u , r , d , l , q ;
bool chk ( int x )
{
	if ( x < 0 )
	{
		return false ;
	}
	return ( x <= n - 2 ) ;
}
int main ( )
{
	cin >> q ;
	while ( q -- )
	{
		cin >> n >> u >> r >> d >> l ;
		if ( chk ( u ) && chk ( r ) && chk ( d ) && chk ( l ) ) // 角上全不放
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 1 ) && chk ( r - 1 ) && chk ( d ) && chk ( l ) ) // 放右上
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u ) && chk ( r - 1 ) && chk ( d - 1 ) && chk ( l ) ) // 放右下
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u ) && chk ( r ) && chk ( d - 1 ) && chk ( l - 1 ) ) // 放左下
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 1 ) && chk ( r ) && chk ( d ) && chk ( l - 1 ) ) // 放左上
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 2 ) && chk ( r - 1 ) && chk ( d ) && chk ( l - 1 ) ) // 放右上右下
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 1 ) && chk ( r - 2 ) && chk ( d - 1 ) && chk ( l ) ) // 放右下左下
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u ) && chk ( r - 1 ) && chk ( d - 2 ) && chk ( l - 1 ) )  // 放左上左下
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 1 ) && chk ( r ) && chk ( d - 1 ) && chk ( l - 2 ) ) // 放左上右上
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 1 ) && chk ( r - 1 ) && chk ( d - 1 ) && chk ( l - 1 ) ) // 放左上右下或右上左下
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 2 ) && chk ( r - 2 ) && chk ( d - 1 ) && chk ( l - 1 ) ) // 放左上右上右下
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 1 ) && chk ( r - 2 ) && chk ( d - 2 ) && chk ( l - 1 ) ) // 放右上右下左下
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 1 ) && chk ( r - 1 ) && chk ( d - 2 ) && chk ( l - 2 ) ) // 放右下左下左上
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 2 ) && chk ( r - 1 ) && chk ( d - 1 ) && chk ( l - 2 ) ) // 放左下左上右上
		{
			cout << "YES" << endl ;
			continue ;
		}
		if ( chk ( u - 2 ) && chk ( r - 2 ) && chk ( d - 2 ) && chk ( l - 2 ) ) // 角上全放
		{
			cout << "YES" << endl ;
			continue ;
		}
		cout << "NO" << endl ;
	}
	return 0 ;
}
```

---

[AC 记录](https://www.luogu.com.cn/record/163809476)

---

## 作者：Tulip_ (赞：0)

### 题意

有一种叫做 Berland crossword 的拼图游戏。这个拼图由 $n$ 行 $n$ 列组成，你可以将里面的一些格子涂成黑色。现在给出 $T$ 个这样的拼图，每个拼图都含有如下限制：

- 第 $1$ 行恰好有 $u$ 个黑色格子。
- 第 $n$ 列恰好有 $r$ 个黑色格子。
- 第 $n$ 行恰好有 $d$ 个黑色格子。
- 第 $1$ 列恰好有 $l$ 个黑色格子。

问是否有满足如上限制的拼图（不需要输出方案）。

**数据范围**：$2\leqslant n\leqslant 100$，$0\leqslant u,r,d,l\leqslant n$，$1\leqslant T\leqslant 10^3$。

### 思路

因为这题**不用给出方案**，只用判断是否能满足条件填图。

那我们就**尽可能满足条件**，那就需要我们动一下脑，就可以发现，**只要判断 $>n-2$ 的行和列的数量储存**下来，然后**逐一判断是否满足情况**。

就用 $a,b,c,e$（使用 $d$ **与文中重复**，所以用 $e$）来储存那些 $> n-2$，如果 $\le n-2$ 为 $0$。

那就**优先判断**输出 `NO` 的：

以样例为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/o54ain48.png)

我们会发现当我们 $u=4$ 和 $d=4$ 但 $l=0$ 时，**不满足**。

那么多举几组例子，我们可以发现：

$(u+d)<(b+e)$

$(r+l)<(a+c)$

$u<(b/2+e/2)$

$d<(b/2+e/2)$

$r<(a/2+c/2)$

$l<(a/2+c/2)$

都是不满足要求的。

那么如果**满足其中一个**，那么就输出 `NO`；否则输出 `YES`。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int u,r,d,l;
int a,b,c,e;
int m;
int main(){
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>n;
		cin>>u>>r>>d>>l;
		a=max(0,u-n+2);
		b=max(0,r-n+2);
		c=max(0,d-n+2);
		e=max(0,l-n+2);
		if((u+d)<(b+e)||(r+l)<(a+c)||u<(b/2+e/2)||d<(b/2+e/2)||r<(a/2+c/2)||l<(a/2+c/2)){
			cout<<"NO"<<endl;
		}else{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：hanshengyuan2024 (赞：0)

#### 题意简述：
在这个游戏中，你需要填充一个大小为 $n \times n$ 的方格矩阵，其中一些方格已经被标记为黑色。每个方格要么是黑色，要么是白色。你的目标是在不违反以下规则的情况下，将剩余的空白方格填充为白色：

1. 每个白色方格都必须与至少一个黑色方格相邻，即每个白色方格的上下左右四个方向至少有一个与黑色方格相邻。

2. 每行和每列上的连续白色方格的数量不得超过给定的数组 $w$ 和 $h$。

为了解决这个题目，你可以使用回溯算法。回溯算法是一种遍历搜索解空间的方法，它尝试所有可能的组合并找到一个满足条件的解。以下是一个可能的实现方式：

1. 定义一个 $n \times n$ 的二维数组 $grid$，用于表示方格矩阵。初始化所有方格为白色，并将黑色方格的位置标记出来。

2. 定义两个长度为 $n$ 的数组 `row` 和 $col$，用于记录每行和每列的白色方格数量。

3. 定义一个递归函数 `solve`，该函数用于尝试填充第 $i$ 行和第 j 列的方格。

4. 在 `solve` 函数中，首先检查当前行和列的白色方格数量是否超过了给定的 $w$ 和 $h$。如果超过了，就返回 `false`。

5. 如果当前方格已经被标记为黑色，那么递归调用 `solve` 函数，填充下一个方格。

6. 如果当前方格是白色，那么尝试填充它并更新 `row` 和 `sol` 数组，然后递归调用 `solve` 函数填充下一个方格。

7. 在 `solve` 函数的递归调用之前，检查当前是否是最后一个方格。如果是最后一个方格，并且已经满足了所有条件，那么返回 `true`，表示找到了一个可行解。

8. 如果 `solve` 函数返回 `false`，表示当前组合不满足条件，那么回溯到上一个方格，尝试其他可能的组合。

9. 最后，在主函数中调用 `solve` 函数开始求解。

#### C++ Code:
```cpp
#include <iostream>
#include <vector>

using namespace std;

bool solve(vector<vector<int>>& grid, vector<int>& row, vector<int>& col, int i, int j, int w, int h) {
    int n = grid.size();

    if (j == n) {
        i++;
        j = 0;
    }

    if (i == n) {
        return true;
    }

    if (row[i] > w || col[j] > h) {
        return false;
    }

    if (grid[i][j] == 1) {
        return solve(grid, row, col, i, j + 1, w, h);
    }

    // 尝试填充当前方格
    grid[i][j] = 1;
    row[i]++;
    col[j]++;

    if (solve(grid, row, col, i, j + 1, w, h)) {
        return true;
    }

    // 回溯
    grid[i][j] = 0;
    row[i]--;
    col[j]--;

    return solve(grid, row, col, i, j + 1, w, h);
}

int main() {
    int n, w, h;
    cin >> n >> w >> h;

    vector<vector<int>> grid(n, vector<int>(n, 0));
    vector<int> row(n, 0);
    vector<int> col(n, 0);

    // 输入黑色方格的位置
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 1) {
                row[i]++;
                col[j]++;
            }
        }
    }

    if (solve(grid, row, col, 0, 0, w, h)) {
        cout << "YES" << endl;

        // 输出填充后的方格矩阵
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
```

这个算法的时间复杂度为 $O(2^n)$，其中 $n$ 是方格矩阵的大小。由于可能存在多个可行解，所以该算法可能会找到其中一个解。如果需要找到所有可能的解，可以稍作修改来进行全排列，并保存所有满足条件的组合。

---

## 作者：GoodLuckCat (赞：0)

为了 ~~不掉灰~~ 保持社贡，来水一篇题解。

先放个题目链接：[CF1494B](https://www.luogu.com.cn/problem/CF1494B)

这道题题目要求在一个 $n\times n$ 的方形网格上填入黑色单元格，使得网格“边缘”上的黑色单元格数量符合要求。问有没有符合要求的方法。

我的思路比较特别，将大家都很关注的四个角落使用 **二进制数** 来表示。因为四个角落都只有 $1$ 或 $0$（涂黑或者不涂黑）两种状态，所以这个二进制数应该位于 $0\sim2^4-1$，也就是 $0\sim15$ 之间。可以用 $i$ 来表示每次尝试的二进制数。

接下来就是将这个二进制数的每一位提取出来，可以直接用 `i&1`，`i&2`，`i&4`，`i&8` 来提取（位运算较快）。如果角上已经涂了，那么就将对应的两个变量减去 $1$。写出来代码是这样的（因为每一次循环都要将变量改变，所以可以用四个临时变量来存储 $U$，$R$，$D$，$L$ 的值）：

```cpp
int u=U,r=R,d=D,l=L;
if(i&1)u--,l--;
if(i&2)u--,r--;
if(i&4)r--,d--;
if(i&8)d--,l--;
```

接下来就可以判断了：如果剩下的四条边的方格数量满足条件（$\ge0$ 并且 $\le n-2$），就有解。所以得出代码如下：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n,U,R,D,L;
        cin>>n>>U>>R>>D>>L;
        string p="NO\n";
        for(int i=0;i<=15;i++)
        {
            int u=U,r=R,d=D,l=L;
            if(i&1)u--,l--;
            if(i&2)u--,r--;
            if(i&4)r--,d--;
            if(i&8)d--,l--;
            if(u>=0&&r>=0&&d>=0&&l>=0&&u<=n-2&&r<=n-2&&d<=n-2&&l<=n-2)
            {
                p="YES\n";
                break;
            }
        }
        cout<<p;
    }
    return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# CF1494B Berland Crossword 题解

## 题目描述

[CF1494B Berland Crossword](https://www.luogu.com.cn/problem/CF1494B)

## 题目解法

### 思路

不难发现，会导致行和列互相干扰的格子只有矩阵角上的四个格子。

共有 $4$ 个格子，有 $2^4=16$ 种情况。

可以暴力枚举所有情况。

每次只需要判断该状态下是否符合题意即可。

在这里使用状态压缩实现。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

struct st{int n, lx[4];};
bool chk(st a, int k)
{
    auto [n, l]=a;
    for(int i=0;i<4;i++, k>>=1)
        if(k&1) l[i]--, l[(i+3)%4]--;
    for(int i=0;i<4;i++)
        if(l[i]<0||l[i]>n-2) return 0;
    return 1;
}

void solve()
{
    int n, u, r, d, l;
    cin>>n>>u>>r>>d>>l;
    st m={n, {u, r, d, l}};
    for(int i=0;i<16;i++)
        if(chk(m, i)) 
            return cout<<"YES\n", void();
    cout<<"NO\n";
}

int main()
{
    int t;
    cin>>t;
    while (t--) solve();
}
```

---

## 作者：JerryLiujiarui (赞：0)

## 题意
有一种拼图游戏，其中每一块拼图都有限制，试求是否有可行的拼图方案。
## 方法
初看这道题，第一想到暴力，但后来想到一种更好的方法：定义一个检验是否有可行方案的函数不就行了吗？
#### 定义函数
定义一个检验的数组:

这道题就是找到所要求内的格子数最值，然后取几个特殊值尝试，每次减 1 ，完成操作后进行两次大小比较，输出结果。
```
    bool check(int n,int u,int r,int d,int l,int i){
	    if(i&1) u--,l--;
	    if(i&2) u--,r--;
	    if(i&4) r--,d--;
	    if(i&8) d--,l--;//特殊值
	    return min(min(u,r),min(d,l))>=0 && max(max(u,r),max(d,l))<=n-2;//最终输出结果
    }

```
#### 实行函数，计算结果
代码主体部分，将函数实行，判断一共 16 种方案是否可行，判断到可行的，输出，结束；一直不可行，就是不行。代码如下：
```
    void solve(){
	 int n,u,r,d,l;
	 cin>>n>>u>>r>>d>>l;
	 for(int i=0;i<16;i++){//也就十六种情况
	     if(check(n,u,r,d,l,i)){
		cout<<"YES"<<endl;//判断可行，输出
		    return;
             }
	 }
	 cout<<"NO"<<endl;//不可行
    }

    int main(){
        ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);//加速代码，可以不看
        int t;
        cin>>t;
        while(t--) solve();//最后计算
	return 0;//打代码好习惯
    }

```




---

## 作者：Cutest_Junior (赞：0)

## 题解 CF1494B 【Berland Crossword】

### 题意

+ $n\times n$ 的方格，都是空白的，要把一些涂成黑色；
+ 最上面一行、最右面一行、最下面一行、最左面一行各要有 $u,r,d,l$ 个黑色格子；
+ 判断是否可行；
+ 多组数据，$2\le n\le100$，$0\le u,r,d,l\le n$。

### 做法

枚举矩形四个角的颜色，状压优化，判断可行性。

---

说人话。

比如左上角是黑色格子，就把 $u$ 和 $l$ 各减 $1$，最后判断 $0\le u,r,d,l\le n-2$ 是否成立。

### 代码

```cpp
#include <cstdio>

using namespace std;

void solve() {
	int n, a[4];
	scanf("%d%d%d%d%d", &n, &a[0], &a[1], &a[2], &a[3]);
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 4; ++j) {
			if ((1 << j) & i) {
				--a[j], --a[(j + 1) % 4];
			}
		}
		for (int j = 0; j < 4; ++j) {
			if (a[j] < 0 || a[j] > n - 2) {
				break;
			}
			if (j == 3) {
				printf("YES\n");
				return;
			}
		}
		for (int j = 0; j < 4; ++j) {
			if ((1 << j) & i) {
				++a[j], ++a[(j + 1) % 4];
			}
		}
	}
	printf("NO\n");
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}
```

---

