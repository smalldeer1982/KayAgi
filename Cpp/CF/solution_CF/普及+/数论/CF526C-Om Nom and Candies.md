# Om Nom and Candies

## 题目描述

桌子上有无限多的红糖果与蓝糖果，每个红糖果重 $ W_{r} $ 克，而每个蓝糖果重 $ W_{b} $ 克。吃一颗红糖果可以获得 $ H_{r} $ 的快乐值，吃一颗蓝糖果可以获得 $ H_{b} $ 的快乐值。

在只能吃 $ C $ 克糖果的前提下，请求出能获得的最大快乐值。

## 样例 #1

### 输入

```
10 3 5 2 3
```

### 输出

```
16
```

# 题解

## 作者：_Kouki_ (赞：2)

### 做法一：  
假设第一种 $ x $ 个，第二种 $ y $ 个。     
根据题意可知:         
$x \times W_r + y \times W_b \le C$      
显然可以通过枚举一个算出另一个。    
这种思想的复杂度为 $O ( \sqrt{ C } ) $。     

1. 如果两种糖中重量最大的超过 $\sqrt{C}$ ，那么该糖最多也只能选择不超过个 $\sqrt{C}$ ，直接枚举该糖个数，记录最大欢乐度。  

1. 如果两种糖重量都小于 $\sqrt{C}$ , 那么从性价比来考虑。   
   假设$ \frac{H_r}{W_r} < \frac{H_b}{W_b}$ ，得到 $ H_r \times W_b  < H_b \times W_r$ 。         
   由这个不等式可知，买 $x$ 个 $r$ 糖得到的价值没有买 $y$ 个 $b$ 糖划算。（因为重量小于 $C$，买这么多糖也不会超重）      
   当需要买超过 $x$ 个 $r$ 糖时，不如去买 $b$ 糖，所以购买 $r$ 糖的数量肯定小于 $y$ 个，可以枚举 $r$ 糖的数量( $0$ 到 $y - 1$ )。   
   因此复杂度为 $O(\sqrt{C})$。   
  
