# Beingawesomeism

## 题目描述

You are an all-powerful being and you have created a rectangular world. In fact, your world is so bland that it could be represented by a $ r \times c $ grid. Each cell on the grid represents a country. Each country has a dominant religion. There are only two religions in your world. One of the religions is called Beingawesomeism, who do good for the sake of being good. The other religion is called Pushingittoofarism, who do murders for the sake of being bad.

Oh, and you are actually not really all-powerful. You just have one power, which you can use infinitely many times! Your power involves missionary groups. When a missionary group of a certain country, say $ a $ , passes by another country $ b $ , they change the dominant religion of country $ b $ to the dominant religion of country $ a $ .

In particular, a single use of your power is this:

- You choose a horizontal $ 1 \times x $ subgrid or a vertical $ x \times 1 $ subgrid. That value of $ x $ is up to you;
- You choose a direction $ d $ . If you chose a horizontal subgrid, your choices will either be NORTH or SOUTH. If you choose a vertical subgrid, your choices will either be EAST or WEST;
- You choose the number $ s $ of steps;
- You command each country in the subgrid to send a missionary group that will travel $ s $ steps towards direction $ d $ . In each step, they will visit (and in effect convert the dominant religion of) all $ s $ countries they pass through, as detailed above.
- The parameters $ x $ , $ d $ , $ s $ must be chosen in such a way that any of the missionary groups won't leave the grid.

The following image illustrates one possible single usage of your power. Here, A represents a country with dominant religion Beingawesomeism and P represents a country with dominant religion Pushingittoofarism. Here, we've chosen a $ 1 \times 4 $ subgrid, the direction NORTH, and $ s = 2 $ steps.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/28f64f5dd2e3bc2e91270492183ebd3ec34bb40a.png)You are a being which believes in free will, for the most part. However, you just really want to stop receiving murders that are attributed to your name. Hence, you decide to use your powers and try to make Beingawesomeism the dominant religion in every country.

What is the minimum number of usages of your power needed to convert everyone to Beingawesomeism?

With god, nothing is impossible. But maybe you're not god? If it is impossible to make Beingawesomeism the dominant religion in all countries, you must also admit your mortality and say so.

## 说明/提示

In the first test case, it can be done in two usages, as follows:

Usage 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/5aa9a3e986e676e61c160aa9ee967c57ee4ce5c6.png)Usage 2:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/100b5a5b446d54b176a5d3a43e9d6e720401be64.png)In the second test case, it can be done with just one usage of the power.

In the third test case, it is impossible to convert everyone to Beingawesomeism, so the answer is "MORTAL".

## 样例 #1

### 输入

```
4
7 8
AAPAAAAA
PPPPAAAA
PPPPAAAA
APAAPPPP
APAPPAPP
AAAAPPAP
AAAAPPAA
6 5
AAAAA
AAAAA
AAPAA
AAPAP
AAAPP
AAAPP
4 4
PPPP
PPPP
PPPP
PPPP
3 4
PPPP
PAAP
PPPP
```

### 输出

```
2
1
MORTAL
4
```

# 题解

## 作者：_6_awa (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1280B)

题目大意：每次可以选定一行或一列的若干个字符从某一个方向全部复制成刚才那一行，问要进行多少次才能全部复制成 `A`。

题目大意：简单来说，其实本题只有六种情况：$0,1,2,3,4$ 或者无解。

首先是 $0$ 和无解的情况，都比较好算，一个全盘 `A`，一个全盘 `P`。特判一下即可。

然后还有 $1$ 的情况。这种情况必须有一边全部是 `A` 才能进行复制。因为如果不全是 `A`，那么还要再多花一步来将那些替换，很明显已经不符合条件了。

$2$ 的情况有两种：一种是占据其中一个角，一种是占掉中间全部的一条线。很明显只有这些才满足条件。

最后是 $3$ 和 $4$ 的情况。很明显，$4$ 边上没有一个 `A`，剩下的就是 $3$ 的情况了。所有情况都枚举了，最后完美输出。

### AC Code:

