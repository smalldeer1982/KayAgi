# [USACO3.4] “破锣摇滚”乐队 Raucous Rockers

## 题目描述

你刚刚继承了流行的 “破锣摇滚” 乐队录制的尚未发表的 $N$（$1\leq N\leq 20$）首歌的版权。你打算从中精选一些歌曲，发行 $M$（$1\leq M\leq 20$）张 CD。每一张 CD 最多可以容纳 $T$（$1\leq T\leq 20$）分钟的音乐，一首歌不能分装在两张 CD 中。CD 数量可以用完，也可以不用完。

不巧你是一位古典音乐迷，不懂如何判定这些歌的艺术价值。于是你决定根据以下标准进行选择：

* 1.歌曲必须按照创作的时间顺序在所有的 CD 盘上出现。(注：第 $i$ 张盘的最后一首的创作时间要早于第 $i+1$ 张盘的第一首)

* 2.选中的歌曲数目尽可能地多。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.4


## 样例 #1

### 输入

```
4 5 2
4 3 4 2```

### 输出

```
3```

# 题解

## 作者：DayC (赞：44)

此题为一道二维费用背包题。(若是不规定“必须按照创作的时间顺序在所有的CD盘上出现”，就是一道排序水题)

与裸的二维费用不同，此题不同点在于状态转移方程。

此题的状态转移方程为：

```cpp
*F[m][t]=max{
    f[m][t]//不选当前歌曲
    f[m-1][T]+1//用一张新的CD来存当前歌曲（m张CD不够存的情况）
    f[m][t-time[i]]+1//一张CD放多首歌曲
}*
```
F[m][t]表示用m张CD，最后一张CD用t分钟所能存的最大歌曲数
time[i]表示第i首哥的时间


```cpp
    #include<iostream>
    #include<cstring>
    #include<iostream>
    #define maxn 21
    using namespace std;
    int N,T,M;
    int f[maxn][maxn];//用于保存状态
    int t[maxn];
    int max(int i,int j,int k){
        i=max(i,j);
        i=max(i,k);
        return i;
    }
    int main(){
        cin>>N>>T>>M;
        for(int i=1;i<=N;i++){
            cin>>t[i];
        }
        for(int i=0;i<=T;i++){//初始化数组
            f[0][i]=0;
        }
        for(int i=1;i<=N;i++){
            for(int m=M;m>=1;m--){//注意：因为是01背包，所以要从后往前更新状态
                for(int j=T;j>=t[i];j--){
                    f[m][j]=max(f[m][j],f[m-1][T]+1,f[m][j-t[i]]+1);//状态转移
                }
            }
        }
        cout<<f[M][T];
    }

```

---

## 作者：微香玉烛暗 (赞：23)

这道题看到大多数人都用$DP$，而$dfs$的几篇题解也相当麻烦，所以发一篇$dfs$题解。因为该题状态转移方程不容易推算，思维难度较高，$dfs$展现更加清晰明了，容易理解。

$dfs$函数中四个值含义先了解一下：               

$i$ :目前搜到的那首歌曲   
$now$ :目前这张碟片已经用的时间  
$s$ :目前用到第几张碟片                    
$sum$ :目前录入碟片的歌曲总数


代码：     
```cpp
# include <cstdio>
# include <iostream>
# include <algorithm>
using namespace std;
const int N=25;
int n,t,m,ans=-1e9,a[N];

void dfs (int i,int now,int s,int sum) {
	if (i>n||s>m) {//歌曲录完或碟片用完时
		ans=max(ans,sum);//更新ans及返回
		return ;
	}
	if (t-now>=a[i]) {//如果本张碟片剩余时间足够录下这首歌
		if (t-now>a[i])/*特判仍有时间*/ dfs (i+1,now+a[i],s,sum+1);//录入歌曲，不换碟片
		/*正好用完或仍有时间都可换碟片*/dfs (i+1,0,s+1,sum+1); //录入歌曲，换碟片
	}
	dfs (i+1,now,s,sum);//不录歌曲
}

int main () {
	scanf ("%d%d%d",&n,&t,&m);
	for (int i=1;i<=n;i++) 
		scanf ("%d",&a[i]);
	dfs (1,0,1,0);//初始
	printf ("%d\n",ans);
	return 0;//结束了
}
//By苍空的蓝耀

```
另外，若有错误，欢迎dl们在评论区指出，蟹蟹！

---

## 作者：Celebrate (赞：15)

这种题我还是比较喜欢用dp，搜索比较麻烦，dp会容易很多

这一道题其实不难，主要是看有没有找到dp的方式，而且这一题的dp不需要加其他算法优化

定义f[j][k]来记录在第j个光碟k内存最多能存多多少首歌

