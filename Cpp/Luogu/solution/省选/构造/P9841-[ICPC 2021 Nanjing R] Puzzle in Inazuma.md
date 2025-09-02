# [ICPC 2021 Nanjing R] Puzzle in Inazuma

## 题目描述

每个旅行者都知道，在稻妻解开谜题后，他们会得到一个宝箱，但很少有人知道这些谜题是由鸣神大社的宫司八重神子设计的，用来测试旅行者是否足够强大以拯救她的朋友雷电将军和稻妻的人民。

在旅行者通过测试后，八重神子必须将谜题重置为初始状态。但这次她遇到了一些麻烦，甚至怀疑其中一些谜题是否已经损坏。

在重置之前，八重神子的谜题可以被视为一个加权无向完全图 $G$。我们也将初始状态表示为另一个加权无向完全图 $H$。$G$ 和 $H$ 都有 $n$ 个顶点，这些顶点从 $1$ 到 $n$ 标记。

为了将图 $G$ 重置为 $H$，八重神子可以执行以下操作任意次：
- 首先选择四个不同的顶点 $a$，$b$，$c$，$d$ 和一个整数 $x$。注意，每次她可以选择不同的 $a$，$b$，$c$，$d$ 和 $x$。
- 令 $(i, j)$ 为顶点 $i$ 和 $j$ 之间的边。将 $(a, b)$，$(a, c)$ 和 $(a, d)$ 的权重增加 $x$，同时将 $(b, c)$，$(b, d)$ 和 $(c, d)$ 的权重减少 $x$。

