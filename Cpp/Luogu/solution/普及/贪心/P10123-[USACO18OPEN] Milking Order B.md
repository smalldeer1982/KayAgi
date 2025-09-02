# [USACO18OPEN] Milking Order B

## 题目描述

Farmer John 的 $N$ 头奶牛（$2\le N\le 100$），方便起见仍然编号为 $1\ldots N$，正好闲得发慌。因此，她们发展了一个与 Farmer John 每天早上为她们挤牛奶的时候的排队顺序相关的复杂的社会结构。经过若干周的研究，Farmer John 发现这个结构基于两个关键特性。

首先，由于奶牛们的社会阶层，某些奶牛会坚持要在其他奶牛之前挤奶，基于她们的社会地位等级。比方说，如果奶牛 $3$ 有最高的地位，奶牛 $2$ 位于中等地位，奶牛 $5$ 是低地位，那么奶牛 $3$ 会最早挤奶，然后是奶牛 $2$，最后是奶牛 $5$。

然后，有些奶牛只允许她们在排队顺序中一个特定的位置挤奶。比方说，奶牛 $4$ 可能坚持要在所有奶牛中的第二位挤奶。

幸运的是，Farmer John 总是能够以一种满足所有这些情况的顺序给他的奶牛们挤奶。

不幸的是，奶牛 $1$ 最近生病了，所以 Farmer John 想要尽早给这头奶牛挤奶，使得她可以回到牛棚获得急需的休息。请帮助 Farmer John 求出奶牛 $1$ 可以在挤奶顺序中出现的最早位置。 

## 说明/提示

在这个例子中，Farmer John 有六头奶牛，其中奶牛 $1$ 生病了。他的挤奶顺序应该为奶牛 $4$ 在奶牛 $5$ 之前，奶牛 $5$ 在奶牛 $6$ 之前。此外，Farmer John 必须要第一个给奶牛 $3$ 挤奶，第三个给奶牛 $5$ 挤奶。

FJ 必须第一个给奶牛 $3$ 挤奶，由于奶牛 $4$ 必须要在奶牛 $5$ 之前，奶牛 $4$ 一定是第二个挤奶的，然后奶牛 $5$ 第三个。于是，奶牛 $1$ 最早在挤奶顺序中出现的位置是第四个。 

## 样例 #1

### 输入

```
6 3 2
4 5 6
5 3
3 1```

### 输出

```
4```

# 题解

## 作者：CD_Sun_doer (赞：7)

#### 题目： [P10123 [USACO18OPEN] Milking Order B](https://www.luogu.com.cn/problem/P10123)


---


### 主要思路：

本题主要思想是贪心，模拟起来分类讨论情况容易掉点，需要细心与耐心，贪心策略倒是不难想：  
1. 最一般的情况，奶牛 1 号不在 $m$ 或 $k$ 中，此时将奶牛 1 **越靠前排越好** （还要把整个社会阶层的尽可能往 **后** 排）。  
1. 特殊情况奶牛 1 在 $k$ 中，则直接输出即可。  
1. 奶牛 1 如果在 $m$ 社会阶层中，则将 1 号及 1 号之前成员全部尽可能往前排。

