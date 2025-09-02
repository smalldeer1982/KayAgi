# Valera and Fools

## 题目描述

One fine morning, $ n $ fools lined up in a row. After that, they numbered each other with numbers from $ 1 $ to $ n $ , inclusive. Each fool got a unique number. The fools decided not to change their numbers before the end of the fun.

Every fool has exactly $ k $ bullets and a pistol. In addition, the fool number $ i $ has probability of $ p_{i} $ (in percent) that he kills the fool he shoots at.

The fools decided to have several rounds of the fun. Each round of the fun looks like this: each currently living fool shoots at another living fool with the smallest number (a fool is not stupid enough to shoot at himself). All shots of the round are perfomed at one time (simultaneously). If there is exactly one living fool, he does not shoot.

Let's define a situation as the set of numbers of all the living fools at the some time. We say that a situation is possible if for some integer number $ j $ ( $ 0<=j<=k $ ) there is a nonzero probability that after $ j $ rounds of the fun this situation will occur.

Valera knows numbers $ p_{1},p_{2},...,p_{n} $ and $ k $ . Help Valera determine the number of distinct possible situations.

## 说明/提示

In the first sample, any situation is possible, except for situation $ {1,2} $ .

In the second sample there is exactly one fool, so he does not make shots.

In the third sample the possible situations are $ {1,2} $ (after zero rounds) and the "empty" situation $ {} $ (after one round).

In the fourth sample, the only possible situation is $ {1,2,3} $ .

## 样例 #1

### 输入

```
3 3
50 50 50
```

### 输出

```
7
```

## 样例 #2

### 输入

```
1 1
100
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2 1
100 100
```

### 输出

```
2
```

## 样例 #4

### 输入

```
3 3
0 0 0
```

### 输出

```
1
```

# 题解

## 作者：Alexxtl (赞：1)

[**更好的阅读体验**](https://www.cnblogs.com/Alexxtl/p/18294941)

## 题目链接

[**Luogu**](https://www.luogu.com.cn/problem/CF369D)

[**Codeforces**](https://codeforces.com/problemset/problem/369/D)

## 题意简述

有 $n$ 个人站成一排，每人手中有 $k$ 发子弹，每次每人会向除自己外编号最小的人开枪，第 $i$ 个人开枪的命中率为 $p_i \%$，剩余最多一人时结束，问有多少种可能的局面。

## 解法说明

从题目要求中可以发现，每次一定是编号最小的人向编号第二小的人开枪，其余人向编号最小的人开枪，也就是说，每次只有编号最小和第二小的两个人受到枪击。

故对于每一轮，我们可以设此时编号最小的和第二小的人分别为 $x,y$，令 $f_{x,y}$ 表示转移到 $x,y$ 所需要的步数（即消耗的子弹数）则会有以下四种情况：

- **两人都未被击中**

未发生变化，忽略。

- **$x$ 被击中，而 $y$ 幸存**

此时如满足 $p_x<100$（否则 $y$ 必然被击中）且 $\exists i \in [y,n], p_i>0$（否则 $x$ 无法被击中），则转移到 $f_{y,y+1}$；

- **$x$ 幸存，而 $y$ 被击中**

此时如满足 $p_x>0$（否则 $y$ 无法被击中）且 $\forall i \in [y,n], p_i \ne 0$（否则 $x$ 必然被击中），则转移到 $f_{x,y+1}$；

- **$x$ 与 $y$ 都被击中**

此时如满足 $p_x>0$（否则 $y$ 无法被击中）且 $\exists i \in [y,n], p_i>0$（否则 $x$ 无法被击中），则转移到 $f_{y+1,y+2}$。

剩余细节详见下面代码中的注释。

## 通过代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define mp make_pair
const int N=3010;

int n,k,p[N],f[N][N],ans;//ans表示可能的局面的数量
bool Genshin[N],Impact[N];//Genshin[i]表示j取[i,n]中任意值时时是否有p[i]>0,Impact[i]表示j取[i,n]中任意值时时是否有p[i]=100
queue<PII> q;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}//快读 

inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
}//快写 

int main(){
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        p[i]=read();
    }
    for(int i=n;i>=1;i--){
        if(Genshin[i+1]||p[i]>0){ 
            Genshin[i]=1;
        }//预处理出Genshin[i]
        if(Impact[i+1]||p[i]==100){
            Impact[i]=1; 
        }//预处理出Impact[i]
    }
    q.push(mp(1,2));
    while(!q.empty()){
        int x=q.front().first,y=q.front().second;
        q.pop();
        if(y>n||f[x][y]>=k){
            continue;
        }//跳过无法转移的情况（剩余人数不大于1或子弹耗尽） 
        if(Genshin[y]&&p[x]!=100){
            if(!f[y][y+1]){
                f[y][y+1]=f[x][y]+1;
                ans++;
                q.push(mp(y,y+1));
            }
        }//x被击中，y幸存 
        if(!Impact[y]&&p[x]>0){
            if(!f[x][y+1]){
                f[x][y+1]=f[x][y]+1;
                ans++;
                q.push(mp(x,y+1));
			}
        }//x幸存，y被击中 
        if(Genshin[y]&&p[x]>0){
            if(!f[y+1][y+2]){
                f[y+1][y+2]=f[x][y]+1;
                ans++;
                q.push(mp(y+1,y+2));
            }
        }//x与y都被击中 
    }
    write(ans+1);//答案要加处在状态(1,2)时的情况 
    return 0;
}
```

---

## 作者：Luzhuoyuan (赞：0)

### 题目链接

[[to Luogu]](https://www.luogu.com.cn/problem/CF369D) [[to Codeforces]](https://codeforces.com/problemset/problem/369/D)

### 题意简述

有 $n$ 个人排成一排，每人手中有一把枪和 $k$ 枚子弹，每次每人会同时向位置编号最小且非自身的人开枪，第 $i$ 个人开枪命中的概率为 $p_i\%$，当只剩下至多一人时结束，问过程中产生局面的种数。

$$1\le n,k\le 3000,0\le p_i\le 100$$

### 做法

本篇搬运[官方题解](https://codeforces.com/blog/entry/9760)。与题面不同，这里的编号从 $1$ 开始。

考虑每次的开枪情况，一定是最左侧的人向第二左的人开枪，其他人向最左侧的人开枪。也就是说第二左的人以及其右边的所有人都一定还活着。那么我们可以将每个状态表示为二元组 $(x,y)$，表示当前最左侧的人是 $x$，第二左的是 $y$。那么 $(x,y)$ 之后的一轮有以下四种情况：

- $x,y$ 都没被击中：此时局面没有发生变化，可以忽略；
- $x$ 被击中，$y$ 没被击中：此时须满足 $p_x<100,\exists i\in [y,n],p_i>0$，可以转移到 $(y,y+1)$；
- $x$ 没被击中，$y$ 被击中：此时须满足 $p_x>0,\forall i\in[y,n],p_i<100$，可以转移到 $(x,y+1)$；
- $x,y$ 都被击中：此时须满足 $p_x>0,\exists i\in [y,n],p_i>0$，可以转移到 $(y+1,y+2)$。

需要满足的条件可以简单预处理。题目要求局面种数，可以从 $(1,2)$（初始状态）开始进行 BFS，能用小于等于 $k$ 步走到的不同状态数即为答案。注意处理人数不大于 $1$ 的情况。复杂度 $O(n^2)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pr pair<int,int>
#define mkp make_pair
#define upd(xx,yy) if(!f[xx][yy])f[xx][yy]=f[x][y]+1,ans++,q.push(mkp(xx,yy))
using namespace std;
const int N=3005;
int n,k,a[N],f[N][N],ans=1;
bool s1[N],s2[N];
//s1[i] 为 i 及以后有没有 p>0
//s2[i] 为 i 及以后有没有 p==100
inline int read(){
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}
queue<pr> q;
inline void bfs(){
    //f 表示该状态之前的操作数加 1，即步数加 1
    f[1][2]=1;q.push(mkp(1,2));
    while(!q.empty()){
        int x=q.front().first,y=q.front().second;q.pop();
        if(y>n||f[x][y]>k)continue;//跳过无法扩展的状态
        if(s1[y]&&a[x]!=100)upd(y,y+1);
        if(!s2[y]&&a[x]>0)upd(x,y+1);
        if(s1[y]&&a[x]>0)upd(y+1,y+2);
    }
}
signed main(){
    n=read(),k=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=n;i>=1;i--)s1[i]=(s1[i+1]||a[i]>0),s2[i]=(s2[i+1]||a[i]==100);
    bfs();printf("%d\n",ans);
    return 0;
}
```

