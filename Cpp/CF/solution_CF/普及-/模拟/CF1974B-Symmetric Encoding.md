# Symmetric Encoding

## 题目描述

Polycarp has a string $ s $ , which consists of lowercase Latin letters. He encodes this string using the following algorithm:

- first, he constructs a new auxiliary string $ r $ , which consists of all distinct letters of the string $ s $ , written in alphabetical order;
- then the encoding happens as follows: each character in the string $ s $ is replaced by its symmetric character from the string $ r $ (the first character of the string $ r $ will be replaced by the last, the second by the second from the end, and so on).

For example, encoding the string $ s $ ="codeforces" happens as follows:

- the string $ r $ is obtained as "cdefors";
- the first character $ s_1 $ ='c' is replaced by 's';
- the second character $ s_2 $ ='o' is replaced by 'e';
- the third character $ s_3 $ ='d' is replaced by 'r';
- ...
- the last character $ s_{10} $ ='s' is replaced by 'c'.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974B/bdd77e5f1b5637622489d2d075a49b021a94a8b9.png) The string $ r $ and replacements for $ s $ ="codeforces".Thus, the result of encoding the string $ s $ ="codeforces" is the string "serofedsoc".

Write a program that performs decoding — that is, restores the original string $ s $ from the encoding result.

## 样例 #1

### 输入

```
5
10
serofedsoc
3
ttf
9
tlrhgmaoi
1
w
15
hnndledmnhlttin```

### 输出

```
codeforces
fft
algorithm
w
meetinthemiddle```

# 题解

## 作者：Dream_Mr_li (赞：2)

## 题面

给定一个编码后的字符串 $s$，要求将其解码成原始字符串 $r$。编码的规则是将字符串 $s$ 中的每个字符替换为它在出现字符组合成的字母表中的对称的字符（对称公式：$n-i+1$）。

## 思路

此题只需模拟即可。

因为字母表中的字符不能重复，所以要将字符串 $s$ 按字母表序排序后去重得到字符串 $b$，之后再把 $b_j$ 的下标 $j$ 记录下来，以便于对称输出，最后输出（$b_{len-j+1}$）就好了。

## 代码

```cpp
#include<bits/stdc++.h>
#define TRACE 1
#define tcout TRACE && cout
#define int long long
#define endl '\n'
const int N=2e5+10;
using namespace std;
char a[N],b[N];
int t,n;
void solve(){
	cin>>n;
	int len_b=0;
	map<char,int>mp,bi;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]++;
	}
	for(auto e:mp){
		b[++len_b]=e.first;
	}
	sort(b+1,b+len_b+1);//这是按字母表排序后的字符串 b
	for(int i=1;i<=len_b;i++){
		bi[b[i]]=i;//记录坐标
	}
	for(int i=1;i<=n;i++){
		cout<<b[len_b-bi[a[i]]+1/*取对称坐标*/];
	}
	cout<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：cute_overmind (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1974B)

### 题目大意
给定一个长度有个 $n$ 字符串 $a$，经过按字典序排序后去重，然后第一个字符替换成最后一个；第二个字符替换成倒数第二个，第三个字符替换成倒数第三个。以此类推。

### 题目分析
考虑模拟。

我们可以先将数组进行排序去重，然后按照题意将字符映射，后即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
char a[N] , b[N];
vector <char> c;
map<char, char> mp;
void solve()
{
	int n;
	cin >> n;
	c.clear();
	mp.clear();
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++) b[i] = a[i];
	sort(a + 1 , a + n + 1);
	for(int i = 1;i <= n;i++)
		if(a[i] != a[i - 1]) c.push_back(a[i]);
	for(int i = 0;i < c.size();i++) mp[c[i]] = c[c.size() - i - 1];
	for(int i = 1;i <= n;i++) cout << mp[b[i]];
	cout << '\n';
}
int main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
} 
```

---

## 作者：Malkin_Moonlight (赞：1)

## 题解：CF1974B Symmetric Encoding

