# スタンプラリー

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_g



# 题解

## 作者：_LPF_ (赞：5)

[邮戳拉力赛](https://www.luogu.com.cn/problem/AT1223)

太妙了，读完题一点思路没有，感觉就像是什么人类智慧性质 DP 题。

先简单分析，发现一直往上走不优的情况，是因为可能可以先略过某个节点。

然后在上面的某个节点 $u$ 进 $e$ 出，绕一圈跑回来，到这里 $d$ 进 $v$ 出，再回去。

看似这个过程很复杂，但实际有性质：这样上下绕圈的节点对是可以匹配的，且一定是**括号序**。

根据贪心的想法，显然不可能存在非括号序的情况。

括号序有很好的性质，就像括号序列计数一样，可以记待匹配的左括号数，并把左右括号的贡献拆靠 DP，从而快速转移。

可以设 $f(i,j)$ 表示前 $i$ 个车站，有 $j$ 个 $d$ 进 $v$ 出的待 $[i+1,n]$ 的车站匹配的最小时间。

转移分挺多种：

- $f(i,j)\gets f(i-1,j)+u+v$，就是正常经过。
- $f(i,j)\gets f(i-1,j)+e+d(j>0)$，上面下来的时候顺路盖戳。
- $f(i,j)\gets f(i-1,j+1)+u+e$，右括号。
- $f(i,j)\gets f(i-1,j-1)+d+v$，左括号。

当然每次都要 $f(i,j)\gets f(i,j)+2\times j\times t$，一次绕圈都要下去再回来。

但这还没有结束，因为第 $i$ 个车站显然可能不会只做一次 左/右括号。

那显然不能平白无故给复杂度多个 $n$，实际也很简单，直接按顺序同层转移即可。

代码简单的可怕。

```cpp
const int N = 3010;
const int inf = 0x3f3f3f3f;
int n, t, f[N][N];

void Min(int &x, int y) {x = x < y ? x : y;}

int main() {
	n = read(), t = read();
	rep(i, 0, n) rep(j, 0, n) f[i][j] = inf;
	f[0][0] = 0;
	rep(i, 1, n) {
		int u = read(), v = read(), d = read(), e = read();
		rep(j, 1, n) if(f[i - 1][j] < inf) f[i - 1][j] += 2 * j * t;
		rep(j, 0, n) Min(f[i][j], f[i - 1][j] + u + v);
		rep(j, 1, n) Min(f[i][j], f[i - 1][j] + d + e);
		rep(j, 1, n) Min(f[i][j], f[i - 1][j - 1] + d + v);
		rep(j, 0, n - 1) Min(f[i][j], f[i - 1][j + 1] + u + e);
		rep(j, 1, n) Min(f[i][j], f[i][j - 1] + d + v);
		per(j, n - 1, 0) Min(f[i][j], f[i][j + 1] + u + e);
	}
	printf("%d\n", f[n][0] + t * (n + 1));
	return 0;
}
```

---

