# Lizards and Basements 2

## 题目描述

有一队人，第 $i$ 个人的血量为 $h_{i}$，你可以用火球点某个人，会对当前的人造成 $a$ 点伤害，对旁边的人造成 $b$ 点伤害。

火球不能打 $1$ 号和 $n$ 号，求最少多少发火球烧死所有人。血量为负数才算死。

## 样例 #1

### 输入

```
3 2 1
2 2 2
```

### 输出

```
3
2 2 2 ```

## 样例 #2

### 输入

```
4 3 1
1 4 1 1
```

### 输出

```
4
2 2 3 3 ```

# 题解

## 作者：kczno1 (赞：8)

$dp[i][j][k]$表示$1..i$该放的火球都放了
($1..i-1$都死了),
且第$i-1$个人放了$j$个,第$i$个人放了$k$个,
$i..n$的最小花费

转移就是枚举第$i+1$个人放$l$个,  
则$dp[i][j][k]=k+min(dp[i+1][k][l])$  
其中$b*j+a*k+b*l>=h[i]$

暴力转移是$O(n*u^3)$的($u$为血量最大值)  
记个后缀$min$就是$O(n*u^2)$的

```cpp
//by kcz 1552920354@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T&x,const T &y)
{
    if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
    if(x<y)x=y;
}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned short us;
typedef unsigned int ui;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define pb push_back
#define mp make_pair
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'-');
    if(c=='-')
    {
        int x=gc-'0';
        while(gc>='0')x=x*10+c-'0';
        return -x;
    }
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
#undef gc

const int N=10+2,U=15+2;
int dp[N][U][U],mn[N][U][U],need[U];
int n,a,b,h[N];

int main()
{
    //freopen("1.in","r",stdin);//freopen("1.out","w",stdout);
    cin>>n>>a>>b;
    rep(i,1,n)h[i]=read();
    memset(dp,(1<<6)-1,sizeof(dp));
    rep(i,0,U-1)
    if(i*b>h[n])dp[n][i][0]=0;
    rep(i,0,U-1)need[i]=i/b+1;
    per(i,n,1)
    {
        if(i<n)
        {
            rep(j,0,U-1)
            {
                int v=h[i]-j*b;
                rep(k,0,U-1)
                {
                    dp[i][j][k]=k+mn[i+1][k][v<0?0:need[v]];
                    v-=a;
                }
            }
        }
        rep(j,0,U-1)
        {
            mn[i][j][U-1]=dp[i][j][U-1];
            per(k,U-2,0)mn[i][j][k]=min(mn[i][j][k+1],dp[i][j][k]);
        }
    }
    int i=1,j=0,k=0;
    printf("%d\n",dp[i][j][k]);
    while(++i<n)
    {
        int v=h[i-1]-j*b-k*a;
        int l=v<0?0:need[v];
        while(dp[i][k][l]!=dp[i-1][j][k]-k)++l;
        j=k;k=l;
        rep(o,1,l)printf("%d ",i);
    }
}


```



---

## 作者：小闸蟹 (赞：7)

