# Fighting Tournament

## 题目描述

## 题意 

Burenka正准备去观看一年中最有趣的体育活动 —— 她朋友Tonya组织的格斗锦标赛。

有 **n** 名运动员参加了大赛，标号分别为为 1，2，... ，n 。第 **i** 名运动员的实力是 **$a_i（1 \le a_i \le n）$** 。**每个运动员的实力是不同的，也就是说，数组 a 是 n 的 一种 全排列** 。

大赛的流程是这样的：

一开始，运动员们**按标号从小到大**排成一列，队头为 **1** 号运动员，队尾为 **n** 号运动员。

每轮一次比赛，**队头**的两个人进行格斗，**赢的人（实力较强的人）变成队头，输的人变成队尾** 。

Burenka 问了 Tonya **q** 个问题，每个问题包含两个整数 **i** 和 **k** ，表示 **i 号运动员在前 k 轮中会胜多少场**。

## 样例 #1

### 输入

```
3
3 1
3 1 2
1 2
4 2
1 3 4 2
4 5
3 2
5 2
1 2 3 5 4
5 1000000000
4 6```

### 输出

```
2
0
1
0
4```

# 题解

## 作者：Eason2009 (赞：11)

小萌新第一次在场上写出线段树题![](//啧.tk/hsh)

------------
[题目传送门](https://www.luogu.com.cn/problem/CF1719C)

首先我们可以发现一个性质：

当实力最强的运动员（也就是 $a_i=n$ 的运动员）到队头或者队里的第二个人时，接下来的比赛中，这位运动员将全部取胜，剩下的所有人都一场也赢不了。

按照这个思路，我们可以进行分类讨论：

设这位运动员的编号为 $i$。

情况 $1$：这次询问的运动员是全场实力最强的（也就是 $a_i=n$）。

这时如果当 $i=1$ 或 $i=2$，说明接下来的所有比赛，这个运动员将会全胜，直接输出 $k$。

否则输出 $k-i+2$，因为这位选手前 $i-2$ 轮比赛都没有被轮到。

注意输出的时候要和 $0$ 比较一下。

情况 $2$：这次询问的运动员前面的运动员已经有运动员的实力大于自己的实力的了。

这时，就说明这位运动员已经被单调队列了，无论如何也轮不到自己，直接输出 $0$。

~~所以大家可不能被单调队列啊。~~

具体实现时可以维护一个前缀最大值，询问的时候比较一下大小即可。

情况 $3$：这次询问的运动员前面的运动员没有运动员的实力大于自己的实力，但是后面有（因为已经不可能是最大值了所以一定有运动员的实力大于自己）。

这个时候就比较麻烦了。

首先我们可以得出：第一个击败这位运动员的运动员一定是编号在这位运动员后面，并且实力比这位运动员强的运动员（设第一个击败这位运动员的运动员的编号为 $j$）。

这个时候我们就可以使用线段树来维护区间最大值。

询问时，直接在线段树上二分即可。

那么这个时候的答案是什么呢？（假设没有 $k$ 的限制）

当 $i=1$ 时，这位运动员的身前没有人可以战胜，所以输出 $j-i-1$。

当 $i>1$ 时，说明这位运动员可以战胜一位编号比自己小的运动员，所以输出 $j-i$。

最后再和 $k$  比较一下大小即可。

代码实现（有许多细节，建议读者耐心看完）：

```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int t,n,q,a[maxn],pos,k,mx[maxn],mn[maxn],tree[maxn*4];
string s;
void pushup(int now)
{
	tree[now]=max(tree[now*2],tree[now*2+1]);
	return;
}
void build(int now,int l,int r)
{
	if(l==r)
	{
		tree[now]=a[l];
		return;
	}
	int mid=l+r>>1;
	build(now*2,l,mid);
	build(now*2+1,mid+1,r);
	pushup(now);
	return;
}
int query(int now,int l,int r)
{
	if(l==r) return l;
	int mid=l+r>>1;
	//if(mid<=pos) return query(now*2+1,mid+1,r);
	if(tree[now*2]>a[pos]) return query(now*2,l,mid);
	else return query(now*2+1,mid+1,r);
}
signed main()
{
	cin>>t;
	while(t--)
	{
		bool flag=0;
		cin>>n>>q;
		for(int i=1;i<=n;i++)
		{
			mx[i]=0;
			cin>>a[i];
		}
		build(1,1,n);
		for(int i=1;i<=n;i++)
		{
			mx[i]=max(a[i],mx[i-1]);
		}
		while(q--)
		{
			cin>>pos>>k;
			if(a[pos]==n)
			{
				if(pos==1)
				{
					cout<<k<<endl;
					continue;
				}
				cout<<max(k-(pos-2),0)<<endl;
				continue;
			}
			else if(a[pos]<mx[pos-1])
			{
				cout<<0<<endl;
				continue;
			}
			else
			{
				int nowpos=query(1,1,n);
				if(pos==1) cout<<min(k,nowpos-2)<<endl;
				else cout<<min(max(k-(pos-2),0),nowpos-pos)<<endl;
			}
		}
	}
	return 0;
}
```

这种方法虽然写起来有些不方便，但我个人认为还是比较好理解的。

最后，祝大家学习愉快![](//啧.tk/qq)

---

## 作者：Hedgehog_210508 (赞：7)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1719C)

**题意简述**：$n$ 个数，每次操作将前两个数比大小，较大的放回队首，较小的放队尾。其次 $q$ 次问询，输出第 $i$ 个数在前 $k$ 次操作获胜几次。

**思路**：
我们通过模拟样例并稍加思考发现： $n-1$ 次比较之后一定是 $n$ 与别人比较，且必定是 $n$ 获胜。

我们只需要单独计算前 $n-1$ 次比较的结果即可。

**代码实现**：
考虑到 $i$ 号获胜只可能是连续的一段操作（因为它失败之后必定会有更大的人顶替，不可能再次上台），维护每个数值连胜的开始时间与结束时间就行了。详见代码。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		ll n,q,a[100009],s[100009],e[100009];
		cin>>n>>q;
		for(ll i=1;i<=n;s[i]=e[i]=0,i++) cin>>a[i];
		ll m=a[1];
		s[m]=1;
		for(ll i=2;i<=n;i++){
			if(a[i]>m) s[a[i]]=i-1,e[m]=i-2,m=a[i];
		}
		e[m]=n-1;
		for(ll i=1;i<=q;i++){
			ll p,k,ans=0;
			cin>>p>>k;
			p=a[p];
			if(p==n){
				ans+=max(ll(0),k-n+1);
			}
			ans+=max(ll(0),min(e[p],k)-s[p]+1);
			if(s[p]==0) ans-=max(ll(0),min(e[p],k)-s[p]+1);
			cout<<ans<<endl;
		}
	}
    return 0;
}
```


---

## 作者：Dregen_Yor (赞：4)

[博客食用效果更佳](https://www.cnblogs.com/Dregen-Yor/p/16596321.html)。

# 思路

根据题意，很容易看出，每个人都完成一次比赛后，即完成 $n-1$ 轮之后，力量值最大的人会留在第一的位置，且在第 $n-1$ 轮完成后，除了力量值最大的人，其他人的胜场数都不会再增加了。所以问题的关键是求所有人都完成一轮，即前 $n-1$ 轮比赛之前的答案。

考虑将所有询问离线处理，并按 $k$ 的大小进行排序，然后暴力模拟前 $n-1$ 轮比赛的情况，同时统计出所有求前 $n-1$ 轮的询问的答案，并储存下来。之后统计 $n-1$ 轮之后的答案的时候判断一下当前询问的点是不是最大值，如果是最大值，在 $n-1$ 轮结束后的答案上加上 $k-n+1$。如果不是最大值直接输出 $n-1$ 轮结束时的答案即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, q, a[100010], ans[100010], w[100010];

struct node {
	int x, k, num;
} ask[100010];

bool cmp(node a, node b) {
	return a.k < b.k;
}

signed main() {
	scanf("%lld", &t);

	while (t--) {
		memset(w, 0, sizeof(w));
		memset(ans, 0, sizeof(ans));
		scanf("%lld%lld", &n, &q);

		for (int i = 1; i <= n; i++) {

			scanf("%lld", &a[i]);
		}

		for (int i = 1; i <= q; i++) {

			scanf("%lld%lld", &ask[i].x, &ask[i].k);
			ask[i].num = i;
		}

		int tot = 1, now = 1;
		sort(ask + 1, ask + 1 + q, cmp);

		for (int i = 2; i <= n; i++) {

			if (a[i] > a[now]) {
				w[i]++;
				now = i;
			} else {
				w[now]++;
			}

			while (ask[tot].k == (i - 1) && tot <= q) {
				ans[ask[tot].num] = w[ask[tot].x];
				tot++;
			}
		}

		for (int i = tot; i <= q; i++) {

			if (ask[i].x != now) {
				ans[ask[i].num] = w[ask[i].x];
			} else {
				ans[ask[i].num] = w[now] + (ask[i].k - n + 1);
			}
		}

		for (int i = 1; i <= q; i++) {

			printf("%lld\n", ans[i]);
		}
	}

	return 0;
}

```


---

## 作者：cjlak1o1 (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1719C)

### 题目大意

序列中的数为 $1$ 到 $n$ 的排列的乱序状态

每一轮选取序列中前两个数，把大的放在序列最前面，把小的放在序列最后。

每次询问原数列第 $i$ 位前 $k$ 轮赢的次数。

### 具体思路

首先，我们要注意一个特殊性质：

- **经过最多不超过 $n-1$ 轮后，赢的人之后将一直会是最大的数，一直排在第一位。**

那么就可以得出一个结论：

- **每一位赢的轮数都是连续的。**

所以我们只要记录一下每一位开始赢和最后一次赢的分别的轮数即可。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1e3;

inline int read(){
	char ch=getchar();int res=0,f=1;
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}

int T,n,k;
int a[N],cnt[N][2],b[N],tot=1,K;
deque<int> q;

int main(){
	T=read();
	while(T--){
		n=read(),k=read();int Max;
		for(int i=1;i<=n;i++){
			a[i]=read();cnt[i][0]=cnt[i][1]=0;
			if(a[i]==n) Max=i;
		}
		//for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		int last=1;cnt[1][0]=1;
		for(int i=2;i<=n;i++){
			if(last==Max) break;
			if(a[last]<a[i]){
				//cout<<last<<endl;
				cnt[last][1]=i-1;
				last=i;
				cnt[last][0]=i-1;
			}
		}
		for(int i=1,id,times;i<=k;i++){
			id=read(),times=read();
			if(id!=Max){
				if(!cnt[id][0]) puts("0");
				else{
					printf("%d\n",max(min(cnt[id][1],times+1)-cnt[id][0],0));
				}
			}
			else printf("%d\n",max(times-max(Max-2,0),0));
		}
	}
}
/*
1
11 11
10 5 7 6 9 4 2 8 1 11 3
1 1
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
*/
```
**蒟蒻拙见，请指教。**

---

## 作者：D2T1 (赞：3)

## div2C. Fighting Tournament

下文中的“它”指 $a_i$。

考虑三种情况：

- 如果 $a_i$ 是 $a$ 中最大的数，那么它参加的所有比赛都必定会获胜，而且它一到第一位就会一直在第一位进行比赛（因为没有其它数字能使它排到最后去）。
- 如果 $\max\limits_{j=1}^{i-1}\{a_j\} > a_i$，那么如果它能够参加比赛，它必定会与它前面那个比它打的对决，所以它必输，答案为 $0$。
- 否则，它会打赢它前面的最大数，并输给它后面第一个比它大的数。这里可以使用单调栈预处理一下。

还有一些细节，比如它根本打不到这么多场，所以还要考虑一下 $k$。具体可以参考代码。

```cpp
#define multiple_test_cases
 
const int N = 1e5 + 10;
int n, q, a[N], mx[N], st[N], lm[N], tot;
 
void solve(){
	n = rdi;
	q = rdi;
	tot = 0;
	for(int i = 1; i <= n; ++ i){
		a[i] = rdi;
		st[i] = lm[i] = 0;
		mx[i] = max(mx[i-1], a[i]);
	}
	st[0] = 0x3f3f3f3f;
	for(int i = n; i >= 1; -- i){
		while(tot && a[st[tot]] < a[i]){
			-- tot;
		}
		lm[i] = st[tot];
		st[++tot] = i;
	}
	while(q--){
		int id = rdi;
		int k = rdi;
		if(id != 1 && id > k + 1){
			puts("0");
		} else if(mx[id-1] > a[id]){
			puts("0");
		} else if(a[id] == n){
			printf("%d\n", k - (id == 1 ? 2 : id) + 2);
		} else {
			int r = min(n, k + 2);
			printf("%d\n", max(0, min(lm[id], r) - (id == 1 ? 2 : id)));
		}
	}
}
```

---

## 作者：xzy090626 (赞：1)

# CF1719C 题解
## 前言
这题好细节啊，似乎是我第 $3$ 道 $\ge$ \*1400 的 Div.2C。

由于是在 archive 里做的，所以放开交了（

下面请欣赏——

![](https://cdn.luogu.com.cn/upload/image_hosting/db7vkgud.png)
## 题意
翻译有点麻烦了，但是很准确。

简单地说就是给定 $n$ 个数，每次把 $a_1$ 和 $a_2$ 进行比较，大的作为 $a_1$，小的放到队尾。$q$ 次询问，每次给定下标 $i$ 和比较次数 $k$，求 $k$ 次比较中 $a_i$ 赢的次数。

注意，$a$ 是一个全排列，因此 $a$ 中**无重复元素**，这一点非常重要。
## 分析
### 0.时间复杂度
容易发现，$n,q\le10^5$，所以询问必须是 $O(1)$ 的回答，预处理也应该是 $O(n)$ 或者 $O(n\log n)$ 的。

这里我写的是 $O(n\log n)$ 的二分。
### 1.观察性质
注意到，当第 $i$ 个数轮到自己的第一次比较时，一定是与 $\max\{a_{[1,i-1]}\}$ 进行比较，因此我们可以找出它前面的最大值，然后比较。如果它比 $\max$ 小，那么它不可能赢任何一次。否则，它会赢至少一次。

但是这里注意到，当 $i=1$ 时，这个是不适用的，所以这题的第一个 corner case 就在这里（对于我的二分而言）。

接着我们观察，看到如果 $a_i$ 后面仍有一段连续的比 $a_i$ 小的序列，那么 $a_i$ 还会赢一些轮。

又可以发现一个 detail，那就是 $k\le10^9$，也就是说，有的数会一直赢。

容易发现这个数就是最大值，因为最大值一旦轮到队首会一直呆在那里。
### 2.寻找最大值
我们发现，对于 $a_i$，如果要求它能赢的次数，我们必须知道最大的 $j$ 使得 $a_{[1,j]}<a_i$，即第一个大于 $a_i$ 的数的前一个。

我们可以感性地把 $a_{[1,j]}$ 理解为 $a_i$ 的「势力范围」。

如何求这个 $j$ 呢？

$O(n^2)$ 的暴力肯定行不通。

容易发现，我们可以维护 $f[i] = \max\{s_{[1,i]}\}$，递推式也很好写，就是 $f[i] = \max(f[i-1],s[i])$。

接着，我们会发现 $f$ 是单调不递减的，可以二分。

于是我们可以愉快地二分到一个 $f[i]$ 使得 $f[i]\le s[i]$，然后 $[1,i]$ 就是 $s[i]$ 的「势力范围」。

这里我用的是 `upper_bound`。
### 3.处理询问
$k$ 是最为细节的地方。

首先，如果 $i$ 的 「势力范围」 在 $i$ 前面，那肯定没戏。

或者如果 $k$ 轮都还轮不到 $i$，那也没戏，即 $k+1<i$。

接着我们开始判断了：
- 如果 $s[i]$ 是最大值，那么答案就是 $k+2-i$。

当然这是错的，因为没有特判 $i=1$。

正确的答案见 code（~~其实是为了让你们好好看看代码，毕竟我调了几十分钟~~

- 否则，如果 $k$ 足够大，那么就是 $j+1-i$。

当然这也是错的，因为没有特判。

- 如果 $k$ 不够大，那么就是 $k+1-i$。

~~当然这也是错的，因为没有特判。~~

正确答案见 code。
### 4.关于 $i=1$
这个时候为什么要特判呢？

当 $i=1$ 且 $s[i]$ 为最大值时，显然会赢 $k$ 轮。

但是如果反之，$i$ 不为 $1$，那么会赢 $k+2-i$ 轮，比如当 $i=2$ 时，会赢 $k$ 轮，但是如果 $i=1$，此时 $k+2-i=k-1$，是不对的。

其他时候也是同理。

根本的角度来说，就是因为 $s_1$ 会参与第一轮，但是 $s_2$ 也会！
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 7;
int s[N],a[N],ans[N];
void solve(){
	int n,q;
	cin>>n>>q;
	memset(a,0,n+10);
	for(int i=1;i<=n;++i){
		cin>>s[i];
	 	a[i] = max(a[i-1],s[i]);
	}
	for(int i=1;i<=n;++i){
		auto p = upper_bound(a+1,a+n+1,s[i]);
		if(*p!=s[i]) --p;
		ans[i] = p-a;
	}
	while(q--){
		int id,k;
		cin>>id>>k;
		if(ans[id]<id || k+1<id) cout<<"0\n";
		else{
			if(ans[id]==a[n]) cout<<k+1-max(id-1,1ll)<<'\n';
			else cout<<min(ans[id],k+1)+(id==1?0:1)-id<<'\n';
		}
	}
}
signed main(){
	//freopen("test.in","r",stdin); 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
	while(T--) solve(); 
    return 0;
}
```
## 总结
不要摆烂！

吃了很多发罚时仍然有可能 Accept，就像开头的图片一样。

**心态是最为重要的，在任何方面。**

---

## 作者：zry……yrz (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1719C)

### 题目大意

有一个长度为 $n$ 的排列，每次选取数组前两人进行比较，强度值大的人排在数组最前，强度值小的人排在数组最后。每次询问给出编号 $i$ 和轮数 $k$，查询在前 $k$ 轮比较中编号为 $i$ 的人赢了几轮。

### 解题思路

由题面可得，$n-1$ 轮比较之后，数组中最大的数必然排在数组最前，且之后的比较也必然是其赢。

那么可以先从左到右进行遍历，判断前 $n-1$ 轮比较中各个编号的人分别赢了几轮。

查询时都将查询的人强度值当做数组中最高的来计算，那么若

- 查询的人编号为 $1$，则其最多能赢 $k-i+1$ 轮。

- 否则其最多能赢 $k-i+2$ 轮。

并将该值与 $0$ 取较大值。

如果查询的人强度值真为数组中最大值，则直接将该值输出，否则再与预处理出的前 $n-1$ 轮其能赢的轮数取较小值输出。

```cpp
//いつもこのような人がいます。優しくしてあげたいです。
#include <bits/stdc++.h>
using namespace std;
int T,n,m,i,Max,y,b,c;
int a[100500],jl[100500];
inline int read()
{
	int s=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=(s<<3)+(s<<1)+c-'0';
		c=getchar();
	}
	return s*f;
}
int main()
{
    T=read();
    while(T)
    {
    	n=read(),m=read();
    	Max=0,y=0;
    	for(i=1;i<=n;i++)
    	{
    		a[i]=read(),jl[i]=0;
    		if(a[i]>Max)//如果强度值比其编号小的人都大，那么他能在前n-1轮赢
			{
				if(y==1) jl[y]=i-y-1;
				else jl[y]=i-y;
				Max=a[i],y=i;
			}
		}
		for(i=1;i<=m;i++)
		{
			b=read(),c=read();
			if(a[b]!=n)//查询的人强度值不是数组中最大的
			{
				if(b==1) printf("%d\n",min(jl[b],max(0,c-b+1)));
				else printf("%d\n",min(jl[b],max(0,c-b+2)));
			}
			else
			{
				if(b==1) printf("%d\n",max(0,c-b+1));
				else printf("%d\n",max(0,c-b+2));
			}
		}
    	T--;
	}
    return 0;
}
```


---

## 作者：lightningZ (赞：0)

## 思路

首先我们发现，只要数列中的最大值到了队头，那么它就会一直赢下去。所以我们只需要预处理出最大值前面那些数会赢多少次，这个显然是小于 $O(n)$ 就可以解决的。

然后，我们考虑怎么计算这个多少次。可以发现，我们直接存储当前的队头，一开始为 $1$。随着 $i$ 每次向后枚举，我们判断一下  $i$ 和队头的关系。如果 $i$ 更大那么 $i$ 赢得次数加一，同时队头变成 $i$。否则原来的队头赢得次数加一。时间复杂度 $O(n)$。

接着考虑怎么处理查询。分成两大类：

1. 查询的次数 $k$ 大于最大值的位置 $p$

	- 查询的是最大值：将 $k$ 减去 $p$，这样队头就是最大值了。那么他是队头的时候，会赢多少次呢？显然是 $k-p+1$。但是它不是队头的时候，和队头的数比较也会赢一次，所以要加一。但注意如果他是第一个数，他不会多赢这一次，因此特判一下即可。
    
	- 查询的不是最大值：按照预处理的次数来就行了，因为在最大值成为队头之后，它永远不可能再赢了。
    
2. 查询的次数 $k$ 小于最大值的位置 $p$

	- 如果 $k=p-1$，那么其实处理方法和上面一样。

	- 如果 $k$ 比 $p-1$ 还小，那么我们可以把所有询问离线下来，按照询问的次数 $k$ 排序。然后，重新按照预处理的方法从 $1$ 到 $n$ 扫一遍，同时用另一个指针 $j$ 记录询问的位置。每次如果发现打的次数 $i-1$ 和 $k_j$ 相同了，我们就把这个时候它询问的数 $x$ 赢得次数存到答案中。

所以我们在处理 $1$ 操作的时候，也不要直接输出，存到 $ans$ 数组中，最后一起输出即可。

时间复杂度 $O(n \log n)$，瓶颈在于要对询问进行排序。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100005;
int a[MAXN],times[MAXN]; // times[i] 表示 i 赢得次数 
int ans[MAXN];
struct Node{int x,y,id;}ask[MAXN]; // 存储询问 
bool cmp1(Node xx,Node yy){ // 按照询问的打架的次数排序 
	return xx.y<yy.y;
}
int main(){
	int T; cin>>T;
	while(T--){
		int n,q; cin>>n>>q;
		int flag=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			times[i]=0; // 清空次数不要用 memset。 
			if(a[i]==n) flag=i; // 找到最大值的位置 
		}
		int lst=1; // 队头一开始是 1 
		for(int i=2;i<flag;i++){ // 只需要预处理最大值之前的就够了 
			if(a[i]<a[lst]) times[lst]++; // 如果队头更大，那么队头++ 
			else times[i]++,lst=i; // 否则 i 次数++，同时更新队头 
		}
		int tot=0;
		for(int i=1;i<=q;i++){
			int x,k; cin>>x>>k;
			if(k<flag-1) ask[++tot]=(Node){x,k,i}; // 如果小于最大值所在的位置就离线下来 
			else{ // 否则直接计算答案 
				if(x!=flag) ans[i]=times[x]; // 如果不是最大值，那么答案就是 times[x] 
				else ans[i]=k-flag+1+(flag!=1); // 否则就用 k-p+1+(p!=1) 计算一下答案 
			}
		}
		sort(ask+1,ask+1+tot,cmp1); // 排序 
		for(int i=1;i<=n;i++) times[i]=0; // 重新清零 
		int j=1; lst=1;
		for(int i=2;i<flag;i++){
			if(a[i]<a[lst]) times[lst]++;
			else times[i]++,lst=i;
			while(j<=tot && ask[j].y==i-1){ // 处理当前打架次数为 i-1 的询问 
				ans[ask[j].id]=times[ask[j].x];
				j++;
			}
		}
		for(int i=1;i<=q;i++) cout<<ans[i]<<endl; // 输出答案 
	}
	return 0;
}
```

---

## 作者：zhicheng (赞：0)

### 思路

我们先考虑前 $n-1$ 次比赛。比赛完后在队伍最前面的一定是最大的数，那么不管以后有多少比赛，不是最大值的数一定一局也赢不了。

我们先预处理出前 $n-1$ 次比赛的胜者的**编号**（记为数组 $p$），因为是从前往后进行的，所以这个编号序列一定不下降。先判断 $\min(n-1,k)$ 是否大于 $i-1$（第 $i$ 个是否要参加），然后求解：

1.  对于不是最大值的数，我们在前 $\min(n-1,k)$ 次比赛中求出答案即可：

    - 如果第 $i-1$ 次比赛的获胜者**是**编号为 $i$ 的人，那么我们在 $[p_1,p_{\min(n-1,k)}]$ 中二分查找第一个大于 $p_i$ 的数（用 `lower_bound` 函数），找到下标后再减去 $i-1$（因为它从第 $i-1$ 次就开始赢，赢到查找值减 $1$） ，就是答案了。但是如果 $i=1$ ，没有第 $0$ 局，所以要减 $1$。
    
    - 否则它一局也没赢。
    
2. 对于是最大值的数，除了它没参加的局没有赢，其他一定都赢了，所以手推一下就是 $l-(i-2)$。同样的，如果 $i=1$ ，要减 $1$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[100010],q[100010];
int main(){
	int n,a,k,u,l,ans,h;
	scanf("%d",&n);
	while(n--){
		memset(q,0,sizeof(q));
		scanf("%d%d",&a,&k);
		for(int i=1;i<=a;i++){
			scanf("%d",&q[i]);
		}
		p[0]=1; //“第零局”，方便第一个数的预处理，
		for(int i=2;i<=a;i++){  //预处理赢的编号
			if(q[i]>q[i-1]){
				p[i-1]=i;
			}
			else{
				q[i]=q[i-1];  //记录最大值
				p[i-1]=p[i-2];
			}
		}
		while(k--){
			ans=0;
			scanf("%d%d",&u,&l);
			h=min(l,a-1); //求min
			if(p[u-1]==u&&p[u-1]==p[a-1]&&h>=u-1){ //是最大值
				ans=l-(u-2)+(u==1?-1:0);
			}
			else if(p[u-1]==u&&h>=u-1){  //不是最大值
				ans=upper_bound(p+1,p+h+1,u)-p-(u-1)+(u==1?-1:0);
			}
			printf("%d\n",ans);
		}
	}
}
```

