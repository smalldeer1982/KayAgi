# [ICPC 2022 Xi'an R] Perfect Word

## 题目描述

给定 $n$ 个字符串，你需要找到最长的「完美单词」。

字符串 $t$ 称为「完美单词」，当且仅当它的所有非空子串都出现在给定的字符串中。

字符串 $s$ 称为 $t$ 的子串，当且仅当 $s$ 可由 $t$ 在开头和结尾分别删去零个或若干个字符得到。

$1\leq n\leq 10 ^ 5$，字符串仅由小写字母组成，且总长不超过 $10 ^ 5$。

## 样例 #1

### 输入

```
4
a
t
b
ab
```

### 输出

```
2
```

# 题解

## 作者：Demeanor_Roy (赞：6)

- [原题链接](https://www.luogu.com.cn/problem/P9364)。

------------

先将所有字符串存下来按长度从小到大排序。然后依次考虑。

为什么要这样做？考虑对于一个字符串 $s[1 \dots n]$，它是完美单词当且仅当给定的字符串中存在 $s[1 \dots n-1]$ 与 $s[2 \dots n]$ 且它们都是完美的。（当然，长度为 $1$ 时例外。）于是我们长度从小到大考虑就能**递推地**得出答案。

剩下的问题是如何确认并快速找到那两个字符串。这里我用的是字典树，实际上实现精细可以做到线性。不过没必要，毕竟排序就带了个 $\log$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=1e5+10;
int n,id,ans,tr[N][30],End[N*30];
string t[N];
bool ex[N];
inline void insert(int cur)
{
	int p=0;
	for(int i=0;i<(int)t[cur].size();i++)
	{
		int to=t[cur][i]-'a';
		if(!tr[p][to]) tr[p][to]=++id;
		p=tr[p][to];
	}
	End[p]=cur;
}
inline bool check(int x)
{
	if((int)t[x].size()==1) return true;
	int p=0;
	for(int i=0;i<(int)t[x].size()-1;i++) p=tr[p][t[x][i]-'a'];
	if(!ex[End[p]]) return false;
	p=0;
	for(int i=1;i<(int)t[x].size();i++)	p=tr[p][t[x][i]-'a'];
	if(!ex[End[p]]) return false;
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) cin>>t[i];
	sort(t+1,t+n+1,[](string a,string b){return (int)a.size()<(int)b.size();});
	for(int i=1;i<=n;i++) insert(i);
	for(int i=1;i<=n;i++) if(check(i)) ex[i]=true,ans=max(ans,(int)t[i].size());
	printf("%d",ans);
	return 0;	
} 
```


---

## 作者：Tiger_Rory (赞：4)

本题有两种解法。

第一种是先对字符串按长度从大到小排序，直接枚举每个字符串的所有子串，判断这些子串是否在给定的字符串里。实现时用 `map` 或者其他你喜欢的容器预先存储每个给定的字符串即可，跑得很快。

第二种是写一个字典树，对字符串从小到大排序后，对于长度为 $1$ 的字符串，直接插入；否则对于长度为 $len$ 的字符串，假设下标从 $1$ 开始，则扫 $1 \sim len-1$ 位和 $2\sim len$ 位看在不在树上。如果在树上，就将其插入树，更新答案；否则结束程序。由于这相当于是递推的过程，所以是正确的，但跑得稍慢。

如有不足，还请指出。

---

## 作者：Atserckcn (赞：3)

[洛谷](https://www.luogu.com.cn/problem/P9364)。

模拟赛打挂了。没想到是道绿。

### 思路
首先显然答案就是给定的单词的其中一个。

将所有单词按照长度由小到大排序。

如果遇到某一单词无法确定是否给定，就分别判断删掉第一个字符组成的字符串和删掉最后一个字符组成的字符串。

由于长度由小到大排序，所以判断长度大的字符串时必定已经判断过长度小的。

为什么是正确的？

最有可能被漏掉的就是卡在中间的字符串。

给个例子。字符串 `abcde` 中的 `bc` 什么时候被判断的？

`abcde`$\rightarrow$`abcd`$\rightarrow$`abc`$\rightarrow$`bc`。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,ans;
string s[N];
map<string ,bool> mp;
bool cmp(string a,string b)
{
	return a.size()<b.size();
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>s[i];
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		string t1=s[i];t1.erase(t1.size()-1,1);
		string t2=s[i];t2.erase(0,1);
		if(s[i].size()==1)
			mp[s[i]]=1;
		else
			mp[s[i]]=(mp[t1]&&mp[t2]);
		if(mp[s[i]])
		{
			ans=(int)s[i].size();
//			cout<<"yes: "<<s[i]<<'\n';
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：AnOIer (赞：3)

集训保龄了，特来补一下题解。

因为字符串的子串长度总是小于等于字符串，所以可以先将字符串按照字符串长度升序排序。

对于一个字符串，如果其长度为 $1$，则将字符串在桶中标记为合法并更新一下答案。

否则直接检查这个字符串去掉第一个字符和去掉最后一个字符的子串是否合法，如果满足则进行标记并更新答案。因为检查的这两个子串都是长度小于原字符串的字符串，若这两个字符串合法则原字符串一定合法。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[100010];
map<string,bool> t;
bool cmp(string a,string b) {
	return a.size()<b.size();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);	
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
	    cin>>s[i];
	}
	sort(s+1,s+1+n,cmp);
	int ans=0;
	for(int i=1;i<=n;i++) {
		if(s[i].size()==1) {
			t[s[i]]=1;
			ans=max(ans,1);
			continue;
		}
		if(s[i].size()>1&&t[s[i].substr(1,s[i].size()-1)]&&t[s[i].substr(0,s[i].size()-1)]) {
			t[s[i]]=1;
			ans=max(ans,(int)(s[i].size()));
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：liaojie159357 (赞：2)

# 题目大意
给定 $n$ 个字符串，找到一个所有非空子串都出现在给定的字符串中，并且使得该串的长度最长。
# 分析
看到字符串总长不超过 $10^5$ ，容易想到一个暴力的解法：从最长的串开始找满足条件的。详细点说就是暴力 (反正都是暴力解法了，再暴力点也没关系) 把当前要判断的串拆成它所有的子串依次看是否出现，诶，这不就是裸的 `multiset` 吗？

`multiset` 作为 `STL` 中的一员，可以看成一个序列，插入和删除一个元素都可以在 $O(\log n)$ 的时间复杂度内完成。与 `set` 相比 `multiset` 可以存在多个重复元素。详细用法可以类比 `set`，`count(x)` 函数可以返回 `multiset` 中有多少个 $x$ 元素。

暴力，多说无益：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=1e5+10;
int n;
multiset<string> s;
string c[M];

bool cmp(string x,string y)
{
	return x.size()<y.size();
}//对c按长度排序 

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		s.insert(c[i]);//存入元素 
	}
	
	sort(c+1,c+n+1,cmp);//排序，万能的sort 
	
	for(int tt=n;tt>=1;tt--)//按长度枚举字符串 
	{
		bool sg=false;//开一个标记 
		for(int l=0;l<=c[tt].size();l++)
		{
			if(sg) break;//如果已经不成立就跳过 
			for(int len=0;len<c[tt].size()-l;len++)
			{
				string tp;
				if(sg) break;//如果已经不成立就跳过 
				for(int r=l;r<=l+len;r++)
					tp+=c[tt][r];//枚举所有的子串 
				if(s.count(tp)==0)//如果该子串没有出现过 
				{
					sg=true;//标记，防止对不可能的继续判断浪费时间 
					break;
				}
			}
		}
		//因为是按照字符串的长度从大到小枚举的，所以第一个符合条件的一定是最优的 
		if(sg==false)//所有子串都出现过 
		{
			cout<<c[tt].size();//答案 
			return 0;
		}
	}
	
	return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：1)

一道挺好的字符串题。

### 题意

给你 $n$ 个字符串，找出一个串，使其的所有子串都在给定字符串中出现过，并且这个串的长度最长。

### 分析

观察题目，对于一个符合规定的长度为 $len$ 的完美单词，它有 $\dfrac{len \times (len+1)}{2}$ 个子串，那么在题目要求的数据范围下，在 $2 \times 10^5$ 次内就能判断出来。

因为问题一定有解，所以先把所有串按长度排序，保证最后选出最长完美单词。

标记所有出现过的单词，暴力搜当前串，检查子串是否出现过。如果没有，那么当前串就不符合规定，继续搜下一个，直到找到符合的串为止。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+10;
int n;
string s[maxn];
map <string,bool> mp;
bool cmp(string x,string y){
	return x.size()>y.size();
}
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
bool ifno(string s){
    int len=s.size();
	for(int i=len;i>=1;i--){
		for(int j=1;j+i<=len;j++){
			if(mp[s.substr(j,i)]==0){
				return 0;
			}
		}
	}
	return 1;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		cin >> s[i];
		mp[s[i]]=1; 
        s[i]='*'+s[i];
	}
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(ifno(s[i])){
			cout << s[i].size()-1;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

给定 $n$ 个字符串，当一个字符串的所有子串均出现过时，我们称这个字符串为「完美单词」。

求这些字符串中长度最长的「完美单词」的长度。

### 题目分析

首先来想暴力，枚举每一个字符串，判断其是否为「完美单词」，如果是，更新最长长度。

看似上述算法的时间复杂度是 $\mathcal O(n \times |s_n|^2)$ 的，肯定过不了。

但是我们可以发现，对于一个「完美单词」，他最多需要 $\dfrac{|s|\times(|s| + 1)}{2}$ 个互不相同的子串，也就是说，$10^5$ 个互不相同的字符串最多构成长度大约为 $450$ 的字符串，所以一个字符串如果不是「完美单词」最多只需要判断 $2 \times 10 ^5$ 次就可以判断出来了。

但是最多只有 $26$ 个字母，也就是说会有很多重复的子串，所以肯定跑不满 $\mathcal O(n \times V)$（$V$ 表示判断次数，本题中为 $2 \times 10 ^ 5$），总的时间复杂度最多也就是 $\mathcal O(n \log |s|)$ 的（省略常数）。

再说一些细节：
- 我们可以从长度较长的字符串开始判断，这样第一个「完美单词」一定是最长的。
- 我们可以写一个 $\operatorname{check}$ 函数，每回发现没出现过的子串时，就说明这个字符串一定不是「完美单词」，后面的子串也就没必要判断了。
- 我们可以把所有的字符串丢进一个 $\operatorname{map}$ 里面，这样就可以实现 $\mathcal O(\log n)$ 判断是否出现过了。
- 我们可以使用 $\operatorname{substr}$ 来枚举子串，加上 $\operatorname{map}$ 判断，总的判断效率仍然是 $\mathcal O(\log n)$ 的。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;
int n;
string s[N];
map <string, bool> mp;

bool cmp(string u, string v)
{
	return u.size() > v.size();
}

bool check(string s)
{
	for(int i = s.size() - 2;i >= 1;i--)
		for(int j = 1;j + i <= s.size();j++)
			if(mp[s.substr(j, i)] == false)
				return false;
	return true;
}

signed main()
{
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)
	{
		cin >> s[i];
		mp[s[i]] = true;
		s[i] = "#" + s[i];
	}
	sort(s + 1, s + n + 1, cmp);
	for(int i = 1;i <= n;i++)
	{
		if(check(s[i]))
		{
			printf("%d", s[i].size() - 1);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Infinity_Fantasy (赞：1)

## 思考
经过思考之后发现，完美单词只能是已给出的，那这样的话题目就转化成了求已给单词满足条件的最大长度。
## 构思
既然这样，我们不妨用一个 map 来映射出每个单词是否有出现，然后从大到小排序，用贪心的思想，依次排查，可以暴力判每一个字符串。
### 单次复杂度分析：
在这段代码中，有两个嵌套的循环。外层循环是从 $0$ 到 $s.size()-1$ 的 for 循环，它迭代了字符串 $s$ 的每个字符，因此它的时间复杂度是 $O(n)$。

内层循环也是一个 for 循环，当字符串满足条件时，它迭代了所有可能的子串长度 $len$。对于每个字符 $i$，内层循环的循环次数是从 $1$ 到 $n-i$，因此内层循环的时间复杂度是  $O(n-i)$。

将内层循环的时间复杂度进行累加，得到总的时间复杂度：
 $O(n-1) + O(n-2) + \dots + O(1) = O(n \times (n-1) \div 2) = O(n^2 \div 2 - n \div 2) \approx O(n^2)$

但是如果是不满足条件的字符串即中途退出的情况，最好的复杂度是 $O(1)$，最坏的情况仍是 $O(n^2)$ 的。

综上所述，整体的复杂度应为 $O(n^2)$。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n;
string s[100005];
map<string,bool> mp;
bool check(string s){
	for(int i=0;i<s.size();i++)
		for(int len=1;len+i-1<s.size();len++)
			if(!mp[s.substr(i,len)]) return false;
	return true;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>s[i],mp[s[i]]=1;
    sort(s+1,s+1+n,[](string a,string b){return (int)a.size()>(int)b.size();});
	for(int i=1;i<=n;i++)
		if(check(s[i])){
			cout<<s[i].size();
			break;
		}
	return 0;
}
```
小笔记：

