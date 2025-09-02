# [ABC111D] Robot Arms

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc111/tasks/arc103_b

すぬけ君の工場では，次のような特徴を持つ **ロボットアーム** を導入することになりました：

- ロボットアームは，$ m $ 個の **腕** と $ m+1 $ 個の **関節** からなる．腕には $ 1 $, $ 2 $, ..., $ m $ で，関節には $ 0 $, $ 1 $, ..., $ m $ で番号が付けられている．腕 $ i $ は関節 $ i-1 $ と関節 $ i $ をつなぐ．腕 $ i $ の長さは $ d_i $ である．
- 各腕には，それぞれ独立に **モード** を指定することができる．モードは `L`, `R`, `D`, `U` のいずれかであり，腕のモードはその腕の向きを指定する．工場を座標平面とみなすと，関節 $ i $ の座標 $ (x_i,\ y_i) $ は次のように定まる：
  - $ (x_0,\ y_0)\ =\ (0,\ 0) $．
  - 腕 $ i $ のモードが `L` のとき，$ (x_i,\ y_i)\ =\ (x_{i-1}\ -\ d_{i},\ y_{i-1}) $．
  - 腕 $ i $ のモードが `R` のとき，$ (x_i,\ y_i)\ =\ (x_{i-1}\ +\ d_{i},\ y_{i-1}) $．
  - 腕 $ i $ のモードが `D` のとき，$ (x_i,\ y_i)\ =\ (x_{i-1},\ y_{i-1}\ -\ d_{i}) $．
  - 腕 $ i $ のモードが `U` のとき，$ (x_i,\ y_i)\ =\ (x_{i-1},\ y_{i-1}\ +\ d_{i}) $．

すぬけ君は，腕のモードをうまく指定することにより，$ N $ 個の点 $ (X_1,\ Y_1),\ (X_2,\ Y_2),\ ...,\ (X_N,\ Y_N) $ のいずれにもロボットアームの関節 $ m $ をちょうど一致させられるようなロボットアームを導入したいです． このようなことは可能でしょうか？ 可能ならば，条件を満たすロボットアームおよび，各点 $ (X_j,\ Y_j) $ にそのロボットアームの関節 $ m $ を到達させるためのモードの指定方法を求めてください．

## 说明/提示

### 制約

- 入力はすべて整数である
- $ 1\ \leq\ N\ \leq\ 1000 $
- $ -10^9\ \leq\ X_i\ \leq\ 10^9 $
- $ -10^9\ \leq\ Y_i\ \leq\ 10^9 $

### 部分点

- $ 300 $ 点分のテストケースでは，$ -10\ \leq\ X_i\ \leq\ 10 $ および $ -10\ \leq\ Y_i\ \leq\ 10 $ が成り立つ．

### Sample Explanation 1

それぞれの $ (X_j,\ Y_j) $ にロボットアームの関節 $ m $ を到達させる方法において，各関節の位置は次のようになります． - $ (X_1,\ Y_1)\ =\ (-1,\ 0) $ に到達させる方法では，まず関節 $ 0 $ の位置は $ (x_0,\ y_0)\ =\ (0,\ 0) $ です．腕 $ 1 $ のモードが `R` なので，関節 $ 1 $ の位置は $ (x_1,\ y_1)\ =\ (1,\ 0) $ です．腕 $ 2 $ のモードが `L` なので，関節 $ m=2 $ の位置は $ (x_2,\ y_2)\ =\ (-1,\ 0) $ です． - $ (X_2,\ Y_2)\ =\ (0,\ 3) $ に到達させる方法では，$ (x_0,\ y_0)\ =\ (0,\ 0),\ (x_1,\ y_1)\ =\ (0,\ 1),\ (x_2,\ y_2)\ =\ (0,\ 3) $ です． - $ (X_3,\ Y_3)\ =\ (2,\ -1) $ に到達させる方法では，$ (x_0,\ y_0)\ =\ (0,\ 0),\ (x_1,\ y_1)\ =\ (0,\ -1),\ (x_2,\ y_2)\ =\ (2,\ -1) $ です．

### Sample Explanation 3

$ (X_j,\ Y_j) $ の中に同じ点が含まれることもあります．

## 样例 #1

### 输入

```
3
-1 0
0 3
2 -1```

### 输出

```
2
1 2
RL
UU
DR```

## 样例 #2

### 输入

```
5
0 0
1 0
2 0
3 0
4 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
2
1 1
1 1```

### 输出

```
2
1 1
RU
UR```

## 样例 #4

### 输入

```
3
-7 -3
7 3
-3 -7```

### 输出

```
5
3 1 4 1 5
LRDUL
RDULR
DULRD```

# 题解

## 作者：CYJian (赞：19)

先考虑判断不合法：

如果对于两个点，$x+y$ 的奇偶性不相同，则一定不合法。因为从 $(0, 0)$ 走到 $(x,y)$，至少需要长度为 $x+y$ 的机械臂。若机械臂增长，则需要保证延长出去的要能收回来。也就是说，你多往左走一格，也就需要再往右走回去一格。这样的话是不能改变奇偶性的。

那么现在我们就能判断出不能构造解的条件了。

若不存在不合法的情况，考虑如何构造：

注意到 $m$ 的限制大约是 $\log (x+y)$，则考虑倍增构造：

先考虑只有一个长度为 $1$ 的机械臂能干啥：

（下面用 `.` 描述的坐标系默认中心为原点）

```plain
...........
...........
...........
...........
.....#.....
....#.#....
.....#.....
...........
...........
...........
...........
```

然后再画出有 $1$ 和 $2$ 的能到达的格点：

（用 `&` 表示第一步 $2$ 到的点，然后 `#` 再表示第二步 $1$ 能到的点）

```plain
...........
...........
.....#.....
....#&#....
...#.#.#...
..#&#.#&#..
...#.#.#...
....#&#....
.....#.....
...........
...........
```

不难发现，这相当于是将 $1$ 的 $3 \times 3$ 的小方格复制了四份，以 `&` 为中心放在 $2$ 到达的 $4$ 个点上。

再加上 $4, 8, \ldots$ 也是同理。不难发现，加到 $2^{30}$ 就能满足题目的要求了。

考虑如何构造。

我们从大到小考虑每个机械臂。设当前到达的点为 $(nx, ny)$，目标点为 $(x, y)$。考虑当前这个机械臂沿着让 $x,y$ 坐标差值和最小的那个方向摆放。若有多个则可以随便摆放。不难发现，这样一定能构造出解。

$\rm Code$：

