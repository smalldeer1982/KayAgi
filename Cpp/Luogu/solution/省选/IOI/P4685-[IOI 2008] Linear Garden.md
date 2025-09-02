# [IOI 2008] Linear Garden

## 题目描述

拉美西斯二世刚刚获胜归来。为了纪念这一胜利，他决定建造一座壮观的花园。这个花园里的植物排成一行，从他在卢克索的宫殿直达卡纳克神庙。所种植的植物只有莲花和纸莎草，因为它们分别代表上埃及和下埃及。

这个花园中必须有$N$棵植物，并且必须保持平衡，即在花园中任取一段，其中莲花和纸莎草的棵数之差不能超过$2$。

花园可以被表示为由字母```L```（莲花）和```P```（纸莎草）组成的字符串。例如，当$N=5$时，有$14$种可能的平衡花园，按照字母排序如下：```LLPLP```，```LLPPL```，```LPLLP```，```LPLPL```，```LPLPP```， ```LPPLL```，```LPPLP```，```PLLPL```，```PLLPP```，```PLPLL```，```PLPLP```，```PLPPL```，```PPLLP``` 和 ```PPLPL```。

给定长度的所有可能的平衡花园可按字母顺序排序，并从$1$开始编号。例如，当$N=5$时，第$12$号花园是```PLPPL```。 

写一个程序，给定植物棵数$N$和一个表示平衡花园的字符串，计算该花园的序号模$M$的结果，其中$M$是一个给定的整数。 注意，在问题求解中，数值 $M$ 除了简化计算外没有其他的作用。 

## 说明/提示

有总分40分的测试点的$N$不超过$40$。

对于所有测试点，$1 \leq N \leq 1,000,000$，$7 \leq M \leq 10,000,000$。 

### 样例说明

第一个样例中，实际的序号是12。因此输出的是12模7，即5。

## 样例 #1

### 输入

```
5
7
PLPPL```

### 输出

```
5```

## 样例 #2

### 输入

```
12
10000
LPLLPLPPLPLL```

### 输出

```
39```

# 题解

## 作者：Seauy (赞：4)

这题正解当然是数位DP

但是当初不会，看到这题直接傻眼，则如之何……

被我用找规律硬找出来了，但是过程十分繁琐~~调了我五小时，眼睛都要看瞎了~~

这里简单说一下找出来的结果

首先是长度为 $ N $ 的公园的个数递推式：

$ f_0=1,f_1=2 $

$ f_i=2^{ [i-2-(i \bmod 2)] \div 2 + 1}+f_{i-1} $

然后令 $ L=0,P=1 $（同时保证了字典序），发现如果第一位为 0，那么花园的排名 $ 1 \leq loc \leq \frac{f_i}{2} $，否则 $ \frac{f_i}{2} < loc\leq f_i $ ~~这不废话吗~~

并且如果把合法花园 $ G_{loc} $ 按位取反一下的话，便是 $ G_{f_i-loc+1} $

然后只用考虑 $ 1 \leq loc \leq \frac{f_i}{2} $ 的情况就行了

最后一个毁天灭地惨无人道（还不是因为你太菜）的规律，如何计算

发现它满足如下程序所得 $ cnt $ 的结果

```cpp
void DFS(int ans,int depth,int thrw,bool com)
{
	if(depth>=n) {cnt=ans;return;}
	if(com)
	{
		if(Garden[depth+1]=='P') DFS((ans+POW2(thrw))%m,depth+2,thrw-1,1);
		else DFS(ans,depth+2,thrw-1,1);
		return;
	}
	if(depth&1)//向右边保留，左边去除 
	{
		if(Garden[depth+1]=='P')
		{
			//printf("+POW %d\n",POW2(thrw));
			DFS((ans+POW2(thrw))%m,depth+1,thrw-(!(n&1)),0);//走右边
		}
		else DFS(ans,depth+2,thrw-1,1);
	}
	else//向左边保留，右边去除 
	{
		if(Garden[depth+1]=='P')
		{
			//printf("+%d\n",f[n-depth-1]+1-POW2(thrw));
			DFS(ans+(f[n-depth-1]+1-POW2(thrw)+m)%m,depth+2,thrw-1,1);
		}
		else DFS(ans,depth+1,thrw-(n&1),0);
	}
}
```

