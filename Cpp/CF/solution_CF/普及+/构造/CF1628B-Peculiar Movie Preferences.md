# Peculiar Movie Preferences

## 题目描述

给定一个含有$n$个字符串的序列，序列中的每个字符串长度均不超过$3$，判断能否从中选出一个非零子段（可以不连续），使得子段中的字符串按照在序列中的顺序首尾相连构成一个回文串。如果能，输出"YES"，否则输出"NO"。

## 样例 #1

### 输入

```
6
5
zx
ab
cc
zx
ba
2
ab
bad
4
co
def
orc
es
3
a
b
c
3
ab
cd
cba
2
ab
ab```

### 输出

```
YES
NO
NO
YES
YES
NO```

# 题解

## 作者：liu_chen_hao (赞：3)

### 简要题意
在 $n$ 个长度不超过 $3$ 字符串中选出若干个（可以不连续），按照原来的顺序排列组成一个新的字符串，问能否组成一个回文串。有多组数据。

$\sum n \le 10^5 $

### 分析
题目中，字符串长度不大于 $3$ 是一个很突兀的条件。仔细想一想，这样能构成回文串的情况会很少：

1. 一个字符串本身就是回文串。

2. 对于长度为 $2$ 的，存在它的倒序串；或者在它后面存在一个长度为 $3$ 的串，其后两位是它的倒序串；或者在它前面存在一个长度为 $3$ 的串，其前两位是它的倒序串。举个例子，$ \texttt {ab}$ 想要构成回文串，要么有 $ \texttt {ba}$，要么在它后面有 $ \texttt {cba}$，要么在它前面有 $ \texttt {bac}$。

3. 对于长度为 $3$ 的，存在它的倒序串；或者它后两位的倒序串在它之前能找到；或者它前两位的倒序串在它之后能找到。举个例子，对于 $ \texttt {abc}$，要么存在 $ \texttt {cba}$，要么在它之前存在 $ \texttt {cb}$，要么在它之后存在 $ \texttt {ba}$。

分析到这里，思路就很明显了：用 C++ STL 里的 map 存下每个字符串，再依次扫描每一个字符串，按照上述情况分情况讨论判断即可。

细节还是有一些的。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int t,n,f;
string s[N],p;
map<string,int> hs;

