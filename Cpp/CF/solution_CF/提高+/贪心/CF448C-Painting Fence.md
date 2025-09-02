# Painting Fence

## 题目描述

Bizon the Champion isn't just attentive, he also is very hardworking.

Bizon the Champion decided to paint his old fence his favorite color, orange. The fence is represented as $ n $ vertical planks, put in a row. Adjacent planks have no gap between them. The planks are numbered from the left to the right starting from one, the $ i $ -th plank has the width of $ 1 $ meter and the height of $ a_{i} $ meters.

Bizon the Champion bought a brush in the shop, the brush's width is $ 1 $ meter. He can make vertical and horizontal strokes with the brush. During a stroke the brush's full surface must touch the fence at all the time (see the samples for the better understanding). What minimum number of strokes should Bizon the Champion do to fully paint the fence? Note that you are allowed to paint the same area of the fence multiple times.

## 说明/提示

In the first sample you need to paint the fence in three strokes with the brush: the first stroke goes on height 1 horizontally along all the planks. The second stroke goes on height 2 horizontally and paints the first and second planks and the third stroke (it can be horizontal and vertical) finishes painting the fourth plank.

In the second sample you can paint the fence with two strokes, either two horizontal or two vertical strokes.

In the third sample there is only one plank that can be painted using a single vertical stroke.

## 样例 #1

### 输入

```
5
2 2 1 2 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
2 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
5
```

### 输出

```
1
```

# 题解

## 作者：wmy_goes_to_thu (赞：21)

话说这是 NOIP2018T1……

这道题肯定是贪心呀，每次在区间内选择最小点，整个区间都减一下这个值，分成若干个子区间进行处理。

