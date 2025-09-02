# [USACO14OPEN] Fair Photography G

## 题目描述

FJ 的 $N$ 头奶牛（$1 \leq N \leq 100,000$）站在一条长长的一维栅栏的不同位置。第 $i$ 头奶牛站在位置 $x_i$（范围为 0 到 1,000,000,000 的整数），其品种为 $b_i$（范围为 1 到 8 的整数）。没有两头奶牛占据相同的位置。

FJ 想为县集市拍摄一张连续区间的奶牛照片，但他希望所有的品种在照片中都能得到公平的代表。因此，他希望确保在照片中出现的任何品种数量都是相等的（例如，包含 27 头品种 1 和品种 3 的照片是可以的，包含 27 头品种 1、3 和 4 的照片也是可以的，但包含 9 头品种 1 和 10 头品种 3 的照片则不可以）。农夫约翰还希望照片中至少有 $K$（$K \geq 2$）个品种（总共 8 个品种）被代表。帮助 FJ 拍摄他的公平照片，找出满足 FJ 约束条件的最大照片大小。照片的大小是照片中奶牛的最大位置和最小位置之间的差。

如果没有满足 FJ 约束条件的照片，则输出 $-1$。

## 说明/提示

输入详情：

品种 id：1 2 3 - 1 1 2 3 1 - ... - 1

位置：1 2 3 4 5 6 7 8 9 10 ... 99 100

输出详情：

从 $x = 2$ 到 $x = 8$ 的范围内有 2 头品种 1、2 和 3。范围从 $x = 9$ 到 $x = 100$ 有 2 头品种 1，但这是无效的，因为 $K = 2$，所以我们必须至少有 2 个不同的品种。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
9 2
1 1
5 1
6 1
9 1
100 1
2 2
7 2
3 3
8 3```

### 输出

```
6```

# 题解

## 作者：401rk8 (赞：4)

模拟赛考到这题了，跟风 yspm 写篇题解

### 翻译
$n$ 头奶牛，每头奶牛有坐标 $x_i$ 和品种 $b_i$，一个区间合法当且仅当这个区间中至少出现了 $k$ 个品种的奶牛且出现品种的奶牛数都相等，求最长合法区间。

### sol
奶牛只有 $8$ 个品种，前缀和后可以在 $O(8)$ 的时间内判断出一个区间是否合法。（如果一个区间合法，那么它两个端点处的前缀和数组差分得到的差分表对应相等，注意这里的差分指的是各个品种出现次数之差，并非还原前缀和数组的差分）

考虑移动区间右端点时维护左端点的合法性。一个暴力的想法是对于每个右端点 $2^8$ 枚举出现过的品种，hash 表记录左端点。复杂度 $O(2^88n)$，不太行。

其实没有必要枚举 $2^8$ 枚举出现品种的集合，左端点从当前右端点向左移时只会出现 $8$ 种集合（每个品种出现了就不会消失），因此只需按每个品种最后一次出现的位置倒序加入当前集合并查询。  
右端点移动会改变这个品种上一次出现的位置到当前位置的出现品种集合，暴力修改即可。  
时间复杂度 $O(8^2n)$

### code
[省略的头文件](https://www.cnblogs.com/401rk8/p/about.html)
```cpp
const int N = 1e5+5;
int n,m;
PII a[N];

int ans=-1,lst[10],sum[N][10]; // lst记录每个品种上次出现的位置
PII tmp[10];
unordered_map<ULL,int> mp; // hash表

ULL hsh(int s,int i) { // hash函数
	int fi = 7; For(j,0,7) if( s & (1<<j) ) { fi = j; break; }
	ULL res = 0;
	For(j,fi+1,7) if( s & (1<<j) ) res = res * 997 + sum[i][j]-sum[i][fi];
	return res;
}

