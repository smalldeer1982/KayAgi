# [ABC074C] Sugar Water

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc074/tasks/arc083_a

すぬけ君はビーカーに砂糖水を作ろうとしています。 最初ビーカーは空です。すぬけ君は以下の $ 4 $ 種類の操作をそれぞれ何回でも行うことができます。一度も行わない操作があっても構いません。

- 操作 1: ビーカーに水を $ 100A $ \[g\] 入れる。
- 操作 2: ビーカーに水を $ 100B $ \[g\] 入れる。
- 操作 3: ビーカーに砂糖を $ C $ \[g\] 入れる。
- 操作 4: ビーカーに砂糖を $ D $ \[g\] 入れる。

すぬけ君の実験環境下では、水 $ 100 $ \[g\] あたり砂糖は $ E $ \[g\] 溶けます。

すぬけ君はできるだけ濃度の高い砂糖水を作りたいと考えています。

ビーカーに入れられる物質の質量 (水の質量と砂糖の質量の合計) が $ F $ \[g\] 以下であり、 ビーカーの中に砂糖を溶け残らせてはいけないとき、 すぬけ君が作る砂糖水の質量と、それに溶けている砂糖の質量を求めてください。 答えが複数ある場合はどれを答えても構いません。

水 $ a $ \[g\] と砂糖 $ b $ \[g\] を混ぜた砂糖水の濃度は $ \frac{100b}{a\ +\ b} $ \[%\]です。 また、この問題では、砂糖が全く溶けていない水も濃度 $ 0 $ \[%\] の砂糖水と考えることにします。

## 说明/提示

### 制約

- $ 1\ ≦\ A\ <\ B\ ≦\ 30 $
- $ 1\ ≦\ C\ <\ D\ ≦\ 30 $
- $ 1≦\ E\ ≦\ 100 $
- $ 100A\ ≦\ F\ ≦\ 3,000 $
- $ A,\ B,\ C,\ D,\ E,\ F $ はすべて整数である。

### Sample Explanation 1

この入力例の状況では、水 $ 100 $ \\\[g\\\] あたり砂糖は $ 15 $ \\\[g\\\] 溶けます。 また、ビーカーに物質を $ 200 $ \\\[g\\\] まで入れることができます。 操作 1 と操作 3 を $ 1 $ 回ずつ行うことで $ 110 $ \\\[g\\\] の砂糖水を作ることができます。 また、これ以上濃度の高い砂糖水を作ることはできません。 たとえば、以下のような操作は条件を満たしません。 - 操作 1 と操作 4 を $ 1 $ 回ずつ行うと、ビーカーに砂糖が溶け残ってしまいます。 - 操作 2 を $ 1 $ 回と操作 3 を $ 3 $ 回行うと、ビーカーの中の物質の量が $ 200 $ \\\[g\\\] を超えてしまいます。

### Sample Explanation 2

ほかに、たとえば以下の出力も正解となります。 ``` 400 200 ``` 一方、以下の出力は不正解となります。 ``` 300 150 ``` なぜなら、砂糖が $ 150 $ \\\[g\\\] 溶けた $ 300 $ \\\[g\\\] の砂糖水を作るにはビーカーに水をちょうど $ 150 $ \\\[g\\\] 入れる必要がありますが、そのようなことは不可能だからです。

## 样例 #1

### 输入

```
1 2 10 20 15 200```

### 输出

```
110 10```

## 样例 #2

### 输入

```
1 2 1 2 100 1000```

### 输出

```
200 100```

## 样例 #3

### 输入

```
17 19 22 26 55 2802```

### 输出

```
2634 934```

# 题解

## 作者：漠寒 (赞：3)

## 题意

你要配置一杯糖水，每次你可以选择如下几个操作中的一个。

1 加入100 $A$ 克的水。

2 加入100 $B$ 克的水。

3 加入 $C$ 克的糖

4 加入 $D$ 克的糖

此外，这杯糖水要满足以下几个要求。

1 糖的质量不能超过水的质量的 $E/100$ 。

2 总质量不能超过 $F$ 。

在此要求下，你要让这杯糖水的浓度最大。

### 解法

看到题解里大佬们都用的枚举操作，我讲一下用 $DP$ 的做法，实际上是因为考试大标题写的 $DP$ 。

