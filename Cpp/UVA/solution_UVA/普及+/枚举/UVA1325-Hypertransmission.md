# Hypertransmission

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4071

[PDF](https://uva.onlinejudge.org/external/13/p1325.pdf)

# 题解

## 作者：_J_C_ (赞：1)

【此题有毒：**如果你先用平方存距离而不是直接开根号，直到要输出的时候在开根号，那么你会WA**（至少我是的，即使long long）】


好了，开始说说思路。思路还是很简单的。

把所有点对间的距离存下来并排序。注意这一步中“距离”建议**开根后储存**，不然你可能不知道怎么WA的（数据的问题吧）。

然后从小到大枚举距离。当然枚举的距离必须是出现在有序序列里的距离。

正确性在于，**如果这个距离不能使的某两个新的点对相互接触，那么这个距离一定是可以缩小的，即不优的**。

然后枚举的时候顺手记录一下record与same[]，前者表示有多少个不稳定的星球，后者表示这个星球收到了多少个与它相同节目的星球的信号。当然，如果收到了不同的信号，--same[]

就好了。

```cpp
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <algorithm>


class item
{
public:
	double len;
	int fr, to;//这是那两个点对的距离
	bool operator<(const item& it) const
	{
		return len < it.len;
	}
}all[1123456];
int end;

int n;
double x[1123], y[1123], z[1123];

#define SQR(a) ((a) * (a))
inline double cntlen(int a, int b)
{
	return sqrt(SQR(x[a] - x[b]) + SQR(y[a] - y[b]) + SQR(z[a] - z[b]));
}

int anounce[1123], same[1123];
int max, record;
double r;


int main()
{
	while (~scanf("%d", &n))
	{
		max = 0; r = 0; record = 0; end = 0;
		for (int i(0); i != n; ++i)
		{
			scanf("%lf%lf%lf%d", &x[i], &y[i], &z[i], &anounce[i]);
			for (int j(0); j != i; ++j)
			{
				all[end].len = cntlen(i, j);
				all[end].fr = i;
				all[end++].to = j;
			}
			same[i] = 1;
		}
		std::sort(all, all + end);
		for (int i(0); i != end; )
		{
			double val(all[i].len);
			while (all[i].len == val && i != end)//一直往下直到有需要不同半径的点对。
//有经验的读者可以看出这个浮点比较写得非常的糟糕、本来使用int存距离的（存开根前的距离），直接改double后这里没来折腾，结果还是过了
			{
				if (anounce[all[i].fr] == anounce[all[i].to])
				{
					if (++same[all[i].fr] == 0) --record;
					if (++same[all[i].to] == 0) --record;
				}
				else
				{
					if (same[all[i].fr]-- == 0) ++record;
					if (same[all[i].to]-- == 0) ++record;
				}
				++i;
			}
			if (record > max)
			{
				max = record;
				r = all[i - 1].len;
			}
		}
		printf("%d\n%.4f\n", max, r);
	}
	return 0;
}
```

---

