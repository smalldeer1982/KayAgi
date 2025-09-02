# [ARC003D] シャッフル席替え

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc003/tasks/arc003_4

高橋君が働くAtCoder社では、いつも $ 1 $ つの円形のテーブルの周囲に社員全員で座ってミーティングを行います。  
 それぞれお気に入りの席があるのでいつも席は同じなのですが、今日は席替えをすることにしました。  
 高橋君がランダムに $ 2 $ 人を選び場所を入れ替える動作を決められた回数行った後の席配置が新しい席配置になります。  
 しかし、残念なことにAtCoder社には隣り合わせにしてしまうとミーティング中におしゃべりをしてミーティングを邪魔してしまう $ 2 $ 人組が存在します。  
 高橋君は真面目なので、ミーティングが滞りなく行われるようにそのような $ 2 $ 人組は $ 1 $ 組も隣り合わせにしたくないと思っています。  
 席替えを行った後に、隣り合わせにしてはいけない $ 2 $ 人組が $ 1 $ 組も隣り合わない確率を求めなさい。 入力は以下の形式で与えられる。

> $ N $ $ M $ $ K $ $ A_{1} $ $ B_{1} $ $ A_{2} $ $ B_{2} $ : : : : $ A_{M} $ $ B_{M} $

- $ 1 $ 行目は、社員の総数として整数 $ N\ (2\ ≦\ N\ ≦11 $)、隣り合わせにしてはいけない $ 2 $ 人組の組数として整数 $ M\ (0\ ≦\ M\ ≦\ 10) $、入れ替える回数として整数 $ K\ (0\ ≦\ K\ ≦\ 20) $ が空白で区切られて与えられる。
- $ 2 $ 行目から $ M $ 行は、$ 1 $ 行に $ 1 $ 組ずつ隣り合わせにしてはいけない $ 2 $ 人が空白で区切られて与えられる。
- $ i+1 $ 行目の整数 $ A_{i} $ と整数 $ B_{i} $ ($ 0\ ≦\ A_{i}\ )\ は、隣り合わせにしてはいけない\ 2 $ 人を表し、それぞれ高橋君から見て右に何人目であるかを表す。
- なお $ A_i\ =\ 0 $ または、$ B_i\ =\ 0 $ の場合は高橋君自身を表す。
 
 ちょうど $ K $ 回の入れ替えを行った後に、隣同士にしてはいけない $ 2 $ 人組が $ 1 $ 組も隣り合っていない確率を標準出力に $ 1 $ 行で出力せよ。  
 誤差は絶対誤差あるいは相対誤差の少なくとも片方が **$ 2e−3 $** 以下であれば許容する。  
 なお、最後には改行を出力せよ。 ```
<pre class="prettyprint linenums">
4 1 1
0 3
```

 ```
<pre class="prettyprint linenums">
0.333333333333
```

- 席替えを行う前は、$ 4 $ 人の配置は下図のようになっています。
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc003_4/61f407bc249a62aa28587ddc10de70ed39cd35f8.png)

- $ 1 $ 回入れ替えるという席変えを行った時、$ 0 $ と $ 3 $ の $ 2 $ 人が隣合わないようにするには、
- $ 0 $ と $ 1 $ を入れ替える。
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc003_4/b19286769fe6c7ecb9a5050f87e1e287f00c5c8a.png)

- $ 2 $ と $ 3 $ を入れ替える。
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc003_4/61d023ca1bef08a0e0342606ed3ec6d425200be6.png)


- の $ 2 $ 通りです。$ 4 $ 人から $ 2 $ 人を選ぶ方法は $ 6 $ 通り存在するので、条件を満たす確率は $ 2/6 $ となり答えは $ 1/3 $ です。
 
```
<pre class="prettyprint linenums">
5 4 20
0 1
0 2
0 3
0 4
```

 ```
<pre class="prettyprint linenums">
0
```

- 高橋君以外の $ 4 $ 人のうち、高橋君と隣り合うことのできる人が $ 1 $ 人も存在しないので、条件を満たすことはありません。
 
```
<pre class="prettyprint linenums">
5 1 2
0 3
```

 ```
<pre class="prettyprint linenums">
0.52
```

- $ 2 $ 回の入れ替えの後、$ 0 $ と $ 3 $ が隣り合わない入れ替え方法は $ 52 $通りあります。
- $ 5 $ 人から $ 2 $ 人を選ぶことを $ 2 $ 回行うと全ての組み合わせは $ (_5C_2)^2\ =\ 10^2\ =\ 100 $ 通りになります。
- したがって、答えは $ 52÷100\ =\ 0.52 $ です。

# 题解

## 作者：Zelotz (赞：5)

这道题使用了蒙特卡罗方法。

蒙特卡罗方法是指使用随机数来解决计算问题的方法。他的工作原理就是两件事：不断抽样、逐渐逼近。

例如计算 $\pi$。

![](https://cdn.luogu.com.cn/upload/image_hosting/6sdoggns.png)

这样的一个圆，在它的右上角做一个正方形。

则圆的面积为 $\frac{\pi}{4}$，正方形的面积为 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ujm91sw4.png)

现在向图中随机放点，则圆的面积比正方形的面积等于红点数比总点数。

记红点数为 $r$，总点数为 $tot$，即 $\frac{\pi}{4}=\frac{r}{tot}$。

所以 $\pi=\frac{4\times r}{tot}$。

回到本题，注意到 $n\leq11,k\leq20$，且精度限制范围大，考虑模拟。

输出满足条件的次数与总共次数的比值即可。

