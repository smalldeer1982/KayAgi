# 「SWTR-1」Ethan and Sets

## 题目描述

$\mathrm{Ethan}$ 有 $n$ 个数字集合，每个集合有如下属性：

编号：第 $i$ 个集合编号为 $i$。

大小：第 $i$ 个集合大小为 $num_i$。

魔力：第 $i$ 个集合魔力为 $t_i$。

数字：第 $i$ 个集合中含有数字 $c_{i,1},c_{i,2},\dots,c_{i,num_i}$。

在 $\mathrm{Ethan}$ 的世界中，一共只有 $m+1$ 个数：$0$ 到 $m$。

$\mathrm{Ethan}$ 对数字有奇特的感情，在这 $m+1$ 个数中，有 $d$ 个数是他喜欢的，分别是 $p_1,p_2,\dots,p_d$ ，剩下 $m-d+1$ 个是他不喜欢的。

现在 $\mathrm{Ethan}$ 要删除一些集合，准确来说，他要选择一段区间 $[L,R]$，**删除所有编号在这个区间以外的集合**。

- 他想要使得在剩余的集合中，包含**所有**他喜欢的数。

- 并且在剩余的集合中，他**不喜欢的数的个数尽可能小**（注：这里的个数是指出现的次数，即如果 $1$ 是 $\mathrm{Ethan}$ 不喜欢的数，并且剩余的集合中出现了 $3$ 个 $1$，那么算 $3$ 个不喜欢的数）。

- 如果有多个满足条件的区间，他想要使得剩余集合的**魔力之和尽可能大**。

求出满足要求的 $[L,R]$，如果无解输出 $-1$，如果有多解，输出任意一解。

## 说明/提示

---

### 样例解释：

在样例 $1$ 中，$\mathrm{Ethan}$  可以选择 $[2,4]$，这样在剩余的集合中包含了所有他喜欢的数，且只有 $2$ 个他不喜欢的数在这些集合中出现。

在样例 $2$ 中，不存在合法的解。

---

### 数据范围：

本题使用 subtask。

subtask 1，$1 \leq n,m \leq 100$，$20\%$。

subtask 2，$1 \leq n,m \leq 500$，$30\%$。

subtask 3，$1 \leq n \leq 3000, 1 \leq m \leq 1000, 1 \leq t_i \leq 10^9$，$50\%$。

## 样例 #1

### 输入

```
5 7 4
1 3 4 5
3 3 4 6 5
4 2 1 5
2 3 1 7 3
5 2 2 4
6 6 3 5 4 6 1 7```

### 输出

```
2 4```

## 样例 #2

### 输入

```
2 3 2
1 2
4 1 1
4 2 1 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 3 2
1 2
1 1 3
1 2 1 2
1 1 2
1 3 1 2 3```

### 输出

```
2 3```

# 题解

## 作者：Alex_Wei (赞：19)

