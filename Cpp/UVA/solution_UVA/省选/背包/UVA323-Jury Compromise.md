# Jury Compromise

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=259

[PDF](https://uva.onlinejudge.org/external/3/p323.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/c7b6c683e8d99d641e6ceda5403d2046b1543157.png)

## 样例 #1

### 输入

```
4 2
1 2
2 3
4 1
6 2
0 0
```

### 输出

```
Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3
```

# 题解

## 作者：ysj1173886760 (赞：24)

这道题很不错，所以写一篇题解吧。

楼上的dalao也说过了，这是一道01背包拔河问题，实际上并不简单的只是01背包拔河。

这道题中物品的属性也有变化，属性不仅仅是要用于拔河的权值，还有另一个属性，就是这道题中的人，每一个人看做一个物品，其p和d值就是用于拔河的权值，而人本身还有一个属性就是体积，一个人就是1，为了满足恰好选m个的要求。

所以正常来说我们的背包应该设成3维，dp[i][j][k]表示前i个人，选了j个人，k=$\sum p[i]-d[i]$ 时最大的$\sum p[i]+d[i]$

我们可以优化成滚动数组。

这些细节就不在多说了，想说的就是这道题可以在网上看到很多的题解。
但是有些题解并不是正确的。

有些做法是先枚举m，以选择的人划分阶段。然后在dp内部判断是否选择了重复的。再继续dp

大概是这样的。
```cpp
for(int j=0;j<m;j++){
            for(int k=0;k<=800;k++)
            	if(f[j][k]>=0){
                for(int i=1;i<=n;i++)
                (judge.....)
                }
```

这样的做法是错误的，因为如果以人数作为阶段划分，每次枚举这一阶段要选那个人进去，首先就需要确定这个人之前没有出现过，第一想法肯定是状压，但是网上的做法并不是这样的。而是写了一个find函数，顺着之前走到过的最优解的路径进行查找，看之前有没有选过这个人。从而更新状态。

但是我们可以发现，如果这样强行把需要记录那个人选没选的信息压掉，就出现了后效性，也就是说，如果达到dp[i][j]这个状态，根据上面的方式转移，其背后还隐藏着路径这个状态。

如果存在相同值也可以到达dp[i][j]这个状态，在上面的方案中是不取的。但是问题来了，如果之后的最优解需要当前选择方案中的一个怎么办呢？？

形象点说，当前选了a b c可以到达dp[i][j],同时如果选d e f也可以到达这个状态,如果最终答案是a d e f，但如果程序选的a b c，那么之后的决策中就没有a，也就不会达到a d e f这个状态。

还有一个很相似的例子就是noip2017 的宝藏，很多人的状态都是错的，因为需要考虑路径的长度，但是数据水就过去了。

这道题一样，是需要考虑已经选择的集合的。
如果根据划分人数为状态，就不需要考虑是否选了重复的。

还有一点就是记路径了。如果用滚动数组的方法记路径会发现出现重复了。但是最终的值是对的，但是方案不对。

这是因为倒叙更新状态的话，dp是不会受到影响的，但是路径数组可能会被自己更新，emm

举个例子，比如当前枚举到3，dp[3][50]是由第三个数转移来的。
我们记录rec[3][50]=3,假设3的权值为5，我们找路径就会先找3，然后找dp[2][45],假设rec[2][45]=2.

如果很巧合的我们用3同样更新了dp[2][45]的话，那么rec[2][45]就变成了3，结果最后找路径就出现了重复。

所以考虑用链表存储路径，状态与状态的转移直接把表头继承过去就行了，然后加上当前点。

总之还是需要多体会吧。dp的后效性还是很坑人的。

对了注意一点，要输出两个换行


代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxx=430;
const int maxn=2e2+10;

int n,m,tot;
int dp[30][maxx*2],p[maxn],d[maxn],rec[30][maxx*2];
struct line
{
	int to,next;
}edge[maxn*4*maxx];

void add1(int a1,int a2,int b)
{
	edge[++tot].to=b;
	edge[tot].next=rec[a1][a2];
	rec[a1][a2]=tot;
}
void print(int now)
{
	if(!now)return;
	print(edge[now].next);
	cout<<" "<<edge[now].to;
}

int main()
{
	int cnt=0;
	cin>>n>>m;
	while(n!=0&&m!=0)
	{
		cnt++;
		for(int i=1;i<=n;i++)cin>>p[i]>>d[i];
		memset(dp,-0x3f,sizeof(dp));
		memset(rec,0,sizeof(rec));
		dp[0][maxx]=0;
		for(int i=1;i<=n;i++)
			for(int j=m;j>=1;j--)
				for(int k=-400;k<=400;k++)
				{
					if(dp[j-1][k-(p[i]-d[i])+maxx]<0)continue;
					if(dp[j-1][k-(p[i]-d[i])+maxx]+p[i]+d[i]>dp[j][k+maxx])
					{
						dp[j][k+maxx]=dp[j-1][k-(p[i]-d[i])+maxx]+p[i]+d[i];
						rec[j][k+maxx]=rec[j-1][k-(p[i]-d[i])+maxx];
						add1(j,k+maxx,i);
					}
				}
		int ans=0,id=0,pp=0,dd=0;
		for(int i=0;i<=400;i++)
		{
			ans=dp[m][maxx+i],id=i;
			if(dp[m][maxx-i]>ans)id=-i,ans=dp[m][maxx-i];
			if(ans>=0)break;
		}
		pp=(ans+id)/2;
		dd=(ans-id)/2;
		cout<<"Jury #"<<cnt<<endl;
		cout<<"Best jury has value "<<pp<<" for prosecution and value "<<dd<<" for defence:"<<endl;
		print(rec[m][id+maxx]);
		cout<<endl;
		cout<<endl;
		cin>>n>>m;
	}
	return 0;
}
```

---

## 作者：随情英 (赞：14)

记一次极痛的教训

本题的思路不难想，可以参考 $01$ 背包拔河问题。

注意到要求在差的绝对值最小的情况下，和最大。可以考虑体积为差值，价值为和跑 $01$ 背包。

本题要求输出方案，使得本来简单的 $dp$ 强行变成毒瘤。

可以考虑记录每一个 $dp$ 状态是由哪一个转移过来。然而，在编写背包问题时，一般会压缩掉外层循环，也就是阶段所代表的状态。所以如果在记录路径转移时，只开二维，就会导致后面覆盖前面，最后回溯出错。这是我在一开始犯得错误，也是本题很坑的点。路径转移要开到三维。

在本题中差值有可能为负数，而负数下标会导致 $RE$，所以我们考虑对每一个差加上一个 $del$, 开到 $400$ 即可, 转移时尤其要注意判断是否越界，不然会导致数组开多大都过不去，且难以查错，这是我犯得第二个错误。

然后，由于 $dp$ 初始状态，我们认为是负无穷， 所以在判断一个状态是否可行时，应判断是否非负， 而不是为正。（本题 $a,b$ 可能为零）， 同时在路径回溯时， 不能认为差值为 $-400$ 时退出，会被卡掉

```cpp
const int maxn = 220;
const int del = 400;
int a[maxn], b[maxn];
int f[22][maxn << 2], d[maxn][22][maxn << 2];
int s[maxn];
int main()
{
    int n, m, t = 0;
    while (std::cin >> n >> m, n || m)
    {
        if (n == 0)
        {
            return 0;
        }
        ++t;
        memset(f, 0xcf, sizeof(f));
        memset(d, 0, sizeof(d));
        f[0][400] = 0;
        for (int i = 1; i <= n; ++i)
        {
            std::cin >> a[i] >> b[i];
            for (int j = m; j; --j)
            {
                for (int k = -del; k <= del; ++k)
                {
                    if (k + del - (a[i] - b[i]) < 0 || (k + del - (a[i] - b[i]) > 800))
                    {
                        continue;
                    }//这里开始没判
                    if (f[j - 1][k - (a[i] - b[i]) + del] + a[i] + b[i] > f[j][k + del])
                    {
                        f[j][k + del] = f[j - 1][k - (a[i] - b[i]) + del] + a[i] + b[i];
                        d[i][j][k + del] = i;
                    }
                }
            }
        }
        int w;
        for (int i = 0; i <= del; ++i)
        {
            if (f[m][del + i] >= 0 || f[m][del - i] >= 0)
            {//这里开始没有等于号
                if (f[m][del + i] > f[m][del - i])
                {
                    w = del + i;
                }
                else
                {
                    w = del - i;
                }
                break;
            }
        }
        printf("Jury #%d\n", t);
        int x = m, y = w, z;
        for (int i = n; i; --i)
        {
            if (d[i][x][y])
            {
                z = d[i][x][y];
                break;
            }
        }
        int tot = 0;
        while (x > 0)
        {
        //这里原来写了 x > 0 && y > 0
            int tmp = d[z][x][y];
            s[++tot] = tmp;
            x--, y -= a[tmp] - b[tmp];
            if (x <= 0 || y <= 0)
            {
                break;
            }
            if (tmp - 1 <= 0)
            {
                break;
            }
            for (int i = tmp - 1; i; --i)
            {
                if (d[i][x][y])
                {
                    z = d[i][x][y];
                    break;
                }
            }
        }
        int P = 0, D = 0;
        for (int i = 1; i <= tot; ++i)
        {
            P += a[s[i]], D += b[s[i]];
        }
        printf("Best jury has value %d for prosecution and value %d for defence:\n", P, D);
        for (int i = tot; i; --i)
        {
            printf(" %d", s[i]);
        }
        puts("\n");
        tot = 0;
    }
    return 0;
}
 //* @Date: 2020-11-29 15:24:52
 //* @LastEditTime: 2020-11-29 20:31:15


---

## 作者：pythoner713 (赞：13)

有 $n$ 个人，每个人有 $d_i,p_i$ 两个分数，要求从中选出 $m$ 个人，使得两个总分的差值 $|\sum d_i-\sum p_i|$ 最小。如果方案不唯一，选总分 $\sum d_i+\sum p_i$ 大的方案（题目疯狂暗示DP...）

不妨把每个人看成物品，有选和不选两种选择。

这样就可以看成一道 $0/1$ 背包问题，背包的容积是 $m$。

沿用[砝码称重](https://www.luogu.com.cn/problem/P1441)的思路，记 $01$ 数组 $f[j][D][P]$ 表示枚举到前 $i$ 个人时，**已经选出 $j$ 个人加入评审团，且当前辩方总分为 $D$，控方总分为 $P$ 的方案是否可行。** 初始状态为 $f[0][0][0]=\text{True}$，然后通过状态转移方程：

$$f[j][D][P] \text{ |= } f[j-1][D-d_i][P-p_i]$$

转移出所有合法方案。然后我们再枚举所有 $f[m][D][P]=\text{True}$ 的合法方案，再其中找出 $|D-P|$ 最小的方案即可。

但是这样会出大问题。由于总分较大（$20\times20=400$），可以发现上述算法的枚举次数高达 $n\times m\times400\times400\le6.4\times10^8$。这些冗余的次数都是因为使用了 $01$ 数组存储状态，没有充分利用数组的价值。

观察到我们可以将上述背包的后两维合并成一维，记 $f[j][k]$ 表示枚举到前 $i$ 个人时，**已经选出 $j$ 个人加入评审团，且当前双方总分之差 $k=D-P$ 时的最大总分 $D+P$。** 请注意，我们此时的状态存的不是可不可行，而是假设可行时的最大总分。前者是布尔数，后者是整数。

为什么呢？因为在用布尔数组 $f[j][D][P]$ 存时，我们可以直接通过两个下标之和 $D+P$ 算出总分。但是用整数数组 $f[j][k]$ 时，只通过 $k=D-P$ 的信息，无法算出总分 $D+P$ 是多少，我们其实是将总分**存到状态中**。这个技巧在DP中挺常见的，例如之前CSP的[Emiya 家今天的饭](https://www.luogu.com.cn/problem/P5664)，和这题有着很多相似之处。

想通这一步后，转移方程就不难推出：

$$f[j][k]=\max(f[j][k],f[j-1][k-(d_i-p_i)]+d_i+p_i)$$

赋初始状态 $f[0][0]=0$，按照上述方程转移（对了，因为这是 $01$ 背包， $j$ 要倒序枚举）。最后我们在最终状态 $f[m][k]$ 中找出 $|k|$ 最小的合法方案即可，如果 $|k|$ 相等，则取 $f[m][k]$ 较大的方案。

还没完呢，这题还要记录那些人被选中了。因此我们要在每次转移时记录此次转移从何人转移而来。具体地说，记 $d[i][j][k]$ 表示枚举到前 $i$ 个人时，$f[j][k]$ 这个状态是通过选了哪个人转移而来的。详情请见代码。

最后有几个坑点提醒大家：

- 枚举时 $k$ 可能是负数，需要加上一个大数（也就是我代码中的下划线），将整个数组平移到正整数中。
- 每输出一个方案后要多空一行（$\text{Output an empty line after each test case}$），也就是 printf("\n\n") 。
- 方案开头要空一个格（$\text{Output a blank before eachindividual candidate number.}$），所以要printf(" %d", A[i])，真有你的啊出题人。

```cpp
#include<bits/stdc++.h>
#define _ 400
using namespace std;

int ans, cnt, n, m, t, suma, sumb, A[50], a[210], b[210], f[30][900], d[210][30][900];

void solve(int i, int j, int k){
	if(!j) return;
	int last = d[i][j][k + _];
	solve(last - 1, j - 1, k - (a[last] - b[last]));
	A[++t] = last;
	suma += a[last], sumb += b[last];
}

int main(){
	while(1){
		cin >> n >> m;
		if(!n && !m) return 0;
		for(int i = 1; i <= n; i++){
			cin >> a[i] >> b[i];
		}
		memset(f, 0xcf, sizeof(f));
		f[0][_] = 0;
		for(int i = 1; i <= n; i++){
			for(int j = 0; j <= m; j++){
				for(int k = -400; k <= 400; k++){
					d[i][j][k + _] = d[i - 1][j][k + _];
				}
			}
			for(int j = m; j; j--){
				for(int k = -400; k <= 400; k++){
					if(k - (a[i] - b[i]) < -400 || k - (a[i] - b[i]) > 400) continue;
					if(f[j - 1][k - (a[i] - b[i]) + _] + a[i] + b[i] > f[j][k + _]){
						f[j][k + _] = f[j - 1][k - (a[i] - b[i]) + _] + a[i] + b[i];
						d[i][j][k + _] = i;
					}
				}
			}
		}
		ans = 400;
		for(int i = -400; i <= 400; i++){
			if(f[m][i + _] < 0) continue;
			if(abs(i) < abs(ans) || (abs(i) == abs(ans) && f[m][i + _] > f[m][ans + _])) ans = i;
		}
		t = suma = sumb = 0;
		solve(n, m, ans);
		printf("Jury #%d\n", ++cnt);
		printf("Best jury has value %d for prosecution and value %d for defence:\n", suma, sumb);
		for(int i = 1; i <= t; i++) printf(" %d", A[i]);
		printf("\n\n");
	}
}
```



---

## 作者：bingxin (赞：7)

## 简化题意

给定 $n$ 个数对 $(p_i,d_i)$，在其中取出 $m$ 对，使这 $m$ 对中 $|\sum p_i - \sum d_i|$ 最小；当有多个值时，取总和之和更大的。

数据范围：$1 \le N \le 200,1 \le M \le 20,0 \le p_i,d_i \le 20$

## 做法分析

既然题目中已经给出了我们这 $m$ 个数对，并且每个数对可以选择选或不选这两种情况，那我们就来考虑用 01 背包来做。我们回想，在普通的 01 背包问题中，每个物品所带来的影响只有 **体积** 和 **价值** 这两个维度，其中价值是我们要求的，而体积用来做转移的状态。然而这道题可以看到，每对数不仅占了一份体积，还都附带了 $(p_i,d_i)$ 的附加信息，这就需要我们将 01 背包问题搬到 **高维** 上来做。

搬到高维上的 01 背包我们如法炮制，我们首先尝试出一种可行方案，然后在可行方案中求出我们想要的最优方案。设 $f_{i,j,d,p}$ 表示：

1. 考虑到第 $i$ 个人 ($1 \le i \le n$)
2. 当前选了 $j$ 个人 ($1 \le j \le i$)
3. 候选人 $d$ 值之和 ($0 \le d \le 20 \times j$)
4. 候选人 $p$ 值之和 ($0 \le p \le 20 \times j$)

这样，我们把人看做物品，考虑每个物品取不取，当外层循环到 $i$ 时，表示已经考虑了前 $i$ 个人，我们用背包 **滚动数组** 优化掉一维，有转移方程:
$$f_{j,d,p} = f_{j,d,p} \ \operatorname{or} \ f_{j - 1,d - D_i,p - P_i}$$
那么我们最后循环一下，求出所有为 true 的状态中 $|d - p|$ 尽量小，有多个值时 $d + p$ 尽量大的状态。

这样对不对呢？可以看到，我们 **分阶段、有顺序、无重复** 地遍历到了每一种情况，但我们考虑这个解法的复杂度却有点不尽人意：每个维度的循环范围已在上文给出，这样解法总体的复杂度便是 $O(NM^5)$ 的（$20$ 与 $M$ 直接同阶了都），而且这样写还有一个坏处：**决策性不够明显**，我们这样设计考虑的是方案的可行性，转移时是或出来的（冷门操作），导致我们并不好解决输出方案这一问。

当然，为了方便大家理解上面的前置状态设计，我也写了一份这样的代码，其中求出来了 $d$ 值和 $p$ 值。~~如果有大佬能好心填一下这个状态记录的话非常感谢orz。~~

```cpp
constexpr int N = 205, M = 25;
int n, m, P[N], D[N];
bool f[M][20 * M][20 * M];
void solve()
{
    for (int i = 1; i <= n; i++)
        cin >> P[i] >> D[i];
    f[0][0][0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = i; j; j--)
            for (int d = 0; d <= 20 * j; d++)
                for (int p = 0; p <= 20 * j; p++)
                    f[j][d][p] |= f[j - 1][d - D[i]][p - P[i]];
    int ansd = 0x3f3f3f3f, ansp = ~0x3f3f3f3f;
    for (int d = 0; d <= 20 * m; d++)
        for (int p = 0; p <= 20 * m; p++)
            if (f[m][d][p])
            {
                if (abs(ansd - ansp) > abs(d - p))
                    ansd = d, ansp = p;
                else if (abs(ansd - ansp) == abs(d - p) && d + p > ansd + ansp)
                    ansd = d, ansp = p;
            }
    cout << ansd << ' ' << ansp;
}
```

我们来考虑这个算法的缺陷：它把所有要维护的信息都堆在了体积上，价值根本就没怎么用，这是不好的。回想我们一开头提到的，价值是我们要求解的并作为 DP 数组的值，我们也试试把其中的体积转化一下，搞一搞转化一个价值出来。

他要的第一关键字是相差最小，能不能存这些人 $d,p$ 之差的绝对值呢？不太行，因为这个最优解并不能导出后面的最优解。加入后边来的这个人一边倒，加上他之后差值就非常大了，根本没法搞。看来差值还是得当成状态，我们换一下，把第二关键字作为值，并在代码里取一下最大值就 ok 了，每新增一个人，导出他之前的差值也非常容易。

设当外层循环到 $i$ 时，设 $f_{j,k}$ 表示在前 $i$ 个人中选出了 $j$ 个，此时 $d - p$ 的差（注意这里是绝对差）为 $k$ 时，双方总和的最大值。有转移：
$$f_{j,k} = \max\limits_{0 \le j \le \min \{i,m\},-20 \times j \le k \le 20 \times j} \{f_{j - 1,k - (D_{i} - P_{i})} + D_{i} + P_{i}\}$$
可能你会注意到，我们在循坏枚举绝对差值的时候，有一半情况数组下标都用的是负数，C++里不允许出现负下标，我们就简单粗暴的给每一个用到 $f$ 数组和 $c$ 数组的地方第二维加一个偏移量，然后就没问题了。

最后我们浅找一下 $f_{m,k}$ 中满足 $|k|$ 最小，相同时 $f_{m,k}$ 最大即可。其中我们使用了滚动数组，转移时保证 $j$ 这一维 **倒序循环** 即可，确保不会被重复选。

最后，本体还要求输出具体方案，由于 01 背包的决策就是选或不选，所以我们记录一个三维 bool 数组 $c_{i,j,k}$ 表示考虑第 $i$ 个人时，$f_{j,k}$ 选了这人没有，套路地把 $\max$ 函数换一下就行，求完之后沿着数组 $c$ 回溯一下 $(i,j,k) \rightarrow (i - 1,j - 1,k - (D_{i} - P_{i}))$。

*以上的每一句话都可在代码中找到详细体现，小的注意事项也写在了注释里。*

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205, M = 25, offset = 400;
int n, m, T, p[N], d[N], f[M][2 * 20 * M];
bool c[N][M][2 * 20 * M]; // 我们要记录的是所有的决策路径, 带上N捏

void print(int i, int j, int k)
{
    if (!j)
        return;
    if (c[i][j][k + offset])
        print(i - 1, j - 1, k - (d[i] - p[i])),
            cout << ' ' << i; // 注意 UVA 地狱输出格式
    else
        print(i - 1, j, k);
}
void solve()
{
    for (int i = 1; i <= n; i++)
        cin >> p[i] >> d[i];
    memset(f, ~0x3f, sizeof(f)); // 求最大值, 我们设初值为负无穷
    f[0][0 + offset] = 0; // 不选人总和为 0
    for (int i = 1; i <= n; i++)
        for (int j = min(i, m); j; j--) // 范围应该很好理解
            for (int k = -20 * j; k <= 20 * j; k++)
            {
                c[i][j][k + offset] = false; // 不选的情况很多, 但选的很少, 所以先默认不选
                if (k - (d[i] - p[i]) < -20 * j || k - (d[i] - p[i]) > 20 * j)
                    continue; // 越界 & 非法情况拜拜
                if (f[j][k + offset] < f[j - 1][k - (d[i] - p[i]) + offset] + d[i] + p[i])
                {
                    f[j][k + offset] = f[j - 1][k - (d[i] - p[i]) + offset] + d[i] + p[i];
                    c[i][j][k + offset] = true; // 只在这里更新一次就好了
                }
            }
    int dlt = 1 << 30, sum = 0, dif = 0;
    for (int k = -20 * m; k <= 20 * m; k++)
    {
        if (f[m][k + offset] < 0)
            continue;
        if (abs(k) < dlt)
            dlt = abs(k), sum = f[m][k + offset], dif = k;
        else if (abs(k) == dlt && f[m][k + offset] > sum)
            sum = f[m][k + offset], dif = k;
    }
    cout << "Jury #" << ++T << '\n' // UVA地狱输出格式提醒
         << "Best jury has value " << ((sum - dif) >> 1) << " for prosecution and value " << ((sum + dif) >> 1) << " for defence:\n";
    print(n, m, dif); // 回溯方案
    cout << "\n\n";
    /* Jury #1
       Best jury has value 6 for prosecution and value 4 for defence:
        2 3 */
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m)
        solve();
    return 0;
}
```


---

## 作者：Itst (赞：7)

### 经典的01背包拔河问题，不是很清楚的可以看下[这道题](https://www.luogu.org/problemnew/show/P1356)或者[这道题](https://www.luogu.org/problemnew/show/P1282)
### 思路都在代码里了，请尽情食用XD
```cpp
#include<bits/stdc++.h>
using namespace std;
short maxN[201][21][801] , thing[201][2];
//保证转移路径不重复所以maxN开了三维（第一维表示看过了几个人，第二维表示已经选了几个人，第三维表示∑P-∑D+400，第三维的平移方法可以避免负数的产生），如果不需要输出人数的话可以只有二、三维
bool p[201][21][801];
//记录是否选了当前物品
inline int max(int a , int b){
    return a > b ? a : b; 
}//手写max会比较快
void output(int a , int b , int c){
    if(!a)	return;
    if(p[a][b][c]){
        output(a - 1 , b - 1 , c - thing[a][0] + thing[a][1]);
        printf(" %d" , a);
        //注意输出格式：空格打在每一个选中的人的前面！
    }
    else	output(a - 1 , b , c);
}//递归输出
int main(){
    int N , M , cou = 0;
    scanf("%d%d" , &N , &M);
    while(N + M){
        memset(maxN[0] , 192 , sizeof(maxN));
        //初始化为负数
        for(int q = 1 ; q <= N ; q++){
            memset(maxN[q] , 192 , sizeof(maxN[q - 1]));
            memset(p[q] , 0 , sizeof(p[q]));
            maxN[q - 1][0][400] = 0;
            scanf("%d%d" , &thing[q][0] , &thing[q][1]);
            for(int i = min(q , M) ; i ; i--)
                for(int j = 0 ; j <= 800 ; j++)
                    if(j + thing[q][0] - thing[q][1] >= 0 && j + thing[q][0] - thing[q][1] <= 800){
                        if(maxN[q - 1][i - 1][j] >= 0 && maxN[q - 1][i - 1][j] + thing[q][0] + thing[q][1] > maxN[q][i][j + thing[q][0] - thing[q][1]]){
                            maxN[q][i][j + thing[q][0] - thing[q][1]] = maxN[q - 1][i - 1][j] + thing[q][0] + thing[q][1];
                            p[q][i][j + thing[q][0] - thing[q][1]] = 1;
                            //标记为已选当前物品
                        }
                        if(maxN[q - 1][i][j + thing[q][0] - thing[q][1]] >= 0 && maxN[q - 1][i][j + thing[q][0] - thing[q][1]] > maxN[q][i][j + thing[q][0] - thing[q][1]]){
                            maxN[q][i][j + thing[q][0] - thing[q][1]] = maxN[q - 1][i][j + thing[q][0] - thing[q][1]];
                            p[q][i][j + thing[q][0] - thing[q][1]] = 0;
                            //标记为未选当前物品
                        }
                    }//状态的两种转移
        }
        printf("Jury #%d\n" , ++cou);
        int i = 0;
        while(maxN[N][M][400 + i] < 0 && maxN[N][M][400 - i] < 0)	i++;
        if(maxN[N][M][400 + i] > maxN[N][M][400 - i]){
            printf("Best jury has value %d for prosecution and value %d for defence:\n" , maxN[N][M][400 + i] + i >> 1 , maxN[N][M][400 + i] - i >> 1);
            output(N , M , 400 + i);
        }
        else{
            printf("Best jury has value %d for prosecution and value %d for defence:\n" , maxN[N][M][400 - i] - i >> 1 , maxN[N][M][400 - i] + i >> 1);
            output(N , M , 400 - i);
        }//输出
        putchar('\n');
        putchar('\n');
        scanf("%d%d" , &N , &M);
    }
    return 0;
}
```

---

## 作者：D2T1 (赞：4)

[$\large\text{My blog}$](https://www.luogu.com.cn/blog/390770/blogcenter)

题目链接：[Luogu](https://www.luogu.com.cn/problem/UVA323) [AcWing](https://www.acwing.com/problem/content/282/)

## 题解 UVA323

考虑 DP。

因为当 $|P-D|$ 相同时，要考虑 $P+D$ 越大，所以设 $dp[i,j,k]$ 表示**前 $i$ 人选 $j$ 人方案差为 $k$ 的最大总分的总分值**。

------------

考虑每个人选或不选。

1. 不选。则 $dp[i,j,k] = dp[i-1,j,k]$
2. 选。$dp[i,j,k] = \max(dp[i,j,k], dp[i-1,j-1,k-p_i+d_i]+p_i+d_i)$（要注意不出界）

因为方案差 $k$ 可能是负数，数组会越界，所以把每个 $k$ 都加上一个偏移量 $Base$，取 $400$（因为最多选 $20$ 人，每人分差最多 $20$）。

------------

找最小的 $|P-D|$，可以从 $dp[n,m,0]\sim dp[n,m,800]$ 中找。

具体方案是：从 $dp[n,m,Base]$ 向两边寻找（两边指 $dp[n,m,Base-1],dp[n,m,Base+1]$，以此类推），如果两边值都是负数，代表方案不存在，否则如果出现正数，则方案存在，找出最大的即可，此时的 $|P-D|$ 设为 $v$。

------------

找具体方案。一种方法是在 DP 过程中使用数组 $Pre$ 记录每次转移从何而来，但是这样会占用很大的空间。于是考虑倒着 DP。

设现在考虑到 $dp[i,j,v]$。

1. 如果 $dp[i-1,j,v]==dp[i,j,v]$，表示没有选第 $i$ 件物品，将 $i$ 减一即可。
2. 如果 $dp[i-1,j,v]≠dp[i,j,v]$，表示选了第 $i$ 件物品，则将 $i$ 存入答案序列，继续考虑 $dp[i-1,j-1,v-p_i+d_i]$。

------------

最后输出。

## 代码

```cpp
//acwing280
//dp[i,j,k]：前 i 人选 j 人方案差为 k 的最大总分的总分值 
#include <bits/stdc++.h>
using namespace std;

const int N = 210, M = 810, Base = 400;
int dp[N][25][M], ans[N];
int n, m, p[N], d[N];
int T;

int main(){
	while(scanf("%d%d", &n, &m) && n && m){
		
		//read & init
		for(int i = 1; i <= n; ++ i) scanf("%d%d", &p[i], &d[i]);
		memset(dp, 0xcf, sizeof(dp)), dp[0][0][Base] = 0;
		
		//dp
		for(int i = 1; i <= n; ++ i)
		for(int j = 0; j <= m; ++ j)
		for(int k = 0; k < M; ++ k){
			dp[i][j][k] = dp[i-1][j][k];
			int val = k - p[i] + d[i];
			if(j < 1 || val < 0 || val >= M) continue;
			dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][val] + p[i] + d[i]);
		}
		
		//find min |D-P|
		int v = 0;
		while(dp[n][m][Base+v] < 0 && dp[n][m][Base-v] < 0) ++ v;
		v = Base + v * (dp[n][m][Base+v] > dp[n][m][Base-v] ? 1 : -1);
		
		//find ans[]
		int cnt = 0, P = 0, D = 0;
		while(m){
			if(dp[n][m][v] != dp[n-1][m][v]){
				ans[++cnt] = n;
				v -= (p[n] - d[n]);
				P += p[n], D += d[n];
				-- m;
			}
			-- n;
		}
		
		//print
		printf("Jury #%d\n", ++ T);
		printf("Best jury has value %d for prosecution and ", P);
		printf("value %d for defence:\n", D);
		sort(ans + 1, ans + cnt + 1);
		for(int i = 1; i <= cnt; ++ i) printf(" %d", ans[i]);
		puts("\n");
		
	}
	return 0;
}
```

---

## 作者：BzhH (赞：3)

读完题,很容易想到这是一道背包问题 ~~,但就是做不来~~,可以看到,方案既与差值有关,又跟和有关,那么可以考虑根据差值或和来考虑状态,可以考虑$f[i][j][k]$表示前$i$个人选了$j$个人并且差值为$k$的和最大的方案

那么状态该如何转移呢?

考虑第$i$个人选或不选

若不选第$i$个人

很明显$f[i][j][k]=f[i-1][j][k])$

若选第$i$个人

第$i$个人的差值已经定了,那么前$i$个人的差值就是$k-(p[i]-d[i])$

可以得出$f[i][j][k]=max(f[i][j][k],f[i-1][j-1[k-(p[i]-d[i])])$

从题目中可以看出,差值的范围$\left [-400,400 \right]$那么可以直接枚举所有差值转移即可

解决了第一小问,接下来就是输出方案,可以考虑把每个状态从哪一个状态转移存起来,可以通过判断$f[i][j][k]$与$f[i-1][j][k]$的关系,若相等,则说明可以不选$i$,若不等,则说明$i$一定被选

代码如下

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int f[205][25][805], p[205], d[205], tot;

void output(int i,int j,int k)//输出方案
{
    int ans[25], cnt = 0, P = 0, D = 0;
    while(j)
    {   
        if(f[i][j][k] == f[i - 1][j][k])
            i--;
        else 
        {
            ans[++cnt] = i;
            k -= (p[i] - d[i]);
            P += p[i];
            D += d[i];
            j--, i--;
        }
    }
    printf("Jury #%d\n", ++tot);
    printf("Best jury has value %d for prosecution and value %d for defence:\n", P, D);
    for (int u = cnt; u >= 1;u--)
        printf(" %d", ans[u]);
    printf("\n\n");//注意要多输出一个换行
}

int main()
{
    int n, m;
    while(scanf("%d%d",&n,&m)&&(n!=0||m!=0))//读入多组数据
    {
        for (int i = 1; i <= n;i++)
            scanf("%d%d", &p[i], &d[i]);
        memset(f, -0x3f, sizeof(f));
        f[0][0][400] = 0;
        for (int i = 1; i <= n;i++)
        {
            for (int j = 0; j <= m;j++)
            {
                for (int k = 0; k <= 800; k++)
                {
                    f[i][j][k] = f[i - 1][j][k];
                    if(j < 1)//因为可以一个人都不选,所以j从0开始,所以要判断j是否等于0
                        continue;
                    int t = k - p[i] + d[i];
                    if(t < 0 || t > 800)//判断是否越界
                        continue;
                    f[i][j][k] = max(f[i - 1][j - 1][t] + p[i] + d[i], f[i][j][k]);
                }
            }
        }
        for (int i = 0; i <= 400; i++)//找出差值最小的方案
        {
            if(f[n][m][400-i] >= 0 ||f[n][m][i+400] >= 0)
            {
                if(f[n][m][400-i] > f[n][m][400+i])
                {
                    output(n, m, 400 - i);
                    break;
                }
                else
                {
                    output(n, m, 400 + i);
                    break;
                }
            }
        }
    }
    return 0;
}
```


