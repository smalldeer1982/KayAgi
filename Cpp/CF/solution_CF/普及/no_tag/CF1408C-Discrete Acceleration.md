# Discrete Acceleration

## 题目描述

There is a road with length $ l $ meters. The start of the road has coordinate $ 0 $ , the end of the road has coordinate $ l $ .

There are two cars, the first standing at the start of the road and the second standing at the end of the road. They will start driving simultaneously. The first car will drive from the start to the end and the second car will drive from the end to the start.

Initially, they will drive with a speed of $ 1 $ meter per second. There are $ n $ flags at different coordinates $ a_1, a_2, \ldots, a_n $ . Each time when any of two cars drives through a flag, the speed of that car increases by $ 1 $ meter per second.

Find how long will it take for cars to meet (to reach the same coordinate).

## 说明/提示

In the first test case cars will meet in the coordinate $ 5 $ .

The first car will be in the coordinate $ 1 $ in $ 1 $ second and after that its speed will increase by $ 1 $ and will be equal to $ 2 $ meters per second. After $ 2 $ more seconds it will be in the coordinate $ 5 $ . So, it will be in the coordinate $ 5 $ in $ 3 $ seconds.

The second car will be in the coordinate $ 9 $ in $ 1 $ second and after that its speed will increase by $ 1 $ and will be equal to $ 2 $ meters per second. After $ 2 $ more seconds it will be in the coordinate $ 5 $ . So, it will be in the coordinate $ 5 $ in $ 3 $ seconds.

In the second test case after $ 1 $ second the first car will be in the coordinate $ 1 $ and will have the speed equal to $ 2 $ meters per second, the second car will be in the coordinate $ 9 $ and will have the speed equal to $ 1 $ meter per second. So, they will meet after $ \frac{9-1}{2+1} = \frac{8}{3} $ seconds. So, the answer is equal to $ 1 + \frac{8}{3} = \frac{11}{3} $ .

## 样例 #1

### 输入

```
5
2 10
1 9
1 10
1
5 7
1 2 3 4 6
2 1000000000
413470354 982876160
9 478
1 10 25 33 239 445 453 468 477```

### 输出

```
3.000000000000000
3.666666666666667
2.047619047619048
329737645.750000000000000
53.700000000000000```

# 题解

## 作者：7KByte (赞：4)

暴力美学，直接二分。

我们二分时间，然后判断两个人是否在规定时间内相遇。

判断也很容易，我们$\rm O(N)$扫一遍，然后用两个人走过的路程和与$l$比较一下。

