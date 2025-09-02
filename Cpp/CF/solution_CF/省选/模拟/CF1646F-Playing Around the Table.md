# Playing Around the Table

## 题目描述

## 题意

有 $n$ 个玩家，从 $1$ 到 $n$ 编号，按顺序形成一个环 $i$ 的右边是 $i + 1$，特别地，$n$ 的右边是 $1$ 。

现在有 $n^2$ 张牌，每张上有一个整数，范围在 $[1, n]$ ，其中值为 $i$ 的牌有 $n$ 张。

每一次操作，令每个玩家选择一张牌给自己的下家。所有这些操作都是同时执行的。

玩家 $i$ 的目标是得到 $n$ 张值为 $i$ 的牌。请找出一种方案：在不超过 $(n ^ 2 - n)$ 次操作使每个玩家达成目标。

你不需要使操作数最小化。

Translated by JDS070115.

## 说明/提示

$2 \leq n \leq 100$

## 样例 #1

### 输入

```
2
2 1
1 2```

### 输出

```
1
2 1```

## 样例 #2

### 输入

```
3
1 1 1
2 2 2
3 3 3```

### 输出

```
6
1 2 3
3 1 2
2 3 1
1 2 3
3 1 2
2 3 1```

# 题解

## 作者：GIFBMP (赞：8)

我们一开始考虑将每个人手上的牌都变成 $\{1,2,\dots,n\}$。

那么我们可以找到第一个手上有重复的牌的人，然后从他开始依次进行以下操作：

1. 若这个人手上有重复的牌，那么将重复的牌中的一张传给下一个人；
2. 否则由于这个人手上已经有 $\{1,2,\dots,n\}$ 数值的牌，因此直接将和上一个人传过来的牌数值相同的牌传给下一个人。

可以证明，这样操作的步数不会超过 $\dfrac{n\times (n-1)}{2}$。

做完上述操作后，接下来就是把它们转化成题目中要求的答案，以 $n=4$ 为例：

我们把操作完后每一个人的牌变换以下形式，即：

第一个人：$\{1,2,3,4\}$；  
第二个人：$\{2,3,4,1\}$；  
第三个人：$\{3,4,1,2\}$；  
第四个人：$\{4,1,2,3\}$；  

那么我们通过观察可以发现，对于任意的 $2\le i\le n$，我们只要执行 $i-1$ 次循环移位操作即可将牌复原。

这一部分的操作数为 $\sum_{i=2}^n(i-1)=\dfrac{n\times (n-1)}{2}$。

因此总操作数为 $\dfrac{n\times (n-1)}{2}+\dfrac{n\times (n-1)}{2}=n^2-n$。

实现时用一个桶维护即可。

Code:

```cpp
#include <cstdio>
using namespace std ;
const int MAXN = 110 , MAXM = 1e4 + 10 ;
int n , t[MAXN][MAXN] , cnt , ans[MAXM][MAXN] ;
int check () {
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= n ; j++)
			if (t[i][j] > 1) return i ;
	return 0 ;
}
void print () {
	for (int i = 1 ; i <= n ; i++ , puts (""))
		for (int j = 1 ; j <= n ; j++)
			for (int k = 1 ; k <= t[i][j] ; k++)
				printf ("%d " , j) ;
}
int main () {
	scanf ("%d" , &n) ;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 , x ; j <= n ; j++)
			scanf ("%d" , &x) , t[i][x]++ ;
	while (1) {
		int nw = check () ;
		if (!nw) break ;
		int las = 0 ; cnt++ ;
		for (int i = 1 ; i <= n ; i++)
			if (t[nw][i] > 1) {
				t[nw][i]-- , ans[cnt][nw] = las = i ;
				//printf ("%d:%d\n" , nw , i) ;
				break ;
			}
		for (int i = nw % n + 1 ; i != nw ; i = i % n + 1) {
			bool flag = 0 ;
			for (int j = 1 ; j <= n ; j++)
				if (t[i][j] > 1) {
					flag = 1 ; t[i][las]++ , t[i][j]-- ; ans[cnt][i] = las = j ;
					//printf ("%d:%d\n" , i , j) ;
					break ;
				}
			if (!flag) ans[cnt][i] = las ;
		}
		t[nw][las]++ ;
		//print () ;
	}
	//print () ;
	for (int i = 2 ; i <= n ; i++) {
		for (int j = 1 ; j < i ; j++) {
			cnt++ ;
			for (int k = 1 ; k <= n ; k++) {
				int tmp = (k + i - j + n) % n ? (k + i - j + n) % n : n ;
				//printf ("%d:%d\n" , k , tmp) ;
				ans[cnt][k] = tmp , t[k][tmp]-- , t[k % n + 1][tmp]++ ;
			}
			//print () ;
		}	
	}
	printf ("%d\n" , cnt) ;
	for (int i = 1 ; i <= cnt ; i++ , puts (""))
		for (int j = 1 ; j <= n ; j++)
			printf ("%d " , ans[i][j]) ;
	return 0 ;
}
```

