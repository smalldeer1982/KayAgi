# [GCPC 2024] Copycat Catcher

## 题目描述

你所在的大学最近成立了“研究生代码抄袭控制（GCPC）”项目，以应对计算机科学作业批改者日益增长的工作量。目前，批改者需要人工检查作业代码是否存在抄袭。GCPC 的目标是通过自动执行抄袭检查，简化批改者的这部分工作。

![](https://cdn.luogu.com.cn/upload/image_hosting/dmrh1qay.png)

:::align{center}
一个抄袭检测键盘
:::

代码由用空格分隔的若干“记号”组成。记号是由字母、数字和括号组成的字符串。如果一个记号仅由单个字母（大小写均可）组成，则它是代码中的变量。

GCPC 希望抄袭检测器能够将查询代码片段与参考代码进行比较。具体来说，它应当检查每个查询是否可以通过从参考代码中选取一段连续的记号，并对变量进行一致性重命名后得到。

变量的一致性重命名指：同一个变量的所有出现都被重命名为同一个变量，并且不同的变量不会被重命名为同一个变量。

GCPC 要求你开发这个抄袭检测器。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
9
for i in range(10) do print i j end
4
3
print j i
2
do print
6
k in range(10) do print k
6
k in range(10) do print j```

### 输出

```
yes
yes
yes
no
```

## 样例 #2

### 输入

```
5
i is i times j
7
5
i is i times j
5
a is a times b
5
j is j times c
5
a is i times j
5
j is i times j
5
0 is 0 times j
5
i is i times i
```

### 输出

```
yes
yes
yes
no
no
no
no
```

## 样例 #3

### 输入

```
5
A 1 ( ) b
4
2
b 2
2
b 1
3
1 ) (
5
a 1 ( ) F
```

### 输出

```
no
yes
no
yes
```

# 题解

## 作者：Crazyouth (赞：0)

## 分析

这种字符串题我们可以直接看出要用哈希，但是这个字母可以更改的限制很难办，所以我们考虑根据题意进行一些模拟。

首先我们枚举每一个单词判断能否作为某次询问的开始单词，接着把母串在这个单词之后的变量按照扫到的顺序定义为“第一个字母”、“第二个字母”……这样一来，我们只需要把每个询问串也按从左到右扫到的顺序把变量名定义为“第一个字母”、“第二个字母”……就可以直接进行哈希比较。这里我的哈希使用了快速幂所以总复杂度 $O(nq\log n)$，如果预处理哈希底数的每一个 $1\sim n$ 的幂次可以做到 $O(nq)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244853;
int hsh[4010],vis[4010],str[2010][4010],ans[2010],used[200],snum[4010],pos[2010],nhs[2010],sz[2010];
string s;
int qpow(int b,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=ret*b%mod;
		b=b*b%mod;
		p>>=1;
	}
	return ret;
}
inline void gethash(int st)
{
	for(int i=0;i+st<s.size();i++)
	{
		if(i)
		hsh[i]=hsh[i-1];
		else
		hsh[i]=0;
		hsh[i]+=snum[i+st]*qpow(200,i)%mod;
		hsh[i]%=mod;
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string t;
		cin>>t;
		pos[i]=s.size();
		if(t.size()==1&&isalpha(t[0]))
		{
			vis[s.size()]=t[0];
			t='|';
		}
		s+=t+'#';
	}
	int q;
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int len,acnt=0,lcnt=0;
		cin>>len;
		memset(used,0,sizeof used);
		for(int j=1;j<=len;j++)
		{
			string t;
			cin>>t;
			if(t.size()==1&&isalpha(t[0]))
			{
				if(!used[t[0]]) used[t[0]]=++acnt;
				str[i][++lcnt]=used[t[0]]+127;
			}
			else
			{
				for(int k=0;k<t.size();k++)
				str[i][++lcnt]=t[k];
			}
			str[i][++lcnt]='#';
		}
		sz[i]=lcnt;
		for(int j=lcnt;j;j--) nhs[i]=nhs[i]*200+str[i][j],nhs[i]%=mod;
	}
	for(int i=1;i<=n;i++)
	{
		memset(used,0,sizeof used);
		int acnt=0;
		for(int j=pos[i];j<s.size();j++)
		{
			if(vis[j])
			{
				if(!used[vis[j]]) used[vis[j]]=++acnt;
				snum[j]=used[vis[j]]+127;
			}
			else snum[j]=s[j];
		}
		gethash(pos[i]);
		for(int j=1;j<=q;j++) if(sz[j]-1<s.size()&&nhs[j]==hsh[sz[j]-1]) ans[j]=1;
	}
	for(int i=1;i<=q;i++) cout<<(ans[i]?"yes\n":"no\n");
}

---

