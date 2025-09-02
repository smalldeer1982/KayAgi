# [ICPC 2021 Nanjing R] Puzzle in Inazuma

## 题目描述

每个旅行者都知道，在稻妻解开谜题后，他们会得到一个宝箱，但很少有人知道这些谜题是由鸣神大社的宫司八重神子设计的，用来测试旅行者是否足够强大以拯救她的朋友雷电将军和稻妻的人民。

在旅行者通过测试后，八重神子必须将谜题重置为初始状态。但这次她遇到了一些麻烦，甚至怀疑其中一些谜题是否已经损坏。

在重置之前，八重神子的谜题可以被视为一个加权无向完全图 $G$。我们也将初始状态表示为另一个加权无向完全图 $H$。$G$ 和 $H$ 都有 $n$ 个顶点，这些顶点从 $1$ 到 $n$ 标记。

为了将图 $G$ 重置为 $H$，八重神子可以执行以下操作任意次：
- 首先选择四个不同的顶点 $a$，$b$，$c$，$d$ 和一个整数 $x$。注意，每次她可以选择不同的 $a$，$b$，$c$，$d$ 和 $x$。
- 令 $(i, j)$ 为顶点 $i$ 和 $j$ 之间的边。将 $(a, b)$，$(a, c)$ 和 $(a, d)$ 的权重增加 $x$，同时将 $(b, c)$，$(b, d)$ 和 $(c, d)$ 的权重减少 $x$。

