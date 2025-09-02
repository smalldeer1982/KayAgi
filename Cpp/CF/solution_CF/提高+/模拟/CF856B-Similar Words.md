# Similar Words

## 题目描述

单词是由小写英文字母组成的非空串。
若一个单词去掉首字母后与另一个单词相同，则这两个单词相似。
现给定n个单词(可能重复)，请挑选尽量多的新单词组成集合x并满足条件：
1.	集合x中的新单词为原n个单词的前缀（包含自身）
2.	集合x中的新单词两两不相似。
输出x中的最大单词数。
共有t组数据

## 说明/提示

对于20%数据，1<=n<=20,长度之和不超过100
对于50%数据，1<=n<=5000
对于100%数据，1<=n<=1000000
数据保证在一组任务中的所有单词长度之和不超过1000000

## 样例 #1

### 输入

```
2
3
aba
baba
aaab
2
aa
a
```

### 输出

```
6
1
```

# 题解

## 作者：_edge_ (赞：0)

没人发题解？

这里的集合是不可重集合。

首先看到这种选一个不能选另外一个的，肯定是连图。

然后我们发现，我们如果把两个相似的进行连边连出来的必然是个树。

具体的，我们可以发现一段字符串是一段字符串去掉头之后相等，那么长度必然差一，并且这两段字符是唯一确定的。

举个例子，我们对于 `aaa` ，那么它在而不能在的，并且长度比它小的字符串有 `aa`，同时也只有 `aa`。

这就意味着每个字符串有个唯一确定的长度比它小的不能连的字符串。

那么连成一棵树之后跑独立集就可以了。这东西可以 DP。

设 $f_{x,0/1}$ 表示他选还是不选，就是没有上司的舞会。

相信来做这题的都会这个基础 DP。

然后确定那个父亲就用哈希就可以了。

注意到这里哈希冲突概率较高，用大一点的模数。

总时间复杂度 $O(n \log n)$。

```cpp
// LUOGU_RID: 96844422
#include <bits/stdc++.h>
#define int __int128
#define pb push_back 
#define ll long long 
using namespace std;
const int INF=2e6+5;
const int INFN=2e6+5;
const int Mod=10000000000000061;
const int base=233;
int n,p[INFN],M[INFN];
string s1[INF];
struct _node_edge{
	int to_,next_; 
}edge[INF<<1];
int tot,head[INF],f[INF][5],vis[INF];
void add_edge(int x,int y) {
//	cout<<x<<" "<<y<<" edge\n";
	edge[++tot]={y,head[x]};
	head[x]=tot;
}
vector <int> cnt;
int Get(int x) {return lower_bound(cnt.begin(),cnt.end(),x)-cnt.begin()+1;}
void DFS(int x,int fa) {
	f[x][1]=1;vis[x]=1;f[x][0]=0;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS(v,x);
		f[x][0]+=max(f[v][1],f[v][0]);
		f[x][1]+=f[v][0];
	}
	return ;
}
int fl=0;
void solve() {
	ll nn=n;cin>>nn;
	n=nn;cnt.clear();
	for (int i=1;i<=n;i++) cin>>s1[i];
	for (int i=1;i<=n;i++) {
		int len=s1[i].size(),ha=0;
		for (int j=0;j<len;j++) {
			ha=(ha*base+s1[i][j])%Mod;
			cnt.pb(ha);
		}
	}
	
//	for (int i=1;i<=n;i++) {
//		int len=s1[i].size(),ha=0;
//		for (int j=1;j<len;j++) {
//			ha=(ha*base+s1[i][j])%Mod;
//			cnt.pb(ha);
//		}
//	}
	
	sort(cnt.begin(),cnt.end());
	cnt.erase(unique(cnt.begin(),cnt.end()),cnt.end());
	
	int len=cnt.size();
	for (int j=0;j<=len;j++) p[j]=M[j]=vis[j]=0;
//	cout<<cnt[0]<<" qwe\n";
//	for (int i=1;i<=n;i++) {
//		int len=s1[i].size(),ha=0;
//		for (int j=0;j<len;j++) {
//			ha=(ha*base+s1[i][j])%Mod;
//			p[Get(ha)]=i;
//		}
//	}

	for (int i=1;i<=n;i++) {
		int len=s1[i].size(),ha=0,ha1=0;
		for (int j=0;j<len;j++) {
			ha=(ha*base+s1[i][j])%Mod;
			if (j) ha1=(ha1*base+s1[i][j])%Mod;
			if (M[Get(ha)]) continue;
			M[Get(ha)]=1;
//			cout<<i<<" "<<j<<" "<<Get(ha1)<<" "<<Get(ha)<<" "<<ha1<<" kewwq\n";
			int it=Get(ha1),it1=Get(ha);
			if (!j || !it) continue;
			if (cnt[it-1]!=ha1) continue;
			add_edge(it,it1);
			add_edge(it1,it);
		}
	}
	int res=0;
	for (int i=1;i<=cnt.size();i++)
		if (!vis[i]) {DFS(i,0);res+=max(f[i][0],f[i][1]);}
	ll ans=res;
	cout<<ans<<"\n";
	for (int i=1;i<=tot;i++) edge[i]={0,0};
	for (int i=0;i<=cnt.size()+5;i++) head[i]=0;
	tot=0;
	return ;
}
signed main()
{
//	freopen("data.in","r",stdin);
	ios::sync_with_stdio(false);
	int t=0;ll tt=0;cin>>tt;t=tt;
	while (t--) {
		solve();
	}
	return 0;
}
```


---

