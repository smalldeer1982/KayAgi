# 「RdOI R2」称重(weigh)

## 题目背景

因为 rui_er 是一个良心出题人，所以本题是一道交互题。

## 题目描述

rui_er 为了准备体测，买了 $n$ 个实心球准备练习，但是却发现在发货时混入了两个质量明显较轻但外观相似的球（这两个球质量相等），且已知这两个球的质量之和大于一个正常的球。为了防止影响训练效果，现在需要找出这两个球。因为手动找太慢了，现在拿来了一个天平，可以在两侧各放上若干个球，得到两侧的质量大小关系。请你帮帮 rui_er，在使用不超过 $k$ 次天平的情况下，找出这两个较轻的球。

这里 $k$ 是每个测试点的属性，你不必也不应该读入。

---

**交互方式**

本题采用 I/O 交互。

你可以选择进行称量操作，此时向标准输出打印一行 `1 p a1 a2 ... ap q b1 b2 ... bq`，表示在天平左盘放入编号为 $a_1,a_2,\cdots,a_p$ 的 $p$ 个球，在天平右盘放入编号为 $b_1,b_2,\cdots,b_q$ 的 $q$ 个球。随后清空缓冲区，并从标准输入读入一个 `<>=` 之一的字符，表示左盘与右盘的质量关系。

对于每次此类询问，你需要保证 $1\le p,q\le n$，$p+q\le n$，所有 $a_i$ 和 $b_i$ 互不相同，且你最多进行此类询问 $k$ 次。

在得到答案后，向标准输出打印一行 `2 x y` 来提交答案，表示编号为 $x$ 的球和编号为 $y$ 的球质量偏轻。

你需要保证 $1\le x\lt y\le n$（注意需要严格按照从小到大顺序输出），且在进行完这一操作后立即终止程序。

交互库在一开始就已经确定小球的情况，不会随着你的询问而改变。

## 说明/提示

**样例解释**

三次询问的结果为 $a_1=a_2,a_3\lt a_4,a_5\gt a_6$，可以知道编号为 $3,6$ 的两个球质量偏轻。

---

**数据范围**

本题按点得分。

$20$ 个非 HACK 测试点中，第一个点 $4$ 分，其它点每点 $5$ 分；$4$ 个 HACK 测试点共 $1$ 分，任意一个测试点不通过则不得分。

|测试点|$n\le$|$k=$|特殊性质|测试点|$n\le$|$k=$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|1|$5$|$50$|无|11|$500$|$50$|无|
|2|$10$|$50$|无|12|$500$|$50$|无|
|3|$100$|$50$|无|13|$500$|$20$|A|
|4|$100$|$50$|无|14|$500$|$20$|B|
|5|$500$|$50$|A|15|$500$|$20$|A|
|6|$500$|$50$|B|16|$500$|$20$|B|
|7|$500$|$50$|A|17|$500$|$20$|无|
|8|$500$|$50$|B|18|$500$|$20$|无|
|9|$500$|$50$|无|19|$500$|$20$|无|
|10|$500$|$50$|无|20|$500$|$20$|无|
|ex1|$500$|$12$|B/HACK|ex3|$500$|$13$|HACK|
|ex2|$500$|$13$|HACK|ex4|$500$|$14$|HACK|

- 特殊性质 A：$n=2^i-1,i\in\left\{4,5,6,7,8\right\}$。
- 特殊性质 B：$n=2^i,i\in\left\{4,5,6,7,8\right\}$。
- 备注：HACK 数据的 $k$ 根据测试点实际情况设置，会卡一些奇怪的做法，保证正解可过。

对于全部数据，$5\le n\le 500$，$k\in\left\{50,20,14,13,12\right\}$。

## 样例 #1

### 输入

```
6

=

<

>```

### 输出

```

1 1 1 1 2

1 1 3 1 4

1 1 5 1 6

2 3 6```

# 题解

## 作者：rui_er (赞：13)

**UPD(2021.6.22)：加强了数据，更新解法。**

本题解是「RdOI R2」称重(weigh) 的官方题解。

简单思维题。

根据题意，一个假球比一个真球轻，但两个假球比一个真球重，显然询问一要得到信息肯定要使 $p=q$，否则得不到任何有用的信息。

考虑分类讨论：

- 第一种情况：在 $n=2i$ 个球中找一个假球。

考虑将球拆为两组，每组有 $i$ 个球，并询问。因为只有一个假球，显然两组的质量肯定不相等，此时假球在质量更小的一组。

- 第二种情况：在 $n=2i$ 个球中找两个假球。

同样拆成两组，各 $i$ 个球。如果得到 `=`，则两组各有一个假球；否则两个假球都在质量更小的一组。

- 第三种情况：在 $n=2i+1$ 个球中找一个假球。

将球拆为三组，分别有 $i,i,1$ 个，询问 $i$ 个球的两组。如果得到 `=`，则单独的球是假球；否则假球在质量更小的一组。

- 第四种情况：在 $n=2i+1$ 个球中找两个假球。

同样拆成三组，分别有 $i,i,1$ 个。询问前两组。如果得到 `=`，则两组各有一个假球；否则在质量更大的一组（总共只有两个假球，可以断定这组必定全为真球）中取一个球与单独的球询问，质量相等则两个假球都在质量更小的一组，否则单独的球是假球，另一个假球在质量更小的一组。

现在思路就比较显然了吧，初始状态是 $\left[1,n\right]$ 中找两个假球，然后按照上面的分类讨论进行二分即可。

std 在所有测试点中的最大询问次数是 $15$ 次。

给出 std 代码供参考：[Link](/paste/2hmfhyk8)

---

**但是上面的 std 在 2021.6.22 的数据加强中被卡成了 Unaccepted $99$ 分。**

考虑进一步优化。

当在区间内找一个假球的时候，我们每次排除 $\dfrac{1}{2}$ 的球，但是显然可以更优。我们在左、右各取大约 $\dfrac{1}{3}$ 的球进行询问，如果相等则递归询问中间段，否则询问更轻的段，这样利用三分的思想，每次可以排除 $\dfrac{2}{3}$ 的球。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const int N = 505;

int n, a[N], b[N];
vector<int> ans;
int interact(int *a, int p, int *b, int q) {
	printf("1 %d ", p);
	rep(i, 1, p) printf("%d ", a[i]);
	printf("%d ", q);
	rep(i, 1, q) printf("%d%c", b[i], " \n"[i==q]);
	fflush(stdout);
	char tmp[2];
	scanf("%s", tmp);
	if(tmp[0] == '<') return -1;
	if(tmp[0] == '=') return 0;
	return 1;
}
void searchAns(int L, int R, int k) {
//	printf("searchAns %d %d %d\n", L, R, k);
	int len = R - L + 1, M = (L + R) >> 1, tA = 0, tB = 0;
	int ML = L + (R - L) / 3, MR = R - (R - L) / 3;
//	printf("%d %d\n", ML, MR);
	if(len == k) {
		if(k == 1) ans.push_back(L);
		else ans.push_back(L), ans.push_back(R);
		return;
	}
	if(k == 1) {
		rep(i, L, ML) a[++tA] = i;
		rep(i, MR, R) b[++tB] = i;
		int res = interact(a, tA, b, tB);
		if(!res) return searchAns(ML+1, MR-1, 1);
		if(res == 1) return searchAns(MR, R, 1);
		return searchAns(L, ML, 1);
	}
	if(len & 1) {
		rep(i, L, M-1) a[++tA] = i;
		rep(i, M, R-1) b[++tB] = i;
		int res = interact(a, tA, b, tB);
		if(!res) {
			searchAns(L, M-1, 1);
			searchAns(M, R-1, 1);
		}
		else if(res == 1) {
			a[1] = L; b[1] = R;
			int qwq = interact(a, 1, b, 1);
			if(qwq == 1) {
				ans.push_back(R);
				searchAns(M, R-1, 1);
			}
			else searchAns(M, R-1, 2);
		}
		else {
			a[1] = R - 1; b[1] = R;
			int qwq = interact(a, 1, b, 1);
			if(qwq == 1) {
				ans.push_back(R);
				searchAns(L, M-1, 1);
			}
			else searchAns(L, M-1, 2);
		}
	}
	else {
		rep(i, L, M) a[++tA] = i;
		rep(i, M+1, R) b[++tB] = i;
		int res = interact(a, tA, b, tB);
		if(!res) {
			searchAns(L, M, 1);
			searchAns(M+1, R, 1);
		}
		else if(res == 1) searchAns(M+1, R, 2);
		else searchAns(L, M, 2);
	}
}

