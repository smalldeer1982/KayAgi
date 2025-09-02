# Binary Table (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is in the number of possible operations that can be made. You can make hacks if and only if you solved both versions of the problem.

You are given a binary table of size $ n \times m $ . This table consists of symbols $ 0 $ and $ 1 $ .

You can make such operation: select $ 3 $ different cells that belong to one $ 2 \times 2 $ square and change the symbols in these cells (change $ 0 $ to $ 1 $ and $ 1 $ to $ 0 $ ).

Your task is to make all symbols in the table equal to $ 0 $ . You are allowed to make at most $ nm $ operations. You don't need to minimize the number of operations.

It can be proved, that it is always possible.

## 说明/提示

In the first test case, it is possible to make only one operation with cells $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ . After that, all symbols will be equal to $ 0 $ .

In the second test case:

- operation with cells $ (2, 1) $ , $ (3, 1) $ , $ (3, 2) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>011<br></br>001<br></br>000<br></br>
  ```
- operation with cells $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>000<br></br>000<br></br>000<br></br>
  ```

In the fifth test case:

- operation with cells $ (1, 3) $ , $ (2, 2) $ , $ (2, 3) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>010<br></br>110<br></br>
  ```
- operation with cells $ (1, 2) $ , $ (2, 1) $ , $ (2, 2) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>000<br></br>000<br></br>
  ```

## 样例 #1

### 输入

```
5
2 2
10
11
3 3
011
101
110
4 4
1111
0110
0110
1111
5 5
01011
11001
00010
11011
10000
2 3
011
101```

### 输出

```
1
1 1 2 1 2 2
2 
2 1 3 1 3 2
1 2 1 3 2 3
4
1 1 1 2 2 2 
1 3 1 4 2 3
3 2 4 1 4 2
3 3 4 3 4 4
4
1 2 2 1 2 2 
1 4 1 5 2 5 
4 1 4 2 5 1
4 4 4 5 3 4
2
1 3 2 2 2 3
1 2 2 1 2 2```

# 题解

## 作者：timmark (赞：8)

# CF1439A2 题解

我们的红太阳 rfy 在模拟赛搬了这题，场上人均 $100+$ 行。

题解中将会结合原题的背景（把二进制表格换成灯）。