```cpp
int x[1010];
int y[1010];
int len[33];

int main() {
	int n = ri;
	for(int i = 1; i <= n; i++)
		x[i] = ri, y[i] = ri;
	int tmp = abs(x[1] + y[1]) & 1;
	for(int i = 1; i <= n; i++)
		if((abs(x[i] + y[i]) & 1) != tmp)
			return puts("-1"), 0;
	printf("%d\n1", 32 - tmp);
	len[1] = 1; int N = 1;
	if(tmp) {
		for(int i = 1; i <= 30; i++) printf(" %d", len[++N] = 1 << i);
		puts("");
	} else {
		for(int i = 0; i <= 30; i++) printf(" %d", len[++N] = 1 << i);
		puts("");
	} char s[40];
	memset(s, 0, sizeof(s));
	for(int i = 1; i <= n; i++) {
		ll nx = 0, ny = 0;
		for(int j = N; j; --j) {
			ll dx = x[i] - nx, dy = y[i] - ny;
			if(abs(dx) > abs(dy)) {
				if(dx > 0) nx += len[j], s[j] = 'R';
				else nx -= len[j], s[j] = 'L';
			} else {
				if(dy > 0) ny += len[j], s[j] = 'U';
				else ny -= len[j], s[j] = 'D';
			}
		} printf("%s\n", s + 1);
	}
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：10)

大概是给出了和cyj不同的另一种证明方法和另一种构造方式？但其实本质是一样的。
_____


首先无解很容易判断。因为多走一步和少走一步之间的差值总是 $2\times$步长 ，所以如果 $x_i+y_i$ 的奇偶性不同的话，就不能同时满足条件。

发现这个题的本质是拆分问题。那么大概可以引导到「二进制拆分」这种泛式的拆分方式上。不妨考虑对于一组 $\{1,2,4\cdots 2^k\}$ 可以拼出哪些坐标。那么考虑对于一组坐标 $(x,y)$ ，他可以被通达，那么可以知道如果想要减小某一维坐标，比如 $x\to x'$，那有两种情况：

1、只是单纯地拿掉几个元素。比如 $16\to11$ 就是简单地拆出 $4$ 和 $1$ 。

2、拿出几个元素并且换进去几个元素。比如 $12\to11$ 就是拆出 $2$ 和 $1$ 放进一个 $4$ 。

可以看出，这是可以相互通达的。

更详细一点。因为对于四个象限，情况都是等价的。所以只考虑第一象限。发现对于 $\{1,2,4\cdots 2^k\}$ ，它可以维护到的位置至少是所有 $|x+y|=\sum _{i=0}^k 2^i=2^{k+1}-1$。但是不仅限于此。发现如果将将其中某个元素的贡献取负，那么就可以访问到所有 $|x+y| - \sum 2^p$ 的格子。换句话说，这个方式可以访问到所有与 $2^{k+1}-1$ 奇偶性相同的格子。

到这一步就已经很完美了，但是依然存在问题。如果 $|x+y|$ 都是偶数，这就挂了。所以此时可以随便向 $x$ 轴或者 $y$ 轴偏移 $1$ ，比如把 $(1,0)$ 变换成原点，就解决了。

实现方面，发现最合法区域后是个内部镂空的菱形。找出来之后，对于一组坐标 $(x,y)$ ，考虑对称着找。反向从大到小枚举每一个步长，如果新的点的 $|x|+|y|$ 之和严格小于当前的步长，就是可以拼出来的。不难知道这样做是对的。 

```cpp
int n ;
int cnt ;
int _eve ;
ll nx, ny ;
int bc[N] ;
struct rg{
    int l ;
    int r ;
    int t ;
}base[N] ; //D  R  U  L
int dx[4] = {0, 1, 0, -1} ;
int dy[4] = {-1, 0, 1, 0} ;
char s[4] = {'U', 'L', 'D', 'R'} ;

int main(){
    cin >> n ;
    bc[0] = 1 ;
    for (int i = 1 ; i <= n ; ++ i){
        cin >> base[i].l >> base[i].r ;
        base[i].t = abs(base[i].l + base[i].r) & 1 ;
    }
    for (int i = 2 ; i <= n ; ++ i)
        if (base[i].t != base[1].t) return puts("-1"), 0 ;
    for (int i = 1 ; i <= 30 ; ++ i) bc[++ cnt] = 1 << i ;
    cout << cnt + 1 + (bool)(!(base[1].t & 1)) << '\n' ;
    if (!(base[1].t & 1)) cout << 1 << " " ;
    for (int i = cnt ; ~i ; -- i) printf("%d%c", bc[i], " \n"[!i]) ;
    for (int i = 1 ; i <= n ; ++ i){
        nx = base[i].l ;
        ny = base[i].r ;
        if (!(base[i].t & 1))
            ny -= 1, putchar('U') ;
		//cout << nx << " " << ny << endl ;
		for (int j = cnt ; ~j ; -- j){
            for (int k = 0 ; k < 4 ; ++ k){
                ll kx = nx + (ll)dx[k] * bc[j] ;
                ll ky = ny + (ll)dy[k] * bc[j] ;
                if (abs(kx) + abs(ky) < bc[j]){
                    nx = kx ; ny = ky ;
					//cout << nx << " " << ny << endl ;
                    printf("%c", s[k]) ; break ;
                }
			}
		}
        puts("") ;
    }
    return 0 ;
}

