# Money Trees

## 题目描述

Luca is in front of a row of $ n $ trees. The $ i $ -th tree has $ a_i $ fruit and height $ h_i $ .

He wants to choose a contiguous subarray of the array $ [h_l, h_{l+1}, \dots, h_r] $ such that for each $ i $ ( $ l \leq i < r $ ),  $ h_i $ is divisible $ ^{\dagger} $ by $ h_{i+1} $ . He will collect all the fruit from each of the trees in the subarray (that is, he will collect $ a_l + a_{l+1} + \dots + a_r $ fruits). However, if he collects more than $ k $ fruits in total, he will get caught.

What is the maximum length of a subarray Luca can choose so he doesn't get caught?

 $ ^{\dagger} $ $ x $ is divisible by $ y $ if the ratio $ \frac{x}{y} $ is an integer.

## 说明/提示

In the first test case, Luca can select the subarray with $ l=1 $ and $ r=3 $ .

In the second test case, Luca can select the subarray with $ l=3 $ and $ r=4 $ .

In the third test case, Luca can select the subarray with $ l=2 $ and $ r=2 $ .

## 样例 #1

### 输入

```
5
5 12
3 2 4 1 8
4 4 2 4 1
4 8
5 4 1 2
6 2 3 1
3 12
7 9 10
2 2 4
1 10
11
1
7 10
2 6 3 1 5 10 6
72 24 24 12 4 4 2```

### 输出

```
3
2
1
0
3```

# 题解

## 作者：yszkddzyh (赞：13)

### 前言

蒟蒻刚开始打 CF，比赛时一遍过还是很开心的。

这是一道很好的双指针题目，建议先完成 [P1147](https://www.luogu.com.cn/problem/P1147)。

### 题目大意

给出两个数列 $\{a_n\}$ 和 $\{b_n\}$，求 $l,r$，使得对于任意 $l\leq i< r$ 都有 $b_{i+1}\mid b_i$，且 $\sum_{i=l}^ra_i\leq k$，输出最大的 $r-l+1$。

### 题目分析

从前往后扫描 $b$，有两个指针 $l,r$，分别代表当前选出的子段的左、右端点，初始值均为 $1$，设当前扫描到 $b_i$，分以下两种情况讨论：

1. $b_i\mid b_{i-1}$，这意味着可以在当前选出的子段后面在添上一个数，这时我们应该添上，即 `r++`，因为添上肯定会比不添要优，这其实是一个贪心的思想。

2. $b_i\nmid b_{i-1}$，这意味着当前选出的子段后面不能再加数了，此时我们应当将 $l$ 和 $r$ 均赋成 $i$，即从 $i$ 开始继续选新的子段。

完成以上步骤后，我们还要检查 $\sum_{i=l}^ra_i$ 是否大于 $k$，如果大于 $k$，那么我们就一直令 `l++`，直到子段和小于等于 $k$。接着，统计答案，即 `ans=max(ans,r-l+1)`。

于是，这题便做完了，注意多组测试！

### 代码

```cpp
/* 码风良好 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int t, n, k, a[N], b[N], s[N];

int main(){

    scanf("%d", &t);
    while(t--){
        int ans = 0;
        scanf("%d %d", &n, &k);
        for(int i = 1; i <= n; i++)
            scanf("%d", a + i),
            s[i] = s[i - 1] + a[i];
            //前缀和，检查子段和是否超过 k 时有用
        for(int i = 1; i <= n; i++)
            scanf("%d", b + i);
        for(int i = 1, l = 1, r; i <= n; i++){
            r = i;
            if(b[i - 1] % b[i]) l = r;//当前子段不能加数了
            while(s[r] - s[l - 1] > k) l++;//判断子段和是否超过 k
            ans = max(ans, r - l + 1);//统计答案
        }
        printf("%d\n", ans);
    }

    return 0;
}

/* MADE IN CHINA */
```

---

## 作者：I_am_AKed_by_NOI (赞：6)

## 前言

这是集训时备战 S 组是的的考试题目的 T1，还是比较简单的，但是我比较菜，花了 30min。

## 题目大意

给定两个数组 $a,h$，求一对 $l,r$ 满足 $a_l+a_{l+1}+\dots+a_{r-1}+a_r \le k$ ，$h_{i} \bmod h_{i-1}=0(l<i\le r)$ ，且 $r-l+1$ 最大。输出 $r-l+1$ 的值。


## 正解

我们把先把整个数组分成若干段，满足每个段当中有：相邻的两个数中后一个数是前一个数的倍数。那么我们只需要在每个段子中寻找一对 $l,r$ 满足 $a_l+a_{l+1}+\dots+a_{r-1}+a_r \le k$ ，并且 $r-l+1$ 最大。

现在考虑在一个段中如何寻找目标 $l,r$。我们可以暴力枚举左端点 $l$，然后二分枚举最大的 $r$。具体来说，我们统计 $a$ 数组前缀和得到 $sum$ 数组，因为 $a$ 数组中的元素都为正数，所以 $sum$ 数组单调递增，因此我们在 $sum$ 数组上二分，找到最大的 $x$ 满足 $sum_x - sum_l \le k$，此时的 $x$ 就是最大的 $r$。找到之后，我们用 $r-l+1$ 更新答案即可。

此外，还需要特判一种情况：如果 $a$ 数组中的所有数都 $>k$，那么直接输出 $0$ 即可。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T,n,k,ans;
int a[N],h[N];
int l[N],sum[N];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		bool flag=0;
		l[0]=ans=0;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]<=k) flag=1;
			sum[i]=sum[i-1]+a[i]; //统计前缀和
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&h[i]);
		}
		int now=0;
		while(now<n) //分成若干段
		{
			now++;
			if(h[now-1]%h[now]==0 && now!=1) continue;
			l[++l[0]]=now; //l[0] 是段的数量
		}
		l[++l[0]]=n+1;
		for(int i=1;i<l[0];i++)
		{
			int L=l[i],R=l[i+1]-1; //第 i 段的左端点和右端点
			for(int j=L;j<=R;j++) //暴力枚举 l
			{
				int left=L,right=R;
				while(left<right) //二分找到 r
				{
					int mid=left+right+1>>1;
					if(sum[mid]-sum[j-1]<=k)
					{
						left=mid;
					}
					else
					{
						right=mid-1;
					}
				}
				ans=max(ans,right-j+1); //更新答案
			}
		}
		if(!flag) cout<<"0\n";
		else printf("%d\n",ans);
	}
	return 0;
}

