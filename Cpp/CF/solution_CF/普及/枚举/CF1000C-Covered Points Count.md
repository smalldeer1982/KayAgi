# Covered Points Count

## 题目描述

**题目大意：**

给你n个区间，求被这些区间覆盖层数为$k(k<=n)$的点的个数

## 样例 #1

### 输入

```
3
0 3
1 3
3 8
```

### 输出

```
6 2 1 
```

## 样例 #2

### 输入

```
3
1 3
2 4
5 7
```

### 输出

```
5 2 0 
```

# 题解

## 作者：良月澪二 (赞：7)

## 差分思想太重要了

把每一条线段看成两个端点，左端点为1右端点为-1

把这些线段按左端点排序，用一个cnt维护当前区间上有多少条线段，遇到左端点+1，遇到右端点-1

直接用map存储，Lambda表达式遍历就好了

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#define A 1000010
#define B 2010

using namespace std;
typedef long long ll;
int n;
ll l, r, ans[A], cnt, tmp;
map<ll, ll> m;

int main(int argc, char const *argv[]) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> l >> r;
		m[l]++; m[++r]--; //不知道为什么++r的去学差分
	}
	for_each(m.begin(), m.end(), [] (const pair<ll, ll> &it) { //不需要理解，知道是遍历就好
		ans[cnt] += it.first - tmp;
		tmp = it.first;
		cnt += it.second;
	});
	for (int i = 1; i <= n; i++) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：SSHhh (赞：6)

我在做这道题时，乍一看，诶，这不是一个前缀和扫一遍吗？于是我就非常愉快的打了一遍。。。然后就 GG 了。

RE 完之后，我再去看了一遍数据范围 -- WOC，为什么 l，r 是 1e18？好吧，那这道题还没有想象中的那么水。。。

不过很快大家就能注意到：n 只有 20 万。这说明了什么呢？说明前缀和改变的节点最多只有 40 万个。那么我们把这些节点存起来再一排序，然后扫一遍不就得了？

那么我们就用一个 now 记录当前段被覆盖了几次，然后枚举排序后前缀和改变的节点，把每次改变之前的一段中的节点数加入覆盖数为 now 的答案，最后修改 now 的值即可。还要注意一点：每一个线段的左端点和右端点的节点类型是不一样的，遇到左端点要 now++，右端点则要 now--。

下面附上代码吧：

```
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n;long long ans[200005];
struct nod{
	long long p;int k;	//p 代表节点下标，k 代表节点类型
};
bool cmp(nod i,nod j){return i.p==j.p?i.k<j.k:i.p<j.p;}
vector<nod> q;	//用 vector 保存节点
int main()
{
	long long l,r;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>l>>r,q.push_back((nod){l,1}),q.push_back((nod){r+1,-1});
	sort(q.begin(),q.end(),cmp);
	long long last=0,now=0;
	for(int i=0;i<q.size();i++)
	{
		long long nex=q[i].p;	//枚举改变的节点
		ans[now]+=q[i].p-last,now+=q[i].k,last=nex;
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";	//输出
}
```

---

## 作者：Limit (赞：3)

