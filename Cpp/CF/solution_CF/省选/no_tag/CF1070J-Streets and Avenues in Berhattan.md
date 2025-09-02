# Streets and Avenues in Berhattan

## 题目描述

Berhattan 是 Berland 的首都。城市中有 $n$ 条东西方向（横向）平行的街道，以及 $m$ 条南北方向（纵向）平行的大道。每条街道与每条大道都相交，形成一个十字路口。因此，Berhattan 一共有 $n \cdot m$ 个十字路口。

最近，Berland 政府进行了更迭。新政府希望以革命英雄的名字来命名所有的街道和大道。

特别委员会准备了 $k$ 个名字的名单。只有这些名字可以被用作街道和大道的新名字。每个名字最多只能使用一次。

委员会成员希望以最小化居民不便为目标来命名街道和大道。他们认为，如果某条街道和某条大道的名字首字母相同，那么它们的交叉口会让居民感到不便。因此，只有每个名字的首字母才是重要的。

给定 $k$ 个名字的首字母，请你求出 $C$ ——在命名完成后，Berhattan 中最小可能的不便十字路口数量。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
2 3 9
EEZZEEZZZ
2 7 9
EEZZEEZZZ
```

### 输出

```
0
4
```

## 样例 #2

### 输入

```
2
4 4 8
CZBBCZBC
1 1 4
TTCT
```

### 输出

```
1
0
```

# 题解

## 作者：Ted_Tong (赞：3)

## 题目大意
有$m$条横线,$n$条竖线，共有 $(n*m)$ 个交叉点.
$(m+n≤k)$个名字（每个名字是一个大写字母），现在要给这$(m+n)$条线命名，若构成一个交叉点的两条直线的名字相同，则这个交叉点不美丽。         

问不美丽的交叉点的最少个数是多少。


多组数据,第一行t(数据组数)$(1≤t≤30000)$

每组数据依次为$n,m,k$,第二行是名称.


$(1≤n,m≤30000;n+m≤k≤2*10^5)$

## 分析
  我们对于一种名称，要尽可能将它全部置于横线或者全部置于竖线上，对于样例1的第二个数据来说，最优方案就是把2条竖线全部置为E，横线中两个E，五个Z。这样看来，我们只需要关注名称分配到横线上还是竖线上了，不必考虑分配到哪个线上。
  
  我们的目标就变成分配颜色到横线和竖线中（而不是哪根横线和哪根竖线中）,使得横竖同名数尽量少（因为$ans$=横向同名*纵向同名）。
  
  再举一个例子：
  
| | E | F |
| :----------: | :----------: |
|E| + |  |
|E| + |  |
|E| + |  |
|E| + |  |
|E| + |  |
|E| + |  |
|F|  | + | 

这样填空肯定不是最优的，因为有两种名字都重复了，我们可以将行中的$F$和列中的$E$互换，那么就可以达到更优情况。所以我们又有了一个结论：当重名种类大于等于$2$时，一定不是最优解。

那么接下来就很清晰了，我们枚举复的名字种类，去看哪种重复更好。然后我们考虑$i$为重复的颜色，$j$为它在列中存在的个数，那么它在行中会有$(cnt[i]-j-(k-n-m)$个（$cnt[i]$表示字母$i$的个数）。

$$ans=cnt[i]-j-(k-n-m)$$

**这个结论成立，当且仅当其他的字母可以填满列中剩余的$(n-j)$个空。**

我们只需要在更新$ans$之前判断其他的字母可以表示的位置就行了。
## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
#define N 200100
#define maxx 27
using namespace std;
ll T,m,n,K,dy,cnt[maxx],ans;
char str[N];
bool dp[N];
int main(){
    ll i,j,k;
    scanf("%lld",&T);
    dp[0]=1;
    while(T--){
        memset(cnt,0,sizeof cnt);
        ans=INF;
        scanf("%lld%lld%lld%s",&m,&n,&K,&str[1]);
        dy=K-m-n;
        if(m>n){//保证n是大的
            swap(m,n);
        }
        for(i=1;i<=K;i++){//出理cnt数组
            cnt[str[i]-'A'+1]++;
        }
        for(i=1;i<=26;i++){
            for(j=1;j<=n;j++){//清空
                dp[j]=0;
            }
            for(j=1;j<=26;j++){
                if(i==j){//要是不同种颜色
                    continue;
                }
                for(k=n;k>=cnt[j];k--){//处理能填满的
                    dp[k]|=dp[k-cnt[j]];
                }
            }
            for(j=min(cnt[i],n);j>=0;j--){
                if(!dp[n-j]){//如果其他颜色不能填到这
                    continue;
                }
                ans=min(ans,j*max(0ll,cnt[i]-j-dy));//更新ans
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}

```

