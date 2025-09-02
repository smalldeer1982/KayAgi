# Find the Spruce

## 题目描述

Holidays are coming up really soon. Rick realized that it's time to think about buying a traditional spruce tree. But Rick doesn't want real trees to get hurt so he decided to find some in an $ n \times m $ matrix consisting of "\*" and ".".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461B/0f830498ab169a471030eeb85fc12c395e76f5ca.png)To find every spruce first let's define what a spruce in the matrix is. A set of matrix cells is called a spruce of height $ k $ with origin at point $ (x, y) $ if:

- All cells in the set contain an "\*".
- For each $ 1 \le i \le k $ all cells with the row number $ x+i-1 $ and columns in range $ [y - i + 1, y + i - 1] $ must be a part of the set. All other cells cannot belong to the set.

Examples of correct and incorrect spruce trees:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461B/2ce2df8e09c4fc74a3e149e5906821e41a5e552f.png)Now Rick wants to know how many spruces his $ n \times m $ matrix contains. Help Rick solve this problem.

## 说明/提示

In the first test case the first spruce of height $ 2 $ has its origin at point $ (1, 2) $ , the second spruce of height $ 1 $ has its origin at point $ (1, 2) $ , the third spruce of height $ 1 $ has its origin at point $ (2, 1) $ , the fourth spruce of height $ 1 $ has its origin at point $ (2, 2) $ , the fifth spruce of height $ 1 $ has its origin at point $ (2, 3) $ .

In the second test case the first spruce of height $ 1 $ has its origin at point $ (1, 2) $ , the second spruce of height $ 1 $ has its origin at point $ (2, 1) $ , the third spruce of height $ 1 $ has its origin at point $ (2, 2) $ .

## 样例 #1

### 输入

```
4
2 3
.*.
***
2 3
.*.
**.
4 5
.***.
*****
*****
*.*.*
5 7
..*.*..
.*****.
*******
.*****.
..*.*..```

### 输出

```
5
3
23
34```

# 题解

## 作者：Lynkcat (赞：5)

我们考虑暴力算法。

$f_{i,j,k}$ 表示 $i,j$ 为根是否能组成 $k$ 高度的三角形，显然只有 $f_{i+1,j-1,k-1}=1$ 且 $f_{i+1,j,k-1}=1$ 且 $f_{i+1,j+1,k-1}=1$ 时，才有 $f_{i,j,k}=1$ 。

这样朴素做时间复杂度是 $\frac{n^2\times m}{8}$ 的，算了一下极限数据是 $1e7$ 级别的，$cf$ 完全能过了，或者你可以用记忆化搜索来完成 $dp$ 的过程，通过剪枝来使时间复杂度更优。