请帮助八重神子确定她是否可以将图 $G$ 变为图 $H$。如果可以，你还需要告诉她详细的步骤。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
0 1 1
0 0
1
1 0 0
1 1
0
```

### 输出

```
1
2 1 3 4 1
```

## 样例 #2

### 输入

```
4
3 3 3
0 0
0
0 0 0
3 3
3
```

### 输出

```
1
1 2 3 4 -3
```

## 样例 #3

### 输入

```
5
-12 15 -12 1
37 14 7
7 9
-11
12 5 1 13
-1 -4 -7
-5 -9
18
```

### 输出

```
-1
```

# 题解

## 作者：Purslane (赞：0)

# Solution

将两张图边权做个差，转化为将边权清 $0$。

显然有必要条件所有边边权和为 $0$。

先考虑 $n=4$ 的情况。这时候假设四个点作为 $a$ 被选择了 $u_{1,2,3,4}$ 次。

那么边 $(i,j)$ 获得的总代价为：$2u_i + 2u_j - u_1 + u_2 + u_3 + u_4$，设为 $w_{i,j}$。

显然如果  $\{i,j,k,t\}= \{1,2,3,4\}$，则 $w_{i,j} + w_{k,t}=0$。

如果满足这种“对称”结构，考虑解方程。

比如：$u_1 + u_2 - u_3 - u_4=x$，$u_1 + u_3 - u_2 - u_4 = y$，$u_1+u_4 - u_2 - u_3 = z$。

则 $u_2 + u_3 + u_4 = 3 u_1 - x - y - z$，$u_2 = u_1 - \frac{y+z}{2}$，$u_3 = u_1 - \frac{x+z}{2}$，$u_4 = u_1 - \frac{x+y}{2}$。

我们对 $u$ 的限制只有 $u \in \mathbb Z$，所以需要三个数模 $2$ 相同。

这是 $n=4$ 有解的充要条件：三个位置奇偶相同，且不相邻的边边权互为相反数。

------

上面的分析是从点数特例入手，接下来我们从边权特例入手——如果边权 $\in\{0,1\}$，且你的操作是选择一个 $K_4$ 将内部所有边异或 $1$，问能否变为 $0$。

对于 $n\le 5$，可以直接 $O(1)$ 或 $O(2^n)$ 判。

考虑选 $5$ 个点，进行若干次操作，会得到下面的结果（有连边表示异或了一次）

![](https://s21.ax1x.com/2025/02/07/pEmewcR.png)

一共用了 $5$ 次操作。

因此当 $n \ge 6$，我们要删除一对边：

1. 如果他们相邻，找一条与他们都不相邻的边，消除，用 $10$ 次操作。
2. 如果他们不相邻，直接做，用 $5$ 次操作。

这一步一共进行 $10\frac{m}{2} \le 2.5 n^2$ 次。

------

根据上面的讨论，我们可以把图上所有边权都变为偶数。

显然我们可以执行这种操作——选择两条不相邻的边，使得他们同时加减一个数。注意所有操作的本质都是它。

这样可以在 $\dbinom{n}{2} \times 8 \le 4n^2$ 次操作内解决问题。（单次操作需要 $4$ 次基本操作，如果要传递到相邻边上去就要进行 $2$ 轮。但是这已经足够了。）

总次数为 $6.5 n^2$，完全足够。

代码有点长。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
int n,w[MAXN][MAXN],m[MAXN][MAXN];
struct OP {int a,b,c,d,w;};
OP operator +(OP x,int id) {
	if(x.a==-1)	return x.a=id,x;
	if(x.b==-1)	return x.b=id,x;
	if(x.c==-1)	return x.c=id,x;
	if(x.d==-1)	return x.d=id,x;
}
vector<OP> res;
void Del1(int a,int b,int c,int d) {
	int x=-1,y=-1;
	ffor(i,1,n) if(i!=a&&i!=b&&i!=c&&i!=d) {
		if(x==-1) x=i;
		else if(y==-1) y=i;
		else break ;
	}
	res.push_back({a,x,y,c,1}),res.push_back({b,x,y,c,1});
	res.push_back({a,x,y,d,1}),res.push_back({b,x,y,d,1});
	res.push_back({a,b,c,d,1});
	return ;
}
void del1(int a,int b,int c,int d) {
	if(a!=c&&a!=d&&b!=c&&b!=d) return Del1(a,b,c,d),void();
	int x=-1,y=-1;
	ffor(i,1,n) if(i!=a&&i!=b&&i!=c&&i!=d) {
		if(x==-1) x=i;
		else if(y==-1) y=i;
		else break ;
	}
	Del1(a,b,x,y),Del1(c,d,x,y);
	return ;
}
void operate(int a,int b,int c,int d,int w) {
	res.push_back({c,a,b,d,-w/2});
	res.push_back({d,a,b,c,-w/2});
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) ffor(j,i+1,n) cin>>w[i][j];
	ffor(i,1,n) ffor(j,i+1,n) {int nw;cin>>nw,w[i][j]=w[i][j]-nw;}
	ffor(i,1,n) ffor(j,i+1,n) m[i][j]=!(w[i][j]%2==0);
	int sum=0;
	ffor(i,1,n) ffor(j,i+1,n) sum+=w[i][j];
	if(sum) return cout<<-1,0;
	if(n<=4) {
		if(w[1][2]+w[3][4]!=0) return cout<<-1,0;
		if(w[1][3]+w[2][4]!=0) return cout<<-1,0;
		if(w[1][4]+w[2][3]!=0) return cout<<-1,0;
		if(m[1][2]!=m[1][3]||m[1][3]!=m[1][4]) return cout<<-1,0;
		cout<<3<<'\n';
		cout<<2<<' '<<1<<' '<<3<<' '<<4<<' '<<(w[1][3]+w[1][4])/2<<'\n';
		cout<<3<<' '<<1<<' '<<2<<' '<<4<<' '<<(w[1][2]+w[1][4])/2<<'\n';
		cout<<4<<' '<<1<<' '<<2<<' '<<3<<' '<<(w[1][2]+w[1][3])/2<<'\n';
		return 0;
	}
	if(n==5) {
		int flg=-1;
		ffor(i,0,31) {
			int ot=0,psl=0;
			ffor(j,1,5) if(i&(1<<j-1)) ot^=1;
			ffor(j,1,5) ffor(k,j+1,5) {
				int w=(!!(i&(1<<j-1)))^(!!(i&(1<<k-1)))^ot;
				if(m[j][k]!=w) {psl=1;break ;}
			}
			if(psl) continue ;
			flg=i;break ;
		}
		if(flg==-1) return cout<<-1,0;
		ffor(i,1,5) if(flg&(1<<i-1)) {
			int mn=-1;
			ffor(x,1,5) if(x!=i) {mn=x;break ;}
			OP ins={-1,-1,-1,-1,1};
			ins=ins+mn;
			ffor(x,1,5) if(x!=i&&x!=mn) ins=ins+x;
			res.push_back(ins);
		}
	}
	else {
		vector<pair<int,int>> sg;
		ffor(i,1,n) ffor(j,i+1,n) if(m[i][j]) sg.push_back({i,j});
		ffor(i,0,(int)sg.size()/2-1) del1(sg[2*i].first,sg[i*2].second,sg[2*i+1].first,sg[2*i+1].second);
	}
	for(auto op:res) {
		int a=op.a,b=op.b,c=op.c,d=op.d;
		vector<int> pos;
		pos.push_back(a),pos.push_back(b),pos.push_back(c),pos.push_back(d);
		for(auto i:pos) for(auto j:pos) if(i<j) {
			if(i==a||j==a) w[i][j]++;
			else w[i][j]--;	
		}
	}
	ffor(i,1,n) ffor(j,i+1,n) if(i!=1||j!=2) {
		if(i!=1&&j!=1&&i!=2&&j!=2) operate(i,j,1,2,-w[i][j]);	
		else {
			int x=-1,y=-1;
			ffor(k,3,n) if(k!=i&&k!=j) {
				if(x==-1) x=k;
				else if(y==-1) y=k;
				else break; 
			}
			operate(i,j,x,y,-w[i][j]);
			operate(x,y,1,2,-w[i][j]);
		}
	}
	cout<<res.size()<<'\n';
	for(auto op:res) cout<<op.a<<' '<<op.b<<' '<<op.c<<' '<<op.d<<' '<<op.w<<'\n';
	return 0;
}
```

