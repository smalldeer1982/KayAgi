# [ABC363C] Avoid K Palindrome 2

## 题目描述

给定长度为 $N$ 的字符串 $S$。
请求出 $S$ 重排字符串（包括 $S$ 本身）中，**不包含**长度为 $K$ 的回文子字符串的个数。

但是，长度为 $N$ 的字符串 $T$“包含长度为 $K$ 的回文作为子字符串” 是指$\exist i \le n-k,j=1,2,3,\dots,k,T_{i+j}=T_{i+K+1-j}$成立。

$T_k$ 表示字符串 $T$ 的第 $k$ 个字符。

## 说明/提示

#### 约束条件
- $ 2\le K \le N \le 10$
- $N,K$为整数
- $S$ 长度为 $N$，仅包含小写字母
  
#### 样例 #1 解释
重新排列 `aab` 得到的字符串是 `aab`，`aba`，`baa`，其中 `aab` 和 `baa` 包含长度 $2$ 的回文子串 `aa` 作为部分字符串。因此，满足条件的字符串只有 `aba`，输出 $1$。
#### 样例 #2 解释
排列 `zzyyx` 得到的字符串有 $30$ 个，其中不包含长度 $3$ 的回文子串的字符串有 $16$ 个。因此，输出 $16$。

## 样例 #1

### 输入

```
3 2
aab```

### 输出

```
1```

## 样例 #2

### 输入

```
5 3
zzyyx```

### 输出

```
16```

## 样例 #3

### 输入

```
10 5
abcwxyzyxw```

### 输出

```
440640```

# 题解

## 作者：T_TLucas_Yin (赞：6)

$K\le N\le 10$，其实这题暴力就能过。但由于发现身边一些用暴力的人有的出了些问题，所以我认为还是有些技巧的。

首先要认识一个好用的函数：


```cpp
next_permutation(a+1,a+1+n);
```

这个函数像这样调用的作用是把 $a_1$ 到 $a_n$ 区间的元素顺序改为当前顺序的下一个排列，并返回 $1$；如果当前顺序已经是最后一个排列了，则返回 $0$。更改耗时基本可以忽略不计。

该函数对数字和字符数组都能用。我们把一个数组先从小到大排序，再循环调用此函数，就能遍历该数组的所有排列。对于数组中元素的重复，它是能**自动过滤掉重复排列**的。

这样就能轻松实现遍历输入字符串的所有排列了。接下来枚举每一种排列的所有长度为 $K$ 的子区间，判断其中是否有回文串，再按情况计数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum;
char c[1000005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>c[i];
	sort(c+1,c+1+n);
	do{
		bool flag=1;
		for(int i=1;i<=n;i++){
			bool flagg=1;
			for(int j=i,k=i+m-1;j<=k;j++,k--){
				if(c[j]!=c[k]) flagg=0;
			}
			if(flagg){
				flag=0;
				break;
			}
		}
		if(flag) sum++;
	}while(next_permutation(c+1,c+1+n));//这是常见的写法
	cout<<sum;
	return 0;
}
```

---

## 作者：OIerWu_829 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc363_c)

蒟蒻的第一场 ABC 打出了 AC ABC 的好成绩。

看到赛时好多人被 C 卡常了，我来写个题解，尽可能写详细一点吧。

---

先输入，初始化一个 $cnt$ 向量，用来记录字符串 $s$ 中每个小写字母的出现次数。然后创建一个长度 $n$ 的字符串 $t$，用于存储当前正在构建的字符串排列。

我们从 $t$ 的第一个位置开始，用递归函数来生成所有可能的排列，并检查每个排列是否满足条件（不包含长度为 $K$ 的回文子串）。参数 $t$ 是正在构建的字符串，$pos$ 是当前要放置字符的位置。

递归的时候，如果 $pos=n$，表示已经构建了一个完整的字符串排列。此时我们检查这个排列是否包含长度为 $K$ 的回文子串，如果没有则把答案加 $1$。在 $pos\ne n$ 的情况下，我们遍历所有可能的小写字母，如果当前字母在 $s$ 中出现过，则将其放在 $t$ 的 $pos$ 位置，并继续递归构建下一个位置的字符。注意调用递归函数后我们要进行回溯，把 $cnt_i$ 重新加回来，尝试其他可能的排列。

然后输出答案就行了。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int n, k;
string s;
vector<int> cnt;
int ans;

bool Check(string str, int sta, int end)
{
  while (sta < end)
  {
    if (str[sta] != str[end])
      return false;
    sta++;
    end--;
  }
  return true;
}

void dfs(string t, int pos)
{
  if (pos == n)
  {
    bool f = true;
    for (int i = 0; i <= n - k; i++)
    {
      if (Check(t, i, i + k - 1))
      {
        f = false;
        break;
      }
    }
    if (f) ans++;
    return;
  }
  for (int i = 0; i < 26; i++)
  {
    if (cnt[i] > 0)
    {
      cnt[i]--;
      t[pos] = i + 'a';
      dfs(t, pos + 1);
      cnt[i]++;
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> k >> s;
  cnt.resize(26, 0);
  for (char c : s) cnt[c - 'a']++;
  string t(n, ' ');
  dfs(t, 0);
  cout << ans;
  return 0;
}
```

---

## 作者：Lydia1010__ (赞：2)

