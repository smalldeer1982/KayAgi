# Find a Number

## 题目描述

给定两个正整数 $d$ 和 $s$。请你找到最小的正整数 $n$，使得 $n$ 能被 $d$ 整除且其各位数字之和等于 $s$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
13 50
```

### 输出

```
699998
```

## 样例 #2

### 输入

```
61 2
```

### 输出

```
1000000000000000000000000000001
```

## 样例 #3

### 输入

```
15 50
```

### 输出

```
-1
```

# 题解

## 作者：是个汉子 (赞：4)

### Solution

本来想的是枚举 $d$ 的倍数的，以为一定能搜到解的，然后看了眼英文发现“无解输出-1”，就果断去想搜索了。

用啥搜？

因为这个题要求最小数 $n$ ，所以不能用dfs，应该用bfs+记忆化搜索，这样是可以保证最小的。

然后设计搜啥？

因为只和各位相加和 $s$ 与 $d|n$ 有关，所以可以将原来bfs换成存储此时数字和此时各位之和，往下搜就是从 $0$~$9$ 枚举增加的这一位。同时拿一个数组 $p[dx][dy]$ 记录当数字是 $dx$ ，数位之和是 $dy$ ，储存从 $x,y$ 这个状态而来，枚举的 $i$ 。拿 $pair$ 就行了。

是不是这样就完了？

当然不是。当你建 $p$ 数组的时候，你就会又和我本来的枚举想法一样，不知道要建多大。想先打个过样例的，发现样例二自己就不行了。所以要优化，可以将第一维转化为数字 $\%d$ 的值，因为bfs所以答案还是对的。

空间复杂度： $O(ns)$ 

### 代码

```c++
#include<bits/stdc++.h>
#define PII pair<int,int>

using namespace std;
const int D=510,S=5010;
int d,s;
bool vis[D][S];
queue<PII> q;
pair<PII,int> p[D][S];

inline void bfs(){
    vis[0][0]=true;
    q.push(make_pair(0,0));
    while(!q.empty()){
        int x=q.front().first,y=q.front().second;
        q.pop();
        for(int i=0;i<10;i++){
            int dx=(x*10+i)%d,dy=y+i;
            if(dy<=s&&!vis[dx][dy]){
                vis[dx][dy]=true;
                p[dx][dy]=make_pair(make_pair(x,y),i);
                q.push(make_pair(dx,dy));
            }
        }
    }
}

void print(int x,int y){	//注意这里的输出和我的记录方式是对应的
    if(!x&&!y) return ;
    print(p[x][y].first.first,p[x][y].first.second);
    putchar('0'+p[x][y].second);
}

int main(){
    scanf("%d%d",&d,&s);
    bfs();
    if(!vis[0][s]) puts("-1");
    else print(0,s);
    return 0;
}
```



---

## 作者：Phartial (赞：2)

## 思路

### 设计状态

首先考虑最粗暴的状态设计 $[n]$，直接将整个数作为状态，可是看到样例二输出的天文数字，显然此状态设计不合理。

考虑优化，因为题目要求结果各个位数之和为 $s$，所以我们可以先给状态添加一个属性 $x$，表示当前各个位数之和，此时状态为 $[n,x]$ ~~看上去更不可做了~~。

别急，再看到第一个条件，这种对余数有特殊要求的条件都有一个固定的套路，就是直接把余数 $m$ 也加进状态中，此时状态为 $[n,x,m]$，而我们又发现这个数字具体是几与转移没关系，所以可以直接扔掉这个属性。

但题目最后还要输出，可以考虑存下每个状态是由哪一个状态转移过来的，输出时倒着输出当前状态的 $x$ 和前一个状态的 $x$ 的差即可，最终属性为 $[x,m,p]$，其中 $p$ 为前一个状态。

### 设计转移

最直观的想法就是每次在末尾添加一个数，由于题目要求 $n$ 最小，所以需要从小到大对每个数转移一遍，用 BFS 实现更为方便。

于是转移就出来了：

$$ [x,m,p] \Rightarrow [x+i,(10\times m+i)\ \%\ d,h] $$

（设当前状态编号为 $h$，$i$ 从 $0$ 到 $9$ 顺序枚举）

## 实现

```cpp
#include <iostream>

