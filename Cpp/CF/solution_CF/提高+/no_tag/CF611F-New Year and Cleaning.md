# New Year and Cleaning

## 题目描述

Limak is a little polar bear. His parents told him to clean a house before the New Year's Eve. Their house is a rectangular grid with $ h $ rows and $ w $ columns. Each cell is an empty square.

He is a little bear and thus he can't clean a house by himself. Instead, he is going to use a cleaning robot.

A cleaning robot has a built-in pattern of $ n $ moves, defined by a string of the length $ n $ . A single move (character) moves a robot to one of four adjacent cells. Each character is one of the following four: 'U' (up), 'D' (down), 'L' (left), 'R' (right). One move takes one minute.

A cleaning robot must be placed and started in some cell. Then it repeats its pattern of moves till it hits a wall (one of four borders of a house). After hitting a wall it can be placed and used again.

Limak isn't sure if placing a cleaning robot in one cell will be enough. Thus, he is going to start it $ w·h $ times, one time in each cell. Maybe some cells will be cleaned more than once but who cares?

Limak asks you one question. How much time will it take to clean a house? Find and print the number of minutes modulo $ 10^{9}+7 $ . It's also possible that a cleaning robot will never stop — then print "-1" (without the quotes) instead.

Placing and starting a robot takes no time, however, you must count a move when robot hits a wall. Take a look into samples for further clarification.

## 说明/提示

In the first sample house is a grid with $ 10 $ rows and $ 2 $ columns. Starting a robot anywhere in the second column will result in only one move (thus, one minute of cleaning) in which robot will hit a wall — he tried to go right but there is no third column. Starting a robot anywhere in the first column will result in two moves. The total number of minutes is $ 10·1+10·2=30 $ .

In the second sample a started robot will try to move "RULRULRULR..." For example, for the leftmost cell in the second row robot will make $ 5 $ moves before it stops because of hitting an upper wall.

## 样例 #1

### 输入

```
1 10 2
R
```

### 输出

```
30
```

## 样例 #2

### 输入

```
3 4 6
RUL
```

### 输出

```
134
```

## 样例 #3

### 输入

```
4 1 500000
RLRL
```

### 输出

```
-1
```

# 题解

## 作者：Light_snow (赞：8)

## 想法

这个题是$NOIP2020$的弱化版。。

我们把所有在二维上的点都一起考虑，那么所有点对于一个步骤的移动是相当于这些所有点所组成的矩形在移动。