但是，这道题说可以竖着刷，所以每次横着涂和竖着涂需要比较！否则会 WA 的！

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int a[100005];
int go(int l,int r)
{
	if(l<1||r<1)return 0;
	if(l>r)return 0;
	if(l==r)return min(a[l],1);
	int m=1111111111,w=0;
	for(int i=l;i<=r;i++)
		if(a[i]<m)
		{
			m=a[i];
			w=i;
		}
	int j=a[w];
	for(int i=l;i<=r;i++)
		a[i]-=j;
	int lf=go(l,w-1);
	int rg=go(w+1,r);
	return min(j+lf+rg,r-l+1);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int ans=min(n,go(1,n));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：colemak (赞：10)

看到这题没人发题解我就发一篇吧。主要算法就是分治，带一点贪心的思想；

首先如果要横着涂，那么该行下面都一定是横着涂的，否则该行在竖着涂时有更优解；其次，每一次涂都一定涂到当前能涂的最大长度。

当然，如果这样贪心的话只有70分左右。有的时候横着涂不一定是最优解，因为横着涂的话可能会产生一些不连通的小块，使我们要浪费很多步数，此时竖着涂可能更优，因此在分治返回值时要在两者中取最小值。对于这些剩下来的小块，再按同样的策略分治，边界条件则是当l==r时return 1。复杂度大概为O(n^2)

以下放代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
using namespace std;
const int N=5010;
typedef long long int ll;
const ll INF=0x7fffffffff;///注意，此处INF值一定要极大
ll h[N],n;//并且变量开longlong，否则会RE
inline ll read()
{
	ll x=0,t=1;char ch=getchar();
	while((ch<'0' || ch>'9') && ch!='-')ch=getchar();
	if(ch=='-')t=-1,ch=getchar();
	while(ch>='0' && ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*t;
}//如果要打快读，记得开longlong函数。。惨痛的教训。
ll slove(int l,int r,ll hi)//l为左边界，r为右边界，hi为已经涂掉的高度
{
	ll minh=INF;
	FOR(i,l,r)minh=min(minh,h[i]);//当前区间最低高度
	if(l==r)return 1;//边界条件
	ll ans=minh-hi;//如果全部横着涂
	int j;//j在循环外面定义，因为跳出循环后还要调用它进行分治
	FOR(i,l,r)//横着涂时要加上被分离的小区间
	{
		if(h[i]==minh)continue;//如果该点没有露出部分则跳过
                                //以此确定露出部分左边界
		for(j=i;j<=r;j++)
        if(h[j+1]==minh || j==r)break;//当右边没有露出或已到右边界跳出循环，确定有边界
		ans+=slove(i,j,minh);//加上切露出部分的费用
		i=j+1;//i从之前的右边界开始，虽然两层循环复杂度实际只有O（n）
	}
	return min(ans,ll(r-l+1));//横着涂与竖着涂取最小值
}
int main()
{
	n=read();
	FOR(i,1,n)h[i]=read();
	cout<<slove(1,n,0)<<endl;
	return 0;
}
```

---

## 作者：hater (赞：7)

这题被选做模拟赛的第二题

联想到积木大赛 + 看到AC人士的时间复杂度为0ms

打比赛时一直在想O(n)算法

讲评竟然是递归+分治 ~~晕~~

先看题目吧

在若干次横刷后 有些栅栏剩余刷的次数会为0 

0 相当于一个间隔 把原来的区间分成若干个区间

这样分析后 看代码会好理解一点

注释比较详尽

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5005],n;
inline int min(int A,int B)
{
	if(A>=B) return B;
	return A; 
}
int dfs(int L,int R)
{
	if(L>R) return 0;
	//区间大小<1 不需要任何操作 
	if(L==R) return min(1,a[L]); 
	//这里 要么1次刷完 要么它剩余刷的次数为0 不要刷的 
	int tot=0,las=L-1,les=a[L]; 
	// las表示上一次0的位置 
	// les是区间的最小值 
	// tot表示 L ~ R 刷完要的最少执行次数 
	for(int i=L+1;i<=R;i++) les=min(les,a[i]);
	 //要刷就要尽量的刷  
	for(int i=L;i<=R;i++)
	{
		a[i]-=les;
		//刷掉 
		if(!a[i])
		  tot+=dfs(las+1,i-1),las=i; 
		//如果a[i]为零  上一次为零的位置+1 这次为零的位置-1
		//别忘记更新las的值 
	} tot+=dfs(las+1,R); 
	//手动执行一遍会发现 las+1 ~ R 的区间尚未执行
	//很好理解  函数只会在发现0才会递归
	return min(tot+les,R-L+1);
	// 还有一种选择 区间内每个栅栏都一个个刷
	// tot 别忘记加上横着刷的次数  
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cout<<dfs(1,n)<<endl;
	return 0;
}
//其他的不解释 
```




---

## 作者：Tony_Peter (赞：6)

第一眼看我就jio得这题和[NOIP2018D1T1](https://www.luogu.org/problemnew/show/P5019)好像的啦？

然后就直接打了差不多的过了样例，后来搞了一会儿其他几道题再回来看，发现好像没那么简单

……于是我突然发现这题会有竖着涂的情况啊……然后就加了一个比较，再然后……就AC了？QWQ

虽然说正解是分治算法……我也不知道我这算不算……就偷懒一下直接放一波我自己的代码吧
```cpp
#include<bits/stdc++.h>
#define ll long long
#define go(i,a,b) for(register ll i=a;i<=b;i++)
using namespace std;
const ll N=5002;
ll n,h[N];
inline ll fr(){
	ll w=0,q=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') q=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		w=(w<<1)+(w<<3)+ch-'0',ch=getchar();
	return w*q;
}
inline ll minn(ll l,ll r){//找到一段连续的栅栏中的最小高度
	ll mi=1e9;
	go(i,l,r)
		mi=min(h[i],mi);
	return mi;
}
inline ll work(ll l,ll r){
	//cout<<l<<" "<<r<<" ans="<<ans<<endl;
	if(r<l||(l==r&&h[l]==0)) return 0;
	if(l==r){//如果只剩下一个栅栏则一次就可以涂完(竖着涂)
		h[l]=0;
		return 1;
	}
	ll mi=minn(l,r),num=l,ans=mi;//ans记录当前所需要涂的次数
	go(i,l,r){
		h[i]-=mi;//减去涂了的部分
		if(h[i]==0){//如果这个栅栏涂完了
			ans+=work(num,i-1);//那么就把中间一段栅栏单独拿出来涂
			num=i+1;//记录断点
		}
	}
	ans+=work(num,r);//最后可能还有一段剩余，不能忘了
	if(ans>r-l+1)//如果这样横着涂比竖着涂要次数多就竖着涂
		return r-l+1;
	else return ans;
}
int main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	n=fr();
	go(i,1,n)
		h[i]=fr();
	printf("%lld\n",work(1,n));
}

```

---

## 作者：白木偶君 (赞：4)

###### 考虑横着涂一次的情况，那么有两个显而易见的事实。
###### 这次涂色长度必须尽可能大。
###### 在这次涂色区域的下方，必定都是横着涂的。
所以，对于一串栅栏h_1,h_2,…,h_n，如果要横着涂，就必定要从底向上涂min⁡{h_1,h_2,…,h_n}次。这样以后，
h_1,h_2,…,h_n就会分成若干不连通的子局面。


```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n;int h[5001];
int solve(int l,int r,int lh)
//令Solve(l,r,h)代表[l,r]这段栅栏，已经从下向上涂了h格的答案。
//令 h^'=min⁡{h_1,h_2,…,h_n}
{
	if(l==r)return 1;//边界情况：l=r 时，答案显然为1。
	if(l>r)return 0;
	int res=0,minh=1e9,la=l-1;
	for(int i=l;i<=r;i++)
	minh=min(minh,h[i]);
	res=minh-lh;
	for(int i=l;i<=r;i++)
	if(h[i]==minh)
	res+=solve(la+1,i-1,minh),la=i;
	res+=solve(la+1,r,minh);//分治
	return min(res,r-l+1);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&h[i]);
	printf("%d",solve(1,n,0));
}
```

---

## 作者：crh1272336175 (赞：3)

看了这么多题解，都是$O(n²)$的复杂度，我就来水一波题解，来个线段树的

不过这次线段树记录的是最小值的下标，而不是最小值

解释都写在注释里了

代码：

```cpp
#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1//宏定义左儿子和右儿子
#pragma GCC optimize(2) 
using namespace std;
typedef long long ll;
const int M=100005;
ll n;
ll h[M],t[M*4];
void build(ll p,ll le,ll ri)//线段树的建树 
{
    if(le==ri) 
    {
        t[p]=le;//本次线段树建立的是下标，而不是值 
        return;
    }
    ll mid=le+ri>>1;
    build(ls,le,mid);
    build(rs,mid+1,ri);
    if(h[t[ls]]<=h[t[rs]]) t[p]=t[ls];
    else t[p]=t[rs];
}
ll query(ll p,ll le,ll ri,ll x,ll y)//线段树的区间询问 
{
    if(le==x && ri==y) return t[p];
    int mid=le+ri>>1,res;
    if(y<=mid) res=query(ls,le,mid,x,y);//整段都在左边 
    else if(x>mid) res=query(rs,mid+1,ri,x,y);//整段都在右边 
    else 
	{
		int x1=query(ls,le,mid,x,mid);
		int x2=query(rs,mid+1,ri,mid+1,y);
		if(h[x1]<=h[x2]) res=x1;
		else res=x2;
	}
    return res;
}
ll dfs(ll le,ll ri,ll hh)
{
    if(le>ri) return 0;//如果只有一个格子，竖着涂一次就可以 
    ll pos=query(1,1,n,le,ri);
	ll hor=dfs(le,pos-1,h[pos])+dfs(pos+1,ri,h[pos])+h[pos]-hh;//左半段递归+右半段递归+下方横着涂的部分 
	ll upright=ri-le+1;//竖着涂的部分 
    return min(hor,upright);
}
int main()
{
    scanf("%lld",&n);
    for(register ll i=1; i<=n; i++) scanf("%lld",&h[i]);
    build(1,1,n);
    printf("%lld",dfs(1,n,0));
    return 0;
}
```


---

## 作者：OIer_hsy (赞：2)

这道题有典型的**分治思想**，具体来说，就是从最低端往上扫，找出在当前（l，r）区间的最小高度，ans加上最小高度，加上递归l，r的结果。

**边界情况**，当l=r 返回值为1。

**同时**，注意当r-l+1>ans时，返回的不是ans而是r-l+1;

递归过程就在下面

```cpp
ll solve(int l,int r,ll h){//递归的初始值为（1,n,0）;
	if (l==r) return 1;
	ll ans,minh=inf;
	FOR(i,l,r) minh=min(minh,hh[i]);
	ans=minh-h;
	FOR(i,l,r){
		int k;
		if (hh[i]==minh) continue;//如果当前这块栅栏已经被覆盖，就继续
		FOR(j,i,r) {
			k=j;//找出最右边界
			if (j==r||hh[j+1]==minh) break;//连续的一段已经结束
                                           //记录点，跳出
		}
		ans+=solve(i,k,minh);//递归求如果横扫，结果是多少
		i=k+1;
	}
	ll ans1=r-l+1;//考虑特别情况，纵切比横切更优。
	return min(ans1,ans);
}
```

主程序很简单，就不写了，只需输入数据，cout<<solve(1,n,0)即可。

---

