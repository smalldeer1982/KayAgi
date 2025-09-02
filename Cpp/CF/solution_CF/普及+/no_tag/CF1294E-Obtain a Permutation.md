# Obtain a Permutation

## 题目描述

You are given a rectangular matrix of size $ n \times m $ consisting of integers from $ 1 $ to $ 2 \cdot 10^5 $ .

In one move, you can:

- choose any element of the matrix and change its value to any integer between $ 1 $ and $ n \cdot m $ , inclusive;
- take any column and shift it one cell up cyclically (see the example of such cyclic shift below).

A cyclic shift is an operation such that you choose some $ j $ ( $ 1 \le j \le m $ ) and set $ a_{1, j} := a_{2, j}, a_{2, j} := a_{3, j}, \dots, a_{n, j} := a_{1, j} $ simultaneously.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1294E/8565157bd76bb2dbe391e7f12ac2946eff0ed96a.png) Example of cyclic shift of the first column You want to perform the minimum number of moves to make this matrix look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1294E/f0a34fa55590e79e2f0e0af3c39b0d9ee30b43c2.png)In other words, the goal is to obtain the matrix, where $ a_{1, 1} = 1, a_{1, 2} = 2, \dots, a_{1, m} = m, a_{2, 1} = m + 1, a_{2, 2} = m + 2, \dots, a_{n, m} = n \cdot m $ (i.e. $ a_{i, j} = (i - 1) \cdot m + j $ ) with the minimum number of moves performed.

## 说明/提示

In the first example, you can set $ a_{1, 1} := 7, a_{1, 2} := 8 $ and $ a_{1, 3} := 9 $ then shift the first, the second and the third columns cyclically, so the answer is $ 6 $ . It can be shown that you cannot achieve a better answer.

In the second example, the matrix is already good so the answer is $ 0 $ .

