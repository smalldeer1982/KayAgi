# Destroy it!

## 题目描述

你正在玩一款名为 Splay the Sire 的电脑卡牌游戏。目前你正在努力击败游戏的最终 Boss。

Boss 战共持续 $n$ 回合。在每一回合，你会获得若干张卡牌。每张卡牌有两个参数：其费用 $c_i$ 和伤害 $d_i$。在每一回合中，你可以选择以某种顺序打出若干张卡牌（你可以选择打出哪些卡牌以及它们的出牌顺序），但你在该回合中打出的卡牌的总费用不能超过 $3$。在打出若干（也可能为零）张卡牌后，你结束本回合，所有未打出的卡牌都会被弃掉。注意，每张卡牌最多只能使用一次。

你的角色还获得了一件神器，可以增强你的部分行动：你打出的每第 $10$ 张卡牌会造成双倍伤害。

在 $n$ 回合内，你最多能造成多少伤害？

## 说明/提示

在示例测试中，最优的行动方案如下：

第一回合，打出全部三张卡牌，顺序任意，共造成 $18$ 点伤害。

第二回合，打出两张卡牌，共造成 $7$ 点伤害。

第三回合，打出第一张和第三张卡牌，共造成 $13$ 点伤害。

第四回合，打出第一张和第三张卡牌，共造成 $25$ 点伤害。

