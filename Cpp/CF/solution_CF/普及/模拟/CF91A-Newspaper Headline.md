# Newspaper Headline

## 题目描述

A newspaper is published in Walrusland. Its heading is $ s_{1} $ , it consists of lowercase Latin letters. Fangy the little walrus wants to buy several such newspapers, cut out their headings, glue them one to another in order to get one big string. After that walrus erase several letters from this string in order to get a new word $ s_{2} $ . It is considered that when Fangy erases some letter, there's no whitespace formed instead of the letter. That is, the string remains unbroken and it still only consists of lowercase Latin letters.

For example, the heading is "abc". If we take two such headings and glue them one to the other one, we get "abcabc". If we erase the letters on positions $ 1 $ and $ 5 $ , we get a word "bcac".

Which least number of newspaper headings $ s_{1} $ will Fangy need to glue them, erase several letters and get word $ s_{2} $ ?

## 样例 #1

### 输入

```
abc
xyz
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
abcd
dabc
```

### 输出

```
2
```

# 题解

## 作者：b6e0_ (赞：5)

[CF题面传送门](https://codeforces.com/contest/91/problem/A) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF91A) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF91A)

看见有大佬用`set`做的，其实没必要，用`vector`就行。

每一个字符$c$开一个`vector`，将$s1$中$c$的位置从小到大放进`vector`中。判断$s2$中有没有$s1$中没有出现的字符。

扫描$s2$。设$s2_{i-1}$在$s1$中的位置为$j$，对于一个字符$s2_i$，在$s2_i$的`vector`中二分查找大于$j$的位置，如果找不到就跳出循环，说明要再拼接一个字符串，累加答案；如果找得到就将$j$更新为这个位置。二分查找可以用`upper_bound`。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
vector<int>pos[300];//位置
int main()
{
	string s1,s2;
	int i,j,ans=0;
	cin>>s1>>s2;
	for(i=0;i<s1.size();i++)
		pos[s1[i]].push_back(i);
	for(i=0;i<s2.size();i++)
		if(pos[s2[i]].empty())//判断s2中有没有s1中没有的字符
			break;
	if(i<s2.size())
	{
		cout<<-1;
		return 0;
	}
	for(i='a';i<='z';i++)
		pos[i].push_back(s1.size()+1);//多放一个位置，以免查找出现越界
	for(i=0;i<s2.size();)
	{
		ans++;
		j=*upper_bound(pos[s2[i]].begin(),pos[s2[i]].end(),-1);//第一个找比-1大的
		while(j<s1.size())
		{
			i++;
			if(i<s2.size())
				j=*upper_bound(pos[s2[i]].begin(),pos[s2[i]].end(),j);//找大于j的
			else
				break;
		}
	}
	cout<<ans;
	return 0;
}
```
时间复杂度为$O(|s2|\log|s1|)$。

---

## 作者：xiaozeyu (赞：2)

**一道字符串题目，我们可以用一个set来存**

**用upper_bound好写**

**set默认的比较规则先按照first比较，如果first相同，再按照second 比较。 注意：定义的时候右边的两个> >要空一格。**


**lower_bound(key_value) ，返回第一个大于等于key_value的定位器，也可以理解为查找“大于等于x”的第一个位置，例如lower_bound（a，a+n,x）-a；**

**upper_bound(key_value)，返回最后一个大于等于key_value的定位器**


**上代码~~·**

------------

```c
//可以在s2上重复搜索，一直在s2后加上所给的字符串
#include<bits/stdc++.h>
using namespace std;
set<int>g[26];//定义一个set
char s1[10020];
char s2[1000020];//定义其他的
int p=-1,z=1;//z一开始要为一，因为不接时为有一串在
int main()
{
	cin>>s1>>s2;//整个输入字符串
	for(int i=0;s1[i];i++)//循环整个s1
		g[s1[i]-'a'].insert(i);//先进行处理s1
	for(int i=0;s2[i];i++)///可以在s2上重复搜索，一直在s2后加上所给的字符串
	{
		if(g[s2[i]-'a'].empty())//判断是否为空
			return cout<<-1,0;//空就输出0
		if(g[s2[i]-'a'].upper_bound(p)==g[s2[i]-'a'].end())//查找插入位置，即能不能s2末尾再上加上字符串
			p=-1,z++;	//计数要插入几个字符串，p重置		
		p=*g[s2[i]-'a'].upper_bound(p);//用upper_bound（）记录插入后地址
	}
	cout<<z;//输出最后结果
}

```


---

## 作者：_WHX985_ (赞：1)

# 题意
输入两个字符串 $s_1$ 和 $s_2$ 问构成 $s_2$ 至少需要几个 $s_1$。
# 思路
虽然用 set 和 vector 也可以，但这样用的知识点较多，所以今天介绍的是本题最见做法，直接枚举。输入后首先看有没有 $s_2$ 字符串有的字符但 $s_1$ 字符串没有，这种情况输出 -1 因为无论拼多少个 $s_1$ 字符串也不会有这个字符。如果没有这样的字符就一个一个找。
# 代码

```cpp
#include<bits/stdc++.h>
#define l size()-1
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define fd(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
int dp[27][10005];
int lpos,pos,ans=1;
string s1,s2;
map<char,bool>mp;
int main(){
	cin>>s1>>s2;
	fo(i,0,s1.l)mp[s1[i]]=1;
	fo(i,0,s2.l)
		if(!mp[s2[i]])return cout<<-1,0;
	fo(i,0,25)
		if(mp[i+'a']){
			int tmp=s1.l+1;
			fd(j,s1.l,0){
				if(s1[j]==i+'a')tmp=j;
				dp[i][j]=tmp;
			}
			fo(j,0,s1.l)
				if(dp[i][j]==s1.l+1)dp[i][j]=tmp;
		}
	fo(i,0,s2.l){
		if(s2[i]==s2[(i+s2.l)%s2.size()]){
			lpos=pos;
			pos=dp[s2[i]-'a'][(pos+1)%s1.size()]; 
		}
		else{
			lpos=pos;
			pos=dp[s2[i]-'a'][pos];
		}
		if(pos<=lpos)ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiaomimxl (赞：1)

# 题意：

给两条字符串 $s1$,$s2$ 问你是否能用 $n$ 条 $s1$ 按顺序排成一条新的字符串，并从其中去掉任意个字符来得到 $s2$，如果能，输出最小的 $n$，否则输出 $-1$。
# 分析：
先对字符串 $s1$ 进行预处理:

$index[i]$ -----字符 $i$ 在 $s1$ 中第一次出现的位置。

$dp[i][j]$ -----第 $i$ 个下标后字符 $j$ 第一次出现的位置。

遍历 $s2$ 的每一个字符，如果存在 $s1$ 中没有的字符，输出 $-1$。

$pre$ 记录 $s2$ 前一个字符出现在 $s1$ 中的位置。然后找当前字符在 $pre$ 后第一次出现的位置，如果 $-1$ 没有， 表示要增加一个 $s1$, 如果有就到那一个位置。往后递推。

# Code：

```cpp
# include<iostream>
# include<string.h>
using namespace std;

int dp[10005][30];
int index[30];
int num = 1;

char s1[10005], s2[1000005];


int main()
{
	
	while(~scanf("%s %s", s1, s2))
	{
		//cout<<s1<<"  "<<s2<<endl;
		int len1 = strlen(s1);
		int len2 = strlen(s2);
		memset(index, -1, sizeof(index));
		memset(dp, -1, sizeof(dp));
		for(int i = 0; i < len1; ++i)
		{
			if(index[s1[i] - 'a'] == -1)
			{
				index[s1[i] - 'a'] = i;
			}
		}
		for(int i = 0; i < len1; ++i)
		{
			for(int j = i+1; j < len1; ++j)
			{
				if(dp[i][s1[j] - 'a'] == -1)
				{
					dp[i][s1[j] - 'a'] = j;
				}
			}
		}
		
		int flag = 0;
		for(int i = 0; i < len2; ++i)
		{
			if(index[s2[i] - 'a'] == -1)
			{
				flag = 1;
				printf("-1\n");
				break;
			}
		}
		if(!flag)
		{
			int pre = index[s2[0] - 'a'];
			int next;
			for(int i = 1; i < len2; ++i)
			{
				next = dp[pre][s2[i] - 'a'];
				if(next == -1)
				{
					num ++;
					pre = index[s2[i] - 'a'];
				}
				else
				{
					pre = next;
				}
			}
			printf("%d\n", num);
		}
		
	}		
	
	return 0;
 } 

```


---

## 作者：HMZHMZHMZ (赞：1)

二分好题（

## 题意

问最少有多少个字符串 $ s_1 $，拼接在一起后删去一些字符能构成 $ s_2 $ 。

## 思路

暴力方法显然。每一次都贪心往后取即可，复杂度 $ O ( \left| s_1 \right| \times \left| s_2 \right|) $ ，不能过。

考虑如何优化。

我们的贪心方法是取当前位置之后第一个我们所需要的字符，所以可以拿一个 ` vector ` 或别的数据结构存储字符出现的位置，然后每一次二分出下标最小的合法字符的下标即可。

最终时间复杂度是 $ O (  \log \left| s_1 \right| \times \left| s_2 \right|) $ 。

## 代码

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m,ans;
char s1[N],s2[N];
vector<int> v[N];
inline int bs(int l,int r,int c,char typ){
    if(v[typ][r]<=c) return 0x3f3f3f;
    while(l<r){
        // cout<<l<<" "<<r<<endl;
        int mid=(l+r)>>1;
        if(v[typ][mid]>c) r=mid;
        else l=mid+1;
    }
    return v[typ][l];
}
int main(){
    cin>>(s1+1)>>(s2+1);
    n=strlen(s1+1),m=strlen(s2+1);
    for(register int i=1;i<=n;++i) v[s1[i]].push_back(i);
    for(register int i=1;i<=m;++i){
        if(!v[s2[i]].size()){
            printf("-1");
            return 0;
        }
    }
    int l=1;
    while(l<=m){
        ans++;
        l++;
        int now=v[s2[l-1]][0];
        while(now<=n&&l<=m){
            now=bs(0,v[s2[l]].size()-1,now,s2[l]);
            if(now>n) break;
            ++l;
        }
        // cout<<l<<endl;
    }
    printf("%d",ans);
    return 0;
}

```

---

## 作者：HEzzz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF91A)

## 解析

因为在新的字符串中可以删掉若干个，所以我们只需要在 $s1$ 寻找 $s2$ 的每一个字符。

这里提前预处理出 $s1$ 各个字符出现的位置，要考虑**贪心**地使用距离上次使用在 $s1$ 的位置 $lst$ 最近的位置，可以想到用**二分**来寻找。如果不能在 $lst$ 后找到需要的字符，那就意味着要多加一个 $s1$。

## code


```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=1e4+5,M=1e6+5; 
int ans=1,lst;
char s1[N],s2[M];
set<int>s[26];
int main()
{ 
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>(s1+1)>>(s2+1);
	int n=strlen(s1+1),m=strlen(s2+1);
	_rep(i,1,n) s[s1[i]-'a'].insert(i);
	_rep(i,1,m)
	{
		if(s[s2[i]-'a'].empty()) 
		{
			cout<<-1;
			return 0;
		}
		set<int>::iterator it=s[s2[i]-'a'].upper_bound(lst);
		if(it==s[s2[i]-'a'].end())
		{  
			ans++; 
			it=s[s2[i]-'a'].upper_bound(0);
			lst=*it;
		}
		else lst=*it;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Peaky (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF91A)。
### 思路
我们可以用一个数组统计每一个字母的几次出现的位置，再依次找 $\texttt{s2}_{i}$ 在 $\texttt{s1}$ 中既**大于** $\texttt{s2}_{i-1}$ 从 $\texttt{s1}$ 中找到的位置，又是**最早**出现的字母的位置。若不存在，则要所接一个 $\texttt{s1}$ 位置为 $\texttt{s2}_{i}$ 在 $\texttt{s1}$ 中**第一次出现的位置**。
### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*
1147517
114514
*/
string s1,s2;
int cnt[129],pos[129][N],sum=1;
int main(){
	cin>>s1>>s2;
	for(int i=0;i<s1.size();i++) pos[s1[i]][++cnt[s1[i]]]=i;
	for(int i=0,j=0;i<s2.size();i++){
		if(!cnt[s2[i]]) return cout<<-1,0;
		if(i==0&&j==0&&s2[i]==s1[j]) continue;
		int l=0,r=cnt[s2[i]],ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(pos[s2[i]][mid]>j) ans=mid,r=mid-1;
			else l=mid+1;
		}
		if(ans==-1) sum++,j=pos[s2[i]][1];
		else j=pos[s2[i]][ans];
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：TsH_GD (赞：0)

### 【题意】

给你两个串 $s1$ , $s2$ ，问构成 $s2$ 至少需要几个 $s1$ ？（可以不连续）。

## 【分析】

* 数组 $f[i][j]$ ：记录 $s1$ 串中第 $i-1$ 个字母后字母 $j$ 第一次出现的位置。
* 数组 $vis[i]$ ：用于判断判断 $s2$ 串中的字母是否都在 $s1$ 中出现过，顺带记录所有 $s1$ 中字母第一次出现的位。
* 遍历 $vis$ 数组，如果出现 $-1$ ，说明存在 $s2$ 中的字符没有在 $s1$ 中出现过。则输出 $-1$  。
* $now$ 记录当前位置，$go$ 记录下一个位置。
* 注意， $f$ 数组，开 $30$ ，而不是直接用字母作为下标，这样的话复杂度会低很多。

### ACCODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[10005][30]; 
int vis[30];
char s1[10005],s2[1000005];
int main()
{
	while(~scanf("%s%s",s1,s2))
	{
		int ans=1;
		int len1=strlen(s1),len2=strlen(s2);
		memset(f,-1,sizeof(f));
		memset(vis,-1,sizeof(vis));
		for(int i=0;i<len1;i++)
		{
			if(vis[s1[i]-97]==-1)vis[s1[i]-97]=i;
			for(int j=i+1;j<len1;j++)
				if(f[i][s1[j]-97]==-1)f[i][s1[j]-97]=j;
		}
		int flag=1;
		for(int i=0;i<len2;i++)
			if(vis[s2[i]-97]==-1)
			{
				puts("-1");
				flag=0;
				break;
			}
		if(!flag)continue;
		int now=vis[s2[0]-97],go;
		for(int i=1;i<len2;i++)
		{
			go=f[now][s2[i]-97];
			if(go==-1)
			{
				ans++;
				now=vis[s2[i]-97];
			}
			else{
				now=go;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
 } 
 ```

---

