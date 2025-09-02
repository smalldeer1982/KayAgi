# [USACO18JAN] Lifeguards S

## 题目描述

FJ 为他的奶牛们建造了一个游泳池，FJ 认为这将有助于他们放松身心以及生产更多牛奶。

为了确保奶牛们的安全，FJ 雇佣了 $N$ 头牛，作为泳池的救生员，每一个救生员在一天内都会有一定的事情，并且这些事情都会覆盖一天内的一段时间。为了简单起见，泳池从时间 $t=0$ 时开门，直到时间 $t=10^9$ 关门，所以每个事情都可以用两个整数来描述，给出奶牛救生员开始以及结束事情的时间。例如，一个救生员在时间 $t=4$ 时开始事情并且在时间 $t=7$ 时结束事情，那么这件事情就覆盖了 $3$ 个单位时间。（注意：结束时间是“点”的时间）

不幸的是，FJ 多雇佣了一名的救生员，但他没有足够的资金来雇佣这些救生员。因此他必须解雇一名救生员，求可以覆盖剩余救生员的轮班时间的最大总量是多少？如果当时至少有一名救生员的事情已经开始，则这个时段被覆盖。

## 样例 #1

### 输入

```
3
5 9
1 4
3 7```

### 输出

```
7```

# 题解

## 作者：违规用户名71524 (赞：23)

这个题一看1e5的数据显然就想到了线段树做法：先把所有时间点离散化然后建线段树维护哪些位置上的覆盖次数为一，然后一个一个奶牛去查询他们的区间。
写着写着突然发现实际上我们就是要处理出每头奶牛区间里仅由他自己覆盖的长度，也就是那些覆盖次数为一的位置上的长度和。这样我们就有了一种线性查询的算法：先用差分算出每个时间点被覆盖的次数，然后对于那些为一的地方加上他们的长度，同时维护前缀和。这样对于每头奶牛就可以o(1)地求他管辖范围内的且仅由他管辖的长度，然后愉快的求最大值输出就好了(。・∀・)ノ

```cpp
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<bitset>
#include<vector>
#include<math.h>
#include<stack>
#include<map>
#include<queue>
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define eps 1e-9
using namespace std;
int n;
struct nod
{
    int l,r,ll,rr;
}cw[100005];
int b[300005],cnt,cc[300005];
int sum[800005];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&cw[i].l,&cw[i].r);
        b[++cnt]=cw[i].r;
        cw[i].r--;
        cw[i].ll=b[++cnt]=cw[i].l;
        cw[i].rr=b[++cnt]=cw[i].r;
    }
    sort(b+1,b+1+cnt);
    int tot=unique(b+1,b+1+cnt)-b;
    for(int i=1;i<=n;i++)
    {
        cw[i].l=lower_bound(b+1,b+1+tot,cw[i].l)-b;
        cw[i].r=lower_bound(b+1,b+1+tot,cw[i].r)-b;
        cc[cw[i].l]++;
        cc[cw[i].r+1]--;
    }//离散化
    int cov=0;//总的覆盖长度
    for(int i=1;i<=tot;i++)
    {
        cc[i]+=cc[i-1];
        if(cc[i])cov+=b[i+1]-b[i];
        if(cc[i]==1)sum[i]=b[i+1]-b[i];
        sum[i]+=sum[i-1];
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=max(ans,cov-(sum[cw[i].r]-sum[cw[i].l-1]));
    }
    printf("%d",ans);
}
```
我虽然是个蒟蒻，但是自认码风清新易读，应该都看得懂吧

φ(゜▽゜*)♪

---

## 作者：mysssss (赞：20)

~~我都不敢想象我居然能写出提高+省选-的题~~

这题看前面的大佬都是用线段树写的

那我就用。。比较玄学的方法写下吧  ~~其实是因为我不会线段树~~

大概思路是用结构体覆盖，也可以将每一段工作时间理解为一截线段

废话不多说，上代码（思路见代码批注）~
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans,sp,m=100000000;
struct tim
{
	int l;
	int r;
}a[100010];//建立结构体，方便记录起始时间点和结束时间点
int cmp(tim x,tim y)
{
	return x.l<y.l;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].l,&a[i].r);
		sort(a+1,a+n+1,cmp);//按起始点排序
		for(int i=1;i<=n;i++)
		{
			if(a[i].r>sp)//原来记录覆盖点的末点小于当前工作结束点
			{
            int u=max(sp,a[i].l);
            //若sp大则意为新输入的这段线段的初始点在原已覆盖所有点之内
            //若a[i].l大则意为新输入的这段线段的初始点在原覆盖线段末点之外
				ans+=a[i].r-u;//加入新覆盖线段的长度
				sp=a[i].r;//更新覆盖线段末点
			}
		}
		sp=0;//一定要记得初始化！！！
		a[n+1].l=a[n].r;//建立边界，防止溢出
		for(int i=1;i<=n;i++)//求出线段对总覆盖线段的最小作用
		{
			if(a[i].r<=sp)//如果此线段的末点在总覆盖线段之内，即无作用
			m=0;
			else
			{
			int z=min(a[i+1].l,a[i].r)-max(a[i].l,sp);
            //配合代码下方的图理解
			m=min(m,z);//求出最小作用段
			sp=max(a[i].r,sp);//更新末端点，不断缩小查找范围
			}
		}
        m=max(0,m);//m不能为负数
		printf("%d",ans-m);//用总线段减去最小的作用段后，即可求出解雇一名救生员后最大的覆盖时间
	return 0;
}
```
![](https://mail.qq.com/cgi-bin/download?mailid=ZC2720-0mP5GMqI_d7F2UQYP0vVQ8c&filename=tijie.png&sid=_EnIf63v4cLZtit3&type=json)

好了，基本就是这样，以此较玄学方法来救助跟我一样的蒟蒻同胞们~

~~感觉我把一道tg+的题硬生生地写成了普及+~~

大佬们多多包容指教咯，完结撒花~

---

## 作者：囧仙 (赞：4)

## 题目大意

> 有 $n$ 个线段 $[a_i,b_i]$ 。现在询问去掉一条线段后，剩余线段可以覆盖的最大长度。

## 题解

请注意**时间段**和**时刻**的区别。前者是一段时间，而后者只是一个时间节点。下文中我们认为第 $i$ 时刻与第 $i+1$ 时刻为第 $i$ 个单位时间。

显然，这题是可以用差分数组来解决的。具体而言，我们开一个数组 $W$ ，其中 $W_i$ 表示第 $i$ 个时段后覆盖层数的**增加值**（特别地，如果 $W_i<0$ ，就认为是覆盖层数减少了 $|W_i|$ ）。于是我们只需要扫描一遍 $W_i$ ，就可以计算出对于每个时间段实际覆盖的层数。对于一个区间 $[s,t]$ ，我们只要 $W_{s+1}\gets W_{s+1}+1 ,W_{t+1}\gets W_{t+1}-1$ 即可（ $s$ 时刻下面的时段是 $s+1$ ， $t$ 时刻下面的时段是 $t+1$ ）。

对于所有线段的实际覆盖长度，只要统计其中有多少个时段被覆盖了不小于 $1$ 次就行了。

我们依次考虑移走线段 $[a,b]$ 带来的影响。显然，移走 $[a,b]$ 后，在 $[a,b]$ 内原来只被覆盖了一层的时段就不会被覆盖了，因此我们要求出有多少只覆盖了一层的线段。事实上，我们可以用前缀和来解决，记 $C_i$ 表示时段 $1\sim i$ 有多少条线段被覆盖了恰好一次，那么计算 $[a,b]$ 中覆盖了一层的线段就是 $C_{b}-C_{a-1}$ 。同样是单次 $\mathcal O(1)$。

但是问题就这么结束了吗？显然没有。由于本题的值域达到了 $10^9$ ，因此我们要进行**离散化**处理，在本题中也就是把所有时刻排个序，并根据它的排名分配在差分数组当中的位置。这样显然不会影响线段覆盖层数的正确性。

总的时间复杂度是 $\mathcal O(n\log n)$ ，而排序就是这种做法的瓶颈（当然你可以用基数排序做到 $\mathcal O(n)$ 排序；这个就是后话了）。事实上，题解区中所谓的“$\mathcal O(n)$ 做法”大多没有考虑排序的复杂度。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e5+3;
int n,S[MAXN],T[MAXN],O[MAXN*2],w,ans,t,W[MAXN*2],C[MAXN*2];
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    n=qread(); up(1,n,i){
        S[i]=qread(),O[++t]=S[i];T[i]=qread(),O[++t]=T[i];
    }
    sort(O+1,O+1+t); up(1,n,i){
        int a=S[i]=lower_bound(O+1,O+1+t,S[i])-O; ++W[a+1];
        int b=T[i]=lower_bound(O+1,O+1+t,T[i])-O; --W[b+1];
    }
    up(1,t,i){
        W[i]+=W[i-1]; int l=O[i]-O[i-1];
        C[i]=C[i-1]+(W[i]==1)*l,w=w+(W[i]>=1)*l;
    }
    up(1,n,i){
        int a=S[i],b=T[i]; ans=max(ans,w-C[b]+C[a]);
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Charles_2016 (赞：4)

这道题可以用差分+树状数组过  
一个救生员在的时间里，认为是左闭右开的，因此在左端点做+1，代表现在多了个救生员，右端点-1，代表一个救生员溜了，因此差分数组在某个点的前缀和表示了当前有几个救生员在干活  
解雇一个救生员会少掉的覆盖时间就是在他在的时间中，只有他一个人在的时间  
总覆盖时间就是有救生员在干活的时间长
求最小值后再用总时间减掉就是答案
```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;
const int INF = 1 << 28;
const int MAXT = 1000000008;
const int MAXN = 100008;
priority_queue<int,vector<int>,greater<int> > pq;//偷懒的离散化
map<int,int> mp;// mp[i] = j 的意思是i在离散化后变为了j
int rev[MAXN * 2];// rev[j] = i 的意思是j是i在离散化之后变成的