```cpp
// 看这题的数据量似乎不算太大
// 所以不用DP也可以
// 直接上DFS也不会超时
// 这个做法比较暴力但是容易想到
// 具体看代码
#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

int n, a, b;
std::array<int, 100> h{ 0 };
std::vector<int> Vec, Temp;

int Ans = INT_MAX;

int Read()
{
    int n = 0, k = 1;
    char ch = getchar();
    while ((ch > '9' || ch < '0') && ch != '-')
        ch = getchar();

    if (ch == '-')
    {
        k = -1;
        ch = getchar();
    }

    while (ch <= '9' && ch >= '0')
    {
        n = n * 10 + ch - '0';
        ch = getchar();
    }

    return n * k;
}

// DFS(Now, Sum)表示：
// 能打败前Now - 1个弓箭手需要最少打Sum发
void DFS(int Now, int Sum)
{
    if (Sum >= Ans) // 剪枝
    {
        return;
    }

    if (Now == n - 1)   // 搜完了，因为最后一个人不能直接打，只能被间接打
    {
        if (h[n - 1] < 0)   // 如果最后一个也被打死了，那就可以更新答案
        {
            Ans = Sum;
            Vec = Temp;
        }

        return;
    }

    // 否则就取肯定能打败其中一个的方案进行DFS
    for (int i = 0;
        i <= std::max({ (h[Now - 1] / b), (h[Now] / a), (h[Now + 1] / b) }) + 1;
        ++i)
    {
        if (h[Now - 1] - b * i < 0) // 如果能打败最左边的那一个，满足我们DFS的要求
        {
            h[Now - 1] -= b * i;    // 那就试一下释放攻击
            h[Now] -= a * i;        // 注意，三个人都会受伤
            h[Now + 1] -= b * i;
            for (int t = 0; t < i; ++t)
            {
                Temp.push_back(Now + 1);
            }

            DFS(Now + 1, Sum + i);  // 往下搜下一个

            h[Now - 1] += b * i;    // 回溯
            h[Now] += a * i;
            h[Now + 1] += b * i;
            for (int t = 0; t < i; ++t)
            {
                Temp.pop_back();
            }
        }
    }

    return;
}

int main()
{
    n = Read();
    a = Read();
    b = Read();
    for (int i = 0; i < n; ++i)
    {
        h[i] = Read();
    }

    // 我们从0开始编号，注意第一个和最后一个人不能直接打
    DFS(1, 0);

    std::cout << Ans << std::endl;
    for (const auto &r : Vec)
    {
        std::cout << r << ' ';
    }
    std::putchar('\n');

    return 0;
}
```

---

## 作者：Fading (赞：6)

第一反应就是**dp**

然后换了好多思路终于$AC$了

最后打开题解发现我和孔爷的思路非常接近！！！

我先设$f[i][j]$表示$[1,i-1]$的都死了，第$i$个点了$j$发的最小点数

然后发现没法转移，因为有一种情况：

第$i$个弓箭手没有死，但是点第$i+1$个人的时候顺便点死了第$i$个

这就很恶心了。。。

所以我就换了思路

设$f[i][j][k]$表示$[1,i-1]$的都死了，第$i$个点了$j$发，还剩$k$点血的最小点数

结果很难处理，你们可以试一下，比较恶心，虽然可以做出来。

后来我干脆就换状态了。。。

设$f[i][j][k]$表示$[1,i-1]$的都死了，第$i-1$个点了$j$发，第$i$个点了$k$发的最小点数

这样子我们转移的时候枚举第$i+1$个点了$l$发，

设此时通过点第$i+1$个人来点死第$i$个人还需要$rem$发，可知

