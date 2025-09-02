# AB Graph

## 题目描述

Your friend Salem is Warawreh's brother and only loves math and geometry problems. He has solved plenty of such problems, but according to Warawreh, in order to graduate from university he has to solve more graph problems. Since Salem is not good with graphs he asked your help with the following problem.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481D/94bc401baa408872926e8e506d8edff2a960c808.png)You are given a complete directed graph with $ n $ vertices without self-loops. In other words, you have $ n $ vertices and each pair of vertices $ u $ and $ v $ ( $ u \neq v $ ) has both directed edges $ (u, v) $ and $ (v, u) $ .

Every directed edge of the graph is labeled with a single character: either 'a' or 'b' (edges $ (u, v) $ and $ (v, u) $ may have different labels).

You are also given an integer $ m > 0 $ . You should find a path of length $ m $ such that the string obtained by writing out edges' labels when going along the path is a palindrome. The length of the path is the number of edges in it.

You can visit the same vertex and the same directed edge any number of times.

## 说明/提示

The graph from the first three test cases is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481D/f91658eafe2032f0ef77ac4d329e5700034dc349.png)In the first test case, the answer sequence is $ [1,2] $ which means that the path is:

 $ $$$1 \xrightarrow{\text{b}} 2 $ $ </p><p>So the string that is obtained by the given path is <span class="tex-font-style-tt">b</span>.</p><p>In the second test case, the answer sequence is  $ \[2,1,3,2\] $  which means that the path is:</p><p> $ $ 2 \xrightarrow{\text{b}} 1 \xrightarrow{\text{a}} 3 \xrightarrow{\text{b}} 2 $ $ </p><p>So the string that is obtained by the given path is <span class="tex-font-style-tt">bab</span>.</p><p>In the third test case, the answer sequence is  $ \[1,3,1,3,1\] $  which means that the path is:</p><p> $ $ 1 \xrightarrow{\text{a}} 3 \xrightarrow{\text{a}} 1 \xrightarrow{\text{a}} 3 \xrightarrow{\text{a}} 1 $ $$$

So the string that is obtained by the given path is aaaa.

The string obtained in the fourth test case is abaaba.

## 样例 #1

### 输入

```
5
3 1
*ba
b*b
ab*
3 3
*ba
b*b
ab*
3 4
*ba
b*b
ab*
4 6
*aaa
b*ba
ab*a
bba*
2 6
*a
b*```

### 输出

```
YES
1 2
YES
2 1 3 2
YES
1 3 1 3 1
YES
1 2 1 3 4 1 4
NO```

# 题解

## 作者：zjjws (赞：11)

这道题，我用的方法是大力分讨 $+$ 构造。

以下用 $p_{x,y}$ 表示有向边 $x\to y$ 的字母。

下列判断有先后，所以每一条判断时前面的一定不成立。

---

$1.$ 当 $m=1$ 时直接输出任意两个不同点即可。

---

$2.$ 当存在 $p_{x,y}=p_{y,x},x!=y$ 的时候，我们可以在这两个点间来回跑来构成任何回文串。

---

那么从此刻开始所有边的反向边都是不同的字母。

---

$3.$ 当 $m$ 是奇数的时候，显然可以在一条边上来回跑。

---

$4.$ 当 $n=2$ 的时候，在前面的条件判断下，显然就已经无解了，因为它只能组成 $ababa\cdots$。

---


我们可以找到这样的一个三元组 $(x,y,z),x!=y!=z$，满足：$p_{x,y}=p_{y,z}$。

首先可以证明任意找选择三个点，都可以找到一个合法的 $x,y,z$ 分配方案，因为总不能这三个点组成的环中三条边两两不同。

然后，利用这个性质，我们就可以构造。

---

$5.$ 当 $\frac{m}{2}$ 是奇数的时候。

我们可以不停地进行 $x\to y\to z\to y\to x\to y\to z\cdots$，构造出 $aabbaa\cdots$，这样是符合条件的解。

---

$6.$ 那么现在只剩下 $\frac{m}{2}$ 是偶数的情况。

我们考虑在构成的回文串的中间划一条线，分成左右两部分。

我们将点插入到边之间，这样就构成了一个完整的序列，例如：

$x\to^{a}y\to^{b}z\cdots$

$x,y,z$ 是点，$a,b$ 是边。

为了方便，我们现在假设 $p_{x,y}=p_{y,z}=a,p_{z,x}=b$（如果 $p_{z,x}=a$ 那就可以直接跑环，但是没必要判这种情况）。

我们把 $y$ 放到之前我说的那条线上，然后自己手模一下，就得到了：

$\cdots z\to^{b} x\to^{a} y\to^{a} z\to^{b} x\cdots$

这是符合条件的一组解。

---

那么所有情况都已经讨论完了，至此，这道题就做完了。

代码就不附了，因为写得比较丑。并且我个人觉得已经写得很清楚了，相信大家都能自己写出来。



---

