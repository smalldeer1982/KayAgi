# You Are Given a WASD-string...

## 题目描述

You have a string $ s $ — a sequence of commands for your toy robot. The robot is placed in some cell of a rectangular grid. He can perform four commands:

- 'W' — move one cell up;
- 'S' — move one cell down;
- 'A' — move one cell left;
- 'D' — move one cell right.

Let $ Grid(s) $ be the grid of minimum possible area such that there is a position in the grid where you can place the robot in such a way that it will not fall from the grid while running the sequence of commands $ s $ . For example, if $ s = \text{DSAWWAW} $ then $ Grid(s) $ is the $ 4 \times 3 $ grid:

1. you can place the robot in the cell $ (3, 2) $ ;
2. the robot performs the command 'D' and moves to $ (3, 3) $ ;
3. the robot performs the command 'S' and moves to $ (4, 3) $ ;
4. the robot performs the command 'A' and moves to $ (4, 2) $ ;
5. the robot performs the command 'W' and moves to $ (3, 2) $ ;
6. the robot performs the command 'W' and moves to $ (2, 2) $ ;
7. the robot performs the command 'A' and moves to $ (2, 1) $ ;
8. the robot performs the command 'W' and moves to $ (1, 1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1202C/14db41d91dc6fffe218fcbada16fff9a7890d775.png)You have $ 4 $ extra letters: one 'W', one 'A', one 'S', one 'D'. You'd like to insert at most one of these letters in any position of sequence $ s $ to minimize the area of $ Grid(s) $ .

What is the minimum area of $ Grid(s) $ you can achieve?

## 说明/提示

In the first query you have to get string $ \text{DSAWW}\underline{D}\text{AW} $ .

In second and third queries you can not decrease the area of $ Grid(s) $ .

## 样例 #1

### 输入

```
3
DSAWWAW
D
WA
```

### 输出

```
8
2
4
```

# 题解

## 作者：DPair (赞：5)

## 【前言】
写完这道题之后一看题解

？？？

怎么一个个都那么长？

怎么一个个都用了前缀和？

提供一种清晰、简单、易懂、好写的解法。

## 【思路】

首先很容易发现行列无关，分别考虑。

与行有关的变量称之为 $Cross$ ，~~于是很自然而然的想到~~把与列有关的变量称之为 $Epic$ (~~bruh~~) 。

首先思考不做修改的答案。

很显然，答案为 **(往右能到达的最大值-往左能到的最小值 + 1) × (往上能到达的最大值 - 往下能到达的最小值 + 1)**

然后考虑修改，由于只能修改一次，我们要么是 **把最大值变小 1** 或者 **把最小值变大 1**。


然后你输出 **(行 - 1) × 列** 和 **(列 - 1) × 行** 的最小值然后就发现 $WA$ 了。

原因是有一些值是取不到的。

那么我们判断行和列是否能缩减。

我们发现，不能缩减的原因在于 **这次移动导致最大值与最小值都发生了变化** 。

也就是说我们要使 **最大值和最小值不会同时发生变化** 。

不难发现最大值与最小值同时发生变化当且仅当 **一个最值第一次出现的时间戳 - 另一个最值最后一次出现的时间戳 <= 1** 。

也就是说如果对于行或列中的某一个指标，该指标 **存在一个最值第一次出现的时间戳 - 另一个最值最后一次出现的时间戳 > 1** ，那么这个指标就可以 **-1** 。

（可能有一些拗口，看不懂可以看代码）

下面简单说明一下原因，当然也可以常试自行理解。

## 【说明】

不难明确一个大前提，要改变最值必须要在 **这个最值第一次出现之前** 改变。且不能在 **另一个最值最后一次出现之前** 改变。

挺废话的，你这一个点移动了后面所有操作都会移动，那么如果一个最值向另一个最值 **靠拢** 了 $1$ ，另一个最值就会自动又 **远离** $1$ 。

首先考虑 **这个值 <= 0** 的情况。

不必多说，大前提都不符合。

考虑 **0 < 这个值 <= 1** 的情况（其实就是取 $1$ ）。

那么变化的位置只能是 **一个最值最后一次出现与另一个最值第一次出现** 之间。

发现是不行的，在这样改变之后，最后一次出现的最值又会 **远离** $1$ 。又等同于没有改变。

而 $ > 1$ 的情况显然是可行的。

差不多就是这样。

## 【代码】
（变量名为什么是 $Cross$ 和 $Epic$ 上面解释过了，能看懂就行）

（ $mini$ 表示最小值，$maxi$ 表示最大值，$fst$ 表示第一次出现的时间戳，$lst$ 表示最后一次出现的时间戳）


```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    //快读，方便阅读省略了
}
template <typename T>
inline void fprint(T x){
    //同上
}
template <typename T>
inline void fprint(T x, char ch){
    //同上
}

char s[200005];
int n;

int Cross, Epic, mini_Cross, mini_Epic, maxi_Cross, maxi_Epic;
int fst_mini_Cross, fst_mini_Epic, fst_maxi_Cross, fst_maxi_Epic;
int lst_mini_Cross, lst_mini_Epic, lst_maxi_Cross, lst_maxi_Epic;
inline void work(){
    scanf("%s", s + 1);
    n = strlen(s + 1);
    Cross = Epic = mini_Cross = mini_Epic = maxi_Cross = maxi_Epic = fst_maxi_Cross = fst_maxi_Epic = fst_mini_Epic = fst_mini_Cross = lst_maxi_Cross = lst_maxi_Epic = lst_mini_Epic = lst_mini_Cross = 0;
    for (register int i = 1;i <= n;i ++){
        if(s[i] == 'W') Epic ++;
        if(s[i] == 'S') Epic --;
        if(s[i] == 'A') Cross --;
        if(s[i] == 'D') Cross ++;
        if(mini_Cross > Cross) mini_Cross = Cross, fst_mini_Cross = i;
        if(mini_Cross == Cross) lst_mini_Cross = i;
        if(mini_Epic > Epic) mini_Epic = Epic, fst_mini_Epic = i;
        if(mini_Epic == Epic) lst_mini_Epic = i;
        if(maxi_Cross < Cross) maxi_Cross = Cross, fst_maxi_Cross = i;
        if(maxi_Cross == Cross) lst_maxi_Cross = i;
        if(maxi_Epic < Epic) maxi_Epic = Epic, fst_maxi_Epic = i;
        if(maxi_Epic == Epic) lst_maxi_Epic = i;
    }
    LL ans = 1ll * (maxi_Epic - mini_Epic + 1) * (maxi_Cross - mini_Cross + 1);
    if(1 < -(lst_mini_Cross - fst_maxi_Cross) || 1 < -(lst_maxi_Cross - fst_mini_Cross)) chmin(ans, 1ll * (maxi_Epic - mini_Epic + 1) * (maxi_Cross - mini_Cross));
    if(1 < -(lst_mini_Epic - fst_maxi_Epic) || 1 < -(lst_maxi_Epic - fst_mini_Epic)) chmin(ans, 1ll * (maxi_Epic - mini_Epic) * (maxi_Cross - mini_Cross + 1));
    fprint(ans, 10);
    return;
}

int main(){
    int ___;
    read(___);
    while(___ --) work();
    return 0;
}

```

