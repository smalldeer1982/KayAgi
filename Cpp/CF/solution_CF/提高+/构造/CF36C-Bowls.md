# Bowls

## 题目描述

有一次Petya心情特别好以至于他想帮妈妈洗碗。水槽中有n个脏的碗。从几何角度看，每个碗都像一个钝头的圆锥。我们可以忽略碗壁和底的厚度。Petya自然地将碗一个个碟起来，也就是说它们的中轴重合（见图）。你将得到Petya洗碗的顺序。请求出碗碟的高度，也就是从最底下的碗的底到最顶上的碗的顶的距离。
![CF36C Bowls](https://cdn.luogu.org/upload/vjudge_pic/CF36C/efa1edfc5c322f108d0b1dc2cca2e87816dc54d2.png)

## 样例 #1

### 输入

```
2
40 10 50
60 20 30
```

### 输出

```
70.00000000
```

## 样例 #2

### 输入

```
3
50 30 80
35 25 70
40 10 90
```

### 输出

```
55.00000000
```

# 题解

## 作者：超级玛丽王子 (赞：2)

很接近实际生活的一道计算几何题——叠碗问题。

~~作为良心出题人，我可能会给这道题加上什么气压的影响之类的~~

# Solution
考虑叠碗的情况。大致就是以下三类：
1. 底对底
2. 侧或沿对底
3. 侧或沿对沿或侧

我们可以按照这三类设计一个二分答案，搜到接触点的高度，再加上碗高即可。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back 
#define REP(i,n) for(int i=0;i<(n);i++)  

int h[4096], r[4096], R[4096];
double H[4096], H2[4096];

double g(int h1, int r1, int R1, int h2, int r2, int R2) {
    if (r2 >= R1)
        return h1;
    double L = 0, R = h1;
    while (R - L > 1e-7) {
        double M = R + L;
        M /= 2;
        int suc = 1;
        double D1 = 1.0 * (R1 - r1) * M / h1 + r1;
        suc &= D1 >= r2;
        if (h2 + M <= h1) {
            double D2 = 1.0 * (R1 - r1) * (M + h2) / h1 + r1;
            suc &= D2 >= R2;
        } 
        else {
            double D2 = 1.0 * (R2 - r2) * (h1 - M) / h2 + r2;
            suc &= R1 >= D2;
        }
        if (suc) R = M;
        else L = M;
    }
    return L;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N;
    scanf("%d", &N);
    REP(i, N) scanf("%d%d%d", h + i, r + i, R + i);
    double res = 0;
    H[0] = 0, H2[0] = h[0];
    REP(i, N - 1) {
        double t = res;
        for (int j = i; j >= 0; j--) {
            if (res > H2[j]) break;
            double tmp = g(h[j], r[j], R[j], h[i + 1], r[i + 1], R[i + 1]);
            t = max(t, tmp + H[j]);
        }
        res = t;
        H[i + 1] = res;
        H2[i + 1] = max(H2[i], res + h[i + 1]);
    }
    res = 0;
    REP(i, N) res = max(res, h[i] + H[i]);
    printf("%.6lf\n", res);
    return 0;
}

```

---

## 作者：L_zaa_L (赞：0)

如果一个碗能被另一个碗卡住，这个卡住的位置肯定比其他所有碗能卡住高，于是我们来讨论一下两个碗会被怎样卡住。

通过分类讨论我们可以发现两个碗如果叠在一起一共有 $5$ 种情况：

定义：$l_x$ 表示 $x$ 这个碗的侧边的斜率，$h_x,r_x,R_x$ 如题面所述。

我们上面的杯子称为 $A$，下面的杯子称为 $B$。

![](https://picx.zhimg.com/80/v2-15807bf23ecb2b71e97f09c7d63f48e2_720w.png)

- 对于第一种的情况如果想要满足，肯定需要 $R_A>R_B\land r_A<R_B\land l_A> l_B$，然后既然想要正好卡在 $B$ 的碗顶上，那么下面那个地方肯定不能碰到 $B$ 的底部（不然就是第 $5$ 种情况），根据相似可以得到 $\frac{(R_B-r_A)}{R_A-r_A}\times h_A\le h_B$。

- 对于第二种情况如果想要满足首先要满足 $R_A<R_B\land l_A> l_B$，然后他的下面也不能碰到底部，也可以根据相似推出限制条件。

- 然后第三种情况有 $l_A<l_B\land r_A>r_B$，就没有然后了。

- 第四种情况更简单，只需要满足 $r_A>R_B$ 就可以了。

- 第五种就直接判断是不是在上面 $4$ 种情况，不是就只有这种情况了。

然后我们可以通过上面五种情况分别计算出每种情况上面的那个碗的碗底到下面那个碗的碗底高度。

## Code

```cpp

#include<bits/stdc++.h>
#define int long long
#define double double
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e4+5,Mod=998244353;
const double eps=1e-10;
bool SSS;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
//inline void Add(int &x,int y){(x=x+y+Mod)%Mod;}
typedef __int128_t i128;
i128 _base=1;
inline int mol(int x){return x-Mod*(_base*x>>64);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int n;
double h[N],r[N],R[N];
double hight[N],xs[N];
inline double l(int x){
	return 1.0*(R[x]-r[x])/h[x];
}
inline double check(int A,int B){//A到B的距离
	if(r[A]>=R[B]){//第四种
		return h[B];
	}
	if(l(A)>=l(B)&&R[B]<=R[A]&&(R[B]-r[A])*h[A]<h[B]*(R[A]-r[A])){//第一种情况
		return h[B]-(double)(R[B]-r[A])/(double)(R[A]-r[A])*(double)h[A];
	}
	if(l(A)>=l(B)&&R[A]<=R[B]&&r[B]<=R[A]&&(R[A]-r[B])*h[B]>=h[A]*(R[B]-r[B])){//第二种
		return (double)(R[A]-r[B])/(double)(R[B]-r[B])*(double)h[B]-h[A];
	}
	if(l(A)<l(B)&&r[A]>=r[B]){	//第三种
		return (double)(r[A]-r[B])/(double)(R[B]-r[B])*(double)h[B];
	}
	return 0;//最后一种
}
inline void solve(){
	n=read();
	For(i,1,n) h[i]=read(),r[i]=read(),R[i]=read();
	double ans=h[1];
	int l=1;
	For(i,2,n){
		Rof(j,i-1,1){
			double p=check(i,j);
			p+=(double)hight[j];
			if(hight[i]<p) hight[i]=p;
		}//找到最高能托起它的
		double p=check(i,l)+(double)hight[l];
		if(hight[i]<p) hight[i]=p;
		ans=max(ans,(hight[i]+h[i]));
		//~ cout<<l<<endl;
	}
	cout<<fixed<<setprecision(10)<<(double)ans<<endl;
	return;
}
bool TTT;
signed main(){
	_base=(_base<<64)/Mod;
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	int T=1;
	while(T--){solve();}
#ifdef LOCAL
	Debug("\nMy Memories: %lldMib\n",(int)(&TTT-&SSS)/1024/1024);
    Debug("\nMy Time: %.3lfs\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}

```

---