substr 函数的用法：$name.substr(i,len)$ 表示的是从 $name$ 中截取一段字符串其下标从 $i$ 开始往后数 $len$ 个字符。

---

## 作者：小小小朋友 (赞：1)

## 题意

很好理解，找到最长的它的所有非空子串都出现过的字符串。

## 做法

我们发现这个要求实际上相当苛刻，如果一个字符串满足条件，那么它所有字串都应该满足条件，我们考虑按长度从大到小排序，然后直接枚举每个字符串的子串是否出现过。

字符串总长不超过 $10^5$，而一个满足要求的字符串的所有子串都会出现，这样看就只有长度小于大约 $400$ 的字符串能成为答案，在最坏情况下约需要判断 $100000^{\frac{3}{2}}$ 次，但是实际上由于字母数量有限，远远跑不满。

我们再利用字符串哈希或者 map/set 存储所有字符串来判断即可通过此题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[100005];
unordered_map<string,bool> um;
bool cmp(string &a,string &b){
    return a.size()>b.size();
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s[i];
        um[s[i]]=1;
    }
    sort(s,s+n,cmp);//按字符串长度排序
    for(int i=0;i<n;i++){
        bool flag=1;
        for(int p=0;flag&&p<s[i].size();p++){
            for(int k=1;k+p<=s[i].size();k++){
                if(um.find(s[i].substr(p,k))==um.end()){//判断字串是否出现
                    flag=0;break;
                }
            }
        }
        if(flag) {
            cout<<s[i].size();
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：yanxu_cn (赞：0)

提供一种写法比较优美的题解，没有涉及字典树之类的东西，应该实现还是比较方便的。

我们注意到一个单词是完美单词，当且仅当：
+ 它的长度为 $1$；
+ 它在给出的字符串当中；

或者
+ 它的长度不为 $1$；
+ 它在给出的字符串当中；
+ 去掉它的最后一个字符得到的单词是完美的；
+ 去掉它的第一个字符得到的单词是完美的。

所以我们直接将字符串按照其长度从小到大排序，然后开一个 `unordered_set` 来存储其完美性即可。如果不想用 STL 也可以手动实现哈希。

贴一下代码。不到 $700$ 字节。速度瓶颈其实是 I/O 和 `string` 啦。

```cpp
// C++11 needed.
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=1e5+7;
string str[maxn];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	unordered_set<string>ok;
	for(int i=1;i<=n;i++)
	{
		cin>>str[i];
	}
	sort(str+1,str+n+1,[&](const string s1,const string s2)->bool{return s1.length()<s2.length();});
	for(int i=1;i<=n;i++)
	{
		if(str[i].length()==1)
			ok.insert(str[i]);
		else
		{
			string s1=str[i].substr(0,str[i].length()-1),
				   s2=str[i].substr(1,str[i].length()-1);
			if(ok.find(s1)!=ok.end()&&ok.find(s2)!=ok.end())
			ok.insert(str[i]);
		}
	}
	int ans=0;
	for(auto&x:ok)
		ans=max(ans,static_cast<int>(x.length()));
	cout<<ans;
	return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

### 前言

第一眼就觉得像字典树，但是我只能打出 $O(N^2)$ 的字典树做法。

感觉这道题有点诈骗题的感觉，实际上有了结论以后方法很多。

-----

### 解析

#### 性质

我们需要一些性质和结论。

根据题目定义，一个「完美单词」的所有非空子串都在输入的字符串中，而这个字符串本身自然也是它自己的非空子串。也就是说，**「完美单词」一定在输入的字符串中**。

又因为对于一个长度为 $s$ 的字符串，它的非空子串有 $\frac{s(s+1)}{2}$ 个，所以首先一共要有那么多个字符串，即 $n \le \frac{s(s-1)}{2}$。当 $n$ 取最大值 $10^5$ 的时候，$s$ 大约在 $447$ 左右。

那么如此，**长度超过 $447$ 的字符串既不能成为「完美单词」，也不能作为「完美单词」的子串对答案做出贡献，可以直接忽略不计**。

这样一来，我们只需要检验长度在 $447$ 以内的字符串是否合法即可，这个的方法就很多了。

可以把所有字符串丢到一个 `map` 或 `set` 之类的容器里面，然后判断「完美单词」的时候暴力查找所有子串，单次查找时间复杂度带 $\log$，但是这样不够优雅。所以我还是选择字典树（因为第一眼就觉得像字典树）。

#### 算法

在读入字符串的时候将所有（长度合法的）字符串压入字典树中，并在每个串末尾对应节点打一个标记。

**如果从根到某个节点上的路径上所有节点都有标记，那么这条路径对应字符串的所有前缀字符串都曾出现过。** 例如：`abcd` 路径上所有节点都有字符串末尾标记，那么 `a`、`ab`、`abc`、`abcd` 都在输入字符串中。

那么**对于一个字符串的所有子串，只需要对它的所有后缀进行上述验证**即可。举个例子：`abcd` 的所有后缀包括 `abcd`、`bcd`、`cd`、`d`，其中：

+ `abcd` 的所有前缀：`a`、`ab`、`abc`、`abcd`
+ `bcd` 的所有前缀：`b`、`bc`、`bcd`
+ `cd` 的所有前缀：`c`、`cd`
+ `d` 的所有前缀：`d`

这样就包括了它的所有子串。验证「完美单词」的时间复杂度也降至 $O(s^2)$ 而不带 $\log$。

#### 时间复杂度

上面算出的 $447$ 约为 $\sqrt{n}$ 级别。因为字符串总长为 $n$，所以最坏情况是有大约 $\sqrt{n}$ 个长度约为 $\sqrt{n}$ 的字符串。

在这种情况下，算法不得不对这 $\sqrt{n}$ 个字符串都进行一次 $O(s^2)$ 的验证，其中 $s$ 为 $\sqrt{n}$ 量级，所以**最坏时间复杂度为 $\bm{O(n \sqrt{n})}$**，常数很小，在 $n \le 10^5$ 的数据范围下可过。（实际上[跑得飞快](https://www.luogu.com.cn/record/201784125)，每个点平均只要 $10$ ms）

### 代码

```cpp
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N=1e5+5,SN=447;
int n; string s[N];

int trie[N][30],idx;
bool ed[N]; //字符串末尾节点标记
void Insert(const string &str) //字典树插入
{
	int p=0;
	for(int i=0;i<(int)str.length();i++)
	{
		int x=str[i]-'a'+1;
		if(!trie[p][x])
			trie[p][x]=++idx;
		p=trie[p][x];
	}
	ed[p]=true;
	return;
}

bool check(const string &str) //检查是否为「完美单词」
{
	for(int i=0;i<(int)str.length();i++) //枚举后缀的起点
	{
		int p=0;
		for(int j=i;j<(int)str.length();j++) //检查后缀的所有前缀
		{
			int x=str[j]-'a'+1;
			p=trie[p][x];
			if(!ed[p]) return false;
		}
	}
	return true;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i]; //string 用 scanf 不好使
		if(s[i].length()<=SN)
			Insert(s[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(s[i].length()<=SN && check(s[i]))
			ans=max(ans,(int)s[i].length());
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：niuzh (赞：0)

### 思路

此题可以暴力去做。

可以一个 `map` 来映射出每个单词是否有出现，然后长度从大到小排序，依次排查，如果有一个单词是完美单词，因为已经排过序，所以可以直接输出并结束程序。

对于一个单词 $s$，其不同的子串个数最多为 $|s|\times (|s|+1) \div 2$ 个，所以由于 $n \le 10^5$，最长的字符串长度也小于 $447$。验证次数也小于 $10^5$ 次，但只有 $26$ 个字母，所以实际次数会远小于 $10^5$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
string s[N];
map<string,bool> m;
bool check(string s)
{
	for (int i=0; i<s.size(); i++)
	{
		for (int len=1; len+i-1<s.size(); len++)
		{
			if (!m[s.substr(i,len)])
			{
				return false;
			}
		}
	}
	return true;
}
int main()
{
	int n;
	cin>>n;
	for (int i=1; i<=n; i++)
	{
		cin>>s[i];
		m[s[i]]=true;
	}
	sort(s+1,s+1+n,[](string a,string b)
	{
		return (int)a.size()>(int)b.size();
	});
	for (int i=1; i<=n; i++)
	{
		if (check(s[i]))
		{
			cout<<s[i].size();
			break;
		}
	}
	return 0;
}

```

---

## 作者：dingshengyang (赞：0)

这是一个洛谷网校秋令营的菜鸡来写题解。菜鸡现在在补 10 月 1 日的题，这题是 @一扶苏一老师讲的，个人觉得十分的清晰。

丢结论：

令 $f(s)$ 为 $s$ 是否为完美单词（若 $f(s) = 1$ 则 $s$ 一定是输入中的单词，想一想，为什么）。令 $s$ 除去最后一个字符的字符串为 $l$，令除去第一个字符的为 $r$，规定 $|S|$ 表示 $S$ 的长度。

特别的，如果 $s$ 的长度为 $1$，$f(s) = 1$（子串仅有自己）。

否则则有：$f(s) = 1$ 当且仅当 $f(l)=1$ 且 $f(r)=1$。

原因很简单，$s$ 长度为 $|s|$ 的子串只有自己，肯定没问题。长度为 $|s| - 1$ 的只有 $l$ 和 $r$。长度低于 $|s| - 1$ 的都被 $l$ 或 $r$ 当中至少一个包含。所以 $s$ 的所有字串均被考虑。

然后我们只需要判断 $l$ 和 $r$ 是否存在，上字典树即可。最后记得把所有字符串按照长度从小到大排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100005;
int son[N][26];
int idx,word[N*26];
int n;
void insert(string s){
    int p = 0;
    for(int i = 0;i < (int)s.size();i ++){
        int c = s[i] - '0';
        if(!son[p][c])son[p][c] = ++idx;
        p = son[p][c];
    }
    word[p] = 1;
}
int query(string s){
    int p = 0;
    for(int i = 0;i < (int)s.size();i ++){
        int c = s[i] - '0';
        if(!son[p][c])return 0;
        p = son[p][c];
    }
    return word[p];
}
vector<string> vec; 
int main(){
    cin >> n;
    for(int i = 1;i <= n;i ++){
        string str;
        cin >> str;
        vec.push_back(str);
    }
    sort(vec.begin(),vec.end(),[](const string& a,const string& b)
    {return a.size() < b.size();});
    int ans = 0;
    for(auto x: vec){
        if(x.size() == 1){
            insert(x);
            ans = max(ans,1);
            continue;
        }
        if(query(x.substr(0,x.size() - 1)) && query(x.substr(1))){
            ans = max(ans,(int)x.size());
            insert(x);
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：0x282e202e2029 (赞：0)

[题目链接](/problem/P9364)

## 思路

第一眼，居然感觉有些像区间 DP。

区间 DP 求每个子区间的最优解，本题求每个子字符串均存在于词典中。

类比一下方法。

先将所有字符串排序，第一关键字为长度。

接着，逐个取出。若长度为 $1$，一定符合，直接加入词典。若长度不为 $1$，则分别检查去掉末尾字符与开头字符的字符串，若二者皆存在于词典中，则代表其所有子字符串均存在于词典中，满足要求，加入词典。

这里使用 `count()` 计算是否存在，[更多 set 常用函数](https://blog.csdn.net/weixin_52115456/article/details/124210086)。

若不存在长度为 $1$ 的字符串，由于 `ans` 初值为 $0$，最后的输出一定为 $0$。

## AC 代码

```cpp
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#define qwq puts("QWQ");
using namespace std;
int cmp(string a, string b)
{
	return a.size() != b.size() ? a.size() < b.size() : a < b;
} // 比较，第一关键字为长度
int n, ans;
string word;
vector<string> words;
set<string> dict; // 词典，unordered_map<string, bool> 也可
int main()
{
    cin >> n;
    while (n--)
	{
        cin >> word;
        words.push_back(word); // 读入
    }
    sort(words.begin(), words.end(), cmp); // 排序
    for (string w : words)
	{
        if (w.size() == 1) // 若长度为 1
		{
			dict.insert(w), ans = 1; // 直接加入
		}
        else // 否则
		{
            if (dict.count(w.substr(0, w.size() - 1)) && dict.count(w.substr(1))) // 满足要求
			{
                ans = max(ans, int(w.size())); // 更新答案
                dict.insert(w); // 加入
            }
        }
    }
    cout << ans; // 输出即可
    return 0;
}
```

---

