# [ABC129D] Lamp

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc129/tasks/abc129_d

縦 $ H $ 行横 $ W $ 列のグリッドが与えられます。このグリッドのうち、いくつかのマスには障害物が存在します。

すぬけ君は、障害物のないマスのうち一つを選び、そのマスに明かりを設置しようとしています。 設置されたマスから、上下左右の四方向にまっすぐに光線が伸びます。それぞれの方向について、最初に障害物が存在するマスにぶつかる、もしくはグリッドの端にぶつかる手前のマスまで照らされます。明かりを設置したマスも照らされますが、障害物が存在するマスは照らされません。

すぬけ君は明かりによって照らされるマスの個数を最大化したいです。

$ H $ 個の長さ $ W $ の文字列 $ S_i $ ($ 1\ <\ =\ i\ <\ =\ H $) が与えられます。$ S_i $ の $ j $ 文字目 ($ 1\ <\ =\ j\ <\ =\ W $) が `#` のとき、グリッドの上から $ i $ 行目で左から $ j $ 列目のマスには障害物があり、 `.` のときは障害物がありません。

照らされるマスの個数の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =\ H\ <\ =\ 2,000 $
- $ 1\ <\ =\ W\ <\ =\ 2,000 $
- $ S_i $ は `#` と `.` のみからなる長さ $ W $ の文字列
- $ S_i $ ($ 1\ <\ =\ i\ <\ =\ H $) のうちいずれかに `.` は最低 $ 1 $ つ存在する

### Sample Explanation 1

すぬけ君が上から $ 2 $ 行目、左から $ 2 $ 列目のマスに明かりを設置すると、上から $ 2 $ 行目のうち左から $ 1 $ 〜 $ 5 $ 列目のマス、 左から $ 2 $ 列目のうち上から $ 1 $ 〜 $ 4 $ 列目のマス全てが照らされ、全部で $ 8 $ マスです。

## 样例 #1

### 输入

```
4 6
#..#..
.....#
....#.
#.#...```

### 输出

```
8```

## 样例 #2

### 输入

```
8 8
..#...#.
....#...
##......
..###..#
...#..#.
##....#.
#...#...
###.#..#```

### 输出

```
13```

# 题解

## 作者：lizhous (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT4742)  
### 分析
一个灯塔会向四个方向照射，所以我们可以知道一个灯塔照射的图形为：
```
  #
  .
#.+.#
  .
  #
```
其中`+`为灯塔。设上方障碍的纵坐标 $y1$，下方为 $y2$；设左方障碍的横坐标 $x1$，右方为 $x2$。则可照射到的方块数是 $(y2-y1-1)+(x2-x1-1)-1$,化简即 $x2-x1+y2-y1-3$。


现在我们思考枚举每个点并求出这个点作为灯塔可照射到的方块数。由于枚举时间复杂度为 $O(n^2)$,$1 \le n \le 2000$,所以期望计算时间复杂度为 $O(1)$,考虑预处理。

关于预处理，我们现在最外围虚拟围一圈障碍物，然后可以处理出对于每个点对应的 $x1,x2,y1,y2$。可以通过 $mox_i$ 记录到当前列第 $i$ 行最晚出现的障碍物的 $x$ 坐标，$moy_i$ 记录到当前行第 $i$ 列最晚出现的障碍物的 $y$ 坐标。正扫一遍可求出 $x1,y1$，倒过来扫就可以求出 $x2,y2$。时间复杂度 $O(n^2)$。