---

## 作者：_1437_ (赞：0)

这题的操作分为 $2$ 个阶段：

第一阶段：$n$ 还没有到首位，其他的选手在乱斗。

第二阶段：$n$ 到首位，$n$ 垄断了后面的获胜轮数。此后不会有除了 $n$ 之外的选手获胜。

对于一般的选手（即满足 $i\not= n$），设 $i$ 出现的位置为 $pos_i$：

如果一个选手前面有比他大的选手，他永远也不会获胜，此时特殊记录。

否则，他将会在第 $(pos_i-1)$ 轮迎来胜局，接下来将一直赢，赢到他后面出现的第一个比他大的选手将他击败，以后便不再赢。

对于 $i=n$，将会自从 $(pos_n-1)$ 轮一直赢。

理清楚这个思路之后，Code 就不难写了。

我使用 $s$ 数组记录后面出现的第一个比他大的选手的位置。

```cpp
int solve() {
	int n = getInt(), q = getInt();
	rep(i, 1, n + 5) p[i] = 0, pos[i] = 0, s[i] = 0;
	int maxn = 0, maxi = 0;
	rep(i, 1, n) {
		p[i] = getInt();
		maxn = max(maxn, p[i]);
		if(maxn != p[i]) {
			s[i] = -1;
		} else {
			s[maxi] = i - maxi - 1;
			maxi = i;
		}
		pos[p[i]] = i;
	}
	while(q--) {
		int x = getInt(), k = getInt();
		if(s[x] == -1) {
			cout << 0 << endl;
			continue;
		}
		int po = pos[p[x]];
		if(k < po - 1) {
			cout << 0 << endl;
			continue;
		}
		int ppo = (po < 2 ? 0 : po - 2);
		if(k <= po - 1 + s[x]) {
			cout << k - ppo << endl;
			continue;
		}
		if(p[x] == n) {
			cout << k - ppo << endl;
			continue;
		}
		if(x == 1) {
			cout << s[x] << endl;
			continue;
		}
		cout << 1 + s[x] << endl;
	}
	return 0;
}
```

