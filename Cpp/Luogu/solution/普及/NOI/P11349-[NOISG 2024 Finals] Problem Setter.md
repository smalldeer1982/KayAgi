# [NOISG 2024 Finals] Problem Setter

## 题目背景

Stuart 是一名热衷于编程比赛的题目设计者，他为多个比赛设定了许多问题。他希望将自己的一些问题提交到编程比赛中，以获得更多的荣誉。

## 题目描述

Stuart 可以将题目提交到 $c$ 个比赛中。如果将问题提交到第 $i$ 个比赛，他的满意度会增加 $s_i$。但由于比赛的结构和其他题目设计者的竞争，第 $i$ 个比赛只会接受质量至少为 $m_i$ 的题目。每个比赛可以接受多个问题，每个问题都会增加 $s_i$ 的满意度。

Stuart 总共设计了 $p$ 道问题，他认为第 $j$ 道问题的质量是 $q_j$。但由于问题准备过程的难度，提交第 $j$ 道问题到任何比赛会使他的满意度减少 $d_j$。显然，每个问题最多只能提交到一个比赛，或者可以选择不提交。

请帮 Stuart 找到一个最优的提交方案，以使他的满意度最大化。如果所有提交方案都会导致负满意度，他可以选择不提交任何问题，最终满意度为 $0$。

## 说明/提示

【样例解释】

对于样例 #1：
- 比赛 $1$ 的最低质量要求为 $2$，问题 $1$ 满足条件，提交后增加 $5 - 2 = 3$ 的满意度。
- 比赛 $1$ 的最低质量要求为 $2$，问题 $2$ 满足条件，提交后增加 $5 - 4 = 1$ 的满意度。
- 最终满意度为 $3 + 1 = 4$。
- 问题 $3$ 和其他比赛没有提交。

对于样例 #2：
- 根据提交方案，最优满意度为 $11$。

对于样例 #3：
- 最优方案使满意度为 $2$。

【数据范围】

- $1 \leq c, p \leq 200,000$
- $0 \leq m_i, s_i, q_j, d_j \leq 1,000,000$

| 子任务编号 | 分值 | 限制条件                     |
|:---:|:---:|:---:|
| $0$ | $0$  | 样例测试用例                     |
| $1$ | $18$ | $1 \leq c \leq 1,000, p = 1$     |
| $2$ | $16$ | $1 \leq c, p \leq 1,000$         |
| $3$ | $26$ | $d_j = 0$                        |
| $4$ | $40$ | 无额外限制                       |

## 样例 #1

### 输入

