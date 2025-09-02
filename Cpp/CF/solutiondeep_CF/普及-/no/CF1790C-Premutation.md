# 题目信息

# Premutation

## 题目描述

A sequence of $ n $ numbers is called permutation if it contains all integers from $ 1 $ to $ n $ exactly once. For example, the sequences \[ $ 3, 1, 4, 2 $ \], \[ $ 1 $ \] and \[ $ 2,1 $ \] are permutations, but \[ $ 1,2,1 $ \], \[ $ 0,1 $ \] and \[ $ 1,3,4 $ \] — are not.

Kristina had a permutation $ p $ of $ n $ elements. She wrote it on the whiteboard $ n $ times in such a way that:

- while writing the permutation at the $ i $ -th ( $ 1 \le i \le n) $ time she skipped the element $ p_i $

 So, she wrote in total $ n $ sequences of length $ n-1 $ each.For example, suppose Kristina had a permutation $ p $ = $ [4,2,1,3] $ of length $ 4 $ . Then she did the following:

1. Wrote the sequence $ [2, 1, 3] $ , skipping the element $ p_1=4 $ from the original permutation.
2. Wrote the sequence $ [4, 1, 3] $ , skipping the element $ p_2=2 $ from the original permutation.
3. Wrote the sequence $ [4, 2, 3] $ , skipping the element $ p_3=1 $ from the original permutation.
4. Wrote the sequence $ [4, 2, 1] $ , skipping the element $ p_4=3 $ from the original permutation.

You know all $ n $ of sequences that have been written on the whiteboard, but you do not know the order in which they were written. They are given in arbitrary order. Reconstruct the original permutation from them.

For example, if you know the sequences $ [4, 2, 1] $ , $ [4, 2, 3] $ , $ [2, 1, 3] $ , $ [4, 1, 3] $ , then the original permutation will be $ p $ = $ [4, 2, 1, 3] $ .

## 说明/提示

The first test case is described in the problem statement.

In the second test case, the sequences are written in the correct order.

## 样例 #1

### 输入

```
5
4
4 2 1
4 2 3
2 1 3
4 1 3
3
2 3
1 3
1 2
5
4 2 1 3
2 1 3 5
4 2 3 5
4 1 3 5
4 2 1 5
4
2 3 4
1 3 4
1 2 3
1 2 4
3
2 1
1 3
2 3```

### 输出

```
4 2 1 3 
1 2 3 
4 2 1 3 5 
1 2 3 4 
2 1 3```

# AI分析结果

### 题目内容
# 排列

## 题目描述
一个由 $n$ 个数字组成的序列如果恰好包含从 $1$ 到 $n$ 的所有整数各一次，则称其为排列。例如，序列 \[ 3, 1, 4, 2 \]、\[ 1 \] 和 \[ 2,1 \] 是排列，而 \[ 1,2,1 \]、\[ 0,1 \] 和 \[ 1,3,4 \] 不是排列。

克里斯蒂娜有一个由 $n$ 个元素组成的排列 $p$。她在白板上写了 $n$ 次这个排列，方式如下：
- 在第 $i$ 次（$1 \leq i \leq n$）书写时，她跳过了元素 $p_i$。

所以，她总共写了 $n$ 个长度为 $n - 1$ 的序列。例如，假设克里斯蒂娜有一个长度为 $4$ 的排列 $p = [4,2,1,3]$。那么她做了以下操作：
1. 写下序列 $[2, 1, 3]$，从原始排列中跳过元素 $p_1 = 4$。
2. 写下序列 $[4, 1, 3]$，从原始排列中跳过元素 $p_2 = 2$。
3. 写下序列 $[4, 2, 3]$，从原始排列中跳过元素 $p_3 = 1$。
4. 写下序列 $[4, 2, 1]$，从原始排列中跳过元素 $p_4 = 3$。

你知道写在白板上的所有 $n$ 个序列，但不知道它们的书写顺序。它们是按任意顺序给出的。从这些序列中重构原始排列。

例如，如果你知道序列 $[4, 2, 1]$、$[4, 2, 3]$、$[2, 1, 3]$、$[4, 1, 3]$，那么原始排列将是 $p = [4, 2, 1, 3]$。

## 说明/提示
第一个测试用例在题目描述中给出。
在第二个测试用例中，序列是按正确顺序书写的。

