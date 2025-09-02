# Coffee Break

## 题目描述

### 题目大意：
给定$n$个数和一个$k$，这$n$个数都不超过$m$

每次从没被去掉的数里面选一个数$a$，去掉$a$，然后可以任意一个$b(b>a+k)$，然后去掉任意一个$c(c>b+k)$，以此类推

问最少能选多少个$a$，然后输出每个数都是选第几个$a$的时候被去掉的

## 样例 #1

### 输入

```
4 5 3
3 5 1 2
```

### 输出

```
3
3 1 1 2 
```

## 样例 #2

### 输入

```
10 10 1
10 5 7 4 6 3 2 1 9 8
```

### 输出

```
2
2 1 1 2 2 1 2 1 1 2 
```

# 题解

## 作者：封禁用户 (赞：2)

## 题解：CF1041C Coffee Break

我发现所有题解都是二分做的，没有排序以外使用 $O(n)$ 算法的题解，所以我来分享一下我的做法。

### 解题思路

我们可以运用**贪心**的思想，也就是：要么能用去掉的最小以前的数，满足此时的数 $\ge$ 以前的数 $+\ k$；要么需要一个额外的 $a$。所以我可以 $O(1)$ 维护一个数组，使得数组从小到大排序，也就是每一次操作要么在队首，要么在队尾。

先看图辅助理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/8zyde8hn.png?x-oss-process=image/resize,m_lfit,h_4000,w_6000)

已有数组即为现有的所有 $a$。

情况 $1$ 对应上面“满足此时的数 $\ge$ 以前的数 $+\ k$”，所以我们将最小的数改为现在的数，并放在数组末端。

情况 $2$ 对应上面“需要一个额外的 $a$”，所以直接在数组末端加入一个元素。

算法复杂度：$O(n)$。

### 温馨提示

- 由于需要保证初始数组的单调性，所以这段代码的综合复杂度是 $O(n \log n)$，而不是 $O(n)$。
- 如果你像我一样没有使用 `STL` 模板，请务必为存储 $a$ 的数组（也就是上文所说的队列）打开双倍空间。
- 最后输出答案即为队列的长度。
- 还有什么疑问可以再结合代码理解，~~自认为码风不错，但是没加注释~~。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
struct p
{
	int a , b , ans;
}a[200005];
struct q
{
	int a , b;
}day[400005];
int n , m , d , s = 1 , e = 1 , dtmp = 2;
bool cmpa(p l , p r)
{
	return l.a < r.a;
}
bool cmpb(p l , p r)
{
	return l.b < r.b;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> d;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i].a;
		a[i].b = i;
		day[i].a = -2000000009;
	}
	day[1].b = 1;
	sort(a + 1 , a + n + 1 , cmpa);
	for(int i = 1 ; i <= n ; i++)
	{
		if(a[i].a - d > day[s].a)
		{
			day[s].a = a[i].a;
			e++;
			day[e] = day[s];
			s++;
			a[i].ans = day[e].b;
		}
		else
		{
			e++;
			day[e].a = a[i].a;
			day[e].b = dtmp;
			a[i].ans = dtmp;
			dtmp++;
		}
	}
	sort(a + 1 , a + n + 1 , cmpb);
	cout << e - s + 1 << '\n';
	for(int i = 1 ; i <= n ; i++)
	{
		cout << a[i].ans << ' ';
	}
	return 0;
}
```

**感谢浏览！**

---

## 作者：Cure_Wing (赞：1)

### 题目
[CF1041C Coffee Break](https://www.luogu.com.cn/problem/CF1041C)

### 解析
考虑为了选到的 $a$ 的个数最少，那么可以使每次选择的序列尽可能的长。如果这一次选择次长序列，那么原最长序列若未被拆散，则答案不变；若原最长序列被拆散，那么答案一定不会更优。故贪心成立。

如果直接在原序列上操作，那么会面临反复横跳的尴尬境界，那么此时可以将序列从小到大排序，可以使用二分（或者直接 `STL`）查找满足条件的数。若满足条件的数已被选择，那么顺移直至符合条件或越界。可以看出，每扫描一遍序列，都能找出当前的 $a$ 所影响的最长序列。

最后注意将序列恢复所得到的就是答案了。

### 代码
很重要的一点是，我们在选取第 $i$ 个 $a$ 时，可以从第 $i$ 个数开始寻找，因为在前 $(i-1)$ 次操作中，前 $(i-1)$ 小的数一定全部被选择了。这样减少了开头的冗余查找，从而大大降低了时间复杂度。

考虑选到第 $i$ 的个数时，搜索合法数的时间为 $\mathcal{O}(\log(n-i))$，而每个位置至多被查询一次，那么总复杂度为 $\mathcal{O}(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
int n,m,k,cnt,count,a[200005];
struct node{
	int a,b,id;
}t[200005];
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i) cin>>t[i].a,t[i].id=i;
	std::sort(t+1,t+n+1,[](node a,node b){return a.a<b.a;});//排序
	for(int i=1;i<=n;++i) a[i]=t[i].a;
	while(count<n){
		int head=++cnt;//很重要的一点
		while(t[head].b&&head<=n) ++head;
		if(head>n) break;
		t[head].b=cnt;++count;
		while(head<=n){//查找当前符合条件的数
			head=std::upper_bound(a+1,a+n+1,a[head]+k)-a;
			while(t[head].b&&head<=n) ++head;
			if(head>n) break;
			t[head].b=cnt;
			++count;
		}
	}//count统计已被选择的数的个数，cnt统计已选择的 a 的个数
	std::sort(t+1,t+n+1,[](node a,node b){return a.id<b.id;});//恢复原序列
	cout<<cnt<<'\n';
	for(int i=1;i<=n;++i) cout<<t[i].b<<' '; 
    return 0;
}
```


