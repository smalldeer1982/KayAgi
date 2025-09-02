# Rooms and Staircases

## 题目描述

有两层房间，每层 $n$ 个，我们用数对 $(a, b)$ 来表示每个房子，其中 $a$ 表示第几层，$b$ 表示从左向右数第几个

对于房子 $(1, i)$ 或 $(2, i)$，都与 $(1, i - 1), (1, i + 1)$ 或 $(2, i - 1), (2, i + 1)$ 相连

而在若干个或个位置中，又有一个双向的梯子，具体来说，若在 $i$ 的位置有一个梯子，则 $(1, i), (2, i)$ 是相连的

求不重复经过同一个房间的情况下，最多能走过多少个房间

## 样例 #1

### 输入

```
4
5
00100
8
00000000
5
11111
3
110
```

### 输出

```
6
8
10
6
```

# 题解

## 作者：sinsop90 (赞：10)

1000*

tag：插头 dp，转化模型能力

这题思维难度很高，代码实现很大。

首先想一下直接 dp 是不太行的，一行的状态数太多，但是考虑到行数很少，而列数很多，不妨将行列反转。

考虑轮廓线 dp。

设 $f_{i,j,s,0/1}$ 表示到 $(i,j)$ 这个格子的轮廓线，状态是一个三位的二进制 $s$，$0/1$ 表示当前的路径线是否联通。

考虑分讨转移 $(i,0),(i,1)$ 位置，具体的：

1. $(i,0)\leftarrow (i-1,1)$

考虑 $(i-1,0)$ 是否有下来的路径线，如果有考虑分三种情况转移，截断，向下，向右（向右需要满足题目条件）。

如果没有，考虑之前如果存在一个联通路径，且存在 $(i-1,1)$ 向下的路径线，则需要考虑增加一个向左拐的路径状态（同理需要满足题目条件）。

2. $(i,1) \leftarrow (i,0)$

考虑 有没有 $(i,0),(i-1,1)$ 来的路径分 $4$ 种情况讨论，是繁琐而简单的，这里就不阐述了，具体可以见代码。

Code：

```cpp
#include<bits/stdc++.h>
#define Inf 1e8
const int N=1010;
using namespace std;
bool vis[N];char S[N];
int f[N][2][8][2];
inline void Max(int &x,int y){x=max(x,y);}
void solve(){
	int n;cin>>n;
	cin>>S;
	for(int i=0;i<N;i++) for(int j=0;j<2;j++) for(int k=0;k<8;k++) for(int p=0;p<2;p++) f[i][j][k][p]=-Inf;
	for(int i=0;i<n;i++) vis[i+1]=S[i]-'0';
//	for(int i=1;i<=n;i++) cout<<vis[i]<<' ';cout<<'\n';
	for(int i=1;i<=n;i++) for(int s=0;s<7;s++){
		if(vis[i]||!(s>>1&1)) f[i][0][s][0]=1; 
	}
	for(int i=1;i<=n;i++) f[i][1][2][0]=f[i][1][0][0]=1;
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int s=0;s<8;s++){
			if(s>>1&1){
				Max(f[i][0][((s>>2)<<2)|0][0],f[i-1][1][s][0]+1);
				Max(f[i][0][((s>>2)<<2)|0][1],f[i-1][1][s][1]+1);
				Max(f[i][0][((s>>2)<<2)|1][0],f[i-1][1][s][0]+1);
				Max(f[i][0][((s>>2)<<2)|1][1],f[i-1][1][s][1]+1);
				if(vis[i]){
					Max(f[i][0][((s>>2)<<2)|2][0],f[i-1][1][s][0]+1);
					Max(f[i][0][((s>>2)<<2)|2][1],f[i-1][1][s][1]+1);
				}
			}else{
				if((s>>2&1)&&vis[i]) Max(f[i][0][((s>>2)<<2)|2][0],f[i-1][1][s][1]+1);
			}
		}
		for(int s=0;s<8;s++){
			if((s>>1&1)&&(s>>2&1)){
				Max(f[i][1][((s&1)<<1)|0][1],f[i][0][s][0]+1);
				Max(f[i][1][((s&1)<<1)|0][1],f[i][0][s][1]+1);
			}
			else if((s>>2&1)){
				Max(f[i][1][((s&1)<<1)|0][0],f[i][0][s][0]+1);
				Max(f[i][1][((s&1)<<1)|0][1],f[i][0][s][1]+1);
				Max(f[i][1][((s&1)<<1)|4][0],f[i][0][s][0]+1);
				Max(f[i][1][((s&1)<<1)|4][1],f[i][0][s][1]+1);
			}
			else if((s>>1&1)){
				Max(f[i][1][((s&1)<<1)|0][1],f[i][0][s][0]+1);
				Max(f[i][1][((s&1)<<1)|0][1],f[i][0][s][1]+1);
				Max(f[i][1][((s&1)<<1)|4][1],f[i][0][s][0]+1);
				Max(f[i][1][((s&1)<<1)|4][1],f[i][0][s][1]+1);
			}else{
				Max(f[i][1][((s&1)<<1)][1],f[i][0][s][1]);
			}
		}
	}
	for(int i=1;i<=n;i++) for(int j=0;j<2;j++) for(int k=0;k<8;k++) ans=max(ans,f[i][j][k][1]);
	cout<<max(n,ans)<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) solve();	
	return 0;
}
```	

