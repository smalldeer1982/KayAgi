# Once in a casino

## 题目描述

## 题目大意
给定两个长度都为n$(1\leq n\leq 10^5)$的数字串A和B，你可以执行若干次操作，每次操作是将相邻的两个位置+1或-1，要求不能对数字串以外的位置进行操作，且操作中每个数字都必须在$[0,9]$中。求把A变成B所执行的最小操作数c，并输出前$\min(c,10^5)$个操作，无解输出-1。

## 样例 #1

### 输入

```
3
223
322
```

### 输出

```
2
1 1
2 -1
```

## 样例 #2

### 输入

```
2
20
42
```

### 输出

```
2
1 1
1 1
```

## 样例 #3

### 输入

```
2
35
44
```

### 输出

```
-1
```

# 题解

## 作者：傅思维666 (赞：2)

## 题解：

**题目大意：**给两个数字串，每次可以对$a[i],a[i+1]$同时+1或-1，那么请回答能否经过若干次操作使得$a$变成$b$。如果不能输出$-1$。如果能输出最小方案（前$10^5$步）。

分析题目，可以发现的性质是：每一位一定受前面那位的影响，所以对前面的数做完修改，在对后面的数做修改时，要考虑好前一次修改的基础。即如果对$a[i]$修改了$b1-a1$，对$a[i+1]$要做$b2-a2-(b1-a1)$的修改。

然后因为不能超限，所以如果$a[n]$也有值的话就说明不能到达。

然后方案就从前往后扫描，对于不合法位置直接dfs输出方案即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
typedef long long ll;
const int maxn=1e6+6;
int n;
char s[maxn],t[maxn];
ll ans,a[maxn];
void dfs(int x, int w) 
{
    if(s[x+1]+w<'0'||s[x+1]+w>'9') 
        dfs(x+1,-w);
    printf("%d %d\n",x,w);
    s[x]+=w;
    s[x+1]+=w;
    if(!(--ans)) 
        exit(0);
}
int main() 
{
    scanf("%d%s%s",&n,s+1,t+1);
    for(int i=1;i<=n;i++)
    {
        a[i]=-a[i-1]+t[i]-s[i];
        ans+=abs(a[i]);
    }
    if(a[n]) 
    {
        puts("-1");
        return 0;
    }
    printf("%lld\n",ans);
    if(!ans) 
        return 0;
    ans=min(ans,(ll)1e5);
    for(int i=1;i<n;i++)
        while(s[i]!=t[i]) 
            dfs(i,t[i]>s[i]?1:-1);
    return 0;
}
```



---

## 作者：Purslane (赞：1)

# Solution

我看到这道题是 `*2700` 觉得它可能有点难。但是非常唐。

考虑设 $\Delta_i$ 为第 $i$ 位和第 $i+1$ 的这组操作中，需要进行多少次 $\pm$ 操作，并且根据 $a_n+ \Delta_{n-1}$ 是否等于 $b_n$ 判断是否有解。如果有解，我们将构造地证明，我们只会在必须加的地方加，必须减的地方减，所以 $c = \sum_{i=1}^{n-1} |\Delta_i|$。

> $\Delta_i$ 显然由递推式 $\Delta_i = b_i - a_i - \Delta_{i-1}$ 给出。

我们从 $1$ 开始尝试把 $\Delta_i$ 删掉。如果我们想把某一个位置（比如 $i+1$）加 $1$，但是当前 $a_{i+1} = 9$，那么是无法进行操作的。

不过注意到此时残余的 $\Delta_{i+1}$ 必然小于零，不然 $a_{i+1}$ 最终会大于 $9$，于是尝试先把 $\Delta_{i+1}$ 进行一次。但是这时候 $a_{i+2}$ 可能等于 $0$，所以我们可能还要考虑 $\Delta_{i+2}$……这样下去，我们一直要考虑到 $\Delta_{n-1}$。注意到，$a_n$ 必定可以让 $\Delta_{n-1}$ 进行（在到达零之前，$\Delta$ 的符号一直不变），那么我们的过程一定可以结束。

其他所有情况都非常相近。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,a[MAXN],b[MAXN],dt[MAXN],c;
string S,T;
vector<pair<int,int>> ans;
void update(int pos) {
	if(dt[pos]>0) a[pos]++,a[pos+1]++,dt[pos]--;
	else a[pos]--,a[pos+1]--,dt[pos]++;
	return ;
}
void del(int pos) {
	if(a[pos]==0) {
		int flg=-1,tval=9;
		roff(j,pos-1,1) {
			if(a[j]!=tval) {flg=j;break;}
			tval=9-tval;
		}
		ffor(i,flg,pos-1) ans.push_back({i,dt[i]/abs(dt[i])}),update(i);
	}
	if(a[pos+1]==0) {
		int flg=-1,tval=9;
		ffor(j,pos+2,n) {
			if(a[j]!=tval) {flg=j;break;}
			tval=9-tval;
		}
		roff(i,flg,pos+2) ans.push_back({i-1,dt[i-1]/abs(dt[i-1])}),update(i-1);
	}
	ans.push_back({pos,-1});
	if(ans.size()>=c) {
		ffor(i,0,c-1) cout<<ans[i].first<<' '<<ans[i].second<<'\n';
		exit(0);	
	}
	return update(pos),void();
}
void add(int pos) {
	if(a[pos]==9) {
		int flg=-1,tval=0;
		roff(j,pos-1,1) {
			if(a[j]!=tval) {flg=j;break;}
			tval=9-tval;
		}
		ffor(i,flg,pos-1) ans.push_back({i,dt[i]/abs(dt[i])}),update(i);
	}
	if(a[pos+1]==9) {
		int flg=-1,tval=0;
		ffor(j,pos+2,n) {
			if(a[j]!=tval) {flg=j;break;}
			tval=9-tval;
		}
		roff(i,flg,pos+2) ans.push_back({i-1,dt[i-1]/abs(dt[i-1])}),update(i-1);
	}
	ans.push_back({pos,1});
	if(ans.size()>=c) {
		ffor(i,0,c-1) cout<<ans[i].first<<' '<<ans[i].second<<'\n';
		exit(0);	
	}
	return update(pos),void();
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>S>>T,S="&"+S,T="&"+T;
	ffor(i,1,n) a[i]=S[i]-'0',b[i]=T[i]-'0';
	ffor(i,1,n-1) dt[i]=b[i]-a[i]-dt[i-1];
	if(a[n]+dt[n-1]!=b[n]) return cout<<-1,0;
	ffor(i,1,n-1) c+=abs(dt[i]);
	cout<<c<<'\n',c=min(c,100000ll);
	ffor(i,1,n-1) {
		while(dt[i]<0) del(i);
		while(dt[i]>0) add(i);
	}
	return 0;
}
```

---