[题目传送门](https://www.luogu.com.cn/problem/CF1974B)

## 思路
首先我们需要把原先的 $s$ 复制到字符串， $r$ 用字典序排序，再去一遍重就可以了。

接着是替换，只需要用 map 保存每个字符为它对称的字符，然后对 $s$ 里的字符一一替换，就可以了。
## 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
#define pb emplace_back
const int MAXN=1e5+5;
const int Mod=1e9+7;
ll T,n,i,j;
string s,r;
map<char,char> mp;
int main()
{
	//freopen("xxx.in","r",stdin);
	//freopen("xxx.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>s;
		r=s;
		ll pos=1;
		sort(r.begin(),r.end());
		for(i=1;i<r.size();i++)
		{
			if(r[i]!=r[i-1])
			{
				r[pos++]=r[i];
			}
		}
		for(i=0;i<pos;i++)
		{
			mp[r[i]]=r[pos-i-1];
		}
		for(i=0;i<s.size();i++) cout<<mp[s[i]];
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：Weekoder (赞：1)

### 思路

基本的字符串模拟题。

解题步骤：

1. 将原字符串按照字典序排序。
2. 将排序后的字符串去重。
3. 映射，存储答案 $ans_{s_i}=s_{|s|-i}$。
4. 按照最开始的字符串顺序输出 $ans$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n;

string s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T --) {
	    cin >> n >> s;
	    string s_ = '#' + s;
	    sort(s.begin(), s.end());
	    string ss = '#' + s;
	    s = "#";
	    for (int i = 1; i <= n; i++)
	    	if (ss[i] != ss[i - 1])
	    		s += ss[i];
	    unordered_map<char, char> ans;
	    for (int i = 1; i <= s.size(); i++)
	    	ans[s[i]] = s[s.size() - i];
	    for (int i = 1; i <= n; i++)
	    	cout << ans[s_[i]];
	    cout << "\n";
	}
	return 0;
}
```

---

## 作者：BDFZ_hym_AK_hym_ing (赞：1)

#### [题目传送门](https://www.luogu.com.cn/problem/CF1974B)
### 题目大意
给你 $t$ 组数据，每组数据输入一个长度 $n$ 和一个字符串 $a$，输出在经历变换后的字符串。
### 题目分析
这题的变换方式实际上是需要先使用一次排序和去重，把字符串变成一个按字典序排序的新数组，在首尾对应调换。举个例子：
```
题目样例5：
15
hnndledmnhlttin
首先先排序（加上去重），再反过来一一对应:
dehilmnt 
||||||||
tnmlihed
最后把原字符串一一对应：
hnndledmnhlttin
|||||||||||||||
meetinthemiddle
好了，解决。
```


### 代码
核心代码：
```cpp
while(t--)
{
	long long n;
	cin>>n;
	string a;
	cin>>a;
	memset(zm,false,sizeof(zm));//memset是个好习惯 
	ans="";dy="";//清空是个好习惯 
	long long i;
	for(i=0;i<n;i++)
	{
		zm[a[i]-'a']=true;
	}
	for(i=0;i<26;i++)
	{
		if(zm[i]==true)
		{
			ans=ans+char(i+'a');
			dy=char(i+'a')+dy;//这是倒置的 
		}
	}
	cout<<ans;
	for(i=0;i<a.size();i++)
	{
		cout<<dy[ans.find(a[i])];//ans.find(a[i])是指在对应表中a[i]的位置，再找到对应的数组中的字符并输出。
	}
	cout<<"\n";
}
```
管理员大大求过！！辛苦啦！！

---

## 作者：Infinite_Loop (赞：0)

# CF1974B
## 题意
定义一种字符串的加密方式（不再展开）。现给定加密后的字符串 $s'$，求原来的字符串 $s$。
## 思路
本题是一道基本的字符串模拟题。

依据字符串的加密方式，可以将 $s'$ 按字典序排序，即为字符串 $r$。因为字符串中可能存在重复的字符，所以有从前往后枚举一遍，求出去重后的结果。因为替换方式为换成对称的另一个字符，那么 $ans _ {i} = s _ {|s| - i}$。最后输出字符串 $ans$ 即可。

需要注意的问题：

- 字符串默认从 $0$ 开始存储，在前面加一个字符会更加方便。
- 输出要换行。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		string S=' '+s;
		sort(s.begin(),s.end());
		s=' '+s;
		string ss=" ";
		for(int i=1;i<=n;i++){
			if(s[i]!=s[i-1]){
				ss+=s[i];
			}
		}
		unordered_map<char,char>mp;
		for(int i=1;i<=ss.size();i++){
			mp[ss[i]]=ss[ss.size()-i];
		}
		for(int i=1;i<=n;i++){
			cout<<mp[S[i]];
		}
		cout<<'\n';
	} 
	return 0;
}
```

---

## 作者：Igallta (赞：0)

- 注：本文字符串下标从 $0$ 开始。

这道题我们的思路大概是这样的：

因为它是根据对称进行加密的，所以密文一定也包含着所有明文包含的字母。

比如是这样的：

明文：`ab`，密文：`ba`。

因为 `ab` 这两个会互相把另一个字母进行记录，也就是 `a` 记录的 `b`，`b` 记录的 `a`，而他们俩又一定会出现。

总结就是明文去重排序后的字符串等于密文去重排序后的字符串。

那有了这个不就好办了吗？

先令 $t=s'$，然后把 $t$ 去重，现在我们就得到了明文去重之后的结果。

那有些人要问了，怎么还原呢？