## 作者：Lynkcat (赞：8)

~~这道 *2000 做了半个多小时，真的是很阴间~~

来讲一下我的阴间做法。

首先如果有 $i,j(i\neq j)$ 满足 $a_{i,j}=a_{j,i}$，那么不管 $m$ 是什么都可以搞定。

如果不存在这两个点，那么当 $m$ 是奇数的时候在任意一条边来回走也可以解决。

重点在当 $m$ 是偶数的时候

![](https://cdn.luogu.com.cn/upload/image_hosting/uvzpqmg4.png)

对于图中 $x,y,z$ 三点，当 $m \bmod 4=0$ 时，可以采用从 $x$ 开始先到 $z$  `abababab……ab`，再从 $x$ 到 $y$ `bababa……ba` 的方法解决。

当 $m \bmod 4=2$ 时，可以采用从 $y$ 开始先到 $x$  `abababab……a`，再从 $x$ 到 $z$ `ababa……ba` 的方法解决。

可以证明，如果找不到 $x,y,z$ 这样的点，那么必然无解，因为走完一条 `b` 边，按照限制，下一条一定是 `a` 边，所以无解。


```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define IOS ios::sync_with_stdio(false)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
//#define int ll
//#define N
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int T,n,m;
string st[2005];
signed main()
{
	IOS;
	cin>>T;
	while (T--)
	{
		int ans=0;
		cin>>n>>m;
		for (int i=1;i<=n;i++)
		{
			cin>>st[i];
			st[i]=' '+st[i];
		}
		for (int i=1;i<=n;i++)
		{
			if (ans) break;
			for (int j=i+1;j<=n;j++)
				if (st[i][j]==st[j][i])
				{
//					puts("YES");
					cout<<"YES"<<endl;
					for (int k=1;k-1<=m;k++)
						if (k%2==1) cout<<i<<" ";
						else cout<<j<<" ";
					cout<<endl;
					ans=1;
					break;
				}
		}
		if (!ans)
		{
			if (m%2==1)
			{
					cout<<"YES"<<endl;
					for (int k=1;k-1<=m;k++)
						if (k%2==1) cout<<1<<" ";
						else cout<<2<<" ";
					cout<<endl;ans=1;
			}
			else 
			{
				for (int i=1;i<=n;i++)
				{
					vector<int>g[2];
					g[0].clear(),g[1].clear();
					for (int j=1;j<=n;j++)
					if (i!=j)
					{
						if (st[i][j]=='b')	
							g[0].push_back(j);
						else g[1].push_back(j);
					}
					if (g[0].size()==0||g[1].size()==0) continue;
					int x=g[0][0],y=g[1][0];
					if (m%4==0)
					{
						cout<<"YES"<<endl;
						cout<<i<<" ";
						for (int i1=1;i1<=m/4;i1++)
							cout<<x<<" "<<i<<" ";
						for (int i1=1;i1<=m/4;i1++)
							cout<<y<<" "<<i<<" ";
						cout<<endl;ans=1;break;
					} else
					{
						cout<<"YES"<<endl;
						cout<<x<<" ";
						for (int i1=1;i1<=m/2;i1++)
							if (i1%2==1) cout<<i<<" ";
							else cout<<x<<" ";
						for (int i1=1;i1<=m/2;i1++)
							if (i1%2==1) cout<<y<<" ";
							else cout<<i<<" ";
						cout<<endl;ans=1;break;
					}
				}
			}
			if (!ans) cout<<"NO"<<endl;
		}
	}
				
}
/*
*/
```


---

## 作者：shicj (赞：2)

分类讨论。

【$1$】当 $m$ 是奇数时，构造 $ \text{abababab} \cdots$ 的串即可满足题意，于是直接交替输出 $1$ 和 $2$ 凑足 $m+1$ 个即可。

【$2$】当 $m$ 是偶数时：

【$2.1$】存在一个点对，来回字母一样，如下图：

![](https://pic1.imgdb.cn/item/67dad1a888c538a9b5c117f9.png)

这时显然和【$1$】相同处理即可。

【$2.2$】存在三个点，路径上字母相同，如下图：

![](https://pic1.imgdb.cn/item/67dad25688c538a9b5c11814.png)

这时构造一个 $\cdots 1\rightarrow2\rightarrow\boxed{1\rightarrow2\rightarrow3}\rightarrow2\rightarrow3\cdots$ 的解即可，具体详见代码。

作为一道细节题，你应该自己实现代码和调试，不建议直接读代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string mp[1001];
int tota[1001];
int totb[1001];
int n,m;
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>mp[i];
		mp[i]=" "+mp[i];
		tota[i]=totb[i]=0;
		for(int j=1;j<=n;j++){
			if(mp[i][j]=='a'){
				tota[j]++;
			}
			else if(mp[i][j]!='b'){
				totb[j]++;
			}
		}
	}
	if(m%2!=0){
		cout<<"YES"<<endl;
		for(int i=1;i<=m+1;i++){
			if(i%2){
				cout<<"1 ";
			}
			else{
				cout<<"2 ";
			}
		}
		cout<<endl;
		return;
	}
	bool flag=false;
	int x=0,y=0,z=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j&&mp[i][j]==mp[j][i]){
				x=i,y=j;
				flag=true;
				break;
			}
		}
		if(flag)break;
	}
	if(x*y!=0){
		cout<<"YES"<<endl;
		for(int i=1;i<=m+1;i++){
			if(i%2){
				cout<<x<<" ";
			}
			else{
				cout<<y<<" ";
			}
		}
		cout<<endl;
		return;
	}
	flag=false;
	x=y=z=0;
	if(n<=2){
		cout<<"NO"<<endl;
		return;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j&&((mp[i][j]=='a'&&tota[j]>=1)||(mp[i][j]=='b'&&totb[j]>=1))){
				for(int k=1;k<=n;k++){
					if(mp[j][k]==mp[i][j]){
						x=i,y=j,z=k;
					}
				}
				if(x*y*z!=0){
					flag=true;
					break;
				}
			}
		}
		if(flag)break;
	}
	if(x*y*z==0){
		cout<<"NO"<<endl;
		return;
	}
