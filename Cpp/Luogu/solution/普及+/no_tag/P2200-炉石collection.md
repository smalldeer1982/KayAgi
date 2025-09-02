# 炉石collection

## 题目描述

小 Z 最近沉迷于一个叫做炉石 collection 的游戏。在游戏中，你需要使用排在 $N \times N$ 的矩阵内的卡牌来击败你的敌人。

在这个游戏中，排兵布阵是游戏的一个重要内容，例如“日怒保卫者”和“上古看守者”放在一起可以起到更好的效果。为了游戏的平衡性，同样种类的卡牌最多只能出战 $2$ 张。

在一次激烈的战斗之后，小 Z 想要重新编排他的队伍。在游戏中，小 Z 可以支付 $A$ 枚金币让你任意横向交换卡牌，支付 $B$ 枚金币让你任意纵向交换卡牌。

你只需要支付一次金币就可以进行某种类型的交换任意次，直到你停下并进行另一种类型的交换，此时需要支付另一种类型交换的费用。例如，“横向交换-横向交换-纵向交换-纵向交换-纵向交换-横向交换-纵向交换”总共要支付 $2A + 2B$ 枚金币。

小 Z 想要知道，他最少要支付多少金币把他目前的布置变换成他想要的布置。

## 说明/提示

对于 $68\%$ 的数据，答案最多只需要支付 $1$ 次费用。

对于 $86\%$ 的数据，答案最多只需要支付 $2$ 次费用。

对于 $100\%$ 的数据，$1 \leq n \leq 300,1 \leq A,B \leq 1000000,1 \leq$ 卡牌类型的标号 $\leq 100000$。

## 样例 #1

### 输入

```
3 16 9
2 5 6
1 1 3
7 8 3
2 5 1
3 3 6
7 8 1```

### 输出

```
34```

## 样例 #2

### 输入

```
2 193 43
1 2
2 1
1 2
2 3```

### 输出

```
Fail```

## 样例 #3

### 输入

```
3 10 20
1 2 3
4 5 4
3 2 1
2 1 2
1 5 3
4 3 4```

### 输出

```
30```

# 题解

## 作者：steambird (赞：14)

## 思路
本题涉及到的操作为”横向交换“与”纵向交换“。

实际上，”横向交换“即改变某张卡牌的列号，而”纵向交换“即改变某张卡牌的行号。

容易想到，既然连续进行同种交换不产生额外花费，我们应当试着先统一改变列号，再统一改变行号（或者反过来）。

可是，从第一个样例中我们就可以发现，这样的操作中可能会有冲突。例如，两张卡牌原先所处的行相同而目标列相同，这会使得按列归位时两张卡牌无法同时被移动到目标列。当两张卡牌原先所处的列相同而目标行相同时，也会产生类似的冲突。

通过手动模拟，可以发现，在出现冲突时，我们可以先正常地横向与纵向移动其它卡牌使其归位，再用一次额外的横向或纵向（注意，两种操作中有一种即可，另一种操作可以在之前提前进行）使冲突的卡牌归位。

还需要注意的是，我们需要尽可能减少冲突从而使花费尽可能小。这意味着当同种类型的卡牌有两张出现时，除非两张都会与某张卡牌产生冲突，否则我们就不将其视为冲突；另外，如果只有一个方向的冲突（如只有横向或纵向交换导致冲突），我们完全可以先进行另一个方向的交换，此时也不视为冲突。

最终的代码模拟上述过程即可。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define CARDID 100003
#define N 303
int cxpos[CARDID],cypos[CARDID],cx2pos[CARDID],cy2pos[CARDID];	// 注意：x 纵向，y 横向。
int oxpos[CARDID],oypos[CARDID],ox2pos[CARDID],oy2pos[CARDID],targets[N][N];	// 卡牌的原先位置
int exist[CARDID] = {}, rexist[CARDID] = {};	// 有几张卡牌
bool counter[CARDID] = {};
bool failure = false;
bool cpx = false, cpy = false;		// 是否有冲突
int xmove = 0, ymove = 0;			// 是否需要进行该方向的交换