---

## 作者：NianFeng (赞：0)

感觉挺有分析难度的，在草稿本上推构造推了七八页的样子。

# 0x01 题目分析

## 题意

给了你俩完全图，用不超过 $10^5$ 次以下操作使第一张图变成第二张图：

> 选择互不相同的点 $a,b,c,d$ 和一个数 $x$，$(a,b),(a,c),(a,d)$ 加上 $x$，$(b,c),(c,d),(b,d)$ 减去 $x$。

或者判断无解。

## 思路

首先，把一张图变成另一张图是很不显然的。直接构造一个图为第二张图减去第一张图，这样问题就变成如何操作出目标图。其次，题目的操作看起来相当复杂，说人话就是把一个鸡爪加上 $x$，剩下的三角形减去 $x$。用红边表示减去，白边表示加上，一次操作效果如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2w7ftrtc.png)

容易发现，每做一次操作总和是不变的，那么一种无解情况就很好判断。求出新图边权和，非零则一定不能成功操作。

显然，下一步就是对操作进行转化了。这个“鸡爪式转化”一次关联了 $6$ 条边，相当难受，不过注意到它并不是对称的，那么就可以简单地取两次分别为 $a,b,c,d,x$ 和 $c,a,b,d,x$，如下图，这样就可以把 $6$ 条边换成 $2$ 条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/yhn645ar.png)

很有道理对吧？~~实际上一点用都没有。~~

会发现这种构造限制很大：第一，它让增加的权值必须为偶数；第二，还要求两个边不相邻，至少这两点就很不好处理。由此观之，我们需要构造的新操作除了减边之外，还要保证相对自由，可拓展性好。

四个点肯定玩不出花来了，考虑多加一个点如何。经过漫长手模（也可以 $O(2^{10})$ 枚举？），我们可以得到这么一个东西：对于点 $a,b,c,d,e,x$，进行 $4$ 次操作 $\{d,a,b,e,-x\}$，$\{d,a,b,c,x\}$，$\{e,a,c,d,x\}$，$\{e,a,b,c,-x\}$，那么结果是从 $a$ 出发连了 $4$ 条正负交错的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/oapxjewt.png)

