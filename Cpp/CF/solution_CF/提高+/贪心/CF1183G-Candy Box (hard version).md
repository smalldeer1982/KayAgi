# Candy Box (hard version)

## 题目描述

本题是同场比赛中 D 题的一个变种，增加了一些额外的限制和任务。

有 $n$ 颗糖果放在一个糖果盒中。第 $i$ 颗糖果的类型为 $a_i$（$1 \le a_i \le n$）。

你需要用这些糖果中的一部分来准备一份礼物，满足以下限制：在礼物中，每种类型的糖果数量必须互不相同（例如，包含两颗 1 型糖果和两颗 2 型糖果的礼物是不合法的）。

某些类型的糖果可以完全不出现在礼物中。某些类型的糖果也可以只取其中一部分放入礼物。

你特别喜欢其中一些糖果，不想把它们放进礼物，而是想自己吃。对于每颗糖果，给定一个数 $f_i$，如果 $f_i = 0$，表示你想自己留着第 $i$ 颗糖果；如果 $f_i = 1$，表示你不介意把它放进礼物。同一种类型的两颗糖果，$f_i$ 的值可能不同。

你希望礼物中糖果的数量尽可能多，但又不想把太多自己想吃的糖果放进礼物。因此，你需要计算在满足条件的情况下，礼物中最多能包含多少颗糖果；在所有能达到最大数量的方案中，你还希望礼物中 $f_i = 1$ 的糖果数量尽可能多。

你需要回答 $q$ 个独立的询问。

如果你使用 Python 编程，建议提交时使用 PyPy 以提高运行效率。

## 说明/提示

在第一个询问中，你可以选择两颗 4 型糖果和一颗 5 型糖果，它们的 $f_i$ 都为 $1$，你不介意把它们送出去作为礼物。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
8
1 0
4 1
2 0
4 1
5 1
6 1
3 0
2 0
4
1 1
1 1
2 1
2 1
9
2 0
2 0
4 1
4 1
4 1
7 0
7 1
7 0
7 1
```

### 输出

```
3 3
3 3
9 5
```

# 题解

## 作者：Eibon (赞：6)

最多的糖果数量很好考虑。

只需从大到小排序，依次选取即可。

如何让 $f_{i}=1$ 的糖果数量最大呢？

考虑用优先队列进行维护。

对于选定的糖果，在比它糖果总数大的糖果中选出 $f_{i}=1$ 数量最多的糖果。这样一定是最优的，因为造成的损失最小。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int T,n,a,f,ans1,ans2,now,tot;
struct node
{
	int num[2];
	bool operator < (const node &x) const
	{
		return num[0]+num[1]<x.num[0]+x.num[1];
	}
};
node cnt[maxn];
priority_queue<int>q;
signed main()
{
    scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&a,&f);
			cnt[a].num[f]++;
		}
		sort(cnt,cnt+n+1);
		now=n;ans1=tot=0;
		for(int i=n;i;i--){
			while(now&&cnt[now].num[0]+cnt[now].num[1]>=i){
				q.push(cnt[now].num[1]);
				now--;
			}
			if(!q.empty()){
				ans1+=i;
				tot+=max(i-q.top(),0ll);
				q.pop();
			}
		}
		ans2=ans1-tot;
		printf("%lld %lld\n",ans1,ans2);
		while(!q.empty()){
			q.pop();
		}
		for(int i=1;i<=n;i++){
			cnt[i].num[0]=cnt[i].num[1]=0;
		}
	}
    return 0;
}
//dyyyyds
```

---

## 作者：wucstdio (赞：4)

感觉D题的思路对G题有一定的提示作用。

首先对于每一个种类记录一个$cnt_1$和$cnt_0$表示两种糖果的种类。为了方便令$cnt=cnt_1+cnt_0$

我们考虑D题的思路：将所有的$cnt$排序，然后从大到小贪心选取。

放到这道题上，为了选出来最优答案，我们还是需要将所有$cnt$排序后进行一次贪心，但是我们很快发现这样做并不能得到最大的$f_i=1$的数量。

怎么办呢？容易发现答案可以拆成若干个互不相同的数相加（就是贪心的过程中每一个种类的糖果选取的数量），那么我们可以想到，对于一个数$x$，能够凑出$x$这么多糖果的一定是数量大于等于$x$的糖果种类（这不是废话吗）。