[题目传送门](https://www.luogu.com.cn/problem/CF1439A2)

## 导入

我们先考虑此题的简单版，即在 $3\times n\times m$ 次内使整个矩阵归零（CF1439A1）。

我们可以发现，对于一个 $2\times 2$ 的矩阵，我们可以在不影响其他灯的情况下使一个灯状态反转。如下图（图 1-1-1），图中有蓝色光晕的是被反转的灯。

| ![1726282215077](https://img.picgo.net/2024/09/15/1724459162538add383e249a31e81.png) |
| :----------------------------------------------------------: |
|                           图 1-1-1                           |

这样复杂度是 $O(nm)$ 的，复杂度正确，但是对于此题不够优。

考虑这个方法有什么缺点。

我们发现对于需要取反更多灯的情况下，不需要对每个灯都做图中的操作，我们可以把它分成几种情况。

## 核心

考虑分类讨论 $2\times 2$ 范围内灯的数量。（对于同一种外形旋转后视作相同，红为亮白为灭）

### $3$ 个灯

即图 2-1-1，可以直接一次将其归零。

| ![1724459646833](https://img.picgo.net/2024/09/15/17244596468338b282087307fc343.png) |
| :----------------------------------------------------------: |
|                           图 2-1-1                           |

### $2$ 个灯

此时有两种情况，图 2-2-1 或 2-2-2，不难发现我们可以用一次操作使当前局面变成三个灯。

| ![1726282394857](https://img.picgo.net/2024/09/15/1726282394857c2486d4c0ef61f39.png) | ![1726282342614](https://img.picgo.net/2024/09/15/17262823126510ab10c14eaf4e47c.png) |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
|                           图 2-2-1                           |                           图 2-2-2                           |

### $1$ 个灯

即图 2-3-1，可以一次将其转化为两个灯。

| ![1726282538076](https://img.picgo.net/2024/09/15/1726282538076977b8efaf3488095.png) |
| :----------------------------------------------------------: |
|                           图 2-3-1                           |

### $4$ 个灯

即图 2-4-1，可以一次将其转化为一个灯。

| ![1726282688685](https://img.picgo.net/2024/09/15/17262826886859b500b285345717b.png) |
| :----------------------------------------------------------: |
|                           图 2-4-1                           |

那么也就是说对于任意一个 $2\times 2$ 的子矩阵，我们最多 $4$ 次即可将其归零。

## 尾声

但是 $n,m$ 可能是奇数，这里给出两种实现方法：

### 本人的赛时做法

显然，整个 $n\times m$ 可以被划分成若干个 $2\times 2$、$2\times 3$、$3\times 2$、$3\times 3$ 的子矩阵。下图（图 3-1-1）是一个 $n=7,m=9$ 的示例。

| ![1726283397063](https://img.picgo.net/2024/09/15/17262833970637eeb741b6a047e98.png) |
| :----------------------------------------------------------: |
|                           图 3-1-1                           |

对于一个 $2\times3$，可以在其边上做最多两次覆盖，如图 3-1-2，左边的 $4$ 个灯用渐变色上下的颠倒表示原状态或取反状态。

| ![1726295340038](https://img.picgo.net/2024/09/15/1726295340038f279ac9b99eeaa40.png) |
| :----------------------------------------------------------: |
|                           图 3-1-2                           |

对于 $2\times 3$ 和 $3\times 3$ 同理。

最后将整个 $n\times m$ 分割后把这几种用函数打包起来进行处理即可。

### 其他人的方法

在 $n$ 或 $m$ 为奇数时，其实可以通过与上面类似的方法把最后的一行或一列先归零，然后按 $n,m$ 为偶数做即可。

## Tips.

在对 $2\times2$ 处理时，可以按照以下流程图（图 4-1-1）。

| ![1726316203498](https://img.picgo.net/2024/09/15/17263162034982c3100c61528058d.png) |
| :----------------------------------------------------------: |
|                           图 4-1-1                           |

## Code

### 码风优化后的赛时代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
int t,n,m,cnt,a[105][105];
struct node{int a,b,c,d,e,f;}ans[30005];
char ch;
void x22(int x,int y){//处理 2*2
	int sum=a[x][y]+a[x+1][y+1]+a[x+1][y]+a[x][y+1];
	if(!sum) return ;
	if(sum==4){//四个灯
		a[x][y]^=1;
		a[x+1][y]^=1;
		a[x][y+1]^=1;
		ans[++cnt]={x,y,x+1,y,x,y+1};
		sum=1;
	}if(sum==1){//一个灯
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				if(a[x+i][y+j]){
					a[x+i][y+j]^=1;
					a[x+1-i][y+j]^=1;
					a[x+i][y+1-j]^=1;
					ans[++cnt]={x+i,y+j,x+1-i,y+j,x+i,y+1-j};
					sum=2;
					goto do2;
				}
			}
		}
	}do2: ;
	if(sum==2){//两个灯
		int xx[5],yy[5],tmp=0;
		for(int i=x;i<x+2;i++) for(int j=y;j<y+2;j++) if(!a[i][j]) ++tmp,xx[tmp]=i,yy[tmp]=j;
		for(int i=x;i<x+2;i++){
			for(int j=y;j<y+2;j++){
				if(a[i][j]){
					a[i][j]^=1;
					a[xx[1]][yy[1]]^=1;
					a[xx[2]][yy[2]]^=1;
					ans[++cnt]={i,j,xx[1],yy[1],xx[2],yy[2]};
					sum=3;
					goto do3;
				}
			}
		}
	}do3: ; 
	if(sum==3){//三个灯
		int xx[5],yy[5],tmp=0;
		for(int i=x;i<x+2;i++){
			for(int j=y;j<y+2;j++){
				if(a[i][j]){
					++tmp;
					xx[tmp]=i;
					yy[tmp]=j;
					a[i][j]^=1;
				} 
			}
		}ans[++cnt]={xx[1],yy[1],xx[2],yy[2],xx[3],yy[3]};
	}
}void x23(int x,int y){//处理 2*3
	if(a[x][y]) ans[++cnt]={x,y,x,y+1,x+1,y+1},a[x][y]^=1,a[x][y+1]^=1,a[x+1][y+1]^=1;
	if(a[x+1][y]) ans[++cnt]={x+1,y,x,y+1,x+1,y+1},a[x+1][y]^=1,a[x][y+1]^=1,a[x+1][y+1]^=1;
	x22(x,y+1);
}void x32(int x,int y){//处理 3*2
	if(a[x][y]) ans[++cnt]={x,y,x+1,y,x+1,y+1},a[x][y]^=1,a[x+1][y]^=1,a[x+1][y+1]^=1;
	if(a[x][y+1]) ans[++cnt]={x+1,y,x,y+1,x+1,y+1},a[x+1][y]^=1,a[x][y+1]^=1,a[x+1][y+1]^=1;
	x22(x+1,y);
}void x33(int x,int y){//处理 3*3
	if(a[x][y+2]) ans[++cnt]={x,y+2,x+1,y+2,x+1,y+1},a[x][y+2]^=1,a[x+1][y+2]^=1,a[x+1][y+1]^=1;
	if(a[x][y+1]) ans[++cnt]={x,y+1,x+1,y+2,x+1,y+1},a[x][y+1]^=1,a[x+1][y+2]^=1,a[x+1][y+1]^=1;
	if(a[x][y]) ans[++cnt]={x,y,x+1,y,x+1,y+1},a[x][y]^=1,a[x+1][y]^=1,a[x+1][y+1]^=1;
	if(a[x+1][y]) ans[++cnt]={x+2,y+1,x+1,y,x+1,y+1},a[x+2][y+1]^=1,a[x+1][y]^=1,a[x+1][y+1]^=1;
	if(a[x+2][y]) ans[++cnt]={x+2,y+1,x+2,y,x+1,y+1},a[x+2][y+1]^=1,a[x+2][y]^=1,a[x+1][y+1]^=1;
	x22(x+1,y+1);
}signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t ;
	while(t--){
		cnt=0;
		cin >> n >> m ;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin >> ch ,a[i][j]=ch-'0';
		if(n & 1){
			if(m & 1){
				for(int i=1;i<=n-3;i+=2) for(int j=1;j<=m-3;j+=2) x22(i,j);
				for(int i=1;i<=n-3;i+=2) x23(i,m-2);
				for(int j=1;j<=m-3;j+=2) x32(n-2,j);
				x33(n-2,m-2);
			}else{
				for(int i=1;i<=n-3;i+=2) for(int j=1;j<=m;j+=2) x22(i,j);
				for(int j=1;j<=m;j+=2) x32(n-2,j);
			}
		}else{
			if(m & 1){//n 奇 m 偶
				for(int i=1;i<=n;i+=2) for(int j=1;j<=m-3;j+=2) x22(i,j);
				for(int i=1;i<=n;i+=2) x23(i,m-2);
			}else for(int i=1;i<=n;i+=2) for(int j=1;j<=m;j+=2) x22(i,j);//n 偶 m 偶
		}cout << cnt << "\n" ;
		for(int i=1;i<=cnt;i++) cout << ans[i].a << " " << ans[i].b << " " << ans[i].c << " " << ans[i].d << " " << ans[i].e << " " << ans[i].f << "\n" ;
	}return 0;
}
```

写了这么多就点个赞吧。

---

## 作者：灵茶山艾府 (赞：7)

本题思路比较简单，但是写起来就需要一些技巧了。

对第 $2$ 至 $n$ 行，从下往上遍历，若当前格点为 $1$，则取当前格点与上一行临近的两个格点翻转。这样可以将第 $2$ 至 $n$ 行的每个格点修改成 $0$。

前两行的思路类似，从右往左遍历直至剩下 2x2。

按照 $1$ 的个数可以把 2x2 分成五种情况，这五种情况可以按照下面的顺序从左至右转换：

```
11  10  00  11  00
11  00  11  10  00
```

也就是说，2x2 至多转换 $4$ 次即可得到全 $0$ 的结果。

所以按照上述方法，总的转换次数是不会超过 $n*m$ 的。

实现上的难度主要体现在 2x2 的转换上，我的方法是用两个数组 $p_0$ 和 $p_1$ 记录 $0$ 和 $1$ 的位置，然后来回倒腾这些位置。

AC 代码（Golang）：

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var T, n, m int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n, &m)
		a := make([][]byte, n)
		for i := range a {
			Fscan(in, &a[i])
		}

		ans := [][][]int{}
		add := func(ps [][]int) {
			ans = append(ans, ps)
			for _, p := range ps {
				a[p[0]][p[1]] ^= 1
			}
		}
		for i := n - 1; i > 1; i-- {
			for j, b := range a[i] {
				if b == '1' {
					if j+1 < m {
						add([][]int{{i, j}, {i - 1, j}, {i - 1, j + 1}})
					} else {
						add([][]int{{i, j}, {i - 1, j}, {i - 1, j - 1}})
					}
				}
			}
		}
		for j := m - 1; j > 1; j-- {
			for i := 0; i < 2; i++ {
				if a[i][j] == '1' {
					add([][]int{{i, j}, {0, j - 1}, {1, j - 1}})
				}
			}
		}

		cell := [][]int{{0, 0}, {0, 1}, {1, 0}, {1, 1}}
		var p0, p1 []int
		for i, p := range cell {
			if a[p[0]][p[1]] == '0' {
				p0 = append(p0, i)
			} else {
				p1 = append(p1, i)
			}
		}
		if len(p1) == 4 {
			ans = append(ans, [][]int{cell[p1[0]], cell[p1[1]], cell[p1[2]]})
			p0, p1 = p1[:3], p1[3:]
		}
		if len(p1) == 1 {
			ans = append(ans, [][]int{cell[p1[0]], cell[p0[0]], cell[p0[1]]})
			p1, p0 = p0[:2], append(p0[2:], p1[0])
		}
		if len(p1) == 2 {
			ans = append(ans, [][]int{cell[p1[0]], cell[p0[0]], cell[p0[1]]})
			p1 = append(p1[1:], p0...)
		}
		if len(p1) == 3 {
			ans = append(ans, [][]int{cell[p1[0]], cell[p1[1]], cell[p1[2]]})
		}

		Fprintln(out, len(ans))
		for _, ps := range ans {
			for _, p := range ps {
				Fprint(out, p[0]+1, p[1]+1, " ")
			}
			Fprintln(out)
		}
	}
}
```


---

## 作者：二gou子 (赞：6)

# 大 模 拟

~~$20min$想出了正解思路，但是代码调了$1h$~~

## 思路
其实我的思路很简单，也很容易想到。题目要求我们更改$m*n$次将所有的$1$改成$0$，然后我们又发现一共有$m*n$个点，那也就是说，我们只需要保证没一次更改都能将一个$0$改成$1$，并且不对前面已经改成$0$的数造成影响，那么就可以解决这个问题了。

首先前面的$n-2$行是不需要考虑下面一行是什么的，直接改就行，每次操作只要不将前面的$0$再改回$1$，随便操作都可以。那么思路就很简单了，只要是$1$就将以这个点为左上角的正方形操作一波，只要把这个点取反，剩下的点无所谓，因为不管怎么样最后你还是要去单独处理那一个点，所以不用管后面点的死活，只需要保证每一次操作都把一个点改成$0$即可。

然后到了$n-1$行，因为最后一行是不能单独操作的，所以要把两行并起来操作，那么就可以一列一列枚举，两个一起改，然后改到最后一个正方形，也就是以$(n-1,m-1)$为左上角坐标的正方形，因为这是最后一个正方形了，我们不能再不顾后面点的死活了，所以说要整体改。手玩之后发现，最差的情况是正方形内全部是$1$。但是即使是这样我们也可以四步解决。那也就是说，**一个内含四个点的正方形，最多需要四步解决，这仍然不违背一次至少改一个点的原则。**那么，这个题就解决了。

但是这个思路虽然非常简单，代码写起来却比较恶心。（也有可能是我太菜了）。但是作为光荣的$CSP-S 2020$选手，在经历过儒略日的洗礼后，已经脱胎换骨了。在心态经过儒略日的锤炼后，我毅然决然地选择$debug$，最终用了$1h$终于切掉了。$CSP-S$的时候$de$了$2h30min$...

## 代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
#define ll long long 
using namespace std;
ll T,n,m,ans,cnt;
bool a[1005][1005];
ll x[1000005],xx[1000005],xxx[1000005],y[1000005],yy[1000005],yyy[1000005];
int tian(int k,int x1,int y1){//取反函数，(x1,y1)是左上角坐标，k代表取反的类型（取反哪三个，具体k是多少代表哪一类不再赘述） 
	if(k==1){
		x[++ans]=x1,y[ans]=y1;
		xx[ans]=x1+1,yy[ans]=y1;
		xxx[ans]=x1,yyy[ans]=y1+1;
		
		a[x1][y1]=!a[x1][y1];
		a[x1+1][y1]=!a[x1+1][y1];
		a[x1][y1+1]=!a[x1][y1+1];
	}
	if(k==2){
		x[++ans]=x1,y[ans]=y1;
		xx[ans]=x1,yy[ans]=y1+1;
		xxx[ans]=x1+1,yyy[ans]=y1+1;
		
		a[x1][y1]=!a[x1][y1];
		a[x1][y1+1]=!a[x1][y1+1];
		a[x1+1][y1+1]=!a[x1+1][y1+1];
	}
	if(k==3){
		x[++ans]=x1,y[ans]=y1;
		xx[ans]=x1+1,yy[ans]=y1;
		xxx[ans]=x1+1,yyy[ans]=y1+1;
		
		a[x1][y1]=!a[x1][y1];
		a[x1+1][y1]=!a[x1+1][y1];
		a[x1+1][y1+1]=!a[x1+1][y1+1];
	}
	if(k==4){
		x[++ans]=x1+1,y[ans]=y1;
		xx[ans]=x1,yy[ans]=y1+1;
		xxx[ans]=x1+1,yyy[ans]=y1+1;
		
		a[x1+1][y1]=!a[x1+1][y1];
		a[x1][y1+1]=!a[x1][y1+1];
		a[x1+1][y1+1]=!a[x1+1][y1+1];
	}
}
void sum_1();
void sum_2();
void sum_3();
void sum_4();

void tepan(){
	int sum=0;
	for(int i=n-1;i<=n;i++){
		for(int j=m-1;j<=m;j++){
			if(a[i][j]==1){
				sum++;//还剩几个1需要干掉
			}
		}
	}
	if(sum==0){
		return;
	}
	if(sum==1){
		sum_1();
	}
	if(sum==2){
		sum_2();
	}
	if(sum==3){
		sum_3();
	}
	if(sum==4){
		sum_4();
	}
}

int main()
{
	cin>>T;
	while(T--){
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char c;
				cin>>c;
				if(c=='0'){
					a[i][j]=0;
				}
				else{
					a[i][j]=1;
				}
			}
		}
		for(int i=1;i<=n-2;i++){
			for(int j=1;j<=m-1;j++){
				if(a[i][j]==0){
					if(a[i][j+1]==1){
						tian(4,i,j);//特判边界，如果倒数第二列是0，但是最后一列是1，那不能将它略过，所以要特判
						continue;
					}
					else{
						continue;
					}
				}
				if(a[i][j+1]==1){
					tian(1,i,j);
				}
				else{
					tian(3,i,j);
				}
			}
		}
		
		for(int i=1;i<=m-2;i++){
			if(a[n-1][i]==0){
				if(a[n][i]==1){
					tian(4,n-1,i);
				}
				else{
					continue;
				}
			}
			else{
				if(a[n][i]==1){
					tian(1,n-1,i);
				}
				else{
					tian(2,n-1,i);
				}
			}
		}
		tepan();
		printf("%lld\n",ans);
		for(int i=1;i<=ans;i++){
			cout<<x[i]<<" "<<y[i]<<" "<<xx[i]<<" "<<yy[i]<<" "<<xxx[i]<<" "<<yyy[i]<<"\n";
		}
	}
	return 0;
}
void sum_1(){
	if(a[n-1][m-1]==1){
		tian(1,n-1,m-1);
		sum_2();
		return;
	}
	if(a[n-1][m]==1){
		tian(2,n-1,m-1);
		sum_2();
		return;
	}
	if(a[n][m-1]==1){
		tian(3,n-1,m-1);
		sum_2();
		return;
	}
	if(a[n][m]==1){
		tian(4,n-1,m-1);
		sum_2();
		return;
	}
}
void sum_2(){//自己手玩去吧。。。
	if(a[n-1][m-1]==1){
		if(a[n][m-1]==1){
			tian(2,n-1,m-1);
			sum_3();
			return;
		}
		if(a[n-1][m]==1){
			tian(3,n-1,m-1);
			sum_3();
			return;
		}
		if(a[n][m]==1){
			tian(4,n-1,m-1);
			sum_3();
			return;
		}
	}
	if(a[n][m-1]==1){
		if(a[n-1][m]==1){
			tian(2,n-1,m-1);
			sum_3();
			return;
		}
		if(a[n][m]==1){
			tian(1,n-1,m-1);
			sum_3();
			return;
		}
	}
	if(a[n-1][m]==1){
		if(a[n][m]==1){
			tian(1,n-1,m-1);
			sum_3();
			return;
		}
	}
	
	
}
void sum_3(){
	if(a[n-1][m-1]==0){
		tian(4,n-1,m-1);
		return;
	} 
	if(a[n-1][m]==0){
		tian(3,n-1,m-1);
		return;
	}
	if(a[n][m-1]==0){
		tian(2,n-1,m-1);
		return;
	}
	if(a[n][m]==0){
		tian(1,n-1,m-1);
		return;
	}
}
void sum_4(){
	tian(1,n-1,m-1);
	sum_1();
	return;
}
```

---

## 作者：DHeasy (赞：1)

$2023/6/29$：在中文句子后补充了句号。

$2023/7/6$：更改了矩阵的表达方式。

首先，看到要在 $n\times m$ 步内完成，所以平均一步要做好一个点。

其次，不能想到前 $n-2$ 行可以用如下方法解决：

-  设当前位是 $a_{i,j}$，如果 $a_{i,j}=1$，则将 $a_{i,j},a_{i+1,j-1},a_{i+1,j}$ 取反（特别的，当 $j=1$ 时，将 $a_{i,j},a_{i+1,j},a_{i+1,j+1}$ 取反），将操作加入答案。

步数一定是小于等于 $(n-2)\times m$ 的，不会超。

正确性等会证明。

#### 为什么是前 $n-2$ 行，不是 $n-1$ 吗？

因为最后一行不能单独做（第 $n$ 行下面没有行了），所以要让第 $n-1$ 行，第 $n$ 行配合的做。

------------

#### 接下来就是思考如何做最后两行

自己在草稿纸上画一画，会发现一个 $2\times 2$ 的矩阵无论初始状态是这样的，都可以消除。

所以，我们可以将最后两行分割成 $2\times 2$ 的矩阵，分开来做。

但是，如果 $m$ 是奇数，则会剩下一列，怎么办呢？其实很简单，我们把这一列单独拿出来做。

不妨做第一列，则如果 $a_{n-1,1}$（第 $n-1$ 行第 $1$ 列）为 $1$，将 $a_{n-1,1},a_{n-1,2},a_{n,2}$ 取反，将操作加入答案。

同理可做 $a_{n,1}$。

接下来，就把矩阵分成若干个 $2\times 2$ 的小矩阵，易得到当矩阵为：

$$\begin{vmatrix}
   1 & 1 \\
   1 & 1
\end{vmatrix}$$

时所需步数最多，为 $4$，发现也不会超。

------------

#### 解法的正确性证明

首先，易得把剩下矩阵分成若干个 $2\times 2$ 的小矩阵是可行的（自己在草稿纸上画一画，步数证明上文也有讲）。

其次，单独做一列也是可行的，因为改变后面的小矩阵仍然可以做。

最后同理，做前 $n-2$ 行时也不会造成什么后果。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,ans,a[10010][7];
char c[110][110];
void left_up(int i){
    ans++;
    a[ans][1]=n-1;
    a[ans][2]=i;
    a[ans][3]=n-1;
    a[ans][4]=i+1;
    a[ans][5]=n;
    a[ans][6]=i;
}
void left_down(int i){
    ans++;
    a[ans][1]=n-1;
    a[ans][2]=i;
    a[ans][3]=n;
    a[ans][4]=i;
    a[ans][5]=n;
    a[ans][6]=i+1;
}
void right_up(int i){
    ans++;
    a[ans][1]=n-1;
    a[ans][2]=i;
    a[ans][3]=n-1;
    a[ans][4]=i+1;
    a[ans][5]=n;
    a[ans][6]=i+1;
}
void right_down(int i){
    ans++;
    a[ans][1]=n-1;
    a[ans][2]=i+1;
    a[ans][3]=n;
    a[ans][4]=i;
    a[ans][5]=n;
    a[ans][6]=i+1;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        ans=0;
        for(int i=1;i<=n;i++) scanf("%s",c[i]+1);
        for(int i=1;i<=n-2;i++){
            if(c[i][1]=='1'){
                ans++;
                a[ans][1]=i;
                a[ans][2]=1;
                a[ans][3]=i+1;
                a[ans][4]=1;
                a[ans][5]=i+1;
                a[ans][6]=2;
                if(c[i+1][1]=='0') c[i+1][1]='1';
                else c[i+1][1]='0';
                if(c[i+1][2]=='0') c[i+1][2]='1';
                else c[i+1][2]='0';
            }
            for(int j=2;j<=m;j++){
                if(c[i][j]=='1'){
                    ans++;
                    a[ans][1]=i;
                    a[ans][2]=j;
                    a[ans][3]=i+1;
                    a[ans][4]=j;
                    a[ans][5]=i+1;
                    a[ans][6]=j-1;
                    if(c[i+1][j]=='0') c[i+1][j]='1';
                    else c[i+1][j]='0';
                    if(c[i+1][j-1]=='0') c[i+1][j-1]='1';
                    else c[i+1][j-1]='0';
                }
            }
        }
        if(m&1){
            if(c[n-1][1]=='1'){
                ans++;
                a[ans][1]=n-1;
                a[ans][2]=1;
                a[ans][3]=n-1;
                a[ans][4]=2;
                a[ans][5]=n;
                a[ans][6]=2;
                if(c[n-1][2]=='0') c[n-1][2]='1';
                else c[n-1][2]='0';
                if(c[n][2]=='0') c[n][2]='1';
                else c[n][2]='0';
            }
            if(c[n][1]=='1'){
                ans++;
                a[ans][1]=n;
                a[ans][2]=1;
                a[ans][3]=n-1;
                a[ans][4]=2;
                a[ans][5]=n;
                a[ans][6]=2;
                if(c[n-1][2]=='0') c[n-1][2]='1';
                else c[n-1][2]='0';
                if(c[n][2]=='0') c[n][2]='1';
                else c[n][2]='0';
            }
            for(int i=2;i<m;i+=2){
                if(c[n-1][i]=='1'&&c[n-1][i+1]=='0'&&c[n][i]=='0'&&c[n][i+1]=='0'){
                    left_up(i);
                    right_up(i);
                    left_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='1'&&c[n][i]=='0'&&c[n][i+1]=='0'){
                    right_up(i);
                    left_up(i);
                    right_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='0'&&c[n][i]=='1'&&c[n][i+1]=='0'){
                    left_down(i);
                    left_up(i);
                    right_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='0'&&c[n][i]=='0'&&c[n][i+1]=='1'){
                    right_down(i);
                    right_up(i);
                    left_down(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='1'&&c[n][i]=='0'&&c[n][i+1]=='0'){
                    left_down(i);
                    right_down(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='0'&&c[n][i]=='1'&&c[n][i+1]=='0'){
                    right_down(i);
                    right_up(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='0'&&c[n][i]=='0'&&c[n][i+1]=='1'){
                    left_up(i);
                    right_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='1'&&c[n][i]=='1'&&c[n][i+1]=='0'){
                    right_up(i);
                    left_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='1'&&c[n][i]=='0'&&c[n][i+1]=='1'){
                    left_up(i);
                    left_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='0'&&c[n][i]=='1'&&c[n][i+1]=='1'){
                    right_up(i);
                    left_up(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='1'&&c[n][i]=='1'&&c[n][i+1]=='0'){
                    left_up(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='1'&&c[n][i]=='0'&&c[n][i+1]=='1'){
                    right_up(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='0'&&c[n][i]=='1'&&c[n][i+1]=='1'){
                    left_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='1'&&c[n][i]=='1'&&c[n][i+1]=='1'){
                    right_down(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='1'&&c[n][i]=='1'&&c[n][i+1]=='1'){
                    left_up(i);
                    left_down(i);
                    right_up(i);
                    right_down(i);
                }
            }
        }
        else{
			for(int i=1;i<m;i+=2){
                if(c[n-1][i]=='1'&&c[n-1][i+1]=='0'&&c[n][i]=='0'&&c[n][i+1]=='0'){
                    left_up(i);
                    right_up(i);
                    left_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='1'&&c[n][i]=='0'&&c[n][i+1]=='0'){
                    right_up(i);
                    left_up(i);
                    right_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='0'&&c[n][i]=='1'&&c[n][i+1]=='0'){
                    left_down(i);
                    left_up(i);
                    right_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='0'&&c[n][i]=='0'&&c[n][i+1]=='1'){
                    right_down(i);
                    right_up(i);
                    left_down(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='1'&&c[n][i]=='0'&&c[n][i+1]=='0'){
                    left_down(i);
                    right_down(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='0'&&c[n][i]=='1'&&c[n][i+1]=='0'){
                    right_down(i);
                    right_up(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='0'&&c[n][i]=='0'&&c[n][i+1]=='1'){
                    left_up(i);
                    right_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='1'&&c[n][i]=='1'&&c[n][i+1]=='0'){
                    right_up(i);
                    left_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='1'&&c[n][i]=='0'&&c[n][i+1]=='1'){
                    left_up(i);
                    left_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='0'&&c[n][i]=='1'&&c[n][i+1]=='1'){
                    right_up(i);
                    left_up(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='1'&&c[n][i]=='1'&&c[n][i+1]=='0'){
                    left_up(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='1'&&c[n][i]=='0'&&c[n][i+1]=='1'){
                    right_up(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='0'&&c[n][i]=='1'&&c[n][i+1]=='1'){
                    left_down(i);
                }
                else if(c[n-1][i]=='0'&&c[n-1][i+1]=='1'&&c[n][i]=='1'&&c[n][i+1]=='1'){
                    right_down(i);
                }
                else if(c[n-1][i]=='1'&&c[n-1][i+1]=='1'&&c[n][i]=='1'&&c[n][i+1]=='1'){
                    left_up(i);
                    left_down(i);
                    right_up(i);
                    right_down(i);
                }
            }
		} 
        printf("%d\n",ans);
        for(int i=1;i<=ans;i++){
            for(int j=1;j<=6;j++) printf("%d ",a[i][j]);
            putchar('\n');
        }
    }
    return 0;
}
```


---

## 作者：lizhous (赞：1)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1439A2)

[本家传送门](https://codeforces.com/problemset/problem/1439/A2)

杂题选讲遇到的好玩构造题！

## 分析

这种题一看就是~~熵增题~~手模题，我们就先模一下 $2\times 2$ 的矩阵。我们首先发现把一个矩阵旋转后他的操作方法是本质一样的，所以可以不考虑旋转的情况，这样大大减少了手模量。本质不同的 $2\times 2$ 的矩阵数量只有 $6$ 个，我们只关心它们之间的转换。下面给出手模过程：

![](https://cdn.luogu.com.cn/upload/image_hosting/36imv51y.png)

我们惊讶的发现，对于一个 $2\times 2$ 的矩阵，最多执行四次操作。均摊下来最多一个点一次，也就满足了题目的要求。

我们把这些操作铺上去就解决的偶数的情况。

考虑奇数情况。行列本质一样，这里只考虑行。我们发现会多一行。这一行里有若干 $1$，我们发现对这一行操作时影响非本行格子是不会影响答案的，所以我们可以用若干上二下一的操作把所有本行格子变成 $0$。均摊也是一个格子最多一次。

至此，本题思路明确，接下来是~~喜闻乐见的~~调代码时间。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,T,len;
bool a[1001][1001],b[5][5];
struct fun
{
	int x[4],y[4];
}ans[1000001];
void wok(int x,int y)
{
	x--;
	y--;
	int cnt=b[1][1]+b[1][2]+b[2][1]+b[2][2]; //采用递推处理
	if(cnt==4)
	{
		int ln=0;
		len++;
		ans[len].x[++ln]=x+1;
		ans[len].y[ln]=y+1;
		
		ans[len].x[++ln]=x+2;
		ans[len].y[ln]=y+1;
		
		ans[len].x[++ln]=x+1;
		ans[len].y[ln]=y+2;
		
		b[1][1]^=1;
		b[1][2]^=1;
		b[2][1]^=1;
		cnt=1;
	} //四个的情况，转化为一个
	if(cnt==1)
	{
		int ln=0;
		len++;
		if(b[1][1])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+2;
			
			b[1][1]^=1;
			b[2][1]^=1;
			b[2][2]^=1;
			cnt=2;
		}
		else if(b[2][2])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+2;
			
			b[1][1]^=1;
			b[2][1]^=1;
			b[2][2]^=1;
			cnt=2;
		}
		else if(b[1][2])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+2;
			
			b[1][1]^=1;
			b[1][2]^=1;
			b[2][1]^=1;
			cnt=2;
		}
		else if(b[2][1])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+2;
			
			b[1][1]^=1;
			b[1][2]^=1;
			b[2][1]^=1;
			cnt=2;
		}
	} //一个的情况，转化为两个
	if(cnt==2)
	{
		int ln=0;
		len++;
		if(b[1][1]&&b[1][2])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+2;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
			
			b[1][1]^=1;
			b[2][2]^=1;
			b[2][1]^=1;
			cnt=3;
		}
		else if(b[1][1]&&b[2][1])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+2;
			
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+2;
			
			b[1][1]^=1;
			b[2][2]^=1;
			b[1][2]^=1;
			cnt=3;
		}
		else if(b[2][2]&&b[2][1])
		{
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+2;
			
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+2;
			
			b[1][1]^=1;
			b[2][2]^=1;
			b[1][2]^=1;
			cnt=3;
		}
		else if(b[2][2]&&b[1][2])
		{
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+2;
			
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
			
			b[1][1]^=1;
			b[2][2]^=1;
			b[2][1]^=1;
			cnt=3;
		}
		else if(b[1][1]&&b[2][2])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+2;
			
			b[1][1]^=1;
			b[2][1]^=1;
			b[1][2]^=1;
			cnt=3;
		}
		else if(b[1][2]&&b[2][1])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+2;
			
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
			
			b[2][1]^=1;
			b[2][2]^=1;
			b[1][1]^=1;
			cnt=3;
		}
	} //四个的情况，转化为三个
	if(cnt==3)
	{
		int ln=0;
		len++;
		if(b[1][1])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+1;
		}
		if(b[2][1])
		{
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+1;
		}
		if(b[1][2])
		{
			ans[len].x[++ln]=x+1;
			ans[len].y[ln]=y+2;
		}
		if(b[2][2])
		{
			ans[len].x[++ln]=x+2;
			ans[len].y[ln]=y+2;
		}
	} //优雅
}
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		len=0;
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)
		{
			for(int z=1;z<=m;z++)
			{
				char didi;
				scanf(" %c",&didi);
				didi-='0';
				a[i][z]=(bool)didi;
			}
		} //输入
		if(n%2==1)
		{
			for(int i=1;i<=m;i++)
			{
				if(a[n][i])
				{
					ans[++len].x[1]=n;
					ans[len].y[1]=i;
					a[n][i]^=1;
					
					ans[len].x[2]=n-1;
					ans[len].y[2]=i;
					a[n-1][i]^=1;
					
					if(i==1)
					{
						ans[len].x[3]=n-1;
						ans[len].y[3]=i+1;
						a[n-1][i+1]^=1;
					}
					else
					{
						ans[len].x[3]=n-1;
						ans[len].y[3]=i-1;
						a[n-1][i-1]^=1;
					}
				}
			}
		} //奇数特殊处理
		if(m%2==1)
		{
			for(int i=1;i<=n;i++)
			{
				if(a[i][m])
				{
					ans[++len].x[1]=i;
					ans[len].y[1]=m;
					a[i][m]^=1;
					
					ans[len].x[2]=i;
					ans[len].y[2]=m-1;
					a[i][m-1]^=1;
					
					if(i==1)
					{
						ans[len].x[3]=i+1;
						ans[len].y[3]=m-1;
						a[i+1][m-1]^=1;
					}
					else
					{
						ans[len].x[3]=i-1;
						ans[len].y[3]=m-1;
						a[i-1][m-1]^=1;
					}
				}
			}
		} //同理
		for(int i=1;i<n;i+=2)
		{
			for(int z=1;z<m;z+=2)
			{
				b[1][1]=a[i][z];
				b[1][2]=a[i][z+1];
				b[2][1]=a[i+1][z];
				b[2][2]=a[i+1][z+1];
				wok(i,z); //铺上去
			}
		}
		printf("%lld\n",len);
		for(int i=1;i<=len;i++)
		{
			printf("%lld %lld %lld %lld %lld %lld\n",ans[i].x[1],ans[i].y[1],ans[i].x[2],ans[i].y[2],ans[i].x[3],ans[i].y[3]);
		}
	}
}
```

---

## 作者：Computer1828 (赞：1)

对于弱化版，我们很快能想到枚举每一个 $2\times 2$ 的正方形然后大模拟。我们规定对于一个 $2\times 2$ 的正方形，它每一块的编号如下，它对应的数字为其小写：

![](https://cdn.luogu.com.cn/upload/image_hosting/2q7mqb1d.png)

对于每一块，都有两种可能：$0$ 或 $1$，那就是 $2^4 = 16$ 种情况。

然后再规定一下每一种情况对应的编号，这可以方便进一步的判断。这里规定：一种情况的编号为 $num = 8a+4c+2b+d+1$。

当 $num = $：

1. 无操作。
2. $(ACD),(ABD),(BCD)$。
3. 同 $2$。
4. $(ABC),(ACD)$。
5. 同 $2$。
6. 同 $4$。
7. $(ACD),(ABD)$。
8. $(BCD)$。

9~15. 同 $2,4,7,8$。

16. $(ABC)$，然后同 $2$。

然后你就通过了弱化版。

考虑优化：首先不用枚举所有的正方形，可以想象一下把一堆正方形卡片丢到一个 $n\times m$ 的盒子，然后只留下最底层的卡片。也就是说，我并不需要枚举每一个正方形，我可以跳着枚举。

然后发现一个问题，对于 $n$ 或 $m$ 为奇数的情况，边角会有空隙。我们可以对其单独处理，单独更新；对于坐标 $(n,m)$ 的角块，注意要提到最前面单独处理。

代码过长，所以放在了[剪贴板](https://www.luogu.com.cn/paste/op5wzu92)

---

## 作者：TEoS (赞：1)

本文同步发表在 [我的blog](https://www.cnblogs.com/TEoS/p/14004239.html)


------------

**题意分析**

给出一个 $n×m$ 的只由 $0,1$ 构成的矩阵，每次可以将一个 $2×2$ 的子矩阵中的 $3$ 个数取反。要求将整个矩阵的所有元素变为 $0$ ，并且操作次数不能超过 $nm$ 次。要求给出操作次数和具体方案。

**思路分析**

由于每次只能修改一个 $2×2$ 的子矩阵中的 $3$ 个数，想到考虑每个 $2×2$ 的子矩阵的情况，尝试把每个 $2×2$ 的子矩阵单独处理，看看合不合法。

显然可以根据 $1$ 的个数划分为五种情况，对每种情况分别考虑：

###### 情况一： $0$ 个 $1$

显然不用处理，需要 $0$ 次操作。

###### 情况二：  $3$ 个 $1$

将 $3$ 个 $1$ 取反即可，需要 $1$ 次操作。

###### 情况三： $2$ 个 $1$ 

将 $2$ 个 $0$ 和 $1$ 个 $1$ 取反，可以变为情况二，接着处理，需要 $2$ 次操作。

###### 情况四： $1$ 个 $1$

将 $2$ 个 $0$ 和 $1$ 个 $1$ 取反，可以变为情况三，接着处理，需要 $3$ 次操作。

###### 情况五： $4$ 个 $1$

将 $3$ 个 $1$ 取反，可以变为情况一，接着处理，需要 $4$ 次操作。

可以发现，所有情况最多只需要 $4$ 次操作，刚好与子矩阵的元素数目相等，因此一定可以满足操作次数不大于 $nm$ 。

若 $n$ 或 $m$ 为奇数，不能刚好划分为 $2×2$ 的子矩阵，就先把一行全部变成 $0$ ，然后再处理剩下的即可。注意后面的处理不能影响到前面已经处理过的元素。

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int N=200,M=3e4+100;
int T,n,m,ans;
int dx[4]={0,1,0,1},dy[4]={0,0,1,1};
int x1[M],x2[M],x3[M],y1[M],y2[M],y3[M],a[N][N];
string s;
int ano(int x)
{
	return ((x-1)^1)+1;
}//找相邻的数，其中奇数较小，偶数较大
void solve1(int i,int j)
{
	ans++;
	for(int k=0,x=i+dx[k],y=j+dy[k];k<4;k++,x=i+dx[k],y=j+dy[k])
		if(!a[x][y])
		{
			if(!x1[ans])
				a[x][y]=1,x1[ans]=x,y1[ans]=y;
			else
				if(!x2[ans])
					a[x][y]=1,x2[ans]=x,y2[ans]=y;//取反 2 个 0
		}
		else
			if(!x3[ans])
				a[x][y]=0,x3[ans]=x,y3[ans]=y;//取反 1 个 1
}//取反 2 个 0 和 1 个 1
void solve2(int i,int j)
{
	ans++;
	for(int k=0,x=i+dx[k],y=j+dy[k];k<4;k++,x=i+dx[k],y=j+dy[k])
		if(a[x][y])
			if(!x1[ans])
				a[x][y]=0,x1[ans]=x,y1[ans]=y;
			else
				if(!x2[ans])
					a[x][y]=0,x2[ans]=x,y2[ans]=y;
				else
					if(!x3[ans])
						a[x][y]=0,x3[ans]=x,y3[ans]=y;
}//取反 3 个 1
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);ans=0;
		for(int i=1;i<=n*m;i++)
			x1[i]=x2[i]=x3[i]=y1[i]=y2[i]=y3[i]=0;
		for(int i=1;i<=n;i++)
		{
			cin>>s;
			for(int j=1;j<=m;j++)
				a[i][j]=s[j-1]-'0';
		}
		if(n&1)// n 为奇数，处理第 n 行
			for(int i=1;i<=m;i++)
				if(a[n][i])
					a[n][i]=0,a[n-1][i]^=1,a[n-1][i==m?i-1:i+1]^=1,x1[++ans]=n,x2[ans]=n-1,x3[ans]=n-1,y1[ans]=i,y2[ans]=i,y3[ans]=i==m?i-1:i+1;
		if(m&1)// m 为奇数，处理第 m 列
			for(int i=1;i<=n;i++)
				if(a[i][m])
					if(i<m)
						a[i][m]=0,a[i][m-1]^=1,a[i==1?i+1:i-1][m-1]^=1,x1[++ans]=i,x2[ans]=i,x3[ans]=i==1?i+1:i-1,y1[ans]=m,y2[ans]=m-1,y3[ans]=m-1;
					else
						a[n][m-1]=0,a[n-1][m]^=1,a[n-1][m-1]^=1,x1[++ans]=n,x2[ans]=n-1,x3[ans]=n-1,y1[ans]=m,y2[ans]=m,y3[ans]=m-1;
		for(int i=1;i<=n;i+=2)
			for(int j=1;j<=m;j+=2)
			{
				if(a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1]==4)
					solve2(i,j);
				if(a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1]==1)
					solve1(i,j);
				if(a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1]==2)
					solve1(i,j);
				if(a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1]==3)
					solve2(i,j);
			}//划分处理，根据处理先后按顺序
		printf("%d\n",ans);
		for(int i=1;i<=ans;i++)
			printf("%d %d %d %d %d %d\n",x1[i],y1[i],x2[i],y2[i],x3[i],y3[i]);
	}
	return 0;
}
```

