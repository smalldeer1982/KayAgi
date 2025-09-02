# Permutation of Rows and Columns

## 题目描述

You have been given a matrix $ a $ of size $ n $ by $ m $ , containing a permutation of integers from $ 1 $ to $ n \cdot m $ .

A permutation of $ n $ integers is an array containing all numbers from $ 1 $ to $ n $ exactly once. For example, the arrays $ [1] $ , $ [2, 1, 3] $ , $ [5, 4, 3, 2, 1] $ are permutations, while the arrays $ [1, 1] $ , $ [100] $ , $ [1, 2, 4, 5] $ are not.

A matrix contains a permutation if, when all its elements are written out, the resulting array is a permutation. Matrices $ [[1, 2], [3, 4]] $ , $ [[1]] $ , $ [[1, 5, 3], [2, 6, 4]] $ contain permutations, while matrices $ [[2]] $ , $ [[1, 1], [2, 2]] $ , $ [[1, 2], [100, 200]] $ do not.

You can perform one of the following two actions in one operation:

- choose columns $ c $ and $ d $ ( $ 1 \le c, d \le m $ , $ c \ne d $ ) and swap these columns;
- choose rows $ c $ and $ d $ ( $ 1 \le c, d \le n $ , $ c \ne d $ ) and swap these rows.

You can perform any number of operations.

You are given the original matrix $ a $ and the matrix $ b $ . Your task is to determine whether it is possible to transform matrix $ a $ into matrix $ b $ using the given operations.

## 说明/提示

In the second example, the original matrix looks like this:

 $  \begin{pmatrix} 1 & 2 \\ 3 & 4 \end{pmatrix}  $

By swapping rows $ 1 $ and $ 2 $ , it becomes:

 $  \begin{pmatrix} 3 & 4 \\ 1 & 2 \end{pmatrix}  $

By swapping columns $ 1 $ and $ 2 $ , it becomes equal to matrix $ b $ :

 $  \begin{pmatrix} 4 & 3 \\ 2 & 1 \end{pmatrix}  $

## 样例 #1

### 输入

```
7
1 1
1
1
2 2
1 2
3 4
4 3
2 1
2 2
1 2
3 4
4 3
1 2
3 4
1 5 9 6
12 10 4 8
7 11 3 2
1 5 9 6
12 10 4 8
7 11 3 2
3 3
1 5 9
6 4 2
3 8 7
9 5 1
2 4 6
7 8 3
2 3
1 2 6
5 4 3
6 1 2
3 4 5
1 5
5 1 2 3 4
4 2 5 1 3```

### 输出

```
YES
YES
NO
YES
YES
NO
YES```

# 题解

## 作者：Showball (赞：7)

**题意**：

给你两个大小为 $n \times m$ 的矩阵，其中元素的是 $n \times m$ 的排列，你可以任意交换两行或者任意交换两列，求是否通过操作使得矩阵 $a$ 变成矩阵 $b$。

**思路**：

由于矩阵中的元素是排列，并且我们每次只能交换两行或者两列。容易发现无论怎么交换同一行和同一列中的元素种类是不会改变的，只会改变相对位置。那么我们可以记录下矩阵 $a$ 中每个元素所在的行和列的位置，再按照其在矩阵 $b$ 矩阵的位置进行交换，交换完所有位置后，如果 $a$ 和 $b$ 一致，那么即可完成操作，否则一定无法通过交换操作使得矩阵 $a$ 变成矩阵 $b$。

**代码**：

```cpp
void Showball(){
   int n,m;
   cin>>n>>m;
   vector<vector<int>> a(n,vector<int>(m)),b(n,vector<int>(m));
   vector<int> row(n*m),col(n*m);
 
   for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
         cin>>a[i][j];
         a[i][j]--;
         row[a[i][j]]=i;
         col[a[i][j]]=j;
      }
   }
 
   for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
         cin>>b[i][j];
         b[i][j]--;
      }
   }
 
   for(int i=0;i<n;i++){
      int r=row[b[i][0]];
      swap(a[i],a[r]);
      for(int j=0;j<m;j++){
         row[a[i][j]]=i;
         row[a[r][j]]=r;
      }
   }
 
   for(int j=0;j<m;j++){
      int c=col[b[0][j]];
      for(int i=0;i<n;i++){
         swap(a[i][j],a[i][c]);
         col[a[i][j]]=j;
         col[a[i][c]]=c;
      }
   }
 
   cout<<(a==b?"YES\n":"NO\n");
}
```