---

## 作者：万弘 (赞：2)

首先是行列无关，那么把行和列的操作抠出来分别处理，这里以行为例。

先求一下，不加操作，会到达的最大值$maxv$和最小值$minv$.

假设我们要让最大值减少1.显然当当前坐标$cur=maxv$第一次出现时，就必须使用-1操作（注意只能用一次），同时更新使用操作后的$tmpmin,tmpmax$。  
$tmpmax-tmpmin+1$就是使用一次操作$-1$后横向上的长度。 

增加1同理。

列同理。

时间复杂度$\mathcal O(n)$
```cpp
/**********/
#define MAXN 200011
char a[MAXN];
ll row[MAXN],col[MAXN];
int main()
{
    ll t=read();
    while(t--)
    {
        scanf("%s",a+1);
        ll n=strlen(a+1),row_cnt=0,col_cnt=0;
        for(ll i=1;i<=n;++i)
        {
            if(a[i]=='W')row[++row_cnt]=1;
            else if(a[i]=='S')row[++row_cnt]=-1;
            else if(a[i]=='A')col[++col_cnt]=-1;
            else col[++col_cnt]=1;
        }
        ll minv=0,maxv=0,cur=0,row_len,row_f,col_len,col_f;
        for(ll i=1;i<=row_cnt;++i)//work row
            cur+=row[i],umax(maxv,cur),umin(minv,cur);
        row_f=row_len=maxv-minv+1;
        ll tmpmin=0,tmpmax=0,flag=0;
        cur=0;
        for(ll i=1;i<=row_cnt;++i)
        {
            cur+=row[i];
            if(cur==maxv&&!flag)flag=1,--cur,umin(tmpmin,cur-1);
            umax(tmpmax,cur),umin(tmpmin,cur);
        }
        umin(row_f,tmpmax-tmpmin+1);
        tmpmin=0,tmpmax=0,flag=0;
        cur=0;
        for(ll i=1;i<=row_cnt;++i)
        {
            cur+=row[i];
            if(cur==minv&&!flag)flag=1,++cur,umax(tmpmax,cur+1);
            umax(tmpmax,cur),umin(tmpmin,cur);
        }
        umin(row_f,tmpmax-tmpmin+1);
        /////work col
        minv=maxv=0;cur=0;
        for(ll i=1;i<=col_cnt;++i)
            cur+=col[i],umax(maxv,cur),umin(minv,cur);
        col_f=col_len=maxv-minv+1;
        tmpmin=0,tmpmax=0,flag=0;
        cur=0;
        for(ll i=1;i<=col_cnt;++i)
        {
            cur+=col[i];
            if(cur==maxv&&!flag)flag=1,--cur,umin(tmpmin,cur-1);
            umax(tmpmax,cur),umin(tmpmin,cur);
        }
        umin(col_f,tmpmax-tmpmin+1);
        tmpmin=0,tmpmax=0,flag=0;
        cur=0;
        for(ll i=1;i<=col_cnt;++i)
        {
            cur+=col[i];
            if(cur==minv&&!flag)flag=1,++cur,umax(tmpmax,cur+1);;
            umax(tmpmax,cur),umin(tmpmin,cur);
        }
        umin(col_f,tmpmax-tmpmin+1);
        printf("%lld\n",min(row_f*col_len,row_len*col_f));
    }
    return 0;
}
```

---

## 作者：皎月半洒花 (赞：2)

这道题简直是`debug`到吐血……

其实思路是很**明晰+清新**的，大概就是你考虑首先显然是**行列无关**的，所以分开考虑；接着你发现我们的最优策略肯定是让某一步相当于每走，但是假设我的$x_{min}$和$x_{max}$均在我这次改动操作的后面，那么我们尝试缩小活动范围，即缩小$x_{max}$的时候也会缩小$x_{min}$，相当于没缩——所以我们应找到一个界点，所有的最大值都在左/右边，对应的所有最小值都在右/左边。

于是我们考虑直接前缀和瞎搞就可以了。但是我`debug`了很久的原因是，这个问题他不是很完美，详细一些就是我们考虑无论怎么移动，都不能越过我们预处理出来的$x_{min}$、$x_{max}$这个界（否则会出现越贪越大）。也就是说，假设一开始我有一个$x_{max}$，接着过了一会儿有一个$x_{min}$，为了“拔高”$x_{min}$我们必须要添加一个$W$，所以我们必须要保证任何时刻不会出现$x_{max}$在放上一个$W$之后越界的情况，也就是说$x_{min}$和$x_{max}$出现的位置之间必须要一个$S$才能用来抵消掉我们$W$。

以上全都是以`W/S`作为例子的，`A/D`的情况分类讨论一下就好。

呃，废话有点多，但是实际上写起来~~挺好写的吧~~也需要一些时间：

