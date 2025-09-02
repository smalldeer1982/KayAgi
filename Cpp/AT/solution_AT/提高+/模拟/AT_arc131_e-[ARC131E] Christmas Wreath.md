# [ARC131E] Christmas Wreath

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc131/tasks/arc131_e

高橋君は、$ N $ 個のボールと $ \frac{N(N-1)}{2} $ 個のロープからなるクリスマス飾りを持っています。ボールには $ 1 $ から $ N $ までの番号が付けられており、どの 2 つの相異なるボールについても、ちょうど 1 つのロープで結ばれています。

![ ](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc131_e/201156bf72fd4f5c2906ec6e262f89d87bd43722.png)

彼は、それぞれのロープを赤・青・白のいずれかの色で点灯させることにしました。

見栄えを良くするため、以下の条件をすべて満たすようにしたいです。

> **条件1** 赤・青・白で点灯されているロープの数は、すべて同数である。
> 
> **条件2** 整数 $ a,\ b,\ c $ $ (1\ \leq\ a\ <\ b\ <\ c\ \leq\ N) $ であって、以下の 3 つのロープの色がすべて異なるものは存在しない。
> 
> - ボール $ a $ と $ b $ を結ぶロープ
> - ボール $ b $ と $ c $ を結ぶロープ
> - ボール $ a $ と $ c $ を結ぶロープ

条件を満たす点灯の方法を 1 つ構成してください。このような方法が存在しない場合、その旨を出力してください。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 50 $
- $ N $ は整数

### Sample Explanation 1

$ N=4 $ では、条件を満たす点灯の方法が存在しないため、`No` と出力すれば正解となります。 `Yes` のときの出力の一例も以下に示しておきますが、\*\*このケースでは不正解となります。\*\*これは、\*\*条件2\*\* で $ (a,\ b,\ c)\ =\ (1,\ 2,\ 3) $ を選ぶと、ボール $ a,\ b $ を結ぶロープは赤、ボール $ b,\ c $ を結ぶロープは白、ボール $ a,\ c $ を結ぶロープは青と、すべて異なるからです。 ``` Yes RBW WB R ```

## 样例 #1

### 输入

```
4```

### 输出

```
No```

# 题解

## 作者：Conan15 (赞：9)

## 前言

2024 年 9 月 11 日：修改题解格式错误问题。

翻译有误，给边染色应当是 RBW 三色，而不是 RGB 三色。\
我码风较为抽象，所以添加了一些注释。\
发现题解区只有一份和我思路相同的题解，但讲解得不是很详细，所以我又写了一篇 QwQ。

一道非常巧妙的构造题。不敢相信这是自己手推出来的。

## 题目翻译

给定一个完全无向图，要求用 RBW 对每条边进行染色，使得三种颜色的边数一样，且不存在三个点使得对应的三条边颜色均不相同。

## 题目讲解

分两类情况讨论——有解和无解。

### 无解判定

注意到总边数是 $\frac{n(n-1)}{2}$，而又需要保证 RBW 三种颜色数量相同，所以边数必须是 $3$ 的倍数，因此 $n \equiv 2 \pmod 3$ 的时候无解。\
另外 $n \leq 4$ 的时候也无解，这个手推一下就知道了。

### 构造思路

我是先想到构造方法再证明的……\
构造方法：对于每一个点 $i$，向 $[1,i)$ 中所有点连**相同颜色的**边。\
它为什么是对的？原因是对于一个点 $i$，它与它前面两个点 $j,k$ 组成**三元环**。但由于 $(j,i)$ 和 $(k,i)$ 同色，所以一定不会出现三条边颜色不同的情况。

发现 $i$ 需要往前面连接 $i-1$ 条边。那么问题就转化为：你需要把 $[0,n-1]$ 总共 $n$ 个数分成 $3$ 组，使得每一组的和相等。

### 如何分组

看到数据范围 $n \leq 50$ 大喜。你会发现总边数是 $\frac{n(n-1)}{2} = 1225$。\
我们使用最暴力的分组想法：设 $f_{i,j,k}$ 表示给前 $[0,i)$ 分配完了，第一组之和 $j$，第二组之和 $k$，第三组之和 $\frac{i(i-1)}{2}-j-k$，**是否可行**。

会发现这样的空间复杂度是 $O(n^5)$ 的，但是由于有 $\frac{1}{4}$ 的常数能开的下。时间复杂度也能过。

然后我们考虑主动转移，并且记录 $pre_{i,j,k}$ 表示哪一组加入了数字 $i$。\
最后倒着推回去就可以求出方案，于是乎问题就解决了。

## 注意事项

要输出 Yes 再输出方案。

## 代码

由于调试的时候心态比较崩，所以码风较为抽象。大家凑合着看吧 QwQ。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 55, M = 1300;
bool f[N][M][M];
struct node {
    int a, b, c;
} pre[N][M][M];
int a[N], b[N], c[N];
int x, y, z;

int ans[N][N];

char get(int x) {   //输出对应字符（是 RBW 不是 RGB）
    if (x == 1) return 'R';
    if (x == 2) return 'B';
    if (x == 3) return 'W';
}

