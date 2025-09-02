# Anagram Search

## 题目描述

若字符串 $s$ 在交换字母顺序后可以得到 $t$，则称两个串是“相似”的（$s$ 为 $t$ 的 anagram）。

给定由小写字母与“?”组成的字符串 $s$ 和由小写字母组成的字符串 $t$。定义一个字符串是好的，当且仅当这个串存在某种将每个“?”替换为一个小写字母的方式，使它与 $p$ 相似（是 $p$ 的 anagram）。问 $s$ 有多少子串是好的（两子串不同当且仅当它们在 $s$ 中的开始位置或终止位置不同）。

## 样例 #1

### 输入

```
bb??x???
aab
```

### 输出

```
2
```

## 样例 #2

### 输入

```
ab?c
acb
```

### 输出

```
2
```

# 题解

## 作者：FP·荷兰猪 (赞：3)

首先考虑到的自然是暴搜一遍，复杂度O(n^2)，回去看了一下数据范围，发现s,p的长度要到1e5，会超时。

~~怎么办呢？~~

因为这道题仅仅是比较两个字符串中字母的个数，显然可以用两个数组记录字符串中一段字符的字母个数，用这两个表比较。往后移动的时候，把之前的那个字母去掉，再往后移动就可以实现遍历s的所有子字符串。这就是我们所熟悉的滑动窗口思想。复杂度为O（n）。

**Solution：**
```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100005],p[100005];
int ans;
int main()
{
	cin>>s>>p;
	int i,j,ls=strlen(s),lp=strlen(p),ss[30],pp[30];
	bool x;
	memset(ss,0,sizeof ss);
	memset(pp,0,sizeof pp);
	for(i=0;i<ls;i++)
	{
		pp[p[i]-'a']++;
	}
	for(i=0;i<ls;i++)
	{
		x=true;
		ss[s[i]-'a']++;
		if(i+1>=lp)
		{
			for(j=0;j<26;j++)
			{
				if(ss[j]>pp[j])
				{
					x=0;
					break;
				}
			}
			if(x)
			{
				ans++;
			}
			ss[s[i-(lp-1)]-'a']--;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Dehydration (赞：1)

### 前言：

代码虽然很长，但十分好理解捏。

### 思路：

前缀和记录 $s$ 里面的所有字母，在进行前缀和与 $t$ 中的比较，不需要管 `?` 的数目，如果一旦 $s$ 的字母数大于 $t$ 中的，直接 `return`，否则总是可以用 `?` 进行排序的。

复杂度 $\Theta(n)$。

### 代码：

有注释可以看一下：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int sums[100005][28],sumt[28],ans;
bool pd(int x,int y){
	for(int i=0;i<26;i++){
		if(sums[y][i]-(x>=0)*sums[x][i]>sumt[i]){//为了防止溢出，因为下表从 0 开始，减1就成了负数，会RE
			return false;
		}
	}
	return true;
}
int main(){
	cin>>s>>t;
	int lens=s.size(),lent=t.size();
	for(int i=0;i<lens;i++){
		if(i==0){
		    if(s[i]=='?')sums[i][27]=1;else
		    sums[i][s[i]-'a']=1;
		}
  		sums[i][27]=sums[i-1][27]+s[i]=='?';
  		for(int j=0;j<26;j++){
			sums[i][j]=sums[i-1][j];
			if(s[i]-'a'==j)sums[i][j]++;
	    }//前缀和数组，各个字母都要记录
	}
	for(int i=0;i<lent;i++){
		sumt[t[i]-'a']++;
	}
	for(int i=0;i<=lens-lent;i++){
		int j=i+lent-1;
		if(pd(i-1,j)){
			ans++;
		}
	}
	cout<<ans<<'\n';//可以，输出！
	return 0;
}
```

### 完美撒花！

---

## 作者：luogu_gza (赞：1)

今天偶然刷到这道题目，发现可以写题解，~~水社贡~~。

---

首先肯定是最朴素的想法。

我们对于每一个在 $s$ 中长度等于 $p$ 的长度的子串，都检查一下是否符合题意。

这样做的复杂度是 $O(n^2)$ ，TLE。

所以我们需要优化。

发现每一次移动窗口只有两个位置，所以，我们每次可以 $O(1)$ 维护窗口。

