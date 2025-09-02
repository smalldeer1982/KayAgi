# Skills

## 题目描述

Lesha plays the recently published new version of the legendary game hacknet. In this version character skill mechanism was introduced. Now, each player character has exactly $ n $ skills. Each skill is represented by a non-negative integer $ a_{i} $ — the current skill level. All skills have the same maximum level $ A $ .

Along with the skills, global ranking of all players was added. Players are ranked according to the so-called Force. The Force of a player is the sum of the following values:

- The number of skills that a character has perfected (i.e., such that $ a_{i}=A $ ), multiplied by coefficient $ c_{f} $ .
- The minimum skill level among all skills ( $ min\ a_{i} $ ), multiplied by coefficient $ c_{m} $ .

Now Lesha has $ m $ hacknetian currency units, which he is willing to spend. Each currency unit can increase the current level of any skill by $ 1 $ (if it's not equal to $ A $ yet). Help him spend his money in order to achieve the maximum possible value of the Force.

## 说明/提示

In the first test the optimal strategy is to increase the second skill to its maximum, and increase the two others by 1.

In the second test one should increase all skills to maximum.

## 样例 #1

### 输入

```
3 5 10 1 5
1 3 1
```

### 输出

```
12
2 5 2 
```

## 样例 #2

### 输入

```
3 5 10 1 339
1 3 1
```

### 输出

```
35
5 5 5 
```

# 题解

## 作者：傅思维666 (赞：7)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11799013.html)

~~2019.11.5模拟赛T2 15分场~~

#### 题意：

学技能，一共有$n$个技能，每个技能的初始等级是$a[i]$，满级是$A$级，你一共可以为你的技能提升$m$级，提升完毕之后的战力为：
$$
force=x\times c_m+y\times c_f
$$
($x$为提升完毕之后这些技能中最小的等级，$y$为满级技能数量)

现在问一共能获得的最大战力是多少。

#### 解析：

一开始看到这道题觉得是贪心。怎么想都没想到贪心策略。以为是自己太笨了~~（事实上的确是）~~

后来搞了一个明知必假的贪心交了上去，骗到了15分。感谢出题人@littleseven 

因为没什么意义，我就不放最开始的代码了。

正解：**二分+贪心枚举**

让我们分析一下：

这个战力只和两个事情有关：满级技能有多少个，级别最低的技能级别有多低。

那么对于我们手中的$m$个技能点，我们可以选择先给一些技能加满，也可以选择尽可能地提升所有技能的最低技能级别。然后我们自然而然地想到，那到底是先给技能点满更优呢？还是先提升技能整体素质更优呢？

然后我们就死在这个思路里了。

为什么不能这么想呢？因为这个思路的两个关键字性质并不一样。什么意思呢？你看，这个战力的计算式，与$c_f$有关的是满级技能的**数量**，而与$c_m$有关的则是最低**等级**，我们要满足其中一个条件，必然要牺牲第二个条件，就导致了没有办法确定到底怎么分配技能点才能得出最优解。

怎么办呢？

都试一下子不就好了？

是的，既然我们的两个条件是“此消彼长”的，那么就“一定一动”，枚举一个条件，然后在这个条件下再枚举第二个条件，持续更新答案即可。

也就是说：先把这个等级从小到大排好序，在技能点够用的情况下，从后向前开始枚举点满的技能个数，然后在剩下的技能中用剩下的技能点尽可能地提升最低等级，得出答案。

一算时间复杂度，是$O(n^2)$的，超时了。

于是我们想到了**“枚举伴侣”——二分**。

用二分来优化枚举，二分的就是最低等级，一个个判合不合法，然后更新答案即可。

至于怎么判断这个合不合法，可以跑一个前缀和。至于输出最后的方案，可以在更新答案处做一个标记，然后按这个标记分配技能点即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1e5+10;
int high,cf,cm,n,m;
int level[maxn],b[maxn],s[maxn],ans,tmp1,tmp2;
bool cmp(int x,int y)
{
    return level[x]<level[y];
}
int check(int x,int rr)
{
    int l,r,mid;
    l=0;r=rr;
    while(l<r)
    {
        mid=(l+r+1)>>1;
        if(level[b[mid]]<x)
            l=mid;
        else 
            r=mid-1;
    }
    return l;
}
signed main()
{
    scanf("%lld%lld%lld%lld%lld",&n,&high,&cf,&cm,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&level[i]);
        b[i]=i;
    }
    sort(b+1,b+1+n,cmp);
    for(int i=1;i<=n;i++)
        s[i]=s[i-1]+level[b[i]];
    m+=s[n];
    ans=-1;
    int i;
    for(i=1;i<=n+1;i++)
    {
        if(high*(n-i+1)+s[i-1]>m)
            continue;
        if(i==1)
            ans=cf*n+cm*high,tmp1=1;
        if(i==1)
            break;
        int l=level[b[1]],r=high;
        while(l<r)
        {
            int mid=(l+r+1)>>1;
            int t=check(mid,i-1);
            if(high*(n+1-i)+mid*t+s[i-1]-s[t]<=m)
                l=mid;
            else 
                r=mid-1;
        }
        if(ans<cf*(n+1-i)+l*cm)
            ans=cf*(n+1-i)+l*cm,tmp1=i,tmp2=l;
    }
    printf("%lld\n",ans);
    for(i=1;i<tmp1;i++)
        if(level[b[i]]<tmp2)
            level[b[i]]=tmp2;
    for(i=tmp1;i<=n;i++)
        level[b[i]]=high;
    for(i=1;i<=n;i++)
        printf("%lld ",level[i]);
    return 0;
}
```



---

## 作者：LEE114514 (赞：3)

## 题目大意

给定 $n,A,cf,cm,m$ 和一个长度为 $n$ 的自然数序列 $a$ ，你有 $m$ 次操作的机会，每次可以将序列一个小于 $A$ 的数字加一，最大化 $(\sum_{i=1}^{n}{[a_i=A]} \times cf)+(\min_{i=1}^{n}{a_i}) \times cm$。

## 思路

我们发现，我们要将有限的 $m$ 次操作分配给两个**没有关联**的变量，但这两个变量都可以对答案做出贡献。

首先我们想到二分，但同时二分这两个变量或者分别二分都是不可取的。前者的原因是无法保证单调性，后者是因为这两个变量“此消彼长”，一个变大一个会变小，**不可分离**。

因此我们大胆猜测是枚举一个，二分一个。在此，我选择枚举 $a_i=A$ 的个数，这时我们需要求最小分数的最大值，这是一个典型的二分答案解决的问题。

在这里首先有一个很显然的贪心，那就是优先把操作给最大的和最小的，因为我们只在意这两者的数量。

注意有一个其他题解没有强调的细节，**一个元素可能既是最大的几个元素（即你想把它加满），又是最小的几个元素（即你想把它加到最低线），注意不要在同一个元素上浪费这两种用途的钱。**

## Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,A,cf,cm,m;
const int maxn=1e5+5;
struct node{
	int val,pos;
}a[maxn];
int b[maxn];
int s[maxn];
int s2[maxn];
int L,R,MID;
int res,maxpos;
bool check(int i,int x,int k){//不减 i 错因：把已经变满的数重新填充（浪费钱）
	int pos=lower_bound(b+1,b+n-i+1,x)-b-1;
	return pos*x-s2[pos]<=k;
}
signed main(){
	cin>>n>>A>>cf>>cm>>m;
	for(int i=1;i<=n;++i) cin>>a[i].val,a[i].pos=i,b[i]=a[i].val;
	sort(a+1,a+n+1,[](node a,node b){return a.val>b.val;});
	for(int i=1;i<=n;++i) s[i]=s[i-1]+(A-a[i].val);//把i个数补满的代价
	sort(b+1,b+n+1);
	for(int i=1;i<=n;++i) s2[i]=s2[i-1]+b[i];//最小的i个数的和
	for(int i=0;i<=n;++i){
		if(m<s[i]) break;
		L=0,R=A;
		while(L<=R){
			MID=(L+R)>>1;
			if(check(i,MID,m-s[i])) L=MID+1;
			else R=MID-1;
		}
		int tmp=i*cf+R*cm;
		if(tmp>res){
			res=tmp;
			maxpos=i;
		}
	}
	cout<<res<<'\n';
	L=0,R=A;
	while(L<=R){
		MID=(L+R)>>1;
		if(check(maxpos,MID,m-s[maxpos])) L=MID+1;
		else R=MID-1;
	}
	for(int i=1;i<=maxpos;++i) a[i].val=A;
	for(int i=1;i<=n;++i) a[i].val=max(a[i].val,R);
	sort(a+1,a+n+1,[](node x,node y){return x.pos<y.pos;});
	for(int i=1;i<=n;++i) cout<<a[i].val<<' ';
}
```