int n;
int d[MAXN * 3];//差分数组
int c[MAXN * 3];//树状数组
int lowbit(int x){
	return x & (-x);
}
void Modify(int pos,int val){
	while (pos <= 3 * n){
		c[pos] += val;
		pos += lowbit(pos);
	}
	return;
}

int query(int x){
	int ans = 0;
	while (x > 0){
		ans += c[x];
		x -= lowbit(x);
	}
	return ans;
}
int l[MAXN];
int r[MAXN];

int main(){
	cin >> n;
	for (int i = 1 ; i <= n ; i++){
		cin >> l[i] >> r[i];
		pq.push(l[i]); pq.push(r[i]);
	}
	int cnt = 0;
	while (!pq.empty()){
		cnt++;
		int t = pq.top();
		while (pq.top() == t && !pq.empty()) pq.pop();
		mp[t] = cnt;
		rev[cnt] = t;
	}//偷懒的离散化
	for (int i = 1 ; i <= n ; i++){
		int ll = mp[l[i]];
		int rr = mp[r[i]];
		d[ll]++; d[rr]--;
	}//做差分 ll处 +1 rr 处 -1 认为是左闭右开区间
	int now = 0;
	for (int i = 1 ; i <= cnt ; i++){
		now += d[i];
		if (now == 1){
			int right = i;
			while (d[right + 1] == 0){
				right++;
			}
			Modify(i,rev[right + 1] - rev[i]);
		}
        //如果now = 1 说明现在这段时间有且仅有一个救生员
        //在i处加上一个离散化之前的长度
	}
	int minn = INF;
	for (int i = 1 ; i <= n ; i++){
		minn = min(minn,query(mp[r[i]] - 1) - query(mp[l[i]] - 1));
	}
	//统计答案 用[l,r)的区间和表示某个救生员单独存在的时间
    //即将其解雇后少掉的覆盖长度
	memset(c,0,sizeof(c));//再初始化树状数组
	now = 0;
	for (int i = 1 ; i <= cnt ; i++){
		now += d[i];
		if (now > 0) Modify(i,rev[i+1]-rev[i]);
        //或者先int Sum 再直接if（now > 0) Sum += rev[i+1] - rev[i];
	}
	int Sum = query(cnt);
    //总时间下的覆盖长度为有救生员的时间长度
    //注意：这一步可以O(n)直接统计，不需要树状数组
    //这里用了树状数组随便卖个萌
	cout << Sum - minn << endl;//答案输出
	return 0;
}
```



---

## 作者：俺是小程 (赞：4)

没必要用线段树，有线性方法。   
首先，一个都不开除时的总时间是很好求出来的。   
考虑炒掉一个救生员对总时间的影响。很明显，假如这个救生员的工作时间刚好被另一个救生员所包含，那开掉他肯定最优。   
假如没有包含的情况， 那么我们肯定要开掉**独立工作时间**最短的那个救生员。   
至于每个救生员的**独立工作时间**怎么求， 首先给左端点排个序， 然后建议自己试一试时间线段之间的几种关系， 观察当前救生员对前一个救生员**独立工作时间**的影响就可以了。   
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 20;
inline int read()
{
	int x = 0; char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int N;
struct Seg
{
	int l, r, t;
	bool operator <(const Seg &rhs) const{
		return l < rhs.l;
	}
}cow[MAXN];
 
int main()
{
	//freopen("p4188.in", "r", stdin);
	cin>>N;
	for(int i = 1; i <= N; i++){
		int l = read(), r = read();
		cow[i] = (Seg){l, r, r - l};
	}
	sort(cow + 1, cow + N + 1);
	
	int len = 0, p = 0; bool flag = false;
	for(int i = 1; i <= N; i++){
		if(cow[i].r <= p) flag = true;
		else {
			len += min(cow[i].r - cow[i].l, cow[i].r - p);
			cow[i].t = min(cow[i].r - p, cow[i].r - cow[i].l);
			if(i > 1 && cow[i].l < p) cow[i - 1].t -= (p - cow[i].l); 
			p = cow[i].r;
		}
	}
	if(flag) cout<<len<<endl;
	else{
		int del = (1 << 29);
		for(int i = 1; i <= N; i++) del = min(del, cow[i].t);
		cout<<len - del<<endl;
	}
	return 0;
}

```