$4$ 条边，看起来是非常不优的，但是这个东西满足两条好的性质：所有边连在一个点上，以及边权可以随意取。为什么这么说呢？我们考虑另一个点 $f$，在上图的基础上用同样的操作处理 $a,b,c,d,f,-x$，结果如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zzakw0rc.png)

这样一来我们就可以把 $(a,e)$ 上的边权转到 $(a,f)$ 上了。

不过这还有个问题，一次这种操作需要 $5$ 个点，转移一条边则需要 $6$ 个点，怎么办呢？很简单，分类讨论。

# 0x02 分类讨论

## Part1: $n=4$

发现上述构造在这里一点用都没有。难不成要用上那个限制很大玩意儿？当然不是。注意到 ~~（注意力惊人）~~ 这种条件下本质不同的操作一共 $4$ 个，边数也只有区区 $6$ 条，那么以四个操作的 $x$ 为未知数，对每一条边建立方程，高斯消元即可。

```cpp
bool GJ(){  //高消板子
    for(int i=1;i<=4;i++){
        int tmp=i;
        for(int j=i;j<=6;j++)
            if(b[j][i]){
                tmp=j;
                break;
            }
        if(tmp!=i)
            swap(b[tmp],b[i]);
        if(!b[i][i]) continue;
        for(int k=1;k<=6;k++){
            if(k==i) continue;
            for(int j=5;j>=i;j--)
                b[k][j]-=b[k][i]*b[i][j]/b[i][i];
        }
    }
    if(b[5][5]||b[6][5])
        return false;
    for(int i=1;i<=4;i++)
        if(!b[i][i]&&b[i][5])
            return false;
        else if(b[i][i])
            b[i][5]/=b[i][i];
    return true;
}

//构造方程系数
b[1][1]=b[1][2]=1,b[1][3]=b[1][4]=-1,b[1][5]=a[1][2];
b[2][1]=b[2][3]=1,b[2][2]=b[2][4]=-1,b[2][5]=a[1][3];
b[3][1]=b[3][4]=1,b[3][2]=b[3][3]=-1,b[3][5]=a[1][4];
b[4][2]=b[4][3]=1,b[4][1]=b[4][4]=-1,b[4][5]=a[2][3];
b[5][2]=b[5][4]=1,b[5][1]=b[5][3]=-1,b[5][5]=a[2][4];
b[6][3]=b[6][4]=1,b[6][1]=b[6][2]=-1,b[6][5]=a[3][4];
//判无解，否则直接输出
if(!GJ()) return print("-1\n"),0;
print("4\n");
print("1 2 3 4 ",b[1][5],'\n');
print("2 1 3 4 ",b[2][5],'\n');
print("3 1 2 4 ",b[3][5],'\n');
print("4 1 2 3 ",b[4][5],'\n');
```

## Part2: $n\ge6$

$n=5$ 还是有点恶心，放下一个说。事实上，有了之前 $6$ 个点就能完成的转移，$n\ge6$ 的情况就很好处理。我们直接枚举每一条边，把它的权值变成 $0$，多出来的权值往下一个放（或者不处理）。这个有点类似均分纸牌？不难证明在和为 $0$ 的情况下一定有解。细节方面，注意一下把边对称复制一遍应该就没了。

```cpp
struct Answer{  //方便处理
    int a,b,c,d,x;
    void out(){
        print(a,' ',b,' ',c,' ',d,' ',x,'\n');
    }
};
vector<Answer>ans;
tp3 mex(int i,int j,int k){
    //暴力找辅助点，不缺这点时间
    //思路中的a,b,c,d,e,f对应i,x,y,z,j,k（好像是的
    int x=1,y=1,z=1;
    while(x==i||x==j||x==k) x++;
    while(y==i||y==j||y==k||y==x) y++;
    while(z==i||z==j||z==k||z==x||z==y) z++;
    return make_tuple(x,y,z);
}

//原图对称处理一下
for(int i=2;i<=n;i++)
    for(int j=1;j<i;j++)
        a[i][j]=a[j][i];
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(i==j||!a[i][j])
            continue;
        int k=j+1==i?i+1:j+1;   //找下一条转出边
        if(k>n) continue;       //找不到没关系，最后统一会在n点处理
        auto [x,y,z]=mex(i,j,k);
        ans.push_back({x,i,y,j,-a[i][j]});
        ans.push_back({j,i,z,x,a[i][j]});
        ans.push_back({j,i,y,z,-a[i][j]});
        ans.push_back({x,i,y,k,a[i][j]});
        ans.push_back({k,i,z,x,-a[i][j]});
        ans.push_back({k,i,y,z,a[i][j]});
        //上面讲的构造正好有两个抵消，就没写了
        a[i][k]+=a[i][j];       //更新边权
        a[k][i]+=a[i][j];
        a[i][j]=a[j][i]=0;
    }
}
print(ans.size(),'\n');
for(auto it : ans)
    it.out();
```

