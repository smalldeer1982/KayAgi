# [ABC260G] Scalene Triangle Area

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc260/tasks/abc260_g

$ N\ \times\ N $ のグリッドがあり、このグリッドの上から $ i $ マス目、左から $ j $ マス目を $ (i,j) $ と呼びます。  
 このグリッドの各マスには高々 $ 1 $ 個のコマが置かれています。  
 グリッドの状態は $ N $ 個の文字列 $ S_i $ として与えられ、

- $ S_i $ の $ j $ 文字目が `O` であるとき $ (i,j) $ に $ 1 $ つコマが置かれていること
- $ S_i $ の $ j $ 文字目が `X` であるとき $ (i,j) $ にコマは置かれていないこと

を表します。

整数 $ M $ が与えられます。 この $ M $ を使って、 $ (s,t) $ に置かれているコマ $ P $ について、以下の条件を全て満たすマス $ (u,v) $ を $ P $ が守っているマスと定義します。

- $ s\ \le\ u\ \le\ N $
- $ t\ \le\ v\ \le\ N $
- $ (u\ -\ s)\ +\ \frac{(v\ -\ t)}{2}\ <\ M $

$ Q $ 個のマス $ (X_i,Y_i) $ について、そのマスを守っているコマの個数を求めてください。

## 说明/提示

### 制約

- $ N,M,X_i,Y_i,Q $ は整数
- $ 1\ \le\ N\ \le\ 2000 $
- $ 1\ \le\ M\ \le\ 2\ \times\ N $
- $ S_i $ は `O`, `X` からなる
- $ 1\ \le\ Q\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ X_i,Y_i\ \le\ N $

### Sample Explanation 1

マス $ (1,1) $ のみにコマが置かれ、このコマによって以下の `#` のマスが守られます。 ``` #### ##.. .... .... ```

## 样例 #1

### 输入

```
4 2
OXXX
XXXX
XXXX
XXXX
6
1 1
1 4
2 2
2 3
3 1
4 4```

### 输出

```
1
1
1
0
0
0```

## 样例 #2

### 输入

```
5 10
OOOOO
OOOOO
OOOOO
OOOOO
OOOOO
5
1 1
2 3
3 4
4 2
5 5```

### 输出

```
1
6
12
8
25```

## 样例 #3

### 输入

```
8 5
OXXOXXOX
XOXXOXOX
XOOXOOXO
OXOOXOXO
OXXOXXOX
XOXXOXOX
XOOXOOXO
OXOOXOXO
6
7 2
8 1
4 5
8 8
3 4
1 7```

### 输出

```
5
3
9
14
5
3```

# 题解

## 作者：wnsyou (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc260_g)

## 题意

给定一个大小为 $n\times n$ 的字符矩阵，每个字符为 `X` 或者 `O`。

对于一个位于 $(x,y)$ 的字符 `o` 和一个格子 $(u,v)$，如果满足以下条件，那么 $(u,v)$ 就可以被 $(x,y)$ 控制。

- $x \leqslant u \leqslant n$，$y \leqslant v \leqslant n$。
- $(u-x)+\frac{v-y}{2} < m$。

给定 $m$ 和询问数 $Q$，每次询问给定 $u$ 和 $v$，求有多少个格子可以控制 $(u,v)$。

## 思路

分为两种做法。

### 0x00

