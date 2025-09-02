# [USACO19OPEN] Left Out S

## 题目描述

Farmer John 正在尝试给他的牛群拍照。根据以往的经验，他知道这一工作往往结果不怎么样。

这一次，Farmer John 购买了一台昂贵的无人机，想要拍一张航拍照。为了使照片尽可能好看，他想让他的奶牛们在拍照时都朝向同一个方向。奶牛们现在在一块有围栏的草地上排列成 $N \times N$（$2 \leq N \leq 1000$）的方阵，例如：

```
RLR
RRL
LLR
```

这里，字符 `R` 表示一头朝右的奶牛，字符 `L` 表示一头朝左的奶牛。由于奶牛们都挤在一起，Farmer John 没办法走到某一头奶牛面前让她调转方向。他能做的只有对着某一行或某一列的奶牛喊叫让她们调转方向，使得被叫到的这一行或列内的所有 `L` 变为 `R`，`R` 变为 `L`。Farmer John 可以对任意多的行或列发号施令，也可以对同一行或列多次发令。

就如同 Farmer John 想象的，他发现他不可能让他的奶牛们都朝向同一个方向。他最多能做的是让所有奶牛中除了一头之外都朝向相同的方向。请找出这样的一头奶牛。


## 说明/提示

在这个例子中，位于第 $1$ 行第 $1$ 列（左上角）的奶牛是那头令人讨厌的奶牛，因为 Farmer John 可以喊叫第 $2$ 行和第 $3$ 列来让所有奶牛都面向左侧，只有这一头奶牛面向右侧。

## 样例 #1

### 输入

```
3
RLR
RRL
LLR```

### 输出

```
1 1```

# 题解

## 作者：Lolierl (赞：31)

USACO银组题目，照例还是比较灵活、巧妙的。

题意：一个01矩阵，每次翻转一行或一列，最后除了一个元素之外的其他元素完全一样，求这个元素。

乍一看似乎没什么思路。怎么下手呢？

首先我们注意到，0和1是对称的，也就是说因为不限次数，只需把每一行翻转一遍就可以把元素01互换。

于是我们先把第一行和第一列翻转成0。

方法：对于第一行中的1，翻转它所在的列；对于第一列中的1，翻转它所在的行。