---

## 作者：wf1594937223 (赞：6)

此题分享两种做法，一种是官方标算，一种是我的乱搞；

标算：

考虑一开始将所有人手上的牌用至多 $\dfrac{n\times (n-1)}{2}$ 次操作变为手上都是 $1,2,...,n$，操作方法为如果一个人手上有重复的牌，那就传这张；否则传上一个人传过来的牌；我们来证明这是符合要求的：

我们设一张牌走的步数为他被移动的次数，并首先只考虑一种颜色；考虑证明一个更强的结论：走了第 $\ge x$ 步的卡片数量 $\le n-x$ 个，因为既然已经走了 $x$ 步，那么走 $x$ 步前一定是有至少 $x$ 个点上面至少有 $1$ 张牌，而这些点是不会移动的。

然后按照我们的策略，我们会发现总步长 $\le \dfrac{n^2 \times (n-1)}{2}$，而每次我们移动的时候步长会减去 $n$（对于还没归位的步数 $-1$，已经归位的帮别人步数 $-1$），证毕。

构造出这个结论之后我们再用 $\dfrac{n \times (n-1)}{2}$ 次操作还原即可，这部分非常简单，留给读者思考。

我的乱搞：

我们考虑我们可以用很简单的暴力使得第 $i$ 位至少有 $i-1$ 个 $i$ 卡牌，然后我们考虑一种构造方式：对于一位 $i$，我们设 $lef_i$ 表示第 $i$ 列剩下的是什么，那么如果 $lef_{i-1}=i$，那么我们可以考虑我们这一位传一个 $i$，整个序列 $lef$ 就相当于固定了这一位然后循环位移了一位的结果（如果有多个就相当于固定多位），这样如果你固定之后 $lef$ 以 $1$ 开头的序列逆序对减少，就固定；否则不固定。这种方法在随机数据下跑得很快，但是对于构造的数据稍有劣势，我们考虑再另一种构造方案：我们用某一列作为“跳板”，使得最后剩下的是形如一个 $1,2,...,n$ 的循环位移序列，然后我们再将其转回去即可；此处跳板如果直接选取 $1$ 的话可能会被 test155 卡掉，所以我们将跳板设为一个随机值即可，怕不稳的话也可以试一下所有列当跳板。

我的乱搞代码（仅供参考）：

