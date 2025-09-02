# Turtle and an Incomplete Sequence

## 题目描述

Turtle was playing with a sequence $ a_1, a_2, \ldots, a_n $ consisting of positive integers. Unfortunately, some of the integers went missing while playing.

Now the sequence becomes incomplete. There may exist an arbitrary number of indices $ i $ such that $ a_i $ becomes $ -1 $ . Let the new sequence be $ a' $ .

Turtle is sad. But Turtle remembers that for every integer $ i $ from $ 1 $ to $ n - 1 $ , either $ a_i = \left\lfloor\frac{a_{i + 1}}{2}\right\rfloor $ or $ a_{i + 1} = \left\lfloor\frac{a_i}{2}\right\rfloor $ holds for the original sequence $ a $ .

Turtle wants you to help him complete the sequence. But sometimes Turtle makes mistakes, so you need to tell him if you can't complete the sequence.

Formally, you need to find another sequence $ b_1, b_2, \ldots, b_n $ consisting of positive integers such that:

- For every integer $ i $ from $ 1 $ to $ n $ , if $ a'_i \ne -1 $ , then $ b_i = a'_i $ .
- For every integer $ i $ from $ 1 $ to $ n - 1 $ , either $ b_i = \left\lfloor\frac{b_{i + 1}}{2}\right\rfloor $ or $ b_{i + 1} = \left\lfloor\frac{b_i}{2}\right\rfloor $ holds.
- For every integer $ i $ from $ 1 $ to $ n $ , $ 1 \le b_i \le 10^9 $ .

If there is no sequence $ b_1, b_2, \ldots, b_n $ that satisfies all of the conditions above, you need to report $ -1 $ .

## 说明/提示

In the first test case, $ [4, 2, 1, 2, 1, 2, 1, 3] $ can also be the answer, while $ [4, 2, 5, 10, 5, 2, 1, 3] $ and $ [4, 2, 1, 2, 1, 2, 1, 4] $ cannot.

In the second test case, $ [1, 2, 5, 2] $ can also be the answer.

From the fourth to the sixth test cases, it can be shown that there is no answer, so you should output $ -1 $ .

## 样例 #1

### 输入

```
9
8
-1 -1 -1 2 -1 -1 1 -1
4
-1 -1 -1 -1
6
3 -1 -1 -1 9 -1
4
-1 5 -1 6
4
2 -1 -1 3
4
1 2 3 4
2
4 2
5
-1 3 -1 3 6
13
-1 -1 3 -1 -1 -1 -1 7 -1 -1 3 -1 -1```

### 输出

```
4 9 4 2 4 2 1 2
7 3 6 13
3 1 2 4 9 18
-1
-1
-1
4 2
6 3 1 3 6
3 1 3 1 3 7 3 7 3 1 3 1 3```

# 题解

## 作者：EuphoricStar (赞：11)

特判全是 $-1$ 的情况。

考虑把所有值不是 $-1$ 的位置提取出来，设其为 $c_1, c_2, \ldots, c_k$。$[1, c_1 - 1]$ 和 $[c_k + 1, n]$ 的 $-1$ 是好处理的，不断乘 $2$ 除 $2$ 即可。容易发现 $[c_1 + 1, c_2 - 1], [c_2 + 1, c_3 - 1], \ldots, [c_{k - 1} + 1, c_k - 1]$ 的构造互相独立，所以我们现在只考虑解决 $a'_1 \ne -1, a'_n \ne -1$ 且 $a'_2 = a'_3 = \cdots = a'_{n - 1} = -1$ 的问题。

容易发现若 $a_i$ 确定，那么 $a_{i + 1}$ 只可能是 $\left\lfloor\frac{a_i}{2}\right\rfloor, 2a_i, 2a_i + 1$ 其一。

发现 $a_i \to a_{i + 1}$ 实质是在满二叉树上走了一条边。因此问题被转化成求一条满二叉树上给定起点 $a'_1$、终点 $a'_n$ 和经过的点数 $n$ 的路径。例如 $a' = [3, -1, -1, -1, 9]$ 就相当于是找到 $3 \to 9$ 在满二叉树上的一条经过点数为 $5$ 的路径：

