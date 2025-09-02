# [USACO14OPEN] Fair Photography S

## 题目描述

FJ 的 N 头奶牛（2 <= N <= 100,000）站在一条长长的一维栅栏的不同位置上。第 i 头奶牛站在位置 $x_i$（范围为 0 到 1,000,000,000 的整数）上，并且要么是纯白色奶牛，要么是斑点奶牛。没有两头奶牛占据相同的位置，并且至少有一头白色奶牛。

FJ 想为县集市拍摄一张连续区间内的奶牛照片，但为了公平对待他的不同奶牛，他希望确保照片中白色奶牛和斑点奶牛的数量相等。FJ 想要确定这样一张公平照片的最大尺寸，其中照片的尺寸是照片中奶牛的最大位置和最小位置之间的差。

为了给自己更大的机会拍摄更大的照片，FJ 带了一桶油漆，他可以用来在他选择的任意一部分白色奶牛上画上斑点，有效地将它们变成斑点奶牛。请确定 FJ 可以拍摄的公平照片的最大尺寸，前提是 FJ 可以选择给一些白色奶牛涂上斑点（当然，如果他认为这样更好，他不需要给任何白色奶牛涂上斑点）。


## 说明/提示

有 5 头奶牛。其中一头是位于位置 8 的白色奶牛，依此类推。

FJ 拍摄了从位置 3 到位置 10 的奶牛照片。在这个范围内有 4 头奶牛——3 头白色和 1 头斑点——所以他需要将其中一头白色奶牛涂成斑点。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 
8 W 
11 S 
3 W 
10 W 
5 S 
```

### 输出

```
7 
```

# 题解

## 作者：Mascros (赞：12)

前缀和记录白牛数减去斑点牛数。

既然白牛可以变成斑点牛，那么**只要一段区间[l,r]内的白牛数大于等于斑点牛数且总数为偶数**，即   sum[r]-sum[l-1]>=0且(sum[r]-sum[l-1])%2==0   ,使r-l最长即可。

观察发现，**当某点i的前缀和sum[i]≥0时**，由于sum[1]一定是1或-1，那么

若i是偶数，那么sum[i]-sum[0]一定满足条件，

若i是奇数，那么sum[i]-sum[1]一定满足条件。

**当某点i的前缀和sum[i]<0时**，要找到点j (j<i)使得sum[i]-sum[j]>=0,当sum[i]-sum[j]=0时一定是最优的（因为前缀和是+1-1连续的且从0开始的）

故记录该前缀和出现的第一次位置即可，这里用map记录。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
typedef long long ll;
struct node{
	ll no;
	int w;//W=1,S=-1
}a[MAXN];
ll sum[MAXN];
map<ll,int> m;
bool cmp(node x,node y)
{
	return x.no<y.no;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	ll x;
	ll ans=0;
	char b;
	sum[0]=0;
    for(int i=1;i<=n;++i)
    {
    	cin>>x>>b;
		a[i].no=x;
        if(b=='W')
        	a[i].w=1;
        else
        	a[i].w=-1;
        
    }
    sort(a+1,a+n+1,cmp);
    m[0]=0;
    for(int i=1;i<=n;++i)
    {
		sum[i]=sum[i-1]+a[i].w;
        if(m[sum[i]]==0&&sum[i]<0)
        	m[sum[i]]=i;
		else if(sum[i]<0)
			ans=max(ans,a[i].no-a[m[sum[i]]+1].no);
		if(sum[i]%2==0&&sum[i]>=0)
			ans=max(ans,a[i].no-a[1].no);
		else if(sum[i]>=0)
			ans=max(ans,a[i].no-a[2].no);
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：ezоixx130 (赞：10)

先对输入按照P值排序，然后令W=-1 S=1，开一个F数组记录前i头牛中，白色牛减去斑点牛的数量，最后统计答案。

排序的时间复杂度为O(nlogn)，统计答案的时间是线性的，所以总的时间复杂度为O(nlogn)。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node{
    int p,st;
    friend bool operator<(const node &n1,const node &n2)
    {
        return n1.p<n2.p;
    }
}a[100001];

int n,ans,f[1000001],now;
char c;

int main()
{
    cin >> n;
    for(int i=1;i<=n;++i)
    {
        cin >> a[i].p >> c;
        if(c=='W')
            a[i].st=-1;
        else
            a[i].st=1;
    }
    sort(a+1,a+n+1);//排序
    memset(f,0x7f,sizeof(f));
    now=n;
    f[now]=a[1].p;
    for(int i=2;i<=n;++i)now+=a[i-1].st,f[now]=min(f[now],a[i].p);
    for(int i=2*n;i;--i)f[i]=min(f[i],f[i+2]);
    now=n;
    for(int i=1;i<=n;++i)now+=a[i].st,ans=max(ans,a[i].p-f[now]);
    cout << ans << endl;
}
```

---

## 作者：majt (赞：8)

