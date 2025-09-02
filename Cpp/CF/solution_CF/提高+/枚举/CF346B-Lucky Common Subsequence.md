# Lucky Common Subsequence

## 题目描述

In mathematics, a subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements. For example, the sequence BDF is a subsequence of ABCDEF. A substring of a string is a continuous subsequence of the string. For example, BCD is a substring of ABCDEF.

You are given two strings $ s_{1} $ , $ s_{2} $ and another string called $ virus $ . Your task is to find the longest common subsequence of $ s_{1} $ and $ s_{2} $ , such that it doesn't contain $ virus $ as a substring.

## 样例 #1

### 输入

```
AJKEQSLOBSROFGZ
OVGURWZLWVLUXTH
OZ
```

### 输出

```
ORZ
```

## 样例 #2

### 输入

```
AA
A
A
```

### 输出

```
0
```

# 题解

## 作者：是个汉子 (赞：14)

[洛谷传送门](https://www.luogu.com.cn/problem/CF346B)	[CF传送门](http://codeforces.com/problemset/problem/346/B)

### Solution

这其实就是加强版的LCS问题。

原来的dp数组是 $f_{i,j}$ ，代表第一个串匹配到 $i$ 位，第二个串匹配到 $j$ 位的最大长度。

现在加入了第三个串，所以dp数组也要改为 $f_{i,j,k}$ ，多了一个第三个串匹配到 $k$ 位。

所以要用KMP将第三个串的能匹配情况算出来。

设当第一个串匹配到 $i$ 位，第二个串匹配到 $j$ 位时，能匹配到第三个串的 $t$ 位，可得转移方程：
$$
f_{i,j,t}=\max\{f_{i,j,t},f_{i-1,j-1,k}\}\\f_{i,j,k}=\max\{f_{i-1,j,k},f_{i,j-1,k},f_{i,j,k}\}
$$
但是，为了~~偷懒~~追求最优，我的 $f$ 数组是用 $\operatorname{string}$ 表示的，转移时直接比较 $\operatorname{size}$ 即可。

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
string a,b,c,dp[111][111][111],ans;
int f[111];
inline void change(string &a,string b){
    if(a.size()<b.size()) a=b;
}

int main(){
    cin>>a>>b>>c;
    int la=a.size(),lb=b.size(),lc=c.size();
    int j=0;
    for(int i=1;i<lc;i++){
        while(j>0&&c[i]!=c[j]) j=f[j-1];
        if(c[i]==c[j]) f[i]=++j;
    }
    for(int i=1;i<=la;i++)
        for(int j=1;j<=lb;j++)
            for(int k=0;k<lc;k++){
                if(a[i-1]==b[j-1]){
                    char tmp=a[i-1];
                    int t=k;
                    while(t>0&&tmp!=c[t]) t=f[t-1];
                    if(tmp==c[t]) t++;
                    change(dp[i][j][t],dp[i-1][j-1][k]+tmp);
                }
                change(dp[i][j][k],dp[i-1][j][k]);
                change(dp[i][j][k],dp[i][j-1][k]);
            }
    for(int i=0;i<lc;i++) change(ans,dp[la][lb][i]);
    if(ans.size()==0) puts("0");
    else printf("%s\n",ans.c_str());
    return 0;
}
```



---

## 作者：氧少Kevin (赞：3)

# CF346B - Lucky Common Subsequence
>- 链接：https://codeforces.com/problemset/problem/346/B
>- 知识点：DP、KMP
>- 难度：紫（*2000）

## 题意
- 给出两个字符串 $A$ 和 $B$，再给出一个模式串 $S$。
- 求 $A$ 和 $B$ 的最长公共子序列，要求不包含子串 $S$。
- 若有多个答案，输出任意。

## 思路
- 我们先考虑怎么求最长的长度。
- 令 $dp[i][j][k]$ 为 $A$ 的前 $i$ 位和 $B$ 的前 $j$ 位形成的最长子序列中，与 $S$ 串匹配长度为 $k$ 的最长的长度。
### 错误思路
- 
### 正确思路
- 使用 KMP 预处理出 $S$ 串的 $\text{nxt}$ 数组
- 我们知道，$nxt[i]$ 表示 $S$ 串的**前 $i$ 个字符**的**最长前后缀**长度。
- 根据 $\text{nxt}$ 数组，用 KMP 处理出 $arr[i][ch]$，代表目前已经和 $S$ 串匹配了 $i$ 位，如果下一个字符是 $ch$，那么加上这个字符后，将会和 $S$ 串匹配多少位。
- 转移：
    - 若 $A_i=B_j$，$dp[i][j][tmp] \leftarrow dp[i-1][j-1][k]+1$，其中 $tmp=arr[k][A_i]$
    - 若 $A_i\neq B_j$，$dp[i][j][k] \leftarrow \max(dp[i-1][j][k],dp[i][j-1][k])$
## 代码
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
const int N		= 110;
const int INF	= 1e9;
using namespace std;

struct PRE{int x,y,z;} pre[N][N][N];
bool flag[N][N][N];

int nxt[N];
int nxt2[N][26];
string A,B,S;

void GetNxt()
{
	int l=0;
	for(int r=2; r<S.length(); r++)
	{
		while(l>0 && S[r]!=S[l+1]) 
		{
			l = nxt[l];
		}
		if(S[r] == S[l+1]) 
		{
			l++;
		}
		nxt[r] = l;
	}
	
	for (int i=0; i<S.length()-1; i++)
	{
		for (int ch=0; ch<26; ch++)
		{
			int cur = i;
			while(cur && S[cur+1]-'A'!=ch)
			{
				cur = nxt[cur];
			}
			cur += (S[cur+1]-'A'==ch);
			
			nxt2[i][ch] = cur;
		}
	}
	
	for (int ch=0; ch<26; ch++)
	{
		nxt2[ S.length()-1 ][ch] = S.length()-1;
	}
}

int dp[N][N][N];
int n,m;

void Find(int x,int y,int z)
{
	if(x==0 || y==0)return;
	Find(pre[x][y][z].x, pre[x][y][z].y, pre[x][y][z].z);
	printf("%c",A[x]);
}

void Sol()
{
	GetNxt();
	memset(dp, -1, sizeof(dp));
	
	dp[0][0][0] = 0;
	
	for (int i=0; i<=n; i++)
	{
		for (int j=0; j<=m; j++)
		{
			if(i>=1 && j>=1 && A[i] == B[j])
			{
				for (int k=0; k<S.length(); k++)
				{
					if(dp[i-1][j-1][k] != -1)
					{
						int tmp = nxt2[k][ A[i]-'A' ];
						
						if(dp[i-1][j-1][k]+1 > dp[i][j][tmp])
						{
							dp[i][j][tmp] = dp[i-1][j-1][k] + 1;
							
							flag[i][j][tmp] = true;
							
							if(flag[i-1][j-1][k])	pre[i][j][tmp] = {i-1,j-1,k};
							else pre[i][j][tmp] = pre[i-1][j-1][k];
						}
					}
				}
			}
			for (int k=0; k<S.length(); k++)
			{
				if(i>=1)
				{
					if(dp[i-1][j][k] > dp[i][j][k])
					{
						dp[i][j][k] = dp[i-1][j][k];
						if(flag[i-1][j][k]) pre[i][j][k] = {i-1,j,k};
						else pre[i][j][k] = pre[i-1][j][k];
					}
				}
				if(j>=1)
				{
					if(dp[i][j-1][k] > dp[i][j][k])
					{
						dp[i][j][k] = dp[i][j-1][k];
						if(flag[i][j-1][k]) pre[i][j][k] = {i,j-1,k};
						else pre[i][j][k] = pre[i][j-1][k];
					}
				}
			}
		}
	}
	
	int ans = 0;
	PRE ans_pre;
	for (int i=0; i<S.length()-1; i++)
	{
		if(dp[n][m][i] >= ans)
		{
			ans = dp[n][m][i];
			if(flag[n][m][i]) ans_pre = {n,m,i};
			else ans_pre = pre[n][m][i];
		}
	}
	if(ans==0)
	{
		printf("%d\n",ans);
		return;
	}
	Find(ans_pre.x, ans_pre.y, ans_pre.z);
}


int main()
{
	cin>>A>>B>>S;
	A = ' '+A;
	B = ' '+B;
	S = ' '+S;
	
	n = A.length()-1;
	m = B.length()-1;
	
	Sol();
	
	return 0;
}
```

---

## 作者：Boxxxxxx (赞：3)

[博客连接](https://blog.csdn.net/qq_43804974/article/details/106583837)

这道题应该是比较典型的利用kmp去dp的题目。

我们思考题意他要求我们的子序列不能够和virus串完全匹配，那么我们就可以在原先求最长公共子序列的基础上在加一个维度。

就是
f[i][j][z]，第一个串枚举到i，第二个串枚举到j，然后他们与virus串匹配的长度是z。

接下来思考转移。

第一个串当做A数组，第二个串当做B数组

即当(A[i] == B[j])的时候可以在原先已经有的子序列基础上加上字符A[i],这个时候与virus匹配到的长度是z。



那么这个长度z是由谁转移来的？这个地方需要kmp去预处理。

我们枚举virus串的长度，然后就假设当前长度为templen，然后枚举下一个字符是谁‘A'-'Z',利用next数组就可以得到加上下一个字符后，与virus串匹配上的长度，（这个部分就是kmp的最基础应用）.

预处理后我们就可以知道有哪些状态加上A[i]这个字符可以到达z状态，这就可以进行转移了。

唯一与最长公共子序列有区别就是(A[i] == B[j])，其他是一样的。

复杂度就是O( | s1 | * | s2 | * | virus|)

在输出路径方面就是和大部分输出路径一样倒推回去就好了

```cpp
char A[max_], B[max_], S[max_];
int next_[max_],lenS,lenA,lenB;
il void getnext() {
	lenS = strlen(S + 1);
	int j = 0;
	for (int i = 2; i <= lenS; i++) {
		while (j&&S[j + 1] != S[i]){
			j = next_[j];
		}
		if (S[j + 1] == S[i])j++;
		next_[i] = j;
	}
}
vector<int> to[max_][30];
int f[max_][max_][max_];
void dfs(int i, int j, int z) {
	if (A[i] == B[j]) {
		for (auto qian : to[z][A[i] - 'A']) {
			if (f[i][j][z] == f[i - 1][j - 1][qian] + 1) {
				dfs(i - 1, j - 1, qian);
				cout << A[i];
				return;
			}
		}
	}
	if (f[i][j][z] == f[i - 1][j][z]) {
		dfs(i - 1, j, z); return;
	}
	if (f[i][j][z] == f[i][j - 1][z]) {
		dfs(i, j - 1, z); return;
	}
}
signed main() {	
	cin >> (A + 1) >> (B + 1) >> (S + 1);
	lenA = strlen(A + 1);
	lenB = strlen(B + 1);
	getnext();
	for (int i = 0; i <= lenS; i++) {
		for (int j = 0; j <= 25; j++) {
			int now = i;
			while (now && S[now + 1]!='A'+j){
				now = next_[now];
			}
			if (S[now + 1] == 'A' + j)now++;
			to[now][j].push_back(i);
		}
	}
	for (int i = 1; i <= lenA; i++) {
		for (int j = 1; j <= lenB; j++) {
			for (int z = 0; z < lenS; z++) {
				if (A[i] == B[j]) {
					for (auto qian : to[z][A[i] - 'A']) {
						f[i][j][z] = max(f[i][j][z], f[i - 1][j - 1][qian] + 1);
					}
				}
				f[i][j][z] = max(f[i][j][z], f[i - 1][j][z]);
				f[i][j][z] = max(f[i][j][z], f[i][j - 1][z]);
			}
		}
	}
	int ans = 0,stu;
	for (int i = 0; i < lenS; i++) {
		if (ans < f[lenA][lenB][i]) {
			ans = f[lenA][lenB][i];
			stu = i;
		}
	}
	if (ans == 0) { cout << 0; return 0; }
	dfs(lenA, lenB, stu);
	return 0;
}
```


---

## 作者：睿智的憨憨 (赞：1)

## 题目大意

给定三个仅由大写英文字母组成的字符串 $s1,s2,virus$，输出 $s1$ 和 $s2$ 的最长公共子序列，且该子序列的子串中不含 $virus$，$1 \le |s1|,|s2|,|virus| \le 100$。

## 解法分析

找字符串的公共子序列，很容易想到 dp，dp 的状态也很好设：$dp_{i,j,k}$ 表示当前已经考虑过 $s1$ 的前 $i$ 个字符，$s2$ 的前 $j$ 个字符，并且以 $virus$ 的前 $k$ 个字符结尾时的最长公共子序列。

普通的 LCS 就不用多说了，关键是 $virus$ 的前 $k$ 个字符在接上一个会变成 $virus$ 的前几个字符，而 kmp 可以很好地解决这个问题。

整体思路就是：先对 $virus$ 进行 kmp，然后在普通 LCS 的基础上通过 kmp 中得到的 nxt 数组确定第三维应该转移到哪里。答案即为 $dp_{|s1|,|s2|,0 \sim |virus|-1}$ 中最长的字符串。

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
string s1, s2, vr;
int n, m, s;
string dp[110][110][110];
int nxt[N];
void KMP(string t){
	int k;
	nxt[1] = k = 0;
	for (int i = 2; i <= s; i++){
		while (k != 0 && t[i] != t[k + 1])
			k = nxt[k];
		if (t[i] == t[k + 1])
			k++;
		nxt[i] = k;
	}
}
void upd(string &a, string b){
	if (b.size() > a.size())
		a = b;
}
int main(){
	cin >> s1 >> s2 >> vr;
	n = s1.size(), m = s2.size(), s = vr.size();
	s1 = ' ' + s1, s2 = ' ' + s2, vr = ' ' + vr;
	if (n > m)
		swap(n, m), swap(s1, s2);
	KMP(vr);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 0; k < s; k++){
				if (s1[i] == s2[j]){
					int t = k;
					while (t > 0 && s1[i] != vr[t + 1])
						t = nxt[t];
					if (s1[i] == vr[t + 1])
						t++;
					upd(dp[i][j][t], dp[i - 1][j - 1][k] + s1[i]);
				}
				upd(dp[i][j][k], dp[i - 1][j][k]);
				upd(dp[i][j][k], dp[i][j - 1][k]);
			}
	string ans;
	for (int k = 0; k < s; k++)
		if (dp[n][m][k].size() >= ans.size())
			ans = dp[n][m][k];
	if (ans.empty())
		cout << "0\n";
	else
		cout << ans << "\n";
	return 0;
}
```

---

## 作者：dengjunhaodejia09 (赞：0)

看这道题的时候一定要认真看题呀。

我们设 $dp_{i,j,k}$ 表示当前匹配到第一个序列的第 $i$ 位，第二个序列的第 $j$ 位，第三个序列匹配到第 $k$ 位时的最长长度，如果第 $i$ 位与第 $j$ 位相等，则与第三个序列匹配，最后输出最长的答案即可。


```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int dp[105][105][105];
    pair<int,pair<int,int> > pre[105][105][105];
    int nxt[105],jiyihua[105][140];
    string s,t,ss;
    int get_id(int id,int zifu){
        if(jiyihua[id][zifu]){
            return jiyihua[id][zifu];
        }
        int idl=id;
        while(idl!=0 && ss[idl+1]!=zifu){
            idl=nxt[idl];
        }
        if(ss[idl+1]==zifu){
            idl++;
        }
        jiyihua[id][zifu]=idl;
        return idl;
    }
    stack<char> zhan;
    void dfs(pair<int,pair<int,int> > Id){
        if(Id.first==0 && Id.second.first==0 && Id.second.second==0){
            return;
        }
                // cout<<Id.first<<' '<<Id.second.first<<' '<<Id.second.second<<' '<<dp[Id.first][Id.second.first][Id.second.second]<<'\n';
        if(pre[Id.first][Id.second.first][Id.second.second].first==Id.first-1 && pre[Id.first][Id.second.first][Id.second.second].second.first==Id.second.first-1){
            zhan.push(s[Id.first]);
        }
        dfs(pre[Id.first][Id.second.first][Id.second.second]);
    }
    int main(){
        cin>>s>>t>>ss;
        s=" "+s;
        t=" "+t;
        ss=" "+ss;
        int n=s.size()-1,m=t.size()-1,len=ss.size()-1;
        int idj=0;
        for(int i=2;i<=len;i++){
            while(idj!=0 && ss[idj+1]!=ss[i]){
                idj=nxt[idj];
            }
            if(ss[idj+1]==ss[i]){
                idj++;
            }
            nxt[i]=idj;
        }
        memset(dp,0xcf,sizeof(dp));
        dp[0][0][0]=0;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                for(int id=0;id<len;id++){
                    if(i+1<=n && j+1<=m && s[i+1]==t[j+1]){
                        int idl=get_id(id,s[i+1]);
                        // cout<<i<<' '<<j<<' '<<id<<' '<<dp[i][j][id]<<" "<<idl<<'\n';
                        if(dp[i+1][j+1][idl]<dp[i][j][id]+1){
                            pre[i+1][j+1][idl]=make_pair(i,make_pair(j,id));
                            dp[i+1][j+1][idl]=dp[i][j][id]+1;
                        }
                    }
                    if(i+1<=n && dp[i+1][j][id]<dp[i][j][id]){
                        dp[i+1][j][id]=dp[i][j][id];
                        pre[i+1][j][id]=make_pair(i,make_pair(j,id));
                    }
                    if(j+1<=m && dp[i][j+1][id]<dp[i][j][id]){
                        dp[i][j+1][id]=dp[i][j][id];
                        pre[i][j+1][id]=make_pair(i,make_pair(j,id));
                    }
                    // cout<<i<<" "<<j<<' '<<id<<' '<<dp[i][j][id]<<"\n";
                }
            }
        }
        pair<int,pair<int,int> > Id=make_pair(0,make_pair(0,0));
        int Max=0;
        for(int i=0;i<len;i++){
            if(Max<dp[n][m][i]){
                Max=dp[n][m][i];
                // cout<<n<<' '<<m<<' '<<i<<' '<<dp[n][m][i]<<'\n';
                Id=make_pair(n,make_pair(m,i));
            }
        }
        // cout<<Max<<"\n";
        dfs(Id);
        if(zhan.size()==0){
            cout<<0;
            return 0;
        }
        while(zhan.size()){
            cout<<zhan.top();
            zhan.pop();
        }
        return 0;
    }
```

---

