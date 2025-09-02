# Dreamoon Likes Permutations

## 题目描述

一个长度为 $m$ 的数列被称为排列，当且仅当其中包含了 $1$ 到 $m$ 中所有整数恰好一次。$m$ 被称为这个排列的长度。

Dreamoon 得到了两个排列 $p_1, p_2$，长度分别为正整数 $l_1, l_2$。

现在 Dreamoon 要将这两个排列合并成一个长度为 $l_1 + l_2$ 的序列 $a$，其中开头的 $l_1$ 个数为排列 $p_1$，结尾的的 $l_2$ 个数为排列 $p_2$。

给出序列 $a$，你需要找到这两个排列 $p_1, p_2$。如果有多种可能的还原方式，你需要找到所有的答案。（注意，也有可能不存在可能的还原方式。）

## 说明/提示

在第一组数据中，两种可能的将 $a$ 分为两个排列的还原方式为 $\{1\} + \{4, 3, 2, 1\}$ 和 $\{1, 4, 3, 2\} + \{1\}$。

在第二组数据中，唯一一种可能的划分方式为：$\{ 2, 4, 1, 3\} + \{2, 1\}$。

在第三种数据中，不存在可能的还原方式。

## 样例 #1

### 输入

```
6
5
1 4 3 2 1
6
2 4 1 3 2 1
4
2 1 1 3
4
1 3 3 1
12
2 1 3 4 5 6 7 8 9 1 10 2
3
1 1 1```

### 输出

```
2
1 4
4 1
1
4 2
0
0
1
2 10
0```

# 题解

## 作者：Blunt_Feeling (赞：4)

## CF1330B Dreamoon Likes Permutations 题解
这道题目我们不妨这样想：

假设至少有一种划分方法，则划分出来的两个集合中，每个集合中的最大值即为这个集合的元素个数。顺着这个思路，我们可以先找出初始数列的最大值 $Max$，然后得出两种可能的划分方法：
- 前 $Max$ 个数分为一组，后 $n-Max$ 个数分为一组。
- 前 $n-Max$ 个数分为一组，后 $Max$ 个数分为一组。

我们开一个 _check()_ 函数检测上述两种划分方法是否可行，最后输出可行的方法即可。需要注意的是，当 $n$ 刚好是 $Max$ 的两倍时，只会有1中可能的方法。对于每组测试数据，最多只能有2种方法，所以在输出时不用开for循环，逐个判断就行了。

至于 _check()_ 函数怎么写，我想应该很简单。可以运用桶排的思想，把两个集合中的所有数分别放入两个桶中，再检查每个桶中有没有漏掉的数。推荐使用C++ _STL_ 中的 _map_ 来实现。你也可以用 _set_ 去重的办法判断，就是写起来没有 _map_ 好写。

思路应该还是比较清晰的，这是我的AC代码：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int maxn=200050;
int T,n,a[maxn];
bool check(int x,int y)
{
	map<int,int> mp1,mp2; //用map开两个桶
	For(i,1,x) mp1[a[i]]++;
    For(i,x+1,x+y) mp2[a[i]]++;
    For(i,1,x)
        if(mp1[i]!=1)
			return false;
    For(i,1,y)
        if(mp2[i]!=1)
			return false;
    return true;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		int Max=0;
		For(i,1,n)
			cin>>a[i],Max=max(a[i],Max);
		int cnt=0;
		bool f1=false,f2=false;
		if(check(Max,n-Max)) f1=true,cnt++;
		if(check(n-Max,Max)) f2=true,cnt++;
		if(f1||f2) //至少有一种划分方法
		{
			if(Max+Max==n) //n刚好是Max的两倍，只有一种方法
				cout<<1<<endl<<Max<<' '<<n-Max<<endl;
			else //有一种或两种方法，视cnt而定
			{
				cout<<cnt<<endl;
				if(f2) cout<<n-Max<<' '<<Max<<endl;
				if(f1) cout<<Max<<' '<<n-Max<<endl;
			}
		}
		else cout<<0<<endl;
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：4)