（逃

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
有 $n$ 个傻子，每个傻子有 $k$ 个子弹，傻子会向除自己外自己编号最小的人开枪，第 $i$ 个傻子有 $p_i\%$ 的可能击毙别人，杀到最后一个人为止，问有多少种可能的局面。
## 大体思路
使用一些 DP 思想，既然每一个傻子都打除自己之外编号最小的，那每一轮只会有编号最小的和编号第二小的收到枪击。

我们把这俩人设为 $minn$ 和 $minn+1$，那么我们就有四种转移：

**俩人都没被击中**

不进行转移。

**只有 $minn$ 被击中了**

转移到 $f_{minn+1,minn+2}$。

**只有 $minn+1$ 被击中了**

转移到 $f_{minn,minn+2}$。

**俩人都被击中了**

转移到 $f_{minn+2,minn+3}$。

当然了，我们还要考虑打中的可能性，但是我们在这里只需要特殊讨论 $100\%$ 和 $0\%$ 的情况，一个是必中，一个是必不中，其他的就四个就得讨论。

这样，我们可以从 $f_{1,2}$ 这种初始情况开始 BFS，然后再搜索的同时转移即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[3005];
int f[3005][3005]; 
bool bz[3005],kz[3005];//记录必中和必不中情况 
queue<pair<int,int>> q;
int main(){
	int ans=0;
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];		 
	}
	for(int i=n;i>=1;i--){
		if(kz[i+1]||a[i]>0){//右边的必中/可中情况必须在前面必中/可中时发生的时候才作用在左边
			kz[i]=1;
		}
		if(bz[i+1]||a[i]==100){
			bz[i]=1;
		}
	}
	f[1][2]=1;
	q.push({1,2});
	while(!q.empty()){
		auto x=q.front();
		q.pop();
		if(x.second>n||f[x.first][x.second]>k){
			continue ;
		}
		if(kz[x.second]&&a[x.first]!=100){
			if(!f[x.second][x.second+1]){
				f[x.second][x.second+1]=f[x.first][x.second]+1;
				ans++; 
				q.push({x.second,x.second+1});
			}//后找到的一定不会比先找到的更优 
		}
		if(!bz[x.second]&&a[x.first]>0){
			if(!f[x.first][x.second+1]){
				f[x.first][x.second+1]=f[x.first][x.second]+1;
				ans++; 
				q.push({x.first,x.second+1});
			}
		}
		if(kz[x.second]&&a[x.first]>0){
			if(!f[x.second+1][x.second+2]){
				f[x.second+1][x.second+2]=f[x.first][x.second]+1;
				ans++; 
				q.push({x.second+1,x.second+2});
			}
		}//四种转移 
	}
	cout<<ans+1;
	return 0;
}
```

---