---

## 作者：wzy2021 (赞：2)

这题可以背包动态规划来做

是一个多个维度的 $01$ 背包。把 n 个候选人看作 n 个物品，

维护 $3$ 个维度

$f[j][k]$ 表示前 $i$ 个人中选出 $j$ 个，总分差为 $k$ 时，俩总分和的最大值

转移方程 ：

1. 不选第 $i$ 个，$f[j][k]$

2. 选第 $i$ 个，$f[j - 1][k - (a[i] - b[i])] + a[i] + b[i]$

所以，$f[j][k] = \max (f[j][k], f[j - 1][k - (a[i] - b[i])) + a[i] + b[i])$

因为总分差有可能是负数，每个 k 加 $400$，那么 k 的范围是 $1,...,800$

初值：$f[0][0] = 0$，其他为 $-\infty$

目标：找到一个状态 $f[j][k]$，使得$\mid k - 400\mid$最小的情况下，$f[j][k]$ 最大

注意：因为每个人只能选一次，故 $j$ 维要倒序枚举

##### 此题要求具体方案

设 $last[i][j][k]$ 代表当第 i 维度时，$f[j][k]$ 是从哪个维度转移

**注意：维度不能省！！！**

求出最优解后，可以沿着 last 数组找到方案：

设 $use = last[i][j][k]$，从状态 $(i, j, k)$ 到状态 $(use - 1, j - 1, use - (a[i] - b[i])))$。最后到$j = 0$ 结束

