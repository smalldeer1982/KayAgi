# Serega the Pirate

## 题目描述

Little pirate Serega robbed a ship with puzzles of different kinds. Among all kinds, he liked only one, the hardest.

A puzzle is a table of $ n $ rows and $ m $ columns, whose cells contain each number from $ 1 $ to $ n \cdot m $ exactly once.

To solve a puzzle, you have to find a sequence of cells in the table, such that any two consecutive cells are adjacent by the side in the table. The sequence can have arbitrary length and should visit each cell one or more times. For a cell containing the number $ i $ , denote the position of the first occurrence of this cell in the sequence as $ t_i $ . The sequence solves the puzzle, if $ t_1 < t_2 < \dots < t_{nm} $ . In other words, the cell with number $ x $ should be first visited before the cell with number $ x + 1 $ for each $ x $ .

Let's call a puzzle solvable, if there exists at least one suitable sequence.

In one move Serega can choose two arbitrary cells in the table (not necessarily adjacent by the side) and swap their numbers. He would like to know the minimum number of moves to make his puzzle solvable, but he is too impatient. Thus, please tell if the minimum number of moves is $ 0 $ , $ 1 $ , or at least $ 2 $ . In the case, where $ 1 $ move is required, please also find the number of suitable cell pairs to swap.

## 说明/提示

In the first example the sequence $ (1, 2), (1, 1), (1, 2), (1, 3), (2, 3), (3, 3) $ , $ (2, 3), (1, 3), (1, 2), (1, 1), (2, 1), (2, 2), (3, 2), (3, 1) $ solves the puzzle, so the answer is $ 0 $ .

The puzzle in the second example can't be solved, but it's solvable after any of three swaps of cells with values $ (1, 5), (1, 6), (2, 6) $ .

The puzzle from the third example requires at least two swaps, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3 3
2 1 3
6 7 4
9 8 5```

### 输出

```
0```

## 样例 #2

### 输入

```
2 3
1 6 4
3 2 5```

### 输出

```
1 3```

## 样例 #3

### 输入

```
1 6
1 6 5 4 3 2```

### 输出

```
2```

# 题解

## 作者：Miraik (赞：6)

不难想，但有点卡常，差评。

首先把可解的概念分析一下，容易发现就是对于 $2$ 到 $n\times m$，与它相邻的四个格子中至少有一个数比它小。

先把 $0$ 的情况判掉。

容易发现一次交换至多只会让 $4$ 个不合法的格子变得合法，因此先统计不合法的格子，如果个数大于 $4$ 个直接输出 $2$ 即可。

然后容易发现被交换的两个格子中至少有一个是不合法的格子或者是和不合法的格子相邻的格子，这个个数最多是 $4\times 5= 20$ 个。

然后第一次先枚举这 $20$ 个，第二层再暴力枚举 $n\times m$ 个，每次只需要检查受交换影响的格子就可以了。

复杂度是 $O(nm)$ 级别的，有差不多 $20\times30$ 的常数，但是剪剪枝必然跑不满，可以过。

[丑陋的代码](https://www.luogu.com.cn/paste/8onqqur7)

---

## 作者：灵茶山艾府 (赞：4)

定义**好格子**为：要么是 $1$，要么至少有一个小于自己的邻居。若不满足，则为**坏格子**。

**观察**：如果所有格子都是好格子，那么无需交换。

**证明**：反证法。假设从 $1$ 开始，某个时刻怎么走也走不下去了（遇到了一堵墙）。设此时没有被访问的最小元素为 $x$，那么 $x$ 必然在墙的另一侧。由于所有比 $x$ 小的数我们都访问过了，所以 $x$ 的邻居必然都大于 $x$，所以 $x$ 必然是个坏格子，矛盾，故原命题成立。

我们可以通过交换坏格子（或者坏格子的邻居）与其他的格子，来让坏格子变成好格子。

如果存在坏格子，我们只需考察其中一个坏格子和它的 $4$ 个邻居，因为这个坏格子必须变成好格子。

枚举其中一个坏格子及其邻居，记作 $(x,y)$，然后枚举所有 $(i,j)$，交换二者。交换后，检查是否有坏格子仍然是坏格子，如果是，那么交换失败。如果不是，继续判断 $(x,y),(i,j)$ 及其邻居（至多 $10$ 个格子）是否均为好格子。如果是，那么记录 $((x,y),(i,j))$ 到集合 $\textit{ans}$ 中（目的是去重，注意保证坐标字典序小的在前面）。

如果枚举结束后，$\textit{ans}$ 是空的，说明至少要操作 $2$ 次；否则只需操作 $1$ 次，且方案数为 $\textit{ans}$ 的大小。

⚠**注意**：提前判断有 $4$ 个坏格子就输出 $2$ 的做法是错误的，hack 数据如下：

```
6 7
1  12 11 10 38 37 36
14 13  9  3 39 35 34
15  8  2 42  4 40 33
16 17  7  5 41 31 32
18 19 20  6 28 29 30
21 22 23 24 25 26 27
```

因为交换 $1$ 和 $42$ 即可。

AC 代码（Golang）：

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m int
	Fscan(in, &n, &m)
	a := make([][]int32, n)
	for i := range a {
		a[i] = make([]int32, m)
		for j := range a[i] {
			Fscan(in, &a[i][j])
		}
	}

	// 好格子：自己是 1，或者存在一个小于自己的邻居
	ok := func(i, j int) bool {
		return a[i][j] == 1 ||
			j > 0 && a[i][j-1] < a[i][j] ||
			j+1 < m && a[i][j+1] < a[i][j] ||
			i > 0 && a[i-1][j] < a[i][j] ||
			i+1 < n && a[i+1][j] < a[i][j]
	}
	// 判断 (i,j)，以及 (i,j) 的邻居，是否都是好格子
	ok2 := func(i, j int) bool {
		return ok(i, j) &&
			(j == 0 || ok(i, j-1)) &&
			(j+1 == m || ok(i, j+1)) &&
			(i == 0 || ok(i-1, j)) &&
			(i+1 == n || ok(i+1, j))
	}

	// 收集坏格子
	type pair struct{ i, j int }
	badPos := []pair{}
	for i := range n {
		for j := range m {
			if !ok(i, j) {
				badPos = append(badPos, pair{i, j})
			}
		}
	}
	if len(badPos) == 0 {
		Print(0)
		return
	}

	ans := map[pair]struct{}{}
	// 除了交换 (bi,bj)，也可以通过交换 (bi,bj) 的邻居，使 (bi,bj) 变成一个好格子
	// 只需检查至多 5 个位置，因为 (bi,bj) 必须变成好格子
	bi, bj := badPos[0].i, badPos[0].j
	for _, p := range []pair{{bi, bj}, {bi, bj - 1}, {bi, bj + 1}, {bi - 1, bj}, {bi + 1, bj}} {
		if p.i < 0 || p.i == n || p.j < 0 || p.j == m {
			continue
		}
		for i := range n {
			for j := range m {
				// 交换其他所有点
				a[p.i][p.j], a[i][j] = a[i][j], a[p.i][p.j]
				// 交换离坏格子很远的点，必然是无效交换，所以先检查是否有坏格子仍然是坏格子
				for _, q := range badPos {
					if !ok(q.i, q.j) {
						goto next
					}
				}
				// 有效交换！进一步检查受到影响的 10 个点是否正常
				if ok2(p.i, p.j) && ok2(i, j) {
					// 注意去重
					ans[pair{min(p.i*m+p.j, i*m+j), max(p.i*m+p.j, i*m+j)}] = struct{}{}
				}
			next:
				a[p.i][p.j], a[i][j] = a[i][j], a[p.i][p.j]
			}
		}
	}

	if len(ans) > 0 {
		Println(1, len(ans))
	} else {
		Print(2)
	}
}
```

