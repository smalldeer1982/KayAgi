# [ABC226D] Teleportation

## 题目描述

AtCoder国家位于无限多的笛卡尔坐标上。

AtCoder国家有 $N$ 个城镇，编号为 $1,2,...,N$。

镇i位于点$(x_i,y_i)$，没有两个不同编号的镇可以在同一坐标上。
AtCoder国家有过渡魔法 (以下简称魔法）。

魔法由一对整数 $(a,b)$ 标识，如果你在点 $(x,y)$ 并使用魔法 $(a,b)$，你可以穿越到 $(x+a，y+b)$。

有一个伟大的魔术师（以下简称魔法师），他可以选择任何一对整数 $(a,b)$ 并学习魔术 $(a,b)$。 魔法师还可以学习任何数量的不同种类的魔法。

当他想用魔法从一个城市移动到另一个城市时，他决定学习一些魔法，这样他就可以对所有一对 $(i,j)$ 不同的城市进行以下操作。

在你所学的魔法中只选择一种类型的魔法时，就只能重复使用所选的魔法，从城市 $i$ 移动到城市 $j$。

为了满足上述条件，魔法师至少要学会多少种不同的魔法？

## 样例 #1

### 输入

```
3
1 2
3 6
7 4```

### 输出

```
6```

## 样例 #2

### 输入

```
3
1 2
2 2
4 2```

### 输出

```
2```

## 样例 #3

### 输入

```
4
0 0
0 1000000000
1000000000 0
1000000000 1000000000```

### 输出

```
8```

# 题解

## 作者：__WaveN__ (赞：12)

# ABC226D Teleportation

## 题意描述

将一种魔法定义为 $(a,b)$，学习这种魔法后，即可从坐标 $(x,y)$ 移动到 $(x+a,y+b)$。

有 $N$ 个坐标，求最少学习多少种魔法才能相互到达所有坐标。

## 思路

有多种魔法，求最少学习的魔法个数，容易想到用 $\operatorname{set}$。

对于 $(x_1,y_1)$ 和 $(x_2,y_2)$，需要用到魔法 $(x_2-x_1,y_2-y_1)$。

由于要令魔法数量最小，所以要令 $(a,b)$ 的公约数最大，也就是最大公约数。

所以最终的魔法 $(a,b)$ 即为 $(\frac{x_2-x_1}{\gcd(x,y)},\frac{y_2-y_1}{\gcd(x,y)})$。

注意其中会出现负数，所以求 $\gcd(x,y)$ 时需要取绝对值。

## 上AC代码

```c++
#include<bits/stdc++.h>//万能头文件
using namespace std;
int x[510],y[510];//存坐标的数组
set<pair<int,int>>a;//建一个set保存每个魔法
int gcd(int x,int y)//辗转相除求最大公约数
{
	if(y==0)
		return x;
	return gcd(y,x%y);
}
int main()
{
	int n;//n个城镇
	scanf("%d",&n);//输入n
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x[i],&y[i]);//输入n个坐标
	for(int i=1;i<=n;i++)//双层枚举
	{
		for(int j=1;j<=n;j++)//注意两层循环都是从1~n，因为从A到B和从B到A是两种不同的情况
		{
			if(i==j)
				continue;//如果i,j相同就跳过，可以省略
            int tx=x[j]-x[i];//x变化的数量
            int ty=y[j]-y[i];//y变化的数量
            int GCD=abs(gcd(tx,ty));//求最大公约数
			a.insert(make_pair(tx/GCD,ty/GCD));//将a和b分别除以最大公约数，存进set
		}
	}
	printf("%d",a.size());//set的大小即为答案
	return 0;//完美结束！！
}
```

##### 管理员辛苦啦！！！感谢审核！！！



---

## 作者：CYZZ (赞：3)

# [Teleportation](https://www.luogu.com.cn/problem/AT_abc226_d)
## 题意
有 $n$ 个有坐标的城市，你可以选定任意组 $(a,b)$，每组可以使你从 $(x,y)$ 到达 $(x+a,y+b)$。问至少需要选几组才能使任意两个城市可以互相到达。

## 思路
考虑最简单的情况：从 $A(x_1,y_1)$ 到 $B(x_2,y_2)$，选 $(x_2-x_1,y_2-y_1)$ 一定没问题，但怎么让这个魔法被更多的城市使用呢？

注意到选的数 $(a,b)$ 必须满足 $\frac{x_2-x_1}{a}=\frac{y_2-y_1}{b}=k$，$k$ 为 $x_2-x_1,y_2-y_1$ 的**正**公因数。为了使 $a,b$ 尽量小，就要使 $k$ 尽量大，最大取到 $\gcd(x_2-x_1,y_2-y_1)$。

考虑到不同的城市中可能算出相同的 $a,b$，所以要去重。把 $(a,b)$ 装进自动去重的 set 里是最好的选择，最后答案就是 set 的大小。

## 细节
- 双重循环枚举 $i,j$ 都是从 $1$ 到 $n$。因为从 $i$ 到 $j$ 和从 $j$ 到 $i$ 是两种不同的情况。
- 算出来的 $\gcd$ 需要取绝对值~~因为是**最大**公因数嘛~~。如果不取绝对值，举个例子：$(x_j-x_i,y_j-y_i)=(-9,-6)$ 时算出来 $\gcd$ 是 $-3$，$(a,b)=(3,2)$，结果与取 $(9,6)$ 时算出的一样，但显然 $(a,b)$ 应该是 $(-3,-2)$。最后导致答案少了一倍。~~当然你在输出时乘上二也行。~~

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[505][2];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i][0],&a[i][1]);
    }
    set<pair<int,int>>s;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)//要从1~n
        {
            if(i==j)
                continue;
            int x=a[j][0]-a[i][0],y=a[j][1]-a[i][1],z=abs(__gcd(x,y));//要取abs
            s.insert(make_pair(x/z,y/z));
        }
    }
    printf("%d",s.size());
}