```cpp
#define MAXN 200010
#define LL long long
#define Inf 192608170

using namespace std ; LL ans ; 
int fhm, fhn, fwm, fwn, pos[2][5], i ; 
int T, N, Sw[MAXN], Sh[MAXN] ; char S[MAXN] ;

int main(){
	cin >> T ; 
	while (T --){
		fhm = fwm = -Inf, fhn = fwn = Inf ;  
		scanf("%s", S + 1), N = strlen(S + 1) ;
		for (i = 1 ; i <= N ; ++ i){
			Sh[i] = Sh[i - 1], Sw[i] = Sw[i - 1] ;
			if (S[i] == 'W') Sh[i] = Sh[i - 1] + 1 ; 
			else if (S[i] == 'S') Sh[i] = Sh[i - 1] - 1 ;
			else if (S[i] == 'D') Sw[i] = Sw[i - 1] + 1 ;
			else if (S[i] == 'A') Sw[i] = Sw[i - 1] - 1 ;
		}//前缀和 : w x h 
		for (i = 0 ; i <= N ; ++ i) fwm = max(Sw[i], fwm), fwn = min(Sw[i], fwn) ;
		for (i = 0 ; i <= N ; ++ i) fhm = max(Sh[i], fhm), fhn = min(Sh[i], fhn) ; 
		for (i = N ; ~i ; -- i) if (Sh[i] == fhn) { pos[0][4] = i ; break ; } //last_min h
		for (i = N ; ~i ; -- i) if (Sw[i] == fwn) { pos[1][4] = i ; break ; } //last_min h
		for (i = 0 ; i <= N ; ++ i) if (Sh[i] == fhm) { pos[0][1] = i ; break ; }  //first_max h
		for (i = 0 ; i <= N ; ++ i) if (Sw[i] == fwm) { pos[1][1] = i ; break ; }  //first_max w
		
		for (i = N ; ~i ; -- i) if (Sh[i] == fhm) { pos[0][3] = i ; break ; } //last_max h
		for (i = N ; ~i ; -- i) if (Sw[i] == fwm) { pos[1][3] = i ; break ; } //last_max h
		for (i = 0 ; i <= N ; ++ i) if (Sh[i] == fhn) { pos[0][2] = i ; break ; }  //first_min h	
		for (i = 0 ; i <= N ; ++ i) if (Sw[i] == fwn) { pos[1][2] = i ; break ; }  //first_min w
		ans = 1ll * (fwn - fwm - 1) * (fhn - fhm - 1) ; //cout << ans << endl ;
		if (pos[0][3] < pos[0][2] && Sh[pos[0][3]] - Sh[pos[0][2]] > 1) 
       		ans = min(ans, 1ll * (fhm - fhn) * (fwm - fwn + 1)) ;
		if (pos[1][3] < pos[1][2] && Sw[pos[1][3]] - Sw[pos[1][2]] > 1) 
        	ans = min(ans, 1ll * (fhm - fhn + 1) * (fwm - fwn)) ;
		if (pos[0][4] < pos[0][1] && Sh[pos[0][4]] - Sh[pos[0][1]] < -1) 
        	ans = min(ans, 1ll * (fhm - fhn) * (fwm - fwn + 1)) ;
		if (pos[1][4] < pos[1][1] && Sw[pos[1][4]] - Sw[pos[1][1]] < -1) 
        	ans = min(ans, 1ll * (fhm - fhn + 1) * (fwm - fwn)) ;
		cout << ans << endl ; 
		pos[0][1] = pos[1][1] = pos[0][2] = pos[1][2] = Inf ;
		pos[0][3] = pos[1][3] = pos[0][4] = pos[1][4] = -Inf ;
	}
}

```

~~嘤嘤嘤鬼知道我做这题时经历了什么啊qaq~~

---

## 作者：Kevin911 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1202C)

感觉没有各位想的这么复杂，~~所以我水一波题解~~

### 思路


------------


因为只允许增加一次操作，所以可以考虑枚举操作的位置和种类。

经过观察会发现，增加一种操作只会影响到它后面的行走范围，且将整个行走轨迹像四个方向平移一个。可以形象化地理解为，前面的轨迹不变，后面的轨迹整体向上下左右中的一个方向平移一格。

因此可以预处理出 $up[i][0/1]$，$down[i][0/1]$，$left[i][0/1]$，$right[i][0/1]$。

其中 $up[i][0]$，$down[i][0]$，$left[i][0]$，$right[i][0]$表示执行前 $i$ 操作后的上下左右边界，$up[i][1]$，$down[i][1]$，$left[i][1]$，$right[i][1]$表示从第 $n$ 个到第 $i$ 个倒序执行的上下左右边界。

然后就可以通过变化的性质更新答案了，具体细节详见代码。

### Talk is cheap，show me your code

