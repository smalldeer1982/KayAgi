# Tokitsukaze and Meeting

## 题目描述

#### 【题目翻译】

Tokitsukaze 正在安排一场学生会议。会议厅的座位是一个 $n$ 行 $m$ 列的矩形。

一共有 $(n \times m)$ 个学生参加会议，这些学生被从 $1$ 到 $(n \times m)$ 编号。这 $(n \times m)$ 个学生中有一些学生比较调皮，有些学生比较严肃。

学生将以编号从小到大的顺序进场。每个学生进场后将会坐在第 $1$ 行第 $1$ 列，而原本的学生将会后退一格，即：

- 原本在第 $i$ 行第 $j$ 列的学生（$1 \leq j \leq m-1$），将会坐到第 $i$ 行第 $(j+1)$ 列；
- 原本在第 $i$ 行第 $m$ 列的学生将会坐到第 $(i+1)$ 行第 $1$ 列。

（具体的过程请看原题面里的图片）

如果某一行或某一列有至少一位严肃的学生，那么这一行或这一列就会认为是好的行货好的列。

对于所有的 $1 \leq i \leq (n \cdot m)$，求当第 $i$ 位学生（即编号为 $i$ 的学生）进场后，好的行及好的列的数量的和。

## 说明/提示

- $1 \leq T \leq 1 \times 10^{4}$
- $1 \leq n,m \leq 1 \times 10^{6},1 \leq (n \cdot m) \leq 1 \times 10^{6}$
- $1 \leq \sum (n \cdot m) \leq 1\times 10^{6}$

Translated by @HPXXZYY

## 样例 #1

### 输入

```
3
2 2
1100
4 2
11001101
2 4
11001101```

### 输出

```
2 3 4 3
2 3 4 3 5 4 6 5
2 3 3 3 4 4 4 5```

# 题解

## 作者：郑朝曦zzx (赞：5)

# 一 解题思路
由于 $\sum n \times m \le 10^6$，所以我们不能在每一次有学生进入教室的时候再重新计算，我们应该利用已有的行列信息推算答案。

我们可以把行和列分开考虑：
- 列

不难发现，在同一列的数对 $m$ 的余数是相同的，所以新进入学生也不会影响之前的列的形态，因此列的答案的单调不减的。

我们可以记录下每个列是否出现过严肃的学生，如果没出现过，现在出现了，那么列的答案加一。

- 行

我们发现每 $m$ 个学生进入就会增加一行，而不会改变队列形态（指 $m$ 个人未进入时的队形）。那么我们就可以用 $row_i$ 记录模 $m$ 余数为 $i$ 的学生在每行的第一个时的答案。

用 $lst$ 记录上一个严肃的学生的编号，那么如果 $i - lst \lt m$ 那么新的这一行就存在严肃的学生。

最后答案为行列二者答案的家和。

注意：本题 IO 量较大，如果用 cin 输入，请关闭同步并加上加速语句，否则第四个测试点会 TLE。

# 二 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
void fastInp()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int row[1000010], col[1000010];
int main()
{
	fastInp();
	int t; cin >> t;
	while (t--)
	{
		int n, m, colcnt = 0, lst = - 1e9;
		cin >> n >> m;
		for (int i = 0; i < n * m; ++i)
		{
			char c; cin >> c;
			if (c == '1')
			{
				lst = i;
				if (col[i % m] == 0)
				{
					col[i % m] = 1;
					++colcnt;	
				}
			}
			if (i - lst < m) row[i % m]++;
			cout << row[i % m] + colcnt << " ";
		}
		cout << endl;
		for (int i = 0; i < max(n, m); ++i)
			col[i] = row[i] = 0;
	}
    return 0;
}
```


---

## 作者：intel_core (赞：2)

如果直接暴力，明显是 $O(n^2m^2)$ 的复杂度。

手玩一下这个有人进教室的过程，发现无论怎么加人，如果 $x,y$ 在一列那么随便怎么搞还是在一列。

接着观察行的情况，不难发现 $t+m$ 时刻相比于 $t$ 时刻多了一行，其它行不变。

把行的贡献和列的贡献拆开统计，最后加在一起。

对于第 $i$ 个人，第 $j$ 个人和他在同一列当且仅当 $m|i-j$。可以对于每个 $i<m$，找到最小的 $j$ 使得 $m|j-i$ 且第 $j$ 个人是老实的，给 $\ge j$ 的所有答案 $+1$。

考虑计算行的贡献，按照 $i \bmod m$ 的余数分类，对于 $i \le m$ 的情况暴力计算。对于 $i>m$ 的情况，从 $i-m$ 时递推来，再加上 $i-m+1,i-m+2,\cdots,i$ 里有没有老实的人即可。

复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e6+10;
int n,m,a[NR],sum[NR],s1[NR],s2[NR];

void solve(){
	cin>>n>>m;
	for(int i=1;i<=n*m;i++)s1[i]=s2[i]=sum[i]=0;
	for(int i=1;i<=n*m;i++)scanf(" %1d",&a[i]),sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=m;i++)
		for(int j=i;j<=n*m;j+=m)
			if(a[j]){
				s1[j]++;
				break;
			}
	for(int i=1;i<=n*m;i++)
		if(sum[i]>sum[max(i-m,0)])s2[i]++;
	for(int i=1;i<=n*m;i++){
		s1[i]+=s1[i-1];
		if(i>m)s2[i]+=s2[i-m];
		printf("%d ",s1[i]+s2[i]);
	}
	puts("");
}

int main(){
	int T;cin>>T;
	while(T--)solve();
	return 0;	
}
```

---

## 作者：NKL丶 (赞：2)

## Description

给出一个 $n$ 行 $m$ 列的矩阵，最初全部为空。现给出一个 01 序列 $S$，逐位将序列内的数放至矩阵的 $(1,1)$ 位置，并将矩阵内所有其余数后移一位（特别的，每一行第 $m$ 列的数移至下一行的第 1 列），问加入 $S$ 的每一位时，矩阵中“好的行和列”的数量为多少。

我们定义一行或一列是好的，当且仅当这一行/列有至少一个数为 1。（$1 \leq \sum n \times m \leq 10^6$）

## Solution

我们将行和列分别考虑。

对于列来说，我们发现编号对 $m$ 取模相同的数在加入数字时永远在同一列，所以开一个桶记录每一列是否已经有 1 出现即可。

但是行的计算与列不同，因为这里的计算是逐行转移，而列只需考虑与 $m$ 取模的结果即可。

通过观察，发现对于每个元素 $S_i$，其在矩阵中某行的可能的状态只有 $m$ 种（即 $S_i$ 在第 1 列、第 2 列…第 $m$ 列），因此考虑类似队列的区间移动，从头开始对 $S$ 进行扫描，每次将第 $i$ 位加入，将第 $i-m$ 位弹出，记录此时区间内 1 的数目，再考虑对答案的贡献，时间复杂度为扫描每一位的 $O(n \times m)$。

## [code](https://www.luogu.com.cn/paste/9l5795tg)

---

