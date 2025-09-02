# Triangle

## 题目描述

There is a right triangle with legs of length $ a $ and $ b $ . Your task is to determine whether it is possible to locate the triangle on the plane in such a way that none of its sides is parallel to the coordinate axes. All the vertices must have integer coordinates. If there exists such a location, you have to output the appropriate coordinates of vertices.

## 样例 #1

### 输入

```
1 1
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
YES
2 1
5 5
-2 4
```

## 样例 #3

### 输入

```
5 10
```

### 输出

```
YES
-10 4
-2 -2
1 2
```

# 题解

## 作者：Michaellg (赞：3)

## 题目分析
由于三角形顶点坐标均为整数，不妨将直角顶点固定为原点 $(0,0)$。

设另外两个顶点坐标为 $(x,y)$ 和 $(s,t)$，其中 $x^2+y^2=a^2,s^2+t^2=b^2$。由于两条直角边垂直，所以两个向量（$(x,y)$ 和 $(s,t)$）垂直，得 $(x,y)\cdot(s,t)=0$，即 $xs+yt=0$，所以 $\dfrac{s}{t}=-\dfrac{y}{x}$。

不妨设 $x>0,y>0$，枚举 $x$，通过 $y^2=a^2-x^2$ 可解出 $y$。再由 $\dfrac{s}{t}=-\dfrac{y}{x}$ 可得 $s$ 与 $t$ 的比例（注意：这个比例必须为最简比例，否则可能漏解），联立 $s^2+t^2=b^2$ 即可解出 $s$ 和 $t$ 的值，共有两组，不妨取 $s<0,t>0$ 的一组。其中有些解会使 $y,s,t$ 不是整数或者 $(x,y)$ 与 $(s,t)$ 连线与坐标轴平行，要舍去。

代码的时间复杂度为 $\mathcal{O}(n)$。

## 代码
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
int main() {
    int a, b;
    cin >> a >> b;
    for (int x = 1; x < a; x++) {
        int y = int(sqrt(a*a - x*x) + 0.001);
        if (y * y + x * x == a * a) { // 判断 y 是否为整数
            int g = __gcd(x, y);
            x /= g, y /= g; // 找到最简比例 x : y
            int k = int(sqrt(b*b / (x*x + y*y)) + 0.001);
            if (k*k * (x*x + y*y) == b*b) { // 判断 s 和 t 是否有整数解
                if (g*x != -k*y && g*y != k*x) { // 判断斜边是否与坐标轴平行
                    cout << "YES\n"; 
                    cout << "0 0\n";
                    cout << g*x << " " << g*y << "\n";
                    cout << -k*y << " " << k*x << "\n";
                    return 0;
                }
            }
            x *= g; // 恢复 x 的值
        }
    }
    cout << "NO\n";
    return 0;
}
```

---

## 作者：loser_seele (赞：2)

因为数据范围很小，考虑暴力枚举。

首先可以假设三角形总有一个顶点位于原点的位置，因为任意三角形都可以平移到一个顶点在原点上，这么做并不影响答案。

然后考虑枚举 $ (0,0) $ 到某点 $ (x,y) $ 的距离为  $ a $，这一步可以直接用枚举 $ x,y $ 的所有取值实现，然后因为三角形是直角三角形，再根据这个向量，作出其垂直向量，并且枚举这个向量的长度，如果等于 $ b $ 则输出答案。如果枚举所有的向量都无解则原问题一定无解。

这么做的时间复杂度看上去是 $ \mathcal{O}(n^3) $ 的，实际上因为长度等于 $ a $ 的变量数实际上很少，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
int a,b;
cin>>a>>b;
for(int i=1;i<=1000;i++)
for(int j=1;j<=1000;j++)
if(i*i+j*j==a*a)
{
for(int k=1;k<=1000;k++)
if(k*i%j==0)
{
int l=-k*i/j;
if(!l||k==i||l==j)
continue;
if(k*k+l*l==b*b)
{
cout<<"YES"<<'\n';
cout<<"0 0\n";
cout<<i<<' '<<j<<'\n';
cout<<k<<' '<<l;
return 0;
}
}
}
cout<<"NO";
}
```


---

## 作者：MoyunAllgorithm (赞：2)

**题目大意：**

在平面直角坐标系中，有直角三角形 $\triangle AOB$ ，其直角边为 $OA$ 和 $OB$ 。请构造一个这样的三角形，使得它的三边都不平行于坐标轴且顶点坐标是整数。（可能无解）