所有的 $use$ 就是人选。

具体实现可以参考程序。

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int n, m, cnt, ans1, ans2, a[210], b[210], f[30][810], ans[30], last[210][30][810];

void find (int i, int j, int k) {
	if (j == 0) return ;
	int use = last[i][j][k];
	find (use - 1, j - 1, k - (a[use] - b[use]));
	ans[++ cnt] = use; ans1 += a[use]; ans2 += b[use];
}

int main() {
	int T = 0;
	while (cin >> n >> m && n) {
		T ++;
		for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
		memset (f, -0x3f, sizeof (f)); cnt = 0; ans1 = 0; ans2 = 0;
		f[0][400] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				for (int k = 0; k <= 800; ++k) last[i][j][k] = last[i - 1][j][k];
			}
			for (int j = m; j; --j) {
				for (int k = 0; k <= 800; ++k) {
					int res = k - (a[i] - b[i]);
					if (res < 0 || res > 800) continue;
					if (f[j][k] < f[j - 1][res] + a[i] + b[i]) {
						f[j][k] = f[j - 1][res] + a[i] + b[i];
						last[i][j][k] = i;
					}
				}
			}
		}
		int sum = 0;
		for (int i = 0; i <= 400; ++i) {
			if (f[m][400 + i] >= 0 && f[m][400 + i] >= f[m][400 - i]) {
				sum = 400 + i; break;
			}
			if (f[m][400 - i] >= 0) {
				sum = 400 - i; break;
			} 
		}
		find (n, m, sum);
		cout << "Jury #" << T << endl;
		cout << "Best jury has value " << ans1 << " for prosecution and value " << ans2 << " for defence:\n";
		for (int i = 1; i <= cnt; ++i) cout << " " << ans[i];
		cout << "\n\n";
	}
	return 0;
}
```

---

## 作者：wyp20130701 (赞：1)

由于选择人数有限制，因此考虑将人数设入动态规划的一维。  
考虑目标是 $D + P$ 最大，那么考虑背包，将 $D + P$ 考虑成物品的总价值。  
设 $dp_{i,j,k}$，表示前 $i$ 个人中选了 $j$ 个人，$D - P = k$，$D + P$ 的最大值。  
转移：$dp_{i,j,k} = \max(dp_{i - 1,j,k}, dp_{i - 1, j - 1, k - d_i + p_i} + d_i + p_i)$。  
采用类似思想滚动第一维，由于是个 01 背包，可以彻底滚动掉。访问 $f_{j - 1,k - d_i + p_i}$ 必须还处在 $i - 1$ 这个阶段，所以 $j$ 应倒序枚举。

```cpp

