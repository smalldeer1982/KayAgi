# [ICPC 2016 WF] Swap Space

## 题目描述

你有许多电脑，它们的硬盘用不同的文件系统储存数据。你想要通过格式化来统一文件系统。格式化硬盘可能使它的容量发生变化。为了格式化，你需要买额外的硬盘。当然，你想要买容量最小的额外储存设备以便省钱。你可以按任意顺序格式化硬盘。格式化之前，你要把该硬盘上所有数据移到一个或更多的其他硬盘上（可以分割数据）。格式化后，该硬盘可以立刻开始使用。你没有必要把数据放到它原来所在的硬盘上。数据也可以被放到你额外买的硬盘上。举个例子，假设你有4个硬盘A、B、C、D，容量分别为6、1、3、3(GB)。新的文件系统下，它们的容量变为6、7、5、5(GB)。如果你只买1GB额外空间，你可以把B硬盘的数据放过去然后格式化硬盘B。现在你的B硬盘有7GB容量了，那么你就可以把A的数据放过去然后格式化A，最后把C、D的数据放到A上，再格式化C和D。

## 样例 #1

### 输入

```
4
6 6
1 7
3 5
3 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
2 2
3 3
5 1
5 10
```

### 输出

```
5
```

# 题解

## 作者：WaterSun (赞：7)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18337603)

怎么没有人证明贪心啊。

# 思路

显然要按 $a_i,b_i$ 的大小关系分类：

1. $a_i < b_i$：

假令有两对数 $(a_1,b_1),(a_2,b_2)$，且 $a_1 \leq a_2$。

 - 如果 $b_1 \geq a_2$。则按照 12 的顺序，将带来 $a_1$ 的花费；而按照 21 的顺序，将带来 $a_2$ 的花费。所以按照 12 顺序更优。

 - 如果 $b_1 < a_2$。则按照 12 的顺序，将带来 $a_1 + a_2 - b_1$ 的花费；而按照 21 的顺序，将带来 $a_2$ 的花费。因为 $a_1 - b_1 < 0$，所以按照 12 顺序更优。

综上，此时按照 $a_i$ 从小往大排序正确。

---

2. $a_i > b_i$：

假令有两对数 $(a_1,b_1),(a_2,b_2)$，且 $b_1 \geq b_2$：

 - 如果 $b_1 \geq a_2$。则按照 12 的顺序，将带来 $a_1$ 的花费；而按照 21 的顺序，将带来 $a_2 + a_1 - b_2$ 的花费。因为 $b_2 - a_2 < 0$，所以按照 12 顺序更优。

 - 如果 $b_1 < a_2$。则按照 12 的顺序，将带来 $a_1 + a_2 - b_1$ 的花费；而按照 21 的顺序，将带来 $a_2 + a_1 - b_2$。因为 $b_2 - b_1 < 0$，所以按照 12 顺序更优。

综上，此时按照 $b_i$ 从大往小排序正确。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define int long long

using namespace std;

typedef pair<int,int> pii;
const int N = 1e6 + 10;
int n,ans,cnt;
vector<pii> A,B;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

