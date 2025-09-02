# Mirror Grid

## 题目描述

You are given a square grid with $ n $ rows and $ n $ columns. Each cell contains either $ 0 $ or $ 1 $ .

In an operation, you can select a cell of the grid and flip it (from $ 0 \to 1 $ or $ 1 \to 0 $ ). Find the minimum number of operations you need to obtain a square that remains the same when rotated $ 0^{\circ} $ , $ 90^{\circ} $ , $ 180^{\circ} $ and $ 270^{\circ} $ .

The picture below shows an example of all rotations of a grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1703E/df4a9e7a944efc8b4d2d665fb77f2a0392653bc5.png)

## 说明/提示

In the first test case, we can perform one operations to make the grid $ \begin{matrix}0 & 1 & 0\\ 1 & 1 & \color{red}{1}\\ 0 & 1 & 0\end{matrix} $ . Now, all rotations of the square are the same.

In the second test case, all rotations of the square are already the same, so we don't need any flips.

## 样例 #1

### 输入

```
5
3
010
110
010
1
0
5
11100
11011
01011
10011
11000
5
01000
10101
01010
00010
01001
5
11001
00000
11111
10110
01111```

### 输出

```
1
0
9
7
6```

# 题解

## 作者：Halberd_Cease (赞：15)

## 题目大意
给你一个 $n\times n$ 的矩阵，仅由 $0$ 和 $1$ 组成，求最少要修改多少个数据才能使该矩阵旋转 $ 0^{\circ} $，$ 90^{\circ} $，$ 180^{\circ} $ 和 $ 270^{\circ} $ 产生的新矩阵完全相同。

## 分析
对于一个点 $P(x,y)$ 在矩阵翻转后对应的点分别为 $P_1(y,n-x+1),P_2(n-x+1,n-y+1),P_3(b-y+1,x)$。

我们要让这个矩阵旋转过后相同，就是要让每一个这样的 $P$ 点和它所对应的点相同。

对于 $n$ 为奇数的矩阵，参考如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fl5ago6b.png)

我们只用枚举绿色区域的值，就可以扩展到不是红色的所有区域，因为红色区域怎么转过后都是自己，所以不用考虑。

对于 $n$ 为偶数的矩阵，参考如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/z1sb3j8w.png)

只用枚举绿色区域就可以将所有区域扩展到。

对于每一个枚举的 $P$ 点，如果它和它扩展的点全部相同答案就不用增加，有一个和其它不同答案就加一，有两个和其它两个不同答案就加二。

