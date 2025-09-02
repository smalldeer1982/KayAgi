# Grid Xor

## 题目描述

Note: The XOR-sum of set $ \{s_1,s_2,\ldots,s_m\} $ is defined as $ s_1 \oplus s_2 \oplus \ldots \oplus s_m $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

After almost winning IOI, Victor bought himself an $ n\times n $ grid containing integers in each cell.  $ n $ is an even integer. The integer in the cell in the $ i $ -th row and $ j $ -th column is $ a_{i,j} $ .

Sadly, Mihai stole the grid from Victor and told him he would return it with only one condition: Victor has to tell Mihai the XOR-sum of all the integers in the whole grid.

Victor doesn't remember all the elements of the grid, but he remembers some information about it: For each cell, Victor remembers the XOR-sum of all its neighboring cells.

Two cells are considered neighbors if they share an edge — in other words, for some integers $ 1 \le i, j, k, l \le n $ , the cell in the $ i $ -th row and $ j $ -th column is a neighbor of the cell in the $ k $ -th row and $ l $ -th column if $ |i - k| = 1 $ and $ j = l $ , or if $ i = k $ and $ |j - l| = 1 $ .

To get his grid back, Victor is asking you for your help. Can you use the information Victor remembers to find the XOR-sum of the whole grid?

It can be proven that the answer is unique.

## 说明/提示

For the first test case, one possibility for Victor's original grid is:

 $ 1 $  $ 3 $  $ 2 $  $ 4 $ For the second test case, one possibility for Victor's original grid is:

 $ 3 $  $ 8 $  $ 8 $  $ 5 $  $ 9 $  $ 5 $  $ 5 $  $ 1 $  $ 5 $  $ 5 $  $ 9 $  $ 9 $  $ 8 $  $ 4 $  $ 2 $  $ 9 $ For the third test case, one possibility for Victor's original grid is:

 $ 4 $  $ 3 $  $ 2 $  $ 1 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 7 $  $ 8 $  $ 8 $  $ 9 $  $ 9 $  $ 1 $

## 样例 #1

### 输入

```
3
2
1 5
5 1
4
1 14 8 9
3 1 5 9
4 13 11 1
1 15 4 11
4
2 4 1 6
3 7 3 10
15 9 4 2
12 7 15 1```

### 输出

```
4
9
5```

# 题解

## 作者：enucai (赞：25)

**Update 2022.2.6:** 修正了错别字（将“亦或”修改为“异或”）。

---

**Preface**：考场上最后三分钟打完结果忘判边界而亡。

### 题意

有一个 $n\times n$（$n$ 为偶数） 的矩阵，告诉你这个矩阵中每个位置四周的数字的异或和，求矩阵中所有数的异或和。

### 思路

以下称每个格子四周的数字异或和组成的矩阵为 $a$。

稍微想想就知道应该怎么构造（~~xxs都会吧~~。

先来看一下对于一个 $6\times 6$ 的矩阵该怎么算。

