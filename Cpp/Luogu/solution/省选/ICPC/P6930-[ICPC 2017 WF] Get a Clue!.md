# [ICPC 2017 WF] Get a Clue!

## 题目描述

20 世纪 40 年代在英国开发的 Cluedo 游戏是世界上最受欢迎的棋盘游戏之一。游戏的目标是确定谁谋杀了 Mr. Body，使用了什么武器，以及谋杀发生的地点。游戏使用一套卡牌，代表六个人（标记为 A，B，……，F），六种武器（标记为 G，H，……，L）和九个房间（标记为 M，N，……，U）。在游戏开始时，随机选择一张人物卡、一张武器卡和一张房间卡，并从牌堆中移除，因此没有人可以看到它们——它们代表凶手、谋杀武器和谋杀地点。剩下的 18 张牌被洗牌并发给玩家，从玩家 1 开始，然后是她右边的玩家 2，依此类推。一些玩家可能会比其他玩家多一张牌。对于这个问题，有四名玩家，所以玩家 4 右边的人是玩家 1。

游戏的其余时间用于寻找线索。玩家轮流行动，从玩家 1 开始并向右移动。每轮包括提出一个建议（包括一个谋杀嫌疑人、一种武器和一个房间），并询问其他玩家是否有证据可以反驳该建议。例如，你可能会对另一个玩家说：“我相信凶手是人物 A，使用武器 L，在房间 T。”如果其他玩家正好持有其中一张牌，该玩家必须向你（且仅向你）展示那张牌。如果他们有多于一张这样的牌，他们可以展示其中任意一张。

在提出建议时，你必须首先询问你右边的人是否有任何证据。如果他们没有，你继续询问他们右边的人，依此类推，直到有人有证据，或者没有人持有你建议中的任何牌。

即使你不是提出建议的人，很多时候你也可以获得信息。假设在上述例子中，你是第三个玩家，并持有牌 A 和 T。如果有人向建议者展示了证据，你就知道那一定是武器牌 L。记录每轮建议和谁提供了证据是玩游戏时的重要策略。

要赢得游戏，你必须提出指控，陈述你对凶手、武器和房间的最终猜测。在陈述你的指控后，你检查游戏开始时放置的一组三张牌——如果它们与你的指控匹配，你就赢了！不用说，在提出指控之前，你要绝对确定你的指控。

这是你的问题。你是玩家 1。给定一组发给你的牌和建议及证据的历史记录，你需要决定你距离能够提出指控有多近。

## 说明/提示

