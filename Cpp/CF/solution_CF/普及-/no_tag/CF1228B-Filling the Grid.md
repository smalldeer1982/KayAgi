# Filling the Grid

## 题目描述

Suppose there is a $ h \times w $ grid consisting of empty or full cells. Let's make some definitions:

- $ r_{i} $ is the number of consecutive full cells connected to the left side in the $ i $ -th row ( $ 1 \le i \le h $ ). In particular, $ r_i=0 $ if the leftmost cell of the $ i $ -th row is empty.
- $ c_{j} $ is the number of consecutive full cells connected to the top end in the $ j $ -th column ( $ 1 \le j \le w $ ). In particular, $ c_j=0 $ if the topmost cell of the $ j $ -th column is empty.

In other words, the $ i $ -th row starts exactly with $ r_i $ full cells. Similarly, the $ j $ -th column starts exactly with $ c_j $ full cells.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228B/718cfa57d80806dbeecabcc145703169da7deb79.png)These are the $ r $ and $ c $ values of some $ 3 \times 4 $ grid. Black cells are full and white cells are empty.You have values of $ r $ and $ c $ . Initially, all cells are empty. Find the number of ways to fill grid cells to satisfy values of $ r $ and $ c $ . Since the answer can be very large, find the answer modulo $ 1000000007\,(10^{9} + 7) $ . In other words, find the remainder after division of the answer by $ 1000000007\,(10^{9} + 7) $ .

## 说明/提示

In the first example, this is the other possible case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228B/9d1150639137da10f3c33f0f1362034ed19afeb9.png)In the second example, it's impossible to make a grid to satisfy such $ r $ , $ c $ values.

In the third example, make sure to print answer modulo $ (10^9 + 7) $ .

## 样例 #1

### 输入

```
3 4
0 3 1
0 2 3 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 1
0
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
19 16
16 16 16 16 15 15 0 5 0 4 9 9 1 4 4 0 8 16 12
6 12 19 15 8 6 19 19 14 6 9 16 10 11 15 4
```

### 输出

```
797922655
```

# 题解

## 作者：Katsura_Hinagiku (赞：4)

我们发现，一些格子是黑是白均满足题目所给要求。若有k个这样的格子，方案数就是$2^k$种。按照题目要求填色，找出这些格子即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int h,w,mp[1005][1005];
ll cnt=0;
const ll MOD=1000000000+7;
ll ksm(ll basic,ll mi)
{
	ll tmp=1;
	while(mi)
	{
		if(mi&1)tmp=tmp*basic%MOD;
		mi>>=1;
		basic=basic*basic%MOD;
	}
	return tmp;
}
int main()
{
	memset(mp,-1,sizeof(mp));
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;++i)
	{
		int kk;
		scanf("%d",&kk);
		for(int j=1;j<=kk;++j)mp[i][j]=1;
		mp[i][kk+1]=0;//连续r[i]个黑色格子
	}
	for(int i=1;i<=w;++i)
	{
		int kk;
		scanf("%d",&kk);
		for(int j=1;j<=kk;++j)
		{
			if(mp[j][i]==0)
			{
				printf("0\n");
				return 0;
			}
			mp[j][i]=1;
		}
		if(mp[kk+1][i]==1)
		{
			printf("0\n");
			return 0;
		}//如果染色产生冲突，无方案
		mp[kk+1][i]=0;//连续c[i]个格子
	}
	for(int i=1;i<=h;++i)
	{
		for(int j=1;j<=w;++j)
		{
			if(mp[i][j]==-1)++cnt;//找到尚未被染色的格子
		}
	}
	printf("%d\n",ksm(2,cnt));
	return 0;
}
```

---

## 作者：andyli (赞：2)

题意：求满足以下条件的图的个数并对$10^9+7$取模：  
- 第$i$行前$r_i$个数均为$1$且第$r_i+1$个数为$0$  
- 第$i$列前$c_i$个数均为$1$且第$c_i+1$个数为$0$。 

若这些条件有冲突（e.g. $r_1=0$且$c_1=1$），则答案为$0$。若不冲突，先计算剩余没有限制的格子数量$k$。这些格子无论填$0$还是$1$都满足要求，用乘法原理可得满足要求的图的总数量为$2^k$。  
代码如下：  
```cpp
const int maxn = 1005, MOD = 1000000007;