//	cerr<<x<<" "<<y<<" "<<z<<endl;
	if((m-2)/2%2==0){
		cout<<"YES"<<endl;
		for(int i=1;i<=m/2-1;i++){
			if(i%2){
				cout<<x<<" ";
			}
			else{
				cout<<y<<" ";
			}
		}
		cout<<x<<" "<<y<<" "<<z<<" ";
		for(int i=m/2+3;i<=m+1;i++){
			if(i%2){
				cout<<z<<" ";
			}
			else{
				cout<<y<<" ";
			}
		}
		cout<<endl;
		return;
	}
	else{
		cout<<"YES"<<endl;
		for(int i=1;i<=m/2-1;i++){
			if(i%2){
				cout<<y<<" ";
			}
			else{
				cout<<x<<" ";
			}
		}
		cout<<x<<" "<<y<<" "<<z<<" ";
		for(int i=m/2+3;i<=m+1;i++){
			if(i%2){
				cout<<y<<" ";
			}
			else{
				cout<<z<<" ";
			}
		}
		cout<<endl;
		return;
	}
	cout<<"NO"<<endl;
}
signed main(){
#ifdef USE_FILE_IO
	freopen("code.in","r",stdin);
	cerr<<"[File IO]"<<endl;
#endif
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Little09 (赞：2)

这是一道构造题，构造方案不唯一，我在这里提供一下我在场上想到的方法。

- 有一条边的两个字母一样。这种情况在这条边上来回走就好了。

- 剩下情况满足每条边的两个字母都不一样。

   - 当长度为奇数时，在一条边来回走就好了。

   - 当长度为偶数时，继续讨论。
       
       - 当 $n=2$ 时，无解。
       
       - 当 $n≥3$ 时，我们考虑绕任意三个点构成的三元环一直走。因为回文串长度为偶数，观察发现满足**中间两个字符**相等，就可以实现回文。根据抽屉原理，三元环中三条边，至少有两边字符相同。把这两条边作为中间两个字符即可。
      
这样这题就构造完了。代码就不用给了吧。

---

## 作者：Determination_Y (赞：1)

# CF1481D AB Graph 题解

### 【思路】

首先有几个显而易见的东西。

1. 如果存在两个点，他们之间的两条边字母相同，那么一定有解（在两个点之间跳。）

2. 否则，这张图的邻接矩阵一定长成这样：
   
   ```
   * a b a
   b * a b
   a b * a
   b a b *
   ```
   
   沿着中间的斜线看，左右两边完全相反。

然后找这种图的特点。

* 如果 $ n=2 $
  
  * 如果 $ m $ 是奇数，有解。
  
  * 如果 $ m $ 是偶数，无解。

* 如果 $ n=3 $，必然有解，证明放在最后。

所以说，对于所有 $ n \ge 3 $，我们直接选择前三个点即可。

### 【代码】

```cpp
#include <bits/stdc++.h>
using namespace std;

char a[1005][1005];
int T,n,m;

int main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			getchar();
			for(int j=1;j<=n;j++){
				scanf("%c",&a[i][j]);
			}
		}
		
		//如果存在两个点，他们之间的两条边字母相同，那么一定有解（在两个点之间跳。）
		bool flag_equ=false;
		int flag1=0,flag2=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(a[i][j]==a[j][i]){
					flag_equ=true;
					flag1=i;
					flag2=j;
					break;
				}
			}
		}
		if(flag_equ==true){
			puts("YES");
			for(int i=1;i<=m+1;i++){
				printf("%d ",i&1?flag1:flag2); 
			}puts("");
		}else{
			
			//如果 n=2
			if(n==2){
				if(m&1){
					puts("YES");
					for(int i=1;i<=m+1;i++){
						printf("%d ",i&1?1:2); 
					}puts("");
				}else{
					puts("NO");
				}
			}else{
				//如果 n>=3，必然有解。选择前三个点。 
				//如果 1 -> 2 -> 3 -> 1 相等，那么直接输出
				if(a[1][2]==a[2][3] and a[2][3]==a[3][1]){
					puts("YES");
					for(int i=1;i<=m+1;i++){
						printf("%d ",(i-1)%3+1); 
					}puts("");
				}else{
					puts("YES");
					//定位3个点.
					//P1 有两个a的出度，两个b的入度 
					int P1;
					if(a[1][2]==a[1][3] and a[1][3]=='a' and a[2][1]==a[3][1] and a[3][1]=='b') P1=1;
					if(a[2][1]==a[2][3] and a[2][3]=='a' and a[1][2]==a[3][2] and a[3][2]=='b') P1=2;
					if(a[3][1]==a[3][2] and a[3][2]=='a' and a[1][3]==a[2][3] and a[2][3]=='b') P1=3;
					
					//P2 有两个b的出度，两个a的入度 
					int P2;
					if(a[1][2]==a[1][3] and a[1][3]=='b' and a[2][1]==a[3][1] and a[3][1]=='a') P2=1;
					if(a[2][1]==a[2][3] and a[2][3]=='b' and a[1][2]==a[3][2] and a[3][2]=='a') P2=2;
					if(a[3][1]==a[3][2] and a[3][2]=='b' and a[1][3]==a[2][3] and a[2][3]=='a') P2=3;
					
					//P3 是剩下那一个点，入度出度都为一a一b 
					int P3;
					P3=6-P1-P2;
					
					
					if(m&1){          //如果 m 是奇数，那么不停跳 ab/ba 即可
						for(int i=1;i<=m+1;i++){
							printf("%d ",i&1?P1:P2);
						}puts("");
					}else if(m%4==0){ //如果 m 可以被 4 整除，那么不停跳 abba/baab 即可
						for(int i=1;i<=m+1;i++){
							if(i%4==1) printf("%d ",P3); 
							if(i%4==2) printf("%d ",P2); 
							if(i%4==3) printf("%d ",P3); 
							if(i%4==0) printf("%d ",P1);
						}puts("");
					}else{            //如果 m 不能被 4 整除，但是可以被 2 整除，那么先跳一个 a/b，再不停跳 abba/baab，最后再跳一个 a/b 即可
						printf("%d ",P1);
						for(int i=2;i<=m;i++){
							if((i-1)%4==1) printf("%d ",P3);
							if((i-1)%4==2) printf("%d ",P2);
							if((i-1)%4==3) printf("%d ",P3);
							if((i-1)%4==0) printf("%d ",P1);
						}printf("%d ",P2);
						puts("");
					} 
				}
			}
		}
		
	}
	return 0;
}

```



### 【证明】

对于 $ n=3 $ 的情况下，必然有解。

1. 假设邻接矩阵是下面这几种情况：
   
   ```
      * a b   |   * b a
      b * a   |   a * b
      a b *   |   b a *
   ```
   
   那么只要不停地跳 $ a/b $ 即可，输出为 `1 2 3 1 2 3 1 2 3 ...`

2. 假设邻接矩阵是下面这几种情况：
   
   ```
      * a a   |   * b b
      b * b   |   a * a
      b a *   |   a b *
   ```
   
   * 如果 $ m $ 是奇数，那么不停跳 $ ab/ba $ 即可，输出为 `1 2 1 2 1 2 ...`
   
   * 如果 $ m $ 被 $ 4 $ 整除，那么不停跳 $ abba/baab $ 即可，输出为 `2 3 2 1 2 3 2 1 2 3 2 1 2...`
   
   * 如果 $ m $ 不能被 $ 4 $ 整除，但是可以被 $ 2 $ 整除，那么先跳一个 $ a/b $，再不停跳 $ abba/baab $，最后再跳一个 $ a/b $ 即可，输出为 `1 2 3 2 1 2 3 2 1 2 3 2 1 2...3 2 1 2 3`

3. 假设邻接矩阵是下面这几种情况：
   
   ```
      * a a   |   * b b   |   * a b   |   * b a
      b * a   |   a * b   |   b * b   |   b * a
      b b *   |   a a *   |   a a *   |   b a *
   ```
   
   套路和上边的一样，可以自己画图看看。

---

## 作者：huayucaiji (赞：1)

~~我是SB~~。

比赛的时候由于有一种情况没有输出 `Yes`，挂了，赛后加上就过了。

而且话说这天早上刚考完 WC2021。不觉得[WC的这道题](https://www.luogu.com.cn/problem/P7323)和他很像吗。我当时吓出一身冷汗。

好啦不说废话，来分析本题。我们不要把它想得过于复杂，我们分成几种情况。我们令 $w(u,v)$ 为从 $u$ 出发，到 $v$ 的这条边上的字符，令 $x,y$ 表示这两种字符。

如果存在某两点 $u,v$，使得 $w(u,v)$ 和 $w(v,u)$ 相同，那么我们可以对于任意 $m$，构造出形如 $u,v,u,v,u,\cdots$ 的答案，最后的串为 $x,x,x\cdots$。显然回文。

如果不存在，说明一定是两点之间的边，有为 `a` 的，也有为 `b` 的。如果 $m$ 为奇数，那么随便找两点我们可以构造如下答案 $u,v,u,v,\cdots,u,v$，那么经过的边形成的串为 $x,y,x,\cdots,y,x$，明显回文。

我们只需要处理剩下的 $m$ 为偶数的情况。我们需要找到如下图的结构：

![](https://images.cnblogs.com/cnblogs_com/huayucaiji/1929202/o_210206054356D.png)

我们可以在 $O(n^2)$ 的时间内找到这样的 $1,2,3$。易证，在目前讨论的大前提下，对于任意 $n\geq 3$，都能至少找出一组这样的结构。我们可以构造出以下两种答案，根据 $m$ 模 $4$ 的余数决定选择哪一种。

- 第一种，经过的点为 $3,1,2,1,3,1,2,3,\cdots,3,1,2,1,3,1,2$，得到的串为 $x,x,y,y,x,x,\cdots,x,x$。显然回文。
- 第二种，经过的点为 $1,3,1,2,1,3,1,2,\cdots,1,3,1,2,1$，得到的串为 $y,x,x,y,y,x,x,y,\cdots,y,x,x,y$。显然回文。

其他情况输出 `NO`。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=1e3+10; 

int n,m;
char ch[MAXN][MAXN];

signed main() {
	int t=read();
	while(t--) {
		n=read();
		m=read();
		
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=n;j++) {
				cin>>ch[i][j];
			}
		}
		
		bool flag=0;
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=n;j++) {
				if(i!=j&&ch[i][j]==ch[j][i]) {
					printf("YES\n");
					for(int k=1;k<=m;k+=2) {
						printf("%d %d ",i,j);
					}
					if((m+1)&1) {
						printf("%d\n",i);
					}
					else {
						printf("\n");
					}
					flag=1;
					break;
				}
			}
			if(flag) {
				break;
			}
		}
		if(flag) {
			continue;
		}
		if(m&1) {
			printf("YES\n");
			for(int i=1;i<=m;i+=2) {
				printf("1 2 ");
			}
			cout<<endl;
			continue;
		}
		int a,b,c;
		bool fa=0,fb=0,f=0;
		for(int i=1;i<=n;i++) {
			fa=fb=0;
			for(int j=1;j<=n;j++) {
				if(ch[i][j]=='a') {
					fa=1;
					a=j;
				}
				if(ch[j][i]=='a') {
					fb=1;
					b=j;
				}
			}
			if(fa&&fb) {
				c=i;
				f=1;
				break;
			}
		}
		if(!f) {
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		if(m%4==0) {
			for(int i=0;i+4<=m;i+=4) {
				printf("%d %d %d %d ",c,b,c,a);
			}
			printf("%d\n",c);
		}
		else {
			for(int i=0;i+4<=m;i+=4) {
				printf("%d %d %d %d ",b,c,a,c);
			}
			printf("%d %d %d\n",b,c,a);
		}
	}
	return 0;
}

