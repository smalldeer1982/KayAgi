# Mike and Frog

## 题目描述

迈克有一只青蛙和一朵花，它的青蛙叫Xaniar，花叫Abol。

开始（时间为0），它的青蛙高度为
$ h_{1}$,花高度为$ h_{2}$。每一秒，迈克都会给他们两个浇水，因此每过一秒青蛙的高度都会由当前的$ h_{1}$变为$(x_{1}\times h_{1}+ y_{1}) mod\ m$,同理，花的高度都会由当前的$ h_{2}$变为$(x_{2}\times h_{2}+ y_{2}) mod\ m$。

已知$x_{1},y_{1},x_{2},y_{2}$都是整数，并且$a\ mod\ b$表示$a$除以$b$所得的余数。

迈克想知道最少多久后青蛙的高度会变成$a_{1}$ 花的高度会变成$a_{2}$。请你计算出最短时间或者告诉迈克这件事根本不会发生。

## 样例 #1

### 输入

```
5
4 2
1 1
0 1
2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1023
1 2
1 0
1 2
1 1
```

### 输出

```
-1
```

# 题解

## 作者：hgzxwzf (赞：2)

## [CF547A](https://codeforces.com/problemset/problem/547/A)

一直浇下去青蛙和花的肯定会出现进入了循环节的情况，假设两者都进入循环节的时间是 $fi$。

$fi$ 之前的某一时间满足 $h_1=a_1,h_2=a_2$ 的情况很好处理，考虑循环节中的情况。

假设青蛙的循环节长度为 $l_1$，$h_1=a_1$ 的情况出现在循环节的 $p_1$ 位置，$l_2,p_2$ 表示花（$p_1,p_2$ 从 $0$ 开始编号，循环节的起点为 $fi$ 时 $h_1,h_2$ 的值）。

那么我们就要找到 $x$ 满足 $x\bmod l_1=p_1,x\bmod l_2=p_2$。

我们枚举 $x$ 满足 $x\bmod l_1=p_1$，再判断 $x\bmod l_2=p_2$ 是否成立。

发现 $x\bmod l_2$ 的值也会进入循环节，所以不同的 $x\bmod l_2$ 的不同值最多有 $l_2$ 个，而 $l_2\le m$，所以我们可以用 $\verb!STL::map!$ 存储有哪些 $x\bmod l_2$ 已经出现过，如果当前的 $x\bmod l_2$ 已经出现过，那么肯定无解，所以有解一定会在 $m$ 次之内找到，时间复杂度 $O(m\log_2m)$。

一些实现的细节请看代码。

```cpp
#include<cstdio>
#include<set>
#include<algorithm>
#include<vector>
#include<stack>
#include<cmath>
#include<vector>
#include<cstring>
#include<queue>
#include<string>
#include<iostream>
#include<map>
#include<bitset>
#include<ctime>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
#define LL long long
#define pi pair<int,int>
#define mk make_pair
#define fi first
#define se second

using namespace std;
const int N=1e6+10;

int h[3],a[3],x[3],y[3],mod,vis[3][N];
int pos[3],l[3];
set<LL>se;

int main()
{
	int fi;
	scanf("%d",&mod);
	rep(i,1,2) scanf("%d%d%d%d",&h[i],&a[i],&x[i],&y[i]);
	if(h[1]==a[1]&&h[2]==a[2]) return printf("%d",0),0;
	rep(j,1,2) vis[j][h[j]]=1;
	rep(i,1,mod)
	{
		rep(j,1,2) h[j]=(1ll*x[j]*h[j]%mod+y[j])%mod;
		if(h[1]==a[1]&&h[2]==a[2]) return printf("%d",i),0;
		rep(j,1,2) if(vis[j][h[j]]&&!vis[j][a[j]]) return puts("-1"),0;
		if(vis[1][h[1]]&&vis[2][h[2]])
		{
			fi=i;
			rep(j,1,2)
			{
				l[j]=0;
				if(h[j]==a[j]) pos[j]=l[j];
				int t=(1ll*x[j]*h[j]%mod+y[j])%mod;
				while(t!=h[j])
				{
					l[j]++;
					if(t==a[j]) pos[j]=l[j];
					t=(1ll*x[j]*t%mod+y[j])%mod;
				}
			}
			break;
		}
		rep(j,1,2) vis[j][h[j]]=1;
	}
	l[1]++,l[2]++;
	for(LL i=pos[1];i;i+=l[1])
	{
		if(se.find(i%l[2])!=se.end()) return puts("-1");
		se.insert(i%l[2]);
		if(i%l[2]==pos[2]) 
			return printf("%lld",i+fi),0;
	}
	puts("-1");
	return 0;
}
```