using namespace std;

const int kD = 501;
const int kS = 5001;

struct Q {
  int x, m, p;  // 状态为 [x,m,p]
} q[kD * kS];

int d, s, h = 1, t, ans, st[kD * kS];
bool v[kS][kD];

bool R(int x, int m, int p) {         // 转移状态
  if (x <= s && !v[x][m]) {           // 如果数字和不大于s且此状态是第一次到
    q[++t] = {x, m, p}, v[x][m] = 1;  // 入队，标记状态
    if (x == s && m == 0) {           // 如果出解
      ans = t;                        // 记录
      return 1;
    }
  }
  return 0;
}

bool B() {                                            // 使用 BFS 求解
  for (R(0, 0, 0); h <= t; ++h) {                     // 初始化，初始状态为 [0,0,0]
    for (int i = 0; i <= 9; ++i) {                    // 0到9顺序转移
      if (R(q[h].x + i, (10 * q[h].m + i) % d, h)) {  // 转移，如果出解
        return 1;                                     // 返回有解
      }
    }
  }
  return 0;  // 否则无解
}

int main() {
  cin >> d >> s;
  if (!B()) {    // 如果无解
    cout << -1;  // 输出-1
  } else {
    t = 0;
    for (int i = ans; q[ans].p; ans = q[ans].p) {
      st[++t] = q[ans].x - q[q[ans].p].x;  // 由于需要倒着输出，所以先用一个栈存下来
    }
    for (; t; --t) {  // 输出
      cout << st[t];
    }
  }
  return 0;
}
```


---

## 作者：hehe012 (赞：2)

```cpp
//bfs做法 
#include<bits/stdc++.h>
using namespace std;
struct num{
	int mod,sum,val;
}f[510][5010];// 记录每一种情况 
queue<num> q;
int d,s,ans1,ans[10000000];
void print(){//输出 
	ans1=0;
	num x;
	x.mod=x.val=0;
	x.sum=s;
	while(f[x.mod][x.sum].val!=-1){
		ans[++ans1]=f[x.mod][x.sum].val;
		x=f[x.mod][x.sum];
	}
	for(int i=ans1-1;i>=1;i--)printf("%d",ans[i]);
}
int main(){
	memset(f,-1,sizeof f);
	cin>>d>>s;
	num st;
	f[0][0].val=0; f[0][0].mod=d+1, f[0][0].sum=s+1;
	f[d+1][s+1].val=-1;
	st.mod=0,st.sum=0;//初始化 
	q.push((num)st);
	while(!q.empty()){//bfs 
		num tmp=q.front();
		q.pop();
		for(int i=0;i<=9;i++){//枚举1~9 
			if(tmp.sum+i<=s){//和要小于s 
				num nxt;
				nxt.mod=(tmp.mod*10+i)%d;
				nxt.sum=tmp.sum+i;//新的数 
				if(f[nxt.mod][nxt.sum].val!=-1)continue;//若已有更小解 
				f[nxt.mod][nxt.sum]=tmp;
				f[nxt.mod][nxt.sum].val=i;
				q.push((num)nxt);//压入队列 
				if(!nxt.mod&&nxt.sum==s){//输出满足条件的最小解 
					print();
					return 0;
				}
			}
		}
	}
	cout<<-1;//没有符合条件的数 
}
```

---

## 作者：KazamaRuri (赞：1)

题意清晰，不再赘述。

## 分析

~~感觉评不到紫。~~

$ d $ 的倍数，自然而然想到取模结果为 $ 0 $。最小的 $ n $，启发我们使用同余最短路。对于 $ s $ 的限制，直接存到状态里，毕竟时空都允许这样做。

如何实现状态间的转移呢，对于一个十进制数，只需要在他末尾添上一个 $ [0,9] $ 以内的数字就能构成一个新数,当然，前导零是不允许的。并且由于状态大小，即数字构造的单调性，可以直接用 bfs 来求最短路。最后时间复杂度为状态个数，也就是 $ O(s \times d) $，可以通过。

这题和 [[ABC077D] Small Multiple](https://www.luogu.com.cn/problem/AT_arc084_b) 的套路一致，都是同余最短路的练习题。

## 代码

没有刻意压行，码量极小。

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
using pii=pair<int,int>;

const int D=505,S=5005;
int d,s,vis[D][S]; pii dis[D][S]; queue<pii>q;
void print(int x,int y){ if(!y) return ;
	print(dis[x][y].first,dis[x][y].second),
	printf("%d",y-dis[x][y].second);
}
bool bfs(){ q.push({0,0}),vis[0][0]=1;;
	while(q.size()&&!vis[0][s]){
		int u=q.front().first,x=q.front().second;
		q.pop(); for(int i=0;i<10;i++){
			int v=(u*10+i)%d,y=x+i;
			if(!y||y>s||vis[v][y]) continue;
			vis[v][y]=1,dis[v][y]={u,x},q.push({v,y});
		}
	} return vis[0][s];
}
int main(){ scanf("%d%d",&d,&s);
	return bfs()?print(0,s),0:0&puts("-1");
}
```

