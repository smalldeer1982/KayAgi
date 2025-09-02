# Exam Cheating

## 题目描述

Zane and Zane's crush have just decided to date! However, the girl is having a problem with her Physics final exam, and needs your help.

There are $ n $ questions, numbered from $ 1 $ to $ n $ . Question $ i $ comes before question $ i+1 $ ( $ 1<=i&lt;n $ ). Each of the questions cannot be guessed on, due to the huge penalty for wrong answers. The girl luckily sits in the middle of two geniuses, so she is going to cheat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796E/ceab15f307581fef6fd702c5ce09caac57a65378.png)However, the geniuses have limitations. Each of them may or may not know the answers to some questions. Anyway, it is safe to assume that the answers on their answer sheets are absolutely correct.

To make sure she will not get caught by the proctor, the girl will glance at most $ p $ times, each time looking at no more than $ k $ consecutive questions on one of the two geniuses' answer sheet. When the girl looks at some question on an answer sheet, she copies the answer to that question if it is on that answer sheet, or does nothing otherwise.

Help the girl find the maximum number of questions she can get correct.

## 说明/提示

Let $ (x,l,r) $ denote the action of looking at all questions $ i $ such that $ l<=i<=r $ on the answer sheet of the $ x $ -th genius.

In the first sample, the girl could get $ 4 $ questions correct by performing sequence of actions $ (1,1,3) $ and $ (2,5,6) $ .

In the second sample, the girl could perform sequence of actions $ (1,3,5) $ , $ (2,2,4) $ , and $ (2,6,8) $ to get $ 7 $ questions correct.

## 样例 #1

### 输入

```
6 2 3
3 1 3 6
4 1 2 5 6
```

### 输出

```
4```

## 样例 #2

### 输入

```
8 3 3
4 1 3 5 6
5 2 4 6 7 8
```

### 输出

```
7```

# 题解

## 作者：wsyhb (赞：13)

## 前言

**截止本文发布前，本题题解区的其它所有题解均会被下列这组数据 Hack 掉**：

``` cpp
Input
10 5 4
3 1 5 9
3 2 6 10
Output
5
```

容易发现这组数据合法（且**官方给出的 std 能通过这组数据**），但其它题解均会输出 $6$，**具体错误原因后文会详细说明**。

另外，这道 DP 题的**转移方程其实可以非常简单**，并不需要像官方题解或者其它题解那么复杂，**本文的转移方程极其简单乃至可以称为本题最简单的题解**。
## 分析 + 题解

简单尝试后可以发现，本题不能纯贪心，考虑 **DP**。

为了方便，我们用 bool 值 $a_i$ 表示第一个人是否有第 $i$ 题的答案，第二个人用 $b_i$ 同理表示。

考虑 DP 状态：

首先需要两维来记录**当前讨论的题数**和**当前剩余偷看的次数**。其次，由于一次偷看可以看连续的 $k$ 道题，我们还需分别记录**当前这次还能偷看两个人的题数**。

更具体地，我们设 $dp[i][j][l][r]$ 表示考虑前 $i$ 道题，当前剩余偷看次数为 $j$，且能偷看第一个人 $l$ 道题，第二个人 $r$ 道题时，可以获得答案的最多题数。

初始时，$dp[0][p][0][0]=0$，其余 $dp$ 值为 $-inf$。

考虑 DP 转移：

一是**不使用**新的偷看次数，那么多做对一道题当且仅当，$a_i$ 为 `true` 且 $l>0$，与 $b_i$ 为 `true` 且 $r>0$ 中至少有一个成立，即：

$$dp[i][j][l][r]+ ((l>0 \; and \; a_i) \; or \; (r>0 \; and \; b_i)) \to dp[i+1][j][\max(l-1,0)][\max(r-1,0)]$$

二是**使用**新的偷看次数，根据贪心策略，若 $a_i$ 为 `true` 才对第一个人使用，若 $b_i$ 为 `true` 才对第二个人使用，即：

$$(if \; a_i \; and \; j>0) \; dp[i][j][l][r]+1 \to dp[i+1][j-1][k-1][\max(r-1,0)]$$

$$(if \; b_i \; and \; j>0) \; dp[i][j][l][r]+1 \to dp[i+1][j-1][\max(l-1,0)][k-1]$$

最终答案即为 $\max\{dp[n][j][l][r]\}$。

此时**时间和空间复杂度**均为 $O(npk^2)$，不足以通过此题。

**空间复杂度**可以通过**滚动数组**优化至 $O(pk^2)$，但时间复杂度如何优化呢？

注意到**若 $p$ 足够大**，我们可以采取“不看白不看”的策略，**将两个人的每一道题看完**，此时答案即为 $\sum_{i=1}^n (a_i \; or \; b_i)$。那么“足够大”的条件是什么呢？

其他题解给出的条件是 $pk \ge 2n$，这是**错误的**，前言中给出的 Hack 数据就是一个例子——下面这张图描述了这组数据给出的信息：

