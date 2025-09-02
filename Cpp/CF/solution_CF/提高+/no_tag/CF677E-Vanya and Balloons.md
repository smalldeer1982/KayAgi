# Vanya and Balloons

## 题目描述

有一个挂着 $n\times n$ 个气球的棋盘，每个气球上有一个数字，数字只可能为 $0,1,2,3$ 中的一个。Vanya 要扎破一个十字形区域内的气球，使得这些气球上的数字乘积最大。

有两种“十字形区域”：一般形和旋转形，例如：

一般形：

```
**o**
**o**
ooooo
**o**
**o**
```

旋转形：

```
o***o
*o*o*
**o**
*o*o*
o***o
```

形式化地讲，十字形可如下定义：给定三个整数 $r,c,d$，满足 $d\leqslant r,c\leqslant n-d+1$。一般形的十字形由所有坐标满足 $|x-r|\cdot|y-c|=0$ 且 $|x-r|+|y-c|<d$ 的气球构成；旋转形的十字形由所有坐标满足 $|x-r|=|y-c|$ 且 $|x-r|<d$ 的气球构成。其中 $x,y$ 分别为气球的横纵坐标。

Vanya 想知道扎破的十字形区域内气球上数字的乘积的最大值，考虑到答案可能很大，故只需要输出答案对 $10^9+7$ 取模后的值。

## 样例 #1

### 输入

```
4
1233
0213
2020
0303
```

### 输出

```
108
```

## 样例 #2

### 输入

```
5
00300
00300
33333
00300
00300
```

### 输出

```
19683
```

## 样例 #3

### 输入

```
5
00003
02030
00300
03020
30000
```

### 输出

```
108
```

## 样例 #4

### 输入

```
5
21312
10003
10002
10003
23231
```

### 输出

```
3
```

## 样例 #5

### 输入

```
5
12131
12111
12112
21311
21212
```

### 输出

```
24
```

# 题解

## 作者：小胖同学 (赞：3)

题目中存在“一般形”和“旋转形”两种十字形。考虑将图旋转 $45$ 度把“旋转形”转化为“一般形”。


![](https://cdn.luogu.com.cn/upload/image_hosting/lrdgbbnz.png)


就像国际象棋有两个象，我们考虑把旋转后的奇数行和偶数行，单独拆出来作为两个新的矩形，计算答案时只需要考虑算原矩形和着两个矩形的“一般形十字”即可。
例如样例 $5$，就可以拆成下图的两个 $5 \times 5$ 和一个 $4 \times 4$ 矩形。


![](https://cdn.luogu.com.cn/upload/image_hosting/60wkfxyy.png)


接下来我们要实现的就是计算“一般形十字”的最值。

枚举每个点为中心点，因为字符只可能是“$0$”,“$1$”,“$2$”或者“$3$”，所以只找到满足到 $4$ 个方向都没到 $0$ 的长度即可。具体可以记 $0$ 个数的前缀和加二分实现。
而后就是找到对于不同中心点如何对比大小，还是因为字符只可能是“$0$”,“$1$”,“$2$”或者“$3$”，每个答案可以别写为 $2^x + 3^y$，我怕会用对数有精度问题，所以果断打开题解。然后发现“[_edge_](https://www.luogu.com.cn/user/208653)”直接用对数算的，所以用了他的 com，具体就 $\times \log_32$ 化为同底数后直接比较指数，即 $2^a \times 3^b$ 比较 $a + b \times \log_23$。

最后对三张图都跑一遍求最值取最大就可以了。

Code:[[Link]](https://www.luogu.com.cn/paste/yljg7p4b)

---

## 作者：_edge_ (赞：0)

思维难度非常低，但是写起来有点搞人的 $2300$。

我们先枚举那个十字中心。

那么枚举这个中心之后一定是尽可能扩展，但是不能扩展到 $0$ 点。

然后这东西可以随手二分长度，统计对角线之类的可以用前缀和。

这时候我们发现，他的乘积稍微有点大，没办法快速比较大小。

我们发现所有的乘积都是 $2^x \times 3^y$。

加入说我们比较 $2^a \times 3^b$ 和 $2^x \times 3^y$，那么必然是作商比较，然后可以约到一些数变成了 $2^c$ 和 $3^z$ 进行比较，取个对数就可以了。

具体的，可以两边同时进行 $\log_2$，变成了 $c$ 和 $z \times \log_{2}^3$ 进行比较大小。

然后统计一下最大值即可。

自认为实现的还算好写给参考一下。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int INF=1e3+5;
const int Mod=1e9+7;
int n;
char Map[INF][INF];
namespace S0{
	int sum[INF][INF],sum1[INF][INF],sum2[INF][INF],sum3[INF][INF];
	void init() {
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) 
				sum[i][j]=sum[i-1][j]+(Map[i][j]=='0');
		}
		
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++)
				sum1[i][j]=sum1[i][j-1]+(Map[i][j]=='0');
		}
		
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				sum2[i][j]=sum2[i-1][j-1]+(Map[i][j]=='0');
		
		for (int i=1;i<=n;i++)
			for (int j=n;j>=1;j--)
				sum3[i][j]=sum3[i-1][j+1]+(Map[i][j]=='0');
	}
};
namespace S2{
	int sum[INF][INF],sum1[INF][INF],sum2[INF][INF],sum3[INF][INF];
	void init() {
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) 
				sum[i][j]=sum[i-1][j]+(Map[i][j]=='2');
		}
		
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++)
				sum1[i][j]=sum1[i][j-1]+(Map[i][j]=='2');
		}
		
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				sum2[i][j]=sum2[i-1][j-1]+(Map[i][j]=='2');
		
		for (int i=1;i<=n;i++)
			for (int j=n;j>=1;j--)
				sum3[i][j]=sum3[i-1][j+1]+(Map[i][j]=='2');
	}
};
namespace S3{
	int sum[INF][INF],sum1[INF][INF],sum2[INF][INF],sum3[INF][INF];
	void init() {
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) 
				sum[i][j]=sum[i-1][j]+(Map[i][j]=='3');
		}
		
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++)
				sum1[i][j]=sum1[i][j-1]+(Map[i][j]=='3');
		}
		
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				sum2[i][j]=sum2[i-1][j-1]+(Map[i][j]=='3');
		
		for (int i=1;i<=n;i++)
			for (int j=n;j>=1;j--)
				sum3[i][j]=sum3[i-1][j+1]+(Map[i][j]=='3');
	}
};