请帮助八重神子确定她是否可以将图 $G$ 变为图 $H$。如果可以，你还需要告诉她详细的步骤。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
0 1 1
0 0
1
1 0 0
1 1
0
```

### 输出

```
1
2 1 3 4 1
```

## 样例 #2

### 输入

```
4
3 3 3
0 0
0
0 0 0
3 3
3
```

### 输出

```
1
1 2 3 4 -3
```

## 样例 #3

### 输入

```
5
-12 15 -12 1
37 14 7
7 9
-11
12 5 1 13
-1 -4 -7
-5 -9
18
```

### 输出

```
-1
```

# 题解

## 作者：modfish_ (赞：0)

以下是一大坨。

## Part 1
首先可以令 $G$ 上的边权全部减去 $H$ 上对应边权。然后目标变成了把 $G$ 上的权全部变成 $0$。

一个显然的想法是把 $n,n-1,n-2,\dots,1$ 的邻边依次变为 $0$，当然这是做不到的。不过可以从 $n$ 做到 $5$。

具体地，设当前枚举的点为 $x$，取出 $1,2,3,4$ 放着作为工具点，对于 $y>4$，显然可以做一次 $(x,1,2,y,-w_{x,y})$ 操作把边 $(x,y)$ 变成 $0$。

最后剩下 $4$ 个点，怎么办？

---

给出第一个操作组：选定四个点 $a,b,c,d$，满足 $w_{a,b}$ 为偶数，将 $(a,b)$ 的权值全部转移至 $(c,d)$，不影响其余任何边。

操作：记初始 $a,b$ 的边权为 $w$，进行 $(c,a,b,d,\frac{w}{2}),(d,a,b,c,\frac{w}{2})$。

可以画图发现这是对的。

---

所以如果 $(x,i)$（$i=1,2,3,4$）的边权是偶数，那么可以轻易地把它转移走。如果有奇数怎么办？

如果只看奇偶性的话，进行一次 $(a,b,c,d,1)$ 实际上就是把六条边的边权的奇偶性都改变一次。对应到这个情境中，就是可以选择三个点，把 $(x,a),(x,b),(x,c)$ 的边权奇偶性改变。

也就是：有 $4$ 个取值 $0/1$ 的数，每次把其中 $3$ 个反转，要求全部变成 $0$。

无论如何都可以做到。下面不带编号地给出做法：

- $4$ 个 $1$：$\{1,1,1,1\}\rightarrow\{1,0,0,0\}\rightarrow\{0,1,1,0\}\rightarrow\{1,0,1,1\}\rightarrow\{0,0,0,0\}$。
- $3$ 个 $1$：$\{1,1,1,0\}\rightarrow\{0,0,0,0\}$。
- $2$ 个 $1$：$\{1,1,0,0\}\rightarrow\{1,0,1,1\}\rightarrow\{0,0,0,0\}$。
- $1$ 个 $1$：$\{1,0,0,0\}\rightarrow\{0,1,1,0\}\rightarrow\{1,0,1,1\}\rightarrow\{0,0,0,0\}$。
- $0$ 个 $1$：不用操作。

所以一定可以把 $(x,1),(x,2),(x,3),(x,4)$ 的边权都变成偶数，最后再全部转移走即可。

## Part 2
现在问题变成了一个 $4$ 个点的完全图，首先可以手玩一下 $n=4$ 何时有解。

首先边权和必定要为 $0$，因为操作不改变边权和。

其次，$n=4$ 时只有 $4$ 种本质不同的操作，即 $a=1,2,3,4$ 时的操作，可以记操作的总权值为 $x_1,x_2,x_3,x_4$。则有方程：

$$\begin{cases}
x_1+x_2-x_3-x_4=-w_{1,2}\\
x_1-x_2+x_3-x_4=-w_{1,3}\\
x_1-x_2-x_3+x_4=-w_{1,4}\\
-x_1+x_2+x_3-x_4=-w_{2,3}\\
-x_1+x_2-x_3+x_4=-w_{2,4}\\
-x_1-x_2+x_3+x_4=-w_{3,4}\\
\end{cases}$$

所以可以得出结论：

$$w_{1,2}+w_{3,4}=w_{1,3}+w_{2,4}=w_{1,4}+w_{2,3}=0$$

这是另一个必要条件。

然后，进行加减消元，可以得出：

$$2(x_1-x_4)=-(w_{1,2}+w_{1,3})$$

$$2(x_2-x_4)=-(w_{1,2}+w_{2,3})$$

$$2(x_3-x_4)=-(w_{1,3}+w_{2,3})$$

所以右边三项都得是偶数，这是第三个必要条件。

都满足后，令 $x_4=0$，就可以得出 $x_1,x_2,x_3$，直接做就行。

## Part 3
你要是认为这就做完了就大错特错了（这么认为的我就是大奶龙）。

以上只是 $n=4$ 的情况，而非剩下 $4$ 个点的情况。比方说，$n=5$ 时，可以做到 $n=4$ 做不到的操作。

我们已经知道了第一个操作组——对偶数边权的转移。所以给出结论：当且仅当剩下的 $6$ 条边权奇偶性相同，且和为 $0$ 时有解。

必要性证明略。充分性证明：如果权值都是奇数就先做一次 $(1,2,3,4,1)$ 变成偶数。然后通过和 $5$ 相邻的 $4$ 条边，把所有边权转移到同一条边上即可。

## Part 4
然而还没有完。$n=5$ 时不能接受奇数边权，然而 $n\ge 6$ 时是可以的。

---

给出第二个操作组：令 $\{a,b,c,d\}=\{1,2,3,4\}$，将 $(a,d)$ 的边权减 $1$，$(5,6)$ 的边权加 $1$，不影响其余任何边。

操作：先操作 $(5,a,b,c,1),(d,b,c,5,1)$，可以发现这样 $(5,a),(5,d),(a,b),(a,c),(b,c),(c,d)$ 的边权分别增加 $1$；然后操作 $(6,a,b,c,-1),(d,b,c,6,-1)$，这样 $(6,a),(6,d),(a,b),(a,c),(b,c),(c,d)$ 的边权分别减少 $1$，总体来看只有 $(5,a),(5,d),(6,a),(6,d)$ 边权改变。最后操作 $(6,5,a,d)$，即可将 $(5,6)$ 加 $1$，$(a,d)$ 减 $1$，并将其余边权恢复。

画个图更容易理解。

---

所以，先判定边权和为 $0$，然后直接找出边权为奇数的边，把它们的边权转移 $1$ 到 $(5,6)$，最后将 $(5,6)$ 的边权（可以证明一定是个偶数）转移到某条边上，之后和 $n=5$ 的一样。

## 总结
把 $G$ 的边权减去 $H$，先把除 $1,2,3,4$ 之间的边以外的边全部变成 $0$，然后分为 $n=4$、$n=5$ 和 $n\ge 6$ 分类讨论即可。

分析以下，除了一开始把其他边变成 $0$ 花费了 $O(n^2)$ 次操作外，剩余都是常数级别的，完全可以通过。实测本题数据每个点不超过 $11000$ 次。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

int G[maxn][maxn], H[maxn][maxn];
int ans[maxn * maxn * maxn][5], cnt = 0;

void operateG(int a, int b, int c, int d, int w){
    cnt ++, ans[cnt][0] = a, ans[cnt][1] = b, ans[cnt][2] = c, ans[cnt][3] = d, ans[cnt][4] = w;
    G[a][b] += w, G[b][a] += w, G[a][c] += w, G[c][a] += w, G[a][d] += w, G[d][a] += w;
    G[b][c] -= w, G[c][b] -= w, G[c][d] -= w, G[d][c] -= w, G[b][d] -= w, G[d][b] -= w;
}
void solve_even(){
    operateG(3, 1, 2, 4, G[1][2] / 2), operateG(4, 1, 2, 3, G[1][2]);
    operateG(4, 1, 2, 3, G[1][3] / 2), operateG(2, 1, 3, 4, G[1][3]);
    operateG(2, 1, 3, 4, G[1][4] / 2), operateG(3, 1, 2, 4, G[1][4]);

    operateG(1, 2, 3, 5, G[2][3] / 2), operateG(5, 1, 2, 3, G[2][3]);
    operateG(1, 3, 4, 5, G[3][4] / 2), operateG(5, 1, 3, 4, G[3][4]);
    operateG(2, 1, 4, 5, G[1][5] / 2), operateG(4, 1, 2, 5, G[1][5]);
}
void swap_one(int a, int b, int c, int d){
    operateG(5, a, b, c, 1), operateG(d, b, c, 5, 1);
    operateG(6, a, b, c, -1), operateG(d, b, c, 6, -1);
    operateG(6, 5, a, d, 1);
}

int main(){
    int n;
    scanf("%d", &n); 
    for(int i = 1; i <= n; i ++){
        for(int j = i + 1; j <= n; j ++){
            scanf("%d", &G[i][j]);
            G[j][i] = G[i][j];
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = i + 1; j <= n; j ++){
            scanf("%d", &H[i][j]);
            H[j][i] = H[i][j];
            G[i][j] -= H[i][j], G[j][i] -= H[j][i];
        }
    }
    for(int x = n; x >= 5; x --){
        for(int i = n; i >= 5; i --){
            if(i == x) continue;
            operateG(x, 1, 2, i, -G[x][i]);
        }
        int a = G[x][1] & 1, b = G[x][2] & 1, c = G[x][3] & 1, d = G[x][4] & 1;
        if(a + b + c + d == 4){
            operateG(x, 1, 2, 3, 1);
            operateG(x, 1, 2, 4, 1);
            operateG(x, 1, 3, 4, 1);
            operateG(x, 2, 3, 4, 1);
        }else if(a + b + c + d == 3){
            if(!a) operateG(x, 2, 3, 4, 1);
            else if(!b) operateG(x, 1, 3, 4, 1);
            else if(!c) operateG(x, 1, 2, 4, 1);
            else operateG(x, 1, 2, 3, 1);
        }else if(a + b + c + d == 2){
            if(a && b) operateG(x, 2, 3, 4, 1), operateG(x, 1, 3, 4, 1);
            else if(a && c) operateG(x, 2, 3, 4, 1), operateG(x, 1, 2, 4, 1);
            else if(a && d) operateG(x, 2, 3, 4, 1), operateG(x, 1, 2, 3, 1);
            else if(b && c) operateG(x, 1, 2, 4, 1), operateG(x, 1, 3, 4, 1);
            else if(b && d) operateG(x, 1, 2, 3, 1), operateG(x, 1, 3, 4, 1);
            else operateG(x, 1, 2, 3, 1), operateG(x, 1, 2, 4, 1);
        }else if(a + b + c + d == 1){
            if(a) operateG(x, 1, 2, 3, 1), operateG(x, 1, 2, 4, 1), operateG(x, 1, 3, 4, 1);
            else if(b) operateG(x, 1, 2, 3, 1), operateG(x, 1, 2, 4, 1), operateG(x, 2, 3, 4, 1);
            else if(c) operateG(x, 1, 2, 3, 1), operateG(x, 1, 3, 4, 1), operateG(x, 2, 3, 4, 1);
            else operateG(x, 1, 2, 4, 1), operateG(x, 1, 3, 4, 1), operateG(x, 2, 3, 4, 1);
        }
        a = -G[x][1] / 2, b = -G[x][2] / 2, c = -G[x][3] / 2, d = -G[x][4] / 2;
        operateG(x, 1, 2, 3, a), operateG(1, x, 2, 3, a);
        operateG(x, 2, 1, 3, b), operateG(2, x, 1, 3, b);
        operateG(x, 3, 1, 2, c), operateG(3, x, 1, 2, c);
        operateG(x, 4, 1, 2, d), operateG(4, x, 1, 2, d);
    }
    int w12 = -G[1][2], w13 = -G[1][3], w14 = -G[1][4], w23 = -G[2][3], w24 = -G[2][4], w34 = -G[3][4];
    if(n == 4){
        if(w12 + w34 != 0 || w13 + w24 != 0 || w14 + w23 != 0){
            printf("-1\n");
            return 0;
        }
        if(((w12 + w13) & 1) || ((w12 + w23) & 1) || ((w13 + w23) & 1)){
            printf("-1\n");
            return 0;
        }
        int x1 = (w12 + w13) / 2, x2 = (w12 + w23) / 2, x3 = (w13 + w23) / 2;
        operateG(1, 2, 3, 4, x1), operateG(2, 1, 3, 4, x2), operateG(3, 1, 2, 4, x3);
    }else if(n == 5){
        int sum = (w12 & 1) + (w13 & 1) + (w14 & 1) + (w23 & 1) + (w24 & 1) + (w34 & 1);
        if((sum != 0 && sum != 6) || (w12 + w13 + w14 + w23 + w24 + w34 != 0)){
            printf("-1\n");
            return 0;
        }
        if(sum == 6) operateG(1, 2, 3, 4, 1);
        solve_even();
    }else{
        if(w12 + w13 + w14 + w23 + w24 + w34 != 0){
            printf("-1\n");
            return 0;
        }
        if(G[1][2] & 1) swap_one(1, 3, 4, 2);
        if(G[1][3] & 1) swap_one(1, 2, 4, 3);
        if(G[1][4] & 1) swap_one(1, 2, 3, 4);
        if(G[2][3] & 1) swap_one(2, 1, 4, 3);
        if(G[2][4] & 1) swap_one(2, 1, 3, 4);
        if(G[3][4] & 1) swap_one(3, 1, 2, 4);
        operateG(1, 2, 5, 6, G[5][6] / 2), operateG(2, 1, 5, 6, G[5][6]);
        solve_even();
    }
    printf("%d\n", cnt);
    for(int i = 1; i <= cnt; i ++) printf("%d %d %d %d %d\n", ans[i][0], ans[i][1], ans[i][2], ans[i][3], ans[i][4]);
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

将两张图边权做个差，转化为将边权清 $0$。

显然有必要条件所有边边权和为 $0$。

先考虑 $n=4$ 的情况。这时候假设四个点作为 $a$ 被选择了 $u_{1,2,3,4}$ 次。

那么边 $(i,j)$ 获得的总代价为：$2u_i + 2u_j - u_1 + u_2 + u_3 + u_4$，设为 $w_{i,j}$。

显然如果  $\{i,j,k,t\}= \{1,2,3,4\}$，则 $w_{i,j} + w_{k,t}=0$。

如果满足这种“对称”结构，考虑解方程。

比如：$u_1 + u_2 - u_3 - u_4=x$，$u_1 + u_3 - u_2 - u_4 = y$，$u_1+u_4 - u_2 - u_3 = z$。

则 $u_2 + u_3 + u_4 = 3 u_1 - x - y - z$，$u_2 = u_1 - \frac{y+z}{2}$，$u_3 = u_1 - \frac{x+z}{2}$，$u_4 = u_1 - \frac{x+y}{2}$。

我们对 $u$ 的限制只有 $u \in \mathbb Z$，所以需要三个数模 $2$ 相同。

这是 $n=4$ 有解的充要条件：三个位置奇偶相同，且不相邻的边边权互为相反数。

------

上面的分析是从点数特例入手，接下来我们从边权特例入手——如果边权 $\in\{0,1\}$，且你的操作是选择一个 $K_4$ 将内部所有边异或 $1$，问能否变为 $0$。

对于 $n\le 5$，可以直接 $O(1)$ 或 $O(2^n)$ 判。

考虑选 $5$ 个点，进行若干次操作，会得到下面的结果（有连边表示异或了一次）

![](https://s21.ax1x.com/2025/02/07/pEmewcR.png)

一共用了 $5$ 次操作。

因此当 $n \ge 6$，我们要删除一对边：

1. 如果他们相邻，找一条与他们都不相邻的边，消除，用 $10$ 次操作。
2. 如果他们不相邻，直接做，用 $5$ 次操作。

这一步一共进行 $10\frac{m}{2} \le 2.5 n^2$ 次。

------

根据上面的讨论，我们可以把图上所有边权都变为偶数。

显然我们可以执行这种操作——选择两条不相邻的边，使得他们同时加减一个数。注意所有操作的本质都是它。

这样可以在 $\dbinom{n}{2} \times 8 \le 4n^2$ 次操作内解决问题。（单次操作需要 $4$ 次基本操作，如果要传递到相邻边上去就要进行 $2$ 轮。但是这已经足够了。）

总次数为 $6.5 n^2$，完全足够。

代码有点长。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
int n,w[MAXN][MAXN],m[MAXN][MAXN];
struct OP {int a,b,c,d,w;};
OP operator +(OP x,int id) {
	if(x.a==-1)	return x.a=id,x;
	if(x.b==-1)	return x.b=id,x;
	if(x.c==-1)	return x.c=id,x;
	if(x.d==-1)	return x.d=id,x;
}
vector<OP> res;
void Del1(int a,int b,int c,int d) {
	int x=-1,y=-1;
	ffor(i,1,n) if(i!=a&&i!=b&&i!=c&&i!=d) {
		if(x==-1) x=i;
		else if(y==-1) y=i;
		else break ;
	}
	res.push_back({a,x,y,c,1}),res.push_back({b,x,y,c,1});
	res.push_back({a,x,y,d,1}),res.push_back({b,x,y,d,1});
	res.push_back({a,b,c,d,1});
	return ;
}
void del1(int a,int b,int c,int d) {
	if(a!=c&&a!=d&&b!=c&&b!=d) return Del1(a,b,c,d),void();
	int x=-1,y=-1;
	ffor(i,1,n) if(i!=a&&i!=b&&i!=c&&i!=d) {
		if(x==-1) x=i;
		else if(y==-1) y=i;
		else break ;
	}
	Del1(a,b,x,y),Del1(c,d,x,y);
	return ;
}
void operate(int a,int b,int c,int d,int w) {
	res.push_back({c,a,b,d,-w/2});
	res.push_back({d,a,b,c,-w/2});
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) ffor(j,i+1,n) cin>>w[i][j];
	ffor(i,1,n) ffor(j,i+1,n) {int nw;cin>>nw,w[i][j]=w[i][j]-nw;}
	ffor(i,1,n) ffor(j,i+1,n) m[i][j]=!(w[i][j]%2==0);
	int sum=0;
	ffor(i,1,n) ffor(j,i+1,n) sum+=w[i][j];
	if(sum) return cout<<-1,0;
	if(n<=4) {
		if(w[1][2]+w[3][4]!=0) return cout<<-1,0;
		if(w[1][3]+w[2][4]!=0) return cout<<-1,0;
		if(w[1][4]+w[2][3]!=0) return cout<<-1,0;
		if(m[1][2]!=m[1][3]||m[1][3]!=m[1][4]) return cout<<-1,0;
		cout<<3<<'\n';
		cout<<2<<' '<<1<<' '<<3<<' '<<4<<' '<<(w[1][3]+w[1][4])/2<<'\n';
		cout<<3<<' '<<1<<' '<<2<<' '<<4<<' '<<(w[1][2]+w[1][4])/2<<'\n';
		cout<<4<<' '<<1<<' '<<2<<' '<<3<<' '<<(w[1][2]+w[1][3])/2<<'\n';
		return 0;
	}
	if(n==5) {
		int flg=-1;
		ffor(i,0,31) {
			int ot=0,psl=0;
			ffor(j,1,5) if(i&(1<<j-1)) ot^=1;
			ffor(j,1,5) ffor(k,j+1,5) {
				int w=(!!(i&(1<<j-1)))^(!!(i&(1<<k-1)))^ot;
				if(m[j][k]!=w) {psl=1;break ;}
			}
			if(psl) continue ;
			flg=i;break ;
		}
		if(flg==-1) return cout<<-1,0;
		ffor(i,1,5) if(flg&(1<<i-1)) {
			int mn=-1;
			ffor(x,1,5) if(x!=i) {mn=x;break ;}
			OP ins={-1,-1,-1,-1,1};
			ins=ins+mn;
			ffor(x,1,5) if(x!=i&&x!=mn) ins=ins+x;
			res.push_back(ins);
		}
	}
	else {
		vector<pair<int,int>> sg;
		ffor(i,1,n) ffor(j,i+1,n) if(m[i][j]) sg.push_back({i,j});
		ffor(i,0,(int)sg.size()/2-1) del1(sg[2*i].first,sg[i*2].second,sg[2*i+1].first,sg[2*i+1].second);
	}
	for(auto op:res) {
		int a=op.a,b=op.b,c=op.c,d=op.d;
		vector<int> pos;
		pos.push_back(a),pos.push_back(b),pos.push_back(c),pos.push_back(d);
		for(auto i:pos) for(auto j:pos) if(i<j) {
			if(i==a||j==a) w[i][j]++;
			else w[i][j]--;	
		}
	}
	ffor(i,1,n) ffor(j,i+1,n) if(i!=1||j!=2) {
		if(i!=1&&j!=1&&i!=2&&j!=2) operate(i,j,1,2,-w[i][j]);	
		else {
			int x=-1,y=-1;
			ffor(k,3,n) if(k!=i&&k!=j) {
				if(x==-1) x=k;
				else if(y==-1) y=k;
				else break; 
			}
			operate(i,j,x,y,-w[i][j]);
			operate(x,y,1,2,-w[i][j]);
		}
	}
	cout<<res.size()<<'\n';
	for(auto op:res) cout<<op.a<<' '<<op.b<<' '<<op.c<<' '<<op.d<<' '<<op.w<<'\n';
	return 0;
}
```