接下来我们的问题就是对每一个$x$选择一个糖果种类$x_i$，使得最后$\sum\min(x,cnt_1[x_i])$最大。

所以对于一个数$x$，我们把所有$cnt\ge x$的都丢到一个集合中，然后选取集合中选取$cnt_1$最大的那个糖果种类加入答案中。

这样做一定是最优的，证明如下：

考虑最优答案，我们发现如果最优答案下$x$选择的不是$cnt_1$最大的，那么检查当前$cnt_1$最大的是否被选择，如果没有被选择，我们一定可以让$x$改选最大的，答案至少不会变劣。

如果$cnt_1$最大的已经被选择了，我们考虑选择$cnt_1$的那个数$y$与$x$的大小关系。如果$y<x$，那么就将$x,y$选择的进行交换，否则不会违反我们从大到小贪心的规则。

最后我们需要实现一个数据结构，支持插入和查询最大值，用一个堆就可以了。

时间复杂度$O(n\log n)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
int t,n,cnt0[200005],cnt1[200005],sa[200005];
priority_queue<int>q;
bool cmp(int a,int b)
{
	return cnt0[a]+cnt1[a]>cnt0[b]+cnt1[b];
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			if(y)cnt0[x]++;
			else cnt1[x]++;
			sa[i]=i;
		}
		while(!q.empty())q.pop();
		sort(sa+1,sa+n+1,cmp);
		int now=1,ans=0,num=0;
		for(int i=n;i>=1;i--)
		{
			while(cnt0[sa[now]]+cnt1[sa[now]]>=i)
			{
				q.push(cnt0[sa[now]]);
				now++;
			}
			if(q.empty())continue;
			int v=q.top();
			q.pop();
			ans+=i;
			num+=min(v,i);
		}
		printf("%d %d\n",ans,num);
		for(int i=1;i<=n;i++)cnt0[i]=cnt1[i]=0;
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

感觉 D 和 G 的差别不是很大。

首先为了总体最大，我每次一定会选择礼物数量最大，相同条件下选择 $f=1$ 的数量更多的。

那么会遇到一个问题，假如直接排好序，那么前面选过最大值了，到后面可能值也不是最大，$f=1$ 的数量也不是最多（参见样例）。

于是我们考虑使用优先队列动态的维护这个过程即可。

[示例代码。](https://www.luogu.com.cn/paste/z2fkvj75)

---

## 作者：Wf_yjqd (赞：0)

CF 评分虚高。。

------------

很显然的是，要转换题目条件为第 $i$ 个种类的总个数和想送出的个数，不然难以处理。

考虑总个数最大的优先级更高，所以一开始假设全都选，然后最小化不送的个数。

按总个数从大到小变量，对于数量相同的种类，放入优先队列中。

每遇到一个未达成的数量值，考虑将优先队列中想送出个数最大的留下，造成的浪费（想送出的个数 $-$ 实际送出的个数）一定最少，则整个过程中送出的想送出的最多。

模拟即可，复杂度 $\operatorname{O}(n\log n)$。

------------

感觉挺明白的，但光看思路确实有点难懂，可以结合代码悟一悟。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+84;
pair<ll,ll> Candy[maxn];//first为总个数，second为想送出的个数
ll T,n,a,f,top,ans1,ans2;
priority_queue<ll> pq;
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        for(ll i=1;i<=n;i++)
            Candy[i].first=Candy[i].second=0;
        for(ll i=1;i<=n;i++){
            scanf("%lld%lld",&a,&f);
            Candy[a].first++;
            if(f)
                Candy[a].second++;
        }
        sort(Candy+1,Candy+n+1);//先按总个数排序
        top=n;
        ans1=ans2=0;
        while(!pq.empty())
            pq.pop();
        for(ll i=n;i>=1;i--){
            while(top&&Candy[top].first>=i){//加入相同个数的
                pq.push(Candy[top].second);
                top--;
            }
            if(!pq.empty()){//取想送出个数最多的一个
                ans2+=i;
                ans1+=max(0ll,i-pq.top());
                pq.pop();
            }
        }
        printf("%lld %lld Sherry\n",ans2,ans2-ans1);
    }
    return 0;
}
```


---