---

## 作者：qhy_ (赞：3)

我们可以先把覆盖面积求出来，再减去最小的单独覆盖区就可以了

一开始我是这样写的：
```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

int num[kMaxN];
int n, sum, ans = 1e9;
struct node {
  int l, r;
} cow[kMaxN];

bool cmp(node x, node y) {
  return x.l == y.l ? x.r < y.r : x.l < y.l;
}

int min(int x, int y) {
  return x < y ? x : y;
}

int main() {
  ios_base::sync_with_stdio(NULL);
  cin.tie(nullptr), cout.tie(nullptr);

  cin >> n;
  cow[n].l = 1e9;
  for (int i = 0; i < n; i++) {
    cin >> cow[i].l >> cow[i].r;
  }
  sort(cow, cow + n, cmp);
  for (int i = 0; i < n; i++) {
    sum += min(cow[i + 1].l, cow[i].r) - cow[i].l;
    if (min(cow[i].r, cow[i + 1].l) - max(cow[i - 1].r, cow[i].r) < ans) {
      ans = min(min(cow[i].r, cow[i + 1].l) - max(cow[i - 1].r, cow[i].l), ans);
    }
  }
  cout << sum - ans << endl;
  return 0;
}
```
但是可能会出错，因为在形如这种的情况下：
![](https://cdn.luogu.com.cn/upload/image_hosting/pujlxibg.png)
它只会算这一部分：
![](https://cdn.luogu.com.cn/upload/image_hosting/5vc4ftdp.png)
很明显，会少算很多

于是我们可以把右边界比前一个右边界短的的区间的右区间拉伸到和上一个一样长，就变成了：
![](https://cdn.luogu.com.cn/upload/image_hosting/0bcqgi8y.png)
这样就可以好好算了。

当然，如果遇到被拉伸过的区间可以直接解雇它，因为不会对总时长有影响。
### CODE

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

int num[kMaxN];
int n, sum, ans = 1e9;
struct node {
  int l, r;
} cow[kMaxN];

bool cmp(node x, node y) {
  return x.l == y.l ? x.r < y.r : x.l < y.l;
}

int min(int x, int y) {
  return x < y ? x : y;
}

int main() {
  cin >> n;
  cow[n].l = 1e9;
  for (int i = 0; i < n; i++) {
    cin >> cow[i].l >> cow[i].r;
  }
  sort(cow, cow + n, cmp);          \\按左边界排序
  for (int i = 0; i < n; i++) {
    if (cow[i].r <= cow[i - 1].r) {
      cow[i].r = cow[i - 1].r;
    }
    sum += min(cow[i + 1].l, cow[i].r) - cow[i].l;
  }
  for (int i = 0; i < n; i++) {
    if (cow[i].r <= cow[i - 1].r) {
      ans = 0;
      break;
    }
    if (min(cow[i].r, cow[i + 1].l) - max(cow[i - 1].r, cow[i].r) < ans) {
      ans = min(min(cow[i].r, cow[i + 1].l) - max(cow[i - 1].r, cow[i].l), ans);
    }
  }
  cout << sum - ans << endl;
  return 0;
}
```

---

## 作者：SUNCHAOYI (赞：2)

**算法：** 贪心   
**时间复杂度：**$O(n)$  
**具体方法：**

按起始时间从小到大排序，$a,b$ 两段线段就只会出现三种情况：$a$  与 $b$ 不重合；$a$ 与 $b$ 有交集；$a$ 包含$b$。然后就可以算出这些数据所能组成的最大覆盖单位长度：用一层循环，两两比较，若不重合，直接加整段；有重合，加未重合的部分；包含，不用再处理了，答案并没有增加。再仔细分析，设每一次输入的那组数据，若使答案增加，就设为有效输入；若无增加，即是包含关系，设为无效输入。

若有效输入的数量 $\le$ 数据总数 $n - 1$，那么说明肯定有无效输入，那么只要减去一个无效输入，答案一定是最优解，即直接输出最大覆盖的单位长度。否则说明所有输入都是有效输入，则需再循环一遍，每次去掉一个数据：若重合，去掉不重合的部分；不重合，去掉整段。然后得出的答案去最大值输出即可。

------------

```
#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;
const int MAX = 100000;
struct node
{
    ll st,ed,t;
}a[MAX];
bool cmp(node x,node y)
{
    if(x.st == y.st) return x.ed > y.ed;
    else return x.st < y.st;
}
int main() 
{
    int n;ll _min = 0x3f3f3f3f;
    scanf("%d",&n);
    for(int i = 0;i < n;i++)
    {
        scanf("%lld%lld",&a[i].st,&a[i].ed);
        a[i].t = a[i].ed - a[i].st;
        _min = min(a[i].t,_min);
    }
    sort(a,a + n,cmp);
    ll k = 0,f = -1,q = 1;
    for(int i = 0;i < n;i++)
    {
        if(f == -1)
        {
            k += a[i].t;
            f = a[i].ed;
        }
        else if(f > a[i].ed) continue;
        else if(f > a[i].st)
        {
            k += a[i].ed - f;
            q++;
            f = a[i].ed;
        }
        else
        {
            q++;
            k += a[i].t;
            f = a[i].ed;
        }
    }
    if(q <= n - 1)
    {
        printf("%d\n",k);
        return 0;
    }
    ll ans = -1,m = k,fs = -1,fd = -1;
    for(int i = 0;i < n;i++)
    {
        k = m;
        if(i == n - 1)
        {
            if(a[i].ed <= fd && a[i].st >= fs)continue;
            if(a[i - 1].ed > a[i].st) k -= a[i].ed - fd;
            else k -= a[i].ed - a[i].st;
        }
        else
        {
            if(i == 0)
            {
                if(a[i].ed > a[i + 1].st) k -= a[i + 1].st - a[i].st;
                else k -= a[i].ed - a[i].st;
                fs = a[i].st;fd = a[i].ed;
            }
            else
            {
                if(a[i].ed > a[i + 1].st && a[i - 1].ed > a[i].st)
                {
                    if(a[i].ed <= fd && a[i].st >= fs)continue;
                    k -= a[i + 1].st - a[i - 1].ed;
                    fd = max(a[i + 1].st,fd);
                    fs = min(a[i - 1].ed,fs);
                }
                else if(a[i].ed > a[i + 1].st && !(a[i - 1].ed > a[i].st))
                {
                    if(a[i].ed <= fd && a[i].st >= fs)continue;
                    k -= a[i + 1].st - a[i].st;
                    fd = max(a[i + 1].st,fd);
                }
                else if(!(a[i].ed > a[i + 1].st) && a[i - 1].ed > a[i].st)
                {
                    if(a[i].ed <= fd && a[i].st >= fs)continue;
                    k -= a[i].ed - a[i - 1].ed;
                    fs = min(a[i - 1].ed,fs);
                }
                else
                {
                    if(a[i].ed <= fd && a[i].st >= fs)continue;
                    k -= a[i].ed - a[i].st;
                    fs = a[i].st;fd = a[i].ed;
                }
            }
        }
        ans = max(ans,k);
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：zmnjkl (赞：1)

本人的第三篇题解，写的不好请指出哦~


------------
### 题意：

一共 $N$ 个区间，每个区间的起点和终点在 $0$ 到 $10^9$ 之间。要求删除一个区间后求出整体覆盖区间最长的方案。

### 分析：

这道题其实是个贪心啦，用一个简单的结构体数组按照起点排序。排完序遍历每个区间，分类算出这个区间和上个区间重叠的部分。最后用总和去减去一个区间，查看最终最大的可能。

### 思路：

对于每个区间都和上一个区间做比较。

- 如果这个区间的终点小于上一个元素的终点，则这个区间被上个区间完全包含。因为这个区间完全被包含了，所以删了它是最值的（删了不会对原区间覆盖值有任何影响）。

- 如果当前区间的起点比上一个区间的终点小（有交集），则 $ans$ 加上当前区间多出来的值（当前终点减去上一个终点），并将这个值推进队列。当然这里同时要把重叠部分一起推进队列（上一个终点减去当前起点）。这个重叠部分是删了上一个元素后多删了的部分，也就是说假设删了上一个元素，我们要把这个重叠部分给加回来。

- 如果当前区间和上一个区间没有交集，则 $ans$ 加上这个区间的大小。

- **不存在当前起点比上一个起点更早的情况！** 按照起点排序能直接避免这个可能。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,mx;
struct Node{
	int s,t;
}num[114514],p;//num存所有区间，p存上一个区间
bool cmp(Node a,Node b){
	return a.s<b.s;//按照起点从小到大排序
}
bool flag;
int main(){
	cin >> n;
	for(int i=0;i<n;i++)cin >> num[i].s >> num[i].t;
	sort(num,num+n,cmp);
	queue<Node>q;//队列储存删除每个元素对整体覆盖区间影响的值
	for(int i=0;i<n;i++){
		if(num[i].t<=p.t)flag=1;//如果中间有个值被覆盖了，则最后直接输出答案
		else{
			if(num[i].s>p.t){//如果当前区间和上个区间没有交集
				ans+=num[i].t-num[i].s;//直接加上这个区间的大小并推进队列
				q.push({num[i].t-num[i].s,0});
			}else if(num[i].s<=p.t){
				ans+=num[i].t-p.t;//如果有交集，则加上后面多余的部分
				q.push({num[i].t-p.t,p.t-num[i].s});//这里同时存入当前区间起点和上个区间终点的差值
			}
			p=num[i];
		}
	}
	if(flag){
		cout << ans;//直接输出答案并退出
		exit(0);
	}
	while(!q.empty()){
		Node t=q.front();
		q.pop();
		mx=max(mx,ans-t.s+q.front().t);//这里如果删除了某个元素，则要加上多删除的重叠部分
	}
	cout << mx;
}

```


---

## 作者：信守天下 (赞：1)

## [洛谷传送门](https://www.luogu.com.cn/problem/P4188)
## 思路
先回顾一下如何求所有区间的覆盖长度。

可以先将所有区间按照左边界排序，然后按顺序处理每个区间。

同时维护已覆盖的右边界。每次对当前区间新增的长度进行累加，并更新右边界。

现在要删掉一个区间。

如果枚举每个要删掉的区间，再重新计算覆盖长度，效率太低。

我们应该考虑删掉一个区间后，覆盖总长的变化，即只被删掉的区间覆盖的长度。

由于⼀个区间可能包含多个区间。

这样就导致了只被该区间覆盖的区域是多个不连续的段，统计总⻓较为麻烦。

但仔细思考，我们的目标是求出最小单独覆盖长度。

如果出现这种情况，我们必然可以选取被包含的区间。

它的单独覆盖长度为 $0$ ，从而直接得到最优答案。

此外，如果⼀个区间相邻的两个区间由交集。

那么它也是会被完全覆盖的，可以删除且覆盖总⻓不减。

我们对所有区间进行一遍扫描，就能检查出上述两种情况。

如果上述两种情况都不存在，说明一个区间最多只会跟相邻两个区间有交。

那么它的单独覆盖⻓度就可以直接计算出来了。

⽤⾃身的覆盖⻓度减去与相邻区间交的⻓度即可。
## 复杂度分析
### 时间复杂度
排序 $O(N \log N)$ 。

求覆盖总⻓ $O(N)$ 。

求每个区间单独覆盖长度 $O(N)$ 。

总时间复杂度为 $O(N \log N)$ 。
### 空间复杂度
记录区间 $O(N)$ 。
## $code$
~~~cpp
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 2;

struct E {
  int l, r;
  bool operator<(const E &e) const {  // 按照左边界排序
    return l < e.l;
  }
} e[kMaxN];
int n, t;

int F() {                                                    // 计算一只奶牛独占的最短时间
  int v = 1e9;                                               // 初始化最值
  e[0].r = e[1].l, e[n + 1] = {e[n].r, 1 << 30};             // 构造左右边界区间
  for (int i = 1; i <= n; i++) {                             // 逐个处理区间
    if (e[i].r <= e[i - 1].r || e[i + 1].l <= e[i - 1].r) {  // 被上个区间包含，或相邻区间接上了
      return 0;
    }
    v = min(v, min(e[i + 1].l, e[i].r) - e[i - 1].r);  // 去除当前区间重叠的部分
  }
  return v;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].l >> e[i].r;
  }

  sort(e + 1, e + 1 + n);

  for (int i = 1, r = e[1].l; i <= n; i++) {  // 逐个区间累加新增长度
    t += max(e[i].r - max(e[i].l, r), 0);     // 从已覆盖右边界开始计算新长度
    r = max(r, e[i].r);                       // 更新已覆盖右边界
  }
  cout << t - F();
  return 0;
}
~~~

---

## 作者：曹老师 (赞：1)

~~写了一上午~~

[Blog传送门QwQ](https://blog.csdn.net/qq_36316033/article/details/79684395)

**知识点：线段树**

所以其实思路应该和扫描线一样看线段覆盖

然后每次枚举删除哪个

线段树更新一下答案比较大小

注意扫描线的时候被覆盖的标记是不可以被下放的

而是应该统计下被覆盖的次数

如果被覆盖的次数边成0了

那么我被覆盖的长度就应该是由下面更新上来

**注意：如果是底层的话，那就不能上传了，下传会运行超限(当然不排除你想开8倍的内存)）**


对于时间的改变就要注意一点，本题是时间段的覆盖而不是时间点的覆盖所以要把所有点变成段，所以就需要-1

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define INF 2147483640
#define MOD 100000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
using namespace std;
const int L1=1e7+5,L2=1e7+5;
struct node{
	int l,r,cov,len;
};
node p[4*L2];
int n,l[2*L2],r[2*L2],q[2*L2],tot,cnt,ans;
void build(int num,int l,int r)
{
	p[num].l=l;
	p[num].r=r;
	p[num].len=0;
	if(l==r)
		return ;
	int mid=(l+r)>>1;
	build(num<<1,l,mid);
	build((num<<1)|1,mid+1,r);
}
void update(int num,int l,int r,int v)
{
	if(p[num].l==l&&p[num].r==r)
	{
		p[num].cov+=v;
		if(p[num].cov==1)
			p[num].len=q[p[num].r+1]-q[p[num].l];
		if(!p[num].cov)
			if(l==r)
				p[num].len=0;
		else
			p[num].len=p[num<<1].len+p[(num<<1)|1].len;
		return;
	}
	int mid=(p[num].l+p[num].r)>>1;
    if(r<=mid)
		update(num<<1,l,r,v);
	else
		if(l>mid)
			update((num<<1)|1,l,r,v);  
    else
	{
		update(num<<1,l,mid,v);
		update((num<<1)|1,mid+1,r,v);  	
	}
 	if(!p[num].cov)
	 	p[num].len=p[num<<1].len+p[(num<<1)|1].len;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		q[++tot]=l[i];
		q[++tot]=r[i];
	}
	sort(q+1,q+tot+1);
	cnt=unique(q+1,q+tot+1)-q-1;
	build(1,1,cnt-1);
	for(int i=1;i<=n;i++)
	{
		l[i]=lower_bound(q+1,q+tot+1,l[i])-q;
		r[i]=lower_bound(q+1,q+cnt+1,r[i])-q-1;
		update(1,l[i],r[i],1);
	}
	for(int i=1;i<=n;i++)
	{
		update(1,l[i],r[i],-1);
		ans=max(ans,p[1].len);
		update(1,l[i],r[i],1);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：1)

# 题目大意

有 $n$ 个线段 $[st_i,ed_i]$ 。现在询问去掉一条线段后，剩余线段可以覆盖的最大长度。

# 题目分析

区间覆盖类问题的变种。

我们先正常按左端点升序、右端点降序排序，求出此时不考虑去掉一个线段时能覆盖的最大长度，记为 $ans_1$。

然后我们就要求出删掉一条线段的最小代价。求解方法与上面一个类似，遍历所有线段，将删掉一个线段而导致减少的距离求出来，取出最小值即可。记最小值为 $ans_2$。

则最后答案为 $ans_1-ans_2$。

# 代码

```cpp
// Problem: P4188 [USACO18JAN]Lifeguards S
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4188
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Date:2022-06-24 10:08
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	#ifndef ONLINE_JUDGE
	#define getc getchar
	#endif
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getc();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getc();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getc();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int INF = 0x3f3f3f3f;
const int N = 1e5 + 5;
struct Node {
	int st,ed;
} node[N];
int n;
int main(void) {
	n = read();
	for (register int i = 1;i <= n; ++ i) {
		node[i].st = read(),node[i].ed = read();
	}
	std::sort(node + 1,node + n + 1,[&](Node x,Node y)mutable {
		return x.st != y.st ? x.st < y.st : x.ed > y.ed;
	});
	int R = 0,ans = 0;
	for (register int i = 1;i <= n; ++ i) {
		if (R < node[i].ed) {
			ans += node[i].ed - std::max(node[i].st,R);
			R = node[i].ed;
		}
	}
	R = 0;
	int tmp = INF;
	node[n + 1].st = node[n].ed;
	for (register int i = 1;i <= n; ++ i) {
		if (R < node[i].ed) {
			int t = std::min(node[i + 1].st,node[i].ed) - std::max(node[i].st,R);
			R = node[i].ed;
			tmp = std::min(tmp,t);
		} else {
			tmp = 0;
		}
	}
	printf("%d\n",ans - std::max(tmp,0));
	
	return 0;
}
```

---

## 作者：RainFestival (赞：1)

**警告：** 这个方法不一定可以通过此题，可能会**超过时空限制**。笔者为了能卡进时空限制，用了一些手段，可能会导致**答案错误**。如果您想要对拍的话，请**不要**使用这份代码。

题意：有 $n$ 个线段，你需要删掉一个线段，使得剩下的线段的并集最大，问这个最大值是多少。

首先我们先把删掉一个转化成保留 $n-1$ 个。

我们发现，设 $f(s)$ 为保留 $s$ 条线段的并集最大值，那么 $f(s)$ 是凸的。

然后我们需要求 $f(n-1)$，所以我们可以考虑 wqs 二分。

每次二分惩罚 $p$，问题转化为选择一条线段需要 $p$ 的代价的最大方案。

我们考虑使用动态规划来解决这个问题，记 $dp_i$ 为考虑了前 $i$ 条线段，一定要选择第 $i$ 条线段的答案。

我们先把所有线段按照左端点排序。

对于一条线段 $i$ 的左右端点是 $l,r$，考虑上一条线段 $j$ 的右端点 $r'$。

+ 如果 $r'<l$，那么这一条线段的对答案的贡献就是 $r-l+1$，即 $dp_i\gets \max(dp_i,dp_j+(r-l+1)-p)$。

+ 如果 $l\le r'\le r$，那么这一条线段的贡献为 $r-r'$，即 $dp_i\gets \max(dp_i,dp_j+(r-r')-p)$。

+ 如果 $r'>r$，那么上一条线段一定包含了这一条，这一条线段一定没有用。

对于第一种情况，因为左端点依次递增，所以，我们把处理过的线段右端点处的答案存进数组里面就可以查询啦。

具体地，我们记 $val_i$ 为右端点 $\le i$ 的答案。每次加入线段的时候，用这一条线段更新 $val_r$。这个时候，$val_i$ 指右端点 $=i$ 的答案。当左端点更新到 $l$ 时，$i\le l-1$ 的 $val_i$ 的答案已经更新完毕，于是把 $i\le l-1$ 的 $val_i$ 更新一下，变成成右端点 $\le i$ 的答案就可以啦，也就是 $val_i\gets \max(val_{i-1},val_i)$。

从而第一种情况的答案 $s_1$ 是 $val_{l-1}-p$。

对于第二种情况，我们需要利用线段树就可以解决啦。

具体地，我们记 $a_k$ 为上一条线段的右端点为 $k$ 的最大答案。

考虑一条线段 $i$，记它的左右端点为 $l,r$，$dp_i=\max\limits_{k=l}^{r} a_k-k+r$。

我们发现 $+r$ 这一项对于每个 $i$ 是固定的，非常容易处理。

我们发现 $-k$ 这一项和 $k$ 有关，不好处理。于是我们记 $b_k=a_k-k$，于是 $\max\limits_{k=l}^{r} a_k-k+r=\max\limits_{k=l}^{r} b_k+r$，然后把 $b_k$ 存进线段树中查询就可以啦。

从而第二种情况的答案 $s_2$ 是 $(\max\limits_{k=l}^{r} b_k)+r-p$。

所以 $dp_i=\max(s_1,s_2)$。

在记录每一个 $dp$ 值的时候，我们顺便记录达到这个 $dp$ 值的方案需要选择 $c_i$ 条线段，这个很容易在取 $\max$ 的时候记录下来。

如果达到最大的 $dp$ 值需要的线段个数 $<k$，我们就加大惩罚 $p$，否则减小。

由于惩罚是个实数，我们需要一个合适的 $eps$，如果太大，就会得到错误的答案，因为我们做了错误的决策，如果太小，二分次数太多，就会超过时间限制。

所以我们手动调整 $eps$，多交几次就过啦。

卡常小技巧：先对所有的区间端点进行离散化，然后就不用动态开点线段树啦。

时间复杂度 $\mathcal{O(n\log n\log V)}$，其中 $\mathcal{V}$ 是值域；空间复杂度 $\mathcal{O(n)}$。

代码如下：

```cpp
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm>
#include<unordered_map>
#define maxn 205000
#define eps 0.5
struct sgt
{
	struct node
	{
		std::pair<double,int> s;
	};
	node a[530005];
	void pushup(int k)
	{
		a[k].s=std::max(a[k*2].s,a[k*2+1].s);
	}
	void update(int k,int x,std::pair<double,int> w,int l,int r)
	{
		if (l==r) return a[k].s=std::max(a[k].s,w),void();
		int mid=(l+r)/2;
		if (x<=mid) update(k*2,x,w,l,mid);
		if (mid<x) update(k*2+1,x,w,mid+1,r);
		pushup(k); 
	}
	std::pair<double,int> ask(int k,int x,int y,int l,int r)
	{
		if (a[k].s.second==-1000000000) return std::make_pair(-100000000000000.0,-100000000);
		if (x<=l&&r<=y) return a[k].s;
		int mid=(l+r)/2;
		std::pair<double,int> s=std::make_pair(-100000000000000.0,-100000000);
		if (x<=mid) s=std::max(s,ask(k*2,x,y,l,mid));
		if (mid<y) s=std::max(s,ask(k*2+1,x,y,mid+1,r));
		return s;
	}
	void pre()
	{
		clear();
	}
	void clear()
	{
		for (int i=1;i<=530000;i++) a[i].s=std::make_pair(-1000000000000000.0,-1000000000);
	}
};
struct node
{
	int l,r;
};
sgt t;
int n,k,maxl=0,g[200005],cnt,ncnt=0;
node f[100005];
std::pair<double,int> val[205005],dp[100005];
std::unordered_map<int,int> mp;
std::pair<double,int> calc(double k)
{
	t.clear();
	int now=0;
	for (int i=0;i<=205000;i++) val[i]=std::make_pair(-1000000000000000.0,-1000000000);
	val[0]=std::make_pair(0.0,0);
	t.update(1,0,std::make_pair(0.0,0),0,maxn);
	for (int i=1;i<=n;i++)
	{
		while (now<f[i].l-1) ++now,val[now]=std::max(val[now-1],val[now]);
		std::pair<double,int> s1=val[f[i].l-1];
		std::pair<double,int> s2=t.ask(1,f[i].l,f[i].r,0,maxn);
		s1.first=s1.first+(g[f[i].r]-g[f[i].l]+1)-k,s2.first=s2.first+g[f[i].r]-k;
		++s1.second,++s2.second;
		dp[i]=std::max(s1,s2);
		val[f[i].r]=std::max(val[f[i].r],dp[i]);
		t.update(1,f[i].r,std::make_pair(dp[i].first-g[f[i].r],dp[i].second),0,maxn);
	}
	std::pair<double,int> ans=std::make_pair(-1000000000000000.0,-1000000000);
	for (int i=1;i<=n;i++) if (dp[i]>ans) ans=dp[i];
	return ans;
}
double bs(double l,double r)
{
	if (r-l<eps) return l;
	double mid=l+(r-l)/2.0;
	int s=calc(mid).second;
	if (s==k) return mid;
	if (k<s) return bs(mid,r);
	return bs(l,mid);
}
int cmp(node x,node y){return x.l<y.l;}
int main()
{
	t.pre();
	scanf("%d",&n);
	k=1;
	k=n-k;
	int ss[200005];
	for (int i=1;i<=n;i++) scanf("%d%d",&f[i].l,&f[i].r),--f[i].r,ss[++ncnt]=f[i].l,ss[++ncnt]=f[i].r;
	for (int i=1;i<=n;i++) maxl=std::max(maxl,f[i].r-f[i].l+1);
	std::sort(ss+1,ss+ncnt+1);
	for (int i=1;i<=ncnt;i++)
	{
		if (ss[i]==ss[i-1]&&i!=1) continue;
		mp[ss[i]]=++cnt;
		g[cnt]=ss[i];
	}
	for (int i=1;i<=n;i++) f[i].l=mp[f[i].l],f[i].r=mp[f[i].r];
	std::sort(f+1,f+n+1,cmp);
	double s=bs(0,maxl);
	std::pair<double,int> sta=calc(s);
	printf("%lld\n",(long long)(sta.first+s*k+0.5));
	return 0;
}
```
[这里](https://www.luogu.com.cn/record/70463909) 是评测记录。

感谢您的阅读。


---

## 作者：linyinuo2008 (赞：0)

注：我这里参考了[俺是小程](https://www.luogu.com.cn/user/57705)大佬的题解并加以了整理。

这题完全没必要用线段树，有线性的正确做法。

首先，我们可以很清楚的看到这是一个区间覆盖问题，通常都会想到用结构体与一些神奇的策略与排序来完成，这道题也不例外。

我们可以依次考虑除去每一段区间对总计划的影响。显而易见的是，一段区间被其它区间包含的越多去掉它收益越大。我们对区间左端点排个序，来依次看一看每一段区间对整体的影响（感性理解一下）。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=100005;

struct Seg
{
	int t,l,r;
}a[N];

bool cmp(Seg p,Seg q)
{
	if(p.l!=q.l)
		return p.l<q.l;
	return p.r<q.r;
}

int n;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].l>>a[i].r;
		a[i].t=a[i].r-a[i].l;
	}
	sort(a+1,a+n+1,cmp);
	int len=0,p=0,flag=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].r<=p) flag=1;
		else
		{
			len+=min(a[i].r-a[i].l,a[i].r-p);
			a[i].t=min(a[i].r-p,a[i].r-a[i].l);
			if(i>=2&&a[i].l<p)
				a[i-1].t-=p-a[i].l;
			p=a[i].r;
		}
	}
	if(flag) cout<<len;
	else
	{
		int d=(1<<30);
		for(int i=1;i<=n;i++)
			d=min(d,a[i].t);
		cout<<len-d;
	}
	return 0;
}
```

**若有错误，欢迎指出！**

---

## 作者：UperFicial (赞：0)

- 最直接的想法是，算出总覆盖长度，然后枚举去除每一条线段的贡献，所以这个问题就被分为了两个子问题。

- 对于第一个问题，考虑将线段按左端点升序排序，然后枚举每一段区间 $[ll,rr]$，记录右端点的最大值 $r$，如果目前这个线段右端点被覆盖过去，则这个线段没有贡献，因为线段的左端点已经按升序排列了。而如果 $r$ 没有覆盖掉这个区间右端点 $rr$ 的话，这个线段的贡献为 $rr-\max(ll,r)$。
- 再来看第二个问题，我们的目标是让第二个问题的答案尽量小，才能保证最终答案尽可能大。如果枚举每一个被删掉的区间，然后再算总贡献的话，效率是 $\mathcal{O}(n^2)$ 的，太拉了。考虑线性的做法。如果第 $i$ 个区间被第 $i-1$ 个区间全部包含，那么，删去第 $i$ 个区间后，总覆盖长度是不变的，也就是总覆盖长度减去了 $0$，所以这样答案为 $0$。再如果，第 $i+1$ 个区间和第 $i-1$ 个区间首尾相连，考虑第 $i$ 个区间的位置关系，如果第 $i$ 个区间包含了第 $i+1$ 个区间，则可以删去第 $i+1$ 个区间，答案为 $0$，而若第 $i$ 个区间，形象的说，被加在 $i-1$ 和 $i+1$ 这两个区间中间，则删去 $i$，答案也是 $0$。

- 对于余下的情况，第 $i$ 条线段的贡献就不是 $0$ 了。考虑 $i$ 真实的左右端点，右端点可能被 $i+1$ 的左端点覆盖掉，所以右端点为 $\min(a[i+1].l,a[i].r)$，同理，左端点也可能被 $i-1$ 的右端点覆盖掉，所以左端点为 $\max(a[i-1].r,a[i].l)$，这里两个作差，得到的是 $i$ 的单点覆盖。所有的 $i$ 取贡献最小的即可。

- PS：这道题做了两天，吐了吐了。

---

## 作者：Parat_rooper (赞：0)

# 解题思路：
这题很容易想到转化可以为线段覆盖问题，即将起始时间设为左端点，结束时间设为右端点，于是本题就转化为了求最短的被一条线段单独覆盖的区间长度。

但要考虑到两种特殊情况，可能会有一条线段被另一条或多条线段包含，那么这时肯定删掉这条线段最优，不会产生任何影响，最短单独覆盖长度为 $0$ 。

所以答案就是用总覆盖长度减去之前所算的长度。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 1e6 + 10;

int n, minn = (1e9 + 1), sum;

struct q {
  int l, r;
}a[kMaxN];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].l >> a[i].r;
  }
  sort (a + 1, a + n + 1, [](q i, q j) { return i.l < j.l;});
  a[0].r = a[1].l, a[n + 1] = {a[n].r, 1 << 30};//设定边界
  for (int i = 1, kl = a[1].l; i <= n; i++) {
    if (a[i].r <= a[i - 1].r || a[i + 1].l <= a[i - 1].r) {
      minn = 0;//如果被之前一条线段包括或被前后两条线段接起来，minn就为0
    } else {//否则就计算最短单独覆盖长度
      int ml = min(a[i + 1].l, a[i].r) - max(a[i - 1].r, a[i].l);
      minn = min(minn, ml);
    }
    sum += max(a[i].r - max(a[i].l, kl), 0);//计算覆盖总长
    kl = max(kl, a[i].r);
  }
  cout << (sum - minn);
  return 0;
}
```
完结撒花。

---

## 作者：tribool4_in (赞：0)

时间复杂度是可以线性的。

如果开除一头牛，显然如果它的工作时间刚好被另一个牛所包含，那开除它肯定最优。否则，一定要开除**独立工作时间最短**的那头牛。

将每头牛工作时间段的左端点排序，遍历所有牛，记录当前（即上一个）的最右端点为 ```r```，总工作时间为 ```tot```。

考虑几种情况，首先如果当前的右端点还不大于 ```r```，说明它肯定已经被包含了；否则考虑更新当前牛的独立工作时间，显然为 ```min(当前 r - 当前 l, 当前 r - r)```，将当前牛的独立工作时间更新并累加 ```tot```。但要注意，如果当前牛的工作时间段与上一头有重合，还需更改上一头牛。

最后如果有牛被包含则直接输出 ```tot```，否则直接遍历一遍取最小值即可。

代码：

```cpp
// Code By WLS
#include <bits/stdc++.h>
const int N = 1e5 + 5;
using namespace std;
struct node {
	int l, r, t;
	bool operator < (node rhs) const {
		return l < rhs.l;
	}
} cow[N];
int n, tot, r, hide;
signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &cow[i].l, &cow[i].r), cow[i].t = cow[i].r - cow[i].l;
	sort(cow + 1, cow + n + 1);
	for (int i = 1; i <= n; i++) {
		if (cow[i].r > r) {
			int tmp = min(cow[i].r - cow[i].l, cow[i].r - r);
			tot += tmp;
			cow[i].t = tmp;
			if (i > 1 && r > cow[i].l) cow[i - 1].t -= (r - cow[i].l);
			r = cow[i].r;
		} else hide = 1;
	}
	if (hide) printf("%d\n", tot);
	else {
		int minn = 0x7fffffff;
		for (int i = 1; i <= n; i++) {
			minn = min(minn, cow[i].t);
		}
		printf("%d\n", tot - minn);
	}
	return 0;
}
```

---

## 作者：Saber_Master (赞：0)

[[USACO18JAN]Lifeguards S](https://www.luogu.com.cn/problem/P4188)

最多去掉一个人

也就是在原来总的贡献上减去那个人独特的贡献

也就是那个人的区间内只被覆盖一次的子区间

先离散差分前缀和搞出每段时间点被覆盖了几次

然后线段树维护区间和就行，贡献只算覆盖次数为$1$的

然后扫描每个人减去最小的消耗的贡献

详见代码

$O(n\log n)$

```cpp
const ll N=1e5+5;

