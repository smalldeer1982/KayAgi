# Domino Carpet

## 题目描述

...Mike the TV greets you again!

Tired of the monotonous furniture? Sick of gray routine? Dreaming about dizzying changes in your humble abode? We have something to offer you!

This domino carpet for only $99.99 will change your life! You can lay it on the floor, hang it on the wall or even on the ceiling! Among other things ...

Having watched the commercial, virus Hexadecimal also wanted to get a Domino Carpet and wanted badly to be photographed in front of it. But of course, a virus will never consent to buying a licensed Carpet! So she ordered a truck of dominoes and decided to make such a Carpet herself.

The original Domino Carpet is a field of squares $ n×m $ in size. Each square is half of a domino, and can be rotated either vertically or horizontally, independently from its neighbors. Vertically rotated domino halves look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77D/24b223911e7d414b4105f5f7b384a2c2404033bc.png)And horizontally rotated halves look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77D/2e953cc07e102d1dc6925e21d1623a202ee1f98f.png)Notice, that some halves looks the same in both rotations, but other halves differ.

Dominoes bought by Hexadecimal are represented by uncuttable chips $ 1×2 $ in size, which can be laid either vertically or horizontally. If the chip is laid vertically, then both of it's halves should be laid vertically orientated; if the chip is laid horizontally, then both of it's halves should be laid horizontally.

The samples of valid and invalid dominoes laid vertically and horizontally are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77D/5374017256a96c5a451a244dd383a369135da2b6.png)Virus Hexadecimal assembles her own Domino Carpet so that the following conditions are satisfied:

- each carpet square is covered by a domino chip, i.e. there are no empty squares;
- all domino chips lie entirely within the carpet and don't overlap with each other;
- if there is a horizontal domino chip with its left half in column $ j $ then there are no horizontal domino chips with their left halves in columns $ j-1 $ or $ j+1 $ .

Before starting to assemble her own Domino Carpet, the virus wants to know the number of ways to achieve the intended purpose modulo $ 10^{9}+7 $ .

You can assume that the virus has an infinitely large number of dominoes of each type.

## 说明/提示

A note to the first example: all correct ways to make Domino Carpet are represented below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77D/981dbdf83cacdc8575134f74d310175de347a9dc.png)And this way is incorrect:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77D/e27d2b360b8d6e5a93ae8ba6b82c2ca4f625b27b.png)

## 样例 #1

### 输入

```
3 4
#################
#O..#...#O.O#...#
#.O.#.O.#.O.#...#
#..O#...#O.O#...#
#################
#O.O#OOO#O.O#...#
#.O.#...#...#.O.#
#O.O#OOO#O.O#...#
#################
#O.O#...#O.O#...#
#...#...#...#.O.#
#O.O#...#O.O#...#
#################
```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
#########
#O.O#O.O#
#.O.#...#
#O.O#O.O#
#########
#...#O.O#
#...#...#
#...#O.O#
#########
```

### 输出

```
2```

## 样例 #3

### 输入

```
2 2
#########
#..O#O..#
#...#...#
#O..#..O#
#########
#O..#..O#
#...#...#
#..O#O..#
#########
```

### 输出

```
0```

# 题解

## 作者：SFlyer (赞：0)

没有什么题解，交一发！

首先，最后一个性质非常的重要，这个告诉我们说，如果有一个占领 $j,j+1$ 列的横向骨牌，那么我们可以把这两列割开，不会影响答案。

因此设 $dp_{i}$ 为刚好放完前 $i$ 列的答案。那么如果我们 $i$ 这一列全部放竖着的，就贡献 $dp_{i-1}$，否则贡献 $dp_{i-2}$。

贡献 $dp_{i-2}$ 前面有一个系数，就是 $i-1,i$ 这两列刚好放完且不全部用竖着的的方案数。这个用另外一个 dp 求出即可。

时间复杂度 $\mathcal{O}(nm)$。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 255;
const ll mod = 1e9+7;

int n,m,a[N][N];
string s[N*4];
ll dp[N];

// 1: hor 2: ver 3: all
int cal(int x,int y){
	int c=0;
	for (int i=x; i<x+4; i++)
		for (int j=y; j<y+4; j++) c+=s[i][j]=='O';
	if (c==0||c==1||c==4||c==5) return 3;
	if (c==2||c==3) return (s[x][y]=='O'?1:2);
	if (c==6) return (s[x+1][y]=='O'?2:1);
}

ll ver(int j){
	int f=(n%2==0);
	for (int i=1; i<=n; i++)
		f&=(a[i][j]!=1);
	return f;
}

ll f[N];
ll hor(int j){
	// j and j+1
	f[0]=1;
	for (int i=1; i<=n; i++) f[i]=0;
	for (int i=1; i<=n; i++){
		if (a[i][j]!=2&&a[i][j+1]!=2){
			f[i]=(f[i]+f[i-1])%mod;
		}
		if (i>=2 && a[i][j]!=1&&a[i][j+1]!=1&&a[i-1][j]!=1&&a[i-1][j+1]!=1){
			f[i]=(f[i]+f[i-2])%mod;
		}
	}
	return (f[n]-ver(j)*ver(j+1)+mod)%mod;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m;
	for (int i=1; i<=4*n+1; i++){
		cin>>s[i]; 
		s[i]=" "+s[i];
	}
	for (int i=2; i<=4*n+1; i+=4){
		for (int j=2; j<=4*m+1; j+=4){
			a[(i+2)/4][(j+2)/4]=cal(i,j);
		}
	}
	dp[0]=1;
	for (int i=1; i<=m; i++){
		dp[i]=(dp[i-1]*ver(i)%mod+(i>=2?(dp[i-2]*hor(i-1)%mod):0))%mod;
	}
	cout<<dp[m]<<"\n"; 
	return 0;
}
```

