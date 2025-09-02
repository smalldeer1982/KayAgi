# [CEOI 2011] Teams

## 题目描述

有 $n$ 个小朋友要进行比赛，他们要被分为若干队伍。每一个小朋友都有一个要求，其中第 $i$ 个小朋友要求他所在的队伍最少要有 $a_i$ 个人（包括自己）。

现在请你求出一种划分方案，在满足所有小朋友的要求的情况下，最大化队伍的数量。同时在此基础上，请你最小化人数最多的队伍的人数。

## 说明/提示

对于 $100\%$ 的数据，有 $1\le n\le 1\ 000\ 000;1\le a_i\le n$，输入保证有解。

## 样例 #1

### 输入

```
5
2
1
2
2
3```

### 输出

```
2
2 4 2
3 5 1 3```

# 题解

## 作者：LlLlCc (赞：5)

这题网上好像找不到比较详细的题解

------------
先解决第一问，如何求出最大队伍数

我们先按$a_{i}$从小到大排序一趟，显然，如果$a_{i+1}$满足那么$a_{i}$也必定满足。手玩几组数据易得，每组人员都是连接在一起的，即：$a_{i},a_{i+1},a_{i+2},\ldots$

我们开两个数组来记录：

$Max_{i}$ : 前$i$个人最多分几组

$f_{i}$ : 第$i$个人为一组的结尾最多分几组

转移方程非常简洁，即：

$f_{i} = Max_{i-a_{i}}+1$

当然前提必须保证： $i>=a_{i}$ 且 $Max_{i-a_{i}}>=0$（或者说$Max_{i-a_{i}}$已经被更新过了）

再考虑如何更新$Max_{i}$

根据定义，$Max_{i}$ 表示前$i$个人最多分几组，所以 :

$Max_{i}=max(f_{i},Max_{i-1})$

初值: $Max_{0}=0$

$Ans=f_{n}$ （因为要满足每个小朋友，所以第$N$个小朋友必取，$Ans$为$f_{n}$而并非$Max_{n}$）

第一问做出来后第二问就容易了

看到“**最小化人数最多**的队伍的人数”，自然而然就会想到用二分来枚举答案

$mid$：人数最多的队伍人数

再开一个数组：

$Lst_{i}$： 枚举完第 $i$ 个人时上一组的结尾位置（思考

因为$mid$表示人数最多的队伍人数，所以: $i-Lst_{i-a_{i}}<=mid$

同时更新操作也和$Max$数组类似：

当$f_{i}>=Max_{i-1}$时：$Lst_{i}=i$ （新开一组，自己为结尾位置）

否则： $Lst_{i}=Lst_{i-1}$ （因为没有新开一组，上一组结尾位置即不变）

在满足组数最多的情况下，用二分来查找 $mid$ 的最小值，即为答案

详见代码：

```
#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;
int n,Ans,Min,Max[maxn],f[maxn],lst[maxn],L,R,mid;
struct lc{
	int x,id;
	bool operator <(const lc b)const{return x<b.x;}
}a[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline int check(int len){
	memset(lst,0,sizeof lst);
	memset(f,-1,sizeof f);
	memset(Max,-1,sizeof Max);
	Max[0]=0;int inf=Max[1];
	for (int i=1;i<=n;i++){
		if (a[i].x<=i&&Max[i-a[i].x]>=0&&lst[i-a[i].x]+len>=i) f[i]=Max[i-a[i].x]+1;     //判断是否能新成一个组 
		if (f[i]>=Max[i-1]) lst[i]=i,Max[i]=f[i];
		else lst[i]=lst[i-1],Max[i]=Max[i-1];
	}
	return f[n];           //返回最大组数 
}
int main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=(lc){read(),i};
	sort(a+1,a+n+1); 
	printf("%d\n",Min=check(n));     //记录最大组数 
	L=0,Ans=R=n;
	while (L<=R){
		mid=L+R>>1;
		if (check(mid)==Min) Ans=mid,R=mid-1;       //查找满足最大组数的前提下mid最小为多少 
		else L=mid+1;
	}
	check(Ans),R=n;       //最后要在check一遍来计算lst数组 
	while (R){  
		L=lst[R-a[R].x];
		printf("%d",R-L);
		for (int i=L+1;i<=R;i++) printf(" %d",a[i].id); //输出答案 
	    putchar('\n');R=L;
	}
	return 0;
}
```
#### 可能讲的不够详细，如有不懂的地方欢迎评论区留言或者私信

---

## 作者：FQ04gty (赞：0)

##### [原题链接](https://www.luogu.com.cn/problem/P4699)

---

我们将小朋友的需求从小到大排序。

