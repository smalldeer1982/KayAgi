# 题目信息

# [USACO14FEB] Auto-complete S

## 题目描述

有 $w$ 个由小写字符构成的字典和 $n$ 个询问。每个询问由一个字符串 $s$ 和一个整数 $k$ 构成，求在字典序排序下字典内由 $s$ 为前缀的第 $k$ 字符串在输入字典的位置。若不存在，则输出 $-1$

## 说明/提示

对于 $100\%$ 的数据，$w \le 30000$，$1\le n \le 1000$，字典内每个字符串的长度均小于等于 $1000$，且字典的单词总长不超过 $10 ^ 6$。

样例解释：

对于第 $1$ 个询问，含义为在字典中找到以 ```a``` 为前缀且按字典序排序后第 $4$ 个字符串，而字典中以 ```a``` 为前缀且按字典序排序后为 $\{$  ```aa```，```aaa```，```aab```，```ab```，```abc```，```ac``` $\}$，第 $4$ 个是 ```ab```，其在输入中为第 $3$ 个，故输出为 $3$

同理，对于第 $2$ 个和第 $3$ 个询问是在字典中找到以 ```da``` 为前缀且按字典序排序后的第 $2$ 和第 $4$ 个字符串。而以 ```da``` 为前缀的字符串按字典序排序后为 $\{$```daa```，```dab```，```dadba``` $\}$，故第 $2$ 个为 ```dab``` ，其在输入中为第 $1$ 个，故第 $2$ 个输出为 $1$，而该序列中没有第 $4$ 个，故第 $3$ 个询问无解，输出 $-1$

来源：USACO 2014 Feburary Contest Silver

翻译：@[zymooll](/user/289296)

## 样例 #1

### 输入

```
10 3
dab
ba
ab
daa
aa
aaa
aab
abc
ac
dadba
4 a
2 da
4 da```

### 输出

```
3
1
-1```

# AI分析结果

### 综合分析与结论
这些题解主要围绕排序和查找展开，解决在字典中查找以给定字符串为前缀的第 k 个字符串位置的问题。主要思路有暴力遍历、二分查找和字典树三种。暴力遍历简单但时间复杂度高，二分查找和字典树在效率上更优。

### 所选题解
- **Expecto（5星）**
    - **关键亮点**：思路简洁清晰，使用 `lower_bound` 函数快速定位前缀位置，代码简洁高效。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
pair<string,int> a[90030];
bool match(string x,string y){
    if (y.length()>x.length()) return 0;
    return x.substr(0,y.size())==y;
}
int main(){
    int w,n;
    cin>>w>>n;
    for (int i=0;i<w;i++){
        cin>>a[i].first;
        a[i].second=i;
    }
    sort(a,a+w);
    while (n--){
        string pre;
        int k;
        cin>>k>>pre;
        int pos=k-1+lower_bound(a,a+w,make_pair(pre,0))-a;
        if (pos>=w ||!match(a[pos].first,pre)) {
            cout<<"-1\n";
            continue;
        }
        cout<<a[pos].second+1<<'\n';
    }
    return 0;
}
```
    - **核心实现思想**：先将字典按字典序排序，对于每个询问，使用 `lower_bound` 找到第一个以给定前缀开头的字符串位置，加上 k 后判断是否越界以及是否仍以该前缀开头，若是则输出对应位置，否则输出 -1。

- **Sooke（4星）**
    - **关键亮点**：手动实现二分查找，详细解释了二分判断条件的使用，有助于理解二分查找的原理。
    - **核心代码**：
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

struct stc{
    string s;
    int n;
}s[30001]; 

bool Cmp(stc x, stc y){
    return x.s < y.s;    
}

string t;
int p, n, k, l, r, m, resl, resr;

int main(){
    cin >> p >> n;
    for(int i = 1 ; i <= p ; i++)
        cin >> s[i].s, s[i].n = i;
    sort(s + 1, s + p + 1, Cmp); 
    for(int i = 1 ; i <= n ; i++){
        cin >> k >> t;
        resl = 0, resr = 0;
        l = 0, r = p; 
        while(l <= r){
            m = (l + r) >> 1;
            if(t > s[m].s)
                l = m + 1, resl = m;
            else
                r = m - 1;
        }
        l = 0, r = p ; t = t + '|'; 
        while(l <= r){
            m = (l + r) >> 1;
            if(t >= s[m].s)
                l = m + 1, resr = m;
            else
                r = m - 1;
        }
        if(resl + k > resr)
            cout << -1 << endl;
        else
            cout << s[resl + k].n << endl; 
    }
    return 0;
}
```
    - **核心实现思想**：先对字典排序，对于每个询问，用二分查找分别找出以给定前缀开头的字符串的左边界和右边界，若左边界加上 k 超过右边界则无解，否则输出对应位置。

