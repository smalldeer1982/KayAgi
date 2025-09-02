# [NERC 2022] BinCoin

## 题目描述

在 BinCoin 公司有 $n$ 名员工，编号从 $1$ 到 $n$。这家公司的隶属关系结构是一棵有根树。换句话说：
- 公司中有一位 CEO——即最高领导。
- 其他每位员工都恰好有一位直接上级。
- 隶属关系结构中没有环。

此外，由于 BinCoin 的 CEO 对所有二进制的东西有着莫名的喜爱，公司的隶属关系结构是一棵**二叉**有根树。这意味着每位员工要么是零位、要么是两位其他员工的直接上级。

在 CEO 看来，在这家公司工作几乎和在矿山里一样危险。因此，员工们有时需要签署免责声明。这个过程按以下方式进行。首先，CEO 拿起记录本，然后递归地执行以下流程：

- 如果持有记录本的员工没有任何下属，他们会在记录本上签名，然后将其交还给他们的上级。如果该员工是 CEO（他没有上级），则流程结束。
- 否则
  - 他们从两名直接下属中随机均匀地选择一位，并将记录本交给他；
  - 当他们收回记录本时，他们自己签名；
  - 然后他们将记录本交给另一位直接下属；
  - 当他们再次收回记录本时，他们将其交还给他们的上级。如果该员工是 CEO（他没有上级），则流程结束。

所有的随机选择都是独立的。

一天，CEO 发现他们记不起隶属关系树了。幸运的是，他们有那个记录本，上面有 $k$ 条记录。每条记录都是一个员工序列，表示他们在记录本上签名的顺序。

请帮助 CEO 恢复这棵隶属关系树。

## 说明/提示

为了适应页面大小，样例中的几行连续的输入被合并到了一行。真实的输入遵循输入格式描述。

翻译由 gemini2.5pro 完成

## 样例 #1

### 输入

```
3 50
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    1 2 3    1 2 3    1 2 3
1 2 3    3 2 1    1 2 3    3 2 1
1 2 3    3 2 1    1 2 3    3 2 1
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    1 2 3    3 2 1    1 2 3
1 2 3    3 2 1    1 2 3    1 2 3
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    3 2 1    1 2 3    3 2 1
1 2 3    3 2 1    3 2 1    1 2 3
1 2 3    3 2 1    1 2 3    3 2 1
3 2 1    3 2 1    1 2 3    1 2 3
3 2 1    3 2 1    ```

### 输出

```
2 -1 2```

## 样例 #2

### 输入

```
5 60
2 4 3 5 1    1 5 2 4 3    1 5 2 4 3
1 5 2 4 3    1 5 3 4 2    1 5 3 4 2
1 5 3 4 2    1 5 3 4 2    1 5 3 4 2
3 4 2 5 1    2 4 3 5 1    1 5 2 4 3
3 4 2 5 1    2 4 3 5 1    2 4 3 5 1
1 5 2 4 3    3 4 2 5 1    3 4 2 5 1
1 5 2 4 3    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    3 4 2 5 1    1 5 3 4 2
1 5 2 4 3    1 5 3 4 2    1 5 2 4 3
2 4 3 5 1    2 4 3 5 1    2 4 3 5 1
2 4 3 5 1    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    1 5 2 4 3    3 4 2 5 1
1 5 3 4 2    3 4 2 5 1    3 4 2 5 1
1 5 2 4 3    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    2 4 3 5 1    2 4 3 5 1
1 5 2 4 3    1 5 2 4 3    1 5 2 4 3
1 5 2 4 3    1 5 2 4 3    3 4 2 5 1
3 4 2 5 1    3 4 2 5 1    1 5 2 4 3
1 5 3 4 2    1 5 3 4 2    2 4 3 5 1
3 4 2 5 1    1 5 2 4 3    3 4 2 5 1```

### 输出

```
5 4 4 5 -1```

# 题解

## 作者：Yifeng0812 (赞：0)

## 核心思路

解题的关键在于签名过程的一个核心性质：任何一个子树（即一个上级和他的所有下属）的成员，在每一次签名生成的最终序列里，总是作为一个连续的、不被外人分开的区间出现。

利用这个特点，我们可以反向推出树的结构。

## 算法步骤

第一步就是识别所有子树。

以第一个签名记录作为基准。遍历其中所有的连续子序列 	$[l \dots r]$。

对于每个子序列，检查其中的员工集合在所有 $k$ 个签名记录中是否都保持连续。

如果一个序列在所有记录中都保持连续，我们就标记它对应一个合法的子树。就用一个布尔数组 $subtree[l][r]$ 来记录。

## 递归建树

