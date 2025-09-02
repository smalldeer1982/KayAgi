# Three Sons

## 题目描述

**题意简述**

给定一个 $n\times m$ 的长方形矩阵，第 $(i,j)$ 个方格上面有一个值 $c_{i,j}$。现在要将矩阵分成三部分，要求两条切割线必须互相平行且与边线平行，不能切开网格，使得切出的三部分每个部分所包含的方格的值的总和分别为 $A$，$B$，$C$。求有多少种切法。

## 样例 #1

### 输入

```
3 3
1 1 1
1 1 1
1 1 1
3 3 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 5
1 1 1 1 1
2 2 2 2 2
3 6 6
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 3
1 2 3
3 1 2
2 3 1
5 6 7
```

### 输出

```
0
```

# 题解

## 作者：Strelitzia_ (赞：4)

## 题目大意

给出一个 $n\times m$ 的矩阵 $C$，将矩阵分成三部分，要求两条切割线必须互相平行且与边线平行，求分开后的三部分矩阵分别的和正好是给定的 $a,b,c$ 的切割方案有多少种。

------------

## 思路

前置：二维前缀和

首先，注意到要讨论切割后的矩阵的和，我们考虑用二维前缀和维护。这个数据范围用二维的数组完全开的下。

注意到 $1\le n,m\le 50$，我们分类讨论横着切还是竖着切，然后暴力枚举所有方案，一共 $(n^2+m^2)$ 种。对于每种情况，我们的二维前缀和可以 $O(1)$ 查询，总体时间复杂度就是 $O(n^2+m^2)$，完全能过。

另外，数据没有保证 $n,m$ 全都大于 $3$。显然，如果行/列数小于 $3$，肯定是不能沿着行/列切的。这一点要特判一下。还有，**这题要用到 ```freopen```**。

剩下的就是裸裸的二维前缀和板子了。放一下主程序代码：

```cpp
signed main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			sum[i][j]=a[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//预处理二维前缀和数组
		}
	}
	int x=read(),y=read(),z=read();
	if(n>=3){//分类讨论
		for(int i=1;i<n;i++){
			for(int j=i+1;j<n;j++){
				int _a=sum[i][m],_b=sum[j][m]-sum[i][m],_c=sum[n][m]-sum[j][m];//查询
				if(_a==x&&_b==y&&_c==z) ans++;
				else if(_a==y&&_b==x&&_c==z) ans++;
				else if(_a==z&&_b==y&&_c==x) ans++;
				else if(_a==x&&_b==z&&_c==y) ans++;
				else if(_a==y&&_b==z&&_c==x) ans++;
				else if(_a==z&&_b==x&&_c==y) ans++;//直接判断
			}
		}
	}
	if(m>=3){
		for(int i=1;i<m;i++){
			for(int j=i+1;j<m;j++){
				int _a=sum[n][i],_b=sum[n][j]-sum[n][i],_c=sum[n][m]-sum[n][j];
				if(_a==x&&_b==y&&_c==z) ans++;
				else if(_a==y&&_b==x&&_c==z) ans++;
				else if(_a==z&&_b==y&&_c==x) ans++;
				else if(_a==x&&_b==z&&_c==y) ans++;
				else if(_a==y&&_b==z&&_c==x) ans++;
				else if(_a==z&&_b==x&&_c==y) ans++;
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：RainSpark (赞：2)

# 题意

给定一个 $n\times m$ 的长方形矩阵，用两条割线将其分成三部分（不能切开网格），使得被分成的三部分的每个部分所包含的方格的值的总和分别为 $A,B,C$，求有多少种切法。

# 思路

本题的数据范围 $1\le n,m\le 50$，范围并不大，可以直接暴力循环枚举每一种可能的分割情况。

由于每次分割都是整行整列分割，所以计算和的时候一定会将一整行或一整列都加上。

这样可以直接建立两个一维前缀和数组，分别记录每行、每列的前缀和，然后 $O(1)$ 查询，注意两层循环的下标。程序复杂度为 $O(nm+n^2+m^2)$。

# 坑点

1. 此前缀和非彼前缀和（$S_{i,j}=F_{j}-F_{i-1}$）。由于每次计算是从行与行、列与列之间分割，而不是常规前缀和那样从一个点到另一个点。所以这道题中的前缀和计算式子为 $S_{i,j}=F_{j}-F_{i}$。

2. 每次暴力枚举的三个总和与 $A,B,C$ 的对应不唯一，所以要用 6 个 `if` 讨论所有情况。

3. 本题需按照 Codeforces 题面的要求开启 `freopen` 文件输入输出（洛谷题面没有说），否则会爆零！

# 代码

```cpp
#include<iostream>
#include<cstdio>
#define N 55
using namespace std;
int n, m, g[N][N];
int a, b, c;
int sumi[N],//记录每行的前缀和
    sumj[N];//记录每列的前缀和