于是我们得到了一个新矩阵：(以5*5为例）

![](https://cdn.luogu.com.cn/upload/pic/65228.png)

于是我们发现：在不改变第一行和第一列的情况下，蓝色部分无法被改变（因为两次翻转同一行等于没有翻转）。

若有解，则解只有以下三种位置：（1，1）、第一行或第一列（除（1，1）外）、蓝色区域中

若答案在蓝色区域中，目标位置此时一定为1并且其他部分全部为0

若答案在（1，1），则蓝色区域一定此时全部为1（翻转第一行再翻转第一列后，图中只有（1，1）为0）

若答案在第一行或第一列（除（1，1））上，则目标位置所在列或行在蓝色区域中一定全部为1且蓝色区域其他部分全部为0（翻转该列或行后，图中只有目标位置为1）

若不符合这三种情况，则无解

（感性理解一下没有其他情况吧qwq，蒟蒻也不会严谨证明啊）

于是我们就愉快地做完了

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector> 
#define pii pair<int, int>
using namespace std; 

int main()
{
	int n; 
	scanf("%d", &n); 
	if(n == 1){printf("-1"); return 0; }
	
	char c; 
	int a[n + 1][n + 1]; 
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		{
			c = getchar(); 
			while(c != 'L' && c != 'R')c = getchar(); 
			a[i][j] = ((c == 'L') ? 0 : 1); 
		}
	
	for(int i = 1; i <= n; i++)
		if(a[i][1])
			for(int j = 1; j <= n; j++)
				a[i][j] ^= 1; 
	
	for(int i = 2; i <= n; i++)
		if(a[1][i])
			for(int j = 1; j <= n; j++)
				a[j][i] ^= 1; 
	//翻转			
	int f = 0; 
	for(int i = 2; i <= n; i++)
		for(int j = 2; j <= n; j++)
			f += a[i][j]; 
	//通过子矩阵和判断情况
	if(f == (n - 1) * (n - 1))
	{
		if(n == 2)printf("-1\n"); else printf("1 1\n"); 
		return 0; 
	}
	else if(f == 1)
	{
		for(int i = 2; i <= n; i++)
			for(int j = 2; j <= n; j++)
				if(a[i][j]){printf("%d %d", i, j); return 0; }
	}
	else if(f == n - 1)
	{
		for(int i = 1; i <= n; i++)
		{
			int s = 0; 
			for(int j = 1; j <= n; j++)
				s += a[i][j]; 
			if(s == n - 1){printf("%d %d", i, 1); return 0; }
		}
		for(int i = 1; i <= n; i++)
		{
			int s = 0; 
			for(int j = 1; j <= n; j++)
				s += a[j][i]; 
			if(s == n - 1){printf("%d %d", 1, i); return 0; }
		}
	}//三种情况
	printf("-1"); 
	return 0; 
} 
```
有错误请指出qwq

---

## 作者：Rainybunny (赞：11)

( 本文也作$8.15$考试题解, 附[题目链接](https://www.luogu.org/problemnew/solution/P5427) )  
一道有趣的题$w$.  
为方便理解, 我们把方向化为一个$01$矩阵.
# $O(n^3)$解法
这是考场上的思路, 应该是最优秀的非正解算法吧, 可惜没有实现.  
首先, 明确一条结论:  
- 在任意两个时刻翻转同一行或同一列是没有意义的.  

我们枚举"令人讨厌的奶牛"的位置, 设为$(r,c)$, 并首先进行会改变$(r,c)$的操作. ( 四种情况: 不改变; 改变行; 改变列; 同时改变行列 ).  
此时, $(r,c)$必须固定不动了 ( 上文结论 ), 设其现在的值为$k$, 则除$(r,c)$外, 矩阵上所有的值应变为$!k$.  
考虑第$r$行, 由于不能改变$(r,c)$, 就不能翻转该行. 那么, 该行上所有未变为$!k$的位置都需要通过翻转其所在列修正. 同理, 第$c$列上所有未变为$!k$的位置都需要通过翻转其所在行修正. 现将第$r$行和第$c$列的位置按上述方式修正.  
考虑任意被修正的一行 ( 列 ), 若该行 ( 列 ) 存在位置的值不为$!k$, 那么必须翻转其所在列 ( 行 ) 修正 ( 上文结论 ).  
如此反复修正, 可以以队列保存所有未满足条件的位置, 得到一个类似$BFS$的$checker$, 由于有意义的修正至多$2n$次 ( 上文结论 ), 该函数复杂度为$O(n)$, 程序复杂度$O(n^2\times n)=O(n^3)$.
# $O(n^2)$解法
首先, 我们把矩阵变为这样:  
![trans5.PNG](https://i.loli.net/2019/08/15/orW14JBmZDPTjG5.png)  
让第一行和第一列变为$0$, 这里采用最暴力的方法: 行上的$1$翻转所在列, 列上的$1$翻转所在行.  
此时对于答案所在区域分类讨论:  
1. 答案是$(1,1)$:  
此时, 完成操作后, 矩阵应为:  
![trans1.PNG](https://i.loli.net/2019/08/15/47exmsNFoZSKufj.png)  
但是我们已经强行将$(1,1)$变为$0$, 所以利用完成的矩阵回推:  
![trans2.PNG](https://i.loli.net/2019/08/15/CobxPlQqX2IFaVj.png)  
故, 当答案是$(1,1)$时, 右下方$?$矩阵应全是$1$.

2. 答案在第一行或第一列, 但不是$(1,1)$:  
不妨令答案在第一行, 则完成的矩阵应为:  
![trans3.PNG](https://i.loli.net/2019/08/15/wQi5KMHNW3v7efS.png)  
同理, 回推出$?$矩阵:  
![trans4.PNG](https://i.loli.net/2019/08/15/v6z5RwWUHPM7Qqd.png)  
故, 此时$?$矩阵中应有一列或一行全为$1$, 其余全为$0$.

3. 答案在$?$矩阵中:  
显然此时$?$矩阵中有且仅有答案位置为$1$, 其余全为$0$.

若不满足以上情况, 则必然无解, 问题就解决了.  
提供一下$AC$代码:
```cpp
#include <cstdio>

#define Int register int

const int MAXN = 1000;
int n;
bool mp[MAXN + 5][MAXN + 5] = {};

inline void Work () {
	scanf ( "%d", &n );
	for ( Int i = 1; i <= n; ++ i ) {
		static char s;
		for ( Int j = 1; j <= n; ++ j ) {
			s = getchar ();
			if ( s ^ 'L' && s ^ 'R' ) {
				-- j; continue;
			}
			mp[i][j] = s == 'L';
		}
	}
	for ( Int i = 1; i <= n; ++ i ) { // 第一行置0 
		if ( mp[1][i] ) {
			for ( Int j = 1; j <= n; ++ j ) {
				mp[j][i] ^= 1;
			}
		}
	}
	for ( Int i = 1; i <= n; ++ i ) { // 第一列置0 
		if ( mp[i][1] ) {
			for ( Int j = 1; j <= n; ++ j ) {
				mp[i][j] ^= 1;
			}
		}
	}
	int s = 0;
	for ( Int i = 2; i <= n; ++ i ) {
		for ( Int j = 2; j <= n; ++ j ) {
			s += mp[i][j];
		}
	}
	if ( s == ( n - 1 ) * ( n - 1 ) ) { // 情况1 
		puts ( n == 2 ? "-1" : "1 1" );
		return ;
	}
	if ( s == 1 ) { // 情况2 
		for ( Int i = 2; i <= n; ++ i ) {
			for ( Int j = 1; j <= n; ++ j ) {
				if ( mp[i][j] ) {
					printf ( "%d %d\n", i, j );
					return ;
				}
			}
		}
	}
	if ( s == n - 1 ) { // 情况3 
		for ( Int i = 2; i <= n; ++ i ) {
			static int s; s = 0;
			for ( Int j = 2; j <= n; ++ j ) {
				s += mp[i][j];
			}
			if ( s == n - 1 ) {
				printf ( "%d 1\n", i );
				return ;
			} else if ( s ) {
				break;
			}
		}
		for ( Int j = 2; j <= n; ++ j ) {
			for ( Int i = 2; i <= n; ++ i ) {
				static int s; s = 0;
				for ( Int i = 2; i <= n; ++ i ) {
					s += mp[i][j];
				}
			}
			if ( s == n - 1 ) {
				printf ( "1 %d\n", j );
				return ;
			} else if ( s ) {
				break;
			}
		}
	}
	puts ( "-1" );
}

int main () {
//	freopen ( "transitioning.in", "r", stdin );
//	freopen ( "transitioning.out", "w", stdout );
	Work ();
	return 0;
}
```

---

## 作者：45dino (赞：8)

提供一个比较有趣的思路。

为了表述方便，下文将 `L` 称为 `0`，`R` 称为 `1`。

如果只观察其中一个 $2\times 2$ 的子矩阵，发现每次操作会更改其中的**偶数**个元素。

所以这个子矩阵能被操作成全部都相同当且仅当其中有偶数个 `1`。

推广到 $n\times n$ 的矩阵，该矩阵能通过操作变得全部都相同当且仅当所有 $2\times 2$ 的子矩阵都有偶数个 `1`。具体可以把这个 $n\times n$ 的矩阵“缩”成 $(n-1)\times(n-1)$ 的矩阵（称为“代表矩阵”）。举个例子：

```
n=4

1011
0011
0011
0011

 ||
 ||
_  _
\  /
 \/
 
100
000
000
```
其中“代表矩阵”的每一个单元格对应原矩阵一个 $2\times 2$ 的子矩阵。如果是 $1$ 说明子矩阵 $1$ 的个数是奇数个。 

可以发现一个规律：**大多数**原矩阵的位置都会被包含在 $4$ 个 $2\times 2$ 的子矩阵内，但有些是只被 $2$ 个或 $1$ 个包含。（想一想，为什么） 

在原问题中，要先反转一位，使得修改过的矩阵满足条件，考虑转换为“代表矩阵”，因为这样更容易判断是否满足条件，即全是 $0$。

如果直接枚举原矩阵修改了哪一位，然后通过“代表矩阵”进行判断的话，复杂度为 $\Theta(n^4)$，所以要研究每次修改在代表矩阵的对应情况。

对于这个原矩阵的修改 $(x,y)$，在“代表矩阵”中修改了所有包含 $(x,y)$ 的子矩阵。

因为代表矩阵的目标状态是全是 $0$，所以把代表矩阵中 $1$ 的位置拎出来，只有三种情况：
- “代表矩阵”中有 $1$ 个位置是 $1$。那么得修改这个 $1$ **且不能影响到其他 $0$**，所以这个 $1$ 只能在角上，修改这个角即可。如果不在角上就是无解。
- “代表矩阵”中有 $2$ 个位置是 $1$。同上，结论是要相邻且在边上。
- **有 $4$ 个位置是 $1$**。结论是必须是在一块的（形成一个 $2\times 2$ 的矩形）

其他情况都是无解。

[code](https://paste.ubuntu.com/p/F9w9r2Rrjd/)

---
Update on 2021/9/20: 重写了一遍，因为以前的代码被 $Hack$ 了。（悲）

Update on 2022/1/7: 有人反映剪贴板挂了，似乎是被我手残删除了/ll

---

## 作者：chihik (赞：5)

为了书写方便，我们将$'L'$表示为0，$'R'$表示为1。

现在题目转化为给你一个01矩阵，每次可将一行或一列的01反转，要求最后只有一个1或只有一个0，问能否办到。

现在，我们将第一行和第一列的元素全变为1（0也可以），这个很好办到，翻转第一行的元素就将该元素所在列翻转，列同理。

经过以上操作之后，我们会得到这样一个矩阵：

![1.PNG](https://i.loli.net/2019/08/15/A7JS2C1sgBDGceF.png)

我们可以将答案分为三部分讨论，即红色部分，紫色部分，黄色部分。

1.如果答案在红色区域，为了使它和第1行，第1列不同，我们需要将第1行，第1列各翻一次，得到这样一个矩阵：

![2.PNG](https://i.loli.net/2019/08/15/M6i5hRmcfDSs7Cd.png)

那么显然，黄色部分必须全为1。

***

2.如果答案在黄色区域，那么黄色区域只能有且仅有1个1。这时整个图也只有1个1。

3.如果答案在紫色区域，那么黄色区域只能有且仅有1行或1列1，这样就可以交换一次得到。

4.如果上述三种情况不满足，输出-1。

注意2,3要求仅有，可以用tot记录判断或者用标记。

程序中的$check1,2,3$分别对应情况1，2，3。

标程：
```cpp
#include <cstdio>

const int MAXN = 1000;
int n, x , y;
bool state[ MAXN + 5 ][ MAXN + 5 ];

void operation( int x , bool f ) {	//将一行或一列取反
	if( f )
		for( int i = 1 ; i <= n ; i ++ )
			state[ x ][ i ] = !state[ x ][ i ];
	else
		for( int i = 1 ; i <= n ; i ++ )
			state[ i ][ x ] = !state[ i ][ x ];
}
void update( int xx , int yy ) {	//更新答案
	if( xx < x || ( xx == x && yy < y ) )
		x = xx , y = yy;
}
bool check1( ) {
	for( int i = 2 ; i <= n ; i ++ )
		for( int j = 2 ; j <= n ; j ++ )
			if( state[ i ][ j ] == 0 ) return 0;
	return 1;
}
bool check2( ) {
	x = 1005 , y = 1005;
	bool f = 1;
	for( int i = 2 ; i <= n ; i ++ )
		for( int j = 2 ; j <= n ; j ++ )
			if( state[ i ][ j ] == 1 ) {
				if( f )
					f = 0 , x = i , y = j;
				else
					return 0;
			}
	return !f;
}
bool check3( ) {
	x = 1005 , y = 1005;
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 2 ; j <= n ; j ++ ) {
			if( !state[ i ][ j ] ) break;
			if( j == n ) 
				update( i , 1 );
		}
	for( int j = 1 ; j <= n ; j ++ )
		for( int i = 2 ; i <= n ; i ++ ) {
			if( !state[ i ][ j ] ) break;
			if( i == n ) 
				update( 1 , j );
		}
	return ( x == 1005 || y == 1005 ) ? 0 : 1; 
}

int main( ) {
	//freopen("transitioning.in","r",stdin);
	//freopen("transitioning.out","w",stdout);
	
	scanf("%d",&n);
	char c;
	for( int i = 1 ; i <= n ; i ++ ) {
		getchar( );
		for( int j = 1 ; j <= n ; j ++ )
			scanf("%c",&c) , state[ i ][ j ] = c == 'L' ? 0 : 1;
	}
	for( int i = 1 ; i <= n ; i ++ )
		if( state[ i ][ 1 ] ) operation( i , 1 );
	for( int i = 1 ; i <= n ; i ++ )
		if( state[ 1 ][ i ] ) operation( i , 0 );
	
	if( check1( ) ) printf("1 1\n");
	else if( check2( ) ) printf("%d %d\n",x,y);
	else if( check3( ) ) printf("%d %d\n",x,y); 
	else printf("-1\n");
	return 0;
}
```


---

## 作者：whiteqwq (赞：3)

[P5427 [USACO19OPEN]Left Out S](https://www.luogu.com.cn/problem/P5427)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1752915)

## 题意
- 给定一个$n\times n$的矩阵，可以给每一行取反，每一列取反。
- 如果可以让所有的数相同或者不能让只有一头奶牛与其他奶牛方向不同，那么输出$-1$。
- 否则输出行列最小的这头奶牛位置。

## 分析

提供一种好写又好想的暴力。

如果没有这样的奶牛，那么我们通过让行取反操作一定可以让所有的行相同。同样如果没有这样的奶牛，我们也可以通过列取反操作让所有的列相同。

考虑用$\text{bitset}$保存每一行每一列的奶牛朝向信息，我们可以暴力判断相邻的两行（注意$1$和$n$相邻）是否相同或者取反后相同。

同样的，我们可以对每一列进行这样的判断。

那么我们要求的奶牛位置肯定会让它所在的行列和它相邻的行列无法匹配，我们暴力找这样的位置就好了。

如果有多个这样的位置记得输出$-1$。

时间复杂度：$O(n^2)$。

## 代码
```
#include<stdio.h>
#include<iostream>
#include<bitset>
using namespace std;
const int maxn=1005;
int n,flg;
int ok1[maxn],ok2[maxn];
string s;
bitset<maxn>a[maxn],b[maxn],c[maxn],d[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=1;j<=n;j++){
			if(s[j-1]=='L')
				a[i][j]=b[j][i]=0,c[i][j]=d[j][i]=1;
			else a[i][j]=b[j][i]=1,c[i][j]=d[j][i]=0;
		}
	}
	a[0]=a[n],b[0]=b[n],c[0]=c[n],d[0]=d[n];
	a[n+1]=a[1],b[n+1]=b[1],c[n+1]=c[1],d[n+1]=d[1];
	for(int i=0;i<=n;i++){
		if(a[i]==a[i+1]||a[i]==c[i+1])
			ok1[i]=0;
		else ok1[i]=1;
	}
	for(int i=0;i<=n;i++){
		if(b[i]==b[i+1]||b[i]==d[i+1])
			ok2[i]=0;
		else ok2[i]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(ok1[i-1]+ok1[i]+ok2[j-1]+ok2[j]==4)
                flg++; 
    if(flg!=1){
	    puts("-1");
        return 0;
    }
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(ok1[i-1]+ok1[i]+ok2[j-1]+ok2[j]==4)
                printf("%d %d\n",i,j);
	return 0;
}
```

---

## 作者：Zenith_Yeh (赞：3)

首先我们可以易证：对奶牛的命令的顺序对最终的状态是没有影响的，所以可以通过这一点发现(并且最终都朝右和都朝左是等价的)。

### 第一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/di5ugj7l.png)

如上情况是我们可以先一行一行的命令使第一列都变为 $L$，变成如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/sbbdlhh8.png)

现在我们发现如果第一行的第二、三个反转一下的话，就可已达成条件。意味着第一行的奶牛(除了第一个)都需要反转，那我们将第一行反转一下变成如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/opctmbq0.png)

此时只有 $(1,1)$ 需要反转，即答案为 $(1,1)$。

### 第二种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/4l0ffqj1.png)

如上情况是我们可以先一行一行的命令使第一列都变为 $L$，变成如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/yqsyb1r1.png)

现在我们发现如果第一行的第三个反转一下的话，就可已达成条件。所以此时只有 $(1,3)$ 需要反转，即答案为 $(1,3)$。

#### 上菜：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,now_x,now_y,dl[1000005],cnt;
char c[1005][1005];
int main()
{	//freopen("leftout.in","r",stdin);
	//freopen("leftout.out","w",stdout);
	cin>>n;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			cin>>c[i][j];
	for(register int i=1;i<=n;++i)
		if(c[i][1]=='R')//现将第一列都变为L。
			for(register int j=1;j<=n;++j)//反转。
			{	if(c[i][j]=='L')c[i][j]='R';
				else if(c[i][j]=='R')c[i][j]='L';
			}
	for(register int j=2;j<=n;++j)
	{	int cnt_l=0,cnt_r=0;
		for(register int i=1;i<=n;++i)//看此时这一列L和R分别由多少个。
			if(c[i][j]=='L')cnt_l++;
			else if(c[i][j]=='R')cnt_r++;
		if(cnt_l==n||cnt_r==n)continue;//这一列以满足。
		if(cnt_l==1)//这一列剩一个与其他的不一样，记录一下。
		{	for(register int i=1;i<=n;++i)
				if(c[i][j]=='L')
				{	now_x=i;
					now_y=j;
					dl[++cnt]=i;
					ans++;
					break;
				}
		}
		else if(cnt_r==1)//同理。
		{	for(register int i=1;i<=n;++i)
				if(c[i][j]=='R')
				{	now_x=i;
					now_y=j;
					dl[++cnt]=i;
					ans++;
					break;
				}
		}
	}
	if(ans==1)//如果记录的只有一个，即为第二种情况，输出。
	{	cout<<now_x<<' '<<now_y;
		return 0;
	}
	for(register int i=2;i<=cnt;++i)//如果不止一个，则看看它们是不是均在一行。
		if(dl[i]!=dl[i-1])
		{	cout<<-1;
			return 0;
		}
	if(cnt==n-1)//如果这一行除了第一个均需要反转，则就是第一种情况，输出这一行的第一个的坐标。
	{   cout<<dl[1]<<' '<<1;
	    return 0;
	}
	cout<<-1;//如果均不满足，输出-1。
	return 0;
}

```