**时间复杂度**：$\mathcal{O}(nm)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：Rnfmabj (赞：3)

本篇题解内含：

- 难得把自己 perf 打上橙的失智尖啸；

- 赛后补 E 时看完题解脱口而出的“这有两千六？”；

- 懒得写方向数组的迫真毒瘤码风。

------------

### 题意

给定一个 $ n × m $ 的矩阵，矩阵内为 $ 1 $ 至 $ n × m $ 的一个排列。

在矩阵内，可以合法地移动到一个元素 $x$ 上，当且仅当先前移动到元素 $x-1$ 上过。

称一个矩阵是“可解的”当且仅当存在一种以 $ 1 $ 为起点的移动方式，可以遍历整个矩阵。同一元素可以重复遍历。

我们可以通过交换两个元素（不需要相邻）在矩阵中的位置，来使得该矩阵可解。

现在要求：

1. 若该矩阵无需交换操作即为“可解的”，输出 $ 0 $。

2. 若该矩阵可以通过一次交换操作变为“可解的”，输出 $1$ 和 $s$， $s$ 为可行的操作方案数。

3. 若该矩阵需要通过至少两次操作才可变为“可解的”，输出 $2$。

$ n × m \le 4e5  $。


------------

### 思路

什么玩意？分点作答？为什么？（伏笔）

我们显然可以通过一次遍历来判断原矩阵是否可解。但不是无脑 BFS （ $ 4e5 $ 的状压你在想桃子……），而是从 $1$ 到 $n × m$ 挨个访问然后判断是否与已访问过的元素相邻，如果相邻那么一定存在走到该元素的方法，反之不存在。

这样我们就做掉了输出 $ 0 $ 的情况。然后呢？

我们考虑上面这个判断方式的原理。

为什么这个判断方式可以在效率上吊着状压遍历打？因为它优化掉了模拟遍历的这个过程，直接以“是否与已访问过的元素相邻”为标准判断，根据复杂度理论必然优秀许多。

————我是赛时思路的分割线————

慢着，这个标准是叫“是否与已访问过的元素相邻”是吧？这个标准也就意味着，“相邻元素全部大于自身”的元素（除了 $1$ ）是**不可能被访问到的**。

同样的，其他不能被访问到的元素也一定是因为若干个其他不能被访问到的元素把它“隔开”了，所以我们想要让这个矩阵可解，必须要使上述不可能被访问到的元素数归零。

如何减少这种元素的数量呢？

要使一个本不能被访问到的元素可以被访问到，则只有两种情况：

1. 它自己被交换到了一个新的位置上，该位置有相邻元素小于该元素。

2. 它的一个相邻元素被交换了，新的相邻元素小于该元素。

那么对于一个元素，就只有 $5$ 类交换方式：换自己，或者换周围的四个相邻元素。

我们枚举整个矩阵，然后依次尝试与这 $5$ 个元素交换，看换完之后新矩阵是否可解即可。而判断是否可解，只需要数本次交换中减少了多少个不可能被访问到的元素，让原来的数量减去这个变化量，看是否归零即可。

你可能会问：“啊你这只枚举了一个元素啊，如果有多个不可能被访问到的元素怎么办？会有方案遗漏吧？”

假设原矩阵只需要一次交换即可变为可解，那么按照可解的定义，我们一定也处理掉了其他的不可访问元素，所以不会有方案遗漏；

