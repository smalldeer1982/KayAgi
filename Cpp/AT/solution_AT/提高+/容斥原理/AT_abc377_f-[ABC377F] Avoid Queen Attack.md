# [ABC377F] Avoid Queen Attack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc377/tasks/abc377_f

縦 $ N $ マス、横 $ N $ マスの $ N\ ^\ 2 $ マスからなるマス目があります。 上から $ i $ 行目 $ (1\leq\ i\leq\ N) $ 、左から $ j $ 列目 $ (1\leq\ j\leq\ N) $ のマスをマス $ (i,j) $ と呼ぶことにします。

それぞれのマスは、空マスであるかコマが置かれているかのどちらかです。 マス目には合計で $ M $ 個のコマが置かれており、$ k $ 番目 $ (1\leq\ k\leq\ M) $ のコマはマス $ (a\ _\ k,b\ _\ k) $ に置かれています。

あなたは、すでに置かれている**どのコマにも取られないように**、いずれかの**空マス**に自分のコマを置きたいです。

マス $ (i,j) $ に置かれているコマは、次のどれかの条件を満たすコマを取ることができます。

- $ i $ 行目に置かれている
- $ j $ 列目に置かれている
- $ i+j=a+b $ となるようなマス $ (a,b)\ (1\leq\ a\leq\ N,1\leq\ b\leq\ N) $ に置かれている
- $ i-j=a-b $ となるようなマス $ (a,b)\ (1\leq\ a\leq\ N,1\leq\ b\leq\ N) $ に置かれている
 
たとえば、マス $ (4,4) $ に置かれているコマは、以下の図で青く示されたマスに置かれているコマを取ることができます。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc377_f/8d18db86e94185f3231deea439fe06a4aa9df2f8.png)

あなたがコマを置くことができるマスがいくつあるか求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq10\ ^\ 9 $
- $ 1\leq\ M\leq10\ ^\ 3 $
- $ 1\leq\ a\ _\ k\leq\ N,1\leq\ b\ _\ k\leq\ N\ (1\leq\ k\leq\ M) $
- $ (a\ _\ k,b\ _\ k)\neq(a\ _\ l,b\ _\ l)\ (1\leq\ k\lt\ l\leq\ M) $
- 入力はすべて整数
 
### Sample Explanation 1