## Part3: $n=5$

~~你不等于四比较松弛，但是不大于六又弥补了这一点。~~

发现直接转移变难了，考虑对原有构造做一定改变。把 $6$ 个点缩成 $5$ 个点依旧可以转移边权，不难构造出这种状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/tes75in0.png)

虽然也只能处理偶数，但总比最开始那个还限定不共点的要方便实现。那么要考虑的就是奇数边权了。在上面的讨论中，我们发现由于改变的边存在重合，构造出来的方案总是带个偶数。那么不妨让这些边不重合，返璞归真，想想最初的构造能带来什么。假定 $x$ 为一个奇数，平凡的，令其为 $1$，不难观察到一次操作可以把选到的 $6$ 条边奇偶性全部改变。因为现在只关心奇偶性而不关心具体边权，本质不同的操作次数降到了 $\binom n4=5$ 种。这还要构造吗？显然，上个爆搜，同时维护奇边数量，就~~不~~轻松地解决了。

```cpp
int nod[6][5]={
    {0,0,0,0,0},
    {0,2,3,4,5},
    {0,1,3,4,5},
    {0,1,2,4,5},
    {0,1,2,3,5},
    {0,1,2,3,4}
};  //预处理一下辅助点
#define t(_) nod[tmp][_]
void dfs(int tmp){
    if(!tot){   //没有奇边了
        for(int i=1;i<=5;i++){
            if(!use[i]) continue;
            ans.push_back({
                nod[i][1],
                nod[i][2],
                nod[i][3],
                nod[i][4],
            1});
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||!a[i][j])
                    continue;
                int k=j+1==i?i+1:j+1;
                if(k>n) continue;
                auto [x,y,z]=mex(i,j,k);
                //按照上面的构造就行，注意权值减半
                //（其实z在这里是没用的
                ans.push_back({x,i,y,j,-a[i][j]/2});
                ans.push_back({x,i,y,k,a[i][j]/2});
                ans.push_back({j,i,k,x,a[i][j]/2});
                ans.push_back({j,i,y,k,-a[i][j]/2});
                ans.push_back({y,i,x,j,-a[i][j]/2});
                ans.push_back({y,i,x,k,a[i][j]/2});
                ans.push_back({j,i,k,y,a[i][j]/2});
                ans.push_back({j,i,x,k,-a[i][j]/2});
                a[i][k]+=a[i][j];
                a[k][i]+=a[i][j];
                a[i][j]=a[j][i]=0;
            }
        }
        print(ans.size(),'\n');
        for(auto it : ans)
            it.out();
        exit(0);
    }
    if(tmp>5) return;
    dfs(tmp+1);     //不选
    use[tmp]=true;  //选，然后修改边权，（注意++和--的顺序
    for(int i=2;i<=4;i++){
        a[t(1)][t(i)]--;
        a[t(i)][t(1)]--;
        tot+=a[t(1)][t(i)]&1?1:-1;
    }
    for(int i=2;i<4;i++){
        for(int j=i+1;j<=4;j++){
            a[t(i)][t(j)]++;
            a[t(j)][t(i)]++;
            tot+=a[t(i)][t(j)]&1?1:-1;
        }
    }
    dfs(tmp+1);
    use[tmp]=false;
    for(int i=2;i<=4;i++){
        a[t(1)][t(i)]++;
        a[t(i)][t(1)]++;
        tot+=a[t(1)][t(i)]&1?1:-1;
    }
    for(int i=2;i<4;i++){
        for(int j=i+1;j<=4;j++){
            a[t(i)][t(j)]--;
            a[t(j)][t(i)]--;
            tot+=a[t(i)][t(j)]&1?1:-1;
        }
    }
}

//由于涉及边权转移，也要对称处理
for(int i=2;i<=n;i++)
    for(int j=1;j<i;j++){
        a[i][j]=a[j][i];
        tot+=a[i][j]&1;     //记录奇边数
    }
dfs(1),print("-1\n");
```

