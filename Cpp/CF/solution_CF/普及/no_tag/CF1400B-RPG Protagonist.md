# RPG Protagonist

## 题目描述

有两个人去买武器，两个人的最大承重分别为 $a,b$，武器店有剑和战斧，有 $c_1$ 把剑，每一把剑的重量为 $w_1$，有 $c_2$ 把战斧，每一把战斧的重量为 $w_2$。两个人购买的武器总重量不能超过自生的最大承重，两个人购买的剑的总数不能超过 $c_1$，购买战斧的总数不能超过 $c_2$，求在满足条件下两人能买到的武器总数的最大值。

本题多测，$1\leqslant a,b,w_1,w_2\leqslant10^9,1\leqslant c_1,c_2\leqslant 2\times 10^5,1\leqslant \sum c_1,\sum c_2\leqslant 2\times 10^5$。

## 样例 #1

### 输入

```
3
33 27
6 10
5 6
100 200
10 10
5 5
1 19
1 3
19 5```

### 输出

```
11
20
3```

# 题解

## 作者：AlanSP (赞：6)

## B.RPG Protagonist

#### [题目链接](https://codeforces.com/contest/1400/problem/B)

阴间题。~~没有二分，递推等高级算法，纯枚举+模拟。~~

我们可以枚举第一个人选$s$的个数。

那么他剩余的空间肯定用来选$w$。

设第一个人选完后剩下的$s$和$w$的个数分别为 $cs,cw$。

那么问题转化成了第二个人在 $cs,cw$ 中选的最大个数。

简单贪心，先考虑最小体积的，再放最大的。

模拟即可。

为了方便，我们可以在枚举前确定 $w$ 和 $s$ 的大小关系，然后枚举较小者。
### Code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int N=2e5+9;
char ch[52];
int n,T,a[N],f[N],g[N],m,s,w,vs,vw;
vector<int> num;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int ans=0;
		scanf("%d%d",&n,&m);
		scanf("%d%d",&s,&w);
		scanf("%d%d",&vs,&vw);
		if(vs>vw)swap(vs,vw),swap(s,w);
		for(int i=0;i<=s&&i*vs<=n;i++)
		{
			int now=vs*i,res=i;
			int bn=n,bm=m,bw=w;
			n-=now;
			res+=min(n/vw,w); 
			w-=min(n/vw,w);
			res+=min(m/vs,s-i);
			m-=min(m/vs,s-i)*vs;
			res+=min(m/vw,w);
			ans=max(ans,res);
			n=bn,m=bm,w=bw;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：ZigZagKmp (赞：4)

本文同步发表于[我的cnblog](https://www.cnblogs.com/ZigZagKmp/p/13563143.html)

本场题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1400-edu-94-solution)

## 题意简述
有2个人去买武器，两个人的最大承重分别为$p,f$，武器店有剑和战斧，有$cnts$把剑，每一把剑的重量为$s$，有$cntw$把战斧，每一把战斧的重量为$w$。两个人购买的武器总重量不能超过自生的最大承重，两个人购买的剑的总数不能超过$cnts$，购买战斧的总数不能超过$cntw$，求在满足条件下两人能买到的武器总数的 最大值。

多测，$1\le p,f,s,w\le 10^9$，$1\le cnts,cntw\le 2\times 10^5$，$1\le \sum cnts,\sum cntw\le 2\times 10^5$。
### 算法考察
贪心
## 算法分析
本问题与传统的多重背包问题很类似，但是本问题有$3$个特殊性。

1. 背包容量很大
2. 有$2$个背包
3. 只有$2$个物品，且价值为1

因为只有$2$个物品，我们可以直接贪心，尽可能选用重量小的物品，证明显然（可以考虑拿出一个重量大的物品一定可以再装下至少一个重量小的物品，一定不会使答案变差）。

以下假设$s<w$（如果输入数据$s>w$直接交换调整）。

因为这一题有$2$个背包，所以我们可以枚举第一个背包选了$i$把剑，我们不难计算出第二个背包选了多少剑，剩余空间我们用战斧填充。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long//其实本题不必要开long long
#define mod 1000000007
#define local
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int p,f,cnts,cntw,s,w;
int ans;
int calc(int x){
	if(x*s>p)return 0;//买x个s已经负担不起了
	int ret=x;p-=x*s;
	int yy=min(cnts-x,f/s);//第二个人购买的s
	ret+=yy;f-=yy*s;
	ret+=min(cntw,p/w+f/w);//两个人购买的w
	p+=x*s;f+=yy*s;//注意修改撤销
	return ret;
}
signed main(){
	int CasT;
	read(CasT);
	while(CasT--){
		read(p);read(f);read(cnts);read(cntw);read(s);read(w);
		if(s>w)swap(s,w),swap(cnts,cntw);//默认s<w
		ans=0;
		for(int i=0;i<=cnts;i++){
			ans=max(ans,calc(i));
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：引领天下 (赞：1)

注意到 $cnts$ 和 $cntw$ 的数量都只有 $2\times 10^5$，所以可以直接暴力枚举。详细看代码。

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int main(){
    register long long t,p,f,s,w,cnts,cntw;
    cin>>t;
    while(t--){
        long long ans=0;
        cin>>p>>f>>cnts>>cntw>>s>>w;
        if(s>w)s^=w^=s^=w,cnts^=cntw^=cnts^=cntw;//注意到斧和剑对答案来说是一样的，所以可以将代价和总量一起换。
        for(int i=0;i<=cnts;i++){//枚举自己带的剑的数量
            if(i*s>p)break;
            int cnt=0,ts=cnts,tw=cntw;//记下总共有多少斧、剑。
            cnt+=i,ts-=i;//带上这些剑
            int tw1=min((p-i*s)/w,tw);//算一下自己还能带多少斧
            cnt+=tw1,tw-=tw1;//带上这些斧
            int ts2=min(f/s,ts);//算一下追随者可以带多少剑
            cnt+=ts2,ts-=ts2;//追随者带上剑
            int tw2=min((f-ts2*s)/w,tw);//算一下追随者可以带多少斧
            cnt+=tw2,tw-=tw2;//追随者带上这些斧
            ans=max(ans,cnt);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Little09 (赞：0)

听说这道题在赛时难倒了好多神仙。其实这只是一个暴力枚举。

首先肯定不能直接贪心做，如果对于某个人去最优的方案，第二个人就不一定最优了。

注意到 $cnt$ 值很小。所以可以考虑枚举第一个人拿了多少把剑，剩余的肯定尽可能拿战斧。第二个人就可以贪心拿重量小的武器知道拿光，然后拿另外一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
int T,a,b,c,d,e,f,ans; 
inline int read()
{
	char C;
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int main()
{
	T=read();
	while (T--)
	{
		a=read(),b=read(),c=read(),d=read(),e=read(),f=read();
		if (e>f) swap(e,f),swap(c,d);
		ans=0;
		for (int i=0;i<=c;i++)
		{
			int aa=a-i*e;
			if (aa<0) break;
			int j=aa/f;
			int ii=b/e;
			if (ii>c-i) ii=c-i;
			int res=b-ii*e;
			int jj=res/f;
			if (jj>d-j) jj=d-j;
			ans=max(ans,i+j+ii+jj);
		}
		cout << ans << endl;
	}
	return 0;
}
```


---