![](https://cdn.luogu.com.cn/upload/image_hosting/zl7sw99g.png)

推一推式子，可以发现：

- 第 $x$ 行第 $(y - 2 \times m) \sim y$ 列的 `O` 都可以控制 $(x,y)$。
- 第 $x - 1$ 行第 $(y - 2 \times (m - 1)) \sim y$ 列的 `O` 都可以控制 $(x,y)$。
- 以此类推。
- 第 $x - m + 1$ 行第 $y - 1$ 列与第 $y$ 列的 `O` 可以控制 $(x,y)$。
- 第 $1 \sim (x - m)$ 行没有可以控制 $(x,y)$ 的格子。

做法就出来了，对于每次询问在线求答案即可。

还有一个小问题，枚举每一行和每一列求答案是 $O(n^2)$ 的，但每一行对答案有贡献的部分是一个区间，可以用前缀和优化，总时间复杂度为 $O(n^2+ Q\times n)$，**并不是最优解法，但可以过此题。**

```cpp
#include <iostream>

using namespace std;

int n, m, q, x, y, sum[2010][2010];
char c;

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c;
      sum[i][j] = sum[i][j - 1] + (c == 'O'); // n 行的前缀和
    }
  }
  for (cin >> q; q; q--) {
    cin >> x >> y;
    int cnt = 0;
    for (int i = 0; i < m && x - i; i++) { // 枚举每一行，如果超出矩阵范围就退出循环
      cnt += sum[x - i][y] - sum[x - i][max(0, y - 2 * (m - i))]; // 前缀和
    }
    cout << cnt << '\n';
  }
  return 0;
}
```

### 0x01

二维差分。

![](https://cdn.luogu.com.cn/upload/image_hosting/sqn8fsfr.png)

对于一个位于 $(x,y)$ 的 `O`，可以控制的范围如上，其他的自己推一下（

先对于每一行列差分一下，变成下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2mretq9q.png)

观察上图，可以发现：第一列可以轻松的用行差分优化，但后面的 $-1$ 怎么办呢？

我们要引入一个差分思想：一个不行就两个！

把这个差分矩阵拆成两个，在最后还原时将两个矩阵加起来。

![](https://cdn.luogu.com.cn/upload/image_hosting/p0ykfv99.png)

左边矩阵差分点只有两个，可以 $O(1)$ 处理差分，可右边怎么办呢？

仔细观察一下，欸，$-1$ 的位置有规律！

将右边矩阵优化成下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/d6pzcg82.png)

差分矩阵通过前缀和思想还原原矩阵，上图每次只要加上 $(x - 1,y + 2)$ 的值就可以了，还原原矩阵时需要将两个差分矩阵加起来，再对它进行列前缀和即可，时间复杂度 $O(n^2+Q)$。

具体实现看代码。

```cpp
#include <iostream>

using namespace std;

int n, m, q, x, y, sum[2010][2010], num[2010][12010][2]; // 注意数组的大小
char c;

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c;
      if (c == 'O') {
        num[i][j][0]++, num[min(n + 1, i + m)][j][0]--; // 左边矩阵
        num[i][j + 2 * m][1]--, num[min(n + 1, i + m)][j][1]++; // 右边矩阵
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n + 2 * m; j++) {
      num[i][j][1] += num[i - 1][j + 2][1]; // 左右矩阵各自进行还原
      num[i][j][0] += num[i - 1][j][0];
      if (j <= n) {
        sum[i][j] = sum[i][j - 1] + num[i][j][1] + num[i][j][0]; // 最终的矩阵还原
      }
    }
  }
  for (cin >> q; q; q--) {
    cin >> x >> y;
    cout << sum[x][y] << '\n';
  }
  return 0;
}
```

---

## 作者：__YSC__ (赞：2)

# 题目描述

有一个 $N×N$ 的矩阵。第 $i$ 行第 $j$ 列的格子用 $(i,j)$ 表示。每个格子上最多一个棋子。矩阵用 $N$ 个字符串 $
S_i$表示：

- 如果 $S_i$ 的第 $j$ 个字符为 `O`，则 $(i,j)$ 上有一个棋子。
- 如果 $S_i$ 的第 $j$ 个字符为 `X`，则 $(i,j)$ 上没有棋子。

给定整数 
$M$。我们定义格子 $(s,t)$ 上的棋子 $P$ 覆盖了格子 $(u,v)$ 当且仅当满足以下所有条件：

- $s \le u \le N$。
- $t \le v \le N$。
- $(u-s)+\frac{v-t}{2}<M$。

给定 $Q$ 次询问，每次询问给出格子 $(X_i,Y_i)$，请你求出有多少棋子覆盖该格子。

# 思路

可以发现，题目的要求就是在覆盖一个三角形，具体如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/6fjvs99p.png)

很容易可以想到差分，首先横着做一遍差分，得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/cqfiood0.png)

竖着的部分很容易处理，但是斜着的该怎么办呢？

可以分开处理竖着的和斜着的，得到以下两个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ekvu7nkp.png)

对这两个图前缀和后累加起来，最后再做一遍横向的前缀和即可。

时空复杂度均为 $O(N(N+M))$。

## 细节

注意数组的第二维要开到 $1.2 \times 10^4$，枚举时也要枚举到 $N + 2M$，因为那个位置可能会对答案造成影响。以及在列方向上差分时要注意与 $N+1$ 取最小值，因为 $N+1$ 行对答案没有影响。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2010;

