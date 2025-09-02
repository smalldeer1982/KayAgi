# Cinema

## 题目描述

Overall there are $ m $ actors in Berland. Each actor has a personal identifier — an integer from $ 1 $ to $ m $ (distinct actors have distinct identifiers). Vasya likes to watch Berland movies with Berland actors, and he has $ k $ favorite actors. He watched the movie trailers for the next month and wrote the following information for every movie: the movie title, the number of actors who starred in it, and the identifiers of these actors. Besides, he managed to copy the movie titles and how many actors starred there, but he didn't manage to write down the identifiers of some actors. Vasya looks at his records and wonders which movies may be his favourite, and which ones may not be. Once Vasya learns the exact cast of all movies, his favorite movies will be determined as follows: a movie becomes favorite movie, if no other movie from Vasya's list has more favorite actors.

Help the boy to determine the following for each movie:

- whether it surely will be his favourite movie;
- whether it surely won't be his favourite movie;
- can either be favourite or not.

## 说明/提示

Note to the second sample:

- Movie jumanji can theoretically have from 1 to 3 Vasya's favourite actors.
- Movie theeagle has all three favourite actors, as the actor Vasya failed to remember, can only have identifier 5.
- Movie matrix can have exactly one favourite actor.
- Movie sourcecode doesn't have any favourite actors.

Thus, movie theeagle will surely be favourite, movies matrix and sourcecode won't surely be favourite, and movie jumanji can be either favourite (if it has all three favourite actors), or not favourite.

## 样例 #1

### 输入

```
5 3
1 2 3
6
firstfilm
3
0 0 0
secondfilm
4
0 0 4 5
thirdfilm
1
2
fourthfilm
1
5
fifthfilm
1
4
sixthfilm
2
1 0
```

### 输出

```
2
2
1
1
1
2
```

## 样例 #2

### 输入

```
5 3
1 3 5
4
jumanji
3
0 0 0
theeagle
5
1 2 3 4 0
matrix
3
2 4 0
sourcecode
2
2 4
```

### 输出

```
2
0
1
1
```

# 题解

## 作者：封禁用户 (赞：4)

## CF234D Cinema 题解
### 解题思路
我们可以在看题面时发现，这道题的数据范围非常小，所以我们只要**模拟**每一个电影的比较过程就可以通过了。

模拟时，我们可以通过以下判断来确定输出是 $0,1$ 还是 $2$。
1. 如果这个电影的最少可能喜爱演员数量 $\ge$ 其他电影的最多可能喜爱演员数量，那么输出：“$0$”。
1. 如果这个电影的最多可能喜爱演员数量 $<$ 其他电影的最少可能喜爱演员数量，那么输出：“$1$”。
1. 如果这个答案不能由前两个判断得出，代表这个电影可能是“$0$”，也可能是“$1$”，所以输出“$2$”。

由这个简单的思路，就不难写出代码了。

**注意：一定要加 $\texttt{freopen}$！**
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct p
{
	int d , b[105] , minn , maxn;
	string s;
}s[105];
int m , k , n , a[105] , maxmin , maxmax;
bool c[105];
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	freopen("input.txt" , "r" , stdin);
	freopen("output.txt" , "w" , stdout);
	cin >> m >> k;
	for(int i = 1 ; i <= k ; i++)
	{
		cin >> a[i];
		c[a[i]] = 1;
	}
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> s[i].s >> s[i].d;
		for(int j = 1 ; j <= s[i].d ; j++)
		{
			cin >> s[i].b[j];
			if(c[s[i].b[j]])
			{
				s[i].minn++;
				s[i].maxn++;
			}
			if(s[i].b[j] == 0)
			{
				s[i].maxn++;
			}
		}
		s[i].maxn = min(s[i].maxn , k);
		s[i].minn = max(s[i].minn , k - m + s[i].d);
	}
	for(int i = 1 ; i <= n ; i++)
	{
		maxmin = maxmax = -1;
		for(int j = 1 ; j <= n ; j++)
		{
			if(i == j)
			{
				continue;
			}
			maxmin = max(maxmin , s[j].minn);
			maxmax = max(maxmax , s[j].maxn);
		}
		if(s[i].minn >= maxmax)
		{
			cout << "0\n";
		}
		else if(s[i].maxn < maxmin)
		{
			cout << "1\n";
		}
		else
		{
			cout << "2\n";
		}
	}
	return 0;
}
```

---

## 作者：Shimotsuki (赞：3)

[传送门 to 洛谷](https://www.luogu.com.cn/problem/CF234D)

[传送门 to CF](http://codeforces.com/problemset/problem/234/D)

这是一道不错的~~暴力~~模拟题，思路很好想，判断喜欢演员的最大值和最小值，然后和 $n$ 部电影的最大值和最小值进行比较即可。本题读入量较大，建议使用较快的读入方式。


- 注意：本题要打文件输入输出！！！

```cpp
//Problem:CF234D
//Time:2022.2.18 evening
//Author:Leonador

