# 题目信息

# Three Blocks Palindrome (hard version)

## 题目描述

The only difference between easy and hard versions is constraints.

You are given a sequence $ a $ consisting of $ n $ positive integers.

Let's define a three blocks palindrome as the sequence, consisting of at most two distinct elements (let these elements are $ a $ and $ b $ , $ a $ can be equal $ b $ ) and is as follows: $ [\underbrace{a, a, \dots, a}_{x}, \underbrace{b, b, \dots, b}_{y}, \underbrace{a, a, \dots, a}_{x}] $ . There $ x, y $ are integers greater than or equal to $ 0 $ . For example, sequences $ [] $ , $ [2] $ , $ [1, 1] $ , $ [1, 2, 1] $ , $ [1, 2, 2, 1] $ and $ [1, 1, 2, 1, 1] $ are three block palindromes but $ [1, 2, 3, 2, 1] $ , $ [1, 2, 1, 2, 1] $ and $ [1, 2] $ are not.

Your task is to choose the maximum by length subsequence of $ a $ that is a three blocks palindrome.

You have to answer $ t $ independent test cases.

Recall that the sequence $ t $ is a a subsequence of the sequence $ s $ if $ t $ can be derived from $ s $ by removing zero or more elements without changing the order of the remaining elements. For example, if $ s=[1, 2, 1, 3, 1, 2, 1] $ , then possible subsequences are: $ [1, 1, 1, 1] $ , $ [3] $ and $ [1, 2, 1, 3, 1, 2, 1] $ , but not $ [3, 2, 3] $ and $ [1, 1, 1, 1, 2] $ .

## 样例 #1

### 输入

```
6
8
1 1 2 2 3 2 1 1
3
1 3 3
4
1 10 10 1
1
26
2
2 1
3
1 1 1```

### 输出

```
7
2
4
1
1
3```

# AI分析结果

### 题目内容（中文重写）
# 三个块的回文（困难版本）

## 题目描述
简单版本和困难版本的唯一区别在于数据范围。

给定一个由 $n$ 个正整数组成的序列 $a$。

我们将三个块的回文序列定义为：最多由两个不同元素（设这两个元素为 $a$ 和 $b$，$a$ 可以等于 $b$）组成，形式为 $ [\underbrace{a, a, \dots, a}_{x}, \underbrace{b, b, \dots, b}_{y}, \underbrace{a, a, \dots, a}_{x}] $ 的序列。其中 $x$ 和 $y$ 是大于或等于 $0$ 的整数。例如，序列 $ [] $、$ [2] $、$ [1, 1] $、$ [1, 2, 1] $、$ [1, 2, 2, 1] $ 和 $ [1, 1, 2, 1, 1] $ 都是三个块的回文序列，但 $ [1, 2, 3, 2, 1] $、$ [1, 2, 1, 2, 1] $ 和 $ [1, 2] $ 不是。

你的任务是从序列 $a$ 中选择一个长度最大的子序列，使其为三个块的回文序列。

你需要回答 $t$ 个独立的测试用例。

回顾一下，如果序列 $t$ 可以通过从序列 $s$ 中移除零个或多个元素而不改变剩余元素的顺序得到，那么序列 $t$ 就是序列 $s$ 的一个子序列。例如，如果 $s=[1, 2, 1, 3, 1, 2, 1]$，那么可能的子序列有：$ [1, 1, 1, 1] $、$ [3] $ 和 $ [1, 2, 1, 3, 1, 2, 1] $，但 $ [3, 2, 3] $ 和 $ [1, 1, 1, 1, 2] $ 不是。

## 样例 #1

### 输入
```
6
8
1 1 2 2 3 2 1 1
3
1 3 3
4
1 10 10 1
1
26
2
2 1
3
1 1 1
```

### 输出
```
7
2
4
1
1
3
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是利用数据范围中 $a_i$ 值域较小（$a_i \le 200$）的特点，通过枚举的方式来找到最长的三个块回文子序列。具体做法是先记录每个数出现的位置和前缀和，然后枚举外层元素 $a$ 及其出现次数 $x$，确定两端 $a$ 的位置，再枚举中间元素 $b$，计算中间 $b$ 的最大出现次数，最后更新答案。

各题解的差异主要体现在代码实现方式和细节处理上，如使用 `vector` 或链式前向星来记录位置，以及前缀和数组的更新方式等。但整体的算法框架和时间复杂度是相似的。

### 所选题解
- **作者：_byta（5星）**
  - **关键亮点**：思路清晰，代码简洁，利用 `vector` 记录每个数出现的位置和次数，通过前缀和数组快速计算区间内元素的出现次数，在统计答案时，对原数组每个数进行处理，找到以其为中心断开时的最大值。
- **作者：Eibon（4星）**
  - **关键亮点**：同样利用 `vector` 记录位置和前缀和数组，逻辑清晰，通过枚举每个位置，找到后缀次数相同的位置，再枚举中间元素，更新答案。
- **作者：奇米（4星）**
  - **关键亮点**：提供了两种写法，一种是常规的前缀和处理，另一种使用链式前向星优化内存，思路详细，代码实现较为完整。

### 重点代码
#### _byta 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int z=200;
int n,m,a[200001],b[200001][201];
vector<int>v[201];// v 存某一个数 ai 到 i 出现的次数以及出现到这个次数的位置 
void solve()
{
    cin >> n;
    for(int i=1; i<=z ;i++)v[i].clear();
    int ans=0;
    for(int i=1; i<=n ;i++)
    {
        cin >> a[i];
        v[a[i]].push_back(i);
        for(int j=1; j<=z ;j++)
        {
            b[i][j]=b[i-1][j];
        }
        b[i][a[i]]++;
        ans=max(ans,b[i][a[i]]);
    }
    for(int i=1; i<=n ;i++)
    {
        int f=b[i][a[i]];
        int l=i;
        int r=v[a[i]][v[a[i]].size()-f];
        if(r<=l) continue;
        for(int j=1; j<=z ;j++)
        {
            ans=max(ans,b[r-1][j]-b[l][j]+f*2);
        }
    }
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }
}
```
**核心实现思想**：先读取输入，使用 `vector` 记录每个数出现的位置，同时更新前缀和数组 `b`。然后枚举每个位置，找到以该位置的数为外层元素时，中间元素的最大出现次数，更新答案。