```



#  

---

## 作者：Hadtsti (赞：9)

~~本篇题解有其它题解都没有的正确性证明部分，希望大家能给个赞，谢谢！~~

### 题意简述

初始位置设置在 $(0,0)$，另给出 $n(1≤n≤1000)$ 组形如 $(x,y)(1\le |x|,|y|\le 10^9)$ 的目标坐标。要求构造长度为 $m$（$m$ 自定，但要求 $m≤40$）的“步长”序列  $c_1,c_2,\cdots,c_m$（$c_i$ 同样自定，要求 $c_i≤10^{12}$）。然后再对每一个目标坐标构造一个长度为 $m$ 的字符串（由 `L`、`R`、`U`、`D` 四种字符构成，分别表示左、右、上、下），使得从 $(0,0)$ 开始走，第 $i$ 步按字符串第 $i$ 个字符所示的方向走长度 $c_i$，在走 $m$ 步后恰好能够走到该组目标坐标。

### 题目分析

~~ARC 的 B 题竟然是个紫的，好家伙~~

十分神奇的构造题。先判断无解的情况：设某一步走之前的坐标是 $(x,y)$，走后的坐标是 $(x',y')$，那么就有 $x'+y'=x+y±c_i$，也就是说这一步走完后的四种情况的 $x+y$ 的奇偶性相同。又因为每一组坐标走的步数相同，因此若题目中给出的目标坐标两两之间 $x+y$ 的奇偶性不完全相同就说明无解。

那么如果坐标的 $x+y$ 奇偶性完全相同就一定有解吗？答案是肯定的。想必大家看到题目后都能够想到 $c_i$ 的构造与“进制拆分”有关（多少有点小学奥数题的感觉）。本题就可以采用二进制和三进制表示两种方式，但使用三进制不如二进制方便，而且得到的答案也稍劣，所以本人采用的是二进制拆分。

由于一个数 $x$ 的二进制表示是一定存在且唯一的，那么我们就有了这样的一个思路雏形：可以对 $x$ 的每一个为 $1$ 的二进制位分配一个对应的 $2$ 的幂。

但这样有两个问题：由于每一步必须走，但是 $x$ 和 $y$ 的二进制表示中对应的一位都是 $0$ 怎么办？如果 $x$ 和 $y$ 的二进制表示中某一位都是 $1$ 又怎么办？

所以我们换一种思路，反过来从 $(x,y)$ 向 $(0,0)$ 走。$c_i$ 直接取 $2^k,2^{k-1},\cdots,4,2,1(2^k\ge\max(x_i,y_i))$。特别地，如果 $x+y$ 都是偶数就再添上一个 $1$ 以保证最后能到达$(0,0)$。从最大的 $2^k$ 向小的扫，每次选择 $x,y$ 当中距离当前扫到的 $2$ 的幂更近的那个（即绝对值更大的），强行让它向 $0$ 的方向走这一步并更新它自己的值（如果原来是 $0$，那么向随便一个方向走就行，本文以正向为例），不断进行下去直到 $x$ 和 $y$ 减到 $0$ 即可。这样构造出来 $m=\lceil \log_2\max(x_i,y_i)\rceil+2\le32$，满足题意。

这种方法的正确性其他题解貌似一笔带过了，在这里我稍微说一下我的思路：对最后的 $c_m=1$（$x+y$ 为奇数）或者 $c_{m-1}=1$（$x+y$ 为偶数）操作完之后的 $(x_0,y_0)$ 进行分析。在这里我们不妨设 $x_0,y_0\ge0,|x_0|\ge|y_0|$（其他情况类似）。只要我们证明 $(x_0,y_0)=(0,0)$（$x_0+y_0$ 为奇数，直接得到答案）或者 $(1,0)$（$x_0+y_0$ 为偶数，再用一个 $1$ 就可以得到答案）即可。

使用反证法，分类讨论：

1. 若 $y_0=0$，但 $x_0>1$，那么反推操作之前的 $x_1,y_1$。若这一步是对 $y_1$ 进行操作，那么有 $y_1=\pm1$，则 $|y_1|=1<|x_1|$，与选择绝对值大的进行操作矛盾！因此这一步只能是对 $x_1$ 进行操作，即 $x_1=x_0\pm1$。若 $x_1=x_0-1$，由 $x_0>1$ 知 $x_1=x_0-1>0$，$x_1>0$ 应该 $-1$ 才对，矛盾！因此我们得到 $x_1=x_0+1>2$。那么再往前一步的 $x_2,y_2$ 仍然有 $y_2=0,x_2=x_1+2>4$（证明过程类似）以及 $y_3=0,x_3=x_2+4>8$……因此得到 $y_i=0,x_i>2^i$。考虑第一步操作，应有 $c_1=2^k\ge\max(|x|,|y|)$，然而由刚刚得到的结论却有 $x>2^k$，矛盾！因此这种情况不成立。

2. 若 $x_0\ge y_0\ge1$，那么类似上面的过程，由每次选择 $x,y$ 中绝对值更大的进行操作以及操作方向向 $0$ 两个性质，我们仍然可以得到每次操作满足 $x_{i+1}=x_i+2^i$ 或者 $y_{i+1}=y_i+2^i$。这样我们虽然不能确定 $x_i$ 和 $y_i$ 的具体大小范围，但是可以确定 $x_i+y_i\ge2^i+1$。那么仍然考虑最初的 $x,y$ 和 $2^k$，应有 $2^k\ge\max(|x|,|y|)$。但由刚刚的结论知 $x+y\ge2^{k+1}+1$，则有 $\max(|x|,|y|)\ge\frac{2^{k+1}+1}2>2^k$，矛盾！

综上，$(x_0,y_0)=(0,0)$ 或 $(1,0)$，即这种方法一定能够得到解，是正确的。具体细节看代码。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m;
long long x[1010],y[1010],c[42];
bool fg;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&x[i],&y[i]);
		k=max(k,max((int)log2(abs(x[i])-1),(int)log2(abs(y[i])-1))+1);//判断最大的 2^k 需要到多大 
		if(i==1) 
			fg=(x[i]+y[i])&1ll;//记录 x+y 的奇偶性 
		else if(((x[i]+y[i])&1ll)!=fg)//x+y 奇偶性不同，无解 
		{
			printf("-1");
			return 0;
		}
	}
	for(long long i=k;i>=0;i--)
		c[++m]=1ll<<i;//c[i] 直接取 2^k,2^(k-1)…4,2,1 
	if(!fg)//x+y 为偶数，再添加一个 1 
		c[++m]=1;
	printf("%d\n",m);
	for(int i=1;i<=m;i++)
		printf("%lld ",c[i]);
	printf("\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(abs(x[i])>abs(y[i]))//取绝对值更大的那个 
				x[i]>=0?(printf("R"),x[i]-=c[j]):(printf("L"),x[i]+=c[j]);//向 0 的方向走 
			else
				y[i]>=0?(printf("U"),y[i]-=c[j]):(printf("D"),y[i]+=c[j]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Felix72 (赞：3)

一个跟题解区所有做法都不一样的构造。

首先还是倍增构造，如果 $x + y$ 为奇数则设置 $c = \{1, 2, 4, \dots, 2^{30}\}$，否则在最前面添上一个 $1$。

然后不失一般性地，再假设 $x$ 和 $y$ 均为非负数（否则把构造的方案镜像一下就行了）。

然后就是一个非常厉害的构造：

我们用一个两行 $m$ 列的矩阵（元素为 ```+```，```-```，```.``` 当中的一种）表示方案。第一行对应 $x$ 轴，第二行对应 $y$ 轴。```+``` 表示 $R$ 或者 $U$ 方向，```-``` 表示 $L$ 或者 $D$ 方向，```.``` 表示此次操作与该维度无关。

比如序列 ```RRLRUDLR``` 就对应如下矩阵：

```txt
+ + - + . . - +
. . . . + - . .
```

定义矩阵每行的和为每个位置 $i$ 的符号（```+``` 代表 $+1$，```-``` 代表 $-1$，```.``` 代表 $0$）乘上对应的 $c_i$。

那么我们把 $x$ 和 $y$ 写成二进制数，其为 $1$ 的位在矩阵上是 ```+```，剩下的是 ```.```。这个矩阵满足两行对应的坐标是 $(x, y)$。但是还有问题，就是它不保证每一列恰好有一个元素是 ```.```，因此不能转化为 ```LRUD``` 序列的形式，于是我们考虑通过调整使得矩阵每行的和不变，且每列恰有一个元素是 ```.```。

直接构造无从下手，我们需要先考虑简单变换：

1. 自己往右移，留下一个相反元素：
   ```+``` $\to$ ```- +```，```-``` $\to$ ```+ -```
2. 连续的 ```+``` 变为开头 ```-``` 末尾 ```+```：```+ + + + + +``` $\to$ ```- . . . . . +```

以上两个变换都用到了 $c_i = 2c_{i - 1}$ 的性质，保证了一行的和不变。

又因为这两个变换都要在右边加元素，因此我们从左往右考虑位置 $i$：

- 如果第 $i$ 列有一个 ```+``` 和一个 ```.```，那么什么也不做；
- 如果第 $i$ 列有是两个 ```.```，那么第 $i - 1$ 列**一定**存在一个 ```+```，对它做变换 $1$，使得第 $i$ 列是一个 ```+``` 一个 ```.```；
- 如果第 $i$ 列有两个 ```+```，那么第 $i - 1$ 列**一定**恰有一个 ```+```，找到这一行，并找到这个 ```+``` 所在的极长连续段，对这一段做变换 $2$。

这个流程进行一遍后，每列就会有至少一个 ```.```，在从左到右，对有两个 ```.``` 的列考虑变换 $1$，则每一列恰有一个 ```.```，构造完毕。

对于正确性的证明：如果上面两个加粗的一定都成立，那么构造显然正确。对这两处的证明就用这个构造本身套上数学归纳法即可。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 1010, M = 45;
int n, m, mp[M], f[2][M]; struct Posi {int x, y;} p[N];
inline void debug()
{
	for(int op = 0; op <= 1; ++op)
	{
		for(int i = 1; i <= m; ++i)
		{
			switch(f[op][i])
			{
				case -1 : cerr << '-'; break;
				case 0 : cerr << ' '; break;
				default : cerr << '+'; break;
			}
		}
		cerr << '\n';
	}
}
inline void solve(int px, int py)
{
	memset(f, 0, sizeof(f));
	if(m == 31)
	{
		for(int i = 1; i <= m; ++i)
		{
			f[0][i] = (bool)(abs(px) & mp[i]);
			f[1][i] = (bool)(abs(py) & mp[i]);
		}
	}
	else
	{
		if(abs(px) & 1) f[0][1] = f[1][2] = 1;
		else f[0][1] = -1, f[0][2] = 1;
		for(int i = 3; i <= m; ++i)
		{
			f[0][i] = (bool)(abs(px) & mp[i]);
			f[1][i] = (bool)(abs(py) & mp[i]);
		}
	}
//	debug();
	for(int i = 1; i <= m; ++i)
	{
		if(f[0][i] && f[1][i])
		{
			for(int op = 0; op <= 1; ++op)
			{
				if(f[op][i - 1] == 1)
				{
					int ln = i - 1, rn = i;
					while(ln >= 1 && f[op][ln - 1] == 1) --ln;
					while(rn <= m && f[op][rn + 1] == 1) ++rn;
					for(int j = ln; j <= rn; ++j) f[op][j] = 0;
					f[op][ln] = -1; f[op][rn + 1] = 1;
					break;
				}
			}
		}
		else if(!f[0][i] && !f[1][i])
		{
			if(f[0][i - 1] == 1) f[0][i - 1] = -1, f[0][i] = 1;
			else assert(f[1][i - 1] == 1), f[1][i - 1] = -1, f[1][i] = 1;
		}
	}
	for(int i = 1; i <= m; ++i)
	{
		if(!f[0][i] && !f[1][i])
		{
			for(int op = 0; op <= 1; ++op)
				if(f[op][i - 1])
					{f[op][i] = f[op][i - 1], f[op][i - 1] *= -1; break;}
		}
	}
	for(int i = 1; i <= m; ++i)
	{
		if(px < 0) f[0][i] *= -1;
		if(py < 0) f[1][i] *= -1;
	}
	int nx = 0, ny = 0;
	for(int i = 1; i <= m; ++i)
	{
		if(f[0][i] == 1) cout << 'R', nx += mp[i];
		else if(f[0][i] == -1) cout << 'L', nx -= mp[i];
		else if(f[1][i] == 1) cout << 'U', ny += mp[i];
		else assert(f[1][i] == -1), cout << 'D', ny -= mp[i];
	}
	assert(nx == px && ny == py);
	cout << '\n';
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
	for(int i = 2; i <= n; ++i)
		if(((p[i].x + p[i].y) & 1) != ((p[1].x + p[1].y) & 1))
			{cout << -1 << '\n'; return 0;}
	if((p[1].x + p[1].y) & 1) {m = 31; for(int i = 1; i <= m; ++i) mp[i] = (1 << (i - 1));}
	else {m = 32; for(int i = 1; i <= m; ++i) mp[i] = (1 << max(0, i - 2));}
	cout << m << '\n';
	for(int i = 1; i <= m; ++i) cout << mp[i] << " "; cout << '\n';
	for(int i = 1; i <= n; ++i) solve(p[i].x, p[i].y);
	return 0;
}
/*

*/
```