~~我甚至没想出 $3nm$ 的怎么做~~

---

## 作者：Hoks (赞：0)

## 前言
难得写了个 $1900$，感谢 [sgl654321](https://www.luogu.com.cn/user/525374) 推的题。

思路还算比较简单，实现好像也不是很难？

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
首先发现我们一次操作会对 $0$ 数量的影响是 $+3,+1,-1,-3$，因为这里面有 $-1$，所以是肯定可以清场的。

手玩会，发现整个矩阵的东西有点太多了。

虽然我们貌似不知道该怎么把一个矩阵的东西清空，但是可以无脑把 $1$ 往右下移。

具体的，先对左边的 $m-2$ 列上的点为左上角无脑把 $1$ 向右移。

然后以 $m-1$ 这列上的点为左上角无脑的把 $1$ 往下面移。

这样最后还有 $1$ 的就剩下一个 $2\times 2$ 的矩阵。

手玩一下就可以得到我们可以以这样的顺序让 $1$ 的数量变动：$4\rightarrow1\rightarrow2\rightarrow3\rightarrow0$。

按思路模拟即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=100+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m;char s[N][N];vector<pair<int,int>>a[4];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void sol()
{
    vector<pair<int,int>>b[2];
    for(int i=n-1;i<=n;i++)
        for(int j=m-1;j<=m;j++)
            b[s[i][j]-'0'].push_back({i,j});
    if(b[1].size()==4)
    {
        for(int i=0;i<3;i++) a[i].emplace_back(b[1][i]),b[0].emplace_back(b[1][i]);
        b[1].erase(b[1].begin(),b[1].end()-1);
    }
    if(b[1].size()==1)
    {
        a[2].emplace_back(b[1][0]);b[0].emplace_back(b[1][0]);b[1].clear();
        for(int i=0;i<2;i++) a[i].emplace_back(b[0][i]),b[1].emplace_back(b[0][i]);
        b[0].erase(b[0].begin(),b[0].end()-2);
    }
    if(b[1].size()==2)
    {
        a[2].emplace_back(b[1][0]);b[0].emplace_back(b[1][0]);b[1].erase(b[1].begin());
        for(int i=0;i<2;i++) a[i].emplace_back(b[0][i]),b[1].emplace_back(b[0][i]);
        b[0].erase(b[0].begin(),b[0].end()-2);
    }
    if(b[1].size()==3) for(int i=0;i<3;i++) a[i].emplace_back(b[1][i]);
}
inline void solve()
{
    n=read(),m=read();for(int i=1,l=0;i<=n;i++) rd(s[i],l),l=0;a[0].clear(),a[1].clear(),a[2].clear();
    for(int i=1;i<n;i++)
        for(int j=1;j<m-1;j++)
        {
            if(s[i][j]=='0'&&s[i+1][j]=='0') continue;int ss=3;
            if(s[i][j]=='1') a[--ss].push_back({i,j}),s[i][j]='0';
            if(s[i+1][j]=='1') a[--ss].push_back({i+1,j}),s[i+1][j]='0';
            if(ss) a[--ss].push_back({i,j+1}),s[i][j+1]^=1;
            if(ss) a[--ss].push_back({i+1,j+1}),s[i+1][j+1]^=1;
        }
    for(int i=1;i<n-1;i++)
    {
        if(s[i][m-1]=='0'&&s[i][m]=='0') continue;int ss=3;
        if(s[i][m-1]=='1') a[--ss].push_back({i,m-1}),s[i][m-1]='0';
        if(s[i][m]=='1') a[--ss].push_back({i,m}),s[i][m]='0';
        if(ss) a[--ss].push_back({i+1,m-1}),s[i+1][m-1]^=1;
        if(ss) a[--ss].push_back({i+1,m}),s[i+1][m]^=1;
    }sol();print(a[0].size());put('\n');
    for(int i=0;i<a[0].size();i++,put('\n')) for(int j=0;j<3;j++) print(a[j][i].first),put(' '),print(a[j][i].second),put(' ');
}
signed main()
{
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：sgl654321 (赞：0)

## 题目大意
给定一个 $n\times m$ 的 $0/1$ 矩阵，每次操作可以选出一个 L 形的三个位置，把 $0$ 变成 $1$，把 $1$ 变成 $0$。在 $n\times m$ 次操作之内把所有位置都变成 $0$。
## 解题思路
由于是 $n\times m$ 次操作，平均下来就是每个位置只有一次操作机会。我们考虑把那些零散的 $1$ 都尽可能聚集到右下角去。

我们遍历 $i\in[1,n-2],j\in[1,m-1]$。如果 $a_{i,j} = 1$，那么就进行操作 $\{a_{i,j},a_{i+1,j},a_{i,j+1}\}$。这样我们只影响到了 $(i,j)$ 下面和右面的位置，已经处理好的左边和上边都不受影响。

那么 $i\in[1,n-2],j=m$ 怎么办呢？如果 $a_{i,m}=1$，我们可以在处理下一行前，先进行操作 $\{a_{i,m},a_{i+1,m},a_{i+1,m-1}\}$。这样对处理过的那些点也是没有影响的。

接下来是 $i\in\{n-1,n\},j\in[1,m-2]$。$i=n-1$ 时，如果 $a_{n-1,j} = 1$，显然操作 $\{a_{n-1,j},a_{n-1,j+1},a_{n,j}\}$。如果 $a_{n,j} =1$，则是操作 $\{a_{n,j},a_{n,j+1},a_{n-1,j+1}\}$。

最终，我们就把除了最右下角的四个点全都变成 $0$ 了，最多操作次数为 $n\times m -4$。还有 $4$ 次机会。

我们对一个 $2\times 2$ 的一个小正方形再次进行讨论。

- 如果其中一个 $1$ 也没有那直接结束了。

- 如果其中有三个 $1$，一次搞定。

- 如果其中有两个 $1$，我们先选出其中有两个 $0$，一个 $1$ 的这个 L 形进行操作。这样就化成三个 $1$ 的情况了。总共要用上两次搞定。

- 如果其中有一个 $1$，我们选出包含这个 $1$ 的一个 L 形，然后就化成有两个 $1$ 的情况了。总共用上三次搞定。

- 如果全是 $1$，那么我们随便选一个 L 形操作，就变成只有一个 $1$ 的情况了。总共用上四次搞定。

经过上述分析，我们知道一个 $2\times2$ 的正方形，$4$ 次就一定可以搞定。

因此本题就在 $n\times m$ 次操作之内解决了，通过了两个版本。

### 参考代码
这题毕竟是个小模拟，码量还是有一点的。

- 用 `change` 这个封装函数来实现位置上的取反并记录答案。

- 用 `work` 这个函数化归思想（即使用递归）来处理最后的 $2\times 2$ 正方形。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct oper{
	ll xa, ya, xb, yb, xc, yc;
} ans[10010];
ll tt, n, m, a[110][110], tot, num;
char ch;
void change(ll xa, ll ya, ll xb, ll yb, ll xc, ll yc){
	ans[++tot] = oper{xa, ya, xb, yb, xc, yc};
	a[xa][ya] = 1 - a[xa][ya]; a[xb][yb] = 1 - a[xb][yb]; a[xc][yc] = 1 - a[xc][yc];
}
void work(ll x, ll y){
	if(a[x][y] == 0 && a[x + 1][y] == 0 && a[x][y + 1] == 0 && a[x + 1][y + 1] == 0) return;
	ll num = a[x][y] + a[x + 1][y] + a[x][y + 1] + a[x + 1][y + 1];
	if(num == 3){
		if(a[x][y] == 0) change(x + 1, y, x, y + 1, x + 1, y + 1);
		else if(a[x][y + 1] == 0) change(x, y, x + 1, y, x + 1, y + 1);
		else if(a[x + 1][y] == 0) change(x, y, x, y + 1, x + 1, y + 1);
		else if(a[x + 1][y + 1] == 0) change(x, y, x, y + 1, x + 1, y);
		return;
	} 
	if(num == 2){
		if(a[x][y] == 0 && a[x + 1][y] == 0) change(x, y, x + 1, y, x, y + 1), work(x, y);
		else if(a[x][y] == 0 && a[x][y + 1] == 0) change(x, y, x + 1, y, x, y + 1), work(x, y); 
		else if(a[x][y] == 0 && a[x + 1][y + 1] == 0) change(x, y, x + 1, y, x + 1, y + 1), work(x, y); 
		else if(a[x + 1][y] == 0 && a[x][y + 1] == 0) change(x, y, x + 1, y, x, y + 1), work(x, y); 
		else if(a[x + 1][y] == 0 && a[x + 1][y + 1] == 0) change(x, y, x + 1, y, x + 1, y + 1), work(x, y); 
		else if(a[x][y + 1] == 0 && a[x + 1][y + 1] == 0) change(x, y, x, y + 1, x + 1, y + 1), work(x, y); 
	}
	if(num == 1){
		if(a[x][y] == 1) change(x, y, x, y + 1, x + 1, y + 1), work(x, y);
		else if(a[x][y + 1] == 1) change(x, y, x, y + 1, x + 1, y + 1), work(x, y);
		else if(a[x + 1][y] == 1) change(x, y, x + 1, y, x + 1, y + 1), work(x, y);
		else if(a[x + 1][y + 1] == 1) change(x, y, x, y + 1, x + 1, y + 1), work(x, y);
	} 
	if(num == 4){
		change(x, y, x + 1, y, x, y + 1); work(x, y);
	}

}
void solve(){
	cin >> n >> m; tot = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) 
			cin >> ch, a[i][j] = ch - '0';
	for(int i = 1; i <= n - 2; i++){
		for(int j = 1; j <= m - 1; j++)
			if(a[i][j] == 1) change(i, j, i + 1, j, i, j + 1);
		if(a[i][m] == 1) change(i, m, i + 1, m - 1, i + 1, m);
	}
	for(int j = 1; j <= m - 2; j++){
		if(a[n - 1][j] == 1) change(n - 1, j, n - 1, j + 1, n, j + 1);
		if(a[n][j] == 1) change(n, j, n - 1, j + 1, n, j + 1);
	}
	work(n - 1, m - 1);
	cout << tot << endl;
	for(int i = 1; i <= tot; i++)
		cout << ans[i].xa << ' ' << ans[i].ya << ' ' << ans[i].xb << ' ' <<ans[i].yb << ' '
		<< ans[i].xc << ' ' <<ans[i].yc <<endl;  
}
int main(){
	cin >> tt; while(tt--) solve();
	return 0;
}

```

---

## 作者：james1BadCreeper (赞：0)

一个比较方便实现的思路。

由于有解，因此我们可以在 $n,m\le 2$ 的时候直接爆搜出答案，我们现在只需要将问题降低规模。对于前 $n-2$ 行，一个数如果是 $1$，那么就对它自己，和它下一行的连着它的两个数操作，就可以将其转化成 $0$。

接下来还剩下两行 $m$ 列，在将底下那个东西转过来再做一遍上面的东西，最后就只剩一个 $2\times 2$ 的正方形，暴力即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

int n, m, dfs_over; 
char a[105][105]; 
struct Node {
    int a, b, c, d, e, f; 
}; 
vector<Node> ans; 

void dfs(int x, vector<Node> li) {
    if (dfs_over) return; 
    bool flg = 1; 
    for (int i = n - 1; i <= n && flg; ++i) for (int j = m - 1; j <= m; ++j)
        if (a[i][j] == 1) { flg = 0; break; }
    if (flg) {
        dfs_over = 1; 
        for (auto it : li) ans.push_back(it); 
        return; 
    }
    if (x > 4) return; 
    for (int i = n - 1; i <= n; ++i) for (int j = m - 1; j <= m; ++j) {
        int arr[7], tot = 0; 
        for (int x = n - 1; x <= n; ++x) for (int y = m - 1; y <= m; ++y)
            if (x != i || y != j) arr[++tot] = x, arr[++tot] = y, a[x][y] ^= 1; 
        li.push_back({arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]}); 
        dfs(x + 1, li); 
        for (int x = n - 1; x <= n; ++x) for (int y = m - 1; y <= m; ++y)
            if (x != i || y != j) a[x][y] ^= 1; 
        li.pop_back(); 
    }
}

void solve(void) {
    cin >> n >> m; 
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] + 1; 
        for (int j = 1; j <= m; ++j)
            a[i][j] -= '0'; 
    }
    ans.clear(); 
    for (int i = 1; i <= n - 2; ++i) for (int j = 1; j <= m; ++j)
        if (a[i][j] == 1) {
            a[i][j] ^= 1; a[i + 1][j] ^= 1; 
            if (j == m) ans.push_back({i, j, i + 1, j, i + 1, j - 1}), a[i + 1][j - 1] ^= 1; 
            else ans.push_back({i, j, i + 1, j, i + 1, j + 1}), a[i + 1][j + 1] ^= 1; 
        }
    for (int j = 1; j <= m - 2; ++j) for (int i = n - 1; i <= n; ++i)
        if (a[i][j] == 1) {
            a[i][j] ^= 1; 
            a[i][j + 1] ^= 1; 
            if (i == n - 1) ans.push_back({i, j, i, j + 1, i + 1, j + 1}), a[i + 1][j + 1] ^= 1; 
            else ans.push_back({i, j, i, j + 1, i - 1, j + 1}), a[i - 1][j + 1] ^= 1; 
        }
    // for (int i = 1; i <= n; ++i, cout << "\n")
        // for (int j = 1; j <= m; ++j)
            // cout << int(a[i][j]); 
    // for (auto it : ans) cout << it.a << " " << it.b << " " << it.c << " " << it.d << " " << it.e << " " << it.f << "\n"; 
    dfs_over = 0; 
    dfs(1, vector<Node>()); 
    cout << ans.size() << "\n"; 
    for (auto it : ans) cout << it.a << " " << it.b << " " << it.c << " " << it.d << " " << it.e << " " << it.f << "\n"; 
}

int main(void) {
    ios::sync_with_stdio(0); 
    int T = 1; cin >> T; 
    while (T--) solve();
    return 0;
}
```

---

## 作者：Schi2oid (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1439A2)
## 题意
给定一个 $n\times m$ 的 $01$ 矩阵，每次操作可以将某个 $2\times2$ 的矩阵内的 $3$ 个数取反，请在 $n\times m$ 步内将矩阵变为全 $0$。
## 初步分析
让我们先来想 $2\times2$ 的矩形。现在让我们来定义四种操作：
```cpp
┌：对于左上，右上，左下格子进行操作

┐：对于左上，右上，右下格子进行操作

└：对于左上，左下，右下格子进行操作

┘：对于右上，左下，右下格子进行操作
```
那么接下来，让我来分别给出对于 $2\times2$ 的格子中 $16$ 种情况的解答：
```cpp
0 0
0 0：不进行操作，步数0。

0 0
0 1：┘，└，┐。步数3。

0 0
1 1：┐，┌。步数2。

1 0
0 1：┌，┘。步数2。

0 1
1 1：┘。步数1。

1 1
1 1：┘，┌，└，┐。步数4。
```
其余情况都能与上述情况中某一种同理，最多操作 $4$ 次。那么，对于 $n\times m$ 矩形中任意的 $2\times2$ 矩形都进行一次归零操作，最多的总操作步数将达到~~惊人的~~ $4(n-1)(m-1)$ 。
## 进一步分析
步数如此爆炸，根本原因出于重叠问题。对于几乎每一个格子，它都属于 $4$ 个 $2\times2$ 的矩形。也就是说，我们对它操作了 $4$ 次。那么，能不能用 $2\times2$ 的矩形不重叠地覆盖 $n\times m$ 呢？显然，对于 $n$ 与 $m$ 都为偶数的情况，我们是可以做到不重叠的。此时最大步数为 $nm$ 。但是对于 $n$ 和 $m$ 有奇数的情况时，我们将直接爆炸。这个时候，要想不重叠，我们需要去处理 $2\times3$ 、$3\times2$ 、$3\times3$ 的矩形~~们~~。

为啥这么说呢？上图。

对于 $n$ 奇 $m$ 偶的情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/c6r8ohy8.png)

