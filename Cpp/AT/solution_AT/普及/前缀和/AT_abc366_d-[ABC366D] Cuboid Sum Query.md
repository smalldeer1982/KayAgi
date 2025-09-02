# [ABC366D] Cuboid Sum Query

## 题目描述

给定一个正整数 $N$ 和满足 $1 \leq x, y, z \leq N$ 的整数组 $(x, y, z)$，对于每个组合都有一个整数 $A_{x, y, z}$。

现在给出 $Q$ 个查询，每个查询要求如下：

对于第 $i$ 个查询 $ (1 \leq i \leq Q) $，给出一组整数 $ (Lx_i, Rx_i, Ly_i, Ry_i, Lz_i, Rz_i) $，其中 $1 \leq Lx_i \leq Rx_i \leq N,\ 1 \leq Ly_i \leq Ry_i \leq N, 1 \leq Lz_i \leq Rz_i \leq N$。要求计算并输出以下求和结果：

$$
\sum_{x=Lx_i}^{Rx_i}\ \sum_{y=Ly_i}^{Ry_i}\ \sum_{z=Lz_i}^{Rz_i}\ A_{x,y,z}
$$

## 说明/提示

### 约束条件

- $1 \leq N \leq 100$
- $1 \leq Q \leq 2 \times 10^{5}$
- $0 \leq A_{x,y,z} \leq 999\ (1 \leq x, y, z \leq N)$
- $1 \leq Lx_i \leq Rx_i \leq N$ $ (1 \leq i \leq Q) $
- $1 \leq Ly_i \leq Ry_i \leq N$ $ (1 \leq i \leq Q) $
- $1 \leq Lz_i \leq Rz_i \leq N$ $ (1 \leq i \leq Q) $
- 所有输入均为整数

### 样例解释 1

对于第 $1$ 个查询，需要求和的值为 $A_{1,2,1} + A_{2,2,1} = 3 + 7 = 10$，因此输出 $10$。对于第 $2$ 个查询，需要求和的值为 $A_{2,1,1} + A_{2,1,2} + A_{2,2,1} + A_{2,2,2} = 5 + 6 + 7 + 8 = 26$，因此输出 $26$。

## 样例 #1

### 输入

```
2
1 2
3 4
5 6
7 8
2
1 2 2 2 1 1
2 2 1 2 1 2```

### 输出

```
10
26```

## 样例 #2

### 输入

```
3
733 857 714
956 208 257
123 719 648
840 881 245
245 112 746
306 942 694
58 870 849
13 208 789
687 906 783
8
3 3 3 3 1 1
1 3 2 3 3 3
2 2 2 3 1 1
1 3 1 1 1 1
2 3 2 3 2 3
1 2 1 1 1 2
3 3 2 2 1 3
1 2 2 3 2 3```

### 输出

```
687
3917
551
1631
5180
3311
1010
4326```

# 题解

## 作者：HeYilin (赞：10)

三维前缀和板子题。

若用 $a$ 表示原数组， $s$ 表示前缀和数组，则一维到三维前缀和分别有如下递推式：

- 一维：

$$
s[i] = s[i-1] + a[i]
$$

- 二维：

$$
s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j]
$$

- 三维：

$$
s[i][j][k]=s[i][j][k-1]+s[i][j-1][k]+s[i-1][j][k]-s[i-1][j-1][k]-s[i-1][j][k-1]-s[i][j-1][k-1]+s[i-1][j-1][k-1]+a[i][j][k]
$$

上述式子一个共同的特点：形如 $s[i][j][k-1]$ 和 $s[i-1][j][k]$ 这样只有一维变化的式子总是符号相同的，其余则是不同的，变化的维数每增加一维，符号便改变一次。

这样比较好记忆，简单的容斥原理即可证明。

更高维的前缀和同理。

下面是我的抽象代码：

```cpp
#include<bits/stdc++.h>
typedef long long int ll;
using namespace std;
const int maxn=105;
int n,q,a[maxn][maxn][maxn],s[maxn][maxn][maxn],x,y,z,xx,yy,zz;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++)cin>>a[i][j][k];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++)s[i][j][k]=s[i][j][k-1]+s[i][j-1][k]+s[i-1][j][k]-s[i-1][j-1][k]-s[i-1][j][k-1]-s[i][j-1][k-1]+s[i-1][j-1][k-1]+a[i][j][k];
		}
	}
	cin>>q;
	while(q--){
		cin>>x>>xx>>y>>yy>>z>>zz;
		cout<<s[xx][yy][zz]-s[xx][yy][z-1]-s[xx][y-1][zz]-s[x-1][yy][zz]+s[x-1][y-1][zz]+s[x-1][yy][z-1]+s[xx][y-1][z-1]-s[x-1][y-1][z-1]<<"\n";
	}
	return 0;
}
/*
2
1 2
3 4
5 6
7 8
2
1 2 2 2 1 1
2 2 1 2 1 2

*/
```