#include<cstdio>
#include<bitset>

using namespace std;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}//快读优化 

#define rd(x) x=read()

struct node{
	int d;
	int b[110];
	char name[110];
}str[110];

int a[110];
int imax[110],imin[110];

bitset<110>vis;
//bitset在本题中可看成bool数组的一种优化，用法和bool数组一样 

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	//十年OI一场空，不打freopen见祖宗 
	int m,k;
	rd(m);rd(k);
	for(int i=1;i<=k;i++){
		rd(a[i]);
		vis[a[i]]=true;
	}
	int n;
	rd(n);
	for(int i=1;i<=n;i++){
		scanf("%s",str[i].name);
		rd(str[i].d);
		for(int j=1;j<=str[i].d;j++){
			rd(str[i].b[j]);
		}
	}
	for(int i=1;i<=n;i++){
		int cnt1=k,cnt2=0,cnt3=m-k,cnt4=0;
		for(int j=1;j<=str[i].d;j++){
			if(!str[i].b[j]) cnt2++;
			else if(!vis[str[i].b[j]]) cnt3--;
			else if(vis[str[i].b[j]]){
				cnt1--;
				cnt4++;
			}
		}
		if(cnt1>=cnt2) imax[i]=cnt4+cnt2;
		else imax[i]=cnt4+cnt1;
		if(cnt3>=cnt2) imin[i]=cnt4;
		else imin[i]=cnt4+cnt2-cnt3;
	}
	for(int i=1;i<=n;i++){
		int cnt=1;
		while(cnt<=n){
			if(cnt!=i&&imax[cnt]>imin[i]) break;
			cnt++;
		}
		if(cnt>n) puts("0");
		else{
			int tmp=1;
			while(tmp<=n){
				if(tmp!=i&&imax[i]<imin[tmp]) break;
				tmp++;
			}
			if(tmp<=n) puts("1");
			else puts("2");
		}
	}
	return 0;//大功告成 
}
```


---

## 作者：LEMON_dasiy (赞：1)

一道非常神奇的模拟，@[yuruilin2026](https://www.luogu.com.cn/user/1294410) 和@[Hootime](https://www.luogu.com.cn/user/1275540) 两个大佬认为这是道水题，一眼秒了。  
个人感觉只要看懂题目要干什么就很好做出来了。   
#### [食用博客园](https://www.cnblogs.com/Yi-oprif-Ai/articles/18730632)
### 题意：
输入 $m$ 和 $k$，表示总演员个数和 Vasya 喜欢的演员的个数；  
然后输入 $k$ 个 Vasya 喜欢的演员的编号 $a_1$ 至 $a_k$；  
接着输入一个 $n$，表示电影的场数；  
第 $i$ 电影的名字是 $s_i$ （貌似并没有用），演员数为 $d_i$，第 $j$ 个演员的编号为 $b_{i_j}$，特殊地，若给定的演员编号为 0 则代表小 V 忘记了这个演员的编号。  
Vasya 喜欢的电影标准为这部电影中他喜欢的演员数大于等于其他电影中他喜欢的演员数。  
求每部电影是不是他喜欢的电影，若是则输出 ```0```，若不是则输出 ```1```，若不能确定则输出 ```2```。
### 思路：
简化了题意之后就很简单了，问题就被转化为如何寻找每场电影可能拥有的最多的喜欢的演员数 ```movie[i].max_love``` 和可能拥有的最少的喜欢的演员数 ```movie[i].min_love```。  
还需要找出其他电影中最少的喜欢的演员数的最大值 ```all_min``` 和最多的喜欢的演员数的最大值 ```all_max```。  
- 若 ```movie[i].min_love``` $\ge$ ```all_max``` 则输出 ```0```；
- 若 ```movie[i].max_love``` $<$ ```all_min``` 则输出 ```1```；
- 其他情况就输出 ```2```。  
## $\mathfrak{CODE}$：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define fast_gets ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define open_f_same freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#define close_f fclose(stdin);fclose(stdout);
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))//卡常 
using namespace std;
//快读快写 
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)){
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
inline void write(int x){
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int love[114];
class cls{
	public:
		string name;//不知道有啥用 
		int d,b[114];
		int max_love,min_love;//可能拥有的最多的喜欢的演员和可能拥有的最少的喜欢的演员
}movie[114];//电影 
int love_op[114];
int main(){
    //fast_gets
    open_f_same 
	int m=read(),k=read();
	for(int i=1;i<=k;i++){
		love[i]=read();
		love_op[love[i]]=1;//标记喜欢的演员的编号 
	}
	int n=read();
	for(int i=1;i<=n;i++){
		cin>>movie[i].name;
		movie[i].d=read();
		for(int j=1;j<=movie[i].d;j++){
			movie[i].b[j]=read();
			if(love_op[movie[i].b[j]]){//如果是喜欢的演员，所以可以确定，最多和最少都加 
				movie[i].max_love++;
				movie[i].min_love++;
			}else if(movie[i].b[j]==0){//如果不知道，那么只加最多的 
				movie[i].max_love++;
			}
		}
		movie[i].max_love=min(movie[i].max_love,k);//不能超出k 
		movie[i].min_love=max(movie[i].min_love,k-m+movie[i].d);//若喜欢的演员-总演员+这场电影的演员>最少的，则说明肯定有几个不知道的演员可以确定是喜欢的 
	}
	for(int i=1;i<=n;i++){
		int all_max=-114514,all_min=-114514;//设为最小值（一定要放在循环里面） 
		for(int j=1;j<=n;j++){//当j!=i时更新最大值和最小值 
			if(j==i) continue;
			all_min=max(all_min,movie[j].min_love);
			all_max=max(all_max,movie[j].max_love);
		}
		if(movie[i].min_love>=all_max){//若这场电影的最小值都大于或等于其他电影最大值的最大值，那么就可以确定这场电影一定是喜欢的 
			cout<<0<<endl;
		}
		else if(movie[i].max_love<all_min){//若这场电影的最大值都小于其他电影小值的最大值，那么就可以确定这场电影一定不是喜欢的 
			cout<<1<<endl;
		}
		else cout<<2<<endl;//否则不能确定 
	}
    close_f
    return 0;
}

```
完结撒花！！！