---

## 作者：NianFeng (赞：0)

感觉挺有分析难度的，在草稿本上推构造推了七八页的样子。

# 0x01 题目分析

## 题意

给了你俩完全图，用不超过 $10^5$ 次以下操作使第一张图变成第二张图：

> 选择互不相同的点 $a,b,c,d$ 和一个数 $x$，$(a,b),(a,c),(a,d)$ 加上 $x$，$(b,c),(c,d),(b,d)$ 减去 $x$。

或者判断无解。

## 思路

首先，把一张图变成另一张图是很不显然的。直接构造一个图为第二张图减去第一张图，这样问题就变成如何操作出目标图。其次，题目的操作看起来相当复杂，说人话就是把一个鸡爪加上 $x$，剩下的三角形减去 $x$。用红边表示减去，白边表示加上，一次操作效果如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2w7ftrtc.png)

容易发现，每做一次操作总和是不变的，那么一种无解情况就很好判断。求出新图边权和，非零则一定不能成功操作。

显然，下一步就是对操作进行转化了。这个“鸡爪式转化”一次关联了 $6$ 条边，相当难受，不过注意到它并不是对称的，那么就可以简单地取两次分别为 $a,b,c,d,x$ 和 $c,a,b,d,x$，如下图，这样就可以把 $6$ 条边换成 $2$ 条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/yhn645ar.png)