## 本题思路：
这道题十分诈骗，乍一看上去十分复杂，但细一想这种题为什么没有取模，一看数据范围瞬间就懂了，这就是一道暴力题。我们只需要暴力提出每一个子串，判断合不合法，统计一下答案即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],jl[105],k,ans;
string s;
map<string,int>mp;
void dfs(int p,int n){
	if(p>n){
		int pd=0;
		string t;
		for(int i=1;i<=n;i++) t+=jl[i];
		if(mp[t]) return;
		for(int i=1;i<=n;i++){
			if(i+k-1>n) break;
			int f=1;//t+=jl[i];
			for(int j=1;j<=k/2;j++){
				if(jl[j+i-1]!=jl[i+k-j])f=0;
				if(!f) break;
			}
			pd=max(pd,f);
			if(pd==1) break;
		}
		ans+=(pd==0&&mp[t]==0?1:0);
//		cout<<t<<endl;
		mp[t]=1;
		return;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			a[i]=1;jl[p]=s[i];
			dfs(p+1,n);
			a[i]=0;
		}
	}
}
int main(){
	int n;
	cin>>n>>k;
	cin>>s;
	s=' '+s;
	dfs(1,n);
	cout<<ans;
	return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
纯纯暴力题。

第一步，先 dfs 枚举可以构成的字符串并去重（当然也可以放进 set 自动去重）。第二步，对每个字符串暴力截取所有长度为 $k$ 的子串。第三步，暴力判断是否回文。完事！
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, k, sum;
string a;
set <string> st;
void dfs (int x) {
	if (x >= n) {
		st.insert (a);
		return ;
	}
	for (int i = x; i < n; ++ i)
		swap (a[i], a[x]), dfs (x + 1), swap (a[i], a[x]);
	return ;
}
bool hw (const string& a) {
	string b = a;
	reverse (b.begin (), b.end ());
	return a == b;
}
bool check (const string& a) {
	for (int i = 0; i <= n - k; ++ i)
		if (hw (a.substr (i, k)))
			return 0;
	return 1;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> k >> a;
	dfs (0);
	for (const string& i : st)
		sum += check (i);
	cout << sum;
	I AK IOI
}
```

---

## 作者：buowen123 (赞：1)

### 题目大意

- 定义一个字符串 $t$ 为“可爱的”，当且仅当这个字符串中不含有长度恰为 $k$ 的回文子串。
- 给你一个字符串 $s$，其中 $|s|=n$。
- 将 $s$ 的字符重新排列得到 $t$，问可以得到多少个“可爱的”字符串。
- $n,k \le 10$，两个字符串如果本身完全相同只计算一次。

### 题目解决

这是一道深搜，string 与 map 的练习题。

看到题目，我们可以枚举 $s$ 如何排列，然后 $O(n)$ 求解，判断新字符串是否符合题意。

如何枚举 $s$ 如何排列呢？我们可以先生成 $1$ 到 $n$ 的排列 $b$，使用 dfs 算法求解。

```cpp
void dfs(int x){
	if(x==n+1){
		//现在生成了一个排列b，下面再填
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){ //判断i用没用过
			vis[i]=1; //如果没用过，标记成用过
			b[x]=i; //让排列b的第x位是i
			dfs(x+1); //往下搜索
			vis[i]=0; //标记成没用过，枚举下一个数
		}
	}
}
```

那么当你获得排列 $b$ 时，让 $t$ 的第 $i$ 位是 $s$ 的第 $b_i$ 位，这就达到了重排的效果。

但是，当 $s$ 含有重复字符时，可能会得到两个相同的 $t$。这时我们可以使用一个 map 来维护 $t$ 是否出现过。

这里，我用 `mp.count(t)` 来表示 map 中是否出现过 $t$。

```cpp
string t;
void dfs(int x){
	if(x==n+1){
		t="";
		for(int i=1;i<=n;i++) t+=s[b[i]-1]; t=" "+t;
		if(!mp.count(t)) mp[t]=1,ans+=slv();
		//slv()表示t是不是“可爱的”
		return;
	}
	//以下省略
}
```

那么如何判断字符串 $t$ 是否含有长度为 $k$ 的回文子串呢？

我们可以设置两个变量 $i,j$，其中 $j=i+k-1$，每一次让 $i$ 加一，让 $j$ 减一，并判断 $t_i$ 与 $t_j$ 是否相等，直到 $i \ge j$。

```cpp
int slv(){
	for(int i=1;i+k-1<=n;i++){
		int j=i+k-1,flg=1;
		for(int x=i,y=j;x<y;x++,y--)
			if(t[x]!=t[y]) flg=0;
		if(flg) return 0;
	}
	return 1;
}
```

接下来就可以献上完整代码啦！

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=12;
int n,k,ans; string s,t;
int vis[maxn],b[maxn];
map <string,int> mp;
int slv(){
	for(int i=1;i+k-1<=n;i++){
		int j=i+k-1,flg=1;
		for(int x=i,y=j;x<y;x++,y--)
			if(t[x]!=t[y]) flg=0;
		if(flg) return 0;
	}
	return 1;
}
void dfs(int x){
	if(x==n+1){
		t="";
		for(int i=1;i<=n;i++) t+=s[b[i]-1]; t=" "+t;
		if(!mp.count(t)) mp[t]=1,ans+=slv();
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=1;
			b[x]=i;
			dfs(x+1);
			vis[i]=0;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k; cin>>s;
	dfs(1);
	cout<<ans<<'\n';
	return 0; 
}
```

---

## 作者：封禁用户 (赞：1)

赛时花了半个小时做这题，菜死了/kk

因为数据范围很小，考虑 dfs。

我们可以先记录每一个字符出现的次数（方便统计），然后 dfs。搜索的最后一步使用双指针判断是否存在长度为 $k$ 的回文子串，没有则答案加一。

