# Square Filling

## 题目描述

You are given two matrices $ A $ and $ B $ . Each matrix contains exactly $ n $ rows and $ m $ columns. Each element of $ A $ is either $ 0 $ or $ 1 $ ; each element of $ B $ is initially $ 0 $ .

You may perform some operations with matrix $ B $ . During each operation, you choose any submatrix of $ B $ having size $ 2 \times 2 $ , and replace every element in the chosen submatrix with $ 1 $ . In other words, you choose two integers $ x $ and $ y $ such that $ 1 \le x < n $ and $ 1 \le y < m $ , and then set $ B_{x, y} $ , $ B_{x, y + 1} $ , $ B_{x + 1, y} $ and $ B_{x + 1, y + 1} $ to $ 1 $ .

Your goal is to make matrix $ B $ equal to matrix $ A $ . Two matrices $ A $ and $ B $ are equal if and only if every element of matrix $ A $ is equal to the corresponding element of matrix $ B $ .

Is it possible to make these matrices equal? If it is, you have to come up with a sequence of operations that makes $ B $ equal to $ A $ . Note that you don't have to minimize the number of operations.

## 说明/提示

The sequence of operations in the first example:

 $ \begin{matrix} 0 & 0 & 0 & & 1 & 1 & 0 & & 1 & 1 & 1 & & 1 & 1 & 1 \\ 0 & 0 & 0 & \rightarrow & 1 & 1 & 0 & \rightarrow & 1 & 1 & 1 & \rightarrow & 1 & 1 & 1 \\ 0 & 0 & 0 & & 0 & 0 & 0 & & 0 & 0 & 0 & & 0 & 1 & 1 \end{matrix} $

## 样例 #1

### 输入

```
3 3
1 1 1
1 1 1
0 1 1
```

### 输出

```
3
1 1
1 2
2 2
```

## 样例 #2

### 输入

```
3 3
1 0 1
1 0 1
0 0 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 2
0 0
0 0
0 0
```

### 输出

```
0
```

# 题解

## 作者：引领天下 (赞：7)

这个题实际上就是裸的暴力……~~然而我仍然在WA了3次，有一次还是样例WA了~~

思路：既然题目没有要求操作次数最少，那么我们**能操作的地方就操作一次**，这样最后没有被操作到的就只能是无法操作的地方了。

