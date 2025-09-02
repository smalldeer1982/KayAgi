# [ARC118B] Village of M People

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc118/tasks/arc118_b

ARC 国には $ N $ 人の国民がおり、全国民が競技プログラミングのプレイヤーです。各国民にはその競技プログラミングの実力によって、$ 1,\ 2,\ \ldots,\ K $ のいずれかひとつの段位が与えられています。

ARC 国では国勢調査が行われて、その結果、段位 $ i $ の国民はちょうど $ A_i $ 人居ることが分かりました。ARC 国の国王はこの統計データをより理解しやすい形にするために、なるべく各段位の人数の割合を保ったまま、ARC 国の状況を $ M $ 人の村に例えることにしました。

$ M $ 人の村における段位 $ i $ の村民の人数 $ B_i $ を上手く定めることで、$ \max_i\left|\frac{B_i}{M}\ -\ \frac{A_i}{N}\right| $ を最小にしてください。ただし、次が成り立つ必要があります。

- 各 $ B_i $ は非負整数で、$ \sum_{i=1}^K\ B_i\ =\ M $ を満たす

そのような $ B\ =\ (B_1,\ B_2,\ \ldots,\ B_K) $ の定め方を、ひとつ出力してください。

## 说明/提示

### 制約

- $ 1\leq\ K\leq\ 10^5 $
- $ 1\leq\ N,\ M\leq\ 10^9 $
- 各 $ A_i $ は非負整数で、$ \sum_{i=1}^K\ A_i\ =\ N $ を満たす

### Sample Explanation 1

この出力において、$ \max_i\left|\frac{B_i}{M}\ -\ \frac{A_i}{N}\right|\ =\ \max\left(\left|\frac{3}{20}-\frac{1}{7}\right|,\ \left|\frac{6}{20}-\frac{2}{7}\right|,\ \left|\frac{11}{20}-\frac{4}{7}\right|\right)\ =\ \max\left(\frac{1}{140},\ \frac{1}{70},\ \frac{3}{140}\right)\ =\ \frac{3}{140} $ となっています。

### Sample Explanation 2

和を $ M\ =\ 100 $ にしなければならないので、$ B_1\ =\ B_2\ =\ B_3\ =\ 33 $ では 条件が満たされないことに注意してください。 なおこの例においては、`34 33 33` の他、`33 34 33` や `33 33 34` という出力も正解となります。

## 样例 #1

### 输入

```
3 7 20
1 2 4```

### 输出

```
3 6 11```

## 样例 #2

### 输入

```
3 3 100
1 1 1```

### 输出

```
34 33 33```

## 样例 #3

### 输入

```
6 10006 10
10000 3 2 1 0 0```

### 输出

```
10 0 0 0 0 0```

## 样例 #4

### 输入

```
7 78314 1000
53515 10620 7271 3817 1910 956 225```

### 输出

```
683 136 93 49 24 12 3```

# 题解

## 作者：loser_seele (赞：1)

一个显然的转化是 $ \left| \frac{B_i}{M}-\frac{A_i}{N} \right|=\frac{1}{NM} \left| NB_i-MA_i\right| $，于是问题转化为求 $ \left| NB_i-MA_i \right| $ 的最小值。

二分答案，设答案为 $ x $，则必须满足 $ \max{\left| NB_i-MA_i \right|} \leq x $，且 $ \sum B_i =M $。

第一个条件显然可以转化为对于所有的 $ i $，都有 $ {\left| NB_i-MA_i \right|} \leq x $，于是可以直接算出 $ B_i $ 的上下界：

$ {\left| NB_i-MA_i \right|} \leq x \leftrightarrow MA_i-x \leq NB_i \leq MA_i+x \leftrightarrow \lceil \frac{MA_i-x}{N} \rceil \leq B_i \leq \lfloor \frac{MA_i+x}{N}\rfloor $，于是问题转化为限制每个变量的上下界，使得其和为 $ M $。

这个显然不难构造，设左边界为 $ L $，右边界为 $ R $，则答案一定满足 $ \sum L_i \leq M \leq \sum R_i $，否则答案显然无法构造。

于是贪心构造即可，使得 $ B_i $ 在不超过 $ M $ 的情况下尽量大且不超过上界即可。

总时间复杂度 $ \mathcal{O}(K\log{NM}) $，可以通过。

代码：

```cpp
#import<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5 + 7;
int k, n, m, suml, sumr;
int a[maxn], l[maxn], r[maxn];
bool check(int x) 
{
	for (int i = 1; i <= k; i++) 
		l[i] = r[i] = 0;
	suml = 0, sumr = 0;
	for (int i = 1; i <= k; i++) 
    {
		l[i] = max(0ll, (m * a[i] - x + n - 1) / n);
		r[i] = (m * a[i] + x) / n;
		suml += l[i];
		sumr += r[i];
	}
	return suml <= m && sumr >= m;
}
signed main () 
{
	cin >> k >> n >> m;
	for (int i = 1; i <= k; i++) 
		cin >> a[i];
	int L = 0, R = n * m, ans;
	while (L <= R) 
    {
		int mid = (L + R) >> 1;
		if (check(mid)) 
        {
			ans = mid;
			R = mid -1;
		} 
        else 
			L = mid + 1;
	}
	check(ans);
	int sum = suml;
	for (int i = 1; i <= k; i++) 
    {
		int x = min(r[i] - l[i], m - sum);
        sum += x;
        cout << x + l[i] << " ";
	}
}
```


---