总觉得上一个题解写的好简单 : (


首先，容易想到问题的本质在于找一段使得白牛比黑牛多（长度当然是偶数），写出答案为：


ans[i]=min{ j | presum[ i ] - presum[ j ] >= 0} （\*）, (presum是前缀和，以下简称s) ，考虑到长度必须为偶数，不妨分奇偶处理（代码中的lefj、lefo分别处理奇、偶）


观察（\*）式，其实只在对每一个 i 找一个最靠左（最小）的 j 使得s[ j ] <=s[ i ] ，这个显然是可以预处理出来的；


以奇数（lefj）为例，lefj[ i+n ]保存下标为奇数的s中最小的j使得 s[ j ] <= i ，由定义得


1、 lefj[ sum[ i ]+n ]=min ( lefj[ sum[ i ]+n ], i ) 2、lefj[i]=min(lefj[i],tmp); tmp=min(tmp,lefj[i]);


于是有了代码的主体


```cpp

for(int i=1;i<=n;i+=2){
    lefj[sum[i]+n]=min(lefj[sum[i]+n],i);
}
for(int i=0;i<=n;i+=2){
    lefo[sum[i]+n]=min(lefo[sum[i]+n],i);
}
```
以及
```cpp

int tmp=lefj[0];
    cow[n+1].pos=inf;
    for(int i=1;i<=2*n;++i){
        lefj[i]=min(lefj[i],tmp);
        tmp=min(tmp,lefj[i]);
    }
```
但是由于一些鬼畜的边界，写代码的时候要注意（不再赘述，看代码吧）！！！

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
#define ll long long
int getint() {
    int x=0,f=1;
    char ch=getchar();
    while(ch==' '||ch=='\n') {
        ch=getchar();
    }
    while(ch<'0'||ch>'9') {
        f=-f;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
const int inf=0x7fffffff;
const int MAXN=101000;
struct COW{
    int pos;
    int col;
}cow[MAXN];
int n,sum[MAXN],lefj[2*MAXN],lefo[2*MAXN],ans;//lefj, lefo分类处理
inline bool cmp(COW a,COW b){
    return a.pos<b.pos;
}
int main(){
    n=getint();
    for(int i=1;i<=n;++i){
        cow[i].pos=getint();
        char ch=getchar();
        if(ch=='W'){
            cow[i].col=1;
        }else{
            cow[i].col=-1;
        }
    }
    sort(cow+1,cow+1+n,cmp);//按pos排序
    for(int i=1;i<=n;++i){
        sum[i]=sum[i-1]+cow[i].col;
        lefj[i-1]=lefj[i-1+n]=inf;
        lefo[i-1]=lefo[i-1+n]=inf;
    }
    for(int i=1;i<=n;i+=2){
        lefj[sum[i]+n]=min(lefj[sum[i]+n],i);//上述分析的1、
    }
    for(int i=0;i<=n;i+=2){
        lefo[sum[i]+n]=min(lefo[sum[i]+n],i);
    }
    int tmp=lefj[0];
    cow[n+1].pos=inf;
    for(int i=1;i<=2*n;++i){//上述分析的2、
        lefj[i]=min(lefj[i],tmp);
        tmp=min(tmp,lefj[i]);
    }
    tmp=lefo[0];
    for(int i=1;i<=2*n;++i){//lefo神奇的边界
        if(i>=n){
            lefo[i]=0;
        }
        lefo[i]=min(lefo[i],tmp);
        tmp=min(tmp,lefo[i]);
    }
    for(int i=1;i<=n;++i){    
        if(i%2==0){    
            ans=max(ans,cow[i].pos-cow[lefo[sum[i]+n]+1].pos);
        }else{
            ans=max(ans,cow[i].pos-cow[lefj[sum[i]+n]+1].pos);
        }
    }
    cout<<ans<<endl;
}
```

---

## 作者：是个汉子 (赞：7)

[原题](https://www.luogu.com.cn/problem/P3105)

### Solution1

##### 考虑如果白牛不能变花牛

如何迅速统计区间牛的数目——利用前缀和统计，设每个牛的 $v=1$ ，求 $sum_i=\sum_{j=1}^iv_j$

那么如何迅速判断是否满足白牛数=花牛数——不妨设白牛的 $v=1$ ，花牛的 $v=-1$ ，那么区间 $(l,r)$ 满足条件就是 $sum_r-sum_{l-1}=0$ 

此时开一个 $map$ 统计 $pre_{sum_i}$ ， $pre_i$ 代表 $i$ 这个值第一次出现的地方， $O(n)$ 扫描取 $max\{pos_i-pos{_{pre_{sum_i}}}\}$ 

##### 现在取消限制，白牛可以变花牛

那么区间满足的条件就得发生变化： $sum_r-sum_{l-1}\equiv 0\pmod 2$ 

说人话就是花牛和白牛一一配对后，剩下的白牛需要为偶数，这样才能保证将刚好一半的白牛转化成花牛，满足条件

此时如何统计答案呢？我们不能用 $O(n^2)$ 去枚举→_→

因为上面用是 $O(n)$ 扫描，下面不能更劣，所以也考虑扫描。（~~这理由好迷，性感理解~~）

分类讨论一下对于不同的 $sum$ 怎么统计答案

- 当 $sum_i<0$ 时，需要找一个 $j$ 满足 $sum_i-sum_j\geq0(j<i)$ 。

  ~~显然~~可得 $sum_j=sum_i$ 时最优，因为 $sum_i-sum_j>0$ 意味着还剩下几只白牛，但再加几只花牛总比白牛变花牛优(ง •_•)ง

  然后用有限制时的 $map$ 法

- 当 $sum_i\geq 0$ 时，奇偶还得分开想

   $sum_i$ 为偶数时， 前 $i$ 只牛都可以取。当 $sum_i$ 为奇数时，还需要将第一只牛舍去，因为第一只牛不管是 $\pm 1$ ， $sum_i-sum_1$ 肯定为偶数，并且最优。

时间复杂度： $O(n\log n)$ 排序 $+$  $O(n)$ 扫描

细节：1.因为我们的 $pos_i$ 是从坐标轴的 $1$ 开始的，所以求 $sum_i>0$  且为偶数的区间长度时答案应该是 $pos_i-pos_1$ ，奇数同理。2.记得排序，**输入不保证有序**。

### Code1

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=100010;
struct node{
    int pos;
    int v;
}cow[N];
int sum[N],ans;
int n;
char op[2];
map<int,int> pre;

inline bool cmp(node a,node y){
    return a.pos<y.pos;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%s",&cow[i].pos,op);
        if(op[0]=='W') cow[i].v=1;
        else cow[i].v=-1;
    }
    sort(cow+1,cow+n+1,cmp);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+cow[i].v;
        if(!pre[sum[i]]&&sum[i]<0) pre[sum[i]]=i;
        else if(sum[i]<0) ans=max(ans,cow[i].pos-cow[pre[sum[i]]].pos);
        if(sum[i]%2==0&&sum[i]>=0) ans=max(ans,cow[i].pos-cow[1].pos);
        else if(sum[i]>=0) ans=max(ans,cow[i].pos-cow[2].pos);
    }
    printf("%d\n",ans);
    return 0;
}
```



你以为真的结束了吗？

~~不瞎~~细心的人会发现我上面写的是Solution1，所以现在是Solution2

### Solution2

受机房奆佬[ql12345](https://www.luogu.com.cn/user/286239)指点此题可以用**二分**

预处理和Solution1的一样

剩下的就是二分区间长度，然后 $O(n)$ 扫描是否存在满足题目条件的区间长度。

时间复杂度： $O(n\log n)$ 

### Code2

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=100010;
int n;
int sum[N],ans;
struct node{
    int pos;
    int v;
}cow[N];
char op[2];

inline bool cmp(node a,node y){
    return a.pos<y.pos;
}

inline bool check(int x){
    int r=0;
    for(int l=1;l<=n;l++){
        while(cow[r].pos-cow[l].pos<x&&r<n) r++;
        if(cow[r].pos-cow[l].pos<x) break;
        if(sum[r]-sum[l-1]>=0&&(sum[r]-sum[l-1])%2==0) return true;
    }
    return false;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%s",&cow[i].pos,op);
        if(op[0]=='W') cow[i].v=1;
        else cow[i].v=-1;
    }
    sort(cow+1,cow+n+1,cmp);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+cow[i].v;
    int l=0,r=1e9+1;
    while(r-l>1){
        int mid=(l+r)>>1;
        if(check(mid)) l=mid;
        else r=mid;
    }
    printf("%d\n",l);
    return 0;
}
```

真的结束了^_^

---

## 作者：Miss_SGT (赞：4)

#### 思路：

读完题目，发现几个对于答案区间显然的要求：

1. 白牛个数大于等于黑牛，这样才能让多的一部分白牛变成黑牛。

2. 区间长度为偶数，不然无论如何两种牛个数也不可能相等。

#### 做法：

对于要求一，我们设区间右端点白牛与花牛的数量总和分别为 $R_W$ 与 $R_S$，**左端点的前一个**白牛与花牛的数量总和分别为 $L_W$ 与 $L_S$。那么有 $R_W - L_W \ge R_S - L_S$，移项可得 $R_W - R_S \ge L_W - L_S$，显然可以用树状数组维护。

对于要求二，因为区间长度为偶数，所以**右端点与左端点的前一个**奇偶性相同，开两个树状数组，分别维护奇数和偶数即可。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
template <typename T> inline void read(T &x) {
    x = 0; char ch = getchar(); int f = 1;
    while (!isdigit(ch) && ch ^ '-') ch = getchar();
    if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar(); x *= f;
}
int n,ans,cnt;
struct cow{int x,d;}a[N];
inline bool cmp(cow x,cow y){return x.x<y.x;}
inline int char_(){
	char c=getchar();
	while(c^'W'&&c^'S') c=getchar();
	return c=='W'?1:(-1);
}
int t[2][N<<1];
inline void add(bool o,int x,int v){
	for(;x<=n+N&&t[o][x]==t[0][0];x+=x&-x) t[o][x]=v;
}
inline int get(bool o,int x){
	int ans=t[0][0];
	for(;x;x-=x&-x) ans=min(ans,t[o][x]);
	return ans;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i].x);
		a[i].d=char_();
	}
	sort(a+1,a+n+1,cmp);
	memset(t,0x3f,sizeof(t));
	add(0,N,0);
	for(int i=1,g;i<=n;i++){
		cnt+=a[i].d;
		g=get(i&1,cnt+N);
		if(g^t[0][0]) ans=max(ans,a[i].x-a[g+1].x);
		add(i&1,cnt+N,i);
	}
	printf("%d",ans);
	return 0;
}

```

**注意，因为差值有负数，所以加上一个 $n$ 再用树状数组，空间也要开两倍。**

---

## 作者：VioletIsMyLove (赞：3)

我的想法很奇怪，将白牛标成 $-1$ ,斑点牛标成 $+1$ ，然后把所有的奇偶分开来做，再用 $RMQ$ 分别标记前面每个区间的最大值，找在前面的第一个大于当前位置的数，当前位置的最优解就是前面第一个大于当前位置的数的下标了，然后结果就是当前位置下标-找到位置下标 $+1$ ,容斥嘛，最后 $ans$ 刷一趟最大值就ok了。感觉这也是一种新解法。。。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct ZS{
	int x,y;
	bool operator <(const ZS b)const{return x<b.x;}
}c[1000005];
int n,ans,lena,lenb,m;
int s[1000005],a[500005][25],b[500005][25];
void make(int &L,int &R,int j,int x){
	if(L+(1<<j)-1<=R){
		if(a[L][j]>=s[x]){R=L+(1<<j)-1;return;}
		if(a[R-(1<<j)+1][j]>=s[x]){L=R-(1<<j)+1;return;}
	}
	else return;
	L=0;R=0;
}
int check(int x){
	int L=1,R=x/2;
	for(int j=15;j>=0;j--){
		make(L,R,j,x);
		if(!L&&!R)return -1;
	}
	return c[(L-1)*2+2].x;
}
void make_(int &L,int &R,int j,int x){
	if(L+(1<<j)-1<=R){
		if(b[L][j]>=s[x]){R=L+(1<<j)-1;return;}
		if(b[R-(1<<j)+1][j]>=s[x]){L=R-(1<<j)+1;return;}
	}
	else return;
	L=0;R=0;
}
int check_(int x){
	int L=1,R=x/2;
	for(int j=15;j>=0;j--){
		make_(L,R,j,x);
		if(!L&&!R)return -1;
	}
	return c[L*2-1].x;
}
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		c[i].x=read();char ch=getchar();
		if(ch=='W')c[i].y--;
		else c[i].y++;
	}
	sort(c+1,c+1+n);
	for(int i=1;i<=n;i++)s[i]=s[i-1]+c[i].y;
	for(int i=1;i<=n;i+=2)if(i<=n)a[++lena][0]=s[i];
	b[++lenb][0]=0;for(int i=2;i<=n;i+=2)if(i<=n)b[++lenb][0]=s[i];
	for(int j=1;j<=15;j++)
		for(int i=1;i<=(n+1)/2;i++)if((1<<j)<=((n+1)/2-i+1))a[i][j]=max(a[i][j-1],a[i+(1<<j-1)][j-1]);
	for(int j=1;j<=15;j++)
		for(int i=1;i<=n/2;i++)if((1<<j)<=(n/2-i+1))b[i][j]=max(b[i][j-1],b[i+(1<<j-1)][j-1]);
	for(int i=3;i<=n;i+=2)if(i<=n){
		int x=check(i);
		if(x!=-1)ans=max(ans,c[i].x-x);
	}
	for(int i=2;i<=n;i+=2)if(i<=n){
		int x=check_(i);
		if(x!=-1)ans=max(ans,c[i].x-x);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Zindow (赞：2)

排序之后令'W'为1， 'S'为-1， 假设有前缀和数组s[i]=Σa[i].second，那么对于一个右端点j来说， 只要满足s[j] - s[i] >= 0， 那么区间[i+1, j]就有可能是合法的。 s[j] - s[i+1] >= 0翻译一下就是区间的W比S多，根据题意，可以把W变成S从而可能使得W和S一样多，那么此时，只要满足i, j是同奇偶的， 也就区间长度是偶数的， 就一定可以通过操作使得区间满足W跟S一样多。 此时， 问题就转化成了， 对于一个端点j， 要找到一个i, 满足s[i] <= s[j] 且i 要尽量小， 这个可以离散化一下用线段树维护最小值解决， 对于同奇偶的条件， 开两棵线段树就可以了。
```cpp
#include <bits/stdc++.h>

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 5;

pair<int, char> a[maxn];
int tree[2][maxn << 3];
int n;

void update(int *tree, int u, int l, int r, int x, int val)
{
    if(l == r) tree[u] = min(tree[u], val);
    else
    {
        int mid = (l + r) >> 1;
        if(x <= mid) update(tree, u << 1, l, mid, x, val);
        else update(tree, u << 1 | 1, mid + 1, r, x, val);
        tree[u] = min(tree[u << 1], tree[u << 1 | 1]);
    }
}

int query(int *tree, int u, int l, int r, int ql, int qr)
{
    if(ql <= l && r <= qr) return tree[u];
    else
    {
        int mid = (l + r) >> 1, res = inf;
        if(ql <= mid) res = min(res, query(tree, u << 1, l, mid, ql, qr));
        if(mid < qr) res = min(res, query(tree, u << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
}

int main(void)
{
    while(~scanf("%d", &n))
    {
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d %c", &a[i].first, &a[i].second);
        }
        sort(a + 1, a + 1 + n);
        int ans = 0, s = 0;
        memset(tree, inf, sizeof tree);
        int delta = n + 1;
        update(tree[0], 1, 1, 2 * n + 1, 0 + delta, 0);
        for(int i = 1; i <= n; ++i)
        {
            s += (a[i].second == 'W') ? 1 : -1;
            int ctrl = (i & 1);
            int pt = query(tree[ctrl], 1, 1, 2 * n + 1, 1, s + delta);
            if(pt != inf) ans = max(ans, a[i].first - a[pt + 1].first);
            update(tree[ctrl], 1, 1, 2 * n + 1, s + delta, i);
        }
        printf("%d\n", ans);
    }

    return 0;
}

```


---

## 作者：MspAInt (赞：1)

[传送门](https://www.luogu.com.cn/problem/P3105)

要使白牛黑牛（指斑点牛）数量相同，那么区间长度必须是偶数。我们可以将白牛涂成黑牛，所以只要保证白牛数量不少于黑牛就行。

直觉转换模型，把白牛看作 $1$，黑牛看作 $-1$，按 $x_i$ 升序做一个前缀和，现在问题就明了很多：对于序列 $s$，找到一对数 $i,j(i>j)$，使得 $s_i-s_{j-1}\ge 0$（$s_0=0$）且 $(i-j+1)\bmod 2=0$，最大化 $x_i-x_j$。

枚举右端点 $i$ 分类讨论：

* $s_i\ge 0$。
	* $i\bmod 2=0$：钦定左端点为 $1$，这是最优的合法选择。$i-1+1$ 为偶数，$s_i-s_{1-1}\ge 0$。
   * $i\bmod 2=1$：钦定左端点为 $2$，显然没有更优选择。$i-2+1$ 为偶数，$s_i-s_{2-1}\ge 0$（证明： $i$ 为奇数且 $s_i\ge 0$ 说明区间 $[1,i]$ 中，白牛数量严格大于黑牛，而 $|s_{2-1}|\le 1$，并不会使区间不合法）。
* $s_i<0$：此时序列中第一个使得 $s_{j-1}=s_i$（$s_i-s_{j-1}=0$）的 $j$ 为最优位置。显然此时黑牛白牛数量相等，同时保证了区间长度为偶数。这里可以开个桶记录。

以及，管理看一眼 [hack贴](https://www.luogu.com.cn/discuss/427127) 罢 ![](//图.tk/q)

Code:（$n\log n$）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{int x,p;}a[N];
int n,m[N],ans;
bool cmp(node p,node q){
    return p.x<q.x;
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        char ch;
        scanf("%d",&a[i].x);
        cin>>ch;
        if(ch=='W')a[i].p=1;
        else if(ch=='S')a[i].p=-1;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)a[i].p+=a[i-1].p;
    for(int i=1;i<=n;i++){
        if(a[i].p<0)
            if(m[a[i].p+n])ans=max(ans,a[i].x-a[m[a[i].p+n]+1].x);
            else m[a[i].p+n]=i;
        else 
            if(i&1)ans=max(ans,a[i].x-a[2].x);
            else ans=max(ans,a[i].x-a[1].x);
    }
    printf("%d\n",ans);
    //system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/117366456)

---

## 作者：denominator (赞：1)

# 「P3105 \[USACO14OPEN\] Fair Photography S」题解

**upd on 2023/7/13**：代码写挂了，但还能过。管理就不用看内容了。

想得有点奇怪，也算一个思路吧。

## Part \#1 转换题意

令牛的位置排序。

这部分和第一篇题解相同——我们要求的序列满足 **区间内 `W` 数大于等于 `S` 数** 并且 **区间长度为偶数**。

## Part \#2 再转换题意

**区间长度为偶数** 这个条件非常棘手，我们先思考以下问题：如果没有这个条件，问题怎么做？

甚至，思考以下问题，我们等会考虑本题目与原题的关系：

> 有三个数列 $\{a_1, a_2, \cdots, a_n\}$、$\{b_1, b_2, \cdots, b_n\}$ 和 $\{c_1, c_2, \cdots, c_n\}$，选取一个区间 $[l,r]$，使得
> $$\sum_{i=l}^r a_i \geq 0$$
>
> 求 $b_r-c_l$ 的最大值。
>
> 数据保证：$1 \leq n \leq 10^5$，且 $c_1 < b_1 < c_2 < b_2 < \cdots < c_n < b_n$。

**注意：下面的做法有一点问题，但是更便于理解题意，勿轻信。后面有纠正**。

然后会想到前缀和。我们要求该区间的和 ${} \geq 0$。也就是说，设序列 $a$ 的前缀和序列为 $\{S_1, S_2, \cdots, S_n\}$，我们需要取一个 $i,j$ 满足 $1 \leq i \leq j \leq n$ 且 $S_j - S_i \geq 0$ 即 $S_i \leq S_j$。

我们可以按照 $S_i$ 为关键字从大到小排序，并维持 $b,c$ 与 $a$ 数列的相对关系。

现在，从左往右线扫一遍，设扫到 $k$。同时维护 $\max\limits_{i=1}^{k-1}b_i=M_k$。那么，对于 $k$ 这个位置而言，当 $i=k$ 时，$j$ 只需满足 $1 \leq j < k$ 且 $b_j > c_i$。对于前者，若条件满足，必须会在排序之前的数组中，$S_i<S_j$；对于后者，若条件满足，必须会在排序之前的数组中，$i<j$。那么，$i=k$ 时的结果 $T_k$ 满足：

$$
\begin{aligned}
T_k &= \max_{i=1}^{k}b_i-c_k\\
   &= \max_{i=1}^{k-1}[b_i-c_k\geq 0](b_i-c_k)\\
   &= -c_k+\max_{i=1}^{k-1}[b_i-c_k\geq 0]b_i\\
   &= [M_k-c_k\geq 0](M_k-c_k)
\end{aligned}
$$

**然后你发现你可能推错了**。

问题在哪呢？看上面提到的两句话：

> ……且 $S_j - S_i \geq 0$ 即 $\bm{S_i \leq S_j}$。
>
> 对于前者，若条件满足，必须会在排序之前的数组中，$\bm{S_i<S_j}$

你的 $S_i=S_j$ 呢？

你可能觉得，按 $S$ 排序应该是不行的。若正好 $j$ 排在了 $i$ 后面（$i \leq j$ 且 $S_i=S_j$），你或许就正好漏掉了一个可能的最大值。

这个好办，再加上第二关键字 $i\leq j$（或 $b_i\leq b_j$，或 $c_i\leq c_j$）。

你觉得这道题可能就结束了。但可惜的是，**然后你发现你可能又推错了**。

问题又在哪呢？看上面提到的两句话：

> ……我们需要取一个 $i,j$ 满足 $1 \leq \bm{i \leq j} \leq n$ 且……
>
> 对于后者，若条件满足，必须会在排序之前的数组中，$\bm{i<j}$。

你的 $i=j$ 呢？

你可能觉得，不就是一个特判的事，或又一个线扫的事嘛。

你完全错了。

如果你还是不知道你错哪了，问题居然在刚开始的第一步！

> ……我们需要取一个 $i,j$ 满足 $1 \leq i \leq j \leq n$ 且 $S_j - S_\bm{i} \geq 0$ 即……

可能眼尖的读者早就发现这个问题了。你想想，在你刚入坑 OI 时，你写下的第一行前缀和代码是什么？$S_j-S_\bm{i-1}$！

或者说，为了让下标好看一点，我们可以把上面那句话改为：

> ……我们需要取一个 $i,j$ 满足 $\bm{0 \leq i \leq j \leq n+1}$ 且 $S_\bm{j+1} - S_i \geq 0$ 即……

平移一下，令 $n'=n+1$ 且 $S'_i=S_{i-1}$，$b'_i=b_{i-1}$，$c'_i=c_i$（实际上 $c$ 不用动，但是也换一下，好看一点）。

把 $n$ 用 $n'$ 替代，$S$ 用 $S'$ 替代，$b$ 用 $b'$ 替代，$c$ 用 $c'$ 替代，你惊奇地发现，上句变成了

> ……我们需要取一个 $i,j$ 满足 $1 \leq \bm{i < j} \leq n'$ 且 $S'_j - S'_i \geq 0$ 即……（注意这里的 $i$ 实际上比上句的 $i$ 大了 $1$）

再换一下其他地方（此处从略），你又惊奇地发现，所有问题都迎刃而解了！

好了，本题完成。写一下伪代码。

```cpp
struct node {
	int S, b, c;
} t[N];
bool cmp (node x, node y) {
	return x.S == y.S? x.c < y.c: x.S < y.S;
}
int solve (int n, int a[], int b[], int c[]) {
	t[1].c = c[1];
	for (int i = 2; i <= n + 1; i++) {
		a[i - 1] += a[i - 2];
		t[i].a = a[i - 1];
		t[i].b = b[i - 1];
		t[i].c = c[i];
	}
	t[n + 1].b = 0x7f7f7f7f; // 这个值大于 b 中其他数
	// 注意上面一句话，有两点注意：
	// 1. 将 t[n + 1].b 设为最大值后，第二关键字不能选择 b，只能选择 c；
	// 2. 这句话只是让 n + 1 无法被选为 i，对后续操作无影响——虽然我们的推导依赖 c_1 < b_1 < c_2 < b_2 < ... < c_n < b_n。
	sort (t + 1, t + n + 2, cmp);
	int M = t[1].b, s = 0xffffffff;
	for (int i = 2; i <= n + 1; i++) {
		if (t[i].c < M) {
			s = min (s, M - t[i].c);
		}
		M = max (M, t[i].b);
	}
	return s;
}
```

## Part \#3 回归原题

终于要来了，是不是很 excited 啊？

上面说了，**区间长度为偶数** 是我们有这种思考的关键。

如果我们将相邻两头牛捆绑起来。建立三个数组 $a,b,c$，考虑从左往右相邻的第 $i$ 对牛：

- 若两头牛均为 `S`，则 $a_i=-1$；
- 若两头牛均为 `W`，则 $a_i=1$；
- 若一头牛为 `S`，一头牛为 `W`，则 $a_i=0$；
- 若两头牛位于 $x_1,x_2$，且 $x_1<x_2$，则 $b_i=x_2$ 且 $c_i=x_1$。

想想看我们为什么这么做。

- 若一段区间和 ${} \geq 0$，则说明 `W` 的数量多于 `S`，需要计入答案。${} \leq 0$ 与 ${}=0$ 同理；
- 若选择的一段区间 $[l,r]$（对应到转换后的 $a$ 序列为 $[m,n]$）对答案有贡献，则贡献为 $x_r-x_l=b_n-c_m$。

完美符合上述题目！

注意一下，要分类讨论：

- 若 $n$ 为奇数，上述合并的贡献可能处于 $[1,n-1]$ 或 $[2,n]$；
- 若 $n$ 为偶数，上述合并的贡献可能处于 $[1,n]$ 或 $[2,n-1]$。

总时复 $\mathcal O(n\log n)$ 带几倍常数。还行。

看来分析得够多了，上代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, a[N], _a[N], p[N];
bool c[N], _c[N];
bool cmp (int a, int b) {
	return _a[a] < _a[b];
}
int b[N], x1[N], x2[N], p1[N];
bool cmp1 (int x, int y) {
	return (b[x] == b[y])? (x2[x] > x2[y]): (b[x] > b[y]);
}
int solve (int l, int r) {
	fill (b + 1, b + n + 1, 0);
	for (int i = l; i <= r; i += 2) {
		if (!c[i] && !c[i + 1]) {
			b[(i - l) / 2 + 2] = -1;
		}
		if (c[i] && c[i + 1]) {
			b[(i - l) / 2 + 2] = 1;
		}
		x1[(i - l) / 2 + 1] = a[i];
		x2[(i - l) / 2 + 2] = a[i + 1];
	}
	int siz = (r - l) / 2 + 2;
	x1[siz] = 1145141919;
	for (int i = 1; i <= siz; i++) {
		b[i] += b[i - 1];
		p1[i] = i;
	}
	sort (p1 + 1, p1 + siz + 1, cmp1);
	int mx = x2[p1[1]], ans = 0;
	for (int i = 2; i <= siz; i++) {
		if (mx - x1[p1[i]] > 0) {
			ans = max (mx - x1[p1[i]], ans);
		}
		mx = max (mx, x2[p1[i]]);
	}
	return ans;
}
int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) {
		char ch[5];
		scanf ("%d%s", &_a[i], &ch);
		_c[i] = (ch[0] == 'W');
		p[i] = i;
	}
	sort (p + 1, p + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		a[i] = _a[p[i]];
		c[i] = _c[p[i]];
	}
	// 如果有用这个代码调试的小盆友（应该没有吧）注意：以下 solve 函数的调用顺序不固定，我自己调试是也被吓了
	if (n % 2 == 0) {
		printf ("%d\n", max (solve (1, n), solve (2, n - 1)));
	} else {
		printf ("%d\n", max (solve (1, n - 1), solve (2, n)));
	}
	return 0;
}
```

~~这种方法竟然能跑进总时间 300ms？码量没超 1.5KB？不可思议。~~

---

## 作者：ethan0328 (赞：1)

## 思路

考虑用 $pre_{i}$ 表是前 $i$ 个牛中白牛数减花牛数。

因为白牛可以变花牛，所以当 $pre_{i}-pre_{j-1}$ 是偶数时，可以取 $i$ 到 $j$ 这段区间。

当 $pre_{i} \ge 0$ 时，若 $pre_{i}$ 是奇数，则 $pre_{i}-pre_{1}$ 显然为偶数且最优。若 $pre_{i}$ 是偶数，则 $pre_{i}-pre_{0}$ 显然为偶数且最优。

当 $pre_{i}<0$ 时，要让 $pre_{i}-pre_{j} \ge 0$，显然 $pre_{i}=pre_{j}$ 时最优，用 map 记录与他值相等的 $pre$ 第一次出现位置即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct cow
{
	int val,pos;
	bool operator <(const cow x) const
	{
		return pos<x.pos;
	}
};
int n,ans,pre[N];
cow c[N];
map<int,int> mp;
int main()
{
	char x;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i].pos;
		cin>>x;
		if(x=='W')
		{
			c[i].val=1;
		}else
		{
			c[i].val=-1;
		}
	}
	sort(c+1,c+1+n);
	for(int i=1;i<=n;i++)
	{
		pre[i]=pre[i-1]+c[i].val;
	}
	for(int i=1;i<=n;i++)
	{
		if(pre[i]<0)
		{
			if(mp[pre[i]]==0)
			{
				mp[pre[i]]=i;
			}else
			{
				ans=max(ans,c[i].pos-c[mp[pre[i]]+1].pos);
			}
		}else
		{
			if(pre[i]&1)
			{
				ans=max(ans,c[i].pos-c[2].pos);
			}else
			{
				ans=max(ans,c[i].pos-c[1].pos);
			}
		}
	}
	cout<<ans;
}
```


---

## 作者：老咸鱼了 (赞：1)

题目看一眼就能发现是前缀和了，如果题目是要求我们求白牛和花斑牛一样多的时候我们只需要判断两种牛数量的从第一头牛到两个点之间的两种牛数量的差值是否相等，如果相等则说明中间这一段和是为0的，也就是两种牛的数量相等，计算的时候第一个点出现的位子要加1，不然牛的数量就不对。

但是题目说白牛可以变成花斑牛，所以当白牛的数量大于花斑牛的时候我们就直接取当前点和最开始的点的距离，如果白牛数量比花斑牛多奇数头那么就取第二个点，偶数就取第一个点，结果对所有的算出来的距离取最大值就是答案了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(){
	int f=1,s=0;char c=getchar();
	while(c<'0'||c>'9'){
		if(c>='a'&&c<='z'||c>='A'&&c<='Z')return c;
		if(c=='-')f=-1;c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=(s<<1)+(s<<3)+(c^48);c=getchar();
	}
	return f*s;
}
const int N=2555555;
ll ans,s[N],sum;
struct f{
	ll x;
	int color;
}a[N];
bool cmp(f a,f b){
	return a.x<b.x;
}
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();
		a[i].color=(read()=='W'?1:-1);
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		sum+=a[i].color;
		if(sum>=0){
			if(sum%2==1){
				ans=max(a[i].x-a[2].x,ans);
			}
			else{
				ans=max(ans,a[i].x-a[1].x);
			}
		}
		else{
			if(!s[-sum])s[-sum]=a[i+1].x;//因为是排好序，所以第一次出现的一定是在最前面的。
			else ans=max(ans,a[i].x-s[-sum]);
		}
	}
	cout<<ans<<endl;
}
```


---

## 作者：ysj1173886760 (赞：1)

很明显的二分了吧

其实是我不会写dp也看不懂题解里dalao的做法QAQ

单调性还是比较显然的

二分一个长度，若存在大于这个长度且满足条件的，说明这个长度可行，否则不可行。

即白牛为1，花牛为-1.

然后离散化一下，再处理一下前缀和。

如果是2的倍数的非负整数，说明满足条件，每次O(n)扫描一遍就行了。

复杂度nlogn

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=1e5+10;

int n;
int sum[maxn];
struct cow
{
	int x,op;
}a[maxn];

bool cmp(const cow &a,const cow &b)
{
	return a.x<b.x;
}
bool check(int x)
{
	int r=0;
	for(int l=1;l<=n;l++)//枚举左端点 
	{					//每个点最多成为左端点一次，右端点一次，所以check一次的复杂度就是O(n)的 
		while(a[r].x-a[l].x<x&&r<n)r++;//找到合法的右端点 
		if(a[r].x-a[l].x<x)break;		//找不到说明后面的也找不到，及时break 
		if(sum[r]-sum[l-1]>=0&&(sum[r]-sum[l-1])%2==0)return true;//满足条件就返回 
	}
	return false;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		char op[2];
		scanf("%d %s",&a[i].x,op);
		if(op[0]=='W')a[i].op=1;
		else a[i].op=-1;
	}
	sort(a+1,a+1+n,cmp);//离散一下 
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i].op;//处理前缀和 
	int lb=0,ub=1e9+1;//设置上边界和下边界，注意左闭右开区间，所以右端点+1 
	while(ub-lb>1)
	{
		int mid=(lb+ub)>>1;
		if(check(mid))lb=mid;
		else ub=mid;
	}
	cout<<lb;
	return 0;
}
```

---

## 作者：时间圣使·凡 (赞：0)

## 一些联想
观察到该题目提及白牛花牛要求数量一致的时候，很容易就联想到与括号匹配一样的做法。
## 解法
将白牛看成 $1$，花牛看成 $-1$；并按照位置排序后进行前缀和的操作（因为牛的位置需要连续）。由于本题的特殊性，白牛可以转变成花牛；同时加上数据范围的限制不能使用 $N^{2}$ 算法，所以需要效率更高的处理方式，于是我们选择分情况处理数据。

#### 情况一：$sum_{i}$ 如果大于0，说明白牛多（$sum_{i}$ 即前缀和数组）。

+ 如果为偶数，则说明从第一头牛到该牛所有牛构成合法的排列，于是直接记录答案（因为在 $i$ 头牛之前所有牛都囊括在内，必然最优。）

+ 如果为奇数，则去掉第一头牛，剩下的全为合法牛（因为去掉的那头牛若为白牛，则花白两种牛数量相等；若为花牛，则白牛多出的数量为偶数），此时需要比较取最优解（因为没有囊括所有的牛）

#### 情况2：$sum_{i}$ 如果小于0，说明花牛多。

+ 由于我们不能把花牛变成白牛，所以寻找包含当前牛最长的序列，便是第一次出现这次出现的 $sum_{i}$ 的值的牛的下一头开始到这头牛的序列（因为这些牛如果不是合法序列那不会造成两次 $sum_{i}$ 的值一样，同时第一次出现的牛到当前牛的序列长度总比后面出现的长）


## 一些细节
可以看到很多题解都使用了 $map$，事实上直接使用数组就可以（因为 $map$ 访问时间实际上更长，而内存占用与数组相比并没怎么节省~~如有错误请评论区指正~~）

**代码中也有详细的解释，不想看解法可以直接看代码。**
## 代码
```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n,ans;
int sum[100010];
struct zwh{
	int col,id;
}f[100010];
int fl[100110];//实际上没必要用map，这里我感觉用map只是为了打代码方便罢了。
bool cmp(zwh x,zwh y){return x.id<y.id;}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		char a;
		cin>>f[i].id>>a;
		if(a=='W') f[i].col=1;
		else f[i].col=-1;//白牛标记为1，花牛标记为-1
	}
	sort(f+1,f+1+n,cmp);//按照位置排序
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+f[i].col;//累计，大于 0 则白牛多，小于 0 则花牛多；两种情况下因白牛可以变成花牛而不同，所以采用这种方式计算。
		if(sum[i]>=0&&sum[i]%2==0) ans=f[i].id-f[1].id;//白牛多且为偶数则开头至此的牛必定都可以通过染色达成合法，且因为是从开头开始，则在数量为i的情况下必定最优。
		else if(sum[i]>=0) ans=max(ans,f[i].id-f[2].id);//如果为奇数，则去掉第一头绝对合法，此时需要考虑去掉第一头是否是最优解
		else if(!fl[sum[i]+100000]) fl[sum[i]+100000]=i;//如果是花牛多且当前花牛个数是第一次出现，标记一下
		else ans=max(ans,f[i].id-f[fl[sum[i]+100000]+1].id);
                //如果当前花牛个数之前出现过，则说明从第一次出现现次数的花牛后一头牛到这头牛所有牛的总和为合法牛串，才会出现重复出现的现象。
                //（PS:解答关于某些疑惑，比如 -3 到 -3 的牛万一后面加了两头白牛变成 -1 不是应该在此答案基础上还会增加 2 吗？注意 -3 的牛出现则说明之前出现了 -1,-2 牛，后面出现两头白牛则 -1 也会与之前的 -1 匹配，实际上比 -3 多出了 4 只;如果多出 3 或 4 只白牛变成了正数，则会在第一、二个判断中计算。）
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

怎么做都可以过吧，不得不说这道题方法很多的，所以这里就补充一种很简单的做法。               

首先我们令白牛为 $1$ ，花斑牛为 $-1$ ，那么我们只需要找到一个区间它的和大于 $0$ 并且长度为偶数它就是合法的。               

接着就很套路了，我们只要两个线段树维护下标为奇数和下标为偶数的前缀和，这个直接扫过去权值线段树就好了。      

查询时查找 $x$ 最靠前的一个合法前缀和位置就好了，合法条件就是该位置的前缀和小于等于当前位置的前缀和。            
```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
struct node
{
	int x,c;
}OX[Len];
bool cmp(node x,node y)
{
	if(x.x > y.x) return false;
	if(x.x == y.x && x.c == 1 && y.c == 0) return false;
	return true;
}
int n,m,ans[Len << 3][2],Sum[Len];char s[5];
inline int Into(int x){return x + 100001;}
inline int ls(int x){return x << 1;}
inline int rs(int x){return x << 1 | 1;}
void push_up(int x,int id){ans[x][id] = min(ans[ls(x)][id] , ans[rs(x)][id]);}
void build(int p,int l,int r)
{
	ans[p][0] = ans[p][1] = 1e9;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
}
void update(int p,int l,int r,int idx,int w,int id)
{
	if(l == r)
	{
		ans[p][id] = min(ans[p][id] , w);
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx , w , id);
	else update(rs(p) , mid + 1 , r , idx , w , id);
	push_up(p , id);
}
int query(int p,int l,int r,int nl,int nr,int id)
{
	if(nl <= l && nr >= r) return ans[p][id];
	int mid = (l + r) >> 1;int res = 1e9;
	if(nl <= mid) res = min(res , query(ls(p) , l , mid , nl , nr , id));
	if(nr > mid) res = min(res , query(rs(p) , mid + 1 , r , nl , nr , id));
	return res;
}
int main()
{
	scanf("%d",&n);
	build(1 , 1 , 200000);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&OX[i].x);scanf("%s",s + 1);
		if(s[1] == 'W') OX[i].c = 1;
		else OX[i].c = -1;
	}
	sort(OX + 1 , OX + 1 + n , cmp);
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		Sum[i] = Sum[i - 1] + OX[i].c;
		ans = max(ans , OX[i].x - query(1 , 1 , 200000 , 1 , Into(Sum[i]) , (i % 2) ^ 1));
		update(1 , 1 , 200000 , Into(Sum[i]) , OX[i].x , i % 2);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：破忆 (赞：0)

