# TRIP - Trip

## 题目描述

Alice and Bob want to go on holiday. Each of them has drawn up a list of cities to be visited in turn. A list may contain a city more than once. As they want to travel together, they have to agree upon a common route. No one wants to change the order of the cities on his list or add other cities. Therefore they have no choice but to remove some cities from the list. Of course the common route is to involve as much sight-seeing in cities as possible. There are exactly 26 cities in the region. Therefore they are encoded on the lists as lower case letters from 'a' to 'z'.

## 样例 #1

### 输入

```
1
abcabcaa
acbacba```

### 输出

```
ababa
abaca
abcba
acaba
acaca
acbaa
acbca```

# 题解

## 作者：zsq259 (赞：12)

### 题目意思:

**有两个字符串(长度$<=80$),按字典序输出它们的最长公共子串的所有情况.**



### 解析

最长公共子序列的长度应该都没问题了吧...~~有问题请自行百度~~

但关键是要求出每种情况,还要按字典序...

考虑到长度$<=80$,我们可以用搜索+剪枝,

设两个串为$a$,$b$,长度为$la$,$lb$,

$f[i][j]$表示$a$串中的$1$~$i$与$b$串中的$ 1$~$j$的最长公共子序列的长度.

先求出最长公共子序列的长度$len$=$f[la][lb]$,

那么.我们就是要求出一个长度为$len$的$a$,$b$,的子串,

我们再设$f1[i][j]$表示在$a$串的$1$~$j$中,字母$i$出现的最后一个位置,

$f2[i][j]$就表示$b$串,其中$i$取$1$~$26$,

那么在搜索时,记录$4$个信息:$a$串还能取的长度$l1$,$b$串还能取的长度$l2$,当前求出的子串$s$和还需要求的子串的长度$l$.

那么,在一开始时,状态就应该是($la,lb,"",len$),其中$s$是一个空串.

那么,在搜索时枚举每个字母$ci$,设$p1$表示$f1[ci][l1]$,$p2$表示$f2[ci][l2]$,

那么,若$f[p1][p2]>=l$,即最终能形成长度为$len$的子串,就将$ci$加入$s$,

并且注意,由于我们是倒着搜的,所以要用$ci+s$而不是$s+ci$.

当$l1$或$l2$小于$0$时,即搜不到了,就返回,

而当$l$等于$0$时就添加答案并返回.

最后排序后输出就行了.





具体实现看代码吧:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

inline int read(){
    int sum=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=sum*10+ch-'0';ch=getchar();}
    return f*sum;
}

int f[101][101],tot=0;
char a[101],b[101];
int f1[27][101],f2[27][101];
string ans[1001];

void find(int l1,int l2,string s,int l){
    if(l1<0||l2<0) return ;
    if(l<=0){ans[++tot]=s;return ;}
    for(int i=1;i<=26;i++){
        int p1=f1[i][l1],p2=f2[i][l2];
        if(f[p1][p2]!=l) continue;
        char c=i+96;
        find(p1-1,p2-1,c+s,l-1);
    }
}

int main(){
	int T=read();
	while(T--){
		cin>>a>>b;tot=0;
		memset(f,0,sizeof(f));
		memset(f1,0,sizeof(f1));memset(f2,0,sizeof(f2));
		int la=strlen(a),lb=strlen(b);
		for(int i=la;i;i--) a[i]=a[i-1];
		for(int i=lb;i;i--) b[i]=b[i-1];//这两步是整体位移,个人习惯而已
		for(int i=1;i<=26;i++){
			for(int j=1;j<=la;j++){
				if(a[j]==i+96) f1[i][j]=j;
				else f1[i][j]=f1[i][j-1];
			}
			for(int j=1;j<=lb;j++){
				if(b[j]==i+96) f2[i][j]=j;
				else f2[i][j]=f2[i][j-1];
			}
		}//记录f1,f2
		for(int i=1;i<=la;i++){
			for(int j=1;j<=lb;j++){
				f[i][j]=max(f[i-1][j],f[i][j-1]);
				if(a[i]==b[j]) f[i][j]=max(f[i-1][j-1]+1,f[i][j]);
			}
		}//寻找最长公共子序列
		find(la,lb,"",f[la][lb]);
		sort(ans+1,ans+tot+1);
		for(int i=1;i<=tot;i++) cout<<ans[i]<<endl;
	}
    return 0;
}