```c++
int n,m,ans,f[3][N][N],a[N][N],s[N][N],T;
string st;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>T;
	while (T--)
	{
		cin>>n>>m;ans=0;
		memset(f,0,sizeof(f));
		for (int i=1;i<=n;i++)
		{
			cin>>st;
			for (int j=0;j<st.length();j++)
				if (st[j]=='*') a[i][j+1]=1,f[1][i][j+1]=1,ans++; else a[i][j+1]=0;
		}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) s[i][j]=s[i][j-1]+a[i][j];
		for (int k=2;k<=n;k++)
		{
			memset(f[k&1],0,sizeof(f[k&1]));
			for (int i=1;i+k-1<=n;i++)
				for (int j=k;j+k-1<=m;j++)
				if (a[i][j])
				{
					if (s[i+1][j+1]-s[i+1][j-2]==3)
						f[k&1][i][j]=f[(k+1)&1][i+1][j-1]&f[(k+1)&1][i+1][j]&f[(k+1)&1][i+1][j+1],ans+=f[k&1][i][j];
				}
		}
		writeln(ans);
	}
}

---

## 作者：封禁用户 (赞：2)

  ## 题意：
  
  题意很好理解，即在一个  $n \times m$ 的字符数组中找松~~鼠~~树。
  
   ## 思路：
   我们可以把松树定义成一个从上到下不断递增的一个二维字符数组，因此，每个   $ * $ 号右面必定有三个 $ * $ 号。
   既然题目要求找松树，那我们就从左向右，从上到下，每遇到一个 $ * $ 号 都向右边相邻的3个点遍历一次，如果为 $ * $ 号，则继续遍历，否则判断 $ * $ 的个数，也就是是否形成松树。
  接着，我们由松树都是从顶端由小到大以次有规律的向下排列得到   ：
  $$dp[x][y]=1+\min(\min(search(x+1,y),search(x+1,y-1)),search(x+1,y+1)$$
  
 即：
 

![](https://cdn.luogu.com.cn/upload/image_hosting/zvwnlfio.png)
         

     
            

Code：
---
```cpp
#include <bits/stdc++.h>//万能头文件 
using namespace std;//命名空间 
const int maxn=510;//因为n*m<=250,000.所以maxn定义为510不会爆 
char mp[maxn][maxn];
int ans,n,m,t; 
int dp[maxn][maxn];
int search(int x,int y){
	if(dp[x][y]) return dp[x][y];
	bool flag=0;//作标记 
	if(x+1<n&&y-1>=0&&y+1<m){
		if((mp[x+1][y]=='*')&&(mp[x+1][y-1]=='*')&&(mp[x+1][y+1]=='*')){//判断点的右、右上、右下是否为‘*’ 
			flag=1;//标记flag为true 
		}
	}
	if(flag) return dp[x][y]=1+min(min(search(x+1,y),search(x+1,y-1)),search(x+1,y+1));//flag为true,执行DP 
	else return dp[x][y]=1;//否则回溯dp为1； 
}
int main()
{
    cin>>t;
    while(t--){
    	memset(dp,0,sizeof(dp));//因为有多组数据，因此每次都将dp数组归零 
    	cin>>n>>m;
    	for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>mp[i][j];
			}
		}
		ans=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(mp[i][j]=='*'){//从*号开始搜索 
					ans+=search(i,j);//搜索 
				}
			}
		}
		cout<<ans<<endl;
	}
    return 0;
}
```
## 完结散花~~~
~~这次好了，管理员大大莫生气~~

---

## 作者：pies_0x (赞：1)

# CF1461B Find the Spruce

如果一棵树以 $(i,j)$ 为树顶，这棵树最高是 $h$，那以 $(i,j)$ 为树顶的松树就有 $h$ 个。

我们以此设计出状态 $dp_{i,j}$，表示以 $(i,j)$ 为树顶的树，最高是多高。

现在还差状态转移方程。

请看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/87d6pvtq.png)

画成三角形可能有点抽象。

如果红色三角形和绿色三角形都达到了最高，那黄色三角形最高为红色三角形的高和绿色三角形的高的较小值加一。

就相当于，以 $(i,j)$ 为树顶的树的最高高度为分别以 $(i+1,j-1)$ 和 $(i+1,j+1)$ 为树顶的最高高度的较小值加一。

所以，我们可以得到状态转移方程：

$$dp_{i,j}=\min(dp_{i+1,j-1},dp_{i+1,j+1})+1$$

当然，转移时有三个地方要判断一下：
1. $(i+1,j-1)$ 是不是“*”；
2. $(i+1,j)$ 是不是“*”；
3. $(i+1,j+1)$ 是不是“*”。

初始化 $dp_{i,j}=1$。

最后写个循环，根据一开始的结论，累加每个点作为树顶时树的最大高度，然后输出即可。

还有一个注意事项，见 Code。

Code:
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

#define N 505

int n,m;
char a[N][N];
int dp[N][N];

signed main()
{
	int tt;
	scanf("%d",&tt);
	while(tt--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				a[i][j]=getchar(),
				j-=(a[i][j]!='.'&&a[i][j]!='*');
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(a[i][j]=='*')
					dp[i][j]=1;
		for(int i=n-1;i>=1;--i)  //要倒序
			for(int j=2;j<m;++j)
				if(a[i][j]=='*'&&a[i+1][j-1]=='*'&&a[i+1][j]=='*'&&a[i+1][j+1]=='*')
					dp[i][j]=min(dp[i+1][j-1],dp[i+1][j+1])+1;
		int ans=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(a[i][j]=='*')
					ans+=dp[i][j];
		printf("%d",ans);putchar('\n');
	}
	return 0;
}/*
1
5 7
..*.*..
.*****.
*******
.*****.
..*.*..
*/
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1461B)

------------

# 题意
给你一个 $n$ 行 $m$ 列由 ```*``` 或者.组成的图形，一个图形高度为 $k$ 时当且仅当满足 $1 \le i \le k$ 时，第 $x+i−1$ 行必须满足在区间 $y−i+1$ 到 $y+i−1$ 全部都是 ```*```。

------------

# 思路
暴力判断当前行是否满足，如果满足我们继续将 $k$ 加大然后继续向下判断，判断 $k$ 的整个过程具有连续性，比如说当 $k = 3$ 时会重复判断 $k = 2$ 时的情况，所以直接继续判断即可。如果不满足则跳出。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,m,sum[505][505];
char str[505][505];
signed main(){
	cin>>T;
	while(T--){
		int ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			getchar();
			for(int j=1;j<=m;j++){
				cin>>str[i][j];
				if(str[i][j]=='*'){
					sum[i][j]=sum[i][j-1]+1;
				}else{
					sum[i][j]=sum[i][j-1];
				}
			}
		}
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=m;j++){
				for(int k=1;;++k){
					int l=i+k-1,l1=j-k+1,r1=j+k-1;
					if(l>n||l1<=0||r1>m){
						break;
					}
					if(sum[l][r1]-sum[l][l1-1]!=2*k-1){
						break;
					}
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
完结撒花~

---

## 作者：过氧化氢_syq0057 (赞：0)

是我傻了，忘了前缀和优化。

暴力题。

从一个 ```*``` 开始找，往下找三个 ```*```，五个 ```*```，每有一层答案加一，不满足了就跳出。

设 $k$ 是松树的层数，则时间复杂度 $O(Tnmk)$，看样子是 $1.25 \times 10^9$ 的，但远远跑不到，差不多 $10^7$ 级别的，能过。

因为题面说了 $\sum n \times m \le 500^2$。

### Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 505;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int T;
int n, m;
char a[N][N];
int sum[N][N];
int ans;
bool check(int x, int l, int r) {
	if (sum[x][r] - sum[x][l - 1] != (r - l + 1)) return 0;//前缀和优化
	return 1;
}
int main() {
	scanf("%d", &T);
	int I, J;
	while (T--) {
		ans = 0;
		scanf("%d%d", &n, &m);
		getchar();
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				a[i][j] = getchar();
			}
			getchar();
		}//字符串读入不要用scanf
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				sum[i][j] = sum[i][j - 1] + (a[i][j] == '*');//前缀和
			}
		}
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				if (a[i][j] == '*') {
					ans++;
					I = 1, J = 1;//能往下几层
					while (j - J >= 1 && j + J <= m && i + I <= n && check(i + I, j - J, j + J))
						ans++, I++, J++;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

完结散花 qaq

---

## 作者：vectorwyx (赞：0)

直接枚举 $x,y,k$。时间复杂度 $O(500^{3})$，但如果在合适的时机 break 就根本跑不满（弱智题）

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=505;
string s[N];
int sum[N][N];

void work(){
	int n=read(),m=read(),ans=0;
	fo(i,1,n) cin>>s[i];
	fo(i,1,n)
		fo(j,1,m) sum[i][j]=sum[i][j-1]+(s[i][j-1]=='*');
	fo(i,1,n)
		fo(j,1,m)
			fo(k,i,n){
				if(j+k-i>m||j-k+i-1<0||sum[k][j+k-i]-sum[k][j-k+i-1]!=2*(k-i)+1) break;
				++ans;
			}
	printf("%d\n",ans);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：LRL65 (赞：0)

预处理 $pre[i][j]$ ，表示第 $i$ 行前 $j$ 个字符有几个为 $*$ 。

然后暴力枚举每个根部点，每往一下行，如果满足 $pre[k][j+(k-i)]-pre[k][j-(k-i)-1]==2*(k-i)+1)$ 答案就可以加1。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,pre[505][505],ans=0;
string a[505];
int main() {
	cin>>t;
	while(t--) {
        ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) {
                pre[i][j]=pre[i][j-1];
                if(a[i][j-1]=='*')pre[i][j]++;
            }
        for(int i=1;i<=n;i++) 
            for(int j=1;j<=m;j++) {
                if(a[i][j-1]=='*') {
                    ans++;
                    for(int k=i+1;k<=n;k++) {
                        if((j+(k-i)<=m&&(j-(k-i)-1)>=0)&&pre[k][j+(k-i)]-pre[k][j-(k-i)-1]==2*(k-i)+1)ans++;
                        else break;
                    }
                }
            }
        cout<<ans<<endl;
	}
}
```


---

