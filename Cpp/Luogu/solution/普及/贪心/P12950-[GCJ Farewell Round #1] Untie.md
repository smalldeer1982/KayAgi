# [GCJ Farewell Round #1] Untie

## 题目描述

一群人围坐成一圈，正在玩一个特殊版本的石头剪刀布游戏。在这个游戏中，每个人秘密选择石头、布或剪刀，然后所有人同时向其他人展示自己的选择。每个人会将自己的选择与左右两位邻居进行比较，可能分别对每位邻居获胜、落败或平局。只有当两人选择相同时才会出现平局。

你希望调整游戏结果，使得没有任何相邻两人出现平局。对于每位玩家，你可以选择保留其原有选择，或者要求他们更改为另外两个选项中的任意一个（由你决定改为哪个）。为了确保在调整后所有相邻玩家的选择都不相同，最少需要改变多少人的选择？

## 说明/提示

**样例解释**

在样例 #1 中，存在一对相邻玩家都选择布（输入的首尾字符），以及另一对相邻玩家都选择剪刀。因此至少需要两次改变。其中一种实现方式是：将最左侧的布改为剪刀，最右侧的剪刀改为石头，得到 SRSRP。

在样例 #2 中，所有 7 位参与者都选择了石头。如果最多改变 3 次选择，那么至少会剩下 4 个石头，其中至少有两个是相邻的。因此最少需要改变 4 次。其中一种实现方式是得到 PRSRPRS。

在样例 #3 中，没有任何相邻玩家出现平局，因此不需要改变。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $\mathbf{C}$ 的每个字符都是大写字母 $\mathbf{R}$、$\mathbf{P}$ 或 $\mathbf{S}$。

**测试集 1（9 分，可见判定）**
- $3 \leq \mathbf{C}$ 的长度 $\leq 10$。

**测试集 2（20 分，可见判定）**
- $3 \leq \mathbf{C}$ 的长度 $\leq 1000$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
PRSSP
RRRRRRR
RSPRPSPRS```

### 输出

```
Case #1: 2
Case #2: 4
Case #3: 0```

# 题解

## 作者：T7_Daniel (赞：4)

## 题目大意(`AC` 后总结的)

给定你一个长度为 $n$ 的环，每个环上有一个颜色，初始已经有颜色了，你可以花费 $1$ 的费用将一个地方的颜色变化。

要求相邻的节点颜色不相同，问至少需要多少费用？

因为这种问题用染色描述更清晰，以下均用颜色称呼，请自行转换一下。

## 思路分析

我们定义 $n$ 为 $C$ 的长度。

按照经验，无论是什么算法，对于当前的颜色，都是需要存储的，也就是说，我们的算法的常数会在 $3$ 以上，甚至如果实现差的话，这个常数还会更大。

这就要求我们的核心算法要尽量做到线性或者单 $log$，显然，染色问题通常使用贪心或者 dp，不可能会出现 $log$。

我考虑的是 dp。

考虑到使用 $dp[i][1/2/3]$ 代表将前 $i$ 人处理好，并让第 $i$ 人选择石头，剪刀，布的最少改变次数。这是一个很经典的状态设计。

转移的设计也是很经典的——我们先枚举第一个色块的颜色情况，然后为 $dp[1][x]$ 赋不同的初值，在此基础下，对其他地方进行转移。

这个转移方法有点状态压缩的味道，但实际上不是：我们进行两次枚举，一次枚举当前状态，另一次枚举上一次状态，比较其是否相同，如果不相同，取更小值 $minn$。

然后在 $minn$ 的基础上，我们再加上当前节点的对应颜色是否需要付出代价。听起来可能有点绕，但是打起来还是很简单的。

## 代码实现

来吧，知道你们想看的是这个。

代码中有注释，可以辅助理解。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;
int dp[N][5];//dp[i][1/2/3]代表将前i人处理好，并让第i人选择Rock,Paper,Scissor的最少改变次数 
int a[N];//初始选择 
int n;

//inline void output(){
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=3;j++) cout<<dp[i][j]<<" ";
//		cout<<"\n";
//	}
//}

inline int getnum(int x){//处理第一人选择颜色x
	memset(dp,0x3f,sizeof dp);//赋为极大值，防止出现影响  
	dp[1][x]=((a[1]==x)?0:1);//处理一开始需不需要改变 
	for(int i=2;i<=n;i++){//这里先不考虑环，下面再考虑 
		for(int b=1;b<=3;b++){//当前状态 
		    int minn=2e9;
			for(int c=1;c<=3;c++)//前一状态 
				if(b!=c) minn=min(minn,dp[i-1][c]);//更新前面的最小值 
			dp[i][b]=minn+((a[i]==b)?0:1);//minn是前面的信息，位运算计算的是这一位的信息 
		}
	}
//	output();
	int res=2e9; 
	for(int j=1;j<=3;j++)
		if(x!=j) res=min(res,dp[n][j]);//如果出的不一样，记录答案，这里是在处理环 
    return res;
}