int main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1; i<=n; i++) cin>>s[i];
		
		// 注意多测清空 
		hs.clear();
		f=0;
		
		// 判断有没有本身就是回文串的 
		for(int i=1; i<=n; i++)
			if(s[i].size()==1 || (s[i].size()==2 && s[i][0]==s[i][1]) || (s[i].size()==3 && s[i][0]==s[i][2]))
			{
				f=1;
				puts("YES");
				break;
			}
		if(f) continue;
		
		// 存到map里 
		for(int i=1; i<=n; i++)
			if(hs.find(s[i])==hs.end()) hs[s[i]]=i;
		
		// 依次扫描 
		for(int i=1; i<=n; i++)
		{
			// 对于长度为2的 
			if(s[i].size()==2)
			{
				p="";
				p+=s[i][1];
				p+=s[i][0];
				if(hs.find(p)!=hs.end())
				{
					f=1;
					puts("YES");
					break;
				}
			}
			// 其余的必为长度为3的 
			else
			{
				// 存在他本身的倒序串 
				p="";
				p+=s[i][2];
				p+=s[i][1];
				p+=s[i][0];
				if(hs.find(p)!=hs.end())
				{
					f=1;
					puts("YES");
					break;
				}
				
				// 它前两位的倒序串
				p="";
				p+=(s[i][1]);
				p+=(s[i][0]);
				if(hs.find(p)!=hs.end() && hs[p]>i)
				{
					f=1;
					puts("YES");
					break;
				}
				
				// 它后两位的倒序串
				p="";
				p+=s[i][2];
				p+=s[i][1];
				if(hs.find(p)!=hs.end() && hs[p]<i)
				{
					f=1;
					puts("YES");
					break;
				}
			}
		}
		if(!f) puts("NO");
	}

	return 0;
}
```


---

## 作者：无钩七不改名 (赞：2)

在比赛的时候我想的是用 $2$ 个字符串拼合来骗分，没想到真的可以过，因为根本没必要用到 $3$ 个或 $3$ 个串以上。

## 思路：

用一个 bool 类型 `bo` 记录是否存在回文，存在为真，不存在为假。如果前面已经判断过为真，则后面的操作可以跳过。

+ 需要注意的是，每组数据操作前 `bo` 都要重置为 $0$。

如果字符串长度为 $1$，那就可以直接判断为回文。

如果字符串长度为 $2$：

+ 如果 $2$ 个字符相同，可以直接判断为回文。

+ 不然的话，先查找长度为 $2$ 且与它相反的字符串，如果存在，判断可以合成回文。

+ 没有的话查找长度为 $3$ 且前 $2$ 个字符与它相反的字符串，如果存在，判断可以合成回文。

如果字符串长度为 $3$：

+ 如果第 $1$ 个和第 $3$ 个字符相同，可以直接判断为回文。

+ 不然的话，先查找长度为 $3$ 且与它相反的字符串，如果存在，判断可以合成回文。

+ 没有的话查找长度为 $2$ 且与它后面 $2$ 个字符相反的字符串，如果存在，判断可以合成回文。


## 代码：

采取的是一种类似 hash 的做法。

但是会被卡，解决方法就是把它变成 hash，比如高一位就那一位的值多 $ \times10$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int T,n;
bool bo;
char c[100005][4];
int val[100005],len[100005];
vector<int> a[85];

int main(){
	//freopen("palindrome.in","r",stdin);
	//freopen("palindrome.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		for(int i=1;i<=85;i++)a[i].clear();
		bo=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) {
			scanf(" %s",&c[i]);
			if(bo)continue;
			len[i]=strlen(c[i]);
			if(len[i]==1||(len[i]==2&&c[i][0]==c[i][1])||(len[i]==3&&c[i][0]==c[i][2])){
				bo=1;
				continue;
			}
			if(len[i]==2){
				val[i]=(c[i][0]-'a'+1)+(c[i][1]-'a'+1);
				if(a[val[i]].size()){
					for(int v:a[val[i]]){
						if(len[v]!=2)continue;
						if(c[v][0]==c[i][1]&&c[v][1]==c[i][0]){
							bo=1;
							break;
						}
					}
				}
				if(bo)continue;
				int y=val[i];
				for(int j=1;j<=26;j++){
					y++;
					if(a[y].size()){
						for(int v:a[y]){
							if(len[v]!=3)continue;
							if(c[v][1]==c[i][0]&&c[v][0]==c[i][1]){
								bo=1;
								break;
							}
						}
					}
				}
			}
			else{
				val[i]=(c[i][0]-'a'+1)+(c[i][1]-'a'+1)+(c[i][2]-'a'+1);
				if(a[val[i]].size()){
					for(int v:a[val[i]]){
						if(len[v]!=3)continue;
						if(c[v][0]==c[i][2]&&c[v][1]==c[i][1]&&c[v][2]==c[i][0]){
							bo=1;
							break;
						}
					}
				}
				if(bo)continue;
				//cout<<11111<<endl;
				val[i]-=(c[i][0]-'a'+1);
				if(a[val[i]].size()){
					for(int v:a[val[i]]){
						if(len[v]!=2)continue;
					//	cout<<v<<"*"<<c[v][1]<<" "<<c[i][2]<<" "<<c[v][0]<<" "<<c[i][1]<<endl;
						if(c[v][1]==c[i][1]&&c[v][0]==c[i][2]){
							bo=1;
							break;
						}
					}
				}
				val[i]+=(c[i][0]-'a'+1);
			}
		//	cout<<val[i]<<"***"<<endl;
			a[val[i]].push_back(i);
		}
		if(bo)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：baoziwu2 (赞：1)

容易想到的一点是，如果当前的字符串序列能构成回文串，那么一定存在只使用 $1$ 个字符串或 $2$ 个字符串拼凑而成。要证明这一点，我们可以利用回文串的性质。

实际上，我们考虑一个大回文串的组成方式仅有 $4$ 种：

- $3 +\cdot \cdot \cdot+ 3$
- $3+\cdot \cdot \cdot+2$
- $2+\cdot \cdot \cdot+3$
- $2+\cdot \cdot \cdot+2$

不难发现，如果我们把中间的字符串全砍掉，剩下的字符仍然是回文串。

那么只需要判断四种情况即可，同时值得注意的一点是题目有顺序要求，因此对于 $3+2$ 型和 $2+3$ 型需要判断顺序。

可以使用 `std::map` 和 `std::string` 来实现代码。

```C++
#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;
const int N = 100010;

