# Optimal Sum

## 题目描述

And here goes another problem on arrays. You are given positive integer $ len $ and array $ a $ which consists of $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . Let's introduce two characteristics for the given array.

- Let's consider an arbitrary interval of the array with length $ len $ , starting in position $ i $ . Value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF182C/a67922122e1d38581ab8c091ae9897d972811ca1.png), is the modular sum on the chosen interval. In other words, the modular sum is the sum of integers on the chosen interval with length $ len $ , taken in its absolute value.
- Value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF182C/93dd358f9082d67d4f803ced64f412bb80cdf4c2.png) is the optimal sum of the array. In other words, the optimal sum of an array is the maximum of all modular sums on various intervals of array with length $ len $ .

Your task is to calculate the optimal sum of the given array $ a $ . However, before you do the calculations, you are allowed to produce no more than $ k $ consecutive operations of the following form with this array: one operation means taking an arbitrary number from array $ a_{i} $ and multiply it by -1. In other words, no more than $ k $ times you are allowed to take an arbitrary number $ a_{i} $ from the array and replace it with $ -a_{i} $ . Each number of the array is allowed to choose an arbitrary number of times.

Your task is to calculate the maximum possible optimal sum of the array after at most $ k $ operations described above are completed.

## 样例 #1

### 输入

```
5 3
0 -2 3 -5 1
2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 2
1 -3 -10 4 1
3
```

### 输出

```
14
```

## 样例 #3

### 输入

```
3 3
-2 -5 4
1
```

### 输出

```
11
```

# 题解

## 作者：npqenqpve (赞：3)

### 思路：

由于区间长度给定，所以考虑枚举那个区间是答案，显然只有 $n$ 种情况，由于对于 $[l,r]$ 这个长度合法的区间，要么改所有负数中前 $k$ 小，要么改所有正数中前 $k$ 大，显然把序列全部取相反数就能把第二个问题变成第一个问题，因此以下所有讨论都是对于改负数中 $k$ 小的。

区间第 $k$ 小值应该都能用各种方法求出，由于这个区间具有长度给定且左端点一直向右的特性，可以选择用码量特别小的 vector 实现二分插入到哪然后快速插入保持单调性，当区间移到 $[l,r]$ 时，判断如果 $a_r$  是负数就插入，如果 $a_{l-1}$ 被插入了就删掉 $a_{l-1}$，然后如果存在第 $k$ 大就记录，否则记录其中的最大值，由于具有单调性，直接访问即可，使用 $p_i$ 记录其值和所在区间。

然后问题就转化为，对每一个 $i$，求 $[i,i+len-1]$ 这个下标区间内比 $p_i$ 小的数之和加上一部分 $p_i$ 然后打擂台比一下，这个也正是这题最具有思维难度的部分（但事实证明只有我这种阴间方法需要处理这个问题），直接考虑离线，按 $p_i$ 的值为第一关键字排序，那么所有合法的值必然在 $p_i$ 加入树状数组之前已经加入了，具体而言，就是把所有比 $p_i$ 小还而且还没有加入树状数组的 $a_i$ 加进去，显然每次大力找是 $n^2$ 级别的，但是实际上只需要加入 $n$ 次，所以顺手把 $a_i$ 也排序，记录下标，然后双指针即可，需要有多少个 $p_i$ 可以各种方法算，比如再开一个树状数组维护个数。

### 代码：
给出贼几把长的实现。