# 0x03 总代码

~~由于更新的码风有点抽象，快读部分就不放了 qwq。~~

```cpp
#include <cstdio>
#include <string>
#include <vector>
#include <tuple>
#define tp3 tuple<int,int,int>
using namespace std;
const int N=105;
int n,a[N][N];
int b[10][10];
int sum,tot;
bool use[6];
int nod[6][5]={
    {0,0,0,0,0},
    {0,2,3,4,5},
    {0,1,3,4,5},
    {0,1,2,4,5},
    {0,1,2,3,5},
    {0,1,2,3,4}
};
struct Answer{
    int a,b,c,d,x;
    void out(){
        print(a,' ',b,' ',c,' ',d,' ',x,'\n');
    }
};
vector<Answer>ans;
bool GJ(){
    for(int i=1;i<=4;i++){
        int tmp=i;
        for(int j=i;j<=6;j++)
            if(b[j][i]){
                tmp=j;
                break;
            }
        if(tmp!=i)
            swap(b[tmp],b[i]);
        if(!b[i][i]) continue;
        for(int k=1;k<=6;k++){
            if(k==i) continue;
            for(int j=5;j>=i;j--)
                b[k][j]-=b[k][i]*b[i][j]/b[i][i];
        }
    }
    if(b[5][5]||b[6][5])
        return false;
    for(int i=1;i<=4;i++)
        if(!b[i][i]&&b[i][5])
            return false;
        else if(b[i][i])
            b[i][5]/=b[i][i];
    return true;
}
tp3 mex(int i,int j,int k){
    int x=1,y=1,z=1;
    while(x==i||x==j||x==k) x++;
    while(y==i||y==j||y==k||y==x) y++;
    while(z==i||z==j||z==k||z==x||z==y) z++;
    return make_tuple(x,y,z);
}
#define t(_) nod[tmp][_]
void dfs(int tmp){
    if(!tot){
        for(int i=1;i<=5;i++){
            if(!use[i]) continue;
            ans.push_back({
                nod[i][1],
                nod[i][2],
                nod[i][3],
                nod[i][4],
            1});
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||!a[i][j])
                    continue;
                int k=j+1==i?i+1:j+1;
                if(k>n) continue;
                auto [x,y,z]=mex(i,j,k);
                ans.push_back({x,i,y,j,-a[i][j]/2});
                ans.push_back({x,i,y,k,a[i][j]/2});
                ans.push_back({j,i,k,x,a[i][j]/2});
                ans.push_back({j,i,y,k,-a[i][j]/2});
                ans.push_back({y,i,x,j,-a[i][j]/2});
                ans.push_back({y,i,x,k,a[i][j]/2});
                ans.push_back({j,i,k,y,a[i][j]/2});
                ans.push_back({j,i,x,k,-a[i][j]/2});
                a[i][k]+=a[i][j];
                a[k][i]+=a[i][j];
                a[i][j]=a[j][i]=0;
            }
        }
        print(ans.size(),'\n');
        for(auto it : ans)
            it.out();
        exit(0);
    }
    if(tmp>5) return;
    dfs(tmp+1);
    use[tmp]=true;
    for(int i=2;i<=4;i++){
        a[t(1)][t(i)]--;
        a[t(i)][t(1)]--;
        tot+=a[t(1)][t(i)]&1?1:-1;
    }
    for(int i=2;i<4;i++){
        for(int j=i+1;j<=4;j++){
            a[t(i)][t(j)]++;
            a[t(j)][t(i)]++;
            tot+=a[t(i)][t(j)]&1?1:-1;
        }
    }
    dfs(tmp+1);
    use[tmp]=false;
    for(int i=2;i<=4;i++){
        a[t(1)][t(i)]++;
        a[t(i)][t(1)]++;
        tot+=a[t(1)][t(i)]&1?1:-1;
    }
    for(int i=2;i<4;i++){
        for(int j=i+1;j<=4;j++){
            a[t(i)][t(j)]--;
            a[t(j)][t(i)]--;
            tot+=a[t(i)][t(j)]&1?1:-1;
        }
    }
}
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            read(a[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int x; read(x);
            a[i][j]=x-a[i][j];
            sum+=a[i][j];
        }
    }
    if(sum)
        return print("-1\n"),0;
    if(n==4){
        b[1][1]=b[1][2]=1,b[1][3]=b[1][4]=-1,b[1][5]=a[1][2];
        b[2][1]=b[2][3]=1,b[2][2]=b[2][4]=-1,b[2][5]=a[1][3];
        b[3][1]=b[3][4]=1,b[3][2]=b[3][3]=-1,b[3][5]=a[1][4];
        b[4][2]=b[4][3]=1,b[4][1]=b[4][4]=-1,b[4][5]=a[2][3];
        b[5][2]=b[5][4]=1,b[5][1]=b[5][3]=-1,b[5][5]=a[2][4];
        b[6][3]=b[6][4]=1,b[6][1]=b[6][2]=-1,b[6][5]=a[3][4];
        if(!GJ()) return print("-1\n"),0;
        print("4\n");
        print("1 2 3 4 ",b[1][5],'\n');
        print("2 1 3 4 ",b[2][5],'\n');
        print("3 1 2 4 ",b[3][5],'\n');
        print("4 1 2 3 ",b[4][5],'\n');
    } else if(n==5){
        for(int i=2;i<=n;i++)
            for(int j=1;j<i;j++){
                a[i][j]=a[j][i];
                tot+=a[i][j]&1;
            }
        dfs(1),print("-1\n");
    } else{
        for(int i=2;i<=n;i++)
            for(int j=1;j<i;j++)
                a[i][j]=a[j][i];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||!a[i][j])
                    continue;
                int k=j+1==i?i+1:j+1;
                if(k>n) continue;
                auto [x,y,z]=mex(i,j,k);
                ans.push_back({x,i,y,j,-a[i][j]});
                ans.push_back({j,i,z,x,a[i][j]});
                ans.push_back({j,i,y,z,-a[i][j]});
                ans.push_back({x,i,y,k,a[i][j]});
                ans.push_back({k,i,z,x,-a[i][j]});
                ans.push_back({k,i,y,z,a[i][j]});
                a[i][k]+=a[i][j];
                a[k][i]+=a[i][j];
                a[i][j]=a[j][i]=0;
            }
        }
        print(ans.size(),'\n');
        for(auto it : ans)
            it.out();
    }
    return 0;
}
```