#include <bits/stdc++.h>
inline int read() {
    int x = 0;
    bool f = true;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = false;
    for (; isdigit(ch); ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    return f ? x : (~(x - 1));
}
inline bool gmx(int &a, int b) {
    return b > a ? a = b, true : false;
}

const int maxn = 205;
const int maxm = 25;
const int maxv = (maxm * 20) << 1;
const int par = maxm * 20;

int f[maxm][maxv];
int d[maxn], p[maxn];
int pre[maxn][maxm][maxv];

void pr(int i, int j, int k) {
    if (j == 0)
        return ;
    int id = pre[i][j][k + par];
    pr(id - 1, j - 1, k - d[id] + p[id]);
    printf(" %d", id);
}

int main() {
    for (int cas = 1, n = read(), m = read(); n; ++cas, n = read(), m = read()) {
        std :: memset(f, 0xc0, sizeof(f));
        f[0][par] = 0;
        for (int i = 1; i <= n; ++i) {
            p[i] = read();
            d[i] = read();
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = m; j; --j)
                for (int k = -400; k <= 400; ++k)
                    if (gmx(f[j][k + par], 
                            f[j - 1][k - d[i] + p[i] + par] 
                            + d[i] + p[i]))
                        pre[i][j][k + par] = i;
                    else
                        pre[i][j][k + par] = pre[i - 1][j][k + par];
        }
        
        for (int dif = 0; dif <= 400; ++dif) {
            int ps = f[m][par + dif], ng = f[m][par - dif];
            if (ps < 0 && ng < 0)
                continue;
            int k = dif;
            if (ps < 0 || ng > ps)
                k = -dif;
            
            printf("Jury #%d\n", cas);
            printf("Best jury has value %d for prosecution and value %d for defence:\n", (f[m][k + par] - k) >> 1, (f[m][k + par] + k) >> 1);
            pr(n, m, k);
            puts("");
            puts("");
            break;
        }
    }
    cout << "防抄袭万岁！！！";
    return 0;
}
```

---

## 作者：Wangzehao2009 (赞：1)

这道题本来是一个比较轻松的 dp，但是由于 UVA 逆天的题目输出形式和输出方案变成了一坨。

考虑背包。注意到问题涉及的值遇较小，所以我们可以大胆的设置状态。

设 $f_{i,j,x,y}$ 表示，前 $i$ 个候选人中选择 $j$ 个人进入陪审团，控方总分 $\sum p=x$，辩方总分 $\sum d=y$ 的方案是否存在，所以这个 dp 是一个 ``bool`` 类型。

和普通的背包类似，不难得到状态转移方程

$$f_{i,j,x,y}=f_{i-1,j,x,y} \lor f_{i-1,j-1,x-p_i,y-d_i}$$

初始状态：$f_{0,0,0,0}=1$

答案是 $f_{n,m,x,y}=1$ 的状态中满足 $abs(x-y)$ 最小的前提下，$x+y$ 最大的 $(x,y)$。

$x,y$ 的值域都是 $[0,20m]$，所以时间复杂度是 $O(400nm^3)$，大约是 $6 \times 10^8$ 左右，但是实际加一些限制远远达不到这个复杂度（详见代码），所以可以放心。但是空间会炸！（别忘了还要输出方案。）

所以我们可以用背包的经典优化方式，**倒着扫**。我们倒着枚举 $j,x,y$，这样我们更新的时候只取还没被更新的状态，所以没有问题。

即
$$f_{j,x,y}=f_{j,x,y} \lor f_{j-1,x-p_i,y-d_i}$$

现在空间问题也解决了！

现在解决如何输出方案。这个其实也是背包的经典问题。我们维护一个指针 $lst_{j,x,y}$，分别表示到达 $(j,x,y)$ 这个状态最后一个要选的的人的编号。

我们最后找到答案状态后再不断跳前一个。假设答案是 $(m,P,D)$。我们可以知道最后一个选择了 $lst_{m,P,D}$ 人，所以 $m'=m-1,P'=P-p_{lst_{m,P,D}},D'=D-d_{lst_{m,P,D}}$，新的状态变为 $(m',P',D')$，再跳 $lst_{m',P',D'}$……

最后说几个要注意的点：

1. 
> Output a blank before each
individual candidate number.

2.
> Output an empty line after each test case.

3. 最后求的方案要逆序输出。

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int const N=203,M=21;
bool f[M][M*M][M*M];
int n,m,lst[M][M*M][M*M],p[N],d[N];
vector <int> ans;
void solve()
{
    ans.clear();
    memset(f,0,sizeof(f)),memset(lst,0,sizeof(lst));
    f[0][0][0]=1;
    int s1=0,s2=0,mincha=0x3f3f3f3f,ansx=0,ansy=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&p[i],&d[i]);
        s1+=p[i],s2+=d[i];
        // 这里有几个小的限制条件，可以优化常数，大家看一下就懂了 
        for(int j=min(i,m);j>=1;--j)
            for(int x=min(m*20,s1);x>=p[i];--x)
                for(int y=min(m*20,s2);y>=d[i];--y)
                    if(!f[j][x][y] && f[j-1][x-p[i]][y-d[i]]) f[j][x][y]=1,lst[j][x][y]=i;
    }
    for(int cha=0;cha<=m*20;++cha)
        for(int x=0;x<=m*20;++x)
        {
            int y=x+cha;
            if(y<=m*20 && f[m][x][y]) 
            {
                if(abs(x-y)<mincha) mincha=abs(x-y),ansx=x,ansy=y;
                else if(abs(x-y)==mincha && x+y>ansx+ansy) ansx=x,ansy=y;
            }
            y=x-cha;
            if(y>=0 && f[m][x][y]) 
            {
                if(abs(x-y)<mincha) mincha=abs(x-y),ansx=x,ansy=y;
                else if(abs(x-y)==mincha && x+y>ansx+ansy) ansx=x,ansy=y;
            }
        }
    printf("Best jury has value %d for prosecution and value %d for defence:\n",ansx,ansy);
    while(lst[m][ansx][ansy])
    {
        int u=lst[m][ansx][ansy];    
        ans.push_back(u);
        ansx-=p[u],ansy-=d[u],m--;
    }
    reverse(ans.begin(),ans.end());
    for(int i:ans) printf(" %d",i);
    puts(""),puts("");
}
int main()
{
    int t=0;
    while(1)
    {
        scanf("%d%d",&n,&m);
        if(n==0 && m==0) break;
        printf("Jury #%d\n",++t);
        solve();
    }
    return 0;
}
```