---

## 作者：shao0320 (赞：1)

#### CF1083B The Fair Nut and Strings

二分套二分大套娃题。

首先一个显然的思路就是枚举有多少数可以加到$A$，之后再处理一下剩下的部分。

假设我们枚举到有$i$个数加到$A$，那么一定是原序列中最大的$i$个数，因为其它数加到$A$不如我们直接把大的数加到$A$花费小。

然后考虑如何确定下界，那显然是下界越大越好，假设令$i$个数到$A$之后我们还有$x$次可加，那我们一定是选择最后一个使得花费小于等于$x$的数。

那么这个东西可以二分。

问题是二分完了如何验证，我们可以把原数组排序，排序后需要加的显然就是前边的一段，设当前二分到的下界是$mid$，而小于$mid$的最后一个位置是$pos$，那花费就是$mid*pos-pre_{pos}$，$pre_{pos}$是排好序后数组的前缀和。

然后这个$pos$也是可以二分的，往死里二分即可（也可以lower_bound）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mp make_pair
#define N 200005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,A,cf,cm,m,a[N],b[N],ll[N],rr[N],cnt,pre[N],suf[N],ans,anspos,anspos2;
pair<int,int>B[N];
signed main()
{
	n=read();A=read();cf=read();cm=read();m=read();
	int cntt=0,minn=1e16;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();minn=min(minn,a[i]);
		if(a[i]==A)cntt++;
		B[i]=mp(a[i],i);
	}
	ans=minn*cm+cntt*cf; 
	sort(B+1,B+1+n);
	for(int i=1;i<=n;i++)b[i]=B[i].first;
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]+b[i];
	for(int i=n;i>=1;i--)suf[i]=suf[i+1]+(A-b[i]);
	reverse(suf+1,suf+1+n);
	for(int i=0;i<=n;i++)
	{
		int tmp=m;
		tmp-=suf[i];
		if(tmp<0)break;
		int l=b[1],r=A,mid,Pos,Ans=0;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(mid>=b[n])Pos=n;
			else Pos=upper_bound(b+1,b+1+(n-i),mid)-b-1;
			if(mid*Pos-pre[Pos]<=tmp)l=mid+1,Ans=mid;
			else r=mid-1;
		}
		if(ans<i*cf+Ans*cm)
		{
			//cout<<i<<" "<<cf<<" "<<l<<" "<<cm<<endl;
			ans=i*cf+Ans*cm;
			anspos=i;
			anspos2=Ans;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(B[i].first<=anspos2)a[B[i].second]=anspos2;
		if(i>=n-anspos+1)a[B[i].second]=A;
	}
	//printf("%lld\n",ans);
	//if(cf==807)cout<<anspos2<<endl;
	cntt=0;minn=1e16;
	for(int i=1;i<=n;i++)
	{
		minn=min(minn,a[i]);
		if(a[i]==A)cntt++;
	}
	printf("%lld\n",cntt*cf+minn*cm);
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);
	return 0;
}