# 0x4f 总结与后话

感觉自己做构造题还是比较菜，需要多练。操作构造题中心思想大部分是将操作重组以达到化简的目的，或者分析结果特殊性质反推过程，挺妙的。

感谢您的观看，有错误/不足之处欢迎指出！(>w<)

---

## 作者：_Flowey_ (赞：0)

### 题意：

给定两个无向的完全图 $G$ 和 $H$，图上的每条边都有边权，用以下操作将 $G$ 变得和 $H$ 完全一致：

- 选择图 $G$ 的四个点 $a,b,c,d$ 和一个整数 $x$，让边 $(a,b)(a,c)(a,d)$ 的权值增加 $x$，边 $(b,c)(c,d)(b,d)$ 的权值减少 $x$。

要求操作次数小于等于 $10^5$。

### 分析：

发现操作后边权和不变，所以两图边权和不同就无解。

如果我们通过选择不同的点和相同的整数进行操作，并 **最终使得某条边增加，另一条边减少**，这道题大概率就做完了，因为这样我们就可以让每条边和对应的边相等。大概 $5000$ 条边，意思是对于每条边我们可以操作 $20$ 次左右，非常宽松。

### 推导：

下面有图（图丑勿喷）。

我们用红色的边表示边权减少，黑色的边表示边权增加，黄色的数字代表需要的操作次数，蓝色的数字代表需要的点数。

