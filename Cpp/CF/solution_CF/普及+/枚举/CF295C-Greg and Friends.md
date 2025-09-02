# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
3 100
50 50 100
```

### 输出

```
5
2
```

## 样例 #3

### 输入

```
2 50
50 50
```

### 输出

```
-1
0
```

# 题解

## 作者：lmy_2011 (赞：6)

### 首先说明
本文思路借鉴于[此](https://blog.csdn.net/qq_43627100/article/details/101713983)
### 题目大意
$m$ 个 $50$ 千克的和 $n$ 个 $100$ 千克的一群人要过河，有且仅有 $1$ 条可载重量为 $k$ 的船，请问最少多少次渡河全部渡过去。
### 基本思路
刚开始我认为这题是个数学题，运用“慢者相伴，快者来回”的方法，先让 $100$ 的人和 $50$ 的人过去，再将 $50$ 的人送回来，可这样还要考虑 $k$ 的重量，太麻烦了。
### 题目思路
这道题只追求最小值，而不纠结中间过程，是一道动态规划题。
#### 状态
这道题我们首先求方案。在这里，$100$ 人和 $50$ 坐与 $50$ 人和 $100$ 坐是无关的，所以它是一个组合数。之后我们再定义 $f_{a,b,c,d}$ 表示 $C_a^c$ 与 $C_b^d$ 之和（从 $a$ 个人中选择 $c$ 个人，同时在 $b$ 个人中选择 $d$ 个人可能的方案）

我们定义 $dp_{i,j,k}$ 表示第 $i$ 次来回，船上 $j$ 个 $50$ 千克的人与 $k$ 个 $100$ 千克的人。
#### 状态转移方程
既然要运过去，还要运过来，就要有两个状态转移方程，它们分别是：
- 运过去：
$$dp_{i,j-a,k-b}=dp_{i,j-a,k-b}+f_{j,k,a,b}\times dp_{i-1,j,k}$$
- 运回来：
$$dp_{i+1,j+a,k+b}=dp_{i+1,j+a,k+b}+f_{x-i,y-j,a,b}\times dp_{i,j,k}$$

最后，记得取模。
#### 边界条件
由于这里的 $dp_{i,j,k}$ 是用来辅助 $f_{a,b,c,d}$ 一起来求方案数，所以我们边界条件就是：
$$dp_{0,x,y}=1$$

---

## 作者：gesong (赞：4)

题目传送门：[CF295C](https://www.luogu.com.cn/problem/CF295C)。
# 思路

本文中令船最多的载重（即题目中的 $k$）设为 $m$，$50$ 千克的人的个数为 $x$，$100$ 千克的人的个数为 $y$。

我们考虑最劣情况，发现就是一个人把另一个拉过去后又自己回来然后又拉下一个人，以此类推，因此最多又 $2n$ 个往返次数，即 $4n$ 个过程（指船从一边到另一边的过程，后文均延用此定义），所以当过程数大于 $4n$ 时，就说明无解。

我们设 $f_{i,j,k}$ 表示现在是第 $i$ 个过程，**这个过程结束后**，还有 $j$ 个 $50$ 千克，$k$ 个 $100$ 千克的人没有过河的方案数，很明显一开始没有人渡河，所以 $f_{0,x,y}=1$，接下来我们考虑转移。

1. 如果 $i$ 是奇数，说明现在是到达对岸的过程，我们枚举这一次渡河的 $50$ 千克的人数 $a$ 与 $100$ 千克的人数 $b$，则 $f_{i,j,k}$ 将要增加的贡献为 $f_{i-1,j+a,k+b}\times C_{j+a}^a\times C_{k+b}^b$。
2. 如果 $i$ 是偶数，说明现在是从对岸回来的过程，我们再次枚举这一次渡河的 $50$ 千克的人数 $a$ 与 $100$ 千克的人数 $b$，则 $f_{i,j,k}$ 将要增加的贡献为 $f_{i-1,j-a,k-b}\times C_{x-j+a}^a\times C_{y-k+b}^b$。

每当进行 $1$ 步骤的转移时，我们判断 $f_{i,0,0}$ 是否不为 $0$，如果不为 $0$，则输出答案，最后如果 $i>4n$ 说明无解。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=60,mod=1e9+7;
int f[4*N][N][N],C[N][N],x,y,n,m;
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++){
		int xx=read();
		if (xx==50) x++;
		else y++;
	}
	C[0][0]=1;
	for (int i=1;i<=n;i++){
		C[i][0]=1;
		for (int j=1;j<=n;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	f[0][x][y]=1;
	for (int i=1;i<=4*n;i++)
		for (int j=0;j<=x;j++)
			for (int k=0;k<=min(y,n-j);k++){
				if (i&1){
					for (int a=0;a<=x-j;a++)
						for (int b=0;b<=y-k;b++)
							if (!(a==0&&b==0)&&50*a+100*b<=m)
								f[i][j][k]=(f[i][j][k]+f[i-1][j+a][k+b]*C[j+a][a]%mod*C[k+b][b]%mod)%mod;
					if (f[i][0][0]){
						cout <<i<<endl<<f[i][0][0];
						return 0;
					}
				}
				else{
					for (int a=0;a<=j;a++)
						for (int b=0;b<=k;b++)
							if (!(a==0&&b==0)&&50*a+100*b<=m)
								f[i][j][k]=(f[i][j][k]+f[i-1][j-a][k-b]*C[x-j+a][a]%mod*C[y-k+b][b]%mod)%mod;
				}
			}
	puts("-1\n0");
    return 0;
}



```