int n, m, q, sum[MAXN][MAXN], a[MAXN][6 * MAXN], b[MAXN][6 * MAXN];

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      char c;
      cin >> c;
      if(c == 'O') {
        a[i][j]++, a[min(n + 1, i + m)][j]--, b[i][j + 2 * m]--, b[min(n + 1, i + m)][j]++;
      }
    }
  }
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n + 2 * m; ++j) {
      a[i][j] += a[i - 1][j];
    }
  }
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n + 2 * m; ++j) {
      b[i][j] += b[i - 1][j + 2];
    }
  }
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      sum[i][j] = sum[i][j - 1] + a[i][j] + b[i][j];
    }
  }
  cin >> q;
  while(q--) {
    int x, y;
    cin >> x >> y;
    cout << sum[x][y] << "\n";
  }
  return 0;
}

```

---

## 作者：jokersen (赞：1)

由于校内 OJ 不是很快，所以加的常数优化有些多，应该是比其他题解中的 $\Theta(nq)$ 做法要快的。

---

带着**正难则反**的思想，我们现将问题转化一下：

>求一个格子能被纸条覆盖到的范围中**纸条的数量**。

可以发现，他所求的答案是个梯形。

于是便可以计算时枚举第几行，循环内部求出这一行的可覆盖到它纸条数就行了。

显然，每一行的答案都是一个**连续的区间**。

不难想到每一行单独作**前缀和**，以实现 $\Theta(1)$ 计算每一行的答案。

再~~略微~~卡常即可通过。

**[AC记录](https://atcoder.jp/contests/abc260/submissions/66004987)**
```cpp
#include<bits/stdc++.h>
#define getc() (ux==vx&&(vx=(ux=In)+fread(In,1,32768,stdin),ux==vx)?EOF:*ux++)
char In[32768],*ux=In,*vx=In;
//fread优化读入
using namespace std;
int pre[2005][2005],vis[2005][2005];
inline void read(int &n){
    char c=getc();n=0;
	while(c<'0'||c>'9') c=getc();
    while(c>='0'&&c<='9') n=(n<<1)+(n<<3)+(c^48),c=getc();
}
inline void sread(short &n){
    char c=getc();n=0;
	while(c<'0'||c>'9') c=getc();
    while(c>='0'&&c<='9') n=(n<<1)+(n<<3)+(c^48),c=getc();
}
//快读
void print(int x){
	if(!x) return putchar('0'),void();
	short a[10],tot=0;
	while(x) a[tot++]=x%10,x/=10;
    while(tot--) putchar(a[tot]^48);
}
//快写(手写栈实现)
int main(){
	int q;
	char c;
	short n,m;
    sread(n),sread(m);
    for(short i=1;i<=n;++i) for(short j=1;j<=n;++j){
        c=getc();
        while(c!='X'&&c!='O') c=getc();
        pre[i][j]=pre[i][j-1]+(c=='O');//前缀和
    }
    read(q);
    while(q--){
		int ans=0;
		short u,v;
        sread(u),sread(v);
		if(vis[u][v]){//防重复计算(应该用处不大)
			print(vis[u][v]),puts("");
			continue;
		}
        for(int i=1;i<=u;++i){
            int l=v+(u-m-i<<1|1),r=v;//每一行答案区间的左右端点。
			if(l>r) continue;//判断右端点在左端点左边的请况
            if(l<1) l=1;//边界
            ans+=pre[i][r]-pre[i][l-1];//求区间答案
        }
        print(vis[u][v]=ans),puts("");
    }
    return 0;
}
```

---

## 作者：AlicX (赞：1)

## Solution

发现 $n \times q$ 是 $4 \times 10^8$ 的，可以通过，所以考虑使用在线做法前缀和。

对于一对 $(x,y)$，能控制它的点的个数可以通过每一行可以控制它的点相加得到。先把式子变化一下：$j>y-2 \times (m-x+i)$。然后就非常明朗了，对于每一行统计出字符 `O` 的个数，在询问时枚举每一行，就可以得出 $y$ 的范围，最后前缀和求解。

```cpp
#include<bits/stdc++.h>
using namespace std; 
const int N=2010;
int n,m,q; 
int s[N][N]; 
signed main(){
	cin>>n>>m; 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c; cin>>c;
			s[i][j]=s[i][j-1]+(c=='O'); 
		}
	} cin>>q; 
	while(q--){ 
		int ans=0; 
		int x,y; cin>>x>>y; 
		for(int i=1;i<=x;i++){ 
			int l=y-2*(m-x+i)+1,r=y; 
			if(l>y) continue; if(l<1) l=1;  
			ans+=s[i][r]-s[i][l-1]; 
		} cout<<ans<<endl; 
	} return 0;  
} //j>y-2(m-x+i) 
```

---

## 作者：WaterSun (赞：0)

# 思路

对于每一行 `O` 的个数，我们可以用前缀和预处理出来。

那么，对于每一次询问时，能够控制 $(x,y)$ 的点，一定在以 $(x,y)$ 为右下角，边长分别为 $\min(m,x)$ 和 $\min(m,y)$ 的矩形。

那么，我们考虑循环这个矩阵的每一行。因为我们已经预处理出每一行 $i$，前 $j$ 的位置有 `O` 的数量 $s_{i,j}$。

由此，用前缀和表示第 $i$ 行的贡献（这里的第 $i$ 行表示的是从 $x$ 向上数 $i$ 行）：

$$
s_{x - i,y} - s_{x - i,y - 2 \times (m - i)}
$$

**注意：$y - 2 \times (m - 1)$ 有可能小于 $0$，要和 $0$ 取 $\max$。**

时间复杂度 $\Theta(mq)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2010;
int n,m,q;
int s[N][N];
char arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++){
		scanf("%s",arr + 1);
		for (re int j = 1;j <= n;j++){
			if (arr[j] == 'O') s[i][j] = s[i][j - 1] + 1;
			else s[i][j] = s[i][j - 1];
		}
	}
	q = read();
	while (q--){
		int x,y,ans = 0;
		x = read();
		y = read();
		for (re int i = 0;i < min(m,x);i++) ans += s[x - i][y] - s[x - i][max(y - 2 * (m - i),0)];
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：xiehanrui0817 (赞：0)

题目：AT_abc260_g

链接：[洛谷](https://www.luogu.com.cn/problem/AT_abc260_g])， [AT](https://atcoder.jp/contests/abc260/tasks/abc260_g)，[vjudge](https://vjudge.csgrandeur.cn/contest/555372#problem/F)

# 题意

- 有一个 $n \times n$ 的矩阵和 $m$ 个棋子，若 $(x, y)$ 是棋子并且 $x <= u, y <= v, (u - x) + \frac{v - y}{2} < m$，那么 $(x, y)$ 就控制了 $(u, v)$，给定 $q$ 组询问，每次给定一个点，问这个点被几个棋子控制。

- 数据范围：$1 \le n \le 2000, 1 \le m \le 2n, 1 \le q \le 2 \times 10^5$。

# 思路

- 可以发现一个棋子可以覆盖的区域像一下区域（红色为棋子，黑色为它控制的点），像一个三角形 （$m = 4$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/hwm7fd7m.png)

- 如果我们把这个三角形内的所有元素 $+1$，最后我们只用输出给定点对应的元素值即可。然后我们发现直接暴力 $+1$ 会超时，首先我们可以做一个列差分，得到下图（$m = 4$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/zpnt42xu.png)

- 然后我们发现直接做列差分是不行的，那该怎么办呢？我们可以把这个图变成两个图，一个做一次行差分，另一个可以斜着做一个差分，这样我们就用 $O(1)$ 做了一个差分，参照下图。做完差分后我们只用把两个差分数组合起来做一遍二维前缀和就得到了答案，$q$ 组询问可以 $O(1)$ 回答。

![](https://cdn.luogu.com.cn/upload/image_hosting/ke17f2oc.png)

- 时间复杂度
  - 每个棋子都做一次差分：$O(n^2)$。
  - 前缀和：$O(n^2)$。
  - $q$ 组询问，每组 $O(1)$，共 $O(q)$
  - 总时间复杂度：$O(n^2 + q)$

---

## 作者：__yabnto__ (赞：0)

### [ABC260G] Scalene Triangle Area
### 题意
有一个 $n \times n$ 的矩阵，里面由 `XO` 组成，对于一个 `O`，如果它的坐标是 $(u, v)$ 那么它所可以影响的点的坐标是 $(x, y)$，其中 $(x, y)$ 满足以下条件：

- $u\le x$

- $v\le y$

- $(x-u)+\dfrac{(y-v)}{2}<M$

给定 $N,M,Q$ 和 $Q$ 次询问 $X_i,Y_i$，询问这个位置被几个 `O` 控制。

### 思路

1.暴力（虽然也能过）

对于一个 `O`,它肯定可以影响几行，而每一行也肯定是连续的一段，那么可以枚举行然后计算连续的一段的左端点和右端点，然后前缀和计算（由于后面有正解，这里就不详细解释了）。

```cpp
#include <iostream>

