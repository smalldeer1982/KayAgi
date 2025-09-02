# Palindrome

## 题目描述

Given a string $ s $ , determine if it contains any palindrome of length exactly $ 100 $ as a subsequence. If it has any, print any one of them. If it doesn't have any, print a palindrome that is a subsequence of $ s $ and is as long as possible.

## 说明/提示

A subsequence of a string is a string that can be derived from it by deleting some characters without changing the order of the remaining characters. A palindrome is a string that reads the same forward or backward.

## 样例 #1

### 输入

```
bbbabcbbb
```

### 输出

```
bbbcbbb
```

## 样例 #2

### 输入

```
rquwmzexectvnbanemsmdufrg
```

### 输出

```
rumenanemur
```

# 题解

## 作者：lg_zhou (赞：8)

PS：一道回文子序列的题，建议大家仔细思考再看，因为此题比较板。

- 题意：输入一个字符串（$n < 50000$）确认它是否包含有长度为 100 的回文子序列，如果有，输出其中一个。如果没有，输出它所包含的最长回文子序列。

首先，**子序列可以不连续，而子串必须连续。**

------------


常见的最长回文子串有两种解法：
1. [manacher](https://www.luogu.com.cn/problem/P3805)。
2. 二分中点 + 哈希判断。

由于与本题无关，不再赘述，有兴趣的同学可以自行了解。

------------


回到最长回文子序列，常见的也有两种解法：
1. 动态规划。
2. 最长回文子序列（LPS）长度恰好等于字符串 S 与 reverse（S）的最长公共子序列（LCS）。

而第二种做法不是能很好地解决非最长的回文子序列 (可能因为我不会) 。所以我们考虑方法一。

轻松的列出转移方程：

$dp[i][j]=\begin{cases}dp[i+1][j-1]+2&S[i]=S[j]\\max(dp[i+1][j], dp[i][j-1])&S[i]!=S[j]\end{cases}$


但我们发现这样的复杂的是 $O(n^2)$ 的，而数据范围是 50000 的，显然会爆掉。

再次观察题面，显然可得：长度大于 100 的回文串肯定包含长度等于 100 的回文串，所以我们的 dp 只用做到出现长度大于等于 100 的回文串即可停止。这样，加一个 $dp[i][j]$ 与 100 的判断条件 + 回溯输出方案 + 滚动数组就能轻易地过掉这道题。

可是当我们仔细想想，就不会出现一组一直让你跑满才得出答案的数据吗？或者说，数据再大点我们还可以这么做吗？仔细观察，我们发现每 2600 个字符中必有一个长度大于等于 100 的回文串！根据抽屉原理， 一共有 26 个小写字母，必有一个字母出现大于等于 100 次，而同一个字母组成的字符串必为回文串。

所以，我们可以在开头判断字符串长度与 2600 的关系，长度比 2600 要大，那么扫一遍输出 100 次出现次数大于 100 次的字符。反之，就正常跑一边 $(n^2)$ 的暴力就 OK 啦。

上代码：
```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int f[2605][2605];
string s;
char ans[51];
int cnt[27],n;
int main(){
    cin >> s;
    n = s.length();
    s = " " + s;
    if (n >= 2600){//统计出现次数大于 100 的直接输出
        for (int i = 1; i <= n; i++){
            cnt[s[i]-'a']++;
        }
        for (int i = 0; i < 26; i++){
            if (cnt[i] >= 100){
                for (int j = 1; j <= 100; j++){
                    cout << (char)('a'+i);
                }
                return 0;
            }
        }
    }

    
    for (int i = n; i >= 1; i--){ // dp
        f[i][i] = 1;
        for (int j = i+1; j <= n; j++){
            if (s[i] == s[j]){
                f[i][j] = f[i+1][j-1]+2;
            }else{
                f[i][j] = max(f[i+1][j], f[i][j-1]);
            }
        }
    }
    
    int x,y,pan;
    x = 1, y = n;
    pan = min(f[x][y],100) % 2; // 判断奇偶性，判断中间的输出几次

    int tot = 0;
    while(x <= y){ // 回溯
        if (s[x] == s[y]){
            ans[++tot] = s[x];
            x++,y--;
        } 
        else if (f[x+1][y] > f[x][y-1]) x++;
        else y--;
    }
    for (int i = 1; i <= min(tot,50); i++) cout << ans[i];
    if (!pan) cout << ans[min(50,tot)];//偶数就多输出一次
    for (int i = min(tot-1,49); i >= 1; i--) cout << ans[i];
    return 0;
}
```


---

## 作者：getchar_unlocked (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF335B)

### 思路

首先考虑如何计算最长回文子序列的长度。不难想到可以作区间 DP，$f_{l,r}$ 表示区间 $[l,r]$ 中的最长回文子序列的长度。易得出转移式：

$$
\begin{cases}
  f_{l,r}\gets f_{l+1,r-1}+2&s_l=s_r\\
  f_{l,r}\gets\max(f_{l+1,r},f_{l,r-1})&s_l\ne s_r
\end{cases}
$$

然而 $n\le5\times10^4$，无法通过。其实题目中要求，当最长回文子序列的长度 $\ge100$ 时，输出一个长度为 $100$ 的子序列即可。所以当 $n\ge2575$ 时，必然有一种字母出现过 $100$ 或更多次（[抽屉定理](https://baike.baidu.com/item/%E6%8A%BD%E5%B1%89%E5%AE%9A%E7%90%86/10661533)），找到这个字母并输出 $100$ 次即可。

剩下的情况输出时可以 dfs。dfs 中分为两种情况：

- 如果 $s_l=s_r$ 且 $f_{l,r}=f_{l+1,r-1}+2$：这说明 $[l,r]$ 是由 $[l+1,r-1]$ 转移而来的，一定能使答案序列最长，故输出 $s_l$ 后，$\operatorname{dfs}(l+1,r-1)$，再输出 $s_r$。
- 否则找到一个满足 $s_l=s_{r-1}$ 或者 $s_{l+1}=s_r$ 的条件 dfs。如果都不满足就随便 dfs 一个。

然而这样做仍然存在问题，因为答案子序列的长度可能 $\ge100$。故在 dfs 中增加一维 $C$，表示还可以拼接多少个字符。到终止时，若 $C=0$，返回一个空串；否则 $C=1$，返回 $s_l$ 或 $s_r$ 中任意一个，因为回文串中间的字符不影响结果。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=5e4+10,M=2.6e3+10;
char s[N];
int dp[M][M],tong[128];
string dfs(int l,int r,int cnt){
	if(!cnt)
		return "";
	if(cnt==1)
		return string(1,s[l]);
	if(s[l]==s[r]&&dp[l][r]==dp[l+1][r-1]+2)
		return s[l]+dfs(l+1,r-1,cnt-2)+s[r];
	if(dp[l][r]==dp[l][r-1])
		return dfs(l,r-1,cnt);
	return dfs(l+1,r,cnt);
}
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	if(n<=2574){
		for(int i=1;i<=n;++i)
			dp[i][i]=1;
		for(int len=2;len<=n;++len)
			for(int l=1;l+len-1<=n;++l){
				int r=l+len-1;
				if(s[l]==s[r])
					dp[l][r]=dp[l+1][r-1]+2;
				else dp[l][r]=max(dp[l+1][r],dp[l][r-1]);
			}
		string ans=dfs(1,n,min(100,dp[1][n]));
		for(char ch:ans)
			printf("%c",ch);
		printf("\n");
		return 0;
	}
	for(int i=1;i<=n;++i)
		++tong[s[i]];
	for(char i='a';i<='z';++i)
		if(tong[i]>=100){
			for(int j=1;j<=100;++j)
				printf("%c",i);
			printf("\n");
			return 0;
		}
	return 0;
}
```

---

## 作者：sto_yxc_orz (赞：2)

好题

[题目传送门](https://www.luogu.com.cn/problem/CF335B)

此题与编辑距离思路极其相似，显然有 ```dp[l][r]``` 为 ```l``` 到 ```r```的最长回文子串。转移方程：

$dp[l][r]=\max{(dp[l][r],dp[l][r-1],dp[l+1][r])}$

如果字符串左右两端相等，还有:

$dp[l][r]=\max{(dp[l][r],dp[l+1][r-1])}$

此时发现时间复杂度平方级别。我们又不难发现，至少有一种小写字母出现一百次，根据[抽屉原理](https://oi-wiki.org/math/combinatorics/drawer-principle/)可得，在 ```n``` 大于 ```2600``` 的情况下，至少有一种小写字母出现一百次，直接找到输出即可。同时平方级别也足够我们通过此题。

输出字符串就 ```dfs``` 一下，根据 ```dp``` 数组输出即可

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+10;
int dp[N][N];
string s;
int cnt=0;
void dfs(int l,int r)
{
	if(l>r)	return ;
	if(l==r)
	{
		cnt++;
		cout<<s[l]; 
		return ;
	}	
	
	if(s[l]==s[r])
	{
		cnt+=2;
		if(cnt>=100)
		{
			cout<<s[l];
			if(cnt==100)	cout<<s[r];
			return ;
		}	
		cout<<s[l];
		dfs(l+1,r-1);
		cout<<s[r];
		
	}	
	else
	{
		if(dp[l][r]==dp[l+1][r]) dfs(l+1,r);
		else dfs(l,r-1);
	}
}

int main()
{
	
	cin>>s;
	int n=s.size();
	s=" "+s;
	if(n>2600)
	{
		map<char,int> mp;
		for(int i=1;i<=n;i++)	mp[s[i]]++;
		for(char i='a';i<='z';i++)
		{
			if(mp[i]>=100)
			{
				for(int j=1;j<=100;j++)	cout<<i;
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++)	dp[i][i]=1;
	for(int len=2;len<=n;len++)
	{
		for(int l=1;l+len-1<=n;l++)
		{
			int r=l+len-1;
			if(s[l]==s[r])	dp[l][r]=max(dp[l][r],dp[l+1][r-1]+2);
			dp[l][r]=max(dp[l][r],dp[l][r-1]);
			dp[l][r]=max(dp[l][r],dp[l+1][r]);
		}
	}
	dfs(1,n);
	return 0;
}
```

---

## 作者：root357 (赞：2)

# CF335B Palindrome

### 题意

给定一个长度 $ \le 5 \times 10^4 $ 的只包含小写字母的字符串，输出一个长度最大且不超过 $ 100 $ 的回文子序列。

### 思路

* $ 0 \thicksim 20 $ pts: DFS 暴力选取并判断。

  时间复杂度 $ O(2 ^ n k) $（$ k $ 为子序列长度）。
  
  由于过于暴力，此处不再赘述。

* $ \approx 60 $（存疑）pts: 区间 DP。

  根据题意可以使用一个区间 DP 来推出最长回文子序列长度。然后使用双指针找出回文子序列。

  $ dp_{i, j} $ 代表区间 $ [i, j] $ 的最长回文子序列的长度。

  初始状态 $ dp_{i, i} = 1 $。

  转移方程:

  $$
  
  dp_{i, j} = \begin {cases} 
  
  1 ,& s_i = s_j \\
  \max \{dp_{i + 1, j}, dp_{i, j - 1}\} ,& s_i \neq s_j.
  
  \end {cases}
  
  $$
  
  时间复杂度 $ O(n ^ 2) $。

* 可问题是我们发现对于 $ n \le 5 \times 10 ^ 4 $，$ O(n ^ 2) $ 的时间复杂度是过不去的。

  我们回看题目，发现最多只求一个长度为 $ 100 $ 的回文子序列，而字符串内又只有小写字母。
  
  那么根据鸽巢原理，设最小的一定包含回文子序列的字符串长度为 $ x $，我们有:
  
  $$ x \div 26 = 99 \cdots\cdots 1 $$
  $$ x = 26 \times 99 + 1 $$
  $$ x = 2575 $$
  
  所以对于长度 $ \ge 2575 $ 的字符串，就肯定有一个长度 $ \ge 100 $ 的回文子序列。

  而对于长度 $ < 2575 $ 的，区间 DP 即可。

  期望得分 $ 100 $ pts。

### 代码

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int cnt[130] = {0};
int dp[2600][2600] = {0};

char s[50010];
char Palindrome[110];

int main () {
    // freopen("palindrome.in", "r", stdin);
    // freopen("palindrome.out", "w", stdout);
    
    scanf("%s", s + 1);
    
    int n = strlen(s + 1);
    
    // 若字符串长度 >= 2575,
    // 根据鸽巢原理 2575 / 26 = 99 ...... 1, 99 + 1 = 100,
    // 则必然存在一个长度 >= 100 的相同字符子序列.
    
    if (n >= 2575) {    
        for (int i = 1; i <= n; i ++)
            cnt[s[i]] += 1;
        
        for (int i = 'a'; i < 'z'; i ++) {
            if (cnt[i] >= 100) {
                for (int j = 1; j <= 100; j ++) 
                    printf("%c", i);
                
                printf("\n");
                
                break;
            }
        }
    }
    else {  // O(2575 ^ 2).
        // 区间 DP 求最长回文子序列.
        
        for (int i = n; i >= 1; i --) {
            dp[i][i] = 1;
            
            for (int j = (i + 1); j <= n; j ++) {
                if (s[i] == s[j]) 
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else 
                    dp[i][j] = max (dp[i + 1][j], dp[i][j - 1]);
            }
        }
        
        int idx = 0;
        int len = min (dp[1][n], 100);
        
        // 找回文子序列.
        
        int l = 1, r = n;
        
        while (l <= r) {
            if (s[l] == s[r]) {
                Palindrome[++ idx] = s[l];
                l ++, r --;
            }
            else if (dp[l + 1][r] > dp[l][r - 1])
                l ++;
            else if (dp[l + 1][r] <= dp[l][r - 1])
                r --;
            
        }
        
        // 输出部分, 记得判断子序列长度奇偶性.
        
        int num = min (idx, 50);
        bool lenIsOdd = len & 1;
        
        for (int i = 1; i <= num - 1; i ++)
            printf("%c", Palindrome[i]);
        
        if (lenIsOdd) printf("%c", Palindrome[num]);
        else printf("%c%c", Palindrome[num], Palindrome[num]);
        
        for (int i = num - 1; i >= 1; i --) 
            printf("%c", Palindrome[i]);
        
        printf("\n");
        
    }
    
    
    return 0;
}
```

Updated on 2022.7.5: 修正了文中多处用词错误.


---

## 作者：longlong_int (赞：1)

# DP 部分

## 状态

用 $dp_{l, r}$ 表示 $[l,r]$ 这个区间内**最长回文子序列的长度**。

## 转移

若 $s_l=s_r$，则 $[l,r]$ 这个区间必定可以由 $[l,l]$、$[l+1,r-1]$、$[r,r]$ 这三个区间拼接而来，且拼接完成后的子序列必定也是回文串。

否则，易得 $dp_{l,r}=\max(dp_{l+1,r},dp_{l,r-1})$。

所以，综合状态转移方程为：

$dp_{l,r}=\begin{cases}
dp_{l+1,r-1}+2 \operatorname{if}s_l = s_r\\
\max(dp_{l+1,r},dp_{l,r-1}) \operatorname{if}s_l \neq s_r
\end{cases}$

# DFS 部分

## 传参

DFS 传参：$l,r,c$，表示在 $[l,r]$ 这个区间内找到一个长度为 $c$ 的回文子序列并输出。

## 出口

$c=0$ 时可直接返回，$c=1$ 时输出 $s_l$ 即可。

## 递归

当 $s_l = s_r$ 时，在 $[l+1,r-1]$ 这个区间内找到一个长度为 $c-2$ 的回文子序列即可（$[l,l]$、$[l+1,r-1]$，$[r,r]$ 三个区间合并）

否则，先判断最长子序列在 $[l,r-1]$ 还是在 $[l+1,r]$ 内，再递归调用 `dfs(l, r - 1, c)` 或 `dfs(l + 1, r, c)` 即可。

# 后期处理

阅读到这里的你应该已经有了思路，准备切换到 ~~AC CODE~~ IDE 写代码了。但是先别急，上面思路的时间和空间复杂度均为 $\mathcal{O}(n^2)$，在 $n=5 \times 10^4$ 时不能通过。

由于题目描述中说 $s$ 只包含小写字母，也就是在 $|s| \geq 2600$ 时至少有一个字母出现了 $100$ 次及以上，则直接输出这个字母 $100$ 次即可。

# AC CODE & [Record](https://codeforces.com/problemset/submission/335/306313441)

```cpp
#include <bits/stdc++.h>
#define endl '\n'
typedef long long ll;
using namespace std;

inline ll read()
{
    ll f = 1, sum = 0; char c = getchar();
    while (!(48 <= c && c <= 57)) { if (c == '-') f = -1; c = getchar();}
    while (48 <= c && c <= 57){sum = sum * 10 + c - 48; c = getchar();}
    return sum * f;
}

inline void write(ll x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}

string s;
int dp[2620][2620];

void dfs(int l, int r, int cnt)
{
    if (cnt == 0) return;
    if (cnt == 1)
    {
        cout << s[l];
        return;
    }

    if (s[l] == s[r])
    {
        cout << s[l];
        dfs(l + 1, r - 1, cnt - 2);
        cout << s[r];
    }
    else
    {
        if (dp[l][r] == dp[l + 1][r])
        {
            dfs(l + 1, r, cnt);
        }
        else
        {
            dfs(l, r - 1, cnt);
        }
    }
    return;
}

map<char, int> mp;

int main()
{
    cin >> s;
    if ((int)(s.size()) >= 2600)
    {
        for (char i : s) mp[i]++;
        for (char i = 'a'; i <= 'z'; i++)
        {
            if (mp[i] >= 100)
            {
                for (int hnfduinhsnfhdu = 1; hnfduinhsnfhdu <= 100; hnfduinhsnfhdu++)
                {
                    cout << i;
                }
                return 0;
            }
        }
    }
    else
    {
        int n = s.size();
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        for (int len = 2; len <= n; len++)
        {
            for (int l = 0; l + len - 1 < n; l++)
            {
                int r = l + len - 1;
                if (s[l] == s[r]) dp[l][r] = dp[l + 1][r - 1] + 2;
                else dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
            }
        }
        dfs(0, n - 1, min(dp[0][n - 1], 100));
    }
    return 0;
}
```

---

## 作者：Hacker_Cracker (赞：1)

## CF335B Palindrome 题解
### Solution
这道题让我们求最长回文子序列。可以使用区间动态规划解决。设 $dp_{l,r}$ 表示 $s$ 的子串 $s_l$ 到 $s_r$ 的最长回文子序列。

显然，如果 $s_l=s_r$，就有 $dp_{l,r} \gets dp_{l+1,r-1}+2$。否则，本状态的 $dp$ 值就由两个长度为 $r-l$ 的子串转移而来，有 $dp_{l,r} \gets \max(dp_{l+1,r},dp_{l,r-1})$。

但是 $n \le 5\times 10^4$，不能使用 $O(n^2)$ 的时间复杂度和空间复杂度通过。

#### 另类的思路
根据鸽巢原理，当一个仅由小写字母组成的字符串长度**不小于** $2.6 \times 10^3$ 时，一定至少有一个字母出现了**不小于** $100$ 次。所以我们遍历一遍字符串，发现有出现次数超过 $100$ 的字符就直接输出即可。

如何输出一个字符串的最长回文子序列？我们需要用到 dfs。对于一对 $(l,r)$，如果 $s_l=s_r$，就先输出 $s_l$，再递归处理 $(l+1,r-1)$。如果不等于，就判断 $dp_{l,r}$ 是由 $dp_{l+1,r}$ 还是 $dp_{l,r-1}$ 转移而来。然后递归处理。

这样分类讨论就不会超时了。
### [AC](https://codeforces.com/problemset/submission/335/306151743) Code
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=3e3+10;
const int L=2e2+10;
int dp[N][N],cnt[N],n;
string s;
void dfs(int l,int r,int cnt){
	if(!cnt) return;
	if(cnt==1){
		cout<<s[l];
		return;
	}
	if(s[l]==s[r]){
		cout<<s[l];
		dfs(l+1,r-1,cnt-2);
		cout<<s[r];
	}else{
		if(dp[l][r]==dp[l+1][r]) dfs(l+1,r,cnt);
		else dfs(l,r-1,cnt);
	}
	return;
}
int main(){
	cin>>s;
	n=s.size();
	s=" "+s;
	for(int i=1;i<=n;i++) cnt[s[i]]++;
	if(n>=2600){
		for(int i='a';i<='z';i++){
			if(cnt[i]>=100){
				for(int j=1;j<=100;j++){
					cout<<(char)i;
				}
				cout<<endl;
				return 0;
			}
		}
	}else{
		for(int i=1;i<=n;i++) dp[i][i]=1;
		for(int len=2;len<=n;len++){
			for(int l=1,r=len;r<=n;l++,r++){
				if(s[l]==s[r]) dp[l][r]=dp[l+1][r-1]+2;
				else dp[l][r]=max(dp[l+1][r],dp[l][r-1]);
			}
		}
		dfs(1,n,min(dp[1][n],100));
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Milthm (赞：0)

很巧妙的题目。

首先想一下怎么 $O(n^2)$ 做。我们知道，一个字符串的最长回文子序列，可以把它倒过来，然后和没倒过来的自己求一遍最长公共子序列。

最长公共子序列可以做到 $O(n^2)$ 求，假设字符串是 $s$，反转后是 $t$，则考虑 dp，设 $dp_{i,j}$ 表示 $s$ 的前 $i$ 个字符和 $t$ 的前 $j$ 个字符的最长公共子序列长度，我们有：

$$ dp_{i,j}=\left\{
\begin{aligned}
&dp_{i-1,j-1}+1,&s_i=t_j\\
&\max\{dp_{i-1,j},dp_{i,j-1}\},&s_i≠t_j
\end{aligned}
\right.
$$

这是求长度，求具体字符串只需要记录每一个 $(i,j)$ 是怎么转移的，回溯即可。

如果长度大于 $100$，我们需要将其分割，取中间那 $100$ 个就行。但是如果长度是奇数的话则中间那一个字符也是不能取的。

然后就做到了 $O(n^2)$，但是我们发现，如果一个字符串中含有 $100$ 个相同字母，那么直接输出这 $100$ 个字符就行。而 $99\times 26+1=2575$，所以长度大于 $2575$ 的字符串一定含有 $100$ 个相同字母，直接输出即可。

所以循环最多也只有 $2575^2$ 次，不会超时。

### AC code

```cpp
#include<bits/stdc++.h>
#define N 3005 
using namespace std;
string s,t,ans;
int cnt[26],dp[N][N],lst[N][N];
void dfs(int x,int y){
	if(!x||!y)return;
	if(lst[x][y]==1){
		ans+=s[x];dfs(x-1,y-1);
	}
	else if(lst[x][y]==2)dfs(x,y-1);
	else dfs(x-1,y);
}
int main(){
	cin>>s;t=s;
	int l=s.size();
	reverse(s.begin(),s.end());s=" "+s,t=" "+t;
	for(int i=1;i<=l;++i)cnt[s[i]-'a']++;
	for(int i=0;i<26;++i){
		if(cnt[i]>=100){
			for(int j=1;j<=100;++j)cout<<char(i+'a');
			return 0;
		}
	}
	for(int i=1;i<=l;++i){
		for(int j=1;j<=l;++j){
			if(s[i]==t[j])dp[i][j]=dp[i-1][j-1]+1,lst[i][j]=1;
			else if(dp[i][j-1]>dp[i-1][j])dp[i][j]=dp[i][j-1],lst[i][j]=2;
			else dp[i][j]=dp[i-1][j],lst[i][j]=3;
		}
	}
	dfs(l,l);
//	cout<<dp[l][l]<<'\n';
	if(dp[l][l]<=100)cout<<ans;
	else{
		ans=" "+ans;
		if(dp[l][l]&1){
			for(int i=dp[l][l]/2-49;i<=dp[l][l]/2;++i)cout<<ans[i];
			for(int i=dp[l][l]/2+2;i<=dp[l][l]/2+51;++i)cout<<ans[i];
		} 
		else{
			for(int i=dp[l][l]/2-49;i<=dp[l][l]/2+50;++i)cout<<ans[i];
		}
	}
	return 0;
}

```

---

## 作者：Jsxts_ (赞：0)

另类 DP。

设 $dp_{i,j}$ 表示 前 $i$ 个字符，组成的回文子序列长度为 $j$ 时，子序列的起点的最大值为多少。显然起点越大越优，所以这个 DP 是正确的。

转移很简单，分类讨论选或不选 $i$：

- 不选，$dp_{i,j}=dp_{i-1,j}$。

- 选，$dp_{i,j}=pre_{dp_{i-1,j-2}-1,s_i}$，其中 $pre_{i,j}$ 表示 $i$ 前第一个字符 $j$ 的位置，表示在之前整个子序列的前后同时选了个 $s_i$。

初始化即 $dp_{i,1}=i,dp_{i,2}=\max(dp_{i-1,2},pre_{i-1,s_i})$。

由于还要记录方案，在 DP 时多记录一个数表示当前回文串的结尾，然后倒着推即可。

不需要特判 $s$ 的长度。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 5e4;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
char s[N + 10];
pair<int,int> dp[N + 10][110];
int n,pre[N + 10][26];
int main() {
	scanf("%s",s + 1);
	n = strlen(s + 1);
	for (int i = 1;i <= n;i ++ ) {
		for (int j = 0;j < 26;j ++ ) pre[i][j] = pre[i - 1][j];
		pre[i][s[i] - 'a'] = i;
	}
	for (int i = 1;i <= n;i ++ ) {
		dp[i][1] = {i,i}, dp[i][2] = max(dp[i - 1][2],{pre[i - 1][s[i] - 'a'],i});
		for (int j = 3;j <= min(i,100);j ++ ) {
			dp[i][j] = dp[i - 1][j];
			if (dp[i - 1][j - 2].first) dp[i][j] = max(dp[i][j],{pre[dp[i - 1][j - 2].first - 1][s[i] - 'a'],i});
		}
//		cout << "dp:" << i << endl;
//		for (int j = 0;j <= i;j ++ ) cout << j << ' ' << dp[i][j].first << ' ' << dp[i][j].second << endl;
	}
	for (int i = 100;i;i -- ) {
		if (dp[n][i].first > 0) {
//			cout << i << endl;
			int t = dp[n][i].second,j = i;
			string ans = "";
			while (j > 0) {
				ans += s[t];
				if (j > 1) j -= 2, t = dp[t - 1][j].second;
				else break;
			}
			cout << ans;
			for (int i = ans.size() - 1 - (j % 2);~i;i -- ) putchar(ans[i]);
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：xuhanxi_dada117 (赞：0)

[题目大意&题目传送门](https://www.luogu.com.cn/problem/CF335B)

# 解法

## 1. 思路启发

要求一个串的最长回文字序列，有两种方法：

+ 区间 dp。（这个方法另外两篇题解有了，不再过多赘述。）

+ 应用公式 $lps(s)=lcs(s,Reverse(s))$。

$lps(s)$ 为 $s$ 的最长回文子列。

本题解主要讲述第二种方法的实现。

## 2.代码过程

求串的反转非常简单，不多讲了。

接下来就是 $lcs$，但这里要记录路径把子列求出来。

本身只需要在 dp 的时候加一个前驱记录，最后扫一遍即可。

在求出子列后，若长度 $\ge 100$ 将其割裂成长度为 $100$ 的回文子列即可。

时间复杂度：$O(n^2)$。

## 3.优化

$O(n^2)$ 肯定过不了 $50000$。所以我们要优化算法。

考虑到 $n\ge 26\times99+1=2575$ 时，必出现 $100$ 个相同字母。

枚举一下输出即可。

那剩下的 $n\le 2575$ 就可以接受 $O(n^2)$ 了。

# 代码

```cpp
#include<bits/stdc++.h>
#define N 3000
using namespace std;
string s,t,op;int ml[N][N],pos[N][N],cnt[30];
void CountOp(int x,int y){//回溯列出 lps
	if(!x||!y) return;
	if(pos[x][y]==1){
		CountOp(x-1,y-1);
		op+=s[x];
	}else if(pos[x][y]==2) CountOp(x-1,y);
	else CountOp(x,y-1);
}
int main(){cin>>s;
	if(s.size()>=2575){//特判大小
		for(int i=0;i<s.size();++i){
			++cnt[s[i]-'a'];
			if(cnt[s[i]-'a']>=100){
				for(int j=1;j<=100;++j) cout<<s[i];
				return 0;
			}
		}
	}
	for(int i=s.size()-1;i>=0;--i) t+=s[i];
	s=" "+s;t=" "+t;
    //lcs
    int S=s.size(),T=t.size();
    for(int i=0;i<=S;++i) ml[i][0]=0;
    for(int i=0;i<=T;++i) ml[0][i]=0;
    for(int i=1;i<=S;++i){
    	for(int j=1;j<=T;++j){
        	if(s[i]==t[j]){
        		ml[i][j]=ml[i-1][j-1]+1;
        		pos[i][j]=1;
			}
        	else{
        		if(ml[i-1][j]>ml[i][j-1]) ml[i][j]=ml[i-1][j],pos[i][j]=2;
        		else ml[i][j]=ml[i][j-1],pos[i][j]=3;
			}
    	}
	}CountOp(S-1,T-1);
    //统计答案
	if(op.size()<=100) cout<<op;
	else{int len=(op.size()-100)/2;
		for(int i=len;i<op.size()-len;++i){
			if(i==op.size()/2&&op.size()%2==1)continue;
			cout<<op[i];
		}
	}
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/126769246)

# 更新一

修改了第三段大小于符号的问题。

---

