# [USACO25FEB] Printing Sequences B

## 题目描述

Bessie 正在学习使用一种简单的编程语言进行编程。她首先定义一个合法的程序，然后执行该程序以产生一些输出序列。

### 定义：

一个程序是一个非空的语句序列。

一个语句的形式或者是 "PRINT $c$"，其中 $c$ 是一个整数，或者是 "REP $o$"，随后是一个程序，随后是 "END"，其中 $o$ 是一个不小于 1 的整数。

### 执行：

执行一个程序将依次执行其语句。

执行语句 "PRINT $c$" 将使 $c$ 追加到输出序列中。

执行以 "REP $o$" 开始的语句将依次执行内部程序共 $o$ 次。

Bessie 知道如何编写的一个程序示例如下。

```plain
REP 3
    PRINT 1
    REP 2
        PRINT 2
    END
END
```

该程序输出序列 $[1,2,2,1,2,2,1,2,2]$。

Bessie 想要输出一个包含 $N$（$1 \le N \le 100$）个正整数的序列。Elsie 挑战她使用不超过 $K$（$1 \le K \le 3$）个 "PRINT" 语句。注意，Bessie 可以使用任意数量的 "REP" 语句。同时注意，序列中的每个正整数都不超过 $K$。

对于 $T$（$1 \le T \le 100$）个独立的测试用例中的每一个，求 Bessie 是否可以编写一个程序，使用至多 $K$ 个 "PRINT" 语句输出给定的序列。

## 说明/提示

样例 1 解释：

对于第二个测试用例，以下代码使用了 $1$ 个 "PRINT" 语句输出了序列 $[1,1,1,1]$。

```plain
REP 4
    PRINT 1
END
```

样例 2 解释：

对于第一个测试用例，以下代码使用了 $2$ 个 "PRINT" 语句输出了序列 $[1,2,2,2]$。

```plain
PRINT 1
REP 3
    PRINT 2
END
```

对于第二个测试用例，答案是 "NO"，因为使用不超过 $2$ 个 "PRINT" 语句输出序列 $[1,1,2,1]$ 是不可能的。

对于第六个测试用例，以下代码使用了 $3$ 个 "PRINT" 语句输出了序列 $[3,3,1,2,2,1,2,2]$。

```plain
REP 2
    PRINT 3
END
REP 2
    PRINT 1
    REP 2
        PRINT 2
    END
END
```

- 测试点 $3$：$K=1$。
- 测试点 $4\sim 7$：$K \le 2$。
- 测试点 $8\sim 13$：没有额外限制。

## 样例 #1

### 输入

```
2
1 1
1
4 1
1 1 1 1```

### 输出

```
YES
YES```

## 样例 #2

### 输入

```
11
4 2
1 2 2 2
4 2
1 1 2 1
4 2
1 1 2 2
6 2
1 1 2 2 1 1
10 2
1 1 1 2 2 1 1 1 2 2
8 3
3 3 1 2 2 1 2 2
9 3
1 1 2 2 2 3 3 3 3
16 3
2 2 3 2 2 3 1 1 2 2 3 2 2 3 1 1
24 3
1 1 2 2 3 3 3 2 2 3 3 3 1 1 2 2 3 3 3 2 2 3 3 3
9 3
1 2 2 1 3 3 1 2 2
6 3
1 2 1 2 2 3```

### 输出

```
YES
NO
YES
NO
YES
YES
YES
YES
YES
NO
NO```

# 题解

## 作者：qhr2023 (赞：10)

## solution

一道普及组的模拟题。

* $k=1$ 时，序列所有元素都为 $1$，一定合法。
* $k=2$ 时，如果序列是 $111 \cdots 222$ 这个形式，或者序列由多个完全相同的子串组成，则合法。
* $k=3$ 时，如果序列是 $k=1$ 时的合法形式拼接上 $k=2$ 时的合法形式，则合法。

考虑实现。对于 $k=2$，把所有相邻且相等的元素看成一个块，若序列块数不超过 $2$，则满足第一个形式；否则，若所有相隔的块元素和长度都相同，则满足第二个形式。可以用一个二元组的数组来维护。

对于实现 $k=3$，枚举一个分界点，若分界点左边是 $k=1$ 时的合法形式，右边是 $k=2$ 时的合法形式，或者反过来，即合法。

## code

```cpp
#include <bits/stdc++.h>
using namespace std; 
int T, a[105], n, k;
bool sol1 (int l, int r) {
	for (int i=l+1; i<=r; ++i)
		if (a[i]!=a[i-1])
			return 0;
	return 1;
}
bool sol2 (int l, int r) {
	vector<pair<int, int>> b;
 	for (int i=l; i<=r; ++i)
 		if (b.size()&&a[i]==a[i-1])
 			b.back().second++;
 		else
 			b.push_back({a[i], 1});
    if (b.size()<=2||b.size()%2==0){
        for (int i=0; i+2<(int)b.size(); ++i)
        	if (b[i]!=b[i+2])
        		return 0;
        return 1;
	}
    return 0;
}
bool sol3 (int l, int r) {
	for (int len=1; l+len-1<=r; ++len) 
		if ((r-l+1)%len==0) {
			bool f=1;
			for (int i=l; i+len<=r; ++i)
				f&=(a[i]==a[i+len]);
            if (!f)
                continue;
            for (int i=l; i<=l+len; ++i)
            	if ((sol1(l, i)&&sol2(i+1, l+len-1))||(sol2(l, i)&&sol1(i+1, l+len-1)))
            		return 1;
		}
	return 0;
}
int main () {
	cin >> T;
	while (T--) {
		cin >> n >> k;
		for (int i=1; i<=n; ++i)
			cin >> a[i];
		if (k==1) puts(sol1(1, n)?"YES":"NO");
		if (k==2) puts(sol2(1, n)?"YES":"NO");
		if (k==3) puts(sol3(1, n)?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：IcyDragon (赞：7)

## 思路

这题可以用区间 DP 做，定义 $dp_{i,j}$ 表示输出区间 $[i,j]$ 至少需要多少个 `PRINT` 语句，$dp_{i,j}$ 初始化为 $\infty$，$dp_{i,i}$ 初始化为 $1$。

状态转移方程有两个，第一个是（显然）：

$$
dp_{i,j} = \displaystyle\min_{i \le k < j}\{dp_{i,k}+dp_{k+1,j}\}
$$

第二个是：

当区间 $[i,j]$ 可以形成若干个长度为 $k$ 的循环节时，
$$
dp_{i,j} = \displaystyle\min_{1 \le k < j-i}\{dp_{i,i+k-1}\}
$$

有了以上状态转移方程，代码就已经很好实现了。

## 代码实现

```cpp
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

int dp[110][110],a[110];