```

希望本篇题解能帮到大家！

---

## 作者：Tang_poetry_syndrome (赞：2)

## [ABC226D] Teleportation
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc226_d) [Atcoder题面](https://atcoder.jp/contests/abc226/tasks/abc226_d)
### 题目大意
给定 $N$ 对坐标，假定当前坐标为 $(X,Y)$，设定操作 $f(x,y)$，则使用该操作能移动到 $(X+x,Y+y)$，求最小不同操作数，使得任意一对坐标能以同一种操作移动到另一对坐标上。
### 思路
容易得出连接坐标 $(X_i,Y_i)$ 与 $(X_j,Y_j)$ 的最优操作为 $(\frac{X_i-X_j}{\gcd(X_i,X_j)},\frac{Y_i-Y_j}{\gcd(Y_i,Y_j)})$。  
举个栗子：（这里我们仅考虑编号小的点走向编号大的点）  
![](https://cdn.luogu.com.cn/upload/image_hosting/6uo0bz3i.png)  
$n=3,X_1=0,Y_1=0,X_2=3,Y_2=3,X_3=-1,Y_3=-1$  
若操作为 $f(2,2)$，则该操作仅能连接 $(0,0)$ 与 $(2,2)$，若操作为 $f(1,1)$，该操作能连接 $(-1,-1),(0,0)$ 与 $(2,2)$。  
这可以证明间距越小，收益越大。  
然后因为该方案将出现两次 $f(1,1)$，所以考虑用 `set` 去重。
最后，题目要求任意两点直接连通，于是答案为 `set` 大小的两倍。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e2+10;
ll n,x[N],y[N];
set<pair<ll,ll> >s;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    	cin>>x[i]>>y[i];
    for(int i=1;i<n;i++)
    	for(int j=i+1;j<=n;j++)
    		{
    			int xchange=x[j]-x[i],ychange=y[j]-y[i],Gcd=__gcd(xchange,ychange);
    			s.insert(make_pair(xchange/Gcd,ychange/Gcd));
			}
	cout<<s.size()*2;
	return 0;
} 
```
[提交记录](https://atcoder.jp/contests/abc226/submissions/45475693)

---

## 作者：e4fsrc2e4fsrc2 (赞：1)

## [Teleportation](https://www.luogu.com.cn/problem/AT_abc226_d)
## 题意
魔法：学习 $(a,b)$ 就可以从 $(x,y)$ 到 $(x+a,y+b)$。

求这 $N$ 个点可以相互到达的学习的魔法数的最小值。
## 思路分析
考虑贪心。

首先从 $i$ 到 $j$，是与从 $j$ 到 $i$ 是不一样的。所以只要计算好从 $i$ 到 $j(i<j)$ 的方案数，再乘 $2$ 即可。

实际上，从 $(x1,y1)$ 到 $(x2,y2)$ 只需要学习 $(x1-x2,y1-y2)$ 即可。又要让两个点尽量能够相互往来，所以除以它们的最大公约数。

其次，输入的数不一定是单调的，所以有可能出现负数，故需要用 ```set``` 来解决。

## AC代码
```cpp
#include<bits/stdc++.h>
#define R register int
using namespace std;
const int N=501;
int n,a[N],b[N];
set<pair<int,int>>s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(R i=1; i<=n; i++)cin>>a[i]>>b[i];
	for(R i=1; i<=n; i++)
		for(R j=i+1; j<=n; j++){
				R x=a[i]-a[j],y=b[i]-b[j],z=__gcd(x,y);
				s.insert({x/z,y/z});
			}
	cout<<s.size()*2;
	return 0;
}

```

---

## 作者：run_away (赞：0)

## 题意

给 $n$ 组坐标 $(x_i,y_i)$，你可以选择学习任意一个形式为 $(a_i,b_i)$ 的魔法。

设当前你在 $(x,y)$，对于每一个魔法 $i$，你可以使用它并到达 $(x+a_i,y+b_i)$。

每个魔法都可以重复使用，求至少需要多少魔法可以让 $n$ 个坐标互相到达。

## 分析

从 $(x_1,y_1)$ 到 $(x_2,y_2)$，需要 $(x_2-x_1,y_2-y_1)$ 的魔法。

为了让魔法的数量尽量少，需要让 $a$ 和 $b$ 的最大公因数尽可能大。

取它们的最大公因数为 $g$，那么使这两个城市间互相抵达的最佳魔法为 $(\frac{x_2-x_1}{g},\frac{y_2-y_1}{g})$。

因为不能重合，所以可以用一个 set 去重。

因为两个城市要双向联通，所以最终答案为 set 大小的二倍。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll mod=1e9+7,maxn=5e2+5,maxt=505;
ll n;
pair<ll,ll>p[maxn];
set<pair<ll,ll> >s;
signed main(){
    n=read();
    for(ll i=1;i<=n;++i){
        p[i].first=read(),p[i].second=read();
    }
    for(ll i=1;i<=n;++i){
        for(ll j=i+1;j<=n;++j){
            ll x=p[j].first-p[i].first,y=p[j].second-p[i].second;
            ll g=__gcd(x,y);
            s.insert({x/g,y/g});
        }
    }
    printf("%lld",s.size()<<1);
    return 0;
}
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：AT_abc226_d [ABC226D] Teleportation

[题目传送门](https://www.luogu.com.cn/problem/AT_abc226_d)

## 思路

有多种过渡魔法，统计过渡魔法个数，容易想到用 [set](https://www.luogu.com/article/zpz9oxbk)。

对于从 $(x,y)$ 到 $(x1,y1)$ 方式，是 $(x1-x,y1-y)$ 的过渡魔法。

因为要令数量最小，所以要令 $(a,b)$ 的公约数最大，也就是最大公约数（C++有`__gcd`）。

所以最终的过渡魔法 $(a,b)$ 即为：$(\frac {x1-x}{\operatorname{abs}(\gcd (x,x1))},\frac {y1-y}{\operatorname{abs}(\gcd (y,y1))})$。

把 $(a,b)$ inesrt 进 set，最后输出 set 的元素个数就行了。

## AC代码

```cpp
#include <bits/stdc++.h>
#define fin(x) freopen (x,"r",stdin)
#define fout(x) freopen (x,"w",stdout)
using namespace std;
int n;
pair<int,int> a[501];
set<pair<int,int> > st; 
signed main ()
{
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i].first>>a[i].second;
	for (int i=1;i<=n;i++)	
		for (int j=1;j<=n;j++)
		{
			if (i==j) continue;
			int tx=a[j].first-a[i].first,ty=a[j].second-a[i].second;
			st.insert (make_pair (tx/abs (__gcd (tx,ty)),ty/abs (__gcd (tx,ty)))); 
		}
	cout<<st.size ();
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc226_d)
# 题目描述
存在 $n$ 个坐标。有若干次操作，其中每一次操作 $(a,b)$ 能使原坐标 $(x,y)$ 转移到 $(a+x,b+y)$。

求至少要几种不同的魔法使得能在 $n$ 个坐标中相互到达。
# 题目分析
用 `set` 去重。因为坐标 $(x_{1},y_{1})$ 与坐标 $(x_{2},y_{2})$ 之间需要魔法 $(\Delta x,\Delta y)$。

将需要的魔法放在 `set` 中去重。

因为每一个魔法需要在更多的地方被使用，且没有使用限制，想到 $\gcd$。

将每一个魔法 $(\Delta x,\Delta y)$ 转化为 $(\frac{\Delta x}{\left|\gcd(\Delta x,\Delta y)\right|},\frac{\Delta y}{\left|\gcd(\Delta x,\Delta y)\right|})$。

将最简魔法塞入 `set` 中，`set` 的大小即为 `ans`。
# 参考代码
```cpp
//你们甭想抄我代码，哈哈哈
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e2+5; 
int n;
struct node{
	int x;
	int y;
}e[MAXN];
set<node>a;
int gcd(int x,int y){
	if(y==0)return x;
	return gcd(y,x%y);
}
int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>e[i].x>>e[i].y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i==j)continue;
	        int Delta_x=e[j].x-e[i].x;
    	    int Delta_y=e[j].y-e[i].y;
        	int gcdd=abs(gcd(Delta_x,Delta_y));
			a.insert(node{Delta_x/gcdd,Delta_y/gcdd});
		}
	cout<<a.size();
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
对于两个点之间的的移动方式步数越小越好，我们可以先构造一个肯定能行的。

就例如两个点 $(x1,y1)$ 和 $(x2,y2)$，那么我们需要的是 $(x1-x2,y1-y2)$ 一步走到，然后就可以把操作缩小，显然距离越近越好，那么同时除以最大公约数就可以了。

最后这里注意一下操作可能会出现负数，然而 c++14 的 $\gcd$ 函数不能处理负数，需要取一个绝对值。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000;
int a[maxn],b[maxn];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	set<pair<int,int>>S;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j){
				int x=a[i]-a[j],y=b[i]-b[j];
				S.insert({x/abs(__gcd(x,y)),y/abs(__gcd(x,y))});
			}
		}
	}
	cout<<S.size()<<"\n";
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

