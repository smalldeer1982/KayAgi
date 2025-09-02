# 题目信息

# Clique Partition

## 题目描述

You are given two integers, $ n $ and $ k $ . There is a graph on $ n $ vertices, numbered from $ 1 $ to $ n $ , which initially has no edges.

You have to assign each vertex an integer; let $ a_i $ be the integer on the vertex $ i $ . All $ a_i $ should be distinct integers from $ 1 $ to $ n $ .

After assigning integers, for every pair of vertices $ (i, j) $ , you add an edge between them if $ |i - j| + |a_i - a_j| \le k $ .

Your goal is to create a graph which can be partitioned into the minimum possible (for the given values of $ n $ and $ k $ ) number of cliques. Each vertex of the graph should belong to exactly one clique. Recall that a clique is a set of vertices such that every pair of vertices in it are connected with an edge.

Since BledDest hasn't really brushed his programming skills up, he can't solve the problem "given a graph, partition it into the minimum number of cliques". So we also ask you to print the partition itself.

## 样例 #1

### 输入

```
3
2 3
5 4
8 16```

### 输出

```
2 1
1
1 1
3 1 5 2 4
2
1 1 2 1 2
1 2 3 4 5 6 7 8
1
1 1 1 1 1 1 1 1```

# AI分析结果

### 题目中文重写
## 团划分

### 题目描述
给定两个整数 $n$ 和 $k$。有一个包含 $n$ 个顶点的图，顶点编号从 $1$ 到 $n$，初始时图中没有边。

你需要为每个顶点分配一个整数，设顶点 $i$ 分配的整数为 $a_i$。所有的 $a_i$ 应该是 $1$ 到 $n$ 的不同整数。

分配整数后，对于每一对顶点 $(i, j)$，如果 $|i - j| + |a_i - a_j| \le k$，则在它们之间添加一条边。

你的目标是创建一个图，该图可以被划分为尽可能少（对于给定的 $n$ 和 $k$ 值）的团。图中的每个顶点都应该恰好属于一个团。回想一下，团是一组顶点，其中任意两个顶点之间都有边相连。

由于 BledDest 还没有真正提升他的编程技能，他无法解决“给定一个图，将其划分为最少数量的团”的问题。因此，我们还要求你输出具体的划分方案。

### 样例 #1
#### 输入
```
3
2 3
5 4
8 16
```
#### 输出
```
2 1
1
1 1
3 1 5 2 4
2
1 1 2 1 2
1 1 2 3 4 5 6 7 8
1
1 1 1 1 1 1 1 1
```

### 综合分析与结论
这些题解的核心思路都是通过合理构造顶点权值 $a_i$ ，将图划分为最少数量的团。各题解的关键在于证明一些贪心结论，并利用这些结论进行团的构造。

#### 思路对比
- **贪心结论推导**：_Z_F_R_、elbissoPtImaerD、Drind 等题解都通过证明一些贪心结论来指导团的划分，如团内结点编号和权值连续、团大小不超过 $k$ 等。
- **几何模型转化**：Jerrycyx 将问题转化为平面直角坐标系中的曼哈顿距离问题，通过图形直观地分析团的构成。
- **特殊情况构造**：yangshengyu0719 通过列举特殊情况总结出构造完全图的规律。

#### 算法要点
- 各题解都将 $n$ 个顶点按连续编号划分为若干部分，每部分大小尽量为 $k$（最后一部分可能小于 $k$）。
- 对于每个部分，通过特定的构造方法分配权值 $a_i$ ，使得该部分构成一个团。

#### 解决难点
- **贪心结论证明**：证明团内结点编号和权值连续、团大小不超过 $k$ 等结论是关键难点，不同题解采用了不同的证明方法。
- **权值构造**：构造满足 $|i - j| + |a_i - a_j| \le k$ 的权值 $a_i$ 是另一个难点，各题解通过不同的方式实现了这一构造。

### 所选题解
- **_Z_F_R_（5星）**
    - **关键亮点**：思路清晰，详细证明了多个贪心结论，代码实现规范。
    - **个人心得**：赛时乱搞过了，后续对表述进行了修改。
    - **核心代码**：
