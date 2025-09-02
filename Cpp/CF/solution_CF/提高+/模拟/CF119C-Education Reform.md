# Education Reform

## 题目描述

## 【题意】
有一所学校，这个学校一个学期有 $n$ 天，要学习 $m$ 门学科。每天都要学习一门学科，每个学科最多只能学习一天。

每门学科有 $3$ 个限制：$a_i,b_i,c_i$。

每天都要布置作业，每一天布置的作业量都有一定限制。

- 每天只能布置一科作业，且作业量保证在该学科的 $a_i,b_i$ 之间。

- 每天作业学科的 $c_i$ 值严格单调递增。

- 每一天的作业量 $x$ 都应该是前一天的作业量 $+k$ 或 $\times k$ （ $k$ 是定值）

求一种方案，使得总作业量最大（~~咳咳~~）

## 说明/提示

$$
n,m \leq 50,k\leq 100
$$
$$
a_i\leq b_i\leq 10^{16},b_i-a_i\leq 100,c_i \leq 100
$$

## 样例 #1

### 输入

```
4 5 2
1 10 1
1 10 2
1 10 3
1 20 4
1 100 5
```

### 输出

```
YES
2 8
3 10
4 20
5 40
```

## 样例 #2

### 输入

```
3 4 3
1 3 1
2 4 4
2 3 3
2 2 2
```

### 输出

```
NO```

# 题解

## 作者：DPair (赞：6)

一道很恶心的 $DP$ 题。

## 【思路】
首先判断这道题是一个有一堆限制还带输出的 $DP$ 。

然后不难发现要把学科按 $c$ 排序，由于最后输出的是学科编号，要把 $id$ 也记录一下。

然后设计状态。

这里设 $dp[i][j][p]$ 表示选了第 $i$ 门学科，到了第 $j$ 天，最后一门学科作业量是 $p$ 能得到的最大总作业量。

发现 $a_i\leq b_i \leq 10^{16}$ 空间必炸。

然后又发现 $b_i-a_i\leq 100$。

好办了，直接改变 $p$ 的定义为 最后一门学科作业量是 $p+a_i$ ，由于 $i$ 已经确定 $p+a_i$ 仍然是定值。

最后空间复杂度 $O(nm(b_i-a_i))$ 。

考虑转移。

首先要求 $c$ 严格递增，由于已经排过序，这里只要判是否相等即可，相等即退出。

然后判 **当前的** $a_i+p -k$ 与 $(a_i+p)/k$ 是否在目标的 $[a,b]$ 之间即可（除法还要判一个整除）。最后如果转移过来的结果大于当前结果，直接更新答案。 

输出其实也不难，每一次成功转移记录一下前驱就行，最后递归输出。

时间复杂度 $O(m^2n(b_i-a_i))$

然后就这么做完了。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
#define int long long
int n, m, k;

int dp[55][55][105];
typedef pair <int, int> pi;

pi pre[55][55][105];

struct Subject {
    int l, r, val, id;
    inline bool operator < (const Subject &tmp) const{
        return val < tmp.val;
    }
}a[55];

inline void output(int x, int y, int z){
    if(y == 1) {printf("%lld %lld\n", a[x].id, a[x].l + z);return;}
    pi cur = pre[x][y][z];
    output(cur.first, y - 1, cur.second);
    printf("%lld %lld\n", a[x].id, a[x].l + z);
}