## 题目翻译

定义长度为 $m$ 置换为 $m$ 个数的序列，且这 $m$ 个数分别为 $1,2,3...m$

现在 $2$ 个置换组成了一个长度为 $n$ 的序列，求出这 $2$ 个置换对应的 $m$ ，如果有多组，则按第一个 $m$ 从小到大输出。

#### 输入格式

第一行一个整数 $T$ ，表示有多组数据。

对于每一组数据:

第一行一个整数 $n$ ，表示序列的长度。

第二行 $n$ 个整数，表示所给的序列。

#### 输出格式

对于每一组数据:

第一行一个整数 $k$ ，表示一共有 $k$ 组置换。

接下来 $k$ 行，每行两个整数 $l1,l2$，表示两个置换的长度。

## 题目分析

思路还是很简单的，我们去枚举两个置换的断点，再开两个桶，然后每个桶有一个 $cnt$，表示从标号 $1$ 开始共有多少连续的 $1$。也就是我们断点前/后的最长置换的长度。如果断点前/后的最长置换长度恰好到了我们的断点，就记录下答案。

对于每次枚举断点，对前面的桶打上标记，对后面的桶抹掉标记，并对各个的 $cnt$ 更新。

## Code:
~~~cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,cnt1,cnt2,len,ans[200001],a[200001],vis1[200001],vis2[200001];
int main()
{
	cin>>T;
	while(T--)
	{
		scanf("%d",&n);
		cnt1=cnt2=len=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			vis1[i]=vis2[i]=0;
		}
		for(int i=1;i<=n;i++)
			vis2[a[i]]++;
		while(vis2[cnt2+1]==1) cnt2++;
		for(int i=1;i<=n;i++)
		{
			vis1[a[i]]++;
			vis2[a[i]]--;
			if(vis1[a[i]]==2&&cnt1>=a[i]) cnt1=a[i]-1;
			if(vis2[a[i]]==0&&cnt2>=a[i]) cnt2=a[i]-1;
			while(vis1[cnt1+1]==1) cnt1++;
			while(vis2[cnt2+1]==1) cnt2++;
			if(cnt1==i&&cnt2==n-i)
				ans[++len]=i;
		}
		printf("%d\n",len);
		for(int i=1;i<=len;i++)
			printf("%d %d\n",ans[i],n-ans[i]);
	}
}
~~~

---

## 作者：Need_No_Name (赞：0)

# Solution For CF1330B

## 题意:

给定一个长度为 $n$ 的序列,将其拆成长度为 $n_1$ $n_2$ 的两个序列,使得两个序列为 $1-n_1$ , $1-n_2$ 的排列,求 $n_1$ , $n_2$

## 分析:

看到这道题,我第一思路是枚举断点,检查是否可行,然后输出即可.但我看了一眼数据范围,别说枚举后 ``sort`` 了,用 $O(n^2)$ 大概率都会炸.看来得找到一种更快捷高效的算法.仔细想一想,检查的部分不太可能进一步优化,那么断点的枚举得进一步优化.如何优化呢?我们容易想到一个序列中有最大值,那么在分解出的两个序列中一定有一个序列包含这个最大值.我们不妨设这个最大值为 $max$ , 那么这两个序列一定是从 $1$ 到 $max$ , 从 $max + 1$ 再到 $n$ 或者是从 $1$ 到 $n - max$ , 从 $n - max + 1$ 再到 $n$ 这两种情况，就简单多了

## 代码:

直接上代码