---

## 作者：B_Qu1e7 (赞：3)

题目大意：

一栋两层的楼，给定一些有上下相通的楼梯的房间，求不重复能够走过的最大房间数。

~~话说那个全0的数据 建二楼有什么意义啊~~

考虑$2+1$种可能的答案。

## ①一层走过两次。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gh03x4t4.png)

这种情况需要有**至少**两个楼梯位于$i$号和$j$号（和……）房间。分别由$i$号和$j$号房间（和……）换入另一层。

答案为$n+s$（楼梯数$s\geq 2$）。

## ②一层只走一次。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s8guzb7d.png)

当遇到一个楼梯时，$ans=max(ans,max(2*i,2*(n-i+1)))$。

**那么，当楼梯数$s\geq 2$时，一定能找到一个编号为$i$的楼梯使得$max(2*i,2*(n-i+1))>n+s$（省略证明过程，请读者自行理解**~~如有反例请举出~~**）**

综上，我们只需考虑②的答案。写完，提交。
~~等等好像哪里不对~~

**要是没有楼梯呢？**

## ③没有楼梯。

~~这还要考虑啥~~ **答案必定为$n$**

结束。

```

#include<cstdio>
#include<algorithm>
#define R register
using namespace std;
int T,N;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		R int ans=0,p=0;
		scanf("%d",&N);
		for(R int i=1,x;i<=N;++i)
		{
			scanf("%1d",&x);
			p|=x;
			//p：有没有楼梯
			if(x)ans=max(ans,max(i,N-i+1));
			//这里的ans算的是一层最大能走过的房间数量，迂回*2即可
		}
		if(!p)
		{
			printf("%d\n",N);//没有楼梯，输出一层的房间数
		}
		else
		{
			printf("%d\n",ans<<1);//否则输出②的答案
		}
	}
}
```

---

## 作者：littlebug (赞：1)

## Solution

因为只有两层，~~所以不用插头 dp~~，可以直接分讨，首先，两层楼之间的梯子（以下简称梯子）是重点。我们不妨设在最左边的梯子的位置为 $l$，最右边的为 $r$，接下来分讨（设选择的梯子的位置为 $i$）：

- 方案 A：如果从一楼左边经过梯子走到二楼右边，答案为 $n+1$，显然不是很优的。
- 方案 B：如果从一楼左边经过梯子之后返回一楼左边，答案为 $i \times 2$。从一楼右边开始同理，答案为 $(n-i+1) \times 2$。
- 方案 C：如果走两个梯子，从一楼左边开始，经过第二个梯子向右走答案为 $n+2$，向左走没有方案 B 更优，排除。
- 方案 D：继续拓展，如果走多个梯子，且一直向右走，那么答案为 $n$ 加上走的梯子个数。

综上，方案 B 和方案 D 是可行的，对于方案 B，显然 $l$ 和 $r$ 分别是从右开始、从左开始最优的。

记得特判一下没有两层楼之间的梯子就可以了，此时答案为 $n$。

## Code

```cpp
#include<iostream>
#include<cstdio>
//#define int long long
#define il inline
using namespace std;

int n;
string s;

il void solve()
{
    cin>>n>>s; s="$"+s;

    int l=2e9,r=-2e9,cnt=0;
    for(int i=1;i<=n;++i) if(s[i]=='1') l=min(l,i),r=max(r,i),++cnt;

    if(l==2e9)
    {
        cout<<n<<'\n';
        return;
    }

    cout<<max(n+cnt,max(r<<1,(n-l+1)<<1))<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF1244B)

------------
# 思路：
如果不存在 $1$ 的话，答案就是 $n$。

存在一个和多个，可以共同讨论。用 $l$，$r$ 记录 $1$ 出现在最左边和最右边的位置。

最左边的贡献将是当前位置 $i \times 2$。最右边的贡献是 $(n-l+1) \times 2$。

两者相比较，取最大的。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int t,n;
string s;
signed main(){
	cin>>t;
	while(t--){
    	cin>>n>>s;
    	int l=-1,r;
    	for(int i=0;i<n;i++){
      		if(s[i]=='1'){
        		r=i+1;
       			if(l==-1){
				   	l=i+1;
				}
      		}

    	}
    	if(l==-1){
			cout<<n<<endl;
		}else{
			cout<<max(r*2,(n-l+1)*2)<<endl;
		}
  	}
  	return 0;
}
```
完结撒花~

