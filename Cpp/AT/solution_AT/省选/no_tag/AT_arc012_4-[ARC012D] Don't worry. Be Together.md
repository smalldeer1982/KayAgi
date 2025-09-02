# [ARC012D] Don't worry. Be Together

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc012/tasks/arc012_4

$ N $ 人の人間が、二次元平面上の格子点にいます。  
 各ターンごとに、各自が上下左右いずれかの方向へちょうど $ 1 $ だけ進みます。  
 これを繰り返し、$ T $ ターンの終了時に全員が同時に原点 $ (0,0) $ へ集まるようにしたいです。  
 その時の各自の進み方の組み合わせが何通りあるかを、 $ modulo $ で割った余りを出力してください。  
 どのようにしても全員が同時に原点に集まることができない場合は、 $ 0 $ を出力してください。  
 入力は以下の形式で標準入力から与えられる。

> $ N $ $ T $ $ modulo $ $ x_1 $ $ y_1 $ $ x_2 $ $ y_2 $ : : $ x_N $ $ y_N $

- $ 1 $ 行目に、人間の数を表す整数 $ N(1≦N≦100,000) $ 、移動ターン数を表す整数 $ T(1≦T≦100,000) $ 、正整数 $ modulo $ が、空白区切りで与えられる。
- $ 2 $ 行目から $ N $ 行間における $ i+1(1≦i≦N) $ 行目には、$ i $ 番目の人がいる座標を表す整数 $ x_i,\ y_i $ が、空白区切りで与えられる。
 
 テストデータには以下の $ 3 $ 種類のテストデータセットのいずれかに含まれており、それぞれのデータセットに含まれているテストデータは、以下に示すように与えられる整数 $ modulo,\ x_i,\ y_i $ の範囲が異なっている。  
 あるテストデータセットに含まれているテストデータ全てに対して正しい解を出力できると、それ以外のテストデータセットで不正解を出力しても以下のように部分点が与えられる。  
- part1 ( $ 40 $ 点) : $ modulo=1,000,000,007 $、$ -1,000,000≦x_i,\ y_i≦1,000,000 $
- part2 ( $ 30 $ 点) : $ 1≦modulo≦1,000,000,007 $、$ -100≦x_i,\ y_i≦100 $
- part3 ( $ 30 $ 点) : $ 1≦modulo≦1,000,000,007 $、$ -1,000,000≦x_i,\ y_i≦1,000,000 $
 
 ちょうど $ T $ ターン後に全員が原点に集まるための進み方が何通りあるかを、$ modulo $で割った余りを出力せよ。  
 どのようにしても全員が同時に原点に集まることができない場合は、$ 0 $ を出力せよ。  
 出力は標準出力におこない、末尾には改行をいれること。  
```

2 2 1000000007
1 1
-1 -1
```

 ```

4
```

- $ x $ 座標が正の方向を右、$ y $ 座標が正の方向を上とします。
- $ 2 $ ターン目に二人が原点に辿り着く方法は、以下の $ 4 $ 通りとなります。
- $ 1 $人目が、下・右の順に移動し、$ 2 $人目が、上・左の順に移動する。
- $ 1 $人目が、下・右の順に移動し、$ 2 $人目が、左・上の順に移動する。
- $ 1 $人目が、右・下の順に移動し、$ 2 $人目が、上・左の順に移動する。
- $ 1 $人目が、右・下の順に移動し、$ 2 $人目が、左・上の順に移動する。
 

```

4 4 1000000007
0 4
4 0
-4 0
0 -4
```

 ```

1
```

- それぞれ、まっすぐ原点に向かって進むパターン以外存在しないので、答えは $ 1 $ 通りとなります。
 
```

1 6 10
0 0
```

 ```

0
```

- $ 6 $ ターンで原点から原点に戻ってくる方法は $ 400 $ 通りあるので、 $ 10 $ で割った余りの $ 0 $ を出力します。
 
```

3 7 12345
2 3
0 1
-2 -1
```

 ```

11415
```

# 题解

## 作者：HomuraAkemi (赞：3)

感谢鱼鱼的帮助/qq

答案显然为多个

$$[x^ay^b](x+x^{-1}+y+y^{-1})^T$$

之积。

