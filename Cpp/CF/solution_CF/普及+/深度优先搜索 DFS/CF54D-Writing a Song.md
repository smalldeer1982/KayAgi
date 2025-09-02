# Writing a Song

## 题目描述

**题目大意**

求一个字符串s，满足该串长度为n，只出现字母表中前k个字母，并且在指定位置必须出现指定字符串p

## 样例 #1

### 输入

```
5 2
aba
101
```

### 输出

```
ababa```

## 样例 #2

### 输入

```
5 2
a
10001
```

### 输出

```
abbba```

## 样例 #3

### 输入

```
6 2
abba
101
```

### 输出

```
No solution```

# 题解

## 作者：minecraft_herobrine (赞：6)

#### UPD：01和字母都已加了空格

### 翻译

给你一个字符串 $S$ 和一个长度为 $n$ 的 01 串，要求你构造一个长度也为 $n$ 的字符串 $T$ 满足：

01 串中是 1 的位置一定是 $T$ 中一个子串 $S$ 的开头，是 0 的位置**一定不是** $T$ 的一个子串 $S$ 的开头

### 题解


#### 先考虑 1 的情况

用一个 $i=1\to n$ 枚举 01 串

如果当前位置是 1，则再用 $j=1\to |S|$ 枚举串 $S$

若串 $T$ 也就是输出串中的位置 $i+j$ 被构造过并且不是 $S[j]$ 则说明出现了冲突，只能输出 No solution

否则就把 $T[i+j]=S[j]$

----

#### 接下来看 0 的情况

但是满足了所有 1，还不一定满足所有 0，~~疑车无据~~

再用 $i=1\to n$ 枚举 01 串中所有是 0 的位置，如果是 1 则跳过

对于每个合法 $i$，枚举 $j=1\to |S|$

如果发现 $T[i+j]\neq 0$ 且 $T[i+j]\neq s[j]$，说明这个 0 ~~被~~满足了，直接 break 掉循环 $j$

但没有发现上面那个条件呢？不满足条件有两种情况：

- $T[i+j]=0$
- $T[i+j]=s[j]$

对于第二种情况显然不能在这个位置上进行补救了，机会只在第一个情况了，这种情况是 $T[i+j]$ 还没被构造的情况，所以就搞一个不和 $S$ 匹配的字符就行了。

但没有出现第一种情况那就只能 No solution 了

只要出现第一种情况就一定可以满足所有 0 和 1 ，~~疑车无据x2~~

