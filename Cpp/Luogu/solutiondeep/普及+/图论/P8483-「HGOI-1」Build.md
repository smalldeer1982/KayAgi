# 题目信息

# 「HGOI-1」Build

## 题目背景

一次旅行，$\text{uuku}$ 到了一个奇怪的小镇。

## 题目描述

这个小镇将要和周围的其他小镇一共 $n$ 个小镇，一起修建一个能**连通**这 $n$ 个小镇，有 $m$ 条高速公路的交通网。其中每条高速公路都将会连接**不同的两个小镇**，即不存在一条高速公路的起点和终点相同。

但高速公路的修建费用是很高的，所以镇长们一致决定将共同承担高速公路的费用，所以他们希望修建的**总费用最小**。

而且由于不同小镇的基础设施建设情况不同，所以每个小镇在修建的费用也不同。经过协商，每条高速公路将由其所连接的两个小镇共同施工。每个小镇负责一半路程。为了同时结束整个施工过程，显然将会有小镇同时进行多条道路的施工，而施工的道路数量越多，所需要花费的价钱就越多。

经过计算，每个小镇施工的花费可以用函数表示，及对于小镇 $i$，有三个参数 $a_i$，$b_i$，$c_i$。对于 $i$ 小镇来说在修建其第 $j$ 条高速时，**这条**高速所需要的花费为 $a_ij^2+b_ij+c_i$。

现在，这些镇长想要 $\text{uuku}$ 给他们提供一个满足要求的**建造方案**，使**总价格最小**。

当然，$\text{uuku}$ 将这个问题交给了你。

## 说明/提示

#### 数据范围
本题采用**捆绑测试**，共有 $6$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。
$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \textbf{特殊限制} \cr\hline
1 & 10 & n,m\le 500  \cr\hline
2 & 20 &  n,m\le 5\times 10^3 \cr\hline
3 & 10 & \text{每个小镇的函数相同}\cr\hline
4 & 20 & a_i=0 \cr\hline
5 & 20 & m=n-1 \cr\hline
6 & 20 & \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$2\le n \le 2 \times 10^5$， $n-1 \le m \le 10^6$，$0 \le a_i$，$b_i$，$c_i \le 10^6$。

数据保证最小价格在 $\tt{long \ long}$ 范围内。

#### 说明

本题有 $\text{spj}$，价格正确可以获得 $30\%$ 的分数。每个 $\text{subtask}$ 取其中所有数据点得分的最小值。

如果你不会构造方案，也请你再输出最小价格后输出 $m$ 行，每行两个 $[1,n]$ 范围内的整数，防止 $\text{spj}$ 出现错误。

本题已添加 hack 数据，为 $\text{subtask7}$，该 $\text{subtask}$ 不计分数，但会影响是否 $\text{AC}$。

## 样例 #1

### 输入

```
4 4
1 2 3
2 3 4
3 4 5
4 5 6```

### 输出

```
114
1 2
1 2
1 3
3 4```

# AI分析结果

### 综合分析与结论
本题目标是构建连通 $n$ 个小镇、含 $m$ 条高速公路的交通网，使总费用最小。大神题解提供了两种思路：
- 思路一：从每个小镇角度出发，用堆维护每个小镇修建下一条公路的代价，取 $2m$ 次最小值，同时满足图连通和无自环条件，通过特定连边方式证明充分性，时间复杂度 $O(m\log n)$。
- 思路二：二分每个点度数的最大值，用二次函数求根公式计算每个点选择次数，判断总度数是否达 $2m$ 及各点度数是否符合条件，复杂度 $O(n\log V + m)$。

### 所选题解
- **星级**：5星
- **关键亮点**：思路清晰，对图连通和无自环条件的证明详细，代码实现规范，还给出赛时爆标思路。

### 重点代码及核心实现思想
```cpp
#define pli pair<ll,int>
const int N = 2e5 + 10;
int n, m, du;
ll ans;
struct P{
    int id, a, b, c, cnt;
    inline void rd(int i){id = i, cin >> a >> b >> c;}
    inline ll get(){cnt++; return (1ll * a * cnt + b) * cnt + c;}
} v[N];
priority_queue<pli, vector<pli>, greater<pli>> q;
pli now;
inline bool cmp(P x, P y){return x.cnt > y.cnt;}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m, du = m << 1;
    for(int i = 1; i <= n; ++i) v[i].rd(i);
    
    for(int i = 1; i <= n; ++i) ans += v[i].get();
    du -= n;
    
    for(int i = 1; i <= n; ++i) q.push(make_pair(v[i].get(), i));
    
    while(du--)
    {
        now = q.top(), q.pop();
        ans += now.first;
        if(v[now.second].cnt == m){v[now.second].cnt++;continue;}
        q.push(make_pair(v[now.second].get(), now.second));        
    }
    for(int i = 1; i <= n; i++) v[i].cnt--; 

    cout<<ans<<'\n';
    
    sort(v + 1, v + n  + 1, cmp);
    int l = 1, r = n;
    while(v[r].cnt == 0) r--;
    while(l < r)
    {
        if(v[1].cnt == 1)break;
        cout<<v[r].id<<' '<<v[l].id<<'\n';
        v[r].cnt--, v[l].cnt--;
        l++;
        if(v[l].cnt <= v[1].cnt && v[1].cnt) l = 1;
        if(!v[r].cnt) r--;
        if(l == r && v[l].cnt)swap(v[l], v[1]), l = 1;
    }
    if(v[1].cnt)
    {
        for(int i = 2; i <= n; i++)
            if(v[i].cnt)
            {
                cout<<v[i].id<<' '<<v[i-1].id<<"\n";
                v[i].cnt--, v[i-1].cnt--;
            }
    }
    return 0;
}
```
核心实现思想：
1. 用结构体 `P` 存储每个小镇的参数和修建次数，`get` 函数计算修建下一条公路的代价。
2. 用优先队列 `q` 维护每个小镇修建下一条公路的最小代价。
3. 先让每个小镇修建一条公路，再取 $2m - n$ 次最小值更新总费用。
4. 最后根据各小镇度数构造连接方案，保证图连通且无自环。

### 最优关键思路或技巧
- 用堆（优先队列）维护每个小镇修建下一条公路的最小代价，高效选择最小费用。
- 从每个小镇角度考虑，将问题转化为度数问题，简化思考。
- 对图连通和无自环条件进行严谨证明，确保方案可行性。

### 可拓展之处
同类型题可考虑不同的费用函数、图的约束条件（如边权限制、特定图结构等）。类似算法套路有贪心算法结合堆优化、二分答案结合数学计算判断可行性。

### 洛谷推荐题目
1. [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)：最小生成树问题，与本题构建连通图的思路相关。
2. [P2872 [USACO07DEC]Building Roads S](https://www.luogu.com.cn/problem/P2872)：同样涉及图的连通性和费用最小化。
3. [P3366 [模板] 最小生成树](https://www.luogu.com.cn/problem/P3366)：经典最小生成树模板题，可加深对图连通和费用优化的理解。

### 个人心得
题解中未包含个人心得。 

---
处理用时：31.82秒