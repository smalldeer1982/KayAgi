# 题目信息

# Chladni Figure

## 题目描述

Inaka has a disc, the circumference of which is $ n $ units. The circumference is equally divided by $ n $ points numbered clockwise from $ 1 $ to $ n $ , such that points $ i $ and $ i + 1 $ ( $ 1 \leq i < n $ ) are adjacent, and so are points $ n $ and $ 1 $ .

There are $ m $ straight segments on the disc, the endpoints of which are all among the aforementioned $ n $ points.

Inaka wants to know if her image is rotationally symmetrical, i.e. if there is an integer $ k $ ( $ 1 \leq k < n $ ), such that if all segments are rotated clockwise around the center of the circle by $ k $ units, the new image will be the same as the original one.

## 说明/提示

The first two examples are illustrated below. Both images become the same as their respective original ones after a clockwise rotation of $ 120 $ degrees around the center.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1147B/e97ded58f64e835700251efbf078bd03afdc1691.png)

## 样例 #1

### 输入

```
12 6
1 3
3 7
5 7
7 11
9 11
11 3
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
9 6
4 5
5 6
7 8
8 9
1 2
2 3
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
10 3
1 2
3 2
7 2
```

### 输出

```
No
```

## 样例 #4

### 输入

```
10 2
1 6
2 7
```

### 输出

```
Yes
```

# AI分析结果

【题目内容（中文重写）】
# 克拉德尼图形

## 题目描述
伊中（Inaka）有一个圆盘，其周长为 $n$ 个单位。圆盘的周长被 $n$ 个点等分为若干部分，这些点按顺时针方向从 $1$ 到 $n$ 编号，使得点 $i$ 和点 $i + 1$（$1 \leq i < n$）相邻，点 $n$ 和点 $1$ 也相邻。

圆盘上有 $m$ 条直线段，这些线段的端点都在上述 $n$ 个点之中。

伊中想知道她的图形是否具有旋转对称性，即是否存在一个整数 $k$（$1 \leq k < n$），使得如果所有线段都绕圆心顺时针旋转 $k$ 个单位，新的图形将与原始图形相同。

## 说明/提示
前两个示例如下图所示。这两个图形绕圆心顺时针旋转 $120$ 度后都与各自的原始图形相同。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1147B/e97ded58f64e835700251efbf078bd03afdc1691.png)

## 样例 #1
### 输入
```
12 6
1 3
3 7
5 7
7 11
9 11
11 3
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
9 6
4 5
5 6
7 8
8 9
1 2
2 3
```
### 输出
```
Yes
```

## 样例 #3
### 输入
```
10 3
1 2
3 2
7 2
```
### 输出
```
No
```

## 样例 #4
### 输入
```
10 2
1 6
2 7
```
### 输出
```
Yes
```

【算法分类】
枚举

【综合分析与结论】
这些题解的核心思路都是通过枚举旋转的单位数（$n$ 的因数），然后检查旋转后的图形是否与原图形重合来判断是否为旋转对称图形。

- **思路对比**：大部分题解直接枚举 $n$ 的因数，然后检查每条线段旋转后是否有对应线段；Piwry 的题解使用 `bitset` 优化，还有一个 $O(m\log n + n)$ 的做法将问题转化为字符串循环节问题；incra 的题解使用字符串哈希的思想。
- **算法要点**：关键在于枚举 $n$ 的因数，以及如何高效判断旋转后的线段是否与原线段对应。
- **解决难点**：处理线段的表示、旋转后的坐标计算以及如何快速判断线段是否对应是主要难点。不同题解采用了不同的数据结构和方法来解决这些问题，如 `vector`、`map`、`set`、`bitset` 等。

【所选题解】
- 作者：是个汉子 (赞：2)，4星。
  - 关键亮点：思路清晰，有小剪枝优化，代码可读性较高。通过枚举 $n$ 的因子和每一位旋转后的情况，判断旋转后和原图形是否重合。
- 作者：wizardMarshall (赞：1)，4星。
  - 关键亮点：思路简洁明了，对注意点有详细说明。通过枚举 $n$ 的因数，使用 `map` 标记线段，判断旋转后线段是否一一对应。
- 作者：绝顶我为峰 (赞：1)，4星。
  - 关键亮点：使用 `set` 维护线段，方便查询端点平移后是否有匹配的线段，时间复杂度分析清晰。

