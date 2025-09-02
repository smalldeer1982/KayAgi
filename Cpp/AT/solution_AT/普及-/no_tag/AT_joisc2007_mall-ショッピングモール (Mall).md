# ショッピングモール (Mall)

## 题目描述

### 题目简述

有一个 $n\times m$ 的网格 $c$，你需要在其中选择一个 $b\times a$ 的长方形（不可旋转），使得它满足：

- 长方形内任何一个格子里的数非负；
- 长方形内所有格子的数之和最小。

求出和的最小值。

## 说明/提示

#### 样例 #1 解释

$31+2+4+100+26+21=184$。

### 数据规模与约定

$1\le m,n\le 1000$，$1\le a,b\le 1000$，$-1\le c_{i,j}\le 100$。

# 题解

## 作者：SkokraFX (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/AT_joisc2007_mall)
看到这个数据范围，就可以知道暴力的时间复杂度肯定过不了，直接想其他方法。考虑使用二维前缀和优化。

给大家看一下二维前缀和的推导公式：

`
$$
sum_{i,j}=sum_{i-1,j}+sum_{i,j-1}+sum_{i-1,j-1}+op_{i,j}
$$
`


直接考虑二维前缀和优化，因为题目要求了判断是否有负数，可以直接用两个数组存下来，一个用来判断是否有负数，可知总求和的时间复杂度为 $O(nm)$，可以直接过掉。