### 模拟样例
为更加直观理解分析，我们模拟样例 $1$ ：
```
4 6
#..#..
.....#
....#.
#.#...
```
求出的 $x1$ 为：
```
111444
000006
000055
113333
```
求出的 $x2$ 为：
```
144477
666666
555557
133777
```
求出的 $y1$ 为：
```
100100
100102
100132
404132
```
求出的 $y2$ 为：
```
154132
454532
454535
454555
```
我们可以发现灯塔在 $(2,2)$ 时照到的方块个数为：$x2_{2,2}-x1_{2,2}+y2_{2,2}-y1_{2,2}-3 =6-0+5-0-3=8$ ,即样例输出的答案。
### code
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n, m, ans, x1[2002][2002], y_1[2002][2002], x2[2002][2002], y2[2002][2002], mox[2002], moy[2002];
char ch[2002][2002];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) { //第一遍求出x1,y1
		for (int z = 1; z <= m; z++) {
			scanf(" %c", &ch[i][z]);
			if (ch[i][z] == '#') {
				mox[i] = z;
				moy[z] = i;
			}
			x1[i][z] = mox[i];
			y_1[i][z] = moy[z];
		}
	}
	for (int i = 0; i < 2002; i++) mox[i] = m + 1; //注意初始化
	for (int i = 0; i < 2002; i++) moy[i] = n + 1;
	for (int i = n; i >= 1; i--) {
		for (int z = m; z >= 1; z--) { //第二遍求x2,y2
			if (ch[i][z] == '#') {
				mox[i] = z;
				moy[z] = i;
			}
			x2[i][z] = mox[i];
			y2[i][z] = moy[z];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int z = 1; z <= m; z++) {
			if (ch[i][z] == '.') {
				ans = max(ans, x2[i][z] - x1[i][z] + y2[i][z] - y_1[i][z] - 3); //更新ans
			}
		}
	}
	cout << ans;
}
```


---

## 作者：_zexal_ (赞：2)

## 分析
注意到 $H,W \leq 2000$，暴力肯定不行，我们需要办法优化，注意到每一次暴力有部分会重复计算，例如计算 $a_{i,j}$ 时转移到 $a_{i,j+1}$ 而 $a_{i,j+1}$ 时也同样转移到了 $a_{i,j}$。所以我们不如使用**悬线法**。
#### 悬线法
悬线法用了一种用已知求未知的思想，例如假设存在一种 $a_{i,j}=a_{i,j-1}$ 的情况，那么如果暴力，我们需要扩张两遍。然而实际上，由于他们相等，所以 $a_{i,j-1}$ 左边能到的区域 $a_{i,j}$ 也同样可以到，同理，$a_{i,j}$ 所能到达的右区域，$a_{i,j-1}$ 同样也可以到。我们把这样的方法就称为**悬线法**。实现代码如下。
```cpp
for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(a[i][j-1]==1&&a[i][j]==1) l[i][j]=l[i][j-1];
		}
		for(int j=m; j>1; j--) if(a[i][j]&&a[i][j+1]) r[i][j]=r[i][j+1];
	}
```
同理，在本题中，我们再用这样的办法求出他的上下悬线就好了，这样我们就获得了他的上下左右，最后直接计算即可。上下部分代码如下。
#### Code
```cpp
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(a[i][j]&&a[i-1][j]) h[i][j]=h[i-1][j];
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			if(a[i][j]&&a[i+1][j]) d[i][j]=d[i+1][j];
```
另外一提悬线法，他还可以用来求最大矩阵这样的问题，例如[此题](https://www.luogu.com.cn/problem/P4147)。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=2005;
int n,m;
char c;
bool a[Maxn][Maxn];
int l[Maxn][Maxn],answer,r[Maxn][Maxn],h[Maxn][Maxn],d[Maxn][Maxn];
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			cin>>c;
			l[i][j]=r[i][j]=j,h[i][j]=i,d[i][j]=i;
			if(c=='#') a[i][j]=0;
			else a[i][j]=1;

		}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(a[i][j-1]==1&&a[i][j]==1) l[i][j]=l[i][j-1];
		}
		for(int j=m; j>1; j--) if(a[i][j]&&a[i][j+1]) r[i][j]=r[i][j+1];
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(a[i][j]&&a[i-1][j]) h[i][j]=h[i-1][j];
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			if(a[i][j]&&a[i+1][j]) d[i][j]=d[i+1][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			answer=max(answer,r[i][j]-l[i][j]+1+d[i][j]-h[i][j]+1);
	cout<<answer-1;
return 0;
}
```


---

## 作者：_byta (赞：2)

首先，大家应该都能想到暴力怎么写，我就不多说了。放一个暴力的代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2002;
const int mod=1e9+7;
int n,m,p,q,ans,sum,tot,k,cnt,a[N][N],b[N][N],f[N],d[N];
char ch[N][N];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>ch[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			sum=0;
			if(ch[i][j]=='.')
			{
				k=i;
				while(ch[k][j]=='.')
				{
					sum++;
					k--;
				}
				k=i+1;
				while(ch[k][j]=='.')
				{
				   sum++;
				   k++;	
				}
				k=j-1;
				while(ch[i][k]=='.')
				{
					sum++;
					k--;
				}
				k=j+1;
				while(ch[i][k]=='.')
				{
					sum++;
					k++;
				}
			}
			ans=max(sum,ans);
		}
	}
	cout<<ans;
	return 0;
}