[code](https://atcoder.jp/contests/abc363/submissions/55798843)

---

## 作者：AK_400 (赞：1)

发现 $n\le 10$，于是我们可以写一个 $O(n^2 n!)$ 的做法。

直接枚举每一个排列，可以直接用 `next_permutation` 来做。

然后枚举左端点，判断子段 $[l,l+k-1]$ 是否回文即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
char s[100];
bool check(int l,int r){
    for(int i=0;i<=r-l;i++){
        if(s[i+l]!=s[r-i])return 0;
    }
    return 1;
}
bool check(){
    for(int i=1;i+k-1<=n;i++){
        if(check(i,i+k-1))return 0;
    }
    return 1;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    sort(s+1,s+1+n);
    int ans=0;
    do{
        ans+=check();
    }
    while(next_permutation(s+1,s+1+n));
    cout<<ans;
    return 0;
}
```

---

## 作者：Moya_Rao (赞：1)

# 题目大意
把字符串 $S$ 进行全排列，回答有多少个全排列后的字符串不包含有长度为 $K$ 的回文串作为子串。

# 思路
全排列？那当然是 DFS！  
嗯对，的确是 DFS。

那么问题来了，如果已经搜到了一个字符串，该如何判断它是否含有长度为 $K$ 的回文串作为子串呢？

我们可以编一个 `check` 函数来判断。我们先找到每一个左端点，如果以这个点为左端点时那个长度为 $K$ 的子串是回文串，那么这个字符串就不行。如果全部遍历下来，没有一个长度为 $K$ 的子串是回文串，则 $ans$ 加 $1$。

判断一个字符串 $str$ 是否为回文串，我也编了一个 `is` 函数来执行。定义 $i$ 正向扫，$j$ 反向扫，如果每一个 $str_i$ 都等于 $str_j$，那么这个字符串 $str$ 就是回文串，否则就不是。

挺好！  
现在我们看看时间复杂度：$O( n! \times n^2)$，算一算，大概是 $O( 362880000 )$，有 $2$ 秒的时限嘞，没问题！  
提交吧！[AC](https://atcoder.jp/contests/abc363/submissions/55793602) 咯！

# 代码
下面放上赛时的 AC 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,h[26];
string s,t;
bool is(string st){
    for(int i=0,j=st.size()-1;i<st.size()&&j>=0;i++,j--)
        if(st[i]!=st[j])return 0;
    return 1;
}
bool check(string str){
    for(int i=0;i<=n-k;i++)
        if(is(str.substr(i,k)))return 0;
    return 1;
}
void DFS(int len){
    if(len>=n){
        if(check(t))ans++;
        return;
    }
    for(int i=0;i<26;i++){
        if(h[i]!=0){
            t+=(char)(i+'a');
            h[i]--;
            DFS(len+1);
            t.erase(len,1);
            h[i]++;
        }
    }
}
int main(){
    cin>>n>>k>>s;
    for(int i=0;i<s.size();i++)h[s[i]-'a']++;
    DFS(0);
    cout<<ans;
    return 0;
}
```
觉得写的还可以就留个赞再走，好吗？

---

## 作者：__little__Cabbage__ (赞：1)

## Description

简要题意：给定一个字符串 $s$，你可以任意对其进行重排，求在所有 $n!$ 个排列中满足不包含长度为 $k$ 的回文子串的个数。

## Solution

因为数据范围只有 $n \le 10$，所以我们可以直接暴力枚举全排列（用 STL 里的 `next_permutation`），每次再对于 $1 \sim n-k+1$ 中的每一个位置作为长度为 $k$ 的回文子串的起点，进行一次检查，如果确定为回文子串则跳过当前循环。最后如果没有出现长度为 $k$ 的回文子串，计数器 $+1$。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
//#define int long long
#define pb emplace_back
using namespace std;
int n,k;
string ss;
vector <int> s;
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k>>ss;
	for(int i=0;i<n;++i) s.pb(ss[i]);
	sort(s.begin(),s.end());
	int ans=0;
	bool ok,ok2;
	//ok 表示当前字符串是否不包含长度为k的子串
	//ok2 为当前长度为k的子串是否回文
	do
	{
		ok=1;
		for(int i=0;i<=n-k;++i)
		{
			ok2=1;
			for(int j=0;j<k;++j)
			{
				if(s[i+j]!=s[i+k-j-1])
				{
					ok2=0;
					break;
				}
			}
			if(ok2)
			{
				ok=0;
				break;
			}
		}
		if(ok) ++ans;
	}while(next_permutation(s.begin(),s.end()));
	cout<<ans;
	return 0;
}
```

---

## 作者：COKENOTFOUND (赞：1)

# AT_abc363_C  Avoid K Palindrome 2 题解

这道题需要使用一种名为 next_permutation 的函数，功能是求出该序列的下一种字典序排列。所以我们只需要先把给定的序列升序排序，然后在用 next_permutation 枚举每一种排列，判断是否有回文子串即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MX=1e6+10;
const int mod=1e9+7;
const int INF=0x3f3f3f;
int n,k;string s;
vector<int> v;
int ans=0;bool fa,fb;
int main(){
	cin >> n >> k;
	cin >> s;
	for(int i=0;i<n;i++){
		int num=s[i]-'a';
		v.push_back(num);
	}
	sort(v.begin(),v.end());
	while(1){
		fa=1;
		for(int i=0;i<=n-k;i++){
			fb=1;
			for(int j=0;j<k;j++){
				if(v[i+j]!=v[i+k-1-j]){
					fb=0;
				}
			}
			if(fb){
				fa=0;
			}
		}
		if(fa){
			ans++;
		}
		if(!next_permutation(v.begin(),v.end())){
        		//next_permutation在降序排序时返回0
			break;//所有排列都算完了
			//如果没有就自动切换为下一组排列
		}
	}
	cout << ans << "\n";
	return 0;
}
//十年OI一场空，不开郎朗见祖宗
//数据不清空，爆零两行泪
```

---

## 作者：zhouzihang1 (赞：1)

# AT_abc363_c [ABC363C](https://www.luogu.com.cn/problem/AT_abc363_c) Avoid K Palindrome 2 题解

前置知识：全排列。

## 思路

显然这是一个全排列问题。

像这种给定集合求它的全排列，我们可以使用 `next_permutation` 来解决。

对于连续空间而言，我们可以使用 `next_permutation(begin,end)` 来求出这一段空间字典序的下一个。

对于判断回文，暴力枚举即可。

---

## 作者：hard_learn (赞：0)

# 简要题意
题目要求计算给定字符串 $S$ 的所有排列中，不包含任何长度为 $K$ 的回文子串的排列个数。

# 思路
生成字符串排列，检查是否无长度为 $K$ 的回文子串，统计符合条件排列数量。

