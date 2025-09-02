# Intriguing Selection

## 题目描述

This is an interactive problem.

You are the head coach of a chess club. The club has $ 2n $ players, each player has some strength which can be represented by a number, and all those numbers are distinct. The strengths of the players are not known to you.

You need to select $ n $ players who would represent your club in the upcoming championship. Naturally, you want to select $ n $ players with the highest strengths.

You can organize matches between the players to do that. In every match, you pick two players, they play some games, and you learn which one of the two has higher strength. You can wait for the outcome of a match before deciding who will participate in the next one.

However, you do not want to know exactly how those $ n $ players compare between themselves, as that would make the championship itself less intriguing. More formally, you must reach a state where there is exactly one way to choose $ n $ players with the highest strengths that is consistent with the outcomes of the matches you organized, but there must be at least two possible orderings of those $ n $ players by strength that are consistent with the outcomes of the matches you organized.

## 说明/提示

In the example, the players in the first test case are sorted by strength in decreasing order. From the matches in the example output, we can deduce that players 1, 2, and 3 have the highest strength, but we do not know how the player 1 compares to the player 2.

## 样例 #1

### 输入

```
2
3

>

<

>

<

>

>

3

<

<

<

>

>```

### 输出

```


? 1 3

? 4 2

? 4 5

? 6 5

? 3 4

? 5 6

!

? 3 4

? 4 2

? 5 3

? 6 4

? 3 1

!
```

# 题解

## 作者：flyfeather☆ (赞：4)

题目中有两个要求，对于第一个随意暴力询问都可以解决。但同时却要求不能确定出完整的顺序。

考虑分开两个队列，两队列共 $n+1$ 个数，第一列 $\lfloor \frac{n+1}{2} \rfloor$ 个，第二列 $\lceil \frac{n+1}{2} \rceil$ 个，每列内降序排列。每次比较最末两个数的大小，淘汰较小的那个，随便从剩余数中取一个插入至该队列对应位置处，直到选出 $n$ 个。

这样保证了两队列各自有序但两队列间的关系不确定，满足题意。



```cpp
#include <bits/stdc++.h>
const int N=205;
int dp[N][N],a[N],b[N],n,T;
char s[5];
int qry(int x,int y){
	if (dp[x][y]!=-1) return dp[x][y];
	printf("? %d %d\n",x,y);
	fflush(stdout);
	scanf("%s",s);
	if (s[0]=='>') dp[x][y]=1;
	else dp[x][y]=0;
	dp[y][x]=dp[x][y]^1;
	return dp[x][y];
}
void Sort(int *a,int n){
	for (int i=1;i<n;i++){
		int mx=i;
		for (int j=i+1;j<=n;j++)
			if (qry(a[j],a[mx])) mx=j;
		std::swap(a[i],a[mx]);	
	}
}
void work(int *a,int n,int x){
	for (int i=n;i>=1;i--)
		if (qry(a[i],x)){
			for (int j=n;j>=i;j--)
				a[j+1]=a[j];
			a[i+1]=x;
			return;
		}
	for (int i=n;i>=1;i--) a[i+1]=a[i];
	a[1]=x;
	return;
}
void solve(){
	scanf("%d",&n);
	for (int i=1;i<=2*n;i++)
		for (int j=1;j<=2*n;j++)
			dp[i][j]=-1;
	int x=(n+1)/2,y=n+1-x;
	int cnt=n;
	for (int i=1;i<=x;i++) a[i]=i;
	for (int j=x+1;j<=x+y;j++) b[j-x]=j;
	Sort(a,x);
	Sort(b,y);
	for (int tim=1;tim<=n;tim++){
		int type=qry(a[x],b[y]);
		if (tim==n){
			puts("!");
			fflush(stdout);
			return;
		}
		if (type==0) work(a,x-1,n+tim+1);
		else work(b,y-1,n+tim+1);
	}
}
int main(){
	scanf("%d",&T);
	while (T--){
		solve();
	}
}
```



---

## 作者：ChiyuYuan (赞：3)

有一种很玄妙的做法，非常简洁。