接下来在整个矩阵枚举即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 1;
long long sum[N][N],op[N][N];//二位前缀和数组
long long pos[N][N];//判断是否有-1的数组 
int main() {
	long long n,m,a,b;
	cin>>n>>m>>a>>b;
	for(long long i = 1;i <= m;i++) {
		for(long long j = 1; j <= n;j++) {
			cin>>op[i][j];
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + op[i][j]; //二位前缀和推导式 
			pos[i][j] = pos[i - 1][j] + pos[i][j - 1] - pos[i - 1][j - 1];//判断是否有-1 
			if(op[i][j] == -1) pos[i][j] += 1;//如果是就将其加1 
		}
	}
	long long ans = INT_MAX;
	for(long long i = b; i <= m;i++) {
		for(long long j = a; j <= n;j++) {
			long long sum1 = 0;
			sum1 = sum[i][j] - sum[i][j - a] - sum[i - b][j] + sum[i - b][j - a];//定义一个值来计算这个A * B矩阵的和 
			if(pos[i][j] - pos[i][j - a] - pos[i - b][j] + pos[i - b][j - a] == 0) {
				ans = min(sum1,ans);//如果在此区间内没有-1就更新答案 
			}
		}
	}
	cout<<ans<<endl;//最后直接输出答案即可 
	return 0;
}
```

---

## 作者：Alice2012 (赞：1)

二维前缀和模板题。

发现可以通过 $\mathcal{O(nm)}$ 枚举出所有的矩形，但是再通过 $\mathcal{O(nm)}$ 去求得每个矩形的信息不可取。此时使用前缀和优化，分别预处理 $c_{i,j},s_{i,j}$ 表示以 $(1,1)$ 为左上角，$(i,j)$ 为右下角的矩形中，负数的个数以及权值和。然后回到当前矩形，可以通过 $c$ 数组计算出它里面负数的个数 $t1$，若 $t1=0$ 则将当前矩形的权值和 $t2$ 统计入答案中。

最后输出最小值，预处理复杂度和计算所有矩形的贡献的复杂度都是 $\mathcal{O(nm)}$ 可以通过。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int n,m,a,b,ans=1e18;
int c[N][N],s[N][N];
signed main(){
	cin>>m>>n>>b>>a;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			c[i][j]=c[i][j-1]+c[i-1][j]-c[i-1][j-1]+(x<0);
			s[i][j]=s[i][j-1]+s[i-1][j]-s[i-1][j-1]+x;
		}
	}
	for(int i=1;i+a-1<=n;i++){
		for(int j=1;j+b-1<=m;j++){
			int x=i+a-1,y=j+b-1;
			if(c[x][y]-c[x][j-1]-c[i-1][y]+c[i-1][j-1])continue;
			ans=min(ans,s[x][y]-s[x][j-1]-s[i-1][y]+s[i-1][j-1]);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

祝大家 NOIp2024 rp++！

---

## 作者：3Luby3 (赞：1)

## 题目大意
给一个面积为 $nm$ 的矩阵，求矩阵里小矩阵面积为 $ab$ 的和的最小值，且这些数都要非负。

## 思路
这道题考虑**二维前缀和**。

先从一维前缀和推：

首先要明白，前缀和是求一个范围的和。例如一维前缀和中的 $s_4$ 就表示 $a$ 数组从下标 $1$ 到下标 $4$ 的和。

那有什么用？我们就可以轻松的求数组里一个范围的和，只需要知道左端点 $l$ 和右端点 $r$ 即可求出。

现在推公式。我们已经清楚的知道前缀和是一个范围的和，所以当前这一位对应的前缀和就是之前所有范围的和加上这一位的数，如下：

```c++
s[i]=s[i-1]+a[i];//s[i-1]是前面所有的和，a[i]是当前这一位的数字
```

求范围和的时候如下：
```c++
int l,r;//左右端点
cin>>l>>r;
cout<<s[r]-s[l-1];
```
再说为什么 $l$ 要减 $1$ 才能求出。

首先理解 $s_r$ 表示的是 $a_1+a_2+a_3+\dots+a_r$，$s_l$ 表示的是 $a_1+a_2+a_3+\dots+a_l$ 当然 $l$ 一定小于 $r$，我们要求的是 $[l,r]$ 这个区间，如果 $s_r-s_l$ 的话会把 $a_l$ 这一位剪掉，所以是 $s_r-s_{l-1}$

我们再来说说二维前缀和，先画个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/r9hsbhfq.png)

这是一个 $7 \times 7$ 的矩阵，这些红点可以当作是（$a$ 数组中的）数字。

现在有这样的一个框：
![](https://cdn.luogu.com.cn/upload/image_hosting/0kw6yr9a.png)

我们要求 `s[x][y]` 的值，那他就等于（以下为模板）

```cpp
s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];//它附近所有点的前缀和+a[i][j]
```
这里为什么要把 `s[x-1][y-1]` 减去呢？

因为 `s[x-1][y]+s[x][y-1]` 已经加了这一部分了，所以要减去。

下面我们再推如何求一个范围的和。

![](https://cdn.luogu.com.cn/upload/image_hosting/3xieoh19.png)

我们需要知道四个点的坐标才行。对应相减，`s[x-1][y-1]` 会减重复，所以要加上，其它有些要减 $1$ 的可以像推一维前缀和时一样理解，这就不多说了。

```cpp
int x1,x2,y1,y2;
cin>>x1>>x2>>y1>>y2;
cout<<s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
```

公式推完了，最后看题目里有一个要求——非负。我们拿一个数组 $sum2$ 记录即可。


## 温馨提示
- 本题最后输出之后还要换行。

## 代码
```c++
#include<iostream>
#define int long long
using namespace std;
int n,m,a,b,sum[1001][1001],sum2[1001][1001],minn=1e18,x;//minn开大才好计算
signed main(){
	ios::sync_with_stdio(0);//加速黑科技
	cin.tie(0);
	cout.tie(0);
    cin>>n>>m>>a>>b;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>x;
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+x;//求出正常的二维前缀和
            sum2[i][j]=sum2[i-1][j]+sum2[i][j-1]-sum2[i-1][j-1];
            if(x==-1) sum2[i][j]++;//有负数
        }
    }
    for(int i=b;i<=m;i++){
        for(int j=a;j<=n;j++){
            int fanwei=sum[i][j]-sum[i][j-a]-sum[i-b][j]+sum[i-b][j-a];//算出这个范围的前缀和
            if(sum2[i][j]-sum2[i][j-a]-sum2[i-b][j]+sum2[i-b][j-a]==0) minn=min(fanwei,minn);//没有负数，更新答案
        }
    }
    cout<<minn<<endl;//一定要换行！！！
    return 0;
}
```

---

## 作者：jinfanhao (赞：1)

这道题考虑二维前缀和。\
给大家一下二维前缀和的核心。$sum_{i-1,j}+sum_{i,j-1}-sum{i-1,j-1}+op_{i,j}$。\
后面直接判断是否有负数，可以用两个数组 $p,q$ 存下来，一个用来判断是否有负数，一个用来做 $op$ 数组的前缀和。\
时间复杂度 $\Omicron\lparen nm\rparen$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1001;
int n,m,x,y,p[N][N],q[N][N],minx=1e18;
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&x,&y);
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            int op;
            scanf("%lld",&op);
            p[i][j]=p[i-1][j]+p[i][j-1]-p[i-1][j-1]+op; 
            q[i][j]=q[i-1][j]+q[i][j-1]-q[i-1][j-1]; 
            if(op==-1)++q[i][j];
        }
    }
	for(int i=y; i<=m; ++i){
        for(int j=x; j<=n; ++j){
            if(!(q[i][j]-q[i][j-x]-q[i-y][j]+q[i-y][j-x]))minx=min(minx,p[i][j]-p[i][j-x]-p[i-y][j]+p[i-y][j-x]); 
        }
    }
    printf("%lld\n",minx);
    return 0; 
}
```

