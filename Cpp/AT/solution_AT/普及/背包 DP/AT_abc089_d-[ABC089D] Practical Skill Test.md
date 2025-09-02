# [ABC089D] Practical Skill Test

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc089/tasks/abc089_d

$ H $ 行 $ W $ 列のマス目があり、$ i $ 行目の $ j $ 列目のマスをマス $ (i,j) $ と呼びます。

このマス目には $ 1 $ から $ H×W $ までの整数が重複なく書かれており、マス $ (i,j) $ に書かれている整数は $ A_{i,j} $ です。

魔法少女であるあなたは、魔力 $ |x-i|+|y-j| $ を消費することでマス $ (i,j) $ に置かれた駒をマス $ (x,y) $ に瞬間移動させることができます。

あなたは、魔法少女としての能力を計るために、$ Q $ 回の実技試験を受けなければなりません。

$ i $ 回目の実技試験は、以下の手順で行われます。

- 初めに、駒が整数 $ L_i $ の書かれているマスに置かれている。
- 駒の置かれているマスに書かれている整数を $ x $ とする。$ x $ が $ R_i $ でない限り、駒を $ x+D $ の書かれているマスに移動することを繰り返す。$ x=R_i $ となったら終了する。
- ただし、$ R_i-L_i $ が $ D $ の倍数であることは保証される。

それぞれの実技試験に対し、あなたの消費する魔力の総和を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 300 $
- $ 1\ \leq\ D\ \leq\ H×W $
- $ 1\ \leq\ A_{i,j}\ \leq\ H×W $
- $ A_{i,j}\ \neq\ A_{x,y}\ ((i,j)\ \neq\ (x,y)) $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ H×W $
- $ (R_i-L_i) $ は $ D $ の倍数

### Sample Explanation 1

\- $ 4 $ が書かれたマスは、マス $ (1,2) $ です。 - $ 6 $ が書かれたマスは、マス $ (3,3) $ です。 - $ 8 $ が書かれたマスは、マス $ (3,1) $ です。 よって、$ 1 $ 回目の実技試験であなたの消費する魔力の総和は、$ (|3-1|+|3-2|)+(|3-3|+|1-3|)=5 $ です。

### Sample Explanation 2

駒を全く移動しない実技試験が存在する場合や、複数の実技試験の内容が同じ場合に注意してください。

## 样例 #1

### 输入

```
3 3 2
1 4 3
2 5 7
8 9 6
1
4 8```

### 输出

```
5```

## 样例 #2

### 输入

```
4 2 3
3 7
1 4
5 2
6 8
2
2 2
2 2```

### 输出

```
0
0```

## 样例 #3

### 输入

```
5 5 4
13 25 7 15 17
16 22 20 2 9
14 11 12 1 19
10 6 23 8 18
3 21 5 24 4
3
13 13
2 10
13 13```

### 输出

```
0
5
0```

# 题解

## 作者：Vector_ (赞：2)

## 题目大意

- 给定一个 $h\times w$ 的矩阵，上面分别是 $1,2,...,h \times w$ 的每一个数。有 $Q$ 次询问，每次询问从数 $l$ 移动到数 $r$ 的代价。

- 每次移动的代价为两个数在矩阵上的曼哈顿距离。

- 移动方式为先从 $l$ 移动到 $l+d$，再移动到 $l+2\times d$ ... 直到移动到 $r$。其中 $d$ 是一开始给定的常数。保证 $r-l$ 是 $d$ 的倍数。

- $1 \le h,w\le 300,1 \le d \le h \times w,1 \le Q \le 10^5$

## 题目分析

我们发现本题的询问具有加和性质，即先从 $a$ 到 $b$，再从 $b$ 到 $c$ 的代价之和等于从 $a$ 到 $c$ 的代价和。所以本题可以利用前缀和思想求解。

利用前缀和思想，先预处理出从 $1..d$ 移动到 $d+1..h \times w$ 的每一个数的代价，询问时只需要输出到达 $r$ 的代价减去到达 $l$ 的代价即可。

关于预处理，记 $dp_i(i>d)$ 为从 $i$ $mod$ $d$ 到达 $i$ 的代价，显然由题意有

$$dp_i=dp_{i-d}+abs(x_i-x_{i-d})+abs(y_i-y_{i-d})$$

