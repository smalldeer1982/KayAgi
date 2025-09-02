# [CoE R4 C] 网格

## 题目描述

**这是一道交互题。**

有一张 $n$ 个点的无向无权图。

这张图有一个特殊性质：存在一个点 $u \ (1 \leq u \leq n)$ 到正整数对 $(x, y) \ (1 \leq x \leq l, 1 \leq y \leq c)$ 的**一一对应**关系，使得 $n = l \cdot c$，且点 $u, v$ 间存在边当且仅当 $u, v$ 对应的数对 $(x_u, y_u), (x_v, y_v)$ 满足 $|x_u - x_v| + |y_u - y_v| = 1$。换而言之，这张图和 $l$ 行 $c$ 列的网格图同构。

现在，你要通过一些询问还原这张图的结构。每次询问时，你需要给定一个点 $u \ (1 \leq u \leq n)$。询问的返回值是一个长为 $n$ 的数组 $\{d_i\} \ (1 \leq i \leq n)$，表示点 $u, i$ 间的最短路径所经过的边数。

请你使用不超过 $q$ 次询问，还原出这张图的结构。

---

### 交互格式

**本题有多组数据。**

首先输入一个整数 $T$，表示数据组数。

对于每组数据：

- 首先输入一个整数 $n$，表示图的点数。
- 接下来，你可以执行一些询问。对于每次询问，输出一个整数 $u$，为你询问的点。然后，输入 $n$ 个整数 $\{d_i\}$，为询问的返回值。
- 当你确定答案后，输出一个整数 $0$，然后输出答案。

在输出答案时：

- 第一行输出两个整数 $l, c$；
- 接下来，输出 $l$ 行 $c$ 列整数，为你还原的对应关系。第 $i$ 行 $j$ 列的数为 $(i, j)$ 对应的编号。

如果有多个答案，你可以输出任意一个。一个答案是正确的，当且仅当它和标准答案无法被任何询问区分：也就是，在这两个答案对应的网格图中，任意点对间的最短路径所经过的边数都是相同的。

---

请注意：**在每次执行询问或者输出答案后，你应该清空缓冲区：**

- 在 C++ 中，使用 `fflush(stdout)` 或 `cout.flush()`。
- 在 Java 中，使用 `System.out.flush()`。
- 在 Python 中，使用 `stdout.flush()`。
- 在 Pascal 中，使用 `flush(output)`。
- 对于其他语言，请自行查阅对应语言的帮助文档。


## 说明/提示

### 样例 $1$ 解释

对于样例，以下 $3$ 行 $2$ 列的网格图也是正确的输出。

```
3 2
4 2
3 5
6 1
```

左边是样例对应的网格图，右边是以上输出对应的网格图。