其中 $f$ 是前缀和数组，$a$ 是读入的那个数组，$t$ 是树状数组，$b$ 是复制 $a$ 并进行排序的，$p$ 是记录每个区间的第 $k$ 小然后离线的，$v_1$ 是用来求区间第 $k$ 小的。
```cpp
int f[(int)(2e5+10)],n,k,len,a[(int)(2e5+10)],t[(int)(2e5+10)];
int lowbit(int x){return x&(-x);}
void add(int x,int k){while(x<=n){t[x]+=k;x+=lowbit(x);} }
int sum(int x){int ans=0;while(x>0){ans+=t[x];x-=lowbit(x);}return ans;}
vector<int>v1;
struct node
{
    int v,id;
}b[(int)(2e5+10)];
bool cmp(node a,node b)
{
    return a.v<b.v;
}
int min(int a,int b)
{
    return a<b?a:b;
}
struct node1
{
    int val,l,r;
}p[(int)(2e5+10)];
bool cmp1(node1 a,node1 b)
{
    if(a.val==b.val) return a.l<b.l;
    return a.val<b.val;
}
int ans=-1,top=0;
void get(int a[])
{
    memset(d,0,sizeof(d));
    memset(f,0,sizeof(f));memset(t,0,sizeof(t));
    memset(p,0,sizeof(p));memset(b,0,sizeof(b));
    v1.clear();top=0;
    for(int i=1;i<=n;i++) 
    {
        b[i]=(node){a[i],i};        
        f[i]=f[i-1]+a[i];
    }
    for(int i=1;i<=len;i++) 
    {
        if(a[i]>0) continue;
        v1.insert(upper_bound(v1.begin(),v1.end(),a[i]),a[i]);
    }
    if(v1.size()==0) p[++top]=(node1){0,1,len};
    else p[++top]=(node1){(min(0,v1[min(v1.size()-1,k-1)])),1,len};
    for(int i=2;i+len-1<=n;i++)
    {
        int l=i,r=i+len-1;
        if(a[l-1]<=0) v1.erase(lower_bound(v1.begin(),v1.end(),a[l-1])); 
        if(a[r]<=0) v1.insert(upper_bound(v1.begin(),v1.end(),a[r]),a[r]);
        if(v1.size()==0) p[++top]=(node1){0,l,r};
        else p[++top]=(node1){(min(0,v1[min(v1.size()-1,k-1)])),l,r};
    }
    sort(p+1,p+1+top,cmp1);
    sort(b+1,b+1+n,cmp);
    int j=1;
    for(int i=1;i<=top;i++)
    {
        while(j<=n&&b[j].v<=p[i].val)
        {
            add(b[j].id,b[j].v);
            j++;
        }
        // cout<<j<<" "<<(f[p[i].r]-f[p[i].l-1]+2*(abs(sum(p[i].r)-sum(p[i].l-1))))<<"\n";
        ans=max(ans,(f[p[i].r]-f[p[i].l-1]+2*(abs(sum(p[i].r)-sum(p[i].l-1)))));
    }
    // cout<<ans<<"\n";
    // puts("");
}
```

---

## 作者：Allanljx (赞：2)

## 题意
有一个数列，可以对它进行最多 $k$ 次操作，每次操作可以将一个数变为它的相反数，输出最后所有长度为 $len$ 的数列的和的绝对值的最大值

## 思路
首先，因为要求绝对值最大，所以将正数变为奇数就相当于将所有数变为自己的相反数。每次不断将第一个数数弹出，分类讨论它是否进行过操作，如果进行过就标记它并用最小的没进行过操作负数进行补位。对于新加入的数讨论它是正数还是负数，如果是负数判断将它进行操作后的值大还是不进行操作的值大。

$q$ 存的是进行操作的数的值和位置，方便与新的数做大小比较

$q1$ 存的是所有没变成正数的负数，当有进行过操作的负数从队列中出去后空缺的位置由 $q1$ 中绝对值最大的数代替。