对于 $n$ 偶 $m$ 奇的情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/vxm2x128.png)

对于 $n$ 、 $m$ 都为奇的情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/3b6ze8d1.png)

那么，我们只需要保证 $2\times3$ 、$3\times2$ 的矩形归零操作次数不超过 $6$ ，$3\times3$ 的矩形归零操作次数不超过 $9$ 。

该怎么做呢……这是这道题的一大难点。~~我甚至曾经打算过暴力bfs打一个512的表~~。经过了 $1h$ 的激烈思考之后，我想明白了。

首先来考虑 $2\times3$ 、$3\times2$ 。以 $2\times3$ 为例（因为 $3\times2$ 本质上与之相同，稍加变通即可），如果最左边两个数同时为 $0$ 或最右边两个数同时为 $0$ ，那么我们可以直接忽略掉这两个 $0$ ，对剩下 $4$ 个数进行操作。否则，我们可以用最多一步操作的代价来转移到有一边全为 $0$ 的这种情况。对于最右边一列的 $4$ 种情况，我们可以分别给出解答：
```cpp
? ? 0
? ? 0:直接对左边4个数进行操作，最多4步。

? ? 0   o│o
? ? 1 : o└─。转化为0，0的情况，最多5步。

? ? 1   o┌─
? ? 0 : o│o。转化为0，0的情况，最多5步。

? ? 1   oo│
? ? 1 : o─┘。转化为0，0的情况，最多5步。
```
至此，我们成功超额完成任务，在 $5$ 步之内完成了对 $2\times3$ 、$3\times2$ 的解答。