int check(int x,int y,int l) {
	if (x-l+1<=0 || x+l-1>n) return 0;
	if (y-l+1<=0 || y+l-1>n) return 0;
	if (S0::sum[x+l-1][y]-S0::sum[x-l][y]>0) return 0;
	if (S0::sum1[x][y+l-1]-S0::sum1[x][y-l]>0) return 0;
	return 1;
}

int check1(int x,int y,int l) {
	if (x-l+1<=0 || x+l-1>n) return 0;
	if (y-l+1<=0 || y+l-1>n) return 0;
	return S2::sum[x+l-1][y]-S2::sum[x-l][y]+S2::sum1[x][y+l-1]-S2::sum1[x][y-l];
}

int check2(int x,int y,int l) {
	if (x-l+1<=0 || x+l-1>n) return 0;
	if (y-l+1<=0 || y+l-1>n) return 0;
	return S3::sum[x+l-1][y]-S3::sum[x-l][y]+S3::sum1[x][y+l-1]-S3::sum1[x][y-l];
}

pii ans1;
int com(pii x,pii y) {
//	cout<<x.fi<<" "<<x.se<<" "<<y.fi<<" "<<y.se<<" endl\n";
	if (x.fi>=y.fi) x.fi-=y.fi,y.fi=0;
	else y.fi-=x.fi,x.fi=0;
	
	if (x.se>=y.se) x.se-=y.se,y.se=0;
	else y.se-=x.se,x.se=0;
	
	if (x.fi==0 && x.se==0) return 1;
	if (y.fi==0 && y.se==0) return 0;
	if (x.fi && y.se) {
		long double xx=x.fi,yy=y.se*log2(3);
		if (xx<yy) return 1;
		return 0;
	}
	if (x.se && y.fi) {
		long double xx=x.se*log2(3),yy=y.fi;
		if (xx<yy) return 1;
		return 0;
	}
	return 0;
}
int ksm(int x,int y) {
	int ba=x%Mod,ans=1;
	while (y) {
		if (y&1) ans=(ans*ba)%Mod;
		ba=(ba*ba)%Mod;y>>=1;
	}
	return ans;
}
namespace Sub {
	int check(int x,int y,int l) {
		if (x-l+1<=0 || x+l-1>n) return 0;
		if (y-l+1<=0 || y+l-1>n) return 0;
		if (S0::sum2[x+l-1][y+l-1]-S0::sum2[x-l][y-l]>0) return 0;
//		cout<<S0::sum3[3][2]<<" qwe\n";
		if (S0::sum3[x+l-1][y-l+1]-S0::sum3[x-l][y+l]>0) return 0;
		return 1;
	}
	int check1(int x,int y,int l) {
		return S2::sum2[x+l-1][y+l-1]-S2::sum2[x-l][y-l]+S2::sum3[x+l-1][y-l+1]-S2::sum3[x-l][y+l];
	}
	int check2(int x,int y,int l) {
		return S3::sum2[x+l-1][y+l-1]-S3::sum2[x-l][y-l]+S3::sum3[x+l-1][y-l+1]-S3::sum3[x-l][y+l];
	}
	void solve() {
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) {
				int l=0,r=1e9,ans=-1;
				while (l<=r) {
					int Mid=(l+r)>>1;
					if (check(i,j,Mid)) l=(ans=Mid)+1;
					else r=Mid-1;
				}
				if (ans==-1) continue;
//				cout<<i<<" "<<j<<" "<<ans<<" kel\n";
				pii xx={check1(i,j,ans),check2(i,j,ans)};
				if (Map[i][j]=='2') xx.fi--;
				if (Map[i][j]=='3') xx.se--;
//				cout<<xx.fi<<" "<<xx.se<<" "<<ans1.fi<<" "<<check1(3,3,2)<<" qwe\n";
				if (com(ans1,xx)) ans1=xx;
			}
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	int fl=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) {
			cin>>Map[i][j];
			if (Map[i][j]!='0') fl=1;
		}
	if (!fl) {cout<<"0\n";return 0;}
		
	S0::init();S3::init();S2::init();