int T, n;
string str[N];
map<string, int> mp;

bool checkPalindrome(string &s) {
	return s.front() == s.back();
}

int main() {
	cin >> T;
	while(T--) {
		mp.clear();
		cin >> n;
		bool flag = false;
		
		for(int i = 1; i <= n; ++ i) {
			cin >> str[i];
			if(!mp[str[i]]) mp[str[i]] = i;
		}
		
		for(int i = 1; i <= n; ++ i) {
			if(flag) break;
			if(checkPalindrome(str[i])) flag = true;
			else if(str[i].length() == 2) {
				string t = str[i];
				reverse(t.begin(), t.end());
				if(mp[t]) flag = true;
			} else if(str[i].length() == 3) {
				string t = str[i]; 
				reverse(t.begin(), t.end());
				if(mp[t]) flag = true;
				
				string t1 = t.substr(1);
				if(mp[t1] and mp[t1] > i) flag = true;
				
				string t2 = t.substr(0, 2);
				if(mp[t2] and mp[t2] < i) flag = true;
			}
		}
		
		if(flag) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：1)

首先判掉存在 $|s_i| = 1$，以及存在回文字符串的情况，输出 `YES`。注意到 $|s_i| = 2 / 3$，所以为了让整个子序列形成回文串，序列两端的字符串相拼接必然回文，这一点是显然的。如当 $|s_{i_1}| = 2, |s_{i_k}| = 3$ 时，为了 $s_{i_1} + s_{i_2} + \cdots + s_{i_k}$ 回文，那么 $s_{i_1,0} = s_{i_k, 2},s_{i_1,1} = s_{i_k, 1}$。因此 $s_{i_1} + s_{i_k}$ 回文。

综上，我们只需判断是否存在 $i < j$ 使得 $s_i + s_j$ 回文，这可以通过哈希（字符串转成 $27$ 进制）+ 桶在线性时间内完成。[代码](https://codeforces.com/contest/1628/submission/143645977)。

---

## 作者：Exber (赞：1)

首先如果有字符串是回文串，那么答案直接是 `YES`，否则字符串的长度一定是 $2$ 或者 $3$。

考虑令组成回文串的**最后一个字符串**为 $s$：

- $|s|=2$，那么 $s$ 肯定是形如 $\texttt{ck}$ 这样的字符串，组成的回文串一定以 $\texttt{kc}$ 开头，又因为字符串长度只有可能是 $2$ 或者 $3$，所以找到 $\texttt{kc}$ 或者 $\texttt{kc*}$（$\texttt{*}$ 代表任意字符）即可。

- $|s|=3$，那么 $s$ 肯定是形如 $\texttt{ckj}$ 这样的字符串，组成的回文串一定以 $\texttt{jk}$ 开头，又因为字符串长度只有可能是 $2$ 或者 $3$，所以找到 $\texttt{jk}$ 或者 $\texttt{jkc}$ 即可。

综上，只需要考虑两个串拼接组成的回文串。赛时这个结论是猜出来的，wtcl。

实现时也有一些细节，部分代码如下：

```cpp
int n;
char tmp[5];
string strs[100005];
map<string,bool> mp;

inline void slove()
{
	scanf("%d",&n);
	bool can=false;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",tmp+1);
		int len=strlen(tmp+1);
		strs[i]=tmp+1;
		bool f=true;
		for(int j=1;j<=len/2;j++)
		{
			f&=tmp[j]==tmp[len-j+1];
		}
		if(f)
		{
			can=true;
		}
	}
	if(can)
	{
		puts("YES");
		return;
	}
	mp.clear();
	for(int i=n;i>=1;i--)
	{
		string str1,str2; 
		for(int j=0;j<strs[i].size();j++)
		{
			str1=strs[i][j]+str1;
		}
		for(int j=0;j<strs[i].size()-1;j++)
		{
			str2=strs[i][j]+str2;
		}
		if(mp[str1]||mp[str2])
		{
			puts("YES");
			return;
		}
		mp[strs[i]]=true;
	}
	mp.clear();
	for(int i=1;i<=n;i++)
	{
		string str2;
		for(int j=1;j<strs[i].size();j++)
		{
			str2=strs[i][j]+str2;
		}
		if(mp[str2])
		{
			puts("YES");
			return;
		}
		mp[strs[i]]=true;
	}
	puts("NO");
}
```

---

## 作者：lizhous (赞：0)

## 分析

首先看到串长度小于三，直觉告诉我这个限制会作为时间复杂度出现。~~然后想了很久都不会。~~

其实是性质题。我们发现若原串中有回文，就必然有解。现在可以排除形如 $a$，$aa$，$aaa$，$aba$ 的串。接下来只剩下长度为 $2,3$ 的串了。

设答案的回文串为 $S_{ans}$，任意字符串 $S$ 长 $L_{S}$，则必然有 $S_{ans_1}=S_{ans_{L_{S_{ans}}}},S_{ans_2}=S_{ans_{L_{S_{ans}}-1}}\cdots$。再设 $S_{ans}$ 是由 $s_{p_1},s_{p_2}\cdots s_{p_{len}}(1 \le p_1 < p_2 <\cdots < p_{len})$ 组成。我们分类讨论一下。

- 若 $L_{s_{p_1}}=L_{s_{p_{len}}}=2$，则有 $s_{p_1,1}=s_{p_{len},2},s_{p_1,2}=s_{p_{len},1}$，直接拼接即为回文串。

- 若 $L_{s_{p_1}}=L_{s_{p_{len}}}=3$，则有 $s_{p_1,1}=s_{p_{len},3},s_{p_1,2}=s_{p_{len},2},s_{p_1,3}=s_{p_{len},1}$，直接拼接即为回文串。

- 若 $L_{s_{p_1}}=2$ 且 $L_{s_{p_{len}}}=3$，则有 $s_{p_1,1}=s_{p_{len},3},s_{p_1,2}=s_{p_{len},2}$，直接拼接即为回文串。

- 若 $L_{s_{p_1}}=3$ 且 $L_{s_{p_{len}}}=2$，则有 $s_{p_1,1}=s_{p_{len},2},s_{p_1,2}=s_{p_{len},1}$，直接拼接即为回文串。

综上，我们发现若由解，则必然存在两个字符串拼接后为回文串。开两个 map 分别维护长度为 $2$ 和长度为 $3$ 的字符串是否匹配即可。具体维护方法可以看注释。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<cstring>
#include<map>
#define int long long
#define mod 998244353
using namespace std;
int T,n;
string a;
map<string,bool> mp,mp2; //分别维护长为2,3的串是否可以匹配
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		mp.clear();
		mp2.clear(); //init
		bool flag=false;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			if(flag){continue;} //有解直接跳出
			if(a.size()==1) //长为1的回文判掉
			{
				flag=true;
				continue;
			}
			if(a.size()==2)
			{
				if(a[0]==a[1]) //长为2的回文判掉
				{
					flag=true;
					continue;
				}
				if(mp[a]==true) //abba 或ab*ba
				{
					flag=true;
					continue;
				}
				string al="";
				al+=a[1]; //翻转
				al+=a[0];
				mp[al]=true; //ba**
				mp2[al]=true; //ba***
			}
			if(a.size()==3)
			{
				if(a[0]==a[2]) //长为3的回文判掉
				{
					flag=true;
					continue;
				}
				if(mp2[a]==true) //abccba
				{
					flag=true;
					continue;
				}
				string al="";
				al+=a[1]; //翻转
				al+=a[2];
				if(mp2[al]==true) //ab*ba
				{
					flag=true;
					continue;
				}
				al="";
				al+=a[1]; //翻转
				al+=a[0];
				mp[al]=true; //ba***
				al="";
				al+=a[2]; //翻转
				al+=a[1]; //翻转
				al+=a[0];
				mp2[al]=true; //cba***
			}
		}
		if(flag) //输出
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
}
```

---

## 作者：清烛 (赞：0)

不知道为什么这么水的题会放在 div2 D。。。

我们可以证明，任何回文子序列都可以看作由 $1$ 或 $2$ 个串扩展而来。所以我们判是否有前一个串和后一个串回文或者存在本身回文的字串即可。证明即考虑一个回文的子序列必然可以去掉中间多余的部分，只保留两边或中间。

后者很好判，即判断 $\texttt a$ 型，$\texttt {aa}$ 型或 $\texttt {a?a}$ 型即可。

前者需要考虑 $\texttt{a} +\texttt{a}$ 型，$\texttt{ab} +\texttt{ba}$ 型，$\texttt{abc} +\texttt{cba}$ 型。以及容易漏掉的 $\texttt{a} +\texttt{ba}$ 型，$\texttt{ab} +\texttt{a}$ 型，$\texttt{ab} +\texttt{cba}$ 型和 $\texttt{abc} +\texttt{ba}$ 型。

这些东西可以维护两个 `std::set<std::string>`，非常好实现，稍微注意一下细节就可以了。

```cpp
set<string> mp, mpl;