![](https://espresso.codeforces.com/73a467f47aacc1ec97b8f8ae8008ac6212511866.png)

考虑先求出 $a'_1 \to a'_n$ 在满二叉树上的最短路（可以先求出两点的 LCA，最短路就是 $a'_1 \to \text{LCA}(a'_1, a'_n) \to a'_n$），设其经过的点数为 $l$，那么无解当且仅当 $l > n$ 或 $l$ 和 $n$ 的奇偶性不同。否则我们先把 $a'_1, a'_2, \ldots, a'_l$ 填上求出来的最短路，然后在 $a'_n$ 和 $2a'_n$ 反复横跳即可。

时间复杂度：每个测试用例 $O(n)$ 或 $O(n \log V)$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 200100;

int n, a[maxn];

inline vector<int> path(int x, int y) {
	vector<int> L, R;
	while (__lg(x) > __lg(y)) {
		L.pb(x);
		x >>= 1;
	}
	while (__lg(y) > __lg(x)) {
		R.pb(y);
		y >>= 1;
	}
	while (x != y) {
		L.pb(x);
		R.pb(y);
		x >>= 1;
		y >>= 1;
	}
	L.pb(x);
	reverse(R.begin(), R.end());
	for (int x : R) {
		L.pb(x);
	}
	return L;
}

void solve() {
	scanf("%d", &n);
	int l = -1, r = -1;
	vector<int> vc;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (a[i] != -1) {
			if (l == -1) {
				l = i;
			}
			r = i;
			vc.pb(i);
		}
	}
	if (l == -1) {
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", (i & 1) + 1, " \n"[i == n]);
		}
		return;
	}
	for (int i = l - 1; i; --i) {
		a[i] = (((l - i) & 1) ? a[l] * 2 : a[l]);
	}
	for (int i = r + 1; i <= n; ++i) {
		a[i] = (((i - r) & 1) ? a[r] * 2 : a[r]);
	}
	for (int _ = 1; _ < (int)vc.size(); ++_) {
		int l = vc[_ - 1], r = vc[_];
		vector<int> p = path(a[l], a[r]);
		if (((int)p.size() & 1) != ((r - l + 1) & 1) || r - l + 1 < (int)p.size()) {
			puts("-1");
			return;
		}
		for (int i = 0; i < (int)p.size(); ++i) {
			a[l + i] = p[i];
		}
		for (int i = l + (int)p.size(), o = 1; i <= r; ++i, o ^= 1) {
			a[i] = (o ? a[i - 1] * 2 : a[i - 1] / 2);
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d%c", a[i], " \n"[i == n]);
	}
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

附：更简单的实现：

```cpp
#include <cstdio>
const int maxn = 200100;
int n, a[maxn];
void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	int lst = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] != -1) {
			if (!lst) {
				for (int j = i - 1, o = 1; j; --j, o ^= 1) a[j] = (o ? a[i] * 2 : a[i]);
				lst = i;
				continue;
			}
			int x = lst, y = i;
			while (y - x > 1) {
				if (a[x] > a[y]) a[x + 1] = a[x] / 2, ++x;
				else if (a[x] < a[y]) a[y - 1] = a[y] / 2, --y;
				else a[x + 1] = a[x] > 1 ? a[x] / 2 : a[x] * 2, ++x;
			}
			if (a[y] != a[x] / 2 && a[x] != a[y] / 2) return (void)puts("-1");
			lst = i;
		}
	}
	if (!lst) {
		for (int i = 1; i <= n; ++i) printf("%d%c", (i & 1) + 1, " \n"[i == n]);
		return;
	}
	for (int i = lst + 1, o = 1; i <= n; ++i, o ^= 1) a[i] = (o ? a[lst] * 2 : a[lst]);
	for (int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i == n]);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}

```

---

## 作者：Disjoint_cat (赞：11)

# [CF1981C](https://www.luogu.com.cn/problem/CF1981C)

众所周知一篇题解需要一张头图。

![](https://cdn.luogu.com.cn/upload/image_hosting/5sfso9km.png)

## 题意

给一个长 $n$ 的序列 $a$，要求把 $a$ 中所有的 $-1$ 替换为任意正整数，且满足对于所有的 $1\le i<n$，要么 $a_i=\lfloor\frac{a_{i+1}}2\rfloor$，要么 $a_{i+1}=\lfloor\frac{a_i}2\rfloor$。

Data range：$n\le2\times10^5$。

## 题解

可以发现每个 $-1$ 组成的连续段中的问题是独立的。

然后如果一个连续段一边是边界，那么问题是简单的。（此时只有一端有限制，你随便怎么填都行，只要别爆范围。）

所以原问题可以转化为：

> 给出 $m,L,R$，构造序列 $f_0,f_1,\ldots,f_m$，满足：
> 
> - $f_0=L,f_m=R$；
> - 对于 $0\le i<m$，$f_{i+1}\in\{\lfloor\frac{f_i}2\rfloor,2f_i,2f_i+1\}$。

此时可以发现这个转化后的问题实质上就是一个初值为 $L$ 的变量 $x$，你需要构造一个 $m$ 次操作的序列，使得 $x$ 最终变成 $R$。

然后可以发现，一次操作相当于在 $x$ 的二进制表示中抠掉末位（除以 $2$）或者加一位（乘 $2$，然后可以再加 $1$）。

先只考虑把 $x$ 从 $L$ 变成 $R$。观察到加位后删位对此没有任何意义（因为这相当于什么都不做），所以你的操作一定是先删一坨位，等到能只通过加位变成 $R$ 再把它加到 $R$。

如果此时操作次数不够就直接炸了。然后如果剩下的操作数是偶数，则一直在 $2R$ 和 $R$ 之间反复横跳就行了。

如果剩下奇数次，则也炸了。因为一次操作必然使 $\mathrm{highbit}(x)$（二进制下为 $1$ 的最高位）加 $1$ 或减 $1$，奇偶性一定改变，最后 $\mathrm{highbit}(x)$ 和 $\mathrm{highbit}(R)$ 奇偶性一定不同，更别说相等了。

综上，时间复杂度为 $\Theta(n)$，如果写得丑可能多只 $\log$ 但没什么问题。

[赛时 submission](https://codeforces.com/contest/1981/submission/263468223)。

---

## 作者：Louis_lxy (赞：7)

## 前言

注：参考 @Disjoint_cat 的思路，写的详细一点然后代码再加个注释方便理解。

## 思路

首先，很明显，对于一段连续的由 $-1$ 组成的子串，一定不与其他由 $-1$ 组成的子串相关（这里默认两个子串不重合）。于是可以单独考虑每个子串。

如果设 $L$ 为子段的前一个的数字（即第一个不是 $-1$ 的数字），$R$ 为子串最后一个数的后一个数，$m$ 为其长度，$f$ 为长度为 $m+1$ 的答案数组，观察题目条件后易得如下结论：

令 $f_0=L,f_m=R$。

有对于 $0\le i<m，f_{i+1}\in\{\lfloor \frac{f_i}{2},2f_i,2f_i+1 \rfloor\}$。

简单解释一下原因，第一个很显然就不多说了，第二和第三个是由于 $b_i=\lfloor \frac{b_{i+1}}{2}\rfloor$，所以 $b_{i+1}\in\{2b_i,2b_i+1\}$。

然后我们就可以发现，此时这个问题已经被我们转化成，使用 $m$ 次按上述规则的变换，变成 $R$。

然后再仔细观察变化规则，其实 $\lfloor \frac{f_i}{2}\rfloor$ 就相当于去掉二进制的最后一位，$2f_i$ 就相当于在最后一位后添上 $0$。$2f_i+1$ 就相当于在最后一位后添上 $1$。

于是我们考虑转化过程，显然不可能先去掉在添回去（除非步骤多了），于是过程一定是先去掉一些 $L$ 的位数（只能删末位），然后再添回 $R$（往末位添）。

如果操作次数不够，那么一定不可能有结果，输出 $-1$。如果是省下的操作奇数次，显然不可能变回去了，想不通的建议重学小学课本，因为位数奇偶性不同，所以一定不可能相等。

最终时间复杂度 $O(n)$。

以上那位大佬也讲了，不过大佬讲的比较简洁，我就再补充一些细节。

首先，要额外考虑前面和后面是一串 $-1$。显然，如果在前端，只需要不断输出 $1$ 和 $2$ 即可，如果在后端，则需要先不断变小，如果不够就不断输出 $1$ 和 $2$。

然后再说一个投机取巧的方式，c++ 为我们提供了一个函数 `__builtin_clz`，它是用来求一个无符号整数前导 $0$ 的个数，但是也可以求有符号整数的，不过它会忽略符号位，显然用 `32-__builtin_clz(x)` 求的就是 $x$ 不含前导 $0$ 的位数（如果是有符号整数就是 `31-__builtin_clz(x)`）。

其它的详见代码注释。

## AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n;
		scanf("%d", &n);
		bool ok = true;
		vector<int> ans;
		for (int i = 1, L = 0, m = 0, R;; ++i)//L是左端点，R是右端点，m是长度
		{
			if (i > n)
			{
				if (ok)
					for (int j = 1; j <= m; ++j)
						ans.push_back(L > 1 ? L >>= 1 : L = 2);//如果最右端有一串-1
				break;
			}
			scanf("%d", &R);
			if (!ok) continue;
			++m;
			if (~R)//判断它是否是-1，如果不是-1就进行如下操作
			{
				if (L)
				{
					int x = 31 - __builtin_clz(L), y = 31 - __builtin_clz(R);//x表示L的位数，y表示R的位数
					if ((y - x - m) & 1 || m < abs(y - x)) ok = false;//y-x-m为剩余的操作次数，如果它是奇数或省下的次数不够则不可能有结果
					else
					{
						int t = min({x, y, (m - abs(y - x)) / 2});//显然操作次数是x和y的最小值或者省下偶数次就直接不断在R和2R横跳
						for (int j = 1; j <= t + max(x - y, 0); ++j)//先去掉L的一串末位
							ans.push_back(L >>= 1), --m;
						for (int j = t + max(y - x, 0) - 1; ~j; --j)//再给添上一些末位
							ans.push_back(L = (L << 1) | ((R >> j) & 1)), --m;
						if (L != R) { ok = false; continue; }//如果两数不相等说明不可能的到结果
						while (m) ans.push_back(L << 1), ans.push_back(L), m -= 2;//如果剩余偶数次，则在R和2R之间横跳
					}
				}
				else
				{
					int t = R; ans.push_back(R);
					for (int j = 1; j < m; ++j)//如果最左端有一串-1
						ans.push_back(t > 1 ? t >>= 1 : t = 2);
					reverse(ans.begin(), ans.end());//原本是倒序存储（因为接触点在后面），但是也可以直接在前面写然后翻转（因为用的是vector所以没法倒序存储）
				}
				L = R, m = 0;//重置
			}
		}
		if (ok)
		{
			for (int i : ans) printf("%d ", i);
			putchar(10);
		}
		else printf("-1\n");
	}
	return 0;
}
```

顺便贴上赛后 AC 记录：[洛谷](https://www.luogu.com.cn/record/161537080)、[CF](https://codeforces.com/contest/1981/submission/264605667)，（洛谷可能看不了）。

---

## 作者：eb0ycn (赞：2)

一眼出结论，但是场上没调出来，遗憾离场，痛失青名。

传送门：[CF1981C](https://www.luogu.com.cn/problem/CF1981C)。

## 题意

给定数列 $a$，构造数列 $b$，满足：

1. 对于 $i \in [1,n-1]$，要么 $b_i=\lfloor \frac{b_{i+1}}{2} \rfloor$，要么 $b_{i+1}=\lfloor \frac{b_i}{2} \rfloor$；

1. 对于满足 $a_i \ne -1$ 的 $i$，要保证 $b_i=a_i$；

1. $1 \leq b_i \leq 10^9$。

或报告无解。

## 思路

首先，观察其本质：$b_{i+1}$ 相对于 $b_i$，实际上有两种可能：要么去掉 $b_i$ 二进制下最后一位，要么在后面加上一位。

考虑只有一个 $a_i \neq -1$ 的时候，我们可以在它两边不断 $\times2$ 和 $\div 2$。

只有两个的时候，假设这两个下标是 $i,j$。

首先，在它们两边的位置直接乘二除以二交替就行了。关键考虑它们之间的位置怎么构造。

$a_i$ 要变成 $a_j$，最暴力的方法显然是一直除以二把它变成 $1$，再一位位加到 $a_j$。但是这种做法太不牛了，因为 $a_i$ 和 $a_j$ **二进制前缀的公共部分**是不用继续操作的。

![解释](https://cdn.luogu.com.cn/upload/image_hosting/bon461zo.png)

这样就能计算它们变换的最小步数。

- 如果它们实际的距离小于最小步数，肯定总司令；
- 如果实际距离大于最小步数，可以交替乘二除以二，此时如果实际距离和最小步数不同奇偶，照样总司令。

接着考虑多个 $a_i \ne -1$ 的情况，显然可以对每对相邻的 $i,j$ 考虑。

然后就做完了，但是代码有亿点点屎，细节也有亿点点多。

时间复杂度：$O(n \log V)$。

## 代码

```cpp
#include<cstdio>
using namespace std;
int t,n,a[200001],real[200001],cnt,b[200001],res,pop[200001],dis1,len,dis2,dis,now,jian;
bool flg,ret[200001][28];
int popc(int ppp,int x){
	res=0;
	while(x)ret[ppp][res++]=x&1,x>>=1;
	return res;
}
int min(int p,int q){return p>q?q:p;}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n),flg=cnt=0;
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			if(~a[i])real[++cnt]=i,pop[cnt]=popc(cnt,a[i]),b[i]=a[i];
		}if(!cnt)for(int i=1;i<=n;++i)printf("%d ",1<<(i&1));
		if(cnt==1)for(int i=1;i<=n;++i)printf("%d ",a[real[1]]<<(200000+real[1]-i&1));
		if(cnt>1){
			for(int i=1;i<real[1];++i)b[i]=a[real[1]]<<(real[1]-i&1);
			for(int i=real[cnt]+1;i<=n;++i)b[i]=a[real[cnt]]<<(i-real[cnt]&1);
			for(int i=1;i<cnt;++i){
				now=pop[i],jian=0,len=real[i+1]-real[i];
				for(int j=0;j<min(pop[i],pop[i+1]);++j){
					if(ret[i][pop[i]-j-1]==ret[i+1][pop[i+1]-j-1])++jian;
					else break;
				}
				dis1=pop[i]-jian,dis2=pop[i+1]-jian,dis=dis1+dis2;
				if(len<dis||dis-len&1){flg=1;break;}
				for(int j=1;j<=dis1;++j)b[j+real[i]]=b[j+real[i]-1]>>1,--now;
				for(int j=dis1+1;j<dis;++j)++now,b[j+real[i]]=b[j+real[i]-1]<<1|(a[real[i+1]]>>pop[i+1]-now&1);
				for(int j=dis;j<len;++j)b[j+real[i]]=a[real[i+1]]<<(j-dis&1);
			}if(flg)printf("-1");
			else for(int i=1;i<=n;++i)printf("%d ",b[i]);
		}printf("\n");
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：1)