```cpp
# include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int T;
int n;
int a[N];
int a1[N];
int flag11;
int flag22;
int main()
{
	cin >> T;
	while(T--)
	{
		flag11 = 0;
		flag22 = 0;
		memset(a1, 0, sizeof(a1));
		int maxx = 0;
		cin >> n;
		for(int i = 1; i <= n; i++)
		{
			cin >> a[i];
			a1[i] = a[i];
			maxx = max(maxx, a[i]);
		}
		sort(a + 1, a + maxx + 1);
		sort(a + maxx + 1, a + n + 1);
		bool flag = false;
		for(int i = 2; i <= maxx; i++)
		{
			if(a[i] - a[i - 1] != 1)
			{
				flag = true;
				break;
			}
		}
		a[maxx] = 0; 
		for(int i = maxx + 1; i <= n; i++)
		{
			if(a[i] - a[i - 1] != 1)
			{
				flag = true;
				break;
			}
		}
		if(flag == false)
		{
			flag11 = 1;
		}
		sort(a1 + 1, a1 + (n - maxx + 1));
		sort(a1 + n - maxx + 1, a1 + n + 1);
		bool flag1 = false;
		for(int i = 1; i <= n- maxx; i++)
		{
			if(a1[i] - a1[i - 1] != 1)
			{
				flag1 = true;
				break;
			}
		}
		a1[n - maxx] = 0;
		for(int i = n - maxx + 1; i <= n; i++)
		{
			if(a1[i] - a1[i - 1] != 1)
			{
				flag1 = true;
				break;
			}
		}
		if(flag1 == false)
		{
			flag22 = 1;
		}
		if((flag11 + flag22) == 0)
		{
			puts("0");
			continue;
		}
		else if(maxx == n - maxx)
		{
			puts("1");
			cout << maxx << " " << n - maxx<< endl;
			continue;
		}
		else
		{
			cout << flag11 + flag22 << endl;
			if(flag11)
			{
				cout << maxx << " " << n - maxx << endl; 
			}
			if(flag22)
			{
				cout << n - maxx << " " << maxx << endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：王熙文 (赞：0)

这道题完全可以用暴力的方法过。

## 题意

给很多个序列，每次求出来有多少个切分点，使它前面的子序列是一个排列，后面的子序列也是一个排列。也要输出方案。

## 思路

想一下最朴素的算法：枚举分割点，判断左右两边是否为某个排列（比如枚举分割点为 $i$，左边看 $a_1\sim a_i$ 是否为 $i$ 的一个排列；右边看 $a_{i+1} \sim a_n$ 是否为 $n-i$ 的一个排列）。

**先考虑左面的序列如何确定是否为一个排列：**

首先，枚举到一个分割点的时候，用一个 `bool` 数组记录一下当前数是否出现过。如果没有出现过，就把这个数标为 $1$，否则直接 pass 掉，因为一个序列的某个数出现了两次，这个序列是不可能成为一个排列的。

接下来，我们求出来这个序列的和，当这个和为长度为当前位置的排列的和时，这个序列就一定为一种排列；否则也不是。

求这个和，可以用前缀和预处理出来，也可以每次枚举时就加上这个数（详见代码）。

**再考虑右面的序列如何确定是否为一个排列：**

同样，和左面的序列的判断方法一样：

首先，先判断后面这个序列的和是否为排列的和，不是的话先 pass 掉，否则就继续判断。

接着，和上面一样，暴力判断是否这个区间的每一个数都只出现了一次。如果都只出现了一次，那么这个序列肯定是一种排列。

## 代码

代码里，算出左面的序列直接用一个数加上了，没有用前缀和，但是求右面的序列，还是要用后缀和的。

我使用了 `bitset` 替代了思路中的 `bool` 数组，使用时都差不多，将数组中所有数赋 `0` 使用 `xxx.reset()` 即可。

还有一点需要注意的，就是求区间和需要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[200010];

long long hzh[200010]; // 后缀和数组

bitset<200010> vis,vis2;

int ans[200010];

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	int t,n;
	cin>>t;
	while(t--)
	{
		// 后缀和由于是赋值操作，所以多测也不用清空
		int k=0; // 方案数
		vis.reset(); // vis 数组多测清空
		cin>>n;
		for(int i=1; i<=n; ++i)
		{
			cin>>a[i];
		}
		hzh[n+1]=0; // n+1 要清空为 0
		for(int i=n; i>=1; --i) // 求后缀数组
		{
			hzh[i]=hzh[i+1]+a[i];
		}
		long long qzh=0; // 前缀和直接扫一遍即可
		for(int i=1; i<n; ++i) // 枚举切分点
		{
		    qzh+=a[i]; // 前缀和加上当前数
			if(vis[a[i]]) break; // 如果左面的区间之前有这个数，就不是一个排列
			vis[a[i]]=1; // 标记出现了这个数
			if(qzh==(1ll*(i+1)*i>>1) /* 左面的区间，判断当前区间之和是否为排列的区间和 */ && hzh[i+1]==(1ll*(n-i+1)*(n-i)>>1) /* 右面的区间，同为判断是否和相等 */ )
			{
				// 如果到目前都满足要求，现在就来看右面的区间是否有重复的数
				vis2.reset(); // vis2 为标记右面的区间出现过的数，每次要清空
				bool flag=1; // 是否满足要求
				int j=n; // 从最右端点开始枚举，实际上从左面枚举也行，是个人习惯
				while(j>i)
				{
					if(vis2[a[j]]) // 是否之前有这个数，如果有，就不是一个排列
					{
						flag=0;
						break;
					}
					vis2[a[j]]=1; // 标记这个数
					--j;
				}
				if(flag) // 如果满足要求，加入答案数组
				{
					ans[++k]=i;
				}
			}
		}
		cout<<k<<endl; // 输出方案数
		for(int i=1; i<=k; ++i)
		{
			cout<<ans[i]<<' '<<n-ans[i]<<endl; // 输出两个序列的长度
		}
	}
	return 0;
}
```