---

## 作者：youdu666 (赞：1)

### 思路：贪心、二分

拿到数据以后，记录数字的原先位置，并按数值进行排序。

顺序扫描数列，在找到一个未被用过的数字后，计数器加一，同时使用二分查找第一个既符合条件又没有用过的数字，贪心地将该数字标为使用后继续向下扫描即可。时间复杂度 $O(n\log_2n)$，可以通过此题。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
inline int read(void)
{
    int x=0,y=1;
    char c=getchar();
    while(c>'9'||c<'0')
    {
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}
const int N=2e5+5;
int n,m,k,ans[N],t,pp;
struct kof{
    int x,ip,usd;
    bool operator<(const kof &T)const{//重构运算符，便于排序和二分
        return x<T.x;
    }
}a[N];
signed main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)
        a[i].x=read(),a[i].ip=i,a[i].usd=0;
    sort(a+1,a+n+1);//排序
    for(int i=1;i<=n;i++)
    {
        if(a[i].usd)
        {
            ans[a[i].ip]=a[i].usd;//这里usd同时充当了使用标记和使用时间
            continue;
        }
        pp++;//次数加一
        ans[a[i].ip]=pp;
        a[i].usd=pp;
        int bk=a[i].x+k+1;//上次的数字
        for(;;)
        {
            t=lower_bound(a+1,a+n+1,(kof){bk,0,0})-a;//用stl二分查找
            while(a[t].usd&&t<=n)t++;//必须要没用过
            if(a[t].x<bk)break;
            a[t].usd=pp;
            bk=a[t].x+k+1;//反复查找直到找不到
        }
    }
    printf("%d\n",pp);//输出
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    printf("\n");
}
```


---

## 作者：Mine_King (赞：1)

我们先把问题转化一下：  
选最少的 $a$，相当于让每次选 $a$ 被删掉的数最多。  

既然要让删掉的数最多，那么每次就要选尽量小的 $a$，这样就可以让后面的 $b,c,d,\cdots$ 有更多的选择。  
再进一步，选 $b$ 的时候也要选得尽量小，理由同上。  
以此类推……  
所以每次选择最小的数删掉，结果最优。  

具体实现就是，对这 $n$ 个数从小到大排序，然后每次找到最小的 $a$，再二分找到最小的大于 $a$ 的 $b$，然后一直二分直到找不到。  
当然我们也要记录每个数是否被删去。如果二分到的结果被删掉了，则往后顺延。  

还不懂的话可以康代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,k,ans;
int v[200005];//v表示这个数是在第几个a被删去的。
struct node
{
	int num,id;
	friend bool operator<(node x,node y)
	{return x.num<y.num||(x.num==y.num&&x.id<y.id);}
}a[200005];//因为要记录第几个被删去，所以还要记录每个数原来的位置，即代码中的id
bool cmp(node x,node y){return x.num<y.num;}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].num),a[i].id=i;
	sort(a+1,a+n+1);
	for(int cnt=0;cnt<n;)//cnt记录的是被删掉的数的个数
	{
		for(int i=ans+1;i<=n;i++)
			if(v[a[i].id]==0)//v=0表示没被删掉
			{
				ans++;cnt++;
				v[a[i].id]=ans;//记录被删掉的时间
				node p;
				p.id=n+1,p.num=a[i].num+k;
                //p作为要二分的数，二分出来的结果要>=p。
				for(;;)
				{
					int j=upper_bound(a+1,a+n+1,p)-a;//二分
					while(v[a[j].id]!=0) j++;//往后顺延
					if(j>n) break;//j>n就再也找不到了，直接退出
					v[a[j].id]=ans;
					cnt++;
                    //标记
					p.num=a[j].num+k;//更新条件
				}
				break;
			}
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++) printf("%d ",v[i]);
	return 0;
}
```