---

## 作者：Graphcity (赞：1)

首先注意到每一条横线和竖线是没有任何区别的，所以我们只在乎所有的行 / 列中放的字母的种类和数量。

又因为大写字母只有 26 个，总数不超过 $2\times 10^5$ 个，可以使用背包 DP 来解决问题。

**结论**：在最优方案中，横行和数列中相同的字母至多一个。

**证明**：如果有两个，它们在横行中的出现次数分别为 $a,c$，竖列为 $b,d$，那么答案就是 $ab+cd$。可以通过调整其它字符的方式使得 $a+c=b+d$。

不妨令 $a\le d$，那么将 $d$ 中取出 $a$ 个字母放到横行，此时的贡献为 $a(d-a)$，又因为 $a+c=b+d$ 所以 $a(d-a)=a(c-b)$。

$ab+cd-(ac-ab)=2ab+c(d-a)>0$，因此这样肯定更优。

那么枚举重复出现的字符，对剩下的字符做背包即可。时间复杂度 $O(k|s|^2)$，字符集长度 $|s|=26$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

int T,n,m,k,cnt[26]; char s[Maxn+5];
int f[Maxn+5];

inline void Solve()
{
    scanf("%d%d%d",&n,&m,&k),scanf("%s",s+1);
    For(i,0,25) cnt[i]=0;
    For(i,1,k) cnt[s[i]-'A']++;
    long long ans=1ll*k*k;
    For(i,0,25)
    {
        For(j,0,k) f[j]=0; f[0]=1;
        For(j,0,25) if(i!=j) Rof(l,k,cnt[j]) f[l]|=(f[l-cnt[j]]);
        For(j,max(0,n-cnt[i]),k) if(f[j])
        {
            int a=max(0,n-j),b=max(0,m-(k-cnt[i]-j));
            if(a+b<=cnt[i]) ans=min(ans,1ll*a*b);
        }
    }
    printf("%lld\n",ans);
}

