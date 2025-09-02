# [ABC022D] Big Bang

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc022/tasks/abc022_d

宇宙はビッグバンによって誕生して以来、膨張し続けていることが知られています。

天文学者である高橋君はその宇宙の膨張の速度を計測することにしました。

高橋君はある $ 2 $ つの日について、同じ $ N $ 個の星の位置を観測しました。星の位置は座標平面上の点として記録されます。つまり各日の観測結果は座標平面上の $ N $ 個の点からなる点集合になります。

$ 2 $ 回の観測の結果を見比べてみると、$ 1 $ 回目の観測結果である点集合に対して以下の $ 3 $ つの操作を順に実行すると $ 2 $ 回目の観測結果である点集合に一致することがわかりました。

1. 同じ向きに同じ距離だけ平行移動する。
2. 原点を中心に同じ角度だけ回転する。
3. 原点を中心に $ P $ 倍 $ (1\ ≦\ P) $ に相似拡大する。つまり点 $ (a,\ b) $ を点 $ (a×P,\ b×P) $ に移すという操作をすべての点に実行する。

ここで $ P $ の値がわかれば膨張速度を求めることができそうです。

いざ $ P $ を求めようとした高橋君でしたが、うっかりどの点がどの星に対応するのか記したデータをなくしてしまいました。

そこで高橋君は優秀なプログラマーであるあなたに助けを借りることにしました。

$ 1 $ 回目と $ 2 $ 回目の観測結果が与えられるので $ P $ を求めてください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1\ ≦\ N\ ≦\ 3,000 $を満たすデータセットに正解した場合は $ 50 $ 点が与えられる。
- $ 1\ ≦\ N\ ≦\ 10^5 $を満たすデータセットに正解した場合はさらに $ 50 $ 点が与えられる。合計で$ 100 $点となる。

### Sample Explanation 1

以下のように操作を実行すれば、 $ 1 $ 回目の観測結果の点集合が、 $ 2 $ 回目の観測結果の点集合に移されます。 1. $ x $ 軸方向に $ -0.5 $、 $ y $ 軸方向に $ -0.5 $ 平行移動させる。 2. 原点を中心にして、$ 45° $ 時計回りに回転させる。 3. 原点を中心に $ 2√2 $ 倍する。 よって $ P\ =\ 2√2 $ となります。

## 样例 #1

### 输入

```
4
0 0
0 1
1 0
1 1
0 2
2 0
-2 0
0 -2```

### 输出

```
2.8284271247```

## 样例 #2

### 输入

```
6
3 4
1 3
4 3
2 2
0 1
2 0
5 5
-1 2
-1 -3
2 1
2 6
4 -3```

### 输出

```
2.2360679775```

# 题解

## 作者：ming2023 (赞：1)

考虑对两个区域分别求一次凸包。

根据题意，假设两次求得的面积分别是 $S_1,S_2$

那么根据平面图形的相似关系，有

$$S_1 \times p^2=S_2$$

故

$$p= \sqrt{\frac{S_2}{S_1}}$$

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+50;
const long double eps=1e-8;

struct Point
{
	long double x,y;
	
	Point(long double x=0,long double y=0):x(x),y(y){}
}a[N];

Point operator -(Point A,Point B){return Point(A.x-B.x,A.y-B.y);}
bool operator < (const Point& a,const Point& b){return a.x<b.x || (a.x==b.x && a.y<b.y);}

long double Cross(Point A,Point B)
{
	return A.x*B.y-B.x*A.y;
}

