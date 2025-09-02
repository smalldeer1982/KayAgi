# 题目信息

# [USACO10OPEN] Time Travel S

## 题目描述

Farmer John 买了台时光机，这使得他可以方便地管理自己的奶牛群。

他现在有 $N$ 个操作（$1 \leq N \leq 8 \times 10^4$），每次操作仅可能是如下三种之一：

1. `a x`：添加一头编号为 $x$ 的奶牛（$1 \leq x \leq 10^6$）。
2. `s`：卖掉最近添加的奶牛（保证此时至少有一头奶牛）。
3. `t x`：回到**第 $x$ 次操作前**的状态（保证第 $x$ 次操作存在）。

你需要在 FJ 执行每次操作后输出他拥有的最新的奶牛的编号。特别地，如果没有奶牛，输出 $-1$。

## 说明/提示

下面是样例解释，其中拥有的奶牛已经按添加顺序排好。

| 操作编号 | 操作  | 拥有的奶牛 | 输出 |
| -------- | ----- | ---------- | ---- |
| 1        | `a 5` | 5          | 5    |
| 2        | `a 3` | 5,3        | 3    |
| 3        | `a 7` | 5,3,7      | 7    |
| 4        | `s`   | 5,3        | 3    |
| 5        | `t 2` | 5          | 5    |
| 6        | `a 2` | 5,2        | 2    |
| 7        | `t 4` | 5,3,7      | 7    |
| 8        | `a 4` | 5,3,7,4    | 4    |
| 9        | `s`   | 5,3,7      | 7    |
| 10       | `t 7` | 5,2        | 2    |
| 11       | `s`   | 5          | 5    |
| 12       | `s`   | /          | -1   |

## 样例 #1

### 输入

```
12
a 5
a 3
a 7
s
t 2
a 2
t 4
a 4
s
t 7
s
s```

### 输出

```
5
3
7
3
5
2
7
4
7
2
5
-1```

# AI分析结果

### 综合分析与结论
本题主要考查可持久化栈的实现，各题解的核心思路均围绕此展开，但实现方式有所不同。部分题解使用数组模拟栈，通过记录状态来实现可持久化；部分题解采用可持久化数据结构（如可持久化数组、主席树、rope 等）；还有部分题解利用树形结构（如并查集、建树）来维护操作状态。

### 所选题解
- **RuntimeErr（4星）**
  - **关键亮点**：思路清晰，代码简洁，通过三个数组 `num`、`t`、`pre` 巧妙地实现了可持久化栈的功能，时间复杂度为 $O(n)$。
  - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int N=8e4+10;
int n,num[N],t[N],pre[N],top;
int main(){
    scanf("%d",&n);
    char ch;int x;
    for(int i=1;i<=n;i++){
        scanf(" %c",&ch);
        if(ch=='a'){ 
          scanf("%d",&x);num[++top]=x;
            t[i]=top;pre[t[i]]=t[i-1];
        }else if(ch=='t'){
            scanf("%d",&x);t[i]=t[x-1];
        }else t[i]=pre[t[i-1]];
        printf("%d\n",t[i]?num[t[i]]:-1);
    }
    return 0;
}
```
  - **核心实现思想**：`num` 数组记录奶牛编号，`t` 数组记录第 `i` 次操作最新的奶牛在 `num` 数组中的位置，`pre` 数组记录前一个奶牛的位置。添加操作时更新 `num`、`t` 和 `pre` 数组；跳转操作直接复制前一次操作的状态；删除操作利用 `pre` 数组找到前一个奶牛的位置。

- **Alarm5854（4星）**
  - **关键亮点**：使用指针实现可持久化栈，思路独特，通过模拟操作过程并画图辅助理解，有助于读者掌握核心思想。
  - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
const int N = 80000 + 10;
struct node;
typedef node* list;
struct node {
    int val; list last;
    node(int val = 0, list last = 0): val(val), last(last){}
};
char opt;
int n, x;
list a[N];
int main() {
    a[0] = new node(3216037), a[read(n)] = new node(-1, a[0]), ++n;
    for (int i = 2; i <= n; ++i) {
        read(opt);
        if (opt == 's') a[i] = new node(a[i - 1]->last->val, a[i - 1]->last->last);
        else {
            read(x); if (opt == 'a') a[i] = new node(x, a[i - 1]);
            else a[i] = new node(a[x]->val, a[x]->last);
        }
        write(a[i]->val, '\n');
    }
    return 0;
}
```
  - **核心实现思想**：定义 `node` 结构体表示节点，包含奶牛编号 `val` 和指向前一个节点的指针 `last`。`a` 数组存储每个操作后的栈顶节点。添加操作创建新节点并更新栈顶；删除操作将栈顶指针指向前一个节点；跳转操作复制指定操作的栈顶节点。

- **Purslane（4星）**
  - **关键亮点**：代码简洁，通过结构体 `Stack` 维护栈节点信息，每个时间点维护一个栈顶指针 `root`，实现可持久化栈。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=8e4+10;
struct Stack {
    int id,son;
}st[MAXN];
int n,idx,root[MAXN];
int main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;st[0]={-1,0};
    ffor(i,1,n) {
        char ch;int x;cin>>ch;
        if(ch=='a') {cin>>x;root[i]=++idx,st[idx]={x,root[i-1]};}
        if(ch=='s') root[i]=st[root[i-1]].son;
        if(ch=='t') {cin>>x;root[i]=root[x-1];}
        cout<<st[root[i]].id<<'\n';
    }
    return 0;
}
```
  - **核心实现思想**：`Stack` 结构体的 `id` 表示奶牛编号，`son` 表示下一个元素的位置。`root` 数组记录每个操作后的栈顶位置。添加操作创建新节点并更新栈顶；删除操作将栈顶指针指向下一个元素；跳转操作复制指定操作的栈顶位置。

### 最优关键思路或技巧
- **数组模拟**：通过数组记录状态，如 `num`、`t`、`pre` 数组，利用数组下标和元素值的关系实现可持久化，时间复杂度低。
- **指针操作**：使用指针可以更直观地表示节点之间的关系，方便实现栈的操作。
- **树形结构**：将操作过程抽象为树形结构，利用节点的父子关系维护状态，便于回溯操作。

### 可拓展之处
同类型题或类似算法套路：
- 可持久化队列：支持队列的插入、删除和回到历史版本操作，可参考可持久化栈的实现思路。
- 可持久化线段树：在区间查询和修改的基础上，支持回到历史版本，常用于解决动态区间问题。
- 可持久化字典树：在字典树的基础上，支持回到历史版本，可用于字符串的动态查询和修改。

### 推荐题目
- [P3919 【模板】可持久化线段树 1（可持久化数组）](https://www.luogu.com.cn/problem/P3919)
- [P4094 [HEOI2016/TJOI2016]字符串](https://www.luogu.com.cn/problem/P4094)
- [P5494 [PKUWC2018]Minimax](https://www.luogu.com.cn/problem/P5494)

### 个人心得摘录与总结
- **RuntimeErr**：在实现删除操作时，因思路错误重构多次，强调了在实现复杂操作时要仔细思考，避免出错。
- **Alarm5854**：一开始使用暴力栈导致空间超限，认识到朴素做法在时间和空间复杂度上的局限性，从而采用更优的“可持久化栈”方法，提醒我们在解题时要考虑数据规模和复杂度。

---
处理用时：50.51秒