---

## 作者：a_sad_soul (赞：4)

### D
三维前缀和懒得推了，直接上二维前缀和，注意到 $n$ 很小，于是可以枚举一维，其它维度用前缀和查询即可，时间复杂度 $O(nq)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[105][105][105];
int a[105][105][105];
int n,q;
int ask(int i,int lx,int ly,int rx,int ry){
	return pre[i][rx][ry]+pre[i][lx-1][ly-1]-pre[i][lx-1][ry]-pre[i][rx][ly-1];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=n;++k)
				scanf("%d",&a[i][j][k]);
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=n;++k){
				pre[i][j][k]=pre[i][j-1][k]+pre[i][j][k-1]-pre[i][j-1][k-1]+a[i][j][k];
			}
		}
	}scanf("%d",&q);
	while(q--){
		int out=0;
		int xa,xb,xc,ya,yb,yc;
		scanf("%d%d%d%d%d%d",&xa,&ya,&xb,&yb,&xc,&yc);
		for(int i=xa;i<=ya;++i){
			out+=ask(i,xb,xc,yb,yc);
		}
		printf("%d\n",out);
	}
	return 0;
}
```

---

## 作者：ecxjs (赞：1)

三维前缀和的模板题。

首先设 $q$ 为前缀和数组，所以 $q_{i,j,k}$ 表示 $a_{1,1,1}$ 到 $a_{i,j,k}$ 的所有元素之和。

$q_{i,j,k}=a_{i,j,k}+q_{i-1,j,k}+q_{i,j-1,k}+q_{i,j,k-1}-q_{i-1,j-1,k}-q_{i-1,j,k-1}-q_{i,j-1,k-1}+q_{i-1,j-1,k-1}$

而题目所需要的：

$
\sum_{x=Lx_i}^{Rx_i}\ \sum_{y=Ly_i}^{Ry_i}\ \sum_{z=Lz_i}^{Rz_i}\ a_{x,y,z}
=q_{Rx,Ry,Rz}-q_{Lx-1,Ry,Rz}-q_{Rx,Ly-1,Rz}-q_{Rx,Ry,Lz-1}+q_{Lx-1,Ly-1,Rz}+q_{Rx,Ly-1,Lz-1}+q_{Lx-1,Ry,Lz-1}-q_{Lx-1,Ly-1,Lz-1}$


代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<vector<vector<int>>> A(N + 1, vector<vector<int>>(N + 1, vector<int>(N + 1, 0)));
    vector<vector<vector<int>>> pf(N + 1, vector<vector<int>>(N + 1, vector<int>(N + 1, 0)));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            for (int k = 1; k <= N; ++k) {
                cin >> A[i][j][k];
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            for (int k = 1; k <= N; ++k) {
                pf[i][j][k] = A[i][j][k]
                                + pf[i - 1][j][k]
                                + pf[i][j - 1][k]
                                + pf[i][j][k - 1]
                                - pf[i - 1][j - 1][k]
                                - pf[i - 1][j][k - 1]
                                - pf[i][j - 1][k - 1]
                                + pf[i - 1][j - 1][k - 1];
            }
        }
    }
    
    int Q;
    cin >> Q;
    while (Q--) {
        int Lx, Rx, Ly, Ry, Lz, Rz;
        cin >> Lx >> Rx >> Ly >> Ry >> Lz >> Rz;
        
        int ans = pf[Rx][Ry][Rz]
                    - (Lx > 1 ? pf[Lx - 1][Ry][Rz] : 0)
                    - (Ly > 1 ? pf[Rx][Ly - 1][Rz] : 0)
                    - (Lz > 1 ? pf[Rx][Ry][Lz - 1] : 0)
                    + (Lx > 1 && Ly > 1 ? pf[Lx - 1][Ly - 1][Rz] : 0)
                    + (Lx > 1 && Lz > 1 ? pf[Lx - 1][Ry][Lz - 1] : 0)
                    + (Ly > 1 && Lz > 1 ? pf[Rx][Ly - 1][Lz - 1] : 0)
                    - (Lx > 1 && Ly > 1 && Lz > 1 ? pf[Lx - 1][Ly - 1][Lz - 1] : 0);
        
        cout << ans << endl;
    }
    
    return 0;
}

---

## 作者：PineappleSummer (赞：1)

[[ABC366D] Cuboid Sum Query](https://www.luogu.com.cn/problem/AT_abc366_d)

三维前缀和板子，但我不会，所以我用了二维前缀和通过了此题。

考虑只在后两维做二位前缀和，预处理 $s_{i,j,k}=s_{i,j-1,k}+s_{i,j,k-1}-s_{i,j-1,k-1}+a_{i,j,k}$。

对于每个询问，枚举第一维，计算后两维的贡献，这里使用一般二维前缀和的方法即可。

时间复杂度 $\mathcal O(nq)$。

```cpp
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++)
				cin >> a[i][j][k],
			sum[i][j][k] = sum[i][j - 1][k] + sum[i][j][k - 1] - sum[i][j - 1][k - 1] + a[i][j][k];
		}
	cin >> q;
	while (q--) {
		int l1, r1, l2, r2, l3, r3;
		cin >> l1 >> r1 >> l2 >> r2 >> l3 >> r3;
		int x = r2, y = r3, i = l2, j = l3, cnt = 0;
		for (int t = l1; t <= r1; t++) {
			cnt += sum[t][x][y] - sum[t][i - 1][y] - sum[t][x][j - 1] + sum[t][i - 1][j - 1];
		}
		cout << cnt << '\n';
	}
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：1)

