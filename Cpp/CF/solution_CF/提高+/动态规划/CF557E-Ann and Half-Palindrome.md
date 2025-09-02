# Ann and Half-Palindrome

## 题目描述

Tomorrow Ann takes the hardest exam of programming where she should get an excellent mark.

On the last theoretical class the teacher introduced the notion of a half-palindrome.

String $ t $ is a half-palindrome, if for all the odd positions $ i $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF557E/e09f17f23488b7cc1450a3fdab11115b8478958b.png)) the following condition is held: $ t_{i}=t_{|t|-i+1} $ , where $ |t| $ is the length of string $ t $ if positions are indexed from $ 1 $ . For example, strings "abaa", "a", "bb", "abbbaa" are half-palindromes and strings "ab", "bba" and "aaabaa" are not.

Ann knows that on the exam she will get string $ s $ , consisting only of letters a and b, and number $ k $ . To get an excellent mark she has to find the $ k $ -th in the lexicographical order string among all substrings of $ s $ that are half-palyndromes. Note that each substring in this order is considered as many times as many times it occurs in $ s $ .

The teachers guarantees that the given number $ k $ doesn't exceed the number of substrings of the given string that are half-palindromes.

Can you cope with this problem?

## 说明/提示

By definition, string $ a=a_{1}a_{2}...\ a_{n} $ is lexicographically less than string $ b=b_{1}b_{2}...\ b_{m} $ , if either $ a $ is a prefix of $ b $ and doesn't coincide with $ b $ , or there exists such $ i $ , that $ a_{1}=b_{1},a_{2}=b_{2},...\ a_{i-1}=b_{i-1},a_{i}&lt;b_{i} $ .

In the first sample half-palindrome substrings are the following strings — a, a, a, a, aa, aba, abaa, abba, abbabaa, b, b, b, b, baab, bab, bb, bbab, bbabaab (the list is given in the lexicographical order).

## 样例 #1

### 输入

```
abbabaab
7
```

### 输出

```
abaa
```

## 样例 #2

### 输入

```
aaaaa
10
```

### 输出

```
aaa
```

## 样例 #3

### 输入

```
bbaabb
13
```

### 输出

```
bbaabb
```

# 题解

## 作者：柳易辰 (赞：5)

## 前言
题目中要求输出所有子串中字典序第 $k$ 小的半回文串，显然地，用到 $\text{Trie}$。

那么如何求半回文串呢？考虑 $\text{DP}$。  

&nbsp;
## $\text{DP}$
假设输入字符串是 $\overline{s_1s_2s_3...s_{n-2}s_{n-1}s_{n}}$，用 $f_{l,r}$ 表示 $\overline{s_ls_{l+1}...s_{r-1}s_r}$ 是否为半回文串。

思考如何状态转移：
1. $l=r$

	非常显然地，$f_{l,r}=\tt{true}$
    
2. $l+1=r$

   转移同样非常浅显，$f_{l,r}=[s_l=s_r]$
   
3. $l+2=r$

	同 2.，$f_{l,r}=[s_l=s_r]$

4. $l+3=r$

	由于半回文串只要求当 $i$ 为奇数时，子串 $\overline{s_ls_{l+1}...s_{r-1}s_r}$ 满足 $s_{l+i-1}=s_{r-i+1}$，所以只要满足 $s_l=s_r$ 即可，同 2. 3.，$f_{l,r}=[s_l=s_r]$
    
5. $l+k=r(k>3)$

	我们固然可以按照题意枚举 $i$ 判断，这样的时间复杂度是每个子串 $O(n)$，显然太慢。但是根据动态规划的思想，我们可以运用已经求得的量来求新的量。求 $f_{l,r}$ 可以转化为求 $[s_l=s_r]\text{ and }f_{l+2,r-r}$。因为$\overline{s_{l+2}s_{l+3}...s_{r-3}s_{r-2}}$ 是半回文串是 $\overline{s_ls_{l+1}...s_{r-1}s_r}$ 是半回文串的**必要条件**。除此之外，还必须满足$s_l=s_r$。
    
