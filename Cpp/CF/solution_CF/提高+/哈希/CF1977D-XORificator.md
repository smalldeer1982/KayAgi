# XORificator

## 题目描述

You are given a binary (consisting only of 0s and 1s) $ n \times m $ matrix. You are also given a XORificator, using which you can invert all the values in a chosen row (i.e. replace 0 with 1 and 1 with 0).

A column in the matrix is considered special if it contains exactly one 1. Your task is to find the maximum number of columns that can be made special at the same time, and the set of rows the XORificator should be used on to achieve that.

## 说明/提示

In the first test case, you can use the XORificator on the second row to make the columns $ 2 $ , $ 3 $ , and $ 4 $ special.

In the second test case, the only column is already special, so you don't need to use the XORificator.

## 样例 #1

### 输入

```
5
3 4
1010
0110
0100
1 1
1
1 1
0
2 5
00101
10110
3 3
101
111
000```

### 输出

```
3
010
1
0
1
1
3
00
2
010```

# 题解

## 作者：masonpop (赞：7)

这个题整体做显然没法做。于是局部考虑，如果**固定 $(i,j)$ 是该列唯一的 $1$** 怎么做。此时发现，所有行的状态全部固定了。因此，答案至少为 $1$ 的有效状态只有 $O(nm)$ 种。

考虑具体实现。枚举列，然后在 $i$ 的变化中，可以 $O(1)$ 维护状态的变化，注意到对于最优状态，**出现次数一定最多**。因此把状态哈希一下，取最多的就行。