细节看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool a[55][55],b[55][55];
vector<pair<int,int> > ans;
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++)scanf("%d",&a[i][j]);
    for (int i=1;i<n;i++)
    for (int j=1;j<m;j++)if(a[i][j]&&a[i+1][j]&&a[i][j+1]&&a[i+1][j+1])ans.push_back(make_pair(i,j)),b[i][j]=b[i+1][j]=b[i][j+1]=b[i+1][j+1]=1;//如果a[i][j]、a[i][j+1]、a[i+1][j]和a[i+1][j+1]都为1的话我们才能在(i,j)操作一次，更新b
    for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++)if(b[i][j]^a[i][j])return !printf("-1");//如果a和b有不一样的地方那肯定就是无解了
    printf("%d\n",ans.size());
    for (vector<pair<int,int> >::iterator it=ans.begin();it!=ans.end();it++)printf("%d %d\n",it->first,it->second);//输出
}
```

---

## 作者：pzc2004 (赞：5)

[题目传送门](https://www.luogu.org/problem/CF1207B)

题目大意：给出一个n行m列的01矩阵（即目标矩阵），原始矩阵也为n行m列的01矩阵且所有元素都为0，每次可以选择一个点(x,y)，$1\le x\le n-1,1\le y\le m-1$，将点(x,y),(x+1,y),(x,y+1),(x+1,y+1)变为1，问是否可以通过若干次操作到达目标矩阵，若不能，输出-1，若可以，则输出到达目标矩阵的步数k和每步进行操作的点的坐标，注意，k不需要最小，k不应超过2500。

因为n,m小于等于50，而k最大为2500，所以我们可以给每个点都进行一次操作，~~也就是可以乱搞~~。我们用一个变量s记录原始矩阵应变为1但还没变为1的元素的数量，二位数组a记录目标矩阵，b记录原始矩阵的每个点是否被操作过，c记录原始矩阵当前的状态。

只要s大于0，就扫一遍原始矩阵，若找到一个点没被操作过，并且该点进行操作后和目标矩阵吻合（就是会被改动的点在目标矩阵中都为1），就进行操作并记录，若找不到这样一个点就输出-1，最后输出即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[55][55],b[55][55],c[55][55],k,x[2505],y[2505],s;//x,y记录每次操作的点的坐标
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){scanf("%d",&a[i][j]);if(a[i][j]==1){s++;}}//记录s
	while(s)
	{
		k++;
		bool bb=0;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m;j++)
			{
				if(a[i][j] && a[i+1][j] && a[i][j+1] && a[i+1][j+1] && b[i][j]==0)//如果该点可以进行操作就操作
				{
					x[k]=i;//记录该点坐标
					y[k]=j;
					b[i][j]=1;
					if(c[i][j]==0)s--;//如果被改动的点原来是零就将s--
					if(c[i+1][j]==0)s--;
					if(c[i][j+1]==0)s--;
					if(c[i+1][j+1]==0)s--;
					c[i][j]=c[i+1][j]=c[i][j+1]=c[i+1][j+1]=1;//全部改成1
					bb=1;
					break;
				}
			}
			if(bb)break;
		}
		if(!bb){printf("-1");return 0;}//如果无法进行操作就输出-1
	}
	printf("%d\n",k);//输出
	for(int i=1;i<=k;i++)printf("%d %d\n",x[i],y[i]);
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1207B Square Filling 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1207B)
### 分析
方法：暴力

我们可以循环除边界以外的所有点，判断这个点以及这个点附近的点（见题目描述）在目标数组中是否为 $1$。如果它们都是 $1$，则将全零数组变为 $1$，并将当前的那个点存入答案数组中。

操作过后，先看操作数组是否与目标数组相等，如果有一个点不相等，则无解，输出 `-1`。判完无解后先输出操作次数，再输出操作的点，由于 $2\le n,m \le 50$，所以暴力不会超时。

### 代码
```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int a[55][55],b[55][55];
int ans=0,x[3005],y[3005];
int n, m;
int main()
{
    memset(a,0,sizeof a);
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			b[i][j]=read();
		}
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<m;j++)
		{
			if(b[i][j]&&b[i+1][j]&&b[i][j+1]&&b[i+1][j+1])
			{
				x[++ans]=i;
				y[ans]=j;
				a[i][j]=a[i+1][j]=a[i][j+1]=a[i+1][j+1]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]!=b[i][j])
			{
				cout<<-1;
				return 0; 
			}
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)
	{
		cout<<x[i]<<' '<<y[i]<<endl;
	}
	return 0;
}
```


---

## 作者：YangXiaopei (赞：1)

## Solution：

我的思路于题解区的各位大神一样，也是能操作就操作。这里主要讲一下如何判 $-1$ 和 $0$。

$0$ 情况：

全都是 $0$ 则为 $0$。

$-1$ 情况：

每一个点能输出并且有 $1$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f = -1;
int n, m, a[1005][1005];
int x[1000005], y[1000005];
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
			if(a[i][j] == 1){
				f = 0;
			}
		}
	}
	if(f == -1){
		cout << 0;
		return 0;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i][j] == 1 && a[i + 1][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j + 1] == 1){
				f++;
				x[f] = i;
				y[f] = j;
			}
		}
	}
	if(f == 0){
		cout << -1;
		return 0;
	}
	cout << f;
	for(int i =1; i <= f; i++){
		cout << "\n" << x[i] << " " << y[i];
	}
	return 0;
} 
```

完结撒花！

---

## 作者：Konnyaku_ljc (赞：1)

给您一个a矩阵，每次能修改b矩阵中相邻的四个格（b为空矩阵），如何能使b变为a？  
那么，我们枚举a矩阵中为一的数，若a[x][y]为1，并且它右边、下边、右下的数都为1，我们便标记要操作此点，并把此点x、y存下，还要标记这四个点都操作过。  
而当一个为1的点未被操作过并且右边、右下、下边的点GG了，输出~~Good Game~~  
如果我们不标记操作过呢？样例1就GG了~~
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m,a[52][52],ans,x[2505],y[2505];
bool c[52][52];
int main()
{
	cin >> n >> m;
	for ( int i = 1; i <= n; i++ )
		for ( int j = 1; j <= m; j++ ) cin >> a[i][j];
	for( int i = 1; i <= n; i++ )
	    for ( int j = 1; j <= m; j++)
	    {
	    	if ( a[i][j] == 1 )
	    	{
	    		if( a[i+1][j] == 1 && a[i][j+1] == 1 && a[i+1][j+1] == 1 )
	    		{
	    			ans++;//记录
                    x[ans] = i;
                    y[ans] = j;
                    c[i][j] = true;//标记
                    c[i+1][j] = true;
                    c[i][j+1] = true;
                    c[i+1][j+1] = true;
				}
				if( ( a[i+1][j] != 1 || a[i][j+1] != 1 || a[i+1][j+1] != 1 ) && !c[i][j]) 
                {
                    cout << -1 << endl;//特判
                    return 0;
                }
			}
		}
	cout << ans << endl;//输出
	for(int i = 1; i <= ans; i++)
	{
		cout << x[i] << " " << y[i] << endl;
	}
	return 0;
}
```

---

## 作者：FJ_OIer (赞：0)

只要在能操作的地方操作一次，不能操作的地方不操作，最后判断最终数组和目标数组是否相同即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans;
bool a[51][51],b[51][51];
vector<int> x,y;//记录答案
int main(){
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for (int i=1;i<n;i++){
        for (int j=1;j<m;j++){
            if (a[i][j]&&a[i+1][j]&&a[i][j+1]&&a[i+1][j+1]){//可以操作
                b[i][j]=b[i+1][j]=b[i][j+1]=b[i+1][j+1]=1;
                ans++;
                x.push_back(i);
                y.push_back(j);
            }
        }
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (b[i][j]!=a[i][j]){
                cout<<-1;
                return 0;
            }
        }
    }
    cout<<ans<<endl;
    for (int i=0;i<x.size();i++){
        cout<<x[i]<<" "<<y[i]<<endl;
    }
    return 0;
}

```