---

## 作者：BreakPlus (赞：2)

一道不错的思维题。

做这题我们需要做这几步：

+ 第一步：翻转直到第一行第一列都变成 ``L``。

首先枚举第一行，如果发现第一行有 ``R`` 那么反转整列。

然后枚举第一列，如果发现第一列有 ``R`` 那么反转整行。

+ 第二步：寻找答案。

分情况讨论：

$\qquad$ 第一种情况：除第一行和第一列全部是  ``R``：答案为 ``1 1``。自己尝试翻转一下就知道了。

$\qquad$ 第二种情况：除第一行和第一列有一行和一列全是 ``R``：如果是行就输出 ``i 1``（$i$ 是全为 ``R`` 的一行），列就是 ``1 j``。


$\qquad$ 第三种情况：翻转后只剩一个 ``R``，它所在的位置就是答案。

$\qquad$ 其他情况：无解

+ 第三步：码码码。


[点击下载代码](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/sxgz4b7c)
```cpp
#include<cstdio>
using namespace std;
const int maxn=1010;
int n,a[maxn][maxn];char s[maxn][maxn];
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
}//读入
void gotoa()
{
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++) if(s[i][j]=='R') a[i][j]=1;//把s转换为数字
}
void change(int i,int x)
{
	if(x==1)
	{
		for(int d=1;d<=n;d++) a[i][d]=(!a[i][d]);
	}else{
		for(int d=1;d<=n;d++) a[d][i]=(!a[d][i]);
	}//反转一行或一列
}
void mfl()
{
	for(int i=1;i<=n;i++) if(a[1][i]) change(i,2);
	for(int i=2;i<=n;i++) if(a[i][1]) change(i,1);//翻转直至第一行第一列变成L
}
void press_output()
{
	int sum=0;
	for(int i=2;i<=n;i++)
	    for(int j=2;j<=n;j++) sum+=a[i][j];//获取R的数量
	if(sum==(n-1)*(n-1))
	{puts("1 1");return;}//第一种情况
	if(sum==1)
	{
		for(int i=2;i<=n;i++)
		    for(int j=2;j<=n;j++)
		    if(a[i][j]) {printf("%d %d\n",i,j);return;}
	}//第二种情况
	if(sum==n-1)
	{
		for(int i=2;i<=n;i++)
		{
			int tmp=0;
			for(int j=2;j<=n;j++) tmp+=a[i][j];
			if(tmp==n-1)
			{
				printf("%d 1\n",i);
				return;
			}
		}//如果一行全是R
		for(int i=2;i<=n;i++)
		{
			int tmp=0;
			for(int j=2;j<=n;j++) tmp+=a[j][i];
			if(tmp==n-1)
			{
				printf("1 %d\n",i);
				return;
			}
		}//如果一列全是R
	}//第三种情况
	puts("-1");//无解
}
int main()
{
	read();//读入
	gotoa();//转换
	mfl();//翻转
	press_output();//判断并输出
	return 1-1;//orz
}
```

