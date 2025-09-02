# 题目信息

# Colored Portals

## 题目描述

一条直线上有 $n$ 个城市，这些城市的编号为 $1$ 到 $n$。

传送门被用于在城市间移动，传送门有四种颜色：蓝色，绿色，红色和黄色。每一个城市都有两种颜色的传送门。你可以从城市 $i$ 到城市 $j$，当且仅当这两个城市存在同色的传送门（例如，你可以从有红色和蓝色的传送门的城市到有蓝色和绿色传送门的城市），花费 $|i - j|$ 个硬币。

你的任务是回答 $q$ 个询问：计算城市 $x$ 到城市 $y$ 的最小花费。

## 样例 #1

### 输入

```
2
4 5
BR BR GY GR
1 2
3 1
4 4
1 4
4 2
2 1
BG RY
1 2```

### 输出

```
1
4
0
3
2
-1```

# AI分析结果

### 题解综合分析与结论
这些题解主要围绕如何计算两个城市间的最小花费展开，核心在于处理有相同传送门颜色可直达和无相同颜色需中转的情况。
- **思路对比**：
    - copper_ingot、初星逝者、postpone 和 GY 程袁浩的思路相近，均是预处理每个城市左右最近的可中转城市，然后根据询问的两个城市的传送门颜色情况计算最小花费。
    - 封禁用户采用构图 + 搜索的方法，构建图后用 BFS 或优化后的单源最短路径算法求解。
    - Redamancy_Lydic 则是对 6 种字母组合存出现位置，通过二分查找计算最小花费。
- **算法要点**：
    - 预处理左右最近中转城市时，使用数组或 map 记录信息。
    - 构图时用邻接表表示图，搜索时用队列存储待探索节点。
    - 二分查找时先对数组存极小值防止卡死。
- **解决难点**：
    - 处理无相同颜色的城市间路径时，需找到合适的中转点使花费最小。
    - 多组测试数据时，要注意数组的清空。

### 所选题解
- **copper_ingot（5 星）**
    - **关键亮点**：思路清晰，代码简洁，通过预处理 pre 和 suf 数组，快速计算最小花费，对无解情况也有明确判断。
    - **个人心得**：无
    - **核心代码**：
```cpp
// 转换函数
int get(char b, char c){
    if (b == 'B' && c == 'G') return 1;
    else if (b == 'B' && c == 'R') return 2;
    else if (b == 'B' && c == 'Y') return 3;
    else if (b == 'G' && c == 'R') return 4;
    else if (b == 'G' && c == 'Y') return 5;
    else return 6;
}
// 主函数部分
while (t--){
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++){
        string s; cin >> s;
        char b = s[0], c = s[1];
        a[i] = get(b, c);
    }
    for (int i = 1; i <= n; i++) pre[i] = 0, suf[i] = inf;
    memset(tmp, 0, sizeof(tmp));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= 6; j++){
            if (a[i]!= j && a[i] + j!= 7) pre[i] = max(pre[i], tmp[j]);
        }
        tmp[a[i]] = max(tmp[a[i]], i);
    }
    memset(tmp, 0x7f, sizeof(tmp));
    for (int i = n; i >= 1; i--){
        for (int j = 1; j <= 6; j++){
            if (a[i]!= j && a[i] + j!= 7) suf[i] = min(suf[i], tmp[j]);
        }
        tmp[a[i]] = min(tmp[a[i]], i);
    }
    while (q--){
        int u, v; scanf("%d%d", &u, &v);
        if (u > v) swap(u, v);
        if (a[u] + a[v]!= 7) printf("%d\n", v - u);
        else if (pre[v] > u && suf[u] < v) printf("%d\n", v - u);
        else if (pre[u]!= 0 || suf[v]!= inf){
            if (pre[u] == 0) printf("%d\n", suf[v] * 2 - u - v);
            else if (suf[v] == inf) printf("%d\n", u + v - pre[u] * 2);
            else printf("%d\n", min(suf[v] * 2 - u - v, u + v - pre[u] * 2));
        }
        else puts("-1");
    }
}
```
核心实现思想：先将传送门颜色转换为数字，方便处理。然后预处理每个城市左右最近的有一对相同传送门的城市编号，最后根据询问的两个城市的情况计算最小花费。
- **初星逝者（4 星）**
    - **关键亮点**：思路明确，定义反串概念，通过预处理左右最近中转点，实现 $O(1)$ 询问。
    - **个人心得**：无
    - **核心代码**：