---

## 作者：William_Fangs (赞：1)

## 这是一道贪心题
可以证明，每次将当前最小的未丢弃的数作为 $a$ 时最优  
将 $a$ 丢弃之后，用二分选择比 $a+k$ 大的最小的未被丢弃的数作为 $b$，以此类推.  
解释见代码  
```cpp
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=200086;
int n,m,k;
struct node//定义一个结构体,记下其数值和id
{
	int v;
	int id;//id在填数时用得到
	bool operator < (const node & rhs)const
	{
		if(v==rhs.v)//这里应判断一下,因为此题没有spj,不特判一下可能会wa
			return id<rhs.id;
		return v<rhs.v;
	}
};
node a[N];
inline bool cmp(node aa,node bb)
{
	if(aa.v==bb.v)
		return aa.id<bb.id;
	return aa.v<bb.v;
}
int cs[N];//存第几次被丢弃
int cnt;
int now;
bool flag[N];//存该数是否被丢弃
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].v);
		a[i].id=i;
	}
	sort(a+1,a+n+1);
	int ac=0;//已经丢了几次a
	while(cnt<n)//cnt表示已经丢了几个数
	{
		int now=-1;
		for(int i=ac+1;i<=n;i++)
      /*
      	当丢了ac次a时,用从ac+1处开始扫最优(可能)
      */
		{
			if(!flag[i])
			{
				now=a[i].v;
				flag[i]=true;
				ac++;
				cnt++;
				cs[a[i].id]=ac;
				break;
			}
		}
		node p;
		p.v=now+k;
		p.id=n+1;/*其实这里可以特判一下,若p.v>a[n].v,则剩下的所有数都只能作为a被丢弃,这样会更快*/
		while(p.v<=a[n].v)
		{
			int j=upper_bound(a+1,a+n+1,p)-a;
			while(flag[j]&&j<=n)//向右找到第一个未被丢弃的数
			{
				j++;
			}
			if(j>n)
			{
				break;
			}
			flag[j]=true;
			cnt++;
			cs[a[j].id]=ac;
			p.v=a[j].v+k;
		}
	}
	printf("%d\n",ac);
	for(int i=1;i<=n;i++)
	{
		if(i!=1) printf(" ");
		printf("%d",cs[i]);
	}
	return 0;
}
```

---

## 作者：ezoixx130 (赞：1)

### 题意：

有$n$个休息时刻，你需要把这$n$个休息时刻安排到尽量少的天中，使得每两个休息时刻的间隔大于$d$分钟，一天有$m$分钟。

注意两天之间的间隔大于d分钟。

### 题解：

我们贪心选取时刻，每次把尽量小的时刻安排进这一天中，如果没有能安排进这一天的时刻了，我们就必须新开一天，并且选取最小的时刻安排进第二天中，然后继续贪心。

这样我们必须有一种数据结构来快速查找和删除。

那当然是set啦！

方法就是，开一个set把所有时刻存储起来，然后每次找到最小的能安排进这一天的时刻，把这个时刻安排进这一天。如果找不到就安排一个最小的时刻到第二天。每次安排完一个时刻就把这个时刻从set中删除。找最小的时刻用lower_bound就可以了。

