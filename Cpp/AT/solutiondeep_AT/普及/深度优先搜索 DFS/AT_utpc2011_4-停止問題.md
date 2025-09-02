# 题目信息

# 停止問題

## 题目描述

Defunge 程序由一个 $R$ 行 $C$ 列的字符数组组成。下面是一个 Defunge 程序的例子：

```plain
6>--v.
.^--_@
```

Defunge 程序从程序的左上角（即第一行第一列）开始执行。**它的执行方向一开始为"右"**，每次朝着执行方向走一步，**如果走出界了，要跳到另一边**。每走到一个格子上，就要执行这个格子上的命令。 Defunge 程序还有一个存储器，这个存储器只能存储 $[0,15]$ 的一个整数，**存储器一开始存储** $\bold{0}$。

在 Defunge 程序中，有且只有 $11+10=21$ 种命令，下面是它们各自的含义：

- `<`：把执行方向设置为"左"。
- `>`：把执行方向设置为"右"。
- `^`：把执行方向设置为"上"。
- `v`：把执行方向设置为"下"。
- `_`：如果存储器存储的数字是 $0$，就把执行方向设置为"右"，否则设置为"左"。
- `|`：如果存储器存储的数字是 $0$，就把执行方向设置为"下"，否则设置为"上"。
- `?`：把执行方向设置为"上下左右"中的**任意**一个（类似于 dfs 把四个方向全搜一遍）。
- `.`：什么也不做。
- `@`：停止程序。
- `0`-`9`：把存储器设置为这个字符表示的数值。
- `+`：让存储器的数值加 $1$。注意当存储器的数值为 $15$ 时要把它设为 $0$。
- `-`：让存储器的数值减 $1$。注意当存储器的数值为 $0$ 时要把它设为 $15$。

现在，给你一个 Defunge 程序，请判断这个程序是否能停止（即执行到命令`@`）。如果能，输出`YES`，否则输出`NO`。

## 说明/提示

$1\leq R,C\leq 20$，保证程序里只有上文提到的 $21$ 种命令。

# AI分析结果

### 题目内容重写（中文）

Defunge 程序由一个 $R$ 行 $C$ 列的字符数组组成。下面是一个 Defunge 程序的例子：

```plain
6>--v.
.^--_@
```

Defunge 程序从程序的左上角（即第一行第一列）开始执行。**它的执行方向一开始为"右"**，每次朝着执行方向走一步，**如果走出界了，要跳到另一边**。每走到一个格子上，就要执行这个格子上的命令。 Defunge 程序还有一个存储器，这个存储器只能存储 $[0,15]$ 的一个整数，**存储器一开始存储** $\bold{0}$。

在 Defunge 程序中，有且只有 $11+10=21$ 种命令，下面是它们各自的含义：

- `<`：把执行方向设置为"左"。
- `>`：把执行方向设置为"右"。
- `^`：把执行方向设置为"上"。
- `v`：把执行方向设置为"下"。
- `_`：如果存储器存储的数字是 $0$，就把执行方向设置为"右"，否则设置为"左"。
- `|`：如果存储器存储的数字是 $0$，就把执行方向设置为"下"，否则设置为"上"。
- `?`：把执行方向设置为"上下左右"中的**任意**一个（类似于 dfs 把四个方向全搜一遍）。
- `.`：什么也不做。
- `@`：停止程序。
- `0`-`9`：把存储器设置为这个字符表示的数值。
- `+`：让存储器的数值加 $1$。注意当存储器的数值为 $15$ 时要把它设为 $0$。
- `-`：让存储器的数值减 $1$。注意当存储器的数值为 $0$ 时要把它设为 $15$。

现在，给你一个 Defunge 程序，请判断这个程序是否能停止（即执行到命令`@`）。如果能，输出`YES`，否则输出`NO`。

### 说明/提示

$1\leq R,C\leq 20$，保证程序里只有上文提到的 $21$ 种命令。

---

### 综合分析与结论

本题的核心是通过模拟 Defunge 程序的执行过程，判断程序是否能停止。由于程序可能进入死循环，因此需要使用深度优先搜索（DFS）来遍历所有可能的状态，并结合状态标记来避免重复访问。难点在于处理方向变化、存储器的数值更新以及边界条件的处理。

### 所选高分题解

