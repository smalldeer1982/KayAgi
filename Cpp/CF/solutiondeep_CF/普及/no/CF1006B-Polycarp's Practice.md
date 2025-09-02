# 题目信息

# Polycarp's Practice

## 题目描述

#### 题目翻译

给定长度为n的序列，要求分成k段，最大化每段最大值的和

## 样例 #1

### 输入

```
8 3
5 4 2 6 5 1 9 2
```

### 输出

```
20
3 2 3```

## 样例 #2

### 输入

```
5 1
1 1 1 1 1
```

### 输出

```
1
5
```

## 样例 #3

### 输入

```
4 2
1 2000 2000 2
```

### 输出

```
4000
2 2
```

# AI分析结果

### 题目内容重写
给定长度为n的序列，要求分成k段，最大化每段最大值的和。

### 算法分类
贪心

### 综合分析与结论
该题的核心思路是通过贪心策略，选择序列中前k个最大的数作为每段的最大值，然后根据这些数的位置将序列分割成k段。所有题解都采用了类似的思路，即先按数值排序选出前k个最大值，再按位置排序确定分割点。不同题解的主要区别在于代码实现细节和优化程度。

### 所选高星题解

#### 1. 作者：jiang_cheng (4星)
**关键亮点**：
- 使用结构体存储数值和位置，便于排序和分割。
- 代码结构清晰，逻辑简单易懂。
- 通过两次排序分别处理数值和位置，确保分割正确。

**核心代码**：
```cpp
struct E {
  int a, b;
} e[2001];

bool C(E e1, E e2) {
  return e1.a > e2.a;
}

bool B(E e1, E e2) {
  return e1.b < e2.b;
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a;
    e[i].b = i;
  }
  sort(e + 1, e + n + 1, C);
  for (int i = 1; i <= k; i++) {
    ans += e[i].a;
  }
  cout << ans << endl;
  sort(e + 1, e + 1 + k, B);
  for (int i = 1; i <= k; i++) {
    if (i != k && i != 1) {
      m = e[i].b - e[i - 1].b;
      cout << m << " ";
      n -= m;
    } else if (i == 1 && k != 1) {
      cout << e[1].b << " ";
      n -= e[1].b;
    } else {
      cout << n;
    }
  }
  return 0;
}
```

#### 2. 作者：K_Madoka (4星)
**关键亮点**：
- 使用结构体存储数值和位置，简化了排序和分割操作。
- 代码简洁，逻辑清晰，适合初学者理解。
- 通过两次排序分别处理数值和位置，确保分割正确。

**核心代码**：
```cpp
struct num {
  int val, pos;
} a[maxn];

int cmp(num a, num b) {
  return a.val > b.val;
}

int cmp2(num a, num b) {
  return a.pos < b.pos;
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].val;
    a[i].pos = i;
  }
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1; i <= k; i++) ans += a[i].val;
  cout << ans << endl;
  sort(a + 1, a + k + 1, cmp2);
  if (k == 1) {
    cout << n << endl;
    return 0;
  } else {
    for (int i = 1; i <= k; i++) {
      if (i == 1) cout << a[i].pos;
      else if (i == k) cout << ' ' << n - a[k - 1].pos;
      else cout << ' ' << a[i].pos - a[i - 1].pos;
    }
  }
  cout << endl;
  return 0;
}
```

#### 3. 作者：_Cloud_ (4星)
**关键亮点**：
- 使用结构体存储数值和位置，简化了排序和分割操作。
- 代码逻辑清晰，处理了特殊情况（如k=1）。
- 通过两次排序分别处理数值和位置，确保分割正确。

**核心代码**：
```cpp
struct Node {
  int num, id;
} a[N];

bool cmp1(Node x, Node y) {
  return x.num > y.num;
}

bool cmp2(Node x, Node y) {
  return x.id < y.id;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i].num);
    a[i].id = i;
  }
  sort(a + 1, a + 1 + n, cmp1);
  int ans = 0;
  for (int i = 1; i <= k; i++) {
    ans += a[i].num;
    a[i].num = -2147483647;
  }
  sort(a + 1, a + 1 + n, cmp2);
  printf("%d\n", ans);
  int p = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i].num == -2147483647 && k) {
      if (k == 1) {
        printf("%d\n", n - p);
        k--;
      } else {
        printf("%d ", i - p);
        p = i;
        k--;
      }
    }
  }
  return 0;
}
```

### 最优关键思路或技巧
1. **结构体存储**：使用结构体存储数值和位置，便于排序和分割操作。
2. **两次排序**：先按数值排序选出前k个最大值，再按位置排序确定分割点。
3. **特殊情况处理**：如k=1时直接输出整个序列长度。

### 可拓展之处
类似的分割问题可以通过贪心策略解决，如将序列分割成k段，使得每段的和最大或最小。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：46.70秒