吐槽：恶心题，赛后才调出来一发过/tuu。

友情提示：这场比赛 CF 有中文官方题解哦！这题使用中文版官方题解 LCA 做也是很好的一种方法。
# 思路
首先不难发现，一个数先乘 $2$ 后除 $2$ 会得到原数。若 $a$ 和 $b$ 间有 $c$ 个 $-1$，则我们可以对 $a$ 先除后乘得到 $b$，最后浪费多余的 $-1$。

首先我们当然贪心考虑最少的乘除次数，那时，$a$ 被除后的“渣渣”$c$ 的二进制是 $b$ 的前缀，此时只要从前缀后一位开始，逐位考虑是否需要在乘 $2$ 后加 $1$。此时，如果 $-1$ 不够用了或剩下的 $-1$ 是奇数，则无解。

最后考虑前缀 $-1$ 和后缀 $-1$。首先整个数列都是 $-1$ 特判一下，$1,2$ 交替输出就行。其次前后缀 $-1$ 处理方法都一样，可以对最前（最后）的非 $-1$ 进行 $1,2$ 倍交替输出就可以。

代码过长，故放个 [CF 提交记录链接](https://codeforces.com/problemset/submission/1981/263703364)（含代码）。

---

## 作者：SamHJD (赞：1)

> 给出一个序列 $a$，你需要构造一个序列 $b$，满足：
>
> * 若 $a_i$ 不为 $-1$，那么 $b_i=a_i$。
> * 否则 $b_i=\left\lfloor\dfrac{b_{i+1}}{2}\right\rfloor$ 或者 $b_{i+1}=\left\lfloor\dfrac{b_{i}}{2}\right\rfloor$​。
>
> 或输出无解。

不妨画出这样一棵带点权的二叉树，根的值为 $1$，设节点 $x$ 的权值为 $v_x$，那么其两个儿子的权值为 $2 v_x,2v_x+1$。不难发现这棵树上移动一步权值的变化相当于 $b_i$ 到 $b_{i+1}$ 的变化。

不难发现 $a$ 中连续一段 $-1$ 的构造是相互独立的，我们考虑长为 $x$ 的一段连续的 $-1$，这段 $-1$ 左右两端的值为 $a,b$，问题可以转化为找出上文构造的树上一条从值为 $a$ 的点到值为 $b$ 的点的一条长为 $x$ 的路径。

于是求出 $a,b$ 的 LCA，若移动到 LCA 后剩余步数为偶数，可以在一条边上反复移动，否则无解。

实现时可判断 $a$ 往右一直除 $2$ 和 $b$ 往左一直除二是否有一个位置相同，或两数除到 $1$ 中间隔的位置数量是否为奇数。

---

## 作者：2022liaojianxiang (赞：0)

由题目可知我们需要构造一组新的解满足数字不超过 $10^9$ 并且相邻两个数必须有其中一个是另一个的 $2$ 倍或 $2$ 倍 $+1$。那么我们发现这其实和二进制很像：等同于相邻的必须有一个是另一个在末尾加上一个 $0$ 或 $1$ 的新二进制位数。那么我们思考怎么从题目入手。

可以发现两个已经填了数字的（且中间没有填数，全为 $-1$）的数才是有关联的，并且两两之间相互独立。

如：数列 $[3,-1,-1,4,-1,5]$ 中，我们只需要处理 $3$ 变化到 $4$ 的过程和 $4$ 变化到 $5$ 的过程而不需要处理 $3$ 变化到 $5$ 的过程，他们之间两两才有联系，其余互相独立。

那么我们思考怎么从一个数转化到另一个数。我们先思考需要的最少步数，这可以方便我们判断中间的空缺数量是否足够我们的变换。我们发现我们的操作可以是从当前二进制数中删掉最后一个数和在当前二进制数中的末尾添加任意一个数 $0$ 或 $1$。那么做法很明显了：我们找到两个数最长公共前缀，从第一个数开始删除直到公共前缀然后再一点点加上后面变换的数的每一个位置所对应的数。

如：$10011101$ 要变换到 $1001010$。也就是先找到最长公共前缀 $1001$，然后把第一个数删去后面 $4$ 位剩下前缀，再补上第二个数后面的 $3$ 位即为最快方法，需要 $7$ 步，也就是这两个数中间应该至少有 $6$ 个 $-1$。

但是要注意并不是中间的 $-1$ 有我们需要的那么多就可以实现，我们还要注意如果当前他还多出来一个 $-1$ 的位置使得我想要转化当前数又变成当前数（也就是多出来的数量为奇数），那这是不可能的。如果多出来的数量为大于 $0$ 的偶数，那么我们可以先让它乘个 $2$ 再除以一个 $2$，都可以总之最后要使得它是原来这个数。

如：$[3,-1,-1,3]$ 是无法转换的，如果想要转换 $[3,-1,-1,-1,3]$，可以将数组变成 $[3,6,3,6,3]$。

最后就可以用模拟的方式做掉这题。
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i(l),i##End(r); i<=i##End; ++i)
using namespace std;
using ll=long long;
const int N=2e5+5,P=998244353;
int n,a,ls,b[N],s,f1[N],f2[N],o;
int dg(int x,int y,int g,int p)
{
	if(x==-1)
	{
		b[g+1]=y;
		for(int i=g;i>=1;i--)
		{
			if(b[i+1]*2<1e9) b[i]=b[i+1]*2;
			else b[i]=b[i+1]/2;
		}
		return 0;
	}
	int c1=x,c2=y,t1=0,t2=0,t=0,e;
	while(c1) f1[++t1]=c1%2,c1/=2;
	while(c2) f2[++t2]=c2%2,c2/=2;
	c1=c2=0;
	while(t<t1&&t<t2)
	{
		c1=c1*2+f1[t1-t],c2=c2*2+f2[t2-t];
		if(c1!=c2) break;
		t++;
	}
	e=t1+t2-2*t-1;
	if(e>g||(g-e)%2) return 1;
	c1=x;
	rep(i,p,p+t1-t-1) c1/=2,b[i]=c1;
	for(int i=p+t1-t,j=t2-t;i<=p+e;i++,j--) b[i]=b[i-1]*2+f2[j];
	rep(i,p+e+1,p+g)
	{
		if(b[i-1]==y) b[i]=b[i-1]*2;
		else b[i]=b[i-1]/2;
	}
	return 0;
}
void _main()
{
	cin>>n,ls=-1,s=0,o=0;
	rep(i,1,n) b[i]=-1;
	rep(i,1,n)
	{
		cin>>a;
		if(o) continue;
		if(a!=-1)
		{
			if(dg(ls,a,s,i-s)) o=1;
			s=0,ls=a,b[i]=a;
		}
		else s++;
	}
	if(o) {cout<<-1<<endl;return;}
	b[0]=1;
	rep(i,n-s+1,n)
	{
		if(b[i-1]*2<1e9) b[i]=b[i-1]*2;
		else b[i]=b[i-1]/2;
	}
	rep(i,1,n) cout<<b[i]<<" ";
	cout<<endl;
}
int main() 
{
	int T=1;
	cin>>T;
	while(T--) _main();
	return 0;
}
```

---

## 作者：Day_Tao (赞：0)

### 题目大意

给定一个长度为 $n$ 的数组 $a$，让你构造一个数组 $b$，满足对于 $a_i\neq -1$，$b_i =a_i$，且 $\forall 1\le i< n,b_i=\lfloor\frac{b_{i+1}}{2}\rfloor$ 或 $b_{i+1}=\lfloor\frac{b_i}{2}\rfloor$，$1\le b_i\le 10^9$。

### Sol

首先我们考虑全为 $-1$。那么可以输出循环输出 $1$ 和 $2$。

接着考虑一般情况。对于最前面一段的 $-1$ 与最后面一段的 $-1$ 是可以直接处理的，直接拿第一个和最后一个非 $-1$ 的数进行更新。然后是中间部分。容易发现这一部分可以拆分成若干个中间全为 $-1$，两端为非 $-1$ 数的区间，而这些区间都是互不干扰的。因为对于一个 $-1$ 只能由相邻的两个数更新，而原先就是非 $-1$ 的数已经确定，所以一个区间内更新的情况是不会影响另一个区间的。

现在我们考虑每一个区间内部的更新。设最左边的数为 $l$，最右边的数为 $r$。首先我们考虑数组 $b$ 的性质。其实对于 $x\times 2$，$\lfloor\frac{x}{2}\rfloor$，我们都可以看做是在二进制下右移一或者左移一。对于这个性质其实官方题解中有个很形象的解释：在一棵满二叉树上，按照深度一层层标号，一次操作其实就是走一条边。这其实也就是满二叉树的性质。所以问题其实就可以转化为，在这棵二叉树上从 $l$ 点走到 $r$ 点的次数能不能满足这段区间的长度，放在二进制上就是经过若干次对 $l$ 或 $r$ 进行左移或右移操作，使得 $l=r$。要达成这个目的，所需花的最少次数就是 $l$ 到 $\operatorname{LCA}(l,r)$，再到 $r$ 的路径长度，或者说是在二进制下对 $l$ 或 $r$ 右移若干次，使得 $l=r$。若区间长度小于所需操作的最小次数，那么就不合法；若区间长度大于所需操作次数，就可以选择在这棵二叉树上在两个节点之间反复移动来消耗，或者说是对于 $l$ 或 $r$ 反复进行先左移再右移操作。而每这样一次操作的贡献是 $2$，所以要使得这个区间长度 $-$ 变成目标状态所需步数 $\bmod\ 2 = 0$。若不满足则也不合法，满足则进行更新。

更多的细节实现我就放在代码的注释中啦。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e5 + 1;
int a[MAX], n, cnt, l, r, T, ed;
bool flag;
inline void solve()
{
    scanf("%d",&n);
    for (register int i = 1; i <= n; ++i)
        scanf("%d",&a[i]), ed = (a[i] != -1) ? i : ed;
    ++ed;            // ed 不需要初始化，因为后面会对全为 -1 的情况先进行处理，而有了非 -1 的数则可以覆盖 ed
    l = 1, flag = 0; // flag 判断是否是第一个非 -1 的数字，l 记录上一个非 -1 数字的位置
    for (register int i = 1; i <= n; ++i)
        if (a[i] != -1)
        {
            r = i;
            if (!flag) // 对于第一个非 -1 的数字，把前面的数字都更新掉
            {
                for (register int j = i - 1; j >= 1; j--) // 因为要求最终数组的每个值的大小在 1 和 1e9 之间，所以先考虑变成 1，再在 1 2 之间反复横跳
                    a[j] = (a[j + 1] == 1) ? a[j + 1] * 2 : a[j + 1] / 2;
                flag = 1;
                l = i;
                continue;
            }
            if (l + 1 == r) // 如果相邻两个数都是非 -1 的情况
            {
                if (a[l] / 2 == a[r] || a[r] / 2 == a[l])
                {
                    l = i;
                    continue;
                }
                else
                {
                    puts("-1");
                    return;
                }
            }
            int x = a[l], y = a[r]; // 对于一般情况
            bool f = 0;             // f 判断是否合法
            while (l + 1 < r)
            {
                int xx = log2(x), yy = log2(y); // 求出两个数二进制长度
                if (xx > yy)                    // 对于两个数长度不相等进行处理
                    x >>= 1, a[++l] = x;
                else if (xx < yy)
                    y >>= 1, a[--r] = y;
                else if (xx == yy) // 长度相等
                {
                    if (x != y) // 两数不相等
                    {
                        x >>= 1, y >>= 1, a[++l] = x, a[--r] = y;                                     // 同时右移
                        if (l + 1 == r && (a[l] / 2 == a[r] || a[r] / 2 == a[l]) || l == r && x == y) // 合法退出
                        {
                            f = 1;
                            break;
                        }
                    }
                    else // 两数相等相等
                    {
                        if ((r - l) % 2 == 0) // 合法进行更新
                        {
                            f = 1;
                            bool p = 0;
                            for (register int j = l + 1; j < r; ++j) // 不断在 * 2 与 / 2 之间横跳
                                a[j] = p ? a[j - 1] / 2 : a[j - 1] * 2, p = !p;
                        }
                        else//不合法退出
                        {
                            puts("-1");
                            return;
                        }
                        break;
                    }
                }
                if (l + 1 == r && (a[l] / 2 == a[r] || a[r] / 2 == a[l])) // 合法退出
                {
                    f = 1;
                    break;
                }
            }
            l = i;
            if (!f) // 不合法
            {
                puts("-1");
                return;
            }
        }
    if (!flag) // 全是 -1 的情况
    {
        for (register int i = 1; i <= n; ++i)
            printf("%d ", (i % 2) ? 1 : 2);
        puts("");
        return;
    }
    for (register int i = ed; i <= n; ++i) // 从最后一个非 -1 的数开始更新
        a[i] = (a[i - 1] == 1) ? a[i - 1] * 2 : a[i - 1] / 2;
    for (register int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
    puts("");
    return;
}
signed main()
{
    scanf("%d",&T);
    while (T--)
        solve();
    system("pause");
    return 0;
}
```

---
### END

---

## 作者：sbno333 (赞：0)

乍一看感觉很难，但是仔细一想发现很简单。

由于是除以 $2$ 下取整，我们不妨按照 $2$ 进制去想，发现相邻两位的极长公共前缀为她们中长度的最小值。

我们考虑两个隔着千山万水的数，每一次赋值 $-1$ 都必须相对于上一个 01 串（数的二进制形式）少一位或多一位（这一位任意），我们可以通过这个性质来把一个数变成另一个数。

怎么变呢？我们考虑用最少的次数来变（假设中间隔的 $-1$ 极少），我们每次删除的是最低位，所以如果少动，就是高位不动，低位删了在加。

考虑不动的高位的最低临界值。

发现就是最长公共前缀。

接着删了再加，至少需要两个串长度分别减去最长公共前缀的的长度的和（特别的，如果最长公共前缀长度为 $0$，报告无解（要求构造正数））。

但是还有一些 $-1$ 没用怎么办呢？我们发现加一次就要删一次，两次操作，所以如果超了，就看看超的是不是偶数个。

对于两边不需要转化的，乱搞就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s[200009];
int f[200009];
int a[200009];
int lcp(string a,string b){
	for(int i=0;i<min(a.size(),b.size());i++){
		if(a[i]!=b[i]){
			return i;
		}
	}
	return min(a.size(),b.size());
}
void _main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		s[i]="";
		int x;
		cin>>x;
		a[i]=x;
		if(x==-1){
			s[i]="-";
		}else{
			while(x){
				s[i]=char((x&1)+'0')+s[i];
				x>>=1;
			}
		}
		if(s[i-1]!="-"){
			f[i]=i-1;
		}else{
			f[i]=f[i-1];
		}
	}
	int t;
	t=n;
	if(s[t]=="-"){
		t=f[t];
	}
	while(f[t]){
		int z;
		z=f[t];
		int c;
		c=lcp(s[z],s[t]);
		if((t-z)-(int)(s[t].size()-c+s[z].size()-c)>=0&&((t-z)-(int)(s[t].size()-c+s[z].size()-c))%2==0){
			int ii;
			ii=t-1;
			for(int i=t-1;s[t].size()+i-t>=c;i--,ii=i){
				a[i]=a[i+1]/2;
			}
			int jj;
			jj=z+1;
			for(int i=z+1;s[z].size()+z-i>=c;i++,jj=i){
				a[i]=a[i-1]/2;
			}
			for(int i=jj;i<=ii;i++){
				if(i==jj)
				a[i]=a[i-1]*2;
				else
				a[i]=a[i-2];
			}
			t=z;
		}else{
			cout<<-1<<endl;
			return;
		}
	}
	int ss;
	ss=0;
	for(int i=n;i>=1;i--){
		if(a[i]!=-1){
			ss=i;
		}
	}
	for(int i=ss-1;i>=1;i--){
		if(i==ss-1)
		a[i]=a[i+1]*2;
		else
		a[i]=a[i+2];
	}
	ss=n+1;
	for(int i=1;i<=n;i++){
		if(a[i]!=-1){
			ss=i;
		}
	}
	for(int i=ss+1;i<=n;i++){
		if(i==ss+1)
		a[i]=a[i-1]*2;
		else
		a[i]=a[i-2];
	}
	if(a[1]==-1){
		for(int i=1;i<=n;i++){
			a[i]=(1<<(i&1));
		}
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
这场原本是上分场的，被拉去开家长会了（为什么学生要在场啊），掉分了，这里的思路是我场上口胡的。

好像又做麻烦了，但是挺好想的。
## 思路分析
首先如果这个数列全是 $-1$ 的话，直接 $1,2,1,2$ 这样的填下去即可，先判掉。

然后考虑有数的情况。

假设 $a_i\not=-1$ 的位置 $i$ 有 $k$ 个。

则若我们以这些点为断点，能把原数列划分为 $k+1$ 段（设长度为 $0$ 的段也算一段）。

对于这个 $k+1$ 段，我们考虑先把首尾只有一边封闭的类似于全是 $-1$ 那样填掉。

接着考虑中间被夹住 $k-1$ 段。

分类讨论下：
1. 这段长度为 $0$，直接跳过。
2. 这段长度不为 $0$，考虑处理。

观察我们的操作，其实就是二进制加/减最后一位。

贪心的想，因为我们有方法可以填多余的空位。

那么我们只要找出最小需要的空位数即可。

具体的，就是对于已经固定的左右端点 $l,r$，找到最小的操作次数使得 $a_l=a_r$。

因为操作一次就是改变一位，所以操作次数最少，也就是保留位数最多。

把 $a_l,a_r$ 拆成二进制，从高到低匹配，直到匹配不上。

比如 $a_l=13,a_r=30$。

则二进制为 $a_l=1101_{(2)},a_r=11110_{(2)}$。

保留的位置即为开头的 $11_{(2)}$。

接着开始填，从 $l$ 开始向右扩展，把多余的位数砍掉。

而 $r$ 也同理向左扩展。

这样就得到了一个缩小过的区间 $[l',r']$，且满足 $a_{l'}=a_{r'}$。

那剩下中间的位数怎么填呢？

反复浪费即可，先乘 $2$ 再除以 $2$ 一路填过来即可。

考虑下为什么这样是对的。

不难发现无解的情况可以分为两种：
1. 光是砍掉 $a_l,a_r$ 需要的操作数就大于有的数量了。
2. 缩小区间 $[l',r']$ 的长度不为奇数。

对于 $1$，我们已经保证所要操作数是最少的了。

对于 $2$，如果我要改变 $[l',r']$ 的长度，就是各再操作一次，把 $a_{l'},a_{r'}$ 同时加一位或者减一位。

这样的话改变操作数是偶数的，并不影响 $[l',r']$ 的奇偶性。

最后讲下怎么判断无解。

既然都构造出原数列了，直接放上去跑一遍看看是不是假的就行。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int T,n,a[N],b[N],d[N],e[N];vector<int>c;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void wtf()
{
    for(int i=1;i<=n;i++)
        if(i&1) print(1),put(' ');
        else print(2),put(' ');
}
signed main()
{
    T=read();
    while(T--)
    {
        n=read();for(int i=1;i<=n;i++) a[i]=read(),b[i]=0;c.clear();
        for(int i=1;i<=n;i++) if(a[i]!=-1) c.push_back(i),b[i]=a[i];
        if(c.empty()){wtf();put('\n');continue;}
        for(int i=c[0]-1;i>=1;i--) if(b[i+1]>1) b[i]=b[i+1]/2;else b[i]=b[i+1]*2;
        for(int i=c.back()+1;i<=n;i++) if(b[i-1]>1) b[i]=b[i-1]/2;else b[i]=b[i-1]*2;
        for(int i=1;i<c.size();i++)
        {
            int l=c[i-1],r=c[i],tot=0,cnt=0,x=a[l],y=a[r];
            if(r-l==1) continue;
            while(x) d[++tot]=x&1,x>>=1;
            while(y) e[++cnt]=y&1,y>>=1;
            int j=0;for(;j<min(tot,cnt)&&d[tot-j]==e[cnt-j];j++);
            for(int k=1;k<=tot-j&&l+k<=n;k++) b[l+k]=b[l+k-1]/2;
            for(int k=1;k<=cnt-j&&r-k>0;k++) b[r-k]=b[r-k+1]/2;
            for(int k=l+tot-j+1;k<r-cnt+j;k++)
            {
                int op=(k-(l+tot-j))&1;
                if(op) b[k]=b[k-1]*2;else b[k]=b[k-1]/2;
            }
        }if(!b[n]||a[n]!=b[n]&&a[n]!=-1){put("-1\n");goto play;}
        for(int i=1;i<n;i++) if(b[i]!=b[i+1]/2&&b[i]/2!=b[i+1]||!b[i]||a[i]!=b[i]&&a[i]!=-1){put("-1\n");goto play;}
        for(int k=1;k<=n;k++) print(b[k]),put(' ');put('\n');play:;
    }
    genshin:;flush();return 0;
}
```

---