```cpp
# include <stdio.h>
# include <random>
# include <time.h>
std::mt19937 ran(time(0));
int a[110][110],b[110][110];
int rem[20010][110],totr,n;
int hav[110],loc[110];
int bel[110],cun;
int pre(int x)
{
	return (x+n-2)%n+1;
}
int nxt(int x)
{
	return x%n+1;
}
void done()
{
	int i,j;
	totr++;
	for(i=1;i<=n;i++)
	{
		for(j=i-1;j>=1;j--)
		{
			if(a[i][j])
				break;
		}
		if(a[i][j])
		{
			rem[totr][i]=j;
			continue;
		}
		for(j=n;j>=i+1;j--)
		{
			if(a[i][j])
				break;
		}
		rem[totr][i]=j;
	}
	for(i=1;i<=n;i++)
	{
		a[i][rem[totr][pre(i)]]++;
		a[i][rem[totr][i]]--;
	}
	return;
}
int check()
{
	int i,j,tot;
	for(i=1;i<=n;i++)
	{
		tot=0;
		for(j=1;j<=n;j++)
		{
			if(j!=i)
				tot+=a[i][j];
		}
		if(tot>1)
			return 1;
	}
	for(i=1;i<=n;i++)
	{
		hav[i]=i;
		for(j=1;j<=n;j++)
		{
			if(j!=i && a[i][j])
				hav[i]=j;
		}
	}
	return 0;
}
void move()
{
	int i,j;
	totr++;
	for(i=1;i<=n;i++)
		rem[totr][i]=hav[i];
	for(i=1;i<=n;i++)
		bel[i]=pre(bel[i]);
	for(i=1;i<=n;i++)
	{
		hav[i]=rem[totr][pre(i)];
		a[i][rem[totr][pre(i)]]++;
		a[i][rem[totr][i]]--;
	}
	return;
}
int che(int x)
{
	if(hav[pre(x)]!=1 && hav[x]!=1)
	{
		if(hav[pre(x)]>hav[x])
			return 1;
		else
			return 0;
	}
	if(hav[x]==1)
	{
		if(hav[x]>hav[pre(pre(x))])
			return 1;
		else
			return 0;
	}
	if(hav[pre(x)]==1)
	{
		if(hav[x]>hav[nxt(x)])
			return 1;
		else
			return 0;
	}
	return 0;
}
void done2()
{
	int i,j;
	totr++;
	for(i=1;i<=n;i++)
	{
		if(hav[pre(i)]==i)
			loc[i]=che(i);
		else
			loc[i]=0;
	}
	for(i=1;i<=n;i++)
	{
		if(loc[i])
			rem[totr][i]=i;
		else
			rem[totr][i]=hav[i];
	}
	for(i=1;i<=n;i++)
	{
		a[i][rem[totr][pre(i)]]++;
		a[i][rem[totr][i]]--;
		if(!loc[i])
			hav[i]=rem[totr][pre(i)];
	}
	return;
}
int check2()
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		if(hav[pre(i)]!=i)
			return 1;
	}
	return 0;
}
int cheok()
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		if(a[i][i]!=n)
			return 1;
	}
	return 0;
}
int main()
{
	int i,j,m;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%d",&m);
			a[i][m]++;
			b[i][m]++;
		}
	}
	while(check() && cheok())
		done();
	for(i=1;i<=n;i++)
		bel[i]=i;
	m=ran()%n+1;
	cun=hav[m];
	hav[m]=m;
	while(cheok())
	{
		move();
		if(cun!=m && bel[m]==cun)
		{
			cun=hav[m];
			hav[m]=bel[m];
		}
		if(cun==m && bel[m]!=hav[m])
		{
			cun=hav[m];
			hav[m]=m;
		}
	}
	if(totr<=n*n-n)
	{
		printf("%d\n",totr);
		for(i=1;i<=totr;i++)
		{
			for(j=1;j<=n;j++)
				printf("%d ",rem[i][j]);
			printf("\n");
		}
		return 0;
	}
	totr=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			a[i][j]=b[i][j];
	}
	while(check() && cheok())
		done();
	while(check2() && cheok())
		done2();
	if(cheok())
		done();
	printf("%d\n",totr);
	for(i=1;i<=totr;i++)
	{
		for(j=1;j<=n;j++)
			printf("%d ",rem[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：peterwuyihong (赞：3)

真的不颓了吗

题意：有 $n$ 个人坐成一个圈，每个人手上有 $n$ 张麻将，麻将上是 $1$ 萬到 $n$ 萬，每次可以让每个人同时掏出一张麻将给下一个人，构造一组方案使得第 $i$ 个人有 $n$ 张 $i$ 萬。

神秘构造题，先搞出中间态，就是每个人有一组一气通贯，然后我们构造。

你把麻将切开，变成这样

![](https://cdn.luogu.com.cn/upload/image_hosting/y78opsm0.png)

然后每一列再错几下就行了。

然后再构造一组让任意情况变成中间态的方法。

非常的简单啊！如果没有变成中间态，那么必然有一行存在两个，然后把这两个给下一行，根据抽屉原理，下一行也必然有两个，然后这么做 $n$ 下，就做好一轮了。

然后暴力做，直到变成中间态。

证明留给读者，可以往反向构造去考虑。

方便实现，可以掏出一个 set，装出现过的第 $i$ 行重复出现过的数，然后就能快速方便地掏出来了，动态维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=j;i<=(k);i++)
signed main(){
  int n;
  cin>>n;
  vector a(n,vector<int>(n));
  vector<vector<int> >ans;
  set<pair<int,int> >S;
  rep(i,0,n-1){
    rep(j,0,n-1){
      int x;
      cin>>x;x--;
      a[i][x]++;
    }
    rep(j,0,n-1)if(a[i][j]>1)S.insert({i,j});
  }
  while(S.size()){
    ans.push_back(vector<int>(n));
    int R=S.begin()->first;
    rep(i,0,n-1){
      auto it=S.lower_bound({(R+i)%n,0});
      assert(it!=S.end());
      ans.back()[(R+i)%n]=it->second;
      if(--a[(R+i)%n][it->second]<2)S.erase(it);
      if(++a[(R+i+1)%n][it->second]>1)S.insert({(R+i+1)%n,it->second});
    }
  }
  cout<<ans.size()+n*(n-1)/2<<endl;
  for(auto i:ans){
    for(int j:i)cout<<j+1<<' ';
    cout<<endl;
  }
  rep(i,0,n-1){
    rep(j,0,i-1){
      rep(k,0,n-1)
      cout<<(i+k+n-j)%n+1<<' ';
      cout<<endl;
    }
  }
}
```

