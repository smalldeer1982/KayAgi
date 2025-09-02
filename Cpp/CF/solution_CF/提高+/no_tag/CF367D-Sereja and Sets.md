# Sereja and Sets

## 题目描述

Sereja has $ m $ non-empty sets of integers $ A_{1},A_{2},...,A_{m} $ . What a lucky coincidence! The given sets are a partition of the set of all integers from 1 to $ n $ . In other words, for any integer $ v $ $ (1<=v<=n) $ there is exactly one set $ A_{t} $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF367D/3f8a940400a40d5f76505a83349ff53839519434.png). Also Sereja has integer $ d $ .

Sereja decided to choose some sets from the sets he has. Let's suppose that $ i_{1},i_{2},...,i_{k} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{k}<=m) $ are indexes of the chosen sets. Then let's define an array of integers $ b $ , sorted in ascending order, as a union of the chosen sets, that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF367D/99f78eca4a538d2f0ed7359631dcfed20f0ac14e.png). We'll represent the element with number $ j $ in this array (in ascending order) as $ b_{j} $ . Sereja considers his choice of sets correct, if the following conditions are met:

 $ b_{1}<=d; b_{i+1}-b_{i}<=d (1<=i&lt;|b|); n-d+1<=b_{|b|}. $ Sereja wants to know what is the minimum number of sets $ (k) $ that he can choose so that his choice will be correct. Help him with that.

## 样例 #1

### 输入

```
3 2 2
1 2
2 1 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 1 1
5 4 5 3 2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7 3 1
4 1 3 5 7
2 2 6
1 4
```

### 输出

```
3
```

# 题解

## 作者：ziyistudy (赞：4)

## 前言

>~~模拟赛看到这题，想了超久。~~
>
>首先 $m\leq 20$ 肯定是状压，可是第一眼看到的是单调队列或者什么，但都和状压联系不上，于是:

## 正言

我们考虑集合 $ans$ 为最后选择的/集合的编号/的集合（~~手动断句~~）。因为每 $d$ 个数都至少有一个被选择，则对于集合 $V=\left \{a_i,...,a_{i+d-1}  \right \}$，必然有 $V\bigcap ans \ne \emptyset $。否则相当于这连续 $d$ 个位置没有被选择，与题目矛盾。

显然相交根本不好做，不如考虑不相交。即若：$ V\bigcap ans = \emptyset $，则这个 $ans$ 是不合法的，需要排除。进一步地，应有 $ans \subseteq \complement V$（可以证明 $ans$ 大小不会超过 $\complement V$ 的大小）。

这样，我们可以对于每个集合 $V$，标记其 $\complement V$，当然因为 $ans$ 也可以是其子集，所以不妨用高维后缀和往前退一下即可。

