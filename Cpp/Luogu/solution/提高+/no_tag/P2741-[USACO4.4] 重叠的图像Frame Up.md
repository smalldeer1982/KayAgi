# [USACO4.4] 重叠的图像Frame Up

## 题目描述

看下面的五张 $9 \times 8$ 的图像：

```plain
........   ........   ........   ........   .CCC....
EEEEEE..   ........   ........   ..BBBB..   .C.C....
E....E..   DDDDDD..   ........   ..B..B..   .C.C....
E....E..   D....D..   ........   ..B..B..   .CCC....
E....E..   D....D..   ....AAAA   ..B..B..   ........
E....E..   D....D..   ....A..A   ..BBBB..   ........
E....E..   DDDDDD..   ....A..A   ........   ........
E....E..   ........   ....AAAA   ........   ........
EEEEEE..   ........   ........   ........   ........

   1          2           3          4          5
```
现在，把这些图像按照 $1\sim 5$ 的编号从下到上重叠，第 $1$ 张在最下面，第 $5$ 张在最顶端。如果一张图像覆盖了另外一张图像，那么底下的图像的一部分就变得不可见了。于是我们得到下面的图像：

```plain
.CCC....
ECBCBB..
DCBCDB..
DCCC.B..
D.B.ABAA
D.BBBB.A
DDDDAD.A
E...AAAA
EEEEEE..
```
对于这样一张图像，计算构成这张图像的矩形图像从底部到顶端堆叠的顺序。

下面是这道题目的规则：

矩形的边的宽度为 $1$，每条边的长度都不小于 $3$。

矩形的每条边中，至少有一部分是可见的。注意，一个角同时属于两条边。

矩形用大写字母表示，并且每个矩形的表示符号都不相同。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 4.4

## 样例 #1

### 输入

```
9 8
.CCC....
ECBCBB..
DCBCDB..
DCCC.B..
D.B.ABAA
D.BBBB.A
DDDDAD.A
E...AAAA
EEEEEE..```

### 输出

```
EDABC```

# 题解

## 作者：pzc2004 (赞：15)