$\color{#00ff00}T2.\ Ethan\ and\ sets$

[$\color{#00ff00}\text{题面}$](https://www.luogu.org/problem/T99101?contestId=21489)

官方题解

---

$Sol\ 1\ :\ 20-50\ pts$

暴力求解，应该能拿到 $20\%$（毕竟是 $subtask$ 制）

（说不定用 $bitset$ 优化能拿到 $50\%$）

---

$Sol\ 2\ :\ 100\ pts$

$\large{Two-pointers}$

这题应该还算简单，$Two-pointers$ 模拟即可 

---

直接上代码（详细注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,g,s[50005],cnt[1005],c[3005][1005],num[50005],p[50005];
bool found=0;
ll ansb=1e18,anss,ansl,ansr;
int main()
{
	cin>>n>>m>>g;
	for(int i=1;i<=g;i++){
		ll x;
		scanf("%lld",&x);
		p[x]=1;//标记为喜欢
	}
	for(ll i=1;i<=n;i++){
		scanf("%lld%lld",&s[i],&num[i]);
		for(ll j=1;j<=num[i];j++)
			scanf("%lld",&c[i][j]);
	}
	ll l=1,r=1,sum=0,sumb=0;//当前区间为 [l,r) , sum = [l,r) 的魔力值之和 , sumb = [l,r) 中不喜欢的数的个数
	while(l<=n){
		while(r<=n){
			bool flag=1,check=1;//flag: 是否有不喜欢的数 (1=NO,0=YES) , check: 是否全部包含了所有 Ethan 喜欢的数
			for(ll i=1;i<=num[r];i++)
				if(!p[c[r][i]])
					flag=0;
			for(ll i=1;i<=m;i++)
				if(p[i]&&!cnt[i])//喜欢但不包含的数
					check=0;
			if(check&&!flag)break;//如果包含了所有喜欢的数 , 且 [l,r-1] 比 [l,r] " 不喜欢的数的个数 " 少 ( 集合 r 有不喜欢的数 ) , 那就选 [l,r-1] , 退出
			for(ll i=1;i<=num[r];i++){//右端点往右移 , 加上集合 r 的所有属性
				if(!p[c[r][i]])sumb++;
				cnt[c[r][i]]++;
			}
			sum+=s[r];
			r++;//右端点 ++ 
		}
		bool check=1;//这边还要再判断一下是否有全部喜欢的数 , 可能是 r>n 从上一个 whlie 循环退出来的
		for(ll i=1;i<=m;i++)
			if(p[i]&&!cnt[i])
				check=0;
		if(check){
			found=1;//标记一下找到了
			if(ansb>sumb||sumb==ansb&&anss<sum)//如果满足更新条件
				ansb=sumb,anss=sum,ansl=l,ansr=r-1;//更新 
		}
		for(ll i=1;i<=num[l];i++){//左端点往右移 , 把集合 l 的所有属性减掉 ( 可以和上面的右端点往右移对比一下 )
			cnt[c[l][i]]--;
			if(!p[c[l][i]])sumb--;
		}
		sum-=s[l]; 
		l++;//左端点 ++
	}
	if(!found) puts("-1");//没找到输出 -1 
	else cout<<ansl<<" "<<ansr<<endl;
}
/*
3 3 2
1 2
5 2 1 2
5 2 1 2
5 2 1 2
*/
```

求赞 $qwq$

---

## 作者：d3ac (赞：9)

嗯........A这道题很开心，我来分享一下我的考场思路：

首先注意，有3000个集合，但是数字却只有1000个，所以我们可以考虑思考从数字下手，然后考虑.....

然后我们想，怎么选择区间，使得覆盖掉所有的数字？
嗯？我们开一个vector，vector的下标表示的是数字，然后，后面记录的是它这个数字在那些区间出现过，读入区间是单调递增的，所以vector里面的元素是有序的(~~我知道你懂了~~)，然后，我们维护一个魔力值的前缀和，所以的话，我们就可以知道任意一个区间的魔力值之和，就可以处理“得剩余集合的魔力之和尽可能大”这个问题，hate数组记录的就是不喜欢的个数，同理就是了，解决“在剩余的集合中，他不喜欢的数的个数尽可能小”

好了，接下来的事情就是......vector中二分，枚举一个区间的左端点，然后枚举每一个数字，找到这个数字在那一个区间出现，这个区间....离左端点越近越好是吧.....所以二分，~~是不是显而易见~~，还有一句是为了处理使得魔力值更大，，下面看

给大家看看我的码子

------------
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define maxn 4000
#define inf 2000000
using namespace std;
int n,m,d,need[maxn],left,right;
long long love[maxn],hate[maxn],lastans=-1e17,lasthate=1e17;
bool book[maxn];
vector<int> v[maxn];
inline int read(){
	register int x=0,f=1; register char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int main()
{
	n=read(); m=read(); d=read();
	for(int i=1;i<=d;i++) need[i]=read(),book[need[i]]=true;//输入喜欢的数字并且标记 
	for(int i=1,temp,cnt,hated;i<=n;i++){
		temp=read(); cnt=read();
		love[i]=love[i-1]+temp;//维护魔力值的前缀和
		hated=0;
		for(int j=1;j<=cnt;j++){
			temp=read();//这个是数字 
			if(book[temp]) v[temp].push_back(i);//需要去重 
			else hated++;
		}
		hate[i]=hate[i-1]+hated;//维护讨厌的数字的前缀和 
	}
	for(int i=1;i<=d;i++) {
		if(v[need[i]].size()==0) printf("-1"),exit(0);
		v[need[i]].push_back(inf);
	}
	for(int i=1;i<=n;i++){//枚举区间的起点 
		int r=0;
		for(int j=1;j<=d;j++){//枚举每一个数字，保证被选中 
		    r=max(r,v[need[j]].at(lower_bound(v[need[j]].begin(),v[need[j]].end(),i)-v[need[j]].begin()));
		}
		if(r==inf) break;//后面的区间一定覆盖不完了 
		while(hate[r]==hate[r+1] && love[r]<love[r+1] && r!=n) r++;//尽量使r更大 
		long long nowans=love[r]-love[i-1];
		long long nowhate=hate[r]-hate[i-1];
		if(lasthate<nowhate) continue;
		if(lasthate!=nowhate){
			lasthate=nowhate;
			lastans=nowans,left=i,right=r;
		}
		else if(lastans<nowans) lastans=nowans,left=i,right=r;
	}
	lastans==-1e17? printf("-1\n"):printf("%d %d\n",left,right);
	return 0;
}
```
对了，set会被卡

---

## 作者：在想Peach (赞：2)

这题我好像想多了（~~就是~~）并且这份代码常数过大貌似重测的时候被卡t一个点，~~然后我就不要脸的吸氧又过了~~。

做法：

找每个点最近到那个点符合条件，发现具有单调性，套了个二分，用树状数组检查，再用二分特判一下接着往后走的情况（后面没有不喜欢的数也可加进来），然后找一个最优的输出。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
using namespace std;
const int maxn=5005;
int n,m,d,lk[maxn],x,y;
int t[maxn],unlike[maxn],usum[maxn];
bool c[maxn][maxn],like[maxn];
int tr[maxn][maxn],far[maxn];
int ans1,out;
long long ans2,sum[maxn];
int read()
{
	char z=getchar();int x=0,y=1;
	while(z<'0'||z>'9'){if(z=='-')y=-1;z=getchar();}
	while(z<='9'&&z>='0'){x=x*10+z-'0';z=getchar();}
	return x*y;
}
int lowbit(int x){return x&-x;}
void add(int here,int x){
	for(int i=x;i<=n;i+=lowbit(i))tr[here][i]+=1;
}
int quary(int here,int x){
	int ansl=0;
	for(int i=x;i;i-=lowbit(i))ansl+=tr[here][i];
	return ansl;
}
bool check(int l,int r)
{
	for(int i=1;i<=d;i++)
	{
		if(quary(i,r)-quary(i,l-1)==0)return 0;
	}
	return 1;
}
int main()
{
	n=read();m=read();d=read();
	for(int i=1;i<=d;i++)lk[i]=read(),like[lk[i]]=1;
	for(int i=1;i<=n;i++)
	{
		t[i]=read();x=read();
		for(int j=1;j<=x;j++)
		{
			y=read();
			if(like[y])c[i][y]=1;
			else unlike[i]++;
		}
		for(int j=1;j<=d;j++)
		{
			if(c[i][lk[j]])add(j,i);
		}
		usum[i]=usum[i-1]+unlike[i];
		sum[i]=sum[i-1]+t[i];
	}
	ans1=1e9+7;
	for(int i=1;i<=n;i++)
	{
		int l=i,r=n,ans=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(check(i,mid))ans=mid,r=mid-1;
			else l=mid+1;
		}
		far[i]=ans;
		if(far[i]==-1)continue;
		//
		l=far[i],r=n,ans=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(usum[mid]==usum[far[i]])ans=mid,l=mid+1;
			else r=mid-1;
		}
		far[i]=ans;
		//
		if(usum[far[i]]-usum[i-1]<=ans1)
		{
			if(usum[far[i]]-usum[i-1]<ans1)ans1=usum[far[i]]-usum[i-1],ans2=sum[far[i]]-sum[i-1],out=i;
			else if(sum[far[i]]-sum[i-1]>ans2)ans2=sum[far[i]]-sum[i-1],out=i;
		}
	}
	if(ans1!=1e9+7)printf("%d %d\n",out,far[out]);
	else printf("%d\n",-1);
	return 0;
}
```


---

## 作者：Eric1031 (赞：1)

 卡过去了。。。
 
 这道题目其实只要一个简单的dp就行了，在每个端点搜一次，搜到最优解便与已找到的解比一次就行了
 
 话不多说，上代码。
 ```
#include<bits/stdc++.h>
using namespace std;
int minn=10000,n,m,d,r,h,k,dis[3001],x,l;
long long maxx,sum[3001];
bool flag,f[3001][1001],c[3001][1001],b[1001],f1,b1[3001];
vector<int> v;
int main()
{
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1;i<=d;i++)
	{
		scanf("%d",&x);
		b[x]=1;//记录喜欢的数
		v.push_back(x);
	}
	for(int i=1;i<=n;i++)
	{
		k=0;
		scanf("%d",&x);
		sum[i]=sum[i-1]+x;
		scanf("%d",&h);
		for(int j=1;j<=h;j++)
		{
			scanf("%d",&x);
			if(x>=1&&x<=m)
			{
				if(!b[x]) k++;
				else
				{
					f[i][x]=1;
				 } 
			}
		}
		if(!k) b1[i]=1;//记录没有不喜欢的数的点
		dis[i]=dis[i-1]+k;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			f1=1;
			for(int p=0;p<v.size();p++)
			{
				c[i][v[p]]|=f[j][v[p]];
			}
			for(int p=0;p<v.size();p++)
			{
				if(!c[i][v[p]])
				{
					f1=0;
					break;
				}
			}
			if(f1)
			{
				while(b1[j+1])
					j++;//如果该点有不喜欢的数，加入它一定不是最优的，反之，加入则可提升魔力值，较原解更优
				if(((dis[j]-dis[i-1])<minn)||(((dis[j]-dis[i-1])==minn)&&((sum[j]-sum[i-1])>maxx)))
				{
					flag=1;
					minn=dis[j]-dis[i-1];
					maxx=sum[j]-sum[i-1];
					l=i;
					r=j;
				}
				break;
			}
		}
	}
	if(flag) printf("%d %d",l,r);
	else printf("-1");
 } 
