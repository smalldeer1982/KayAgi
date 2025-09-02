# [ARC142C] Tree Queries

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc142/tasks/arc142_c

$ N $ 頂点の木があり、各頂点には $ 1,\ldots,N $ と番号が付けられています。  
 また、各整数 $ u,v\,\ (1\ \leq\ u,v\ \leq\ N) $ に対し、頂点 $ u,v $ の距離 $ d_{u,v} $ を次のように定めます。

- 頂点 $ u $ と頂点 $ v $ を結ぶ最短パスに含まれる辺の本数

あなたは次のような質問を $ 0 $ 回以上 $ 2N $ 回以下行うことが出来ます。

- $ 1\leq\ u,v\ \leq\ N $ かつ $ u+v\ >\ 3 $ を満たす整数 $ u,v $ を指定し、頂点 $ u,v $ の距離 $ d_{u,v} $ を聞く。

頂点 $ 1,2 $ の距離 $ d_{1,2} $ を求めてください。

### Input &amp; Output Format

**この問題はインタラクティブな問題**（あなたの作成したプログラムとジャッジプログラムが入出力を介して対話を行う形式の問題）である。

まず、あなたのプログラムに標準入力から正の整数 $ N $ が与えられる。

> $ N $

その後、あなたは質問を行うことが出来る。  
 質問は標準出力に以下の形式で出力せよ(末尾に改行を入れること)。

> ? $ u $ $ v $

質問が正当な場合、その質問への答え $ d_{u,v} $ が標準入力から与えられる。

> $ d_{u,v} $

質問の形式が間違っている・質問を規定の回数より多く行った等の理由から質問が不正と判定された場合、質問への答えの代わりに `-1` が与えられる。

 ```
-1
```

この時、提出はすでに不正解と判定されている。ジャッジプログラムはこの時点で終了するため、あなたのプログラムも終了するのが望ましい。

答え $ d_{1,2} $ が分かったら、標準出力に以下の形式で出力せよ(末尾に改行を入れること)。

> ! $ d_{1,2} $

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 100 $
- $ N $ は整数
- 木はプログラムとジャッジの対話の開始前に決定される

### 注意点

- **出力を行うたびに標準出力をflushせよ。そうしなかった場合、ジャッジ結果が TLE となる可能性がある。**
- 答えを出力したら(または `-1` を受け取ったら)直ちにプログラムを正常終了せよ。そうしなかった場合、ジャッジ結果は不定である。
- 不正なフォーマットの出力を行った場合のジャッジ結果は不定である。
- 特に、余計な改行も不正なフォーマットの出力とみなされるので注意せよ。

### 入出力例

木がこの画像のような時の対話の一例を示します。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc142_c/2372d0c2156cba417b179dc14ab627f8984c08d8.png)

 入力 出力 説明 `3`  まず整数 $ N $ が与えられます。  `?` `1` `3` $ 1 $ 回目の質問として頂点 $ 1,3 $ の距離を聞きます。 `1`  頂点 $ 1,3 $ の距離が与えられます。  `?` `2` `2` $ 2 $ 回目の質問として頂点 $ 2,2 $ の距離を聞きます。 `0`  頂点 $ 2,2 $ の距離が与えられます。  `?` `2` `3` $ 3 $ 回目の質問として頂点 $ 2,3 $ の距離を聞きます。 `1`  頂点 $ 2,3 $ の距離が与えられます。  `?` `3` `1` $ 4 $ 回目の質問として頂点 $ 3,1 $ の距離を聞きます。 `1`  頂点 $ 3,1 $ の距離が与えられます。  `?` `3` `2` $ 5 $ 回目の質問として頂点 $ 3,2 $ の距離を聞きます。 `1`  頂点 $ 3,2 $ の距離が与えられます。  `?` `2` `2` $ 6 $ 回目の質問として頂点 $ 2,2 $ の距離を聞きます。 `0`  頂点 $ 2,2 $ の距離が与えられます。  `!` `2` 頂点 $ 1,2 $ の距離を回答し、終了します。実際に木の頂点 $ 1,2 $ の距離は $ 2 $ であるため AC が得られます。

# 题解

## 作者：gcx114514 (赞：1)

首先我们可以使用 $n-2$  次询问查询出所有点到 1 的距离（除了 2 号），取出其中距离 1 号点为 1 的节点则这些节点一定是 1 的儿子（同时也区分出不同子树）。现在对于两种不同情况，分别为:只有一个距离点 1 的点和有多个。

先考虑有多个点:我们可以发现求点 2 到这些点的距离，如果每个都相同那么表示点 2 也是距离 1 号点 1 的点，即点 1 和 2 距离为 1。如果不是全部相同，那么说明点 2 是 1 号点某个儿子子树中的点，而这个儿子就是距离二号点最近的那个，那么点 1 和点 2 距离为该儿子到 2 号点的距离加一。