公式如下：
```cpp
f[j][k]=max(
f[j][k],//原封不动
max(f[j-1][t]+1,//多增加一张光碟
f[j][k-a[i]]+1//不增加光碟
));
```

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
int a[31],f[31][31];
int main()
{
	int i,j,k;
	scanf("%d%d%d",&n,&t,&m);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);//输入
	//不需要初始化了，因为在函数外面定义的数一开始都为0 
	for(i=1;i<=n;i++)//因为需要按照顺序，所以需要逐个找 
		for(j=m;j>=1;j--)//这个是01背包，不可以自己叠加自己的，所以只能从后往前 
			for(k=t;k>=a[i];k--)//和前面一样的道理，这一句和上一句换一下应该也没有问题，只是这样好解释一点 
				f[j][k]=max(f[j][k],max(f[j-1][t]+1,f[j][k-a[i]]+1));//刚刚说的dp公式 
	int maxx=0;//我不能保证f[m][t]就是最大值，所以我还是找一下吧 
	for(i=1;i<=m;i++) for(j=1;j<=t;j++) maxx=max(maxx,f[i][j]);
	printf("%d\n",maxx);//输出 
	return 0;
}
```

---

## 作者：Drifterming (赞：10)

/\*每一首歌都有三种状态。 1、在当前盘里装 2、换张盘装 3、不装    那我们对每首歌进行三种状态的dfs，选到最后找出最大值，且这样做第i张盘的最后一首歌一定比第i+1张盘的第一张早，因为dfs中的歌的编号是递增的\*/




```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath> 
using namespace std;
int n,m,t,ans=-1,tot=1;
int cd[25],tim[25];
void dfs(int now,int sum)    //now表示当前选到了第几首歌，sum表示选了几首歌 
{
    if(sum+n+1-now<=ans) return;    //重要剪枝，如果把后面的歌全装上也不能使答案更新，那么在往下一定不会有更优解，则return 
    if(now==n+1)    //歌选完了 
    {
        ans=max(ans,sum);
        return; 
    }
    if(cd[tot]>=tim[now])        //在当前盘里装 
    {
        cd[tot]-=tim[now];
        dfs(now+1,sum+1);
        cd[tot]+=tim[now];
    }
    if(tot<m&&t>=tim[now])        //换张盘装 
    {
        tot++;
        cd[tot]-=tim[now];
        dfs(now+1,sum+1);
        cd[tot]+=tim[now];
        tot--;
    }
    dfs(now+1,sum);        //不装 
}
int main()
{
    scanf("%d%d%d",&n,&t,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&tim[i]);
    }
    for(int i=1;i<=m;i++)
    {
        cd[i]=t;
    }
    dfs(1,0);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：The_Stardust (赞：6)

提供一种不太一样的dp思路，时间复杂度O(n*n)，空间可以用滚动数组优化一下，效率较高

用dp[i][j]表示前i首曲子中选j首所用的最少CD片个数，

g[i][j]表示满足dp[i][j]的情况下最后一个CD片的使用时间大小

那么从dp[i-1][j]可以更新到dp[i][j]和dp[i][j+1]，分别为不选和选