至于为什么，我先奉上我找规律用的程序

```cpp
/*
	01 序列 称其为平衡序列时，任何一段的 0 与 1 个数之差小于等于 2
	将长度为 n 的所有平衡 01 序列 按字典序排序，问某个序列在第几个 %m
	L=0 P=1
	
	已知 Last 是平衡序列，长 a
	 
	
	n=1
	0 | 1
	
	n=2
	00 01 | 10 11
	
	n=3
	001 010 011 | 100 101 110
	
	n=4
	0010 
*/
#include<bits/stdc++.h>
#define mid ((L+R)>>1)
using namespace std;

const int MAXN=1e6;

int n;
int A[50][MAXN+5],num[50];
int f[50];

void PrintBinary(int ob,int len)
{for(int i=len;i;i--) cout<<((ob&(1<<(i-1)))>0);cout<<' ';}

int sum[3];
bool Check(int a,int len,bool b)
{
	memset(sum,0,sizeof sum);
	sum[b]=1; 
	for(int i=1;i<=len;i++,a>>=1)
	{
		sum[a&1]++;
		if(abs(sum[0]-sum[1])>2) return 0;
	}
	return 1;
}

bool Begin(int depth)
{
	if(depth==1) return 0;
	return depth&1;
}

int Translate(string ob,int len)
{
	int cnt=0;
	for(int i=0;i<len;i++) cnt=(cnt<<1)+(ob[i]=='P');
	return cnt;
}

int main()
{
	int show;scanf("%d",&show);
	f[1]=2;
	A[1][1]=0,A[1][2]=1,num[1]=2;
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
		for(int j=1;j<=num[i-1];j++)
		{
			if(Check(A[i-1][j],i-1,0)) A[i][++num[i]]=(A[i-1][j]<<1);
			if(Check(A[i-1][j],i-1,1)) A[i][++num[i]]=(A[i-1][j]<<1|1);
		}
	for(int i=1,choice,temp,val,times;i<=n;i++)
	{
		if(i>1)
		{
			if(i&1) f[i]=pow(2,(i-3)/2+1)+f[i-1];
			else f[i]=pow(2,(i-2)/2+1)+f[i-1];
		}
		printf("n=%d have %d ---------------- formula result: %d\n",i,num[i],f[i]);
		for(int j=1;j<=num[i];j++) PrintBinary(A[i][j],i);
		printf("\n");
		if(show==i)
		{
			while(1)
			{
				scanf("%d",&choice);
				if(choice==-1) break;
				temp=0;
				times=1;
				val=Begin(choice);
				for(int j=1,lst=-1;j<=num[i];j++)
				{
					if(!temp)
					{
						temp=1;
						lst=((A[i][j]&(1<<(i-choice)))>0);
						continue;
					}
					if(((A[i][j]&(1<<(i-choice)))>0)!=lst)
					{
						lst=((A[i][j]&(1<<(i-choice)))>0);
						printf("%d ",temp);
						temp=1;
						times++;
					}
					else temp++;
				}
				printf("%d\n",temp);
				for(int j=1;j<=times;j++) printf("%d ",val),val=1-val;
				printf("\n");
			}
			for(string KEY;1;)
			{
				cin>>KEY;
				if(KEY=="-1") break;
				int Code=Translate(KEY,i);
				for(int L=1,R=num[i];L<=R;)
				{
					if(A[i][mid]==Code) {printf("%d\n",mid);break;}
					if(A[i][mid]<Code) L=mid+1;
					else R=mid-1;
				}
			}
		}
	}
	return 0;
}
```

先输入 $ show,n $，表示程序会展示 $ N \in [1,n] $ 中所有花园的状态，并且展示到 $ N=show $ 的时候会暂停

对于暂停的那个 $ N $，接着输入若干 $ choice $，表示在长度为 $ N $ 的所有花园中，依次输出第 $ choice $ 位连续为 $ 0/1 $ 的段的长度