[题目传送门](https://www.luogu.org/problem/P2741)

~~这题在NOIP2018前几天被我们教练拿来当PJ信心赛的T3~~

思路很容易想到，因为每个矩形的每条边都有一部分露出来，所以只需要记录下每种字母的x、y坐标的最大值、最小值即可确定每个矩形，然后就可以推出哪些字母覆盖了哪些字母。

然后就是怎么找情况了，一开始我选择最暴力的方法，枚举所有排列，如果不满足字母覆盖关系就退出。

代码：
```
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int jx[26][4],ss;//jx记录每个矩形的四个角，ss记录字母的种数
bool b[26][26];//b[i][j]表示字母j覆盖了字母i
bool bbb[26];//bbb[i]表示字母i是否出现过
void dfs(string s)
{
	if(s.size()==ss){cout<<s<<endl;return;}//如果枚举完了就输出
	for(int i=0;i<26;i++)//枚举每种字母
	{
		if(!bbb[i])continue;//如果字母i没出现过就continue
		bool bb=1;
		for(int j=0;j<s.size();j++)
		{
			if(b[i][s[j]-'A']){bb=0;break;}//如果不满足覆盖关系就退出
		}
		if(bb){bbb[i]=0;dfs(s+char(i+'A'));bbb[i]=1;}//如果满足覆盖关系就往下dfs
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	string s[n];
	for(int i=0;i<n;i++)cin>>s[i];
	for(int k=0;k<26;k++)jx[k][1]=jx[k][3]=999;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(s[i][j]!='.')
			{
				int kkk=s[i][j]-'A';
				bbb[kkk]=1;
				jx[kkk][0]=max(jx[kkk][0],i);//记录每个矩形的四角
				jx[kkk][1]=min(jx[kkk][1],i);
				jx[kkk][2]=max(jx[kkk][2],j);
				jx[kkk][3]=min(jx[kkk][3],j);
			}
		}
	}
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)for(int k=0;k<26;k++)if(bbb[k] && (((i==jx[k][0] || i==jx[k][1]) && j<=jx[k][2] && j>=jx[k][3]) || ((j==jx[k][2] || j==jx[k][3]) && i<=jx[k][0] && i>=jx[k][1])))b[k][s[i][j]-'A']=1;//记录覆盖关系
	for(int i=0;i<26;i++)if(bbb[i])ss++;
	dfs("");
}
```
结果最后一个点悲惨TLE。

然后改变思路，因为已知哪个字母在哪个字母下面，可以想到使用拓扑排序，于是便AC了。

代码：
```
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int jx[26][4],ss,kkk,n,m,rd[26];//变量都一样,rd[i]表示字母i的入度
bool b[26][26],bbb[26];
char sss[26];
inline void dfs(int l)//拓扑排序（懒得改函数名了）
{
    if(l==ss){printf("%s\n",sss);return;}
    for(register int i=0;i<26;++i)
    {
        if(!bbb[i])continue;//如果字母i没出现过就continue
        if(rd[i]==0)//如果字母i的入度等于0就进行拓扑排序
        {
        	for(register int j=0;j<26;j++)
        	{
        		if(b[i][j])rd[j]--;//将所有覆盖当前字母的入度减1
			}
			sss[l]=i+'A';
			bbb[i]=0;
        	dfs(l+1);//往下dfs
        	bbb[i]=1;
        	for(register int j=0;j<26;j++)
        	{
        		if(b[i][j])rd[j]++;//进行还原
			}
		}
    }
}
int main()//都一样
{
    int i,j,k;
    scanf("%d%d\n",&n,&m);
    char s[n][m];
    for(i=0;i<n;++i)scanf("%s",s[i]);
    for(k=0;k<26;++k)jx[k][1]=jx[k][3]=999;
    for(i=0;i<n;++i)
    {
        for(j=0;j<m;++j)
        {
            if(s[i][j]!='.')
            {
                kkk=s[i][j]-'A';
                bbb[kkk]=1;
                jx[kkk][0]=max(jx[kkk][0],i);
                jx[kkk][1]=min(jx[kkk][1],i);
                jx[kkk][2]=max(jx[kkk][2],j);
                jx[kkk][3]=min(jx[kkk][3],j);
            }
        }
    }
    for(i=0;i<n;++i)for(j=0;j<m;++j)for(k=0;k<26;++k)if(k!=s[i][j]-'A' && !b[k][s[i][j]-'A'] && bbb[k] && (((i==jx[k][0] || i==jx[k][1]) && j<=jx[k][2] && j>=jx[k][3]) || ((j==jx[k][2] || j==jx[k][3]) && i<=jx[k][0] && i>=jx[k][1])))
	{b[k][s[i][j]-'A']=1;rd[s[i][j]-'A']++;}//如果字母k在字母s[i][j]-'A'下面就将字母s[i][j]-'A'的入度加1
    for(i=0;i<26;++i)if(bbb[i])++ss;
    dfs(0);
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：iamzq (赞：12)

# 这道题好难啊
~~对于我这个小蒟蒻来说~~

## 这道题，明显就是个拓扑 ~~我觉得爆搜的都是巨佬~~
###### 删除线用上瘾了
好，进入正题。这道拓扑题首先是要建边。因为他说每一条边都至少有一个。所以我们只要找出一个个矩阵的边界，~~这非常好找~~，然后开始建边。建边就是枚举每一个矩形，发现“有外员侵入”的就建一条边。比如
```
AAABBBA
A..B.BA
AAABBBA
```
此时，A矩阵的边界为上：1 下：3 左：1 右：7

B矩阵的边界同理~~懒~~
然后就枚举A矩阵，发现有B“侵入”，就A->b建一条边

边建好了，接下来就是拓扑。
由于他说不只一个情况，所以我们要去深搜。深搜就是把队列里面每一个入度为0的都拿出来跑一遍，而不是每次取头跑了。把每一次的答案记下来，sort一下就好了。
# 代码（你们最喜欢的）
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[31][31];
const int N=500001;
struct data{
	int x1=1e9,x2,y1=1e9,y2;
}x[27];
int node[N],head[N],nxt[N],into[N],zf,cnt,b[N],ans[N],bb[N],q[N],r,hh=1;
string ans2[N];
void add(int x,int y)
{
	node[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void dfs(int dep)
{
	if(dep>zf)
	{
		for(int i=zf;i>=1;i--){
			char c=ans[i]+'A'-1;
			ans2[hh]+=c;
		}
		hh++;
		return;
	}
	for(int i=1;i<=r;i++)
	{
		if(b[i]==0)
		{
			int rr=r;
			int x=q[i];
			for(int j=head[x];j;j=nxt[j])
			{
				into[node[j]]--;
				if(into[node[j]]==0)q[++r]=node[j];
			}
			b[i]=1;
			ans[dep]=x;
			dfs(dep+1);
			b[i]=0;
			for(int j=head[x];j;j=nxt[j])into[node[j]]++;
			r=rr;
		}
		
	}
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
    for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
    	{
    		if(a[i][j]!='.')
			{
				int h=(int)(a[i][j]-'A'+1);
				if(bb[h]==0)zf++;
				bb[h]=1;
				if(i<x[h].x1)x[h].x1=i;
				if(i>x[h].x2)x[h].x2=i;
				if(j<x[h].y1)x[h].y1=j;
				if(j>x[h].y2)x[h].y2=j;
		    }
		}
	for(int i=1;i<=26;i++)
	{
		if(x[i].x1!=0){
			for(int j=x[i].x1;j<=x[i].x2;j++)
			{
				int h=a[j][x[i].y1]-'A'+1;
				if(h!=i)add(h,i),into[i]++;
				h=a[j][x[i].y2]-'A'+1;
				if(h!=i)add(h,i),into[i]++;
			}
			for(int j=x[i].y1;j<=x[i].y2;j++)
			{
				int h=a[x[i].x1][j]-'A'+1;
				if(h!=i)add(h,i),into[i]++;
				h=a[x[i].x2][j]-'A'+1;
				if(h!=i)add(h,i),into[i]++;
			}
			
		}
	}
	for(int i=1;i<=26;i++)
    	if(bb[i]==1&&into[i]==0)q[++r]=i;
	dfs(1);
	sort(ans2+1,ans2+hh);
	for(int i=1;i<=hh-1;i++)
	{
		for(int j=0;j<zf;j++)printf("%c",ans2[i][j]);
		printf("\n")；
	}
}
```
~~为什么我的码风上了这里就变得鬼畜了~~
好，没了
###### 这是我的第一篇题解。

###### ~~删除线太好用了~~

---

## 作者：interestingLSY (赞：8)

#爆搜即可

###原因

题目中说“矩形的每条边中，至少有一部分是可见的。注意，一个角同时属于两条边。“

这就意味着我们可以通过记录同一个矩形中字母的最大x坐标、最大y坐标、最小x坐标、最小y坐标来获得矩形的左下角和右上角的坐标

接着，由题意我们可知符合的方案可能不只有一个，所以可以dfs（bfs也行）

###实现

每次dfs时，寻找当前“完整”的矩形（“完整”是指矩形的各条边都没有被其它还没被消除的矩形挡住），然后去掉这个矩形，继续递归

###细节

-消除矩形：把要消除的矩形各边都设成空白（就是"."）即可

###优化

我们可以使用拓扑排序，然后在图上跑dfs，这样就能更快的AC了

（但其实爆搜就挺快了，才44ms）

###代码

```cpp
#include <bits/stdc++.h>
#define INF ((int)(1e9))
#define LINF ((ll)(1e18))
#define pb push_back
#define mp make_pair
#define ll long long
#define _tp template
#define _tyn typename
#define ull unsigned ll
#define pii pair<int,int>
#define uint unsigned int
#define ms(_data) memset(_data,0,sizeof(_data))
#define fin(_filename) freopen(_filename,"r",stdin)
#define fout(_filename) freopen(_filename,"w",stdout)
#define msn(_data,_num) memset(_data,_num,sizeof(_data))
using namespace std;
_tp<_tyn T>void mymax( T &_a , T _b ){ if( _a < _b ) _a = _b; }
_tp<_tyn T>void mymin( T &_a , T _b ){ if( _a > _b ) _a = _b; }
int getnum(){
    char ch = '.';
    int fu = 1;
    while( ch < '0'  ||  ch > '9' ){
        ch = getchar();
        if( ch == '-' ) fu = -1;
    }
    int ret = 0;
    while( ch >= '0'  &&  ch <= '9' ){
        ret = ret * 10 + (ch-'0');
        ch = getchar();
    }
    return ret;
}
char getlet(){
    char ch = '%';
    while( ( ch < 'A'  ||  ch > 'Z' )  &&  ch != '.' ) ch = getchar();
    return ch;
}
void read( int &x, int &y ){
    x = getnum(); y = getnum();
}
void read( char &c ){
    c = getlet();
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#define MAXN 40
struct Pos{
    int y,x;
    Pos(){}
    Pos( int yy , int xx ){
        y = yy;
        x = xx;
    }
};
int n,m;
int data[MAXN][MAXN];
Pos ld[MAXN],ur[MAXN];
bool exist[MAXN];

//检测一个矩形是否完整
bool test( int x ){
    for( int i = ld[x].x ; i <= ur[x].x ; i++ ){
        if( data[ld[x].y][i] != x  &&  data[ld[x].y][i] != -1 ) return 0;
        if( data[ur[x].y][i] != x  &&  data[ur[x].y][i] != -1 ) return 0;
    }
    for( int i = ur[x].y ; i <= ld[x].y ; i++ ){
        if( data[i][ld[x].x] != x  &&  data[i][ld[x].x] != -1 ) return 0;
        if( data[i][ur[x].x] != x  &&  data[i][ur[x].x] != -1 ) return 0;
    }
    return 1;
}
//消除一个矩形
void seton( int x , int a ){
    for( int i = ld[x].x ; i <= ur[x].x ; i++ ){
        data[ld[x].y][i] = a;
        data[ur[x].y][i] = a;
    }
    for( int i = ur[x].y ; i <= ld[x].y ; i++ ){
        data[i][ld[x].x] = a;
        data[i][ur[x].x] = a;
    }
}

vector<string> ans;
void dfs( string now ){
    bool gao = 0;
    for( int i = 0 ; i < 26 ; i++ ){
        if( !exist[i] ) continue;
        if( !test(i) ) continue;
        gao = 1;
        exist[i] = 0;
        int ls[MAXN][MAXN];
        memcpy(ls,data,sizeof(ls));
        seton(i,-1);
        dfs( now + (char)(i+'A') );
        memcpy(data,ls,sizeof(data));
        exist[i] = 1;
    }
    if( gao ) return;
    reverse(now.begin(),now.end());
    ans.pb(now);
}
int main(){
    //fin("frameup.in");
    //fout("frameup.out");
    for( int i = 0 ; i < 26 ; i++ ){
        ld[i].y = 0; ld[i].x = INF;
        ur[i].y = INF; ur[i].x = 0;
    }
    msn(data,-1);
    ms(exist);

    read(n,m);
    for( int i = 1 ; i <= n ; i++ ){
        for( int j = 1 ; j <= m ; j++ ){
            char c; read(c);
            if( c == '.' ) continue;
            data[i][j] = c-'A';
            exist[data[i][j]] = 1;
                       //记录矩形左下角、右上角坐标
            mymax( ld[data[i][j]].y , i );
            mymin( ld[data[i][j]].x , j );
            mymin( ur[data[i][j]].y , i );
            mymax( ur[data[i][j]].x , j );
        }
    }

    dfs("");

        //整理答案
    sort(ans.begin(),ans.end());
    for( uint i = 0 ; i < ans.size() ; i++ )
        cout << ans[i] << endl;

    return 0;
}
```

---

## 作者：Loser_King (赞：7)

USACO上的拓扑（比较）模板的题。

同时也是某班模拟赛的第三题（虽然模拟赛数据大幅弱化）。

## 简明题意

> 给定一些由大写字母组成的长方形框，把这些框上下叠放在一起，形成一张字符图像。
>
> 求所有上下叠放的可能方案。

## 做法

#### 33pts / 模拟赛AC 做法

其实和100pts很类似。。。

首先是预处理

以样例为例来说明：

```text
.CCC....  .###....  ........
ECBCBB..  E#####..  +EEEEE..
DCBCDB..  ######..  E....E..
DCCC.B..  ####.#..  E....E..
D.B.ABAA  #.######  E....E..
D.BBBB.A  #.####.#  E....E..
DDDDAD.A  ######.#  E....E..
E...AAAA  E...####  E....E..
EEEEEE..  EEEEEE..  EEEEE+..
   1         2         3
```

如果我们从样例中抽出所有为`E`的字符，而把其他的大写字母都变成`#`，那么样例就变成了图2。

我们再提取出位于最左边，最右边，最上面，最下面的字符，标为`+`，用它勾勒出边框，就变成了图3。

由于题目保证方框的四条边都至少有一个点可见，所以依此就可以判断每一个矩形框的位置。

有关代码如下：

```c++
	memset(u,0x3f,sizeof u);	//初始最上和最左要赋极大值
	memset(l,0x3f,sizeof l);
	for(int ch=65;ch<=mx;ch++)	//mx是ascii最大的字符，由于'A'>'.'，所以可以进行初步筛选
	    for(int i=1;i<=n;i++)
	        for(int j=1;j<=m;j++)
	            if(c[i][j]==ch)
	            		//cnt+=vis[ch],vis[ch]=0,  这一句话在100 pts里有用
					u[ch]=min(u[ch],i),d[ch]=max(d[ch],i),
	            	l[ch]=min(l[ch],j),r[ch]=max(r[ch],j);
						//u[i],d[i],l[i],r[i]数组分别表示由字符i组成的方框最上下左右的位置
```

```c++
inline int check(char ch,int i,int j){	//判断(i,j)是否在由字符ch组成的方框上
	return (i==u[ch]||i==d[ch])&&j<=r[ch]&&j>=l[ch]||	//(i,j)在框的上面或下面
	       (j==l[ch]||j==r[ch])&&i<=d[ch]&&i>=u[ch];	//(i,j)在框的左面或右面
}
```

然后是判断两个框的上下关系。

如果一个框 A 直接覆盖在另一个 B 上，那么在最终的答案中B一定在A的前面。

所以我们可以使用`std::vector<int>e[i]`来表示覆盖在字符i之上的所有方框。

有关代码如下：

```c++
	for(int ch=65;ch<=mx;ch++)
	    for(int i=1;i<=n;i++)
	        for(int j=1;j<=m;j++)
	            if(check(ch,i,j)&&c[i][j]!=ch){	//如果一个点在ch方框上但是实际不是字符ch
	            	int flg=0;
	            	for(int t=0;t<e[ch].size();t++)
	            	    if(e[ch][t]==c[i][j])flg=1;	//去重
	            	if(!flg)e[ch].push_back(c[i][j]),in[c[i][j]]++;	
				}
```

然后就是枚举方案了。

在 33pts 中你实际只要枚举全排列即可。

只有被方框A覆盖的所有方框都在答案里时，方框 A 才可以在答案里。

有关代码如下：

```c++
void search(){
	for(int i=65;i<=mx;i++)s[i-65]=i;mx-=64;	//初始排列为ABCDEF...
	do{
		int flg=0;	//flg表示该序列可以为答案(0)或者不能(1)
		memcpy(ii,in,sizeof in);
		for(int i=0;i<mx&&!flg;i++)
		    if(!in[s[i]]){
		    	for(int j=0;j<e[s[i]].size();j++)
		    		in[e[s[i]][j]]--;
			}else flg=1;
		if(flg==0)cout<<s<<endl;
		memcpy(in,ii,sizeof in);
	}while(next_permutation(s,s+mx));	//全排列
}
```

#### 55 pts

> 如果一个框 A 直接覆盖在另一个框 B 上，那么在最终的答案中B一定在A的前面。

其实我们可以发现，这显然就是 拓扑排序 啊！

前面的`in`数组表示入度，然后就可以做了。

#### 100 pts

其实有个小坑点，就是 `A~mx` 中不是每个字符都会出现的！

所以我们需要多加一个判断。

首先我们要把拓扑排序中的 `vis` 数组初始为 1 ，然后发现一种字符 i 就 `cnt++,vis[i]=0`

这样就可以做到AC了！

## 代码

```c++
//P2741 AC Code
//written by Loster_King(159686)
//29ms /  640.00KB / 1.44KB C++ O2
#include<bits/stdc++.h>
using namespace std;
int const N=233;
int n,m,cnt,in[N],ii[N],u[N],d[N],l[N],r[N];bool vis[N];
char mx,c[N][N],s[N];
vector<char>e[N];
inline int check(char ch,int i,int j){
	return (i==u[ch]||i==d[ch])&&j<=r[ch]&&j>=l[ch]||
	       (j==l[ch]||j==r[ch])&&i<=d[ch]&&i>=u[ch];
}
void topo_sort(string s){
    if(s.length()==cnt){cout<<s<<endl;return;}
    for(int i=65;i<=mx;i++)
        if(!in[i]&&!vis[i]){
        	for(int j=0;j<e[i].size();j++)in[e[i][j]]--;
        	vis[i]=1;topo_sort(s+(char)i);vis[i]=0;
        	for(int j=0;j<e[i].size();j++)in[e[i][j]]++;
        }
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	memset(u,0x3f,sizeof u);
	memset(l,0x3f,sizeof l);
	memset(vis,1,sizeof vis);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
	        cin>>c[i][j],mx=max(mx,c[i][j]);
	for(int ch=65;ch<=mx;ch++)
	    for(int i=1;i<=n;i++)
	        for(int j=1;j<=m;j++)
	            if(c[i][j]==ch)
	            	cnt+=vis[ch],vis[ch]=0,
                	u[ch]=min(u[ch],i),d[ch]=max(d[ch],i),
	            	l[ch]=min(l[ch],j),r[ch]=max(r[ch],j);
	for(int ch=65;ch<=mx;ch++)
	    for(int i=1;i<=n;i++)
	        for(int j=1;j<=m;j++)
	            if(check(ch,i,j)&&c[i][j]!=ch){
	            	int flg=0;
	            	for(int t=0;t<e[ch].size();t++)
	            	    if(e[ch][t]==c[i][j])flg=1;
	            	if(!flg)e[ch].push_back(c[i][j]),in[c[i][j]]++;
                    }
	topo_sort("");
}
```



---

## 作者：__Hacheylight__ (赞：6)

这题整体难度不大，但有很多细的东西，所以容易错。

1.读入矩阵

2.求出有多少个图像（即矩阵中有多少种不同的字母），并从小到大排序

3.t表示有几张图像，从1~t枚举出压在第i张图像上面的图像（x），构成拓扑结构，即i是x的入度，必须有i才有x

4.做一遍dfs,搜出所有的可能：

   ①枚举当前没有入度的节点（代码中是f[i]==0），将它加入答案，标记已使用
   
   ②将以i为入度的点的f减一，
   
   ③重复①,②
   

代码上有注释，易懂：
```cpp
#include <bits/stdc++.h>
#define INF 100
using namespace std ;
char a[31][31],x[31] ;//x代表 第i号是字母c 
int y['Z'] ; // 字母c是第i号 
int t=0 ;//有几个不同的字母 
int f[31] ;//图像i下面压着多少个图像 
int sum[31] ;//表示i上面压着几张图片。拓扑排序后面好删 
int b[31][31] ;//表示i上面压的第j张图像是x 
char ans[100] ;//一个答案串 
int vis[31] ;//当前字母是否在搜索中已经出现过 
int h[31][31] ;//表示i上面是否已经搜索到j在i上面 
int n,m ;
int hash['Z'] ;
void dfs(int k,int val)
{
	if (k==t) //已经枚举过了t个图像 
	{
		for (int i=1;i<=t;i++) printf("%c",ans[i]) ;
		printf("\n") ;
		return ; 
	}
	for (int i=1;i<=t;i++)
	{
		if (f[i]==0 && !vis[i]) //入度为0 且没有访问过 
		{
			vis[i]=1 ;
			ans[k+1]=x[i] ;
			for (int j=1;j<=sum[i];j++)
			f[b[i][j]]-- ;
			dfs(k+1,i) ;//dfs(i,j)表示刚刚定下第j个位置放i 
			for (int j=1;j<=sum[i];j++)
			f[b[i][j]]++ ;
			vis[i]=0 ;
		}
	}
	//题目已保证读入数据合法，不用担心没有答案 
	return ;
}
int main()
{
	scanf("%d%d",&n,&m) ;
	for(int i=0;i<n;i++)  //读入矩阵 
    {  
        scanf("\n");  
        for(int j=0;j<m;j++)  
        {  
        	scanf("%c",&a[i][j]);  
        }
    } 
	for (int i=0;i<n;i++) 
	for (int j=0;j<m;j++){
		char c=a[i][j] ; 
		if (!hash[c] && isalpha(c)){ //当前字母新出现  
			x[++t]=c ;//x 第i号是字母c 
			hash[c]++ ;
		} 
	}
	for (int i=1;i<=t;i++) //排成字典序 
	for (int j=i+1;j<=t;j++)
	if (x[i]>x[j]){
		char tmp=x[i];x[i]=x[j];x[j]=tmp ;
	}
	for (int i=1;i<=t;i++) //字母c是第i号 
	{
		y[x[i]]=i ;
	}
	for (int k=1;k<=t;k++) //枚举t张图 
	{
		int minx=INF,maxx=-INF,miny=INF,maxy=-INF ;
		for (int i=0;i<n;i++) //图像的位置，只需要知道minx,maxx,miny,maxy 
		for (int j=0;j<m;j++){
			if (a[i][j]==x[k]){
				minx=min(minx,i);miny=min(miny,j);
				maxx=max(maxx,i);maxy=max(maxy,j);
			}
		}
		int i=maxx ;
		for (int j=miny+1;j<=maxy-1;j++){
			if (a[i][j]!=x[k] && !h[k][y[a[i][j]]]){ //B向A连边
				b[k][++sum[k]]=y[a[i][j]];//拓扑排序,表示图像b(a[i][j])的下面有图像a(x[k])  
				f[y[a[i][j]]]++; //图像b的前+1	
				h[k][y[a[i][j]]]=1 ;//判重 
			} 
		}
		i=minx ;
		for (int j=miny+1;j<=maxy-1;j++){
			if (a[i][j]!=x[k] && !h[k][y[a[i][j]]]){
				b[k][++sum[k]]=y[a[i][j]];
				h[k][y[a[i][j]]]=1 ;
				f[y[a[i][j]]]++;
			}
		} 
		int j=maxy ;
		for (int i=minx;i<=maxx;i++){
			if (a[i][j]!=x[k] && !h[k][y[a[i][j]]]){
				b[k][++sum[k]]=y[a[i][j]];
				f[y[a[i][j]]]++;
				h[k][y[a[i][j]]]=1 ;
			}
		}
		j=miny ;
		for (int i=minx;i<=maxx;i++){
			if (a[i][j]!=x[k] && !h[k][y[a[i][j]]]){
				b[k][++sum[k]]=y[a[i][j]];
				f[y[a[i][j]]]++;
				h[k][y[a[i][j]]]=1 ;
			}
		}
	}
	for (int i=1;i<=t;i++) 
	if (f[i]==0) //入度为0的点 
	{
		vis[i]=1;
		ans[1]=x[i] ;
		for (int j=1;j<=sum[i];j++)
		f[b[i][j]]-- ;
		dfs(1,i) ;//dfs(i,j)表示刚刚定下第j个位置放i 
		for (int j=1;j<=sum[i];j++) //清标记 
		f[b[i][j]]++ ;
		vis[i]=0 ;
	} 
	 return 0 ;
}
```

---

## 作者：ergeda (赞：4)

    
```cpp
//本蒟蒻没用什么拓补排序，此题爆搜即可
//让我来一发第二快最明了的代码
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define rep(i,a,b) for(i=(a);i>=(b);--i)
#define ll long long
#define inf 999999999
#define mm(a,b) memset(a,b,sizeof(a))
using namespace std;
int read(){
    int sum = 0,fg = 1;
    char c = getchar();
    while(c < '0' || c > '9'){if (c == '-')fg = -1;c = getchar();}
    while(c >='0' && c <='9')sum = sum *10 + c-'0',c = getchar();
    return sum * fg;
}
int minn(int x,int y){return x < y ? x : y;}
int maxx(int x,int y){return x < y ? y : x;}
int n,m,all;
char s[40][40];
char ss[40];
struct node{
    int l ,up ,r ,down;//记录这个字母矩阵的最上、下的横坐标，最左、右的纵坐标
    node(){
        l = inf,r = 0,up = inf,down = 0;
    }
};
const int maxn = 100010;
node a[30];
bool p[30] ,vis[30];//p数组记录某个字母是否在矩阵中出现,vis数组记录某个字母的图像是否已重叠上去
int map[30][30], road[30];//map[i][j]=1表示要重叠j矩阵，就要先重叠i矩阵
void dfs(int h, int tot){//h为当前放哪个字母的图像，tot为已放了几个图像
    int i;road[tot] = h;
    For(i,1,26){
        if(p[i]){
            if(map[i][h] && !vis[i]){//易得如果一个图像若还未重叠&&在重叠当前图像之前要先重叠i字母的图像，则不成立
                return;
            }
        }
    }
    if(tot == all){
        For(i,1,tot){
            printf("%c",road[i] - 1 + 'A');//由于是字典序，搜到一个就输出一个
        }
        printf("\n");
        return;
    }
    For(i,1,26){
        if(!p[i] || i == h)continue;
        if((map[h][i] && !vis[i]) || (!map[h][i] && !vis[i])){//下一个要重叠的图像可能是要在自己之后重叠的，也可能是和自己摆放顺序没有直接关系的
            vis[i] = 1;
            dfs(i,tot + 1);
            vis[i] = 0;
        }
    }
}
int main(){
    int i,j;
    n = read(), m = read();
    For(i,1,n){
        scanf("%s", ss+1);
        For(j,1,m){
            s[i][j] = ss[j];
            if(ss[j] > 'Z' || ss[j] < 'A')continue;
            int tmp = ss[j] - 'A' + 1;//把字母转化为数字
            if(!p[tmp])p[tmp] = 1,++all;
            a[tmp].l = minn(a[tmp].l , j);//上面说了
            a[tmp].r = maxx(a[tmp].r , j);
            a[tmp].up = minn(a[tmp].up , i);
            a[tmp].down = maxx(a[tmp].down , i);
        }
    }
    For(i,1,26){
        if(p[i]){
            int x = a[i].up;
            For(j,a[i].l,a[i].r){//以下这些冗杂的代码仅仅是为了遍历整个矩阵，确立两个字母图像之间的关系
                int tmp = s[x][j] - 'A' + 1;
                if(tmp != i){//若在i的矩阵中却不是i字母，则必定在i图像之后重叠
                    map[i][tmp] = 1;
                }
            }
            x = a[i].down;
            For(j,a[i].l,a[i].r){
                int tmp = s[x][j] - 'A' + 1;
                if(tmp != i){
                    map[i][tmp] = 1;
                }
            }
            x = a[i].l;
            For(j,a[i].up,a[i].down){
                int tmp = s[j][x] - 'A' + 1;
                if(tmp != i){
                    map[i][tmp] = 1;
                }
            }
            x = a[i].r;
            For(j,a[i].up,a[i].down){
                int tmp = s[j][x] - 'A' + 1;
                if(tmp != i){
                    map[i][tmp] = 1;
                }
            }
        }
    }
    For(i,1,26){
        if(p[i]){
            mm(vis,0);
            vis[i] = 1;
            dfs(i, 1);
        }
    }
    return 0;
}
//THE END
```

---

## 作者：gyh20 (赞：2)

判断每个矩形的对角位置即可确定矩形，再判断重叠关系。从深度小的向深度大的建边，最后拓扑排序即可。

本题的难度并不在于拓扑排序，这个排序只是最简单的模版。本题难度主要在于判断矩形覆盖关系。同时需要理解并运用如何使用两个点来确定一个矩形。

代码如下：
```c
#pragma GCC optimize(200000)
#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
struct das {
	int x1,x2,y1,y2;
} f[102];
int map[102][102],a,b,c,rd[102],d,e[102][102],g,m,n,ans[102];
char t;
bool p,v[102],z[102];
void dfs(int x) {
	bool h[102]= {0};
	ans[++ans[0]]=x;
	v[x]=1;
	if(ans[0]==g) {
		for(int i=1; i<=ans[0]; i++)putchar(ans[i]+'A'-1);
		putchar('\n');
	} else {
		for(int i=1; i<=a; i++) {
 
			if(e[x][i]) {
				rd[i]--;
				h[i]=1;
			}
		}
		for(int i=1; i<=a; i++)	if(rd[i]==0&&!v[i])dfs(i);
 
		for(int i=1; i<=a; i++)if(h[i])rd[i]++;
	}
	ans[0]--;
	v[x]=0;
}
int main() {
	cin>>m>>n;
	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++) {
			cin>>t;
			if(t=='.')map[i][j]=0;
			else {
				map[i][j]=t-'A'+1;
				if(!z[map[i][j]])z[map[i][j]]=1,g++;
			}
			a=max(a,map[i][j]);
		}
	}
	for(int i=1; i<=a; i++)f[i].x1=f[i].y1=0x7fffffff;
	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++) {
			if(map[i][j]) {
				if(i<f[map[i][j]].x1)f[map[i][j]].x1=i;
				if(i>f[map[i][j]].x2)f[map[i][j]].x2=i;
				if(j<f[map[i][j]].y1)f[map[i][j]].y1=j;
				if(j>f[map[i][j]].y2)f[map[i][j]].y2=j;
			}
		}
	}
	for(int i=1; i<=a; i++) {
		for(int k=f[i].x1; k<=f[i].x2; k++) {
			if(map[k][f[i].y1]!=i&&!e[i][map[k][f[i].y1]])e[i][map[k][f[i].y1]]=1;
			if(map[k][f[i].y2]!=i&&!e[i][map[k][f[i].y2]])e[i][map[k][f[i].y2]]=1;
		}
		for(int k=f[i].y1; k<=f[i].y2; k++) {
			if(map[f[i].x1][k]!=i&&!e[i][map[f[i].x1][k]])e[i][map[f[i].x1][k]]=1;
			if(map[f[i].x2][k]!=i&&!e[i][map[f[i].x2][k]])e[i][map[f[i].x2][k]]=1;
		}
	}
	for(int i=1; i<=a; i++) {
		for(int j=1; j<=a; j++) {
			if(!z[i])rd[i]=-1;
			if(e[i][j]==1) {
				rd[j]++;
			}
		}	}
		for(int i=1; i<=a; i++) {
			if(rd[i]==0) {
				v[i]=1;
				dfs(i);
			}
		}
 
}
```


---

## 作者：Vin_1999 (赞：2)

floodfill+拓补排序

以下是本蒟蒻丑陋的代码（真的不好看，所以就别抄了）




```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<climits>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
```
static int ind[27],n,h,w,Map[31][31],
vis[27],G[27][27],sqx[27][2],sqy[27][2],ccnt,q[27];





```cpp
char s[27]={0};int num[27]={0};
void work(int clr)
{
    int lu[2],rd[2];int p;
    lu[0]=sqx[clr][0];lu[1]=sqy[clr][0];
    rd[0]=sqx[clr][1];rd[1]=sqy[clr][1];
    rep(i,lu[1]+1,rd[1]) if(((p=Map[lu[0]][i])!=clr)&&!G[clr][p]) ind[p]++,G[clr][p]=1;
    rep(i,lu[0]+1,rd[0]) if(((p=Map[i][rd[1]])!=clr)&&!G[clr][p]) ind[p]++,G[clr][p]=1;
    rep(i,lu[1],rd[1]-1)
    if(((p=Map[rd[0]][i])!=clr)&&!G[clr][p])
    ind[p]++,G[clr][p]=1;
    rep(i,lu[0],rd[0]-1) if(((p=Map[i][lu[1]])!=clr)&&!G[clr][p]) ind[p]++,G[clr][p]=1;
}
void toposort(int dep,string str)
{
    if(dep>ccnt) {cout<<str<<endl;return;}
    rep(i,1,ccnt)
      if(!ind[q[i]]&&!vis[q[i]])
      {
          vis[q[i]]=1;
          rep(j,1,ccnt) if(G[q[i]][j]) ind[j]--;
          str+=s[q[i]];
          toposort(dep+1,str);
          str.erase(str.size()-1,1);
          rep(j,1,ccnt) if(G[q[i]][j]) ind[j]++;
          vis[q[i]]=0;
        }
}
int main()
{                
  freopen("e:/in.txt","r",stdin);
     scanf("%d%d",&h,&w);
     rep(i,1,26) sqx[i][0]=sqy[i][0]=INT_MAX;
     rep(i,1,26) sqx[i][1]=sqy[i][1]=INT_MIN;
     rep(i,1,h)
       rep(j,1,w)
       {
           int t;
        char ch;
          ch=getchar();
           while((ch<'A'||ch>'Z')&&ch!='.')
              ch=getchar(); 
           if(ch=='.') continue;
           if(!num[ch-'A'+1]) s[++ccnt]=ch,t=ccnt,num[ch-'A'+1]=t;else t=num[ch-'A'+1];
           Map[i][j]=t;
           sqx[t][0]=min(i,sqx[t][0]);sqx[t][1]=max(i,sqx[t][1]);
           sqy[t][0]=min(j,sqy[t][0]);sqy[t][1]=max(j,sqy[t][1]);
      }
  int t=0;
    rep(i,1,27) if(num[i]) q[++t]=num[i]; 
  rep(i,1,ccnt) 
    work(i);
  toposort(1,"");
  return 0;
}//by lyyz-ljy
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2741)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;很容易看出来，这道题是拓扑排序的题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们扫描一个矩形$a$的边，如果发现上面有矩形$b$的代表字母，我们就可以确定$b$的顺序在$a$之后，从$b$向$a$连一条边。这样就可以构造出一个$DAG$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不过，由于题目要求输出所有的顺序，所以我们跑拓扑序的时候得用$DFS$，每次从整个图中选择一个入度为$0$的点进行下一次搜索，而不是用队列头的点。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;另外，按照上述方法连边，得到的顺序是反序，总之得在排序之前把顺序调整正确。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其他的看代码。  
# 代码
```cpp
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXH = 305, MAXW = 35, MAXSIZ = 30;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct edge
{
	int to, nxt;
}Graph[MAXSIZ * MAXSIZ / 2];

struct circle
{
	int lx, ly, rx, ry;
	circle()
	{
		lx = ly = 10005;
		rx = ry = -1;
	}
}a[MAXSIZ];

vector<string> res;

int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
int head[MAXSIZ], into[MAXSIZ];
int mp[135];
char remp[MAXSIZ], tmp[MAXSIZ];
char board[MAXH][MAXW];
int H, W, cnt, tot;
bool used[MAXSIZ] = {};

void addEdge( const int from, const int to )
{
	cnt ++;
	Graph[cnt].to = to;
	Graph[cnt].nxt = head[from];
	into[to] ++;
	head[from] = cnt;
}

string trans( const char* str )
{
	string ans = "";
	for( int i = tot ; i >= 1 ; i -- )
	{
		ans.push_back( str[i] );
	}
	return ans;
}

void DFS( const int dep )
{
	if( dep > tot )
	{
		res.push_back( trans( tmp ) );
		return;
	}
	for( int i = 1 ; i <= tot ; i ++ )
	{
		if( ! used[i] && ! into[i] )
		{
			used[i] = true;
			for( int j = head[i] ; j ; j = Graph[j].nxt )
			{
				into[Graph[j].to] --;
			}
			tmp[dep] = remp[i];
			DFS( dep + 1 );
			used[i] = false;
			for( int j = head[i] ; j ; j = Graph[j].nxt )
			{
				into[Graph[j].to] ++;
			}
		}
	}
}

int main()
{
	int indx;
	read( H ), read( W );
	for( int i = 1 ; i <= H ; i ++ )
	{
		scanf( "%s", board[i] + 1 );
		for( int j = 1 ; j <= W ; j ++ )
		{
			if( 'A' <= board[i][j] && board[i][j] <= 'Z' && ! mp[board[i][j]] )
			{
				mp[board[i][j]] = ++tot;
				remp[tot] = board[i][j];
			}
			indx = mp[board[i][j]];
			a[indx].lx = MIN( a[indx].lx, i );
			a[indx].ly = MIN( a[indx].ly, j );
			a[indx].rx = MAX( a[indx].rx, i );
			a[indx].ry = MAX( a[indx].ry, j );
		}
	}
	for( int i = 1 ; i <= tot ; i ++ )
	{
		for( int j = a[i].lx ; j <= a[i].rx ; j ++ )
		{
			indx = mp[board[j][a[i].ly]];
			if( indx ^ i ) addEdge( indx, i );
			indx = mp[board[j][a[i].ry]];
			if( indx ^ i ) addEdge( indx, i );
		}
		for( int j = a[i].ly ; j <= a[i].ry ; j ++ )
		{
			indx = mp[board[a[i].lx][j]];
			if( indx ^ i ) addEdge( indx, i );
			indx = mp[board[a[i].rx][j]];
			if( indx ^ i ) addEdge( indx, i );
		}
	}
	DFS( 1 );
	ios :: sync_with_stdio( false );
	sort( res.begin(), res.end() );
	for( int i = 0 ; i < res.size() ; i ++ )
	{
		cout << res[i] << endl;
	}
	return 0;
}
```

---

## 作者：Bzy_temp (赞：1)

#没有用到拓扑排序~~（也不会用）~~,bfsAC没报时间，只是代码有点长




```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;//流操作命名空间 
char mp[35][35];//地图 
bool lt[30],gt[30],ud[30];
//lt出现字母//gt该字母是否已近可以解锁//ud该字母是否已经被解锁 
int edge[30][4];//每个字母框的四个边 
int a,b;//长宽 
string ans[10000];int pt=0;//答案+指针//排序输出 
//结构体//bfs时传递状态 
struct node{
    char  mp[35][35];
    bool  gt[30];
    bool  ud[30];//同上 
    char used[30];//记录过去解锁的字母 
    int point;
    node(){
        memset(mp,' ',sizeof(mp  ));
        memset(gt, 0 ,sizeof(gt  ));
        memset(ud, 0 ,sizeof(ud  ));
        memset(used,0,sizeof(used));
        point=0;//构造函数 
    }
};
queue<node>que;//队列bfs用 
//判断该状态是否可以输出，及是否全部解锁 
bool checkout(node nod){
    for(int i=0;i<=25;i++)if(lt[i] xor nod.ud[i])return false;
    return true;
}
//搜索这个字母是否可以解锁 
bool search(node nod,int index){
    for(int i=edge[index][0];i<=edge[index][1];i++){
        int now1=nod.mp[i][edge[index][2]];
        int now2=nod.mp[i][edge[index][3]];
        if(now1!=(char)(index+65) and now1!='*')return false;
        if(now2!=(char)(index+65) and now2!='*')return false;
    }
    for(int i=edge[index][2];i<=edge[index][3];i++){
        int now1=nod.mp[edge[index][0]][i];
        int now2=nod.mp[edge[index][1]][i];
        if(now1!=(char)(index+65) and now1!='*')return false;
        if(now2!=(char)(index+65) and now2!='*')return false;
    }
    return true;
}
//解锁这个字母 
node reclear(node nod,int index){
    for(int i=edge[index][0];i<=edge[index][1];i++){
        nod.mp[i][edge[index][2]]='*';
        nod.mp[i][edge[index][3]]='*';
    }
    for(int i=edge[index][2];i<=edge[index][3];i++){
        nod.mp[edge[index][0]][i]='*';
        nod.mp[edge[index][1]][i]='*';
    }
    return nod;
}
//初始化，寻找lt与edge 
void init(node nod){
    for(int i=0;i<=a-1;i++)for(int j=0;j<=b-1;j++){
        int now=nod.mp[i][j]-65;        if(now>=0 and now<=25){
            if(lt[now])edge[now][1]=i;
            else       edge[now][0]=i,lt[now]=true;
        }
    }
    for(int i=0;i<=29;i++)lt[i]=false;
    for(int i=0;i<=b-1;i++)for(int j=0;j<=a-1;j++){
        int now=nod.mp[j][i]-65;
        if(now>=0 and now<=25){
            if(lt[now])edge[now][3]=i;
            else       edge[now][2]=i,lt[now]=true;
        }
    }
}
//主函数//bfs 
int main(){
    cin>>a>>b;
    node all=*new node();
    for(int i=0;i<=a-1;i++)cin>>all.mp[i];//输入 
    init(all);que.push(all);//初始化 
    //bfs 
    while(!que.empty()){
        node now=que.front();que.pop();
        if(checkout(now)){
            //如果全部解锁成功,记录used 
            for(int i=now.point-1;i>=0;i--)ans[pt]+=now.used[i];
            pt++;
            continue;
        }
        for(int i=0;i<=25;i++)if(lt[i] xor now.gt[i]){
            //若果还没解锁，就搜索是否可以解锁 
            if(search(now,i))now.gt[i]=true;
        }
        for(int i=25;i>=0;i--)if(now.gt[i] xor now.ud[i]){
            //解锁所有可以解锁的//传递状态 
            node next=now;
            next.ud[i]=true;
            next=reclear(next,i);
            next.used[next.point++]=(char)(i+65);
            que.push(next);
        }
    }
    sort(ans,ans+pt);//排序输出 
    for(int i=0;i<=pt-1;i++)cout<<ans[i]<<"\n";
    return 0;
}
```

---

## 作者：_J_C_ (赞：1)

非常开心的用**暴力**过了这题……

虽说是暴力，还是要一点优化（**剪枝**）

首先是处理字符的问题。我用bool bExisted[26]表示这个字符是否出现过。（其中'A'的下标为0，'B'为1，以此类推）

然后我们再扫一遍bExisted给出现过的字符按照顺序分配hash值。（因为我们需要深搜，可以写for(i->26)，但我更喜欢for(i->end_of_hash)）

再然后就是处理矩形的问题，大家大概都能想到这个做法：因为这个矩形的每条边都会出现在最终图像中，所以我们可以扫描一遍图像，在相同字母中取最小的x作为矩形的left，最小的y作为矩形的top，最大的x作为矩形的right，最大的y作为矩形的bottom（这四个量分别是矩形的左、上、右、下边框）。注意，这个时候我们已经得到了每个字符的hash值，可以直接访问每个字符对应的矩形实例了。

哦对了，我们需要定义一个rect：

```cpp
class rect
{
public:
	rect() : left(11234), top(11234), right(-11234), bottom(-11234) {}//初始化
	int left, top, right, bottom;
}all[26];//由于只有26个大写字母，它只要开26个就够了。
```

然后就是搜索了。朴素的深搜大家都懂：枚举全排列，判断是否可行。（似乎只TLE一个点，而且O2也过不去的一个点）

优化：用cover**记录每个位置要被覆盖的次数**。

如下图：

```cpp
AAA..
A.BBB
A.B.B
AABBB
```

那么cover数组如下：

```cpp
11100
10211
10201
11211
```
即这个位置总共会被覆盖多少次。

这样有什么好处呢？如果当前放下去的矩形所要露出来的地方**cover不等于1**，那么我们现在把它放下去肯定是不合法的：因为cover不等于1，意味着这个位置**还要被后来的矩形覆盖**。

这样子就可以0msAC那个TLE的点了。

上代码：

```cpp
#include <cstdio>
#include <cstdlib>

#include <algorithm>

inline void GetMin(int& a, int b) { if (b < a) a = b; }
inline void GetMax(int& a, int b) { if(b > a) a = b; }

class rect
{
public:
    rect() : left(11234), top(11234), right(-11234), bottom(-11234) {}
    int left, top, right, bottom;
}all[26];
int iEnd;
int hash[26];
char val[26];
bool bExisted[26];

int n, m;

int cover[31][31];//覆盖次数
char map[31][31];//目标状态

char buf[31][31];//搜索时的状态
char old[26][31][31];//选择前的状态（回溯时用）
bool bUsed[26];//这个矩形是否已被放置
char out[26];//存储方案

void dfs(int now)
{
    if (now == iEnd)
    {
        printf("%s\n", out);
        return;
    }
    for (int i(0); i != iEnd; ++i)
    {
        if (bUsed[i]) continue;
        
        bool fail(false);
        
        for (int x(all[i].left); x <= all[i].right; ++x)
        {
            if (map[x][all[i].top] == val[i] && cover[x][all[i].top] != 1
                || map[x][all[i].bottom] == val[i] && cover[x][all[i].bottom] != 1)
            {
                fail = true;//这里在通过cover数组判断这么做是否可行，原理如前文所述
                break;
            }
        }
        if (fail) continue;
        for (int y(all[i].top); y <= all[i].bottom; ++y)
        {
            if (map[all[i].left][y] == val[i] && cover[all[i].left][y] != 1
                || map[all[i].right][y] == val[i] && cover[all[i].right][y] != 1)
            {
                fail = true;
                break;
            }
        }
        if (fail) continue;
        
        bUsed[i] = true;
        
        for (int x(all[i].left); x <= all[i].right; ++x)
        {
            old[now][x][all[i].top] = buf[x][all[i].top];//记录修改前将被修改的位置的状态
            old[now][x][all[i].bottom] = buf[x][all[i].bottom];
        }
        for (int y(all[i].top); y <= all[i].bottom; ++y)
        {
            old[now][all[i].left][y] = buf[all[i].left][y];
            old[now][all[i].right][y] = buf[all[i].right][y];
        }
        
        for (int x(all[i].left + 1); x < all[i].right; ++x)
        {
            buf[x][all[i].top] = val[i];//修改搜索状态
            buf[x][all[i].bottom] = val[i];
            --cover[x][all[i].top];//修改将被覆盖的次数
            --cover[x][all[i].bottom];
        }
        for (int y(all[i].top); y <= all[i].bottom; ++y)
        {
            buf[all[i].left][y] = val[i];//如上循环，只是矩形有四条边，所以分两个循环
            buf[all[i].right][y] = val[i];
            --cover[all[i].left][y];
            --cover[all[i].right][y];
        }
        
        out[now] = val[i];//标记方案
        dfs(now + 1);
        
        for (int x(all[i].left + 1); x < all[i].right; ++x)//回溯状态
        {
            buf[x][all[i].top] = old[now][x][all[i].top];
            buf[x][all[i].bottom] = old[now][x][all[i].bottom];
            ++cover[x][all[i].top];
            ++cover[x][all[i].bottom];
        }
        for (int y(all[i].top); y <= all[i].bottom; ++y)
        {
            buf[all[i].left][y] = old[now][all[i].left][y];
            buf[all[i].right][y] = old[now][all[i].right][y];
            ++cover[all[i].left][y];
            ++cover[all[i].right][y];
        }
        
        bUsed[i] = false;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i(0); i != n; ++i)
    {
        scanf("%s", map[i]);
        for (int j(0); j != m; ++j)
        {
            if (map[i][j] != '.') bExisted[map[i][j] - 'A'] = true;//标记该字符为“存在”
            buf[i][j] = '.';
        }
    }
    for (int i(0); i != 26; ++i)//为字符分配hash值（主要是需要hash连续排列，否则可以直接取其ASCII码
    {
        if (bExisted[i])
        {
            hash[i] = iEnd;
            val[iEnd++] = 'A' + i;//标记这个hash的原值
        }
    }
    for (int i(0); i != n; ++i)//寻找矩形的边界
    {
        for (int j(0); j != m; ++j)
        {
            if (map[i][j] != '.')
            {
                rect& x(all[hash[map[i][j] - 'A']]);
                GetMin(x.left, i);
                GetMin(x.top, j);
                GetMax(x.right, i);
                GetMax(x.bottom, j);
            }
        }
    }
    for (int i(0); i != iEnd; ++i)
    {
        for (int x(all[i].left + 1); x < all[i].right; ++x)
        {
            ++cover[x][all[i].top];//初始化cover
            ++cover[x][all[i].bottom];
        }
        for (int y(all[i].top); y <= all[i].bottom; ++y)
        {
            ++cover[all[i].left][y];
            ++cover[all[i].right][y];
        }
    }
    dfs(0);//寻找方案，输出
    return 0;
}
```


---

## 作者：Vector_Mingfan (赞：0)

[题目由此去](https://www.luogu.com.cn/problem/P2741)
------------
~~一道非常恶心的题目（~~

以上为感受

------------


### 题目大意：

$1.$ 有一堆中空的矩形框，一个框由一种大写字母构成且一种字母只出现一次 ~~【看到到这儿，就有点当初刚学OI时的一道题有点像（大雾弥漫】~~。

$2.$ 这些框宽为$1$，每条边的长度都至少$3$。

$3.$ 求从底层至最上层的框顺序，有多个答案就按字典序输出

------------
### 分析:

再看分析之前要先保证回$string$和$char$的一些用法。

$First.$因为
“${\color{red}\colorbox{blue}{一个角同时属于两条边}}$”，于是我们保存每个矩形的左上角坐标与右下角坐标，就确定了整个矩形。

$Next.$可以看出，最上层的矩形是完整的，于是它可以作为本题突破口。

（一）从上层往底层，逐层搜索完整的矩形

$1.$ 按字符从大到小搜索矩形

$2.$ 当该矩形只含 “ . ”  $or$ 该矩形的字母时，就是符合题意的。

$3.$ 若矩形符合题意，就将其字符放入栈中，然后全部变成 “ . ” ， 删除该矩形

$4.$ ${\color{red}DFS}$：将当层删去的矩形恢复成删前的样子，注意不是恢复成输入时的样子。


------------
上代码：
```
#include <bits/stdc++.h>
using namespace std;

const int MAXX = 35;
const int INF = 0x7fffffff/2;

struct Nice {
	int x1 , y1 , x2 , y2;
}tc[MAXX];
int h , w , cnt , cntans;
char g[MAXX][MAXX] , c[MAXX] , ans[MAXX] , Ans[MAXX * MAXX][MAXX] , tp[MAXX];
bool v[MAXX] , flag[MAXX];
int dx[] = {1 , 0 , -1 , 0} , dy[] = {0 , 1 , 0 , -1};

bool cmp(int a , int b) {
	return a > b;
}

int Cmp(const void *a , const void *b) {
	char *s1 = (char *)a , *s2 = (char *)b;
	return strcmp(s1 , s2);
}

bool dfs(int x , int y , int xx , int yy) {
	if (x == tc[xx].x1 && y == tc[xx].y1 && yy == 3) {
		g[x][y] = '.';
		return 1;
	}
	if (!(g[x][y] == '.' || g[x][y] - 'A' == xx)) {
		return  0;
	}
	if (x == tc[xx].x2 && y == tc[xx].y1 ) {
		if (dfs(x , y + 1 , xx , yy + 1)) {
			g[x][y] = '.';
			return 1;
		}
		else return 0;
	}
	else if (x == tc[xx].x2 && y == tc[xx].y2 ) {
		if (dfs(x - 1 , y , xx , yy + 1)) {
			g[x][y] = '.';
			return 1;
		}
		else return 0;
	}
	else if (x == tc[xx].x1 && y == tc[xx].y2 ) {
		if (dfs(x , y - 1 , xx , yy + 1)) {
			g[x][y] = '.';
			return 1;
		}
		else return 0;
	}
	else {
		if (dfs(x + dx[yy] , y + dy[yy] , xx , yy)) {
			g[x][y] = '.';
			return 1;
		}
		else return 0;
	}
}

void work(int x , int y , int xx , int yy) {
	g[x][y] = xx + 'A';
	if(x == tc[xx].x1 && y == tc[xx].y1 && yy == 3) {
		return;
	}
	if(x == tc[xx].x2 && y == tc[xx].y1) {
		work(x , y + 1 , xx , yy+1);
	}
	else if(x == tc[xx].x2 && y == tc[xx].y2) {
		work(x - 1 , y , xx , yy + 1);
	}
	else if(x == tc[xx].x1 && y == tc[xx].y2) {
		work(x , y - 1 , xx , yy + 1);
	}
	else {
		work(x + dx[yy] , y + dy[yy] , xx , yy);
	}
}

void DFS(int xi , int yi) {
	if (yi == cnt) {
		for (int i=yi-1; i>=0; i-- ) {
			tp[yi - 1 - i] = ans[i];
		}
		memcpy(Ans[cntans++ ] , tp , sizeof(tp));
		return ;
	}
	for (int i=1; i<=cnt; i++ ) {
		if (!flag[i] && dfs(tc[c[i]].x1 , tc[c[i]].y1 , c[i] , 0)) {
			flag[i] = 1;
			ans[yi] = c[i] + 'A';
			DFS(i , yi + 1);
			work(tc[c[i]].x1 , tc[c[i]].y1 , c[i] , 0);
			flag[i] = 0;
		}
	}
}

void Work() {
    for (int i=1; i<=h; i++) {
    	scanf("%s",g[i] + 1);
    	for(int j=1; j<=w; j++) {
	    	if(g[i][j] != '.') {
	    		int kkk=g[i][j] - 'A';
	    		if(i < tc[kkk].x1 || j < tc[kkk].y1 ) {
	    			tc[kkk].x1 = min(tc[kkk].x1 , i);
					tc[kkk].y1 = min(tc[kkk].y1 , j);	    			
				}
	    		if(i > tc[kkk].x2 || j > tc[kkk].y2 ) {
	    			tc[kkk].x2 = max(tc[kkk].x2 , i);
					tc[kkk].y2 = max(tc[kkk].y2 , j);	    			
				}
	    		if(!v[kkk]) {
	    			v[kkk] = 1;
	    			c[++cnt] = kkk;
				}
			}
		}
	} 
}

int main(void ) {
	scanf("%d %d",&h,&w);
	for (int i=0; i<26; i++ ) {
		tc[i].x1 = INF;
		tc[i].y1 = INF;
		tc[i].x2 = 0;
		tc[i].y2 = 0;
	}
	Work();
	sort(c + 1 , c + cnt + 1 , cmp);
	DFS(-1 , 0);
	qsort(Ans , cntans , sizeof(char)*55 , Cmp);
	for (int i=0; i<cntans; i++ ) {
		cout << Ans[i];
	}
}

/*
in:
9 8
.CCC....
ECBCBB..
DCBCDB..
DCCC.B..
D.B.ABAA
D.BBBB.A
DDDDAD.A
E...AAAA
EEEEEE..
out:
EDABC
*/  
```
 我：“AC！AC！AC！啊。。。WA*还RE。”很惨44分。

 心想：RE改改就好。。。可是数组开大了RE的点又变成WA。。。

So!改！

经过思考：貌似要vector和stack。

额。。。在150多行的代码中加vector和stack。。。可海星。

中途对小号私信发泄。。。~~内容为【数据删除，请自行想象|A|】~~

提出我最后的AC代码：
```cpp
//stack（堆栈） 提供了堆栈的全部功能，也就是说实现了一个先进后出的
#include <bits/stdc++.h>
#include <vector>
#include<stack>
using namespace std;

const int MAXX = 50 + 5;
const int INF = 0x3f3f3f3f;

vector<string> Ans;//记录最终答案并用来排字典序
stack<char> mx;//储存旧图信息，方便回溯 
//被逼无奈才用vector和stack 
struct Nice {
	int x1 , y1 , x2 , y2;
}tc[MAXX];
int h , w , cnt , cntans;
char g[MAXX][MAXX] , c[MAXX] , ans[MAXX] , tp[MAXX];
bool v[MAXX] , flag[MAXX];
int dx[4] = {1 , 0 , -1 , 0} , dy[4] = {0 , 1 , 0 , -1};


bool cmp(int a , int b) {
	return a > b;
}

bool dfs(int x , int y , int xx , int yy) {
	if (!(g[x][y] == '.' || g[x][y] - 'A' == xx)) {
		return 0;
	}
	if (x == tc[xx].x1 && y == tc[xx].y1 && yy == 3) {
		mx.push(g[x][y]) , g[x][y] = '.';
		return 1;
	}

	if (x == tc[xx].x2 && y == tc[xx].y1 ) {
		if (dfs(x , y + 1 , xx , yy + 1)) {
			mx.push(g[x][y]) , g[x][y] = '.';
			return 1;
		}
		else return 0;
	}
	else if (x == tc[xx].x2 && y == tc[xx].y2 ) {
		if (dfs(x - 1 , y , xx , yy + 1)) {
			mx.push(g[x][y]) , g[x][y] = '.';
			return 1;
		}
		else return 0;
	}
	else if (x == tc[xx].x1 && y == tc[xx].y2 ) {
		if (dfs(x , y - 1 , xx , yy + 1)) {
			mx.push(g[x][y]) , g[x][y] = '.';
			return 1;
		}
		else return 0;
	}
	else {
		if (dfs(x + dx[yy] , y + dy[yy] , xx , yy)) {
			mx.push(g[x][y]) , g[x][y] = '.';
			return 1;
		}
		else return 0;
	}
}

void work(int x , int y , int xx , int yy) {
	g[x][y] = mx.top();
	mx.pop();
	if(x == tc[xx].x1 && y == tc[xx].y1 && yy == 3) {
		return;
	}
	if(x == tc[xx].x2 && y == tc[xx].y1) {
		work(x , y + 1 , xx , yy + 1);
	}
	else if(x == tc[xx].x2 && y == tc[xx].y2) {
		work(x - 1 , y , xx , yy + 1);
	}
	else if(x == tc[xx].x1 && y == tc[xx].y2) {
		work(x , y - 1 , xx , yy + 1);
	}
	else {
		work(x + dx[yy] , y + dy[yy] , xx , yy);
	}
}

void DFS(int xi , int yi) {
	if (yi == cnt) {
		string sss; 
		for (int i=yi-1; i>=0; i-- ) {
			sss += ans[i]; 
		}
		Ans.push_back(sss);
		sss.clear();
		return ;
	}
	for (int i=1; i<=cnt; i++ ) {
		if (!flag[i]) {
			if (dfs(tc[c[i]].x1 , tc[c[i]].y1 , c[i] , 0)) {
				flag[i] = 1;
				ans[yi] = c[i] + 'A';
				DFS(i , yi + 1);
				work(tc[c[i]].x1 , tc[c[i]].y1 , c[i] , 0);
				flag[i] = 0;				
			}
		}
	}
}

void Work() {
    for (int i=0; i<h; i++) {
    	scanf("%s",g[i]);
    	for(int j=0; j<w; j++) {
	    	if(g[i][j] != '.') {
	    		int kkk = g[i][j] - 'A';
	    		tc[kkk].x1 = min(tc[kkk].x1 , i);
				tc[kkk].y1 = min(tc[kkk].y1 , j);
	    		tc[kkk].x2 = max(tc[kkk].x2 , i);
				tc[kkk].y2 = max(tc[kkk].y2 , j);
	    		if(!v[kkk]) {
	    			v[kkk] = 1;
	    			c[++cnt] = kkk;
				}
			}
		}
	}
}

int main() {
	scanf("%d %d",&h,&w);
	for (int i=0; i<50; i++ ) {
		tc[i].x1 = INF;
		tc[i].y1 = INF;
		tc[i].x2 = 0;
		tc[i].y2 = 0;
	}
	Work();
	sort(c + 1 , c + cnt + 1 , cmp);
	DFS(-1 , 0);
	sort(Ans.begin(),Ans.end());
	for (int i=0; i<Ans.size() ; i++ ) {
		cout << Ans[i] << "\n";
	}
}

/*
in:
9 8
.CCC....
ECBCBB..
DCBCDB..
DCCC.B..
D.B.ABAA
D.BBBB.A
DDDDAD.A
E...AAAA
EEEEEE..
out:
EDABC
*/ 
```
感觉是做复杂了。。。看来VC还是那样弱啊qwq

#### 这篇题解都到这里了，求管理给过qwq



---

## 作者：Celebrate (赞：0)

这道题是我在USACO里面用时最久的一道~~好了不废话了~~

这一道题正解是拓扑，但是我觉得拓扑比暴力更好打。。。。

思路：

因为“矩形的每条边中，至少有一部分是可见的”，所以我们只

需要根据边来找出矩形的左上角和右上角

然后搜索每一个矩阵，如果这个矩阵被别的矩阵覆盖了，就与

另外一个矩阵建立一条边，然后拓扑一次就好了

注：没有被连接的矩形才是最底的（当前），这样可以省去很

的步骤

代码如下：

```cpp
#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;
struct node
{
    int x,y,next;
}a[5100];int len,last[51];//边，表示要先用了这一个矩阵才能用下一个矩阵 
int s[51];//表示有多少个矩阵在这一个点的上面 
struct node1
{
    int x1,y1;
    int x2,y2;
    node1()
    {
    	x1=y1=100;
    }
}g[51];//记录左上和右下 
inline void ins(int x,int y)//建边 
{
    len++;
    a[len].x=x;a[len].y=y;s[y]++;
    a[len].next=last[x];last[x]=len;
}
int n,m,length,d[51];//length表示出现的矩阵的次数，d为编目录优化，这个还挺有用的 
int f[51][51];//地图 
bool v[51];//这种型号的矩阵是否有 
inline void find(int k)//查找为k的矩阵 
{
	bool bk[51];memset(bk,true,sizeof(bk));//记录那种矩形是否被找过，如果找过了，就没有必要多建边了 
    for(int j=g[k].y1;j<=g[k].y2;j++)//先找上下 
    {
        if(f[g[k].x1][j]!=k && bk[f[g[k].x1][j]]==true) 
		{
			ins(k,f[g[k].x1][j]);
			bk[f[g[k].x1][j]]=false;
		}
        if(f[g[k].x2][j]!=k && bk[f[g[k].x2][j]]==true) 
		{
			ins(k,f[g[k].x2][j]);
			bk[f[g[k].x2][j]]=false;
		}
    }
    for(int i=g[k].x1;i<=g[k].x2;i++) //再找左右 
    {
        if(f[i][g[k].y1]!=k && bk[f[i][g[k].y1]]==true) 
		{
			ins(k,f[i][g[k].y1]);
			bk[f[i][g[k].y1]]=false;
		}
        if(f[i][g[k].y2]!=k && bk[f[i][g[k].y2]]==true) 
		{
			ins(k,f[i][g[k].y2]);
			bk[f[i][g[k].y2]]=false;
		}
    }
}
int b[51];//记录拓扑时的队列 
inline void tuopu(int x,int t)//删边或者回溯 
{
    for(int k=last[x];k;k=a[k].next)
    {
        int y=a[k].y;
        s[y]+=t;
    }
}
void dfs(int k)//拓扑排序，k表示现在队列里有k-1个 
{
    if(k==length+1)//如果到达了 
    {
       	for(int i=1;i<k;i++) printf("%c",b[i]+'A'-1);//变为字符串然后输出 
        printf("\n");return;
    }
    for(int i=1;i<=length;i++)//枚举 
    {
        if(v[d[i]]==true)//如果没有被找过 
        {
            if(s[d[i]]==0)//如果地下没有矩形了 
            {
                v[d[i]]=false;
                b[k]=d[i];//记录 
                tuopu(d[i],-1);//伪删边 
                dfs(k+1);//往下搜索 
                v[d[i]]=true;//回溯 
                b[k]=0;
                tuopu(d[i],1);
            }
        }
    }
}
inline int cmp(const void *xx,const void *yy)//排序 
{
	int x=*(int*)xx;
	int y=*(int*)yy;
	if(x>y) return 1;
	if(x<y) return -1;
	return 0;
}
int main()
{
    char st[51];int i,j;
    scanf("%d%d",&n,&m);
    memset(v,false,sizeof(v));
    for(i=1;i<=n;i++)
    {
        scanf("%s",st+1);
        for(j=1;j<=m;j++)
        {
            if(st[j]=='.') continue;//不用管没有的 
            f[i][j]=st[j]-'A'+1;
            if(v[f[i][j]]==false)
            {
                v[f[i][j]]=true;
                length++;d[length]=f[i][j];
            }
            g[f[i][j]].x1=min(g[f[i][j]].x1,i);//记录左上角和右下角 
            g[f[i][j]].y1=min(g[f[i][j]].y1,j); 
            g[f[i][j]].x2=max(g[f[i][j]].x2,i);
            g[f[i][j]].y2=max(g[f[i][j]].y2,j);
        }
    }
    qsort(d+1,length,sizeof(int),cmp);//记得排序目录 
    for(i=1;i<=length;i++)//找一次 
    {
        find(d[i]);
    }
    dfs(1);//拓扑排序 
    return 0;
}
```

---

## 作者：vinvor (赞：0)

拓扑排序

由题意可知，不存在一个矩形的一条边被完全覆盖，所以我们可以计算出矩形的坐标。读入时记录矩形的每个点中最小x1，最小y1，最大x2，最大y2。可知左上角(x1，y1)右下角(x2，y2)右上角(x2，y1)左下角(x1，y2)。查找该矩形A边上，非该矩形的字母B，即覆盖矩形A被矩形B覆盖。建立一条有向边B->A，表示B是A的必要条件。然后进行拓扑排序，搜索求所有的拓扑序列，并排序输出。

注意，该题中的字母可能不连续，不要直接for(i='A';i<='Z';i++)。

字符串处理

每次找到一个完全框（也就是这个框的所有字母都可见，要么是原来的字母，要么是“\*”，“\*”是后面用到的临时标记），拿掉，把框上的所有字母都标记为“\*”。重复上述过程直到所有框都被拿掉。因为要求输出所有答案，所以用dfs来寻找所有解。

下附代码：

```cpp
#include<bits/stdc++.h> 
#define rep(i, n) for(int i = 1; i <= n;i++)
using namespace std;
int w, h, p, l[50], r[50], u[50], d[50], D[50];
char mapp[50][50], _p[50];
bool a[50], g[50][50];
void dfs(){
    bool flag = 0;
    rep(i, 26)
        if(a[i]){
            flag = 1;
            break;
        }
    if(!flag){
        rep(i, p)
            printf("%c", _p[i]);
        printf("\n");
        return;
    }
    rep(i, 26)
        if(a[i] && D[i] == 0){
                _p[++p] = i + '@';
                rep(j, 26)
                    if(g[i][j])
                        D[j]--;
                a[i] = 0;
                dfs();
                rep(j, 26)
                    if(g[i][j])
                        D[j]++;
                a[i] = 1;
                p--;
        }
}
int main(){
    ios::sync_with_stdio(false);
    scanf("%d%d", &w, &h);
    rep(i, w){
        scanf("\n");
        rep(j, h){
            char c = getchar();
            mapp[i][j] = c;
            if(!l[c - '@'] || j < l[c - '@'])
                l[c - '@'] = j;
            if(!r[c - '@'] || j > r[c - '@'])
                r[c - '@'] = j;
            if(!u[c - '@'] || i < u[c - '@'])
                u[c - '@'] = i;
            if(!d[c - '@'] || i > d[c - '@'])
                d[c - '@'] = i;
            a[c - '@'] = 1;
        }
    }
    memset(g, 0, sizeof(g));
    rep(i, 26)
        if(a[i]){
            for(int j = l[i]; j <= r[i]; j++){
                if(mapp[u[i]][j] != '.')
                    g[i][mapp[u[i]][j] - '@'] = 1;
                if(mapp[d[i]][j] != '.')
                    g[i][mapp[d[i]][j] - '@'] = 1;
            }
            for(int j = u[i]; j <= d[i]; j++){
                if(mapp[j][l[i]] != '.')
                    g[i][mapp[j][l[i]] - '@'] = 1;
                if(mapp[j][r[i]] != '.')
                    g[i][mapp[j][r[i]] - '@'] = 1;
            }
        }
    rep(i, 26)
        rep(j, 26)
            if(i != j && g[i][j])
                D[j]++;
    p = 0;
    dfs();
    return 0;
}
```

---

## 作者：Drinkwater (赞：0)

这道题真心难搞，细节比较多，对于像我这样的蒟蒻，代码基础不是很好，生生调了一个下午才搞对，这道题我们看到题目给出的条件说：

矩形的边的宽度为 1 ，每条边的长度都不小于 3 。


矩形的每条边中，至少有一部分是可见的。注意，一个角同时属于两条边。


矩形用大写字母表示，并且每个矩形的表示符号都不相同。

这样的话我们可以首先预处理搞出每个矩形的左上角和右下角，然后扫描矩形的每一条边，遇到不是本矩形自身的字母，我们就加一条边s[i][j]，表示i被j覆盖，这样搞完后，我们直接跑拓扑排序就好，但是我们要处理处每种可能的情况，所以我们要用dfs而不是for循环了，在网上学习了一下拓扑排序，没想到就是楼下的，好巧啊，但是预处理等其他的并没有抄袭，大家可以借鉴一下（蒟蒻连拓扑排序都不会555~）这个拓扑排序算是写的很好的了，（题解才两篇，管理员大人帮忙过下）

/*************************************************************************

    > Author: Drinkwater-cnyali
    > Created Time: 2017/5/6 14:44:08
************************************************************************/













```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int maxn = 100000;
const int inf = 0x3f3f3f3f;
int n,m;
char Map[40][40];
struct node { int x,y;};node M[40][2];
void init()
{
    REP(i,1,31)
    {
        REP(l,1,31)
            REP(r,1,31)
                M[i][0].x = -inf,M[i][0].y = -inf;
        REP(l,1,31)
            REP(r,1,31)
                M[i][1].x = inf,M[i][1].y = inf;
    }
}
int id[40],cnt,vis[40],s[40][40],deg[40],ans[40],ff;
map<string,bool>mp;
vector<string> as;
void topsort(int x,string now)
{
    if(x > cnt && !mp[now])
    {
        mp[now] = 1;
        as.push_back(now);
        return ;
    }
    REP(i,1,cnt)
    {
        if(!deg[id[i]] && !vis[id[i]])
        {
            vis[id[i]] = 1;
            deg[id[i]] = -1;
            REP(j,1,cnt)
                if(s[id[i]][id[j]])
                    deg[id[j]]--;
            topsort(x+1,now+char(id[i]+'A'-1));
            REP(j,1,cnt)
                if(s[id[i]][id[j]])
                    deg[id[j]]++;
            deg[id[i]] = 0,vis[id[i]] = 0;
        }
    }
}
int main()
{
    n = read(), m = read();
    init();
    for(int i = 1; i <= n; i++)
    {
        scanf("%s",Map[i]);
        int Len = strlen(Map[i]);
        for(int j = 0; j < Len;++j)
        {
            if(Map[i][j] == '.')continue;
            int T = Map[i][j] - 'A' +1;
            if(!vis[T])id[++cnt] = T,vis[T] = 1;
            M[T][0].x = max(M[T][0].x,i);
            M[T][0].y = max(M[T][0].y,j);
            M[T][1].x = min(M[T][1].x,i);
            M[T][1].y = min(M[T][1].y,j);
        }
    }
    /*REP(i,1,cnt)
    {
        int T = id[i];
        cout<<T<<endl;
        cout<<M[T][0].x<<" "<<M[T][0].y+1<<endl;
        cout<<M[T][1].x<<" "<<M[T][1].y+1<<endl;
        cout<<"~~~~"<<endl;
    }*/memset(s,0,sizeof(s));
    REP(k,1,cnt)
    {
        int T = id[k],c;
        int Mx = M[T][1].x,My = M[T][1].y,Fx = M[T][0].x,Fy = M[T][0].y;
        REP(i,Mx,Fx)
        {
            if(Map[i][My] != '.')
            {
                c = Map[i][My]-'A'+1;
                if(!s[T][c] && T != c)s[T][c] = 1,deg[c]++;
            }
            if(Map[i][Fy] != '.')
            {
                c = Map[i][Fy]-'A'+1;
                if(!s[T][c] && T != c)s[T][c] = 1,deg[c]++;
            }
        }
        REP(i,My,Fy)
        {
            if(Map[Mx][i]!='.')
            {
                c = Map[Mx][i]-'A'+1;
                if(!s[T][c] && T != c)s[T][c] = 1,deg[c]++;
            }
            if(Map[Fx][i]!='.')
            {
                c = Map[Fx][i]-'A'+1;
                if(!s[T][c] && T != c)s[T][c] = 1,deg[c]++;
            }
        }
    }
    /*REP(i,1,cnt)
    {
        cout<<"!!!"<<id[i]<<endl;
        REP(j,1,cnt)if(s[id[i]][id[j]])cout<<id[j]<<" ";
        cout<<endl;
    }*/
    memset(vis,0,sizeof(vis));
    topsort(1,"");
    sort(as.begin(),as.end());
    REP(i,0,as.size()-1)
        cout<<as[i]<<endl;
    return 0;
}

```

---

## 作者：Skywalker_David (赞：0)

【分析】：

首先对于每种字符，会组成不同矩形，统计这些矩形的左上角<即最左值和最上值>，右上角<即最右值和最下值>，然后建图：若本来在该矩形的边上存在不同于该矩形的字符，则将该矩形和不同于该矩形的字符对应的矩形编号连一条有向边，然后跑一边拓扑排序，注意，不同的拓扑序可能造成答案不同，因此用DFS来枚举所有拓扑序而不仅仅只跑一遍，最后对答案排序，输出即可

【时间复杂度】：

设字符种类为kind，则建图过程复杂度为O(kind\*H\*W)，统计入度O(kind\*kind)，拓扑排序O(kind\*kind\*kind)

【代码】：

                                      
                    
```cpp
#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#include<algorithm>  
#include<iostream>  
#include<vector>  
#include<stack>  
#include<queue>  
#include<map>  
using namespace std;  
#define MAX 31  
#define MAXN 101  
#define IMAX 21474836  
struct rectangle  
{  
      int l,r,u,d;  
      void reset(){l=IMAX,r=0,u=IMAX,d=0;}  
};  
rectangle a[MAX];  
int H,W,kind=0,indegree[MAXN];  
char in[MAX][MAX];  
bool visin[MAXN],map1[MAX][MAX],vis[MAXN];  
map<char,int> number;  
map<int,char> word;  
map<string,bool> hash;  
string empty;  
vector<string> ans;  
void pre_group()  
{  
      for(int i=1;i<=kind;i++)  
      {  
            for(int j=a[i].l;j<=a[i].r;j++)  
            {  
                  if(in[a[i].u][j]!=word[i] && in[a[i].u][j]!='.')  
                        map1[i][number[in[a[i].u][j]]]=true;  
                  if(in[a[i].d][j]!=word[i] && in[a[i].d][j]!='.')  
                        map1[i][number[in[a[i].d][j]]]=true;                    
            }  
            for(int j=a[i].u;j<=a[i].d;j++)  
            {  
                  if(in[j][a[i].l]!=word[i] && in[j][a[i].l]!='.')  
                        map1[i][number[in[j][a[i].l]]]=true;  
                  if(in[j][a[i].r]!=word[i] && in[j][a[i].r]!='.')  
                        map1[i][number[in[j][a[i].r]]]=true;                    
            }  
      }  
      for(int i=1;i<=kind;i++)  
            for(int j=1;j<=kind;j++)  
                  if(map1[i][j])  
                       indegree[j]++;  
}  
void topsort(int floor,string now)  
{  
      if(floor==kind+1 && !hash[now])  
      {  
            hash[now]=true;  
            ans.push_back(now);  
            return;  
      }  
      for(int i=1;i<=kind;i++)  
      {  
            if(indegree[i]==0 && !vis[i])  
            {  
                   vis[i]=true;  
                   indegree[i]=-1;  
                   for(int j=1;j<=kind;j++)  
                         if(map1[i][j])  
                               indegree[j]--;  
                   topsort(floor+1,now+(char)word[i]);  
                   for(int j=1;j<=kind;j++)  
                         if(map1[i][j])  
                               indegree[j]++;  
                   indegree[i]=0;  
                   vis[i]=false;  
            }  
      }  
}  
int main()  
{  
      scanf("%d%d",&H,&W);  
      for(int i=1;i<=H;i++)  
      {  
            scanf("\n");  
            for(int j=1;j<=W;j++)  
            {  
                  scanf("%c",&in[i][j]);  
                  if(!visin[in[i][j]] && in[i][j]!='.')  
                  {  
                        kind++;  
                        visin[in[i][j]]=true;  
                        number[in[i][j]]=kind;  
                        word[kind]=in[i][j];  
                        a[number[in[i][j]]].reset();  
                  }  
                  a[number[in[i][j]]].l=min(j,a[number[in[i][j]]].l);  
                  a[number[in[i][j]]].r=max(j,a[number[in[i][j]]].r);  
                  a[number[in[i][j]]].u=min(i,a[number[in[i][j]]].u);  
                  a[number[in[i][j]]].d=max(i,a[number[in[i][j]]].d);  
            }  
      }  
      pre_group();  
      topsort(1,empty);  
      sort(ans.begin(),ans.end());  
      for(int i=0;i<(int)ans.size();i++)  
            cout<<ans[i]<<endl;  
      return 0;  
}
```

---

