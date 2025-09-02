# The Evil Temple and the Moving Rocks

## 题目描述

Important: All possible tests are in the pretest, so you shouldn't hack on this problem. So, if you passed pretests, you will also pass the system test.

You are an adventurer currently journeying inside an evil temple. After defeating a couple of weak monsters, you arrived at a square room consisting of tiles forming an $ n×n $ grid, surrounded entirely by walls. At the end of the room lies a door locked with evil magical forces. The following inscriptions are written on the door:

 The sound of clashing rocks will awaken the door!Being a very senior adventurer, you immediately realize what this means. In the room next door lies an infinite number of magical rocks. There are four types of rocks:

- '^': this rock moves upwards;
- '<': this rock moves leftwards;
- '>': this rock moves rightwards;
- 'v': this rock moves downwards.

To open the door, you first need to place the rocks on some of the tiles (one tile can be occupied by at most one rock). Then, you select a single rock that you have placed and activate it. The activated rock will then move in its direction until it hits another rock or hits the walls of the room (the rock will not move if something already blocks it in its chosen direction). The rock then deactivates. If it hits the walls, or if there have been already $ 10^{7} $ events of rock becoming activated, the movements end. Otherwise, the rock that was hit becomes activated and this procedure is repeated.

If a rock moves at least one cell before hitting either the wall or another rock, the hit produces a sound. The door will open once the number of produced sounds is at least $ x $ . It is okay for the rocks to continue moving after producing $ x $ sounds.

The following picture illustrates the four possible scenarios of moving rocks.

- Moves at least one cell, then hits another rock. A sound is produced, the hit rock becomes activated. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/e59337ab587cdbd312be54b98490f9dd41771d7b.png)
- Moves at least one cell, then hits the wall (i.e., the side of the room). A sound is produced, the movements end. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/c851677c9f0333311db78372cd0f7a39ffa6d87e.png)
- Does not move because a rock is already standing in the path. The blocking rock becomes activated, but no sounds are produced. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/c66c40007af71e8e53cf79ddc8cdd98e93f6d4dd.png)
- Does not move because the wall is in the way. No sounds are produced and the movements end. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/cc4822df065eca79c7f861576c809682dbd03809.png)

Assume there's an infinite number of rocks of each type in the neighboring room. You know what to do: place the rocks and open the door!

## 说明/提示

Here's a simulation of the first example, accompanied with the number of sounds produced so far.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/993406596a8a9d2174b87998a59e0de263168fa6.png) 0 sound  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/b35282721e4af0a10d08ab1a78c0f07e1070b1ab.png) 1 sound  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/ab195786b1f075b2dea28b2ce43b3c8a652b5402.png) 2 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/ca56c629d5cdddddcb6d12b51e02f1bbb53818d4.png) 3 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/de9249ae306be70d11ecaaf2ef1c74c2c830e965.png) 4 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/6ebca45731d036edba59b18dc824f53a3538bd23.png) still 4 sounds In the picture above, the activated rock switches between the '^' rock and the '<' rock. However, no sound is produced since the '^' rock didn't move even a single tile. So, still 4 sound.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/01e80bfbe73cce15e24d09cbfa6668f94e0a4d77.png) 5 sounds At this point, 5 sound are already produced, so this solution is already correct. However, for the sake of example, we will continue simulating what happens.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/0e90e3332608eaa6aff1cdf25b2e9cbf4f28970b.png) 6 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/23837a3b87bcf845e820a5cd4ea38533148b7e0a.png) 7 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/531092411052672c8c8a68c14289ed1d95d42f7e.png) still 7 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/964734e8afeb0b85aaaeee1f6f71f9f03ec4f5dc.png) 8 sounds And the movement stops. In total, it produces 8 sounds. Notice that the last move produced sound.

Here's a simulation of the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/228f1e59c6313428337f4ca8d5beee2d44d5dc0b.png) 0 sound  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/f1858e1b5f4d00ad15cd32166d7ec7c3df4920e3.png) 1 sound  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/a96837bf11495f1f735decb970e12cdb49ee1c50.png) 2 sounds Now, the activated stone will switch continuously from one to another without producing a sound until it reaches the $ 10^{7} $ limit, after which the movement will cease.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/cb118e148b6ce5c1e286426601b934f8d8e94470.png)In total, it produced exactly 2 sounds, so the solution is correct.

## 样例 #1

### 输入

```
5 5
```

### 输出

```
>...v
v.<..
..^..
>....
..^.<
1 1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
>vv
^<.
^.<
1 3
```

# 题解

## 作者：Kazeno_Akina (赞：1)