---

## 作者：封禁用户 (赞：1)

这不是一道二维前缀和大水题吗？

我们可以设两个前缀和数组，$s_{i,j}$ 表示 $\sum_{x,y=0}^{i,j} a_{x,y}$，$neg_{i,j}$ 表示 $\sum_{x,y=0}^{i,j} a_{x,y}=-1$，再依次遍历每一个 $m\times n$ 的矩阵，如果 $neg_{i,j}-neg_{i-b,j}-neg_{i,j-a}+neg_{i-b,j-a}=0$，表示这个矩阵没有 $-1$，就拿这部分的加和，也就是 $s_{i,j}-s_{i-b,j}-s_{i,j-a}+s_{i-b,j-a}$ 和原来的答案比较（取 $\min$），否则忽略掉这部分。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1005;
int s[N][N];
int neg[N][N];
signed main(){
	int n,m,a,b;
	int sum=1e9;
	int ccf;
	scanf("%lld%lld%lld%lld",&n,&m,&a,&b);
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j){
			scanf("%lld",&ccf);
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+ccf;
			neg[i][j]=neg[i-1][j]+neg[i][j-1]-neg[i-1][j-1]+(ccf==-1?1:0);
		}
	}for(int i=b;i<=m;++i){
		for(int j=a;j<=n;++j){
			if(neg[i][j]-neg[i-b][j]-neg[i][j-a]+neg[i-b][j-a]==0)
			sum=min(sum,s[i][j]-s[i-b][j]-s[i][j-a]+s[i-b][j-a]);
		}
	}printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：SMall_X_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_joisc2007_mall)

---

**温馨提示：岛国题要换行！**

需要求一个矩阵的和，考虑二维前缀和。

题目中不允许矩阵中有负数，结合求和的最小值，我们把负数赋为最大值不就行了吗。

接下来就是求二维前缀和了。

基于容斥原理，二维前缀和有如下递推关系：

$$sum_{i,j}=sum_{i-1,j}+sum_{i,j-1}-sum_{i-1,j-1}+c_{i,j}$$

 接下来枚举矩阵的左上角的点，求矩阵里数的和，如图，矩阵里数的和就是绿色框的大矩阵减去红色框小矩阵再减去黄色框的小矩阵，因为蓝色矩阵被减了两次，所以再加上蓝色矩阵，答案就是：

$$sum_{i+a-1,j+b-1}-sum_{i+a-1,j-1}-sum_{i-1,j+b-1}+sum_{i-1,j-1}$$

