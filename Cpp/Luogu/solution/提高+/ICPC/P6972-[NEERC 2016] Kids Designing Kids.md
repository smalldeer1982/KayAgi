# [NEERC 2016] Kids Designing Kids

## 题目描述

凯文和金伯利的额头上都有雀斑。  

他们都在纸上画了自己的雀斑图。每幅图都是一个由像素组成的矩形：每个单元格要么有雀斑，要么没有雀斑。  

他们开玩笑地提议，当他们长大、结婚并有了孩子时，孩子的雀斑图是通过以下过程产生的：  

凯文和金伯利的图通过平行平移移动，然后在每个单元格中，只有当且仅当父母中有一个人在这个位置有雀斑时，孩子才有雀斑。  

现在他们想知道，是否存在一个平行平移可以使他们的孩子获得特定的雀斑图（例如，一个闪电），以及这个平行平移是什么。

## 说明/提示

时间限制：2 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 3
..*
.*.
*.*
3 3
**.
..*
.*.
5 2
.*
*.
**
.*
*.
```

### 输出

```
YES
0 2
```

# 题解

## 作者：zhylj (赞：2)

不妨称三个矩阵分别为 $A,B,C$，问题等价于将三个矩阵平移后异或起来都为 $0$。

分别找到三个矩阵中最上面的 $1$ 中最左边的，我们断言：合法解中这三个 $1$ 必然有两个是重合的。证明考虑反证，若都不重合，考虑这三个点构成的图形中最上面的 $1$ 中最左边的，其必然不可能被其它另外的 $1$ 所覆盖，所以在最终的图形中必然为 $1$，显然不可能为解。

于是只有 $\mathcal O(1)$ 种可能，暴力 Check 即可，时间复杂度 $\mathcal O(n^2)$。

```cpp
#define fi first
#define se second
#define mkp std::make_pair
#define NO mkp(INF, INF)
typedef std::pair <int, int> pii;
const int N = 4000 + 5, O = 2000, INF = 0x3f3f3f3f;

int h[3], w[3], mat[3][N][N], ans_mat[N][N]; pii top_l[3];
char s[N];

void GetAnsMat(int t_1, int t_2, int mov_x, int mov_y) {
	memset(ans_mat, 0, sizeof(ans_mat)); 
	for(int i = 1; i <= h[t_1]; ++i)
		for(int j = 1; j <= w[t_1]; ++j)
			ans_mat[O + i][O + j] ^= mat[t_1][i][j];
	for(int i = 1; i <= h[t_2]; ++i)
		for(int j = 1; j <= w[t_2]; ++j)
			ans_mat[O + i + mov_x][O + j + mov_y] ^= mat[t_2][i][j];
}

std::vector <pii> a, b;
pii Check(int t) {
	a.clear(); b.clear();
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j) {
			if(mat[t][i][j]) a.push_back(mkp(i, j));
			if(ans_mat[i][j]) b.push_back(mkp(i - O, j - O));
		}
	if(a.size() != b.size()) return NO;
	if(a.size() == 0) return mkp(0, 0);
	int mov_x = b[0].fi - a[0].fi, mov_y = b[0].se - a[0].se;
	for(int i = 0; i < a.size(); ++i)
		if(b[i].fi != mov_x + a[i].fi || b[i].se != mov_y + a[i].se) return NO;
	return mkp(mov_x, mov_y);
}

int main() {
	for(int t = 0; t < 3; ++t) {
		scanf("%d%d", &h[t], &w[t]);
		top_l[t] = mkp(0, 0);
		for(int i = 1; i <= h[t]; ++i) {
			scanf("%s", s + 1);
			for(int j = 1; j <= w[t]; ++j) {
				mat[t][i][j] = (s[j] == '*');
				if(top_l[t] == mkp(0, 0) && s[j] == '*')
					top_l[t] = mkp(i, j);
			}
		}
	}
	int mov_x, mov_y; pii tmp;
	mov_x = top_l[0].fi - top_l[1].fi;
	mov_y = top_l[0].se - top_l[1].se;
	GetAnsMat(0, 1, mov_x, mov_y);
	tmp = Check(2);
	if(tmp != NO) {
		printf("YES\n%d %d\n", mov_y, mov_x);
		continue;
	}
	mov_x = top_l[0].fi - top_l[2].fi;
	mov_y = top_l[0].se - top_l[2].se;
	GetAnsMat(0, 2, mov_x, mov_y);
	tmp = Check(1);
	if(tmp != NO) {
		printf("YES\n%d %d\n", tmp.se, tmp.fi);
		continue;
	}
	mov_x = top_l[1].fi - top_l[2].fi;
	mov_y = top_l[1].se - top_l[2].se;
	GetAnsMat(1, 2, mov_x, mov_y);
	tmp = Check(0);
	if(tmp != NO) {
		printf("YES\n%d %d\n", -tmp.se, -tmp.fi);
		continue;
	}
	printf("NO\n");
	return 0;
}
```

---