int main() {
    int n; cin >> n;
    if (n % 3 == 2 || n <= 4) return puts("No"), 0; //特判无解
    f[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        int s = (i - 1) * i / 2;
        for (int j = 0; j <= s; j++)
            for (int k = 0; k <= s; k++) {
            	if (!f[i][j][k]) continue;
            	//主动转移。条件当然是 f[i][j][k] 可行。
                f[i + 1][j + i][k] |= 1, pre[i + 1][j + i][k] = (node){i, 0, 0};
                f[i + 1][j][k + i] |= 1, pre[i + 1][j][k + i] = (node){0, i, 0};
                f[i + 1][j][k] |= 1, pre[i + 1][j][k] = (node){0, 0, i};
                //根本不用担心 pre 会被重复覆盖，毕竟只要有一条合法路径就可以了。
                // if (f[i][j][k]) cout << '\t' << i << ' ' << j << ' ' << k << ' ' << i * (i - 1) / 2 - j - k << endl;
            }
    }
    int s = (n - 1) * n / 2;
    if (s % 3 != 0) return puts("No"), 0;   //保险特判无解
    else {
        // cout << f[n][s / 3][s / 3] << endl;

        //a, b, c 表示每一组分配到了哪些数。
        //x, y, z 表示每一组有多少个数。
        int A = s / 3, B = s / 3, C = s / 3, cnt = n;
        //A, B, C 表示当前每一组之和。
        while (A || B || C) {
            node now = pre[cnt][A][B];
            if (now.a) A -= now.a, a[++x] = cnt - 1;
            else if (now.b) B -= now.b, b[++y] = cnt - 1;
            else C -= now.c, c[++z] = cnt - 1;
            //模拟现在从每一组中“删除”数字。
            cnt--;
        }
    }
    //把每一组的数字转化为图。
    for (int i = 1; i <= x; i++) {
        int p = n - 1 - a[i] + 1;
        for (int j = 1; j <= n - p; j++) ans[p][j] = 1;
    }
    for (int i = 1; i <= y; i++) {
        int p = n - 1 - b[i] + 1;
        for (int j = 1; j <= n - p; j++) ans[p][j] = 2;
    }
    for (int i = 1; i <= z; i++) {
        int p = n - 1 - c[i] + 1;
        for (int j = 1; j <= n - p; j++) ans[p][j] = 3;
    }
    puts("Yes");    //因为这个 WA 了一发。
    for (int i = 1; i < n; i++, putchar('\n'))
        for (int j = 1; j <= n - i; j++) putchar(get(ans[i][j]));
    return 0;
}
```

---

## 作者：Egg_eating_master (赞：4)

首先当 $n\le 4$ 或 $n\equiv 2\pmod 3$ 时显然无解。

考虑怎么保证不存在彩色三角形。对于每个 $i$，把边 $(1\sim i-1,i)$ 分成一类，同一类的边染相同的颜色。这样对于任意三个点 $a<b<c$，边 $(a,c)$ 和 $(b,c)$ 都一定是同色的。

接下来保证三种颜色的边数量相同，问题转化为把 $1,2,\cdots, n-1$ 分成三组，使得每组内的数之和相等。

先从边界情况开始考虑：

- 当 $n=6$ 时，分成 $\{1,4\},\{2,3\},\{5\}$；
- 当 $n=7$ 时，分成 $\{1,6\},\{2,5\},\{3,4\}$；
- 当 $n=9$ 时，分成 $\{1,2,3,6\},\{4,8\},\{5,7\}$；
- 当 $n=10$ 时，分成 $\{1,2,3,4,5\},\{6,9\},\{7,8\}$；

当 $n>10$ 时，考虑递推构造，把 $[n-6,n-1]$ 首尾分成三组，然后转化为 $n-6$ 的子问题。

于是就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 55;
int n;
int ans[maxn];
int p;
char c[4] = {'#', 'R', 'W', 'B'};
void work5() {ans[1] = 1; ans[2] = 2; ans[3] = 2; ans[4] = 1; ans[5] = 3;}
void work8() {
    ans[1] = ans[2] = ans[3] = ans[6] = 1;
    ans[4] = ans[8] = 2; ans[5] = ans[7] = 3;
}
void work9() {
    ans[1] = ans[2] = ans[3] = ans[4] = ans[5] = 1;
    ans[6] = ans[9] = 2; ans[7] = ans[8] = 3;
}
int main() {
    cin >> n; n--;
    if (n % 3 == 1 || n <= 4) {cout << "No" << endl; return 0;}
    if (n % 6 == 5) work5(), p = 6;
    if (n % 6 == 2) work8(), p = 9;
    if (n % 6 == 3) work9(), p = 10;
    if (n % 6 == 0) p = 1;
    for (int i = p; i <= n; i += 6) {
        ans[i] = ans[i + 5] = 1;
        ans[i + 1] = ans[i + 4] = 2;
        ans[i + 2] = ans[i + 3] = 3;
    }
    cout << "Yes" << endl;
    for (int i = n; i >= 1; i--, cout << endl)
        for (int j = 1; j <= i; j++)
            cout << c[ans[i]];
    return 0;
}
```