转移的时候根据当前CD片能不能装下当前歌曲要分类讨论，剩下的细节看代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,m;
int a[25];
int dp[25][25],g[25][25];
int main()
{
	scanf("%d%d%d",&n,&t,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	memset(dp,0x3f,sizeof(dp));
	memset(g,0x3f,sizeof(g));
	g[0][0]=0;
	dp[0][0]=1;
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<i;++j)
		{
			if(dp[i-1][j]==dp[i][j])
			{
				if(g[i-1][j]<g[i][j]) g[i][j]=g[i-1][j];//最后一个CD剩余容量更大，转移
			}
			if(dp[i-1][j]<dp[i][j])//使用CD片更少，转移
			{
				dp[i][j]=dp[i-1][j];
				g[i][j]=g[i-1][j];
			}//不选
			if(a[i]>t) continue;//细节判一下歌曲是否大于CD最大容量
			if(g[i-1][j]+a[i]>t)
			{
				if(dp[i-1][j]+1==dp[i][j+1])
				{
					if(a[i]<g[i][j+1]) g[i][j+1]=a[i];
				}
				if(dp[i-1][j]+1<dp[i][j+1])
				{
					dp[i][j+1]=dp[i-1][j]+1;
					g[i][j+1]=a[i];
				}
			}
			else
			{
				if(dp[i-1][j]==dp[i][j+1])
				{
					if(g[i-1][j]+a[i]<g[i][j+1]) g[i][j+1]=g[i-1][j]+a[i];
				}
				if(dp[i-1][j]<dp[i][j+1])
				{
					dp[i][j+1]=dp[i-1][j];
					g[i][j+1]=g[i-1][j]+a[i];
				}
			}//选，分类讨论
		}
	}
	for(int i=n;i>=0;--i)//从大到小扫
	{
		if(dp[n][i]<=m)//如果使用CD片个数符合要求
		{
			printf("%d",i);//输出
			return 0;
		}
	}
	return 0;
}
```

然后发现i只从i-1转移过来，可以滚动数组，小套路
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,m;
int a[21];
int dp[2][21],g[2][21];
int op;
int fop=1;//滚动的核心
inline int read()
{
	int a=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		a=(a<<1)+(a<<3)+ch-48;
		ch=getchar();
	}
	return a;
}
int main()
{
	n=read(),t=read(),m=read();
	for(int i=1;i<=n;++i) a[i]=read();
	memset(dp,0x3f,sizeof(dp));
	memset(g,0x3f,sizeof(g));
	g[0][0]=0;
	dp[0][0]=1;
	for(int i=1;i<=n;++i)
	{
		op^=1;
		fop^=1;
		for(int j=0;j<i;++j)
		{
			if(dp[fop][j]==dp[op][j])
			{
				if(g[fop][j]<g[op][j]) g[op][j]=g[fop][j];
			}
			else if(dp[fop][j]<dp[op][j])
			{
				dp[op][j]=dp[fop][j];
				g[op][j]=g[fop][j];
			}
			if(a[i]>t) continue;
			if(g[fop][j]+a[i]>t)
			{
				if(dp[fop][j]+1==dp[op][j+1])
				{
					if(a[i]<g[op][j+1]) g[op][j+1]=a[i];
				}
				else if(dp[fop][j]+1<dp[op][j+1])
				{
					dp[op][j+1]=dp[fop][j]+1;
					g[op][j+1]=a[i];
				}
			}
			else
			{
				if(dp[fop][j]==dp[op][j+1])
				{
					if(g[fop][j]+a[i]<g[op][j+1]) g[op][j+1]=g[fop][j]+a[i];
				}
				else if(dp[fop][j]<dp[op][j+1])
				{
					dp[op][j+1]=dp[fop][j];
					g[op][j+1]=g[fop][j]+a[i];
				}
			}
		}
	}
	for(int i=n;i>=0;--i)
	{
		if(dp[op][i]<=m)
		{
			printf("%d",i);
			return 0;
		}
	}
	return 0;
}
```
学会了可以去做[机器人小Q](https://www.luogu.com.cn/problem/P1687)
，双倍经验

---

## 作者：Bzy_temp (赞：6)



```cpp
###//成功把它压成了1维DP
//表示作为蒟蒻的我已经非常开心了.
#include<bits/stdc++.h>//万能头文件
using namespace std;//流操作命名空间
int song[25];int dp[450];//存储//DP
int main(){
    int a,b,c;cin>>a>>b>>c;int mx=0;//输入//赋值
    for(int i=1;i<=a;i++)cin>>song[i];//输入
    for(int i=1;i<=a;i++){
        if(song[i]>b)continue;//判断是否大于CD//大于就Continue
        for(int j=c-1;j>=0;j--){
            for(int k=0;k<=b;k++){
                        if(song[i]<=k) dp[j*(b+1)+k-song[i]]=max(dp[j*(b+1)+k-song[i]],dp[j*(b+1)+k]+1);
                           else dp[(j+1)*(b+1)+b-song[i]]=max(dp[(j+1)*(b+1)+b-song[i]],dp[j*(b+1)+k]+1);//分类讨论DP
            }
        }
    }
    for(int i=0;i<=b*c;i++)if(dp[i]>mx)mx=dp[i];//求最大值
    cout<<mx;//输出
}
```

---

## 作者：Eismcs (赞：5)

惊奇于数据范围之小，让我奇特的DP也能水过。五重循环都50ms过了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int a[25],f[25][25][25],ss;
//f[i][j][k]表示第i个CD，现在取到了第j首歌，此CD已存k分钟的歌了。
int main(){
	int n=read(),t=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<m;i++){
    //枚举CD
		for(int j=1;j<=n;j++){
        //枚举所选的歌
			for(int k=0;k+a[j]<=t;k++){
            //枚举此CD已经存了多少分钟
				for(int l=j-1;l>=0;l--){
                //枚举上一个CD取到了哪
					for(int c=0;c<=t;c++){
						f[i+1][j][k+a[j]]=max(f[i+1][j][k+a[j]],f[i][l][c]+1);
					}
                    //第一种情况，这个CD还没用过。
					f[i+1][j][k+a[j]]=max(f[i+1][j][k+a[j]],f[i+1][l][k]+1);
                    //第二种情况，这个CD已用了k分钟。
					ss=max(ss,f[i+1][j][k+a[j]]);
                    //时刻更新最大值。
				}
			}
		}
	}
	printf("%d\n",ss);//输出。
	return 0;
} 
```
然而，我们还是可以优化，可以变成四重循环
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int a[25],f[25][25][25],ss;
int main(){
	int n=read(),t=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<m;i++){
		for(int j=1;j<=n;j++){
			for(int l=j-1;l>=0;l--){
            //改变枚举顺序
				for(int c=0;c<=t;c++){
					f[i+1][j][a[j]]=max(f[i+1][j][a[j]],f[i][l][c]+1);
				}
                //当此CD没用过时，当然没存歌，当作用了零分钟即可。
				for(int k=0;k+a[j]<=t;k++){
					f[i+1][j][k+a[j]]=max(f[i+1][j][k+a[j]],f[i+1][l][k]+1);
					ss=max(ss,f[i+1][j][k+a[j]]);
				}
			}
		}
	}
	printf("%d\n",ss);
	return 0;
} 
```
虽然还比不上二维费用背包快，但这种DP也能锻炼思维罢

---

## 作者：Dawn_Sdy (赞：3)

此题其实是可以做到$O( n^2)$的QAQ


看到有很多巨佬用的都是3重循环，那我就发个不一样的好了



------------


不难看出，这是一道线性动态规划问题

设每首歌的长度为$len[i]$

### 方法1：

设 $f[i][j][k]$ 为前$i$首歌曲用$j$张唱片另加$k$分钟所选的最多歌曲数

易得方程

当k>=len[i]时：

$g[i][j][k]=max(g[i-1][j][k-len[i]]+1,g[i-1][j][k])$

当k< len[i]时

$g[i][j][k]=max(g[i-1][j-1][t-len[i]]+1,g[i-1][j][k])$

边界：

$f[0][j][k]=0$

Anser：$f[n][m][0]$

时间复杂度$O(n*m*t)$

即$O(10^3* 10^6*10^6)$

显然会超时

采取降维的方式优化，改变状态描述

### 方法2：

令$f[i][j]=(a,b)$为前$i$首歌中选$j$首个的最小的唱片为：$a$张唱片再加$b$分钟

易得状态转移方程:

$f[i][j]=min(f[i-1][j],f[i-1][j-1]+len[i])$

对于取$f[i-1][j-1]+len[i]$时的更新方式：

$f[i][j].a=(f[i-1][j-1].b+len[i]>t?f[i-1][j-1].a+1:f[i-1][j-1].a);$

$f[i][j].b=(f[i-1][j-1].b+len[i]>t?len[i]:f[i-1][j-1].b+len[i]);$

时间复杂度：$O(n^2)$
可过！



