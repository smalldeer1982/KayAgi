# Bathroom terminal

## 题目描述

给你  $N$  个字符串，它们代表了单词。每个单词只由字符 `'a'-'e'` 组成，最大长度为  $L$  。另外，有  $M$  个模式串，由字符 `'a'-'e'` 和至多三个的 '?' 组成，最大长度为  $L$  。其中， '?' 可以代表 `'a'-'e'` 中的任何一个字符以及一个空字符 `''` 。对于每一个模式串，输出与之匹配的单词数。

## 样例 #1

### 输入

```
3 1
abc
aec
ac
a?c
```

### 输出

```
3
```

# 题解

## 作者：_Mikasa (赞：9)

### 先看题目大意：
给你 $N$ 个字符串，它们代表了单词。每个单词只由字符 `'a'-'e'` 组成，最大长度为 $L$ 。另外，有 $M$ 个模式串，由字符 `'a'-'e'` 和至多三个的 `'?'` 组成，最大长度为 $L$ 。其中， `'?'` 可以代表 `'a'-'e'` 中的任何一个字符以及一个空字符 `''` 。对于每一个模式串，输出与之匹配的单词数。
 
  这道题校内模拟赛刚拿到的时候想用字典树，但结果一看字母的范围只有 $a$ 到 $e$ 。所以我们可以考虑把模式字符串里的问号一个个枚举成字符 然后，用深搜把转换后的字符串一个个与原本的字符串进行比较，看是否和原本给出的字符串一样，如果一样， 就把总数加上 mp 里存的原字符串的数量。 说白了就是把枚举变换过后的的字符串当作索引，每次 $ans$ 都加上 mp 里这个索引所对应的原本单词出现过的数量。 如果没出现过就加的是零，不影响结果。
  
##   代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans=0,l[1000000];
string s[1000000],x[1000000];
map <string ,int> mp;//用map记下给出的原本字符串的数量
map <string ,int> vis;
void dfs(string x,int k){
	if(k==0){
		if(mp[x]&&!vis[x]){
			vis[x]=1;
			ans+=mp[x];	
		} 
			return;
	}
	for(int i=0;i<x.length();i++){
		if(x[i]=='?'){
			for(int j='a';j<='e'+1;j++){
				if(j=='e'+1){
					x.erase(i,1);//枚举问号是空字符时 就把它删掉
					dfs(x,k-1);//找到了一个问号就把问号--
				}else{
					x[i]=char(j);
					dfs(x,k-1);
				}
			}
		}
		
	}
}
int main(){
//freopen("game.in","r",sdtin);
//freopen("game.out","w",stdout);
    cin>>n>>m;
	long long i,j;
	for(i=1;i<=n;i++){
		cin>>s[i];
		mp[s[i]]++;
	}
	for(i=1;i<=m;i++){
		cin>>x[i];
	}
	for(i=1;i<=m;i++){
		for(j=0;j<x[i].length();j++){
			if(x[i][j]=='?')
				l[i]++;//记下模式串问号的数量
		}
	}
	for(i=1;i<=m;i++){
		ans=0;
		vis.clear();
		dfs(x[i],l[i]);
		cout<<ans<<endl;
	}	
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
```
  

---

## 作者：Imken (赞：7)

~~因为字典树不会写，所以只好写一个搜索水过去。~~

## 题意

求 $N$ 个由字母 `a` 到 `e` 组成的字符串（单词串）与一些包含 `?` 的模式串的匹配个数。每一个 `?` 匹配 `a` 到 `e` 的字母或者空字符。

## 分析

根据题目数据分析，最多有 $3$ 个 `?`，所以对于每一个模式串，与之匹配的单词串最多由 $6^3 = 216$ 个；考虑到 $M$ 最大为 $5000$，暴搜绰绰有余。

所以只需要对每一个模式串进行深搜，枚举所有可能的情况，进行判断即可。

## 解决

考虑使用 `multiset` 维护单词串的集合，`set` 维护搜索到的所有匹配串的集合（其实也可以用 `map`）。

（但是因为我们校内模拟赛打了这道题，时限 $1$ 秒，可以使用效率在大多数情况下更优的 `unordered_set` 来维护所有匹配串的集合）

不过要特别注意，在考场上测试随机数据时发现，对于多次相同且几乎所有单词串都匹配的情况下，可以硬生生把你卡到 $12$ 秒左右。因此，可以使用 `unordered_map` 存储每一次询问，重复时取出。

完整代码如下：
```c++
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#define FILE_OPEN(filename) \
	freopen(filename".in", "r", stdin); \
	freopen(filename".out", "w", stdout);


using std::string;
using std::set;
using std::cin;
using std::multiset;
using std::unordered_set;
using std::unordered_map;

string mode_s;
string target_s;
unordered_set<string> all_status;
multiset<string> target_strs;
unordered_map<string, int> ans_rec;

void dfs(const string &s) noexcept
{
	string b;
	int i, j, cnt = 0;
	int lens = s.length();
	for (i = 0; i < lens; i++) {
		if (s[i] == '?') {
			cnt++;
			// Delete
			b = s;
			b.erase(i, 1);
			dfs(b);
			// Replace
			b = s;
			for (j = 'a'; j <= 'e'; j++) {
				b[i] = j;
				dfs(b);
			}
		}
	}
	// If there is no `?` in the string
	if (!cnt) {
		all_status.insert(s);
	}
}

int n, m;
int i, j;
int ans;

int main() noexcept
{
	// FILE_OPEN("game");
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		cin >> target_s;
		target_strs.insert(target_s);
	}
	for (i = 1; i <= m; i++) {
		all_status.clear();
		ans = 0;
		cin >> mode_s;
		// map 的默认值是 0，这里设成 -1 特殊标记
		if (ans_rec[mode_s] == 0) {
			dfs(mode_s);
			for (unordered_set<string>::iterator it = all_status.begin();
				it != all_status.end(); it++) {
				ans += target_strs.count(*it);
			}
			printf("%d\n", ans);
			ans_rec[mode_s] = ans == 0 ? -1 : ans;
		} else {
			printf("%d\n", ans_rec[mode_s] == -1 ? 0 : ans_rec[mode_s]);
		}
	}
}

