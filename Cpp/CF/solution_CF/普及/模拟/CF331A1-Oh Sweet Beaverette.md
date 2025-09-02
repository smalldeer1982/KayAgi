# Oh Sweet Beaverette

## 题目描述

有 $n$ 棵树，每一棵树都有一个美丽值。你可以砍倒任意一些树（当然也可以不砍），使砍完后剩下的这些树满足以下要求：

1. 美丽值总和尽可能的大。
2. 第一棵树和最后一棵树的美丽值必须相等。
3. 最少剩余 $2$ 棵树。

保证至少有两棵树的美丽值相等。

## 样例 #1

### 输入

```
5
1 2 3 1 2
```

### 输出

```
8 1
1 ```

## 样例 #2

### 输入

```
5
1 -2 3 1 -2
```

### 输出

```
5 2
2 5 ```

# 题解

## 作者：AC_love (赞：2)

贪心。

一个显而易见的贪心策略是：先砍掉所有美丽度为负数的树，然后在剩下的美丽度为正数的树种选取。

然而这个显然的贪心策略显然是错的，举个例子：

```
-2 100 1 5 1 -2
```

如果我们把两棵美丽度为 $-2$ 的树砍掉了，那么为了满足第二个条件，我们就必须砍掉美丽度为 $100$ 的树，这波丢了西瓜拣芝麻，实在不划算。

因此我们不能盲目乱砍滥伐，应该考虑怎么才能更优。

我们想到：美丽度为负数的树除非是作为两个端点，不然我们死都不可能会留着这玩意有碍市容，因此我们只要枚举端点，然后砍掉中间所有美丽度为负数的树即可。

我们想到，一段显然越长越好，也就是说针对每个点作为左端点，我们都希望枚举它最靠右的右端点在哪。

对于 Subtask 1，直接暴力枚举每个点作为左端点时的右端点在哪即可，复杂度 $O(n^2)$。

对于 Subtask 2，我们可以用一个 map 来存每个数对应的左端点和右端点的位置，然后用前缀和快速处理这一段的最大子序列和，复杂度 $O(n \log n)$。

实际上不用 map 而用 vector 理论上可以做到 $O(n)$，但是比较麻烦，其实没有必要。

代码实现如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 3e4;
const int inf = 1145141919810ll;

int n, ans = -inf;
int a[N];
int pre[N];
int le, ri;

map <int, int> lef;
map <int, int> rig;

signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> a[i];
		pre[i] = pre[i - 1] + max(a[i], 0ll);
		if(lef[a[i]] == 0)
			lef[a[i]] = i;
		rig[a[i]] = i;
	}
	for(int i = 1; i <= n; i = i + 1)
	{
		int l = lef[a[i]];
		int r = rig[a[i]];
		if(l == r)
			continue;
		if(a[i] >= 0)
		{
			if(pre[r] - pre[l - 1] > ans)
			{
				ans = pre[r] - pre[l - 1];
				le = l, ri = r;
			}
		}
		else
		{
			if(pre[r] - pre[l - 1] + 2ll * a[i] > ans)
			{
				ans = pre[r] - pre[l - 1] + 2ll * a[i];
				le = l, ri = r;
			}
		}
	}
	cout << ans << " ";
	queue <int> q;
	for(int i = 1; i <= le - 1; i = i + 1)
		q.push(i);
	for(int i = le + 1; i <= ri - 1; i = i + 1)
		if(a[i] < 0)
			q.push(i);
	for(int i = ri + 1; i <= n; i = i + 1)
		q.push(i);
	cout << q.size() << "\n";
	while(!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	return 0;
}
```

---

## 作者：Feyn (赞：2)

就是一道很基础的题目。

题意是说给定一个序列，希望保留一些数，满足保留的第一个数和最后一个相等，在这个基础上希望最大化保留的数之和。

由于没有特殊限制，可以直接考虑相等的两个数是什么，具体而言就是枚举右端点。对于一个右端点，肯定会贪心地选择最左边的和它相同的数，毕竟这意味着有更多的数可以被保留下来。至于中间的数，肯定是贪心地只要正数并把负数丢掉，维护一个前缀和即可。

代码：

```
map<int,int>pl;bool out[N];
int m,a[N],sum[N],ans=-1e18,ansPl,num;

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);for(int i=1;i<=m;i++)read(a[i]),sum[i]=sum[i-1]+max(a[i],0);
	for(int i=1;i<=m;i++){
		if(pl.count(a[i])==0){pl[a[i]]=i;continue;}
		int npl=pl[a[i]],nowData=a[i]*2+sum[i-1]-sum[npl];
		if(nowData>ans)ans=nowData,ansPl=i;
	}
	out[pl[a[ansPl]]]=out[ansPl]=true;num=2;
	for(int i=pl[a[ansPl]]+1;i<ansPl;i++)if(a[i]>0)out[i]=true,num++;
	printf("%I64d %I64d\n",ans,m-num);
	for(int i=1;i<=m;i++)if(out[i]^1)printf("%I64d ",i);
	
	return 0;
}
```

---

## 作者：zhuweiqi (赞：1)

### 方法一：暴力枚举

时间复杂度：$O(n^3)$

期望得分：$30$ 分

思路：枚举左端点和右端点（即砍完树之后的第一棵树和最后一棵树），如果它们的美丽值不相等则直接跳过，否则就把左端点和右端点的这两棵树以及这个**开**区间内所有美丽值大于零的树都选了，得到一个美丽值总和，如果这个数大于之前得到的最大的数，就更新最大值。输出部分则先找出能得到最大值的那种方案，然后砍倒的树的数量就是位于左端点之前的所有树和位于右端点之后的所有树以及这个**开**区间内所有美丽值小于或者等于零的树，最后依次输出它们即可。注意！题目保证至少有两棵树的美丽值相同，但没说解一定是正数，所以美丽值总和的最大值的初始值要赋值为一个**极小值**并且枚举的区间内的左右端点都必须选上，不能因为它是负数就不选了！另外，记得要开 $64$ 位有符号整型变量来存储这个最大值！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
int a[102]; 
int main(){
	int n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	long long ans=-1e18;
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]!=a[j]) continue;
			long long now=2*a[i];
			for(int k=i+1;k<j;k++) if(a[k]>0) now+=a[k];
			if(now>ans) ans=now; 
		}
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]!=a[j]) continue;
			long long now=2*a[i];
			for(int k=i+1;k<j;k++) if(a[k]>0) now+=a[k];
			if(now==ans){
				int cnt=i-1+n-j;
				for(int k=i+1;k<j;k++) if(a[k]<0) cnt++;
				printf("%lld %d\n",ans,cnt);
				for(int k=1;k<i;k++) printf("%d ",k);
				for(int k=i+1;k<j;k++) if(a[k]<0) printf("%d ",k);
				for(int k=j+1;k<=n;k++) printf("%d ",k);
				return 0;
			}
		}
	}
	return 0;
}
```

### 方法二：优化了一点点的枚举

时间复杂度：$O(n^2)$

期望得分：$30$ 分

