# 题目信息

# [NEERC 2017] Designing the Toy

## 题目描述

你是这里的玩具生产大佬。最近你买了一台 3D 打印机，它给你提供了一个~~大赚一笔~~创造新玩具的机会。

你的打印机只能打印由一个个单位方块（棱长为 $1$ 的正方体）构成的几何体。因此，你不能打印出任何“光滑”的几何体（比如球体）。另外，这台打印机打印的几何体可以有完全不相连甚至浮空的部分。

建立空间直角坐标系。一个 $[x , x + 1] $ $\times $ $[y , y + 1]$ $\times $ $[z , z + 1]$ 的方块用整数三元组 $(x , y , z)$ 表示。

现在你想指定打印出的几何体在平面 $Oxy$，平面 $Oxz$ 和平面 $Oyz$ 上的投影面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/udemly1h.png)

给出三个正整数 $a,b,c$，依次表示几何体在平面 $Oxy$，平面 $Oxz$ 和平面 $Oyz$ 上的投影面积。判断该集合体是否存在，若存在，找到满足条件的几何体。

## 说明/提示

时间限制：3s，内存限制：512MB。

Translated by Georiky

## 样例 #1

### 输入

```
4 3 5
```

### 输出

```
6
0 0 0
0 1 0
0 2 0
0 2 2
1 2 2
0 0 2
```

## 样例 #2

### 输入

```
100 1 1
```

### 输出

```
-1
```

# AI分析结果

### 算法分类
构造

### 综合分析与结论
题目要求根据给定的三个投影面积构造一个由单位立方体组成的几何体。核心思路是通过判断三个面积的最大值是否小于等于其他两个面积的乘积来判断是否有解，若有解则通过构造满足条件的立方体排列来实现。

### 所选题解
#### 1. 作者：scp020 (赞：9)
- **星级**: 5
- **关键亮点**: 提供了清晰的构造思路，详细解释了无解条件和构造方法，代码简洁且高效。
- **个人心得**: 通过空间想象能力，解决了构造问题，代码实现中使用了排序和标记数组来简化逻辑。

```cpp
int main() {
    cin >> p[1].first >> p[2].first >> p[3].first;
    p[1].second = 1, p[2].second = 2, p[3].second = 3;
    sort(p + 1, p + 4);
    a = p[1].first, b = p[2].first, c = p[3].first;
    if (a * b < c) {
        cout << -1;
        return 0;
    }
    for (int i = 1; i <= a; i++) v[++cnt][p[1].second] = i, v[cnt][p[2].second] = i, v[cnt][p[3].second] = 1, vis[i][i] = 1;
    for (int i = a + 1; i <= b; i++) v[++cnt][p[1].second] = i, v[cnt][p[2].second] = a, v[cnt][p[3].second] = 1, vis[i][a] = 1;
    for (int i = 1; i <= b; i++)
        for (int j = 1; j <= a && cnt < c; j++) if (!vis[i][j]) v[++cnt][p[1].second] = i, v[cnt][p[2].second] = j, v[cnt][p[3].second] = 1;
    write(cnt), Putchar('\n');
    for (int i = 1; i <= cnt; i++, Putchar('\n')) for (int j = 3; j; j--) write(v[i][j]), Putchar(' ');
    fwrite(Ouf, 1, p3 - Ouf, stdout), fflush(stdout);
    return 0;
}
```

#### 2. 作者：我怂了 (赞：3)
- **星级**: 4
- **关键亮点**: 提供了无解情况的详细证明，构造思路清晰，代码实现中使用了pair来简化排序和坐标处理。
- **个人心得**: 通过简化构造过程，减少了代码复杂度，提高了可读性。

```cpp
int main() {
    pair<int, int> s[4];
    s[1].second = 1, s[2].second = 2, s[3].second = 3;
    cin >> s[1].first >> s[2].first >> s[3].first;
    sort(s + 1, s + 4);
    int a = s[1].first, b = s[2].first, c = s[3].first;
    if (a * b < c) {
        cout << -1;
        goto IAKIOI;
    }
    for (int i = 0; i < a; i++) {
        v[++cnt].p[s[1].second] = i;
        v[cnt].p[s[2].second] = i;
        vis[i][i] = true;
    }
    for (; i < b; i++) {
        v[++cnt].p[s[1].second] = i;
        v[cnt].p[s[2].second] = a - 1;
        vis[a - 1][i] = true;
    }
    for (int j = 0; j < b && i < c; j++) {
        for (int k = 0; k < a && i < c; k++) {
            if (!vis[j][k]) {
                v[++cnt].p[s[1].second] = j;
                v[cnt].p[s[2].second] = k;
                i++;
            }
        }
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; i++) {
        cout << v[i].p[3] << ' ' << v[i].p[2] << ' ' << v[i].p[1] << '\n';
    }
IAKIOI:
    return 0;
}
```

### 最优关键思路或技巧
1. **无解条件判断**: 通过判断三个投影面积的最大值是否小于等于其他两个面积的乘积来确定是否有解。
2. **构造方法**: 沿对角线放置立方体，利用遮挡关系满足其他投影面积的要求。
3. **代码优化**: 使用pair和标记数组简化排序和坐标处理，提高代码可读性和效率。

### 可拓展之处
类似构造题可以通过空间想象和投影关系来简化问题，适用于其他几何体构造或投影问题。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)
3. [P1010 过河卒](https://www.luogu.com.cn/problem/P1010)

### 个人心得摘录
- **scp020**: 通过空间想象能力，解决了构造问题，代码实现中使用了排序和标记数组来简化逻辑。
- **我怂了**: 通过简化构造过程，减少了代码复杂度，提高了可读性。

---
处理用时：29.46秒