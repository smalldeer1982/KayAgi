# [GCJ 2018 #1A] Waffle Choppers

## 题目描述

无限煎饼屋的食客们已经厌倦了圆形煎饼，因此厨师们即将推出新的菜单选项：华夫饼！作为宣传噱头，他们制作了一个巨大的华夫饼，这个华夫饼是一个由 $\mathrm{R}$ 行 $\mathrm{C}$ 列方格组成的网格。每个格子要么是空的，要么包含一颗巧克力豆。

现在，厨师们要把华夫饼分给饥饿的食客们。一条水平切割沿着两行之间的整条网格线切开；一条垂直切割沿着两列之间的整条网格线切开。为了效率，一位厨师会恰好进行 $\mathbf{H}$ 次不同的水平切割，另一位厨师会恰好进行 $\mathbf{V}$ 次不同的垂直切割。这样就会方便地为每位食客分出 $(\mathbf{H}+1) \times (\mathbf{V}+1)$ 块华夫饼。每块的大小不一定相等，但这没关系；市场调研显示食客们并不在意这一点。

食客们真正关心的是他们能分到多少巧克力豆，因此每一块中必须恰好有相同数量的巧克力豆。你能判断厨师们能否用给定数量的水平和垂直切割实现这个目标吗？

## 说明/提示

**样例解释**

注意，最后两个样例不会出现在测试集 1 中。

在样例 1 中，一种可行的切割方式是在从上往下数的第二行和第三行之间进行水平切割，在从左往右数的第四列和第五列之间进行垂直切割。这样会得到如下的分块，每块恰好有两颗巧克力豆：

```
.@@. .@
.... .@

@.@. @@
```

在样例 2 中，无论如何切割，都会得到包含不同数量巧克力豆的分块，因此该情况不可能实现。

在样例 3 中，华夫饼中没有巧克力豆。任何切割方式都会得到每块都含有相同数量巧克力豆（零颗），因此食客们会满意……不过也许没有巧克力豆他们就没那么开心了！

在样例 4 中，和样例 2 一样，无论如何切割都无法实现目标。

在样例 5 中，厨师们可以进行仅有的两次水平切割，并在第一列和第三列右侧进行两次垂直切割。

虽然样例 6 在其他水平和垂直切割次数下可能可行，但请记住你必须恰好使用 $H$ 次水平切割和 $V$ 次垂直切割。无论如何进行一次水平切割和两次垂直切割，都无法实现目标。

**数据范围**

- $1 \leqslant \mathrm{T} \leqslant 100$。

**测试集 1（9 分，公开）**

- $2 \leqslant \mathbf{R} \leqslant 10$。
- $2 \leqslant \mathbf{C} \leqslant 10$。
- $\mathbf{H}=1$。
- $\mathbf{V}=1$。

**测试集 2（16 分，隐藏）**

- $2 \leqslant \mathbf{R} \leqslant 100$。
- $2 \leqslant \mathbf{C} \leqslant 100$。
- $1 \leqslant \mathbf{H}<\mathbf{R}$。
- $1 \leqslant \mathbf{V}<\mathbf{C}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
3 6 1 1
.@@..@
.....@
@.@.@@
4 3 1 1
@@@
@.@
@.@
@@@
4 5 1 1
.....
.....
.....
.....
4 4 1 1
..@@
..@@
@@..
@@..
3 4 2 2
@.@@
@@.@
@.@@
3 4 1 2
.@.@
@.@.
.@.@```

### 输出

```
Case #1: POSSIBLE
Case #2: IMPOSSIBLE
Case #3: POSSIBLE
Case #4: IMPOSSIBLE
Case #5: POSSIBLE
Case #6: IMPOSSIBLE```

# 题解

## 作者：llamn (赞：3)

首先，一个显然的判断是：如果巧克力的总数不是 $({H}+1)({V}+1)$ 的倍数，那么一定没有正确的切割方案。但是从样例就能看出来，只判断这一条是过不了的。

*观察*较小的数据，*注意*到 $H = V = 1$，此时的做法应为使横方向那一刀上下的巧克力数相等、纵方向那一刀左右的巧克力数相等。

这*启示*我们正确的划分方案中，横着切的每一刀之间的巧克力数量都应该相等。纵向同理。

但还有一种反例：在样例中的第四组数据中，可以找到上述划分方案，但最后的结果却不合法。

所以最后我们还要按照找出的方案划分，再验证一下分出的每一块的巧克力是否相等。

```cpp
#include <bits/stdc++.h>
#define _eggy_ using
#define _party_ namespace
#define pf printf
#define sf scanf
_eggy_ _party_ std; _party_ llamn{
int n,m,i,j,k,t0,t1,t2,t3;
int $, _, sum1[110], sum2[110], sum[110][110], q1, q2;
int p1[110], p2[110], tp1, tp2;

#define IMP {puts("IMPOSSIBLE");continue;}
int main()
{
	sf("%d",&$); for (_ = 1; _ <= $; _++)
	{
		pf("Case #%d: ",_);
		
		sf("%d%d%d%d",&n,&m,&q1,&q2);
		memset(sum1,0,sizeof(sum1));
		memset(sum2,0,sizeof(sum2));
		memset(sum,0,sizeof(sum));
		for (i = 1; i <= n; i++)
		{
			sf("%*[^.@]");
			for (j = 1; j <= m; j++)
			{
				sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
				if (getchar() == '@') sum1[i]++, sum2[j]++, sum[i][j]++;
			}				
		}if (sum[n][m] % ((q1 + 1) * (q2 + 1))) IMP
		
		t1 = sum[n][m] / (q1 + 1), t2 = t3 = tp1 = 0;
		for (i = 1; i <= n; i++)
		{
			t2 += sum1[i];
			if (t2 > t1) {t3 = 1; break;}
			if (t2 == t1) p1[++tp1] = i, t2 = 0; // 在 i 行后切蛋糕 
		}if (t3) IMP
		
		t1 = sum[n][m] / (q2 + 1), t2 = t3 = tp2 = 0;
		for (i = 1; i <= m; i++)
		{
			t2 += sum2[i];
			if (t2 > t1) {t3 = 1; break;}
			if (t2 == t1) p2[++tp2] = i, t2 = 0; // 在 i 列后切蛋糕 
		}if (t3) IMP
		
		t1 = sum[n][m] / (q1 + 1) / (q2 + 1), t3 = 0;
		for (i = 1; i <= tp1; i++)
		{
			for (j = 1; j <= tp2; j++)
			{
				if (sum[p1[i]][p2[j]] - sum[p1[i-1]][p2[j]] - sum[p1[i]][p2[j-1]] + sum[p1[i-1]][p2[j-1]] != t1)
				{
					t3 = 1;
					break;
				}
			}if (t3) break;
		}if (t3) IMP
		puts("POSSIBLE");
	}
    return 0;
}
}signed main(){return llamn::main();}

```

---

