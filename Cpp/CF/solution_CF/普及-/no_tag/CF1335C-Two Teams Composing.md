# Two Teams Composing

## 题目描述

You have $ n $ students under your control and you have to compose exactly two teams consisting of some subset of your students. Each student had his own skill, the $ i $ -th student skill is denoted by an integer $ a_i $ (different students can have the same skills).

So, about the teams. Firstly, these two teams should have the same size. Two more constraints:

- The first team should consist of students with distinct skills (i.e. all skills in the first team are unique).
- The second team should consist of students with the same skills (i.e. all skills in the second team are equal).

Note that it is permissible that some student of the first team has the same skill as a student of the second team.

Consider some examples (skills are given):

- $ [1, 2, 3] $ , $ [4, 4] $ is not a good pair of teams because sizes should be the same;
- $ [1, 1, 2] $ , $ [3, 3, 3] $ is not a good pair of teams because the first team should not contain students with the same skills;
- $ [1, 2, 3] $ , $ [3, 4, 4] $ is not a good pair of teams because the second team should contain students with the same skills;
- $ [1, 2, 3] $ , $ [3, 3, 3] $ is a good pair of teams;
- $ [5] $ , $ [6] $ is a good pair of teams.

Your task is to find the maximum possible size $ x $ for which it is possible to compose a valid pair of teams, where each team size is $ x $ (skills in the first team needed to be unique, skills in the second team should be the same between them). A student cannot be part of more than one team.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, it is possible to construct two teams of size $ 3 $ : the first team is $ [1, 2, 4] $ and the second team is $ [4, 4, 4] $ . Note, that there are some other ways to construct two valid teams of size $ 3 $ .

## 样例 #1

### 输入

```
4
7
4 2 4 1 4 3 4
5
2 1 5 4 3
1
1
4
1 1 1 3```

### 输出

```
3
1
0
2```

# 题解

## 作者：lingfunny (赞：4)

## 题目翻译
有$n$个小朋友，第$i$个小朋友的技能值为$a_i$，现在请你把这$n$个小朋友分$2$组，这个分组必须满足以下条件：
- 两组小朋友必须人数相同
- 第一组小朋友的技能值必须不同
- 第二组小朋友的技能值必须相同

举个栗子：

- 当分组为$[1, 2, 3]$和$[4, 4]$时，这就是一个**不正确**的分组，因为第一组和第二组人数不同；
- 当分组为$[1, 2, 3]$和$[3, 3, 4]$时，这就是一个**不正确**的分组，因为第二组小朋友技能值不同；
- 当分组为$[1, 1, 2]$和$[3, 3, 3]$时，这就是一个**不正确**的分组，因为第一组小朋友的技能值相同。
- 当分组为$[1, 2, 3]$和$[3, 3, 3]$时，这就是一个**正确**的分组，因为第一组小朋友技能值不同，第二组小朋友技能值相同。
- 当分组为$[5]$和$[6]$时，这就是一个**正确**的分组。

你需要计算出，第一组小朋友最多能有多少个人。**有些小朋友可以不在分组里。**

**数据范围**：
$a_i\le n \le 2\times 10^5$
## 题目分析
划重点：**有些小朋友可以不在分组里。**

首先需要找到两个值：有多少种不同的技能值$x$，**相同的技能值的数量最大值**$y$。

粗体字可能比较难理解，举个栗子：

例如这$n$个小朋友技能值分别是```1 1 1 1 1 2 2 2 3 4 5```，那与$1$相同技能值的数量就是$5$，与$2$相同的技能值就是$3$。我们就只需要知道这个最大值，在这个栗子中，$y=5$。

那么，接下来一共有$3$种情况：
- $x<y$，这时候不同的比相同的少，就可以把相同的分为一组，然后把$y$个不同的之中选$x$个分到另一组（因为有些小朋友可以不给他分组），第一组有$x$个人。
- $x=y$，这时候比较特殊，也许你会想说$x$个分为一组，$y$个分为一组。但是我们的$x$是不同的技能值数量，是包括那个$y$的。就像在上面那个例子，$x=y=5$。但是并不是把$[1,1,1,1,1]$一组，$[1,2,3,4,5]$一组，因为这样就是无中生$1$了。所以只应该选择少$1$个，所以第一组应该有$x-1$个人。
- $x>y$，这时候相同的人数比不同的多，就可以把所有不同$y$个人的分为一组，再从选择$x$中选择$y$个人即可。

也许你又迷惑了，$x,y$怎么求呢？