刚刚看到这题时感觉特别难...经过大约10分钟的思考....
呀 ~~水题QAQ~~ 不多说了上代码呀QAQ
```
#include<iostream>//标准模板呀QAQ
#include<cstdio>
#include<cmath>
#include<string.h>
#include<algorithm>
#define For(i,f,l) int pd=(f<l)*1+(l<=f)*-1;for(i=f;i!=l+pd;i+=pd)
using namespace std;
void read(long long &n)
{
  long long x=0;int w=1; char ch=0;
  while(!isdigit(ch)){if(ch=='-')w=-1;if(ch=='+')w=1;ch=getchar();}
  while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
  n=w*x;
}
void write(long long x)
{
  if(x<0){putchar('-');x=-x;}
  if(x>9)write(x/10);
  putchar(x%10+'0');
}
struct Sort//定义一个类
{
  long long w,a;
  //w为位置,a为做的操作
}p[1000000];
bool cmp(Sort &a,Sort &b)
{
  return a.w<b.w;//按w的大小排序
}
int i,j,k,sum=0,m;
long long ans[1000000],l,r,n,now=0;//注意开long long
int main()
{
  read(n);
  for(i=1;i<=n;i++)
  {
  	read(l);read(r);
  	sum++;
    p[sum].w=l;
  	p[sum].a=1;//区间起始位置为++
  	sum++;
  	p[sum].w=r+1;//结束位置为--
  	p[sum].a=-1;
  }
  sort(p+1,p+sum+1,cmp);//排序
  l=p[1].w;//当前位置
  now=p[1].a;//当前覆盖层数
  for(i=2;i<=sum;i++)
  {
  	ans[now]+=p[i].w-l;//当前层数的个数为前后操作位置只差
  	l=p[i].w;
  	now+=p[i].a;
  }
  for(i=1;i<=n;i++)cout<<ans[i]<<" ";//输出呀QAQ
  return 0;
}
```
算是一道大水题呀QAQ...
建议去做一下[借教室](https://www.luogu.org/problemnew/show/P1083),用了差不多的思想呀...

---

## 作者：yuheng_wang080904 (赞：2)

## 题目意思

给你 $n$ 个区间，求被这些区间覆盖层数为 $k(k<=n)$ 的点的个数

输入第一行一个整数 $n(n<=2×10^5)$ ,以下 $n$ 行，每行有两个整数，即这个区间的左右端点 $l$,$r(0<=l<=r<=10^{18})$。

要求输出 $n$ 个整数，即每个被覆盖层数对应的点的个数

## 思路

大家可以自行对样例画一张图来理解。

我们可以想到对于每一个 $[l_i,r_i]$，可以让 $[l_i,∞)+1$，同时 $[r_i +1,∞)-1$。这样正好保证了每一段中的每一个点都被计算一次。这个工作可以在输入的同时完成。用一个 $pair$ 数组来存这些操作。

然后把 $pair$ 数组进行排序，一段一段操作。用变量 $cnt$ 来判断这个区间内点的覆盖次数：每次加上这个 $pair$ 中的第二个值就行。答案可以用一个数组保存，注意每次加上的是区间那一段点的个数。

## 代码

接下来贴无注释代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pll pair<long long,long long>
pll cl[400010];
int n,i,c,cnt;
long long f[400010];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(i=1;i<=n;i++){
    	long long l,r;
    	cin>>l>>r;
    	cl[++c]=pll(l,1);
    	cl[++c]=pll(r+1,-1);
    }
    sort(cl+1,cl+c+1);
    for(i=1;i<=c;i++){
    	f[cnt]+=cl[i].first-cl[i-1].first;
    	cnt+=cl[i].second;
    }
    for(i=1;i<=n;i++)cout<<f[i]<<" ";
    return 0;
}
```
## 另解代码

大家可以学习一下另一种思路：离散，差分。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l[200005],r[200005],x[400010],cnt[400010],res[200005];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&l[i],&r[i]),r[i]++;
        x[i*2-1]=l[i],x[i*2]=r[i];
    }
    sort(x+1,x+2*n+1);
    for(int i=1;i<=n;i++){
        int tl=lower_bound(x+1,x+2*n+1,l[i])-x,tr=lower_bound(x+1,x+2*n+1,r[i])-x;
        cnt[tl]++,cnt[tr]--;
    }
    for(int i=1;i<=2*n;i++)cnt[i]+=cnt[i-1];
    for(int i=1;i<=2*n;i++)res[cnt[i]]+=x[i+1]-x[i];
    for(int i=1;i<=n;i++)printf("%lld%c",res[i]," \n"[i==n]);
    return 0;
}
```


---

## 作者：VenusM1nT (赞：2)