---

## 作者：WoodReal12 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1207B)

[codeforces 传送门](https://codeforces.com/problemset/problem/1207/B)

本题纯暴力

## 题目大意
给你一个矩阵，问你是否可以将一个一开始全零但同样大小的矩阵变为所给的矩阵。不可以就输出 $-1$，否则先输出操作数量，然后每行输出 $(x_i,y_i)$，表示本次操作选中 $(x,y)$。

## 题目分析
乍一看感觉没有什么想法，但一看数据范围：$2≤n,m≤50$。

这不是纯暴力吗？

## 思路
既然题目说“你不必最小化步骤”，那么我们就在所有可以操作的地方操作一次，最后再验证可否变为输入的矩阵即可。

具体细节请看代码

## 代码

```cpp
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

int a[55][55],b[55][55];//a表示操作的矩阵，一开始是全零的；b表示目标矩阵。
int ans=0,x[3005],y[3005];//ans为操作次数，x存储每次操作的x坐标，y存储每次操作的y坐标  
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>b[i][j];
	memset(a,0,sizeof(a));
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
			if(b[i][j]&&b[i+1][j]&&b[i][j+1]&&b[i+1][j+1]){//判断是否可以操作
				ans++,x[ans]=i,y[ans]=j;
				a[i][j]=a[i+1][j]=a[i][j+1]=a[i+1][j+1]=1;
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!=b[i][j]){//若不相同输出-1
				cout<<-1<<endl;
				return 0; 
			}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)
		cout<<x[i]<<' '<<y[i]<<endl;
	return 0;
}

```

[洛谷 AC 记录](https://www.luogu.com.cn/record/122950140)

[codeforces AC 记录](https://codeforces.com/problemset/submission/1207/220630827)

---

## 作者：HEzzz (赞：0)


首先我们做一个分析，这道题是比赛的第二题，然后我们发现数据只有 $50$，并且不需要输出操作次数最少的方案，最后得出结论，此题做法就是**暴力**。

做法：因为不需要输出操作次数最少的方案，所以我们可以把每一个能执行操作的方格都操作一次，这样如果还是不能变成目标的样子，说明目标无法实现。

代码也很简单，不懂可以看注释。

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl;
int n,m,a[60][60],b[60][60];
vector<pair<int,int> >ans;
int main() 
{
	cin>>n>>m;
	_rep(i,1,n) _rep(j,1,m) cin>>a[i][j];
	_rep(i,1,n-1) _rep(j,1,m-1) 
	{
		if(a[i][j]&&a[i+1][j]&&a[i][j+1]&&a[i+1][j+1])//这个方格能执行操作
		{
			ans.push_back(make_pair(i,j));//计入操作方案中
			b[i][j]=b[i+1][j]=b[i][j+1]=b[i+1][j+1]=1;//更新
		}
	}
	_rep(i,1,n) _rep(j,1,m) if(a[i][j]!=b[i][j]) //最全面的去操作都做不到，即无论如何都不能到达目标
	{
		cout<<"-1\n";//不可行
		exit(0);
	}
	cout<<ans.size()<<endl;//输出操作次数
	for(int i=0;i<ans.size();i++) cout<<ans[i].first<<" "<<ans[i].second<<endl;//以及操作的方块
	return 0;
}
```


---

## 作者：Minakami_Yuki (赞：0)

考场上想了个很$naive$的`dp`，$\color{black}{Q}\color{red}{uank}$大爷提醒后才发现没有最优化。

身败名裂

# 题目链接

[(Luogu)CF1207B Square Filling](https://www.luogu.org/problem/CF1207B)

# 题意简述

给你一个`01`矩阵，每次操作可将一个$2\times 2$的正方形全部赋值为$1$，问你能不能将一个空矩阵变成目标矩阵。

# 解题思想

既然题目中不要求最优解，我们就不需要考虑少覆盖几个正方形。

直接从$(1, 1)$开始枚举，依次考虑以当前点为**左上角**的正方形，如果可以覆盖，直接覆盖并记录路径。

然后在全部覆盖完后将答案矩阵和目标矩阵进行对比，若一致则输出方案。

注意不要越界。

# 参考代码

```c++
#include <cstdio>

const int N = 100;

int a[N][N], b[N][N];

int n, m;

int x[N * N], y[N * N], cnt;

int main() {
    scanf("%d%d", &n, &m);
    for(register int i = 1; i <= n; i++) {
        for(register int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for(register int i = 1; i <= n; i++) {
        for(register int j = 1; j <= m; j++) {
            if(a[i][j] && a[i + 1][j] && a[i][j + 1] && a[i + 1][j + 1] && i + 1 <= n && j + 1 <= m)
                b[i][j] = b[i + 1][j] = b[i][j + 1] = b[i + 1][j + 1] = 1, x[++cnt] = i, y[cnt] = j;
        }
    }
    for(register int i = 1; i <= n; i++)
        for(register int j = 1; j <= m; j++)
            if(a[i][j] != b[i][j])
                return puts("-1"), 0;
    printf("%d\n", cnt);
    for(register int i = 1; i <= cnt; i++) {
        printf("%d %d\n", x[i], y[i]);
    }
    return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

我们可以根据这样一个原则来判断:如果所有A中的1都存在在一个$2* 2$的全为1的矩形中，那么B一定能转化成A,否则,由于存在某些1周围没有1个$2* 2$的全为1的矩阵包括它,那么我们找不到一种不覆盖掉应该为0的位置的操作使这些1的位置变为1。  
为了记录操作,我们还需要确定是哪个矩形覆盖了某个位置,因此我们将所有操作过的矩形的位置标记为1防止重复操作。  
```cpp
#include <cstdio>

using namespace std;

const int sz = 2000000, maxn = 100, maxk = 2510	;
char buf[sz], *p1 = buf, *p2 = buf;
inline char gc() { return p1==p2&&(p2=(p1=buf)+fread(buf,1,sz,stdin), p1==p2)?EOF:*p1++; }
#define gc() getchar()
inline void read(int &x) {
    x = 0; char ch = gc();
    while(ch < '0' || ch > '9') ch = gc();
    while(ch >= '0' && ch <= '9') x = (x<<3)+(x<<1)+(ch&15), ch = gc();
}

int a[maxn][maxn], b[maxn][maxn];
int stp[maxk][2], k = 0;

int main() {
	int nx, ny;
	read(nx); read(ny);
	for(int i = 1; i <= nx; i++)
		for(int j = 1; j <= ny; j++)
			read(a[i][j]);
	for(int i = 1; i <= nx; i++)
		for(int j = 1; j <= ny; j++)
			if(a[i][j] && !b[i][j]) {
				if(a[i-1][j-1]&&a[i-1][j]&&a[i][j-1]) {
					b[i][j] = 1; stp[k][0] = i-1; stp[k++][1] = j-1;
					continue;
				}
				if(a[i-1][j]&&a[i-1][j+1]&&a[i][j+1]) {
					b[i][j] = b[i][j+1] = 1; stp[k][0] = i-1; stp[k++][1] = j;
					continue;
				}
				if(a[i][j-1]&&a[i+1][j-1]&&a[i+1][j]) {
					b[i][j] = b[i+1][j-1] = b[i+1][j] = 1;
					stp[k][0] = i; stp[k++][1] = j-1;
					continue;
				}
				if(a[i][j+1]&&a[i+1][j]&&a[i+1][j+1]) {
					b[i][j] = b[i][j+1] = b[i+1][j] = b[i+1][j+1] = 1;
					stp[k][0] = i; stp[k++][1] = j;
					continue;
				}
				printf("-1\n");
				return 0;
			}
	printf("%d\n", k);
	for(int i = 0; i < k; i++)
		printf("%d %d\n", stp[i][0], stp[i][1]);
	return 0;
}


```

---

