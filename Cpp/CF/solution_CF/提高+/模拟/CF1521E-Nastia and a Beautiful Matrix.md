# Nastia and a Beautiful Matrix

## 题目描述

You like numbers, don't you? Nastia has a lot of numbers and she wants to share them with you! Isn't it amazing?

Let $ a_i $ be how many numbers $ i $ ( $ 1 \le i \le k $ ) you have.

An $ n \times n $ matrix is called beautiful if it contains all the numbers you have, and for each $ 2 \times 2 $ submatrix of the original matrix is satisfied:

1. The number of occupied cells doesn't exceed $ 3 $ ;
2. The numbers on each diagonal are distinct.

Make a beautiful matrix of minimum size.

## 说明/提示

Note that $ 0 $ in this problem represents a blank, not a number.

Examples of possible answers for the first test case:

 $ \begin{array}{cc} 1 & 1 \\ 4 & 0 \\ \end{array} \hspace{0,5cm} \begin{array}{cc} 1 & 4 \\ 1 & 0 \\ \end{array} \hspace{0,5cm} \begin{array}{cc} 4 & 0 \\ 1 & 1 \\ \end{array} $

Examples of not beautiful matrices for the first test case:

 $ \begin{array}{cc} 1 & 0 \\ 4 & 1 \\ \end{array} \hspace{0,5cm} \begin{array}{cc} 4 & 1 \\ 7 & 1 \\ \end{array} \hspace{0,5cm} \begin{array}{cc} 1 & 0 \\ 4 & 0 \\ \end{array} $

The example of the not beautiful matrix for the second test case:

 $ \begin{array}{cc} 3 & 4 & 0 & 2 & 2 \\ 3 & 2 & 3 & 3 & 0 \\ 0 & 1 & 0 & 0 & 0 \\ 3 & 0 & 0 & 0 & 0 \\ 2 & 1 & 3 & 3 & 3 \\ \end{array} $

Everything is okay, except the left-top submatrix contains $ 4 $ numbers.

## 样例 #1

### 输入

```
2
3 4
2 0 0 1
15 4
2 4 8 1```

### 输出

```
2
4 1
0 1
5
3 0 0 2 2
3 2 3 3 0
0 1 0 4 0
3 0 0 0 0
2 1 3 3 3```

# 题解

## 作者：tzc_wk (赞：5)

> 摘自我的 [贪心/构造/DP 杂题选做Ⅱ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp2.html) 中的第 $44$ 题

首先不难发现对于一个 $n\times n$ 的矩阵，按照如下方式填能够最大化有值的位置个数：
$$
\begin{bmatrix}
*&*&*&*&*&\cdots\\
*&0&*&0&*&\cdots\\
*&*&*&*&*&\cdots\\
*&0&*&0&*&\cdots\\
*&*&*&*&*&\cdots
\end{bmatrix}
$$
其中 $*$ 表示一个非零值。由此我们可以得到，对于一个 $n\times n$ 的矩阵，其中最多可以有 $n^2-\lfloor\dfrac{n}{2}\rfloor^2$ 个非零元素。

但是，$n^2-\lfloor\dfrac{n}{2}\rfloor^2\ge m$ 并不一定是我们能够将 $a_1$ 个 $1$、$a_2$ 个 $2$、$a_3$ 个 $3$、……、$a_k$ 个 $k$ 填入矩阵的**充分条件**，显然，如果 $a_1=n^2-\lfloor\dfrac{n}{2}\rfloor^2$，且 $n\ge 2$，那么我们全填 $1$ 肯定不符合条件 $2$。容易发现，我们最多在这 $n^2-\lfloor\dfrac{n}{2}\rfloor^2$ 个非零位置中，填入 $n·\lceil\dfrac{n}{2}\rceil$ 个同种元素，这个可以通过对矩阵进行黑白染色 + 抽屉原理证明，构造如下：
$$
\begin{bmatrix}
1&1&1&1&1&\cdots\\
*&0&*&0&*&\cdots\\
1&1&1&1&1&\cdots\\
*&0&*&0&*&\cdots\\
1&1&1&1&1&\cdots\\
\end{bmatrix}
$$
因此我们再记 $mx=\max\limits_{i=1}^ka_i$，那么 $n^2-\lfloor\dfrac{n}{2}\rfloor^2\ge m$ 且 $mx\le n·\lceil\dfrac{n}{2}\rceil$ 是否充分了呢？答案是肯定的。我们依次写下 $a_1$ 个 $1$，$a_2$ 个 $2$，……，$a_k$ 个 $k$，这样可以得到一个长度为 $m$ 的序列，不妨称之为 $b_1,b_2,\cdots,b_m$，那么我们按照如下方式填数：