```cpp
#include <iostream>
using namespace std;
int t,n,m;
char a[423][311];
int main()
{
    cin >> t;
    while(t --)
    {
        cin >> n >> m;
        int sum = 0,f = 4,b = 0,b2 = 0,b3 = 0,b4 = 0,sum2 = 0;
        for(int i = 1;i <= n;i ++)
            for(int j = 1;j <= m;j ++)
            {
                cin >> a[i][j];
                if(a[i][j] == 'A')sum ++;
                else sum2 ++;
                if(((i == 1 && j == 1) || (i == 1 && j == m) || (i == n && j == 1) || (i == n && j == m)) && a[i][j] == 'A')f = 2;//角落
                if((i == 1 || j == 1 || i == n || j == m) && a[i][j] == 'A')f = min(f,3);//边上点
                if(i == 1 && a[i][j] == 'A')b ++;//边上线
                if(i == n && a[i][j] == 'A')b2 ++;
                if(j == 1 && a[i][j] == 'A')b3 ++;
                if(j == m && a[i][j] == 'A')b4 ++;
            }
        for(int i = 1;i <= n;i ++)
        {
        	int num = 0;
        	for(int j = 1;j <= m;j ++)
        		if(a[i][j] == 'A')num ++;
        	if(num == m)f = 2;
		}//中间线判断
		for(int j = 1;j <= m;j ++)
        {
        	int num = 0;
        	for(int i = 1;i <= n;i ++)
        		if(a[i][j] == 'A')num ++;
        	if(num == n)f = 2;
		}
        if(b == m || b2 == m || b3 == n || b4 == n)f = 1;
        if(sum == 0)cout << "MORTAL\n";//全为P
        else if(sum2 == 0)cout << "0\n";//全为A
        else cout << f << endl;//否则输出
    }
}
```

---

## 作者：weizhiyonghu (赞：4)

首先看到数据范围：$1 \le T \le 2 \times 10^4,1 \le n,m \le 60$。保守估计评测机速度为 $10^7$ 次计算/秒，可以发现留给每组询问的时间最多就是 $\frac{10^7}{2 \times 10^4}=5 \times 10^2$，也就是大约 ${\rm \Theta}{(nm)}$ 的时间复杂度。

那么，考虑分类讨论，对每一个元素 $(x,y)$ 求出 ${\rm\Theta}{(1)}$ 判定式，进而解决问题。

(1):显然，如果所有位置本来就是 `A` ，那么直接输出 `0` .

(2):如果这个矩形有一条边全都是 `A` ，即若 $[(1,i)=\texttt{A}]_{1\le i \le n},[(n,i)=\texttt{A}]_{1\le i \le n},[(i,1)=\texttt{A}]_{1\le i \le m},[(i,m)=\texttt{A}]_{1\le i \le m}$ 其中之一满足，则只用把这一整列向一个方向移动就能全部变成 `A` ，此时输出 `1` .

(3):如果这个矩形四顶点上有任意一点为 `A` ，即满足 $[(1,1)=\texttt{A}],[(1,m)=\texttt{A}],[(n,1)=\texttt{A}],[(n,m)=\texttt{A}]$ 其中之一，可以将这个点先向所在边的垂直方向拉出一整列，再平行该边推过去即可。此时输出 `2` .

(4):如果这个矩形内部有长为 $n$ ，竖直方向的全 `A` 列或长为 $m$ ，水平方向的全 `A` 行，那么只需要将这个列/行向垂直于该列/行的方向平推即可。此时输出 `2`.

(5):如果这个矩形四条边上有任意一点为 `A` ，即满足 $[(1,i)=\texttt{A}]_{1 \le i \le m},[(i,m)=\texttt{A}]_{1 \le i \le n},[(n,i)=\texttt{A}]_{1 \le i \le m},[(i,1)=\texttt{A}]_{1 \le i \le n}$ 其中之一，那么可以将其先垂直于该边拉出一列，然后平行于该边向两侧平推，此时输出 `3`.

(6):其余情况，除了全 `P` 矩阵外均输出 `4`。因为无论哪个元素，只要向两边分别平推即可得到一行，将一行垂直推即可获得整个矩阵。

(7):全 `P` 矩阵，输出 `MORTAL` .