最后输入 -1 结束这一层的研究

比如当 $ N=5 $ 时，所有段转成 $ 0/1 $ 表示法长这样：

00101 00110 01001 01010 01011 01100 01101 10010 10011 10100 10101 10110 11001 11010

那么你再输入 $ choice=3 $，那么它会输出

2 3 2 2 3 2

1 0 1 0 1 0

表示前 **2** 个公园的第 3 位为 1，接下来 **3** 个公园的第 3 位为 0 ，再接下来 **2** 个公园的第 3 位为 1……

如果你展示出所有 $ choice \in [1,N] $，发现去掉 $ 0/1 $ 那行，会形成一个数字金字塔，顶端只有两个 $ \frac{f}{2} $，而最底层全为 1

从上一层变到下一层的规律大概是：有两个奇数，会选择两个相反的方向，一个把自己的一半向下取整放在左边，另一半放在右边，自己消失（两半的和当然要跟原来一样）；另一个则是向右

其它所有偶数全把自己分成相等的两半，1 就不用动了

至于选哪两个奇数……不是每次奇数把自己分成两半都会有一半是奇数，另一半是偶数嘛，那么下一层所选的奇数就是它们分出来的两奇数

然后还有每一层第一个花园的第 $ choice $ 位是 0 还是 1 的问题。规律是前两层第一个花园的第 $ choice $ 位是 0，之后一层便是 1，然后 $ 0/1 $ 交替

可能有些细节没有提到（因为过于复杂且已经过去好久了），还需大家自己看程序琢磨一下

最后把 AC 代码奉上：

```cpp
/*
	当 n 为 1 时， 奇数编号序列末尾为 0，偶数为 1
	当 n 为奇数时，奇数编号序列末尾为 1，偶数为 0
	当 n 为偶数时，奇数编号序列末尾为 0，偶数为 1
	
	序列个数为
		当 n 为奇数时 f[n]=(2^((n-3)/2)+f[n-1]/2)*2
		当 n 为偶数时 f[n]=(2^((n-2)/2)+f[n-1]/2)*2 
					  f[1]=2
	
	当序号 <= f[n]/2 时，开头为 0
	当序号 >  f[n]/2 时，开头为 1
	
	对于奇数来说 
		当序号 <= 2^((n-3)/2) 时，第二个为 0
		接下来 f[n-1]/2 个      ，第二个为 1
		接下来 f[n-1]/2 个      ，第二个为 0 
		最后      2^((n-3)/2) 个，第二个为 1
		
		          9
		          
		   31          31
		8      23   23     8
		8    15  8 8  15   8
		4 4 4 11 8 8 11 4 4 4
		4 4 4 4 7 4 4 4 4 4 4 7 4 4 4
		
	对于每个 n，第一个序列总会是 0010101010101... 
	
	序列个数的一半为
		当 n 为奇数时 f[n]/2=2^((n-3)/2)+f[n-1]/2
		当 n 为偶数时 f[n]/2=2^((n-2)/2)+f[n-1]/2
					  f[1]/2=1
*/
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6;

int n,m,cnt;
int f[MAXN+5];
string Garden;

int mem[MAXN+5]={1};
int POW2(int index)
{
	if(mem[index]) return mem[index];
	if(index<0) return 1;
	return mem[index]=(POW2(index-1)<<1)%m;
}

void DFS(int ans,int depth,int thrw,bool com)
{
	if(depth>=n) {cnt=ans;return;}
	if(com)
	{
		if(Garden[depth+1]=='P') DFS((ans+POW2(thrw))%m,depth+2,thrw-1,1);
		else DFS(ans,depth+2,thrw-1,1);
		return;
	}
	if(depth&1)//向右边保留，左边去除 
	{
		if(Garden[depth+1]=='P')
		{
			//printf("+POW %d\n",POW2(thrw));
			DFS((ans+POW2(thrw))%m,depth+1,thrw-(!(n&1)),0);//走右边
		}
		else DFS(ans,depth+2,thrw-1,1);
	}
	else//向左边保留，右边去除 
	{
		if(Garden[depth+1]=='P')
		{
			//printf("+%d\n",f[n-depth-1]+1-POW2(thrw));
			DFS(ans+(f[n-depth-1]+1-POW2(thrw)+m)%m,depth+2,thrw-1,1);
		}
		else DFS(ans,depth+1,thrw-(n&1),0);
	}
}

int main()
{
	f[1]=2,f[0]=1;
	scanf("%d %d",&n,&m);
	cin>>Garden,Garden=" "+Garden;
	//cout<<Garden<<endl;
	//printf("%d\n",Garden.length());
	//printf("Begin prework.\n");
	for(int i=2;i<=n;i++)
	{
		if(i&1) f[i]=(POW2((i-3)/2+1)+f[i-1])%m;
		else f[i]=(POW2((i-2)/2+1)+f[i-1])%m;
	}
	//printf("Prework Complete.\n");
	if(Garden[1]=='P')
	{
		for(int i=1;i<=n;i++)
			if(Garden[i]=='P') Garden[i]='L';
			else Garden[i]='P';
		//printf("Start DFS\n");
		DFS(1,1,n/2-1,0);
		printf("%d\n",(f[n]-cnt+1+m)%m);
	}
	else DFS(1,1,n/2-1,0),printf("%d\n",cnt);
	return 0;
}
```
时空复杂度 $ O(n) $