---

## 作者：do_it_tomorrow (赞：3)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1646f-playing-around-the-table-de-ti-jie/)
## 题目大意

有 $n$ 种牌，一种 $n$ 张，一共 $n$ 个玩家，一人 $n$ 个。每个人一次将一张牌对给下家，求构造方案使可以在 $n\cdot (n-1)$ 次操作之内使第 $i$ 个人拥有 $n$ 张 $i$。

数据范围满足，$1\le n\le 100$。

## 思路

因为直接构造出题目要求的情况会出现如果一个人提前完成了牌的收集，那么在接下来的操作中他的牌会被打乱，并不足够优秀。

考虑先构造出每一个人都拥有 $1$ 到 $n$ 号牌的方案，在使用 $\dfrac{n\cdot(n-1)}{2}$ 的交换次数交换为题目要求的方案。

现在问题转化为了怎么构造出每一个人都拥有 $1$ 到 $n$ 号牌的方案。

如果没有构造出上述的情况，那么一定有一个人拥有重复的牌，将这个牌传给下家。如果这个人手中的牌都没有重复，那么可以它可以将上家传给他的牌传给下家，这样就可以保证手中现在的情况不被破坏。

只考虑值为 $1$ 的牌需要被往前送多少次。把牌看作 $1$ ，人看作 $−1$ ，那么必然存在一个循环移位使得前缀和非负。于是不难发现，在这个循环移位下，每张牌只会往前走，不会从第 $n$ 个人回到第 $1$ 个人。

所以这个操作是可以在 $\dfrac{n\cdot(n-1)}{2}$ 次操作之内完成的。