---

## 作者：dci66666 (赞：3)

~~欸谁把我题解删了（那我重写一篇吧。~~
## 题目理解
（这题目翻译也太简单了吧，可我又看不懂日文）

给定 $n$ 组坐标。构造长度为 $m$ 的序列 $\{c_n\}$ 和 $n$ 组包含 `LRUD` 的路径，满足对于每一组坐标：

- $c_i$ 表示第 $i$ 步「步长」。
- 对于每个坐标，从 $(0,0)$ 开始走，共走 $m$ 步。第 $i$ 步可以让 $(x,y)$ 变成 $(x±c_i,y)$ 或 $(x,y±c_i)$。
- 走完 $m$ 次之后，恰好走到这组坐标。
- 要求 $m\leq 40,c_i\leq 10^{12}$。

$1\leq n\leq 1000$（摘自原题）

看完题目，可以看出这显然是个构造题，这个问题的关键就是序列 $\{c_n\}$，由于 $m$ 非常小，但又必须在 $m$ 步数中达到，又发现不了什么特殊性质，只能考虑 $\{c_n\}$ 有什么特殊构造。

首先 $m\leq 40$， $x$ 绝对值与 $y$ 绝对值之和又非常大但是不超 $2e9$ 这一点非常关键，因为 $2^{40}\ge2e9$ 于是想到可以构造形如 $2^k$ 的序列解决.....

$1，2，4，8，16.....$

这种序列有什么特殊性质吗？

有！该序列可以找到前 $1$ 到 $k$ 项之和即 $\sum_{i=1}^{k}a_i$ 从一到该数的所有和都可以凑出来。

举个栗子。

![](https://cdn.luogu.com.cn/upload/image_hosting/rvhj9248.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

好了，大概是这样，这种凑法的本质是二进制分解。

现在，我们就可以把 $c_n$ 序列构造类似情况。（注意 $2^{32}$ 开 $int$ 会炸，要开 $long long$ ）

那么序列构造好了，怎么处理 $x_iy_i$ 呢？

我们可以构造 $c_i=2^{i-1}$ 的序列，目标凑出 $x_iy_i$ 绝对值相加（原题说了，可以上下左右任意方向移动，所以正负只是表明方向，在数值上我们只关心绝对值），那么利用前面的思路，两数绝对值之和一定可以凑出来！！！

**有些爱思考的人会问了，每次只能在 $x$ 方向或 $y$ 方向上移动万一走不出来怎么办？你怎么保证一定可以刚好走到呢？？**

这就是这题最为巧妙的地方了。

我们可以逆向操作从 $(x,y)$ 到 $(0,0)$，我们的目标是走到 $(0,0)$ ，我们将 $c_i$ 逆向操作，对于绝对值较大的 $x$ 或 $y$ ，如果是负数，则加 $c_i$ 否则减 $c_i$ 只要如此操作，序列操作到末尾时就一定能到达 $(0,0)$。

证明的话也好证，对于每一项而言，当该项操作完后，该项绝对值一定小于等于 $c_i$ 这一项（当且仅当该项等于 $0$），那么只要这样当 $c_i$ 等于 $1$ 时坐标就一定可以达到 $0(<1)$ 而一恰好是我们的最后一项，所以，一定可以解决。

看到样例中还有 $-1$ 的情况，我们序列操作完后必定得到奇数，但是如果是偶数怎么办，可以把 $1$ 删去，但是这又有问题出现了，比方说样例三直接打脸，所以我们应该加上再 $1$ 的项，当奇偶性不同时直接 $-1$ 就行。

还没懂？那看代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e3+50;
ll x[N],y[N],m,d,n,c[35],num=-1,ans,maxn;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		if(num==-1)num=(abs(x[i])+abs(y[i]))%2;
		else if((abs(x[i])+abs(y[i]))%2!=num)ans=-1;
	}
	if(ans==-1)puts("-1");
	else {
		printf("%lld\n",33-num);
		int k=0;
		if(num)k++;
		for(int i=k;i<=32;i++)
		printf("%lld ",c[i]=pow(2,max(0,i-1)));
		printf("\n");
		for(int i=1;i<=n;i++){
			string s;
			ll disx=abs(x[i]),disy=abs(y[i]);
			for(int j=32;j>=k;j--){
			    if(disx>disy){
				    if(x[i]<0){
					    x[i]+=c[j];
					    s+='L';
				    }else x[i]-=c[j],s+='R';
			    }else {
			    	if(y[i]<0){
					    y[i]+=c[j];
					    s+='D';
				    }else y[i]-=c[j],s+='U';
				}
				disx=abs(x[i]),disy=abs(y[i]);
			}
			reverse(s.begin(),s.end());
			cout<<s;
			printf("\n");
		}
	}
}
```
代码做了很多压代码的操作，希望各位喜欢，求过！！

---

## 作者：Chthologist7507 (赞：3)

给一个和大家都不太一样的做法？

判无解，如果奇偶不同就无解，因为加减满足奇偶性不变

然后考虑数据范围，观察到 $10^{12}\approx2^{40}$，可以想到倍增构造，于是就让机械臂长为 $1,2,4,8...2^{39}$

然后这里需要注意的是如果 $x+y$ 为奇数的情况，这时需要额外补一个长度为 $1$ 的机械臂补全

从大到小安排机械臂，使用贪心构造，横纵坐标中离目标点差最小的优先，因为有 $2^{k+1}-2^k=2^k$，所以可以知道一定能构造出解

```cpp
// Problem: AT4432 [ARC103B] Robot Arms
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT4432
// Memory Limit: 1000 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define inl inline
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
const int N=1010;
int x[N],y[N],cnt,d[N],pd[2];
signed main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m;cin>>n;
	rep(i,1,n){cin>>x[i]>>y[i];pd[(x[i]+y[i])&1]++;}
	if(pd[0]&&pd[1]){cout<<"-1";return 0;}
	pre(i,38,0)d[++cnt]=1ll<<i;
	if(pd[0])d[++cnt]=1;
	cout<<cnt<<'\n';rep(i,1,cnt)cout<<d[i]<<' ';cout<<'\n';
	rep(i,1,n){
		rep(j,1,cnt){
			if(abs(x[i])>abs(y[i])){
				if(x[i]<0){cout<<"L";x[i]+=d[j];}
				else{cout<<"R";x[i]-=d[j];}
			}
			else{
				if(y[i]<0){cout<<"D";y[i]+=d[j];}
				else{cout<<"U";y[i]-=d[j];}
			}
		}
		cout<<'\n';
	}
}