# 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
string s;
bool ff(const string& s){
    int l=0,r=s.size()-1;
    while(l<r){
        if(s[l]!=s[r]){
            return 0;
        }
        l++;
        r--;
    }
    return 1;
}
int st(int n,int k,string s){
    set<string>aa;
    sort(s.begin(),s.end());
    do{
        bool flag=1;
        for(int i=0;i<=n-k;i++){
            string tt=s.substr(i,k);
            if(ff(tt)==1){
                flag=0;
                break;
            }
        }
        if(flag==1){
            aa.insert(s);
        }
    }while(next_permutation(s.begin(),s.end()));
    return aa.size();
}
signed main(){
    cin>>n>>k;
    cin>>s;
    cout<<st(n,k,s)<<endl;
    return 0;
}

```

---

## 作者：Breath_of_the_Wild (赞：0)

题意：输入一个字符串 $S$，你需要用这个字符串里的所有元素进行重新排列，如果这个字符串不包含长度为 $K$ 的子串，算作一个可行的答案。

思路：首先注意到 $N,K\le 10$，而且这是道 C 题，因此我们可以暴力解决，即生成一个全排列，重排 $S$ 的所有字符。

于是，如果枚举到终点了，就可以按照题目所说的进行判断回文。

但是注意：可能有的字符串有多个相同的字符，导致排列出来多个相同的字符串。而观察样例可以得到题目不允许这样的字符串，因此可以用 map 来维护，如果以前出现过了就直接返回。

其实每回的 C 题都是一样的套路，不同的判断罢了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,vis[14],ans[14],anss,cnt;
string s;
map<string,bool> mp;
void DFS(int x){
	if(x==n){
		bool allf=0;
		string sss="";
		for(int i=0;i<s.size();i++) sss+=s[ans[i]];
		if(mp[sss]) return;
		mp[sss]=1;
		cnt++;
		for(int i=0;i<s.size()-k+1;i++){
			int l=i,r=i+k-1;bool f=0;
			while(l<=r&&sss[l]==sss[r]){
				if(l==r||l+1==r){
					f=1;
					break;
				}
				l++,r--;
			}
			if(f){
				allf=1;
				break;
			}
		}
		if(allf) anss++;
		return ;
	}
	for(int i=0;i<s.size();i++){
		if(!vis[i]){
			vis[i]=1;
			ans[x]=i;
			DFS(x+1);
			vis[i]=0;
			ans[x]=0;
		}
	}
}
int main(){
  ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>k>>s;
	DFS(0);
	cout<<cnt-anss;
	return 0;
}

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑枚举当前字符串摆放的全排列。

然后使用字符串哈希算法怕判重。

每次按照题意判断一下是否有长度为 $k$ 的回文串即可。

时间复杂度为 $O(N!N^2)$，注意因为重复的全排列很多，远远没有达到这个上限。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=15;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,k,ans,l1,l2;
ll p[N];
map<ll,bool> f;
char s[N],t[N];
bool End;
int main(){
	n=read(),k=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	  p[i]=i;
	while(1){
		ull h=0;
		bool F=1;
		for(int i=1;i<=n;i++){
			t[i]=s[p[i]];
			h=(h*137ull+t[i]);
		}
		if(!f[h]){
			for(int i=1;i<=n-k+1;i++){
				string a,b;
				for(int j=i;j<=i+k-1;j++)
				  a+=t[j];
				b=a;
				reverse(b.begin(),b.end());
				if(a==b){
					F=0;
					break;
				}
			}
			ans+=F;
			f[h]=1;
		}
		if(!next_permutation(p+1,p+n+1))
		  break;
	}
	write(ans);
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：a1111a (赞：0)

# 思路
用 DFS 列举出每一种排列方式，注意不能重复。再判断每种排列方式有没有长度为 $K$ 的回文子串，如果没有，则答案加 $1$。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans;
string s;
bool v[12];
bool f(string x){//判断是否回文
	for(int i=0;i<x.length();i++)
		if(x[i]!=x[x.length()-1-i])
			return 0;
	return 1;
}
void dfs(int x,string ss){
	if(x>=n){
		bool kg=0;
		for(int i=0;i<n-k+1;i++){//判断是否有回文子串
			string xx;
			for(int j=i;j<=i+k-1;j++)
				xx+=ss[j];
			if(f(xx)){
				kg=1;
				break;
			}
		}
		if(!kg)
			ans++;
		return;
	}
	string sss;
	for(int i=0;i<n;i++){
		bool kg=0;
		for(int j=0;j<sss.length();j++)
			if(s[i]==sss[j]){//防止重复
				kg=1;
				break;
			}
		if(!v[i]&&!kg){
			sss+=s[i];//记录用过的字符
			v[i]=1;
			dfs(x+1,ss+s[i]);
			v[i]=0;
		}
	}
}
int main(){
	cin>>n>>k>>s;
	dfs(0,"");
	cout<<ans;
	return 0;
}
```

---

## 作者：qhr2023 (赞：0)

## 题意

求将给定的字符串 $s$ 的字符置换后得到的字符串中，不含有长度为 $k$ 的回文子串的字符串的个数。

## 思路

数据范围太小了，直接暴力。每次生成全排列，枚举每个长度为 $k$ 的子串，判断是否回文。

## 实现