------------

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
char s[maxn];
int up[maxn][2],down[maxn][2],le[maxn][2],ri[maxn][2];
signed main()
{
	int t;
	cin>>t;
	for(int p=1;p<=t;p++)
	{
		memset(up,-0x7f,sizeof(up));
		memset(down,0x7f,sizeof(down));
		memset(le,0x7f,sizeof(le));
		memset(ri,-0x7f,sizeof(ri));
		cin>>s+1;
		int n=strlen(s+1);
		int x=0,y=0;
		up[0][0]=down[0][0]=le[0][0]=ri[0][0]=0;
		for(int i=1;i<=n;i++)
		{
			if(s[i]=='W') y++;
			if(s[i]=='A') x--;
			if(s[i]=='S') y--;
			if(s[i]=='D') x++;
			up[i][0]=max(up[i-1][0],y);
			down[i][0]=min(down[i-1][0],y);
			le[i][0]=min(le[i-1][0],x);
			ri[i][0]=max(ri[i-1][0],x);
		}
		le[n+1][1]=ri[n+1][1]=x;
		up[n+1][1]=down[n+1][1]=y;
		for(int i=n;i>=1;i--)
		{
			if(s[i]=='W') y--;
			if(s[i]=='A') x++;
			if(s[i]=='S') y++;
			if(s[i]=='D') x--;
			up[i][1]=max(up[i+1][1],y);
			down[i][1]=min(down[i+1][1],y);
			le[i][1]=min(le[i+1][1],x);
			ri[i][1]=max(ri[i+1][1],x);
		}
		int ans=(up[n][0]-down[n][0]+1)*(ri[n][0]-le[n][0]+1);
		for(int i=1;i<n;i++)
		{
			int u=max(up[i][0],up[i+1][1]-1),d=min(down[i][0],down[i+1][1]-1),l=min(le[i][0],le[i+1][1]),r=max(ri[i][0],ri[i+1][1]);
			ans=min(ans,(u-d+1)*(r-l+1));
			u=max(up[i][0],up[i+1][1]+1),d=min(down[i][0],down[i+1][1]+1),l=min(le[i][0],le[i+1][1]),r=max(ri[i][0],ri[i+1][1]);
			ans=min(ans,(u-d+1)*(r-l+1));
			u=max(up[i][0],up[i+1][1]),d=min(down[i][0],down[i+1][1]),l=min(le[i][0],le[i+1][1]-1),r=max(ri[i][0],ri[i+1][1]-1);
			ans=min(ans,(u-d+1)*(r-l+1));
			u=max(up[i][0],up[i+1][1]),d=min(down[i][0],down[i+1][1]),l=min(le[i][0],le[i+1][1]+1),r=max(ri[i][0],ri[i+1][1]+1);
			ans=min(ans,(u-d+1)*(r-l+1));
		}
		cout<<ans<<endl;
	}
	return 0;//完结撒花
}
```

---

## 作者：cjrqwq (赞：1)

### 思路

观察 $\tt DDDWWW$ 和 $\tt WWWDDD$，发现结果没有区别。所以**上下，左右**不会相互影响，就可以考虑分别处理。

对于 $\tt DSAWWAW$，分别处理就是 $\tt DAA,SWWW$。

对于 $\tt DAA$，记最开始在 $0$，路径就是：$0,1,0,-1$。最大值与最小值的差为 $2$，但自己占格子，经过的格子数量 $3$，可以得出，经过的格子数量为 $ma-mi+1$。（上下方向同样适用）

对于一个字符，处理后的坐标是在前一个的基础上 $+1$ 或者 $-1$。可以理解为前缀和。

$\tt WWDDD$ 前缀和后：
```
0 -1 -1 0 1 1 2
```
---
此时，我们要加入一个操作，也就是从 $i$ 开始的元素都会 $+1$ 或者 $-1$。

最小值可能有很多个，区间为 $[ml,mr]$，最大值的区间为 $[mal,mar]$。

理想情况是 $mr<mal$ 或者 $mar<ml$，这样可以将长度减少 $1$。

如果区间相交了，将最小值 $+1$，就必定会加上最大值，没用。将最大值 $-1$，就必定会加上最小值，没用。

如果是 $0,-1$ 这类，虽然符合，但事实上如果走了，最少也是两格。所以要特判下。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int N = 2e5+10;
int T,ans,n;
char s[N];
int mi,ma;
void find(int a[],int&x,int&y) {
	mi=0,ma=0;
	mil=-1,mir=-1,mal=-1,mar=-1;
	for(int i=1;i<=n;i++) 
		mi=min(mi,a[i]),ma=max(ma,a[i]);
	for(int i=0;i<=n;i++) {
		if(a[i]==mi&&mil==-1) mil=i;
		if(a[i]==mi) mir=i;
		if(a[i]==ma&&mal==-1) mal=i;
		if(a[i]==ma) mar=i;
	}
	if(mir<mal||mar<mil) x=max(ma-mi,2LL);
	else x=ma-mi+1;
	y=ma-mi+1;
}
int a[N],b[N];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>s+1;
		n=strlen(s+1);
		for(int i=1;i<=n;i++) {
			a[i]=a[i-1],b[i]=b[i-1];
			if(s[i]=='D') a[i]++;
			if(s[i]=='A') a[i]--;
			if(s[i]=='S') b[i]--;
			if(s[i]=='W') b[i]++; 
		}
		int x1=0,x2=0,y1=0,y2=0;
		find(a,x1,x2),find(b,y1,y2);
		cout<<min(x1*y2,x2*y1)<<"\n";
	}
	return 0;
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：1)

不错的题，需要点思维和码力。

容易发现，左右和上下互不影响，可以分开处理，这里以左右举例。

定义向左走一格 $-1$，向右走一格 $+1$，求个前缀和找到最大值和最小值，和出现最值的最早时间与最晚时间。定义为 $l,r,l2,r2$。

只有当我们放了一个 A 或 D 使得所有最大值 $-1$ 且最小值不变，或最小值 $+1$ 且最大值不变时，面积才会减小。

假如我们要让最大值 $-1$，那么当且仅当 $r<l2$ 且在坐标 $(r,l2)$ 中存在一个数不等于 $r$ 对应的值时满足。原理很简单，不过多解释。

其他情况同理。

复杂度 $O(n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
ll T,n,sum[N],sum2[N];
string s;
bool chk(int l,int r){
  for(int i=l+1;i<=r;++i)if(sum[i]!=sum[l])return true;
  return false;
}
bool chk2(int l,int r){
  for(int i=l+1;i<=r;++i)if(sum2[i]!=sum2[l])return true;
  return false;
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>T;
  while(T--){
    cin>>s;n=s.size();s="."+s;
    ll ma=0,mi=0,ma2=0,mi2=0;
    for(int i=1;i<=n;++i){
      sum[i]=sum[i-1];
      if(s[i]=='A')--sum[i];
      if(s[i]=='D')++sum[i];
      ma=max(ma,sum[i]);mi=min(mi,sum[i]);
      sum2[i]=sum2[i-1];
      if(s[i]=='S')--sum2[i];
      if(s[i]=='W')++sum2[i];
      ma2=max(ma2,sum2[i]);mi2=min(mi2,sum2[i]);
    }
    int l=1e9,r=-1e9,l2=1e9,r2=-1e9;
    for(int i=0;i<=n;++i){
      if(sum[i]==mi)l=min(l,i),r=max(r,i);
      if(sum[i]==ma)l2=min(l2,i),r2=max(r2,i);
    }
    ll tot=(ma2-mi2+1)*(ma-mi+1),ans=tot;
    if((l>r2||r<l2)&&(chk(r2,l-1)||chk(r,l2-1)))ans=min(ans,tot-(ma2-mi2+1));
    l=l2=1e9;r=r2=-1e9;
    for(int i=0;i<=n;++i){
      if(sum2[i]==mi2)l=min(l,i),r=max(r,i);
      if(sum2[i]==ma2)l2=min(l2,i),r2=max(r2,i);
    }
    if((l>r2||l2>r)&&(chk2(r2,l-1)||chk2(r,l2-1)))ans=min(ans,tot-(ma-mi+1));
    cout<<ans<<endl;
  }
  return 0;
}

```