**注意**：假设我们有一个set，名字为a，我们要查找元素x，使用`lower_bound(a.begin(),a.end(),x)`的时间复杂度为$O(n)$，而使用`a.lower_bound(x)`的时间复杂度为$O(log(n))$。

时间复杂度：$O(nlog(n))$

空间复杂度：$O(n)$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 200010

struct data
{
    int val,id;
    bool operator<(const data d)const
    {
        return val<d.val;
    }
}x;
int n,m,d,pos[MAXN];
set<data> a;

int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&x.val);x.id=i;
        a.insert(x);
    }
    int now=(*a.begin()).val,cnt=1;
    pos[(*a.begin()).id]=1;
    a.erase(a.begin());
    for(int i=2;i<=n;++i)
    {
        data x;x.val=now+d+1;
        auto p=a.lower_bound(x);
        if(p!=a.end())
        {
            pos[(*p).id]=cnt;
            now=(*p).val;
            a.erase(p);
            continue;
        }
        ++cnt;
        p=a.begin();
        pos[(*p).id]=cnt;
        now=(*p).val;
        a.erase(p);
    }
    printf("%d\n",cnt);
    for(int i=1;i<=n;++i)printf("%d ",pos[i]);
}
```

---

## 作者：AlicX (赞：0)

## Solution 

~~一道恶评题~~ 

记上一次删的数为 $lst$，因为要尽量在少选初始数的情况下删除所有数，所以初始数一定是越小越好，也说明了 $lst$ 越小越好，这样可供删除的数就越多。据此，我们可以先对数组排序。

选出初始数后，更新 $lst$ 是一个十分简单的过程，每一次二分找出一个数 $x$，使得 $x \ge lst+k+1$，删除它后将 $lst$ 赋为 $x$。

因为每个数只会删除一次，所以总的时间复杂度为 $\mathcal{O(n\log n)}$。

```cpp
// Celestial Cyan 
// Luogu uid : 706523 
// Luogu : https://www.luogu.com.cn/problem/CF1041C
// CF : https://codeforces.com/problemset/problem/1041/C
// AT : sb
// FTOJ : nb 
// Contest : Codeforces Round 509 (Div. 2)
// Cnblogs : died 
// Memory Limit: 256 MB
// Time Limit: 2000 ms 
// 2023/7/17 

