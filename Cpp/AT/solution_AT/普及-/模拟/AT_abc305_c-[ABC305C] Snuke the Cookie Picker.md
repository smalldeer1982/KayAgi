# [ABC305C] Snuke the Cookie Picker

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc305/tasks/abc305_c

縦 $ H $ マス, 横 $ W $ マスのグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と呼びます。  
 はじめ、グリッド上には、ある **縦横 $ 2 $ マス以上** の部分長方形の内部にあるマスにクッキーが 1 枚ずつ置かれていて、それ以外のマスにはクッキーが置かれていません。  
 形式的に説明すると、以下の条件を全て満たす 4 つの整数の組 $ (a,b,c,d) $ がただ 1 つ存在します。

- $ 1\ \leq\ a\ \lt\ b\ \leq\ H $
- $ 1\ \leq\ c\ \lt\ d\ \leq\ W $
- グリッド上のマスのうち、$ a\ \leq\ i\ \leq\ b,\ c\ \leq\ j\ \leq\ d $ を満たす全てのマス $ (i,\ j) $ にはクッキーが 1 枚ずつ置かれていて、それ以外のマスにはクッキーが置かれていない。
 
ところが、すぬけ君がグリッド上のクッキーのどれか 1 枚を取って食べてしまいました。  
 すぬけ君がクッキーを取ったマスは、クッキーが置かれていない状態に変わります。

すぬけ君がクッキーを食べた後のグリッドの状態が入力として与えられます。  
 マス $ (i,\ j) $ の状態は文字 $ S_{i,j} $ として与えられて、`#` はクッキーが置かれているマスを, `.` はクッキーが置かれていないマスを意味します。  
 すぬけ君が食べたクッキーが元々置かれていたマスを答えてください。(答えは一意に定まります。)

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 500 $
- $ S_{i,j} $ は `#` または `.`
 
### Sample Explanation 1

はじめ、クッキーは $ (2,\ 3) $ を左上、$ (4,\ 5) $ を右下とする部分長方形の内部にあるマスに置かれていて、すぬけ君は $ (2,\ 4) $ にあるクッキーを食べたことがわかります。よって $ (2,\ 4) $ を出力します。

### Sample Explanation 2

はじめ、クッキーは $ (1,\ 1) $ を左上、$ (3,\ 2) $ を右下とする部分長方形の内部にあるマスに置かれていて、すぬけ君は $ (1,\ 2) $ にあるクッキーを食べたことがわかります。

## 样例 #1

### 输入

```
5 6
......
..#.#.
..###.
..###.
......```

### 输出

```
2 4```

## 样例 #2

### 输入

```
3 2
#.
##
##```

### 输出

```
1 2```

## 样例 #3

### 输入

```
6 6
..####
..##.#
..####
..####
..####
......```

### 输出

```
2 5```

# 题解

## 作者：_Ad_Astra_ (赞：2)

首先由于 $a \lt b$ 且 $c \lt d$，则有饼干的长宽至少为 $2$，那么上下左右边界上最后各至少有一块饼干。那么我们只要取最上、最左、最下、最右四块的位置，就可以得出原来饼干的范围。接下来只要枚举范围内的每个点并判断即可。

时间复杂度 $O(nm)$。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a=500,b,c=500,d;
char mp[510][510];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>mp[i][j];
			if(mp[i][j]=='#')a=min(a,i),b=max(b,i),c=min(c,j),d=max(d,j);
		}
	for(int i=a;i<=b;i++)
		for(int j=c;j<=d;j++)
			if(mp[i][j]=='.')
				cout<<i<<" "<<j;
	return 0;
}
```

---

## 作者：whx2009 (赞：1)

## 本题思路：
这道题其实十分简单，可以直接标记一个有蛋糕的位置的前后左右的位置，如果有一个本来没有蛋糕的格子，但却被超过 $1$ 个格子标记，那么就是这个格子中的蛋糕被吃了。

原因是题目中说了原有一个长方形的格子中都是蛋糕，只要把每一个周围标记一下，就一定能找到被吃的一个的位置。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[501][501];
int b[501][501];
int main()
{
	int h,w;
	cin>>h>>w;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
		  cin>>a[i][j];
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			if(a[i][j]=='#')
			{
				b[i+1][j]++;
				b[i-1][j]++;
				b[i][j+1]++;
				b[i][j-1]++;
			}
		}
	}
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			if(a[i][j]=='.' && b[i][j]>=2)
			{
				cout<<i<<" "<<j;
				return 0;
			}
		}
	}
	return 0;
}

```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc305_c)
# 思路