//	cout<<check(1,1,1)<<" qwe\n";
//	cout<<com({0,2},{2,2})<<" qwe\n";
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) {
			int l=0,r=1e9,ans=-1;
			while (l<=r) {
				int Mid=(l+r)>>1;
				if (check(i,j,Mid)) l=(ans=Mid)+1;
				else r=Mid-1;
			}
			
			if (ans==-1) continue;
			pii xx={check1(i,j,ans),check2(i,j,ans)};
			if (Map[i][j]=='2') xx.fi--;
			if (Map[i][j]=='3') xx.se--;
			if (com(ans1,xx)) ans1=xx;
		}
	
	Sub::solve();
	
	int res=ksm(2,ans1.fi)*ksm(3,ans1.se)%Mod;
	cout<<res<<"\n";
	return 0;
}
```


---

## 作者：xzggzh1 (赞：0)

CF677E 【Vanya and Balloons】

题意：

有一个矩阵，矩阵里只有 $0，1，2，3$ ,求一个乘积最大的十字形（可以横着摆，可以竖着摆放）。

---

看到那么多数的乘积，如果直接纪录因子 $2$ 和 $3$ 的个数，很难比较两个数的大小，因为 $n$ 最大可以有 $10^3$ ，直接算出答案显然不是正确做法。

那么考虑换一种方式比较每个乘积值的大小。

其实很多人看到连乘就会想到取对数，由对数的运算法则可以把许多数的乘积“打下来”，变成许多数的求和。显然地，对数函数在其定义域上单调递增。

所以我们可以用一个数的对数值来代替其原值以方便比较大小。

那么这个问题就可以简化了，把每个数取对，然后乘积变成和，找到最大和的取法，计算答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1E3 + 10;
const int MOD = 1E9 + 7;
char s[MAXN][MAXN];
double p[4][MAXN][MAXN];
int n, a[8][MAXN][MAXN];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    double val[4] = { 0., 0., log(2.), log(3.) };
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            s[i][j] -= '0';
            p[0][i][j] = p[0][i][j - 1] + val[s[i][j]];
            p[1][i][j] = p[1][i - 1][j - 1] + val[s[i][j]];
            p[2][i][j] = p[2][i - 1][j] + val[s[i][j]];
            p[3][i][j] = p[3][i - 1][j + 1] + val[s[i][j]];
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (s[i][j]) {
                a[0][i][j] = a[0][i][j - 1] + 1;
                a[1][i][j] = a[1][i - 1][j - 1] + 1;
                a[2][i][j] = a[2][i - 1][j] + 1;
                a[3][i][j] = a[3][i - 1][j + 1] + 1;
            } else
                a[0][i][j] = a[1][i][j] = a[2][i][j] = a[3][i][j] = 0;
    for (int i = n; i >= 1; --i)
        for (int j = n; j >= 1; --j)
            if (s[i][j]) {
                a[4][i][j] = a[4][i][j + 1] + 1;
                a[5][i][j] = a[5][i + 1][j + 1] + 1;
                a[6][i][j] = a[6][i + 1][j] + 1;
                a[7][i][j] = a[7][i + 1][j - 1] + 1;
            } else
                a[4][i][j] = a[5][i][j] = a[6][i][j] = a[7][i][j] = 0;
    double ans = -1.0;
    int x = 0, y = 0, z = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (!s[i][j])
                continue;

            int l = min(min(a[0][i][j], a[2][i][j]), min(a[4][i][j], a[6][i][j]));
            double res =
                p[0][i][j + l - 1] - p[0][i][j - l] + p[2][i + l - 1][j] - p[2][i - l][j] - val[s[i][j]];
            if (ans < res)
                ans = res, x = i, y = j, z = l;
            l = min(min(a[1][i][j], a[3][i][j]), min(a[5][i][j], a[7][i][j]));
            res = p[1][i + l - 1][j + l - 1] - p[1][i - l][j - l] + p[3][i + l - 1][j - l + 1] -
                  p[3][i - l][j + l] - val[s[i][j]];
            if (ans < res)
                ans = res, x = i, y = j, z = -l;
        }
    if (ans < 0.)
        puts("0");
    else if (z > 0) {
        unsigned ans = s[x][y];
        for (int i = -z + 1; i < z; ++i)
            if (i) {
                ans = ans * s[x][y + i] % MOD;
                ans = ans * s[x + i][y] % MOD;
            }
        printf("%u\n", ans);
    } else {
        unsigned ans = s[x][y];
        for (int i = -z - 1; i > z; --i)
            if (i) {
                ans = ans * s[x + i][y + i] % MOD;
                ans = ans * s[x + i][y - i] % MOD;
            }
        printf("%u\n", ans);
    }
    return 0;
}
```

---

