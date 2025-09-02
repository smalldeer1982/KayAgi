# 题目信息

# Group Photo 2 (online mirror version)

## 题目描述

Many years have passed, and $ n $ friends met at a party again. Technologies have leaped forward since the last meeting, cameras with timer appeared and now it is not obligatory for one of the friends to stand with a camera, and, thus, being absent on the photo.

Simply speaking, the process of photographing can be described as follows. Each friend occupies a rectangle of pixels on the photo: the $ i $ -th of them in a standing state occupies a $ w_{i} $ pixels wide and a $ h_{i} $ pixels high rectangle. But also, each person can lie down for the photo, and then he will occupy a $ h_{i} $ pixels wide and a $ w_{i} $ pixels high rectangle.

The total photo will have size $ W×H $ , where $ W $ is the total width of all the people rectangles, and $ H $ is the maximum of the heights. The friends want to determine what minimum area the group photo can they obtain if no more than $ n/2 $ of them can lie on the ground (it would be strange if more than $ n/2 $ gentlemen lie on the ground together, isn't it?..)

Help them to achieve this goal.

## 样例 #1

### 输入

```
3
10 1
20 2
30 3
```

### 输出

```
180
```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3
```

### 输出

```
21
```

## 样例 #3

### 输入

```
1
5 10
```

### 输出

```
50
```

# AI分析结果

### 题目重写
# Group Photo 2 (在线镜像版本)

## 题目描述
许多年过去了，$n$ 个朋友在一次聚会上再次相遇。自上次见面以来，技术取得了巨大进步，带定时器的相机出现了，现在不再需要其中一个朋友拿着相机站着，从而缺席照片。

简单来说，拍照过程可以描述如下。每个朋友在照片上占据一个像素矩形：第 $i$ 个朋友站立时占据一个宽为 $w_{i}$ 像素、高为 $h_{i}$ 像素的矩形。但是，每个人也可以为了拍照躺下，那么他将占据一个宽为 $h_{i}$ 像素、高为 $w_{i}$ 像素的矩形。

照片的总尺寸将为 $W×H$，其中 $W$ 是所有人矩形的总宽度，$H$ 是高度的最大值。朋友们想确定，如果躺下的人不超过 $n/2$ 个，他们能得到的合影最小面积是多少（如果超过 $n/2$ 个男士一起躺在地上，会很奇怪，不是吗？..）

帮助他们实现这个目标。

## 样例 #1
### 输入
```
3
10 1
20 2
30 3
```
### 输出
```
180
```
## 样例 #2
### 输入
```
3
3 1
2 2
4 3
```
### 输出
```
21
```
## 样例 #3
### 输入
```
1
5 10
```
### 输出
```
50
```

### 综合分析与结论
- **思路**：这几道题解的核心思路都是通过枚举最大高度，再针对每种高度情况进行贪心处理。
- **算法要点**：先确定不可行的情况（如有人的$h$和$w$都大于枚举高度），再对不同类型的人（根据$h$和$w$与枚举高度的关系分类）确定是否躺下，对于可躺可不躺的人，按照$w - h$的差值进行贪心选择。
- **解决难点**：难点在于如何在躺下人数不超过$n/2$的限制下，合理地选择躺下的人以达到最小面积。通过枚举高度并分类讨论，有效解决了这个难点。

### 所选的题解
- **作者：communist (5星)**
  - **关键亮点**：思路清晰，代码简洁明了。直接对所有可能的最大高度进行枚举，然后通过分类讨论和排序贪心，计算每种情况下的最小面积。
  - **核心代码**：
```cpp
bool cmp(const int &a, const int &b) {
    return w[a] - h[a] > w[b] - h[b];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &h[i]);
        hh = max(w[i], max(hh, h[i])), sw += w[i];
    }
    for (int maxh = 1; maxh <= hh; maxh++) {
        int cnt = 0, rs = sw;
        vector<int> v;
        for (int i = 1; i <= n; i++) {
            if (w[i] > maxh && h[i] > maxh) {
                cnt = 1e9;
                break;
            } else if (w[i] > maxh && h[i] <= maxh)
                continue;
            else if (w[i] <= maxh && h[i] > maxh) {
                rs += h[i] - w[i];
                cnt++;
            } else if (w[i] > h[i])
                v.push_back(i);
        }
        if (cnt > n / 2)
            continue;
        sort(v.begin(), v.end(), cmp);
        for (int i = 0; i < v.size() && cnt + i < n / 2; i++)
            rs += h[v[i]] - w[v[i]];
        ans = min(ans, rs * maxh);
    }
    printf("%d\n", ans);
    return 0;
}
```
  - **核心实现思想**：通过`cmp`函数对可躺可不躺的人按$w - h$从大到小排序，在`for (int maxh = 1; maxh <= hh; maxh++)`循环中，对每种最大高度情况进行处理，判断可行性并计算最小面积。
- **作者：Happy_mouse (4星)**
  - **关键亮点**：对题目分析详细，将人的情况分为5种，架构清晰，代码注释详细。
  - **核心代码**：
```cpp
bool cmp(int x, int y) {
    return w[x] - h[x] > w[y] - h[y];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, mh = 0, sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i] >> h[i], mh = max({mh, h[i], w[i]}), sum += w[i];
    int hfn = n / 2, ans = 1e9;
    for (int high = 1; high <= mh; high++) {
        int cnt = 0, we = sum, sz = 0;
        for (int i = 1; i <= n; i++) {
            if (h[i] > high && w[i] > high) {
                cnt = n + 1;
                break;
            } else if (h[i] <= high && w[i] > high) continue;
            else if (h[i] > high && w[i] <= high) cnt++, we += h[i] - w[i];
            else if (h[i] < w[i]) a[++sz] = i;
        }
        if (cnt > hfn) continue;
        sort(a + 1, a + sz + 1, cmp);
        for (int i = 1; i <= min(hfn - cnt, sz); i++) we += h[a[i]] - w[a[i]];
        ans = min(ans, we * high);
    }
    cout << ans;
    return 0;
}
```
  - **核心实现思想**：与`communist`思路类似，通过`cmp`函数排序，在`for (int high = 1; high <= mh; high++)`循环中，对每种高度情况按5种分类处理，判断可行性并计算最小面积。

### 最优关键思路或技巧
- **枚举 + 贪心**：通过枚举最大高度，将复杂问题简化为针对每种高度的贪心选择问题。对不同类型的人进行合理分类，针对可躺可不躺的人按$w - h$差值贪心选择，有效解决了在限制条件下求最小面积的问题。

### 可拓展之处
此类题目属于贪心策略结合枚举的问题。类似套路是当直接贪心难以解决问题时，通过枚举某个关键参数，在每个枚举值下进行贪心选择。同类型题通常会在限制条件和贪心策略的设计上有所变化，例如改变限制条件的形式，或者改变贪心选择的依据。

### 洛谷相似题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过贪心策略对物品进行分组，考查贪心思想的应用。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要根据题目条件设计合理的贪心策略来解决问题。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过排序和贪心来优化计算顺序，与本题通过合理排序进行贪心选择有相似之处。 

---
处理用时：31.37秒