……如果所有的交换都没能使计数器归零呢？

那就说明该元素不可能在一次交换中变为可访问的，原矩阵一定需要至少两次才可变为可解。

诶！？题目要求的分点作答原来是干这个用的！我们判断一次的复杂度是 $O(nm)$ 的，并且可以顺带统计方案数，而如果需要统计两次及以上的方案数的话……设最少需要 $k$ 次，那么时间复杂度直接飙到 $O((nm)^k)$ ，当场上天。

至此，我们得到了本题的正解，并理解了出题人的良苦用心（迫真）。



------------

### 代码

由于调试原因没有写方向数组，导致代码可读性[跳水](https://www.bilibili.com/video/BV1zW411P7Yh)……请酌情参考。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define R read()
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout)
using namespace std;
inline ll read() {
	ll s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
inline void write(ll x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10),x%=10;
	putchar('0'+x);
}//Don't use it for CF.
inline void wk(ll x){write(x);putchar(' ');}
inline void we(ll x){write(x);putchar('\n');}
vector<ll>a[400005];
vector<bool>b[400005];
ll n,m;
ll cnt;//不可访问元素数
bool check(ll x,ll y){//检查一个元素是否为不可访问
	if(x<0||x>=n||y<0||y>=m)return 0;
	bool res=1;
	if(a[x][y]==1)return 0;//特判起点
	if(x)res&=(a[x][y]<a[x-1][y]);
	if(x<n-1)res&=(a[x][y]<a[x+1][y]);
	if(y)res&=(a[x][y]<a[x][y-1]);
	if(y<m-1)res&=(a[x][y]<a[x][y+1]);
	return res;
}
ll curx,cury;
signed main(){
	n=R,m=R;
	for(ll i=0;i<n;i++){
		for(ll j=0;j<m;j++){
			a[i].push_back(R);
			b[i].push_back(0);
		}
	}
	for(ll i=0;i<n;i++){
		for(ll j=0;j<m;j++){
			ll res=check(i,j);
			cnt+=res;
			if(res)curx=i,cury=j;
		}
	}
	if(!cnt){//没有不可访问元素，原矩阵可解
		we(0);
		return 0;
	}
	bool flag=1;
	ll res=0;
	for(ll i=0;i<n;i++){
		for(ll j=0;j<m;j++){
			if(abs(i-curx)+abs(j-cury)<=1)continue;
			for(ll k=1;k<=5;k++){
				ll tmpx=-1,tmpy=-1;
				if(k==1)tmpx=curx,tmpy=cury;
				if(k==2&&curx)tmpx=curx-1,tmpy=cury;
				if(k==3&&curx<n-1)tmpx=curx+1,tmpy=cury;
				if(k==4&&cury)tmpx=curx,tmpy=cury-1;
				if(k==5&&cury<m-1)tmpx=curx,tmpy=cury+1;
				if(tmpx<0&&tmpy<0)continue ;//枚举不可访问元素和它的邻居
			ll tmp=cnt;
			for(ll q=1;q<=5;q++){
				if(q==1&&!b[i][j])tmp-=check(i,j),b[i][j]=1;
				if(q==2&&i&&!b[i-1][j])tmp-=check(i-1,j),b[i-1][j]=1;
				if(q==3&&i<n-1&&!b[i+1][j])tmp-=check(i+1,j),b[i+1][j]=1;
				if(q==4&&j&&!b[i][j-1])tmp-=check(i,j-1),b[i][j-1]=1;
				if(q==5&&j<m-1&&!b[i][j+1])tmp-=check(i,j+1),b[i][j+1]=1;
			}
			for(ll q=1;q<=5;q++){
				if(q==1&&!b[tmpx][tmpy])tmp-=check(tmpx,tmpy),b[tmpx][tmpy]=1;
				if(q==2&&tmpx&&!b[tmpx-1][tmpy])tmp-=check(tmpx-1,tmpy),b[tmpx-1][tmpy]=1;
				if(q==3&&tmpx<n-1&&!b[tmpx+1][tmpy])tmp-=check(tmpx+1,tmpy),b[tmpx+1][tmpy]=1;
				if(q==4&&tmpy&&!b[tmpx][tmpy-1])tmp-=check(tmpx,tmpy-1),b[tmpx][tmpy-1]=1;
				if(q==5&&tmpy<m-1&&!b[tmpx][tmpy+1])tmp-=check(tmpx,tmpy+1),b[tmpx][tmpy+1]=1;
			}
			for(ll q=1;q<=5;q++){
				if(q==1)b[i][j]=0;
				if(q==2&&i)b[i-1][j]=0;
				if(q==3&&i<n-1)b[i+1][j]=0;
				if(q==4&&j)b[i][j-1]=0;
				if(q==5&&j<m-1)b[i][j+1]=0;
				if(q==1)b[tmpx][tmpy]=0;
				if(q==2&&tmpx)b[tmpx-1][tmpy]=0;
				if(q==3&&tmpx<n-1)b[tmpx+1][tmpy]=0;
				if(q==4&&tmpy)b[tmpx][tmpy-1]=0;
				if(q==5&&tmpy<m-1)b[tmpx][tmpy+1]=0;
			}//记录原不可访问数，剪掉该区域的不可访问数
			swap(a[i][j],a[tmpx][tmpy]);
			for(ll q=1;q<=5;q++){
				if(q==1&&!b[i][j])tmp+=check(i,j),b[i][j]=1;
				if(q==2&&i&&!b[i-1][j])tmp+=check(i-1,j),b[i-1][j]=1;
				if(q==3&&i<n-1&&!b[i+1][j])tmp+=check(i+1,j),b[i+1][j]=1;
				if(q==4&&j&&!b[i][j-1])tmp+=check(i,j-1),b[i][j-1]=1;
				if(q==5&&j<m-1&&!b[i][j+1])tmp+=check(i,j+1),b[i][j+1]=1;
			}
			for(ll q=1;q<=5;q++){
				if(q==1&&!b[tmpx][tmpy])tmp+=check(tmpx,tmpy),b[tmpx][tmpy]=1;
				if(q==2&&tmpx&&!b[tmpx-1][tmpy])tmp+=check(tmpx-1,tmpy),b[tmpx-1][tmpy]=1;
				if(q==3&&tmpx<n-1&&!b[tmpx+1][tmpy])tmp+=check(tmpx+1,tmpy),b[tmpx+1][tmpy]=1;
				if(q==4&&tmpy&&!b[tmpx][tmpy-1])tmp+=check(tmpx,tmpy-1),b[tmpx][tmpy-1]=1;
				if(q==5&&tmpy<m-1&&!b[tmpx][tmpy+1])tmp+=check(tmpx,tmpy+1),b[tmpx][tmpy+1]=1;
			}
			for(ll q=1;q<=5;q++){
				if(q==1)b[i][j]=0;
				if(q==2&&i)b[i-1][j]=0;
				if(q==3&&i<n-1)b[i+1][j]=0;
				if(q==4&&j)b[i][j-1]=0;
				if(q==5&&j<m-1)b[i][j+1]=0;
				if(q==1)b[tmpx][tmpy]=0;
				if(q==2&&tmpx)b[tmpx-1][tmpy]=0;
				if(q==3&&tmpx<n-1)b[tmpx+1][tmpy]=0;
				if(q==4&&tmpy)b[tmpx][tmpy-1]=0;
				if(q==5&&tmpy<m-1)b[tmpx][tmpy+1]=0;
			}//计算新的不可访问数，加回去看是否归零
			if(tmp==0){
				res++;
				flag=0;
			}
			swap(a[i][j],a[tmpx][tmpy]);
			}
		}
	}
	for(ll k=2;k<=5;k++){//为了防止方案重复，单独处理该元素与其邻居互换的情况。
		ll i=curx,j=cury;
		ll tmpx=-1,tmpy=-1;
				if(k==2&&curx)tmpx=curx-1,tmpy=cury;
				if(k==3&&curx<n-1)tmpx=curx+1,tmpy=cury;
				if(k==4&&cury)tmpx=curx,tmpy=cury-1;
				if(k==5&&cury<m-1)tmpx=curx,tmpy=cury+1;
				if(tmpx<0&&tmpy<0)continue ;
			ll tmp=cnt;
			for(ll q=1;q<=5;q++){
				if(q==1&&!b[i][j])tmp-=check(i,j),b[i][j]=1;
				if(q==2&&i&&!b[i-1][j])tmp-=check(i-1,j),b[i-1][j]=1;
				if(q==3&&i<n-1&&!b[i+1][j])tmp-=check(i+1,j),b[i+1][j]=1;
				if(q==4&&j&&!b[i][j-1])tmp-=check(i,j-1),b[i][j-1]=1;
				if(q==5&&j<m-1&&!b[i][j+1])tmp-=check(i,j+1),b[i][j+1]=1;
			}
			for(ll q=1;q<=5;q++){
				if(q==1&&!b[tmpx][tmpy])tmp-=check(tmpx,tmpy),b[tmpx][tmpy]=1;
				if(q==2&&tmpx&&!b[tmpx-1][tmpy])tmp-=check(tmpx-1,tmpy),b[tmpx-1][tmpy]=1;
				if(q==3&&tmpx<n-1&&!b[tmpx+1][tmpy])tmp-=check(tmpx+1,tmpy),b[tmpx+1][tmpy]=1;
				if(q==4&&tmpy&&!b[tmpx][tmpy-1])tmp-=check(tmpx,tmpy-1),b[tmpx][tmpy-1]=1;
				if(q==5&&tmpy<m-1&&!b[tmpx][tmpy+1])tmp-=check(tmpx,tmpy+1),b[tmpx][tmpy+1]=1;
			}
			for(ll q=1;q<=5;q++){
				if(q==1)b[i][j]=0;
				if(q==2&&i)b[i-1][j]=0;
				if(q==3&&i<n-1)b[i+1][j]=0;
				if(q==4&&j)b[i][j-1]=0;
				if(q==5&&j<m-1)b[i][j+1]=0;
				if(q==1)b[tmpx][tmpy]=0;
				if(q==2&&tmpx)b[tmpx-1][tmpy]=0;
				if(q==3&&tmpx<n-1)b[tmpx+1][tmpy]=0;
				if(q==4&&tmpy)b[tmpx][tmpy-1]=0;
				if(q==5&&tmpy<m-1)b[tmpx][tmpy+1]=0;
			}
			swap(a[i][j],a[tmpx][tmpy]);
			for(ll q=1;q<=5;q++){
				if(q==1&&!b[i][j])tmp+=check(i,j),b[i][j]=1;
				if(q==2&&i&&!b[i-1][j])tmp+=check(i-1,j),b[i-1][j]=1;
				if(q==3&&i<n-1&&!b[i+1][j])tmp+=check(i+1,j),b[i+1][j]=1;
				if(q==4&&j&&!b[i][j-1])tmp+=check(i,j-1),b[i][j-1]=1;
				if(q==5&&j<m-1&&!b[i][j+1])tmp+=check(i,j+1),b[i][j+1]=1;
			}
			for(ll q=1;q<=5;q++){
				if(q==1&&!b[tmpx][tmpy])tmp+=check(tmpx,tmpy),b[tmpx][tmpy]=1;
				if(q==2&&tmpx&&!b[tmpx-1][tmpy])tmp+=check(tmpx-1,tmpy),b[tmpx-1][tmpy]=1;
				if(q==3&&tmpx<n-1&&!b[tmpx+1][tmpy])tmp+=check(tmpx+1,tmpy),b[tmpx+1][tmpy]=1;
				if(q==4&&tmpy&&!b[tmpx][tmpy-1])tmp+=check(tmpx,tmpy-1),b[tmpx][tmpy-1]=1;
				if(q==5&&tmpy<m-1&&!b[tmpx][tmpy+1])tmp+=check(tmpx,tmpy+1),b[tmpx][tmpy+1]=1;
			}
			for(ll q=1;q<=5;q++){
				if(q==1)b[i][j]=0;
				if(q==2&&i)b[i-1][j]=0;
				if(q==3&&i<n-1)b[i+1][j]=0;
				if(q==4&&j)b[i][j-1]=0;
				if(q==5&&j<m-1)b[i][j+1]=0;
				if(q==1)b[tmpx][tmpy]=0;
				if(q==2&&tmpx)b[tmpx-1][tmpy]=0;
				if(q==3&&tmpx<n-1)b[tmpx+1][tmpy]=0;
				if(q==4&&tmpy)b[tmpx][tmpy-1]=0;
				if(q==5&&tmpy<m-1)b[tmpx][tmpy+1]=0;
			}
			if(tmp==0){
				res++;
				flag=0;
			}
			swap(a[i][j],a[tmpx][tmpy]);
			
	}
	if(flag){//至少两次
		we(2);
	}
	else {//输出方案数
		wk(1),we(res);
	}
	return 0;
}

