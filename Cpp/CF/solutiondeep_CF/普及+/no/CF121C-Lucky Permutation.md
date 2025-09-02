# 题目信息

# Lucky Permutation

## 题目描述

Petya loves lucky numbers. Everybody knows that lucky numbers are positive integers whose decimal representation contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

One day Petya dreamt of a lexicographically $ k $ -th permutation of integers from $ 1 $ to $ n $ . Determine how many lucky numbers in the permutation are located on the positions whose indexes are also lucky numbers.

## 说明/提示

A permutation is an ordered set of $ n $ elements, where each integer from $ 1 $ to $ n $ occurs exactly once. The element of permutation in position with index $ i $ is denoted as $ a_{i} $ ( $ 1<=i<=n $ ). Permutation $ a $ is lexicographically smaller that permutation $ b $ if there is such a $ i $ ( $ 1<=i<=n $ ), that $ a_{i}&lt;b_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ a_{j}=b_{j} $ . Let's make a list of all possible permutations of $ n $ elements and sort it in the order of lexicographical increasing. Then the lexicographically $ k $ -th permutation is the $ k $ -th element of this list of permutations.

In the first sample the permutation looks like that:

1 2 3 4 6 7 5

The only suitable position is 4.

In the second sample the permutation looks like that:

2 1 3 4

The only suitable position is 4.

## 样例 #1

### 输入