我们先看题目给出的图片：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974B/bdd77e5f1b5637622489d2d075a49b021a94a8b9.png)

既然它是对称的，那我们再对称回去不就完了吗？

我们用一个桶来记录每一个字母在字符串 $t$ 中在哪一位，减少时间复杂度，方便还原。这个桶就叫 $mp$ 吧。

对称怎么处理呢？

先说结论：假设有一个数组 $a$（下标从 $0$ 开始）那么它的第 $i$ 位对称元素就是：$a_{a.size-1-i}$。

- 为了方便解释，这里假设 $i \leqslant \frac{a.size}{2}$。

为什么呢？先看前两个：$a.size-1$，这是数组 $a$ 最后一位的下标。再看 $-i$，我们看：

其实找出对称元素，就是找一个下标 $j$，让 $|n-j| = |i-0|$（也就是到左或右两个端点距离一致）所以才左移 $i$ 位。

当 $i > \frac{a.size}{2}$ 同理，不做解释。

回到题目，我们知道对称元素下标是怎么计算的了，这个地方的式子还不简单吗？

循环，$s'_i = t_{t.size-mp_{s'_i}-1}$ 即可让 $s'$ 变成 $s$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define LL k<<1
#define RR k<<1|1
using namespace std;
int ToT, n;
string s, t,p;
map<char, int>mp;
signed main() {
	cin >> ToT;
	while (ToT--) {
		cin >> n >> t;
		s = t;
		p="";
		sort(s.begin(), s.end());//排序
     	//至于为什么要排序，是因为我使用的去重方式是比较相邻两个一不一样
		for(int i=0;i<s.size();i++){//去重
			if(s[i]==s[i+1])continue;//重复
			else p+=s[i];//记录
		}
		for (int i = 0; i < p.size(); i++) {
			mp[p[i]] = i;//记录字母在p中排第几位
		}
		for (int i = 0; i < n; i++) {
			t[i] = p[p.size() - mp[t[i]] - 1];//还原
		}
		cout << t << '\n';//输出
	}
	return 0;
}
```

---

## 作者：L_xcy (赞：0)

[Symmetric Encoding](https://codeforces.com/problemset/problem/1974/B)

---

### 题目大意

有一种加密字符串的方法，先按字典序排序，再去重，把这个字符串称作 $r$ ，再把 $r$ 反转，最后把最开始的字符串中的每个字符替换为字符串 $r$ 中的对称字符。

现给出加密后的字符串，让你求原来的。

---

### 解题思路

其实就是把给出的字符串再加密回去。我用 ```map``` 存每个字符所对应的字符，最后输出即可。

时间复杂度 $O(n \log n)$ ，瓶颈在排序。

---

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
void solve() {
	string a,b,c;
	int n;
	map<char,char> ch;
	map<char,bool> bz;
	cin>>n;
	cin>>a;
	c=a;
	sort(a.begin(),a.end());
	for(int i=0;i<n;i++) {
		if(!bz[a[i]]) {
			b+=a[i];
			bz[a[i]]=1;
		}
	}
	for(int i=0;i<b.size();i++) {
		ch[b[i]]=b[b.size()-i-1];
	}
	for(int i=0;i<n;i++) {
		cout<<ch[c[i]];
	}
	cout<<'\n';
}
int main() {
	cin>>T;
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路
看了半天才把题意看懂，我们只需要根据题意走一遍就好了。

首先构造字符串 $r$，我们只需要把原先的 $s$ 复制一个，用字典序排序，再去一遍重就可以了。

再接着就是我们的替换了。只需要用 map 保存每个字符为它对称的字符，然后对 $s$ 里的字符一一替换，我们就成功解决此题了！

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, cnt;
string s;
map<char, char> q;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> s;
		string r = s;
		cnt = 1;
		sort(r.begin(), r.end());
		for (int i = 1; i < (int)r.length(); i++) {
			if (r[i] != r[i - 1]) {
				r[cnt++] = r[i];
			}
		}
		for (int i = 0; i < cnt; i++) {
			q[r[i]] = r[cnt - i - 1];
		}
		for (int i = 0; i < (int)s.length(); i++) cout << q[s[i]];
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：roumeideclown (赞：0)

# 题解：CF1974B Symmetric Encoding

## 题意简述

有一个仅包含小写字母的字符串 $s$ ，可以通过以下方式加密它：

- 首先，创建一个字符串 $r$，按字典序存储 $s$ 中所有不同的字母；

- 然后 $s$ 中的所有字符将被替换为 $r$ 中对应字符的对称的字符（第一个与最后一个对称，第二个与倒数第二个对称，以此类推）。

现给出一个加密后的字符串，请解密。

## 解法分析

观察题意不难发现，解密的过程实则就是重新加密的过程。因此按题意模拟即可。具体思路如下：

按题意创建字符串 $r$，然后将 $r$ 反转存进 $q$ 中，此时 $r$ 和 $q$ 中相同位置的字母是对称的，于是可以用数组存下密文到明文的映射，对应输出。细节见代码。

## 代码实现

```cpp
#include<bits/stdc++.h>
//#pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
string s,r,q;
int n;
bool f[145];
char c[145];
void work() {
  //初始化
	memset(f,0,sizeof(f));
	r=q="";
  //输入
	cin>>n>>s;
  //创建字符串 r
	for(int i=0;i<n;i++) {
		if(!f[s[i]]) {
			f[s[i]]=1;
		}
	}
	for(int i=(int)'a';i<=(int)'z';i++) {
		if(f[i]) {
			r=r+char(i);
		}
	}
  //将 r 反转存入 q 中
	q=r;
	reverse(r.begin(),r.end());
  //建立映射
	for(int i=0;i<q.length();i++) {
		c[int(q[i])]=r[i];
	}
  //输出
	for(int i=0;i<n;i++) {
		cout<<c[int(s[i])];
	}
	cout<<'\n';
}
int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(0),cout.tie(0);
  //多组数据
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++) {
		work();
	}
	return 0;
}