using namespace std;

const int MaxN = 2010;

int f[MaxN][MaxN], n, m, l, r, q, ans;
char c[MaxN][MaxN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c[i][j], f[i][j] = f[i][j - 1] + (c[i][j] == 'O');
    }
  }
  for (cin >> q; q; q--) {
    cin >> l >> r, ans = 0;
    for (int i = max(l - m, 1); i <= l; i++) {
      int j = max(r - (m - (l - i)) * 2, 0);
      (j <= r) && (ans += f[i][r] - f[i][j]);
    }
    cout << ans << '\n';
  }
  return 0;
}
```

2.正解 差分

我们来看这样一组数据
```
OXXXXXXXX
XXXXXXXXX
XXXXXXXXX
XXXXXXXXX
XXXXXXXXX
XXXXXXXXX
XXXXXXXXX
XXXXXXXXX
XXXXXXXXX
```
而 $m$ 设为 
$3$，那么可以得知 `O` 所影响的点是（$1$ 表示影响了）：
```
111111000
111100000
110000000
000000000
……………………
```
那么由于是二位差分所以先以列的方向做差分，可以得到：
```
1,0,0,0,0,0,-1,0,0
1,0,0,0,-1,0,0,0,0
1,0,-1,0,0,0,0,0,0
……………………
```
得到这个后会发现如果直接以行的方向做差分是不行的所以可以把它拆开得到：
```
1,0,0,0,0,0,0,0,0
1,0,0,0,0,0,0,0,0
1,0,0,0,0,0,0,0,0
……………………
```
和：
```
0,0,0,0,0,0,-1,0,0
0,0,0,0,-1,0,0,0,0
0,0,-1,0,0,0,0,0,0
……………………
```
这时第一个矩阵可以做以行的方向做差分了：
```
1,0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0,0
-1,0,0,0,0,0,0,0,0
……………………
```
那第二个矩阵怎么办？很简单，只要以斜着做差分就行了，如下图所示：
```
0,0,0,0,0,0,-1,0,0
0,0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0,0
1,0,0,0,0,0,0,0,0
……………………
```
![](https://cdn.luogu.com.cn/upload/image_hosting/j80f4k2b.png)
这样就可以了，这四个差分点分别就是（$i, j$ 表示 `O` 的位置）：$(i, j), (i + m, j), (i, j + 2 \times m), (i + m, j)$

最后反着还原原数组即可。
```cpp
#include <iostream>