```
7 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 7
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 幸运排列

## 题目描述
Petya 喜欢幸运数字。众所周知，幸运数字是指十进制表示中仅包含幸运数字 4 和 7 的正整数。例如，47、744、4 是幸运数字，而 5、17、467 不是。
有一天，Petya 梦到了从 1 到 n 的整数的字典序第 k 个排列。确定在这个排列中，位于索引也是幸运数字的位置上的幸运数字有多少个。

## 说明/提示
一个排列是一个由 n 个元素组成的有序集合，其中从 1 到 n 的每个整数恰好出现一次。排列中位置索引为 i 的元素表示为 \(a_{i}\)（\(1\leq i\leq n\)）。排列 a 在字典序上小于排列 b，如果存在这样的 i（\(1\leq i\leq n\)），使得 \(a_{i}<b_{i}\)，并且对于任何 j（\(1\leq j<i\)），都有 \(a_{j}=b_{j}\)。让我们列出所有可能的 n 个元素的排列，并按字典序递增的顺序对其进行排序。那么字典序第 k 个排列就是这个排列列表中的第 k 个元素。
在第一个样例中，排列如下：
1 2 3 4 6 7 5
唯一合适的位置是 4。
在第二个样例中，排列如下：
2 1 3 4
唯一合适的位置是 4。

## 样例 #1
### 输入
```
7 4
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4 7
```
### 输出
```
1
```

### 算法分类
数学（结合逆康托展开和数位DP等数学方法）

### 综合分析与结论
所有题解都基于 \(n\) 很大（\(10^9\)）但 \(k\) 规模相对小（\(10^9\) 远小于 \(n\) 的全排列数）这一特点，发现排列前面大部分位置 \(a_i = i\)，仅后面少数位置（不超过13个）会变化。对于前面部分，通过数位DP或爆搜计算幸运数字个数；对于后面变化部分，利用逆康托展开计算排列并统计幸运数字个数。不同题解在具体实现细节上有差异，如数位DP的状态定义和转移方程、逆康托展开的实现方式等。

### 所选的题解
- **作者：wxzzzz (5星)**
    - **关键亮点**：思路清晰，结合数位DP和逆康托展开两种方法，对 \(a_{pos + 1}\sim a_n\) 暴力逆康托展开求幸运数个数，对 \(a_1\sim a_{pos}\) 数位DP求 \(1\sim pos\) 中的幸运数个数，还给出了数位DP状态转移方程。
    - **重点代码核心思想**：先预处理阶乘，通过逆康托展开确定变化部分的排列，再用数位DP计算固定部分的幸运数字个数，最后累加两部分结果。
    - **核心代码片段**：
```cpp
int main() {
    p[0] = 1;
    for (int i = 1; i <= 13; i++)
        p[i] = p[i - 1] * i;
    cin >> n >> m;
    if (!limit()) {
        cout << "-1";
        return 0;
    }
    m--;
    for (int i = 1; i <= 13; i++) {
        pos = n - i;
        if (p[i] > m)
            break;
    }
    for (int i = pos + 1; i <= n; i++) {
        v.push_back(i);
        s.push_back(m / p[n - i]), m %= p[n - i];
    }
    int now = pos;
    for (auto i : s) {
        int val = v[i];
        v.erase(lower_bound(v.begin(), v.end(), val));
        if (check(++now) && check(val))
            ans++;
    }
    int dig = 0, sum = 0, d[15];
    f[1][4] = f[1][7] = 1;
    for (int i = 2; i <= 10; i++) {
        f[i][4] = f[i - 1][4] + f[i - 1][7];
        f[i][7] = f[i - 1][4] + f[i - 1][7];
    }
    pos++;
    while (pos) {
        d[++dig] = pos % 10;
        pos /= 10;
    }
    for (int i = 1; i < dig; i++)
        for (int j = 0; j <= 9; j++)
            sum += f[i][j];
    for (int i = dig; i >= 1; i--) {
        for (int j = 0; j < d[i]; j++)
            sum += f[i][j];
        if (d[i]!= 4 && d[i]!= 7)
            break;
    }
    ans += sum;
    cout << ans;
    return 0;
}
```
- **作者：lfxxx (4星)**
    - **关键亮点**：代码简洁，逻辑清晰，通过预处理阶乘，利用逆康托展开处理后面变化部分，数位DP处理前面固定部分，状态定义和转移较为清晰。
    - **重点代码核心思想**：预处理阶乘，确定固定部分和变化部分，逆康托展开得到变化部分排列，数位DP计算固定部分幸运数字个数并累加。
    - **核心代码片段**：
```cpp
signed main(){
    cin>>n>>k;
    k--;
    fac[0]=1;
    for(int i=1;i<=13;i++) fac[i]=fac[i-1]*i;
    for(int i=1;i<=13;i++){
        pre=n-i;
        if(fac[i]>k) break;
    }
    if(n<=13&&k>=fac[n]){
        cout<<"-1\n";
        return 0;
    }
    for(int i=pre+1;i<=n;i++) D.push_back(i),f.push_back(k/fac[n-i]),k%=fac[n-i];
    for(int x:f){
        a.push_back(D[x]);
        D.erase(find(D.begin(),D.end(),a.back()));
    }
    int tot=pre;
    while(pre>0) dight.push_back(pre%10),pre/=10;
    memset(dp,-1,sizeof(dp));
    int ans=(tot!=0?dfs(dight.size()-1,true,true)-1:0);
    for(int x:a) tot++,ans+=(check(tot)&check(x));
    cout<<ans<<'\n';
    return 0;
}
```
- **作者：attack (4星)**
    - **关键亮点**：思路直接，利用逆康托展开和爆搜两种简单易懂的方法分别处理变化部分和固定部分，代码结构清晰。
    - **重点代码核心思想**：预处理阶乘确定变化部分，爆搜计算固定部分幸运数字个数，逆康托展开得到变化部分排列并统计幸运数字个数。
    - **核心代码片段**：
```cpp
signed main() {
    N = read(); K = read() - 1;
    int T = -1; fac[0] = 1;
    for(int i = 1; i <= N;i++) {
        fac[i] = i * fac[i - 1];
        res.push_back(N - i + 1);
        if(fac[i] > K) {T = i; break;}
    }
    if(T == -1) {puts("-1"); return 0;}
    dfs(0, N - T);
    for(int i = T; i >= 1; i--) {
        int t = find(K / fac[i - 1]), pos = N - i + 1;
        if(check(pos) && check(t)) ans++;
        K = K % fac[i - 1];
    }
    cout << ans;
    return 0;
}
```

### 最优关键思路或技巧
利用阶乘增长迅速以及 \(k\) 相对较小的特点，将排列分成前面固定部分（\(a_i = i\)）和后面变化部分。对于固定部分，通过数位DP（或爆搜）统计幸运数字个数；对于变化部分，运用逆康托展开确定排列并统计幸运数字个数。这种分治思想简化了问题，避免对大规模全排列的直接计算。

### 可拓展之处
同类型题可涉及不同数字定义下的排列问题，或对排列有其他特殊要求，类似算法套路是分析数据规模特点，利用排列性质（如康托展开相关性质），结合合适的计数方法（如数位DP、搜索等）解决问题。

### 洛谷题目推荐
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及到排列与逆康托展开的应用。
- [P4931 情侣？给我烧了！（加强版）](https://www.luogu.com.cn/problem/P4931)：考查组合数学与排列相关知识。
- [P2676 [USACO07DEC]Bookshelf B](https://www.luogu.com.cn/problem/P2676)：结合了贪心和数学知识，与本题利用数学性质优化问题有相似之处。 

---
处理用时：87.17秒