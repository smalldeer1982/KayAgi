# Enduring Exodus

## 题目描述

In an attempt to escape the Mischievous Mess Makers' antics, Farmer John has abandoned his farm and is traveling to the other side of Bovinia. During the journey, he and his $ k $ cows have decided to stay at the luxurious Grand Moo-dapest Hotel. The hotel consists of $ n $ rooms located in a row, some of which are occupied.

Farmer John wants to book a set of $ k+1 $ currently unoccupied rooms for him and his cows. He wants his cows to stay as safe as possible, so he wishes to minimize the maximum distance from his room to the room of his cow. The distance between rooms $ i $ and $ j $ is defined as $ |j-i| $ . Help Farmer John protect his cows by calculating this minimum possible distance.

## 说明/提示

In the first sample, Farmer John can book room $ 3 $ for himself, and rooms $ 1 $ and $ 4 $ for his cows. The distance to the farthest cow is $ 2 $ . Note that it is impossible to make this distance $ 1 $ , as there is no block of three consecutive unoccupied rooms.

In the second sample, Farmer John can book room $ 1 $ for himself and room $ 3 $ for his single cow. The distance between him and his cow is $ 2 $ .

In the third sample, Farmer John books all three available rooms, taking the middle room for himself so that both cows are next to him. His distance from the farthest cow is $ 1 $ .

## 样例 #1

### 输入

```
7 2
0100100
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 1
01010
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 2
000
```

### 输出

```
1
```

# 题解

## 作者：EXODUS (赞：9)

# Part 1：前言

一开始题读错了，还以为是所有人住的房间与牛住的房间，题面好像有点歧义，管理员可以修改下。

>希望人住的房间离最远的牛的房间位置尽量小

改为

>希望 Farmer John 住的房间离最远的牛的房间位置尽量小

# Part 2：正文

首先注意到题面里有这样一句话：
>希望人住的房间离最远的牛的房间位置尽量小。

最大值最小就可以直接无脑上二分了，这边给出两种二分方法。

1. 二分答案，问题转化为是否存在一个 $i$，满足距离其不超过 $x$ 的房子中有不少于 $k+1$ 个空房间，也就是 $[i-x,i+x]$ 中空房子数量，前缀和优化可做到 $O(n)$ 判断，时间复杂度 $O(n\log n)$。

2. 对每个位置进行二分，求出其能装下 $k+1$ 个人的最小距离，依然可以用前缀和优化，最后对所有位置的最小距离取 $\min$ 即可。

代码给的是第一种实现方式。~~好像是最快的？~~


# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}
const int N=1e5+7;
int n,k;
int sum[N];
char s[N];
bool check(int x){
	for(int i=1;i<=n;i++){
		if(s[i]!='0')continue;
		int l=max(i-x,1),r=min(i+x,n);
		if(sum[r]-sum[l-1]>=k+1)return 1;
	}return 0;
}
int main(){
	n=read(),k=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(s[i]=='0');
	int l=0,r=n,ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}printf("%d\n",ans);
	return 0;
}
```
# Part 4：后文
点赞再走吧（可怜

---

## 作者：Priori_Incantatem (赞：4)

这题有很多做法，单调队列/双指针+二分  
这里讲一个最简单的，既不用双指针也不用单调队列

首先，输入时我们把可以住的房间都给筛出来，并储存下它们的位置

然后，由于题目给定了需要 $k+1$ 个房间，我们就枚举长度为 $k+1$ 的连续区间，用二分查找找出最靠近中间的的那间房（让农夫住在这里），并算出离两端的距离。

最后取最小值即可

```cpp
#include<cstdio> 
#include<iostream>
using namespace std;
const int Maxn=100000+10,inf=0x3f3f3f3f;
int n,k,cnt,ans=inf;
int a[Maxn];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&n,&k); // 这里 k 没有加1，是为了后面计算的方便
	char s[Maxn];
	scanf("%s",s+1);
	for(int i=1;i<=n;++i)
	if(s[i]=='0')a[++cnt]=i; // 筛出空房
	n=cnt;
	for(int i=1;i+k<=n;++i)
	{
		int l=i,r=i+k;
		int tmp=(a[l]+a[r])>>1;
		while(l<r)
		{
			int mid=(l+r)>>1;
			++mid;
			if(a[mid]<=tmp)l=mid;
			else r=mid-1;
		}
		for(int j=min(l-2,i);j<=min(l+2,i+k);++j) // 为保险起见，我们也要查看一下相邻的几个房间
		ans=min(ans,max(a[j]-a[i],a[i+k]-a[j]));
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Pentiment (赞：2)

这里提供一种其它题解中没有的 $O(N)$ 做法。

显然 FJ 预定的 $k+1$ 个房间是连续的，并且有 **最大值最小** 的一类要求，因此可以考虑用双指针。

首先预处理出 `nxt` 数组，`nxt[i]` 表示 $i$ 下标对应的下一个空位（含本身）。枚举左端点，为了获取 FJ 距离牛的最远位置，我们还需要一个指针 `tmp` 表示 FJ 的最优位置。将 $l,r$ 移到合适的位置之后，直接跳转 `tmp` 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n, k, sum, ans = 0x7f7f7f7f, p, r = 1, nxt[MAXN], tmp;
char s[MAXN];
int main() {
    scanf("%d%d%s", &n, &k, s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0')
            nxt[p] = i, p = i;
    }
    nxt[p] = 0x7f7f7f7f;
    for (int l = 1; l <= n; l++) {
        if (s[l - 1] == '0')
            sum--;
        while (r <= n && sum < k + 1) {
            if (s[r] == '0')
                sum++;
            r++;
        }
        if (sum >= k + 1) {
            while (max(abs(nxt[tmp] - l), abs(r - 1 - nxt[tmp])) < max(abs(tmp - l), abs(r - 1 - tmp)))
                tmp = nxt[tmp];
            ans = min(ans, max(abs(tmp - l), abs(r - 1 - tmp)));
        }
    }
    printf("%d", ans);
}
```



---

## 作者：cqbzhr (赞：2)

这个题太水了，~~枉为黄题~~。

## 题意

人住的房间离最远的牛的房间位置最小。

说人话就是求最大值的最小值，然后我就笑了，直接上二分（尽管学校 oj 给的正解是双指针）。

## 正解

其实这道题就只是让我们在 $n$ 个空位里筛出 $k+1$ 个位置，使得人住的房间离最远的牛的房间位置最小。

设农夫约翰的位置为 $i$，牛的位置所在的区间长度为 $m$，且满足 $i$ 为 $m$ 的中位数。

令 $mid$ 为 $m$ 的二分之一，则牛的位置的区间范围即为 $[i-mid,i+mid]$。

- 用一个桶来记录空位置的下标 $t$，并找到最后一个空位。
- 对于 $t$ 进行二分，用 $ans$ 取出最远距离的最小值即可。

### AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,k,a[N],ans=INT_MAX,tmp,l,r,m;
char s[N];
int main(){
	scanf("%d%d\n%s",&n,&k,s);
	int t=0;
	for(int i=0;i<n;i++)
		if(s[i]=='0')
			a[t++]=i;
	for(int i=0;i+k<t;i++){
		tmp=(a[i+k]+a[i])/2;
		l=lower_bound(a,a+t-1,tmp)-a;
		ans=min(ans,max(a[l]-a[i],a[i+k]-a[l]));//距离最大值的最小值
		l--;
		ans=min(ans,max(a[l]-a[i],a[i+k]-a[l]));
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：yangzd (赞：1)

# 题目大意：

农夫带着他的牛们离家出走了，他们到了一个旅店，旅店房间状况通过一个 $01$ 串告诉你，$0$ 代表空的，$1$ 代表被占了，问怎么安排住宿可以使牛离农夫的最远距离最小。

# 分析：

通过前缀和处理出某个位置之前的 $0$ 的个数，然后二分枚举对于位置 $i$ 的左右两边可以放置下所有牛的最小距离。然后输出最小的那个一个就可以了。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[100005],n,m;
char x[100005];

bool check(int pos,int dis)
{
    int l=max(pos-dis,1);
	int r=min(pos+dis,n);
    
    return a[r]-a[l-1]>=m+1;
}

signed main()
{
	ios::sync_with_stdio(0);
	
	cin >> n >> m;

	cin >> x+1;
	
    memset(a,0,sizeof a);
    
    for (int i=1; i<=n; i++)
    {
        if(x[i]=='0')
            a[i]=a[i-1]+1;
            
        else
			a[i]=a[i-1];
    }

    int l,r,mid,ans=999999;
    
    for (int i=1; i<=n; i++)
    {
        if(x[i]=='1')
			continue;
				
        l=1,r=n;
            
        while(l<r)
        {
            mid=(l+r)/2;
                
            if(check(i,mid))
               r=mid;
                    
            else
				l=mid+1;
        }
            
        ans=min(ans,r);
    }
        
    cout << ans << endl;
}
```

---