一些细节可以看代码帮助理解

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,bin;
char res[114];
int main()
{
	int n,m,i,j,len,lenb;
	scanf("%d %d",&n,&m);
	cin>>s>>bin;
	len=s.size();
	lenb=bin.size();
	for(i=0;i<lenb;i++)
	{
		if(bin[i]=='1')
		{
			for(j=0;j<len;j++)
			{
				if(res[i+j] && res[i+j]!=s[j])//已经被构造过但发生冲突
				{
					printf("No solution");
					return 0;
				}
				res[i+j]=s[j];
			}
		}
	}
	for(i=0;i<n;i++)
	{
		if(bin[i]=='0')
		{
			for(j=0;j<len;j++)
				if(res[i+j] && res[i+j]!=s[j]) break;//构造过并且不和S匹配就不管它了
			if(j==len)
			{
				for(j=0;j<len;j++)
				{
					if(!res[i+j])//第一种情况
					{
						res[i+j]=(s[j]=='a') ? 'b' : 'a';//构造一个不和S匹配的字符
						break;
					}
				}
				if(j==len)//如果没有第一种情况肯定就救不回来了
				{
					printf("No solution");
					return 0;
				}
			}
		}
	}
	for(i=0;i<n;i++)
	{
		if(!res[i]) res[i]='a';//如果前面都没构造说明这个位置可以填任意字符
		printf("%c",res[i]);
	}
	return 0;
}
```


---

## 作者：XiaoQuQu (赞：5)

~~不是吧四个 AC 两个题解~~

此题建议难度：入门 / 普及-.此题建议标签：字符串

一道微坑水题。我将我的思路与做题时遇到的坑给大家分享一下，希望大家都有收获。

## 题意
~~没人看不懂吧~~

大意就是让你弄一个字符串，根据他的 01 串来搞。

怎么个搞法呢？很简单。

设当前我们在这个 01 串的第 $i$ 位，则从第 $i$ 位开始，一直到第 $i+|p|$ 位，都必须和她的字符串 $p$ 相等。（ $|p|$ 表示字符串 $p$ 的长度）
## 怎么做？
先按照 01 串中的 `1` 来构建字符串，**最后来判断是否符合 `0`**。

**注意！！！一定要判断是否符合 `0` ！！！！！**

还是不明白？我画个图你就懂了。
---
这是样例：

![STEP1.png](https://i.loli.net/2021/07/24/AGbec5xOvEBwT6U.png)

好。第一步，我们要以 01 串的第一个字符来构建。一看，哇塞，是 `1` ，这说明什么？接下来 $i+|p|$ 位都得是这个 $p$ 串。

![STEP2.png](https://i.loli.net/2021/07/24/S83mxkUwZgAVfOr.png)

这时，我们发现，第 $2$ 位居然是 `0`？先放一边，不管他。

![STEP3.png](https://i.loli.net/2021/07/24/S83mxkUwZgAVfOr.png)

咦？又是一个 `1`？那就继续构建吧。注意！如果构建出的字符串的长度大于 $n$ 了，直接输出 `No solution` 即可。

![STEP4.png](https://i.loli.net/2021/07/24/a4RKlgjHWenpxqi.png)

好了，我们原本的字符串构建完毕了。现在开始判断是否符合在 01 串中 `0` 的地方不是开头。还是不明白？继续看。

![STEP5.png](https://i.loli.net/2021/07/24/EBS4iyn5L8uvFaW.png)

我们用 $j$ 遍历啊，遍历啊，终于遍历到一个 `0` 了。现在开始判断。

![STEP1.png](https://i.loli.net/2021/07/24/wfXoH8qT4GKQ1Fg.png)

判断 $j+0$ 和 $p$ 串的第 $0$ 位是否相同。

说了这么多，那如果是样例二呢？
---
也还是挺简单的。第一步，和样例一样。先构建出一个字符串。

![STEP1.png](https://i.loli.net/2021/07/23/UVkGi8hXma6v4wI.png)

然后用 $j$ 挨个遍历，突然！发现有 `0` 出现！

![STEP2.png](https://i.loli.net/2021/07/23/TpbtORVAeaEJ7YL.png)

如果没有字符，直接添上一个不为 $p$ 串第 $0$ 位的字符。

![STEP3.png](https://i.loli.net/2021/07/23/WeSlIomgds9GhOD.png)

注意！填的这个字符串必须不与 $p$ 串的第 $0$ 位相同！否则的话。。。`WA`了解一下？

![STEP4.png](https://i.loli.net/2021/07/23/7QuzmV1ojlErF4h.png)

像这样，挨个填完，就好了。

## 最后
码字+画图不易啊！！！求过啊！！！   
UPDATE:2021/07/24 更新了图  
UPDATE:2021/07/26 修复了图片无法加载的问题，如果还是无法加载就等一会。  
UPDATE 2021/07/27 $\LaTeX$ 与 英文之间加入了空格。

---

## 作者：xuchuhan (赞：3)

## 解法

设 $\texttt{01}$ 串为 $t$。

先按题意，若 `t[i]='1'`，那么就从第 $i$ 位开始，在答案串上逐位填充字符串 $p$。若答案串当前位已被填充说明与之前的填充冲突，直接输出 `No solution`。

填充完毕，此时的答案串有部分确定，又有部分不确定。

不确定的部分就需要利用**搜索**填充，每位可填充字母表前 $k$ 位字符。搜索的过程中，若从下标 $0$ 开始，已填充好的部分字符串存在某下标 $i$，使得 `t[i]='0'`，且从 $i$ 开始的 $\lvert p \rvert$ 位字符组成的字符串与 $p$ 相同，那么不符答案串成立条件，停止搜索。

只要搜到 $1$ 个答案，立刻输出并结束代码。若搜索结束仍未搜到答案，输出 `No solution`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s,t,ans;
void dfs(int step,string st){//当前枚举到step位，已填充完毕的字串为st
	for(int i=0;i<st.size();i++){
		//若每填充一次，就检查一次。发现不合法，立刻退出。不能填充完所有未填充字符'@'再进行检查。这样效率太低。
		if(t[i]=='1')
			continue;
		bool flg=0;
		for(int j=i;j<=i+s.size()-1;j++){//逐位检查，若不合法则退出。同样，用substr提取整个字符串再用==比对效率会低。
			if(st[j]!=s[j-i]){
				flg=1;
				break;
			}
		}
		if(!flg)
			return;
	}
	if(step>=n){//合法答案
		cout<<st;
		exit(0);//结束整份程序
	}
	if(ans[step]=='@'){//未被填充
		for(int i=0;i<k;i++)
			dfs(step+1,st+char(i+'a'));//前k个字母都可填充
	}
	else//已被填充，直接放入
		dfs(step+1,st+ans[step]);
}
int main(){
	cin>>n>>k>>s>>t;
	for(int i=0;i<n;i++)
		ans+='@';//某位是'@'表示其未被填充
	for(int i=0;i<t.size();i++){
		if(t[i]=='1'){
			if(i+s.size()>n){//无法填充
				cout<<"No solution";
				return 0;
			}
			for(int j=0;j<s.size();j++){
				if(ans[i+j]!=s[j]&&ans[i+j]!='@'){//填充冲突
					cout<<"No solution";
					return 0;
				}
				ans[i+j]=s[j];
			}
		}
	}
	dfs(0,"");
	cout<<"No solution";
	return 0;
}
```