---

## 作者：QiFeng233 (赞：0)

## [B] Dreamoon Likes Premutations

考虑一下排列的性质：

- 排列内各元素互不相同，即长度 $l$ 的排列内不同的元素有 $l$ 个。
- 排列的和就是等差数列求和，$sum=\frac{l\times(l+1)}{2}$。
- 排列内最大的元素就是排列的长度。

我的做法用到了性质一、二，官方题解用到了性质三。

**我的做法**：

考虑枚举分界点，那么左右两边都是合法排列当且仅当同时满足性质一和性质二。容易证明当 $a_i$ 是正数时这样做一定正确。数据范围保证了这一点。性质一和性质二都可以 $O(n)$ 预处理，然后最后枚举分界点也是 $O(n)$的。

```
#include<bits/stdc++.h>
#define int long long
#define ll long long
using std::pair;
using std::make_pair;
namespace QiFeng233{
	int t,n,k;
	int a[200020],dif1[200020],dif2[200020],vis[200020];
	ll s[200020];
	pair<ll,ll> ans[200020];
	void solve(){
		scanf("%lld",&t);
		while(t--){
			scanf("%lld",&n);
			for(int i=0;i<=n+1;++i)a[i]=0,dif1[i]=0,dif2[i]=0,s[i]=0;
			k=0;
			for(int i=1;i<=n;++i)scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
			for(int i=0;i<=n;++i)vis[i]=0;
			for(int i=1;i<=n;++i){
				dif1[i]=dif1[i-1];
				if(!vis[a[i]])++dif1[i],vis[a[i]]=1;
			}
			for(int i=0;i<=n;++i)vis[i]=0;
			for(int i=n;i;--i){
				dif2[i]=dif2[i+1];
				if(!vis[a[i]])++dif2[i],vis[a[i]]=1;
			}
			for(int i=1;i<n;++i){
				ll s1=s[i],s2=s[n]-s[i],l1=i,l2=n-i;
				if(2*s1==l1*(l1+1)&&2*s2==l2*(l2+1)&&dif1[i]==l1&&dif2[i+1]==l2&&l1!=0&&l2!=0){
					ans[++k]=make_pair(l1,l2);
				}
			}
			printf("%lld\n",k);
			for(int i=1;i<=k;++i)printf("%lld %lld\n",ans[i].first,ans[i].second);
		}
	}
}
signed main(){
	QiFeng233::solve();
	return 0;
}
```