int main()
{
    scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
结论+背包题，感觉挺有意思。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
感觉没有任何做题的方向？

那就先分类讨论猜想一下。

1. 如果能够用不同的名字命名行和列，那肯定全部不同最好，答案即为 $0$。
2. 如果难以避免相同的名字，那肯定是只有一种重复的名字最好。

考虑证明：

设 $tot_i$ 表示行的名字为 $i$ 的个数，$cnt_i$ 表示列的名字为 $i$ 的个数，$S$ 表示名字的集合。

那么产生的答案即为 $\sum\limits_{i\in S}tot_i\times cnt_i$。

若有两种重复的字符，分别为 $i,j$，此时答案为 $tot_i\times cnt_i+tot_j\times cnt_j$。

不妨设 $cnt_i<tot_j$，那么我们可以通过交换的方式把列上的 $i$ 全部交换到行上。

那么行的情况就变成了 $tot_i+cnt_i$ 个 $i$ 名字，$tot_j-cnt_i$ 个 $j$ 名字。

列上则全是 $j$ 名字。

此时答案为 $(tot_j-cnt_i)\times(cnt_i+cnt_j)$。

其实到这一步答案就很明显了。

因为 $tot_j-cnt_i+cnt_i+cnt_j=tot_j+cnt_j$，而 $tot_j-cnt_i<tot_j$。

也就是 $xy>(x-c)(y+c),0<c<x$ 这种式子，显然是成立的。

所以前面那个答案严格劣于后面这个答案了。

有了这个结论，考虑如何实现。

先枚举相同的那个字符，然后对着其他字符跑一遍背包处理出哪些数量的名字是可以被凑出来的。

枚举给行与列的不重复名字数量，剩下的没被用到的名字就都可以给列用。

再剩下的就是重复部分了，判断下是否可行直接记录答案即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,V=2e5,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int T,n,m,k,ans,cnt[N],f[N];char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    T=read();
    while(T--)
    {
        n=read(),m=read();read();k=0;rd(s,k);ans=INF;
        for(int i='A';i<='Z';i++) cnt[i]=0;
        for(int i=1;i<=k;i++) cnt[s[i]]++;
        for(int i='A';i<='Z';i++)
        {
            for(int j=0;j<=k;j++) f[j]=0;f[0]=1;
            for(int j='A';j<='Z';j++) if(i!=j) for(int l=k;l>=cnt[j];l--) f[l]|=f[l-cnt[j]];
            for(int j=max(0ll,n-cnt[i]);j<=k;j++)
                if(f[j])
                {
                    int h=max(0ll,n-j),r=max(0ll,m-(k-cnt[i]-j));
                    if(h+r<=cnt[i]) ans=min(ans,h*r);
                }
        }print(ans);put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
半个结论题，加上一点点的背包 DP 优化。
## 分析。
有一个很显然的结论就是：在最优情况下最多只有一种名字（就是大写字母）会分别在行和列。证明如下：

设代价答案全部由 $A$ 得出，则我们不妨令集合 $S_A$ 和集合 $S_B$ 中分别有 $i$ 个 $A$ 和 $a-i$ 个 $A$。那么我们就考虑是否存在更优情况。我们将 $A$ 替换成 $B$ 则有一个转换：我们相当于把这个操作看做从 $S_B$ 中抽出 $j$ 个 $B$ 放入 $S_A$ 中，同时一共存在 $sum$ 个 $B$ 则显然存在一个答案贡献差。这个答案贡献差就是：
$$i\times\left(a-i\right)-\left(\left(i-j\right)\times\left(a-i+j\right)+j\times\left(sum-j\right)\right)$$
注意到上面的式子有一个约束条件为 $j$ 的取值范围最小为 $0$ 且最大为 $sum$ 和 $i$ 的较小值，在他们之间的 $j$ 都可以被取到。考虑化简上式则有：
$$2\times j^2-j\times\left(2\times i-a+sum\right)$$
将 $\left(2\times i-a+sum\right)$ 看做是一个常数，则这个式子就是一个以 $j$ 为自变量的单峰向上二次函数。

那么显然最大值只能在这个区间的端点上取到，这个端点有三种情况，分别是 $j=0$ 或者 $j=i$ 或者 $j=sum$ 时可以取到。且这三种情况都是对应着由 $A$ 或者 $B$ 得到的答案贡献。证毕。

有一个很显然的算法就是枚举中间的种类，然后在考虑能放在 $A$ 中的数取到多少个。显然我们通过以上的式子不难求得 $B$ 的个数，相应的最大值也可以求出来。这样基本的思路就出现了，因为只有 $26$ 个大写字母，所以直接背包 DP 优化即可。

代码如下，仅供参考：
```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,m,k,sum[100];
int ans;
char s[200005];
bool dp[200005];
int main(){
	cin>>t;
    while(t--){
    	bool flag=1;
    	ans=0x3f3f3f3f;
    	cin>>n>>m>>k>>s+1;
        int len=strlen(s+1);
        memset(sum,0,sizeof(sum));
        for (int i=1;i<=len;i++){
        	sum[s[i]-'A']++;
		}
        dp[0]=1;
        memset(dp,0,sizeof(dp));    
    	for (int i=0;i<=25;i++){
    		for (int j=k;j>=sum[i];j--){
    			dp[j]|=dp[j-sum[i]];
			}
		}
		for (int i=n;i<=k-m;i++){
			if(dp[i]){
				cout<<"0\n";
				flag=0;
				break;
			}
		}
		if(flag==0){
			continue;
		}
		for (int i=0;i<=25;i++){
			memset(dp,0,(n+m)*2);
			dp[0]=1;
			for (int j=0;j<=25;j++){
				if(i!=j){
					for (int k=n+m;k>=sum[j];k--){
						dp[k]|=dp[k-sum[j]];
					}
				}
			}
			for (int j=0;j<=n+m;j++){
				if(dp[j]){
					int l=max(n-j,0);
					int r=max(m-(k-sum[i]-j),0);
					if(l+r<=sum[i]){
						ans=min(ans,l*r);
					}
				}
			}
		}
		cout<<ans<<"\n";
	}
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

