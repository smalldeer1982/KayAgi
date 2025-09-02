# Palindromes

## 题目描述

Friday is Polycarpus' favourite day of the week. Not because it is followed by the weekend, but because the lessons on Friday are 2 IT lessons, 2 math lessons and 2 literature lessons. Of course, Polycarpus has prepared to all of them, unlike his buddy Innocentius. Innocentius spent all evening playing his favourite game Fur2 and didn't have enough time to do the literature task. As Innocentius didn't want to get an F, he decided to do the task and read the book called "Storm and Calm" during the IT and Math lessons (he never used to have problems with these subjects). When the IT teacher Mr. Watkins saw this, he decided to give Innocentius another task so that the boy concentrated more on the lesson and less — on the staff that has nothing to do with IT.

Mr. Watkins said that a palindrome is a string that can be read the same way in either direction, from the left to the right and from the right to the left. A concatenation of strings $ a $ , $ b $ is a string $ ab $ that results from consecutive adding of string $ b $ to string $ a $ . Of course, Innocentius knew it all but the task was much harder than he could have imagined. Mr. Watkins asked change in the "Storm and Calm" the minimum number of characters so that the text of the book would also be a concatenation of no more than $ k $ palindromes. Innocentius can't complete the task and therefore asks you to help him.

## 样例 #1

### 输入

```
abacaba
1
```

### 输出

```
0
abacaba
```

## 样例 #2

### 输入

```
abdcaba
2
```

### 输出

```
1
abdcdba
```

## 样例 #3

### 输入

```
abdcaba
5
```

### 输出

```
0
a+b+d+c+aba
```

## 样例 #4

### 输入

```
abacababababbcbabcd
3
```

### 输出

```
1
abacaba+babab+bcbabcb
```

# 题解

## 作者：_lxy_ (赞：2)

### 题意

一个字符串，求最少改多少个字符能把这个字符串拆成 $k$ 个回文串。

### 分析

