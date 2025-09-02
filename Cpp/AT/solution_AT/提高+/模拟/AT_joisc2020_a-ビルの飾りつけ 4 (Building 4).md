# ビルの飾りつけ 4 (Building 4)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2020/tasks/joisc2020_a



# 题解

## 作者：lfxxx (赞：0)

首先考虑下 $O(n^2)$ 咋做，不妨 $dp_{i,j,0/1}$ 表示考虑前 $i$ 个，停在 $a_i,b_i$ 上，选了 $j$ 个 $a_i$ 是否可能。

发现 $dp$ 值只有 $0/1$ 这未免太浪费，不妨设计 $g_{i,0/1}$ 表示 $dp_{i,j,0/1} = 1$ 的 $j$ 构成的集合，打表发现集合一定形如一个区间，这是因为当 $a_{i-1},b_{i-1}$ 都能转移到 $i$ 时，之前转移到 $a_{i-1},b_{i-1}$ 中较小值的点也能转移到较大值，并且贡献差只有 $1$，等于说是把一个区间平移一个后再与自己拼接，故还是一个区间，直接维护区间即可做到 $O(n)$，输出方案倒着推回去即可。


```cpp
// LUOGU_RID: 196731778
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+114;
const int inf = 1e9;
int la[maxn],ra[maxn],lb[maxn],rb[maxn];
int a[maxn],b[maxn];
char ans[maxn];
int n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=2*n;i++) cin>>a[i];
    for(int i=1;i<=2*n;i++) cin>>b[i];
    la[1]=ra[1]=1;
    lb[1]=rb[1]=0;
    for(int i=2;i<=2*n;i++){
        la[i]=inf,ra[i]=-inf,lb[i]=inf,rb[i]=-inf;
        if(a[i-1]<=a[i]) la[i]=min(la[i],la[i-1]+1),ra[i]=max(ra[i],ra[i-1]+1);
        if(b[i-1]<=a[i]) la[i]=min(la[i],lb[i-1]+1),ra[i]=max(ra[i],rb[i-1]+1);
        if(a[i-1]<=b[i]) lb[i]=min(lb[i],la[i-1]),rb[i]=max(rb[i],ra[i-1]);
        if(b[i-1]<=b[i]) lb[i]=min(lb[i],lb[i-1]),rb[i]=max(rb[i],rb[i-1]);
    }
    if(la[2*n]<=n&&ra[2*n]>=n){
        char now='a';
        int v=n;
        for(int i=2*n;i>=2;i--){
            ans[i]=now+('A'-'a');
            if(now=='a'){
                v--;
                if(a[i-1]<=a[i]&&la[i-1]<=v&&ra[i-1]>=v){
                    now='a';
                }else{
                    now='b';
                }
            }else{
                if(a[i-1]<=b[i]&&la[i-1]<=v&&ra[i-1]>=v){
                    now='a';
                }else{
                    now='b';
                }
            }
        }
        ans[1]=now+('A'-'a');
        for(int i=1;i<=2*n;i++) cout<<ans[i];
    }else if(lb[2*n]<=n&&rb[2*n]>=n){
        char now='b';
        int v=n;
        for(int i=2*n;i>=2;i--){
            ans[i]=now+('A'-'a');
            if(now=='a'){
                v--;
                if(a[i-1]<=a[i]&&la[i-1]<=v&&ra[i-1]>=v){
                    now='a';
                }else{
                    now='b';
                }
            }else{
                if(a[i-1]<=b[i]&&la[i-1]<=v&&ra[i-1]>=v){
                    now='a';
                }else{
                    now='b';
                }
            }
        }
        ans[1]=now+('A'-'a');
        for(int i=1;i<=2*n;i++) cout<<ans[i];
    }else{
        cout<<-1;
    }
    return 0;
}
```

---

## 作者：DerrickLo (赞：0)

容易想到一个 $O(n^2)$ 的暴力 DP。

用 $dp_{i,j,0/1}$ 表示前 $i$ 个数中选了 $j$ 个 $a$ 中的数，第 $i$ 个数选择 $a$ 还是 $b$ 中的数，转移很好转。