---

## 作者：Hoks (赞：1)

## 前言
比较有意思的搜索题。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
看到 $d\mid n$ 且 $n$ 的各数位之和为 $s$，首先想到数位 dp。

但是由于题目只让我们求符合条件的最小 $n$，所以根本没必要跑数位 dp 了。

考虑记忆化搜索，设计 $dp_{i,j}$ 表示数字为 $i$，个数为之和为 $j$ 的最小数字。

但由于数字可能会非常大，所以考虑把 $i$ 对 $d$ 取模。

转移的时候考虑枚举的数字为 $k$，转移方程式即为 $10\times dp_{i,j}+k\rightarrow dp_{(10\times i+k)\bmod d,j+k}$。

具体实现考虑使用 bfs，这样就可以保证求出来的数字是最小的数字。

但是这样还是会有问题，原因还是答案可能非常之大。

考虑对于每个 $dp_{i,j}$ 记录下他是从哪个状态加了哪个数字转移过来的，最后直接递归输出 $dp_{0,s}=0$ 即可。

如果 $dp_{0,s}=0$ 则无解。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=510,M=5010,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f,lim=20;
int d,s;bool mp[N][M];pair<pair<int,int>,int>a[N][M];queue<pair<int,int>>q;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='0'&&c<='1'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void put(int x,int y)
{
    if(!x&&!y) return;
    put(a[x][y].first.first,a[x][y].first.second);
    print(a[x][y].second);
}
signed main()
{
    d=read(),s=read();mp[0][0]=1;q.push({0,0});
    while(!q.empty())
    {
        auto [x,y]=q.front();q.pop();
        for(int i=0;i<10;i++)
        {
            int dx=(x*10+i)%d,dy=y+i;
            if(dy>s||mp[dx][dy]) continue;
            mp[dx][dy]=1,a[dx][dy]={{x,y},i},q.push({dx,dy});
        }
    }if(!mp[0][s]) put("-1");else put(0,s);
    genshin:;flush();return 0;
}
```

---

## 作者：yanghanyv (赞：1)

### 思路

- 从 0 开始递推，每次在当前数字的末尾加上一位数字。于是用 $\{i,j\}$ 表示余数为 $i$，且各位数字之和为 $j$ 时组成的最小数，则状态 $\{i,j\}$ 可以推出状态 $\{(i+k) \mod d,j+k\}(0 \leq k \leq 9)$。
- 考虑 DP，然而发现找不到一个合适的顺序，能够满足无后效性原则，于是考虑用 BFS 搜索。
- 本来是以为要用记忆化搜索的，但我们却发现，只要 BFS 时，队列中的状态满足从小到大顺序，则扩展出来的新状态也会有序。由于队列中最开始只有 $\{0,0\}$，满足了有序的条件，所以后面也一定有序。（这个结论好像可以用数学归纳法证明，但我太菜了，不会证）
- 也就是说，一个状态第一次被扩展到时，一定是得到了最小数。所以我们只要记录，一个状态第一次被扩展到时，是由哪个状态得来的，也就是它的前驱。输出时可以递归输出。
- 最终状态为 $\{0,s\}$。
- 时间复杂度 $O(ds)$，可以通过本题。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N=5e2+5;
const int M=5e3+5;
int d,s;
pii pre[N][M];//pre[i][j]表示状态{i，j}是由哪个状态扩展来的
queue<pii> que;
void bfs(){
	que.push({0,0});
	while(que.size()){
		int rem=que.front().first,sum=que.front().second;
		que.pop();
		for(int i=0;i<=9;i++){
			int rem1=(rem*10+i)%d,sum1=sum+i;
			if(sum1<=s&&pre[rem1][sum1]==(pii){-1,-1}){//只要第一次扩展
				pre[rem1][sum1]={rem,sum};
				que.push({rem1,sum1});
			}
		}
	}
}
void print(int rem,int sum){//递归输出
	if(rem||sum){
		print(pre[rem][sum].first,pre[rem][sum].second);
		printf("%d",sum-pre[rem][sum].second);
	}
}
int main(){
	scanf("%d%d",&d,&s);
	for(int i=0;i<d;i++){
		for(int j=0;j<=s;j++){
			pre[i][j]={-1,-1};//初始化
		}
	}
	bfs();
	if(pre[0][s]==(pii){-1,-1}){//如果BFS结束后，答案没有被扩展到，则无解
		printf("-1");
	}else{
		print(0,s);
	}
	return 0;
}
```