---

## 作者：CJ_Fu (赞：0)

## [CF1202C You Are Given a WASD-string...](https://www.luogu.com.cn/problem/CF1202C)

\*2100

给你一个操作序列，求在任意位置插入一个 $t\in$ `WASD`，使得包含路径的最小矩形的面积最小。

$|s|\le 2\times 10^5$

简单题，插入一个操作仅会将后面所有到达的位置向相应方向移动一格，于是记录前后缀相应坐标的最大最小值，然后求解时直接给后缀加上相应位移再计算面积即可。枚举所有的空隙以及操作符，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+7;
char s[maxn]; int dx[maxn],dy[maxn];
int posx[maxn],posy[maxn];
int pxmi[maxn],pymi[maxn];
int pxmx[maxn],pymx[maxn];
int sxmi[maxn],symi[maxn];
int sxmx[maxn],symx[maxn];
int dxl[]={1,-1,0,0},dyl[]={0,0,-1,1};
void solve(){
    cin>>s; int n=strlen(s);
    for(int i=1;i<=n;i++) dx[i]=s[i-1]=='W'?-1:(s[i-1]=='S'?1:0),dy[i]=s[i-1]=='A'?-1:(s[i-1]=='D'?1:0);
    for(int i=1;i<=n;i++){
        posx[i]=posx[i-1]+dx[i];
        posy[i]=posy[i-1]+dy[i];
        pxmi[i]=min(pxmi[i-1],posx[i]);
        pxmx[i]=max(pxmx[i-1],posx[i]);
        pymi[i]=min(pymi[i-1],posy[i]);
        pymx[i]=max(pymx[i-1],posy[i]);
    }
    sxmi[n]=sxmx[n]=posx[n];
    symi[n]=symx[n]=posy[n];
    for(int i=n-1;~i;i--){
        sxmi[i]=min(sxmi[i+1],posx[i]);
        sxmx[i]=max(sxmx[i+1],posx[i]);
        symi[i]=min(symi[i+1],posy[i]);
        symx[i]=max(symx[i+1],posy[i]);
    }
    long long ans=1ll*(pxmx[n]-pxmi[n]+1)*(pymx[n]-pymi[n]+1);
    for(int i=0;i<=n;i++){
        for(int j=0;j<4;j++){
            int tx=dxl[j],ty=dyl[j];
            int xl=min(sxmi[i]+tx,pxmi[i]),xr=max(sxmx[i]+tx,pxmx[i]);
            int yl=min(symi[i]+ty,pymi[i]),yr=max(symx[i]+ty,pymx[i]);
            ans=min(ans,1ll*(xr-xl+1)*(yr-yl+1));
        }
    }
    cout<<ans<<'\n';
}
signed main(){
    int T; cin>>T; while(T--) solve();
    return 0;
}
```

---

## 作者：happy_zero (赞：0)

由于只能插入一个字符，所以至多把高或宽减少 $1$，另一条不变。考虑检查是否能减少 $1$。高和宽之间没有影响，可以分开统计。以下以高为例：

记往上为正，往下为负，原点为 $0$，$now$ 表示当前的位置，$l$ 表示最下到达哪里，$r$ 表示最上到达哪里，则高为 $r-l+1$（注意这里是格子所以得加 $1$）。设没有添加任何的高为 $x$。

在过程中，如果 $r-l+1$ 大于 $x$，那么我们要想高减 $1$ 就一定得在当前字符前插入一个字符，相应的 $r$ 减一，$now$ 减一；或 $l$ 加一，$now$ 加一。若之前已经插入一个字符就说明高不能变成 $x-1$。（当前不满足肯定得先满足当前的，否则一定不优）

值得注意的是，如果当前 $r-l+1\le2$（也就是原点和相邻的一个点），若插入一个字符会使另一边的贡献加一，则也无解。（其实这只在 $x=1$ 的情况下出现，也可以特判）

就比如第二个样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/lsx92j36.png)

即使在 `D` 之前添加一个 `A` 也是不行的。

代码（感觉细节没有很多？）：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n;
bool chk(int x, char x1, char x2) {//x1 为正方向，x2 为负方向 
	int now = 0, cnt = 0, r = 0, l = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == x1) now++;
		if (s[i] == x2) now--;
		r = max(now, r), l = min(l, now);
		if (r - l + 1 > x) {
			if (r - l + 1 > 2) {
				cnt++;
				if (s[i] == x1) r--, now--;//根据情况添加 
				else l++, now++;
			}
			else return 0;
		}
		if (cnt > 1) return 0;
	}
	return 1;
}
void solve() {
	cin >> s; n = s.size();
	int ans1 = 0, ans2 = 0, now1 = 0, now2 = 0, l1 = 0, r1 = 0, l2 = 0, r2 = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'A') now1++;
		if (s[i] == 'D') now1--;
		if (s[i] == 'W') now2++;
		if (s[i] == 'S') now2--;
		l1 = min(l1, now1), l2 = min(l2, now2);
		r1 = max(r1, now1), r2 = max(r2, now2);
	}
	ans1 = r1 - l1 + 1, ans2 = r2 - l2 + 1; 
	if (ans2 > 2 && chk(ans2 - 1, 'W', 'S')) ans2--;//注意对应清楚 
	if (ans1 > 2 && chk(ans1 - 1, 'A', 'D')) ans1--;
	cout << min((r1 - l1 + 1) * ans2, (r2 - l2 + 1) * ans1) << '\n';
	//不变高 * 变宽 或 不变宽 * 变高 
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：摸鱼酱 (赞：0)

[CF1202C You Are Given a WASD-string...](https://www.luogu.com.cn/problem/CF1202C)

给定一个长度为 $n$ 的 `WASD` 组成的移动序列，四个字母分别对应在方格纸上向上左下右走一格，定义权值为最小的能包含所有被经过的格子的矩形的面积，求至多在序列任意位置插入任意一个上述移动后能达到的最小权值。

$1\leq n\leq 2\times 10^5$。

首先发现横纵坐标是独立的，假设原本移动序列的权值为 $a\times b$，则猜想答案会是 $\min\{(a-1)\times b,a\times (b-1)\}$，即插入的操作使得长的那边退回来一步，但是考虑这样一个操作序列 `ADAD` 原本是 $1\times 2$，但任意添加操作之后并不能让权值变为 $0\times 2$，甚至不能变为 $1\times 1$，这启发我们更深入地思考。

我们把问题转化为分别检查 $a,b$ 是否能减一，因为减一就是最大可能的贡献，即得到了一个 `+1/-1` 序列，将其做前缀和，贡献就是前缀和的 $\max-\min+1$，问是否能在其中插入一个 `+1/-1` 使得这个贡献减一，也就是将其前缀和数组的一个后缀 `+1/-1`。

不难发现，若这个后缀中同时存在最大值和最小值，那么显然是不行的，因为它们同时改变是不会贡献的；若这个后缀以外的前缀中同时存在最大值和最小值，那么也是不行的，因为它们根本就没有受到影响。所以我们需要找到这样一个位置，使得它能够把最大值出现的位置和最小值出现的位置分开，即最大值只出现在这个位置之前，最小值只出现在这个位置之后或者反过来，那么我们就可以在这里插入一个操作使得贡献减一。

特殊的是，若出现了分割点是最值，分割点的前一个位置是另一种最值，即序列的前缀和在 `0,-1` 或是 `0,1` 之间横跳，也是不行的，所以实现上我们只需要检查最后一个最大值的位置加一是否小于第一个最小值的位置，或者反过来。

于是就 $a,b$ 分开检查再最和计算答案，时间复杂度 $O(n)$，[一份参考代码实现](https://www.luogu.com.cn/paste/nvseqyrl)。

---

## 作者：fanypcd (赞：0)

### 题意：

给定一个行走序列（上下左右），可以在任意位置加入一次行走操作（也可以不加），求最终能囊括整个行走范围的矩形面积的最小值。

### 分析：

看一下怎么求出能囊括整个行走范围的矩形面积的最小值。

假设经过的第 i 个点的横坐标为 $x_i$，纵坐标为 $y_i$，那么矩形面积就应该是 $(\max \limits_{i=1} ^{n} x_i - \min \limits_{i=1} ^ {n}x_i + 1) \times (\max \limits_{i=1} ^{n} y_i - \min \limits_{i=1} ^ {n}y_i + 1)$。

感觉不能一眼看出加入的行走操作该放到哪里，那就只好都试一遍了。

枚举放的位置和放什么操作后，如果能 $O(1)$ 求出加入了操作后的矩形面积，那这道题就做完了。

仔细想想其实挺容易的。

加入的操作会把原来的操作序列分成两个部分，前面的部分显然横纵坐标的最值不变，后面的部分横纵坐标之一的最值会视具体操作而变化 1。

于是先 $O(n)$ 记录下每次操作到操作结束之间经过的点的横纵坐标最值，模拟加入操作时再和之前的最值比较一下即可得出此时的最小面积。

时间复杂度 $O(Tn)$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define N 200005
char s[N];
int n;
int minx[N], miny[N], maxx[N], maxy[N];
void walk(char opt, int &x, int &y, int delta)
{
	switch(opt)
	{
		case 'W': y += delta; break;
		case 'A': x -= delta; break;
		case 'S': y -= delta; break;
		case 'D': x += delta; break;
		default: assert(0 == 1);
	}
	return;
}
void solve()
{
	int nowx = 0, nowy = 0;
	minx[n + 1] = maxx[n + 1] = miny[n + 1] = maxy[n + 1] = 0;
	for(int i = n; i >= 1; i--)
	{
		walk(s[i], nowx, nowy, -1);
		minx[i] = min(minx[i + 1], nowx), maxx[i] = max(maxx[i + 1], nowx);
		miny[i] = min(miny[i + 1], nowy), maxy[i] = max(maxy[i + 1], nowy);
	}
	int ans = (maxx[1] - minx[1] + 1) * (maxy[1] - miny[1] + 1);
	int xmin = nowx, xmax = nowx, ymin = nowy, ymax = nowy;
	for(int i = 1; i <= n; i++)
	{
		walk(s[i], nowx, nowy, 1);
		xmin = min(xmin, nowx), xmax = max(xmax, nowx);
		ymin = min(ymin, nowy), ymax = max(ymax, nowy);
		ans = min(ans, (max(xmax, maxx[i + 1]) - min(xmin, minx[i + 1]) + 1) * (max(ymax, maxy[i + 1] + 1) - min(ymin, miny[i + 1] + 1) + 1));//W
		ans = min(ans, (max(xmax, maxx[i + 1] - 1) - min(xmin, minx[i + 1] - 1) + 1) * (max(ymax, maxy[i + 1]) - min(ymin, miny[i + 1]) + 1));//A
		ans = min(ans, (max(xmax, maxx[i + 1]) - min(xmin, minx[i + 1]) + 1) * (max(ymax, maxy[i + 1] - 1) - min(ymin, miny[i + 1] - 1) + 1));//S
		ans = min(ans, (max(xmax, maxx[i + 1] + 1) - min(xmin, minx[i + 1] + 1) + 1) * (max(ymax, maxy[i + 1]) - min(ymin, miny[i + 1]) + 1));//D
	}
	printf("%lld\n", ans);
	return;
}
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		solve();
	}
	return 0;
}
```