```
upd:之前忘记加上多组数据了$Q \omega Q$...

---

## 作者：Itst (赞：6)

### ~~原本以为是青铜，结果是个王者qwq~~
### 刚看题，哇塞LCS裸题~~看起来就很简单的样子~~，然而……
### 最开始以为至多只有1000个LCS然后开了1000的数组结果美妙RE
### 然后用set判重更是TLE美滋滋
### 所以就需要用到~~玄学的~~优化方法了
------------
### LCS的转移方程就不再赘述，重点提一下输出路径的方式（敲黑板划重点）：
### 多开两个辅助数组f[ i ][ j ]与g[ i ][ j ]代表s1从第一个字符到第i个字符中（（char）（‘a’ + j））最后一次出现的位置，计算完这两个数组之后，进行递归输出，同时使用枚举法，从后往前一个一个枚举当前位置可填的字母。
### 设dfs( a , b , c)表示当前s1的长度为a，s2的长度为b，待枚举的字母数量为c时的枚举过程，枚举‘a’-‘z’，得到该字母的f[ a ][ b ]与g[ a ][ b ]，如果当s1长度为f[ a ][ b ],s2长度为g[ a ][ b ]时的最长公共子序列长度正好为当前还未枚举的长度c，则dfs(f[ a ][ b ] - 1 , g[ a ][ b ] - 1 , c - 1)，枚举完第一位后即得到一种满足题意的字符串
### 现在的你肯定是云里雾里：为什么这样子可以起到优化的效果？
```
当然先要拿样例数据说话
sample input：
abcabcaa
acbacba

看样例输出就能知道LCS的值为5
那么我们先枚举第5位，先枚举到‘a’
如果没有f、g数组我们的可选方案有(0,0)(0,3)(0,6)(3,0)(3,3)(3,6)(6,0)(6,3)(6,6)(7,0)(7,3)(7,6)
而因为同种情况中只考虑一种，依据贪心算法可知选择(7,6)也就是最后出现的一对必定是最好的，因为选择(7,6)之后s1与s2的选择空间是最大的
所以你能够看出来，这种方法可以做到不重不漏（TLE的很多都是判重上时间开销太大比如我233）
```
### 至于排序set完全可以胜任（使用vector+sort同理）
### 接下来仍然是上代码
```cpp
#pragma GCC optimize(2)
//玄学O2优化安排！
#include<bits/stdc++.h>
using namespace std;
string s1 , s2;
vector < string > s;
short maxN[81][81] , last1[26][81] , last2[26][81] , cou;
//last1、last2对应上面的f、g。
inline int max(int a , int b){
    return a > b ? a : b;
}
void create(int a1 , int a2 , int num , string ss){
	if(num == 0){
		s.push_back(ss);
		return;
	}
	for(int i = 0 ; i < 26 ; i++)
		if(last1[i][a1] >= num && last2[i][a2] >= num && maxN[last1[i][a1]][last2[i][a2]] == num)
			create(last1[i][a1] - 1 , last2[i][a2] - 1 , num - 1 , (char)('a' + i) + ss);
            //递归输出最重要的过程！！！
}
int main(){
    ios::sync_with_stdio(0);
    int T;
    for(cin >> T ; T ; T--){
        memset(maxN , 0 , sizeof(maxN));
        memset(last1 , 0 , sizeof(last1));
        memset(last2 , 0 , sizeof(last2));
        cin >> s1 >> s2;
        for(int i = 1 ; i <= s1.size() ; i++)
            for(int j = 1 ; j <= s2.size() ; j++){
                if(s1[i - 1] == s2[j - 1])	maxN[i][j] = max(maxN[i][j] , maxN[i - 1][j - 1] + 1);
                maxN[i][j] = max(maxN[i][j] , max(maxN[i - 1][j] , maxN[i][j - 1]));
            }
            //LCS DP求解
        for(int i = 1 ; i <= s1.size() ; i++)
        	for(int j = 0 ; j < 26 ; j++)
        		if(s1[i - 1] - 'a' == j)	last1[j][i] = i;
        		else	last1[j][i] = last1[j][i - 1];
        for(int i = 1 ; i <= s2.size() ; i++)
        	for(int j = 0 ; j < 26 ; j++)
        		if(s2[i - 1] - 'a' == j)	last2[j][i] = i;
        		else	last2[j][i] = last2[j][i - 1];
		create(s1.size() , s2.size() , maxN[s1.size()][s2.size()] , "");
        sort(s.begin() , s.end());
        for(int i = 0 ; i < s.size() ; i++)	cout << s[i] << endl;
        //输出
        s.clear();
        cout << endl;
        cou = 0;
    }
    return 0;
}
```

---

## 作者：EternalHeart1314 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/SP33)

# Problem

给定两个只包含小写字母的字符串（长度 $\le 80$），求两串所有的最长公共子序列，按字典序输出。

# Solution

首先用 dp 求出两串的最长公共子序列的长度，可参考 [P1439](https://www.luogu.com.cn/problem/P1439) 的 $O(n^2)$ 做法，然后考虑搜索。

设第一个字符串为 $s$，第二个为 $t$，下标从 $1$ 开始，$f_{i,j}$ 表示 $s$ 的前 $i$ 个字符与 $t$ 的前 $j$ 个字符的最长公共子序列的长度。

预处理 $g_{i,j}$ 表示 $s$ 前 $i$ 个字符中 $j$ 最后出现的位置，若没有出现取 $0$。但为了方便，$j$ 取 $0$ 表示字符 `a`，取 $1$ 表示字符 `b`，$\dots$，取 $25$ 表示字符 `z`。

$h_{i,j}$ 同理求 $t$。

搜索状态为 $(x,y,z,st)$，$x,y,z$ 是 `int`，$st$ 是 `string`，分别表示 $s$ 还能取前 $x$ 个字符，$t$ 还能取前 $y$ 个字符，还要取的公共子序列的长度要为 $z$，已经取了公共子序列 $st$ 了。

搜索时枚举字符 `a` 到 `z`，表示将要取这个字符，然后转移到 $(g_{x,i}-1,h_{y,i}-1,z-1,i+st)$，$i$ 表示枚举的字符，取 $0\sim 25$ 分别表示字符 `a`$\sim $`z`，$i+st$ 表示把 $i$ 对应的字符放到 $st$ 前面：

```cpp
void dfs(int x, int y, int z, string st) {
	if (!z) {
		ans.push_back(st);
		return ;
	}
	For (i, 0, 25) if (g[x][i] && h[y][i])
		dfs(g[x][i] - 1, h[y][i] - 1, z - 1, (char)('a' + i) + st);
}
```

从 $(n,m,f_{n,m},\text{空串})$ 开始搜索，$ans$ 里即是所有的最长公共子序列。

超时，考虑最优性剪枝。

发现若 $f_{x,y}<z$，则这个状态是不能产生最长公共子序列的。因为能取的里面取最长公共子序列，长度都已经不够了：

```cpp
void dfs(int x, int y, int z, string st) {
	if (f[x][y] < z) return ;
	if (!z) {
		ans.push_back(st);
		return ;
	}
	For (i, 0, 25) if (g[x][i] && h[y][i])
		dfs(g[x][i] - 1, h[y][i] - 1, z - 1, (char)('a' + i) + st);
}
```

其实 $z$ 那维是不需要的，因为 $z=f_{n,m}-|st|$：

```cpp
void dfs(int x, int y, string st) {
	if (f[x][y] + st.size() < f[n][m]) return ;
	if (st.size() == f[n][m]) {
		ans.push_back(st);
		return ;
	}
	For (i, 0, 25) if (g[x][i] && h[y][i])
		dfs(g[x][i] - 1, h[y][i] - 1, (char)('a' + i) + st);
}
```

# Code

```cpp
#include <bits/stdc++.h>
#define For(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;

