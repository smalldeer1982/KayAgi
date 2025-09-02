# 题目信息

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 样例 #1

### 输入

```
3
rivest
shamir
adleman
```

### 输出

```
bcdefghijklmnopqrsatuvwxyz
```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever
```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz
```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck
```

### 输出

```
acbdefhijklmnogpqrstuvwxyz
```

# AI分析结果

### 题目中文重写
# 狐狸与名字

## 题目描述

狐狸 Ciel 打算在 FOCS（狐狸操作计算机系统，发音：“Fox”）上发表一篇论文。她听闻了一个传言：论文上的作者名单总是按字典序排列的。

在查看了一些例子后，她发现有时并非如此。在一些论文中，作者的名字在正常意义上并非按字典序排列。但总是存在这样的情况：在对字母表中的字母顺序进行某些修改后，作者的顺序就变成了字典序！

她想知道，是否存在一种拉丁字母表的字母顺序，使得她提交的论文上的名字是按字典序排列的。如果存在，你应该找出任意一种这样的顺序。

字典序的定义如下。当我们比较 $s$ 和 $t$ 时，首先找到最左边字符不同的位置：$s_{i} \neq t_{i}$。如果不存在这样的位置（即 $s$ 是 $t$ 的前缀或者反之），则较短的字符串较小。否则，我们根据字母表的顺序比较字符 $s_{i}$ 和 $t_{i}$。

## 样例 #1

### 输入
```
3
rivest
shamir
adleman
```

### 输出
```
bcdefghijklmnopqrsatuvwxyz
```

## 样例 #2

### 输入
```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer
```

### 输出
```
Impossible
```

## 样例 #3

### 输入
```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever
```

### 输出
```
aghjlnopefikdmbcqrstuvwxyz
```

## 样例 #4

### 输入
```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck
```

### 输出
```
acbdefhijklmnogpqrstuvwxyz
```

### 综合分析与结论
这些题解的核心思路都是通过拓扑排序来解决问题。根据输入的字符串构建有向图，图中的节点为字母，边表示字母之间的先后顺序。在构建图的过程中，需要注意特判一个字符串是另一个字符串前缀的情况，若后一个字符串是前一个字符串的前缀且长度更短，则不存在合法的字典序。最后进行拓扑排序，若排序结果包含 26 个字母，则输出该拓扑序列作为合法的字典序；若存在环或不满足前缀条件，则输出 "Impossible"。

### 所选题解
- **作者：杨誉yy（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对建图和拓扑排序的过程解释清晰，并且强调了特判条件和代码中的注意事项。
    - **核心代码**：
```cpp
for(i=2;i<=n;i++)
{
    cin>>now;
    int len=min(pas.length(),now.length());
    for(j=0;j<=len;j++)
    {
        if(j==len)
        {
            if(pas.length()>now.length())
            {
                printf("Impossible");
                return 0;
            }
            break;
        }
        if(pas[j]!=now[j])
        {
            int up=pas[j]-'a';
            int down=now[j]-'a'; 
            l[up][++cnt[up]]=down;
            num[down]++;
            break;	
        }		
    }
    pas=now;
}
```
核心实现思想：遍历相邻的两个字符串，找到第一个不同的字符，建立有向边。同时特判后一个字符串是前一个字符串前缀的情况。

- **作者：Juanzhang（4星）**
    - **关键亮点**：使用 dfs 进行拓扑排序，代码简洁，适合喜欢 dfs 方式的读者。
    - **核心代码**：
```cpp
bool dfs(int u) {
    if (vis[u]) {
        return vis[u] > 1;
    }
    vis[u] = 1;
    for (int v : e[u]) {
        if (!dfs(v)) {
            return 0;
        }
    }
    a[++now] = u;
    vis[u] = 2;
    return 1;
}
```
核心实现思想：通过 dfs 对每个字母进行遍历，标记节点的访问状态，同时判断是否存在环。

- **作者：lym12321（4星）**
    - **关键亮点**：使用优先队列进行拓扑排序，可以求出字典序最小的字典序，并且代码有详细的注释。
    - **核心代码**：
```cpp
int topoSort(){
    int cnt = 0;
    priority_queue <int> q;
    for(int i = 0; i < 26; i++){
        if(!deg[i]) q.push(-i);
    }
    while(!q.empty()){
        int k = -q.top(); q.pop();
        arr[++cnt] = k;
        for(auto to : ch[k]){
            deg[to]--;
            if(!deg[to]) q.push(-to);
        }
    }
    return cnt;
}
```
核心实现思想：使用优先队列存储入度为 0 的节点，每次取出队列中最小的节点，更新其相邻节点的入度，直到队列为空。

### 最优关键思路或技巧
- **拓扑排序**：利用拓扑排序解决字母字典序的问题，将字母看作节点，字母之间的先后顺序看作有向边。
- **特判前缀情况**：在构建图的过程中，特判一个字符串是另一个字符串前缀的情况，避免出现不合法的字典序。
- **代码优化**：可以使用优先队列进行拓扑排序，求出字典序最小的字典序。

### 可拓展之处
同类型题或类似算法套路：
- 其他需要根据元素之间的先后顺序进行排序的问题，如课程表问题（判断是否可以完成所有课程、求出课程学习顺序等）。
- 任务调度问题，根据任务之间的依赖关系安排任务的执行顺序。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：涉及任务之间的先后顺序，可使用拓扑排序解决。
- [P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)：通过拓扑排序计算最大食物链的数量。
- [P3243 [HNOI2015]菜肴制作](https://www.luogu.com.cn/problem/P3243)：需要求出满足条件的字典序最小的排列，可使用拓扑排序和优先队列解决。

### 个人心得摘录与总结
- **作者：Enterpr1se**：一开始想到用 Floyd 算法，但发现算法标签是拓扑排序。做题前查看字典序的定义，注意到字典序中的小细节，如字符串前缀的情况。在实现过程中，总结了 `Impossible` 的三种成因，使思路更加清晰。
- **作者：kdy20100729**：一开始代码没有通过第 13 个点，经过分析发现是没有特判后一个字符串是前一个字符串的子串且前一个字符串长度更长的情况，提醒我们在做题时要考虑全面。 

---
处理用时：43.74秒