由于 $m\leq 20$，我们状压 $V$。最后我们统计合法的 $ans$ 的 $1$ 的个数的最小值即可（代表选了多少个不同集合）。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=998244353;
// head
const int N=1e5+5,M=22;
int col[N];
int sum[M];
bool flag[1<<M];
signed main() 
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n,m,d;cin>>n>>m>>d;
    for(int i=0;i<m;i++){
        int s;cin>>s;
        for(int j=0;j<s;j++) {int tmp;cin>>tmp;--tmp;col[tmp]=i;}
    }
    for(int i=0;i<d-1;i++) sum[col[i]]++;
    for(int i=d-1;i<n;i++){
        sum[col[i]]++;
        int now=0;
        for(int j=0;j<m;j++){
            if(!sum[j]) now|=(1<<j);
        }
        flag[now]=1;
        sum[col[i-d+1]]--;
    }
    int ans=1e9;
    for(int i=(1<<m)-1;i>=0;i--) {
        if(flag[i]) {
            for(int j=0;j<m;j++) if(i&(1<<j)) flag[i^(1<<j)]=1;
        }
    }
    for(int i=(1<<m)-1;i>=0;i--){
        if(!flag[i]){
            ans=min(ans,(int)__builtin_popcount(i));
        }
    }
    cout<<ans<<endl;
}
```

---

## 作者：hhhua (赞：3)

每长度为 $d$ 的窗口至少要有一个数。求最少选的集合数。

正难则反。状态空间可枚举，我们可以不求合法方案最小值，而是把不合法方案标记，最后枚举合法的方案求最小值。

长度为 $d$ 的窗口没有数，一定不合法。我们可以把这个窗口内集合出现情况用**二进制**标记，假设为 $S$。则

$$U = 2^m - 1, \complement_US = false $$
$$\sum_{X\subset \complement_US} X = false$$
最后枚举状态空间，在合法状态中求最小。

如果暴力标记子集，复杂度过不去。类似**懒标记**思想，我们采用这种方法：最后枚举状态空间的时候，从大到小枚举，**自己不合法的就下放一层子集**，合法就更新答案。
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010, M = 22, INF = 0x3f3f3f3f;

int n, m, d;
int cnt[N];
int num[N];
bool st[1 << M];

int main()
{
    scanf("%d%d%d", &n, &m, &d);
    
    for (int i = 1; i <= m; i ++ )
    {
        int cnt;
        scanf("%d", &cnt);
        while (cnt -- )
        {
            int x;
            scanf("%d", &x);
            num[x] = i - 1; //标记，方便计数
        }
    }
    
;
    for (int i = 1; i <= n; i ++ )
    {
        if (i < d) cnt[num[i]] ++ ; //统计当前区间个数
        else
        {
            if (i > d) cnt[num[i - d]] -- ; //维护滑动窗口
            cnt[num[i]] ++ ;
            
            //标记不合法的最大状态
            int state = 0;
            for (int j = 0; j < m; j ++ )
                if (!cnt[j]) state += (1 << j);
            st[state] = true;
        }
    }
    int res = INF;
    for (int state = (1 << m) - 1; ~state; state -- )
    {
        if (st[state]) //不合法，标记子集
        {
            for (int j = 0; j < m; j ++ )
                if (state >> j & 1) st[state ^ (1 << j)] = true;
        }
        else
        {
            int count = 0;
            for (int j = 0; j < m; j ++ ) count += (state >> j & 1);
            res = min(res, count);
        }
    }
    
    printf("%lld\n", res);
    return 0;
}
```

---

## 作者：xxseven (赞：3)

看到数据范围 $m \le 20$，考虑状压。但是直接状压 DP 的话找不到好的转移，要思考其他方法。

发现限制条件是每相邻两个数之间的差不能超过 $d$，离头尾的距离也不能超过 $d$。  
很复杂是不是？可以将其转化为另一个等价条件：每连续的 $d$ 个数中至少选 $1$ 个数。

接下来的做法就比较好想：对于每连续的 $d$ 个数，找到全部包含这些数的集合，那么这些集合之间至少要选出 $1$ 个，这些集合的补集和其子集 $1$ 个都没有选出，直接标记为非法。最后在没有标记为非法的集合中找 $\operatorname{popcount}$ 最小的那个即可。