$$rem=(\text{剩余血量}\geq0?\text{剩余血量}/b+1:0$$

$$∴f[i+1][k][l]=min(l+f[i][j][k]),l\geq rem$$

然后就做完了？

第$n$个数很不好转移。所以我们转移到$f[n-1]$

最后枚举所有的$f[n-1][j][k],$算出点死第$n$个人还需要的火球数$rem$，答案就是

$$min(f[n-1][j][k]+rem)$$

输出方案就随便记录转移位置，暴力跳就好啦！

有一个小结论：点火球的方案经过打乱后依然可行。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll f[22][201][201],g[22][201][201][2],n,a,b;
//g记录转移位置
ll x[22],mx[22];
inline ll read(){
    ll x=0;char ch=getchar();int f=1;
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
//f[i][j][k] 1~i-1 die,i-1 j fa,i k fa;
int main(){
    n=read(),a=read(),b=read();
    for (int i=1;i<=n;i++) x[i]=read(),mx[i]=(x[i]/a)+1;
    ll mini=x[1]/b+1;//点死第1个人的火球数
    memset(f,0x3f,sizeof(f));
    for (int j=mini;j<=20;j++){
        f[2][0][j]=j;//初始化
    }
    for (int i=2;i<=n-1;i++){
        for (int j=0;j<=(i==2?0:16);j++){
            for (int k=0;k<=16;k++){//点死一个人最多用16个
                if (f[i][j][k]>=0x3f3f3f3f-200) continue;//剪枝
                ll rem=(x[i]-j*b-k*a)>=0?(x[i]-j*b-k*a)/b+1:0;//求rem
                for (int l=max(0LL,rem);l<=16;l++){
                    //f[i][j][k]->f[i+1][k][l]
                    if (l+f[i][j][k]<f[i+1][k][l]){
                        f[i+1][k][l]=l+f[i][j][k];
                        g[i+1][k][l][0]=j,g[i+1][k][l][1]=k;//记录转移位置
                    }
                }
            }
        }
    }
    ll id0=0,id1=0,idrem=0,ans=0x3f3f3f3f;
    for (int j=0;j<=16;j++){
        for (int k=0;k<=16;k++){
            if (f[n-1][j][k]>=0x3f3f3f3f-200) continue;
            ll rem=(x[n-1]-j*b-k*a)>=0?(x[n-1]-j*b-k*a)/a+1:0;//求rem
            if (k*b<=x[n]) rem=((x[n]-b*k)/b+1);
            if (f[n-1][j][k]+rem<ans){
                id0=j,id1=k,ans=f[n-1][j][k]+rem;idrem=rem;
            }
        }
    }
    cout<<ans<<endl;
    //输出方案
    while (idrem--) cout<<n-1<<" ";//输出点死最后一个人的火球
    ll T=n-1;
    while (T!=1){
    	ll idd0=id0,idd1=id1;
    	//cout<<idd0<<" "<<idd1<<endl;
    	id0=g[T][idd0][idd1][0];
    	id1=g[T][idd0][idd1][1];
    	while (idd1--) cout<<T<<" ";
        T--;
    }
    return 0;
}
```

$hack$数据好多啊，调了很久。。。

---

## 作者：Nwayy (赞：4)

很好的搜索题，但是屡次 UKE 搞得我只能上 CF 网站交......

# solution 一维 dfs

- 这样我们这一维只计次数，每一层枚举对几号造成伤害，然后每到一层就扫一遍数组，看看是否全部死亡，是就更新。

- 但是这样容易死循环，所以我们在递归下一层需要特判当前枚举的人以及上一个和下一个人都不能小于 $0$。

```cpp
void dfs(int p){
	if(p>=ans) return;
	int flag=0;
	for(int i=1;i<=n;i++){
		if(s[i]>=0){
			flag=1;
			break;
		}
	}//每次扫一遍数组
	if(flag==0){
		if(p<ans){
			ans=p;
			for(int i=1;i<=ans;i++) st[i]=c[i];
		}
		return;
	}
	for(int i=2;i<n;i++){
		if(s[i]<0 && s[i-1]<0 && s[i+1]<0) continue;//保证不要死循环
		s[i]-=a;
		s[i-1]-=b,s[i+1]-=b;
		c[p+1]=i;
		dfs(p+1);
		s[i]+=a;
		s[i-1]+=b,s[i+1]+=b;//回溯
	}
}
```
- 但是这样子复杂度就会超级高，所以我们考虑二维 dfs 优化。

# solution二维 dfs

- 两个维度分别是当前是第几个人以及以及使用的次数。

- 每一层我都枚举我对当前号码使用几次伤害，然后加上这个次数，那么最多使用几次呢？设 $s_{i}$ 表示第 $i$ 个人当前血量，当前递归到第 $k$ 层，对当前人造成伤害为 $a$，对两边造成的伤害为 $b$，则最多使用次数为：

$$\max(s_{k}\div a + 1,\max(s_{k-1} \div b + 1,s_{k+1} \div b + 1))$$

- 加 $1$ 是因为要保证每个人血量都应小于 $0$。

- 这样子开始是第 $2$ 层，递归边界是 $n-1$ 层，因为第一个和最后一个都不能打。

```cpp
void dfs(int k,int p){
	if(p>=ans) return;
	if(k>=n){
		int flag=0;
		for(int i=1;i<=n;i++){
			if(s[i]>=0){
				flag=1;
				break;
			}
		}//边界判断是否都死亡
		if(flag==0){
			ans=p;
			for(int i=1;i<=p;i++) st[i]=c[i];
		}
		return;
	}
	for(int i=0;i<=max(s[k]/a+1,max(s[k-1]/b+1,s[k+1]/b+1));i++){//可以一次都不打
		s[k]-=i*a;
		s[k-1]-=i*b,s[k+1]-=i*b;
		for(j=p+1;j<=p+i+1;j++) c[j]=k;//加上次数
		dfs(k+1,p+i);
		s[k]+=i*a;
		s[k-1]+=i*b,s[k+1]+=i*b;//回溯
	}
}
```
- 但是这样发现还是会超时，继续考虑优化。

# solution 优化
- 超时的原因显而易见：每次到边界我都要遍历一次来判断。

- 注意到每个人是最多被三种不同情况伤害的，即第 $i$ 个人最多会连带受到第 $i-1$，$i$，$i+1$ 三个人的伤害，之后就跟他没有关系了，所以我们到第 $i+1$ 人的时候判断第 $i$ 人是否死亡了，这样就能保证每个人最终都符合要求。

- 值得提醒的是，最后到边界的时候要判断第 $n-1$ 和 第 $n$ 个人是否符合要求。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,ans=1e9;
int a,b,s[15],st[1000005],c[1000005];
void dfs(int k,int p){
	if(p>=ans) return;
	if(k>=n){
		if(s[k]>=0 || s[n]>=0) return;//边界判断后两个人
		ans=p;
		for(int i=1;i<=p;i++) st[i]=c[i];
		return;
	}
	for(int i=0;i<=max(s[k]/a+1,max(s[k-1]/b+1,s[k+1]/b+1));i++){
		if(s[k-1]-i*b>=0) continue; //判断前一个是否符合要求
		s[k]-=i*a;
		s[k-1]-=i*b,s[k+1]-=i*b;
		for(int j=p+1;j<=p+i+1;j++) c[j]=k;
		dfs(k+1,p+i);
		s[k]+=i*a;
		s[k-1]+=i*b,s[k+1]+=i*b;
	}
}
int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(i=1;i<=n;i++) scanf("%d",&s[i]);
	dfs(2,0);
	printf("%d\n",ans);
	for(i=1;i<=ans;i++) printf("%d ",st[i]);
	return 0;
}
```
话说洛谷能不能优化一下这个提交问题......我至今提交还是 UKE，只能上 CF。

---

## 作者：CheerJustice (赞：3)

## [点我传送](https://www.luogu.com.cn/problem/CF6D)

# solution:

虽然有的大佬使用 dp 切掉了这题，但是算法标签都写了，我们直接~~电风扇~~ dfs 开转！不就是模拟，剪枝嘛，爆搜人无所畏惧。

我们枚举第 $ 2 $ 到第 $ n-1 $ 个小怪每个要打多少次。不难发现，在枚举第 $ i $ 个小怪时，必须保证能打死第 $ i-1 $ 个小怪（因为后面都无法对它造成伤害了），而第 $ i $ 个小怪也没必要直接打死，可以留给打第 $ i+1 $ 个小怪时的溅射伤害。但是一次最多打死周围三个小怪，次数再多显然不优。这样枚举次数的区间就出来了，时间复杂度大大降低，轻松 AC。

## Code：

```c++看看
#include <bits/stdc++.h>
using namespace std;
inline int in(){
	char c=getchar();int f=1;int x;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}
template <typename T>
inline void in(T &x){
	char c=getchar();int f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
// 以上快读，请允许我略~
const int N=205;
int n,a,b,cnt,ans=Max;
int hp[25],tmp[N],Ans[N];
// hp：每个小怪的剩余生命 tmp：存待定方案 Ans：存最终方案
void dfs(int now,int t){
    //now:当前考虑的小怪编号 t：施法次数总和
    if(t>=ans) return;//基础剪枝，应该不用说了
    if(now==n){// 方案满足题意的条件
        if(hp[n]<0){
            ans=t;
            for(int i=1;i<=cnt;i++) Ans[i]=tmp[i];//记录最终方案
        }
		return;
    }
    int mx=max(hp[now]/a,max(hp[now-1],hp[now+1])/b)+1;
    //mx为可行施法次数的上限
    for(int i=0;i<=mx;i++)//枚举当前小怪要打多少下
        if(hp[now-1]<b*i){
        //如果打不死第now-1个小怪，后面就永远也打不死了
            hp[now]-=a*i,hp[now+1]-=b*i;
            for(int j=1;j<=i;j++) 
                tmp[++cnt]=now;
            dfs(now+1,t+i);
            hp[now]+=a*i,hp[now+1]+=b*i,cnt-=i;    
        }
}
int main(){
    in(n),in(a),in(b);
	for(int i=1;i<=n;in(hp[i++]));
	dfs(2,0);
    printf("%d\n",ans);
	for(int i=1;i<=ans;i++) 
		printf("%d ",Ans[i]);
    return 0;//结束力~
}

```

---

## 作者：XL4453 (赞：3)

### 解题思路：

考虑动态规划。

发现每一个人受到的伤害只和自己和两边的直接火球有关，考虑用顺推 DP 求解。

设 $f_{i,j,k}$ 表示到考虑第 $i$ 个人，前 $i-1$ 个人已经全被打死，其中第 $i-1$ 个人受到了 $j$ 个火球，第 $i$ 个人受到了 $k$ 个火球的最小使用火球数量。

然后枚举第 $i+1$ 个人受到的火球，不妨设其为 $l$，其中需要满足第 $i$ 个人死亡，也就是 $(j+l)\times b+k\times a>h_i$。

然后在这些可行解中找一个最小的就行了。

发现最后一个人的情况不好处理，考虑单独拎出来处理，直接枚举再给倒数第二个人补多少刀就行了。

还有就是注意路径的记录。

---
### 调试建议：

看清楚哪里是小于，哪里是小于等于，本题中，死亡是严格小于零。


---
### 代码： 

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[15][20][20],n,hp[15],a,b,ans=2147483647,fr[20][20][20];
int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++)
	scanf("%d",&hp[i]);
	memset(f,63,sizeof(f));
	for(int i=(hp[1]/b+1);i<=16;i++)
	f[2][0][i]=i;
	for(int i=3;i<=n;i++)
	for(int j=0;j<=16;j++)
	for(int k=0;k<=16;k++)
	for(int l=0;l<=16;l++)
	if((j+l)*b+k*a>hp[i-1]){
		if(f[i][k][l]>f[i-1][j][k]+l){
			f[i][k][l]=f[i-1][j][k]+l;
			fr[i][k][l]=j;
		}
	}
	int rec=2147483647,ans=2147483647,p1,p2;
	for(int i=0;i<=16;i++){
		for(int j=0;j<=16;j++){
			int now=hp[n-1]-i*b-j*a>=0?(hp[n-1]-i*b-j*a)/a+1:0;
			if(j*b<=hp[n])now=(hp[n]-b*j)/b+1;
			if(f[n-1][i][j]+now<ans){
				ans=now+f[n-1][i][j];
				rec=now;
				p1=i;
				p2=j;
			}
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=rec;i++)
	printf("%d ",n-1);
	int now=n-1,rp1,rp2;
	while((now-1)){
		rp1=p1,rp2=p2;
		p1=fr[now][rp1][rp2];
		p2=rp1;
		for(int i=1;i<=rp2;i++)
		printf("%d ",now);
		now--;
	}
	printf("\n");
	return 0;
}
```


---

## 作者：_lxy_ (赞：2)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF2600-zuo-ti-ji-lu.html)

#### 题意

一排人，血量分别为 $h_i$，攻击某个人，会对他造成 $a$ 点伤害，对旁边的人造成$b$ 点伤害。不能打 $1$ 号和 $n$ 号，求最少多少次使所有人血量小于 $0$。

#### 分析

数据范围很小，爆搜即可。发现对于一个人的攻击不会对与其距离超过 $1$ 的人有影响，因此从左向右枚举每一位攻击的次数，时间复杂度大致为 $\mathcal{O}((n-2)^{\frac{h_i}{a}})$，最差情况是 $(10-2)^{15}=8^{15} \approx 3.5\times 10^{13}$，会 TLE，考虑剪枝。如果枚举到一半发现此时用的次数已经大于当前的最优次数，说明一定不可能更优，就直接 return，这样复杂度大大优化。

#### 核心代码

```cpp
int n,a,b,h[17],sum,ans=1e9,path[167],ansp[167],tmp;
void dfs(int x,int step){
    if(step>=ans) return;
    if(x==n){
        if(h[n]<0){
            ans=step;
            for(int i=0;i<=path[0];i++) ansp[i]=path[i];
        }return;
    }
    for(int i=0;i<=qmax((h[x-1]/b),qmax((h[x]/a),(h[x+1]/b)))+1;i++){
        if (h[x-1]<b*i){
            h[x-1]-=b*i;h[x]-=a*i;h[x+1]-=b*i;
            for(int j=1;j<=i;j++) path[++path[0]]=x;
            dfs(x+1,step+i);
            h[x-1]+=b*i;h[x]+=a*i;h[x+1]+=b*i;
            for(int j=1;j<=i;j++) path[0]--;    
        }
    }
}
int main(){
    qread(n,a,b);int i,j;for(i=1;i<=n;i++) qread(h[i]);dfs(2,0);
    printf("%d\n",ans);for(i=1;i<=ansp[0];i++) printf("%d ",ansp[i]);
    return 0;
}
```

[record](https://codeforc.es/problemset/submission/6/171690420)

---

## 作者：Night_sea_64 (赞：1)

本蒟蒻用的是迭代加深搜索。

我们定义一个 $md$ 表示当前最多打多少次。每个人枚举打多少次，然后在枚举的过程中暂时改变人的血量，并记录一个 $c$ 数组表示这个人被打了多少次（只算以他为中心的次数，不算旁边的人的次数）。

我们可以做一些可行性剪枝：

1. 每次枚举这个人要打多少次，最多枚举到：这个人要打的次数、左边要打的次数和右边要打的次数的最大值。如果这个值大于剩余可以打的次数，就为剩余可以打的次数。（因为式子太长了，所以不把式子打出来了）。
1. 如果一个人所有被打的情况都被枚举过了，那就赶紧判断这个人是否打死了。如果没有就停止枚举这种方案了。

此题思路不难，代码也不难。**唯一坑点就是题目中没说血量 $<0$ 才算死掉**。AC 代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int n,x,y,md;//x,y 为题面中的 a,b。
int a[15],b[15],c[15];//a 数组是血量，b 数组用来备份 a 数组。
void dfs(int step,int cnt)//step 表示下标，cnt 表示剩余可以打的次数。
{
    if(step>2&&a[step-2]>=0)return;
    if(step==n)
    {
        if(a[n-1]>=0||a[n]>=0)return;
        cout<<md<<endl;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=c[i];j++)
                cout<<i<<" ";
        cout<<endl;
        exit(0);
    }
    int xx=min(max(int(ceil((a[step]+1)*1.0/x)),max(int(ceil((a[step-1]+1)*1.0/y)),int(ceil((a[step+1]+1)*1.0/y)))),cnt);//这东西要放在外面提前算好，不然每次循环中都还得算一次，会 TLE（亲身经历）
    for(int i=0;i<=xx;i++)
    {
        c[step]=i;
        a[step]-=i*x;
        a[step-1]-=i*y;
        a[step+1]-=i*y;
        dfs(step+1,cnt-i);
        c[step]=0;
        a[step]+=i*x;
        a[step-1]+=i*y;
        a[step+1]+=i*y;
    }
}
int main()
{
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(md=1;;md++)
    {
        memcpy(b,a,sizeof(b));
        dfs(2,md);
        memcpy(a,b,sizeof(a));
    }
    return 0;
}
```

---

## 作者：suolk (赞：0)

这题也可以用 dp 做，但是 dfs 效率也不差，交了一发加了个快读之后在 cf 界面显示仅需 124 ms，稳稳的o(*￣▽￣*)ブ。  

 dfs 仅有两个参数 depth 和 i，depth 表示选了几个数，i 表示从第几个数开始选。   

具体思路：对于第 i 个数，若它前面一个生命值已经为负数了，则可以选择直接对 $ i+1 $ 个人释放火球，或选择对当前的第 i 人释放火球。  

由于直接选择攻击第 $ i+1 $ 个人时，没有人受伤，因此传参的时候 depth 无需+1，也不需要改变任何其他的状态

```cpp
if (hp[i - 1] < 0 && i + 1 < n)
    dfs(depth, i + 1);
```

而若选择对第 i 人放火球则需要选上，所以不仅 depth 要加一，还要改变状态并做好回溯的操作


```cpp
if (hp[i] >= 0 || hp[i - 1] >= 0 || hp[i + 1] >= 0) {
	hp[i] -= a, hp[i - 1] -= b, hp[i + 1] -= b, v.emplace_back(i);
	dfs(depth + 1, i);
	hp[i] += a, hp[i - 1] += b, hp[i + 1] += b, v.pop_back();
    }
```

按这种计算方法，若第 n 个人以及他前面的二人的血量都为负数，那么再往前的人一定也已经死了（因为只有当 $ hp[i-1]<0 $ 时才会往后艘），这时候直接记录答案即可  


```cpp
if (hp[n] < 0 && hp[n - 1] < 0 && hp[n-2] < 0) {
	if (minx > depth) {
		minx = depth;
		ans.clear();
		for (int i = 0; i < v.size(); ++i)
			ans.emplace_back(v[i]);
	}
	return;
}
```

若选择的个数已经超过了此前找的某个答案数则直接返回


```cpp
if (depth >= minx)
	return;
```
下附完整代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef const int ci;

int n, a, b, minx = INF;
int hp[15];
vector<int> ans, v;

void dfs(ci& depth, ci& i) {
    if (depth >= minx)
        return;
    if (hp[n] < 0 && hp[n - 1] < 0 && hp[n-2] < 0) {
        if (minx > depth) {
            minx = depth;
            ans.clear();
            for (int i = 0; i < v.size(); ++i)
                ans.emplace_back(v[i]);
        }
        return;
    }
    if (hp[i - 1] < 0 && i + 1 < n)
     dfs(depth, i + 1);
    if (hp[i] >= 0 || hp[i - 1] >= 0 || hp[i + 1] >= 0) {
        hp[i] -= a, hp[i - 1] -= b, hp[i + 1] -= b, v.emplace_back(i);
        dfs(depth + 1, i);
        hp[i] += a, hp[i - 1] += b, hp[i + 1] += b, v.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i)
        cin >> hp[i];
    dfs(0, 2);
    cout << minx << endl;
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
}
```


---

## 作者：zrzring (赞：0)

[更好的阅读体验](http://zrzring.cn/index.php/archives/261)

> 你拥有一个直接伤害为a，溅射伤害为b，溅射范围为1的技能，问至少多少次技能能消灭一排随从

> 限制：不能打1号和n号随从，生命值**小于**0才算死亡

限制貌似是让你做的更舒服一些，至少我是这么认为的

dp或者dfs都可以，实现本质是一样的，dp做法因为上一个会对当前造成影响，记录一下上一个状态即可

这样多一维变成`f[i][j][k]`表示第i个随从被打k下，第i-1个随从被打j下，前i-2个随从都死了的最少技能次数

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

void file() {
    freopen("std.in", "r", stdin);
    freopen("wa.out", "w", stdout);
}

const int N = 1e6 + 10, M = 2e6 + 10, inf = 0x3f3f3f3f;

inline int read() {
    bool sym = 0; int res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}

int n, a, b, rem, f[21][201][201], pre[21][201][201][2], hp[100];

int main() {
    n = read(); a = read(); b = read();
    for (int i = 1; i <= n; i++) hp[i] = read();
    memset(f, 0x3f, sizeof(f));
    for (int k = hp[1] / b + 1; k <= 20; k++) f[2][0][k] = k;
    for (int i = 2; i <= n - 1; i++) {
        for (int j = 0; j <= 20; j++) {
            for (int k = 0; k <= 20; k++) {
                if (f[i][j][k] == inf) continue;
                rem = hp[i] - j * b - k * a;
                rem < 0 ? rem = 0 : rem = rem / b + 1;
                for (int l = rem; l <= 20; l++) {
                    if (l + f[i][j][k] < f[i + 1][k][l]) {
                        f[i + 1][k][l] = l + f[i][j][k];
                        pre[i + 1][k][l][0] = j;
                        pre[i + 1][k][l][1] = k;
                    }
                }
            }
        }
    }
    int x, y;
    int ans = inf, j0, k0, r0;
    for (int j = 0; j <= 20; j++) {
        for (int k = 0; k <= 20; k++) {
            if (f[n - 1][j][k] == inf) continue;
            if (k * b <= hp[n]) rem = (hp[n] - b * k) / b + 1;
            else {
                rem = hp[n] - j * b - k * a;
                if (rem < 0) rem = 0; else rem = rem / b + 1;
            }
            if (rem + f[n - 1][j][k] < ans) {
                ans = rem + f[n - 1][j][k];
                x = j; y = k; r0 = rem;
            }
        }
    }
    printf("%d\n", ans);
    while (r0--) printf("%d ", n - 1);
    for (int i = n - 1; i >= 2; i--) {
        int tx = x, ty = y;
        x = pre[i][tx][ty][0];
        y = pre[i][tx][ty][1];
        while (ty--) printf("%d ", i);
    }
    return 0;
}
```

---

## 作者：叶枫 (赞：0)

$dfs$ 好啊

### 题意

- 有一队人，你可以用火球点某个人，会对当前人造成a点伤害，对旁边的人造成b点伤害。

- 不能打1号和n号，求最少多少发点死所有人。

### Note 
- 一个人被打死当且仅当它的血量$<0$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#define ll long long
#define maxn 100005
#define inf 2147483647
#define mod 10003
#define eps 1e-6
#define pi acos(-1.0)
#define de(x) ((x)*(x))
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int n,a,b,h[15],tot,ans;
int p[155],val[155];
inline void check(){
	int yu=max(h[n-1]/a+(h[n-1]>=0),h[n]/b+(h[n]>=0));
	for(int i=1;i<=yu;i++) p[++tot]=n-1;
	if(ans>tot){
		for(int i=1;i<=tot;i++) val[i]=p[i];
		ans=tot;
	}
	tot-=yu;
}
inline void dfs(int now){//标准的dfs
	if(now>n-1) {check();return;}
	if(h[now-1]<0) dfs(now+1);
	int last=tot,A=h[now-1],B=h[now],C=h[now+1];
    while(1){
        h[now]-=a; h[now-1]-=b;
		h[now+1]-=b; p[++tot]=now;
        if(h[now-1]<0) dfs(now+1);
        if((h[now-1]<0&&h[now]<0)||tot>=ans){
            tot=last;
            h[now-1]=A; h[now]=B; h[now+1]=C;
            break;
        }
    }
}
signed main(){
	n=read(); a=read(); b=read();
	for(int i=1;i<=n;i++) h[i]=read();
	ans=inf; tot=0;
	dfs(2);
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++) printf("%d ",val[i]);
    return 0;
}
```

---

