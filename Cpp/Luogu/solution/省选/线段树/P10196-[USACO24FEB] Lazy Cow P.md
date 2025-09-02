# [USACO24FEB] Lazy Cow P

## 题目描述

Bessie 正在努力为美国件算机奥林匹克二月的竞赛准备测试用例。每一分钟，她可以选择不准备测试用例，不花费能量；或者对于某个正整数 $a$，花费 $3^{a−1}$ 能量准备 $a$ 个测试用例。

Farmer John 有 $D$（$1\le D\le 2\cdot 10^5$）个需求。对于第 $i$ 个需求，他告诉 Bessie，在前 $m_i$ 分钟内她总共需要准备至少 $b_i$ 个测试用例（$1\le m_i\le 10^6,1\le b_i\le 10^{12}$）。

令 $e_i$ 为满足前 $i$ 个需求 Bessie 最小需要花费的能量。输出 $e_1,\ldots,e_D$ 模 $10^9+7$ 的余数。 

## 说明/提示

### 样例解释 1

对于第一个测试用例，

- $i=1$：如果 Bessie 在前 $5$ 天分别制作 $[2,3,2,2,2]$ 个测试用例，她将花费 $3^1+3^2+3^1+3^1+3^1=21$ 单位能量，并在第 $5$ 天结束时制作了 $11$ 个测试用例。
- $i=2$：Bessie 可以遵循上面的策略，确保在第 $5$ 天结束时制作了 $11$ 个测试用例，而这将自动满足第二个需求。
- $i=3$：如果 Bessie 在前 $10$ 天分别制作 $[2,3,2,2,2,0,1,1,1,1]$ 个测试用例，她将花费 $25$ 单位能量并满足所有需求。可以证明她无法花费更少的能量。
- $i=4$：如果 Bessie 在前 $10$ 天每一天制作 $3$ 个测试用例，她将花费 $3^2\cdot 10=90$ 单位能量并满足所有需求。

对于每一个 $i$，可以证明 Bessie 无法花费更少的能量满足前 $i$ 个需求。

### 测试点性质

- 测试点 $4-5$：$D\le 100$，且对于所有 $i$，$m_i\le 100$。
- 测试点 $6-8$：$D\le 3000$。
- 测试点 $9-20$：没有额外限制。

## 样例 #1

### 输入

```
4
5 11
6 10
10 15
10 30```

### 输出

```
21
21
25
90```

## 样例 #2

### 输入

```
2
100 5
100 1000000000000```

### 输出

```
5
627323485```

## 样例 #3

### 输入

```
20
303590 482848034083
180190 112716918480
312298 258438719980
671877 605558355401
662137 440411075067
257593 261569032231
766172 268433874550
8114 905639446594
209577 11155741818
227183 874665904430
896141 55422874585
728247 456681845046
193800 632739601224
443005 623200306681
330325 955479269245
377303 177279745225
880246 22559233849
58084 155169139314
813702 758370488574
929760 785245728062```

### 输出

```
108753959
108753959
108753959
148189797
148189797
148189797
148189797
32884410
32884410
32884410
32884410
32884410
32884410
32884410
3883759
3883759
3883759
3883759
3883759
3883759```

# 题解

## 作者：chrhaa (赞：4)

### 数据结构题

考虑到 $b$ 的数据范围极大，先离散化。

因为贡献是 $3^{a-1}$，所以一定测试用例越平均越好（感性理解）。发现约束条件是针对前缀的，那么有一个显然的贪心，即在平均分布的情况下，测试用例多的日子尽量靠前。

定每天准备 $a_i$ 个测试用例，那么有 $a_i \geq a_{i+1}$，画成条状图，就是一个向左上延伸的台阶。对于第 $i$ 个要求，若当前状态尚未满足，则一定要增加 $m_i$ 前的 $a_i$ 值，由于特殊的贡献方式，更新$a_i$值时一定要先增加较小的 $a_i $，形象一点说，就是往这个台阶里倒水。而增加了前面的 $a_i$，后面就可以去掉若干，同理是把台阶从上至下切掉一部分。

区间赋值，区间和查询，最长值相等区间长度，即可用线段树维护，以下是一份丑陋的代码。

```
#include<stdio.h>
const int N=200005;
const int M=4000005;
const int K=1000000;

#define ll long long
const ll P=1000000007;

inline ll Q(ll x,ll y=P-2,ll z=1){
	for(;y;y>>=1,x=x*x%P)
	(y&1)&&(z=z*x%P);return z;
}

bool t[M];
int lb[M],rb[M];
ll lf[M],rf[M];
ll sm[M],lz[M];

#define ls (x<<1)
#define rs (x<<1|1)

inline void tag(int x,int l,int r,ll v){
	sm[x]=(r-l+1)*v;
	lb[x]=rb[x]=r-l+1;
	lf[x]=rf[x]=v;
	lz[x]=v;
}

inline void pushdown(int x,int l,int r){
	if(lz[x]>=0){
		int mid=(l+r)>>1;
		tag(ls,l,mid,lz[x]);
		tag(rs,mid+1,r,lz[x]);
		lz[x]=-1;
	}
}

inline void pushup(int x,int l,int r){
	sm[x]=sm[ls]+sm[rs];
	lf[x]=lf[ls];
	rf[x]=rf[rs];
	lb[x]=(t[ls]&&rf[ls]==lf[rs])?(lb[ls]+lb[rs]):lb[ls];
	rb[x]=(t[rs]&&rf[ls]==lf[rs])?(rb[rs]+rb[ls]):rb[rs];
	t[x]=(lb[x]==r-l+1);
}

void build(int x,int l,int r){
	sm[x]=0;
	lz[x]=-1;
	lb[x]=rb[x]=r-l+1;
	lf[x]=rf[x]=0;
	t[x]=1;
	
	if(l<r){
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
}

void update(int x,int l,int r,int L,int R,ll v){
	if(L>R||r<L||l>R) return ;
	if(L<=l&&r<=R){
		tag(x,l,r,v);
		return ;
	}
	
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	update(ls,l,mid,L,R,v);
	update(rs,mid+1,r,L,R,v);
	pushup(x,l,r);
}

ll query(int x,int l,int r,int L,int R){
	if(L>R||r<L||l>R) return 0;
	if(L<=l&&r<=R) return sm[x];
	
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R); 
}

int queryl(int x,int l,int r,int p){
	if(l==r)
	return 1;
	
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	
	if(p<=mid) return queryl(ls,l,mid,p);
	else{
		int res=queryl(rs,mid+1,r,p);
		
		if(res==p-mid&&rf[ls]==lf[rs])
		return res+rb[ls];
		else return res;
	}
}

int queryr(int x,int l,int r,int p){
	if(l==r)
	return 1;
	
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	
	if(p<=mid){
		int res=queryr(ls,l,mid,p);
		
		if(res==mid-p+1&&rf[ls]==lf[rs])
		return res+lb[rs];
		else return res;
	}else return queryr(rs,mid+1,r,p);
}

int n,m;
ll ans,a,b,c,tmp;

void calc(int x,ll y,ll f)
{(y>0)&&(ans=(ans+P+Q(3,y-1)*f*(ll)x%P)%P);}

signed main(){
	int i,x,p,y;
	scanf("%d",&n);
	build(1,1,K);
	
	for(i=1;i<=n;i++){
		scanf("%d%lld",&m,&b);
		a=query(1,1,K,m,m);
		b-=query(1,1,K,1,m);
		p=m;
		
		if(b<=0)
		goto END;
		
		tmp=b;
		
		while(b>0&&p>0){
			x=queryl(1,1,K,p);
			p-=x;
			x=m-p;
			calc(x,a,-1);
			y=int(b%(ll)x);
			
			if(p>0){
				c=query(1,1,K,p,p);
				
				if((c-a)*(ll)x<b){
					b-=(c-a)*(ll)x;
					calc(x,c,1);
					a=c;
				}else{
					a+=b/(ll)x;
					calc(y,a+1,1);
					update(1,1,K,p+1,p+y,a+1);
					calc(x-y,a,1);
					update(1,1,K,p+y+1,p+x,a);
					b=0;
				}
			}else{
				a+=b/(ll)x;
				calc(y,a+1,1);
				update(1,1,K,1,y,a+1);
				calc(x-y,a,1);
				update(1,1,K,y+1,x,a);
			}
		}
		
		b=tmp;
		p=m+1;
		
		if(p<=K)
		a=query(1,1,K,p,p);
		
		while(b>0&&p<=K){
			x=queryr(1,1,K,p);
			p+=x;
			x=p-m-1;
			calc(x,a,-1);
			y=int(b%(ll)x);
			
			if(p<=K){
				c=query(1,1,K,p,p);
				
				if((a-c)*(ll)x<b){
					b-=(a-c)*(ll)x;
					calc(x,c,1);
					a=c;
				}else{
					a-=b/(ll)x;
					calc(y,a-1,1);
					update(1,1,K,p-y,p-1,a-1);
					calc(x-y,a,1);
					update(1,1,K,p-x,p-y-1,a);
					b=0;
				}
			}else if(a*(ll)x>=b){
				a-=b/(ll)x;
				calc(y,a-1,1);
				update(1,1,K,p-y,p-1,a-1);
				calc(x-y,a,1);
				update(1,1,K,p-x,p-y-1,a);
			}else update(1,1,K,m+1,K,0);
		}
		
		END:;
		printf("%lld\n",ans);
	}return 0;
}

```