const int N = 80 + 7;
int T, n, m, f[N][N], g[N][27], h[N][27];
vector<string> ans;
string s, t;

void dfs(int x, int y, string st) {//搜索 
	if (f[x][y] + st.size() < f[n][m]) return ;
	if (st.size() == f[n][m]) {
		ans.push_back(st);
		return ;
	}
	For (i, 0, 25) if (g[x][i] && h[y][i])
		dfs(g[x][i] - 1, h[y][i] - 1, (char)('a' + i) + st);
}

main() {
	cin >> T;
	while (T--) {
		ans.clear();
		cin >> s >> t;
		n = s.size(), s = ' ' + s;
		m = t.size(), t = ' ' + t;
		For (i, 1, n) For (j, 1, m)
			f[i][j] = max({f[i - 1][j], f[i][j - 1], f[i - 1][j - 1] + (s[i] == t[j])});
		For (i, 1, n) {
			For (j, 0, 25) g[i][j] = g[i - 1][j];
			g[i][s[i] - 'a'] = i;
		}//预处理 g 和 h 
		For (i, 1, m) {
			For (j, 0, 25) h[i][j] = h[i - 1][j];
			h[i][t[i] - 'a'] = i;
		}
		dfs(n, m, "");
		sort(ans.begin(), ans.end());
		for (string st : ans) cout << st << '\n';
	}
	return 0;
}
```

---

## 作者：Komeijizen (赞：2)

其他的题解貌似都是用 dfs 来凑方案，这里给出一种正序进行的，比较暴力的解法。

考虑在不需要输出方案时求 LCS 的做法：

设两个字符串分别为 $A$ 和 $B$ 长度分别为 $n$ 和 $m$ ， 令 $dp_{i,j}$ 为 $A$ 的前 $i$ 个字符与 $B$ 的前 $j$ 个字符组成的 LCS 长度。  


转移为 $dp_{i,j}=\max(dp_{i-1,j},dp_{i,j-1},dp_{i-1,j-1}+[A_i=B_j])$。


可以发现，这种转移的实质相当于在一个已有的状态后面接一个能匹配的位置。这样能做到在 $O(nm)$ 时间内求出  LCS 长度，但是很难求具体方案（因为不知道当前状态接的上一个具体的状态是什么） 。   
对此，我们可以对状态做出一些改变：   

设 $dp_{i,j}$ 为 $A$ 的前 $i$ 个字符与 $B$ 的前 $j$ 个字符组成，**以 $A_i$ 和 $B_j$ 结尾的** LCS 长度。这样，我们可以维护每一个状态的前驱，进而方便地统计答案。

至于转移，笔者采取了暴力枚举转移点的方式，即对于每一个 $i,j$ 枚举所有在其之前并能匹配的点进行转移，dp 部分时间复杂度 $O(n^2m^2)$ 。这样显然还有优化的空间，但足以通过本题的数据。对于按字典序输出的需求，把所有可行解塞进 set 排序即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int A[85],B[85],n,m;
int dp[85][85];//dp[i][j]->由A的前i个与B的前j个组成的，以A[i]与B[j]为结尾的LCS长度.
vector<pair<int,int>>pre[85][85];
void Trans(int i,int j,int p,int q){
    if(dp[i][j]<dp[p][q]+1){
        dp[i][j]=dp[p][q]+1;
        pre[i][j].clear();
        pre[i][j].push_back({p,q});
    }else if(dp[i][j]==dp[p][q]+1){
        pre[i][j].push_back({p,q});
    }
}
set<string>st;
string tmp;
int mx=0;

void getans(int i,int j){
    tmp.insert(tmp.size(),1,A[i]);
    for(pair<int,int>nx:pre[i][j]){
        getans(nx.first,nx.second);
    }
    if(tmp.size()==mx){
        string ttmp=tmp;
        reverse(ttmp.begin(),ttmp.end());
        st.insert(ttmp);
    }
    tmp.erase(tmp.end()-1);
    return;
}

void solve(){
    cin>>s1>>s2;
    n=s1.size(),m=s2.size();
    memset(dp,0,sizeof dp);
    memset(A,0,sizeof A);
    memset(B,0,sizeof B);

    st.clear();
    tmp.clear();
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++)pre[i][j].clear();
    }
    for(int i=1;i<=n;i++)A[i]=s1[i-1];
    for(int i=1;i<=m;i++)B[i]=s2[i-1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(A[i]==B[j]){
                for(int p=0;p<i;p++){
                    for(int q=0;q<j;q++){
                        if(A[p]==B[q]){
                            Trans(i,j,p,q);
                        }
                    }
                }
            }
        }
    }
    mx=0;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            mx=max(mx,dp[j][i]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(dp[i][j]==mx)getans(i,j);
        }
    }
    for(string nw:st){
        cout<<nw<<endl;
    }

}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
}
```