我们可以用一个类似前缀和数组一样的东西来优化程序，使我们枚举的效率从三重循环优化到了两重循环，即用一个一维数组 $f$，用 $f_i$ 表示如果把所有在第 $1$ 棵树到第 $i$ 棵树之间的美丽值大于零的树都选了可以获得的美丽值总和是多少，当 $a_i\leq 0$ 时，$f_i=f_{i-1}$，反之 $f_i=f_{i-1}+a_i$，注意 $f$ 数组要开 long long。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
int a[102]; 
long long f[102];
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]<=0) f[i]=f[i-1];
		else f[i]=f[i-1]+a[i];
	}
	long long ans=-1e18;
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]!=a[j]) continue;
			long long now=2*a[i]+f[j-1]-f[i];
			if(now>ans) ans=now; 
		}
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]!=a[j]) continue;
			long long now=2*a[i]+f[j-1]-f[i];
			if(now==ans){
				int cnt=i-1+n-j;
				for(int k=i+1;k<j;k++) if(a[k]<0) cnt++;
				printf("%lld %d\n",ans,cnt);
				for(int k=1;k<i;k++) printf("%d ",k);
				for(int k=i+1;k<j;k++) if(a[k]<0) printf("%d ",k);
				for(int k=j+1;k<=n;k++) printf("%d ",k);
				return 0;
			}
		}
	}
	return 0;
}
```

### 方法三：优化了亿点点的枚举

时间复杂度：$O(n\log n)$

期望得分：$100$ 分

可以发现，我们想要求出最优解就必须要枚举，而我们在枚举的时候因为很多不必要的枚举就浪费了大量的时间，比如说：如果当 $a_i\not =a_j$ 或者当 $a_i=a_j$ 但是存在一个 $k$（$k<i$）并且 $a_k=a_i$ 或者存在一个 $l$（$j<l$）并且 $a_j=a_l$ 时，我们完全不需要枚举这些情况，因为这些情况要么无解，要么肯定不是最优解或者是最优解之一，将来一定会有**至少不比它劣的解**出现，因此，我们需要按树的美丽值的大小（即 $a_i$ 的值）对 $a$ 数组进行排序，并且当 $a_i$ 的值相等时肯定是树的位置越前面的树排在越前面的地方，在此过程中我们需要用结构体同时记录每棵树的美丽值和它原来的位置，然后用一重循环扫过去，找到一对 $i,j$，使得 $a_{i-1}\not = a_i$ 并且 $a_j \not = a_{j+1}$ 并且 $a_i=a_j$ 并且 $i\not =j$（因为题目中说最少留两棵树），它所能获得的美丽值总和最大的值就是 $a_i$ 与 $a_j$ 与把所有在第 $i+1$ 棵树到第 $j-1$ 棵树之间的美丽值大于零的树都选了所得到的美丽值的和的总和，最后，我们就可以得出最优解啦！输出也是同理。上最终代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
struct tree{
	int a,p;
}s[300002];
bool cmp(tree a,tree b){
	if(a.a!=b.a) return a.a<b.a;
	return a.p<b.p;
}
long long f[300002];
int st[300002];
int main(){
	int n=read(),fir=1;
	long long ans=-1e18;
	for(int i=1;i<=n;i++){
		st[i]=read();
		s[i].a=st[i];
		s[i].p=i;
		if(s[i].a<0) f[i]=f[i-1];
		else f[i]=f[i-1]+s[i].a;
	}
	s[n+1].a=1e9+7;
	sort(s+1,s+1+n,cmp);
	for(int i=2;i<=n+1;i++){
		if(s[i].a!=s[i-1].a){
			if(fir!=i-1){
				i--;
				long long now=s[fir].a*2+f[s[i].p-1]-f[s[fir].p];
				if(now>ans) ans=now;
				i++;
			}
			fir=i;
		}
	}
	fir=1;
	for(int i=2;i<=n+1;i++){
		if(s[i].a!=s[i-1].a){
			if(fir!=i-1){
				i--;
				long long now=s[fir].a*2+f[s[i].p-1]-f[s[fir].p];
				if(now==ans){
					int cnt=s[fir].p-1+n-s[i].p;
					for(int j=s[fir].p+1;j<s[i].p;j++) if(st[j]<0) cnt++;
					printf("%lld %d\n",ans,cnt);
					for(int j=1;j<s[fir].p;j++) printf("%d ",j);
					for(int j=s[fir].p+1;j<s[i].p;j++) if(st[j]<0) printf("%d ",j);
					for(int j=s[i].p+1;j<=n;j++) printf("%d ",j);
					return 0;
				}
				i++;
			}
			fir=i;
		}
	}
	return 0;
}
```

---

## 作者：_shine_ (赞：1)

不难发现一件事：对于在 $i$ 之后能跟 $i$ 匹配的 $j$，最好的办法显然是使得 $j$ 最大。则用前缀和统计整个和，并且用前缀和维护负数和，在枚举 $i$ 统计出最小答案时在后面计算出满足最大答案的条件并输出即可。