---

## 作者：xhhhh36 (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF1980E)

首先可以发现每次交换不会改变行和列中元素的集合，只会交换行互列对应的编号，所以直接对于行和列开两个数组记录一下矩阵 $a$ 中行和列转移到了矩阵 $b$ 中行和列对应的编号，如果发现冲突则无解。

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N=2e5+5;
int T,n,m,a[N][2],b[N][2],h[N],l[N];
signed main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while (T--){
		cin>>n>>m;
		for (int i=1;i<=n;i++){
			h[i]=0;
		}
		for (int j=1;j<=m;j++){
			l[j]=0;
		}
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++){
				int x;
				cin>>x;
				a[x][0]=i;
				a[x][1]=j;
			}
		}
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++){
				int x;
				cin>>x;
				b[x][0]=i;
				b[x][1]=j;
			}
		}
		bool f=0;
		for (int i=1;i<=n*m;i++){
			if (!h[a[i][0]]){
				h[a[i][0]]=b[i][0];
			} else if (h[a[i][0]]!=b[i][0]){
				f=1;
				cout<<"NO"<<endl;
				break;
			}
			if (!l[a[i][1]]){
				l[a[i][1]]=b[i][1];
			} else if (l[a[i][1]]!=b[i][1]){
				f=1;
				cout<<"NO"<<endl;
				break;
			}
		}
		if (!f) cout<<"YES"<<endl;
	}
	return 0;
}
```

---

## 作者：Enoch006 (赞：2)

很显然的结论：无论怎么交换，每行每列的元素一定是捆绑在一起的。

如果后来的矩阵每行每列是捆绑在一起可以对应原来的矩阵，那么一定就有一种方案能将后来的矩阵构造出来，这一点 @yshpdyt 的题解已经证明了其充分性与必要性。

这里来提供一个略微简单的写法。

注意到要比较每行每列捆在一起后是不是一样的，其实不需要手写 hash，直接用 map 存一下每行每列的值有哪些，因为可以直接用 map 判等，所以直接判就行了。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 200005
#define maxn 1005
#define inf 0x3f3f3f3f3f3f
using namespace std;
int T,n,m;
int h[maxm],l[maxm];
vector<int>mp[maxm];
map<int,int>h_a[maxm],h_b[maxm];
map<int,int>l_a[maxm],l_b[maxm];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=max(n,m);i++){
			h_a[i].clear();l_a[i].clear();
			h_b[i].clear();l_b[i].clear();
			mp[i].clear();
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int x;cin>>x;
				mp[i].push_back(x);
				h_a[i][x]=1;
	            l_a[j][x]=1;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int x;cin>>x;
				h_b[i][x]=1;
				l_b[j][x]=1;
				h[x]=i;
				l[x]=j;
			}
		}		
		bool ans=1;
		for(int i=1;i<=n;i++){
			int hh=h[mp[i][0]];
			if(h_a[i]!=h_b[hh]){
				ans=0;
				break;
			}
		}
		for(int i=1;i<=m;i++){
			int ll=l[mp[1][i-1]];
			if(l_a[i]!=l_b[ll]){
				ans=0;
				break;
			}
		}		
		if(ans)cout<<"YES\n";
		else cout<<"NO\n";
	}
    return 0;
}
```

~~其实如果想把几个循环压一起写代码会更短？~~

---

## 作者：yshpdyt (赞：2)

## 题意
两个 $n\times m$ 矩阵，里面元素构成排列，你可以交换任意一列任意一行，求任意次操作后两个矩阵能否相同。

## Sol
典，怎么感觉在另一个比赛网站做过。

无论如何交换，每一行每一列元素构成的集合不变。

由于里面元素是排列，只需要判断两个矩阵构成的集合是否相同，对于含多个元素整体判断是否相同，可以考虑排序后记录哈希值，再判断哈希值构成的集合是否相同。这样一定是充要条件，必要性不难想，充分性在于列与行的排序相对独立，可以先将行按一定顺序排序，再将每行的值按一定顺序排列。