---

## 作者：Jayun (赞：1)

# 题目大意：

有 $n\cdot n$ 头牛，有的牛朝左边，有的牛朝右边，可以将某一行或某一列的奶牛全部往后转（即朝左的向右，朝右的向左），现在让所有奶牛中除了一头之外都朝向相同的方向，请找出这样的一头奶牛。

# 正文：

## 举例：

直接这么推会比较难，那就把思路倒过来，假设捣乱的那头牛的位置在 $[1,1]$，因为方便我就设 L 为 $1$，R 为 $0$：

```
011
111
111
```

就像这样，除了那头牛，其他的牛都往一个方向看。如果我们要把上面的 01 矩阵变为样例的，应该怎么变？

很容易，因为一个操作是将某一行或一列取反，那某一行**和**某一列的交叉处，就是**不更改**方向的牛。既然这样，那把上面的 01 矩阵变为样例的，可以这样：

```
   ↓
 011       010
→111   →   001
 111       110
```

其实可以发现，样例矩阵把每一个第一个数是 $0$ 的行取反（第一行除外），再把每一个第一个数是 $0$ 的列取反（第一列除外），就能得到原先的 01 矩阵。

## 解决问题:

那我们换一个想法，将样例矩阵的每一个第一个数是 $1$ 的行取反，再把每一个第一个数是 $1$ 的列取反，会怎样呢？

