# 题目信息

# Gas Pipeline

## 题目描述

You are responsible for installing a gas pipeline along a road. Let's consider the road (for simplicity) as a segment $ [0, n] $ on $ OX $ axis. The road can have several crossroads, but for simplicity, we'll denote each crossroad as an interval $ (x, x + 1) $ with integer $ x $ . So we can represent the road as a binary string consisting of $ n $ characters, where character 0 means that current interval doesn't contain a crossroad, and 1 means that there is a crossroad.

Usually, we can install the pipeline along the road on height of $ 1 $ unit with supporting pillars in each integer point (so, if we are responsible for $ [0, n] $ road, we must install $ n + 1 $ pillars). But on crossroads we should lift the pipeline up to the height $ 2 $ , so the pipeline won't obstruct the way for cars.

We can do so inserting several zig-zag-like lines. Each zig-zag can be represented as a segment $ [x, x + 1] $ with integer $ x $ consisting of three parts: $ 0.5 $ units of horizontal pipe + $ 1 $ unit of vertical pipe + $ 0.5 $ of horizontal. Note that if pipeline is currently on height $ 2 $ , the pillars that support it should also have length equal to $ 2 $ units.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/f1dfe38b83de03ccc78e9e23fedbdc3223f970d0.png)Each unit of gas pipeline costs us $ a $ bourles, and each unit of pillar — $ b $ bourles. So, it's not always optimal to make the whole pipeline on the height $ 2 $ . Find the shape of the pipeline with minimum possible cost and calculate that cost.

Note that you must start and finish the pipeline on height $ 1 $ and, also, it's guaranteed that the first and last characters of the input string are equal to 0.

## 说明/提示

The optimal pipeline for the first query is shown at the picture above.

The optimal pipeline for the second query is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/2782d7e4c7012251045217f9f050b1e333f47c33.png)The optimal (and the only possible) pipeline for the third query is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/7e72ed8fa647ff66b04ca0425394c874c1b110fe.png)The optimal pipeline for the fourth query is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1207C/248de9c02a0298296e2131b26213178e9c6ad6ba.png)

## 样例 #1

### 输入

```
4
8 2 5
00110010
8 1 1
00110010
9 100000000 100000000
010101010
2 5 1
00
```

### 输出

```
94
25
2900000000
13
```

# AI分析结果

### 题目内容重写

#### 题目描述

你负责在一条道路上安装天然气管道。为了简化问题，我们将道路视为 $OX$ 轴上的线段 $[0, n]$。道路上可能有多个交叉路口，但为了简化问题，我们将每个交叉路口表示为整数 $x$ 的区间 $(x, x + 1)$。因此，我们可以将道路表示为一个由 $n$ 个字符组成的二进制字符串，其中字符 `0` 表示当前区间没有交叉路口，字符 `1` 表示存在交叉路口。

通常情况下，我们可以在道路上以高度为 $1$ 单位安装管道，并在每个整数点安装支撑柱（因此，如果我们负责 $[0, n]$ 的道路，我们必须安装 $n + 1$ 个支撑柱）。但在交叉路口处，我们需要将管道提升到高度 $2$，以便管道不会阻碍车辆的通行。

我们可以通过插入几个“之”字形线段来实现这一点。每个“之”字形可以表示为整数 $x$ 的线段 $[x, x + 1]$，由三部分组成：$0.5$ 单位的水平管道 + $1$ 单位的垂直管道 + $0.5$ 单位的水平管道。注意，如果管道当前高度为 $2$，支撑它的支柱长度也应为 $2$ 单位。

每单位天然气管道的成本为 $a$ bourles，每单位支柱的成本为 $b$ bourles。因此，并不总是最优的将整个管道都安装在高度 $2$。找到成本最小的管道形状，并计算该成本。

注意，你必须以高度 $1$ 开始和结束管道，并且保证输入字符串的第一个和最后一个字符为 `0`。

### 算法分类
动态规划

### 题解分析与结论

本题的核心是通过动态规划来找到安装管道的最小成本。由于管道的高度在不同位置可能为1或2，且交叉路口处必须为2，因此需要根据当前位置的状态（高度1或2）和前一个位置的状态进行转移。

### 高星题解推荐

