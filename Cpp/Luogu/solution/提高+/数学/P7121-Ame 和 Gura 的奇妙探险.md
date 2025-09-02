# Ame 和 Gura 的奇妙探险

## 题目背景


#### 鉴于洛谷的 SPJ 编译可能依赖于用户选择的编译器版本，且 SPJ 使用了 C++11，请 C++ 选手使用 C++11 或以上进行提交。

~~Lewdson~~ Watson Amelia 和 Gawr Gura 在玩 Mivicraft。

Gura 想将地狱里的交通升级为冰船隧道，但在此之前她先得有一把精准采集的镐子。尝试了一遍又一遍，但终究未能成功的她只好可怜兮兮地找到 Ame。Ame 立刻说道：“So easy! I'll get it in my first try.”

（第一次之后）“Well let's try it again!”

（第二次之后）“Hmmm maybe something's getting wrong today?”

（第三次之后）“I'll give you a ground pound you silly enchanting table!”

（第四次之后）“.. Damn.”

于是 Ame 决定借助一些 技 巧 来拿到精准采集的镐子。她通过查询资料得知 Mivicraft 产生随机数使用了梅森旋转算法（Mersenne Twister，MT19937）。Mivicraft 会通过一个 MT19937 引擎产生一系列的随机数来生成世界的区块。

## 题目描述

Ame 知道，只要她能够找到初始化 MT19937 引擎时使用的种子，她就能够推断出自己如何才能获得一把精准采集的镐子。于是她游历世界，并通过聪明的侦探头脑算出了这个 MT19937 引擎 **刚被初始化后** 生成的 $N$ 个随机数（注：这里的 $N$ 是 MT19937 引擎中的一个参数）。现在她把这 $N$ 个随机数给了你，希望你能够推断出初始化 MT19937 引擎时使用的种子（$0\le\text{种子}<2^{32}$）。值得注意的是，Mivicraft 使用的并非标准的 MT19937 引擎，其中的一些参数与论文相比有所改变，Ame 把它们附加到了输入中。请你帮帮 Ame 吧！

好心的 Mivik 为你准备了一份简单易懂的 MT19937 实现，请在附件中查看。

## 说明/提示

### 样例解释 #1

十个参数全部使用标准的 MT19937 参数，种子为 `233333`。也就是说，你可以通过下面的程序产生同样的随机数序列：

```cpp
#include <iostream>
#include <random>

std::mt19937 engine(233333);
int main() {
	for (int i = 0; i < 624; ++i)
		std::cout << engine() << std::endl;
	return 0;
}
```

### 测试点约束

**本题采用捆绑测试。**

对于全部数据，有 $10\le M<N\le 2\times 10^5$，$0\le A,B,C<2^{32}$，$1\le U,S,T,L\le 31$，$1\le F<2^{32}$，保证 $F$ 是奇数。

每个子任务的具体限制见下表：

| 子任务编号 | 分值 | 特殊限制 |
|:-:|:-:|:-:|
| 1 | 20 | 种子小于等于 $1000$ |
| 2 | 30 | $U=S=T=L=16$，$A=B=C=0$ |
| 3 | 50 | 无 |

**注：下发文件使用 UTF-8 编码，请使用可识别该编码的编辑器打开。**