ll n;
ll lsh[N<<1], h; 
ll st[N], ed[N];
ll d[N<<1];
ll cnt[N<<1];

namespace seg{
	ll dat[N<<3];
	
	inline void build(ll p, ll l, ll r){
		if (l==r) return (void)(cnt[l]==1?dat[p]=d[l]:0);
		ll mid=l+r>>1;
		build(p<<1, l, mid); build(p<<1|1, mid+1, r);
		dat[p]=dat[p<<1]+dat[p<<1|1];
	}
	
	inline ll query(ll p, ll l, ll r, ll u, ll v){
		if (u<=l && r<=v) return dat[p];
		ll mid=l+r>>1, res=0;
		if (u<=mid) res+=query(p<<1, l, mid, u, v);
		if (v>mid) res+=query(p<<1|1, mid+1, r, u, v);
		return res;
	}
}

ll res;
int main(){
	read(n);
	for (R ll i=1; i<=n; i++){
		read(st[i]); read(ed[i]);
		lsh[++h]=st[i]; lsh[++h]=ed[i];
	}
	sort(lsh+1, lsh+h+1);
	h=unique(lsh+1, lsh+h+1)-lsh-1;
	for (R ll i=1; i<=h; i++) d[i]=lsh[i]-lsh[i-1];
	for (R ll i=1; i<=n; i++){
		st[i]=lower_bound(lsh+1, lsh+h+1, st[i])-lsh;
		ed[i]=lower_bound(lsh+1, lsh+h+1, ed[i])-lsh;
		++cnt[st[i]+1]; --cnt[ed[i]+1];
	}
	for (R ll i=1; i<=h; i++){
		cnt[i]+=cnt[i-1];
		if (cnt[i]>0) res+=d[i];
	}
	seg::build(1, 1, h);
	ll sum=0x7fffffff;
	for (R ll i=1; i<=n; i++){
		chkmin(sum, seg::query(1, 1, h, st[i]+1, ed[i]));
	}
	writeln(res-sum);
}
```


---

## 作者：elijahqi (赞：0)

 http://www.elijahqi.win/2018/02/02/luogu4188-usaco18janlifeguards-s/
 http://blog.csdn.net/elijahqi/article/details/79243018
 这可能是非常辣鸡的题解 因为做法超级麻烦
题意翻译

FJ为他的奶牛们建造了一个游泳池，FJ认为这将有助于他们放松身心以及生产更多牛奶。

为了确保奶牛们的安全，FJ雇佣了N头牛，作为泳池的救生员，每一个救生员在一天内都会有一定的事情，并且这些事情都会覆盖一天内的一段时间。为了简单起见，泳池从时间t=0时开门，直到时间t=1000000000关门，所以每个事情都可以用两个整数来描述，给出奶牛救生员开始以及结束事情的时间。例如，一个救生员在时间t=4时开始事情并且在时间t=7时结束事情，那么这件事情就覆盖了3个单位时间。（注意：结束时间是“点”的时间）

不幸的是，FJ雇佣了多于一名的救生员，但他没有足够的资金来雇佣这些救生员。因此他必须解雇一名救生员，求可以覆盖剩余救生员的轮班时间的最大总量是多少？如果当时至少有一名救生员的事情已经开始，则这个时段被覆盖。

输入格式

输入的第一行包括一个整数N（1≤N≤100000）。接下来N行中，每行告诉了我们一个救生员在0~10000000000范围内的开始以及结束时间。所有的结束时间都是不同的。不同的救生员的事情覆盖的时间可能会重叠。

输出格式

如果FJ解雇一名救生员仍能覆盖的最大时间。

感谢@Shan_Xian 提供的翻译
题目描述

Farmer John has opened a swimming pool for his cows, figuring it will help them relax and produce more milk.

To ensure safety, he hires

NN

N cows as lifeguards, each of which has a shift that covers some contiguous interval of time during the day. For simplicity, the pool is open from time

t=0t=0

t=0 until time

t=1,000,000,000t = 1,000,000,000

t=1,000,000,000 on a daily basis, so each shift can be described by two integers, giving the time at which a cow starts and ends her shift. For example, a lifeguard starting at time

t=4t = 4

t=4 and ending at time

t=7t = 7

t=7 covers three units of time (note that the endpoints are "points" in time).

Unfortunately, Farmer John hired 1 more lifeguard than he has the funds to support. Given that he must fire exactly one lifeguard, what is the maximum amount of time that can still be covered by the shifts of the remaining lifeguards? An interval of time is covered if at least one lifeguard is present.
输入输出格式

输入格式：

The first line of input contains

NN

N (

1≤N≤100,0001 \leq N \leq 100,000

1≤N≤100,000 ). Each of the next

NN

N lines describes a lifeguard in terms of two integers in the range

0…1,000,000,0000 \ldots 1,000,000,000

0…1,000,000,000 , giving the starting and ending point of a lifeguard's shift. All such endpoints are distinct. Shifts of different lifeguards might overlap.

输出格式：

Please write a single number, giving the maximum amount of time that can still be covered if Farmer John fires 1 lifeguard.
输入输出样例

输入样例#1： 复制

3
5 9
1 4
3 7

输出样例#1： 复制

7

给定n条线段 然后询问删除哪条使得覆盖的剩余长度最长 一开始想了个错误的方法 首先先把区间转点 然后跑线段树 每次看哪条线段被覆盖大于等于2的段数多就 选择删掉哪条 但这显然是错的

所以其实应该和扫描线一样看线段覆盖  然后每次枚举删除哪个  线段树更新一下答案比较大小

注意扫描线的时候被覆盖的标记是不可以被下放的 而是应该统计下被覆盖的次数 如果被覆盖的次数边成0了那么我被覆盖的长度就应该是由下面更新上来
```
#include<cstdio>
#include<algorithm>
#define N 220000
#define inf 0x3f3f3f3f
using namespace std;
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
inline int read(){
	int x=0,f=1;char ch=gc();
	while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=gc();}
	while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
	return x*f;
}
struct node{
	int l,r,left,right,len,cov;
}tree[N<<1],a[N];
int n,st[N],ed[N],root,num,tot,q[N],st1[N],ed1[N],ans=0;;
inline void update(int x){
	if (tree[x].cov) return;
	int l=tree[x].left,r=tree[x].right;
	tree[x].len=tree[l].len+tree[r].len;
}
inline void build(int &x,int l,int r){
	x=++num;if (l==r) {tree[x]=a[l];return;}int mid=l+r>>1;
	build(tree[x].left,l,mid);build(tree[x].right,mid+1,r);
	tree[x].l=tree[tree[x].left].l;tree[x].r=tree[tree[x].right].r;
}
inline void modify(int x,int l,int r,int l1,int r1,int v){
	if (l1<=l&&r1>=r) {tree[x].cov+=v;
		if (tree[x].cov==1) tree[x].len=tree[x].r-tree[x].l;
		if (!tree[x].cov) update(x);return;}
	int mid=l+r>>1;
	if (l1<=mid) modify(tree[x].left,l,mid,l1,r1,v);
	if (r1>mid) modify(tree[x].right,mid+1,r,l1,r1,v);update(x);
}
inline void print(int x){
	if (tree[x].left) print(tree[x].left);
	printf("%d %d %d\n",tree[x].l,tree[x].r,tree[x].len);
	if (tree[x].right) print(tree[x].right);
}
int main(){
	freopen("lifeguards.in","r",stdin);
	freopen("lifeguards.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i) st[i]=read(),ed[i]=read(),q[++tot]=st[i],q[++tot]=ed[i];sort(q+1,q+tot+1);
	int nn=unique(q+1,q+tot+1)-q-1;for (int i=1;i<nn;++i) a[i].l=q[i],a[i].r=q[i+1];build(root,1,nn-1);
	for (int i=1;i<=n;++i) st1[i]=lower_bound(q+1,q+nn+1,st[i])-q,ed1[i]=lower_bound(q+1,q+nn+1,ed[i])-q-1;
	--nn;for (int i=1;i<=n;++i) modify(root,1,nn,st1[i],ed1[i],1);//print(root),puts("dfs");	//printf("%d\n",tree[root].len);
	
	for (int i=1;i<=n;++i){
		modify(root,1,nn,st1[i],ed1[i],-1);ans=max(ans,tree[root].len);modify(root,1,nn,st1[i],ed1[i],1);
	}
	printf("%d\n",ans);
	return 0;
}


```

---

