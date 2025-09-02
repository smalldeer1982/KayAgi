# Bessie's Birthday Cake (Hard Version)

## 题目描述

[Proof Geometric Construction Can Solve All Love Affairs - manbo-p](https://soundcloud.com/alice-law-314125270/manbo-p-proof-geometric-construction-can-solve-all-love-affairs)

⠀



This is the hard version of the problem. The only difference between the two versions is the constraint on $ y $ . In this version $ 0 \leq y \leq n - x $ . You can make hacks only if both versions are solved.

Bessie has received a birthday cake from her best friend Elsie, and it came in the form of a regular polygon with $ n $ sides. The vertices of the cake are numbered from $ 1 $ to $ n $ clockwise. You and Bessie are going to choose some of those vertices to cut non-intersecting diagonals into the cake. In other words, the endpoints of the diagonals must be part of the chosen vertices.

Bessie would only like to give out pieces of cake which result in a triangle to keep consistency. The size of the pieces doesn't matter, and the whole cake does not have to be separated into all triangles (other shapes are allowed in the cake, but those will not be counted).

Bessie has already chosen $ x $ of those vertices that can be used to form diagonals. She wants you to choose no more than $ y $ other vertices such that the number of triangular pieces of cake she can give out is maximized.

What is the maximum number of triangular pieces of cake Bessie can give out?

## 说明/提示

In test cases $ 1 $ , $ 2 $ and $ 3 $ , you can get $ 6 $ , $ 5 $ and $ 2 $ non-intersecting triangular pieces of cake, respectively. A possible construction is shown in the following pictures:

The green dots represent vertices that Bessie chose, the yellow dots represent vertices that you chose, the blue lines represent diagonals that are drawn, and the red numbers represent triangles that are counted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C2/1d0397b12ffc5a0058affa34960ac433601c6be3.png)

## 样例 #1

### 输入

```
3
8 4 2
1 6 2 5
7 3 1
6 4 3
4 2 2
1 3```

### 输出

```
6
5
2```

# 题解

## 作者：littlebug (赞：1)

## Solution

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C2/1d0397b12ffc5a0058affa34960ac433601c6be3.png)

做完这道题的 [Easy Version](/problem/CF1942C1) 后，这道题就简单多了。**这篇题解是在 Easy Version 的基础上写的**，将用到 [这篇题解](/article/eb1npo6o) 中的一些证明。

因为要使**选中的点的个数和**与**两个选中点相邻的点的个数**之和最大，所以考虑隔一个位置插一个点，这样所有操作对答案的贡献最大。设当前连续的一段没被选中的点的个数为 $k$，统计每次操作的贡献。

- 若 $k$ 为偶数，易证明选一个点贡献 $+2$。
- 若 $k$ 为奇数，那么选一个点贡献 $+2$，直到最后只剩 $3$ 个点的时候，贡献 $+3$。例如在样例 #2 中，点 $1$ 所在的连续段长度为 $3$（即 $k=3$），所以选中点 $1$ 可以使点 $1$ 左右两边的点都对答案产生贡献，再加上点 $1$ 自身，于是贡献 $+3$。

所以可以考虑贪心，统计所有奇数段，从小到大排序，再依次操作直到 $y=0$ 或没有奇数段了，这时把剩下的 $y$ 给偶数段就可以，偶数段贡献 $=y \times 2$。