In the third example, it is enough to shift the second column cyclically twice to obtain a good matrix, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3 3
3 2 1
1 2 3
4 5 6```

### 输出

```
6```

## 样例 #2

### 输入

```
4 3
1 2 3
4 5 6
7 8 9
10 11 12```

### 输出

```
0```

## 样例 #3

### 输入

```
3 4
1 6 3 4
5 10 7 8
9 2 11 12```

### 输出

```
2```

# 题解

## 作者：syksykCCC (赞：13)

先观察一下两种操作：

* 单点修改
* 整列上移

发现了什么？**不同列之间互不影响**，所以我们可以对于每一列分开处理。

那么，对于一列 $j$，因为“先修改，后上移”和“先上移，后修改”没有本质区别，所以我们定义 $same_{j, i}$（$0\le i <n $）表示将第 $j$ 列上移 $i$ 个单位后，有几个数是不用变的。那么上移了 $i$ 个单位以后，自然还有 $n - same_{j, i}$ 个数是需要变的，那么就要花费 $n - same_{j,i}$ 次修改操作，上移也花费了 $i$ 次操作，那第 $j$ 列的最优方案就是 $\min\limits_{0 \le i < n } \left(i + n - same_{j, i} \right)$，最终答案就是：

$$ans = \sum_{j = 1}^{m}\left( \min\limits_{0 \le i < n } \left(i + n - same_{j, i} \right) \right)$$

现在唯一的问题就是如何求出 $same$ 了。我们发现，如果一个数 $a_{i, j}$ 是 **应该出现在第 $\boldsymbol{j}$ 列** 的数字，那么一定有 $j \le a_{i,j} \le n \times m$，同时 $a_{i, j} \equiv j \pmod{m}$（后者在代码里写作了 `(a[i][j] - j) % m`）。

如果上面的条件满足了，那我们就可以算一下 $a_{i,j}$ 这个数字应该出现在哪一行。显然，它应该出现在 $\dfrac{a_{i,j} - j}{m} + 1$ 行（记作 $k$）。

那如果我们把 $a_{i,j}$ 移到第 $k$ 行，它就不用变了。回顾 $same$ 的定义，从第 $i$ 行移到第 $k$ 行，要移动几次呢？

* 如果 $i \ge k$，移动 $i - k$ 个单位即可；
* 如果 $i < k$，那首先把它移到第 $1$ 行需要 $i - 1$ 次，然后再移 $1$ 次到第 $n$ 行，从第 $n$ 行移到第 $k$ 行需要 $n - k$ 次，加起来，就是 $i - 1 + 1 + n - k$，化简得 $i - k + n$。

如果合并的话，就是要移动 $(i - k + n) \bmod n$ 次，那么我们就可以把 $same_{j, (i - k + n) \bmod n}$ 增加 $1$ 了。

注意 $n, m$ 都有可能达到 $2 \times 10^5$，所以需要开不定长数组，时间复杂度 $\mathcal O(nm)$。$same$ 可以每列重复使用，舍去前一个维度。

代码贴出，仅供参考。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int NM = 2e5 + 5;
int n, m, same[NM], ans;
vector<int> a[NM];
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		a[i].push_back(0); // 下标凑成从 1 开始
		for(int j = 1; j <= m; j++)
		{
			int val;
			cin >> val;
			a[i].push_back(val);
		}
	}
	for(int j = 1; j <= m; j++)
	{
		int tans = INT_MAX;
		for(int i = 0; i < n; i++) same[i] = 0;
		for(int i = 1; i <= n; i++)
		{
			if(a[i][j] < j || a[i][j] > n * m || (a[i][j] - j) % m != 0) continue;
			int k = (a[i][j] - j) / m + 1;
			same[(i - k + n) % n]++;
		}
		for(int i = 0; i < n; i++) tans = min(tans, i + n - same[i]);
		ans += tans;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：清尘 (赞：2)

由题意易得每列互不相关，对每列单独考虑

在一列中，有些数本来就是目标状态中这一列的数，可以通过若干次移动操作使其在正确的位置，有些数则只能修改

统计这一列如果移动 k 次(0 <= k <= n - 1)有多少数不需要修改

设第 i 行第 j 列的数为 x，若 x <= n * m && (x - j) % m == 0, 说明 x 在目标状态中是第 j 列第 (x - j) / m + 1 行的数，(注意这里一定要判断x <= n * m，比赛时没判断查了半天也没发现)

可以通过 p = (i - (x - j) / m - 1 + n) % n 次移动操作使 x 在正确的位置（+ n 在 % n 是为了处理负数）并在计数数组 c 中使 c[p]++

最后枚举移动次数 k，这一列需要的步骤 ans = min (k + n - c[k])，并将 ans 累加到最终答案res中

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
inline void read (int &x) {
    char ch = getchar(); x = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
}
const int N = 2e5 + 10;
int n, m, res, c[N];
vector<int> v[N];
signed main() {
    read (n), read (m);
    int x;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) read (x), v[i].push_back (x);
    for (int j = 1; j <= m; ++j) {
        for (int i = 0; i < n; ++i) c[i] = 0;
        int ans = 1e9, tmp = 0;
        for (int i = 1; i <= n; ++i) {
            int t = v[i][j - 1];
            if ((t - j) % m == 0 && t <= n * m) 
                ++c[(i - (t - j) / m - 1 + n) % n];
        }
        for (int i = 0; i < n; ++i) ans = min (ans, i + n - c[i]);
        res += ans;
    } printf ("%d\n", res);
    return 0;
}
```

---

## 作者：wssdl (赞：1)

**写在最前：如果有不懂，欢迎私信。如果有小错误，欢迎指出。**

### 思路

看完题之后，我们知道了这一题支持两种操作：

1. 把某一列统一向上挪一格，第一行挪到最后一行。

2. 把某一个数改成 $1$ 到 $n \times m$ 中的任意一个数字。

显然，列于列之间互相不影响，所以我们可以一列一列地算出最小次数，然后累加即可。

那么怎么计算每一列的最小值呢？

一开始我想到了直接暴力来计算每一列往上挪的次数，但是，这样很明显会超时。

那怎么来优化呢？

其实，我们只用记录每一个点到它应该到的位置的距离即可，比如，我们现在有一个 $3 \times 3$ 的矩阵：

```cpp
3 3
3 2 1
1 2 3
4 5 6
```

其中，数字 $1$ 应该到 $(1, 1)$ 这个位置，但是， $1$ 现在在 $(2, 1)$ ，所以它到目标位置要挪 $1$ 次。