其中 $x_i,y_i$ 分别是数 $i$ 的横、纵坐标。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[90010],y[90010],dp[90010];
int read(){int x;scanf("%d",&x);return x;
int main()
{
	int h=read(),w=read(),d=read(),n=h*w;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
		{
			int now=read();
			x[now]=i;
			y[now]=j;
		}
	for(int i=d+1;i<=n;i++) dp[i]=dp[i-d]+abs(x[i]-x[i-d])+abs(y[i]-y[i-d]);//预处理
	int q=read();
	while(q--)
	{
		int l=read(),r=read();
		printf("%d\n",dp[r]-dp[l]);//利用前缀和思想回答每次询问
	}
	return 0;
}
```

---

## 作者：__WaveN__ (赞：2)

# [ABC089D] Practical Skill Test

### 题目大意

给定一个 $h\times w$ 的矩阵和一个 $d$，上面分别是 $1,2, \cdots ,h \times w$ 的每一个数。有 $Q$ 次询问，每次询问从数 $l$ 移动到数 $r$ 的代价。

每次移动的代价为两个数在矩阵上的曼哈顿距离。

移动方式为先从 $l$ 移动到 $l+d$，再移动到 $l+2\times d \cdots $ 直到移动到 $r$。

### 思路分析

运用**前缀和**思想，用 `dis` 数组预处理从 $1,2, \cdots ,d$ 移动到 $d+1,d+2, \cdots ,h \times w$ 的距离，输出答案即为 `dis[r]-dis[l]`。

前缀和数组 $dis_i$ 的意思是从 $i \bmod  d$ 到达 $i$ 的距离，转移式为：

 $dis_i=dis_{i-d}+\left| x_i-x_{i-d}\right|+\left| y_i-y_{i-d}\right|$

### AC代码

```c++
#include<bits/stdc++.h>
using namespace std;
int h,w,d,q;
int x[90010],y[90010];//输入数字的横纵坐标
int dis[90010];//预处理的距离数组
int main()
{
    scanf("%d%d%d",&h,&w,&d);
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {
            int num;
            scanf("%d",&num);
            x[num]=i;
            y[num]=j;//记录坐标
        }
    }
    for(int i=d+1;i<=h*w;i++)
        dis[i]=dis[i-d]+abs(x[i]-x[i-d])+abs(y[i]-y[i-d]);//转移式
    scanf("%d",&q);
    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",dis[r]-dis[l]);
    }
	return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 解题思路：
求出每一个点上的数字所对的坐标，通过枚举每一个点，算出它前一个点到它的曼哈顿距离，再累加起来，运用前缀和思想，每一个输出的答案为        $dp_{r}-dp_{l}$。
# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=9e4+10;
int h,w,q,d;
int nn;
int x[N],y[N];
int dp[N];
signed main(){
	cin>>h>>w>>d;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>nn;
			y[nn]=j;
			x[nn]=i;
		}
	}
	for(int i=d+1;i<=h*w;i++){
		dp[i]=dp[i-d]+abs(x[i]-x[i-d])+abs(y[i]-y[i-d]);
	}
	int l,r;
	cin>>q;
	while(q--){
		cin>>l>>r;
		cout<<dp[r]-dp[l]<<endl;
	}
	return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc089_d)

终于过了，什么时候修一下 rmj 啊。

