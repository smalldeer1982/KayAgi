# [GCJ 2020 #1A] Pattern Matching

## 题目描述

许多终端使用星号(`*`)表示"任意字符串"，包括空字符串。例如，当列出匹配`BASH*`的文件时，终端可能显示 BASH、BASHER 和 BASHFUL。对于`*FUL`，可能显示 BEAUTIFUL、AWFUL 和 BASHFUL。当列出`B*L`时，可能显示 BASHFUL、BEAUTIFUL 和 BULL。

在本题中，**模式**是仅由大写字母和星号(`*`)组成的字符串，**名称**是仅由大写字母组成的字符串。若模式 $p$ 能通过将每个星号替换为任意字符串（可为空）得到名称 $m$，则称 $p$ 匹配 $m$。注意不同星号可被替换为不同字符串。

给定 $\mathrm{N}$ 个模式，请构造一个长度不超过 $10^{4}$ 的字符串，使其同时匹配所有给定模式；若不存在这样的字符串，则报告无解。

## 说明/提示

样例 #1 中，其他可行解包括 COCOCONUTS 和 ILIKECOCONUTS，但 COCONUTSAREGREAT 和 COCOANUTS 不符合要求。注意同一模式可能在测试用例中重复出现。

样例 #2 无解，故输出 `*`。

以下情况不会出现在测试集 1，但可能出现在测试集 2 或 3：

```
  4
  H*O
  HELLO*
  *HELLO
  HE*
```

可行解包括 HELLO 和 HELLOGOODBYEHELLO，但 OTHELLO 和 HELLOO 不符合。

```
  2
  CO*DE
  J*AM
```

无解，输出 `*`。

```
  2
  CODE*
  *JAM
```

CODEJAM 是可行解之一。

以下情况仅可能出现在测试集 3：

```
  2
  A*C*E
  *B*D*
```

可行解包括 ABCDE 和 ABUNDANCE，但 BOLDFACE 不符合。

```
  2
  A*C*E
  *B*D
```

无解，输出 `*`。

**数据范围**

- $1 \leqslant \mathrm{T} \leqslant 100$
- $2 \leqslant \mathrm{N} \leqslant 50$
- $2 \leqslant \mathrm{P}_{\mathrm{i}}$ 长度 $\leqslant 100$
- 每个 $\mathrm{P}_{\mathrm{i}}$ 仅含大写字母和星号
- 每个 $\mathrm{P}_{\mathrm{i}}$ 至少包含一个大写字母

**测试集 1（5 分，可见判果）**
- 每个 $\mathrm{P}_{\mathrm{i}}$ 仅含一个星号
- 星号必须位于模式开头

**测试集 2（5 分，可见判果）**
- 每个 $\mathrm{P}_{\mathrm{i}}$ 仅含一个星号

**测试集 3（18 分，可见判果）**
- 每个 $\mathrm{P}_{\mathrm{i}}$ 至少含一个星号

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5
*CONUTS
*COCONUTS
*OCONUTS
*CONUTS
*S
2
*XZ
*XYZ```

### 输出

```
Case #1: COCONUTS
Case #2: *```

# 题解

## 作者：qkj_qwq (赞：3)

## 解题思路
注意到，所有字符串长度总和，即 $\mathrm{P_i\times N=5\times10^3}$，是远远小于 $10^4$ 的。所以所有字符串拼起来是完全没有问题的。

我们定义开头为第一个字符到第一个星号之前的串，结尾为最后一个字符到最后一个星号之后的串。那么，如果方案是符合要求的，每一个字符串的开头必须为最长开头的前缀（例如 `ABC*...` 为 `ABCD*...` 的前缀），每一个字符串的结尾必须为最长结尾的后缀（例如 `...*XYZ` 为 `...*WXYZ` 的后缀）。这样是因为开头、结尾没有星号，只能老老实实地抄下来，这样能保证方案符合要求。中间不用管，因为中间的星号可以表示成其他字符串或空串。

那么答案就出来了：最长的开头，加上所有去掉星号的字符串，再加上最长的结尾。~~反正长度不超限，那我也懒得优化了~~

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string dlt(string str)//去掉星号
{
	str.erase(remove(str.begin(),str.end(),'*'),str.end());
	return str;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		int n;
		string st="",ed="",all="";
		bool f=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			string a,now="",noww="";
			cin>>a;
			all+=dlt(a);
			for(int i=0;i<a.size();i++)
				if(a[i]=='*')break;
				else now+=a[i];
			for(int i=a.size()-1;i>=0;i--)
				if(a[i]=='*')break;
				else noww=a[i]+noww;
			if(now!="")//处理开头
			{
				if(st=="")st=now;
				else if(now.size()>st.size())
				{
					if(now.substr(0,st.size())==st)st=now;
					else f=1;
				}
				else if(now.size()<st.size())
				{
					if(st.substr(0,now.size())!=now)f=1;
				}
				else if(now!=st)f=1;
			}
			if(noww!="")//处理结尾
			{
				if(ed=="")ed=noww;
				else if(noww.size()>ed.size())
				{
					if(noww.substr(noww.size()-ed.size(),ed.size())==ed)ed=noww;
					else f=1;
				}
				else if(noww.size()<ed.size())
				{
					if(ed.substr(ed.size()-noww.size(),noww.size())!=noww)f=1;
				}
				else if(noww!=ed)f=1;
			}
		}
		if(f)cout<<"*\n";
		else cout<<st<<all<<ed<<'\n';
	}
	return 0;
}

```

---