**思路：**

前置知识：平面直角坐标系、勾股定理、相似三角形

本题其实是数学题，我们不妨设点 $O$ 的坐标是 $(0,0)$ ，可以画出图：
![](https://cdn.luogu.com.cn/upload/image_hosting/spzzsor7.png)

如图，作 $AP \perp x$轴于点 $P$ ， $BQ \perp x$轴于点 $Q$ ，显然根据勾股定理，有

$OP^{2} + AP^{2} = AO^{2} $，$OQ^{2} + QB^{2} = BO^{2} $ 。

这个时候，我们只要暴力枚举 $AP$ 和 $BQ$ 的值，计算出 $OQ$ 和 $OP$ 的值，就可以确定这个 $\triangle AOB$ 。

那么，我们如何判定 $ \angle AOB = 90^{\circ}$ 呢？事实上，因为如果  $ \angle AOB = 90^{\circ}$ ，那么因为同时 $ \angle APO = \angle BQO =90^{\circ}$ ，可以得到

$ \triangle APO \sim \triangle OQB $

即 $\dfrac{OQ}{AP} = \dfrac{BQ}{OP}$

十字相乘，得 $ OQ·OP = AP·BQ$ 此时，可以轻松的判断 $ \angle AOB $ 是否为直角。

最后，需要避免斜边 $AB$ 平行 x轴，这个时候简单判断高度即可。代码非常简单，需要注意的是为了避免 `sqrt()` 运算出现问题，我们可以提前将平方根预处理出来。具体见代码
```c
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1005;
int sq[MAXN*MAXN];
int A,B;
int main()
{
	for(int i=1;i<=MAXN;i++) sq[i*i]=i;
	scanf("%d %d",&A,&B);
	int h1,h2,l1,l2;
    //如果i==A或者j==B，会出现平平行
	for(int i=1;i<A;i++)
	{
		for(int j=1;j<B;j++)
		{
			int l1=sq[A*A-i*i];
			int l2=sq[B*B-j*j];
			if(l1*l2==i*j&&i!=j)//判定直角和斜边
			{
				printf("YES\n0 0\n%d %d\n%d %d\n",-l1,i,l2,j);
				return 0;
			}
		}
	}
	puts("NO");//判断无解
	return 0;
}
```

谢谢观看(づ￣ 3￣)づ


---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF407A)