很有道理对吧？~~实际上一点用都没有。~~

会发现这种构造限制很大：第一，它让增加的权值必须为偶数；第二，还要求两个边不相邻，至少这两点就很不好处理。由此观之，我们需要构造的新操作除了减边之外，还要保证相对自由，可拓展性好。

四个点肯定玩不出花来了，考虑多加一个点如何。经过漫长手模（也可以 $O(2^{10})$ 枚举？），我们可以得到这么一个东西：对于点 $a,b,c,d,e,x$，进行 $4$ 次操作 $\{d,a,b,e,-x\}$，$\{d,a,b,c,x\}$，$\{e,a,c,d,x\}$，$\{e,a,b,c,-x\}$，那么结果是从 $a$ 出发连了 $4$ 条正负交错的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/oapxjewt.png)

$4$ 条边，看起来是非常不优的，但是这个东西满足两条好的性质：所有边连在一个点上，以及边权可以随意取。为什么这么说呢？我们考虑另一个点 $f$，在上图的基础上用同样的操作处理 $a,b,c,d,f,-x$，结果如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zzakw0rc.png)

这样一来我们就可以把 $(a,e)$ 上的边权转到 $(a,f)$ 上了。

不过这还有个问题，一次这种操作需要 $5$ 个点，转移一条边则需要 $6$ 个点，怎么办呢？很简单，分类讨论。