~~最后 BB 两句~~

这题是窝省集训队入门测题目，当时信心满满地交了上去，第二天去上课路上发现只有 60，T 到飞起

然后让教练帮忙看看哪错了，却没发现

稍加检查，发现是写递归 pow ~~忘记记忆化了~~ smg

由于常数比直接数位DP小太多了，所以一时间拿了窝省的效率 rk1

不过随后便被窝省神仙甩掉了，最后一次看到是 rk3

不建议大家用找规律这种不是办法的办法做题，一是经常找不准，二是要找就要花很多的时间，考场上可是不能这么干的，~~到时候万一只会找规律不就药丸~~

---

## 作者：zifanwang (赞：3)

一道~~基础 dp 题~~远古 IOI 题。

用 $dp_{i,x,y}$ 表示考虑完了前 $i$ 位，以当前位结尾的后缀中 `L` 的个数减 `P` 的个数最大为 $x$，`P` 的个数减 `L` 的个数最大为 $y$，剩下的位有多少种合法的构造方案，由题意得 $0\le x,y<3$。直接暴力转移即可。

花园的序号 $=$ 字典序小于这个花园的个数 $+1$。考虑如何统计字典序小于这个花园的个数，可以枚举第一个不同的位，暴力求和即可。

代码：

```c++
#include<bits/stdc++.h>
#define mxn 1000003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,m,x,y,ans,f[mxn][3][3];
char s[mxn];
signed main(){
	scanf("%d%d%s",&n,&m,s+1);
	rept(i,0,3)rept(j,0,3)f[n][i][j]=1;
	drep(i,n-1,1){
		rept(x,0,3){
			rept(y,0,3){
				if(x!=2)f[i][x][y]=f[i+1][x+1][max(y-1,0)];
				if(y!=2)f[i][x][y]=(f[i][x][y]+f[i+1][max(x-1,0)][y+1])%m;
			}
		}
	}
	rep(i,1,n){
		if(s[i]=='L'){
			x++,y=max(y-1,0);
			if(x>2)break;
		}else{
			if(x!=2)ans=(ans+f[i][x+1][max(y-1,0)])%m;
			x=max(x-1,0),y++;
			if(y>2)break;
		}
	}
	cout<<(ans+1)%m;
	return 0;
}
```

---

## 作者：ix35 (赞：3)

## P4685 [IOI2008] Linear Garden

之前仅有的一篇题解我是真没看懂，而且看起来方法和我完全不同，所以我自己写一篇吧...

考虑满足题目要求的几何意义：遇到一个 $L$ 就向上走一格，遇到一个 $P$ 就向下走一格，而满足要求的花园中任意一段的 $L$ 与 $P$ 的数量差不超过 $2$，其实就等价于在图像上任取两个点，纵坐标的差不能超过 $2$，也就是说图像在一个宽度最多为 $2$ 的区域内，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ll0gq653.png)