其次如果只有一个点距离 1 号距离为 1（设为点 $p$）并且点 2 到这个点的距离为 2，那么就要分类讨论（因为 1，2 的距离既可以是 1，也可以是 3）。

那么我们可以先假设距离为 3，那么一定存在且仅存在一个点到 2 距离为 1，到 1 距离为 2（设为点 $q$）。那么点 $p$ 与点 $q$ 的距离一定为 1，否则点 1，2 距离为 1。

既然这样，那么我们可以在使用 $n-3$ 次求出点 2 到其他所有点的距离找出是否存在点 $q$ 即可解决。所以最坏情况下会使用 $n-4$ 次操作完成。


```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int Max=110;
int dis[Max][Max];
queue<int>q;
signed main(){
	int n;
	cin>> n;
	int ma=-1,mi=10000;
	for(int i=3;i<=n;++i){
		cout << "? 1 "<< i << endl;
		int x;
		cin>> x;
		dis[i][1]=dis[1][i]=x;
		if(x==1)q.push(i);
	}
	if(q.empty()){
		cout << "! 1"<< endl;
		return 0;
	}
	int j=q.size();
	if(j==1){
		int k=q.front();
		int pos=0;
		for(int i=3;i<=n;++i){
			if(i!=k){
				cout << "? 2 "<< i << endl;
				int x;
				cin>> x;
				if(x==1&&dis[1][i]==2){
					pos=i;
					break;
				}
			}
		}
		if(pos){
			cout << "? "<< pos << ' '<< k << endl;
			int x;
			cin>> x;
			if(x==1) {
				cout << "! 3"<<endl;
				return 0;
			}else{
				cout << "! 1"<<endl;
				return 0;
			}
		}else{
			cout << "? 2 "<< k << endl;
			int x;
			cin>> x;
			cout << "! " << x+1 << endl;
			return 0;
		}
	}
	while(!q.empty()){
		int z=q.front();
		q.pop();
		cout << "? 2 "<< z << endl;
		int x;
		cin>> x;
		ma=max(ma,x);
		mi=min(mi,x);
	}
	if(ma==2){
		cout << "! 1" << endl;
	}else{
		cout << "! "<< 1+mi << endl;
	}
	return 0;
}

```

---

## 作者：Tenshi (赞：0)

## 分析

看到 $2n$ 次查询容易想到分别查询 $1, 2$ 号点到其他点的距离，我们记 $a[u], b[u]$ 分别代表点 $u$ 到 $1, 2$ 的距离。

然后开始分类讨论：

- 当 $1, 2$ 点相邻的时候：\
  可以知道对任意点 $u \geq 3$, $|a[u]-b[u]|$ 必然为 $1$。
- 而当 $1, 2$ 点不相邻的时候：\
  一定存在至少一个点 $u_0$ 在 $1, 2$ 号点中间，那答案 $res$ 就是 $a[u_0]+b[u_0]$。而这个 $res$ 可以通过求 $\min_u a[u]+b[u]$ 简单地得到。

这题核心就是这样上述两种情况，但其实有一个巨坑的细节：

当点数 $n$ 为 $4$ 时，即使对任意点 $u \geq 3$，$|a[u]-b[u]|$ 为 $1$，也并不一定意味着答案为 $1$，请注意特判处理这种情况。

## AC 代码：

```cpp
// Problem: C - Tree Queries
// Contest: AtCoder - AtCoder Regular Contest 142
// URL: https://atcoder.jp/contests/arc142/tasks/arc142_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
 
#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()
 
#define x first
#define y second
using pii = pair<int, int>;
using ll = long long;
 
inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=110;

int a[N], b[N];

int q(int fir, int sec){
	cout<<"? "<<fir<<" "<<sec<<endl;
	int x; cin>>x;
	return x;
}

void o(int x){
	cout<<"! "<<x<<endl;
}

void solve(){
	int n; cin>>n;
	rep(i, 3, n) a[i]=q(1, i);
	rep(i, 3, n) b[i]=q(2, i);
	bool fl=true;
	rep(i, 3, n) if(abs(a[i]-b[i])!=1) fl=false;
	if(fl){
		int res=1;
		if(n==4){
			if(q(3, 4)==1 && a[3]+b[3]==3 && a[4]+b[4]==3) res=3;
		}
		o(res);
	}
	else{
		int res=1e9;
		rep(i, 3, n) res=min(res, a[i]+b[i]);
		o(res);
	}
}

signed main(){
	solve();	
	return 0;
}
```

---

