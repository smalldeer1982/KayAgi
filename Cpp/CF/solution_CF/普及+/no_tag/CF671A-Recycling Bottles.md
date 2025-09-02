# Recycling Bottles

## 题目描述

It was recycling day in Kekoland. To celebrate it Adil and Bera went to Central Perk where they can take bottles from the ground and put them into a recycling bin.

We can think Central Perk as coordinate plane. There are $ n $ bottles on the ground, the $ i $ -th bottle is located at position $ (x_{i},y_{i}) $ . Both Adil and Bera can carry only one bottle at once each.

For both Adil and Bera the process looks as follows:

1. Choose to stop or to continue to collect bottles.
2. If the choice was to continue then choose some bottle and walk towards it.
3. Pick this bottle and walk to the recycling bin.
4. Go to step $ 1 $ .

Adil and Bera may move independently. They are allowed to pick bottles simultaneously, all bottles may be picked by any of the two, it's allowed that one of them stays still while the other one continues to pick bottles.

They want to organize the process such that the total distance they walk (the sum of distance walked by Adil and distance walked by Bera) is minimum possible. Of course, at the end all bottles should lie in the recycling bin.

## 说明/提示

Consider the first sample.

Adil will use the following path: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671A/9e150a5b7d96969b57a5b1f4dea00f000710a7e2.png).

Bera will use the following path: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671A/3884532a18b9773dea1f2047e6bbd80cd6d12185.png).

Adil's path will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671A/d2c02d2d4b61a9b8e78355ce9a7fbc852f71e66b.png) units long, while Bera's path will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671A/da983b0763053dcb65ef9a22647e2063dd0571f6.png) units long.

## 样例 #1

### 输入

```
3 1 1 2 0 0
3
1 1
2 1
2 3
```

### 输出

```
11.084259940083
```

## 样例 #2

### 输入

```
5 0 4 2 2 0
5
5 2
3 0
5 5
3 5
3 3
```

### 输出

```
33.121375178000
```

# 题解

## 作者：Trilliverse (赞：0)

## 思路：
- 设人到垃圾的距离为dis1(人->垃圾)，垃圾到垃圾桶的距离为dis2(垃圾->桶)，
- 则第一步走的路程为 dis1 + dis2 
- 剩下的路程都是从垃圾桶出发去捡垃圾 所以距离为往返的路程 dis2* 2 
------------

对于每一种方案来说 可以优化的距离为 dis1+dis2-dis2*2 = **dis1-dis2** 所以我们要找所有方案中的 **abs(dis1-dis2)** 的最大值来进行优化