```



---

## 作者：ZMQ_Ink6556 (赞：0)

## 题解：CF613B Skills

### 解题思路

明显**二分**。发现**排序**后具有**单调性**。枚举能填满多少个位置然后二分剩下的能填到什么高度或枚举能填到多少高度然后二分剩下的可以填满多少。明显前者更好写，因为后者需要两个二分。

二分前预处理前缀和 $s_i = s_{i - 1} + a_i$。

想计算将 $(l , r)(a_l , a_{l + 1} , \dots , a_r \le p)$ 补到 $p$ 所需的货币为 $p \times (r - l + 1) - (s_r - s_{l - 1})$。

因为 $m \le 10^{15}$，所以显然需要 **long long**。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , p , cf , cm , m , qzh[100005] , nxt[100005] , pre[100005] , l , r , mid , ans = -1 , anss , anst , ansss , anssd , minr = 1000000009;
struct p_
{
	int a;
	int tag;
}a[100005];
inline bool cmp(p_ l , p_ r)
{
	return l.a < r.a;
}
inline bool cmp2(p_ l , p_ r)
{
	return l.tag < r.tag;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> p >> cf >> cm >> m;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i].a;
		a[i].tag = i;
	}
	sort(a + 1 , a + n + 1 , cmp);
	for(int i = 1 ; i <= n ; i++)
	{
		qzh[i] = qzh[i - 1] + a[i].a;
	}
	a[n + 1].a = p;
	for(int i = 0 ; i <= n ; i++)
	{
		m -= (n - i) * p - qzh[n] + qzh[i];
		if(m < 0)
		{
			m += (n - i) * p - qzh[n] + qzh[i];
			continue;
		}
		l = 1;
		r = i;
		anst = 1;
		while(l <= r)
		{
			mid = (l + r) / 2;
			if(a[mid].a * mid - qzh[mid] <= m)
			{
				anst = mid;
				l = mid + 1;
			}
			else
			{
				r = mid - 1;
			}
		}
		if(anst == i)
		{
			anss = min(a[anst].a + (m - (a[anst].a * anst - qzh[anst])) / anst , p) * cm + (n - i) * cf;
			if(anss > ans)
			{
				ans = anss;
				ansss = i;
				anssd = min(a[anst].a + (m - (a[anst].a * anst - qzh[anst])) / anst , p);
			}
		}
		else
		{
			anss = min(min(a[anst].a + (m - (a[anst].a * anst - qzh[anst])) / anst , p) , a[anst + 1].a) * cm + (n - i) * cf;
			if(anss > ans)
			{
				ans = anss;
				ansss = i;
				anssd = min(min(a[anst].a + (m - (a[anst].a * anst - qzh[anst])) / anst , p) , a[anst + 1].a);
			}
		}
		m += (n - i) * p - qzh[n] + qzh[i];
		if(i == 0)
		{
			break;
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		if(i <= ansss)
		{
			a[i].a = max(a[i].a , anssd); 
		}
		else
		{
			a[i].a = p;
		}
	}
	sort(a + 1 , a + n + 1 , cmp2);
	for(int i = 1 ; i <= n ; i++)
	{
		minr = min(minr , a[i].a);
	}
	ans = minr * cm;
	for(int i = 1 ; i <= n ; i++)
	{
		if(a[i].a == p)
		{
			ans += cf;
		}
	}
	cout << ans << '\n';
	for(int i = 1 ; i <= n ; i++)
	{
		cout << a[i].a << ' ';
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

这有蓝？

显然的事情是升满是从大往小考虑，提高最低的等级是从小往大考虑，两者互不影响，所以先把所有技能按照等级排序，于是考虑枚举 $i$ 表示把等级前 $i$ 大的升满，再二分一个 $mid$ 表示剩下的钱币能把最低的等级提高到多少，check 的时候考虑里面再套一个二分求解需要将哪些技能提高到 $mid$，剩下的就是一个前缀和预处理了。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5+114;
const int inf = 1e18+114;
int n,A,m,a[maxn];
pair<int,int> b[maxn];
int p[maxn];
int cm,cf;
int pre[maxn];
bool check(int x,int w,int cst){
    //[1,x] 升到 w 花费是否不超过 cst
    return w*x-pre[x]<=cst;
}
int cha,chb;
int solve(int x){
    if(A*x-(pre[n]-pre[n-x])>m) return -inf;
    int cst=m-(A*x-(pre[n]-pre[n-x]));
    int l=0,r=A+1;
    while(l+1<r){
        int mid=(l+r)>>1;
        int L=1,R=n-x+1;
        while(L+1<R){
            int Mid=(L+R)>>1;
            if(a[Mid]<=mid) L=Mid;
            else R=Mid;
        }
        if(check(L,mid,cst)) l=mid;
        else r=mid;
    }
    if(x==n) l=A;
    cha=x,chb=l;
    return x*cf+l*cm;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>A>>cf>>cm>>m;
    for(int i=1;i<=n;i++) cin>>a[i],b[i].first=a[i],b[i].second=i;
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++) p[b[i].second]=i;
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
    int ans=0,P=1;
    for(int i=0;i<=n;i++){
        int res=solve(i);
        if(res>=ans){
            ans=res;
            P=i;
        }
    }
    cout<<ans<<'\n';
    solve(P);
    for(int i=1;i<=n;i++){
        if(n-p[i]+1<=cha) cout<<A<<' ';
        else cout<<max(chb,a[p[i]])<<' ';
    }
    return 0;
}
```