------------
放AC代码：

```cpp
#include<bits/stdc++.h>
#define INF 0x7ffffff
using namespace std;
int ans;
int len[1005];
struct node{
	int a,b;
}f[1005][1005];
bool check(int a1,int a2,int b1,int b2)
{
	if (a1!=a2)
		return (a1<a2?1:0);
	else
		return (b1<b2?1:0); 
}
int main(){
	int n,m,t;
	cin>>n>>t>>m;
	for (int i=1;i<=n;i++)
		cin>>len[i];
	for (int i=0;i<=n;i++)
		for (int j=0;j<=n;j++)
			f[i][j].a=f[i][j].b=INF;
	for (int i=0;i<=n;i++)
		f[i][0].a=f[i][0].b=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=i;j++)
			{
			int a1,a2,b1,b2;
			a1=f[i-1][j].a;
		  a2=(f[i-1][j-1].b+len[i]>t?f[i-1][j-1].a+1:f[i-1][j-1].a);
			b1=f[i-1][j].b;
			b2=(f[i-1][j-1].b+len[i]>t?len[i]:f[i-1][j-1].b+len[i]);
			if (check(a1,a2,b1,b2))
	 		   {
	 		   f[i][j].a=a1;
			   f[i][j].b=b1;	
			   }
			else
			   {
			   f[i][j].a=a2;
			   f[i][j].b=b2;
			   }
			}
	for (int i=1;i<=n;i++)
		if (f[n][i].a<m&&f[n][i].b<=t)
			ans=max(ans,i);
	cout<<ans<<endl;
	return 0;
}
```

搞定，完美

---

## 作者：_l_l_ (赞：2)

这道题我们使用 DP。

定义 $dp_{i,j,k}$ 代表已经选到第 $i$ 个唱片，用了 $j$ 个唱片，第 $j$ 个唱片剩余 $k$ 分钟。

那么我们可以新开一个唱片，也可以继续填充唱片，甚至可以不选，即：

$$
dp_{i,j,k}=\max\{dp_{i-1,j,k},dp_{i-1,j-1,t}+1,dp_{i-1,j,k-a_i}\}
$$

优化：可以使用滚动数组优化 DP，如果不懂可以去看 P1048 的第一篇题解，写得很详细。

[https://www.luogu.com.cn/problem/solution/P1048](https://www.luogu.com.cn/problem/solution/P1048)

代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 21;
int f[MAXN][MAXN];
int a[MAXN];
int main() {
	int n, t, m;
    scanf("%d %d %d", &n, &t, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            for (int k = t; k >= a[i]; k--) {
                f[j][k] = max(max(f[j][k], f[j - 1][t] + 1), f[j][k - a[i]] + 1);
            }
        }
    }
    printf("%d", f[m][t]);
    return 0;
}
```

---

## 作者：前卫 (赞：2)

//EMMMMMM......changdu自然就是每首歌的长度啦OVO，f是dp数组，f[i][j]的值，就是在对第i张唱片进行决策，这张唱片还剩下j的空间,最    //多装下多少首歌

//至于转移呢，，，如果能装下，f[这张唱片][剩余空间减去这首歌长度]=放之后/放之前+1  两个找一个最大的

//不能装下，开一张新唱片，显然空间是t，f[这张唱片][剩余空间减去这首歌长度]=放之后/放之前+1 两个找一个最大的

```cpp
//最后在f[m][1..t]中找一个最大的即可
//ovo
#include<cstdio>
#include<algorithm>
using namespace std;
int i,j,k,n,t,m,ans,changdu[21],f[21][21];
int main()
{
    scanf("%d%d%d",&n,&t,&m);
    for(i=1;i<=n;i++)
      scanf("%d",&changdu[i]);
     for(i=1;i<=n;i++)
        for(j=m;j>=1;j--)//反过来是因为第二个方程用到j+1的状态
           for(k=0;k<=t;k++)
           {
                if(changdu[i]<=k) 
                  f[j][k-changdu[i]]=max(f[j][k-changdu[i]],f[j][k]+1);  
                else
                  f[j+1][t-changdu[i]]=max(f[j+1][t-changdu[i]],f[j][k]+1);
           }
    ans=-1000000;
    for(i=0;i<=t;i++)
      ans=max(ans,f[m][i]);
    printf("%d",ans); 
    return 0;
}
```

---

## 作者：zht467 (赞：1)

f[i][j]表示前i首歌放到前j个盘里最多能放多首

ntr[i][j]表示i~j中最多能放进一张盘中多少首歌 

ntr数组可以贪心预处理出来。






```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#define N 21 
#define max(x, y) ((x) > (y) ? (x) : (y))
int n, t, m;
int a[N], b[N], ntr[N][N], f[N][N];
//f[i][j]表示前i首歌放到前j个盘里最多能放多首 
//ntr[i][j]表示i~j中最多能放进一张盘中多少首歌 
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + ch - '0';
    return x * f;
}
inline void init()
{
    int i, j, k, sum, cnt;
    for(i = 1; i <= n; i++)
        for(j = i; j <= n; j++)
        {
            sum = cnt = 0;
            for(k = i; k <= j; k++) b[k] = a[k];
            std::sort(b + i, b + j + 1);
            for(k = i; k <= j; k++)
                if(sum + b[k] <= t)
                {
                    cnt++;
                    sum += b[k];
                }
            ntr[i][j] = cnt;
        }
}
int main()
{
    int i, j, k;
    n = read();
    t = read();
    m = read();
    for(i = 1; i <= n; i++) a[i] = read();
    init();
    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++)
            for(k = 0; k < i; k++)
                f[i][j] = max(f[i][j], f[k][j - 1] + ntr[k + 1][i]);
    printf("%d\n", f[n][m]);
    return 0;
}
```

---

## 作者：Snitro (赞：1)

dp写法


[http://blog.csdn.net/fine\_rose/article/details/72628529](http://blog.csdn.net/fine\_rose/article/details/72628529)


维护一个二维数组f[i][j],表示在只使用前 i 首歌，总耗时 j 的情况下能够达到的最大的乐曲数目。那么最后只需要将 f[n][t \* m] 输出即可(n 表示乐曲总数， t 表示每张唱片的时间， m 表示唱片的个数)


由于同一首歌不能将其从中间分开后放在两个唱片内，因此 f[i][j] 的计算需要考虑以下三种情况：


当不将第 i 首歌放入唱片时 f[i][j] = f[i - 1][j]


当将第 i 首歌放入唱片时需要考虑以下两种情况：


由于每张唱片的时间为 t ，那么通过计算可以得出 j % t 表示的是总时间 j 对应的最后一张不完整的唱片的时间。j / t 表示从时间 j 所包含的完整唱片的个数。


如果第 i 首歌的时间大于 j % t ，说明第 i 首歌可以完整的放入最后一张不完整的唱片，此时 f[i][j] = f[i - 1][j - song[i]] + 1 (song[i] 表示第 i 首歌的时长，下同。)


如果第 i 首歌的时间小于 j % t ，说明第 i 首歌由于时长过长而无法放入最后一张不完整的唱片，因此可以将其放入最后一张 完整的 唱片。此时f[i][j] = f[i - 1[j / t \* t - song[i]] + 1


因此总结出状态转移方程：


当jmodt≥song[i]时



f[i][j]=max(f[i−1][j],f[i−1][j−song[i]]+1)

当jmodt<song[i] 且 j÷t⋅t−song[i]≥0时




f[i][j]=max(f[i−1][j],f[i−1][j÷t⋅t−song[i]]+1)

源代码


二维数组



```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,t,m;//n首歌   每一张 t 分钟    m 张cd 
int f[25][405];
int song[25];
int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    cin >> n >> t >> m;
    for(int i = 1;i <= n;i++)
        cin >> song[i];
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= t * m;j++){
            f[i][j] = f[i - 1][j];
            if(j % t >= song[i])
                f[i][j] = max(f[i][j],f[i - 1][j - song[i]] + 1);
            else if (j / t * t - song[i] >= 0)
                f[i][j] = max(f[i][j],f[i - 1][j / t * t - song[i]] + 1);
        }
    }
    cout << f[n][t * m];
    return 0;
}
```
一维滚动数组

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,t,m;//n首歌   每一张 t 分钟    m 张cd 
int f[405];
int song[25];
int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    cin >> n >> t >> m;
    for(int i = 1;i <= n;i++)
        cin >> song[i];
    for(int i = 1;i <= n;i++) {
        for(int j = t * m;j >= 1;j--){
            f[j] = f[j];
            if(j % t >= song[i])
                f[j] = max(f[j],f[j - song[i]] + 1);
            else if (j / t * t - song[i] >= 0)
                f[j] = max(f[j],f[j / t * t - song[i]] + 1);
        }
    }
    cout << f[t * m];
    return 0;
}
```

