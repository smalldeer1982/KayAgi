# 题目信息

# XOR on Segment

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . You are allowed to perform two operations on this array:

1. Calculate the sum of current array elements on the segment $ [l,r] $ , that is, count value $ a_{l}+a_{l+1}+...+a_{r} $ .
2. Apply the xor operation with a given number $ x $ to each array element on the segment $ [l,r] $ , that is, execute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a6ed6800239445c652bf1618450a09b2fce8b86d.png). This operation changes exactly $ r-l+1 $ array elements.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise xor operation to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of $ m $ operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

## 样例 #1

### 输入

```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3
```

### 输出

```
26
22
0
34
11
```

## 样例 #2

### 输入

```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3
```

### 输出

```
38
28
```

# AI分析结果

### 题目内容
# 线段上的异或运算

## 题目描述
给定一个数组 $a$，由 $n$ 个整数 $a_{1},a_{2},\cdots,a_{n}$ 组成。允许对该数组执行两种操作：
1. 计算当前数组在区间 $[l,r]$ 上元素的和，即计算 $a_{l}+a_{l + 1}+\cdots+a_{r}$ 的值。
2. 对区间 $[l,r]$ 上的每个数组元素应用与给定数字 $x$ 的异或运算，即执行 $a_{i}=a_{i}\oplus x$，其中 $l\leqslant i\leqslant r$。此操作恰好改变 $r - l + 1$ 个数组元素。

表达式 $x\oplus y$ 表示对数字 $x$ 和 $y$ 应用按位异或运算。该操作在所有现代编程语言中都存在，例如在 C++ 和 Java 语言中用 “^” 表示，在 Pascal 中用 “xor” 表示。

给定一个由 $m$ 个上述类型操作组成的列表。任务是执行所有给定操作，对于每个求和查询，应输出得到的结果。

## 样例 #1
### 输入
```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3
```
### 输出
```
26
22
0
34
11
```

## 样例 #2
### 输入
```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3
```
### 输出
```
38
28
```

### 综合分析与结论
1. **思路**：大部分题解采用线段树结合二进制拆位的方法。由于常规线段树难以处理区间异或操作，将整数序列按二进制位拆分成多个01序列，对每个二进制位分别用线段树维护，这样区间异或操作就转化为01序列的区间取反操作。少数题解采用暴力法，如循环展开或利用指令集优化暴力算法，还有使用分块算法解题。
2. **算法要点**：
    - **线段树 + 二进制拆位**：将每个数拆成二进制，用线段树维护每个区间内第 $i$ 二进制位为 $1$ 的个数。区间异或时，根据异或值的二进制位决定是否对相应二进制位的线段树进行区间取反；区间求和时，将每个二进制位的统计结果乘以 $2^i$ 后累加。
    - **暴力法**：通过循环展开或指令集优化，直接对区间进行操作。循环展开是将循环体展开以减少循环控制的开销；指令集优化利用特定指令集并行处理数据，提高运算效率。
    - **分块算法**：将数组分块，在块内统计和与二进制位信息，通过维护每个块的公共异或和、每位0和1的个数等信息，实现区间异或和求和操作。
3. **解决难点**：常规线段树无法直接处理区间异或操作与区间求和的兼容问题。通过二进制拆位，将异或操作分解到各个二进制位上，使得每个二进制位上的操作可以用经典的线段树区间翻转问题解决。暴力法需解决时间复杂度问题，通过循环展开和指令集优化提高效率。分块算法需合理维护块内信息，以实现高效的区间操作。

### 所选的题解
1. **作者：gzw2005 (赞：65)  星级：5星**
    - **关键亮点**：思路清晰，先通过简化问题找规律，再详细阐述二进制拆位结合线段树的解法，代码实现规范，注释详细。
    - **个人心得**：无
    - **重点代码 - 核心实现思想**：通过 `buildTree` 函数建树，将每个数按二进制位处理并记录在 `cnt` 数组中；`update` 函数实现区间异或，根据异或值二进制位对 `cnt` 数组相应位进行取反操作并更新懒标记；`query` 函数实现区间求和，将每个二进制位的统计结果乘以 $2^i$ 累加得到和。