**附件下载备用链接：[百度网盘](https://pan.baidu.com/s/1ZJQfZK93Qw2lYrDHLQJh2Q) 提取码：jf9e**

## 样例 #1

### 输入

```
见 sample/1.in```

### 输出

```
见 sample/1.out```

## 样例 #2

### 输入

```
见 sample/2.in```

### 输出

```
见 sample/2.out```

# 题解

## 作者：Mivik (赞：4)


[欢迎到我的博客查看](https://mivik.gitee.io/2020/solution/mivik-newbie-and-chinos-contest-2020-solution-amegura/)

首先来拆解一下随机数生成器生成 $N$ 个随机数的过程。

1. 调用 `init(uint32_t seed)`，`index` 置为 $N$。
2. 第一次调用 `gen()` 时由于 `index` 为 $N$ 会先调用 `twist()` 函数，从而将 `index` 置为 `0`。
3. 总共 $N$ 次调用 `gen()`，第 $i$ 次调用会依次返回 `temper(mt[i - 1])`。

然后我们考虑设计出 `temper(uint32_t x)` 的反函数。我们观察这个函数：

```cpp
static inline uint32_t temper(uint32_t x) {
	x ^= (x >> U);
	x ^= (x << S) & B;
	x ^= (x << T) & C;
	x ^= (x >> L);
	return x;
}
```

那么我们只需要实现下面两种操作：

- 根据 `(x ^ (x >> L))` 还原出 `x`
- 根据 `(x ^ ((x << L) & V))` 还原出 `x`

就可以反向进行 `temper` 操作了。

我们以第一种反向操作为例。我们注意到 `(x ^ (x >> L))` 二进制下最高的 `L` 位和 `x` 是相同的，于是我们就可以立即得到 `x` 二进制下的最高 `L` 位。接下来，由于我们知道了 `x` 最高的 `p1` 位，我们可以通过异或还原出 `x` 最高的 `2L` 位，以此类推。下图简单解释了这一流程（`L = 6`）：

```plain
AAAAAABBBBBB--------------------|       --> x
      AAAAAABBBBBB--------------|------ --> (x >> L)
```

我们第一步能知道 `A` 的部分，然后通过异或就可以得出 `B` 的部分，以此类推。下面是简要的代码：

```cpp
inline uint32_t inv_shift_right(uint32_t v, uint8_t bits) {
	if (bits == 32) return v;
	// cur 表示已经得出的部分，k 表示当前已经推导了前几位。
	uint32_t mask = (-1U) << (32 - bits), cur = v & mask;
	for (uint8_t k = bits; k < 32; k += bits)
		cur |= (v ^ (cur >> bits)) & (mask >>= bits);
	return cur;
}
```

同样地，第二种反向操作也可以通过相似的方式实现：

```cpp
inline uint32_t inv_shift_left(uint32_t v, uint8_t bits, uint32_t m) {
	if (bits == 32) return v;
	uint32_t mask = (1U << bits) - 1, cur = v & mask;
	for (uint8_t k = bits; k < 32; k += bits)
		cur |= (v ^ ((cur << bits) & m)) & (mask <<= bits);
	return cur;
}
```

于是我们就可以反向 `temper` 操作来得到刚调用 `twist()` 函数后的 `mt` 数组中的 $N$ 个数。我们观察这个 `twist` 函数：

```cpp
// 得到下一状态
inline void twist() {
	for (int i = 0; i < N; ++i) {
		uint32_t tmp = (mt[i] & (1U << 31)) | (mt[keep_in_range(i + 1)] & 0x7fffffffU);
		tmp = (tmp & 1)? ((tmp >> 1) ^ A): (tmp >> 1);
		mt[i] = mt[keep_in_range(i + M)] ^ tmp;
	}
	index = 0;
}
```

我们发现不行了：我们没法倒推出 `tmp`，因为我们并不知道 `tmp` 一开始到底是不是奇数，如果暴力枚举是 $O(2^N)$ 的。怎么办呢？

我们考虑从其它地方切入，观察这个 `init()` 函数：

```cpp
// 使用种子初始化
inline void init(uint32_t seed) {
	mt[0] = seed;
	for (int i = 1; i < N; ++i)
		// 注意这里的无符号整型乘法溢出为定义行为，即得到的结果与真实结果在模 2 ^ 32 意义下同余
		mt[i] = F * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i;
	index = N;
}
```

由于 $F$ 是奇数，那么 $F$ 在模 $2^{32}$ 意义下有逆元。使用这个逆元，我们可以通过 `mt[i]` 解出 `(mt[i - 1] ^ (mt[i - 1] >> 30))`，从而用上面提到的反向操作得出 `mt[i - 1]` 的值。也就是说我们只要知道了 `mt[N - 1]` 就可以推出整个调用 `twist()` 之前的 `mt` 数组，我们只需要枚举一下 `mt[N - 1]` 的值并检查一下就好了。时间复杂度 $O(N)$。

[mivik.h](https://mivik.gitee.io/mivik.h)

[代码](https://paste.ubuntu.com/p/TPbJGmKDNg/)

---

