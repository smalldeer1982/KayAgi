# コメント

## 题目描述

### 题目背景

ニワンゴ君正在考虑动画网站弹幕显示方法的新方案。


在有 $N$ 条评论的视频中，评论将以每秒显示 $1$ 个字符的速度从屏幕左侧向右侧流动。在这些评论中，可以按照任意顺序每隔 $1$ 秒显示一条评论。换句话说，第 $i$ 条显示的评论将在最初显示的评论基础上向右移动 $i-1$ 个字符的位置。

ニワンゴ君希望创建出一种情况，即“ $N$ 条评论在同一位置的字符均相同”。也就是说对于所有 $i$，存在整数 $X$ 和字符 $Y$，使得第 $i$ 条显示的评论的第 $X-i$ 个字符为字符 $Y$。

## 样例 #1

### 输入

```
3
abcd
bdac
aca```

### 输出

```
YES```

## 样例 #2

### 输入

```
4
dwango
niconico
niwango
ginza```

### 输出

```
NO```

# 题解

## 作者：mbzdf (赞：0)

# [AT_dwango2015_finals_2](https://www.luogu.com.cn/problem/AT_dwango2015_finals_2) 题解

## 简要题意

题目给出了一个视频评论的显示方法：评论以每秒显示一个字符的速度从屏幕左侧向右侧流动。在有 $N$ 条评论的视频中，可以按照任意顺序每隔 $1$ 秒显示一条评论，即第 $i$ 条显示的评论将在最初显示的评论基础上向右移动 $i-1$ 个字符的位置。现在要判断是否可以通过适当的显示顺序，使得至少创建一种情况，即“所有 $N$ 条评论在同一竖列的字符均相同”。

## 题目思路

我们可以利用最大流算法来解决这个问题。首先，我们要构建一个网络流图，图中包含了评论的信息以及评论之间的关系。具体步骤如下：

1. 对于每一条评论字符串，将其中每个字符作为一个节点，构建一个二分图。其中，左侧的节点表示评论的字符，右侧的节点表示评论的位置。
2. 如果评论中的某个字符和位置匹配，连接对应的左右节点。
3. 添加源点和汇点，使得源点与所有评论的字符节点相连，所有评论的位置节点与汇点相连。

构建好网络流图后，我们可以通过不断增广的方式，找到一种评论显示的顺序，使得至少创建一种“所有 $N$ 条评论在同一位置的字符均相同”的情况。如果找到这样一种情况，输出 `YES`；否则输出 `NO`。

## AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct line
{
    int to;
    int cap;
    int rev;
};

const int maxlen = 120000;

vector<vector<line>> graph(maxlen + 5);
bool vis[maxlen + 5];
int capa[maxlen + 5];

int p1, p2;

inline void add_line(int go, int to, int cap)
{
    graph[go].push_back({to, cap, (int)(graph[to].size())});
    graph[to].push_back({go, 0, (int)(graph[go].size() - 1)});
}

inline void lose_line(int go, int to, int cap)
{
    for(int t = 0; t < graph[go].size(); ++t)
    {
        line& i = graph[go][t];
        if(i.to == to)
            i.cap += cap,
            graph[to][i.rev].cap -= cap;
    }
}

int dfs(int now, int end, int sum)
{
    if(now == end) return sum;
    vis[now] = 1;
    for(int t = 0; t < graph[now].size(); ++t)
    {
        line& i = graph[now][t];
        if(vis[i.to] || !i.cap) continue;
        int flow = dfs(i.to, end, min(sum, i.cap));
        if(flow)
        {
            if(now < p1 && i.to >= p1 && i.to < p1 + p2)
                capa[i.to - p1] = now;
            if(i.to < p1 && now >= p1 && now < p1 + p2)
                capa[now - p1] = -1;
            i.cap -= flow;
            graph[i.to][i.rev].cap += flow;
            return flow;
        }
    }
    return 0;
}

string words[1005];
int n, minsize = 0x3fffffff;
bool used[505][maxlen + 5];

int main()
{
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> words[i],
        minsize = min(minsize, (int)words[i].size());
    minsize += n;
    
    for(int t = 0; t < 26; ++t)
    {
        p1 = n, p2 = minsize;
        for(int i = 0; i < p1 + p2 + 2; ++i)
            graph[i].clear(),
            capa[i] = -1;
        for(int i = 0; i < p1; ++i)
        {
            for(int j = 0; j < p2; ++j)
            {
                if(j < words[i].size() && words[i][j] == ('a' + t))
                    used[i][j] = 1,
                    add_line(i, j + p1, 1);
                else
                    used[i][j] = 0;
            }
        }
        for(int i = 0; i < p1; ++i)
            add_line(p1 + p2, i, 1);
        for(int i = 0; i < p2; ++i)
            add_line(i + p1, p1 + p2 + 1, 1);
        
        int sum_flow = 0;
        for(int i = 0; i <= p2 - p1; ++i)
        {
            while(1)
            {
                for(int j = 0; j <= p1 + p2 + 1; ++j)
                    vis[j] = 1;
                for(int j = i; j < i + p1; ++j)
                    vis[j + p1] = 0;
                for(int j = 0; j < p1; ++j)
                    vis[j] = 0;
                vis[p1 + p2] = 0;
                vis[p1 + p2 + 1] = 0;
                
                int flow = dfs(p1 + p2, p1 + p2 + 1, 0x3fffffff);
                if(!flow) break;
                sum_flow += flow;
            }
            if(sum_flow == n)
            {
                cout << "YES" << endl;
                return 0;
            }
            if(capa[i] >= 0)
                lose_line(capa[i], i + p1, 1),
                lose_line(p1 + p2, capa[i], 1),
                lose_line(i + p1, p1 + p2 + 1, 1),
                --sum_flow,
                capa[i] = -1;
        }
    }
    cout << "NO" << endl;
    return 0;
}
```

---