如果还不懂可以看着代码自己推演一下，代码注释详细：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int cow_pos[111];//奶牛所在位置 
bool pos_cow[111];//第i个位置是否有奶牛 
int a[111];//m头有社会阶层的奶牛，挤奶先后顺序已定 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); 
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	for(int i=1;i<=k;i++){
		int cow,pos;
		cin>>cow>>pos;
		pos_cow[pos]=true;
		cow_pos[cow]=pos;
		if(cow==1){
			//特殊情况,一号奶牛位置已定直接输出 
			cout<<pos;
			return 0;
		}
	}
	int now_pos=n;//当前所在位置
	//倒叙遍历 
	for(int i=m;i>=1;i--){
		if(cow_pos[a[i]]){
			now_pos=cow_pos[a[i]]-1;
			//如果奶牛a[i]位置已定则当前位置为a[i]位置前一位
			continue;
		}
		if(a[i]==1){//__如果社会阶层中有1则尽可能往前排 
			int cnt=1,begi=1;
			for(int j=1;j<i;j++){//1号及社会阶层中1号之前的成员都尽可能往前排 
				if(cow_pos[a[j]]){
					begi=cow_pos[a[j]]+1;
					cnt=1;//社会阶层中1号前的成员如果有确定位置的要重置cnt 
					continue;
				}++cnt;
			}
			for(int j=begi;j<=n;j++){
				if(!pos_cow[j]){
					pos_cow[j]=true;
					cnt--;
				}
				if(!cnt){//社会阶层中1号之前奶牛位置已定，则直接输出 
					cout<<j;
					return 0;
				}
			}
		}else{//__否则尽可能排的靠后 
			while(pos_cow[now_pos]){
				now_pos--;
			}
			pos_cow[now_pos--]=true;
		}
	}
	//按照策略排好后，从前往后找空位，越靠前越好 
	for(int i=1;i<=n;i++){
		if(!pos_cow[i]){//找到直接输出 
			cout<<i;
			return 0;
		}
	}
	return 0;
} 
```  
~~也是侥幸拿下总运行时间的最优解之一。~~

---

## 作者：DeepSleep_Zzz (赞：2)

**begin**

# Part 1 题目大意

题目已经讲得很清楚了，我们只需要找到奶龙 $1$ 最早可以出现的位置即可。

# Part 2 解题思路

这题的本质就是分类讨论，考我们的分类思想，一看数据范围也很小，所以果断选择模拟（~~标签里的贪心纯废话~~），注意别漏点就行。

1. 第一种最好想，$1$ 在 $K$ 里直接输出。
2. 当 $1$ 在 $M$ 里时把他和他前面的家属尽量往前排。
3. 最普通的情况，当 $1$ 既不在 $K$ 里也不在 $M$ 里时，把所有的奶龙都往后排，然后从前往后找第一个空地儿。

# Part 3 Code


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
# define 我才是奶龙 return 0  // 别直接化身CVer，你谷会CE。。（但是语法没错误，VScode能跑。）
ll n,m,k;
ll ord[110]; // 存储社会阶层
ll cow[110]; // 存储每个奶龙的位置
bool pos[110]; // 判断每个位置是否有奶龙
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for (ll i=1;i<=m;i++)
    {
        cin>>ord[i];
    }
    for (ll i=1;i<=k;i++)
    {
        ll c,p;
        cin>>c>>p;
        cow[c]=p;
        pos[p]=1;
        if (c==1) // 情况1
        {
            cout<<p;
            我才是奶龙;
        } // 摊牌
    }
    ll now=n;
    for (ll i=m;i>=1;i--)
    {
        if (cow[ord[i]])
        {
            now=cow[ord[i]]-1;
            continue;
        }
        if (ord[i]==1) // 情况2.1
        {
            ll bgn=1,cnt=1;
            for (ll j=1;j<i;j++)
            {
                if (cow[ord[j]])
                {
                    bgn=cow[ord[j]]+1;
                    cnt=1;
                } // 我们只需要把这只奶龙（的下一只）到奶龙1安顿好就可以了 所以cnt要重置
                else
                {
                    cnt++;
                } // 统计需要安顿的龙数量
            }
            for (ll j=bgn;j<=n;j++)
            {
                if (!pos[j])
                {
                    pos[j]=1;
                    cnt--;
                } // 见缝插龙
                if (cnt==0)
                {
                    cout<<j;
                    我才是奶龙;
                } // 都安顿完了直接输出 然后摊牌
            }
        }
        else // 情况2.2
        {
            while (pos[now])
            {
                now--;
            } // 那就往后排吧
            pos[now--]=1;
        }
    }
    for (ll i=1;i<=n;i++) // 情况3
    {
        if (!pos[i]) // 见缝插龙（梅开二度）
        {
            cout<<i;
            我才是奶龙;
        }
    }
    我才是奶龙;
}
```

**end**（期末考完试彻底癫狂。。望见谅。。。。）

---

## 作者：zy567 (赞：1)

# 大意：
给定一些奶牛，它们有的形成社会阶层，有的需要特定位置，求放到哪里才能让奶牛 $1$ 尽快挤完奶。
# 思路：
分两种情况讨论：