对于子集的标记可以先对最大的集合打上标记，之后倒序下传即可避免重复标记，还可以用[子集枚举](https://oi-wiki.org/math/binary-set/#%E5%AD%90%E9%9B%86%E9%81%8D%E5%8E%86)技巧优化。

下面贴代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;
const int N=1e5+6;
int n,m,d,id[N],f[1<<20],buck[N],now,ans=1e9;
int cnt(int x){ //计算popcount
	int res=0;
	while(x){
		x-=lowbit(x);
		res++;
	}
	return res;
}
int main(){
	cin>>n>>m>>d; int U=(1<<m)-1; //U为全集
	for(int x,i=1;i<=m;++i){
		cin>>x; 
		for(int y,j=1;j<=x;++j){
			cin>>y;
			id[y]=i;
		}
	}
	for(int i=1;i<=n;++i){
		if(i>d) {
			buck[id[i-d]]--;//开桶记录出现次数，为0则删去
			if(!buck[id[i-d]]) now&=(U-(1<<id[i-d]-1));
		}
		buck[id[i]]++;
		now|=(1<<id[i]-1);
		if(i<d) continue;
		f[now^U]=1;//标记补集
	}
	for(int i=U;i>=1;--i){
		if(f[i]==1) for(int j=i;j;j=(j-1)&i){
			f[j]=2;//标记为2，避免遍历到这个子集时再次遍历下传
		}
		else if(!f[i]) ans=min(ans,cnt(i));
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：hater (赞：3)

一个比较妙的题 

把一段长度为 d 的区间 所出现过的数 

当成一个集合 

那么答案不可能是 这个集合的补集及其子集 

这样的话就没有一个数在其区间内 

那我们可以考虑在 补集打标记 

每一次遍历到的时候 下放他的子集 

所以这个题就做完了

最后注意遍历的顺续  

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
using namespace std ; 
const int N = 1e5+10 , _S = (1<<21) ; 
int n , d , ans = 20 , S , m , a[N] , t[25] ;   
bool mp[_S] ; 
int low( int x ) { return x&(-x) ; } 
int cnt( int x ) { 
  int tot = 0 ;
  for( ; x ; x-=low(x) ) tot ++ ; 
  return tot ; 
} 
void cov( int x ) { 
  int p = x ; 
  while( x ) { 
    mp[p^low(x)] = 1 ; 
    x -= low(x) ; 
  } 
} 
signed main( ) { 
  scanf( "%d %d %d" , &n , &m , &d ) ; 
  S = (1<<m)-1 ; 
  fp( i , 1 , m ) { 
     int lx , x ; scanf( "%d" , &lx ) ; 
     fp( j , 1 , lx ) 
       scanf( "%d" , &x ) , a[x] = i-1 ;  
  }  
  int now_s = 0 ; 
  fp( i , 1 , n ) { 
    t[a[i]] ++ ; 
    if( t[a[i]] == 1 ) now_s += ( 1<<a[i] ) ; 
    if( i < d ) continue ;  
    mp[S^now_s] = 1 ; 
    t[a[i-d+1]] -- ; 
    if( t[a[i-d+1]] == 0 ) now_s -= ( 1<<a[i-d+1] ) ; 
  } 
  fq( j , 1 , S ) { 
       if( mp[j] ) cov( j ) ; 
	    else ans = min( ans , cnt(j) ) ;   
	}  
  printf( "%d\n" , ans ) ; 
  return 0 ; 
} 
```


---

## 作者：C_Pos_Princess (赞：0)

# 题解：CF367D Sereja and Sets

根据题意我们可以知道，在任意连续 $d$ 个数字中，必定至少选一个数字存在，否则就不满足题目条件。

那我们就在以 $d$ 为大小的数字区间中统计数字数量，把不满足当前区间的集合编号都或起来，记录一下此状态不可行，以此类推，这些状态的子集也不可行，所以我们选择高维前缀和枚举子集来维护。


**小细节**：高维前缀和中数组下标一般都**从零开始**，好处理。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5+10;
const int M = 22;
int col[N];
int sum[M];
bool flag[1<<M];
int n,m,d;


int main(){
	scanf("%d%d%d",&n,&m,&d);
	for(int i = 0;i<m;i++){
		int s;
		scanf("%d",&s);
		for(int j = 0;j<s;j++){
			int tmp;
			scanf("%d",&tmp);
			--tmp;
			col[tmp] = i;
		}
	}
	for(int i = 0;i<d-1;i++) sum[col[i]]++;
	for(int i = d-1;i<n;i++){
		sum[col[i]]++;
		int now = 0;
		for(int j =0;j<m;j++){
			if(!sum[j]) now|=(1<<j);
		}
		flag[now] = 1;
		sum[col[i-d+1]]--;
	}
	
	int ans = 1e9;
	for(int i = (1<<m)-1;i>=0;i--){
		if(flag[i]) {
			for(int j = 0;j<m;j++){
				if(i&(1<<j)) flag[i^(1<<j)] = 1;
			}
		}
	}
	for(int i = (1<<m)-1;i>=0;i--){
		if(!flag[i]) {
			ans = min(ans,(int)__builtin_popcount(i));
		}
	}
	printf("%d",ans);
	
	
	
	return 0;
}
```

附高维前缀和练习题：[Compatible Numbers](https://www.luogu.com.cn/problem/CF165E)。

---

## 作者：Drest (赞：0)

# [CF367D] Sereja and Sets 题解

[luogu](https://www.luogu.com.cn/problem/CF367D)
|
[CodeForces](https://codeforces.com/contest/367/problem/D)

## 解题思路

由题意可以得知，对于任意一个长度为 $d$ 的区间，都应该与所选集合相交。

我们设 $i$ 的**所属集合**（即哪个集合包含 $i$）为 $x_i$，那么对于集合 $x_i, x_{i+1},...,x_{i+d-1}$ 构成的集合（集合的集合），其**补集**一定不合法，其**补集的子集**一定也不合法。

于是我们可以遍历所有长度为 $d$ 的区间，将所有不合法的集合剔除，那么我们就得到了所有合法的集合，取长度最小的一个即可。

## 代码

```cpp

#include<bits/stdc++.h>
using namespace std;

const int N = 1 << 22;

int n, m, d; // 尼 马 德

int s[N], vis[25];

bool del[N];

signed main() {

    cin >> n >> m >> d;
  // input
    for (int i = 1; i <= m; i++) {
        int num;
        cin >> num;

        while (num--) {
            int x;
            cin >> x;
            s[x] = i;
        }
    }
  // 特判一下
    if (m == 1) {
        cout << 1;
        return 0;
    }

  // 先将前 d - 1 个加入
    for (int i = 1; i < d; i++) vis[s[i]]++;
    int l = 1, r = d;

  // 遍历长度为 d 的所有区间
    while (r <= n) {
        vis[s[r]]++;

        int st = 0;
        for (int i = 1; i <= m; i++) {
            if (vis[i]) st |= (1 << (i - 1));   // 目前选取的所有集合
        }
        del[((1 << m) - 1) ^ st] = true;  // 删除它的补集
      
        vis[s[l]]--;
        l++, r++;

    }
    int ans = m;
    for (int i = (1 << m) - 1; i > 0; i--) { // 需要从大到小遍历集合
        if (del[i]) {   // 删除补集的子集
            for (int j = 1; j <= m; j++) {  // 寻找其所有子集
                if (i & (1 << (j - 1)))  
                    del[i ^ (1 << (j - 1))] = true;
            }
        } else {
            ans = min(ans, __builtin_popcount(i));  // 否则合法，处理答案
        }
    }

    cout << ans;
    return 0;
}

````

---

## 作者：Targanzqq (赞：0)

### 一道经典的状压 dp。

我们考虑原题中的限制：$b_{i+1}-b_i\le d$，也就是说 $b_{i}+d\ge b_{i+1}$，就是说对于每个长度为 $d$ 的区间，里面一定有一个数被放进去了，也就是说如果有一个长度为 $d$ 的区间没有元素被放进去，他就是不合法的。

因此我们可以双指针维护一个长度为 $d$ 的区间，记录两个数据，一个是区间内每个元素所在的集合，另一个是区间内每个集合的出现次数。然后对于出现在区间里的集合，我们把他们的补集加进一个判定数组 $g$。对于 $g$ 和 $g$ 的子集都是不合法的。这部分时间复杂度为 $O(n)$。

接下来到了 dp 的部分。我们从大到小枚举一个集合组，对于当前集合组，如果它不合法，我们去掉其中的一个集合并令这个状态也不合法（如果去掉更多的集合也可以通过这种状态转移）。然后如果它合法，我们只要统计其中 $1$ 的个数即可。时间复杂度 $O(m2^m)$。总时间复杂度 $O(m2^m+n)$。

源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,d,k;//尼 玛 德
int a[100005],f[1<<20],g[1<<20],sz[21],cs[21],ans=LONG_LONG_MAX;

signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>d;
	for(int i=0;i<m;i++){
		cin>>sz[i];
		for(int j=1;j<=sz[i];j++){
			int k;cin>>k;
			a[k]=i;
		}
	}
	for(int i=1;i<=d;i++){
		k|=(1<<a[i]);cs[a[i]]++;
	}
	g[k^((1<<m)-1)]++;
	for(int i=d+1;i<=n;i++){
		//cout<<(k^((1<<m)-1))<<endl; 
		cs[a[i-d]]--;if(cs[a[i-d]]==0)k^=(1<<a[i-d]);
		k|=(1<<a[i]);cs[a[i]]++;
		g[k^((1<<m)-1)]++;
	}
	for(int i=(1<<m)-1;i>=1;i--){
		if(g[i]){
			for(int j=0;j<m;j++){
				if(i&(1<<j))g[i^(1<<j)]++;
			}
		}
		else{
			int res=0;
			for(int j=0;j<m;j++){
				if(i&(1<<j))res++;
			}
			ans=min(ans,res);
		}
	}
	cout<<ans;
}

```

---