```


---

## 作者：Day_Tao (赞：0)

小清新分讨 + 构造。

考虑 $m$ 为奇数，可以直接在一条边上来回跳。

$m$ 为偶数时，如果有双向边都是同色时，也直接来回跳即可。考虑 $m$ 为偶数且不存在同色双向边如何构造。考虑一个三元环，必定存在形如

![](https://cdn.luogu.com.cn/upload/image_hosting/ec2ku9x1.png) 

的一组。这样的话就可以构造出 `aabbaa...` 和 `abbaabba...` 的方案了。对于 $m\bmod4$ 分讨一下即可。

无解当且仅当 $n=2\wedge m\operatorname{and}1=1\wedge c_{2,1}\neq c_{1,2}$。

code：

```cpp
int n,m;char c[N][N];
inline void solve(int x,int y,int z){
	if(m%4){
		for(int i=1;i<=m/4;i++)printf("%lld %lld %lld %lld ",x,y,z,y);
		printf("%lld %lld %lld\n",x,y,z);
	}
	else{
		for(int i=1;i<=m/4;i++)printf("%lld %lld %lld %lld ",y,z,y,x);
		printf("%lld\n",y);
	}
}
inline void SOLVE(){
	n=rd(),m=rd();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>c[i][j];
	if(n==2&&c[1][2]!=c[2][1]&&!(m&1)){puts("NO");return ;}
	puts("YES");
	if(m&1){
		for(int i=1;i<=m/2+1;i++)printf("%lld %lld ",1ll,2ll);
		puts("");
	}
	else{
		for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(c[i][j]==c[j][i]){
			for(int k=1;k<=m/2;k++)printf("%lld %lld ",i,j);
			printf("%lld\n",i);return ;}	
		if(c[1][2]==c[2][3])solve(1,2,3);
		else if(c[2][3]==c[3][1])solve(2,3,1);
		else solve(3,1,2);
	}
	return ;
}
```

---

## 作者：Priestess_SLG (赞：0)

~~史中食~~

考虑巨大分类讨论（后面需要满足前面的不满足）：

+ $m=1$：输出任意一条边。
+ $m\equiv 1\pmod 2$ ：正反循环输出一条边。
+ $\exists x,y,a_{x,y}=a_{y,x}$：一直输出这一条边。
+ $n=2$：无解。
+ 找到任意一个三元环，若三条边相等则反复输出这三条边。
+ 否则必然存在两条连续的边相等，然后对 $m\bmod 3$ 的值分三类情况讨论：
  + 若 $m\equiv0\pmod 3$ 则构造 `abaabaabaaba` 或 `babbabbabbab`。
  + 若 $m\equiv1\pmod 3$ 则构造 `baabaabaab` 或 `abbabbabba`。
  + 若 $m\equiv2\pmod 3$ 则构造 `aabaabaabaabaa` 或 `bbabbabbabbabb`。

然后就做完了，但是代码很难写。

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define eb emplace_back
#define pb push_back
using namespace std;
char a[2010][2010];
signed main(){
    int T;
    cin>>T;
    int tc=T,ca=1;
    while(T--){
        int n,m;cin>>n>>m;
        for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        cin>>a[i][j];
        // if(tc==320){
        //     ++ca;
        //     if(ca==58){
        //         cout<<n<<' '<<m<<'\n';
        //         for(int i=1;i<=n;++i,cout<<'\n')
        //         for(int j=1;j<=n;++j)cout<<a[i][j];
        //         return 0;
        //     }else continue;
        // }
        if(m==1)cout<<"YES\n1 2\n";
        else if(m&1){
            cout<<"YES\n";
            for(int i=1;i<=m/2+1;++i)cout<<"1 2 ";
            cout<<'\n';
        }else{
            int ok=0,X,Y;
            for(int i=1;i<n;++i)
            for(int j=i+1;j<=n;++j)
            if(a[i][j]==a[j][i]){
                ok=1;
                X=i,Y=j;
                goto ee;
            }ee:;
            if(ok){
                cout<<"YES\n";
                for(int i=1;i<=m/2;++i)cout<<X<<' '<<Y<<' ';
                cout<<X;
                cout<<'\n';
            }else{
                if(n>2){
                    cout<<"YES\n";
                    char x1=a[1][2],x2=a[2][3],x3=a[3][1];
                    if(x1==x2&&x1==x3){
                        for(int i=0;i<=m;++i){
                            if(i%3==0)cout<<"1 ";
                            else if(i%3==1)cout<<"2 ";
                            else cout<<"3 ";
                        }
                        cout<<'\n';
                        continue;
                    }
                    int cnv=0;
                    if(x1=='a')++cnv;
                    if(x2=='a')++cnv;
                    if(x3=='a')++cnv;
                    if(cnv<2){
                        if(x1=='a')x1='b';else x1='a';
                        if(x2=='a')x2='b';else x2='a';
                        if(x3=='a')x3='b';else x3='a';
                    }
                    switch(m%3){
                    case 0:
                        if(x1=='a'&&x2=='b'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"1 ";
                                else if(i%3==1)cout<<"2 ";
                                else cout<<"3 ";
                            }
                            cout<<'\n';
                        }
                        if(x2=='a'&&x3=='b'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"2 ";
                                else if(i%3==1)cout<<"3 ";
                                else cout<<"1 ";
                            }
                            cout<<'\n';
                        }
                        if(x3=='a'&&x1=='b'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"3 ";
                                else if(i%3==1)cout<<"1 ";
                                else cout<<"2 ";
                            }
                            cout<<'\n';
                        }
                        break;
                    case 2:
                        if(x1=='a'&&x2=='a'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"1 ";
                                else if(i%3==1)cout<<"2 ";
                                else cout<<"3 ";
                            }
                            cout<<'\n';
                        }
                        if(x2=='a'&&x3=='a'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"2 ";
                                else if(i%3==1)cout<<"3 ";
                                else cout<<"1 ";
                            }
                            cout<<'\n';
                        }
                        if(x3=='a'&&x1=='a'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"3 ";
                                else if(i%3==1)cout<<"1 ";
                                else cout<<"2 ";
                            }
                            cout<<'\n';
                        }
                        break;
                    default:
                        if(x1=='b'&&x2=='a'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"1 ";
                                else if(i%3==1)cout<<"2 ";
                                else cout<<"3 ";
                            }
                            cout<<'\n';
                        }
                        if(x2=='b'&&x3=='a'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"2 ";
                                else if(i%3==1)cout<<"3 ";
                                else cout<<"1 ";
                            }
                            cout<<'\n';
                        }
                        if(x3=='b'&&x1=='a'){
                            for(int i=0;i<=m;++i){
                                if(i%3==0)cout<<"3 ";
                                else if(i%3==1)cout<<"1 ";
                                else cout<<"2 ";
                            }
                            cout<<'\n';
                        }
                    }
                }else{
                    cout<<"NO\n";
                }
            }
        }
    }
}
```