```


显然，上面这段代码会超时。考虑怎么优化。我们发现，如果同一行或同一列

有连续的两盏灯，根据上面的暴力写法，我们每次都要重新寻找每一盏灯向四

方能扩展的最大长度，但如果我们每搜到一盏灯就记录下他的四方能扩展的长

度，那下一盏灯就可以继承上一盏灯的信息，从而可以大大优化时间。

正确代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2002;
const int mod=1e9+7;
int n,m,p,q,ans,sum,tot,k,cnt,a[N][N],b[N][N],f[N],d[N][N],c[N][N];
char ch[N][N];
int main()
{
	std::ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>ch[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			sum=0;
			if(ch[i][j]=='.')
			{
				k=i;
				while(ch[k][j]=='.')
				{
					if(ch[i-1][j]=='.')
					{
					   sum=c[i-1][j];
					  break;
				    }
					sum++;
					k--;
				}
				k=i+1;
				while(ch[k][j]=='.')
				{
					if(ch[i-1][j]=='.')
					{
					   sum=c[i-1][j];
					  break;
				    }
				   sum++;
				   k++;	
				}
				c[i][j]=sum;
				k=j-1;
				while(ch[i][k]=='.')
				{
					if(ch[i][j-1]=='.')
					{
						sum=c[i][j]+d[i][j-1]-1;
						break;
					}
					sum++;
					k--;
				}
				k=j+1;
				while(ch[i][k]=='.')
				{
					if(ch[i][j-1]=='.')
					{
						sum=c[i][j]+d[i][j-1]-1;
						break;
					}
					sum++;
					k++;
				}
				d[i][j]=sum-c[i][j]+1;
			}
			ans=max(sum,ans);
		}
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：scp020 (赞：1)

### 题目大意

给出一张 $h$ 行 $w$ 列只由 `.` 和 `#` 组成的图，其中 `.` 代表空地，可以放东西，`#` 代表障碍物，不可放东西。

我们可以在任意一个 `.` 上放灯，灯可以照亮上下左右四个方向，即水平和竖直两条线，且当光碰到障碍物时停止传播。

求光可以照亮几个空地。

### 思路

因为光只能向 $4$ 个方向传播，所以我们进行预处理每一个位置向 $4$ 个方向能照亮几个空地。

定义 $4$ 个数组 $f1$、$f2$、$f3$、$f4$ 分别表示该位置向左、右、上、下 $4$ 个方向可以照亮几个空地。

方法类似于最长公共子串，下面给出状态转移方程：

$f1_{i,j}=\begin{cases}0 & a_{i,j}= \# \\f1_{i,j-1}+1 & a_{i,j}= . \end{cases}$

$f2_{i,j}=\begin{cases}0 & a_{i,j}= \# \\f2_{i-1,j}+1 & a_{i,j}= . \end{cases}$

$f3_{i,j}=\begin{cases}0 & a_{i,j}= \# \\f3_{i,j+1}+1 & a_{i,j}= . \end{cases}$

$f4_{i,j}=\begin{cases}0 & a_{i,j}= \# \\f4_{i+1,j}+1 & a_{i,j}= . \end{cases}$