---

## 作者：__LZH__ (赞：0)

# CF613B Skills

## 题意

每个角色有 $n$ 项技能。每项技能由一个非负整数 $a_i$ 表示当前技能等级。所有技能的最大等级相同，为 $A$。

玩家的力量值为以下值的总和：

- 角色所精通的技能数量 $u \times c_f$。

- 所有技能中的最低技能等级 $v \times c_m$。

现在小 $L$ 拥有 $m$ 个货币，帮助他花费这些钱，以达到可能的最大力量值。

## 思路

首先，两个影响力量值的东西都无法区分优先级，但可以发现第一项是以技能数量为单位，于是可以枚举使用第一项的次数，然后又能发现此处有单调性，即最小值越大所需金币越大，本处提供三种思路：
- 1\. 二分需要变化的最小值，不过 check 需要用二分，因此时间复杂度为 $O(n \log V \log n)$ 级（$V$ 为值域）。

- 2\. 二分需变化人数，此时 check 就可以 $O(1)$ 判断，时间复杂度为 $O(n \log n)$。

- 3\. 双指针维护需变化人数，也是本篇最难的思路，时间复杂度 $O(n)$。

~~太菜了，只会第一种。~~

## 代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 10;

struct node{
  int x, id;
}a[N];

int n, A, p, q, m, sum[N], pre[N], b[N];