/*
5
5 12
3 2 4 1 8
4 4 2 4 1

4 8
5 4 1 2
6 2 3 1

3 12
7 9 10
2 2 4

1 10
11
1

7 10
2 6 3 1 5 10 6
72 24 24 12 44 44 2


1
5 10
5 6 5 5 5
6 3 1 8 4

*/
```

思路可以拿走，请把赞留下。

---

## 作者：ArcherHavetoLearnWhk (赞：2)

### 大致题意

给出 $\{a_n\},\{b_n\}$ ，选择一组 $l$ 和 $r$，求最大的 $r-l+1$ 并使得对于 $l\le i<r$，$h_{i+1}|h_i$，并 $sum_{l,r}=\sum_{i=l}^r{a_i}\le k$。

### 思路

明显，$r-l+1$ 越小就有越有可能有符合条件的区间，符合单调性，所以选择二分或者双指针，我选择双指针，它时间复杂度更低。

#### 所以，总体流程就是:

首先，将 $l$ 和 $r$ 设为 $1$ ，然后试着扩展右端点，此时，若 $h_r$ 是 $h_{r+1}$ 倍数，就扩展右端点；

否则，将左端点设为右端点的位置，前面的区间因为不符合要求的 $h_{r+1}$ 不能增加数，就不再计算了。

然后，右端点每次尝试扩展一次，就看看 $sum_{l,r}$，这里用前缀和数组提高效率。如果 $sum_{l,r}>k$ 就缩小区间长度，左端点向右端点靠拢直到 $sum_{l,r}\le k$，更新最大值，并进行下一轮，直到检查完两个序列。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200005],h[200005],s[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s[i]=s[i-1]+a[i];
		}
		for(int i=1;i<=n;i++)cin>>h[i];
		int ma=0,l,r;
		l=r=1;
		while(r<=n){
			if(h[r-1]%h[r])l=r;
			while(s[r]-s[l-1]>k)l++;
			ma=max(ma,r-l+1);
			r++;
		}
		cout<<ma<<'\n';
	}
	return 0;
}
```


---

## 作者：One_JuRuo (赞：2)

## 思路

要求最长长度，想到可以二分答案。

那么现在需要考虑如何快速验证答案是否正确。

可以 $O(n)$ 枚举区间左端点，因为有了长度，所以可以直接获得右端点的值，直接验证右端点是否合法。

因为要求区间的每个数都是右边的数的倍数，所以可以提前预处理每个点最远的满足这个条件的右端点，直接判断合不合法。

还要求和要小于某个值，这个直接前缀和预处理即可。