- 在 $(1,2),(1,4),(1,6),\cdots,(3,2),(3,4),(3,6),\cdots,(5,2),(5,4),\cdots$（即所有横坐标为奇数，纵坐标为偶数的格子）中依次填下 $b_1,b_2,\cdots$。
- 填完了横坐标为奇数，纵坐标为偶数的点后，再填横纵坐标均为奇数的点，即 $(1,1),(1,3),(1,5),\cdots,(3,1),(3,3),\cdots$。
- 如果这些点填完了还有剩余的数，那就再依次在 $(2,1),(2,3),(2,5),\cdots,(4,1),(4,3),\cdots$，也就是所有横坐标为偶数，纵坐标为奇数的点中填数。

不难发现，在这样的构造方式下，所有形如 $(2x+2,2y+1),(2x+1,2y+2)$（也就是禁止填上相同的数的点对们）所填上的数在 $b$ 序列中的距离都 $\ge n·\lceil\dfrac{n}{2}\rceil$，而根据假设不存在 $>n·\lceil\dfrac{n}{2}\rceil$ 的 $a_i$，因此这些点对中填上的数必然不同，因此我们的构造是合法的。

```cpp
const int MAXN=500;
const int MAXM=2e5;
int m,k,a[MAXM+5],res[MAXN+5][MAXN+5],ord[MAXM+5];
void solve(){
	scanf("%d%d",&m,&k);int mx=0;
	for(int i=1;i<=k;i++) scanf("%d",&a[i]),chkmax(mx,a[i]);
	int sz;
	for(sz=1;;sz++) if(sz*sz-(sz>>1)*(sz>>1)>=m&&sz*(sz+1>>1)>=mx) break;
	for(int i=1;i<=sz;i++) for(int j=1;j<=sz;j++) res[i][j]=0;
	vector<pii> sp;vector<int> vec;
	for(int i=2;i<=sz;i+=2) for(int j=1;j<=sz;j+=2) sp.pb(mp(i,j));
	for(int i=1;i<=sz;i+=2) for(int j=1;j<=sz;j+=2) sp.pb(mp(i,j));
	for(int i=1;i<=sz;i+=2) for(int j=2;j<=sz;j+=2) sp.pb(mp(i,j));
	for(int i=1;i<=k;i++) ord[i]=i;
	sort(ord+1,ord+k+1,[&](int x,int y){return a[x]>a[y];});
	for(int i=1;i<=k;i++) for(int j=1;j<=a[ord[i]];j++) vec.pb(ord[i]);
	for(int i=0;i<vec.size();i++) res[sp[i].fi][sp[i].se]=vec[i];
	printf("%d\n",sz);
	for(int i=1;i<=sz;i++) for(int j=1;j<=sz;j++) printf("%d%c",res[i][j]," \n"[j==sz]);
}
int main(){
	int qu;scanf("%d",&qu);
	while(qu--) solve();
	return 0;
}
```

---

## 作者：Mihari (赞：2)

# 壹、题目描述 &para;

