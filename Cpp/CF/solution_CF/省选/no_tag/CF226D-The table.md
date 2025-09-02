# The table

## 题目描述

Harry Potter has a difficult homework. Given a rectangular table, consisting of $ n×m $ cells. Each cell of the table contains the integer. Harry knows how to use two spells: the first spell change the sign of the integers in the selected row, the second — in the selected column. Harry's task is to make non-negative the sum of the numbers in each row and each column using these spells.

Alone, the boy can not cope. Help the young magician!

## 样例 #1

### 输入

```
4 1
-1
-1
-1
-1
```

### 输出

```
4 1 2 3 4 
0 
```

## 样例 #2

### 输入

```
2 4
-1 -1 -1 2
1 1 1 1
```

### 输出

```
1 1 
1 4 
```

# 题解

## 作者：szh_AK_all (赞：3)

在决斗中通过了此题。

由于 $n,m\le 100$ 且 $|a_i|\le 100$，所以在初始情况下所有数的总和是不超过 $-10000$ 的。而每次操作一行或者一列，是将这一行或者这一列的权值和 $sum$ 变为 $-sum$，那么当 $sum\ge 0$ 时，这样操作显然是不优的；当 $sum<0$ 时，一次操作可以让所有数的和增加 $-2\times sum$，因为 $sum<0$，所以 $sum\le -1$，从而得到 $-2\times sum\ge 2$。

也就是说，每一次不劣的操作都至少可以让最终数字和增加 $2$，由于最多只需要增加 $10000$，所以最多需要进行 $5000$ 次操作。而每次进行操作可以用 $O(n\times m)$ 的时间来判定，最终时间复杂度不会爆掉。

需要注意的是，最终操作顺序是无关紧要的，所以每一行或者每一列最多进行一次操作，且进行两次操作等于不操作。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105][105];
int h[105], l[105], ph[105], pl[105];
int n, m;

int ch() {
	int wei = -1;
	for (int i = 1; i <= n; i++) {
		int sum = 0;
		for (int j = 1; j <= m; j++)
			sum += a[i][j];
		if (sum < 0)
			wei = i;
	}
	if (wei != -1) {
		h[wei] ^= 1;
		for (int j = 1; j <= m; j++)
			a[wei][j] *= -1;
		return 1;
	}
	return 0;
}

int cl() {
	int wei = -1;
	for (int j = 1; j <= m; j++) {
		int sum = 0;
		for (int i = 1; i <= n; i++)
			sum += a[i][j];
		if (sum < 0)
			wei = j;
	}
	if (wei != -1) {
		l[wei] ^= 1;
		for (int i = 1; i <= n; i++)
			a[i][wei] *= -1;
		return 1;
	}
	return 0;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	while (ch() || cl()) {//每次操作直到不能操作为止
		int tt;
	}
	int hl = 0, ll = 0;
	for (int i = 1; i <= max(n, m); i++) {
		if (h[i])
			ph[++hl] = i;
		if (l[i])
			pl[++ll] = i;
	}
	cout << hl << " ";
	for (int i = 1; i <= hl; i++)
		cout << ph[i] << " ";
	cout << endl << ll << " ";
	for (int i = 1; i <= ll; i++)
		cout << pl[i] << " ";
}
```

---

## 作者：iyaang (赞：3)

[神秘的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17072132.html)

[题目链接](https://www.luogu.com.cn/problem/CF226D)

调整构造。

发现 $n$ 和 $m$ 较小只有 $100$，因此可以考虑尝试进行修改从而不断逼近答案。

容易发现如果将某一行或列上的数字翻转，那么得到的新的和一定与原来的和异号，因此答案一定有解。在每次操作中，我们寻找是否有行或列和为负值，如果有就翻转。这样操作答案一定是单增的。

单次操作的时间复杂度为 $O(n)$，一次操作至少能将答案增加 $2$，又有 $\lvert a_{i,j} \rvert \le 100$，所以整个矩阵中的值最小为 $-100^3$，总的操作次数不会超过 $500000$ 次，事实证明很难跑满。

特别的，在这种自适应的调整中会出现“撤销”的操作，即将同一行或列翻转两次，此时相当于不进行该操作，需要删掉。

$Code$
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
	return s*w;
}

namespace LgxTpre
{
	static const int MAX=110;
	static const int mod=998244353;
	static const int INF=200707070707;
	
	int n,m;
	int a[MAX][MAX];
	
	int rsum[MAX],csum[MAX];
	set<int> rop,cop;
	inline int check()
	{
		for(int i=1;i<=n;++i)
			if(rsum[i]<0)
				return i;
		for(int i=1;i<=m;++i)
			if(csum[i]<0) 
				return i+n;
		return -1;
	}
	inline void print()
	{
		for(int i=1;i<=n;++i,puts(""))
			for(int j=1;j<=m;++j)
				cout<<a[i][j]<<" ";
		for(int i=1;i<=n;++i)
			cout<<rsum[i]<<" ";
		cout<<endl;
		for(int i=1;i<=m;++i)
			cout<<csum[i]<<" ";
		cout<<endl;
		getchar();
	}
	inline void solve()
	{
		while(1)
		{
			int p=check();
			if(p==-1) break;
			if(p<=n)
			{
				if(rop.find(p)!=rop.end()) rop.erase(p);
				else rop.insert(p);
				for(int i=1;i<=m;++i)
					rsum[p]-=a[p][i],csum[i]-=a[p][i],
					a[p][i]=-a[p][i],
					rsum[p]+=a[p][i],csum[i]+=a[p][i];					
			}
			if(p>n)
			{
				p-=n;
				if(cop.find(p)!=cop.end()) cop.erase(p);
				else cop.insert(p);
				for(int i=1;i<=n;++i)
					csum[p]-=a[i][p],rsum[i]-=a[i][p],
					a[i][p]=-a[i][p],
					csum[p]+=a[i][p],rsum[i]+=a[i][p];
			}
		}
		return;
	}
	
	inline void lmy_forever()
	{
		n=read(),m=read();
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				a[i][j]=read(),
				rsum[i]+=a[i][j],csum[j]+=a[i][j];
		solve();
		cout<<rop.size()<<" ";
		for(auto it=rop.cbegin();it!=rop.cend();++it)
			cout<<*it<<" ";
		cout<<endl;
		cout<<cop.size()<<" ";
		for(auto it=cop.cbegin();it!=cop.cend();++it)
			cout<<*it<<" ";
		return;
	}
}

signed main()
{
	LgxTpre::lmy_forever();
	return (0-0);
}
```

