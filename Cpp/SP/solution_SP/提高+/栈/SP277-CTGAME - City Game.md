# CTGAME - City Game

## 题目描述

Bob is a strategy game programming specialist. In his new city building game the gaming environment is as follows: a city is built up by areas, in which there are streets, trees, factories and buildings. There is still some space in the area that is unoccupied. The strategic task of his game is to win as much rent money from these free spaces. To win rent money you must erect buildings, that can only be rectangular, as long and wide as you can. Bob is trying to find a way to build the biggest possible building in each area. But he comes across some problems - he is not allowed to destroy already existing buildings, trees, factories and streets in the area he is building in.

Each area has its width and length. The area is divided into a grid of equal square units.The rent paid for each unit on which you're building stands is 3$.

Your task is to help Bob solve this problem. The whole city is divided into **K** areas. Each one of the areas is rectangular and has a different grid size with its own length **M** and width **N**. The existing occupied units are marked with the symbol **R**. The unoccupied units are marked with the symbol **F**.

## 样例 #1

### 输入

```
2
5 6
R F F F F F
F F F F F F
R R R F F F
F F F F F F
F F F F F F

5 5
R R R R R
R R R R R
R R R R R
R R R R R
R R R R R```

### 输出

```
45
0```

# 题解

## 作者：Doubeecat (赞：3)