---

## 作者：TernaryTree (赞：0)

简单 $2000$。

可以重复经过边或点，就随便做了。

如果 $i$ 到 $j$ 的字符等于 $j$ 到 $i$ 的字符，或者 $m$ 是奇数，就直接在 $i,j$ 之间反复横跳就行。

所以我们只用考虑所有 $i$ 到 $j$ 的字符不等于 $j$ 到 $i$ 的字符，并且 $m$ 为偶数。

如果存在 $i$ 有一条入边等于出边（即存在两条字符不相同的出边）是能构造的。设入边前面的点是 $x$，出边出去的点是 $y$，那么我们在 $x,i,y$ 之间反复横跳。不存在就构造不了了，因为我们连长度为 $2$ 的回文串都构造不出来，构造偶数更不可能。

代码不放了。

---

## 作者：DaiRuiChen007 (赞：0)

# CF1481D 题解



## 思路分析

[Problem Link](https://codeforces.com/problemset/problem/1481/D)

首先，如果有一对点 $(i,j)$ 正向和反向字母相同，那么重复 $i\to j\to i\to j\to\cdots$ 即可。

否则，每对点之间的两条边一定是 $\texttt a,\texttt b$ 各一个，假如 $m\bmod 2=1$，那么随便找一对点 $(i,j)$ 重复 $i\to j\to i\to j\to\cdots$ 即可。

剩下的只有 $2\mid m$ 的情况，考虑得到的字符串中第 $\dfrac m2$ 个和第 $\dfrac m2+1$ 个字符，显然这两个字符需要相同，而且这两条边必然是连接三个不同的节点，因此找到一组 $(i,j,k)$ 使得 $j\to i=i\to k=\texttt a $（事实上 $j\gets i=j\gets k=\texttt b$，因此找 $\texttt a$ 或 $\texttt b$）没有区别。

接下来考虑 $\dfrac m2$ 的奇偶性：

- 若 $4\mid m$，那么形成的字符串形如 $\texttt{bababa}\cdots\texttt{ba}+\texttt{ab}\cdots\texttt{ababab}$，因此行走的路径应该是 $i\to (j\to i\to j\to\cdots \to j\to i)\to (k\to i\to k\to\cdots\to i\to k)$。
- 若 $4\nmid m$，那么形成的字符串形如 $\texttt{ababa}\cdots \texttt{ba}+\texttt{ab}\cdots\texttt{babab}$，因此行走的路径应该是 $j\to (i\to j\to\cdots i\to j\to i)\to (k\to i\to k\to\cdots i\to k)$。

分情况进行模拟即可。

时间复杂度 $\Theta(n^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1001;
vector <int> in[MAXN],out[MAXN];
char ch[MAXN][MAXN];
inline void solve() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) {
		scanf("%s",ch[i]+1);
		in[i].clear(),out[i].clear();
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			if(i==j) continue;
			if(ch[i][j]==ch[j][i]||(m%2!=0)) {
				puts("YES");
				for(int k=0;k<=m;++k) {
					printf("%d ",(k%2==1)?i:j);
				}
				puts("");
				return ;
			}
			if(ch[i][j]=='a') {
				in[j].push_back(i);
				out[i].push_back(j);
			}
		}
	}
	for(int i=1;i<=n;++i) {
		if(in[i].empty()||out[i].empty()) continue;
		puts("YES");
		int j=in[i].front(),k=out[i].front();
		if(m%4==0) {
			printf("%d ",i);
			for(int t=1;t<=(m/4);++t) printf("%d %d ",j,i);
			for(int t=1;t<=(m/4);++t) printf("%d %d ",k,i);
		} else {
			printf("%d ",j);
			for(int t=1;t<=(m/2);++t) printf("%d ",(t%2==1)?i:j);
			for(int t=1;t<=(m/2);++t) printf("%d ",(t%2==1)?k:i);
		}
		puts("");
		return ;
	}
	puts("NO");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：xuezhe (赞：0)