其实只要离散差分搞一下就可以了……然而我在看到这一题的时候第一想法又是区间加什么的，于是就大力搞了个离散 + 线段树，做法也差不多，取出每个位置的累加次数，然后减去这个位置作为**右端点**的次数，得到的就是以它为左端点的右侧一条线段对应的累加值，存一下就行了。  
（实在太暴力了，我佛了）
```cpp
#include<bits/stdc++.h>
#define MAXN 400005
#define reg register
#define inl inline
#define int long long
using namespace std;
struct Segment
{
	int x,y;
}a[MAXN];
int n,node[MAXN],tot,ans[MAXN],duan[MAXN];
int t[MAXN<<2],tag[MAXN<<2];
map <int,int> mp;
inl void PushUp(reg int rt)
{
	t[rt]=t[rt<<1]+t[rt<<1|1];
}
inl void PushDown(reg int rt,reg int len)
{
	if(tag[rt])
	{
		t[rt<<1]+=tag[rt]*(len-(len>>1));
		t[rt<<1|1]+=tag[rt]*(len>>1);
		tag[rt<<1]+=tag[rt];
		tag[rt<<1|1]+=tag[rt];
		tag[rt]=0;
	}
}
void Modify(reg int rt,reg int l,reg int r,reg int tl,reg int tr,reg int val)
{
	if(tl<=l && r<=tr)
	{
		t[rt]+=val;
		tag[rt]+=val;
		return;
	}
	reg int mid=(l+r)>>1;
	if(tl<=mid) Modify(rt<<1,l,mid,tl,tr,val);
	if(tr>mid) Modify(rt<<1|1,mid+1,r,tl,tr,val);
	PushUp(rt);
}
int Query(reg int rt,reg int l,reg int r,reg int tl,reg int tr)
{
	if(tl<=l && r<=tr) return t[rt];
	reg int mid=(l+r)>>1,res=0;
	PushDown(rt,r-l+1);
	if(tl<=mid) res+=Query(rt<<1,l,mid,tl,tr);
	if(tr>mid) res+=Query(rt<<1|1,mid+1,r,tl,tr);
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(reg int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
		node[++tot]=a[i].x;
		node[++tot]=a[i].y;
	}
	sort(node+1,node+tot+1);
	tot=unique(node+1,node+tot+1)-node-1;
	for(reg int i=1;i<=tot;i++) mp[node[i]]=i;
	for(reg int i=1;i<=n;i++) duan[mp[a[i].y]]++;
	for(reg int i=1;i<=n;i++) Modify(1,1,n*2,mp[a[i].x],mp[a[i].y],1);
	for(reg int i=1;i<tot;i++) ans[Query(1,1,n*2,i,i)-duan[i]]+=node[i+1]-node[i]-1;
	for(reg int i=1;i<=tot;i++) ans[Query(1,1,n*2,mp[node[i]],mp[node[i]])]++;
	for(reg int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：1)

# [CF1000C](https://www.luogu.com.cn/problem/CF1000C) 题解
## 题目描述
给定 $n$ 个区间，枚举有多少个节点被覆盖 $k$ 次，$k=\left[1,n\right]$。

## 题目分析
**关于差分**

你会发现不可以用差分，因为 $0\le l\le r\le 10^{18}$。

---
**关于离散化**

~~我不想用。~~

---
**直接记录**

记录每一个 $l_i,r_i$，同时记录节点的类型：$l_i$ 还是 $r_i$。

将这个结构体按照位置排序，因为任意 $l_i\le r_i$，所以排序后不存在下标为负的情况。

同时对于每一个节点，记录此时节点被覆盖的次数 $cnt$。每访问到一个节点就存储 $ans_{now}$，并且改变 $now$ 的值。

最后直接输出 $ans$ 数组。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
int n;
struct node{
	int pl;
	int k;
	bool operator <(const node o)const{
		return pl<o.pl;
	}
}e[MAXN<<1];
void Push(int i,int x,int k){
	e[i].pl=x;
	e[i].k=k;			
}
int ans[MAXN];
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		int li,ri;
		cin>>li>>ri;
		Push(i*2-1,li,1);
		Push(i*2,ri+1,-1); 
	}
	sort(e+1,e+2*n+1);
	int now=0,lst=0;
	for(int i=1;i<=n*2;i++){
		int siz=e[i].pl-lst;
		ans[now]+=siz;
		now+=e[i].k;
		lst=e[i].pl;
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
		
}
```