综上，我们可以得到状态转移方程（化简形式）：
$$
f_{l,r}=\begin{cases}
[s_l=s_r],\ r-l<4 \\
[s_l=s_r]\text{ and }f_{l+2,r-2},\ r-l\geqslant 4
\end{cases}
$$

当然，我们也可以将第二维化为字符串的长度，用 $f_{l,r-l+1}$ 记录 $\overline{s_ls_{l+1}...s_{r-1}s_r}$ 是否为半回文串。那么状态转移方程是这样的：
$$
f_{i,l}=\begin{cases}
[s_l=s_{i+l-1}],\ l<4 \\
[s_l=s_{i+l-1}]\text{ and }f_{i+2,l-4}, l\geqslant 4
\end{cases}
$$
&nbsp;
## $\text{Trie}$
$\text{DP}$ 已经做完了，接下来我们来考虑 $\text{Trie}$ 的部分。

显然地，为了求解第 $k$ 小，我们要将字符串一一插入到 $\text{Trie}$ 中。字符串的数量约是 $\frac{n^2}{2}$。单次插入的复杂度约是字符串长度，那么这样的时间复杂度是 $\mathcal{O}(n^3)$，无法通过。

再想，字符串中**只有 $a$ 和 $b$**，那么这个 $\text{Trie}$ 的形态类似于**二叉排序树**。二叉排序树怎么求第 $k$ 小？相信大家都会。

我们只需要在插入时，记录 $\text{Trie}$ 上到任意结点 $p$ 结尾的字符串数量 $c_p$。在查询时，如果 $k\leqslant c_p$，那么输出以 $\text{Trie}$ 上这个结点结尾的字符串。否则分别向左向右搜索。

现在再处理插入的问题。$\text{Trie}$ 是前缀插入。$\overline{s_1},\overline{s_1s_2},...,\overline{s_1...s_{n-2}},\overline{s_1s_{n-1}}$ 均是 $\overline{s_1...s_n}$ 的前缀，可以在插入 $\overline{s_1...s_n}$ 时一并进行处理。

于是我们只要插入 $\overline{s_1...s_n},\overline{s_2...s_n},...,\overline{s_{n-1}...s_n},\overline{s_n}$ 即可。假设插入 $\overline{s_l...s_n}$，进行到字符串上的 $s_i$，此时 $\text{Trie}$ 上插入到点 $p$。那么 $c_p=c_p+f_{l,i}$ （第一种表示方法）。