signed main(){
    n = read();
    for (re int i = 1,a,b;i <= n;i++){
        a = read(),b = read();
        if (a <= b) A.push_back({a,b});
        else B.push_back({a,b});
    }
    sort(A.begin(),A.end(),[](const pii &a,const pii &b){
        if (a.fst != b.fst) return a.fst < b.fst;
        else return a.snd > b.snd;
    });
    sort(B.begin(),B.end(),[](const pii &a,const pii &b){
        if (a.snd != b.snd) return a.snd > b.snd;
        else return a.fst < b.fst;
    });
    for (pii p:A){
        if (cnt >= p.fst){
            cnt -= p.fst; cnt += p.snd;
        }
        else{
            ans += (p.fst - cnt); cnt = p.snd;
        }
    }
    for (pii p:B){
        if (cnt >= p.fst){
            cnt -= p.fst; cnt += p.snd;
        }
        else{
            ans += (p.fst - cnt); cnt = p.snd;
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：5)

[传送门](https://www.luogu.com.cn/problem/P6927)

~~我贪心太菜了，只能从写题解练起~~

题目中的硬盘可以分为两类：

1.格式化后容量增大；

2.格式化后容量减小。

对于**第一种硬盘**，基于贪心的思路，由于格式化后总容量一定增大，我们需要让额外容量尽可能小，所以我们**按照格式化前的容量从小到大排序**；

对于**第二种硬盘**，我们希望让它格式化后剩余的容量尽可能大，所以**按照格式化后的容量从大到小排序**。

之后在处理过程中，我们只需要储存当前可用空间，边处理边改变答案就可以了。

下面是代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace Std
{
    template<typename tp>
    void read(tp &x)
    {
        x=0;
        tp nev=1;
        char c=getchar();
        while(c<'0'||c>'9'){if(c=='-'){nev=-1;}c=getchar();}
        while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    }
    int n,cnt1=0,cnt2=0;
    ll ans=0,now=0;
    struct node
    {
        ll st,ed;
        node(){}
        node(ll _st,ll _ed){st=_st,ed=_ed;}
    }k1[1000001],k2[1000001];
    bool cmp1(node x,node y)
    {
        return x.st<y.st;
    }
    bool cmp2(node x,node y)
    {
        return x.ed>y.ed;
    }
    int main(void)
    {
        read(n);
        ll st,ed;
        for(int i=1;i<=n;++i)
        {
            read(st),read(ed);
            if(st<ed) k1[++cnt1]=node(st,ed);
            else k2[++cnt2]=node(st,ed);
        }
        sort(k1+1,k1+1+cnt1,cmp1);
        sort(k2+1,k2+1+cnt2,cmp2);
        for(int i=1;i<=cnt1;++i)
        {
            if(k1[i].st>now)
            {
                ans+=k1[i].st-now;
                now=k1[i].ed;
            }
            else
            {
                now+=k1[i].ed-k1[i].st;
            }
        }
        for(int i=1;i<=cnt2;++i)
        {
            if(k2[i].st>now)
            {
                ans+=k2[i].st-now;
                now=k2[i].ed;
            }
            else
            {
                now+=k2[i].ed-k2[i].st;
            }
        }
        printf("%lld\n",ans);
        return 0;
    }
}
int main()
{
    return Std::main();
}
```


---

## 作者：Code_星云 (赞：4)

开始想了很多贪心方案，但总能被自己 Hack 掉。但是把那些方案融合一下，能发现这题有两个性质：

1. 若有 $a_i \leq b_i$，那么若存在一组满足该条件的硬盘，先选 $a_i$ 小的更优。

证明：设有 $(a_1, b_1)$，$(a_2,b_2)$，且 $a_1 \leq a_2$，$a_1 \leq b_1$，$a_2 \leq b_2$。那么假若 $b_1 \geq a_2$，若先选 $a_1$，总花费为 $a_1$，收益为 $b_1 + b_2$；若先选 $a_2$，收益也为 $b_1 + b_2$，不如选 $a_1$。其次，若 $b_1 < a2$（此时有 $a_1 \leq b_1 < a_2 \leq b_2$），先选 $a_1$，花费则为 $a_1 + a_2 - b_1$；先选 $a_2$，则花费为 $a_2$，又由于 $a_1 - b_1 \leq 0$，所以还是先选 $a_1$ 更优。证毕。

2. 若有 $a_i > b_i$，那么若存在一组满足该条件的硬盘，先选 $b_i$ 大的更优。

证明：设有 $(a_1, b_1)$，$(a_2,b_2)$，且 $b_1 > b_2$，$a_1 > b_1$，$a_2 > b_2$。若 $b_1 > a_2$，若先选 $a_1$（此时有 $a_2 > b_1 > a_2>b_2$），花费为 $a_1$；否则花费为 $a_2 + a_1 - b_2$，而 $a_2-b_2>0$，所以不会更优。若 $b_1 \leq a_2$（此时有 $a_1 > b_1 > b_2$），若先选 $a_1$，花费为 $a_1 + a_2 - b_1$；否则花费为 $a_2 + b_2 - a_1$，因为 $b_1 > b_2$，所以第一种更优。证毕。

然后这题还有一些细节，就是要处理排序参数相同的情况，但比较容易想到。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
#define int long long

const int N = 1000005;
struct node{
	int x, y;
}b1[N], b2[N];
int n, c1 = 0, c2 = 0, ans = 0, res = 0;

bool cmp1(node rhs1, node rhs2){
	if(rhs1.x == rhs2.x) return rhs1.y > rhs2.y;
	return rhs1.x < rhs2.x;
}
bool cmp2(node rhs1, node rhs2){
	if(rhs1.y == rhs2.y) return rhs1.x < rhs2.x;
	return rhs1.y > rhs2.y;
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i ++){
		int x, y; scanf("%lld %lld", &x, &y);
		if(x <= y) b1[++ c1] = (node){x, y};
		else b2[++ c2] = (node){x, y};
	}
	sort(b1 + 1, b1 + c1 + 1, cmp1);
	for(int i = 1; i <= c1; i ++){
		if(res >= b1[i].x){
			res -= b1[i].x;
			res += b1[i].y;
		}else{
			ans += b1[i].x - res;
			res = b1[i].y;
		}
	}
	sort(b2 + 1, b2 + c2 + 1, cmp2);
	for(int i = 1; i <= c2; i ++){
		if(res >= b2[i].x){
			res -= b2[i].x;
			res += b2[i].y;
		}else{
			ans += b2[i].x - res;
			res = b2[i].y;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Tanliu (赞：3)

对于 $b\ge a$ 的硬盘。

不难发现这类硬盘要么没有贡献，要么贡献为负。所以我们希望此时空出来的硬盘尽可能多，才能最小化额外硬盘的大小。

此时我们希望先对尽可能格式化后的大小更大，所以额外硬盘的挤压更少，所以我们以 $a$ 为第一关键字排序， $b$ 为第二关键字排序。

对于 $b\lt a$ 的硬盘

我们发现这种硬盘是有正贡献的，一开始转移的数据肯定能全部存过去格式化后的硬盘。

所以，我们希望一开始的 $a$ 尽可能小以获得最小的额外硬盘的大小。

实现贪心即可。

```cpp
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int n;
ll ans,value;
struct poi{
	int a,b;
}a[N],b[N];
bool cmp_1(poi a,poi b){
	return a.a<b.a;
}
bool cmp_2(poi a,poi b){
	return a.b>b.b;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){scanf("%d %d",&a[i].a,&a[i].b);b[i].a=a[i].a;b[i].b=a[i].b;}
	sort(a+1,a+n+1,cmp_1);
	sort(b+1,b+n+1,cmp_2);
	for(int i=1;i<=n;i++){
		if(a[i].a<=a[i].b){
			if(a[i].a>value){
				ans+=a[i].a-value;
				value=a[i].a;
			}
			value+=a[i].b-a[i].a;
		}
	}
	for(int i=1;i<=n;i++){
		if(b[i].a>b[i].b){
			if(value<b[i].a){
				ans+=b[i].a-value;
				value=b[i].a;
			}
			value+=b[i].b-b[i].a;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ppllxx_9G (赞：3)

容易发现所有磁盘都可以分成两类：

1. 格式化后容量变大。

2. 格式化后容量变小。

我们贪心的想，肯定让能变大的先变大，然后再考虑变小的。

因为先处理容量变大，再处理容量变小的，因此总容量会随着格式化先变大，再变小。

我们对于这两部分单独考虑贪心策略：

* 格式化后容量变大：我们单独拿出两个磁盘，$a_1 \lt b_1$，$a_2 \lt b_2$，$a_1 \lt a_2$。
  * 如果 $b_1 \lt a_2$，那么先选 $a_1$ 的代价是 $a_1+a_2-b_1$，先选 $a_2$ 的代价是 $a_2$，因为 $b_1 \gt a_1$，所以先选 $a_1$ 更优。
  * 如果 $b_1 \ge a_2$，先选 $a_1$ 的代价是 $a_1$，先选 $a_2$ 的代价是 $a_2$，发现还是先选 $a_1$ 更优。因此直接按 $a$ 从小到大排序即可。

* 格式化后容量变小：和上述过程类似，两个磁盘，$a_1 \gt b_1$，$a_2 \gt b_2$，$a_1 \lt a_2$，讨论 $b_2$ 和 $a_1$ 的大小关系
  * 如果 $b_2 \gt a_1$，那么先选 $a_1$ 的代价是 $a_1+a_2-b_1$，先选 $a_2$ 的代价是 $a_2$，先选 $a_2$ 更优。
  * 如果 $b_2 \le a_1$，那么先选 $a_1$ 的代价是 $a_1+a_2-b_1$，先选 $a_2$ 的代价是 $a_1+a_2-b_2$，发现 $a_1+a_2$ 的部分是相同的，所以实际上两种情况都只与 $b_1$，$b_2$ 有关，所以按 $b$ 从大到小排序。

总结：如果整个问题的贪心策略不明显，可以分成不同情况讨论。能用不等式严谨地表示最好。

---

## 作者：SunsetVoice (赞：2)

更新：一处英文和汉字之间已添加空格，请管理员检查。

更新 2：一处公式和汉字标点之间已减少空格，请管理员检查。

更新 3：已将标点和汉字间的空格删除。

这是一道贪心题。

对于每一个硬盘，有三种情况。

1. $ a_i < b_i $ 在这种情况下，格式化这种硬盘会给我们带来更大的空间，因此**优先**格式化，力图使剩余空间最大。
2. $ a_i > b_i $ 在这种情况下格式化这种硬盘会把剩余空间缩小。
3. $ a_i = b_i $ 对于这种情况，格式化和不格式化对剩余代价都没有影响，也可以看作是给我们带来了 $0$ 个剩余空间。所以我们将其归类到第一类。

所以我们格式化硬盘的顺序是先第 $1$ 类再第 $2$ 类。

为了达到将硬盘分类的目的，我们需要对硬盘排序。

第 $1$ 类中 $a_i$ 较**小**的优先。原因是由于取第 $1$ 类的硬盘对我们始终有好处，所以我们从需要空间最小的开始。

第 $2$ 类中 $b_i$ 较**大**的优先。原因是由于取第 $2$ 类的硬盘对我们始终没有好处，所以我们坏中取最优，给我们剩余空间最大的。至于为什么不是 $a_i$ 为关键字，是因为这些硬盘我们总要格式化完，$a_i$ 是多少其实已经没有影响了。

**请注意！**必须要开 `long long` 否则你会收获可爱的红色。

统计方式很简单，这里采用一种比较多余的方式，读者可以自己写一个统计方式。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct yinpan{
	int a1,b1;
}a[1000001] = {0},b[1000001] = {0};
int na = 0,nb = 0;
bool cmp(yinpan x,yinpan y){
	return x.a1<y.a1;
}
bool cmp2(yinpan x,yinpan y){
	return x.b1>y.b1;
}
signed main(){
	int n,i,j;
	while(cin>>n){
		na = 0;
		nb = 0;
		for(i = 1;i<=n;i++){
			int x,y;
			cin>>x>>y;
			if(x<=y){
				na++;
				a[na].a1 = x;
				a[na].b1 = y;
			}else{
				nb++;
				b[nb].a1 = x;
				b[nb].b1 = y;
			}
		}
		sort(a+1,a+na+1,cmp);
		sort(b+1,b+nb+1,cmp2);
		int s = 0,ans = 0;
		for(i = 1;i<=na;i++){
			ans = min(ans,s-a[i].a1);
			s+=(a[i].b1-a[i].a1);
		}
		for(i = 1;i<=nb;i++){
			ans = min(ans,s-b[i].a1);
			s+=(b[i].b1-b[i].a1);
		}
		if(ans>0)cout<<ans<<endl;
		else cout<<-ans<<endl;
	}
	system ("pause");
}

```
[双倍经验](https://www.luogu.com.cn/problem/SP27102)

[三倍经验](https://www.luogu.com.cn/problem/UVA1747)

---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6927)

一道很好的贪心题。

发现硬盘种类分为两种：1、格式化后硬盘容量增大，2、格式化后硬盘容量不增大。

考虑对这两种硬盘分别贪心。

显然对于第 $1$ 种硬盘，按格式化前的容量由小到大排序是最优解。因为这种硬盘是不断获得空间的过程，由于获得的空间总和一定，因此应该让每次获得空间所付出的代价尽量小，所以采取如上的贪心策略。

而对于第 $2$ 种硬盘，按格式化后的容量由大到小排序是最优解。因为这种硬盘是不断失去空间的过程，由于失去的空间总和一定，因此应该让每次失去之后所获得的空间尽量更大。

然后分别对两种硬盘进行贪心即可，每次贪心过程中维护现有的硬盘空间大小，同时更新答案。注意模拟时应该先模拟第 $1$ 种硬盘。

时间复杂度 $O(nlogn)$。

代码：
```cpp
#include<bits/stdc++.h>
#define back return
#define ll long long
#define ri register int
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
struct node
{
	int x,y;
}a1[1000005],a2[1000005];
bool cmp1(node a,node b)
{
	back a.x<b.x;
}
bool cmp2(node a,node b)
{
	back a.y>b.y;
}
int n,cnt1,cnt2;
ll sp,ans;
int main()
{
	n=read();
	for(ri i=1;i<=n;i++)
	{
		int a,b;
		a=read(),b=read();
		if(b>a)
			a1[++cnt1].x=a,a1[cnt1].y=b;
		else
			a2[++cnt2].x=a,a2[cnt2].y=b;
	}
	sort(a1+1,a1+cnt1+1,cmp1);
	sort(a2+1,a2+cnt2+1,cmp2);
	for(ri i=1;i<=cnt1;i++)
	{
		if(a1[i].x>sp)
			ans+=a1[i].x-sp,sp=a1[i].y;	
		else
			sp+=a1[i].y-a1[i].x;	
	}
	for(ri i=1;i<=cnt2;i++)
	{
		if(a2[i].x>sp)
			ans+=a2[i].x-sp,sp=a2[i].y;
		else
			sp+=a2[i].y-a2[i].x;
	}
	cout<<ans<<"\n";
	back 0;
}
```

---

## 作者：ivyjiao (赞：2)

三倍经验：

[P6927 [ICPC2016 WF] Swap Space](https://www.luogu.com.cn/problem/P6927)

[UVA1747 Swap Space](https://www.luogu.com.cn/problem/UVA1747)

[SP27102 FN16SWAP - Swap Space](https://www.luogu.com.cn/problem/SP27102)

首先，一个硬盘进行格式化后，对空间的贡献显然为 $b_i-a_i$。

我们可以把这些硬盘分为两类，一类贡献为正，一类贡献不为正（第二类很多题解说“贡献为负”，其实是错的，可能出现 $a_i=b_i$）。

对于贡献为正的硬盘，我们肯定希望先格式化的硬盘 $a_i$ 越小越好。因为每次格式化后都有收益，且总收益一定，我们要先格式化代价较小的，否则后格式化的硬盘就会需要更多的空间。所以这样格式化总代价一定最小。

对于贡献不为正的硬盘，我们肯定希望先格式化的硬盘 $b_i$ 越大越好。因为每次格式化后都有损耗，且总损耗一定，我们要先格式化收益较大的，否则后格式化的硬盘就会需要更多的空间。所以这样格式化总代价一定最小。

因为先获得再失去肯定比先失去再获得更优，所以要先格式化第一类硬盘。

代码：

```
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
int n,x,y,l,r,cnt,ans;
pair<int,int>a[1000001],b[1000001];
bool cmp(pair<int,int>x,pair<int,int>y){
    return x.se>y.se;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x>>y;
        if(y>x) a[++l]={x,y};
        else b[++r]={x,y};
    }
    sort(a+1,a+1+l);
    sort(b+1,b+1+r,cmp);
    for(int i=1;i<=l;i++){
        if(cnt<a[i].fi){
            ans+=a[i].fi-cnt;
            cnt+=a[i].fi-cnt;
        }
        cnt-=a[i].fi;
        cnt+=a[i].se;
    }
    for(int i=1;i<=r;i++){
        if(cnt<b[i].fi){
            ans+=b[i].fi-cnt;
            cnt+=b[i].fi-cnt;
        }
        cnt-=b[i].fi;
        cnt+=b[i].se;
    }
    cout<<ans;
}
```

---

## 作者：_shining (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P6927)

## 题意

这题就是让我们求最小的额外容量。

## 思路

不难发现答案一定是满足单调性的——如果你 $x$ 的容量可以的话，那么比 $x$ 还大的容量肯定可以，再看一眼数据范围 $n\le 10^6$，那么就可以想到**二分答案**。

我们先将硬盘排序，先把格式化后空间**大于**原来数据量的排序，这样就可以获得更多的容量。之后再把格式化后空间**小于**原来数据量的排序，尽可能的位后面的硬盘备份留足空间。

排完序后，把这两种情况塞到一个数组中二分答案即可。

综上，时间复杂度为 $\mathcal{O(n\log n)}$，空间复杂度为 $\mathcal{O(n)}$。

代码：

```cpp
#include <iostream>
#include <algorithm>
#define int long long 
using namespace std;//命名空间
const int N = 1e6 + 5;
int n, cntb, cntc;
struct poi{
	int a, b;
}a[N], b[N], c[N];
inline bool check(int mid)
{
	int now = mid;//now表示当前有的容量 
	for(int i = 1; i <= n; i++){
		if(now < a[i].a) return 0;
		now -= a[i].a;
		now += a[i].b;
	}
	return 1;
}
inline bool cmpb(poi x, poi y){return x.a < y.a;}
inline bool cmpc(poi x, poi y){return x.b > y.b;}
signed main()//主函数
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		int x, y;
		cin >> x >> y;
		if(x <= y) b[++cntb] = {x, y};//格式化后有更多的容量 
		else c[++cntc] = {x, y};
	}
	sort(b + 1, b + cntb + 1, cmpb);
	sort(c + 1, c + cntc + 1, cmpc);
	for(int i = 1; i <= cntb; i++) a[i] = b[i];
	for(int i = 1; i <= cntc; i++) a[i + cntb] = c[i];
	int l = -1, r = 1e15 + 5; 
	while(r - l > 1){
		int mid = l + r >> 1;
		if(check(mid)) r = mid;
		else l = mid;
	} 
	cout << r;
	return 0;//华丽结束
} 
```

---

## 作者：DengDuck (赞：1)

来个相当严谨的证明。

首先依旧是分类，显然 $a_i<b_i$ 的比 $a_i\geq b_i$ 的更优，因为可以使空闲的空间变多。

然后对于 $a_i<b_i$ 内部，我们考虑有 $a_x<a_y$，此时空闲空间为 $t$：
- 如果 $t\geq a_y$ 那么选谁代价都一样。
-  如果 $a_x\leq t<a_y$，那么先选 $a_x$ 是无需代价的，而且可以使 $t$ 变大减少选 $a_y$ 时的代价，所以选 $a_x$ 更优。
- 如果 $t<a_x$，那么选谁都需要多余的代价产生，先选 $a_x$ 代价为 $a_x-t+\max(a_y-b_x,0)$，先选 $a_y$ 代价是 $a_y-t$，容易看出前者更小。

所以这一部分我们的策略是 $a_x<a_y$。

对于 $a_i\geq b_i$，是类似地分讨，但是会更加复杂，所以不多赘述。

然后我们直接模拟就做完了。

---

## 作者：ZPB2011 (赞：1)

# [Swap Space](https://www.luogu.com.cn/problem/P6927)

## 思路

看完发现可以贪心。

我们可以按 $a_i$ 和 $b_i$ 来分类。

- $a_i \le b_i$ 可以按 $a_i$ 从小到大排序，这样可以尽量不让 $a_i$ 比当前剩余空间多。

- $a_i > b_i$ 可以按 $b_i$ 从大到小排序，这样可以得到尽量多的空间。

## AC code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;

const int N = 1e5 + 5;

struct node {
	int x, y;
};

vector<node> a, b;

bool cmp(node x, node y) {
	return x.x < y.x;
}

bool cmp2(node x, node y) {
	return x.y > y.y;
}

signed main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		if(x <= y) {
			a.push_back({x, y});
		}
		else {
			b.push_back({x, y});
		}
	}
	sort(a.begin(), a.end(), cmp);//贪心
    sort(b.begin(), b.end(), cmp2);
	int ans = 0, sum1 = 0, sum2 = 0;
	for(int i = 0; i < a.size(); i++) {
		int x = a[i].x, y = a[i].y;
		if(sum1 - sum2 < x) {
			int tmp = x - (sum1 - sum2);
			ans += tmp;
			sum1 += tmp;
		}
		sum2 += x;
		sum1 += y;
	}
	for(int i = 0; i < b.size(); i++) {
		int x = b[i].x, y = b[i].y;
		if(sum1 - sum2 < x) {
			int tmp = x - (sum1 - sum2);
			ans += tmp;
			sum1 += tmp;
		}
		sum2 += x;
		sum1 += y;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://doittomorrow.xyz/post/icpc2016-wf-swap-space-de-ti-jie/)
# 题目大意
给你 $n$ 个硬盘，第 $i$ 个硬盘原来有 $a_i$ 的内存，但是在转化格式之后内存就变成了 $b_i$。在转化格式的时候，全部的资料都需要转移到其他空间，如果空间不够用就可以额外申请空间。在最开始的时候每个硬盘都装满了，求额外申请的空间的最小值。

# 思路
首先所有的硬盘一共与三种分类：$a_i<b_i$，$a_i=b_i$，$a_i>b_i$。

因为第 $2$ 类对于答案没有影响，所以为了便于处理，我们将第 $2$ 类归入第一类，即 $a_i\le b_i$，$a_i>b_i$。

应该优先处理第 $1$ 类，因为在修改之后剩余的空间是在增加的。

对于第 $1$ 类，应该按 $a_i$ 从小到大处理更优，证明如下：
> 假设有 $2$ 块硬盘分别是 $(a_1,b_1)$ 和 $(a_2,b_2)$。

> 如果 $b_1\ge a_2 $：先处理 $a_1$ 再处理 $a_2$，需要的代价是 $a_1$；先处理 $a_2$ 再处理 $a_1$，需要的代价是 $a_2$。因为 $a_1\le a_2$，所以先处理第 $1$ 块更优。

> 如果 $b_1< a_2$：先处理 $a_1$ 再处理 $a_2$，需要的代价是 $a_1+a_2-b_1$；先处理 $a_2$ 再处理 $a_1$，需要的代价是 $a_2$。因为$a_1+a_2-b_1\le a_2$，所以先处理第 $1$ 块更优。

对于第 $2$ 类，应该按 $b_i$ 从大到小处理更优，证明如下：
> 假设有 $2$ 块硬盘分别是 $(a_1,b_1)$ 和 $(a_2,b_2)$。

> 如果 $b_1\ge a_2 $：先处理 $a_1$ 再处理 $a_2$，需要的代价是 $a_1$；先处理 $a_2$ 再处理 $a_1$，需要的代价是 $a_2+a_1-b_2$。因为 $a_1\le a_2+a_1-b_2$，所以先处理第 $1$ 块更优。

> 如果 $b_1< a_2$：先处理 $a_1$ 再处理 $a_2$，需要的代价是 $a_1+a_2-b_1$；先处理 $a_2$ 再处理 $a_1$，需要的代价是 $a_2+a_1-b_2$。因为$a_1+a_2-b_1\le a_2+a_1-b_2$，所以先处理第 $1$ 块更优。

所以，排序之后模拟整个过程，时间复杂度 $O(n\log n)$。

# AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,c1,c2,ans,cnt;
struct node{int a,b;}s1[N],s2[N];
bool cmp1(node x,node y){return x.a<y.a;}
bool cmp2(node x,node y){return x.b>y.b;}
signed main(){
	cin>>n;
	for(int i=1,a,b;i<=n;i++){
		cin>>a>>b;
		if(a<b) s1[++c1]={a,b};
		else s2[++c2]={a,b};
	}sort(s1+1,s1+1+c1,cmp1),sort(s2+1,s2+1+c2,cmp2);
	for(int i=1;i<=c1;i++){
		if(cnt<s1[i].a) ans+=(s1[i].a-cnt),cnt=0;
		else cnt-=s1[i].a;
		cnt+=s1[i].b;
	}for(int i=1;i<=c2;i++){
		if(cnt<s2[i].a) ans+=(s2[i].a-cnt),cnt=0;
		else cnt-=s2[i].a;
		cnt+=s2[i].b;
	}cout<<ans<<endl;
	return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

每个硬盘格式化之后大小会发生改变，并且格式化时硬盘内不能有东西。所以需要新的空间来辅助格式化，问最少要多少新的空间。

## 解法

贪心即可。硬盘可以分为两类：格式化之后空间变大的和格式化之后空间变小的。

* 考虑情况 $1$，空间变大，那么取的时候应该优先取花费更小的，即格式化之前空间很小的。

* 考虑情况 $2$，空间变小，那么取的时候应该优先取价值更大的，即格式化之后空间很大的；

将情况 $1$ 的前后空间存进 $a$ 数组，情况 $2$ 存进 $b$ 数组，进行 sort 排序，分别遍历，更新当前可用空间。若此时可用空间不足装进原本空间，即移动数据时有数据无处存放，将答案加上还需要的空间。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,a1,b1,cun,cnt;
struct node
{
	int x,y;
}a[1000001],b[1000001];
bool cmpa(node x,node y)
{
	return x.x < y.x;
}
bool cmpb(node x,node y)
{
	return x.y > y.y;
}

signed main()
{
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		if(x < y) a[++a1] = (node){x,y};//情况1
		else b[++b1] = (node){x,y};//情况2
	}
	sort(a + 1,a + a1 + 1,cmpa);//分别排序
	sort(b + 1,b + b1 + 1,cmpb);
	for(int i = 1;i <= a1;i++)
	{
		if(cun < a[i].x)//空间不足
		{
			cnt += a[i].x - cun;
			cun = a[i].x;
		}
		cun -= a[i].x;//更新当前可用空间
		cun += a[i].y;
	}
	for(int i = 1;i <= b1;i++)
	{
		if(cun < b[i].x)
		{
			cnt += b[i].x - cun;
			cun = b[i].x;
		}
		cun -= b[i].x;
		cun += b[i].y;
	}
	printf("%lld",cnt);
	return 0;
}
```


---

## 作者：lqsy002 (赞：0)

## 题目大意
题目已经写得很清楚了。[题目链接](https://www.luogu.com.cn/problem/P6927)。
## 解题思路
**贪心。**

1. 扩大的，要先选初始空间小的，这样花费小，空间扩大后说不定就能存储初始空间大的了，这样通过空间扩大的硬盘可以积累一定的空间。
2. 空间不变的无所谓，我是先进性的初始空间小的。
3. 空间缩小的，应该先选择缩小后空间较大的，这样可以用来存储后面空间较大的。

综上，可以发现能将硬盘容量变大的优先，这种硬盘就是以格式化前的大小升序排序。然后如果硬盘容量变小，那就是先填格式化后较大的硬盘（因为装完可以提供较大的空间）。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int a,b,cmp_ab;
	void compare(){
		if(a>b)
			cmp_ab=1;
		else if(a<b)
			cmp_ab=-1;
		else 
			cmp_ab=0;
	}
}hdd[1000010];
bool cmp(node x,node y){
	if(x.cmp_ab!=y.cmp_ab)
		return x.cmp_ab<y.cmp_ab;
	if(x.cmp_ab<0)
		return x.a<y.a||(x.a==y.a&&x.b>y.b);
	if(x.cmp_ab==0)
		return x.a<y.a;
	return x.b>y.b||(x.b==y.b&&x.a<y.a);
}
long long ans,space;
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&hdd[i].a,&hdd[i].b);
		hdd[i].compare();
	}
	sort(hdd+1,hdd+1+n,cmp);
	for(int i=1;i<=n;++i)
		if(space<hdd[i].a){
			ans+=hdd[i].a-space;
			space=hdd[i].b;
		}else
			space+=hdd[i].b-hdd[i].a;
	cout<<ans;
	return 0;
}
```

---

## 作者：_zexal_ (赞：0)

一道简单贪心题。考虑 $a \ge b$ 和 $a \lt b$ 的情况即可。由于要求最后的附加内存尽可能的小，所以我们一定会要求我们能拿的磁盘空间尽可能的大。当 $a \le b$ 时，格式化硬盘过后只会**增加**容量，所以我们一定会优先。当 $a \gt b$ 时，我们容量会减少，所以我们一定会放最后，并且 $b$ 越大的我们越前面。

我们在输入把硬盘分成两类对应上述情况。然后对 $a\le b$ 情况的按照 $a$ 值从小到大排序。对 $a \gt b$ 情况按 $b$ 的值从大到小排序即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int Maxn=2e6+5;
#define F(i,a,b) for(int i=a;i<=b;i++)
int n,ans;
struct node{
	int a,b;
}f[Maxn],f1[Maxn],f2[Maxn];
int tot1,tot2;
bool cmp(node a,node b){
	return a.a<b.a;
}
bool cmb(node a,node b){
	return a.b>b.b;
}
signed main(){
	cin>>n;
	F(i,1,n){
		cin>>f[i].a>>f[i].b;
		if(f[i].a<=f[i].b) f1[++tot1]=f[i];
		else f2[++tot2]=f[i];
	}
	sort(f1+1,f1+tot1+1,cmp);
	sort(f2+1,f2+tot2+1,cmb);
	int Ans=0;
	F(i,1,tot1){
		if(Ans<f1[i].a) ans+=f1[i].a-Ans,Ans=f1[i].a;
		Ans=Ans-f1[i].a+f1[i].b;
	}
	F(i,1,tot2){
		if(Ans<f2[i].a) ans+=f2[i].a-Ans,Ans=f2[i].a;
		Ans=Ans-f2[i].a+f2[i].b;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：elonzhang (赞：0)

# [P6927 [ICPC2016 WF] Swap Space](https://www.luogu.com.cn/problem/P6927)

## 思路
首先可以发现确定了格式化硬盘的顺序我们可以通过线性时间复杂度算出额外硬盘的空间。然后我们考虑贪心策略：当 $b_i\ge a_i$ 时我们要按照 $b_i$ 的大小降序排序，因为这样可以尽量产生更多的空间供第二种使用；当 $b_i<a_i$ 时，则需要以 $a_i$ 升序排序，尽量不要让所需 $a_i$ 大于当前的 $ans$ 。显然先处理第一种更好，所以开始愉快的写代码吧！

## ACcode
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=1e6+1;
int n,t,a[N],b[N],id[N],ans,sum;

bool cmp(int x,int y){
	int ax=a[x],bx=b[x],cx=b[x]-a[x],ay=a[y],by=b[y],cy=b[y]-a[y];
	return ((cx>=0)^(cy>=0)?cx>cy:(cx>=0?ax<ay:bx>by));
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
//	freop();
//↑以上为初始化↑
//------------------------------
	cin >> n;
	for(int i = 1;i<=n;++i) cin >> a[i] >> b[i],id[i]=i;
	sort(id+1,id+n+1,cmp);
	for(int i = 1;i<=n;++i)	ans=max(ans,a[id[i]]-sum),sum+=b[id[i]]-a[id[i]];
	cout << ans << endl;
	return 0;
}
```

