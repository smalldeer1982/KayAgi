# 题目信息

# Shuffling Songs

## 题目描述

Vladislav 有一个由 $n$ 首歌组成的播放列表，编号从 $1$ 到 $n$。歌曲 $i$ 属于流派 $g_i$ 并由作者 $w_i$ 创作。他希望以这样一种方式制作播放列表：每对相邻的歌曲要么有相同的作者，要么属于相同的流派（或两者兼有）。他称这样的播放列表为激动人心的。 $g_i$ 和 $w_i$ 都是长度不超过 $10^4$ 的字符串。

但是有可能不总是能使用所有歌曲制作出激动人心的播放列表，因此洗牌过程分为两步。首先，移除一些数量（可能为零）的歌曲，然后重新排列剩余的歌曲使播放列表激动人心。

由于 Vladislav 不喜欢从他的播放列表中移除歌曲，他希望尽可能少地进行移除。帮助他找出为了能重新排列剩余歌曲使播放列表激动人心而需要进行的最少移除数量。

## 样例 #1

### 输入

```
4
1
pop taylorswift
4
electronic themotans
electronic carlasdreams
pop themotans
pop irinarimes
7
rap eminem
rap drdre
rap kanyewest
pop taylorswift
indierock arcticmonkeys
indierock arcticmonkeys
punkrock theoffspring
4
a b
c d
e f
g h```

### 输出

```
0
0
4
3```

# AI分析结果

### 题目内容重写
# 洗牌歌曲

## 题目描述

Vladislav 有一个由 $n$ 首歌组成的播放列表，编号从 $1$ 到 $n$。歌曲 $i$ 属于流派 $g_i$ 并由作者 $w_i$ 创作。他希望以这样一种方式制作播放列表：每对相邻的歌曲要么有相同的作者，要么属于相同的流派（或两者兼有）。他称这样的播放列表为激动人心的。 $g_i$ 和 $w_i$ 都是长度不超过 $10^4$ 的字符串。

但是有可能不总是能使用所有歌曲制作出激动人心的播放列表，因此洗牌过程分为两步。首先，移除一些数量（可能为零）的歌曲，然后重新排列剩余的歌曲使播放列表激动人心。

由于 Vladislav 不喜欢从他的播放列表中移除歌曲，他希望尽可能少地进行移除。帮助他找出为了能重新排列剩余歌曲使播放列表激动人心而需要进行的最少移除数量。

## 样例 #1

### 输入

```
4
1
pop taylorswift
4
electronic themotans
electronic carlasdreams
pop themotans
pop irinarimes
7
rap eminem
rap drdre
rap kanyewest
pop taylorswift
indierock arcticmonkeys
indierock arcticmonkeys
punkrock theoffspring
4
a b
c d
e f
g h```

### 输出

```
0
0
4
3```

### 题解分析与结论

本题的核心是通过状态压缩动态规划（状压DP）来解决，主要难点在于如何高效地表示歌曲的选择状态，并在此基础上进行状态转移。由于 $n \leq 16$，状压DP是可行的解决方案。各题解基本都采用了这一思路，但在实现细节和优化上有所不同。

### 所选高分题解

#### 1. 作者：spire001 (★★★★☆)
**关键亮点**：
- 使用哈希表优化字符串比较，减少常数时间。
- 详细解释了状态转移方程，逻辑清晰。
- 代码结构清晰，初始化与状态转移部分分离，便于理解。

