# 题目信息

# Most Similar Words

## 题目描述

You are given $ n $ words of equal length $ m $ , consisting of lowercase Latin alphabet letters. The $ i $ -th word is denoted $ s_i $ .

In one move you can choose any position in any single word and change the letter at that position to the previous or next letter in alphabetical order. For example:

- you can change 'e' to 'd' or to 'f';
- 'a' can only be changed to 'b';
- 'z' can only be changed to 'y'.

The difference between two words is the minimum number of moves required to make them equal. For example, the difference between "best" and "cost" is $ 1 + 10 + 0 + 0 = 11 $ .

Find the minimum difference of $ s_i $ and $ s_j $ such that $ (i < j) $ . In other words, find the minimum difference over all possible pairs of the $ n $ words.

## 说明/提示

For the second test case, one can show that the best pair is ("abb","bef"), which has difference equal to $ 8 $ , which can be obtained in the following way: change the first character of the first string to 'b' in one move, change the second character of the second string to 'b' in $ 3 $ moves and change the third character of the second string to 'b' in $ 4 $ moves, thus making in total $ 1 + 3 + 4 = 8 $ moves.

For the third test case, there is only one possible pair and it can be shown that the minimum amount of moves necessary to make the strings equal is $ 35 $ .

For the fourth test case, there is a pair of strings which is already equal, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
6
2 4
best
cost
6 3
abb
zba
bef
cdu
ooo
zzz
2 7
aaabbbc
bbaezfe
3 2
ab
ab
ab
2 8
aaaaaaaa
zzzzzzzz
3 1
a
u
y```

### 输出

```
11
8
35
0
200
4```

# AI分析结果

### 题目中文重写
# 最相似的单词

## 题目描述
给定 $n$ 个长度均为 $m$ 的单词，这些单词由小写拉丁字母组成。第 $i$ 个单词记为 $s_i$。

在一次操作中，你可以选择任意一个单词中的任意一个位置，并将该位置的字母更改为字母表中前一个或后一个字母。例如：
- 你可以将 'e' 更改为 'd' 或 'f'；
- 'a' 只能更改为 'b'；
- 'z' 只能更改为 'y'。

两个单词之间的差异是使它们相等所需的最少操作次数。例如，"best" 和 "cost" 之间的差异为 $1 + 10 + 0 + 0 = 11$。

找出满足 $i < j$ 的 $s_i$ 和 $s_j$ 之间的最小差异。换句话说，找出这 $n$ 个单词所有可能的单词对之间的最小差异。

## 说明/提示
对于第二个测试用例，可以证明最优的单词对是 ("abb", "bef")，其差异为 $8$，可以通过以下方式得到：将第一个字符串的第一个字符用一次操作更改为 'b'，将第二个字符串的第二个字符用 $3$ 次操作更改为 'b'，将第二个字符串的第三个字符用 $4$ 次操作更改为 'b'，总共进行 $1 + 3 + 4 = 8$ 次操作。

对于第三个测试用例，只有一个可能的单词对，并且可以证明使这两个字符串相等所需的最少操作次数是 $35$。

对于第四个测试用例，有一对字符串已经相等，因此答案是 $0$。

## 样例 #1

### 输入
```
6
2 4
best
cost
6 3
abb
zba
bef
cdu
ooo
zzz
2 7
aaabbbc
bbaezfe
3 2
ab
ab
ab
2 8
aaaaaaaa
zzzzzzzz
3 1
a
u
y
```

### 输出
```
11
8
35
0
200
4
```

### 题解综合分析与结论
这些题解的核心思路一致，都是利用数据范围小的特点，采用暴力枚举的方法来解决问题。具体步骤为：先枚举所有不同的字符串对，再计算每对字符串对应位置字符的 ASCII 值之差的绝对值之和，最后取所有和的最小值。

#### 算法要点
- 枚举所有满足 $i < j$ 的字符串对 $(s_i, s_j)$。
- 计算每对字符串对应位置字符的 ASCII 值之差的绝对值，并求和得到这对字符串的差异度。
- 不断更新最小差异度。

#### 解决难点
本题难点在于理解字符串差异度的计算方式，以及避免枚举相同的字符串对。各题解都通过计算字符 ASCII 值之差的绝对值解决了差异度计算问题，通过 $j = i + 1$ 避免了重复枚举。

### 题解评分与选择
- **Engulf（5星）**：思路清晰，代码使用了 `std::vector` 和 `std::min` 等标准库，可读性高，且代码结构良好。
- **5k_sync_closer（4星）**：思路明确，代码简洁，使用了自定义函数计算绝对值，逻辑清晰。
- **OLE_OIer（4星）**：思路正确，使用了函数封装字符串差异度的计算，代码结构清晰，且使用了打擂台的方法求最小值。

### 所选题解
- **Engulf（5星）**
    - **关键亮点**：使用 `std::vector` 存储字符串，代码结构清晰，可读性高。
    - **核心代码**：
```cpp
int calc(string a,string b){
    int ans=0;
    for(int i=0;i<a.size();i++){
        int cost=min(abs(a[i]-b[i]),abs(a[i]-b[i])+26);
        ans+=cost;
    }
    return ans;
}

void solve(){
    int n,m;
    cin>>n>>m;
    vector <string> a(n);
    for(auto &i:a)cin>>i;
    int ans=0x3f3f3f3f;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            ans=min(ans,calc(a[i],a[j]));
        }
    }
    cout<<ans<<endl;
}
```
- **5k_sync_closer（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，使用自定义函数计算绝对值。
    - **核心代码**：
```cpp
int f(int x) {return x >= 0? x : -x;}
int T, n, m, q;char s[150][15];
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);q = 1e9;
        for(int i = 1;i <= n;++i) scanf("%s", s[i]);
        for(int i = 1, t;i <= n;++i)
            for(int j = i + 1;j <= n;++j)
            {
                t = 0;
                for(int k = 0;k < m;++k)
                    t += f(s[i][k] - s[j][k]);
                if(t < q) q = t;
            }
        printf("%d\n", q);
    }
    return 0;
}
```
- **OLE_OIer（4星）**
    - **关键亮点**：使用函数封装字符串差异度的计算，代码结构清晰，打擂台求最小值。
    - **核心代码**：
```cpp
int dif(string a,string b){
    int len=a.length(),tot=0;
    for(int i=0;i<len;++i) tot+=abs(a[i]-b[i]);
    return tot;
}
void func(){
    int n,len,minn=1e9;
    cin>>n>>len;
    string s[60];
    for(int i=1;i<=n;++i) cin>>s[i];
    for(int i=1;i<=n;++i){
        for(int j=1;j<i;++j) minn=min(minn,dif(s[i],s[j]));
    }
    cout<<minn<<"\n";
}
```

### 最优关键思路或技巧
- 利用暴力枚举法，在数据范围较小时，简单直接地解决问题。
- 使用函数封装字符串差异度的计算，提高代码的可读性和可维护性。
- 采用打擂台的方法求最小值，避免额外的空间开销。

### 可拓展之处
同类型题目可能会增加数据范围，此时暴力枚举可能会超时，需要考虑更高效的算法，如动态规划、贪心算法等。类似的算法套路包括字符串匹配、编辑距离等问题。

### 洛谷相似题目推荐
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)
- [P1200 [USACO1.1]你的飞碟在这儿Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)

### 个人心得摘录与总结
- **ttq012**：提到不能枚举两个相同的字符串，这是在实现暴力枚举时需要注意的细节，避免重复计算导致结果错误。 

---
处理用时：35.69秒