[更好的阅读体验](https://www.luogu.com.cn/blog/IceNirvana/solution-cf329d)

感觉是相当精妙的构造题。

对于两个小样例大概是随便手玩就行的~~考虑复制样例~~。因此重点讨论最大的样例，即 $n=100$ 并有 $x=10^5$ 这个样例。

* 以下约定 $k=\dfrac{n}{2}$

考虑到整个网格放满了也就只有 $10^4$ 个石头，达不到要求的响声次数，所以必然要考虑的是，如何重复利用一块石头。

考虑做一个能自己循环动的东西。于是经过一些人类智慧，我们获得了一个用两行发出大概 $k^2$ 次响声的做法：考虑将第一行的前 $k$ 个全填上 `>`，后 $k-1$ 个由 `.` 和 `>` 交替；第二行首先输出 `^`，然后 $k-1$ 个由 `.` 和 `<` 交替，最后 $k$ 个输出 `<`。

在左下角启动整张图的运动，那么这张图中每两行都会自己循环 $k$ 次然后触发上面那一组的运动。

这样去做在整张图里就可以大概跑到 $k^3-k^2$ 次响声，显然可以通过。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,x;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >> n >> x,k=(n>>1);
	if(n==5){
		cout << ">...v\nv.<..\n..^..\n>....\n..^.<\n1 1";
		return 0;
	}
	if(n==3){
		cout << ">vv\n^<.\n^.<\n1 3";
		return 0;
	}//以上是针对样例特判，下面才是重点
	for(int i=1;i<=k;++i){
		for(int j=1;j<=k;++j) cout << '>';
		for(int j=1;j<k;++j){
			if(j&1) cout << '.';
			else cout << '>';
		}
		cout << "v\n^";
		for(int j=2;j<=k;++j){
			if((k-j)&1) cout << '<';
			else cout << '.';
		}
		for(int j=1;j<=k;++j) cout << '<';
		cout << '\n';
	}
	cout << n << ' ' << 1;
	return 0;
}
```

---

## 作者：moonbowqwq (赞：1)

[题目链接](https://codeforces.com/problemset/problem/329/D)

~~这题咋弱这么多。~~

## 题意简述

有一个 $n \times n$ 的网格和无限的石头，整个网格被墙包围。石头有以下四种类型：

- `^` 型：这种石头会向上运动；
- `v` 型：这种石头会向下运动；
- `<` 型：这种石头会向左运动；
- `>` 型：这种石头会向右运动。

你可以在每个格子上摆放任意石头，但是每个格子上最多只能放一个。摆放完之后你需要选择一个石头并激活它。被激活的石头将开始运动，直到撞上墙或者另一块石头，然后停下来。如果它撞到了另一块石头，被撞到的石头将开始运动。如果总撞击次数达到 $10^7$ 次，石头也停止运动。  
如果一块石头停止运动前移动了至少一个格子，那么它将会发出一次声音。  
现在请你构造一个方案，使所有石头在停止运动之前至少发出了 $x$ 次声音。

## 解题思路

考虑这样一个结构：

```
>>>.>.>.v
^.<.<.<<<
```

我们设第一行从左到右有 $x$ 个连续的字符 `>`，设模式串为 `>.`，对第一行跑一遍 KMP 后的匹配数是 $y$，那么我们从 $(1, 1)$ 开始跑，除掉最后一次撞墙的次数，总的响的次数是 $x \times y$。

那么我们尝试围绕这个结构来进行构造，例：

```
n = 10, 从 (1, 1) 出发

>>>>>>.>.v
.v.<.<<<<<
^>>>>>.>.v
.v.<.<<<<<
^>>>>>.>.v
.v.<.<<<<<
^>>>>>.>.v
^v.<.<<<<<
^>>>>>.>.v
^..<.<<<<<
```

具体说说这个结构吧，已知输入的数字 $n$，那么我们设 $k = \frac{n}{2}$，对于最左边的那一列，从下到上重复 $\frac{n}{2}$ 次 `^`，在这之后，一直交替重复 `^`、`.` 即可。然后对于每行的第 $2$ 到第 $n$ 个，一半是重复的 `>` 或 `<`，一半是交替重复的 `.` 和 `<` 或 `>`，然后对于每一行的第二个字符或结尾，改为 `v` 即可。

当然我还学到一种构造方法，比较相似但不完全相同（感谢 lyx %%%）：

```
n = 10, 从 (1, 1) 出发

>>>>>.>.>v
^.<.<.<<<<
v<.<.<<<<<
>>>>.>.>.^
>>>>>.>.>v
^.<.<.<<<<
v<.<.<<<<<
>>>>.>.>.^
>>>>>.>.>v
^.<.<.<<<<
```

拆分开来可以看做是两种结构不断重复：

```
>>>>.>.v
^<.<.<<<
```

```
>>>>.>.v
^<.<.<<<
```

对于每种结构，第一行都会有连续的 $x$ 个 `>` 或 `<`，然后第二行有连续的 $x - 1$ 个 `>` 或 `<`，其余的差不多，可以直接观察看一下。

假设 $n$ 为二的倍数，$x = \frac{n}{2}$，那么其发出的响声次数就为：

$$(2x^2 - x) \times \lfloor \frac{x}{2} \rfloor$$

也是能稳过的。

## 代码实现

第二个构造的代码就不贴了吧，懒得改代码了 qwq。

```
#include <bits/stdc++.h>

using namespace std;

int k;

char stone[305][305];