```

---

## 作者：Exp10re (赞：1)

### 解题思路

考虑构造。

无解是好判的：由于每一次行动都会使得 $x$ 或 $y$ 加上 $2c_i$，故若存在两点横纵坐标之和奇偶性不同则无解。

否则猜测一定有解。

考虑在加上一个 $c_i$（按照题目的说法就是加上一条机械臂）对可到达的点的影响：可以发现，加上 $c_i$ 之后相当于可到达的点的位置向上下左右各平移了 $c_i$ 的距离之后的点。

以 $c={1,3}$ 为例，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/6enprk9z.png)

这是仅考虑 $c={1}$ 时的可到达的位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/iiobmq2o.png)

这是考虑 $c={1,3}$ 时的可到达的位置。可以发现就是 $c={1}$ 时的可到达的位置向四个方向偏移三格的结果。

故我们构造 $c={1,1,2,4,\cdots,2^{37}}$ 就能够得到数据范围内横纵坐标之和为偶数的所有解。

这个构造满足：

$$c^i=\begin{cases}
1 & i=1 \\
2^{i-1} & otherwise. \\
\end{cases}$$

可以发现，考虑到 $c^i$ 时能到达的所有点即为与 $(0,0)$ 曼哈顿距离不超过 $2^i$ 的所有点，加上 $2^i$ 之后可以到达与 $(0,0)$ 曼哈顿距离不超过 $2^{i+1}$ 的所有点，故以上构造能够到达与 $(0,0)$ 曼哈顿距离不超过 $2^{38}$ 的所有点。

而对于横纵坐标之和为奇数的解，在开头加上一个 $1$ 构造一个 $1$ 的偏移，即将中心视为 $(1,0)$ 之后沿用以上方法构造。

对于方向的构造如下：从大到小考虑各个机械臂，对于当前在 $(nx,ny)$，需要到达 $(x,y)$ 的状态，若横坐标差值较大就考虑往左右走，往左还是往右取决于当前点在目标的右边还是左边，纵坐标同理。

证明可以考虑：往横向某个方向移动 $c_i$ 之后横坐标差值一定小于 $c_i$，纵坐标同理，由于所有点一定可达，故考虑完所有值之后两个坐标的差值均为 $0$。

---

## 作者：Corzica (赞：1)

一般遇到这种拆分问题，会往二进制的方面想。

然后注意到不管你的坐标如何变化，但是你两维的和的奇偶性是整体不变的，所以如果发现两维的和的奇偶性不同的话，直接返回无解。

然后考虑有解的时候怎么构造，这时候直接依次输出 2 的幂次，在草稿纸上画图发现这样构造恰好可以覆盖所有的奇偶性一致的点。如果整体是偶数的话就额外再多输出一个 1 即可。

还要输出方案，在我们草稿纸上的模拟过程中，可以发现可行的半径是一直在扩大的。我们反向做这个过程，不断缩小这个点对圆点的曼哈顿距离即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, x[1005], y[1005], sum, c[1005], cnt;
inline void solve(int p, int q, int w) {
	if (!w) {
		return;
	}
	if (abs(p) > abs(q)) {
		if (p > 0) {
			solve(p - c[w], q, w - 1);
			cout << "R";
		} else {
			solve(p + c[w], q, w - 1);
			cout << "L";
		}
	} else {
		if (q >= 0) {
			solve(p, q - c[w], w - 1);
			cout << "U";
		} else {
			solve(p, q + c[w], w - 1);
			cout << "D";
		}
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i];
	}
	sum = ( (abs(x[1]) + abs(y[1])) % 2);
	for (int i = 1; i <= n; i++) {
		if ((abs(x[i]) + abs(y[i])) % 2 != sum) {
			cout << -1;
			exit(0);
		}
	}
	if (sum == 1) {
		cnt = 31;
		int op = 1;
		cout << cnt << "\n";
		for (int i = 1; i <= 31; i++, op *= 2) {
			cout << (c[i] = op) << " ";
		}
		cout << "\n";
	} else {
		cnt = 32;
		int op = 1;
		cout << cnt << "\n" << (c[1] = 1) << " ";
		for (int i = 2; i <= 32; i++, op *= 2) {
			cout << (c[i] = op) << " ";
		}
		cout << "\n";
	}
	for (int i = 1; i <= n; i++) {
		solve(x[i], y[i], cnt);
		cout << "\n";
	}
}
```

---

## 作者：Alarm5854 (赞：1)

看了题解区都是用 $2$ 的幂次方解的，这里来介绍一种用 $3$ 的幂次方的解法，虽然只能卡着边缘过且写起来非常暴力，因为最坏情况下的 $m=2\lceil \log_3 V\rceil$ 的，其中 $V$ 是值域，代入 $V$ 的最大值可得 $m=40$。

考虑平衡三进制：每一个整数数 $x$ 都可以唯一表示为 $n=\sum_{i=0}^{+\infty}k_i\times 3^i,k_i\in\{-1,0,1\}$，那么每一个 $(x_i,y_i)$ 就可以用两份的 $3$ 的幂表示出来。

首先，先判掉存在两组坐标使得 $x+y$ 的奇偶性不同的情况。然后，就可以按位考虑。设 $x$ 的第 $i$ 位为 $a_i$，$y$ 的第 $i$ 位为 $b_i$，所有 $(a_i,b_i)$ 中 $0$ 最少的那对的 $0$ 的数量为 $c$，那么就有以下情况：