先暴力求出每一段改为回文串所需的最小修改次数，将 $[i,j]$ 改为回文串所需的最小修改次数为 $f_{i,j}$ ，然后 dp 即可。定义 $dp_{i,k}$ 为将 $[0,i]$ 改为能拆成 $k$ 个回文串所需的最小修改次数，$dp_{i,k}=\min(dp_{j \in [0,i-1],k})$。在 dp 的时候，更新 dp 值的同时，记录路径，$dp1_{i,k}$ 表示 $dp_{i,k}$ 是从哪转移的，最后从后向前找到路径，依照路径分段输出，再修改一下回文即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int inf=2139062143;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
template<class T1,class T2>inline T1 qmax(const T1 &x,const T2 &y){return x>y?x:y;}
template<class T1,class T2>inline T1 qmin(const T1 &x,const T2 &y){return x<y?x:y;}
const int MAXN=507;
string s;int n,m,dp[MAXN][MAXN],f[MAXN][MAXN],ans=inf,dp1[MAXN][MAXN];
vector<int>a;
int main()
{
	cin>>s;n=s.size();qread(m);int i,j,k;mem(dp,0x7f);
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			int l=j-i+1;
			for(k=i;k<i+l/2;k++) if(s[k]!=s[j-(k-i)]) f[i][j]++; //将[i,j]变成回文串的最小花费
		}
	}
	for(i=0;i<n;i++) dp[i][1]=f[0][i];
	for(i=0;i<n;i++) //当前枚举到的位数
	{
		for(j=0;j<i;j++)
		{
			for(k=1;k<=m;k++) //分成的回文串数
			{
				if(dp[i][k]>dp[j][k-1]+f[j+1][i])
				{
					dp[i][k]=dp[j][k-1]+f[j+1][i]; //更新dp值
					dp1[i][k]=j;
				}
			}
		}
	}int pos=n-1,t=0;
	for(i=1;i<=m;i++)
		if(ans>dp[n-1][i]) ans=dp[n-1][i],t=i; //找出dp最小值
	while(pos>=0&&t>=0)
	{
		a.push_back(pos); //加入路径
		pos=dp1[pos][t--];
	}
	a.pop_back();
	reverse(a.begin(),a.end()); //由于是从后往前加入的，所以需要翻转
	printf("%d\n",ans);
	int last=-1;
	for(i=0;i<a.size();i++)
	{
		if(i!=0) putchar('+');
		for(j=last+1;j<=a[i];j++) 
		{
			if(s[j]==s[a[i]-(j-last-1)]) putchar(s[j]); //无需修改
			else if(a[i]-(j-last-1)>j) putchar(s[j]); //前半部分对应的已修改
			else putchar(s[a[i]-(j-last-1)]); //需要修改
		}
		last=a[i];
	}
	return 0;
}
```

---

## 作者：Roshin (赞：0)

## 题意简述

输入一个**包含大小写字母**的字符串 $s\;(|s|\leq 500)$ 与整数 $k\;(1\leq k\leq |s|)$ 。

询问**最少**修改多少个字符能使得 $s$ 可以分割成**不超过** $k$ 段回文串（**回文串判定区分大小写**）。

输出第一行表示最小修改次数。

输出第二行表示 $s$ 的修改和分割的结果，相邻的回文串以 `+` 字符相连。

## 思路
+ 类似区间dp求出修改区间 $[l,r]$ 为回文串的最小修改次数。
+ 设状态 $dp[i][j]$ ，其中 $i$ 为结尾，回文串个数为 $j$ 的最小修改数。
+ 状态转移 $dp[i][j] = \min(dp[i][j], dp[k][j - 1] + cost[k + 1][i])$ 。
	+ 解释一下转移，枚举分界点 $k$ , 从 $dp[k][j - 1]$ 转移到 $dp[i][j]$ 即在 $s[k]$ 后面接上 $s[k+1,i]$ 。
    + $s[k+1,i]$ 是一段回文串，转移代价即预处理的修改次数为 $cost[k+ 1][i]$ 。
+ 然后递归输出方案即可, 时间复杂度 $O(n^3)$ 。

## Code
```c++
#include<bits/stdc++.h>
const int N = 510;
int cost[N][N];
int dp[N][N], n;
string s;
// dp[i][j] i 为结尾，回文串个数为 j 的最小修改数。
// dp[i][j] = min(dp[i][j], dp[k][j - 1] + cost[k + 1][i])
void Print(int now, int num) {
    for (int i = 0; i < now; i++) {
        if (dp[i][num - 1] + cost[i + 1][now] == dp[now][num]) {
            Print(i, num - 1);
            int len = now - (i + 1) + 1;
            for (int j = i + 1; j <= i + 1 + len / 2 - 1; j++) {
                s[j] = s[now - (j - (i + 1))];
            }
            for (int j = i + 1; j <= now; j++)
                printf("%c", s[j]);
            if (now != n)
                printf("+");
            break;
        }
    }
}
int main() {
    IOS;
    int K;
    cin >> s >> K;
    s = " " + s;
    n = s.size() - 1;
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if (len == 2) {
                cost[l][r] = !(s[l] == s[r]);
                continue;
            }
            cost[l][r] = cost[l + 1][r - 1] + !(s[l] == s[r]);
        }
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= K; j++) {
            for (int k = 0; k < i; k++) {
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + cost[k + 1][i]);    // [k + 1, i] 为新的一段回文串。
            }
        }
    }
    int ans = 1e9;
    for (int i = 1; i <= K; i++) {	// 找出满足条件的最小修改次数
        ans = min(ans, dp[n][i]);
    }
    int num = n;
    for (int i = 1; i <= K; i++) {
        if (dp[n][i] == ans) {
            num = i;
            break;
        }
    }
    printf("%d\n", ans);
    Print(n, num);
    return 0;
}
```

---