然后我们发现满足 $dp_{i,j,0/1}=1$ 的 $j$ 是一段区间，那么我们可以用 $dp_{i,0/1}$ 表示第 $i$ 个数选择 $a$ 中的数还是 $b$ 中的数，选择 $a$ 中的数的个数所在的区间，然后转移就把区间合并一下就可以了。

求操作序列可以把 DP 过程倒序做一下就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000005],b[1000005];
vector<int>ans;
struct segment{
	int l,r;
	friend segment operator+(const segment&a,const segment&b){
		return {min(a.l,b.l),max(a.r,b.r)};
	}
	friend void operator+=(segment&a,const segment&b){
		a=a+b;
	}
}f[1000005][2];
signed main(){
	cin>>n;
	for(int i=1;i<=2*n;i++)cin>>a[i];
	for(int i=1;i<=2*n;i++)cin>>b[i];
	for(int i=1;i<=2*n;i++)f[i][0]=f[i][1]={1000000000000000000ll,-1000000000000000000ll};
	f[1][0]={1,1},f[1][1]={0,0};
	for(int i=2;i<=2*n;i++){
		if(a[i-1]<=a[i])f[i][0]+=f[i-1][0];
		if(b[i-1]<=a[i])f[i][0]+=f[i-1][1];
		if(a[i-1]<=b[i])f[i][1]+=f[i-1][0];
		if(b[i-1]<=b[i])f[i][1]+=f[i-1][1];
		f[i][0].l++,f[i][0].r++;
	}
	if(f[2*n][0].l<=n&&f[2*n][0].r>=n){
		int flag=0,hv=n;
		for(int i=2*n;i;i--){
			ans.emplace_back(flag);
			if(flag==0){
				if(a[i-1]<=a[i]&&f[i-1][0].l<=hv-1&&f[i-1][0].r>=hv-1){
					hv--;
					continue;
				}
				if(b[i-1]<=a[i]&&f[i-1][1].l<=hv-1&&f[i-1][1].r>=hv-1){
					hv--,flag=1;
					continue;
				}
			}
			else{
				if(a[i-1]<=b[i]&&f[i-1][0].l<=hv&&f[i-1][0].r>=hv){
					flag=0;
					continue;
				}
			}
		}
		reverse(ans.begin(),ans.end());
		for(int v:ans)cout<<((v==0)?"A":"B");
		return 0;
	}
	if(f[2*n][1].l<=n&&f[2*n][1].r>=n){
		int flag=1,hv=n;
		for(int i=2*n;i;i--){
			ans.emplace_back(flag);
			if(flag==0){
				if(a[i-1]<=a[i]&&f[i-1][0].l<=hv-1&&f[i-1][0].r>=hv-1){
					hv--;
					continue;
				}
				if(b[i-1]<=a[i]&&f[i-1][1].l<=hv-1&&f[i-1][1].r>=hv-1){
					hv--,flag=1;
					continue;
				}
			}
			else{
				if(a[i-1]<=b[i]&&f[i-1][0].l<=hv&&f[i-1][0].r>=hv){
					flag=0;
					continue;
				}
			}
		}
		reverse(ans.begin(),ans.end());
		for(int v:ans)cout<<((v==0)?"A":"B");
		return 0;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2020A 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2020_a)

**题目大意**

> 给 $2n$ 个数对 $(a_i,b_i)$，构造一个非降序列 $c_i$ 满足 $\forall 1\le i\le n,c_i\in\{a_i,b_i\}$，且 $c_i=a_i$ 的位置恰好有 $n$ 个。
>
> 数据范围：$n\le 5\times 10^5$。

**思路分析**

考虑 dp，最朴素的设计就是令 $dp_{i,j,0/1}$ 表示 $c_1\sim c_i$  中选了 $j$ 个 $a_i$，且上一个是 $a_i/b_i$ 是否可行。

打表可以发现：每个 $dp_{i,*,0/1}$ 中合法的 $j$ 都是连续的一段，这样就只要记录左右端点 $\mathcal O(1)$ 转移了。

输出方案直接倒序还原即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5,inf=1e9;
struct Info {
	int l,r;
	Info(int x=inf,int y=-inf): l(x),r(y) {}
	inline friend Info operator +(const Info &u,const Info &v) { return Info(min(u.l,v.l),max(u.r,v.r)); }
	inline bool in(int x) { return l<=x&&x<=r; } 
} dp[MAXN][2];
int n,a[MAXN],b[MAXN];
char o[MAXN];
signed main() {
	scanf("%d",&n),n<<=1;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	dp[1][0]={0,0},dp[1][1]={1,1};
	for(int i=2;i<=n;++i) {
		if(a[i-1]<=a[i]) dp[i][0]=dp[i][0]+dp[i-1][0];
		if(a[i-1]<=b[i]) dp[i][1]=dp[i][1]+dp[i-1][0];
		if(b[i-1]<=b[i]) dp[i][1]=dp[i][1]+dp[i-1][1];
		if(b[i-1]<=a[i]) dp[i][0]=dp[i][0]+dp[i-1][1];
		++dp[i][1].l,++dp[i][1].r;
	}
	if(dp[n][0].in(n/2)||dp[n][1].in(n/2)) {
		for(int i=n,k=0,s;i;--i) {
			if((i==n||a[i]<=(s?b[i+1]:a[i+1]))&&dp[i][0].in(n/2-k)) s=0;
			else s=1,++k;
			o[i]="AB"[s];
		}
		for(int i=1;i<=n;++i) printf("%c",o[i]);
		puts("");
	} else puts("-1");
	return 0;
}
```



---

## 作者：SentoAyaka (赞：0)

考虑朴素 dp，设 $f_{i,j,0/1}$ 表示到 $i$，选了 $j$ 个 $A$，当前是 $A/B$ 时是否合法。复杂度 $O(n^2)$。

考虑这个转移的性质，大胆猜测对于 $(i,0/1)$，合法的 $j$ 是一段连续区间。通过打表不难验证。

直接设 $f_{i,0/1}$ 表示合法 $j$ 的区间，转移就是区间合并。复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int ll
#define ll long long
#define db double
#define MP make_pair
#define vec vector<int>
#define pii pair<int,int>
#define pb emplace_back
#define l first
#define r second
#define ls k<<1
#define rs k<<1|1
#define CLK (double)clock()/CLOCKS_PER_SEC
using namespace std;
mt19937 rnd(time(0));
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
void write(int x){
    if(x<0){putchar('-');write(-x);}
    else {
        if(x>9)write(x/10);
        putchar(x%10+'0');
    }
}
const int N=1e6+5,inf=1e18;
int n,m,a[N],b[N],ans[N];pii f[N][2];
void upd(pii &x,pii y){
    x.l=min(x.l,y.l),x.r=max(x.r,y.r);
}
void MAIN(){
    n=read(),m=n*2;a[m+1]=b[m+1]=inf;
    for(int i=1;i<=m;i++)a[i]=read();
    for(int i=1;i<=m;i++)b[i]=read();
    for(int i=1;i<=m;i++){
        f[i][0]=f[i][1]=MP(inf,-inf);
        if(a[i-1]<=a[i])upd(f[i][0],f[i-1][0]);
        if(b[i-1]<=a[i])upd(f[i][0],f[i-1][1]);
        if(a[i-1]<=b[i])upd(f[i][1],f[i-1][0]);
        if(b[i-1]<=b[i])upd(f[i][1],f[i-1][1]);
        f[i][0].l++,f[i][0].r++;
    }
    if(n<min(f[m][0].l,f[m][1].l)||n>max(f[m][0].r,f[m][1].r))
        return puts("-1"),void();
    for(int i=m,flg=0;i>=1;i--){
        flg=(b[i]<=(flg?b[i+1]:a[i+1]))&&(n>=f[i][1].l&&n<=f[i][1].r);
        ans[i]=flg,n-=!flg;
    }
    for(int i=1;i<=m;i++)putchar('A'+ans[i]);
}
signed main(){
    // freopen("read.in","r",stdin);
    // freopen("write.out","w",stdout);
    int T=1;while(T--)MAIN();
    // printf("\nTIME:%lf\n",CLK);
    return 0;
}
```


---