输出方案就记录一下位置即可。[代码](https://codeforces.com/contest/1977/submission/262943486)。

---

## 作者：phigy (赞：6)

考虑当我们确定 $(i,j)$ 是 $1$ 而第 $j$ 列的其它位置是 $0$ 时，我们就可以确定翻转的哪些行。

考虑到同一列确定的 $1$ 的位置不同，翻转的哪些行也一定不完全相同，因此我们只需要枚举 $(i,j)$，确定 $(i,j)$ 是 $1$ 而第 $j$ 列的其它位置是 $0$ 后，将此时对应的翻转的行的答案 $+1$ 即可。

我们可以通过将每一位映射到一个随机数上做异或，实现这个集合哈希，具体的我们对每行全是 $0$ 时候的翻转行做前后缀，然后就可以快速求出对应翻转行的哈希值了。

这样就做到了 $O(nm)$。

```cpp
#include <bits/stdc++.h>
 
#define REN (300000)
#define MAXN (REN+5)
 
using namespace std;
 
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int T;
int n,m;
string c;
inline int s(int x,int y) {return c[(x-1)*m+y-1]-'0';}
unsigned long long hsh[MAXN];
unsigned long long pre[MAXN],suf[MAXN];
unordered_map<unsigned long long,int>mp_num,mp_i,mp_j;
 
signed main()
{
    int i,j,k;
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;
    for(i=1;i<=REN;i++) {hsh[i]=rnd();}
    while(T--)
    {
        cin>>n>>m;
        for(i=0;i<=n+1;i++) {pre[i]=suf[i]=0;} mp_num.clear();mp_i.clear();mp_j.clear();c.clear();
        for(i=1;i<=n;i++) 
        {
            string tmp;
            cin>>tmp;
            for(char pp:tmp) {c.push_back(pp);}    
        }
        for(j=1;j<=m;j++)
        {
            for(i=1;i<=n;i++) {pre[i]=pre[i-1]^(hsh[i]*s(i,j));}
            for(i=n;i>=1;i--) {suf[i]=suf[i+1]^(hsh[i]*s(i,j));}
            for(i=1;i<=n;i++)
            {
                unsigned long long now=pre[i-1]^suf[i+1]^(hsh[i]*(1-s(i,j)));
                if(!mp_num.count(now)) {mp_i[now]=i;mp_j[now]=j;}
                mp_num[now]++;
            }
        }
        int rnum=-1,ri,rj;
        for(auto [hs,num]:mp_num) 
        {
            if(num>rnum) {rnum=num;ri=mp_i[hs];rj=mp_j[hs];}
        }
        cout<<rnum<<'\n';
        for(i=1;i<=n;i++) {cout<<(char)((i==ri)^(s(i,rj))+'0');} cout<<'\n';
    }
    return 0;
}
```

---

## 作者：Yc_cY (赞：4)

考虑枚举每一列，并且枚举哪一行上的数字是 $1$，共 $ n \times m $ 种状态，并且发现每一种状态出现的次数就是这种状态下满足条件列的个数，即答案（可以反过来想，在该状态下本列满足条件，那么这一种状态每出现一次就代表这种状态下满足条件的列多了一个），于是直接 map 统计，统计完再枚举一遍找答案，时间复杂度 $O( nm ) $。

code:

```cpp
#include<bits/stdc++.h>
#define For( i , a , b ) for( register int i = ( a ) ; i <= ( b ) ; ++i )
#define Rep( i , a , b ) for( register int i = ( a ) ; i >= ( b ) ; --i )
#define ull unsigned long long
using namespace std ;
const int N = 3e5 + 5 , p = 1331 ;
int T , n , ans , m , t[ N ] ;
ull cnt ;
char ch ;
vector < int > v[ N ] ;
map < ull , int > M ;
void add( ull tmp ) {
    if( M.count( tmp ) ) M[ tmp ] ++ , ans = max( M[ tmp ] , ans ) ;
    else M[ tmp ] = 1 ;
}
int main() {
    scanf("%d" , &T ) ;
    while( T-- ) {
        M.clear() ; ans = 1 ;
        scanf("%d%d" , &n , &m ) ;
        For( i , 1 , n ) v[ i ].clear() ;
        For( i , 1 , n ) For( j , 1 , m ) {
            ch = getchar() ; while( ch != '1' && ch != '0' ) ch = getchar() ;
            v[ i ].push_back( ch - '0' ) ;
        }
        For( j , 1 , m ) {
            For( i , 1 , n ) t[ i ] = v[ i ][ j - 1 ] ; cnt = 0 ;
            For( i , 1 , n ) cnt = cnt * p + t[ i ] ;
            ull res = 1 ;
            Rep( i , n , 1 ) {
                if( t[ i ] ) add( cnt - res ) ;
                else add( cnt + res ) ;
                res = res * p ;
            }
        }
        printf("%d\n" , ans ) ;
        bool flag = 0 ;
        For( j , 1 , m ) {
            For( i , 1 , n ) t[ i ] = v[ i ][ j - 1 ] ; cnt = 0 ;
            For( i , 1 , n ) cnt = cnt * p + t[ i ] ;
            ull res = 1 ;
            Rep( i , n , 1 ) {
                ull tp = cnt ;
                if( t[ i ] ) tp -= res ;
                else tp += res ;
                res = res * p ;
                if( !flag && M[ tp ] == ans ) {
                    For( k , 1 , n ) printf("%d" , t[ k ] ^ ( i == k ) ) ; printf("\n") ;
                    flag = 1 ; break ;
                }
            }
            if( flag == 1 ) break ;
        }
    }
    return 0 ;
}
```

---

## 作者：_Deer_Peach_ (赞：1)

学习哈希时的练习题，~~被卡了很长时间~~，发篇题解巩固一下。

题意：

给你一个 $n \times m $ 的二进制矩阵，可以任意次数反转任意一行，将这一行的 $1$ 改为 $0$，$0$ 改为 $1$，使矩阵中的特殊列尽可能多。

若一列只含有一个 $1$，则这列为特殊列。

思路：

直接枚举所有反转方案肯定不行，因为数据范围不允许。

所以我们可以对于每一列枚举每一行，通过反转后使该列该行 $1$，其余为 $0$，再用哈希表记录每种反转方案能使多少了成为特殊列，最后选择特殊列最多的方案。

最后可以使用双哈希来避免哈希冲突。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int N=3e5+5;
const int Mod1=1e9-71,Mod2=1e9+7;//两个质数
const int P=131;
struct node{
	int hash_1,hash_2;//双哈希
	bool operator<(const node x)const{
		return hash_1<x.hash_1||(hash_1==x.hash_1&&hash_2<x.hash_2);
	}
};
string s[N];//矩阵
int ppow1[N],ppow2[N];//哈希的幂次
signed main(){
	IOS;
	int t;
	cin>>t;
	while(t--){
		int n,m,res=0;
		cin>>n>>m;
		map<node,int>mp;//哈希表记录每种方案的特殊列的数量
		for(int i=1;i<=n;i++){
			cin>>s[i];
			s[i]=" "+s[i]; 
		}
		ppow1[0]=ppow2[0]=1;
		for(int i=1;i<=n;i++){//预处理哈希的幂次
			ppow1[i]=ppow1[i-1]*P%Mod1;
			ppow2[i]=ppow2[i-1]*P%Mod2;
		}
		for(int j=1;j<=m;j++){
			int hash_1=0,hash_2=0;
			for(int i=1;i<=n;i++){//计算使第j列全变为0的方案的哈希值
				hash_1=hash_1*P+s[i][j];
				hash_1%=Mod1;
				hash_2=hash_2*P+s[i][j];
				hash_2%=Mod2;			 
			}
			for(int i=1;i<=n;i++){//枚举每一行，计算使第i行为1的方案哈希值
				node Hash;
				Hash.hash_1=(hash_1+((s[i][j]^1)-s[i][j]+Mod1)*ppow1[n-i])%Mod1;
				Hash.hash_2=(hash_2+((s[i][j]^1)-s[i][j]+Mod2)*ppow2[n-i])%Mod2;
				mp[Hash]++;
				res=max(res,mp[Hash]);
			}
		}
		cout<<res<<endl;
		for(int j=1;j<=m;j++){//找对应的方案
			int hash_1=0,hash_2=0;
			for(int i=1;i<=n;i++){
				hash_1=hash_1*P+s[i][j];
				hash_1%=Mod1;
				hash_2=hash_2*P+s[i][j];
				hash_2%=Mod2;			 
			}
			bool flag=false;
			for(int i=1;i<=n;i++){
				node Hash;
				Hash.hash_1=(hash_1+((s[i][j]^1)-s[i][j]+Mod1)*ppow1[n-i])%Mod1;
				Hash.hash_2=(hash_2+((s[i][j]^1)-s[i][j]+Mod2)*ppow2[n-i])%Mod2;
				if(mp[Hash]==res){
					s[i][j]^=1;
					for(int k=1;k<=n;k++){
						cout<<s[k][j];
					}cout<<endl;
					flag=true;
					break;
				}
			}if(flag)break;
		}
	}

	return 0;
}
```
[提交记录](https://codeforces.com/problemset/submission/1977/311262060)。

---

## 作者：yshpdyt (赞：1)

## 题意
$n\times m$ 的 $01$ 矩阵，可以将任意行取反。

最大化只有一个位置为 $1$ 的列数，并输出任意取反方案。
## Sol
妙妙题，但被 `map` 和哈希坑掺了。

如果确定一个位置为 $1$，那么整个矩阵的取反情况都确定了。

考虑朴素的暴力方法，枚举每一个为 $1$ 的位置，遍历矩阵进行暴力统计答案，时间复杂度 $O(n^2m^2)$ 。

考虑优化，一种取反方法会有多个列满足条件，这几个列统计答案会遍历很多次矩阵，不妨将一个点变为 $1$ 的方案数与取反方案绑定，为该方案增加贡献，获得贡献最高的方案就是最优答案。

具体来说，有若干位置可以通过一种取反方案变成 $1$，这几个点一定不会位于同一列，使用该取反方案的答案就是点数，在枚举点数时，用桶记录点数，实时维护最大值，以及对应的方案即可。同一列不会算重吗？当然不会，一列只能有一个 $1$，所以一列上的各个位置对应取反方案一定不同。


接下来的问题就算如何构造桶了，不难想到用哈希代替一种方法，由于这是代码力量的比赛，记得至少要写双哈希。

具体实现可以看代码注释。

时间复杂度 $O(nm\log (nm))$。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ul unsigned long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll P4=131,xn4[N];
ll P5=97,xn5[N];
const ll mod2=1145141;//
const ll mod3=20080103;//质数生日！
ll st,ed;
struct Hash{
    ul x1,x2;
    ll x4,x5;
    //自然溢出日常被叉，所以多写了点。
    friend bool operator==(const Hash &a,const Hash &b){
        return a.x1==b.x1&&a.x2==b.x2&&a.x4==b.x4&&a.x5==b.x5;
    }   
    friend Hash operator+(const Hash &a,const Hash &b){
        return {a.x1+b.x1,a.x2^b.x2,(a.x4+b.x4)%mod2,(a.x5+b.x5)%mod3};
    }   
    friend Hash operator-(const Hash &a,const Hash &b){
        return {a.x1-b.x1,a.x2^b.x2,(a.x4-b.x4+mod2+mod2)%mod2,(a.x5-b.x5+mod3+mod3)%mod3};
    }   
    friend bool operator<(const Hash &a,const Hash &b){
        if(a.x1!=b.x1)return a.x1<b.x1;
        if(a.x2!=b.x2)return a.x2<b.x2;
        if(a.x4!=b.x4)return a.x4<b.x4;
        return a.x5<b.x5;
    }//用map的话，一定要明确所以大小关系，不然会导致元素混乱。
}h[N],res;
map<Hash,ll>mp;
string ans;
ll n,m;
void sol(){
    mp.clear();
    cin>>n>>m;
    res={0,0,-1,-1};
    string s="\n";//习惯下标从 1 开始，正常输出会 0 的位置，所以把0换成换行，后续就不需要换行；
    ans="\n";
    vector<string>v(n+2);//放置炸，用vector
    for(int i=1;i<=n;i++){
        s+='0';
        cin>>v[i];
        v[i]=" "+v[i];
    }
    mp[res]=-1;
    for(int j=1;j<=m;j++){
        Hash now={0,0,0,0};
        for(int i=1;i<=n;i++){
            s[i]='0';//先将该列所有位置翻转成0
            ///后续只需要每次更改一位即可。
            if(v[i][j]-'0'==1)now=now+h[i],s[i]='1';
        }
        for(int i=1;i<=n;i++){
            if(v[i][j]-'0'==0)now=now+h[i],s[i]='1';
            if(v[i][j]-'0'==1)now=now-h[i],s[i]='0';
            mp[now]++;
            if(mp[res]<mp[now]){//写等于会提埃奥义
                res=now;
                ans=s;
            }
            if(v[i][j]-'0'==0)now=now-h[i],s[i]='0';
            if(v[i][j]-'0'==1)now=now+h[i],s[i]='1';
        }
    }
    //由于ans[0] 是换行符，所以不需要换行。
    cout<<mp[res]<<ans<<endl;
}
int main(){
    st=clock();
    xn4[0]=xn5[0]=1;
    for(int i=1;i<=N-3;i++){
        xn4[i]=xn4[i-1]*P4%mod2;
        xn5[i]=xn5[i-1]*P5%mod3;
        ul x1=xn4[i]*xn5[i];
        ul x2=xn4[i]^xn5[i];
        h[i]={x1,x2,xn4[i],xn5[i]};
    }
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：0Io_oI0 (赞：0)

题目大概其实就是想让我们通过翻转某些行，使得尽可能多的列成为特殊列。

众所周知，暴力肯定是不行的，所以我们需要考虑优化！
 
对于每一列 $j$，枚举每一行 $i$，通过翻转某些行使得第 $j$ 列第 $i$ 行为 $1$，其余行为 $0$。

我们可以用哈希表记录每种翻转能够使多少列成为特殊列，最后选择最高的方案。

但h是，又众所周知哈希会出现哈希冲突所以我们还需要优化哈希！

我们用双哈希来存储翻转方案，来避免哈希冲突。并且可以预处理哈希值，这样可以更快！

总时间复杂度为 $O(nm\times \log (nm))$，轻松卡过本题数据。

**代码实现：**

还有不懂得看代码吧！ 

```cpp
#include<bits/stdc++.h>
#define I using
#define AK namespace
#define IOI std
#define i_ak return
#define ioi  0
#define i_will signed
#define ak main
#define IMO ()
#define int long long
I AK IOI;
const int N=3e5+5,P=13331,M1=1e9+7,M2=998244353;
string s[N];//存储矩阵的每一行
int p1[N],p2[N];
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>s[i];//输入矩阵的每一行
	//预处理哈希幂次
	p1[0]=p2[0]=1;
	for(int i=1;i<n;i++){
		p1[i]=1ll*p1[i-1]*P%M1;
		p2[i]=1ll*p2[i-1]*P%M2;
	}
	//哈希表，记录每种翻转方案的频率
	map<array<int,2>,int>mp;
	//枚举每一列 
	for(int j=0;j<m;j++){
		//计算使得第 j 列全部变成 0 的操作序列的哈希值
		int h1=0,h2=0;
		for(int i=0;i<n;i++){ 
			h1=(1ll*h1*P+s[i][j])%M1;
			h2=(1ll*h2*P+s[i][j])%M2;
		}
		//枚举每一行，计算使得第 j列的第 i 行为 1 的操作序列的哈希值
		for(int i=0;i<n;i++){
			array<int,2>t;
			t[0]=(h1+1ll*((s[i][j]^1)-s[i][j]+M1)*p1[n-1-i])%M1;
			t[1]=(h2+1ll*((s[i][j]^1)-s[i][j]+M2)*p2[n-1-i])%M2;
			mp[t]++;//更新哈希表的频率
		}
	}
	//找到最大频率
	int ret=0;
	for(auto&it:mp)ret=max(ret,it.second);
	cout<<ret<<'\n';//输出最大特殊列数
	//找到对应的翻转方案
	for(int j=0;j<m;j++){
		int h1=0,h2=0;
		for(int i=0;i<n;i++){
			h1=(1ll*h1*P+s[i][j])%M1;
			h2=(1ll*h2*P+s[i][j])%M2;
		}
		for(int i=0;i<n;i++){
			array<int,2>t;
			t[0]=(h1+1ll*((s[i][j]^1)-s[i][j]+M1)*p1[n-1-i])%M1;
			t[1]=(h2+1ll*((s[i][j]^1)-s[i][j]+M2)*p2[n-1-i])%M2;
			if(mp[t]==ret){//如果找到最大频率对应方案
				s[i][j]^=1;//翻转第 i 行
				for(int i=0;i<n;i++)cout<<s[i][j];//输出翻转方案
				puts("");
				return;
			}
		}
	}
}
i_will ak IMO{
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	i_ak ioi;
} 
```

亲测可过，请勿抄袭！

---

## 作者：Priestess_SLG (赞：0)

有一个性质是说：确定某一个位置为 $1$ 而其所在列的其余位置全部为 $0$，那么可以确定整个矩阵以及她的全部取反关系。因此可以直接暴力模拟，做到时间复杂度为 $O(n^2m^2)$。

然后考虑枚举确定的这个 $1$ 的位置。对于 $1$ 的位置从 $(i,j)$ 移动到 $(i+1,j)$ 的情况，只会有第 $i$ 行和第 $i+1$ 行的所有状态全部取反。然后又可以简单证明最优解肯定是在所有 $(i,j)$ 中出现次数最多的。因此考虑对答案哈希，且这个哈希需要满足可以快速切换某一行的状态。

可以设计一个类似于 Xor-Hash 的方法：把每一个坐标 $(i,j)$ 都映射到一个 $[0,2^{64})$ 内的随机整数，然后把她们的值异或起来就是答案。把答案扔到一个哈希表里求出现次数最多的数，可以做到 $O(\omega nm)$，其中 $\omega$ 视哈希表的优劣程度而不同，通常为常数级。这里为了方便使用了 `unordered_map` 代替（

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
mt19937_64 mt(time(0));
vector<vector<char>> mp;
const int N = 300010;
int pre[N], suf[N], Hash[N];
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        unordered_map<int, int> pp;
        unordered_map<int, pair<int, int>> xixi;
        mp.resize(n + 2);
        for (int i = 0; i <= n + 1; ++i) mp[i].resize(m + 2);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) cin >> mp[i][j];
        int mx = -1, ii = -1, jj = -1;
        for (int i = 1; i <= n; ++i) Hash[i] = mt();
        for (int j = 1; j <= m; ++j) {
            for (int i = 1; i <= n; ++i) {
                pre[i] = pre[i - 1];
                if (mp[i][j] == '1') pre[i] ^= Hash[i];
            }
            suf[n + 1] = 0;
            for (int i = n; i; --i) {
                suf[i] = suf[i + 1];
                if (mp[i][j] == '1') suf[i] ^= Hash[i];
            }
            vector<int> v;
            for (int i = 1; i <= n; ++i) {
                int now = pre[i - 1] ^ suf[i + 1];
                if (mp[i][j] == '0') now ^= Hash[i];
                ++pp[now], xixi[now] = {i, j};
                v.emplace_back(now);
            }
        }
        for (auto &[i, j] : pp)
            if (mx < j) {
                mx = j;
                ii = xixi[i].first;
                jj = xixi[i].second;
            }
        cout << mx << '\n';
        for (int i = 1; i <= n; ++i) {
            if (i == ii) {
                if (mp[i][jj] == '0') cout << "1";
                else cout << "0";
            } else {
                if (mp[i][jj] == '1') cout << "1";
                else cout << "0";
            }
        }
        cout << '\n';
    }
    return 0;
}

```