---

## 作者：minecraft_herobrine (赞：0)

## Update
$2021.11.1$：精简了一些地方的描述，减少 $Latex$ 的使用

## Solution

分析一下每个骨牌上点的形状，$0,1,4,5$ 这四种点是横竖均可的，而 $2,3,6$ 需要区分横竖。

这个输入方式看着就让人烦，先把这一堆字符都给弄成数字的形式，处理出每个位置只能按横竖中某一种方法摆放骨牌还是两种都可以。用两个二进制表示这个位置 是 $1/$ 否 $0$ 可以放横/竖（第 $1/2$ 位二进制）放骨牌。显然两个二进制的值只能取 $1/2/3$，因为骨牌至少可以按照横竖中的某一种方式摆放。

设 $dp[i]$ 表示前 $i$ 列有多少种方案。初值 $dp[0]=1$

对于每一列先看一下所有位置是否能够全放上竖的骨牌，如果所有位置全都可以放竖着的骨牌，则 $dp[i]$ 的初值给为 $dp[i-1]$，否则为 $0$。

若此时不在第一列，则用一个 $cnt[j]$ 表示对于第 $i$ 列和第 $i-1$ 列中，前 $j$ 行的总方案数。初值 $cnt[0]=1$。

先计算一下有多少个可以横放的方格的数量 $x$，把 $cnt[j-1]\times x$ 加到 $cnt[j]$ 中。

如果目前是第一行，显然没有竖放的情况，跳过。否则由于是看本列和上一列，要想竖放骨牌必须要这两行两列都支持放竖的，如果可以，将 $cnt[j]+=cnt[j-2]$。

最后处理完cnt数组，将 $dp[i]+=dp[i-2]*cnt[n]$，但此时需要注意如果整列竖放是可行的话，要排除一次，因为在处理cnt数组的时候也把整列竖放的情况考虑了。$dp[m]$ 的值就是最后的答案。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
char s[1145][1145];
ll a[256][256],dp[256],cnt[256];
ll check(ll x,ll y)
{
	bool f1=((s[x][y]=='O')&&(s[x+2][y+2]=='O')),f2=((s[x][y+2]=='O')&&(s[x+2][y]=='O'));
	bool f3=((s[x+1][y]=='O')&&(s[x+1][y+2]=='O')),f4=((s[x][y+1]=='O')&&(s[x+2][y+1]=='O'));
	/*
	f1: f2: f3: f4:
	O.. ..O ... .O.
	... ... O.O ...
	..O O.. ... .O.
	*/
	if(s[x+1][y+1]=='O')
	{
		if(f1 && f2) return 5;//1
		else if(f1 || f2)
		{
			if(f1) return -3;//横3 
			else return 3;//竖3 
		}
		else return 1;//1
	}
	else
	{
		if(f1 && f2)//4/6/-6
		{
			if(f4) return -6;//横6 
			if(f3) return 6;//竖6 
			return 4;
		}
		else if(f1) return -2;//横2
		else if(f2) return 2;//竖2 
		else return 0;
	}
}
ll Dir(ll x)
{
	if(x==0 || x==1 || x==4 || x==5) return 3;
	else return (x>0 ? 1 : 2);
	//1:只能竖 2:只能横 3:均可 
}
int main()
{
	ll n,m,i,j;
	scanf("%lld %lld",&n,&m);
	for(i=0;i<=4*n;i++)
	{
		scanf("%s",s[i]);
	}
	ll x=1,y=1;
	for(i=1;i<4*n+1;i+=4)
	{
		y=1;
		for(j=1;j<4*m+1;j+=4)
		{
			ll S=check(i,j);
			a[x][y]=Dir(S);
			y++;
		}
		x++;
	}
	dp[0]=1;
	for(i=1;i<=m;i++)
	{
		ll tg=(n+1)%2;//n必须是偶数 
		for(j=1;j<=n && tg;j++) tg=a[j][i]&1;//必须都可以竖放 
		dp[i]=dp[i-1]*tg;
		if(i==1) continue;//此时不存在横放的情况 
		memset(cnt,0,sizeof(cnt));
		cnt[0]=1;
		for(j=1;j<=n;j++)
		{
			cnt[j]=cnt[j-1]*(a[j][i]&a[j][i-1]&2)/2;
			if(j==1) continue;
			bool v=a[j][i]&a[j-1][i]&a[j][i-1]&a[j-1][i-1]&1;
            if(!v) tg=0;//如果不存在能全部竖放的那就无所谓了 
            cnt[j]=(cnt[j]+cnt[j-2]*v)%mod;
		}
		dp[i]=(dp[i]+((dp[i-2]*(cnt[n]-tg))%mod))%mod;//如果存在全部竖放的tg一定是1，减掉即可 
	}
	printf("%lld",dp[m]);
	return 0;
}
```

---

