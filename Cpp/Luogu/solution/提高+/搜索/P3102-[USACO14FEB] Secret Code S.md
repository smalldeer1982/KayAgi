# [USACO14FEB] Secret Code S

## 题目描述

Farmer John has secret message that he wants to hide from his cows; the message is a string of length at least 2 containing only the characters A..Z.

To encrypt his message, FJ applies a sequence of "operations" to it, where an operation applied to a string S first shortens S by removing either some (but not all) of the initial characters or some (but not all) of the final characters from S, after which the original string S is attached either at the beginning or end.  For example, a single operation to the string ABC could result in eight possible strings:

AABC
ABABC
BCABC
CABC
ABCA
ABCAB
ABCBC
ABCC
Given the final encrypted string, please count the number of possible ways FJ could have produced this string using one or more repeated operations applied to some source string.  Operations are treated as being distinct even if they give the same encryption of FJ's message.  For example, there are four distinct separate ways to obtain AAA from AA.

Print your answer out modulo 2014.

农民约翰收到一条的消息，记该消息为长度至少为2，只由大写字母组成的字符串S，他通过一系列操作对S进行加密。


他的操作为，删除S的前面或者后面的若干个字符（但不删光整个S），并将剩下的部分连接到原字符串S的前面或者后面。如对于S=‘ABC’，共有8总可能的操作结果：


AABC

ABABC

BCABC

CABC

ABCA

ABCAB

ABCBC

ABCC

给出加密后的目标字符串，请计算共有多少种加密的方案。


对于同字符的字符串，加密方案不止一种，比如把AA加密成AAA，共有4种加密方案。将你的答案mod 2014后输出。


## 说明/提示

Here are the different ways FJ could have produced ABABA:

1. Start with ABA -> AB+ABA

2. Start with ABA -> ABA+BA

3. Start with AB -> AB+A -> AB+ABA

4. Start with AB -> AB+A -> ABA+BA

5. Start with BA -> A+BA -> AB+ABA

6. Start with BA -> A+BA -> ABA+BA

7. Start with ABAB -> ABAB+A

8. Start with BABA -> A+BABA


## 样例 #1

### 输入

```
ABABA 
```

### 输出

```
8 
```

# 题解

## 作者：Expecto (赞：12)

记忆化搜索简单易懂。

RT，用map存一个字符串的方案数，每次四种情况累加起来

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
map<string,int> f;
int find(string x){
    if (f[x]!=0) return f[x];
    int tmp=1;
    int l=x.size();
    for (int i=1;i*2<l;i++){
        if (x.substr(0,i)==x.substr(l-i,i)) 
            tmp+=find(x.substr(i,l-i))+find(x.substr(0,l-i));
        if (x.substr(0,i)==x.substr(i,i))
            tmp+=find(x.substr(i,l-i));
        if (x.substr(l-2*i,i)==x.substr(l-i,i)) 
            tmp+=find(x.substr(0,l-i));
    }
    return f[x]=tmp%2014;
}
int main(){
    cin>>s;
    cout<<(find(s)+2014-1)%2014;
    return 0;
}
```

---

## 作者：chenxinyang2006 (赞：4)

**本题解适合有想法，但是掉坑的人。完全不会的别看**

这题是个神仙题

本题有两个大坑：

1、不能不删字符，也就是ABA无法变到ABAABA

2、方案数一开始应该为1，表示这个子串一开始有1种方案（即它本身，不变换），但是你应该输出经过变换后的方案，所以还要-1

（但是我很好奇，直接-1不会因为%2014后方案为0，然后输出-1而去世？果然USACO太水了）

然后就可以了，不过我真的想膜拜不看题解一遍AC的人，这两个坑基本上都会掉一个，而且如果两个都有（写初值赋0、可以不删字符的版本）在样例还会负负得正

code：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int n;
char str[105];
int dp[105][105];

bool pre(int s1,int e1,int s2,int e2){
	for(int i = 0;i <= (e2 - s2);i++){
		if(str[s1 + i] != str[s2 + i]){
			return 0;
		}
	}
	return 1;
}

bool las(int s1,int e1,int s2,int e2){
    for(int i = 0;i <= (e2 - s2);i++){
		if(str[e1 - (e2 - s2) + i] != str[s2 + i]){
			return 0;
		}
	}
	return 1;
}

int main(){
	scanf("%s",str + 1);
	n = strlen(str + 1);
	for(int i = 1;i <= n;i++){
		dp[i][i + 1] = 1;
	}
	for(int len = 3;len <= n;len++){
		for(int i = 1;i <= n;i++){
			int j = i + len - 1;
			if(j > n){
				break;
			}
			dp[i][j] = 1;
			for(int k = i;k < j;k++){
				if((k - i + 1) > (j - k)){
				    if(pre(i,k,k + 1,j)){
				    	dp[i][j] = (dp[i][j] + dp[i][k]) % 2014;
				    }
					if(las(i,k,k + 1,j)){
						dp[i][j] = (dp[i][j] + dp[i][k]) % 2014;
					}
				}
				if((k - i + 1) < (j - k)){
					if(pre(k + 1,j,i,k)){
				    	dp[i][j] = (dp[i][j] + dp[k + 1][j]) % 2014;
				    }
					if(las(k + 1,j,i,k)){
						dp[i][j] = (dp[i][j] + dp[k + 1][j]) % 2014;
					}
				}
			}
		}
	}
	printf("%d\n",dp[1][n] - 1);
	return 0;
}

```