题意：给定 $ n $ 个城市的坐标，每次可以学习一种魔法 $ (a,b) $，学习后可以从坐标 $ (x,y) $ 到达 $ (x+a,y+b) $，求使得城市之间可以两两到达需要学习的最少魔法数量。

实际上，从 $ (x_1,y_1) $ 到达 $ (x_2,y_2) $ 只需要学习魔法 $ (\vert x_1-x_2 \vert,\vert y_1-y_2 \vert ) $ 即可，然后把这个坐标约分之后统计有多少不同的魔法即可。

注意虽然需要约分，但是约分时不能去掉原本的符号，因为不同符号的魔法被视为不同方案。

这里判断重复的过程用 STL 的 unordered_map 实现，时间复杂度 $ \mathcal{O}(n^2) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int gcd(int x,int y)
{
if(x==0)
return y;
if(y==0)
return x;
return gcd(y,x%y);
}
unordered_map<int,bool>xzy;
int x[1010],y[1010];
signed main()
{
ios::sync_with_stdio(0);
int n;
cin>>n;
for(int i=1;i<=n;i++)
cin>>x[i]>>y[i];
int ans=0;
for(int i=1;i<=n;i++)
for(int j=1;j<=n;j++)
{
if(i!=j)
{
int gcdx=x[i]-x[j],gcdy=y[i]-y[j];
int gcder=gcd(abs(gcdx),abs(gcdy));
gcdx/=gcder,gcdy/=gcder;
//cout<<gcdx<<' '<<gcdy<<endl;
int res=gcdx*19260817LL+gcdy*998244353LL;
/*if(!xzy[gcdx]||!yz[gcdy])
ans++;
xz[gcdx]=1,yz[gcdy]=1;*/
if(!xzy[res])
ans++;
xzy[res]=1;
}
}
cout<<ans<<endl;
}
```


---

