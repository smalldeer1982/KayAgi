# Numeric String Template

## 题目描述

Kristina 有一个名为 $a$ 的数组，称为模板，数组包含 $n$ 个整数。她还有 $m$ 个仅包含小写字母的字符串。这些字符串从 1 到 $m$ 编号。她想检查这些字符串是否符合模板。

一个字符串 $s$ 如果满足以下所有条件则被认为符合模板：

- 字符串 $s$ 的长度等于数组 $a$ 的元素个数。
- 数组 $a$ 中相同的数字对应到字符串 $s$ 中的相同字符。因此，如果 $a_i = a_j$，则 $s_i = s_j$（对于 $1 \le i,j \le n$）。
- 字符串 $s$ 中的相同字符对应到数组 $a$ 中的相同数字。因此，如果 $s_i = s_j$，则 $a_i = a_j$（对于 $1 \le i,j \le n$）。

换句话说，字符串中的字符和数组中的数字之间必须有一一对应的关系。例如，如果 $a = [3, 5, 2, 1, 3]$，则字符串 `abfda` 符合模板，而字符串 `afbfa` 不符合，因为字符 `f` 对应了数字 $1$ 和 $5$。

## 样例 #1

### 输入

```
3
5
3 5 2 1 3
2
abfda
afbfa
2
1 2
3
ab
abc
aa
4
5 -3 5 -3
4
aaaa
bcbc
aba
cbcb```

### 输出

```
YES
NO
YES
NO
NO
NO
YES
NO
YES```

# 题解

## 作者：liuzhengtao (赞：1)

## 思路分析
首先判断长度和元素个数是否相等，如果相等，我们分别对 $a$ 和 $s$ 进行映射，按照题意要求两次判断存储的值是否相等。
## code
```cpp
#include <iostream>
#include <cstring>
#include <map>
using namespace std;
const int N = 2e5 + 10;
int a[N] , t , n , m; 
string s;
int main()
{
    cin >> t;
    for(int i=1;i<=t;i++)
	{
		cin >> n;
	    for(int j = 0;j < n;j++) 
	    {
			cin >> a[j];
	    }
	    cin >> m;
	    for(int j=1;j<=m;j++)
		{
	        cin >> s;
	        if(s.length() != n)
			{
	            cout << "NO" <<endl;
	            continue;
	        }
	        map<int , char> c1;
	        map<char , int> c2; 
	        bool flag = true;  
	        for(int j = 0;j < n;j++)
			{
	            int num = a[i];
	            char c = s[i]; 
	            if(c1.count(num) && c1[num] != c)
				{
	                flag = 0;
	                break;
	            }
	            if(c2.count(c) && c2[c] != num)
				{
	                flag = 0;
	                break;
	            } 
	            c1[num] = c,c2[c] = num;
	        }
	        if(flag)
			{
				cout<<"YES"<<endl;
			}
			else 
			{
				cout<<"NO"<<endl;
			}
	    }	
	} 
    return 0;
}
```

---

## 作者：cute_overmind (赞：1)