---

## 作者：dfkdsmbd (赞：2)

争取抢下一血。

这个题有一个很显然的贪心想法，每次扫描到某一行或者某一列的时候如果发现和为负数就进行修改。这样的复杂度和正确性是对的，因为显然对于整个表格，你的总权值和是在不断增加的，除了这一行/列以外，其他的点是没有变化的，每次至少增加2，而点权绝对值只有100以内。而这个上界又特别松，cf机器也不慢，所以肯定是能过的。

注意你还得输出修改次数最小的方案，对于某一行/列，如果修改了偶数次，那么它就是废操作。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <utility>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
#include <set>
#define ri register int
#define pi acos(-1.0)

using namespace std;

inline char gch()
{
    static char buf[100010], *h = buf, *t = buf;
    return h == t && (t = (h = buf) + fread(buf, 1, 100000, stdin), h == t) ? EOF : *h ++;
}

typedef long long lo;

typedef unsigned int uint;

template<typename inp_typ>

inline void re(inp_typ &x)
{
    x = 0;
    char a; bool b = 0;
    while(!isdigit(a = getchar()))
        b = a == '-';
    while(isdigit(a))
        x = x * 10 + a - '0', a = getchar();
    if(b == 1)
        x = - x;
}

int n, m, a[110][110], ta1, ta2, sta1[10010], sta2[10010], cnt1[110], cnt2[110];

inline bool check()
{
    for(ri i = 1; i <= n; i ++)
    {
        int su = 0;
        for(ri j = 1; j <= m; j ++)
            su += a[i][j];
        if(su < 0)
            return 1;
    }
    for(ri i = 1; i <= m; i ++)
    {
        int su = 0;
        for(ri j = 1; j <= n; j ++)
            su += a[j][i];
        if(su < 0)
            return 1;
    }
    return 0;
}

inline void print()
{
    for(ri i = 1; i <= n; i ++, printf("\n"))
        for(ri j = 1; j <= m; j ++)
            printf("%d ", a[i][j]);
    printf("\n");
}