考虑分类讨论。

若 $m$ 为奇数，则直接在一条边来回走就好了。

否则若存在一条边满足它上面的字符与反向边上的字符相同，在这条边上来回走就好了。

否则每条边都与其反向边上的字符不同，考虑寻找一个点 $A$，满足它向点 $B$ 连出的边上的字母为 $\texttt{a}$，向点 $C$ 连出的字母为 $\texttt{b}$，则可以这样构造：若长度为 $4$ 的倍数，则走形如 $A \rightarrow B \rightarrow A \rightarrow C \rightarrow A \rightarrow \dots$ 的路径，否则走形如 $B \rightarrow A \rightarrow C \rightarrow A \rightarrow B \rightarrow \dots$ 的路径。

若上述情况都无法构造出，则每条路径都必然是 $\texttt{a}$ 与 $\texttt{b}$ 交错的路径，必然无法产生长度为偶数的回文串，故无解。

Code:

```cpp
int T,n,m;
char g[1005][1005];
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i)
            cin>>(g[i]+1);
        if(m==1){
            puts("YES\n1 2");
            continue;
        }
        if(m&1){
            puts("YES");
            for(int i=0;i<=m;++i)
                printf("%d ",(i&1)?(1):(2));
            putchar(10);
            continue;
        }
        bool flg=false;
        for(int i=1;i<=n && !flg;++i)
            for(int j=i+1;j<=n && !flg;++j){
                if(g[i][j]==g[j][i]){
                    flg=true;
                    puts("YES");
                    for(int k=0;k<=m;++k)
                        printf("%d ",(k&1)?(i):(j));
                    putchar(10);
                }
            }
        if(flg)
            continue;
        for(int i=1;i<=n;++i){
            int c[2]={};
            for(int j=1;j<=n;++j)
                if(i!=j)
                    c[g[i][j]-'a']=j;
            if(c[0] && c[1]){
                flg=true;
                puts("YES");
                if(!(m%4)){
                    for(int k=0;k<=m;++k){
                        switch(k%4){
                            case 0:{
                                printf("%d ",i);
                            }break;
                            case 1:{
                                printf("%d ",c[0]);
                            }break;
                            case 2:{
                                printf("%d ",i);
                            }break;
                            case 3:{
                                printf("%d ",c[1]);
                            }break;
                        }
                    }
                }else{
                    for(int k=0;k<=m;++k){
                        switch(k%4){
                            case 0:{
                                printf("%d ",c[0]);
                            }break;
                            case 1:{
                                printf("%d ",i);
                            }break;
                            case 2:{
                                printf("%d ",c[1]);
                            }break;
                            case 3:{
                                printf("%d ",i);
                            }break;
                        }
                    }
                }
                putchar(10);
                break;
            }
        }
        if(!flg)
            puts("NO");
    }
    return 0;
}
```



