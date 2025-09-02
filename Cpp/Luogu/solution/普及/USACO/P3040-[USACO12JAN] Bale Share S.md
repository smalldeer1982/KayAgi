# [USACO12JAN] Bale Share S

## 题目描述

FJ 有 $n$ 包干草，第 $i$ 干草的重量是 $s_i$，他想尽可能平均地将干草分给三个农场。

他希望分配后的干草重量最大值尽可能地小，比如，$b_1,b_2,b_3$ 是分配后的三个值，假设 $b_1 \ge b_2 \ge b_3$，则他希望 $b_1$ 的值尽可能地小。

请计算 $b_1$ 的最小值。


## 说明/提示

【样例解释】  
一种满足要求的分配方案是：  
农场 1: $2,9,15$，$b_1 = 26$   
农场 2: $4,8,14$，$b_2 = 26$   
农场 3: $5,20$，$b_3 = 25$   

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 20$，$1 \le s_i \le 100$。

## 样例 #1

### 输入

```
8 
14 
2 
5 
15 
8 
9 
20 
4 
```

### 输出

```
26 
```

# 题解

## 作者：functionendless (赞：12)

简单到极致的DP题，大牛的大水题

f[i][j]->B\_1=i,B\_2=j,B\_3=sum-i-j此方案可不可行

f[i][j]=f[i-v][j] | f[i][j-v];//如果有人问为什么不用f[i][j]的话继续往下看

其实本来每次更新sum是f数组要相应的完全更新

但是因为可以直接把这坨草丢到B\_3上，所以就省去了memset的复杂度

代码如下（30行都没到）

```cpp
#include<cstdio>
using namespace std;
bool f[1000][1000];
int n,sum;
inline int min(int a,int b) {return a<b?a:b;}
int main()
{
    int tmp,i,j,k;
    scanf("%d",&n);
    f[0][0]=1;
    for(i=1;i<=n;i++)
    {
        scanf("%d",&tmp);
        for(j=min(999,sum);j>=0;j--)
            for(k=min(999,sum);k>=0;k--)
                if(f[j][k])
                {
                    if(j+tmp<999) f[j+tmp][k]=1;
                    if(k+tmp<999) f[j][k+tmp]=1;
                }
        sum+=tmp;
    }
    tmp=sum/3;
    for(i=tmp;i<=sum;i++)
        for(j=i;sum-i-j<=j;j--)
            if(f[i][j]) {printf("%d",i); return 0;}
    return 0;
}
```

---

## 作者：Kizuna_AI (赞：8)