最后进行计算答案，对于每个位置 $i,j$，可以照亮的空地数为 $f1_{i,j}+f2_{i,j}+f3_{i,j}+f4_{i,j}-3$，因为在左、右、上、下 $4$ 个方向上 $i,j$ 这个空地被算了 $4$ 次，实际上应该只算 $1$ 次，所以要减 $3$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,f1[2010][2010],f2[2010][2010],f3[2010][2010],f4[2010][2010],ans;
char a[2010][2010];
int main()
{
	ios::sync_with_stdio(false);
	cin>>h>>w;
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) cin>>a[i][j];//我这里写getchar挂掉了。 
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			f1[i][j]=(a[i][j]=='.'?f1[i][j-1]+1:0),f3[i][j]=(a[i][j]=='.'?f3[i-1][j]+1:0);
	for(int i=h;i;i--)
		for(int j=w;j;j--)
			f2[i][j]=(a[i][j]=='.'?f2[i][j+1]+1:0),f4[i][j]=(a[i][j]=='.'?f4[i+1][j]+1:0);
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			ans=max(ans,f1[i][j]+f2[i][j]+f3[i][j]+f4[i][j]-3);
	cout<<ans;
	return 0;
}
```


---

## 作者：dingshengyang (赞：0)

+ BF（朴素解法）

枚举每一个空地，看看上下左右最多能照到哪里。如果纵向照亮 $x$ 格，横向照亮 $y$ 格，则答案为 $\max\{x+y-1\}$。该算法时间复杂度最坏为 $O(nm(n+m))$（即全部是空地）。

+ 正解

首先，建立两个 `vector<int>[]`，取名为 $table$ 和 $table2$。

$table_i$ 表示第 $i$ 行所有的障碍物在第几列。

$table2_j$ 表示第 $j$ 列所有的障碍物在第几行。

然后对于每个空格点 $i,j$，二分找 $table$ 中 $i$ 的前驱后继和 $table2$ 中的 $j$ 的前驱后继。最后别忘记每个 $table$ 和 $table2$ 添加两个哨兵节点。（如果是 $table$，是 $0$ 和 $m+1$，如果是 $table2$，是 $0$ 和 $n+1$）。

注意：实际上在 $table$ 和 $tbale2$ 中找到的前驱后继都是开区间。因为障碍物上是不能放灯的。然后前驱加一，后继减一。众所周知，闭区间 $[l,r]$ 的长度就是 $r-l+1$。然后把两个闭区间的长度加起来，再减一（放灯的位置算了两遍）。


来一个有趣的话题。首先，前面说过，全是空地能卡 BF 算法，而二分法却达到了「最高境界」$O(nm)$。（因为只有哨兵节点）；而如果全是障碍物，BF 达到了「最高境界」$O(nm)$（根本放不了灯），二分却被卡成 $O(2nm(\log m+\log n))$，当然还是可以过的，因为时限有 $2$ 秒，根本不卡常（AT 良心）。

然后看代码。代码里有注释，如果觉得上述解释太过于抽象，可以看注释。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2050;
char maps[N][N];
int n,m,ans;
vector<int> table[N],table2[N];//上述 table 和 table2
int main() {
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++)table[i].push_back(0);//哨兵（极小值）
	for(int j = 1;j <= m;j ++)table2[j].push_back(0);//哨兵（极小值）
	for(int i = 1; i <= n; i ++) {
		scanf("%s",maps[i]+1);
		for(int j = 1; j <= m; j ++) {
			if(maps[i][j] == '#'){
//				printf("%d ",j);
				table[i].push_back(j);//预处理
				table2[j].push_back(i);
			}
		}
//		puts("");//这些都是调试行，别管
	}
	for(int i = 1;i <= n;i ++)table[i].push_back(m+1);//哨兵（极大值）
	for(int j = 1;j <= m;j ++)table2[j].push_back(n+1);//哨兵（极大值）
//	puts("!!!???");
//	for(int i = 1;i <= m;i ++){
//		for(auto j:table2[i]){
//			printf("%d ",j);
//		}
//		printf("\n");
//	}//这些都是调试行，别管
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			if(maps[i][j] == '.') {
				int last,next,temp1,temp2;//非常清晰
           /*
           last：这一行（列）的最近的上一个障碍物。
           next：这一行（列）的最近的下一个障碍物。
           这些都是可以废物利用的，见下。
           temp1：一行可以照到几个格子（包括自己）。
           temp1：一列可以照到几个格子（包括自己）。
           */
				int l = 0,r = table[i].size()-1;//有哨兵还不用担心越界
				while(l < r) {//二分找前驱
					int mid = l+r+1 >> 1;
					if(table[i][mid] < j) {
						l = mid;
					} else {
						r = mid - 1;
					}
				}
				last = table[i][l]+1;//开区间转闭区间（1）
				l = 0,r = table[i].size()-1;//二分找后继
				while(l < r) {
					int mid = l+r>>1;
					if(table[i][mid] > j){
						r = mid;
					}else{
						l = mid + 1;
					}
				}
				next = table[i][l]-1;//开区间转闭区间（2）
				//if(i == 2 && j == 2)printf("last=%d,next=%d\n",last,next);
				temp1 = next-last+1;
				l = 0,r = table2[j].size()-1;//二分找前驱
				while(l < r) {
					int mid = l+r+1 >> 1;
					if(table2[j][mid] < i) {
						l = mid;
					} else {
						r = mid - 1;
					}
				}
				last = table2[j][l]+1;//开区间转闭区间（1）（废物利用）
				l = 0,r = table2[j].size()-1;
				while(l < r) {//二分找后继
					int mid = l+r>>1;
					if(table2[j][mid] > i){
						r = mid;
					}else{
						l = mid + 1;
					}
				}
				next = table2[j][l]-1;//开区间转闭区间（2）（废物利用）
				//if(i == 2 && j == 2)printf("last=%d,next=%d\n",last,next);
				temp2 = next-last+1;
				ans = max(ans,temp1+temp2-1);//更新答案
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

够详细了吧……

---

## 作者：HMP_Haoge (赞：0)

板子题。

要向四个方向拓展，显然不能每次都暴力计算四边的个数，数据范围也不允许。于是我们就需要预处理出每个点向四个方向拓展的最大个数，然后再枚举每个点求出最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define MAXN 2010

int n,m;
int up[MAXN][MAXN],down[MAXN][MAXN],L[MAXN][MAXN],R[MAXN][MAXN],a[MAXN][MAXN],maxx;
char s[MAXN];
//一车子二维数组 

int main()
{
	scanf("%d%d",&n,&m);
	for(ri i=1;i<=n;++i)
	{
		scanf("%s",s+1);
		for(ri j=1;j<=m;++j)
		{
			if(s[j]=='#') a[i][j]=1;
		}
	}
	
	//left
	for(ri i=1;i<=n;++i)
	{
		for(ri j=1;j<=m;++j)
		{
			if(a[i][j]) L[i][j]=0;
			else L[i][j]=L[i][j-1]+1;
		}
	}
	
	//right
	for(ri i=1;i<=n;++i)
	{
		for(ri j=m;j>=1;--j)
		{
			if(a[i][j]) R[i][j]=0;
			else R[i][j]=R[i][j+1]+1;
		}
	}
	
	//up
	for(ri i=1;i<=n;++i)
	{
		for(ri j=1;j<=m;++j)
		{
			if(a[i][j]) up[i][j]=0;
			else up[i][j]=up[i-1][j]+1;
		}
	}
	
	//down
	for(ri i=n;i>=1;--i)
	{
		for(ri j=1;j<=m;++j)
		{
			if(a[i][j]) down[i][j]=0;
			else down[i][j]=down[i+1][j]+1;
		}
	}
	for(ri i=1;i<=n;++i)
	{
		for(ri j=1;j<=m;++j)
		{
			a[i][j]=0;//a数组废物利用
			a[i][j]=up[i][j]+down[i][j]+L[i][j]+R[i][j]-3;
			//注意这里由于放灯的位置重复计算了4次，所以需要减去其中的3次 
			maxx=max(maxx,a[i][j]);
		}
	}
	printf("%d",maxx);
	return 0; 
}
```


