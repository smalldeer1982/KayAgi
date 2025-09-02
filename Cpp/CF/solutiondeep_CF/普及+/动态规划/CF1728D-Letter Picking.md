# 题目信息

# Letter Picking

## 题目描述

Alice and Bob are playing a game. Initially, they are given a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string is even. Each player also has a string of their own, initially empty.

Alice starts, then they alternate moves. In one move, a player takes either the first or the last letter of the string $ s $ , removes it from $ s $ and prepends (adds to the beginning) it to their own string.

The game ends when the string $ s $ becomes empty. The winner is the player with a lexicographically smaller string. If the players' strings are equal, then it's a draw.

A string $ a $ is lexicographically smaller than a string $ b $ if there exists such position $ i $ that $ a_j = b_j $ for all $ j < i $ and $ a_i < b_i $ .

What is the result of the game if both players play optimally (e. g. both players try to win; if they can't, then try to draw)?

## 说明/提示

One of the possible games Alice and Bob can play in the first testcase:

1. Alice picks the first letter in $ s $ : $ s= $ "orces", $ a= $ "f", $ b= $ "";
2. Bob picks the last letter in $ s $ : $ s= $ "orce", $ a= $ "f", $ b= $ "s";
3. Alice picks the last letter in $ s $ : $ s= $ "orc", $ a= $ "ef", $ b= $ "s";
4. Bob picks the first letter in $ s $ : $ s= $ "rc", $ a= $ "ef", $ b= $ "os";
5. Alice picks the last letter in $ s $ : $ s= $ "r", $ a= $ "cef", $ b= $ "os";
6. Bob picks the remaining letter in $ s $ : $ s= $ "", $ a= $ "cef", $ b= $ "ros".

Alice wins because "cef" &lt; "ros". Neither of the players follows any strategy in this particular example game, so it doesn't show that Alice wins if both play optimally.

## 样例 #1

### 输入

```
2
forces
abba```

### 输出

```
Alice
Draw```

# AI分析结果

### 题目内容重写
# 字母选择

## 题目描述

Alice和Bob在玩一个游戏。初始时，他们被给定一个非空字符串$s$，由小写拉丁字母组成。字符串的长度为偶数。每个玩家也有一个自己的字符串，初始为空。

Alice先开始，然后他们轮流行动。在一次行动中，玩家可以选择字符串$s$的第一个或最后一个字母，将其从$s$中移除，并将其添加到自己的字符串的最前面。

当字符串$s$变为空时，游戏结束。拥有字典序较小字符串的玩家获胜。如果两个玩家的字符串相等，则为平局。

字符串$a$字典序小于字符串$b$，如果存在一个位置$i$，使得对于所有$j < i$，$a_j = b_j$，并且$a_i < b_i$。

如果两个玩家都采取最优策略（即都试图获胜；如果不能，则试图平局），游戏的结果是什么？

## 说明/提示

在第一组测试用例中，Alice和Bob可能的一种游戏过程如下：

1. Alice选择$s$的第一个字母：$s=$ "orces"，$a=$ "f"，$b=$ "";
2. Bob选择$s$的最后一个字母：$s=$ "orce"，$a=$ "f"，$b=$ "s";
3. Alice选择$s$的最后一个字母：$s=$ "orc"，$a=$ "ef"，$b=$ "s";
4. Bob选择$s$的第一个字母：$s=$ "rc"，$a=$ "ef"，$b=$ "os";
5. Alice选择$s$的最后一个字母：$s=$ "r"，$a=$ "cef"，$b=$ "os";
6. Bob选择$s$中剩余的字母：$s=$ "", $a=$ "cef"，$b=$ "ros"。

Alice获胜，因为"cef" < "ros"。在这个例子中，玩家没有遵循任何策略，因此它不能说明如果双方都采取最优策略，Alice会获胜。

## 样例 #1

### 输入

```
2
forces
abba```

### 输出

```
Alice
Draw```

### 题解分析与结论

本题是一个典型的博弈论问题，结合了区间DP的思想。各题解的思路主要集中在如何通过区间DP来判断Alice和Bob在最优策略下的胜负情况。以下是各题解的要点对比：

1. **区间DP与博弈论结合**：大多数题解都采用了区间DP的思路，通过定义$dp_{l,r}$来表示区间$[l,r]$的胜负情况，Alice和Bob分别选择最优策略来最大化或最小化结果。
2. **状态转移**：题解中普遍提到，Alice和Bob的选择会影响后续的DP状态，因此需要枚举Alice和Bob的选择，并根据选择的结果来更新DP状态。
3. **平局判断**：部分题解特别强调了平局的判断条件，即当Alice和Bob的选择无法改变结果时，游戏结果为平局。
4. **优化与简化**：部分题解通过观察发现Bob不可能获胜，因此只需判断Alice是否获胜或平局，从而简化了问题。

### 精选题解

#### 题解1：作者：MoyunAllgorithm (赞：15)
**星级：4.5**
**关键亮点**：
- 通过观察发现Bob不可能获胜，只需判断Alice是否获胜或平局。
- 提出了判断平局的条件，即字符串是回文、两两重复或回文套两两重复时，平局。
- 代码简洁，时间复杂度为$O(N)$。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,N;
char s[2005];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s+1);
        int N=strlen(s+1);
        int l=1,r=N;
        while(l<r&&s[l]==s[r]) l++,r--;
        if(l>=r)
        {
            puts("Draw");
            continue;
        }
        bool flag=1;
        for(int i=l;i+1<=r;i+=2)
        {
            if(s[i]!=s[i+1]) flag=0;
        }
        puts(flag?"Draw":"Alice");
    }
    return 0;
}
```

#### 题解2：作者：DaiRuiChen007 (赞：10)
**星级：4.0**
**关键亮点**：
- 使用区间DP，定义$dp_{l,r}$表示区间$[l,r]$的胜负情况。
- 通过枚举Alice和Bob的选择，更新DP状态。
- 代码清晰，时间复杂度为$O(N^2)$。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2001;
char s[MAXN];
int dp[MAXN][MAXN];
inline int comb(char x,char y) {
	if(x>y) return 1;
	if(x<y) return -1;
	return 0;
}
inline void solve() {
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<n;++i) dp[i][i+1]=(s[i]==s[i+1])?0:1;
	for(int len=4;len<=n;len+=2) {
		for(int l=1,r=len;r<=n;++l,++r) {
			dp[l][r]=-1;
			int f1=dp[l+2][r]==0?comb(s[l],s[l+1]):dp[l+2][r];
			int f2=dp[l+1][r-1]==0?comb(s[l],s[r]):dp[l+1][r-1];
			int f3=dp[l][r-2]==0?comb(s[r],s[r-1]):dp[l][r-2];
			int f4=dp[l+1][r-1]==0?comb(s[r],s[l]):dp[l+1][r-1];
			dp[l][r]=max(min(f1,f2),min(f3,f4));
		}
	}
	if(dp[1][n]==1) puts("Alice");
	if(dp[1][n]==0) puts("Draw");
	if(dp[1][n]==-1) puts("Bob");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

#### 题解3：作者：pineappler (赞：7)
**星级：4.0**
**关键亮点**：
- 将Alice和Bob的各一步操作看成一个整体，简化了状态转移。
- 通过枚举Alice和Bob的选择，判断是否能够达成平局。
- 代码简洁，时间复杂度为$O(N^2)$。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2005;
char s[N];
bool dp[N][N];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		memset(s,0,sizeof s);
		scanf("%s",s+1);
		int n=strlen(s+1);
		for(int i=1;i<n;i++) 
			if(s[i] == s[i+1]) dp[i][i+1]=true;
			else dp[i][i+1]=false;
		for(int len=4;len<=n;len+=2){
			for(int l=1;l<=n-len+1;l++){
				int r=l+len-1;
				if((s[r]==s[l] && dp[l+1][r-1] || s[r]==s[r-1] && dp[l][r-2]) && 
				   (s[l]==s[r] && dp[l+1][r-1] || s[l]==s[l+1] && dp[l+2][r])) dp[l][r]=true;
				else dp[l][r]=false;
			}
		}
		if(dp[1][n]) printf("Draw\n");
		else printf("Alice\n");
	}
	return 0;
}
```

### 最优关键思路与技巧
1. **区间DP与博弈论结合**：通过定义$dp_{l,r}$来表示区间$[l,r]$的胜负情况，结合Alice和Bob的最优策略进行状态转移。
2. **平局判断**：通过观察字符串的结构（如回文、两两重复等）来判断是否能够达成平局。
3. **优化与简化**：通过观察发现Bob不可能获胜，从而简化问题，只需判断Alice是否获胜或平局。

### 拓展与推荐题目
1. **洛谷P1005 矩阵取数游戏**：考察区间DP与博弈论结合的问题。
2. **洛谷P1040 加分二叉树**：考察区间DP的应用。
3. **洛谷P1063 能量项链**：考察区间DP与环形问题的结合。

### 个人心得摘录
- **调试经历**：部分题解提到在调试过程中发现Bob不可能获胜，从而简化了问题的复杂度。
- **踩坑教训**：在状态转移时，需要注意Alice和Bob的选择对后续状态的影响，避免遗漏某些情况。
- **顿悟感想**：通过观察字符串的结构，可以简化问题的复杂度，减少不必要的计算。

---
处理用时：72.64秒