注意下精度问题，这里$eps=10^{-7}$，精度低会WA，精度高容易TLE。
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
using namespace std;
int n,a[N],l;
double tm[N];
bool check(double tm){
	double now=tm;
	double sp=1,dn=0;
	rep(i,1,n+1){
		if((a[i]-a[i-1])/sp<now){
			now-=(a[i]-a[i-1])/sp;
			dn+=a[i]-a[i-1];sp++;
		}
		else{
			dn+=sp*now;now=0;
		}
	}
	if(now)return true;
	sp=1;now=tm;
	pre(i,n,0){
		if((a[i+1]-a[i])/sp<=now){
			now-=(a[i+1]-a[i])/sp;
			dn+=a[i+1]-a[i];sp++;
		}
		else{
			dn+=sp*now;now=0;
		}
	}
	if(dn>a[n+1])return true;
	return false;
}
void solve(){
	scanf("%d",&n);scanf("%d",&a[n+1]);
	rep(i,1,n)scanf("%d",&a[i]);
	double l=0,r=a[n+1];
	while(fabs(l-r)>1e-7){
		double mid=(l+r)/2.00;
		//cout<<l<<" "<<r<<" "<<mid<<endl; 
		if(check(mid))r=mid;
		else l=mid;
	}
	printf("%.8lf\n",l);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
} 
```

---

## 作者：jun头吉吉 (赞：3)

# CF1408C 【Discrete Acceleration】
[$\color{red}{\sout{\text{更好的}}}\color{block}{\text{阅读体验}}$](https://chen-jia-liang.gitee.io/blog/2020/10/01/%E9%A2%98%E8%A7%A3-CF1408C-%E3%80%90Discrete-Acceleration%E3%80%91/)
## 题意
有两辆小车，分别在数轴的$0$与$l$，相向而行。有$n$面旗子，分别在$a_1,a_2,\dots,a_n$，小车每经过一面旗子速度加一，求用多久相遇。

($1<a_1<a_2\ldots<a_n<l$)

## 题解
看着官方题解$O(n \log{\frac{1}{\epsilon}})$和$O(n)$的做法，小蒟蒻陷入了沉思……

在比赛的时候只想出一个$O(n\times \log_2(\frac{l}{eps})\times log_2(n))$的做法，由于数据比较水就过了

首先，第一只$\log$我们来枚举所需要的时间。如果一个旗子也没有，那么很明显所用的时间为$\frac l 2$，因此二分上节定位$\frac l 2$。

设两辆车分别为$A$、$B$。

来考虑相遇意味着什么：在这个时间点前$A$，$B$的坐标$A_x<B_x$，在这个点后$A_x>B_x$。因此二分很明显是正确的。我们只需要找第一个$A_x≥ B_x$的点即可。

那么`check()`怎么写呢？如果暴力一个一个旗子过的话，`check()`会被卡到$O(n)$，这显然不是我们所期望的。

但如果我们用$At_x$表示$A$到第$x$面旗所花的时间，$Av_x$表示过了这个点所用的速度。那么我们只需要找到一个

$$At_x<time\le At_{x+1} $$

那么$At_x\to time$的速度就是$Av_{x}$，$A$的坐标即为$a_x+(time-At_{x})\times Av_x$

$At$与$Av$的处理很容易。并且$At$是单调上升的，同样可以二分。因此我们可以用$O(log_2(n))$找到$At_x<time\le At_{x+1}$,并求出$A_x$了。

$B$也是同理。

最后只需要比较$A_x$与$B_x$，`check()`就写完了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,L,a[100000+100];
int av[100000+100],bv[100000+100]; 
double at[100000+100],bt[100000+100];
const double eps=1e-7;
bool check(double time){
	int l1=0,r1=n+1,res;
	while(l1<=r1){
		int mid=l1+r1>>1;
		if(at[mid]<time)res=mid,l1=mid+1;
		else r1=mid-1;
	}
	double ax=a[res]+(time-at[res])*av[res];
	int l2=0,r2=n+1;
	while(l2<=r2){
		int mid=l2+r2>>1;
		if(bt[mid]<time)res=mid,r2=mid-1;
		else l2=mid+1;
	}
	double bx=a[res]-(time-bt[res])*bv[res];
	return bx<=ax;	
} 
signed main(){
	for(scanf("%d",&t);t--;){
		scanf("%d%d",&n,&L);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		a[0]=0,a[n+1]=L;
		at[0]=0,av[0]=1;
		for(int v=1,i=1;i<=n+1;i++)
			at[i]=at[i-1]+1.0*(a[i]-a[i-1])/v,
			v++,av[i]=v;
		bt[n+1]=0;bv[n+1]=1;
		for(int v=1,i=n;i>=0;i--)
			bt[i]=bt[i+1]+1.0*(a[i+1]-a[i])/v,
			v++,bv[i]=v;
		double l=0,r=1.0*L/2,ans;
		while(l+eps<r){
			double mid=(l+r)/2;
			if(check(mid))ans=mid,r=mid;
			else l=mid;
		}
		printf("%.10lf\n",ans);
	}
	
	return 0;
}
```

---

## 作者：钓鱼王子 (赞：2)

比较无聊的一道题。。。