```


---

## 作者：xzggzh1 (赞：4)

神仙 SharpnessV 的字典树题解中做法过于复杂了，活活把这个 `1700` 的题恶评到了紫。

---

题意：

求 $n$ 个字符串中能与一个至多带三个 `?` 的字符串匹配的数量。

其中 `?` 可以代表任意一个字符或者空字符，其中字符串中只会出现 $a,b,c,d,e$ 这五个字符。

---

根据计算，三个 `?` 能玩出的花样只有至多 $6^3$ 种，直接枚举出所有可能性和这些字符串的 $\rm hash $ 值，然后匹配一下即可。

其中要注意的是 若有连续两个 `?` 可能会出现重复计算贡献的情况，这里要特判一下去个重。

由于cf可以 $\rm hack$，这里的时间不是卡的很紧，那么直接把字符串用 `std::string` 的形式丢到 `map` 里面就既方便又不用怕 $\rm hash$ 碰撞了。

----

核心代码：

```cpp
map<string,int> mp;
set<string>s;string b;
int work(int si,string res){
	if(si==b.size()){
		if(s.count(res))return 0;
		else{
			s.insert(res);
			return mp[res];
		}
	}
	if(b[si]!='?') return work(si+1,res+b[si]);
	int sum=work(si+1,res);
	for(int i=0;i<5;i++)
	sum+=work(si+1,res+char(i+'a'));
	return sum;
}
int main(){
	int n,m;
	cin>>n>>m;string a;
	for(int i=0;i<n;i++){
		cin>>a;
		mp[a]++;
	}
	for(int i=0;i<m;i++){
		s.clear();
	   cin>>b;
		cout<<work(0,"")<<'\n';
	}
}
```

---

## 作者：vanueber (赞：2)

[原题传送门](https://codeforces.com/problemset/problem/852/G)

## 题目大意

给定 $N$ 个最大长度不超过 $L$ 的字符串与 $M$ 个模式串。模式串中，有若干个 `'?'` 字符，可以代表 `'a~e'` 中任意一个字符与字符 `' '`。对于每一个模式串，要求输出与之匹配的单词数。

## 题目分析

因为每个模式串中 `'?'` 字符的数量不会超过 $3$ 个，所以我们考虑找到串中 `'?'` 的的位置，暴力枚举它们所有可能情况。在枚举的过程中，可以按照它们各自 `'?'` 字符的数量分类讨论，分别枚举它们可能的情况，同时，为降低枚举 `' '` 的困难，不妨将其记作字符 `'f'`，最终利用 `map` 或 `unordered_map` 统计答案时对于字符串再做分离处理，在 2000ms 的时限内可以通过，具体实现见代码部分。

## 代码部分

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> check;
string st;
int n, m, ans = 0;

string get(string str) //对枚举出的一种字符串做‘ ’分离操作
{
    string ret;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != 'f')
            ret += str[i];
    }
    return ret;
}

void work(string ss)
{
    vector<int> pos; //记录?的位置
    for (int i = 0; i < ss.size(); i++)
    {
        if (ss[i] == '?')
            pos.push_back(i);
    }
    map<string, int> vis;
    switch (pos.size()) //分4种情况讨论
    {
    case 0:
    {
        if (check[ss] != 0)
            ans++;
        break;
    }
    case 1:
    {
        string t = ss;
        for (int i = 0; i <= 5; i++) //记'f'为' '，枚举到'f'
        {
            t[pos[0]] = 'a' + i;
            string lst = get(t);
            if (check[lst] != 0 && vis[lst] == 0)
            {
                vis[lst]++;
                ans += check[lst];
            }
        }
        break;
    }
    case 2:
    {
        string t = ss;
        for (int i = 0; i <= 5; i++)
        {
            for (int j = 0; j <= 5; j++)
            {
                t[pos[0]] = 'a' + i;
                t[pos[1]] = 'a' + j;
                string lst = get(t);
                if (check[lst] != 0 && vis[lst] == 0)
                {
                    vis[lst]++;
                    ans += check[lst];
                }
            }
        }
        break;
    }
    case 3:
    {
        string t = ss;
        for (int i = 0; i <= 5; i++)
        {
            for (int j = 0; j <= 5; j++)
            {
                for (int k = 0; k <= 5; k++)
                {
                    t[pos[0]] = 'a' + i;
                    t[pos[1]] = 'a' + j;
                    t[pos[2]] = 'a' + k;
                    string lst = get(t);
                    if (check[lst] != 0 && vis[lst] == 0)
                    {
                        vis[lst]++;
                        ans += check[lst];
                    }
                }
            }
        }
        break;
    }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        cin >> st;
        check[st]++;
    }
    for (int i = 1; i <= m; i++)
    {
        ans = 0;
        cin >> st;
        work(st);
        printf("%d\n", ans);
    }

    return 0;
}
```
希望这篇题解对你有帮助