```


---

## 作者：Melo_qwq (赞：0)

我们亲爱的 bitset 还是太神了。

我究竟是如何拿到最优解的。

考虑枚举区间右端点 $R$，直接从右往左扫一遍左端点，发现：

- 如果当前区间 $[L,R]$ 还没有包含所有喜欢的数字，必须往左扩展。
- 否则，如果当前集合有不喜欢的数字，这个集合一定不被加入我们枚举的区间里。
- 如果不符合上面两种情况，为了使魔力之和最大，这个集合一定是要加进来的。

那么就做完了，每个集合不喜欢数字的个数可以在输入的时候顺便算出来，喜欢的数字是否包含可以用 bitset 维护，总体复杂度 $\Theta(\frac{n^3}{w})$，如果写的比较优美可以做到 $\Theta(\frac{n^2m}{w})$。

跑不满，但是看起来比较极限，不过很快就跑过去了，而且好像比正解还快，bitset 还是太神了。

Code

```cpp
#include <bits/stdc++.h>
#define int long long 
#define f(i ,m ,n ,x) for (int i = (m) ; i <= (n) ; i += (x))

template < typename T > inline void read ( T &x ) {
    x = 0 ;
    bool flag (0) ; char ch = getchar () ;
    while (! isdigit (ch)) {
        flag = ch == '-' ;
        ch = getchar () ;
    } while (isdigit (ch)) {
        x = (x << 1) + (x << 3) + (ch ^ 48) ;
        ch = getchar () ;
    } flag ? x = - x : 0 ;
} template < typename T ,typename ...Args >
inline void read ( T &x ,Args &...tmp ) {
    read (x) ,read (tmp...) ;
}