---

## 作者：Waldin (赞：1)

考虑 01 背包模式动态规划（Dynamic Programming，DP）。

设 $DP_{i,j,k}$ 表示前 $i$ 个候选人选了 $j$ 个，且 $D-P=k$ 时 $D+P$ 的最大值，则状态转移方程为
$$
DP_{i,j,k}=\max\left\{DP_{i-1,j,k},DP_{i-1,j-1,k-(d_i-p_i)}+\left(d_i+p_i\right)\right\}
$$
初始状态 $DP_{i,0,0}=0$。然后模仿 01 背包模型进行转移即可，也因此该题支持像 01 背包一样通过倒序转移第二维来压掉第一维。

总时间复杂度为 $O\left(NM^2p_i\right)$。

实现中可以利用指针使数组下标支持负数；记录方案只需要开一个 `bitset` 数组来保存每一个状态选的什么人即可，这个 `bitset` 同样也可以压掉第一维。参考代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define typeof(...) __decltype(__VA_ARGS__)
constexpr size_t MAXN = 200, MAXM = 20, MAXpd = 20;

#ifndef _getchar_nolock
#define _getchar_nolock getchar_unlocked
#endif
class FastIn_Base {
public:
	template<typename _Ty>
	FastIn_Base& operator>>(_Ty& __restrict__ int_var) noexcept {
		int c; bool f;
		if (is_signed<_Ty>::value)
			f = false;
		while (!isdigit(c = _getchar_nolock()))
			if (is_signed<_Ty>::value && c == 45)
				f = true;

		int_var = c - 48;
		while (isdigit(c = _getchar_nolock()))
			int_var = int_var * 10 + (c - 48);

		if (is_signed<_Ty>::value && f)
			int_var = -int_var;
		return *this;
	}
};
#define intIn ((FastIn_Base) {})
#define cin intIn

template<typename _Ty>
bool to_max(_Ty& __restrict__ x, const _Ty y) noexcept {
	if (y > x) {
		x = y;
		return true;
	}
	return false;
}