用了两个数组， $F$ 求出糖可以达到的数目， $g$ 求出水可以到达的数目，之后列举糖的数目，从满足浓度条件的所需的最少的水开始，一直加到超过质量要求为止。中间找到一个可行的水的质量时，便可以停止（高浓度优先）。这样不断比较即可。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f,F[4001],g[4000],anss,anst,anscz,ss,tt,cz;//cz的比较是因为考试题多了个限制条件 
int main()
{
	//freopen("easy.in","r",stdin);
	//freopen("easy.out","w",stdout);
	cin>>a>>b>>c>>d>>e>>f;
	anss=10000000;
	anscz=10000000;
	a*=100;
	b*=100;
	for(int i=1;i<=f;i++)F[i]=2e9,g[i]=2e9;
	for(int i=c;i<=f;i++)F[i]=min(F[i],F[i-c]);
	for(int i=d;i<=f;i++)F[i]=min(F[i],F[i-d]);//糖 
	for(int j=a;j<=3500;j+=100)g[j]=min(g[j],g[j-a]+1);
	for(int j=b;j<=3500;j+=100)g[j]=min(g[j],g[j-b]);//水 
	for(int i=1;i*(100+e)<=f*e;i++){
		if(!F[i]){//可行糖 
			int mn;
			if((i*100)%e==0)mn=(i*100)/e;
			else mn=(i*100)/e+1;//向上取整 
			if(mn%100!=0)mn=100*(mn/100)+100;//整百方便枚举 
			for(int j=mn;j+i<=f;j+=100){
				if(g[j]!=2e9){//可行水 
					ss=j;
					tt=i;
					cz=g[j];
					break;
				}
			}
			if(((anst*ss<anss*tt)||(anst*ss==anss*tt&&cz<anscz)||(anst*ss==anss*tt&&ss<anss&&cz==anscz))&&(ss+tt)<=f){//限制条件较多，考试没spj ，此题应该只用第一个判断 
				anst=tt;
				anss=ss;
				anscz=cz;
			}
		}
	}
	if(anss==10000000){//对于我的初始赋值较大要整一下 ，不然不知不觉超f 
		if(b<=f){
			cout<<b<<" "<<0<<endl;
			return 0;
		}
		if(a<=f){
			cout<<a<<" "<<0<<endl;
			return 0;
		}
		cout<<0<<" "<<0<<endl;
		return 0;
	}
	cout<<anss+anst<<" "<<anst<<endl;
}
/*
1 2 10 20 4 610
7 12 7 9 67 3000
12 15 25 30 2 1524
*/
```


---

## 作者：_Above_the_clouds_ (赞：2)

# 思路：
用四重循环枚举操作 $1$，操作 $2$，操作 $3$，操作 $4$ 的次数，用 `check` 函数，找到最优解。

如果水加上糖的克数大于 $f$，说明超出了烧杯容量，直接退出；如果会有未溶解的糖也退出；否则用 $sum$ 记录糖水率，找到更高的糖水率时，$sum$ 更新，$ans$ 记录总和，$ans2$ 记录糖的克数。最后输出即可。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f,ans,ans2;
long double sum;
void check(long double x,long double y){
	if(x+y>f) return ;
	if(x*e<y*100) return ;
	if(sum<=100*y/(x+y)) sum=100*y/(x+y),ans=x+y,ans2=y;
	return ;
}
int main(){
	cin>>a>>b>>c>>d>>e>>f;
	for(int i=0;i<=100;i++)
		for(int j=0;j<=100;j++)
			for(int k=0;k<=100;k++)
				for(int l=0;l<=100;l++)
					check(100*a*i+100*b*j,c*k+d*l);
	cout<<ans<<" "<<ans2;
	return 0;
}
```


---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc083_a)

#### 思路

不难想到，这道题可以用 DP，$dp_{i,j}$ 表示有 $i$ 克水 $j$ 克糖是否可行，可以为 $1$，否则为 $0$，初始条件为 $dp_{0,0} = 1$（表示有 $0$ 克水 $0$ 克糖），详细 DP 过程请看代码。

