# [ARC081F] Flip and Rectangles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc081/tasks/arc081_d

$ H\ \times\ W $ のマス目があります． マス目の各マスは黒か白かに塗られており，上から $ i $ 番目，左から $ j $ 番目のマスは，$ S_i $ の $ j $ 文字目が `#` のとき黒マス，`.` のとき白マスです．

すぬけ君は，マス目に対して次の操作を好きな回数行うことができます．

- マス目の任意の行または列を選び，その行または列のすべてのマスの色を反転する (すなわち，黒で塗られたマスを白に，白で塗られたマスを黒に塗り替える)．

操作の後，すぬけ君はマス目に沿った長方形を $ 1 $ 個選びます．このとき，選んだ長方形に含まれるすべてのマスは黒で塗られていなければなりません．

うまく操作を行うとき，すぬけ君が選ぶことができる最大の長方形の面積を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ H\ \leq\ 2000 $
- $ 2\ \leq\ W\ \leq\ 2000 $
- $ |S_i|\ =\ W $
- $ S_i $ は `#`, `.` のみからなる．

### Sample Explanation 1

下図のように，上から $ 1 $ 行目，左から $ 3 $ 列目を反転させると，$ 2\ \times\ 3 $ の長方形を選ぶことができます． !\[\](https://atcoder.jp/img/arc081/2995c3921ed4dffc8ee528b63b9c6118.png)

## 样例 #1

### 输入

```
3 3
..#
##.
.#.```

### 输出

```
6```

## 样例 #2

### 输入

```
4 4
....
....
....
....```

### 输出

```
16```

## 样例 #3

### 输入

```
10 8
##...#.#
##...#.#
..###.#.
#.##.#.#
.#..#.#.
..##.#.#
##.#.#..
...#.#..
###.#.##
###..###```

### 输出

```
27```

# 题解

## 作者：command_block (赞：12)

**题意** ： 给出一个 $n\times m$ 的 $01$ 矩阵。

每次操作可以将一行或一列取反，可以进行任意多次操作，问矩阵中全 $1$ 矩形面积的最大值。

$n,m\leq 2000$ ，时限$\texttt{2s}$。

------------

首先考虑如何判定一个矩形经过操作能否变为全 $1$。

先观察一些性质 ： 

- 若某个矩形能被操作为全 $1$ ，那么其任意子矩形也一定可以。

- 行列任意交换不影响某个矩形是否能变为全 $1$。

任选位置 $[x,y]$ ，若 $A[x,y]=0$ 则将整个矩形取反，这样总有 $A[x,y]=1$。

先查看第 $x$ 行和第 $y$ 列，若某个数为 $0$ ，则翻转对应 行/列。

在这之后，若做其他操作，则第 $x$ 行和第 $y$ 列必被破坏。所以不能进一步操作，检查此时矩阵是否全黑即可。

这等价于，对于位置 $A[i,j]$ （$i\neq x,j\neq y$），检查 $! A[x,y],!A[x,j],!A[i,y],A[i,j]$ 的异或值是否为 $1$。

也即 $A[x,y],A[x,j],A[i,y],A[i,j]$ 的异或值是否为 $0$。

由于 $[x,y]$ 也是任选的，我们得到一条性质 ： 任意一个子矩形的四个角的异或和为 $0$。

这同时也是充要条件。

> 在转化充要条件时，判定算法可能是构造性的。此时要尽量多想“有没有其他方法也可以完成构造？”，以得到更多性质。

> 比方说，在本题中，若直接选择第一行第一列开始构造（而不是任意的 $[x,y]$）就很难得到这个性质。

该条件依然难以维护，考虑进行简化 ： 能否只考虑一小部分矩形的约束呢？

条件可以看作若干异或方程组，线性相关的方程组显然是无用的。

略微手玩方程之间的线性相关模式后，可以发现，只需要考虑所有的 $2\times 2$ 矩形，因为更大的矩形的四个角都可以用内部所有的 $2\times 2$ 矩形异或出来。

于是，对每个 $2\times 2$ 矩形，查看内部是否有奇数个 $1$ 。若是，则称为坏矩形。

若一个大矩形包含了坏矩形，则无法变为全 $1$ ，反之可以。

至此，我们将原问题转化为了最大全 $1$ 矩形问题。

（注意，长或宽为 $1$ 的矩形总是好的）

这是经典问题，这里用悬线法解决。

复杂度 $O(n^2)$。

```cpp
#include<algorithm>
#include<cstdio>
#define MaxN 2050
using namespace std;
const int mod=998244353;
int n,m,l[MaxN][MaxN],r[MaxN][MaxN],up[MaxN][MaxN];
char a[MaxN][MaxN];
int main()
{
  scanf("%d%d",&n,&m);
  int ans=max(n,m);
  for (int i=1;i<=n;i++){
    scanf("%s",a[i]+1);
    for (int j=1;j<=m;j++)
      a[i][j]=(a[i][j]=='#');
  }
  n--;m--;
  for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++){
      a[i][j]=!((a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1])&1);
      l[i][j]=r[i][j]=j;
    }
  for (int i=1;i<=n;i++){
    for (int j=2;j<=m;j++)
      if (a[i][j]&&a[i][j-1])
        l[i][j]=l[i][j-1];
    for (int j=m-1;j;j--)
      if (a[i][j]&&a[i][j+1])
        r[i][j]=r[i][j+1];
    for (int j=1;j<=m;j++)
      if (a[i][j]){
        if (a[i-1][j]){
          l[i][j]=max(l[i][j],l[i-1][j]);
          r[i][j]=min(r[i][j],r[i-1][j]);
        }up[i][j]=up[i-1][j]+1;
        ans=max(ans,(r[i][j]-l[i][j]+2)*(up[i][j]+1));
      }
  }printf("%d",ans);
  return 0;
}
```

---

## 作者：C　C　A (赞：8)

$$\huge\rm [ARC081D]Flip~and~Rectangles$$

$$\large\text{——}~The~~Solution~~Written~~by~~CCA~\text{——}$$

---

$$\LARGE\mathcal{Description}$$

$\quad$给定一个 $01$ 矩阵，每次操作可以将一行或一列的颜色取反，问经过若干次操作后的最大全 $1$ 子矩阵中 $1$ 的数量是多少 。

$\quad n,m\leqslant 2\times 10^3$

---

$$\LARGE\mathcal{Solution}$$

$\quad$先考虑弱化问题，一个 $2\times 2$ 的 $01$ 矩阵能经过若干次操作变成全 $1$ ，当且仅当其中有偶数个 $1$ 。

$\quad$对于一个 $n\times m$ 的矩阵，对于第一行和第一列上的数，经过若干次操作后一定可以使它变成全 $1$ ，因为如果其中有某个数不是 $1$ ，一定可以通过取反它所在的行或列来将它变成 $1$ ，且不影响其他的第一行和第一列上的结点 。

$\quad$如果一个 $n\times m$ 的矩阵，其中每一个 $2\times 2$ 的子矩阵中都有偶数个 $1$ ，而一行或一列上的数取反不会影响到任何一个 $2\times 2$ 的矩阵上 $1$ 个数的奇偶性，所以当它第一行和第一列上的数都为 $1$ 时，格点 $(1,1)$ ，$(1,2)$ ，$(2,1)$ ，$(2,2)$ 所构成的 $2\times 2$ 的矩阵中已经有了 $3$ 个 $1$ ，为了保证 $1$ 奇偶性，$(2,2)$ 上的数也一定为 $1$ ，而如果它为 $1$ ，以此类推，整个 $n\times m$ 的矩阵都为 $1$ 。

$\quad$于是就可以在每个非边的格点上标一个数，若它表示的 $2\times 2$ 矩阵内有偶数个 $1$ ，它的值就为 $1$ ，否则为 $0$ ，这些数又会形成一个矩阵，这样问题就转化成了求新的矩阵的最大全 $1$ 子矩阵，用单调队列极其套路地求一下就好了 。

$\quad$输出的时候要注意，单独的一行或者一列是一定可以变成全 $1$ 的，要将 $n$ 和 $m$ 对 $\rm Ans$ 取一下 $\rm Max$ 。

$\quad$时间复杂度 $\mathcal{O}(N^2)$ 。

---

$$\LARGE\mathcal{Code}$$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 10;

char s[N][N];
int n, m, top, ans, l[N], r[N], h[N], st[N], a[N][N];

int Count(int x, int y) { 
    return (s[x][y] == '#') + (s[x + 1][y] == '#') + (s[x][y + 1] == '#') + (s[x + 1][y + 1] == '#');
}

int main () {
    
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);

    for(int i = 1; i < n; i++)
        for(int j = 1; j < m; j++)
            if(Count(i, j) % 2 == 0) a[i][j] = 1;
    n--, m--;

    for(int i = 1; i <= n; i++) {
        memset(l, 0, sizeof(l)), memset(r, 0, sizeof(r));
        for(int j = 1; j <= m; j++) h[j] = a[i][j] * h[j] + a[i][j];
        top = 0;
        for(int j = m; j >= 1; j--) {
            for(; top && h[st[top]] > h[j]; --top) l[st[top]] = j;
            st[++top] = j;
        }
        top = 0;
        for(int j = 1; j <= m; j++) {
            for(; top && h[st[top]] > h[j]; --top) r[st[top]] = j;
            st[++top] = j;
        }
        for(int j = 1; j <= m; j++) if(!r[j]) r[j] = m + 1;
        for(int j = 1; j <= m; j++) ans = max(ans, (h[j] + 1) * (r[j] - l[j]));
    }

    printf("%d", max(ans, max(n + 1, m + 1)));

    return 0;
}
```


---

## 作者：louhao088 (赞：7)

人类智慧题。


------------


我们首先需要知道什么样的矩阵才是合法的。如果一个矩阵，它的每一列与都与第一列一样，或者与第一列相反，那么这个矩阵就是合法的。因为一个合法矩阵无论怎么变化都满足上述性质，而这个变化过程是可逆的。

这样我们很容易做到 $O(n^3)$。


------------

考虑合法矩阵所含的性质，我们发现对于每一个 $2 \times 2$ 的矩阵其所含 1 的个数必然是偶数。因为上下两行必然相同或相反。

我们又发现，如果一个矩阵其所含的每一个 $2 \times 2$ 的矩阵都合法的话，这个矩阵满足上述性质，也就是说其必然合法。

然后我们只要以每个 $2 \times 2$ 的矩阵的合法状态构建一个新矩形，然后求其最大全 1 子矩形即可。这个有 $O(n^2)$ 经典做法。

注意，一行或一列的矩形必然合法。 


------------
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2005;
inline int read(){
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x){
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,l[maxn][maxn],r[maxn][maxn],up[maxn][maxn],ans,c[maxn][maxn];
char b[maxn][maxn],a[maxn][maxn];
signed main(){
	n=read(),m=read();ans=max(n,m);
	for(int i=1;i<=n;i++)scanf("%s",b[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)c[i][j]=(b[i][j]=='.');n--,m--;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=(c[i][j]^c[i+1][j]^c[i][j+1]^c[i+1][j+1])^1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)l[i][j]=j,r[i][j]=j;
		for(int j=1;j<=m;j++)if(a[i][j]&&a[i][j-1])l[i][j]=l[i][j-1];
		for(int j=m;j>=1;j--)if(a[i][j]&&a[i][j+1])r[i][j]=r[i][j+1];
		for(int j=1;j<=m;j++)if(a[i][j]){
			if(a[i-1][j])l[i][j]=max(l[i-1][j],l[i][j]),r[i][j]=min(r[i][j],r[i-1][j]);
			up[i][j]=up[i-1][j]+1;ans=max(ans,(r[i][j]-l[i][j]+2)*(up[i][j]+1));
		}
	}
	cout<<ans<<endl;
 	return 0;
}
```