注意最后要对贡献取 $\min(n,cnt)$ 就好了。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define il inline
#define pb emplace_back
using namespace std;
const int MAXN=2e5+5;
int n,x,y;
int a[MAXN];
vector <int> eve;
il void solve()
{
	eve.clear();
	cin>>n>>x>>y;
	for(int i=1;i<=x;++i)
		cin>>a[i];
	sort(a+1,a+x+1);
	int cnt=x; //cnt 为最终选定的点数 
	for(int i=2;i<=x;++i)
	{
		if(a[i]-a[i-1]-1==0)
			continue;
		if(a[i]-a[i-1]-1==1)
			++cnt;
		else
		{
			if((a[i]-a[i-1]-1)&1)
				eve.pb(a[i]-a[i-1]-1);
		}
	}
	if(a[1]+n-a[x]-1==1)
		++cnt;
	else
	{
		if((a[1]+n-a[x]-1)&1)
			eve.pb(a[1]+n-a[x]-1);
	}
	sort(eve.begin(),eve.end());
	for(int i:eve) //奇数段 
	{
		if(y>=i/2)
			y-=i/2,cnt+=i;
		else
			cnt+=y*2,y=0;
		if(!y) break;
	}
	cnt=min(n,cnt+y*2); //偶数段 
	cout<<cnt-2<<'\n'; //最后要 -2 
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

在 Hard 版本中，你可以多指定 $y$ 个点。我们将单分成两部分。前面 $x$ 个点的答案和剩下 $y$ 个点的答案。

前面 $x$ 个点就是 Easy 版本。后面的 $y$ 个点，我们徐亚把他们放在这 $x$ 个点之间的间隔中，并让答案最大。

我们发现在这 $x$ 个点中，若两个点之间的距离 $\ge2$，会有 $\displaystyle\frac{d}{2}$ 可以放置。对于前面放置的点，答案会增加 $2$。最后一个点，若答案为奇数，则答案会增加 $3$，因为这个点离相邻的两个点距离都是 $2$。否则答案还是增加 $2$。

所以我们预处理出相邻的点之间的距离，根据距离的奇偶性为第一关键字，大小为第二关键字（更小的排在前面），进行排序。最后贪心即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,a[200005],d[200005];
bool cmp(int x,int y)
{
  bool u=((x+1)%2==0),v=((y+1)%2==0);
  if(u==0&&v==1) return 0;
  if(u==1&&v==0) return 1;
  return x<y;
}
void solve()
{
  int ans=0;
  cin>>n>>x>>y;
  for(int i=1;i<=x;i++) cin>>a[i];
  sort(a+1,a+x+1);
  ans=x-2;
  for(int i=1;i<=x;i++)//Easy 版本的答案
  {
    int now=a[i]+2,now1=i+1;
    if(now>n) now-=n;
    if(now1>x) now1-=x;
    if(now==a[now1]) ans++;
  }
  for(int i=1;i<=x;i++)//预处理距离
  {
    if(i<x) d[i]=a[i+1]-a[i]-1;
    else d[i]=a[1]+n-1-a[x];
  }
  sort(d+1,d+x+1,cmp);
  for(int i=1;i<=x;i++)
  {
    if(d[i]<=1) continue;
    if(y>=d[i]/2-1) y-=d[i]/2-1,ans+=(d[i]/2-1)*2;//前面的点
    else ans+=y*2,y=0;//不够放了，全部放置，赛时 y=0 和 ans+=y*2 打反了，没调出来（）
    if(d[i]&1)//距离为奇数
    {
      if(y>0) y--,ans+=3;
    }
    else
    {
      if(y>0) y--,ans+=2;
    }
  }
  cout<<ans<<"\n";
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：Angela2022 (赞：0)

## CF1942C2题解

观察一下简单版本：  
首先，在这 $x$ 个被选中的点内部，可以形成 $x-2$ 个三角形（如图中Test Case 1的1、2号三角形）。  
而对于剩下的点，如果有两个被选中的点之间夹了一个点，且所夹的点没有被选中，那么会额外增加一个三角形（如图中Test Case 3的1、2号三角形）。  
![](https://cdn.luogu.com.cn/upload/image_hosting/2miusrq7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

于是我们把这选中的 $x$ 个点从前往后遍历，如果第 $i$ 个点与 $i- 1$ 个点相减为二（即他们中间夹了一个点），那么将答案加一，注意还要特判一下第1个点和第 $x$ 个点之间是否也夹了一个点。最后将答案加上 $x-2$ 即可。

那么，如果我们可以加 $y$ 个点，怎么加最优呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/vhz9nc6l.png?x-oss-process=image/resize,m_lfit,h_170,w_225)![](https://cdn.luogu.com.cn/upload/image_hosting/g31b00ip.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

观察样例1，我们发现这是在两个相隔两个未选点的已选点之间，添加1个点把原来的四边形全切成三角形。观察样例2，发现这是在两个相隔三个未选点的已选点之间，添加1个点把原来的五边形全切成三角形。  
我们称一个由两个已选点和他们中间的未选点组成的图形为“基本图形”，称其中未选点的个数为“基本图形的大小”。  
然后我们发现，如果要把一个基本图形**全部**切成三角形，那么至少要在未选点中**隔一个选一个点**作为新加的点。设基本图形的大小为 $k$ 。若 $k$ 为奇数，那么至少要添加 $\frac{k - 1}{2}$ 个点才能把这个基本图形**全**切成三角形，也就是说切出 $k$ 个三角形；若 $k$ 为偶数，那么至少要添加 $\frac{k}{2}$ 个点才能把这个基本图形**全**切成三角形，也就是说切出 $k$ 个三角形。  
那么如果剩下的 $y$ 已经不足以把一个基本图形全切成三角形怎么办呢？此时我们只能贪心地取，每添加一个点相当于添加两个三角形，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gdh18g5u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们发现，无论是把一个偶数大小的基本图形**全**切成三角形，还是把一个基本图形**不完全**地切成三角形，每加一个新点，至多只能产生两个新三角形。而如果把一个**奇数**大小的基本图形**全**切成三角形，最后一次加新点时相当于产生了三个新三角形。也就是说，我们希望完全切成三角形的奇数大小的基本图形尽可能多。  
由于每次只添加一个新点，那么我们可以贪心：把所有的基本图形以大小的奇偶性为第一关键字（奇数在前），大小为第二关键字（小的在前）排序（假设我们切完了一个奇数大小的基本图形，却没有把一个比他小的奇数大小基本图形，那么我们可以先切完小的那个来获取不劣的答案）。依次往后，如果当前的基本图形可以全切成三角形就全切，否则按照上文所说方式贪心地加点。时间复杂度 $O(x)$ 。

### Code  
```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int t,n,x,y,a[N],d[N],CNT;
bool cmp(int p,int q){
    if(p%2!=q%2)return p%2>q%2;
    return p<q;
}
signed main(){
    cin>>t;
    while(t--){
        cin>>n>>x>>y;
        for(int i=1;i<=x;i++)cin>>a[i];
        sort(a+1,a+x+1);
        int cnt=0;CNT=0;
        a[++x]=a[1]+n;
        for(int i=2;i<=x;i++){
            if(a[i]-a[i-1]==2){cnt++;}
            if(a[i]-a[i-1]>2){d[++CNT]=a[i]-a[i-1]-1;}
        }
        x--;
        sort(d+1,d+CNT+1,cmp);
        for(int i=1;i<=CNT;i++){
            if(d[i]%2==1){
                int k=d[i]/2-1;
                if(y>k){y-=k+1;cnt+=k*2+3;}
                else{cnt+=y*2;y=0;break;}
            }
            else{
                int k=(d[i]/2);
                cnt+=min(y,k)*2;y-=min(y,k);
            }
            if(y<=0)break;
        }
        cnt+=x-2;
        cout<<cnt<<endl;
    }
    return 0;
}
```

蒟蒻的第一篇题解，如有错误请大佬随时指出，谢谢！

---

## 作者：AK_400 (赞：0)

C1 中发现结论：若一个点未被选中，但它的相邻两个点均被选中，那么这个点对答案有贡献。

于是我们对于一个未被选中的点的连续段（下简称段），肯定是间隔着放点最优，但是如果这个段的长度是偶数，那么必定有一个和旁边的点挨着，很浪费，所以先放奇数。

对于长度为奇数的段，如果不放满，那么也会有浪费，如图（右边的三个点都没有贡献）：![](https://cdn.luogu.com.cn/upload/image_hosting/zuybmjp0.png)

所以有了这样一个贪心：对于连续段，能选奇数选奇数，能选小的就选小的，能放满就放满。

计算答案时，如果没放满，那么每放一个点，就有两个点做出贡献，否则整段都有贡献。

复杂度：排序 $O(n\log n)$，计算答案 $O(n)$。


```cpp
    #include<bits/stdc++.h>
    #define int long long
    using namespace std;
    int n,x,y,d[200005],len[200005],le[200005],tote,lo[200005],toto,boto,bote;
    void slv(){
        for(int i=1;i<=toto;i++)lo[i]=0;
        for(int i=1;i<=tote;i++)le[i]=0;
        toto=tote=0;
        cin>>n>>x>>y;
        for(int i=1;i<=x;i++)cin>>d[i];
        int ans=x-2;
        sort(d+1,d+1+x);
        for(int i=2;i<=x;i++){
            len[i]=d[i]-d[i-1]-1;
        }
        len[1]=n-d[x]+d[1]-1;
        sort(len+1,len+1+x);//从小到大选
        for(int i=1;i<=x;i++){
            if(len[i]%2==0)le[++tote]=len[i];
            else lo[++toto]=len[i];
        }
        for(boto=1;boto<=toto;boto++){//先奇数再偶数
            if(y<lo[boto]/2)break;
            y-=lo[boto]/2;//尽量放满
            ans+=lo[boto];
        }
        if(boto<=toto){
            cout<<ans+y+y<<endl;
            return;
        }
        for(bote=1;bote<=tote;bote++){
            // cout<<le[bote]<<endl;
            if(y<le[bote]/2)break;
            ans+=le[bote];
            y-=le[bote]/2;
        }
        if(bote<=tote){
            cout<<ans+y+y<<endl;
            return;
        }
        cout<<ans<<endl;
        return;
    }
    signed main(){
     
        int T;
        cin>>T;
        while(T--)
        slv();
        return 0;
    }
```

---

## 作者：HasNoName (赞：0)

### 思路

先求出不加点的情况下的答案，再加上新加点和已有点或新加点组成的三角形个数。

在两点之间距离为偶数的情况下选点，一定比两点之间距离为奇数的情况下选点优。因为两点之间距离为奇数的情况下选点每选一个点加一个三角形，但两点之间距离为偶数的情况下选点，有一个点还会增加两个三角形。

当两点距离为偶数时，设距离为 $2\times k$，则选 $k-1$ 个点，可以增加 $k$ 个三角形。所以距离越小时越优，对偶数排序。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,k;
int a[N],b[N],c[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>k;
        int ans=max(m+k-2,0);
        for(int i=1;i<=m;i++)
        {
            cin>>a[i];
        }
        sort(a+1,a+m+1);//对点排序
        int l=0,r=0;
        for(int i=1;i<m;i++)
        {
            if(a[i+1]==a[i]+2)
                ans++;
            else if(a[i+1]-a[i]>1)
            {
                if((a[i+1]-a[i])&1)c[++r]=a[i+1]-a[i];
                else if(a[i+1]-a[i]>2)b[++l]=a[i+1]-a[i];//奇偶分类
            }
        }
        if((a[m]+2)%n==a[1])//奇偶分类
            ans++;
        else if(a[1]+n-a[m]>1&&m)
        {
            if((a[1]+n-a[m])&1)c[++r]=a[1]+n-a[m];
            else if(a[1]+n-a[m]>2)b[++l]=a[1]+n-a[m];
        }
        sort(b+1,b+l+1);
        for(int i=1;i<=l;i++)//间隔为偶数偶数
        {
            if(k==0)break;
            if(k>=b[i]/2-1)
            {
                k-=b[i]/2-1;
                ans+=b[i]/2;
            }
            else
            {
                ans+=k;
                k=0;
                break;
            }
        }
        for(int i=1;i<=r;i++)//间隔为奇数
        {
            if(k==0)break;
            if(k>=c[i]/2)
            {
                k-=c[i]/2;
                ans+=c[i]/2;
            }
            else
            {
                ans+=k;
                k=0;
                break;
            }
        }
        if(k)ans-=k;//多的点由于无法增加三角形，且之前计算过，所以减去
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：hyman00 (赞：0)

### 题意

有一个正 $n$ 边形的蛋糕，目前有 $x$ 个关键点为顺时针的第 $a_i$ 个，你可以再添加 $y$ 个关键点，然后在关键点之间连边，边不相交，最大化分出的三角形个数。

$4\le n\le 10^9,2\le x\le \min(n,2\times 10^5),0\le y\le n-x$ 

在 C1 中，有 $y=0$ 

### C1 做法

关键点的位置是固定的。

我们令 $d_i$ 为第 $i$ 个和下一个顺时针上的距离，不难发现答案为 $x-2+\sum_{i}[d_i=2]$。

解释下，就是这 $x$ 个点构成了一个 $x$ 边形，能分出 $x-2$ 个，外面如果距离恰好为 $2$ 会多一个。

复杂度 $O(n\log n)$，瓶颈在于排序。

### C2 做法

考虑 C1 中的 $d_i=2$ 的情况，其实就是说中间跨过的点也有可能成为某个三角形的顶点，即答案为可能是**可能成为某个三角形的顶点**的顶点个数减二。

一开始这样的点数我们是知道的，考虑继续标记一个点带来的贡献。

- $d=2k(k>1)$ 

可以一个隔一个地标记，标记 $x(x<k)$ 个的贡献是 $2x$，另外如果恰好 $k-1$ 可以有额外的一个贡献.

- $d=2k-1(k>0)$

同上，但是不会有额外贡献。

综上，前一种情况更优。把 $\set{d_i}$ 按奇偶性分别从小到大排序，贪心地先选偶数再选奇数，可以证明是最优的。

复杂度也是 $O(n\log n)$。

### 赛时代码

```c++
int n,x,y;
int a[200005];
int d[200005];
vi v0,v1;
void run(){
	cin>>n>>x>>y;
	rep(i,x)cin>>a[i];
	sort(a,a+x);
	rep(i,x-1)d[i]=a[i+1]-a[i];
	d[x-1]=a[0]+n-a[x-1];
	v1.clear();
	v0.clear();
	rep(i,x){
		if(d[i]&1)v1.pb(d[i]);
		else v0.pb(d[i]);
	}
	int s=x-2;
	sort(all(v0));
	sort(all(v1));
	for(int i:v0){
		if(i==2){
			s++;
		}
		else{
			if(y>=i/2-1){
				y-=i/2-1;
				s+=i-1;
			}
			else{
				s+=y*2;
				y=0;
			}
		}
	}
	for(int i:v1){
		if(y>=i/2){
			y-=i/2;
			s+=i-1;
		}
		else{
			s+=y*2;
			y=0;
		}
	}
	cout<<s<<"\n";
}
```

---