---

## 作者：rui_er (赞：4)

总算铂金组场切一题。似乎做麻烦了，而且常数蛮大的，但是没啥思维难度，记录一下。

对于每一个需求，我们将其放置在平面直角坐标系的 $(m_i,b_i)$ 位置。另外，自然有一个 $(0,0)$ 需求，也同样处理这个点。我们需要支持插入一个点的操作，并维护出答案。

先考虑不需要动态插点，只在最后求一次答案怎么做。鉴于代价呈指数函数增长，一个基础的思路就是考虑所有“最严格”的需求，并将所有要完成的工作尽量平均地分给截止前的每一时刻。接下来的问题就是如何判定“最严格”。

考虑下图中的需求：（横纵坐标不是整数，但这不重要）

![](https://cdn.luogu.com.cn/upload/image_hosting/wiyajxpg.png)

现有 $A,B,C,D,E,F,P$ 七个需求，那么直观上 $P$ 需求就不是“最严格”的，因为 $D$ 需求比 $C$ 需求多出来的工作量会被平均分到 $h$ 线段上，而这样就自然满足了 $P$ 需求。容易证明，一个需求是“最严格”的，当且仅当它在所有需求组成的上凸壳内。假如不需要动态插点，维护出上凸壳并计算出每一个线段分别的代价，再加起来即可。

假如在上面的基础上加入 $Q$ 需求，则 $C,D$ 需求就不再“最严格”了，将它们弹出并插入 $Q$ 需求即可。上述过程可以使用平衡树维护。代码中平衡树节点的 $m,b$ 即为需求的坐标，$E$ 是当前需求和上凸壳中前一个需求之间的线段对应的代价，$sumE$ 是子树内 $E$ 的和。在实现时，只需要弹出不再“最严格”的所有需求，再插入当前需求，最后重新计算当前需求及其后继（如果存在）的 $E$ 即可。

时间复杂度 $O(D\log D)$。

免责声明：这是我第一次写平衡树维护凸包，是边口胡边写加上 debug 好久出来的产物，因此代码可能较为丑陋，请谨慎参考。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, ll b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, ll b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

typedef Modint<1000000007> mint;
const ll N = 5e5 + 5;

map<ll, ll> now;

inline bool check(ll m1, ll b1, ll m2, ll b2, ll m3, ll b3) {
    ll dm1 = m2 - m1, db1 = b2 - b1;
    ll dm2 = m3 - m2, db2 = b3 - b2;
    return (__int128)db1 * dm2 > (__int128)db2 * dm1;
}

inline mint calc(ll m1, ll b1, ll m2, ll b2) {
    ll dm = m2 - m1, db = b2 - b1;
    if(db < dm) return db;
    mint k = mint(3) ^ (db / dm - 1);
    return (db % dm) * (k * 3) + (dm - db % dm) * k;
}

struct Node {
	ll m, b, rnd, sz, lc, rc;
	mint E, sumE;
	Node(ll m = 0, ll b = 0, mint E = 0, ll sz = 0) : m(m), b(b), E(E), sumE(E), rnd(rand()), sz(sz), lc(0), rc(0) {}
};
struct FHQTreap {
	Node t[N];
	ll sz, rt;
	void pushup(ll u) {
		t[u].sz = t[t[u].lc].sz + t[t[u].rc].sz + 1;
		t[u].sumE = t[t[u].lc].sumE + t[t[u].rc].sumE + t[u].E;
	}
	ll newnode(ll m, ll b, mint E) {
		t[++sz] = Node(m, b, E, 1);
		return sz;
	}
	void split(ll u, ll lim, ll& x, ll& y) {
		if(!u) {x = y = 0; return;}
		if(t[u].m <= lim) {
			x = u;
			split(t[u].rc, lim, t[u].rc, y);
		}
		else {
			y = u;
			split(t[u].lc, lim, x, t[u].lc);
		}
		pushup(u);
	}
	ll merge(ll u, ll v) {
		if(!u || !v) return u | v;
		if(t[u].rnd < t[v].rnd) {
			t[u].rc = merge(t[u].rc, v);
			pushup(u);
			return u;
		}
		else {
			t[v].lc = merge(u, t[v].lc);
			pushup(v);
			return v;
		}
	}
	ll merge(ll u, ll v, ll args...) {
	    return merge(merge(u, v), args);
	}
	void insert(ll m, ll b, mint E) {
		ll L, R;
		split(rt, m, L, R);
		rt = merge(L, newnode(m, b, E), R);
	}
	void erase(ll m) {
		ll L, M, R;
		split(rt, m - 1, L, R);
		split(R, m, M, R);
		M = merge(t[M].lc, t[M].rc);
		rt = merge(L, M, R);
	}
	ll kth(ll u, ll k) {
	    if(k <= 0 || k > t[u].sz) return 0;
		while(true) {
			if(t[t[u].lc].sz >= k) {u = t[u].lc; continue;}
			if(t[t[u].lc].sz + 1 == k) return u;
			k -= t[t[u].lc].sz + 1;
			u = t[u].rc;
		}
	}
	ll pre(ll m) {
		ll L, R;
		split(rt, m - 1, L, R);
		ll ans = kth(L, t[L].sz);
		rt = merge(L, R);
		return ans;
	}
	ll suc(ll m) {
		ll L, R;
		split(rt, m, L, R);
		ll ans = kth(R, 1);
		rt = merge(L, R);
		return ans;
	}
	void print(ll u) {
	    if(t[u].lc) print(t[u].lc);
	    cout << "(" << t[u].m << ", " << t[u].b << ", " << t[u].E << ", " << t[u].sumE << ")" << endl;
	    if(t[u].rc) print(t[u].rc);
	}
}fhq;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    fhq.insert(0, 0, 0);
    now[0] = 0;
    ll n, m, b;
    for(cin >> n; n; --n) {
        cin >> m >> b;
        if(now[m] < b) {
            ll p = fhq.pre(m);
            if(fhq.t[p].b < b) {
                if(now[m]) {
                    fhq.erase(m);
                    now[m] = 0;
                }
                // cout << "P " << p << " " << fhq.t[p].m << " " << fhq.t[p].b << " " << m << " " << b << endl << flush;
                ll q = fhq.pre(fhq.t[p].m);
                // cout << "? " << q << endl << flush;
                while(q) {
                    // cout << "Q " << q << endl << flush;
                    if(!check(fhq.t[q].m, fhq.t[q].b, fhq.t[p].m, fhq.t[p].b, m, b)) {
                        fhq.erase(fhq.t[p].m);
                        now[fhq.t[p].m] = 0;
                        p = q;
                        q = fhq.pre(fhq.t[p].m);
                    }
                    else break;
                }
                // cout << "?" << endl << flush;
                ll x = fhq.suc(m);
                // cout << "X " << x << " " << fhq.t[x].m << " " << fhq.t[x].b << " " << m << " " << b << endl << flush;
                while(x) {
                    if(fhq.t[x].b <= b) {
                        fhq.erase(fhq.t[x].m);
                        now[fhq.t[x].m] = 0;
                        x = fhq.suc(m);
                    }
                    else break;
                }
                // cout << "X " << x << " " << fhq.t[x].m << " " << fhq.t[x].b << " " << m << " " << b << endl << flush;
                if(x) {
                    ll y = fhq.suc(fhq.t[x].m);
                    while(y) {
                        // cout << "Y " << y << endl << flush;
                        if(!check(m, b, fhq.t[x].m, fhq.t[x].b, fhq.t[y].m, fhq.t[y].b)) {
                            fhq.erase(fhq.t[x].m);
                            now[fhq.t[x].m] = 0;
                            x = y;
                            y = fhq.suc(fhq.t[x].m);
                        }
                        else break;
                    }
                    fhq.erase(fhq.t[x].m);
                    fhq.insert(fhq.t[x].m, fhq.t[x].b, calc(fhq.t[p].m, fhq.t[p].b, fhq.t[x].m, fhq.t[x].b));
                }
                if(!x || check(fhq.t[p].m, fhq.t[p].b, m, b, fhq.t[x].m, fhq.t[x].b)) {
                    if(x) {
                        fhq.erase(fhq.t[x].m);
                        fhq.insert(fhq.t[x].m, fhq.t[x].b, calc(m, b, fhq.t[x].m, fhq.t[x].b));
                    }
                    fhq.insert(m, b, calc(fhq.t[p].m, fhq.t[p].b, m, b));
                    now[m] = b;
                }
            }
        }
        // fhq.print(fhq.rt);
        cout << fhq.t[fhq.rt].sumE << endl;
        // cout << flush;
    }
    return 0;
}
```

---

## 作者：pikiuk (赞：4)

将限制 $(t,x)$ 视作点，则只需要满足上凸包上的点即可满足其他限制。

考虑确定了凸包上的点后，从前往后以此满足限制即可，对于一段显然均分最优。

用 `set` 维护动态凸包即可，加入或删除点的时候对贡献重新计算。

时间复杂度 $\mathcal{O}(n\log n)$。

---

## 作者：IamZZ (赞：3)

**P组练习总结#11**

赛时又双叒叕爆零了！

原因：此题细节打挂导致浪费大量时间而只获得样例正确（乐！

温馨提示，此做法并非题解所给出的正解，而且常数巨大，复杂度也并不优秀。

具体的体现形式？看看结果：

![](https://cdn.luogu.com.cn/upload/image_hosting/tsc9fcxq.png)

众所周知，USACO 时间限制两秒，有 -O2，能跑到这么快我已经很感激了（乐，顺便一提，洛谷评测机 -O2 跑得飞快，这个代码妥妥过。

但是对于一个不擅长凸包的人来说，这是一件好事，反正我在考场上死也想不出来凸包怎么做，于是开始模拟……

慎入，请对自己常数有充分的信心！

### 题目大意

FJ 无视劳动法，压迫自己可怜的奶牛 Bessie 给 USA Cowmputing Olympiad Feb 场出题！

简直是可恶至极，居然在数据中出现了 1 分钟出 $10^{12}$ 道题这种要求！

~~怪不得 Feb 场这么非人，奶牛用牛语水出的题目谁能做啊（不是……~~

具体来说，贪心的 FJ 手上有 $d(d\leq2\times10^5)$ 个要求形如 $m_i,b_i(m_i\le10^6,b_i\le10^{12})$，表示在前 $m_i$ 分钟里，Bessie 要出至少 $e_i$ 道题。

可怜的奶牛 Bessie 肯定被压迫得神经质了，耗能可怕，如果在第 $i$ 分钟里她选择出 $a_i$ 道题，那她将会消耗的能量是：$3^{a_i-1}$，不出则不消耗。

现在，要求你求出同时满足前 $i$ 个要求所需要的最小的能量总和 $e_i$，答案对 $10^9+7$ 取模。

### 解题思路

拿到这道题的第一眼我就瞄出了一个性质，决定了这道题我就不会往凸包上想……

性质一：挺明显的，对于每分钟出的题目 $a_i$，序列 $a$ 应该是一个**固定的单调不上升的序列**，这样一定最优。

只有我们的 $a$ 是排好序的，我们才可以让每个 $i$ 的前缀和都尽量大，固定的也很好想，$a$ 中的数是可以确定的。

性质二：再从能量的消耗上入手推性质，既然是指数级，我们可以想到，尽量让每一分钟的 $a_i$ 平均分配题目，这样能用最小的能量出要求的题目。

本以为性质一假了，但其实是代码假了，怪不得性质，人太菜（笑。

### 具体实现

有了这两条性质，我十分聪（yu）明（chun）得认为，这是一道用数据结构的模拟题，一道几何数学题就此转世……

操作很杂，考虑用线段树，支持区间赋值，区间求和，单点求值，没了。

记录以下信息：

$s$：区间内的出题总数，出了几道题？

$w$：区间内的能量消耗，要补补了！

$v$：懒标记，在叶子的时候就是那个时间对应的出题数。

为方便书写，计 $S_i$ 为 $i$ 的前缀和，具体用线段树求。

这三个信息的修改与统计并不是很难，但讨厌的模拟还没开始呢。

遇到询问，先判断 $S_{m_i}$是否满足 $e_i$，若满足直接输出当前答案 $ans$。

不满足？那就需要在前面补出题了！

看图辅助理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/lzu2d32p.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/qzamsdm6.png)

但问题还没有解决，$pos$ 怎么找到？

我们发现，$pos$ 是满足 $S_{pos-1}+a_{pos-1}\times(m-pos+1)\ge b$ 最右的一个位置（为了满足单调性，$a_{pos}\le a_{pos-1}$）。

为了方便边界，我们计 $a_0=+\infty$， 毕竟 $a_1$ 没有限制。

这样子我们就可以二分找到 $pos$ 了，二分上要用线段树求 $S,a$，常数和复杂度都巨大。

计 $v=\lfloor\frac{b-S_{pos-1}}{m-pos+1}\rfloor$，$x=(b-S_{pos-1})\bmod(m-pos+1)$。

那我们将 $pos$ 到 $pos+x-1$ 全部赋值为 $v+1$，$pos+x$ 到 $m$ 赋值为 $v$，在赋值的时候更新答案！

考场的时候也不知道是不是脑子被牛踢了，一看 $b\leq10^{12}$，快速幂虽然可以，但是会增加一些些常数，对于卡常做法，这是不能接受的！

于是我想到了，$\Theta(\sqrt b)$ 预处理，$\Theta(1)$ 查询的……**光速幂**！在此感谢毒瘤 lxl 的真传助我卡常！

记录 $f_i=3^i,g_i=f_{10^6}^i(i\leq10^6)$，那 $3^b=g_{\lfloor \frac b{10^6}\rfloor}\times f_{b \bmod 10^6}$，记得取模。

补题操作完成了，可是你会发现，是不能通过第三个样例的！

我们还漏了什么？哦……前面补的题目，是不是要从后面取？

没错！前面加了那么多道题，后面就不用出那么多题来满足特定的条件了~多么好！又给我们加工作量了！

两种情况，若 $m$ 之后全部出题量都能被清除掉，那直接清掉就好了（赋值为 0）。

否则就需要一下操作，看图写话：

![](https://cdn.luogu.com.cn/upload/image_hosting/ey20aowu.png)

我们不妨计 $w=b-S_m$，现在我们要找到最左的一个 $pos$ 满足 $S_{pos}-S_m-a_{pos+1}\times(pos-m)\ge w$（还是满足单调性的限制）。

还是二分去找这个 $pos$，再次计 $v=\lfloor\frac{S_{pos}-S_m-w}{pos-m}\rfloor$，$x=(S_{pos}-S_m-w)\bmod(pos-m)$。

重新分配 $m+1$ 到 $pos$ 的出题数，将 $m+1$ 到 $m+x$ 赋为 $v+1$，$m+x+1$ 到 $pos$ 赋为 $v$。

综上我们完成了一次要求的修改，答案实时更新。

复杂度 $\Theta(d\log_2^2m)$，有点卡常，啊啊啊可恶为什么我的代码常数总是这么大！！

完结撒花(●'◡'●)，P.S.代码已优化，USACO 官网可以跑进 1900ms 了。

### 参考代码

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5,d=1e9+7,Z=1e6; 
int q,m,l,r,mid,p,g[N]={1},f[N]={1},ans;
ll b,op,v,x,w;
struct tree
{
	ll v,s,w;//标记，数量，答案
}t[N<<2];
int calc(ll p)//光速幂！我不太智慧
{
	if(!p)
	  return 0;
	--p;//能量消耗的次数是出题数减一
	int v=1ll*g[p/Z]*f[p%Z]%d;
	return v; 
}
void pushdown(int l,int r,int p)
{
	if(t[p].v<0)
	  return ;
	int mid=l+r>>1;
	t[p<<1].v=t[p].v;//懒标记下传
	t[p<<1|1].v=t[p].v;
	t[p<<1].s=t[p].v*(mid-l+1);//出题数更新
	t[p<<1|1].s=t[p].v*(r-mid);
	t[p<<1].w=1ll*(mid-l+1)*calc(t[p].v)%d;//光速幂配合答案更新
	t[p<<1|1].w=1ll*(r-mid)*calc(t[p].v)%d;
	t[p].v=-1;
	return ;
}
ll query(int l,int r,int p,int x,int y)//求区间出题数
{
	if(l>y||r<x)
	  return 0;
	if(l>=x&&r<=y)
	  return t[p].s;
	int mid=l+r>>1;
	pushdown(l,r,p);
	return query(l,mid,p<<1,x,y)+query(mid+1,r,p<<1|1,x,y);
}
ll find(int l,int r,int p,int x)//查询a[pos]
{
	if(!x)
	  return 1e12;//a[0]视为inf
	if(l>x||r<x)
	  return 0;
	if(l==r)
	  return t[p].v;
	int mid=l+r>>1;
	pushdown(l,r,p);
	return find(l,mid,p<<1,x)|find(mid+1,r,p<<1|1,x);
}
void modify(int l,int r,int p,int x,int y,ll z)//区间赋值修改
{
	if(l>y||r<x)
	  return ;
	if(l>=x&&r<=y)
	{
		t[p].v=z;//懒标记更新
		t[p].s=z*(r-l+1);//大小更新
		t[p].w=1ll*calc(z)*(r-l+1)%d;//区间答案更新
		return ;
	}
	pushdown(l,r,p);
	int mid=l+r>>1;
	modify(l,mid,p<<1,x,y,z);
	modify(mid+1,r,p<<1|1,x,y,z);
	t[p].s=t[p<<1].s+t[p<<1|1].s;
	t[p].w=t[p<<1].w+t[p<<1|1].w;
	return ;
}
void build(int l,int r,int p)//赋初值
{
	if(l==r)
	  return ;
	t[p].v=-1;
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	return ; 
}
int main()
{
	int i;
	scanf("%d",&q);
	for(i=1;i<=Z;++i)//光速幂预处理
	  f[i]=1ll*f[i-1]*3%d;
	for(i=1;i<=Z;++i)
	  g[i]=1ll*g[i-1]*f[Z]%d;
	build(1,N,1);
	while(q)
	{
		--q;
		scanf("%d%lld",&m,&b);
		x=query(1,N,1,1,m); 
		if(x>=b)//根本不用修改
		{
			ans=t[1].w%d;
			printf("%d\n",ans);
			continue;
		}
		l=1,r=m;
		while(l<=r)//补题二分
		{
			mid=l+r>>1;
			op=find(1,N,1,mid-1);//求a[pos-1]
			if(query(1,N,1,1,mid-1)+op*(m-mid+1)>=b)
			  p=mid,l=mid+1;
			else
			  r=mid-1;
		}
		w=b-x;//计算w
		b=b-query(1,N,1,1,p-1);
		v=b/(m-p+1);
		x=b%(m-p+1);
		modify(1,N,1,p,p+x-1,v+1);//前半段赋值
		modify(1,N,1,p+x,m,v);//后半段赋值
		l=m+1,r=N-1;
		if(query(1,N,1,m+1,N)>w)//后面取一部分
		{
			while(l<=r)
			{
				mid=l+r>>1;
				op=find(1,N,1,mid+1);//求a[pos+1]
				if(query(1,N,1,m+1,mid)-op*(mid-m)>=w)
				  p=mid,r=mid-1;
				else
				  l=mid+1;
			}
			b=query(1,N,1,m+1,p);
			v=(b-w)/(p-m);
			x=(b-w)%(p-m);
			modify(1,N,1,m+x+1,p,v);//前半段
			modify(1,N,1,m+1,m+x,v+1);//后半段
		}
		else//取光了
		  modify(1,N,1,m+1,N,0);//清空！
		ans=t[1].w%d;
		printf("%d\n",ans);
	}
}
```



