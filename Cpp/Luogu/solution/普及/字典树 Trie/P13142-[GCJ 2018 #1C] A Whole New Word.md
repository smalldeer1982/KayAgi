# [GCJ 2018 #1C] A Whole New Word

## 题目描述

Vincent 和 Desta 是从小一起长大的朋友。今天，Vincent 用一些字母牌向 Desta 展示了 $N$ 个不同的 $L$ 字母单词。每个字母牌上有一个大写英文字母和一个 $1$ 到 $L$ 之间的数字。一个单词由 $L$ 个数字分别为 $1$ 到 $L$ 的字母牌按顺序拼成。（Vincent 的单词不一定是真正的英文单词。）

例如，如果 Vincent 有 $N = 3$ 个长度为 $L = 4$ 的单词，分别是 $\{\text{CAKE}, \text{TORN}, \text{SHOW}\}$，那么 Vincent 必须向 Desta 展示如下内容：

![](https://cdn.luogu.com.cn/upload/image_hosting/ve1i8p4m.png)

Desta 觉得造单词一定很简单，他想用上述规则造出一个新的单词，并且不能和 Vincent 已有的单词重复。然而，Desta 没有自己的字母牌，他只能使用 Vincent 的字母牌。

例如，如果 Vincent 的单词如上例所示，Desta 可以拼出新的单词，如 $\text{CORN}$、$\text{SAKE}$ 或 $\text{CHRE}$（Desta 造的单词也不一定是真正的英文单词）。每个例子如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/0rhou6na.png)

注意，上图的三行是独立的。Desta 只需要造出一个新单词即可。

但是，在上述例子中，Desta 不能拼出 WAKE，因为没有数字为 $1$ 的 $\text W$ 字母牌。也不能拼出 coo，因为长度不对。

注意，有时 Desta 可能无法造出新单词。例如，如果 Vincent 只有一个单词，那么 Desta 无法造出任何新单词。又如，如果 Vincent 的单词为 $\{\text{AA}, \text{AB}, \text{BA}, \text{BB}\}$，那么 Desta 能拼出的所有单词都已在 Vincent 的单词列表中。

请帮助 Desta 选择一个他能用 Vincent 的字母牌拼出的新单词，或者指出无法拼出新单词。

## 说明/提示

**样例解释**

注意，最后两个样例不会出现在测试集 1 中。

样例 1 中，只能用 Vincent 的字母牌拼出 A、B、C、D 这四个单词，但这些单词都已在 Vincent 的单词列表中，所以 Desta 不能选择它们。

样例 2 中，有 $12$ 个可能的新单词可以拼出，其中之一是 $\text{WA}$。

样例 3 已在题目描述中解释，Desta 无法拼出新单词。

样例 4 已在题目描述中解释，也可以输出如 $\text{SAKF}$ 等其它答案。

样例 5 也可以输出如 $\text{TRAPJAM}$ 等其它答案。

**数据范围**

- $1 \leqslant T \leqslant 100$。
- Vincent 的单词互不相同。

**测试集 1（11 分，可见）**

- $1 \leqslant N \leqslant 26^{2}$。
- $1 \leqslant L \leqslant 2$。

**测试集 2（17 分，隐藏）**

- $1 \leqslant N \leqslant 2000$。
- $1 \leqslant L \leqslant 10$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
4 1
A
B
C
D
4 2
WW
AA
SS
DD
4 2
AA
AB
BA
BB
3 4
CAKE
TORN
SHOW
5 7
HELPIAM
TRAPPED
INSIDEA
CODEJAM
FACTORY```

### 输出

```
Case #1: -
Case #2: WA
Case #3: -
Case #4: CORN
Case #5: HOLIDAY```

# 题解

## 作者：qkj_qwq (赞：3)

## 解题思路

暴搜。反正数据水。

先把每个字符串都记录一遍，以及每个位上是否有这个字符也记录一遍。

暴搜时，把当前位的所有可能的字符都搜一遍，如果这个字符是字母牌的字符，则进入下一层搜索。记得搜到答案就立刻停止搜索。

若未停止搜索，则最坏情况（即同一位的字母牌都不同）要搜索 $10^{10}$ 次，这样 $15.00\text{s}$ 也救不了你。若立刻停止搜索，则每组数据如果有解，最坏情况要搜到最后（当 $t=L+1$ 时）一共 $N+1$ 次。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[20][36],m;
map<string,bool>p;
string ans;
bool dfs(int t,string now)
{
	if(t==m+1)
	{
		if(!p[now]){ans=now;return 1;}//搜到答案立刻停止搜索
		return 0;
	}
	for(int i=0;i<26;i++)
		if(a[t][i]&&dfs(t+1,now+char(i+'A')))return 1;//搜到答案立刻停止搜索
    return 0;
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
		memset(a,0,sizeof a);
		p.clear();
		int n;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			int ss=0;
			string s;
			cin>>s;
			p[s]=1;
			for(int j=0;j<m;j++)
				a[j+1][s[j]-'A']++;
		}
		ans="-";
		dfs(1,"");
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：lkjlkjlkj2012 (赞：2)

update2025.7.11：修正数学推导。
### 思路
来讲一个随机化做法。我们每次随机拼出一个单词，判断它是否在已有单词中。设总共有 $P$ 个可能拼出的单词，则每次失败概率为 $\frac{N}{P}$。设我们随机 $k$ 次，那么假设存在解，则找到的概率 $C=1-(\frac{N}{P})^k$。由于 $N\le 2000$，所以 $\frac{N}{P}\le\frac{2000}{2001}$（$n\in\mathbb{N}$，$26^L\in\mathbb{N}$）。可得当存在解时，$C=1-(\frac{N}{P})^k\ge 1-(\frac{2000}{2001})^k$。取 $k=10^4$ 即可通过。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,l;
string s[2005];
int main()
{
    cin>>t;
    for(int ti=1;ti<=t;ti++)
    {
        cout<<"Case #"<<ti<<": ";
        cin>>n>>l;
        for(int i=1;i<=n;i++)
            cin>>s[i];
        bool flag=false;
        for(int x=1;x<=10000;x++)
        {
            string tmp;
            for(int i=0;i<l;i++)
                tmp+=s[rand()%n+1][i];
            bool fl=false;
            for(int i=1;i<=n;i++)
                if(tmp==s[i])
                {
                    fl=true;
                    break;
                }
            if(!fl)
            {
                cout<<tmp<<endl;
                flag=true;
                break;
            }
        }
        if(!flag)
            cout<<"-"<<endl;
    }
}
```

---