#### Eibon 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
const int maxn=2e5+5;
int T,n,ans;
int a[maxn],num[maxn][205];
vector<int>v[205];
signed main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        ans=1;
        for(int i=1;i<=200;i++){
            v[i].clear();
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            v[a[i]].push_back(i);
            for(int j=1;j<=200;j++){
                if(a[i]==j){
                    num[i][j]=num[i-1][j]+1;
                }
                else{
                    num[i][j]=num[i-1][j];
                }
                ans=max(ans,num[i][j]);
            }
        }
        for(int i=1;i<=n;i++){
            int m=num[i][a[i]];
            int k=v[a[i]][v[a[i]].size()-m];
            if(k<=i){
                continue;
            }
            for(int j=1;j<=200;j++){
                ans=max(ans,num[k-1][j]-num[i][j]+m*2);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：与 _byta 的思路类似，先初始化 `vector` 和前缀和数组，读取输入并更新信息。然后枚举每个位置，找到后缀次数相同的位置，再枚举中间元素，更新答案。

#### 奇米的代码（写法 1）
```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
    int sum=0,ff=1; char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') ff=-1;
        ch=getchar();
    }
    while(isdigit(ch))
        sum=sum*10+(ch^48),ch=getchar();
    return sum*ff;
}

const int N=2e5+5;

int n,m,f[N][205],g[N][205],a[N],pre[205][N],suf[205][N],ans;

int main()
{
    int Q=read();
    for (;Q--;)
    {
        n=read();
        for ( int i=1;i<=n;i++ )
        {
            a[i]=read();
            for ( int j=1;j<=200;j++ ) f[i][j]=f[i-1][j];
            f[i][a[i]]++;
            pre[a[i]][f[i][a[i]]]=i;
        }
        for ( int i=n;i>=1;i-- ) 
        {
            for ( int j=1;j<=200;j++ ) g[i][j]=g[i+1][j];
            g[i][a[i]]++;
            suf[a[i]][g[i][a[i]]]=i;
        }
        for ( int i=1;i<=200;i++ ) 
        {
            for ( int j=1;j<=f[n][i]/2;j++ ) 
            {
                int pos1=pre[i][j];
                int pos2=suf[i][j];	
                if(pos1>pos2) continue;
                for ( int k=1;k<=200;k++ ) 
                {
                    if(k==i) continue;
                    ans=max(ans,j*2+f[pos2][k]-f[pos1][k]);
                }
//				if(ans==4) cout<<i<<" "<<j<<" "<<pos1<<" "<<pos2<<endl;
            }
            ans=max(ans,f[n][i]);
        }
        printf("%d\n",ans);
        ans=0;
        for ( int i=1;i<=n;i++ ) 
            for ( int j=1;j<=200;j++ ) 
            {
                f[i][j]=g[i][j]=0;
                pre[j][i]=suf[j][i]=0;
            }
    }
    return 0;
}
```
**核心实现思想**：先读取输入，分别计算前缀和后缀的元素出现次数，记录每个数出现到特定次数的位置。然后枚举外层元素和其出现次数，确定两端位置，再枚举中间元素，更新答案。

### 关键思路或技巧
- **利用值域小的特点**：由于 $a_i$ 的值域较小（$a_i \le 200$），可以通过枚举外层元素和中间元素来找到最长的三个块回文子序列。
- **前缀和数组**：使用前缀和数组可以快速计算区间内元素的出现次数，时间复杂度为 $O(1)$。
- **记录位置**：使用 `vector` 或其他数据结构记录每个数出现的位置，方便确定两端元素的位置。

### 拓展思路
同类型题或类似算法套路：
- 其他需要枚举元素并计算区间信息的题目，可以借鉴前缀和数组的思想，快速计算区间内元素的出现次数或其他统计信息。
- 对于数据范围较小的题目，可以考虑通过枚举的方式来解决问题。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：涉及前缀和和枚举的思想，通过枚举子段的起点和终点，利用前缀和快速计算子段和。
- [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)：同样需要枚举矩形的边界，利用前缀和计算矩形内元素的和。
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)：可以通过枚举元素和位置，结合前缀和来解决问题。

### 个人心得
- **suxxsfe**：赛时写出了 E2 的做法，但是算错复杂度，导致以为自己的做法只能 AC E1，就没交到 E2 上，然后赛后秒 A。这提醒我们在比赛中要准确计算复杂度，不要轻易放弃自己的思路。

---
处理用时：80.72秒