- **曹老师（4星）**
    - **关键亮点**：使用字典树解决问题，时间复杂度低，适用于处理大量字符串前缀查询。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int L = 1000005;
short vis[L];
int n, m, tree[L][30], tot = 0, val[L], size[L], num[L];

void build(string s, int cnt) {
    int len = s.length(), now = 0;
    for(int i=0; i<len; i++) {
        int id = s[i] - 'a';
        if(!tree[now][id])
            tree[now][id] = ++tot;
        now = tree[now][id];
    }
    val[now] = -1;
    size[now] = 1;
    num[now] = cnt;
}

void dfs(int x) {
    vis[x] = 1;
    for(int i=0; i<26; i++)
        if(tree[x][i]) {
            dfs(tree[x][i]);
            size[x] += size[tree[x][i]];
        }
}

int find(int x, string s) {
    int len = s.length(), now = 0, ans = 0;
    for(int i=0; i<len; i++) {
        int id = s[i] - 'a';
        if(!tree[now][id])
            return -1;
        now = tree[now][id];
    }
    if(size[now] < x)
        return -1;
    if(val[now] == -1)
        x--;
    for(int i=0; i<26; i++) {
        if(!x && val[now] == -1)
            return num[now];
        if(size[tree[now][i]] < x)
            x -= size[tree[now][i]];
        else {
            if(tree[now][i]) {
                now = tree[now][i];
                i = -1;
                if(val[now] == -1)
                    x--;
            }
        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++) {
        string s;
        cin>>s;
        build(s, i);
    }
    for(int i=1; i<=tot; i++)
        if(!vis[i])
            dfs(i);
    for(int i=1; i<=m; i++) {
        int x;
        string s;
        cin>>x>>s;
        printf("%d\n",find(x, s));
    }
    return 0;
}
```
    - **核心实现思想**：将所有单词插入字典树，通过深度优先搜索维护每个节点子树中单词的数量，对于每个询问，在字典树中找到前缀对应的节点，根据子树中单词数量确定第 k 个单词的位置。

### 最优关键思路或技巧
- **使用 `lower_bound` 函数**：可以快速定位到第一个以给定前缀开头的字符串位置，减少查找时间。
- **字典树**：适用于处理大量字符串前缀查询，通过维护节点信息可以高效地找到符合条件的字符串。

### 拓展思路
同类型题可考察不同数据结构的应用，如在字符串匹配、前缀查询等场景中使用哈希表、AC 自动机等。类似算法套路可用于解决其他排序和查找问题，如在有序数组中查找满足特定条件的元素。

### 推荐题目
1. [P1481 魔族密码](https://www.luogu.com.cn/problem/P1481)：考察字典树的应用，判断一个单词是否可以由其他单词拼接而成。
2. [P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)：使用字典树判断名字是否存在以及是否重复点名。
3. [P3879 [TJOI2010] 阅读理解](https://www.luogu.com.cn/problem/P3879)：通过字典树和哈希表实现对文章中单词的查询。

### 个人心得摘录与总结
- **一只野生蒟蒻**：原使用 `substr` 在洛谷能过，但在其他 OJ 超时，后改用逐个字符比较通过所有点，说明不同 OJ 数据强度不同，且 `substr` 函数可能存在性能问题。
- **Hexarhy**：暴力算法开 O2 后能 AC，体现了编译器优化对程序性能的影响，但不建议依赖优化，应优先考虑算法优化。 

---
处理用时：48.91秒