```


---

## 作者：IdnadRev (赞：3)

好简单啊，为什么过的人那么少。。。

一个显然的判定方法是检查每个大于 $1$ 的位置，其上下左右是否有比它小的数字。可以对每个位置维护其相邻的小于它的数字数量，再维护一个全局不合法数字数量，就可以快速判断一次交换是否合法了。

随便找到一个不合法的位置，那么我们交换的位置一定是这个不合法位置，或者其上下左右。枚举这五个位置中的一个，再随便枚举另一个位置模拟一下交换即可。

复杂度 $O(nm)$。

```cpp
#include<stdio.h>
#include<vector>
using namespace std;
const int maxn=400005;
int n,m,ans,tott;
int x[maxn],y[maxn],vis[maxn],dx[5]= {0,1,0,0,-1},dy[5]= {0,0,1,-1,0},tot[maxn];
vector<int>a[maxn];
long long res;
void cswap(int p,int q) {
	int ax=x[p],ay=y[p],bx=x[q],by=y[q];
	tott-=(tot[p]==0)+(tot[q]==0);
	swap(a[ax][ay],a[bx][by]),x[q]=ax,y[q]=ay,x[p]=bx,y[p]=by;
	for(int i=1; i<=4; i++) {
		int ux=ax+dx[i],uy=ay+dy[i];
		if(ux>=1&&ux<=n&&uy>=1&&uy<=m) {
			int u=a[ux][uy];
			if(u==p||u==q)
				continue;
			tott-=tot[u]==0,tot[u]+=(q<=u)-(p<=u),tott+=tot[u]==0;
			tot[p]-=(u<=p),tot[q]+=(u<=q);
		}
	}
	for(int i=1; i<=4; i++) {
		int ux=bx+dx[i],uy=by+dy[i];
		if(ux>=1&&ux<=n&&uy>=1&&uy<=m) {
			int u=a[ux][uy];
			if(u==p||u==q)
				continue;
			tott-=tot[u]==0,tot[u]+=(p<=u)-(q<=u),tott+=tot[u]==0;
			tot[p]+=(u<=p),tot[q]-=(u<=q);
		}
	}
	tott+=(tot[p]==0)+(tot[q]==0);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) {
		a[i].resize(m+1);
		for(int j=1; j<=m; j++)
			scanf("%d",&a[i][j]),x[a[i][j]]=i,y[a[i][j]]=j;
	}
	tot[1]=1e9;
	for(int i=1; i<=n*m; i++) {
		int px=x[i],py=y[i];
		for(int j=1; j<=4; j++) {
			int ux=px+dx[j],uy=py+dy[j];
			if(ux>=1&&ux<=n&&uy>=1&&uy<=m)
				tot[i]+=a[ux][uy]<=i;
		}
		if(tot[i]==0&&ans==0)
			ans=i;
	}
	if(ans==0) {
		puts("0");
		return 0;
	}
	for(int i=1; i<=n*m; i++)
		tott+=tot[i]==0;
	for(int d=0; d<=4; d++) {
		int ux=x[ans]+dx[d],uy=y[ans]+dy[d];
		if(ux>=1&&ux<=n&&uy>=1&&uy<=m)
			vis[a[ux][uy]]=1;
	}
	for(int d=0; d<=4; d++) {
		int ux=x[ans]+dx[d],uy=y[ans]+dy[d];
		if(ux>=1&&ux<=n&&uy>=1&&uy<=m) {
			for(int i=1; i<=n*m; i++)
				if(vis[i]==0||(vis[i]==1&&d==0&&i!=ans)) {
					int r=a[ux][uy];
					cswap(i,r);
					if(tott==0)
						res++;
					cswap(i,r);
				}
		}
	}
	if(res==0)
		puts("2");
	else printf("1 %lld\n",res);
	return 0;
}
```

---

## 作者：by_chance (赞：2)

[Link](https://www.luogu.com.cn/problem/CF1700E)

看到这个奇怪的问题，可以想到枚举。

首先对原题做一些转化：对于两个相邻的格子，从数字较小的那个向另一个连有向边。如此建图之后，“可解”就变成：除了填 $1$ 的格子，其它格的入度均不为 $0$。

那么首先对给定的填法建图（其实只用统计入度），如果已经满足条件，输出 $0$ 即可。否则，记 $cnt$ 为入度为 $0$ 的格数（不含 $1$）。

由于只能交换一对格子，所以至多影响 $10$ 个格子的度，当 $cnt \gt 10$ 时可以直接输出 $2$。

然后，由于入度为 $0$ 的格需要被消灭，所以其周围 $4$ 格与本身一定至少一个被改变。枚举这个格子和与之交换的格子即可。注意不要重复枚举。

下面的问题是判定交换两个格子是否满足条件。这并不麻烦。

首先把与这两个格子相关的边全部断开，也就是修改入度。注意不要重复。

然后交换数字，再连边。在此过程中，记录所涉及点入度的改变量。

最后对所有初始入度为 $0$ 的点判断一下，再对所有涉及的点判断一下入度就可以了。注意初始化不能用 memset（其实我没试过，不过大概率会 TLE）。

时间复杂度 $O(n\times m)$，但是大常数，但是能过。

代码写得很丑，开始绕了许多弯路。[Code](https://www.luogu.com.cn/paste/4s6kwixk)

Upd：修改了格式。

---

## 作者：_anll_ (赞：0)

第一次订过 div2 的 E 题，~~虽然花了一个下午加一个晚上找两个笨蛋错误~~所以特此纪念。

简单模拟题，但要注意细节。
## 大体思路
根据题意可轻松得知一个格子不合法当且仅当格子内的数不等于 $1$ 且附近四个格子没有比它小的数。因此我们可以先 $O(n\times m)$ 遍历整个矩阵求不合法格子个数 $cnt$。如果 $cnt$ 为 $0$ 则直接输出 $0$，反之需要继续判断。

由于我们只处理交换一次就变为合法的情况，因此我们只需要对于任意一个不合法坐标 $(x,y)$ 进行处理。具体而言，因为将一个不合法格子变为合法只有两种情况：选择将自身交换至比自身小的元素附近、将周围元素与比自身小的元素交换。因此可以枚举它上下左右以及自己本身与整个矩阵各个格子交换是否可以变为合法。如果可以则将方案数增加。若到枚举结束还没找到方案，则说明有至少两个不合法格子无法共享一次交换而变为合法，因此我们需要交换两次以上。

显然当且仅当交换前的不合法数刚好为 $cnt$，交换后无不合法数时交换有效。

对于交换 $(a,b)$ 和 $(x,y)$，会且仅会影响以 $(a,b)$ 和 $(x,y)$ 为中心的上下左右以及自己的格子，至多 $10$ 个。而因为我们需要处理交换前和交换后的，每次判断是否合法还需遍历周围的四个格子，因此时间复杂度大概为 $O(nm)$，还会有一点常数，大概是 $80$ 左右。但实际操作时我用了 map 进行对 $(a,b),(x,y)$ 的查重，因此时间复杂度会再高一点，但依旧可以通过本题。

## 代码
写的有点丑，码量稍微有点大，将就着参考一下就好了。
```cpp
#include<iostream>
#include<vector>
#include<map>
#define int long long
using namespace std;
const int N=4e5+5;
int n,m,cnt,ans,px,py,pos[5][2]={{+1,0},{-1,0},{0,+1},{0,-1},{0,0}}; 
vector<int> mp[N],vo[N];
map<pair<pair<int,int>,pair<int,int> >,int> vu;
bool ch(int x,int y){
	if(x<1||x>n||y<1||y>m) return 0;
	return 1;
}
bool check1(int x,int y){
	if(!ch(x,y)) return 1;
	for(int i=0;i<4;i++){
		int xx=x+pos[i][0],yy=y+pos[i][1];
		if(!ch(xx,yy)) continue;
		if(mp[xx][yy]<mp[x][y]) return 1;
	}
	return 0;
}
int work(int a,int b,int x,int y){
	int xx,yy,tot=0;
	for(int i=0;i<5;i++){
		xx=x+pos[i][0],yy=y+pos[i][1];
		/*使用vector判重, 用map或unordered_map均会超时 
		注意这里为1时也需跳过, 因为1的周围没有比它小的
		这里不能盲目continue!  这个错误我调了两个小时啊啊啊 */ 
		if(vo[xx][yy]||(ch(xx,yy)&&mp[xx][yy]==1)) goto bbb;
		vo[xx][yy]=1;
		if(!check1(xx,yy)) tot++;
		bbb:
		xx=a+pos[i][0],yy=b+pos[i][1];
		if(vo[xx][yy]||(ch(xx,yy)&&mp[xx][yy]==1)) continue;
		vo[xx][yy]=1;
		if(!check1(xx,yy)) tot++;
	}
	for(int i=0;i<5;i++){
		xx=x+pos[i][0],yy=y+pos[i][1];
		vo[xx][yy]=0;
		xx=a+pos[i][0],yy=b+pos[i][1];
		vo[xx][yy]=0;
	}
	return tot;
}
void check2(int a,int b,int x,int y){
	int xx,yy,tot1=0,tot2=0;
	if(!ch(x,y)) return;
	tot1=work(a,b,x,y);
	if(cnt!=tot1) return; 
	swap(mp[a][b],mp[x][y]);
	tot2=work(a,b,x,y);
	if(!tot2&&!vu[{{a,b},{x,y}}]){
		vu[{{a,b},{x,y}}]=vu[{{x,y},{a,b}}]=1;
		ans++;
	}
	swap(mp[a][b],mp[x][y]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;int awa;
	for(int i=1;i<=n;i++){
		mp[i].push_back(0);vo[i].push_back(0);
		for(int j=1;j<=m;j++){
			cin>>awa;
			mp[i].push_back(awa);vo[i].push_back(0);
		}
		vo[i].push_back(0);
	}
	//这里记得把vo给大一点不然访问到边界外会RE 
	for(int i=0;i<=m+1;i++) vo[0].push_back(0);
	for(int i=0;i<=m+1;i++) vo[n+1].push_back(0);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
		if(!check1(i,j)&&mp[i][j]!=1) cnt++,px=i,py=j;
	if(!cnt){cout<<0;return 0;}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<5;k++)
				check2(i,j,px+pos[k][0],py+pos[k][1]);
	if(ans) cout<<"1 "<<ans;
	else cout<<2;
	return 0;
}
```

---

## 作者：Creative_sad_yosgic (赞：0)

## Serega the Pirate
### 思路
首先分析题意和样例，易得出不合法的格子就是**上下左右都没有比它小**的格子。

然后先 nm 枚举判定一遍，如果没有不合法格子就直接输出 0 然后结束。

但如果有不合法的格子呢？我的处理是先丢进一个队列里~~然后继续分析~~。

题目告诉你交换 2 次及以上就直接输出 2，考虑什么样的情况 1 次交换不能解决问题，易发现每次交换只会影响到 4 个格子的合法状态，所以不合法的格子数量大于 4 就可以直接输出 2 了。

然后想到需要交换的要么是**不合法的格子**，要么是**它周围的格子**，所以考虑暴力一点，直接把这些格子丢队列里，然后在所有格子中暴力枚举交换，影响到的也只有交换两个元素周围的格子，把这些丢进一个 pair 里，然后判所有目前可能不合法的格子的合法性就好了。因为基本上总会提前退出，所以复杂度跑不满，Accepted 是稳的。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int ans,res,sum,fuc[3003][3003],cnt,cnt2;
map<int,map<int,int>> vis;//范围较大用二维 map 记录当前交换是否已经统计过
pair<int,int> No[25],tmp[25];//用于记录可能不合法格子
struct node{
	int x,y;
};
queue<node> q;//记录初始不合法及周围格子
vector<int> a[400005];//存图 因为范围不定用 vector
bool coke(int x,int y){
	if(a[x][y]==1) return true;
	int minn=0x3f3f3f3f;
	if(x+1<=n) minn=min(minn,a[x+1][y]);
	if(x-1>=1) minn=min(minn,a[x-1][y]);
	if(y+1<=m) minn=min(minn,a[x][y+1]);
	if(y-1>=1) minn=min(minn,a[x][y-1]);
	return minn<a[x][y];
}//判定当前格子是否合法
void Push(int x,int y){
	q.push({x,y});No[++cnt].first=x,No[cnt].second=y;
	if(x+1<=n) {q.push({x+1,y}); No[++cnt].first=x+1,No[cnt].second=y;}
	if(x-1>=1) {q.push({x-1,y});No[++cnt].first=x-1,No[cnt].second=y;}
	if(y+1<=m) {q.push({x,y+1});No[++cnt].first=x,No[cnt].second=y+1;}
	if(y-1>=1) {q.push({x,y-1});No[++cnt].first=x,No[cnt].second=y-1;}//将初始不合法及周围格子放入队列
}
void ge(int x,int y){
	if(x+1<=n) {tmp[++cnt2].first=x+1,tmp[cnt2].second=y;}
	if(x-1>=1) {tmp[++cnt2].first=x-1,tmp[cnt2].second=y;}
	if(y+1<=m) {tmp[++cnt2].first=x,tmp[cnt2].second=y+1;}
	if(y-1>=1) {tmp[++cnt2].first=x,tmp[cnt2].second=y-1;}//将交换后可能不合法的格子记录
}
void bfs(){
	while(!q.empty()){
		node c=q.front();
		q.pop();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){//暴力枚举交换
				cnt2=0;
				//if(c.x==i&&c.y==j) continue;
				ge(i,j);
				ge(c.x,c.y);
				swap(a[c.x][c.y],a[i][j]);
				if((!coke(c.x,c.y))||(!coke(i,j))) {swap(a[c.x][c.y],a[i][j]);continue;}
				int flag=0;
				for(int k=1;k<=cnt;k++){
					if(!coke(No[k].first,No[k].second)){
						flag=1;
						swap(a[c.x][c.y],a[i][j]);
						break;
					}
				}
				if(flag) {continue;}
				for(int k=1;k<=cnt2;k++){
					if(!coke(tmp[k].first,tmp[k].second)){
						flag=1;
						swap(a[c.x][c.y],a[i][j]);
						break;
					}
				}
				if(flag) continue;
				if(vis[a[c.x][c.y]][a[i][j]]==0) res++,vis[a[c.x][c.y]][a[i][j]]=1,vis[a[i][j]][a[c.x][c.y]]=1;
				swap(a[c.x][c.y],a[i][j]);//别忘了交换回去
			}
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
	    a[i].resize(m+1);//定义一个范围
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]!=1&&!coke(i,j)){
				++ans;
				Push(i,j);
				if(ans>4){
					cout<<2;
					return 0;
				}
			}
		}
	if(!ans) cout<<0;
	else{
		bfs();
		/*for(int i=1;i<=cnt;i++){
			cout<<No[i].first<<" "<<No[i].second<<'\n';
		}*/
		if(!res) cout<<2;
		else cout<<1<<" "<<res;
	}
    return 0;		
}
```