すでに置かれているコマは、以下の図で青く示されたマスに置かれたコマを取ることができます。 !\[\](https://img.atcoder.jp/abc377/49766c3613371e99673e5722bd64ad58.png) よって、あなたがすでに置かれているコマに取られないように自分のコマを置くことができるマスはマス $ (6,6) $ とマス $ (7,7) $ の $ 2 $ つです。

### Sample Explanation 2

$ 10\ ^\ {18} $ マスのうち、置くことができないマスは $ 1 $ 行目のマス、$ 1 $ 列目のマス、およびマス $ (1,1), $ マス $ (2,2),\ldots, $ マス $ (10\ ^\ 9,10\ ^\ 9) $ の $ 3\times10\ ^\ 9-2 $ マスです。 答えが $ 2\ ^\ {32} $ 以上になる場合があることに注意してください。

## 样例 #1

### 输入

```
8 6
1 4
2 1
3 8
4 5
5 2
8 3```

### 输出

```
2```

## 样例 #2

### 输入

```
1000000000 1
1 1```

### 输出

```
999999997000000002```

## 样例 #3

### 输入

```
20 10
1 4
7 11
7 15
8 10
11 6
12 5
13 1
15 2
20 10
20 15```

### 输出

```
77```

# 题解

## 作者：xpz0525 (赞：5)

### [ABC377F] Avoid Queen Attack 题解
本题因为棋子数量少，可以采用和 C 题类似的思路，从已有的棋子出发，去计算不能放棋子的格子数量。 

难点在于，皇后的攻击范围是沿着 8 个方向延伸的。所以我们不能简单地用一个 `set` 来存放不能放棋子的格子坐标。我们只能每次考虑新的皇后攻击范围和之前的皇后有哪些点重复，这样我 们就可以不断地往不能放棋子的格子数量中加上（原本能攻击到的格子数量 $-$ 已经被之前考虑的皇后攻击过的格子）即可。 

实现上，可以先用 B 题的思路考虑纵横两个方向上有哪些格子会被攻击，计算剩余的格子数量。 然后再考虑一条对角线，用对角线长度减去和之前纵横两个方向上重复的格子数量，再将答案减去这个结果。最后再考虑另一条对角线，用对角线长度减去和之前所有方向上重复的格子数量， 再将答案减去这个结果即可。

**AC** 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int n,q; 
	cin>>n>>q; 
	set<int> h,v,d1,d2; // d1 存 i+j=d 的对角线，d2 存 i-j=d 的对角线 
	for(int k=1,i,j;k<=q;k++){ 
	    cin>>i>>j; 
	    h.insert(i); 
	    v.insert(j); 
	    d1.insert(i+j);
	    d2.insert(i-j);
	 } 
	ll ans=1ll*(n-h.size())*(n-v.size()); 
	for(int d:d1){ // i+j=d 的对角线 
	    set<int> s; // 记录已经被算过的行坐标 
	    for(int i:h){ // 找到所有和该对角线相交的水平线 
	        if(1<=d-i&&d-i<=n){ 
	            s.insert(i); 
	        } 
	    } 
	    for(int j:v){ // 找到所有和该对角线相交的垂直线 
	        if(1<=d-j&&d-j<=n){ 
	            s.insert(d-j); 
	        } 
	    } 
	    int len=0; 
	    if(d<=n+1){ // 在左上部分, 列坐标只能取1~d-1 
	        len=d-1; 
	    }else{ // 在右下部分，列坐标只能取d-n~n 
	        len=n-(d-n)+1; 
	    } 
	    ans-=len-s.size(); 
	} 
	for(int d:d2){ // i-j=d 的对角线 
	    set<int> s; // 记录已经被算过的行坐标 
	    for(int i:h){ // 找到所有和该对角线相交的水平线 
	        if(1<=i-d&&i-d<=n){ 
	            s.insert(i); 
	        } 
	    } 
	    for(int j:v){ // 找到所有和该对角线相交的垂直线 
	        if(1<=j+d&&j+d<=n){ 
	            s.insert(j+d); 
	        } 
	    } 
	    for(int e:d1){ // i-j=d i+j=e => i=(d+e)/2 j=(e-d)/2 
	        if((d+e)%2) continue; // 不相交 
	        int si=(d+e)/2,sj=(e-d)/2; 
	        if(si>=1&&si<=n&&sj>=1&&sj<=n){ 
	            s.insert(si); 
	        } 
	    } 
		int len=0; 
		if(d>=0){ // i>=j 在左下部分，列坐标只能取1~n-d 
			len=n-d; 
		}else{ // 在右上部分，列坐标只能取1-d~n 
			len=n-(1-d)+1; 
		} 
		ans-=len-s.size(); 
	} 
	cout<<ans;
	return 0;
}
```

[$\textit{\textmd Write by @xpz0525 }$](https://www.luogu.com.cn/user/787357)$\textit{\textmd On November 6, 2024}$

---

## 作者：include13_fAKe (赞：3)

## 前言

CSP 考完晚上在补文化课，没打 ABC。

赛后发现这次比赛考了好多和国际象棋有关的题（我本来就是一名国际象棋棋手），并且 F 题这么简单？

[我的国际象棋战绩](https://www.luogu.com.cn/paste/833k0ajr)

## 思路

以下称不能放棋子为**被标记**。称有无横行覆盖、有无竖列覆盖、有无左斜行覆盖、有无右斜行覆盖为**覆盖情况**。总的覆盖情况共 $2^4=16$ 种。

小容斥题。

读入棋子时就标记它所控制的格子，时间复杂度 $O(nm)$，无法接受。

考虑记录每个棋子控制的横行、竖列、左斜行、右斜行，然后记录哪些横行、竖列、左斜行、右斜行被标记了。左斜行和右斜行可以用 $x$ 和 $y$ 的和与差来表示，开 `map` 不会炸。然后枚举每一种覆盖情况，以及覆盖它们的行、列、左斜行、右斜行即可。时间复杂度 $O(m^4)$。

因为当横行和数列固定时，左斜行和右斜行也固定下来了，故可以在算**同时被横行、竖列、左斜行覆盖的情况**、**同时被横行、竖列、右斜行覆盖的情况**或者**同时被时横行、竖列、左斜行、右斜行覆盖的情况**时，仅枚举横行和竖列即可。时间复杂度 $O(m^2)$。

对于**同时被横行、左斜行、右斜行覆盖的情况**和**同时被竖列、左斜行、右斜行覆盖的情况**，可以枚举左斜行和右斜行做到时间复杂度 $O(m^2)$。

对于两种线（指横行、竖列、左斜行、右斜行中的两者）覆盖的情况，直接枚举即可，时间复杂度 $O(m^2)$。

注意判定格子的合法性的问题。左斜行和右斜行相交的情况可以用和差问题来处理。

此外要注意如何 $O(1)$ 计算每一条斜线的长度，留给读者思考。

总时间复杂度 $O(m^2)$。细节有点多，需要一定代码能力。

## 代码

[Submission](https://atcoder.jp/contests/abc377/submissions/59204652)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

map<int,int> A,B,C,D;
struct node{
	int x,y;
	int a,b,c,d;//横、竖、左斜、右斜  
}ch[2024];
int n,m;
int a[2024],b[2024],c[2024],d[2024];
int include13=0;
struct node2{
	int x,y;
}ab[2024*2024],cd[2024*2024];
int ptr1,ptr2;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>ch[i].x>>ch[i].y;
		ch[i].a=ch[i].x,ch[i].b=ch[i].y,ch[i].c=ch[i].x+ch[i].y,ch[i].d=ch[i].x-ch[i].y;
		a[i]=ch[i].a,b[i]=ch[i].b,c[i]=ch[i].c,d[i]=ch[i].d;
		A[ch[i].a]=1,B[ch[i].b]=1,C[ch[i].c]=1,D[ch[i].d]=1;
	}
	sort(a+1,a+m+1),sort(b+1,b+m+1),sort(c+1,c+m+1),sort(d+1,d+m+1);
	int a1=unique(a+1,a+m+1)-a-1;
	int b1=unique(b+1,b+m+1)-b-1;
	int c1=unique(c+1,c+m+1)-c-1;
	int d1=unique(d+1,d+m+1)-d-1;
//	cout<<a1<<' '<<b1<<' '<<c1<<' '<<d1<<endl;
	include13+=a1*n;
//	cout<<include13<<endl;
	include13+=b1*n;
//	cout<<include13<<endl;
	for(int i=1;i<=c1;i++){
		int num=c[i]-1;
		if(num>n)	num=2*n-num;
		include13+=num;
	}
//	cout<<include13<<endl;
	for(int i=1;i<=d1;i++){
		int num=n-abs(d[i]);
		include13+=num;
	}
//	cout<<include13<<endl;
	//xy1 x+y xy2 x-y;
	for(int i=1;i<=a1;i++){
		for(int j=1;j<=b1;j++){
			int x=a[i],y=b[j];
//			cout<<'#'<<x<<' '<<y<<endl;
			ab[++ptr1]=(node2){x,y};
			include13--;
			if(C[x+y])	include13++;
			if(D[x-y])	include13++;
			if(C[x+y]&&D[x-y])	include13--;
		}
	}
//	cout<<include13<<endl;
	for(int i=1;i<=c1;i++){
		for(int j=1;j<=d1;j++){
			int xy1=c[i],xy2=d[j];
			if((xy1+xy2)%2==0){
				int x=(c[i]+d[j])/2,y=(c[i]-d[j])/2;
				if(1<=x&&x<=n&&1<=y&&y<=n){
//					cout<<'#'<<x<<' '<<y<<endl;
					cd[++ptr2]=(node2){x,y};
					include13--;
					if(A[x])	include13++;
					if(B[y])	include13++;
				}
			} 
		}
	}
//	cout<<include13<<endl;
	for(int i=1;i<=a1;i++){
		for(int j=1;j<=c1;j++){
			int x=a[i],xy1=c[j];
			int y=xy1-x;
			if(1<=x&&x<=n&&1<=y&&y<=n){
//				cout<<x<<' '<<y<<endl;
				include13--;
			}
		}
	}
//	cout<<include13<<endl;
	for(int i=1;i<=a1;i++){
		for(int j=1;j<=d1;j++){
			int x=a[i],xy2=d[j];
			int y=x-xy2;
			if(1<=x&&x<=n&&1<=y&&y<=n){
				include13--;
			}
		}
	}
	for(int i=1;i<=b1;i++){
		for(int j=1;j<=c1;j++){
			int y=b[i],xy1=c[j];
			int x=xy1-y;
			if(1<=x&&x<=n&&1<=y&&y<=n){
				include13--;
			}
		}
	}
	for(int i=1;i<=b1;i++){
		for(int j=1;j<=d1;j++){
			int y=b[i],xy2=d[j];
			int x=xy2+y;
			if(1<=x&&x<=n&&1<=y&&y<=n){
				include13--;
			}
		}
	}
	cout<<n*n-include13<<endl;
	return 0;
} //ABC377F 
```