## AC Code:
```cpp
#include<bits/stdc++.h> //真方便 

using namespace std;  

long long C,H[3],W[3];
int AC;
void swap_(long long &a, long long &b) //交换 
{
    long long t;
    t = a, a = b, b = t; 
}

int main()
{
    while(scanf("%lld", &C) != EOF)
    {
        scanf("%lld %lld %lld %lld", &H[1], &H[2], &W[1], &W[2]);//输入 
        if(W[2] > W[1])  swap_(W[2], W[1]), swap_(H[1], H[2]);//必须加这一步 
        
        long long maxn = -1, sum = 0; //maxn 为最大欢乐值 sum 为当前已经装的容积 
        
        if(W[1] * W[1] >= C) //装得下 
        {
        	for(int i = 0; i <= C/W[1]; i++)//枚举 
            {
              sum = i*H[1];
              sum += ((C-i*W[1])/W[2] * H[2]);   
              if(maxn < sum)  maxn = sum;    
            } 
        }
        else//装不下 比较性价比 
        {
            sum = 0;
            if(((H[1]*1.0) / W[1]) > ((H[2]*1.0) / W[2]))   swap_(H[1], H[2]), swap_(W[1], W[2]);//性价比 
            for(int i = 0; i <= W[2]; i++)//枚举 
            {
              sum = i*H[1];
              sum += ((C-i*W[1])/W[2] * H[2]);   
              if(maxn < sum)  maxn = sum;           
            }    
        } 
        
        printf("%lld\n", maxn);//输出              
    } 
    return 0;//完美结束 
}
```     
保证 $\colorbox{#44d920}{\color{white}AC}$

### 做法二：(剩余系)

不懂概念的去BDFS。     

对于同一个剩余系 $ y $ ，表示放满两种物品后，背包里面最终浪费的空间。     

**最优值在两端**     
只有两种商品，背包剩余空间一定。  
如果 $ r $ 性价比高，则越多越好，否则越少越好。      

所以求出所有剩余系，并且记录每个剩余系里面对应的最小 $ t $ 值(最大 $ t $ 值可以通过最小 $ t $ 值推出来)。    
比较最优值，得到全局最优。

本问题要分**两步**:    
1. 求出所有剩余系对应的 $ t $ 最小值 $t_{min}$(下面代码是保存在 $ a $ 数组中)。    

1. 如果 $ C_r $ 的性价比高，则要推出所在剩余系的 $ t $ 最大值 $ t_{ max } $ 因为同一个剩余系里面 $ t $ 的周期是 $ \frac{ W_b } { d } $,可以通过周期求出t的最大值。   
$t_{max} = t_{min} +  C / a / ( W_b / d ) \times ( W_b / d ) $    

$\textbf{d 表示}gcd(W_r,W_b)$   。 

如果 $( t_{max} > C / a )$ ，那么 $( t_{max} - = W_b / d )$。

## AC Code:
```cpp
#include<bits/stdc++.h>

using namespace std;

map<long long,long long>mp;
long long MINN[1000000],LA[1000000];//MINN 剩余系中最小的 LA 剩下的空间 
long long C,Hr,Hb,Wr,Wb;
int AC;
int main()
{
    scanf("%lld %lld %lld %lld %lld",&C ,&Hr, &Hb, &Wr, &Wb);
    if(Wr<Wb){swap(Hr,Hb);swap(Wr,Wb);}
    
	long long cnt=0;
	long long d=__gcd(Wr,Wb);
	long long minn=min(Wb/d+1,C/Wr+1);
	
	for(long long i=0;i<=minn;i++)//求模Wb的剩余系(C-x*Wr)%cb
    {
		long long t=((C-Wr*i)%Wb+Wb)%Wb;//(C-x*Wr)%cb
		if(mp.find(t)==mp.end())
		{
			LA[cnt]=t;//多余
			MINN[cnt++]=i;//剩余系里面保存的是x的最小取值
			mp[t]=1;
		}
	}
	
	long long maxn=0;
	if(Hr*Wb<=Hb*Wr)//如果LA性价比低，则取同余系中的数目
	{
		for(long long i=0;i<cnt;i++)
		{
			long long t=Wr*MINN[i];
			if(t>C){continue;}
			maxn=max(maxn,Hr*MINN[i]+(C-t)/Wb*Hb);
		}
	}
	else//LA糖果性价比高，则要取剩余系里面LA糖果的最大数目
    {
		for(long long i=0;i<cnt;i++)//(C-x*cr)%cb
		{
            long long nn=(C/Wr-MINN[i])/(Wb/d);// C/wr表示x的最大取值，MINN[i]是x的最小取值，整除的结果是看横跨几个周期
			nn=nn*Wb/d+MINN[i];//nn是x与MINN[i]在同一个剩余类的的最大取值
			long long t=nn*Wr;
			if(t>C){continue;}
			maxn=max(maxn,Hr*nn+(C-t)/Wb*Hb);
		}
	}
	
	printf("%lld",maxn);
    return 0;
}
```

---

## 作者：run_away (赞：1)

## 题意

有两种糖果，给出每种糖果的重量 $w_r,w_b$ 和吃掉一颗获得的快乐值 $h_r,h_b$。

你最多可以吃 $c$ 重量的糖果，求最大可获得的快乐值。

## 分析

看前面很多 dalao 都用了一些很强的算法，我只能来水一发 $O(\sqrt n)$ 的暴力。

考虑枚举每种糖果吃掉的数量，但是时间复杂度最大可到 $10^9$，明显过不了。

我们发现，若吃红糖 $i$ 颗，那么可吃蓝糖 $(c-i\times w_r)\div w_b$ 颗，反之亦然。

所以只要在枚举时考虑两种情况，可以在枚举 $1\sim\sqrt n$ 时同时计算 $\sqrt n\sim n$ 的值。

所以就直接打一个循环暴力水过，时间复杂度 $O(\sqrt n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
ll c,hr,hb,wr,wb,ans;
signed main(){
    c=read(),hr=read(),hb=read(),wr=read(),wb=read();
    for(ll i=0;i<=sqrt(c);++i){
        if(i*wr<c){
            ans=max(ans,i*hr+(c-i*wr)/wb*hb);
        }
        if(i*wb<c){
            ans=max(ans,i*hb+(c-i*wb)/wr*hr);
        }
    }
    printf("%lld",ans);
}
```

---

## 作者：Halberd_Cease (赞：1)

根号分治入门好题。

首先想到通过确定一种糖果的数量 $O(1)$ 推出另外一种。

枚举花费大的糖果可以最小化时间开销，令 $W_x=\max(W_b,W_r)$。

然后考虑根号分治：

- 对于 $W_x>\sqrt{C}$，因为 $W_x\le 10^9$ 所以总共枚举的数量不会超过 $\sqrt{10^9}\approx31622$；
- 对于 $W_x<\sqrt{C}$，必定有 $W_b\times W_r<C$，即两种如果都买到总重量 $W_b\times W_r$，那么买蓝色的贡献 $W_r\times H_b$ 和买红色的贡献 $W_b\times H_r$ 就可以确定，不失一般性假设 $W_r\times H_b<W_b\times H_r$，那么最优解中买蓝色的数量一定不超过 $W_r$ 个，因为如果超过，就一定可以用总价值更高，总花费相同的 $W_b\times H_r$ 替代，因此从 $0$ 到 $W_r-1$ 枚举蓝色个数，并且有 $W_r<\sqrt{C}$，不会超时，同理 $W_r\times H_b>W_b\times H_r$ 时亦然。

```cpp
    if (wb > wr)
    {
        swap(wb, wr);
        swap(hb, hr);
    }
    if (wr * wr >= c)
    {
        for (int i = 0; i <= c / wr; i++)
        {
            int ls = c - wr * i;
            int j = ls / wb;
            ans = max(ans, i * hr + j * hb);
        }
    }
    else
    {
        if (hr * wb > hb * wr)
        {
            swap(wb, wr);
            swap(hb, hr);
        }
        for (int i = 0; i <= wb; i++)
        {
            int ls = c - wr * i;
            int j = ls / wb;
            ans = max(ans, i * hr + j * hb);
        }
    }
```

---

## 作者：Autream (赞：0)

#### 题意简述
有红色和蓝色两种糖果，每颗红糖重 $W_r$ 克，每颗蓝糖重 $W_B$ 克。吃一颗红糖可以获得 $H_r$ 的快乐值，吃一颗蓝糖可以获得 $H_b$ 的快乐值。
问在最多吃 $C$ 克糖果的情况下能获得的快乐值。

---
#### 题目分析
题解区的大佬都是用什么根号分治和剩余系来做的，像我这种蒟蒻根本看不懂，所以我就想到了一个暴力的做法。

其实我们可以直接枚举选几颗红糖，剩下的重量全选蓝糖（枚举蓝糖同理），每次更新最大快乐值就可以了，最多枚举 $\sqrt C$ 次。

可以设吃 $i$ **克**红糖，$j$ **克**蓝糖。因为我们是通过枚举的方式来找到最优解，而最优解一定在解空间的边界上取得。所以，我们只需要在边界上进行枚举即可找到最优解。考虑到解空间大小为 $i_{\text{max}} \times j_{\text{max}}$，那么当 $i_{\text{max}} \times j_{\text{max}} \leq C$ 时，我们只需要循环 $\sqrt C$ 次，就可以覆盖到整个解空间边界，从而找到最优解。

---
#### AC Code
```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=1e9+5;
int C,Wr,Wb,Hr,Hb,ans;
signed main() {
    std::cin>>C>>Hr>>Hb>>Wr>>Wb;
    rep(i,0,std::sqrt(N)) {
        if(Wr*i<C) {
            ans=std::max(ans,i*Hr+(C-i*Wr)/Wb*Hb);
        }
        if(Wb*i<C) {
            ans=std::max(ans,i*Hb+(C-i*Wb)/Wr*Hr);
        }
    }
    std::cout<<ans;
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF526C)
## 思路
看起来像是根号分治入门题？

+ 若 $wr \ge \sqrt c$，则我们可以枚举 $r$ 的个数，时间复杂度 $O( \sqrt c)$。
+ 若 $wb \ge \sqrt c$，则我们可以枚举 $b$ 的个数，时间复杂度 $O( \sqrt c)$。
+ 接下来考虑捆绑一些物品：若 $\frac{hr}{wr} < \frac{hb}{wb}$，即 $r$ 的性价比比 $b$ 低。设当 $r$ 选择了 $x$ 个，$b$ 选择了 $y$ 个时，它们的价值相等，则 $x \times hr=y \times hb$。显然，此时 $b$ 的重量比 $r$ 低，所以选 $r$ 的数量一定小于 $x$ 个，那么我们显然可以枚举这个数量，时间复杂度 $O( \sqrt c)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int c,hr,hb,wr,wb;
    cin>>c>>hr>>hb>>wr>>wb;
    if (wr>=sqrt(c)){
        int ans=0;
        for (int i=0;i<=sqrt(c);++i){
            int x=wr*i;
            int y=c-x;y/=wb;
            if (x>c) break;
            ans=max(ans,i*hr+y*hb);
        }
        cout<<ans<<'\n';
    }else if (wb>=sqrt(c)){
        int ans=0;
        for (int i=0;i<=sqrt(c);++i){
            int x=wb*i;
            int y=c-x;y/=wr;
            if (x>c) break;
            ans=max(ans,i*hb+y*hr);
        }
        cout<<ans<<'\n';
    }else{
        int ans=0;
        if (hr*wb>hb*wr) swap(hr,hb),swap(wb,wr);
        for (int i=0;i<=wb;++i){
            int now=i*hr;
            now+=((c-i*wr)/wb*hb);
            ans=max(ans,now);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```


---

## 作者：cfkk (赞：0)

主要知识：[剩余系](https://blog.csdn.net/shuimu12345678/article/details/7880732)

次要知识：[map](https://www.cnblogs.com/fnlingnzb-learner/p/5833051.html)

思路：

不难看出对于同一个剩余系 y（表示放满两种物品后，背包里面最终浪费的空间），最优值在两端（只有两种商品，背包剩余空间一定，如果 cr 性价比高，则越多越好，否则越少越好）。

所以求出所有剩余系，并且记录每个剩余系里面对应的最小 t 值（最大 t 值可以通过最小 t 值推出来），比较最优值，得到全局最优。

本问题分为两步：

第一步，求出所有剩余系对应的 t 的最小值$t_{min}$（下面代码是保存在 a 数组中）。

第二步，如果 cr 的性价比高，则要推出所在剩余系的 t 最大值 $t_{max}$，因为同一个剩余系里面 t 的周期都是  $cb/d$ ，可以通过周期求出 t 的最大值。

公式：$t_{max}=t_{min}+C/cr/(cb/d)^2)$

如果 $t_{max}>C/cr$ ，那么 $t_{max}=t_{max}-cb/d$

让我们来举一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/qc8jcryi.png)

上图中，$C/cr=33$，$cb/d=5,d=gcd(3,5)=1$

代码来喽：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    char ch=getchar();
    int s=0,w=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-'){w=-1;}
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        s=(s<<1)+(s<<3)+ch-48;
        ch=getchar();
    }
    return w*s;
}
inline void print(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9){print(x/10);}
    putchar(x%10+'0');
}
map<int,int>mp;
int a[1000000];
signed main()
{
    int c=read(),Hr=read(),Hb=read(),Wr=read(),Wb=read();
	if(Wr<Wb){swap(Hr,Hb);swap(Wr,Wb);}
	int cnt=0;
	int d=__gcd(Wr,Wb);
	int lim=min(Wb/d+1,c/Wr+1);
	for(int i=0;i<=lim;i++)//求模wb的剩余系(c-x*cr)%cb
    {
		int tmp=((c-Wr*i)%Wb+Wb)%Wb;//(c-x*cr)%cb
		if(mp.find(tmp)==mp.end())
		{
			a[cnt++]=i;//剩余系里面保存的是x的最小取值
			mp[tmp]=1;
		}
	}
	int ans=0;
	if(Hr*Wb<=Hb*Wr)//如果r性价比低，则取同余系中的数目
	{
		for(int i=0;i<cnt;i++)
		{
			int tmp=Wr*a[i];
			if(tmp>c){continue;}
			ans=max(ans,Hr*a[i]+(c-tmp)/Wb*Hb);
		}
	}
	else//r糖果性价比高，则要取剩余系里面r糖果的最大数目
    {
		for(int i=0;i<cnt;i++)//(c-x*cr)%cb
		{
            int nn=(c/Wr-a[i])/(Wb/d);// c/wr表示x的最大取值，a[i]是x的最小取值，整除的结果是看横跨几个周期
			nn=nn*Wb/d+a[i];//nn是x与a[i]在同一个剩余类的的最大取值
			if(nn>c/Wr){nn-=Wb/d;}
			int tmp=nn*Wr;
			if(tmp>c){continue;}
			ans=max(ans,Hr*nn+(c-tmp)/Wb*Hb);
		}
	}
	print(ans);
    return 0;
}

```


---