三维前缀和板子。

三维前缀和可以类似二维前缀和来做，先给一下二维前缀和数组的计算方法：
$$sum_{i,j}=a_{i,j}+sum_{i-1,j}+sum_{i,j-1}-sum_{i-1,j-1}$$
同样的，可以写出三维前缀和数组的计算方法：
$$sum_{i,j,k}=a_{i,j,k}+sum_{i,j,k-1}+sum_{i,j-1,k}+sum_{i-1,j,k}-sum_{i,j-1,k-1}-sum_{i-1,j,k-1}-sum_{i-1,j-1,k}+sum_{i-1,j-1,k-1}$$
计算答案的时候把加减号交换一下，其余还是类比二维前缀和即可。

这种高维前缀和（区别一下树状数组区间修改区间查询使用的高维前缀和）完全可以类比二维的来做，思维难度并不高。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int maxn=3e2+10;
const int mod=1e9+7;
int n,a[maxn][maxn][maxn];
int sum[maxn][maxn][maxn];
int Q;
signed main()
{
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				a[i][j][k]=read();
				sum[i][j][k]=a[i][j][k]+sum[i][j][k-1]+sum[i][j-1][k]+sum[i-1][j][k]-sum[i][j-1][k-1]-sum[i-1][j][k-1]-sum[i-1][j-1][k]+sum[i-1][j-1][k-1];
			}
		}
	}
	Q=read();
	while(Q--)
	{
		int lx=read(),rx=read(),ly=read(),ry=read(),lz=read(),rz=read();
		int ans=0;
		ans=sum[rx][ry][rz]-sum[rx][ry][lz-1]-sum[rx][ly-1][rz]-sum[lx-1][ry][rz]+sum[rx][ly-1][lz-1]+sum[lx-1][ry][lz-1]+sum[lx-1][ly-1][rz]-sum[lx-1][ly-1][lz-1];
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：0)

### 题意

给出一个三维立方体，每个点有权值。求该立方体的一个子立方体的权值和。

### 思路

看到这道题肯定想到三维前缀和，但我们想象不出来三维前缀和怎么写。发现 $1\le N \le 100$，$1 \le Q \le 10^5$，$O(NQ)$ 可过，我们可以做 $N$ 次二维前缀和，这是简单的。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int a[101][101][101], s[101][101][101];
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            for (int k = 1; k <= n; k ++)
                cin >> a[i][j][k];
    for (int k = 1; k <= n; k ++)
        for (int i = 1; i <= n; i ++)
            for (int j = 1; j <= n; j ++)
                s[k][i][j] = -s[k][i - 1][j - 1] + s[k][i][j - 1] + s[k][i - 1][j] + a[k][i][j];
    int q;
    cin >> q;
    for (int k = 1; k <= q; k ++) {
        int L1, R1, L2, R2, L3, R3, res = 0;
        cin >> L1 >> R1 >> L2 >> R2 >> L3 >> R3;
        for (int i = L1; i <= R1; i ++) 
            res += s[i][R2][R3] - s[i][L2 - 1][R3] - s[i][R2][L3 - 1] + s[i][L2 - 1][L3 - 1];
        cout << res << "\n";
    }
}
int main() {
    int T = 1;
    // cin >> T;
    while (T --) solve();
    return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc366_d)

## 思路

