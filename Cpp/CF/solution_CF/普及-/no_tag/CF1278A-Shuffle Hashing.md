# Shuffle Hashing

## 题目描述

Polycrap正在建立他自己的网页服务。作为一个很现代的网站其包含登入的功能。当然，这总会涉及到密码的安全问题。

Polycarp决定要储存密码的哈希值。密码的哈希值由以下这个算法来生成：

1.把只包含小写拉丁字母的密码$p$进行随机打乱，记为$p'$（$p'$可能和$p$相等）；

2.生成两个随机的只包含小写拉丁字母的字符串$s_1$和$s_2$（这两个串中的任何一个可能为空串）；

3.哈希算法的结果$h=s_1+p'+s_2$，此处的$+$是指把前后两个字符串首尾相接。

举个例子，$p=\texttt {abacaba}$，则$p'$可能为$\texttt{aabcaab}$。随机生成两个字符串$s_1=\texttt{zyx}",s_2=\texttt{kjh}$。那么$h=\texttt{zyxaabcaabkjh}$。

需要注意的是，从$p$变换道$p'$的过程中，不会添加或者删除任何字母，只会改变字母的顺序。

现在Polycarp想让你帮他编写密码哈希的校验模块。给出密码$p$和生成的哈希$h$，你需要检查$h$是否是$p$的一个哈希结果。

## 说明/提示

第一组查询的解释已经在题干中给出。

第二组查询中$s_1$和$s_2$均是空串，$p'$是$p$的一种打乱。

第三组查询中哈希不能通过密码生成。

第四组查询中$s_1=\texttt{n}$，$s_2$是空串，$p'=\texttt{one}$是$p$的一种打乱（虽然打乱并没有效果）。

第五组查询中哈希不能通过密码生成。

## 样例 #1

### 输入

```
5
abacaba
zyxaabcaabkjh
onetwothree
threetwoone
one
zzonneyy
one
none
twenty
ten
```

### 输出

```
YES
YES
NO
YES
NO
```

# 题解

## 作者：爱滑稽的蒟蒻 (赞：1)

没人发题解蒟蒻来一发~

题意：

给你一个原字符串s1和一个后字符串s2

判断s2中是否存在连续的一段区间，使这段区间内每个字母的个数与s1完全一致

思路：

	大水题……
    从s2的第一个字母开始搜，如果搜到和s1相同的字母
    就从这个字母开始搜第二次，搜到没有s1中的字母
    再判断长度与s1是否相等就好了
    
注：为了方便，可用map记录字母出现的次数

放代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	while(c<'0'||c>'9') {if(c=='-') f=1;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(f) x=-x;
	return x;
}
inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}
char s1[2000],s2[2000];
int len1,len2;
map<char,int>q,m,s;//记录字母出现的次数 
bool dfs2(int x)
{
	s=q;//暂时储存，判断结束后重新赋值 
	int num=0;
	for(int i=x;i<len2;i++)
	{
		if(q[s2[i]]) q[s2[i]]--,num++;//如果s1中存在，就-- 
		else break;//如果这个字母已经不存在了就不需要搜了 
	}
	if(num==len1) return true;
	else 
	{
		q=s;//重新赋值 
		return false;
	}
}
bool dfs1()
{
	for(int i=0;i<len2;i++)
	{
		if(q[s2[i]]==0) continue;
		else if(dfs2(i)) return true;//找到了就开始搜 
	}
	return false;
}
int main()
{
	int T=read();
	while(T--)
	{
		q=m;
		cin>>s1>>s2;
		len1=strlen(s1);len2=strlen(s2);
		for(int i=0;i<len1;i++)
			q[s1[i]]++;//储存字母个数 
		//cout<<q['a']<<endl;
		if(dfs1()) puts("YES");
		else puts("NO");
	}
}
```


---

## 作者：TemplateClass (赞：0)

此题是一道大水题。

我们截取 $h$ 中一段长度为 $p$ 的字串，逐一比较即可。

因为会打乱，所以要先 `sort` 一下。

最后，如果 $h$ 的长度小于 $p$ 的长度，直接输出 `NO`。

AC 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--){
		string p, h; bool flag=0;
		cin>>p>>h; sort(&p[0], &p[p.size()]);
		if(h.size()<p.size()){ cout<<"NO"<<"\n"; continue; } 
		for(int i=0;i<h.size()-p.size()+1;++i){
			string sub=h.substr(i, p.size());
			sort(&sub[0], &sub[sub.size()]);
			if(sub==p){ flag=1; break; }
		}
		if(flag) cout<<"YES"<<"\n";
		else cout<<"NO"<<"\n";
	}
}
```

---

## 作者：CodingOIer (赞：0)

## CF1278A Shuffle Hashing 题解

### 思路分析

这道题的数据范围十分明显，$t \le 10^2$，同时 $p$ 和 $h$ 的长度小于 $10^2$。

所以此题可以用深搜的方式通过。

首先统计出每个字符出现的次数。

Code：

```cpp
for (int i = 0; i < len_s; i++)
{
    s[p[i] - 'a']++;
}
```

然后枚举起始下标 $i$，$i$ 从 $0$ 到 $len_h - len_p$，这是最大可以容纳下所有字符的位置，再往后肯定无法满足条件，因为长度小于原来的长度，所以肯定无法匹配。

再枚举 $j$，从 $i$ 到 $i + len_p$，统计出这段的所有字符出现次数。

最后从 $0$ 到 $25$ 判断是否完全匹配。

Code:

```cpp
for (int i = 0; i <= len_h - len_p; i++)
{
    memset(k, 0, sizeof(k));
    for (int j = 0; j < len_p; j++)
    {
        k[h[i + j] - 'a']++;
    }
    f = true;
    for (int i = 0; i < 26; i++)
    {
        if (k[i] != s[i])
        {
            f = false;
        }
    }
    if (f)
    {
        printf("YES\n", i);
        return;
    }
}
```