int main(void) noexcept {
	ios::sync_with_stdio(false);

	uint8_t N, cnt = 0;
	while (cin >> N, N) {
		uint8_t M;
		cin >> M;
		uint8_t p[MAXN + 1], d[MAXN + 1];
		for (typeof(N)i = 1; i <= N; ++i)
			cin >> p[i] >> d[i];
		int16_t DP_BASE[MAXM + 1][2 * MAXpd * MAXM + 1],
			* DP[MAXM + 1];
		bitset<MAXN + 1> slc_BASE[MAXM + 1][2 * MAXpd * MAXM + 1],
			* slc[MAXM + 1];
		for (typeof(M)i = 0; i <= M; ++i) {
			DP[i] = &DP_BASE[i][400];
			memset(DP_BASE[i], 0xCF, sizeof(DP_BASE[i]));
			slc[i] = &slc_BASE[i][400];
		}
		DP[0][0] = 0;
		for (typeof(N)i = 1; i <= N; ++i)
			for (auto j = min(i, M); j; --j)
				for (int16_t k = max(-400, d[i] - 400 - p[i]); k <= min(400, d[i] + 400 + p[i]); ++k)
					if (to_max(DP[j][k], (int16_t)(DP[j - 1][k - (d[i] - p[i])] + (d[i] + p[i])))) {
						slc[j][k] = slc[j - 1][k - (d[i] - p[i])];
						slc[j][k][i] = true;
					}

		int16_t ans;
		for (int16_t i = 0; i <= 400; ++i) {
			if (DP[M][i] >= 0 && DP[M][i] >= DP[M][-i]) {
				ans = i;
				break;
			}
			if (DP[M][-i] >= 0) {
				ans = -i;
				break;
			}
		}
		uint16_t sumd = 0, sump = 0;
		uint8_t rcd[MAXN], idx = 0;
		for (typeof(N)i = 1; i <= N; ++i)
			if (slc[M][ans][i]) {
				sumd += d[i];
				sump += p[i];
				rcd[idx++] = i;
			}

		cout << "Jury #" << (uint16_t)++cnt << "\nBest jury has value " << sump << " for prosecution and value " << sumd << " for defence:\n";
		for (typeof(idx)i = 0; i < idx; ++i)
			cout << ' ' << (uint16_t)rcd[i];
		cout << "\n\n";
	}
	return 0;
}
```

---

## 作者：block_in_mc (赞：1)

## 题目大意

有 $n$ 个人，每个人有两个 $0$ 至 $20$ 之间的属性 $(d,p)$，从中选出 $m$ 个，使得 $|\sum d-\sum p|$ 最小，在此基础上，使 $\sum d+\sum p$ 最大。

## 解题思路

我们用 $dp_{i,j,k}$ 代表从前 $i$ 个人中选出 $j$ 个人，且 $\sum d-\sum p=k$ 时 $\sum d+\sum p$ 的最大值。由于 $\sum d-\sum p$ 可能小于 $0$，这里我们将其加上 $400$ 防止访问到小于 $0$ 的下标。

初始时，$dp_{0,0,400}=0$，其余为 $-\inf$，类似于 01-背包，我们枚举第 $i$ 个人是否被选择，状态转移方程容易推出：

$$dp_{i,j,k}=\max\{dp_{i-1,j,k},dp_{i-1,j-1,k-(d_i-p_i)}\}$$

枚举 $i,j,k$ 进行转移即可，同时注意判断 $k-(d_a-p_a)$ 是否在 $0$ 到 $800$ 之间，防止 RE。类似于 01-背包，第一维可以省略。

显然，若 $dp_{n,m,k}<0$，则不存在一种方案使得 $|\sum d-\sum p|=k$。为了找到满足条件的答案，我们枚举 $0\le i\le 400$，若 $dp_{n,m,400-i}$ 和 $dp_{n,m,400+i}$ 有至少一个大于等于 $0$，则记录其中较大的一个的 $400+i$ 或 $400-i$ 的值（记为 $ans$），并退出循环。此时的 $|ans-400|$ 即为 $|\sum d-\sum p|$ 的最小值，$dp_{n,m,ans}$ 即为 $\sum d+\sum p$ 的最大值。

接下来还要统计 $\sum d$ 和 $\sum p$ 并输出方案。我们再定义一个数组 $pre$，其中 $pre_{i,j,k}$ 代表 $dp_{i,j,k}$ 选择的编号最大的人。在求 $dp$ 数组时顺便求出 $pre$ 数组。具体地：

- 若 $dp_{i,j,k}$ 由 $dp_{i-1,j,k}$ 转移而来，则 $pre_{i,j,k}=pre_{i-1,j,k}$；
- 否则 $pre_{i,j,k}=i$。

接下来我们考虑如何从找到的答案 $dp_{n,m,ans}$ 递推出答案。令 $s=pre_{n,m,ans}$，首先，$s$ 一定被选择，然后考虑选择 $s$ 前状态如何表示，不难发现为 $dp_{s-1,m-1,ans-(d_s-p_s)}$，再将 $s$ 视为 $pre_{s-1,m-1,ans-(d_s-p_s)}$，不断重复此过程直到 $m=0$。

同时，注意本题特别的输出格式。

- 输出方案时，先输出空格，再输出编号；
- 输出方案时，编号要从小到大排序；
- 两个测试数据的输出间有一个换行。

AC 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, d[202], p[202], dp[25][810], pre[210][25][810];
int main() {
    for (int _ = 1; true; _++) {
        memset(dp, 0xcf, sizeof dp);
        memset(pre, 0, sizeof pre);
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) break;
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &d[i], &p[i]);
        dp[0][400] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= 1; j--)
                for (int k = 0; k <= 800; k++)
                    if (k - d[i] + p[i] >= 0 && k - d[i] + p[i] <= 800 && dp[j - 1][k - (d[i] - p[i])] + d[i] + p[i] > dp[j][k])
                        dp[j][k] = dp[j - 1][k - d[i] + p[i]] + d[i] + p[i], pre[i][j][k] = i;
                    else pre[i][j][k] = pre[i - 1][j][k];
        int ans = 0;
        for (int i = 0; i <= 400; i++) {
            if (dp[m][400 - i] < 0 && dp[m][400 + i] < 0) continue;
            if (dp[m][400 - i] > dp[m][400 + i]) ans = 400 - i;
            else ans = 400 + i;
            break;
        }
        int i = pre[n][m][ans], j = m, k = ans, sumd = 0, sump = 0;
        vector<int> res;
        while (j) {
            res.push_back(i);
            sumd += d[i], sump += p[i], k -= d[i] - p[i];
            i = pre[i - 1][--j][k];
        }
        sort(res.begin(), res.end());
        printf("Jury #%d\n", _);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", sumd, sump);
        for (int id : res) printf(" %d", id);
        printf("\n\n");
    }
    return 0;
}
```

---

## 作者：松鼠的星星 (赞：1)

## 题目大意
从 $n$ 个人中选出 $m$ 个人组成陪审团，要求如下：控方和辩方分别给每个人打分，第 $i$ 个人的辩方得分和控方得分分别是 $a_i$ 和 $b_i(a_i,b_i \in [0,20])$。设选出的 $m$ 个人的辩、控总分分别为 $A,B$，输出所有方案中 $\left\vert A-B\right\vert$ 最小的方案，若方案不唯一，则输出其中 $A+B$ 最大的方案。

## 分析
很明显，这是一道 0/1 背包问题，我们把 $n$ 个人看作 $n$ 个物品，那么每个物品有如下三种体积：
- $1$：每个人对容积的贡献是 $1$。
- 辩方得分：即 $a_i$。
- 控方得分：即 $b_i$。

然后依次考虑每个人的选或不选，用一个布尔型的数组 $dp_{j,x,y}$ 表示在选中 $j$ 个人的情况下，辩方总分 $x$，控方总分为 $y$ 是否可行，转移方程为
$$dp_{j,x,y}=dp_{j,x,y} \operatorname{or} dp_{j-1,x-a_i,y-b_i}$$
我们最后要找的就是状态 $dp_{j,x,y}$，满足 $dp_{j,x,y}=true$，且 $\left\vert A-B\right\vert$ 最小，当其相同时 $A+B$ 最大。

但这样并没有用到价值，因为我们只考虑 $\left\vert A-B\right\vert$ 相同时的最小 $A+B$ 的值，所以可以将辩、控双方得分之和作为价值。现在记 $dp_{j,k}$ 为在选中 $j$ 个人的情况下，辩控双方总分之差为 $k$ 时的总分之和最大值。
$$dp_{j,k}=max(dp_{j,k},dp_{j-1,k-(a_i-b_i)}+(a_i+b_i))$$