### 题目大意
[自己去看](https://www.luogu.com.cn/problem/CF2000C)
### 题目分析
我们可以建立两个 `map` 数组分别对整形数组 $a$ 以及字符串 $s$ 进行映射。

接着我们输入完 $m$ 个字符串后我们可以对两个 `map` 中存储的数值进行判断，如果相等就输出 `Yes`，不然输出 `No`。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N] , t , n , m; 
string s;
void solve(){
	cin >> n;
    for(int i = 0;i < n;i++) 
        cin >> a[i];
    cin >> m;
    while(m--){
        cin >> s;
        if(s.length() != n){
            cout << "NO\n";
            continue;
        }
        map<int , char> c;
        map<char , int> cc; 
        bool flag = true;  
        for(int i = 0;i < n;i++){
            int num = a[i];
            char ch = s[i]; 
            if(c.count(num) && c[num] != ch){
                flag = false;
                break;
            }
            if(cc.count(ch) && cc[ch] != num){
                flag = false;
                break;
            } 
            c[num] = ch;
            cc[ch] = num;
        }
        cout << (flag ? "YES" : "NO") << '\n';
    }
}
int main(){
	cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：TPJX (赞：1)

### 分析
可以通过建立数字到字符的映射和字符到数字的映射，来检查字符串是否符合模板。首先检查字符串长度是否与模板长度相等，然后用两个 STL 库中的 map，如果 map 中出现冲突，即不满足一一对应关系，则字符串不匹配模板。
### 代码
```cpp
#include <iostream>
#include <map>
using namespace std;
const int MAXN = 2e5 + 10;
int a[MAXN]; 
int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 0; i < n; i++) 
            cin >> a[i];
        int m; cin >> m;
        while (m--) {
            string s; cin >> s;
            if (s.length() != n) {
                cout << "NO\n";
                continue;
            }
            map<int, char> nc;
            map<char, int> cn; 
            bool ok = true;  
            for (int i = 0; i < n; i++) {
                int num = a[i];
                char ch = s[i]; 
                if (nc.count(num) && nc[num] != ch) {
                    ok = false;
                    break;
                }
                if (cn.count(ch) && cn[ch] != num) {
                    ok = false;
                    break;
                } 
                nc[num] = ch;
                cn[ch] = num;
            }
            cout << (ok ? "YES" : "NO") << endl;
        }
    }
    return 0;
}
```

---

## 作者：SB_ME (赞：0)

~~A了这道题，祝你们成功（滑稽）~~

## 题目描述
  一个序列 $a$，字符串 $s$，求每个字符串是否能够不重复的与 $a$ 中的元素映射。

## 思路
  要解决检查字符串是否匹配模板的问题，我们需要确保字符串中的字符与模板中的数字之间存在一一对应的关系。那么直接用字典啊。对于每个字符串，我们需要创建字符与其对应位置之间的映射。如果整数数组中两个位置具有相同的值，则字符串中对应的字符必须相同。如果字符串中的两个字符相同，则整数数组中对应的位置也必须持有相同的值。
## C++代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string mt(const vector<int>&t,const string&s) {
    if(t.size()!=s.size()) return"NO";
    unordered_map<char,int> c2n;
    unordered_map<int,char> n2c;
    for(size_t i=0;i<s.size();++i) {
        char c=s[i];
        int n=t[i];
        if(c2n.count(c)) {
            if(c2n[c]!=n)return "NO";
        }else c2n[c]=n;
        if(n2c.count(n)) {
            if(n2c[n]!=c)return "NO";
        }else n2c[n]=c;
    }
    return "YES";
}
int main() {
    int tc;
    cin>>tc;
    while(tc--) {
        int n;
        cin>>n;
        vector<int> t(n);
        for(int i=0;i<n;++i)
           cin>>t[i];
        int m;
        cin>>m;
        vector<string> s(m);
        for(int i=0;i<m;++i)cin>>s[i];
        for(const auto& str:s)cout<<mt(t,str)<<'\n';
    }
    return 0;
}