那么下面上代码：
```cpp
#include <iostream>
#include <string.h>
#include <cstring>
#define ri register int
#define sp1 cin.tie(0),cout.tie(0)
#define sp2 ios::sync_with_stdio(0)

using namespace std;
const int N = 65;
int T,n,m;char mp[N][N];

inline bool check_line()
{
	bool flg1,flg2,flg3,flg4;
	flg1=flg2=flg3=flg4 = true;
	for(ri i = 1;i <= m;i++)
		flg1 = flg1 & (mp[1][i] == 'A'),
		flg2 = flg2 & (mp[n][i] == 'A');
	for(ri j = 1;j <= n;j++)
		flg3 = flg3 & (mp[j][1] == 'A'),
		flg4 = flg4 & (mp[j][m] == 'A');
	if(flg1||flg2||flg3||flg4) return true;
	else return false;
}

inline bool check_r()//r
{
	for(ri i = 1;i <= n;i++)
	{
		bool flg = true;
		for(ri j = 1;j <= m;j++)
			if(mp[i][j] == 'P')
				{flg=false;break;}
		if(flg == true) return true; 
	}
	return false;
}

inline bool check_c()
{
	for(ri i = 1;i <= m;i++)
	{
		bool flg = true;
		for(ri j = 1;j <= n;j++)
			if(mp[j][i] == 'P')
			{flg = false;break;}
		if(flg == true) return true;
	}
	return false;
}

int main()
{
	freopen("in.txt","r",stdin);
	sp1,sp2;cin >> T;
	while(T --)
	{
		cin >> n >> m;bool is_all = true,is_none = true;
		for(ri i = 1;i <= n;i++)
			for(ri j = 1;j <= m;j++)
				cin >> mp[i][j],
				is_all &= (mp[i][j] == 'A'),
				is_none &= (mp[i][j] == 'P');
		if(is_none == true) {printf("MORTAL\n");continue;} 
		if(is_all == true) {printf("0\n");continue;}
		bool flg = check_line();
		if(flg == true){printf("1\n");continue;}
		bool is_r=check_r(),is_c=check_c();
		if(is_r||is_c) {printf("2\n");continue;}
		int ans = 0x3f3f3f3f;
		for(ri i = 1;i <= n;i++)
			for(ri j = 1;j <= m;j++)
				if(mp[i][j] == 'A')
					if(i == 1 && j == 1) ans = min(ans,2);
					else if(i == 1 && j == m) ans = min(ans,2);
					else if(i == n && j == 1) ans = min(ans,2);
					else if(i == n && j == m) ans = min(ans,2);
					else if(i == n || j == m) ans = min(ans,3);
					else if(i == 1 || j == 1) ans = min(ans,3);
		if(ans == 0x3f3f3f3f) ans = 4;
		printf("%d\n",ans);
	}
	fclose(stdin);
	return 0;
}
```

---

## 作者：xieyikai2333 (赞：1)