---

## 作者：封禁用户 (赞：4)

### 三维DP

```
dp[i][j][k]表示第i次运送后对岸有j个50kg，k个100kg的方案数
若经过2*n次运送后则必为无解（原因自己想）
```

题意:

有一个船最多能载K千克, 现在有n个人要过河, 船只有一条,每个人要么是50千克,要么是100千克,问有多少种方案可以到达河对岸,且来回次数最少?
先输出最少来回次数,再输出方案数,结果对10^9+7取模
无解输出
-1 
0
```
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
long long n, k;
long long a[55];
long long c[55][55];
long long dp[105][55][55];
/*int会炸！！！！！*/
long long num_50, num_100;
long long old, now;
bool ok;
int main() {
    for(int i = 0; i < 50; i++) {
        c[i][0] = 1;
        for(int j = 1; j <= i; j++) 
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }
    scanf("%lld%lld", &n, &k);
    k /= 50;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        if(a[i] == 50)
            num_50++;
        else
            num_100++;
    }
    old = 1;
    now = 0;
    dp[0][num_50][num_100] = 1;
    for(int l = 0; l < 2 * n; l++) {
    	/*从这岸到那岸*/
        swap(now, old);
        memset(dp[now], 0, sizeof(dp[now]));
        for(int i = 0; i <= num_50; i++) {
            for(int j = 0; j <= num_100; j++) {
                if(i + j * 2 && (i + j * 2) <= k) {
                    for(int x = i; x <= num_50; x++) {
                        for(int y = j; y <= num_100; y++) {
                            dp[now][num_50 - x + i][num_100 - y + j] += dp[old][x][y] * c[x][i] % MOD * c[y][j] % MOD;
                        }
                    }
                }
            }
        }
        if(dp[now][num_50][num_100]) {
            printf("%d\n", l * 2 + 1);
            printf("%lld\n", dp[now][num_50][num_100] % MOD);
            ok = 1;
            break;
            //输出解
        }
        /*从那岸回来*/
        swap(now, old);
        memset(dp[now], 0, sizeof(dp[now]));
        for(int i = 0; i <= num_50; i++) {
            for(int j = 0; j <= num_100; j++) {
                if(i + j * 2 && (i + j * 2) <= k) {
                    for(int x = i; x <= num_50; x++) {
                        for(int y = j; y <= num_100; y++) {
                            dp[now][num_50 - x + i][num_100 - y + j] += dp[old][x][y] * c[x][i] % MOD * c[y][j] % MOD;
                        }
                    }
                }
            }
        }
    }
    if(ok == 0)
        printf("-1\n0");
       //无解
    return 0;
}
```

---

## 作者：zztqwq (赞：3)

下文中大写 $K$ 表示输入的变量，小写 $k$ 表示枚举的变量。

假设有 $tot_5$ 个 $50\mathrm{kg}$ 的人，$tot_1$ 个 $100\mathrm{kg}$ 的人，$f(pos,j,k)$ 表示这一轮结束后船在 $pos$ 岸（$0$ 为出发岸，$1$ 为对岸），对岸 $50\mathrm{kg}$ 的有 $j$ 个，$100\mathrm{kg}$ 的有 $k$ 个，方案数是多少。那么有两种情况：