---

## 作者：TLEWA (赞：0)

这道题目需要用到前缀和的思想。

显然， $O(n^3)$ 的暴力会超时，于是我们预处理一下每个方块上下左右最多能延申多少个，预处理可以做到 $O(n^2)$。

然后对于每个点，我们直接查预处理出来的表，取最小值，这部分也是 $O(n^2)$ 的，于是总时间复杂度为 $O(n^2)$，不会超时。

AC 代码：
```cpp
#include<iostream>
using namespace std;

int n,m,q1[2005][2005],q2[2005][2005],q3[2005][2005],q4[2005][2005],maxn;
bool arr[2005][2005];
char c;

int main() {
	cin >> n >> m;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			cin >> c;
			arr[i][j]=(c=='.');
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			q1[i][j]=arr[i][j]*(q1[i][j-1]+1);
			q3[i][j]=arr[i][j]*(q3[i-1][j]+1);
		}
	}
	for(int i=n;i;--i) {
		for(int j=m;j;--j) {
			q2[i][j]=arr[i][j]*(q2[i][j+1]+1);
			q4[i][j]=arr[i][j]*(q4[i+1][j]+1);
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(arr[i][j])
				maxn=max(maxn,q1[i][j]+q2[i][j]+q3[i][j]+q4[i][j]-3);
//			cout << q1[i][j] << ' ' << q2[i][j] << ' ' << q3[i][j] << ' ' << q4[i][j] << endl;
		}
//		cout << endl;
	}
	
	cout << maxn << endl;
	return 0;
}
```


---