这里也是用到了滑动窗口的思想。

复杂度： $O(n)$

ps：我的代码的缺省源不放了，反作弊


```cpp
string a,b;
map<char,int> ma,mb;
int check()
{
    int res=0;
    fo(i,'a','z')
    {
        if(ma[i]<=mb[i]) res+=mb[i]-ma[i];
        else return 0;//a
    }
    return res==ma['?'];
}
signed main(){
    cin>>a>>b;
    if(a.size()<b.size()) puts("0");
    else
    {
        fo(i,0,b.size()-1) ma[a[i]]++,mb[b[i]]++;
        int ans=check();
        fo(i,b.size(),a.size()-1) ma[a[i-b.size()]]--,ma[a[i]]++,ans+=check();
        write(ans);
    }
    return 0;
}

```

---

## 作者：Kyl_in_2024 (赞：0)

**前言**

~~有个同学第一遍没过我不说是谁。~~

**思路**

重新排序其实并不需要真的重排，只要统计字母个数有没有超出 $t$ 的数量即可。

众所周知，数据范围提示做法，因为一个个枚举字符串肯定会超时，所以可以用桶数组前缀和或者边输入边统计。~~后面的方法太麻烦了所以没用。~~ 注意字符串 $t$ 里是确定没有 `?` 的，不然预处理的时候麻烦一点。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int b[100005][26];
int x[26],sum=0;
int main(){
	string s,p;
	cin>>s>>p;
	if(s[0]!='?') b[0][s[0]-'a']++;
	for(int i=1;i<s.size();i++){
		for(int j=0;j<26;j++) b[i][j]=b[i-1][j];
		if(s[i]!='?') b[i][s[i]-'a']++;
	}
	for(int i=0;i<p.size();i++) x[p[i]-'a']++;
	bool flag=1;
	for(int i=p.size()-1;i<s.size();i++){
		flag=1;
		for(int j=0;j<26;j++){
			if(b[i][j]-((i==p.size()-1)?0:b[i-p.size()][j])>x[j]) flag=0;
		}
		if(flag) sum++;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Peaky (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF144C)。

**题目大意**

若字符串 s 在交换字母顺序后可以得到 t，则称 s 为 t 的 anagram 。

给定由小写字母与“?”组成的字符串 s 和由小写字母组成的字符串 t 。  
定义一个字符串是好的，当且仅当这个串存在某种将每个“?”替换为一个小写字母的方式，使它是 p 的 anagram 。  
问 s 有多少子串是好的。

**思路**

考虑到 $ | \text s| = 1\times10^5 $，所以爆搜是肯定不可以的。  
由于在某个 $ \text i $，使得 $ \text s_i , \text s_{i+1} ,..., \text s_{i+|p|-1} $ 的每一个字母的个数相等就可以称该范围内的字符串为“相似”的，于是就可以想到可以用[滑动窗口](https://www.cnblogs.com/huansky/p/13488234.html)。

代码如下：
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=1e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
char s[N],t[N];
int k,ans,tl,sl,flag,cnts[128],cntt[128];
int main(){
	cin>>s>>t;
	tl=strlen(t);
	for(int i=0;i<tl;i++) cntt[t[i]]++;
	sl=strlen(s);
	for(int i=0;i<sl;i++){
		if(s[i]!='?') cnts[s[i]]++;
		if(i>=tl&&s[i-tl]!='?') cnts[s[i-tl]]--;
		if(i>=tl-1)
			for(k='a',flag=1;k<='z';k++)
				if(cnts[k]>cntt[k]){flag=0;break;}
		ans+=flag;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

对于一个区间，由于是对字母进行重排。

所以和 $t$ 串长度相等的区间中，只要没有这个区间中的某个字符的数量 $> t$ 串中某个字符的数量，那么就一定可行。

因为除了这个区间内已有的字符，剩余的就是 $?$，然后将在 $t$ 中但未在当前区间中的字符填充进去即可。

然后就是要获得区间某个字符的个数，前缀和即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
string s, p;
int sum[200010][30];
int cnt[30];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> s >> p;
	n = s.size(), m = p.size();

	if (s[0] != '?') sum[0][s[0] - 'a']++;

	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < 26; ++j) sum[i][j] += sum[i - 1][j];

		if (s[i] != '?')
			sum[i][s[i] - 'a']++;
	}

	for (int i = 0; i < m; ++i) cnt[p[i] - 'a']++;

	int res = 0;

	for (int i = 0; i + m - 1 < n; ++i) {
		int cc[30] = {};
		for (int j = 0; j < 26; ++j) cc[j] = sum[i + m - 1][j] - (i == 0 ? 0 : sum[i - 1][j]);

		bool ok = true;
		for (int j = 0; j < 26; ++j) if (cc[j] > cnt[j])
			ok = false;

		res += ok;
	}

	printf("%d\n", res);

	return 0;
}
```

---

## 作者：Empty_Dream (赞：0)

# CF144C 解题报告

## 题意

给两个字符串 $s$ 和 $t$，让你求 $s$ 好的**子串**的个数。

对于 $s_1$ 和 $s_2$，若 $s_1$ 交换字母顺序后可以得到 $s_2$，即 $s_1$ 和 $s_2$ 拥有的字母相同且相同字母的个数相同，则我们称之为 $s_1$ 相似于 $s_2$。

## 分析

由题意得，可以记录每个字符出现了几次。这里可以记录 $s$ 的字串每个字母出现了多少次，再比较 $t$ 中的字母，若相同，则满足条件。

这里可以优化一下，直接记录 $t$ 中每一个字符的出现次数减去 $s$ 中对应字符的出现个数 $a_i$，如果 $a_i \ge 0$ 那么 $t$ 中出现的字符的次数一定比 $s$ 中的多。显然，如果每一个字符都是 $t$ 比 $s$ 多，那么 $s$ 在补全 `?` 之后字符出现次数一定与 $t$ 相同。

不断挪动 $s$ 中对应的区间，维护 $a$ 数组，实时更新答案。

一个特判，如果 $s$ 比 $t$ 短，那么一定不可能有合法情况。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int cnt;
int a[26];
string s, t;

int main(){
    cin >> s >> t;
	if (s.size() < t.size()) return cout << "0", 0;
	for (int i = 0; i < t.size(); i++){//初始化a
		a[t[i] - 'a']++;
		if (s[i] != '?') a[s[i] - 'a']--;
	}
	int l = 0, r = t.size() - 1;
	while (r < s.size()){
		int i = 0;
		while (i < 26 && a[i] >= 0) i++;//判断t中字符的出现次数的是否大于s
		if (i == 26) cnt++;//满足条件，全部大于等于
        if (r == s.size() - 1) break;
		if (s[l] != '?') a[s[l] - 'a']++;//挪动窗口，维护a
        if (s[r + 1] != '?') a[s[r + 1] - 'a']--;
		l++, r++;
	}
	cout << cnt;
	return 0;
}
```

---

## 作者：_szs9601 (赞：0)

### 思路
称两个串是相似的条件是字符串 $s$ 在交换字母顺序后可以得到 $t$。因为交换次数是无限的，而且 $?$ 可以变成任何字母，所以我们只要判断 $s$ 子串中的各个字母总数小于等于 $t$ 中的字母总数，因为剩下的字母可以直接用 $?$ 补上。

对于 $s$，我们用前缀和统计出现的字母个数，然后枚举 $s$ 中的每一个长度和 $t$ 相等的子串，判断是否相似。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,len,len1,ans,flag;
int f[100100][150],e[150];
char s[100100],s1[100100],ch;
int main(){
	scanf("%s",s+1);len=strlen(s+1);
	for(i=1;i<=len;i++)
		if(s[i]!='?') f[i][s[i]]=1;
	for(i=1;i<=len;i++)
		for(ch='a';ch<='z';ch++)
			f[i][ch]+=f[i-1][ch];//前缀和
	scanf("%s",s1+1);len1=strlen(s1+1);
	for(i=1;i<=len1;i++) e[s1[i]]++;
	for(i=len1;i<=len;i++){//枚举子串
		flag=1;
		for(ch='a';ch<='z';ch++)
			if(f[i][ch]-f[i-len1][ch]>e[ch]) flag=0;
		if(flag) ans++; //判断是否相似
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

水蓝水蓝的萌萌题。

首先发现相似的两个字符串一定是长度相等的，那么就考虑在 $s$ 中枚举每一个长度和 $l$ 字符串相等子串。

然后考虑如何判断。

由于这相似的两个字符串可以任意调换位置，那么只需要两个字符串中所拥有的的各个字符数量相等即可。

具体地，用滑动窗口的方式统计每一种字符出现的次数，然后计算出确定小写字母的相差值，然后和可以任意换的问号字符的数量比较即可。

---------------

注意如果用滑动窗口写，记得判断两串长度，否则会 RE。

-------------
### 代码：

```cpp
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
int sum1[30],sum2[30],len1,len2,ans;
string s,l;
bool check(){
	int tot=0;
	for(int i=1;i<=26;i++)
	tot+=abs(sum1[i]-sum2[i]);
	return tot<=sum1[0];
}
int main(){
	cin>>s>>l;
	len1=s.length();
	len2=l.length();
	if(len1<len2){
		printf("0\n");
		return 0;
	}
	for(int i=0;i<len2;i++){
		if(s[i]=='?')sum1[0]++;
		else sum1[s[i]-'a'+1]++;
		sum2[l[i]-'a'+1]++;
	}
	ans+=check();
	for(int i=len2;i<len1;i++){
		if(s[i-len2]=='?')sum1[0]--;
		else sum1[s[i-len2]-'a'+1]--;
		if(s[i]=='?')sum1[0]++;
		else sum1[s[i]-'a'+1]++;
		ans+=check();
	}
	printf("%d",ans);
	return 0;
}
```




---

## 作者：QQH08 (赞：0)

这题不用滑动窗口，暴力也可以解吧。

首先，如果 $2$ 个字符串交换字母顺序后相同， 只要它们每个字母出现的个数相同即可。那么这题中的 ? 可以随便换，所以只要 s 的子串中每一个字母的个数都小于等于 t 即可。

对于 s 的每一个子串，先预处理出 s 中每个字母前缀和的个数，然后每次枚举每个字母，分别判断就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005; 
char s[N],t[N];
int ans,s1[N][26],s2[26];
int main(){
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<26;j++){
			if(j==int(s[i]-'a'))s1[i][j]=s1[i-1][j]+1;
			else s1[i][j]=s1[i-1][j];
		}
	}
	for(int i=1;i<=m;i++)s2[int(t[i]-'a')]++;
	for(int i=1;i+m-1<=n;i++){
		bool flag=1;
		for(int j=0;j<26;j++)
			if(s1[i+m-1][j]-s1[i-1][j]>s2[j]){
				flag=0;
				break;
			}
		if(flag)ans++;
	}
	printf("%d",ans);
	return 0;
} 
```


---

## 作者：iiawaKL (赞：0)

###### 蒟蒻写题解啦AWAAWA

今天我们来讲一题看上去很难但想清楚思路后就堪比~~黑题~~红题的一道题->Anagram Search。

如果我们暴搜一遍，那是杠杠的T，但是我们可以往下想，慢慢的，我们就可以想到滑动窗口了。

不懂滑动窗口的小蒟蒻们看下->[滑动窗口](https://www.cnblogs.com/HM1997/p/11149005.html)

代码见下->

```
#include<bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define FORN(i,n) for(int i=1;i<=n;i++)
using namespace std;
const int Maxl=26;
string s,p;
int freq[Maxl];
int orz[Maxl]; 
int res; 
int main(){
	cin>>s>>p;
	if(s.size()<p.size()){
		cout<<0<<endl;
		return 0;
	}
	for(int i=0;i<p.size();i++){
		freq[p[i]-'a']++;
		if(s[i]!='?')orz[s[i]-'a']++;
	}
	bool flagp=true;
	for(int i=0;i<26;i++){
		if(orz[i]>freq[i])flagp=false;
	}
	if(flagp)res++;
	int l=0,r=p.size()-1;
	while(l<s.size()){
		if(s[l]!='?')orz[s[l]-'a']--;
		l++;r++;
		if(r==s.size())break;
		if(s[r]!='?')orz[s[r]-'a']++;
		bool flag=true;
		for(int i=0;i<26;i++){
			if(orz[i]>freq[i])flag=false;
		}
		if(flag)res++;
	}
	cout<<res<<endl;
	return 0;
}
```


---