---

## 作者：AladV (赞：2)

## 题意分析
~~hjh这道题居然没人A。~~
就是说让你构造一个串，然后必须在某些位置为开头开始一个特定的串，不让开使得地方不能有这个特定的串。

## 做法分析
先按照他给的 01 串强制构造，在构造的时候如果冲突（在之前的某处给这个地方赋了 'a'，但是现在需要 'b'，那就一定不可以，因为这个东西是不可改变的，冲突就是冲突）。

然后把剩下的空的地方给一个随便选的字母，这里建议选择一个跟 p 字符串的首字母不一样的字母。

之后遍历整个数组，处理一下不让有的地方他有的问题。遇到一个从 0 开始，但是跟 p 完全相同的串的时候，我们循环这个小段，找到第一个不被任何以 1 开头的串覆盖的位置 pos，然后试图更改他，即，改成一个与这个位置当前字母不一样的字母，如果不能改就输出不行好了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=110;
char s[N],p[N],is[N];
int n,k,plen;
bool vis[N],isfugai[N];
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
int main()
{
	for(int i=1;i<=105;i++) s[i]='*';
	n=read(),k=read();
	cin>>p;
	plen=strlen(p);
	cin>>is;
	for(int i=0;i<n;i++) if(is[i]=='1') vis[i+1]=true;
	for(int i=1;i<=n;i++)
	{
		if(vis[i])
		{
			int pos=0;
			for(int j=i;j<=i+plen-1;j++)
			{
				isfugai[j]=true;
				if(s[j]!=p[pos] && s[j]!='*') {puts("No solution");exit(0);}
				s[j]=p[pos];
				pos++;
			}
		}
	}
	char use='*';
	// for(int i=1;i<=n;i++) cout<<isfugai[i];
	for(int j=0;j<k;j++)
	{
		if((char)('a'+j)!=p[0]) use='a'+j;
	}
	for(int i=1;i<=n;i++) if(s[i]=='*') s[i]=use;
	int pos=1;
	while(1)
	{
		if(s[pos]=='*') break;
		pos++;
	}
	if((pos-1)>n) {puts("No solution");exit(0);}
	// for(int i=1;i<=n;i++) cout<<s[i];
		// puts("");
	for(int i=1;i<=n;i++)
	{
		if(!vis[i]) 
		{
			bool flag=false;
			int pos=0;
			for(int j=i;j<=i+plen-1;j++) 
			{
				if(s[j]!=p[pos]) flag=true;
				pos++; 
			}
			if(!flag) 
			{
				bool change2=false;
				int pos=-1;
				for(int j=i;j<=i+plen-1;j++)
				{
					pos++;
					if(!isfugai[j]) 
					{
						char change='*';
						for(int alpha=0;alpha<k;alpha++)
						{
							if((char)(alpha+'a')!=p[pos]) change=alpha+'a';
						}
						if(change=='*') flag=true;
						else s[j]=change,change2=true;
					}
					if(change2) break;
				}
				if(!change2) puts("No solution"),exit(0);
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<s[i];
	return 0;
}
```


---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
要求构造一个字符串 $s$，满足该串长度为 $n$，只出现字母表中前 $k$ 个字母，并且在指定位置必须出现指定字符串 $p$，或者报告无解.  
$n\le100$.
## $\text{Solution}$
第一眼：毒瘤计数题...  
看完题意：恶心贪心题...   
看到数据范围：就这？  
或许贪心构造还是可做的，但是对于这个数据范围，我们不必冒着 WA 的风险动脑.  
首先 KMP 预处理一下，然后设计 $dp_{i,j}$ 表示填到第 $i$ 位，匹配到 $p$  的第 $j$ 位是否合法.  
转移暴力在 kmp 上跳即可，这数据范围也不需要预处理加速了.  
对于输出方案，dp 过程中记录一下转移路径即可.  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
//#define double long double
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=105;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m,k;
int dp[N][N],frm[N][N],id[N][N];
int p[N],jd[N];
char s[N];
void kmp(){
  p[1]=0;
  for(int i=1,j=0;i<m;i++){
    while(j&&s[i+1]!=s[j+1]) j=p[j];
    if(s[i+1]==s[j+1]) ++j;
    p[i+1]=j;
  }
  //for(int i=1;i<=m;i++) printf("i=%d p=%d\n",i,p[i]);
  return;
}
int find(int j,int id){
  char c='a'+id-1;
  while(j&&s[j+1]!=c) j=p[j];
  if(s[j+1]==c) ++j;
  return j;
}
void print(int k,int pl){
  if(!k) return;
  print(k-1,frm[k][pl]);
  putchar('a'+id[k][pl]-1);
}
signed main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  #endif
  n=read();k=read();
  scanf(" %s",s+1);m=strlen(s+1);
  for(int i=1;i<=n-m+1;i++) scanf("%1d",&jd[i+m-1]);
  kmp();
  dp[0][0]=1;
  for(int i=0;i<=n;i++){    
    if(jd[i]){
      if(!dp[i][m]){
	printf("No solution\n");return 0;
      }
      for(int j=0;j<m;j++) dp[i][j]=0;
      //dp[i][p[m]]=1;frm[i][p[m]]=dp[i][m];id[i][p[m]]=id[i][m];
    }
    else{
      dp[i][m]=0;
    }
    if(i==n) break;
    for(int j=0;j<=m;j++){
      if(!dp[i][j]) continue;
      for(int p=1;p<=k;p++){
	int to=find(j,p);
	//printf("k=%d (%d %d) -> (%d %d)\n",p,i,j,i+1,to);
	dp[i+1][to]=1;frm[i+1][to]=j;id[i+1][to]=p;
      }
    }
  }
  for(int i=0;i<=m;i++){
    if(dp[n][i]){
      print(n,i);return 0;
    }
  }
  printf("No Solution\n");
  return 0;
}
/*

*/

```


---

## 作者：Graph_Theory (赞：0)

题解中 $01$ 串简称为 $b$。

题解中答案串简称为 $a$。

题解中 $p$ 串长度简称为 $l$。

### 题目

构造一个 $a$ 满足下列要求。

1. 对于所有 $b_i=1$ 时 $a_{i \to i+l}=p$。
2. 对于所有 $b_i=0$ 时 $a_{i \to i+l}\ne p$。
3. $a$ 出现的所有字母对应字母表序号均不超过 $k$。

无法构造时输出无解。

### 思路

首先满足第一条。

考虑无解情况怎么出现，当 $b_i=1$ 填充当前位置时发现某一位被填充过且与之前填充的不相即为无解。直接暴力即可。

```cpp
for(j=0;j<l&&b[i]=='1';j++)
		{
			if(a[i+j] && a[i+j]!=s[j]) return cout<<"No solution",0;
			a[i+j]=s[j];
		}
```

考虑第二条。

此时第一条满足之后第二条有可能会出现 $b_i=0$ 时 $a_{i \to i+l}= p$ 的情况。例如 `aaa 101` 时第一条都满足但第二条不满足。

并且当前还有没填写的地方，所以此时我们还要考虑新增加的字母会不会导致不满足。

第一点很好满足循环即可。

第二点显然我们可以利用 `a` 和 `b` 来组成任意不等于 $s$ 的字符串，又因为 $k>1$ 所以显然满足第三条。 

```cpp
for(j=0;j<l;j++) if(a[i+j] && a[i+j]!=s[j]) break;
if(j==l)
{
	for(j=0;j<l;j++)
	{
		if(!a[i+j])
		{//这里不能全部填上否则后面的可能不满足，只填一个就可以满足。
			a[i+j]=((s[j]=='a') ? 'b' : 'a');
			break;
		}
	}
	if(j==l) return cout<<"No solution",0;
}
```

最后再把没填上的添上，这些没任何限制，填 `a` 就可以。

---

## 作者：zhengtianyu1220 (赞：0)

## CF54D Writing a Song

**让我们一起写一首歌。**

### 字符串构造题。

要求构造一个字符串 $S$，满足该串长度为 $n$，只出现字母表中前 $k$ 个字母。并且给出一个模式串 $P$，要求在 $S$ 串某些地方必须出现 $P$，其他地方必须不出现 $P$。

首先满足 $01$ 串中为 1 的条件。在 $s$ 中，每一个为 $1$ 的位置放个 $P$ 即可，若有冲突即为 `No solution`。

再先满足 $01$ 串中为 $0$ 的条件。在 $s$ 中，每一个为 $0$ 的位置检查一遍子串是否为 $P$。

经典 dfs。

### code。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,vis[105];
char s[105],a[105],ans[105];
bool check(int p){
    if(p<m-1)return 1;
    for(int i=0;i<m;i++)
        if(ans[p-i]!=s[m-1-i])return 1;
    return 0;
}
bool dfs(int p){//核心
    if(p==n)return 1;
    if(ans[p]==0)
    {
        for(int i=0;i<k;i++)
        {
            ans[p]=i+'a';
            if(check(p)&&dfs(p+1))return 1;
        }
        return 0;
    }
    else
    {
        if(vis[p])return dfs(p+1);
        if(check(p)&&dfs(p+1))return 1;
        return 0;
    }
}
int main()
{
    scanf("%d %d %s %s",&n,&k,s,a);
    m=strlen(s);
    int flag=1;
    for(int i=0;i<n-m+1;i++)
        if(a[i]=='1'){
            for(int j=0;j<m;j++){
                if(ans[i+j]==0)ans[i+j]=s[j];
                else if(ans[i+j]!=s[j])flag=0;
            }
            if(!flag)break;
            vis[i+m-1]=1;
        }
    if(flag!=0){
        ans[n]='\0'; 
        if(dfs(0)!=0)cout<<ans;
        else printf("No solution");
    }
    else printf("No solution");
    return 0;//好习惯
}
```
改了很多遍求通过。

---

## 作者：luxiaomao (赞：0)

## [CF54D](https://www.luogu.com.cn/problem/CF54D) 字符串构造题

你说得对，但是为什么这道题有 KMP 的标签啊。

## Problem

要求构造一个字符串 $S$，满足该串长度为 $n$，只出现字母表中前 $k$ 个字母。并且给出一个模式串 $P$，要求在 $S$ 串某些地方必须出现 $P$，其他地方必须不出现 $P$。

## Solution

第一眼看起来确实像要把 KMP 算法的过程倒推，细想其实并没有那么难。

我们先考虑 01 串中为 $1$ 的部分：

显然，对于每个必须出现 $P$ 的地方，我们无脑地把 $P$ 写上去，如果写到一半发现这里已经有了别的字母（为了满足别的“必须出现”需求），不符预期，输出 `No solution`。

这一过程完成之后，我们考虑剩下的为 $0$ 的部分：

- 如果该位置和 $P$ 不匹配，那么符合要求，直接跳过。

- 如果该位置还没被填满，但填了的部分和 $P$ 匹配，那么我们随便找一个还没填的空子，填一个和 $P$ 不匹配的字符。

- 如果该位置已经被填满，并且与 $P$ 匹配，那么没救了，输出 `No solution`。

现在我们可以输出答案了。不过别忘了，有的空可能还没被填上。对于这些空，我们随便输出一个字母即可。

## Code

```cpp
#include<bits/stdc++.h>
#define N 105
using namespace std;

int n,m,lens,k;
char a[N],b[N],s[N];

int main()
{
	scanf("%d%d",&n,&k);
	scanf("%s",b),m = strlen(b);
	scanf("%s",s),lens = strlen(s);
	if(lens+m-1 > n)
		return printf("No solution\n"),0;
	for(int i = 0;i < lens;i++)
		if(s[i] == '1')
			for(int j = 0;j < m;j++)
			{
				if(a[i+j] && a[i+j] != b[j])
					return printf("No solution\n"),0;
				a[i+j] = b[j];			
			}
	for(int i = 0;i < lens;i++)
		if(s[i] == '0')
		{
			int j;
			for(j = 0;j < m;j++)
			{
				if(a[i+j] && a[i+j] != b[j])break;
			}
			if(j < m)continue;
			for(j = 0;j < m;j++)
			{
				if(!a[i+j])
				{
					a[i+j] = b[j]=='a'?'b':'a';
					break;
				}
			}
			if(j == m)
				return printf("No solution\n"),0;
		}
	for(int i = 0;i < n;i++)
		printf("%c",a[i]?a[i]:'a');
	return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## 题目大意：

给你两个数字 $n, k$ 和一个字符串 $p$ 以及一个 $01$ 串，让你构造一个字符串 $s$ 满足几点。

* $|s| = n$。

* $s$ 中只包含前 $k$ 个小写字母。

* 若 $01$ 串第 $i$ 位为 $1$，那 $s$ 从第 $i$ 为开始的一个长 $|p|$ 的子串为 $p$。

* 若 $01$ 串第 $i$ 位为 $0$，那 $s$ 从第 $i$ 为开始的一个长 $|p|$ 的子串不为 $p$。

可以满足输出 $s$，否则输出 `No solution`。

## Solution:

首先满足 $01$ 串中为 $1$ 的条件。

在 $s$ 中，每一个为 $1$ 的位置放个 $p$ 即可，若有冲突即为 `No solution`。

再先满足 $01$ 串中为 $0$ 的条件。

在 $s$ 中，每一个为 $0$ 的位置检查一遍子串是否为 $p$。

有几种情况：

* 完全为 $p$，`No solution` 无疑了。

* 有与 $p$ 不同的位，铁定满足可以跳过。

* 有没填的位，随便填一个不同的即可。

具体细节看代码。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k;
string s, p, q;
int main(){
	cin >> n >> k >> p >> q;
	for(int i = 1; i <= n; i++){
		s = s + '0';
	}
	for(int i = 0; i < q.size(); i++){
		if(q[i] == '1'){
			for(int j = i, k = 0; k < p.size(); j++, k++){
				if(p[k] != s[j] && s[j] != '0'){
					cout << "No solution";
					return 0;
				}
				s[j] = p[k];
			}
		}
	}
	for(int i = 0; i < q.size(); i++){
		if(q[i] == '0'){
			if(i + p.size() > n){
				break;
			}
			int flag = 0;
			for(int j = i, k = 0; k < p.size(); j++, k++){
				if(p[k] != s[j] && s[j] != '0'){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				for(int j = i, k = 0; k < p.size(); j++, k++){
					if(s[j] == '0'){
						if(p[k] == 'a'){
							s[j] = 'b';
						}
						else{
							s[j] = 'a';
						}
						flag = 1;
						break;
					}
				}
				if(flag == 0){
					cout << "No solution";
					return 0;
				}
			}
		}
	}
	for(int i = 0; i < n; i++){
	    if(s[i] == '0'){
	        s[i] = 'a';
	    }
	}
	cout << s;
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

~~KMP好难呀！~~

------------

## 大致思路：
题目告诉了我们一个字符串 $p$ 和坐标 $01$ 字符串 $positions$，要求我们在 $positions$ 字符串中出现 $1$ 的地方加上 $p$ 字符串。乍一看像是个 KMP 模板，其实不然，因为 $n \le 100$！！！暴力就可以切掉这道题，所以，我们先用一个循环依次填入 $p$ 字符串中的第一个数，并将 $vis$ 数组中对应的位置赋值为 $1$。然后，调用 dfs 函数见剩下的字符填入 $ans$ 字符串，同时在填的时候调用 check 函数判断是否与一开始填的第一个字符冲突，也就是没空间，是的话，就返回 ``false``。否则继续递归填字符。



------------
## 警钟敲烂：
如果返回 ``false`` 时，输出一定要注意那个是 ``No solution``，不是 ``No Solution``！！

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m, k;
bool vis[109];
char p[105], positions[105], ans[105];
bool check(int pos)
{
    if (pos < m - 1)
    {
        return 1;
    }
    for (int i = 0; i < m; i++)
    {
        if (ans[pos - i] != p[m - 1 - i])
        {
            return 1;
        }
    }
    return 0;
}
bool dfs(int pos)
{
    if (pos == n)
    {
        return 1;
    }
    if (ans[pos] == 0)
    {
        for (int i = 0; i < k; i++)
        {
            ans[pos] = i + 'a';
            if (check(pos) && dfs(pos + 1))
            {
                return 1;
            }
        }
        return 0;
    }
    else
    {
        if (vis[pos])
        {
            return dfs(pos + 1);
        }
        if (check(pos) && dfs(pos + 1))
        {
            return 1;
        }
        return 0;
    }
}
int main()
{
    memset(ans, 0, sizeof(ans));
    n = read();
    k = read();
    cin >> p;
    m = strlen(p);
    cin >> positions;
    bool b = 1;
    for (int i = 0; i < strlen(positions); i++)
    {
        if (positions[i] == '1')
        {
            for (int j = 0; j < m; j++)
            {
                if (ans[i + j] == 0)
                {
                    ans[i + j] = p[j];
                }
                else if (ans[i + j] != p[j])
                {
                    b = 0;
                }
            }
            if (!b)
            {
                break;
            }
            vis[i + m - 1] = 1;
        }
    }
    if (b)
    {
        ans[n] = '\0';
        if (dfs(0))
        {
            cout << ans;
        }
        else
        {
            cout << "No solution";
        }
    }
    else
    {
        cout << "No solution";
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121169391)

---

## 作者：FwbAway (赞：0)

自己做一个字符串，从一个地方开始判断。

这就是一个 01 字符串罢了，遍历数组，处理没有也不让有的地方有的问题。遇到一个从 0 开始，但是跟 p 完全相同的串的时候，我们循环这个小段，发现第一个不被任何以 1 开头的串覆盖的位置 pos，然后去更改他，即改成一个与这个位置当前字母不一样的字母，如果不能改输出不行好了。

注意满足所有的 1，还不一定满足所有的 0。

对于第二种情况显然不能在这个位置上进行补救了，机会只在第一个情况了，这种情况是 $T[i+j]T[i+j]$ 还没被构造的情况，所以就搞一个不和 $S$ 匹配的字符就行了。

---