按题意模拟，记录两个人的位置和速度，判断谁下一次进行变化即可。如果两人在同一段之间就输出答案即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,a[1000002],b[1000002],t,ans,pos1,pos2;
long double tim1,sp1,sp2,p1,p2;
int main(){
	t=read();
	while(t--){
		n=read(),m=read();
		for(re int i=sp1=sp2=1;i<=n;++i)a[i]=read();
		p1=0,p2=m;pos1=1,pos2=n;tim1=0;
		while(pos2-pos1>=0){
			long double tim=min((p2-a[pos2])/sp2,(a[pos1]-p1)/sp1);
			if((p2-a[pos2])/sp2<(a[pos1]-p1)/sp1){
				p2-=sp2*tim;
				p1+=sp1*tim;
				--pos2;++sp2;
			}
			else{
				p1+=sp1*tim;
				p2-=sp2*tim;
				++pos1;++sp1;
			}
			tim1+=tim;
		}
		printf("%.10Lf\n",tim1+(p2-p1)/(sp1+sp2));
	}
}
```


---

## 作者：yanxu_cn (赞：0)

### 分析

直接模拟，从两边分别做，每次处理判断哪边**先结束**这一段就先模拟，就可以轻松 $\Theta(n)$ 解决了。目前比洛谷的最优解还快？

小做一点提醒：输出请务必使用 `printf` 函数，用标准流式输出会导致丢精度和科学计数法的问题。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[100007];
int main()
{
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  register int T,n,l,flag1,flag2;
  long double t1,t2;
  cin>>T;
  while(T--)
  {
    cin>>n>>l;
    flag1=0;
    flag2=n;
    t1=t2=0;
    for(int i=1;i<=n;i++)cin>>f[i];
    f[0]=0,f[n+1]=l;
    #define v__1 (flag1+1)
    #define v__2 (n-flag2+1)
    #define distan__(flaggg) ((long double)(f[flaggg+1]-f[flaggg]))
    while(flag1!=flag2)
    {
      if(t1+((long double)distan__(flag1))/v__1<t2+((long double)distan__(flag2))/v__2)//move CarL
      {
        t1+=((long double)distan__(flag1))/v__1;
        flag1++;
      }
      else
      {
        t2+=((long double)distan__(flag2))/v__2;
        flag2--;
      }
    }
    printf("%.9llf\n",/*cout<<*/(double)(distan__(flag1)+v__1*t1+v__2*t2)/(v__1+v__2))/*<<'\n'*/;
    #undef v__1
    #undef v__2
    #undef distan__
  }
  return 0;
}
```
评测记录：
![](https://cdn.luogu.com.cn/upload/image_hosting/2whg7bxk.png)

---

## 作者：过氧化氢_syq0057 (赞：0)

好题，真的好题（

居然一遍过了 qaq~~（样例过了就是过了~~

## solution

模拟。

对于左右两个车，判断哪一个到下一个旗帜用时最短，直接让它跑过去，更新另一边，直到他们相遇（就是互相指向对方身后的旗帜），然后就赢了。

举个栗子：

样例中的
```
2 10
1 9
```
就是两车分别从 $0$ 和 $10$ 位置出发，同时到达 $1$ 和 $9$，耗时 $1s$，两车速度均变为 $2m/s$；下次两车到下一个旗帜之前就会相遇，所以耗时 $\frac{(9-1)}{4}=2s$，总耗时 $1s+2s=3s$。

再来个：

样例中的
```
5 7
1 2 3 4 6
```
两车分别从 $0$ 和 $7$ 位置出发，同时到达 $1$ 和 $6$，耗时 $1s$，两车速度均变为 $2m/s$；

下次左边的车率先到达 $2$ 位置，耗时 $\frac{1}{2}s$，速度变为 $3m/s$。右边到达 $5$ 位置，速度不变；

再下一次左边率先到达 $3$ 位置，耗时 $\frac{1}{3}s$，速度变为 $4m/s$。右边到达 $\frac{13}{3}$ 位置，速度不变；

再下一次右边率先到达 $4$ 位置，耗时 $\frac{1}{6}s$，速度变为 $3m/s$。左边到达 $\frac{11}{3}$ 位置，速度不变；

最后，两车在没有到达下一个旗帜前相遇，耗时 $\frac{4-\frac{11}{3}}{4+3}=\frac{1}{7}s$。

总耗时 $1s+\frac{1}{2}s+\frac{1}{3}s+\frac{1}{6}s+\frac{1}{7}s=\frac{7}{15}s=2.047619047619048...s$。

题解区大佬二分做法好强啊 /jy，吊打我这模拟 qwq。

## code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 100005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int T;
int n, L;
double a[N];
double ans;
int main() {
	scanf("%d", &T);
	int l, r; double ld, rd, lastld, lastrd, spl, spr, sl, sr; 
	while (T--) {
		ans = 0.0;
		scanf("%d%d", &n, &L);
		for (int i=1; i<=n; i++)
			scanf("%lf", &a[i]);
		l = 1, r = n, spl = spr = 1;
		for (int i=1; i<n; i++) {
			if (a[i] <= L && a[i + 1] > L) {
				r = i;
				break;
			}
		}//找一找右边的车从哪两个旗帜之间开始
		lastld = 0, lastrd = L;//分别是左右两边车的位置
		while (lastld < lastrd) {
			if (r - l == -1) {
				ans += (lastrd - lastld) / (spl + spr);
				break;
			}//如果下次就相遇（互相指向对方身后的旗帜）
			ld = (a[l] - lastld), rd = (lastrd - a[r]);
			sl = ld / spl, sr = rd / spr;//sl,sr分别是左右两边到下一个旗帜的时间,spl,spr分别是左右两边目前速度
//			printf("%.6lf %.6lf %.6lf %.6lf\n", ld, rd, sl, sr);
			if (sl < sr) {
				ans += sl;
				lastrd -= sl * spr, lastld = a[l];
				l++, spl++;
			}
			else if (sl > sr) {
				ans += sr;
				lastld += sr * spl, lastrd = a[r];
				r--, spr++;
			}
			else {
				ans += sl;
				lastld = a[l], lastrd = a[r];
				l++, r--, spl++, spr++;
			}//分三种情况讨论
//			printf("%.15lf ", ans);
//			printf("%.15lf %.15lf\n", lastld, lastrd);
		}
		printf("%.15lf\n", ans);
	}
	return 0;
}
```

完结散花 qaq

---

## 作者：s_r_f (赞：0)

对每个点计算左边的车到达这个点的时间，以及右边的车到达这个点的时间，然后找到两辆车相遇的位置即可。

$\Theta(n)$ 

code : 
```cpp
#include <bits/stdc++.h>
#define db long double
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
const int N = 100005;
int n,l,a[N]; db tl[N],tr[N];
inline void solve(){
	int i,p; db ans = 1e18,nt,nx,ny;
	read(n),read(l);
	a[0] = 0; for (i = 1; i <= n; ++i) read(a[i]); a[++n] = l;
	tl[0] = 0; for (i = 1; i <= n; ++i) tl[i] = tl[i-1] + (a[i] - a[i-1]) * 1.0 / i;
	tr[n] = 0; for (i = n-1; i >= 0; --i) tr[i] = tr[i+1] + (a[i+1] - a[i]) * 1.0 / (n-i); 
	for (i = 0; i < n; ++i){
		nt = max(tl[i],tr[i+1]),nx = a[i] + (nt-tl[i]) * (i+1),ny = a[i+1] - (nt-tr[i+1]) * (n-i);
		if (nx <= ny) ans = min(ans,nt + (ny-nx) / (n+1));
	}
	cout << fixed << setprecision(20) << ans << '\n';
}
int main(){ int T; read(T); while (T--) solve(); return 0; }
```

---

## 作者：vectorwyx (赞：0)

我们把从左向右开的车称作甲车，另一辆称为已车，则有：

> 1.甲车从第i面旗帜驶向第 $i+1$ 面旗帜的速度为 $i$，乙车从第 $i+1$面旗帜驶向第 $i$ 面旗帜的速度为 $n-i+1$

> 2.甲乙两车在第 $i$ 面旗帜和第 $i+1$ 面旗帜之间相遇的充要条件为：甲车到达第 $i$ 面旗帜时乙车还未到达第 $i$ 面旗帜，甲车到达第 $i+1$ 面旗帜时乙车已经驶过第 $i+1$ 面旗帜

因此，我们预处理出甲乙两车到每一面旗帜和终点的时刻，根据性质2判断出它们的相遇点在哪段区间，之后就转化成了一个简单的相遇问题，直接求解即可qwq。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define db double
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=1e5+5;
int a[maxn];
db t[maxn][2];

void work(){
	int n=read();
	a[n+1]=read();
	fo(i,1,n) a[i]=read();
	t[n+1][1]=0;
	//预处理出甲乙两车到达每一面旗帜的时刻，t[i][0/1]表示甲车/乙车到达第i面旗帜的时刻 
	fo(i,1,n+1) t[i][0]=t[i-1][0]+(a[i]-a[i-1])*1.0/i;
	go(i,n,0) t[i][1]=t[i+1][1]+(a[i+1]-a[i])*1.0/(n-i+1);
	int pos=-1;
	//查找相遇点位于哪段区间 
	fo(i,0,n) if(t[i][0]<=t[i][1]&&t[i+1][0]>=t[i+1][1]){
		pos=i;
		break;
	}
	db ans;
	//相遇问题+分类讨论 
	if(t[pos][0]>=t[pos+1][1]){
		db t1=t[pos][0]-t[pos+1][1];
		db s1=t1*(n-pos+1);
		db s=a[pos+1]-a[pos]-s1;
		db _t=s/(n+2);
		ans=t[pos][0]+_t;
	}else{
		db t0=t[pos+1][1]-t[pos][0];
		db s0=t0*(pos+1);
		db s=a[pos+1]-a[pos]-s0;
		db _t=s/(n+2);
		ans=t[pos+1][1]+_t;		
	}
	printf("%.10lf\n",ans);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：Little09 (赞：0)

一个奇怪的做法。先算出两个人到达每个标志用的时间，然后枚举所有两个相邻标志之间，检查两车是否在此之间相遇。如果找到了，计算出时间就可以了。

注意一下精度。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l;
int a[100005]; 
long double x[100005],y[100005];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n >> l;
		for (int i=1;i<=n;i++) cin >> a[i];
		a[n+1]=l,y[n+1]=0,x[0]=0;
		for (int i=1;i<=n+1;i++)
		{
			x[i]=x[i-1]+((long double)(a[i]-a[i-1]))/((long double)i);
		}
		for (int i=n;i>=0;i--)
		{
			y[i]=y[i+1]+((long double)(a[i+1]-a[i]))/((long double)(n-i+1));
		}
		for (int i=1;i<=n;i++)
		{
			if (x[i]==y[i]) 
			{
				printf("%.10Lf\n",x[i]);
				goto uuu;
			}
		}
		for (int i=0;i<=n;i++)
		{
			if ((x[i+1]<=y[i]&&x[i+1]>=y[i+1])||(y[i]>=x[i]&&y[i]<=x[i+1]))
			{
				if (x[i]<y[i+1])
				{
					long double v1=i+1,v2=n+1-i;
					long double s=a[i+1]-a[i]-v1*(y[i+1]-x[i]);
					long double t=s/(v1+v2)+y[i+1];
					printf("%.10Lf\n",t);
					break;
				}
				else
				{
					long double v1=i+1,v2=n+1-i;
					long double s=a[i+1]-a[i]-v2*(x[i]-y[i+1]);
					long double t=s/(v1+v2)+x[i];
					printf("%.10Lf\n",t);
					break;
				}
			}
		}
		uuu:;
	}
	return 0;
}
```


---

## 作者：LRL65 (赞：0)

这题直接模拟就行了。

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
double n,t,l,a[100005];
int main() {
	cin>>t;
	while(t--) {
		cin>>n>>l;
		for(int i=1;i<=n;i++)cin>>a[i];//输入
		int i1=1,i2=n;//一开始标志为1和n
        double speed1=1,speed2=1,t1=0,t2=l,ans=0;//speed是速度，t1,t1是位置，ans是答案
		while(1) {
            //cout<<t1<<" "<<t2<<" "<<ans<<endl;
			if(i1>i2) {
				printf("%.7lf\n",ans+(t2-t1)/(speed1+speed2));
				break;//如果遇到过所有标志了，就输出剩下的时间+ans
			}
			else if((a[i1]-t1)/speed1==(t2-a[i2])/speed2) {//同时到达标志
                double time=(a[i1]-t1)/speed1;
                ans+=time;
				t2=a[i2],t1=a[i1];
				i1++;i2--;
				speed1++;speed2++;
			}
			else if((a[i1]-t1)/speed1<(t2-a[i2])/speed2) {//左边的车先到达标志
                double time=(a[i1]-t1)/speed1;
                ans+=time;
				t2=t2-time*speed2,t1=a[i1];
				i1++;
				speed1++;
			}
			else {//右边的先
                double time=(t2-a[i2])/speed2;
                ans+=time;
				t1=t1+time*speed1,t2=a[i2];
				i2--;
				speed2++;
			}
		}
	}
}
```


---

## 作者：MVP_Harry (赞：0)

写法和前面的大佬不太一样。我维护了一个$time[i][j]$，$j = 0 , 1$，表示第$j$个人走到第$i$个加速点的时间。然后枚举每两个相邻的加速点，第一个人在加速点$i$，第二个人在加速点$i + 1$，然后就利用小学的行程问题解法即可。

关键代码如下：

```
int pos[maxn];
long double Time[maxn][2];

void solve() {
	int N, L;
	cin >> N >> L;
	memset(pos, 0, sizeof pos);
	memset(Time, 0, sizeof(Time)); 
	for (int i = 1; i <= N; i++)
		cin >> pos[i];
	pos[N + 1] = L; 
	for (int i = 1; i <= N + 1; i++) {
		Time[i][0] = Time[i - 1][0] + (long double) (pos[i] - pos[i - 1]) / (long double) i; 
	}	
	for (int i = N; i >= 0; i--) {
		Time[i][1] = Time[i + 1][1] + (long double) (pos[i + 1] - pos[i]) / (long double) (N - i + 1); 
	}
	long double ans = INF; 
	for (int i = 0; i <= N; i++) {
		//first car start from pos[i], second car start from pos[i + 1];
		long double t1 = Time[i][0], t2 = Time[i + 1][1]; 
		int v1 = i + 1, v2 = N - i + 1;
		long double dist = pos[i + 1] - pos[i]; 
		if (t1 + (long double) dist / (long double) v1 < t2 || t1 > (long double) dist / (long double) v2 + t2) { 
			continue; 
		}
		if (t1 > t2) {
			long double Time_dif = t1 - t2; 
			dist -= (long double) Time_dif * v2; 
			ans = min(ans, t1 + (long double) dist / (v1 + v2)); 
		} else {
			long double Time_dif = t2 - t1; 
			dist -= (long double) Time_dif * v1; 
			ans = min(ans, t2 + (long double) dist / (v1 + v2)); 
		}
	}
	printf("%.6Lf\n", ans);
}
```

---

## 作者：Isshiki_Hugh (赞：0)

双指针模拟

不断靠近即可

我是通过不断调用doo实现的
```cpp
//头文件略
const int N = 1e6+9;
const int inf = 1e9+9;
const double eps = 1e-7;
int _,n,l,pl,pr;
double ans,a[2*N];
struct node{
    double v,p;
}u,v;

inline void doo(){
    double dis_u = a[pl] - u.p;
    double dis_v = v.p - a[pr];
    double t_u = dis_u / u.v;
    double t_v = dis_v / v.v;
    if(t_u < t_v){
        ans += t_u , u.p = a[pl++] , u.v+=1.0 , v.p = v.p - v.v * t_u;
    } else if(t_u > t_v){
        ans += t_v , v.p = a[pr--] , v.v+=1.0 , u.p = u.p + u.v * t_v;
    } else {
        ans += t_u , u.p = a[pl++] , u.v+=1.0 , v.p = a[pr--] , ++v.v;
    }
    return;
}

int main(){
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifdef LOCAL //use "g++ xxx.cpp -DLOCAL"
        freopen("in.in", "r", stdin);
    #endif
    cin >> _;
    while(_--){
        ans = 0;
        cin >> n >> l;
        rep(i,1,n) cin >> a[i];
        u.p = 0 , u.v = v.v = pl = 1 , v.p = l , pr = n;
        while(pl <= pr){
            // cout << "now in " << _ << " and pl = " << pl << " , pr = " << pr << "\n";
            // cout << "u in " << u.p << "  , v in " <<  v.p << "\n";
            // cout << "u sp " << u.v << "  , v sp " <<  v.v << "\n";
            doo();
        }
        ans += (v.p - u.p) / (u.v + v.v);
        // cout << "now in " << _ << " and pl = " << pl << " , pr = " << pr << "\n";
        // cout << "u in " << u.p << "  , v in " <<  v.p << "\n";
        // cout << "u sp " << u.v << "  , v sp " <<  v.v << "\n";
        printf("%.15lf\n",ans);
        // cout << ans << "\n";
    }

    return 0;
}
```

---

## 作者：RedLycoris (赞：0)

一道较为简单的双指针

每次维护左边的人走到那个旗子，右边的人走到那个旗子，慢慢向中间不断更新靠拢即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define mp make_pair
#define ri register int
#define ld long double
using namespace std;
const int mxn=2e5+5;
vector<int>g[mxn];
int n,m;
ld len;
ld a[mxn];
inline void solve(){
	cin>>n>>len;
	for(int i=1;i<=n;++i)cin>>a[i];
	int l=1,r=n;
	ld cl=0,cr=len;
	ld sl=1,sr=1;
	ld ans=0;
	for(;l<=r;){//向中间推
		ld dl=a[l]-cl,dr=cr-a[r];
		ld tl=dl/sl,tr=dr/sr;
		if(tl<tr){
			cl=a[l];
			cr-=tl*sr;
			ans+=tl;
			sl=sl+1;
			++l;
		}else{
			cr=a[r];
			cl+=tr*sl;
			ans+=tr;
			sr=sr+1;
			--r;
		}
	}
	ans+=(cr-cl)/(sl+sr);//中间没有旗子了
	cout<<fixed<<setprecision(9)<<ans<<'\n';
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;cin>>T;
	for(;T--;)solve();
}
```

---