【重点代码】
- **是个汉子的题解**：
```c++
for(int i=1;i<=n/2;i++)
    if(n%i==0) d.push_back(i);
for(int i=1,u,v;i<=m;i++){
    scanf("%d%d",&u,&v);
    if(u>v) swap(u,v);
    p[u].push_back(v-u);
    p[v].push_back((n+u-v-1)%n+1);
}
for(int i=1;i<=n;i++)
    sort(p[i].begin(),p[i].end());
for(int i=0;i<d.size();i++){
    flag=1;
    int now=d[i];
    for(int j=1;j<=n;j++){
        if(p[j].size()!=p[(j+now-1)%n+1].size()){
            flag=0;
            break;
        }
        for(int k=0;k<p[j].size();k++){
            if(p[j][k]!=p[(j+now-1)%n+1][k]){
                flag=0;
                break;
            }
        }
        if(flag==0) break;
    }
    if(flag==1) break;
}
```
核心实现思想：先存储 $n$ 的因数，再存储线段信息并排序。然后枚举因数，对于每个因数检查每个点旋转后的线段是否与原线段对应。

- **wizardMarshall 的题解**：
```c++
void check(int k) {
    for (int i = 1; i <= m; i++) {
        mp[a[i]] = 1;
    }
    for (int i = 1; i <= m; i++) {
        int v1 = (a[i].first + k - 1) % n + 1, v2 = (a[i].second + k - 1) % n + 1;
        if (v1 > v2) swap(v1, v2);
        if (!mp[{v1, v2}]) {
            return;
        }
        mp[{v1, v2}] = 0;
    }
    cout << "Yes";
    exit(0);
}
for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
        check(i);
        if (i * i != n && i != 1) check(n / i);
    }
}
```
核心实现思想：定义 `check` 函数，先标记所有线段，然后检查旋转后的线段是否存在且一一对应。枚举 $n$ 的因数，调用 `check` 函数进行判断。

- **绝顶我为峰的题解**：
```cpp
for(int i=2;i*i<=n;++i)
    if(n%i==0)
    {
        int g=i;
        bool flag=1;
        for(auto i:s)
        {
            pair<int,int> p={(i.first+g-1)%n+1,(i.second+g-1)%n+1};
            if(p.first>p.second)
                p.first^=p.second^=p.first^=p.second;
            if(!s.count(p))
            {
                p={p.second,p.first};
                if(s.count(p))
                    continue;
                flag=0;
                break;
            }
        }
        if(flag)
        {
            puts("YES");
            return 0;
        }
        g=n/i;
        flag=1;
        for(auto i:s)
        {
            pair<int,int> p={(i.first+g-1)%n+1,(i.second+g-1)%n+1};
            if(p.first>p.second)
                p.first^=p.second^=p.first^=p.second;
            if(!s.count(p))
            {
                p={p.second,p.first};
                if(s.count(p))
                    continue;
                flag=0;
                break;
            }
        }
        if(flag)
        {
            puts("YES");
            return 0;
        }
    }
```
核心实现思想：枚举 $n$ 的因数，对于每个因数，遍历所有线段，检查旋转后的线段是否在 `set` 中存在。

【最优关键思路或技巧】
- 利用旋转对称的性质，只枚举 $n$ 的因数，减少不必要的计算。
- 使用合适的数据结构（如 `vector`、`map`、`set`、`bitset` 等）来存储和查询线段信息，提高判断效率。

【可拓展之处】
同类型题可能会有不同的图形或更复杂的旋转规则，可以考虑使用类似的枚举因数和检查对应关系的方法。类似算法套路包括在处理周期性或对称性问题时，先找出周期或对称的规律，然后通过枚举关键参数进行判断。

【推荐题目】
- P1379 八数码难题（搜索相关，可锻炼对状态的判断和枚举）
- P1019 单词接龙（字符串和搜索结合，需要考虑匹配和枚举）
- P1135 奇怪的电梯（模拟和搜索，类似判断状态是否可达）

【个人心得】
- incra：提到赛时代码没有乘上随机权值，加上后被 WA 的概率会低一些，提醒在使用哈希等方法时要注意细节，合理设置参数以提高准确性。
- aaaaaaaawsl：对为什么只需要枚举 $n$ 的因数给出了感性证明，帮助理解问题的本质和算法的合理性。 

---
处理用时：63.64秒