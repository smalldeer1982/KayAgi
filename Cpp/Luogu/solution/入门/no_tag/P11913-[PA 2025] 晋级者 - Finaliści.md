# [PA 2025] 晋级者 / Finaliści

## 题目背景

PA 2025 R1C.

## 题目描述

PA 2025 决赛的晋级规则如下：

- 只有 $20$ 名选手能获得进入决赛的资格：
	- 前 $10$ 名选手根据线上赛的排名决定；
    - 接下来的 $10$ 名选手同样按照线上赛的排名顺序选出，但是排除那些至少参加过两次 PA 决赛的选手。
- 只有波兰公民或在波兰学习、工作或居住的选手才能进入决赛。
- 为选出这 $20$ 名决赛选手，首先会去除无法进入决赛或放弃参赛的选手。接着，根据上述规则，从剩余的选手中选出 $20$ 名决赛选手。

PA 2025 线上赛共有 $n$ 人参赛，其中第 $i$ 个人的排名为 $i$。对于每个人，都知道他是否能够进入决赛，以及他之前参加 PA 决赛的次数。

根据比赛规则，选出 $20$ 名决赛选手。数据保证能够按照上述规则选出 $20$ 人。

## 说明/提示

- $20\le n\le 10^4$；
- $0\le x_i\lt 20$。

## 样例 #1

### 输入

```
35
NIE 0
NIE 0
TAK 3
TAK 0
TAK 7
TAK 5
NIE 0
NIE 0
TAK 7
TAK 1
NIE 0
TAK 8
TAK 1
TAK 3
NIE 0
TAK 2
NIE 0
TAK 1
NIE 4
TAK 2
TAK 2
TAK 1
TAK 1
TAK 0
TAK 0
TAK 0
TAK 0
TAK 0
NIE 0
TAK 1
TAK 2
TAK 0
TAK 0
TAK 0
TAK 0```

### 输出

```
3 4 5 6 9 10 12 13 14 16 18 22 23 24 25 26 27 28 30 32```

# 题解

## 作者：banglee (赞：2)

## P11913 [PA 2025] 晋级者 / Finaliści 题解
[洛谷传送门](https://www.luogu.com.cn/problem/P11913)

## 题目大意
总共 $20$ 个决赛资格，其中前 $10$ 名选手根据线上赛排名决定；接下来的 $10$ 名选手同样按线上赛排名顺序选出，但要排除至少参加过两次 PA 决赛的选手。

只有波兰公民或在波兰学习、工作或居住的选手才能进入决赛，在输入中通过 `TAK` 和 `NIE` 来区分选手是否具备参赛资格。

## 思路
将能进入决赛的选手编号存储在一个数组中。

从存储能进入决赛选手编号的数组中，按顺序选取前 $10$ 名选手，将他们的编号存入另一个数组。

再次遍历存储能进入决赛选手编号的数组，对于每个选手，看他的参加决赛的次数是否小于 $2$。如果小于 $2$ 并且这个选手尚未在答案数组中，就将其加入答案数组，直到答案数组中有 $20$ 名选手。

对答案数组进行排序，然后按顺序输出即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,c,x[10005],e[10005],ans[25];
string s[10005];
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>s[i]>>x[i];
	for (int i=1;i<=n;i++)
		if (s[i]=="TAK") e[++k]=i;
	for (int i=1;i<=k && c<10;i++)
		ans[++c]=e[i];
	for (int i=1;i<=k && c<20;i++) {
		int idx=e[i];
		if (x[idx]<2) {
			bool flag=false;
			for (int j=1;j<=c;j++)
				if (ans[j]==idx) {
					flag=true;
					break;
				}
			if (!flag) ans[++c]=idx;
		}
	}
	sort(ans+1,ans+21);
	for (int i=1;i<=20;i++)
		cout<<ans[i]<<" ";
	return 0;
}
```

---