因为两块联通块就可以看成一块饼干，所以直接判断一个点号四周的井号个数是否有两个及以上，如果有就正确，否则不对。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char mp[505][505];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];//输入 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((mp[i+1][j]=='#')+(mp[i-1][j]=='#')+(mp[i][j-1]=='#')+(mp[i][j+1]=='#')>=2 && mp[i][j]=='.'){//如果 '#' 个数大于等于2，就正确 
				return cout<<i<<" "<<j<<endl,0;
			}
		}
	}
	return 0;//听懂掌声 
}
```


---

## 作者：ljlawa (赞：1)

很明显，因为长宽都大于 $2$，所以我们一定可以根据输入得到一个矩形。

我们只需要在输入的时候记录矩形的四条边的方位，然后在这个矩形里面找到那个点。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n, m;
char a[N][N];
int hl, hr, sl, sr;

int main()
{
	cin >> n >> m;
	hl = n; sl = n;
	for (int i = 1; i <= n; i ++)
	{
		for (int j = 1; j <= m; j ++)
		{
			cin >> a[i][j];
			if (a[i][j] == '#') hl = min (hl, i), sl = min (sl, j), hr = max (hr, i), sr = max (sr, j);
		}
	}
	int x = hl, y = sl;
	for (int i = hl; i <= hr; i ++)
	{
		for (int j = sl; j <= sr; j ++)
		{
			if (a[i][j] != '#')
			{
				cout <<i << " " << j;
				return 0;
			}
		}
	}
	
    return 0;
}

```


---

## 作者：Coffee_zzz (赞：1)

### 思路

貌似是一种新颖的做法。

我们知道，如果某一行或某一列全没有饼干，那么这一行或列一定不和饼干组成的矩形相交。

那么我们就可以从左往右、从右往左、从上往下、从下往上各扫一次，确定出这个饼干形成的矩形。

最终，我们只需要遍历这个矩形中的每一个元素，寻找唯一的空格子即可。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;
char c[505][505];
int h,w,a,b,e,d;
signed main(){
	cin>>h>>w;
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) cin>>c[i][j];
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) if(c[i][j]=='#') {a=i;break;}
	for(int i=h;i>=1;i--) for(int j=1;j<=w;j++) if(c[i][j]=='#') {b=i;break;}
	for(int j=1;j<=w;j++) for(int i=1;i<=h;i++) if(c[i][j]=='#') {e=j;break;}
	for(int j=w;j>=1;j--) for(int i=1;i<=h;i++) if(c[i][j]=='#') {d=j;break;}
	for(int i=a;i>=b;i--) for(int j=e;j>=d;j--) if(c[i][j]=='.') {cout<<i<<' '<<j;break;}
	return 0;
}
```

---

## 作者：mark0575 (赞：0)

## 思路：

可能相对来说有点复杂。我们把 `#` 看成 $1$，把 `.` 看成 $0$。通过题目中的样例我们可以发现，这个矩形的左上顶点一定是第一个满足这个条件的点：

$a_{i,j}+a_{i+1,j}+a_{i,j+1}\geq2$

同理，这个矩形的右下顶点一定是从后面起第一个满足这个条件的点：

$a_{i,j}+a_{i-1,j}+a_{i,j-1}\geq2$

那么，我们可以跑两遍循环。第一遍正着遍历，求出左上顶点。第二遍反着遍历，求出右下顶点。接下来，我们在这个区间内寻找为 $0$ 的点就好了。

## AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010][1010];
int n,m;
int x1,x2,y11,y2;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			char c;
			cin>>c;
			if(c=='.')
			{
				a[i][j]=0;
			}
			else
			{
				a[i][j]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)//求出左上顶点
	{
		for(int j=1;j<=m;j++)
		{
			if(!x1&&a[i][j]+a[i+1][j]+a[i][j+1]>=2)
			{
				x1=i;
				y11=j;
				break;
			}
		}
	}
	for(int i=n;i>=1;i--)//求出右下顶点
	{
		for(int j=m;j>=1;j--)
		{
			if(!x2&&a[i][j]+a[i-1][j]+a[i][j-1]>=2)
			{
				x2=i;
				y2=j;
				break;
			}
		}
	}
	for(int i=x1;i<=x2;i++)//寻找被吃掉的饼干
	{
		for(int j=y11;j<=y2;j++)
		{
			if(!a[i][j])
			{
				cout<<i<<" "<<j;
				return 0;
			}
		}
	}
	return 0;
}

```


---

## 作者：MOwansui (赞：0)

题目大意：

给你一个高 $h$ 宽 $w$ 的矩阵，共有 $4$ 个未给定的 $a,b,c,d$，他们满足以下三个条件：

- $1≤a<b≤h$。
- $1≤c<d≤w$。
- 从 $S_{a,c}$ 到 $S_{b,d} $的每一个点上都有饼干 `#`，而其他的点上则为 `.`。

已知高桥在这个范围内吃掉了一块饼干，问你该饼干的横纵坐标是多少。

思路:

要符合题目要求，她吃的饼干一定长宽 $\ge 2$，所以我们去上下左右这四个点取范围，然后枚举每一个点判断就行了。

代码：
```
#include<bits/stdc++.h>
using namespace std;
char graph[1111][1111]; 
int main()
{
    long long eight, iight;
    cin >> eight>> iight;
    for(int a = 0; a < eight; a++)
        for(int b = 0; b <iight; b++)
            cin >> graph[a][b];
 
    for(long long a = 0; a <eight; a++)
    {
        for(long long b = 0; b <iight; b++)
        {
            if(graph[a][b] == '#') continue;
            long long fff = 0;
            if(graph[a - 1][b] == '#') fff++;
            if(graph[a][b - 1] == '#') fff++;
            if(graph[a + 1][b] == '#') fff++;
            if(graph[a][b + 1] == '#') fff++;
            if(fff >= 2) 
            {
                cout << a + 1 << ' ' << b + 1;
                return 0;
            }
       }
    }
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**题意**

在 $h\times w$ 大小的地图中，有一个长方形，其中只有一个格子为 `.`，其余为 `#`，长方形外的格子都是 `.`，问那个长方形内为 `.` 的格子坐标是多少。

**分析**

大水题。

暴搜整个地图，找到长方形开始点坐标与结束点坐标，在其中暴搜那个 “`.`” 即可。

找起点与找终点时，按顺序找，先找起点，找到第一个“`#`”，但是这个不一定是起点，因为那个要找的点可能在左上角，于是我们需要继续搜索，往下寻找，令起始点坐标为后面出现的“`#`”的横坐标或纵坐标与第一个“`#`”的横坐标或纵坐标的最小值，这样就一定能找到开始点。同理找到终点。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[501];
int main()
{
	int h,w,sx=501,sy=501,ex=-1,ey=-1;
	cin>>h>>w;
	for(int i=1;i<=h;i++) cin>>s[i];
	for(int i=1;i<=h;i++)
	{
		for(int j=0;j<w;j++)
		if(s[i][j]=='#')//找起始点
		{
			sx=min(sx,j+1);//为避免要找的格子在角落，使用min
			sy=min(sy,i);//同上
		}
	}
	for(int i=h;i>0;i--)
	{
		for(int j=w-1;j>=0;j--)
		if(s[i][j]=='#')//找终点
		{
			ex=max(ex,j+1);//为避免要找的格子在角落，使用max
			ey=max(ey,i);//同上
		}
	}
	for(int i=sy;i<=ey;i++)//暴搜
	for(int j=sx-1;j<=ex-1;j++)
	if(s[i][j]=='.')
	{
		cout<<i<<' '<<j+1;//+1是因为字符串是从0开始的
		return 0;
	}
	return 0;
}

---

## 作者：tbdsh (赞：0)

# 题意简述
[题目传送门](/problem/at_abc305_c)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-abc305-c)

一个 $H(2\le H\le 500)$ 行 $W(2\le W\le 500)$ 列的矩阵。$(i, j)$ 表示第 $i$ 行第 $j$ 列的格子。