第五回合，打出唯一的一张卡牌，该卡牌会造成双倍伤害（$200$）。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3
1 6
1 7
1 5
2
1 4
1 3
3
1 10
3 5
2 3
3
1 15
2 4
1 10
1
1 100
```

### 输出

```
263
```

# 题解

## 作者：xukuan (赞：3)

算法：线性动态规划

## dp成立的证明：

**重复子问题：**

对于第i次攻击，还有j轮触发暴击时，处理方案相同

**最优子结构：**

对于第i次攻击，还有j轮触发暴击时，可以通过之前的处理方式得到最优结构

**无后效性：**

对于第i次攻击，还有j轮触发暴击时，之前的取法的不同不会导致之后的取法发生变化

## 其他：

**如何转移和计算价值：**

由于限制了每次出手的总花费$\leq 3$，并且每张牌花费都为正，所以每次最多出三张。所以，只保留3张最大的1，1张最大的2和1张最大的3，枚举子集即可。枚举的时候可以先预处理各种方案的和，再用状态压缩的形式来方便计算。

转移的价值就是用的和，如果一次操作能够触发暴击，那么根据贪心可以知道，在当前的选项中放上价值最大的一个时最优的

**边界：** 没有坑，在此不再多讲

## 状态转移方程：

$f_{i,j}=f_{i-1,j-k}+v$

其中v表示转移后的价值

dp类题目，我就不放代码了，原因有2：
1. dp重在理解，理解之后代码一般都不难想
2. dp类题目是贺题党福利，不放代码也是为了防止贺题

---

## 作者：cmll02 (赞：2)

一道简单 dp。

状态 $dp_{i,j}$ 为第 $i$ 轮，离上一次暴击过了 $j$ 次攻击的最大值。

然后直接转移即可。

注意所有的情况都要转移，包括 $3,2+1,2,1+1+1,1+1,1$ 和啥都不选。

由于我比较懒，就写了个 $k\log k$ 的排序，事实上可以 $O(k)$ 做，但是细节比较多。

总复杂度 $O(Sn+k\log k)$，本题 $S=10$。

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <queue>
#define int long long
inline int read()
{
    int num=0,f=1;char c=getchar();
    while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
    while(c>47&&c<58)num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num*f;
}
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
int dp[200005][10];
int a[4][200005];
signed main()
{
    int T=read();
    //while(T--)
    //memset(dp,-0x3f,sizeof(dp));
    for(int i=0;i<=T;i++)for(int j=0;j<=9;j++)dp[i][j]=-0x3f3f3f3f3f3f3f3fll;
    dp[0][0]=0;
    for(int i=1;i<=T;i++)
    {
        int n=read();
            int c1=0,c2=0,c3=0;
            for(int i=0;i<n;i++)
            {
                int c=read(),d=read();
                if(c==1)a[1][c1++]=-d;
                if(c==2)a[2][c2++]=-d;
                if(c==3)a[3][c3++]=-d;
            }
            std::sort(a[1],a[1]+c1);
            std::sort(a[2],a[2]+c2);
            std::sort(a[3],a[3]+c3);
            for(int ii=0;ii<=9;ii++)dp[i][ii]=dp[i-1][ii];
            if(c3)
            {
                for(int j=0;j<9;j++)dp[i][j+1]=max(dp[i][j+1],dp[i-1][j]-a[3][0]);
                dp[i][0]=max(dp[i][0],dp[i-1][9]-2*a[3][0]);
            }
            if(c2&&c1)
            {
                for(int j=0;j<8;j++)dp[i][j+2]=max(dp[i][j+2],dp[i-1][j]-a[2][0]-a[1][0]);
                dp[i][0]=max(dp[i-1][8]-min(a[2][0],a[1][0])-a[2][0]-a[1][0],dp[i][0]);
                dp[i][1]=max(dp[i-1][9]-min(a[2][0],a[1][0])-a[2][0]-a[1][0],dp[i][1]);
            }
            if(c1>2)
            {
                for(int j=0;j<7;j++)
                    dp[i][j+3]=max(dp[i][j+3],dp[i-1][j]-a[1][0]-a[1][1]-a[1][2]);
                dp[i][0]=max(dp[i-1][7]-a[1][1]-a[1][0]-a[1][0]-a[1][2],dp[i][0]);
                dp[i][1]=max(dp[i-1][8]-a[1][1]-a[1][0]-a[1][0]-a[1][2],dp[i][1]);
                dp[i][2]=max(dp[i-1][9]-a[1][1]-a[1][0]-a[1][0]-a[1][2],dp[i][2]);
            }
            if(c1>=1)
            {
                for(int j=0;j<9;j++)dp[i][j+1]=max(dp[i][j+1],dp[i-1][j]-a[1][0]);
                dp[i][0]=max(dp[i][0],dp[i-1][9]-a[1][0]*2);
            }
            if(c1>=2)
            {
                for(int j=0;j<8;j++)dp[i][j+2]=max(dp[i][j+2],dp[i-1][j]-a[1][1]-a[1][0]);
                dp[i][0]=max(dp[i-1][8]-a[1][1]-a[1][0]*2,dp[i][0]);
                dp[i][1]=max(dp[i-1][9]-a[1][1]-a[1][0]*2,dp[i][1]);
            }

            if(c2>=1)
            {
                for(int j=0;j<9;j++)dp[i][j+1]=max(dp[i][j+1],dp[i-1][j]-a[2][0]);
                dp[i][0]=max(dp[i][0],dp[i-1][9]-a[2][0]*2);
            }
            //puts("");for(int ii=0;ii<=9;ii++)printf("%lld ",dp[i][ii]);
        
    }
    //puts("");
    int ans=0;
    for(int i=0;i<=9;i++)ans=max(ans,dp[T][i]);
    printf("%lld\n",ans);
}
```

---

## 作者：SkyRainWind (赞：1)

来一个不用记搜的题解

首先发现每一个turn有用的牌最多5张（3张cost=1，1张cost=2，,1张cost=3）

令$dp[i][j]$表示当前要打$i$轮，之前最后一次打的牌为第$j$张（$\mod 10$）的最大伤害

则我们有

$$dp[i][(j+k)\ mod\ 10]=max\{dp[i-1][j]+z[k][fg]) \}$$
其中：$i$表示当前轮，$j$枚举上一轮到$j-th$张牌了（$\mod 10$），$k$表示这一轮打几张牌，$z[][]$定义如下