![](https://cdn.luogu.com.cn/upload/image_hosting/5ejfsbmr.png)

黑色的是我们的规定区域，蓝色的是我们所有二维的点的矩阵，可以看出对于每一步所出界的贡献我们是可以用这个超出的矩形面积来算的。

我们在移的过程中，维护现在这个矩形的左上和右下的端点就可以解决，超界就拉回来。

但是我们发现有些点是会走很多很多很多轮的，复杂度代价太高。

这里建议读者手玩几组样例，我们会发现，除了第一次的计算外，第二第三轮，在每一步所出界的边是一样的。

所以我们单独处理第一轮，第二轮，记录第二轮出界的边以及在第几轮出界，然后在第$(n > 2)$轮我们要维护的就是这个矩形的长宽了。

可能代码会更加清晰一些。

## 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long

ll n,h,w;
ll x1,x2,y1,y2;
ll mod = 1e9 + 7;
char s[1000005];

void get(ll &x,ll &y,int k){
	if(s[k] == 'U')y -- ;
	if(s[k] == 'R')x ++ ;
	if(s[k] == 'D')y ++ ;
	if(s[k] == 'L')x -- ;
} 

ll ans = 0;

ll c[1000005],e[1000005];

int main(){
	scanf("%lld%lld%lld",&n,&h,&w);
	scanf("%s",s + 1);
	ll k = strlen(s + 1);
	x1 = 1,x2 = w,y1 = 1,y2 = h;
	for(int i = 1;i <= k;++i){
		get(x1,y1,i);
		get(x2,y2,i);
		if(x1 == 0&&x1 <= x2&&y1 <= y2)x1 = 1,ans = (ans + i * (y2 - y1 + 1) % mod) % mod;
		if(x2 == w + 1&&x1 <= x2&&y1 <= y2)x2 = w,ans = (ans + i * (y2 - y1 + 1) % mod) % mod;
		if(y1 == 0&&x1 <= x2&&y1 <= y2)y1 = 1,ans = (ans + i * (x2 - x1 + 1) % mod) % mod;
		if(y2 == h + 1&&x1 <= x2&&y1 <= y2)y2 = h,ans = (ans + i * (x2 - x1 + 1) % mod) % mod;						
	}
	ll num = 0;
	for(int i = 1;i <= k;++i){
		get(x1,y1,i);
		get(x2,y2,i);
		if(x1 == 0&&x1 <= x2&&y1 <= y2)x1 = 1,ans = (ans + (i + n) * (y2 - y1 + 1) % mod) % mod,c[++num] = i,e[num] = 0;
		if(x2 == w + 1&&x1 <= x2&&y1 <= y2)x2 = w,ans = (ans + (i + n) * (y2 - y1 + 1) % mod) % mod,c[++num] = i,e[num] = 0;
		if(y1 == 0&&x1 <= x2&&y1 <= y2)y1 = 1,ans = (ans + (i + n) * (x2 - x1 + 1) % mod) % mod,c[++num] = i,e[num] = 1;
		if(y2 == h + 1&&x1 <= x2&&y1 <= y2)y2 = h,ans = (ans + (i + n) * (x2 - x1 + 1) % mod) % mod,c[++num] = i,e[num] = 1;						
	}
	if(!num && x1 <= x2 && y1 <= y2){puts("-1");return 0;}
	for (ll nw=2,x=x2-x1+1,y=y2-y1+1;x>0&&y>0;nw++)
		for (int i=1;i<=num;i++) 
		{
			if (e[i] == 1&&x>0&&y>0) ans = (ans + std::max(x,0ll)*(nw * n % mod + c[i]) % mod) % mod,y--;
			if (e[i] == 0&&x>0&&y>0) ans = (ans + std::max(y,0ll)*(nw * n % mod + c[i]) % mod) % mod,x--;
		}
	std::cout<<ans % mod;
}
```

---

## 作者：__stick (赞：1)

## 题意

一个 $w\times h$ 的方格，每次一个机器人沿着一个固定路径走，遇到边界就停止，问从每个节点开始一共能走多少步。

## 思路

一个非常暴力的想法是先模拟一遍从 $(0,0)$ 开始的走路过程，找出向每个方向走 $i$ 格最少需要走多少步，然后预处理出来每一行水平方向能走多多少格，每一列竖直方向能走多少格，然后就是枚举每一个格子，对所在行列答案取一下 min 就是当前格子对答案的贡献。

然而这样复杂度爆炸，肯定不能通过，但是会发现有很多格子的计算是重复且无意义的，具体的，我们设当前格子水平方向上 $x$ 步出界，竖直方向上 $y$ 步出界，答案就是 $\min(x,y)$ 如果 $x$ 小于 $y$ 的话 $y$ 的增加减少对答案毫无影响。

由于我们必须计算每一个位置对答案的贡献，则说明每一个横坐标都要和每一个纵坐标进行匹配，那当前横坐标上的出界次数对答案的贡献就是所有纵坐标最小出界次数中大于等于它的数的个数。

纵坐标也是同理，不过不能带上等号，否则就重复了。

这种问题就是双指针的经典问题了，排个序双指针扫一下就做完了，当然二分也是可以通过的。
## 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define mp make_pair
const int mod=1e9+7;
const int MAXN=5e5+10;
int X[MAXN*2],Y[MAXN*2];
int mmin=0;
ll work(int i,int x,int l,int r,int h,int X[],int n)
{
	ll ans=1e18;
	if(x>0)
	{
		if(i+r>h)cmin<ll>(ans,X[h-i+1+MAXN]);
		else
		{
			int k=(h-r-i)/x;
			while(i+k*x+r<=h)k++;
      		cmin<ll>(ans,X[h-i-k*x+1+MAXN]+(ll)k*n);
		}
	}
	if(x<0)
	{
		if(i-l<1)cmin<ll>(ans,X[-i+MAXN]);
		else
		{
			int k=(l-i)/x;
			while(i+k*x-l>0)k++;
			cmin<ll>(ans,X[-k*x-i+MAXN]+(ll)k*n);
		}
	}
	if(i+r>h)cmin<ll>(ans,X[h-i+1+MAXN]);
	if(i-l<1)cmin<ll>(ans,X[-i+MAXN]);
	return ans;
}
ll a[MAXN],b[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,h,w;cin>>n>>h>>w;
	string s;cin>>s;s=' '+s;s.shrink_to_fit();
	int mx1=0,my1=0,mx2=0,my2=0;
	auto nxt=[&](int& x,int& y,char c)
	{
		if(c=='U')x--;
		else if(c=='D')x++;
		else if(c=='L')y--;
		else if(c=='R')y++;
	};
	int x=0,y=0;
	for(int i=1;i<=n;i++)
	{
		nxt(x,y,s[i]);
		if(x>0)cmax(mx1,x);
		else cmax(mx2,-x);
		if(y>0)cmax(my1,y);
		else cmax(my2,-y);		
		if(!X[x+MAXN])X[x+MAXN]=i;
		if(!Y[y+MAXN])Y[y+MAXN]=i;
	}
	for(int i=1;i<=h;i++)
	{
		a[i]=work(i,x,mx2,mx1,h,X,n);
	}
	for(int i=1;i<=w;i++)
	{
		b[i]=work(i,y,my2,my1,w,Y,n);
	}
	sort(a+1,a+h+1),sort(b+1,b+w+1);
	if(a[h]==1e18&&b[w]==1e18)
	{
		cout<<-1;
		return 0;
	}
	int i=1,j=1;
	ll ans=0,sum=0;
	while(i<=h)
	{
		while(j<=w&&a[i]>=b[j])sum+=b[j]%mod,j++,sum%=mod;
		a[i]%=mod;
		ans+=(ll)(w-j+1)*(a[i])%mod+sum;ans%=mod;
		i++;
	}
	cout<<ans%mod;
 	return 0;
}
```


---

## 作者：lfxxx (赞：0)

想清楚就不难。

我们考虑讨论下每个点出发是怎么走出界的。

显然分为 $4$ 类共 $2 \times (w+h)$ 种，即向方向 $ty$ 走了 $c$ 步走出界。假设向走出界的方向总共走了 $st$ 步（假若往其相反的方向移动一步则视为减去一步）。

一种走出界在一个格子上会发生说明第 $c$ 步时第一次在方向 $ty$ 上走了 $st$ 步，且在第 $1$ 步到第 $c-1$ 步时往与 $ty$ 垂直的方向走到的最远处没有走出界并且往与 $ty$ 相反的方向移动的步数加上 $st$ 也没有出界，更进一步地，我们发现界限大小减去往与 $ty$ 垂直的方向走到的两个最远处之间的距离就是满足条件的格子数。

于是考虑对 $2 \times (w+h)$ 种情况分别求出 $c$，这一步可以通过预处理一个周期内第一次走到某个最远距离的步数与一整个周期走完在某个方向上总共移动的步数得到，然后再按照 $c$ 排序计算贡献即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e5+114;
const int mod = 1e9+7;
int n,h,w;
char c[maxn];
//0-上 1-下 2-左 3-右
int cnt[maxn][4];//一次循环中 4 个方向第一次走到多远是走了多少步
int mx[4];
int sum[4];
vector< pair<int,pair<int,int> > > opt;//(最初到达需要多少步,哪个方向,这个方向上走了多少格)
void ins(int ty,int st){
    //方向 走了多少格
    if(cnt[st][ty]<0x3f3f3f3f){
        opt.push_back(make_pair(cnt[st][ty],make_pair(ty,st)));
        return ;
    }
    if(sum[ty]<=0) return ;
    //st-k*sum[ty]<=mx[ty]
    //k*sum[ty]>=st-mx[ty]
    int k=(st-mx[ty]+sum[ty]-1)/sum[ty];
    st-=k*sum[ty];
    opt.push_back(make_pair(cnt[st][ty]+k*n,make_pair(ty,st+k*sum[ty])));
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>h>>w;
    for(int i=1;i<=n;i++) cin>>c[i];
    int x=0,y=0;
    memset(cnt,0x3f3f3f3f,sizeof(cnt));
    cnt[0][0]=cnt[0][1]=cnt[0][2]=cnt[0][3]=0;
    for(int i=1;i<=n;i++){
        if(c[i]=='U') x++;
        else if(c[i]=='D') x--;
        else if(c[i]=='L') y--;
        else y++;
        if(x>0) cnt[x][0]=min(cnt[x][0],i),mx[0]=max(mx[0],x);
        else if(x<0) cnt[-x][1]=min(cnt[-x][1],i),mx[1]=max(mx[1],-x);
        if(y>0) cnt[y][3]=min(cnt[y][3],i),mx[3]=max(mx[3],y);
        else if(y<0) cnt[-y][2]=min(cnt[-y][2],i),mx[2]=max(mx[2],-y);
    }
    sum[0]=x,sum[1]=-x,sum[2]=-y,sum[3]=y;
    for(int i=0;i<2;i++)
        for(int j=1;j<=h;j++) ins(i,j);
    for(int i=0;i<2;i++)
        for(int j=1;j<=w;j++) ins(i+2,j); 
    int sum=0;
    int ans=0;
    sort(opt.begin(),opt.end());
    int u=0,d=0,l=0,r=0;
    for(pair<int,pair<int,int> > now:opt){
        int ty=now.second.first,st=now.second.second;
        if(ty==0){
            if(st+d<=h){
                ans+=max(0*1ll,w-l-r)*now.first%mod;
                sum+=max(0*1ll,w-l-r);
            }
            u=max(u,st);
        }else if(ty==1){
            if(st+u<=h){
                ans+=max(0*1ll,w-l-r)*now.first%mod;
                sum+=max(0*1ll,w-l-r);
            }
            d=max(d,st);
        }else if(ty==2){
            if(st+r<=w){
                ans+=max(0*1ll,h-u-d)*now.first%mod;
                sum+=max(0*1ll,h-u-d);
            }
            l=max(l,st);
        }else{
            if(st+l<=w){
                ans+=max(0*1ll,h-u-d)*now.first%mod;
                sum+=max(0*1ll,h-u-d);
            }   
            r=max(r,st); 
        }
        ans%=mod;
    }
    if(sum<h*w){
        cout<<"-1\n";
        return 0;
    }else cout<<ans<<"\n";
    return 0;
}
```

---

