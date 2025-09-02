# [GCPC 2024] Headline Heat

## 题目描述

德国 ICPC 场景被广泛认为是最具竞争力的之一。
至少，这是我们对学生们说的。
无数的竞争关系交织成一张复杂的网络，充满了嫉妒、绝望、荣耀与胜利，这些都体现在两块不断变换的记分牌——Winter Contest 和 GCPC 上。
尽管一代又一代的参赛者往往会忘记前辈们的恩怨，但我们教练，作为永恒的连续性灯塔，保留着那些早已被遗忘队伍之间的琐碎冲突。
为了追求完美的平衡，我们以愤怒的呐喊在社交媒体上抗议每一篇不公正的新闻报道，表达我们对教练职责的奉献。
也就是说，如果一篇新闻报道中出现了某所大学的对手大学名称的次数多于该大学本身的名称次数，那么该大学的教练就会生气。

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/81caxzmt.png)

Winter Contest 2024 前十名记分牌。
:::

为了平息这片愤怒之海中的波澜，一位新任权威被指派负责校对 GCPC 和 Winter Contest 的媒体报道，以防止报道不均。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 1 4
hpi
fau
kit
1 3
kit destroys hpi at wintercontest
gcpc is great
team moshpit from hpi beats kit teams
whats the abbreviation for university of erlangen nuremberg```

### 输出

```
yes
yes
no
yes```

## 样例 #2

### 输入

```
6 3 5
uds
cu
tum
rwth
uni ulm
uni
4 1
2 5
1 3
last gcpc rwth had a team in top ten two places behind tum
who is team debuilding from constructor university bremen
top ten teams last year are from kit cu uds hpi tum and rwth
uni ulm cu uni ulm
sunday alright lets go```

### 输出

```
no
yes
no
no
yes```

# 题解

## 作者：Crazyouth (赞：0)

## 分析

我们考虑这样一个算法：

对所有大学名称建立 AC 自动机，但是每一个状态（即结点）上面存一个长度为 $m$ 的数组。对于每一条边 $i$，设它连接 $u,v$，那么就在串 $u$ 对应的状态上的数组第 $i$ 位加一，$v$ 的第 $i$ 位减一，这样一个连通块出现次数相等就等价于在处理询问的时候访问到的状态上的数组的每一位之和都是 $0$。

不难发现这个做法复杂度 $O(m\sum|t|)$，过不了。但是有一种东西叫做和哈希，就是在星战用到的那个算法。我们为每一个下标 $i$ 赋一个随机权值 $r_i$，在该下标加一时改为加 $r_i$，减法同理。那么数组全 $0$ 就等价于这所有哈希值和为 $0$，冲突概率是很小的。

复杂度 $O(m+\sum|t|)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string s;
int r[1000010],pos[1000010];
struct node
{
	int son[27];
	unsigned long long hs;
	int fail;
	int idx;
	node()
	{
		memset(son,0,sizeof son);
		hs=fail=idx=0;
	}
}tr[1000010];
int tot=0,icnt=0;
unsigned long long ans=0;
void insert(int idx)
{
	int u=0;
	for(int i=0;i<s.size();i++)
	{
		int &nxt=tr[u].son[s[i]&31];
		if(!nxt) nxt=++tot;
		u=nxt;
	}
	pos[idx]=u;
}
void build()
{
	queue<int> q;
	for(int i=0;i<27;i++) if(tr[0].son[i]) q.push(tr[0].son[i]);
	while(q.size())
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<27;i++)
		{
			if(tr[u].son[i])
			{
				tr[tr[u].son[i]].fail=tr[tr[u].fail].son[i];
				tr[tr[u].son[i]].hs+=tr[tr[tr[u].fail].son[i]].hs;
				q.push(tr[u].son[i]);
			}
			else tr[u].son[i]=tr[tr[u].fail].son[i];
		}
	}
}
void query()
{
	int u=0;
	for(int i=0;i<s.size();i++)
	{
		u=tr[u].son[s[i]&31];
		ans+=tr[u].hs; 
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	mt19937_64 rnd(19260817);
	int n,m,k;
	cin>>n>>m>>k;
	getline(cin,s);
	for(int i=1;i<=n;i++)
	{
		getline(cin,s);
		insert(i);
	}
	for(int i=1;i<=m;i++)
	{
		r[i]=rnd();
		int u,v;
		cin>>u>>v;
		tr[pos[u]].hs+=r[i];
		tr[pos[v]].hs-=r[i];
	}
	build();
	getline(cin,s);
	while(k--)
	{
		getline(cin,s);
		ans=0;
		query();
		cout<<(ans?"no":"yes")<<'\n';
	}
}

---

