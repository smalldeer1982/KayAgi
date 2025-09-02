# Cursed Game

## 题目描述

You found an antique box in your warehouse and decided to open it. The moment you open the box, it traps you into a cursed game where you are playing against a demon. The game consists of $ 333 $ rounds and you have to win all rounds in order to escape. The demon also gives you $ 999 $ coins that you can use throughout all rounds.

Note that in this problem, denote cell $ (r, c) $ of a grid as the cell in row $ r $ and column $ c $ of the grid.

Before the start of each round, the demon will prepare a secret paper, which can be represented as a grid with $ 3 $ rows and $ 3 $ columns, both numbered from $ 1 $ to $ 3 $ . The demon will secretly put a hole in one or more cells, and you are not aware which cells have a hole in it. Then, the round starts with the demon giving you an odd integer $ N $ ( $ 3 \leq N \leq 33 $ ).

Within each round, you can ask the demon several queries, each costing you one coin. For each query, you are allowed to give the demon your paper, which can be represented as a grid with $ N $ rows and $ N $ columns, both numbered from $ 1 $ to $ N $ . Each cell is coloured either black or white by you.

For each of your query, the demon will calculate a binary result grid with $ N - 2 $ rows and $ N - 2 $ columns, both numbered from $ 1 $ to $ N - 2 $ . The value on cell $ (r, c) $ of the result grid is filled as follows.

- The demon will put the secret paper on top of your paper such that the cell $ (r + i - 1, c + j - 1) $ of your paper aligns with the cell $ (i, j) $ of the secret paper, for $ 1 \leq i, j \leq 3 $ .
- The demon can only see the colour of the cell in your paper if the corresponding cell in the secret paper has a hole in it.
- The value on cell $ (r, c) $ of the result grid is $ 1 $ if there is an odd number of black cells that it can see through the holes, or $ 0 $ otherwise.

You win the round if the result grid consists of only the values $ 1 $ . Otherwise, the demon will give you the result grid as a feedback, and the round continues.

If you have spent all the coins and still did not win all the rounds, then you will be trapped forever. Escape the cursed game!

## 说明/提示

Sample Interaction #1

The following interaction only shows $ 2 $ rounds. The actual interaction stays until you win all $ 333 $ rounds or you run out of coins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906C/37c84dede82381a4f24254eee6774fc481cfcb99.png)Explanation for the sample interaction #1

For the first round, the following illustration shows how the demon finds the value in cell $ (1, 1) $ of the result grid for the first and second queries. The grey-colored square represents the secret paper, and the circles represent the holes. In the first query, there are $ 4 $ black cells that can be seen through the holes, therefore the value in cell $ (1, 1) $ of the result grid is $ 0 $ . In the second query, there are $ 5 $ black cells that can be seen through the holes, therefore the value in cell $ (1, 1) $ of the result grid is $ 1 $ . As the result grid consists of only 1, the first round ends.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906C/6f97bd68e5e86b9b407597d473edac9794aa20f9.png)For the second round, the following illustration shows how the demon find the value in cell $ (2, 1) $ of the result grid for the first query. Since there are $ 2 $ black cells that can be seen through the holes, the value in cell $ (2, 1) $ is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906C/77cc40cef2907cecd6b6e9d5a9f4895b61aca734.png)

# 题解

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1906C)

**题目大意**

> 交互器有一个 $3\times 3$ 的 01 矩阵 $a$，你每次可以询问一个 $n\times n$ 的矩阵 $b$，返回 $n-2\times n-2$ 矩阵 $c$ 满足 $c_{x,y}=\oplus_{i,j\in[1,3]}a_{i,j}\&b_{x+i-1,y+j-1}$。
>
> 你需要构造一个 $b$ 使得返回的 $c$ 是全 $1$ 矩阵，要求 $333$ 组数据的交互次数 $\le 999$。
>
> 数据范围：$n\le 33,2\nmid n$。

**思路分析**