一开始，在矩阵内的某个矩形内的每个格子上都有一个饼干，没有饼干在其他格子上。然而 Snuke 取走了一个饼干，这个饼干对应的格子变空了。给出拿走饼干后的矩阵，请你求出 Snuke 拿走的饼干的格子位置。

`#` 表示有饼干，`.` 表示空。 

# 分析
不难发现，他吃掉的饼干的位置的四周至少有两个饼干。

所以，本题我们可以直接暴力枚举每个点，判断这个点的上下左右是否有至少两个饼干。如果是，那么直接输出位置，并结束程序。

时间复杂度：$O(H\times N)$。

空间复杂度：$O(H\times N)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int n, m, fx[2][4] = {{1, -1, 0, 0}, {0, 0, 1, -1}};
string s[505];
int main(){
  cin >> n >> m;
  for (int i = 1; i <= n; i++){
    cin >> s[i];
    s[i] = ' ' + s[i] + ' ';
  }
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      if (s[i][j] == '.'){
        int sum = 0;
        for (int k = 0; k < 4; k++){
          sum += s[i + fx[0][k]][j + fx[1][k]] == '#';
        }
        if (sum >= 2){
          cout << i << ' ' << j;
          return 0;
        }
      }
    }
  }
  return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路
我们可以很容易发现一个神奇小结论，就是缺的那一个地方相邻的 `#` 个数一定是大于等于 $2$ 的。

类似样例二相邻的有两个就是在矩形的四个角上。

相邻的有三个就是在矩形的边上。

相邻的有四个就是在矩形里面。

然后就很容易打出来代码了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 10000;
char mp[maxn][maxn];
int X[] = {0, 0, 1, -1};
int Y[] = {1, -1, 0, 0};
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> (mp[i] + 1);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mp[i][j] == '.'){
				int cnt = 0;
				for (int k = 0; k < 4; k++) {
					int nx = i + X[k];
					int ny = j + Y[k];
					if (mp[nx][ny] == '#') {
						cnt ++;
					}
				}
				if (cnt >= 2) {
					cout << i << " "<< j << "\n";
					return 0;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：CheZiHe929 (赞：0)

# AT_abc305_c 题解
## 原题链接
[**Atcoder**](https://atcoder.jp/contests/abc305/tasks/abc305_c)

[**洛谷**](luogu.com.cn/problem/AT_abc305_c)

## 题目大意
给你一个高 $h$ 宽 $w$ 的矩阵，共有 $4$ 个未给定的数 $a,b,c,d$，他们满足以下三个条件：

- $ 1 \leq a < b \leq h $。
- $ 1 \leq c < d \leq w $。
- 从 $S_{a,c}$ 到 $S_{b,d}$ 的每一个点上都有饼干 `#`，而其他的点上则为 `.`。

已知高桥在这个范围内吃掉了一块饼干，问你该饼干的横纵坐标是多少。

## 思路分析
因为是寻找原来应该是饼干 `#` 但却变成了 `.` 的位置，所以我们不难发现，如果它是符合题意的点的话，那么它的上下左右至少有 $2$ 个 `#`，换句话说，如果一个点原来就是 `.` 的话，那么它的上下左右至多有 $1$ 个 `#`，所以我们只要枚举判断找出上下左右有 $\geq 2$ 个 `#` 的 `.` 即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[505][505];
int h,w; 
signed main(){
	cin>>h>>w;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>s[i][j];//输入矩阵 
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++){//挨个点枚举 
			int cnt=0;//计数上下左右共有几个# 
			if(s[i][j]=='.'){//首先要满足是. 
				if(s[i+1][j]=='#')//下 
					cnt++;
				if(s[i-1][j]=='#')//上 
					cnt++;
				if(s[i][j+1]=='#')//右 
					cnt++;
				if(s[i][j-1]=='#')//左 
					cnt++;
				if(cnt>=2){//符合题意 
					cout<<i<<' '<<j<<endl;
					return 0;//直接结束程序 
				}
			}
		}
}

```

## AC 记录
[**Atcoder**](https://atcoder.jp/contests/abc305/submissions/42202174)

[**洛谷**](luogu.com.cn/record/112616628)

**THE END.**

**THANK YOU.**

---