代码没什么难度，就是很暴力的取出一行或一列排序算哈希值，将所有行或所有列的哈希值比对一下即可。唯一要注意的时代码强制的题要写双哈希防止被卡。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
const ll b1=131,b2=151;
const ll mod1=1145141,mod2=20080103;
struct Hash{
    ll h1,h2;
    friend Hash operator+(const Hash &a,const Hash &b){
        return {(a.h1+b.h1)%mod1,(a.h2+b.h2)%mod2};
    }
    friend Hash operator-(const Hash &a,const Hash &b){
        return {(a.h1-b.h1+mod1)%mod1,(a.h2-b.h2+mod2)%mod2};
    }
    friend Hash operator*(const Hash &a,const ll &b){
        return {(a.h1*b)%mod1,(a.h2*b)%mod2};
    }
    friend bool operator==(const Hash &a,const Hash &b){
        return (a.h1==b.h1)&&(a.h2==b.h2);
    }
    friend bool operator<(const Hash &a,const Hash &b){
        if(a.h1==b.h1)return a.h2<b.h2;
        return (a.h1<b.h1);
    }
}h[N];
ll n,m;
vector<vector<ll> >a,b;
vector<Hash>c1,c2;
void sol(){
    cin>>n>>m;
    a.clear(),b.clear();
    c1.clear(),c2.clear();
    a.resize(n),b.resize(n);
    for(int i=0;i<n;i++){
        Hash hsh={0,0};
        vector<ll>p;
        p.resize(m);
        for(int j=0;j<m;j++)cin>>p[j];
        a[i]=p;
        sort(p.begin(),p.end());
        for(int j=0;j<m;j++)hsh=hsh+(h[j]*p[j]);
        c1.push_back(hsh);
    }
    for(int i=0;i<n;i++){
        Hash hsh={0,0};
        vector<ll>p;
        p.resize(m);
        for(int j=0;j<m;j++)cin>>p[j];
        b[i]=p;
        sort(p.begin(),p.end());
        for(int j=0;j<m;j++)hsh=hsh+(h[j]*p[j]);
        c2.push_back(hsh);
    }
    sort(c1.begin(),c1.end());
    sort(c2.begin(),c2.end());
    for(int i=0;i<n;i++){
        if(c1[i]==c2[i])continue;
        cout<<"NO\n";
        return ;
    }
    c1.clear(),c2.clear();
    for(int j=0;j<m;j++){
        Hash hsh={0,0};
        vector<ll>p;
        p.resize(n);
        for(int i=0;i<n;i++)p[i]=a[i][j];
        sort(p.begin(),p.end());
        for(int i=0;i<n;i++)hsh=(hsh+(h[i]*p[i]));
        c1.push_back(hsh);
    }
     for(int j=0;j<m;j++){
        Hash hsh={0,0};
        vector<ll>p;
        p.resize(n);
        for(int i=0;i<n;i++)p[i]=b[i][j];
        sort(p.begin(),p.end());
        for(int i=0;i<n;i++)hsh=(hsh+(h[i]*p[i]));
        c2.push_back(hsh);
    }
    sort(c1.begin(),c1.end());
    sort(c2.begin(),c2.end());
    for(int i=0;i<m;i++){
        if(c1[i]==c2[i])continue;
        cout<<"NO\n";
        return ;
    }
    cout<<"YES\n";
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    h[0]={1,1};
    for(int i=1;i<=N-5;i++){
        h[i].h1=h[i-1].h1*b1%mod1;
        h[i].h2=h[i-1].h2*b2%mod2;
    }
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
唯一要注意的时代码强制的哈希题要写双哈希
```

---

## 作者：ST_AS_IS_ZHY (赞：1)

## 题目大意

给定两个 $n \cdot m$ 的矩阵，可以进行若干次交换任意两列或两行的操作。问能否通过操作使得两个矩阵相同。

## 思路

无论是交换行还是交换列，都不会影响每一行或者一列中的元素种类，也就是说可以将每一行或者一列作为一个整体，统计在两个矩形中的出现次数，如果不相同，就说明有某一行或者一列的元素种类不相同，也就是无法转换成一样的，

统计出现次数可以用神奇的 `map` 套 `vector` ，用映射的方法可以大大减少码量（主体部分大概 $30$ 行左右）。

## code

```cpp
// Problem: Permutation of Rows and Columns
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1980E
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
//#define int long long
#define fi first
#define se second
#define PII pair<int, int>

using namespace std;

const int N = 2e6 + 10, M = 2e6 + 10, INf = 0x3f3f3f3f;

int n, m, ans, mp1[N], mp2[N];

map<vector<int>, int> l1, h1, l2, h2;
map<int, vector<int> > idl, idh;
vector<int> cy;

inline int get(int a, int b) {return (a - 1) * m + b;}
inline void clear() {l1.clear(), h1.clear(), l2.clear(), h2.clear(), idl.clear(), idh.clear();}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T --)
	{
		cin >> n >> m; bool flag = true;
		for(int i = 1; i <= n; i ++) for(int j = 1; j <= m; j ++) cin >> mp1[get(i, j)];
		for(int i = 1; i <= n; i ++) for(int j = 1; j <= m; j ++) cin >> mp2[get(i, j)];
		for(int i = 1; i <= n; i ++)
		{
			for(int j = 1; j <= m; j ++) cy.push_back(mp1[get(i, j)]);
			sort(cy.begin(), cy.end()); idl[i] = cy, l1[cy] ++; while(cy.size()) cy.pop_back();
			for(int j = 1; j <= m; j ++) cy.push_back(mp2[get(i, j)]);
			sort(cy.begin(), cy.end()); l2[cy] ++; while(cy.size()) cy.pop_back(); 
		}
		for(int j = 1; j <= m; j ++)
		{
			for(int i = 1; i <= n; i ++) cy.push_back(mp1[get(i, j)]);
			sort(cy.begin(), cy.end()); idh[j] = cy, h1[cy] ++; while(cy.size()) cy.pop_back();
			for(int i = 1; i <= n; i ++) cy.push_back(mp2[get(i, j)]);
			sort(cy.begin(), cy.end()); h2[cy] ++; while(cy.size()) cy.pop_back();
		}
		for(int i = 1; i <= n; i ++) if(l1[idl[i]] > l2[idl[i]]) flag = false; /不知道为啥大于号改成不等于号就错了
		for(int i = 1; i <= m; i ++) if(h1[idh[i]] > h2[idh[i]]) flag = false; /有没有佬可以解释一下qaq
		if(!flag) cout << "NO" << '\n';
		else cout << "YES" << '\n'; 
		clear();
	}	
	return 0;
}
```

---

## 作者：madfallen (赞：0)

注意到每次交换行或列时，每一行内元素构成的集合不变，每一列内元素构成的集合也不变。

如果操作前矩阵 $A$ 与操作后矩阵 $B$ 的每一行每一列元素形成的集合能够一一对应，那我们只需要把对应的两行调整到 $A$ 和 $B$ 中相同的位置，对应的两列调整到 $A$ 和 $B$ 中相同的位置即可。

判断两行是否相等可以用和哈希，再增加平方和哈希、立方和哈希防止被卡。将 $A$ 中行列哈希值与 $B$ 中比较即可。

Tips: $n$ 和 $m$ 都可能达到 $2 \times 10^5$，需要开 vector。

代码是好懂的。

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2e5; 
vector<int>a[N+5],a1[N+5],a2[N+5];
vector<int>b[N+5],b1[N+5],b2[N+5];
int hash1[N+5],hash2[N+5],hash11[N+5],hash22[N+5],hash111[N+5],hash222[N+5];
int n,m,t,lstn;
signed main(){
	cin>>t;
	while(t--){
		for(int i=1;i<=lstn;i++)a[i].clear(),b[i].clear(),a1[i].clear(),b1[i].clear(),a2[i].clear(),b2[i].clear();
		cin>>n>>m,lstn=n;
		for(int i=1;i<=n;i++){
			for(int j=1,x;j<=m;j++){
				scanf("%d",&x);
				a[i].push_back(x);
				a1[i].push_back(x*x);
				a2[i].push_back(x*x*x);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1,x;j<=m;j++){
				scanf("%d",&x);
				b[i].push_back(x);
				b1[i].push_back(x*x);
				b2[i].push_back(x*x*x);
			}
		}
		for(int i=1;i<=n;i++){
			hash1[i]=hash11[i]=hash111[i]=0;
			for(int j=0;j<m;j++)hash1[i]+=a[i][j];
			for(int j=0;j<m;j++)hash11[i]+=a1[i][j];
			for(int j=0;j<m;j++)hash111[i]+=a2[i][j];
		}
		for(int i=1;i<=n;i++){
			hash2[i]=hash22[i]=hash222[i]=0;
			for(int j=0;j<m;j++)hash2[i]+=b[i][j];
			for(int j=0;j<m;j++)hash22[i]+=b1[i][j];
			for(int j=0;j<m;j++)hash222[i]+=b2[i][j];
		}
		sort(hash1+1,hash1+n+1);
		sort(hash2+1,hash2+n+1);
		sort(hash11+1,hash11+n+1);
		sort(hash22+1,hash22+n+1);
		sort(hash111+1,hash111+n+1);
		sort(hash222+1,hash222+n+1);
		int flag=1;
		for(int i=1;i<=n;i++){
			if(hash1[i]!=hash2[i])flag=0;
			if(hash11[i]!=hash22[i])flag=0;
			if(hash111[i]!=hash222[i])flag=0;
		}
		for(int i=0;i<m;i++){
			hash1[i+1]=hash11[i+1]=hash111[i+1]=0;
			for(int j=1;j<=n;j++)hash1[i+1]+=a[j][i];
			for(int j=1;j<=n;j++)hash11[i+1]+=a1[j][i];
			for(int j=1;j<=n;j++)hash111[i+1]+=a2[j][i];
		}
		for(int i=0;i<m;i++){
			hash2[i+1]=hash22[i+1]=hash222[i+1]=0;
			for(int j=1;j<=n;j++)hash2[i+1]+=b[j][i];
			for(int j=1;j<=n;j++)hash22[i+1]+=b1[j][i];
			for(int j=1;j<=n;j++)hash222[i+1]+=b2[j][i];
		}
		sort(hash1+1,hash1+m+1);
		sort(hash2+1,hash2+m+1);
		sort(hash11+1,hash11+m+1);
		sort(hash22+1,hash22+m+1);
		sort(hash111+1,hash111+m+1);
		sort(hash222+1,hash222+m+1);
		for(int i=1;i<=m;i++){
			if(hash1[i]!=hash2[i])flag=0;
			if(hash11[i]!=hash22[i])flag=0;
			if(hash111[i]!=hash222[i])flag=0;
		}
		puts(flag?"YES":"NO");
	}
}


```