Point ch[N];
int main()
{
	int n;cin>>n;
	for(int i=0;i<n;i++) cin>>a[i].x>>a[i].y;
	
	//处理第一组数据
	sort(a,a+n);
	int m=0;
	for(int i=0;i<n;i++)//维护上凸壳
	{
		while(m>1 && Cross(ch[m-1]-ch[m-2],a[i]-ch[m-2])<=0) m--;
		ch[m++]=a[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--)//下凸包
	{
		while(m>k && Cross(ch[m-1]-ch[m-2],a[i]-ch[m-2])<=0) m--;
		ch[m++]=a[i];
	}
	if(n>1) m--;
	
	long double S1=0;//实际上还需要/2才是真正的面积
	for(int i=1;i<=m-2;i++)
	{
		Point a=ch[0],b=ch[i],c=ch[i+1];
		S1+=Cross(b-a,c-a);
	}
	
	memset(ch,0,sizeof(ch));
	m=0;
	for(int i=0;i<n;i++) cin>>a[i].x>>a[i].y;
	sort(a,a+n);
	
	for(int i=0;i<n;i++)//第二块 维护上凸壳
	{
		while(m>1 && Cross(ch[m-1]-ch[m-2],a[i]-ch[m-2])<=0) m--;
		ch[m++]=a[i];
	}
	k=m;
	for(int i=n-2;i>=0;i--)//第二块 下凸包
	{
		while(m>k && Cross(ch[m-1]-ch[m-2],a[i]-ch[m-2])<=0) m--;
		ch[m++]=a[i];
	}
	if(n>1) m--;
	
	long double S2=0;
	for(int i=1;i<=m-2;i++)
	{
		Point a=ch[0],b=ch[i],c=ch[i+1];
		S2+=Cross(b-a,c-a);
	}
	
	printf("%.9Lf\n",sqrt(S2/S1));
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [ABC022D] Big Bang


## 大意

给你两个点集 $A,B$，保证两个点集形成的图像相似，求相似比。但我们不知道点的对应关系。

## 思路

首先我们不知道两幅图的点的对应关系，这让我们无从下手。因此我们迫切需要找到一个可以对应起来的点。假设我们找到的点分别为 $p,p'$（$p$ 在 $A$ 中，$p'$ 在 $B$ 中），我们不要求这两个点是已经存在的某个点，但我们要保证在两幅图中分别加入点 $p,p'$，这两幅图依然保持相似。

仔细思考得知，我们可以取所有点的平均值。即假设 $A$ 中的点的坐标为 $(x_1,y_1)(x_1,y_2)\dots(x_n,y_n)$，那么 $p$ 的坐标为 $(\overline{x_i},\overline{y_i})$（$\overline{x_i}$ 表示 $x_1\sim x_n$ 的平均数）。对于 $p'$ 我们也这样定义。因此我们就找到了两幅图中的一组对应点了！

现在事情就好办多了，我们找到两幅图中到对应点距离最远的（或者最近的）点 $q,q'$，求出 $p-q,p'-q'$ 距离之比即可。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=5e5+5;
const int M=1e3;
const int MOD=998244353;
const int INF=1e9;
//变量
double suma,sumb,sumx,sumy,disa,disb;
int n;

struct node{
	int x,y;
}a[N],b[N];

double dis( double x,double y,double a,double b){//注意x,y,a,b也是double
	return sqrt((x-a)*(x-a)+(y-b)*(y-b));
}

bool cmp(node a,node b){
	return dis(a.x,a.y,sumx,sumy)>dis(b.x,b.y,sumx,sumy);
}
bool cmp2(node a,node b){
	return dis(a.x,a.y,suma,sumb)>dis(b.x,b.y,suma,sumb);
}


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y,sumx+=a[i].x,sumy+=a[i].y;
    for(int i=1;i<=n;i++)cin>>b[i].x>>b[i].y,suma+=b[i].x,sumb+=b[i].y;
    sumx/=n;sumy/=n;suma/=n;sumb/=n;
//    cout<<sumx<<endl;
    
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1,cmp2);
    
//    for(int i=1;i<=n;i++)disa+=dis(sumx,sumy,a[i].x,a[i].y);
//    for(int i=1;i<=n;i++)disb+=dis(suma,sumb,b[i].x,b[i].y);
//    
    printf("%.10lf\n",1.00*dis(b[1].x,b[1].y,suma,sumb)/dis(a[1].x,a[1].y,sumx,sumy));
//    printf("%.8lf\n",disb/disa);
    
#ifdef PAUSE_ON_EXIT
    system("pause");
#endif
    return 0;
}

```






---

## 作者：AkeRi (赞：0)

# Description
略。

# Solution
我们只想知道放大了多少倍而不是相似的结果，所以只需要求出两个图形的重心到各自个点欧几里得距离的和，再用第二次结果比上第一次结果就是膨胀的倍数了。

时间复杂度 $\Theta(n)$。

```cpp
/*

by L1rs1ngzN1sLyr

*/
std::pair<int,int>a[KI],b[KI];
int n=read();
double sumxa,sumxb,sumya,sumyb,ansa,ansb;
double dis(int x,int y,int sa,int sb)
{
    return std::sqrt((sa-x)*(sa-x)+(sb-y)*(sb-y));
}
int main()
{
    for(int i=1;i<=n;i++) a[i].first=read(),a[i].second=read();
    for(int i=1;i<=n;i++) b[i].first=read(),b[i].second=read();
    for(int i=1;i<=n;i++) sumxa+=a[i].first,sumxb+=b[i].first,sumya+=a[i].second,sumyb+=b[i].second;
    double s1=sumxa/n,s2=sumxb/n,s3=sumya/n,s4=sumyb/=n;
    for(int i=1;i<=n;i++)
    {
        ansa+=std::sqrt((s1-a[i].first)*(s1-a[i].first)+(s3-a[i].second)*(s3-a[i].second));
        ansb+=std::sqrt((s2-b[i].first)*(s2-b[i].first)+(s4-b[i].second)*(s4-b[i].second));
    }
    printf("%.12lf\n",ansb/ansa);
}
```

---

## 作者：Goodans (赞：0)

# 问题分析
我们被要求通过两次观测到的星星位置来计算宇宙膨胀的比例因子 $P$。

已知的三个变换是：

* 平移：使得两次观测的点集合在平移后对齐。
* 旋转：绕原点旋转相同的角度。
* 放大：在原点为中心进行相似变换，即每个点的坐标乘以相同的比例 $P$。
我们需要通过这两组点来推断 $P$ 的值。

# 解题思路
假设我们知道两组点，分别为第一次观测的 $A$ 和第二次观测的 $B$，它们在经过平移、旋转和放大的操作后应该保持相对的几何结构。

我们将从以下几步入手来推导 $P$：

平移和旋转后的距离保持不变：

旋转不会改变点与点之间的相对距离。
平移也不会影响点之间的相对距离。
因此，我们可以通过比较两个点集合的相对距离来计算放大比例 $P$。

计算点对之间的距离： 对于每一对点 $(A_i, A_j)$，我们可以计算它们之间的欧几里得距离。在第二次观测中，经过旋转和放大后，所有的距离应当是第一次观测中对应距离的 $P$ 倍。

思路清晰，代码就不放了。

---