I. $pos=0$：
$$
f(1,j+c_5,k+c_1)\gets f(1,j+c_5,k+c_1)+\binom{tot_5-j}{c_t}\binom{tot_1-k}{c_1}f(0,j,k)
$$
其中 $c_5,c_1$ 是枚举的变量，满足 $0\le c_5\le tot_5-j$，$0\le c_1\le tot_1-k$，$0< 50c_5+100c_1\le K$。

II. $pos=1$：
$$
f(0,j-c_5,k-c_1)\gets f(0,j-c_5,k-c_1)+\binom{j}{c_5}\binom{k}{c_1}f(1,j,k)
$$
同理，$0\le c_5\le j$，$0\le c_1\le k$，$0<50c_5+100c_1\le K$。

初始值为 $f(0,0,0)=1$，其余为 $0$。枚举轮数（一来一回算两轮）$i$，$i$ 对应的 $pos$ 就是 $i\bmod 2$。当 $f(i\bmod 2,n,n)\not= 0\;(i\bmod 2=1)$ 时则最小值为 $i$。如果 $i>4n$ 时还没有答案，那么一定无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
const int mod=1e9+7,N=310;
inline int qpow(int a,int n)
{
	int ans=1;
	while(n)
	{
		if(n&1)ans=(long long)ans*a%mod;
		a=(long long)a*a%mod;
		n>>=1;
	}
	return ans;
}
int inv[N],p[N];
int binom(int n,int m){return (long long)p[n]*inv[n-m]%mod*inv[m]%mod;}
int f[2][60][60];
int main()
{
	p[0]=inv[0]=1;
	for(int i=1;i<=50;i++)p[i]=(long long)p[i-1]*i%mod,inv[i]=qpow(p[i],mod-2);
	int n=read(),K=read(),tot5=0,tot1=0;
	for(int i=1;i<=n;i++)
	{
		int x=read();
		tot5+=(x==50);
		tot1+=(x==100);
	}
	f[0][0][0]=1;
	for(int i=1;i<=4*n;i++)
	{
		for(int j=0;j<=tot5;j++)
			for(int k=0;k<=tot1;k++)
				f[i&1][j][k]=0;
		for(int j=0;j<=tot5;j++)
		{
			for(int k=0;k<=tot1;k++)
			{
				if(i&1)
				{
					for(int c5=0;c5<=tot5-j;c5++)
					{
						for(int c1=0;c1<=tot1-k;c1++)
						{
							if(!c5&&!c1)continue;
							if(50*c5+100*c1>K) continue;
							f[1][j+c5][k+c1]+=(long long)binom(tot5-j,c5)*binom(tot1-k,c1)%mod*f[0][j][k]%mod;
							f[1][j+c5][k+c1]%=mod;
						}
					}
				}
				else
				{
					for(int c5=0;c5<=j;c5++)
					{
						for(int c1=0;c1<=k;c1++)
						{
							if(!c5&&!c1)continue;
							if(50*c5+100*c1>K) continue;
							f[0][j-c5][k-c1]+=(long long)binom(j,c5)*binom(k,c1)%mod*f[1][j][k]%mod;
							f[0][j-c5][k-c1]%=mod;
						}
					}
				}
			}
		}
		if(f[i&1][tot5][tot1])
		{
			printf("%d\n%d",i,f[i&1][tot5][tot1]);
			return 0;
		}
	}
	printf("-1\n0");
	return 0;
}
```



---

## 作者：SevenDawns (赞：3)

### 首先
我们考虑每次船来回运人时都可以看成一种dp状态

又因为人的体重只有50kg和100kg两种，

所以我们可以开一个三维数组dp[i][j][k],第1维表示在出发岸50kg有i个,第2维表示在出发岸100kg有j个，第3维表示船在哪一岸

又考虑到每一个人都是不同的，所以我们需要对在船岸的这一边的人数和上船的人数去组合数,可以打一个杨辉三角的表b[i][j],用来快速查询组合数

所以状态转移就可以枚举在此岸上船50kg和100kg的人数并取组合数乘上自己的原值（乘法原理）
### 其次
本题还要求求最短运送次数，我们就可以用广搜来遍历枚举答案

同理dp的状态转移也可以在广搜中一起完成
```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct kk
{
	ll i,j,k;
}sh[1000001];//数组模拟队列 
ll n,w,step[100][100][3],dp[100][100][3];
ll a[100],t50,t100,b[1000][1000],mod;
void bfs(ll i1,ll j1,ll wh)
{
	ll l,r;
	l=0;r=0;
	sh[l].i=i1;
	sh[l].j=j1;
	sh[l].k=wh;
	r++;
	while (l<r)
	{
		ll nowi,nowj,nowh;
		nowi=sh[l].i;
		nowj=sh[l].j;
		nowh=sh[l].k;
		l++;
		if (nowh==1)//枚举出发岸 
		for (ll x=0;x<=nowi;x++)
		{
			for (ll y=0;y<=nowj;y++)
			{
				if (50*x+100*y>w || (x==0 && y==0))
				  continue;//判断体重是否超过船载重 
				ll xi,xj,xwh;
				xi=nowi-x;
				xj=nowj-y;
				xwh=1-nowh;
				if (step[xi][xj][xwh]!=0)//重点，此处与一般的广搜不同，当一种状态被遍历过了不能直接标记掉，还要取最优情况 
				{
					if (step[nowi][nowj][nowh]+1<step[xi][xj][xwh])
					  step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
					if (step[nowi][nowj][nowh]+1==step[xi][xj][xwh])//步数相同时，更新dp值 
					{
						dp[xi][xj][xwh]+=(b[nowi+1][x+1]%mod)*(b[nowj+1][y+1]%mod)*(dp[nowi][nowj][nowh]%mod);
				    	dp[xi][xj][xwh]%=mod;
					}
		    	}
				else
				{
					dp[xi][xj][xwh]=(b[nowi+1][x+1]%mod)*(b[nowj+1][y+1]%mod)*(dp[nowi][nowj][nowh]%mod);
					dp[xi][xj][xwh]%=mod;
					step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
					sh[r].i=xi;
					sh[r].j=xj;
					sh[r].k=xwh;
					r++;
				}
			}
		}
		if (nowh==0)//枚举对岸 
		for (ll x=0;x<=t50-nowi;x++)
		{
			for (ll y=0;y<=t100-nowj;y++)
			{
				if (50*x+100*y>w || (x==0 && y==0))
				  continue;
				ll xi,xj,xwh;
				xi=nowi+x;
				xj=nowj+y;
				xwh=1-nowh;
				if (step[xi][xj][xwh]!=0)
				{
					if (step[nowi][nowj][nowh]+1<step[xi][xj][xwh])
					  step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
					if (step[nowi][nowj][nowh]+1==step[xi][xj][xwh])
					{
						dp[xi][xj][xwh]+=(b[t50-nowi+1][x+1]%mod)*(b[t100-nowj+1][y+1]%mod)*(dp[nowi][nowj][nowh]%mod);
					    dp[xi][xj][xwh]%=mod;
					}
		    	}
				else
				{
					dp[xi][xj][xwh]=(b[t50-nowi+1][x+1]%mod)*(b[t100-nowj+1][y+1]%mod)*(dp[nowi][nowj][nowh]%mod);
					dp[xi][xj][xwh]%=mod;
					step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
					sh[r].i=xi;
					sh[r].j=xj;
					sh[r].k=xwh;
					r++;
				}
			}
		}
	}
}
int main()
{
	scanf("%lld%lld",&n,&w);
	for (ll x=1;x<=n;x++)
	  scanf("%lld",&a[x]);
	memset(dp,0,sizeof(dp));
	memset(step,0,sizeof(step));
	for (ll x=1;x<=n;x++)
	{
		if (a[x]==50)
		  t50++;
		if (a[x]==100)
		  t100++;
	}
	b[1][1]=1;
	for (ll x=2;x<=50;x++)
	{
		for (ll y=1;y<=x;y++)
		  b[x][y]=b[x-1][y]+b[x-1][y-1];//杨辉三角
	}
	mod=1000000007;
	dp[t50][t100][1]=1;//令1表示出发岸，0表示到达岸
	step[t50][t100][1]=0;//初始化
	bfs(t50,t100,1);//广搜函数 
	if (step[0][0][0]==0)//如何到达的步数为0就不能到达
	{
		printf("-1\n");
		printf("0\n");
	}
	else
	{
		printf("%lld\n",step[0][0][0]);//答案即为出发岸无人且船在对岸的情况
		printf("%lld\n",dp[0][0][0]);
	}
} 
```

---

