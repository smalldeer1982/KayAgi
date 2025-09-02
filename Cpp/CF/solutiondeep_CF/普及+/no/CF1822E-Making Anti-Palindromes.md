# 题目信息

# Making Anti-Palindromes

## 题目描述

给您一个由小写字母组成的字符串 $s$，在每次操作中，您可以交换 $s$ 中的任意两个字母，请问把 $s$ 变为“反回文串”的最小操作次数是多少？


“反回文串”定义为：对于一个长度为 $n$ 的字符串 $s$，如果对于任意 $1\leqslant i\leqslant n$ 均有 $s_i\not=s_{n-i+1}$，那么字符串 $s$ 就叫做“反回文串”。

## 样例 #1

### 输入

```
10
10
codeforces
3
abc
10
taarrrataa
10
dcbdbdcccc
4
wwww
12
cabbaccabaac
10
aadaaaaddc
14
aacdaaaacadcdc
6
abccba
12
dcbcaebacccd```

### 输出

```
0
-1
1
1
-1
3
-1
2
2
2```

# AI分析结果

### 题目内容重写
**题目描述**

给你一个由小写字母组成的字符串 $s$，在每次操作中，你可以交换 $s$ 中的任意两个字母，请问把 $s$ 变为“反回文串”的最小操作次数是多少？

“反回文串”定义为：对于一个长度为 $n$ 的字符串 $s$，如果对于任意 $1\leqslant i\leqslant n$ 均有 $s_i\not=s_{n-i+1}$，那么字符串 $s$ 就叫做“反回文串”。

**样例 #1**

### 输入
```
10
10
codeforces
3
abc
10
taarrrataa
10
dcbdbdcccc
4
wwww
12
cabbaccabaac
10
aadaaaaddc
14
aacdaaaacadcdc
6
abccba
12
dcbcaebacccd
```

### 输出
```
0
-1
1
1
-1
3
-1
2
2
2
```

### 算法分类
贪心、字符串

### 题解综合分析
本题的核心思路是通过交换字符使得字符串变为“反回文串”，即任意位置的字符与其对称位置的字符不相同。题解主要集中在以下几个要点：
1. **无解条件**：如果字符串长度为奇数，或者某个字符的出现次数超过字符串长度的一半，则无解。
2. **最小交换次数**：统计所有非法对（即字符与其对称位置的字符相同），并计算最小交换次数。如果某个字符的非法对数量超过总非法对的一半，则交换次数为该字符的非法对数量；否则，交换次数为总非法对数的一半向上取整。

### 所选高分题解
#### 题解1：作者：Lonehll (赞：9)
**星级**：5星  
**关键亮点**：
- 详细分析了无解条件，并给出了充要条件。
- 通过统计非法对的数量，提出了最小交换次数的计算方法。
- 代码实现清晰，逻辑严谨。

**核心代码**：
```cpp
int t, num[30];
char c[200010];

int main() {
    cin >> t;
    int n, cnt = 0;
    while(t--) {
        memset(num, 0, sizeof(num));
        cnt = 0;
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> c[i];
            num[c[i]-'a']++;
        }
        if(n % 2 != 0) {
            cout << -1 << endl;
            continue;
        }
        int maxx = 0;
        for(int i = 0; i < 26; i++) {
            if(num[i] > maxx)
                maxx = num[i];
        }
        if(maxx > n/2) {
            cout << -1 << endl;
            continue;
        }
        memset(num, 0, sizeof(num));
        for(int i = 1; i <= n/2; i++) {
            if(c[i] == c[n-i+1])
                cnt++, num[c[i]-'a']++;
        }
        maxx = 0;
        for(int i = 0; i < 26; i++) {
            if(num[i] > maxx)
                maxx = num[i];
        }
        if(maxx <= cnt-maxx)
            cnt = (cnt+1)/2;
        else
            cnt = maxx;
        cout << cnt << endl;
    }
    return 0;
}
```

#### 题解2：作者：WaterSun (赞：1)
**星级**：4星  
**关键亮点**：
- 简洁明了地分析了无解条件。
- 通过统计冲突对数，提出了最小交换次数的计算方法。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
int n;
int vis[50];
string s;

inline void solve(){
    int Max = 0,ans = 0;
    cin >> n >> s;
    s = ' ' + s;
    if (n & 1){
        puts("-1");
        return;
    }
    memset(vis,0,sizeof(vis));
    for (re int i = 1;i <= n;i++){
        vis[s[i] - 'a']++;
        Max = max(Max,vis[s[i] - 'a']);
    }
    if (Max > n / 2){
        puts("-1");
        return;
    }
    memset(vis,0,sizeof(vis));
    for (re int i = 1,j = n;i <= j;i++,j--){
        if (s[i] == s[j]) vis[s[i] - 'a']++;
    }
    int cnt = 0,num = 0;
    for (re int i = 0;i < 26;i++){
        if (vis[i]){
            cnt += vis[i];
            num = max(num,vis[i]);
        }
    }
    if (num * 2 <= cnt) printf("%d\n",up(cnt,2));
    else printf("%d\n",num);
}
```

### 最优关键思路
1. **无解条件**：字符串长度为奇数或某个字符出现次数超过一半时，直接输出-1。
2. **最小交换次数**：统计所有非法对，若某个字符的非法对数量超过总非法对的一半，则交换次数为该字符的非法对数量；否则，交换次数为总非法对数的一半向上取整。

### 拓展思路
类似的问题可以扩展到其他字符串操作，如通过插入、删除等操作使得字符串满足特定条件。可以进一步研究如何在更复杂的条件下进行优化。

### 推荐题目
1. [P1223 字符串的排列](https://www.luogu.com.cn/problem/P1223)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)

---
处理用时：47.23秒