本题还要求输出方案，我们可以使用 $s_{i,j,k}$ 表示当外循环到 $i$ 时，$dp_{j,k}$ 是从哪里得到的。然后递归得到方案，直到 $j=0$ 的时候。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200 + 10;
const int MAXM = 20 + 10;
const int ADD = 400;
int n, m;
int a[MAXN];
int b[MAXN];
int dp[MAXM][(ADD << 1) + 10];
int s[MAXN][MAXM][(ADD << 1) + 10];
vector<int> ans;
int suma, sumb;
void get_p(int i, int j, int k)
{
    if (!j) return;
    int t = s[i][j][k];
    suma += a[t];
    sumb += b[t];
    get_p(t - 1, j - 1, k - (a[t] - b[t]));
    ans.push_back(t);
}
int main()
{
    int T = 0;
    while (true)
    {
        cin >> n >> m;
        if (!n && !m)
            break;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i] >> b[i];
        }
        ans.clear();
        suma = sumb = 0;
        memset(dp, 0xcf, sizeof(dp));
        dp[0][ADD] = 0;
        for (int i = 1; i <= n; i++)
        {
            memcpy(s[i], s[i - 1], sizeof(s[i]));
            for (int j = m; j > 0; j--)
            {
                for (int k = 0; k <= (ADD << 1); k++)
                {
                    if (k - (a[i] - b[i]) < 0 || k - (a[i] - b[i]) > (ADD << 1)) continue;
                    if (dp[j][k] < dp[j - 1][k - (a[i] - b[i])] + a[i] + b[i])
                    {
                        dp[j][k] = dp[j - 1][k - (a[i] - b[i])] + a[i] + b[i];
                        s[i][j][k] = i;
                    }
                }
            }
        }
        int tmp = 0;
        for (int k = 0; k <= ADD; k++)
        {
            if (dp[m][ADD + k] >= 0 && dp[m][ADD + k] >= dp[m][ADD - k])
            {
                tmp = k + ADD;
                break;
            }
            if (dp[m][ADD - k] >= 0)
            {
                tmp = ADD - k;
                break;
            }
        }
        get_p(n, m, tmp);
        cout << "Jury #" << ++T << endl;
        cout << "Best jury has value " << suma << " for prosecution and value " << sumb << " for defence:\n";
        for (int i : ans) cout << " " << i;
        cout << endl << endl;
    }
    return 0;
}
```

---

## 作者：yaoxiangyuan (赞：1)

### 1.题意：
从 $n $个人中选出 $m$ 个，每个人有固定的 $ p$ 值，$d $  值，要求使 $ m $ 个人的 $p $ 总和 $d$ 。 $ A $ 总和的差的绝对值最小，若有多解则取两者和最大的。


------------

### 2.分析：$dp$



 $f[i][j]$  表示在选  $ m $ 个人中的第 $i$ 个人的时候使所有已选中的人的 $p , d$ 差为 $j$ 时，所能获得的 $p ,d $最大和。

  $f[i+1][j+p[k]-d[k] ] =f[i][j]+p[k]+d[k]; $
  
  (要求 $k$ 之前没有选过，要查看  $ f[i][j]$  的完整路径，确保无  $k$ 。)

填写完成后，观察 $ f[m]$ 找到最小差值，最大和。知道和差自然可以求出总的 $ p , d$  。


------------

## 3.AC代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define maxn 205
#define maxm 25

int n, m, w;
int f[maxm][maxn *10];
int p[maxn], d[maxn];
int path[maxm][maxn *10];
bool vis[maxn];
int stk[maxn];

void input()
{
    for (int i =0; i < n; i++)
        scanf("%d%d", &p[i], &d[i]);
}

void getpath(int i, int j)
{
    memset(vis, 0, sizeof(vis));
    while (path[i][j] !=-1)
    {
        int k = path[i][j];
        vis[k] =true;
        i--;
        j -= p[k] - d[k];
    }
}

void make(int i, int j, int k)
{
    int a = p[k] + d[k];
    int b = p[k] - d[k];
    if (f[i +1][j + b] ==-1|| f[i +1][j + b] < f[i][j] + a)
    {
        f[i +1][j + b] = f[i][j] + a;
        path[i +1][j + b] = k;
        return;
    }
}

void work()
{
    w = m *20;
    memset(f, -1, sizeof(f));//初始化全为-1
    memset(path, -1, sizeof(path));
    f[0][w] =0;
    for (int i =0; i < m; i++)
        for (int j =0; j <=2* w; j++)
            if (f[i][j] !=-1)
            {
                getpath(i, j);//得到路径
                for (int k =0; k < n; k++)
                    if (!vis[k])
                        make(i, j, k);
            }
    int d1 =-1, d2 =-1, dd;
    for (int i =0; i <= w; i++)
        if (f[m][w + i] !=-1)
        {
            d1 = i;
            break;
        }
    for (int i =0; i <= w; i++)
        if (f[m][w - i] !=-1)
        {
            d2 = i;
            break;
        }
    if (d1 ==-1|| (d2 < d1 && d2 !=-1))
        dd = w - d2;
    else if (d2 ==-1|| (d1 < d2 && d1 !=-1))
        dd = w + d1;
    else if (f[m][w + d1] > f[m][w - d2])
        dd = w + d1;
    else
        dd = w - d2;
    int a = f[m][dd];
    int b = dd - w;
    int ansp = (a + b) /2;
    int ansd = (a - b) /2;
    printf("Best jury has value %d for prosecution and value %d for defence:\n", ansp, ansd);
    int top =0;
    a = m;
    b = dd;
    while (path[a][b] !=-1)
        {
            int k = path[a][b];
            stk[top++] = k;
            a--;
            b -= p[k] - d[k];
        }
    sort(stk, stk + top);
    for (int i =0; i < top; i++)
        printf(" %d", stk[i] +1);
    putchar('\n');
    putchar('\n');
}

int main()
{
	int t =0;
    while (scanf("%d%d", &n, &m), n | m)//多组数据
    {
        t++;
        printf("Jury #%d\n", t);
        input();//读入
        work();//开始dp
    }
    return 0;
}
```


---

## 作者：kkkfc0114514 (赞：0)

# 题目分析
这是一个有很多个维度的 01 背包。把 $N$ 个候选人看作 $N$ 个物品。那么，这 $N$ 个物品有三种体积：

- “人数”，每个人的人数都是 $1$，最终要填满容量为 $M$ 的背包。
- “辩方得分”，辩方打的分数 $d_i$。
- “控方得分”，控方打的分数 $p_i$。

考虑按照人数划分阶段。当枚举完前 $i$ 个人时，设 $f_{j,d,p}$ 表示有 $j$ 个人进入陪审团，当前辩方总分 $d$，控方总分 $p$ 的状态是否可行，则：
$$
f_{j,d,p} = f_{j,d,p}\ or\ f_{j-1,d-d_i,p-p_i}
$$
初始时 $f_{0,0,0} = 1$，其余的为 $0$。目标是找到一个状态 $f_{M,D,P}$，使得 $f_{M,D,P} = 1$，且 $\left|D-P\right|$ 尽量小，$\left|D-P\right|$ 相同时 $D+P$ 尽量大。

但是这种方法没有很好的利用 dp 中“价值”这一维度。事实上，可以把控方辩方的分差 $d_i - p_i$ 作为物品的体积之一，把控方辩方的分数和 $d_i + p_i$ 作为物品的价值。

设 $f_{i,j,k}$ 表示前 $i$ 个人中有 $j$ 个人进入了陪审团，此时辩方总分和控方总分的差为 $k$ 时，辩方总分和控方总分的和的最大值，则：
$$
f_{i,j,k} = \max(f_{i - 1,j,k},f_{i - 1,j - 1,k - (d_i - p_i)} + d_i + p_i)
$$
初始时 $f_{0,0,0} = 0$，其余为负无穷。目的是找到一个 $f_{N,M,K}$，使得 $|k|$ 尽量小，当 $|k|$ 相同时 $f_{N,M,K}$ 尽量大。

值得注意的是，$k$ 可能为负数，在实现时需要给 $k$ 加上一个固定值。

最后输出方案时，根据 $(N,M,K)$ 不断往前推即可，具体见代码。

# Code
```cpp
#include <bits/stdc++.h>
namespace SXL {
	using std::max;
	constexpr int MAXN = 200;
	constexpr int MAXM = 20;
	constexpr int MAXK = 800;
	constexpr int pyl = 400;
	int n,m;
	int d[MAXN + 5],p[MAXN + 5];
	int f[MAXN + 5][MAXM + 5][MAXK + 5];
	int tot;
	int cnt;
	int ans[MAXM + 5];
	void work() {
		memset(f,128,sizeof(f));
		tot = 0;
		for(int i = 1;i <= n;i++) {
			scanf("%d%d",d + i,p + i);
		}
		f[0][0][pyl] = 0;
		for(int i = 1;i <= n;i++) {
			for(int j = 0;j <= m;j++) {
				for(int k = 0;k <= MAXK;k++) {
					f[i][j][k] = f[i - 1][j][k];
					int c = k - d[i] + p[i];
					if(c < 0 || c > MAXK || j == 0) continue;
					f[i][j][k] = max(f[i][j][k],f[i - 1][j - 1][c] + d[i] + p[i]);
				}
			}
		}
		int v = 0;
		while(f[n][m][pyl + v] < 0 && f[n][m][pyl - v] < 0) v++;
		if(f[n][m][pyl - v] > f[n][m][pyl + v]) v = pyl - v;
		else v = pyl + v;
		int i = n,j = m;
		while(i) {
			if(f[i][j][v] == f[i - 1][j][v]) {
				i--;
				continue;
			}
			ans[++tot] = i;
			v = v - d[i] + p[i];
			i--;
			j--;
		}
		int a1 = 0,a2 = 0;
		for(int i = 1;i <= tot;i++) {
			a1 += d[ans[i]];
			a2 += p[ans[i]];
		}
		printf("Jury #%d\n",++cnt);
		printf("Best jury has value %d for prosecution and value %d for defence:\n",a1,a2);
		for(int i = tot;i >= 1;i--) {
			printf(" %d",ans[i]);
		}
		puts("");
		puts("");
	}
	void main() {
		while(true) {
			scanf("%d%d",&n,&m);
			if(!n && !m) break;
			work();
		}
	}
}
int main() {
	SXL::main();
	return 0;
}
```