#### 1. 作者：Fijian_Bus (5星)
**关键亮点**：
- 使用 DFS 结合状态标记，避免了重复访问。
- 详细解释了如何处理方向变化和存储器的数值更新。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
bool dfs(int y, int x, int z, int d) {
    y = (y + n) % n;
    x = (x + m) % m;
    if(vis[y][x][z][d]) return false;
    vis[y][x][z][d] = true;
    if(ch[y][x] == '@') return true;
    // 处理各种命令
    switch(ch[y][x]) {
        case '>': d = 1; break;
        case '<': d = 2; break;
        case '^': d = 4; break;
        case 'v': d = 3; break;
        case '_': d = (!z) ? 1 : 2; break;
        case '|': d = (!z) ? 3 : 4; break;
        case '?': 
            for(int i = 1; i <= 4; i++) 
                if(dfs(y + dy[i], x + dx[i], z, i)) return true;
            return false;
        case '+': z = (z + 1) % 16; break;
        case '-': z = (z + 15) % 16; break;
        default: z = ch[y][x] - '0'; break;
    }
    return dfs(y + dy[d], x + dx[d], z, d);
}
```

#### 2. 作者：Jorisy (4.5星)
**关键亮点**：
- 使用 `switch` 语句处理各种命令，代码简洁。
- 详细解释了如何处理边界条件和存储器的数值更新。
- 代码可读性强，逻辑清晰。

**核心代码**：
```cpp
void dfs(int x, int y, int s, int fx) {
    while(x < 1) x += r;
    while(x > r) x -= r;
    while(y < 1) y += c;
    while(y > c) y -= c;
    if(b[x][y][s][fx]) return;
    if(a[x][y] == '@') { cout << "YES" << endl; exit(0); }
    b[x][y][s][fx] = true;
    switch(a[x][y]) {
        case '>': dfs(x + X[4], y + Y[4], s, 4); break;
        case '<': dfs(x + X[3], y + Y[3], s, 3); break;
        case '^': dfs(x + X[1], y + Y[1], s, 1); break;
        case 'v': dfs(x + X[2], y + Y[2], s, 2); break;
        case '_': if(s) dfs(x + X[3], y + Y[3], s, 3); else dfs(x + X[4], y + Y[4], s, 4); break;
        case '|': if(s) dfs(x + X[1], y + Y[1], s, 1); else dfs(x + X[2], y + Y[2], s, 2); break;
        case '?': for(int i = 1; i <= 4; i++) dfs(x + X[i], y + Y[i], s, i); break;
        case '.': dfs(x + X[fx], y + Y[fx], s, fx); break;
        case '+': s = (s + 1) % 16; dfs(x + X[fx], y + Y[fx], s, fx); break;
        case '-': s = (s + 15) % 16; dfs(x + X[fx], y + Y[fx], s, fx); break;
        default: s = a[x][y] - '0'; dfs(x + X[fx], y + Y[fx], s, fx); break;
    }
}
```

#### 3. 作者：_caiji_ (4星)
**关键亮点**：
- 使用 `while` 循环处理边界条件，避免负数取模问题。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码**：
```cpp
void dfs(int x, int y, int dir, int cnt) {
    while(x < 1) x += n;
    while(x > n) x -= n;
    while(y < 1) y += m;
    while(y > m) y -= m;
    if(vis[x][y][dir][cnt]) return;
    if(a[x][y] == '@') { puts("YES"); exit(0); }
    vis[x][y][dir][cnt] = true;
    switch(a[x][y]) {
        case '>': dfs(x + dx[1], y + dy[1], 1, cnt); break;
        case 'v': dfs(x + dx[2], y + dy[2], 2, cnt); break;
        case '<': dfs(x + dx[3], y + dy[3], 3, cnt); break;
        case '^': dfs(x + dx[4], y + dy[4], 4, cnt); break;
        case '_': if(cnt == 0) dfs(x + dx[1], y + dy[1], 1, cnt); else dfs(x + dx[3], y + dy[3], 3, cnt); break;
        case '|': if(cnt == 0) dfs(x + dx[2], y + dy[2], 2, cnt); else dfs(x + dx[4], y + dy[4], 4, cnt); break;
        case '?': for(int i = 1; i <= 4; i++) dfs(x + dx[i], y + dy[i], i, cnt); break;
        case '.': dfs(x + dx[dir], y + dy[dir], dir, cnt); break;
        case '+': dfs(x + dx[dir], y + dy[dir], dir, (cnt + 1) % 16); break;
        case '-': dfs(x + dx[dir], y + dy[dir], dir, (cnt + 15) % 16); break;
        default: dfs(x + dx[dir], y + dy[dir], dir, a[x][y] - '0'); break;
    }
}
```

### 最优关键思路与技巧

1. **状态标记**：使用四维数组 `vis[x][y][z][d]` 来标记当前状态是否已经访问过，避免重复搜索。
2. **边界处理**：通过取模或 `while` 循环处理边界条件，确保程序在走出界时能够跳到另一边。
3. **命令处理**：使用 `switch` 语句或 `if-else` 结构处理各种命令，代码简洁且易于维护。
4. **存储器更新**：在处理 `+` 和 `-` 命令时，使用 `(z + 15) % 16` 来避免负数取模问题。

### 可拓展之处

本题的解法可以拓展到其他类似的模拟题，尤其是涉及状态转移和边界处理的题目。例如，处理迷宫问题、自动机问题等。

### 推荐相似题目

1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录

- **调试经历**：在处理 `?` 命令时，最初没有考虑到四个方向都需要搜索，导致程序无法正确判断是否能停止。
- **踩坑教训**：在处理 `-` 命令时，直接使用 `(z - 1) % 16` 会导致负数取模问题，后来改用 `(z + 15) % 16` 解决。
- **顿悟感想**：通过本题，深刻理解了状态标记在搜索中的重要性，避免重复访问是提高效率的关键。

---
处理用时：92.42秒