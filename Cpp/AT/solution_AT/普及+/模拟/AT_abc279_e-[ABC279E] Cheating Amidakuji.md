# [ABC279E] Cheating Amidakuji

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc279/tasks/abc279_e

<!-- 
$ N $ 本の縦棒と、それらの間を結ぶ $ M $ 本の横棒からなるあみだくじがあります。
各横棒は縦棒と垂直に引かれていて、その高さは相異なります。
縦棒を左から順に $ 1,2,\dots,N $、横棒を上から順に $ 1,2,\dots,M $ としたとき、
横棒 $ i\ (1\ \leq\ i\ \leq\ M) $ は縦棒 $ A_i $ と縦棒 $ A_i+1 $ の間を結んでいます。

縦棒 $ 1 $ の上端からあみだくじを下に辿っていったとき、最終的に到達する縦棒の番号を**スコア**と定義します。

$ i=1,2,\dots,M $ について、以下の質問に答えてください。

- 横棒 $ i $ を消したときのスコアを $ S_i $ と定義する。$ S_i $ を求めよ。

なお、実際には横棒は消さないため、各質問は独立であることに注意してください。

より厳密には、以下の通りです。
-->$ 1 $ 以上 $ N-1 $ 以下の整数からなる長さ $ M $ の数列 $ A=(A_1,A_2,\dots,A_M) $ が与えられます。 $ i=1,2,\dots,M $ について、以下の質問に答えてください。

- 数列 $ B=(B_1,B_2,\dots,B_N) $ がある。最初、各 $ j $ について $ B_j=j $ である。今から、$ k=1,2,\dots,i-1,i+1,\dots,M $ の順に以下の操作を行う （すなわち、$ i $ を除いた $ 1 $ 以上 $ M $ 以下の整数 $ k $ について、昇順に以下の操作を行う）。
  - $ B_{A_k} $ と $ B_{A_k+1} $ の値を入れ替える。
- 全ての操作が終了した段階で、$ B_j=1 $ を満たす $ j $ の値を $ S_i $ と定義する。$ S_i $ を求めよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N-1\ (1\leq\ i\ \leq\ M) $
- 入力は全て整数
 
### Sample Explanation 1

$ i\ =\ 2 $ のとき、操作によって $ B $ は以下のように変化します。 - 最初、$ B\ =\ (1,2,3,4,5) $ - $ k=1 $ として操作を行う。すなわち $ B_1 $ と $ B_2 $ の値を入れ替えて、$ B\ =\ (2,1,3,4,5) $ - $ k=3 $ として操作を行う。すなわち $ B_3 $ と $ B_4 $ の値を入れ替えて、$ B\ =\ (2,1,4,3,5) $ - $ k=4 $ として操作を行う。すなわち $ B_2 $ と $ B_3 $ の値を入れ替えて、$ B\ =\ (2,4,1,3,5) $ 全ての操作が終了した段階で $ B_3=1 $ であるため、$ S_2\ =\ 3 $ です。 同様に、 - $ i=1 $ のとき：$ k=2,3,4 $ の順に操作を行うと $ B=(1,4,3,2,5) $ になるので、$ S_1=1 $ - $ i=3 $ のとき：$ k=1,2,4 $ の順に操作を行うと $ B=(2,1,3,4,5) $ になるので、$ S_3=2 $ - $ i=4 $ のとき：$ k=1,2,3 $ の順に操作を行うと $ B=(2,3,4,1,5) $ になるので、$ S_4=4 $ です。

## 样例 #1

### 输入

```
5 4
1 2 3 2```

### 输出

```
1
3
2
4```

## 样例 #2

### 输入

```
3 3
2 2 2```

### 输出

```
1
1
1```

## 样例 #3

### 输入

```
10 10
1 1 1 9 4 4 2 1 3 3```

### 输出

```
2
2
2
3
3
3
1
3
4
4```

# 题解

## 作者：FFTotoro (赞：12)

很妙的一道题，完美利用了交换操作的一些性质。

首先，不考虑忽略的操作——即假设全部操作都正常进行；对于每次操作，用 $X_i$ 记录第 $i$ 次操作的第一个数，$Y_i$ 记录第 $i$ 次操作的第二个数。