同理，数字 $4$ 应该到 $(2, 1)$ 这个位置，但是， $4$ 现在在 $(3, 1)$ ，所以它到目标位置要挪 $1$ 次 。

我们用一个桶数组 $s$ 来记录。

为什么要用桶数组呢，因为 $s_i$ 表示的是把某一列向上挪 $i$ 此后，有 $s_i$ 个数字已经到了目标位置，剩下就有 $n - s_i$ 个数，这样的话，要想求出每一列的最小次数，我们就只用从 $s_i$ 中取出最大值，然后剩下的数字单独执行操作二即可，最小次数就是 $i + n - s_i$ 。

可能有细心的童鞋发现了，数字 $3$ 在 $(1, 1)$ ，但是它应该去 $(1, 3)$ ，不在同一列了怎么办？

其实很简单，既然不在同一列了，那肯定怎么往上挪也挪不到目标位置了，所以它要执行操作 $2$ 。

在程序里，我把它和超过 $n \times m$ 的数字单独拿出来计算了。

那怎么清空 $s$ 数组呢？

如果直接清空的话，最坏情况复杂度会达到 $2e5$ 的平方，会超时，所以我们只能在取最大值时清空 $s$ 数组。

~~那怎么读入呢？~~

直接开二维数组肯定不行，所以要使用 ~~人见人爱~~ 的 $vector$ 。

### $code$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int n, m, ans;  // n和m为题目输入，ans负责累加答案

int s[N];

vector<int> a[N];

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {    //行
    a[i].push_back(0);              //因为vector是从0开始的，我们习惯从1开始，所以先加入一个0
    for (int j = 1; j <= m; j++) {  //列
      int x;
      cin >> x;
      a[i].push_back(x);  //读入
    }
  }
  for (int i = 1; i <= m; i++) {  //我们一列一列地枚举处理
    int sum = 0;                  //记录特殊的数，比如目标位置不在该列或者超过n*m的数字个数，这些特殊数字只能执行第二种操作，所以最后要单独累加
    for (int j = 1; j <= n; j++) {
      int x = (a[j][i] % m == 0 ? a[j][i] / m : a[j][i] / m + 1), y = (a[j][i] % m ? a[j][i] % m : m);  //计算目标的x,y位置
      if (y != i || a[j][i] > n * m) {                                                                  //发现特殊的数
        sum++;                                                                                          //累加
        continue;
      }
      if (x == j && y == i) {  //如果不需要移动，那就是移动0次
        s[0]++;
      } else if (x < j) {  //如果目标位置在现在位置的上面
        s[j - x]++;
      } else {  //在下面
        s[n - x + j]++;
      }
    }
    int minx = 1e9;
    for (int j = 0; j < n; j++) {
      minx = min(minx, j + n - s[j] - sum);  //取最小操作次数，在上文里讲过
      s[j] = 0;                              //清空
    }
    ans += minx + sum;  //累加每一列的最小值
  }
  cout << ans;  //输出
  return 0;
}
```

**RP++!**

---

## 作者：Inui_Sana (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1294E)

解题思路：（话说好像不太需要这个）

题目一共有两种操作。很容易可以发现：这两种操作不会做横向更改，只有纵向。那我们对于一列，设第 $i$ 列用 $j$ 次整体上移操作能有 $k$ 个位置上的数成功对应，那么剩下 $n-k$ 个位置需要进行修改，所以 $ans= \sum\limits_{i=1}^m \min\limits_{0\leq j<n}(j+n-k)$。

具体求进行 $j$ 次上移后有多少对应上，我们可以建立一个 $cnt$ 数组，枚举该列中的所有数。如果它的对应位置在这列中，那么看他上移多少位能回到对应位置上，设将要 $x$ 次操作，则将 $cnt_x+1$，也就是 $k$ 值 $+1$。

因为这题 $n$ 和 $m$ 的值域是不确定的，所以采用一维数组表示二维。

code：

```cpp
int n,m,ans,e[maxn],cnt[maxn];
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*m;i++)scanf("%d",&e[i]);
	for(int i=1;i<=m;i++){
		int res=infi;
		for(int j=0;j<n;j++)cnt[j]=0;
		for(int j=i;j<=n*m;j+=m){
			if(e[j]%m!=i%m)continue;
			int u=(j-1)/m+1,v=(e[j]-1)/m+1;
			if(v>n)continue;
			cnt[(u+n-v)%n]++;
		}
		for(int j=0;j<n;j++)res=min(res,j+n-cnt[j]);
		ans+=res;
	}
	printf("%d",ans);
}
signed main(){
	int t=1;
//	scanf("%d",&t);
	while(t--)solve();
}