首先要确定的是达到目标要用的点数。

从 $4$ 个点开始，我们可以从基本操作中推出两个简单形式。

启示着我们可以用 $5$ 个点推出一个更简单的形式。

接下来我们继续尝试 $4$ 个点和 $5$ 个点的情况，发现还有一种形式比较简洁，剩下的都很乱。

启示着我们可以用 $6$ 个点推出一个更简单的形式。

对于新的操作，考虑和旧的操作搭配食用。

![](https://cdn.luogu.com.cn/upload/image_hosting/8vasuyeu.png)

### 解题：

首先判无解。

对于 $n \ge 6$ 的情况，我们可以通过使用 $6$ 个点和 $10$ 次操作达到目标，在 $20$ 次内，所以一定有解（甚至超额完成，因为这两条边连接在一起，形式简单）。

对于 $n=5$ 的情况，我们可以通过使用 $5$ 个点，$4$ 次操作，将边权差为偶数的边消去，只剩下了奇数的边。重新考虑一下这种特殊局面下的发生的变化：

- 我们只用考虑边的奇偶性（即边权只有 $0$ 和 $1$）。

- 使 $x$ 为奇数，操作将变为 让所选的 $4$ 个点之间的 $6$ 条边进行取反。

所以我们可以 $O(2^{C_{n}^{4}}) $ 的枚举，由于 $ n=5$，我们只枚举 $2^5$ 次。

对于 $n=4$ 的情况，解方程即可。

---

## 作者：Vct14 (赞：0)

以下内容摘自官方题解，只有一些很小的修改。

------------

通过对两个图的每一条对应的边的权值做差，可以把题意转换为给定一个图 $G$，询问是否可以通过有限次操作把所有边权都变成 $0$。

我们先来讨论 $n\geqslant6$ 时的情况。

首先不难发现，每次操作后总和必须一样。接下来我们说明只要总和一样的时候，图 $G$ 一定可以变成图 $H$。

我们假设图中存在 $6$ 个点 $A,B,C,D,E,F$，并进行如下一系列操作：

- 将 $DA,DB,DE$ 边上的值 $-1$，将 $AB,BE,EA$ 边上的值 $+1$。
- 将 $DA,DB,DC$ 边上的值 $+1$，将 $AB,BC,CA$ 边上的值 $-1$。
- 将 $EA,EC,ED$ 边上的值 $+1$，将 $AC,CD,DA$ 边上的值 $-1$。
- 将 $EA,EB,EC$ 边上的值 $-1$，将 $AB,BC,CA$ 边上的值 $+1$。

经过以上操作后，我们将 $AB,BE$ 边上的值增大了 $1$，将 $AC,AD$ 边上的值减小了 $1$。

类似地，我们可以将 $AB,BE$ 边上的值减小 $1$，将 $AC,AF$ 边上的值增大 $1$。

从而我们可以通过有限次操作将 $AD$ 边上的值减小了 $1$，并将 $AF$ 边上的值增大了 $1$。

因此 $n\geqslant6$ 的时候只要总和一样，则一定可以在有限步之内将图 $G$ 变成图 $H$。

接下来讨论 $n=5$ 时的情况。

通过 $4$ 次操作，我们可以将 $AB,AE$ 边上的值增大 $1$，将 $AC,AD$ 边上的值减小 $1$。

类似地，我们可以将 $AB,AC$ 边上的值增大 $1$，将 $AD,AE$ 边上的值减小 $1$。

从而我们可以通过有限次操作将 $AD$ 边上的值减小 $2$，并将 $AB$ 边上的值增大 $2$。

因此我们只需考虑奇偶性，可以通过 $O(2^\binom{n}{2}$) 的复杂度完成。（其实可以优化成 $O(2^n)$。）

最后讨论 $n=4$ 时的情况，相当于 $4$ 个未知数，$6$ 个方程，直接找有没有解即可。

---