---

## 作者：lupengheyyds (赞：0)

# CF1977D XORificator

## 题意

给你一个二进制（仅由 $0$ 和 $1$ 组成）$n \times m$ 矩阵。你可以进行以下操作任意次：反转某一行中的所有值（即用 $1$ 替换 $0$，用 $0$ 替换 $1$）。

矩阵中的某一列如果只包含一个 $1$，则被视为特殊列。你的任务是找出最多有多少列可以同时被特殊化，以及为达到这一目的应在哪几行反转。

$1\le nm\le 3\times 10^5$

## 题解

我们发现，如果我们钦定第 $j$ 列的第 $i$ 行位置为 $1$，其他行位置为 $0$。会发现其实我们确定了整个矩阵。它的反转方式也是唯一确定的。

于是可以考虑枚举每一列，得到钦定某一个位置为 $1$ 时哪些行需要反转。

在最多列出现的反转方案就是答案。于是我们可以将一种反转方案哈希起来，放入 `map` 进行统计，这里我用的随机权值异或的哈希方法。

接着考虑如何 $\mathcal O(1)$ 求出反转方案的哈希值。

可以统计前后缀的哈希值，为 $1$ 视作反转，为 $0$ 视作不反转，一个位置为 $1$ 的反转方案应该为前后缀的反转方案加上这一位的相反状态。