接着，利用 $C_i$ 记录 $B_i$ 最终的位置；

最后，我们来考虑忽略掉的操作——对于忽略第 $i$ 个操作，如果本次操作对 $1$ 有影响，那么 $1$ 最终的位置其实就是不忽略操作时和它交换的数最终的位置（判断操作对 $1$ 有没有影响，即为判断是否 $X_i=1$ 或 $Y_i=1$）。这样，直接调用 $C$ 数组存下的答案即可求解。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[200001],y[200001],b[200001],c[200001];
int main(){
  int n,m; cin>>n>>m;
  vector<int> a(m);
  iota(b+1,b+n+1,1);
  for(int i=0;i<m;i++){
    cin>>a[i]; x[i]=b[a[i]],y[i]=b[a[i]+1];
    swap(b[a[i]],b[a[i]+1]);
  } // 模拟正常操作
  for(int i=1;i<=n;i++)c[b[i]]=i; // 记录 c 数组
  for(int i=0;i<m;i++){
    if(x[i]==1)cout<<c[y[i]]<<endl; // 1 是第一个操作数
    else if(y[i]==1)cout<<c[x[i]]<<endl; // 1 是第二个操作数
    else cout<<c[1]<<endl;
  }
  return 0;
}
```

---

## 作者：Daidly (赞：4)

给定长度为 $m$ 的数组 $a$，其中值的范围是 $1\sim n-1$，求出对于 $i=1\sim m$ 经过下列操作后的答案。

- 初始一个 $1\sim n$ 的排列 $b$ 满足 $b_i=i$；

- 对于 $j\in[1,m],j\ne i$，从小到大依次交换 $b_{a_j}$ 和 $b_{a_j+1}$；

- 定义操作完后排列的答案为 $ans$ 满足 $b_{ans}=1$。

$n,m\leq 2\times 10^5$

---

由于只需要求排列种值为 $1$ 的下标，我们重点关注 $1$。

考虑第 $i$ 次操作不做的影响，记 $now$ 为前 $i-1$ 次操作做完后 $1$ 的位置。

- 若 $now=a_i$，操作后会使 $now\gets a_i+1$，不操作则会让 $now$ 停留在 $a_i$​ 处。而之后会按此时的 $b_{a_i}$ 的轨迹走下去；

- 若 $now=a_i+1$，操作后会使 $now\gets a_i$，不操作则会让 $now$ 停留在 $a_i+1$ 处。而之后会按此时的 $b_{a_i+1}$ 的轨迹走下去；

- 其他情况操作均不会对 $1$ 的最终位置造成影响。

由于对于每个 $i$ 只会减少一次操作，不妨先求出经过每一次操作后的序列，记 $pos[i]$ 表示值为 $i$ 的数最后的位置。

- 若 $1$ 的轨迹在删除第 $i$ 次操作后不变，答案即为 $pos[1]$；

- 若 $1$ 的轨迹在删除第 $i$ 次操作后改变，那么就相当于它在第 $i-1$ 次操作后轨迹替换成了和它进行第 $i$ 次操作的对象。换一种方式理解，就是在第 $i$ 次操作后加上一次和第 $i$ 次操作相同的抵消操作，这个抵消操作会使原本 $1$ 的轨迹变成 $b_{a_i+1}(now=a_i)$ 或 $b_{a_i}(now=a_i+1)$。

所以我们只需要记录每一个数最后的位置，再模拟一次操作过程，对于每一个 $i$ 的询问输出改变后 $1$ 的轨迹即可。

代码见 [Submission #36871525](https://atcoder.jp/contests/abc279/submissions/36871525)。

---

## 作者：rui_er (赞：3)

曾经总结过[一类分治套路](https://www.cnblogs.com/ruierqwq/p/a-kind-of-divide-and-conquer.html)，没想到竟然派上用场了。

这种每个操作依次缺席的问题可以通过分治来解决。设 `solve(l, r)` 表示缺席的操作在 $[l,r]$ 之间时求出它们的答案。

设 $mid=\lfloor\frac{l+r}{2}\rfloor$，考虑将区间 $[l,r]$ 划分为两个区间 $[l,mid],[mid+1,r]$。对于区间 $[l,mid]$，可以知道区间 $[mid+1,r]$ 的操作一定是执行了的。因此，在递归求解 $[l,mid]$ 的时候，我们遍历 $[mid+1,r]$ 的每一个操作，统计它对答案的影响。反之亦然。

本题中要注意操作执行的顺序问题。

由主定理易证复杂度为 $T(m)=2T(\frac{m}{2})+\Theta(m)=\Theta(m\log m)$。

```cpp
// Problem: E - Cheating Amidakuji
// Contest: AtCoder - TOYOTA SYSTEMS Programming Contest 2022(AtCoder Beginner Contest 279)
// URL: https://atcoder.jp/contests/abc279/tasks/abc279_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n, m, a[N], p[N], pos[N], ans[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
void swp(int i) {
	int x = p[i], y = p[i+1];
	swap(p[i], p[i+1]);
	swap(pos[x], pos[y]);
}
void calc(int& i) {i = pos[i];}
void solve(int L, int R, int now) {
	if(L == R) {
		ans[L] = now;
		return;
	}
	int M = (L + R) >> 1;
	{
		solve(L, M, now);
		rep(i, M+1, R) swp(a[i]);
		rep(i, L, M) calc(ans[i]);
		per(i, R, M+1) swp(a[i]);
	}
	{
		rep(i, L, M) swp(a[i]);
		calc(now);
		per(i, M, L) swp(a[i]);
		solve(M+1, R, now);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m) scanf("%d", &a[i]);
	rep(i, 1, n) p[i] = pos[i] = i;
	solve(1, m, 1);
	rep(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：2)

### upd on 2024/07/22：这就是 CDQ 分治。。。

## 简要题意：

给你两个数组 $A$ 和 $B$，初始时，$B_i=i$。

定义第 $k$ 次操作为 $\operatorname{swap}(B_{A_k},B_{A_k+1})$。

定义 $S_i$ 为依次进行 $1$ 到 $m$ 除 $i$ 号操作外的所有操作后，数字 $1$ 在 $B$ 数组中的位置。

请依次输出 $S_i$ 。
 
## 套路分析：

这种每个物品/操作依次缺席的问题，一般都可以用分治来解决。

具体的讲：

定义函数 $\text{solve}(L,R)$ 表示在考虑 $1$ 至 $L-1$ 的影响下，$L$ 至 $R$ 区间的答案。

我们令 $mid=\dfrac{(L+R)}{2}$。

- 计算 $L$ 至 $mid$ 的答案。
- 将 $mid+1$ 至 $R$ 的影响并入 $L$ 到 $mid$ 的答案中。
- 全局加入 $L$ 至 $mid$ 的影响。
- 计算 $mid+1$ 至 $R$ 的答案。

如果两次合并的总时间复杂度在 $\Theta(n)$ 的量级，易证该算法的总时间复杂度是 $\Theta (n\log n)$ 的。

## 本题要点：

我们拉个辅助数组 $pos$，表示数组 $b$ 值为 $i$ 的数的位置。

因为每次我们都在回溯之前将 $pos$ 和 $b$ 数组复原了，所以**设原来 $x$ 的位置在 $i$，交换前 $i$ 处已被重置为 $i$，交换后的 $pos_i$ 即为交换后 $x$ 的位置。**

## 代码

```cpp
//By: Luogu@tzl_Dedicatus545(LuoguID:308854)
#define rep(i,x,y,z) for(int i=(x);i<=(y);i+=(z))
#define per(i,x,y,z) for(int i=(x);i>=(y);i-=(z))

void swp(int i){
	int x=b[i],y=b[i+1];
	swap(b[i],b[i+1]);
	swap(pos[x],pos[y]);
}

void solve(int l,int r,int now1){
	if(l==r){
		ans[l]=now1;
		return ;
	}
	int mid=(l+r)/2;
    
	{
		solve(l,mid,now1);
		rep(i,mid+1,r,1)
			swp(a[i]);
		rep(i,l,mid,1)
			ans[i]=pos[ans[i]];
		per(i,r,mid+1,1)
			swp(a[i]);
	}
	{
		rep(i,l,mid,1)
			swp(a[i]);
		now1=pos[now1];
		per(i,mid,l,1)
			swp(a[i]);
		solve(mid+1,r,now1);
	}
}
```

---

## 作者：OMG_wc (赞：2)

先预处理出正常情况下所有数的最终位置 $p_i$。

然后模拟交换 $b$ 数组，由于只需追踪 $1$，中间少交换一次，如果和 $1$ 无关（也就是 $b_{a_i}$ 和 $b_{a_i+1}$ 都不是 $1$），那答案就是 $p_1$。

若 $b_{a_i}$ 是 $1$，因为少交换一次，真正的 $1$ 是正常情况下的 $b_{a_i+1}$，所以答案是 $p_{b_{a_i+1}}$。

若 $b_{a_i+1}$ 是 $1$，因为少交换一次，真正的 $1$ 是正常情况下的 $b_{a_i}$，所以答案是 $p_{b_{a_i}}$。

时间复杂度 $O(n)$，代码如下:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 200005;

int a[N], b[N], p[N];
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) b[i] = i;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        swap(b[a[i]], b[a[i] + 1]);
    }
    for (int i = 1; i <= n; i++) p[b[i]] = i;
    for (int i = 1; i <= n; i++) b[i] = i;
    for (int i = 1; i <= m; i++) {
        int ans = p[1];
        if (b[a[i]] == 1)
            ans = p[b[a[i] + 1]];
        else if (b[a[i] + 1] == 1)
            ans = p[b[a[i]]];
        printf("%d\n", ans);
        swap(b[a[i]], b[a[i] + 1]);
    }
    return 0;
}