inline int mini(int x, int y) {
	return x<y?x:y;
}

inline bool judge(int x1, int y1, int x2, int y2) {
	int &type1 = targets[x1][y1], &type2 = targets[x2][y2];
	bool f1, f2;
	switch (rexist[type1]) {
		case 1:
			switch (rexist[type2]) {
				case 1:
					return (x1 == x2) ? (cypos[type1] == cypos[type2]) : (cxpos[type1] == cxpos[type2]);
					break;
				case 2:
					return (x1 == x2) ? (cypos[type1] == cypos[type2] && cypos[type1] == cy2pos[type2]
						&& oxpos[type1] == oxpos[type2] && oxpos[type1] == ox2pos[type2]) 
						: (cxpos[type1] == cxpos[type2] && cxpos[type1] == cx2pos[type2]
						&& oypos[type1] == oypos[type2] && oypos[type1] == oy2pos[type2]);
					break;
			}
			break;
		case 2:
			switch (rexist[type2]) {
				case 1:
					return (x1 == x2) ? (cypos[type1] == cypos[type2] && cy2pos[type1] == cypos[type2]
						&& oxpos[type1] == oxpos[type2] && ox2pos[type1] == oxpos[type2]) 
						: (cxpos[type1] == cxpos[type2] && cx2pos[type1] == cxpos[type2]
						&& oypos[type1] == oypos[type2] && oy2pos[type1] == oypos[type2]);
					break;
				case 2:
					f1 = (x1 == x2) ? (cypos[type1] == cypos[type2] && cy2pos[type1] == cypos[type2]
						&& oxpos[type1] == oxpos[type2] && ox2pos[type1] == oxpos[type2]) 
						: (cxpos[type1] == cxpos[type2] && cx2pos[type1] == cxpos[type2]
						&& oypos[type1] == oypos[type2] && oy2pos[type1] == oypos[type2]);
					f2 = (x1 == x2) ? (cypos[type1] == cypos[type2] && cypos[type1] == cy2pos[type2]
						&& oxpos[type1] == oxpos[type2] && oxpos[type1] == ox2pos[type2]) 
						: (cxpos[type1] == cxpos[type2] && cxpos[type1] == cx2pos[type2]
						&& oypos[type1] == oypos[type2] && oypos[type1] == oy2pos[type2]);
					return f1 && f2;
					break;
			}
			break;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n,a,b,tmp;
	cin>>n>>a>>b;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin>>tmp;
			targets[i][j] = tmp;
			if (!exist[tmp]) {
				oxpos[tmp] = i;
				oypos[tmp] = j;
			} else {
				ox2pos[tmp] = i;
				oy2pos[tmp] = j;
			}
			exist[tmp]++;
			rexist[tmp]++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin>>tmp;
			if (!exist[tmp]) {
				failure = true;
			} else {
				exist[tmp]--;
				if (oxpos[tmp] != i && ox2pos[tmp] != i) {
					xmove = 1;
				}
				if (oypos[tmp] != j && oy2pos[tmp] != j) {
					ymove = 1;
				}
				if (counter[tmp]) {
					cx2pos[tmp] = i;
					cy2pos[tmp] = j;
				} else {
					cxpos[tmp] = i;
					cypos[tmp] = j;
				}
				counter[tmp] = true;
			}
		}
	}
	if (failure) {
		cout<<"Fail"<<endl;
		return 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < i; k++) {
				if (judge(i,j,k,j)) {
					cpx = true;
				}
			}
			for (int k = 0; k < j; k++) {
				if (judge(i,j,i,k)) {
					cpy = true;
				}
			}
		}
	}
	int result = xmove * b + ymove * a;
	if (cpx && cpy) {
		result += mini(a,b);
	}
	cout<<result<<endl;

	return 0;
}
```

---

