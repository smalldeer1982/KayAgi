# 题目信息

# Decode

## 题目描述

In a desperate attempt to obtain your waifu favorite character, you have hacked into the source code of the game. After days of struggling, you finally find the binary string that encodes the gacha system of the game. In order to decode it, you must first solve the following problem.

You are given a binary string $ s $ of length $ n $ . For each pair of integers $ (l, r) $ $ (1 \leq l \leq r \leq n) $ , count the number of pairs $ (x, y) $ $ (l \leq x \leq y \leq r) $ such that the amount of $ \mathtt{0} $ equals the amount of $ \mathtt{1} $ in the substring $ s_xs_{x+1}...s_y $ .

Output the sum of counts over all possible $ (l, r) $ modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
4
0000
01010101
1100111001
11000000111```

### 输出

```
0
130
147
70```

# AI分析结果

### 题目内容重写

#### 题目描述

为了获得你最喜欢的游戏角色，你黑入了游戏的源代码。经过几天的努力，你终于找到了编码游戏抽卡系统的二进制字符串。为了解码它，你必须先解决以下问题。

给定一个长度为 $n$ 的二进制字符串 $s$。对于每一对整数 $(l, r)$ $(1 \leq l \leq r \leq n)$，统计满足条件的 $(x, y)$ $(l \leq x \leq y \leq r)$ 的数量，使得子串 $s_xs_{x+1}...s_y$ 中 $0$ 的数量等于 $1$ 的数量。

输出所有可能的 $(l, r)$ 的计数之和，结果对 $10^9+7$ 取模。

#### 样例

##### 输入

```
4
0000
01010101
1100111001
11000000111
```

##### 输出

```
0
130
147
70
```

### 题解分析与结论

#### 综合分析

本题的核心在于如何高效地统计所有满足条件的子串，并计算其对答案的贡献。各题解普遍采用了前缀和的思路，将 $0$ 视为 $-1$，$1$ 视为 $1$，通过前缀和的变化来快速判断子串中 $0$ 和 $1$ 的数量是否相等。此外，题解中普遍使用了 `map` 或数组来记录前缀和的出现次数，并通过动态更新的方式来计算贡献。

#### 最优关键思路

1. **前缀和与哈希表**：通过前缀和的变化来判断子串中 $0$ 和 $1$ 的数量是否相等，使用 `map` 或数组记录前缀和的出现次数。
2. **贡献计算**：对于每个满足条件的子串 $(x, y)$，其贡献为 $(x+1) \times (n-y+1)$，即该子串被包含的区间数量。
3. **动态更新**：在遍历时动态更新前缀和的出现次数，并累加贡献。

#### 推荐题解

##### 题解1：作者：ZhaoV1 (赞：8)

**星级：5星**

**关键亮点**：
- 使用前缀和和 `map` 记录前缀和的出现次数，思路清晰。
- 通过动态更新 `map` 中的值，高效计算贡献。
- 代码简洁，易于理解。

**核心代码**：
```cpp
void solve(){
	int res = 0;
	cin >> s;
	n = s.size(); s = " " + s;

	map<int,int> mp;
	mp[0] = 1;
	int sum = 0;
	for(int i=1;i<=n;i++){
		if(s[i] == '1') sum++;
		else sum--;
		res = (res+mp[sum]*(n-i+1))%MOD;
		mp[sum] = (mp[sum] + i+1)%MOD;
	}
	cout << (res+MOD)%MOD << '\n';
}
```

##### 题解2：作者：PineappleSummer (赞：4)

**星级：4星**

**关键亮点**：
- 使用前缀和和 `map` 记录前缀和的出现次数，思路清晰。
- 通过动态更新 `map` 中的值，高效计算贡献。
- 代码简洁，易于理解。

**核心代码**：
```cpp
void solve () {
	scanf ("%s", s + 1);
	n = strlen (s + 1);
	cnt.clear (); int ans = 0;
	cnt[0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] + (s[i] == '0' ? 1 : -1);
		ans = (ans + cnt[f[i]] * (n - i + 1) % mod) % mod;
		cnt[f[i]] = (cnt[f[i]] + i + 1) % mod;
	}
	printf ("%lld\n", ans);
}
```

##### 题解3：作者：___w (赞：3)

**星级：4星**

**关键亮点**：
- 使用前缀和和数组记录前缀和的出现次数，避免了 `map` 的 `log` 复杂度。
- 通过动态更新数组中的值，高效计算贡献。
- 代码简洁，易于理解。

**核心代码**：
```cpp
void solve() {
	cin >> (c+1);
	int n = strlen(c+1), ans = 0; vi s(n+1), cnt(n*2+5);
	for (int i = 1; i <= n; ++i) {
		s[i] = c[i] == '0' ? -1 : 1;
		s[i] += s[i-1];
	}
	cnt[n] = 1;
	for (int i = 1; i <= n; ++i) {
		ans = (ans+1ll*(n-i+1)*cnt[s[i]+n]%mod)%mod;
		cnt[s[i]+n] = (cnt[s[i]+n]+i+1)%mod;
	}
	cout << ans << '\n';
}
```

### 拓展与推荐题目

#### 同类型题或类似算法套路

- **前缀和与哈希表**：常用于统计子数组或子串的某些性质，如和、差、数量等。
- **动态更新与贡献计算**：在遍历时动态更新某些值，并计算其对答案的贡献。

#### 推荐题目

1. **洛谷 P1115 最大子段和**（题号：P1115）
2. **洛谷 P3406 前缀和与差分**（题号：P3406）
3. **洛谷 P3374 树状数组 1**（题号：P3374）

### 个人心得总结

- **调试经历**：在处理前缀和时，需要注意初始值的设置，如 `map[0] = 1`，以避免遗漏某些情况。
- **踩坑教训**：在处理负数前缀和时，可以使用偏移量或 `map` 来避免数组下标为负数的问题。
- **顿悟感想**：通过前缀和的变化来判断子串的性质，是一种非常高效且通用的方法，值得深入理解和掌握。

---
处理用时：46.99秒