const int N = 3007 ;
int n ,m ,d ,no[N] ,t[N] ,l ,r ,min = 0x3f3f3f3f ,max = 0 ;
bool yes[N] ;
std :: bitset < N > have[N] ,zero ,cur ; 

signed main () {
    read (n ,m ,d) ;
    f (i ,1 ,d ,1) {
        int p ; read (p) ;
        yes[p] = true ;
    }
    f (i ,1 ,n ,1) {
        int num ; read (t[i] ,num) ;
        f (j ,1 ,num ,1) {
            int c ; read (c) ;
            if (yes[c]) have[i][c] = true ;
            else no[i] ++ ;
        }
    }
    f (ed ,1 ,n ,1) {
        bool ok (0) ;
        cur &= zero ;
        int cant = 0 ,mo = 0 ,bef = 0 ;
        for (int st = ed ; st ; st --) {
            if (ok && no[st] == 0) mo += t[st] ;
            if (ok && no[st]) break ;
            if (! ok) {
                cur |= have[st] ;
                cant += no[st] ;
                mo += t[st] ;
                if (static_cast < int > (cur.count ()) == d) ok = true ; 
            } bef = st ;
        }
        if (ok) {
            if (cant < min) {
                l = bef ,r = ed ;
                min = cant ;
                max = mo ;
            } else if (cant == min && max < mo) {
                max = mo ;
                l = bef ,r = ed ;
            }
        }
    } if (! l) return puts ("-1") ,0 ;
    std :: cout << l << ' ' << r << '\n' ;
    return 0 ;
}
```

---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Solution]}}$

先统计出每个集合中我喜欢的数**各有**几个，以及我不喜欢的数**一共**有几个（至于每个我不喜欢的数各有几个我不关心）。

由于每个区间中我不喜欢的数至少都是 $0$ 个，所以在满足了条件 $1$ 的情况下，区间长度越大，这个区间会越不优。

所以，我们可以用**尺取法**（即 `Two-Pointers`）算法来求出满足条件的最小区间。

需要注意的是，如果 $[L,R]$ 是以 $L$ 为左端点的符合条件的最小区间，但是集合 $R+1$ 中没有我不喜欢的数，那么 $[L,R+1]$ 是优于 $[L,R]$（你可以认为因为 $t_{i}$ 都是大于 $0$ 的，集合 $R+1$ 没有任何副作用，不要白不要）。


至于说如何快速算出 $[L,R]$ 中**一共**有多少我不喜欢的数和法力值的总和，可以用**前缀和**求出。

还有一个地方，法力值的前缀和数组记得开 `long long`~~（当然不开他只会友善地扣你 $50$ 分）~~。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=3010,M=1010;
long long pret[N];//注意注意 
int Unlike[N],cnt[M],preu[N];
int Like[N][M],n,m,d,ansL,ansR;
map<int,int> p;//喜欢的数的编号 
inline void add(int u){
	for(int i=1;i<=d;i++)
		cnt[i]+=Like[u][i];
}
inline void del(int u){
	for(int i=1;i<=d;i++)
		cnt[i]-=Like[u][i];
}
inline bool check(){
	for(int i=1;i<=d;i++)
		if (!cnt[i]) return false;
	return true;
}
inline bool check(int l,int r){
	if (ansL==0) return true;
	if (preu[r]-preu[l-1]<preu[ansR]-preu[ansL-1])
		return true;//不喜欢的数更少 
	if (preu[r]-preu[l-1]>preu[ansR]-preu[ansL-1])
		return false;//不喜欢的数更多 
	if (pret[r]-pret[l-1]>pret[ansR]-pret[ansL-1])
		return true;//法力的和更大 
	return false;//再见吧次优解 
}
int main(){
	n=read();m=read();d=read();
	for(int i=1;i<=d;i++)
		p[read()]=i;
	for(int i=1;i<=n;i++){
		pret[i]=pret[i-1]+read();
		for(int j=1,q=read(),u;j<=q;j++){
			u=read();
			if (p[u]!=0) Like[i][p[u]]++;
			else Unlike[i]++;
		}
		preu[i]=preu[i-1]+Unlike[i];
	}
	for(int l=1,r=1;l<=n;l++){
		while (r<=n&&!check()) add(r++);
		while (r<=n&&Unlike[r]==0) add(r++);
//		没有副作用，不要白不要，要了法力和更大 
		if (check()&&check(l,r-1)) ansL=l,ansR=r-1;
		del(l);
	}
	if (ansL==0) printf("-1");
	else printf("%d %d",ansL,ansR);
	return 0;
}
```

---