这里为方便输入字符串时从 $1$ 计数，为方便全排列，先排序，详情见代码。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, cnt;
char s[15];
int main () {
	cin >> n >> k;
	for (int i=1; i<=n; i++)
		cin >> s[i];
	sort(s+1, s+n+1);
	do {
		bool ok=1;
		for (int i=1; i<=n-k+1; i++) {
			int len=i+k-1;
			bool f=1;
			for (int l=i, r=len; l<=len&&r>=0; l++, r--)
				if (s[l]!=s[r]) {
					f=0;
					break;
				}
			if (f) {
				ok=0;
				break;
			}
		}
		cnt+=ok; 
	} while (next_permutation(s+1, s+n+1));
	cout << cnt;
	return 0;
}
```

---

## 作者：yinyuxuan (赞：0)

## ABC 363 C
### [题目](https://atcoder.jp/contests/abc363/tasks/abc363_c)
### 大意
标题：避免长度为 $K$ 的回文串

给定一个长度为 $N$ 的字符串 $S$，将 $S$ 进行全排列，这些字符串中（不重复），不包含（子串）长度为 $K$ 的回文串的字符串有多少个？（子串必须连续）

数据很小，$2 \le K \le N \le 10$
### 思路
首先将字符串 $S$ 进行全排列（全排列函数 `next_permutation()`）

将每一个全排列字符串从 $1$ 到 $ N - K + 1$ 遍历一遍，判断以此为开头的长度为 $K$ 的字符串是否是回文串

判断回文串可以从两头开始到中间比较是否相同，如果都相同则是回文串：
```cpp
bool p(string s, int l, int r)
{
	while (l < r)
	{
		if (s[l] != s[r]) return false;//不是回文串的情况
		l++; r--;
	}
	return true;
}
```
然后如果发现这个全排列字符串包含长度为 $K$ 的回文串，不满足题目要求，则返回 false：
```cpp
bool str(int n, int k, string s)
{
	for (int i = 0; i <= n - k; i++)
	{
		int r = i + k - 1;
		if (p(s, i, r) == true) return false;
	}
	return true;
}
```
统计返回 true （也就是符合题目要求）的字符串有多少个，最后输出数量即可。

### 时间复杂度
全排列 $O(N!)$，最多 $10!=3628800$

然后第二步判断回文串是 $O((N - K + 1) \times (K / 2))$

把它们再相乘就是最终的时间复杂度，可以把 $K = 2$ 到 $10$ 带入算一下，是不会超过 2s 时限的。

---

## 作者：zjj2024 (赞：0)

### 思路

数据范围很小，考虑搜索。

将每一个字符对应成数字，每个数字统计其个数。

每一次从个数不为 $0$ 的数中选一个，再判断是否回文。若回文，直接判定为不可行。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b[26],a[15],ans,r;//用b数组统计每个字母对应数字出现的个数
string s;
bool cmp(int x,int y)
{
	return x>y;
}
void dfs(int k)
{
	if(k>n)
	{
		ans++;//答案不会超过10!，用int即可
		return;
	}
	for(int i=0;i<r;i++)
	{
		if(!b[i])continue;
		if(k>=m)//如果可能出现回文即判断是否会出现回文，进行剪枝
		{
			if(a[k-m+1]==i)
			{
				bool flag=1;
				for(int j=1;j<m-1;j++)//用暴力方法判断是否回文
				{
					if(a[k-m+1+j]!=a[k-j])
					{
						flag=0;
						break;
					}
				}
				if(flag)continue;
			}
		}
		b[i]--;
		a[k]=i;
		dfs(k+1);//递归调用
		b[i]++;//回溯
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>s;
	for(int i=0;i<n;i++)
	{
		b[s[i]-'a']++;
	}
	sort(b,b+26,cmp);//由于n只有10，所以每次最多只有10种选法，可以进行剪枝
	for(int i=0;i<26;i++)
	{
		if(!b[i])
		{
			r=i;
			break;
		}
	}
	dfs(1);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：pengzy (赞：0)

### 思路：

看到数据范围是很小的，可以直接枚举全排列，使用函数 `next_permutation`。然后再写一个判定函数，枚举生成的字符串中每一个长度为 $k$ 的字串，看看是不是回文。注意要先按字典序排序。

怎么看是不是回文串？反转，看看是否和原串相同。若相同，就是回文串的。

但这个写法是比较慢的，也可以用类似双指针来写。

```cpp
bool judge(string s)
{
	string t(s.rbegin(),s.rend());
	return (t==s);
}
int main()
{
	cin>>n>>k>>s;
	sort(s.begin(),s.end());
	do{
		bool f=0;
		for(int i=0;i<n-k+1;i++) {
			if(judge(s.substr(i,k))) {
				f=1;
				break;
			}
		}
		if(!f)ans++;
	}while(next_permutation(s.begin(),s.end()));
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
先将输入的字符串 $S$ 进行排序，然后对 $S$ 进行全排列。暴力枚举 $S$ 的长度为 $K$ 的所有子串，如果这些字串都不是回文串，那么答案 $+1$。

最后输出答案。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#define N 15
int n,k;
signed main(){
	std::string s;
	std::cin>>n>>k>>s;
	int cnt=0;	
	std::sort(s.begin(),s.end());
	do{
		for(int i=0;i<n;i++){
			for(int j=i;j<n;j++){
				if(j-i+1==k){
					int left=i;
					int right=j;
					bool flag=false;
					while(left<=right){
						if(s[left]!=s[right]){
							flag=1;
							break;
						}
						left++;
						right--;
					}
					if(flag==0)goto oi;
				}
			}
		}
		cnt++;
		oi:;
	}
	while(std::next_permutation(s.begin(),s.end())); 
	std::cout<<cnt;
}
```

---

## 作者：_O_v_O_ (赞：0)

我们注意到 $n\le 10$，所以考虑直接 $O(n!)$ 枚举全排列，然后再 $O(n)$ 检查一下，注意要用 `std::map` 去重，复杂度 $O(n!n)$。

可是我们发现上面那份代码会被卡！~~这就是这个蒟蒻场上吃了 $10$ 发罚时的原因。~~

我们注意到，虽然枚举是 $O(n!)$ 的，可是最多出现的字符串个数却没有那么多，所以我们可以用一个 `std::set` 来存储所有被枚举到的字符串，再在最后来，实测常数比一开始小多了。

这是第一个方法中用时最小的一个：[link](https://atcoder.jp/contests/abc363/submissions/55802063)。

这是第二个方法：[link](https://atcoder.jp/contests/abc363/submissions/55807251)。

---

## 作者：zhangxiaohan007 (赞：0)

[原题传送门](https://atcoder.jp/contests/abc363/tasks/abc363_c)

这道题其实并没有那么复杂，实际上还是
一个大家肯定都知道的算法——暴力枚举。这道题 $n$ 的数据量很小，就算枚举出所有情况，$n!$ 的复杂度也不会爆。再加上枚举中间长度为 $k$ 的字符串，总的时间复杂度应该是 $O(n!\times n)$ 的，足以通过此题。

那该怎么枚举呢？当然是枚举出所有的字符串，然后判断符不符合条件就行了。这里就要用到一个神奇的函数——```next_permutation```。具体用法可以参考我在网上找的[博客](https://blog.csdn.net/weixin_52115456/article/details/127626074)。这个函数可以来帮助我们枚举字符串，剩下我们只需判断每个枚举出来的字符串是否符合要求就行了。

下面给大家贴出代码参考：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define inf 2e9
#define all(x) x.begin(),x.end()
using namespace std;
int n,k,c[30],ans,nn;
string s;
bool huiwen(int l,int r)
{
	int len=r-l+1;
	for(int i=1;i<=len/2;i++)
	{
		if(s[l+i-1]!=s[r-i+1])return false;
	}
	return true;
}
int main()
{
	cin>>n>>k>>s;
	nn=1;
	for(int i=1;i<=n;i++)nn*=i;
	sort(all(s));
	bool tf=false;
	for(int l=0;l<n-k+1;l++)
	{
		if(huiwen(l,l+k-1))
		{
			tf=true;
			break;
		}
	}
	if(!tf) ans++;
	while(next_permutation(all(s)))
	{
		bool tf=false;
		for(int l=0;l<n-k+1;l++)
		{
			if(huiwen(l,l+k-1))
			{
				tf=true;
				break;
			}
		}
		if(!tf) ans++;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：wly09 (赞：0)

这题能开题解是我没想到的。

## 题意简述

给定一个字符串 $S$，求 $S$ 的所有**不同**排列中，不含长为 $K$ 的回文子串的个数。

## 思路

看一眼 $N\le 10$，那就暴力枚举。

若枚举 $S$ 的排列，还要写哈希去重，我们不妨定义一个数组 $T$，$T_c$ 表示 $S$ 中字符 $c$ 的数量，每次选一个非零的取出，这样 DFS 是不重不漏的。

暴力判回文即可。

[记录](https://atcoder.jp/contests/abc363/submissions/55812655)

---

## 作者：Otue (赞：0)

枚举所有全排列，具体可用 `next_permutation`。然后判断是否有长度为 K 的回文串即可。复杂度 $O(n!n^2)$，跑了 1300 ms。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5;

int n, k, p[N], res;
char a[N], b[N];
map<string, int> vis;

signed main() {
	cin >> n >> k >> (a + 1);
	_for(i, 1, n) p[i] = i;
	do {
		_for(i, 1, n) b[i] = a[p[i]];
		string s = "";
		_for(i, 1, n) s += b[i];
		int ff = 0;
		_for(i, 1, n - k + 1) {
			int flg = 0;
			_for(j, i, i + k - 1) {
				if (b[j] != b[2 * i + k - 1 - j]) {
					flg = 1;
					break;
				}
			}
			if (!flg) {
				ff = 1;
				break;
			}
		}
		if (!ff && !vis[s]) res++, vis[s] = 1;
	} while (next_permutation(p + 1, p + n + 1));
	cout << res << endl;
}
```

---

## 作者：Drifty (赞：0)

### Preface

一道挺水的题，不知道为什么赛时一坨人在犇犇里说暴力过不了。

### Solution

注意到 $n \le 10$，而 $10! = 3628800$，感觉起来暴力应该可以过，于是我们考虑暴力判断每个排列是否含有长度为 $k$ 的回文串，并记录个数，最后与总排列数相减即为答案。

时间复杂度 $O(n!nk)$（实际会快一些）。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
    int k, n, ans = 0, tot = 0; string s;
    cin >> n >> k >> s;
    sort (s.begin(), s.end());
    do {
        for (int i=0; i<=n-k; i++) {
            bool f = 1;
            for (int j=1; j<=k; j++) 
                if (s[i+j-1] != s[i+k-j]) {f=0; break;}
            if (f) {ans ++; break;}
        } tot ++;
    }
    while (next_permutation(s.begin(), s.end()));
    cout << tot - ans;
	return 0;
}
```

---

## 作者：_Hzx_ (赞：0)

【**题目大意**】 

给出一个长度为 $n$ 字符串 $s$ 和 $k$。将 $s$ 中的字符任意打乱重新拼成一个字符串，求所有可能的字符串中长度为 $k$ 的回文序列个数之和。 

----

【**解法**】 

直接暴力。

使用 ```next_permutation``` 全排列函数，暴力枚举出每一个打乱后可能的结果，进行判断即可。

写一个 ```check``` 函数，判断当前枚举出来的字符串是否存在一个长度为 $k$ 的回文序列，是的话将 $res$ 加 $1$。

```check``` 怎么写呢？取下前后两个端点的下标 $l$ 和 $r$，每次将 $l$ 加 $1$，$r$ 减 $1$，然后判断下标为 $l$ 和 $r$ 位置上的字符是否相同即可。

最后的 $res$ 即为答案。

----

【**代码**】

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k, res;
string s;

bool check() {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (j - i + 1 == k) {
				int l = i, r = j;
				bool ok = false;
				while (l <= r) {
					if (s[l] != s[r]) {
						ok = true;
						break;
					}
					++l;
					--r;
				}
				if (!ok)
					return false;
			}
		}
	}
	return true;
}

int main(){
	scanf("%d%d", &n, &k);
	cin >> s;
	sort(s.begin(), s.end());
	if (check())
		res = 1;
	while (next_permutation(s.begin(), s.end())) 
		if (check())
			res++;
	printf("%d\n", res); 
}
```