我们发现，对于一个组，我们至少需要一个长度为其中小朋友要求最大值的子串。

理由如下：如果存在一个以某个小朋友结尾的队伍，那么选一些要求更高的小朋友在同一队伍中，一定比选一些要求更低的小朋友来得优。

那么我们考虑最大化这些构成组的小朋友的组数，设 $f_i$ 是  $a_i$ 从小到大排序后，考虑了前 $i$ 个小朋友，至多分多少组。

容易有转移方程 $f_i=\max(f_{i-1},f_{i-a_i}+1)$，特殊地，$f_t$ 只能从 $f_{t-a_t}$ 转移过来，因为必然存在一个以要求最高小朋友为结尾的组。

DP 出的方案先将其分组好，对于剩下的小朋友我们考虑二分：

设现在有 $n$ 个组，$m$ 个未分配的小朋友，答案为 $mid$。

显然，$mid$ 的下界为分好的组中人数最多的，上界为 $n$。

我们发现，要求高的小朋友，放在已经人数较多的组中，一定比把要求低的小朋友放在人数较多的组中更优。

因此我们贪心地把小朋友按从大到小地顺序，放入已有人数从大到小排序的组中，尽量放满。

这时，除了能放小朋友的最后一组没有放满，其它小朋友都放在一个满的组中，由于上文所说 $mid$ 的下界一定大于需求最大小朋友的需求，因此这些组达到了所有小朋友的要求。

那么对于最后一组我们考虑调整：

我们每次把倒数第二组要求最低的小朋友调到最后一组，直到最后一组满足要求。此时若倒数第二组空了，我们再从前面调。

从最后一组调整到第一组，若中途发现调整不下去了，就说明不存在这个答案的方案。

如果调整完，第一组依然合法，就说明存在合法方案。

##### 实现细节

调整小朋友的过程不必开多个桶，只需要维护每个桶的一个指针即可，所有操作都在一个长度为 $m$ 的，包含所有小朋友的桶中进行。

总时间复杂度 $O(n\log n)$。

### Code

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#define mid ((L+R)/2)
#define l(i) (r[i-1]+1)
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
const int SIZE=2e6+10;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x*10)+(ch^48),ch=getchar();
    return x;
}
vector<int>ans[SIZE];
pii a[SIZE],b[SIZE];
int t,lst,dp[SIZE],k[SIZE],v[SIZE],pre[SIZE],r[SIZE],maxn,n,m,cnt[SIZE];
inline bool check(int x)
{
    ll sum=0,tot=0;
    for(int i=1;i<=n;i++)sum+=(v[i]=x-k[i]);
    if(sum<m)return false;
    for(lst=1;lst<=n;lst++)
    {
        tot+=v[lst],r[lst]=tot;
        if(tot>=m){r[lst]=m;break;}
    }
    if(tot==m)return true;
    r[lst+1]=m+1;
    for(int i=lst;i>1;i--)
    {
        r[i]=min(r[i],r[i+1]-1);
        if(b[l(i)].first<=k[i]+r[i]-r[i-1])return true;
        while(l(i)>1&&b[l(i)].first>k[i]+r[i]-r[i-1])r[i-1]--;
        if(l(i)==1)return false;
    }
    return b[1].first<=k[1]+r[1];
}
int main()
{
    t=read();
    for(int i=1;i<=t;i++)a[i]={read(),i};
    sort(a+1,a+t+1);
    for(int i=1;i<=t;i++)
    {
        dp[i]=dp[i-1],pre[i]=i-1;
        if(i>=a[i].first&&dp[i-a[i].first]+1>=dp[i]||i==t)dp[i]=dp[i-a[i].first]+1,pre[i]=i-a[i].first;
    }
    n=dp[t];
    for(int i=t,cnt=n;i;)
    {
        if(pre[i]==i-1&&a[i].first!=1){b[++m]=a[i--];continue;}
        for(int j=i;j>pre[i];j--)ans[cnt].push_back(a[j].second);
        maxn=max(maxn,k[cnt--]=a[i].first),i=pre[i];
    }
    reverse(k+1,k+n+1);
    int L=maxn,R=t,final;
    while(L<=R)
    {
        if(check(mid))final=mid,R=mid-1;
        else L=mid+1;
    }
    check(final);
    for(int i=1;i<=n;i++)if(i<=lst)for(int j=r[i-1]+1;j<=r[i];j++)ans[n-i+1].push_back(b[j].second);
    printf("%d\n",n);
    for(int i=1;i<=dp[t];i++)
    {
        printf("%d ",ans[i].size());
        for(int ths:ans[i])printf("%d ",ths);
        putchar('\n');
    }
    return 0;
}
```



---