---

## 作者：星落云川 (赞：0)

首先让我们来看题目中给的两种操作：  
- 选择矩阵中任意一个元素进行变换
- 选择矩阵中任意一列进行周期上移  
  
这两种操作都只会对矩阵的列有影响。因此，在对矩阵的操作过程中，其实是以列为基本单位进行操作的。我们可以依次对每一列进行操作，计算出每一列所需操作的最小值，累加起来的和就是最终答案。  
  
我们取出矩阵的某一列进行上移操作后，没有归位的元素需要用操作一变换为对应元素。矩阵上移的格数最多为 $n$ (超过 $n$ 就转回来了，没有意义)，因此，对于每一种上移的情况都有与之对应的变换情况。我们对每一种情况进行枚举，就能得出最小的操作次数。  
  
如果采用模拟的方式，时间复杂度将为 $O(mn^2)$，显然会超时。  
  
由于题目要求的目标矩阵形式是给定的，所以我们可以求出矩阵中任意某个数所在的位置，并与现在矩阵中该数的位置进行比较，得出上移的格数。然后，另开一个数组记录上移某个格数时归位元素的个数。对上移的格数进行枚举， 最终得出上移操作 $x$ 格能够获得的最大归位元素个数 $max$， 则该行复位需要的最小操作数为 $n-max+x$。此时，时间复杂度被优化到 $O(nm)$。  
  
至于求某个元素应在格的公式，其实题目的图已经给出了,在此不再赘述。如果不好理解，如下代码可供参考。  
  
值得注意的点：  
- 题目中 $n$ 和 $m$ 都可能达到 $10^5$ 级别，因此不能直接开二维数组。由于题目对 $nm$ 进行了限定，因此可以直接开一维数组，再从中取数。当然也可以通过动态数组解决。  
- 题目中只说明了所给矩阵中的元素小于 $2·10^5$，并没有说明元素小于 $nm$，因此必须进行判断，谨防数组越界。(惨痛的教训$QAQ$)  
  
为您奉上代码：
```c
#include<stdio.h>
#include<stdlib.h>
int mat[200005]={}, row[200005]={}, cnt[200005]={};
int read()
{
	int x=0;
	char ch = getchar();
	while( ch<'0' || ch>'9' ) ch = getchar();
	while( ch>='0' && ch<='9' ){
		x = (x<<3) + (x<<1) + ch - 48;
		ch = getchar();
	}
	return x;
}
int cmp( int n, int m, int j )
{
	int move, realN, min=2<<29;
	for( int i=1; i<=n; i++ ){
		if( row[i] % m != j%m ) continue; //如果该元素不应该在该列在必须通过变换的方式解决
		if( row[i]<1 || row[i]>n*m ) continue; //谨防越界
		realN = (row[i]-j) / m + 1; //应该放在的位置
		move = i - realN; //向上移动的格数
		if( move<0 ) move += n; //周期性移动
		cnt[ move ]++; //移动move个单位归位元素个数
	}
	for( int i=0; i<n; i++ )
		min = min < n-cnt[i]+i ? min : n-cnt[i]+i;
	return min;
}
int main()
{
	int n, m, ans=0;
	scanf("%d %d", &n, &m);
	for( int i=1; i<=n*m; i++ )
		mat[i] = read();
	for( int j=1; j<=m; j++ ){ //操作只对列有影响 枚举列
		for( int i=0; i<n; i++ )
			cnt[i] = 0; //初始化
		for( int i=0; i<n; i++ )
			row[ i+1 ] = mat[ j + i*m ];
		ans += cmp( n, m, j );
	}
	printf("%d\n", ans);
	system("pause");
	return 0;
}
```


---