$book$ 存的是当前这个位置的数有没有进行操作，因为优先队列无法弹出某一特定的数，因此只能在需要弹出的数在队首才可被弹出

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
int n,len,k,a[100005],now,sum,ans=-9999999999;
int book[100005];
priority_queue<pair<int,int> > q,q1;
void init()//将正数变为负数 
{
	memset(book,0,sizeof(book));
	for(int i=1;i<=n;i++) a[i]=-a[i];
	while(q.size()) q.pop();
	while(q1.size()) q1.pop();
	now=0,sum=0;
}
void work()
{
	for(int i=1;i<=n;i++)
	{
		if(i<=len)//序列长度不够 
		{
			if(a[i]>=0) sum+=a[i];//正数直接加 
			else
			{
				if(now<k) now++,sum-=a[i],q.push(mp(a[i],i)),book[i]=1;//还有操作次数 
				else
				{
					if(q.size()&&a[i]<=q.top().first)//进行操作
					{
						book[q.top().second]=0;
						sum+=q.top().first*2; 
						sum-=a[i];
						q1.push(mp(-q.top().first,q.top().second));//弹出的数等待补位 
						q.pop();
						q.push(mp(a[i],i));
						book[i]=1;
					}
					else//不进行操作 
					{
						sum+=a[i];
						q1.push(mp(-a[i],i));
					}
				}
			}
			if(i==len) ans=max(ans,sum);
			continue;
		}
		while(q1.size()&&q1.top().second<=i-len) q1.pop();//将下标不符合要求的数弹出 
		if(!book[i-len]) sum-=a[i-len];//没有进行操作 
		else
		{
			sum+=a[i-len],book[i-len]=0,now--;
			if(q1.size())//补位 
			{
				q.push(mp(-q1.top().first,q1.top().second));
				sum+=2*q1.top().first;
				book[q1.top().second]=1;
				q1.pop();
				now++;
			}
		}
		while(q.size()&&!book[q.top().second]) q.pop();
		if(a[i]>=0) sum+=a[i];//正数直接加 
		else
		{
			if(now<k) sum-=a[i],book[i]=1,q.push(mp(a[i],i)),now++;//还有操作次数 
			else
			{
				if(q.size()&&a[i]<=q.top().first)//进行操作 
				{
					book[q.top().second]=0;
					sum+=q.top().first*2;
					sum-=a[i];
					q1.push(mp(-q.top().first,q.top().second));
					q.pop();
					q.push(mp(a[i],i));
					book[i]=1;
				}
				else//补位 
				{
					sum+=a[i];
					q1.push(mp(-a[i],i));
				}
			}
		}
		ans=max(ans,sum);
	}
}
signed main()
{
	cin>>n>>len;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cin>>k;
	work();
	init();
	work();
	cout<<ans;
   	return 0;
}
```


---

## 作者：王熙文 (赞：1)

这道题是在太毒瘤了，我和学长们都提交了好几次才 AC，写篇题解记录一下。

## 题解

首先，我们将区间改变后和的绝对值分为两类，分别为负数和非负数。负数要最小，非负数要最大。

首先考虑非负数：

那么我们改变的数一定是前 $k$ 小的负数（如果负数个数不足 $k$ 个就设为负数个数个）

我们将长度为 $k$ 的区间从左到右枚举，类似滑动窗口的样子，可以将这个问题简化一下：维护一个数列，支持插入和删除数，每插入和删除一次数后求前 $\min(\text{cnt\_fu},k)$ 小的数的和（设为 $x$）。

先不考虑求和的事，如果求出来了，我们同时记录一个当前所有数的和 $\text{nowsum}$。如果求出来了 $x$，则答案为 $\text{nowsum}-2x$。

负数也类似。

所以现在问题便转化为了上面这个问题。

其实不用想得太复杂。我们可以先把所有数离散化一下。因为我们要求的是前 $k$ 小的和，所以我们对于数与数之间只需要知道大小关系。设 $a$ 表示离散化后的数组。对于原本数的大小，我们需要记录一个 $id$，$id_{a_i}$ 表示 $a_i$ 原本的大小。

对于非负数，我们需要求前 $k$ 小，而对于负数，我们需要求前 $k$ 大。不如统一一下，对于非负数离散化时离散化后的数与数之间的关系与之前的恰好相反（比如之前的是 $-1,1,2,-5,3$，正常离散化应该变成 $2,3,4,1,5$，但我们把它变成 $4,3,2,5,1$）。这样就可以统一变成求前 $k$ 大的数的总和了。

这样离散化之后，就可以进行值域分块了。设块长为 $B$，第 $i$ 块维护的是 $(i-1)B+1 \sim iB$，则对于每一个块，需要维护 $2$ 个东西：$sum_i$ 表示第 $i$ 块有多少个数，$sum2_i$ 表示第 $i$ 块的数的和。

另外还需要维护一个 $cnt_i$ 表示值为 $i$ 的数出现次数。

这样的话插入和删除对这三个东西相应地改就好了。

对于查询：

从大到小遍历每一个块，统计当前出现了多少数，如果这个数加上当前块的数量（$sum_i$）超过了 $k$，则当前块往上（不含当前块）的所有块都可以选，当前块需要再次看每一个数能否选。实现可以参考我的代码。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,k,tot;

int a[100010],b[100010],lst[100010],id[100010];

// 值域分块，第 i 块维护 (i-1)*block+1~i*block 里的数

int sum[1010],sum2[1010];

int cnt[100010];

int block;

void add(int x)
{
	int p=(x-1)/block+1;
	++sum[p];
	sum2[p]+=id[x];
	++cnt[x];
}

void del(int x)
{
	int p=(x-1)/block+1;
	--sum[p];
	sum2[p]-=id[x];
	--cnt[x];
}

int get_sum()
{
	int ccnt=0;
	for(int i=tot/block+1; i>=0; --i)
	{
		ccnt+=sum[i];
		if(ccnt>=k)
		{
			int nowsum=0,nowcnt=ccnt-sum[i];
			for(int j=tot/block+1; j>i; --j) nowsum+=sum2[j];
			for(int j=i*block; j>=(i-1)*block; --j)
			{
				if(nowcnt+cnt[j]>=k) return nowsum+id[j]*(k-nowcnt);
				nowsum+=cnt[j]*id[j];
				nowcnt+=cnt[j];
			}
		}
		else if(i==0)
		{
			int nowsum=0;
			for(int j=tot/block+1; j>=0; --j) nowsum+=sum2[j];
			return nowsum;
		}
	}
	return 114514;
}

signed main()
{
	int len,ans=0;
	scanf("%lld%lld",&n,&len);
	for(int i=1; i<=n; ++i)
	{
		scanf("%lld",&a[i]);
		b[i]=lst[i]=a[i];
	}
	scanf("%lld",&k);
	sort(b+1,b+n+1);
	tot=unique(b+1,b+n+1)-b-1;
	block=sqrt(tot);
	for(int i=1; i<=n; ++i)
	{
		int last=a[i];
		a[i]=tot-(lower_bound(b+1,b+tot+1,a[i])-b)+1;
		id[a[i]]=last;
	}
	// 全变正数
	int nowsum=0;
	for(int i=1; i<=len; ++i)
	{
		if(id[a[i]]<0) add(a[i]);
		nowsum+=id[a[i]];
	}
	int gt=get_sum();
	ans=max(ans,nowsum-get_sum()*2);
	for(int i=2; i<=n-len+1; ++i)
	{
		int j=i+len-1;
		if(id[a[i-1]]<0) del(a[i-1]);
		if(id[a[j]]<0) add(a[j]);
		nowsum+=id[a[j]]-id[a[i-1]];
		int gt=get_sum();
		ans=max(ans,nowsum-get_sum()*2);
	}
	// 全变负数
	memset(sum,0,sizeof(sum));
	memset(sum2,0,sizeof(sum2));
	memset(cnt,0,sizeof(cnt));
	for(int i=1; i<=n; ++i)
	{
		int last=lst[i];
		a[i]=lower_bound(b+1,b+tot+1,lst[i])-b;
		id[a[i]]=last;
	}
	nowsum=0;
	for(int i=1; i<=len; ++i)
	{
		if(id[a[i]]>0) add(a[i]);
		nowsum+=id[a[i]];
	}
	ans=max(ans,-nowsum+get_sum()*2);
	for(int i=2; i<=n-len+1; ++i)
	{
		int j=i+len-1;
		if(id[a[i-1]]>0) del(a[i-1]);
		if(id[a[j]]>0) add(a[j]);
		nowsum+=id[a[j]]-id[a[i-1]];
		ans=max(ans,-nowsum+get_sum()*2);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Adolfo_North (赞：0)

大家讲的都很好，但代码略显繁琐，请允许我补充一点自己的见解。

首先，我们不应被绝对值所迷惑，直接求最大或最小即可。我采用求最大的方式，所以按其讲解。

其次，对于变成相反数的操作，我们需要分将负数变为正数，与将正数变成负数的情况讨论，但事实上我们可以将原数组全部变为其相反数，即可用同一套班子解决。

我采用了将负数变为正数取最大的方法。

我们令 $x=1$ 且 $a_x\sim a_x+len-1$ 的和为 $sum$。则将该区间内的负数 $x$ 翻转对 $sum$ 的贡献是 $x\times 2$。在遍历时记录下负数，再进行操作即可。之后我们令 $x$ 不断自增，并按原思路维护即可。

具体看代码吧：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+7;
int a[N],b[N];
int solve(int n,int len,int k,int a[]){
	multiset<int> s;
	int ans=-1e9,sum=0;
	for(int i=1;i<=len;i++){
		if(a[i]<0) s.insert(a[i]);
		sum+=a[i];
	}
	int now=sum,cnt=0;
	for(auto x:s){
		now-=2*x;
		if(++cnt==k) break;
	}
	ans=max(ans,now);
	for(int l=2,r=len+1;r<=n;l++,r++){
		sum-=a[l-1],sum+=a[r];
		if(a[r]<0) s.insert(a[r]);
		if(a[l-1]<0) s.erase(s.lower_bound(a[l-1]));
		now=sum,cnt=0;
		for(auto x:s){
			now-=2*x;
			if(++cnt==k) break;
		}
		ans=max(ans,now);
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n,len,k;
	cin>>n>>len;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=-a[i];
	cin>>k;
	cout<<max(solve(n,len,k,a),solve(n,len,k,b));
	return 0;
}
```