我们考虑每两个为一组，令每对小的构成的集合为 $S$, 另一个为 $T$。

令 $S$ 里最大的下标为 $x$，和其一对的另一数的下标为 $y$。

容易发现 $y$ 一定在答案里。

proof：我们先钦定 $T$ 为答案，再进行替换，发现一定是有些 $T$ 中的数比有些 $S$ 中的小，被替换出来。但是 $y$ 一定比 $x$ 大，所以 $y$ 大于 $S$ 中所有数，不可能被替换。

那么我们只需要让其他数和 $y$ 的关系不被确定就行了。

我们考虑直接比较选出剩下的 $n-1$ 个数，但是我们知道了 $y$ 一定比 $x$ 大，如果 $x$ 比其他数都打，我们就寄了。

那么 $x$ 也不能被比较，此时我们选出除 $x$ 和 $y$ 的 $n-1$ 个数，然后把 $x$ 和 $n-1$ 个数里最小的比较就好了。

---

## 作者：swiftc (赞：1)

考虑 $n=3$ 的情况，假设我们第一次询问 $(a,b)$，得到 $a<b$，如果第二次询问仍然包含 $a$ 的话就可能得到前 $3$ 名的排序了。

接着询问 $b$ 不好做，于是我们考虑询问另一个不相交的 $(c,d)$，得到 $b<d$，我们再询问一次 $(a,c)$ 的大小关系，不妨设 $a<c$，此时我们可以询问 $a$ 与其他所有人的大小关系，因为存在两个比它大的大小关系不确定。

考虑这样一个算法，我们维护一个初始包含所有数的队列，每次依次取出 $a,b,c,d$ 四个数，按照如上方法询问，之后再按 $b,c,d$ 的顺序放回，这样一直做到只剩三个数为止，此时我们一定能保证这三个数中我们只知道一对的大小关系，结束即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, mp[210][210];
int query(int a, int b) {
  if (mp[a][b] != -1)
    return mp[a][b];
  cout << "? " << a << " " << b << '\n';
  cout.flush();
  char c;
  cin >> c;
  return mp[a][b] = c == '<';
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    n <<= 1;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        mp[i][j] = -1;
    vector<int> v;
    for (int i = 1; i <= n; i++)
      v.push_back(i);
    while (v.size() > 3) {
      int a = v.back();
      v.pop_back();
      int b = v.back();
      v.pop_back();
      int c = v.back();
      v.pop_back();
      int d = v.back();
      v.pop_back();
      if (!query(a, b))
        swap(a, b);
      if (!query(c, d))
        swap(c, d);
      if (!query(a, c))
        swap(a, c), swap(b, d);
      for (int i = 1; i <= n; i++) {
        if (i != a)
          query(i, a);
      }
      v.push_back(b), v.push_back(c), v.push_back(d);
    }
    cout << "! " << '\n';
    cout.flush();
  }
  return 0;
}
// 1 6 4 3 2 5
```

---

## 作者：Luzhuoyuan (赞：0)

另一种抽象的做法。

考虑将序列中的数两两配对，每对中较小的值排序后，这些值中较小的 $\lceil\frac n 2\rceil$ 个一定都在原序列较小的一半中。所以先将这部分删除，然后将它们所在数对的另一个值再进行配对（有落单的就自成一组），排序后再取最小的 $\lceil\frac{\lfloor\frac n 2\rfloor}2\rceil$ 位删掉，重复即可将较小的一半都删去。而在过程中留下的部分中每个值都只会与至多一个留下的值比较，所以无法排出顺序。

实现比较抽象，复杂度 $O(n^2\log n)$。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=205;
int _,n,m,f[N][N],cnt;
struct node{int x,y,z;}a[N];
inline bool ask(int x,int y){
	if(x==y)return 0;
	if(!~f[x][y]){
		char c;cout<<"? "<<x<<' '<<y<<endl,cin>>c;
		f[x][y]=c=='>',f[y][x]=!f[x][y];
	}return f[x][y];
}
signed main(){
	cin>>_;
	while(_--){
		cin>>n;m=n;cnt=0;
		for(int i=1;i<=n*2;i++)for(int j=1;j<=n*2;j++)f[i][j]=-1;
		for(int i=1;i<=n;i++)a[i]={i*2-1,i*2,0};
		while(cnt<n){
			for(int i=1;i<=m;i++)if(a[i].y&&ask(a[i].x,a[i].y))swap(a[i].x,a[i].y);
			for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)a[i].z+=ask(a[i].x,a[j].x);
			sort(a+1,a+m+1,[](node x,node y){return x.z>y.z;});
			int mm=m,cs=n-cnt;while(mm&&cs>0)cs-=1+!!a[mm--].y,cnt++;
			for(int i=mm+1;i<m;i++)if(a[i].y==0)swap(a[i],a[m]);
			m-=!a[m].y;
			for(int i=1;i<=(m-mm+1)/2;i++)a[mm+i].x=a[m-i+1].y;
			if((m-mm)&1)a[(m+mm+1)>>1].y=0;
			m=(m+mm+1)>>1;for(int i=1;i<=m;i++)a[i].z=0;
		}
		cout<<'!'<<endl;
	}
	return 0;
}
```

