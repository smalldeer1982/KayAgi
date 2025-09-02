# Fixed Prefix Permutations

## 题目描述

You are given $ n $ permutations $ a_1, a_2, \dots, a_n $ , each of length $ m $ . Recall that a permutation of length $ m $ is a sequence of $ m $ distinct integers from $ 1 $ to $ m $ .

Let the beauty of a permutation $ p_1, p_2, \dots, p_m $ be the largest $ k $ such that $ p_1 = 1, p_2 = 2, \dots, p_k = k $ . If $ p_1 \neq 1 $ , then the beauty is $ 0 $ .

The product of two permutations $ p \cdot q $ is a permutation $ r $ such that $ r_j = q_{p_j} $ .

For each $ i $ from $ 1 $ to $ n $ , print the largest beauty of a permutation $ a_i \cdot a_j $ over all $ j $ from $ 1 $ to $ n $ (possibly, $ i = j $ ).

## 样例 #1

### 输入

```
3
3 4
2 4 1 3
1 2 4 3
2 1 3 4
2 2
1 2
2 1
8 10
3 4 9 6 10 2 7 8 1 5
3 9 1 8 5 7 4 10 2 6
3 10 1 7 5 9 6 4 2 8
1 2 3 4 8 6 10 7 9 5
1 2 3 4 10 6 8 5 7 9
9 6 1 2 10 4 7 8 3 5
7 9 3 2 5 6 4 8 1 10
9 4 3 7 5 6 1 10 8 2```

### 输出

```
1 4 4 
2 2 
10 8 1 6 8 10 1 7```

# 题解

## 作者：World_Creater (赞：8)

考虑一个简单贪心：如果我们要让答案尽可能大，首先要求最终算出来排列第一位是 $1$，再第二位是 $2$，再考虑第三位是 $3$ 等等。

假设现有一个排列 $p=\{4,5,1,3,2\}$，如果我们找到了一个排列 $q$ 与之配对，根据题意，如果要最大化答案，我们先要使得 $q$ 的第 $4$ 位是 $1$，再使得 $q$ 的第 $5$ 位是 $2$，再考虑 $q$ 的第 $1$ 位是 $3$ 等等。

上述寻找 $q$ 的过程不太好解决，我们考虑求出 $q$ 的逆排列 $q'$，满足 $q'_{q_i}=i$，这样子，如果我们要找 $q$ 的第 $4$ 位为 $1$，在逆排列 $q'$ 中就表现为第 $1$ 位为 $4$，第 $5$ 位是 $2$ 就对应逆排列中第 $2$ 位是 $5$。

发现最终在逆排列上表现为一个前缀查找的形式，可以使用字典树贪心解决。