int main()
{
    re(n), re(m);
    for(ri i = 1; i <= n; i ++)
        for(ri j = 1; j <= m; j ++)
            re(a[i][j]);
    while(check())
    {
        for(ri i = 1; i <= n; i ++)
        {
            int su = 0;
            for(ri j = 1; j <= m; j ++)
                su += a[i][j];
            if(su < 0)
            {
                for(ri j = 1; j <= m; j ++)
                    a[i][j] = -a[i][j];
                cnt1[i] ++;
                //print();
            }
        }
        for(ri i = 1; i <= m; i ++)
        {
            int su = 0;
            for(ri j = 1; j <= n; j ++)
                su += a[j][i];
            if(su < 0)
            {
                cnt2[i] ++;
                for(ri j = 1; j <= n; j ++)
                    a[j][i] = -a[j][i];
                //print();
            }
        }
    }
    for(ri i = 1; i <= n; i ++)
        if(cnt1[i] & 1)
            sta1[++ ta1] = i;
    for(ri i = 1; i <= m; i ++)
        if(cnt2[i] & 1)
            sta2[++ ta2] = i;
    printf("%d ", ta1);
    for(ri i = 1; i <= ta1; i ++)
        printf("%d ", sta1[i]);
    printf("\n");
    printf("%d ", ta2);
    for(ri i = 1; i <= ta2; i ++)
        printf("%d ", sta2[i]);
    system("pause");
}
```

---

## 作者：__Watcher (赞：1)

注意到 $|a_{i,j}|\le100$，是 $100$ 而不是 $1e9$，显然是从这里作为切入口。

考虑暴力修改。

明显，若将一个和为负数的行或列进行翻转操作，那么整个矩阵的总和必能增加至少 $2$。初始时，总和最小为 $-10000$，那么最大经过 $10000$ 次操作后，必定无法通过这种规则进行操作了。

反观规则，不能操作的充要条件就是没有任意一行或列的和是负数。

因此我们可以花费 $O(nm)$ 的复杂度进行一次操作，总共进行了 $10000$ 次，时间复杂度可以接受。

对于一行或一列，如果它需要操作偶数次，那么可以不进行操作。

可以证明，操作顺序不影响结果。

于是，这题就做完了。

---
提供代码，仅供参考：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll read() {
	ll x=0, f=1; char ch=' ';
	while(!isdigit(ch)) {ch=getchar(); if(ch=='-') f=-1;}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x*f;
}
int n, m, needh[105], needl[105], a[105][105]; 
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			a[i][j]=read();
		}
	}
	while(1) {
		int k=-1;
		for(int i=1;i<=n;i++) {
			int nows=0;
			for(int j=1;j<=m;j++) {
				nows+=a[i][j];
			}
			if(nows<0) {
				k=i;
				break;
			} 
		}
		if(k!=-1) {
			needh[k]=1-needh[k];
			for(int j=1;j<=m;j++) {
				a[k][j]=-a[k][j];
			}
			continue;
		}
		k=-1;
		for(int j=1;j<=m;j++) {
			int nows=0;
			for(int i=1;i<=n;i++) {
				nows+=a[i][j];
			}
			if(nows<0) {
				k=j;
				break;
			} 
		}
		if(k!=-1) {
			needl[k]=1-needl[k];
			for(int i=1;i<=n;i++) {
				a[i][k]=-a[i][k];
			}
			continue;
		}
		break;
	}
	int numh=0, numl=0;
	for(int i=1;i<=n;i++) if(needh[i]) numh++;
	cout<<numh<<" ";
	for(int i=1;i<=n;i++) if(needh[i]) printf("%d ", i);
	cout<<endl;
	for(int i=1;i<=m;i++) if(needl[i]) numl++;
	cout<<numl<<" ";
	for(int i=1;i<=m;i++) if(needl[i]) printf("%d ", i);
}

```


---

## 作者：Purslane (赞：0)

# Solution

解一定存在。

考虑所有 $2^{n+m}$ 种翻转情况中，必然有 $\sum_{i=1}^n \sum_{j=1}^m a_{i,j}$ 的最大值。

这时候必定所有行和列的和非负，否则可以通过翻转使得这个值更大。

考虑对原来的矩阵直接进行调整，如果有一列或者一行是负的，直接翻转。

这样至少使得 $\sum_{i=1}^n \sum_{j=1}^m a_{i,j}$ 增加 $2$。而增加的上限是 $O(nmV)$，所以复杂度为 $O(n^4)$。（认为 $n,m,V$ 同阶）

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
int n,m,a[MAXN][MAXN],pre1[MAXN],pre2[MAXN],flg1[MAXN],flg2[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) ffor(j,1,m) cin>>a[i][j],pre1[i]+=a[i][j],pre2[j]+=a[i][j];
	
	while(1) {
		int psl=0;
		ffor(i,1,n) if(pre1[i]<0) {
			psl=1,pre1[i]=-pre1[i],flg1[i]^=1;
			ffor(j,1,m) pre2[j]=pre2[j]-2*a[i][j],a[i][j]=-a[i][j];
		}
		ffor(j,1,m) if(pre2[j]<0) {
			psl=1,pre2[j]=-pre2[j],flg2[j]^=1;
			ffor(i,1,n) pre1[i]=pre1[i]-2*a[i][j],a[i][j]=-a[i][j];	
		}
		if(!psl) break ;
	}
	
	vector<int> vc1,vc2;
	ffor(i,1,n) if(flg1[i]) vc1.push_back(i);
	ffor(i,1,m) if(flg2[i]) vc2.push_back(i);
	cout<<vc1.size()<<' '; for(auto id:vc1) cout<<id<<' '; cout<<'\n';
	cout<<vc2.size()<<' '; for(auto id:vc2) cout<<id<<' '; cout<<'\n';
	return 0;
}
```

![](https://s21.ax1x.com/2024/06/11/pkUrWFg.png)

---