# 0x02 分类讨论

## Part1: $n=4$

发现上述构造在这里一点用都没有。难不成要用上那个限制很大玩意儿？当然不是。注意到 ~~（注意力惊人）~~ 这种条件下本质不同的操作一共 $4$ 个，边数也只有区区 $6$ 条，那么以四个操作的 $x$ 为未知数，对每一条边建立方程，高斯消元即可。

```cpp
bool GJ(){  //高消板子
    for(int i=1;i<=4;i++){
        int tmp=i;
        for(int j=i;j<=6;j++)
            if(b[j][i]){
                tmp=j;
                break;
            }
        if(tmp!=i)
            swap(b[tmp],b[i]);
        if(!b[i][i]) continue;
        for(int k=1;k<=6;k++){
            if(k==i) continue;
            for(int j=5;j>=i;j--)
                b[k][j]-=b[k][i]*b[i][j]/b[i][i];
        }
    }
    if(b[5][5]||b[6][5])
        return false;
    for(int i=1;i<=4;i++)
        if(!b[i][i]&&b[i][5])
            return false;
        else if(b[i][i])
            b[i][5]/=b[i][i];
    return true;
}

//构造方程系数
b[1][1]=b[1][2]=1,b[1][3]=b[1][4]=-1,b[1][5]=a[1][2];
b[2][1]=b[2][3]=1,b[2][2]=b[2][4]=-1,b[2][5]=a[1][3];
b[3][1]=b[3][4]=1,b[3][2]=b[3][3]=-1,b[3][5]=a[1][4];
b[4][2]=b[4][3]=1,b[4][1]=b[4][4]=-1,b[4][5]=a[2][3];
b[5][2]=b[5][4]=1,b[5][1]=b[5][3]=-1,b[5][5]=a[2][4];
b[6][3]=b[6][4]=1,b[6][1]=b[6][2]=-1,b[6][5]=a[3][4];
//判无解，否则直接输出
if(!GJ()) return print("-1\n"),0;
print("4\n");
print("1 2 3 4 ",b[1][5],'\n');
print("2 1 3 4 ",b[2][5],'\n');
print("3 1 2 4 ",b[3][5],'\n');
print("4 1 2 3 ",b[4][5],'\n');
```

