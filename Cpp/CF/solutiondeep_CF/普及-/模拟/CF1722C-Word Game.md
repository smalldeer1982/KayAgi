# 题目信息

# Word Game

## 题目描述

Three guys play a game: first, each person writes down $ n $ distinct words of length $ 3 $ . Then, they total up the number of points as follows:

- if a word was written by one person — that person gets 3 points,
- if a word was written by two people — each of the two gets 1 point,
- if a word was written by all — nobody gets any points.

 In the end, how many points does each player have?

## 说明/提示

In the first test case:

- The word $ \texttt{abc} $ was written by the first and third guys — they each get $ 1 $ point.
- The word $ \texttt{def} $ was written by the second guy only — he gets $ 3 $ points.

## 样例 #1

### 输入

```
3
1
abc
def
abc
3
orz for qaq
qaq orz for
cod for ces
5
iat roc hem ica lly
bac ter iol ogi sts
bac roc lly iol iat```

### 输出

```
1 3 1 
2 2 6 
9 11 5```

# AI分析结果

### 题目中文重写
# 单词游戏

## 题目描述
三个人玩一个游戏：首先，每个人写下 $n$ 个不同的长度为 $3$ 的单词。然后，他们按照以下规则计算总分数：
- 如果一个单词只有一个人写了，那么这个人得 $3$ 分；
- 如果一个单词有两个人写了，那么这两个人各得 $1$ 分；
- 如果一个单词三个人都写了，那么没有人得分。

最后，每个人各得了多少分？

## 说明/提示
在第一个测试用例中：
- 单词 $\texttt{abc}$ 是第一个人和第三个人写的，他们每人得 $1$ 分。
- 单词 $\texttt{def}$ 只有第二个人写了，他得 $3$ 分。

## 样例 #1
### 输入
```
3
1
abc
def
abc
3
orz for qaq
qaq orz for
cod for ces
5
iat roc hem ica lly
bac ter iol ogi sts
bac roc lly iol iat
```

### 输出
```
1 3 1 
2 2 6 
9 11 5
```

### 综合分析与结论
这些题解的核心思路都是先统计每个单词的出现次数，再根据出现次数按照得分规则为每个人加分。不同题解在数据结构和实现细节上有所差异：
- **achjuncool**：使用四个 `map<string, bool>` 分别记录每个人是否写出某个单词以及该单词是否已统计过，然后遍历所有单词进行加分。
- **lihanwen12**：将长度为 $3$ 的小写字母单词转换为 $26$ 进制数，用布尔数组记录每个单词是否被每个人写出，最后遍历所有可能的单词进行加分。
- **Moyou**：使用 `unordered_map<string, int>` 统计每个单词的出现次数，再遍历每个人写下的单词进行加分。
- **Lantrol**：使用 `map<string, int>` 统计每个单词的出现次数，然后遍历每个人写下的单词进行加分。
- **Kedit2007**：使用 `map<string, int>` 统计每个单词的出现次数，通过函数封装遍历每个人写下的单词进行加分。

### 题解选择
- **Moyou（4星）**：
    - **关键亮点**：思路清晰，使用 `unordered_map` 统计单词出现次数，其内部实现为哈希表，查找和插入操作的平均时间复杂度为 $O(1)$，代码简洁易读。
    - **核心代码**：
```cpp
unordered_map<string, int> h;
int cnt[5];
while(T--)
{
    h.clear();
    int n;
    cin >> n;
    memset(cnt, 0, sizeof cnt);
    string a[5][1010];
    for(int i = 1; i <= 3; i ++)
    {
        for(int j = 1; j<=n;j++)
        {
            cin >> a[i][j];
            h[a[i][j]]++; // 统计字符串出现个数
        }
    }
    for(int i = 1; i <= 3; i ++)
    {
        for(int j = 1; j <= n; j ++)
        {
            if(h[a[i][j]] >= 3) continue; // 根据规则加分
            if(h[a[i][j]] == 2) cnt[i] ++;
            else if(h[a[i][j]] == 1) cnt[i] += 3;
        }
    }
    cout << cnt[1] << ' ' << cnt[2] << ' ' << cnt[3] << endl; // 输出得分
}
```
- **Lantrol（4星）**：
    - **关键亮点**：思路简洁直接，使用 `map<string, int>` 统计单词出现次数，代码结构清晰，易于理解。
    - **核心代码**：
```cpp
map<string,int> mp;
void solve(){
    mp.clear();
    int n;
    string s[4][1005];
    int ans[4]={0,0,0,0};
    cin>>n;
    for(int j=1;j<=3;j++)
    for(int i=1;i<=n;i++){
        cin>>s[j][i];
        mp[s[j][i]]++;
    }
    for(int j=1;j<=3;j++){
        for(int i=1;i<=n;i++){
            if(mp[s[j][i]]==1){
                ans[j]+=3;
            }
            if(mp[s[j][i]]==2){
                ans[j]+=1;
            }
        }
    }
    cout<<ans[1]<<" "<<ans[2]<<" "<<ans[3]<<endl;
}
```
- **Kedit2007（4星）**：
    - **关键亮点**：将核心逻辑封装在函数中，提高了代码的复用性，使用 `map<string, int>` 统计单词出现次数，代码简洁明了。
    - **核心代码**：
```cpp
vector<int> WordGame(vector<string> a, vector<string> b, vector<string> c)
{
    map<string, int> cnt;
    vector<int> ret(3, 0);
    for (auto& s : a)
        cnt[s]++;
    for (auto& s : b)
        cnt[s]++;
    for (auto& s : c)
        cnt[s]++;
    for (auto s : a)
    {
        if (cnt[s] == 1) ret[0] += 3;
        if (cnt[s] == 2) ret[0] += 1;
    }
    for (auto s : b)
    {
        if (cnt[s] == 1) ret[1] += 3;
        if (cnt[s] == 2) ret[1] += 1;
    }
    for (auto s : c)
    {
        if (cnt[s] == 1) ret[2] += 3;
        if (cnt[s] == 2) ret[2] += 1;
    }
    return ret;
}
```

### 最优关键思路或技巧
使用 `unordered_map` 或 `map` 统计单词的出现次数，利用哈希表或红黑树的特性，高效地进行查找和插入操作，从而简化了统计过程。

### 可拓展之处
同类型题可以是多人游戏得分统计，单词长度或规则可以变化，解题思路依然是先统计元素出现次数，再根据规则计算得分。类似算法套路可用于统计元素频率并根据频率进行相应操作的题目。

### 推荐题目
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：统计每个位置被操作的次数，根据次数判断灯的状态。
- [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：简单的数组操作，可类比本题的输入和遍历过程。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：统计每个位置的占用情况，根据占用情况计算剩余树的数量。

### 个人心得摘录与总结
- **achjuncool**：“我才不会说我忘记初始化调了好久呢”，总结为在多组数据的题目中，一定要记得对变量进行初始化，否则可能会导致结果错误，调试时间增加。

---
处理用时：38.23秒