---

## 作者：Jerrywang09 (赞：2)

笔者友情提醒：此做法太过搞笑，请勿在吃饭时观看。

容易想到一个很暴力的容斥：先把 $n^2$ 个点全部算上，然后枚举每个集合 $S$，对于 $S$ 中**所有皇后都可以攻击到的格子总数**乘上容斥系数。

但考虑到很多情况下，枚举的皇后集合 $S$ 都可以攻击到的格子总数是 $0$。那么想办法不计算这些情况。

因此，可能对答案产生贡献的 $S$ 一定满足以下两个特征之一：

1. 所有皇后在一条直线上。
2. 所有皇后的攻击范围交于一个格子。

对于情况 1，计数每行、每列、每个斜线的皇后数目 $t$。对角线的处理方式可以参见代码。$len$ 表示这一条直线的长度，则对答案的贡献是
$$
len\sum_{i=1}^t (-1)^i \binom t i
$$

对于情况 2，先求出所有皇后的攻击范围可能交于哪些格子。然后枚举这些格子，枚举 $S$ 中是否含有行、列、对角线上的皇后。以 $S$ 中只含有行、列上的皇后为例，对答案的贡献是
$$
\sum_{i=1}^{t_1} \sum_{j=1}^{t_2} (-1)^{i+j} \binom {t_1} i \binom {t_2} j\\
=\sum_{i=1}^{t_1} (-1)^i \binom {t_1} i\sum_{j=1}^{t_2} (-1)^{j}  \binom {t_2} j
$$

