# Table with Letters - 2

## 题目描述

Vasya has recently started to learn English. Now he needs to remember how to write English letters. He isn't sure about some of them, so he decided to train a little.

He found a sheet of squared paper and began writing arbitrary English letters there. In the end Vasya wrote $ n $ lines containing $ m $ characters each. Thus, he got a rectangular $ n×m $ table, each cell of the table contained some English letter. Let's number the table rows from top to bottom with integers from 1 to $ n $ , and columns — from left to right with integers from 1 to $ m $ .

After that Vasya looked at the resulting rectangular table and wondered, how many subtables are there, that matches both following conditions:

- the subtable contains at most $ k $ cells with "a" letter;
- all letters, located in all four corner cells of the subtable, are equal.

Formally, a subtable's definition is as follows. It is defined by four integers $ x_{1},y_{1},x_{2},y_{2} $ such that $ 1<=x_{1}&lt;x_{2}<=n $ , $ 1<=y_{1}&lt;y_{2}<=m $ . Then the subtable contains all such cells $ (x,y) $ ( $ x $ is the row number, $ y $ is the column number), for which the following inequality holds $ x_{1}<=x<=x_{2},y_{1}<=y<=y_{2} $ . The corner cells of the table are cells $ (x_{1},y_{1}) $ , $ (x_{1},y_{2}) $ , $ (x_{2},y_{1}) $ , $ (x_{2},y_{2}) $ .

Vasya is already too tired after he's been writing letters to a piece of paper. That's why he asks you to count the value he is interested in.

## 说明/提示

There are two suitable subtables in the first sample: the first one's upper left corner is cell $ (2,2) $ and lower right corner is cell $ (3,3) $ , the second one's upper left corner is cell $ (2,1) $ and lower right corner is cell $ (3,4) $ .

## 样例 #1

### 输入

```
3 4 4
aabb
baab
baab
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 5 1
ababa
ccaca
ccacb
cbabc
```

### 输出

```
1
```

# 题解

## 作者：_edge_ (赞：3)

这道题目还是有点意思的，只可惜没人来发一篇题解。

首先，我们先枚举一下矩阵的上边界，下边界和左边界，这样已经可以确定两个点的位置了，显然，如果我们选择枚举右边界肯定会 TLE 起飞。

那么我们考虑优化掉这个右边界，相信看题解的各位都应该会二维前缀和来处理这个 `a`，很容易发现这个右边界其实具有单调性，即随着这个左边界不断变大，右边界肯定是只增不减。

因此我们考虑用双指针来维护这个东西，~~你以为这样就好了么？不我们还要考虑**满足四个角的字母相等**。~~

这个东西比较麻烦，因为我们双指针不会一个一个扫，而是直接统计答案的。

那么如何来维护？

我们考虑给它记录一个桶，当前我的左右指针包含的区域，如果满足两个点相等，我们把这两个点的值扔进桶里面，在记录答案的时候，将左边界的那个减到，就维护好了。

只能说多做题才能想到这种思路。