![](https://cdn.luogu.com.cn/upload/image_hosting/jy23v0au.png)

---

### 评分标准

对于一个子任务，令 $q_{\max}$ 为你在这个子任务的所有测试数据中的最大询问次数。

如果交互的格式不合法，运行超出了时间限制，或者你的答案不正确，或者 $q_{\max} > q$，你的得分为 $0$。

否则，对于子任务 $1 \sim 3$，你得满分；对于子任务 $4$，你的分数由下表给出：

| 条件 | 分数 |
| :-: | :-: |
| $q_{\max} \leq 3$ | $61$ |
| $q_{\max} = 4$ | $41$ |
| $q_{\max} = 5$ | $31$ |
| $q_{\max} = 6$ | $21$ |
| $q_{\max} \geq 7$ | $11$ |

---

### 数据规模

**本题采用捆绑测试。**

| 子任务 | 分值 | $n \leq$ | $q = $  | 特殊性质 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $3$ | $4$ | $4$ | 无 |
| $2$ | $13$ | $10^5$ | $4$ | 存在解使得 $l = 1$ |
| $3$ | $23$ | $36$ | $36$ | 存在解使得 $2 \leq l, c \leq 6$ |
| $4$ | $61$ | $10^5$ | $12$ | 无 |

对于所有数据，保证 $1 \leq T \leq 10^3$，$1 \leq n \leq 10^5$，$\sum n \leq 3 \times 10^5$。

在部分测试数据中，交互器是自适应的。也就是，图的结构可能会根据你的询问而变化。但是可以保证：在每次询问之后，存在至少一个答案符合当前所有询问的返回值。


## 样例 #1

### 输入

```
1
6

0 2 2 3 1 1

2 0 2 1 1 3

2 2 0 1 1 1

3 1 1 0 2 2

1 1 1 2 0 2

1 3 1 2 2 0```

### 输出

```


1

2

3

4

5

6

0
2 3
2 5 1
4 3 6```

## 样例 #2

### 输入

```
2
1



2

1 0```

### 输出

```


0
1 1
1

2

0
2 1
1
2```

# 题解

## 作者：Sakura_xyz (赞：2)

~~直接模拟即可。~~

### 分析
我们注意到这样一件事情，对于一张网格图来说，确定两个邻角到每个点的曼哈顿距离就可以确定整张图的结构。

规定网格图规模为 $l \times c$ ， $(i,j)$ 代表第 $i$ 行第 $j$ 列。

例如，设图的左上角为 $a$ ，左下角为 $b$ ，则对于点 $p$ 来说，很显然有

$$p : (\frac{1}{2}(dis(a,p) - dis(b,p) + dis(a,b) + 2),\frac{1}{2}(dis(a,p) + dis(b,p) - dis(a,b) + 2))$$

我们构造两条路径：

1.从左上角 $a$ 一直向下走，至 $p$ 点所在行，再向右走，至 $p$ 点所在列。

2.从右下角 $b$ 一直向上走，至 $p$ 点所在行，再向右走，至 $p$ 点所在列。

可以发现，两条路径的长度分别为 $dis(a,p),dis(b,p)$ 。

首先，无论 $p$ 点的坐标在哪个位置，两条路径必然恰好覆盖全了一整列，并且从第一列至 $p$ 所在列走了两次，进而可求得 $p$ 点的 $y$ 坐标，又由于 $p$ 点到 $a,b$ 的距离确定，相减就能得出 $x$ 坐标。

现在问题就转化成了在 $3$ 次询问内找出网格图的两个邻角。

我们先询问 $1$ 号点，这时候，距离 $1$ 号点最远的点一定在角上，可以采用反证法，若其不是一个角，则可继续向远离 $1$ 的位置找点，找到的角必然更远。这时候，我们知道了一个角，询问这个角，便一定能找出这个角的对角（距离其最远的点）。钦定找到的角为 $x$ ，对角为 $y$ ，则有 $l + c = dis(x,y) - 2$ ，又已知 $l \times c = n$ ，则能确定出 $l,c$ 。

并且，我们确定了 $l,c$ ，只需要知道一个点和 $x$ 的距离，就能确定其与 $y$ 的距离。

现在，我们根据已知条件，求出点 $1$ 的坐标。

设：
$$sum_1 = \sum_{i = 1}^{ n } { [dis(x,i) + dis(1,i) = dis(x,1)] }$$
$$sum_2 = \sum_{i = 1}^{ n } { [dis(y,i) + dis(1,i) = dis(y,1)] }$$

不妨设 $x$ 为左上角， $y$ 为右下角。

我们观察到，满足 $sum_1$ 求和号内条件的点必然在以左上角为 $x$ ，右下角为 $1$ 的矩形中，满足 $sum_2$ 求和号内条件的点必然在以 $1$ 为左上角， $y$ 为右下角的矩形中。也就意味着，设点 $1$ 的坐标为 $(i,j)$ ，则 $sum_1 = i \times j,sum_2 = (r - i + 1) \times (c - j + 1)$ ，又由于我们知道 $1$ 与左上角的距离，便可以求得坐标。

不妨设 $l \leq c$ ，我们从网格图的左上向右下画一条线，注意到，当 $1$ 在线的下侧时，右上角比左下角距离更远。所有距离 $x$ 为 $c - 1$ 的点必然在从右上角开始，坐标每次变化 $(1,-1)$ 得到的，那么，其他距离 $x$ 为 $c - 1$ 的点就一定比右上角近，因此，不可能存在一个点使得 $1$ 到这个点的距离与 $1$ 到右上角的距离相等，因此可以确定右下角，左上角同理。

注意到 $l = c$ 时无法判断是左上角还是右下角，不过此时是对称的，没有影响。

另外，我们观察到，有很多情况需要特判。

定义一个点的度数为与其距离为 $1$ 的节点的个数。

首先，只有一个点的时候直接判。

然后，我们发现，若点 $1$ 的度数为 $1$ ，则必然是一个 $1 \times n$ 的网格，直接输出即可。

同理，若点 $1$ 的度数为 $2$ ，则询问其中一个与点 $1$ 相邻的点 $q$ ，若 $q$ 度数为 $1$ ，则是 $1 \times n$ ，若其度数为 $3$ ，则将 $1$ 看做找到的角， $q$ 看做最开始询问的 $1$ ，正常计算即可。若 $q$ 度数为 $2$ ，询问距离其最远的点 $s$ ，若 $s$ 度数为 $1$ ，则是 $1 \times n$ 的情况，否则表明 $1,q$ 是一个 $2 \times \frac{n}{2}$ 的网格的两个邻角。

~~以上是我花 $10$ 块钱买了官方题解的原因。~~

### AC 代码
```cpp
#include<iostream>
#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>
#define MAXN 100005
#define fi first
#define se second

using namespace std;

int n,a1[MAXN],a2[MAXN],a3[MAXN];

void Ask(int * a,int x){
	cout << x << endl;
	for(int i=1;i<=n;i++) cin >> a[i];
}

int X,Y,Z,l,c,x_1,y_1;

inline int dis_1(int x) { return a1[x]; }
inline int dis_X(int x) { return a2[x]; }
inline int dis_Y(int x) { return l+c-2-a2[x]; }
inline int dis_Z(int x) { return a3[x]; }
inline int Abs(int x) { return x>0?x:-x; }

inline int get_d(int * a){
	int ret=0;
	for(int i=1;i<=n;i++) ret+=(a[i]==1);
	return ret;
}

void solve_1(){
	vector <int> a(n,0);
	a[0]=1;
	for(int i=1;i<=n;i++) a[a1[i]]=i;
	cout << 0 << endl;
	cout << 1 << ' ' << n << endl;
	for(int i=0;i<n;i++) cout << a[i] << ' ';
	cout << endl;
}

void get_ans(int pos_1){
	for(int i=1;i<=n;i++) if(a2[i]>=a2[Y]) Y=i;
	int sum_lc=dis_X(Y)+2;
	for(int i=1;i<=n;i++){
		if((!(n%i))&&i+n/i==sum_lc){
			l=i; c=n/i; break;
		}
	}
	int t1=0,t2=0;
	for(int i=1;i<=n;i++){
		if(dis_1(i)+dis_X(i)==dis_X(pos_1)) t1++;
		if(dis_1(i)+dis_Y(i)==dis_Y(pos_1)) t2++;
	}
	for(int i=1;i<=l;i++){
		for(int j=1;j<=c;j++){
			if(i+j==dis_1(X)+2&&i*j==t1&&(l-i+1)*(c-j+1)==t2){
				x_1=i,y_1=j;
				break;
			}
		}
	}
	vector <int> ld,ru;
	for(int i=1;i<=n;i++){
		if(dis_X(i)==l-1&&dis_1(i)==Abs(l-x_1)+Abs(y_1-1)){
			ld.push_back(i);
		}
		if(dis_X(i)==c-1&&dis_1(i)==Abs(1-x_1)+Abs(c-y_1)){
			ru.push_back(i);
		}
	}
	vector < vector <int> > a(l,vector <int> (c,0));
	if(Z){
		if(dis_X(Z)==l-1){
			for(int i=1,tx,ty;i<=n;i++){
				ty=(dis_Z(i)+dis_X(i)-dis_X(Z)+2)/2;
				tx=dis_X(i)-ty+2;
				a[tx-1][ty-1]=i;
			}
			cout << 0 << endl;
			cout << l << ' ' << c << endl;
			for(int i=0;i<l;i++){
				for(int j=0;j<c;j++){
					cout << a[i][j] << ' ';
				}
				cout << endl;
			}
		}
		else{
			for(int i=1,tx,ty;i<=n;i++){
				tx=(dis_Z(i)+dis_X(i)-dis_X(Z)+2)/2;
				ty=dis_X(i)-tx+2;
				a[tx-1][ty-1]=i;
			}
			cout << 0 << endl;
			cout << l << ' ' << c << endl;
			for(int i=0;i<l;i++){
				for(int j=0;j<c;j++){
					cout << a[i][j] << ' ';
				}
				cout << endl;
			}
		}
		return;
	}
	if(ld.size()==1){
		Ask(a3,ld[0]),Z=ld[0];
		for(int i=1,tx,ty;i<=n;i++){
			ty=(dis_Z(i)+dis_X(i)-dis_X(Z)+2)/2;
			tx=dis_X(i)-ty+2;
			a[tx-1][ty-1]=i;
		}
		cout << 0 << endl;
		cout << l << ' ' << c << endl;
		for(int i=0;i<l;i++){
			for(int j=0;j<c;j++){
				cout << a[i][j] << ' ';
			}
			cout << endl;
		}
	}
	else{
		Ask(a3,ru[0]),Z=ru[0];
		for(int i=1,tx,ty;i<=n;i++){
			tx=(dis_Z(i)+dis_X(i)-dis_X(Z)+2)/2;
			ty=dis_X(i)-tx+2;
			a[tx-1][ty-1]=i;
		}
		cout << 0 << endl;
		cout << l << ' ' << c << endl;
		for(int i=0;i<l;i++){
			for(int j=0;j<c;j++){
				cout << a[i][j] << ' ';
			}
			cout << endl;
		}
	}
}

void solve_2(){
	int p;
	for(int i=1;i<=n;i++){
		if(a1[i]==1) { p=i; Ask(a2,p); break; }
	}
	if(get_d(a2)>=3){
		swap(a2,a1); X=1;
		get_ans(p);
	}
	else if(get_d(a2)==1){
		vector <int> a(n,0);
		a[0]=p;
		for(int i=1;i<=n;i++) a[a2[i]]=i;
		cout << 0 << endl;
		cout << 1 << ' ' << n << endl;
		for(int i=0;i<n;i++) cout << a[i] << ' ';
		cout << endl;
	}
	else{
		for(int i=1;i<=n;i++) if(a2[i]>=a2[Z]) Z=i;
		Ask(a3,Z);
		if(get_d(a3)==1){
			vector <int> a(n,0);
			a[0]=Z;
			for(int i=1;i<=n;i++) a[a3[i]]=i;
			cout << 0 << endl;
			cout << 1 << ' ' << n << endl;
			for(int i=0;i<n;i++) cout << a[i] << ' ';
			cout << endl;
		}
		else{
			swap(a1,a2);
			get_ans(p);
		}
	}
}

void solve(){
	X=Y=Z=l=c=x_1=y_1=0;
	cin >> n;
	Ask(a1,1);
	if(get_d(a1)==0){
		cout << 0 << endl;
		cout << 1 << ' ' << 1 << endl;
		cout << 1 << endl;
		return;
	}
	if(get_d(a1)==1) return solve_1();
	if(get_d(a1)==2) return solve_2();
	for(int i=1;i<=n;i++) if(a1[i]>=a1[X]) X=i;
	Ask(a2,X);
	get_ans(1);
}

int main(){
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

```

---