最后输出即可。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int mapp[110][110];
int ans;
int n;
void work(int x,int y)
{
	int xx=x-1;int yy=y-1;
	int x_1=1+yy,y_1=n-xx;
	int x_2=n-xx,y_2=n-yy;
	int x_3=n-yy,y_3=1+xx;
	int sum=mapp[x][y]+mapp[x_1][y_1]+mapp[x_2][y_2]+mapp[x_3][y_3];
	if(sum==0||sum==4)ans+=0;
	if(sum==1||sum==3)ans+=1;
	if(sum==2)ans+=2;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n;
		char x;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				cin>>x;
				mapp[i][j]=x-'0';
			}
			
		}
		if(n%2==0)
		{
			for(int i=1;i<=n/2;i++)
			for(int j=1;j<=n/2;j++)
			work(i,j);
		}
		else
		{
			for(int i=1;i<=n/2;i++)
			for(int j=1;j<=n/2+1;j++)
			work(i,j);
		}
		cout<<ans<<'\n';
	}//
}
```

---

## 作者：lizhous (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1703E)  
[本家传送门](https://codeforces.com/contest/1703/problem/E)  
## 分析
旋转时矩阵不变，当且仅当一个数旋转 $4$ 次所经过的点在原矩阵中值相等。我们可以只枚举 $\frac{1}{4}$ 的矩阵，将每个点对应旋转的四个点扫一遍。若 $1$ 的个数多，则将 $0$ 全部改为 $1$，否则将 $1$ 全部改为 $0$。方便起见，代码中枚举的是右上角。四个点位置为 $(i,z),(n-z+1,i),(n-i+1,n-z+1),(z,n -i+1)$，如下图。  
![](https://cdn.luogu.com.cn/upload/image_hosting/klovmmz3.png)   
特别的，当 $n$ 为奇数时，会有中间一个十字扫不到，我们需要特殊处理。  
![](https://cdn.luogu.com.cn/upload/image_hosting/jyk7bfmb.png)  
## code
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<map>
#define int long long
using namespace std;
int t, n, a[1001][1001], cnt1, cnt2, ans;
char ch;
signed main() {
	scanf("%lld", &t);
	while (t--) {
		ans = 0; //初始化
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++) {
			for (int z = 1; z <= n; z++) {
				scanf(" %c", &ch); //输入的是char
				a[i][z] = ch - '0';
			}
		}
		cnt1 = cnt2 = 0; //n可能为0
		for (int i = 1; (i << 1) <= n; i++) { //只枚举行和列的一半
			for (int z = 1; (z << 1) <= n; z++) {
				cnt1 = cnt2 = 0; //初始化
				if (a[i][z] == 1) { //扫四个点，累计
					cnt1++;
				} else {
					cnt2++;
				}
				if (a[n - z + 1][i] == 1) {
					cnt1++;
				} else {
					cnt2++;
				}
				if (a[n - i + 1][n - z + 1] == 1) {
					cnt1++;
				} else {
					cnt2++;
				}
				if (a[z][n - i + 1] == 1) {
					cnt1++;
				} else {
					cnt2++;
				}
				ans += min(cnt1, cnt2); //找少的更改
			}
		}
		cnt1 = cnt2 = 0;
		if (n & 1) { //奇数特殊处理
			for (int i = 1; (i << 1) <= n; i++) {
				cnt1 = cnt2 = 0;
				if (a[i][n / 2 + 1] == 1) { //十字上四个点累加
					cnt1++;
				} else {
					cnt2++;
				}
				if (a[n / 2 + 1][n - i + 1] == 1) {
					cnt1++;
				} else {
					cnt2++;
				}
				if (a[n / 2 + 1][i] == 1) {
					cnt1++;
				} else {
					cnt2++;
				}
				if (a[n - i + 1][n / 2 + 1] == 1) {
					cnt1++;
				} else {
					cnt2++;
				}
				ans += min(cnt1, cnt2); //同样取少
			}
		}
		cout << ans << endl; //输出
	}
}
```
$\texttt{Update}:$ 发现换行有误，进行更改。

---

## 作者：FJ_OIer (赞：3)

首先不难发现，

- 旋转 $90^\circ$ 时，$a_{i,j}=a_{j,n-i+1}$
- 旋转 $180^\circ$ 时，$a_{i,j}=a_{n-i+1,n-j+1}$（上下颠倒左右翻转）
- 旋转 $270^\circ$ 时，$a_{i,j}=a_{n-j+1,i}$

考虑贪心：遍历矩阵，每次答案加上 $a_{i,j}$、$a_{j,n-i+1}$、$a_{n-i+1,n-j+1}$ 和 $a_{n-j+1,i}$ 全部变 $1$ 的修改次数和全部变 $0$ 的修改次数的较小值。