- [题目传送门-洛谷](https://www.luogu.com.cn/problem/CF1280B)

- [题目传送门-CodeForces](https://codeforces.com/problemset/problem/1280/B)

---

## 闲话

- 做法其他题解好像讲的差不多了。。。

- 写这篇题解主要是讲如何将代码写得短小精悍，重点放在**代码实现**上。

---

## 解题思路

其他题解说得差不多了，我简单说一下。

答案及其优先级如下：

1. 矩阵全 `A`：$0$；
1. 有一边上全 `A`：$1$；
1. 内部有行全 `A`：$2$；
1. 内部有列全 `A`：$2$；
1. 角上有 `A`：$2$；
1. 边上有 `A`：$3$；
1. 内部有 `A`：$4$；
1. 没有 `A`：`MORTAL`。

---

## 代码实现

- 代码里有详细的注释，所以看起来和其他题解长度相当。实则只有 $32$ 行！！！

### **AC 代码**

**有注释版：**

```cpp
#include <bits/stdc++.h>　
using namespace std;
const int INF=114514;
bool f[65];//f[j]表示第j列是否全A。
void solve(){　
	memset(f,true,sizeof(f));
	int n,m,ans=INF;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){　
		bool flag=true;//flag表示该行是否全A。
		for(int j=1;j<=m;j++){　
			char ch;
			scanf(" %c",&ch);
			if(ch!='A')f[j]=flag=false;//该行、该列并非全A。
			else ans=min(ans,4-(i==1||i==n)-(j==1||j==m));//对应解题思路中⑤⑥⑦。
//两个表达式都成立说明在角上，对应值为2；
//一个成立说明在边上，对应值为3；
//都不成立说明在内部，对应值为4。
		}
		if(flag)ans=min(ans,2-(i==1||i==n));//对应解题思路中②③。
//表达式成立说明在边上全A，对应值为1；
//不成立说明内部有行全A，对应值为2。
	}
	int cnt=0;//cnt表示有几列全A。
	for(int j=1;j<=m;j++)if(f[j])ans=min(ans,2-(j==1||j==m)),cnt++;//对应解题思路中②④。
//表达式成立说明在边上全A，对应值为1；
//不成立说明内部有列全A，对应值为2。
	if(cnt==m)puts("0");//对应解题思路中①。
//所有列全A即矩阵全A。对应值为0。
	else if(ans==INF)puts("MORTAL");//对应解题思路中⑧。
	else printf("%d\n",ans);
	return;
}
int main(){　
	int T;
	scanf("%d",&T);
	while(T--)solve(); 
	return 0;
}
```

**无注释版：**

```cpp
#include <bits/stdc++.h>　
using namespace std;
const int INF=114514;
bool f[65];
void solve(){　
	memset(f,true,sizeof(f));
	int n,m,ans=INF;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){　
		bool flag=true;
		for(int j=1;j<=m;j++){　
			char ch;
			scanf(" %c",&ch);
			if(ch!='A')f[j]=flag=false;
			else ans=min(ans,4-(i==1||i==n)-(j==1||j==m));
		}
		if(flag)ans=min(ans,2-(i==1||i==n));
	}
	int cnt=0;
	for(int j=1;j<=m;j++)if(f[j])ans=min(ans,2-(j==1||j==m)),cnt++;
	if(cnt==m)puts("0");
	else if(ans==INF)puts("MORTAL");
	else printf("%d\n",ans);
	return;
}
int main(){　
	int T;
	scanf("%d",&T);
	while(T--)solve(); 
	return 0;
}
```

---

## 作者：万弘 (赞：1)

[本场比赛完整题解](https://www.luogu.com.cn/blog/c2522943959/cf1281round-607-div-2-ti-xie)
### D - Beingawesomeism

题意:我不知道怎么概括...读者自己看吧...

但这题的做法其实很简单,就是分情况讨论:  
- 如果所有都是`A`那就是0
- 如果有一条边全都是`A`那直接推过去就好了,1
- 有一行或一列全都是`A`,那么我们可以花一次让他们到边上,也就变成前一种情况,所以是2
- 有一个角是`A`把它沿着边推到底,又变成一条边全都是`A`的情况,所以也是2
- 边上有一个点是`A`可以花一次把它推到角上,又变成前一种情况,3
- 一个普通的点`A`,可以花一次把它推到边上,所以是4
- 根本没有`A`,无解

每组数据$O(nm)$

有意思的是,第一次写的很丑然后就WA了,第二次改得好看了一点,核心内容似乎没变但就过了
```cpp
/**********/
#define MAXN 111
char a[MAXN][MAXN];
ll n,m,cnt_all,cnt_edge,cnt_corner;//总的A数量,边上的A数量,角上的A数量
bool flag;//是否存在有一行或一列全是A
bool calc_all()//是否全都是A顺便求出那几个数量
{
	cnt_all=cnt_edge=cnt_corner=0;
	flag=0;
	for(ll i=1;i<=n;++i)
		for(ll j=1;j<=m;++j)
			if(a[i][j]=='A')
			{
				++cnt_all;
				ll c=(i==1||i==n)+(j==1||j==m);
				if(c==1)++cnt_edge;
				if(c==2)++cnt_corner;
			}
	return cnt_all==n*m;
}
bool calc_edge()//是否有一条边都是A
{
	for(ll i=1;i<=n;++i)
	{
		ll tmp=0;
		for(ll j=1;j<=m;++j)
			if(a[i][j]=='A')++tmp;
		if(tmp==m)
		{
			if(i==1||i==n)return 1;//有一条边是A
			flag=1;//普通的一行是A
		}
	}
	for(ll j=1;j<=m;++j)
	{
		ll tmp=0;
		for(ll i=1;i<=n;++i)
			if(a[i][j]=='A')++tmp;
		if(tmp==n)
		{
			if(j==1||j==m)return 1;
			flag=1;
		}
	}
	return 0;
}
int main()
{
	ll task=read();
	while(task--)
	{
		flag=0;
		n=read(),m=read();
		for(ll i=1;i<=n;++i)scanf("%s",a[i]+1);
		if(calc_all())
		{
			puts("0");continue;
		}
		if(calc_edge())
		{
			puts("1");continue;
		}
		if(cnt_corner||flag)puts("2");//那几种情况
		else if(cnt_edge)puts("3");
		else if(cnt_all)puts("4");
		else puts("MORTAL");
	}
	return 0;
}
```

---

## 作者：installb (赞：1)

分类讨论题  

首先如果全`P`无解 否则答案最多是4 最少是0(全是`A` 这是个坑点)  
然后选择的行列一定是有`A`的 否则就是浪费  

答案为 1/2/3/4 分别对应:  
(步数顺序:蓝->绿->橙->红)  

红色格子为`A`  
![](https://cdn.luogu.com.cn/upload/image_hosting/cz3ix1th.png)  

2还有一种情况 即以行一列都填满  
![](https://cdn.luogu.com.cn/upload/image_hosting/sl7e54zj.png)  

最优解之一一定是只选择含有`A`的格子/一整行整列操作的  
如果选择的部分含有`P` 会留下一部分`P`花至少一步去掉 然而其实是可以从一开始就把这几个`P`用`A`覆盖掉 后者不会更劣

下面代码:  

```cpp
typedef long long LL;
 
LL n,m,k,T,ans;
LL lin[3000005],col[3000005];
char ch;
 
int main(){
	cin >> T;
	while(T --){
		cin >> n >> m; ans = 5;
		LL flg = 0;
		for(LL i = 1;i <= n;i ++) lin[i] = 0;
		for(LL j = 1;j <= m;j ++) col[j] = 0;
			
		for(LL i = 1;i <= n;i ++){
			for(LL j = 1;j <= m;j ++){
				cin >> ch; if(ch == 'P'){ flg = 1; continue; }
				
				ans = min(ans,4LL); // 有就至少是4
				if(i == 1 && j == 1) ans = min(ans,2LL);
				if(i == 1 && j == m) ans = min(ans,2LL);
				if(i == n && j == 1) ans = min(ans,2LL);
				if(i == n && j == m) ans = min(ans,2LL);
                // 角落 2
				lin[i] ++; col[j] ++;
				if(i == 1 || i == n || j == 1 || j == m) ans = min(ans,3LL); // 边缘 3
			}
		}
		
		for(LL i = 1;i <= n;i ++) if(lin[i] == m) ans = min(ans,2LL); // 2 第二种情况
		if(lin[1] == m || lin[n] == m) ans = min(ans,1LL); // 一整行一整列 1
		for(LL j = 1;j <= m;j ++) if(col[j] == n) ans = min(ans,2LL); // 行列都要看
		if(col[1] == n || col[m] == n) ans = min(ans,1LL);
		
		if(!flg) ans = 0; // 全是'A'
		
		if(ans == 5) cout << "MORTAL" << endl; // 无解
		else cout << ans << endl;
	}
	return 0;
}
```

~~第一场Div1 自闭~~

---

## 作者：_lxy_ (赞：0)

### 题意

略。

### 分析

容易看出，原矩阵只有 $7$ 种情况，分类讨论即可。

1. 若字符矩阵全是 `P`，则无解；
  
2. 若字符矩阵本来就全是 `A`，则需要 $0$ 步操作；
  
3. 若原矩阵的第一行或第一列或最后一行或最后一列是 `A`，则只需 $1$ 步操作，即推整行或整列；
  
4. 若原矩阵有整行或整列的 `A`，且不是在边界的行或列，则需要 $2$ 步操作，即向两个方向推该行或列；
  
5. 若没有整行整列的 `A`，但有在四个角的 `A`，则需要 $2$ 步操作，即先推完整行，再用行推完整个矩阵；
  
6. 若没有整行整列的 `A`，也没有四个角的 `A`，但有在边界的 `A`，则需要 $3$ 步操作，即先向两个方向推完整个行或列，再推完整个矩阵。
  
7. 若只有普通的 `A`，也就是没有在以上 2-6 情况中的任意一种，则需要 $4$ 步操作，即向四个方向推。

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> Pair;
const int inf=2139062143;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
template<class T> T qmax(T x,T y){return x>y?x:y;}
template<class T,class ...Arg> T qmax(T x,T y,Arg ...arg){return qmax(x>y?x:y,arg...);}
template<class T> T qmin(T x,T y){return x<y?x:y;}
template<class T,class ...Arg> T qmin(T x,T y,Arg ...arg){return qmin(x<y?x:y,arg...);}
const int MAXN=67;
int T,n,m;
char s[MAXN][MAXN];
int main()
{
    qread(T);int i,j;
    while(T--)
    {
        qread(n,m);for(i=1;i<=n;i++) scanf("%s",s[i]+1);bool f=false;
        for(i=1;i<=n;i++) for(j=1;j<=m;j++) if(s[i][j]=='A') f=true;
        if(!f){printf("MORTAL\n");continue;}f=false;
        bool flag=true;for(i=1;i<=n;i++) for(j=1;j<=m;j++) if(s[i][j]=='P') flag=false;if(flag){printf("0\n");continue;}
        for(i=1;i<=m;i++) if(s[1][i]=='P'){f=true;break;}
        if(!f){printf("1\n");continue;}f=false;
        for(i=1;i<=m;i++) if(s[n][i]=='P'){f=true;break;}
        if(!f){printf("1\n");continue;}f=false;
        for(i=1;i<=n;i++) if(s[i][1]=='P'){f=true;break;}
        if(!f){printf("1\n");continue;}f=false;
        for(i=1;i<=n;i++) if(s[i][m]=='P'){f=true;break;}
        if(!f){printf("1\n");continue;}f=true;
        for(i=1;i<=n;i++)
        {
            bool fl=true;
            for(j=1;j<=m;j++) if(s[i][j]=='P') fl=false;
            if(fl) 
            {
                f=false;printf("2\n");
                break;
            }
        }
        if(!f) continue;
        for(i=1;i<=m;i++)
        {
            bool fl=true;
            for(j=1;j<=n;j++) if(s[j][i]=='P') fl=false;
            if(fl) 
            {
                f=false;printf("2\n");
                break;
            }
        }
        if(!f) continue;
        if(s[1][1]=='A'||s[1][m]=='A'||s[n][m]=='A'||s[n][1]=='A')
        {
            printf("2\n");
            continue;
        }
        for(j=1;j<=n;j++)
        {
            if(s[j][1]=='A'||s[j][m]=='A') 
            {
                printf("3\n");f=false;
                break;
            }
        }
        if(!f) continue;
        for(i=1;i<=m;i++)
        {
            if(s[1][i]=='A'||s[n][i]=='A')
            {
                printf("3\n");f=false;
                break;
            }
        }
        if(!f) continue;
        printf("4\n");
    }
    return 0;
}
```

---

## 作者：Hooch (赞：0)

我们可以将整个矩阵分成 4 种情况：

+ 全为 `A`。

输出 0 即可。

+ 全为 `P`。

输出 `MORTAL`。

+ 没有任何一个 `A` 在边上

如同：

```
PPPP
PAAP
PPPP
```

像这种情况，我们先将 `A` 复制到一整排，这时步数为 2,。

接着在把这一排往上下都复制一遍。

所用步数为 4。

+ 其他...

我们可以发现有一整排 `A` 都在边上就能 1 次让整个矩阵都成为 `A`。

否则一整排 `A` 不在边上，这样需要两边都复制过去。

如果找不到一整排 `A` 那就要判断有没有一个角上有 `A`。

如果有，那么就要 2 步；否则是 3 步。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 65;
int t, n, m; char a[N][N];
signed main() {
    ios :: sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> n >> m; int flg = 1, err = 1, kkk = 1; 
		/*
		flg = 0表示不为特殊情况，= 1表示为
		PPPP 
		PAAP 
		PPPP 
		的情况
		err=1 表示全为 P
		kkk=1 表示全为 A 
		*/
        for (int i(1); i <= n; ++i) for (int j = 1; j <= m; ++j) {
                cin >> a[i][j];
                if (a[i][j] == 'A') {
                    if (i == n || i == 1 || j == 1 || j == m) flg = 0;
                    err = 0;
                } else if (a[i][j] == 'P') kkk = 0;
        }
        if (kkk) puts("0");
        else if (err) puts("MORTAL");
        else if (flg) puts("4");
        else {
            int kk = 0x3f3f3f3f;
            for (int i = 1; i <= n; ++i) {
                bool flg = 1;
                for (int j = 1; j <= m; ++j) flg &= (a[i][j] == 'A');
                if (flg) {kk = min((i == 1 || i == n) ? 1 : 2, kk);} //如果是边上的，只需 1 步 
            }
            for (int j = 1; j <= m; ++j) {
                bool flg = 1;
                for (int i = 1; i <= n; ++i) flg &= (a[i][j] == 'A');
                if (flg) {kk = min((j == 1 || j == m) ? 1 : 2, kk);} //同上 
            }
            if (kk ^ 0x3f3f3f3f) {printf("%d\n", kk); continue;}
			if (a[1][1] == 'A' || a[1][m] == 'A' || a[n][1] == 'A' || a[n][m] == 'A') puts("2");
			else puts("3"); //判断有没有角上是 A 
        }
    }
}
```

---

## 作者：_Dreamer_ (赞：0)

# $CF1280B$   $Beingawesomeism$ 题解

总的来说还是分类讨论了

- 无解情况  所有字符全为 $P$ 

- ans = 1  最靠近边缘的行或列全为 $A$ 即第 1 行,第 1 列,第 n 行,第 n 列

- ans = 2  四个角落为 $A$  可以通过一次操作变为 ans = 2 的情况 

  ​      		或者不是靠近边缘的某些行列全为 $A$ 直接在该行或列左右刷两次即可

- ans = 3   四条边上的某些点 为 $A$ 可以通过一次操作变为 ans = 2 中第二种情况

- ans = 4   其余的情况就是四了

当然 符合多种情况的取 $\min$ 就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,m;
char s[65][65];
int allrow[65],allcloum[65];
int solve()
{
	int ans=4;
	bool f=0;// ans = 0 情况 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='P')
			{
				allcloum[j]=1;
				allrow[i]=1;
				f=1;
			}
			if(s[i][j]=='A'&&(i==1||i==n||j==1||j==m))
			{
				ans=min(ans,3);
				// ans = 3 情况 
			}
		}
	}
	if(f==0)return 0;
	if(s[1][1]=='A'||s[1][m]=='A'||s[n][1]=='A'||s[n][m]=='A')
	{
		ans=min(ans,2);// ans = 2 情况 
	}
	for(int i=1;i<=n;i++)
	{
		if(allrow[i]==0)
		{
			if(i==1||i==n)ans=min(ans,1);
			// ans = 1 情况 
			else ans=min(ans,2);
			// ans = 2 情况 
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(allcloum[i]==0)
		{
			if(i==1||i==m)ans=min(ans,1);
			// ans = 1 情况 
			else ans=min(ans,2);
			// ans = 2 情况 
		}
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(allrow,0,sizeof allrow);
		memset(allcloum,0,sizeof allcloum);
		bool flag=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s[i]+1);
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='A')flag=1;// 无解情况 
			}
		}
		if(flag==0)
		{
			puts("MORTAL");
		}
		else
		{
			printf("%d\n",solve());
		}
	}
	return 0;
}
```

---