void solve1(){
  int n = k, x = k >> 1;
  for(int i = n - x + 1; i <= n; ++i)
    stone[i][1] = '^';
  for(int i = n - x; i > 0; i -= 2)
    stone[i][1] = '.', stone[i - 1][1] = '^';
  stone[1][1] = '>';
  ++x;
  for(int i = 1; i <= x; ++i){
    for(int j = 1; j <= n; j += 2)
      stone[j][i + 1] = '>';
    for(int j = 2; j <= n; j += 2)
      stone[j][n - i + 1] = '<';
  }
  for(int i = x + 1; i < n; ++i){
    char c1 = (i - x) & 1 ? '.' : '>';
    char c2 = (i - x) & 1 ? '.' : '<';
    for(int j = 1; j <= n; j += 2)
      stone[j][i + 1] = c1;
    for(int j = 2; j <= n; j += 2)
      stone[j][n - i + 1] = c2;
  }
  for(int j = 1; j <= n; j += 2){
    stone[j][n - 1] = stone[j + 1][3] = '.';
    stone[j][n] = stone[j + 1][2] = 'v';
  }
  stone[n][2] = '<';
  for(int i = 1; i <= k; ++i)
    printf("%s\n", stone[i] + 1);
  printf("1 1");
  return;
}

int main(){
  int x;
  scanf("%d%d", &k, &x);
  solve1();
  return 0;
}
```

---

## 作者：xyf007 (赞：1)

要在 $100 \times 100$ 的网格内发出 $10^5$ 次声音，一个很自然的想法就是形成循环。因此我们要让它**循环多次**，且**每一次循环发出多次声音**，即 `>>>.>.>.v` 型。  
而有关形成大循环的部分，可以上下蛇形来回绕，具体方案如下（官方做法）：
```
1 copy of
v<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v>v^
24 copies of
v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.
v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^
24 copies of
v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^
.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^.^
1 copy of
>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^
....................................................................................................
1 1
```
~~我自己的做法是尝试从边长为 $\sout{4}$ 的正方形开始，一圈绕完之后跳到边长为 $\sout{6}$ 的正方形直到边长为 $\sout{100}$ 的正方形，但是这样只有 $\sout{84549}$ 次，无法通过。~~

---

## 作者：LTb_ (赞：0)

考虑一种宽 1 列，长 $3k + 2$ 行的单元，大概长下面这个样子

```
v
v
v
.
v
.
v
.
v
.
>
```

先是 $k$ 个连续的 `v`，然后是 $k$ 个间隔一格的 `v`，最后是一个 `>` 或者 `<`。

我们把它当作一个黑盒来看待——这个单元从最上面输入一个信号，从最下面输出一个信号，每次做出 $k+1$ 的贡献。并且，这个单元只能被“使用” $k$ 次。

于是自然地想到，把这个单元从左到右堆叠 $n$ 次，把最后一个单元输出的信号返回给第一个单元。

然后冷静分析一下这种构造的总贡献。每个单元每次做 $33$ 的贡献，一共循环 $32$ 次，一共 $100$ 个单元，贡献是 $33 \times 32 \times 100 = 105600$，能过。

放一下 Generator 的代码。

```c++
// 2021.8.8
// Code by LTb
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ll long long
#define debug printf("Passing Line %d in function [%s].\n",__LINE__,__FUNCTION__)
#define fi first
#define se second
inline int read(){
	int x=0,f=1;
	char ch;
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return f*x;
}
inline void chmax(int &x,int y){x=max(x,y);}
inline void chmin(int &x,int y){x=min(x,y);}

const int MOD = 998244353;
inline int add(int x,int y){return(x+y>=MOD)?(x+y-MOD):((x+y<0)?(x+y+MOD):(x+y));}

const int MAXN = 105;
int n = 100;
char a[MAXN][MAXN];

signed main()

{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = '.';

	int k = 32;
	
	for (int i = 1; i <= k; i++)
		a[i][1] = 'v';

	for (int i = k + 2; i <= n - 1; i += 2)
		a[i][1] = 'v';

	a[n][1] = '>';

	k = 31;
	for (int j = 2; j <= n - 1; j++) {
		if (j % 2 == 0) {
			for (int i = n; i >= n - k + 1; i--)
				a[i][j] = '^';

			for (int i = n - k - 1; i >= 3; i -= 2)
				a[i][j] = '^';

			a[2][j] = '>';
		} else {
			for (int i = 2; i <= k + 1; i++)
				a[i][j] = 'v';

			for (int i = k + 3; i <= n - 2; i += 2)
				a[i][j] = 'v';

			a[n][j] = '>';
		}
	}

	k = 32;
	for (int i = n; i >= n - k + 1; i--)
		a[i][n] = '^';

	for (int i = n - k - 1; i >= 3; i -= 2)
		a[i][n] = '^';

	for (int i = 2; i <= n; i++)
		a[1][i] = '<';

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << a[i][j];
		cout << '\n';
	}
	return 0;
}
```

碎碎念：提答构造真是太好玩了（

---