最后说一下，本代码是可以卡成$n ^ 4$的，但是USACO数据比较弱智，所以过了

---

## 作者：曹老师 (赞：2)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco14feb-scode.html)

~~一个我独立思考也思考不出来的$DP$题~~

设$f_{i,j}$表示区间$[i , j]$内的方案数。每一个最后组成的字串一部分是原字符串另一部分是原字符串的前缀或后缀，所以枚举断点$K$。

断点$K$将原区间分为$[i , k]$和$[k+1 , j]$，因为两段区间不能相等，所以易得区间较长的为原字符串，问题就是判断另一个字串是不是原字符串的前缀或后缀。可以类似弗洛伊德预处理出，$jud_{i,j,k}$表示$[i , i + k - 1]$和$ [j , j + k - 1]$是否相等，**第三维为长度**。

然后就是四个状态转移方程。注意，长的是原字符串，因此要判断一下长度。

**状态转移方程：（以下的$len1$表示断点$K$的前半段，$len2$表示断点$K$之后的区间）**

$$f_{i,j} += f_{k+1,j} , if(len1 < len2 \quad and \quad (jud_{i,k+1,len1}\quad or \quad jud_{i,j-len1+1,len1}))$$
$$f_{i,j} += f_{i,k} , if(len1 > len2 \quad and \quad (jud_{i,k+1,len2} \quad or \quad jud_{k-len2+1,k+1,len2}))$$

**$or$前面部分为前接，后面部分为后接**

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 2014
using namespace std;

const int L = 105;
int len , jud[L][L][L] , f[L][L];
char s[L];