接下来，再让我们来研究研究 $3\times3$ 的情况。可以发现，我们如果直接对前两行做一个 $2\times3$ ，再对后两行做一个 $2\times3$ ，就能够实现在 $10$ 步之内完成 $3\times3$ 的解答。但是，距离 $9$ 步还是有那么一点点差距的。

事实上，当我们对前两行做过一次 $2\times3$ 后，这个矩形就会变成这个样子：
```cpp
0 0 0
0 0 0
? ? ?
```
而如果最后一行的第一个或最后一个为 $0$ ，按照我们之前的优化，将能够在 $4$ 步之内完成，也就是说，一共最多需要 $9$ 步。否则，这个矩形只能长这样：
```cpp
0 0 0
0 0 0
1 ? 1
```
而又根据刚才的优化，对于一个为
```cpp
0 0 0
1 1 1
```
或
```cpp
0 0 0
1 0 1
```
的矩形，它们的归零操作次数分别为 $3$ 和 $2$ 。也就是说总操作次数最多分别为 $8$ 和 $7$ 。所以说，我们成功证明了直接对前两行做一个 $2\times3$ ，再对后两行做一个 $2\times3$ ，步数不会超过9。至此，这道题就华丽地结束了。~~颇有种劫后余生的侥幸啊哈哈~~
## 码
```cpp
#include<bits/stdc++.h>
using namespace std;
int temp[10005][10]={0},point=0,a[105][105]={0};
void push_ans(int i,int j,int x,int y)//做一次最基础操作，以i,j这个小个子为左上的2*2矩形，x,y点不进行操作
{
	point++;//总的操作次数 
	int xxx=0;
	for(int ii=i;ii<=i+1;ii++)
		for(int jj=j;jj<=j+1;jj++)
			if(ii!=x||jj!=y)
			{
				xxx++;
				temp[point][xxx]=ii;
				xxx++;
				temp[point][xxx]=jj;
				a[ii][jj]=1-a[ii][jj];//存储操作位置并进行相应操作，把复杂度为3的反向优化成复杂度为4（误）其实是为了少敲点码 
			}
} 
void _2H2L(int i,int j)//两行两列的归零操作 
{
	int a11=a[i][j],a12=a[i][j+1],a21=a[i+1][j],a22=a[i+1][j+1];//把数读出来 
	if(a11==0&&a12==0&&a21==0&&a22==0) return;
	else if(a11==0&&a12==0&&a21==0&&a22==1)
	{
		push_ans(i,j,i,j);
		push_ans(i,j,i,j+1);
		push_ans(i,j,i+1,j);
	}
	else if(a11==0&&a12==0&&a21==1&&a22==0)
	{
		push_ans(i,j,i,j+1);
		push_ans(i,j,i+1,j+1);
		push_ans(i,j,i,j);
	}
	else if(a11==0&&a12==0&&a21==1&&a22==1)
	{
		push_ans(i,j,i+1,j+1);
		push_ans(i,j,i+1,j);
	}
	else if(a11==0&&a12==1&&a21==0&&a22==0)
	{
		push_ans(i,j,i+1,j);
		push_ans(i,j,i+1,j+1);
		push_ans(i,j,i,j);
	}
	else if(a11==0&&a12==1&&a21==0&&a22==1)
	{
		push_ans(i,j,i+1,j+1);
		push_ans(i,j,i,j+1);
	}
	else if(a11==0&&a12==1&&a21==1&&a22==0)
	{
		push_ans(i,j,i,j+1);
		push_ans(i,j,i+1,j);
	}
	else if(a11==0&&a12==1&&a21==1&&a22==1)
	{
		push_ans(i,j,i,j);
	}
	else if(a11==1&&a12==0&&a21==0&&a22==0)
	{
		push_ans(i,j,i+1,j+1);
		push_ans(i,j,i+1,j);
		push_ans(i,j,i,j+1);
	}
	else if(a11==1&&a12==0&&a21==0&&a22==1)
	{
		push_ans(i,j,i,j);
		push_ans(i,j,i+1,j+1);
	}
	else if(a11==1&&a12==0&&a21==1&&a22==0)
	{
		push_ans(i,j,i,j);
		push_ans(i,j,i+1,j);
	}
	else if(a11==1&&a12==0&&a21==1&&a22==1)
		push_ans(i,j,i,j+1);
	else if(a11==1&&a12==1&&a21==0&&a22==0)
	{
		push_ans(i,j,i,j+1);
		push_ans(i,j,i,j);		
	}
	else if(a11==1&&a12==1&&a21==0&&a22==1)
		push_ans(i,j,i+1,j);
	else if(a11==1&&a12==1&&a21==1&&a22==0)
		push_ans(i,j,i+1,j+1);
	else if(a11==1&&a12==1&&a21==1&&a22==1)
	{
		push_ans(i,j,i+1,j+1);
		push_ans(i,j,i,j);
		push_ans(i,j,i,j+1);
		push_ans(i,j,i+1,j);
	}
}
void _2H3L(int i,int j)//两行三列 
{
	if(a[i][j]==0&&a[i+1][j]==0)//判是否有一边为0 
		_2H2L(i,j+1);
	else if(a[i][j+2]==0&&a[i+1][j+2]==0)
		_2H2L(i,j);
	else if(a[i][j+2]==0&&a[i+1][j+2]==1)
	{
		push_ans(i,j+1,i,j+2);
		_2H2L(i,j);
	}
	else if(a[i][j+2]==1&&a[i+1][j+2]==0)
	{
		push_ans(i,j+1,i+1,j+2);
		_2H2L(i,j);
	}
	else if(a[i][j+2]==1&&a[i+1][j+2]==1)
	{
		push_ans(i,j+1,i,j+1);
		_2H2L(i,j);
	}
}
void _3H2L(int i,int j)//三行两列，码和两行三列大同小异 
{
	if(a[i][j]==0&&a[i][j+1]==0)
		_2H2L(i+1,j);
	else if(a[i+2][j]==0&&a[i+2][j+1]==0)
		_2H2L(i,j);
	else if(a[i+2][j]==0&&a[i+2][j+1]==1)
	{
		push_ans(i+1,j,i+2,j);
		_2H2L(i,j);
	}
	else if(a[i+2][j]==1&&a[i+2][j+1]==0)
	{
		push_ans(i+1,j,i+2,j+1);
		_2H2L(i,j);
	}
	else if(a[i+2][j]==1&&a[i+2][j+1]==1)
	{
		push_ans(i+1,j,i+1,j);
		_2H2L(i,j);
	}
}
void _3H3L(int i,int j)//简洁明快的三行三列（我最大但是我最短）
{
	_2H3L(i,j);
	_2H3L(i+1,j);
}
int main(){
	int t,n,m;
	cin>>t;
	for(int ii=1;ii<=t;ii++)
	{
		scanf("%d%d",&n,&m);
		memset(temp,0,sizeof(temp));
		point=0;
		getchar();
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=m;k++)
			{
				char c=getchar();
				a[j][k]=c-'0';
			}
			getchar();
		}//读入 
		if(n%2==0&&m%2==0)
			for(int i=1;i<=n-1;i+=2)
				for(int j=1;j<=m-1;j+=2)
					_2H2L(i,j);
		else if(n%2==1&&m%2==0)
		{
			for(int i=1;i<=n-3;i+=2)
				for(int j=1;j<=m-1;j+=2)
					_2H2L(i,j);
			for(int i=1;i<=m-1;i+=2)
				_3H2L(n-2,i);
		}
		else if(n%2==0&&m%2==1)
		{
			for(int i=1;i<=n-1;i+=2)
				for(int j=1;j<=m-3;j+=2)
					_2H2L(i,j);
			for(int i=1;i<=n-1;i+=2)
				_2H3L(i,m-2);
		}
		else
		{
			for(int i=1;i<=n-3;i+=2)
				for(int j=1;j<=m-3;j+=2)
					_2H2L(i,j);
			for(int i=1;i<=m-3;i+=2)
				_3H2L(n-2,i);
			for(int i=1;i<=n-3;i+=2)
				_2H3L(i,m-2);
			_3H3L(n-2,m-2);
		}
		printf("%d\n",point);
		for(int i=1;i<=point;i++)
		{
			for(int j=1;j<=6;j++)
				printf("%d ",temp[i][j]);
			printf("\n");
		}//输出 
	}
	return 0;
} 
```
------------
这篇一定要过啊$qaq$