- $c=2$，此时不需要任何 $3^i$ 填充。
- $c=1$，此时恰好需要一个 $3^i$ 填充。可以证明：此时不存在一对 $(a_i,b_i)$ 满足存在两个 $0$，否则会导致奇偶性不同，从而无解，此时分为 $4$ 种情况：

| $a_i/b_i$ | $-1$ | $0$ | $1$ |
| :----------: | :----------: | :----------: | :----------: |
| $-1$ | 无 | $\texttt{L}$ | 无 |
| $0$ | $\texttt{D}$ | 无 | $\texttt{U}$ |
| $1$ | 无 | $\texttt{R}$ | 无 |

也就是说，直接在非 $0$ 的那一维往对应的方向走去。

- $c=0$，此时需要两个 $3^i$ 填充，此时 $9$ 种情况均有可能：

| $a_i/b_i$ | $-1$ | $0$ | $1$ |
| :----------: | :----------: | :----------: | :----------: |
| $-1$ | $\texttt{LD}$ | $\texttt{RR},a_{i+1}\leftarrow a_{i+1}-1$ | $\texttt{LU}$ |
| $0$ | $\texttt{UU},b_{i+1}\leftarrow b_{i+1}-1$ | $\texttt{LR}$ | $\texttt{DD},b_{i+1}\leftarrow b_{i+1}+1$ |
| $1$ | $\texttt{RD}$ | $\texttt{LL},a_{i+1}\leftarrow a_{i+1}+1$ | $\texttt{RU}$ |

也就是说，当两个都非 $0$ 的情况下，直接往对应的方向走去；否则，如果恰好有一个 $0$，那么在非 $0$ 的那一维要往相反方向走两步，到 $i+1$ 的时候再一起处理；否则，直接走两步方向互相相反的即可。

代码远远长于 $2$ 的幂，但十分暴力。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e3+7;
ll n,m,c[41],flg[2],x[N],y[N];
char pth[N][41];
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;++i){
		scanf("%lld%lld",x+i,y+i);
		flg[(x[i]+y[i])&1]=1;
	}
	if(flg[0]&&flg[1]){//奇偶矛盾
		puts("-1");
		return 0;
	}
	for(ll i=0,j=1;i<20;++i,j*=3){//平衡三进制在值域为 10^9 的时候最高位为第 19 位
		int f=1;
		for(ll k=1;k<=n;++k){//判断 0 最少的一对是几个 0
			if(!(x[k]%3)&&!(y[k]%3))
				continue;
			if(!((x[k]%3)&&(y[k]%3)))
				f=min(f,0);
			else
				f=-1;
		}
		if(f==1){//都是 0
			for(ll k=1;k<=n;++k){
				x[k]/=3;
				y[k]/=3;
			}
			continue;
		}
		if(f){//没有 0
			c[m]=j;
			c[m+1]=j;
			for(ll k=1;k<=n;++k){
				ll a=(x[k]%3+3)%3;
				ll b=(y[k]%3+3)%3;
				if(!a&&!b){//同表格
					pth[k][m]='L';
					pth[k][m+1]='R';
				}
				else if(!a&&b==1){
					y[k]+=2;
					pth[k][m]='D';
					pth[k][m+1]='D';
				}
				else if(!a&&b==2){
					y[k]-=2;
					pth[k][m]='U';
					pth[k][m+1]='U';
				}
				else if(a==1&&!b){
					x[k]+=2;
					pth[k][m]='L';
					pth[k][m+1]='L';
				}
				else if(a==1&&b==1){
					--x[k];
					--y[k];
					pth[k][m]='R';
					pth[k][m+1]='U';
				}
				else if(a==1&&b==2){
					--x[k];
					++y[k];
					pth[k][m]='R';
					pth[k][m+1]='D';
				}
				else if(a==2&&!b){
					x[k]-=2;
					pth[k][m]='R';
					pth[k][m+1]='R';
				}
				else if(a==2&&b==1){
					++x[k];
					--y[k];
					pth[k][m]='L';
					pth[k][m+1]='U';
				}
				else{
					++x[k];
					++y[k];
					pth[k][m]='L';
					pth[k][m+1]='D';
				}
			}
			m+=2;
		}
		else{
			c[m]=j;
			for(ll k=1;k<=n;++k){
				ll a=(x[k]%3+3)%3;
				ll b=(y[k]%3+3)%3;
				if(a==1){//同表格
					--x[k];
					pth[k][m]='R';
				}
				else if(a==2){
					++x[k];
					pth[k][m]='L';
				}
				else if(b==1){
					--y[k];
					pth[k][m]='U';
				}
				else{
					++y[k];
					pth[k][m]='D';
				}
			}
			++m;
		}
		for(int k=1;k<=n;++k){
			x[k]/=3;
			y[k]/=3;
		}
	}
	printf("%lld\n",m);
	for(int i=0;i<m;++i)
		printf("%lld%c",c[i]," \n"[i==m-1]);
	for(int i=1;i<=n;++i)
		puts(pth[i]);
	return 0;
}
```

---

## 作者：cirnovsky (赞：1)

## $\mathcal{Description}$

[Link](https://atcoder.jp/contests/abc111/tasks/arc103_b).

给定 $n$ 组坐标。构造长度为 $m$ 的序列 $\{c_n\}$ 和 $n$ 组包含 `LRUD` 的路径，满足对于每一组坐标：

- $c_i$ 表示第 $i$ 步「步长」。
- 对于每个坐标，从 $(0,0)$ 开始走，共走 $m$ 步。第 $i$ 步可以让 $(x,y)$ 变成 $(x±c_i,y)$ 或 $(x,y±c_i)$ 。
- 走完 $m$ 次之后，恰好走到这组坐标。
- 要求 $m\leq 40,c_i\leq 10^{12}$ 。

## $\mathcal{Solution}$

好强的题啊。

先考虑无解的情况。

即是 $x_{i}+y_{i}$ 的奇偶性不同的情况为无解。

仔细看 $m$ 的限制疑似是 $\log(x+y)$ 级别的，考虑二进制拆分。

于是考虑 $\{2^{k}\}$ 可以凑出的坐标。

只考虑 1-dimension 的做法。

我们能够维护的地方就是 $\sum_{i=0}^{k}2^{i}=2^{k+1}-1$（这里算的是曼哈顿距离）。

那么这一定是个奇数，如果 $(x,y)$ 的曼哈顿距离是偶数就考虑换原点。

那么这就做完了。

## $\mathcal{Code}$

[full ver.](https://www.luogu.com.cn/paste/x1re8ezs)

```cpp
using i64 = long long;
using pii = std::pair<i64, i64>;

std::vector<int> sL;
std::vector<std::string> dR;
std::pair<int, int> as[MAXN];
int n, wax[4], way[4];
char trans[4];