（逃

---

## 作者：_edge_ (赞：0)

更加抽象的做法，我们考虑询问 $2i,2i+1$。

那么我们可以把他分成上面较小值 $n$ 个，下面较大值 $n$ 个，两个序列，我们尝试每次从较小的里面淘汰一个最小的，然后再把他下面的那个数插进去。

注意到，如果下面的均为前 $n$ 大，则一定合法。

否则，一定是有两个前 $n$ 大的在同一列，如果他们两个不是次大和最大则一定合法，因为无法从询问中得知其余的点和最大值的关系。

否则，如果一个是次大，则我们可以尝试把他取出来。

注意到上方的最大值在这种情况下为次大值，且这个最大值只在最后会被询问，因此我们直接存下来，最后让他和目前的最小值比较一下即可（两者中一定有一个不是前 $n$ 大的）。


```cpp
#include <bits/stdc++.h>
#define int long long 
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
mt19937 rnd(4);
int gen(int l,int r) {return rnd()%(r-l+1)+l;}
const int INF=5e5+5;
const int INFN=1e3+5;
int n,v3[INF],pre[INF],p[INF];
vector <pii> cnt;
map <int,map<int,int> >Map;
char cc[INFN][INFN];
char query(int x,int y) {
    if (Map[x][y]) return cc[x][y];
    char c;cout<<"? "<<x<<" "<<y<<endl;
    cin>>c;cc[x][y]=c;Map[x][y]=1;return c;
}
void solve() {
    cin>>n;cnt.clear();Map.clear();
    for (int i=0;i<=n*2;i++) pre[i]=0;
    for (int i=1;i<=n*2;i++) p[i]=i;
    for (int i=1;i<=n;i++) {
        int x=p[i],y=p[i+n];
        char c=query(x,y);
        if (c=='<') cnt.pb({x,0}),pre[x]=y;
        else cnt.pb({y,0}),pre[y]=x;
    }
    sort(cnt.begin(),cnt.end(),[](pii x,pii y){return query(x.fi,y.fi)=='<';});
    int M=cnt.back().fi;cnt.pop_back();
    int T=n;
    while (T--) {
        int len=cnt.size(),x=cnt[0].fi,sum2=0;
        for (int i=1;i<len;i++) {
            char c=query(cnt[i].fi,x);
            if (c=='<') x=cnt[i].fi;
            sum2+=!cnt[i].se;
        }
        if (!sum2) {
            char c=query(M,x);
            if (c=='<') x=M;
        }
        vector < pii > cnt1;
        if (!pre[x]) ;
        else cnt1.pb({pre[x],1});
        for (int i=0;i<len;i++)
            if (cnt[i].fi==x) ;
            else cnt1.pb(cnt[i]);
        cnt=cnt1;
    }
    cout<<"!"<<endl;
}
signed main()
{
    int t=0;cin>>t;
    while (t--) solve();
    return 0;
}
```

---