---

## 作者：傅思维666 (赞：1)

## 题解：

暴力的思路肯定就是枚举$d$的所有倍数。

看到第二个样例之后绝望。然后又发现了-1的情况，所以觉得正解应该是搜索。

然后还要找最小值，所以感觉应该是BFS，然后觉得裸的BFS转不了，所以应该加个记忆化。

嗯，于是正解的思路就拿出来了。BFS+记忆化。

我们设$pre[d][s]$为当前枚举到的各位和为$s$，当前数字对$d$取模结果为$d$的**上一个**$d,s$和位数。这样就可以用递归输出答案。

为什么在状态设置上要加上对$d$取模呢？因为当前数字可能很大，但是其对$d$取模的结果是当前状态下唯一的，所以可以保证正确性。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int d,s,pre[505][5005][3];
bool v[505][5005];
queue<int>qx,qy;
void bfs()
{
    v[0][0]=1;
    qx.push(0);
    qy.push(0);
    while(!qx.empty())
	{
        int x=qx.front();
		qx.pop();
        int y=qy.front();
		qy.pop();
        for(int i=0;i<=9;i++)
		{
            int xx=(10*x+i)%d,yy=y+i;
            if(v[xx][yy]||yy>s)
                continue;
            v[xx][yy]=1;
            pre[xx][yy][0]=x;
            pre[xx][yy][1]=y;
            pre[xx][yy][2]=i;
            qx.push(xx);
            qy.push(yy);
        }
    }
}
void print(int x,int y)
{
    if(!x&&!y)
        return;
    print(pre[x][y][0],pre[x][y][1]);
    printf("%d",pre[x][y][2]);
}
int main()
{
	scanf("%d%d",&d,&s);
    bfs();
    if(v[0][s]==0)
        puts("-1");
    else 
        print(0,s);
    return 0;
}
```



---

## 作者：liuyifan (赞：1)

## BFS模板题
先根据位数进行BFS，如果位数和>s位数和>s就不入队，剩下的每次入队前都%d就好了（控制数字大小别超inti。然后当余数等于0（被d整除了），位数和等于ss时就是答案

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
#define ll long long
#define inf 0x3f3f3f3f//无穷大
using namespace std;
int d,s,pre[505][5005][3];//三维数组(比较慢,如果要卡常尽量用多个二维)
bool vis[505][5005];//判断搜过没有
queue<int>Qx,Qy;//BFS队列
inline void bfs()//BFS
{
    vis[0][0]=1;
    Qx.push(0);
    Qy.push(0);//初始化
    while(!Qx.empty())//开始搜索
    //上述语句含义:Qx不为空
	{
        reg int x=Qx.front();
		Qx.pop();
        reg int y=Qy.front();
		Qy.pop();//弹出搜过了的元素
        for(reg int i=0;i<=9;i++)
		{
            reg int xx=(10*x+i)%d,yy=y+i;
            if(vis[xx][yy]||yy>s)continue;
            vis[xx][yy]=1;
            pre[xx][yy][0]=x;
            pre[xx][yy][1]=y;
            pre[xx][yy][2]=i;//保存搜索结果
            Qx.push(xx),Qy.push(yy);//加入新元素
        }
    }
}
inline void out(reg int x,reg int y)
{
    if(x==0&&y==0)return;
    out(pre[x][y][0],pre[x][y][1]);
    printf("%d",pre[x][y][2]);
}//递归输出结果
int main()
{
	ios::sync_with_stdio(0);//cin,cout加速,NOIP慎用
	cin>>d>>s;
    bfs();
    if(vis[0][s]==0)puts("-1");//无解情况
    else out(0,s);//递归输出
    return 0;//结束
}
```