## Part2: $n\ge6$

$n=5$ 还是有点恶心，放下一个说。事实上，有了之前 $6$ 个点就能完成的转移，$n\ge6$ 的情况就很好处理。我们直接枚举每一条边，把它的权值变成 $0$，多出来的权值往下一个放（或者不处理）。这个有点类似均分纸牌？不难证明在和为 $0$ 的情况下一定有解。细节方面，注意一下把边对称复制一遍应该就没了。

```cpp
struct Answer{  //方便处理
    int a,b,c,d,x;
    void out(){
        print(a,' ',b,' ',c,' ',d,' ',x,'\n');
    }
};
vector<Answer>ans;
tp3 mex(int i,int j,int k){
    //暴力找辅助点，不缺这点时间
    //思路中的a,b,c,d,e,f对应i,x,y,z,j,k（好像是的
    int x=1,y=1,z=1;
    while(x==i||x==j||x==k) x++;
    while(y==i||y==j||y==k||y==x) y++;
    while(z==i||z==j||z==k||z==x||z==y) z++;
    return make_tuple(x,y,z);
}

//原图对称处理一下
for(int i=2;i<=n;i++)
    for(int j=1;j<i;j++)
        a[i][j]=a[j][i];
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(i==j||!a[i][j])
            continue;
        int k=j+1==i?i+1:j+1;   //找下一条转出边
        if(k>n) continue;       //找不到没关系，最后统一会在n点处理
        auto [x,y,z]=mex(i,j,k);
        ans.push_back({x,i,y,j,-a[i][j]});
        ans.push_back({j,i,z,x,a[i][j]});
        ans.push_back({j,i,y,z,-a[i][j]});
        ans.push_back({x,i,y,k,a[i][j]});
        ans.push_back({k,i,z,x,-a[i][j]});
        ans.push_back({k,i,y,z,a[i][j]});
        //上面讲的构造正好有两个抵消，就没写了
        a[i][k]+=a[i][j];       //更新边权
        a[k][i]+=a[i][j];
        a[i][j]=a[j][i]=0;
    }
}
print(ans.size(),'\n');
for(auto it : ans)
    it.out();
```

## Part3: $n=5$

~~你不等于四比较松弛，但是不大于六又弥补了这一点。~~

发现直接转移变难了，考虑对原有构造做一定改变。把 $6$ 个点缩成 $5$ 个点依旧可以转移边权，不难构造出这种状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/tes75in0.png)

虽然也只能处理偶数，但总比最开始那个还限定不共点的要方便实现。那么要考虑的就是奇数边权了。在上面的讨论中，我们发现由于改变的边存在重合，构造出来的方案总是带个偶数。那么不妨让这些边不重合，返璞归真，想想最初的构造能带来什么。假定 $x$ 为一个奇数，平凡的，令其为 $1$，不难观察到一次操作可以把选到的 $6$ 条边奇偶性全部改变。因为现在只关心奇偶性而不关心具体边权，本质不同的操作次数降到了 $\binom n4=5$ 种。这还要构造吗？显然，上个爆搜，同时维护奇边数量，就~~不~~轻松地解决了。