```cpp
const int N = 15;
int n, m, k, a[N], b[N], f[N][N], g[N];
signed main() 
{
    cin >> n >> m >> k;
    R(i, 1, m) cin >> a[i] >> b[i], ++a[i], ++b[i], f[a[i]][b[i]] = f[b[i]][a[i]] = 1;
    mt19937 rnd(time(0));
    int p = 0, q = 0;
    R(t, 1, 3e6)
    {
        ++q;
        R(i, 1, n) g[i] = i;
        bool cnt = 0;
        R(i, 1, k)
        {
            int x = 0, y = 0;
            do 
            {
                x = rnd() % n + 1, y = rnd() % n + 1;
            } while (x == y); 
            swap(g[x], g[y]);
        }
        R(i, 1, n - 1) cnt |= f[g[i]][g[i + 1]]; cnt |= f[g[n]][g[1]];
        p += !cnt;
    }
    printf("%.8Lf", (long double)p * 1.0 / q);
    return 0;
}

```

---

## 作者：SunsetSamsara (赞：1)

## 题意

有 $n$ 个人，其中有 $m$ 组人不能相邻。再随机交换 $k$ 对人，求不能相邻的人相邻的概率（误差不小于 $2 \times 10^{-3}$）。

## 分析

这个做法的突破口在于误差不能超过 $2 \times 10^{-3}$。这个误差的允许范围很大，所以我们可以通过一种朴素的方法——蒙特卡罗方法进行概率计算。

由于 $n \leq 11$，所以我们可以通过暴力模拟的方法解决问题。

但！是！这里 `rand` 实现的伪随机数会挂，所以我使用了 `mt19937` 来解决这个问题。

## 代码

正好 $1.00$ 分钟，蛮快的。

[（省略 $10.251 \operatorname{kb}$ 的快读）](https://www.luogu.com.cn/paste/61l9qqpd)

```cpp
#include <random>
using std::mt19937;
mt19937 gen(114514);
inline int getrand(int n) { return gen() % n; }
int n, m, k;
const int N = 30;
int id[N], mat[N][N];
int main() {
	cio.scan(n, m, k);
//	cio.print("n: ", n, " m: ", m, " k: ", k, '\n');
	for (int i = 1, x, y; i <= m; ++ i) {
		cio.scan(x, y);
		mat[x][y] = mat[y][x] = 1;
	}
	const int T = 1919810; int cnt = 0;
	for (int _ = T; _; -- _) {
		for (int i = 0; i < n; ++ i) id[i] = i;
		for (int i = 1, x, y; i <= k; ++ i) {
			x = getrand(n), y = getrand(n - 1);
			if (y >= x) ++ y;
			id[x] ^= id[y] ^= id[x] ^= id[y];
		}
		bool flag = 1;
		for (int j = 0; j < n; ++ j)
			if (mat[id[j]][id[(j + 1) % n]]) {
				flag = 0;
				break;
			}
		cnt += flag;
	}
	cio.setprecision(3);
	cio.print((double)cnt / T);
}
```

---

## 作者：Purslane (赞：1)

## Solution

我还以为是什么高级知识点呢 . 

$N \le 11$ , 由圆排列的知识 , 一共只有 $(N-1)!$ 种情况 , 小于 $3,628,800$ . 

大家有没有听说过一个计算 $\pi$ 的程序 ? 类似于这样 :

```cpp
int cnt=0;
ffor(i,1,N) { //下面的rand_max是已知常量
	double x=rand()/rand_max,y=rand()/rand_max;
	if(x*x+y*y<=1) cnt++;
}
double pi=cnt*4.0/N;
```

这个可能不大准 , 因为是随机的 . 但是 $N$ 足够大 , 就可以近似于圆周率 .

这道题也差不多 . 我们随机模拟一下 . 就可以大致算出概率了 .

注意 , 由于是随机 , 我们应该使用更为随机的东西 : mt19937 , 而不是 rand  .

后者会挂 ( 毕竟是伪随机数 ) .

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=20+5;
mt19937 m_rand(time(NULL));
int mrand(int mx) {
    return m_rand()%mx;
}
int n,m,k,id[MAXN],fbd[MAXN][MAXN];
signed main() {
	srand(time(0));
    cin>>n>>m>>k;
    ffor(i,1,m) {
        int x,y;cin>>x>>y;
        fbd[x][y]=fbd[y][x]=1;
    }
    int N=3000000,cnt=0;
    ffor(i,1,N) {
        ffor(j,0,n-1) id[j]=j;
        ffor(j,1,k) {
            int x=mrand(n),y=mrand(n-1);
			if(y>=x) y++;
            swap(id[x],id[y]);
        }
        int flg=1;
        ffor(j,0,n-1) if(fbd[id[j]][id[(j+1)%n]]) flg=0;
        cnt+=flg;
	} 
    cout<<fixed<<setprecision(10)<<cnt*1.0/N;
    return 0;
}
```

这种萌萌题应当降绿 !

---

## 作者：12345678hzx (赞：0)

## 题目大意
有 $n$ 个人，其中有 $m$ 组人不能相邻。随机交换 $k$ 对人，求不能相邻的人相邻的概率，误差不小于 $2\times 10^{-3}$。

## 思路
不知道大家有没有听过[这么一个故事](https://baijiahao.baidu.com/s?id=1665678874727402934&wfr=spider&for=pc)。

文中通过扔针来算圆周率的方法就运用了随机性，且可以注意到，扔的次数越多，结果就越接近。

这题也是一样的，由于此题只要与结果的误差不小于 $2\times 10^{-3}$ 就行，所以我们就可以照着题目暴力模拟，每次随机出两个人并交换统计情况即可。

需要注意的一点是随机数生成不能用 `rand`，这是伪随机，且值域很小，需要用 `mt19937`，虽然它也是伪随机，但是值域比较大，与真实情况更相近。

---