第 $1$ 只奶牛包含在 $K$ 头奶牛当中，直接输出即可。

如果不包含，那么则看第 $1$ 只奶牛是否包含在 $M$ 头奶牛当中：

如果包含，则把 $1$ 号奶牛尽量往前放。

如果不包含，那么把所有包含在序列当中的奶牛尽量往后放，放完了之后，剩余的奶牛顺序已经无关，此时把 $1$ 号奶牛尽量往前放即可。
# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
bool b1[N],b2[N];
int p[N],sum[N],a[N],b[N],n,m,k;
bool check(){
	for(int i=0;i<n;i++) b1[i]=b2[i]=0;
	for(int i=0;i<k;i++){
		if(b1[a[i]]&&p[a[i]]==b[i]) continue;
		if(b1[a[i]]) return 0;
		if(b2[b[i]]) return 0;
		b1[a[i]]=1;
		b2[b[i]]=1;
		p[a[i]]=b[i];
	}
	int j=0;
	for(int i=0;i<m;i++){
		int c=sum[i];
		if(b1[c]){
			if(j>p[c]) return 0;
			j=p[c];
			continue;
		}
		while(b2[j]){
			j++;
			if(j==n) return 0;
		}
		b2[j]=1;
		p[c]=j;
	}
	return 1;
}
int main(){
	cin>>n>>m>>k;
	for(int i=0;i<m;i++){
		cin>>sum[i];
		sum[i]--;
	}
	for(int i=0;i<k;i++){
		cin>>a[i]>>b[i];
		a[i]--;b[i]--;
	}
	k++;
	for(int i=0;i<n;i++){
		a[k-1]=0;
		b[k-1]=i;
		if(check()){
			cout<<i+1;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：_weishiqi66_ (赞：1)

贪心。简单记录一下思路。

对于奶牛 $1$ 我们要让他尽可能地早挤奶。同时要满足两个条件。
1. 特定的奶牛要在特定的时候挤奶
2. 奶牛阶级中，排在后面的奶牛，不能在前面的奶牛之前挤奶

我们分类讨论一下

情况一，奶牛 $1$ 是特定的奶牛，那么答案就是他对应的特定位置。不可能更早，要不然无法满足题目条件。

情况二，奶牛 $1$ 是在奶牛阶级中。那么我们就希望奶牛阶级的奶牛们排在越前面越好。

情况三，奶牛 $1$ 不在奶牛阶级中。我们就希望奶牛阶级的奶牛们拍的越后越好，把奶牛阶级尽可能地往后面排，而奶牛 $1$ 只需要找最前面的一个空位即可。

具体操作见代码

```
#include <bits/stdc++.h>
using namespace std;


const int N=1e6;
int n,m,k,ran[N],ans[N];
int pd,f[N];
struct code {
	int x,p;
}c[N];
bool cmp(code v1,code v2) {
	return v1.p<v2.p;
}

int main() {
	//freopen("in.txt","r",stdin);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) {
		cin>>ran[i];
		if(ran[i]==1) pd=i;
		f[ran[i]]=i;
	}
	for(int i=1;i<=k;i++) {
		cin>>c[i].x>>c[i].p;
		ans[c[i].p]=c[i].x;
		if(c[i].x==1) {
			cout<<c[i].p;
			return 0;
		}
	}
	sort(c+1,c+1+k,cmp);
	if(pd==0) {
		for(int i=1;i<=n;i++) {
			int x=c[i].x,p=c[i].p;
			if(f[x]!=0) {
				ran[f[x]]=0;
				for(int j=f[x]-1;j>=1;j--) {
					while(ans[p]!=0) p--;
					ans[p]=ran[j];
					ran[j]=0;
				}
			}
		}
		for(int i=1;i<=n;i++) {
			if(ans[i]==0) {
				cout<<i;
				return 0;
			}
		}
	}
	else {
		int ansj=1,cj=1;
		for(int i=1;i<=n;i++) {
			int x=c[i].x,p=c[i].p;
			if(f[x]!=0) {
				while(cj<f[x]) {
					if(ran[cj]!=0) {
						while(ans[ansj]!=0) ansj++;
						ans[ansj]=ran[cj];
						ran[cj]=0;
					}
					cj++;
				}
				ansj=c[i].p+1;
				cj=f[x]+1;
			}
			
		}
		if(cj<=pd) {
			for(cj;cj<=pd;cj++) {
				while(ans[ansj]!=0) ansj++;
				ans[ansj]=ran[cj];
				ran[cj]=0;
			}
		}
		
		for(int i=1;i<=n;i++) {
			if(ans[i]==1) {
				cout<<i;
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：39xiemy (赞：1)

## 题目大意

有 $N$ 头编号为 $1 \sim N$ 的奶牛和 $N$ 个从左到右编号为 $1 \sim N$ 的空位。其中有 $M$ 头奶牛 $m_i$ 必须按输入时的顺序排列，两两之间可以插入其他奶牛；有 $K$ 头奶牛 $c_i$ 必须在第 $p_i$ 个空位。在满足上述要求的情况下，求奶牛 $1$ 能出现的最靠前的位置。

## 分析

由于有两种不同的要求，所以需要进行分类讨论：

1. 当奶牛 $1$ 在 $K$ 头奶牛中时，直接输出奶牛 $1$ 所对应的 $p_i$。

1. 当奶牛 $1$ 在 $M$ 头奶牛中时，令奶牛 $1$ 在 $M$ 头奶牛中的第 $t$ 个位置。先从 $t \sim 1$ 找到第一头位置确定的奶牛 $m_i$，然后根据贪心的思想，奶牛 $m_i$ 的后面第 $t-i$ 个空位即为奶牛 $1$ 所在的位置；若没有找到，从位置 $1$ 开始的第 $t$ 个空位即为奶牛 $1$ 所在的位置。

1. 当奶牛 $1$ 既不在 $M$ 头奶牛中也不在 $K$ 头奶牛中时，让 $M$ 头奶牛尽量往后排，然后输出从 $1$ 开始的第一个空位即可。

时间复杂度为 $O(N^2)$。

## 代码

代码为格式化后的：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,t,bj[102],now,b[102],c,p,v,bjn[102],cnt;
int main() {
	cin>>n>>m>>k;
	for(int i=1; i<=m; i++) cin>>b[i],t+=(b[i]==1)*i;
	for(int i=1; i<=k; i++) {
		cin>>c>>p;
		bj[p]=c,bjn[c]=p;
		if(c==1) { //当奶牛1在K头奶牛中时，直接输出
			cout<<p;
			return 0;
		}
	}
	if(t) { //当奶牛1在M头奶牛中时
		for(int i=t-1; i>=1; i--) {
			if(bjn[b[i]]) {
				now=bjn[b[i]],v=t-i;
				break;//找到奶牛1前面的第一头位置确定的奶牛并记录下位置以及奶牛1和它中间之间有几头奶牛(包含奶牛1)
			}
		}
		if(!now) v=t; //若没找到，就从位置1开始找到第t个空位
		while(1) {
			if(!bj[++now]) {
				if(++cnt==v) {
					cout<<now;
					return 0;
				}
			}
		}
	}
	now=n+1; //当奶牛1不在K头和M头奶牛中时，将M头奶牛尽量往后排
	for(int i=m; i>=1; i--) {
		if(!bjn[b[i]]) {
			while(1) {
				if(!bj[--now]) {
					bj[now]=b[i];
					break;
				}
			}
		} else now=bjn[b[i]];//要注意M头奶牛中的第bi只奶牛可能已经确定位置
	}
	for(int i=1; i<=n; i++) {
		if(!bj[i]) {//找到第1个空位输出 
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：__Sky__Dream__ (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P10123)

## 题目大意
给定一些奶牛，它们有的形成社会阶层，有的需要特定位置，求放到哪里才能让奶牛 $1$ 尽快挤完奶。

## 解题思路
想让奶牛 $1$ 尽快挤完奶，就得让它**尽量靠前**，那么就有三个情况：

1. 奶牛 $1$ 在 $K$ 头奶牛中，则直接输出其位置即可；
1. 奶牛 $1$ 在 $M$ 头奶牛中，使劲**往前放**；
1. 奶牛 $1$ 不在这两个序列内，则把序列内的奶牛使劲**往后放**，把奶牛 $1$ 使劲**往前放**。

我们以样例为例：在这个例子中，Farmer John 有六头奶牛，他的挤奶顺序应该为奶牛 $4$ 在奶牛 $5$ 之前，奶牛 $5$ 在奶牛 $6$ 之前。此外，Farmer John 必须要第一个给奶牛 $3$ 挤奶，第三个给奶牛 $5$ 挤奶。Farmer John 必须第一个给奶牛 $3$ 挤奶，由于奶牛 $4$ 必须要在奶牛 $5$ 之前，奶牛 $4$ 一定是第二个挤奶的，然后奶牛 $5$ 第三个。于是，奶牛 $1$ 最早在挤奶顺序中出现的位置是第四个。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool bo1[100];
bool bo2[100];
int pos[100];
int N,M,K;
int ord[100];
int cow1[101];
int cow2[101];
bool check()
{
    for(int i=0;i<N;i++)
        bo1[i]=bo2[i]=0;
    for(int i=0;i<K;i++)
    {
        if(bo1[cow1[i]]&&pos[cow1[i]]==cow2[i]) continue;
        if(bo1[cow1[i]]) return 0;
        if(bo2[cow2[i]]) return 0;
        bo1[cow1[i]]=1;
        bo2[cow2[i]]=1;
        pos[cow1[i]]=cow2[i];
    }
    int j=0;
    for(int i=0;i<M;i++)
    {
        int cow=ord[i];
        if(bo1[cow])
        {
            if(j>pos[cow]) return 0;
            j=pos[cow];
            continue;
        }
        while(bo2[j])
        {
            j++;
            if(j==N)
                return 0;
        }
        bo2[j]=1;
        pos[cow]=j;
    }
    return 1;
}
  
int main()
{
    cin>>N>>M>>K;
    for(int i=0;i<M;i++)
    {
        cin>>ord[i];
        ord[i]--;
    }
    for(int i=0;i<K;i++)
    {
        cin>>cow1[i]>>cow2[i];
        cow1[i]--;
		cow2[i]--;
    }
    K++;
    for(int i=0;i<N;i++)
    {
        cow1[K-1]=0;
        cow2[K-1]=i;
        if(check())
        {
            cout<<i+1;
            return 0;
        }
    }
    return 0;
}
```
欢迎大家指出错误！

---

## 作者：ICU152_lowa_IS8 (赞：1)

一道入门分类讨论题，细节不是特别多也不是特别坑，~~但是是真的难调而且数据不是特别水漏点还不行~~。

首先分两种情况讨论：

第 $1$ 只奶牛包含在 $K$ 头奶牛当中，直接输出即可。

如果不包含，那么则看第 $1$ 只奶牛是否包含在 $M$ 头奶牛当中：

如果包含，则**把 $1$ 号奶牛尽量往前放**。

如果不包含，那么把所有包含在序列当中的奶牛**尽量往后放**，放完了之后，剩余的奶牛顺序已经无关，此时把 $1$ 号奶牛尽量往前放即可。

如果如上叙述看不懂可以结合代码理解。

时间复杂度 $O(N)$（会发现代码中内层循环最多扫了两遍数组，所以复杂度不是 $O(NM)$ 的）。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int a[1005];//M头奶牛的序列 
int p[1005];//第i个位置放置的奶牛 
int put[1005];//第i头奶牛放置的位置 
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		p[y]=x;//序列中放入奶牛 
		put[x]=y;//记录 
		if(x==1){//判断 
			cout<<y;
			return 0;
		}
	}
	int now=n;//当前奶牛放在什么位置 
	for(int i=m;i>=1;i--){
		if(put[a[i]]){//如果放过了，剩下所有的奶牛一定要放在它的前面（因为搜索是逆序） 
			now=put[a[i]]-1;
			continue;
		}
		if(a[i]==1){
			int cnt=1,start=1;//在第1头奶牛前面的最后的一头没有被放置过的奶牛可以被放在start位置，从后面有连续cnt头奶牛需要被放置 
			for(int j=1;j<i;j++){
				if(put[a[j]]){
					start=put[a[j]]+1;
					cnt=1;//注意这里要归1 
					continue;
				}
				cnt++;
			}
			for(int j=start;j<=n;j++){
				if(!p[j])cnt--;
				if(cnt==0){//第1头奶牛将被放置 
					cout<<j;
					break;
				}
			}
			return 0; 
		}
		else{
			while(p[now]){//尽量往后放 
				now--;
			}
			p[now]=a[i];
		}
	}
	for(int i=1;i<=n;i++){
		if(!p[i]){//全部放置完之后检查最靠前的未被放置的奶牛 
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：tder (赞：1)

考虑枚举第 $1$ 头牛的位置 $t$。

用 $v_i=1$ 表示已经确定有牛第 $i$ 个挤奶，$c_i=1$ 表示已经确定第 $i$ 牛挤奶的排位，$p_i$ 表示第 $i$ 牛挤奶的排位。

那么，对于第 $1$ 头牛，显然，有：

$$
\begin{cases}
v_t=1 \\
c_1=1 \\
p_1=t
\end{cases}
$$

接下来，考虑已确定排位的 $k$ 头牛，若第 $a_i$ 头牛的位置为 $b_i$，则有：

$$
\begin{cases}
v_{b_i}=1 \\
c_{a_i}=1 \\
p_{a_i}=b_i
\end{cases}
$$

特别地，若在操作前已经确定有牛第 $b_i$ 个挤奶，或已经确定第 $a_i$ 牛挤奶的排位，即 $v_{b_i}=1$ 或 $c_{a_i}=1$，无解。

有贪心策略将剩余牛放在当前最靠前的不确定的排位 $q$。由题意，若用 $s_i$ 表示已规定挤奶顺序的 $m$ 头牛，则 $p_{s_1}<p_{s_2}<\cdots<p_{s_m}$。那么：

$$
\begin{cases}
v_{q}=1 \\
c_{s_i}=1 \\
p_{s_i}=q
\end{cases}
$$

无解情况同上。

初始时 $q=1$，每次操作后将 $q$ 后移至第一个不确定的排位。若 $q>n$，无解。

时间复杂度 $O(N^2)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e2 + 5;
int n, m, k, s[N], a[N], b[N], p[N];
bool v[N], c[N];
bool check(int t) {
    memset(v, 0, sizeof(v)); memset(c, 0, sizeof(c)); memset(p, 0, sizeof(p));
    v[t] = c[1] = 1; p[1] = t;
    for(int i = 1; i <= k; i++) {
        if(v[b[i]] || c[a[i]]) return 0;
        v[b[i]] = c[a[i]] = 1; p[a[i]] = b[i];
    }
    int q = 1;
    for(int i = 1; i <= m; i++) {
        if(c[s[i]]) {
            if(q > p[s[i]]) return 0;
            q = p[s[i]];
        } else {
            while(v[q]) {
                q++;
                if(q > n) return 0;
            }
            v[q] = 1; p[s[i]] = q;
        }
    }
    return 1;
}
signed main() {
    cin>>n>>m>>k;
    for(int i = 1; i <= m; i++) cin>>s[i];
    for(int i = 1; i <= k; i++) cin>>a[i]>>b[i];
    for(int i = 1; i <= n; i++) if(check(i)) {
        cout<<i<<endl;
        break;
    }
    return 0;
}
```

---

## 作者：125125A (赞：0)

# 前言
随机跳题跳过来的，当我看见 $834$ 提交但是只有 $138$ 通过的时候，我还以为是什么世纪级难题。
# 正文
[题目传送门](https://www.luogu.com.cn/problem/P10123)
## 题目大意
给定一些奶牛，它们有的形成社会阶层，有的需要特定位置，求放到哪里才能让奶牛 $1$ 尽快挤完奶。
## 思路
想让奶牛 $1$ 尽快挤完奶，就得让它尽量靠前，那么就有三个情况：

1. 如奶牛 $1$ 在 $K$ 头奶牛中，直接输出其位置即可；

1. 如奶牛 $1$ 在 $M$ 头奶牛中，则把奶牛 $1$ 往前放；

1. 如奶牛 $1$ 不在这两个序列内，则把序列内的奶牛往后放，把奶牛 $1$ 往前放。
## Code:

```
#include<bits/stdc++.h>
using namespace std;

bool b1[100], b2[100];
int pos[100];
int N, M, K;
int sum[100];
int arr[101];
int brr[101];

bool check() {
	for (int i = 0; i < N; i++)
		b1[i] = b2[i] = 0;
	for (int i = 0; i < K; i++) {
		if (b1[arr[i]] && pos[arr[i]] == brr[i]) continue;
		if (b1[arr[i]]) return 0;
		if (b2[brr[i]]) return 0;
		b1[arr[i]] = 1;
		b2[brr[i]] = 1;
		pos[arr[i]] = brr[i];
	}
	int j = 0;
	for (int i = 0; i < M; i++) {
		int cow = sum[i];
		if (b1[cow]) {
			if (j > pos[cow]) return 0;
			j = pos[cow];
			continue;
		}
		while (b2[j]) {
			j++;
			if (j == N)
				return 0;
		}
		b2[j] = 1;
		pos[cow] = j;
	}
	return 1;
}

int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		cin >> sum[i];
		sum[i]--;
	}
	for (int i = 0; i < K; i++) {
		cin >> arr[i] >> brr[i];
		arr[i]--;
		brr[i]--;
	}
	K++;
	for (int i = 0; i < N; i++) {
		arr[K - 1] = 0;
		brr[K - 1] = i;
		if (check()) {
			cout << i + 1;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：csxx601cjy (赞：0)

## P10123 [USACO18OPEN] Milking Order B 题解

[AC 记录](https://www.luogu.com.cn/record/178553461)  
[查看题目](https://www.luogu.com.cn/problem/P10123)  
[在专栏中阅读](https://www.luogu.com.cn/article/epfrioen)

## 题意
奶牛挤奶时要根据社会地位或者固定位置挤奶，求奶牛 $1$ 的最前挤奶位置。

## 思路
贪心分三种情况：
1. 奶牛 $1$ **固定位置**，直接输出即可。
2. 奶牛 $1$ 有**社会地位**，尽量把地位大的在符合要求的情况下靠前放，奶牛 $1$ 也尽量往前放。
3. **既没有固定位置，也没有社会地位**，让有社会地位的在符合要求的情况下靠后放，奶牛 $1$ 尽量往前放。

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
const int n=110;
int N,M,K,m[n],c[n],p[n],a[n],t[n],x=0,l=0;//a[i]是第i个挤奶的牛编号,t是桶
int main(){
	cin>>N>>M>>K;
	for(int i=1;i<=N;i++)a[i]=t[i]=0;
	for(int i=1;i<=M;i++){
		cin>>m[i];
		if(m[i]==1)x=1;//奶牛1有社会关系
	}
	for(int i=1;i<=K;i++){
		cin>>c[i]>>p[i];
		a[p[i]]=c[i];//牛ci一定要放在pi位
		t[c[i]]=1;//桶记录固定位置的牛
		if(c[i]==1) {cout<<p[i];return 0;}//奶牛1固定位置,直接输出
	}
	if(x){//奶牛1有社会关系
		for(int i=1;i<=N;i++){//尽量靠前放
			if(a[i]==m[l+1]) l++;//固定位置直接跳过
			else if(!a[i] && !t[m[l+1]]){
				a[i]=m[++l];//否则直接放
				if(m[l]==1) {cout<<i;return 0;}//牛1找到位置
			}
		}
	}
	else{
		for(int i=N;i>0;i--){//尽量靠后放
			if(a[i]==m[M]) M--;//固定位置直接跳过
			else if(!a[i] && M>0 && !t[m[M]]) a[i]=m[M--];//否则直接放
		}
		for(int i=1;i<=n;i++) if(!a[i]) {cout<<i;return 0;}//牛1找到位置
	}
	return 0;
}
```
此代码时空复杂度比较小，代码行数 35 也比较小，本萌新认为比较好理解。  
欢迎大家作出评价！

---

## 作者：yanlikun (赞：0)

# **思路**
题意就不一一赘述，很容易理解，但情况比较多，接下来我就来梳理一下：

1. 首先来看最简单的情况，若输入的 $c_i$ 中含有 $1$ ，直接输出即可。

1. 再来看输入的  $m_i$  中是否含有 $1$ ，具体看代码注释。

# **代码实现**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,mm[105],ans[105],where[105],tag;
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		cin>>mm[i];
		if(mm[i]==1)//标记1在m数组中所处的位置
			tag=i;
	}
	for(int i=1;i<=k;i++)
	{
		int c,p;
		cin>>c>>p;
		ans[p]=c;//记录已知数所处的位置以及放入答案序列
		where[c]=p;
	}
	where[mm[m+1]]=n+1;
	//因为要使1所处位置尽量靠前，分两部分处理
	for(int i=m;i>tag;i--)//部分一：1之后的m_i倒着处理，方便使1之后的m_i尽量在答案序列中靠后
	{
		if(where[mm[i]])
			continue;
		for(int l=where[mm[i+1]]-1;l>=1;l--)
			if(!ans[l])
			{
				ans[l]=mm[i];
				where[mm[i]]=l;
				break;
			}
	}
	where[mm[0]]=0;
	for(int i=1;i<=tag;i++)//部分二：1以及之前的m_i正着处理，使1之前的m_i尽量在答案序列中靠前，最终使得1也靠前
	{
		if(where[mm[i]])
			continue;
		for(int l=where[mm[i-1]]+1;l<=n;l++)
			if(!ans[l])
			{
				ans[l]=mm[i];
				where[mm[i]]=l;
				break;
			}
	}
	if(where[1])
	{
		cout<<where[1];
		return 0;
	}
	for(int i=1;i<=n;i++)//如未确定出1的位置，则选取答案序列中为空的位置中最靠前的
		if(!ans[i])
		{
			cout<<i;
			break;
		}
	return 0;
}
```

---

## 作者：44i11 (赞：0)

## 题意简述
有 $n$ 头奶牛需要挤奶，并且有 $m$ 头奶牛产生了阶级，阶级高的奶牛必须比阶级低的奶牛先挤奶，有 $k$ 头奶牛只允许她们在一个特定的位置挤奶，让你求第 $1$ 头奶牛最早可以在第几个挤奶。

## 解题思路
若要使第 $1$ 头奶牛更早地挤奶，应当考虑以下两种情况。

1. 奶牛 $1$ 在阶级中，那么只要把比他阶级高的奶牛尽量往前放，就能使奶牛 $1$ 更早的挤奶。
2. 奶牛 $1$ 不在阶级中，那么只要把有阶级的奶牛尽量往后放，就能使奶牛 $1$ 更早的挤奶。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 105;
ll a[N], n, m, k, b[N], c[N], vis[N];//vis[i]表示被安排在第i个位置的奶牛编号
bool flag;
ll find(ll x){//找到奶牛x在第几个挤奶
	for(int i = 1; i <= n; i++){
		if(vis[i] == x){
			return i;
		}
	}
	return -1;
}
int main(){
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++){
		cin >> a[i];		
		if(a[i] == 1){//证明奶牛1在阶级中
			flag = 1;
		}
	}
	for(int i = 1; i <= k; i++){
		cin >> b[i] >> c[i];
		vis[c[i]] = b[i];
	}
	ll tmp = 1;
	if(flag){//第一种情况
		for(int i = 1; i <= n;){
		    if(find(a[tmp]) != -1){
		    	i = find(a[tmp]) + 1;//阶级高的奶牛往前放
		    	tmp++;
		    	continue;
			}
			if(!vis[i]){
				vis[i] = a[tmp];
				if(a[tmp] == 1){
					cout << i;
					break;
				}
				tmp++;
			}
			i++;
		}
	}else{//第二种情况
    	for(int i = 1; i <= m; i++){
    		ll wz = find(a[i]), tmp = i;
    		if(wz != -1){
    			for(int j = wz - 1; j >= 1 && tmp != 1; j--){
    				if(!vis[j] && find(a[tmp - 1]) == -1){
    					vis[j] = a[--tmp];//有阶级的奶牛往后放
    				}
    			}
    		}
    	}
    	for(int i = 1; i <= n; i++){//因为阶级已经处理完了，所以没有被安排的最早位置就是奶牛1的最早挤奶位置
    	    if(!vis[i]){
    	        cout << i;
    	        break;
    	    }
    	}	    
	}
	return 0;
}
```

---