首先如果 $n>3$，我们构造仅有 $b_{2,2}=1$ 的矩阵，那么 $c_{1\sim 3,1\sim 3}$ 就是行列反转的 $a$。

知道 $a$ 之后，我们用 $a$ 中最靠右下角的 $1$ 来调整每个 $c$ 即可，需要 $2$ 次询问。

如果 $n=3$，那么随机一个矩阵 $b$，得到的结果可以看做 $\{0,1\}$ 中的随机变量，那么直接随机，期望 $2$ 次询问得到结果。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int n,a[45][45],b[3][3];
string op;
void solve() {
	cin>>n;
	if(n==3) {
		while(true) {
			cout<<(rnd()&1)<<(rnd()&1)<<(rnd()&1)<<endl;
			cout<<(rnd()&1)<<(rnd()&1)<<(rnd()&1)<<endl;
			cout<<(rnd()&1)<<(rnd()&1)<<(rnd()&1)<<endl;
			cin>>op;
			if(op=="CORRECT") return ;
			int x; cin>>x;
		}
		return ;
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) cout<<(i==3&&j==3);
		cout<<endl;
	}
	cin>>op;
	if(op=="CORRECT") return ;
	for(int i=1;i<=n-2;++i) for(int j=1;j<=n-2;++j) {
		char w; cin>>w; a[i][j]=w-'0';
	}
	for(int i=1;i<=3;++i) for(int j=1;j<=3;++j) b[3-i][3-j]=a[i][j];
	memset(a,0,sizeof(a));
	int x=0,y=0;
	for(int i:{0,1,2}) for(int j:{0,1,2}) if(b[i][j]) x=i,y=j;
	for(int i=1;i<=n-2;++i) for(int j=1;j<=n-2;++j) {
		int val=0;
		for(int u:{0,1,2}) for(int v:{0,1,2}) val^=b[u][v]&a[i+u][j+v];
		if(!val) a[i+x][j+y]^=1;
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) cout<<a[i][j];
		cout<<endl;
	}
	cin>>op;
}
signed main() {
	int _=333;
	while(_--) solve();
	return 0;
}
```

---

## 作者：max0810 (赞：0)

## 题目大意

交互库有一个 $3\times 3$ 的 01 矩阵 $a$，每次询问一个 $n\times n$ 的 01 矩阵 $b$，交互库会返回一个 $(n-2)\times (n-2)$ 的 01 矩阵 $c$，满足：

$$c_{x,y} = \bigoplus\limits_{1 \le i,j \le 3} \left ( a_{i,j} \operatorname{AND} b_{x+i-1,y+j-1} \right ) $$

如果一次询问后 $c$ 矩阵内所有元素全都是 $1$，你就获胜了。否则，交互库会告诉你 $c$ 矩阵。**保证 $n$ 是奇数**。

## 题解

因为平均下来一组数据只有 $3$ 次询问，所以我们不能太依赖于交互库，考虑直接把 $a$ 求出，然后构造矩阵 $b$。

如何得到矩阵 $a$？可以在 $b$ 的某个位置填 $1$，这样就可以得到 $a$ 哪些位置为 $1$。

具体地，对于 $n\ge 5$，我们可以构造一个矩阵 $b$ 满足 $b_{3,3}=1$，其余位置为 $0$。那么得到的矩阵 $c$ 就有 $c_{i,j}=a_{3-i+1,3-j+1}=a_{4-i,4-j}$，这样就通过一次询问求出了 $a$。

然后需要根据 $a$ 来构造 $b$。我们找到最大的 $x,y$ 使得 $a_{x,y}=1$（满足 $a_{x,y}$ 的右下部分没有 $1$ 即可）。然后从左上到右下枚举 $b_{i,j}$，对于一个位置 $b_{i,j}$，若生成的 $c_{i,j}=0$，就将 $b_{i+x-1,j+y-1}$ 取反，就能使 $c_{i,j}=1$，且不会影响 $c_{i,j}$ 左上角的数。

因为不同的 $b_{i,j}$ 对应的 $b_{i+x-1,j+y-1}$ 肯定是不同的，所以这样子依次改下去，就能使整个 $b$ 符合条件。

对于 $n<5$，即 $n=3$ 时，返回值只有 $1$ 个数，不能得到很好的信息。所以可以考虑直接随机，因为只有 $0$ 和 $1$ 两种可能，所以随机的正确率为  $\frac 1 2$。

对于 $n \ge 5$ 的情况，共需要 $2$ 次询问。而 $n=3$ 时，期望用 $2$ 次询问，所以 $999$ 次询问时绰绰有余的。

## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <random>
#define ll long long
using namespace std;
const int N = 40;
int a[4][4],b[N][N],c[N][N],n;
mt19937 rnd(114514);
bool pri()
{
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)cout << b[i][j];
        cout << endl;
    }
    string s;cin >> s;
    return s[0]=='C';
}
int get(int i,int j)
{
    bool sum = 0;
    for(int x = 1;x <= 3;x++)for(int y = 1;y <= 3;y++)
        sum ^= a[x][y]&b[i+x-1][j+y-1];
    return sum;
}
inline int rd()
{
    char c;int f = 1;
    while(!isdigit(c = getchar()))if(c=='-')f = -1;
    int x = c-'0';
    while(isdigit(c = getchar()))x = x*10+(c^48);
    return x*f;
}
int main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int t = 333;
    while(t--)
    {
        memset(a,0,sizeof a);memset(b,0,sizeof b);
        n = rd();
        if(n == 3)
        {
            while(1)
            {
                for(int i = 1;i <= n;i++)for(int j = 1;j <= n;j++)
                    b[i][j] = rnd()&1;
                if(pri())break;else rd();
            }
            continue;
        }
        b[3][3] = 1;
        if(pri())continue ;
        for(int i = 1;i <= n-2;i++)
        {
            string s;cin >> s;
            if(i <= 3)
                for(int j = 1;j <= 3;j++)
                    a[4-i][4-j] = s[j-1]-'0';
        }
        int x = 0,y = 0;
        for(int i = 1;i <= 3;i++)for(int j = 1;j <= 3;j++)
            if(a[i][j])x = i,y = j;
        for(int i = 1;i <= n-2;i++)for(int j = 1;j <= n-2;j++)
            if(!get(i,j))b[i+x-1][j+y-1] ^= 1;
        pri();
    }
    return 0;
}
```