bool check(int l,int r,int k){
	string s="",s1="";
	int i;
	for(i = l; i < l+k; i++){
		s.push_back(a[i]+'0');
	}
	for(; i <= r; i++){
		s1.push_back(a[i]+'0');
		if(s1.size() == s.size()){
			if(s != s1){
				return false;
			}
			s1.clear();
		}
	}
	return true;
}

int main(){
	int t,n,k;
	for(cin>>t; t--; cout<<'\n'){
		cin>>n>>k;
		memset(dp,0x3f,sizeof dp);
		for(int i = 1; i <= n; i++){
			cin>>a[i];
			dp[i][i] = 1;
		}
		for(int d = 2; d <= n; d++){
			for(int i = 1; i+d-1 <= n; i++){
				int j = i+d-1;
				for(int k = i; k < j; k++){
					dp[i][j] = min(dp[i][j],dp[i][k]+dp[k+1][j]);
				}
				for(int k = 1; k <= d/2; k++){
					if(d%k==0 && check(i,j,k)){
						dp[i][j] = min(dp[i][j],dp[i][i+k-1]);
						break;
					}
				}
			}
		}
		cout<<(dp[1][n]<=k ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：5)

简单题，鉴定为铜组第二简单的。（关于我铜组第一题做了一个小时，第二题做了十分钟，第三题做了五十分钟）

首先，发现 $K\le 3$，尝试枚举 $K$。

对于 $K=1$，因为只有一种数，所以直接输出 `YES` 可以拿个十分。

对于 $K=2$，根据样例发现可以枚举循环节，然后判断每个循环节是否满足全部相同。

对于 $K=3$，肯定先枚举循环节，接着，因为 $3=1+2$，我们又发现，一个满足条件的循环节 $t_1,t_2,t_3\dots,t_m$ 是需要满足有一个 $i$ 使得 $t_1,t_2,t_3\dots,t_i$ 是满足 $K=2$ 的条件的，且 $t_{i+1},t_{i+2},t_{i+3}\dots,t_m$ 是全部相同的或者有一个 $i$ 使得 $t_1,t_2,t_3\dots,t_i$ 是全部相同的，且 $t_{i+1},t_{i+2},t_{i+3}\dots,t_m$ 是满足 $K=2$ 的条件的。

于是代码可以通过递归实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[110];
int cnt[4];
int a2[110],cnt2[4];
inline bool check(int a[],int cnt[],int n,int num);//提前声明函数来递归
inline bool checker(int a[],int a2[],int cnt2[],int n){
	bool flg=0;
	for(int i=1;i<=n;i++){
		memset(cnt2,0,sizeof cnt2);
		for(int j=1;j<=i;j++) cnt2[a[j]]++;
		bool p=check(a,cnt2,i,2);//递归
		int cnt=0;
		for(int j=i+2;j<=n;j++) if(a[j]!=a[j-1]) cnt++;
		if(cnt==0 && p) flg=1;//先 K=2 后完全相同
		memset(cnt2,0,sizeof cnt2);
		for(int j=i+1;j<=n;j++) cnt2[a[j]]++,a2[j-i]=a[j];
		p=check(a2,cnt2,n-i,2);//递归乘 2
		cnt=0;
		for(int j=2;j<=i;j++) if(a[j]!=a[j-1]) cnt++;
		if(cnt==0 && p) flg=1;//先完全相同后 K=2 
	}
	return flg;
}
inline bool check(int a[],int cnt[],int n,int num){
	bool flag=0;
	for(int i=1;i<=n;i++)
		if(n%i==0){
			bool f=0;
			for(int j=i+1;j+i-1<=n;j+=i) for(int k=j;k<=j+i-1;k++) if(a[k]!=a[k-j+1]) f=1;//判断是否是循环节
			if(!f && num==2){//如果解决的是 K=2 的问题
				int cnt=0;
				for(int j=2;j<=i;j++) if(a[j]!=a[j-1]) cnt++;
				if(cnt<2) flag=1;
			}
			if(!f && num==3){//如果解决的是 K=3 的问题
				if(checker(a,a2,cnt2,i)) flag=1;//判断是否满足上面的一大啪啦的 K=3 的循环节
				int cnt=0;
				for(int j=2;j<=i;j++) if(a[j]!=a[j-1]) cnt++;
				if(cnt<3) flag=1;
			}
		}
	if(flag) return 1;
	else return 0;
}
inline void solve(){
	cin>>n>>k;
	memset(a,0,sizeof a);
	for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
	if(k==1){
		cout<<"YES\n";
		return;
	}
	if(k==2){
		if(cnt[1]==0 && cnt[2]!=0) cout<<"YES\n";//全部相同
		else if(cnt[1]!=0 && cnt[2]==0) cout<<"YES\n";//全部相同
		else if(check(a,cnt,n,2)) cout<<"YES\n";//判断循环节 
		else cout<<"NO\n";
	}
	if(k==3){
		int sum=(cnt[0]!=0)+(cnt[1]!=0)+(cnt[2]!=0);
		if(sum==1) cout<<"YES\n";//全部相同
		else{
			if(check(a,cnt,n,3)) cout<<"YES\n";//进入递归 
			else cout<<"NO\n";
		}
	}
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：hjyowl (赞：4)

### 思路

注意到 $n\le 100$，考虑使用区间动态规划。

定义 $f_{l,r}$ 为 $l$ 到 $r$ 之间最少需要多少次。

首先 $f_{l,r}$ 肯定能取到 $f_{l,k}+f_{k+1,r}$ 这段。

然后开始考虑枚举 $f_{l,r}$ 中通过循环做的数量，也就是只要哪个循环段的长度为 $r-l+1$ 的因数而且每个段是一样的即可，也就是对于满足条件的 $k$，$f_{l,r}$ 可以取到 $f_{l,l+k-1}$。

最后判断一下 $f_{1,n}$ 是否小于等于 $m$ 就行。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N =110;
int f[N][N],a[N];
bool checker(int l,int r,int len){
	set<string>s;
	for (int i = l; i <= r; i += len){
		string t = "";
		for (int j = i; j <= i + len - 1; j ++ ){
			t += (char)(a[j] + '0');
		}
		s.insert(t);
	}
	return s.size() == 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin >> T;
	while (T -- ){
		int n,k;
		cin >> n >> k;
		memset(f,0x3f,sizeof f);
		for (int i = 1; i <= n; i ++ ){
			cin >> a[i];
			f[i][i] = 1;
		}
		for (int len = 2; len <= n; len ++ ){
			for (int l = 1; l + len - 1 <= n; l ++ ){
				int r = l + len - 1;
				for (int k = l; k < r; k ++ ){
					f[l][r] = min(f[l][r],f[l][k] + f[k + 1][r]);
				}
				vector<int>vec;
				for (int k = 1; k * k <= len; k ++ ){
					if (len % k == 0){
						if (k * k == len){
							if (checker(l,r,k)){
								vec.push_back(k);
							}
						}
						else{
							if (checker(l,r,k)){
								vec.push_back(k);
							}
							if (checker(l,r,len / k)){
								vec.push_back(len / k);
							}
						}
					}
				}
				for (int i = 0; i < vec.size(); i ++ ){
					f[l][r] = min(f[l][r],f[l][l + vec[i] - 1]);
				}
			}
		}
		if (f[1][n] <= k){
			puts("YES");
		}
		else{
			puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：AuZeb (赞：4)

## 思路
前置知识：区间 DP + kmp。

通过观察可以发现如果序列中有多个元素反复出现，则可以使用 `REP` 语句重复输出。要使 `PRINT` 语句少，则应该使用更多的 `REP` 语句，那么通过寻找最短循环节，就可以减少 `PRINT` 语句数量。我们可以设 $f[i][j]$ 表示 $i$ 到 $j$ 至少使用的 `PRINT` 语句数量，如果 $i$ 到 $j$ 可以由一个最短循环节重复构成，那么 $f[i][j]=f[i][i+minl-1]$，即次数等于输出最小循环节的次数，然后再通过枚举小区间合并转移。最后判断 $f[1][n]$ 是否小于等于 $k$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std; const int maxn=102;
int a[maxn],f[maxn][maxn],tem[maxn],nxt[maxn];
int sol(int l,int r){ // 计算最小循环节
	int cnt=r-l+1,j=0;
	for(int i=1;i<=cnt;i++) tem[i]=a[l-1+i],nxt[i]=0;
	for(int i=2;i<=cnt;i++){
		while(j&&tem[j+1]!=tem[i]) j=nxt[j];
		if(tem[j+1]==tem[i]) j++; nxt[i]=j;
	}
	if(cnt%(cnt-nxt[cnt])==0) return cnt-nxt[cnt];
	return -1;
}
int main(){
	int T; cin>>T; while(T--){
		int n,k; cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		memset(f,0x3f3f3f3f,sizeof(f));
		for(int i=1;i<=n;i++) f[i][i]=1;
		for(int len=2;len<=n;len++) // 枚举区间长度。
			for(int st=1;st+len-1<=n;st++){ // 枚举区间起点。
				int la=st+len-1,minl=sol(st,la);
				if(minl!=-1) f[st][la]=f[st][st+minl-1];
				// 如果存在循环节，更新，因为循环节可以通过 REP 语句重复输出。
				for(int m=st;m<la;m++) // 枚举区间分割点
					f[st][la]=min(f[st][la],f[st][m]+f[m+1][la]);
			}
		if(f[1][n]<=k) cout<<"YES\n"; else cout<<"NO\n";
	}
	return 0;
}
```

本题是 [UVA11022](https://www.luogu.com.cn/problem/UVA11022) 的简单版，做完本题的可以完成这道题，需要注意没翻译到的是：**不同阶的串是不能压缩的，不同阶的串指两个串被压缩的次数不同。**

例如字符串 ABABB，压缩为 $\texttt{(AB)}_2\texttt{B}$，此时后两个 B 不能再压缩因为他们是不同价的。

---

## 作者：tuntunQwQ (赞：3)

设 $f_{l,r}$ 为 $a_l$ 至 $a_r$ 最少可以使用多少次 "PRINT" 语句。

如果 $a_l,a_{l+1},...,a_{r}$ 的循环节长度为 $m$，则 $a_l$ 至 $a_r$ 可以在 "REP" 语句内部加入 $a_l$ 至 $a_{l+m-1}$ 的语句即可，故 $f_{l,r}$ 可以由 $f_{l,l+m-1}$ 转移过来。

另外，对于 $[l,r)$ 范围内的 $k$，$f_{l,r}$ 均可以由 $f_{l,k}+f_{k+1,r}$ 转移过来，也就是将 $a_l$ 至 $a_k$、$a_{k+1}$ 至 $a_r$ 的语句拼接起来即可。

对于判断循环节的实现方法，可以枚举 $l+r-1$ 的因数，判断每一段是否相等。

代码如下，可供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int t,n,k,a[N],f[N][N];
bool is(int l,int r,int k){
	string s="",s1="";
	for(int i=l;i<=r;i+=k){
		for(int j=i;j-i+1<=k;j++)s1+=a[j];
		if(i!=l&&s1!=s)return false;
		s=s1,s1="";
	}
	return true;
}
int main(){
	cin>>t;
	while(t--){
		memset(f,0x3f,sizeof f);
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i],f[i][i]=1;
		for(int len=2;len<=n;len++){
			for(int l=1;l+len-1<=n;l++){
				int r=l+len-1;
				for(int m=1;m*m<=len;m++){
					if(len%m==0){
						if(is(l,r,m))f[l][r]=min(f[l][r],f[l][l+m-1]);
						if(is(l,r,len/m))f[l][r]=min(f[l][r],f[l][l+len/m-1]);
					}
				}
				for(int k=l;k<r;k++)f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
			}
		}
		cout<<(f[1][n]<=k?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：Deltary_ (赞：3)

赛场上很自然想到的是区间 DP。

定义 $dp[l][r]$ 为区间 $[l, r]$ 内最少使用 `PRINT` 语句的次数。考虑转移，在 $[l, r]$ 内枚举 $m$，若 $[l, r]$ 区间可以由 $[l, m]$ 循环得到，就把 $[l, m]$ 的答案转移给 $[l, r]$。如果不可以就把两个区间 $[l, m]$ 与 $[m+1,r]$ 答案相加。

转移方程如下：

$$dp[l][r]=
\left\{\begin{matrix}
   \ dp[l][m]+dp[m+1][r] (\text{任意情况})
   \\ dp[l][p] (\ [l, r]\ \text{可由若干个} \ [l, p] \ 循环得到)
\end{matrix}\right.$$


常数不是很大，直接暴力循环判断是否满足即可。时间复杂度 $O(T \times n^4)$。

慢着，似乎哪里有问题？这个复杂度能过？

对于任意情况的转移是 $O(T \times n^3)$。把视线放到暴力判断那一块，不难发现，在枚举 $p$ 的时候并不用循环处理每一位，可以判断 $(p-l+1) \mid len$ 是否成立，若不成立则说明 $[l, r]$ 不可由若干个 $[l, p] $ 循环得到，直接跳出循环。$len$ 的约数个数肯定是严格小于 $2 \sqrt{len}$ 的（貌似高了许多），最简单的质数筛的写法就可以证明。这样看总复杂度（最坏）就是 $O(T \times n^3 \sqrt{n})$。循环判断不符合很快也会跳出循环。$10^2$ 绰绰有余（逃）
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
void solve();
void fac();
signed main(){
	ios::sync_with_stdio(false);
	int _=read();
	while(_--) solve();
	return 0;
}
const int N=2e3+10;
int n,K;
int val[N];
int dp[N][N];
void solve(){
	memset(dp,0x3f,sizeof(dp)); 
	n=read(),K=read();
	for(int i=1;i<=n;i++) val[i]=read();
	for(int i=1;i<=n;i++) dp[i][i]=1;
	for(int len=2;len<=n;len++){
		for(int l=1;l<=n;l++){
			int r=l+len-1; if(r>n) continue;
			for(int m=l;m<r;m++){
				dp[l][r]=min(dp[l][r],dp[l][m]+dp[m+1][r]);
			}
			for(int p=1;p<=len;p++){
				if(len%p!=0) continue;
				bool rr=true;
				for(int pos=l;pos<=r;pos++) if(val[pos]!=val[l+(pos-l)%p]){
					rr=false; break;
				}
				if(rr) dp[l][r]=min(dp[l][r],dp[l][l+p-1]);
			}
		}
	}
	cout<<((dp[1][n]<=K)?"YES":"NO")<<"\n";
	return;
}
```

---

## 作者：hinin (赞：3)

[更好的阅读体验，包括整个铜组](https://www.cnblogs.com/hinin/articles/18731814)。


# T3：Printing Sequences

链接：[USACO](https://usaco.org/index.php?page=viewproblem&cpid=1481)。

### 题意
本题要求判断对于给定的整数序列，是否可以使用不超过 $K$ 个 `PRINT` 语句来生成该序列。序列的生成可以通过 `PRINT` 语句直接输出一个整数，也可以使用 `REP` 语句重复执行一段程序。我们需要使用区间动态规划（区间 DP）来解决这个问题。

### 思路
这题使用区间 DP。

本题的核心是使用区间 DP 来计算输出任意区间 $[l, r]$ 所需的最少 `PRINT` 语句数量。我们定义状态 $dp_{l, r}$ 表示输出区间 $[l, r]$ 所需的最少 `PRINT` 语句数量。

状态转移方程
- 边界条件：
  - 当 $l > r$ 时，区间为空，不需要 `PRINT` 语句，即 $dp_{l, r} = 0$。
  - 当 $l = r$ 时，区间只有一个元素，需要一个 `PRINT` 语句，即 $dp_{l, r} = 1$。

- 状态转移：
  - 划分区间：尝试将区间 $[l, r]$ 划分为两个子区间 $[l, m]$ 和 $[m + 1, r]$，则 $dp_{l, r} = \min(dp_{l, r}, dp_{l, m} + dp_{m + 1, r})$，其中 $l \leq m < r$。
  - 重复子区间：检查区间 $[l, r]$ 是否可以通过重复某个子区间得到。如果可以，则 $dp[l][r] = \min(dp[l][r], dp[l][l + len - 1])$，其中 $len$ 是重复子区间的长度。

### 考时代码

``` cpp
// Hinin（Neko233）
#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast", "-funroll-all-loops")
#define ll long long
#define pii pair<int, int>

#define y1 kairiki
#define x first
#define y second

#define repeat(x, a, b) for(int x = a; x <= b; x ++)
#define rpless(x, a, b) for(int x = a; x >= b; x --)
#define repeatl(x, a, b) for(int x = a; x < b; x ++)
#define rplessr(x, a, b) for(int x = a; x > b; x --)

using namespace std;

const int N = 1e2 + 1;
int T, n, k, a[N], dp[N][N]; // dp[l][r] 表示输出区间 [l, r] 所需的最少 PRINT 语句数量

// 检查区间 [l, r] 是否可以通过重复某个子区间得到
bool can_repeat(int l, int r) 
{
	repeatl(len, 1, ((r - l + 1) << 1)) {
		if ((r - l + 1) % len == 0) {
			bool flg = true;
			
			repeat(i, l, r - len) if (a[i] != a[i + len]) {
				flg = false;
				break;
			}
			
			if (flg) { return true; }
		}
	}
	
	return false;
}

// 计算输出区间 [l, r] 所需的最少 PRINT 语句数量
int dfs(int l, int r) {
	if (l > r) { return 0; }
	if (dp[l][r]!= -1) { return dp[l][r]; }
	if (l == r) { return dp[l][r] = 1; }
	
	int ans = r - l + 1; // 初始化为最大可能值
	// 尝试将区间 [l, r] 划分为两个子区间
	
	repeatl(m, l, r) 
	{ ans = min(ans, dfs(l, m) + dfs(m + 1, r)); }
	
	// 检查区间 [l, r] 是否可以通过重复某个子区间得到
	if (can_repeat(l, r)) {
		int len = (r - l + 1);
		repeat(y1, 1, len / 2) if (len % y1 == 0) {
			bool flg = true;
			repeat(i, l, r - y1) if (a[i]!= a[i + y1]) {
				flg = false;
				break;
			}
			
			if (flg) { ans = min(ans, dfs(l, l + y1 - 1)); }
		}
	}
	
	return dp[l][r] = ans;
}

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); 
	
	cin >> T;
	
	while (T --) {
		cin >> n >> k;
		repeat(i, 1, n) { cin >> a[i]; }
		
		memset(dp, -1, sizeof dp);
		
		int ans = dfs(1, n);
		if (ans <= k) { cout << "YES" << endl; }
		else { cout << "NO" << endl; }
	}
	
	return 0;
}

```

- 时间复杂度：$O(Tn^3)$。
- 空间复杂度：$O(n^2)$，主要用于存储 $dp$ 数组。

---

## 作者：MaiJingYao666 (赞：2)

# 题解：P11838 [USACO25FEB] Printing Sequences B  
其实不难，但是我的做法就很额……难评。  
***  

### 解题思路    
首先，我们定义对于一个数列 $SSSS...SS$，$S$ 为它的最简形式。  
同时，对于一个数列 $A$，若 $A$ 只有一个数，如 $[1,1,1]$，那就被称为一块数，同时，数列 $[1,2,1]$ 的块数应该为 3。

看到 $k \le 3$，就自信的分讨：  
1.    $k=1$，那显然只有该数列只有一块数。
2.    $k=2$，那么该数列的最简形式的块数不超过 2。
3.    $k=3$，那么就分几种情况了，学过小学加法的都知道，$3=1+2=2+1$，意思就是该数列的最简形式可以是一个块数不大于 3 的数列；  
也可以是由一个最简形式块数不超过 1 的前缀数列加上一个最简形式块数不超过 2 的后缀数列；  
或者由一个最简形式块数不超过 2 的前缀数列加上一个最简形式块数不超过 1 的后缀数列。

好了看懂了，那我们只需要做出一个能计算最简形式和块数的功能就行了。  

### AC 代码  
优雅的百行代码。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=105;//真的有必要吗？ 
int t;
int n,k;
int a[N];
inline int check(int l,int r){
	int m;
	for(int len=1;len<=r-l+1;len++){
		if((r-l+1)%len) continue;
		bool flag=1;
		for(int i=l+len-1;i<=r-len;i+=len){
			for(int j=1;j<=len;j++){
				if(a[i+j]!=a[l+j-1]){
					flag=0;
					break;
				}
			}
			if(!flag){
				break;
			}
		}
		if(flag){
			return len;
		}
	}
}
inline int check2(int l,int r){
	int ans=0;
	for(int len=1;len<=r-l+1;len++){
		int flag=(r-l+1)/len;
		int cnt=1;
		for(int i=l+1;i<=l+len-1;i++){
			if(a[i]!=a[i-1])cnt++;
		}
		if(cnt>2)return ans;
		int cs=1;
		for(int i=l+len-1;i<=r-len;i+=len){
			for(int j=1;j<=len;j++){
				if(a[i+j]!=a[l+j-1]){
					flag=cs;
					break;
				}
			}
			if(flag!=(r-l+1)/len){
				break;
			}
			else cs++;
		}
		ans=max(ans,len*cs);
	}
	return ans;
}
inline int count(int l,int r){
	int cnt=1;
	for(int i=l+1;i<=r;i++){
		if(a[i]!=a[i-1])cnt++;
	}
	return cnt;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		int m=check(1,n);
		if(k==1){
			if(m==1)cout<<"YES\n";
			else cout<<"NO\n";
		}
		if(k==2){
			int cnt=count(1,m);
			if(cnt>2)cout<<"NO\n";
			else cout<<"YES\n";
		}
		if(k==3){
			int cnt=count(1,m);
			int l=0,r;
			if(cnt<=3){
				cout<<"YES\n";
			}
			else{
				int p=check2(1,m);
				reverse(a+1,a+m+1);//转换前后缀 
				int q=check2(1,m);
				reverse(a+1,a+m+1);
				if(check(p+1,m)==1 || check(1,m-q)==1){
					cout<<"YES\n";
				}
				else{
					cout<<"NO\n";
				}
			}
		}
	}
}
```

---

## 作者：MoGuYun_12 (赞：1)

考虑区间 dp，记 $f_{i,j}$ 为从 $i$ 至 $j$ 的区间内最少要进行几次操作。

然后是区间 dp 的固定流程，第一层枚举区间长度，第二层枚举左右端点，第三层枚举区间内断点。

关键是如何计算一段区间内需要操作的次数。从题意可得知最优情况是将一段子区间重复多次，此时子区间内的不同元素个数会造成贡献。所以再枚举子区间长度，判断是否重复即可。转移方程为 $f_{i,j} = \min(f_{i,j},cal(i,i+len-1))$。其中 $len$ 是子区间长度，$cal$ 函数用来计算贡献。

时间复杂度 $O(n^4)$。


```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 105;
int n,m,a[N],f[N][N],v[N];

bool check(int x,int y,int l){
	for(int i=x;i<=y-l;i++)	if(a[i]!=a[i+l]) return false;
	return true;
}
int cal(int x,int y){
	int cnt=0;
	memset(v,0,sizeof v);
	for(int i=x;i<=y;i++) if(!v[a[i]]) cnt++,v[a[i]]=1;
	return cnt;
}
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T; cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		memset(f,0x3f,sizeof f);
		for(int i=1;i<=n;i++) f[i][i]=1;
		for(int l=2;l<=n;l++){
			for(int i=1,j=i+l-1;j<=n;i++,j++){
				for(int k=i;k<j;k++) f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
				for(int k=i;k<j;k++){
					int len=k-i+1;
					if(l%len!=0) continue;
					if(check(i,j,len)) f[i][j]=min(f[i][j],cal(i,i+len-1));
				}
			}
		}
//		cout<<f[1][n]<<endl;
		if(f[1][n]<=m) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}    
	return 0;
}

```

---

## 作者：George222 (赞：1)

## 思路

本题解使用简单 dp 解决本问题。

设 $dp_{i, j}$ 为区间 $[i, j]$ 中使用的 print 代码个数，判断 $\text{if } dp_{1, n} \le k$。

对于长度为 $1$ 的子序列，$dp_{i, i} = 1$，指使用一个 print 语句输出字符。

对于长度大于 $1$ 的子序列，设子序列长度为 $len$，从 $2 \sim n$；左右边界为 $[i, j]，1 \le i \le n - len + 1$：

1. 在子序列中遍历一个可能的分隔点，设为 $l$，$i \leq l \leq j$；初始化 $dp_{i, j} = \min(dp_{i, j}, dp_{i, l} + dp_{l + 1, j})$。
2. 然后开始检查子序列是否可以由子序列中的一个子序列拼接而来。
3. 枚举子序列中的子序列的长度，即周期长度，设为 $l$，$1 \le l < len$ 且 $len \bmod l = 0$。
4. 检查周期中每个位置 $p$，$i \le p \leq j$，是否满足 $a_p = a_{i + (p - i) \bmod l}$，即为检查子序列中每 $l$ 位是否与周期 $p_{i} \sim p_{i + l - 1}$ 相同。如果全部满足，则更新 $dp_{i, j} = \min(dp_{i, j}, dp_{i, i + l - 1})$。

输出：判断 $dp_{1, n} \le k$ 即可。

时间复杂度约为 $O(T \times n^3 \times f(n))$ 左右，其中 $f(n)$ 表示 $n$ 的因子数量。


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
int n, k;

int main()
{
    int t;
    cin >> t;
    while (t--)
	{
        int n, k;
        cin >> n >> k;
        int a[105];
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        int dp[105][105];
        for (int i = 1; i <= n; i++)
        {
        	for (int j = 1; j <= n; j++)
        		dp[i][j] = 105;
		}
        for (int i = 1; i <= n; i++)
            dp[i][i] = 1;
        
        for (int len = 2; len <= n; len++)
		{
            for (int i = 1; i <= n - len + 1; i++)
			{
                int j = i + len - 1;
                for (int l = i; l < j; l++)
                    dp[i][j] = min(dp[i][j], dp[i][l] + dp[l + 1][j]);

                int x = len;
                for (int l = 1; l < x; l++)
				{
                    if (x % l != 0)
                        continue;
                    bool flag = true;
                    for (int p = i; p <= j; p++)
					{
                        if (a[p] != a[i + (p - i) % l])
						{
                            flag = false;
                            break;
                        }
                    }
                    if (flag)
                        dp[i][j] = min(dp[i][j], dp[i][i + l - 1]);
                }
            }
        }
        cout << (dp[1][n] <= k ? "YES" : "NO") << "\n";
    }
    return 0;
}
```

---

## 作者：The_Chariot (赞：1)

~~第一次写题解被打回两次。~~

提供一种区间 dp 的想法。

这题的数据范围很小，$N\le100$，容易想到区间 dp。

对于这题最暴力的想法是先枚举一个大区间 $(l,r)$，再在其中枚举一个循环节区间 $(l,z)$，扫一遍看这个大区间能否被这个循环节区间通过一次循环得到。时间复杂度为 $O(N^4 T)$。

如何优化呢？

假设区间 $(l,z)$ 属于 $(l,r)$，那么下一次枚举到 $(l,r+1)$ 时会重复枚举一遍 $(l,z)$。那么我们可以考虑预处理出可以被一次循环的区间 $(l,r)$，用数组 $xh_{l,r}$ 维护 $(l,r)$ 的循环节长度，那么便能避免重复计算循环节区间。

转移公式：

$$dp_{l,r}=\begin{cases}\min^{z\leq r}_{z=l}\,\,(dp_{l,z}+dp_{z+1,r})&xh_{l,r}=\infty\\dp_{l\,,\,l\,+\,xh_{l,r}\,- 1}&xh_{l,r}\ne\infty\end{cases}$$

时间复杂度 $O(N^3 T)$。

在代码中我使用了一种比较丑的预处理实现，希望看到此题解的人自己思考如何实现。

代码如下（石山见谅）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t,n,k;
int a[N];
int dp[N][N];
int xh[N][N];
int main(){
	t=rd();
	while(t--){
        n=rd();
        k=rd();
		for(int i=1;i<=n;i++) a[i]=rd();
		memset(dp,63,sizeof(dp));
		memset(xh,63,sizeof(xh));
		for(int i=1;i<=n/2;i++){
			for(int l=1;l<=n-i+1;l++){
				int r=l+i-1;
				int ll=r+1;
				int rr=ll+i-1;
				int cnt=1;
				while(ll<=n&&rr<=n){
					if(ll>rr){
						xh[l][rr]=min(xh[l][rr],i);
						rr=ll+i-1;
						cnt=1;
					}
					if(a[ll]!=a[l+cnt-1]) break;
					ll++,cnt++;
				}
				if(ll>rr){
					xh[l][rr]=min(xh[l][rr],i);
					rr=ll+i-1;
					cnt=1;
				}
			}
		}
		for(int i=1;i<=n;i++) dp[i][i]=1;
		for(int i=2;i<=n;i++){
			for(int l=1;l<=n-i+1;l++){
				int r=l+i-1;
				for(int k=l;k<r;k++){
					dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
					if(xh[l][r]!=xh[0][0]) dp[l][r]=min(dp[l][r],dp[l][l-1+xh[l][r]]);
				}
			}
		}
		if(dp[1][n]>k) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：Helenty (赞：1)

### Subtask 1

对于 $K=1$，答案总是 `YES`，因为序列中的所有元素都必须是  `1`。

### Subtask 2
对于 $K=2$，需要检查序列是否可以表示为交替的相同数字块。具体步骤如下：

- 遍历序列一次，将连续相同的数字分组为块。
- 记录每个块的大小和值。
- 检查块的数量是否是偶数或小于等于 2。
- 如果块的数量大于 2 且是奇数，返回 `NO`。
- 否则，检查每个块 $i$ 是否与块 $i+2$ 相同。
- 如果所有这些条件都满足，返回 `YES`；否则，返回 `NO`。

### Subtask 3

**不难发现，本题是一道记忆化搜索题。**

设 $d$ 阶序列是可以最多使用 $d$ 个 `REP` 输出的序列。就可以将 $K=3$ 问题简化为以下情况：

- 外层 `REP`：
  - <输出一阶序列的程序>
  - <输出二阶序列的程序>
  - <输出一阶序列的程序>
  - <输出二阶序列的程序>
  - 结束；

- 外层 `REP`：
  - <输出二阶序列的程序>
  - <输出一阶序列的程序>
  - <输出二阶序列的程序>
  - <输出一阶序列的程序>
  - 结束；

外层 `REP` 的内部将构成序列的某个重复块。遍历每个前缀并检查它是否是重复块。如果是，检查它是否可以是外层 `REP` 主体的输出。即查看它是否是一阶和二阶序列的连接。

时间复杂度：$\mathcal{O}\left(N^2\left(\sum_{i=1}^v \frac{1}{d_i^2}\right)\right) = \mathcal{O}(N^2)$。

### 完整代码


```cpp
#include <bits/stdc++.h>
using namespace std; 
 
void solve(){
    int n, k;
    cin >> n >> k;
 
    vector<int> A(n);
    for (int &i : A)
        cin >> i;
    
    auto check1 = [&](int l, int r){
        for (int i = l + 1; i <= r; i++)
            if (A[i] != A[i - 1])
                return false;
        return true;
    };
    auto check2 = [&](int l, int r){
        vector<pair<int, int>> blk;
 
        for (int i = l; i <= r; i++){
            if (blk.size() and A[i] == A[i - 1])
                blk.back().second++;
            else
                blk.push_back({A[i], 1});
        }
        if (blk.size() <= 2 or blk.size() % 2 == 0){
            for (int i = 0; i + 2 < blk.size(); i++)
                if (blk[i] != blk[i + 2])
                    return false;
            return true;
        }
        return false;
    };
    auto check3 = [&](int l, int r){
        for (int blkLen = 1; blkLen <= r - l + 1; blkLen++){
            if ((r - l + 1) % blkLen)
                continue;
 
            bool ok = true;
 
            for (int i = l; i + blkLen <= r; i++)
                ok &= (A[i] == A[i + blkLen]);
            
            if (!ok)
                continue;
            

            for (int i = l; i <= l + blkLen; i++)
                if ((check1(l, i) and check2(i + 1, l + blkLen - 1)) or (check2(l, i) and check1(i + 1, l + blkLen - 1)))
                    return true;
        }
        return false;
    };
 
    if (k == 1)
        cout<<(check1(0, n - 1) ? "YES" : "NO")<<"\n";
    else if (k == 2)
        cout<<(check2(0, n - 1) ? "YES" : "NO")<<"\n";
    else
        cout<<(check3(0, n - 1) ? "YES" : "NO")<<"\n";
}
 
int main(){
    int tc; 
    cin >> tc;
    
    while (tc--) 
        solve();
}
```

---

## 作者：LittleAcbg (赞：1)

考虑进行区间 DP，容易想到用 $g[l][r]$ 表示打印**整个**区间 $[l,r]$ 最少需要几次 `PRINT` 语句。

接着我们思考如何转移。在转移的过程中，我们发现只有两种可能的转移：

1. 使用 `REP` 语句，使用 $[l,r]$ 的某个周期的答案代表区间 $[l,r]$ 的答案。
2. 使用并列语句，将此区间分成两部分，分别打印。

第二种转移更简单，只需要枚举分割点即可。考虑第一种转移里如何维护 $[l,r]$ 的所有周期。

为了避免大家不知道周期的概念，这边给出周期的定义，对长度为 $n$ 的序列 $a_1,a_2,...,a_n$，若长度为 $m$ 的序列 $b_1,b_2,...,b_m$ 满足：

- $m|n$。
- 对 $1\le r\le m$，$1\le qm+r\le n$，$a_{qm+r}=b_r$ 均成立。

则称 $b$ 为 $a$ 的一个周期。显然 $a$ 可由若干个 $b$ 依次拼接得到。

我们维护 $[l,r]$ 的所有周期，再进行一次 DP，用 $f[l][r][k]$ 表示区间 $[l,r]$ 是否具有长度为 $k$ 的周期。

$f[l][r][k]$ 的转移只依赖 $f[l][r-k][k]$，如果 $f[l][r-k][k]=1$ 即 $[l,r-k]$ 有长度为 $k$ 的周期，并且 $[r-k+1,r]$ 这一段和前面的周期（可取 $[l,l+k-1]$）相同，那么 $f[l][r][k]=1$。

判断两个区间是否相等可以使用字符串哈希。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int N = 109;
const int B = 13; // Hash Base
int n,k,a[N],g[N][N];
bitset<N> f[N][N]; // 用三维数组也一样的
ll h[N],p[N]; // 哈希使用自然溢出，下一行是区间哈希
ll H(int l, int r) {return h[r] - h[l - 1] * p[r - l + 1];}
bool mian()
{
    for (int l = 1; l <= n; ++l)
        for (int r = l; r <= n; ++r)
            f[l][r].reset(); // 清空 f
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    p[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        // Hash 预处理
        p[i] = p[i - 1] * B;
        h[i] = h[i - 1] * B + a[i];
    }
    for (int l = n; l >= 1; --l)
        for (int r = l; r <= n; ++r)
        {
            f[l][r][r - l + 1] = 1;
            for (int k = 1; k <= r - l; ++k) // f 的转移
                f[l][r][k] = (f[l][r - k][k] && H(l, l + k - 1) == H(r - k + 1, r));
        }
    for (int i = 1; i <= n; ++i) g[i][i] = 1;
    for (int l = n; l >= 1; --l)
        for (int r = l + 1; r <= n; ++r)
        {
            g[l][r] = r - l + 1; // g 会在此处初始化，不需要清空
            for (int k = 1; k <= r - l; ++k) // 使用循环
                if (f[l][r][k]) g[l][r] = min(g[l][r], g[l][l + k - 1]);
            for (int k = l; k < r; ++k) // 分成两部分
                g[l][r] = min(g[l][r], g[l][k] + g[k + 1][r]);
        }
    return g[1][n] <= k;
}
int main()
{
    int t;
    scanf("%d", &t); // 多组数据处理
    while (t--) puts(mian() ? "YES" : "NO");
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

看到数据范围，明显可以进行区间 DP。$dp_{i,j}$ 表示输出 $dp_{i,j}$ 所最小需要的输出操作数。

初始状态下，$dp_{i,i}=1$，其他的取极大值。一种显然的转移是 $dp_{i,j}=\min(dp_{i,k}+dp_{k+1,j}),k\in[i,j-1]$。

但是我们还有一种转移。我们可以使用循环直接处理一整段循环的东西。因此我们枚举区间长度的所有因数，看这是不是一个循环节，如果是那么 $dp_{i,j}=\min(dp_{i,j},dp_{i,i+l-1})$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, a[105], dp[105][105];
inline void tmin(int& l, const int r) {
	(l > r) && (l = r);
}
inline bool check(int l, int r, int d) {
	string vl = "";
	for (int i = 0; i * d != (r - l + 1); ++i) {
		string tmp = "";
		for (int j = l + i * d; j != l + (i + 1) * d; ++j)
			tmp += char(a[j] ^ 48);
		if (!vl.size()) vl = tmp;
		else if (vl != tmp) return 0;
	}
	return 1;
}
int main() {
	ios::sync_with_stdio(0);
	for (cin >> t; t; t--) {
		cin >> n >> m; memset(dp, 0x3f, sizeof dp);
		for (int i = 1; i <= n; ++i) cin >> a[i];
		for (int i = 1; i <= n; ++i) dp[i][i] = 1;
		for (int l = 2; l <= n; ++l)
#define t (s + l - 1) 
			for (int s = 1; t <= n; ++s) {
				for (int j = s; j != t; ++j)
					tmin(dp[s][t], dp[s][j] + dp[j + 1][t]);
				for (int j = 1; j != l; ++j)
					if (l % j == 0)
						if (check(s, t, j)) {
							tmin(dp[s][t], dp[s][s + j - 1]);
							break;
						}
			}
		puts(dp[1][n] <= m ? "YES" : "NO");
	}
}
```

至于为什么 $k$ 这么小？因为最优的情况下每一层循环就必定对应一个输出，情况非常有限，可以用来暴力判断。这也是一种解法，只是细节略多。

---

## 作者：Zhl2010 (赞：0)

考场上写这道题是脑子抽了，硬是写了 $300$ 行的暴力（建议大家不要模仿）。。。


题目要求判断是否存在一个程序，该程序要用不超过 $K$ 个 `PRINT` 语句（允许任意嵌套的 REP 循环）输出给定的序列。



### 1. 函数 **pdo()**
- **作用**：判断序列是否由同一个数字反复构成。

### 2. 函数 **pds(st, ed)**
- **作用**：检测区间内的序列是否可以由 $2$ 个 `PRINT` 语句生成。
- **实现**：
  - 从区间起始位置提取第一个连续相同的数字段，设为 $xa$，长度记为 $la$。
  - 紧接着提取第二个连续相同的数字段，设为 $xb$，长度记为 $lb$。
  - 随后遍历整个区间，要求序列严格地按“一个长度为 $la$ 的 $xa$ 段 + 一个长度为 $lb$ 的 $xb$ 段”交替重复。
  - 如果整个区间均满足这一交替模式，则说明可以设计程序（例如外层循环中先 `PRINT` $xa$，再 `REP` 循环打印 $xb$），返回真。

### 3. 函数 **pdt()**
- **作用**：判断整个序列是否可以由 $3$ 个 `PRINT` 语句生成，即考虑更复杂的嵌套结构。
- **实现**：
  - 通过尝试不同的分割方案，将序列划分为两个部分：
    - 一部分利用前面两种模式（调用 $pds$）构成一个“基础模式”并存入数组 $b$ 中；
    - 另一部分则利用剩余部分构成第三个 `PRINT` 输出的结构。
  - 在不同分割位置上检测是否存在一个嵌套 `REP` 的循环结构，能够完整输出目标序列。
  - 若存在这种划分，则返回真。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int a[1000010];
int pdo(){
	int t=0;
	int pd=0;
	for(int i=1;i<=n;i++){
		if(t!=a[i]){
			t=a[i];
			pd++;
		}
	}
	return pd<=1;
}
int pds(int st,int ed){
//	int l=1;
//	if(a[1]==a[2]){
//		int xh=a[1];
//		int pd=1;
//		while(a[l+1])++l;
//		for(int i=1;i<=n;i++){
//			for(int j=i;j<=l;j++){
//				if(a[j]!=xh){
//					pd=0;
//					break;
//				}
//				i=j+1;
//			}
//			if(i>n||pd==0){
//				pd=0;
//				break;
//			}
//		}
//		return pd;
//	}
	int pd=1;
	int xa,xb,la=1,lb=1;
	int now=st;
	xa=a[now];
	while(a[now+1]==xa){
		now++;
		la++;
	}
	now++;
	if(now>n)return 1; 
	xb=a[now];
	while(a[now+1]==xb&&now+1<=n){
		now++;
		lb++;
	}
//	cout<<"------"<<la<<' '<<lb<<endl;
	for(int i=st;i<=ed;i++){
		int t=i;
		for(int j=t;j<=t+la-1;j++){
			if(j>ed){
				pd=0;
				break;
			}
			if(a[j]!=xa||j>ed){
				pd=0;
				break;
			}
			i=j;
		}
		i++;
		t=i;
		for(int j=t;j<=t+lb-1;j++){
//			cout<<"***"<<j<<' '<<a[j]<<endl;
			if(j>ed){
				pd=0;
				break;
			}
			if(a[j]!=xb||j>ed){
				pd=0;
				break;
			}
			i=j;
		}
//		i++;
		if(pd==0)break;
	}
	
	return pd;
}
int b[1000010];

int pdt(){
	int pd=0;
	for(int i=1;i<=n;i++){
		int cnt=0;
		if(pds(1,i)){
//			cout<<i<<endl;
			for(int j=1;j<=i;j++){
				b[++cnt]=a[j];
			}
//			int p=0;
//			int ss=0;
//			for(int j=i+1;j<=n;j++){
//				if(j+cnt-1>n)break;
//				int f=1;
//				for(int k=j;k<=j+cnt-1;k++){
//					if(a[k]!=b[k-j+1]){
//						f=0;
//					}
//				}
//				if(f==1){
//					p=1;
//					break;
//				}
//			}
			int now=i+1;
			int x=a[now],l=1;
			while(a[now+1]==x&&now+1<=n){
				l++;
				now++;
			}
			for(;l>0;now--){
//			cout<<l<<endl;
			int p=1;
			for(int j=1;j<=n;j++){
				int t=j;
				for(int k=t;k<=cnt+t-1;k++){
					if(a[k]!=b[k-t+1]||k>n){
//						cout<<k<<' '<<k-j+1<<endl;
						p=0;
						break;
					}
					j=k;
				}
				j++;
				t=j;
//				if(j==n+1)break;
//				cout<<p<<endl;
				for(int k=t;k<=l+t-1;k++){
					if(a[k]!=x||k>n){
						p=0;
						break;
					}
					j=k;
				}
				if(p==0)break;
			}
			if(p){
				pd=1;
				break;
			}
			l--;
			}
			if(pd){
				pd=1;
				break;
			}
		}
	}
	if(pd==1)return 1;
	int now=1;
	int x=a[now],l=1;
	while(a[now+1]==x&&now+1<=n){
		l++;
		now++;
	}
	now++;
	for(;l>0;now--){
	for(int i=now;i<=n;i++){
		if(pds(now,i)){
			int cnt=0;
//			cout<<i<<endl;
			int p=1;
			for(int j=now;j<=i;j++){
				b[++cnt]=a[j];
			}
//			cout<<cnt<<endl;
			for(int j=1;j<=n;j++){
				int t=j;
				for(int k=t;k<=l+t-1;k++){
					if(a[k]!=x||k>n){
						p=0;
						break;
					}
					j=k;
				}
				j++;
				t=j;
//				cout<<j<<endl;
//				if(j==n+1)break;
//				cout<<p<<endl;
				for(int k=t;k<=cnt+t-1;k++){
					if(a[k]!=b[k-t+1]||k>n){
//						cout<<k<<' '<<k-j+1<<' '<<a[k]<<endl;
						p=0;
						break;
					}
					j=k;
				}
				if(p==0)break;
			}
			if(p){
				pd=1;
				break;
			}
		}
	}
	l--;
	}
	return pd;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		if(k==1){
			if(!pdo())cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}else if(k==2){
			if(pds(1,n)||pdo())cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}else{
			if(pds(1,n)||pdo()||pdt())cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
			
		}
		
	}
	
	
	
	return 0;
}
/*
????????????????????????????

???????
REP x
    PRINT a
    REP y
        PRINT b
    END
END
abbbbabbbb
REP x
    REP y
        PRINT b
    END
    PRINT a
END
bbbbabbbba
REP x
    REP y
        PRINT b
    END
    REP z
        PRINT c
    END
END
bbcccbbccc

???????
REP x
    PRINT a
    REP y
        PRINT b
        REP z
	        PRINT c
	    END
    END
END
??????????? T
aTTTTaTTTTaTTTT
TTTTaTTTTaTTTTa 

10
10 3
1 1 2 1 2 1 2 1 2 1

*/

```

---

## 作者：five_rice_water (赞：0)

一道比较好的题目。

首先看状态，$f_{i,j}$ 表示从 $i$ 到 $j$ 这个区间最少需要几个输出的语句。

怎么转移？

首先对于任何一对 $i$ 和 $j$，都可以无脑得到 $f_{i,j} = \min \{f_{i,j},f_{i,k}+f_{k+1,j}\}$，其中 $k$ 需要枚举，范围 $i \le k < j$。

然后我们需要发挥想象力，对于一个序列，如果能够找到长度是**整个序列的循环节长度的因数**的循环节，那么输出整个序列的代价就是输出这一个循环节的代价，原因是可以在输出这个循环节之后加一个循环就可以了。

也就是 $f_{i,j} = \min \{f_{i,j},f_{i,i+len-1}\}$，其中 $len$ 是枚举并且判断可行的循环节的长度。

然后就做完了。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 105;
int T, n, k, a[N], f[N][N];

//f[i][j]表示i~j区间的数最少需要多少个print输出
int check(int l, int r, int len) {
	for (int i = l; i <= r; i++) {
		if (a[l + ((i - l) % len)] != a[i])
			return 0;
	}
	return 1;
}

signed main() {
	cin >> T;
	while (T--) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		memset(f, 0x3f, sizeof(f));
		for (int i = 1; i <= n; i++) {
			f[i][i] = 1;
		}
		for (int len = 2; len <= n; len++) {
			for (int i = 1; i + len - 1 <= n; i++) {
				int j = i + len - 1;
				for (int k = i; k < j; k++) {
					f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
				}
				for (int k = 1; k <= len; k++) {
					if (len % k != 0)
						continue;
					if (check(i, j, k)) {
						//check(i,j,k) 判断i~j区间能不能得到长度为k的循环节
						f[i][j] = min(f[i][j], f[i][i + k - 1]);
					}
				}
			}
		}
		if (f[1][n] > k) {
			cout << "NO" << endl;
		} else {
			cout << "YES" << endl;
		}
	}
	return 0;
}
```

---