---

## 作者：_Rainlzy (赞：0)

从此题来看明显是dp（~~当然看标签也是可以的~~），二维费用背包题，许多人也讲到了。

那么什么是二维背包应用题呢？

> 二维费用的背包问题指的是对于每件物品，具有两种不同的费用。选择某件物品必须付出两种代价；对于每种代价都有一个可付出的最大值,并问你怎样选择物品可以得到最大的价值。

既然是动规，我们就设 $f[i][j]$ 为第 $i$ 个光盘在前 $j$ 分钟最多能选的歌曲数量。

那么就会出现情况：

- 用新的CD卡存
- 还是用这张CD卡
- 不选

那么我的转移方程式式

$$f[j][k]=max(f[j][k],max(f[j-1][t]+1,f[j][k-a[i]]+1));$$

而且不需要初始化数组也能过掉这题。

```
#include<bits/stdc++.h>
using namespace std;
int n,t,m,a[25],f[25][25];
int main(){
    cin>>n>>t>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
            for(int k=t;k>=a[i];k--)//三重循环
               f[j][k]=max(f[j][k],max(f[j-1][t]+1,f[j][k-a[i]]+1));//状态转移方程
    cout<<f[m][t]<<endl;	
    return 0;
}
```

---

## 作者：LRL65 (赞：0)

一道比较简单的dp（背包）

 $f[i][j]$ 的意思为**第i个光盘前j分钟最多可选的歌曲**。
 
那么我们来分析一下，应该共有3种情况：

1. 不选这首歌
1. 用一张新的CD存
1. 继续用这一张CD存

所以状态转移方程为：

$f[i][j]=max(max(f[i][j],f[i-1][t]),f[i][j-a[k]])$

（其中$a_k$为歌的时间）