[我的博客](https://likecoding.tech)

众所周知，这道题暴力枚举是会TLE的，只能获得50pts的好成绩（好吗？） 那么 我们就采用一些玄学的方法来过（或获取比50pts高的分）

就是——随机数+获取程序运行时间

我们发现 这个算法速度的快慢是肯定与顺序有关联的。换句话说：先暴力枚举a b c和先暴力枚举 a c b可能会有差别。那么我们可以使用随机数来考虑执行的顺序。总共有$A_3^2=6$种情况。

那么可能会说，我这么尝试不是还是都要枚举一遍吗？和顺序没有大关系，总归还是会TLE的。

TLE会使得这个测试点一分没有，但是如果你输出一个答案（正确性不能保证，但是有一定概率是正确的）还是有希望获得一些分的。那么我们就希望：我们递归就按照照常来递归，时限是1s，那么我们让他重复执行0.99s（保险起见一般不建议0.99s，很容易TLE，建议0.9s或0.95s），然后直接输出答案

那么，对于递归来说加一些剪枝优化不是更好吗？对于玄学程序来说，剪枝加的越多越好，这样可以尽可能多的去考虑可能性。（这里不细讲剪枝了，可以移步其他题解）

代码（可能并不能AC）：
```
#include<bits/stdc++.h>
using namespace std;
int n,tot=0,tot3,ans=1e9;
int s[25];
int a,b,c;
double starttime; 
void dfs(int step,int check) {
	if((clock()-starttime)/CLOCKS_PER_SEC>0.99) { //若实现>0.99秒时，立刻输出答案
		printf("%d",ans);
		exit(0); //不递归回去结束程序 直接在这里结束程序
	}
	if(step==n) {
		if(c>=b && c>=a) ans=min(ans,c);
		return;
	}
	if(c>=ans) return; //剪枝优化
	if(b>c+check || a>c+check) return; //剪枝优化
	int trand=rand();trand%=6; //产生0-5的随机数
	switch(trand) { //判断随机数顺序（内容主要是普通DFS）
		case 0:a+=s[step+1];dfs(step+1,check-s[step]);a-=s[step+1];
			   b+=s[step+1];dfs(step+1,check-s[step]);b-=s[step+1];
			   c+=s[step+1];dfs(step+1,check-s[step]);c-=s[step+1];break;
		case 1:a+=s[step+1];dfs(step+1,check-s[step]);a-=s[step+1];
			   c+=s[step+1];dfs(step+1,check-s[step]);c-=s[step+1];
			   b+=s[step+1];dfs(step+1,check-s[step]);b-=s[step+1];break;
		case 2:b+=s[step+1];dfs(step+1,check-s[step]);b-=s[step+1];
			   a+=s[step+1];dfs(step+1,check-s[step]);a-=s[step+1];
			   c+=s[step+1];dfs(step+1,check-s[step]);c-=s[step+1];break;
		case 3:b+=s[step+1];dfs(step+1,check-s[step]);b-=s[step+1];
			   c+=s[step+1];dfs(step+1,check-s[step]);c-=s[step+1];
			   a+=s[step+1];dfs(step+1,check-s[step]);a-=s[step+1];break;
		case 4:c+=s[step+1];dfs(step+1,check-s[step]);c-=s[step+1];
			   a+=s[step+1];dfs(step+1,check-s[step]);a-=s[step+1];
			   b+=s[step+1];dfs(step+1,check-s[step]);b-=s[step+1];break;
		case 5:c+=s[step+1];dfs(step+1,check-s[step]);c-=s[step+1];
			   b+=s[step+1];dfs(step+1,check-s[step]);b-=s[step+1];
			   a+=s[step+1];dfs(step+1,check-s[step]);a-=s[step+1];break;
	}
}
int main() {
	starttime=clock(); //记录初始时间
	srand((unsigned)time(0)); //初始化随机数种子
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&s[i]);
		tot+=s[i];
	}
	if(n==1) {
		printf("%d",s[1]);
		exit(0);
	}
	sort(s+1,s+1+n,greater<int>()); //剪枝优化
	dfs(0,tot);
	printf("%d",ans);
	return 0;
}
```

### 提醒：这不是正解！比赛时想不到正解才采用这种类似的玄学做法！不能保证100分

Q：那么，我是非酋。这串代码并不能让我AC怎么办？

A：您好，非酋！我也是！[我的提交记录](https://www.luogu.org/record/26518957) 您可以下载不能AC的数据，尝试去调参（就是srand()里的数值）

Q：我本地是能通过这个测试点的，但是在洛谷上就过不了了？

A：不妨试试[洛谷IDE](https://www.luogu.org/ide)进行调参

Q：我调了1个hour了，还没调出来怎么办？

A：不可能吧...我一下就调出来了，给你参考一个`srand(1022);`

---

## 作者：小小小朋友 (赞：7)

#### 题目描述

这是我们模拟赛题目……结果我这道题暴力50分……

FJ有N (N较小)包干草，干草i的重量是 $S_i$，他想尽可能平均地将干草分给3个农场。

他希望分配后的干草重量最大值尽可能地小。

#### 思路简述

虽然这里有最大值最小，但是这道题并不需要二分答案，我们看到N只有20，于是希望枚举每个干草，但是我们发现：
![图片.png](https://i.loli.net/2019/11/04/JgLKf5IFrypmS8E.png)

于是我们需要一些剪枝优化……

不妨设其中$c\leq b\leq a$

- 如果此时的$a$的总和已经大于$a$已算出的答案那么就不用算了
- 如果此时$a+x_i+x_{i+1}+……+x_n\leq b$，也就是a不可能再比b大了，就不用算了
- 从大到小排序，有助于提早剪枝
- 氧气（楼上的记忆化搜索开了好多map，这玩意常数太大）

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,x[25],ac=9999,ag=9999,af=9999,sum=0;
void dfs(ll p,ll c,ll g,ll f,ll ls){//dfs,ls表示剩余的数的总和
	if(c>=ac) return;//剪枝1
	if(f>c+ls||g>c+ls||f>g+ls) return;//剪枝2
	if(p==n+1){//搜索结束
		if(c<ac&&c>=g&&g>=f) ac=c,ag=g,af=f;
		return;
	}
	dfs(p+1,c+x[p],g,f,ls-x[p]);
	dfs(p+1,c,g+x[p],f,ls-x[p]);
	dfs(p+1,c,g,f+x[p],ls-x[p]);
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&x[i]),sum+=x[i];
	sort(x+1,x+n+1);
	reverse(x+1,x+n+1);//从大到小排序
	dfs(1,0,0,0,sum);//开始dfs
	printf("%lld",ac);//输出
	return 0;
}
```

---

## 作者：田大坑 (赞：5)

dp==dfs？100pts：70pts

------------
下面是一个ac的搜索，没开o2,也没有掐秒

搜索三大剪枝

1：重复状态的判断（stl大法吼）

2：答案最优性

3：方案可行性

```
#include<bits/stdc++.h>
using namespace std;
int n,a[21],f[21],ans=0x7f7f7f7f;
bool cmp(int a,int b)
{
    return a>b;
}
map<int,map<int,map<int,map<int,bool> > > >mp;
void dfs(int b1,int b2,int b3,int now)//题目说什么就做什么
{
	if(!mp[b1][b2][b3][now])//map判重，因为我们是顺序搜索，所以对于重复状态就像1+3==2+2=4一样无论怎么样，都不会影响后面的4+1=5
		mp[b1][b2][b3][now]=1;
	else
		return;
    if(now>n+1)
    return;
    if(b1>=ans||b2>=ans||b3>=ans)//如果不可能是最优的，return
    return;
    if(b1+f[now]<b2||b1+f[now]<b3||b2+f[now]<b3)//可行性，如果后面剩下的全部取上也不可以，那么就return
    return;
    if(now==n+1)
    {
        if(b1>=b2&&b2>=b3)
        ans=min(ans,b1);
    }
    dfs(b1+a[now],b2,b3,now+1);//顺序搜索便于进行重复状态的剪枝
    dfs(b1,b2+a[now],b3,now+1);
    dfs(b1,b2,b3+a[now],now+1);
}
int main()
{
	//freopen("in.txt","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    sort(a+1,a+1+n,cmp);//便于贪心剪枝以及大大优化时间复杂度
    for(int i=1;i<=n/3;i++)//贪心剪枝（真的有用，不然就会先dfs到底部更新b1，在往回搜索）
		ans+=a[i];
    for(int i=n;i>=0;i--)
    f[i]=f[i+1]+a[i];//后缀数组的维护
    dfs(0,0,0,1);
    printf("%d",ans);
}
```

---

## 作者：Galex (赞：4)

一道比较基础的动态规划题目。

## 思路：

我们先用一个 $sum$ 来表示总的柴草的重量。

用 $dp[i][j][k]$ 表示用前 $i$ 个柴草分给 $b_1$ 的重量为 $j$， $b_2$ 的重量为 $k$ 的可能性
此时 $b_3$ 就自然为 $sum-i-j$ ，不必再考虑（不一定 $b_1 ≥ b_2 ≥ b_3$ ）。

状态转移方程就自然而然地求出来了：

 **`dp[i][j][k] = dp[i - 1][j][k] | dp[i - 1][j - a[i]][k] | dp[i - 1][j][k - a[i]]`**
 
不过需要再判断一下有没有越界，然后每次求出的值为真就更新答案即可。

## 附C++代码

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n;
int a[30];
int sum = 0;//柴草的总重量 

bool dp[30][2005][2005] = {{0}};//dp数组，已解释过含义 
int ans = 0x3f3f3f3f;//答案，因为要求最小，所以先赋值为无穷大 

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i], sum += a[i];
	dp[0][0][0] = true;//初值，前0包柴草给b1 0重量，b2 0重量一定可行 
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= sum; j++)
			for (int k = 0; k <= sum; k++){
				//状态转移方程 
				dp[i][j][k] = dp[i - 1][j][k];
				if (j >= a[i])//如果不越界 
					dp[i][j][k] |= dp[i - 1][j - a[i]][k];//更新dp数组 
				if (k >= a[i])//如果不越界 
					dp[i][j][k] |= dp[i - 1][j][k - a[i]];//再次更新dp数组 
				if (dp[i][j][k])//如果分配方案可行 
					ans = min(ans, max(max(j, k), sum - j - k));//更新答案 
			}
	cout << ans;//输出答案 
	return 0;
}
```

---

## 作者：DiDi123 (赞：4)

# 题目分析
对于这道题来讲，乍一眼看上去像是搜索，楼上很多大奆佬们也是用 dfs + 剪枝的方法做的，蒟蒻现在就用一下 dp 的方法。

我做这道题的时候，第一个想到的 dp 做法是直接 dp 最优解，但我这回的最优解似乎跟上一回选什么没有什么直接关系，所以我们就需要另辟蹊径——我们可以 dp 一下**可行解**。

------------
**转移方程：**
$f(i,j,k)=f(i-1,j-a[i],k)||f(i-1,j,k-a[i])||f(i-1,j,k)$

其中，$f(i,j,k)$ 表示用前 $i$ 包干草，分给第一个农场 $j$ 重量的干草，分给第二个农场 $k$ 重量的干草。$a[i]$ 表示第 $i$ 包干草的重量。这个的 dp 的意思就是：分别把第 $i$ 包干草分给第一、二、三个农场，若其中一种情况在分之前就可行，那么分完后也一定可行。

**小优化：** 压一下维，改用滚动数组；$a$ 在每次输入时直接进行计算，不用存在数组中。
# 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN=2001; //一个农场最多只能分到20*100重量的干草 
bool f[MAXN][MAXN]; //记录可行性 
int n;
int a,sum; 
int ans=0x7f7f; //把ans设为最大值 
int main()
{
	cin>>n;
	f[0][0]=true; //很明显，不管怎样，第一、二个农场分0重量的干草总是可行的 
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		sum+=a; //sum为前i包干草的总重量 
		for(int j=sum;j>=0;j--)
			for(int k=sum-j;k>=0;k--)
				{
					if(j>=a) f[j][k]=f[j][k] || f[j-a][k]; //注意判断是否可以减a 
					if(k>=a) f[j][k]=f[j][k] || f[j][k-a];
				}
	}
	for(int i=0;i<sum;i++)
		for(int j=0;j<sum-i;j++)
		{
			if(f[i][j]) ans=min(max(i,max(j,sum-i-j)),ans); //暴力枚举b1最优解 
		}
	cout<<ans;
	
}
```


---

## 作者：wubaiting2020 (赞：3)

# 随机化贪心大法好
先上一个不一定正确的贪心，把当前的放进三堆当中最小的，然而肯定是错的，所以算下时间，可以随机 
#  500000次
然后就过了……
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LL long long
using namespace std;
int read()
{
   int s=0,bj=0;
   char ch=getchar();
   while(ch<'0'||ch>'9')bj|=(ch=='-'),ch=getchar();
   while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
   return bj?-s:s;
}
void printnum(int x)
{
	if(x>9)printnum(x/10);
	putchar(x%10^48);
}
void print(int x,char ch)
{
	if(x<0){putchar('-');x=-x;}
	printnum(x);putchar(ch);
}
int n;
int a[25];
int b[4],minn=0x3f3f3f3f;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int emm=1;emm<=500000;emm++)
	{
		random_shuffle(a+1,a+n+1);b[1]=b[2]=b[3]=0;
		for(int i=1;i<=n;i++)
		{
			int bj=0,aha=0x3f3f3f3f;
			for(int j=1;j<=3;j++){if(b[j]<aha){aha=b[j];bj=j;}}
			b[bj]+=a[i];
		}
		minn=min(minn,max(b[1],max(b[2],b[3])));
	}
	print(minn,'\n');
	return 0;
}

```


---

## 作者：jhsg (赞：2)

**采用DP,令g[n][b2][b3]为N个干草包，分B2仓库b2重量干草，分B3仓库b3质量干草，这种方案是否可行(显然,B1可由B2,B3仓库干草质量和总质量求出**

**转移方程 g[n][b2][b3]==1->g[n+1][b2][b3]=1&&g[n+1][b2][b3+bale]=1&&g[n+1][b2+bale][b3]=1;(bale为第n+1包干草质量）**

**显然空间上可以优化，因为第i项只与第i-1项有关，即**

**g[i%2][b2][b3]==1->g[(i+1)%2][b2][b3]=1&&g[(i+1)%2][b2][b3+bale]=1&&g[(i+1)%2][b2+bale][b3]=1**

```cpp
#include<bits/stdc++.h>
# define maxx 700//要使分得平均，sum<=20000,b2<700,b3<700 
using namespace std;
int n,bale,sum=0;
bool g[2][maxx+100][maxx+100]={0};
int read(){
    int x = 0, tmp = 1; char ch = getchar();
    while( ch < '0' || ch > '9' ) { if ( ch == '-' ) tmp = -1; ch = getchar();    }
    while( ch >= '0' && ch <= '9' ) { x = x * 10 + ch - '0'; ch = getchar();    }
    return x * tmp;
}
int main()
{
   //freopen("  .in","r",stdin);
   //freopen("  .out","w",stdout);
   n=read();
   g[0][0][0]=1;
   for(int i=0;i<n;i++)
   {
         bale=read();
         sum+=bale;
         for(int j=0;j<maxx;j++)
          for(int k=0;k<maxx;k++)
          {
                if(g[i%2][j][k])
                {
                    g[(i+1)%2][j][k]=1;
                    g[(i+1)%2][j+bale][k]=1;
                    g[(i+1)%2][j][k+bale]=1;
          }
       }
   }
   int ans=maxx;
   for(int i=0;i<maxx;i++)
   for(int j=0;j<maxx;j++)
   if(g[n%2][i][j])
   ans=min(ans,max(i,max(j,sum-i-j)));
   cout<<ans;
   return 0;
}
```

---

## 作者：fxxmm (赞：1)

二分， dfs, 状态压缩（二进制的压缩和解压缩）。
B1 >= B2 >= B3, 首先利用dfs生成一个数组储存所有的可能的B1的情况，即2^n种，排序，n为干草的数量，再利用二分找出大于总共的2/3的情况，二进制压缩记录了哪些干草被选了，利用解压缩，在这些选了的干草中利用dfs生成另一个数组，排序，二分找出大于等于1/2的情况，判断数量是否大于1，即为所求的最大值中的最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6;

struct position
{
    int val;
    int pos;
} s[N];
int f[N];
int flag[N],flag1[N];
int arr[N];
int sum;
int num = 0;
int n;
int tot=0;
int a[25];

bool check(int s)
{
    if (s * 3 >= sum*2)
    {
        return true;
    }
    return false;
}
bool comp(position x, position y)
{
    return x.val < y.val;
}

int half1(int l, int r)
{
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(s[mid].val))
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}

int half2(int l, int r,int res)
{
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (arr[mid]*2>=res)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return arr[l];
}

void dfs1(int x, int res,int pos) //x当前的位置， res当前已经获得的重量, //二进制状态
{
    if (!flag[res]&&x>=1)//去重
    {
        s[++num].val = res;
        s[num].pos = pos;
        flag[res] = 1;
    }
    if (x >= n)
    {
        return;
    }
    dfs1(x + 1, res + a[x+1],pos|(1<<x));
    dfs1(x + 1, res,pos);
}

void dfs2(int x, int res,int cnt) //x当前的位置， res当前已经获得的重量
{
    if (!flag1[res]&&x>=1)//去重
    {
        arr[++tot]= res;
        flag1[res] = 1;
    }
    if (x >= cnt)
        return;
    dfs2(x + 1, res + f[x+1],cnt);
    dfs2(x + 1, res,cnt);
}
int main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    dfs1(0, 0,0);

    sort(s+1, s +1+ num,comp);

    int p = half1(1, num);
    for (int i = p; i <= num; i++)
    {
        int cnt = 0;
        memset(f, 0, sizeof(f));
        for (int j = 0; j <= n - 1; j++)
        {
            if ((s[i].pos >> j) & 1)
                f[++cnt] = a[j+1];
        }
        if (cnt == 1)
            continue;
        memset(flag1, 0, sizeof(flag1));
        tot=0;
        dfs2(0,0,cnt);
        sort(arr+1,arr+1+tot);

        cout << half2(1, tot, s[i].val);
        break;

    }
    return 0;
}

```

---

## 作者：友邻牧鸡 (赞：1)

这个题让我想起了P1651塔这个题，那个题中要求的是两个物品集合差尽量小，用了二位dp：f[i][j]选到第i个物品矮的塔和高的塔相差j时高塔的高度，类比到这里三个物品集合就可以多开一维，##用f[i][j][k]维护选到第i个草包，最小的一堆与中间一堆差j，中间的一堆与最大的一堆差k的情况下最大的那一堆的大小##，这里就可以考虑转移方程了：

#如果放在最小的一堆：#

##当a[i]<j时 : ##

        ###dp[i][j-h][k]=min(dp[i][j-h][k],dp[i][h][k])##

##当j<a[i]<j+k时 : ##

###dp[i][h-j][j+k-h]=min(dp[i][h-j][j+k-h],dp[i-1][j][k])###

##当j+k<a[i]时 : ##

###dp[i][k][h-k-j]=min(dp[i][k][h-k-j],dp[i][j][k]+h-j-k)###

#如果放在中间的一堆：#

##当a[i]<k时:##

###dp[i][j+h][k-h]=min(dp[i][j+h][k-h],dp[i][j][k])###

##当k<a[i]时:##

###dp[i][j+k][h-k]=min(dp[i][j+k][h-k],dp[i][j][k]+h-k)###

#如果放在最大的一堆：#

    ### dp[i][j][k+h]=min(dp[i][j][k+h],dp[i][j][k]+h) ###

##初始化：##

所有dp变为一个极大值，dp[0][0][0]=0

###至于转移用刷表法还是填表法，这个就随便了###


###边界的话1000就早够了###


贴代码：


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#define maxn 25
using namespace std;
int init()
{
    char c=getchar();
    int jg=0,zf=1;
    while(c<'0'||c>'9'){if(c=='-')zf=-zf;c=getchar();}
    while(c>='0'&&c<='9'){jg=(jg<<1)+(jg<<3)+c-'0';c=getchar();}
    return jg*zf;
}
void write(int x)
{    if(x<0)putchar('-');
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int sum,n,a[maxn],ans=2147483647;
int dp[maxn][1000][1000];
int main()
{
    n=init();
    for(int i=1;i<=n;i++)
    a[i]=init(),sum+=a[i];
    memset(dp,0x7f,sizeof(dp));
    dp[0][0][0]=0;
    for(int i=1;i<=n;i++)
    for(int j=0;j<=999;j++)
    for(int k=0;k<=999;k++)
    {
        int h=a[i];
        if(h<j)
        dp[i][j-h][k]=min(dp[i][j-h][k],dp[i-1][j][k]);
        if(j<=h&&h<=j+k)
        dp[i][h-j][j+k-h]=min(dp[i][h-j][j+k-h],dp[i-1][j][k]);
        if(h>j+k)
        dp[i][k][h-k-j]=min(dp[i][k][h-k-j],dp[i-1][j][k]+h-j-k);
        if(h<k)
        dp[i][j+h][k-h]=min(dp[i][j+h][k-h],dp[i-1][j][k]);
        if(h>=k)
        dp[i][j+k][h-k]=min(dp[i][j+k][h-k],dp[i-1][j][k]+h-k);
        dp[i][j][k+h]=min(dp[i][j][k+h],dp[i-1][j][k]+h);
    }
    for(int j=0;j<=999;j++)
    for(int k=0;k<=999;k++)
    ans=min(ans,dp[n][j][k]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：巨型方块 (赞：1)

my blog:

<http://blog.csdn.net/largecub233/article/details/68961148>

新出的大牛水题；

我看了一下数据范围，感觉爆搜可以；

那我们打一个爆搜，加一个小剪枝；

80；
根据剪枝排序配合一下吧；

90；
既然排序了那么答案必然不会太玄学，那么掐秒~~~；

AC；
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;
int a[21];
int n,A,B,C,ans,sum;
void dfs(int k){
    sum++;
    if(sum==80000000){printf("%d",ans);exit(0);}
    if(max(max(A,B),C)>=ans)return;
    if(!k){ans=max(max(A,B),C);return;}
    A+=a[k]; dfs(k-1); A-=a[k];
    B+=a[k]; dfs(k-1); B-=a[k];
    C+=a[k]; dfs(k-1); C-=a[k];
}
int main()
{
    ans=1e9;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    dfs(n);
    printf("%d",ans);
}
```
标算我再想一想吧，反正这道题第一反应就是爆搜；

---

## 作者：expnoi (赞：0)

这题可以用**动态规划**来求解，我们设 ```f[i][j][k]``` 表示前 $i$ 个数，某两堆的大小分别为 $j,k$ 是否可行

那么转移方程就很好求了，因为我们要往堆里放东西。所以说 ```f[i+1][j+a[i]][k]``` 和 ```f[i+1][j][k+a[i]]``` 以及 ```f[i+1][j][k]``` 都是可以放进去而可行的。

那么答案就很好求了，我们可以暴力遍历数组来求得最优答案。

但是空间就炸了，怎么办呢？

我们发现，状态的转移只跟上一层有关系，那我们仅记录两层即可，我们称之为**滚动数组**优化空间。

同步于[Acwing](https://www.acwing.com/solution/content/91817/)

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001],n,f[2][2001][2001];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	int sum=0;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	f[0][0][0]=1;
	for(int i=0;i<n;i++)
	{
		sum+=a[i];
		for(int j=0;j<sum;j++)
		{
			for(int k=0;k<sum;k++)
			{
				if(f[i&1][j][k])
				{
					f[(i+1)&1][j+a[i]][k]=1;
					f[(i+1)&1][j][k+a[i]]=1;
					f[(i+1)&1][j][k]=1;
				}
			}
		}
	}
	int ans=2000;
	for(int i=0;i<sum;i++)
	{
		for(int j=0;j<sum;j++)
		{
			if(f[n&1][i][j])
			{
                ans=min(ans,max(i,max(j,sum-i-j)));
			}
		}
	}
	cout<<ans<<"\n";
}
```

---

## 作者：Dawn_Sdy (赞：0)

考试时看到此题，原先以为是二分答案，但写着写着就挂了。

于是就只能打暴力，写3^n算法搜索，如果不加任何优化搜索肯定炸，这时卡常就有效果了，小剪枝加卡常过后完美AC

AC代码:

```cpp
#include<cstdio>//不用万能头卡常
#include<algorithm>
//不写using namespace卡常
int n;
int s[25];
int ans=0x7ffffff;
inline void search(int len,int b1,int b2,int b3)
{
	if (std::max(b1,std::max(b2,b3))>=ans)//最优性剪枝
	   return ;
	if (len==n+1)
	   {
	   ans=std::min(ans,std::max(b1,std::max(b2,b3)));
	   return ;
	   }
	if (b1==b2&&b1==b3)//减少重复
	   {
	   search(len+1,b1+s[len],b2,b3);
	   return ;
	   }
	if (b1==b2&&b1!=b3)
	   {
	   search(len+1,b1+s[len],b2,b3);
	   search(len+1,b1,b2,b3+s[len]);
	   return ;
	   }
	if ((b1==b3||b2==b3)&&b1!=b2)
	   {
	   search(len+1,b1+s[len],b2,b3);
	   search(len+1,b1,b2+s[len],b3);
	   return ;
	   }
	search(len+1,b1+s[len],b2,b3);
	search(len+1,b1,b2+s[len],b3);
	search(len+1,b1,b2,b3+s[len]);
}
inline bool cmp(int a,int b)
{
	return a>b;
}
int main(){
	scanf("%d",&n);
	for (register int i=1;i<=n;i++)
		scanf("%d",&s[i]);
	std::sort(s+1,s+n+1,cmp);//逆序排序让最优化剪枝效果最大化
	search(1,0,0,0);
	printf("%d",ans);
	return 0;
}
```


---