题目大意是给定 $Q$ 次询问，求三维空间中数字的和。

首先，暴力求和时间复杂度 $\mathcal{O}(N^3Q)$，绝对会超时，此时我们考虑前缀和。但三维前缀和的式子很难推，而且推出来容易错，怎么办呢？

看到数据 $1\le Q\le 2\times 10^5$ 和 $1\le N\le 100$，就可以想到**用 $N$ 个二维前缀和来代替三维前缀和**，用慢一些的运行速度换更低的思维难度，最终时间复杂度 $\mathcal{O}(NQ)$，足以通过此题。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll k=0;bool flag=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')flag=0;c=getchar();}
	while(isdigit(c)){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=110;
int n,q,sum[N][N][N];
signed main(){
	cin>>n;
	for(int k=1;k<=n;++k){//注意第一重循环是分层的，所以下面询问的时候输入顺序要颠倒。
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				sum[k][i][j]=sum[k][i-1][j]+sum[k][i][j-1]-sum[k][i-1][j-1]+read();
			}
		}
	}
	cin>>q;
	while(q--){
		int z=read(),zz=read(),x=read(),xx=read(),y=read(),yy=read(),ans=0;//记得颠倒输入、答案初始值赋 0。
		for(int i=z;i<=zz;++i){
			ans+=sum[i][xx][yy]-sum[i][xx][y-1]-sum[i][x-1][yy]+sum[i][x-1][y-1];
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/172092259)

---

## 作者：Scean_Tong (赞：0)

### 题意

给你一个三维数组，给出 $q$ 次询问，每次求出 $\displaystyle{\sum_{x=Lx_i}^{Rx_i} \sum_{y=Ly_i}^{Ry_i} \sum_{z=Lz_i}^{Rz_i} A_{x,y,z}}$ 的值。

### 思路
静态多次询问求和，考虑前缀和，非常直观的做法就是维护 $a$ 数组的三维前缀和，每次询问根据容斥原理求出答案。时间复杂度为 $O(n^3 + q)$。当然也可以把三维拆成 $n$ 个二维，对于每一个二维数组分别维护其二维前缀和，对于每一次询问，枚举第一维从 $L_x$ 到 $Rx$，根据二维前缀和容斥原理相加得到答案，时间复杂度为 $O(n^3 + qn)$。

### 代码
这里给出三维前缀和的实现，大家可以当作三维前缀和板子使用。



```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<vector<vector<int>>> A(110, vector<vector<int>>(110, vector<int>(110)));
vector<vector<vector<int>>> sum(110, vector<vector<int>>(110, vector<int>(110)));
void build() {
	int N=A.size();
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			for(int k=0;k<N;++k){
				sum[i][j][k]=A[i][j][k];
				if(i>0)sum[i][j][k]+=sum[i-1][j][k];
				if(j>0)sum[i][j][k]+=sum[i][j-1][k];
				if(k>0)sum[i][j][k]+=sum[i][j][k-1];
				if(i>0&&j>0)sum[i][j][k]-=sum[i-1][j-1][k];
				if(i>0&&k>0)sum[i][j][k]-=sum[i-1][j][k-1];
				if(j>0&&k>0)sum[i][j][k]-=sum[i][j-1][k-1];
				if(i>0&&j>0&&k>0)sum[i][j][k]+=sum[i-1][j-1][k-1];
			}
		}
	}
}
int query(int x1,int x2,int y1,int y2,int z1,int z2){
	int ans=0;
	ans+=(sum[x2][y2][z2]-(x1>0?sum[x1-1][y2][z2]:0)-(y1>0?sum[x2][y1-1][z2]:0)-(z1>0?sum[x2][y2][z1-1]:0)+(x1>0&&y1>0?sum[x1-1][y1-1][z2]:0)+(x1>0&&z1>0?sum[x1-1][y2][z1-1]:0)+(y1>0&&z1>0?sum[x2][y1-1][z1-1]:0)-(x1>0&&y1>0&&z1>0?sum[x1-1][y1-1][z1-1]:0));
	return ans;
}

int32_t main(){
	int N;
	cin>>N;
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			for (int k=0;k<N;++k){
				cin>>A[i][j][k];
			}
		}
	}
	build();
	int Q;
	cin>>Q;
	while(Q--){
		int Lx,Rx,Ly,Ry,Lz,Rz;
		cin>>Lx>>Rx>>Ly>>Ry>>Lz>>Rz;
		--Lx;--Rx;--Ly;--Ry;--Lz;--Rz;
		cout<<query(Lx,Rx,Ly,Ry,Lz,Rz)<<'\n';
	}

	return 0;
}

```

---