还有一些细节在代码中体现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,a[25],f[25][25];
int main(){
    cin>>n>>t>>m;
    for(int i=1;i<=n;i++)cin>>a[i];//输入
    for(int i=1;i<=t;i++)f[0][i]=0;//初始化要清0
    for(int k=1;k<=n;k++) //第一层为第几首歌
        for(int i=m;i>=1;i--)//第二层要倒着
            for(int j=t;j>=a[k];j--)f[i][j]=max(max(f[i][j],f[i-1][t]+1),f[i][j-a[k]]+1);
    cout<<f[m][t]<<endl;//输出
}
```





---

## 作者：Ing1024 (赞：0)

机房老师给找的题，没想到是个绿题dp，于是写个题解吧。

那么对于每一首歌，我们有三种决策方案：

1.不管这首歌

2.将这首歌刻在现在已经用过的但有剩余的唱片上

3.用一张新唱片去刻录这首歌

那这样就很清晰了，设dp[i][j][k]为前i首歌，用j张唱片，且该唱片可以用k分钟。

则有dp[i][j][k]=max

{

	dp[i-1][j][k] 不管这首歌
    
   	(k>=a[i])dp[i-1][j][k-a[i]]+1 刻在用过唱片上
    
    (k>=a[i])dp[i-1][j-1][t]+1 用一张新唱片去刻录这首歌(注意这里要从上一张唱片的最大歌曲数转移，也就是k=t)
}

其实这样我们就可以AC了，但是根据上面的分析我们发现这是个01背包，所以去考虑降维！（三维to二维）

将第一维去掉，因为我们发现转移方程都是第一维都是i-1，所以我们可以倒着dp，只保存最近的两个状态。

贴一下降维代码
```cpp
#include<iostream>
using namespace std;
int n,m,t,a[21],dp[21][21];
int main()
{
	cin>>n>>t>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	for(int j=m;j>=1;j--)
	for(int k=t;k>=a[i];k--)//dp[j][k]表示j张唱片，第j张唱片用了至多k分钟所可以录下的最大歌曲数目 
	dp[j][k]=max(dp[j][k-a[i]]+1,dp[j-1][t]+1); 
	cout<<dp[m][t]<<endl;
	return 0;
}
```



---

## 作者：Y_B_Y (赞：0)

看到n<=20,脑海中想了一下2$^2$$^0$的大小,选择了dfs

### 一.主要做法

#### 1.一首歌**存**或**不存**

- 存:先判断现在在用的光盘是否够用,够用就将剩余容量减去这首歌的大小,不够就判断用一张新的光盘够不够,够就存进去,不够就说明这首歌只能不存(新的都不够就没有更大的了)

- 不存:到下一首歌

#### 2.判断超界与结束


- 超界  if(num>m) return;

- 结束 now==n+1 //now表示现在是第几首歌

### 二.开始dfs
直接上代码吧

```cpp
void dfs(int now,int num,int tot,int ans)//now表示现在是第几首歌,num表示正在用第几张光盘,tot表示这张光盘已经用了多少,ans表示存了多少歌
{
	if(num>m) return;//超过可以使用的光盘数
	if(now==n+1)//所有歌都搜索了一遍,结束
	{
		maxn=max(maxn,ans);//取最大值
		return;
	}
	dfs(now+1,num,tot,ans);//不选
	if(tot+a[now]<=t) dfs(now+1,num,tot+a[now],ans+1);//如果这一张光盘容量够,存进去
	else//不够
	{
		if(a[now]<=t)dfs(now+1,num+1,a[now],ans+1);一定要判断下一张光盘够不够
	}
	return;
}
```

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,m,a[21],maxn;//n为歌的个数,t为光盘容量,m为光盘数,a[i]表示第i首歌的大小,maxn为搜到的结果的最大值
void dfs(int now,int num,int tot,int ans)//搜索,前面讲过了,void表示这个函数无数据类型
{
	if(num>m) return;
	if(now==n+1)
	{
		maxn=max(maxn,ans);
		return;
	}
	dfs(now+1,num,tot,ans);
	if(tot+a[now]<=t) dfs(now+1,num,tot+a[now],ans+1);
	else
	{
		if(a[now]<=t)dfs(now+1,num+1,a[now],ans+1);
	}
	return;
}
int main()
{
	cin>>n>>t>>m;//输入
	for(int p=1;p<=n;p++) cin>>a[p];//输入
    dfs(1,1,0,0);//搜索
	cout<<maxn;//输出
    return 0;
} 
```



---

## 作者：ghj1222 (赞：0)

```
#include <bits/stdc++.h>
using namespace std;

int N, T, M, ans, a[30];

void search(int song, int disk, int used, int tot)
{
	if (disk > M && used > 0)
		return;
	if (disk == M + 1 || song == N + 1)
	{
		ans = max(ans, tot);
		return;
	}
	search(song + 1, disk, used, tot);
	if (T - used > a[song])
		search(song + 1, disk, used + a[song], tot + 1);
	else if (T - used == a[song])
		search(song + 1, disk + 1, 0, tot + 1);
	else if (T - used < a[song])
	{
		if (a[song] < T)
			search(song + 1, disk + 1, a[song], tot + 1);
		else if (a[song] == T && disk != M)
			search(song + 1, disk + 2, 0, tot + 1);
	}
}

int main()
{
	scanf("%d%d%d", &N, &T, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &a[i]);
	search(1, 1, 0, 0);
	printf("%d\n", ans);
	return 0;
}
/*
数据范围贼TM小直接搜过
search(song, disk, used, tot)表示当前正在抉择第song首歌是否被刻录，
已经刻录了disk张光盘
第disk张光盘用了used分钟
已经刻录了tot首歌

两种转移，刻录或不刻录
不刻录，要考虑是新撵一张，还是刚好刻满一张再撵一张，还是这张还没刻满
根据贪心，如果这张还能刻这个乐曲我们绝对不把乐曲刻在下一张
另外还判一下乐曲时间是否和光盘容量相等

最后统计答案的时候，如果M张光盘满了或者N首歌搜完了直接更新就行
另外还有就是如果M张光盘都满了，你还刻了M+1张就不合法了
*/
```