---

## 作者：intel_core (赞：0)

首先 `check` 一下 0，发现等价于除了 1 之外的每个数与它四相邻的数中都有一个比它小的。

然后考虑把 1 和 2 区分开，发现一步能达到要求没有显然的充要条件。

所以我们可以考虑暴力的尝试，套用前述结论暴力枚举所有格子检查，但明显过不了。

注意到若我们交换 $x$ 和 $y$（不妨 $x<y$），此时只会导致原本与 $y$ 四相邻的数的合法状态改变。

所以，我们得到结论：若不合法的格子多于4个，则一步解决不了。

现在考虑统计数量，若不合法的格子不多于4个，则交换中的 $y$ 的范围不超过 $20$ 个。

然后 $x$ 全局枚举，`check` 的时候只需要考虑与 $x$ 和 $y$ 四相邻的格子即可。

复杂度 $O(nm)$，常数理论最大 $800$。

---

## 作者：james1BadCreeper (赞：0)

首先看看什么时候答案是 $0$：一个点能够走到，要么它是 $1$，要么在一个四联通块中有点可以走到它，也就是上下左右有一个数比它小。

当有一些点不满足上述条件时，就必须要执行交换操作了。交换什么？只有交换这个四联通块中的点和局外的一个点才可能让这个点变得合法。但是这道题并不需要我们输出操作数，只有在操作数为 $1$ 的时候才要求我们输出方案数，因此可以暴力枚举：选择其中任意一个不能被走到的点，枚举与它交换的点，交换后看能影响到的 $10$ 个点（相当于改变了两个四联通块，共 $10$ 个点）和剩下的原本就不能到的点是否满足条件，满足条件就是一种方案。