signed main() {
	read(n,m); --m;
	For(i,1,n) read(a[i].fi,a[i].se), --a[i].se; sort(a+1,a+n+1);
	For(i,1,n) {
		mp[0] = a[i].fi;
		For(j,0,7) sum[i][j] = sum[i-1][j]; ++sum[i][a[i].se];
		For(j,lst[a[i].se]+1,i) { // 暴力修改
			int s = 0; For(k,0,7) if( sum[i-1][k]-sum[j-1][k] ) s |= 1<<k;
			mp.erase(hsh(s,j-1)); // 删去原来状态
			s |= 1<<a[i].se; ULL h = hsh(s,j-1);
			if( !mp.count(h) ) mp[h] = a[j].fi; // 更新当前状态
		}
		lst[a[i].se] = i;
        // s为当前集合，tmp按每个品种最后一次出现的位置排序加入s
		For(j,0,7) tmp[j] = MP(lst[j],j); sort(tmp,tmp+8,greater<PII>());
		int s = 0; For(j,0,m-1) s |= 1 << tmp[j].se;
		for(int j = m; j < 8 && tmp[j].fi; ++j) {
			s |= 1 << tmp[j].se;
			ULL h = hsh(s,i);
			if( mp.count(h) ) ckmax(ans,a[i].fi-mp[h]);
		}
	}
	write(ans);
	return iocl();
}
```

---

## 作者：ZhongYuLin (赞：2)

考虑 $O(2^m)$ 枚举每一种集合，使得有且仅有集合中的品种的奶牛出现，且两两数量相等。考虑哈希，我们要构造一种哈希方式，使得能够将一组奶牛自然地消除。例如，$|S|=\left \{ 1,2 \right \} $ 时，我们要使得 ```1 1 2 ``` 与 ```1``` 等价。设集合中有 $N$ 个品种，这中的第 $i$ 种奶牛的哈希值为 $h_i$，构造积哈希，使得 $\prod_{i=1}^N h_i\equiv 1\pmod P$。容易想到对前 $N-1$ 个随机赋权，最后一个为它们积的逆元。维护每个哈希值最远的合法位置即可。


```cpp
#include<bits/stdc++.h>
#define se second
#define fi first
using namespace std;
using ull=unsigned long long;
using ll=long long;
using uc=short;
using pii=pair<int,int>;
const int N=1e5+3,P=1e9+9;
struct Node{
    ull x,y;int id;
    friend bool operator<(Node x,Node y){
        return x.x==y.x?x.y<y.y:x.x<y.x;
    }
    friend bool operator==(Node x,Node y){
        return x.x==y.x&&x.y==y.y;
    }
}b[N];
ull fp(ull a,ull b=P-2){ull ans=1;for(;b;b>>=1,a=a*a%P)if(b&1)ans=ans*a%P;return ans;}
void ckmx(int &x,int y){if(x<y)x=y;}
mt19937_64 rg(random_device{}());
int n,m,len,K;
pii a[N];
int ans[N],id[N],mx[N];
ull W1[8],W2[8],h1[N],h2[N];
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>K;m=8;
    for(int i=1;i<=n;++i)cin>>a[i].fi>>a[i].se,--a[i].se;
    sort(a+1,a+1+n);a[0].fi=-5e8;
    for(int i=0;i<m;++i)W1[i]=rg()%P,W2[i]=rg()%P;
    h1[0]=h2[0]=1;int ans=-1;
    for(uc s=1;s<1<<m;++s){
        if(__builtin_popcount(s)<K)continue;
        vector<uc>tmp;
        for(int i=0;i<m;++i)
            if(s&1<<i)tmp.push_back(i);
        int len=tmp.size();
        ull val1[m],val2[m],k1=1,k2=1;
        copy(W1,W1+m,val1);copy(W2,W2+m,val2);
        for(int i=0;i<len-1;++i)k1=k1*val1[tmp[i]]%P,k2=k2*val2[tmp[i]]%P;
        val1[tmp.back()]=fp(k1);val2[tmp.back()]=fp(k2);
        b[len=1]={1,1,0};
        for(int i=1;i<=n;++i){
            h1[i]=h1[i-1];h2[i]=h2[i-1];
            if(s&1<<a[i].se){
                h1[i]=h1[i]*val1[a[i].se]%P;
                h2[i]=h2[i]*val2[a[i].se]%P;
            }
            b[++len]={h1[i],h2[i],i};
        }
        sort(b+1,b+1+len);
        memset(mx,0,sizeof(mx));
        int now=1;id[b[0].id]=1;
        for(int i=1;i<=len;++i){
            if(b[i]==b[i-1])id[b[i].id]=now;
            else id[b[i].id]=++now;
        }
        int R=0,cnt[m];
        for(int i=1;i<=n;++i){
            if(R<i)R=i,fill(cnt,cnt+m,0);
            for(;R<=n&&(s&1<<a[R].se);++R){
                ckmx(mx[id[R]],R);
                ++cnt[a[R].se];
            }
            for(int i=0;i<m;++i)
                if((s&1<<i)&&!cnt[i])
                    goto end;
            ckmx(ans,a[mx[id[i-1]]].fi-a[i].fi);
            end:;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Piggy343288 (赞：0)

显然这道题的解法与 $8$ 强相关。从这一点下手，我们不难想到先对每一种奶牛做前缀和，这样我们可以做到 $O(8)$ 查询每个区间是否可行，从而有了一个 $O(4n^2)$ 的纯暴力做法。不知道多少 pts，反正不是正解。  
下一步我们考虑优化。如果我们能快速地找到哪些区间是合法的，那么时间复杂度显然会大大降低。那么我们考虑对每个点编码，要同时把两个目的压缩在一个编码函数中，即每种奶牛出现的次数和出现的奶牛种类。我们不难写出下面的编码：  
```cpp
ull myEncode(int encoder, int i) {
    int first = 0;
    for (; first <= 7; first++)
        if (encoder & (1 << first)) {
            break;
        }
    ull ret = 0;
    for (int j = first + 1; j <= 7; j++)
        if (encoder & (1 << j))
            ret = (ret * 1001) + sum[i][j] - sum[i][first];
    return ret;
}
``` 
其中，$encoder$ 状压的表示了哪些奶牛种类出现了，而 $i$ 就是我们要编码的点。不难发现，如果两个点的前缀和之差（这里是八个颜色分别做差）相等，且选取的奶牛种类相等，那么编码值也相等。  

接下来考虑每次加入一个端点怎么快速查询。先考虑从右端点，从右向左的加入端点，每次检查；同时考虑枚举所有出现奶牛的集合，并查编码值。这两种一个是 $O(n^2)$ 的，一个是 $O(2^8n)$ 的，都不优。我们把它们结合起来，可以从右向左依次加入某个颜色最后一个出现的位置，可以证明颜色出现的集合其变化不会超过八次。每次加入的时候强制选择这头奶牛，然后对此时的编码进行查询，若查询到就更新答案。  
最后还有一个小问题：怎么修改。答案是直接暴力枚举端点然后暴力修改即可。时间复杂度可以接受。  
代码是比较好写的，就不放了。核心的编码已经给出，如果你总是 WA，不妨考虑你的编码是否正确。

---

## 作者：Genius_Star (赞：0)

[或许更好的阅读体验。](https://www.cnblogs.com/rgw2010/p/18444952)

模拟赛题，场切了，来写一篇题解。

### 思路：

注意一下模拟赛题需要求出每一种颜色集合的最大答案，而本题主只需要求出颜色数量大于 $\ge K$ 的答案。

先考虑将所有牛按照位置排序。

然后考虑暴力枚举颜色的出现集合 $[1,2^m)$，本题中只需要枚举二进制中 $1$ 数量 $\ge k$ 的集合即可，设为 $S$。

之后求出所有颜色在 $S$ 中的最长连续段：$[l_1,r_1],[l_2,r_2],\cdots,[l_k,r_k]$，需要对于每个连续段 $[l_i,r_i]$ 找到一个最长的子区间 $[l',r']$ 使得每种颜色出现的次数相同且 $a_{r'}-a_{l'}$ 的值最大。

考虑使用前缀和 $s_{x,y}$ 表示 $[l_i,x]$ 中颜色 $y$ 出现的次数，则若 $[l',r']$ 可以使得所有颜色的出现次数相等显然当且仅当对于所有的 $x$ 满足 $s_{r',x} - s_{l'-1,x} = k$，其中 $k$ 为定值。

可以枚举 $k$ 去找符合条件的 $l'$，但是复杂度不优，考虑到有 $s_{l'-1,x} = s_{r',x} - k$，则有：

$$s_{l'-1,x+1} - s_{l'-1,x} = (s_{r',x+1} -k) - (s_{r',x} - k) = s_{r',x+1} - s_{r',x}$$

即 $s_{r'}$ 与 $s_{l'-1}$ 的差分数组是相同的即可，故可以使用哈希或者 `map` 存储这个差分数组，这样就可以对于每个 $r'$ 快速找到距离最远的 $l'$ 满足要求。

使用 `map` 的时间复杂度为 $O(2^M N M)$，使用哈希的可以少一个 $M$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const ll N=1e5+10,M=10; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	int x;
	int col;
	inline bool operator<(const Node&rhs)const{
		return x<rhs.x;
	}
}a[N];
int n,m,cnt;
int id[N];
vector<int> t;
map<vector<int>,int> F;
inline int get(int l,int r){
	if(l>r)
	  return -1;
	if(cnt==1)
	  return a[r].x-a[l].x;
	int ans=-1;
	F.clear(),t.clear();
	t.resize(cnt-1);
	F[t]=l;
	For(i,l,r){
		if(id[a[i].col])
		  t[id[a[i].col]-1]++;
		if(id[a[i].col]!=cnt-1)
		  t[id[a[i].col]]--;
		if(F.count(t))
		  ans=max(ans,a[i].x-a[F[t]].x);
		else
		  F[t]=i+1;
	}
	return ans;
}
inline int work(int S){
	int ans=-1,sum=0;
	cnt=0;
	For(i,0,7){
	    if((S>>i)&1ll)
		  id[i]=cnt++;
		else
		  id[i]=-1;
	}
	if(cnt<m)
	  return -1;
	For(i,1,n){
		if((S>>a[i].col)&1ll)
		  sum++;
		else{
			ans=max(ans,get(i-sum,i-1));
			sum=0;
		}
	}
	ans=max(ans,get(n-sum+1,n));
	return ans;
}
int main(){
//	open("ptb.in","ptb.out");
	n=read(),m=read();
	For(i,1,n){
		a[i].x=read();
		a[i].col=read()-1;
	}
	t.resize(10);
	sort(a+1,a+n+1);
	if(m==1){
		write(a[n].x-a[1].x);
		putchar('\n');
		exit(0);
	}
	int ans=-1;
	For(S,1,(1ll<<8)-1)
	  ans=max(ans,work(S));
	write(ans);
	return 0;
}
```

---