```c++
#include<iostream>
using namespace std;
const int N=105;
int n,a[N][N],ans[N];
int ck(){
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(a[i][j]>1){
        // cout<<"i="<<i<<" j="<<j<<'\n';
        return i;
    }
    return 0;
}
signed main(){
    cin>>n;
    for(int i=1,x;i<=n;i++) for(int j=1;j<=n;j++) cin>>x,a[i][x]++;
    cout<<(n-1)*n<<'\n';
    for(int num=1;num<=(n-1)*n/2;num++){
        int p=ck(),f=1;
        // cout<<"p="<<p<<'\n';
        if(!p){
            for(int i=1;i<=n;i++) cout<<1<<' ';
            cout<<'\n';continue;
        }
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=n;j++){
        //         cerr<<a[i][j]<<' ';
        //     }
        //     cerr<<'\n';
        // }
        // cout<<p<<'\n';
        for(int i=p;i!=p||f;i=i%n+1,f=0){
            for(int j=1;j<=n;j++){
                if(a[i][j]>1){
                    a[i][j]--;
                    a[i%n+1][j]++;
                    ans[i]=j;
                    break;
                }
            }
        }
        for(int i=1;i<=n;i++){
            cout<<ans[i]<<' ';
        }
        cout<<'\n';
    }
    
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            for(int k=1;k<=n;k++){
                cout<<(i+k-j-1)%n+1<<' ';
            }
            cout<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：ChickyHas (赞：1)

好题，给我们提供了设置中间状态来构造的思路。

这个题让我们从初始状态到所有数相同，但其实从样例也能看出来，前一半的操作做完后每个玩家都应该 $1,2,\cdots,n$ 的牌各有一张，这是我们的中间状态。

考虑怎么从初始状态到中间状态，如果此时不是中间状态，那么必然有某一个玩家两张牌相同，我们找到这张牌，把他传给下一个玩家。

下一个玩家接到这张牌，能干什么呢？

如果下一个玩家本来也有重复的牌，那就把上一张牌收着，把重复的传下去。如果没有就直接把和上一张牌相同的牌传下去，因为没有重复的话每种牌都有一张，因此肯定可以传下去。

此时我们已经到了中间状态，用的次数是不超过 $\frac{n(n-1)}{2}$ 的，因为重复的只有这么多。

接下来到最终状态，我们把 $1,2,\cdots,n$ 可以排成 

$2,3,4,\cdots,n,1$

$3,4,\cdots,n,1,2$

$\cdots$

那么我们只要通过每次对于某一列循环移位，就可以做到 $\frac{n(n-1)}{2}$ 次了。

加起来次数不超过 $n^2-n$ 那么就做完了。

---

## 作者：drowsylve (赞：1)

### 题解
一道课上讲的比较简单的构造。

一种比较直接的想法是直接把当前不需要的牌传给下家，但如果某位玩家提前组好了牌，或者每位玩家都只有一张牌没有组好，那么接下来的传递就会浪费一些次数。

一种思路是先考虑一个中间状态，即所有玩家拥有 $n$ 种不同的牌各一张。

此状态转移至最终状态比较显然，对于每个 $k$，第 $i$ 个人传递牌 $i-k$，进行 $k$ 次传递即可归位，操作次数为 $n\times(n-1)/2$。

于是问题转化为如何构造出中间状态。一种比较直接的想法是直接找到当前手中有重复的牌的人，由他开始不断向下传递，直到所有人都没有重复的牌，也就达成了中间状态。

关于正确性，每种类型的牌，只需要最多 $\sum i=n\times(n−1)/2$ 步即可完成，而每次操作是 $n$ 步，共有 $n$ 种牌，所以最终操作次数不会超过 $n\times(n−1)/2$。

代码实现比较简单。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n;
int c[N][N],ans[N*N][N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	int s;
	for(int i=1;i<=n;i++){
		int a;
		for(int j=1;j<=n;j++){
			cin>>a;
			if((++c[i][a])>1) s=i;
		}
	}
	int rd=0;
	while(1){
		int g=-1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(c[i][j]>1){
					c[i][j]--;
					ans[++rd][i]=g=j;
					s=i;
					break;
				}
			}
			if(g!=-1) break;
		}
		if(g==-1) break;
		for(int s0=s+1;s0<s+n;s0++){
			int i=s0%n;
			if(i==0) i=n;
			c[i][g]++;
			for(int j=1;j<=n;j++){
				if(c[i][j]>1){
					c[i][j]--;
					ans[rd][i]=g=j;
					break;
				}
			}
		}
		c[s][g]++;
	}
	for(int i=2;i<=n;i++){
		//move card i,i+1...i+n-1 in round (1~i-1) begin at player j
		for(int j=1;j<i;j++){
			rd++;
			for(int k=i,dt=0;k<i+n;k++,dt++){
				int cd=k%n;
				if(cd==0) cd=n;
				int p=(j+dt)%n;
				if(p==0) p=n;
				ans[rd][p]=cd;
			}
		}
	}
	cout<<rd<<'\n';
	for(int i=1;i<=rd;i++){
		for(int j=1;j<=n;j++)
			cout<<ans[i][j]<<' '; 
		cout<<'\n';
	}
	return 0;
}
```
#####  _拜谢唐爷爷的激情讲解。_