bool cmp(node a, node b){
  return a.x > b.x;
}

bool check(int x, int i){
  int s = i * A - sum[i];
  int k = lower_bound(b + 1, b + (n - i) + 1, x) - b - 1;
  return m >= s + k * x - pre[k];
}

signed main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> A >> p >> q >> m;
  for(int i = 1; i <= n; i++){
    cin >> a[i].x; b[i] = a[i].x;
     a[i].id = i;
  }
  sort(b + 1, b + 1 + n);
  sort(a + 1, a + 1 + n, cmp);
  for(int i = 1; i <= n; i++){
    sum[i] = sum[i - 1] + a[i].x;
  }
  for(int i = 1; i <= n; i++){
    pre[i] = pre[i - 1] + b[i];
  }
  int ans = -1e9, ansi = 0, ansk = 0;
  for(int i = 0; i <= n; i++){
    int s = i * A - sum[i];
    if(s > m){
      continue;
    }
    int l = a[n].x, r = A, an = a[n].x;
    while(l <= r){
      int mid = (l + r) >> 1;
      if(check(mid, i)){
        l = mid + 1, an = mid;
      }else{
        r = mid - 1;
      }
    }
    if(an != -1){
      int op = i * p + an * q;
      if(op > ans){
        ans = op, ansi = i, ansk = an;
      }
    }
  }
  cout << ans << '\n';
  int s = 0;
  for(int i = 1; i <= ansi && s < m; i++){
    s += (A - a[i].x);
    if(s > m){
      break;
    }
    a[i].x = A;
  }
  for(int i = n; i > ansi && s < m && ansk >= a[i].x; i--){
    s += ansk - a[i].x;
    if(s > m){
      break;
    }
    a[i].x = ansk;
  }
  for(int i = 1; i <= n; i++){
    b[a[i].id] = a[i].x;
  }
  for(int i = 1; i <= n; i++){
    cout << b[i] << ' ';
  }
  return 0;
}
```

---

## 作者：cosf (赞：0)

## [CF613B](https://www.luogu.com.cn/problem/CF613B)

这里提供一个单 $\log$ 算法。

即然 Codeforces 上这题有一个 `two pointers`，那就尊重一下它吧。

首先给 $a$ 从小到大排个序。然后我们维护两个指针 $l, r$，表示 $a_1, \dots, a_l$ 全部加到一个 $< a_{l + 1}(a_{n + 1} = +\infty)$ 的数作为 $\min$，并且 $a_r, \dots, a_n$ 全部加到 $A$。

可以发现，$l$ 越大，$a_1, \dots, a_l$ 加到同一个数的花费越大。同理，$r$ 越小，$a_r, \dots, a_n$ 全部加到 $A$ 的花费也越大。它们都是单调的，因此可以用双指针，$l, r$ 同时从极大值转向极小。

令 $sum_i = \sum_{j \le i}a_i$。则对于一对 $l, r$，它们的花费 $\le m$ 等价于 $(n - r + 1)A - (sum_{n} - sum_{r - 1}) + l\times a_l - sum_l \le m$。

这个难看的式子可以拆成两部分。

第一部分是 $(n - r + 1)A - (sum_{n} - sum_{r - 1})$，表示将 $a_r$ 到 $a_n$ 全加到 $A$。

第二部分是 $l\times a_l - sum_l$，表示将 $a_1$ 到 $a_l$ 全加到 $a_l$。

当然，最终的力量肯定不止这样。除了 $c_f(n - r + 1)$（即最后的加到 $A$）和 $c_m\times a_l$ 以外，可能还有多余的力量。而这些力量，可能可以让 $a_1$ 到 $a_l$ 全体再加上一个数，让整个序列的 $\min$，也就是 $a_l$，加上那个数。

当然，这里的“多余的力量”，就是前面那个难看的式子右边减左边。将得到的结果除以 $l$，就是可以增加的力量了。

综合起来，这个式子非常的乱（也是没过审的原因），为了不影响阅读，把它放到文末了。

接下来谈谈转移时的问题。

这和往常双指针略有不同的是，$l$ 可能会大于 $r$，而大于 $r$ 的所有 $a_i$ 的值，都从原来的值变成了 $A$。这对 $sum_l$ 是可能会有影响的。

由于每次转移 $r$ 只会让一个数变化，所以套一个树状数组即可。


至于还原 $a_i$，我们维护产生答案的 $l, r$ 以及 $a_l$，让 $a_1, \dots, a_{l - 1}$ 变成 $a_l$，$a_r, \dots a_n$ 变成 $A$，其他不变即可。


复杂度瓶颈位于树状数组，排序可以优化到 $O(n)$。总复杂度 $O(n\log n)$。

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100005
#define lowbit(x) ((x) & -(x))

using ll = long long;
using pli = pair<ll, int>;

pli val[MAXN];
ll t[MAXN];

int n;

ll a, cf, cm, m;

ll out[MAXN];

void add(int p, ll v)
{
    while (p <= n)
    {
        t[p] += v;
        p += lowbit(p);
    }
}

ll sum(int p)
{
    ll res = 0;
    while (p)
    {
        res += t[p];
        p -= lowbit(p);
    }
    return res;
}

int main()
{
    cin >> n >> a >> cf >> cm >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i].first;
        out[i] = val[i].first;
        val[i].second = i;
    }
    sort(val + 1, val + n + 1);
    for (int i = 1; i <= n; i++)
    {
        add(i, val[i].first);
    }
    int l = n, r = n;
    while (r && val[r].first == a)
    {
        r--;
    }
    ll res = (n - r) * cf;
    while (val[l].first * l > m + sum(l))
    {
        l--;
    }
    ll mo = min((m - l * val[l].first + sum(l)) / l, a - val[l].first) + val[l].first;
    res += cm * mo;
    int rl = l, rr = r + 1;
    for (; r; r--)
    {
        if (m < a - val[r].first)
        {
            break;
        }
        m -= (a - val[r].first);
        add(r, a - val[r].first);
        val[r].first = a;
        while (val[l].first * l > m + sum(l))
        {
            l--;
        }
        ll mm = min((m - l * val[l].first + sum(l)) / l, a - val[l].first) + val[l].first; // 公式不要搞错
        ll cr = (n - r + 1) * cf + cm * mm;
        if (cr >= res)
        {
            res = cr;
            rl = l, rr = r, mo = mm;
        }
    }
    cout << res << endl;
    for (int i = rr; i <= n; i++)
    {
        out[val[i].second] = a;
    }
    for (int i = 1; i <= rl; i++)
    {
        out[val[i].second] = mo;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << out[i] << ' ';
    }
    cout << endl;
    return 0;
}

```