**官方题解**：

记 $a_i$ 中最大的数为 $ma$，那么根据性质三，最多可能划分为两个排列——$(ma,n-ma)$ 或者 $(n-ma,ma)$。我们只用 $O(n)$ 检查一下它们是否是合法的排列即可。

代码来自于官方题解。

```
#include<cstdio>
const int SIZE = 200000;
int p[SIZE];
int ans[SIZE][2];
int ans_cnt;
bool judge(int a[], int n){
    static int used[SIZE+1];
    for(int i = 1; i <= n; i++) used[i] = 0;
    for(int i = 0; i < n; i++) used[a[i]] = 1;
    for(int i = 1; i <= n; i++) {
        if(!used[i]) return 0;
    }
    return 1;
}
bool judge(int len1, int n){
    return judge(p, len1) && judge(p + len1, n - len1);
}
int main() {
    int t = 0;
    scanf("%d", &t);
    while(t--) {
        ans_cnt = 0;
        int n;
        scanf("%d", &n);
        int ma=0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &p[i]);
            if(ma < p[i]) ma = p[i];
        }
        if(judge(n - ma,n)) {
            ans[ans_cnt][0] = n - ma;
            ans[ans_cnt++][1] = ma;
        }
        if(ma * 2 != n && judge(ma,n)) {
            ans[ans_cnt][0] = ma;
            ans[ans_cnt++][1] = n - ma;
        }
        printf("%d\n", ans_cnt);
        for(int i = 0; i < ans_cnt; i++) {
            printf("%d %d\n", ans[i][0], ans[i][1]);
        }
    }
    return 0;
}
```

---

## 作者：dead_X (赞：0)

## 1 题意简述
给你 $n$ 个数，输出所有划分方案，使得划分后左右的两个序列都是从 $1$ 到 $k$ 的一种排列。
## 2 思路简述
这题其实比2A好想?

前后分别统计合法位置然后对比即可

一个排列是合法

稍稍有一点点复杂(指Wa了3发)
## 3 代码
```
# include <bits/stdc++.h>
const int N=200010,INF=0x3f3f3f3f;
int a[N],n,T;
bool pre[N],suf[N];
std::map <int,bool> Map;
int read()
{
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
int main(void){
	T=read();
	while(T--)
    {
		Map.clear();
		n=read();
		for(int i=1;i<=n;++i){
			a[i]=read();
			pre[i]=suf[i]=false;
		}
		int cnt=0,maxx=0;
		for(int i=1;i<=n;++i){
			if(!Map[a[i]]) Map[a[i]]=true,++cnt;
			maxx=std::max(maxx,a[i]);
			if(cnt==i&&maxx==i) pre[i]=true;
		}
		Map.clear();
		maxx=0,cnt=0;
		for(int i=n;i;--i){
			if(!Map[a[i]]) Map[a[i]]=true,++cnt;
			maxx=std::max(maxx,a[i]);
			if(cnt==n-i+1&&maxx==n-i+1) suf[i]=true;
        }
		int ans=0;
		for(int i=1;i<n;++i) if(pre[i]&&suf[i+1]) ++ans;
		printf("%d\n",ans);
		for(int i=1;i<n;++i) if(pre[i]&&suf[i+1]) printf("%d %d\n",i,n-i);
	}
 
	return 0;
}
```
## 4 总结
思路显然，写起来有一点点恶心

正常的2B(指我过不去)

---