int main() {
	scanf("%d", &n);
	searchAns(1, n, 2);
	sort(ans.begin(), ans.end());
	printf("2 %d %d\n", ans[0], ans[1]);
	fflush(stdout);
	return 0;
}
```

---

## 作者：Grand_Dawn (赞：9)

### 概述

题目简述：在 $n$ 个球中用天平找到 $2$ 个轻球。

本题解在所有测试点中的最大询问次数为 $11$ 次，且在所有在该题范围内的数据都可以做到 $11$ 次，非常优秀。

$f(n)=\left\lceil\log_3\left(\dfrac{n(n-1)}{2}\right)\right\rceil$ 是本问题询问次数的理论下限。

为了尽可能逼近该数值，每次询问都需要尽可能将当前所有状态数进行三等分。

### 对于其它题解在 $n$ 较大时未能够足够逼近下界的论述

为了易于讨论，该部分内容忽略边界条件。

@[Little09](https://www.luogu.com.cn/user/151475) 的方法（方法一）：

简述：将球分为两份，如果相等，每一份都有一个轻球；否则，轻的那一份有两个轻球。之后进行递归处理。

为了更易于理解，此处放上一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/vq7e0ouh.png?height=100)

（其中横纵坐标均为 $1\sim n$，由于 $n$ 足够大，可以忽略间隙。）

（图中第一个轻球指的是位置编号较小的轻球，第二个轻球指的是位置编号较大的轻球，下同。）

可以发现如果得到的是相等的答案，状态数仅仅变为原来的约一半，远不到 $\frac{1}{3}$。

 @[WYXkk](https://www.luogu.com.cn/user/130151) 的方法（方法二）：
 
简述：将球分为三份，用两次询问获得两两之间的关系。如果有两份比第三份轻，那么这一份都有一个轻球；如果仅有一份比剩下两份轻，那么这一份有两个轻球。同样进行递归处理。

![](https://cdn.luogu.com.cn/upload/image_hosting/zw6jod5h.png)

（括号内第一个字母为靠左的球所在的集合，第二个字母为靠右的球所在的集合。下同。）

可以发现最劣情况为有两份比第三份轻的情况，用 $2$ 次询问仅将状态数变为原来的 $\frac{2}{9}$。

@[Rui_er](https://www.luogu.com.cn/user/122461) 的方法：类似方法一，但处理边界情况更劣。

### 第三种方法的引出

可以发现在方法二中，第一次询问恰好将状态分为 $\frac{1}{3}$，而第二次询问没有达到下界。考虑优化第二次询问：

将球尽可能平均地分为 $3$ 份 $A,B,C$，且要求 $A$ 和 $C$ 中球的数量相同。

第一次询问 $A$ 和 $C$，会分为三种情况：$(A,A)+(A,B),(B,B)+(A,C),(B,C)+(C,C)$。

先讨论 $(A,A)+(A,B)$ 的状态数，发现 $(A,A)$ 的状态数大约占 $(A,A)+(A,B)$ 的状态数的 $\frac{1}{3}$。

因此可以考虑将 $(A,A)+(A,B)$ 分开 $(A,A),(A,B)$ 并将 $(A,B)$ 状态数将为一半。

因此下一次集合可以将 $B$ 中的球均分为两份（是奇数的话从 $C$ 拿一个球，这个球不可能为轻球），进行一次询问。

如果重量相等，那么两个轻球都在 $A$；否则一个轻球在 $A$，另一个在轻的那份里。

$(B,C)+(C,C)$ 的情况类似。接下来讨论 $(B,B)+(A,C)$：

+ 如果 $C$ 可以均分为两份，那么将两份进行一次询问。

如果重量相等，那么两个轻球都在 $B$；否则一个轻球在 $A$，另一个在轻的那份里。

+ 排除上述情况，但所有球可以均分为两份的话，可以将 $A$ 和 $C$ 的一半，以及 $B$ 和 $C$ 的另一半进行询问，可以得到与上述类似的结果。

+ 排除上述情况，但此处球的总数量不为原来的 $n$，则可以从其它地方拿来一个正常球使两边球数相同。

+ 排除上述所有的情况之后，那么只能在第一次询问之前将 $C$ 的大小减一。

图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/om0i76i3.png)

边界情况：

两个球 $a,b$：直接返回。

三个球 $a,b,c$：询问一次即可获得答案。

### 对于三种方法可能未能取到下界的另一个原因

在 $n$ 个球中找到 $1$ 个轻球的下界为 $\left\lceil\log_3n\right\rceil$，且可以取到下界：一直尽可能均分为 $3$ 份。

但分别在一份 $x$ 个球和一份 $y$ 个球中分别找到 $1$ 个轻球的下界是 $\left\lceil\log_3(xy)\right\rceil$，而现在所需要的询问数量为 $\left\lceil\log_3(x)\right\rceil+\left\lceil\log_3(y)\right\rceil$。

考虑优化：首先假设其中一份有 $x=2$ 个球 $a,b$，其一次询问状态数仅变为原来的 $\frac{1}{2}$。这个过程可以优化到 $\frac{1}{3}$：

将另一份 $y$ 分为两份，一份尽可能接近 $\frac{1}{3}y$，另一份 $\frac{2}{3}y$。

将 $a$ 和 $\frac{1}{3}y$ 放在天平的左侧，$\frac{2}{3}y$ 放在右侧。如果数量不相同则添加正常球（顶多约 $\frac{1}{3}y$ 个）。

补充：由于两份球各找一个轻球的状态由方法三有 $x,y\le\left\lceil\frac{n}{3}\right\rceil$，而已知的正常球个数至少为 $\left\lfloor\frac{n}{3}\right\rfloor$，因此正常球数量足够来使两边数量相同。

+ 如果平衡，则轻球为 $a$ 并在 $\frac{2}{3}y$ 那一份再找一个轻球。

+ 如果右侧重量比较轻，则轻球为 $b$ 并在 $\frac{2}{3}y$ 那一份再找一个轻球。

+ 如果左侧重量比较轻，则 $a,b$ 中有一个轻球，并在 $\frac{1}{3}y$ 那一份再找一个轻球。此处进行递归操作。

每种情况都将 $2y$ 的状态数划分为 $\frac{2}{3}y$，是比较优秀的操作。

可以将 $x=2$ 的情况进行推广为对于更大的 $x$ 分为 $A,B$ 两份的情况。在这种情况下，误差开始增大，因此需要详细考虑是否该使用该操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/1n47o08m.png)

### 建立决策树

发现对于以上方法，像 $n=7,13,20,21,22,37,38,115$ 之类的数据并没有取到 $f(n)$，因此可以使用建立决策树的策略，将决策树直接枚举出来，将答案降为最小。

决策数量为 $\Theta(3^n)$，但由于很多决策都能够将状态尽可能三等分，所以找到这样的一个决策并不是太难。

经测试，找到一个决策的时间复杂度**大约**为 $\Theta(n)$，判断一个决策的合法性需要 $\Theta(s)$ 的时间复杂度。（$s$ 为当前节点的状态总数。）

决策树较为平均，因此决策树的深度约为 $\Theta(\log_3({n^2}))$，且一层节点的状态数之和为 $\Theta(n^2)$。

因此总复杂度约为 $\Theta(n^3\log_3({n^2}))$。

优化：如果 $n$ 和 $n-1$ 都需要搜索决策树，那么强制钦定 $n$ 号球一直不选可以减少一倍的常数。

同理，可以发现对于两份分别找轻球的状态时，$x=5,7,11,19$ 之类的数据使用二分法和三分法仍然显得比较差。

发现当 $x=5,7,11,19$ 的时候，可以依次用 $3,4,5,6$ 次操作，对于另一份进行 $y=5,11,22,38$ 等分（最坏条件下为上取整）。

注意此处如果球的数量不同仍需要补充正常球使球的数量相同。

决策状态数量为 $\Theta(3^{x+y})$，如果实现较差的暴力可能只能找出 $x=5$ 的决策树，实现较好的暴力可以找到 $x=7,11,19$ 的决策树。

### 打表

对于 $n=115,343,344$ 以及 $x=172,y=343$ 仍然没有卡到下界，且无法在搜索的时间复杂度内通过。可以发现有些节点找到一个决策的次数远超过 $\Theta(n)$。

因此，可以采用的方法是将这些节点的决策打表。

需要打印的字符串为所有需要决策的情况使用的询问，对于每一个点可以使用长度为 $n$ 或 $x+y$，每一位为 $0,1,2$ 的字符串记录。

此时的代码可以在一秒内通过，但代码长度很有可能超限。

字符串压缩方法：将 $4$ 位压成 $1$ 位减少长度，总共需要 $3^4=81$ 种不同的可见字符。

又可以发现在原字符串中，连续的 $0$ 出现次数非常多，因此又可以将压缩后的字符串的连续的 $0$ 进行二次压缩，即用剩下的可见字符表示 $4k$ 个 $0$。

需要注意的是，由于寻找决策的过程需要用到随机数。因为打表的代码和原代码需要有相同的结果。因此需要可复现的随机数实现，这里使用 [P7738](https://www.luogu.com.cn/problem/P7738) 的下发代码。

### 第三种方法的不足之处

对于在 $n$ 个球中找到 $2$ 个轻球，一次操作的第二个步骤，实际上误差比较大，足以达到 $\frac{2}{3}n$。

对于在两堆球中分别找到 $2$ 个轻球，仍然有一些 $x,y$ 也存在误差，并没能卡到下界。

### 表现

对于 $2\le n\le10^7$ 的最坏情况，进行整理：
 
| 最坏情况下的称量次数 | 为 $f(n)$ 的 $n$ 的个数 | 为 $f(n)+1$ 的 $n$ 的个数 | 总计 |
| :-: | :-: | :-: | :-: |
| 方法一&方法二（另一原因无优化） | $5519275$ | $4480724$ | $9999999$ |
| 方法三（另一原因无优化） | $5519275$ | $4480724$ | $9999999$ |
| 方法三（$x=2,4$ 优化） | $7910718$ | $2089281$ | $9999999$ |
| 方法三（无优化搜索决策树） | $8442161$ | $1557838$ | $9999999$ |
| 方法三（优化搜索决策树） | $9939102$ | $60897$ | $9999999$ |
| 方法三（打表+优化搜索决策树） | $9968628$ | $31371$ | $9999999$ |

（注：用@[WYXkk](https://www.luogu.com.cn/user/130151) 的代码跑出来的结果和他题解里的结果略有不同，有可能我使用方法不对。）

对于足够大的 $n$，最后的方法能取到 $f(n)$ 的数量占比大于 $99\%$。

一个不够充分的证明：

$n\le 10^4$ 经程序计算满足条件。

对于 $n\leftarrow 3n$，由于为三分法，原本不能取到的数 $\times 3$ 左右的数，显然都不能够取到最优解。

运用数学归纳法可以得证。

对于最坏情况下的称量次数一定 $\le f(n)+1$，该点比较难以证明。欢迎读者补充证明。

关于是否对于每个 $n$ 都有卡到 $f(n)$ 次的方法，我的观点与 @[WYXkk](https://www.luogu.com.cn/user/130151) 不同，因为决策数量是指数级别的，很可能存在恰好将状态均分为三种的决策。

在本题中，试验过所有可能的数据，询问次数均没有超过 $11$ 次，且 $11$ 次为本题理论下界。

更好的是，对于所有 $n\le 500$，询问次数均没有超过 $f(n)$ 次。最小的超过询问次数的是 $595$。

~~因此，又可以加强数据了。~~

[本文中用到的代码](https://www.luogu.com.cn/paste/mdywt0s3)

### 本文中提到的链接

1.@[Little09](https://www.luogu.com.cn/user/151475) 的[题解](https://www.luogu.com.cn/blog/LJA001111/solution-p7579)

2.@[WYXkk](https://www.luogu.com.cn/user/130151) 的[题解](https://www.luogu.com.cn/blog/WYXkk/solution-p7579)

3.@[Rui_er](https://www.luogu.com.cn/user/122461) 的[题解](https://www.luogu.com.cn/blog/ak-ioi/rdoi-r2-cheng-zhong-weigh-ti-xie)

顺便附上[本文链接](https://www.luogu.com.cn/blog/134249/solution-P7579)



---

## 作者：zhangxiao666 (赞：5)

## 前言：
个人觉得比较好的一道分治题，也比较考验思维，因此写一写题解，管理大大求通过。

[博客使用效果更佳](https://www.luogu.com.cn/blog/zhangxiao666/p7579-rdoi-r2-cheng-zhong-weigh-ti-xie)

## 题意：
[题目](https://www.luogu.com.cn/problem/P7579)

一道交互题。

有 $n$ 个球，里面有两个假球，假球比普通球的要轻，每次可以询问任意两组球的轻重关系，第一组轻为 $<$ ,第二组轻为 $>$ ,一样重量为 $=$ 。

## 思路：

先考虑在一个区间内找 $1$ 个假球。

我们可以将区间尽量平均分为 $3$ 份，先询问相等的两组球的轻重关系，分 $3$ 种情况：

+ 第一组轻

由于在区间里只有 $1$ 个假球，且区间长度一定，所以这个假球一定在第一组里，所以继续在第一组寻找 $1$ 个假球。

+ 第二组轻

与第一种情况一样，假球一定在第二组里，所以继续在第二组寻找 $1$ 个假球。

+ 一样重

因为只有一个假球，所以这个假球一定不在这两组里（否则一定会有一组轻），那么假球就一定在剩下的那组里，在剩下的那组寻找 $1$ 个假球。

$1$ 个假球的情况解决了，$2$ 个假球呢？

我们先将区间平均分成 $2$ 份，根据区间长度分为 $2$ 种情况。

+ 区间长度为偶数

询问平均分成的两段区间，和上面类似，也是 $3$ 种情况。

1. 第一组轻

因为有 $2$ 个假球，且区间长度一定，想让第一组轻，$2$ 个假球都得在第一组里，所以在第一组继续寻找两个假球。

2. 第二组轻

与第一种情况类似，$2$ 个假球一定都在第二组里，所以在第二组继续寻找两个假球。

3. 一样重

因为有两个球，既然一样重，那就一边一个，分别在两组中寻找一个假球。

+ 区间长度为奇数

因为是奇数，所以一定会有一个球不在两个区间内（被单独拿出来），我们还是先询问两端均等的区间，依旧是三种情况：

1. 第一组轻

与偶数中的情况类似，第一组一定有假球，现在的问题就是剩下的那个球是不是假球。

我们可以换一个角度考虑，如果想确定第一个球是不是假球，最好的办法就是拿个真的和他比，但是我么如何找真的呢？

通过上面的研究，我们发现，假球一定在第一组和中间那个，剩下的第二组里一定都是真球。因此，直接将第二组拿出一个与剩下的那个球询问。相等则 $2$ 个假的都在第一组，否则剩下的是个假的，第一组有 $1$ 个假的。

2. 第二组轻

和第一组轻的情况一样，通过从第一组拿出球与剩下的那个比较。相等则 $2$ 个假的在第二组，反之 $1$ 个假的在第一组，$1$ 个是剩下的那个球。

3. 一样重

由于一样重，所以剩下的那个不可能是假球（否则一、二两组中只有一个假的，且球数一样，无论在哪组都不可能一样重）。

这样，就又回到了偶数的情况，两个假的一边一个。

## 代码

请勿抄袭

```cpp
#include<bits/stdc++.h>
using namespace std;
int jia1,jia2;//jia1和jia2表示两个假球的编号 
char ask(int l1,int r1,int l2,int r2)//询问l1~r1与l2~r2之间球的轻重关系。 
{
	printf("1 ");
	printf("%d ",r1-l1+1);//长度 
	for(int i=l1;i<=r1;i++) printf("%d ",i);
	printf("%d ",r2-l2+1);
	for(int i=l2;i<=r2;i++) printf("%d ",i);
	printf("\n");
	char ch; 
	cin>>ch;
	return ch;//读入并返回轻重关系 
}
void print()//输出结果 
{
	if(jia1>jia2) swap(jia1,jia2);//保证先输出的小 
	printf("2 %d %d\n",jia1,jia2);
	exit(0);//直接结束程序 
}
void make_ans(int ans)//将ans设为假球 
{
	if(!jia1) jia1=ans;
	else jia2=ans,print();
}
void find(int l,int r,int num)//l，r该次寻找区间的左右端点，num该区间中假球的数量 
{
	if(l==r)//找的只有一个球，这个球一定是假的 
	{
		make_ans(l);
		return;
	} 
	if(num==1)//找一个假球的情况 
	{
		int midl=l+(r-l)/3;//区间分为三份 
		int midr=r-(r-l)/3;
		char op=ask(l,midl,midr,r);//询问 
		if(op=='=')//相等，假期在剩下那组 
		{
			find(midl+1,midr-1,1);
		}
		if(op=='<')//否则在轻的那组 
		{
			find(l,midl,1);
		}
		if(op=='>')
		{
			find(midr,r,1);
		} 
	} 
	else//找两个假球的情况 
	{
		int mid=(l+r)/2;//先把区间分成二份		
		if((r-l+1)%2==0)//区间长度为偶数的情况 
		{
			char op=ask(l,mid,mid+1,r);//询问
			//以下为题解中的三种情况 
			if(op=='=')
			{
				find(l,mid,1);
				find(mid+1,r,1);
			}
			if(op=='<')
			{
				find(l,mid,2); 
			}
			if(op=='>')
			{
				find(mid+1,r,2);
			}
		}
		else//区间长度为奇数的情况 
		{ 
			char op=ask(l,mid-1,mid+1,r);//询问
			//三种情况 
			if(op=='=')
			{
				find(l,mid-1,1);
				find(mid+1,r,1);
			}
			if(op=='<')
			{
				char opt=ask(mid,mid,mid+1,mid+1);
				//右边（第二组）的球都是真的，利用询问得出剩下的那个是否为假球 
				if(opt=='=')//相等，不是假球 
				{
					find(l,mid-1,2);
				}
				else//不相等，是假球 
				{
					make_ans(mid);
					find(l,mid-1,1);					
				}
			}
			if(op=='>')
			{
				char opt=ask(mid,mid,mid-1,mid-1);
				if(opt=='=')
				{
					find(mid+1,r,2);
				}
				else
				{
					make_ans(mid);
					find(mid+1,r,1);					
				}
			}
		}
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	find(1,n,2);//根据题意，在n个球中找两个假球 
}
```


写题解不易，点个赞呗

---

## 作者：MarchKid_Joe (赞：5)

# [(交互题)weigh](https://www.luogu.com.cn/problem/P7579)

## 前言

这是一篇写完二分被卡成 $99$ 分却又没有耐心全部改成三分的人的题解。

## 二分

对于区间 $[l,r]$ 二分，若区间 $[l,r]$ 内**有劣质球才分类讨论，否则直接跳出**：

### 区间长度为奇数

将中点 $mid$ 为 $\frac{l+r}{2}$ 抛出来然后将区间平均分，则区间可以分为 $3$ 部分：$A:[l,mid-1]$，中点 $mid$，$B:[mid+1,r]$。此时将区间 $A,B$ 进行比较，通过交互库得到比较结果：

- ${A}={B}$
  - 若 $[l,r]$ 区间内有 $2$ 个劣质球，则只有一种情况：$A,B$ 区间**一定各有一个劣质球**，中点为**一定为正常球**。
  - 若 $[l,r]$ 区间内有 $1$ 个劣质球，则只有一种情况：$A,B$ 区间**都没有劣质球**，中点**一定为劣质球**。
- ${A}\gt{B}$
  - 若 $[l,r]$ 区间内有 $2$ 个劣质球，则有两种情况：$A$ 区间**一定没有劣质球**。$B$ 区间**可能有一个劣质球**，则中点**为劣质球**；$B$ 区间**可能有两个劣质球**，则中点**为正常球**。所以只需要先判断中点 $mid$ 是哪类球就可以确定 $B$ 区间的状态。
  - 若 $[l,r]$ 区间内有 $1$ 个劣质球，则只有一种情况：$A$ 区间**一定没有劣质球**。$B$ 区间**一定有一个劣质球**，中点**一定为正常球**。
- ${A}\lt{B}$ 和 ${A}\gt{B}$ 同理，两个区间反过来即可。

### 区间长度为偶数

将区间平均分：则左区间为 $A:[l,\frac{l+r-1}{2}]$，右区间为 $B:[\frac{l+r+1}{2},r]$。通过交互库得到区间 $A,B$ 的比较结果：

- ${A}={B}$
  - 若 $[l,r]$ 区间内有 $2$ 个劣质球，则只有一种情况：$A,B$ 区间**一定各有一个劣质球**。
  - 若 $[l,r]$ 区间内有 $1$ 个劣质球，情况根本就不存在。
- ${A}\gt{B}$
  - 若 $[l,r]$ 区间内有 $2$ 个劣质球，则只有一种情况：$A$ 区间**一定有两个劣质球**，$B$ 区间**一定没有劣质球**。
  - 若 $[l,r]$ 区间内有 $1$ 个劣质球，则只有一种情况：$A$ 区间**一定有一个劣质球**，$B$ 区间**一定没有劣质球**。
- ${A}\lt{B}$ 同理。

## 优化

很多人可能写完二分被卡为 $99$ 分，但是又不想重新分类讨论三分：当时本人想修改为三分时，发现若区间内含有两个劣质球分类讨论很难搞，那就~~猴分~~：二分与三分结合。因为对于区间 $[l,r]$ 内的**仅含有一个劣质球**，三分很好解决！！！

___

设区间划分为三个区间 $A,B,C$。其中 $A,B$ 区间**长度相等**，比较区间 $A,B$ 得到比较结果：

- $A=B$：这个劣质球一定在 $C$。
- ${A}\gt{B}$：这个劣质球一定在 $B$。
- ${A}\lt{B}$：这个劣质球一定在 $A$。

___

明白了没有？对于区间 $[l,r]$ 含有 $2$ 个劣质球，采用刚刚写过的二分；若只含有 $1$ 个劣质球，则就进行三分，采用上述这么简单的分类讨论即可，不必重新在讨论三分时区间含有 $2$ 个劣质球这么恶心的情况了。

## 代码

代码自己最好找一张纸，每种情况列好了再写最好，本来就是分类讨论，思路容易乱哦。

代码仅供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
set<int> ans; /*set 自动从小到大排序*/
char query(int l1, int r1, int l2, int r2) /*查询[l1,r1],[l2,r2] 区间大小关系*/
{
	putchar('1');
	printf(" %d", r1 - l1 + 1), fflush(stdout);
	for (int i = l1; i <= r1; i++) printf(" %d", i), fflush(stdout);
	printf(" %d", r2 - l2 + 1), fflush(stdout);
	for (int i = l2; i <= r2; i++) printf(" %d", i), fflush(stdout);
	putchar('\n'); char c; return cin >> c, c;
}
void answer(){putchar('2');for (auto i : ans) printf(" %d", i);fflush(stdout);exit(0);} /*输出答案*/
void insert(const int &x) {ans.insert(x);if (ans.size() == 2) return answer();} /*插入答案*/
void solve2(int, int, int);
void solve3(int, int, int);
inline void solve2(int l, int r, int k) /*? 显然，没有客观性*/
{
	if (!k) return void();
	if (l == r) return insert(l);
	int length = r - l + 1, mid = (l + r) >> 1, lmid, rmid;
	char x = query(l, lmid = ((length % 2 == 0) ? (l + r - 1) >> 1 : mid - 1), rmid = ((length % 2 == 0) ? (l + r + 1) >> 1 : mid + 1), r);
	if (x == '=')
	{
		if (k == 1) insert(mid);
		solve3(l, lmid, k - 1);
		solve3(rmid, r, k - 1);
		return void();
	}
	if (k == 1)
	{
		solve3(l, lmid, x == '<');
		solve3(rmid, r, x == '>');
	}
	if (k == 2)
	{
		if (length % 2 == 0 || query(mid, mid, mid + (x == '<' ? 1 : -1), mid + (x == '<' ? 1 : -1)) == '=')
			solve2(l, lmid, (x == '<') * 2), solve2(rmid, r, (x == '>') * 2);
		else
			insert(mid), solve3(l, lmid, x == '<'), solve3(rmid, r, x == '>');
	}
}
inline void solve3(int l, int r, int k)
{
	if (!k) return void();
	int length = r - l + 1, size = length / 3, lmid = l + size - 1, rmid = lmid + size;
	if (length <= 2) return solve2(l, r, k);
	char x = query(l, lmid, lmid + 1, rmid);
	if (x == '=') solve3(rmid + 1, r, 1);
	if (x == '>') solve3(lmid + 1, rmid, 1);
	if (x == '<') solve3(l, lmid, 1);
}
signed main()
{
	cin >> n;
	solve2(1, n, 2);
	answer();
	return 0;
}
```

---

## 作者：Flanksy (赞：5)

### 交互，模拟，二分，三分

思路来自 @[WYXkk](https://www.luogu.com.cn/user/130151) 的题解，由于实现复杂，重点讲解如何实现。

------------

#### 交互实现

天平两端的球数量必须相等，否则询问没有意义，注意每次刷新缓冲区。

使用 ```vector<int>``` 存储一堆小球的编号，重载运算符能方便地合并两堆小球。本文代码中的所有 ```auto``` 都能直接替换为 ```vector<int>```。

```cpp
auto operator+(const auto &x,const auto &y){
	auto ret=x;
	for(int i:y) ret.push_back(i);
	return ret;
}

int cmp(const auto &x,const auto &y){//等重量返回0,x较重返回1,y较重返回-1
	printf("1 %u ",x.size());
	for(int i:x) printf("%d ",i);
	printf("%u ",y.size());
	for(int i:y) printf("%d ",i);
	putchar('\n');
	fflush(stdout);
	static char s[2];
	scanf("%s",s);
	if(s[0]=='=') return 0;
	return s[0]=='<' ? -1:1;
}
```
------------

轻球只有两个，分类讨论三种主要情况。

#### 一堆球中没有轻球

没有轻球毫无价值，不管。

#### 一堆球中仅有一个轻球

将球分成三份，比较其中等量的两份，等重说明轻球在未比较过的一份中，否则轻球在较轻的一份中，递归重复上述步骤。

递归边界：仅剩一个小球。

为减少比较次数，尽可能让分出的每份小球相等。

```cpp
void divI(auto x){
	if(x.empty()) return;
	if(x.size()==1u){
		if(ans[0]==0){ans[0]=x[0];return;}
		else ans[1]=x[0],sort(ans,ans+2),printf("2 %d %d\n",ans[0],ans[1]),exit(0);
	}
	int o,s=x.size(),d=s/3;//均分三份,记录每份大小 
	vector<int> v[3];
	if(s%3==2){//多余两个球 分给v[0]和v[1] (否则2个球的情况无限递归)
		for(int i=0;i<=d;i++) v[0].push_back(x[i]);
		for(int i=d+1;i<=d*2+1;i++) v[1].push_back(x[i]);
		for(int i=d*2+2;i<s;i++) v[2].push_back(x[i]);
	}
	else{//可能多出的1个球归入v[2]不参与比较
		for(int i=0;i<d;i++) v[0].push_back(x[i]);
		for(int i=d;i<d*2;i++) v[1].push_back(x[i]);
		for(int i=d*2;i<s;i++) v[2].push_back(x[i]);
	}
	if((o=cmp(v[0],v[1]))==0) divI(v[2]);
	else divI(~o ? v[1]:v[0]);
}
```
#### 一堆球中存在两个轻球

最开始时的情况。从特殊情况（递归边界）入手，其他三种特殊情况最终都转化成剩余两个球的情况或两个一堆球中仅存在一个轻球的情况。

- 两个球，直接输出答案。
- 三个球，比较其中两个，等重则都是轻球，不等则排除重球。
- 四个球，比较前两个小球，等重说明后两个小球也等重，此时比较第二第三个小球，轻者即为轻球，若前两个小球不等重则分别在两组中寻找一个轻球。
- 五个球，两两分组剩余一个球，比较有两个小球的两组，不等则合并较轻组和剩余的一个球递归寻找其中的两个轻球，否则分别在两组中寻找一个轻球。

当球数大于五时，均分小球为三份，剩余至多两个小球单独处理。

比较两次均分的小球，如果结果相同则只可能是全等重（否则假设第一份有 0 个轻球，第二份有 1 个轻球，则第三份需要 2 个轻球，总数为 3），此时剩余小球必定为两个，且都是轻球。

由于仅有两个轻球，必有两份小球等重，两次比较结果中没有相等说明未比较的两份小球等重，若两份等重小球比第三份轻则分别在两份中寻找一个轻球，否则合并第三份小球和多余小球递归查询。

```cpp
void divII(auto x){
	if(x.empty()) return;
	if(x.size()==2u) printf("2 %d %d\n",x[0],x[1]),exit(0);
	int o;vector<int> v[4];
	if(x.size()==3u){
		for(int i=0;i<3;i++) v[i].push_back(x[i]);
		if((o=cmp(v[0],v[1]))==0) divII(v[0]+v[1]);
		else divII(~o ? v[1]+v[2]:v[0]+v[2]);
	}
	else if(x.size()==4u){
		for(int i=0;i<4;i++) v[i].push_back(x[i]);
		if((o=cmp(v[0],v[1]))==0) divII(~cmp(v[1],v[2]) ? v[2]+v[3]:v[0]+v[1]);
		else divI(v[0]+v[1]),divI(v[2]+v[3])
	}
	else if(x.size()==5u){
		v[0].push_back(x[0]),v[0].push_back(x[1]);
		v[1].push_back(x[2]),v[1].push_back(x[3]);
		v[2].push_back(x[4]);
		if((o=cmp(v[0],v[1]))==0) divI(v[0]),divI(v[1]);
		else divII(~o ? v[1]+v[2]:v[0]+v[2]);
	}
	else{//一般情况
		int s=x.size(),d=s/3;
		for(int i=0;i<3;i++) for(int j=0;j<d;j++) v[i].push_back(x[i*d+j]);
		for(int i=d*3;i<s;i++) v[3].push_back(x[i]);
		int o1=cmp(v[0],v[1]),o2=cmp(v[1],v[2]);
		if(o1==0&&o2==0) divII(v[3]);
		else if(o1==1){//关键:o1!=o2 
			if(o2==0) divI(v[1]),divI(v[2]);
			else divII(v[1]+v[3]);
		}
		else if(o1==0){
			if(o2==1) divII(v[2]+v[3]);
			else divI(v[0]),divI(v[1]);
		}
		else{//o1==-1
			if(o2==0) divII(v[0]+v[3]);
			else divI(v[0]),divI(v[2]);
		}
	}
}
```

**实际上球数大于二的情况都可以一般化处理，但其和上述特判三、四个球的情况相比可能会多比较一次，解法劣化。而且由于两个函数对应的轻球数量不同，一般化处理需要合并二者，增加思维难度和代码难度。**

题目的坑点主要是一般情况的分类讨论和细节问题。对于一般情况全部列举判断，完整[代码](https://www.luogu.com.cn/paste/ia3028k1)里的注释很详细。

---

## 作者：WYXkk (赞：4)

提供一个奇怪的做法（

首先把球均分成三份 $A,B,C$，如果球数不是 $3$ 的倍数就记剩下的一或二个为一份 $D$。

用 $w(X)$ 表示 $X$ 中球的总重。

由于轻球只有两个，故 $A,B,C$ 的重量不会不全相等（否则至少 $0+1+2=3$ 个轻球）。

所以，可以用两次比较得到 $A,B,C$ 的轻重关系。（如果 $w(A)\neq w(B),w(B)\neq w(C)$ 则由上有 $w(A)=w(C)$）

- 情况一：$w(A)=w(B)=w(C)$

  可以推出轻球全在 $D$ 中。而 $D$ 中至多有两个球，那么就做完了。

- 情况二：$w(A)=w(B)>w(C)$

  可以推出 $A,B$ 中都没有轻球，这样只需要递归找 $C\cup D$ 中的两个轻球。

- 情况三：$w(A)>w(B)=w(C)$

  可以推出 $B,C$ 中各有一个轻球。一堆球中找一个轻球是经典小学奥数题（均分为三份，比较其中个数相等的两份，相等则轻球在剩下一组，否则在两组中较轻的那组，如此递归，只需要 $\lceil\log_3 n\rceil$ 次称量，且这是理论下界）。

递归边界：

- $2$ 个球：答案就是这两个。

- $3$ 个球：设三球为 $a,b,c$，$w(a)=w(b)$ 则答案为 $a,b$，否则答案为 $c$ 和 $a,b$ 中轻的那个。

- $4$ 个球：设四球为 $a,b,c,d$。

  - $w(a)=w(b)$

    $w(b)>w(c)$ 则答案为 $c,d$，反之答案为 $a,b$。

  - $w(a)\neq w(b)$

    答案为 $a,b$ 中轻的那个和 $c,d$ 中轻的那个。

- $5$ 个球：设五球为 $a,b,c,d,e$。

  - $w(a,b)=w(c,d)$

    答案为 $a,b$ 中轻的那个和 $c,d$ 中轻的那个。

  - $w(a,b)>w(c,d)$

    用 $3$ 个球的方法找到 $c,d,e$ 中的两个轻球。

经过计算，$n\le 500$ 时这种方法不会使用超过 $12$ 次称量。

~~写起来可能巨大复杂，所以代码咕了~~ [参考实现](https://www.luogu.com.cn/paste/2umie277)（与 @[九九九九](https://www.luogu.com.cn/user/151475) 的方法进行了结合）

------

$f(n)=\left\lceil\log_3\left(\dfrac{n(n-1)}2\right)\right\rceil$ 是容易得到的一个称量次数理论下限。（你要若干次询问来区分 $\dfrac{n(n-1)}2$ 种情况，每次询问有三种结果）

我枚举了 $2\le n\le10^7$，得到了一个表：

| 最坏情况下的称量次数                                     | 为 $f(n)$ 的 $n$ 的个数 | 为 $f(n)+1$ 的 $n$ 的个数 | 为 $f(n)+2$ 的 $n$ 的个数 | 总计      |
| -------------------------------------------------------- | ----------------------- | ------------------------- | ------------------------- | --------- |
| @[九九九九](https://www.luogu.com.cn/user/151475) 的方法 | $7$                     | $7910750$                 | $2089242$                 | $9999999$ |
| 我的方法                                                 | $1316554$               | $5711715$                 | $2971730$                 | $9999999$ |
| 以上两者的结合                                           | $5519262$               | $4480737$                 | $0$                       | $9999999$ |

以及极其低效的 std（改进后）：[8,87284,406516,911635,1494401,1890585,1895631,1523493,984298,509563,209455,67290,16482,2962,367,28,1] 的第 $x$ 项（$8$ 是第 $0$ 项）是 $2\le n\le 10^7$ 中最坏情况下称量次数为 $f(n)+x$ 的 $n$ 的个数。也就是最多会到使用 $f(n)+16$ 次称量……

我猜测有一部分 $n$ 确实没有卡到 $f(n)$ 次的方法。

另外，我怀疑，这玩意在 $n$ 比较大的时候，最小称量次数还是个 open problem……

---

## 作者：yanbinmu (赞：2)

## 题意
交互题。
在 $k$ 此询问内找出 $n$ 个球中两个较轻的球（其他球重量相当，两个较轻的球重量相当）。
## 分析
分类讨论：

1. 有偶数个球。
2. 有奇数个球。
### 偶数个球
如果已知要找一个球，那么分为两组，对轻的那一组递归求解即可。

如果要找两个球，分为两部分后有两种情况：

1. 两球在同一个部分， 则所在的部分一定比零一部分轻。
2. 两球在两部分，则转化为找一个求的情况。

### 奇数个球
如果要找一个球，那么我们可以单独出来个，剩下两部分比较。
如果相同，那么单独出来的是较轻的，否则递归求解。

如果要找两个，同样单独出来一个，并且剩下的分为两部分，那么分为三种情况：

1. 两球分别在两部分，则两部分重量相等，转化为偶数个中找一个或者奇数个中找一个。
2. 两球都在在两部分中的一个，则为较轻的部分。
3. 两球中一个是单独那一个。

那如何分辨 2 和 3 呢？

考虑到假球质量小，那我们就在质量大的那一组挑一个和单独的比。
如果相同，那么就是 2，反之是 3。

但是被卡掉了。

既然二分不行，那我们分成三段可以吗？
好像可以处理只有一个球的情况。

那两个球呢？不行。

那我们只用三分去优化找一个球的情况可不可以？

将整个范围 $n$ 分为以下三段：

- $\lfloor\frac{n}{3}\rfloor$
- $n - 2\lfloor\frac{n}{3}\rfloor$
- $\lfloor\frac{n}{3}\rfloor$

我们去看前后两段的大小，无外乎相等或某一个较大。

如果相等，那么轻的球在中间。

否则，就在轻的那一部分。

可以通过。


```cpp
#include<bits/stdc++.h>
using namespace std;
int ans1, ans2;
char ask(int l, int r, int x, int y) {
	cout << "1 ";
	cout << r - l + 1 << " ";
	for (int i = l;i <= r;i ++ ) {
		cout << i << " ";
	}
	cout << y - x + 1 << " ";
	for (int i = x;i <= y;i ++ ) {
		cout << i << " ";
	}
	cout << endl;
//	fflush(stdout);
	char ch;
	cin >> ch;
	return ch;
}
void print() {
	if(ans1>ans2) swap(ans1, ans2);
	cout << "2 " << ans1 << " " << ans2 <<"\n";
	exit(0);
}
void make_ans(int ans) {
	if(!ans1) ans1 = ans;
	else ans2 = ans, print();
}
void find(int l, int r, int num) {
	if(l == r) {
		make_ans(l);
		return;
	}
	if(num == 1) {
		int midl = l + (r - l)/3;
		int midr = r - (r - l)/3;
		char op = ask(l, midl, midr, r);
		if(op == '=') {
			find(midl + 1, midr - 1, 1);
		}
		if(op == '<') {
			find(l, midl, 1);
		}
		if(op == '>') {
			find(midr, r, 1);
		}
	} 
	else {
		int mid=(l + r) / 2;
		if((r - l + 1) % 2 == 0) {
			char op=ask(l, mid, mid + 1, r);
			if(op == '=') {
				find(l, mid, 1);
				find(mid + 1, r, 1);
			}
			if(op == '<') {
				find(l, mid, 2);
			}
			if(op == '>') {
				find(mid + 1, r, 2);
			}
		}
		else {
			char op=ask(l, mid - 1, mid + 1, r);
			if(op == '=') {
				find(l, mid - 1, 1);
				find(mid + 1, r, 1);
			}
			if(op == '<') {
				char opt=ask(mid, mid, mid + 1, mid + 1);
				if(opt == '=') {
					find(l, mid - 1, 2);
				} 
				else {
					make_ans(mid);
					find(l, mid - 1, 1);
				}
			}
			if(op == '>') {
				char opt = ask(mid, mid, mid - 1, mid - 1);
				if(opt == '=') {
					find(mid + 1, r, 2);
				} 
				else {
					make_ans(mid);
					find(mid + 1, r, 1);
				}
			}
		}
	}
}
int main() {
//	cin.tie(nullptr);
//	cout.tie(nullptr);
	int n;
	cin >> n;
	find(1, n, 2);
}
```

---

## 作者：Little09 (赞：2)



可以先考虑次品只有一个球的情况。这很明显是一个小学数学题，每次尽量平均分成三份，称量球个数相等的两份。如果相等，次品在另外一份；否则次品在轻的那一份。

接下来考虑两个球。这次把它分成两份（多出来的不管），如果相等，那么每一份有一个次品；否则，轻的那一份有两个次品。

递归处理即可。记得注意边界情况。还有分成两份是如果有多出来的球，在往下递归的时候要带上它。

本代码在所有测试点中的最大询问次数是 $12$ 次。看上去很优秀。

代码写得很丑，不放了吧。

[](膜拜rui_er！！！)

---

## 作者：Ian_NIE (赞：1)

## 0x00 前言

又是一道思维题加上交互题，一样，我们还是直接先输出再输入，不需要写奇怪的那种 ```extern "C"```。

## 0x01 题目大意

现在有 $n$ 个球，其中有两个假球。一个假球比一个真球轻，但是两个假球比一个真球重。请在有限的（题目没有明确指出，但是应该是使用最少的步骤数）步骤里找到真球。每一次告诉评测机天枰左和右，评测机可以告诉你这个天枰哪边重，或者一样重。最后输出两个真球，结束。

这里简述一下这道题目评测机返回的信息代表着什么：（AC 的返回信息不用说吧）
- ```Too many queries!```：这代表着你的算法不够优，需要继续改进算法。
- ```Unexpected end of file - int32 expected```：该输出表示你没有输出，有可能一些条件下你的代码没有输出结果。
- ```Wrong answer.```：你的答案是错的，重新检查逻辑。

好了，现在可以想思路了。

## 0x02 算法设计 & 改进

### 0x0001 第一阶段 初遇
对于这个数学问题，不难想到一个小奥问题：在多个球里面找一个假球，这个时候我们的经典做法是三分天枰两边各一堆，天枰下面还剩下一堆。

![](https://cdn.luogu.com.cn/upload/image_hosting/6l2qqe2n.png)

就是这样，所以我们可以学习原问题（我们称它是“天枰一假问题”）也尝试三分。但是，原题是“天枰一假问题”，我们要解决的问题是“天枰双假问题”，不仅如此，题目还给出了关键条件：“两个假球比一个真球重”。现在我们需要考虑在计算两个假球的情况下，这种常规操作是否还具有确定性。

首先，三分，所以必有两堆的个数是一样的，比较这两堆。假设这两堆是 $X$ 和 $Y$，另外一堆是 $Z$，而它们的重量是 $W_X$，$W_Y$ 和 $W_Z$。如果 $W_X = W_Y$，那么你不知道假球是在 $X$ 和 $Y$ 里每个里面各一个还是在 $Z$ 里面。如果 $W_X > W_Y$ 或者 $W_X < W_Y$，那么此时我们能知道的信息更少，虽然知道多的那堆一定全是真球，但是因为剩下的是一大堆，不是 $1$ 个，所以我们不能进行试金石操作，导致失败。

经过上面的反思，我们发现如果下面剩下的是 $1$ 个时很好做，当没有剩下任何球的时候，应该也可以做。这个时候我们果断考虑二分法，这时候有可能会剩下一个，也可能什么也不剩下。假设现在是“$n$ 球天枰二假问题”，那么分成在天枰两边的球的数量一定是 $\lfloor \frac n 2 \rfloor$。我们分类讨论：
- 如果 $2 \mid n$，那么显然不会剩下任何球，如果两边平衡，那么天枰两堆各一个假球，转换为“天枰一假问题”。如果两边不平衡，则更轻的那一边有两个假球，继续递归即可。
- 如果 $2 \nmid n$，那么会剩下一个球，如果两边平衡，因为天平下面只有一个球，所以两边不可能全部都是真球，所以此时天平两边两堆里各一个假球，转换成功。如果不平衡，还是更重的里面全部都是真球，随便取出一个，称之为“试金石”。此时需要检查，如果这个多余的球和“试金石”一样，那么刚刚天枰较轻一侧有两个假球，继续递归。如果不同（一定比“试金石”更轻），那么这是其中一个假球，而刚刚天枰较轻一侧有一个假球，转换成经典问题。

所以，此时我们证明了二分法对于“天枰两假问题”的正确性，一旦只剩下一个球，立即转换成三分即可。

正常的三分法我也列出过程：
- 和上面一样，设这数量相同的两堆是 $X$ 和 $Y$，另外一堆是 $Z$，而它们的重量是 $W_X$，$W_Y$ 和 $W_Z$。
- 如果 $W_X = W_Y$，因为只有一个假球，所以 $Z$ 里面出一个假球，继续递归。
- 如果 $W_X > W_Y$ 或者 $W_X < W_Y$，那么较轻的那个里面出一个假球，同样继续递归。

此时，我们的方法就是不断递归，不能三分就继续二分，直到可以三分。（显然三分比而二分更高效）。此时对于“$n$ 球天平二假问题”，次数为最多就是一直在二分，次数为 $2\log n$，应该可以了吧（然而……）。

### 0x0002 改进？

把这个破百的代码写出来，让同学把代码提交上去（同学比我写的快），然后只得了 [29 分](https://www.luogu.com.cn/record/222711744)。继续思考，对于三分部分，我们可以确定显然不可以进一步改进。但是进而思考二分部分，前面有一个系数 $2$。这个 $2$ 是两次询问，能否直接优化？但是，如果我们可以把哪一个多余的球放在中间，使得两边再进行下一步的时候可以带上这一个球，就可以省去比较另外两个球，这样就可以严格控制在 $\log n$ 次之内。

好了，这下终于写完了，但是还是只有 [54 分](https://www.luogu.com.cn/record/222715310)。

### 0x0003 终结

这时候，我们不得不来处理一下三分存在的问题。

我们先找到三分我们的代码：
```cpp
double m1 = l + (r - l) / 3;
double m2 = l + (r - l) / 3 * 2;
```
这是我们在 $54$ 分代码里的三分：
```cpp
int lmid = l + (r - l + 1) / 3 - 1, rmid = l + (r - l + 1) / 3 * 2 - 1;
```

发现问题了吗？假设现在的区间是 $[l, r]$，那么绝对的三分的左三等分点和右三等分点是 $l + \frac{r - l}3$ 和 $l +\frac{2(r-l)}3$。如果是整数，我们不能简单地理解成距离除以三，而是重新理解，进行分组。

我们首先先确定下来一个块的长度，我们把这个段里面分成的三个块分成 $[l,lmid]$，$[lmid+1,rmid]$ 和 $[rmid+1,r]$，其中前两段长度一定相等，定义这个长度为 $size$，根据正常的小数三分的方法，定义 $size = \lceil \frac{r - l}3\rceil$，可以证明，这样可以保证三个块之间的数目差距最小。使用经典方式，$size \gets  \lfloor \frac{r-l+2}3\rfloor$。此时，可以推出 $lmid \gets l + size - 1$，$rmid \gets l + 2size - 1$。由于 $size$ 是一个长度，所以最后的 $-1$ 是必要的。如果是简单的前面那种情况，模拟一下 $r - l = 7$ 的情况，你会最终卡死在 $0\; 0\; 2$，导致题目出错。（我说的是上面 $54$ 分的那个）

最终我们终于[通过](https://www.luogu.com.cn/record/222889040)了这道题目。

## 0x03 完整代码

思维题目，我不想给代码分述，但是有两个关键点：
- 由于几个函数需要相互调用（二分之后一定是三分，但是由于在二分的时候整体个数是奇数偶数不固定，所以这两种情况我写了两个函数，这两个函数可能会相互调用），所以我们先只写函数签名，再写函数主体，像这样：
  ```cpp
  void func(...);

  void func(...)
  {
      ...;
  }
  ```
- 如果二分但是当前的长度是奇数，那么不应该有返回值，因为有两个假球，不可能区间里所有的球都是假的。但是如果此时长度是偶数，那么如果长度就是 $2$，那么直接返回这两个球即可。如果正在三分，那么现在区间里只有一个假球，如果此时区间长度就是 $1$，那么这时候也需要返回。

完整代码如下：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> fake;
void f_2j(int l, int r);
void f1_2j(int l, int r);
void f_j(int l, int r);

int main(int argc, char** argv)
{
	cin >> n;
	if(n & 1) f1_2j(1, n);
	else f_2j(1, n);
	sort(fake.begin(), fake.end());
	cout << 2 << ' ';
	for(int i = 0; i < fake.size(); i++)
		cout << fake[i] << ' ';
	cout << endl;
	
	return 0;
}

void f_2j(int l, int r)
{
	if(r - l + 1 == 2)
	{
		fake.push_back(l), fake.push_back(r);
		return ;
	}
	int mid = l + r >> 1, size = mid - l + 1;
	// l-mid mid+1-r
	cout << 1 << ' ' << size << ' ';
	for(int i = l; i <= mid; i++)
		cout << i << ' ';
	cout << size << ' ';
	for(int i = mid + 1; i <= r; i++)
		cout << i << ' ';
	cout << endl;
	char ans1;
	cin >> ans1;
	if(ans1 == '=') f_j(l, mid), f_j(mid + 1, r);
	if(ans1 == '<')
	{
		if(size % 2 == 0) f_2j(l, mid);
		if(size % 2 == 1) f1_2j(l, mid);
	}
	if(ans1 == '>')
	{
		if(size % 2 == 0) f_2j(mid + 1, r);
		if(size % 2 == 1) f1_2j(mid + 1, r);
	}
} 
void f1_2j(int l, int r)
{
	int mid = l + r >> 1, size = mid - l;
	// l-mid-1 mid mid+1-r
	cout << 1 << ' ' << size << ' ';
	for(int i = l; i <= mid - 1; i++)
		cout << i << ' ';
	cout << size << ' ';
	for(int i = mid + 1; i <= r; i++)
		cout << i << ' ';
	cout << endl;
	char ans1;
	cin >> ans1;
	if(ans1 == '=') f_j(l, mid - 1), f_j(mid + 1, r);
	if(ans1 == '>')
	{ // l-mid-1都是真的 
		size++;
		if(size % 2 == 0) f_2j(mid, r);
		if(size % 2 == 1) f1_2j(mid, r);
	}
	if(ans1 == '<')
	{ // mid+1-r都是真的 
		size++;
		if(size % 2 == 0) f_2j(l, mid);
		if(size % 2 == 1) f1_2j(l, mid);
	}
}
void f_j(int l, int r)
{
	if(l == r)
	{
		fake.push_back(l);
		return ;
	}
	int lmid = l + (r - l + 2) / 3 - 1, rmid = l + (r - l + 2) / 3 * 2 - 1, size = (r - l + 2) / 3;
	// [l,lmid][lmid+1,rmid][rmid+1,r]
	cout << 1 << ' ' << size << ' ';
	for(int i = l; i <= lmid; i++)
		cout << i << ' ';
	cout << size << ' ';
	for(int i = lmid + 1; i <= rmid; i++)
		cout << i << ' ';
	cout << endl;
	char ans;
	cin >> ans;
	if(ans == '=') f_j(rmid + 1, r);
	if(ans == '>') f_j(lmid + 1, rmid);
	if(ans == '<') f_j(l, lmid);
}
```

这样就结束了。

## 0x04 结尾

本题算法：递归，数学。

制作不易，AC 记录已经在上面附上了。

---

## 作者：Fisher9 (赞：1)

**题意**

有一些球,其中有两个小球比其他的轻且这两个球等重。有一个天平，只能量出两边等重或一边更轻（重）三种情况。现在要在有限次称量内找出较轻的两个小球。

**前言**

我的第一感觉：很像标准小奥题，一堆球乘几次，要找到更轻的一个小球。这种题时，一般办法是三分，将球分为三堆，取两堆数量相等的称量。相等就说明特殊的球在另一堆里，否则就是在更轻的那堆。

**实际称量方法**

这道题能三分吗？似乎不行，如果一开始两堆重量相等，那不能确定是两堆中各有一个轻的小球还是第三堆里有两个轻的球。所以一开始只能二分。这里分为两种情况：

情况一：小球数目为偶数，可以均分为两堆，若重量相等，说明两边各有一个轻球，否则两个轻的球就是在较轻一边，可以对这一边继续处理。

情况二：小球数目为奇数，可以分为两堆数量相等的球和多出的一个球，并对两堆相等的球进行称量，若重量相等，只能是两边各有一个轻球，否则如果一边更重，就说明这边没有轻球，只需对剩下的那一堆与多出的球进行处理。

按照上面的分法，要么最后还剩两个球，都只能是轻球，要么就得到了两堆球，其中各有一个轻球，可以三分处理。

**代码部分**

先是三分部分，可以递归处理。

```cpp
int find1(int l,int r){//轻的一个球在区间[l,r]内
	if(l==r) return l;//只剩一个球时返回，这个就是轻球
	int t=(r-l+2)/3;//分成三堆，这里t表示称量的两堆中有多少球
	cout<<1<<" "<<t;
	for(int i=l;i<=l+t-1;i++){
		cout<<" "<<i;
	}
	cout<<" "<<t;
	for(int i=l+t;i<=l+t*2-1;i++){
		cout<<" "<<i;
	}
	cout<<endl;//询问部分
	cin>>c;
	if(c=='=') return find1(l+2*t,r);//相等取第三堆
	else if(c=='<') return find1(l,l+t-1);
	else return find1(l+t,l+2*t-1);//不相等说明轻的一边有轻球
}
```
这里要注意三分时称量的两堆小球个数 $t$ 的值应为 $t=(r-l+2)\div3$ 而不是 $t=(r-l+1)\div3$，否则剩两个球会无限循环，~~我在这卒了好几次~~。

接下来写初始的二分，一旦找出一堆中只有一个轻球，就调用 $\operatorname{find1}$ 查询。

```cpp
void find2(int l,int r){//左右区间
	if(r-l==1){
		cout<<2<<" "<<l<<" "<<r;
		return;//如果剩两个球就说明这两个球是轻球
	}
	int x,y;
	int t=r-l+1;
	if(t%2==0){//偶数情况
		t/=2;
		cout<<1<<" "<<t;
		for(int i=l;i<=l+t-1;i++){
			cout<<" "<<i;
		}
		cout<<" "<<t;
		for(int i=l+t;i<=r;i++){
			cout<<" "<<i;
		}
		cout<<endl;
		cin>>c;
		if(c=='='){
			x=find1(l,l+t-1);
			y=find1(l+t,r);//两堆分别寻找轻球
			cout<<2<<" "<<x<<" "<<y;
		}	
		else if(c=='<') find2(l,l+t-1);
		else find2(l+t,r);//不等重就在轻的一边继续找
	}
	else{
		t/=2;
		cout<<1<<" "<<t;
		for(int i=l;i<=l+t-1;i++){
			cout<<" "<<i;
		}
		cout<<" "<<t;//这里将中间编号l+t的球剩下了，为了保证不管测哪堆球都是连续区间。
		for(int i=l+t+1;i<=r;i++){
			cout<<" "<<i;
		}
		cout<<endl;
		cin>>c; 
		if(c=='='){
			int x=find1(l,l+t-1);
			int y=find1(l+t+1,r);
			cout<<2<<" "<<x<<" "<<y;
		}	
		else if(c=='<') find2(l,l+t);
		else find2(l+t,r);
	}
	
}
```
这一部分的坑主要是输出部分，因为可能多次返回，所以要注意只在确定轻球编号后输出一遍结果。最终大约会问 $2\times\log_{3}(x)$ 次，在规定的次数内。

最后奉上完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char c;
int find1(int l,int r){//找到一个轻球
	if(l==r){
		return l;//分到最后返回轻球编号
	}
	int t=(r-l+2)/3;
	cout<<1<<" "<<t;
	for(int i=l;i<=l+t-1;i++){
		cout<<" "<<i;
	}
	cout<<" "<<t;
	for(int i=l+t;i<=l+t*2-1;i++){
		cout<<" "<<i;
	}
	cout<<endl;
	cin>>c;
	if(c=='=') return find1(l+2*t,r);
	else if(c=='<') return find1(l,l+t-1);
	else return find1(l+t,l+2*t-1);
}
void find2(int l,int r){//找到两个轻球
	if(r-l==1){
		cout<<2<<" "<<l<<" "<<r;
		return;
	}
	int x,y;
	int t=r-l+1;
	if(t%2==0){
		t/=2;
		cout<<1<<" "<<t;
		for(int i=l;i<=l+t-1;i++){
			cout<<" "<<i;
		}
		cout<<" "<<t;
		for(int i=l+t;i<=r;i++){
			cout<<" "<<i;
		}
		cout<<endl;
		cin>>c;
		if(c=='='){
			x=find1(l,l+t-1);
			y=find1(l+t,r);
			cout<<2<<" "<<x<<" "<<y;
		}	
		else if(c=='<') find2(l,l+t-1);
		else find2(l+t,r);
	}
	else{
		t/=2;
		cout<<1<<" "<<t;
		for(int i=l;i<=l+t-1;i++){
			cout<<" "<<i;
		}
		cout<<" "<<t;
		for(int i=l+t+1;i<=r;i++){
			cout<<" "<<i;
		}
		cout<<endl;
		cin>>c; 
		if(c=='='){
			int x=find1(l,l+t-1);
			int y=find1(l+t+1,r);
			cout<<2<<" "<<x<<" "<<y;//统计后输出
		}	
		else if(c=='<') find2(l,l+t);
		else find2(l+t,r);
	}
	
}
int main(){
	int n;
	cin>>n;
	find2(1,n);
}
```

---

## 作者：yanxu_cn (赞：0)

目前。。貌似是最优解（交互次数目前最优秀）？

简单的非传统题。

考虑一个区间只有一个轻球，这时根据小学奥数知识可以将区间分成尽可能等长的三段，询问等长度的前两段，然后就可以一次将区间范围的期望缩小到原区间的 $\displaystyle\frac{1}{3}$。

那么如果一个区间有两个轻球呢？我们考虑如果要完美的区分，只能将区间分成 $m+1+m$ 或者 $m+m$ 这些段。这样可以一次将区间约缩小 $\displaystyle\frac{1}{2}$。如果结果是 `=` 那么轻球在两个 $m$ 之内各有一个。如果是 `<` 那么轻球的可能区间可以去掉右边的 $m$。相反类似。于是可以缩小区间。我们可以先不断二分缩小区间，等到两个球分开时就可以用上面的方法。

然后就可以了。

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	int l1=1,l2=1,r1=n,r2=n;
	while(l1<r1&&l1==l2&&r1==r2)
	{
		int mid=l1+r1-1>>1;
		int lx1=l1,rx1=mid,lx2=r1-mid+l1,rx2=r1;
		cout<<"1 "<<mid-l1+1<<' ';
		for(int i=lx1;i<=rx1;i++)
		{
			cout<<i<<' ';
		}
		cout<<mid-l1+1<<' ';
		for(int i=lx2;i<=rx2;i++)
		{
			cout<<i<<' ';
		}
		cout<<endl;
		char chr;
		cin>>chr;
		if(chr=='=')
		{
			r1=rx1;
			l2=lx2;
		}
		else if(chr=='<')
		{
			r1=r2=lx2-1;
		}
		else if(chr=='>')
		{
			l1=l2=rx1+1;
		}
	}
	while(l1<r1)
	{
		int len=(r1-l1+2)/3;
		int lx1=l1,rx1=l1+len-1,lx2=rx1+1,rx2=lx2+len-1,lx3=rx2+1,rx3=r1;
		cout<<"1 "<<len<<' ';
		for(int i=lx1;i<=rx1;i++)
		cout<<i<<' ';
		cout<<len<<' ';
		for(int i=lx2;i<=rx2;i++)
		cout<<i<<' ';
		cout<<endl;
		char chr;
		cin>>chr;
		if(chr=='=')l1=lx3,r1=rx3;
		else if(chr=='<')l1=lx1,r1=rx1;
		else if(chr=='>')l1=lx2,r1=rx2;
	}
	while(l2<r2)
	{
		int len=(r2-l2+2)/3;
		int lx1=l2,rx1=l2+len-1,lx2=rx1+1,rx2=lx2+len-1,lx3=rx2+1,rx3=r2;
		cout<<"1 "<<len<<' ';
		for(int i=lx1;i<=rx1;i++)
		cout<<i<<' ';
		cout<<len<<' ';
		for(int i=lx2;i<=rx2;i++)
		cout<<i<<' ';
		cout<<endl;
		char chr;
		cin>>chr;
		if(chr=='=')l2=lx3,r2=rx3;
		else if(chr=='<')l2=lx1,r2=rx1;
		else if(chr=='>')l2=lx2,r2=rx2;
	}
	cout<<"2 "<<min(l1,l2)<<' '<<max(l1,l2)<<endl;
	return 0;
}
```

---