注意数据范围：$a_i\le 2\times 10^5$，桶排有请~
## 示例代码
```cpp
#include <iostream>
using namespace std;
int t,n,x,kind,maxtong;				//x是一会要输入的tmp，kind就是上文说的y，maxtong就是上文说的x
const int maxn = 200005;
int tong[maxn];						//桶~
int main(){
	cin>>t;
	while(t--){
		kind=maxtong=0;						//有多组数据，要清零
		cin>>n;
		for(register int i=1;i<=n;++i){
			cin>>x;
			if(!tong[x]++)++kind;
			//可以改写为
			/*
        if(!tong[x])++kind;				//如果这个技能值没见过，就把y++
        tong[x]++;						//桶值++
        */
		}
		for(register int i=1;i<=n;++i)
		maxtong=max(maxtong,tong[i]);		//桶中找最值
		if(maxtong == kind)					//分析都有了
			cout<<(kind-1);
		else if(maxtong > kind)
			cout<<kind;
		else
			cout<<maxtong;
		for(int i=1;i<=n;++i)				//多组数据，要清零
		tong[i]=0;
		cout<<endl;							//十年cf一场空，不打换行见祖宗
	}
	return 0;
}
```

---

## 作者：andyli (赞：4)

题意：  

有 $n$ 个学生，每个学生有一个能力值 $a_i$，从中选一些学生，使得这些学生能恰好分为两组，满足：  
- 两组人数相同
- 第一组所有学生的能力不重复，第二组所有学生的能力相同。

求每组的人数的最大值。  

$1\leq n\leq 2\times 10^5, 1\leq a_i\leq n$。  

分析：  

统计每个能力出现的次数，找出出现次数最多的数，设其出现次数为 $a$，再统计除去这个数有多少个不同的数，设为 $b$，则每组人数可为 $\min\{a,b\}$。当 $a\geq 2$ 时，还可把出现次数最多的数分到第一组，答案为 $\min(a-1,b+1)$。  

时间复杂度 $\mathcal O(n)$。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
const int maxn = 200005, INF = -1u / 2;

int c[maxn], A[maxn];
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        for (int i = 1; i <= n; i++)
            c[i] = 0;
        for (int i = 1; i <= n; i++)
            io.read(A[i]), c[A[i]]++;
        int p = 0;
        for (int i = 1; i <= n; i++)
            if (c[i] > c[p])
                p = i;
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (c[i] && i != p)
                cnt++;
        writeln(max(min(cnt, c[p]), c[p] <= 1 ? -INF : min(c[p] - 1, cnt + 1)));
    }
    return 0;
}
```

---

## 作者：laboba (赞：2)

首先，我们要统计出两个数k和l，分别代表一共有多少种不同的数和出现最多的数出现了多少次。具体怎么统计，我是用了一个map（STL大法好），因为200000多个log不会爆，每个位置记录对应的数字出现了多少次（就类似于桶），然后k就是mp.size(),l是最大的元素。[如果你不会map](https://www.cnblogs.com/hailexuexi/archive/2012/04/10/2440209.html)。

接下来，答案就很显然了但是还是要分类讨论一下：

1. 当l-k>2 此时答案就是k
2. 当l-k<2 此时左边没有出现最多次的那个数答案一定不小于右边有出现最多次的那个数，所以答案为min(k-1,l)。

代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
const int N=210000;
int a[N],bt[N];
map<int,int>mp;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),mp[a[i]]++;
		int mx1=mp.size(),mx2=-1;//mx1即为k，mx2即为l
		for(int i=1;i<=mp.size();i++){
			mx2=max(mx2,mp[i]);
		}
		mx1--;//为了方便一点，不减也可以，只要将后面的改动一下即可。
		if(mx2-mx1>1)printf("%d\n",mx1+1);
		else printf("%d\n",min(mx1,mx2));
		mp.clear();//记得清空，为这个调了好一会。。。。。
	}
}
```
UPD 三分钟后:兴高采烈的拿给一位神仙同学看，被秒指出了笔误。。。

---

## 作者：oimaster (赞：1)