时间限制：4 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
B I P C F
A G M - - -
```

### 输出

```
AGM
```

## 样例 #2

### 输入

```
2
A B C D H
F G M M
F H M - *
```

### 输出

```
E??
```

## 样例 #3

### 输入

```
3
A C M S D
B G S - G
A H S - - S
C J S *
```

### 输出

```
???
```

# 题解

## 作者：Leasier (赞：0)

我们可以将题意及限制抽象成：

- 第 $1, 2, 3, 4$ 个人依次选择 $A \sim U$ 中卡牌（分别去掉三张 $A \sim F, G \sim L, M \sim U$ 中的卡牌后）的 $5, 5, 4, 4$ 张。
- 第 $1$ 个人的选择固定。
- 每个人有一些必须选的，有一些卡牌集至少选一张的，还有一些必须不选的。
- 求去掉的三张卡牌依次可能是啥，或报告多解。

直接状压爆搜每个人的选择即可，但这样时间复杂度理论上是不对的，如果想要对可以一个一个人爆搜后 FWT 起来。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

int known = 0;
int cnt[57], bans[7];
char s[17], guess[57][7], result[57][7];
bool no[27], ok1[7], ok2[17], ok3[27];
vector<int> v[7];

bool dfs0(int cur, int pre, int state, int ban){
	if (cur == 19){
		int size = v[0].size();
		for (int i = 0; i < size; i++){
			if ((state & v[0][i]) == 0) return false;
		}
		return true;
	}
	int cur_i = cur + 1;
	for (int i = pre + 1; i <= 21; i++){
		if (!(state >> (i - 1) & 1) && !(ban >> (i - 1) & 1) && !(bans[0] >> (i - 1) & 1) && dfs0(cur_i, i, state | (1 << (i - 1)), ban)) return true;
	}
	return false;
}

bool dfs3(int cur, int pre, int state, int ban){
	if (cur == 15){
		int size = v[3].size();
		for (int i = 0; i < size; i++){
			if ((state & v[3][i]) == 0) return false;
		}
		return dfs0(15, 0, 0, ban | state);
	}
	int cur_i = cur + 1;
	for (int i = pre + 1; i <= 21; i++){
		if (!(state >> (i - 1) & 1) && !(ban >> (i - 1) & 1) && !(bans[3] >> (i - 1) & 1) && dfs3(cur_i, i, state | (1 << (i - 1)), ban)) return true;
	}
	return false;
}

bool dfs2(int cur, int pre, int state, int ban){
	if (cur == 11){
		int size = v[2].size();
		for (int i = 0; i < size; i++){
			if ((state & v[2][i]) == 0) return false;
		}
		return dfs3(11, 0, 0, ban | state);
	}
	int cur_i = cur + 1;
	for (int i = pre + 1; i <= 21; i++){
		if (!(state >> (i - 1) & 1) && !(ban >> (i - 1) & 1) && !(bans[2] >> (i - 1) & 1) && dfs2(cur_i, i, state | (1 << (i - 1)), ban)) return true;
	}
	return false;
}

inline bool check(int x, int y, int z){
	int ban = (1 << (x - 1)) | (1 << (y - 1)) | (1 << (z - 1));
	if (no[x] || no[y] || no[z] || (known & ban) != 0) return false;
	return dfs2(6, 0, 0, ban | known);
}

int main(){
	int n;
	char ans1 = '\0', ans2 = '\0', ans3 = '\0';
	cin >> n;
	cin.getline(&s[1], 2, '\n');
	cin.getline(&s[1], 11, '\n');
	for (int i = 1; i <= 5; i++){
		int ch = s[i * 2 - 1] - 'A' + 1;
		known |= 1 << (ch - 1);
		no[ch] = true;
	}
	for (int i = 1; i <= n; i++){
		cin.getline(&s[1], 13, '\n');
		for (int j = 1; j <= 3; j++){
			guess[i][j] = s[j * 2 - 1];
		}
		do {
			cnt[i]++;
			result[i][cnt[i]] = s[cnt[i] * 2 + 5];
			if (cnt[i] == 3) break;
		} while (result[i][cnt[i]] == '-');
	}
	for (int i = 1; i <= n; i++){
		int state = 0;
		for (int j = 1; j <= 3; j++){
			state |= 1 << (guess[i][j] - 'A');
		}
		for (int j = 1; j <= cnt[i] && result[i][j] == '-'; j++){
			bans[(i + j) % 4] |= state;
		}
		if (result[i][cnt[i]] != '-'){
			if (i % 4 == 1){
				int ch = result[i][cnt[i]] - 'A' + 1;
				no[ch] = true;
				v[(i + cnt[i]) % 4].push_back(1 << (ch - 1));
			} else {
				v[(i + cnt[i]) % 4].push_back(state);
			}
		}
	}
	for (int i = 1; i <= 6; i++){
		for (int j = 7; j <= 12; j++){
			for (int k = 13; k <= 21; k++){
				if (check(i, j, k)) ok1[i] = ok2[j] = ok3[k] = true;
			}
		}
	}
	for (int i = 1; i <= 6; i++){
		if (ok1[i]){
			if (ans1 == '\0'){
				ans1 = i + 'A' - 1;
			} else {
				ans1 = '?';
				break;
			}
		}
	}
	for (int i = 7; i <= 12; i++){
		if (ok2[i]){
			if (ans2 == '\0'){
				ans2 = i + 'A' - 1;
			} else {
				ans2 = '?';
				break;
			}
		}
	}
	for (int i = 13; i <= 21; i++){
		if (ok3[i]){
			if (ans3 == '\0'){
				ans3 = i + 'A' - 1;
			} else {
				ans3 = '?';
				break;
			}
		}
	}
	cout << ans1 << ans2 << ans3;
	return 0;
}
```

---

