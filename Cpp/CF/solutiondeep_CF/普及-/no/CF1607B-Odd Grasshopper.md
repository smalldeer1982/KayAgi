# 题目信息

# Odd Grasshopper

## 题目描述

The grasshopper is located on the numeric axis at the point with coordinate $ x_0 $ .

Having nothing else to do he starts jumping between integer points on the axis. Making a jump from a point with coordinate $ x $ with a distance $ d $ to the left moves the grasshopper to a point with a coordinate $ x - d $ , while jumping to the right moves him to a point with a coordinate $ x + d $ .

The grasshopper is very fond of positive integers, so for each integer $ i $ starting with $ 1 $ the following holds: exactly $ i $ minutes after the start he makes a jump with a distance of exactly $ i $ . So, in the first minutes he jumps by $ 1 $ , then by $ 2 $ , and so on.

The direction of a jump is determined as follows: if the point where the grasshopper was before the jump has an even coordinate, the grasshopper jumps to the left, otherwise he jumps to the right.

For example, if after $ 18 $ consecutive jumps he arrives at the point with a coordinate $ 7 $ , he will jump by a distance of $ 19 $ to the right, since $ 7 $ is an odd number, and will end up at a point $ 7 + 19 = 26 $ . Since $ 26 $ is an even number, the next jump the grasshopper will make to the left by a distance of $ 20 $ , and it will move him to the point $ 26 - 20 = 6 $ .

Find exactly which point the grasshopper will be at after exactly $ n $ jumps.

## 说明/提示

The first two test cases in the example correspond to the first two jumps from the point $ x_0 = 0 $ .

Since $ 0 $ is an even number, the first jump of length $ 1 $ is made to the left, and the grasshopper ends up at the point $ 0 - 1 = -1 $ .

Then, since $ -1 $ is an odd number, a jump of length $ 2 $ is made to the right, bringing the grasshopper to the point with coordinate $ -1 + 2 = 1 $ .

## 样例 #1

### 输入

```
9
0 1
0 2
10 10
10 99
177 13
10000000000 987654321
-433494437 87178291199
1 0
-1 1```

### 输出

```
-1
1
11
110
190
9012345679
-87611785637
1
0```

# AI分析结果

### 题目内容
# 奇数蚱蜢

## 题目描述
蚱蜢位于数轴上坐标为\(x_0\)的点。
无所事事的它开始在数轴上的整数点之间跳跃。从坐标为\(x\)的点向左跳距离\(d\)，会将蚱蜢移动到坐标为\(x - d\)的点，而向右跳则会将它移动到坐标为\(x + d\)的点。
蚱蜢非常喜欢正整数，因此对于从\(1\)开始的每个整数\(i\)，都有以下规律：开始跳跃后恰好\(i\)分钟，它会进行一次距离恰好为\(i\)的跳跃。所以，在第\(1\)分钟它跳\(1\)，然后跳\(2\)，依此类推。
跳跃的方向确定如下：如果蚱蜢在跳跃前所在的点的坐标为偶数，蚱蜢就向左跳，否则它就向右跳。
例如，如果在连续\(18\)次跳跃后它到达坐标为\(7\)的点，由于\(7\)是奇数，它将向右跳距离\(19\)，最终到达点\(7 + 19 = 26\)。由于\(26\)是偶数，下一次跳跃蚱蜢将向左跳距离\(20\)，并移动到点\(26 - 20 = 6\)。
求恰好\(n\)次跳跃后蚱蜢将位于哪个点。

## 说明/提示
示例中的前两个测试用例对应于从点\(x_0 = 0\)开始的前两次跳跃。
由于\(0\)是偶数，长度为\(1\)的第一次跳跃向左进行，蚱蜢最终到达点\(0 - 1 = -1\)。
然后，由于\(-1\)是奇数，长度为\(2\)的跳跃向右进行，将蚱蜢带到坐标为\(-1 + 2 = 1\)的点。