---

## 作者：比利♂海灵顿 (赞：0)

# CF1439A2 Binary Table (Hard Version)

## 题意:

和本题简单版本规则一样，给出 $n*m$ 的矩阵，每次操作对任意 $2*2$ 的格子内的三个点取反，最后将整个矩阵变为 $0$。只是操作次数需要控制在 $nm$ 次而不是 $3nm$ 次。

## 简单版本

对于在某个 $2*2$ 格子内的 $1$，可以在三次操作后在其他三个数不变的基础上修改它为 $0$，如修改格子 $(i,j)$ 具体操作方式就是这样：

```
i, j   i - 1, j       i - 1, j - 1
i, j   i - 1, j       i, j - 1
i, j   i - 1, j - 1   i, j - 1
```

最多有 $nm$ 个 $1$，每个 $1$ 操作 $3$ 次，所以最多操作 $3nm$ 次。

## 优化

这个想法来自一道[状压DP题](https://www.luogu.com.cn/problem/P2595)，一行一行地讨论，保证当前行没有 $1$ 的前提下，尽可能让步数最少。

枚举行数 $i$ 和列数 $j$，对于每一种情况分别进行操作。讨论局部 $1$ 的分布，然后进行最优操作，最后将操作数控制在 $nm$ 以内，具体操作参见代码注释。

对于边界（最后一行），分几种情况讨论，对于每 $2$ 列的任何情况，最多操作 $2$ 次。

对所有的情况, 每个 $1$ 最多使用 $1$ 次操作，即使是算上前一列的操作给后一列增加的 $1$，也最多只要考虑 $nm$ 个 $1$，所以总操作数也不超过 $nm$。（代码注释中的证明更加严谨）

## 代码（主函数）

```cpp
int main() {
  t = RD();  //读入优化 函数省略
  for (register int T(1); T <= t; ++T) {
    Clr();  //初始化变量 函数省略
    n = RD();
    m = RD();
    for (register int i(1); i <= n; ++i) {
      gets(s);  //按行读入
      for (register int j(1); j <= m; ++j) {
        b[i][j] = s[j - 1] - '0';  //存为 bool 数组
        if (b[i][j]) {
          ++cnt1;
        }
      }
    }
    for (register int i(1); i < n; ++i) {  //枚举行数, 最后一行单独讨论
      for (register int j(1); j < m; j++) {  //枚举列数, 最后一列单独讨论
        if (!b[i][j]) {                      //当前为0
          if (b[i][j + 1] && b[i + 1][j] &&
              b[i + 1][j + 1]) {  //但是右边, 下边, 右下三个格子恰好可以一次消掉
            sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j + 1, i + 1, j + 1,
                    i + 1, j);  //取反(3个1, 1次操作)
            b[i][j + 1] = 0;
            b[i + 1][j] = 0;
            b[i + 1][j + 1] = 0;  //维护数组
            ++j;  //由于一次讨论了两列, 额外往后移动一格
          }
          continue;  //反正当前格子是0, 就往下讨论
        }
        if (b[i][j] && b[i][j + 1]) {  //连续两个格子都有1,
                                       //分三类讨论下一行两个格子的三种情况
          b[i][j + 1] = 0;
          if (b[i + 1][j]) {  //左下是1, 将三个1同时消除
            sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j, i, j + 1, i + 1,
                    j);  // 3个1, 1次操作
            b[i + 1][j] = 0;
          } else {
            if (b[i + 1][j + 1]) {  //右下是1, 同样同时消除三个1
              sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j, i, j + 1, i + 1,
                      j + 1);  // 3个1, 1次操作
              b[i + 1][j + 1] = 0;
            } else {  //下方两个0, 或两个1,
                      //用两步在不破坏下一行的基础上消除这一行的两个1
              sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j, i + 1, j, i + 1,
                      j + 1);
              sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j + 1, i + 1, j,
                      i + 1, j + 1);  // 2个1, 2次操作
            }
          }
          ++j;  //由于一次操作两列, 所以 j 额外增加 1
          continue;
        }
        if (j + 2 <= m) {  //由于之前已经讨论过当前格为0的情况,
                           //所以能运行到这里的当前格一定是1
          if (b[i][j + 2] &&
              (!b[i + 1]
                 [j + 1])) {  //两个1中间隔一个0,
                              //可以用两步在不修改其他格的情况下对这两个1取反
            sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j, i, j + 1, i + 1,
                    j + 1);
            sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j + 2, i, j + 1,
                    i + 1, j + 1);  // 2个1, 2次操作
            b[i][j + 2] = 0;
            j += 2;  //由于一下子考虑了三列, 所以 j 额外加2
            continue;
          }
        }
        if ((!b[i + 1][j]) &&
            (b[i + 1][j + 1])) {  //在2*2格子的对角线上有两个1,
                                  //可以两步解决这两个1
          sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j, i, j + 1, i + 1, j);
          sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j + 1, i + 1, j, i + 1,
                  j + 1);  // 2个1, 2次操作
          b[i + 1][j + 1] = 0;
          ++j;  //额外加1, 同上
          continue;
        }
        //在除去前面众多情况后, 只剩下了一种最普通的情况,
        //在以(i,j)为左上角的2*2方格中,
        //左上角为1, 右上角为0, 左下角未知, 右下角为0,
        //这时只能用一个操作, 在改变下一行两个格子的代价下, 将(i,j)的1取反
        sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, j, i + 1, j + 1, i + 1,
                j);  // 1个1, 1次操作
        b[i + 1][j] ^= 1;
        b[i + 1][j + 1] ^= 1;
        continue;
      }
      if (b[i][m]) {  //对于最后一列, 情况较为特殊, 因为没有右边的格子了
        if (b[i + 1][m - 1] &&
            (!b[i + 1]
               [m])) {  //也是类似的对角线, 只不过方向和之前的那种情况垂直
          sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, m, i, m - 1, i + 1, m);
          sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i + 1, m - 1, i, m - 1,
                  i + 1, m);  // 2个1, 2次操作
          b[i + 1][m - 1] = 0;
          continue;
        }
        //最后剩下的情况, 即以(i,m)为右上角的2*2格子里,
        //左上角为0, 右上角为1, 左下角为0, 右下角未知,
        //取反下一行两个点为代价, 取反(i,m)的1
        sprintf(ans[++cnta], "%d %d %d %d %d %d\n", i, m, i + 1, m, i + 1,
                m - 1);  // 1个1, 1次操作
        b[i + 1][m] ^= 1;
        b[i + 1][m - 1] ^= 1;
        continue;
      }
    }
    for (register int i(1); i < m; i++) {  //对于最后一行
      if (!b[n][i]) {                      //没有1就不操作了, 跳过
        continue;
      }
      if (b[n][i] && b[n][i + 1]) {  //两个连续的1
        sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n - 1, i, n - 1, i + 1, n,
                i);
        sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n - 1, i, n - 1, i + 1, n,
                i + 1);  // 2个1, 2次操作
        b[n][i + 1] = 0;
        ++i;
        continue;
      }
      if (i + 2 <= m) {     //这时已经确定(n,i)为1, (n,i+1)为0了
        if (b[n][i + 2]) {  //两个1中间隔了一个0
          sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n, i, n - 1, i + 1, n,
                  i + 1);
          sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n, i + 2, n - 1, i + 1, n,
                  i + 1);  // 2个1, 2次操作
          b[n][i + 2] = 0;
          i += 2;
          continue;
        }
      }
      //这种情况比较少见, 但是出现这种情况时, (n,i + 1),(n,i + 2)都一定为0,
      //所以相当于把本来右边两个格子的操作预算透支在了这个格子上,
      //所以操作数还是对的
      sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n, i, n - 1, i, n - 1, i + 1);
      sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n, i, n - 1, i, n, i + 1);
      sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n, i, n - 1, i + 1, n, i + 1);
      continue;
    }
    if (b[n][m]) {  //对于最后一个格子为1, 也有这种情况,
                    //右边也没有为0的格子的操作数供它透支,
                    //左边的格子就算是0, 也可能已经被透支了,
                    //但是别忘了, 只有最后一行有透支这种东西,
                    //在前面的行里面只有某些极限数据才会吃满m(n-1)种操作,
                    //对于我的算法, 这种数据必须满足m为偶数, 第一行全是1,
                    //后面(n-1)行全是0,
                    //而这种数据的(m,n)是取不到1的,
                    //而其他数据总能挤出一两个可供透支的操作数,所以算法正确
      sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n, m, n - 1, m, n - 1, m - 1);
      sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n, m, n - 1, m, n, m - 1);
      sprintf(ans[++cnta], "%d %d %d %d %d %d\n", n, m, n - 1, m - 1, n, m - 1);
    }
    printf("%d\n", cnta);  //统计的操作数
    for (register int i(1); i <= cnta; ++i) {
      printf(ans[i]);  //早已经按格式作为字符串存起来(sprintf())的操作
    }
  }
  return 0;
}
```

---

## 作者：wwldx (赞：0)

这题其实就是个单纯的暴力题，我们先从上往下，从左往右，一个一个遍历，假如当前位置是1，那肯定是要改变成0，为了不影响之前已经确定过的，我们每次将当前位置，以及正下方的数字，然后第三个数字随便选右边或者右下的数字都可以，当然，假如当前位置在右边界了，那选择下方和左下方即可，从上往下遍历前$n-2$行，再遍历最后2行的前$m-2$个，保留最后一个$2*2$的矩阵，对他单独分析即可，假如里面没有1直接输出就好，假如里面有一个1，我们可以分析得出，1的格子操作次数必然是$2*k+1$,其他格子的操作次数是分别是$2*a$,$2*b$,$2*c$,而他们相加得是$3*x$次，所以我们易得值为1的格子的操作最小是3，其他3个格子的操作次数都是2，所以当4个格子的和为1时，操作次数为3，设1的格子为a，其他3个格子为b,c,d,翻转操作分别是$（a,b,c),(a,b,d),(a,c,d)$