神仙的转化就是，**注意到**，

$$x+x^{-1}+y+y^{-1}=(x+y)(1+1/xy)$$

然后所求即为


$$[x^ay^b]\sum_{0\le i\le T}{T\choose i} x^iy^{T-i}\sum_{0\le j\le T}{T\choose j} (xy)^{-j}$$

注意到，当且仅当，$i-j=a$ 且 $T-i-j=b$ 时有贡献。解至多有一个，不难直接求出。

对任意模数的处理是平凡的（Dirichlet 定理），这里不再赘述。

启示是，在处理此类问题时可以考虑因式分解，让形式变得更好看。另一篇题解提供了几何意义上理解的角度。

Madoka 最可爱啦/qq 期待和你 be together（

---

## 作者：Francais_Drake (赞：1)

### 题意
有 $n$ 个点，第 $i$ 个点的横纵坐标为 $(x_i,y_i)$。每一步可以向上/下/左/右走一步。设 $f(i)$ 为从原点开始走 $T$ 步刚好能到达 $(x_i,y_i)$ 的方案数，求 $\prod_{i=1}^n f(i)\bmod mod$。$1\le mod\le 10^9+7;n,T\le 10^5;|x_i|,|y_i|\le 10^6$。
### 解法
如果考虑在 $x/y$ 轴方向正向/反向走了多少步的情况，则和式难以化简。（虽然也可以推出正确的结论）

考虑将整个坐标系逆时针旋转 45 度，将某个点 $(x,y)$ 对应到新坐标系上的 $(y+x,y-x)$，则在原图上向左/上/右/下走一步对应了在新的坐标系上向左上/右上/右下/左下走一步，新的坐标系上每次可以从某个点 $(x,y)$ 走到 $(x\pm 1,y\pm 1)$ 的位置。此时每走一步对横纵坐标的贡献互不影响，所以可以把横纵坐标的变化分别独立出来看，则走 $T$ 步到新坐标系上的点 $(X,Y)$ （令 $X,Y\ge 0$）的方案数为 $\binom{T}{\frac{T-X}2}\binom{T}{\frac{T-Y}2}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/c4cegtkd.png)