---

## 作者：Ebola (赞：4)

如果方格是2\*2的，不难发现，当且仅当方格内有偶数个黑格子，可以翻成全黑

把结论拓展到大方格中，容易证明，一个大方格能翻成全黑，当且仅当所有2\*2的子矩形内都有偶数个黑格子

于是我们可以在每个2\*2子矩形的中央扣一个绿帽，于是问题变成了求一个内部（包括边界）全是绿帽的最大子矩形。可以用单调栈来维护。具体地，对于每行的一个位置，记h\[y\]表示y这一列从这行往上数有多少个连续的绿帽，向左右分别扩展至第一个h比它小的位置，然后这一段的长度乘上h\[y\]就是这一个位置对答案的贡献

最后不要忘记max(n,m)对答案的贡献

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2010;
bool mp[N][N],good[N][N];
int deep[N][N];
int L[N],R[N];
int s[N],top;
char ss[N];
int H,W,ans=0;

int main()
{
    scanf("%d%d",&H,&W);
    for(int i=1;i<=H;i++)
    {
        scanf("%s",ss+1);
        for(int j=1;j<=W;j++)
            mp[i][j]=(ss[j]=='#');
    }
    for(int i=1;i<H;i++)
        for(int j=1;j<W;j++)
        {
            int cnt=mp[i][j]+mp[i+1][j]+mp[i][j+1]+mp[i+1][j+1];
            good[i][j]=!(cnt&1);
        }
    for(int i=1;i<=H;i++)
        for(int j=1;j<=W;j++)
            deep[i][j]=good[i][j]?deep[i-1][j]+1:0;
    for(int i=1;i<=H;i++)
    {
        s[top=1]=0;
        for(int j=1;j<W;j++)
        {
            while(top&&deep[i-1][s[top]]>=deep[i-1][j]) top--;
            L[j]=s[top];s[++top]=j;
        }
        s[top=1]=W;
        for(int j=W-1;j>=1;j--)
        {
            while(top&&deep[i-1][s[top]]>=deep[i-1][j]) top--;
            R[j]=s[top];s[++top]=j;
        }
        for(int j=1;j<W;j++)
            ans=max(ans,(deep[i-1][j]+1)*(R[j]-L[j]));
    }
    ans=max(ans,max(H,W));
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：THE_Archangel (赞：2)

提供一个应该算不太需要多发现性质的做法。

首先能发现一个矩阵是合法的，当且仅当它的每一行都和第一行一样，或正好相反。

充分性很显然，必要性的证明如下：

考虑一个矩阵如果合法，那必然能从一个全黑的矩阵进行若干次操作，因为操作是可逆的。然后如果操作行会使其与第一行相反，操作列不会影响其他行与第一行的相对状态。

令 $s$ 表示原矩阵，$a_{i,j}=[s_{i,j}=\#]$。

构造数组 $b_{i,j}=a_{i,j}\oplus a_{i+1,j}$。

则可以发现一个合法矩阵，每一行一定是全 $0$ 或全 $1$。

于是可以在 $\mathcal O(nm)$ 时间内递推处理出每个位置最多能往左扩展的长度 $mx_{i,j}$，用单调栈处理出每个位置向上最多能扩展到的位置 $Up_{i,j}$，向下最多能扩展到的位置 $Down_{i,j}$。

然后就可以用 $(Down_{i,j}-Up_{i,j}+2)\times mx_{i,j}$ 更新答案。

注意单独的行和列也是合法的，于是答案要和 $n,m$ 取个 $\max$。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, m, ans;
char s[N][N];
int a[N][N];
int mx[N], Up[N], Down[N];
int stk[N], top;

int main() {
	scanf("%d%d", &n, &m), ans = max(n, m);
	for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j <= m; ++j)
			a[i][j] = s[i][j] != s[i + 1][j];
		a[i][0] = -1;
	}
	for (int j = 1; j <= m; ++j) {
		for (int i = 1; i < n; ++i)
			if (a[i][j] == a[i][j - 1]) ++mx[i];
			else mx[i] = 1;
		top = 0;
		for (int i = 1; i < n; ++i) {
			while (top && mx[stk[top]] >= mx[i]) --top;
			Up[i] = stk[top] + 1, stk[++top] = i;
		}
		top = 0;
		for (int i = n - 1; i; --i) {
			while (top && mx[stk[top]] >= mx[i]) --top;
			Down[i] = top ? stk[top] - 1 : n - 1, stk[++top] = i;
		}
		for (int i = 1; i < n; ++i)
			ans = max(ans, (Down[i] - Up[i] + 2) * mx[i]);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：1)

严肃抨击洛谷管理员七篇题解就关通道的行为。

---

我秉持着一向观察不到性质的作风，使用暴力方法通过了此题。

记两个 01 串“匹配”的长度为它们的最长公共前缀或者最长全不等前缀的长度。

考虑枚举矩形的第一列，记为 $s$。那么问题显然可以转化为一堵 $H-1$ 列的墙，第 $i$ 列的高度为第 $i$ 个串和第 $i+1$ 个串在 $s$ 之后的子串的匹配长度，在这一堵墙上找一个最大矩形。

这个文字说的我自己都看不懂，所以我拿第一组样例举例。$s=1$ 时相邻两行的匹配长度分别为 $3,1$，而 $s=2$ 时相邻两行的匹配长度分别为 $2,2$。那么在第一堵墙上能得到的面积就是 $6$（别忘了，匹配的一个 $3$ 表示两个字符串共有的长度，所以是 $3+3$）。同理，第二堵墙上最大面积也是 $6$，因为两个 $2$ 要算三次。

接下来考虑 $s\to s+1$ 的过程。那么对于高度不为 $1$ 的墙，高度 $-1$ 即可，因为不可能有新的匹配。高度为 $1$ 的墙就需要重新进行匹配了，直接暴力扫即可。由于每两行之间的匹配计算过程只会从左往右扫一遍，所以维护墙的高度的复杂度是 $O(HW)$ 的。

找最大矩形的过程就不用多说了吧！因为我早已学会了笛卡尔树的使用，所以我就用笛卡尔树找到了最大矩形。如果你这一部分不会的话，我建议你去学一学笛卡尔树，然后你就会了。

代码很好写，这里就不放了。祝你成功。

---

## 作者：_Hermione_ (赞：1)

这道题其实就是一个普通的悬线法：通过若干次操作后找出最大全$1$矩阵，关键在于如何确定障碍点和非障碍点。

观察一下样例一

可以画出下面这个图

![](https://cdn.luogu.com.cn/upload/image_hosting/63rg72ls.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

看左上角那个$2×2$的矩阵，我们可以通过反转第一行来使它变成一个全$1$矩阵。

而对于左下角那个$2×2$的矩阵的矩阵而言，可以发现无论做多少次操作它都无法变成一个全$1$矩阵。

通过对比发现：左上角那个$2×2$的矩阵可以变成一个全$1$矩阵是因为它有偶数个$1$，而左下角那个$2×2$的矩阵的矩阵无法变成一个全$1$矩阵是因为它有奇数个$1$。

所以可以得出结论：

**对于有偶数个1的矩阵，
可以通过若干次操作后使它变成一个全1矩阵，
反之则不能。**

------------

 _在这里声明一下：下文提到的 “全 $1$矩阵 ”是指可以通过若干次操作后变成全 $1$矩阵的矩阵（即有偶数个1的矩阵），它在操作之前不一定是全 $1$矩阵_

------------

因为所有的大矩形都是由若干个$2×2$矩阵组成的，所以一个矩阵里要全部是全$1$矩阵，那么这个矩阵必定也是一个全$1$矩阵；同理，如果一个矩阵里包含了非全$1$矩阵，那么这个矩阵一定不是全$1$矩阵。

我们可以把所有的$2×2$矩阵看成点，有偶数个$1$的$2×2$矩阵标记为$1$，就是非障碍点，反之为$0$，就是障碍点。

这样我们就确定了障碍点和非障碍点，就可以通过枚举所有的极大子矩阵（即所有全$1$矩阵），来找出最大子矩阵。

特别地，对于样例二，我们可以把所有的点转化为$1$，所以整个大矩阵就是一个全$1$矩阵，面积为$16$。

------------

至于悬线法，
[戳这里](https://oi-wiki.org/misc/hoverline/)

（这是oi wiki里的一篇文章，本人当时就是看这篇文章学习的悬线法 ^_^）



------------

Code
```cpp
#include "iostream"
#include "cstdio"

#define N 2005

using namespace std;

int n,m,ans;
int l[N][N],r[N][N],up[N][N];
bool a[N][N];

int main()
{
	scanf("%d%d",&n,&m);
	ans=max(n,m);
	for(int i=1;i<=n;i++)
	{
	    for(int j=1;j<=m;j++)
	    {
	    	char c;
	    	cin>>c;
	    	if(c=='#')
	    		a[i][j]=true;
	    }
	}
	n--;m--;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
	    	a[i][j]=!((a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1])&1);
	    	l[i][j]=r[i][j]=j;
	    }
	for(int i=1;i<=n;i++)
		for(int j=2;j<=m;j++)
	    	if(a[i][j]&&a[i][j-1])
				l[i][j]=l[i][j-1];
	for(int i=1;i<=n;i++)
	    for(int j=m-1;j;j--)
	    	if(a[i][j]&&a[i][j+1])
	        	r[i][j]=r[i][j+1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j])
				up[i][j]=up[i-1][j]+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]&&a[i-1][j])
			{
	    		l[i][j]=max(l[i][j],l[i-1][j]);
	         	r[i][j]=min(r[i][j],r[i-1][j]);
	       	}
	       	ans=max(ans,(r[i][j]-l[i][j]+2)*(up[i][j]+1));
		}
	printf("%d\n",ans);
	return 0;
}
```

------------

蒟蒻的第一篇题解，刚交的时候没有过……原因是不够详细。

现在改了改，希望内容质量能有所提升~

---

## 作者：_edge_ (赞：0)

该题需要稍微转化，首先说一下我的想法。

~~很容易发现~~如果一个矩形需要满足条件，那么必须有第一行异或之后等于另外行，或者第一行就等价于另外行。

然后这个时候，我们就能写出 $O(n^3)$ 的做法，枚举矩形上边界和下边界，然后从左往右扫描即可。

然后我们思考正解。

这里感谢 @kobe303 学长教的一步，就是把上一行和这一行异或一下，这样会发现这个所求的矩形即为一行全 $0$ 或者一行全 $1$，这东西可以很好的用单调栈优化。

具体的，我们处理每一个 $(x,y)$ 向左能延伸到哪里，然后利用单调栈求出他上边界和下边界。

更具体的，对于一个满足要求的子矩形，一定满足有一行是顶着左边界的，因此，我们可以枚举这一行，然后用单调栈求上边界和下边界。

具体的可以参考最大全黑子矩形的做法。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define pb push_back
using namespace std;
const int INF=2e3+5;
const int Mod=1e9+7;
const int base=233;
int n,m,a[INF][INF],b[INF][INF],ba[INF],U[INF][INF];
int hash1[INF][INF],hash2[INF][INF],d[INF];
int Get(int x,int l,int r) {
    return (hash1[r][x]-hash1[l-1][x]*ba[r-l+1]%Mod+Mod)%Mod;
}
int Get1(int x,int l,int r) {
    return (hash2[r][x]-hash2[l-1][x]*ba[r-l+1]%Mod+Mod)%Mod;
}
int check(int l,int r,int xx,int ll,int rr,int yy) {
    if (Get(xx,l,r)==Get(yy,ll,rr)) return 1;
    else if (Get1(xx,l,r)==Get(yy,ll,rr)) return 1;
    else return 0;
}
// void del(int x) {
//     L[R[x]]=L[x];
//     R[L[x]]=R[x];
// }
char Map[INF][INF];

int q[INF],r,R[INF][INF],L[INF][INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;int ans=max(n,m);
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            cin>>Map[i][j];
            if (Map[i][j]=='#') a[i][j]=1;
            b[i][j]=a[i][j]^1;
        }
    }
    
    for (int i=1;i<n;i++) {
        for (int j=1;j<=m;j++)
            b[i][j]=a[i+1][j]^a[i][j];
        b[i][0]=-1;
    }

    for (int i=1;i<n;i++) {
        for (int j=1;j<=m;j++)
            if (b[i][j]==b[i][j-1]) U[i][j]=U[i][j-1];
            else U[i][j]=j;
    }
    for (int j=1;j<=m;j++) {
        r=0;
        for (int i=1;i<n;i++) {
            while (r>0 && U[q[r]][j]<=U[i][j]) r--;
            L[i][j]=q[r]+1;
            q[++r]=i;
        }  
    }

    for (int j=m;j>=1;j--) {
        r=0;
        for (int i=n-1;i;i--) {
            while (r>0 && U[q[r]][j]<=U[i][j]) r--;
            if (r) R[i][j]=q[r]-1;
            else R[i][j]=n-1;
            q[++r]=i;
        }
    }
    // cout<<U[2][3]<<" "<<U[1][3]<<" awejri\n";
    for (int i=1;i<n;i++) {
        for (int j=1;j<=m;j++) {
            // cout<<R[i][j]<<" "<<L[i][j]<<" "<<i<<" "<<j<<" "<<U[i][j]<<" ?\n";
            ans=max(ans,(R[i][j]-L[i][j]+2)*(j-U[i][j]+1));
        }    
    }
    cout<<ans<<"\n";
    return 0;
}
```


---