[ac records]()
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn=3e5+10;
map<int,int>p;
int n,num,now_ans=LONG_LONG_MIN;
int a[maxn],b[maxn],c[maxn];
vector<int>ans;
void out_puts(int u){
    printf("%lld %lld\n",u,ans.size());
    for(int i=0;i<ans.size();++i)printf("%lld ",ans[i]);
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;++i){scanf("%lld",&a[i]);b[i]=b[i-1]+a[i];p[a[i]]=max(p[a[i]],i);if(a[i]<0)c[i]=c[i-1]+a[i];else c[i]=c[i-1];}
    for(int i=1;i<=n;++i){if(p[a[i]]==i)continue;now_ans=max(now_ans,b[p[a[i]]]-b[i-1]-(c[p[a[i]]-1]-c[i]));}
    for(int i=1;i<=n;++i){if(p[a[i]]==i)continue;if(now_ans==b[p[a[i]]]-b[i-1]-(c[p[a[i]]-1]-c[i])){num=0;for(int j=1;j<=n;++j){if(j<i || j>p[a[i]] || (a[j]<0 && j!=i && j!=p[a[i]])){ans.push_back(j);num+=a[j];}}out_puts(b[n]-num);return 0;}}
    return 0;
}
```


---

## 作者：RE_Prince (赞：1)

# CF331A1 Oh Sweet Beaverette 

[link](https://www.luogu.com.cn/problem/CF331A1)


## Sol

一道很基础的暴力题。


其实这道题细节还挺多的，比较考验思维能力。思路就是暴力枚举左右端点，如果相同，累加 $[l,r]$ 这段区间内的和。注意一下，题目要求是美丽值最大，因此 $[l,r]$ 这段区间内拉低美丽值的树必须砍掉。这个可以在记录答案后统一输出。

但是，要特判一下 $n=2$ 的情况，否则有可能你的程序一棵也没保留，不符合题意。

这个思路可以解决第一行的输出，但第二行呢？


我们现在已经把美丽值最大的左右端点求出来了，记为 $[ansl,ansr]$。因为是最大的，所以这段区间前面和后面的树都要砍掉。而且，我们要砍掉美丽值 $<0$ 的树，因为这些树拉低了总体的美丽值。这个上文提到过，这里不过多阐述。


到这里代码很好写了：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,i,j,k=-1e18,al,ar;
int a[100009];
signed main()
{
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	if(n==2) return cout<<a[1]+a[2]<<" 0",0;
	al=1,ar=n;
	for(int l=1;l<=n;l++)
	{
		for(int r=l+1;r<=n;r++)
		{
			int sum=0;
			if(a[l]!=a[r]) continue;//直接跳过不符合要求的区间
			sum+=a[l]*2;
			for(i=l+1;i<=r-1;i++)//累加答案
				if(a[i]>0) sum+=a[i];
			if(sum>k) k=sum,al=l,ar=r;//找到更优，标记并更新max
		}
	}
	cout<<k<<" ";
	int sum=0;
	for(i=al+1;i<ar;i++)//拉低美丽值的树砍掉
		if(a[i]<0) sum++;
	cout<<sum+al-1+n-ar<<"\n";//这是总数
	for(i=1;i<al;i++) cout<<i<<" ";//砍掉前面
	for(i=al+1;i<ar;i++)
		if(a[i]<0) cout<<i<<" ";
	for(i=ar+1;i<=n;i++) cout<<i<<" ";//砍掉后面
	return 0;
}
```

---

## 作者：qusia_MC (赞：0)

似乎还没有人交 $O(n)$ 的题解，我来教一发。

感谢陈哲大人私信提示我。
## 分析
$n$ 棵树，砍去一些，首尾美丽要一样，求这些数美丽和的最大值。

------------
以下我们设第 $i$ 棵树的美丽度为 $a_i$。
## 思路
不难想到：

- 贪心思路：很容易想到，就是把 $a_i$ 为负数的全都砍了。但是这样有几个反例：

  首先：

   ```
   -2 99999999 1 1 -2
   ```
   按理说按照贪心应该把两个负数砍了，但这样就要被迫砍掉另一个超级大的，得不偿失了。
 
   再就是：
   ```
   -1 1 -1
   ```
   砍了的话就不能有两颗一样的。

- $O(n^3)$ 思路：这个是能过得（我不知道这么简单为什么是黄）先 $O(n^2)$ 找两个相同的数，再 $O(n)$ 累加。这么简单就不打了，是个人就会。但是这个最多能得三分之一分就算你牛。

- $O(n^2)$ 思路：提前 $O(1)$ 前缀和处理，再 $O(n^2)$ 找相同的数，再累加。这个前缀和思路有点思维含量（但不多），稍微打一下。这个大概能得一半分左右把。
   ```
   int a[10010];//数组
   int zhui[10010];//前缀和
   for(int i=1;i<=n;i++)
   {
   cin>>a[i];
   if(a[i]<0)zhui[i]=zhui[i-1];//小于0则不累加，有损市容。
   else zhui[i]=zhui[i-1]+a[i];//否则加上，市容rp++
   }
   ```

- $O(n \log n)$ 思路：拷贝数组，排序，前缀和 map 维护。这里不打了，其他题解都有。这个应该能对，具体请参考其他人的题解。

- $O(n)$ 思路：这也是今天的重点，可以省去排序。