## 【题意】
在数轴上有N头牛
有白牛和花牛。你可以把任意白牛涂成花牛。

找一段尽量长的区间，使得区间的两端点均有一头牛，且区间中白牛与花斑牛的数量相等。

求最长的区间长度

## 【分析】
首先对奶牛排序

构造白牛与花牛数量差的前缀和，白牛视为$+1$，花牛视为$-1$，设前$i$头牛的前缀和为$s[i]$

考虑以$i$为右端点的最优解

$s[i]$有几种情况

### s[i]<0

此时花牛比白牛多，要找到一个$j$,使得$s[j]=s[i]$

那么$i$与$j$之间的白牛数与花牛数相等

显然，记录$s[i]$最早出现的位置即可

### s[i]>0且s[i]为偶数

白牛比花牛多，前$i$头牛一定可行，答案为二者距离差

### s[i]<0且s[i]为奇数

与第二中情况类似，第2头牛到第$i$头牛一定可行

## 【算法】
勉强算贪心吧

## 【代码】
```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int n,s[maxn],lst[maxn],ans;
struct why{
    int k,x;
	bool operator <(why b)const{return x<b.x;}
}a[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
 	freopen("P3105.in","r",stdin);
 	freopen("P3105.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();
		char ch=getchar();
		while(ch!='W'&&ch!='S') ch=getchar();
		if(ch=='W') a[i].k=1;else a[i].k=-1;
	}
	memset(lst,63,sizeof lst);
	int INF=lst[0];s[0]=n;//lst记录最早出现的位置，为了防止s[i]出现负数，初始时加上n
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i].k;
		if(lst[s[i]]==INF) lst[s[i]]=i;
	}
	for(int i=1;i<=n;i++){
		int x=s[i]-n;//计算时再减回来
		if(x<0){
			int j=lst[s[i]];
			if(j<i) ans=max(ans,a[i].x-a[j+1].x);  
		}else
		if(x%2==0) ans=a[i].x-a[1].x;
		else ans=max(a[i].x-a[2].x,ans);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：JMercury (赞：0)

这题其实就是要求最长的一段区间，其中牛的个数为偶数，且白牛个数不少于斑点牛数量。

~~我感觉我思路有点奇怪~~

首先，由于考虑的是一个区间，可以先考虑前缀和：把白牛设为1，斑点牛设为-1。这样可以轻松求出一个区间内白牛比斑点牛多多少。保存至$frt[\ ]$

然后，如果第$l$头牛到第$r$头牛是可行的，那么$frt[r]-frt[l-1]>=0$且$(r-l+1)\ mod\ 2=0$。枚举每一个右端点$r$，要找的是从$[1,r]$内第一个$l$使得$frt[l]$不大于$frt[r]$.。所以考虑维护第一个$x$满足$frt[x] < frt[i]$。将他计入$mi[\ ]$

求答案枚举右端点即可

附上AC代码

```cpp
#include<bits/stdc++.h>
const int maxn=100010;
using namespace std;