---

## 作者：_xxxxx_ (赞：1)

### 题解

给出 $n$ 和 $n$ 条线段，问在数轴上，被 $i$ 条线段覆盖的点的个数有多少个（$0\le i\le n$）？

### 分析

一看到题，很容易想到建一个大小为线段最大覆盖区域的差分数组，存完扫一遍输出。但是你开数组的时候，会发现......

$$0\le l,r\le10^{18}$$

但是，随即你会看到 $n\le 2 \times 10^5$。意思就是说，只会有 $4 \times 10^5$ 个端点，那就还是可以用差分， 因为只会影响这些地方。

用结构体存起来，把节点排好序，用上差分数组就能算了。

拿一个 $id$ 存现在的节点的坐标，当前的点数就是当前差分数组的值减去 $id$。到下一层的时候把 $id$ 改为当前差分数组的值就好了。

另外注意一下到右端点的时候的时候要减一，有差分。

### 代码

```
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <cstdio>
#include <algorithm>
#define int long long//开long long 
using namespace std;
const int N = 4e5 + 10;
const int INF = 0x3f3f3f3f;
int n, len, ans[N];
//len是点的个数 
struct node
{
	int num;
	bool flag;
}p[N];
bool cmp(node a, node b)
{
	return a.num < b.num;//从小到大 
}
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		p[++len].num = x;//左 
		p[len].flag = 1;
		p[++len].num = y + 1;//右，差分 
		p[len].flag = 0;
	}
	sort(p + 1, p + len + 1, cmp);
	int id = p[1].num, now = p[1].flag;
	for(int i = 2; i <= 2 * n; i++)
	{
		ans[now] += p[i].num - id;//算个数 
		id = p[i].num;
		if(p[i].flag == 1)//判断是否右端点 
		{
			now++;
		}
		else
		{
			now--;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		cout << ans[i] << " ";
	}
	return 0;
}
```

最后解释一下为什么 `ans[now]` 不会出现负数下标。

因为左端点总是坐标比右端点小，所以会减一前就一定会加一，有点像[括号匹配](https://www.luogu.com.cn/problem/CF1023C)。

---

## 作者：jhdrgfj (赞：1)

## 解法

使用离散化 + 差分。

用一个 ``map`` 储存每一个层数变化的点。那么每读入一条线段的左右端点 $l,r$，就将 $d_l + 1$，$d_{r+1}+1$。将所有线段读入完后，再使用前缀和统计各层数对应的端点数量就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[200005],n,l,r,x,la;  //数据很大，要开 long long
map<ll,int> m;
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>l>>r;
		m[l]++;
		m[r+1]--;       //差分
	}
	for (auto i=m.begin();i!=m.end();i++){
        a[x]+=i->first-la;         //两个点之间有 r-l 个点
        x+=i->second; 
        la=i->first;            //记录上一个点
	}
	for (int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
}
```


---

## 作者：xiaozeyu (赞：1)

**Python 题解**

[CF1000C Covered Points Count](https://www.luogu.com.cn/problem/CF1000C)

~~既然到高中了，就要好好学习 python~~ 

这道题直接用 Python 做时有点麻，最后还是稍微参照了一下别人用的数据类型才解决一些 MLE 和 TLE 的问题

题目会给出一些线段在一个较长的坐标轴上进行覆盖。

然后我们要统计出不同覆盖次数的点数。

我们可以进行差分，因为坐标大但是总共的修改量更小，所以我们在统计的时候可以根据修改过的点的坐标进行枚举。

我们可以用 c++ 中的 map 存差分数组，然后对于输入排序，再遍历排完序的输入数组，不用去管重复的坐标，上一次的值加上这次坐标对应的差分数组的值可以得出后面的值的大小，而这次的坐标减去上一次的坐标可以得出两者之间值与上一个坐标的值相同的点的个数。

如果用 Python 写起来短但是感觉麻烦（？）。

这个 defaultdict 用起来跟 c++ 的 map 差不多。

输入时用 split 分割。

```python
l,r=map(int,input().split());
```

这句话来实现正常读入。

c++ 版的太好写了就不写了。

---

```python
from collections import*
n=int(input())
f=[0]*(n+1)
d=defaultdict(int)
for i in range(0,n):
 l,r=map(int,input().split());d[l]+=1;d[r+1]-=1
