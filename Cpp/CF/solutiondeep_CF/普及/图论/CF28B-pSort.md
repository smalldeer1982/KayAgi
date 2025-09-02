# 题目信息

# pSort

## 题目描述

给定一个长度为 $n$ 的数列 $\{a_n\}$，初始时 $\{a_n\} = \{1, 2, \dots, n\}$。位置 $i$ 上的数可以和位置 $i \pm d_i$ 上的数交换。给定一个 $1 \sim n$ 的全排列，问初始的数列可否交换成给定的形式。

## 说明/提示

$1 \le n \le 100$

## 样例 #1

### 输入

```
5
5 4 3 2 1
1 1 1 1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
7
4 3 5 1 2 7 6
4 6 6 1 6 6 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
7
4 2 5 1 3 7 6
4 6 6 1 6 6 1
```

### 输出

```
YES
```

# AI分析结果

### 题解综合分析与结论
这些题解主要围绕判断初始数列能否通过给定交换规则变换成目标排列展开，采用了并查集、Floyd算法和DFS三种主要方法。
- **思路对比**
    - **并查集**：将能相互交换的位置合并到一个集合，最后检查初始位置和目标位置是否在同一集合。
    - **Floyd算法**：将问题转化为图的连通性问题，通过动态规划标记两点间是否可达。
    - **DFS**：构建图后，遍历图标记连通块，判断初始位置和目标位置是否在同一连通块。
- **算法要点**
    - **并查集**：实现查找和合并操作，时间复杂度$O(n\alpha(n))$。
    - **Floyd算法**：三重循环更新可达性矩阵，时间复杂度$O(n^3)$。
    - **DFS**：递归遍历图，每个节点最多访问一次，时间复杂度$O(n)$。
- **解决难点**
    - **并查集**：需要想到用集合来表示可交换位置的关系。
    - **Floyd算法**：理解动态规划的思想和位运算在标记可达性中的应用。
    - **DFS**：构建图和标记连通块。

### 高评分题解
- **作者：赤霞QvQ（5星）**
    - **关键亮点**：思路清晰，详细证明了相邻元素可交换能得到全排列的结论，代码实现简洁易懂。
    - **个人心得**：一开始没想到用并查集，看到算法标签才顿悟。
```cpp
int father(int x) {
    if(fa[x]!=x) fa[x]=father(fa[x]);
    return fa[x];
}

void un(int x,int y) {
    int u=father(x),v=father(y);
    if(u!=v) fa[u]=v; 
}

int main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>f[i];
        fa[i]=i;
    }
    for(int i=1;i<=n;i++) {
        cin>>d[i];
        if(i>d[i]) un(i,i-d[i]);
        if(i+d[i]<=n) un(i,i+d[i]);
    }
    for(int i=1;i<=n;i++) {
        if(father(i)!=father(f[i])) {
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
```
- **作者：PDY08（4星）**
    - **关键亮点**：采用Floyd算法求解，详细解释了算法原理和位运算的应用。
```cpp
int main() {
    int n, d;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) b[i][i] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> d;
        if (i - d >= 1) b[i][i - d] = 1;
        if (i + d <= n) b[i][i + d] = 1; 
    } 
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                b[i][j] |= (b[i][k] & b[j][k]) | (b[i][k] & b[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!b[i][a[i]]) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
    return 0;
} 
```
- **作者：Error_Eric（4星）**
    - **关键亮点**：使用DFS算法，分析了时间复杂度，指出了并查集的复杂度问题。
```cpp
void dfs(int x,int col) {
    for(rei i=0;i<u[x].size();i++)
        if(!c[u[x][i]])
            c[u[x][i]]=col,dfs(u[x][i],col);
}

int main() {
    readln(n);
    for(rei i=1;i<=n;i++)readln(f[i]);
    for(rei j=1;j<=n;j++) {
        readln(d[j]);
        if(j-d[j]>=1)u[j-d[j]].push_back(j),u[j].push_back(j-d[j]);
        if(j+d[j]<=n)u[j+d[j]].push_back(j),u[j].push_back(j+d[j]);
    }
    for(rei i=1;i<=n;i++)if(!c[i])c[i]=++top,dfs(i,top);
    for(rei i=1;i<=n;i++)if(c[i]!=c[f[i]])return puts("NO"),0;
    return puts("YES"),0;
}
```

### 最优关键思路或技巧
- 并查集是解决此类具有传递关系问题的有效数据结构，能高效判断元素是否属于同一集合。
- 将问题转化为图的连通性问题，利用图论算法求解。

### 拓展思路
同类型题可考察元素间的传递关系，如等价类划分、网络连通性判断等。类似算法套路包括使用并查集维护集合关系、Floyd算法求图的传递闭包、DFS或BFS遍历图判断连通性。

### 推荐题目
- [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：并查集基础应用，判断两人是否有亲戚关系。
- [P2814 家谱](https://www.luogu.com.cn/problem/P2814)：并查集维护家族关系。
- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)：可使用并查集实现Kruskal算法求最小生成树。

### 个人心得总结
- 赤霞QvQ：一开始没想到用并查集，看到算法标签才顿悟，说明算法标签有时能提供关键思路。
- Error_Eric：认为并查集虽然帅，但DFS复杂度更低且更好理解，提醒我们在选择算法时要综合考虑复杂度和实现难度。 

---
处理用时：33.45秒