接下来转化一下问题：原来我们要求的是某个状态的字典序，其实就是问有多少个状态字典序更小，可以枚举 $i$，固定前 $i$ 位与给定状态相等，第 $i+1$ 位比给定状态小，而 $i+2$ 位之后随意安排，这样就可以不重不漏地统计所有字典序更小的状态，这是数位 DP 的思想。

于是我们按照套路，先解决计数问题，即：在宽度为 $2$ 的区域内走 $i$ 步，有多少种走法。显然从中间一行开始走和从两边的行开始走答案不同，设 $dp(0,i)$ 和 $dp(1,i)$ 分别表示从两边/中间的行开始行走 $i$ 步的方案数，两边只能走到中间，而中间可以走到任意一边，所以：

$$dp(0,i)=dp(1,i-1)$$

$$dp(1,i)=2\times dp(0,i-1)$$

边界状态：

$$dp(0,0)=dp(1,0)=1$$

然后就可以开始数位 DP，按照给定状态走，遇到一个 $L$，让当前位置往上一格，同时维护曾经走过的最高和最低位置，如果遇到一格 $P$ 就要统计贡献了，先当它是 $L$ 计算一次后面的位的贡献，设曾经走过的最高和最低位置分别是 $mx,mn$，当前所在的位置是 $pos$：

1. $mx=mn+2$，那么宽度为 $2$ 的区域已经框定（即 $[mn,mx]$），如果 $pos=mx$ 或者 $pos=mn$，那么就是从这个区域的两边开始走，贡献是 $dp(0,n-i)$，其中 $i$ 是当前位置；反之如果 $pos=mn+1=mx-1$，那么就是从中间开始走，贡献是 $dp(1,n-i)$；

2. $mx=mn+1$，那么宽度为 $2$ 的区域可以是 $[mn,mx+1]$，也可以是 $[mn-1,mx]$，容易发现不管 $pos$ 是 $mx$ 还是 $mn$，都有一种情况处在两边，一种情况处在中间，所以贡献是 $dp(0,n-i)+dp(1,n-i)$，但是还要注意这两种情况是有交集的，也就是不断在 $[mn,mx]$ 之间反复横跳，这种状态多数了一次，要减掉一次，所以实际贡献是 $dp(0,n-i)+dp(1,n-i)-1$。