最终的 01 矩阵是这样：

```
000
011
011
```

可以发现除了第一行和第一列，其他数字都是 $1$，根据这个特性，就能解答这题了。

答案分为三种类型：

1. 捣乱的牛在左上角，即 $[1,1]$。
2. 捣乱的牛在第一行或第一列（左上角除外），即 $[1,x]$ 或 $[x,1] (1<x\leq n)$。
3. 其他。

第二和第三种的最终 01 矩阵分别是：

```
000
010
010
(第二种，[1,2])
```

可以发现第二种类型有 $(n-1)$ 个 $1$。

```
000
001
000
(第三种，[2,3])
```

可以发现捣乱的牛所在的位置就是 $1$，其他都是 $0$。

# 代码：

```cpp
const int N = 1010;

int n;
int a[N][N], b;

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		char c;
		c = getchar();
		while(c != 'L' && c != 'R')
			c = getchar();
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = c=='L'?1:0;
			c = getchar();
		}
	}
	for (int i = 1; i <= n; i++)
		if(a[i][1])
			for (int j = 1; j <= n; j++)
				a[i][j] ^= 1;
				
	for (int i = 2; i <= n; i++)
		if(a[1][i])
			for (int j = 1; j <= n; j++)
				a[j][i] ^= 1;
	for (int i = 2; i <= n; i++)
		for (int j = 2; j <= n; j++)
			b += a[i][j];
	if(b == (n-1) * (n-1))
	{
		if(n == 2) puts("-1");
		else puts("1 1");
		return 0;
	}
	if(b == 1)
	{
		for (int i = 2; i <= n; i++)
			for (int j = 2; j <= n; j++)
				if(a[i][j])
				{
					printf("%d %d", i, j);
					return 0;
				}
	}
	if(b == n-1)
	{
		int c = 0;		
		for (int i = 1; i <= n; i++)
		{
			c = 0;
			for (int j = 1; j <= n; j++)
				c += a[i][j];
			if(c == b) 
			{
				printf("%d 1", i);
				return 0;
			}
		}
		c = 0;		
		for (int i = 1; i <= n; i++)
		{
			c = 0;
			for (int j = 1; j <= n; j++)
				c += a[j][i];
			if(c == b) 
			{
				printf("1 %d", i); 
				return 0;
			}
		}
	}
    return 0;
}



```