int main () {
	std::ios::sync_with_stdio ( 0 ); std::cin.tie ( 0 ); std::cout.tie ( 0 );
	std::cin >> n; initial ();
	rep ( i, 1, n )	std::cin >> as[i].first >> as[i].second;
	rep ( i, 2, n ) if ( ( as[i].first + as[i].second + as[i - 1].first + as[i - 1].second ) & 1 )	return ( puts ( "-1" ), 0 );
	sL.push_back ( 1 );
	rep ( i, 1, 30 )	sL.push_back ( 1 << i );
	if ( ( ( as[1].first + as[1].second ) & 1 ) ^ 1 )	sL.push_back ( 1 );
	std::reverse ( sL.begin (), sL.end () );
	rep ( i, 1, n ) {
		dR.push_back ( std::string () );
		i64 curx = as[i].first, cury = as[i].second;
		if ( ( ( curx + cury ) & 1 ) ^ 1 )	dR[i - 1].push_back ( 'U' ), cury --;
		per ( j, 30, 0 ) rep ( k, 0, 3 ) {
			i64 nxtx = curx + ( i64 )wax[k] * ( ONE64 << j );
			i64 nxty = cury + ( i64 )way[k] * ( ONE64 << j );
			if ( std::abs ( nxtx ) + std::abs ( nxty ) < ( ONE64 << j ) ) {
				curx = nxtx, cury = nxty;
				dR[i - 1].push_back ( trans[k] );
				break;
			}
		}
	}
	std::cout << sL.size () << '\n';
	for ( int p : sL )	std::cout << p << ' ';
	std::cout << '\n';
	for ( std::string p : dR )	std::cout << p << '\n';
	return 0;
}
```

---

## 作者：mskqwq (赞：0)

无解的一个充分条件是所有的 $x_i + y_i$ 的奇偶性相等，这个条件其实也是必要的。

首先考虑一维的情况，既 $y_i =0$，发现这个 $\le 40$ 的限制大概是 $\log $ 级的，尝试让 $c_i =2^{i-1}$，发现这样可以构造出在 $[-2^m+1,2^m-1]$ 范围内的所有奇数，偶数的话多加一个 $1$ 就行，接下来只考虑奇数的情况，且 $\vert x_i \vert \le 2^{m}-1$。

接着尝试构造，考虑倒着做，从 $x_i$ 走到 $0$。若 $x_i \le 0$ 则让 $x_i \gets x_i + 2^{m-1}$，否则让 $x_i \gets x_i -2^{m-1}$。不难发现这样做之后 $x \in [-2^{m-1}+1,2^{m-1}-1]$，于是变成了子问题。

然后是二维的情况，依旧让 $c_i = 2^{i-1}$，打表发现可以构造出所有 $\vert x_i \vert +|y_i| \le 2^{m}-1$  的情况。构造方法也很简单，每次对绝对值最大的那个执行一维时的操作。

证明方法和一维类似，通过分讨 $x_i$，$y_i$ 的正负性可以发现一次操作过后 $|x_i| +|y_i| \le 2^{m-1}-1$。

```c++
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char ch=getchar();int f=1,x=0;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e5+10,mod=998244353;
int n,x[N],y[N],d[N],k=0,f=-1;
void misaka(){
    n=read();
    rep(i,1,n){
        x[i]=read(),y[i]=read();
        if(f!=-1&&f!=(x[i]+y[i]&1)) puts("-1"),exit(0);
        f=x[i]+y[i]&1;
    }
    if(!f) d[++k]=1;
    rep(i,0,30) d[++k]=1<<i;
    printf("%d\n",k);
    rep(i,1,k) printf("%d ",d[i]);puts("");
    rep(i,1,n){
        vector<char> v;
        _rep(j,k,1){
            if(abs(x[i])>abs(y[i])){
                if(x[i]<0) v.eb('L'),x[i]+=d[j];
                else v.eb('R'),x[i]-=d[j];
            }
            else{
                if(y[i]<0) v.eb('D'),y[i]+=d[j];
                else v.eb('U'),y[i]-=d[j];
            }
        }
        reverse(rg(v));
        for(char x:v) putchar(x);puts(""); 
    }
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    while(T--) misaka();
    return 0;
}
```

---

## 作者：ask_silently (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_arc103_b)

# 题目大意

给你 $n$ 组坐标，需要构造出来一个长度为 $m$ 的序列 $c$ 为每次走的步数，请你在 $m$ 次操作后，到达每一组坐标。

# 思路分析

这道题有两种情况，先判断特殊情况，即不能到达的情况。每组坐标走的总步数是一致的，所以 $x+y$ 的步数奇偶性相等。

再判断如何到达，我们发现 $2^m$ 大约是 $X$ 和 $Y$ 的范围，所以我们可以考虑 $\log(x)$ 的思路，继而想到二进制分解，我们发现每次操作可以对 $x,y$ 中绝对值更大的数操作，这样我们就能逼近 $(0,0)$，而这样一直进行此操作，就能找到解了。

注意运算符优先级。

# AcCode


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N=1010;

int n,m,k,flag;
int x[N],y[N],ci[N];
 
inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f),c=getchar();
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

inline int max(int a,int b,int c){
	return (a>b)?((a>c)?(a):(c)):((b>c)?(b):(c));
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		x[i]=read(),y[i]=read();
		k=max(k,log2(llabs(x[i])-1)+1,log2(llabs(y[i])-1)+1);
		if(i==1) flag=(llabs(x[i])+llabs(y[i]))&1;
		if(flag!=((llabs(x[i])+llabs(y[i]))&1)){
			cout<<-1;
			return 0;
		}
	}
	for(int i=k;i>=0;i--) ci[++m]=1ll<<i;
	if(!flag) ci[++m]=1;
	cout<<m<<endl;
	for(int i=1;i<=m;i++) cout<<ci[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(llabs(x[i])>llabs(y[i])){
				if(x[i]<0){cout<<"L";x[i]+=ci[j];}
				else{cout<<"R";x[i]-=ci[j];}
			}else{
				if(y[i]<0){cout<<"D";y[i]+=ci[j];}
				else{cout<<"U";y[i]-=ci[j];}
			}
		}
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：YuYuanPQ (赞：0)

题目要求构造路径。

我们知道，任何非负整数都可以由多个不同的二次幂相加得到。

简单证明一下：用二进制表示出来，就可以容易地得到此结论。

那么我们先预处理好。

接下来怎么办？

考虑贪心。

对于每一个点，进行判断。

接下来设当前坐标为 $(p,q)$，目标点坐标为 $(x,y)$。

初始时 $p$，$q$ 都为 $0$。

分类讨论。

当 $x$ 与 $p$ 的差比 $y$ 与 $q$ 的差大时：

判断一下 $x$ 和 $p$ 谁大。
- 当 $p<x$ 时，往右走。
- 否则，往左走。

否则：

判断一下 $y$ 和 $q$ 谁大。

- 当 $q<y$ 时，往上走。
- 否则，往下走。

完结撒花~

---

## 作者：_edge_ (赞：0)

首先有曼哈顿距离转切比雪夫距离，然后构造 $1,2,4,8,\cdots ,2^{30}$（为了保险起见可以多去一点点），每次两个维是独立的。

然后每次能更改一个数字的符号，产生的贡献是这个这个数字乘 $2$，还有一种情况需要补一个一，就是一开始的时候 $x+y$ 全是偶数的（如果又出现偶数又出现奇数容易发现其无解）。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e3+5;
int n,aa[INF],bb[INF],m,cc[INF],ff[INF][INF],gg[INF][INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>aa[i]>>bb[i];
		int x=aa[i],y=bb[i];
		aa[i]=x+y;bb[i]=x-y;
	}
	m=35;int ba=1,sum3=0;
	for (int i=1;i<=m;i++) 
		cc[i]=ba,ba*=2,sum3+=cc[i];
	int fl1=0,fl2=0;
	for (int i=1;i<=n;i++)
		if ((aa[i]%2+2)%2==1) fl1=1;
		else fl2=1;
	if (fl1 && fl2) cout<<"-1\n";
	else {
		if (fl2) cc[++m]=1,sum3++;
		for (int i=1;i<=n;i++) {
			int P=sum3-aa[i];
			for (int j=1;j<=35;j++)
				if ((P>>j)&1) ff[i][j]=-1;
				else ff[i][j]=1;
			
			P=sum3-bb[i];
			for (int j=1;j<=35;j++)
				if ((P>>j)&1) gg[i][j]=-1;
				else gg[i][j]=1;
		}
		cout<<m<<"\n";
		for (int i=1;i<=m;i++) cout<<cc[i]<<" ";
		cout<<"\n";
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=35;j++) {
				if (ff[i][j]==-1 && gg[i][j]==-1) cout<<"L";
				else if (ff[i][j]==1 && gg[i][j]==1) cout<<"R";
				else if (ff[i][j]==-1 && gg[i][j]==1) cout<<"D";
				else cout<<"U";
			}
			if (m==36) cout<<"R";
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：xht (赞：0)

> [ARC103D Robot Arms](https://atcoder.jp/contests/arc103/tasks/arc103_b)

## 题意

- 平面上有 $n$ 个整点 $(x_i, y_i)$。
- 要求构造出一个长度为 $m(\in [1,40])$ 的整数序列 $d(\in [1,10^{12}])$，满足 $d$ 可以生成所有整点。
- 称一个整数序列 $d_{1\dots m}$ 可以生成一个整点 $(x_i,y_i)$，当且仅当可以从 $(0,0)$ 开始，每次往上下左右中的一个方向走一个 $d_i$，最终可以恰好在 $(x_i,y_i)$。
- $n \le 10^3$，$|x_i|,|y_i| \le 10^9$。

## 题解

有解当且仅当所有 $x_i + y_i$ 的奇偶性相同。

若 $x_i + y_i \equiv 1 \pmod 2$，则 $2^0,2^1,\cdots,2^{30}$ 即可；若 $x_i + y_i \equiv 0 \pmod 2$，则再加一个 $1$ 即可。

构造时从大到小考虑，走距离更远的方向。

## 代码

```cpp
const int N = 1e3 + 7;
int n;
ll x[N], y[N], z[N];