---

## 作者：ShiRoZeTsu (赞：0)

- 当 $n \geq 5$ 时，我们可以考虑先求出这个矩阵 $a$。

考虑构造这样的一个 $b$：
$$
\begin{pmatrix}
0 & 0 & 0 & \cdots & 0 \\
0 & 0 & 0 & \cdots & 0 \\
0 & 0 & 1 & \cdots & 0 \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
0 & 0 & 0 & \cdots & 0
\end{pmatrix}
$$
即除了 $b_{3, 3} = 1$ 外，所有 $b_{i, j} = 0$。

这样做有什么意义？

我们在得到的矩阵 $c$ 上找到左上角的九宫格，发现 $c_{1, 1} = 1$ 当且仅当 $a_{3, 3} = 1$，$c_{1, 2} = 1$ 当且仅当 $a_{2, 1} = 1$，$c_{2, 1} = 1$ 当且仅当 $a_{1,2} = 1$ …… $c_{i, j} = 1$ 当且仅当 $a_{4-i, 4-j} = 1$。这个性质比较显然。

在得到矩阵 $a$ 后，构造答案就很容易了。

直接暴力遍历 $(n-2) \times (n-2)$ 个位置，然后检查其对应的九宫格是否满足异或为 $1$，同时记录一个对答案产生贡献的位置 $(x, y)$，如果异或不为 $1$ 就将 $(x, y)$ 取反，然后就做完了。

为什么这样构造是对的？相邻两个位置答案不会影响吗？