---

## 作者：Lovable_Wind (赞：0)

由于前两题都是推结论的题，做这题时也先上手推了一下结论。（**以下所有表述默认 $i$ 从 $1$ 到 $n$**)

考虑样例数列，手玩一波

$1$ $3$ $4$ $2$

因为 $1<3$，将 $1$ 推至尾部，得

$3$ $4$ $2$ $1$

同理推得以下数列

$4$ $2$ $1$ $3$

$4$ $1$ $3$ $2$

$4$ $3$ $2$ $1$

若进一步下推，则可得

$4$ $2$ $1$ $3$

此时与前面的数列重复，即表明已经出现循环。

考虑出现循环的 **原因**，是因为最大值永远不会换掉，每一个数前来比较，结果一定相同。而由此可以得到结论：

在最大值到达第一个位置之后，所有非最大值的数字一定不会胜利，而最大值数字每场都胜利。

而若最大值初始在位置 $i$ ，到达第一个位置所需要的轮数应为 $i-1$。

于是，考虑模拟最大值到第一个位置的过程。因为只需要考虑首尾，用双端队列来维护。

而由于可能会有在 $i-1$ 轮内的提问，考虑用优先队列存储提问，然后在模拟时存储这些提问的答案到 $ans$ 数组。

在 $i-1$ 轮后的提问，判断是否是最大值，**若是**，则将前 $i-1$ 轮的获胜数与 $k-i+1$ 相加 ( $k$ 为询问的轮数）作为答案。**若不是**，则直接输出前 $i-1$ 轮中模拟出的答案。

---

## 作者：小木虫 (赞：0)

### Preface  
一道很小清新的 C 题，趁着没有题解先抢个沙发先。  
### Problem  
$n$ 个能力互不相同且能力序列为 $1$ 到 $n$ 的数字的一个排列的人打擂台，每次序列的前两个人打，赢的回原位，输的去尾部。  
现在给你 $q$ 次询问，每次询问问 $x$ 经过 $k$ 轮擂台赛后赢了多少次。$(k\leq 10^9)$  
### Solution  
乍一看这个 $k$ 这么大这题好像很牛逼一样，但是实际你想一下经过最多 $n$ 轮游戏后这些人里最厉害的就会排到最前面，那么之后其它人就再也不可能赢了，每次都是这个人赢，于是我们将询问按时间离线下来，用双端队列模拟打擂台过程，然后让轮数大于 $n$ 次的询问分类讨论，如果问的是最厉害的人那么直接后面全赢，不然一次都赢不了。  
code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int T;int n,q,a[N];
int w[N];int res[N];int d[N];
struct Qry{
	int x,t,id;
}Q[N];
bool cmp(Qry a,Qry b){
	return a.t<b.t;
}
void init(){
	
}
void solve(){
	cin>>n>>q;int head=100000;int tail=n+100000-1;
	for(int i=100000;i<n+100000;i++)
		cin>>a[i],d[a[i]]=i-100000+1;
	for(int i=1;i<=n;i++)w[i]=0;
	for(int i=1;i<=q;i++){
		cin>>Q[i].x>>Q[i].t,Q[i].id=i;
	}int p=1;
	sort(Q+1,Q+1+q,cmp);
	for(int i=1;i<=n;i++){
		if(a[head]>a[head+1]){
			swap(a[head],a[head+1]);
		}
		w[d[a[head+1]]]++;
		a[++tail]=a[head];
		head++;
		while(i==Q[p].t){
			res[Q[p].id]=w[Q[p].x];
			p++;if(p>q)break;
		}
		if(p>q)break;
	}
	while(p<=q){
		if(Q[p].x!=d[a[head]]){
			res[Q[p].id]=w[Q[p].x];
		}else{
			res[Q[p].id]=w[Q[p].x]+Q[p].t-n;
		}
		p++;
	}
	for(int i=1;i<=q;i++)
		cout<<res[i]<<endl;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)init(),solve();
	return 0;
}
```


---

## 作者：芝麻馅儿汤圆 (赞：0)

## 题意
有一场格斗锦标赛，规则如下：

每轮取队首两个运动员比赛，实力值高的获胜。胜者放回队首，败者放于队尾，

现给定一个长度为 $ n $ 的数组，表征每位运动员的实力，给定多次询问，对于每次询问：

给定两个数 $ i $ , $ k $  , 你需要求出**原顺序**第 $ i $ 个运动员前 $ k $ 轮获胜次数。

特殊约定：全体运动员实力表征值集合 保证是一个长度为  $ n $ 的全排列。

## 分析
首先对样例手测一遍，我们会发现，对于每组运动员的前两位，ta们最早比赛是第 $ 1 $ 场，对于其他运动员，最早比赛是第 $ i - 1 $ 场。并且当能打败ta的运动员一旦出现，那么ta就不会再获胜（因为比ta强的总在队首），同理可知，若ta前面存在比ta强大的 那么ta也无获胜机会。而对于最强大的运动员，则在轮到ta以后，还能进行几轮则赢几轮（注意对于每次询问要特判是否能够进行比赛）
于是问题被分解为两个部分：
#### Part1：
求一个无序数列第一个大于它本身的数的位置，观察数据范围，暴力查找的复杂度是 $ O(n^2) $ ，显然过不去。所以考虑单调栈（不会的小伙伴戳[P5788](https://www.luogu.com.cn/problem/P5788)）该数据结构支持 $ O(n) $ 复杂度，维护一个数组每个数第一个大于它本身的数的位置。
#### Part2：
求每个数是否被"覆盖"，这里直接用 $ O(n) $ 暴力遍历一遍即可。

## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

#define lli long long int
#define endl "\n"
#define shang_ge_buff ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);

using namespace std;

const int maxn = 2e5 + 27;

int a[maxn], b[maxn], st[maxn], wp[maxn], tp = 0;

void solve() {
	memset(wp, 0, sizeof wp);
	memset(st, 0, sizeof st);
	int n, mxs, q;
	cin >> n >> q;
	//输入数据并记录最奆运动员的位置 
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] == n)
			mxs = i;
	}
	int kl, op;
	//对运动员记录"(被)覆盖"信息 
	int lc = a[1];
	b[1] = lc;
	for (int i = 2; i <= n; i++) {
		if (lc > a[i])
			b[i] = lc;
		else
			lc = a[i], b[i] = a[i];
	}
	//单调栈维护"该数字在该数列出现的第一个比他大的数" 
	for (int i = n; i >= 1; --i) {
		while (tp && a[st[tp]] <= a[i])
			tp--;
		wp[i] = st[tp];
		st[++tp] = i;
	}
	for (int i = 1; i <= q; i++) {
		cin >> kl >> op;
		//如果ta被覆盖了 说明ta没机会获胜 
		if(b[kl] != a[kl]) {
			cout << 0 << endl;
		}
		//如果最强的就是ta 
		else if(kl == mxs) {
			//初始在第一场比赛内 
			if(kl == 1 || kl == 2) {
				cout << op << endl;
			}
			//初始不在第一场比赛内 
			else {
				op -= kl - 2;
				op > 0 ? cout << op << endl : cout << 0 << endl;
			}
		}
		//如果最强的不是ta  且没有被"覆盖" 
		else {
			//初始在第一场比赛内 
			if(kl == 1) {
				(op > wp[kl] - kl - 1) ? cout << wp[kl] - kl - 1: cout << op;
			}
			else if(kl == 2) {
				if(op == 1)
					cout << (a[2] > a[1]);
				else {
					int jdslf;
					jdslf = wp[kl] - kl;
					jdslf > op ? cout << op : cout << jdslf;
				}
			}
			//不在第一场比赛内 
			else {
				op -= kl - 2;
				if(op < 0)
					op = 0;
				(op > wp[kl] - kl) ? cout << wp[kl] - kl : cout << op;
			}
			cout << endl;
		}
	}
	return ;
}

int main() {
	shang_ge_buff
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}
```