bool check(string s) {
    if (s.size() == 1) return 1;
    if (s.front() == s.back()) return 1;
    return 0;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        mp.clear(), mpl.clear();
        bool flg = 0;
        FOR(i, 1, n) {
            string s; cin >> s;
            if (check(s)) flg = 1;
            string ss = s; reverse(ss.begin(), ss.end());
            if (mp.count(ss)) flg = 1;
            if (mpl.count(ss)) flg = 1;
            ss.pop_back();
            if (mp.count(ss)) flg = 1;

            mp.insert(s);
            if (s.size() == 3) s.pop_back(), mpl.insert(s);
        }
        if (flg) print("YES");
        else print("NO");
    }
    return output(), 0;
}
```

---

## 作者：HoshizoraZ (赞：0)

期末考结束后康复训练，碰到了这题，刚开始降智了想复杂了不少时间。

## 一些说明

由于字符串最多只有 $3$ 位，所以可以考虑将字符串看作 $26$ 进制数，将其存入哈希表。

对于自己本身存在回文串的情况（包括所有长度为 $1$ 的字符串），直接输出 `YES` 即可。

下文说到的所有**反序串**意思是将字符串前后反转得到的字符串。两个字符串相加就是将这两个串拼接。

## 如何找回文串

这个字符串一定是最简单的，也就是无法通过再删除一个子串使得这个字符串回文。

例如 `ab, cd, cba`，当然可以顺次拼接得到 `abcdcba`，但是可以删掉第二个串，变成 `abcba` 照样是回文串。

最简单的字符串拼接如下（下文数字若无说明代表串长）：

- $2+2$ 或 $3+3$
- $2+3$ 或 $3+2$

至于其它的拼接情况，我们可以做一些测试：

- $2+3+2$ 或 $3+2+3$，显然这个中间位置的字符串就是回文串。
- $2+2+3$ 或 $3+2+2$，由于前两个字符和最后两个字符相同，所以可以删掉第二个字符串。
- $2+3+3$ 或 $3+3+2$，一样可以删掉第二个字符串，理由同上。

（做题时硬是把 $2+3+3$ 看作了简单串，写了一堆冗余的情况……）

至此三串拼接的情况都可以删掉至少一个串，更多串拼接的情况就不用再尝试了。

### 对于第一种情况，$2+2$ 或 $3+3$

对每个字符串**反序串**的哈希值存入表中，如果某个字符串 $a$ 的**正序**哈希值在表中能查到，说明存在一个字符串 $b$，使得 $a$ 反转能得到 $b$，故 $a+b$ 一定是回文串。

### 对于第二种情况，$2+3$ 或 $3+2$

以 $3+2$ 为例，我们会发现前一个串的第 $3$ 个字符是什么都可以，因为它处在正中央位置。

这里有两种处理办法：

- 从左到右枚举，碰到长度为 $3$ 的字符串就**删掉最后一个字符**，并将**反序**哈希值记录到表中；遇到长度为 $2$ 的字符就把它的哈希值拿来找，找到了就输出 `YES`。
- 从左到右枚举，碰到长度为 $3$ 的字符串就**不删除**，并将**反序**哈希值记录到表中；遇到长度为 $2$ 的字符就把它的开头用 `a` 到 `z` 每一个字符都加一遍，算出其其**正序**哈希值并查表。

前者程序复杂度 $\mathcal{O}(n)$，后者 $\mathcal{O}(|S|\times n)$，此处 $|S|$ 代表字符集大小，等于 $26$。

## 代码实现

字符串哈希可以用 `std::map` 代替。

给个[评测链接](https://codeforces.ml/problemset/submission/1628/143853593)。

---

## 作者：Purslane (赞：0)

## Solution

题目大意 : 从 $n$ 个字符串中选出几个 , 按**原有顺序**拼在一起 . 问能否组成一个回文串 .

选择这 $n$ 个字符串 , 共有 $2^n$ 种方法 , 直接枚举显然不可取 . 但因为每个字符串的长度不超过 $3$ 我们有这样一个直觉 : 如果有答案不会太长 . 

当存在一个字符串是回文串时 , 一定符合条件 . 如果是 $2$ 个字符串 , 也好判断 .

> 判断方法 : 这样一定是 $2$ 长度或 $3$ 长度 . 对于每一个字符串 , 配对它的前一半 . 
>
> 当长度为 $2$ 时 , 寻找是否有 $2$ 长度的字符串与之相反或 $3$ 长度的前 $2$ 个字符与之相反  .
>
> 当长度为 $3$ 时 , 寻找是否有 $3$ 长度的字符串与之相反或 $2$ 长度的与之后 $2$ 个字符相反  .
>
> 更加直观的 , 当我们发现 $ab$ 时 , 判断是否有  $ba$ 或 $bac$ ; 当我们发现 $abc$ 时 , 判断是否有 $cba$ 或 $cb$ . 显然可以用  `map` 轻松维护 .

如果有答案 , 是否一定存在长度为 $2$ 个字符串的回文呢 ? 答案是肯定的 . 假设有多个长度的回文串 , 那么组成这个回文串的第一个和最后一个字符串一定可以构成回文 .

> 证明 : 显然 , 第一个和最后一个字符串都不是长度为 $1$ 的 . 否则这个串单独即可构成回文 .
> - 当第一个为 $2$ , 最后一个为 $2$ 时 , 一定是 $ab$ 与 $ba$ 的形式 , 拼在一起满足回文要求 ;
> - 当第一个为 $2$ , 最后一个为 $3$ 时 , 一定是 $ab$ 与 $cba$ 的形式 , 拼在一起满足回文要求 ;
> - 当第一个为 $3$ , 最后一个为 $2$ 时 , 一定是 $abc$ 与 $ba$ 的形式 , 拼在一起满足回文要求 ;
> - 当第一个为 $3$ , 最后一个为 $3$ 时 , 一定是 $abc$ 与 $cba$ 的形式 , 拼在一起满足回文要求 ;

> 综上 , 一定满足要求 .

那么就可以直接执行上述算法了 .

[code](https://codeforces.com/contest/1629/submission/143762102)

---