---

## 作者：Reunite (赞：1)

不懂。

显然如果对于每个点，如果我让它与编号大的点连边全部同色，那显然一定不存在三色三元环。因为找到三元环编号最小的点，它向另外两个点的连边同色，显然不满足。

然后我们就暴力试图分配三种边，如果发现无法分配，就直接无解就行。复杂度 $O(n^2)$，正确性未知。我也不明白为啥它能把所有的边在有解的时候恰好分配完。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,m;
int a[55][55];

int main(){
	scanf("%d",&n);
	if(n*(n-1)%6!=0){puts("No");return 0;}
	int x=n*(n-1)/6,pos=0,x1=x,x2=x,x3=x;
	while(x1||x2||x3){
		if(n-pos-1<=x1){
			for(int i=pos+2;i<=n;i++) a[pos+1][i]=1;
			pos++;
			x1-=n-pos;
			continue;
		}
		if(n-pos-1<=x2){
			for(int i=pos+2;i<=n;i++) a[pos+1][i]=2;
			pos++;
			x2-=n-pos;
			continue;
		}
		if(n-pos-1<=x3){
			for(int i=pos+2;i<=n;i++) a[pos+1][i]=3;
			pos++;
			x3-=n-pos;
			continue;
		}
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++) putchar(a[i][j]==1?'R':a[i][j]==2?'B':'W');
		puts("");
	}

	return 0;
}
```

---

## 作者：GI录像机 (赞：0)

## 思路

当边数不为三的倍数时，显然无解。

当一个点连出的所有边都是同一颜色时，我们就可以忽略该点。因为所有包含该点的三元环都至少有两个同色边。

问题加强成让所有的 $i$ 向 $j>i$ 连出的边同色，且每种颜色的数量相同。

考虑从 $i=1$ 开始填红，直到编号最小的 $j$ 需要连出的边数大于红所剩的染色数量。

假设此时还有 $R$ 条边需要染红。那么我们直接把会连出 $R$ 条边的点染红即可。

蓝边同理。就算蓝色最后同样有 $R$ 条边需要染红，我们也可以直接染连出 $R-1$ 和 $1$ 条边的点。

把剩下的边染白，即为答案。

## 代码

```cpp
// LUOGU_RID: 147790489
#include<bits/stdc++.h>
using namespace std;
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 60, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int n = read(), col[N][N], cnt1, cnt2, cnt3;
signed main() {
	cnt1 = cnt2 = cnt3 = n * (n - 1) / 6;
	if(n % 3 == 2 || n <= 4) {
		puts("No");
		return 0;
	}
	for(int i = 1; i <= n; i++) {
		if(cnt1 < n - i)continue;
		cnt1 -= n - i;
		for(int j = i + 1; j <= n; j++) col[i][j] = 'R';
	}
	for(int i = 1; i <= n; i++) {
		if(cnt2 < n - i || col[i][n] == 'R')continue;
		cnt2 -= n - i;
		for(int j = i + 1; j <= n; j++) col[i][j] = 'B';
	}
	puts("Yes");
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			if(!col[i][j])col[i][j] = 'W';
			putchar(col[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Schi2oid (赞：0)


题意：给定一张 $n$ 个点的完全图，要求将边染成三种颜色，满足三种颜色的边数都相同，且不存在三元环中的边两两异色。

题解：考虑递归构造，尝试将 $n$ 个点划分为两个集合 $A,B$，分别满足上述条件，并且适当地构造之间的连边使得整张图依然满足条件。

考虑对于 $A$ 中每个点，钦定其与 $B$ 中点的连边都为某一个确定的颜色，那么所有包含 $B$ 中两个点，$A$ 中一个点的环就都合法，只需要考虑 $B$ 中一个点，$A$ 中两个点的情况。 那么我们就需要找到一种合适的钦定 $A$ 中点与 $B$ 连边的颜色的方案，使得任意一条 $A$ 中的边一定都有一端点钦定的颜色与该边颜色相同。令 $|A|=6$，则容易找到一组构造：

![](https://z1.ax1x.com/2023/10/25/piVdX5D.png)

因此只要获得了 $n-6$ 的构造，我们就可以获得 $n$ 的构造，解出较小的构造后不断递推求解即可。

---

## 作者：songhongyi (赞：0)

首先边数不是 $3$ 的倍数肯定寄。等价于 $n=3k+2$。

那我们看看没有异色三元环意味着什么。我们随便选出来三个点，一定有一个点的两边是同色的。

不过随便一个点太没用了，加强为三个中最大的点。

这意味着，我们只需要对每个 $i$，把 $i \to 1, i\to 2,\cdots,i\to i-1$ 连为一个颜色，一定就满足要求。

再考虑总颜色相等。这等价于把 ${0,1,\cdots,n-1}$ 分为 $3$ 个和相等的集合。考虑到 $n$ 只有 50，那么就可以直接背包 DP。

貌似也可以随机化，挺搞笑的。



---

