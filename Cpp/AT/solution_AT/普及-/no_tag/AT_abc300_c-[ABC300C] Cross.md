# [ABC300C] Cross

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc300/tasks/abc300_c

縦 $ H $ マス横 $ W $ マスのグリッドがあります。グリッドの上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と呼びます。  
 グリッドの各マスには `#` と `.` のいずれかの文字が書かれています。$ (i,\ j) $ に書かれている文字を $ C[i][j] $ とします。また、整数 $ i,\ j $ が $ 1\ \leq\ i\ \leq\ H $ と $ 1\ \leq\ j\ \leq\ W $ の少なくとも一方を満たさない場合、 $ C[i][j] $ を `.` と定義します。

正整数 $ a,\ b,\ n $ が以下の条件を全て満たす時、$ (a,b) $ および $ (a+d,b+d),(a+d,b-d),(a-d,b+d),(a-d,b-d) $ $ (1\ \leq\ d\ \leq\ n) $ の $ 4n\ +\ 1 $ マスを **$ (a,b) $ を中心とするサイズ $ n $ のバツ印** と呼びます。

- $ C[a][b] $ は `#` である。
- $ 1\ \leq\ d\ \leq\ n $ を満たす整数 $ d $ について、 $ C[a+d][b+d],C[a+d][b-d],C[a-d][b+d],C[a-d][b-d] $ はいずれも `#` である。
- $ C[a+n+1][b+n+1],C[a+n+1][b-n-1],C[a-n-1][b+n+1],C[a-n-1][b-n-1] $ のうち少なくとも 1 つは `.` である。
 
例えば次の図で示された例では、$ (2,\ 2) $ を中心とするサイズ $ 1 $ のバツ印と $ (3,\ 7) $ を中心とするサイズ $ 2 $ のバツ印がグリッド上にあります。