> 二分答案：![dk](https://cdn.luogu.com.cn/upload/pic/62228.png)![dk](https://cdn.luogu.com.cn/upload/pic/62228.png)![dk](https://cdn.luogu.com.cn/upload/pic/62228.png)为什么没人写我

> 别的题解的做法——桶：![xyx](https://cdn.luogu.com.cn/upload/pic/62230.png)

> OI-Master：我来肝一篇二分答案的题解！二分答案裸题！

首先，想要二分答案，我们就需要看看这个答案是否具有单调性。注意，后面扯了很长的感性理解，如果您能反应出来为什么具有单调性就请跳过下面两段。

- 我们很容易发现，当 $x$ 定在一个值时，可以得到两个好的团队，那么对于所有 $y<x$，团队大小为 $y$ 也可以得到两个好的团队。原因是，我们可以选出现在两个团队里的若干个人，他们放在一起也能满足题目的要求。

- 同时，当 $x$ 定在一个值时，不可以得到两个好的团队，那么对于所有 $y>x$，一定也无法得到好的团队。原因是如果 $y$ 为大小能得到好的团队，$x<y$ 所以 $x$ 也能得到好的团队。然而 $x$ 大小的团队不是好的团队，所以 $y$ 也不是。

接下来，我们知道答案具有单调性特征，应该研究如何写二分的检查函数。这时候，我们就会用到贪心的思想。

- 首先，找出人数最多的那个水平，看看是否大于等于 $mid$，如果小于的话就说明 $mid$ 太大。这里是贪心。

> 其实在这里，作者贪心的原方法是这样：我们尽量选同样分数人数大于 $mid$ 的分数，如果选不到我们就选等于 $mid$ 的分数，否则就返回 `false`。这样就可以让本分数尽量为第二队做贡献。不过简化了得到上面的结果。具体`check()` 后面有。

- 然后，我们把这个人数扣掉 $mid$，也就是说有 $mid$ 个这个人数的同学进队了。
- 最后，我们看看剩下的不同水平人数是否大于等于 $mid$，如果可以就说明第二队——水平不同的人数也够，那么说明可以。否则不可以。

扯差不多了，我们来看看代码。注意二分答案有很多不同的风格，个人写个人的，大家可以参考我的 `check()`。

```cpp
#include<iostream>
using namespace std;
int n;
int a[200010];
int b[200010];
int c[200010];
bool check(int mid){
	for(int i=1;i<=n;++i)
		c[i]=b[i];
	int jj=0;
	for(int i=1;i<=n;++i)
		if(b[i]>=mid&&b[i]>b[jj])
			jj=i;
	if(jj==0)
		return false;
	c[jj]-=mid;
	int tot=0;
	for(int i=1;i<=n;++i)
		if(c[i]>=1)
			++tot;
	if(tot>=mid)
		return true;
	return false;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n;++i)
		b[i]=0;
	for(int i=1;i<=n;++i)
		++b[a[i]];
	int l=0;
	int r=n;
	int mid;
	while(l+1<r){
		mid=(l+r)/2;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	cout<<l<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```

原版贪心：

```cpp
bool check(int mid){
	for(int i=1;i<=n;++i)
		c[i]=b[i];
	int jj=0;
	for(int i=1;i<=n;++i)
		if(c[i]>mid){
			jj=i;
			break;
		}
	if(jj==0){
		for(int i=1;i<=n;++i)
			if(c[i]==mid){
				jj=i;
				break;
			}
		if(jj==0)
			return false;
	}
	c[jj]-=mid;
	int tot=0;
	for(int i=1;i<=n;++i)
		if(c[i]>=1)
			++tot;
	if(tot>=mid)
		return true;
	return false;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1335C)

------------
# 题意：
在一个数组中挑些数分为两组，一组全不相同，一组全部相同。

------------

# 思路：
我们求出一共有多少种数字 $x$，并且求出这些数字中个数最多的一种是多少个，假设是 $y$ 个。除去这一种，还剩 $ x - 1$ 种数字。在 $x - 1$ 和 $y$ 中取个最小值。然后如果 $y$ 比 $x - 1$ 多 $2$ 的话，说明 $y$ 还可以分一个出去，那么最终答案再增加一个。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
const int INF=0x3f3f3f3f;
int T,n,a[N],b[N];
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
		memset(b,0,sizeof(b));
        int maxn=0,s=0;
        for(int i=0;i<n;i++){
            cin>>a[i];
            b[a[i]]++;
        }
        for(int i=1;i<=n;i++){
            maxn=max(b[i],maxn);
            if(b[i]){
				s++;
			}
        }
        s--;
        int ans=min(s,maxn);
        if(maxn-ans>=2){
			ans++;
		}
		cout<<ans<<endl;
    }
    return 0;
}
```
完结撒花~

---

## 作者：juicyyou (赞：0)

# CF1335C Two Teams Composing
## 题目大意:
本题一共 $t$ 组数据。对于每一组数据, 给定一个 $n$ 并且给定一个数列 $a_n$ , 你可以任选这个数列的任意一个子序列并将其分为元素个数相等的两组, 使得第一组中的任意两个数均不相等, 并且使得第二组中的所有数均相等。求第一组或第二组中元素个数的最大值。
## 解法:
这题直接模拟即可。首先统计一下每种数在数列中出现了几次, 然后对于每种数, 考虑两种情况:

+    把所有这种数都放在第二类里, 其他数各取一个放在第一类。但注意, 这两个的结果可能不同, 所以要取 $\min$。
+    把一个这种数放在第一类, 其他放在第二类里。但注意, 这两个的结果也可能不同, 所以也要取 $\min$。

然后把这所有情况取一个 $\max$ 就行了。

下面是我的Code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<cctype>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 2e5 + 5;
const ll maxm = 1e3 + 5;
template<class T>
inline T qread(T &IEE){
	register T x = 0, f = 1;
	register char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -f;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return IEE = x * f;
}
ll ans, cnt, n, b, c, t;
ll a[maxn], f[maxn];
int main(){
	cin >> t;
	while(t--){
		cin >> n;
		ans = cnt = 0;
		for(int i = 1;i <= n;i++){
			f[i] = 0;
		}
		for(int i = 1;i <= n;i++){
			qread(a[i]);
			if(!f[a[i]]) cnt++;
			f[a[i]]++;
		}
		for(int i = 1;i <= n;i++){
			if(!f[a[i]]) continue;
			ans = max(ans, min(cnt, f[a[i]] - 1));
			ans = max(ans, min(cnt - 1, f[a[i]]));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```
上述算法的时间复杂度即为 $O(\sum n)$, 可以通过此题。

---

## 作者：_jimmywang_ (赞：0)

还可以的题啦~~

要有一个好的分组的话，怎么办呢？

首先，~~组内人数不超过总人数~~

我们可以记录最多出现的那个数出现了几次，设为$mx$,共出现了$sum$个不同的数。

接下来$i$从$n/2$开始，向下循环查找，找到一个就输出并退出。

那么怎样才算找到了呢？

### $1.i<=mx$
显然，要不然第二组都不能满足。

### $2.sum>=1$

这次要不然第一组不能满足了

### $3.$($sum==i$&&$mx-1>=i$)$||sum>i$

这个怎么说呢~~

就好比这组数据：$5,3,2,5,5,5$

本来应该分成$(2,3,5)$和$(5,5,5)$

$i=3$时，$sum=i$

但是如果只用$sum>i$，那个在第一组里的$5$就不行了。

所以要加上$sum==i$&&$mx-1>=i$

完整代码：

```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll T;
ll n;
ll a[200010];
ll k[200010];
int main(){
    T=d;
    while(T--){
        ll n=d,mx=0;
        ll sum=0;
        memset(k,0,sizeof(k));
        f(i,1,n){
            a[i]=d;
            if(!k[a[i]])sum++;
            k[a[i]]++;
            mx=max(mx,k[a[i]]);
        }
        for(int i=n/2;i>=0;i--){
            if(i>mx)continue;
            if(sum<i)continue;
            if((sum==i&&mx-1>=i)||sum>i){cout<<i<<endl;break;}
        }
    }
    return 0;
}


```


---

## 作者：Cult_style (赞：0)

这道题按题意模拟就可以了，把每一组都列出来看哪一组可以拥有最多的人。

首先用一个vis数组来存能力值为a[i]的人有几个，然后用一个变量cnt来存总共有多少种能力值，cnt-1后就是第一组的人数了，当然，因为第一组的不能相同，所以每个能力值只能选一个人。

cnt要减一是因为本来算上了a[i]自己本身

答案就是最大的min(cnt-1，vis[i]);

不过还有一种情况，就拿样例来说：

4

1 1 1 3

可以吧vis[i]中的一个让给第一组，所以如果vis[i]-(cnt-1)≥2，cnt就可以加1，但不能加更多了，因为第一组不能有相同的。

```
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[200005],vis[200005];
int cnt,ans,ma;
int main(){
	scanf("%d",&t);
	for(int u=1;u<=t;u++){
		scanf("%d",&n);
		cnt=ans=ma=0;
		for(int i=1;i<=n;i++)
			vis[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			vis[a[i]]++;
		}
		for(int i=1;i<=n;i++)
			if(vis[i]>0) cnt++;
		for(int i=1;i<=n;i++){
			if(vis[i]>0){
				if(min(cnt-1,vis[i])>ans) ans=min(cnt-1,vis[i]);
				if(vis[i]>cnt-1){
					int x=vis[i]-(cnt-1);
					x/=2;
					if(x>1) x=1;
					x+=cnt-1;
					if(x>ans) ans=x;
				}
			}
		}	
		printf("%d\n",ans);
	}
	return 0;
}
```


---