int n,ans,frt[maxn<<1],mi[maxn<<1];
struct Cow
{
    int x,w;
}a[maxn];

inline bool cmp(Cow x,Cow y) {return x.x<y.x;}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].x);
        char ch;cin>>ch;
        a[i].w=(ch=='W'? 1:-1);
    }
    sort(a+1,a+n+1,cmp);
    memset(frt,0x7f,sizeof(frt));
    memset(mi,0x7f,sizeof(mi));
    for(int i=1;i<=n;i++)
        a[i].w+=a[i-1].w,frt[a[i].w+n+1]=min(frt[a[i].w+n+1],a[i].x);
    for(int i=1;i<=2*n+1;i++)
    {
        mi[i]=frt[i];
        if(i>=3) mi[i]=min(mi[i],mi[i-2]);
    }
    for(int i=1;i<=n;i++) ans=max(ans,a[i].x-mi[a[i].w+n]);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：羚羊WANG (赞：0)

相信大家看到这里的时候，各位题目意思都理解的清清楚楚，明明白白

可以设$f_i$表示当前距离选到$i$时，区间长度的最大值

首先，我们可以观察出，选取区间时必须满足的两个条件：

$1.$当前区间内白斑牛的个数大于等于花斑牛的个数

$2.$当前区间内白斑牛与花斑牛的个数差应为$2$的倍数