---

## 作者：crashed (赞：1)

# Updates

经 @liqingyacng 提醒，修复了代码当中的实现错误。

# 题目
[点这里](https://www.luogu.org/problem/P5427)看题目。
# 分析
对于这种 $01$ 方阵带操作的问题，我们~~理所应当地~~应该首先想到规范某一行，然后再进行其它操作。  
  
（经验不足，同时在时间分配上有问题）    
  
以下假设 $L$ 代表 $0$，$R$ 代表 $1$。  
  
我们先假定一个目标颜色，也就是想要方阵中较多的颜色都是这种颜色，以下就用$0$。根据经验，我们先仅对列进行操作，把最后一行全部变成 $0$。  
  
为了找到一个最小的答案，我们从上到下，从左到右遍历这个方阵。如果我们发现某一行中**较少的颜色**（不是非目标颜色哦，可以行翻转的）只有一个，那么我们就可以认为这个位置为暂定答案。如果我们发现一行中较少的颜色不止一个，就说明这个方阵没救了。如果我们发现有两行都满足较少的颜色只有一个，也说明这个方阵没救了。如果我们最后发现所有行颜色统一，那么这个方阵可以被统一，没救。   
  
以上的东西可以用 $O(n^2)$ 判定。    

> upt: 实际上我们做的事情不止有判定，也有找出答案位置的过程。如果某一行两种颜色都只有一个，应该还有选择靠前一个的过程。

但是现在会有一个问题——如果答案在最后一行里面肿么办呢？最后一行已经被翻好了呀！    

只需要另选一行规范后检查即可。一个答案不可能同占两行。    
  
所以总的时间是 $O(n^2)$。  

# 代码 
```cpp
#include <cstdio>
#include <cstring>

const int MAXN = 1005;

template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
    while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
    return a < b ? a : b;
}

int N, x, y;
char s[MAXN];
bool board[MAXN][MAXN], side[MAXN][MAXN];

bool chk( const int base )
{
    memcpy( side, board, sizeof( board ) );
    for( int i = 1 ; i <= N ; i ++ )
        if( side[base][i] )
            for( int j = 1 ; j <= N ; j ++ )
                side[j][i] ^= 1;
    int cnt0 = 0, cnt1 = 0, dif = 0;
    int less;
    for( int i = 1 ; i <= N ; i ++ )
    {
        if( i == base ) continue;
        cnt0 = cnt1 = 0;
        int fir0 = -1, fir1 = -1;
        for( int j = N ; j ; j -- )
        {
            cnt0 += ! side[i][j];
            cnt1 += side[i][j];
            if( side[i][j] ) fir1 = j;
            else fir0 = i;
        }
        if( ! MIN( cnt0, cnt1 ) ) continue;
        if( MIN( cnt0, cnt1 ) > 1 ) return false;
        dif ++;
        if( dif > 1 ) return false;
        less = cnt0 < cnt1 || ( cnt0 == cnt1 && fir0 < fir1 ) ? 0 : 1;
        for( int j = 1 ; j <= N ; j ++ )
            if( side[i][j] == less )
                x = i, y = j;
    }
    return dif;
}

int main()
{
    read( N );
    for( int i = 1 ; i <= N ; i ++ )
    {
        scanf( "%s", s + 1 );
        for( int j = 1 ; j <= N ; j ++ )
        {
            board[i][j] = ( s[j] == 'R' );
        }
    }
    if( N == 1 ) return puts( "1 1" ), 0;
    if( chk( N ) )
        write( x ), putchar( ' ' ), write( y ), putchar( '\n' );
    else if( chk( 1 ) )
        write( x ), putchar( ' ' ), write( y ), putchar( '\n' );
    else puts( "-1" );
    return 0;
}
```

---

## 作者：PPL_ (赞：0)

~~上午考试又双叒叕炸了~~

[题目传送](https://www.luogu.org/problem/P5427)

刚开始也没什么思路，于是就是爆搜(反正我就26pts)，各种搜索+玄学剪枝可能会更多，但是考场上搜索的都没AC

这里就不展开，毕竟既不能AC，而且大家都会

下面提到的人自动理解为奶牛，因为我做的题就是人。。。

下面开始讲大佬的思路：

![](https://cdn.luogu.com.cn/upload/pic/72265.png )

上面的表是为了方便理解

我们先考虑把他们全部转换为L或R

那么如果要转换，c1这一列的元素与相邻的c2的元素应该全部相同或全部不相同

否则就是有问题

枚举每一列和每一行，统计**相邻的**相同和不同的个数 (没读懂多读几遍，相信你)

如果两个计数的都大于了1，不可能了，就算有人调皮也不止一个，直接-1走你

如果其中一个为0，那么暂时不管，接着走

否则其中一个为1，先记录这一对小伙子，其中之一必有调皮的人

如果已经记录过一对小伙子了，那么比较他们是否有相同的一个人，如果没有，-1走你，有就可以不管了

反复进行这种操作，行比较了之后比较列，直到所有的都比较完了之后，如果只有一对小伙子，-1走你，毕竟你不知道哪个是调皮的人

如果有两对以上，输出相同的就行了

如果有多种情况的怎么办？

通过在考场上手推，**只存在n=2时有多种情况**，其余都不可能，特判一下就好了

**毕竟我也是听了之后理解了写的，代码可能不止一点丑，如果理解了最好自己写，我的代码可能看着头大**

```cpp
//12252024832524
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define Min(x,y) (x<y?x:y)
#define Max(x,y) (x>y?x:y)
using namespace std;

typedef long long LL;
const int MAXN = 1005;
int n;
bool a[MAXN][MAXN],S;

int Read()
{
	int x1 = 0,f1 = 1;char c1 = getchar();
	while(c1 > '9' || c1 < '0'){if(c1 == '-')f1 = -1;c1 = getchar();}
	while(c1 >= '0' && c1 <= '9'){x1 = (x1*10) + (c1^48);c1 = getchar();}
	return x1 * f1;
}
char gc()
{
	char c = getchar();
	while(c != 'L' && c != 'R')c = getchar();
	return c;
}
void fuyi()
{
	printf("-1");
	exit(0);
}
bool same(int x1,int y1,int x2,int y2)
{
	if(x1 == x2 && y1 == y2)
		return 1;
	return 0;
}

int main()
{
//	freopen("transitioning.in","r",stdin);
//	freopen("transitioning.out","w",stdout);
	n = Read();
	for(int i = 1;i <= n;++ i)
		for(int j = 1;j <= n;++ j)
			if(gc() == 'R')
			{
				a[i][j] = 1;
				S ^= 1;
			}
	if(n == 1)
	{
		printf("1 1");
		return 0;
	}
	if(n == 2)
	{
		if(S)
			printf("1 1");
		else
			printf("-1");
		return 0;
	}
	if(!(n & 1) && !(S & 1))
	{
		printf("-1");
		return 0;
	}
	int x = 0,y = 0;
	int ly,ry;
	int s[2],t = 0;
	int ybx[10] = {},yby[10] = {};
//	puts("---r---");
	for(int i = 1;i < n;++ i)
	{
		s[0] = s[1] = 0;
		for(int j = 1;j <= n;++ j)
		{
			if(a[i][j] == a[i+1][j])
			{
				s[0]++;
				ly = j;
			}
			else
			{
				s[1]++;
				ry = j;
			}
		}
		if(s[0] > 1 && s[1] > 1)
			fuyi();
		if(!s[0] || !s[1])
			continue;
		if(s[0] == 1)
		{
			if(t == 4)
				t = 2;
			ybx[++t] = i;
			yby[t] = ly;
			ybx[++t] = i+1;
			yby[t] = ly;
			if(t == 4)
			{
				if(same(ybx[1],yby[1],ybx[3],yby[3]) || same(ybx[1],yby[1],ybx[4],yby[4]) || same(ybx[2],yby[2],ybx[4],yby[4]) || same(ybx[2],yby[2],ybx[3],yby[3]) )
					continue;
				else
					fuyi();
			}
		}
		if(s[1] == 1)
		{
			if(t == 4)
				t = 2;	
			ybx[++t] = i;
			yby[t] = ry;
			ybx[++t] = i+1;
			yby[t] = ry;
			if(t == 4)
			{
				if(same(ybx[2],yby[2],ybx[3],yby[3]) || same(ybx[2],yby[2],ybx[4],yby[4]) || same(ybx[1],yby[1],ybx[4],yby[4]) || same(ybx[1],yby[1],ybx[3],yby[3]) )
					continue;
				else
					fuyi();
			}
		}
	}
//	puts("---c---");
	for(int i = 1;i < n;++ i)
	{
		s[0] = s[1] = 0;
		for(int j = 1;j <= n;++ j)
		{
			if(a[j][i] == a[j][i+1])
			{
				s[0]++;
				ly = j;
			}
			else
			{
				s[1]++;
				ry = j;
			}
		}
		if(s[0] > 1 && s[1] > 1)
			fuyi();
		if(!s[0] || !s[1])
			continue;
		if(s[0] == 1)
		{
			if(t == 4)
				t = 2;
			ybx[++t] = ly;
			yby[t] = i;
			ybx[++t] = ly;
			yby[t] = i+1;
			if(t == 4)
			{
				if(same(ybx[2],yby[2],ybx[3],yby[3]) || same(ybx[2],yby[2],ybx[4],yby[4]) || same(ybx[1],yby[1],ybx[4],yby[4]) || same(ybx[1],yby[1],ybx[3],yby[3]))
					continue;
				else
					fuyi();
			}
		}
		if(s[1] == 1)
		{
			if(t == 4)
				t = 2;
			ybx[++t] = ry;
			yby[t] = i;
			ybx[++t] = ry;
			yby[t] = i+1;
			if(t == 4)
			{
				if(same(ybx[2],yby[2],ybx[3],yby[3]) || same(ybx[2],yby[2],ybx[4],yby[4]) || same(ybx[1],yby[1],ybx[4],yby[4]) || same(ybx[1],yby[1],ybx[3],yby[3]))
					continue;
				else
					fuyi();
			}
		}
	}
	
	if(t < 3)
		fuyi();
	if(same(ybx[2],yby[2],ybx[3],yby[3]) || same(ybx[2],yby[2],ybx[4],yby[4]))
		printf("%d %d",ybx[2],yby[2]);
	else if(same(ybx[1],yby[1],ybx[4],yby[4]) || same(ybx[1],yby[1],ybx[3],yby[3]))
		printf("%d %d",ybx[1],yby[1]);
//	puts("---end---");
	return 0;
}
```


---

## 作者：wyl_AC (赞：0)

这道题，分析题意，大概就是一个01表格，要将其转化为只有一个为1或只有一个为0的情况，无限次取反，每次只能取反一行或一列，求那个不同的点的位置，且必须最前面的那个。
那么简单分析题意后，就应该知道全取反一遍也可以，所以L和R的意义差不多。

要求最前面那个的话，那么最后一行我们可以先暴力列取反为一样的，
那么前面的少数的如果只有一个，那么他一定是答案，而如果有两个那么一定无解。
因为如果再次进行列取反，那么会导致最后一行混乱。

并且，可以看出选用其他行对全局影响一致，如果担心最后一行也有，那么换一行再来一边就行了，不过好像没有这种数据。（我换成用倒数第二行当起点还是对了，可以查我提交记录）
```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
#define LL long long
#define M 1005
void read(LL &x){
	x=0;LL f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')
			f=-f;
		c=getchar();
	} 
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	x*=f;
	return ;
}
LL n,mp[M][M];
int main(){
	//freopen("transitioning.in","r",stdin);
	//freopen("transitioning.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++){
		char c;
		for(int j=1;j<=n;j++){
			c=getchar();
			if(c=='R')
				mp[i][j]=1;
		}
		if(i<n)
			c=getchar();
	}
	for(int i=1;i<=n;i++){
		if(mp[n][i])
			for(int j=1;j<=n;j++){
				mp[j][i]=1-mp[j][i];
			}
	}
	LL a,b;
	bool f=0,s=0;
	LL tp=0;
	for(LL i=n-1;i>0;i--){
		LL l=0,r=0;
		LL u=0,v=0;
		for(LL j=n;j>0;j--){
			if(mp[i][j])
				r++,u=j;
			else
				l++,v=j;
		}
		if(r&&l)
			tp++;
		if(tp>=2)
			s=1;
		if(r>1&&l>1){
			s=1;
			break;
		}else if(r==1||l==1){
			a=i;
			if(r<l)
				b=u;
			else
				b=v;
			f=1;
		}
	}
	if(s||!f)
		puts("-1");
	else
		printf("%lld %lld",a,b);
	return 0; 
}
```


---

## 作者：Singercoder (赞：0)

做法基本都和正解一样，这里特别说一下思考过程。

首先应该容易想到的暴力做法是枚举每个位置，将其选为特殊点并更改(0->1 or 1->0)，然后问题就转化为了判断当前矩阵能否通过一系列翻转得到一个全部为0的矩阵。

既然要求全部为0，那只要将为1的部分全部翻转掉即可；依照这样的思路，我们可以想到分别枚举每一行，如果行首元素为1则翻转；然后对每一列做同样的检查+翻转即可，总复杂度是$n^4$。

由此考虑优化：如果不枚举特殊点，那做完上述操作后特殊点会不会自己显现出来呢？

答案是会的，在令第一行和第一列都为0后，分如下三种可能：

1. 如果剩余部分全部为1，则特殊点为(1,1)。

2. 如果剩余部分有一行或一列全部为1，则特殊点为对应行或列的首个元素。

3. 如果剩余部分中只有一个1，则它就是特殊点。
4. 否则无解。

显然涵盖了所有情况，这样的思考过程也相对自然些。

注意判断的顺序，先判(1,1)能保证n=2时的答案正确。

```cpp
#include<bits/stdc++.h>

#define gc() getchar()

#define ri register int

inline int read()
{
	ri ret=0;char ch=gc();
	while(!isdigit(ch))ch=gc();
	while(isdigit(ch))
	{
		ret=ret*10+ch-'0';
		ch=gc();
	}
	return ret;
}

const int MAXN=1e3+10;

int n;
char c[MAXN][MAXN];
int a[MAXN][MAXN];
int s[MAXN][MAXN];

int main()
{
//	freopen("1.in","r",stdin);
	
	n=read();
	for(ri i=1;i<=n;++i)
	{
		scanf("%s",c[i]+1);
		for(ri j=1;j<=n;++j)a[i][j]=c[i][j]=='R';
	}
	
	for(ri i=1;i<=n;++i)if(a[i][1])
		for(ri j=1;j<=n;++j)a[i][j]^=1;
	for(ri j=1;j<=n;++j)if(a[1][j])
		for(ri i=1;i<=n;++i)a[i][j]^=1;
	
	for(ri i=1;i<=n;++i)
		for(ri j=1;j<=n;++j)
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];//二维前缀和方便判断
	
	ri delta=s[n][n]-s[1][n]-s[n][1]+s[1][1],x=0,y=0;//预处理判别式方便分类
	if(delta==(n-1)*(n-1)){x=1;y=1;}
	else if(delta==n-1)
	{
		for(ri i=1;i<=n;++i)if(s[i][n]-s[i-1][n]==n-1){x=i;y=1;}
		for(ri j=1;j<=n;++j)if(s[n][j]-s[n][j-1]==n-1){x=1;y=j;}
	}
	else if(delta==1)
	{
		for(ri i=1;i<=n;++i)
			for(ri j=1;j<=n;++j)if(a[i][j]){x=i;y=j;break;}
	}
	
	if(!x)printf("-1\n");
	else printf("%d %d\n",x,y);
	
	return 0;
}
```



---