---

## 作者：ax_by_c (赞：0)

每个人手中没有相同的牌是容易的，只需要 $\frac{n(n-1)}{2}$ 次操作，于是考虑通过 $\frac{n(n-1)}{2}$ 次操作使每个人手中没有相同的牌。

每次操作时，若某人手中有相同牌，则选择一张相同牌向后传。否则这个人手中没有相同牌，选择上一个人传来的牌向后传即可。

关于次数的证明：考虑每种牌，在第 $i$ 列最多会移动 $i-1$ 次（至多 $i-1$ 个人已经有了这种牌），所以总操作次数不超过 $\frac{n(n-1)}{2}$。

综上，总操作次数不超过 $n(n-1)=n^2-n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
const int N=105;
const int M=1e4+5;
int n,cnt,ans,res[M][N];
set<int>a[N];
vector<int>b[N];
int pre(int x){
	if(x==1)return n;
	return x-1;
}
int nxt(int x){
	if(x==n)return 1;
	return x+1;
}
void main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1,tmp;j<=n;j++){
			scanf("%d",&tmp);
			if(a[i].count(tmp))b[i].push_back(tmp);
			else a[i].insert(tmp);
		}
		if((int)a[i].size()!=n)cnt++;
	}
	while(cnt){
		ans++;
		int fd=0;
		for(int i=1;i<=n;i++){
			if((int)a[i].size()!=n){
				fd=i;
				break;
			}
		}
		for(int i=fd;i<=n;i++){
			if((int)a[i].size()!=n)res[ans][i]=b[i].back();
			else res[ans][i]=res[ans][pre(i)];
		}
		for(int i=1;i<fd;i++){
			if((int)a[i].size()!=n)res[ans][i]=b[i].back();
			else res[ans][i]=res[ans][pre(i)];
		}
		for(int i=1;i<=n;i++){
			if((int)a[i].size()!=n){
				b[i].pop_back();
				if(a[i].count(res[ans][pre(i)]))b[i].push_back(res[ans][pre(i)]);
				else a[i].insert(res[ans][pre(i)]);
				if((int)a[i].size()==n)cnt--;
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=n;j++){
			for(int t=1,p=j;t<=i;t++,p=nxt(p)){
				res[ans+t][p]=(j+i-1)%n+1;
			}
		}
		ans+=i;
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",res[i][j]);
		}
		putchar('\n');
	}
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

直接构造（第 $i$ 个人随便丢一张不是 $i$ 的牌）为何劣？因为在最坏情况下每一轮只能使得一个人多获得一张其需要的牌甚至没有人获得自己需要的牌。粗略估计一下次数上界会比 $n^2$ 大。

当然我不是很会分析，只是组略估计一下。

考虑先构造一个中间态：所有人的牌都是 $1\sim n$。

以 $n=4$ 作为例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/lezu27q4.png)


这个时候我们发现只需要对每一列错位一下就行了。

这里的次数是 $\sum\limits _{i=1}^{n-1} i = \dfrac{n\times (n-1)}{2}$，因为第一列不用错，其后的第 $i$ 列要错 $i$ 次才能到达对应位置。

然后考虑到达这个中间态的次数。

最坏情况就是每个人都有 $n$ 张一样的牌，类似：