## 样例 #1
### 输入
```
9
0 1
0 2
10 10
10 99
177 13
10000000000 987654321
-433494437 87178291199
1 0
-1 1
```
### 输出
```
-1
1
11
110
190
9012345679
-87611785637
1
0
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过找规律发现蚱蜢每跳4次会回到初始位置附近（与初始位置的偏移量有规律）。算法要点在于利用这个规律，减少计算量，避免对每一次跳跃都进行模拟。解决难点在于如何准确找出这个规律，并根据初始位置的奇偶性进行分类讨论。

### 所选的题解
- **作者：言琢დ（5星）**
  - **关键亮点**：通过分析得出以\(x_0 = 0\)为起点的循环节，进而推出一般情况下\(x_0\)为奇数或偶数时的答案公式，实现\(O(1)\)单次询问。
  - **重点代码**：
```cpp
int maps(int i, int x){
    if (i == 0) return 0;
    if (i == 1) return x;
    if (i == 2) return -1;
    return -x - 1;
}
signed main(){
    int t = init();
    while (t--) {
        int x0 = init(), n = init();
        int d = maps(n % 4, n);
        if (x0 % 2 == 0) print(x0 - d), putchar('\n');
        else print(x0 + d), putchar('\n');
    }
}
```
  - **核心实现思想**：`maps`函数根据跳跃次数\(n\)对\(4\)取模的结果，计算出以\(0\)为起点移动\(n\)步的答案\(d\)，最后根据\(x_0\)的奇偶性输出\(x_0 \pm d\)。

- **作者：remmymilkyway（4星）**
  - **关键亮点**：先通过列举不同\(x_0\)的情况找到每\(4\)次操作回到\(x_0\)的规律，并给出了详细证明，然后通过模拟最后几步得出结果。
  - **重点代码**：
```cpp
void solve() {
	cin >> x0 >> n;
	res = x0;
	for (long long i = n / 4LL * 4LL + 1; i <= n; i++) {
		if (res % 2) res += i;
		else res -= i;
	}
	cout << res << endl;
}
```
  - **核心实现思想**：从\(4\times\lfloor \frac{n}{4}\rfloor + 1\)开始模拟到\(n\)，根据当前位置\(res\)的奇偶性决定是加上还是减去跳跃距离\(i\)。

- **作者：Madefaker（4星）**
  - **关键亮点**：分别模拟\(x_0\)为奇数和偶数的情况，得出位置变化规律以\(4\)为周期的公式，直接套公式求解，时间复杂度\(O(1)\)。
  - **重点代码**：
```cpp
if(x1 % 2ll == 1ll) {
    if(n % 4ll == 0ll) cout << x0;
    else if(n % 4ll == 1ll) cout << x0 + n;
    else if(n % 4ll == 2ll) cout << x0 - 1ll;
    else cout <<x0 - n - 1ll;
}
else {
    if(n % 4ll == 0ll) cout << x0;
    else if(n % 4ll == 1ll) cout << x0 - n;
    else if(n % 4ll == 2ll) cout << x0 + 1ll;
    else cout <<x0 + n + 1;
}
```
  - **核心实现思想**：根据\(x_0\)的奇偶性，以及\(n\)对\(4\)取模的结果，直接套用相应公式输出结果。

### 最优关键思路或技巧
通过对小数据的列举和分析，找出蚱蜢跳跃位置以\(4\)为周期的规律，利用这个规律避免对大量跳跃次数的暴力模拟，从而优化算法。对于此类大数据范围的题目，找规律是一种重要的优化手段。

### 可拓展之处
同类型题通常是给定复杂的操作规则和较大的数据范围，需要通过找规律来简化计算。类似算法套路是先通过手动模拟小数据，观察操作结果的周期性或其他规律，然后利用这些规律优化算法，避免暴力枚举。

### 推荐洛谷题目
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析数据找出规律来解决问题。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：需要通过数学推导找出满足条件的规律。
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)：通过找规律计算金币数量。 

---
处理用时：58.54秒