```cpp
int nod[6][5]={
    {0,0,0,0,0},
    {0,2,3,4,5},
    {0,1,3,4,5},
    {0,1,2,4,5},
    {0,1,2,3,5},
    {0,1,2,3,4}
};  //预处理一下辅助点
#define t(_) nod[tmp][_]
void dfs(int tmp){
    if(!tot){   //没有奇边了
        for(int i=1;i<=5;i++){
            if(!use[i]) continue;
            ans.push_back({
                nod[i][1],
                nod[i][2],
                nod[i][3],
                nod[i][4],
            1});
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||!a[i][j])
                    continue;
                int k=j+1==i?i+1:j+1;
                if(k>n) continue;
                auto [x,y,z]=mex(i,j,k);
                //按照上面的构造就行，注意权值减半
                //（其实z在这里是没用的
                ans.push_back({x,i,y,j,-a[i][j]/2});
                ans.push_back({x,i,y,k,a[i][j]/2});
                ans.push_back({j,i,k,x,a[i][j]/2});
                ans.push_back({j,i,y,k,-a[i][j]/2});
                ans.push_back({y,i,x,j,-a[i][j]/2});
                ans.push_back({y,i,x,k,a[i][j]/2});
                ans.push_back({j,i,k,y,a[i][j]/2});
                ans.push_back({j,i,x,k,-a[i][j]/2});
                a[i][k]+=a[i][j];
                a[k][i]+=a[i][j];
                a[i][j]=a[j][i]=0;
            }
        }
        print(ans.size(),'\n');
        for(auto it : ans)
            it.out();
        exit(0);
    }
    if(tmp>5) return;
    dfs(tmp+1);     //不选
    use[tmp]=true;  //选，然后修改边权，（注意++和--的顺序
    for(int i=2;i<=4;i++){
        a[t(1)][t(i)]--;
        a[t(i)][t(1)]--;
        tot+=a[t(1)][t(i)]&1?1:-1;
    }
    for(int i=2;i<4;i++){
        for(int j=i+1;j<=4;j++){
            a[t(i)][t(j)]++;
            a[t(j)][t(i)]++;
            tot+=a[t(i)][t(j)]&1?1:-1;
        }
    }
    dfs(tmp+1);
    use[tmp]=false;
    for(int i=2;i<=4;i++){
        a[t(1)][t(i)]++;
        a[t(i)][t(1)]++;
        tot+=a[t(1)][t(i)]&1?1:-1;
    }
    for(int i=2;i<4;i++){
        for(int j=i+1;j<=4;j++){
            a[t(i)][t(j)]--;
            a[t(j)][t(i)]--;
            tot+=a[t(i)][t(j)]&1?1:-1;
        }
    }
}

//由于涉及边权转移，也要对称处理
for(int i=2;i<=n;i++)
    for(int j=1;j<i;j++){
        a[i][j]=a[j][i];
        tot+=a[i][j]&1;     //记录奇边数
    }
dfs(1),print("-1\n");
```

# 0x03 总代码

~~由于更新的码风有点抽象，快读部分就不放了 qwq。~~

```cpp
#include <cstdio>
#include <string>
#include <vector>
#include <tuple>
#define tp3 tuple<int,int,int>
using namespace std;
const int N=105;
int n,a[N][N];
int b[10][10];
int sum,tot;
bool use[6];
int nod[6][5]={
    {0,0,0,0,0},
    {0,2,3,4,5},
    {0,1,3,4,5},
    {0,1,2,4,5},
    {0,1,2,3,5},
    {0,1,2,3,4}
};
struct Answer{
    int a,b,c,d,x;
    void out(){
        print(a,' ',b,' ',c,' ',d,' ',x,'\n');
    }
};
vector<Answer>ans;
bool GJ(){
    for(int i=1;i<=4;i++){
        int tmp=i;
        for(int j=i;j<=6;j++)
            if(b[j][i]){
                tmp=j;
                break;
            }
        if(tmp!=i)
            swap(b[tmp],b[i]);
        if(!b[i][i]) continue;
        for(int k=1;k<=6;k++){
            if(k==i) continue;
            for(int j=5;j>=i;j--)
                b[k][j]-=b[k][i]*b[i][j]/b[i][i];
        }
    }
    if(b[5][5]||b[6][5])
        return false;
    for(int i=1;i<=4;i++)
        if(!b[i][i]&&b[i][5])
            return false;
        else if(b[i][i])
            b[i][5]/=b[i][i];
    return true;
}
tp3 mex(int i,int j,int k){
    int x=1,y=1,z=1;
    while(x==i||x==j||x==k) x++;
    while(y==i||y==j||y==k||y==x) y++;
    while(z==i||z==j||z==k||z==x||z==y) z++;
    return make_tuple(x,y,z);
}
#define t(_) nod[tmp][_]
void dfs(int tmp){
    if(!tot){
        for(int i=1;i<=5;i++){
            if(!use[i]) continue;
            ans.push_back({
                nod[i][1],
                nod[i][2],
                nod[i][3],
                nod[i][4],
            1});
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||!a[i][j])
                    continue;
                int k=j+1==i?i+1:j+1;
                if(k>n) continue;
                auto [x,y,z]=mex(i,j,k);
                ans.push_back({x,i,y,j,-a[i][j]/2});
                ans.push_back({x,i,y,k,a[i][j]/2});
                ans.push_back({j,i,k,x,a[i][j]/2});
                ans.push_back({j,i,y,k,-a[i][j]/2});
                ans.push_back({y,i,x,j,-a[i][j]/2});
                ans.push_back({y,i,x,k,a[i][j]/2});
                ans.push_back({j,i,k,y,a[i][j]/2});
                ans.push_back({j,i,x,k,-a[i][j]/2});
                a[i][k]+=a[i][j];
                a[k][i]+=a[i][j];
                a[i][j]=a[j][i]=0;
            }
        }
        print(ans.size(),'\n');
        for(auto it : ans)
            it.out();
        exit(0);
    }
    if(tmp>5) return;
    dfs(tmp+1);
    use[tmp]=true;
    for(int i=2;i<=4;i++){
        a[t(1)][t(i)]--;
        a[t(i)][t(1)]--;
        tot+=a[t(1)][t(i)]&1?1:-1;
    }
    for(int i=2;i<4;i++){
        for(int j=i+1;j<=4;j++){
            a[t(i)][t(j)]++;
            a[t(j)][t(i)]++;
            tot+=a[t(i)][t(j)]&1?1:-1;
        }
    }
    dfs(tmp+1);
    use[tmp]=false;
    for(int i=2;i<=4;i++){
        a[t(1)][t(i)]++;
        a[t(i)][t(1)]++;
        tot+=a[t(1)][t(i)]&1?1:-1;
    }
    for(int i=2;i<4;i++){
        for(int j=i+1;j<=4;j++){
            a[t(i)][t(j)]--;
            a[t(j)][t(i)]--;
            tot+=a[t(i)][t(j)]&1?1:-1;
        }
    }
}
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            read(a[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int x; read(x);
            a[i][j]=x-a[i][j];
            sum+=a[i][j];
        }
    }
    if(sum)
        return print("-1\n"),0;
    if(n==4){
        b[1][1]=b[1][2]=1,b[1][3]=b[1][4]=-1,b[1][5]=a[1][2];
        b[2][1]=b[2][3]=1,b[2][2]=b[2][4]=-1,b[2][5]=a[1][3];
        b[3][1]=b[3][4]=1,b[3][2]=b[3][3]=-1,b[3][5]=a[1][4];
        b[4][2]=b[4][3]=1,b[4][1]=b[4][4]=-1,b[4][5]=a[2][3];
        b[5][2]=b[5][4]=1,b[5][1]=b[5][3]=-1,b[5][5]=a[2][4];
        b[6][3]=b[6][4]=1,b[6][1]=b[6][2]=-1,b[6][5]=a[3][4];
        if(!GJ()) return print("-1\n"),0;
        print("4\n");
        print("1 2 3 4 ",b[1][5],'\n');
        print("2 1 3 4 ",b[2][5],'\n');
        print("3 1 2 4 ",b[3][5],'\n');
        print("4 1 2 3 ",b[4][5],'\n');
    } else if(n==5){
        for(int i=2;i<=n;i++)
            for(int j=1;j<i;j++){
                a[i][j]=a[j][i];
                tot+=a[i][j]&1;
            }
        dfs(1),print("-1\n");
    } else{
        for(int i=2;i<=n;i++)
            for(int j=1;j<i;j++)
                a[i][j]=a[j][i];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||!a[i][j])
                    continue;
                int k=j+1==i?i+1:j+1;
                if(k>n) continue;
                auto [x,y,z]=mex(i,j,k);
                ans.push_back({x,i,y,j,-a[i][j]});
                ans.push_back({j,i,z,x,a[i][j]});
                ans.push_back({j,i,y,z,-a[i][j]});
                ans.push_back({x,i,y,k,a[i][j]});
                ans.push_back({k,i,z,x,-a[i][j]});
                ans.push_back({k,i,y,z,a[i][j]});
                a[i][k]+=a[i][j];
                a[k][i]+=a[i][j];
                a[i][j]=a[j][i]=0;
            }
        }
        print(ans.size(),'\n');
        for(auto it : ans)
            it.out();
    }
    return 0;
}
```