别忘了答案要在上面的基础上加 $1$，因为算的是排名。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
int dp[2][MAXN],ans,n,p,mx,mn,nw;
char c[MAXN];
int main () {
	scanf("%d%d",&n,&p);
	dp[0][0]=dp[1][0]=1;
	for (int i=1;i<=n;i++) {
		dp[0][i]=dp[1][i-1];
		dp[1][i]=(dp[0][i-1]+dp[0][i-1])%p;
	}
	scanf("%s",c+1);
	ans=1;
	for (int i=1;i<=n;i++) {
		if (c[i]=='L') {
			nw++;
			mx=max(mx,nw);
			mn=min(mn,nw);
		} else {
			nw++;
			int tmx=max(mx,nw);
			int tmn=min(mn,nw);
			if (tmx-tmn==2) {
				if (nw==tmx||nw==tmn) {ans=(ans+dp[0][n-i])%p;}
				else {ans=(ans+dp[1][n-i])%p;}
			} else if (tmx-tmn==1) {
				ans=(ans+dp[0][n-i]+dp[1][n-i]-1)%p;
			}
			nw-=2;
			mx=max(mx,nw);
			mn=min(mn,nw);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：DDOSvoid (赞：2)

令 $L=-1,P=1$，则满足条件的序列一定任意一个前缀的任意一个后缀只能是 $-2,-1,0,1,2$

一共只有 5 个状态，那么我们可以压一下状态，然后就可以直接做 数位dp 了

令 $f[i][j][0/1]$ 表示到了第 $i$ 位，状态为 $j$，是否顶着上界

复杂度为 $O(n2^5)$

```cpp
#include<iostream>
#include<cstdio>
#define maxn 1000010
#define maxm 32
#define ll long long
using namespace std;

inline int F(int x) {
    return x + 2; 
}

int n, p, a[maxn];

char s[maxn]; 

int f[2][32][2];
inline void mem(int F) {
    for (int i = 0; i < 32; ++i)
        for (int j = 0; j < 2; ++j) f[F][i][j] = 0; 
}

inline bool check(int st, int x) {
    if (!x && (st & 1)) return 0;
    if (x && (st & 16)) return 0;
    return 1; 
}

int main() {
    scanf("%d%d%s", &n, &p, s + 1); int M = 31;
    for (int i = 1; i <= n; ++i) a[i] = (s[i] == 'P');
    if (a[1]) f[1][2][0] = f[1][8][1] = 1;
    else f[1][2][1] = 1; 
    for (int i = 1; i < n; ++i) {
        int t2 = i & 1, t1 = t2 ^ 1; mem(t1);
        for (int j = 0, st; j <= M; ++j) {
            if (!f[t2][j][0] && !f[t2][j][1]) continue ; 
            for (int k = 0; k < 2; ++k) {
                if (!check(j, k)) continue ; 
                st = k ? j << 1 | 8 : j >> 1 | 2;
                f[t1][st][0] = (f[t1][st][0] + f[t2][j][0]) % p;
                if (k < a[i + 1]) f[t1][st][0] = (f[t1][st][0] + f[t2][j][1]) % p;
                else if (k == a[i + 1]) f[t1][st][1] = (f[t1][st][1] + f[t2][j][1]) % p; 
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= M; ++i)
        for (int j = 0; j < 2; ++j) ans = (ans + f[n & 1][i][j]) % p;
    cout << ans << endl;
    return 0;
}

```


---

## 作者：hegm (赞：1)

### [P4685 [IOI2008] Linear Garden](https://www.luogu.com.cn/problem/P4685)

首先将 `LP` 替换为 `01`。

考虑基础思路，从头向后考虑，对于第 $i$ 位，如果可以填 `0` 而方案填了 `1`，那么将答案增加第 $i$ 位填 `0` 且前 $i-1$ 位不变的方案数。

那么问题转化成了，每次询问一个前缀限制下，对应长度能有多少种方案满足题意。

考虑将前缀限制压缩一下，容易发现，我们任何一个位置的前缀信息可以压缩为两个数字 $A,B$ 表示当前位置接着向下填可以填充多少个连续的 $0/1$。

容易发现，$A,B$ 的范围是 $[0,2]$。

举个例子，比如 $01$ 这个前缀限制。

那么你极限可以填 $010$ 即 $A=1$ 个 $0$，如果填 $0100$ 就会不满足题目限制。

同理可以填 $011$ 即 $B=1$ 个 $1$，如果填 $0111$ 就会不满足限制。

因此 $01$ 这个前缀的限制为 $A=1,B=1$。

同理可知：

$00\to (0,2)$

$0\to (1,2)$

既然把前缀限制压缩了，那么我们就可以用 `dp` 预处理出方案数。

$f_{a,b,i}$ 表示在 $A=a,B=b$ 的限制下，长度为 $i$ 的段的方案数是多少。

考虑转移，手模几个就会发现规律。

在 $(A,B)$ 情况下向后填一个 $0$ 那么限制会变成 $(A-1,\min(B+1,2))$。

填 $1$ 同理。

那么转移很显然 $f_{a,b,i}=f_{a-1,\min(b+1,2),i-1}+f_{\min(a+1,2),b-1,i-1}$。

注意 $a=0$ 或者 $b=0$ 时的边界。 初始化的话 $f_{a,b,0}=1$ 即可。


### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define make make_pair
#define N 1000006
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,f[3][3][N],sum=2,ans,A,B;
char c[N];
int add(int a,int b){return (1ll*a+b)%m;}
signed main()
{
	n=read();m=read();cin>>(c+1);
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)
	{
		f[i][j][0]=1;
		if(i)f[i][j][1]++;
		if(j)f[i][j][1]++;
	}
	for(int i=2;i<=n;i++)
	{
		for(int x=0;x<3;x++)for(int y=0;y<3;y++)
		{
			if(x)f[x][y][i]=add(f[x][y][i],f[x-1][min(2,y+1)][i-1]);
			if(y)f[x][y][i]=add(f[x][y][i],f[min(2,x+1)][y-1][i-1]);
		}
	}
	A=2;B=2;
	for(int i=1;i<=n;i++)
	{
		if(c[i]=='P'&&A!=0)ans=add(ans,f[A-1][min(2,B+1)][n-i]);
		if(c[i]=='P')A=min(A+1,2),B--;
		else B=min(B+1,2),A--;
	}
	cout<<add(ans,1)<<"\n";
	return 0;
}

```

---

## 作者：0x3F (赞：1)

“第几个”可以看作“小于等于它的数量”。

考虑 `DP`。

对于每一个位置 $i$，包含 $1$ 到 $i$ 的前缀的每一个后缀（包括空串）中 `L` 最多比 `P` 多两个，`P` 也最多比 `L` 多两个。

由于涉及到字典序，可以多开一维表示当前是小于还是等于，类似于数位 `DP`

于是可以设计状态了。

$dp_{i,p,l,t}$ 表示符合下列要求的前缀的数量。

+ 长度为 $i$；

+ 该前缀的所有后缀中，`P` 比 `L` 多的数量的最大值为 $p$；

+ 该前缀的所有后缀中，`L` 比 `P` 多的数量的最大值为 $l$；

+ $t=1$ 则该前缀的字典序严格小于原串对应前缀的字典序；

+ $t=0$ 则两串相等。

滚动数组优化，时间 $O(n)$ ，空间 $O(1)$。

转移自己想吧。

```cpp
#include <cstdio>
int n， m, a;
int dp[2][3][3][2];
char ch;
bool x;
int main() {
	scanf(“%d%d”, &n, &m);
	dp[0][0][0][0] = 1;
	for (int t = 1; t <= n; t++) {
		x = (t&1);
		ch = getchar();
		while (ch != ‘L’ && ch != ‘P’) ch = getchar();
		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++) {
				for (int k = 0; k <= 1; k++) {
					dp[x][i][j][k] = 0;
				}
			}
		}
		if (ch == 'P') {
			for (int i = 1； i <= 2; i++) {
				for (int j = 0; j <= 1; j++) {
					if (!j) {
						dp[x][i][j][0] += dp[!x][i-1][j][0];
						dp[x][i][j][1] += dp[!x][i-1][j][1];
					}
					dp[x][i][j][0] += dp[!x][i-1][j+1][0];
					dp[x][i][j][1] += dp[!x][i-1][j+1][1];
				}
			}
			for (int i = 0; i <= 1; i++) {
				for (int j = 1; j <= 2; j++) {
					if (！i) {
						dp[x][i][j][1] += dp[!x][i][j-1][0] + dp[!x][i][j-1][1];
					}
					dp[x][i][j][1] += dp[!x][i+1][j-1][0] + dp[!x][i+1][j-1][1];
				}
			}
		} else {
			for (int i = 0; i <= 1; i++) {
				for (int j = 1; j <= 2; j++) {
					if (!i) {
						dp[x][i][j][0] += dp[!x][i][j-1][0];
						dp[x][i][j][1] += dp[!x][i][j-1][1];
					}
					dp[x][i][j][0] += dp[!x][i+1][j-1][0];
					dp[x][i][j][1] += dp[!x][i+1][j-1][1];
				}
			}
			for (int i = 1; i <= 2; i++） {
				for (int j = 0; j <= 1; j++) {
					if (!j) {
						dp[x][i][j][1] += dp[!x][i-1][j][1];
					}
					dp[x][i][j][1] += dp[!x][i-1][j+1][1];
				}
			}
		}
		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++) {
				for (int k = 0; k <= 1; k++) {
					dp[x][i][j][k] %= m;
				}
			}
		}
	}
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) {
			for (int k = 0; k <= 1; k++) {
				a += dp[x][i][j][k];
			}
		}
	}
	a %= m;
	printf("%d\n", a);
	return 0;
}
```


---