因为左右相邻的两个位置，如果左边格子的目标位是 $(i+x, j+y)$，那么右边格子的目标位一定是 $(i+x, j+y+1)$。（上下相邻同理）

因此这样构造，相邻答案无影响。

这样对于每个 $n \geq 5$ 的轮，我们都能在 $2$ 次询问内得到正确答案。

$$
 \ 
$$

- 当 $n=3$ 时，我们可以直接构造一个随机的 $01$ 矩阵。

考虑这样做的概率。首先矩阵 $a$ 是固定的，所以 $a_{i, j} \operatorname{and} b_{i, j} = 1$ 只取决于 $b_{i, j}$ 的取值（因为如果 $a_{i, j} = 0$，那么一定没有贡献），因此 $a_{i, j} \operatorname{and} b_{i, j} = 1$ 的概率是 $\frac{1}{2}$。

然后我们考虑任意两个随机变量 $x, y$ 之间异或的结果。首先，$x, y$ 是 $0$ 或 $1$ 的概率均为 $\frac{1}{2}$，那么有：

| $\oplus$ | $x = 0$ | $x = 1$ |
| :------: | :-----: | :-----: |
| $y = 0$  |   $0$   |   $1$   |
| $y = 1$  |   $1$   |   $0$   |

那么 $x \oplus y = 1$ 的概率也是 $\frac{1}{2}$。因此，所有随机变量异或和为 $1$ 的概率也为 $\frac{1}{2}$。



也就是说，我们每次构造这个随机矩阵就像抛硬币，有 $\frac{1}{2}$ 的概率得到正面（获胜），有 $\frac{1}{2}$ 的概率得到反面（失败），我们最终目的是在 $999$ 次抛硬币中得到 $333$ 次正面。

可以考虑求出这样做失败的概率，设这个事件为 $A$，有：
$$
P(A) = \frac{\sum \limits_{i=0}^{332} \binom{999}{i}}{2^{999}}
$$

这个概率是 $10^{-27}$ 量级的，可以说相当小了。 

总共的期望次数是 $666$ 次得到胜利，非常地有趣。



Code：

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

const int maxn = 335;

int n, px, x, y, T = 333;
int a[3][3], b[maxn][maxn];
char s[maxn];

int main() {
    srand(time(NULL));
    while(T--) {
        scanf("%d", &n);
        if(n == 3) {
            while(true) {
                //构造随机矩阵
                for(int i = 1; i <= n; i++) {
                    for(int j = 1; j <= n; j++)
                        putchar('0' + (rand() % 2));
                    putchar('\n');
                }
                fflush(stdout);
                scanf("%s", s+1);
                if(s[1] == 'C') break;
                scanf("%s", s+1);
            }
        }
        else {
            //求出矩阵 a
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++)
                    putchar('0' + (i == 3 && j == 3));
                putchar('\n');
            }
            fflush(stdout);
            scanf("%s", s+1);
            if(s[1] == 'C') continue;
            for(int i = 2; i >= 0; i--) {
                scanf("%s", s+1);
                for(int j = 2; j >= 0; j--)
                    a[i][j] = s[3-j] - '0';
            }
            for(int i = 4; i <= n-2; i++) scanf("%s", s+1);

            //构造答案
            for(int i = 1; i <= n-2; i++)
                for(int j = 1; j <= n-2; j++)
                    b[i][j] = 0;
            for(int i = 1; i <= n-2; i++)
                for(int j = 1; j <= n-2; j++) {
                    px = 0;
                    for(int k = 0; k <= 2; k++)
                        for(int l = 0; l <= 2; l++) {
                            if(a[k][l]) {
                                px ^= b[i+k][j+l];
                                //记录一个有效位置
                                x = k, y = l;
                            }
                        }
                    if(!px) b[i+x][j+y] ^= 1;
                }
            //输出
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++)
                    putchar('0' + b[i][j]);
                putchar('\n');
            }
            fflush(stdout);
            scanf("%s", s+1);
        }
    }
    return 0;
}
```

---