---

## 作者：A6n6d6y6 (赞：0)

## 题目大意
对 $n$ 块硬盘更改格式，对于第 $i$ 块硬盘初始容量为 $a_i$，更改后容量为 $b_i$。所有硬盘初始均存满了数据。每个硬盘更改时必须将硬盘中的数据复制到空容量中，数据可以拆分成多个部分存放在不同硬盘。处理过程中可能至少需要额外 $m$ 的容量来使得 $n$ 块硬盘都能更改成功，问 $m$ 的最小值。

## 问题分析
遇到这种求最小值的题，考虑**贪心**。

硬盘有三类情况（其实第二类可以随便归为其他一种）： 
- $a_i<b_i$
- $a_i=b_i$
- $a_i>b_i$

显然优先处理第一类，其次第二类，最后第三类。

考虑第一类的处理顺序：

**结论**：对于第一类，以 $a_i$ 从小到大排序一定为最优方案。

**证明**：取第一类的硬盘如果从 $a_i$ 大的取，会需要更多额外容量。

考虑第三类的处理顺序：

**结论**：对于第三类，以 $b_i$ 从大到小排序一定为最优方案。

**证明**：取第三类的硬盘如果从 $b_i$ 小的取，会使后面的数据容易无处可存。

对于第二类，可以归到第一类中（前面说了）

所以既然有了顺序，那这道题就变成模拟题了，在此不再赘述。

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;
struct disk{
	int a,b;
}d[maxn];
bool cmp(disk a,disk b){
	if(a.a<=a.b&&b.a>b.b)return 1;//优先处理第一类
	if(a.a>a.b&&b.a<=b.b)return 0;//最后处理第三类
	if(a.a<=a.b&&b.a<=b.b)return a.a<b.a;//第一类按照a从小到大排序
	if(a.a>a.b&&b.a>b.b)return a.b>b.b;//第一类按照b从大到小排序
}
int n,t,ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>d[i].a>>d[i].b;
	sort(d+1,d+n+1,cmp);//排序 
	for(int i=1;i<=n;i++){
		t-=d[i].a;
		ans=min(ans,t);
		t+=d[i].b;
	}//模拟 
	cout<<-ans;//输出答案 
	return 0;
}
```
经验池：

[\[ICPC2016 WF\] Swap Space](https://www.luogu.com.cn/problem/P6927)

[FN16SWAP - Swap Space](https://www.luogu.com.cn/problem/SP27102)

[Swap Space](https://www.luogu.com.cn/problem/UVA1747)

~~蒟蒻第一次写题解，管理大大求过~~

---