void ns() // no_solution, 条件互相冲突
{
    writeln(0);
    exit(0);
}
bool vis[maxn][maxn], m[maxn][maxn];
int main()
{
    int h, w;
    io.read(h, w);
    for (int i = 0; i < h; i++) {
        int t;
        io.read(t);
        for (int j = 0; j <= t; j++) {
            if (j < t) // 前r_i个格子为1
                if (vis[i][j] && !m[i][j]) // 与其他条件冲突
                    ns();
                else
                    vis[i][j] = true, m[i][j] = true;
            else if (vis[i][j] && m[i][j]) // 第r_i+1个格子为0并与其他条件冲突
                ns();
            else
                vis[i][j] = true;
        }
    }
    for (int i = 0; i < w; i++) {
        int t;
        io.read(t);
        for (int j = 0; j <= t; j++) {
            if (j < t) // 前c_i个格子为1
                if (vis[j][i] && !m[j][i]) // 与其他条件冲突
                    ns();
                else
                    vis[j][i] = true, m[j][i] = true;
            else if (vis[j][i] && m[j][i]) // 第r_i+1个格子为0并与其他条件冲突
            else
                vis[j][i] = true;
        }
    }
    int ans = 1;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (!vis[i][j]) // 无限制
                ans = (ans << 1) % MOD;
    writeln(ans);
    return 0;
}
```

---

## 作者：HuZHUNZHUN (赞：1)

### 本蒟蒻的第一篇题解QAQ

本题思路：

1) 读入行的要求，无条件填充。

2) 读入列的要求，如果要求与已经填充的相矛盾，输出 $0$，结束运行，否则填充进去。

3) 看看还有几个块没有被填充，用 $2^{k}$ 计算结果就行啦。

无注释代码奉上：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int a[1010][1010],n,m;
int main()
{
	memset(a,-1,sizeof(a));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int k;
		scanf("%d",&k);
		for(int j=1;j<=k;j++) a[i][j]=1;
		a[i][k+1]=0;
	}
	for(int j=1;j<=m;j++)
	{
		int k;
		scanf("%d",&k);
		for(int i=1;i<=k;i++)
		{
			if(a[i][j]!=0)
			{
				a[i][j]=1;
			}
			else
			{
				cout<<0<<endl;
				return 0;
			}
		}
		if(a[k+1][j]!=1)
		{
			a[k+1][j]=0;
		}
		else
		{
			cout<<0<<endl;
			return 0;
		}
	}
	long long ans=1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]==-1) ans=ans*2%mod;
	printf("%lld\n",ans);
	return 0;
}

---

## 作者：弦巻こころ (赞：1)

我们首先可以发现,答案就等于 $2^x$ (x 为未被限制的方块),那怎么求这个未被限制的方块呢?

很简单,它给出的第$r^i$ 或$c^i$个一定是第一个白色说明之前全是黑的.我们只需按题目要求染色即可. 

对于矛盾的情况,一定是既要求它是白的,又要求它是黑的,那么就是矛盾的情况了.

所以我们将白染成1黑染成2 最后再扫一遍有多少数为0即可.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int vis[1005][1005];
int n,m;
int h,w,ans=1;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n-1;i++)
	{
		scanf("%d",&h);
		for(int j=0;j<h;j++)
		{
			vis[i][j]=1;
		}
		vis[i][h]=2;//染色
	}
	for(int i=0;i<=m-1;i++)
	{
		scanf("%d",&w);
		for(int j=0;j<w;j++)
		{
			if(vis[j][i]==2)//注意判矛盾的情况
			{
				cout<<0;
				return 0;
			}
			vis[j][i]=1;
		}
		if(vis[w][i]==1)
		{
			cout<<0;
			return 0;
		}
		vis[w][i]=2;
	}
	for(int i=0;i<=n-1;i++)
	{
		for(int j=0;j<=m-1;j++)
		{
			if(!vis[i][j])//统计有多少个数未被限制
			{
				ans*=2;
				ans%=mod;
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：xh39 (赞：0)

这道题数据范围较小,可以暴力。比赛时为了节约时间,提高正确率,就没写快速幂了。

标记每一个方格必须涂黑,严禁涂黑,可涂可不涂。(涂黑表示满格)

然后找可涂可不涂的方格,然后每次×2

用样例1来说一下我的方法吧。
```
3 4
0 3 1
0 2 3 0
```
首先,0 3 1表示行,先判断0,如果0,0选了,连续涂黑的格子就不会是0了,所以标记为不能涂黑

3:1,0 1,1 1,2必须涂,如果不涂就不会是3。1,3严禁涂,不然就是4以上了

重复步骤,得到这个涂完的方格
```
+--+--+--+--+
|0 |  |  |  |
+--+--+--+--+
|1 |1 |1 |0 |
+--+--+--+--+
|1 |0 |  |  |
+--+--+--+--+
```
其中1表示必须涂,0表示严禁涂。

接下来看列,重复行的步骤,得到

```
+--+--+--+--+
|0 |1 |1 |0 |
+--+--+--+--+
|1 |1 |1 |0 |
+--+--+--+--+
|1 |0 |1 |  |
+--+--+--+--+
```

只剩下一个格子可以 可选可不选了,答案就是2¹=2了。

注意特判既必须选,又严禁选的格子(样例2)此时就没有方案,输出0。
```cpp
//这里1表示涂,2表示不涂,0表示可涂可不涂。
#include<iostream>
using namespace std;
long long mark[1005][1005]={0},a[1005],b[1005];
int main(){
	long long n,m,i,j,sum=1;
	cin>>n>>m;
	for(i=0;i<n;i++){
		cin>>a[i];
		for(j=0;j<a[i];j++){
			mark[i][j]=1;
		}
		mark[i][j]=2;
	}
	for(i=0;i<m;i++){
		cin>>b[i];
		for(j=0;j<b[i];j++){
			if(mark[j][i]==2){ //现在要标记为1,可是已经标记为2了,所以遇到了既必须选,又严禁选的格子。
				cout<<0;
				return 0;
			}
			mark[j][i]=1;
		}
		if(mark[j][i]==1){ //没方案,与上面注释一样。
			cout<<0;
			return 0;
		}
		mark[j][i]=2;
	}
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(mark[i][j]==0){ //可选可不选,就是没有标记过的格子。
				sum<<=1; //×2的快速版。
				sum%=1000000007;
			}
		}
	}
	cout<<sum;
	return 0;
}
```
我太弱了,讲得不怎么好,如果有哪个地方有疑问,可以在评论区回复。

---

## 作者：Steven_Meng (赞：0)

## 广告
想要更佳的食用体验，请前往[蒟蒻のBlog](https://stevenmhy.tk/archives/9b983113.html)

## $Pro2$

[传送门](https://codeforces.com/contest/1228/problem/B)

给你两个数列$r[i],c[i]$，要你构造一个长$h$宽$w$的格子图，使得第$i$个纵列从最上面数起刚好有$c[i]$个连续的黑色格子，第$i$个横列从最左边数起刚好有$r[i]$个连续的黑色格子。

求满足条件的格子图的总数。

## $Sol2$

设这个图是$map$，注意到$map[i][1 \to r[i]]$都必须是黑色的，$map[i][r[i]+1]$必须为白色的，对于$c[i]$也是同理。

如果这样染色出现冲突，答案就是$0$。

发现剩下的格子都可以随意染色，设有$k$个，于是答案就是$2^{k}$

## $Code2$

```cpp
#include <bits/stdc++.h>
#define MAXN 2000005
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=(x<<3)+(x<<1)+(ch^'0');
        ch=getchar();
    }
    return x*f;
}
int a[1005][1005];
int main(){
	int h=read(),w=read();
	memset(a,-1,sizeof(a));
	for (register int i=1;i<=h;++i){
		int len=read();
		for (register int j=1;j<=len;++j){
			if (a[i][j]==0){//出现冲突
				puts("0");
				return 0;
			}
			a[i][j]=1;
		}
		if (a[i][len+1]==1){
			puts("0");
			return 0;
		}
		a[i][len+1]=0;
	}
	for (register int i=1;i<=w;++i){
		int len=read();
		for (register int j=1;j<=len;++j){
			if (a[j][i]==0){
				puts("0");
				return 0;
			}
			a[j][i]=1;
		}
		if (a[len+1][i]==1){
			puts("0");
			return 0;
		}
		a[len+1][i]=0;
	}
	long long ans=1;
	for (register int i=1;i<=h;++i){
		for (register int j=1;j<=w;++j){
			if (a[i][j]==-1) ans=(ans*2ll)%((long long)1e9+7);//没被染色
		}
	}
	printf("%lld\n",ans);
}
```

---

