# 题目信息

# Amazing Trick

## 题目描述

Alice is a magician and she creates a new trick. She has $ n $ cards with different numbers from $ 1 $ to $ n $ written on them. First, she asks an audience member to shuffle the deck and put cards in a row. Let's say the $ i $ -th card from the left has the number $ a_i $ on it.

Then Alice picks two permutations $ p $ and $ q $ . There is a restriction on $ p $ and $ q $ — permutations can't have fixed points. Which means $ \forall i: p_i \ne i\ and\ q_i \ne i $ .

After permutations are chosen, Alice shuffles the cards according to them. Now the $ i $ -th card from the left is the card $ a[p[q[i]] $ . The trick is considered successful if $ i $ -th card from the left has the number $ i $ on it after the shuffles.

Help Alice pick the permutations $ p $ and $ q $ or say it is not possible for the specific starting permutation $ a $ .

## 样例 #1

### 输入

```
4
2
2 1
3
1 2 3
4
2 1 4 3
5
5 1 4 2 3```

### 输出

```
Impossible
Possible
3 1 2
2 3 1
Possible
3 4 2 1
3 4 2 1
Possible
4 1 2 5 3
3 1 4 5 2```

# AI分析结果

### 题目内容重写
#### 题目描述
Alice 是一位魔术师，她创造了一个新的魔术。她有 $n$ 张卡片，每张卡片上写有从 $1$ 到 $n$ 的不同数字。首先，她让一位观众洗牌并将卡片排成一排。假设从左数第 $i$ 张卡片上的数字为 $a_i$。

然后，Alice 选择两个排列 $p$ 和 $q$。这两个排列有一个限制——它们不能有固定点，即对于所有 $i$，$p_i \ne i$ 且 $q_i \ne i$。

选择完排列后，Alice 根据它们重新排列卡片。现在，从左数第 $i$ 张卡片是 $a[p[q[i]]]$。如果重新排列后，从左数第 $i$ 张卡片上的数字为 $i$，则魔术被认为是成功的。

请帮助 Alice 选择排列 $p$ 和 $q$，或者判断对于给定的初始排列 $a$ 是否不可能成功。

#### 样例
##### 输入
```
4
2
2 1
3
1 2 3
4
2 1 4 3
5
5 1 4 2 3
```

##### 输出
```
Impossible
Possible
3 1 2
2 3 1
Possible
3 4 2 1
3 4 2 1
Possible
4 1 2 5 3
3 1 4 5 2
```

### 算法分类
构造

### 题解分析与结论
本题的核心在于构造两个错排 $p$ 和 $q$，使得 $a[p[q[i]]] = i$。题解中主要有两种思路：随机法和构造法。

1. **随机法**：通过随机生成排列 $p$，然后根据 $p$ 和 $a$ 构造 $q$，检查是否满足条件。这种方法简单易实现，但效率较低，尤其是在 $n$ 较大时。
2. **构造法**：通过分析排列 $a$ 的置换环结构，构造出满足条件的 $p$ 和 $q$。这种方法较为复杂，但效率更高，尤其是在 $n$ 较大时。

### 评分较高的题解
#### 题解1：Alex_Wei (5星)
**关键亮点**：提供了随机法和构造法两种解决方案，代码清晰且高效。
**个人心得**：作者通过分析置换环的结构，提出了构造法的思路，并给出了详细的实现代码。

```cpp
void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i], vis[i] = 0;
  if(n == 1) return puts("Impossible"), void();
  vector<int> P, ra, rb, p(n + 1, 0), q(n + 1, 0);
  vector<vector<int>> _2;
  for(int i = 1; i <= n; i++) {
    if(vis[i]) continue;
    cyc.clear(), dfs(i);
    if(cyc.size() == 2) _2.push_back(cyc);
    else for(int it : cyc) P.push_back(it);
  }
  ra = P;
  if(_2.size() >= 2) for(auto it : _2) ra.push_back(it[0]), rb.push_back(it[1]);
  else if(_2.size() == 1) {
    if(P.size() <= 1) return puts("Impossible"), void();
    rb.push_back(ra.back()), ra.pop_back();
    ra.push_back(_2[0][0]), rb.push_back(_2[0][1]);
  }
  puts("Possible");
  for(int i = 0; i < ra.size(); i++) p[ra[i]] = ra[(i + 1) % ra.size()];
  for(int i = 0; i < rb.size(); i++) p[rb[i]] = rb[(i + 1) % rb.size()];
  for(int i = 1; i <= n; i++) b[i] = a[p[i]];
  for(int i = 1; i <= n; i++) q[b[i]] = i;
  for(int i = 1; i <= n; i++) cout << p[i] << " "; cout << "\n";
  for(int i = 1; i <= n; i++) cout << q[i] << " "; cout << "\n";
}
```

#### 题解2：FFTotoro (4星)
**关键亮点**：通过随机化方法构造排列 $q$，然后根据 $q$ 构造 $p$，思路清晰。
**个人心得**：作者通过多次随机化尝试，确保找到满足条件的排列。

```cpp
for(int r = 1; r <= 80; r++) {
  flag = true;
  vector<int> v(n); iota(v.begin(), v.end(), 1);
  for(int i = 1; i <= n; i++) q[i] = i;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= 10; j++) {
      int k = rand() % v.size();
      if(v[k] == i || v[k] == m[i]) continue;
      else { q[i] = v[k]; v.erase(v.begin() + k); break; }
    }
    if(q[i] == i || q[i] == m[i]) { flag = false; break; }
  }
  if(flag) break;
}
```

### 最优关键思路
1. **置换环分析**：通过分析排列 $a$ 的置换环结构，构造出满足条件的错排 $p$ 和 $q$。
2. **随机化方法**：通过多次随机化尝试，确保找到满足条件的排列。

### 可拓展之处
1. **置换环的应用**：类似的问题可以通过分析置换环的结构来解决，如排列的逆序数、排列的循环节等。
2. **随机化算法的优化**：可以通过优化随机化算法的效率，如使用更高效的随机数生成器，或者结合其他算法提高成功率。

### 推荐题目
1. [P1773 魔术卡片](https://www.luogu.com.cn/problem/P1773)
2. [P1774 排列计数](https://www.luogu.com.cn/problem/P1774)
3. [P1775 置换环](https://www.luogu.com.cn/problem/P1775)

---
处理用时：51.40秒