int main(){
    int T;cin>>T;
    int now=0;//测试数据组数 
    while(T--){
    	now++;
    	string s;cin>>s;
    	n=s.size();
    	s=" "+s;//处理为1~s.size()
    	for(int i=1;i<=n;i++){//处理初始选择 
    		if(s[i]=='R') a[i]=1;
    		else if(s[i]=='P') a[i]=2;
    		else a[i]=3;
		}
    	int ans=2e9;
    	for(int i=1;i<=3;i++)
    		ans=min(ans,getnum(i));//处理第一人选择i时的答案
		printf("Case #%d: %d\n",now,ans);
	}
	return 0;
}
```

---

## 作者：iChen (赞：1)

动态规划好题。

### 形式化题意
给一个字符串 $s$，首尾相连形成一个环，由 $R$，$P$，$S$ 三种字符组成。现在要使 $s$ 中没有任意两个相邻的字符相同，至少要改变几个字符？
### 状态设计
由于是一个一维字符串，并且每个字符仅与相邻的两个字符有关，于是想到线性动规。

常规地，需要有一维 $i$，表示考虑到了第 $i$ 个字符。考虑到此字符需要与左右两个字符不同，并且仅有 $3$ 种不同的字符，所以想到设计第二维 $j$ 取 $[0, 2]$，分别表示 $3$ 种不同的字符。

### 转移方程

首先，因为两个相邻的字符不能相同，所以 $dp_{i, j}$ 不能从 $dp_{i - 1, j}$ 转移。

那么就需要从另外两种字符转移：

$dp_{i, j} = min_{0 \le k \le 2, k\not=j}\{dp_{i - 1, k}\}$

另外，如果当前考虑的此字符与原字符串中字符不同（$j \not= s[i]$），代表需要改变此字符，所以需要加一。

最终还需要考虑第 $n$ 个字符与第 $1$ 个字符间的关系，复制第 $1$ 个字符到字符串尾即可。

### Accepted Code
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

constexpr int INF = 0x3f3f3f3f;
constexpr int N = 1e3 + 5;
int T, len, idx;
string s;

inline void solve() {
    cin >> s;
    len = s.size();
    int a[N] = {0};
    for (int i = 0; i < len; ++i) {
        if (s[i] == 'R') a[i] = 0;
        else if (s[i] == 'P') a[i] = 1;
        else a[i] = 2;
    }
    
    int ans = INF;
    for (int first = 0; first < 3; ++ first) {
        int dp[N][3];
        memset(dp, 0x3f, sizeof(dp));
        dp[0][first] = (first == a[0] ? 0 : 1);
        
        for (int i = 1; i < len; ++ i) {
            for (int c = 0; c < 3; ++ c) {
                int cost = (c == a[i] ? 0 : 1);
                for (int p = 0; p < 3; ++ p) {
                    if (p == c) continue;
                    dp[i][c] = min(dp[i][c], dp[i - 1][p] + cost);
                }
            }
        }
        
        for (int c = 0; c < 3; ++ c) {
            if (c == first) continue;
            ans = min(ans, dp[len - 1][c]);
        }
    }
    
    printf("Case #%d: %d\n", ++ idx, ans);
}

int main() {
    scanf("%d", &T);
    while (T --) solve();
    return 0;
}
```

求个赞

---

## 作者：guoshengyu1231 (赞：1)

# 题意简述
给定一个字符串，仅包含三种字符。你需要将其若干个字符进行修改，使其任意两个连续的字符和首尾的两个字符都不相同，问最少需要修改多少次。
# 思路
不难发现这题可以使用动态规划，那既然是动态规划，那三要素可不能少。
## 状态
首先第一个状态必然是目前已经枚举到的字符数，其次不难想到，状态的转移必然与前一个字符有关。所以可以得出状态 $dp_{i,c}$ 表示修改前 $ i $ 字符时，第 $ i $ 个字符改为 $c$（$\texttt{R}$、$\texttt{S}$、$\texttt{P}$）时需要的最小次数。
## 边界
由于还需要考虑首尾的情况，所以不妨我们分类讨论，对于第 $1$ 个位置改为三种字符的情况分别填充一次 $dp$ 数组。这里我们不妨假设第一个字符改为字符 $\texttt{R}$，所以 $dp_{1,\texttt{R}}=[s_1\ne \texttt{R}]$。
## 转移
因为我们需要满足改完后的 $s_i\ne s_{i-1}$ 所以肯定是从不相等的转移而来。具体的，设 $j$ 为 $s_i$ 需要改成的字符，在设 $l$ 为 $s_{i-1}$ 需要改成的字符。那必然需要满足 $j\ne l$，如果 $j\ne l$，那么便可以得到转移费用 $cost=\min\{dp_{i-1,l}\}$。则 $dp_{i,j}=[s_i\ne j]+cost$。  $\\$  
差不多这些就是主要部分了，具体的细节可以看代码注释。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
int dp[maxn][3],n;
int a[maxn];
int get(char c)//将字符转化成对应的数字
{
	if(c=='R') return 0;
	if(c=='S') return 1;
	if(c=='P') return 2;
}
void make_dp(int k)
{
	//cout<<"_____DP_____\n";
	dp[0][k]=(a[0]!=k);//初始化
	//for(int i=0;i<3;i++) cout<<dp[0][i]<<' ';
	//cout<<"\n";
	for(int i=1;i<n;i++)
	 {
	 	for(int j=0;j<3;j++)
	  	 {
	  		dp[i][j]=(a[i]!=j);
	  		int cost=maxn;
	  		for(int l=0;l<3;l++)
	  	 	 if(j!=l) cost=min(cost,dp[i-1][l]);
	  		dp[i][j]+=cost;
	  		//cout<<dp[i][j]<<' ';
	  	 }
	  	//cout<<"\n";
	 }
	 
}
int solve(string s)
{
	int ans=maxn;
	n=s.size();
	for(int i=0;i<n;i++) a[i]=get(s[i]);//转化成数字
	for(int i=0;i<3;i++)
	 {
	 	memset(dp,0x3f,sizeof dp);	
		make_dp(i);//填充dp表
		for(int j=0;j<3;j++)
		 if(i!=j) ans=min(ans,dp[n-1][j]);//枚举可行的结尾
	 }
	return ans;
}
int main()
{
	int T;cin>>T;
	for(int i=1;i<=T;i++)
	 {
	 	string s;cin>>s;
	 	printf("Case #%d: %d\n",i,solve(s));
	 }
	return 0;
}
```

---