---

## 作者：Sun_wtup (赞：0)

# CF1202C You Are Given a WASD-string... 题解
[题目传送](https://www.luogu.com.cn/problem/CF1202C)
## 题意
有一个机器人，给出一个只由 $\texttt{WASD}$ 组成的字符串控制它行走。$\texttt{W}$ 代表上，$\texttt{S}$ 代表下，$\texttt{A}$ 代表左，$\texttt{D}$ 代表右。可以在给定的字符串中加入这四个字母中的一个（也可以不加），改变机器人行动轨迹，使其经过的所有矩形面积最小。
## 分析与思路
我们可以把字符串中的上下走和左右走的分开，分别统计最上面，最下面，最左面，最右面到达的位置（假设初始位置为 $0$，$0$）。然后把横着走的（即左右走）和竖着做的（即上下走的）单独拎出来看。我们要判断能不能减小走完后的长和宽,如果不能就输出原面积，如果能就取最小值输出。
## 实现
统计上下左右方向的最值很简单，接着最难得部分就是判断能不能缩小。我们定义 $\texttt{W}$ 是 $1$，$\texttt{S}$ 是 $-1$，$\texttt{A}$ 是 $-1$，$\texttt{D}$ 是 $1$。以样例的 $\texttt{DSAWWAW}$ 举例，可以得到横着走的是 $\texttt{DAA}$，竖着走的是 $\texttt{SWWW}$，我们要想缩小矩形面积，长或宽，而长由最上面和最下面的值决定，宽由最左面和最右面的值决定。那么我们就需要缩小最大值，但最小值不动。或者扩大最小值，但最大值不动（因为 $\texttt{A}$ 是 $-1$，$\texttt{D}$ 是 $1$，所以最左面的值就是横着的最小值，最右面就是横着的最大值，同样对于竖着的，最上面就是最大值，最下面就是最小值）。

先处理横着的，想要变小最大值，就必须在它第一次出现**之前**插入一个能使最大值变小的字母，而且不能在最小值最后一次出现之前插入，因为这样会使最大值与最小值同时变大或变小，极差还是没有变（例如$\texttt{ADAADDD}$，这时两个最值出现的时间分别是 $4$ 和 $7$，如果在第三个 $\texttt{A}$ 前加一个 $\texttt{D}$，就会使后面的值都加 $1$，最小值是 $-1$，最大值是 $2$，两个最值同时变化同时变化同样的值，极差不变）。类似的，若果想变大最小值，就要在它第一次出现之前处理，且在最大值最后一次出现之后处理。还有一种特殊情况，就是一个最值第一次出现的时间与另一个最值最后一次出现的时间相差 $1$，这种情况也不能缩小极差，换句话说无法缩小面积。然后我们要就记录最大值和最小值第一次和最后一次出现的时间，判断一个最值第一次出现的时间-另一个最值最后一次出现的时间是否大于 $1$，然后再把这一个第最值一次出现的时间改为最后一次出现的时间，另一个同理，再比较一遍，只要满足一个，就能缩小极差了。

竖着的同理，最后在给这两种情况（减小横着的极差，减小竖着的极差）取最小值即可（不减小的答案为（最右面-最左面+$1$）$\times$（最上面-最下面+$1$））。
## Code
``` cpp
#include <bits/stdc++.h>
//#include <windows.h>
//#include <psapi.h>
//#include <time.h>
using namespace std;
#define debug(x) std::cerr<<#x<<'='<<x<<std::endl
#define int long long
int sideway,vertical;//分别为横，竖
int up,down,lft,rigt;
int upfirstime,downfirstime,leftfirstime,rightfirstime;
int uplastime,downlastime,leftlastime,rightlastime;
string  reset(string a){//将字符串改为从 1 开始
    string t="+";
    for(int i=0;i<a.size();i++)t+=a[i];
    a="";
    a+=t;
    return a;
}
void clear(){//清空
    sideway=vertical=0;
    up=down=lft=rigt=0;
    upfirstime=downfirstime=leftfirstime=rightfirstime=0;
    uplastime=downlastime=leftlastime=rightlastime=0;
}
void handle(string a){//记录每个最值的两个时间
    for(int j=1;j<=a.size();j++){
        if(a[j]=='W')vertical++;
        else if(a[j]=='S')vertical--;
        else if(a[j]=='A')sideway--;
        else if(a[j]=='D')sideway++;
        if(vertical>up)up=vertical,upfirstime=j;
        if(vertical==up)uplastime=j;
        if(vertical<down)down=vertical,downfirstime=j;
        if(vertical==down)downlastime=j;
        if(sideway>rigt)rigt=sideway,rightfirstime=j;
        if(sideway==rigt)rightlastime=j;
        if(sideway<lft)lft=sideway,leftfirstime=j;
        if(sideway==lft)leftlastime=j;
    }
    // debug(vertical);
    // debug(sideway);
}
signed main()
{
//  freopen("Luogu_CF_1202_C.cpp.in","r",stdin);
//  freopen("Luogu_CF_1202_C.cpp.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    string a;
    for(int i=1;i<=n;i++){
        cin>>a;
        int ans=0;
        a=reset(a);
    //    cout<<a<<" ";
        clear();
        handle(a);
        ans=(up-down+1)*(rigt-lft+1);//不减小的面积
        if(leftfirstime-rightlastime>1 or rightfirstime-leftlastime>1)ans=min(ans,(up-down+1)*(rigt-lft));
        if(upfirstime-downlastime>1 or downfirstime-uplastime>1)ans=min(ans,(up-down)*(rigt-lft+1));
        cout<<ans<<"\n";//判断，取最小值
    }
//  fclose(stdin);
//  fclose(stdout);
    return 0;
}
```

本蒟蒻水平有限，如有不周之处，希望能原谅。

---

## 作者：tzc_wk (赞：0)

### 题意：
有一个由“WASD"组成的字符串$s$，代表机器人的移动命令。"W"表示向上移动一格，"A"表示向左移动一格，"S"表示向下移动一格，"D"表示向右移动一格。这个机器人的轨迹可以被一个矩形正好包围，现在允许你在$s$的任意位置添上"WASD"中的**一个**字符，也可以不添，形成一个新的指令，使得这个矩形的面积尽可能小。题目包含多测。

### 思路：
~~我的做法可能和大家不太一样。~~ 

前缀和+线段树。首先我们先用前缀和将进行完第$i$个指令之后机器人的位置求出来。我们记$sum_{i,0}$表示进行完第$i$个指令之后机器人的纵坐标，$sum_{i,1}$表示进行完第$i$个指令之后机器人的横坐标。因此矩形的面积就是


$S=(max(sum[1][0],sum[2][0],\dots,sum[n][0],0)-min(sum[1][0],sum[2][0],\dots,sum[n][0],0)+1)*(max(sum[1][1],sum[2][1],\dots,sum[n][1],0)-min(sum[1][1],sum[2][1],\dots,sum[n][1],0)+1);$

而我们枚举每一个位置$i$，在第$i$个位置后面添上一个'W'其实就是$sum_{i,1}=sum_{i-1,1}+1,sum_{i+1,1}=sum_{i,1}+1,sum_{i+2,1}=sum_{i+1,1}+1,\dots sum_{n+1,1}=sum_{n,1}$，其他也一样，这个操作可以用线段树来维护。

然后Div.1.5C，Div.1B的难度的题。就可以愉快地解决了！

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T;
string s;
int sum[200005][2];
struct seg{//线段树的代码。不会线段树的前往https://blog.csdn.net/huangzihaoal/article/details/81813454
	struct node{
		int l,r,mn,mx,lz;
	} s[800005];
	inline void build(int k,int l,int r,int type){
		s[k].l=l;s[k].r=r;
		if(l==r){
			s[k].mn=s[k].mx=sum[l][type];
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid,type);
		build(k<<1|1,mid+1,r,type);
		s[k].mn=min(s[k<<1].mn,s[k<<1|1].mn);
		s[k].mx=max(s[k<<1].mx,s[k<<1|1].mx);
	}
	inline void pushdown(int k){
		s[k<<1].mx+=s[k].lz;
		s[k<<1].mn+=s[k].lz;
		s[k<<1].lz+=s[k].lz;
		s[k<<1|1].mx+=s[k].lz;
		s[k<<1|1].mn+=s[k].lz;
		s[k<<1|1].lz+=s[k].lz;
	}
	inline void change(int k,int l,int r,int val){
		if(l>r)	return;
		if(l<=s[k].l&&s[k].r<=r){
			s[k].lz+=val;
			s[k].mx+=val;
			s[k].mn+=val;
			return;
		}
		pushdown(k);
		int mid=(s[k].l+s[k].r)>>1;
		if(r<=mid)		change(k<<1,l,r,val);
		else if(l>mid)	change(k<<1|1,l,r,val);
		else			change(k<<1,l,mid,val),change(k<<1|1,mid+1,r,val);
		s[k].mn=min(s[k<<1].mn,s[k<<1|1].mn);
		s[k].mx=max(s[k<<1].mx,s[k<<1|1].mx);
	}
	inline int query_mn(){
		return s[1].mn;
	}
	inline int query_mx(){
		return s[1].mx;
	}
} st[2];
int area(){
	return (max(st[0].query_mx(),0ll)-min(st[0].query_mn(),0ll)+1)*(max(st[1].query_mx(),0ll)-min(st[1].query_mn(),0ll)+1);
}
signed main(){
	cin>>T;
	while(T--){
		cin>>s;
		s=" "+s;
		for(int i=0;i<=s.size();i++)	sum[i][0]=sum[i][1];//清空sum数组，因为用memset会超时所以这样循环地写。
		for(int i=1;i<s.size();i++){//求前缀和，即执行完第i个指令后机器人的横纵坐标
			sum[i][0]=sum[i-1][0];
			sum[i][1]=sum[i-1][1];
			if(s[i]=='W')	sum[i][0]++;
			if(s[i]=='A')	sum[i][1]--;
			if(s[i]=='S')	sum[i][0]--;
			if(s[i]=='D')	sum[i][1]++;
		}
		st[0].build(1,1,s.size()-1,0);
		st[1].build(1,1,s.size()-1,1);//建树
		int ans=area();//不添加任何字符
		for(int i=0;i<=s.size();i++){
        	//在第i个字符后添加'A'
			st[0].change(1,i,s.size()-1,-1);
			ans=min(ans,(max(st[0].query_mx(),0ll)-min(st[0].query_mn(),min(sum[i-1][0]-1,0ll))+1)*(max(st[1].query_mx(),0ll)-min(st[1].query_mn(),0ll)+1));
			st[0].change(1,i,s.size()-1,1);
            //在第i个字符后添加'D'
			st[0].change(1,i,s.size()-1,1);
			ans=min(ans,(max(st[0].query_mx(),max(sum[i-1][0]+1,0ll))-min(st[0].query_mn(),0ll)+1)*(max(st[1].query_mx(),0ll)-min(st[1].query_mn(),0ll)+1));
			st[0].change(1,i,s.size()-1,-1);
            //在第i个字符后添加'W'
			st[1].change(1,i,s.size()-1,-1);
			ans=min(ans,(max(st[0].query_mx(),0ll)-min(st[0].query_mn(),0ll)+1)*(max(st[1].query_mx(),0ll)-min(st[1].query_mn(),min(sum[i-1][1]-1,0ll))+1));
			st[1].change(1,i,s.size()-1,1);
            //在第i个字符后添加'S'
			st[1].change(1,i,s.size()-1,1);
			ans=min(ans,(max(st[0].query_mx(),0ll)-min(st[0].query_mn(),0ll)+1)*(max(st[1].query_mx(),max(sum[i-1][1]+1,0ll))-min(st[1].query_mn(),0ll)+1));
			st[1].change(1,i,s.size()-1,-1);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