---

## 作者：wcyQwQ (赞：2)



[题目传送门](https://www.luogu.com.cn/problem/SP33)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/05/03/SP33%20TRIP/)


## 前言

一道输出 dp 方案的题目，如果你不会输出 dp 的方案，那么这题是一道很好的练手题

### 前置芝士

LCS

## 分析

求 LCS 长度的话应该不用多说了，这里具体说一下如何把所有 LCS 找出来。(用 $f[i][j]$ 表示 LCS 长度)

我们用 $recordA[i][j]$，来表示 $s1$ 中前 $i$ 个字符中字符 $j$ 出现的最后一个下标, $recordB[i][j]$ 同理，只不过是表示 $s2$ 中的字符。

然后在找方案的过程中，我们选择倒序遍历，每次用 $len$  表示 LCS 取的剩下的长度，一旦有 `f[recordA[i][k]][recordB[j][k]] == len` 我们就把字符 $k$ 加入我们的答案字符串，并以 $recordA[i][k]-1$ 和 $recordB[j][k]-1$ 为起点继续搜索，直至 `len == 0` 将当前字符串加入答案数组中。

具体实现看代码。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 110, M = 30;
int f[N][N];
int recordA[N][M], recordB[N][M];
vector<string> res;

inline void init(string s1, string s2)
{
    // 求LCS长度
    int l1 = s1.size(), l2 = s2.size();
    for (int i = 1; i <= l1; i++)
        for (int j = 1; j <= l2; j++)
        {
            f[i][j] = max(f[i][j - 1], f[i - 1][j]);
            if (s1[i - 1] == s2[j - 1]) f[i][j] = f[i - 1][j - 1] + 1;
        }
    // 预处理两个数组
    for (int i = 1; i <= l1; i++)
        for (int j = 0; j < 26; j++)
            if (s1[i - 1] == char('a' + j)) recordA[i][j] = i;
            else recordA[i][j] = recordA[i - 1][j];
    
    for (int i = 1; i <= l2; i++)
        for (int j = 0; j < 26; j++)
            if (s2[i - 1] == char('a' + j)) recordB[i][j] = i;
            else recordB[i][j] = recordB[i - 1][j];
}

inline void print(int i, int j, int len, string str)
{
    if (len == 0)
    {
		// 剩余长度为0，此时的str为一个LCS
        res.push_back(str);
        return;
    }
    if (i == 0 || j == 0) return; // 任意一个搜完了，剪枝
    for (int k = 0; k < 26; k++)
    {
        int ki = recordA[i][k], kj = recordB[j][k];
        if (f[ki][kj] == len) // 以ki-1和kj-1为起点搜索
            print(ki - 1, kj - 1, len - 1, char('a' + k) + str); // 注意倒序添加
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        memset(f, 0, sizeof f);
        memset(recordA, 0, sizeof recordA);
        memset(recordB, 0, sizeof recordB);
        res.clear();
        string s1, s2;
        cin >> s1 >> s2;
        init(s1, s2);
        int l1 = s1.size(), l2 = s2.size();
        print(l1, l2, f[l1][l2], "");
        sort(res.begin(), res.end());
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << endl;
    }
    return 0;
}
```





---

## 作者：LCat90 (赞：1)

[原文](https://blog.csdn.net/qq_66589321/article/details/124768003?spm=1001.2014.3001.5501)

题目大意，求出最长公共子序列（拉出序列（多个））。

分析：先用 ``dp`` 求出长度 $len$。接下来用搜索拉出序列。

注意：若两个串相同，则它们尾部相等（显然）。

所以定义 $ra[i][j]$ 为在 $s1$ 中，前 $i$ 个字符中字符为 $j+'0'$ 的最大下标。$rb[i][j]$ 同理。

那么有：

```cpp
for(int i = 1;i <= n1; ++i) // 下标
	for(int j = 1;j <= n2; ++j) // 'a'~'z'
		if(c1[i] == c2[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
		else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
```
我们要找子串，因为其字符分别相同，所以 $j$ 相等，分别寻找 $i$ 即可。

在搜索的角度思考：传入参数 $x$, $y$, $len$, $c$。分别表示 $s1$ 的前 $x$ 个字符，$s2$ 的前 $y$ 个，子串还剩的长度，目前的子串。

枚举字符 $k$，找到其在两字符串中的最后位置 $t1$ 和 $t2$，当 $s1[1...t1]$ 和 $s2[1...t2]$ 中有长度为 $len$ 的相同子串时，就往前搜索。
 
若 $len$ 为 $0$，说明已经查找到一个解，存入 ``string`` 数组，输出时排序即可。
```cpp
void dfs(int x, int y, int len, string c) {
	if(!len) {
		s[++sum] = c;
		return ;
	}
	for(int k = 0;k < 26; ++k) {
		int t1 = ra[x][k], t2 = rb[y][k];
		if(dp[t1][t2] == len) {
			dfs(t1 - 1, t2 - 1, len - 1, char(k + 'a') + c); // 当前字符在存入子串		
		}
	}
}
```

---

## 作者：lyas145 (赞：0)

题目在[这里](https://www.luogu.com.cn/problem/SP33)。

# 解题思路

设 Alice 的清单为字符串 $a$（长度为 $n$），Bob 的清单为字符串 $b$（长度为 $m$）。

符合条件的清单的长度很好求，就是 $a$ 和 $b$ 的最长公共子序列的长度，并且 $n,m$ 范围较小，可以 $\mathcal{O}(nm)$ 地求。

设 $f_{i,j}$ 表示 $a$ 长度为 $i$ 的前缀与 $b$ 长度为 $j$ 的前缀的最长公共子序列的长度，那么转移方程为

$$f_{i,j}=\begin{cases}
\max\{f_{i-1,j},f_{i,j-1}\} & a_i\ne b_j\\
\max\{f_{i-1,j},f_{i,j-1},f_{i-1,j-1}+1\} & a_i=b_j
\end{cases}$$

然后是求所有符合条件的清单，注意到 $n,m\le 80$ 且符合条件的清单的数量最多为 $1000$，这为我们用 DFS 解决此题带来了希望。

暴搜代码如下：

```cpp
vector<string> ans;  //ans 是存答案的。
void dfs(int x,int y,int z,string s) {
    //x 表示 a 长度为 x 的前缀还没用；
    //y 表示 b 长度为 y 的前缀还没用；
    //z 表示还需要多少字符才能拼出符合条件的字符串；
    //s 表示目前拼出的符合条件的清单的后缀。
    if (!z) {ans.push_back(s);return ;}
    //符合条件的清单拼好了，加入答案。
    if (!x || !y) {return ;}
    //如果还没拼好 a 或 b 的字符就用完了，那只好无功而返了。
    for (char c='a';c<='z';c++) {
        //枚举下一个加入符合条件的清单的后缀的字符。
        int xx=x,yy=y;
        while (a[xx]!=c && xx) {xx--;}
        while (b[yy]!=c && yy) {yy--;}
        //从 x（或 y）向前找字符 c 在 a（或 b）中第一次出现的位置。
        if (!xx || !yy) {continue;}
        //如果没有，那么只好 continue 掉了。
        dfs(xx-1,yy-1,z-1,c+s);
        //往下继续搜。
    }
}
```

>Q：为啥是从 $x$（或 $y$）向前找字符 $c$ 在 $a$（或 $b$）中**第一次**出现的位置？不能选字符 $c$ 第二次及以上出现的位置吗？
>
>A：当然可以！但是选第一次出现的位置以后会有更大的选择空间，并且对答案无影响。

>Q：为啥是从后往前搜？
>
>A：这个你一会就知道了。

可以发现，*从 $x$（或 $y$）向前找字符 $c$ 在 $a$（或 $b$）中第一次出现的位置*这个过程会花费不少时间，能优化吗？

既然我在题解中说了，那必然可以。

再新开两个数组 $nea_{i,c},neb_{j,c}$。

$nea_{i,c}$ 表示从 $i$ 向前找字符 $c$ 在 $a$ 中第一次出现的位置。

$neb_{j,c}$ 表示从 $j$ 向前找字符 $c$ 在 $b$ 中第一次出现的位置。

$nea,neb$ 预处理代如下：

```cpp
for (int i=1;i<=n;i++) {
	ca[a[i]-'a']=i;
		for (int j=0;j<26;j++) {
			nea[i][j]=ca[j];
		}
	}
for (int i=1;i<=m;i++) {
	cb[b[i]-'a']=i;
	for (int j=0;j<26;j++) {
		neb[i][j]=cb[j];
	}
}
```

其中 $ca,cb$ 是辅助数组。

这样以来，*从 $x$（或 $y$）向前找字符 $c$ 在 $a$（或 $b$）中第一次出现的位置*这个过程就能直接 $\mathcal{O}(1)$ 地搞了。

但这还不够。

还能加啥优化？

把 DFS 第二行变成 `if (min(x,y)<z) {return ;}`？

呃，其实有更好的。

$f_{x,y}$ 不就能表示 $a$ 长度为 $x$ 的前缀与 $b$ 长度为 $y$ 的前缀的最长公共子序列的长度吗？

于是上面的 `if` 直接进化为 `if (f[x][y]<z) {return ;}`。

然后就能过题了。

你应该也明白了为啥是从后向前了吧？

# 码儿

```cpp
#include<bits/stdc++.h>
#define qwq return
using namespace std;
const int N=85,M=30;
int T,n,m;
char a[N],b[N],ca[N],cb[N];
int nea[N][M],neb[N][M],f[N][N];
vector<string> ans;
inline int read() {
	int x=0,f=1;
	char c=getchar();
	while (!isdigit(c)) {f=(c=='-'?-1:1);c=getchar();}
	while (isdigit(c)) {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	qwq x*f;
}
void clear() {
	memset(ca,0,sizeof ca);
	memset(cb,0,sizeof cb);
	memset(nea,0,sizeof nea);
	memset(neb,0,sizeof neb);
	memset(f,0,sizeof f);
	ans.clear();
}
void dfs(int x,int y,int z,string s) {
	if (!z) {ans.push_back(s);qwq ;}
	if (f[x][y]<z) {qwq ;}
	for (int i=0;i<26;i++) {
		if (!nea[x][i] || !neb[y][i]) {continue;}
		dfs(nea[x][i]-1,neb[y][i]-1,z-1,char(i+'a')+s);
	}
}
int main() {
	T=read();
	while (T--) {
		clear();
		scanf("%s%s",a+1,b+1);
		n=strlen(a+1);
		m=strlen(b+1);
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=m;j++) {
				f[i][j]=max(f[i-1][j],f[i][j-1]);
				if (a[i]==b[j]) {f[i][j]=max(f[i][j],f[i-1][j-1]+1);}
			}
		}
		for (int i=1;i<=n;i++) {
			ca[a[i]-'a']=i;
			for (int j=0;j<26;j++) {
				nea[i][j]=ca[j];
			}
		}
		for (int i=1;i<=m;i++) {
			cb[b[i]-'a']=i;
			for (int j=0;j<26;j++) {
				neb[i][j]=cb[j];
			}
		}
		dfs(n,m,f[n][m],"");
		sort(ans.begin(),ans.end());
		for (string i : ans) {cout<<i<<"\n";}
	}
	qwq 0;
}
```

Thanks for reading！

---

## 作者：xyvsvg (赞：0)

首先 LCS 各位都会求，那么我们只需要在转移时顺便维护一下可行方案即可。

即，我们设 $f_{i,j}$ 为考虑到 $i,j$ 位置时的答案，设 $cnt_{i,j}$ 表示 $f_{i,j}$ 取最值时的所有方案（使用 ```set``` 维护）。

由于保证方案数不超过 $1000$，所以复杂度为 $O(nmV\log V)$，其中 $V=1000$，$n,m$ 分别为两个字符串的长度，可以通过。

参考实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef set<string> bst;
void solve()
{
    string a,b;
    cin>>a>>b;
    int n=a.size(),m=b.size();
    a=' '+a,b=' '+b;
    vector<vector<int> >dp(n+10,vector<int>(m+10,0));
    vector<vector<bst> >cnt(n+10,vector<bst>(m+10));
    auto trans=[&](int &x,int y,bst&a,bst&b)
    {
        if(x<y)
            x=y,a=b;
        else if(x==y)
            for(const auto&s:b)
                a.insert(s);
    };
    int ans=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            if(a[i]==b[j])
            {
                dp[i][j]=dp[i-1][j-1]+1;
                for(const auto&s:cnt[i-1][j-1])
                    cnt[i][j].insert(s+a[i]);
                if(cnt[i][j].empty())
                    cnt[i][j].insert(string({a[i]}));
            }
            trans(dp[i][j],dp[i-1][j],cnt[i][j],cnt[i-1][j]);
            trans(dp[i][j],dp[i][j-1],cnt[i][j],cnt[i][j-1]);
            ans=max(ans,dp[i][j]);
        }
    bst out;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(dp[i][j]==ans)
                for(const auto&s:cnt[i][j])
                    out.insert(s);
    for(const auto&s:out)
        cout<<s<<endl;
    cout<<endl;
}
signed main()
{
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}

```

---

## 作者：鱼跃于渊 (赞：0)

一道不错的 dp 题，可以练练输出方案。
## 1. 做法
首先我们显然可以将问题转化为 LCS，求法应该不用多说。  
最大的难点就在于如何按字典序输出每个方案，我们考虑使用搜索先求出所有方案在进行排序。  
搜索不加剪枝是过不了的，为方便起见，我们从后往前处理。  
我们设 $ls_{i,j}$ 为第 $i$ 个字符在字符串 $s$ 的 $1$ 到 $j$ 出现的最大下标，$lt_{i,j}$ 同理，表示字符串 $t$ 的。  
则我们在搜索的时候设 $\mathrm{len}$ 为 LCS 剩下的长度，若字符 $x$ 有所对应的 LCS 的长度等于 $\mathrm{len}$，就把 $x$ 加入当前字符串中，若 $\mathrm{len}=0$ 就将当前字符串加入答案中。
## 2. 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=85;
char s[N],t[N];
int T,n,m,mx,f[N][N],ls[N][N],lt[N][N];
vector <string> ans;
void dfs(string st,int len,int ps,int pt){
	if(!len){
		ans.push_back(st);
		return;
	}
	if(ps<1||pt<1) return;
	char op;
	for(int i=0,p1,p2;i<26;i++){
		p1=ls[i][ps];p2=lt[i][pt];
		if(f[p1][p2]!=len) continue;
		op=i+'a';
		dfs(op+st,len-1,p1-1,p2-1);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		memset(f,0,sizeof(f));ans.clear();mx=0;
		cin>>(s+1)>>(t+1);
		n=strlen(s+1);m=strlen(t+1);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				f[i][j]=max({f[i-1][j],f[i][j-1],f[i-1][j-1]+(s[i]==t[j])});
				mx=max(mx,f[i][j]);
			}
		}
		for(int i=0;i<26;i++){
			for(int j=1;j<=n;j++)
				ls[i][j]=(s[j]-'a'==i?j:ls[i][j-1]);
			for(int j=1;j<=m;j++)
				lt[i][j]=(t[j]-'a'==i?j:lt[i][j-1]);
		}
		dfs("",mx,n,m);
		sort(ans.begin(),ans.end());
		for(auto s:ans) cout<<s<<'\n';
	}
	return 0;
} 
```

---

## 作者：Erica_N_Contina (赞：0)

## 题意

求出两个字符串的所有最长公共子序列。即其 LCS 可能不止一个，请按字典序把所有 LCS 输出。

## 思路

让我们来回顾一下 LCS 的普通求法。

### LCS

我们定义 $dp_{i,j}$ 为字符串 $A$ 前 $i$ 位和 $B$ 的前 $j$ 位可以构成的 LCS 长度。

转移 $dp_{i,j}=\max(dp_{i-1,j},dp_{i,j-1},dp_{i-1,j-1}+[A_i=B_j])$。

那么我们怎么样来记录 LCS 呢？

如果我们只需要求出一种方案，那么我们只需要在转移的时候记录自己是从哪里转移过来的即可。

### 一边 dp 一边记录方案

即我们记录数组 $c_{i,j}=1/2/3$，表示 $dp_{i,j}=dp_{i-1,j}/dp_{i,j-1}/dp_{i-1,j-1}+[A_i=B_j]$。在输出方案时，我们从 $c_{n,m}$ 一直往回走到 $c_{1,1}$，并顺便记录答案即可。

对于多种方案的情况，其实就是在转移的时候 $dp_{i-1,j}/dp_{i,j-1}/dp_{i-1,j-1}+[A_i=B_j]$ 中有值相等的情况。因为每个点最多只有 $3$ 种转移，所以我们扩展一维 $c_{n,m,3}$，最后一维为 bool，标记从哪转移过来是否可行。

最后输出的时候，我们用 dfs 扫描一遍即可。

其实还有一种做法，不需要第 $3$ 维的辅助：

### 预处理后倒序拼凑

我们处理出的 $dp$ 数组难道只有 $dp_{n,m}$ 有用吗？不不不，其他的也要用上！既然 $dp_{i,j}$ 存储了从 $A$ 中取前 $i$ 个，$B$ 中取前 $j$ 个可以组成的 LCS 的长度，我们就可以考虑用这个信息做一些判定。

我们考虑用双指针，一开始分别指向 $A,B$ 的末尾，然后不断往前拼凑出我们要的 LCS 。这样的话我们同样需要使用 dfs，思维也和上面的差不多，但是实现起来更简单了。

但是这样写我们需要处理出两个数组 $cA,cB$，$cA_{i,j}$ 满足 $A_{cA_{i,j}}=A_i$，这样我们在双指针不断往前找的时候就简单许多了。

当我们的一个 dfs 分支拼凑出了目标长度的公共子序列，我们就结束这个分支，并且把序列加入到 $ans$ 列表中

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*/
///////ACACACACACACAC///////////
#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;
const int N=1e2+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;
int n,m,p,q,T,s[N];
int dp[N][N];
int cA[N][N], cB[N][N];

vector<string> ans;

void init(){
	memset(dp, 0, sizeof dp);
	memset(cA, 0, sizeof cA);
	memset(cB, 0, sizeof cB);
	ans.clear();
}
void lcs(string s1, string s2) {

	int len1 = s1.size(), len2 = s2.size();
	
	for (int i = 1; i <= len1; i++)//dp部分 
        for (int j = 1; j <= len2; j++) {
			dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
	}
	
	for (int i = 1; i <= len1; i++)
        for (int j = 0; j < 26; j++){
        	if (s1[i - 1] == char('a' + j)) cA[i][j] = i; 
			else cA[i][j] = cA[i - 1][j];//存储A串中第i个位置前面的最近的字符j的下标 
		}
	            
	for (int i = 1; i <= len2; i++)
        for (int j = 0; j < 26; j++){
        	if (s2[i - 1] == char('a' + j)) cB[i][j] = i; 
			else cB[i][j] = cB[i - 1][j];//存储B串中第i个位置前面的最近的字符j的下标
		}
	           
}
void dfs(int i, int j, int len, string s) {
	if (!len) {//已经凑齐了len长了 
		ans.push_back(s);
		return ;
	}
	if (!(i||j)) return;//剪枝 
	
	for (int k = 0; k < 26; k++) {
		int kA = cA[i][k], kB = cB[j][k];
		//不断根据cA,cB数组往前跳，并且通过dp数组判定这样跳是否可以得到长度符合要求的公共子序列 
		if (dp[kA][kB] != len)continue;
		dfs(kA - 1, kB - 1, len - 1, char('a' + k) + s);
		//因为我们是从后往前凑的，所以新的字符一个接在s的前面 
	}
}
void solve() {
	string s1, s2;
	cin >> s1 >> s2;
	init();
	
	lcs(s1, s2);
	int len1 = s1.size(), len2 = s2.size();
	
	dfs(len1, len2, dp[len1][len2], "");//dp[len1][len2]就是lcs的长度 
	
	sort(ans.begin(), ans.end());//按字典序排序 
	for (auto v:ans)cout << v << endl;
}
signed main() {
	int T;
	cin >> T;
	while (T--)solve();
	return 0;
}
```




---