---

## 作者：Hughpig (赞：0)

考虑枚举 $s$ 的所有排列，可以用 `next_permutation(s.begin(),s.end())` 进行枚举，然后检查有无长为 $K$ 的回文串即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

string s;
ll n,k,ans;

bool isp(string t){
	string qwq=t;
	reverse(qwq.begin(),qwq.end());
	return qwq==t;
}

bool check(){
	for(int i=0;i<=n-k;++i){
		auto t=s.substr(i,k);
		if(isp(t))return 0;
	}
	return 1;
}

int main()
{
   	cin>>n>>k;
   	cin>>s;sort(s.begin(),s.end());
    do{
    	ans+=check();
	}while(next_permutation(s.begin(),s.end()));
	cout<<ans;
	return 0;
}
```

---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc363_c)

## 思路：
看到数据范围，很小，是明显的暴搜题，然后再想到了 `next_permutation()` 函数，这样就不用手写全排列了，就可以得出一下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
char s[15];
int n,k,ans=0;
bool vis[15];
bool check(){
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			if(j-i+1==k){
				int l=i,r=j;
				bool ok=0;
				while(l<=r){
					if(s[l]!=s[r]){
						ok=1;
						break;
					}
					l++;
					r--;
				}
				if(!ok){
					return 0;
				}
			}
		}
	}
	return 1;
}
signed main(){
	cin>>n>>k>>s;
	if(check()){
		ans++;
	}
	while(next_permutation(s,s+n)){
		//cout<<s<<endl;
		if(check()){
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```
然后就愉快的过不了样例，检查一下问题 `check` 函数显然没有问题，因为第一个样例过了，那么就是 `next_permutation()` 的问题了，我们知道[这个函数](https://blog.csdn.net/howardemily/article/details/68064377)的判定方式是是否还有下一个的排列，那么最后一个排列显然是字典序降序的，所以初始需要 `sort` 一遍。
## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
char s[15];
int n,k,ans=0;
bool vis[15];
bool check(){
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			if(j-i+1==k){
				int l=i,r=j;
				bool ok=0;
				while(l<=r){
					if(s[l]!=s[r]){
						ok=1;
						break;
					}
					l++;
					r--;
				}
				if(!ok){
					return 0;
				}
			}
		}
	}
	return 1;
}
signed main(){
	cin>>n>>k>>s;
	sort(s,s+n);
	if(check()){
		ans++;
	}
	while(next_permutation(s,s+n)){
		//cout<<s<<endl;
		if(check()){
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：nsty_iridescent (赞：0)

### 题目大意

给定一个长度为 $N$ 且只包含小写英文字母的字符串 $S$。求 $S$ 的全排列中不包含长度为 $K$ 的回文字符子串的个数。

### 思路

这道题的思路个人认为不算太难，我们只需要枚举字符串的全排列，再挨个检查全排列中是否有长度为 $k$ 的回文子串就可以了。

下面来介绍一下这里面我用到的 $\operatorname{next\_permutation}$ 函数。它的主要功能就是求一个字符串中从起始字符 $s$ 开始长度为 $k$ 的子串的**当前排列**的**下一个排列**（可以理解为求全排列）。

### 代码

```cpp
#include<bits/stdc++.h>                         
#define int long long
#define endl '\n'
using namespace std;
int n,k,ans;
string s;
set<string>qpl; //用于存储全排列
bool check(string s){
    int l=0,r=s.length()-1;
    while(l<r){ //左右比对是否回文
        if(s[l]!=s[r])return false;
        l++;
        r--;
    }
    return true;
}
signed main(){
    ios::sync_with_stdio(0);
  	cin.tie(0),cout.tie(0);
    cin>>n>>k>>s;
    sort(s.begin(),s.end());    
    do{ //求全排列
        qpl.insert(s);
    }while(next_permutation(s.begin(),s.end()));
    //因为求的是当前排列的下一个排列，所以要用 do-while 来执行
    for(string now:qpl){
        bool fl=true;
        for(int i=0;i<=n-k;i++){
            if(check(now.substr(i,k))){ //找出长度为 k 的子串
                fl=false;
                break;
            }
        }
        if(fl)ans++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个长度为 $N$ 的字符串 $S$，要求将 $S$（包括它本身）的字符排列组合后得到的字符串（不重复）中，**不包含** 长度为 $K$ 的回文字符串作为子串的字符串的个数。判定条件是，当且仅当存在一个不大于 $(N−K)$ 的非负整数 $i$，对于每个 $1\le j\le K$ 都有 $T_{i+j} = T_{i-j+K+1}$ 时，此时长度为 $N$ 的字符串 $T$ 才包含一个长度为 $K$ 的回文字符串作为子串。

## 解题思路

首先，对于 $S$ 的排列组合，一个 `map` 加上 DFS 就可以枚举出来，接下来，对于新形成的一个字符串 $T$，按照上面给的判定条件用双重循环模拟即可。但是有个坑，如果你的 $T$ 下标从 $0$ 开始，那就要把判定条件中的下标稍微修改一下。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k,bz[11],ans,p,q;
char s[11],t[11];
map<string,int> mp;

void dfs(int x)
{
	if(x==n)
	{
		string tp;
		for(int i=0; i<n; ++i) tp+=t[i];
		
		if(!mp[tp])
		{
			mp[tp]=1; q=1;
			
			for(int i=0; i<=n-k; ++i)
			{
				p=0;
				
				for(int j=1; j<=k; ++j)
				{
					if(t[i+j-1]!=t[i-j+k])
					{p=1; break;}
				}
				
				if(!p) q=0;
			}
			
			ans+=q;
		}
	}
	
	for(int i=0; i<n; ++i)
	{
		if(!bz[i])
		{
			bz[i]=1; t[x]=s[i];
			dfs(x+1); t[x]=0; bz[i]=0;
		}
	}
}

int main()
{
	scanf("%d%d%s",&n,&k,s);
	dfs(0); printf("%d",ans);
    return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

题意：对于一个长度为 $N$ 的字符串 $S$，找出其有多少种排列方式使得任意一个长度为 $K$ 的字串不是回文串。

数据范围小到 $10$，明显是一道暴力~~送分题~~，考虑全排列求解。先对字符串排序，然后用 `next_permutation` 枚举字符串的排列，并判断是否合法，即任意一个长度为 $K$ 的字串都不是回文串，若合法，则计入答案。

该算法比较优秀，时间复杂度 $O(N\log N+N!\times N^{2})$，轻松通过此题。

[代码链接](https://atcoder.jp/contests/abc363/submissions/55809167)

---

## 作者：UnfortunatelyDead (赞：0)

由于题面要求不能存在长为 $k$ 的回文子串，又发现 $n$ 较小，考虑枚举全排列。

然后你可以进行一次马拉车，得到 $p_i$，容易发现若存在 $i$ 使得 $p_i \geq k$，一定存在一个长为 $k$ 的回文子串。

或者也可以直接枚举中心 $i$，判断是否相同，不过这个需要注意 $k$ 的奇偶情况。

[代码](https://atcoder.jp/contests/abc363/submissions/55785078)。

---

## 作者：yegengghost (赞：0)

**已提交翻译。**

## 人话翻译：

给你一个长度为 $N$ 的字符串 $S$，其中只有小写英文字母。

求将 $S$ 的字符（包括字符串 $S$ 本身）置换后得到的字符串中，**不包含**长度为 $K$ 的回文字符串作为子串的字符串个数。

## 解析：

首先笑点兼泪点解析：$2 \leq K \leq N \leq 10$。

**不是，哥们。**

就这么小的范围不暴力做？

我们直接用 ```next_permutation``` 暴力地把每一种结果枚举出来，在照题意判断即可。

```cpp
//看好了我自己，代码之力是这么用的！
//N连10都不到你不暴力还想干嘛~~哎呦 .
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114514;
const int mod=1;
int n,k;
string s;
int ksm(int x,int k)
{
    int ans=1,base=x;
    while(k)
    {
        if(k&1) ans=1ll*ans*base%mod;
        base=1ll*base*base%mod; k>>=1;
    }
    return ans;
}
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
void func()
{
	int ans=0;
	sort(s.begin(),s.end());
	do
	{
		bool flag;
		for(int i=0;i<=n-k;i++)//不包含长度为 K 的回文字符串作为子串的字符串个数。
		{
			flag=1;
			for(int j=1;j<=k;j++)
				if(s[(i+j)-1]!=s[(i+k+1-j)-1])
				{
					flag=0;
					break;//照题意执行即可 
				}
			if(flag)
				break;
		}
		if(!flag)
			ans++;//统计答案 
	}while(next_permutation(s.begin(),s.end()));
	//最暴力的部分 
	cout<<ans<<'\n';
}
signed main()
{
	n=read();
	k=read();
	cin>>s;
	func();
	return 0;
}
```

---

## 作者：cqbzcjh (赞：0)

对于求字符串的全排列，STL 库中有一个函数 **next_permutation**。

1. 它的前两个参数分别是起始位置和终止位置。第三个参数是自定义的比较函数，不写自动按照字典序从小到大。

2. 它可以求出比当前字典序大的下一个排列。

3. 它的返回值是 bool 类型。如果有下一个排列，返回真；否则当前已经是字典序最大的排列，返回假。

所以，我们先按升序排序（字典序最小的排列），再用它求出全排列。由于数据范围很小，对于每一个排列，只需要暴力判断即可。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans=0;
string s;
bool check(string t){
	int len=t.size();
	//判断回文串
	bool flag=true;
	for(int i=0,j=len-1;i<=j;i++,j--){
		if(t[i]!=t[j]){
			flag=false;
			break;
		}
	}
	return flag;
}
int main(){
	cin>>n>>k>>s;
	sort(s.begin(),s.end());
	do{
		bool flag=false;
		//暴力枚举子串
		for(int i=0;i<n-k+1;i++){
			//substr在s中截取从i开始的k个字符
			if(check(s.substr(i,k))){
				flag=true;
				break;
			}
		}
		if(!flag)ans++;
	}while(next_permutation(s.begin(),s.end()));//全排列函数
	cout<<ans;
	return 0;
}
```

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc363_c [ABC363C] Avoid K Palindrome 2

### 题目大意
给你一个长度为 $N$ 的字符串 $S$，求它有多少种排列满足其中没有长度为 $K$ 的回文。

--------------------------------
### 题解
仔细看可以发现一个细节：“$2 \le K \le N \le 10$”，所以我们直接暴力枚举所有排列就可以了。

---
### 代码
```cpp

#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

char t[20];//原数组 
int s[50];//加工为整型数组便于枚举全排的原数组 
int c[50];//加工为双倍数组便于判断回文的原数组 
int n, k;//如题所述 
int num;//答案数 

bool check() {
	memset(c, 0, sizeof c);//字母从1开始，所以可以全赋0 
	for (int i = 1; i <= n; ++i) {//字母之间隔一个空隙，便于处理偶数长度 
		c[i * 2] = s[i];
	}
	for (int i = 2; i <= 2 * n; ++i) {
		if (k % 2 == 0 && c[i] != 0)	continue;//长度为偶数但中心为字母的排除 
		if (k % 2 == 1 && c[i] == 0)	continue;//长度为奇数但中心不为字母的排除 
		int ch = 0;
		for (int j = 1; j < k; ++j) {//判断回文 
			if (c[i - j] != c[i + j])	ch = 1;
		}
		if (ch == 0)	return 0;//有就不行 
	}
	return 1;
}

int main() {
	scanf("%d%d%s", &n, &k, t + 1);
	for (int i = 1; i <= n; ++i) {//加工为整型，便于next_permutation枚举全排 
		s[i] = t[i] - 'a' + 1;//字母下标从1开始，例如a->1，b->2 
	}
	sort(s + 1, s + 1 + n);//排序可将排列从第一个开始（否则字典序比输入小的将被遗漏） 
	do {
		if (check())	num++;
	} while (next_permutation(s + 1, s + 1 + n));
	printf("%d", num);
	return 0;
}

```

---