![](https://cdn.luogu.com.cn/upload/image_hosting/t9ggbfts.png)

## $\texttt{code}$

```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define QAQ cout<<"QAQ\n";
const int MAXN=1e3+5,inf=1e9,mod=1e9+7;
int n,m,a,b,ans=inf;
int c[MAXN][MAXN],sum[MAXN][MAXN];
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>m>>n>>b>>a;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
			if(c[i][j]<0){
				c[i][j]=inf;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+c[i][j];
	    }
	}
	for(int i=1;i+a<=n;i++){
		for(int j=1;j+b<=m;j++){
			ans=min(ans,sum[i+a-1][j+b-1]-sum[i+a-1][j-1]-sum[i-1][j+b-1]+sum[i-1][j-1]);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Ak_hjc_using (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_joisc2007_mall)

### 题意

给出一个 $n$ 行 $m$ 列的矩阵，求出其中的一个长为 $b$，宽为 $a$ 的子矩阵，要求其中的和最小，并且其中的数全部非负。

### 思路

像这种求最大最小加权矩形，我们可以考虑使用二维前缀和来解决，我们可以用两个数组来存储前缀和，一个用来记录和，一个用来记录其中负数的个数，然后我们枚举每一个矩形，求出其中的最小值，其中我们求出值可以用这个公式。

$$sum_{i,j} - sum_{i,j - a} - sum_{i - b,j} + sum_{i - b,j - a}$$

然后我们在判断一下其中是否有负数即可。

不放代码。

---

## 作者：fanfan2012 (赞：0)

二维前缀和练习题。

二维前缀和递推式：

$$\sum^{i,j}_ {1,1}=\sum^{i-1,j}_ {1,1}+\sum^{i,j-1}_ {1,1}-\sum^{i-1,j-1}_ {1,1}+a_{i,j}$$

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010
#define int long long
main(){
    int m, n, x, y, a;
    cin >> n >> m >> x >> y;
    int s[maxn][maxn] = {}, b[maxn][maxn] = {}, ans = 1e18;
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            cin >> a;
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a; 
            b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1]; 
            if(a == -1)b[i][j]++;
        }
    }for(int i = y; i <= m; ++i){
        for(int j = x; j <= n; ++j){
            int f = s[i][j] - s[i][j - x] - s[i - y][j] + s[i - y][j - x]; 
            if(b[i][j] - b[i][j - x] - b[i - y][j] + b[i - y][j - x] == 0)ans=min(f,ans); 
        }
    }cout<<ans<<"\n";
}
```

---

## 作者：didi2012 (赞：0)

明显的二维前缀和。

注意题目中说每个格子都需要非负，所以我们可以用两个数组来存前缀和：所有数以及 $-1$ 的个数。

代码：
```cpp
#include <iostream>
using namespace std;
#define maxn 1005
#define int long long
signed main(){
    int m, n, x, y, a;
    cin >> n >> m >> x >> y;//输入
    int s[maxn][maxn] = {}, b[maxn][maxn] = {}, ans = 1e18;
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            cin >> a;
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a; //二维前缀和递推式
            b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1]; //-1 格子的递推
            if(a == -1)
            {
                b[i][j] += 1; //当 a=-1 时，-1 的前缀和 +1
            }
        }
    }
    for(int i = y; i <= m; ++i){
        for(int j = x; j <= n; ++j){
            int f = s[i][j] - s[i][j - x] - s[i - y][j] + s[i - y][j - x]; //计算出 b*a 的矩阵所有数的和。
            if(b[i][j] - b[i][j - x] - b[i - y][j] + b[i - y][j - x] == 0){ //没有 -1
                ans=min(f,ans); //更新答案
            }
        }
    }
    cout << ans; //输出答案
}
```

---

## 作者：xrtbclx (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_joisc2007_mall)

### part one 暴力解法——
最容易的做法便是 暴力枚举 坐标 $O(nm)$，再进行求和 $O(nm)$，并进行是否有负数的判断 $O(nm)$，总复杂度 $O(n^2m^2)$。由数据范围可知这绝对无法全部 AC。

### part two 前缀和 优化——
考虑使用 前缀和 优化，使求和及负数判断 $O(nm)$ 优化为 $O(1)$，总复杂度为 $O(nm)$。即可 AC！

### 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,a,b;
long long num[1005][1005],s[1005][1005],p[1005][1005],ans=1e9;//定义(记得开 long long)。
int main()
{
    cin >>n>>m>>a>>b;//输入。
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >>num[i][j];//输入。
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + num[i][j];//求和的 前缀和。
            p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1];//负数判断的 前缀和。
            if(num[i][j] == -1)p[i][j]++;
        }
    }
    for(int i = b; i <= m; i++)
    {
        for(int j = a; j <= n; j++)//枚举 坐标。
        {
            long long tmp = s[i][j] - s[i][j-a] - s[i-b][j] + s[i-b][j-a];//求和。
            int bl = p[i][j] - p[i][j-a] - p[i-b][j] + p[i-b][j-a];//求子矩阵中负数的个数。
            if(bl == 0)ans = min(tmp,ans);//更新答案。
        }
    }
    cout<<ans<<"\n";//输出。
    return 0;//AC 结束！
}
```

---

## 作者：xd244 (赞：0)

二维前缀和板子题。

二维前缀和的递推式写一下：$s_{i,j}=s_{i-1,j}+s_{i,j-1}-s_{i-1,j-1}+a_{i,j}$。

所以得到了下列代码：
```cpp
#include<iostream>
using namespace std;
int main(){
    int m,n,x,y;cin>>n>>m>>x>>y;
    long a[1010][1010]={},s[1010][1010]={},minn=1e8;
    for(int c=1;c<=m;c++){
        for(int _c=1;_c<=n;_c++)cin>>a[c][_c],s[c][_c]=s[c-1][_c]+s[c][_c-1]-s[c-1][_c-1]+a[c][_c];//计算前缀和
    }for(int c=y;c<=m;c++){
        for(int _c=x;_c<=n;_c++){
            long f=s[c][_c]-s[c][_c-x]-s[c-y][_c]+s[c-y][_c-x];//子矩阵和
            minn=min(f,minn);
        }
    }cout<<minn<<"\n";//换行！（虽然题目中有了）
}
```
于是光荣满江红了。

为什么呢？看题目中这段话：
>- 长方形内**任何一个格子**里的数非负；
>
>- 长方形内所有格子的数之和最小。

不是总和非负，而是每一个格子非负！

所以还需要用一个数组来统计 -1 的个数，判断矩阵里面有没有非负数。

代码如下：
```cpp
#include<iostream>
using namespace std;
int main(){
    int m,n,x,y;cin>>n>>m>>x>>y;
    long a[1010][1010]={},s[1010][1010]={},num[1010][1010]={},minn=1e8;
    for(int c=1;c<=m;c++){
        for(int _c=1;_c<=n;_c++){
            cin>>a[c][_c];
            s[c][_c]=s[c-1][_c]+s[c][_c-1]-s[c-1][_c-1]+a[c][_c];//二维前缀和
            num[c][_c]=num[c-1][_c]+num[c][_c-1]-num[c-1][_c-1];//统计 -1 个数的前缀和
            if(a[c][_c]==-1)num[c][_c]++;//等于 -1 就把这个格子 +1
        }
    }for(int c=y;c<=m;c++){
        for(int _c=x;_c<=n;_c++){
            long f=s[c][_c]-s[c][_c-x]-s[c-y][_c]+s[c-y][_c-x];
            if(num[c][_c]-num[c][_c-x]-num[c-y][_c]+num[c-y][_c-x]==0)minn=min(f,minn);//判断有没有非负数，没有就更新答案
        }
    }cout<<minn<<"\n";
}
```

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_joisc2007_mall)

### $\texttt{Description}$

在一个 $n \times m$ 的矩阵中，寻找一个 $a \times b$ 的矩阵，要求这个矩阵中没有负数，求出矩阵中和最小的满足条件的矩阵所有数字的和。

### $\texttt{Solution}$

首先想到暴力，但是一看数据范围，$n,m \le 10^3$，非常大，暴力肯定过不了。

再看一眼题目，要求矩阵中所有数字的和，所以我们可以考虑使用二维前缀和来优化我们的代码。

一维前缀和大家都会，那么再放一下二维前缀和的推导式：

$$s_{i,j}=s_{i,j-1}+s_{i,j}+s_{i-1,j}+a_{i,j}$$

其中 $a$ 就是我们输入的矩阵，而 $s$ 是前缀和数组。

接着我们就是判断每个 $a \times b$ 的矩阵中有没有负数即可，如果有的话就跳过，分钟就用这个矩阵的使用数字的总和更新答案。

放一下访问的公式，也就是每个 $a \times b$ 的矩阵的所有数字的总和：

$$sum=s_{i,j}-s_{i,j-a}-s_{i-b,j}+s_{i-b,j-a}$$

公式中的 $sum$ 就是当前矩阵的数字总和。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e3 + 5;
int n, m, x, y;
int a[N][N], s[N][N];
int f[N][N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m >> x >> y;
	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
			f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + (a[i][j] == -1);
		}
	}
	
	int minn = 1e18;
	for (int i = y; i <= m; i++) {
		for (int j = x; j <= n; j++) {
			int sum = s[i][j] - s[i][j - x] - s[i - y][j] + s[i - y][j - x];
			if (f[i][j] - f[i][j - x] - f[i - y][j] + f[i - x][j - y] == 0) minn = min(minn, sum);
		}
	}
	
	cout << minn;
	return 0;
}
```

---

