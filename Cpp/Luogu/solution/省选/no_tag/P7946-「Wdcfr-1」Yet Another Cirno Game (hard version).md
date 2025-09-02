# 「Wdcfr-1」Yet Another Cirno Game (hard version)

## 题目描述

**两个版本之间的唯一区别是你是否需要找到一种方法来获得最大分数。**

Cirno 画了一张图。这张图由 $4\cdot n$ 个节点组成，节点编号为 $0$ 到 $4\cdot n - 1$。此外：

- 对于 $0\le i\le 3$ 和 $0 \le j, k < n$，节点 $(n\cdot i + j)$ 和节点 $(n\cdot i + k)$ 是相连的。
- 对于 $0 \le i \le n$ 和 $0 \le j, k \le 3$，节点 $(i + n\cdot j)$ 和节点 $(i + n\cdot k)$ 是相连的。

Cirno 叫来了 Daiyousei 和她一起玩。

游戏规则如下：

- 首先，Cirno 选择 $2\cdot n$（即一半）的节点，并将它们涂成蓝色。其余的节点保持红色。
- 然后有 $2\cdot n$ 轮：每轮 Cirno 首先选择一个蓝色节点，Daiyousei 选择一个红色节点。如果这两个节点是相连的，Daiyousei 得到一分。

试图最大化 Daiyousei 能得到的分数。

## 说明/提示

### 解释

在下图中，矩阵中的节点是相互连接的。Cirno 选择了节点 $0,1,2,3,4,5$。

下面的箭头显示了 Daiyousei 获得她能得到的最大分数的一种可能方式。