---

## 作者：回青绝影 (赞：1)

## 裸的贪心……

就是，先考虑有没有楼梯……

1.如果没有，那就肯定只能走一层……直接输出n。

2.else，那就是贪心了！！！
	
    考虑可以从任意房间出发，但肯定是从边上走最优
    
    而且有楼梯一定要上
    
    通过思考……肯定是绕一圈最大的最优
    
——于是，就想到了！找到端点的两个楼梯，然后看是左边走最右边的楼梯远，还是右边走最左边的楼梯远，就可以了……

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans1,ans2,n,T;
char s[10001];
int main(){
    scanf("%lld",&T);
    while (T--){
        scanf("%lld",&n);
        cin>>(s+1);
        ans1=0;ans2=0;
        for (int i=n;i>=1;i--)if (s[i]=='1'){ans1=i;break;}
        for (int i=1;i<=n;i++)if (s[i]=='1'){ans2=i;break;}
        // printf("%lld %lld\n",ans1,ans2);
        if (ans1!=0&&ans2!=0){
            printf("%lld\n",max(2*(n-ans2+1),2*ans1));
        }else printf("%lld\n",n);
    }
    return 0;
}
```


还有就是，原来，我还考虑了如果只有一个楼梯的情况
于是——
```
ans=max(n+1,2*ans1);
```
于是就很~~华丽~~（shabi）的错了……

---

## 作者：installb (赞：1)

其实只有两种走法有可能是最大值  

一种是从右上角开始 走到最左边的1 往下走 再走到最右下角的格子  
一种是从左上角开始 走到最右边的1 往下走 再走到最左下角的格子  
这两个之间取最大
![](https://cdn.luogu.com.cn/upload/image_hosting/6j8dvbsn.png)  

在中间上上下下会把一个格子完全堵死(楼上和楼下都访问过 不能再访问) 不如一直走  

假设最左边的1的位置为$l$ 最右边的位置是$r$  
那么$l$左边的楼下 $l$左边的楼上 $r$右边的楼下 $r$右边的楼上  
这四个部分中 无论怎么走 都不可能经过三个及以上的部分  
![](https://cdn.luogu.com.cn/upload/image_hosting/mu5lnnru.png)

上面两种方式都是经过了两个部分  
如果左边取一部分 右边取一部分  
答案一定不会更优

答案就是$max\{r\times 2,(n-l+1)\times 2\}$  
$(n-l+1)+r\leq max\{r\times 2,(n-l+1)\times 2\}$

代码  
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;
typedef long long LL;
 
LL t,n,m,k;
string s;
 
int main(){
	ios::sync_with_stdio(false);
	cin >> t;
	while(t --){
		cin >> n;
		LL lmx = n + 1,rmx = 0;
		cin >> s; s = ' ' + s;
		for(LL i = 1;i <= n;i ++){
			if(s[i] == '1'){
				lmx = min(lmx,i);
				rmx = max(rmx,i);
			}
		}
      // 记录最左边和最右边的1的位置
		if(!rmx){
			cout << n << endl; // 一个1都没有 记得特判
			continue;
		}
		LL ans = max(rmx * 2,(n - lmx + 1) * 2);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：floodfill (赞：0)

# 题解：CF1244B

### 题目大意
  在若干个或个位置中，有一个双向的梯子。具体地，若在 $i$ 的位置有一个梯子，则房间 $(1,i),(2,i)$ 是相连的。

求不重复经过同一个房间的情况下，最多能走过多少个房间？
### 思路
  我们先判断一下输入的 $01$ 串有没有梯子（即代码中的 $j$ 是否 $=0$），若 $j=0$（没有梯子，$01$ 串中全部是 $0$）就直接输出 $n$，反之就输出 $\max\left\{2i,2(n-i+1)\right\}$。当然了，这里  
  $$ans\gets\max\left\{ans,\max\left\{2i,2(n-i+1)\right\}\right\}$$
  是和  
  $$ans\gets\lfloor\frac{\max\left\{ans,\max\left\{i,n-i+1\right\}\right\}}{2}\rfloor$$ 
  等价的。

###  _Code_ 
  ```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
    	  int n,j=0,ans=0;
        cin>>n;
        for(int i=1;i<=n;i++){
        	int c;
        	scanf("%1d",&c);
        	if(c){
        		j=1;//若有梯子,令j=1
        		ans=max(ans,max(2*i,2*(n-i+1)));
			}
		  }
	    if(j){
          cout<<ans<<endl;//有梯子,输出答案
        }else{
		    cout<<n<<endl;//没有梯子,直接输出n
	    }
    }
    return 0;
}
```

---

## 作者：jixiyue114514 (赞：0)

## 题目大意
有一个两层的房子，每层有 $n$ 间屋子，每层的相邻两个屋子可以到达。两层之间有一些屋子有电梯相连。

问从任意屋子开始，不经过重复屋子最多能经过多少屋子。
## 思路
开始的房屋肯定是第 $1$ 间或 $n$ 间（第一层或第二层都行），然后走到最远的电梯，经过的房屋数乘 $2$，取最大即可。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,S,T;
string s;
int main(){
	cin>>t; 
	for(t;t--;) {
		S=-1;
		cin>>n>>s;
		for(size_t i=0;i<s.size();i++)
			if(s[i]=='1'){
				T=i+1;
				if(S==-1){
					S=i+1;
				}
			}
		if(S==-1) {
			printf("%d\n",n);
		}else{
			printf("%d\n",max((n-S+1)*2,T*2));
		} 
	}
	return 0;
}
```
![成功AC](https://cdn.luogu.com.cn/upload/image_hosting/1inpds5v.png)
可以看到成功AC了。

---

## 作者：GoodLuckCat (赞：0)

首先看一个自己造的数据：

```
1
12
011001000100
```

画成图就是这个样子：（`O` 代表房间，`|` 代表梯子）

```
OOOOOOOOOOOO 第二层
 ||  |   |
OOOOOOOOOOOO 第一层
```

经过分析我们可以得到：最短路线只有三种情况。

1. 从第二层的最左边的房间开始走，走到第二层最右边的梯子，下来，再走到第一层最左边的房间。
2. 从第二层的最右边的房间开始走，走到第二层最左边的梯子，下来，再走到第一层最右边的房间。
3. 这种情况很特殊——没有梯子！由于不能重复走，所以只能走 $n$ 个房间（即从某一层的最左边的房间走到最右边的房间）。

第三种情况要特判，然后计算前两种方法哪一个路程长。

在我给的这个数据中，显然第二种方法路程长（因为第一个梯子与左边的距离较小）。注意答案要乘二，因为要在每一层都走一遍，一共走两遍。

代码如下（第一次在题解中的代码写注释）：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,minn=1002,maxn=-1;
        //minn:最左边的1的位置
        //maxn:最右边的1的位置
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            char a;
            cin>>a;
            if(a=='1'&&i<minn)minn=i;
            if(a=='1'&&i>maxn)maxn=i;
            //一定是1才可以
        }
        if(minn==1002&&maxn==-1)cout<<n;
        //初始值没变说明没有梯子,最多走n个格子
        else cout<<2*max(maxn,(n-minn+1));
        //两个方向都走一遍,*2
        cout<<endl;
    }
}
```

---

## 作者：远辰 (赞：0)

# 题意
已经说的很清楚了

# 解法

我是维护了三个东西...vis,fr,to,用来记录最前面的1和最后面的1，然后比较对前面的1与h[1],最后面的1与h[n]的距离，因为最长的一定是走一个类似于回环的东西...

![](https://cdn.luogu.com.cn/upload/image_hosting/tz9ndffx.png)

梯子数大于等于1都可以用这个结论；
注意特判一下是否全为零！！！
# code
```
#include<bits/stdc++.h>
using namespace std;
char h[1005];
int n,t,ans,fr,to;
bool vis;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        vis=0,fr=0,to=0;
        for(int i=1;i<=n;++i)
        {
            cin>>h[i];
            if(h[i]=='1')
            {
                if(vis==0)
                {
                    vis=1;
                    fr=i;
                    to=i;
                }else to=i;
            }
        }
        if(fr==0&&to==0)
        {
            cout<<n;
        }else printf("%d",((fr-1)<=(n-to))?(n-fr+1)*2:(to)*2);
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：xukuan (赞：0)

这次比赛四道可做题（ABDG）之一

我们考虑，有以下几种路径：

- 从左往右，每有一个楼梯就变换楼层
- 从左往右，到最右边的楼梯上楼，走到最左边
- 从右往左，到最左边的楼梯上楼，走到最右边

三种情况分别考虑即可

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=1010,INF=2147483647;
ll n;
char s[N];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		x=-x;
		putchar('-');
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

int main(){
	for(ll T=read(); T; T--){
		n=read();
		scanf("%s",s+1);
		ll ans=0;
		for(ll i=1; i<=n; i++) ans+=s[i]-48;
		ll l=1,r=n;
		for(l=1; l<=n; l++){
			if(s[l]=='1') break;
		}
		for(r=n; r>=1; r--){
			if(s[r]=='1') break;
		}
		if(r==0) r=-INF;
		if(l==n+1) l=INF;
		write(max(ans+n,max(n-l+1,r)*2)); putchar('\n');
	}
	return 0;
}
 
```

---