![](https://cdn.luogu.com.cn/upload/image_hosting/8827lbin.png)

在第一幅图中，红色格子的 $a$ 值的异或和为黄色格子所有数字的异或和。

在第二幅图中，蓝色格子的 $a$ 值的异或和为绿色格子所有数字的异或和。

绿色格子与黄色格子合起来就是整个矩阵了。所以只要将红、蓝格子的 $a$ 值异或起来就是答案。

再来看一下对于一个 $8\times 8$ 的矩阵该怎么算：

![](https://cdn.luogu.com.cn/upload/image_hosting/z7558vr4.png)

算的方法和 $6\times 6$ 一样。

是不是瞬间豁然开朗（bushi。

----

接下来看看红点与蓝点位置有什么特征。

很容易发现蓝点与红点关于中间的竖线对称，即若位置 $(i,j)$ 为红点，则位置 $(i,n-j+1)$ 必是蓝点。所以问题简化：红点位置有什么特征。

对于 $8\times 8$ 的矩阵，把红点位置都表示出来：

- $(1,3)$，$(3,1)$
- $(1,7)$，$(3,5)$，$(5,3)$，$(7,1)$
- $(4,8)$，$(6,6)$，$(8,4)$
- $(8,8)$

容易发现，第一组横纵坐标值和为 $4$，第二组为 $8$，第三组为 $12$，第四组为 $16$。而且每一组的相邻两个横坐标差为 $2$。

再观察一下，发现前两组的第一个横坐标为 $1$，后两组第一个横坐标为 $2$（可以反推一下，$(4,8)$ 前面一个是 $(2,10)$，$(8,8)$ 一直往前推是 $(2,14)$）。而前两组的横纵坐标和小于等于 $n$，后两组横纵坐标和大于 $n$。特征便显而易见了。

在用这种方法算一下 $6\times 6$ 的矩阵，发现也符合规律。所以着这种方法是可行的。

### 代码

**Talk is cheap, show me the code.**

[Codeforces status](https://codeforces.com/contest/1628/submission/143737617)

```cpp
int n,a[1010][1010];
void work(){
	n=read();
	For(i,1,n) For(j,1,n) a[i][j]=read();
	int ans=0;
	for(int sum=4;sum<=2*n;sum+=4){
		if(sum<=n){
			for(int i=1;i<=n;i+=2){
				int j=sum-i;
				if(j>n||j<1) continue;
				ans^=a[i][j];
				ans^=a[i][n-j+1];
			}
		}else{
			for(int i=2;i<=n;i+=2){
				int j=sum-i;
				if(j>n||j<1) continue;
				ans^=a[i][j];
				ans^=a[i][n-j+1];
			}
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：Jsxts_ (赞：5)

手玩的。

考虑将图黑白染色，那么黑白方法是一样的，只关注如何选出若干黑格使得所有白格的贡献次数为奇数。

然后发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/88v359ls.png)

如图，只选第一条直线的黄格能得到蓝格的异或和，选前两条直线的黄格能得到红格的异或和，以此类推。

然后另一个方向的就反过来。

然后白格对黑格的方法类似。

然后做完了。



---

## 作者：Jim_Franklin (赞：3)

是 zak 的做法 QwQ。

我们钦定 $b$ 的第一行都是 $0$。

然后根据 $a_{i,j}=b_{i-1,j}\oplus b_{i+1,j}\oplus b_{i,j+1}\oplus b_{i,j-1}$ （不存在的 $b$ 我们将他设为 $0$ ）就可以递推出 $b$ 数组，现在要证明此时的 $b$ 数组一定是合法的。

题目中提到了 $b$ 一定是有解的（这个其实可以构造证明）。

设 $v=b_{1,1}$ 将 $b_{1,1}$ 异或上 $v$ 这时会影响到的位置有 $(2,1)$ 和 $(1,2)$ 发现能够同时影响到他们的格子还有 $(2,2)$ 于是把 $b_{2,2}$ 再异或上 $v$ 重复这么做下去，并对第一行的其他格子如法炮制，就能把第一行的 $b$ 全部变成 $0$。

于是我们证明了对于任意一个合法的 $b$ 我们一定可以将他转换为一个第一行都是 $0$ 的且合法的 $b'$  。

于是我们的做法就得到了证明。

```cpp
void sol(){
	n=rd();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)a[i][j]=rd();
	int ans=0;
	for(int i=1;i<n;i++)
		for(int j=1;j<=n;j++)
			res[i+1][j]=a[i][j]^res[i-1][j]^res[i][j+1]^res[i][j-1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
          ans^=res[i][j],res[i][j]=0;
	cout<<ans<<'\n';
}
```

---

## 作者：Rain_chr (赞：2)

大家怎么观察能力这么强，题解区全是手玩的，我来说一个不用手玩也能做出题目的做法。

首先我们可以发现每一位之间互相独立，那么没什么好说的，先拆位再处理，现在 $a,b$ 矩阵就都只有 $0,1$ 两种取值了。

根据 $a$ 矩阵的计算方式，我们可以得到 $a_{i,j}=b_{i-1,j}\oplus b_{i,j-1}\oplus b_{i,j+1}\oplus b_{i+1,j}$，移个项之后得到：

$$a_{i,j}\oplus b_{i-1,j}\oplus b_{i,j-1}\oplus b_{i,j+1}\oplus b_{i+1,j}=0$$

这是经典异或高斯消元问题，可以得到 $b$ 矩阵的一组解，于是我们就有了一个多项式复杂度的做法，尽管这是 $O(n^6)$ 的。

对于这种相邻四个数组成的高斯消元问题，可以发现如果知道了第 $i$ 行所有 $b_{i,j}$ 的取值，通过上面的这个式子可以直接异或得到第 $i+1$ 行的所有 $b_{i+1,j}$，那我们是不是可以先设参，假设已知第 $1$ 行的 $b_{1,j}$ 取值，然后就可以表示出所有的 $b_{i,j}$ 了。最后只要用最后一行的 $a_{n,j}$ 列一个式子就可以了，复杂度就是 $O(n^3)$，还是过不去。

考场上我突然意识到一件事情，题目竟然是保证有解的，那么我就第一行全填 $0$ 再递推出 $b$ 矩阵就可以了。

时间复杂度为 $O(n^2\log V)$，但是你这时候发现拆位就很蠢了，把所有位放在一起进行上述操作就可以了，时间复杂度 $O(n^2)$

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2300}$
---
### 解题思路：

其实没有必要给出一个完整的构造方法，直接让程序生成一下就可以了。代码可能更长一点，但是不用动脑子。

首先做一些基本的转化，问题实质上就是用一些类似于十字去掉中间的一个格子的图形覆盖整个矩形。直接用这些个原始的东西不太好做，考虑将两个图形放到一起，形成一个单元，也就是两个相邻的格子以及旁边的所有格子，去覆盖整个矩形。

将第一排特别考虑，显然是尽可能地放置从而使得第一排全都放满。其他的位置从横排考虑只会出现两种情况，连续有两个空白和只有一个空白，两个的话就在这个格子下面和右下放一个，只有一个的话就在这个格子下面和下面的下面放就行了。

如果没有写错的话，最后一排上再处理之前的内容的时候就已经被放满了，不需要特殊考虑。

复杂度 $O(nm)$。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int T,n,a[1005][1005],b[1005][1005],ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
			b[i][j]=0;
		}
		ans=0;
		for(int j=1;j<=n;j++){
			int i=1;
			if(b[i][j]==0){
				if(b[i][j+1]==0&&j+1<=n){
					if(j>=2)if(b[i][j-1]==1)continue;
					ans^=a[i][j];
					ans^=a[i][j+1];
					b[i][j]++;b[i][j+1]++;b[i][j-1]++;b[i][j+2]++;
					b[i+1][j]++;b[i+1][j+1]++;
				}
				else{
					ans^=a[i+1][j];
					ans^=a[i+2][j];
					b[i][j]++;b[i+1][j]++;b[i+2][j]++;b[i+3][j]++;
					b[i+1][j+1]++;b[i+1][j-1]++;b[i+2][j-1]++;b[i+2][j+1]++;
				}
			}
		}
		for(int i=2;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(b[i][j]==0){
				if(b[i][j+1]==0&&j+1<=n){
					ans^=a[i+1][j];
					ans^=a[i+1][j+1];
					b[i][j]++;b[i+1][j]++;b[i][j+1]++;b[i+1][j-1]++;
					b[i+1][j+1]++;b[i+1][j+2]++;b[i+2][j]++;b[i+2][j+1]++;
				}
				else{
					ans^=a[i+1][j];
					ans^=a[i+2][j];
					b[i][j]++;b[i+1][j]++;b[i+2][j]++;b[i+3][j]++;
					b[i+1][j+1]++;b[i+1][j-1]++;b[i+2][j-1]++;b[i+2][j+1]++;
				}
			}
		}
//		for(int i=1;i<=n;i++){
//			for(int j=1;j<=n;j++)
//			printf("%d",b[i][j]);
//			printf("\n");
//		}
		printf("%d\n",ans);
		
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：1)

# CF1628C - Grid Xor 题解

## 题目大意

[题目链接](https://codeforces.com/problemset/problem/1628/C)

已知一个 $n\times n$ 的矩阵 $v$，现在对这个矩阵进行一次变换，得到一个 $n\times n$ 的矩阵 $a$。

具体变换规则如下：

$a$ 中的每一个元素 $a(i,j)$ 的值是 $v$ 矩阵中所有与元素 $v(i,j)$ 相邻（也就是有一条公共边）的所有元素的异或值之和。

现在已经将 $a$ 矩阵给出，请求出 $v$ 矩阵里所有数的异或和。

数据范围保证： $n\le1000$。

## 思路分析

首先考虑 $a$ 矩阵里所有数的异或和，将答案记为 $\text{ans}$ 。

用 $c(i,j)$ 表示此时元素 $v(i,j)$ 对 $\text{ans}$ 的贡献，也就是 $v(i,j)$ 在计算 $\text{ans}$ 的时候被异或了几次（注意这里是 $v$）。

那么如果在 $\text{ans}$ 上异或一个数 $a(i,j)$，那么所有与 $c(i,j)$ 元素相邻的值都会 $+1$。

只要存在某种方式使得每一个$c(i,j)$ 都是奇数，那么 $\text{ans}$ 的值就是我们所求的答案值。

这种情况可以~~口胡~~想出一个贪心的算法，对于每一个不在第 $1$ 行的数，如果 $c(i-1,j)$ 是偶数，那么就在 $\text{ans}$ 上异或上 $a(i,j)$ 的值，这样就可以得出正确的答案。

关于本方法的正确性，证明留作习题，请自行尝试 逃）

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1001;
int c[MAXN][MAXN],a[MAXN][MAXN],n,ans;
inline bool side(int x) {
	return x==1||x==n; //判断第x行或列是否在矩阵的边缘 
}
inline int judge(int x,int y) {
	//计算(x,y)周围有几个相邻的格子，也就是基础的c[x][y]的值 
	if(side(x)&&side(y)) return 2;
	if(side(x)||side(y)) return 3;
	return 4;
}
inline void work(int x,int y) {
	//向四个方向尝试拓展 
	if(x!=1) ++c[x-1][y];
	if(y!=1) ++c[x][y-1];
	if(x!=n) ++c[x+1][y];
	if(y!=n) ++c[x][y+1];
	ans^=a[x][y];
	return ;
}
inline void solve() {
	ans=0;
	memset(c,0,sizeof(c));
	memset(a,0,sizeof(a));
	scanf("%lld",&n);
	for(register int i=1;i<=n;++i) {
		for(register int j=1;j<=n;++j) {
			scanf("%lld",&a[i][j]);
			ans^=a[i][j];
			c[i][j]=judge(i,j);
		}
	}
	//按贪心解法操作进行大模拟
	for(register int i=2;i<=n;++i) {
		for(register int j=1;j<=n;++j) {
			if(c[i-1][j]%2==0) work(i,j);
		}
	} 
	printf("%lld\n",ans);
	return ;
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve(); //多组数据 
	return 0;
}
```



---

## 作者：Sword_K (赞：0)

[题目链接](https://codeforces.com/problemset/problem/1628/C)

提供一个比较憨，但不需要 $n$ 是偶数的限制的手玩构造方法。

首先有两个 trick ：

- 并不需要真的还原棋盘，可以利用已知信息直接求答案，即用一些格子表示出整张棋盘的异或和。

- 将棋盘黑白染色（国际象棋棋盘的样子）后，黑色格子和白色格子是独立的，可以分开计算。

于是就可以快乐地手推了。

这种题一般要么推成递归的形式，要么直接推出通解，前者一般要简单一点。

这里就不展示我推的心路历程了，主要解释我的图。

 ![img](https://cdn.luogu.com.cn/upload/image_hosting/0exqu9fi.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000) 

 ~~没错，我菜到手推了 $n = 16$ 的才找出规律~~

 红色格子是选了的格子，黄色格子是没有选的格子，蓝色格子是需要满足相邻格子中有奇数个红色格子的格子。

 可以发现如果把第一行第一列去掉，那么递归的形式可以表述为红蓝相间一圈后黄蓝相间一圈，这里的一圈是两行两列的。

 但这样归纳的话边界情况比较麻烦，不妨让整张棋盘在右下角扩展一行一列，颜色为黄蓝相间。 设 A = “黄蓝一圈，红蓝一圈”， B = “红蓝一圈，黄蓝一圈”，递归形式为：ABAB...

这样做的话，边界就只需要判断当前递归的矩形是否合法即可。

~~或许你发现了，这个做法更适合用来解决 $n$ 是奇数的情况，不过偶数也能做而已~~

[代码](https://codeforces.com/contest/1628/submission/162043385)

---

## 作者：FiraCode (赞：0)

[【题目链接】](https://luogu.com.cn/problem/CF1628C)

## 题解思路：
若能找到一个 $(i , j)$ 集合，表示只取 $a_{i,j}$ 时，原矩阵的每个元素的贡献都足 $1$，那么答案就是 $a_{i , j}$ 的异或和，用 $c_{i , j}$ 来表示 $a_{i,j}$ 取不取，取为 $1$，不取为 $0$。

我们第一行随便赋值 $c_{1,i}$，我们统一赋值成 $1$ 然后从第二行开始从上往下扫描，对于当前位置 $(i , j)$，我们的目标是让 $a_{i - 1 , j}$ 的贡献为 $1$ 即：

$$c_{i - 2,j} \oplus c_{i - 1 , j - 1} \oplus c_{i - 1}{j + 1} \oplus c_{i , j} = 1$$

这样就得到了 $c_{i,j}$。

不过现在还要证明 $a_{n,i}$ 的贡献为 $1$。

考虑现在还有一个合法方案 $c_{i , j}$ $'$，我们逐一比较求得的 $c_{1 , j}$ 与 $c_{1,j}$ $'$，如果不一样，则修改 $c_{1 , i}$ $'$，然后一次修改受影响的 $c_{i , j}$ $'(i > 1)$，整个过程保证 $a_{i , j}$ $'$ 的贡献仍然为 $1$。可以发现后两行一定是修改 $(n - 1 , n - i) , (n - 1 , n - i + 2) , (n , n - i + 1)$，则最后一行 $a_{i,j}$ $'$ 的贡献不变

## AC Code:
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream> 
#include <algorithm>
using namespace std;
const int N = 1010;
int a[N][N] , c[N][N];
void solve () {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i)  
        for (int j = 1; j <= n; ++ j)
            cin >> a[i][j];
    for (int i = 1; i <= n; ++ i) c[1][i] = 1;//先把c[1][i]初始化成1
    for (int i = 1; i <= n; ++ i) c[i][n + 1] = 0;
    for (int i = 2; i <= n; ++ i) 
        for (int j = 1; j <= n; ++ j) {
            c[i][j] = c[i - 2][j] ^ c[i - 1][j - 1] ^ c[i - 1][j + 1] ^ 1;
        }
    int ans = 0;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            if (c[i][j])
                ans ^= a[i][j];
    cout << ans << endl;
}
int main() {
    int T;
    cin >> T;
    while (T --) solve();
    return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

#### 题意
$t$ 组询问给一个 $n\times n$ 的网格图 $a$ ，每个格点表示另一个大小相同的网格图（下面称为原网格图）上与对应位置四相连的格点的异或和，求原网格图的异或和。  
$1 \leq t \leq 100, 2 \leq n, \sum n \leq 1000, 0 \leq a_{i, j} \leq 2^{30} - 1$ 。  
#### 题解
解法好像有很多，那天赛后发出来很多奇形怪状看不懂又很震撼的代码。  
我这种感觉比较好理解：  
首先考虑所有 $a$ 格点的异或和，在原网格图 $b$ 中，对这个异或和贡献了奇数次的点只有边上一圈，以 $8 \times 8$ 为例，我们求出了黑色部分的异或和：  
[![](http://icypigeon.cf/wp-content/uploads/2022/01/wp_editor_md_ab5a9592ce4bddccb3657f4c91ab55f3.jpg)](http://icypigeon.cf/wp-content/uploads/2022/01/wp_editor_md_ab5a9592ce4bddccb3657f4c91ab55f3.jpg)  
我们对中间红色圈内部的异或和考虑能否用类似的结构，发现除了黑色部分贡献了奇数次以外，剩余的部分和 $6 \times 6$ 的原问题等价，也就是用中间红色圈内部的异或和异或上黑色部分的异或和，得到了下图红色部分的异或和：  
[![](http://icypigeon.cf/wp-content/uploads/2022/01/wp_editor_md_fc9b0702edcef82f9b34751ab407bc22.jpg)](http://icypigeon.cf/wp-content/uploads/2022/01/wp_editor_md_fc9b0702edcef82f9b34751ab407bc22.jpg)  
反复这个操作，直到 $4 \times 4$ 的小格子，发现除了两条对角线部分以外的点的异或和按圈分组全都求出来了。  
下面考虑对角线的答案，比较简单，以 $8 \times 8$ 网格图的主对角线为例，不难发现，将下图黑色部分的 $a$ 异或起来，就是主对角线的异或和：  
[![](http://icypigeon.cf/wp-content/uploads/2022/01/wp_editor_md_a29658b7f399dcb29b58bfe37c3995d8.jpg)](http://icypigeon.cf/wp-content/uploads/2022/01/wp_editor_md_a29658b7f399dcb29b58bfe37c3995d8.jpg)  
副对角线类似处理，就做完了。  

#### code

```cpp
// global:
const int maxn = 1e3 + 10;
int a[maxn][maxn];
int s[maxn][maxn];
int n;
inline void init() {
    rep(i,1,n) rep(j,1,n) s[i][j] ^= s[i][j - 1];
    rep(j,1,n) rep(i,1,n) s[i][j] ^= s[i - 1][j];
}
inline int sum(int x1, int y1, int x2, int y2) {
    return s[x2][y2] ^ s[x1 - 1][y2] ^ s[x2][y1 - 1] ^ s[x1 - 1][y1 - 1];
}
// main:
cin >> n;
rep(i,1,n) rep(j,1,n) cin >> a[i][j], s[i][j] = a[i][j];
init();
int ans = 0;
for(int i = 1, lst = 0; i < (n >> 1); ++ i) {
	lst ^= sum(i, i, n - i + 1, n - i + 1);
	ans ^= lst;
}
rep(i,1,n) rep(j,1,n)
	if((i + j < n + 1 && i % 2 && j % 2) || (i < j && i % 2 && j % 2 == 0)) ans ^= a[i][j];
cout << ans << endl;
```

---

