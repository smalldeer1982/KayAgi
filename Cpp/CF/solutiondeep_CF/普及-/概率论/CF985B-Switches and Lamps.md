# 题目信息

# Switches and Lamps

## 题目描述

You are given $ n $ switches and $ m $ lamps. The $ i $ -th switch turns on some subset of the lamps. This information is given as the matrix $ a $ consisting of $ n $ rows and $ m $ columns where $ a_{i,j}=1 $ if the $ i $ -th switch turns on the $ j $ -th lamp and $ a_{i,j}=0 $ if the $ i $ -th switch is not connected to the $ j $ -th lamp.

Initially all $ m $ lamps are turned off.

Switches change state only from "off" to "on". It means that if you press two or more switches connected to the same lamp then the lamp will be turned on after any of this switches is pressed and will remain its state even if any switch connected to this lamp is pressed afterwards.

It is guaranteed that if you push all $ n $ switches then all $ m $ lamps will be turned on.

Your think that you have too many switches and you would like to ignore one of them.

Your task is to say if there exists such a switch that if you will ignore (not use) it but press all the other $ n-1 $ switches then all the $ m $ lamps will be turned on.

## 样例 #1

### 输入

```
4 5
10101
01000
00111
10000
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 5
10100
01000
00110
00101
```

### 输出

```
NO
```

# AI分析结果

### 题目中文重写
## 开关与灯

### 题目描述
你有 $n$ 个开关和 $m$ 盏灯。第 $i$ 个开关可以打开部分灯，这些信息用一个 $n$ 行 $m$ 列的矩阵 $a$ 表示，其中若 $a_{i,j}=1$，则表示第 $i$ 个开关可以打开第 $j$ 盏灯；若 $a_{i,j}=0$，则表示第 $i$ 个开关与第 $j$ 盏灯没有连接。

初始时，所有 $m$ 盏灯都是关闭的。

开关状态只能从“关闭”变为“打开”。这意味着，如果有两个或更多连接到同一盏灯的开关被按下，那么在任何一个开关被按下后，灯就会被打开，并且即使之后再按下任何连接到这盏灯的开关，灯的状态也会保持不变。

保证当按下所有 $n$ 个开关时，所有 $m$ 盏灯都会被打开。

你认为开关太多了，想要忽略其中一个。

你的任务是判断是否存在这样一个开关，如果你忽略（不使用）它，但按下其他 $n - 1$ 个开关，所有 $m$ 盏灯仍然可以被打开。

### 样例 #1
#### 输入
```
4 5
10101
01000
00111
10000
```
#### 输出
```
YES
```

### 样例 #2
#### 输入
```
4 5
10100
01000
00110
00101
```
#### 输出
```
NO
```

### 题解综合分析与结论
- **思路对比**：大部分题解（如 ztyo_zysclown、AutumnKite 等）思路一致，先统计每盏灯连接的开关数量，再枚举开关，判断去掉该开关后是否有灯无法被打开。望月Asta 的题解使用 `std::bitset` 优化位运算，直接模拟枚举删除串的过程。Creative_sad_yosgic 提出找“无用灯”的思路。
- **算法要点**：多数题解核心是统计每盏灯的开关连接数，时间复杂度为 $O(n^2)$；望月Asta 题解使用 `std::bitset` 优化，时间复杂度为 $O(\frac{n^2 m}{w})$。
- **解决难点**：主要难点在于避免 $O(n^3)$ 的枚举复杂度，多数题解通过统计每盏灯连接的开关数解决；望月Asta 题解用 `std::bitset` 优化位运算。

### 评分较高的题解
1. **AutumnKite（4星）**
    - **关键亮点**：思路清晰，对时间复杂度有明确分析，代码使用 `register` 关键字提高效率。
    - **核心代码**：
```cpp
const int N = 2005;
int n, m, cnt[N];
char a[N][N];
int main(){
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            while (!isdigit(a[i][j] = getchar()));
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            cnt[j] += a[i][j] ^ '0'; 
    for (register int i = 1; i <= n; ++i){
        register bool bo = true;
        for (register int j = 1; j <= m; ++j)
            if (a[i][j] == '1' && cnt[j] == 1) bo = false; 
        if (bo) return printf("YES"), 0;
    }
    return printf("NO"), 0;
}
```
核心实现思想：先统计每盏灯连接的开关数，再枚举开关，若去掉该开关后有灯连接的开关数为 1，则该开关不能去掉。
2. **togeth1（4星）**
    - **关键亮点**：思路简洁明了，代码可读性高。
    - **核心代码**：
```cpp
int n,m,sum[2010];
char a[2010][2010];
int main() {
    cin>>n>>m;
    for(int i=1; i<=n; i++) 
        for(int j=1; j<=m; j++)
            cin>>a[i][j],sum[j] += a[i][j] - '0';
    for(int i=1; i<=n; i++){
        bool flag = 0;
        for(int j=1; j<=m; j++)
            if(a[i][j] == '1' && sum[j] == 1) flag = 1;
        if(!flag) {cout<<"YES"; return 0;}
    }
    cout<<"NO";
    return 0;
}
```
核心实现思想：统计每盏灯连接的开关数，枚举开关，若去掉该开关后有灯连接的开关数为 1，则该开关不能去掉。
3. **xvl_（4星）**
    - **关键亮点**：思路清晰，对关键数组的作用有明确注释。
    - **核心代码**：
```cpp
int n, m;
char a[2005][2005];
int cnt[2005]; 
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == '1') cnt[j]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        bool flag = 0;
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '1') {
                if (cnt[j] == 1) flag = 1; 
            }
        }
        if (!flag) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
```
核心实现思想：统计每盏灯连接的开关数，枚举开关，若去掉该开关后有灯连接的开关数为 1，则该开关不能去掉。

### 最优关键思路或技巧
- 统计每盏灯连接的开关数，避免 $O(n^3)$ 的枚举复杂度，将时间复杂度优化到 $O(n^2)$。
- 使用 `std::bitset` 优化位运算，可进一步优化时间复杂度。

### 可拓展之处
同类型题可能会增加开关状态变化规则、灯的状态变化规则等。类似算法套路可用于解决矩阵相关的枚举优化问题，通过统计某些信息减少不必要的枚举。

### 推荐洛谷题目
1. [P1161 开灯](https://www.luogu.com.cn/problem/P1161)
2. [P2241 统计方形（数据加强版）](https://www.luogu.com.cn/problem/P2241)
3. [P1540 [NOIP2010 提高组] 机器翻译](https://www.luogu.com.cn/problem/P1540)

### 个人心得摘录与总结
题解中未包含个人心得。 

---
处理用时：34.85秒