[传送门 to CF](https://codeforces.com/contest/1521/problem/E).

>中文翻译：
>
>你有 $k$ 个数字，他们分别是 $1,2,3,...,k$，对于数字 $i$ 你有相同的 $a_i$ 个。
>
>定义一个 $n\times n$ 的矩阵为美丽矩阵：
>
>- 这个 $n\times n$ 的矩阵包含了你所拥有的所有数字；
>- 对于每个 $2\times 2$ 的子矩阵，占用的格子不能超过 $3$（当一个格子的数为 $0$ 时，我们认为它没有被占用）并且每个对角线的数字是不同的；
>
>现在，你要构造一个最小的美丽矩阵。

# 贰、题解 &para;

最小的美丽矩阵，即我们得找到一个最小的 $n$，这个 $n$ 显然具有单调性，我们不妨考虑二分。

对于一个二分的 $n$，怎么填这个 $n\times n$ 的矩阵才是最优？

贪心地，我们将奇数列全部填完，把偶数列全部空出来（因为我们可以触及 $\lceil{n\over 2} \rceil$ 而不是 $\lfloor{n\over 2} \rfloor$），这样我们什么限制都不用考虑。

但是每个 $2\times 2$ 的子矩阵我们都没有填满，空了很多，这很亏。

考虑将刚刚的贪心进行拓展——我们把偶数列的奇数行填了，那么我们总共填了多少格子呢？不难计算，这样填，我们总共可以填 $n^2-\lceil{n\over 2} \rceil^2$ 个数字，也就是说，只有 $\sum a_i\le n^2-\lfloor{n\over 2} \rfloor^2$ 时我们才可以装下所有数字。

但是这不一定合法——奇数列的偶数行和偶数列的奇数行不能填同样的数字，所以我们还要考虑出现次数最多的数字 $x=\{i|a_i=\max\{a\}\}$，对于这个数字，我们只能将它填在不会冲突的位置 —— 所有奇数列，这些奇数列一共有 $n\times \lceil{n\over 2} \rceil$ 个格子，所以，对于二分的 $n$，我们有两个限制：

- $\sum a_i\le n^2-\lfloor{n\over 2} \rfloor^2$；
- $x=\{i|a_i=\max\{a\}\},a_x\le n\times \lceil{n\over 2} \rceil$；

二分得到 $n$，然后我们考虑构造方案，考虑这样的一个网格：~~宅了题解的图~~

<center>
    <img src="https://cdn.luogu.com.cn/upload/image_hosting/walrc0jr.png">
</center>

其实这就是上面的 “偶数列的奇数行” 之类的东西，对于蓝色的格子，可以随便乱填的，但是对于红色和黄色，它可能有冲突。同时，同一颜色不会冲突。

我们将所有的 $a_i$ 从大到小排序，先贪心地，将大的数字尽量往红色填，如果红色填不下，就往蓝色填 —— 可以证明这是一定可行的，因为 红色+蓝色 就有 $n\times \lceil{n\over 2} \rceil$ 个，这甚至可以满足最大的 $a_i$.

当红色都被填完时，有几种情况：

- 最大的颜色还没有被填完，那么它会被蓝色消耗掉；
- 最大的颜色已经被填完了，甚至还填了一些其他的颜色；

对于第一种情况，剩下的蓝色格子一定不会和红色冲突，而黄色格子我们可以保证和红色格子填的最大数字不一样 —— 因为 红+蓝 的组合拳已经把最大数字消耗掉，无论如何都不会冲突；

对于第二种情况，可以保证填在红色的比最大数稍微小一点的数字和后面填进黄色的数字不一样 —— 如果蓝色都不能将小的数字吸纳掉，那么它将会变成出现次数最多的数字。

所以，无论如何，这样填都不会冲突。

照着这个思路填格子就好了。

时间复杂度 $\mathcal O(n\log n)$，在于排序~~用基排也不是不可以~~.

# 叁、参考代码 &para;

```cpp
const int maxk=1e5;

pll a[maxk+5]; int m, k;

inline void input(){
	m=readin(1), k=readin(1);
	rep(i, 1, k) a[i]=mp(readin(1), i);
}

inline ll bisearch(){
	ll sum=0, maxx=0;
	rep(i, 1, k) sum+=a[i].fi, maxx=max(maxx, a[i].fi);
	ll l=0, r=1000, mid, ans=-1;
	while(l<=r){
		mid=(l+r)>>1;
		if(sum<=mid*mid-(mid>>1)*(mid>>1) && maxx<=mid*((mid+1)>>1))
			ans=mid, r=mid-1;
		else l=mid+1;
	}
	return ans;
}

int mat[1005][1005];

vector<pii>red, blue, yellow;

signed main(){
	rep(tmp, 1, readin(1)){
		input();
		int n=bisearch();
		sort(a+1, a+k+1);
		red.clear(); blue.clear(); yellow.clear();
		rep(i, 1, n) rep(j, 1, n) mat[i][j]=0;
		for(int i=1; i<=n; i+=2)
			for(int j=2; j<=n; j+=2)
				red.push_back(mp(i, j));
		for(int i=1; i<=n; i+=2)
			for(int j=1; j<=n; j+=2)
				blue.push_back(mp(i, j));
		for(int i=2; i<=n; i+=2)
			for(int j=1; j<=n; j+=2)
				yellow.push_back(mp(i, j));
		for(int i=k; i>=1; --i) while(a[i].fi){
			--a[i].fi;
			if(!red.empty()) mat[red.back().fi][red.back().se]=a[i].se, red.pop_back();
			else if(!blue.empty()) mat[blue.back().fi][blue.back().se]=a[i].se, blue.pop_back();
			else mat[yellow.back().fi][yellow.back().se]=a[i].se, yellow.pop_back();
		}
		printf("%d\n", n);
		rep(i, 1, n){
			rep(j, 1, n) printf("%d ", mat[i][j]);
			Endl;
		}
	}
	return 0;
}
```



---

## 作者：ReTF (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1521E)

讲一个和题解区做法不一样的构造。

可以发现在横坐标和纵坐标均为偶数的格子里放 $0$ 可以满足第二个限制，并且 $0$ 的个数最少。

我们把格子分成三类，分别记作：

- $a$ 格子：横坐标为偶数，纵坐标为奇数的格子，数量记为 $A$；
- $b$ 格子：横坐标为奇数，纵坐标为偶数的格子，数量记为 $B$；
- $c$ 格子：横坐标为奇数，纵坐标为奇数的格子，数量记为 $C$。

可以发现如果选择同种颜色的话，每个 $a$ 类型和 $b$ 类型的格子会和斜对角至多四个另一类型的格子产生冲突。要规避这种局面，就要尽量减少同时放在 $a$ 格子和 $b$ 格子的颜色数。可以想到将 $c$ 格子作为“备用”：如果一种颜色放不下的话就放到 $c$ 格子中。

我们二分一个答案矩阵大小，将最优化问题转化为可行性问题。将颜色按照出现次数从大到小排序。**每次选择 $\bf a$ 和 $\bf b$ 中剩余格子数最大的格子类型，然后将当前颜色全部填进去，如果不够的话就填进 $\bf c$ 格子**。最后得到的矩阵就是答案。

这样做为什么是对的？首先 $C\ge \max\{A,B\}$。考虑出现次数最多的元素。如果该元素一开始就无法填入，那么一定不存在方案。否则的话剩下的元素出现的次数都 $\le \lfloor \dfrac{n}{2} \rfloor$，即使两种元素全部填入 $c$ 格子中也不会把 $c$ 格子占满。

[代码](https://codeforces.com/contest/1521/submission/236050110)

---

## 作者：清尘 (赞：1)

[My blog](https://www.cnblogs.com/whx666/p/CF1521E.html)

**其实这题并不需要排序，下面会给出证明**

答案满足单调性，可以通过二分找出边长 $len$。如下图所示将网格染成四种颜色：![](https://img2020.cnblogs.com/blog/1604447/202105/1604447-20210512202652123-155545459.png)

（图片的markdown好像挂了？就是[官方题解](https://codeforc.es/blog/entry/90477)里的图，也可以在[这里](https://img2020.cnblogs.com/blog/1604447/202105/1604447-20210512202652123-155545459.png)看）

饱和的情况就是把所有非白色的格子都填上数，共 $S=len^2-\lfloor \frac{len}{2} \rfloor^2$ 个，那么二分第一个条件是 $S\ge\sum a_i$

然后考虑众数 $x$，为了满足对角线不重复，它最多只能放在蓝色和红(或黄)色的格子里，共 $T=len\times \lceil \frac{len}{2} \rceil$ 个，需满足 $T\ge a[x]$

对于满足以上两个条件的 $len$，一定可以构造出一个解，方法如下：

把所有数排成一列，相同的数排在一起，$x$ 排在最前面，**其他数顺序随意**，然后先往红格子放，红的放完了放蓝的，最后放黄的。

简单的证明一下所有 $2\times 2$ 对角线不重复：所有对角线都由一个黄的一个红的组成，进行分类，

1、如果 $x$ 填满了红格子，并且根据二分条件 $x$ 最多填满蓝的，不会填到黄的，所以黄和红不重复

2、如果 $x$ 没填满红格子，若出现重复，则存在一个 $y$，在红格子里填了，又填满了蓝的，还得填黄的。而格子数量 蓝 $\ge$ 红，$x$ 又是众数，显然不可能

所以其他数的填放顺序根本无所谓，不需要排序。 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
void read (int &x) {
    char ch = getchar(); x = 0; while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
} const int N = 2e5 + 5, M = 2000, NN = N * 5;
int n, s, mx, a[N], res[M][M], sr, sb, sy, id[N];
pair<int, int> r[NN], b[NN], y[NN];
#define xx first
#define yy second
int get () {
    int l = 0, r = 1000, mid, res = 0;
    while (l <= r) {
        mid = l + r >> 1;
        if (s <= mid * mid - (mid / 2) * (mid / 2) && a[1] <= mid * ((mid + 1) / 2))
            res = mid, r = mid - 1;
        else l = mid + 1;
    }
    return res;
}
signed main() {
    int T; read (T);
    while (T--) {
        read (s), read (n); mx = 0;
        for (int i = 1; i <= n; ++i) {
            read (a[i]), id[i] = i;
            if (a[i] > a[mx]) mx = i;
        }
        id[1] = mx, id[mx] = 1; swap (a[1], a[mx]);
        int len = get (); sr = sb = sy = 0;
        for (int i = 2; i <= len; i += 2)
            for (int j = 1; j <= len; j += 2) r[++sr] = {i, j};
        for (int i = 1; i <= len; i += 2)
            for (int j = 1; j <= len; j += 2) b[++sb] = {i, j};
        for (int i = 1; i <= len; i += 2)
            for (int j = 2; j <= len; j += 2) y[++sy] = {i, j};
        for (int i = 1; i <= len; ++i)
            for (int j = 1; j <= len; ++j) res[i][j] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= a[i]; ++j) {
                if (sr) res[r[sr].xx][r[sr].yy] = id[i], --sr;
                else if (sb) res[b[sb].xx][b[sb].yy] = id[i], --sb;
                else res[y[sy].xx][y[sy].yy] = id[i], --sy;
            }
        }
        printf ("%d\n", len);
        for (int i = 1; i <= len; ++i) {
            for (int j = 1; j <= len; ++j) printf ("%d ", res[i][j]); puts ("");
        }
    }
    return 0;
}
```



---

## 作者：7KByte (赞：1)

奇怪的构造题增加了。

要求最小的矩阵，直接二分答案转化为判定。

然后考虑怎样填一个矩形最优。

手算一下不难发现，只填奇数列是个很优的方式，并且不用考虑对角线不同的情况。

扩展一下，我们还可以在偶数列的奇数行填数，这样我们最多可以填 $n^2-\left\lfloor\dfrac{n}{2}\right\rfloor^2$ 个数。

并且通过反证法我们不难证明任意一种方案不可能填比这更多的数。

但是不代表一定可以这么填，比如所有数相同，那么偶数列的就不能填。

所以还有一个有解限制条件，就是出现次数最多的数不超过奇数列之和，即 $n\left\lceil\dfrac{n}{2}\right\rceil$ 。

简单运用图论知识我们也能证明如果超过这个数，一定存在两个格子公共顶点。

最后考虑构造。

如果只填奇数列，则可以随意填，这启发了我们。

我们将奇数列奇数行的格子称为 $a$，奇数列的偶数行格子称为 $b$ ，偶数列的奇数行格子称为 $c$ ，剩下的留空。非空的格子一共 $n^2-\left\lfloor\dfrac{n}{2}\right\rfloor^2$ 个。

并且还有 $sz_a\ge sz_b = sz_c$ ， $sz_a+sz_b=n\left\lceil\dfrac{n}{2}\right\rceil$ 。

其中 $a$ 的对角线是空格子，可以任意填。

我们将所有数按出现次数从大到小排序，优先填入 $b$ 格子，那么最后一定是一种颜色将 $b$ 格子收尾并剩下几个，我们将剩下这几个填入 $a$ 格子。

固定了 $b$ 格子后，其余颜色又与 $b$ 格子中任意一个互不相同，所以剩下没有填的颜色随便找空格子填即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 1005
#define M 200005
using namespace std;
typedef pair<int,int> Pr;
int m,k,a[M],T,c[N][N];Pr u[M];
vector<Pr>p,q,w;
void calc(int n){
	p.clear();q.clear();w.clear();
	rep(i,0,n+1)rep(j,0,n+1)c[i][j]=0;
	rep(i,1,n)rep(j,1,n){
		if(i&1){
			if(j&1)w.push_back(make_pair(i,j));
			else p.push_back(make_pair(i,j));
		}
		else if(j&1)q.push_back(make_pair(i,j));
	}
	pre(i,T,1){
		rep(j,1,u[i].first){
			if(p.size()){
				Pr now=p[p.size()-1];
				p.pop_back();
				c[now.first][now.second]=u[i].second; 
			}
			else {
				if(q.size()){
					Pr now=q[q.size()-1];
					int x=now.first,y=now.second,col=u[i].second;
					if(c[x-1][y-1]!=col&&c[x-1][y+1]!=col&&c[x+1][y-1]!=col&&c[x+1][y+1]!=col){
						c[x][y]=col;q.pop_back();
					}
					else{
						now=w[w.size()-1];
						c[now.first][now.second]=col;w.pop_back();
					}
				}
				else{
					Pr now=w[w.size()-1];
						c[now.first][now.second]=u[i].second;w.pop_back();
				}
			}
		}
	}
	rep(i,1,n){rep(j,1,n)printf("%d ",c[i][j]);putchar('\n');}
}
void solve(){
	scanf("%d%d",&m,&k);T=0;
	rep(i,1,k){
		scanf("%d",&a[i]);
		if(a[i])u[++T]=make_pair(a[i],i);
	}
	sort(u+1,u+T+1);
	int l=1,r=1000,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(mid*((mid+1)/2)>=u[T].first&&(mid*mid)-(mid/2)*(mid/2)>=m)ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);calc(ans);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：STrAduts (赞：0)

要把所有数容纳下就一定至少有，$\sum \limits _{i = 1 \to k} a_i < n^2$。但这个限制太弱了可恶。

考虑一种构造，一排全放数字，一排隔一个放一个。感觉可以做到最优。

接下来考虑普适化的细节，即需要满足对角线数组不同。

全放数字的就直接往上怼，不够换下一个数字，顺序填即可。

全放数字的不妨均为奇数行，则隔一个放一个的为偶数行，在所有奇数行确定后再填。从下往上，只有能填就填。

事实证明，一行填满，一行隔一个填一个的思路是对的。

但并不是按顺序能填就填，因为在这样的逻辑中，只能填下 $n \times \lceil \frac {n} {2} \rceil$ 个同种类的数，不然就会破坏规则二。

（可使用抽屉原理证明。

而 $n^2 - \lfloor \frac {n} {2} \rfloor^2$ 是这样填最多可以有多少个非零的数填入。

故可以得出 $n^2 - \lfloor \frac {n} {2} \rfloor^2 \geq m$，$n \times \lceil \frac {n} {2} \rceil \geq \max \limits _{i = 1 \to n} a_i$。但这充分吗？

Two thousand years later...

充分。

我们考虑按以下方式构造，按从数字个数从大到小的顺序依次将对应数字填入这些格子：

- 第一类：横坐标为奇数，纵坐标为偶数。
- 第二类：横坐标为奇数，纵坐标为奇数。
- 第三类：横坐标为偶数，纵坐标为奇数。

（允许最后一类不填。

那么会破坏第二个限制的就是第一类格子的数和相邻的第三类格子的数相同。

而第一类格子填入的最后一个数是第 $\lceil \frac {n} {2} \rceil \times \lceil \frac {n} {2} \rceil$ 个填入的，第三类格子填入的第一个数是第 $n \times \lceil \frac {n} {2} \rceil + 1$ 个填入的。

若假设会相同，那么第一类格子应全是这个相同的数 $x$。

因为如果不是 $x$，则有另一个数 $y$ （$y$ 应比 $x$ 后填入）跨越了第一类和第三类，$y$ 的个数至少为 $n \times \lceil \frac {n} {2} \rceil - \lceil \frac {n} {2} \rceil \times \lceil \frac {n} {2} \rceil + 2$ ，而 $x$ 的数个数至多为 $\lceil \frac {n} {2} \rceil \times \lceil \frac {n} {2} \rceil - 1$。

因为 $n \times \lceil \frac {n} {2} \rceil - \lceil \frac {n} {2} \rceil \times \lceil \frac {n} {2} \rceil + 2 = \lceil \frac {n} {2} \rceil \times \lfloor \frac {n} {2} \rfloor + 2$ 且 $\lceil \frac {n} {2} \rceil \times \lfloor \frac {n} {2} \rfloor + 2 - (\lceil \frac {n} {2} \rceil \times \lceil \frac {n} {2} \rceil - 1) = \lceil \frac {n} {2} \rceil \times (1 / 0) + 3 > 0$，所以 $n \times \lceil \frac {n} {2} \rceil - \lceil \frac {n} {2} \rceil \times \lceil \frac {n} {2} \rceil + 2 > \lceil \frac {n} {2} \rceil \times \lceil \frac {n} {2} \rceil - 1$ 。而这与按照数字个数从大到小的顺序矛盾。

故第一类应全是 $x$，因为是按顺序且第三类的第一个也是 $x$，那么说明这个数的个数至少为 $n \times \lceil \frac {n} {2} \rceil + 1$，这与 $n \times \lceil \frac {n} {2} \rceil \geq \max \limits _{i = 1 \to n} a_i$ 矛盾。

故第一类格子的数和相邻的第三类格子的数不可能相同。

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

int Abs (int x) { return x < 0 ? -x : x; }
int Max (int x, int y) { return x > y ? x : y; }
int Min (int x, int y) { return x < y ? x : y; }

int Read () {
    int x = 0, k = 1;
    char s = getchar ();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar ();
    }
    while ('0' <= s && s <= '9') 
        x = (x << 3) + (x << 1) + (s ^ 48), s = getchar ();
    return x * k;
}

void Write (int x) {
    if (x < 0)
        putchar ('-'), x = -x;
    if (x > 9)
        Write (x / 10);
    putchar (x % 10 + '0');
}

void Print (int x, char s) { Write (x), putchar (s); }

const int Maxn = 1e5 + 5;
const int Maxm = 5e2 + 5;

int a[Maxn], Num[Maxn], Res[Maxm][Maxm];

bool Cmp (int x, int y) { return a[x] > a[y]; }

/*
1
25 3
12 10 3
*/

int main () {
    int t = Read ();
    while (t--) {
        int m = Read (), k = Read (), Ma = -1;
        for (int i = 1; i <= k; i++)
            a[i] = Read (), Ma = Max (Ma, a[i]), Num[i] = i;
        int n;
        for (n = 1; n; n++)
            if (n * n - (n / 2) * (n / 2) >= m && n * ((n + 1) / 2) >= Ma)
                break;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                Res[i][j] = 0;
        int p = 1, Limit = 1;
        for (int i = 1; i <= k; i++)
            if (a[Num[i]] != 0)
                Limit = i;
        bool Flag = false;
        for (int i = 1; i <= n; i += 2)
            for (int j = 2; j <= n; j += 2) {
                while (!a[Num[p]] && p <= Limit) 
                    p++;
                if (p == Limit + 1) {
                    Flag = true;
                    break;
                }
                Res[i][j] = Num[p], a[Num[p]]--;
            }      
        if (Flag || (!a[Num[Limit]] && p == Limit)) {
            Print (n, '\n');
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    Print (Res[i][j], j == n ? '\n' : ' ');
            continue;
        }
        for (int i = 1; i <= n; i += 2)
            for (int j = 1; j <= n; j += 2) {
                while (!a[Num[p]] && p <= Limit) 
                    p++;
                if (p == Limit + 1) {
                    Flag = true;
                    break;
                }
                Res[i][j] = Num[p], a[Num[p]]--;
            }
        if (Flag || (!a[Num[Limit]] && p == Limit)) {
            Print (n, '\n');
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    Print (Res[i][j], j == n ? '\n' : ' ');
            continue;
        }
        for (int i = 2; i <= n; i += 2)
            for (int j = 1; j <= n; j += 2) {
                while (!a[Num[p]] && p <= Limit) 
                    p++;
                if (p == Limit + 1) {
                    Flag = true;
                    break;
                }
                Res[i][j] = Num[p], a[Num[p]]--;
            }
        if (Flag || (!a[Num[Limit]] && p == Limit)) {
            Print (n, '\n');
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    Print (Res[i][j], j == n ? '\n' : ' ');
            continue;
        }
    }
    return 0;
}
```

---

## 作者：Rainy7 (赞：0)

- **前言**

  一道构造题。
  
  ~~关于我被卡常了这件事（（~~

------------


- **分析**

  首先，考虑每个 $2\times2$ 矩阵都必须有一个 $0$ ，不妨先计算出最少需要几个 $0$ 。

  显然，对于每个 $(i+j) \equiv 0 \pmod{2}$ 且 $i$ 和 $j$ 都为偶数时候，把 $(i,j)$ 赋值为 $0$ ，此时的 $0$ 数量最少。

  所以最少需要的 $0$ 的个数是 $\left\lfloor \dfrac{p}{2} \right\rfloor ^2$ 。

  所以在算 $p$ 的时候，最小的 $p$ 一定要满足 $m>p^2-\left\lfloor \dfrac{p}{2} \right\rfloor ^2$ 。

  接着我们对 $0$ 的上下左右染色，上下为 $1$ ，左右为 $2$ 。

  ![](https://i.loli.net/2021/10/13/nmNMLhavOU64HKF.png)

  因为 $0$ 此时已经满足题目要求了。所以我们考虑对角线要求。

  此时只要考虑每组的 $1$ 和 $2$ 不同就好了。

  但是，有可能此时染色无法满足要求。如果出现一个颜色的数量大于白色和 $0$ （或 $1$ ）的总数，就无法满足要求。

  但这种颜色最多存在 $1$ 个，所以开头计算 $p$ 的时候再多判断一下就好了。

  如果保证一定有解，那就直接染色就好了。把 $cnt_i$ 从小到大排序，$0$ 从数量最小的颜色开始赋值，$1$ 从最大的开始赋值。注意这里的赋值包括 $0$ ，也优先考虑 $0$ 。可以证明这样一定满足题目要求。


- **代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=1e5+5,M=3000+5;
struct node{
	int id,x;
}cnt[N];
int T,n,m,p,a[M][M],ans[M][M];
bool cmp(node u,node v)
{	if(u.x!=v.x)return u.x<v.x;
	else return u.id<v.id;
}
void solve()
{	
	cnt[0].x=p*p-m;cnt[0].id=0;
	for(int i=1;i<=p;i++)
		for(int j=1;j<=p;j++)
			a[i][j]=-1;
	for(int i=1;i<=p;i++)
		for(int j=1;j<=p;j++)
		{	
			if((i&1)==0&&(j&1)==0&&((i+j)&1)==0)
			{	
				a[i][j]=ans[i][j]=0;
				cnt[0].x--;
				a[i-1][j]=a[i+1][j]=1;
				a[i][j-1]=a[i][j+1]=2;
			}
		}
	int x=0,y=n;
	while(x<=n&&cnt[x].x==0)x++;
	while(y>=0&&cnt[y].x==0)y--;
	for(int i=1;i<=p;i++)
		for(int j=1;j<=p;j++)
		{	
			if(a[i][j]==0)continue;
			else if(a[i][j]==1)
			{	
				ans[i][j]=cnt[x].id;
				cnt[x].x--;
				while(x<=n&&cnt[x].x==0)x++;
			}
			else if(a[i][j]==2)
			{	
				ans[i][j]=cnt[y].id;
				cnt[y].x--;
				while(y>=0&&cnt[y].x==0)y--;
			}
		}
	for(int i=1;i<=p;i++)
		for(int j=1;j<=p;j++)
		{	
			if(a[i][j]!=-1)continue;
			ans[i][j]=cnt[x].id;
			cnt[x].x--;
			while(x<=n&&cnt[x].x==0)x++;
		}
}
int main()
{	
	scanf("%d",&T);
	while(T--)
	{	
		scanf("%d%d",&m,&n);
		for(int i=1;i<=n;i++)
		{	
			scanf("%d",&cnt[i].x);
			cnt[i].id=i;
		}
		sort(cnt+1,cnt+1+n,cmp);
		if(m==1)
		{	
			printf("1\n%d\n",cnt[n]);
			continue;
		}
		p=2;
		while(p*p-(p/2)*(p/2)<m)p++;
		while(cnt[n].x>p*p-(p/2)*(p/2)-(p/2)*((p+1)/2))p++;
		solve();
		printf("%d\n",p);
		for(int i=1;i<=p;i++)
		{	
			for(int j=1;j<=p;j++)
				printf("%d ",ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}
```

------------

$$\text{by Rainy7}$$

---