![](https://cdn.luogu.com.cn/upload/image_hosting/arvev74k.png)

可以发现，这组数据需要至少 $2 \lceil \dfrac{n}{k} \rceil =6$ 次才能看完尽可能多的答案，而并非 $\lceil \dfrac{2n}{k} \rceil=5$ 次，因此，**正确的**条件为 $p \ge 2 \lceil \dfrac{n}{k} \rceil$。（$p$ 的**数量级仍为** $\dfrac{n}{k}$）

**时间复杂度** $O(npk^2)$ 至此被优化成了 $O(n^2k)$，足以通过此题。

## 代码

转移方程已在前文完整列出，优化方法也已在前文讲解，代码就真的很好写了~

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e3+5;
const int max_p=1e3+5;
const int max_k=50+5;
bool a[max_n],b[max_n];
int dp[2][max_p][max_k][max_k];
inline void check_max(int &x,int y)
{
	x=max(x,y);
}
int main()
{
	int n,p,k;
	scanf("%d%d%d",&n,&p,&k);
	int r;
	scanf("%d",&r);
	for(int i=1;i<=r;++i)
	{
		int x;
		scanf("%d",&x);
		a[x]=true;
	}
	int s;
	scanf("%d",&s);
	for(int i=1;i<=s;++i)
	{
		int x;
		scanf("%d",&x);
		b[x]=true;
	}
	if(p>=2*((n+k-1)/k))
	{
		int ans=0;
		for(int i=1;i<=n;++i)
			ans+=a[i]|b[i];
		printf("%d\n",ans);
		return 0;
	}
	for(int j=0;j<=p;++j)
		for(int l=0;l<k;++l)
			for(int r=0;r<k;++r)
				dp[0][j][l][r]=-1e9;//记得赋初值为 -inf 
	dp[0][p][0][0]=0;
	for(int i=1;i<=n;++i)
	{
		int y=i&1,x=y^1;//滚动数组下标，由 x 向 y 转移 
		for(int j=0;j<=p;++j)
			for(int l=0;l<k;++l)
				for(int r=0;r<k;++r)
					dp[y][j][l][r]=-1e9;//记得赋初值为 -inf 
		for(int j=0;j<=p;++j)
			for(int l=0;l<k;++l)
				for(int r=0;r<k;++r)
				{
					if(dp[x][j][l][r]>=0)
					{
						check_max(dp[y][j][max(l-1,0)][max(r-1,0)],dp[x][j][l][r]+((l>0&&a[i])||(r>0&&b[i])));
						if(j>0)
						{
							if(a[i])
								check_max(dp[y][j-1][k-1][max(r-1,0)],dp[x][j][l][r]+1);
							if(b[i])
								check_max(dp[y][j-1][max(l-1,0)][k-1],dp[x][j][l][r]+1);
						}
					}
				}
	}
	int x=n&1,ans=0;
	for(int j=0;j<=p;++j)
		for(int l=0;l<k;++l)
			for(int r=0;r<k;++r)
				ans=max(ans,dp[x][j][l][r]);
	printf("%d\n",ans);
	return 0;
}
/*
10 5 4
3 1 5 9
3 2 6 10
*/
```

---

## 作者：feecle6418 (赞：6)

# 全新 $O(N^2)$ 做法，与 $k$ 无关！！！！1

以下，用 $n,p,k$ 等小写字母表示变量，$N,P,K$ 表示题目中输入的数。

首先有一个 dp，设 $f(i,p,q,cnt)$ 表示 $1\sim i$ 中用了 $cnt$ 次偷看次数，两边当前还未结束的偷看区间分别剩了 $p,q$ 次，这时 $1\sim i$ 至多能看多少题。这个 dp 是 $O(NPK^2)$ 的，无法通过。

接下来有两条优化的路子。

- 法一（题解做法）：注意到，若 $P\ge 2\lceil \dfrac{N}{K}\rceil$ 则一定能把所有题答案看完。所以 $P$ 的范围是 $O(\dfrac{N}{K})$ 的，所以总 dp 复杂度是 $O(N^2K)$ 的，所以直接卡个上界就能通过本题。
- 法二：注意到，只有 $p=0$ 或 $q=0$ 的状态是有用的。这基于，只有在用完了某一边的偷看时长后，才可能会在这边新开。所以，不会在 $p>0$ 且 $q>0$ 的状态新开偷看。因此，只转移 $p=0/q=0$ 的状态，就直接 $O(NPK)$ 了。

结合以上两个优化，就可以做到 $O(NPK)=O(N^2)$！

具体地，状态如下：

- $f(i,k,j,0/1)$ 表示 $1\sim i$，目前某一边还剩 $k$ 次偷看，另一边还剩 $0$ 次偷看，总共用了 $j$ 次偷看，$k$ 记录的是第一个人 / 第二个人的方案数。

转移（具体转移时加上的代价比较繁琐，如果不理解可以对照下面的代码模拟，以下方程中直接用 $C$ 代替了）：

- $f(i,0,j,0)\to f(i,0,j,1),f(i,0,j,1)\to f(i,0,j,0)$（这两个状态是等价的，互相取个 max）
- $f(i,k,j,a)\to f(i+1,\max(k-1,0),j,a)$（直接往前延伸）
- $f(i,k,j,a)\to f(i+k,K-k,j+1,1-a)+C$（把另一边新开一段）

总时间复杂度 $O(N^2)$。下面的代码总用时仅 1.7s，在 2021.10.25 是洛谷最优解、cf 第一页的前一半。

```cpp
#include<bits/stdc++.h>
using namespace std;
int s1[1005],s2[1005],s[1005],S[1005],n,p,m,n1,n2;
void upd(short &x,short y){
	x=max(x,y);
}
int main(){
	cin>>n>>p>>m>>n1;
	for(int i=1,x;i<=n1;i++)cin>>x,s1[x]++;
	cin>>n2;
	for(int i=1,x;i<=n2;i++)cin>>x,s2[x]++;
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(S[i]=s1[i]|s2[i]);
	if(p>(n+m-1)/m*2)return cout<<s[n],0;
	vector<vector<vector<short>>> f[2];
	for(int o=0;o<2;o++){
		f[o].resize(n+2);
		for(int i=0;i<=n+1;i++){
			f[o][i].resize(m+2);
			for(int j=0;j<=m;j++)f[o][i][j].resize(p+2);
		}
	}
	short ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i&&j<=p;j++){
			upd(f[0][i][0][j],f[1][i][0][j]);
			upd(f[1][i][0][j],f[0][i][0][j]);
			for(int k=0;k<=m;k++){
				if(k)f[0][i][k][j]+=s1[i],f[1][i][k][j]+=s2[i];
				upd(f[0][i+1][max(k-1,0)][j],f[0][i][k][j]);
				upd(f[1][i+1][max(k-1,0)][j],f[1][i][k][j]);
				upd(f[1][min(i+k,n)][m-k][j+1],f[0][i][k][j]+s[min(i+k,n)-1]-s[i]+((!s1[i]||!k)&&S[i]));
				upd(f[0][min(i+k,n)][m-k][j+1],f[1][i][k][j]+s[min(i+k,n)-1]-s[i]+((!s2[i]||!k)&&S[i]));
				ans=max(ans,f[0][i][k][j]);
				ans=max(ans,f[1][i][k][j]);
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：littleseven (赞：3)

# CF 796E Exam Cheating

**题目链接：**[洛谷 CF 796E Exam Cheating](https://www.luogu.org/problem/CF796E)		[CF 796E Exam Cheating](https://codeforces.com/problemset/problem/796/E)

**算法标签:**  `DP`、`真的只有DP`

## 题目描述：

muronglin是个学渣，考试的时候，她一道题也不会做

她的左右桌分别是学霸chhokmah和学霸lukelin，虽然学霸并不是题题都会做，但他们做了的题一定都对

现在muronglin想要作弊，但是为了不被监考员抓住，她最多偷看p次，一次能看连续的k道题

给定n和la和lb，分别为题目总数，chhokmah做出题目数和lukelin做出题目数，再给出两位学霸做出题目序列，问muronglin最多能偷看到几道题的答案

## 题解：

> 题解中部分参考：https://www.luogu.org/blog/megaaspirin/solution-cf796e   
>
> 如有侵权请直接联系我撤回（qq 3364445435）

**DP**

这道题真的是有够折磨，本来看着很友好就准备开人生第二道黑题，可是这题是~~真友好~~啊！！！

考虑题目中两个人做出来的题可以开一个$a[x], b[x]$存起来，如果第 $k$ 题 $a$ 大神做过，那么 $a[k] = 1$，以此类推。

**状态**其实蛮好想到的：

- $dp[i][j][L][R]$ 表示当前为第$i$题，已经偷看了 $j$ 次，还能向左边的大神看 $L$ 道题，向右边的大神看 $R$ 道题。

**转移方程**开始就是这道题 ~~善意~~ 的所在了：

> 分类讨论（当前为第 $i$ 道题）：
>
> - 都不看，该次略过
> - 偷看左边
>   - 接上一次偷看
>   - 消耗一次次数重新看
> - 偷看右边
>   - 接上一次偷看
>   - 消耗一次次数重新看
> - 两边都看
>   - 左边
>     - 接上一次偷看
>     - 消耗一次次数重新看
>   - 右边
>     - 接上一次偷看
>     - 消耗一次次数重新看
>
> [ 酸爽.jpg ]

全！！！体！！！人！！！员！！！做！！！好！！！作！！！战！！！准！！！备！！！

设 $res$ 保存状态：

1. $res = dp[i - 1][j][L - 1][R - 1]$  无论你看不看，都要走到下一道题。
2. $res = dp[i][j][max(L-1, 0)][max(R-1, 0)]$ 都不看，下一题
3. $if (L)~~dp[i][j][L-1][max(R-1,0)] = max(itself, res+a[I])$ 左边可以接上一次看
4. $dp[i][j+1][k-1][max(R-1,0)]=max(itself,res+a[I])$ 左边消耗一次次数重新看
5. $if(L)~~dp[i][j+1][L-1][k-1] = max(itself, res+(a[I] | b[I]))$ 左边接着看，右边用一次次数看
6. $if(R)~~dp[i][j][max(L-1, 0)][R-1] = max(itself, res+b[I])$ 右边可以接上一次看
7. $dp[i][j+1][max(L-1, 0)][k-1]=max(itself, res+b[I])$ 右边消耗一次次数重新看
8. $if(R)~~dp[i][j+1][k-1][R-1] = max(itself,res+(a[I] | b[I]))$ 右边接着看，左边有一次次数看
9. $dp[i][j+2][k-1][k-1] = max(itself,res+(a[I]|b[I]))$ 左右都重新用一次次数看
10. $if(L \&\& R)~~dp[i][j][L-1][R-1] = max(itself, res+(a[I] | b[I]))$ 两边都可以接着看

你认为到这里差不多就结束了吗…………………………

仔细算一算，**M乐了~(MLE)~** ，我们会发现每一次转移这和上一次操作和本次操作有关，所以 $i$ 这一维是可以滚动掉的。

再仔细算一算，**T在偷偷乐~(TLE)~**，我们发现如果 $p*k \ge n \times 2$ ，我为啥要DP呢，我左一眼右一眼都看了不就得了………………

然后就真没有然后了，写挂的可以先盯着视力表看一会儿  [ 擦汗.jpg ]

## AC代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

const int M = 55;

const int inf = 0x3f3f3f3f;

char *p1, *p2, buf[100000];

#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1 ++ ) 

int rd() {
	int x = 0, f = 1;
	char c = nc();
	while (c < 48) {
		if (c == '-') {
			f = -1;
		}
		c = nc();
	}
	while (c > 47) {
		x = (((x << 2) + x) << 1) + (c ^ 48);
		c = nc();
	}
	return x * f;
}

int n, p, k, ans;

int a[N], b[N];

int dp[2][N][M][M];

int main() {
	n = rd(), p = rd(), k = rd();
	int numa = rd();
	for (int i = 1; i <= numa; i ++ ) {
		int x = rd();
		a[x] = 1;
	}
	int numb = rd();
	for (int i = 1; i <= numb; i ++ ) {
		int x = rd();
		b[x] = 1;
	}
	if (p * k >= n * 2) {
		for (int i = 1; i <= n; i ++ ) {
			ans += (a[i] | b[i]);
		}
		printf("%d\n", ans);
		return 0;
	}
	memset(dp, -inf, sizeof dp);
	dp[0][0][0][0] = 0;
	for (int I = 1; I <= n; I ++ ) {
		int i = I % 2, last = (I + 1) % 2;
		memset(dp[i], -inf, sizeof dp[i]);
		for (int j = 0; j <= p; j ++ ) {
			for (int L = 0; L <= k; L ++ ) {
				for (int R = 0; R <= k; R ++ ) {
					int res = dp[last][j][L][R];
					dp[i][j][max(L - 1, 0)][max(R - 1, 0)] = max(dp[i][j][max(L - 1, 0)][max(R - 1, 0)], res);
					if (L) {
						dp[i][j][L - 1][max(R - 1, 0)] = max(dp[i][j][L - 1][max(R - 1, 0)], res + a[I]);
						dp[i][j + 1][L - 1][k - 1] = max(dp[i][j + 1][L - 1][k - 1], res + (a[I] | b[I]));
					}
					if (R) {
						dp[i][j][max(L - 1, 0)][R - 1] = max(dp[i][j][max(L - 1, 0)][R - 1], res + b[I]);
						dp[i][j + 1][k - 1][R - 1] = max(dp[i][j + 1][k - 1][R - 1], res + (a[I] | b[I]));
					}
					if (L && R) {
						dp[i][j][L - 1][R - 1] = max(dp[i][j][L - 1][R - 1], res + (a[I] | b[I]));
					}
					dp[i][j + 1][k - 1][max(R - 1, 0)] = max(dp[i][j + 1][k - 1][max(R - 1, 0)], res + a[I]);
					dp[i][j + 1][max(L - 1, 0)][k - 1] = max(dp[i][j + 1][max(L - 1, 0)][k - 1], res + b[I]);
					dp[i][j + 2][k - 1][k - 1] = max(dp[i][j + 2][k - 1][k - 1], res + (a[I] | b[I]));
				}
			}
		}
	}
	for (int j = 0; j <= p; j ++ ) {
		for (int L = 0; L <= k; L ++ ) {
			for (int R = 0; R <= k; R ++ ) {
				ans = max(ans, dp[n % 2][j][L][R]);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：serene_analysis (赞：2)

似乎是 [feecle6418](https://www.luogu.com.cn/user/42156) 题解中提及的第二种做法的另一种写法，但是思路和优化有较大差异。

能过 [wsyhb](https://www.luogu.com.cn/user/145355) 的 hack 数据。

---

观察到 $n,p \leq 1000,k \le 50$，因此我们可以 $\mathcal{O}(n^2)$ 枚举对两个人偷看的左端点 $l,r$（这里的左端点指的是对于所有题而言选择的某道题的位置，并非给定序列中的某道题的位置，下同）再 $\mathcal{O}(k)$ 的判断两个区间重合了多少道题，设为 $both_{l,r}$，这一步是 $\mathcal{O}(n^2k)$ 的，为了后续的转移我们再设 $llen_{i},rlen_{i}$ 分别表示左端点为 $i$ 且不被对另一个人的偷看干扰时偷看第一个人/第二个人能看到的题数。

再观察一下可以得出两个简单而关键的结论：对同一个人的任意两次观察不会重叠；相同的观察按任何顺序进行得到的答案都是一样的。那么可以考虑设状态了。设 $mx_{i,j,l,0/1/2}$ 表示选择 $i$ 作为目前为止最靠右的左端点，已经进行了 $j$ 次选择，另一个人的最靠右的左端点为 $i-l$，第一个人/第二个人/两个人都选择 $i$ 最多能抄到的题数，我们来考虑一下转移。

首先看两个人都选。那么这时二者左端点相同，于是 $l=0$。根据我们的结论，上一个左端点 $i' \leq i-k$，二者都选需要两次操作故 $j'=j-2$，而对于上个状态的较靠左的最靠右的左端点则没有要求，同时选完之后会有 $llen_{i}+rlen_{i}-both_{i,i}$ 的贡献，故 $mx_{i,j,0,2}=(\max\limits_{1 \le i \le i-k,0 \le d \le k,0 \le id \le 2} mx_{i',j-2,d,id})+llen_{i}+rlen_{i}-both_{i,i}$。再考虑只选一个人，以选第二个人为例，那么分其从 $i-l$ 处转移而来和从 $i-k$ 及之前转移而来讨论，前者贡献是 $(\max\limits_{k-l \le d \le k} mx_{i-l,j-1,d,0})+rlen_{i}-both_{i-l,i}$ 意为前一个对第二个人的偷看和这个偷看不重叠的最优答案，后者贡献与两个人都选的分析几乎一模一样，是 $(\max\limits_{1 \le i \le i-k,0 \le d \le k,0 \le id \le 2} mx_{i',j-1,d,id})+rlen_{i}$。对二者取个 $\max$ 即可得到当前状态的答案，选第一个人同理。为了防止大家看晕贴个代码。

```cpp
for(int i=1;i<=n;i++)for(int j=1;j<=p;j++){
		if(j>=2){
			for(int ni=1;ni<=i-k;ni++)for(int d=0;d<=k;d++)mx[i][j][0][2]=std::max(
				{mx[i][j][0][2],mx[ni][j-2][d][0],mx[ni][j-2][d][1],mx[ni][j-2][d][2]});
			mx[i][j][0][2]+=llen[i]+rlen[i]-both[i][i];
		}
		for(int l=1;l<=k;l++){
			for(int ni=1;ni<=i-k;ni++)for(int d=0;d<=k;d++)mx[i][j][l][1]=std::max(
				{mx[i][j][l][1],mx[ni][j-1][d][0],mx[ni][j-1][d][1],mx[ni][j-1][d][2]});
			for(int ni=1;ni<=i-k;ni++)for(int d=0;d<=k;d++)mx[i][j][l][0]=std::max(
				{mx[i][j][l][0],mx[ni][j-1][d][0],mx[ni][j-1][d][1],mx[ni][j-1][d][2]});
			mx[i][j][l][1]+=rlen[i],mx[i][j][l][0]+=llen[i];
			if(i-l<0)continue;
			for(int d=k;d>=k-l;d--)mx[i][j][l][1]=std::max(mx[i][j][l][1],mx[i-l][j-1][d][0]+rlen[i]-both[i-l][i]);
			for(int d=k;d>=k-l;d--)mx[i][j][l][0]=std::max(mx[i][j][l][0],mx[i-l][j-1][d][1]+llen[i]-both[i][i-l]);
		}
	}
```

分析可知时间复杂度是 $\mathcal{O}(n^2pk^2)$ 的，需要优化。观察到无论当前状态最后一维是多少，我们都需要对 $mx$ 的第一维前缀、第二维某个位置和第三第四维所有位置求最值（下称第一种转移），这可以用前缀和优化。而剩下的那个循环则是第一、二、四维某个位置，第三维后缀求最值（下称第二种转移），这可以用后缀和优化。于是时间复杂度就被优化到了 $\mathcal{O}(npk)$。

然而还没有结束，空间复杂度也是 $\mathcal{O}(npk)$ 的，算一下就会发现 $\text{256MB}$ 装不下，又不能直接滚动数组，怎么办呢？观察到我们对具体值的关心仅限于 $[i-k,i]$，$i-k$ 前面的值都是前缀和（也即第一种转移），这个前缀和有两维都是取遍的，有一维可以在处理完 $i$ 之后动态加入，只有一维是真正需要保存的，于是这个数组就变成了 $\mathcal{O}(p)$ 的。至于第二种转移，我们可以通过维护第一维大小为 $2k$ 的数组来实现，设 $i$ 对 $2k$ 取模的余数为 $i$ 这个位置的信息在数组中的保存位置，那么这个余数加上或减去 $k$ 就是 $i-k$ 的保存位置，拿出来用即可，$i$ 算完就放到对应位置。还没完！你发现常数太大了过不去，怎么办？

注意这几点：具体实现时前缀和可以用后缀和替代；最后一维循环展开；$l=0$ 时只算最后一维为 $2$，反之只算最后一维为 $0/1$。这样大概就可以过了。当然还有最后用记录的数组统计答案而非在过程中统计，但是前面几点就够了。

时间复杂度 $\mathcal{O}(npk)$，空间复杂度 $\mathcal{O}(pk^2)$。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
const int maxn=1e3+5;
const int maxp=1e3+5;
const int maxk=55;
int n,p,k,gl,gr;
int lef[maxn],rig[maxn],lpt[maxn],rpt[maxn];
int llen[maxn],rlen[maxn];
int both[maxn][maxn];
int mmx[2*maxk][maxn][maxk][3],hmx[2*maxk][maxn][maxk][3];
int gmx[maxn][3];
int same(int lp,int rp){
	int ret=0;
	if(lp<=rp)for(int i=rp;i<=std::min(n,lp+k-1);i++)ret+=(lpt[i]&rpt[i]);
	else for(int i=lp;i<=std::min(n,rp+k-1);i++)ret+=(lpt[i]&rpt[i]);
	return ret;
}
int gid[maxn];
signed main(){
	scanf("%d%d%d%d",&n,&p,&k,&gl);
	for(int i=1;i<=gl;i++)scanf("%d",lef+i),lpt[lef[i]]=1;
	scanf("%d",&gr);
	for(int i=1;i<=gr;i++)scanf("%d",rig+i),rpt[rig[i]]=1;
	for(int i=1;i<=n;i++){
		gid[i]=(i-1)%(2*k)+1;
		for(int j=1;j<=n;j++)both[i][j]=same(i,j);
	}
	for(int i=1;i<=n;i++)for(int j=i;j<=std::min(n,i+k-1);j++)llen[i]+=lpt[j];
	for(int i=1;i<=n;i++)for(int j=i;j<=std::min(n,i+k-1);j++)rlen[i]+=rpt[j];
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=p;j++){
			for(int l=0;l<=k;l++){
				int zer=0,one=0,two=0;
				if(l==0)two=(j>=2?std::max({gmx[j-2][0],gmx[j-2][1],gmx[j-2][2]})+llen[i]+rlen[i]-both[i][i]:0),
					ans=std::max(ans,two),mmx[gid[i]][j][l][2]=two;
				else{
					zer=one=std::max({gmx[j-1][0],gmx[j-1][1],gmx[j-1][2]});
					one+=rlen[i],zer+=llen[i];
					if(i-l>=0){
						int nid=gid[i-l];
						zer=std::max(zer,hmx[nid][j-1][k-l][1]+llen[i]-both[i][i-l]),one=std::max(one,hmx[nid][j-1][k-l][0]+rlen[i]-both[i-l][i]);
					}
					ans=std::max({ans,zer,one});
					mmx[gid[i]][j][l][0]=zer,mmx[gid[i]][j][l][1]=one;
				}
			}
		}
		for(int j=1;j<=p;j++)for(int l=k;l;l--){
			hmx[gid[i]][j][l][0]=std::max(mmx[gid[i]][j][l][0],hmx[gid[i]][j][l+1][0]);
			hmx[gid[i]][j][l][1]=std::max(mmx[gid[i]][j][l][1],hmx[gid[i]][j][l+1][1]);
			hmx[gid[i]][j][l][2]=std::max(mmx[gid[i]][j][l][2],hmx[gid[i]][j][l+1][2]);
		}
		if(i-k+1>=1)for(int j=1;j<=p;j++)for(int id=0;id<=2;id++)
			gmx[j][id]=std::max(gmx[j][id],hmx[gid[i-k+1]][j][1][id]);
	}
	printf("%d",ans);
	return 0;
}
/*
8 3 3
4 1 3 5 6
5 2 4 6 7 8
*/
/*
18 3 6
13 1 2 3 4 5 6 9 10 11 12 13 14 18
7 5 6 7 8 9 10 18
*/
```

感谢你的阅读。

---

## 作者：tzc_wk (赞：1)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/796/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF796E)

~~当被数据结构搞自闭的 tzc 信心满满地点开一道 *2400 的 dp 题时……~~

~~却发现自己不会做？！~~

~~这足以证明蒟蒻 dp 之菜/dk/dk/wq/wq~~

设 $a_i=[\text{第一个人会做第}\ i\ \text{题}]$，$b_i=[\text{第二个人会做第}\ i\ \text{题}]$

考虑 $dp$，$dp_{i,j,x,y}$ 表示现在已经考虑到了第 $i$ 个人，现在已经消耗了 $j$ 次偷看的机会，此次向左边的人的偷看机会已经向左边的人偷看 $x$ 题，此次向左边的人的偷看机会已经向左边的人偷看 $y$ 题，所能做出的最多题数。如果 $x=k$ 表示在不消耗新的偷看机会的情况下不能再偷看第一个人的试卷，$y=k$ 也同理。

分两种情况转移：

1. 不消耗新的偷看机会，即从 $dp[i][j][x][y]$ 转移到 $dp[i+1][j][\min(x+1,k)][\min(y+1,k)]$，此时能多做出一道题当且仅当 $(a_{i+1}\land x+1\leq k)\lor (b_{i+1}\land y+1\leq k)$，即 $dp[i+1][j][\min(x+1,k)][\min(y+1,k)]\leftarrow dp[i][j][x][y]+(a_{i+1}\land x+1\leq k)\lor (b_{i+1}\land y+1\leq k)$

2. 消耗新的偷看机会。还是分两种情况，一是偷看第一个人的试卷，即 $dp[i+1][j+1][1][\min(y+1,k)]\leftarrow dp[i][j][x][y]+a[i+1]$，第二种是偷看右边人的试卷，即 $dp[i+1][j+1][\min(x+1,k)][1]\leftarrow dp[i][j][x][y]+b[i+1]$。

最终答案即为 $\max dp[n][j][x][y]$。

这样 DP 时间复杂度为 $npk^2$，会炸。考虑优化，感性理解一下可知当 $p$ 比较大的时可以选择将两个人的每道题的答案看完，这样答案即为 $a_i\lor b_i=1$ 的 $i$ 的个数。随便算一下就知道这样的 $p$ 的临界值为 $2\lceil\dfrac{n}{k}\rceil$，也就是说你只需对 $p\leq 2\lceil\dfrac{n}{k}\rceil$ 的情况跑一遍上述 DP 即可。时间复杂度也随之降到了 $n^2k$。

注意滚动数组优化，否则会 MLE。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e3;
const int MAXK=50;
int n,n1,n2,p,k,dp[2][MAXN+5][MAXK+3][MAXK+3];
int isa[MAXN+5],isb[MAXN+5];
int main(){
	scanf("%d%d%d",&n,&p,&k);
	scanf("%d",&n1);for(int i=1,x;i<=n1;i++) scanf("%d",&x),isa[x]=1;
	scanf("%d",&n2);for(int i=1,x;i<=n2;i++) scanf("%d",&x),isb[x]=1;
	if(p>=(n+k-1)/k*2){
		int ret=0;
		for(int i=1;i<=n;i++) ret+=isa[i]|isb[i];
		printf("%d\n",ret);return 0;
	}
	int pre=0,cur=1;memset(dp[pre],192,sizeof(dp[pre]));
	dp[pre][0][k][k]=0;
	for(int i=1;i<=n;i++){
		memset(dp[cur],192,sizeof(dp[cur]));
		for(int j=0;j<=p;j++){
			for(int x=1;x<=k;x++) for(int y=1;y<=k;y++){
				chkmax(dp[cur][j][min(x+1,k)][min(y+1,k)],dp[pre][j][x][y]+((isa[i]&&x<k)||(isb[i]&&y<k)));
				if(j<p){
					if(isa[i]) chkmax(dp[cur][j+1][1][min(y+1,k)],dp[pre][j][x][y]+1);
					if(isb[i]) chkmax(dp[cur][j+1][min(x+1,k)][1],dp[pre][j][x][y]+1);
				}
			}
		} pre^=cur^=pre^=cur;
	} int ans=0;
	for(int j=0;j<=p;j++) for(int x=1;x<=k;x++) for(int y=1;y<=k;y++)
		chkmax(ans,dp[pre][j][x][y]);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：泠小毒 (赞：1)

# Exam Cheating
muronglin是个学渣，考试的时候，她一道题也不会做

她的左右桌分别是学霸chhokmah和学霸lukelin，虽然学霸并不是题题都会做，但他们做了的题一定都对

现在muronglin想要作弊，但是为了不被监考员抓住，她最多偷看p次，一次能看连续的k道题

给定n和la和lb，分别为题目总数，chhokmah做出题目数和lukelin做出题目数，再给出两位学霸做出题目序列，问muronglin最多能偷看到几道题的答案
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190516/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190516.html)
## 解法
可以看出是个dp，设dp[i][j][x][y]表示前i个问题，用j次机会，chhokmah还能看x道题，lukelin还能看y道题的最优值

转移时分情况讨论，如果都没有机会，分4种：都不偷看，偷看任意1位，偷看2位

如果任意1位没有机会，分3种：只偷看1位，偷看2位，重新开始偷看2位

如果都有机会，就顺着模拟
## ac代码
```cpp
#include<bits/stdc++.h>
#define get(x,y) x=max(x,y)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,p,k,la,lb,ans=0,x,y=1,a[1010],b[1010],dp[2][1010][60][60];
int main()
{
    memset(dp,-0x3f,sizeof(dp)),dp[0][0][0][0]=0,scanf("%d%d%d",&n,&p,&k);
	scanf("%d",&la);FOR(i,1,la)scanf("%d",&x),a[x]=1;
	scanf("%d",&lb);FOR(i,1,lb)scanf("%d",&x),b[x]=1;
	if(p*k>=2*n){FOR(i,1,n)ans+=a[i]|b[i];printf("%d\n",ans);return 0;}
    FOR(i,1,n)
	{
        x=y,y^=1,memset(dp[x],-0x3f,sizeof(dp[x]));
        FOR(j,0,p)FOR(ii,0,k)FOR(jj,0,k)if(!ii&&!jj)
		{
	        get(dp[x][j][0][0],dp[y][j][0][0]);
	        get(dp[x][j+1][k-1][0],dp[y][j][0][0]+a[i]);
	        get(dp[x][j+1][0][k-1],dp[y][j][0][0]+b[i]);
	        get(dp[x][j+2][k-1][k-1],dp[y][j][0][0]+(a[i]|b[i]));
	    }
	    else if(!ii)
		{
	        get(dp[x][j][0][jj-1],dp[y][j][0][jj]+b[i]);
	        get(dp[x][j+1][k-1][jj-1],dp[y][j][0][jj]+(a[i]|b[i]));
	        get(dp[x][j+2][k-1][k-1],dp[y][j][0][jj]+(a[i]|b[i]));
	    }
	    else if(!jj)
		{
	        get(dp[x][j][ii-1][0],dp[y][j][ii][0]+a[i]);
	        get(dp[x][j+1][ii-1][k-1],dp[y][j][ii][0]+(a[i]|b[i]));
	        get(dp[x][j+2][k-1][k-1],dp[y][j][ii][0]+(a[i]|b[i]));
	    }
	    else get(dp[x][j][ii-1][jj-1],dp[y][j][ii][jj]+(a[i]|b[i]));
    }
    FOR(l,0,p)FOR(i,0,k)FOR(j,0,k)get(ans,dp[x][l][i][j]);printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Prean (赞：0)

注意到本质不同的偷看只有 $2n$ 种，于是先设 $dp[n][m]$ 表示前 $n$ 个位置进行 $m$ 次操作的最大值。

我们还需要知道上一次在两边进行操作的位置，不难发现这个位置一定在 $k$ 步以内。于是设 $dp[n][m][x][y]$ 表示两个序列上次偷看的位置是 $n-x,n-y$，如果 $x,y>k$ 那么显然令其等于 $k$ 是没问题的。

这样就可以 $O(n^2k^2)$了。

但是这样子难优化，重新设状态 $dp[n][m][x][y]$ 表示两个序列分别还可以偷看 $x$ 和 $y$ 个位置。

显然可以 $dp[n][m][x][y]\to dp[n][m+1][k-1][y]/dp[n][m+1][x][k-1]/dp[n][m+2][x][y]$。

而且很显然的是，进行这个操作的话显然是 $dp[n][m][0][y]$ 或者 $dp[n][m][x][0]$ 最优。

因为如果区间重合了，那么对区间稍微平移一下的可能偷看到答案的题的集合一定会比当前集合大。

所以问题相当于变成取一整行或者一整列的最值。

接下来考虑 $dp[n][m][x][y]\to dp[n+1][m][x-1][y-1]$。考虑用一个数来表示现在的 $(r,r)$ 是真正的 $(0,0)$。这样子就只需要进行行加和列加即可。

容易发现每次不会被修改的位置一定是一行/一列/$(x,x)$。

因为只有行修改和列修改以及单点修改，直接对每行和每列永久化加法懒标记即可。

时间复杂度 $O(npk)$。

然后因为显然，若 $p\geq2\lfloor\frac{n+k-1}{k}\rfloor$ 那么直接统计所有能做的题即可，可以卡上界，此时 $p$ 是 $O(\frac{n}{k})$ 级别的，复杂度变为 $O(n^2)$。
```cpp
#include<cstdio>
#include<cctype>
namespace SOLVE{
	const int M=1005;
	int n,m,k,tx[55],ty[55],id[M],w[M][55][55];bool v1[M],v2[M];
	inline int max(const int&a,const int&b){
		return a>b?a:b;
	}
	inline int read(){
		int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
	}
	inline void main(){
		int ans(0);n=read();m=read();k=read();
		for(int m=read();m--;)v1[read()]=true;for(int m=read();m--;)v2[read()]=true;
		if(m>2*(int(n+k-1)/k)){
			int ans(0);for(int i=1;i<=n;++i)(v1[i]||v2[i])&&++ans;printf("%d",ans);return;
		}
		for(int j=0;j<=m;++j)for(int x=0;x<=k;++x)for(int y=0;y<=k;++y)w[j][x][y]=-114514;
		for(int j=0;j<=m;++j)w[j][0][0]=0;
		for(int i=0;i<=n+1;++i)id[i]=(i+k)%(k+1);
		for(int i=1;i<=n;++i){
			const int&a=id[i-1],&b=id[i],&c=id[i+1];
			for(int j=m;j>=0;--j){
				int mx(0);
				for(int x=0;x<=k;++x)mx=max(mx,max(tx[b]+ty[x]+w[j][b][x],tx[x]+ty[b]+w[j][x][b]));
				if(j+2<=m&&mx>w[j+2][a][a]+tx[a]+ty[a])w[j+2][a][a]=mx-tx[a]-ty[a];
				for(int x=0;x<=k;++x){
					if(tx[b]+ty[x]+w[j][b][x]>tx[a]+ty[x]+w[j+1][a][x]){
						w[j+1][a][x]=tx[b]+ty[x]+w[j][b][x]-tx[a]-ty[x];
					}
					if(tx[x]+ty[b]+w[j][x][b]>tx[x]+ty[a]+w[j+1][x][a]){
						w[j+1][x][a]=tx[x]+ty[b]+w[j][x][b]-tx[x]-ty[a];
					}
				}
			}
			if(v1[i]&&v2[i]){
				for(int x=0;x<=k;++x)++tx[x];for(int j=0;j<=m;++j)--w[j][b][b];
			}
			else if(v1[i]){
				for(int x=0;x<=k;++x)if(x!=b)++tx[x];
			}
			else if(v2[i]){
				for(int x=0;x<=k;++x)if(x!=b)++ty[x];
			}
			for(int j=0;j<=m;++j){
				for(int x=0;x<=k;++x)if(x!=b){
					if(tx[b]+w[j][b][x]>tx[c]+w[j][c][x])w[j][c][x]=tx[b]+w[j][b][x]-tx[c];
					if(ty[b]+w[j][x][b]>ty[c]+w[j][x][c])w[j][x][c]=ty[b]+w[j][x][b]-ty[c];
				}
				if(tx[b]+ty[b]+w[j][b][b]>tx[c]+ty[c]+w[j][c][c])w[j][c][c]=tx[b]+ty[b]+w[j][b][b]-tx[c]-ty[c];
				for(int x=0;x<=k;++x)w[j][b][x]=w[j][x][b]=-114514;
				ans=max(ans,w[j][c][c]+tx[c]+ty[c]);
			}
		}
		printf("%d",ans);
	}
}
signed main(){
	SOLVE::main();
}
```
调了好久，阴间死我了！

---

## 作者：sleepyNick (赞：0)

## $\text {Description}$

KajKeusaka是个学渣，考试的时候，他一道题也不会做

他的左右桌分别是学霸Modest_Man和学霸Dawn_Chase，虽然学霸并不是题题都会做，但他们做了的题一定都对

现在KajKeusaka想要作弊，但是为了不被监考员抓住，他最多偷看p次，一次能看连续的k道题

给定n和la和lb，分别为题目总数，Modest_Man做出题目数和Dawn_Chase做出题目数，再给出两位学霸做出题目序列，问KajKeusaka最多能偷看到几道题的答案

## $\text{Solution}$

本题解主要是对julaoModest_Man题解的补充~

令$dp[i][j][L][R]$表示第$i$道题，已经偷看了$j$次，左边还可以看$L$题，右边还可以看$R$题时最多能偷看到的题数

分类讨论：

 - 两个人都不偷看
 - 偷看左边，可以接着上次看下去，也可以用一次次数重新开始看
 - 偷看右边，同上
 - 两人都看，可以(左边/右边)重新看/重新看，接着看/接着看，接着看/重新看，重新看/接着看

两人做出的题目用布尔型存起来方便提取
枚举$i,j,L,R$
先是继承上次的状态$dp[i-1][j][L-1][R-1]$，用$res$存起来
为什么？因为就算你不看，题目还是会下去，L和R都是要减的
```fix(x,y)```是将x更新（如果y更大）

$$if (L) fix (dp[i][j][L - 1][max (R - 1, 0)], res + a[I]);$$

如果左边可以看，不用花费次数直接更新，注意R-1不要越界

$$fix (dp[i][j + 1][k - 1][max (R - 1, 0)], res + a[I]);$$

左边不管可不可以看，直接重新开始看，这要花费一次次数，并且左边剩余次数重置为k-1



$$if (L) fix (dp[i][j + 1][L - 1][k - 1], res + (a[I]~|~ b[I]));$$

如果左边可以看，继承左边，重置右边，花费一次次数。$a[I]~|~b[I]$是表示两边都看能不能成功看到答案

$$fix (dp[i][j + 2][k - 1][k - 1], res + (a[I]~ |~ b[I]));$$

不管两边能不能看，暴力重置，花费两次次数

$$ if (L ~and~ R) fix (dp[i][j][L - 1][R - 1], res + (a[I] ~|~ b[I]));$$

如果两边都可以看，再好不过，不需要花费次数

再算上右边的镜像模式，这样我们就转移完了，$ans$就是所有情况打擂台

但是这样会mle，发现$i$这维完全可以滚动掉。

还有tle的风险，但是如果$p*k>=n*2$，那么就全部偷看呗，不看白不看，直接两边每次都看，特判输出。

空间复杂度：$O(pk^2)$

时间复杂度：$O(npk^2)<=O(2n^2k)$

Code:

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
#define rep(x,a,b) for (register int x = a; x <= b; x++)
#define MAXN 1005
#define MAXM 60
using namespace std;

int dp[2][MAXN][MAXM][MAXM], a[MAXN], b[MAXN], n, m, k, l, r, ans;

inline void fix (int &a, int b) {a = max (a, b);}

inline int read () {
	register int s = 0, w = 1;
	register char ch = getchar ();
	while (! isdigit (ch)) {if (ch == '-') w = -1; ch = getchar ();}
	while (isdigit (ch)) {s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar ();}
	return s * w;
}

int main () {
	n = read (), m = read (), k = read ();
	l = read (); rep (i, 1, l) a[read ()] = 1;
	r = read (); rep (i, 1, r) b[read ()] = 1;
	if (m * k >= n * 2) {
		rep (i, 1, n) ans += a[i] | b[i];
		printf ("%d\n", ans); return 0;
	}
	memset (dp, -0x3f3f3f, sizeof dp), dp[0][0][0][0] = 0;
	rep (I, 1, n) {
		int i = I % 2, last = (I + 1) % 2;
		memset (dp[i], -0x3f3f3f, sizeof dp[i]);
		rep (j, 0, m) rep (L, 0, k) rep (R, 0, k) {
			int res = dp[last][j][L][R];
			fix (dp[i][j][max (L - 1, 0)][max (R - 1, 0)], res);
			if (L) fix (dp[i][j][L - 1][max (R - 1, 0)], res + a[I]);
			if (L) fix (dp[i][j + 1][L - 1][k - 1], res + (a[I] | b[I]));
			if (R) fix (dp[i][j][max (L - 1, 0)][R - 1], res + b[I]);
			if (R) fix (dp[i][j + 1][k - 1][R - 1], res + (a[I] | b[I]));
			if (L && R) fix (dp[i][j][L - 1][R - 1], res + (a[I] | b[I]));
			fix (dp[i][j + 1][k - 1][max (R - 1, 0)], res + a[I]);
			fix (dp[i][j + 1][max (L - 1, 0)][k - 1], res + b[I]);
			fix (dp[i][j + 2][k - 1][k - 1], res + (a[I] | b[I]));
		}
	}
	rep (j, 0, m) rep (L, 0, k) rep (R, 0, k) fix (ans, dp[n % 2][j][L][R]);
	printf ("%d\n", ans);
	return 0;
}
```


---

## 作者：ModestCoder_ (赞：0)

作弊要警告处分的说。。。

显然是一道DP的题目

设计状态：$dp[i][j][k][l]$表示第i道题目，用了j次偷看机会，两个人分别还剩$k,l$道题目可以偷看

用刷表法转移，分类讨论

 - 不偷看
 - 只偷看左边：1、直接偷看；2、重新偷看
 - 只偷看右边：1、直接偷看；2、重新偷看
 - 两边一起偷看：1、都直接偷看；2、都重新偷看；3、左边那位直接偷看，右边那位重新偷看；4、左边那位重新偷看，右边那位直接偷看

注：直接偷看的意思是用了上次机会继续偷看下去，重新偷看的意思是重新新用一个机会开始偷看

转移的时候需要注意：

 - 是否还能继续直接偷看
 - 不管看不看，只要还在这次机会里面，都要使剩余的题目数-1，具体在代码中体现为$max(k-1,0)$

时空间复杂度$O(npk^2)$

空间上发现第一位滚动掉就可以避免MLE

时间上怎么优化？发现如果$p*k>=2*n$的话，你直接全部偷看过来得了。这个一特判，时间复杂度上界变为$O(n^2k)$，就可以过啦

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 1010
#define maxm 60
using namespace std;
int n, p, K, a[maxn], b[maxn], dp[2][maxn][maxm][maxm];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void upd(int &x, int y){ if (x < y) x = y; }

int main(){
	n = read(), p = read(), K = read();
	int x = read();
	for (int i = 1; i <= x; ++i){
		int y = read(); a[y] = 1;
	}
	x = read();
	for (int i = 1; i <= x; ++i){
		int y = read(); b[y] = 1;
	}
	if (p * K >= (n << 1)){
		int ans = 0;
		for (int i = 1; i <= n; ++i) ans += a[i] | b[i];
		return printf("%d\n", ans), 0;
	}
	memset(dp, -0x3f, sizeof(dp)); dp[0][0][0][0] = 0;
	for (int i = 1; i <= n; ++i){
		int now = i & 1, pre = now ^ 1;
		memset(dp[now], -0x3f, sizeof(dp[now]));
		for (int j = 0; j <= p; ++j)
		for (int k = 0; k <= K; ++k)
		for (int l = 0; l <= K; ++l){
			int tmp = dp[pre][j][k][l];
			upd(dp[now][j][max(k - 1, 0)][max(l - 1, 0)], tmp);
			if (k) upd(dp[now][j][k - 1][max(l - 1, 0)], tmp + a[i]);
			upd(dp[now][j + 1][K - 1][max(l - 1, 0)], tmp + a[i]);
			if (l) upd(dp[now][j][max(k - 1, 0)][l - 1], tmp + b[i]);
			upd(dp[now][j + 1][max(k - 1, 0)][K - 1], tmp + b[i]);
			if (k && l) upd(dp[now][j][k - 1][l - 1], tmp + (a[i] | b[i]));
			if (k) upd(dp[now][j + 1][k - 1][K - 1], tmp + (a[i] | b[i]));
			if (l) upd(dp[now][j + 1][K - 1][l - 1], tmp + (a[i] | b[i]));
			upd(dp[now][j + 2][K - 1][K - 1], tmp + (a[i] | b[i]));
		}
	}
	int ans = 0;
	for (int j = 0; j <= p; ++j)
	for (int k = 0; k <= K; ++k)
	for (int l = 0; l <= K; ++l) upd(ans, dp[n & 1][j][k][l]);
	printf("%d\n", ans);
	return 0;
}
```


---