# 0x4f 总结与后话

感觉自己做构造题还是比较菜，需要多练。操作构造题中心思想大部分是将操作重组以达到化简的目的，或者分析结果特殊性质反推过程，挺妙的。

感谢您的观看，有错误/不足之处欢迎指出！(>w<)

---

## 作者：_Flowey_ (赞：0)

### 题意：

给定两个无向的完全图 $G$ 和 $H$，图上的每条边都有边权，用以下操作将 $G$ 变得和 $H$ 完全一致：

- 选择图 $G$ 的四个点 $a,b,c,d$ 和一个整数 $x$，让边 $(a,b)(a,c)(a,d)$ 的权值增加 $x$，边 $(b,c)(c,d)(b,d)$ 的权值减少 $x$。

要求操作次数小于等于 $10^5$。

### 分析：

发现操作后边权和不变，所以两图边权和不同就无解。

如果我们通过选择不同的点和相同的整数进行操作，并 **最终使得某条边增加，另一条边减少**，这道题大概率就做完了，因为这样我们就可以让每条边和对应的边相等。大概 $5000$ 条边，意思是对于每条边我们可以操作 $20$ 次左右，非常宽松。

### 推导：

下面有图（图丑勿喷）。

我们用红色的边表示边权减少，黑色的边表示边权增加，黄色的数字代表需要的操作次数，蓝色的数字代表需要的点数。

首先要确定的是达到目标要用的点数。

从 $4$ 个点开始，我们可以从基本操作中推出两个简单形式。

启示着我们可以用 $5$ 个点推出一个更简单的形式。

接下来我们继续尝试 $4$ 个点和 $5$ 个点的情况，发现还有一种形式比较简洁，剩下的都很乱。

启示着我们可以用 $6$ 个点推出一个更简单的形式。

对于新的操作，考虑和旧的操作搭配食用。

![](https://cdn.luogu.com.cn/upload/image_hosting/8vasuyeu.png)

### 解题：

首先判无解。

对于 $n \ge 6$ 的情况，我们可以通过使用 $6$ 个点和 $10$ 次操作达到目标，在 $20$ 次内，所以一定有解（甚至超额完成，因为这两条边连接在一起，形式简单）。

对于 $n=5$ 的情况，我们可以通过使用 $5$ 个点，$4$ 次操作，将边权差为偶数的边消去，只剩下了奇数的边。重新考虑一下这种特殊局面下的发生的变化：

- 我们只用考虑边的奇偶性（即边权只有 $0$ 和 $1$）。

- 使 $x$ 为奇数，操作将变为 让所选的 $4$ 个点之间的 $6$ 条边进行取反。

所以我们可以 $O(2^{C_{n}^{4}}) $ 的枚举，由于 $ n=5$，我们只枚举 $2^5$ 次。

对于 $n=4$ 的情况，解方程即可。

---