但是如果直接遍历矩阵，会导致重复计算（$a_{i,j}$、$a_{j,n-i+1}$、$a_{n-i+1,n-j+1}$ 和 $a_{n-j+1,i}$ 每个点都会增加一次答案，总共计算四次）。第一是通过观察确定遍历范围或者直接在矩阵上修改，这里不再赘述。第二是因为每个点都计算了四次，直接把最终答案除以 $4$ 即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
char c;
int a[101][101];
int main(){
    cin>>t;
    while (t--){
        cin>>n;
        int ans=0;
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                cin>>c;//注意输入方式
                a[i][j]=c-48;
            }
        }
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                int cnt=a[i][j]+a[j][n-i+1]+a[n-i+1][n-j+1]+a[n-j+1][i];//统计有几个1
                ans+=min(cnt,4-cnt);
            }
        }
        cout<<ans/4<<endl;
    }
    return 0;
}
```

---

## 作者：xiaomuyun (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1703E)

## 题目分析

主要的算法楼上都说了，在纸上推一推可以发现，每次旋转点 $(i,j)$ 分别会变成 $(j,n-i+1)$、$(n-i+1,n-j+1)$、$(n-j+1,i)$。然后我主要想讲的是统计答案的部分。

我们可以把四个坐标上的值加起来，如果说它们都相等，即都为 $1$ 或 $0$ 时，那么和为 $4$ 或 $0$。如果有一个和其他的不一样，那么和为 $1$ 或 $3$，这时需要让答案加一。所以我们可以直接让答案增加 $\min(4-sum,sum)$（$sum$ 是四个数的和）即可。

## 代码实现

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e2+1;
int t,n,a[maxn][maxn],res=0;
int main(){
	scanf("%d",&t);
	while(t--){
		res=0;
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				char ch;
				cin>>ch;
				a[i][j]=(int)ch-'0';
			}
		}
		for(int i=1;i<=(n+1)/2;++i){
			for(int j=1;j<=(n+1)/2;++j){
				int cnt=a[i][j]+a[n-i+1][n-j+1]+a[j][n-i+1]+a[n-j+1][i];
				res+=min(4-cnt,cnt);//更新答案
				a[i][j]=a[n-i+1][n-j+1]=a[j][n-i+1]=a[n-j+1][i]=0;//以防找到这四个点中的另外一个然后再一次更新答案
			}
		}
		printf("%d\n",res);
	}
	return 0;
}
```

---

## 作者：jr_inf (赞：2)

# 题目大意
给出一个由 $0,1$ 组成的矩阵，求最少改变矩阵中的多少个数，使得矩阵旋转 $0^\circ , 90^\circ , 180^\circ , 270^\circ$ 后相同。

# 思路
在一个 $n \times n$ 的矩阵中，对于任意一点 $P(i,j)$ 旋转 $90^\circ , 180^\circ , 270^\circ$ 后的对应点分别位于 $P_1(j,n-i+1),P_2(n-i+1,n-j+1),P_3(n-j+1,i)$。所以只要让矩阵内所有的对应点相等， 矩阵在旋转后就会相同。

但是，当 $n$ 为奇数时，循环就会出现少加或多加的情况，所以需要特判。

综上，对于每个 $P$，求出最少需要改变多少个数，使 $P$ 和他所有的对应点相等， 当 $n$ 是奇数时特判，求和即为答案。

# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
int n,t,a[110][110],ans;
int main()
{
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				char ch;
				cin>>ch;
				a[i][j]=ch-'0';
			}
		}
		for(int i=1;i<=n/2;i++)
		{
			for(int j=1;j<=n/2;j++)
			{
				int cnt=a[i][j]+a[n-j+1][i]+a[j][n-i+1]+a[n-i+1][n-j+1];//求对应点
				ans+=min(cnt,4-cnt);//求和
			}
		}
		if(n%2==1)//特判
		{
			for(int i=1;i<=(n+1)/2;i++)
			{
				int j=(n+1)/2;
				int cnt=a[i][j]+a[n-j+1][i]+a[j][n-i+1]+a[n-i+1][n-j+1];
				ans+=min(cnt,4-cnt);
			}
		}
		cout<<ans<<endl;
	}
}
```


---

## 作者：Symbolize (赞：1)

# 思路
不难发现，对于任意一个点，假设很坐标为 $x$ 纵坐标为 $j$，那么旋转过后的点分别为 $(y,n-x+1),(n-x+1,n-y+1),(n-y+1,x)$。我们可以直接算出旋转后每个点的位置，所以对于每个点，要保证这四个点相同，那就有都为 $1$，和都为 $0$ 两种情况，我们显然是选更改操作少的。为了方便计算，定义一个 $sum$ 变量为这四个点之和，那么全更改为 $0$ 的操作数即为 $4-sum$，那么全更改为 $1$ 的操作数即为 $sum$，那么每次累加的答案就是 $\min(4-sum,sum)$。

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
//#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e3+10;
using namespace std;
int t,n,a[N][N],ans;
char ch;
void getans()
{
	cin>>n;
	rep1(i,1,n)
	{
		rep1(j,1,n)
		{
			cin>>ch;
			a[i][j]=ch-'0';//用int类型存储，方便加和
		}
	}
	rep1(i,1,n+1>>1)//实质上我们只需要遍历左上角，旋转后就都遍历到了
	{
		rep1(j,1,n+1>>1)
		{
			int sum=a[i][j]+a[n-i+1][n-j+1]+a[j][n-i+1]+a[n-j+1][i];//加和
			ans+=min(4-sum,sum);//累加
			a[i][j]=a[n-i+1][n-j+1]=a[j][n-i+1]=a[n-j+1][i]=0;//变为一样的即可
		}
	}
	cout<<ans<<endl;//输出
	ans=0;
	return;
}
signed main()
{
	cin>>t;
	while(t--) getans();//t组数据
	return 0;
}
```

