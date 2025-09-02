# Phoenix and Socks

## 题目描述

To satisfy his love of matching socks, Phoenix has brought his $ n $ socks ( $ n $ is even) to the sock store. Each of his socks has a color $ c_i $ and is either a left sock or right sock.

Phoenix can pay one dollar to the sock store to either:

- recolor a sock to any color $ c' $ $ (1 \le c' \le n) $
- turn a left sock into a right sock
- turn a right sock into a left sock

The sock store may perform each of these changes any number of times. Note that the color of a left sock doesn't change when it turns into a right sock, and vice versa.

A matching pair of socks is a left and right sock with the same color. What is the minimum cost for Phoenix to make $ n/2 $ matching pairs? Each sock must be included in exactly one matching pair.

## 说明/提示

In the first test case, Phoenix can pay $ 2 $ dollars to:

- recolor sock $ 1 $ to color $ 2 $
- recolor sock $ 3 $ to color $ 2 $

 There are now $ 3 $ matching pairs. For example, pairs $ (1, 4) $ , $ (2, 5) $ , and $ (3, 6) $ are matching.In the second test case, Phoenix can pay $ 3 $ dollars to:

- turn sock $ 6 $ from a right sock to a left sock
- recolor sock $ 3 $ to color $ 1 $
- recolor sock $ 4 $ to color $ 1 $

 There are now $ 3 $ matching pairs. For example, pairs $ (1, 3) $ , $ (2, 4) $ , and $ (5, 6) $ are matching.

## 样例 #1

### 输入

```
4
6 3 3
1 2 3 2 2 2
6 2 4
1 1 2 2 2 2
6 5 1
6 5 4 3 2 1
4 0 4
4 4 4 3```

### 输出

```
2
3
5
3```

# 题解

## 作者：Gokix (赞：7)