---

## 作者：z_yq (赞：0)

# #1.简单题意
有 $n$ 个数对 $(d_i,p_i)$ 要取出 $m$ 对，使选出的 $\left| \sum\limits_{i=1}^md_i - \sum\limits_{i=1}^mp_i \right|$ 最小的情况下 $\sum\limits_{i=1}^md_i + \sum\limits_{i=1}^mp_i$ 最大。
# #2. 做法
定义 $dp_{i,j,k}$ 表示考虑到第 $i$ 对数，前面选了 $j$ 对，$ \sum\limits_{i=1}^md_i - \sum\limits_{i=1}^mp_i +400 = k$ 时，$\sum\limits_{i=1}^md_i - \sum\limits_{i=1}^mp_i$ 的最大值，这个定义唯一可能需要解释的是 $k$，毕竟想到如何表示 $\left| \sum\limits_{i=1}^md_i - \sum\limits_{i=1}^mp_i \right|$ 是一个问题，所以我们可以将 $\left| \sum\limits_{i=1}^md_i - \sum\limits_{i=1}^mp_i \right|$ 变成 $\left| \sum\limits_{i=1}^md_i - \sum\limits_{i=1}^mp_i +400\right|$ 正因为 $\left| \sum\limits_{i=1}^md_i - \sum\limits_{i=1}^mp_i \right| \le 400$ 所以我们可以把它增加 $400$，于是，我们就可以把绝对值拆了。\
然而，状态转移式更好推,如果我们选，则：$dp_{i,j,k}=dp_{i-1,j-1,k-p_i+d_i}+p_i+d_i$ 如果不选就是 $dp_{i,j,k}=dp_{i-1,j,k}$ 中间取最大值即可。
# #3.Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=210,M=810,P=400;
ll p[N],d[N],a[N],n,m,dp[N][25][900],rd[N],cnt;
int main()
{
    while(cin>>n>>m)
    {
        cnt++;
        if(n==0 && m==0) break;
        for(int i=1;i<=n;i++)
            cin>>p[i]>>d[i];
        memset(dp,-0x3f,sizeof(dp));
        dp[0][0][P]=0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=m;j++)
                for(int k=0;k<M;k++)
                {
                    dp[i][j][k]=dp[i-1][j][k];
                    if(j>=1 && (k-p[i]+d[i])>=0 && (k-p[i]+d[i])<=800)
                        dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-1][k-p[i]+d[i]]+p[i]+d[i]);
                }
        ll id=0;
        while(dp[n][m][P+id]<0 && dp[n][m][P-id]<0) id++;
        if(dp[n][m][P+id]<dp[n][m][P-id]) id=P-id;
        else id=P+id;
        ll i=n,j=m,tmp_cnt=0;
        while(j)
        {
            if(dp[i][j][id]==dp[i-1][j][id]) i--;
            else
            {
                rd[++tmp_cnt]=i;
                id-=p[i]-d[i];
                i--;j--;
            }
        }
        ll sum_p=0,sum_d=0;
        for(int i=1;i<=tmp_cnt;i++)
            sum_p+=p[rd[i]],sum_d+=d[rd[i]];
        printf("Jury #%lld\nBest jury has value %lld for prosecution and value %lld for defence:\n",cnt,sum_p,sum_d);
        sort(rd+1,rd+tmp_cnt+1);
        for(int i=1;i<=tmp_cnt;i++)
            cout<<" "<<rd[i];
        cout<<"\n\n";
    }
    return 0;
}
```

---

## 作者：niuzh (赞：0)

## 思路

此题是一道 $01$ 背包。

考虑令 $dp_{i,j,k}$ 表示所有在前 $i$ 个人中选 $j$ 个人且差值为 $k$ 的最大总分。

这里的 $-400\le k\le400$，所以考虑 $+400$ 的偏移。

然后，对每个人只有选或不选两种情况：

- 选第 $i$ 人：$dp_{i-1,j-1,k-(p_i-d_i)}+d_i+p_i$ 注意，$k$ 减后的差值有可能越界。

- 不选第 $i$ 人：$dp_{i-1,j,k}$。

最后考虑具体方案，只需从最后往前倒退即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200+10,M=800+10,K=20+10,base=400;
int d[N],p[N],dp[N][K][M],ans[N],cnt=0;
int main()
{
	int n,m,T=1;
	while (cin>>n>>m,n||m)
	{
		if(!n&&!m)
		{
			break;
		}
		for (int i=1; i<=n; i++)
		{
			cin>>p[i]>>d[i];
		}
		memset(dp,-0x3f,sizeof(dp));
		dp[0][0][base]=0;
		for (int i=1; i<=n; i++)
		{
			for (int j=0; j<=m; j++)
			{
				for (int k=0; k<M; k++)
				{
					dp[i][j][k]=dp[i-1][j][k];
					int c=k-p[i]+d[i];
					if (j-1<0||c<0||c>800)
					{
						continue;
					}
					else
					{
						dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-1][c]+p[i]+d[i]);
					}
				}
			}
		}
		int v=0;
		while (dp[n][m][base+v]<0&&dp[n][m][base-v]<0)
		{
			v++;
		}
		if (dp[n][m][base-v]>dp[n][m][base+v])
		{
			v=base-v;
		}
		else
		{
			v=base+v;
		}
		int i=n,j=m,dcnt=0,pcnt=0;
		cnt=0;
		while (j)
		{
			if (dp[i][j][v]==dp[i-1][j][v]) i--;
			else
			{
				ans[++cnt]=i;
				v-=(p[i]-d[i]);
				i--;
				j--;
			}
		}
		for (int i=1; i<=cnt; i++)
		{
			dcnt+=d[ans[i]];
			pcnt+=p[ans[i]];
		}
		printf("Jury #%d\n",T++);
		printf("Best jury has value %d for prosecution and value %d for defence:\n",pcnt,dcnt);
		for (int i=1; i<=cnt; i++)
		{
			cout<<" "<<ans[cnt-i+1];
		}
		cout<<"\n\n";
	}
	return 0;
}
```

---

## 作者：Otue (赞：0)

发现大家代码写长了....
## 思路
这是一个具有多个维度的 $0/1$ 背包问题。把 $N$ 个候选人看成 $N$ 个物品，那么每个物品都有如下三种体积：

* "人数" ，每个 "候选人" 的 "人数" 都是 $1$ 。最终要填满容积为 $M$ 的背包。
* "辩方得分"，即辩方给该候选人打的分数 $a_i$。
* "控方得分"，即控方给该候选人打的分数 $b_i$。

因此，我们一次考虑每个候选人是否选入评审团，当外层循环到 $i$ 时，表示已经考虑了前 $i$ 个人的入选情况，此时用 `bool` 类型的数组 $dp_{j,d,p}$ 表示有 $j$ 个人选入评审团，当前辩方总分为 $d$，控方总分 $p$ 的状态是否可行。可以得出如下方程：

$$\large dp_{j,d,p}=dp_{j,d,p} \  \text{or} \ dp_{j-1,d-a_i,p-b_i}$$


上述算法并没有合理运用背包 "价值" 这一维度，还有很多优化空间。事实上，我们并不需要关心双方得分，只需要关心差值。

设 $dp_{i,j,k}$ 表示前 $i$ 个候选人选了 $j$ 个，且辩方减控方差值为 $k$ 时，双方总和的最大值。有如下转移方程：

$$\large dp_{i,j,k}=\max\{dp_{i-1,j,k},dp_{i-1,j-1,k-(a_i-b_i)}+a_i+b_i\}$$

目标：找到一个 $dp_{n,m,k}$，满足 $k$ 尽量小，当 $|k|$ 相同时使得 $dp_{n,m,k}$ 尽量大即可。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 205, M = 810, base = 400;  // base是一个偏移量，避免差值负数

int n, m, p[N], d[N], dp[N][25][M];
int ans[N], l, T;

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        for (int i = 1; i <= n; i++) cin >> p[i] >> d[i];
        memset(dp, -0x3f, sizeof dp);
        dp[0][0][base] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= M - 5; k++) {
                    dp[i][j][k] = dp[i - 1][j][k];
                    int t = k - (p[i] - d[i]);
                    if (t < 0 || t > M - 5) continue;
                    if (j >= 1) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k - (p[i] - d[i])] + p[i] + d[i]);
                }
            }
        }
        int id = 0;
        while (dp[n][m][base - id] < 0 && dp[n][m][base + id] < 0) id++;  // 找到最小的k
        if (dp[n][m][base - id] > dp[n][m][base + id]) id = base - id;  // 还需要找到最大的方案
        else id = base + id;
        l = 0;
        int i = n, j = m, k = id;  // 开始倒推
        while (j) {
            if (dp[i][j][k] == dp[i - 1][j][k]) i--;
            else {
                ans[++l] = i;
                k -= p[i] - d[i];
                i--, j--;
            }
        }
        int res1 = 0, res2 = 0;
        for (int i = 1; i <= l; i++) {
            res1 += p[ans[i]];
            res2 += d[ans[i]];
        }
        printf("Jury #%d\n", ++T);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", res1, res2);
        sort(ans + 1, ans + l + 1);
        for (int i = 1; i <= l; i++) cout << ' ' << ans[i];
        puts("\n");
    }
}
```

---