int ans = 0;
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> g[i][j];
		}
	}
	cin >> a >> b >> c;
	for (int i = 1; i <= n; i++) { //计算每行的前缀和
		for (int j = 1; j <= m; j++) {
			sumi[i] += g[i][j]; //将单行的值累加
		}
		sumi[i] += sumi[i - 1]; //计算前缀和
	}
	for (int j = 1; j <= m; j++) { //计算每列的前缀和
		for (int i = 1; i <= n; i++) {
			sumj[j] += g[i][j];
		}
		sumj[j] += sumj[j - 1];
	}
	int s1, s2, s3;
	if (n >= 3) {
		for (int i = 1; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				s1 = sumi[i];
				s2 = sumi[j] - sumi[i];
				s3 = sumi[n] - sumi[j]; //计算和
				if (s1 == a && s2 == b && s3 == c) //对应不唯一，分六种情况讨论
					ans++;
				else if (s1 == a && s2 == c && s3 == b)
					ans++;
				else if (s1 == b && s2 == a && s3 == c)
					ans++;
				else if (s1 == b && s2 == c && s3 == a)
					ans++;
				else if (s1 == c && s2 == a && s3 == b)
					ans++;
				else if (s1 == c && s2 == b && s3 == a)
					ans++;
			}
		}
	}
	if (m >= 3) {
		for (int i = 1; i < m; i++) {
			for (int j = i + 1; j < m; j++) {
				s1 = sumj[i];
				s2 = sumj[j] - sumj[i];
				s3 = sumj[m] - sumj[j];
				if (s1 == a && s2 == b && s3 == c)
					ans++;
				else if (s1 == a && s2 == c && s3 == b)
					ans++;
				else if (s1 == b && s2 == a && s3 == c)
					ans++;
				else if (s1 == b && s2 == c && s3 == a)
					ans++;
				else if (s1 == c && s2 == a && s3 == b)
					ans++;
				else if (s1 == c && s2 == b && s3 == a)
					ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```
[AC 记录（CF）](https://codeforces.com/problemset/submission/120/161844325)

[AC 记录（洛谷）](https://www.luogu.com.cn/record/77964644)

---

## 作者：Jerrlee✅ (赞：1)

## 题意
给定一个 $n \times m$ 的长方形矩阵，第 $(i,j)$ 个方格上面有值 $c_{i,j}$。可以横或竖着把矩阵切成三部分，不能切开网格，使切出的三部分每个部分所包含的方格的值的总和分别为 $A$，$B$，$C$。求有多少种切法。
## 思路
首先 $n,m \leq 50$，可以直接暴力枚举每一种切法的值并与 $A$，$B$，$C$ 比较。

计算值嘛，搞个前缀和就行了。要注意的是枚举 $n$ 和 $m$，需要两个前缀和数组。

注意一下每次循环的下标就好了，按照题目要求开 `freopen` 文件输入输出。

细节都讲完了，具体看代码吧。
## 代码
（这份代码是从 @piggy123 巨佬的错误代码改正过来的）
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[505][505],sml[505],smc[505],smll[505],smcc[505];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ll n,m;
    cin >> n >> m;
    for (ll i=1;i<=n;i++){
        for (ll j=1;j<=m;j++){
            cin >> a[i][j];
            smc[i]+=a[i][j];
            sml[j]+=a[i][j];
        }
    }
    for (ll i=1;i<=n;i++){
        smcc[i]=smcc[i-1]+smc[i];
    }
    for (ll i=1;i<=m;i++){
        smll[i]=smll[i-1]+sml[i];
    }
    ll x,y,z,ans=0;
    cin >> x >> y >> z;
    if (n>=3){// 特判建议加上，毕竟 n,m 可以有一个数小于三的
        for (ll i=1;i<n;i++){
            for (ll j=i+1;j<n;j++){
                // 1 to i,i+1 to j, j+1 to n
                ll a=smcc[i],b=smcc[j]-smcc[i],c=smcc[n]-smcc[j];
                //cout << i << " "<< j << " "<< a << " "<< b << " "<< c << endl;
                if(a==x&&b==y&&c==z)ans++;
                else if(a==y&&b==x&&c==z)ans++;
                else if(a==y&&b==z&&c==x)ans++;
                else if(a==z&&b==x&&c==y)ans++;
                else if(a==x&&b==z&&c==y)ans++;
                else if(a==z&&b==y&&c==x)ans++;
            }
        }
    }
    if (m>=3){
        for (ll i=1;i<m;i++){
            for (ll j=i+1;j<m;j++){
                // 1 to i,i+1 to j, j+1 to n
                ll a=smll[i],b=smll[j]-smll[i],c=smll[m]-smll[j];
//              cout << i << " "<< j << " "<< a << " "<< b << " "<< c << endl;
                if(a==x&&b==y&&c==z)ans++;
                else if(a==y&&b==x&&c==z)ans++;
                else if(a==y&&b==z&&c==x)ans++;
                else if(a==z&&b==x&&c==y)ans++;
                else if(a==x&&b==z&&c==y)ans++;
                else if(a==z&&b==y&&c==x)ans++;
            }
        }
    }
    cout << ans;// notice the value of i and j!
}
```
[AC 记录（洛谷）](https://www.luogu.com.cn/record/70747051)

[AC 记录（CF）](http://codeforces.com/contest/120/submission/148532354)

---

## 作者：HMZHMZHMZ (赞：1)

## 题意

给定一个 $ n \times m $ 的矩阵，有两种分割方式，分别为横着切两刀和竖着切两刀。问有多少种情况切完以后所得的 $ 3 $ 个子矩阵的值分别为给定的 $ 3 $ 个数。

## 思路

发现 $ n $，$ m \leq 50 $ ，复杂度基本不用担心。

题目中要求子矩阵和，自然想到二维前缀和。

于是题目变得非常简单。每一次只需枚举切哪里，然后利用二位前缀和计算子矩阵中的数字和，再判断是否相等即可。

时间复杂度 $ O ( n ^ 2 + m ^ 2 ) $ ，可以轻松跑过。

## 代码

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=101;
int a[N][N],n,m,s[N][N],b[N],c[N],ans;
inline int read(){
    int s=0,f=0;
    char ch=getchar();
    while(ch>'9'||ch<'0') f|=ch=='-',ch=getchar();
    while(ch<='9'&&ch>='0'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
    return f?-s:s;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    n=read(),m=read();
    for(register int i=1;i<=n;++i){
        for(register int j=1;j<=m;++j){
            a[i][j]=read();
            s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];//计算二位前缀和，s[i][j]表示是以(1,1)为左上角，(i,j)为右下角的矩阵值的和
        }
    }
    for(register int i=1;i<=3;++i) b[i]=read();
    sort(b+1,b+3+1);//sort一遍方便比较，不过好像没什么必要（
    for(register int i=1;i<n;++i){
        for(register int j=i+1;j<n;++j){
            c[1]=s[i][m],c[2]=s[j][m]-s[i][m],c[3]=s[n][m]-s[j][m];//计算矩阵值
            sort(c+1,c+3+1);
            bool flag=1;
            for(register int l=1;l<=3;++l) if(b[l]!=c[l]) flag=0;
            if(flag) ans++;//判断是否合法
        }
    }
    for(register int i=1;i<m;++i){//同理
        for(register int j=i+1;j<m;++j){
            c[1]=s[n][i],c[2]=s[n][j]-s[n][i],c[3]=s[n][m]-s[n][j];
            sort(c+1,c+3+1);
            bool flag=1;
            for(register int l=1;l<=3;++l) if(b[l]!=c[l]) flag=0;
            if(flag) ans++;
        }
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：BerlandsFD (赞：0)

本题的数据极小，所以我们只用暴力枚举即可。为了使运算更简单，我们使用二维前缀和记录和。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
int n, m;
int a, b, c;
int sum[N][N];

int f(int x, int y, int z)
{
	if ((x == a && y == b && z == c) || (x == b && y == c && z == a) || (x == c && y == a && z == b) || (x == c && y == b && z == a) || (x == a && y == c && z == b) || (x == b && y == a && z == c)) return 1;
	else return 0;
}

int main()
{
    freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			int tmp;
			cin >> tmp;
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + tmp;
		}
	cin >> a >> b >> c;
	int ans = 0;
	for (int i = 2; i < m; i++)
	{
		for (int j = i + 1; j <= m; j++)
		{
			int x = sum[n][i - 1];
			int y = sum[n][j - 1] - sum[n][i - 1];
			int z = sum[n][m] - sum[n][j - 1];
			if (f(x, y, z)) ans++;
		}
	}
	for (int i = 2; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			int x = sum[i - 1][m];
			int y = sum[j - 1][m] - sum[i - 1][m];
			int z = sum[n][m] - sum[j - 1][m];
			if (f(x, y, z)) ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：CarroT1212 (赞：0)

题意题面已经说得很清楚了。

$n,m$ 都很小，我们可以分沿着行切和沿着列切两种情况，枚举两条切割线的位置，看看分出的三个部分的方格值总和是否分别为 $A,B,C$，最后输出满足条件的方案数即可。

然后是一些细节问题：

在算分成的三个部分的方格值总和时，可以使用二维前缀和维护矩阵和，$O(1)$ 即可得出三个值；

在算分出的三个部分的方格值总和是否分别为 $A,B,C$ 时，一种情况一种情况写非常麻烦，我们就可以先把 $A,B,C$ 的值从小到大排序，再在枚举时将分成的三个部分的方格值总和也从小到大排序，这样处理，到时算的时候直接一个一个比较就可以了；

最后也是最重要的：这题要打 freopen……（输入：`input.txt`，输出：`output.txt`）

------------

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rnt register long long
using namespace std;
const ll N=57,M=57;
ll n,m,ans;
ll mp[N][M],sum[N][M],a[3],x[3];
ll cal(ll x1,ll y1,ll x2,ll y2) { //二维前缀和计算矩阵和
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}
void horizontal() {
	for (rnt i=1;i<n;i++) {
		for (rnt j=i+1;j<n;j++) {
			x[0]=cal(1,1,i,m);
			x[1]=cal(i+1,1,j,m);
			x[2]=cal(j+1,1,n,m);
			sort(x,x+3); //排序
			if (x[0]==a[0]&&x[1]==a[1]&&x[2]==a[2]) ans++;
		}
	}
}
void vertical() {
	for (rnt i=1;i<m;i++) {
		for (rnt j=i+1;j<m;j++) {
			x[0]=cal(1,1,n,i);
			x[1]=cal(1,i+1,n,j);
			x[2]=cal(1,j+1,n,m);
			sort(x,x+3); //一样排序
			if (x[0]==a[0]&&x[1]==a[1]&&x[2]==a[2]) ans++;
		}
	}
}
int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout); //害惨无数人
	cin>>n>>m;
	for (rnt i=1;i<=n;i++) {
		for (rnt j=1;j<=m;j++) {
			cin>>mp[i][j];
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+mp[i][j]; //二维前缀和初始化
		}
	}
	cin>>a[0]>>a[1]>>a[2];
	sort(a,a+3); //排序
	horizontal(); //两种情况
	vertical();
	cout<<ans;
	return 0;
}
```

---