时间复杂度 $\mathcal{O}(nm)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int a[50005][13];
struct trie{
	int tree[500005][13];
	int cnt;
	void reset()
	{
		for(int i=0;i<=cnt;i++) memset(tree[i],0,sizeof(tree[i]));
		cnt=0;
	}
	void insert(int a[])
	{
		int p=0;
		for(int i=1;i<=m;i++)
		{
			if(tree[p][a[i]]==0) tree[p][a[i]]=++cnt;
			p=tree[p][a[i]];
		}
	}
	int find(int a[])
	{
		int p=0,cnt=0;
		for(int i=1;i<=m;i++)
		{
			int x=a[i];
			if(tree[p][x]!=0)
			{
				cnt++;
				p=tree[p][x];
			}
			else return cnt;
		}
		return cnt;
	}
}T;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cin>>a[i][j];
			}
			int b[15];
			for(int j=1;j<=m;j++)
			{
				b[a[i][j]]=j;//求出逆排列
			}
			T.insert(b);
		}
		for(int i=1;i<=n;i++)
		{
			cout<<T.find(a[i])<<" ";//在字典序中贪心查找
		}
		T.reset();
		cout<<"\n";
	}
}
```

---

## 作者：LKY928261 (赞：4)

考虑互逆的排列 $p$ 和 $q$（即，满足 $\forall i\in[1,m],q_{p_i}=i$），此时 $p\cdot q$ 的美观度取最大值 $m$。在已知排列 $q$ 的情况下，能够求出唯一的排列 $p$，若再加入另一个排列 $r$，注意到题目中排列的美观度是最长的满足 $a_i=i$ 的前缀长度， $r\cdot q$ 的美观度即为 $p$ 和 $r$ 最长公共前缀长度。

于是，先对每个排列 $a_j$ 求逆，然后枚举 $a_i$，与所有 $a_j$ 尝试匹配，匹配到的最大长度即为答案。

但是这样显然会超时。由于只需要前缀长度，考虑建一颗 trie 树，先将所有 $a_j$ 的逆排列加入，再对每个 $a_i$ 进行匹配。

复杂度 $O(nm)$。

[赛时 AC 代码](https://codeforces.com/contest/1792/submission/190363330)

---

## 作者：ningago (赞：3)

看个样例：

> 3 4 9 6 10 2 7 8 1 5

如果他的答案为 $3$，则代表着：存在一个排列，使得第 $3$ 位为 $1$，且第 $4$ 位为 $2$，且第 $9$ 位为 $3$。

所以说考虑维护**第 $i$ 位为 $j$** 的集合。

对于每个排列，考虑枚举他的答案，每次相当于将对应的集合交起来，判断是否不为空。

使用 bitset 维护集合，复杂度是 $O(\dfrac{n^2m}{w})$ 的。

实际测试时间 $\leq 1s$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>

#define N 50010

std::bitset <N> bs[11][11],tmp;
int T;
int n,m;
int mp[N][11];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= m;j++)
			{
				scanf("%d",&mp[i][j]);
				bs[j][mp[i][j]].set(i);
			}
		}
		for(int i = 1;i <= n;i++)
		{
			tmp.set();
			int ans = 0;
			for(int j = 1;j <= m;j++)
			{
				tmp = tmp & bs[mp[i][j]][j];
				if(tmp.any())
					ans = j;
				else
					break;
			}
			printf("%d ",ans);
		}
		putchar('\n');
		for(int i = 1;i <= m;i++)
			for(int j = 1;j <= m;j++)
				bs[i][j].reset();
	}
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

来点低复杂度无 Trie 做法。

若 $p\cdot q$ 的美丽度为 $k$，则 $\forall i\le k,q_{p_i}=i$。

这个比较难维护，令 $p'$ 为 $p$ 的“逆排列”且 $p'_{p_i}=i$。

若 $p\cdot q$ 的美丽度为 $k$，则 $\forall i\le k,q'_{q_{p_i}}=q'_i=p_i$，即 $\operatorname{LCP}(p,q')=k$。

令 $p_{[j]}$ 表示 $p$ 长度为 $j$ 的前缀。 

令 $S_j=\{a_{i_{[j]}}'\}$，对每个 $a_i$ 找到最大的 $k$ 使得 $\exists j,\operatorname{LCP}(a_i,a_j')=k$ 即 $a_{i_{[k]}}\in S_k$。

此时最大的 $k$ 即为 $a_i$ 的答案。用 `set<vector<int>>` 维护 $S_j$。

复杂度 $O(nm^2\log n)$。题解区最短解。

代码（C++20）：
```cpp
#include <set>
#include <vector>
#include <cstdio>
using namespace std;
int T, n, m, p[20], a[50050][20];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        set<vector<int>> s[20];
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
                scanf("%d", &a[i][j]), p[a[i][j]] = j;
            for (int j = 1; j <= m; ++j)
                s[j].emplace(p + 1, p + j + 1);
        }
        for (int i = 1, q; i <= n; ++i)
        {
            q = 0;
            for (int j = m; j; --j)
                if (s[j].contains(vector<int>(a[i] + 1, a[i] + j + 1)))
                {
                    q = j;
                    break;
                }
            printf("%d ", q);
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：__Aaaaaaaa (赞：1)

在群里看到有大佬用 hash 乱搞过去的，打比赛时我用的是字典树。

人话版题面：  
对于每个序列 $a_i$，求最大的 $k(0\leqslant k\leqslant n)$ 使得存在序列 $a_j$ 满足 $a_j$ 的第 $a_{i,c}$ 个数等于 $c (1\leqslant c\leqslant k)$。

那么很明显，对于每个 $a_i$ 我们可以生成一个序列 $pos$，使  $\mathit{a}_{i, \mathit{pos}_{j}} = j$，我们只需要对于每个 $a_i$ 在所有 $pos$ 中找到前缀匹配最长的 $pos$ 即可，先在 trie 里面存入所有的 $pos$，然后对于每个 $a_i$ 一一匹对即可。

时间复杂度是线性。
### Don't talk much:
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N=5e4+10,M=5e5+10;
int son[M][10],idx=1;
int n,m;
void clear(){
	for(int i=1;i<=idx;i++){
		for(int j=0;j<10;j++)
			son[i][j]=0;
	}
	idx=1;
}
void insert(int a[]){
	int u=1;
	for(int i=1;i<=n;i++){
		int x=a[i];
		if(!son[u][x])
			son[u][x]=++idx;
		u=son[u][x];
	}
}
inline int read(){
	int x=0;
	char ch=getchar();
	bool flag=false;
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			flag=true;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	if(flag)return -x;
	return x;
}
int a[N][12];
int pos[12];
int main(){
	int T;
	T=read();
	while(T--){
		m=read(),n=read();
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++)
				a[i][j]=read();
		}
		for(int p=1;p<=m;p++){
			for(int i=1;i<=n;i++)
				pos[i]=0;
			for(int i=1;i<=n;i++)
				pos[a[p][i]]=i;
			insert(pos);
		}
		for(int p=1;p<=m;p++){
			for(int i=1,u=1;i<=n;i++){
				if(!son[u][a[p][i]]){
					printf("%d ",i-1);
					break;
				}
				else
					u=son[u][a[p][i]];
				if(i==n)
					printf("%d ",n);
			}
		}
		puts("");
		clear();
	}
	return 0;
}
```

---

## 作者：masonpop (赞：0)

提供一个乱搞做法，能通过现有数据。思路十分暴力，跑的也很慢，仅供参考。

首先考虑 $r$ 数组美观的条件，即 $q_{p_i}=i$。那么，我们就是要构造一个 $q$，使得其尽可能多的满足下列条件：$q$ 的第 $p_i$ 位是 $i$。

也就是说，我们可以把满足形如“第 $a$ 位的值是 $b$”的数组看成一个集合，然后从小到大枚举 $i$，看当前所有集合的交是否为空集。

这种集合操作显然用 bitset 维护。用一个二维 bitset 数组维护这种条件。复杂度 $O(\frac{n^2m}{w})$。看似不可思议但是跑过去了。[代码](https://codeforces.com/contest/1792/my)。

---

## 作者：loser_seele (赞：0)

不难发现可以转换问题，将乘积转化为一个数与所有数的逆排列的 LCS 问题，因为显然这是等价的，其他题解已经解释过了。

于是实际上这里要求的是多个子串 LCS 问题，观察到数据范围很小，完全可以考虑暴力将每个串的所有子串丢进一个哈希表里，然后枚举 LCS 长度，用哈希值判一下是否有两个前缀哈希值相同即可。

时间复杂度 $ \mathcal{O}(nm^2) $，可以通过。不建议用太小的模数，建议双哈希。

代码：

[提交记录](https://codeforces.com/contest/1792/submission/192996115)，不知道为什么交不上去。

---

