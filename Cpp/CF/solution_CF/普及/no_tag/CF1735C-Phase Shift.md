# Phase Shift

## 题目描述

There was a string $ s $ which was supposed to be encrypted. For this reason, all $ 26 $ lowercase English letters were arranged in a circle in some order, afterwards, each letter in $ s $ was replaced with the one that follows in clockwise order, in that way the string $ t $ was obtained.

You are given a string $ t $ . Determine the lexicographically smallest string $ s $ that could be a prototype of the given string $ t $ .

A string $ a $ is lexicographically smaller than a string $ b $ of the same length if and only if:

- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter, that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test case, we couldn't have the string "a", since the letter a would transit to itself. Lexicographically the second string "b" is suitable as an answer.

In the second test case, the string "aa" is not suitable, since a would transit to itself. "ab" is not suitable, since the circle would be closed with $ 2 $ letters, but it must contain all $ 26 $ . The next string "ac" is suitable.

Below you can see the schemes for the first three test cases. The non-involved letters are skipped, they can be arbitrary placed in the gaps.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735C/40f1e4167acecb5e201b23a56898bccbc525d101.png)

## 样例 #1

### 输入

```
5
1
a
2
ba
10
codeforces
26
abcdefghijklmnopqrstuvwxyz
26
abcdefghijklmnopqrstuvwxzy```

### 输出

```
b
ac
abcdebfadg
bcdefghijklmnopqrstuvwxyza
bcdefghijklmnopqrstuvwxyaz```

# 题解

## 作者：minecraft_herobrine (赞：6)

题意：一个字符串 $S$ 被加密为了 $T$，加密方式为建立一个映射表，将每个小写字母映射到另一个小写字母。给定 $T$，求字典序最小的 $S$，映射表只能将 $26$ 个小写字母全串起来，不允许出现大小小于 $26$ 的闭环（参考样例 $2$）。

