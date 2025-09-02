# オレンジグラフ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/mujin-pc-2016/tasks/mujin_pc_2016_c



# 题解

## 作者：rui_er (赞：0)

本文中点的编号从 $0$ 开始。

显然，题目中要求橙色的边构成极大的二分图。枚举二分图左右部分别有哪些点。特别地，钦定 $0$ 号点是左部点。将所有跨左右部的边染为橙色，如果所有点通过橙色的边连通，就得到了一组合法的解；如果不连通，显然可以将更多的边染成橙色，使得所有点连通。

```cpp
// Problem: C - オレンジグラフ
// Contest: AtCoder - MUJIN プログラミングチャレンジ Programming Challenge
// URL: https://atcoder.jp/contests/mujin-pc-2016/tasks/mujin_pc_2016_c
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 16;

int n, m;
vector<int> e[N];

struct Dsu {
    int fa[N];
    void init(int x) {rep(i, 0, x - 1) fa[i] = i;}
    int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if(x == y) return false;
        fa[x] = y;
        return true;
    }
}dsu;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int ans = 0;
    rep(S, 0, (1 << n) - 1) {
        if(S & 1) {
            dsu.init(n);
            int cnt = n;
            rep(u, 0, n - 1) {
                for(int v : e[u]) {
                    if(((S >> u) & 1) != ((S >> v) & 1)) {
                        cnt -= dsu.merge(u, v);
                    }
                }
            }
            if(cnt == 1) ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：LinkWish (赞：0)

一个没有奇环的图就是一个二分图，这是显而易见的。

注意到这个性质后我们枚举每一个点属于哪一个点集，然后连接跨越两个点集的边，判一下图连不连通，如果不连通肯定可以继续加边而且不会形成奇环，如果连同就贡献一次答案。由于我们在枚举时会枚举到两次等价的情况，所以最后的答案要除以二。

注意，由于题目要求，输出时要换行。

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace _Fast_IO{
	char ch;
	int _stack[55],top,sign;
	template<typename _T>inline void read(_T &x){
		ch=getchar(),sign=1;
		for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')sign=-1;
		for(x=0;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
		x*=sign;
	}
	template<typename _T>inline void write(_T x){
		sign=top=0;
		if(x<0)sign=1,x=-x;
		if(!x)_stack[++top]=0;
		while(x){
			_stack[++top]=x%10;
			x/=10;
		}
		if(sign)putchar('-');
		while(top)putchar(_stack[top--]+48);
	}
}
using namespace _Fast_IO;
int n,m,ans;
struct T{int x,y;}e[125];
bool is[20][20],vis[20];
void dfs(int x){
	vis[x]=1;
	for(int i=1;i<=n;i++)
		if(is[x][i]&&!vis[i])dfs(i);
}
signed main(){
	read(n),read(m);
	for(int i=1;i<=m;i++)read(e[i].x),read(e[i].y);
	for(int i=0;i<(1<<n);i++){
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				is[j][k]=0;
		for(int j=1;j<=m;j++)
			if((bool)(i&(1<<(e[j].x-1)))!=(bool)(i&(1<<(e[j].y-1))))
				is[e[j].x][e[j].y]=is[e[j].y][e[j].x]=1;
		for(int j=1;j<=n;j++)vis[j]=0;
		dfs(1);
		int flag=1;
		for(int j=1;j<=n;j++){
			if(!vis[j]){
				flag=0;
				break;
			}
		}
		if(flag)ans++;
	}
	write(ans/2),puts("");
	return 0;
}
```


---