所以

我们可以首先按照到原点的距离排序

然后如下

```cpp
now=n;
	f[now]=e[1].dis;
	for(register int i=2;i<=n;++i)
		{
			now+=e[i-1].st;
			f[now]=min(f[now],e[i].dis);	
		}
	for(register int i=n*2;i;--i)
		f[i]=min(f[i],f[i+2]);
```

通过这样，我们就可以求出所有$f$数组的值

最后，我们按照区间进行枚举可以求出答案

```cpp
now=n;
	for(register int i=1;i<=n;++i)
		{
			now+=e[i].st;
			ans=max(ans,e[i].dis-f[now]);
		}
```

最后的最后

总代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
struct node{
	int dis;
	int st;
}e[200010];
int now;
int ans;
int f[200010];
inline bool cmp(node a,node b){
	return a.dis<b.dis;
}
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		{
			e[i].dis=read();
			char c;
			cin>>c;
			if(c=='W')
				e[i].st=-1;
			else
				e[i].st=1;
		}
	sort(e+1,e+n+1,cmp);
	memset(f,0x7f,sizeof(f));
	now=n;
	f[now]=e[1].dis;
	for(register int i=2;i<=n;++i)
		{
			now+=e[i-1].st;
			f[now]=min(f[now],e[i].dis);	
		}
	for(register int i=n*2;i;--i)
		f[i]=min(f[i],f[i+2]);
	now=n;
	for(register int i=1;i<=n;++i)
		{
			now+=e[i].st;
			ans=max(ans,e[i].dis-f[now]);
		}
	write(ans);
	return 0;
}
```


---