##### 注意： 如果有多个答案，输出任意一种即可，如果和样例输出不一样可以计算下浓度，看是否相等。
code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,e,f,dp[3310][3310],ma,ml;
int main()
{
	cin >> a >> b >> c >> d >> e >> f;
	dp[0][0] = 1;//初始条件
	for(int i = 0;i <= f;i++)
	{
		for(int j = 0;j + i <= f;j++)
		{
			if(i >= b * 100) dp[i][j] = max(dp[i][j],dp[i - b * 100][j]);	//当dp[i][j - b * 100]满足,则dp[i][j]一定满足
			if(i >= a * 100) dp[i][j] = max(dp[i][j],dp[i - a * 100][j]);//同理
			if(j >= c) dp[i][j] = max(dp[i][j],dp[i][j - c]);
			if(j >= d) dp[i][j] = max(dp[i][j],dp[i][j - d]);
 			
			if(e * i >= j * 100 && dp[i][j])
			{
				if(ml * (i + j) <= j * (ma + ml))//判断浓度是否比当前最浓浓度浓，怕多次除精度丢失，这里利用了等式的性质
				{
					ma = i;
					ml = j;
				}
			}
		}
	}
	printf("%lld %lld",ma + ml,ml);
	return 0;
}

```


---

## 作者：zhengzonghaoak (赞：1)

思路 ： 考虑到数据比较水，可以枚举，通过循环来列举出所有可能出现的糖水配置的情况，进一步排除掉不符合题意的，记录下最优解即可。代码如下。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a,b,c,d,e,f;//题目中的a,b,c,d,e,f 
double ans;//记录最优解 
double nd;//循环中的浓度 
int x,y;//糖水的质量与糖的质量 
int rz,rj;//水的质量与糖的质量 
int main(){
	cin>>a>>b>>c>>d>>e>>f;
	a*=100;
	b*=100;
	ans=-1.0;
	for(int i=0;i<=f/a;i++){//注意要从0开始，因为有可能不加 
		for(int j=0;j<=f/b;j++){
			for(int k=0;k<=f/c;k++){
				for(int m=0;m<=f/d;m++){
					rz=k*c+m*d;//算出水与糖的质量 
					rj=i*a+j*b;
					if(rz+rj>f) continue;//如果装不下的话去掉 
					if((rj/100)*e<rz) continue;//如果溶解不了的话去掉 
					nd=1.0*rz/(rz+rj);//算出浓度 
					if(nd>ans){//如果比当前的最优解还要优 
						ans=nd;//记录下新的最优解 
						x=rz+rj;//算出溶剂的质量 
						y=rz;//算出糖的质量 
					} 
				}
			}
		}
	}
	cout<<x<<" "<<y<<"\n";//输出 
	return 0;//华丽结束！！！ 
}
```
跪求管理员大大通过！！！

---

## 作者：小小小朋友 (赞：1)

### 题目简介

有四种操作，要配置出糖水的浓度最高，求配置的糖水的质量，以及溶解在其中的糖的质量。

有SPJ

### 思路简介

四重循环 暴力枚举

### 代码和解析

```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c,d,e,f;
int ansm=100,anss=0;
int main(){
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);
    a*=100,b*=100;
    for(double i1=0;i1*a<=f;i1+=1){//a操作
        for(double i2=0;i2*b+i1*a<=f;i2+=1){//b操作
            for(double i3=0;i3*c+i2*b+i1*a<=f;i3+=1){//c操作
                for(double i4=0;i4*d+i3*c+i2*b+i1*a<=f;i4+=1){//d操作
                    if((i3*c+i4*d)/(i1*a+i2*b+i3*c+i4*d)>(double)anss/ansm){//判断是否优于答案
                        double p=(a*e*i1+b*e*i2)/100;
                        if(p<(i3*c+i4*d)) continue;//判断浓度是否小于限制
                        anss=(int)i3*c+i4*d;
                        ansm=(int)(i1*a+i2*b+i3*c+i4*d);//更新答案
                    }
                }
            }
        }
    }
    //输出答案
    cout<<ansm<<' '<<anss;
    return 0;
}
```

---

## 作者：whx2009 (赞：1)

## 本题思路：
这道题很多人一看就想到了用 DP 算法去做，可是对于一些萌新来说就十分困难了，但是我们可以看到这道题的时限有 $3$ 秒之多，我们就可以去尝试暴力，分别枚举每次选择后的糖的含量，在选出最大的方案输出质量与糖水就可以了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b,c,d,e,f,sum1=0,sum2=0;
	cin>>a>>b>>c>>d>>e>>f;
	double ans=0;
	a*=100,b*=100;
	for(int long i=0;i<=f/a;i++)//枚举方案一 
	{
		for(int long j=0;j<=f/b;j++)//枚举方案二 
		{
			for(int long x=0;x<=f/c;x++)//枚举方案三 
			{
				for(int long y=0;y<=f/d;y++)//枚举方案四 
				{
					if((i*a+j*b)/100*e<x*c+y*d) break;
					if(i*a+j*b+x*c+y*d>f) break;
					double x1=x*c+y*d,x2=i*a+j*b;
					double m=x1/x2;
					if(m>=ans)//符合就储存 
					{
						ans=m;
						sum1=i*a+j*b+x*c+y*d;
						sum2=x*c+y*d;
					}
				}
			}
		}
	}
	cout<<sum1<<" "<<sum2;
	return 0;//完结撒花！！！ 
}