s=p=0
for k in sorted(d):#range(0,ff+2):
 f[s]+=k-p;s+=d[k];p=k
for i in range(1,n+1):
 print(f[i])
```

---

感谢管理员的审核。

---

## 作者：AlicX (赞：0)

## Solution 

类似扫描线的思路，加入进来一条线段 $[l,r]$，可以在 $l$ 的位置 $+1$，在 $r+1$ 的位置 $-1$，然后将数组按下标排序，当一段区间的覆盖数为正数时，这个覆盖数的答案就应该加上 $r-l+1$。注意开 `long long` ！！！

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=4e5+10; 
int n; 
pii a[N]; 
int ans[N]; 
map<int,int> mp; 
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
};  
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il bool cmp(pii a,pii b){
	return a.x<b.x; 
}
signed main(){ 
	n=read(); int cnt=0; 
	for(int i=1,l,r;i<=n;i++) l=read(),r=read(),a[++cnt]={l,1},a[++cnt]={r+1,-1};  
	sort(a+1,a+cnt+1,cmp); mp[a[1].x]+=a[1].y; 
	for(int i=2;i<=cnt;i++){ 
		if(mp[a[i-1].x]>=1) ans[mp[a[i-1].x]]+=a[i].x-a[i-1].x; 
		mp[a[i].x]=mp[a[i-1].x]+a[i].y; 
	} for(int i=1;i<=n;i++) printf("%lld ",ans[i]); puts("");  
	return 0;
} /* */ 
```

CSP2023 RP++。


---

## 作者：FutureSnow (赞：0)


其实这道题不能直接差分的，不然等着你的就是一片基佬紫，因为这题的数据会惊到你的，$1 \le l \le r \le 10^{18}$!

如果不能直接模拟差分的话，我们就需要考虑存有效区间端点来复盘差分过程了。


我们再来回顾一下差分的具体操作（默认区间 $ +1 $）

```cpp
cin >> l >> r;//区间的左端点和右端点
sub[l]++; sub[r + 1]--;//在差分数组中进行区间增加操作
```
其实区间端点最重要的是它的位置信息，所以我们在存有效节点的时候只需要存它的位置和它是左端点还是右端点行了（节点类型）

#### 这里注意一下，差分时在左端点 $+1$，右端点的下一个点 $-1$，所以说左端点的 $type$ 存 $1$， 右端点的下一个点的 $type$ 存 $-1$（直接存右端点$+1$），这样有利于下一步遍历。

#### 然后把数组按位置从小到大排序，如果位置相同，左端点在前，右端点在后。

#### 接下来，进入第三步，遍历

在遍历时我们定义一个 $cnt$ 变量记录当前被覆盖的层数，定义一个类似于桶的数组 $cnt$ 遇到端点时就加上 $type$。对于每两个端点的区间，只要有 $cnt > 0$，在桶数组按题目要求进行统计：

```cpp
tong[cnt] = r - l + 1;
```
随后输出桶数组即可。

接下来看完整AC代码，这里我使用的是vector<struct>来存储输入。
  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct etu{
	int x;
	int type;
};

bool cmp(etu a, etu b){
	if(a.x == b.x){
		return a.type < b.type;
	}
	return a.x < b.x;
}
vector<etu> urp;
int n, l, r, tong[200020];
signed main (){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> l >> r;
		urp.push_back((etu){l, 1});
		urp.push_back((etu){r + 1, -1});
	}
	sort(urp.begin(), urp.end(), cmp);
	int cnt = 0, last = 0, now = 0;
	int len = urp.size();
	for(int i = 0; i < len; i++){
		now = urp[i].x;
		tong[cnt] += now - last;
		cnt += urp[i].type;
		last = now;
	}
	for(int i = 1; i <= n; i++){
		cout << tong[i] << " ";
	}
	return 0;
}
```


---