---

## 作者：syf159 (赞：1)

[洛谷 题目传送门](https://www.luogu.com.cn/problem/CF234D)  
[codeforces 题目传送门](https://codeforces.com/problemset/problem/234/D)

## 分析

对于这一题，可以看到，小 V 喜欢的演员的位置并不重要，所以，为了节省时间，我们可以对小 V 喜欢的演员进行一个桶排。
```cpp
for(int i=1; i<=m; i++)
	{
		cin>>t;
		love_actor[t]=true;
	}
```
对于每一部电影，把确定喜欢的和不确定喜欢的进行累加，再进行一定的处理。
```cpp
for(int i=1; i<=k; i++)
	{
		cin>>name;
		int num;
		cin>>num;
		for(int j=1; j<=num; j++)
		{
			cin>>t;
			if(t==0) movie[i].equivocal++;
			else if(love_actor[t]==true) movie[i].equivocal++,movie[i].certain++;
		}
		movie[i].equivocal=min(movie[i].equivocal,m);
		movie[i].certain=max(movie[i].certain,m-n+num);
	}
```
最后，对电影进行大小比较，就可以求出最终答案。
```cpp
for(int i=1; i<=k; i++)
	{
		max_certain=-1,max_equivocal=-1;
		for(int j=1; j<=k; j++)
		{
			if(i==j) continue;
			max_certain=max(max_certain,movie[j].certain);
			max_equivocal=max(max_equivocal,movie[j].equivocal);
		}
		if(movie[i].certain>=max_equivocal)
		{
			cout<<"0\n";
		}
		else if(movie[i].equivocal<max_certain)
		{
			cout<<"1\n";
		}
		else
		{
			cout<<"2\n";
		}
	}
```
## 提醒
这题需要开文件读写，否则会 WA 得很惨……

然后题目中也说了，此题时间比较少，建议使用快读。

## 代码
主要的代码在文章中给了，完整代码看 [这里](https://www.luogu.com.cn/paste/6pmhaa4l)。

---

## 作者：Error_Eric (赞：0)

#### 题意

有 $m$ 个演员编号分别为 $1$ 至 $m$。其中，编号分别为 $a_1$ 至 $a_k$ 的 $k$ 个演员是小 V 所喜爱的。

当且仅当不存在拥有更多小 V 喜欢的演员的电影时，这个一个电影是小 V 喜爱的的电影。

小 V 记录了下个月 $n$ 个电影的影片名称  $s_i$，演员人数 $d_i$ 和演员编号 $b_{ij}$。特殊地，若给定的演员编号为 $0$ 则代表小 V 忘记了这个演员的编号。

试求出每个电影是否是小 V 喜爱的电影。若肯定是，输出 ``0``；若不可能是，输出``1``，若不确定，输出``2``。

 $1\leq k \leq m \leq 100,1\leq d_i\leq m,0\leq b_{ij}\leq m,1\leq |s_i|\leq10$

电影名称由小写字母组成。同一部电影中不会出现两个相同的演员编号。

有相当多的多余信息。例如影片的名字，演员的具体编号等。去掉多余信息本质上是给定每个 $a_i$ 的范围，求 $a_i$ 是否可能或是否一定是 $a$ 的最大值。

#### 解法

首先可以注意到喜欢的演员的顺序不重要，但是后面又要快速知道是否喜爱这个演员。所以桶排之。

```cpp
readln(m),readln(k);
    for(rei i=1;i<=k;i++)readln(ai),like[ai]=1;
```

一个影片具体有那些演员也不重要，只需要知道喜欢的人数和不确定的人数(0的个数)就可以。我们分别记一定拥有的喜欢的演员的人数，不确定的人数，实际上拥有的喜欢的演员的人数为 $u_i,v_i,a_i$。显然 $a_i\in[u_i,u_i+v_i]$

```cpp
for(rei i=1;i<=n;i++){
    cin>>si;
    readln(di);
    for(rei j=1;j<=di;j++){
        readln(bij);
        if(bij==0)u[i]++;
        else if (like[bij])v[i]++;
    }
        ...
}
```

一个影片 $i$ 一定是喜欢的，当且仅当 $\forall j\ u_i\geq u_j+v_j$ 。一定不是喜欢的，当且仅当 $\forall j\ u_i+v_i\le u_j$。

那么统计 $\max\{u_i+v_i\},\min\{u_j\}$ 。

```cpp
if(v[i]>v[lf])lf=i;
if(v[i]+u[i]>v[mf]+u[mf])mf=i;
```

并逐个比较

```cpp
for(rei i=1;i<=n;i++){
    if(v[i]>=v[mf]+u[mf])puts("0");
    else if (v[i]+u[i]<v[lf])puts("1");
    else puts("2");
}
```

然后交上去，会发现样例都 $\color{red}\texttt{WA}$ 。

注意以下细节：

可能多余的 $0$ 中有几个必须填上喜欢的演员。

```cpp
if(v[i]<k-(m-di)){
    int cc=k-(m-di)-v[i];
    v[i]+=cc,u[i]-=cc;
}
```

$0$ 可能没法全部用喜欢的演员填满。

```cpp
u[i]=min(u[i],k-v[i]);
```

有可能 $\forall j\not=i\ \min\{a_i\}>\max\{a_j\}$ 但是 $\max\{a_i\}>\min\{a_i\}$ 。试维护次小的 $\max\{a_i\}$。

```cpp
if(v[i]+u[i]>v[mf]+u[mf])mu=mf,mf=i;
    else if (v[i]+u[i]>v[mu]+u[mu])mu=i;
```

```cpp
if(v[i]>=v[mf]+u[mf] or (i==mf and v[i]>=v[mu]+u[mu]))puts("0");
```

最后加上文件输入输出。

#### Code

代码都分成一部分一部分放了，完整的可以看[这里](https://codeforces.ml/contest/234/submission/166903933)。

题解主要是写给n年没写代码的自己整理思路的。

---

## 作者：开始新的记忆 (赞：0)

思路：此题需要一定的思维过程，在最后确定这部电影是否可能成为最喜欢或者一定不可能或者一定是，有以下几点：1.如果这部电影的确定喜欢人数，已经大于其他任意一个电影的喜欢人数加不确定人数之和，那么可以确定它就是最喜欢的。2.如果这部电影的喜欢人数加上不确定人数已经小于了所有电影中最多一部的喜欢人数，那么这部电影肯定是不喜欢的。3.其余为不确定。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 107
int zero[N],vis[N],a[N];
int d[N][N];
int like[N],mlike[N];
map<int,int> mp;

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int m,k,chang,i,j,maxilike,ka,maximlike;
    char ss[17];
    while(scanf("%d%d",&m,&k)!=EOF)
    {
        mp.clear();
        for(i=0;i<k;i++)
        {
            scanf("%d",&a[i]);
            mp[a[i]] = 1; 
        }
        memset(zero,0,sizeof(zero));
        maxilike = maximlike = -10000;
        scanf("%d",&chang);
        for(i=0;i<chang;i++)
        {
            scanf("%s",ss);
            scanf("%d",&ka);
            for(j=0;j<ka;j++)
            {
                scanf("%d",&d[i][j]);
                if(d[i][j] == 0)
                    zero[i]++;
            }
            if(ka == m)
            {
                maxilike = max(maxilike,k);
                maximlike = max(maximlike,k);
                mlike[i] = k;
                like[i] = k;
            }
            else
            {
                int ca = 0;
                memset(vis,0,sizeof(vis));
                for(j=0;j<k;j++)
                    vis[a[j]] = 1;
                for(j=0;j<ka;j++)
                {
                    if(mp[d[i][j]])
                        ca++;
                    vis[d[i][j]] = 1;
                }
                int unvis = 0;
                for(j=1;j<=m;j++)
                {
                    if(!vis[j])
                        unvis++;
                }
                if(unvis < zero[i])
                {
                    like[i] = ca + zero[i] - unvis;
                    mlike[i] = ca + min(zero[i],k-ca);
                }
                else
                {
                    mlike[i] = ca + min(zero[i],k-ca);
                    like[i] = ca;
                }
                maxilike = max(maxilike,like[i]);
                maximlike = max(maximlike,mlike[i]);
            }
        }
        for(i=0;i<chang;i++)
        {
            if(like[i] >= maximlike || (like[i] >= maxilike && mlike[i] == maximlike))
            {
                if(like[i] >= maximlike)
                    printf("0\n");
                else
                {
                    int flag = 1;
                    for(j=0;j<chang;j++)
                    {
                        if(j!=i && like[i] < mlike[j])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if(flag)
                        printf("0\n");
                    else
                        printf("2\n");
                }
            }
            else if(mlike[i] < maxilike)
                printf("1\n");
            else
                printf("2\n");
        }
    }
    return 0;
}
```


---