![](https://cdn.luogu.com.cn/upload/image_hosting/l0f7h15x.png)

然后我们发现也可以类似的错位，从第一列开始，第 $i$ 位错 $i$ 次，最后一列不用错。

这里的次数上界也是 $\dfrac{n\times(n-1)}{2}$。

总次数上界就是 $n\times (n-1)=n^2-n$。

然后按照这个思路模拟：

设 $a_{i,j}$ 为第 $i$ 个人第 $j$ 张牌目前有多少张。

对于到达中间态中的每一轮的第 $i$ 个人：

* $\exists j,a_{i,j}>1$，将 $j$ 丢给下家。
* 否则直接将上家丢给你的牌丢给下家。

实际操作中，我们先找到第一个有重复牌的，设这个位置为 $j$，然后先操作 $j\sim n$，然后操作 $1\sim j-1$。

因为如果直接让操作顺序为 $1\sim n$，可能会出现 $1$ 已经合法，而又不知道它的上家给它的牌的情况。 

然后对于中间态到最终状态，此时终末状态都是固定的就不用考虑什么策略了，随便手模一下找规律就行。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=110;
int n;
int c[N][N];
int tot,ans[N*N][N];//答案 
int pd(int i)
{
	F(j,1,n) if(c[i][j]>1) return j;
	return 0;
}
il void solve()
{
	n=read();
	F(i,1,n) F(j,1,n) c[i][read()]++;
	while(1)//转中间态的每一轮 
	{
		int j=1;
		while(j<=n&&!pd(j)) j++;//找到第一个需要更改的j
		if(j>n) break;
		++tot;
		F(i,j,n)
		{
			int k=pd(i);
			if(k) ans[tot][i]=k;
			else ans[tot][i]=ans[tot][i-1];
		}
		if(j!=1)
		{
			ans[tot][1]=ans[tot][n];
			F(i,2,j-1)
			{
				int k=pd(i);
				if(k) ans[tot][i]=k;
				else ans[tot][i]=ans[tot][i-1];
			}
		}
		c[1][ans[tot][n]]++;
		c[1][ans[tot][1]]--;
		F(i,2,n)
		{
			c[i][ans[tot][i]]--;
			c[i][ans[tot][i-1]]++;
		}
//		F(i,1,n) printk(ans[tot][i]);
//		puts("");
	}
	put(tot+n*(n-1)/2);//先把中间态的答案输出，后面操作的次数是固定的
	F(i,1,tot)
	{
		F(j,1,n) printk(ans[i][j]);
		puts("");
	}
//后面是固定操作，可以自己手模理解一下
	tot=1;
	F(i,1,n-1) ans[tot][i]=i+1;
	ans[tot][n]=1;
	F(i,1,n) printk(ans[tot][i]);
	puts("");
	F(i,2,n-1)
	{
		++tot;
		F(j,1,n-1) ans[tot][j]=ans[tot-1][j+1];
		ans[tot][n]=ans[tot-1][1];
		f(j,tot,1)
		{
			F(k,1,n) printk(ans[j][k]);
			puts("");
		}
	}
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

在洛谷没有通过的原因是洛谷 RMJ 无法提交。这份代码可以在 CF 上通过。

---

## 作者：MEKHANE (赞：0)

# CF1646F

又是一道构造题。（不要求最小）

首先两个要素：$n(n-1)$ 以及第 $i$ 人拿全部的 $i$ 牌。

将 $n(n-1)$ 转换为我们可知且熟悉的转移形式：$\binom{n}{2}$ 。这预示着我们要进行两步的操作。

考虑如果我们一步正常转移会发生什么问题。考虑贪心的每次将不在位置上的数通过一次操作传递回到位置上。发现这样我们无法利用剩余的未进行传递的人。

这预示着我们每次操作不能单个考虑，需要全局考虑。全局相等为结果，那么我们有什么中间状态可以缓冲呢？

考虑每个人每种牌都有一个的状态。构造方法很直白：拿到上家的牌后，每次将重复的牌递给下家。这样每次都至少有两个人种类多 $1$ ，所以最多的次数为 $n(n-1)/2$。

剩下的就很简单了；考虑将 $1,2,3,4 \dots n$ 形成一个环将其挪至正确的位置，像这样：

第一个人：$1,2,3$ 

第二个人：$2,3,1$  

第三个人：$3,1,2$ 

这样对于列 $i$ ,我们都仅需要 $i-1$ 次操作，所以次数为 $n(n-1)/2$ 。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=122;
int xl[N*N][N],mp[N][N],dq[N],dq1[N],n,col,tot,cnt[N];
void add(int x,int y){
	mp[x][y]++,cnt[x]+=(mp[x][y]==1);
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
		cin>>col,add(i,col);
	}
	for(int i=1;i<=n*(n-1)/2;i++){
		int pd=1;
		for(int j=1;j<=n;j++)
			if(cnt[j]!=n) {pd=0; break;}
		if(pd) break;
		tot++; int cs=0;
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++)
				if(mp[j][k]>1) {cs=j; break;}
			if(cs) break;
		}
		for(int j=cs;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(mp[j][k]>1) {xl[tot][j]=k,mp[j][k]--,add(j%n+1,k); break;}
		for(int j=1;j<=cs-1;j++)
			for(int k=1;k<=n;k++)
				if(mp[j][k]>1) {xl[tot][j]=k,mp[j][k]--,add(j%n+1,k); break;}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) dq[j]=(i+j-2)%n+1;
		for(int j=1;j<=i-1;j++){
			tot++;
			for(int j=1;j<=n;j++) xl[tot][j]=dq[j],dq1[j%n+1]=dq[j];
			for(int k=1;k<=n;k++) dq[k]=dq1[k];
		}
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=n;j++) cout<<xl[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：红黑树 (赞：0)

## [题意](https://codeforces.com/contest/1646/problem/F)
$n$ 个人围成一个圈，每个人有 $n$ 张牌，每种牌上写有一个 $1$ 到 $n$ 的数，保证每种牌恰好有 $n$ 张，在操作中，你让每个人选一张牌传给下一个人。传牌操作是所有人在同一瞬间做完的。

你要构造一个方案，使得操作数不超过 $n \times \left(n - 1\right)$，并且最终让第 $i$ 个人手里所有的牌上写的数都是 $i$。

$2 \leq n \leq 100$

## 题解
直接随便传不要的牌的话可能导致有一个人恰好集齐了所有的牌，于是阻塞后面的传牌。

这题实际上可以选一个中间状态，从起始状态先转到中间状态，再又中间状态转到最终状态。

我这里选的中间状态是让每个人都恰好有 $1$ 到 $n$ 的牌各一张。

转到最终状态是平凡的。操作次数最多为 $\frac{n \times \left(n - 1\right)}2$ 次。

现在考虑从起始状态转到最终状态。

起始只要让每个人不要把自己手里只出现了一次的牌丢掉就行了。如果当前这个人已经恰好有 $1$ 到 $n$ 的牌各一张，那就传走上一个人准备传过来的牌即可。

操作次数最多也为 $\frac{n \times \left(n - 1\right)}2$ 次。证明平凡。

## 代码
```cpp
// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  tp n = bin;
  vector<vector<tp>> a(n + 1, vector<tp>(n + 1, 0));
  for (tp i = 1; i <= n; ++i) {
    for (tp j = 1; j <= n; ++j) ++a[i][bin];
  }
  auto chk = [&]() -> tp {
    for (tp i = 1; i <= n; ++i) {
      for (tp j = 1; j <= n; ++j) {
        if (a[i][j] == 0) return i;
      }
    }
    return 0;
  };
  vector<vector<tp>> tar;
  while (chk() != 0) {
    tp k = chk(), b = k;
    vector<tp> add(n + 1);
    auto fprint = [&](tp i) -> void {
      for (tp j = 1; j <= n; ++j) {
        if (a[i][j] >= 2) { tar.back()[i - 1] = j; add[i % n + 1] = j; --a[i][j]; return; }
      }
      add[i % n + 1] = tar.back()[i - 1] = exchange(add[i], -1);
    };
    tar.push_back(vector<tp>(n));
    fprint(k);
    for (k = k % n + 1; k != b; k = k % n + 1) fprint(k);
    for (tp i = 1; i <= n; ++i) {
      if (add[i] != -1) ++a[i][add[i]];
    }
  }
  for (tp i = 0; i < n; ++i) {
    for (tp k = i; k >= 1; --k) {
      tar.push_back(vector<tp>(n));
      for (tp j = 1; j <= n; ++j) tar.back()[j - 1] = (j + k - 1) % n + 1;
    }
  }
  bin << tar.size() << '\n';
  for (auto& i : tar) {
    for (auto& j : i) bin << j << ' ';
    bin << '\n';
  }
  return 0;
}

void MIST() {
}

// :\ */
```

---