---

## 作者：huangboning (赞：0)

题目意思说的很清楚，这里就不再赘述。

直接暴力时间复杂度太高，于是考虑哈希。设每一行的哈希值为 $h_i=\prod\limits_{j=1}^na_{i,j}+\sum\limits_{i=1}^na_{i,j}$,每一列的哈希值为 $c_j=\prod\limits_{j=1}^na_{i,j}+\sum\limits_{i=1}^na_{i,j}$。容易发现，交换任意两行或两列，就等于将它们的哈希值互换。于是分别求出两个矩阵的哈希值，排序后比较即可。

时间复杂度 $O(nm)$。


代码：

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int T,n,m;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		int a[n+1][m+1],b[n+1][m+1],h1[n+1],c1[m+1],h2[n+1],c2[m+1],x=1,y=1;
		for(int i=1;i<=n;i++){//哈希值初始化
			h1[i]=h2[i]=1;
		}
		for(int i=1;i<=m;i++){
			c1[i]=c2[i]=1;
		}
		for(int i=1;i<=n;i++){//计算矩阵a哈希值
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				h1[i]*=a[i][j];//计算每行数值相乘
				c1[j]*=a[i][j];//计算每列数值相乘
			}
		}
		for(int i=1;i<=n;i++){//计算矩阵b哈希值
			for(int j=1;j<=m;j++){
				cin>>b[i][j];
				h2[i]*=b[i][j];
				c2[j]*=b[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				h1[i]+=a[i][j];//计算每行数值相加
				h2[i]+=b[i][j];
				c1[j]+=a[i][j];//计算每列数值相加
				c2[j]+=b[i][j];
			}
		}
		sort(h1+1,h1+n+1);//排序
		sort(c1+1,c1+m+1);
		sort(h2+1,h2+n+1);
		sort(c2+1,c2+m+1);
		bool pd=1;
		for(int i=1;i<=n;i++){//比较行和列哈希值
			if(h1[i]!=h2[i])pd=0;
		}
		for(int i=1;i<=m;i++){
			if(c1[i]!=c2[i])pd=0;
		}
		if(pd)cout<<"YES\n";
		else cout<<"NO\n";
	}
}
```

---

## 作者：shicj (赞：0)

# cf1980E Permutation of Rows and Columns 题解

我认为这题应该评黄。

## 0x00 题目大意

给你一个 $n\times m$ 矩阵，里面元素构成排列，你可以交换任意一列任意一行，求**任意次**操作后两个矩阵能否相同。

## 0x01 解题思路

看到题面，可能没有什么思路，我们来按题目模拟一下。

设原始矩阵为：

$$  \begin{pmatrix} 
a_{1,1} & a_{1,2} & \cdots & a_{1,m} \\
a_{2,1} & a_{2,2} & \cdots & a_{2,m} \\
\vdots & \vdots & \ddots & \vdots \\
a_{n,1} & a_{n,2} & \cdots & a_{n,m}\\
\end{pmatrix}  $$

对于交换行，设交换后每一行分别为 $x_1,x_2,\cdots ,x_n$，如下：

$$  \begin{pmatrix} 
a_{x_1,1} & a_{x_1,2} & \cdots & a_{x_1,m} \\
a_{x_2,1} & a_{x_2,2} & \cdots & a_{x_2,m} \\
\vdots & \vdots & \ddots & \vdots \\
a_{x_n,1} & a_{x_n,2} & \cdots & a_{x_n,m}\\
\end{pmatrix}  $$

继续交换列，设交换后每一列分别为 $y_1,y_2,\cdots ,y_n$，如下：

$$  \begin{pmatrix} 
a_{x_1,y_1} & a_{x_1,y_2} & \cdots & a_{x_1,y_m} \\
a_{x_2,y_1} & a_{x_2,y_2} & \cdots & a_{x_2,y_m} \\
\vdots & \vdots & \ddots & \vdots \\
a_{x_n,y_1} & a_{x_n,y_2} & \cdots & a_{x_n,y_m}\\
\end{pmatrix}  $$

仔细观察上面的矩阵，可以发现交换前在同一行（行号相同）的元素还在同一行，交换前在同一列的元素还在同一列。

因为操作次数不限，所以两个矩阵只要满足上述条件（即 $A$ 矩阵中同一行的元素在 $B$ 中也在同一行，$A$ 矩阵中同一列的元素在 $B$ 中也在同一列），就可以完成，否则不能。

## 0x02 代码实现

首先，$m,n$ 不确定，范围太大，需要动态处理（这在CF中很常见），可以用 `vector`：
```cpp
//分配一个n行，不定列数的二维数组
vector<vector<int> >a(n);
//加列时用push_back()
```

接下来为了方便行列的比对，我的思路是排序后直接检验（似乎也可以哈希）。

`vector` 的排序可以直接 `sort`：
```cpp
sort(a.begin(),a.end());
```

二维 `vector` 也可以（但需要先排第一维再第二维）`sort`：
```cpp
for(int i=0;i<a.size();i++){
    sort(a[i].begin(),a[i].end());
}
sort(a.begin(),a.end());
```

## 0x03 AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[10000001];
int b[10000001];
//#define a[i][j] a[i*(m+1)+j]
//#define b[i][j] b[i*(m+1)+j]
void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i*(m+1)+j]);
        }
    }
    vector<vector<int> >line1(n);
    vector<vector<int> >col1(m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            line1[i-1].push_back(a[i*(m+1)+j]);
        }
        sort(line1[i-1].begin(),line1[i-1].end());
        //cout<<"DEBUG LINE "<<i<<" [1]   : ";
        //for(auto o:line1[i-1])cout<<o<<" ";
        //cout<<endl;

    }
    sort(line1.begin(),line1.end());
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++){
            col1[j-1].push_back(a[i*(m+1)+j]);
        }
        sort(col1[j-1].begin(),col1[j-1].end());
    }
    sort(col1.begin(),col1.end());
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&b[i*(m+1)+j]);
        }
    }
    vector<vector<int> >line2(n);
    vector<vector<int> >col2(m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            line2[i-1].push_back(b[i*(m+1)+j]);
        }
        sort(line2[i-1].begin(),line2[i-1].end());
    }
    sort(line2.begin(),line2.end());
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++){
            col2[j-1].push_back(b[i*(m+1)+j]);
        }
        sort(col2[j-1].begin(),col2[j-1].end());
    }
    sort(col2.begin(),col2.end());
    for(int i=1;i<=n;i++){
        //cout<<"DEBUG LINE "<<i<<" [1]   : ";
        //for(auto o:line1[i-1])cout<<o<<" ";
        //cout<<endl;
        //cout<<"DEBUG LINE "<<i<<" [2]   : ";
        //for(auto o:line2[i-1])cout<<o<<" ";
        //cout<<endl;
        if(line1[i-1]!=line2[i-1]){
            cout<<"NO"<<endl;
            return;
        }
    }
    for(int j=1;j<=m;j++){
        if(col1[j-1]!=col2[j-1]){
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：jr_inf (赞：0)

若某个数字位于 $a_{x,y},b_{x^\prime,y^\prime}$，那么 $a$ 的第 $x$ 行就是 $b$ 的第 $x^\prime$ 行，$a$ 的第 $y$ 列就是 $b$ 的第 $y^\prime$ 列，因为行列的交点是不变的。根据 $a,b$ 我们能够得到 $n\times m$ 个对应关系，检查是否有某行/列被对应到两个位置就能知道是否合法。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<set>
#define fre(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define mst(x,y) memset(x,y,sizeof(x))
//#define int long long
//#define int unsigned long long
using namespace std;
//const int p=415411;
const int iinf=2147483647;
const long long linf=9223372036854775807;
const int N=2e5+10;
int t,n,m,nx[N],ny[N],x;
bool f;
struct node{int x,y;}a[N],b[N];
signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n*m;i++)nx[i]=ny[i]=0;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&x),a[x]=((node){i,j});
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&x),b[x]=((node){i,j});
				nx[a[x].x]=i,ny[a[x].y]=j;
			}
		}
		f=1;
		for(int i=1;i<=n;i++)f&=(bool)nx[i];//cout<<nx[i]<<' ';cout<<endl;
		for(int i=1;i<=m;i++)f&=(bool)ny[i];//cout<<ny[i]<<' ';cout<<endl;
		for(int i=1;i<=n*m;i++)f&=(nx[a[i].x]==b[i].x&&ny[a[i].y]==b[i].y);
		puts(f?"YES":"NO");
	}
}
```