---

## 作者：Keroshi (赞：0)

# 题意
给出 $n$ 个人的强度 $a_1$ 到 $a_n$，在战斗中，如果 $a_i>a_j$，则第 $i$ 个人总能赢得第 $j$ 个人。   
在比赛中，排在队伍最前面的两个人出来战斗，获胜者到队伍的最前面，失败者到队伍的后面。   
每次询问第 $i$ 个人在前 $k$ 轮比赛中获得了多少胜利。  
# 题目分析   
先看一个例子：有五个人进行战斗，下图是他们的战斗情况。   
![](https://cdn.luogu.com.cn/upload/image_hosting/wr25shpr.png)   
不难发现，经过 $n$ 轮已后，第一个数总是他们强度的最大值。   
而第 $n$ 轮中，第一个数是前 $n+1$ 项的最大值。
那么可以想到，记录每个人进入队头的时间和退出队头的时间，每个人的总时间就是退出队头和进入队头时间差。
时间复杂度 $O(n)$。
# 代码   
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,q,a[N],s1[N],s2[N];
int main(){
    scanf("%d",&t);
    while(t--){
        memset(s1,0,sizeof(s1));
        memset(s2,0,sizeof(s2));
        scanf("%d%d",&n,&q);
        int maxx=0; // 最大值
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            if(a[i]>maxx){
                s1[a[i]]=i; // 更新进入队头时间
                s2[maxx]=i; // 更新推出队头时间
                maxx=a[i];
            }
        }
        for(int i=1;i<=q;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            x=a[x];
            if(x==maxx){ // 为最大值
                if(s1[x]==1) printf("%d\n",max(0,y+2-s1[x])-1); // 当一开始就为队头时的特判
                else printf("%d\n",max(0,y+2-s1[x]));
            }
	       else{ // 不为最大值
                if(s1[x]==0) printf("0\n"); // 没有进入过队头
                else {
                    if(s1[x]==1) printf("%d\n",max(0,min(y+2,s2[x])-s1[x]-1)); // 当一开始就为队头时的特判
                    else printf("%d\n",max(0,min(y+2,s2[x])-s1[x]));
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：cachejtt (赞：0)

## 题意
给你 $n$ 位选手，他们每个人有一个能力值 $a_i$，保证 $a$ 是 $n$ 的排列。初始他们按 $1$ 至 $n$ 的顺序排成一列。每次，站在队头的两位选手走出来，打一场比赛，能力值高的那个人赢得这场比赛，并回到队头，输的人归到队尾。

有 $q$ 次询问，每次给出序号 $i$ 和 $k$，问你，编号为 $i$ 的选手（注意不是能力值为 $i$）在前 $k$ 场比赛中赢了几场？

## 思路
考虑经过最多 $n$ 场后，能力值最大的人（即能力值为 $n$ 的人一定会做当前擂主），此后其他人再也赢不到，而是他赢下每一场。

我们假设经过 $cnt$ 场比赛，能力值为 $n$ 的人当上了擂主。

预处理一个表示前 $cnt$ 场中，其他人赢了几场的数组 $g$。$g_i$ 表示编号为 $i$ 的人赢了几场。

这样当询问的 $k\ge cnt$ 时，其他的人的答案即为 $g_i$，最大的人的答案为 $k-cnt+g_i$。

那么，当 $k<cnt$ 时，又该怎么办呢？我们考虑处理两个数组 $l$ 和 $r$，分别代表第 $i$ 个人当上擂主的比赛场数区间，也就是说，第 $i$ 个人从第 $l_i$ 场比赛开始当擂主，第 $r_i$ 场比赛是他当擂主的最后一场。

这样的话，只需把 $k$ 与 $l_i$ 和 $r_i$ 比较即可。

- 若 $k>r_i$，则赢了 $r_i-l_i+1$ 场。这里有个小细节，若 $l_i=r_i=0$，他应该赢了 $0$ 场而不是 $1$ 场，因此对于所有 $r_i=0$ 应将其赋值为 $-1$。
- 若 $k<l_i$，则他还没开始当擂主，因此一场都赢不到。
- 否则，$k$ 落在 $l_i$ 到 $r_i$ 中间。则目前他已经是擂主，还没结束他的擂主。因此答案为 $k-l_i+1$。

## 代码
多组数据注意清零。

```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ms(x, i) memset((x),(i),sizeof x)
#define endl "\n"
using namespace std;
int t=1,n,qq,a[200005],g[200005],l[200005],r[200005],x,y;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>qq;
    ms(g,0);
    ms(l,0);
    ms(r,0);
    rep(i,1,n){
      cin>>a[i];
    }
    if(a[1]>a[2])l[1]=1;
    int p=1,q=2;
    rep(i,2,n){//i,i+1
      q=i;
      if(a[p]<a[q]){
        l[q]=i-1;
        r[p]=i-2;
        p=q;
      }
      if(a[p]==n){
        q=i-1;
        break;
      }
    }
    rep(i,1,n){
      if(r[i]==0)r[i]=-1;
    }
    rep(i,1,qq){
      cin>>x>>y;
      if(x==p){
        if(y<q)cout<<0<<endl;
        else cout<<y-q+1<<endl;
        continue;
      }
      if(y>=r[x])cout<<r[x]-l[x]+1<<endl;
      else if(y<l[x])cout<<0<<endl;
      else cout<<y-l[x]+1<<endl;
    }
  }
  return 0;
}
```

---

## 作者：Lib_Zhang (赞：0)

#### 题意简述:
有 $n$ 个角斗士站在一排 , 士兵的力量值使用一个排列 , 每次对排头前 $2$ 名士兵的力量值进行对比 , 大的人继续站在排头(赢) , 小的人去末尾(输) .

每次给定一个询问 , 给出 $p , k$，表示第 $p$ 位士兵在前 $k$场战斗中赢的次数.

#### 分析:

显然的通过读题(模拟)，可以发现在经过最多 $n$ 轮战斗，战斗值最高的士兵会一直站在排头，剩下的士兵会按原顺序排列 (即所有决斗都是排头获胜).

然后就可以暴力模拟 , 通过双端队列和动态数组存储.

### 代码:


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<set>
#include<stack>
#include<map>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<utility>
#define mid (l+r>>1)
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pai;
const double eps = 1e-10;
const int base = 13331;
const long long mod = 998242353;
long long maxn = -2147483647-1,minn = 0x7f7f7f7f;
ll a[100005],t,n,m,op,k,player1,player2,ans;
vector<ll> v[100005];
int main(){
	//freopen("filename.in","r",stdin);
	//freopen("filename.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		deque<ll> q;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			q.push_back(i);
			v[i].clear();
		}
		for(int i=1;i<=n;++i){   //模拟 
			player1 = q.front(),q.pop_front();
			player2 = q.front(),q.pop_front();
			if(a[player1]<a[player2]){
				swap(player1,player2);
			}
			q.push_front(player1),q.push_back(player2);
			v[player1].push_back(i);
		}
		for(int i=1;i<=m;++i){
			ans = 0;
			cin>>op>>k;
			ans = upper_bound(v[op].begin(),v[op].end(),k)-v[op].begin();
			if(a[op]==n){
				ans+=max((ll)0,k-n);
			}
			cout<<ans<<endl;
		}
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}


```


#### 总结:
有一定细节 , 考场上罚了5发 , 关键是找出最大值在经过 $n$ 轮后永远在排头.

---

## 作者：y_kx_b (赞：0)

## 大家好我非常不喜欢DS所以我没用DS做这道题

思路：二分找到第一个大于本士兵战力的第一个士兵，然后模拟即可。

以下令 $q$ 为被查询士兵的位置，$k$ 为战斗轮数。

$%另外还有几个特殊情况。$

1. 如果士兵是体力最大的那个（表现为他的战力等于总人数 $n$），那么他战无不胜，只要他一上场就开始连胜。所以胜利轮数为 $\max(k-q+2-[q=1],0)$。其中 $q-1$ 为他前面的人数，$q-2+[q=1]$ 为他刚好未加入战斗时的轮数。答案对 $0$ 取 $\max$ 是因为有可能他没上场时前面的答案为负数；减去 $[q=1]$ 是因为他站第一个位置和站第二个位置都$%一样参加第一场战斗，但前者多加了一个 \$1\$，要减掉。$是直接从第一轮起略杀全场，胜利轮数都为 $k$。

否则，二分出第一个大于本士兵战力的士兵的下标，记为 $r$。

2. 如果士兵站第一个位置，那他将会击败 $(1,r)$ 内的所有士兵。也就是说，答案是 $\min(k,r-2)$。

3. 如果 $r<p$，那么这意味着在这个士兵上场之前，已经有更nb的人霸占了这个场地，那么，他不可能赢，也就是直接输出 $0$。

4. 否则，$r>q$，他击败 $\min (\max(k-q+2,0),r-q)$ 人。$r-q$ 是因为他最多赢这么多人；$k-q+2$ 是他最多参加了这么多轮。

最后附上代码，注释是考场上写的。
```cpp
int n,m;
int a[N];
int maxa[N];//[1,i]内最大值。
bool major(){
	n=read();int qwq=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)maxa[i]=max(a[i],maxa[i-1]);
	// for(int i=1;i<=n;i++)disp(1,maxa[i]);
	while(qwq--){
		int q=read(),k=read();
		if(a[q]==n){
			printf("%d\n",max(0,k-q+2-(q==1)));
			//站在第一个位置和第二个位置是一样的
			continue;//enter next query
		}
		//binary_search.
		int l=0,r=n+1;
		while(l+1<r){
			itn mid=l+r>>1;
			if(maxa[mid]>a[q])r=mid;
			else l=mid;
		}
		//r为第一个大于该点a值的下标；r!=q.
		if(r<q){puts("0");continue;}
		if(q==1){
			//r代表他最长能活多久。
			printf("%d\n",min(k,r-2));//第一个人只能打败(1,r)区间内的人
			continue;
		}
		printf("%d\n",min(r-q,max(k-q+2,0)));
		// disp(2,114,r);
	}
	return 114514;
}
```

---

## 作者：cst_123 (赞：0)

- [传送门](https://www.luogu.com.cn/problem/CF1719C)

### 题意

$T$ 组数据，有 $n$ 个实力各不相同的人打擂台，实力分别是 $1$ 到 $n$。这些人会按照读入的顺序排成一个队列进行比赛，每次最前面的两人比较实力，实力高的到第一个，实力低的到最后。

再给你 $q$ 个询问，每次问你 $a_i$ 经过 $k$ 轮擂台后，赢了多少场。

### 思路

我们可以定义两个数组，$l$ 数组记 $a_i$ 在第几轮开始在第一位，另一个 $r$ 数组记 $a_i$ 又在第几轮结束到了最后。

之后再定义一个数组 $Max$，表示每轮都是谁在第一位。

最后判断 $a_i$ 胜利的时间是否比 $k$ 小或相等的，并且 $a_i$ 是否胜过。

若是，答案就是 $k-l_{a_i}+1$。还要注意的是，如果 $k$ 大于了 $a_i$ 最后结束胜利的时间，那需输出 $r_{a_i}-l_{a_i}+1$，可以与之前的进行比较，取最小值。

若不是，输出 $0$。

### 代码

```cpp
T=read();
while(T--){
	n=read();
	q=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		l[i]=0;
      	r[i]=0;
	}
	Max[1]=a[1];//首先a[1]在最前
	for(int i=2;i<=n;i++)
		Max[i]=max(Max[i-1],a[i]);//记录每一轮都是谁胜
	for(int i=2;i<=n;i++){
		if(Max[i]!=Max[i-1]){//若Max数组变了，就把记录该数的开始时间，并把上一个数的结尾记录
			l[Max[i]]=i;
			r[Max[i-1]]=i-1;
		}
	}
	r[Max[n]]=1e10;//最后Max的最后一个数必是胜利者，将其也存入r数组，这里我将其记录为一个极大值
	l[a[1]]=2;//存入开头
	for(int i=1;i<=q;i++){
		x=read();k=read();
      	k++;//因为位置和轮数差1，所以要加
		if(l[a[x]]<=k&&r[a[x]]!=0)
			cout<<min(k-l[a[x]]+1,r[a[x]]-l[a[x]]+1)<<endl;
		else cout<<0<<endl;
	}
}
```

---

## 作者：qwq___qaq (赞：0)

分享一种线性做法（CF 上的标签我一个也没用到）：

对于 $a_x=n$，当和他比较时，是它就会多胜利一次，我们可以分三种情况：$y<x-1$，此时是不会比较到 $x$ 的；否则在比较不到 $x$ 时，前面的数会比较 $\max(x-2,0)$，那么答案就是 $y-\max(x-2,0)$。

否则，记录 $num_x$ 表示 $[x,n]$ 出现的最靠左的位置，那么此时如果 $\min(num_{a_x+1})<x$（$x$ 被弹出）或 $y<x-1$（还没到关于 $x$ 的操作）答案都是 $0$；否则如果弹出 $x$，就需要 $num_{a_x+1}-2$ 次比较，但是最多比较次数为 $y$，所以上界就是 $\min(num_{a_x+1}-2,y)$，下界是比较到 $x$，此时仍需要 $\max(0,x-2)$ 次操作，所以答案就是 $\min(num_{a_x+1}-2,y)-max(0,x-2)$。

时间复杂度 $O(n+q)$。

---