## AC code

```cpp
// LUOGU_RID: 126800277
#include<bits/stdc++.h>
using namespace std;
long long T,n,k,a[200005],h[200005],l,r,mid,ans,rm[200005];
inline bool check(long long x)
{
	for(long long i=1;i<=n-x+1;++i) if(a[i+x-1]-a[i-1]<=k&&rm[i]>=i+x-1) return 1;//合法
	return 0;//没有合法的
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		for(long long i=1;i<=n;++i) scanf("%lld",&a[i]),a[i]+=a[i-1];//前缀和预处理
		for(long long i=1;i<=n;++i) scanf("%lld",&h[i]);
		rm[n]=n;
		for(long long i=n-1;i>=1;--i)
			if(h[i]%h[i+1]==0) rm[i]=rm[i+1];
			else rm[i]=i;//预处理最远达到的合法右端点（仅满足整除条件）
		l=0,r=n;//二分
		while(l<=r)
		{
			mid=l+r>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
} 
```

---

## 作者：igAC (赞：1)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1873F)

[CFlink](https://codeforces.com/problemset/problem/1873/F)

简要题意：

求最长的区间 $[l,r]$ 使得 $i \in [l,r)$ 都有 $h_{i+1}|h_i$ 且 $k \ge \sum_{i=l}^{r}a_i$。

输出长度。

# $\text{Code}$

显然具有单调性，可以二分可以双指针，作者选择写双指针，求和可以用前缀和。

# $\text{Solution}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n,k,h[N],a[N],sum[N],ans,p;
void solve(){
	n=read(),k=read(),ans=0,p=1;
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) h[i]=read();
	for(int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;++i) if(a[i]<=k) ans=1;
	for(int i=1;i<=n;++i){
		p=max(p,i);
		while(p<n && h[p]%h[p+1]==0 && sum[p+1]-sum[i-1]<=k){
			++p;
			ans=max(ans,p-i+1);
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：phigy (赞：0)

首先 $h_{i+1}|h_i$ 的要求将 $a$ 划分成了众多段。

然后对于在 $\sum_{i=l}^r a_i\leq k$ 的情况下找到最大的 $r-l+1$。

我们发现 $\sum_{i=l}^r a_i$ 是满足 $l$ 一定时随 $r$ 增大增大，$r$ 一定时随 $l$ 增大减少，因此对于每个 $l$ 的最大 $r$ 是不降的。

因此我们可以使用双指针去解决这个问题，同时对于分段问题，我们只需要强制将 $l$ 保持和 $r$ 在一段内即可。

```cpp
#include <csignal>
#include <iostream>

#define int long long

using namespace std;

int T;
int n;
int a[2000005];
int h[2000005];
signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        for(i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        for(i=1;i<=n;i++)
        {
            cin>>h[i];
        }
        int res=0;
        int maxx=0;
        h[0]=h[1];
        for(j=1,i=1;i<=n;i++)
        {
            if(h[i-1]%h[i]!=0)
            {
                j=i;
                res=0;
            }
            res+=a[i];
            while(res>k)res-=a[j],j++;
            if(res<=k)
            {
                maxx=max(maxx,i-j+1);
            }
        }
        cout<<maxx<<endl;
    }
    return 0;
}
```


---

## 作者：Natori (赞：0)

>[CF1873F Money Trees](https://www.luogu.com.cn/problem/CF1873F)

双指针好题，但是我用的队列（

------------
考虑先找出所有极长的、满足任意一个数都能被它后面的那个数整除的连续段。显然这个操作可以在 $\mathcal{O}(n)$ 的时间复杂度内完成。

求出每个极长连续段的答案，取 $\max$ 即为最终答案。那么现在的问题就是求一个数列中，满足和不超过正整数 $m$ 的子串的最长长度。

注意到这个问题可以使用双指针法解决：右端点从左向右扫，每 $+1$ 就相当于加入一个值。同时维护当前选中的数的和，如果超过 $m$ 就删除之前的数，直到和 $\le m$。在维护过程中更新答案即可。

时间复杂度 $\mathcal{O}(n)$。代码使用了 ```std::queue```，和双指针本质相同。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
namespace Fast_In_Out{
	char buf[1<<21],*P1=buf,*P2=buf;
	#define gc (P1==P2&&(P2=(P1=buf)+fread(buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
	int read(){
		int f=1,x=0;
		char c=gc;
		while(c<'0'||c>'9'){
			if(c=='-')
			    f=-1;
			c=gc;
		}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';
			c=gc;
		}
		return f*x;
	}
	void write(int x){
		if(x<0)
			x=-x,putchar('-');
		if(x>9)
			write(x/10);
		putchar(x%10+'0');
	}
	#undef gc
}
using namespace Fast_In_Out;
typedef pair<int,int> pii;
const int N=2e5+8,oo=1e18+8;
int n,m,a[N],b[N];
vector<pii> vec;
int work(int ll,int rr){
	queue<int> que;
	int now=0,res=0,siz=0;
	for(int i=ll;i<=rr;i++){
		if(now<=m){
			now+=a[i];
			que.push(a[i]);
			siz++;
		}
		while(now>m&&que.empty()==0){
			now-=que.front();
			que.pop();
			siz--;
		}
		res=max(res,siz);
	}
	return res;
}
void solve(){
	vec.clear();
	for(int i=1;i<=n;i++)
		a[i]=b[i]=0;
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	b[0]=b[n+1]=oo;
	int pos=1;
	for(int i=1;i<=n;i++){
		if(b[i]%b[i+1]!=0){
			vec.push_back({pos,i});
			pos=i+1; 
		}
	}
	int ans=0;
	for(auto cur:vec){
		int l=cur.first,r=cur.second;
		int tmp=work(l,r);
//		write(tmp),putchar(' ');
		ans=max(ans,tmp);
	}
	write(ans),putchar('\n');
}
bool Mend;
signed main(){
//	File_Work();
	fprintf(stderr,"%.3lf MB\n\n\n",(&Mbegin-&Mend)/1048576.0);
	int testnum=read();
	while(testnum--)
		solve();
	fprintf(stderr,"\n\n\n%.0lf ms",1e3*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：technopolis_2085 (赞：0)

分析：

我们可以对于每一个 $i$，找出以 $i$ 为左边界的最靠右的右边界 $bor_i$，可以用双指针实现。

然后对于每一个 $i$，二分 $i$ 和 $bor_i$ 中最靠右的边界使得区间和小于等于 $k$，并将区间长度更新到答案。

然后就做完了。注意本题是多测。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+10;
int h[maxn],a[maxn];
int bor[maxn];
int sum[maxn];

int main(){
	int t;
	scanf("%d",&t);
	
	while (t--){
		int n,k;
		scanf("%d%d",&n,&k);
		
		for (int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			sum[i]=sum[i-1]+a[i];
		}
		for (int i=1;i<=n;i++){
			scanf("%d",&h[i]);
		}
		
		for (int i=1;i<=n;i++){
			int j=i;
			while (j+1<=n&&h[j]%h[j+1]==0) j++;//i是左界，j是右界
			for (int x=i;x<=j;x++) bor[x]=j;
			i=j;//到下一个区间
		}
		
		int ans=0;
		for (int i=1;i<=n;i++){
			int l=i,r=bor[i];//二分
			int best=i-1;
			
			while (l<=r){
				int mid=(l+r)/2;
				if (sum[mid]-sum[i-1]<=k){
					best=mid;
					l=mid+1;
				}else r=mid-1;
			}
			
			ans=max(ans,(best-i+1));
		}
		printf("%d\n",ans);
		
		for (int i=1;i<=n;i++){
			bor[i]=0; sum[i]=0;
		}
	}
	return 0;
} 
```


---

## 作者：linxuanrui (赞：0)

### 思路

二分答案。

首先，预处理出每个左端点 $i$ 的最右边的右端点 $j$，使得 $\forall i\le x< j,a_{x+1}\ | \ a_x$。

接下来枚举左端点，二分右端点即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
typedef long long ll;
using namespace std;
int t,n,m,a[200005],h[200005],num[200005],ans,sum[200005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		ans = 0;//多测一定要清空呀……
		cin >> n >> m;
		for(int i = 1;i <= n;i++)cin >> a[i],sum[i] = sum[i - 1] + a[i];
		for(int i = 1;i <= n;i++)cin >> h[i];
		num[n] = 1;
		for(int i = n - 1;i >= 1;i--){//记录每个左端点最右的右端点
			if(h[i] % h[i + 1] == 0)num[i] = num[i + 1] + 1;
			else num[i] = 1;
		}
		for(int i = 1;i <= n;i++){
			int l = i,r = i + num[i];
			while(r - l > 1){
				int mid = (l + r) / 2;
				if(sum[mid] - sum[i - 1] <= m)l = mid;
				else r = mid;
			}
			if(sum[l] - sum[i - 1] <= m)ans = max(ans,l - i + 1);
		}
		cout << ans << endl;
	}
}
```

---