注意模数不一定为质数，考虑将最后的答案写成 $\prod_{i=2}i^{c_i}$ 的形式，则上面的组合数可以拆成某个阶乘除以某个阶乘的形式，乘/除某个阶乘等效于对 $c$ 前缀加/前缀减，最后处理整个答案时将每个 $i$ 分解质因数以快速计算 $\prod i^{c_i}$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000010;
int n,m,i,j,t,x,y,u,w,a=1;
int v[maxn],p[maxn],d[maxn];
long long pw[maxn];
inline int Pow(int d,long long z){
	int r=1;
	do{
		if(z&1) r=(1LL*r*d)%m;
		d=(1LL*d*d)%m;
	}while(z>>=1);
	return r;
} 
int main(){
	for(i=2;i<maxn;++i){
		if(!v[i]) v[i]=p[++t]=i; 
		for(j=1;j<=t;++j){
			u=p[j];
			if(v[i]<u||i*u>=maxn) break;
			v[i*u]=u;
		}
	} 
	scanf("%d%d%d",&n,&t,&m);
	while(n--){
		scanf("%d%d",&x,&y);
		u=x+y; w=x-y;
		if(u<0) u=-u;
		if(w<0) w=-w;
		if(u<w) swap(u,w); 
		if(t<u||(u^t)&1){
			printf("0\n");
			return 0;
		}
		x=(t-u)>>1; y=(t-w)>>1;
		d[t]+=2; --d[x]; --d[y];
		--d[t-x]; --d[t-y];
	}
	x=0;
	for(i=maxn-1;i;--i){
		if(!(x+=d[i])) continue;
		for(u=i;u!=1;){
			w=v[u]; y=0;
			while(v[u]==w) ++y,u/=w;
			pw[w]+=1LL*y*x;
		}
	}
	for(i=2;i<maxn;++i){
		if(!(u=pw[i])) continue;
		a=(1LL*a*Pow(i,u))%m;
	}
	printf("%d\n",a);
	return 0;
}
```

---

## 作者：N_z_ (赞：0)

来一手大力推式子。

不妨设 $X,Y\ge0$，枚举 $i$ 表示一共向上多少步，我们可以得到：

$$
\begin{aligned}
&\sum_i \binom{T}{X+2i}\binom{X+2i}{i}\binom{T-X-2i}{\frac{T-X-2i+Y}{2}}\\
=&\sum_i\frac{T!}{i!(X-i)!(\frac{T-X-2i+Y}{2})!(\frac{T-X-2i-Y}{2})!}\\
=&\sum_i\frac{T!\binom{\frac{T-X-Y}{2}}{i}\binom{\frac{T+X+Y}{2}}{X+i}}{(\frac{T-X-Y}{2})!(\frac{T+X+Y}{2})!}\\
=&\frac{T!}{(\frac{T-X-Y}{2})!(\frac{T+X+Y}{2})!}\sum_i\binom{\frac{T-X-Y}{2}}{i}\binom{\frac{T+X+Y}{2}}{X+i}\\
=&\frac{T!}{(\frac{T-X-Y}{2})!(\frac{T+X+Y}{2})!}\sum_i\binom{\frac{T-X-Y}{2}}{i}\binom{\frac{T+X+Y}{2}}{\frac{T-X+Y}{2}-i}\\
=&\frac{T!}{(\frac{T-X-Y}{2})!(\frac{T+X+Y}{2})!}\binom{T}{\frac{T-X+Y}{2}}\\
=&\frac{(T!)^2}{(\frac{T-X-Y}{2})!(\frac{T-X+Y}{2})!(\frac{T+X-Y}{2})!(\frac{T+X+Y}{2})!}
\end{aligned}
$$

于是处理一下阶乘与阶乘逆即可。

<https://atcoder.jp/contests/arc012/submissions/65100477>

---

## 作者：_fairytale_ (赞：0)

首先每个人独立，对于每个人我们求的是这种形式的式子：

$$
\begin{aligned}
&[x^{a}y^{b}](x+\dfrac{1}{x}+y+\dfrac{1}{y})^T\\
=&[x^{a}y^{b}](x+y)^T(1+\dfrac{1}{xy})^T\\
\end{aligned}
$$

转化成，从 $(0,0)$ 开始要么往上要么往右走 $T$ 步，然后还有 $T$ 步要么不动要么往左下角走，到 $(a,b)$ 的走法方案数。

显然前 $T$ 步要走到 $y=x-a+b$ 这条直线上，我们又有 $x+y=T$，所以最后走到的 $(x,y)$ 是唯一的，解得

$$\begin{cases}
x=\dfrac{a-b+T}{2}\\
y=\dfrac{b-a+T}{2}\\
\end{cases}$$

最后走的 $T$ 步贡献是 ${T\choose x-a}$，所以单个人的方案数是 ${T\choose x}{T\choose x-a}$。最后把所有人的方案数乘起来即可。

对组合数的处理，可以先处理出每个数在答案中的指数，然后计算每个质数在答案中的指数。

```cpp
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>T>>mod;
	auto mulfac=[&](int x,int op)->void{
		c[1]+=op;
		c[x+1]-=op;
	};
	auto mulC=[&](int n,int m)->void{
		if(n<0||m<0||n<m){
			cerr<<"invalid\n";
			cout<<"0\n";
			exit(0);
		}
		mulfac(n,1),mulfac(m,-1),mulfac(n-m,-1);
	};
	for(int i=1,a,b;i<=n;++i){
		cin>>a>>b;
		a=abs(a),b=abs(b);
		if(a<b)swap(a,b);
		if((a-b+T)%2){
			cout<<"0\n";
			return 0;
		}
		int x=(a-b+T)/2; 
		mulC(T,x),mulC(T,x-a);
	}
	rep(i,2,1000000){
		c[i]+=c[i-1];
		int x=i;
		for(int j=2;j*j<=x;++j){
			if(x%j==0){
				while(x%j==0)x/=j,a[j]+=c[i]; 
			}
		}
		if(x!=1)a[x]+=c[i];
	}
	int ans=1;
	rep(i,1,1000000)ans=1ll*ans*qp(i,a[i])%mod;
	cout<<ans<<'\n';
	return 0;
}
```

---