另外，注意一下 long long 以及 freopen。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define int long long 
#define pb push_back
using namespace std;
const int INF=405;
int n,m,a,ans,sum[INF][INF],aa[INF];
char Map[INF][INF];
int f(int x,int y,int xx,int yy) {
    swap(xx,x);swap(y,yy);
    int ll=xx-1,rr=yy-1;
    // if (ll<0) ll=0;if (rr<0) rr=0;
    return sum[x][y]-sum[ll][y]-sum[x][rr]+sum[ll][rr];
}
signed main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%lld %lld %lld",&n,&m,&a);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) {
            scanf(" %c",&Map[i][j]);
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(Map[i][j]=='a');
        }
    // cout<<f(1,3,2,6)<<"\n";
    for (int i=1;i<=n;i++) {
        for (int j=i+1;j<=n;j++) {
            for (int k=0;k<=26;k++) aa[k]=0;
            for (int l=1,p=1;l<=m;l++) {
                if (Map[i][l]!=Map[j][l]) continue;
                while (p<=m && f(i,l,j,p)<=a) {
                    if (Map[j][p]==Map[i][p])
                        aa[Map[j][p]-'a']++;
                    p++;
                }
                aa[Map[i][l]-'a']--;
                if (aa[Map[i][l]-'a']>0) 
                    ans+=aa[Map[i][l]-'a'];
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```


---

## 作者：封禁用户 (赞：2)

## 题解：CF253D Table with Letters - 2

### 解题思路：

首先，我们可以看出这道题在不考虑时间时可以 $O(n^8)$ 枚举端点，并验证。稍加优化，就可以做到 $O(n^4)$ 的。优化方法为直接生成矩形，在此就不多说了。

我们观察数据：$n \le 400$，也就是说最多使用 $O(n^3)$ 或 $O(n^3 \log n)$ 的复杂度。由此，我们可以尝试先枚举一个点，再确定剩下的内容。此时我们可以延申出可行的优化方法：**前缀和**存储 `a` 的个数。

在实际操作中，我们就会发现这个方法不可行，因为如果此时已经用了 $O(n^2)$ 的复杂度，确定了一横一竖两个坐标，此时没有足够简单的方法来简化复杂度 ~~（没有本蒟蒻会的方法）~~。

既然具体思路有错误，但是大方向仍然可取，所以我们可以稍微更改一下方向，先确定两个横向坐标的位置，然后用**双指针**的算法将时间复杂度压到 $O(n^3)$，左右指针分别指这个矩形两个纵向坐标的位置。

接下来，又出现了一个问题：四个角的字母相等这个条件如何满足。我们肯定是没有额外的复杂度去一一判断了，所以可以用**桶**将每个字母出现的位置装下来，在指针移动时进行更新。

### 题目坑点：

- 复杂度卡的比较紧，需要卡常。
- 枚举纵向坐标时不一定保证 $l \le r$，需要判断。
- 要开 **long long**！
- 要加文件读写！

### 参考代码：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2) //这行代码只是为了加速，在正式比赛中使用会被禁赛，洛谷中也会显示编译错误，但是 CF 上可以用。
using namespace std;
long long n , m , k , b[405][405] , c[405][405] , ans , l , r , tmp[30];
char a[405][405];
int get(int p1 , int p2 , int q1 , int q2)
{
	if(p1 > p2) //特判 l > r
	{
		return 0;
	}
	return c[p2][q2] - c[p1 - 1][q2] - c[p2][q1 - 1] + c[p1 - 1][q1 - 1];
}
int main()
{
	freopen("input.txt" , "r" , stdin);
	freopen("output.txt" , "w" , stdout);
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			cin >> a[i][j];
			if(a[i][j] == 'a')
			{
				b[i][j] = 1;
			}
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			c[i][j] += c[i][j - 1] + c[i - 1][j] - c[i - 1][j - 1] + b[i][j];
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = i + 1 ; j <= n ; j++)
		{
			l = 1;
			r = 0;
			memset(tmp , 0 , sizeof(tmp));
			while(l <= m)
			{
				while(get(i , j , l , ++r) <= k)
				{
					if(r > m)
					{
						break;
					}
					if(a[i][r] == a[j][r] && r > 0)
					{
						tmp[a[j][r] - 'a' + 1]++;
					}
				}
				r--;
				if(a[i][l] == a[j][l])
				{
					tmp[a[i][l] - 'a' + 1]--;
					if(l <= r)
					ans += tmp[a[i][l] - 'a' + 1];
				}
				l++;			
			}
		}
	}
	cout << ans;
	return 0;
}
```

### 附件：

文件读写在 `C++` 中的写法：

```cpp
freopen("input.txt" , "r" , stdin);
freopen("output.txt" , "w" , stdout);
```

**感谢阅读！**

---

## 作者：rui_er (赞：1)

发现数据范围只够 $\mathcal O(n^3)$ 的，因此考虑枚举上下左边界。发现“包含不超过 $k$ 个 `a`”是有单调性的，因此可以处理出字母 `a` 的二维前缀和，使用双指针维护左右边界。

具体地，我们枚举上下边界 $u,d$，在移动 $l,r$ 指针的时候记录数组 $buc$，$buc_i$ 表示有多少个 $l\le j\le r$ 满足 $s_{u,j}=s_{d,j}=i$。然后在满足“长宽大于一”且左上、左下字母相等的情况下利用 $buc$ 数组即可统计答案。

注意本题需要文件读写，文件名是 `input.txt` 和 `output.txt`。

```cpp
// Problem: CF253D Table with Letters - 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF253D
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define debug prllf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 405;

ll n, m, k, sum[N][N], buc[26], ans;
char s[N][N];
template<typename T> void chkmin(T &x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T &x, T y) {if(x < y) x = y;}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &k);
	rep(i, 1, n) scanf("%s", s[i]+1);
	rep(i, 1, n) rep(j, 1, m) sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + (s[i][j] == 'a');
	rep(u, 1, n) {
		rep(d, u+1, n) {
			memset(buc, 0, sizeof(buc));
			ll l = 1, r = 1, now = 0;
			while(l < m) {
				while(r <= m && sum[d][r] - sum[u-1][r] - sum[d][l-1] + sum[u-1][l-1] <= k) {
					if(s[u][r] == s[d][r]) ++buc[s[u][r]-'a'];
					++r;
				}
				if(l < r && s[u][l] == s[d][l]) {
					--buc[s[u][l]-'a'];
					now += buc[s[u][l]-'a'];
				}
				++l;
			}
			ans += now;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
给定一个 $n\times m$ 的字符矩阵，求四个角相等的且其中有小于 $k$ 个 `a` 的矩阵个数。

翻译一下输入输出格式。
### 输入格式
第一行输出三个整数 $n$、$m$、$k$。
后 $n$ 行每行 $m$ 个字符，代表给定的字符矩阵。
### 输出格式
输出一行，表示矩阵个数。
### 注意
这道题需要文件读入读写。
## 大体思路
这道题有个相当类似的，相当于板子题的 [P8783](https://www.luogu.com.cn/problem/P8783)，和这道题思路很像，只是这道题还要处理四个角相同的字母。

和上面的题一样，我们相当于维护两条线，困住两行每次线往下滑一个，记录每列的前缀和，每次向右边加，看看 `a` 的数量符不符合小于 $k$ 个即可。

我们在 $O(n^2)$ 枚举 $m$ 的组合的前提下，用双指针来查 $n$ 的组合，$l=1$，$r=1$，比 $k$ 小的往后查，大的把 $l$ 往前提。

关于记录那四个角，我们用一个 map 记录一下 $l$ 和 $r$ 之间的 $i$ 和 $j$ 中有多少个相同的字母对。

下面看代码。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[405][405];
long long sum[405][405];
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='a'){
				sum[i][j]++;
			}
			sum[i][j]+=sum[i][j-1];//前i行第j列的前缀和，每行算自己的 
		}
	}
	long long ans=0;
	for(int i=1;i<=m;i++){//来处理一下行的组合 
		for(int j=i+1;j<=m;j++){
			map<char,int> mp;
			int l=1,r=1,x=0;//双指针查一下满足条件的列组合 
			while(l<=r&&r<=n){//
				x+=sum[r][j]-sum[r][i-1];//现在a的个数 
				while(x>k){//超过了k，l就往前提。 
					x-=sum[l][j]-sum[l][i-1];
					if(a[l][j]==a[l][i]){
						mp[a[l][j]]--;//左端点列的两个端点不行了 
					}
					l++;
				}
				if(a[r][j]==a[r][i]){
					if(mp[a[r][j]]>0){
						ans+=mp[a[r][j]];//如果前面的l有这个字母，且整个矩阵a个数还小于k，有几个ans就加几 
					}
					mp[a[r][j]]++;//右端点新加上来 
				}
				r++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：LiJoQiao (赞：0)

[更好的阅读体验](https://www.cnblogs.com/LiJoQiao/p/18019847)  

本题需要文件读写。如果没过可能是这个原因。  

最朴素的方法是枚举这个矩阵，需要确定矩阵的四条边，来判断是否满足条件，运用二位前缀和计算 `a` 的数量，用前缀和优化后时间复杂度为 $O(n^4)$，不能通过。  

显然一个矩阵的子矩阵的 `a` 的数量小于等于该矩阵的 `a` 的数量。  
由此可以得出，假设一个符合要求的矩阵内部有一个四个角相等的矩阵，那么这个矩阵一定符合要求。  
可以通过这个性质来统计矩阵的数量吗？  

这四个角需要相等的条件也可以看作是两个**同一列的相同字符端点对**相等且对应端点在同一行。  
枚举统计的矩阵的所在行，我们就可以在这个端点对上做文章。  

由于上述性质，我们可以先找出相同字符端点对，利用一个双指针，左端点表示矩阵的左侧的端点对，右端点表示矩阵可能的右侧的端点对，来维护一个 `a` 符合要求的可能的右侧端点对的一个区间。  
我们在统计答案的时候不断累加左开右闭的两个指针的区间、与左指针代表的端点对匹配的右侧端点对个数，同时不断移动左右指针即可。  

这个过程均摊下来是 $O(n)$ 的。程序整体的时间复杂度为 $O(n^3)$，可以通过。  

代码如下。  

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MAXN=400+10,MAXM=400+10;
int n,m,k,sum[MAXN][MAXM],pa[26],pc[MAXM];
char jz[MAXN][MAXM];
ll ans;
int gc(){
    int x=getchar();
    while(x==' '||x=='\r'||x=='\n')x=getchar();
    return x;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            jz[i][j]=gc();
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(jz[i][j]=='a');
        }
    for(int i=1;i<n;++i){
        for(int j=i+1;j<=n;++j){
            int p=0;
            for(int k=1;k<=m;++k){
                if(jz[i][k]==jz[j][k]){
                    pc[++p]=k;
                }
            }
            for(int i1=0;i1<26;++i1)pa[i1]=0;
            int lp=1,rp=1;
            while(lp<p){
                while(rp<p&&
                sum[j][pc[rp+1]]-sum[i-1][pc[rp+1]]-sum[j][pc[lp]-1]+sum[i-1][pc[lp]-1]<=k)
                    {++rp;++pa[jz[j][pc[rp]]-'a'];}
                ans+=pa[jz[j][pc[lp]]-'a'];
                ++lp;
                --pa[jz[j][pc[lp]]-'a'];
                while(rp<lp){++rp;++pa[jz[j][pc[rp]]-'a'];}
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：lizicheng3042 (赞：0)

## 特殊地  
本题需要在提交时在输入前加入以下代码：
```cpp
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```
~~（虽然很奇怪但都是远古题了就谅解一下吧）~~  
## 解题思路
根据题目的数据范围，可知时间复杂度最高不能超过 $O(n^3)$，否则必然超时。  
根据题目信息，我们考虑取维护矩阵的边界信息，但是如果四个边界都维护显然会炸。我们观察给出矩阵所需满足的条件：  
1. 内部的 $a$ 不能超过 $k$ 个。  
2. 四个端点的字母相同。  
我们发现，满足矩阵在上下边界或左右边界确定时具有一定的性质，因为当右边界向右移动时，$a$ 的个数只增不减，而左边界向右移动时，$a$ 的个数只减不增，所以考虑使用双指针维护对于所有左边界，可行的右边界的范围。
## 具体细节
首先，为了快捷地求出区间内 $a$ 的个数，我们需要应用二维前缀和。此外，因为第二个条件，我们需要在指针移动时将符合条件的边界放入桶中（每个桶存对于某个字母来说符合条件的边界数目），并在左指针扫到该边界时累加结果，并将该边界从桶中取出。  
以下为具体代码：  
```cpp
#include<cstdio>
using namespace std;
long long n,m,k,sum[404][404],tong[50],ans;
char ak[404][404];
int get(int x,int x2,int y,int y2)
{
	if(x>x2)
		return 0;
	return sum[x2][y2]-sum[x-1][y2]-sum[x2][y-1]+sum[x-1][y-1];
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int a=1;a<=n;a++)
	{
		scanf("%s",ak[a]+1);
		for(int b=1;b<=m;b++)
		{
			if(ak[a][b]=='a')
				sum[a][b]++;
		}
	}
	for(int a=1;a<=n;a++)//计算二位前缀和
		for(int b=1;b<=m;b++)
		{
			sum[a][b]+=sum[a-1][b]+sum[a][b-1]-sum[a-1][b-1];
		}
	for(int a=1;a<n;a++)
	{
		for(int b=a+1;b<=n;b++)
		{
			int lp=1,rp=0;
			for(int a=1;a<=26;a++)tong[a]=0;
			while(lp<m)
			{
				while(get(a,b,lp,++rp)<=k&&rp<=m)
				{
					if(ak[a][rp]==ak[b][rp]&&rp)//符合条件的边界加入桶
						tong[ak[a][rp]-'a'+1]++;
				}
				rp--;
				if(ak[a][lp]==ak[b][lp])//累加答案
				{
					int c=ak[a][lp]-'a'+1;
					tong[c]--;
					if(lp<=rp)
					ans+=tong[c];
				}
				lp++;				
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