> [SP277 CTGAME - City Game](https://www.luogu.com.cn/problem/SP277)
> 
> 有 $k$ 片土地，每片土地被分成 $n \times m$ 个格子，每个格子里写着 `R` 或者 `F`.
> 
> 对于每片土地，找一块矩形土地，要求这片土地都标着 `F`并且面积最大。
> 
> $n,m \leq 10^3$

## 解题思路

单调栈/悬线法

类似这类有障碍点找最大矩形的题显然可以用悬线法来做，不过这题里是大材小用。

其实这题是[这题](https://www.luogu.com.cn/problem/SP1805)的变式，一时没有思路可以看下上面那题。

考虑怎么构成一个极大矩形，发现一个矩形实际上可以按照行拆分成一条一条的，比如这样。

```
FFF    F F F
FFF => F F F
FFF    F F F
       1 2 3
```

所以这就启发我们，对于每一个格子，可以先将其上边连续的 `F` 数量处理出来，记作 $h_{i,j}$，这里可以采用递推。

若 $a_{i,j}$  $=$ `F`，则 $h_{i,j} = h_{i-1,j} + 1$ 

否则 $h_{i,j} = 0$ 

我们在读入时预处理就能做到。

```cpp
cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        for (int j = 1;j <= m;++j) {
            cin >> g[i][j];
            if (g[i][j] == 'F') h[i][j] = h[i-1][j] + 1;
        }
    }
```

这样，我们就把问题拆分成了每一行上单独的[这题](https://www.luogu.com.cn/problem/SP1805)，我们对于每一行跑一遍单调栈就解决了。

具体地说，我们现在对于一堆矩形，要求出其最大面积。我们建立两个栈，一个用来表示高度，一个用来表示宽度。从左到右扫描每个矩形：
- 若当前矩形比栈顶矩形的高度高，直接进栈。
- 反之，不断取出栈顶直到当前矩形比栈顶矩形的高度大。注意在出栈过程中，这些矩形也是有用的。我们考虑取他们的公共部分，也就是累加他们的宽度之和，并且用每个矩形的高度乘上累计宽度取更新答案。在这个过程结束后，我们就把当前高度与累计宽度的矩形再进栈。

整个过程结束之后，我们要将栈排空，这里我们可以直接添加一个高度为 $0$ 的矩形方便实现，写成代码也就是

```cpp
stack <int> s1,s2;

int work(int x) {
    int ans = 0;
    while (!s1.empty()) s1.pop();//清空两个栈
    while (!s2.empty()) s2.pop();
    s1.push(0);s2.push(0);//保证不访问空栈
    for (int i = 1;i <= m + 1;++i) {
        int now = h[x][i];//当前位置最大的 F 连续高度
        if (now > s1.top()) {s1.push(now),s2.push(1);}//直接进栈的情况
        else {
            int wid = 0;
            while (!s1.empty() && now < s1.top()) {
                wid += s2.top();//累加高度
                ans = max(ans,wid * s1.top();//更新答案
                s1.pop(),s2.pop();
            }
            s1.push(now),s2.push(wid+1);//最后入栈
        }
    }
    return ans;
}
```

对于每一行，我们都执行一个这样的过程

```cpp
int ans = 0;
for (int i = 1;i <= n;++i) ans = max(ans,work(i));    
```

时间复杂度 $O(nm)$

## 代码

```cpp
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
#define ll long long
#define ri register int

char buf[1 << 20], *p1, *p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)?EOF: *p1++)
inline int read() {
	ri v = getchar();int f = 1,t = 0;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {t = t * 10 + v - 48;v = getchar();}
	return t *= f;
}

const int N = 1e3+10;

int n,m,h[N][N];

char g[N][N];

stack <int> s1,s2;

int work(int x) {
    int ans = 0;
    while (!s1.empty()) s1.pop();
    while (!s2.empty()) s2.pop();
    s1.push(0);s2.push(0);
    for (int i = 1;i <= m + 1;++i) {
        int now = h[x][i];
        if (now > s1.top()) {s1.push(now),s2.push(1);}
        else {
            int wid = 0;
            while (!s1.empty() && now < s1.top()) {
                wid += s2.top();
                ans = max(ans,wid * s1.top());
                s1.pop(),s2.pop();
            }
            s1.push(now),s2.push(wid+1);
        }
    }
    return ans;
}

void solve() {
    memset(h,0,sizeof h);
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        for (int j = 1;j <= m;++j) {
            cin >> g[i][j];
            if (g[i][j] == 'F') h[i][j] = h[i-1][j] + 1;
        }
    }
    int ans = 0;
    for (int i = 1;i <= n;++i) ans = max(ans,work(i));
    printf("%d\n",ans * 3);
}

signed main() {
    int T;cin >> T;
    while (T--) solve();
	return 0;
}
```

---

## 作者：Rye_Catcher (赞：3)

- 题目链接：

  https://www.luogu.org/problemnew/show/SP277

- 思路：

  ### 单调栈
  
  如果不知道这是什么可以先做[这道题](https://www.luogu.org/problemnew/show/SP1805)和看看本蒟蒻的博客：
  
  https://www.luogu.org/blog/Rye-Catcher/solution-sp1805
  
  或者到网上搜其他dalao的博客
  
  如果你知道单调栈的思路，那么就不难想了。
  
  刚刚链接里的那道题是在一根数轴上单调栈，那么在这道题中我的思路就是把每纵行看做一个数轴，以向右为正方向，数轴上每个横行对应每个点记录从这开始向右最多有几块空地（就好比是链接中矩形高度），用单调栈思路一根一根数轴的处理，不断更新最大值。
  
  单调栈具体实现跟链接中那道题几乎一样，唯一难题就是怎样预处理向右拓展的最多空地数，好吧其实这也不是最难之处。
  
  我们对于每一横行输入搞一个last记录上一个R的位置，先初始last=0,然后如果接下来在j处读到了一个R，就遍历last+1到j-1的空地，把下标为k（从1开始数第k个）的空地数赋值为j-k(在纸上画一画其实很容易理解),再把last设为j。注意，我们还要在越界处进行一次操作。
  
  如果上面看不懂就看代码吧，如果弄清链接那道题其实代码很好懂。
  
- Tips:

  ### 毒瘤输入  毒瘤输入  毒瘤输入
  搞这输入跟我从想题到打完代码时间一样长。
  
  POJ discuss区中甚至有人反映数据输出可能不严格按照要求（例如：两个字符间有多个空格）建议用cin读入。
  
- 代码：

```
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <algorithm>
#define ri register int 
using namespace std;
int n,m,t,anss=0;
int city[1010][1010];
template <class T>inline void read(T &x){
	x=0;char c;int neg=0;
	while(!isdigit(c=getchar()))neg=c=='-';
	x=c-48;
	while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
	x=neg?-x:x;
}
inline int solve(int r){  //单调栈
	int w[1005],s[1005],p,ans=0;
	city[n+1][r]=p=0;
	for(ri i=1;i<=n+1;i++){
		if(city[i][r]>s[p]){
			s[++p]=city[i][r];
			w[p]=1;
		}
		else {
			int wid=0;
			while(s[p]>city[i][r]){
				wid+=w[p];
				ans=max(ans,wid*s[p]);
				p--;
			}
			if(city[i][r])s[++p]=city[i][r],w[p]=wid+1;
		}
	}
	return ans;
}
int main()
{
	char ch;string sp;
	cin>>t;
	while(t--){
	    anss=0;
		read(n),read(m);
		for(ri i=1;i<=n;i++){
			int last=0;     
			for(ri j=1;j<=m;j++){
			    cin>>sp;ch=sp[0]; //毒瘤输入
			     if(ch=='R'){ 
					for(ri k=last+1;k<j;k++){//预处理
						city[i][k]=j-k;
					}
					last=j;
				}
				else if(j==m){//注意这个操作必不可少
				    for(ri k=last+1;k<=j;k++){
						city[i][k]=j-k+1;
					}
				}
			}
		//	putchar('\n');
		}
		for(ri i=1;i<=m;i++){//注意n,m的区别
			anss=max(anss,solve(i));
		}
		memset(city,0,sizeof(city));
		cout<<anss*3<<endl;
	}
	return 0;
}
```

代码效率较高，不过我很佩服10ms，POJ0ms的大佬们

---

## 作者：ycy1124 (赞：0)

前言：[双倍经验](https://www.luogu.com.cn/problem/UVA1330)，[三倍经验](https://www.luogu.com.cn/problem/P4147)。
### 题意
在一个由 ``F`` 和 ``R`` 构成的矩形中找到一个最大的 ``F`` 矩形并输出其面积乘 $3$。
### 思路
很板子的单调栈求最大矩形面积。只需要先对每个点求一下向上最长能有几个连续的 ``F``，然后拿一个单调栈去求一下最大矩形。我们发现，对于一些底边在一条线上的矩形前面的高矩形是不能和后面的矮矩形组成一个高矩形的，而一个矮矩形可以和后面的高矩形的一部分组成一个矮矩形。于是我们每次将栈顶比自己高的矩形弹出并统计一次答案和宽度，最终答案取一个最大值。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1001][1001];
int h[1001][1001];
struct Node{
	int h,w;
};
stack<Node>q;
int main(){
    int t;
    cin>>t;
    while(t--){
        while(!q.empty()){
            q.pop();
        }
        for(int i=1;i<=1000;i++){
            for(int j=1;j<=1000;j++){
                a[i][j]=' ';h[i][j]=0;
            }
        }
        int n,m;
    	scanf("%d%d",&n,&m);
    	for(int i=1;i<=n;i++){
    		for(int j=1;j<=m;j++){
    			cin>>a[i][j];
    		}
    	}
    	for(int i=1;i<=n;i++){
    		for(int j=1;j<=m;j++){
    			if(h[i][j]==0&&a[i][j]=='F'){
    				int js=0;
    				int x=i;
    				int y=j;
    				while(a[x][y]=='F'){
    					h[x][y]=++js;
    					x--;
    				}
    			}
    		} 
    	}
    	int ans=0;
    	for(int i=1;i<=n;i++){
    		for(int j=1;j<=m;j++){
    			if(q.empty()||h[i][j]>q.top().h){
    				q.push({h[i][j],1});
    			}
    			else{
    				int js=0;
    				while(!q.empty()&&h[i][j]<=q.top().h){
    					ans=max(ans,q.top().h*(js+q.top().w));
    					js+=q.top().w;
    					q.pop();
    				}
    				q.push({h[i][j],1+js});
    			}
    		}
    		int js=0;
    		while(!q.empty()){
    			ans=max(ans,q.top().h*(js+q.top().w));
    			js+=q.top().w;
    			q.pop();
    		}
    	}
    	printf("%d\n",ans*3);   
    }
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/201416394)。

---

## 作者：Harrylzh (赞：0)

预处理出从每个格子可以向上延伸多少个，再枚举矩形的底边，就会发现题目变成了做 $n$ 遍[这个](https://www.luogu.com.cn/problem/SP1805)问题，取最大值。把矩形存在单调栈中，使矩形的高度单调递增，在出栈时更新答案即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool mp[1000+5][1000+5];
long long n,m;
long long a[1000+5][1000+5];
struct node
{
	long long s,w;
};
long long t;
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		memset(a,0,sizeof(a));
		memset(mp,0,sizeof(mp));
		cin>>n>>m;
		for(long long i=1;i<=n;i++)
		{
			for(long long j=1;j<=m;j++)
			{
				char ch;
				cin>>ch;
				if(ch=='F') mp[i][j]=1;
			}
		}
		for(long long i=1;i<=n;i++)
		{
			for(long long j=1;j<=m;j++)
			{
				if(mp[i][j])
				{
					a[i][j]=a[i-1][j]+1;
				}
			}
		}
		long long zans=0;
		for(long long i=1;i<=n;i++)
		{
			stack<node>st;
			while(!st.empty()) st.pop();
			long long ans=0;
			for(long long j=1;j<=m+1;j++)
			{
				if(st.empty()||(a[i][j]>st.top().s))
				{
					st.push({a[i][j],1});
				}
				else
				{
					long long w=0;
					while((!st.empty())&&st.top().s>a[i][j])
					{
						w+=st.top().w;
						ans=max(ans,w*st.top().s);
						st.pop();
					}
					st.push({a[i][j],w+1});
				}
			}
			zans=max(ans,zans);
		}
		printf("%lld\n",zans*3);
	}
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP277)

# 前置知识

[单调栈](https://oi-wiki.org/ds/monotonous-stack/)

# 解法

令 $f_{i,j}(1 \le i \le n,1 \le j \le m)$ 表示从 $(1,j)$ 到 $(i,j)$ 中以 $(i,j)$ 结尾的均为 ``F`` 的子串长度，即 $(i,j)$ 上面可延伸的最大距离（子矩形的长）。

用单调栈的第一维存储子矩形的长，第二维存储子矩形的宽。考虑依次枚举每一行和每一列，进行出入栈的操作。当枚举到 $(i,j)$ 的位置时，记录子矩形的宽 $num$，有如下操作：

  - 对于栈中原来的元素中大于当前的长 $f_{i,j}$，要将其弹出栈，计数器 $num$ 加 $1$。
    - 子矩形的宽为弹出栈的元素个数。
    - 其所形成的子矩形面积为 $num \times $ 栈中当前的元素。
  - 将所得到的长 $f_{i,j}$ 和宽 $num$ 入栈。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1001][1001];
int main()
{
    int n,m,t,v,i,j,ans,num;
    char pd;
    cin>>t;
    for(v=1;v<=t;v++)
    {
        ans=0;
        cin>>n>>m;
        memset(f,0,sizeof(f));
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                cin>>pd;
                if(pd=='F')
                {
                    f[i][j]=f[i-1][j]+1;
                }
            }
        }
        for(i=1;i<=n;i++)
        {
            stack<pair<int,int>> s;
            s.push(make_pair(f[i][1],1));
            for(j=2;j<=m;j++)
            {
                num=0;
                while(s.empty()==0&&s.top().first>=f[i][j])
                {
                    num+=s.top().second;
                    ans=max(ans,num*s.top().first);
                    s.pop();
                }
                s.push(make_pair(f[i][j],num+1));
            }
            num=0;
            while(s.empty()==0)
            {
                num+=s.top().second;
                ans=max(ans,num*s.top().first);
                s.pop();
            }
        }
        cout<<ans*3<<endl;
    }
    return 0;
}
```

# 后记

多倍经验：P4147 | P5943 | UVA1330

---

## 作者：Unnamed114514 (赞：0)

### 前置知识
[单调栈](https://oi-wiki.org/ds/monotonous-stack/)，是一种线性的数据结构，通常用栈或数组模拟实现。顾名思义，就是保持单调性的栈，通常使用的是单调递增以及单调递减的单调栈，递增和递减都是指从栈底到栈顶的顺序，它的模板有如下：视野总和、求最大区间、直方图中最大的矩形等。因为每个元素入队一次，出队一次，所以总的复杂度为 $O(n)$。所以本题单调栈是可行的，复杂度为 $O(nm)$，还有[双倍经验](https://www.luogu.com.cn/problem/UVA1330)。
***
首先，存储前缀和为 $sum_{i,j}$ 表示到达第 $(i,j)$ 个位置的连续的 `F` 的个数，然后我们构建一个单调递增栈，以 `sum` 升序排列，求出最左边可以影响的点 $l_i$，以及最右边可以影响的点 $r_i$。从贪心的角度，我们肯定要去到我们可以取到的最左和最右。由此，该矩阵长为 $r_i-l_i+1$，宽为 $sum_{i,j}$。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,sum[1005][1005],ans,l[1005],r[1005],t;
stack<int> stk;
signed main(){
	scanf("%lld",&t);
	for(int i=1;i<=t;i++){//多组测试数据
		scanf("%lld%lld",&n,&m);
		ans=-2e9;//初始化为极小值
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				l[j]=r[j]=0;
				char s;
				cin>>s;
				if(s=='F')
					sum[i][j]=sum[i-1][j]+1;//前缀和
				else
					sum[i][j]=0;			
			}
			stk.push(1);
			for(int j=2;j<=m;j++){
				int x=stk.top();
				while(sum[i][x]>sum[i][j]&&!stk.empty()){
					stk.pop();
					r[x]=j-1;
					if(stk.empty())
						break;
					x=stk.top();
				}
				stk.push(j);
			}
			while(!stk.empty()){
				int x=stk.top();
				stk.pop();
				r[x]=m;
			}
			stk.push(m);
			for(int j=m-1;j>=1;j--){
				int x=stk.top();
				while(sum[i][x]>sum[i][j]&&!stk.empty()){
					stk.pop();
					l[x]=j+1;
					if(stk.empty())
						break;
					x=stk.top();
				}
				stk.push(j);
			}	
			while(!stk.empty()){
				int x=stk.top();
				stk.pop();
				l[x]=1;
			}//单调栈的模板
			for(int j=1;j<=m;j++)
				ans=max(ans,(r[j]-l[j]+1)*sum[i][j]);//求最大
		}
		printf("%lld\n",ans*3);//注意乘3
	}
	return 0;
}
```

---

## 作者：William_Fangs (赞：0)

介绍一种解决这种最大子矩阵的方法

--> 悬线法
--  

我们开三个数组$up[i][j],le[i][j],ri[i][j]$表示下端在第$i$行,从第$j$的矩形发出悬线的矩形的信息,它们分别表示

- $up[i][j]$ 此点向上拓展的最大高度
- $le[i][j]$ 以$up[i][j]$为高的悬线向左最多拓展到多少列
- $ri[i][j]$ 以$up[i][j]$为高的悬线向右最多拓展到多少列  

如何维护$up$呢? 如果第$i-1$行不为障碍物,加一就好了,否则设为一  

那$le$呢 ? 不妨设$lo$为当前当前这一行第$j$列左边的第一个障碍,则$le[i][j]=max(le[i-1][j],lo+1);$  

同理,设设$ro$为当前当前这一行第$j$列右边的第一个障碍,则$ri[i][j]=min(ri[i-1][j],ro-1);$  

最后求出最大的$up[i][j]*(ri[i][j]-le[i][j]+1)$即可

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int N=1086;
int s[N][N];
int up[N][N];
int le[N][N];
int ri[N][N];
int lo,ro;
char c;
int n,m;
int T;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(s,0,sizeof(s));
		scanf("%d%d",&n,&m);
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=m; j++)
			{
				c=getchar();
				while(c!='F'&&c!='R')
					c=getchar();
				s[i][j]=c=='F'?1:0;
			}
		}
		int ans=0;
		for(int j=1;j<=m;j++)
			ri[0][j]=99999;
		for(int i=1; i<=n; i++)
		{
			lo=0;
			ro=m+1;
			for(int j=1; j<=m; j++)
			{
				if(!s[i][j])
				{
					up[i][j]=le[i][j]=0;
					lo=j;
				}
				else
				{
					up[i][j]=up[i-1][j]+1;
					le[i][j]=max(le[i-1][j],lo+1);
				}
			}
//			if(T==1)
//			{
//				T++;
//				T--;
//			}
			for(int j=m; j>=1; j--)
			{
				if(!s[i][j])
				{
					ri[i][j]=n+1;
					ro=j;
				}
				else
				{
					ri[i][j]=min(ri[i-1][j],ro-1);
					ans=max(ans,up[i][j]*(ri[i][j]-le[i][j]+1));
				}
			}
		}
		printf("%d\n",ans*3);
//		if(T==1)
//		{
//			T++;
//			T--;
//		}
	}
	return 0;
}
```

---