[AC记录](https://codeforces.com/contest/852/submission/214425148) 

---

## 作者：kczw (赞：1)

# 题意
给定 $N$ 个目标字符串，以及 $M$ 个初始字符串。

在 $M$ 个初始字符串中，有至多 $3$ 个 `'?'` ，每一个'?'都可以用 `'a'-'e'` 中的字母或是空字符替换。问每一个初始字符串可以得到多少个目标字符串。
# 思路
首先，此题有两秒的时间限制，以及 $N\leq10^5$ 和 $M\leq5\times10^3$ 还有对于每个字符串至多 $3$ 个可替换机会加上 $6$ 个选择。暴力搜索极限情况下有 $5\times10^3\times(47+6^3)$ 种可组成字符串。

其次，对于检查每一个可组成字符串是否在 $M$ 个字符串中，直接用 set 就可以了。
# 实现
```cpp
#include<iostream>
#include<map>
#define int long long
using namespace std;
string s;
map<string,int>vis;
map<string,bool>check;
int ans,n,m;
void dfs(int k,string S){
	if(k==s.size()){
		if(check[S]==0){
			check[S]=1;
			ans+=vis[S];
		}return;
	}if(s[k]=='?'){
		dfs(k+1,S);
		for(char i='a';i<='e';i++)
			dfs(k+1,S+i);
	}else dfs(k+1,S+s[k]);
}signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)cin>>s,vis[s]++;	
	for(int i=1;i<=m;i++){
		cin>>s;
		ans=0;
		check.clear();
		dfs(0,"");
		printf("%lld\n",ans);
	}return 0;
}
```

---

## 作者：7KByte (赞：1)

真心的毒瘤题  
光做这道题代码重构了3遍，提交了20+  
我还是太蒻了QAQ  
以上是废话  


------------
这道题一眼所见必为字典树，直接插入n个原始串，再直接匹配询问串即可，然而实现过程中遇到了很多问题


------------
### 第一代  
直接在find的里面修改，遇到问号直接累加  
然而出了问题——只过了一个测试点  
蒟蒻的我百思不得其解，实验多次无望的情况下开始了第一次重构代码


------------
### 第二代  
只有五千次询问，且最多只有3个问号，显然可以暴力枚举出所有可能的串，再注意匹配，复杂度显然是可以AC的，更何况还放了2000ms的时限  
然而还是WA了，经过多次对拍发现神奇的现象：一共有n个字典串，然而有时查询的结果大于n!!!  
**显然统计了重复的串**  
打个比方：  
a??b  
'?'可以表示空，所以枚举后会出现**a' '?b**与**a?' 'b**，而我们在匹配的时候是忽略空字符的，那么以上的两种情况实际上是完全相同的，我们把相同的情况统计了多次  

------
### 第三代  
在第二代枚举的基础上，多开一个字典树，保留相同的串，保证在同一次询问中不会匹配两个完全相同的串，**空间复杂度即维护两个字典树，时间复杂度(nlen+mlen^2)**，复杂度是可行的,并获得了AC

------
### 第四代  
在第一代的基础上，把find函数修改一下，如：
```
void find(char *x,int now,int len,int p){
	int l,r;
	if(x[now]=='?'){
		l=0,r=4;
		if(now+1<=len&&x[now+1]=='?'){
			if(x[now+2]=='?'){
			  if(now+3<=len)
			    find(x,now+3,len,p);
			  else{
			   sum+=f[p].end;
		       return;
			   }
			}
			else if(now+2<=len)
			  find(x,now+2,len,p);
			else{
			sum+=f[p].end;
	        return;
			}
		}
		else if(now+1<=len)
		  find(x,now+1,len,p);
		else {
		sum+=f[p].end;return;
	    }
	}
	else l=r=x[now]-'a';
	for(int i=l;i<=r;i++){
		if(now==len){
			if(f[p].next[i])
			  sum+=f[f[p].next[i]].end;
		}
		else{
			if(f[p].next[i])
			  find(x,now+1,len,f[p].next[i]);
		}
	}
}
```
即我们不提前枚举，而是直接匹配原始串，遇到'?'的时候直接讲指针往后跳，也就是指连续问号这一段只匹配一次，匹配完直接跳过，这样可以保证匹配的唯一性  
如果巨佬觉得难理解的话结合代码画个图试试   

-----
### 后记  
做题不能太莽撞，一定要先做好准备工作，梳理好思路，千万不能像本蒟蒻一样，浪费了多次重构代码的时间以至于被[机房巨佬](https://www.luogu.org/space/show?uid=118273)狂虐  
至于代码还是自己写比较好QwQ  
愿这篇题解对你有些帮助

---

## 作者：_anll_ (赞：0)

模拟赛被这个题暴虐了，偶然发现题解区学长云集，这不得凑个热闹。
## 题目大意
先给你 $N$ 个字符串，每个字符串只由字符 `'a'-'e'` 组成，最大长度为 $L$。

再给你 $M$ 个模式串，由字符 `'a'-'e'` 和至多三个的 `'?'` 组成，最大长度也为 $L$。其中，`'?'` 可以代表 `'a'-'e'` 中的任何一个字符以及一个空字符  `''`。问你对于每一个模式串，与之匹配的单词数有多少。

## 题目思路
模拟赛的时候看到这道题想复杂了，听同学讲解才恍然大悟。

我们在输入时先将这 $N$ 个字符串处理一下，拿 map 存储每个字符串出现过多少次。

因为只有 `'a'~'e'` 五个字母的可能性，而 `'?'` 更是只有三个，所以我们可以通过**深搜枚举**模式串可能变成的所有字符串。

知道了使用深搜，不妨想想如何实现。我们令模式串为 $s$，很容易想到开始深搜时带一个空串 $ss$，以及一个表示当前在第几位的索引 $x$，每次根据 $s_{x+1}$ 往 $ss$ 末尾添加。若 $s_{x+1}$ 不为 `'?'`，就将 $ss$ 的末尾加上 $s_{x+1}$，否则从 `'a'~'e'` 以及 `''` 各尝试一遍。当索引 $x$ 等于$s$ 的长度，就说明枚举已结束，由于会出现重复的变形，这时需要特判一下 $ss$ 是否被枚举过。若未被枚举过，就可将答案加上该字符串出现的次数。

最后漂亮地输出答案就好啦。

## 代码演示
如果对于思路还有不解的话，可以结合下面的代码理解。
```cpp
#include<iostream>
#include<map>
#define int long long
using namespace std;
int n,m,ans;
string s;
map<string,int> mo,vu;
void dfs(int x,string ss){
	if(x==s.size()-1){
		if(!vu[ss]){
			vu[ss]=1,ans+=mo[ss];
		}
		
		return;
	}
	if(s[x+1]=='?'){
		dfs(x+1,ss);
		for(char i='a';i<='e';i++) dfs(x+1,ss+i);
	}
	else dfs(x+1,ss+s[x+1]);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s;
		mo[s]+=1;
	}
	while(m--){
		vu.clear();ans=0;
		cin>>s;
		dfs(-1,"");
		cout<<ans<<endl;
	}
	return 0;
}
```
完结撒花~

---

## 作者：_qingshu_ (赞：0)

~~欸？模拟赛签到题居然没有交完题解，看我来水一发。~~
# 题意分析：

给定 $n$ 个匹配串，$m$ 个模式串，所有串均有字符 $\texttt{a}\sim\texttt{e}$ 组成。求将每个模式串变形后可以与多少个匹配串匹配？

定义合法的变形为将模式串中不超过 3 个的 $\texttt{?}$ 当成空字符或者任意一个字符。

# 思路讲解：

因为每一个模式串最多只有 3 个 $\texttt{?}$ 字符，每一串最多可以变形出 $6^{3}$ 种也就是 216 种不同的串。

既然这么小？么考虑暴力搜索。

首先开一个桶记录每一种串的个数。再利用 string 可以直接用 $+$ 进行叠加操作的优秀特点，我们直接把现在的状态在搜索中用一个 string 表示，如果现在的这个数位为问号，就所有的都试一下就好了。

**注意**一定要判重，搜索结果会出现重复的变形。

# code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string s1,s2;
map<string,int>ton;
map<string,bool>check;
long long ans;
void dfs(int pre,string now){
	if(pre==s2.size()){
		if(check[now]==0){
			check[now]=1;
			ans+=ton[now];
		}
		return;
	}
	if(s2[pre]!='?'){
		dfs(pre+1,now+s2[pre]);
	}
	else{
		dfs(pre+1,now);
		for(char i='a';i<='e';i++){
			dfs(pre+1,now+i);
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s1;
		ton[s1]++;
	}
	for(int i=1;i<=m;i++){
		cin>>s2;
		ans=0;
		check.clear();
		dfs(0,"");
		cout<<ans<<endl;
	}
}
```

update:

修改了公式外使用英文逗号。

修改了字符未使用\texttt。

---