---

## 作者：Tom_yyt (赞：0)

题意非常清晰，此处不再赘述。
### 思路大致如下：

$f_{a,b}$ 表示 $\mod d \equiv a$ 且数字和为 $b$ 的最小非负整数

#### 用BFS扩展:
对于当前状态 $f_{a,b}$ 枚举下一位添什么数字 $(x=0 \to 9)$

进而到达状态$f_{(a\times 10+x)\!\!\!\mod d~,~(b+x) }$

**但是 $f$ 记录的数可能太大，无法存储，故记录其前驱并递归输出（注意： $f$ 已不复存在！！！）**


```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int d,s;
  bool flag;
  int mp[510][5010];
  pair<int,int> fa[510][5010];//前驱
  bool vis[510][5010];
  void out(int x,int y)//输出
  {
      if(fa[x][y].second==0)
      {
          putchar('0'+mp[x][y]);
          return;
      } 
      out(fa[x][y].first,fa[x][y].second);
      putchar('0'+mp[x][y]);
  }
  void bfs()
  {
      queue<pair<int,int> >q;
      vis[0][0]=1;
      q.push(make_pair(0,0));
      while(!q.empty())
      {
          pair<int,int> x=q.front();
          q.pop();
          if(x.second==s&&x.first==0)//找到了mod d 余0且和为s的数
          {
              flag=1;
              out(x.first,x.second);
              break;
          }
          for(int i=0;i<=9;i++)
          {
              pair<int,int> j=make_pair(((x.first)*10+i)%d,(x.second)+i);
              if(vis[j.first][j.second]) continue;
              if(j.second>s) continue;
              vis[j.first][j.second]=1;
              fa[j.first][j.second]=x;
              mp[j.first][j.second]=i;
              q.push(j);
          }
      }
  }
  signed main()
  {
      cin>>d>>s;
      bfs();
      if(!flag||!vis[0][s]) puts("-1");
      return 0;
  }
```


---

## 作者：lgnotus (赞：0)

### 题目描述

给定两个数$d(1\le d \le 500)$和$s(1\le s\le 5000)$，找出最小数$n$使得$d\mid n$且$n$的各个位数之和为$s$。

### 解题方法

用**bfs**，状态有两个：

- （此状态用$num$表示）当前枚举到的数字对$d$取模（设有一数$a_1a_2...a_n$和一数$b_1b_2...b_n$对$d$取模的余数相同，这时，$a$数加上一位$a_{n+1}$，$b$数增加一位$b_{n+1}$，$a_1a_2...a_na_{n+1}$和$b_1b_2...b_nb_{n+1}$对$d$取模的余数仍相同，那说明$a$数和$b$数要么都能被$d$整除，要么不能，所以这样即可避免枚举的数爆$int$，也可避免重复）
- （此状态用$sum$表示）当前枚举到的数字各个位数相加的和