---

## 作者：_edge_ (赞：0)

看了一眼题解区，发现全都是高科技的数据结构。

但这道题目明明不用这样呀。

考虑当前这个，我们需要把负数前 $k$ 小变成相反数，把正数变成负数相当于是整一个序列取相反数后把负数前 $k$ 小变成相反数。

那么我们维护的是区间的前 $k$ 小，并且这个区间还是滑动的。

考虑维护两个 set 或者堆，一个是要修改的数，另外一个则是备用的数。

在一开始我们先把 $1$ 到 $len-1$ 这些数扔到 set 或者堆里面，这个可以很容易维护。

然后对于要滑动的时候，如果滑出去的那个数在答案 set 里面则把它搞出去，然后再维护答案的 set 大小为 $k$。

具体的，就把备用的 set 里面的数扔到答案的 set 里面。

然后滑进来的数可以很好维护，可以自己思考一下。

注意这边特判一下 $k=0$ 的情况，可能出现 RE 的现象。

附：`s.begin` 代表头指针，`s.rbegin` 代表尾指针。

但是不能直接删除尾指针，要删除 `s.erase(--s.end())`。

核心代码如下：

```cpp
	scanf("%lld %lld",&n,&len);
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	scanf("%lld",&k);int sum=0;
	for (int i=1;i<len;i++) {
		if (a[i]<0 && k) {
			if (s.size()<k) s.insert(a[i]),sum1+=a[i];
			else if (*s.rbegin()>=a[i])
				{sum1-=*s.rbegin();s1.insert(*s.rbegin());
				s.erase(--s.end());s.insert(a[i]);sum1+=a[i];}
			else s1.insert(a[i]);
		}
		sum+=a[i];
	}
	
	for (int i=len;i<=n;i++) {
		if (i!=len  && k) {
			int l=i-len;
			sum-=a[l];
			if (s.find(a[l])!=s.end()) {sum1-=a[l];s.erase(s.find(a[l]));}
			else if (s1.find(a[l])!=s1.end()) s1.erase(s1.find(a[l]));
		}
		
		while (s.size()<k && s1.size()) {
			s.insert(*s1.begin());
			sum1+=*s1.begin();
			s1.erase(s1.begin()); 
		}
		
		if (a[i]<0  && k) {
			if (s.size()<k) s.insert(a[i]),sum1+=a[i];
			else if (*s.rbegin()>=a[i])
				{sum1-=*s.rbegin();s1.insert(*s.rbegin());
				s.erase(--s.end());s.insert(a[i]);sum1+=a[i];}
			else s1.insert(a[i]);
		}
		sum+=a[i];
//		cout<<sum<<" "<<sum1<<" pp\n";
		ans=max(ans,sum-sum1-sum1);
	}
```


---