当4个格子的和为2时，2个1的格子的操作次数分别是$2*k+1$和$2*l+1$,其他2个格子分别是$2*a$和$2*b$，相加依然得为$3*n$，所以易得2个1的格子操作次数都为1，0的格子都为2，设2个1的格子分别为a，b，2个0的格子分别为c，d，那么操作就是(a,c,d),(b,c,d)，总操作次数为2次。

当4个格子的和为3时，设3个1的格子分别为a,b,c,0的格子为d,那么同理分析，可得出次数分别为1，1，1，0，操作为(a,b,c)，总操作次数为1次

当4个格子全为1时，次数分别为3,3,3,3,操作为(a,b,c),(b,c,d),(c,d,a),(d,a,b)，总操作次数为4。

所以可以看出，将前面的全部暴力处理，只留最后一个$2*2$的矩阵进行单独分析，矩阵的次数也不会超过4次，前面的次数最多为$n*m-4$，所以不会超过$n*m$
以下为ac代码：（判断次数的时候写的过分复杂了，但我懒得写简洁了，总之大概意思大家都懂）
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<n;i++)
#define per(i,a,n) for(int i=n-1;i>=a;i--)
typedef long long ll;
typedef double db;
typedef pair<int,int> P;
typedef vector<int> VI;
//const ll mod=1000000007;
const int maxn=2e2+10;
const int inf=0x3f3f3f3f;
//const ll inf = 1e18;
//const int inf=0x7fffffff;
ll gcd(ll a,ll b) {
    return b?gcd(b,a%b):a;
}
//	  freopen("1.txt","r",stdin);
//    freopen("2.txt","w",stdout);
#define ms(a) memset(a,0,sizeof(a))
#define mss(a) memset(a,-1,sizeof(a))
#define msi(a) memset(a,inf,sizeof(a))
#define iossync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
//head
int a[maxn][maxn];
int n,m;
int T;
int cnt=0;
struct node{
	int a[6];
	node(int x,int x1,int x2,int x3,int x4,int x5)
	{
		a[0]=x,a[1]=x1,a[2]=x2,a[3]=x3,a[4]=x4,a[5]=x5;
	}
	node()
	{
		rep(i,0,6)
		a[i]=0;
	}
	friend ostream & operator << (ostream & c,const node & b);
};
ostream & operator << (ostream & c,const node & b)
{
	rep(i,0,3)
	{
		if(i)
		cout<<" ";
		cout<<b.a[i*2]<<" "<<b.a[i*2+1];
	}
	return c; 
}
vector< node> v1;
void change(int x1,int y1,int z)
{//1  下1 下2    2 下 下左 
	cnt++;
	int x2=x1+1,y2=y1;
	int x3=x1+1,y3=y1+1;
	if(z==3) y3-=2,x3-=1;
	if(z==2) y3-=2;   
	a[x1][y1]^=1;
	a[x2][y2]^=1;
	a[x3][y3]^=1;
	v1.push_back(node(x1,y1,x2,y2,x3,y3));
	//emmm,似乎得最后一起输出呀 
//	cout<<x1<<" "<<y1<<" "<<x1+1<<" "<<y1<<" "<<x1+1<<" "<<y1+1<<"\n";
}
void work()
{
//预留2行单独处理 
	cnt=0;
	v1.clear();
	rep(i,1,n-1)
	{
		rep(j,1,m+1)
		{
			if(a[i][j])
			{
				if(j<m)
					change(i,j,1); 
				else
					change(i,j,2);
			}
		}
	}
	rep(i,1,m-1)
	{
		if(a[n-1][i] && a[n][i])
			change(n-1,i,1);
		else
		if(a[n-1][i])
			change(n-1,i+1,3);
		else
		if(a[n][i])
			change(n-1,i+1,2);
	}
	//单独分析2*2的
	int sum=a[n-1][m]+a[n-1][m-1]+a[n][m]+a[n][m-1];
	switch(sum)
	{
		case 1:{
			rep(i,n-1,n+1)
			{
				rep(j,m-1,m+1)
				{
					if(a[i][j])
					{
						cnt+=3;
						int x1=i,y1=j+1;
						if(y1>m)
						y1-=2;
						int x2=i+1,y2=j;
						if(x2>n)
						x2-=2;
						int x3=n,y3=m;
						if(x3==i) x3--;
						if(y3==j) y3--;
						v1.push_back(node(i,j,x1,y1,x2,y2));
						v1.push_back(node(i,j,x1,y1,x3,y3));
						v1.push_back(node(i,j,x3,y3,x2,y2));
					}
				}
			 } 
			break;
		}
		case 2:{
			cnt+=2;
			int x1,y1,x2,y2;
			int x3,y3,x4,y4;
			if(a[n-1][m-1])
			{
				x1=n-1,y1=m-1;
				if(a[n-1][m])
				{
					x2=n-1,y2=m;
					x3=n,y3=m-1;
					x4=n,y4=m;
				}
				else
				if(a[n][m-1])
				{
					x2=n,y2=m-1;
					x3=n-1,y3=m;
					x4=n,y4=m;
				}
				else
				{
					x2=n,y2=m;
					x3=n,y3=m-1;
					x4=n-1,y4=m;
				}
			}
			else
			if(a[n-1][m])
			{
				if(a[n][m-1])
				{
					x1=n-1,y1=m;
					x2=n,y2=m-1;
					x3=n-1,y3=m-1;
					x4=n,y4=m;
				}
				else
				{
					x1=n-1,y1=m;
					x2=n,y2=m;
					x3=n-1,y3=m-1;
					x4=n,y4=m-1;
				}
			}
			else
			{
				x1=n,y1=m-1;
				x2=n,y2=m;
				x3=n-1,y3=m-1;
				x4=n-1,y4=m;
			}
			v1.push_back(node(x1,y1,x3,y3,x4,y4));
			v1.push_back(node(x2,y2,x3,y3,x4,y4));
			break;
		}
		case 3:{
			cnt++;
			if(a[n-1][m-1]==0)
			v1.push_back(node(n-1,m,n,m-1,n,m));
			else
			if(a[n-1][m]==0)
			v1.push_back(node(n-1,m-1,n,m-1,n,m));
			else
			if(a[n][m-1]==0)
			v1.push_back(node(n-1,m-1,n-1,m,n,m));
			else
			v1.push_back(node(n-1,m-1,n-1,m,n,m-1));
			break;
		}
		case 4:{
			cnt+=4;
			v1.push_back(node(n-1,m-1,n-1,m,n,m-1));
			v1.push_back(node(n-1,m,n,m-1,n,m));
			v1.push_back(node(n-1,m-1,n-1,m,n,m));
			v1.push_back(node(n-1,m-1,n,m-1,n,m));
			break;
		}
	}
	cout<<cnt<<"\n";
	for(auto now:v1)
	{
		cout<<now<<"\n";
	}
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		rep(i,1,n+1)
		{
			rep(j,1,m+1)
			scanf("%1d",&a[i][j]);
		}
		work();
	}
	return 0;
}
```


---

## 作者：KSToki (赞：0)

# 题目大意
给定一个 $n\times m$ 的 $01$ 矩阵，每次操作可以将某个 $2\times2$ 的矩阵内的 $3$ 个数取反，请在 $n\times m$ 步内将矩阵变为全 $0$。
# 分析
**大模拟**，首先每次将 $(1,1)$~$(n-2,m-2)$ 中的变为全 $0$，显然每次只需要一步（另外两个可以随便点）。处理最后两列，即 $(1,m-1)$~$(n-2,m)$，显然一行一步，最后两行同理。然后特判最后一个 $2\times2$，可以手模，发现一定能在 $4$ 步内做完，所以能在 $n\times m$ 步内将矩阵变为全 $0$。其实最后一步才是码量最大的。
# 代码
大模拟要有耐心，前方高能：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	int res=0;
    while(ch>='0'&&ch<='9')
    {
    	res=res*10+ch-'0';
		ch=getchar();
    }
    return res;
}
int T,n,m,a[101][101],ans[10001][6];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				scanf("%1d",&a[i][j]);
		int cnt=0;
		for(int i=1;i<n-1;++i)
			for(int j=1;j<m-1;++j)
				if(a[i][j]==1)
				{
					if(a[i+1][j]==1&&a[i+1][j+1]==1)
					{
						++cnt;
						ans[cnt][0]=i;
						ans[cnt][1]=j;
						ans[cnt][2]=i+1;
						ans[cnt][3]=j;
						ans[cnt][4]=i+1;
						ans[cnt][5]=j+1;
						a[i][j]^=1;
						a[i+1][j]^=1;
						a[i+1][j+1]^=1;
					}
					else
					{
						++cnt;
						ans[cnt][0]=i;
						ans[cnt][1]=j;
						ans[cnt][2]=i;
						ans[cnt][3]=j+1;
						ans[cnt][4]=i+1;
						ans[cnt][5]=j+1;
						a[i][j]^=1;
						a[i][j+1]^=1;
						a[i+1][j+1]^=1;
					}
				}
		for(int i=1;i<m-1;++i)
		{
			if(a[n-1][i]==0&&a[n][i]==1)
			{
				++cnt;
				ans[cnt][0]=n;
				ans[cnt][1]=i;
				ans[cnt][2]=n-1;
				ans[cnt][3]=i+1;
				ans[cnt][4]=n;
				ans[cnt][5]=i+1;
				a[n][i]=0;
				a[n-1][i+1]^=1;
				a[n][i+1]^=1;
			}
			else if(a[n-1][i]==1&&a[n][i]==0)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=i;
				ans[cnt][2]=n-1;
				ans[cnt][3]=i+1;
				ans[cnt][4]=n;
				ans[cnt][5]=i+1;
				a[n-1][i]=0;
				a[n-1][i+1]^=1;
				a[n][i+1]^=1;
			}
			else if(a[n-1][i]==1&&a[n][i]==1)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=i;
				ans[cnt][2]=n-1;
				ans[cnt][3]=i+1;
				ans[cnt][4]=n;
				ans[cnt][5]=i;
				a[n-1][i]=a[n][i]=0;
				a[n-1][i+1]^=1;
			}
		}
		for(int i=1;i<n-1;++i)
		{
			if(a[i][m-1]==0&&a[i][m]==1)
			{
				++cnt;
				ans[cnt][0]=i;
				ans[cnt][1]=m;
				ans[cnt][2]=i+1;
				ans[cnt][3]=m;
				ans[cnt][4]=i+1;
				ans[cnt][5]=m-1;
				a[i][m]=0;
				a[i+1][m]^=1;
				a[i+1][m-1]^=1;
			}
			else if(a[i][m-1]==1&&a[i][m]==0)
			{
				++cnt;
				ans[cnt][0]=i;
				ans[cnt][1]=m-1;
				ans[cnt][2]=i+1;
				ans[cnt][3]=m;
				ans[cnt][4]=i+1;
				ans[cnt][5]=m-1;
				a[i][m-1]=0;
				a[i+1][m]^=1;
				a[i+1][m-1]^=1;
			}
			else if(a[i][m-1]==1&&a[i][m]==1)
			{
				++cnt;
				ans[cnt][0]=i;
				ans[cnt][1]=m-1;
				ans[cnt][2]=i;
				ans[cnt][3]=m;
				ans[cnt][4]=i+1;
				ans[cnt][5]=m-1;
				a[i][m-1]=a[i][m]=0;
				a[i+1][m-1]^=1;
			}
		}
		if(a[n-1][m-1]==1&&a[n-1][m]==1&&a[n][m-1]==1&&a[n][m]==1)
		{
			++cnt;
			ans[cnt][0]=n-1;
			ans[cnt][1]=m-1;
			ans[cnt][2]=n-1;
			ans[cnt][3]=m;
			ans[cnt][4]=n;
			ans[cnt][5]=m-1;
			a[n-1][m-1]=a[n-1][m]=a[n][m-1]=0;
		}
		int res=0;
		for(int i=n-1;i<=n;++i)
			for(int j=m-1;j<=m;++j)
				res+=a[i][j];
		if(res==3)
		{
			int now=0;
			++cnt;
			for(int i=n-1;i<=n;++i)
				for(int j=m-1;j<=m;++j)
					if(a[i][j]==1)
					{
						a[i][j]=0;
						ans[cnt][now]=i;
						++now;
						ans[cnt][now]=j;
						++now;
					}
		}
		if(res==1)
		{
			if(a[n-1][m]==1)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=m;
				ans[cnt][2]=n;
				ans[cnt][3]=m;
				ans[cnt][4]=n;
				ans[cnt][5]=m-1;
				a[n-1][m]=0;
				a[n][m]=a[n][m-1]=1;
			}
			else if(a[n-1][m-1]==1)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=m-1;
				ans[cnt][2]=n;
				ans[cnt][3]=m;
				ans[cnt][4]=n;
				ans[cnt][5]=m-1;
				a[n-1][m-1]=0;
				a[n][m]=a[n][m-1]=1;
			}
			else if(a[n][m-1]==1)
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=m-1;
				ans[cnt][2]=n-1;
				ans[cnt][3]=m;
				ans[cnt][4]=n;
				ans[cnt][5]=m-1;
				a[n][m-1]=0;
				a[n-1][m-1]=a[n-1][m]=1;
			}
			else
			{
				++cnt;
				ans[cnt][0]=n-1;
				ans[cnt][1]=m-1;
				ans[cnt][2]=n-1;
				ans[cnt][3]=m;
				ans[cnt][4]=n;
				ans[cnt][5]=m;
				a[n][m]=0;
				a[n-1][m-1]=a[n-1][m]=1;
			}
			res=2;
		}
		if(res==2)
		{
			if(a[n][m-1]==a[n-1][m])
			{
				if(a[n][m-1]==1)
				{
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
				}
				else
				{
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m;
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m;
				}
			}
			else
			{
				if(a[n-1][m-1]==1&&a[n-1][m]==1)
				{
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
				}
				else if(a[n-1][m-1]==1&&a[n][m-1]==1)
				{
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n;
					ans[cnt][5]=m;
				}
				else if(a[n][m]==1&&a[n-1][m]==1)
				{
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m-1;
					++cnt;
					ans[cnt][0]=n-1;
					ans[cnt][1]=m;
					ans[cnt][2]=n;
					ans[cnt][3]=m-1;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m-1;
				}
				else
				{
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m-1;
					++cnt;
					ans[cnt][0]=n;
					ans[cnt][1]=m-1;
					ans[cnt][2]=n-1;
					ans[cnt][3]=m;
					ans[cnt][4]=n-1;
					ans[cnt][5]=m-1;
				}
			}
		}
		printf("%d\n",cnt);
		for(int i=1;i<=cnt;++i)
		{
			for(int j=0;j<6;++j)
				printf("%d ",ans[i][j]);
			printf("\n");
		}	
		cnt=0;
	}
	return 0;
}
```


---