---

## 作者：GNAQ (赞：0)

楼下神犇太厉害了……一维（不过貌似复杂度还是O(NMT)


###既然有了这么多题解，而且几乎都有代码，那么我就只讲一发思路吧 ……而且毕竟抄代码还不如不做，白白浪费好题



我们设f[n][m][k]表示前n首歌按顺序尽量向m张盘里装，然后附加k分钟所能装的最多歌曲数。那么，显然k<=T，因为……如果k>T那f[i][j][k]等价于f[i][j+1][k-T]，所以k>T是没有意义的

我们来考虑第n首歌装到第m+1张盘里的决策，也就是转移f[n][m][k] （因为m张盘外加k分钟，如果用那k分钟，也就是向m+1张里面装）


先初始化一下，也就是尝试放弃第i首歌

```cpp
 f[i][j][k]=max(f[i][j][k],f[i-1][j][k]);
```

如果第j+1张盘的前k分钟能装的下，

```cpp
if (k>=a[i]) f[i][j][k]=max(f[i][j][k],f[i-1][j][k-a[i]]+1);
```
那就不装，或者用前j张和j+1张的前k-a[i]分钟装前i-1首，第j+1张的最后a[i]分钟（歌曲的长度）装第i首,这两个里面取max


如果第j+1张盘的前k分钟装不下，

```cpp
else if (j>=1 && t-a[i]>=0) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][t-a[i]]+1);
```
那么，假如说存在第j张盘（可以有j=0而k>0，也就是装第一张），那么就不装，或者用前j-1张盘外加第j张盘的T-a[i]分钟装前i-1首，用第j张盘装第i首试一下 （那么，就相当于尽量把第i首歌往j整张盘里装，如果a[i]小于T，那一定能装上，而如果T<a[i]了，那这首歌显然只能放弃）。

###我们为什么要有第二个方程？原因在于k不一定大于a[i]，而如果这首歌对决策有影响，那么T一定大于a[i]，所以有必要试着装一下。


---

## 作者：一念之间 (赞：0)

找一下规律：

样例：4 5 2

4 3 4 2

```cpp
num=1
f[i]=0 0 0 1 1 1 1 1 1 1
num=2
f[i]=0 0 1 1 1 1 1 2 2 2
num=3
f[i]=0 0 1 1 1 1 1 2 2 2
num=4
f[i]=0 1 1 1 2 2 2 2 2 3
```
可见有两个状态：
1.如果该状态将要存放的歌，为一张CD上，即 if(j-a[i]>=(cd-1)\*m)

2.如果该状态将要存放的歌，为两张CD上，即  if(j-a[i]<(cd-1)\*m&&(cd-1)\*m-(j-a[i])>=a[i])

满足这两项的合法状态，才可以 f[j]=max(f[j],f[j-a[i]]+1)

--------------------------------

代码比较辣鸡，很短：


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m,t,a[20000],cd;
int f[20000];//f[j]表示第j分钟最多有i首歌 
int main()
{
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    for(int i=1;i<=n;i++)
    { 
    for(int j=m*t;j>=1;j--)
    {  
      if(j%m==0)cd=j/m;
      else cd=j/m+1; //判断为第cd张唱片 
        if(j-a[i]>=(cd-1)*m)
        f[j]=max(f[j],f[j-a[i]]+1);
        if(j-a[i]<(cd-1)*m&&(cd-1)*m-(j-a[i])>=a[i])
        f[j]=max(f[j],f[j-a[i]]+1);//判断是否合法 
    }
    for(int j=1;j<=m*t;j++)
    f[j]=max(f[j],f[j-1]);//我比较辣鸡，上面有一点缺陷，这里再重新更新一下 
    }
    cout<<f[m*t];
}
```

---

## 作者：WilliHouse (赞：0)

这道题可以用dfs解是因为数据太水了，稍微大一点就得爆，正解是用DP。好像其他dalao都是用三维的，或f[i][j]


设f[j][k]表示第j张盘用k分钟最多能录入的歌曲数，由此得出状态转移方程


if（不能装） f[j+1][t-time[i]]=max(f[j+1][t-time[i]],f[j][k]+1);



else f[j][k-time[i]]=max(f[j][k-time[i]],f[j][k]+1); 

我们要求的是最多能录入的歌曲数，所以需要遍历比较最大值。


最大值为本题答案（新人题解，不喜勿喷）


上代码

```cpp
#include<stdio.h>
int max(int x,int y)//比较函数
{
    if(x>y) 
    return x;
    return y;
}
int time[21],f[21][21];
int main()
{
     int n,t,m;
     scanf("%d%d%d",&n,&t,&m);
     for(int i=1;i<=n;i++)
     scanf("%d",&time[i]);
     for(int i=1;i<=n;i++)//三重循环
        for(int j=m;j>=1;j--)
           for(int k=0;k<=t;k++)//注意从0开始
           {
                if(time[i]<=k) f[j][k-time[i]]=max(f[j][k-time[i]],f[j][k]+1);  //不装的情况
                else f[j+1][t-time[i]]=max(f[j+1][t-time[i]],f[j][k]+1);  //其他情况
           }
    int temp=-(1<<30);//赋很小的值给temp
    for(int i=0;i<=t;i++)
        if(f[m][i]>temp) temp=f[m][i];
    printf("%d",temp); //比较找出最大值
}