#include<bits/stdc++.h>
//#define int long long 
#define x first
#define y second
#define il inline 
#define db double
#define low(x) x&-x
#define ls(x) x<<1
#define rs(x) x<<1|1 
#define pb(x) push_back(x)
#define gcd(x,y) __gcd(x,y) 
#define lcm(x,y) x*y/gcd(x,y) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=2e5+10,INF=1e9+7; 
int n;
int m,k; 
pii a[N];
int cnt[N];
bool st[N]; 
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
signed main(){ 
	n=read(),m=read(),k=read(); 
	for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=i;
	sort(a+1,a+n+1); int ans=0; 
	for(int i=1;i<=n;i++){ 
		if(st[i]) continue; 
		st[i]=true; ans++; 
		int lst=a[i].x+k+1; cnt[a[i].y]=ans; 
		while(lst<=m){ 
			int x=lower_bound(a+1,a+n+1,pii(lst,0))-a; 
			while(x<=n&&st[x]) x++; if(x>n) break; 
			cnt[a[x].y]=ans; st[x]=true; lst=a[x].x+k+1;  
		} 
	} printf("%d\n",ans); for(int i=1;i<=n;i++) printf("%d ",cnt[i]); puts(""); 
	return 0; 
} /* */ 
```

---

## 作者：zsyyyy (赞：0)

# CF1041C题解 尺取

## 题意

给定 $n$ 个数表示一些时间点。

给出一个 $d$ ，表示相差大于 $d$ 的时间点可以安排在一天中。

再给出一个 $m$ 表示一天的时间长度。（保证 $m$ 大于所有时间点）

问最少多少天可以安排完所有时间点并给出方案。



## 思路

先排序，然后再用尺取，如果左右端点可以匹配就右移左端点并记录左右端点安排在了第几天，否则就右移右端点。

特别的，如果左右端点可以匹配但是右端点已经匹配过了那么就不匹配这两个点并且右移右端点，因为已经与右端点匹配到同一天的那个时间点会与当前的左端点冲突（一定冲突的原因：如果这两个点不会冲突的话它们一定已经匹配过了）。

注意因为最后的顺序不能是排序后的顺序，所以必须用结构体。


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=200005;
int n,m,d,book[MAX],cnt,t,ans[MAX];
struct node
{
	int ti,d,book; //分别表示：时间点,原始位置,最终安排在第几天
}a[MAX];
bool cmp(node x,node y)
{
	return x.ti<y.ti;
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&d);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i].ti);
		a[i].d=i;
	}
	sort(a+1,a+n+1,cmp);
	int r,l;
	r=l=1;
	while(l<=r&&l<=n&&r<=n)
	{
		if(a[r].ti-a[l].ti>d)
		{
			if(a[r].book) //左右端点可以匹配但右端点已经匹配过的情况
			{
				r++;
				continue;
			}
			a[r].book=a[l].book;
			if(!a[r].book)  a[r].book=a[l].book=++t;
			cnt++;
			l++;
		}
		else  r++;
	}
	printf("%lld\n",n-cnt);
	for(int i=1;i<=n;i++)
	{
		if(!a[i].book)  a[i].book=++t;
		ans[a[i].d]=a[i].book;  //记录原顺序下的答案
	}
	for(int i=1;i<=n;i++)  printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：Daidly (赞：0)

每次选最小的可以使答案最优，并且选的越小越好，因此我们想到了贪心做法。

先对序列排序，使序列单调。

再通过二分查找找到第一个满足条件（大于上一个加 $k$）的数，再这样查找下去，直到不存在满足条件的数。

这样从前到后寻找到的数就是一组，它们的次数是一样的。

关于细节：

- 二分查找的是原序列最小没有被查找的数加上 $k$，并且在查找内部不能选择已经确定过的。

- 注意二分查找边界条件。

- 查找区间可以设为 $[now+1,n]$，每一次找到就记录答案即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}
const int MAXN=2e5+5;
int n,m,k,ans[MAXN],cnt;
struct node{
	int w,num;
}a[MAXN];
bool cmp(node x,node y){
	return x.w<y.w;
}
void find(int x,int pos){
	if(a[n].w<=x+k)return;
	int l=pos+1,r=n;
	while(l<=r){
		int mid=l+r>>1;
		if(a[mid].w>x+k)r=mid-1;
		else l=mid+1;
	}
	while(ans[a[l].num])l++;
	if(l>n)return;
	ans[a[l].num]=cnt;
	find(a[l].w,l);
}
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;++i){
		a[i].w=read();
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i){
		if(!ans[a[i].num]){
			cnt++;
			ans[a[i].num]=cnt;
			find(a[i].w,i);
		}
    }
    print(cnt),puts("");
    for(int i=1;i<=n;++i){
		print(ans[i]),printf(" ");
	}
	return 0;
}

---

## 作者：帅到报警 (赞：0)

### 【题意描述】
XXX 找到了一份工作，他想在工作期间喝咖啡。但是有一些限制。给出 n , m , d , n 为他希望在某一天的这一分钟休息， m 为一天的长度， d 为每两杯咖啡之间的至少间隔。然后让我们求出最少用几天可以在给出的 n 个时间点都喝过咖啡。然后输出，每个时间点在第几天。

### 【分析】
这道题乍一看是要用贪心的，因为对于每一天的每一个时间点，如果这一天能塞下这个时间点，那么对于下一天如果塞这个时间点必定更优。所以只要在每一天塞下最多的就行了。即先排一遍序，从第一个开始塞入每一天中，直到所有元素都被选中。

但是！！！

由于数据非常恶心，所以普通的从 1 开始搜索的策略是不可行的，肯定超时。那么就要考虑二分查找，**用二分找到第一个满足条件的元素，再向后一个个寻找第一个未使用的元素，直到这一天塞不下停止**。

但是！！！

程序依然在这里跑超时了...然后只能再进行优化，将**每一天的最初元素从上一天得最初元素得后一个开始找**，这样就可以跑过了。

### 【核心代码】
1、储存这个时间点的信息：

	tim -> 时间点   grp -> 第几天   
    tag -> 是否访问过   id -> 原始编号
```cpp
struct Node{
	int tim, grp, tag, id;
	bool operator < (const Node b){
		return tim < b.tim;
	}
	Node(){tag = 0;}
}a[N];
```

2、从第一天开始塞时间点， pree 为上一天的第一个元素， num 为第几天，numm 为这天找到了第几个， k 为已塞入的总元素个数。
```cpp
while(k != n)
{
	for(int i = pree; i <= n; i++)
		if(!a[i].tag)
		{
			pre = i, pree = pre + 1;
			break;
		}
	a[pre].tag = 1, k++, a[pre].grp = num;
	while(true)
	{
		numm = Search(pre);
		if(numm > n)  break;
		a[numm].grp = num, a[numm].tag = 1, k++, pre = numm;
	}
	num++;
}
```

3、关键：**二分**，记得每一次找到的不一定符合，要继续找。如果没有符合条件的 return n + 1 ， 就可以跳出了主程序的循环。
```cpp
inline int Search(int x)
{
	int l = x, r = n, mid;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(a[mid].tim - a[x].tim > d)
			r = mid - 1;
		else  l = mid + 1;
	}
	for(int i = l; i <= n; i++)
		if(!a[i].tag)  return i;
	return n + 1;
}
```

4、第一行输出总天数，第二行输出每一个时间点的组别。
```cpp
cout << num - 1 << endl;
for(int i = 1; i <= n; i++)
	printf("%d ", a[kth[i]].grp);
