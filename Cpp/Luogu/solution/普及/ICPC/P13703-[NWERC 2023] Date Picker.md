# [NWERC 2023] Date Picker

## 题目描述

NWERC 即将到来，你的日程表已经被各种会议填满了。
你的一个队友想要安排一次会议，并征求你的意见。
不过，他并没有直接询问你的具体日程，而是让你分别填写两个投票表：
一个用来表示你哪几天有空，另一个用来表示你哪几个小时有空！

![](https://cdn.luogu.com.cn/upload/image_hosting/6a7bghv1.png)
:::align{center}
一个已填好的日程表。
:::

作为一名计算机科学家，你只会在整点安排会议，并且每次会议持续的时间都是整数小时。
因此，你的日程表可以建模为一个 $7$ 行 $24$ 列的矩阵（行表示天，列表示小时）。
矩阵中的每个单元格要么是 '$\texttt{.}$'，要么是 '$\texttt{x}$'，
分别表示你在那一天的那一小时有空或已经有会议。

你需要在第一个投票表中至少选择 $d$ 天，在第二个投票表中至少选择 $h$ 个小时，
我们假设会议会以等概率安排在你所选择的所有天和小时的组合中的任意一个。
如果你最优地填写投票表，问你能参加会议的概率是多少？

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
xxxxxx..xx..xxxxxxxxxxxx
xxxxxxxxxxxxx....xxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxx
xxxxxx..xx..xxxxxxxxxxxx
xxxxxxxxxxxxx...x..xxxxx
xxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxx
2 5```

### 输出

```
0.8
```

## 样例 #2

### 输入

```
xxxxxxxxx.....x...xxxxxx
xxxxxxxx..x...x...xxxxxx
xxxxxxxx......x...x.xxxx
xxxxxxxx...xxxxxxxxxxxxx
xxxxxxxx...xxxxxxxxxxxxx
xxxxxxxx...xxxxxxxx.xxxx
......xxxxxxxxxxxxxxxxxx
3 8```

### 输出

```
0.958333333333333```

# 题解

## 作者：__CuSO4__ (赞：2)

### 题意简述

给你一个 $7\times24$ 的 $01$ 矩阵，从中选取 $d$ 行 $h$ 列，求行与列交叉点中 $0$ 的个数占总交叉点的最大比例。

### 思路

这题是搜索和贪心的结合。

可以考虑先确定行的方案，对于列的方案，有以下贪心策略：

- 对于每一列，计算在选出的 $d$ 行中对应位置的 $0$ 个数。

- 空闲个数最多往少依次选出 $h$ 的一列，就能保证在当前行的方案下最优。

所以，先暴搜确定行的方案，再贪心确定列的方案，取最大值即为答案（~~其实思路很好想到~~。

### 代码
``` cpp
#include <iostream>
#include <algorithm> 
using namespace std;

//a：是否空闲    b：日期是否被选择   c：对于每个小时，空闲的日期数
int a[10][30], d, h, maxn, b[10], c[30];
char ch;

void dfs(int x, int cnt)
{
    if (x > 7)
    {
    	if (cnt == d)
    	{
	        for (int i = 1; i <= 24; i++)
	        {
	            c[i] = 0;
	            for (int j = 1; j <= 7; j++)
	                if (b[j] && a[j][i]) c[i]++;
	        }
            //贪心，先选大的
	        sort(c+1, c+1+24);
	        int sum = 0;
	        for (int i = 24; i >= 24-h+1; i--) sum += c[i];
	        maxn = max(maxn, sum);
		}
        return;
    }
    b[x] = 1, dfs(x+1, cnt+1);
    b[x] = 0, dfs(x+1, cnt);
}

int main()
{
    for (int i = 1; i <= 7; i++)
        for (int j = 1; j <= 24; j++)
            cin >> ch, a[i][j] = ch=='.'?1:0;
    cin >> d >> h;
    dfs(1, 0);
    printf("%.10f", 1.0 * maxn / d / h);
    return 0;
}
```

---

## 作者：ZBXAPCY (赞：1)

**前言**：建议将文字与代码片段结合理解。

**题目大意**：给定一个 7 行 24 列的矩阵（表示 7 天的 24 小时是否空闲），$\texttt{.}$ 表示空闲，$\texttt{x}$ 表示忙碌。需要选择至少 $d$ 天和至少 $h$ 小时，使得这些天和小时的交叉点中空闲的比例（题目中说的概率也行，两者本质是同一种东西）最大，求这个最大比例。

我就先讲讲我的做题过程与思路：我看到题目首先想到了贪心，于是立刻敲起了代码，但敲了半个小时后连样例都没过，便决定放弃贪心。转念一想此题的数据范围那么小，干脆用暴力的方法，于是就开始写枚举子集的代码，就是先输入整个矩阵、至少选择的天数 $d$、小时数 $h$，然后枚举天的子集（枚举选哪一行），只要满足它的子集元素数量与 $d$ 相等（刚好选了 $d$ 行），就计算出在选择小时的最优情况下的比例（选择列），并更新最大值答案。

以下可能出现的问题：

枚举子集是什么？  
是请自行搜索，顺便补充一下位运算知识。

“计算出在选择小时的最优情况下的比例”这一句说的太含糊了，没看懂。  
不理解确实很正常，这一部分涉及到一些贪心，是问题的核心，在代码中会详细解释。

这样实现的时间复杂是多少？会不会超时？  
时间复杂度为 $\mathcal{O}(2^7 \cdot dh)$，不会超时。因为我们需要枚举子集并计算出每个天数子集在选择小时方面的选择上的最优解（会在代码中体现），附加一句，实际上真正的时间复杂度要小很多。

什么？您没看懂？别划走，下面还有高清注释代码，可结合代码理解，有可能就懂了。

代码：

```cpp
//最近在改善码风。
#include <bits/stdc++.h>//从小用到大的万能头 
using namespace std;
char a[10][30];
//a数组用于存储矩阵 ，a[i][j]表示第i天第j小时是否空闲 
int d, h, hh[30];
/*d、h和题目所说一样，hh数组作用：hh[i]表示在选择的日期固定的情况下第i个小时的空闲时间*/
long double ans;//ans用于记录答案 
bool pd (int x) {
	int sum = 0;
	while (x) {
		sum += x & 1;
		x >>= 1;
	}
	return sum == d;
}//用于判断枚举的子集元素的数量是否为d 
bool cmp (int x, int y) {
	return x > y;//排序标准：先大后小 
}
int main () {
	for (int i = 1; i <= 7; i++) 
		for (int j = 1; j <= 24; j++)
			cin >> a[i][j];
	cin >> d >> h;//输入 
	for (int i = 1; i < (1 << 7); i++) {
	//枚举天数的子集 
		if (!pd (i))continue;
		/* 
		显然跳过的只有两种情况:
		1.选择天数<d
		这种情况根本就不满足题目要求，显然要跳过
		2.选择天数>d
		虽然题目同意这种情况，但这样不可能是最优解，
		因为如果我们有选择了大于d天，
		显然我们可以只保留其中空闲小时最大的d天，
		而被我们抛弃的那些天本身比例不会大于1，
		所以这样的概率至少不会小于选择了大于d天 
		*/ 
		int x = i, l = 0;
		long double fr = 0;//fr用于记录如果按这种天数方案空闲的纵横交叉点最多是多少 
		memset (hh, 0, sizeof (hh));
		//清空hh数组
		for (int j = 7; x; j--, x >>= 1) {
		/*想象把x转化为二进制（前面不足补0） ，例如5=0000101
		我们依次从后面取出它的每一位，
		如果是1表示我们选了这一天
		反之表示我们没选 
		*/
			if (! (x & 1)) continue;//如果我们没选就跳过 
			for (int k = 1; k <= 24; k++) //选了就判断这一天每小时是否空闲 
				if (a[j][k] == '.') //若空闲则这一小时的空闲时间加1 
					hh[k]++;
		}
		sort (hh + 1, hh + 24 + 1, cmp);
		for (int j = 1; j <= h; j++) //因为题目至少让我们选择h小时，所以选空闲天数最多的h小时，为何只选h小时的贪心策略和i一样 
			fr += hh[j];
		ans = max (ans, fr / (long double) (d * h) );//计算比例公式为：空闲交叉点/总交叉点，因为我们已经贪心的选了最少的时间，所以总交叉点就是d*h 
		//取比例的最大值 
	}
	printf ("%.7Lf\n", ans);//输出。题目有精度要求 
    return 0;
}
```
超清无注释版代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[10][30];
int d, h, hh[30];
long double ans;
bool pd (int x) {
	int sum = 0;
	while (x) {
		sum += x & 1;
		x >>= 1;
	}
	return sum == d;
}
bool cmp (int x, int y) {
	return x > y;
}
int main () {
	for (int i = 1; i <= 7; i++) 
		for (int j = 1; j <= 24; j++)
			cin >> a[i][j];
	cin >> d >> h;
	for (int i = 1; i < (1 << 7); i++) {
		if (!pd (i))continue;
		int x = i, l = 0;
		long double fr = 0;
		memset (hh, 0, sizeof (hh));
		for (int j = 7; x; j--, x >>= 1) {
			if (! (x & 1)) continue;
			for (int k = 1; k <= 24; k++) 
				if (a[j][k] == '.') 
					hh[k]++;
		}
		sort (hh + 1, hh + 24 + 1, cmp);
		for (int j = 1; j <= h; j++) 
			fr += hh[j];
		ans = max (ans, fr / (long double) (d * h) );
	}
	printf ("%.7Lf\n", ans);
    return 0;
}
```

文章结尾说一下，建议大家掌握好枚举子集，本文章仅仅说了它的冰山一角，它常常用于优化 DFS，状压 DP 也是它的重要应用，最重要的是它的代码量还比 DFS 小，此外，它还能二次优化，请读者自行探索。

求赞求通过。

---

## 作者：Doraeman (赞：1)

我看到英文题意时，~~实在是不理解~~什么叫“hour/day combinations”。  
~~当然不是因为我英语不好。~~

## 题意
已知一个日期表格，画出了一周 $7$ 天每天 $24$ 小时。

在 $7$ 天中任选至少 $d$ 天，在 $24$ 小时中任选至少 $h$ 小时。设选择 $x$ 天，$y$ 小时。  
**注意：此处“天”两两不同，“小时”也两两不同。**

接着，在 $x\times y$ 种 “天与小时的组合（hour/day combinations）”中，等概率选择 $1$ 种，求选中的格子在日期表格中为 ```.``` 的概率。

### 样例分析
为了方便理解题意，现在给出自测样例 #2 的分析。  
~~已经看懂“hour/day combinations”的大佬可以直接跳到下一部分。~~

在这个样例中，我们选择第 $1,2,3$ 天，并选择第 $10,11,12,13,14,16,17,18$ 小时。  

|days/hours|$10$ |$11$ |$12$ |$13$ |$14$ |$16$ |$17$ |$18$ |
|:--:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$   | $\bullet$  | $\bullet$  | $\bullet$  | $\bullet$  | $\bullet$  | $\bullet$  | $\bullet$  | $\bullet$  |
|$2$   | $\bullet$  | $\times$  |  $\bullet$ | $\bullet$  | $\bullet$  | $\bullet$  |  $\bullet$ | $\bullet$  |
|$3$   | $\bullet$  | $\bullet$  |  $\bullet$ | $\bullet$  | $\bullet$  | $\bullet$  | $\bullet$  | $\bullet$  |

在以上表格中列举出的全部 $24$ 种“小时 / 天”的组合中，只有“第 $2$ 天的第 $12$ 小时”这个组合在日期表格上对应着 ```x```，其余的组合都对应着 ```.```。  
所以答案是 $\frac{23}{24}=0.958\dot3\approx0.985333$，与样例输出相符。

## 分析
显然，这道题数据量非常小。因为 $d,h$ 满足 $d\le7,\ h\le24$。  
因此，可以**暴力（~~非常暴力~~）搜索**完成本题。  
然而，想要获得一个**靠谱的解题思路**却比较困难。

## 思路
思路中涉及到[**排列组合**](https://oi-wiki.org/math/combinatorics/combination/)知识中的[**组合数**](https://oi-wiki.org/math/combinatorics/combination/#%E7%BB%84%E5%90%88%E6%95%B0)。

首先，我们要确定：总共挑选 $x$ 天（$x\ge d$）。 

### 组合数求 days 可能性
使用组合数求 $\operatorname{C}_7^x$ 的值，并列出所有 $1\sim7$ 中选择 $x$ 个数的情况。  
这部分的内容与题目 [P1061 [NOIP2006 普及组] Jam 的计数法](https://www.luogu.com.cn/problem/P1061) 的内容非常相似，写法可以参考当时我那篇~~格式问题审核不通过的~~[题解](https://www.luogu.com.cn/article/nxzxot9d)。

核心思路就是：

1. 如果第 $n$ 位的字母是最大序号，应当向前找到第 $1$ 个不相邻的字母，并将其进一位，紧随其后填上每个数。
2. 如果第 $n$ 位的字母不是最大序号，直接向右移动一位。

#### 组合求 $\operatorname{C}_7^x$ 全部情况的代码
```cpp
void Cnext(int n){
	if(a[n] < 7){ // 不到临界值 
		a[n]++;
		return;
	}

    // 到临界值了, 向上一位"进位" 
	for(int i=n; i>1; i--)
		if(a[i] != a[i-1] + 1){
			a[i-1]++;
			for(int j=i; j<=n; j++)
				a[j] = a[i-1] + (j-i+1);
			return;
		}
}
```

### 根据已知的 days 求最佳的 hours
这部分仍然以自测样例 #2 作为例子。  
例如：我们选取了 ```1,2,3``` 这 $3$ 天。

我们可以根据日期表格，分别求出第 $1,2,3$ 天的 $1\sim24$ 小时，每个小时所包含的 ```.```。

```
xxxxxxxxx.....x...xxxxxx
xxxxxxxx..x...x...xxxxxx
xxxxxxxx......x...x.xxxx
xxxxxxxx...xxxxxxxxxxxxx
xxxxxxxx...xxxxxxxxxxxxx
xxxxxxxx...xxxxxxxx.xxxx
......xxxxxxxxxxxxxxxxxx
```
在以上这个日期表格中：
- 第 $1,2,3$ 天的第 $9,11$ 小时都包含 $2$ 个 ```.```；
- 第 $1,2,3$ 天的第 $10,12,13,14,16,17,18$ 小时都包含 $3$ 个 ```.```；
- 第 $1,2,3$ 天的第 $20$ 小时包含 $1$ 个 ```.```；
- 第 $1,2,3$ 天的其它的小时不包含任何 ```.```。

求出 $1\sim24$ 这 $24$ 个小时的 ```.``` 的数量之后，对它们进行从大到小排序。  
以上这个样例中，排序后序列为：```3 3 3 3 3 3 3 2 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0```。  
从有序的序列中选择至少 $h$ 个元素求包含 ```.``` 的总数并求和。

最后，题目要求概率的最大值，即以上序列中选择 $y$ 个元素（$y\ge h$）的总和与 $(x\times y)$（小时 / 天的组合） 的**比值的最大值**。  
$x$ 已知，所以可以在单调不减的序列中从前到后循环求当前的元素总和（即包含 ```.``` 的数量）。**如果已选择的元素大于等于 $h$ 就考虑更新概率最大值。**

## 细节
题目使用 SPJ，要求误差不超过 $10^{-6}$，所以输出时保留 $7$ 位小数比较合适。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

bool cal[10][30];
int a[10], b[30], 
    C7[] = {1, 7, 21, 35, 35, 21, 7, 1};
	// C(7,n)有C7[n]种情况
double ans = -1;

// 求C(7,n)的下一种情况 
void Cnext(int n){
	if(a[n] < 7){
		a[n]++;
		return;
	}
	
	for(int i=n; i>1; i--)
		if(a[i] != a[i-1] + 1){
			a[i-1]++;
			for(int j=i; j<=n; j++)
				a[j] = a[i-1] + (j-i+1);
			return;
		}
}

void go(int n, int m){
	// 7天中选择n天, 24小时中选择m小时 
	for(int i=1; i<=n; i++)
		a[i] = i;
	
	for(int _=1; _<=C7[n]; _++){
        memset(b, 0, sizeof(b));
		for(int j=1; j<=24; j++) // 遍历小时 
			for(int i=1; i<=n; i++) // 遍历序列中的所有天 
				b[j] += cal[a[i]][j];
		sort(b + 1, b + 25, greater<int>());
		
		double sum = 0, p = 0, maxi = -1;
		for(int i=1; i<=24; i++){
			sum += b[i], // 元素求和 
			p = sum / (i * n); // 计算概率 
			if(i >= m) // 如果大于等于m, 可以更新概率最大值
				maxi = max(p, maxi);
		}

		ans = max(maxi, ans);
		Cnext(n);
	}
}

int main(){
	for(int i=1; i<=7; i++)
		for(int j=1; j<=24; j++){
			char x; cin >> x;
			cal[i][j] = (x == '.');
		}
    int n, m; cin >> n >> m;
    
    // 分别枚举选择n,n+1,...,7天 
    for(int i=n; i<=7; i++)
    	go(i, m);
    
    // 输出答案 
    printf("%.7lf",ans);
}
```

---

## 作者：lmz105 (赞：0)

### 思路
首先用一个七位二进制数来枚举第一个投票表中选择的情况，$1$ 代表选，当这个二进制数中 $1$ 的数量不少于 $d$ 时，用一个数组记录此情况下每个小时的空闲数量，接着将数组从大到小排序，最后计算选数组前几个（不少于 $h$）时平均空闲比例最大，并记录下这个比例，所有比例的最大值就是答案。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,a[8];
double ans;
int main(){
	for (ll i=0;i<7;i++){
		for (ll u=0;u<24;u++){
			char ch;
			cin >> ch;
			a[i]|=((ch=='.')<<u);
		}
	}
	cin >> n >> m;
	ll maxx=(1<<7)-1;
	for (ll i=0;i<=maxx;i++){
		if (__builtin_popcount(i)>=n){
			ll sum[26]={0};
			for (ll u=0;u<7;u++){
				if ((i>>u)&1){
					for (ll j=0;j<24;j++){
						sum[j]+=((a[u]>>j)&1);
					}
				}
			}
			sort(sum,sum+24,greater<ll>());
			ll s=0;
			for (ll u=0;u<24;u++){
				s+=sum[u];
				if (u+1>=m){
					ans=max(ans,(1.0*s/(u+1)/__builtin_popcount(i)));
				}
			}
		}
	}
	cout << fixed << setprecision(7) << ans;
	return 0;
} 
```

---