如果遍历了所有的下标，还是没有匹配，则 `printf("NO\n")`。

### 代码实现

```cpp
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define debug printf("Debug\n")
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int MaxN = 1e2 + 5;
int t;
bool f;
int s[35];
int k[35];
char p[MaxN];
char h[MaxN];
int len_p, len_h;
void solve()
{
    memset(s, 0, sizeof(s));
    getchar();
    scanf("%s", &p);
    getchar();
    scanf("%s", &h);
    len_p = strlen(p);
    len_h = strlen(h);
    for (int i = 0; i < len_p; i++)
    {
        s[p[i] - 'a']++;
    }
    for (int i = 0; i <= len_h - len_p; i++)
    {
        memset(k, 0, sizeof(k));
        for (int j = 0; j < len_p; j++)
        {
            k[h[i + j] - 'a']++;
        }
        f = true;
        for (int i = 0; i < 26; i++)
        {
            if (k[i] != s[i])
            {
                f = false;
            }
        }
        if (f)
        {
            printf("YES\n", i);
            return;
        }
    }
    printf("NO\n");
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

注：本代码时间复杂度为 $t \times len_h \times len_p$，最大为 $10^6$。

---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，我们可以把 $h$ 中每个连续的长度与 $p$ 相等的字符串在排序后与排序后的 $p$ 比较。只要有一次相等，就输出 `YES`，否则输出 `NO`。
## 代码
```python
a = int(input())
for b in range(a):
    c,d,i = sorted(list(input())),list(input()),0
    e = len(c)
    for f in range(0,len(d)-e+1):
        if sorted([d[f+h] for h in range(e)]) == c:
            i = 1
            print('YES')
            break
    if i == 0:
        print('NO')
```
还没有 python 题解，希望管理员通过！字数可能有点少，但是这道题就是这么简单！

---

## 作者：loser_seele (赞：0)

既然题目里写了哈希，那就来一个哈希做法。

具体地，枚举需要匹配的串的所有子串，然后将这个字串内所有出现的字符的出现次数用哈希函数映射成一个值，丢哈希表里，最后比对文本串的哈希值是否出现过即可。

时间复杂度 $ \mathcal{O}(kn^2) $，其中 $ k=26 $ 为字符集大小，$ n $ 为较短串的大小，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=9284776759;
int hasher(string s) 
{
	int cnt[27]= {0};
	int res=0;
	for (auto x:s)
	cnt[x-'a'+1]++;
	for (int i=1;i<=26;i++)
	res*=2333,res+=cnt[i],res%=mod,cnt[i]=0;
	return res;
}
unordered_map<int,int>table;
signed main() 
{
	int T;
	cin>>T;
	while(T--) 
	{
		table.clear();
		string s,t;
		cin>>s>>t;
		if(s.size()>t.size())
		    puts("NO"); 
		else 
		{
			for (int i=0;i<t.size()-s.size()+1;i++) 
			{
				string tmp=t.substr(i,s.size());
				table[hasher(tmp)]++;
			}
			if(table[hasher(s)])
			    puts("YES"); 
			else
			    puts("NO");
		}
	}
}
```


---

## 作者：Ninelife_Cat (赞：0)

本题数据范围较小，用暴力就能过。

由于 $p'$ 是 $h$ 的一个子串，所以我们直接把 $h$ 的所有子串一一拉出来和 $p$ 进行匹配，一旦匹配合法直接输出 ```YES```。

匹配的话就把两个字符串排一下序，判是否相等就好了。

注意特判 $h$ 长度比 $p$ 小的不合法情况。

核心代码：

```cpp
#define ri register
int T;
string s,t;
signed main()
{
	cin>>T;while(T--)
	{
		cin>>s>>t;
		if(t.size()<s.size()) {cout<<"NO\n";continue;}//特判不合法情况
		sort(s.begin(),s.end());
		for(ri int i=0;i<=t.size()-s.size();++i)
		{
			string a=t.substr(i,s.size());//截取子串
			sort(a.begin(),a.end());
			if(s==a) {cout<<"YES\n";goto End;}
		}
		cout<<"NO\n";End:;
	}
	return 0;
}
```

---

## 作者：YGB_XU (赞：0)

在这里提供一种较为暴力且易懂的做法，我们枚举第二个字符串中每个长度等于第一个字符串的连续子串，并记录其中每个字母出现的次数。若相同字母出现的次数都完全相同，则说明这段子串可以由第一个字符串重组得到。这样每组数据时间复杂度为 $O(\left|s\right|^2)$，最大只会到一万，全部数据下来也只会到百万级（而且实际上远小于这个数字）。此外还要注意特判 $\left|s_1\right|>\left|s_2\right|$ 的情况，直接输出 `NO`。

详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int cnt[30],ans[30];
int len1,len2;
string s1,s2;

bool check(int x){
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<len1;i++){
		cnt[s2[i+x]-'a'+1]++;//将字符转换为字母表编号，下同
	}
	for(int i=1;i<=26;i++) if(cnt[i]!=ans[i]) return false;
	return true;
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		memset(ans,0,sizeof(ans));
		cin>>s1>>s2;
		len1=s1.length(),len2=s2.length();
		if(len1>len2){//特判s1比s2长的情况
			printf("NO\n");
			continue;
		}
		for(int i=0;i<len1;i++) ans[s1[i]-'a'+1]++;//预处理s1字母数量
		bool flag=false;
		for(int i=0;i<=len2-len1;i++) if(check(i)){
			flag=true;
			printf("YES\n");
			break;
		}
		if(!flag) printf("NO\n");
	}
	return 0;
}

```

---