## 样例 #1
### 输入
```
5
4
4 2 1
4 2 3
2 1 3
4 1 3
3
2 3
1 3
1 2
5
4 2 1 3
2 1 3 5
4 2 3 5
4 1 3 5
4 2 1 5
4
2 3 4
1 3 4
1 2 3
1 2 4
3
2 1
1 3
2 3
```
### 输出
```
4 2 1 3 
1 2 3 
4 2 1 3 5 
1 2 3 4 
2 1 3
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕如何从给定的 $n$ 个长度为 $n - 1$ 的无序序列中还原出原始排列展开。不同题解思路差异较大，有的利用数据出现次数特点，有的采用拓扑排序，有的使用贪心策略。

### 所选的题解
- **作者：LegendaryGrandmaster（5星）**
  - **关键亮点**：采用贪心策略，通过给每个数赋予权值并按权值排序来重构原始排列，思路新颖且代码简洁高效。
  - **重点代码**：
```cpp
struct node{
    int id,x;
}a[200001];
bool cmp(node a,node b)
{
    return a.x>b.x;
}
int main()
{
    int t;
    cin>>t;
    while(t--){
        memset(a,0,sizeof(a));
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            for(int j=1;j<n;j++){
                int x;
                cin>>x;
                a[x].x+=n-j+1;
                a[x].id=x;
            }
        }
        sort(a+1,a+1+n,cmp);
        for(int i=1;i<=n;i++)cout<<a[i].id<<' ';
        puts("");
    }
}
```
  - **核心实现思想**：定义结构体 `node` 记录数的值 `id` 和权值 `x`，遍历输入序列计算每个数的权值，权值计算方式为每次出现时加上 $n - j + 1$，最后按权值从大到小排序并输出数的值。
- **作者：Otue（4星）**
  - **关键亮点**：通过分析原序列第一个数在新序列中的出现规律，利用桶记录新序列第一个位置数字的出现次数，快速确定原序列第一个数，进而还原整个序列，思路清晰易懂。
  - **重点代码**：
```cpp
const int N = 105, mod = 1e8;
#define int long long
int T, n, a[N][N];
int tong[N];

signed main() {
    cin >> T;
    while (T--) {  
        memset(tong, 0, sizeof tong);
        cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < n; j++) {
                int c;
                cin >> c;
                a[i][j] = c;
            }
        }
        for (int i = 1; i <= n; i++) tong[a[i][1]]++;  
        int id = 0;
        for (int i = 1; i <= n; i++) {
            if (tong[i] == n - 1) id = i;  
        }
        int t = 0, x = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i][1]!= id) t = i, x = a[i][1];
        }
        cout << id << ' ';  
        for (int i = 1; i <= n - 1; i++) {
            cout << a[t][i] << ' ';
        }
        puts("");
    }
}
```
  - **核心实现思想**：开数组 `tong` 作为桶，统计新序列第一个位置每个数出现的次数，找到出现 $n - 1$ 次的数 `id` 作为原序列第一个数，再找到第一个位置不是 `id` 的序列，将 `id` 与该序列拼接得到原序列。
- **作者：云裳（4星）**
  - **关键亮点**：与 Otue 思路类似，同样抓住原排列第一个数字在新序列中的出现特征来求解，代码简洁明了，逻辑清晰。
  - **重点代码**：
```cpp
void solve() {
    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        ll a[110][110], buc[110]; 
        for(int i=1;i<=100;i++) buc[i] = 0; 
        for(int i=1;i<=n;i++)  for(int j=1;j<n;j++)  cin >> a[i][j];
        ll first, id; 
        for(int i=1;i<=n;i++) {
            buc[a[i][1]]++;
            if (buc[a[i][1]] > 1) { 
                first = a[i][1];
                break;
            }
        }
        for(int i=1;i<=n;i++) if (a[i][1]!= first) { 
            id = i;
            break;
        }
        cout << first << " ";                    
        for(int i=1;i<n;i++) cout << a[id][i] << " "; 
        cout << "\n";
    }
}
```
  - **核心实现思想**：用数组 `buc` 记录新序列第一个位置每个数出现的次数，找到出现次数大于1的数 `first` 作为原序列第一个数，再找到第一个位置不是 `first` 的序列，输出 `first` 并拼接该序列得到原序列。

### 最优关键思路或技巧
观察原排列中元素在生成序列中的位置特征，如原排列第一个元素在生成的 $n$ 个序列中，有 $n - 1$ 个序列其第一个位置是该元素，利用此特征可快速确定原排列第一个元素，进而还原整个排列。或者像 LegendaryGrandmaster 通过给元素赋予权值并排序的方式巧妙还原排列。

### 可拓展思路
此类题目属于序列重构类型，类似的题目可能会改变生成子序列的规则，比如按不同的跳跃间隔生成子序列等。解题时需仔细分析原序列与子序列之间元素的对应关系和分布规律。

### 洛谷题目推荐
 - [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：通过归并排序等方法统计逆序对数量，与本题类似，都涉及对序列元素关系的分析处理。
 - [P1083 借教室](https://www.luogu.com.cn/problem/P1083)：可通过二分查找和差分的方法解决，同样需要分析数据间的逻辑关系，类似本题对原序列与生成序列关系的分析。
 - [P1130 红牌](https://www.luogu.com.cn/problem/P1130)：利用模拟和贪心策略解决问题，与本题部分题解思路类似，通过分析问题特点找到解决方法。 

---
处理用时：59.25秒