```


---

## 作者：Misserina (赞：0)

### 解析

先打两个数组 water 和 sugar，得到所有可能的水和糖的质量，再利用贪心思想，枚举每个可能的水的质量对应的最大浓度（即最大的糖的质量），找出最优解。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f;
bool water[35],sugar[3005];
int main() {
	scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
	water[0]=1;
	sugar[0]=1;
	for (int i=0;i<=30;i++) {
		if (water[i]) {
			if (i+a<=30) water[i+a]=1;
			if (i+b<=30) water[i+b]=1;
		}
	}
	for (int i=0;i<=3000;i++) {
		if (sugar[i]) {
			if (i+c<=3000) sugar[i+c]=1;
			if (i+d<=3000) sugar[i+d]=1;
		}
	}
	int res_w=100*a;
	int res_s=0;
	for (int i=1;i<=f/100;i++) {
		if (water[i]) {
			int s=min(f-100*i,i*e);
			s=max(s,0);
			while (!sugar[s]) s--;
			if (s*(res_s+res_w)>res_s*(i*100+s)) {
				res_s=s;
				res_w=i*100;
			}
		}
	}
	printf("%d %d",res_s+res_w,res_s);
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

你要做出一杯糖水，求出在满足所有条件下浓度最高的糖水的糖量和水量。

- 糖水总重量不能超过 $f$。

- 每一百克水中不能有超过 $e$ 克糖。


## 解题思路

一看数据范围，直接四重暴力枚举。分别枚举每种情况有多少次，最后更新答案即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, c, d, e, f;
double maxx, ans1, ans2;
int main() {
    cin >> a >> b >> c >> d >> e >> f;
    for(int sa = 0; sa <= 100; sa++) {
        for(int sb = 0; sb <= 100; sb++) {
            for(int sc = 0; sc <= 100; sc++) {
                for(int sd = 0; sd <= 100; sd++) {
                    int s1 = 100 * sa * a + 100 * sb * b;
                    int s2 = sc * c + sd * d;
                    if(s1 + s2 == 0) continue;    //特判
                    if(s1 + s2 > f) {    //条件1
                        continue;
                    }
                    if(s2 * 100 > s1 * e) {        //条件2
                        continue;
                    }
                    double s = 100 * s2 * 1.000 / (s1 + s2) ;
                    if(s >= maxx) {        //更新答案
                        maxx = s;
                        ans1 = s1 + s2;
                        ans2 = s2;
                    }
                }
            }
        }
    }
    cout << ans1 << " " << ans2 << '\n';
    return 0;
}
```

---

## 作者：Kano_zyc (赞：0)

## 题意简述

找出最大糖水浓度。我们的目标是在总质量不超过 $F$ 的情况下，找出最大的糖水浓度。

## 思路

首先读入题目中给出的所有参数。

然后，通过双重循环遍历所有可能的水的组合（以 $A$ 和 $B$ 为单位）。

对于每种水的组合，我们计算出这种组合下可以加入的糖的最大量（考虑到 $E$ 的限制，水的量，以及总质量 $F$ 的限制）。

接下来，我们通过另外一个双重循环遍历所有可能的糖的组合（以 $C$ 和 $D$ 为单位）。

对于每种糖的组合，我们计算出糖水的浓度，如果这个浓度超过了当前最大的浓度，我们就更新最大浓度以及对应的糖和总质量。

最后，我们输出最大总质量和对应的糖的质量。


## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int A, B, C, D, E, F;
    cin >> A >> B >> C >> D >> E >> F;

    double max_density = -1.0;
    int max_sugar = 0, max_total = 0;

    // 遍历所有可能的水的组合
    for(int a = 0; 100*A*a <= F; ++a) {
        for(int b = 0; 100*A*a + 100*B*b <= F; ++b) {
            int water = 100*A*a + 100*B*b;

            // 计算这种组合下可以加入的糖的最大量
            int max_sugar_here = min({E * (A * a + B * b), F - water, F});

            // 遍历所有可能的糖的组合
            for(int c = 0; C*c <= max_sugar_here; ++c) {
                for(int d = 0; C*c + D*d <= max_sugar_here; ++d) {
                    int sugar = C*c + D*d;

                    // 计算糖水的浓度
                    double density = 100.0 * sugar / (sugar + water);

                    // 如果这个浓度超过了当前最大的浓度，就更新最大浓度以及对应的糖和总质量
                    if(density > max_density) {
                        max_density = density;
                        max_sugar = sugar;
                        max_total = sugar + water;
                    }
                }
            }
        }
    }

    // 输出最大总质量和对应的糖的质量
    cout << max_total << " " << max_sugar << endl;

    return 0;
}
```

---

## 作者：mz2022 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc083_a)

题目大意：
--------
给你以下 $4$ 个操作

操作 $1$：加入 $100$ $\times$ $A$ 克的水。

操作 $2$：加入 $100$ $\times$ $B$ 克的水。

操作 $3$：加入 $C$ 克糖。

操作 $4$：加入 $D$ 克糖。

以及 $2$ 个限制条件

$1$：糖的质量不能超过水的质量的 $E/100$。

$2$：糖水的总质量不超过 $F$ 克。

思路：
--------
 
其实看到这题我的第一想法是 DP，但是我的 DP 水平不允许我这么做，然后我看到了 $3$ 秒的限时，果断开始打暴力，做法就是枚举这四个操作然后取最优解。

AC Code：
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,d,e,f;
double maxx,ans1,ans2;
signed main()
{
	cin>>a>>b>>c>>d>>e>>f;
	for(int i1=0;i1*a<=f;i1++)
	{
		for(int i2=0;i2*b<=f;i2++)
		{
			for(int i3=0;i3*c<=f;i3++)
			{
				for(int i4=0;i4*d<=f;i4++)
				{
					double su=i3*c+i4*d;
					double wa=i1*a*100+i2*b*100;
					if(su>wa*e/100||wa+su>f)break;//限制条件
					double con=su/wa;
					if(con>maxx)//取最优解 
					{
						maxx=con;
						ans1=su+wa;
						ans2=su;
					}
				}
			}
		}
	}
	cout<<ans1<<" "<<ans2; 
	return 0;
} 
```

---

## 作者：0xyz (赞：0)

目前本题最优时间复杂度？

### 一、做法

1. 我们求出不定方程 $XC+YD=\gcd(C,D)$ 的一组特解。

2. 我们枚举 $i$，看它是否能表示为 $XC+YD$，其中 $X,Y\in\mathbb{N}$。

3. 我们预处理出小于等于每个 $i$ 的最大的可以表示为 $XC+YD$ 的数 $w_i$。

4. 枚举操作 $1$ 和 $2$ 分别进行多少次，然后取**容器剩下可用质量**以及**可以溶解在当前质量的水里的糖的最大质量**的最小值 $k$，那么真正可以加入水里的质量是 $w_k$，然后判断此时糖水的浓度是不是大于原来的答案，如果大于的话改一下答案即可。

时间复杂度 $O(F+AB)$。

### 二、代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;return;}
	exgcd(b,a%b,y,x);y-=a/b*x;
}
ll a,b,c,d,e,f,p,q=-1,x,y,g,v[3010],w[3010];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>a>>b>>c>>d>>e>>f;g=__gcd(c,d);exgcd(c,d,x,y);d/=g;c/=g;
	for(ll i=0,mx=0,s,X,Y;i<=f;i++){
		if(i%g){w[i]=mx;continue;}
		X=x*i/g;Y=y*i/g;
		if(X<0)s=(d-X)/d,X+=s*d,Y-=s*c;
		if(Y<0)s=(c-Y)/c,X-=s*d,Y+=s*c;
		if(X>=0&&Y>=0)mx=i;
		w[i]=mx;
	}
	for(ll i=0;i*100*a<=f;i++)
		for(ll j=0,t=a*i;100*t<=f;j++,t+=b)
			if(w[min(e*t,f-100*t)]*p>100*t*q)p=100*t,q=w[min(e*t,f-100*t)];
	cout<<p+q<<' '<<q<<'\n';
	return 0;
}
```

---