令$z[i][flag]$表示当前这一轮打了$i$张牌，是否（$flag==0$表示否）有double的最大伤害

注意到因为$i \le 5$，所以每一轮暴力$O(5!)$判断即可

代码：
```cpp
// by Balloons
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define mpr make_pair
#define debug() puts("okkkkkkkk")
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)

using namespace std;

typedef long long LL;
#define int LL 

const int inf = 1 << 30;
const int maxn=2e5+5;

int n;
int nk[maxn];
int c1_tmp[maxn],c1[maxn][4],c2[maxn],c3[maxn];
int dp[maxn][11],z[7][3];

int cmp(int a,int b){return a>b;}

signed main(){
//	freopen("CF-1176F.in","r",stdin);
	scanf("%I64d",&n);
	int tyf;
	for(int i=1;i<=n;i++){
		int ccnt=0,len=0,len2=0,len3=0;
		c2[i]=-1;c3[i]=-1;
		scanf("%I64d",&nk[i]);
		for(int j=1;j<=nk[i];j++){
			int cst,cx;scanf("%I64d%I64d",&cst,&cx);
			if(cst==1)c1_tmp[++ccnt]=cx;
			if(cst==2)c2[i]=max(c2[i],cx),len2=1;
			if(cst==3)c3[i]=max(c3[i],cx),len3=1;
		}
		sort(c1_tmp+1,c1_tmp+ccnt+1,cmp);
		c1[i][1]=c1[i][2]=c1[i][3]=-1;
		if(ccnt>=1)c1[i][1]=c1_tmp[1],++len;
		if(ccnt>=2)c1[i][2]=c1_tmp[2],++len;
		if(ccnt>=3)c1[i][3]=c1_tmp[3],++len;
		if(i==1)tyf=len+len2+len3;
	}
	
	for(int i=0;i<=n;i++){
		for(int j=0;j<=9;j++){
			dp[i][j]=-1e18;
		}
	}
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		vector<pair<int,int> >vm;
		for(int j=0;j<=3;j++)z[j][0]=z[j][1]=-1e18;
		z[0][0]=0;
		if(c1[i][3]!=-1)vm.push_back(mpr(1,c1[i][3]));
		if(c1[i][2]!=-1)vm.push_back(mpr(1,c1[i][2]));
		if(c1[i][1]!=-1)vm.push_back(mpr(1,c1[i][1]));
		if(c2[i]!=-1)vm.push_back(mpr(2,c2[i]));
		if(c3[i]!=-1)vm.push_back(mpr(3,c3[i]));
		
		do{
			int cnt=0,res=0,pc1=0,mx=0,nums=0;
			for(int j=0;j<vm.size();j++){
				pair<int,int>cur=vm[j];
				if(cnt+cur.first>3)break;
				cnt+=cur.first;
				++nums;
				
				res+=cur.second;mx=max(mx,cur.second); 
//				printf("Q %d %d\n",tmp,z[cnt][1]);
				z[nums][0]=max(z[nums][0],res);
				z[nums][1]=max(z[nums][1],res+mx);
			}
		}while(next_permutation(vm.begin(),vm.end()));
		
		for(int j=0;j<10;j++){
			for(int k=0;k<=3;k++){
				int fg=0;
				if(j+k>=10)fg=1;
				dp[i][(j+k)%10]=max(dp[i][(j+k)%10],dp[i-1][j]+z[k][fg]);
//				if(i==n && (j+k)%10==0)printf("FQ  %d %d %d %d\n",dp[i-1][j],z[k][fg],j,k);
//				printf("%d %d %d;  (j,k)=(%d,%d)\n",i,(j+k)%10,dp[i][(j+k)%10],j,k);
			}
		} 
		vm.clear();
	}
	int ans=0;
	for(int j=0;j<=9;j++)ans=max(ans,dp[n][j]);
//	printf("%I64d\n",dp[n][j]);
	printf("%I64d\n",ans);

	return 0;
}

```

---