```

---

## 作者：CraZYali (赞：0)

# ~~我真的好久没写题解了~~


注意到数据范围：$$1 \le n \le 20$$


那么即使爆搜， 时间复杂度也只是$$O(2^n) \approx O (10^6)$$


----

但是如果是**简单的**dfs就完了， 那就~~没有意思~~AC了


所以我决定状态压缩一下2333


***重要代码***处有注释



 ![](https://cdn.luogu.com.cn/upload/pic/6211.png) 

~~虽说我的代码很差~~


----

```cpp
#define REP(i, s, e) for(register int i = s; i <= e ;i++)

#include<bits/stdc++.h>

using namespace std;
const int maxn = 100;

int m, n, k, ans;
int a[maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> n >> k >> m;
    int N = 0, K;
    REP(i, 1, n) {
        scanf("%d", &K);
        if (K <= k) a[++N] = K;//其实我是应为怕下面建出负数原地爆炸而已(逃
    }
    n = N;
    int _max = (1<<n)-1;
    REP(i, 1, _max) {
        int t = i, s = 1;
        int pos = 0, xuan = 0,  T = k;
      //pos    代表当前位置
      //xuan    代表已经选了多少歌
      //T 代表这张碟还剩多少空间
        while (t) {
            pos++;
            if (t & 1)
                if (T - a[pos] < 0)
                    if (s >= m) break;
          /*
          为什么这里可以直接break呢？
          因为对于 s >= m 的情况，后面的歌都可以不管了
          这就意味着，必然此时答案与之前一种最后选到当前选的碟的答案相同
          显然可以直接break
          */
                    else {    //在分一组
                        s++;
                        T = k - a[pos];
                        xuan++;
                        ans = max(ans, xuan);
                    }
                else {    //直接搞到碟里面去
                    T -= a[pos];
                    xuan++;
                    ans = max(ans, xuan);
                }
            t >>= 1;
        }
    }
    cout << ans; 
    return 0;
}
```

---

## 作者：罗旅洲 (赞：0)

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
int a[110],dp[111][111][111],ans;        //dp[i][j][k],i表示放第i首歌
                                        //j表示放入第j个CD,k表示CD剩下的时间
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
#endif
    int i,j,k,m,n,t; 
    scanf("%d%d%d",&n,&t,&m);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(i=1;i<=n;i++)
        for(j=m;j>=1;j--)                //当做01背包搞
            for(k=t;k>=a[i];k--){        //每首歌只能放一次，要倒着枚
                dp[i][j][k]=dp[i-1][j-1][t]+1;
                for(int u=0;u<i;u++)
                    if(dp[u][j][k-a[i]]+1>dp[i][j][k])
                        dp[i][j][k]=dp[u][j][k-a[i]]+1;        //把前面可以放入的放在这个盘里·
            }
    for(i=1;i<=n;i++)
        if(ans<dp[i][m][t])
            ans=dp[i][m][t];
    printf("%d",ans);
    return 0;
}

```

---

## 作者：约修亚_RK (赞：0)

我想说的是，裸的DFS并不会超时。

这题的 n <= 20，所以即便是暴力，也只有 2^20 种情况。搜索中，对于每首歌，选择放或者不放；放在当前光盘还是下一张光盘显然应当采取贪心策略，当前光盘放得下就放，放不下就放在下一张上。

边界条件是搜索完每一首歌。用一个ans来记录最大值。


```cpp
/* P2736
 * Au: SJoshua
 */
#include <cstdio>

int n, t, m, length[21], ans;

void dfs(int step = 0, int disk = 1, int left = t, int sel = 0) {
    if (step == n) {
        if (sel > ans) {
            ans = sel;
        }
        return;
    }
    if (length[step] <= t) { 
        if (length[step] <= left) { 
            dfs(step+1, disk, left-length[step], sel+1); 
        } else if (disk < m) {  
            dfs(step+1, disk+1, t-length[step], sel+1);  
        }
    }
    dfs(step+1, disk, left, sel);
}

int main(void) {
    scanf("%d %d %d", &n, &t, &m);
    for (int k = 0; k < n; k++) {
        scanf("%d", &length[k]);
    }
    dfs();
    printf("%d", ans);
    return 0;
}
```

---

## 作者：__stdcall (赞：0)

比较简单的搜索，直接DFS就可以，代码不长，思路在代码里面已经写得很清楚了


需要注意的是裸的DFS会超时，需要加一个IDA\*进行剪枝


剪枝的思路很简单：如果当前搜索到第i首歌，假如把后面的所有歌都选上（尽管不可能）还不能比当前最优解大的话，剪枝


代码如下：


···cpp





    


```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int n,m,t;
int a[30];
int rst = 0;
void dfs( int song , int cd , int time , int chosen )
{
    if( cd == m || song == n ) // 所有歌曲或者所有cd都用完了 
    {
        rst = max( rst , chosen );
        return;
    }
    if( chosen + n - song <= rst ) // IDA*
    {
        return;
    }
    if( time - a[song] >= 0 ) // 当前cd还能装得下这首歌 
    {
        dfs( song+1 , cd , time - a[song] , chosen+1 ); // 选择这首歌 
        dfs( song+1 , cd , time , chosen ); // 不选择这首歌 
    }
    else // 装不下这首歌 
    {
        dfs( song+1 , cd , time , chosen ); // 不选择这首歌 
        dfs( song , cd+1 , t , chosen ); // 换下一张cd 
    }
}
int main()
{
    //freopen( "rockers.in" , "r" , stdin );
    //freopen( "rockers.out" , "w" , stdout );
    cin >> n >> t >> m;
    for( int i = 0 ; i < n ; ++i )
    {
        cin >> a[i];
    }
    dfs( 0 , 0 , t , 0 );
    cout << rst << endl;
    return 0;
}
···
```

---