这样再枚举答案数字的每一位即可，但是，因为状态存储的是当前枚举到的数字对$d$取模，无法直接存储答案，可以定义一个二维$p$数组，$p[i][j]$存储的是一个**三元组**，$p[num][sum].num$表示当前状态（具体表示见上）的上一个状态的$num$，$p[num][sum].sum$表示当前状态的上一个状态的$sum$，$p[num][sum].x$表示**表示当前状态的上一个状态的原数新增的那一位数**，这样输出就可以用递归来实现。

### code

```C++
#include<bits/stdc++.h>
using namespace std;
int d,s;
struct node
{
    int num,sum;
};
struct pre
{
    int num,sum,x;
};
int vis[501][5001];
pre p[501][5001];
queue<node>q;
bool check(int num,int sum)
{
    if(!vis[num][sum]&&sum<=s)return 1;
    return 0;
}
void bfs()
{
    vis[0][0]=1;
    node t;t.num=0;t.sum=0;
    q.push(t);
    while(!q.empty())
    {
        node tmp=q.front();q.pop();
        int num=tmp.num,sum=tmp.sum;
        for(int i=0;i<=9;i++)
        {
            int new_num=(10*num+i)%d,new_sum=sum+i;
            if(check(new_num,new_sum))
            {
                vis[new_num][new_sum]=1;
                node tp;
                tp.num=new_num;tp.sum=new_sum;
                pre temp;
                temp.num=num;temp.sum=sum;temp.x=i;
                p[new_num][new_sum]=temp;
                q.push(tp);
            }
        }
    }
}
void print(int dd,int ss)
{
    if(ss==0)return;
    print(p[dd][ss].num,p[dd][ss].sum);
    cout<<p[dd][ss].x;
}
int main()
{
    cin>>d>>s;
    bfs();
    if(!vis[0][s])cout<<-1<<endl;
    else print(0,s);
    return 0;
}

```





---

## 作者：永不复行 (赞：0)

首先500*5000种状态
可能有人会问如何回溯之前的数字，这里可以参考前向星，

但由于要bfs（如果dfs可能会优先较长的数，就不是最小的了，如 3 6 正确答案 6,dfs出12）
所以很自然的想到了用queue来实现
所以每个状态存的是第一个转移到它的上一位的状态，
如：对3 999 时dp[0][18](99)={现在的数9,之前的余数0,之前的总和9};

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	char num;
	int s,mod;
}di[505][5005],ed;
bool vis[505][5005];
char st[5005];
queue < node > q;
int d,s,cnt;
int main()
{
	scanf("%d%d",&d,&s);
	for(int i=1;i<=9;i++)
	{
		node p;p.s=i;p.num='0'+i;p.mod=i%d;		
		di[i%d][i].num='0'+i;
		di[i%d][i].s=-1;
		vis[i%d][i]=1;
		q.push(p);
	}
	ed.s=-1;
	while(!q.empty())
	{
		node tmp=q.front();
		q.pop();
		if(!tmp.mod&&tmp.s==s)
		{
			ed=tmp;
			break;
		}
		for(int i=0;i<=9;i++)if(!vis[(tmp.mod*10+i)%d][tmp.s+i]&&(tmp.s+i)<=s)
		{
			node p;p.mod=(tmp.mod*10+i)%d;p.s=tmp.s+i;p.num='0'+i;
			vis[p.mod][p.s]=1;
			di[p.mod][p.s]=tmp;
			q.push(p);
		}
	}
	if(ed.s==-1)printf("-1");
	else while(ed.s!=-1)
	{
		st[++cnt]=ed.num;
		ed=di[ed.mod][ed.s];
	}
	for(int i=cnt;i>=1;i--)putchar(st[i]);
}
```

---