![](https://cdn.luogu.com.cn/upload/image_hosting/7v3w2cz9.png)

### 约束

$1\le n\le 2\times 10^6$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
0 1 2 3 4 5```

### 输出

```
6
6 7 8 9 10 11```

# 题解

## 作者：NaOH_Frog (赞：3)

算是官方题解（

该问题可以转化为：有一个 $4$ 行 $n$ 列的矩阵，琪露诺选取了 $2\cdot n$ 个点（假设染为黑色），每次按照题目中的流程进行，如果琪露诺和大妖精选的两个点在同行同列大妖精即得分。

定义 「$H(x)$」为有 $x$ 个黑格的列。

显然，一个 $H(x)$ 可以和一个 $H(4-x)$ 抵消。特别的，一个 $H(2)$ 可以自己把自己消掉。

如果我们先按上述方式把能消的列都消了，那么我们会发现只会剩下 $H(4)$ 和 $H(1)$（或 $H(3)$ 和 $H(0)$，可以根据对称性不失一般性的只考虑其中一种），而且 $H(1)$ 是 $H(4)$ 数量的 $2$ 倍。设此时 $H(4)$ 数量为 $d$。

那么我们考虑先在一开始把多余的 $H(4)$ 消掉。现在我们定义「位置为 $x$ 的列」为唯一一个黑格在第 $x$ 行的 $H(1)$。删掉多余的 $H(4)$ 有三种方法：

第一种拿两个位置不同的 $H(1)$ 删掉一个 $H(4)$。这时，当且仅当某一位置的 $H(1)$ 超过一半时才可能删不完。可以列方程解决。具体解决方法可以把四种位置的列的数量排序后作为四个参数（设为 $w,x,y,z$），把每一组（如位置为 $1$ 的列和位置为 $2$ 的列）可能的删法的数量当作未知数（设为 $a$ 到 $f$），然后解不等式。或者钦定其中两个为 $0$ 也行。

这么消完以后，会发现只剩下 $1$ 种位置的 $H(1)$ 了。设此时只剩位置为 $0$ 的 $H(1)$。

第二种是拿一个第 $0$ 行为白格的 $H(3)$ 去消。

第三种是拿一个第 $0$ 行为白格的 $H(2)$ 和另一个位置为 $0$ 的 $H(1)$ 去消。

如果还有剩下的 $H(4)$，只好摆烂，每个 $H(4)$ 都得剩下一个格子不能得分。

按照上述顺序模拟过程即可。记得将多余的 $H(4)$ 删完了之后把剩下的全匹配掉。

为什么这样最优呢？因为第 $0$ 行的白格全部被匹配掉了。而且如果 $H(1)$ 全部能被消完，显然能把所有多余的 $H(4)$ 消掉。


```cpp
#include <bits/stdc++.h>
#define tn (2 * n)
using namespace std;
const int N = 2e6 + 7;
int f[N][4];
int a[2 * N], cnt[N], n, ans[2 * N], anss[4 * N], siz[5], mp[4 * N], tmp, dif;
int p[5][N];
bool used[N];
int v[4][N], sizz[4];
bool chg = false;
#define re register
inline int read()
{
	re int x=0,f=1;re char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
int*GP(){static int x[]{0,1,2,3};sort(x,x+4,[](int x,int y){return sizz[x] > sizz[y];});return x;}
void out(){
	for(int p0, p4, i = 0; i < siz[0]; i++){
		p0 = p[0][i], p4 = p[4][i];
		for(int j = 0; j < 4; j++) f[p0][j] = f[p4][j] + tn;
	}
	int po = 0;
	for(int p1, p3, i = 0; i < siz[1]; i++){
		p1 = p[1][i], p3 = p[3][po];
		if(used[p1]) continue;
		while(used[p3]) po++, p3 = p[3][po];
		int v1 = 0, v2 = -1, v3 = 0, v4 = 0;
		bool flag = false;
		for(int j = 0; j < 4; j++) if(f[p1][j] && !f[p3][j]) flag = true, v1 = j;
		if(!flag){
			for(int j = 0; j < 4; j++){
				if(f[p1][j]) v1 = j;
				else if(!f[p3][j]) v4 = j;
				else v2 != -1 ? v3 = j : v2 = j;
			}
		}
		if(flag){
			for(int j = 0; j < 4; j++){
				if(v1 == j) f[p3][j] = f[p1][j] + tn;
				else f[p1][j] = f[p3][j] + tn;
			}
		}else{
			f[p1][v4] = f[p1][v1] + tn;
			f[p3][v4] = f[p3][v1] + tn;
			f[p1][v2] = f[p3][v2] + tn;
			f[p1][v3] = f[p3][v3] + tn;
		}
		po++;
	}
	for(int p2, i = 0; i < siz[2]; i++){
		p2 = p[2][i];
		if(used[p2]) continue;
		int v1 = -1, v2, v3 = -1, v4;
		for(int j = 0; j < 4; j++){
			if(f[p2][j]) v1 != -1 ? v2 = j : v1 = j;
			else v3 != -1 ? v4 = j : v3 = j;
		}
		f[p2][v3] = f[p2][v1] + tn;
		f[p2][v4] = f[p2][v2] + tn;
	}
	printf("%d\n", tn - dif);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 4; j++){
			if(f[i][j] > tn && chg) anss[mp[i + j * n]] = f[i][j] - tn - 1;
			if(f[i][j] <= tn && chg) ans[f[i][j] - 1] = i + j * n;
			if(f[i][j] > tn && !chg) ans[f[i][j] - tn - 1] = i + j * n;
		}
	}
	for(int i = 0; i < tn; i++) printf("%d ", chg ? ans[anss[i]] : ans[i]);
	exit(0);
}
int main(){
	n = read();
	for(int i = 0; i < tn; i++) a[i] = read(), f[a[i] % n][a[i] / n] = i + 1, cnt[a[i] % n]++, mp[a[i]] = i;
	for(int i = 0; i < n; i++) p[cnt[i]][siz[cnt[i]]] = i, siz[cnt[i]]++;
	if(siz[1] < siz[3]){
		chg = true;
		swap(siz[0], siz[4]);
		swap(siz[1], siz[3]);
		swap(p[0], p[4]);
		swap(p[1], p[3]);
		tmp = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < 4; j++){
				if(f[i][j]) f[i][j] = 0;
				else f[i][j] = ++tmp;
			}
		}
	}
	for(int i = 0; i < siz[1]; i++){
		for(int j = 0; j < 4; j++){
			if(f[p[1][i]][j]){
				v[j][sizz[j]++] = p[1][i];
			}
		}
	}
	dif = siz[4] - siz[0];
	while(dif){
		int p4 = p[4][siz[4] - 1], v1 = GP()[0], v2 = GP()[1], v3 = -1, v4;
		if(!sizz[v2]) break;
		int p11 = v[v1][sizz[v1] - 1], p12 = v[v2][sizz[v2] - 1];
		for(int i = 0; i < 4; i++){
			if(i != v1 && i != v2) v3 != -1 ? v4 = i : v3 = i;
		}
		f[p12][v1] = f[p4][v1] + tn;
		f[p11][v2] = f[p4][v2] + tn;
		f[p12][v3] = f[p4][v3] + tn;
		f[p11][v4] = f[p4][v4] + tn;
		f[p11][v3] = f[p11][v1] + tn;
		f[p12][v4] = f[p12][v2] + tn;
		used[p4] = true, used[p11] = true, used[p12] = true;
		dif--, siz[4]--, sizz[v1]--, sizz[v2]--;
	}
	if(!dif) out();
	int v1 = GP()[0];
	for(int i = 0; i < siz[2]; i++){
		int p2 = p[2][i];
		if(f[p2][v1]) continue;
		int p11 = v[v1][sizz[v1] - 1], p12 = v[v1][sizz[v1] - 2], p4 = p[4][siz[4] - 1];
		int v2 = -1, v3 = 0, v4;
		for(int j = 0; j < 4; j++){
			if(!f[p2][j] && j != v1) v4 = j;
			else if(j != v1) (v2 != -1 ? v3 = j : v2 = j);
		}
		f[p2][v1] = f[p4][v1] + tn;
		f[p2][v4] = f[p4][v4] + tn;
		f[p11][v4] = f[p11][v1] + tn;
		f[p12][v4] = f[p12][v1] + tn;
		f[p11][v2] = f[p4][v2] + tn;
		f[p11][v3] = f[p4][v3] + tn;
		f[p12][v2] = f[p2][v2] + tn;
		f[p12][v3] = f[p2][v3] + tn;
		used[p4] = true, used[p2] = true, used[p11] = true, used[p12] = true;
		dif--, siz[4]--, sizz[v1] -= 2;
		if(!dif) out();
	}
	for(int i = 0; i < siz[3]; i++){
		if(sizz[v1] == 2) break;
		int p3 = p[3][i];
		if(f[p3][v1]) continue;
		int p11 = v[v1][sizz[v1] - 1], p12 = v[v1][sizz[v1] - 2], p13 = v[v1][sizz[v1] - 3], p4 = p[4][siz[4] - 1];
		int v2 = -1, v3 = -1, v4 = 0;
		for(int j = 0; j < 4; j++) if(j != v1) v2 != -1 ? (v3 != -1 ? v4 = j : v3 = j) : v2 = j;
		f[p3][v1] = f[p4][v1] + tn;
		f[p11][v2] = f[p11][v1] + tn;
		f[p12][v3] = f[p12][v1] + tn;
		f[p13][v4] = f[p13][v1] + tn;
		f[p12][v2] = f[p4][v2] + tn;
		f[p13][v2] = f[p3][v2] + tn;
		f[p11][v3] = f[p4][v3] + tn;
		f[p13][v3] = f[p3][v3] + tn;
		f[p11][v4] = f[p4][v4] + tn;
		f[p12][v4] = f[p3][v4] + tn;
		used[p4] = true, used[p3] = true, used[p11] = true, used[p12] = true, used[p13] = true;
		dif--, siz[4]--, sizz[v1] -= 3;
		if(!dif) out();
	}
	for(int i = 0; i < dif; i++){
		int p11 = v[v1][sizz[v1] - 1], p12 = v[v1][sizz[v1] - 2], p4 = p[4][siz[4] - 1];
		int v2 = -1, v3 = -1, v4 = 0;
		for(int j = 0; j < 4; j++) if(j != v1) v2 != -1 ? (v3 != -1 ? v4 = j : v3 = j) : v2 = j;
		f[p12][v4] = f[p4][v1] + tn;
		f[p11][v2] = f[p11][v1] + tn;
		f[p12][v3] = f[p12][v1] + tn;
		f[p12][v2] = f[p4][v2] + tn;
		f[p11][v3] = f[p4][v3] + tn;
		f[p11][v4] = f[p4][v4] + tn;
		used[p4] = true, used[p11] = true, used[p12] = true;
		siz[4]--, sizz[v1] -= 2;
	}
	out();
	return 0;
}
```

---