[CF 传送门](https://codeforces.com/contest/407/problem/A)

[AC 记录](https://codeforces.com/contest/407/submission/300575503)

# 题意简述

给定一个直角三角形，两直角边长为 $a$ 与 $b$ $(1\le a,b\le 1000)$。问能不能把它放在平面直角坐标系中，使得每个顶点对应的坐标为均整数，且三边均不与坐标轴平行。

# 题解

前置知识：[勾股定理](https://baike.baidu.com/item/%E5%8B%BE%E8%82%A1%E5%AE%9A%E7%90%86/91499)，[平面直角坐标系](https://baike.baidu.com/item/%E5%B9%B3%E9%9D%A2%E7%9B%B4%E8%A7%92%E5%9D%90%E6%A0%87%E7%B3%BB/1296463)，[相似三角形（主要用性质）](https://baike.baidu.com/item/%E7%9B%B8%E4%BC%BC%E4%B8%89%E8%A7%92%E5%BD%A2/159057)。

首先，根据勾股定理，先求出 $x_1$，$x_2$，$y_1$ 和 $y_2$ 使得 $x_1^2+x_2^2=a^2$ 且 $y_1^2+y_2^2=b^2$。\
**可能有多个解，一定不要忘记都遍历尝试一遍！**\
![](https://cdn.luogu.com.cn/upload/image_hosting/qn7hqh85.png)

然后把这两个三角形拼起来（为了方便输出，这里把直角顶点放在原点）。\
![](https://cdn.luogu.com.cn/upload/image_hosting/lsvvuv6g.png)

可是怎么判断 $\angle BA_1B=90^{\circ}$ 呢？\
这里就要用到相似三角形了（不会的赶紧去看前置知识（有链接））。\
若 $\angle BA_1B=90^{\circ}$ 且 $B_1C_1 \perp C_1C$，$BC\perp C_1C$，则 $\angle B_1A_1C_1=\angle A_1BC$（余角的等角相等）。\
那么就有 $\triangle A_1BC \sim \triangle A_1B_1C_1$。\
根据相似三角形的性质，$\dfrac{B_1C_1}{A_1C}=\dfrac{C_1A_1}{BC}$。\
十字相乘，从而 $B_1C_1\times BC=C_1A_1\times A_1C$。\
所以我们有了判断 $\angle BA_1B=90^{\circ}$ 的条件 $B_1C_1\times BC=C_1A_1\times A_1C$（因为这个条件可以反推相似再证明 $\angle BA_1B=90^{\circ}$）。\
那么最后就可以输出了。

# AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
#define CLOSE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define F first
#define S second
#define lowbit(x) x&-x
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int Stack[105];
inline void print(ll x){
    int cnt=0;
    if(x<0) putchar('-'),x=-x;
    while(x){
    	Stack[++cnt]=x%10;
    	x/=10;
    }
    while(cnt--) putchar((char)Stack[cnt+1]+'0');
    return;
}
int a,b;
vector<int> v[3];
void fun(int x,int p){
    for(int i=1;i*i<x;i++){
        int q=x-i*i;
        if((int)sqrt(q)*(int)sqrt(q)==q) v[p].push_back(i);//利用勾股定理
    }
}
int main(){
    cin>>a>>b;
    int A=a*a,B=b*b;
    fun(A,1);
    fun(B,2);//求解
    if(!v[1].size()||!v[2].size()){
        cout<<"NO";//若无解，直接输出NO
        return 0;
    }
    bool flag=0;
    for(int i=0;i<v[1].size();i++){
        for(int j=0;j<v[2].size();j++){
            int x=v[1][i],y=v[2][j],xx=sqrt(A-x*x),yy=sqrt(B-y*y);
            if(!x||!y) continue;
            if(x*y!=yy*xx){
                if(x*yy==y*xx) swap(yy,y);
                else continue;
            }
            if(x==y) y=-y;
            else yy=-yy;
            cout<<"YES\n";
            cout<<"0 0\n";//方便输出，直角顶点定在原点
            cout<<x<<' '<<xx<<'\n';
            cout<<y<<' '<<yy<<'\n';//输出
            flag=1;
            break;
        }
        if(flag) break;
    }
    if(!flag) cout<<"NO";
    return 0;
}
```

---

## 作者：zzhbpyy (赞：1)

### [Problem - 407A - Codeforces](https://codeforces.com/problemset/problem/407/A)

## 思路

要想构成不与坐标轴平行三角形，每条边都应该是[勾股数](https://baike.sogou.com/v4423976.htm?fromTitle=勾股数#:~:text=所谓勾股数，一般是指能够构成直角三角形三条边的三个正整数,(例如a%2Cb%2Cc)。即a²%2Bb²%3Dc²%2Ca%2Cb%2Cc∈N)。

为了满足构成直角的条件，两条边应该都是同一个勾股数的倍数。容易想到取 $a$ 和 $b$ 的最大公因数，将其暴力拆分成两数平方和。

设 $c^2+d^2=\gcd(a,b)$。这样，我们就可以构造出三个点：$(0,0)$，$(\frac{a}{\gcd(a,b)}\times c,\frac{a}{\gcd(a,b)}\times d)$ 和 $(-\frac{b}{\gcd(a,b)}\times d,\frac{b}{\gcd(a,b)}\times c)$。

这样交上去一看，发现 WA on test 11，原因是当 $\frac{a}{\gcd(a,b)}\times d=\frac{b}{\gcd(a,b)}\times c$ 时，斜边与坐标轴平行，我们只要取 $(0,0)$，$(\frac{a}{\gcd(a,b)}\times d,\frac{a}{\gcd(a,b)}\times c)$ 和 $(-\frac{b}{\gcd(a,b)}\times c,\frac{b}{\gcd(a,b)}\times d)$ 三个点即可。

## Code

```c++
int sqrt(int b){
	for(int i=1;i<=1000;i++){
		if(i*i>b)return i-1;
	}
	return 0;
}
bool check(int a){
	int h=sqrt(a);
	return h*h==a;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>a>>b;
	int l=0;
	int h=__gcd(a,b);
	for(l=1;l*l<=h*h;l++){
		if(check(h*h-l*l))break;
	}
	if(l*l>=h*h){
		cout<<"NO",exit(0);
	}cout<<"YES\n";
	cout<<"0 0\n";
	int c=l*(a/h),d=(int)sqrt(h*h-l*l)*(a/h),e=-(int)sqrt(h*h-l*l)*(b/h),f=(b/h)*l;
	if(c==e||d==f){
		cout<<(int)sqrt(h*h-l*l)*(a/h)<<' '<<l*(a/h)<<'\n'<<-(b/h)*l<<' '<<(int)sqrt(h*h-l*l)*(b/h)<<'\n';
	}
	else cout<<l*(a/h)<<' '<<(int)sqrt(h*h-l*l)*(a/h)<<'\n'<<-(int)sqrt(h*h-l*l)*(b/h)<<' '<<(b/h)*l<<'\n';
}
```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF407A)

## 题意
有一个直角三角形的两条直角边长度分别为 $a$ 和 $b$。你的任务是确定是否可以将该三角形定位在平面上，使其任意一条边均不平行于坐标轴，并且所有顶点的坐标为整数。如果存在这样的定位方式，输出对应顶点的坐标。

## 思路
这题数据很小，考虑一下暴力枚举。时间复杂度为 $\Theta(n^3)$，可以通过。我们假设一个点在原点上，然后枚举一条边长为 $a$ 的边且不与坐标轴平行，再得出另一条边。成功则输出 `YES` 和坐标，没有就直接输出 `NO`。

## code
```cpp
#include<bits/stdc++.h>、、万能头
using namespace std;
int a,b,x,y,i,j,k,g;
int gcd(int x,int y)//不用内部函数，从我做起
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int main()
{
	scanf("%d%d",&a,&b);//时间较少
	for(x=1;x<a;x++)
	{
		y=int(sqrt(a*a-x*x)+0.01);
		if(x*x+y*y==a*a)
		{
			g=gcd(x,y);
			x/=g;
			y/=g;
			k=int(sqrt(b*b/(y*y+x*x))+0.01);
			if(k*k*(x*x+y*y)==b*b)
			{
				if(g*x!=-k*y&&g*y!=k*x)
				{
					cout<<"YES"<<endl;
					cout<<"0 0"<<endl;
					cout<<g*x<<" "<<g*y<<endl;
					cout<<-k*y<<" "<<k*x<<endl;
					return 0; 
				}
			}
			x*=g;
		} 
	}
	cout<<"NO"<<endl;
	return 0;
}

```

---

## 作者：mirance2025 (赞：0)

### 题目描述
众所周知，一位 OIer 需要至少将题目读 $3$ 遍。

[CF407A](https://www.luogu.com.cn/problem/CF407A)

### 题意分析

我们把直角顶点固定在平面直角坐标系的原点 $(0, 0)$ 处。
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/9z49b2hk.png)
 
由相似三角形可知，$ \frac{x_1}{x_2} = - \frac{y_1}{y_2}$。

由勾股定理，可知，$x_1^2 + y_1^2 = a^2$，$x_2^2 + y_2^2 = b^2$。

假设 $x_1 > 0$，$y_1 > 0$，由 $x_1^2 + y_1^2 = a^2$ 推得 $y_1^2 = a^2 - x_1^2$，再由 $\frac{x_1}{x_2} = -\frac{y_1}{y_2}$ 知 $x_2 : y_2 = t$。

由 $x_2^2 + y_2^2 = b^2$ 可知 $(ty_2)^2 + y_2^2 = b^2$，解出 $y_2$。

```
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
int a, b;
int main(){
    scanf("%d%d", &a, &b);
    for(int ta = 1 ; ta < a ; ta++) {
        int tb = int(sqrt(a * a - ta * ta) + 0.001);
        if(tb * tb + ta * ta == a * a) {
            int g = __gcd(ta, tb);
            ta /= g, tb /= g; 
            int k = int(sqrt(b * b / (ta * ta + tb * tb)) + 0.001);
            if(k * k * (ta * ta + tb * tb) == b * b) {
                if(g * ta != -k * tb && g * tb != k * ta) {
                    printf("YES\n0 0\n"); 
					printf("%d %d\n%d %d\n", g * ta, g * tb, -k * tb, k * ta);
                    return 0;
                }
            }
            ta *= g;
        }
    }
    printf("NO\n");
    return 0;//华丽结束 
}
```

都看到这了，点个赞，关注 [zzxzzxCCC](https://www.luogu.com.cn/user/500803) 再走吧。

---

## 作者：02Ljh (赞：0)

提供一种需要的数学知识不多 不需要数学证明的做法（有点偏暴力枚举）

## 引理
- 勾股定理

$c^2=\sqrt{a^2+b^2}$

直角三角形的两条直角边的平方和等于斜边的平方

## 思路

一个直角三角形三条边均不于 $x,y$ 轴平行，每个顶点对应的坐标为均整数，那么这三边的长度必须都满足勾股定理，即对于每条边均能找到两个数的平方等于它的长度。

观察数据范围，发现 $a,b\leq1000$ 。那么，我们为何不把所有勾股数 $O(1000^2)$ 筛出来，然后在依次枚举每个点，看看他们是否合法。

为了方便讨论，我们不妨把其中一个点定为 $(0,0)$。

于是，我们就将代码写了出来，交上去。

${\color{Red} \mathbf{Wrong \ answer \ on \ 11} } $

~~过年来点红色，多喜庆~~

根据#11的测试点，我们发现，其实一个斜边长度可中，合法的直角边长度不止一个。

比如说：
$\sqrt{50^2}=\sqrt{1^2+7^2}=\sqrt{5^2+5^2}$

对这个算法进行优化，开一个 ```vector```,储存所有可能的情况。

那会不会爆空间捏？因为可爱的 ```vector``` 是动态分配内存的，所以也不用担心 MLE 。

**如果还没看懂 code中有详细的讲解**

实现上讲一个细节，不要用 ```yn``` 当变量名，这是个系统内部函数。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f
#define int long long
#define MAXN 1000019
#define WA puts("CCF");
#define MOD 100019
struct lxy
{
    vector<int> p1,p2;
    int flag;
} ;
lxy a[MAXN];//储存斜边长为整数的拆分方式
lxy gen[MAXN];//边长为根号的拆分方式
int get(int x,int y)//求斜边长
{
    return x*x+y*y;
}
bool hf(int lx1,int lx2)//是否为0（为0说明与x轴或者y轴平行）
{
    return (lx1!=0&&lx2!=0);
}
vector<int> xf,yf,xn,ynn,po;
/*
xf,yf 第一个点的坐标
xn,ynn 第二个点的坐标
po 第二个点是有哪个第一个点转化而来
*/
int gg;//斜边长
bool ck(int pos)
{
    int nx=xn[pos],ny=ynn[pos];
    if(hf(nx,ny)&&(abs(nx)*abs(nx)+abs(ny)*abs(ny))==gg)
    //当边不与x,y轴平行 且长度等于第三边时
    {
    	cout<<"YES\n"<<"0 0\n"; 
        cout<<xf[po[pos]]<<" "<<yf[po[pos]]<<"\n";//第一个点
        cout<<nx<<" "<<ny<<"\n"; //第二个
        return true; 
    }
    else return false;
}
 main()
{
    //freopen("sample1.in","r",stdin);
    //freopen("out.txt","w",stdout);
    /*ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);*/
    int n,m;
    int ans=INF;
    for(int i=1;i<=1000;i++)
    {
        for(int j=1;j<=1000;j++)
        {
            int sum=get(i,j);
            gen[sum].flag=true;
            gen[sum].p1.push_back(i);//存根号
            gen[sum].p2.push_back(j);
            int q=sqrt(sum);
            if(q*q==sum)
            {
                a[q].flag=true;
                a[q].p1.push_back(i);//是整数存整数
                a[q].p2.push_back(j);
            }
        }
    }
    cin>>n>>m;
    if(!a[n].flag||!a[m].flag||!gen[get(n,m)].flag)
    //三边中有一边筛不出来
    {
        cout<<"NO";
        return 0;
    }
    for(int i=0;i<a[n].p1.size();i++)//存第一边
    {
        xf.push_back(a[n].p1[i]);
        yf.push_back(a[n].p2[i]);
    }
    for(int i=0;i<xf.size();i++)
    {
        for(int j=0;j<a[m].p1.size();j++)//第二边
        {
            int xi=xf[i]-a[m].p1[j];
            int yi=yf[i]+a[m].p2[j];
            xn.push_back(xi);
            ynn.push_back(yi);
            po.push_back(i);
            xi=xf[i]-a[m].p2[j];//分x,y坐标讨论
            yi=yf[i]+a[m].p1[j];
            xn.push_back(xi);
            ynn.push_back(yi);
            po.push_back(i);
        }
    }
    gg=get(n,m);//斜边长
    for(int i=0;i<xn.size();i++)
    {
        if(ck(i)) return 0;//依次检查
    }
    cout<<"NO";
    return 0;
}

```
Happy 0x7e7 year!

![](https://cdn.luogu.com.cn/upload/image_hosting/ld18p4i7.png)

---

## 作者：wwxxbb (赞：0)

### 思路

先规定一些东西，变量名与题目不同。

不妨设两直角边长为 $x, y$，直角点 $A (0, 0)$，剩下两个点 $B (a_1, b_1), C (a_2, b_2)$，其中点 $A$ 在第二象限，点 $B$ 在第一象限，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rnbdpk2e.png)

设 $\overrightarrow{AB} = (a_1, b_1), \overrightarrow{AC} = (a_2, b_2)$。

$\because AB \perp AC$

$\therefore \overrightarrow{AB} \cdot \overrightarrow{AC} = 0$

$\therefore a_1 a_2 + b_1 b_2 = 0$

$\therefore \begin{cases}
    a_1 a_2 + b_1 b_2 = 0 \\
    a_1 ^ 2 + b_1 ^ 2 = x \\
    a_2 ^ 2 + b_2 ^ 2 = y
\end{cases}$

所以我们只需枚举 $a_1, a_2$，再用勾股定理算出 $b_1, b_2$，再判断是否合法。

注意：由于 C++ 的 `sqrt` 函数存在精度误差，所以算出 $b_1, b_2$ 后还要再判断 $a_1 a_1 + b_1 b_1 = x$，另一个点也是同理。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int x, y;
    cin >> x >> y;
    for (int a1 = 1; a1 < x; a1 ++) // 只需要枚举到 x - 1
    // 我枚举的是绝对值，所以下面判断条件少一个负号，输出的时候也要加上负号
        for (int a2 = 1; a2 < y; a2 ++) {
            int b1 = sqrt(x * x - a1 * a1), b2 = sqrt(y * y - a2 * a2);
            if (a1 * a1 + b1 * b1 != x * x || a2 * a2 + b2 * b2 != y * y) continue;
            if (a1 * a2 == b1 * b2 && b1 != b2)
            // 如果 b1 == b2，即两个点纵坐标相等，则斜边与 x 轴平行，不符合题意
                return cout << "YES\n0 0\n" << -a1 << ' ' << b1 << '\n' << a2 << ' ' << b2, 0; 
        }
    return cout << "NO", 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF407A)
## 思路
前置知识：初中数学。

众所周知，一条线段要能在平面直角坐标系中表示出来，并且不与坐标轴平行，这条线段的值一定是勾股数，所以我们对于题目给我们的两条线段要**先进行勾股数判定**。

但是，勾股数并不一定只能表示为一组两个整数的平方，有可能有多组整数满足条件（这个不判会 $\verb!WA on 21!$）。

而且，要让我们的这两条线段的夹角是 $\verb!Rt!$ 角，必须满足左边的直角三角形和右边的直角三角形相似（直角放在直线上基本模型）。

放张图解释一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/yit5y9ma.png)

$∵ ∠AOC=90\degree$

$∴ ∠DOC+∠AOB=90\degree$

又 $∵ ∠DOC+∠DCO=90\degree$

$∴ ∠AOB=∠DCO$

同理，可得 $\triangle ODC$ 与 $\triangle ABO$ 的另外对应角也相等

$∴ \triangle ODC ∽ \triangle ABO$

$∴ \frac{CD}{OD}=\frac{OB}{BA}$

$∴ CD \times BA=OD \times OB$
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
#define pf(x) (x*x)
vector< pair<int,int> >q[2];
inline void find(int co,int x){
    for (int i=1;i*i<x*x;++i){
        int la=(x*x)-(i*i);
        if (la<(i*i)) break;
        if (pf((int)(sqrt(la)))==la)
            q[co].push_back({i,(int)sqrt(la)});
    }
    if (!q[co].size()){cout<<"NO\n";exit(0);}
}//寻找平方和为 x 的两个数
inline bool similar(pair<int,int>x,pair<int,int>y){return (x.first*y.second==y.first*x.second);}//相似三角形的判定 SAS
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int a,b;cin>>a>>b;
    find(0,a),find(1,b);
    pair<int,int>x,y;int tag=0;
    for (int i=0;i<q[0].size();++i)
        for (int j=0;j<q[1].size();++j)
            if (similar(q[0][i],q[1][j])){
                tag=1;x=q[0][i],y=q[1][j];
                break;//找到一组就好了
            }
    if (!tag) return cout<<"NO\n",0;
    if (x.second==y.first) swap(x.first,x.second),swap(y.first,y.second);//如果斜边在同一直线上，换一下
    if (x.second==y.first) return cout<<"NO\n",0;//如果换完还在同一直线上，无解
    cout<<"YES\n0 0\n";
    cout<<x.first<<' '<<x.second<<'\n';
    cout<<-y.second<<' '<<y.first<<'\n';
    return 0;
}

```


---

## 作者：Cuiyi_SAI (赞：0)

## 解题思路

我们只考虑有一个顶点在原点 $O$ 的 $Rt\Delta AOB$。因为对于三个顶点，若原本都为整点，那么平移后也是整点，显然平移不会影响最终答案的存在性。所以我们先确定一个点，只考虑剩下两个点。

考虑两条始点在原点的向量 $\overrightarrow{OA}$  和 $\overrightarrow{OB}$，坐标分别为 $(x_1,y_1)$ 和 $(x_2,y_2)$ ，若他们围成的 $Rt\Delta AOB$ 满足要求，那么在边长上显然有:

$$
|\overrightarrow{OA}|^2=x_1^2+y_1^2=a^2
$$

$$
|\overrightarrow{OB}|^2=x_2^2+y_2^2=b^2
$$

因为 $\angle AOB$ 为直角，因此 $\overrightarrow{OA}~\bot~\overrightarrow{OB}$ ，也就有 $\overrightarrow{OA}\cdot\overrightarrow{OB}=0$。考虑将这条方程也作用到坐标上，也就是

$$
\begin{aligned}
&\overrightarrow{OA}\cdot\overrightarrow{OB}=0\\
&=(x_1\vec{i}+y_1\vec{j})(x_2\vec{i}+y_2\vec{j})=0\\
&=x_1x_2\vec{i}^2+y_1y_2\vec{j}^2+x_1y_2\vec{i}\cdot\vec{j}+x_2y_1\vec{i}\cdot\vec{j}\\
&=x_1x_2+y_1y_2=0
\end{aligned}
$$

将三个关于 $x_1,y_1,x_2,y_2$ 的方程联立，得到

$$
(x_1+x_2-b) (x_1+x_2+b)=(a-y_1-y_2)(a+y_1+y_2)
$$

设 $s=x_1+x_2,t=y_1+y_2$，则原方程等于

$$
(s-b)(s+b)=(a-t)(a+t)
$$

我们枚举 $s$，然后对方程左边枚举约数，就可以得到 $s,t$，然后再枚举 $x_1$ ，就可以得到 $x_2$，然后再枚举 $y_1$ ，也能顺势得到 $y_2$，最终即为答案。

```cpp
#include  <bits/stdc++.h>
using namespace std;
int a,b;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b;
	for(int i=-1000;i<=1000;i++)
	{
		long long num=(i-b)*(i+b);
		if(num==0) continue;
		bool flag=false;
		if(num<0) num=abs(num),flag=true;
		for(int j=1;j*j<=num;j++)
		{
			if(num%j!=0) continue;
			int c=j,d=num/j;
			if(flag) c=-c;
			if(c-a!=a-d) continue;
			int s=i,t=c-a;
			for(int x1=-a;abs(x1)<=a;x1++)
			{
				int x2=s-x1;
				for(int y1=1;abs(y1*y1)<=abs(x1*x2);y1++)
				{
					if(abs(x1*x2)%y1!=0) continue;
					int y2=-x1*x2/y1;
					if(y1+y2==abs(t)&&(x1*x1+y1*y1==a*a&&x2*x2+y2*y2==b*b||x1*x1+y2*y2==a*a&&x2*x2+y1*y1==b*b))
					{
						if(!(x1*x1+y1*y1==a*a&&x2*x2+y2*y2==b*b)) swap(y1,y2);
					    if(y1==y2) y2=-y2,x2=-x2;
					    if(x1==x2) x1=-x1,y1=-y1;
                        cout<<"YES"<<'\n';
						cout<<x1<<' '<<y1<<'\n';
						cout<<x2<<' '<<y2<<'\n';
						cout<<0<<' '<<0;
						return 0;
					}
				}
			}
		}
	}
	cout<<"NO";
	return 0;
}
```

---