考虑建立最优状态下的映射表。因为是要字典序最小，贪心将第一次出现位置靠前的字符需要映射到最小的字符上。从前往后找若发现一个未出现过的字符，就从字母 $a$ 开始找能够映射的字符，对每个字符判断是否会出现环，如果发现会出现长度小于 $26$ 的环就不可行直到找到当前不构成环或构成长度等于 $26$ 的环的字符即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
char s[MAXN];
map<char,char> mp;
bool vis[130];
bool v[130];
bool check(char a,char b)
{
	int i;
	memset(v,false,sizeof(v));
	v[a]=true;
	for(i=1;;i++)
	{
		if(!b) return false;//映射表断了，显然还没构成环
		if(v[b]) break;//查到环就判断环的大小
		v[b]=true;
		b=mp[b];//顺着已建立的映射表跳
	}
	return i<26;
}
int main()
{
	int T,n,i,j;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		scanf("%s",s+1);
		mp.clear();
		memset(vis,false,sizeof(vis));
		for(i=1;i<=n;i++)
		{
			if(mp[s[i]]!=0) continue;
			for(j=97;j<123;j++)
			{
				if(mp[s[i]]!=0) break;
				if(!vis[j])
				{
					if(check(s[i],j)) continue;//发现小于26的环
					else
					{
						mp[s[i]]=j;
						vis[j]=true;
						break;
					}
				}
			}
		}
		for(i=1;i<=n;i++) printf("%c",mp[s[i]]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：EclipSilvia (赞：2)

## 题目

现在有一个仅包含小写字母的字符串 $s$ 被加密了。很遗憾，你并不知道这个串是什么。但是通过某种奇妙的方式，你得知了这个串的加密方式：将 $26$ 个英文字母排列成一个环（很遗憾，你仍然不知道它们排列的顺序），然后将 $s$ 中的每个字符都替换成环中其顺时针方向的下一个字符。

给出 $ss$ 被加密之后得到的字符串 $t$，你需要求出所有可能的 $s$ 中，字典序最小的那一个。

**提示**:可以证明，对于任意字符串 $t$，都至少存在一个可以加密为 $t$ 的字符串 $s$。我们称字符串 $a$ 的字典序小于 $b$，当且仅当 $a$ 与 $b$ 第一个不同的位置上 $a$ 的字符更小，或者 $a$ 是 $b$ 的前缀。
## 输入

第一行一个正整数 $t$ 表示测试数据的组数。
对于每组数据，第一行一个正整数 $n$ 表示串 $t$ 的长度，第二行给出 $t$。
## 输出

对于每组数据，输出一个字符串 $s$ 表示 $t$ 的原串中字典序最小的那一个。

**简化题意：**  
现有一个 $26$ 个小写字母形成的环，将一个字符串加密，加密规则为将字母变换为环中该字母顺时针的下一个字母。
现给出加密后的字符串，要求解密出字典序最小的字符串  

**分析：**  
对于每一个字母 $tt$，按照字典序找到它在环中的前一个字母 $ss$，形成 $ss$ 到 $tt$ 的一条边。   
注意：如果当前字母 $tt$ 与找到的字母 $ss$ 已经连通，那么不能对 $ss$ 到 $tt$ 连边，因为这样会形成环。只有在已经有 $25$ 条边时，才可以连接成一个环。  
我们用并查集来维护已经连接的字母的信息。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 27;
int cnt,f[maxn],pre[maxn],nxt[maxn];
/*
pre[i]表示i在环中的前一个字母
nxt[i]表示i在环中的后一个字母
*/
inline int read(){int a=0,b=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') b=-1;ch=getchar();}while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}return a*b;}
int find(int x) {return f[x]==x?x:f[x]=find(f[x]);}
void calc(int x)
{
	//按照字典序找它在环中的前一个字母 
	for(int i=1; i<=26; i++)
	{
		if(i == x) continue; //前一个字母不可能为本身
		if(!nxt[i])
		{//当i所代表的字母后一个字母没有确定时 
			if(cnt != 25 && find(i) == find(x)) continue; //没有25条连边，并且i与x本身已经连通，那么不能i到x连边
			++cnt;
			nxt[i] = x;
			pre[x] = i;
			f[find(i)] = find(x); 
			break;
		} 
	}
}
signed main()
{
	int T = read();
	while(T--)
	{	
		cnt = 0;//cnt表示已经连接的边的条数 
		int n = read();
		string t;
		cin >> t;
		for(int i=1;i<=26;i++)
		{
			f[i] = i;
			pre[i] = 0;
			nxt[i] = 0;
		}
		for(int i=0;i<t.size();i++)
		{
			int x = t[i] - 'a' + 1;
			if(!pre[x]) calc(x);//如果当前字母没有找到它在环中的前一个字母，那么就查找
			putchar(pre[x] + 'a' - 1); 
		}
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：ScottSuperb (赞：0)

## 解法分析
贪心加模拟。对于给定的目标串，为了使字典序最小，我们在确定每个字母的源时从 $\texttt a$ 开始检查。确定一个字母的源有两个规则：

1. 先前已确定过该字母的源；
1. 候选的源满足未被使用过、不同于该字母、选择该源后不会过早地产生环（即产生的环中少于 $26$ 个字母）三个条件。

那么基于这两个规则，我们就可以写出代码了。其中检查是否过早产生环的函数中，先检查已使用的源的个数 $cnt$ 是否等于 $25$ 即是否不早，再采用迭代方式向上层层追溯是否出现过该候选源或该字母即是否有环。
## 代码
读写函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

char s, ans[100005], src['z' + 1], sr;
int v['z' + 1], cnt;

inline bool check(char& c, char& c2) {
  if (cnt == 25) return false;
  for (char ch = src[c]; ch; ch = src[ch])
    if (ch == c || ch == c2) return true;
  return false;
}

int main() {
  int t = read(), n;
  while (t--) {
    n = read(), cnt = 0;
    for (char i = 'a'; i <= 'z'; ++i) src[i] = v[i] = 0;
    for (int i = 0; i < n; ++i) {
      s = getchar();
      if (src[s])
        ans[i] = src[s];
      else {
        for (sr = 'a'; v[sr] || s == sr || check(sr, s); ++sr)
          ;
        ans[i] = sr, src[s] = sr, v[sr] = 1, ++cnt;
      }
    }
    for (int i = 0; i < n; ++i) putchar(ans[i]);
    putchar('\n');
  }
  return 0;
}
```

---