```

---

## 作者：JOE_ZengYuQiao_0928 (赞：0)

### 思路分析
枚举每一个 $i$，统计上一个 $a_i$ 出现的位置与上一个 $s_i$ 出现的位置，看看上一个 $a_i$ 与上一个 $s_i$ 出现的位置是否一致。

- 若一致，那么前 $i$ 位绝对是匹配的，继续枚举 $i$。
- 否则，这两个串一定不匹配，不必继续枚举了。

~~代码就不用我多说了吧！~~

---

## 作者：ghx0052 (赞：0)

## 题意（翻译）
一个字符串 $s$ 被认为是与 $a$ 匹配的，需要同时满足以下所有条件：

- 字符串 $s$ 的长度等于数组 $a$ 中的数字数量。
- $a$ 中的相同数字对应于 $s$ 中的相同字母。因此，如果 $a_i = a_j$，那么 $s_i = s_j (1 \le i, j \le n)$。
- $s$ 中的相同字母对应于 $a$ 中的相同数字。因此，如果 $s_i = s_j$，那么 $a_i = a_j (1 \le i, j \le n)$。

## 思路

对于每个 $s$ 我们只需要扫一遍，每当遇见一个字母，就用 `unordered_map` 查找一下对应在 $a_i$ 中的数，如果有值，则比对是否相等，不相等就直接输出 `NO`；如果没值，就查找当前值是否被其他字母占用，被占则输出 `NO`；

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010], t, n, t1; 
string s;
int main(){
	cin >> t;
    while (t --) {
        cin >> n;
        for (int i = 0; i < n; i ++) cin >> a[i];
        cin >> t1;
        while (t1 --){
            unordered_map<int, char> mp;
            unordered_map<char, int> mp1;
            cin >> s;
            if(s.size() != n){
                cout << "NO\n";
                continue;
            }
            bool flag = 1;  
            for(int i = 0; i < n; i ++) {
                if ((mp.count(a[i]) && mp[a[i]] != s[i]) || (mp1.count(s[i]) && mp1[s[i]] != a[i])){
                    flag = 0;
                    break;
                }
                mp[a[i]] = s[i];
                mp1[s[i]] = a[i];
            }
            cout << (flag ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

# 题意

给定一个序列 $a$，若干字符串 $s_i$，问每个 $s_i$ 是否能够不重复的与 $a$ 中的元素映射。

# 思路

我们可以开一个集合 $b$ 和一个桶 $f$，$b$ 中存 $a$ 中哪些元素有 $s_i$ 中某个字母的映射，$f$ 存 $26$ 个小写字母在 $a$ 中的映射是什么。

对于一个字符串 $s$，如果 $a_i$ 和 $s_i$ 都没有映射，那就把这两个互相映射，如果其中一个有映射了，另外一个没有，那显然是不合法的，如果都有映射了，但是不是相互映射的关系，那也是不合法的，还有，如果 $a$ 的长度和 $s$ 的长度不同，也不合法。

对于集合我使用 `unordered_set` 存（你可以用哈希，但是麻烦），比 `set` 更快。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=415411,INF=0x7fffffff;
int t,n,m,a[N],f[26];
unordered_set<int>b;
string s;
bool check()
{
	if(s.size()!=n)return 0;
	b.clear();
	for(int i=0;i<26;i++)f[i]=INF;
	for(int i=0;i<n;i++)
	{
		if(b.find(a[i])==b.end())
		{
			if(f[s[i]-'a']!=INF&&f[s[i]-'a']!=a[i])return 0;
			b.insert(a[i]);
			f[s[i]-'a']=a[i];
		}else if(f[s[i]-'a']!=a[i])return 0;
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>a[i];
		}
		cin>>m;
		while(m--)
		{
			cin>>s;
			if(check())
			{
				cout<<"YES\n";
			}else
			{
				cout<<"NO\n";
			}
		}
	}
}
```

---

## 作者：Lfz312g (赞：0)

