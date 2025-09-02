# Meximum Array

## 题目描述

Mihai has just learned about the [MEX](https://en.wikipedia.org/wiki/Mex_(mathematics)) concept and since he liked it so much, he decided to use it right away.

Given an array $ a $ of $ n $ non-negative integers, Mihai wants to create a new array $ b $  that is formed in the following way:

While $ a $ is not empty:

- Choose an integer $ k $ ( $ 1 \leq k \leq |a| $ ).
- Append the MEX of the first $ k $ numbers of the array $ a $ to the end of array $ b $ and erase them from the array $ a $ , shifting the positions of the remaining numbers in $ a $ .

But, since Mihai loves big arrays as much as the MEX concept, he wants the new array $ b $ to be the lexicographically maximum. So, Mihai asks you to tell him what the maximum array $ b $ that can be created by constructing the array optimally is.

An array $ x $ is lexicographically greater than an array $ y $ if in the first position where $ x $ and $ y $ differ $ x_i > y_i $ or if $ |x| > |y| $ and $ y $ is a prefix of $ x $ (where $ |x| $ denotes the size of the array $ x $ ).

The MEX of a set of non-negative integers is the minimal non-negative integer such that it is not in the set. For example, MEX({ $ {1, 2, 3} $ }) $ = 0 $ and MEX({ $ {0, 1, 2, 4, 5} $ }) $ = 3 $ .

## 说明/提示

In the first test case, the lexicographically maximum array $ b $ is obtained by selecting $ k=5 $ , resulting in the $ MEX $ of the whole array $ a $ . It is lexicographically maximum because an array starting with a smaller number than $ 4 $ is lexicographically smaller, and choosing a $ k<5 $ would result in an array starting with a number smaller than $ 4 $ .

In the second test case, there are two ways to obtain the maximum array: first selecting $ k=6 $ , then $ k=2 $ , or first selecting $ k=7 $ and then $ k=1 $ .

## 样例 #1

### 输入

```
6
5
1 0 2 0 3
8
2 2 3 4 0 1 2 0
1
1
5
0 1 2 3 4
4
0 1 1 0
10
0 0 2 1 1 1 0 0 1 1```

### 输出

```
1
4 
2
5 1 
1
0 
1
5 
2
2 2 
4
3 2 2 0```

# 题解

## 作者：vectorwyx (赞：5)

贪心思路是每次选最靠左的与整体 mex 相同的位置对应的前缀删去。

用 deque 维护每个值的位置序列，每次按值从小到大遍历直到遇到某个空的 deque，这个 deque 对应的值即为 mex。然后考察每个在 mex 之前的 deque 的第一个元素，把它们取 max 就是要删除的前缀的长度，然后暴力遍历在 mex 之前的每个 deque，弹出 $\le pos$ 的数即可。重复这个过程直至删去了所有的数，时间复杂度 $O(n)$。

代码如下：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')fh=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e5+5;
int a[N],n,b[N],m;
deque<int> g[N];

void solve(){
	cin>>n;fo(i,1,n) g[i].clear();
	fo(i,1,n) a[i]=read(),g[a[i]].pb(i);
	int pos=0;m=0;
	while(pos<n){
		int t=pos;
		fo(i,0,n){
			if(g[i].empty()){
				b[++m]=i;
				break;
			} 
			big(pos,g[i][0]);
		}
		big(pos,t+1);
		fo(i,0,n){
			if(g[i].empty()) break;
			while(!g[i].empty()&&g[i][0]<=pos) g[i].pop_front();
		}
	}
	cout<<m<<'\n';out(b,1,m);
}

signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：BAKABAKABAKABAKA (赞：3)

贪心思想，依次求出最优区间，对于一个已知 $ l $ 的区间，$ r $ 显然越小越好。于是考虑二分。二分的时候需要计算区间 $ \text{mex} $，参考 [P4137 Rmq Problem / mex](https://www.luogu.com.cn/problem/P4137)，用主席树做即可。时间复杂度 $ \Theta(n \log^2 n) $，无需卡常。

[Code & Submission](https://codeforces.com/contest/1629/submission/266701349)

---

## 作者：cqbzhzf (赞：1)

[题目链接](http://codeforces.com/contest/1628/problem/A)

### 题目大意

给出一个长度为 $n$ 的序列 $a$ 和一个空序列 $b$，你每次可以选择 $a$ 的一个前缀，将它的 $\operatorname{mex}$  加入序列 $b$ 的末尾，然后将 $a$ 的这个前缀删除。求 $b$ 的最大字典序。

注意：$1\le n\le2\times10^5$，$0\le a_i\le n$。
### 解题思路
显然地我们每次肯定要选 $\operatorname{mex}$ 最大的一个前缀，为了最大化我们后面的值，那么我们显然是选的前缀越短越好。

而考虑如何快速求到这个前缀，我们可以考虑从小到大枚举这个 $\operatorname{mex}$ 的值，假设现在枚举到 $x$，那么证明我们得到的前缀 $1\sim r$ 之中已经有 $0\sim x−2$ 了，我们就先看这个前缀中是否有 $x−1$ ，如果有就枚举下一个数，不然我们就让 $r$ 跳到第一个 $x$ 处。

显然这样一次的复杂度是 $O(\operatorname{mex}\log n)$ 的，但是因为删除的数字个数和 $\operatorname{mex}$ 同级，而一个数字最多被删除一次，这样时间复杂度就是 $O(n\log n)$ 了。

写个 vector 上二分就好了。
### 题解
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n;
vector<int> v[N],mex;
int lb(int x,int L)
{
	int l=0,r=v[x].size()-1;
	while(l<=r)
    	{
		int mid=(l+r)>>1;
		if(v[x][mid]<=L)
          		l=mid+1;
		else 
          		r=mid-1;
	}
	return (l>=v[x].size())?(n+1):v[x][l];
}
int main()
{
	scanf("%d",&T);
	while(T--)
    	{
		scanf("%d",&n);mex.clear();
		for(int i=0;i<=n;i++)v[i].clear();
		for(int i=1,x;i<=n;i++)
        	{
			scanf("%d",&x);
			v[x].push_back(i);
		}
		int l=0;
		while(l<n)
       		{
			int r=l+1;
			for(int i=0;i<=n;i++)
         		{
				int p=lb(i,l);
				if(p>n)
                		{
					mex.push_back(i);
					break;
				}
				r=max(p,r);
			}
			l=r;
		}
		printf("%d\n",mex.size());
		for(int i=0;i<mex.size();i++)
			printf("%d ",mex[i]);
		putchar('\n');
	}
}
```

---

## 作者：jzcrq (赞：1)

### 题目概述

对于给定的数组 $a$，将它划成一或几部分，使每部分的 MEX 顺次组成的数组 $b$ 字典序最大。

我们可以先将 $a$ 数组扫一遍，记录每个数字第一次出现的位置。

之后我们从 0 开始，从小到大确定每个数字出现的位置，记录到目前位置下标最大的位置 $pos_{max}$，直到找到一个数字 $a_{none}$ 没有出现。

我们可以把从数组头到 $pos_{max}$ 这一段划成一部分。这部分包含了数组 $a$ 中最长的连续的 $0,1,2...max$ 的序列的每个元素，所以它可以令 $b$ 的字典序最大化。

而这个 $max$ 就是 $a_{none}-1$，也就是这一部分的 MEX。

依照题目所述，我们将这部分去掉，然后继续扫，直到整个数组 $a$ 为空即可。

显然，我们不能把前面的数组像描述中那样去掉。

但我们可以通过把起点换成 $pos_{max}+1$ 来“掐掉”前面的那部分。

这样就构造出了字典序最大的数组 $b$。

坏消息是，这种做法最坏是 $\mathcal{O}(n^2)$ 的，可以被极端数据卡。

怎么办？ 优化！

我们发现：当我们扫到的 0 没有再出现时，后面的每部分 MEX 都一定是 0，最优方案就是后面每个元素对应一个 0。

可以进而想到，本次扫描的 VEX一定小于或等于上次扫描的 $a_{none}-1$，可以借此进行优化。

------------

### Code

```cpp
#include <cstdio>
#include <cstring>

const int MAXN=2e5+10;
int t,n,num[MAXN],pos[MAXN],output[MAXN];

inline int read()
{
	int x=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x;
}

int main()
{
	t=read();
	for (;t--;)
	{
		memset(num,0,sizeof(num));
		memset(output,0,sizeof(output));
		int head=1,lst=0,top=MAXN,cnt=0,tot=0;
		n=read();
		for (int i=1;i<=n;i++) num[i]=read();
		while (head<=n)
		{
			cnt=0;
			memset(pos,0,sizeof(pos));
			for (int i=head;i<=n;i++)
			{
				if (!pos[num[i]])
				{
					pos[num[i]]=i;
					if (num[i]<=top) cnt++;
					if (cnt==top) break;
				}
			}
			cnt=0,lst=head;
			for (int i=0;i<=n+1;i++)
			{
				if (pos[i])
				{
					cnt++;
					if (lst<pos[i]) lst=pos[i];
				}
				else
				{
					output[++tot]=cnt;
					head=lst+1;
					top=cnt;
					break;
				}
			}
		}
		printf("%d\n",tot);
		for (int i=1;i<=tot;i++) printf("%d ",output[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：zhicheng (赞：0)

### 思路

贪心。

因为要字典序最大，设现在剩下的数组的 MEX 是 $mex$，每次考虑删除 $a$ 数组 MEX 等于 $mex$ 的最短前缀。这样 $b$ 的这一位一定最大，而且 $a$ 留下的最多，下一次也一定更优。所以先找出 $a$ 的 MEX，每次从前往后计算这个前缀的 MEX，当他等于 $mex$ 时就退出（方法为记录小于 $mex$ 的不同的数有多少个，当有 $mex$ 个的时候就可以了）。与此同时可以更新 $mex$，但是注意要拿另外的东西记录（代码中为 $mexx$，方法为依次删除，如果这个数 $a_i$ 删完了就取 $mexx\leftarrow \min(mexx,a_i)$）。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],ans[200010];
map<int,int>mapp,q;
int main(){
	int t,n,cnt,mex,mexx,now,sum;
	scanf("%d",&t);
	while(t--){
		cnt=0;
		now=1;
		scanf("%d",&n);
		mapp.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			mapp[a[i]]++;
			ans[i]=0;
		}
		for(int i=0;i<=n;i++){
			if(!mapp[i]){
				mexx=mex=i;  //计算原来的 MEX
				break;
			}
		}
		while(now<=n){
			if(mex==0){
				cnt+=n-now+1;  //特判一下
				goto kk;
			}
			q.clear();
			sum=0;
			while(sum!=mex){
				if(a[now]<=mex&&!q[a[now]]){
					q[a[now]]=1;  //记录小于 MEX 的不同数的个数，如果等于 MEX 就可以了
					sum++;
				}
				mapp[a[now]]--;
				if(mapp[a[now]]==0){
					mexx=min(mexx,a[now]);  //删除和更新
				}
				now++;
			}
			mex=mexx;
			ans[++cnt]=sum;
		}
		kk:printf("%d\n",cnt);
		for(int i=1;i<=cnt;i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
}
```

---

## 作者：Exber (赞：0)

首先设当前 $\operatorname{MEX}$ 为 $mex$，那么**由于想要答案字典序尽可能大，所以这一次删数后加进 $b$ 的数肯定是 $mex$**。

那么**为了让 $b$ 后面的位也尽可能大，即让剩下的数组 $\operatorname{MEX}$ 尽可能大，那么我们删掉的数肯定要尽可能少**。所以每次选一个最短的满足 $\operatorname{MEX}=mex$ 前缀删去即可。

部分代码如下：

```cpp
int n,a[400005];
int tot[400005],tot2[400005],b[400005];

inline void slove()
{
	scanf("%d",&n);
	int mex=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		tot[a[i]]++;
		while(tot[mex]>0)
		{
			mex++;
		}
	}
	int cnt=0,submex=0,nxtmex=mex;
	for(int i=1;i<=n;i++)
	{
		tot2[a[i]]++;
		while(tot2[submex]>0)
		{
			submex++;
		}
		if(a[i]<mex&&tot[a[i]]==1)
		{
			nxtmex=min(nxtmex,a[i]);
		}
		tot[a[i]]--;
		if(submex==mex)
		{
			b[++cnt]=mex;
			mex=nxtmex;
			for(int j=submex-1;j>=0;j--)
			{
				tot2[j]=0;
			}
			submex=0;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
	{
		printf("%d ",b[i]);
	}
	printf("\n");
	for(int i=0;i<=n;i++)
	{
		tot[i]=0;
		tot2[i]=0;
	}
}
```

---

