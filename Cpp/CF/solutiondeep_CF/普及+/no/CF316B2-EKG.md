# 题目信息

# EKG

## 题目描述

一家医院的挂号处，排起了一条长度为 $n$ 的队，这 $n$ 个人依次编号为 $1\sim n$



一个人只会记得他前面的人的编号，而其中的某些人，已经忘记了前面人的编号。



给出 $n$ 和 $pos$ ，请求出编号为 $pos$ 的人在队伍中所有可能站的位置。

## 说明/提示

$0 \le a_i \le n$  

$1 \le n,pos \le 1000$



感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
6 1
2 0 4 0 6 0
```

### 输出

```
2
4
6
```

## 样例 #2

### 输入

```
6 2
2 3 0 5 6 0
```

### 输出

```
2
5
```

## 样例 #3

### 输入

```
4 1
0 0 0 0
```

### 输出

```
1
2
3
4
```

## 样例 #4

### 输入

```
6 2
0 0 1 0 4 5
```

### 输出

```
1
3
4
6
```

# AI分析结果

### 题目内容
# EKG

## 题目描述
一家医院的挂号处，排起了一条长度为 $n$ 的队，这 $n$ 个人依次编号为 $1\sim n$ 。
一个人只会记得他前面的人的编号，而其中的某些人，已经忘记了前面人的编号。
给出 $n$ 和 $pos$ ，请求出编号为 $pos$ 的人在队伍中所有可能站的位置。

## 说明/提示
$0 \le a_i \le n$  
$1 \le n,pos \le 1000$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1
### 输入
```
6 1
2 0 4 0 6 0
```
### 输出
```
2
4
6
```

## 样例 #2
### 输入
```
6 2
2 3 0 5 6 0
```
### 输出
```
2
5
```

## 样例 #3
### 输入
```
4 1
0 0 0 0
```
### 输出
```
1
2
3
4
```

## 样例 #4
### 输入
```
6 2
0 0 1 0 4 5
```
### 输出
```
1
3
4
6
```

### 算法分类
动态规划

### 综合分析与结论
所有题解思路核心一致，均是先将给定队列信息看作若干条链，最终完整队列由这些链组成。暴力枚举所有链的组合时间复杂度为 $O(2^n)$ 不可行，于是都采用 01 背包优化。将除 $pos$ 所在链外的其他链长当作物品，通过 01 背包求出 $pos$ 前面人数的所有可能组合，再加上 $pos$ 在其所在链中的位置，即为 $pos$ 在队伍中所有可能站的位置，时间复杂度优化到 $O(n^2)$ 。不同题解在代码实现细节上略有差异，如建链方式、背包实现方式、记录位置方式等。

### 所选的题解
- **作者：Priori_Incantatem (5星)**
    - **关键亮点**：思路清晰，代码简洁高效。通过 `nxt` 数组构建链关系，利用 `vis` 数组标记已处理的节点，在找链长时使用 `goto` 语句跳出循环确定 `pos` 在其所在链中的位置，背包部分代码标准。
    - **重点代码**：
```cpp
// 读入数据
n=read(),pos=read();
for(int i=1;i<=n;++i)
{
    int x=read();
    if(x)nxt[x]=i,vis[i]=1;
}
// 找链长和pos在其所在链中的位置
for(int i=1;i<=n;++i)
{
    if(vis[i])continue;
    int cnt=0,x=i;
    while(x)
    {
        ++cnt;
        if(x==pos){val=cnt;goto GG;}
        x=nxt[x];
    }
    a[++m]=cnt;
    GG:;
}
// 01背包
f[0]=1;
for(int i=1;i<=m;++i)
{
    for(int j=n;j>=a[i];--j)
    if(f[j-a[i]])f[j]=1;
}
// 输出结果
for(int i=0;i<=n;++i)
if(f[i])printf("%d\n",i+val);
```
- **作者：linziyang1 (4星)**
    - **关键亮点**：使用 `vector` 存储链结构，代码结构清晰，逻辑完整。通过 `gx` 函数预处理出以每个节点结尾的已知连续序列，再通过 `search` 函数找出包含特定序列的最长序列，最后利用背包求出所有可能位置。
    - **重点代码**：
```cpp
// 预处理出以i结尾的一条已知连续的序列
void gx(int x) {
    if (vec[x].size())	return;
    if (pre[x]) {
        gx(pre[x]);
        add(x, pre[x]);
    }
    vec[x].push_back(x);
}
// 找出包含vec[i]的最长序列
for (int i = 1; i <= n; ++i) {
    if (vis[i])	continue;
    int no = i, max_size = vec[i].size();
    for (int j = 1; j <= n; ++j) {
        if (vis[j])	continue;
        if (search(j, i)) { 
            if (vec[j].size() > max_size) { 
                no = j;
                max_size = vec[j].size();
            }
        }
    }
    for (int j = 0; j < vec[no].size(); ++j) {
        vis[vec[no][j]] = true; 
    }
    v.push_back(vec[no]); 
}
// 确定x的位置
for (int i = 0; i < v.size(); ++i) { 
    bool cmp = 0;
    for (int j = 0; j < v[i].size(); ++j) {
        if (v[i][j] == x) {
            fst = i; 
            snd = j; 
            cmp = 1; 
            break;
        }
    }
    if (cmp)	break; 
}
// 01背包
vector<int>().swap(v[fst]);
f[0] = 1; 
for (int i = 0; i < v.size(); ++i) {
    if (v[i].size()) {
        for (int j = n; j >= v[i].size(); --j) { 
            if (f[j - v[i].size()]) {
                f[j] = 1;
            }
        }
    }
}
// 输出结果
for (int i = 0; i <= n; ++i) {
    if (f[i]) {
        cout << i + snd + 1 << endl; 
    }
}
```
- **作者：bloodstalk (4星)**
    - **关键亮点**：代码简洁明了，变量命名直观。通过 `head` 数组标记链的起点，在遍历链时同时确定 `pos` 在其所在链中的位置并剔除该链，背包部分代码简洁标准。
    - **重点代码**：
```cpp
// 标记链的起点和构建链关系
for(re int i=1;i<=n;i++)
{
    x = read();
    if(!x) continue;
    next[x] = i, head[i] = 0;
}
// 找链长和pos在其所在链中的位置
for(re int i=1;i<=n;i++)
{
    if(!head[i]) continue;
    int p = i; cnt = 0, flag = 1;
    while(p)
    {
        ++cnt;
        if(p == pos) { wz = cnt; flag = 0; break; }
        p = next[p];
    }
    if(flag) a[++m] = cnt;
}
// 01背包
f[0] = 1;
for(re int i=1;i<=m;i++)
    for(re int j=n;j>=a[i];j--)
        f[j] += f[j-a[i]];
// 输出结果
for(re int i=0;i<=n;i++) if(f[i]) cout << i + wz << "\n";
```

### 最优关键思路或技巧
将实际排队问题抽象为链结构，利用 01 背包解决链长组合问题，优化暴力枚举。在建链过程中，合理使用数组标记和循环遍历确定链长及特定元素位置。在背包实现上，采用标准的 01 背包动态规划方式，通过双重循环更新状态。

### 同类型题或类似算法套路
此类题目通常将实际场景转化为图结构（这里是链），对于求解组合数量或可能性问题，若暴力枚举复杂度高，可考虑能否转化为背包问题。类似套路如将物品重量或价值对应实际问题中的某个属性，通过背包的状态转移方程求解。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典 01 背包问题，通过采药时间和价值的限制，练习 01 背包的基本实现。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：是 01 背包的变形，在完全背包基础上加深对背包问题的理解和应用。
- [P2782 友好城市](https://www.luogu.com.cn/problem/P2782)：需要先对数据进行排序，再利用最长上升子序列的思路结合动态规划求解，与本题将实际问题转化为可利用动态规划解决的思路类似。 

---
处理用时：71.25秒