注意到前后两个求和可以在处理情况 1 时预处理，于是本题就做完了。

注意使用 `__gnu_pbds`，否则会 TLE。如果还有不理解的，或者感觉此做法太搞笑想吐槽一下的，欢迎私信笔者。

```cpp
// [ABC377F] Avoid Queen Attack
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=1005;
using namespace std;
char buf[1<<21], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int n, m; ll ans, C[N][N];
__gnu_pbds::gp_hash_table<int, ll> row, col, dia1, dia2;
vector<pair<int, int>> S;

int main()
{
#ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin);
#endif
    n=read(), m=read(); ans=(ll)n*n;
    rep(i, 0, m)
    {
        C[i][0]=1;
        rep(j, 1, i) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    rep(i, 1, m)
    {
        int x=read(), y=read();
        row[x]++, col[y]++;
        dia1[x-y]++, dia2[x+y]++;
    }
    for(auto &[x,t]:row)
    {
        ll sum=0;
        rep(x, 1, t) sum+=C[t][x]*((x&1)?-1:1);
        ans+=sum*n; t=sum;
    }
    for(auto &[x,t]:col)
    {
        ll sum=0;
        rep(x, 1, t) sum+=C[t][x]*((x&1)?-1:1);
        ans+=sum*n; t=sum;
    }
    for(auto &[x,t]:dia1)
    {
        ll sum=0;
        rep(x, 1, t) sum+=C[t][x]*((x&1)?-1:1);
        ans+=sum*(n-abs(x)); t=sum;
    }
    for(auto &[x,t]:dia2)
    {
        ll sum=0;
        rep(x, 1, t) sum+=C[t][x]*((x&1)?-1:1);
        ans+=sum*(min(x, n+n+2-x)-1); t=sum;
    }
    for(auto [x,t]:row) for(auto [y,t]:col)
        S.push_back({x, y});
    for(auto [x,t]:row) for(auto [y,t]:dia1) if(x-y>0)
        S.push_back({x, x-y});
    for(auto [x,t]:row) for(auto [y,t]:dia2) if(y-x>0)
        S.push_back({x, y-x});
    for(auto [x,t]:col) for(auto [y,t]:dia1) if(x+y<=n)
        S.push_back({x+y, x});
    for(auto [x,t]:col) for(auto [y,t]:dia2) if(y-x>0)
        S.push_back({y-x, x});
    for(auto [x,t]:dia1) for(auto [y,t]:dia2) if((x+y)%2==0)
        S.push_back({(x+y)/2, (y-x)/2});
    stable_sort(S.begin(), S.end());
    S.erase(unique(S.begin(), S.end()), S.end());
    for(auto [x,y]:S) if(1<=x && x<=n && 1<=y && y<=n)
    {
        ans+=row[x]*col[y]+row[x]*dia1[x-y]+row[x]*dia2[x+y]+col[y]*dia1[x-y]+col[y]*dia2[x+y]+dia1[x-y]*dia2[x+y];
        ans+=row[x]*col[y]*dia1[x-y]+row[x]*col[y]*dia2[x+y]+row[x]*dia1[x-y]*dia2[x+y]+col[y]*dia1[x-y]*dia2[x+y];
        ans+=row[x]*col[y]*dia1[x-y]*dia2[x+y];
    }
    printf("%lld", ans);

    return 0;
}
```