inline char work(ll x, ll y, ll &X, ll &Y, ll k) {
	if (abs(x - X) > abs(y - Y)) {
		if (x > X) return X += k, 'R';
		return X -= k, 'L';
	}
	if (y > Y) return Y += k, 'U';
	return Y -= k, 'D';
}

int main() {
	rd(n);
	for (int i = 1; i <= n; i++)
		rd(x[i], y[i]), z[i] = abs(x[i] + y[i]) % 2;
	for (int i = 1; i <= n; i++)
		if (z[i] != z[1]) return print(-1), 0;
	vector<ll> d;
	for (int i = 30; ~i; i--) d.pb(1ll << i);
	if (!z[1]) d.pb(1ll);
	print(d.size());
	for (ll k : d) print(k, ' ');
	prints("");
	for (int i = 1; i <= n; i++) {
		ll X = 0, Y = 0;
		for (ll k : d)
			printc(work(x[i], y[i], X, Y, k));
		prints("");
	}
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：0)

### 大意

有 $ n $ 个目标点，让你构造一个末端可以恰好到达每个目标点的机械臂。

机械臂最多有 $ m $ 个节点，每个节点有方向和长度两个值，方向可以是上下左右，长度固定并表示该节点与上一个节点在坐标轴依照方向的距离差。

求构造机械臂每个节点的长度，以及对于每个目标点来说机械臂每个节点的方向。

默认机械臂的第 $ 0 $ 号节点为原点。

### 思路

用奇偶性证明如果任意两个目标点的坐标和（ $ x_i + y_i $ ）奇偶性不同，则无解。

显然所有点的坐标和都是偶数的情况可以用长度为 $ 1 $ 的机械臂转换为所有点的坐标和都是奇数的情况，用 $ 1 $ 是因为它小，不会造成大差异。

如果我们的机械臂是一个长度为 $ k $ 的满足 $ a_i=2^{i - 1} $ 的序列 $ a $ ，那么可以到达的所有点就是满足坐标和为奇数且 $ |x_i| + |y_i| \leq 2^k - 1 $ 的所有点。

可以使 $ k $ 递增，用归纳法证明。

发现 $ 2^{30} - 1 \leq 10^9 + 10^9 $ ，仅需长度为 $ 30 $ 左右的机械臂（坐标和为偶数的情况额外需要一个节点）。

对于每个目标点从大往小贪心枚举边并决定方向即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int x[1010],y[1010],z[50];
int main(){
    cin>>n;
    f(i,1,n){
        scanf("%d %d",&x[i],&y[i]);
        if((abs(x[i-1]+y[i-1])&1)!=(abs(x[i]+y[i])&1) && i>1)goto unfind;
        m=max(m,(x[i]+y[i])&1);
    }
    printf("%d\n",32-m);
    if(m)g(i,30,1)printf("%d ",z[30-i+1]=(1<<i));
    else g(i,30,0)printf("%d ",z[30-i+1]=(1<<i));
    m=32-m;
    printf("%d\n",z[m]=1);
    f(i,1,n){
        f(j,1,m){
            if(abs(x[i])>abs(y[i])){
                if(x[i]>0)putchar('R');
                else putchar('L');
                if(x[i]>0)x[i]-=z[j];
                else x[i]+=z[j];
            }else{
                if(y[i]>0)putchar('U');
                else putchar('D');
                if(y[i]>0)y[i]-=z[j];
                else y[i]+=z[j];
            }
        }
        putchar('\n');
    }
    goto end;
    unfind:;
    printf("-1\n");
    end:;
    return 0;
}
```

---

## 作者：关怀他人 (赞：0)

### ARC103D
#### Solution
不难发现一个结论：对于$d={1,2,4,...,2^k}$，可以走到所有$|x|+|y|\leq 2k−1$且$x+y\equiv 1(mod \ 2)$的点

证明的话考虑二进制拆分$x$和$y$坐标即可。

那么有解当且仅当所有数的$x+y\ mod \ 2$都要相等，如果都是偶数那么$d$集合中再加一个$1$即可。

求方案数的话，从大到小枚举$k$，每次把$|x|,|y|$中较大的那个的绝对值减去$2^k$即可。

#### Code
```cpp
int n;
ll x[MAXN],y[MAXN],cnt[2];
vector<ll> d;

int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%lld%lld",&x[i],&y[i]);
        cnt[(x[i] + y[i]) & 1] += 1;
    }
    if(cnt[0] && cnt[1]) {puts("-1"); return 0;}
    for(int i = 31;i >= 0;i--) d.push_back(1ll << i);
    if(cnt[0]) d.push_back(1);
    printf("%d\n",(int)d.size());
    for(auto i : d) printf("%lld ",i); printf("\n");
    for(int i = 1;i <= n;i++){
        for(auto p : d){
            if(llabs(x[i]) > llabs(y[i])){
                putchar(x[i] < 0 ? 'L' : 'R');
                if(x[i] < 0) x[i] += p;
                else x[i] -= p;
            }else{
                putchar(y[i] < 0 ? 'D' : 'U');
                if(y[i] < 0) y[i] += p;
                else y[i] -= p;
            }
        }
        putchar('\n');
    }
    return 0;
}
```

---