# 题解 CF2000C Numeric String Template
## 题意简述
给定一个序列 $a$ 和若干个字符串 $s$，判断 $a$ 中的数与 $s$ 中的字符是否对应。
## 解法分析
由于 $ -10^9 \le a_i \le 10^9 $，无法开一个桶来存储每一个数对应的字符，所以考虑使用 ```std::map```。对于字符串中的每一个字符 $s_i$，定义一个数组存储其对应的数。    
遍历一遍字符串，如果当前遍历到的字符在 ```map``` 和数组中是否对应，如有不对应的元素，输出 ```NO```，否则输出 ```YES```。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf=1145141919;
int a[200005];
int c[27];
map<int,char> mp;
void solve()
{
	memset(a,0,sizeof(a));
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	int t;
	cin>>t;
	while (t--)
	{
		string s;
		cin>>s;
		bool ok=1;
		for (int i=0;i<27;i++) c[i]=inf;
		if (s.size()!=n) ok=0;
		mp.clear();
		for (int i=0;i<s.size();i++)
		{
			if (ok==0) break;
			if (mp.find(a[i])!=mp.end())
			{
				if (mp[a[i]]!=s[i]) 
				{
					ok=0;
					break;
				}
			}
			else mp[a[i]]=s[i];
			if (c[s[i]-'a']!=inf) 
			{
				if (c[s[i]-'a']!=a[i])
				{
					ok=0;
					break;
				}
			}
			else c[s[i]-'a']=a[i];
		}
		if (ok) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
int main()
{
	int T;
	cin>>T;
	while (T--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：cqbzhzf (赞：0)

[CF链接](https://codeforces.com/problemset/problem/2000/C)
### 前置知识
[map](https://oi-wiki.org/lang/csl/associative-container/#map)
### 思路
一眼模拟题，如果当前字符串与模板的长度不同，肯定不合法。而想要判断字符串的每一位都是否合法很容易想到 $O(n^2)$ 的暴力判断，可是明显会超时，于是采用 map 来打标记，从而优化时间复杂度。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long//保险
using namespace std;
const int N=2e5+5;
int t,n,m,a[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		cin>>m;
		while(m--)
		{
			map<char,int> mp1;
			map<int,char> mp2;//用map储存，否则暴力判断会TLE	
			bool pd=true;
			string s;
			cin>>s;
			int lens=s.length();
			s=' '+s;
			if(lens!=n)
				pd=false;
			for(int i=1;i<=n;i++)
			{
				int x=mp1.count(s[i]),y=mp2.count(a[i]);//mp.count()返回bool类型，如果mp中存在询问值，返回1，否则返回0
				if(x==0&&y==0)//当前s[i],a[i]均未被标记，于是打上标记
				{
					mp2[a[i]]=s[i];
					mp1[s[i]]=a[i];
				}
				else if(x&&y)//当前s[i]和a[i]已被标记，进行其他判断
				{
					if(mp1[s[i]]!=a[i]||mp2[a[i]]!=s[i])//只要有一个不匹配就不合法
					{
						pd=false;
						break;
					}
				}
				else
				{
					pd=false;	
					break;
				}
			}
			if(pd==true)
				cout<<"YES\n";
			else
				cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：roumeideclown (赞：0)

# 题解：CF2000C Numeric String Template

## 题意简述

给出一个数列 $a$ 与一个字符串 $s$，判断 $a$ 中的数与 $s$ 中的字符是否一一对应。（不是很好概括，不清楚可以去读原题意）。

## 解法分析

由题意，可知 $a$ 与 $s$ 长度必须相等（若不相等显然不合题意），因此我们只需判断对于所有 $1 \le i,j \le len$（其中 $len$ 为 $s$ 的长度），是否存在 $a_i = a_j$ 且 $s_i \ne s_j$ 或 $s_i = s_j$ 且 $a_i \ne a_j$。若上面两个命题中有一个成立，则给出的数列与字符串是不“一一对应”的。

不妨先研究是否存在 $a_i = a_j$ 且 $s_i \ne s_j$ 的情况，因为判断 $s_i = s_j$ 且 $a_i \ne a_j$ 与上一种情况是几乎一样的。

由于 $1 \le len \le 2 \times 10^5 $，因此我们不能 $ O(n^2) $ 地来判断，我们可以用一个数组 $num$，其中 $num_{a_i}$ 表示 $a_i$ 对应的 $s_i$。又因为 $ -10^9 \le a_i \le 10^9 $，所以我们要先对数组 $a$ 离散化。

判断 $s_i = s_j$ 且 $a_i \ne a_j$ 时，为了方便处理，我是现把 $s_i$ 全部转换成整数，但这一步似乎没有必要？（我自己也不清楚请大神在评论区指出一下）

具体细节详见代码。

## 代码实现


```cpp
#include<bits/stdc++.h>
//#pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,a[N],tmp[N],c[N],num1[35],num2[35];
string s;
bool check() {
//输入字符串
	cin>>s;
//特判，若 s 与 a 不等长则返回 false
	if(s.length()!=n) return 0;
//对 a 特判，若离散化后存在大于 26 的元素，则不可能一一对应。
	for(int i=1;i<=n;i++) {
		if(a[i]>26) return 0;
	}
//字符转整数
	for(int i=1;i<=n;i++) {
		tmp[i]=c[i]=int(s[i-1]);
	}
//离散化
	sort(tmp+1,tmp+1+n);
	int len=unique(tmp+1,tmp+1+n)-(tmp+1);
	for(int i=1;i<=n;i++) c[i]=lower_bound(tmp+1,tmp+1+len,c[i])-tmp;
	memset(num1,0xff,sizeof(num1));
	memset(num2,0xff,sizeof(num2));
//判断，若当前关系与之前建立的关系不同则返回 false
	for(int i=1;i<=n;i++) {
		if(num1[a[i]]==-1) num1[a[i]]=c[i];
		else if(num1[a[i]]!=c[i]) return 0;
		if(num2[c[i]]==-1) num2[c[i]]=a[i];
		else if(num2[c[i]]!=a[i]) return 0;
	}
	return 1;
}
void solve() {
//输入
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		tmp[i]=a[i];
	}
//对数组 a 离散化
	sort(tmp+1,tmp+1+n);
	int len=unique(tmp+1,tmp+1+n)-(tmp+1);
	for(int i=1;i<=n;i++) a[i]=lower_bound(tmp+1,tmp+1+len,a[i])-tmp;
	scanf("%d",&m);
//进行判断
	for(int i=1;i<=m;i++) {
		if(check()) printf("YES\n");
		else printf("NO\n");
	}
}
int main() {
//多组数据の输入
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：_dbq_ (赞：0)

## 前言
没有读题的同学可以点击[这里](https://www.luogu.com.cn/problem/CF2000C)或[这里](https://codeforces.com/problemset/problem/2000/C)读题。

本题使用知识点：**字符串处理**。

## 思路
读题后可以发现，当一个字符串合法时，注意到每一个相同字符所对应数字一定相同，不同字符所对应的数字一定不同。可以分步完成。

我们对于每一个字符串定义一个对应表 $key$，$key_i$ 为第 $i$ 个小写字母所对应的数字。

遍历一遍字符串，对于第 $i$ 个字符判断 $key_i$。如果没有值，则 $key_i=a_i$；否则如果 $key_i$ 与 $a_i$ 不相等，则证明这个字符同时对应了多个数，输出 `NO`。

遍历完成后我们得到了 $key$，我们要继续判断 $key$ 中是否有值相等。这里我对 $key$ 进行了排序，只要判断相邻两个数是否相等。如有相等，则输出 `NO`，否则输出 `YES`。

## 代码

```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
cint N=2e5+10;
int n;
int a[N];
int key[30];
inline LL read(){
    LL x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void write(LL x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
    return ;
}
void put(LL num){
    write(num);
    putchar('\n');
}
void res()
{
    for(int i=0;i<=29;i++)
        key[i]=INTINF;//建议初始化一下
    return ;
}
bool check()
{
    string s;
    cin>>s;
    if(s.size()!=n) return false;
    for(int i=0;i<s.size();i++)
    {
        if(key[s[i]-'a'+1]==INTINF) key[s[i]-'a'+1]=a[i+1];
        else
        {
            if(key[s[i]-'a'+1]!=a[i+1]) return false;
        }
        //是否有同一个字符占用两个数
    }
    sort(key+1,key+27);
    for(int i=1;i<=26;i++)
    {
        if(i==1) continue;
        if(key[i]==key[i-1]&&key[i]!=INTINF) return false;
        //是否有多个字符使用同一个数
    }
    return true;
}
void solve()
{
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    int T=read();
    while(T--)
    {
        res();
        if(check()) cout<<"YES";
        else cout<<"NO";
        cout<<endl;
    }
}
int main()
{
    #ifdef dbq
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    int T=read();
    while(T--)
    {
        solve();
    }
    return 0;
}
```

---