---

## 作者：Reunite (赞：1)

考虑如果从 $(t_1,y_1)$ 到 $(t_2,y_2)$ 如何最优，因为每分钟代价是指数，显然越平均越好，除一下模一下即可简单计算。再考虑三个 $t$ 单增的点 $(t_{1,2,3},y_{1,2,3})$ 如何分配最优，如果这三个点上凸，那显然直接 $1,2$ 一段，$2,3$ 一段更优，否则可以证明直接走 $1,3$ 在最优的同时也满足了 $(t_2,y_2)$ 的限制。

可以归纳说明我们分的段一定在当前点集的上凸壳上，只需要 set 维护动态加点上凸壳即可，每次删除一段点之后撤销贡献再加入该点两端贡献即可。代码细节非常多。复杂度均摊 $O(n\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#define int long long
#define mod 1000000007
using namespace std;

int n,ans;
set <pair <int,int>> st;

inline int calc(int x,int k){
	if(k<0) return 0;
	k%=(mod-1);
	int tmp=1;
	while(k){
		if(k&1) tmp=tmp*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return tmp;
}

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int val(int x,int y){
	int xx=x/y,md=x%y;
	return (calc(3,xx)*md%mod+calc(3,xx-1)*(y-md)%mod)%mod;
}

inline double K(int x,int y,int xx,int yy){return x==xx?1e9:1.*(y-yy)/(x-xx);}

signed main(){
	in(n);
	st.insert({0,0});
	int x,y;
	in(x),in(y);
	st.insert({x,y});
	ans=val(y,x);
	printf("%lld\n",ans);
	for(int i=2;i<=n;i++){
		int x,y;
		in(x),in(y);
		auto rt=st.lower_bound({x,0});
		auto lf=prev(rt);
		if((*lf).second>=y||(rt!=st.end()&&(*rt).first==x&&(*rt).second>=y)){
			printf("%lld\n",ans);
			continue;
		}
		while(rt!=st.end()&&(*rt).second<=y) rt++;
		if(rt==st.end()){
			while(lf!=st.begin()){
				int x1=(*lf).first,y1=(*lf).second;
				int x2=(*prev(lf)).first,y2=(*prev(lf)).second;
				if(K(x,y,x1,y1)>K(x1,y1,x2,y2)) lf--;
				else break;
			}
			auto it=next(lf);
			while(it!=st.end()){
				auto tmp=*prev(it);
				(ans+=mod-val((*it).second-tmp.second,(*it).first-tmp.first))%=mod;
				it++;
			}
			(ans+=val(y-(*lf).second,x-(*lf).first))%=mod;
			st.erase(next(lf),st.end());
			st.insert({x,y});
			printf("%lld\n",ans);
			continue;
		}
		while(next(rt)!=st.end()){
			int x1=(*rt).first,y1=(*rt).second;
			int x2=(*next(rt)).first,y2=(*next(rt)).second;
			if(K(x1,y1,x2,y2)>K(x,y,x1,y1)) rt++;
			else break;
		}
		while(lf!=st.begin()){
			int x1=(*lf).first,y1=(*lf).second;
			int x2=(*prev(lf)).first,y2=(*prev(lf)).second;
			if(K(x,y,x1,y1)>K(x1,y1,x2,y2)) lf--;
			else break;
		}
		auto it=next(lf);
		while(prev(it)!=rt){
			auto tmp=*prev(it);
			(ans+=mod-val((*it).second-tmp.second,(*it).first-tmp.first))%=mod;
			it++;
		}
		int x1=(*lf).first,y1=(*lf).second;
		int x2=(*rt).first,y2=(*rt).second;
		if(K(x1,y1,x2,y2)<K(x1,y1,x,y)){
			(ans+=val(y-y1,x-x1))%=mod;
			(ans+=val(y2-y,x2-x))%=mod;
			st.erase(next(lf),rt);
			st.insert({x,y});
		}
		else (ans+=val(y2-y1,x2-x1))%=mod;
		printf("%lld\n",ans);
	}

	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：1)

怎么题解全是线段树啊，**提供一个不用线段树的做法。**

场上用了两个半小时才切掉，真不能要了。

下面的 $(x,y)$ 对应原题面中的 $(m,b)$。

只有一个需求的时候的最小能量，考虑就是有 $x$ 分钟有 $y$ 的测试样例时，注意到 $3^{t-1}$ 的性质，有 $\sum_{j<i}3^{j-1}<3^{i-1}$，那么就是全部往小的，平均摊开一定是最优秀的。

不难实现，在一段连续的，$x$ 分钟有 $y$ 个需求时可以 $O(\log V)$ 的时间求（瓶颈在于求快速幂），记这个函数是 $f(x,y)$ 表示最小能量。

就是首先你要发现答案可以表示成，考虑从所有需求中选一个子序列 $(x_1,y_1),(x_2,y_2),\cdots,(x_k,y_k)$，如果这个子序列可以满足所有需求的限制（并且不存在二维偏序），那么答案可以写成：

$$f(x_1,y_1)+\sum_{i=2}^kf(x_i-x_{i-1},y_i-y_{i-1})$$

接下来考虑一组询问的做法，考虑三个决策点 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$，分别代表每一个需求，设 $x_1<x_2<x_3,y_1<y_2<y_3$。（如果形成了二维偏序的关系，后面那个是没意义的），钦定 $x_1,x_3$ 已经选择，那么就需要考虑 $x_2$ 是否被选。

鉴于那个函数是平均分配的，它肯定同时具备许多直线的性质。

这里想了很长时间，考虑扔到二维平面上，往**凸包**上去想就是有前途的。注意到如果上面那个子序列选凸包是一定可以合法的，我们显然只需要对于同一个 $x$，考虑最大的 $y$。然后凸包的那些线段就会把输入的所有 $(x,y)$ 包含在里面，而且最小的性质，满足会节省的最多。

所以关于答案的子序列选取，直接选取凸包然后计算上文那个柿子就行了。

$O(n^2)$ 做法就呼之欲出了：对于每次询问，直接用单调栈维护凸包，但是不能动态。

考虑用 ```std::set``` 维护上凸包，一条线段的权值就是 $f(\triangle x,\triangle y)$，答案是所有线段的权值和。然后插入点 $(x_i,y_i)$ 也就是 $(m_i,b_i)$ 时，找到新的前驱和后继，然后删去被删的点的贡献，加入 $(\text{pre},p)$ 以及 $(p,\text{nxt})$ 的贡献即可（有可能不存在）

每个点最多删一次，所以复杂度是对的。时间复杂度 $O(n\log nV)$。

[提交记录 / 赛时 AC 代码。](https://loj.ac/s/2014586)

赛时写复杂了，斜率小于 $0$ 的完全不用维护，因为对于答案的贡献是 $0$。

---

## 作者：Perta (赞：1)

设 $a_i$ 表示在第 $i$ 分钟准备了 $a_i$ 个测试用例。

***

考虑仅处理一个需求 $(m,d)$ 时怎么放更优：

- $\max_{1\leq i\leq m}a_i-\min_{1\leq i\leq m}a_i\leq1$。

若该条件不满足，即存在 $(i,j)$ 使得 $\lvert a_i-a_j\rvert\geq2$，那么设 $S=a_i+a_j$，令 $a_i\leftarrow\lfloor\frac{S}{2}\rfloor,a_j\leftarrow\lceil\frac{S}{2}\rceil$，答案显然更优（操作后两者代价之和必然小于操作前的 $3^{\max(a_i,a_j)}$）。

由于 $\sum_{i=1}^{m}a_i=d$，故 $\max_{1\leq i\leq m}a_i=\lceil\frac{d}{2}\rceil,\min_{1\leq i\leq m}a_i=\lfloor\frac{d}{2}\rfloor$。代价是容易计算的。

***

假设现在需要新加入一个需求 $(m',d')$。强制令 $a_i\geq a_{i+1}$，对后续的影响显然不会更劣，加入一个需求时需要额外准备的测试用例不会更多。

若需求 $(m',d')$ 已经被满足，直接忽略这个需求即可；

否则，在 $[1,m']$ 中还需要额外准备 $d'-\sum_{i=1}^{m'}a_i$ 个测试用例。等价于，每次选择一个 $i\in[1,m']$，令 $a_i\leftarrow a_i+1$，直到 $\sum_{i=1}^{m'}a_i=d'$，这样不会影响到之前的决策。为了使代价最小化，每次选择的 $a_i$ 应等于 $\min_{1\leq j\leq m'}a_j$。最后，依然强制令 $a_i\geq a_{i+1}$。

不过，额外准备了 $x$ 个，意味着可以在 $[m'+1,+\infty)$ 中少准备 $x$ 个。类似的，每次选择一个 $i\in[m'+1,+\infty)$，要求 $a_i>0$，令 $a_i\leftarrow a_i-1$，直到减去的总和等于 $x$ 或者 $\forall i\in[m'+1,+\infty),a_i=0$。每次选择的 $a_i$ 应等于 $\max_{m'<j}a_j$。

上述两种操作本质是相同的。

***

以**需要额外准备的操作**为例。

可以发现，我们每次修改的 $a_i$ 值域是一个区间 $[l,r]$。由于 $a_i\geq a_{i+1}$，可以强行令每次修改的下标区间为 $[L,R](R=m')$，其中 $L$ 为最小的满足修改前 $a_i=r$ 的 $i$。设修改后 $[L,R]$ 中 $a_i$ 的值域为 $[l',r']$，有结论：

- $r'-l'\leq 1$。

这个式子与仅处理一个需求时的那个式子长得很像，它的意义可以理解为：将 $[L,R]$ 中的与额外需要的测试用例合起来，重新分配到 $[L,R]$ 中去，合法的同时使得代价最小。相当于将 $[L,R]$ 单独提出来作为一个需求对应的序列，类似于前文那个式子，可以得到 $r'-l'\leq1$。

***

那么维护就好做了。

过程很简单：每次找到需要修改的 $[L,R]$，然后找到需要覆盖成 $r'$ 的 $[L,mid]$ 和需要覆盖成 $l'$ 的 $[mid+1,R]$，数据结构维护即可。

找 $[L,R]$ 可以在线段树上二分，操作只有区间覆盖，时间复杂度 $O(n\log m)$。

由于不喜欢线段树上二分的细节（才不是写寄了），作者一怒之下将二分套到了线段树外，导致[代码](https://www.luogu.com.cn/paste/eqdmblf0)抽象的同时还多了个 $\log$。

---

## 作者：Judgelight (赞：0)

[传送门](https://www.luogu.com.cn/problem/P10196)

---

真勾巴绷不住了会 $m_i$ 递增不会这个题。

我们先考虑 $m_i$ 递增，本质上就是每次在末尾多添一个限制。如果这个限制已经满足了，那么我们就不管它；如果这个限制不满足，我们就去找前面测试用例数量最少的那些天去增加，这么做是最优的因为对于 $a>b,3^{a+1}-3^a>3^{b+1}-3^b$。

然后就有一个很傻逼的 $O(\log^2 n)$ 的做法，因为测试用例数量是无序的。但是真的是无序的吗，其实让测试用例递减一定是优的，因为这样能满足的限制更多，所以我们就得到了一个 $O(\log n)$ 的做法。

然后我们考虑如果 $m_i$ 不递增，那么对于 $[1,m_i]$ 部分我们要做的事情是不变的；对于 $[m_i+1,n]$，我们要做的是减少一部分的测试用例数量，因为前面增加了一些，那我们减少肯定也是先减大的，所以我们做一个和前面类似的操作即可，复杂度也是 $O(\log n)$ 的。

所以我们最后复杂度是 $O(d\log n)$ 的，因为我傻逼所以写的 $O(D\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define eb emplace_back
#define mk make_pair
#define N 1000009
using namespace std;
const int mod=1e9+7,n=1000001,inf=1e18;
int ksm(int a,int b){
	if(b<0)return 0;
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return ans;
}
int d;
struct Node{int l,r,s[2],cov,mn,mx;}tr[N*4];
inline void pushup(int u){
	tr[u].s[0]=tr[u<<1].s[0]+tr[u<<1|1].s[0];
	tr[u].s[1]=tr[u<<1].s[1]+tr[u<<1|1].s[1],(tr[u].s[1]>=mod)&&(tr[u].s[1]-=mod);
	tr[u].mx=max(tr[u<<1].mx,tr[u<<1|1].mx),tr[u].mn=min(tr[u<<1].mn,tr[u<<1|1].mn);
}
inline void eval(Node &t,int cov){
	t.s[0]=(t.r-t.l+1)*cov,t.s[1]=(t.r-t.l+1)*ksm(3,cov-1)%mod;
	t.mn=t.mx=t.cov=cov;
}
inline void pushdown(int u){if(~tr[u].cov)eval(tr[u<<1],tr[u].cov),eval(tr[u<<1|1],tr[u].cov),tr[u].cov=-1;}
void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r,tr[u].cov=-1;
	if(l==r)return ;
	int mid=(l+r)>>1;build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	pushup(u);
}
void mdf(int u,int l,int r,int x){
	if(l>r)return ;
	if(tr[u].l>=l&&tr[u].r<=r){eval(tr[u],x);return ;}
	pushdown(u);int mid=(tr[u].l+tr[u].r)>>1;
	if(l<=mid)mdf(u<<1,l,r,x);if(r>mid)mdf(u<<1|1,l,r,x);
	pushup(u);
}
int qry(int u,int l,int r){
	if(l>r)return 0;
	if(tr[u].l>=l&&tr[u].r<=r)return tr[u].s[0];
	pushdown(u);int mid=(tr[u].l+tr[u].r)>>1;
	if(r<=mid)return qry(u<<1,l,r);if(l>mid)return qry(u<<1|1,l,r);
	return qry(u<<1,l,r)+qry(u<<1|1,l,r);
}
int qryp(int u,int l,int r,int x){
	pushdown(u);
	if(tr[u].l>=l&&tr[u].r<=r){
		if(tr[u].mx<=x)return tr[u].l;if(tr[u].mn>x)return tr[u].r+1;
		if(tr[u<<1].mn>x)return qryp(u<<1|1,l,r,x);
		else return qryp(u<<1,l,r,x);
	}
	int mid=(tr[u].l+tr[u].r)>>1;
	if(r<=mid)return qryp(u<<1,l,r,x);if(l>mid)return qryp(u<<1|1,l,r,x);
	if(tr[u<<1].mn>x)return qryp(u<<1|1,l,r,x);
	else return qryp(u<<1,l,r,x);
}
int qrys(int u,int l,int r,int x){
	pushdown(u);
	if(tr[u].l>=l&&tr[u].r<=r){
		if(tr[u].mn>=x)return tr[u].r;if(tr[u].mx<x)return tr[u].l-1;
		if(tr[u<<1|1].mx<x)return qrys(u<<1,l,r,x);
		else return qrys(u<<1|1,l,r,x);
	}
	int mid=(tr[u].l+tr[u].r)>>1;
	if(r<=mid)return qrys(u<<1,l,r,x);if(l>mid)return qrys(u<<1|1,l,r,x);
	if(tr[u<<1|1].mx<x)return qrys(u<<1,l,r,x);
	else return qrys(u<<1|1,l,r,x);
}
signed main(){
	scanf("%lld",&d);
	build(1,1,n);
	for(int i=1,x,y;i<=d;i++){
		scanf("%lld%lld",&x,&y);
		int dt=y-qry(1,1,x);
		if(dt<=0){printf("%lld\n",tr[1].s[1]);continue;}
		int l=0,r=1e12;
		while(l<r){
			int mid=(l+r+1)>>1;int pos=qryp(1,1,x,mid);
			if(mid*(x-pos+1)-qry(1,pos,x)<=dt)l=mid;
			else r=mid-1;
		}
		int pos=qryp(1,1,x,l),res=l*(x-pos+1)-qry(1,pos,x);
		mdf(1,pos,pos+(dt-res)-1,l+1),mdf(1,pos+(dt-res),x,l);
		if(y!=tr[1].s[0]){
			if(qry(1,x+1,n)<=dt){mdf(1,x+1,n,0);goto end;}
			l=0,r=1e12;
			while(l<r){
				int mid=(l+r)>>1;int pos=qrys(1,x+1,n,mid);
				if(qry(1,x+1,pos)-mid*(pos-x)<=dt)r=mid;
				else l=mid+1;
			}
			pos=qrys(1,x+1,n,l),res=qry(1,x+1,pos)-l*(pos-x);
			mdf(1,pos-(dt-res)+1,pos,l-1),mdf(1,x+1,pos-(dt-res),l);
		}
		end:;
		printf("%lld\n",tr[1].s[1]);
	}
	return 0;
}
```

---

## 作者：小木虫 (赞：0)

### Preface  
咋都是维护凸包，发怒。  
我没维护凸包过的。  
### Problem  
Bessie 正在努力为美国件算机奥林匹克二月的竞赛准备测试用例。每一分钟，她可以选择不准备测试用例，不花费能量；或者对于某个正整数 $a$，花费 $3^{a−1}$ 能量准备 $a$ 个测试用例。

Farmer John 有 $D$（$1\le D\le 2\cdot 10^5$）个需求。对于第 $i$ 个需求，他告诉 Bessie，在前 $m_i$ 分钟内她总共需要准备至少 $b_i$ 个测试用例（$1\le m_i\le 10^6,1\le b_i\le 10^{12}$）。

令 $e_i$ 为满足前 $i$ 个需求 Bessie 最小需要花费的能量。输出 $e_1,\ldots,e_D$ 模 $10^9+7$ 的余数。
### Solution  
先考虑一下 $O(nq\log V)$ 咋做。  
首先肯定对于只有一个限制你就平摊就对了。  
对于每个询问，我们把限制从小到大排序，删掉一些没用的限制。  
然后我们使用栈维护连续段，每段内准备的测试用例个数是相等的。  
我们肯定每次加一个测试用例是加到已经有的测试用例数最小的时间。  
如果我们对于个数相同的时间选前面的时间的话，你会发现我们的测试用例数对于时间是不升的，所以我们的栈是一个单调栈，不断合并连续段即可。  
每加一个限制最多会使得段数加一，所以单次是均摊 $O(n\log V)$ 的（含快速幂）。  

然后考虑一下怎么变得更快。  
先用一个 ODT 维护一下原来的连续段，加一个限制依然最多会使得段数加一，所以如果可以比较好的合并段和维护信息那么复杂度是对的。  

对于在新加限制前面的段，我们可以直接套用之前暴力的栈合并，但是你如果直接加会导致后面的限制变松，为了再紧一紧，你要把后面的测试用例收回。  

所幸这两部分是完全对称的，至此我们就 AC 了这道题，总复杂度 $O(n(\log n+\log V))$。  
特别注意 Set 的迭代器管理，非常恶心。  

```cpp
#include <bits/stdc++.h>
#define mp make_pair
#define fir first
#define sec second
#define int long long
using namespace std;
const int N=2e5+10,mod=1e9+7,maxv=1e6;
int D;
int qpow(int a,int b){
	b--;if(b==-1)return 0;
	int res=1;a%=mod;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;b>>=1;
	}return res;
}
pair <int,int> q[N];
namespace seg{
	int tree[(maxv+10)<<4],tag[(maxv+10)<<4];
	void pushdown(int rt,int left,int right){
		int mid=(left+right)>>1;
		if(tag[rt]){
			tag[rt<<1]+=tag[rt];
			tag[rt<<1|1]+=tag[rt];
			tree[rt<<1]+=(tag[rt]*(mid-left+1));
			tree[rt<<1|1]+=(tag[rt]*(right-mid));
			tag[rt]=0;
		}
	}
	void pushup(int rt){tree[rt]=tree[rt<<1]+tree[rt<<1|1];}
	void update(int rt,int left,int right,int L,int R,int x){
		if(left<right)pushdown(rt,left,right);
		if(left>=L&&right<=R){
			tag[rt]+=x;
			tree[rt]+=x*(right-left+1);
			return;
		}int mid=(left+right)>>1;
		if(L<=mid)update(rt<<1,left,mid,L,R,x);
		if(mid<R)update(rt<<1|1,mid+1,right,L,R,x);
		pushup(rt);
	}
	int query(int rt,int left,int right,int L,int R){
		if(left<right)pushdown(rt,left,right);
		if(left>=L&&right<=R)return tree[rt];
		int mid=(left+right)>>1,res=0;
		if(L<=mid)res+=query(rt<<1,left,mid,L,R);
		if(mid<R)res+=query(rt<<1|1,mid+1,right,L,R);
		return res;
	}
}
struct node{
	int l,r,s;
	bool operator <(const node b)const{
		if(r!=b.r)return r<b.r;
		return l<b.l;
	}
};
int ans=0;
set <node> S;
void modify(int x,int w){
	w=w-seg::query(1,1,maxv,1,x);
	if(w<=0)return;
	auto it=S.lower_bound((node){0,x,0});auto tmp=it;
	if(x!=tmp->r){
		S.insert((node){tmp->l,x,tmp->s});
		S.insert((node){x+1,tmp->r,tmp->s});
		S.erase(tmp);
	}
	it=S.lower_bound((node){0,x,0});
	auto pre=it;pre--;
	int Tmp=w;
	while(w){
		int Top=pre->s,sz=(it->r)-(it->l)+1,p=it->s;
		if(w>=(Top-p)*sz){
			w-=(Top-p)*sz;
			ans-=qpow(3,p)*sz%mod;
			ans+=qpow(3,Top)*sz%mod;
			seg::update(1,1,maxv,it->l,it->r,Top-p);
			ans%=mod;ans+=mod;ans%=mod;
			int L=pre->l,R=it->r;
			S.erase(pre);
			it=S.lower_bound((node){0,x,0});
			S.erase(it);
			it=S.insert((node){L,R,Top}).fir;
			pre=it;pre--;
		}else{
			int to=w/sz,m=w%sz;w=0;
			seg::update(1,1,maxv,it->l,it->r,to);
			if(m){
				ans-=qpow(3,p)*sz%mod;
				p+=to;sz-=m;
				ans+=qpow(3,p)*sz%mod;
				ans+=qpow(3,p+1)*m%mod;
				ans%=mod;ans+=mod;ans%=mod;
				int L=it->l,R=it->r;
				S.erase(it);
				seg::update(1,1,maxv,L,L+m-1,1);
				S.insert((node){L+m,R,p});
				it=(S.insert((node){L,L+m-1,p+1})).fir;
			}else{
				ans-=qpow(3,p)*sz%mod;
				p+=to;
				int L=it->l,R=it->r;
				S.erase(it);
				it=(S.insert((node){L,R,p})).fir;
				ans+=qpow(3,p)*sz%mod;
				ans%=mod;ans+=mod;ans%=mod;
			}
		}
	}
	if(x==1e6)return;
	x++;w=min(Tmp,seg::query(1,1,maxv,x,maxv));
	it=S.lower_bound((node){0,x,0});
	pre=it;pre++;
	while(w){
		int Top=pre->s,sz=(it->r)-(it->l)+1,p=it->s;
		if(w>=(p-Top)*sz){
			w-=(p-Top)*sz;
			ans-=qpow(3,p)*sz%mod;
			ans+=qpow(3,Top)*sz%mod;
			seg::update(1,1,maxv,it->l,it->r,Top-p);
			ans%=mod;ans+=mod;ans%=mod;
			int L=it->l,R=pre->r;
			S.erase(pre);
			it=S.lower_bound((node){0,x,0});
			S.erase(it);
			it=S.insert((node){L,R,Top}).fir;
			pre=it;pre++;
		}else{
			int to=w/sz,m=w%sz;w=0;
			seg::update(1,1,maxv,it->l,it->r,-to);
			if(m){
				ans-=qpow(3,p)*sz%mod;
				p-=to;sz-=m;
				ans+=qpow(3,p)*sz%mod;
				ans+=qpow(3,p-1)*m%mod;
				ans%=mod;ans+=mod;ans%=mod;
				int L=it->l,R=it->r;
				S.erase(it);
				seg::update(1,1,maxv,R-m+1,R,-1);
				S.insert((node){L,R-m,p});
				it=(S.insert((node){R-m+1,R,p-1})).fir;
			}else{
				ans-=qpow(3,p)*sz%mod;
				p-=to;
				int L=it->l,R=it->r;
				S.erase(it);
				it=(S.insert((node){L,R,p})).fir;
				ans+=qpow(3,p)*sz%mod;
				ans%=mod;ans+=mod;ans%=mod;
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	S.insert((node){0,0,(int)1e12});
	S.insert((node){1,(int)1e6,0});
	S.insert((node){(int)1e6+1,(int)1e6+1,0});
	cin>>D;
	for(int i=1;i<=D;i++){
		cin>>q[i].fir>>q[i].sec;
		modify(q[i].fir,q[i].sec);
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

不难发现是平均分。同时注意到 $a_i\ge a_{i+1}$，否则可以交换。

每次新加入限制时选前面最靠前的最小值加，同时后面最靠后的最大值可以减。

使用线段树优化这一过程，时间复杂度 $O(D\log V)$。

比较考验线段树二分基本功。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=1e9+7;
const int N=1e6+5;
const int NN=1e6;
ll fpw(ll a,ll b,ll p){
	a=a%p;
	ll r=1;
	while(b){
		if(b&1)r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r%p;
}
struct DS1{
	struct node{
		ll sz,sum,z,pz;
		ll lsz,rsz;
	}tr[N*4];
	void pu(int u){
		tr[u].sz=tr[u<<1].sz+tr[u<<1|1].sz;
		tr[u].sum=(tr[u<<1].sum+tr[u<<1|1].sum)%mod;
		tr[u].lsz=tr[u<<1].lsz;
		tr[u].rsz=tr[u<<1|1].rsz;
	}
	void pd_(int u,int L,ll z,ll pz){
		if(z==-1)return ;
		tr[u].sz=z*L;
		tr[u].sum=pz*L%mod;
		tr[u].z=z;
		tr[u].pz=pz;
		tr[u].lsz=tr[u].rsz=z;
	}
	void pd(int u,int l,int r){
		int mid=l+((r-l)>>1);
		pd_(u<<1,mid-l+1,tr[u].z,tr[u].pz);
		pd_(u<<1|1,r-mid,tr[u].z,tr[u].pz);
		tr[u].z=-1;
	}
	void bld(int u,int l,int r){
		tr[u].z=-1;
		if(l==r)return ;
		int mid=l+((r-l)>>1);
		bld(u<<1,l,mid);
		bld(u<<1|1,mid+1,r);
		pu(u);
	}
	void upd_(int u,int l,int r,int ql,int qr,ll z,ll pz){
		if(ql<=l&&r<=qr){
			pd_(u,r-l+1,z,(z==0)?(0):(fpw(3,z-1,mod)));
			return ;
		}
		pd(u,l,r);
		int mid=l+((r-l)>>1);
		if(ql<=mid)upd_(u<<1,l,mid,ql,qr,z,pz);
		if(mid+1<=qr)upd_(u<<1|1,mid+1,r,ql,qr,z,pz);
		pu(u);
	}
	void upd(int u,int l,int r,int ql,int qr,ll z){
		upd_(u,l,r,ql,qr,z,(z==0)?(0):(fpw(3,z-1,mod)));
	}
	ll Qsz(int u,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return tr[u].sz;
		pd(u,l,r);
		int mid=l+((r-l)>>1);
		ll res=0;
		if(ql<=mid)res+=Qsz(u<<1,l,mid,ql,qr);
		if(mid+1<=qr)res+=Qsz(u<<1|1,mid+1,r,ql,qr);
		return res;
	}
	int findL(int u,int l,int r,int x,ll p,ll &rsum){
		if(r<=x){
			ll rr=rsum+tr[u].sz;
			int res=NN+1;
			if(tr[u].rsz*(x-r+1)-(rsum+tr[u].rsz)<=p){
				if(tr[u].lsz*(x-l+1)-(rsum+tr[u].sz)<=p)res=l;
				else{
					pd(u,l,r);
					int mid=l+((r-l)>>1);
					res=min(res,findL(u<<1|1,mid+1,r,x,p,rsum));
					res=min(res,findL(u<<1,l,mid,x,p,rsum));
				}
			}
			rsum=rr;
			return res;
		}
		if(x<l)return NN+1;
		pd(u,l,r);
		int mid=l+((r-l)>>1);
		int res=findL(u<<1|1,mid+1,r,x,p,rsum);
		return min(res,findL(u<<1,l,mid,x,p,rsum));
	}
	int findR(int u,int l,int r,int x,ll p,ll &lsum){
		if(x+1<=l){
			ll lt=lsum+tr[u].sz;
			int res=0;
			if(lsum+tr[u].lsz-tr[u].lsz*(l-x)<=p){
				if(lsum+tr[u].sz-tr[u].rsz*(r-x)<=p)res=r;
				else{
					pd(u,l,r);
					int mid=l+((r-l)>>1);
					res=max(res,findR(u<<1,l,mid,x,p,lsum));
					res=max(res,findR(u<<1|1,mid+1,r,x,p,lsum));
				}
			}
			lsum=lt;
			return res;
		}
		if(r<x+1)return 0;
		pd(u,l,r);
		int mid=l+((r-l)>>1);
		int res=findR(u<<1,l,mid,x,p,lsum);
		return max(res,findR(u<<1|1,mid+1,r,x,p,lsum));
	}
}tr;
int n;
void slv(int _csid,int _csi){
	tr.bld(1,1,NN);
	scanf("%d",&n);
	rep(_,1,n){
		int x;
		ll y;
		scanf("%d %lld",&x,&y);
		y=max(y-tr.Qsz(1,1,NN,1,x),0ll);
		if(x!=NN){
			ll p=min(y,tr.Qsz(1,1,NN,x+1,NN)),lsum=0;
			int res=tr.findR(1,1,NN,x,p,lsum);
			p-=tr.Qsz(1,1,NN,x+1,res)-tr.Qsz(1,1,NN,res,res)*(res-x);
			tr.upd(1,1,NN,x+1,res,tr.Qsz(1,1,NN,res,res));
			if(p){
				tr.upd(1,1,NN,x+1,res,tr.Qsz(1,1,NN,res,res)-p/(res-x));
				if(p%(res-x))tr.upd(1,1,NN,res-p%(res-x)+1,res,tr.Qsz(1,1,NN,res,res)-1);
			}
		}
		{
			ll p=y,rsum=0;
			int res=tr.findL(1,1,NN,x,p,rsum);
			p-=tr.Qsz(1,1,NN,res,res)*(x-res+1)-tr.Qsz(1,1,NN,res,x);
			tr.upd(1,1,NN,res,x,tr.Qsz(1,1,NN,res,res));
			if(p){
				tr.upd(1,1,NN,res,x,tr.Qsz(1,1,NN,res,res)+p/(x-res+1));
				if(p%(x-res+1))tr.upd(1,1,NN,res,res+p%(x-res+1)-1,tr.Qsz(1,1,NN,res,res)+1);
			}
		}
		printf("%lld\n",tr.tr[1].sum);
	}
}
void main(){
	int T=1,csid=0;
//	scanf("%d",&csid);
//	scanf("%d",&T);
	rep(i,1,T)slv(csid,i);
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Nelofus (赞：0)

首先对每个区间，一定尽可能把数平摊。

不难发现如果 $m_i\le m_j$ 且 $b_i\ge b_j$ ，$j$ 就没用了。

更进一步地说，若有三个点 $i,j,k$ 满足 $m_i<m_j<m_j$，且
$$
\dfrac{(B_j-B_i)}{m_j-m_i}<\dfrac{(B_k-B_i)}{m_k-m_i}
$$
那么 $j$ 就没用了，因为直接把 $B_k-B_i$ 摊到 $(i,k]$ 里，多余的从前往后放，$j$ 的限制就自然满足了。

把有用的部分画出来显然是一个左上凸壳，`std::set` 维护即可。

```cpp
#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 2e5 + 10;
constexpr int mod = 1e9 + 7;
constexpr i64 inf = 1e12;
std::set<std::pair<int, i64>> st;
int ans = 0;
int n;
int M[N];
i64 B[N];

inline int f_pow(int a, i64 k) {
	if (k < 0)
		return 0;
	int base = 1;
	for (; k; k >>= 1, a = 1ll * a * a % mod)
		if (k & 1)
			base = 1ll * base * a % mod;
	return base;
}
inline int Plus(const int &x, const int &y) {
	return x + y >= mod ? x + y - mod : x + y;
}
inline int Minu(const int &x, const int &y) {
	return x - y < 0 ? x - y + mod : x - y;
}

#define x first
#define y second
inline std::pair<int, i64> trans(std::pair<int, i64> A, std::pair<int, i64> B) {
	return std::make_pair(B.x - A.x, B.y - A.y);
}
inline i64 Cross(const std::pair<int, i64> &A, const std::pair<int, i64> &B) {
	return 1ll * A.x * B.y - 1ll * A.y * B.x;
}

inline int Calc(const int &len, const i64 &cnt) {
	int p = cnt % len;
	int res = 0;
	res = Plus(res, 1ll * p * f_pow(3, (cnt - 1) / len + 1 - 1) % mod);
	res = Plus(res, 1ll * (len - p) * f_pow(3, cnt / len - 1) % mod);
	return res;
}

std::set<std::pair<int, i64>>::iterator delete_p(std::set<std::pair<int, i64>>::iterator it, int rt) {
	auto itp = std::prev(it);
	auto itn = std::next(it);

	auto prv = *itp;
	auto point = *it;
	ans = Minu(ans, Calc(point.x - prv.x, point.y - prv.y));
	if (itn != st.end()) {
		auto nxt = *itn;
		ans = Minu(ans, Calc(nxt.x - point.x, nxt.y - point.y));
		ans = Plus(ans, Calc(nxt.x - prv.x, nxt.y - prv.y));
	}
	st.erase(it);
	return rt ? itn : itp;
}

void insert_p(std::pair<int, i64> point) {
	auto itn = st.upper_bound({point.x, inf});
	auto itp = std::prev(itn);
	/* 天然满足 */
	if (itn != st.end()) {
		if (Cross(trans(*itp, *itn), trans(*itp, point)) <= 0)
			return ;
	} else {
		std::pair<int, i64> t = *itp;
		if (point.y <= t.y)
			return ;
	}

	/* 往前删点 */
	while (itp != st.begin()) {
		auto itf = std::prev(itp);
		if (Cross(trans(*itf, point), trans(*itf, *itp)) <= 0)
			itp = delete_p(itp, 0);
		else
			break;
	}
	/* 往后删点 */
	while (itn != st.end()) {
		auto itb = std::next(itn);
		if (itb == st.end()) {
			/* 检验一下还能不能插入 */
			auto prv = *itp;
			auto nxt = *itn;
			if (Cross(trans(prv, nxt), trans(prv, point)) <= 0)
				return ;
			/* 或者是后面的不用留了 */
			else if (nxt.y <= point.y)
				itn = delete_p(itn, 1);
			break;
		}
		if (Cross(trans(point, *itb), trans(point, *itn)) <= 0)
			itn = delete_p(itn, 1);
		else
			break;
	}
	auto prv = *itp;
	ans = Plus(ans, Calc(point.x - prv.x, point.y - prv.y));
	if (itn != st.end()) {
		auto nxt = *itn;
		ans = Plus(ans, Calc(nxt.x - point.x, nxt.y - point.y));
		ans = Minu(ans, Calc(nxt.x - prv.x, nxt.y - prv.y));
	}
	st.insert(point);
}

int main() {
#ifdef HeratinoNelofus
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> M[i] >> B[i];
	st.insert({0, 0});
	for (int i = 1; i <= n; i++) {
		insert_p(std::make_pair(M[i], B[i]));
		std::cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Jsxts_ (赞：0)

贪心+模拟。

首先这个序列任何时候都递减。

加入一条限制，首先判断是否本来已经满足条件。之后，容易发现理想情况肯定是恰好满足限制，并将 $1\sim x$ 中的数尽量均分。我们称这样的分配方案为“变成这段和的平均分”。

那么由于之前可能有 $x'<x$ 的其它限制使得不能用上面的方案，并且仍然是尽量平均分最优，我们容易得到结论：我们会将一段以 $x$ 结尾的极长后缀修改为这一段和的平均分，并且不修改剩下的部分使得所有限制仍然合法并且 $1\sim x$ 的和恰好为 $y$。

那么做出这个修改还会影响 $x'>x$ 的其他限制（因为前缀和变大所以可以减小一些位置的数）。考虑将之前的所有限制的位置存下来（它们会将这个序列分成若干段）。由于还是要时刻满足序列递减，所以不难想到是往之后的每一段考虑：使这一段整体减若干次直到再减就不能使序列递减。这样之后，这一段就可以和往后的一段合并（也就是这个限制没有用了！）。当然，可以将数减小的前提肯定是前缀和不会比之前要小。

举个例子：
```
3
2 10
6 20
3 15
```

第一个限制使序列变为 `5 5`，第二个限制出现时，若没有第一个限制肯定是 `4 4 3 3 3 3` 最优，由于第一个限制只能变为 `5 5 3 3 2 2`。

第三个限制出现时，先将序列变为 `5 5 5 3 2 2`，但此时第二个限制对应前缀和已经 $>20$，所以可以将后面那一段 `3 2 2` 变为 `2 2 1`（也就是和为 $7$ 的平均分与和为 $5$ 的平均分）。

那么考虑维护这个过程。由于序列长度只有 $10^6$，可以直接用线段树维护这个序列，只需要支持区间推平区间求和。然后也同时维护一个 set 存所有有效限制对应的连续段（就是它所约束着的连续段），这里 set 只需要存区间以及区间和（因为区间内肯定是平均分最优）。第一个部分往前修改时，可以直接从 $x$ 的位置往前遍历 set 的每个连续段，遇到一个合法的段时（即将这段变成新的平均分后满足这段的限制时）就将其删除（限制弱于当前这个），否则就将所有被删除的区间合并为一个新的区间，标记为当前这个限制所约束的区间。

往后修改也只需在 set 上遍历即可，由于颜色段均摊复杂度为 $O(n\log n)$。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 5e18;
const int N = 1e6+1;
inline ll read() {
	ll s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n;
/*
用set维护每段区间：和、区间、贡献
每段内会平均分 
加入一段，首先往前找：
若这段求出来的平均数小于则加上

否则停止，删除扫到的区间，加入新区间。

然后会有一些多余贡献需要往后枚举区间

扫的时候：若可以往后合并，则合并，否则直接将区间和减掉对应数即可
*/
struct node {
	int l,r;
	ll s;
	bool operator < (const node &x) const {
		return l == x.l ? r < x.r : l < x.l;
	}
};
set<node> S;
typedef set<node>::iterator IT;
struct Seg {
	int l,r;
	ll s,tag;
}t[N * 4 + 10];
void build(int x,int l,int r) {
	t[x].l = l, t[x].r = r, t[x].tag = INF;
	if (l == r) return;
	int mid = l + r >> 1;
	build(x<<1,l,mid), build(x<<1|1,mid + 1,r);
}
void f(int x,ll s) {
	t[x].s = (t[x].r - t[x].l + 1ll) * s;
	t[x].tag = s;
}
void pushdown(int x) {
	if (t[x].tag != INF) f(x<<1,t[x].tag), f(x<<1|1,t[x].tag), t[x].tag = INF;
}
void pushup(int x) {
	t[x].s = t[x<<1].s + t[x<<1|1].s;
}
void modify(int x,int l,int r,ll s) {
	if (l > r) return;
	if (t[x].l >= l && r >= t[x].r) {
		f(x,s);
		return;
	}
	pushdown(x);
	int mid = t[x].l + t[x].r >> 1;
	if (mid >= l) modify(x<<1,l,r,s);
	if (mid < r) modify(x<<1|1,l,r,s);
	pushup(x);
}
ll query(int x,int l,int r) {
	if (l > r) return 0;
	if (t[x].l >= l && r >= t[x].r) {
		return t[x].s;
	}
	int mid = t[x].l + t[x].r >> 1;
	pushdown(x);
	ll res = 0;
	if (mid >= l) res = query(x<<1,l,r);
	if (mid < r) res += query(x<<1|1,l,r);
	return res;
}
const int mod = 1e9 + 7;
int qpow(int a,ll b) {
	if (b < 0) return 0;
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		b >>= 1, a = 1ll * a * a % mod;
	}
	return res;
}
int calc(int x,ll y) {
	if (!y) return 0;
	return (1ll * (x - y % x) * qpow(3,y / x - 1) + y % x * qpow(3,y / x)) % mod;
}
void upd(int l,int r,ll y) {
	int le = r - l + 1;
	modify(1,l,l + y % le - 1,y / le + 1);
	modify(1,l + y % le,r,y / le);
}
int main() {
	n = read();
	int ans = 0;
	S.insert({-1,0,INF}), S.insert({N + 1,N + 1,0});
	S.insert({1,N,0});
	build(1,1,N);
	for (int i = 1;i <= n;i ++ ) {
		int x = read();
		ll y = read(),sum = query(1,1,x);
		if (sum >= y) {
			printf("%d\n",ans);
			continue;
		}
		auto t = --S.lower_bound({x + 1,-1,0ll});
		int l = t -> l,r = t -> r;
		ll ts = t -> s,lv = t -> s / (t -> r - t -> l + 1);
		ans = (ans - calc(r - l + 1,ts) + mod) % mod;
		S.erase(t);
		ll nv = ts - (x - l + 1ll) * lv - min(x - l + 1ll,ts % (r - l + 1));
		if (x != r) S.insert({x + 1,r,nv}), ans = (ans + calc(r - x,nv)) % mod;
		while (1) {
			t = --S.lower_bound({x + 1,-1,0ll});
			if (t -> r == 0) {
				S.insert({1,x,y});
				ans = (ans + calc(x,y)) % mod;
				upd(1,x,y);
				break;
			}
			ll tt = query(1,1,t -> l - 1),vv = y - tt;
			ll lv2 = vv / (x - t -> l + 1);
			if (t -> s > (t -> r - t -> l + 1) * lv2 + min(t -> r - t -> l + 1ll,vv % (x - t -> l + 1))) {
				vv -= t -> s;
				ans = (ans + calc(x - t -> r,vv)) % mod;
				S.insert({t -> r + 1,x,vv});
				upd(t -> r + 1,x,vv);
				break;
			}
			ans = (ans - calc(t -> r - t -> l + 1,t -> s) + mod) % mod;
			S.erase(t);
		}
		ll rest = query(1,1,x) - sum;
		while (rest) {
			t = S.lower_bound({x + 1,-1,0});
			if (t -> r == N + 1) {
				upd(x + 1,N,0);
				S.insert({x + 1,N,0});
				break;
			}
			auto t2 = t;t2 ++;
			ll lv = t -> s / (t -> r - t -> l + 1);
			ll lv2 = (t2 -> s + t2 -> r - t2 -> l) / (t2 -> r - t2 -> l + 1);
			ll all = (t -> r - t -> l + 1ll) * (lv - lv2) + t -> s % (t -> r - t -> l + 1);
			if (rest >= all && t2 -> r != N + 1) {
				ll tv = t -> s + t2 -> s - all;
				int l = t -> l,r = t2 -> r;
				ans = (ans - calc(t -> r - t -> l + 1,t -> s) + mod) % mod;
				ans = (ans - calc(t2 -> r - t2 -> l + 1,t2 -> s) + mod) % mod;
				S.erase(t), S.erase(t2);
				ans = (ans + calc(r - l + 1,tv)) % mod;
				S.insert({l,r,tv});
				rest -= all;
				upd(l,r,tv);
			}
			else {
				ans = (ans - calc(t -> r - t -> l + 1,t -> s) + mod) % mod;
				int l = t -> l,r = t -> r;
				ll ts = max(0ll,t -> s - rest);
				S.erase(t);
				S.insert({l,r,ts}), ans = (ans + calc(r - l + 1,ts)) % mod;
				upd(l,r,ts);
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