int main() {
	scanf("%s",s+1);
	len = strlen(s+1);
	for(int i=1; i<=len; i++)
		for(int j=1; j<=len; j++)
			for(int k=1; k + i - 1 <= len && k + j - 1 <= len; k++) {
				if(s[k + i - 1] == s[k + j - 1])
					jud[i][j][k] = 1;
				else
					break;
			}	
	for(int i=1; i<=len; i++)
		for(int j=1; j<=len; j++)
			f[i][j] = 1;
	for(int l=3; l<=len; l++)
		for(int i=1; i+l-1<=len; i++) {
			int j = i + l - 1;
			for(int k=i; k<j; k++) {
				int len1 = k - i + 1 , len2 = j - k;
				if(len1 < len2 && jud[i][k+1][len1])
					f[i][j] = (f[i][j] + f[k+1][j]) % mod;
				if(len1 < len2 && jud[i][j-len1+1][len1])
					f[i][j] = (f[i][j] + f[k+1][j]) % mod;
				if(len1 > len2 && jud[i][k+1][len2])
					f[i][j] = (f[i][j] + f[i][k]) % mod;
				if(len1 > len2 && jud[k-len2+1][k+1][len2])
					f[i][j] = (f[i][j] + f[i][k]) % mod;
			}
		}
	printf("%d",f[1][len] - 1);
	return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3102

---

## 作者：Pine (赞：2)

# 思路

字符串长度较小 暴力预处理相同部分

用dp思想进行区间动规 枚举删去后留下的长度进行更新


```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;
const int mod = 2014;
int dp[120][120];
char a[105];
int f[120][120][120];
int len;
int main()
{
    scanf("%s", (a + 1));
    len = strlen(a + 1);
    for (int i=1; i<=len; i++)
        for (int j=1; j<=len; j++)
            for (int k=1; i+k-1<=len && j+k-1<=len && a[i+k-1]==a[j+k-1]; k++)
                f[i][j][k] = 1;
    for (int i=1; i<=len; i++)
        for (int j=1; j<=len; j++)
            dp[i][j] = 1;
    for (int w=2; w<=len; w++)// 要更新串的长度
        for (int i=1; i+w-1<=len; i++)// 要更新串的开头位置
        {
            int j = i + w - 1;// 要跟新串的结尾位置
            for (int k=1; k*2<w; k++)// 删除后留下K的长度
            {
                if (f[i][i+k][k]) dp[i][j] += dp[i+k][j], dp[i][j] %= mod;
                // 表示要更新串是由i+k~j的长度删去末尾几个字符后加到原串的开头得到
                if (f[i][j-k+1][k]) dp[i][j] += dp[i+k][j], dp[i][j] %= mod;
                // 表示要更新的串是由i+k~j的长度删去开头几个字符后加到原串的开头得到
                if (f[i][j-k+1][k]) dp[i][j] += dp[i][j-k], dp[i][j] %= mod;
                // 表示要更新的串是由i~j-k的长度删去末尾几个字符后加到原串的末尾得到
                if (f[j-2*k+1][j-k+1][k]) dp[i][j] += dp[i][j-k], dp[i][j] %= mod;
                // 表示要更新的串是由i~j-k的长度删去开头几个字符后加到原串的末尾得到
            }
        }
    printf("%d\n", dp[1][len] - 1);
    return 0;
}
```

---

## 作者：Zenith_Yeh (赞：1)

我们只需枚举一个串在哪儿切开是满足条件的，然后不断递归即可。由于搜索量比较大，所以使用 $map$ 优化进行记忆化搜索即可。

**上菜：**

```
#include<bits/stdc++.h>
inline int read()
{	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c&15),c=getchar();
	return f?-x:x;
}
using namespace std;
string qj[105][105],s;
map<string,int> mp;
int dfs(int a,int b,string now)//递归函数
{	if(mp[now])return mp[now];
	int len=now.size(),tot=1;
	len/=2;
	if(now.size()%2==0)len--;
	for(register int i=1;i<=len;++i)
	{	if(qj[a][i]==qj[a+i][i])//四个判断
		{	tot+=dfs(a+i,b,qj[a+i][b-a+1-i]);
			tot%=2014;
		}
		if(qj[a][i]==qj[b-i+1][i])
		{	tot+=dfs(a+i,b,qj[a+i][b-a+1-i]);
			tot%=2014;
		}
		if(qj[b-i+1][i]==qj[a][i])
		{	tot+=dfs(a,b-i,qj[a][b-a+1-i]);
			tot%=2014;
		}
		if(qj[b-i+1][i]==qj[b-i-i+1][i])
		{	tot+=dfs(a,b-i,qj[a][b-a+1-i]);
			tot%=2014;
		}
	}
	mp[now]=tot%2014;
	return tot%2014;
}
int main()
{   cin>>s;
	for(register int i=0;i<s.size();++i)qj[i][1]=s[i];
	for(register int j=2;j<=s.size();++j)
		for(register int i=0;i<=s.size()-j;++i)
			qj[i][j]=qj[i][j-1]+qj[i+j-1][1];
	cout<<(dfs(0,s.size()-1,s)+2013)%2014;//由于自身不算，所以-1
	return 0;
}
```


---

## 作者：羚羊WANG (赞：0)

相信大家看到这里的时候都已经理解了题目意思

这里给大家一个推荐，看一道题最重要的是数据大小

有时候，一道题目的数据范围就决定了一道题的难度和算法

这道题，我们可以发现题目字符串的范围只有$100$

所以我们可以考虑记忆化搜索

用$map$存储之后记忆化即可

代码:

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 2014
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
string s;
map<string,int> mp;
inline int dfs(string x){
//	cout<<x<<endl;
	if(mp[x])
		return mp[x];
	int sum=1;
	for(register int i=1;i*2<x.size();++i)//枚举转移串
		{
			if(x.substr(0,i)==x.substr(x.size()-i,i))
				sum+=dfs(x.substr(i,x.size()-i))+dfs(x.substr(0,x.size()-i));
			if(x.substr(0,i)==x.substr(i,i))
				sum+=dfs(x.substr(i,x.size()-i));
			if(x.substr(x.size()-i*2,i)==x.substr(x.size()-i,i))
				sum+=dfs(x.substr(0,x.size()-i));
		}
	mp[x]=(sum%mod+mod)%mod;
	return mp[x];
}
signed main(){
//	freopen("scode.in","r",stdin);
//	freopen("scode.out","w",stdout);
	cin>>s;
	write((dfs(s)%mod-1+mod)%mod);
	return 0;
}
```


---

## 作者：CR_Raphael (赞：0)

赛前做模拟卷做到这题。

题面别看错了，~~因为我就看错了（推荐直接看英文题面），~~给出**加密后的**，问有多少**加密方式**，不是问有多少**原串**。

倒推，每个操作相当于把一大块分成操作新得到的一小块和还可以再由操作得到的一大块。

于是想到“类区间DP”，dp[i][j]表示i到j的区间的分法，O(n)枚举操作情况。注意把原串本身贴在自己前后是不行的。

用记忆化搜索写的。

~~记忆化搜索到底算不算DP啊！~~

为了判断能否操作，需要在O(1)时间内为字符串判等。我们可以用预处理，O(n^3)时间里先算一发：d[i][j][k]表示i开始长k的子串和j开始长k的子串是否相等（长度不等的当然字符串不等），可以用d[i][j][k-1]顺推，这样就OK了。

上代码：（最后输出那个减一是为了减去不加密的原串本身的情况）

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

const int maxn = 105;
const int modd = 2014;

char c[maxn];
int n;
int dp[maxn][maxn];
bool d[maxn][maxn][maxn];

bool checkk(int l, int r, int k) {
	if(k-1 > 0 && !d[l][r][k-1]) return false;
	else return c[l+k-1] == c[r+k-1];
}

int do_dp(int l, int r) {
	if(l == r) return 1;
	if(dp[l][r] != -1) return dp[l][r];
	int i, ll;
	dp[l][r]=1;
	
	for(i=(l+r+1)/2+1; i <= r; i++) {
		ll=r-i+1;
		if(d[l][i][ll]) dp[l][r]=dp[l][r]+do_dp(l, i-1), dp[l][r]%=modd;
	}
	
	for(i=(l+r+1)/2+1; i <= r; i++) {
		ll=r-i+1;
		if(d[i-ll][i][ll]) dp[l][r]=dp[l][r]+do_dp(l, i-1), dp[l][r]%=modd;
	}
	
	for(i=l; i <= (l+r)/2-1; i++) {
		ll=i-l+1;
		if(d[l][i+1][ll]) dp[l][r]=dp[l][r]+do_dp(i+1, r), dp[l][r]%=modd;
	}
	
	for(i=l; i <= (l+r)/2-1; i++) {
		ll=i-l+1;
		if(d[l][r-ll+1][ll]) dp[l][r]=dp[l][r]+do_dp(i+1, r), dp[l][r]%=modd;
	}
	
	return dp[l][r];
}

int main() {
	scanf("%s", c+1);
	n=1;
	while(c[n] != 0) n++;
	n--;
	int i, j, k;
	for(i=1; i <= n; i++)
		for(j=1; j <= n; j++)
			dp[i][j]=-1;
	for(k=1; k <= n; k++) 
		for(i=1; i <= n-k+1; i++) 
			for(j=1; j <= n-k+1; j++) 
				d[i][j][k]=checkk(i, j, k);
	do_dp(1, n);
	
	printf("%d\n", dp[1][n]-1);
	return 0;
}
```

以上。

---