```
3 3
2 5
1 1
8 3
3 2
9 4
1 3```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4
2 3
1 1
8 4
2 0
7 0
1 0
8 0```

### 输出

```
11```

## 样例 #3

### 输入

```
5 1
3 4
1 2
5 6
2 8
4 0
3 6```

### 输出

```
2```

# 题解

## 作者：shaun2000 (赞：3)

# solution
考虑贪心。

由于每一场比赛可以投无限道题目，所以对于每一道题目，我们一定是把它投给满足质量要求的增加满意度最多的比赛，如果亏就不投。所以可以先处理出质量为 $i$ 的比赛所能提供的最大满意度 $a[i]$ ，又因为一道质量为 $i$ 的题目，一定满足任一一场质量要求为 $j \le i$ 的比赛，所以我们可以通过 $a[i]=\max(a[i] ,a[i-1])$ 处理出一道质量为 $i$ 的题所能得到的最大满意度。最后求出满意度减去每一道题带来的满意度损失的和即为答案。

时间复杂度： $O(c+p)$。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;

int a[1000005];
int main(){
    int c,p;
	scanf("%d%d",&c,&p) ;
	for(int i=1;i<=c;i++)
	{
		int m,s;
		scanf("%d%d",&m,&s);
		a[m]=max(a[m],s);//求出质量为m的比赛的最大满意度
	}
	for(int i=1;i<=1000000;i++)
		a[i]=max(a[i],a[i-1]);//求出质量为i的题能获得的最大满意度
	long long ans=0;//long long
	for(int i=1;i<=p;i++)
	{
		int q,d;
		scanf("%d%d",&q,&d);
		ans+=max(0,a[q]-d);//若亏，则不投
	}
	printf("%lld\n",ans);
   	return 0;
}
``````
[ac记录](https://www.luogu.com.cn/record/195962883)

---

## 作者：linch (赞：3)

建议评黄。

Knowledge：贪心，双指针。

## Problem
你有 $p$ 道题可以投给 $c$ 个比赛，第 $j$ 题质量为 $q_j$，投给任何一个比赛会让你的满意度减少 $d_j$。第 $i$ 个比赛只接受质量不低于 $m_i$ 的题目，任意一道题投给这场比赛会使你的满意度增加 $s_i$，你需要求出最大的满意度。

## Solution
考虑贪心。

容易发现第 $i$ 道题投给第 $j$ 个比赛所得满意度为 $s_j-d_i$。那么对于每道题，可以投给一个符合条件且 $s_j$ 最大的比赛。但根据这个思路枚举每一道题、每一场比赛的复杂度是 $O(cp)$ 的，无法通过。

**如何优化找比赛的过程？**

可以使用双指针。

将比赛和题目质量分别按倒序排序。那么对于一个题目 $i$，将指向比赛的指针 $j$ 移到第一个满足 $m_j \le a_i$ 的位置。由于比赛的质量要求按倒序排序，**那么这道题一定符合 $[j,c]$ 范围内比赛的要求**。我们只需要预处理出 $[j,c]$ 范围内比赛 $s_i$ 的最大值，即可计算出这道题所贡献的满意度。

综合时间复杂度为 $O(c \log c + p \log p)$，可以通过本题。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int c,p,mx[maxn];
long long sum;
struct node{
	int x,y;
}a[maxn],b[maxn];
bool cmp(node xx,node yy){
	return xx.x>yy.x;
}
int main(){
	cin>>c>>p;
	for(int i=1;i<=c;i++){
		cin>>a[i].x>>a[i].y;//比赛，x 代表质量要求，y 代表满意度。
	}
	for(int i=1;i<=p;i++){
		cin>>b[i].x>>b[i].y;//题目，x 代表质量，y 代表扣减的满意度。
	}
	sort(a+1,a+c+1,cmp);
	sort(b+1,b+p+1,cmp);
	for(int i=c;i>=1;i--){
		mx[i]=max(mx[i+1],a[i].y);
	}//预处理 [i,c] 内满意度最大值。
	int j=1;
	for(int i=1;i<=p;i++){//枚举每一道题。
		while(j<=c && a[j].x>b[i].x){
			j++;
		}
		if(j==c+1) break;//这道题无法满足任何比赛的要求，很明显后面的题也无法满足，退出。
		if(mx[j]>b[i].y){
			sum+=mx[j]-b[i].y;
		}
	}
	cout<<sum<<"\n";
	return 0;
}
```
[AC record](https://www.luogu.com.cn/record/193626076)

---

## 作者：Duanhen (赞：2)

## 题目大意
有 $c$ 个比赛，每个比赛有最低质量要求 $m$ 和满意度 $s$，而有 $p$ 个题目，每个题目有质量 $q$ 和负满意度 $d$，要求将题目上交的同时求得使满意度最大的方案（如果某道题目能拿到的最大满意度不足损失的满意度，则可以不交该题目）。

## 解题思路
该题本质上就是一道贪心题，对于每一道题目，我们在该题可以提交的所有比赛中（即题目质量满足比赛要求），选择满意度最大的比赛，如果该满意度大于该题上交时损失的满意度（即可以使总满意度变大），则将该题交到该比赛上。

如果直接暴力查找匹配每道题，不用想都知道会超时到怀疑人生。那我们就可以采取带预处理的方法，怎么做呢？

我们可以将所有比赛按题目质量要求从小到大排序，这样在后面查找每道题可以提交的最高质量比赛时，便可以利用有序性，用二分法进行查找把复杂度降到 $\log$ 级别。并且在排好序之后，开一个数组 $M$，预处理前 $i$ 场比赛的最大满意度，之所以这样写，是因为一旦某道题目满足第 $i$ 场比赛的质量要求，则其必然满足 $i$ 之前所有比赛的质量要求，故在这些比赛里挑出满意度最高的比赛进行提交。

## 参考代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;

struct game{ ll m,s; }ga[N];
struct question{ ll q,d; }qu[N];
bool cmp(game &a, game &b){
	return a.m < b.m;
}
ll M[N];

int main(){
	ll c, p,res = 0;
	cin >> c >> p;
	for(int i=1;i<=c;i++) cin >> ga[i].m >> ga[i].s;
	for(int i=1;i<=p;i++) cin >> qu[i].q >> qu[i].d;
	sort(ga+1,ga+c+1,cmp); //排序
	for(int i=1;i<=c;i++) M[i] = max(M[i-1],ga[i].s); //预处理
	for(int i=1;i<=p;i++){
		ll L = 1, R = c;
		ll ind = 0; //ind记录该题目能交到的最高质量要求的比赛
		while(L <= R){ //二分
			ll mid = (L+R)/2;
			if(ga[mid].m <= qu[i].q) ind = mid,L = mid + 1;
			else R = mid - 1;
		}
		if(M[ind] > qu[i].d)res += M[ind]-qu[i].d;//如果这个题目能加大满意度，则加上，否则不交该题目
	}
	cout << res;
	return 0;
}
```

---

## 作者：savvsavsaasvav (赞：1)

## 前言
一道简单的贪心+双指针问题，我觉得出的挺不错的，题目理解起来简单，代码写起来短。

## 朴素做法：
对于第 $i$ 道题目，去遍历每一场比赛 $j$，对于满足 $m_j\le q_i$ 的所有比赛，在它们其中取一个最大的 $s_j$，若是还比 $d_j$ 要小，那就不投，不然就投这场比赛。时间复杂度 $O(cp)$。

## 正解
需要开一个 pair（或者结构体）来分别储存每一场比赛和每一道题目的信息。然后将它们按照质量要求或质量从大到小排。然后用一个后缀 max 来记录对于每一个比赛，它以及质量要求比它低的所有比赛的 $s_i$ 的最大值。

考虑使用双指针 $(i,j)$ 来记录当前遍历到的第 $i$ 道题目及质量要求比 $s_i$ 要小的的 $j$ 的最小值。然后利用我们刚才预处理的后缀 max，来知道是否要投及投完后获得的满意度，将其记录在 $ans$ 中。时间复杂度 $O(c\log c+p\log p)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
int c,p,mx[N];
pair<int,int>con[N];//分别表示比赛的最低要求质量和满意度增加量。
pair<int,int>pro[N];//分别表示题目的质量和满意度减少量。
long long ans=0;//一定记得开 long long
int main(){
	scanf("%d%d",&c,&p);
	for(int i=1;i<=c;++i){
		scanf("%d%d",&con[i].fi,&con[i].se);
	}
	for(int i=1;i<=p;++i){
		scanf("%d%d",&pro[i].fi,&pro[i].se);
	}
	sort(con+1,con+1+c,greater<pair<int,int> >());//倒序排序
	sort(pro+1,pro+1+p,greater<pair<int,int> >());
	for(int i=c;i>=1;--i){
		mx[i]=max(mx[i+1],con[i].se);//后缀 max
	}
	for(int i=1,j=1;i<=p;++i){
		while(pro[i].fi<con[j].fi&&j<=c){
			j++;
		}
		if(j==c+1){//遍历到质量要求最小的都不满足条件，就不会有任何比赛满足 m_j<=q_i，此题作废。
			break;
		}
		ans+=max(0,mx[j]-pro[i].se);//如果满足要求的最大满意度都不能抵消满意度 d[i] 的损失，就不投任何比赛。
	}
	printf("%lld",ans);
}
```

---

## 作者：why17 (赞：0)

~~看到大佬们的代码都好简短，再一看自己写的什么玩意~~

### 题目大意：

我们的主角 Stuart 准备了 $p$ 个问题，要提交到 $c$ 个比赛中。每个比赛有一个质量要求和一个满意度增益，每道题也有一个质量和一个满意度损失，我们需要最大化满意程度。

### 解题思路：

我们先读取比赛数和题目数，再把每个比赛和题目的两个参数分别存到两个数组中。接着，把比赛按照其最低质量要求 $m$ 排序，再维护一个前缀和数组 $b$，其中第 $i$ 项表示前 $i+1$ 个比赛中最大的满意度增益 $s$。然后对于每道题目，用二分找到最大的满足 $m$ 小于等于 $q$ 的 $m$，接着计算提交题目到该比赛能增加的净满意度 $s-d$，如果为正就累加到总满意度中。最后输出总满意度就可以了。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int c,p;
int f(const vector<int>& m,int q){
	int l=0,r=m.size()-1;
	int ans=-1;
	while(l<=r){
		int mid=l+(r-l)/2;
		if(m[mid]<=q){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return ans;
}
int main(){
	cin>>c>>p;
	vector<pair<int,int> > com(c);
	for(int i=0;i<c;i++) cin>>com[i].first>>com[i].second;
	sort(com.begin(),com.end());
	vector<pair<int,int> > pr(p);
	for(int i=0;i<p;i++) cin>>pr[i].first>>pr[i].second;
	vector<int> m(c),b(c);
	int maxn=0;
	for(int i=0;i<c;i++){
		m[i]=com[i].first;
		if(i==0) maxn=com[i].second;
		else maxn=max(maxn,com[i].second);
		b[i]=maxn;
	}
	long long tot=0;
	for(int i=0;i<p;i++){
		int q=pr[i].first;
		int d=pr[i].second;
		int tmp=f(m,q);
		if(tmp!=-1){
			int cur=b[tmp]-d;
			if(cur>0) tot+=cur;
		}
	}
	cout<<tot;
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11349)

# 题目分析

先对所有比赛按 $m$ 从小到大排序。不难发现，如果一道题目可以投到比赛 $i$，那么从比赛 $1$ 到比赛 $i-1$ 都可以投。因此，对于一道题目 $j$，只需要找满足 $m_i<=p_j$ 的最大的 $i$，显然可以想到二分。

再加一个优化，就是可以先将所有 $m$ 值相同的比赛分为一类，然后找每一类中最大的 $s$，即将所有 $m$ 值相同的比赛放在一起变成一个新比赛，其 $m$ 为原来这些比赛的 $m$，其 $s$ 为原来这些比赛的 $s$ 的最大值。然后在这些类比赛中二分。进一步优化，可以先预处理出前 $i$ 类比赛中 $s$ 的最大值，用数组存储。

# 代码


```
#include<bits/stdc++.h>
#define N 1000001
using namespace std;
map<int,int>mem;
struct match{
	int m,maxs;
}ma[N],mm[N];
struct tm2{
	int p,q;
}t[N];
int cmp(match a,match b){
	if(a.m!=b.m){
		return a.m<b.m;
	}
	else{
		return a.maxs>b.maxs;
	}
}//排序规则：先按m从小到大排序，m相同则用s从大到小排序
long long ans=0;
long long maxx[N];
int main(){
	int c,p,h=1;
	cin>>c>>p;
	for(int i=1;i<=c;i++){
		cin>>mm[i].m>>mm[i].maxs;
	}
	for(int i=1;i<=p;i++){
		cin>>t[i].p>>t[i].q;
	}
	sort(mm+1,mm+1+c,cmp);
	for(int i=1;i<=c;i++){
		if(!mem[mm[i].m]){
			mem[mm[i].m]=h;
			ma[h].m=mm[i].m;
			ma[h].maxs=mm[i].maxs;
			h++;
		}
	}//比赛分类
	maxx[0]=-1;
	for(int i=1;i<h;i++){
		maxx[i]=max(maxx[i-1],(long long)ma[i].maxs);
	}
	for(int i=1;i<=p;i++){
		int l=0,r=h-1,mid;
		while(l<r){
			mid=(l+r+1)>>1;
			if(ma[mid].m>t[i].p){
				r=mid-1;
			}
			else if(ma[mid].m<=t[i].p){
				l=mid;
			}
		}//二分找位置
		if(l>=h){
			l=h-1;
		}//这个题目质量很高，所有比赛都可以投
		ans+=max((long long)0,maxx[l]-t[i].q);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：signed_long_long (赞：0)

# 题目解法
暴力枚举每个题目投到比赛里的满意度最大值的时间复杂度 $O(cp)$ 肯定是会 TLE 的。

可以发现，如果 $q_i\ge q_j$ 且 $q_i<m_k$（即如果第 $j$ 个问题的质量小于等于第 $i$ 个问题的质量且编号为 $k$ 的比赛不接受第 $i$ 题），那么第 $k$ 个比赛肯定也不接受第 $j$ 题。

所以可以考虑按照 $m$ 和 $q$ 把比赛和题目降序排序，然后再枚举题目，再枚举比赛。而如果第 $i$ 题不被第 $j$ 个比赛接受，那么第 $i+1$ 题也不会被第 $1\sim j$ 个比赛接受，接下来枚举第一个能接受第 $i$ 题的比赛，用 $j$ 表示，预处理第 $j\sim c$ 个比赛的最大满意度，如果最大满意度大于把第 $i$ 题投出去要消耗的满意度，那么答案增加最大满意度。


代码片段：
```cpp
for(int i=1;i<=p;i++){
	while(g[last].a>h[i].a and last<=c) last++;
	if(last>c) return printf("%lld\n",ans),0;
	if(maxn[last]>h[i].b) ans+=maxn[last]-h[i].b;
}
```

---