signed main(){
    read(n);read(m);read(k);
    for (register int i = 1;i <= m;i ++){read(a[i].l);read(a[i].r);read(a[i].val);a[i].id = i;}
    sort(a + 1, a + m + 1);
    for (register int i = 1;i <= m;i ++){
        for (register int j = 1;j <= n && j <= i;j ++){
            for (register int p = a[i].l;p <= a[i].r;p ++){
                int dis = p - a[i].l;
                if(j == 1) {dp[i][j][dis] = p;continue;}
                for (register int q = 1;q < i;q ++){
                    if(a[q].val == a[i].val) continue;
                    if(p - k >= a[q].l && p - k <= a[q].r && dp[q][j - 1][p - k - a[q].l] && dp[q][j - 1][p - k - a[q].l] + p > dp[i][j][dis]) dp[i][j][dis] = dp[q][j - 1][p - k - a[q].l] + p, pre[i][j][dis] = make_pair(q, p - k - a[q].l);
                    if(p % k == 0 && (p / k) >= a[q].l && (p / k) <= a[q].r && dp[q][j - 1][(p / k) - a[q].l] && dp[q][j - 1][(p / k) - a[q].l] + p > dp[i][j][dis]) dp[i][j][dis] = dp[q][j - 1][(p / k) - a[q].l] + p, pre[i][j][dis] = make_pair(q, (p / k) - a[q].l);
                }
            }
        }
    }
    pi pos;
    int ans = -0x3f3f3f3f;
    for (register int i = n;i <= m;i ++){
        for (register int p = a[i].r;p >= a[i].l;p --){
            int dis = p - a[i].l;
            if(dp[i][n][dis] && dp[i][n][dis] > ans) pos = make_pair(i, dis), ans = dp[i][n][dis];
        }
    }
    if(ans == -0x3f3f3f3f) printf("NO\n");
    else{
        printf("YES\n");
        output(pos.first, n, pos.second);
    }
    return 0;
}
```

---

## 作者：jzp_1025 (赞：1)

# 题目分析

因为要求 $c_i$ 递增，所以我们肯定排序一下再来处理。

现在题目就转化为让一个**合法子序列**的作业数量和最大。所以我们考虑子序列 dp。

后效性只跟**上一个学科**和**学科作业数**有关，考虑把这两维记在状态中。因为 $a_i,b_i\le10^{16}$ 所以直接记作业数是肯定不行的，但 $b_i-a_i\le100$ 所以我们考虑做差后存到状态中。

我们就能得出状态 $f_{t,i,w}$ 表示第 $t$ 天学第 $i$ 门学科且当天学科作业数量为 $a_i+w$ 的最大作业总和。

得到转移方程 $f_{t,i,w}=\max\limits_{j=1}^{i-1}({f_{t-1,j,w+a_i-k-a_j}+w+a_i,f_{t-1,j,(w+a_i)/k-a_j}+w+a_i})$。

我们得到最大的作业和后，就递归往前找就可以了。

总时间复杂度 $O(nm^2(b_i-a_i))$。

式子看起来有点丑，详见代码。

# Code

```cpp
const int maxn=100+10;
int d,n,val;
struct Subject{
	int l,r,c;
	int id;
	bool operator < (const Subject &it)const{
		return c<it.c;
	}
}s[maxn];
int mx,tmp;
int p;
int f[maxn][maxn][maxn];
void find(int t,int x,int now){
	if(!t)return ;
	mx=-1,p=0,tmp=0;
	for(int i=1;i<x;i++){
		if(s[i].c>=s[x].c)continue ;
		int j=now-val-s[i].l;
		if(j>=0&&j<=s[i].r-s[i].l&&f[t-1][i][j]){
			if(f[t-1][i][j]>mx){
				mx=f[t-1][i][j];
				tmp=j+s[i].l;
				p=i;
			}
		}
		if(now%val==0){
			j=now/val-s[i].l;
			if(j>=0&&j<=s[i].r-s[i].l&&f[t-1][i][j]){
				if(f[t-1][i][j]>mx){
					mx=f[t-1][i][j];
					tmp=j+s[i].l;
					p=i;
				}
			}
		}
	}
	find(t-1,p,tmp);
	cout<<s[x].id<<' '<<now<<'\n';
}
signed main(){
	cin>>d>>n>>val;
	for(int i=1;i<=n;i++){
		cin>>s[i].l>>s[i].r>>s[i].c;
		s[i].id=i;
	}
	sort(s+1,s+1+n);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=s[i].r-s[i].l;j++){
			f[1][i][j]=s[i].l+j;
		}
	}
	for(int t=2;t<=d;t++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				if(s[i].c<=s[j].c)continue ;
				for(int k=0;k<=s[j].r-s[j].l;k++){
					if(f[t-1][j][k]==0)continue ;
					int now=1ll*(s[j].l+k)+val-s[i].l;
					if(now>=0&&now<=s[i].r-s[i].l){
						f[t][i][now]=max(f[t][i][now],f[t-1][j][k]+now+s[i].l);
					}
					now=1ll*(s[j].l+k)*val-s[i].l;
					if(now>=0&&now<=s[i].r-s[i].l){
						f[t][i][now]=max(f[t][i][now],f[t-1][j][k]+now+s[i].l);
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=s[i].r-s[i].l;j++){
			if(f[d][i][j]>mx){
				mx=f[d][i][j];
				tmp=j+s[i].l;
				p=i;
			}
		}
	}
	if(!p){
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	find(d,p,tmp);

	return 0;
}
```

---

## 作者：zplqwq (赞：1)

首先 $c_i$ 的限制你排个序就好了。

这种题你显然考虑类似这样的状态：$dp_{i,j}$ 表示当前时间为第 $j$  天，第 $i$ 科必选的最大值。但你发现这样你没法转移，因为你不知道前一天的作业量，于是你再加一维，$dp_{i,j,k}$ 第 $j$  天，第  $i$  科必选且今天的作业量为 $k$ 的最大值，但因为 $a_i \le 10^{16}$ 这样空间肯定就寄了。再读一遍题发现 $b_i-a_i\le100$ 也就是说每一个作业量的范围都很小，所以你设 $dp_{i,j,k}$ 为第 $j$  天，第  $i$  科必选且今天的作业量为 $k+a_i$ 的最大值。注意，这里的 $k$ 和下文的 $k$ 意义不同。

考虑转移，当前的作业量必定是从前一天选择的科目的作业量 $\times k$ 或 $+k$ 得到，所以你枚举前一天选的是哪科，然后根据你今天的作业量可以推断出前一天的作业量，具体地：

- 当 $a_{pre} \le o-k \le b_{pre}$  时，可以由 $dp_{pre,j-1,o-k-a_{\text{pre}}}$ 转移

- 当 $a_{pre} \le \frac{o}{k} \le b_{pre}$ 时，可以由 $dp_{pre,j-1,\frac{o}{k}-a_{\text{pre}}}$  转移。

对于输出方案，典中典做法就是记录每个状态从哪个状态转移来递归输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e18;
const int N=1e6+10;
const int M=110;
int n,m,k,dp[M][M][M];
pair<int,int> pre[M][M][M];
struct node{
	int l,r,val,id;
}a[N];
int cmp(node x,node y){
	return x.val<y.val;
}
void print(int i,int j,int p){
	if(j==1){cout<<a[i].id<<" "<<p+a[i].l<<"\n";return ;}
	print(pre[i][j][p].first,j-1,pre[i][j][p].second);
	cout<<a[i].id<<" "<<p+a[i].l<<"\n";
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>a[i].l>>a[i].r>>a[i].val;
		a[i].id=i;
	}
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			for(int o=a[i].l;o<=a[i].r;o++){
				int p=o-a[i].l;
				if(j==1){dp[i][j][p]=o;continue;}
				for(int z=1;z<i;z++){
					if(a[i].val==a[z].val) continue;
					if(o-k>=a[z].l and o-k<=a[z].r and dp[z][j-1][o-k-a[z].l] and dp[z][j-1][o-k-a[z].l]+o>dp[i][j][p]){
						dp[i][j][p]=dp[z][j-1][o-a[z].l-k]+o;
						pre[i][j][p]=make_pair(z,o-a[z].l-k);
					}
					if(o%k==0 and o/k>=a[z].l and o/k<=a[z].r and dp[z][j-1][(o/k)-a[z].l] and dp[z][j-1][(o/k)-a[z].l]+o>dp[i][j][p]){
						dp[i][j][p]=dp[z][j-1][(o/k)-a[z].l]+o;
						pre[i][j][p]=make_pair(z,o/k-a[z].l);
					}
				}
			}
		}
	}
	int ans=-inf;pair<int,int> pos;
	for(int i=n;i<=m;i++){
		for(int o=a[i].l;o<=a[i].r;o++){
			int p=o-a[i].l;
			if(dp[i][n][p] and dp[i][n][p]>ans){
				// cout<<ans<<" "<<i<<" "<<n<<" "<<p<<" "<<dp[i][n][p]<<endl;
				ans=dp[i][n][p];pos=make_pair(i,p);
			}
		}
	}
	if(ans!=-inf){
		cout<<"YES\n";
		print(pos.first,n,pos.second);
	}
	else cout<<"NO\n";
	return 0;
}
```





---

## 作者：_edge_ (赞：1)

个人感觉有 pj T3 的难度 (

首先看到这种题目，发现它有很多限制，并且是最优问题，一般情况下可以考虑 DP。

首先需要满足 $c_i$ 单调递增，不妨对 $c_i$ 进行排序，然后再这上面进行 DP。

那么我们考虑，每一天要在前一天基础上 $\times k$ 或者 $+k$，再看一眼数据范围 $b_i \le 10^{16}$，那好像是无法直接进行一个背包的，然后我们再看一眼 $b_i-a_i \le 100$ ！！！那不是可以将无用状态全部压缩掉？

那么我们设状态，$f_{i,j,k}$ 当前是第 $i$ 天，已经前面有了 $j$ 天选择了，当天的作业量是 $k$，所拥有的作业量最大值。

当然我们这里要记录前驱。

因为我考虑到有 $\times k$ ，如果是直接枚举当前这个状态，然后枚举前面的来更新有点麻烦，于是我们直接考虑用刷表来做，就是当前枚举这个状态去更新后面的状态。

这样的话复杂度大概是 $O(n^3 \times 100)$，是可以通过这道题目的。

细节这边要注意一点这个数组的下标不能超过 $100$，以及你当前计算最大作业要加上 $a_i$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int INF=105;
const int INFN=55;
int kk,f[INFN][INFN][INF],f1[INFN][INFN][INF][2];
struct ND {
        int x,y,z,id;
} aa[INF];
//
int n,m,k;
bool cmp(ND xx,ND yy) {
        return xx.z<yy.z;
}
void print(int x,int y,int z) {
        if (x==0) return;
        print(f1[x][z][y][0],f1[x][z][y][1],z-1);
        // cout<<y<<"\n";
        cout<<aa[x].id<<" "<<y+aa[x].x<<"\n";
        return;
}
signed main()
{
        memset(f,-63,sizeof f);
        scanf("%lld %lld %lld",&n,&m,&kk);
        for (int i=1; i<=m; i++)
                scanf("%lld %lld %lld",&aa[i].x,&aa[i].y,&aa[i].z),aa[i].id=i;
        sort(aa+1,aa+1+m,cmp);
        // for (int i=0;i<=100;i++)
        f[0][0][0]=0; // 50*50*50*100 = 125000*50 = 6250000
        for (int i=0; i<=m; i++) {
                for (int l=0; l<=aa[i].y-aa[i].x; l++) f[i][1][l]=aa[i].x+l;
                for (int j=0; j<=i; j++) {
                        for (int l=0; l<=aa[i].y-aa[i].x; l++)
                                for (int k=i+1; k<=m; k++) {
                                        if (f[i][j][l]<-1e9) continue;
                                        if (aa[i].z<aa[k].z) {
                                                if (0<=l+kk+aa[i].x-aa[k].x&&l+kk+aa[i].x-aa[k].x<=100)
                                                        if (f[k][j+1][l+kk+aa[i].x-aa[k].x]<f[i][j][l]+l+kk+aa[i].x)
                                                        {
                                                                f[k][j+1][l+kk+aa[i].x-aa[k].x]=f[i][j][l]+l+kk+aa[i].x;
                                                                f1[k][j+1][l+kk+aa[i].x-aa[k].x][0]=i;
                                                                f1[k][j+1][l+kk+aa[i].x-aa[k].x][1]=l;
                                                        }
                                                if (0<=(aa[i].x+l)*kk-aa[k].x && (aa[i].x+l)*kk-aa[k].x<=100)
                                                        if (f[k][j+1][(aa[i].x+l)*kk-aa[k].x]<f[i][j][l]+(aa[i].x+l)*kk)
                                                        {
                                                                f[k][j+1][(aa[i].x+l)*kk-aa[k].x]=f[i][j][l]+(aa[i].x+l)*kk;
                                                                f1[k][j+1][(aa[i].x+l)*kk-aa[k].x][0]=i;
                                                                f1[k][j+1][(aa[i].x+l)*kk-aa[k].x][1]=l;
                                                        }
                                        }
                                }
                }
        }
        // cout<<f[5][3][2]<<" "<<"\n";
        int ans=-1,ans1=-1,ans2=-1;
        for (int i=n; i<=m; i++) {
                for (int j=0; j<=aa[i].y-aa[i].x; j++) {
                        if (f[i][n][j]>0) {
                                if (f[i][n][j]>ans) {
                                        ans=f[i][n][j],ans1=i; ans2=j;
                                        // cout<<i<<" "<<n<<" "<<j<<" "<<f[i][n][j]<<"\n";
                                        // cout<<ans<<"\n";
                                }
                        }
                }
        }
        if (ans==-1) cout<<"NO\n";
        else {
                cout<<"YES\n";
                print(ans1,ans2,n);
        }
        return 0;
}

```

若有问题还请指出。

---

## 作者：Re_Yks_Offical (赞：0)

很容易写错代码的题。

显然，先对 $c_i$ 排序。

因为 $b_i-a_i$ 很小，考虑将枚举 $[a_i,b_i]$ 内的作业量作为一个维度。容易得出状态：$dp_{i,j,t}$ 为当前已经遍历完前 $i$ 个科目，选中了 $j$ 个科目（包括第 $i$ 个科目），且第 $i$ 个科目的课后作业量为 $t+a_i$ 时的**前驱科目**、**前驱科目的课后作业量**和**所有科目的总作业量**（事实上对于每个 $dp_{i,j,t}$ 都是含有 $3$ 个元素的元组）。

然后考虑转移。

- 如果希望从第 $i$ 个科目开始，即 $j=1$ 时，$dp_{i,j,t}$ 固定为 $(0,0,t+a_i)$。
- 反之，需要枚举前驱 $lst$，有两种转移
  - 加法运算，$dp_{i,j,t}$ 由 $dp_{lst,j-1,t+a_i-k-a_{lst}}$ 转移而来。前提是 $t+a_i-k-a_{lst}$ 在 $[a_{lst},b_{lst}]$ 范围内。
  - 乘法运算，$dp_{i,j,t}$ 由 $dp_{lst,j-1,\frac{t+a_i}{k}-a_{lst}}$ 转移而来。注意除了 $\frac{t+a_i}{k}-a_{lst}$ 在 $[a_{lst},b_{lst}]$ 范围内的限制，还需满足 $k\mid(t+a_i)$。

当然，转移结果需要对**所有科目的总作业量**取最大值。

最后，在寻找到 $j=n$ 且**所有科目的总作业量**最大的状态后，进行对该状态的回溯操作即可。

实际代码和上述文段略有差异。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fr first
#define sc second
#define in(x,y,t) (x<=t&&t<=y)
const int N=105;
int n,m,k;
struct node{
    int a,b,c,id;
    bool operator<(node _)const{
        return c<_.c;
    }
}p[N];
struct node2{
    int a,b,c,d;
}dp[N][N][N];
stack<pair<int,int> >ans;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for (int i=1;i<=m;i++)
        cin>>p[i].a>>p[i].b>>p[i].c,p[i].id=i;
    sort(p+1,p+m+1);
    dp[0][0][0]={1,0,0,0};
    for (int i=1;i<=m;i++){
        for (int t=0;t<=p[i].b-p[i].a;t++)
            dp[i][1][t]={1,0,0,t+p[i].a};
        for (int lst=1;lst<i;lst++){
            if (p[i].c<=p[lst].c)
                continue;
            for (int j=2;j<=n;j++)
                for (int t=p[i].a;t<=p[i].b;t++){
                    if (in(p[lst].a,p[lst].b,t-k)&&dp[lst][j-1][t-k-p[lst].a].d+t>dp[i][j][t-p[i].a].d)
                        dp[i][j][t-p[i].a]={dp[lst][j-1][t-k-p[lst].a].a,lst,t-k,dp[lst][j-1][t-k-p[lst].a].d+t};
                    if (t%k==0&&in(p[lst].a,p[lst].b,t/k)&&dp[lst][j-1][t/k-p[lst].a].d+t>dp[i][j][t-p[i].a].d)
                        dp[i][j][t-p[i].a]={dp[lst][j-1][t/k-p[lst].a].a,lst,t/k,dp[lst][j-1][t/k-p[lst].a].d+t};
                }
        }
    }
    int mx=0;
    for (int i=n;i<=m;i++)
        for (int t=p[i].b-p[i].a;t>=0;t--)
            if (dp[i][n][t].a)
                mx=max(mx,dp[i][n][t].d);
    for (int i=n;i<=m;i++)
        for (int t=p[i].b-p[i].a;t>=0;t--)
            if (dp[i][n][t].a&&dp[i][n][t].d==mx){
                cout<<"YES\n";
                int id=i,num=t+p[i].a;
                node2 now=dp[i][n][t];
                for (int x=1;x<=n;x++){
                    ans.push({id,num});
                    num=now.c,id=now.b;
                    now=dp[id][n-x][now.c-p[now.b].a];
                }
                while (ans.size()){
                    cout<<p[ans.top().fr].id<<' '<<ans.top().sc<<'\n';
                    ans.pop();
                }
                return 0;
            }
    cout<<"NO\n";
    return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF119C)

我无言以对，代码能力还是差。

思路不算很难，但是代码难度有点大。

肯定是先对 $c$ 进行排序，设 $dp_{i,j,k}$ 表示以第 $i$ 个学科为末尾，选择 $j$ 个学科，$i$ 学科获得 $k$ 个作业的最大作业量。

这样设的原因是方便我们到时候输出方案。（如果你设前 $i$ 个就，很难输出）。

但是 $a_i,b_i$ 可以很大，用 map 存储的话也不行，因为这样带个 $\log$，时间不能承受。

但是我们观察到 $b_i-a_i\le 100$ 的性质，所以不妨把这段空间对应的数平推到 $[0,b_i-a_i]$ 上去代替表示即可。

这样 $k$ 的空间就被我们解决。这是本题用到平推空间的一个寄巧。

转移方程是显然的，设 $\max(j-1,1)\le l < i$，显然有转移方程：

$$dp_{i,j,k}=\max\{dp_{i,j,k},dp_{l,j-1,\frac{k}{K}}+k ,dp_{i,j-1,k-K}+k\}$$

这里还需要注意一些判断条件。

然后记录方案的话就直接对 $dp_{i,j,k}$ 记录上一步然后递归输出即可。

时间复杂度为 $O(nm^2\times \max(b_i-a_i))$

~~我的代码不存在可读性。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =105;
#define int long long
struct node{
	int a,b,c,id;
}Nw[200];
int dp[N][N][N],lst[N][N][N],lst1[N][N][N];
bool vis[N][N][N];
bool cmp(node A,node B){
	return A.c<B.c;
}
void Print(int i,int j,int k){
	if(j==0)	return ;
	Print(lst[i][j][k-Nw[i].a],j-1,lst1[i][j][k-Nw[i].a]);
	printf("%lld %lld\n",Nw[i].id,k);
}
signed main(){
	int n,m,K;
	scanf("%lld%lld%lld",&n,&m,&K);
	for(int i=1;i<=m;i++)	scanf("%lld%lld%lld",&Nw[i].a,&Nw[i].b,&Nw[i].c),Nw[i].id=i;
	sort(Nw+1,Nw+m+1,cmp);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=min(i,n);j++)
			for(int k=Nw[i].a;k<=Nw[i].b;k++){
				if(j==1){
					dp[i][j][k-Nw[i].a]=max(dp[i][j][k-Nw[i].a],k),vis[i][j][k-Nw[i].a]=true; 
				}
				for(int l=max(1ll,j-1);l<i;l++){
					if(Nw[i].c<=Nw[l].c||l<j-1)	continue;
					if(k%K==0&&(k/K>=Nw[l].a&&k/K<=Nw[l].b)){	
						if(vis[l][j-1][k/K-Nw[l].a]==true)	vis[i][j][k-Nw[i].a]=true;
						if(dp[i][j][k-Nw[i].a]<dp[l][j-1][k/K-Nw[l].a]+k&&vis[l][j-1][k/K-Nw[l].a]==true)	lst[i][j][k-Nw[i].a]=l,lst1[i][j][k-Nw[i].a]=k/K,
							dp[i][j][k-Nw[i].a]=max(dp[i][j][k-Nw[i].a],dp[l][j-1][k/K-Nw[l].a]+k),vis[i][j][k-Nw[i].a]=true;
						}	
					if(k-K>0&&(k-K>=Nw[l].a&&k-K<=Nw[l].b)){
						if(vis[l][j-1][k-K-Nw[l].a]==true)	vis[i][j][k-Nw[i].a]=true;
						if(dp[i][j][k-Nw[i].a]<dp[l][j-1][k-K-Nw[l].a]+k&&vis[l][j-1][k-K-Nw[l].a]==true)	lst[i][j][k-Nw[i].a]=l,lst1[i][j][k-Nw[i].a]=k-K,
							dp[i][j][k-Nw[i].a]=max(dp[i][j][k-Nw[i].a],dp[l][j-1][k-K-Nw[l].a]+k),vis[i][j][k-Nw[i].a]=true;
					}
				}
			}
		}
	int ans=0;
	for(int i=1;i<=m;i++)
		for(int j=Nw[i].a;j<=Nw[i].b;j++)
			ans=max(ans,dp[i][n][j-Nw[i].a]);
//	cout<<ans<<endl;
//	cout<<dp[1][1][7]<<endl;
	if(ans==0)	puts("NO"),exit(0);
	for(int i=1;i<=m;i++)
		for(int j=Nw[i].a;j<=Nw[i].b;j++){
			if(ans==dp[i][n][j-Nw[i].a])	cout<<"YES"<<endl,Print(i,n,j),exit(0);
		}
//	cout<<"NO"<<endl;
	return 0;
}
// dp[i][j][k] [1,i] chose j , hw k 's max 


```

---