![image](https://img.atcoder.jp/ghi/abc300c_aa5161e20f55652dc61ad221348765bb002e4eed378c352bc0e44c7555148ebc.jpg)

グリッドにはいくつかのバツ印があります。バツ印を構成するマス以外に `#` は書かれていません。  
 また、異なるバツ印を構成するマス同士は頂点を共有しません。以下の 2 つのグリッドは異なるバツ印を構成するマス同士が頂点を共有している例で、**このようなグリッドの状態は入力として与えられません。** 例えば左のグリッドでは $ (3,\ 3) $ と $ (4,\ 4) $ が頂点を共有しているのが条件に反しています。

![image2](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc300_c/af4437e0a6d74885bdf21777218fa90fa4795735.png)

$ N\ =\ \min(H,\ W) $ とします。また、サイズ $ n $ のバツ印の個数を $ S_n $ とします。$ S_1,\ S_2,\ \dots,\ S_N $ を計算してください。

## 说明/提示

### 制約

- $ 3\ \leq\ H,\ W\ \leq\ 100 $
- $ C[i][j] $ は `#` または `.`
- 異なるバツ印を構成するマス同士は頂点を共有しない
- $ H,\ W $ は整数
 
### Sample Explanation 1

問題文に書かれた説明の通り、$ (2,\ 2) $ を中心とするサイズ $ 1 $ のバツ印と $ (3,\ 7) $ を中心とするサイズ $ 2 $ のバツ印が書かれています。

### Sample Explanation 2

バツ印が 1 個も書かれていない場合もあります。

## 样例 #1

### 输入

```
5 9
#.#.#...#
.#...#.#.
#.#...#..
.....#.#.
....#...#```

### 输出

```
1 1 0 0 0```

## 样例 #2

### 输入

```
3 3
...
...
...```

### 输出

```
0 0 0```

## 样例 #3

### 输入

```
3 16
#.#.....#.#..#.#
.#.......#....#.
#.#.....#.#..#.#```

### 输出

```
3 0 0```

## 样例 #4

### 输入

```
15 20
#.#..#.............#
.#....#....#.#....#.
#.#....#....#....#..
........#..#.#..#...
#.....#..#.....#....
.#...#....#...#..#.#
..#.#......#.#....#.
...#........#....#.#
..#.#......#.#......
.#...#....#...#.....
#.....#..#.....#....
........#.......#...
#.#....#....#.#..#..
.#....#......#....#.
#.#..#......#.#....#```

### 输出

```
5 0 1 0 0 0 1 0 0 0 0 0 0 0 0```

# 题解

## 作者：CuteChat (赞：7)


# 原题大意

[原题链接](https://www.luogu.com.cn/problem/AT_abc300_c)

请统计，在题目给出的 $h$ 行 $w$ 列矩阵中，有多少大小分别为 $1, 2, 3... \min(h, w)$ 由 `#` 组成的“十字架”？

注意，一个“十字架”的大小指中心到任意最外点的长度，例如下图就是两个分别以 $(2, 2)$ 为中心的 $1$ 大小“十字架”，$(3, 7)$ 为中心的 $2$ 大小“十字架”。

![](https://img.atcoder.jp/ghi/abc300c_aa5161e20f55652dc61ad221348765bb002e4eed378c352bc0e44c7555148ebc.jpg)

# 题目分析

模拟，枚举。

枚举每一个 $x, y$，再判断，以 $x, y$ 为中心，最大的“十字架”是多大，并且统计答案。

# 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int h, w;
char s[102][102];
int ans[101];
const int dir[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
#define check(x, y) (x >= 1 && x <= h && y >= 1 && y <= w)

int cross(int i, int j) { // 以 i, j 为中心，最大的“十字架”是多大
	if (s[i][j] == '.') return 0; // 不可能，绝对不可能
	int res = 0;
	for (int d = 1; ; ++d) {
		bool ok = 1;
		for (int k = 0; k < 4 && ok; ++k) {
			int nx = i + d * dir[k][0], ny = j + d * dir[k][1];
			if (check(nx, ny) && s[nx][ny] == '#');
			else ok = 0;
		}
		if (ok) res = d;
		else break;
	}
	return res;
}

int main() {
	scanf("%d%d", &h, &w);
	getchar();
	for (int i = 1; i <= h; ++i) {
		scanf("%s", s[i] + 1);
	}
	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			int tmp = cross(i, j);
			ans[tmp]++;
		}
	}
	for (int i = 1; i <= min(h, w); ++i) { // 一定要注意 min(h, w)
		printf("%d " ,ans[i]);
	}
	return 0;
}
```

# 总结

比较繁琐的模拟、枚举题，在代码中，一定一定要注意很多的细节，如 $x, y$ 这个位置不能是 `.`，最后输出答案最大是 `min(h, w)`。

---

## 作者：CheZiHe929 (赞：2)

# AT_abc300_c



## 原题闪现

[**Atcoder**](https://atcoder.jp/contests/abc300/tasks/abc300_c)
[**洛谷**](https://www.luogu.com.cn/problem/AT_abc300_c)

## 题目大意
其实挺好理解的，就是在矩阵中有一些十字架，他的大小是从中心交叉点向外延伸的```#```的数量（四个方向都要有），问每种大小的十字架分别有多少个。

## 思路

输入矩阵之后，就可以挨个点进行枚举判断，如果该点是```#```那么就对他的左上，左下，右上，右下进行判断，取其最小值为改十字架的大小。最后将其的大小所在的答案数组的答案加 $1$。

## 代码 
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];//定义答案数组记录每种大小十字架的个数
char c[105][105];//定义字符数组
signed main(){
	int h,w;//定义矩阵的长和宽
	cin>>h>>w;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>c[i][j];//输入该矩阵
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			if(c[i][j]=='#'){//如果他是#（即有可能为一个十字架的中心交叉点）
				int d,m=0;//d为该十字架的大小,m为每次四个方向向外延伸的数量
            	int x=i,y=j;//这里需要有一个x和一个y，这样才能保证i，j不被影响
            	while(c[x][y]=='#')//只要还能向外延伸
					x--,y--,m++;//对左下判断
	            d=m;//更新十字架大小
				m=0;//将延伸数量清零
				x=i,y=j;//维护x，y的值
				while(c[x][y]=='#')
					x--,y++,m++;//左上
				d=min(d,m);//因为四边都必须要有#，所以取最小值
				m=0;
				x=i,y=j;
				while(c[x][y] == '#')
					x++,y++,m++;//右上
				d=min(d,m);
				m=0,x=i,y=j;
				while(c[x][y] == '#')
					x++,y--,m++;//右下
				d=min(d,m);
				a[d]++;//大小为d的矩阵的数量+1
		    }
	for(int i=2;i<=min(h,w)+1;i++)//这里注意i从2开始枚举，因为之前在a数组中存的每个十字架的大小是包括中心交叉点的，所以我们这里要排除中心交叉点
		cout<<a[i]<<' ';//输出答案 
	return 0;
}

```

## 无注释版
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
char c[105][105];
signed main(){
	int h,w;
	cin>>h>>w;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>c[i][j];
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			if(c[i][j]=='#'){
				int d,m=0;
            	int x=i,y=j;
            	while(c[x][y]=='#')
					x--,y--,m++;
	            d=m;
				m=0;
				x=i,y=j;
				while(c[x][y]=='#')
					x--,y++,m++;
				d=min(d,m);
				m=0;
				x=i,y=j;
				while(c[x][y] == '#')
					x++,y++,m++;
				d=min(d,m);
				m=0,x=i,y=j;
				while(c[x][y] == '#')
					x++,y--,m++;
				d=min(d,m);
				a[d]++;
		    }
	for(int i=2;i<=min(h,w)+1;i++)
		cout<<a[i]<<' ';
	return 0;
}
```

## AC记录
[**Atcoder**](https://atcoder.jp/contests/abc300/submissions/41123429)
[**洛谷**](https://www.luogu.com.cn/record/109429661)

**THE END.**

**THANK YOU.** 

---

## 作者：small_john (赞：1)

## 分析

简单的暴力题。

我们只要找到每个为 `#` 的格子，以他为中心往外扩展即可，具体见代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
char a[N][N];
int n,m,ans[N];
int f(int x,int y)
{
	int ret = 0;
	while(x-ret-1>0&&x+ret+1<=n&&y-ret-1>0&&y+ret+1<=m/*没有越界*/
		&&a[x-ret-1][y-ret-1]=='#'&&a[x-ret-1][y+ret+1]=='#'&&a[x+ret+1][y-ret-1]=='#'&&a[x+ret+1][y+ret+1]=='#'/*往外扩展都是#*/)
			ret++;
	return ret;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=m;j++)
			cin>>a[i][j];
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=m;j++)
			if(a[i][j]=='#')
				ans[f(i,j)]++;//统计
	for(int i = 1;i<=min(n,m);i++)
		cout<<ans[i]<<' ';
 	return 0;
}
```

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc300_c)

# $\mathbf{Solution}$

对于每一个中心点，暴力往四个角找。如果某一个角碰到了边界或者遇到了 `.`，立马停止。因为可能存在两个 X 形的两个角有一部分重合的情况。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e2 + 5;
int n, m, used[MAXN][MAXN], ans[MAXN];
char mp[MAXN][MAXN];
bool check(int x, int y){
	return (mp[x + 1][y + 1] == '#' && mp[x - 1][y + 1] == '#' && mp[x + 1][y - 1] == '#' && mp[x - 1][y - 1] == '#');//判断是否为中心点
}
bool check2(int x, int y){
	return mp[x][y] != '#';
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++)cin >> mp[i][j];
	}
	memset(used, 0, sizeof(used));
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			if(mp[i][j] == '#' && check(i, j)){
//				printf("%d %d\n", i, j);
				int cnt = 0;
				int tx1 = i, ty1 = j, tx2 = i, ty2 = j, tx3 = i, ty3 = j, tx4 = i, ty4 = j;
				while(1){
					cnt ++;
					tx1 ++, ty1 ++;
					tx2 ++, ty2 --;
					tx3 --, ty3 ++;
					tx4 --, ty4 --;//四个角分别进行拓展
//					printf("t1:%d %d %d\n", tx1, ty1, check2(tx1, ty1));
//					printf("t2:%d %d %d\n", tx2, ty2, check2(tx2, ty2));
//					printf("t3:%d %d %d\n", tx3, ty3, check2(tx3, ty3));
//					printf("t4:%d %d %d\n", tx4, ty4, check2(tx4, ty4));
					if(check2(tx1, ty1) || check2(tx2, ty2) || check2(tx3, ty3) || check2(tx4, ty4)){//一个角不合法，立马退出
						cnt --;
						ans[cnt] ++;
						break;
					}
				}
//				printf("%d\n", cnt);
				tx1 = i, ty1 = j, tx2 = i, ty2 = j, tx3 = i, ty3 = j, tx4 = i, ty4 = j;
				while(cnt --){
					tx1 ++, ty1 ++;
					tx2 ++, ty2 --;
					tx3 --, ty3 ++;
					tx4 --, ty4 --;
					used[tx1][ty1] = used[tx2][ty2] = used[tx3][ty3] = used[tx4][ty4] = 1;//标记为不可达，防止被重复统计
				}
			}
			used[i][j] = 1;
		}
	}
	for(int i = 1;i <= min(n, m);i ++)cout << ans[i] << ' ';
	return 0;
}
```


---

## 作者：minVan (赞：0)

**题目大意**

我们有一个字符矩阵，其中只有 `.` 和 `#`。

我们定义一个特殊子矩阵，满足一下几个条件：

- 是一个正方形。

- 这个正方形的中心向左上、左下、右上和右下一直到子矩阵角落都是 `#`。

- 任意两个共角的 `#` 不能在不同正方形。

问有多少特殊子矩阵。

**解题思路**

枚举每个点，向左上、左下、右上和右下枚举，一直到有一个不为 `#`。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int h, w, n, s[N];
char c[N][N];
int main() {
    cin >> h >> w;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            cin >> c[i][j];
        }
    }
    n = min(h, w);
    for(int i = 2; i <= h - 1; i++) {
        for(int j = 2; j <= w - 1; j++) {
            if(c[i][j] == '#') {
                int d;
                for(d = 1; d <= n; d++) {
                    if(i + d > h || i - d < 1 || j + d > w || j - d < 1 || c[i + d][j + d] != '#' || c[i + d][j - d] != '#' || c[i - d][j + d] != '#' || c[i - d][j - d] != '#') {
                        d--;
                        break;
                    }
                }
                ++s[d];
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << s[i] << ' ';
    }
    return 0;
}
```

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/)

[atcoder](https://atcoder.jp/contests/abc300/tasks/abc300_c)

### 题目大意

我们有一个 $H$ 行 $W$ 列的网格。我们用 $(i,j)$ 表示网格第 $i$ 行第 $j$ 列的单元格。网格中的每个单元格都有一个符号 `#` 或 `.` 写在上面。定义 $C_{i,j}$ 为写在 $(i,j)$ 上的字符。对于整数 $i$ 和 $j$，若不满足 $1 \le i \le H$ 或 $1 \le j \le W$，则 $C_{i,j}$ 为 `.`。

由 $(a,b)$ 和 $(a+d,b+d),(a-d,b-d),(a-d,b-d)(1 \le d \le n,1 \le n)$ 组成的 $(4n+1)$ 个单元格，当且仅当以下所有条件被满足时，我们称其为以 $(a,b)$ 为中心的大小为 $n$ 的**交叉**：

+ $C_{a,b}$ 是 `#`。
+ 当 $1 \le d \le n$ 时，$C_{a+d,b+d},C_{a+d,b-d},C_{a-d,b+d}$ 和 $C_{a-d,b-d}$ 都是 `#`。
+ $C_{a+n+1,b+n+1},C_{a+n+1,b-n-1},C_{a-n-1,b+n+1}$ 中至少一个是 `.`。

设 $N=\min(H,W)$，$S_n$ 是大小为 $n$ 的**交叉**的数量，求 $S_1,S_2,\dots,S_N$。

$3 \le H,W \le 100$。

### 思路

可以先枚举**交叉**的中心位置，再枚举大小和判断，记录最大的大小。开一个桶，把大小扔到桶里计数，就可以输出了。$O(HWN)$。

#### code

好像很丑陋……答案没有单调性，不可以二分……

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long
#define For(i,a,b) for(int i=(a);i<(b);++i)
int n,m,t[110];char s[110][110];
void solve(){
	cin>>n>>m;
	For(i,0,n)cin>>s[i];
	For(i,0,n)For(j,0,m)if(s[i][j]=='#'){
		int f=0;
		For(k,1,min(n,m)){
			if(i-k<0||i+k>=n||j-k<0||j+k>=m)break;//由题，超出边界不合法
			if(s[i-k][j-k]!='#'||s[i-k][j+k]!='#'||s[i+k][j-k]!='#'||s[i+k][j+k]!='#')break;//当前四个顶点有不是 # 的也不合法
			f=k;//最大大小
		}
		if(f){
			++t[f];//用桶记录
			continue;
		}
	}
	For(i,1,min(n,m)+1)cout<<t[i]<<' ';
	return;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc300_c)         
很简单的搜索。        
我们可以扫一遍 $c$，设这次扫到的位置是 $(i,j)$。        
根据题意，我们可以枚举 $d$，$d$ 为十字架边的长度，判断 $(i,j)$ 到 $(i+d,j+d),(i+d,j-d),(i-d,j+d),(i-d,j-d)$ 四个位置是否都是 `#`，如果都是，那么就是一个十字架。            
因为我们需要寻找最大的十字架，所以我们需要枚举找到最大的 $d$，可以倒序枚举，也可以正序枚举并记录答案。      
我们可以优化一下。我们正序枚举 $d$，在判断的时候无需再判断比 $d$ 小的长度，只判断 $(i+d,j+d),(i+d,j-d),(i-d,j+d),(i-d,j-d)$ 即可。             
同样，我们如果判断的时候发现十字架构成不了了，那么我们记录答案并继续枚举 $i,j$ 即可。          
[CODE](https://www.luogu.com.cn/paste/7a0xx9kz)

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc300_c)

#### 题意

给出 $h$ 行 $w$ 列矩阵，求出有多少大小分别为 $1, 2, 3... \min(h, w)$ 由 # 组成的“十字架”？

#### 思路

由于 $h$ 和 $w$ 很小，直接模拟即可，每次枚举到 # 就以 当前的 # 为中心向四边搜，如果四条边的都相等，那么这就是一个十字架。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,ans[1145],n,s1,s2,s3,s4;
char a[110][110];
int main()
{
	scanf("%d%d",&h,&w);
	n = min(h,w);//求出最小的 
	for(int i = 1;i <= h;i++)
		for(int j = 1;j <= w;j++)
			cin >> a[i][j];
	for(int i = 1;i <= h;i++)//找十字架 
	{
		for(int j = 1;j <= w;j++)
		{
			if(a[i][j] == '#')
			{
				s1 = s2 = s3 = s4 = 0;
				for(int z = i,zz = j;z >= 1 && zz >= 1;z--,zz--) 
				{
					if(a[z][zz] == '#') s1++;
					else break;
				}
				for(int z = i,zz = j;z <= h && zz >= 1;z++,zz--) 
				{
					if(a[z][zz] == '#') s2++;
					else break;
				}
				for(int z = i,zz = j;z >= 1 && zz <= w;z--,zz++) 
				{
					if(a[z][zz] == '#') s3++;
					else break;
				}
				for(int z = i,zz = j;z <= h && zz <= w;z++,zz++) 
				{
					if(a[z][zz] == '#') s4++;
					else break;
				}
				//cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
				if(s1 == s2 && s2 == s3 && s3 == s4) ans[s1 - 1]++;//由于它们都算了当前的#，所以要-- 
			}
		}
	}
	for(int i = 1;i <= n;i++) printf("%d ",ans[i]);
    return 0;
}

```


---

