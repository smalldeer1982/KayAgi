# 题目信息

# String Coloring (easy version)

## 题目描述

This is an easy version of the problem. The actual problems are different, but the easy version is almost a subtask of the hard version. Note that the constraints and the output format are different.

You are given a string $ s $ consisting of $ n $ lowercase Latin letters.

You have to color all its characters one of the two colors (each character to exactly one color, the same letters can be colored the same or different colors, i.e. you can choose exactly one color for each index in $ s $ ).

After coloring, you can swap any two neighboring characters of the string that are colored different colors. You can perform such an operation arbitrary (possibly, zero) number of times.

The goal is to make the string sorted, i.e. all characters should be in alphabetical order.

Your task is to say if it is possible to color the given string so that after coloring it can become sorted by some sequence of swaps. Note that you have to restore only coloring, not the sequence of swaps.

## 样例 #1

### 输入

```
9
abacbecfd```

### 输出

```
YES
001010101```

## 样例 #2

### 输入

```
8
aaabbcbb```

### 输出

```
YES
01011011```

## 样例 #3

### 输入

```
7
abcdedc```

### 输出

```
NO```

## 样例 #4

### 输入

```
5
abcde```

### 输出

```
YES
00000```

# AI分析结果

### 题目中文重写
# 字符串染色（简单版本）

## 题目描述
这是该问题的简单版本。实际的问题有所不同，但简单版本几乎是困难版本的一个子任务。请注意，约束条件和输出格式是不同的。

给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

你必须将其所有字符染成两种颜色之一（每个字符只能染一种颜色，相同的字母可以染相同或不同的颜色，即你可以为 $s$ 中的每个索引精确选择一种颜色）。

染色后，你可以交换字符串中相邻的、颜色不同的两个字符。你可以任意次数（可能为零次）执行此操作。

目标是使字符串按字典序排序，即所有字符应按字母顺序排列。

你的任务是判断是否可以对给定的字符串进行染色，使得染色后可以通过一系列交换操作使其按字典序排序。请注意，你只需恢复染色方案，而不需要恢复交换操作的序列。

## 样例 #1
### 输入
```
9
abacbecfd
```
### 输出
```
YES
001010101
```

## 样例 #2
### 输入
```
8
aaabbcbb
```
### 输出
```
YES
01011011
```

## 样例 #3
### 输入
```
7
abcdedc
```
### 输出
```
NO
```

## 样例 #4
### 输入
```
5
abcde
```
### 输出
```
YES
00000
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕如何对字符串进行染色，使得通过交换相邻不同颜色字符能让字符串按字典序排序。不同题解采用了不同的思路和方法：
- **流绪、LZYAC、Xdl_rp**：他们的思路类似，都是基于寻找前面出现过的字母的最大涂色值（需构成逆序对），当前字母的涂色值为该最大值加一，最后判断最大涂色值是否超过 2 来确定是否有解。
- **chinaxjh**：将问题转化为二分图判定问题，通过冒泡排序找出逆序对并建图，然后用深度优先搜索进行染色判断。
- **Erica_N_Contina、_masppy_**：他们的思路一致，是将字符串划分为两个不下降子序列，以第一个字符为起点尽可能选大数构成一个不下降子序列，剩下的构成另一个，最后判断另一个子序列是否也不下降来确定是否有解。

### 所选题解
- **流绪（4星）**：
  - **关键亮点**：思路清晰，代码简洁，直接实现了 hard 版本的思路并适配本题。
  - **个人心得**：提到没人发跟 hard 一样的解法，自己来实现。
- **chinaxjh（4星）**：
  - **关键亮点**：独特地将问题转化为二分图判定问题，思路新颖。
  - **个人心得**：比赛完发现正解类似导弹拦截，提醒要对冒泡排序原理有所了解。
- **Erica_N_Contina（4星）**：
  - **关键亮点**：通过分析颜色相同和不同字符的相对位置关系，将问题转化为划分两个不下降子序列，思路巧妙。

### 重点代码
#### 流绪
```cpp
int sum[maxn] = {0};
int ans[maxn];
int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin >> n ;
    int tot = 0;
    for(int i=1;i<=n;i++)
    {
        char c;
        cin >> c;
        int maxx = 0;
        for(int j=c-'a'+1;j<26;j++)
            maxx = max(maxx,sum[j]);
        ans[i] = maxx+1;
        sum[c-'a'] = max(sum[c-'a'],maxx+1);
        tot = max(tot,maxx+1);
    } 
    if(tot > 2)
        cout << "NO";
    else
    {
        cout << "YES\n";
        for(int i=1;i<=n;i++)
            cout << ans [i]-1;
    }
    return 0;
}
```
**核心实现思想**：遍历字符串，对于每个字符，找到前面比它大的字母的最大编号，当前字符编号为该最大值加一，最后判断最大编号是否超过 2。

#### chinaxjh
```cpp
void add(int x, int y) {
    len++;
    a[len] = y;
    nxt[len] = las[x];
    las[x] = len;
}//链式前向星
bool dfs(int v, int c) {
    color[v] = c;
    for (int i = las[v]; i; i = nxt[i]) {
        if (color[a[i]] == c)
            return false;
        if (color[a[i]] == 0 && !dfs(a[i], -c))
            return false;
    }
    return true;
}//染色判断
void solve() {
    for (int i = 1; i <= n; ++i) {
        if (color[i] == 0) {
            if (!dfs(i, 1)) {
                cout << "No" << endl;
                return;
            }
        }
    }
    cout << "Yes" << endl;
    for (i = 1; i <= n; i++)
        if (color[i] == 1)
            printf("%d", 0);
        else
            printf("%d", 1);
}
int main() {
    cin >> n;
    scanf("%s", s + 1);
    for (i = 1; i <= n; i++) num[i] = i;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n - 1; j++)
            if (s[j] > s[j + 1]) {
                swap(s[j], s[j + 1]);
                swap(num[j], num[j + 1]);
                add(num[j], num[j + 1]);
                add(num[j + 1], num[j]);
            }
    solve();
}
```
**核心实现思想**：用冒泡排序找出逆序对，用链式前向星建图，然后用深度优先搜索对图进行染色判断是否为二分图。

#### Erica_N_Contina
```cpp
signed main(){
    n=rd;
    scanf("%s",s+1);
    c=s[1];
    ans[1]=1;
    for(int i=2;i<=n;i++){
        if(s[i]>=c) {
            c=s[i];
            ans[i]=1;
            continue;
        }
        s[++cnt]=s[i];
        ans[i]=0;
    }
    for(int i=2;i<=cnt;i++){
        if(s[i]<s[i-1]){
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++)cout<<ans[i];
    return 0;
}
```
**核心实现思想**：以第一个字符为起点，尽可能选大数构成一个不下降子序列，染色为 1，剩下的染色为 0，最后判断染色为 0 的字符是否构成不下降子序列。

### 最优关键思路或技巧
- 可以将问题转化为不同的模型，如二分图判定、划分不下降子序列等，从不同角度思考问题。
- 对于字符染色问题，通过记录前面字符的信息来确定当前字符的染色情况。

### 可拓展之处
同类型题可能会增加颜色种类、改变交换规则等。类似算法套路可以用于解决一些序列操作和排序问题，如通过特定操作使序列满足某种顺序要求。

### 推荐洛谷题目
- P1090 [NOIP2004 提高组] 合并果子
- P1880 [NOI1995] 石子合并
- P1040 [NOIP2003 提高组] 加分二叉树

---
处理用时：56.66秒