顺带一提，如果你还会网络流，就能切掉 [P1129 [ZJOI2007] 矩阵游戏](https://www.luogu.com.cn/problem/P1129) 了。

---

## 作者：ShadowNull (赞：0)

## 题目大意
给定 $n \times m$ 的矩阵 $a$ 和 $b$，其中元素为 $n \times m$ 的排列。

试问：是否存在一种方案，使得将矩阵 $a$ 的若干行进行交换、若干列进行交换后，得到矩阵 $b$。

## 题目分析
容易发现，任意一行的元素操作后，这些元素仍然会在同一行。同理，任意一列的元素在操作后，这些元素仍然会在同一列。

因此，如果我们能通过操作将矩阵 $a$ 变为矩阵 $b$，必然需要满足如下条件：
- 对于矩阵 $a$ 的每一行，矩阵 $b$ 中都存在一行，使得这两行中包含的元素相同。
- 对于矩阵 $a$ 的每一列，矩阵 $b$ 中都存在一列，使得这两列中包含的元素相同。

于是我们想到利用 SumHash 计算每一行、每一列包含了哪些元素，丢到 set 里面遍历一下就行了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define ULL unsigned long long

const int N = 2e5+10;
int n, m;
ULL hashtb[N];
ULL a[N][2], b[N][2];
unordered_set<ULL> row, col;

inline void init()
{
    mt19937_64 rd(time(0));
    for (int i = 1; i < N; i++) hashtb[i] = rd();
}

inline void solve()
{
    for (int i = 1; i <= n; i++) a[i][0] = b[i][0] = 0;
    for (int i = 1; i <= m; i++) a[i][1] = b[i][1] = 0;
    cin >> n >> m;
    row.clear();
    col.clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int x; cin >> x;
            a[i][0] += hashtb[x];
            a[j][1] += hashtb[x];
        }
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int x; cin >> x;
            b[i][0] += hashtb[x];
            b[j][1] += hashtb[x];
        }
    
    for (int i = 1; i <= n; i++) row.insert(b[i][0]);
    for (int i = 1; i <= m; i++) col.insert(b[i][1]);

    for (int i = 1; i <= n; i++)
        if (row.find(a[i][0]) == row.end()) {cout << "NO" << endl; return;}
    for (int i = 1; i <= m; i++)
        if (col.find(a[i][1]) == col.end()) {cout << "NO" << endl; return;}
    cout << "YES" << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int T; cin >> T;
    for (int i = 1; i <= T; i++)
        solve();
    return 0;
}

```

---

