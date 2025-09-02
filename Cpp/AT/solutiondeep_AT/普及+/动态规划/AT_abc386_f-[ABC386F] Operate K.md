# 题目信息

# [ABC386F] Operate K

## 题目描述

给定字符串 $ S $，你需要判断是否有可能通过最多 $ K $ 次操作将其变为字符串 $ T $。

这里操作的定义如下：
1. 在 $ S $ 的任意位置（包括头尾）插入一个字符。
2. 从 $ S $ 删除一个字符。
3. 将 $ S $ 中的某个字符替换为另一个字符。

## 样例 #1

### 输入

```
3

abc

awtf```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2

abc

awtf```

### 输出

```
No```

## 样例 #3

### 输入

```
17

twothousandtwentyfour

happynewyear```

### 输出

```
Yes```

# AI分析结果

### 题目内容重写
给定字符串 $ S $，你需要判断是否有可能通过最多 $ K $ 次操作将其变为字符串 $ T $。

这里操作的定义如下：
1. 在 $ S $ 的任意位置（包括头尾）插入一个字符。
2. 从 $ S $ 删除一个字符。
3. 将 $ S $ 中的某个字符替换为另一个字符。

### 样例 #1
#### 输入
```
3
abc
awtf
```
#### 输出
```
Yes
```

### 样例 #2
#### 输入
```
2
abc
awtf
```
#### 输出
```
No
```

### 样例 #3
#### 输入
```
17
twothousandtwentyfour
happynewyear
```
#### 输出
```
Yes
```

### 题解综合分析与结论
本题的核心是判断是否可以通过最多 $ K $ 次操作将字符串 $ S $ 转换为字符串 $ T $。由于 $ K $ 的范围较小（$ K \leq 20 $），因此可以采用动态规划（DP）的方法来解决。大多数题解都基于编辑距离的思想，通过优化状态转移来减少计算量。

### 所选高星题解

#### 题解1：作者：Inv_day_in_R (赞：8)
**星级：5星**
**关键亮点：**
- 使用DP状态 $dp(i,j)$ 表示 $S$ 的前 $i$ 个字符与 $T$ 的前 $j$ 个字符之间的最少操作次数。
- 通过观察 $|i-j|>k$ 的情况，优化了状态转移，只计算 $|i-j| \leq k$ 的状态。
- 代码简洁，优化了内存使用，避免了不必要的计算。

**核心代码：**
```cpp
int k;
string s,t;
int f[500010][45];
int&dp(int i,int j){return f[i][i-j+22];}
void solve(){
	cin>>k>>s>>t;
	int n=s.size(),m=t.size();
	if(abs(n-m)>k){
		cout<<"No";
		return;
	}
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=k;i++){
		dp(0,i)=i;
		dp(i,0)=i;
	}
	for(int i=1;i<=n;i++)for(int j=max(1ll,i-k);j<=min(i+k,m);j++){
		dp(i,j)=min({dp(i-1,j)+1,dp(i,j-1)+1,dp(i-1,j-1)+(s[i-1]!=t[j-1])});
	}
	if(dp(n,m)<=k)cout<<"Yes";
	else cout<<"No";
}
```

#### 题解2：作者：wang54321 (赞：7)
**星级：4星**
**关键亮点：**
- 提出了一种 $O(k^2\log n+n)$ 的做法，通过键值互换优化了DP状态。
- 使用二分哈希来求LCP，进一步优化了时间复杂度。
- 思路清晰，代码实现较为复杂但效率高。

**核心代码：**
```cpp
int K;
const int N=5e5+5;
char a[N],b[N];
int n,m;
int f[N][45];
void get(int &x,int y){
	if(y<x)x=y;
}
signed main(){
	cin>>K;
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1),m=strlen(b+1);
	memset(f,0x3f,sizeof f);
	f[0][0+K]=0;
	fo(i,0,n){
		fo(j,-K,K){
			if(f[i][j+K]>K||i+j<0||i+j>m)continue;
			if(j+K-1>=0)get(f[i+1][j+K-1],f[i][j+K]+1);
			get(f[i][j+K+1],f[i][j+K]+1);
			get(f[i+1][j+K],f[i][j+K]+1);
			if(a[i+1]==b[i+j+1])get(f[i+1][j+K],f[i][j+K]);
		}
	}
	if(m-n<=K&&m-n>=-K&&f[n][m-n+K]<=K)cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```

#### 题解3：作者：xyx404 (赞：4)
**星级：4星**
**关键亮点：**
- 通过优化DP数组为一维，减少了内存使用。
- 进一步优化了循环，只计算在编辑距离范围内的子串部分。
- 代码实现较为简洁，适合初学者理解。

**核心代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
LL k;
string S,T;
int dp[500050];
void solve(string S,string T){
	LL n=T.size(),m=S.size();
	if(abs(n-m)>k){
		cout<<"No";return;
	}
	if(m>n){
		solve(T,S);
		return;
	}
	vector<int>dp(m+1);
	vector<int>dp2(m+1);
	for(int i=0;i<=min(m,k);i++)dp2[i]=i;
	for(LL i=1;i<=n;i++){
		dp[0]=i;
		char ti=T[i-1];
		for(LL j=max(1ll,i-k);j<=min(m,i+k);j++){
			char sj=S[j-1];
			int add=(ti==sj)?0:1;
			dp[j]=min({dp2[j]+1,dp[j-1]+1,dp2[j-1]+add});
		}
		swap(dp,dp2);
	}
	if(dp2[m]<=k){
		cout<<"Yes";
	}
	else cout<<"No";
	return;
}
int main(){
	cin>>k>>S>>T;
	solve(S,T);
	return 0;
}
```

### 最优关键思路或技巧
1. **状态优化**：通过观察 $|i-j|>k$ 的情况，只计算 $|i-j| \leq k$ 的状态，减少了不必要的计算。
2. **键值互换**：通过将DP状态的定义进行转换，优化了时间复杂度。
3. **一维DP优化**：通过将二维DP数组优化为一维，减少了内存使用，同时保持了计算效率。

### 可拓展之处
- 类似的问题可以应用于其他字符串匹配或编辑距离的场景，如拼写检查、DNA序列比对等。
- 可以进一步优化LCP的计算方法，如使用SA-IS算法等。

### 推荐相似题目
1. [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)
2. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
3. [P3809 【模板】后缀排序](https://www.luogu.com.cn/problem/P3809)

---
处理用时：59.15秒