```


---

## 作者：IYSY2009I (赞：1)

[题目描述部分翻译](https://www.luogu.com.cn/paste/l67nzvtx)

我们拿样例1举个例子。

我们考虑没有进行操作二和进行了操作二分别是什么样子：

进行了：

```
12345
21345
23145
23415
24315
```


没进行：

```
12345
21345
21435
24135
```

于是我们发现，只有 $3$ 和 $1$ 的顺序进行了互换，而其它数字都没有发生改变，操作二正好交换的是 $3$ 和 $1$。

换句话说，一个操作只是相当于互换了两个元素的内容（数字），对于这两个元素的移动轨迹并没有什么变化（决定变化的是下标）。

所以我们可以先执行这 $M$ 个操作，记录下这些操作分别交换了什么数字。处理查询时只要检查该操作是否与 $1$ 有关系，如果没有输出最后 $1$ 在原本结果的下标，如果有就输出原本与 $1$ 互换的数字在原本结果的下标就可以了。

时间复杂度 $O(N+M)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
int a[200005];
int b[200005];
pair<int,int> swp[200005];
int id[200005];
int main(){
	int n=read(),m=read();
	for(int i=1;i<=m;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=i;
	for(int i=1;i<=m;i++){
		swp[i].first=b[a[i]];
		swp[i].second=b[a[i]+1];
		swap(b[a[i]],b[a[i]+1]);
	}
	for(int i=1;i<=n;i++)
		id[b[i]]=i;
	for(int i=1;i<=m;i++){
		if(swp[i].first==1||swp[i].second==1) printf("%d\n",id[swp[i].first+swp[i].second-1]);
		else printf("%d\n",id[1]);
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

对于每一个 $k$，预处理出 “第 $k$ 次操作之前的操作结果” 和 “第 $k$ 次操作之后的操作结果”，并将这些结果**合并**即可。

从左往右操作 $i$ 时，`1` 的位置可以通过从**左往右**模拟找到。

$p[i][j]= $“从右往左操作 $i$ 时，当前位置 $j$ 的数值最终的下标” 可以通过从**右往左模拟**找到。

### 代码
```
# include <bits/stdc++.h>
# define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    rep(i, m) cin >> a[i];
    rep(i, m) a[i]--;
    vector<int> s(m);{ 
        int p = 0;
        rep(i, m) {
            s[i] = p;
            if (a[i] == p) p++;
            else if (a[i]+1 == p) p--;
        }
    }
    vector<int> ans(m);
    {
        vector<int> p(n);
        rep(i, n) p[i] = i;
        for (int i = m-1; i >= 0; --i) {
            ans[i] = p[s[i]];
            swap(p[a[i]], p[a[i]+1]);
        }
    }
    rep(i, m) cout << ans[i]+1 << '\n';
    return 0;
}
```

---