![](https://cdn.luogu.com.cn/upload/image_hosting/74l9npxt.png)

远古 ABC 压轴题。

读题，发现 $q$ 很大，又发现 $h,w$ 较小，想到进行预处理。

设 $dis_i$ 为从 数 $i\bmod d$ 移动到数 $x$ 的代价，显然有转移：

$$dis_i=dis_{i-d}+dist(i-d,i)$$

其中 $dist(i-d,i)$ 为数 $i-d$ 到数 $i$ 的曼哈顿距离。
求曼哈顿距离函数：
```cpp
int dist(int a,int b){
	return abs(x[a]-x[b])+abs(y[a]-y[b]);//x,y 为横、纵坐标
}
```

对于每次询问，由于 $r-l$ 是 $d$ 的倍数，所以 $r \bmod d=l\bmod d$，所以 $l$ 到 $r$ 的距离可由 $dis_r-dis_l$ 直接得到。

[完整代码](https://atcoder.jp/contests/abc089/submissions/44790030)。预处理时间复杂度 $O(nm)$，询问时间复杂度 $O(q)$。

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc089_d)
# 题目描述
存在 $h\times w$ 的矩阵。其中 $1,2,\dots,h \times w$ 的每一个格子均有一个数 $a_{i}$。

有 $Q$ 次询问，每次询问从数 $l$ 移动到数 $r$ 的代价。而每次移动的代价为两个数在矩阵上的曼哈顿距离。

移动方式为：$l,l+d,l+2\times d,l+3\times d,\dots,r$。其中 $d$ 是常数。

保证 $r-l$ 是 $d$ 的倍数。
# 题目分析
显然本题种的操作有一个特殊的性质：$a$ 到 $c$ 的代价就是 $a$ 到 $b$ 和 $b$ 到 $c$ 的代价之和。

考虑 `dp`，$dp_{i}$ 就是跳到第 $i$ 个格子需要的代价。

转移方程：$dp_{i}=dp_{i-d}+\left|x_{i}-x_{i-d}\right|+\left|y_{i}-y_{i-d}\right|$。

答案即为 $dp_{r}-dp_{l}$。
# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,m,d;
int x[MAXN],y[MAXN];
int dp[MAXN];
void solve(){
	int a,b;
	cin>>a>>b;
	cout<<dp[b]-dp[a]<<'\n';
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>m>>d;
	for(int i=1,a;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a,x[a]=i,y[a]=j;
	for(int i=d+1;i<=n*m;i++)
		dp[i]=dp[i-d]+abs(x[i]-x[i-d])+abs(y[i]-y[i-d]);
	
	int T; 
	cin>>T;
	while(T--)solve();
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [Practical Skill Test](https://www.luogu.com.cn/problem/AT_abc089_d)
## 思路分析
由于询问次数比较大，所以暴力模拟的复杂度为 $O(nmq)$，必定会 TLE。

### 如何处理？

注意到题目中所给的 $d$ 是固定的，先预处理出一个 $\verb|dp|$ 数组，令 $dp_i$ 表示跳到编号为 $i$ 的格子所需要的魔法最小点数。

很容易得出 $\verb|dp|$ 方程：$dp_i=dp_{i-d}+\left|x_i-x_{i-d}\right|+\left|y_i-y_{i-d}\right|$。

状态的转移是从这个格子的前一个格子转移过来。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=9e4+1;
int n,m,q,d,x[N],y[N],ans[N],a,b;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>d;
	for(R i=1; i<=n; i++)
		for(R j=1; j<=m; j++)
			cin>>a,x[a]=i,y[a]=j;
	for(R i=d+1; i<=n*m; i++)
		ans[i]=ans[i-d]+abs(x[i]-x[i-d])+abs(y[i]-y[i-d]);
	cin>>q;
	while(q--)cin>>a>>b,cout<<ans[b]-ans[a]<<'\n';
	return 0;
}

```

---

## 作者：Prolystic (赞：0)

## Part I Preface

[原题目(Luogu)](https://www.luogu.com.cn/problem/AT_abc089_d)

[原题目(AtCoder)](https://atcoder.jp/contests/abc089/tasks/abc089_d)

## Part II Sketch

- 给定一个正整数 $Q$，表示询问次数。
- 给定两个正整数 $H, W$，表示矩阵长和宽。接下来给定一个 $H \times W$ 矩阵。
- 给定一个正整数 $D$。
- 对于每次询问，给定两个正整数 $L,R$。需要求出从 $L$ 挪动到 $R$ 的代价。
- 操作中，每次可以从 $l$ 移动到 $l + D, l + 2D, l + 3D\dots\dots$，每次的花费为两数的曼哈顿距离。
- $1\leq H, W \leq 300$，$1 \leq D \leq H \times W$，$1 \leq Q \leq 10^5$。

## Part III Analysis

为了方便，记曼哈顿距离为 $\operatorname{mht}(a, b)$。

观察题目，我们不难发现每一次移动的代价就是两个数的曼哈顿距离。观察下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/x0g326ad.png)

我们要从 $A$ 走到 $B$，最短的路线就是直接走 $AB$ 这条线段。但是再矩阵里，我们无法走斜线，那该怎么走出最短的路线呢？不难想，先向上走，补齐 $A$ 和 $B$ 纵坐标的差距，再向右走，补齐横坐标的差距，到达 $B$。曼哈顿距离的路线，和理想中的线，正好就是一个长方形的两边和对角线。所以，我们可以把曼哈顿距离看做是以 $AB$ 为对角线的长方形的两边。

（蓝线表示了曼哈顿距离，红线是理想中的最短路）

![](https://cdn.luogu.com.cn/upload/image_hosting/0dosv1fd.png)

小学时，我们就学过阶梯图形的周长问题。将上图中的 $AD,CE$ 向左平移，$DC$ 向上平移，我们就能得到一个和图(1)一样的蓝线。所以，我们又得到了一个理论：即 $\operatorname{mht}(a,b) = \operatorname{mht}(a, c) + \operatorname{mht}(c, b)$，反过来，也有 $mht(a, c) = \operatorname{mht}(a, b) - \operatorname{mht}(b , c)$。

那么问题就好办了，这个问题直接变成了一个具有传递性的递推问题。我们直接预处理出 $1 - H \times W$ 的每一个数的曼哈顿距离，存在数组 $dp$ 里，运用定理(2)，求 $L$ 到 $R$ 的代价时直接用 $\mathit{dp}_R - \mathit{dp}_L$ 即可。

转移方程：$\mathit{dp}_{i, j} = \mathit{dp}_{i - d} + |x_i - x_{i - d}| + |y_i - y_{i - d}|$。

预处理 $O(HW)$，询问是 $O(Q)$ 的，很明显不会超时。

## Part IV Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int MAXN = 90005;
int x[MAXN], y[MAXN];
int dp[MAXN];
int H, W, D, N, Q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> H >> W >> D;
	N = H * W;
	for(int i = 1; i <= H; i++){ 
		for(int j = 1; j <= W; j++){
			int num;
			cin >> num;
			x[num] = i, y[num] = j;
		}
	}
	for(int i = D + 1; i <= N; i++) dp[i] = dp[i - D] + abs(x[i] - x[i - D]) + abs(y[i] - y[i - D]);
	cin >> Q;
	while(Q--){
		int L, R;
		cin >> L >> R;
		cout << dp[R] - dp[L] << '\n';
	}
	return 0;
}
```

## Part V Record

![](https://cdn.luogu.com.cn/upload/image_hosting/keuj2nvu.png)

[Record](https://www.luogu.com.cn/record/110117602)

---

## 作者：Ja50nY0un9_as_AgNO3 (赞：0)

拿到题目后不难想到这样一个思路：我们存下每一个数的横纵坐标，然后每次询问从起点一步一步跳到终点。这样做的复杂度是 $O\left(\dfrac{nmq}{d}\right)$ 的。

然而这样就产生了一个问题：当 $d$ 很小，$n, m, q$ 又很大，而且每次询问中起点都趋近 $1$ 而终点趋近 $9\times10^4$ 的时候，会被卡到 $O(nmq)$ 的复杂度，妥妥超时。

所以，我们需要把询问优化到 $O(1)$ 的复杂度。这需要我们进行预处理。

考虑结合前缀和的思想。对于编号为 $i$ 的点，我们存储从 $i\bmod d$ 走到它的代价 $dis_i$。显然，由于每个点只计算一次，而且可以根据 $dis_{i-d}$ 一步推出，这个预处理是 $O(nm)$ 的。

在询问时，设起点为 $l$，终点为 $r$，则显然答案为 $dis_r-dis_l$。

下附代码。

```cpp
# include <iostream>
using namespace std;
int n, m, d;
int x[90001], y[90001];
int ans[90001];

inline int dis(int a, int b){
    return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}

void init(int a){//初始化模 d 与 a 同余的点
    if (a + d > n * m)
        return;
    ans[a + d] = ans[a] + dis(a, a + d);
    init(a + d);
}

int main(){
    cin >> n >> m;
    cin >> d;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++){
            int k;
            cin >> k;
            x[k] = i, y[k] = j;
        }
    for (int i = 1; i <= d; i++)
        init(i);
    int q;
    cin >> q;
    while (q--){
        int l, r;
        cin >> l >> r;
        cout << ans[r] - ans[l] << endl;
    }
    return 0;
}
```

---