```cpp
void buildTree(int L, int R, int cur) {
    if (L == R) {
        for (int i = 0; i < 20; i++)
            if ((a[L] >> i) & 1) cnt[cur][i] = 1;
        return;
    }
    int mid = (L + R) >> 1;
    buildTree(L, mid, ls(cur));
    buildTree(mid + 1, R, rs(cur));
    up(cur);
}
void update(int L, int R, int cur, int l, int r, int val) {
    if (R < l || r < L) return;
    if (l <= L && R <= r) {
        for (int i = 0; i < 20; i++)
            if ((val >> i) & 1) cnt[cur][i] = (R - L + 1) - cnt[cur][i];
        tag[cur] ^= val;
        return;
    }
    int mid = (L + R) >> 1;
    down(L, R, cur);
    update(L, mid, ls(cur), l, r, val);
    update(mid + 1, R, rs(cur), l, r, val);
    up(cur);
}
long long query(int L, int R, int cur, int l, int r) {
    if (R < l || r < L) return 0;
    if (l <= L && R <= r) {
        long long ret = 0, Pow = 1;
        for (int i = 0; i < 20; i++) {
            ret += Pow * cnt[cur][i];
            Pow <<= 1;
        }
        return ret;
    }
    int mid = (L + R) >> 1;
    down(L, R, cur);
    return query(L, mid, ls(cur), l, r) + query(mid + 1, R, rs(cur), l, r);
}
```
2. **作者：若玉 (赞：53)  星级：4星**
    - **关键亮点**：另辟蹊径采用暴力 + 循环展开的方法，代码简洁，利用题目时限和数据范围特点卡过题目。
    - **个人心得**：无
    - **重点代码 - 核心实现思想**：在循环中展开操作，`opt == 1` 时，将区间求和循环展开，每次累加7个数，并处理边界情况；`opt == 2` 时，将区间异或循环展开，每次对7个数进行异或操作，并处理边界。
```cpp
while (m--) {
    opt = read(); x = read(); y = read();
    if (opt == 1) {
        ans = 0;
        for (int i = x; i <= y; i += 7)
            ans += a[i] + a[i + 1] + a[i + 2] + a[i + 3] + a[i + 4] + a[i + 5] + a[i + 6], l = i;
        for (int i = l; i <= l + 6; i++)
            if (i > y) ans -= a[i];
        printf("%I64d\n", ans);
    } else {
        z = read();
        for (int i = x; i <= y; i += 7) {
            a[i] ^= z;
            a[i + 1] ^= z;
            a[i + 2] ^= z;
            a[i + 3] ^= z;
            a[i + 4] ^= z;
            a[i + 5] ^= z;
            a[i + 6] ^= z;
            l = i;
        }
        for (int i = l; i <= l + 6; i++)
            if (i > y) a[i] ^= z;
    }
}
```
3. **作者：SymphonyOfEuler (赞：15)  星级：4星**
    - **关键亮点**：同样采用线段树 + 二进制拆位，代码结构清晰，对线段树的各个操作（建树、更新、查询）分别用函数实现，逻辑明确。
    - **个人心得**：无
    - **重点代码 - 核心实现思想**：`build_tree` 函数建树，根据每个数二进制位情况初始化 `cnt` 数组；`update` 函数实现区间异或，根据异或值二进制位决定是否对相应二进制位的线段树进行区间取反；`query` 函数实现区间求和，返回相应二进制位上1的个数，最终在主函数中累加得到和。
```cpp
void build_tree(int p, int l, int r, int x) {
    if (l == r) {
        cnt[x][p] = (a[l] & d[x])!= 0;
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(lc(p), l, mid, x);
    build_tree(rc(p), mid + 1, r, x);
    push_up(p, x);
}
void update(int p, int l, int r, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
        move_tag(p, l, r, x);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r, x);
    if (ql <= mid) {
        update(lc(p), l, mid, ql, qr, x);
    }
    if (qr > mid) {
        update(rc(p), mid + 1, r, ql, qr, x);
    }
    push_up(p, x);
}
int query(int p, int l, int r, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
        return cnt[x][p];
    }
    push_down(p, l, r, x);
    int res = 0, mid = (l + r) >> 1;
    if (ql <= mid) {
        res += query(lc(p), l, mid, ql, qr, x);
    }
    if (qr > mid) {
        res += query(rc(p), mid + 1, r, ql, qr, x);
    }
    return res;
}
```

### 最优关键思路或技巧
线段树结合二进制拆位是本题的主流且高效的方法。通过将整数拆分为二进制位，把复杂的区间异或操作转化为简单的01序列区间翻转问题，利用线段树的特性进行维护和查询。这种方法充分利用了位运算的独立性，巧妙解决了区间异或与求和的不兼容性问题。

### 可拓展之处
同类型题或类似算法套路：对于涉及区间位运算（如异或、与、或）且需要维护区间和等信息的问题，可考虑二进制拆位结合线段树的方法。类似地，在处理一些对整数的特殊操作且要求区间统计的场景下，也可尝试将整数按位分解处理。

### 洛谷相似题目
1. **P3373 【模板】线段树 2**：涉及区间乘法、加法等操作，需要合理维护线段树的懒标记，与本题线段树维护思路有相似之处。
2. **P1558 色板游戏**：同样是线段树维护区间信息，涉及区间染色和查询颜色数量等操作，锻炼线段树的综合应用能力。
3. **P2824 [HEOI2016/TJOI2016]排序**：虽然不是位运算相关，但通过线段树维护区间信息来解决排序问题，对理解线段树的应用场景拓展有帮助。 

---
处理用时：51.49秒