```

### 【正解】
```cpp
#include <bits/stdc++.h>
#define N 200010
using namespace std;

int kth[N];
int n, m, d, k, num, pre, pree, numm;

struct Node{
	int tim, grp, tag, id;
	bool operator < (const Node b){
		return tim < b.tim;
	}
	Node(){tag = 0;}
}a[N];

inline int Search(int x)
{
	int l = x, r = n, mid;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(a[mid].tim - a[x].tim > d)
			r = mid - 1;
		else  l = mid + 1;
	}
	for(int i = l; i <= n; i++)
		if(!a[i].tag)  return i;
	return n + 1;
}

int main()
{
	scanf("%d %d %d", &n, &m, &d);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i].tim), a[i].id = i;
	num = 1, pree = 1, sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++)
		kth[a[i].id] = i;
	while(k != n)
	{
		for(int i = pree; i <= n; i++)
			if(!a[i].tag)
			{
				pre = i, pree = pre + 1;
				break;
			}
		a[pre].tag = 1, k++, a[pre].grp = num;
		while(true)
		{
			numm = Search(pre);
			if(numm > n)  break;
			a[numm].grp = num, a[numm].tag = 1, k++, pre = numm;
		}
		num++;
	}
	cout << num - 1 << endl;
	for(int i = 1; i <= n; i++)
		printf("%d ", a[kth[i]].grp);

	return 0;
}
```

---

## 作者：wz20201136 (赞：0)

# 思路 : 二分答案 + 贪心检查
二分答案：

我们这里二分的并不是下一个翻译中的 $b$ 的值，而是直接二分删去 $a$ 的次数。因为满足只要满足可以删除 $x$ 个 $a$，那么删除 $x+1$ 个 $a$ 一定也满足条件。

贪心检查：

检查是否符合条件，检查的其实是所有处在同一组的两个元素之差的最小值是否大于 $k$ 设这个值为 $Min$，所以说我们要构造出 $mid$ 组元素使得 $Min$ 最大。
我的贪心策略是对于排序后的每个下标 $i$ 我们都让第 $i-mid$ 个元素与他同一组。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,d,ans[200005];
struct node
{
	int num,id;
	bool operator<(const node &o) const
	{
		return num<o.num;
	}
}a[200005];
bool check(int x)
{
	for(int i=x+1;i<=n;i++)
		if(a[i].num-a[i-x].num-1<d) return 0;
	return 1;
}
int main()
{
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].num;
		a[i].id=i;
	}
	sort(a+1,a+n+1);
	int l=1,r=n,find;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))
		{
			find=mid;
			r=mid-1;	
		}
		else l=mid+1;
	}
	for(int i=1;i<=n;i++) ans[a[i].id]=i%find;
	cout<<find<<endl;
	for(int i=1;i<=n;i++)
	{
		if(ans[i]==0) cout<<find<<' ';
		else cout<<ans[i]<<' ';
	}
	return 0;
}
```

---

