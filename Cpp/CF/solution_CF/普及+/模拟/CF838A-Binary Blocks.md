# Binary Blocks

## 题目描述

You are given an image, that can be represented with a $ 2 $ -d $ n $ by $ m $ grid of pixels. Each pixel of the image is either on or off, denoted by the characters "0" or "1", respectively. You would like to compress this image. You want to choose an integer $ k&gt;1 $ and split the image into $ k $ by $ k $ blocks. If $ n $ and $ m $ are not divisible by $ k $ , the image is padded with only zeros on the right and bottom so that they are divisible by $ k $ . Each pixel in each individual block must have the same value. The given image may not be compressible in its current state. Find the minimum number of pixels you need to toggle (after padding) in order for the image to be compressible for some $ k $ . More specifically, the steps are to first choose $ k $ , then the image is padded with zeros, then, we can toggle the pixels so it is compressible for this $ k $ . The image must be compressible in that state.

## 说明/提示

We first choose $ k=2 $ .

The image is padded as follows:

`<br></br>001000<br></br>101100<br></br>110010<br></br>000000<br></br>`We can toggle the image to look as follows:

`<br></br>001100<br></br>001100<br></br>000000<br></br>000000<br></br>`We can see that this image is compressible for $ k=2 $ .

## 样例 #1

### 输入

```
3 5
00100
10110
11001
```

### 输出

```
5
```

# 题解

## 作者：PeterBei (赞：0)

考虑将整个矩阵放进二位前缀和中，然后枚举 $k$ 并遍历整个矩阵来判断有多少位置需要改变状态，统计最小值即可。

需要注意前缀和数组需要开两倍以满足在外圈补 $0$ 的需求。

```
int calc(int x1, int y1, int x2, int y2){
	return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}
int main(){
    int n = read(), m = read();
    for(int i = 1; i <= n; i++){
    	scanf("%s", str + 1);
    	for(int j = 1; j <= max(n, m) * 2; j++){
    		sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (str[j] == '1');
		}
	}
	for(int i = n + 1; i <= max(n, m) * 2; i++){
    	for(int j = 1; j <= max(n, m) * 2; j++){
    		sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	} int ans = 0x3f3f3f3f;
	for(int k = 2; k <= max(n, m); k++){
		int newn = (n / k + (bool)(n % k)) * k, newm = (m / k + (bool)(m % k)) * k, kr = k * k, cnt = 0;
		for(int i = 1; i <= newn; i += k){
			for(int j = 1; j <= newm; j += k){
				int z = calc(i, j, i + k - 1, j + k - 1);
				cnt += min(kr - z, z);
			}
		} ans = min(ans, cnt);
	} cout << ans;
    return 0;
}
```

---

## 作者：OcTar (赞：0)

## CF838A

### 题目大意

要把 $n\times m$ 的矩阵分成若干 $k\times k$ 的块，使得每个块相等，周围部分全 ``0``，求出需修改最少的 $k$。

### 题目分析

时限 2s，考虑直接枚举 $k$。

维护一个二维前缀和表示块内 ``1`` 的数量，注意前缀和数组要开大，防止块长接近 $n$ 或 $m$ 的情况。

最后枚举每个块，算出最小修改数目即可。注意输入的矩阵不含空格，用字符串输入。

完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5010;
int a[maxn][maxn];
int n, m, ans = 0x3f3f3f3f;
int calc(int x1, int y1, int x2, int y2) {
	return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) a[i][j + 1] = s[j] - '0';
	}
	for (int i = 1; i <= max(n, m) * 2; i++) {
		for (int j = 1; j <= max(n, m) * 2; j++) {
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}
	for (int k = 2; k <= max(n, m); k++) {
		int kn = ceil(n * 1.0 / k) * k, km = ceil(m * 1.0 / k) * k, kcnt = 0;
		for (int i = 1; i <= kn; i += k) {
			for (int j = 1; j <= km; j += k) {
				int num = calc(i, j, i + k - 1, j + k - 1);
				kcnt += min(num, k * k - num);
			}
		}
		ans = min(ans, kcnt);
	}
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：KaguyaH (赞：0)

[CF838A](/problem/CF838A)

直接枚举 $k$ 即可。

利用二维前缀和记录范围内 $1$ 的数量。

$n, m$ 同阶，总运算次数约为

$$\sum_{i = 1}^n \frac{n^2}{i^2} < \sum_{s = 1}^{n^2} \frac{n^2}i = n^2 \log n.$$

时间复杂度为 $\mathcal O(n^2 \log n)$，不太稳。

实际上，若 $d | k \land 1 < d < k$，则 $d$ 必然不劣于 $k$，因为每个块内都有显然更细致的切换方式。故 $k$ 选质数即可。

$n$ 以内的质数密度约为 $\frac 1 {\log n}$，故总体时间复杂度为 $\mathcal O(n^2)$。

Code：

```cpp
# include <cctype>
# include <cstdio>

namespace Main {
    namespace Source {
        typedef short unsigned int hu;
        typedef unsigned int uint;
        static const uint UINT_MAX(0xffffFFFFu);
        static inline char read() { char t; while (isspace(t = getchar())); return t; }
        static inline const uint min(const uint a, const uint b) { return b < a ? b : a; }
        static inline const void amin(uint& a, const uint b) { a = min(a, b); }
        static inline const bool is_prime(const hu x) {
            if (x < 2) return false;
            for (hu i(2); i < x; ++i) if (not(x % i)) return false;
            return true;
        }
    }
    using namespace Source;
    enum { N = 2500, M = 2500 };
    static hu n, m;
    static hu a[N * 2][M * 2];
    static uint s[N * 2][M * 2];
    static uint ans(UINT_MAX);
    static inline const uint nt(const hu k, const hu x, const hu y) {
        const uint t(s[x][y] + s[x - k][y - k] - s[x - k][y] - s[x][y - k]);
        return min(t, k * k - t);
    }
    static inline const uint nt(const hu k) {
        uint r(0);
        for (hu i(k); i - k < n; i += k)
            for (hu j(k); j - k < m; j += k)
                r += nt(k, i, j);
        return r;
    }
    static inline const void main() {
        scanf("%hu%hu", &n, &m);
        for (hu i(1); i <= n; ++i)
            for (hu j(1); j <= m; ++j)
                a[i][j] = read() - '0';
        for (hu i(1); i < n * 2 or i < m * 2; ++i)
            for (hu j(1); j < m * 2 or j < n * 2; ++j)
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        for (hu i(2); i <= n or i <= m; ++i) if (is_prime(i)) amin(ans, nt(i));
        // printf("%u\n", nt(2));
        printf("%u\n", ans);
    }
}

signed int main() { Main::main(); return 0; }
```

---