于是我们就可以 $\mathcal O(nm)$ 的解决掉这道题。

---

## 作者：yyz1005 (赞：0)

# CF1977D XORificator 题解

题目大意：给定一个 $n \times m$ 的 $01$ 矩阵，可以选择若干行，将其行内每一个数取反，使得有尽可能多的列仅有一个 $1$，输出方案，$\sum nm \le 3 \cdot 10^5$。

注意到对于点 $(i,j)$ 处取到 $1$，其余第 $j$ 列的都为 $0$ 对应了一个固定的操作结果。

另外注意到答案一定在这 $n \cdot m $ 种结果中。

因此，考虑将每一个结果的操作抽象为一个类型，枚举每一个点对应的操作。

应当注意到同一列内操作的维护可以做到 $O(1)$ 移动。

本人的代码是将其变为一个 $131$ 进制数模大质数的形式存储。

代码比较复杂。

[Code](https://codeforces.com/contest/1977/submission/262968640)

---

## 作者：sbno333 (赞：0)

感觉 D<C 是显然的。

我们考虑已经确定了异或操作器，我们考虑答案。

此时需要拿操作器异或上我们的每一列。

我们考虑一列列处理，此时发现如果想让这一列产生贡献，总共有 $n$ 种答案符合条件。

我们假设把这一列变成 $0$，这显然唯一确定的操作器，即与本列相同，假设变成第 $i$ 行为 $1$，其它为 $0$，即原基础上第 $i$ 行异或 $1$，其它不变。

发现每列有 $n$ 种，共 $m$ 列，总共有 $nm$ 种。

可以给每个操作器投票，最后处理票数最高的。

但是生成器是 01 字符串啊，时间复杂度接受不了。

考虑哈希维护，为了确保万无一失，可以采用双哈希，为了防 hack，可以用 rand 实现哈希系数，让你自己都不知道哈希系数。

然后就好了，不过这里 $n,m$ 没有具体限制，建议以为数组存储。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>//双哈希
#define mod 998244353
map<pii,int> p;
bool s[300009];
int n,m;
int sc(int i,int j){//模拟二位数组
	return (i-1)*m+(j-1);
}
void _main(){
	p.clear();
	int x1,x2;
	x1=rand()%32768+114514;
	x2=rand()%32768+114514;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char t;
			cin>>t;
			t-='0';
			s[sc(i,j)]=t;
		} 
	} 
	for(int j=1;j<=m;j++){
		int h1,h2;
		h1=h2=0;
		int xx1,xx2;
		xx1=1,xx2=1;
		for(int i=1;i<=n;i++){
			h1+=s[sc(i,j)]*xx1;//哈希 1
			h2+=s[sc(i,j)]*xx2;//哈希 2
			h1%=mod;
			h2%=mod;
			xx1*=x1;
			xx2*=x2;
			xx1%=mod;
			xx2%=mod;
		}
		xx1=1,xx2=1;
		for(int i=1;i<=n;i++){
			h1-=s[sc(i,j)]*xx1;
			h2-=s[sc(i,j)]*xx2;
			h1+=mod,h2+=mod;
			h1%=mod;
			h2%=mod;
			s[sc(i,j)]=!s[sc(i,j)];//临时处理这一位取反，然后变回来
			h1+=s[sc(i,j)]*xx1;
			h2+=s[sc(i,j)]*xx2;
			h1%=mod;
			h2%=mod;
			p[{h1,h2}]++;
			h1-=s[sc(i,j)]*xx1;
			h2-=s[sc(i,j)]*xx2;
			h1+=mod,h2+=mod;
			h1%=mod;
			h2%=mod;
			s[sc(i,j)]=!s[sc(i,j)];
			h1+=s[sc(i,j)]*xx1;
			h2+=s[sc(i,j)]*xx2;
			h1%=mod;
			h2%=mod;
			xx1*=x1;
			xx2*=x2;
			xx1%=mod;
			xx2%=mod;
		}
	}
	int ma;
	ma=0;
	pii mas;
	mas={0,0};
	for(int j=1;j<=m;j++){
		int h1,h2;
		h1=h2=0;
		int xx1,xx2;
		xx1=1,xx2=1;
		for(int i=1;i<=n;i++){
			h1+=s[sc(i,j)]*xx1;
			h2+=s[sc(i,j)]*xx2;
			h1%=mod;
			h2%=mod;
			xx1*=x1;
			xx2*=x2;
			xx1%=mod;
			xx2%=mod;
		}
		xx1=1,xx2=1;
		for(int i=1;i<=n;i++){//重新跑一遍，枚举每一个票数不为 0 的答案
			h1-=s[sc(i,j)]*xx1;
			h2-=s[sc(i,j)]*xx2;
			h1+=mod,h2+=mod;
			h1%=mod;
			h2%=mod;
			s[sc(i,j)]=!s[sc(i,j)];
			h1+=s[sc(i,j)]*xx1;
			h2+=s[sc(i,j)]*xx2;
			h1%=mod;
			h2%=mod;
			if(p[{h1,h2}]>ma){
				ma=p[{h1,h2}];
				mas={j,i};
			}
			h1-=s[sc(i,j)]*xx1;
			h2-=s[sc(i,j)]*xx2;
			h1+=mod,h2+=mod;
			h1%=mod;
			h2%=mod;
			s[sc(i,j)]=!s[sc(i,j)];
			h1+=s[sc(i,j)]*xx1;
			h2+=s[sc(i,j)]*xx2;
			h1%=mod;
			h2%=mod;
			xx1*=x1;
			xx2*=x2;
			xx1%=mod;
			xx2%=mod;
		}
	}
	cout<<ma<<endl;
	s[sc(mas.second,mas.first)]=!s[sc(mas.second,mas.first)];
	for(int i=1;i<=n;i++){
		cout<<s[sc(i,mas.first)];
	}
	cout<<endl;
}
signed main(){
	srand(time(0));
	std::ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--){
		_main();
	} 
	return 0;
}
```

## 后记

这两场比赛是我的升紫局，写点题解纪念一下（发挥确实超长，比我平时预计多对一题），可能把 THUSC 和 APIO 的 rp 用这个上了，两场比赛怒斩 $272$ rating。

---