我们现在知道哪些员工集合是子树。对于任意一个代表子树的区间 $[l, r]$，其根节点 $u$ 是唯一能将该区间分割成两个更小的合法子树（或空区间）的节点。
从整个员工序列 $[0, n-1]$ 开始，找到它的根节点（即 CEO）。

然后，对 CEO 分割出的左右两个子区间递归地执行相同的操作，找它们的根节点（即 CEO 的下属），并以此类推，直到确定所有父子关系。
使用记忆化来优化寻找根节点的过程，避免重复计算。

## AC code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

// 寻找 [l, r] 段对应子树的根节点
int find_root(int l, int r, int n, const vector<vector<int>>& records, const vector<char>& subtrees, map<pair<int, int>, int>& memo)
{
    if (l > r) 
	{
		return 0;
	}
    if (l == r) 
	{
		return records[0][l];
	}
    if (memo.count({l, r})) 
	{
		return memo.at({l, r});
	}
    for (int i = l; i <= r; ++i) 
	{
        int u = records[0][i];
        // 检查 u 是否能将 [l,r] 分割成两个合法的子树（或空/叶子）
        bool leftt = (i == l) ? true : subtrees[l * n + (i - 1)];
        bool rightt = (i == r) ? true : subtrees[(i + 1) * n + r];
        if (leftt && rightt)
		{
            return memo[{l, r}] = u;// 找到根，记忆化并返回
        }
    }
    return -1;// 理论上对于合法的子树段不会发生
}

// 递归构建树
void build(int l, int r, int n, const vector<vector<int>>& records, const vector<char>& subtrees, vector<int>& parent, map<pair<int, int>, int>& memo)
{
    if (l >= r) 
	{
		return;
	}
    int root = find_root(l, r, n, records, subtrees, memo);
    if (root == -1) 
	{
		return;
	}
    int idx = -1;
    for(int i = l; i <= r; ++i) 
	{
        if (records[0][i] == root) 
		{
            idx = i;
            break;
        }
    }
    // 递归构建左子树
    if (idx > l) 
	{
        int left = find_root(l, idx - 1, n, records, subtrees, memo);
        if (left != -1) 
		{
            parent[left] = root;
            build(l, idx - 1, n, records, subtrees, parent, memo);
        }
    }
    // 递归构建右子树
    if (idx < r) 
	{
        int right = find_root(idx + 1, r, n, records, subtrees, memo);
        if (right != -1) 
		{
            parent[right] = root;
            build(idx + 1, r, n, records, subtrees, parent, memo);
        }
    }
}

signed main() //使用signed纯纯是为了帅，本质上与int没有任何区别 
{
	// 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    // 存储所有记录和每个节点在各记录中的位置
    vector<vector<int>> records(k, vector<int>(n));
    vector<vector<int>> pos(k, vector<int>(n + 1));
    for (int i = 0; i < k; ++i) 
	{
        for (int j = 0; j < n; ++j) 
		{
            cin >> records[i][j];
            pos[i][records[i][j]] = j;
        }
    }
    // 使用一维数组 vector<char> 模拟二维数组，更快
    // is_subtree_flat[l * n + r] 表示 records[0][l...r] 是否是子树
    vector<char> subtrees(n * n, 0);
    // 遍历每个记录，用她来排除掉不连续的段
    for (int l = 0; l < n; ++l) 
	{
        set<int> group;
        for (int r = l; r < n; ++r) 
		{
            group.insert(records[0][r]);
            // 如果这个段已经被之前的记录排除了，就没必要再检查了
            if (group.size() % 2 == 0) 
			{
                continue;
            }
            bool valid = true;
            for (int j = 0; j < k; ++j) 
			{
                int minp = n, maxp = -1;
                for (int node : group) 
				{
					// 更新当前记录j中，该段节点的位置范围
                    minp = min(minp, pos[j][node]);
                    maxp = max(maxp, pos[j][node]);
                }
                if (maxp - minp + 1 != group.size()) 
				{
					// 如果范围大小不等于段长，则它不连续
                    valid = false;
                    break; 
                }
            }
            if (valid) 
			{
                subtrees[l * n + r] = 1;
            }
        }
    }
    vector<int> parent(n + 1, 0);
    map<pair<int, int>, int> memo;// 用于记忆化 find_root
    // 从整个序列开始构建
    int ceo = find_root(0, n - 1, n, records, subtrees, memo);
    if (ceo != -1) parent[ceo] = -1;
    build(0, n - 1, n, records, subtrees, parent, memo);
    // 输出结果
    for (int i = 1; i <= n; ++i) 
	{
        cout << parent[i] << (i == n ? "" : " ");
    }
    cout << endl;
    return 0;
}
```

---