## 附

前面提到的公式：

$$

\begin{aligned}
&cf(n - r + 1) & (\text{The power of As})
\\
&+ cm(a_l & (\text{The power of min})\\
&+ \min\{A - a_l, & (\text{The max addable value of }a_l)\\
&\bigg\lfloor\Big(m - \\
&((n - r + 1)A - sum_n + sum_{r - 1}) & (\text{The cost of }a_{r\dots n})\\
&-(l\times a_l - sum_l)\Big) & (\text{The cost of }a_{1\dots, a_l})\\
&\div l\bigg\rfloor\}) & (\text{Unused units are equally divided})
\end{aligned}
$$

建议自己再推一遍。


---

## 作者：1234567890sjx (赞：0)

二分套二分，新 `trick++`！

首先如果在给定的 $m$ 次机会下可以恰好让所有数都为 $A$，那么这是一种最优情况，特判掉。

然后将 $a$ 数组排序，考虑枚举让多少个数组中的数恰好为 $A$，贪心的从后面往前面变即可。

然后考虑计算让技能的最低等级值为 $k$，发现在 $k$ 满足条件的前提下越大越好。所以二分找到第一个满足条件的 $k$。问题在于如何判定。

容易发现，判定的时候，二分查找到下标最大且值比二分得出的最低等级值 $k$ 小的位置 $p$，维护一个前缀和，直接计算需要增加几个 $1$ 才能满足条件即可。

因为是二分套二分所以时间复杂度是 $O(n\log^2n)$。

鉴于和其他题解的思路不太一样所以放一下代码。[代码](https://www.luogu.com.cn/paste/58rccl7m)。


---