```cpp
vector<int> Gen_vec(int siz) {
    int i;
    vector<int> vec;
    for(i = siz / 2; i >= 1; i--) {
        vec.push_back(i);
    }
    for(i = siz; i > siz / 2; i--) {
        vec.push_back(i);
    }
    return vec;
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while(testcase--) {
        int n, k, i, j;
        n = Read(), k = Read();
        for(i = 1; i <= n; i += k) {
            int l = i, r = min(i + k - 1, n);
            auto vec = Gen_vec(r - l + 1);
            for(auto v : vec) {
                Write(v + i - 1), putchar(' ');
            }
        }
        putchar('\n'), Write((n + k - 1) / k), putchar('\n');
        for(i = 1; i <= n; i += k) {
            int l = i, r = min(i + k - 1, n);
            for(j = l; j <= r; j++) {
                Write((l - 1) / k + 1), putchar(' ');
            }
        }
        putchar('\n');
    }
    return 0;
}
```
核心实现思想：通过 `Gen_vec` 函数生成每个部分的权值排列，然后按顺序输出每个部分的权值和所属团的编号。

- **elbissoPtImaerD（4星）**
    - **关键亮点**：将问题转化为平面直角坐标系中的曼哈顿距离问题，思路新颖。
    - **个人心得**：被结论题创飞了，被数据范围骗光了。
    - **核心代码**：
```cpp
il void Solve()
{
    int n,k;rd(n),rd(k);
    ve<int>a(n),c(n);
    int ans=0;
    for(int l=0;l<n;l+=k) {
        int r=min(n,l+k),mid=l+r>>1,t=r;
        for(int i=mid;i>=l;--i) a[i]=--t;
        for(int i=r-1;i>mid;--i) a[i]=--t;
        ans++;
    }
    for(int x:a) wrt(x+1,' ');
    wrt('\n',ans,'\n');
    for(int i=0;i<n;++i) wrt(i/k+1," \n"[i==n-1]);
    return;
}
```
核心实现思想：通过循环将顶点按连续编号划分为若干部分，对于每个部分，按特定顺序分配权值，最后输出权值和所属团的编号。

- **Drind（4星）**
    - **关键亮点**：明确给出了子图数量的计算方法，并补充了证明。
    - **个人心得**：由于 checker 出锅导致晚了半个小时才发现程序写挂了一个很弱智的问题。
    - **核心代码**：
```cpp
inline void fake_main(){
    int n,k; cin>>n>>k; int tot=1;
    for(int i=1;i<=n;i+=k){
        int ed=min(n,i+k-1);
        int len=ed-i+1;
        for(int j=i;j<=i+len/2-1;j++){
            ans[j]=j+(len+1)/2;
            bel[j]=tot;
        }
        for(int j=i+len/2;j<=ed;j++){
            ans[j]=j-len/2;
            bel[j]=tot;
        }
        tot++;
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" "; cout<<"\n";
    cout<<tot-1<<"\n";
    for(int i=1;i<=n;i++) cout<<bel[i]<<" "; cout<<"\n";
}
```
核心实现思想：通过循环将顶点按连续编号划分为若干部分，对于每个部分，按特定规则分配权值和所属团的编号，最后输出结果。

### 最优关键思路或技巧
- **贪心思想**：通过证明贪心结论，如团内结点编号和权值连续、团大小不超过 $k$ 等，指导团的划分和权值构造。
- **几何模型转化**：将问题转化为平面直角坐标系中的曼哈顿距离问题，利用图形直观地分析团的构成。
- **特殊情况构造**：通过列举特殊情况总结出构造完全图的规律，简化权值构造过程。

### 可拓展之处
同类型题可能会改变连边条件或团的定义，类似算法套路可以是先通过分析问题性质得出一些贪心结论，然后利用这些结论进行构造。

### 洛谷推荐题目
1. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)
2. [P2825 [HEOI2016/TJOI2016]游戏](https://www.luogu.com.cn/problem/P2825)
3. [P3959 [NOIP2017 提高组] 宝藏](https://www.luogu.com.cn/problem/P3959)

### 个人心得摘录与总结
- **_Z_F_R_**：赛时乱搞过了，后续对表述进行了修改，说明有时候可以先尝试一些直观的思路，后续再完善。
- **elbissoPtImaerD**：被结论题创飞了，被数据范围骗光了，提醒我们在解题时不能被数据范围误导，要深入分析问题本质。
- **Drind**：由于 checker 出锅导致晚了半个小时才发现程序写挂了一个很弱智的问题，强调了调试环境和细心检查代码的重要性。

---
处理用时：46.52秒