### 注：
1. 两点间距离公式：
$dis = \sqrt{(\mathtt{x}_1-\mathtt{x}_2)^2 + (\mathtt{y}_1-\mathtt{y}_2)^2}$
2. 有关pair用法详见[pair用法](https://zh.cppreference.com/w/cpp/utility/pair)
----

### 具体注释详见code
```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn = 100005;

int x[maxn],y[maxn];//垃圾的横纵坐标
int n,ax,ay,bx,by,tx,ty;
double ans,tmp;
//first位置存的是个距离，second位置存的是对应垃圾的编号 
pair<double,int> A[maxn],B[maxn],t[maxn]; 


double D(int x1,int y1,int x2,int y2) {
	return sqrt(1.0*(x1-x2)*(x1-x2)+1.0*(y1-y2)*(y1-y2));
}

int main() {
  scanf("%d %d %d %d %d %d %d",&ax,&ay,&bx,&by,&tx,&ty,&n);
  for(int i=1;i<=n;i++) {
    scanf("%d %d",&x[i],&y[i]);置
    double dis = D(x[i],y[i],tx,ty);
    A[i] = make_pair(D(ax,ay,x[i],y[i]) - dis,i);
    B[i] = make_pair(D(bx,by,x[i],y[i]) - dis,i);
    t[i] = make_pair(dis * 2,i);
    ans += t[i].first;
   }
  sort(A+1,A+1+n);
  sort(B+1,B+1+n);
  
  tmp = min(A[1].first,B[1].first);//tmp不断更新最大的差值
  if(A[1].second == B[1].second)  //如果捡同一个垃圾 
   tmp = min(tmp,min(A[1].first + B[2].first, A[2].first +B[1].first));
  else //不同的垃圾 
   tmp = min(tmp,A[1].first + B[1].first);
  printf("%.15lf\n",ans + tmp);
  return 0;
}

```


---

## 作者：qjxqjx (赞：0)

## 题目大意：
有两个人捡瓶子，分别从原来的位置出发，捡到一个后返回垃圾箱扔垃圾，两人独立仍放和行走。

问最后距离之和的最小值。

## 题目思路：
令最开始的距离为 $sum=∑2 \times dist_i$。

既然两人可以同时到一个点，则距离为

$sum-dist_i+disa_i+disb_i-dist_i$。

当然，也可以一个人去，则为 $sum-dist_i+(disa_i\parallel disb_i)$。

每次维护一个最小值即可了。

## 代码：
```c
#include<bits/stdc++.h>
using namespace std;
//dalao可以帮忙改一下
#define maxn 200005
#define inf 0x3f3f3f3f
#define INF 9999999999
#define rdint(x) scanf("%d",&x)
#define rdllt(x) scanf("%lld",&x)
#define rdult(x) scanf("%lu",&x)
#define rdlf(x) scanf("%lf",&x)
#define rdstr(x) scanf("%s",x)
typedef long long  ll;
typedef unsigned long long ull;
typedef unsigned int U;
#define ms(x) memset((x),0,sizeof(x))
const long long int mod = 1e9 + 7;
#define Mod 1000000000
#define sq(x) (x)*(x)
#define eps 1e-3
typedef pair<int, int> pii;
#define pi acos(-1.0)
const int N = 1005;
#define REP(i,n) for(int i=0;i<(n);i++)
typedef pair<int, int> pii;
//dalao可以帮忙改一下
inline ll rd() {
    ll x = 0;
    char c = getchar();
    bool f = false;
    while (!isdigit(c)) {
        if (c == '-') f = true;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return f ? -x : x;
}
 
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a%b);
}
ll sqr(ll x) { return x * x; }
 
/*ll ans;
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1; y = 0; return a;
    }
    ans = exgcd(b, a%b, x, y);
    ll t = x; x = y; y = t - a / b * y;
    return ans;
}
*/
 
 
 
ll qpow(ll a, ll b, ll c) {
    ll ans = 1;
    a = a % c;
    while (b) {
        if (b % 2)ans = ans * a%c;
        b /= 2; a = a * a%c;
    }
    return ans;
}
 
 
double ax, ay, bx, by, tx, ty;
struct node {
    double x, y;
}indx[maxn];
 
double dis(double a, double b, double x, double y) {
    return sqrt(1.0*(a - x)*(a - x) + 1.0*(b - y)*(b - y))*1.0;
}
 
double dist[maxn], disa[maxn], disb[maxn];
 
int main()
{
    //ios::sync_with_stdio(0);
    rdlf(ax); rdlf(ay); rdlf(bx); rdlf(by); rdlf(tx); rdlf(ty);
    int n; rdint(n);
    double ans = 0.0;
    for (int i = 1; i <= n; i++) {
        rdlf(indx[i].x), rdlf(indx[i].y);
        dist[i] = 1.0*dis(indx[i].x, indx[i].y, tx, ty);
        disa[i] = 1.0*dis(ax, ay, indx[i].x, indx[i].y);
        disb[i] = 1.0*dis(bx, by, indx[i].x, indx[i].y);
        ans += 2.0*dist[i];
    }
    double Max = INF * 1.0;
    double Maxx = INF * 1.0;
    int posa, posb;
 
    for (int i = 1; i <= n; i++) {
        if (Max > disa[i] - dist[i]) {
            Max =1.0* disa[i] - 1.0*dist[i]; posa = i;
        }
        if (Maxx > disb[i] - dist[i]) {
            Maxx = 1.0*disb[i] - 1.0*dist[i]; posb = i;
        }
    }
//  cout << posa << ' ' << posb << endl;
    double sum = ans;
    if (Maxx < 0 && Max < 0) {
        if (posa != posb) {
            sum = ans + Maxx * 1.0 + Max * 1.0;
        }
        else {
            for (int i = 0; i <= n; i++) {
                if (i != posa) {
                    sum = min(sum, ans - dist[posa] + disa[posa] - dist[i] + disb[i]);
                }
            }
            for (int i = 0; i <= n; i++) {
                if (i != posb) {
                    sum = min(sum, ans - dist[posb] + disb[posb] - dist[i] + disa[i]);
                }
            }
        }
    }
    else {
        if (Max < Maxx) {
            sum = ans + disa[posa] - dist[posa];
        }
        else {
            sum = ans + disb[posb] - dist[posb];
        }
    }
    printf("%.9lf\n", 1.0*sum);
    return 0;
}
```


---