## 输入处理
可以用正数前缀和处理，就是和前缀和方法一样，但是只统计正数（最优嘛，有损市容的打死也不能留）。

在开一个 map 统计一个数据左右两次出现的位置，就可以了。

接下来，直接打擂台，以前我们用 map 存储过了，直接找出现两次的数，在取这个区间中的树砍的最优方案，由于之前前缀和了，所以这边可以 $O(1)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,pair<int,int>> mp;//定义
int ans=-1e18,ans2,ans_ID,ans_ID2;//ans要足够小，不然可能WA两个点。
int zhui[999];
signed main()
{

    int n,a[999];
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);//输入
        if(a[i]>=0)
        {
        	zhui[i]=zhui[i-1]+a[i];//可以留着
		}
        else
        {
        	zhui[i]=zhui[i-1];//有损市容打死不留
		}
        if(mp[a[i]].first==0)mp[a[i]].first=i;
        mp[a[i]].second=i;//更新
    }
    for(int i=1;i<=n;i++)
    {
		if(mp[a[i]].first!=mp[a[i]].second)
		{
			if(ans<=zhui[mp[a[i]].second-1]-
			zhui[mp[a[i]].first]+
			a[i]*2)//换元转原式
			{
				ans=zhui[mp[a[i]].second-1]-
			    zhui[mp[a[i]].first]+a[i]*2;
				ans_ID=mp[a[i]].first;
				ans_ID2=mp[a[i]].second;
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
	    if(i<ans_ID||i>ans_ID2)cnt++;
	    else if(a[i]<0&&i!=ans_ID&&i!=ans_ID2)cnt++;
	}//先扫一遍
	cout<<ans<<" "<<cnt<<endl;
	for(int i=1;i<=n;i++)
	{
	    if(a[i]<0&&i!=ans_ID&&i!=ans_ID2)cout<<i<<" ";//再来一遍
		else if(i>=ans_ID&&i<=ans_ID2);
		else cout<<i<<" ";
	}
    return 0;
}
```

---

## 作者：Lijunzhuo (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF331A1)  
很简单，我们可以用暴力来解决这个问题。  
此题中有 $2$ 个想法是错的：  
1. 所有负数都应该被砍掉。**错了**！砍树后第一棵树和最后一棵树的美丽值可能是负数，故想法错误。错误样例：
```
5
-3 -5 3 -5 0
```
输出应为：
```
-7 2
1 5
```

2. 枚举左右端点美丽值的时候找到了可以立刻退出，不必担心其他左右端点美丽值相同的情况，因为第一个左右端点美丽值相同的情况范围是最大的。**全错**！错了两处：**不可以**立刻退出；第一个左右端点美丽值相同的情况范围**不一定**最大的。错误样例 $1$：
```
10
-111 -999 -3 -2 -1 1 -1 -2 -3 -789
```
输出应为：
```
-1 7
1 2 3 4 8 9 10
```
错误样例 $2$：
```
6
1 2 1 10 50 2
```
输出应为：
```
65 1
1
```

好了，易错点讲完了，下面就是此题的正确思路了。  
暴力枚举左右端点，若左右端点美丽值相同，求出它们的和，并判断是否需要修改正确答案的值。

有一个可以优化的点：  
我们可以用整体减空白的方法，用总树量减去答案剩余的数量求出砍倒的树的数量。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=105,INF=1e18;
long long A[N],n,sum,ansz,z;
long long anssum=-INF,ansl,ansr;
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&A[i]);
	for(long long i=1;i<n;i++) //暴力 
		for(long long j=n;j>i;j--)
			if(A[i]==A[j])
			{
				sum=A[i]+A[j];  //头和为尾可能是负数
				z=j-i+1; 
				for(int k=i+1;k<j;k++)
				{
					sum+=(A[k]>0)?A[k]:0;
					if(A[k]<0) z--;
				}
				if(anssum<sum)
				{
					anssum=sum;
					ansl=i;
					ansr=j;
					ansz=z;
				}
			}
	if(n==2) {printf("%lld 0\n",A[1]+A[2]);return 0;}
	printf("%lld %lld\n",anssum,n-ansz); //整体减空白 
	for(long long i=1;i<=n;i++)
	{
		if((A[i]<0&&(i!=ansl&&i!=ansr))||(i<ansl||i>ansr))
			printf("%lld ",i);
	}
	return 0;
}
```
[记录](https://www.luogu.com.cn/record/132175158)

---