---

## 作者：叶ID (赞：1)

题目链接：[CF547A Mike and Frog](https://www.luogu.org/problemnew/solution/CF547A)

### 题目大意

你有两个数 $H_1$、$H_2$。每次操作，你可以将 $H_1$ 变成 $(H_1 \cdot x_1 + y_1)\ mod\ M$，$H_2$ 变成 $(H_2 \cdot x_2 + y_2)\ mod\ M$ （两个变换会在一次操作时同时进行）。

问，你至少需要进行多少次操作，才能使得 $H_1 = A_1$ 和 $H_2 = A_2$ 同时满足。

数据范围：$H_1,x_1,y_1 <M$ ，$H_2,x_2,y_2 < M$ ，$2 \leq M \leq 10^6$

### 解题思路

注意到本题 $M$ 只有 $10^6$，我么可以对于 $H_1$ 和 $H_2$ 分别暴力模拟。

对于一个数 $a$，如果不断进行操作，其变化规律应当如下：

a → b → (c → d → e → f) → (c → d → e → f) → ...

感性理解一下，我们发现这个数进行一定次数操作后一定会进入一个循环。

我们称这个数达到第一个 $c$ （如上面的描述）之后就算进入了循环，到达第二个 $c$ 时算“发生循环”。那么，一个数的变化规律可以这么描述：

- 对于任意一个数，其变换 $0$ 次或若干次就会进入一个长度大于 $0$ （废话），且小于等于 $M$ 的循环。

比如，上面的描述中，$a$ 在变换两次后就进入了一个长度为 $4$ 的循环。

我们用 $a^k$ 表示数 $a$ 操作 $k$ 次后的结果，用 $rd_a$ 表示 $a$ 进入循环前的变换次数，用 $r_a$ 表示 $a$ 进入的循环的长度。

对于 $H_1$，我们先暴力求出一个最小的 $cnt_{H_1}$（其实这样表示不准确，但是为了和$rd$、$r$的表达方式对等所以这么写），使得 $H_1^{cnt_{H_1}} = A_1$。我们还可以暴力求出 $rd_{H_1}$ 和 $r_{H_1}$。

然后我们很容易知道 $H_1^x = A_1$ 的条件。

- 如果 $cnt_{H_1} < rd_{H_1}$，则当且仅当正整数 $k$ 满足 $k = cnt_{H_1}$ 时，有 $H_1^k = A_1$
- 否则，当且仅当正整数 $k$ 同时满足以下条件时，有 $H_1^k = A_1$
  - $k \geq rd_{H_1}$ （显然）
  - $(k - rd_{H_1})\ mod\ r_{H_1} = (cnt_{H_1} - rd_{H_1})$ （即，经过若干次循环以后会回到我们需要的位置）

然后我们对于 $H_2$ 也这样计算。随后我们分类讨论如何求得答案$ans$。

- 如果两个数的 $cnt$ 均小于 $rd$，那么，$ans$ 必须满足 $ans = cnt_{H_1}$ 和 $ans = cnt_{H_2}$。那么，当且仅当 $cnt_{H_1} = cnt_{H_2}$ 时有解，解是 $cnt_{H_1}$。
- 如果只有一个数的 $cnt$ 小于 $rd$，不妨令 $cnt_{H_1} < rd_{H_1}$。那么，必定有 $ans = cnt_{H_1}$。那么，当且仅当 $cnt_{H_1} \geq rd_{H_2}$ 且 $(cnt_{H_1} - rd_{H_2})\ mod\ r_{H_2} = (cnt_{H_2} - rd_{H_2})$ 时有解，解是 $cnt_{H_1}$。
- 如果没有一个数的 $cnt$ 小于 $rd$，那么，$ans$ 必须满足：
  - $ans \geq rd_{H_1}$ $\texttt{\color{grey}condition 1}$
  - $ans \geq rd_{H_2}$ $\texttt{\color{grey}condition 2}$
  - $(ans - rd_{H_1})\ mod\ r_{H_1} = (cnt_{H_1} - rd_{H_1})$ $\texttt{\color{grey}condition 3}$
  - $(ans - rd_{H_2})\ mod\ r_{H_2} = (cnt_{H_2} - rd_{H_2})$ $\texttt{\color{grey}condition 4}$

那么对于第三种情况，我们定义变量 $p$，并赋值为满足条件1和3的最小值。很显然，此时 $p = cnt_{H_1}$。

随后，我们不停地将 $p$ 的值增加 $r_{H_1}$ （可知这样不会破坏条件1和3），直到其满足条件2。由于 $rd_{H_2}$ 最大只能为 $M-1$，所以不会超时。此时的 $p$ 已经同时满足条件1，2和3。

最后我们再将 $p$ 的值不停增加 $r_{H_1}$ （可知这样不会破坏条件1，2，3），直到 $p$ 满足条件4（此时答案为 $p$），或者已经增加了超过 $M$ 次（此时无解）。

综合所有情况，就是正解了。

### 代码

注意千万不要把 `y1` 定义成全局变量！如果评测机编译器版本较老，这会和 `math.h` 冲突，造成错误。

```cpp
// status: [Accepted]
// oj:     [%uContest]

#include<bits/stdc++.h>
using namespace std;

// 不开 long long 见祖宗
typedef long long ll;
#define int ll

// 题目中的 M
int mod1;

// 让 h 每次以 h = (h * x + y) % mod1 的形式变换，返回变换到 a 所需的最少步骤数。
// 如果无法变换到 a，返回-1
// * flag: 是否允许在 h==a 时返回0
int findNext(int h,int a,int x,int y,bool flag = false) {
    int cnt = 0;
    if(flag && h==a) return 0;
    do {
        cnt++;
        h = (h * x + y) % mod1;
        // 如果变换超过 M 次还没有找到答案，那么此时肯定已经“发生循环”，不可能还会找到答案。
        if(cnt > mod1) {
            return -1;
        }
    } while(h != a);
    return cnt;
}

int st[1000000];
int st_t = 0;
// 让 h 每次以 h = (h * x + y) % mod1 的形式变换，返回 h 初次“进入循环”时变成的数。
int findCyclicNode(int h,int x,int y) {
    // 可以直接用数组统计是否出现。此处使用一个计数量(st_t)，可以避免清空数组的麻烦
    ++st_t;
    // 此处要先记录访问 h 一次，否则如果 h 本身就在循环内，会出现问题。
    st[h] = st_t;
    // 由于一个数不断变换必定会出现循环，因此while(1)即可。
    while(1) {
        h = (h * x + y) % mod1;
        // 第一个出现超过 1 次的值，一定是初次“进入循环”时的值
        if(st[h] == st_t) return h;
        st[h] = st_t;
    }
}

// 除法上取整（避免double精度问题）
// * 这份代码中没有用到此函数
int divCeil(int x,int y) {
    return x/y + int(bool(x%y));
}

signed main() {
#ifdef OFFLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
#endif

    // 不要将 y1 作为全局变量，否则要换个名字。
    int h1,a1,x1,y1;
    int h2,a2,x2,y2;

    ios::sync_with_stdio(false);
    cin>>mod1>>h1>>a1>>x1>>y1>>h2>>a2>>x2>>y2;

    // 求cnt_{H_1}
    int cnt1 = findNext(h1,a1,x1,y1);
    int cnt2 = findNext(h2,a2,x2,y2);

    // H_1 和 H_2 有一个无法到达 A_1 或 A_2。无解。
    if(cnt1 == -1 || cnt2 == -1) {
        cout<<-1<<endl;
        exit(0);
    }

    // 先寻找初次进入循环时到达的数字
    int p1 = findCyclicNode(h1,x1,y1);
    int p2 = findCyclicNode(h2,x2,y2);

    // 再求循环长度
    int r1 = findNext(p1,p1,x1,y1);
    int r2 = findNext(p2,p2,x2,y2);

    // 然后求初次进入循环之前的步骤数
    int rd1 = findNext(h1,p1,x1,y1,true);
    int rd2 = findNext(h2,p2,x2,y2,true);

    // cnt - rd 在解法中被频繁使用，创建变量以图方便。
    int d1 = cnt1 - rd1;
    int d2 = cnt2 - rd2;

    // 调试信息（在一般的平台下，使用cerr输出调试信息可避免一部分的“不删调试见祖宗”）
    cerr<<"1: "<<r1<<' '<<rd1<<' '<<d1<<endl;
    cerr<<"2: "<<r2<<' '<<rd2<<' '<<d2<<endl;

    // 如果两个数都有 cnt < rd （即 cnt - rd < 0）
    if(d1 < 0 && d2 < 0) {
        if(cnt1 == cnt2) {
            cout<<cnt1<<endl;
        }
        else {
            cout<<-1<<endl;
        }
        exit(0);
    }
    // 如果只有一个数
    else if(d1 < 0) {
        if(cnt1 - rd2 >= 0 && (cnt1 - rd2) % r2 == d2) {
            cout<<cnt1<<endl;
        }
        else {
            cout<<-1<<endl;
        }
        exit(0);
    } else if(d2 < 0) {
        if(cnt2 - rd1 >= 0 && (cnt2 - rd1) % r1 == d1) {
            cout<<cnt2<<endl;
        }
        else {
            cout<<-1<<endl;
        }
        exit(0);
    }

    // 如果没有数满足 cnt < rd
    // 先使p满足条件1和3
    int p = rd1 + d1;
    // 然后满足2
    while(p < rd2) p += r1;
    // 最后满足4
    for(int i=1;i<=r2+1;i++,p+=r1) {
        if((p-rd2) % r2 == d2) {
            cout<<p<<endl;
            exit(0);
        }
    }

    // 无解
    cout<<-1<<endl;
}

```

评测记录：[R25577582](https://www.luogu.org/record/25577582)


---

## 作者：_edge_ (赞：0)

exgcd 的解题方式。

首先很容易观察出这个肯定是一条链套上一个环，然后在环内走一走。

我们需要做的，就是把链和环记录下来，这是找循环饥节的部分。

```cpp
	vis1[a1]=++tot1;cnt1[tot1]=a1;
	while (1) {
		a1*=x;a1+=y;a1%=m;
		if (vis1[a1]) {
			L1=vis1[a1];
			break;
		}
		vis1[a1]=++tot1;cnt1[tot1]=a1;
	}
	
	vis2[a2]=++tot2;cnt2[tot2]=a2;
	while (1) {
		a2*=xx;a2+=yy;a2%=m;
		if (vis2[a2]) {
			L2=vis2[a2];
			break;
		}
		vis2[a2]=++tot2;cnt2[tot2]=a2;
	}
	
	if (!vis1[b1] || !vis2[b2]) {cout<<"-1\n";return 0;}
```

和上面代码一样，注意，这里第一次也要记录下来。

然后接下来的，如果目标数在链上面，那就查找一下就可以了。

```cpp
	if (vis1[b1]<L1 || vis2[b2]<L2) {
		if (vis1[b1]<L1) {
			int xx=vis1[b1];
			if (xx<=L2) {
				if (cnt2[xx]==b2) cout<<xx-1<<"\n";
				else cout<<"-1\n";
				return 0;
			}
			xx-=L2;
			xx%=tot2-L2+1;
			xx+=L2;
			if (cnt2[xx]==b2) cout<<vis1[b1]-1<<"\n";
				else cout<<"-1\n";
		}
		else {
			int xx=vis2[b2];
			if (xx<=L1) {
				if (cnt1[xx]==b1) cout<<xx-1<<"\n";
				else cout<<"-1\n";
				return 0;
			}
			xx-=L1;
			xx%=tot1-L1+1;
			xx+=L1;
			if (cnt1[xx]==b1) cout<<vis2[b2]-1<<"\n";
			else cout<<"-1\n";
		}
		return 0;
	}
```

如上查找方式，注意这里可能有环走来走去的情况，所以要取模一下。

还有一种可能的情况就是在两个环上。

这种情况我们先设答案是 $x$。

设环长分别为 $tot1,tot2$。

则需要满足以下两条等式

$(L1+x) \equiv K1 \pmod {tot1}$

$(L2+x) \equiv K2 \pmod {tot2}$

$L1,L2$ 是起始点，$K1,K2$ 是终点。

如果你熟悉 exgcd 就会发现，这个是类似于 exCRT 一样的形式。

于是把他拆一拆 

$L1+x+tot1 \times y1 = K1$

$L2+x+tot2 \times y2 = K1$

然后上下相减就可以得到标准的二元一次方程。

这里的问题可能跟环的相对大小有关，所以如果 $L1>L2$ 那就交换一下，效果一样。

这题目说实在确实很难调，至少对我来说，但还是希望读者能够自行调出这道题目。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=2e6+5;
namespace G{
	int xx,yy,c;
	int exgcd(int x,int y) {
		if (!y) {
			xx=c/x;
			yy=1;
			return x;
		}
		int tmp=exgcd(y,x%y);
		int tt=xx;xx=yy;yy=tt-x/y*yy;
		return tmp;
	}
};
int m,x,y,a1,b1,xx,yy,a2,b2,cnt1[INF],cnt2[INF],vis1[INF],vis2[INF],tot1,tot2,L1,L2;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>m>>a1>>b1>>x>>y>>a2>>b2>>xx>>yy;
	if (a1==b1 || a2==b2) {cout<<"-1\n";return 0;} 
	// a1->(a1*x+y)%m
	// a2->(a2*xx+yy)%m
	vis1[a1]=++tot1;cnt1[tot1]=a1;
	while (1) {
		a1*=x;a1+=y;a1%=m;
		if (vis1[a1]) {
			L1=vis1[a1];
			break;
		}
		vis1[a1]=++tot1;cnt1[tot1]=a1;
	}
	
	vis2[a2]=++tot2;cnt2[tot2]=a2;
	while (1) {
		a2*=xx;a2+=yy;a2%=m;
		if (vis2[a2]) {
			L2=vis2[a2];
			break;
		}
		vis2[a2]=++tot2;cnt2[tot2]=a2;
	}
	
	if (!vis1[b1] || !vis2[b2]) {cout<<"-1\n";return 0;}
	if (vis1[b1]<L1 || vis2[b2]<L2) {
		if (vis1[b1]<L1) {
			int xx=vis1[b1];
			if (xx<=L2) {
				if (cnt2[xx]==b2) cout<<xx-1<<"\n";
				else cout<<"-1\n";
				return 0;
			}
			xx-=L2;
			xx%=tot2-L2+1;
			xx+=L2;
			if (cnt2[xx]==b2) cout<<vis1[b1]-1<<"\n";
				else cout<<"-1\n";
		}
		else {
			int xx=vis2[b2];
			if (xx<=L1) {
				if (cnt1[xx]==b1) cout<<xx-1<<"\n";
				else cout<<"-1\n";
				return 0;
			}
			xx-=L1;
			xx%=tot1-L1+1;
			xx+=L1;
			if (cnt1[xx]==b1) cout<<vis2[b2]-1<<"\n";
			else cout<<"-1\n";
		}
		return 0;
	}
	
	tot1-=L1;tot2-=L2;
	tot1++;tot2++;
	
	int K1=vis1[b1]-L1,K2=vis2[b2]-L2;
	if (L1<L2) {
		int S1=L2,S2=0;S1-=L1;
		G::c=K1-K2-S1+S2;
		int tmp=G::exgcd(tot1,tot2);
		if ((K1-K2-S1+S2)%tmp) {cout<<"-1\n";return 0;}
		int Tx=tot2/tmp;
		G::xx%=Tx;G::xx+=Tx;G::xx%=Tx;
		int X=K1-G::xx*tot1-S1;
		int LC=tot1*(tot2)/tmp;
		cout<<(X%LC+LC)%LC+L2-1<<"\n";
	}
	else {
		swap(L1,L2);swap(K1,K2);swap(tot1,tot2);
		int S1=L2,S2=0;S1-=L1;S1%=tot1;
		G::c=K1-K2-S1+S2;
		int tmp=G::exgcd(tot1,tot2);
		if ((K1-K2-S1+S2)%tmp) {cout<<"-1\n";return 0;}
		int Tx=tot2/tmp;
		G::xx%=Tx;G::xx+=Tx;G::xx%=Tx;
		int X=K1-G::xx*tot1-S1;
		int LC=tot1*(tot2)/tmp;
		cout<<(X%LC+LC)%LC+L2-1<<"\n";
	}
	// (L1+x)%tot1=K1
	// (L2+x)%tot2=K2
	 
	return 0;
}
```


---

## 作者：wtyqwq (赞：0)

题意翻译：有两个数 $h_1$ 和 $h_2$，每一个回合 $h_1$ 会变成 $(h_1 \times x_1+y_1) \bmod m$，$h_2$ 会变成 $(h_2 \times x_2+y_2) \bmod m$。问最早在第几个回合满足 $h_1=a_1$ 且 $h_2=a_2$。

解题思路：模数不大，且 $h_1,h_2$ 只能是 $[0,m-1]$ 之间的数，可以证明一定具有周期性。可以发现每一个变换都是一个 $ρ$ 形的东西，所以我们可以预处理出两个 $ρ$ 形的变换，然后我们根据两个点在不在圈上分情况讨论并分别计算，求答案用扩展欧几里得算法即可  [[P5656]](https://www.luogu.com.cn/problem/P5656)。 

---