```

---

## 作者：DrAlfred (赞：0)

摘要：模拟

[传送门：https://www.luogu.com.cn/problem/CF1974B](https://www.luogu.com.cn/problem/CF1974B)

## 题意

定义一种对字符串 $s$ 的加密方法。

1. 定义一个辅助字符串 $r$，由字符串 $s$ 内所有不同的字母组成，按照字母顺序排序。
2. 将 $s$ 内的每个字符替换为其在 $r$ 中出现位置对称的字符。

现在已知加密后的字符串 $s'$，求原字符串 $s$。

## 分析思路

注意到该加密方法的一个性质：出现的字符种类不变，即如果对加密后的字符串 $s'$ 构造辅助串 $r'$，有 $r = r'$。

由此，我们注意到，对 $s'$ 再进行一次加密，在 $r'$ 中对称的字符组没有变化。原先交换的字符会被交换回来，所以只要模拟对 $s'$ 进行一次加密即可。

时间复杂度 $O\left(n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
inline void solve(void) {
    string b, r;
    cin >> n >> b;
    vector<int> vis(26, -1);
    for (int i = n - 1; i >= 0; i--) {
        if (vis[b[i] - 'a'] == -1) {
            r += b[i], vis[b[i] - 'a'] = 1;
        }
    }
    sort(r.begin(), r.end());
    for (size_t i = 0; i < r.size(); i++) {
        vis[r[i] - 'a'] = i;
    }
    auto get = [&](char c) {
        return r[r.size() - 1 - vis[c - 'a']];
    };
    for (auto c : b) cout << get(c);
    cout << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：nsty_iridescent (赞：0)

### 题目大意

给定一个由小写拉丁字母组成的字符串 $s$，通过以下编码规则对其进行编码：

* 构建辅助字符串 $r$，包含 $s$ 中所有不同的字母，按字母顺序排列。

* 使用 $r$ 中的对称字符替换 $s$ 中的每个字符，替换规则为：$r$ 中的第一个字符替换 $s$ 中的最后一个字符，$r$ 中的第二个字符替换 $s$ 中的倒数第二个字符，以此类推。

你需要编写一个程序，对给定的编码结果进行解码，即从编码结果中还原出原始字符串 $s$。

### 思路

题目中，我们需要根据给出编码规则逐个还原出原始字符串 $s$。为了做到这一点，我们首先需要构建一个辅助字符串 $r$，其中包含了字符串 $b$ 中出现的所有不同的字母，并按字母顺序排列。然后，我们将根据编码规则对应位置的字符替换为 $r$ 中对应位置的字符即可。

代码中我们将用到几个标准库中的函数，如果不知道用途，可以看我在代码中打出的注释。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
#define endl '\n'
using namespace std;
int t,n;
signed main(){
    cin>>t;
    while(t--){
    	string b;
        cin>>n>>b;
        // 构建辅助字符串r
        vector<char>r;
        for(char ch:b){
        	// find用于在容器中查找特定值的位置，检查当前字符是否已经在r中出现过。
            if(find(r.begin(),r.end(),ch)==r.end()){
                r.push_back(ch);
            }
        }
        sort(r.begin(),r.end());
        // 根据编码规则逐个还原出原始字符串s
        string s;
        for(char ch:b){
        	// distance用于两迭代器间的距离，再次用于计算该位置与辅助字符串的起始位置之间的距离，以便正确地从r中获取替换字符。
            s+=r[r.size()-1-distance(r.begin(),find(r.begin(),r.end(),ch))];
        }
        cout<<s<<endl;
    }
    return 0;
}

```

---