---

## 作者：Theophania (赞：0)

提供一种和官方题解不一样的做法。

由于边上只有两种字符，3 条边组成的环只有 4 种可能：`aaa`，`aab`，`abb`，`bbb`。第一种和第四种可以构造出任意长度的回文串是显然的，而第二种和第三种是等价的。很容易发现，第二种情况也可以构造出任意长度的回文串：当长度为奇数时以 `b` 为对称轴，当长度为偶数时对称轴在两个 `a` 中间。

所以当 $n\ge 3$ 时可以构造出任意的回文串，下面看 $n=2$ 的情况。

$n=2$ 的时候只存在一个环，有两条边，如果字符一样就可以构造出任意长度的回文串，如果不一样就只能构造出奇数长度的回文串。

代码细节稍微有点多。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 9;
char a[maxn][maxn];
signed main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%s", a[i] + 1);
        if (n == 2)
        {
            if (a[1][2] == a[2][1])
            {
                printf("YES\n");
                for (int i = 0; i <= m; ++i)
                    printf("%d ", (i & 1) + 1);
                printf("\n");
            }
            else
            {
                if (m % 2 == 0)
                    printf("NO\n");
                else
                {
                    printf("YES\n");
                    for (int i = 0; i <= m; ++i)
                        printf("%d ", (i & 1) + 1);
                    printf("\n");
                }
            }
        }
        else
        {
            if (a[1][2] == a[2][3] && a[1][2] == a[3][1])
            {
                printf("YES\n");
                for (int i = 0; i <= m; ++i)
                    printf("%d ", (i % 3) + 1);
                printf("\n");
            }
            else
            {
                int x, y, z, cnt = (m - 1) / 2;
                if (a[1][2] == a[2][3])
                    x = 3, y = 1, z = 2;
                else if (a[1][2] == a[3][1])
                    x = 2, y = 3, z = 1;
                else
                    x = 1, y = 2, z = 3;
                deque<int> ans;
                if (m & 1)
                {
                    ans.push_back(x);
                    ans.push_back(y);
                }
                else
                {
                    ans.push_back(y);
                    ans.push_back(z);
                    ans.push_back(x);
                }
                for (int i = 1; i <= cnt; ++i)
                {
                    int now = ans.back();
                    if (now == 3)
                        ans.push_back(1);
                    else
                        ans.push_back(now + 1);
                }
                for (int i = 1; i <= cnt; ++i)
                {
                    int now = ans.front();
                    if (now == 1)
                        ans.push_front(3);
                    else
                        ans.push_front(now - 1);
                }
                printf("YES\n");
                for (auto i : ans)
                    printf("%d ", i);
                printf("\n");
            }
        }
    }
    return 0;
}
```


---