---

## 作者：Jasper08 (赞：0)

我们知道，边长为 $n$ 的正方形中的一个点 $(i,j)$ 旋转 $90^{\circ}$ 后，会变为点 $(j,n-i+1)$。那么点 $(i,j)$ 旋转 $90^{\circ},180^{\circ},270^{\circ}$ 后所得到的点分别为 $(j,n-i+1),(n-i+1,n-j+1),(n-j+1,i)$。我们分别用两个变量 $zero$ 和 $one$ 记录这 $4$ 个点中 $0$ 和 $1$ 的个数，则它们对答案的贡献为 $\min(zero, one)$。

枚举 $i,j\;(1\le i\le \lceil n/2\rceil,1\le j\le \lfloor n/2 \rfloor)$ 即可，时间复杂度 $O(Tn^2)$。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 110;

int t, n, ans;
bool a[N][N];

int main() {
    scanf("%d", &t);
    while (t -- ) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                scanf("%1d", &a[i][j]);
        }

        ans = 0;
        for (int i = 1; i <= ceil(n/2.0); ++i) {
            for (int j = 1; j <= floor(n/2.0); ++j) {
                int zero = 0, one = 0;
                if (a[i][j]) one ++; else zero ++;
                if (a[j][n-i+1]) one ++; else zero ++;
                if (a[n-i+1][n-j+1]) one ++; else zero ++;
                if (a[n-j+1][i]) one ++; else zero ++;
                ans += min(one, zero);
            } 
        }
        printf("%d\n", ans);
    }
    system("pause");
    return 0;
}
```

---

## 作者：OLE_OIer (赞：0)

# CF1703E Editorial

这道题是一道很好的二维数组模拟题。

思路：因为想要求出想顺时针转 $4$ 次 $90\degree$，就可以遍历对应点，求至少要改几个数字。

下面来推导楼上同学说的点旋转公式：

设开始点是在左数第 $i$ 行上数第 $j$ 列，即为 $(i,j)$。

则转一次后变为右数第 $j$ 行上数第 $i$ 列。即为 $(n+1-j,i)$。

则再转一次后相当于是到了右数第 $i$ 行下数第 $j$ 列，即为 $(n+1-i,n+1-j)$。

最后为左数第 $j$ 行下数第 $i$ 列。即为 $(j,n+1-i)$。

最后模拟即可。代码附上：
```
//CF1703E Mirror Grid
#include<bits/stdc++.h>
#define int long long
#define elif else if
using namespace std;
void func(){
	int n,ans=0,tmp;cin>>n;
	char a[110][110]={};
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j) cin>>a[i][j];
	}
	for(int i=1;i<=(n+1)/2;++i){
		for(int j=1;j<=(n)/2;++j){
			tmp=a[i][j]+a[n+1-j][i]+a[n+1-i][n+1-j]+a[j][n+1-i]-4*'0';//看有多少个1
			ans+=min(tmp,4-tmp);//计数
		}
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```
建议写代码前思考一下，把公式推好写草稿纸或记事本上，这样不易错。

---

## 作者：Scorilon (赞：0)

给定一个矩阵，判断最少将多少个格反转后使得旋转零度，九十度，一百八十度，二百七十度相等。

枚举矩阵每个位置是 $0$ 还是 $1$，若已经判断过则跳过，全统 $1$ 和全统 $0$ 取操作数小值。

其中通过观察可得旋转后的位置分别为 $a_{i,j}$，$a_{i,n-j-1}$，$a_{n-i-1,n-j-1}$，$a_{n-j-1,i}$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int t,n,ans;
char a[105][105];//储存矩阵
bool vis[105][105];//判断是否枚举
int main(){
	scanf("%d",&t);
	while(t--){
		memset(vis,0,sizeof(vis));
		ans=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf(" %s",a[i]);
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				int cnt1=0,cnt2=0;
				if(a[i][j]=='0'&&!vis[i][j]){//枚举全为0
					vis[i][j]=true;
					cnt1++;
					if(a[j][n-i-1]=='1') cnt2++;
					else cnt1++;
					vis[j][n-i-1]=true;
					if(a[n-i-1][n-j-1]=='1') cnt2++;
					else cnt1++;
					vis[n-i-1][n-j-1]=true;
					if(a[n-j-1][i]=='1') cnt2++;
					else cnt1++;
					vis[n-j-1][i]=true;
				}
				else if(a[i][j]=='1'&&!vis[i][j]){//枚举全为1
					vis[i][j]=true;
					cnt2++;
					if(a[j][n-i-1]=='0') cnt1++;
					else cnt2++;
					vis[j][n-i-1]=true;
					if(a[n-i-1][n-j-1]=='0') cnt1++;
					else cnt2++;
					vis[n-i-1][n-j-1]=true;
					if(a[n-j-1][i]=='0') cnt1++;
					else cnt2++;
					vis[n-j-1][i]=true;
				}
				ans+=min(cnt1,cnt2);//取更小值
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：Michael1234 (赞：0)

- 本题可以使用**模拟**的思路：

- 读入后，设置一个 $len=\lfloor n\div 2\rfloor $。

- 我们把这些部分（`Y`）一个个算好：

~~~
YYNNN YYNN
YYNNN YYNN
NNNNN NNNN
NNNNN NNNN
NNNNN
~~~

- 每个 `Y` 的推导公式如下，计算以下四个点中有几个 $0$ 和几个 $1$。

1. $mp_{i,j}$
2. $mp_{j,n-i+1}$
3. $mp_{n-j+1,i}$
4. $mp_{n-i+1,n-j+1}$

- 我们每次统计就将答案加上 $0$ 的个数和 $1$ 的个数中少的那个。

- 如果 $n$ 是奇数，我们还需要把这些部分（`Y`）算好。

~~~
NNYNN
NNYNN
NNNNN
NNNNN
NNNNN
~~~

- 每个 `Y` 的推导公式如下，计算以下四个点中有几个 $0$ 和几个 $1$。

1. $mp_{i,len+1}$
2. $mp_{len+1,n-i+1}$
3. $mp_{n-len,i}$
4. $mp_{n-i+1,n-len}$

- 我们每次统计就将答案加上 $0$ 的个数和 $1$ 的个数中少的那个。

- 最后直接输出答案即可。

## CODE

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int t,n,ans,len,cnt0,cnt1;
char mp[N][N];
int main()
{
	cin>>t;
	while(t--)
	{
		ans=0;//清空！
		cin>>n;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>mp[i][j];//读入
		len=n/2;//计算len
		for(int i=1;i<=len;i++)
		{
			for(int j=1;j<=len;j++)
			{
				cnt0=0;
				cnt1=0;//清空！
				if(mp[i][j]=='0') cnt0++;
				else cnt1++;
				if(mp[j][n-i+1]=='0') cnt0++;
				else cnt1++;
				if(mp[n-j+1][i]=='0') cnt0++;
				else cnt1++;
				if(mp[n-i+1][n-j+1]=='0') cnt0++;
				else cnt1++;
				ans+=min(cnt0,cnt1);
			}
		}//按推导公式进行计算第一步
		if(n%2)//当n为奇数
		{
			for(int i=1;i<=len;i++)
			{
				cnt0=0;
				cnt1=0;//清空！
				if(mp[i][len+1]=='0') cnt0++;
				else cnt1++;
				if(mp[len+1][n-i+1]=='0') cnt0++;
				else cnt1++;
				if(mp[n-len][i]=='0') cnt0++;
				else cnt1++;
				if(mp[n-i+1][n-len]=='0') cnt0++;
				else cnt1++;
				ans+=min(cnt0,cnt1);
			}//再次按照公式推导
		}
		cout<<ans<<"\n";//输出
	}
	return 0;
}
~~~

---