**核心代码**：
```cpp
bool dp[N][1 << N];
int n, tot;

inline int getid(string &s) {
    return hs[s] ? hs[s] : hs[s] = ++tot;
}

void solve() {
    hs.clear();
    memset(dp, 0, sizeof dp);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        string x, y;
        cin >> x >> y;
        a[i] = getid(x);
        b[i] = getid(y);
    }
    const int x = 1 << n;
    for(int i = 1; i <= n; i++) dp[i][1 << (i - 1)] = true;
    for(int i = 0; i != x; i++) 
        for(int j = 1; j <= n; j++) 
            if(i & (1 << (j - 1)) && dp[j][i]) 
                for(int p = 1; p <= n; p++) 
                    if(!(i & (1 << (p - 1)))) 
                        if(a[p] == a[j] || b[p] == b[j]) 
                            dp[p][i | (1 << (p - 1))] = true;
    int ans = n;
    for(int i = 0; i != x; i++) 
        for(int j = 1; j <= n; j++) 
            if(dp[j][i]) 
                ans = min(ans, n - __builtin_popcount(i));
    cout << ans << '\n';
}
```

#### 2. 作者：zhuweiqi (★★★★☆)
**关键亮点**：
- 使用 `map` 进行字符串离散化，简化比较操作。
- 状态转移方程清晰，代码简洁。
- 初始化部分处理得当，避免无效状态。

**核心代码**：
```cpp
int f[1<<16][16];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n,cnt=0,ans=1;
        cin>>n;
        p.clear();
        for(int i=0;i<n;i++){
            string x,y;
            cin>>x>>y;
            if(!p[x]) p[x]=++cnt;
            if(!p[y]) p[y]=++cnt;
            a[i]=p[x],b[i]=p[y];
        }
        for(int i=0;i<(1<<n);i++){
            for(int j=0;j<n;j++){
                if(((i>>j)&1)==0) f[i][j]=-1e9;
                else if((i&(i-1))==0) f[i][j]=1;
                else f[i][j]=-1e9;
            }
        }
        for(int i=0;i<(1<<n);i++){
            for(int j=0;j<n;j++){
                if(f[i][j]<0) continue;
                ans=max(ans,f[i][j]);
                for(int k=0;k<n;k++){
                    if(((i>>k)&1)==0 && (a[k]==a[j] || b[k]==b[j])){
                        f[i|(1<<k)][k]=max(f[i|(1<<k)][k],f[i][j]+1);
                    }
                }
            }
        }
        cout<<n-ans<<"\n";
    }
    return 0;
}
```

#### 3. 作者：Gapple (★★★★☆)
**关键亮点**：
- 使用 `hash<string>` 进行字符串离散化，简化比较操作。
- 状态转移方程清晰，代码结构简洁。
- 初始化部分处理得当，避免无效状态。

**核心代码**：
```cpp
vector<vector<int>> dp(1 << n, vector(n, 0));
for(int i = 0; i < n; ++i)
    dp[1 << i][i] = 1;
for(int i = 1; i < (1 << n); ++i) {
    for(int j = 0; j < n; ++j) {
        if((i & (1 << j)) == 0) continue;
        for(int k = 0; k < n; ++k) {
            if(i & (1 << k) || songs[j] != songs[k]) continue;
            dp[i | (1 << k)][k] = max(dp[i | (1 << k)][k], dp[i][j] + 1);
        }
    }
}
int ans = n - 1;
for(const auto& each : dp)
    ans = min(ans, n - reduce(each.begin(), each.end(), 0, [](int x, int y) { return max(x, y); }));
cout << ans << '\n';
```

### 最优关键思路与技巧
1. **状态压缩DP**：利用二进制位表示歌曲的选择状态，通过位运算进行状态转移。
2. **字符串离散化**：通过哈希表或 `map` 将字符串转换为整数，简化比较操作。
3. **初始化与状态转移分离**：确保状态转移前的初始化处理得当，避免无效状态。

### 可拓展之处
- **类似题目**：可以扩展到其他需要状态压缩的问题，如旅行商问题（TSP）、子集选择问题等。
- **优化技巧**：在状态压缩DP中，可以通过预处理、剪枝等技巧进一步优化时间复杂度。

### 推荐题目
1. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)
2. [P1171 售货员的难题](https://www.luogu.com.cn/problem/P1171)
3. [P1896 [SCOI2005]互不侵犯](https://www.luogu.com.cn/problem/P1896)

---
处理用时：58.16秒