---

## 作者：kczw (赞：1)

# 题意
一个 $N\times N$ 的棋盘上有 $M$ 个皇后（皇后的移动规则题面有图片讲解），问有多少个空位是任意皇后不能一步走到的。

$N\le10^9,M\le10^3$。
# 思路
一个皇后所能控制的点，可以看做四条直线。如果只有一个皇后，我们可以很方便的计算四条直线被棋盘覆盖的长度。

这里四条直线的一次函数表达式也很好推，对于一个格子 $(a,b)$，如果上面有一个皇后，那么四条直线的一次函数表达式为 $y=b,x=a,y=x+(b-a),y=-x+(a+b)$。

现在需要处理的问题是多个皇后相交的点会多算的问题，既然多算了，我们可以统计多算的贡献并减掉。

已知 $M\le10^3$，所以最多有 $4\times 10^3$ 条不同直线，注意到直线分四种（一种角度为一种），而同种直线是平行的，不会相交，所以其实交点只有 $(3+2+1)\times10^3\times10^3=6\times10^6$ 个。

现在我们能根据一次函数表达式，找出两两不同种直线交点，然后判断交点是否在棋盘内。如果有三条直线相交于一点，会导致一个交点被判 $3$ 次，四条直线相交于一点，其交点被判 $6$ 次。

我们用 map 存一下不同交点被判次数，然后减去对应的多算贡献，最后得到皇后总覆盖位置数，用棋盘大小减去其即可。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int n,m;
set<int>h,w;
set<pair<int,int>>f,g;
map<pair<int,int>,int>ch;
long long num;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		h.insert(x);
		w.insert(y);
		f.insert({1,y-x});
		g.insert({-1,y+x});
	}
	num+=h.size()*n;
	num+=w.size()*n;
	for(auto u:h)
	for(auto v:w)
		ch[{u,v}]+=1;
	for(auto t:f){
		num+=n-abs(t.second);
		for(auto u:h){
			int x=u,y=t.first*u+t.second;
			if(1<=x&&x<=n&&1<=y&&y<=n)
				ch[{x,y}]++;
		}
		for(auto u:w){
			int x=(u-t.second)/t.first,y=u;
			if(1<=x&&x<=n&&1<=y&&y<=n)
				ch[{x,y}]++;
		}
	}
	for(auto t:g){
		num+=n-abs(t.second-n-1);
		for(auto u:h){
			int x=u,y=t.first*u+t.second;
			if(1<=x&&x<=n&&1<=y&&y<=n)
				ch[{x,y}]++;
		}
		for(auto u:w){
			int x=(u-t.second)/t.first,y=u;
			if(1<=x&&x<=n&&1<=y&&y<=n)
				ch[{x,y}]++;
		}
		for(auto u:f)if((t.second-u.second)%2==0){
			int x=(t.second-u.second)/2;
			int y=x+u.second;
			if(1<=x&&x<=n&&1<=y&&y<=n)
				ch[{x,y}]++;
		}
	}
	for(auto t:ch){
		if(t.second==1)num-=1;
		if(t.second==3)num-=2;
		if(t.second==6)num-=3;
	}
	printf("%lld",1ll*n*n-num);
	return 0;
}
```

---