如果一开始就不能到达的节点超过了 $10$ 个，那么一次交换操作就肯定不能完成了（一次交换只能影响至多 $10$ 个点）。

时间复杂度 $O(nm)$，因为需要枚举方向带一个约百倍的常数。但实际上很快就会因为不符合条件而跳出循环，根本跑不满，可以轻松通过。

只要不像笔者一样把 $j$ 写成 $i$，代码就不难写了。个人认为这份代码还是比较清爽的。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;
const int dx[] = {0, 1, -1, 0, 0}, dy[] = {0, 0, 0, 1, -1};

int n, m, X[400005], Y[400005];
vector<vector<int> > a;
vector<int> v;

bool check(int x, int y) {
    if (a[x][y] == 1) return true;
    for (int i = 1; i <= 4; ++i) {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && a[tx][ty] < a[x][y]) return true;
    }
    return false;
}

int main(void) {
    scanf("%d%d", &n, &m);
    a.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i].resize(m + 1);
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            X[a[i][j]] = i, Y[a[i][j]] = j;
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (!check(i, j)) v.push_back(a[i][j]);
    if (v.empty()) return puts("0"), 0;
    if (v.size() >= 10) return puts("2"), 0;
    set<pair<int, int>> s;
    for (int i = 0; i < 5; ++i) {
        int x = X[v[0]] + dx[i], y = Y[v[0]] + dy[i];
        if (x < 1 || x > n || y < 1 || y > m) continue;
        for (int xx = 1; xx <= n; ++xx)
            for (int yy = 1; yy <= m; ++yy) {
                swap(a[x][y], a[xx][yy]);
                bool ok = true;
                for (int j = 0; j < v.size() && ok; ++j)
                    if (!check(X[v[j]], Y[v[j]])) ok = false;
                for (int j = 0; j < 5 && ok; ++j) {
                    int tx = x + dx[j], ty = y + dy[j];
                    if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && !check(tx, ty)) ok = false;
                }
                for (int j = 0; j < 5 && ok; ++j) {
                    int tx = xx + dx[j], ty = yy + dy[j];
                    if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && !check(tx, ty)) ok = false;
                }
                if (ok) {
                    int u = a[x][y], v = a[xx][yy];
                    if (u > v) swap(u, v);
                    s.insert(make_pair(u, v));
                }
                swap(a[x][y], a[xx][yy]);
            }
    }
    if (s.empty()) puts("2");
    else printf("1 %d\n", s.size());
    return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：0)

这能 *2600 ？

显然暴力就是枚举交换哪两块，复杂度 $O((nm)^2)$ 。

题目相当于要求对于除了 1 以外的块，每一块的相邻的四个块都要有至少一个比它小的。

找出所有不符合条件的，考虑在答案为 1 的时候不符合条件的最多能有多少个。

然后会发现就是有公共块的 4 个，所以 $cnt>4$ 的时候直接 2，因为每次操作最多只能使 4 个不合法的变合法。

考虑暴力枚举交换的两块，其中一块发现只有三种可能。

1. 值为 1 的块

2. 不合法的块

3. 和不合法的块相邻的块

相邻的块可以再分类讨论缩小数量级，不过不分讨也行，直接暴力枚举一共有 16 块，算上前两种一共有 20 块。

然后枚举这 20 块，然后暴力枚举另一块，判断的时候只用判掉所有不合法的块以及交换的两块相邻的块在交换以后是否合法即可，实现精细可以做到 $O(20\times 4nm)$ ，但直接暴力的 $O(20^2nm)$ 也可以过，原因是一定跑不满。

https://codeforces.com/contest/1700/submission/161387023

---