```cpp
// 反串函数
inline string rs(string s){
    if(s=="BG")return "RY";
    if(s=="BR")return "GY";
    if(s=="GR")return "BY";
    if(s=="RY")return "BG";
    if(s=="GY")return "BR";
    if(s=="BY")return "GR";
}
// 主函数部分
while(t--){
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        a[i]=0;
        b[i]=1000000;
        cin >> s[i];
    }
    mp.clear();
    for(int i=1;i<=n;i++){
        for(auto y:v)if(y!=rs(s[i])&&s[i]!=y)a[i]=max(mp[y],a[i]);
        mp[s[i]]=i;
    }
    mp.clear();
    for(int i=n;i>=1;i--){
        for(auto y:v)if(y!=rs(s[i])&&s[i]!=y)b[i]=min(mp[y]==0?1000000:mp[y],b[i]);
        mp[s[i]]=i;
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        if(l>r)swap(l,r);
        if(s[r]!=rs(s[l])){
            cout<<r-l<<endl;
        }
        else{
            int ans=100000000;
            if(a[l]!=0)ans=min(r-a[l]+l-a[l],ans);
            if(b[r]!=1000000)ans=min(b[r]-l+b[r]-r,ans);
            if(a[r]!=0){
                if(a[r]>=l)ans=min(r-l,ans);
                if(a[r]<=l)ans=min(r-a[r]+l-a[r],ans);
            }
            if(b[l]!=1000000){
                if(b[l]<=r)ans=min(r-l,ans);
                if(b[l]>=r)ans=min(b[l]-r+b[l]-l,ans);
            }
            if(ans==100000000)cout<<-1<<endl;
            else cout<<ans<<endl;
        }
    }
}
```
核心实现思想：先定义反串函数，然后预处理每个城市左右最近的中转点，最后根据询问的两个城市是否为反串计算最小花费。
- **postpone（4 星）**
    - **关键亮点**：定义颜色比较枚举类型，使用 map 存颜色到城市的映射，代码可读性好。
    - **个人心得**：此题思路较易想，但实现不简单，用朴素遍历复杂度高，分开从前到后和从后到前遍历可解决。
    - **核心代码**：
```cpp
// 颜色比较函数
ColorCompare check(const string &L, const string &R) {
    if (L == R) {
        return same;
    }
    for (auto i : L) {
        if (R.find(i)!= string::npos) {
            return part;
        }
    }
    return diff;
}
// 解决函数
void solve() {
    int n, q;
    cin >> n >> q;

    vector<string> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector<int> L(n, -1e8), R(n, 1e8);
    for (int i = 0; i < n; i++) {
        for (auto color : g) {
            if (check(color, c[i]) == part and f.contains(color)) {
                L[i] = max(L[i], f[color]);
            }
        }
        f[c[i]] = i;
    }
    f.clear();
    for (int i = n - 1; ~i; i--) {
        for (auto color : g) {
            if (check(color, c[i]) == part and f.contains(color)) {
                R[i] = min(R[i], f[color]);
            }
        }
        f[c[i]] = i;
    }
    f.clear();

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (r < l) {
            swap(l, r);
        }

        if (check(c[l], c[r])!= diff) {
            cout << r - l << "\n";
        } else if (L[l]!= -1e8 or R[l]!= 1e8) {
            cout << min({l - L[l] + r - L[l],
                         R[l] - l + std::abs(r - R[l]),
                         R[r] - r + R[r] - l,
                         r - L[r] + std::abs(L[r] - l)}) << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
}
```
核心实现思想：先定义颜色比较函数，然后预处理每个城市左右最近的中转站，最后根据询问的两个城市的颜色关系计算最小花费。

### 最优关键思路或技巧
- 预处理每个城市左右最近的可中转城市，将复杂的中转问题简化为固定数组的查找，降低时间复杂度。
- 用数字或 map 表示传送门颜色，方便比较和处理。

### 拓展思路
同类型题可能会增加城市维度、传送门颜色种类或边权规则，类似算法套路是预处理关键信息，如最近可达点、颜色组合位置等，再根据询问情况计算结果。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：考察图的最短路计算。
- [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：经典的单源最短路径问题。
- [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：进一步考察单源最短路径算法的优化。

### 个人心得摘录与总结
- postpone：提到此题思路易想但实现难，朴素遍历复杂度高，分开前后遍历可解决，强调了算法优化的重要性。
- Redamancy_Lydic：指出 `memset` 可能带来问题，提醒注意数组初始化。 

---
处理用时：55.14秒