#### 题解1：兮水XiShui丶 (5星)
- **关键亮点**：清晰地定义了状态转移方程，并正确处理了交叉路口和非交叉路口的转移逻辑。代码简洁且易于理解。
- **代码核心思想**：
  - 定义 `f[i][j]` 表示铺设到第 `i` 个区域时，高度为 `j` 的最小成本。
  - 根据当前字符是否为 `1` 进行不同的状态转移。
  - 最终输出 `f[n][0]`，即铺设到第 `n` 个区域且高度为1的最小成本。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int oo=(1ll<<62); 
const int N=2e5+10;
int n,a,b;
string s;
int f[N][2];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        cin >> n >> a >> b;
        cin >> s;
        f[0][0] = b;
        f[0][1] = oo;
        for(int i=0;i<n;i++){
            if(s[i]=='0'){
                f[i+1][0] = min(f[i][0],f[i][1] + a) + a + b;
                f[i+1][1] = min(f[i][0] + a , f[i][1]) + a + 2*b;
            }
            else{
                f[i+1][1] = f[i][1] + a + 2*b;
                f[i+1][0] = oo;
            }
        }
        cout << f[n][0] << endl;
    }
    return 0;
}
```

#### 题解2：引领天下 (4星)
- **关键亮点**：详细解释了状态转移的逻辑，并提供了清晰的代码实现。特别强调了交叉路口处高度必须为2的限制。
- **代码核心思想**：
  - 定义 `f[i][j]` 表示到达第 `i` 个位置时，高度为 `j` 的最小成本。
  - 根据当前字符是否为 `1` 进行不同的状态转移。
  - 最终输出 `f[n-1][0] + b`，即铺设到第 `n` 个位置且高度为1的最小成本。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
string s;
#define ll long long
#define inf 884888488848997
ll a,b,f[200005][2];
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>a>>b>>s;
        memset(f,0,sizeof(f));
        f[0][1]=inf;f[0][0]=a+b;
        for (int i=1;i<s.size();i++){
            k=(s[i]=='1');
            if(k){
                f[i][0]=inf;
                f[i][1]=min(f[i-1][0]+2*a+2*b,f[i-1][1]+2*b+a);
            }else{
                f[i][0]=min(f[i-1][0]+a+b,f[i-1][1]+2*a+2*b);
                f[i][1]=min(f[i-1][0]+2*a+b,f[i-1][1]+2*b+a);
            }
        }
        cout<<f[n-1][0]+b<<endl;
    }
}
```

#### 题解3：Ericby666 (4星)
- **关键亮点**：简洁明了地定义了状态转移方程，并正确处理了交叉路口和非交叉路口的转移逻辑。代码实现清晰。
- **代码核心思想**：
  - 定义 `dp[i][j]` 表示到第 `i` 个位置时，高度为 `j` 的最小成本。
  - 根据当前字符是否为 `1` 进行不同的状态转移。
  - 最终输出 `dp[n][0]`，即铺设到第 `n` 个位置且高度为1的最小成本。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,dp[200005][2];
string s;
signed main(){
    scanf("%lld",&t);
    while(t--){
        int n,a,b;
        scanf("%lld%lld%lld",&n,&a,&b);
        cin>>s;
        dp[0][0]=b;
        dp[0][1]=1e18;
        for(int i=0;i<n;i++){
            if(s[i]=='0'){
                dp[i+1][0]=min(dp[i][0],dp[i][1]+a)+a+b;
                dp[i+1][1]=min(dp[i][1],dp[i][0]+a)+a+b*2;
            }
            else{
                dp[i+1][1]=dp[i][1]+a+b*2;
                dp[i+1][0]=1e18;
            }
        }
        printf("%lld\n",dp[n][0]);
    }
    return 0;
}
```

### 最优关键思路与技巧
- **状态定义**：使用二维数组 `dp[i][j]` 表示到第 `i` 个位置时，高度为 `j` 的最小成本。
- **状态转移**：根据当前字符是否为 `1` 进行不同的状态转移，确保在交叉路口处高度必须为2。
- **边界处理**：初始化 `dp[0][0]` 为 `b`，表示从高度1开始，且第一个支撑柱的成本为 `b`。

### 拓展思路
- **类似题目**：可以考虑其他需要根据状态转移的动态规划问题，如路径规划、资源分配等。
- **优化**：可以通过滚动数组优化空间复杂度，减少内存使用。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

---
处理用时：56.55秒