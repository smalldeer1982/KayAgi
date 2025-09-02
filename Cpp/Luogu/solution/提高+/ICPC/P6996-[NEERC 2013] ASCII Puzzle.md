# [NEERC 2013] ASCII Puzzle

## 题目描述

Fili 和 Floi 玩一个拼图游戏。Fili 拿出一张用 $W \times H$ 网格线划分的矩形纸，在网格线上将其切成若干块，并小心地将这些块打乱，但不旋转。Floi 必须在不旋转的情况下将这些块重新组合成矩形。

Fili 在将原始纸张切成块时遵循了一些约束，以确保生成的拼图是合理的。首先，Fili 选择三个整数 $w, h$ 和 $n$，使得原始矩形纸的宽度为 $W = w_n$ 个单元格，高度为 $H = h_n$ 个单元格。这里 $w$ 和 $h$ 是 Floi 已知的，但 $n, W$ 和 $H$ 是未知的。这样，原始矩形纸可以被切割成一个简单的 $k = n^{2}$ 个矩形拼图，每个矩形的宽度为 $w$ 个单元格，高度为 $h$ 个单元格。然而，对于 $k > 1$ 的简单拼图不被认为是这个游戏的合理拼图。相反，原始矩形被切割成的块是基于这些简单的 $w \times h$ 单元格矩形，并在相邻块之间有锯齿边缘。正式地说，原始 $W \times H$ 纸张被切割成的块满足以下合理拼图的约束：

有 $k = n^{2}$ 个块。

每个块是一个简单的 $4$ 连通的无孔单元格区域。

原始矩形 $W \times H$ 纸张的每个单元格恰好属于一个块。

每个块包含原始纸张简单拼图中对应 $w \times h$ 矩形的四个角。

每个块的单元格只能来自简单拼图中对应的 $w \times h$ 矩形、与该矩形相邻的单元格以及简单拼图中相邻矩形的内部单元格。

两个相邻块之间的切割不能是直的。只有位于原始 $W \times H$ 纸张边界上的块才有直边。

这些约束的推论是，每个合理拼图的块都适合一个 $(3w - 2) \times (3h - 2)$ 单元格的矩形。此外，每个块的描述将以 $(3w - 2) \times (3h - 2)$ 的单元格网格给出，使得简单拼图中对应的 $w \times h$ 矩形正好位于中心。

下图左侧显示了一张样例矩形纸，用 $W \times H = 12 \times 9$ 的方格网格划分，并用粗虚线切割成一个简单拼图，包含 $k = 9$ 个宽度为 $w = 4$ 个单元格，高度为 $h = 3$ 个单元格的矩形。这个简单拼图的中央 $3 \times 4$ 块的角用黑色显示。它们必须是任何合理拼图的中央块的一部分。合理拼图中央块的其他潜在单元格用灰色显示。粗黑线显示了 $(3w - 2) \times (3h - 2) = 10 \times 7$ 的矩形区域，将描述这个中央块。右图显示了拼图右上角块的相同情况。

![](/upload/images2/neerc_a.png)

你的任务是帮助 Floi 解决这个拼图。

## 说明/提示

时间限制：1 秒，内存限制：128 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 4 3
..........
..........
...AAAA...
...AAAAAA.
...A.AA...
..........
..........

..........
..........
...BBBB...
.....BB...
...BBBB...
....BB....
.....B....

..........
..........
...C..C...
..CCC.C...
...CCCC...
..........
..........

..........
....D.....
...DDDD...
...DDD....
...DDDD...
..........
..........
```

### 输出

```
8 6
AAAABBBB
AAAAAABB
ADAABBBB
DDDDCBBC
DDDCCCBC
DDDDCCCC
```

# 题解

## 作者：zhylj (赞：5)

考虑暴搜每个位置放哪个拼图，然后 $\mathcal O(wh)$ Check，注意到由于题目的限制，角落上的拼图的位置是确定的；而边界上的拼图被确定在 $n-2$ 个位置里，可以在内部枚举选择方案；剩下的位置再暴搜。这样情况就只剩下了 $(n-2)!^4((n-2)^2)!$ 种，非常之少，随便实现就可以过了。

```cpp
const int N = 50;

int k, w, h, n, W, H;
char str[N][N][N], ans[N][N];

void Output() {
	printf("%d %d\n", W, H);
	for(int i = 1; i <= H; ++i)
		printf("%s\n", ans[i] + 1);
}

bool Repl(int id, int pos_x, int pos_y, char c_bg, char c_ed) {
	std::vector <pii> vaild_pos;
	int mov_x = -h + (pos_x - 1) * h + 1, mov_y = -w + (pos_y - 1) * w + 1;
	bool up_b = true, dn_b = true, lf_b = true, ri_b = true;
	for(int y = w; y <= 2 * w - 1; ++y) {
		if(str[id][h - 1][y] != '.' || str[id][h][y] == '.') up_b = false;
		if(str[id][2 * h][y] != '.' || str[id][2 * h - 1][y] == '.') dn_b = false;
	}
	for(int x = h; x <= 2 * h - 1; ++x) {
		if(str[id][x][w - 1] != '.' || str[id][x][w] == '.') lf_b = false;
		if(str[id][x][2 * w] != '.' || str[id][x][2 * w - 1] == '.') ri_b = false;
	}
	if((up_b && pos_x != 1) || (dn_b && pos_x != n) ||
		(lf_b && pos_y != 1) || (ri_b && pos_y != n)) return false;
	for(int x = 1; x <= h * 3 - 2; ++x)
		for(int y = 1; y <= w * 3 - 2; ++y) {
			int nx = x + mov_x, ny = y + mov_y;
			if(str[id][x][y] != '.') {
				if(nx <= 0 || ny <= 0 || nx > H || ny > W || ans[nx][ny] != c_bg)
					return false;
				vaild_pos.push_back(mkp(nx, ny));
			}
		}
	for(pii i : vaild_pos) {
		int x = i.fi, y = i.se;
		ans[x][y] = c_ed;
	}
	return true;
}

bool vis[N];
void Dfs(int cur_pos_x, int cur_pos_y) {
	if(cur_pos_x == n + 1) { Output(); exit(0); }
	for(int i = 1; i <= k; ++i) {
		if(!vis[i] && Repl(i, cur_pos_x, cur_pos_y, '.', i - 1 + 'A')) {
			vis[i] = true;
			Dfs(cur_pos_x + (cur_pos_y == n), cur_pos_y % n + 1);
			Repl(i, cur_pos_x, cur_pos_y, i - 1 + 'A', '.');
			vis[i] = false;
		}
	}
}

int main() {
	rd(k, w, h);
	n = lround(floor(sqrt(k)));
	W = w * n; H = h * n;
	for(int i = 1; i <= H; ++i)
		for(int j = 1; j <= W; ++j) ans[i][j] = '.';
	for(int i = 1; i <= k; ++i)
		for(int j = 1; j <= h * 3 - 2; ++j)
			scanf("%s", str[i][j] + 1);
	Dfs(1, 1);
	return 0;
}
```

---