&nbsp;
## $\text{Code}$
两种状态转移方程的[代码](https://www.luogu.com.cn/paste/m6n1za7a)都有。

$\text{Trie}$ 的存储方法有很多种，这里用的是 $\text{vector}\ +$ 结构体，这样可以防止做题是不知道 $\text{Trie}$ 数组应该开多大又怕 $\text{MLE}$ 的情况。通常只要空间卡的不死都可以用。

---

## 作者：ifffer_2137 (赞：1)

这里是 $O(n^2\log n)$ 的巨卡做法。
### 题意
给定一个字符集大小为 $2$ 的字符串 $s$，要输出它所有子串中字典序第 $k$ 小的半回文串。若字符串 $t$ 是半回文串 ，则对于 $\forall i\in[1,\frac{|t|+1}{2}]∀i∈[1, 2∣t∣+1]$ 且 $i$ 为奇数，满足 $t_i=t_{|t|-i+1}$。数据保证有解。**注意同一子串在字典序排列中出现次数与其在 $s$ 中出现次数相同。**
### 分析
我们发现这个半回文串出奇的没有任何性质，于是我们直接考虑暴力 $O(n^2)$ 枚举回文中心找出所有半回文串，放到一起排个序直接输出第 $k$ 小。

我们要快速排序，只需要快速比较。比较两个子串的字典序的话很简单，只要 $O(n^2)$ 暴力 DP 求出所有后缀的 LCP，就可以 $O(1)$ 分讨求出任意两个子串的 LCP 用于比较字典序了。时间复杂度 $O(n^2\log n)$，瓶颈在排序，但是比较牛的是复杂度不依赖字符集大小。

接下来就可以卡常了。先特判一下全部相等的情况，~~直接乱搞一下就行了~~。然后再加个`Ofast`，`inline`等等，最后把`sort`改成`stable_sort`就冲过去啦|！！！
### 代码

```cpp
//From: ifffer_2137
#pragma GCC("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=5e3+5;
int n,k,tot;
string s;
int lcp[maxn][maxn];
pii sub[maxn*maxn];
inline int min(int x,int y){return x<y?x:y;}
inline bool cmp(pii x,pii y){
	int lenx=x.sec-x.fir+1,leny=y.sec-y.fir+1;
	if(lcp[x.fir][y.fir]>=min(lenx,leny)) return lenx<leny;
	return s[x.fir+lcp[x.fir][y.fir]]<s[y.fir+lcp[x.fir][y.fir]];
}
signed main(){
	cin.tie(0),cout.tie(0);
	cin>>s;n=s.size();s=' '+s;
	k=read();
	bool f=true;
	for(int i=1;i<=n;i++) if(s[i]!='a') f=false;
	if(f&&n>10) goto AllSame;
	f=true;
	for(int i=1;i<=n;i++) if(s[i]!='b') f=false;
	if(f&&n>10) goto AllSame;
	for(int i=n;i>=1;i--){
		for(int j=n;j>=1;j--){
			lcp[i][j]=(s[i]==s[j]?lcp[i+1][j+1]+1:0);
		}
	}
	for(int i=1;i<=n;i++){
		sub[++tot]=mkpr(i,i);
		if(i-1<1||i+1>n) continue;
		int l=i-1,r=i+1;
		while(s[l]==s[r]){
			sub[++tot]=mkpr(l,r);
			l-=2,r+=2;
			if(l<1||r>n) break;
		}
		if(i-2<1||i+2>n) continue;
		l=i-2,r=i+2;
		while(s[l]==s[r]){
			sub[++tot]=mkpr(l,r);
			l-=2,r+=2;
			if(l<1||r>n) break;
		}
	}
	for(int i=1;i<n;i++){
		int l=i,r=i+1;
		while(s[l]==s[r]){
			sub[++tot]=mkpr(l,r);
			l-=2,r+=2;
			if(l<1||r>n) break;
		}
		if(i-1<1||i+2>n) continue;
		l=i-1,r=i+2;
		while(s[l]==s[r]){
			sub[++tot]=mkpr(l,r);
			l-=2,r+=2;
			if(l<1||r>n) break;
		}
	}
	stable_sort(sub+1,sub+tot+1,cmp);
	for(int i=sub[k].fir;i<=sub[k].sec;i++) cout<<s[i];
	cout<<"\n";return 0;
	AllSame:;
	for(int i=1;i<=n;i++){
		k-=(n-i+1);
		if(k<=0){
			for(int j=1;j<=i;j++) cout<<s[j];
			cout<<"\n";return 0;
		}
	}
	return 0;
}
```

---

## 作者：ailanxier (赞：1)

## 算法：dp+字典树

&emsp;&emsp;在CF刷字符串题的时候遇到了这题，其实并没有黑题这么难，个人感觉最多是紫题吧（~~虽然一开始以为是后缀自动机的神仙题~~）。

&emsp;&emsp;首先注意到字符串 $s$ 长度很小( $1\le|s|\le5000$ ),可以 $\mathcal O(n^2)$ 地把所有子串求出来，再用Trie树存起来，这样就方便我们dfs求字典序第 $k$ 小的半回文串。所以问题重心变为怎么快速判断这些子串是否为半回文串。根据半回文串的特点，长度长的半回文串是包含长度小的半回文串的，所以我们可以用区间dp解决。设 $f[i][l]$ 表示 $s[i,i+l-1]$ 是否为半回文串，它的转移方程可以写作( $[A]$ 表示 $A$ 为真时值为1，否则为0)：
$$
\left\{\begin{array}{l}f[i][1]=1\\ f[i][2]=[s[i]=s[i+1]]\\f[i][3]=[s[i]=s[i+2]]\\f[i][4]=[s[i]=s[i+3]] \\ f[i][l]~=[~s[i]=s[i+l-1]\&\&f[i+2][l-4]~],l\ge5\end{array}\right.
$$
&emsp;&emsp;这样dp的时间复杂度也是 $\mathcal  O(n^2)$ 的。之后dfs求解第 $k$ 小的半回文串就比较简单了，由于Trie节点数也是 $\mathcal O(n^2)$ 的，所以总时间复杂度是 $\mathcal O(n^2)$ 的。

## $Code:$

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e3 + 5;
bool f[N][N];
int trie[N * N][2],cnt,num[N * N],tot,k;
char s[N+6],ans[N];

void dfs(int now){
    for(int i = 0;i <= 1;i++){
        int next = trie[now][i];
        if(next == 0) continue;
        //如果该节点所表示的半回文串数量大于k，说明答案就是该半回文串。
        if(k <= num[next]) {
            ans[++tot] = i + 'a';
            for(int j = 1; j <= tot; j++) printf("%c", ans[j]);
            exit(0);
        }
        k -= num[next];     //k为全局变量
        ans[++tot] = i + 'a';
        dfs(next);
        tot--;
    }
}

int main() {
    scanf("%s %d",s+1,&k);
    int len = strlen(s+1);
    for(int i = 1;i <=len;i++) f[i][1] = 1;
    for(int i = 1;i < len;i++) f[i][2] = s[i] == s[i+1];
    for(int i = 1;i < len;i++) f[i][3] = s[i] == s[i+2];
    for(int i = 1;i < len;i++) f[i][4] = s[i] == s[i+3];
    for(int l = 5;l <= len;l++)
        for(int i = 1; i <= len; i++)
            f[i][l] = (s[i] == s[i+l-1] && f[i+2][l-4]);
    //将s所有子串加入trie树中
    for(int i = 1;i <= len;i++){
        int now = 0;
        for(int l = 1; l+i-1 <= len; l++){
            int c = s[i+l-1] - 'a';
            if(trie[now][c] == 0) trie[now][c] = ++cnt;
            now = trie[now][c];
            if(f[i][l]) num[now]++;
        }
    }
    dfs(0);
    return 0;
}

```



---

## 作者：Terry_RE (赞：0)

# CF557E Ann and Half-Palindrome 题解
## 思路
看到题目发现是字符串匹配问题，所以数据结构用 trie。首先我们考虑朴素算法：枚举字符串的每一个字串，并判断其是否为“半回文串”。如果是则插入 trie。最后前缀遍历字典树即可求出答案。但是，这样做的时间复杂度显然是 $O(n^4)$ 的。  

我们可以利用 trie 的特性，枚举字符串的子字符串开头，在插入字典树时遍历子字符串结尾。同时每插一次就判一次子字符串是否为半回文串。这样做可以优化至 $O(n^3)$，但显然还是会 TLE。  

我们引入**区间 dp** 的思想，预处理字符串所有的半回文子串。然后再枚举子字符串开头插入字典树。这样就可以把时间复杂度优化为 $O(n^2)$，可通过本题。

## 注意点
在前缀遍历时，我们会不断更新答案字符串，这样就会造成不断的插入删除字符，会有较大的时间开销。所以我们需要用 
```cpp
s.push_back('');
s.pop_back('');
```
来更新字符串而不是用 
```cpp
s += '';
```
否则你会喜提 wa on test 11，~~别问我怎么知道的~~。还有就是数组一定要开大，如果你用的 vector 当我没说。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1.5e7;

string str;

int k;

int cnt;
int nxt[N][2];
int num[N];
bool dp[5200][5200];

void update(int l){
	int pos = 0;

	for(int r = l; r < str.size(); ++r){
		if(nxt[pos][str[r] - 'a'] == 0)
			nxt[pos][str[r] - 'a'] = ++cnt;

		pos = nxt[pos][str[r] - 'a'];

		if(dp[l][r])
			num[pos]++;
	}

	//num[pos] ++;

	return ;
}

string ans;
int tot;

void dfs(int pos){
	tot += num[pos];

	if(tot >= k){
		cout << ans;

		exit(0);
	}

	if(nxt[pos][0] ^ 0)
		ans.push_back('a'), dfs(nxt[pos][0]), ans.pop_back();
	
	if(nxt[pos][1] ^ 0)
		ans.push_back('b'), dfs(nxt[pos][1]), ans.pop_back();
}


int main(){
	cin.tie(0) -> ios::sync_with_stdio(false);

	cin >> str;

	int n = str.size();

	str = " " + str;

	cin >> k;

	for(int L = 1; L <= n; ++L)
		for(int l = 1; l + L - 1 <= n; ++l){
			int r = L + l - 1;

			if(L <= 4)
				dp[l][r] = (str[l] == str[r]);
    //注意分类讨论
			else
				dp[l][r] = (str[l] == str[r]) && dp[l+2][r-2]; 
		}

	for(int i = 1; i <= n; ++i)
		update(i);

	dfs(0);

	return 0;
}

```

---

## 作者：ReTF (赞：0)

一个非 dp 的做法。

以下默认字符串下标由 $1$ 开始。

若 $s_{l,r}(l\ge 3,r\le n-2)$ 为半回文串且 $s_{l-2}=s_{r+2}$，则 $s_{l-2,r+2}$ 为半回文串。

可以枚举每个字符作为半回文串的中心字符（偶数长度的半回文串有两个中心字符）按照上述过程向两边扩展。

需要注意的是，每个半回文串有选中心字符和不选中心字符两种选法，也需要进行讨论。

为了找到第 $k$ 小的半回文串，可以把所有的后缀放进一棵字典树中，这样一个子串就转化成了一个后缀的前缀。在插入某个后缀时，将它所有为半回文串的前缀末尾所在的节点权值加 $1$。维护子树权值和，在字典树上递归查询即可求出答案。

详见代码。

```cpp
void insert(int p){
	int x=rt;
	for(int i=p;i<=n;i++){
		int ch=c[i];
		if(!son[x][ch])x=son[x][ch]=++Idx;
		else x=son[x][ch];
		sum[x]+=v[p][i];
	}
}
void dfs(int p){
	int rts=sum[p]-sum[son[p][0]]-sum[son[p][1]];
	//当前节点的串个数
	if(k<=rts)return;//答案就在当前节点上
	k-=rts;//当前节点所代表串的字典序小于它的左右两个儿子，需要先减掉
	if(k<=sum[son[p][0]])ans.push_back(0),dfs(son[p][0]);//在左儿子
	else k-=sum[son[p][0]],ans.push_back(1),dfs(son[p][1]);//在右儿子
}
int main(){
	cin>>str>>k;
	n=str.length();
	for(int i=1;i<=n;i++)c[i]=str[i-1]-'a';
	for(int i=1,lim;i<=n;i++){//枚举长为奇数的半回文串 
		//isv 的两个值代表选中心字符和不选中心字符两种选法时当前子串是否为半回文串
		//rad 为半径，lim 为半径的最大值
		lim=min(i-1,n-i),isv[0]=isv[1]=1;
		for(int rad=0;rad<=lim;rad++){
			isv[rad&1]&=(c[i-rad]==c[i+rad]);
			if(isv[rad&1])v[i-rad][i+rad]=1;
		}
	}
	for(int i=1,lim;i<n;i++){//枚举长为偶数的半回文串 
		lim=min(i,n-i),isv[0]=isv[1]=1;
		for(int rad=1;rad<=lim;rad++){
			isv[rad&1]&=(c[i-rad+1]==c[i+rad]);
			if(isv[rad&1])v[i-rad+1][i+rad]=1;
		}
	}
	for(int i=1;i<=n;i++)
		insert(i);
	for(int i=Idx;i>=0;i--)//维护字典树子树和
		sum[i]+=sum[son[i][0]]+sum[son[i][1]];
	dfs(rt);
	for(int i=0;i<ans.size();i++)
		putchar(ans[i]?'b':'a');
}
```

---

## 作者：qiyue7 (赞：0)

暴力 超级大暴力 两个for循环建立原串Suffix Trie查询排名 一个O(n^2)的dp预处理出所有的half-palindrome  

思路 做法都不难 

但是暴力的做法需要考虑的细节奇多 稍微卡点空间O(4 * n^2) 
(如果建ST时直接处理就O（3 * n^2）, 存在空间复杂度O（n^2/8+n）的小常数做法但是码量太大了没必要)值得一提的是dp处理palindrome的时候细节还是很多的（大概是真正的难点），处理一下就好

AC代码：

```cpp
#include<string>
#include<vector>
#include<regex>
#include<algorithm>
#include<random>
#include<map>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory.h>
#include<functional>
#include<array>
using namespace std;
array<array<bool, 5200>, 5200> matrix;
string s;
int trie[25200000][2], deep[25200000], fa[25200000], ans[25200000];
int last[10000];
array<char, 6000> ch;
int N;
int len = 0;
void dfs1(int a, int k)
{
	if (k == 0)
	{
		matrix[a][a] = true;
		while (a - k > 0 && ch[a - k] == ch[a + k])
			matrix[a - k][a + k] = true, k++;
		if (k != 0)
			k--;
		dfs1(a, k + 2);
		return;
	}
	if (a - k < 0)
		return;
	if (ch[a - k] == ch[a + k])
	{
		matrix[a - k][a + k] = true;
		dfs1(a, k + 2);
	}
}
void dfs2(int a, int k)
{
	if (k == 0)
	{
		while (a - k > 0 && ch[a - k] == ch[a + k-1])
			matrix[a - k][a + k-1] = true, k++;
		if (k != 0)
			k--;
		dfs2(a, k + 2);
		return;
	}
	if (a - k < 0)
		return;
	if (ch[a - k] == ch[a + k-1])
	{
		matrix[a - k][a + k-1] = true;
		dfs2(a, k + 2);
	}
}
list<int> st;
int K;
bool dfs3(int p)
{
	//cout << K <<" "<<ans[p]<< endl;
	K -= ans[p];
	if (K < 1)
		return true;
	for (int i = 0; i < 2; ++i)
	{
		if (trie[p][i] != -1)
		{
			st.push_back(i);
			if (dfs3(trie[p][i]))
				return true;
			st.pop_back();
		}
	}
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	memset(ans, 0, sizeof(ans));
	memset(trie, -1, sizeof(trie));
	cin >> s;
	ch.fill(-1);
	int root = 0, p, cur = 1;
	deep[0] = 0;
	N = s.size();
	for (int i = 0; i < s.size(); ++i)
	{
		p = root;
		for (int j = i; j < s.size(); ++j)
		{
			if (trie[p][s[j] - 'a'] == -1)
			{
				trie[p][s[j] - 'a'] = cur++;
				deep[trie[p][s[j] - 'a']] = deep[p] + 1;
				fa[trie[p][s[j] - 'a']] = p;
				p = trie[p][s[j] - 'a'];
			}
			else
				p = trie[p][s[j] - 'a'];
		}
		last[i + 1] = p;
	}
	for (int i = 0; i < 5200; ++i)
		matrix[i].fill(false);
	for (int i = 0; i < s.size(); ++i)
		ch[i + 1] = s[i];
	for (int i = 1; i <= s.size(); ++i)
		dfs1(i, 0), dfs2(i, 0);
	cin >> K;
	for (int i = s.size(); i >0; --i)
	{
		int f = last[i];
		while (f != 0)
		{
			//cout << i << " " << matrix[i][deep[f]+i-1] <<" "<<deep[f]+i-1<< endl;;
			if (matrix[i][deep[f] + i - 1])
				ans[f]++;
			f = fa[f];
		}
	}
	dfs3(0);
	for (auto &s : st)
		cout << char(s+'a');
	cout << endl;
	return 0;
}
```


---