using namespace std;

const int MaxN = 2010;

int n, m, t, l, r;
char c[MaxN][MaxN];
int q[MaxN * 3][MaxN], x[MaxN * 3][MaxN * 5], st[MaxN * 3][MaxN * 5];

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c[i][j];
      if (c[i][j] == 'O') {
        q[i][j]++, q[i + m][j]--, x[i][j + 2 * m]--, x[i + m][j]++;
      }
    }
  }
  for (int i = 1; i <= n + m; i++) {
    for (int j = 1; j <= n + 2 * m; j++) {
      x[i][j] += x[i - 1][j + 2];
    }
  }
  for (int i = 1; i <= n + m; i++) {
    for (int j = 1; j <= n; j++) {
      q[i][j] += q[i - 1][j];
    }
  }
  for (int i = 1; i <= n + m; i++) {
    for (int j = 1; j <= n + 2 * m; j++) {
      st[i][j] = q[i][j] + x[i][j];
    }
  }
  for (int i = 1; i <= n + m; i++) {
    for (int j = 1; j <= n + 2 * m; j++) {
      st[i][j] += st[i][j - 1];
    }
  }
  for (cin >> t; t; t--) {
    cin >> l >> r;
    cout << st[l][r] << '\n';
  }
  return 0;
}
```
这是本蒟蒻的第一篇题解，请管理大大放宽放宽吧。

---