[CF1515D](https://www.luogu.com.cn/problem/CF1515D)

一道蛮有意思的题

------------

在本题解中，记左袜子为 $a_i$，右袜子为 $b_i$。一开始，左袜子数记作 $L$，右袜子数记作 $R$。

------------

把袜子存入数组 $a$、$b$ 中。

首先可以把已经配对的（同色同左右）袜子从数组中删去了。具体操作十分简单，这里不详细说明。

删完后我们的 $a$、$b$ 数组满足以下性质：$\min(a_i,b_i)=0 \space (1 \le i \le \max(L,R))$。简单来说就是对于任意颜色的袜子，要么左袜子没了，要么右袜子没了，要么左右袜子都没了。

接下来我们要转换袜子，一共有三种情况：

1. 有两只同色同左右的袜子，我们可以花费1元把它俩其中之一的左右改变，形成配对。

![1](https://cdn.luogu.com.cn/upload/image_hosting/46n8ccud.png)

2. 有两只不同色不同左右的袜子，我们可以花费1元使得他俩同色，形成配对。

![2](https://cdn.luogu.com.cn/upload/image_hosting/cnl20q2x.png)

3. 有两只不同色同左右的袜子，我们至少要花2元配对他俩。

![3](https://cdn.luogu.com.cn/upload/image_hosting/378cjw44.png)

显然我们想让情况3尽可能少出现。

那么到底何时会出现情况3呢？

考虑有两堆异色同左右个数均为奇数的袜子，则每一堆中袜子按情况1两两配对，最后两堆各剩下1只袜子。此时就会出现情况3。

知道了这个，本题就好解了。

------------

暴力分类讨论。

现在，记 $u$ 为左袜子的个数和，$v$ 为右袜子的个数和，$conu$ 为个数为奇数的左袜子堆数，$conv$ 为个数为奇数的右袜子堆数。

1. 若 $u=v$：

	全部按情况2计算，没有情况3，答案就是 $u$。
    
2. 若 $u>v$（$v>u$ 同理）：

	a.若 $v>=conu$：
    	
	考虑右袜子一定可以按照情况1或情况2把 $conu$ 的部分配对完，剩余的左袜子一定是情况1。没有情况3，答案是 $\frac{u+v}{2}$。
    
    b.若 $v<conu$：
    
    必然会出现情况3，答案是右袜子全部按情况1或2配对的花费 $v$，加上左袜子按情况1部分的花费 $u-conu$，加上必然按情况3配对的花费 $2 \times \frac{conu-v}{2}$.整理得答案为 $\frac{u+conu}{2}$.

------------

有了分类讨论的结果，代码自然而然就出来了。

CODE:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
long long t,n,l,r,ans,a[200010],b[200010],conu,conv;

void init(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	ans=0;
}

int main(){
	long long i,j,u,v;
	cin>>t;
	while(t--){
		init();
		cin>>n>>l>>r;
		for(i=1;i<=l;i++){
			cin>>u;
			a[u]++;
		}
		for(i=1;i<=r;i++){
			cin>>u;
			b[u]++;
		}
		for(i=1;i<=n;i++){//去除本来就配对的
			if(a[i]>b[i]){
				a[i]-=b[i];
				b[i]=0;
			}
			else{
				b[i]-=a[i];
				a[i]=0;
			}
		}
		u=v=conu=conv=0;
		for(i=1;i<=n;i++){
			u+=a[i];
			conu+=a[i]%2;
			v+=b[i];
			conv+=b[i]%2;
		}
		if(u==v){//没有情况3
			ans=u;
		}
		else if(u>v){
			if(v>=conu){//也没有情况3
				ans=(u+v)/2;
			}
			else{//必然有情况3
				ans=(u+conu)/2;
			}
		}
		else{//v>u与u>v同理
			if(u>=conv){
				ans=(u+v)/2;
			}
			else{
				ans=(v+conv)/2;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：45dino (赞：3)

题目大意：

- 给定 $n$ 只袜子，其中有 $l$ 只左袜子，$r$ 只右袜子，每只袜子都有一个颜色。

- 每次操作可以将一只袜子的左右属性进行切换或更换一只袜子的颜色。

- 求把所有袜子都两两配对的最少操作次数。

- $2≤n≤2\times 10^5$

分析：

要分成三个阶段：首先，先将能配对的配上，此时对于一种颜色的袜子，要么全是左袜子，要么全是右袜子。此时没有花费。

接着，再改变某些袜子的颜色，使得要么全是左袜子，要么全是右袜子。如果一种颜色的袜子的只数大于1，就可以把一半的左右属性切换。这样每一种颜色的袜子的只数不多于1只。此时每次配对花费一次操作。

最后，同时改变袜子的颜色和左右，每次配对花费两次操作。

实现时可以将两种袜子的数列放在一个数组里，用下标0和1区分，这样比较好写。

[赛时代码](https://codeforces.com/contest/1515/submission/114926182)

比赛结束后，本蒟蒻看到了一位大佬的代码，很受启发！！111，给大家分享一下

[参考代码](http://codeforces.com/contest/1515/submission/114883138)

其中有一段我觉得写的挺好：
```
	for (int i=1; i<=n; i++)
	{
		while(tab[i][0]>1 && x>0)
		{
			x-=2;
			tab[i][0]-=2;
			wyn++;
		}
		while(tab[i][1]>1 && x<0)
		{
			x+=2;
			tab[i][1]-=2;
			wyn++;
		}
	}
```
在这段代码中，$x$ 代表左袜子未配对数量和右袜子未配对的差。

如果 $x$ 大于 $0$，说明左袜子未匹配的数量更多，如果某种颜色的左袜子只数大于 $1$，则可以把其中的一只左袜子变成右袜子，同时完成一次配对。对于右袜子也是同理。

可以证明，这样的操作是不劣的。

---

## 作者：Echo_Long (赞：2)

### [Phoenix and Socks](https://www.luogu.com.cn/problem/CF1515D)

$*1500$ 调了一个小时，什么水平。

首先 我们先将所有能匹配上的袜子进行配对，这样是绝对不劣的。

其次我们严格让左面的袜子多，方便我们进行处理，统计 $cntl$ 为左面的袜子个数，$cntr$ 为右面的袜子个数。

那么我们首先期望要用每次 $1$ 的代价消除 $cntl$ 和 $cntr$ 之间的数量差距。

只要左面点有袜子的数量 $\ge 2$，那么可以合法地减小 $cntl$ 和 $cntr$ 之间的数量差距，用 $1$ 的代价移动并匹配即可。

注意特判奇数和 $cntl-cntr<a[i]$ 的情况。

对于最后的局面，我们直接让左面袜子和右面袜子用 $1$ 的代价更改颜色并匹配，计入答案为 $\frac {( cntl + cntr )} 2$。

如果 $cntl$ 最后没有和 $cntr$ 相等，那么还需要加上用于消除两边数量差距的 $\frac {( cntl - cntr )} 2$。

时间复杂度 $O(n)$。

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define eb emplace_back
#define ls p<<1
#define rs p<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define getchar() cin.get()
#define print(x) cout<<#x<<'='<<x<<endl
const int N = 2e5 + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , l , r , a[N] , b[N] , ans;

signed main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
    int T = read();
    while ( T -- )
    {
        n = read() , l = read() , r = read();
        memset ( a , 0 , sizeof a );
        memset ( b , 0 , sizeof b );
        ans = 0;
        for ( int i = 1 ; i <= l ; i ++ ) ++ a[read()];
        for ( int i = l + 1 ; i <= n ; i ++ ) ++ b[read()];
        for ( int i = 1 ; i <= n ; i ++ )
        {
            if ( a[i] >= b[i] ) a[i] -= b[i] , b[i] = 0;
            else if ( a[i] < b[i] ) b[i] -= a[i] , a[i] = 0;
        }
        // for ( int i = 1 ; i <= n ; i ++ ) cout << a[i] << ' ' << b[i] << endl;
        int cntl = 0 , cntr = 0;
        for ( int i = 1 ; i <= n ; i ++ ) cntl += a[i] , cntr += b[i];
        if ( cntl < cntr )
        {
            for ( int i = 1 ; i <= n ; i ++ ) swap ( a[i] , b[i] );
            swap ( cntl , cntr );
        }
        for ( int i = 1 ; i <= n ; i ++ )
        {
            if ( a[i] >= 2 )
            {
                if ( a[i] > ( cntl - cntr ) ) ans += ( cntl - cntr ) / 2 , cntl = cntr;
                else ans += a[i] / 2 , cntl -= a[i] / 2 * 2;
            }
            if ( cntl == cntr ) break;
        }
        if ( cntl == cntr ) cout << ans + ( cntl + cntr ) / 2 << endl;
        else cout << ans + ( cntl + cntr ) / 2 + ( cntl - cntr ) / 2 << endl;
    }
    return 0;
}
```

### 

---

## 作者：Light_snow (赞：1)

本文同步自[link](https://www.cnblogs.com/dixiao/p/14728152.html)。

看出来如果 $l,r$ 不相等，则一定要从多的一边向少的一边转变，那么这个时候尽量让能匹配的袜子多就行了，即把多的一边的多出来的同色袜子移到另一边。

最后统计答案统计为需要更改的袜子，以及还未配对的袜子的数目的一半。

```cpp
// code by fhq_treap
#include<bits/stdc++.h>
#define ll long long
#define N 300005

inline ll read(){
    char C=getchar();
    ll A=0 , F=1;
    while(('0' > C || C > '9') && (C != '-')) C=getchar();
    if(C == '-') F=-1 , C=getchar();
    while('0' <= C && C <= '9') A=(A << 1)+(A << 3)+(C - 48) , C=getchar();
    return A*F;
}


struct P{
	int to,next;
};

struct Map{
	P e[N << 1];
	int head[N],cnt;
	Map(){
		std::memset(head,0,sizeof(head));
		cnt = 0;
	}
	inline void add(int x,int y){
		e[++cnt].to = y;
		e[cnt].next = head[x];
		head[x] = cnt;
	}
};

ll t,n,l,r;
ll c[N],lc[N],rc[N],cnt[N];
bool del[N];

int main(){
	t = read();
	while(t -- ){
		n = read(),l = read(),r = read();
		for(int i = 1;i <= n;++i)
		c[i] = read(),lc[c[i]] = 0,rc[c[i]] = 0,cnt[c[i]] = 0,del[c[i]] = 0;
		for(int i = 1;i <= l;++i)
		lc[c[i]] ++ ,cnt[c[i]] ++ ;
		for(int i = l + 1;i <= n;++i)
		rc[c[i]] ++ ,cnt[c[i]] ++ ;
		for(int i = 1;i <= l;++i)
		if(rc[c[i]])
		rc[c[i]] -- ,lc[c[i]] -- ,cnt[c[i]] -= 2;
		ll need = abs(r - l) / 2;
		if(l > r){
			for(int i = 1;i <= l;++i){
				while(need && lc[c[i]] >= 2)
				lc[c[i]] -= 2,cnt[c[i]] -= 2,need -- ;
			}
		}else{
			if(l < r){
				for(int i = l + 1;i <= n;++i)
				while(need && rc[c[i]] >= 2)
				rc[c[i]] -= 2,cnt[c[i]] -= 2,need -- ;
			}
		}
		ll ans = 0;
		for(int i = 1;i <= n;++i){
			if(!del[c[i]])
			del[c[i]] = 1,ans += cnt[c[i]] ;
		}
		std::cout<<ans / 2 + abs(r - l) / 2<<std::endl;
	}
}
```


---

## 作者：water_tomato (赞：1)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1515d-phoenix-and-socks-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1515D)。

有 $n$ 只袜子，每只袜子都可能是左/右袜子且有一种颜色。每次操作你可以：改变袜子的颜色或改变袜子的左右性。你需要使左右袜子一一配对（具体地，若两只袜子一左一右且颜色相同，则这两只袜子配对）。求最小操作数。

## 解析

首先由于左右袜子必须要一一配对，所以两者数量一定要相等，因此答案最小为 $|\frac{l-r}{2}|$，即我们至少要进行 $|\frac{l-r}{2}|$ 次更改左右性的操作。我们考虑怎么使这些操作收益最大化，即操作后改变颜色的操作数最小。

> 穿插一个小证明：我们一定只会进行 $|\frac{l-r}{2}|$ 次更改左右性的操作。因为假设左右袜子数相等，我们最优再进行两次更改左右性操作才能使两对袜子配对，而更改颜色也只需要两次，没必要再进行更改左右性的操作。

首先我们可以先把已经配好对的袜子排除掉，显然改变已配对的袜子的左右性是愚蠢的。又有显然地，更改左右性的操作只会在袜子多的那边进行。假设左袜子多，那么对于左袜子中未匹配的袜子，如果有一种颜色的袜子不少于两只，更改其中一只的左右性一定是更优的，因为这样更改之后就直接匹配了，无需再更改颜色。先尽可能找出这种袜子，然后剩下的袜子就随意了，最后统计答案时再加上仍未得到匹配的袜子数即可。

代码附有注释，可食用。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,l,r,ans,x;
int c[N],tl[N],tr[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&l,&r);
		ans=abs(l-r)/2;//更改左右性的操作数
		for(int i=1;i<=n;i++) tl[i]=tr[i]=0;
		for(int i=1;i<=n;i++) scanf("%d",&c[i]);
		for(int i=1;i<=l;i++) tl[c[i]]++;
		for(int i=l+1;i<=n;i++) tr[c[i]]++;
		for(int i=1;i<=n;i++){
			if(tl[i]>0&&tr[i]>0){
				int t=min(tl[i],tr[i]);
				tl[i]-=t;
				tr[i]-=t;//这里是去除已配对的袜子
			}
		}
		int x=ans;
		if(l>r){//找袜子多的那边，进行操作
			for(int i=1;i<=n&&x>0;i++){
				while(x>0&&tl[i]>=2){//如果有不少于 2 只的，选它
					x--;
					tl[i]-=2;//一只左右性换了，一只匹配上了，故未匹配的直接减 2
				}
			}
			for(int i=1;i<=n&&x>0;i++){
				while(x>0&&tl[i]>=1){//处理剩余的操作次数
					x--;
					tl[i]-=1;//未匹配的袜子数只能减 1
				}
			}
			for(int i=1;i<=n;i++){
				ans+=tl[i];//答案加上未匹配的袜子数
			}
		}
		else{//同上
			for(int i=1;i<=n&&x>0;i++){
				while(x>0&&tr[i]>=2){
					x--;
					tr[i]-=2;
				}
			}
			for(int i=1;i<=n&&x>0;i++){
				while(x>0&&tr[i]>=1){
					x--;
					tr[i]-=1;
				}
			}
			for(int i=1;i<=n;i++){
				ans+=tr[i];
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

模拟题。                

显然先把左右袜子可以配对的配对了是最优的。                

接着我们分开处理，把数量多的那种袜子中颜色相同的拿出来直接改袜子种类配对，这也可以证明是不劣的。（这里定义袜子种类说的是左右袜子）                      

但这里要注意我们数量多的袜子最后配对完后数量仍然需要严格大于等于数量少的袜子，否则我们又会牺牲次数去改变袜子的种类。

最后我们直接配对就好了。                  

时间复杂度 $O(n)$ 。                 

~~如果不是晚上打说不定真的是随便切~~                    

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
const int Len = 2e5 + 5;
int n,m,a[Len],l,r,lcnt[Len],L[Len],R[Len];
bool flag[Len];
int Iabs(int x){return x < 0 ? -x : x;}
vector<int> v[Len];
int idx[Len],smr[Len];
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d %d %d",&n,&l,&r);
		for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
		for(int i = 1 ; i <= l ; i ++) v[a[i]].push_back(i);
		int ans = 0 , sizl = 0 , sizr = 0;
		for(int i = l + 1 ; i <= n ; i ++) 
		{
			int lens = v[a[i]].size();
			if(idx[a[i]] >= lens) continue;
			flag[v[a[i]][idx[a[i]]]] = flag[i] = 1 ; idx[a[i]] ++;
		}
		for(int i = 1 ; i <= l ; i ++) 
		{
			if(flag[i]) continue;
			L[++ sizl] = a[i]; 
		}
		for(int i = l + 1 ; i <= n ; i ++)
		{
			if(flag[i]) continue;
			R[++ sizr] = a[i];
		}
		sort(L + 1 , L + 1 + sizl) ; sort(R + 1 , R + 1 + sizr);
		if(sizl > sizr) 
		{
			for(int i = 1 ; i <= sizl ; i ++) smr[i] = L[i];
			for(int i = 1 ; i <= sizr ; i ++) L[i] = R[i];
			for(int i = 1 ; i <= sizl ; i ++) R[i] = smr[i];
			swap(sizl , sizr);
		}
		for(int i = 1 ; i <= n ; i ++) flag[i] = 0;
		int ccz = sizr;
		int siml = sizl , simr = sizr;
		for(int i = 2 ; i <= sizr ; i ++)
		{
			if(R[i] == R[i - 1] && simr > siml)
			{
				ans ++;
				simr -= 2;
				i ++;
			}
		}
		printf("%d\n",ans + (simr - siml) / 2 + (simr + siml) / 2);
		for(int i = 1 ; i <= n ; i ++) v[i].clear() , flag[i] = idx[i] = 0;
	}
	return 0;
}
```

---

## 作者：CLZY (赞：0)

## 题意

​	你有$n$只有颜色且分为左右的袜子，前$l$只袜子是左袜子，后$r$只袜子是右袜子，每只袜子都有一个颜色$C_i$，你可以花费1代价做如下**某一个**操作

​	（1）把某只袜子重新染成任意一种颜色

​	（2）把某只左袜子变成右袜子（不改变颜色）

​	（3）把某只右袜子变成左袜子

​	问最少要花费多少代价，可以把这$n$只袜子配成对，两只袜子配成对是指这其中一只袜子是左袜子，另一只袜子是右袜子，且两只袜子颜色相同。

​	数据范围	$1\leq n \leq 2*10^5$，$n$是偶数，$l+r=n$，$1\leq C_i \leq n $

## 题解

​	对于左右袜子，我们分别建一个桶，如果原先就可以配对的，我们成对先删去。

​	之后我们观察可以发现，对于一堆相同颜色的左或右袜子或者某个左袜子配对某个右袜子，花费1代价就可以配对出1对，先成对统计。	

​	于是问题在于那些的落单的一边的袜子，它们又需要换颜色，又需要换方向，我们要尽量减少这样的情况的发生。

​	那我们先统计出左和右桶中某个颜色的袜子数为奇数的数量，优先考虑用对侧的袜子消去，即尽量使花2代价配对的对数尽量少。

# CODE

​	```

​	

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define ll long long
#define ri register int
#define rep(i,l,r) for(ll i=(l);i<=(r);++i)
#define req(i,r,l) for(ll i=(r);i>=(l);--i)
#define wif while
const ll inf = INT_MAX , df = 3e5 + 7 ;
inline ll read()	{
	ll x = 0 , y = 1 ;	char ch=getchar();
	wif(ch>'9'||ch<'0')	y=(ch=='-')?-1:1,ch=getchar();
	wif(ch>='0'&&ch<='9')	x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;	}
ll i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,buc[2][df];
int main()	{
	t=read();
	wif(t--)	{
		n=read(),l=read(),r=read();
		rep(i,1,n)	buc[0][i]=buc[1][i]=0;
		rep(i,1,l)	x=read(),buc[0][x]++;
		rep(i,1,r)	x=read(),buc[1][x]++;
		rep(i,1,n)	{
			ll tmp = min(buc[0][i],buc[1][i]);
			rep(j,0,1)	buc[j][i] -= tmp ;
		}
		ll cnt0=0,cnt1=0,ans=0,num0=0,num1=0;
		rep(i,1,n)	cnt0+=buc[0][i],cnt1+=buc[1][i],num0+=buc[0][i]%2,num1+=buc[1][i]%2;
		cnt0-=num0,cnt1-=num1;
		ll tmp=min(num0,num1);
		ans+=tmp;num0-=tmp,num1-=tmp;
		if(num1)	swap(num0,num1),swap(cnt0,cnt1),swap(buc[0],buc[1]);
		if(num0<=cnt1)	{
			ans+=num0,cnt1-=num0;
			ans+=cnt0/2+cnt1/2;
		}
		else	{
			ans+=num0+cnt0/2;
		}
		printf("%lld\n",ans);
	}
}
```

​	

---

## 作者：5ab_juruo (赞：0)

有 $n$ 只袜子，现在可以改颜色或者更改左右，求最小操作数使袜子全部配对。

首先，我们不妨设 $l\ge r$（否则可以交换，不影响答案），同时，我们维护每种颜色袜子的数量。如果左右都有这种颜色的袜子，则显然可以将其删除，不会影响最终答案。假设删完后左袜子有 $l^\prime$ 只，右袜子有 $r^\prime$ 只。

接下来，左右没有颜色相同的袜子，我们要将一部分左袜子变成右袜子。注意到，如果某种颜色的左袜子有多只，那么我们将其中一只变成右袜子以后，我们就可以减少更改颜色的操作数量。

所以，我们统计能够匹配成对的（颜色相同的）左袜子数（设其有 $k$ 对），然后根据大小分类讨论：

- 若 $l^\prime - r^\prime \ge 2k$，即将所有的袜子对拆散后，依旧无法使左右袜子数相同。此时一部分左袜子（指没有匹配的，下同）要移过去，剩下的左袜子要改颜色（由于颜色两两不同，所以一定全部要改），答案就是 $l^\prime + k$；
- 若 $l^\prime - r^\prime < 2k$，即左袜子配的对子数，大于左右袜子差，即有一部分对子无法拆散。此时剩下的左袜子（此处指没有移过去，或没有与移过去的配对的，下同）依旧要全部改颜色。注意到移过去了 $\dfrac{l^\prime+r^\prime+2k}{2}-r^\prime = \dfrac{l^\prime+2k-r^\prime}{2}$ 只袜子，剩下的左袜子与右袜子数相同，所以答案是 $\dfrac{l^\prime+2k-r^\prime}{2}+r^\prime = \dfrac{l^\prime+r^\prime}{2}+k$。

Code：

```cpp
#include <iostream>
using namespace std;
 
const int max_n = 200000;
 
struct ass
{
	int cnt[max_n], siz;
 
	void insert(int x)
	{
		cnt[x]++;
		siz++;
	}
 
	void clear(int n)
	{
		for (int i = 0; i < n; i++)
			cnt[i] = 0;
		siz = 0;
	}
 
	int operator[](const int& id)
	{
		return cnt[id];
	}
 
	int at(const int& id)
	{
		return cnt[id];
	}
	
	void reduce(int id, int x)
	{
		siz -= x;
		cnt[id] -= x;
	}
 
	int size() const { return siz; }
} bass[2];
 
inline int my_min(int a, int b) { return (a < b)? a:b; }
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int cas, n, l, r, offst;
	ass *pl, *pr;
	
	cin >> cas;
	while (cas--)
	{
		cin >> n >> l >> r;
		bass[0].clear(n), bass[1].clear(n);
 
		for (int i = 0, ta; i < l; i++)
		{
			cin >> ta;
			bass[0].insert(ta-1);
		}
		for (int i = 0, ta; i < r; i++)
		{
			cin >> ta;
			bass[1].insert(ta-1);
		}
 
		if (bass[0].size() > bass[1].size())
			pl = bass, pr = bass + 1;
		else
			pl = bass + 1, pr = bass;
		
		for (int i = 0; i < n; i++)
			if (pl->at(i) > 0 && pr->at(i) > 0)
			{
				auto x = my_min(pl->at(i), pr->at(i));
				pl->reduce(i, x);
				pr->reduce(i, x);
			}
		
		offst = 0;
		for (int i = 0; i < n; i++)
			if (pl->at(i) > 1)
			{
				offst += pl->at(i) / 2;
				pl->reduce(i, (pl->at(i) / 2) * 2);
			}
		
		if (pl->size() >= pr->size())
			cout << pl->size() + offst << endl;
		else
			cout << (pl->size() + pr->size()) / 2 + offst << endl;
	}
	
	return 0;
}
```

---

