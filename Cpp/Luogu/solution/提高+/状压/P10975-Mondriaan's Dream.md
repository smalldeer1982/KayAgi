# Mondriaan's Dream

## 题目描述

荷兰著名画家皮特·蒙德里安对正方形和矩形非常着迷。有一天晚上，在创作完他的“厕所系列”画作后（他不得不用厕纸画画，因为他所有的画纸都用完了），他梦见用宽度为 $2$、高度为 $1$ 的小矩形以不同的方式填充一个大矩形。

![](https://cdn.luogu.com.cn/upload/image_hosting/5b9lwj6n.png)

作为这方面的专家，他一眼就看出需要使用计算机来计算填充这个大矩形的不同方式。请帮助他，以免他的梦想变成噩梦！

## 样例 #1

### 输入

```
1 2
1 3
1 4
2 2
2 3
2 4
2 11
4 11
0 0```

### 输出

```
1
0
1
2
3
5
144
51205```

# 题解

## 作者：Little_Cart (赞：22)

### 题意

用大小为 $1 \times 2$ 和 $2 \times 1$ 的小矩形填充一个 $h \times w$ 的大矩形，求方案数。

### 思路

一眼状压 dp，注意到可以维护 $dp_{i,S}$ 表示目前枚举到第 $i$ 行，且第 $i$ 行的填充状态为 $S$，预处理判断合法状态以及合法转移即可，时间复杂度 $O(h \times 4^w)$。

这个时候就有人问了，主播主播，状压 dp 确实很强，但状态转移还是太吃操作了，有没有更加简单又强势的算法推荐一下吗？有的兄弟，有的。

这个时候我们引出轮廓线 dp，也就是所谓的插头 dp。

说一下轮廓线 dp 的一些定义。

![](https://cdn.luogu.com.cn/upload/image_hosting/2exisaqs.png)

我们假定绿色格子为已决策格子。

轮廓线：已决策格子和没决策格子的分界线，也就是图中黑线。

![](https://cdn.luogu.com.cn/upload/image_hosting/026mo0ti.png)

插头：一个格子某个方向的插头存在表示这个格子在这个方向与相邻格子相连，因此，一个格子有四个插头，分别在上下左右。

轮廓线上方与其相连的有 $n+1$ 个插头，包括 $n$ 个下插头和 $1$ 个右插头，也就是图中灰色部分。

由于这道题不需要考虑连通性，所以也不需要学到最小表示法，每个插头只需要用 0 或 1 表示，所以维护轮廓线上方的插头状态二进制压缩存储即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/fj3ilme3.png)

举一个这道题的例子，其中灰色插头为 0，表示不需要与之前的状态产生联系，红色插头为 1，表示需要和之前的状态拼成一个 $1 \times 2$ 矩形。

枚举到当前状态时，因为左侧有一个 1 的插头，所以只有一种转移，也就是把表示当前的方格与左侧组成 $1 \times 2$ 矩形，此时的状态需要把左侧的 1 插头变为 0 插头。

对于这道题而言，一共有四种情况。

1. 左侧为 1，上方为 1。

这种状态不符合条件，不产生贡献。

2. 左侧为 1，上方为 0。

把左侧的 1 插头变为 0 插头。

3. 左侧为 0，上方为 1。

把上方的 1 插头变为 0 插头。

4. 左侧为 0，上方为 0。

这个时候有两种情况，第一种是向下转移，将下方 0 插头变为 1 插头，第一种是向右转移，将右侧 0 插头变为 1 插头。

最后统计贡献即可，时间复杂度 $O(hw \times 2^w)$。

### 转移细节

![](https://cdn.luogu.com.cn/upload/image_hosting/aezaw2wi.png)

在枚举到行末之后，要进行下一行的枚举，所以要将状态左移一位。（注意最右侧插头若为 1 则删除该状态）

![](https://cdn.luogu.com.cn/upload/image_hosting/yzoaqbqg.png)

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define fi first
#define se second
#define mkp make_pair
const int N=10024,M=16;
int t,n,m,cur;
int a[M][M],f[2][N];
int get(int stt,int k){
    return (stt>>k)&1;
}
int calc(int k,int v){
    return v*(1<<k);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(cin>>n>>m){
		if(n==0&&m==0){
			break;
		}
		cur=0;
		memset(f,0,sizeof(f));
		f[0][0]=1;
		for(int i=1;i<=n;i++){
			cur^=1;
			memset(f[cur],0,sizeof(f[cur]));
			for(int j=0;j<(1<<m);j++){
				f[cur][j<<1]=f[cur^1][j];
			}
			for(int j=1;j<=m;j++){
				cur^=1;
				memset(f[cur],0,sizeof(f[cur]));
				for(int st=0;st<(1<<(m+1));st++){
					if(!f[cur^1][st]) continue;
					int x=get(st,j-1),y=get(st,j);
					if(x && y){
						continue;
					}
					else if(x){
						f[cur][st-calc(j-1,1)]+=f[cur^1][st];
					}
					else if(y){
						f[cur][st-calc(j,1)]+=f[cur^1][st];
					}
					else{
						f[cur][st+calc(j-1,1)]+=f[cur^1][st];
						f[cur][st+calc(j,1)]+=f[cur^1][st];
					}
				}
			}
		} 
		cout<<f[cur][0]<<"\n";
	}
	return 0;
}
```

---

## 作者：Brilliant11001 (赞：20)

### [更好的阅读体验](https://www.cnblogs.com/Brilliant11001/p/18386601)

## [题目传送门](https://www.luogu.com.cn/problem/P10975)

#### 题目大意

给定一个 $N\times M$ 的网格，求用 $1\times 2$ 和 $2\times 1$ 的长方形去铺满它有多少种方案。

数据范围：$N,M\le 11$。

#### 思路：

考虑怎么放才能刚好填满网格。

可以想到，如果先放横着的，再放竖着的，那么当我们将横着的都放完后，若竖着的恰好能刚好嵌进去，说明这是一个合法方案。

也就是说，放完横着的矩形后放竖着的矩形的方法的唯一确定的，那么：

>**求总的方案数其实就是求横着放且合法（使竖着的能嵌进去刚好铺满网格）的方案数。**

因为放横着的矩形时拓展的方向是横向的，就是说我们放矩形时，当前放的这个矩形只影响到下一列，这启示我们**将“列号”作为 dp 的阶段**，同时由于上一列的放置情况会影响到当前这一列，所以我们需要将**上一列伸出来的部分**作为状态中的一维才能转移。

那么如何表示上一列那些地方伸出来了呢？

如果用 bool 数组来表示第 $i$ 行有没有伸出来，不仅效率低下，而且不方便计算，这时候状态压缩就来了：采用二进制压缩，相当于将原来的 bool 数组变成一个二进制数 $state$，$state$ 的第 $i$ 位表示第 $i$ 是否伸出，$0$ 表示未伸出，$1$ 表示伸出。

设 $f(i, state)$ 表示已经摆完了前 $i - 1$ 列，且从第 $i - 1$ 列伸到第 $i$ 列的方案数，那么状态转移方程为：

$$f(i, state) = \sum f(i - 1, last\_state)$$

其中 $last\_state$ 是第 $i - 2$ 列伸到第 $i - 1$ 的状态，且需要满足 $last\_state$ 对于 $state$ 合法。

$last\_state$ 对于 $state$ 合法当且仅当以下两个条件满足：

1. $state \wedge last\_state = 0$，即第 $i - 2$ 列伸到第 $i - 1$ 的小方格和 $i - 1$ 列放置的小方格不重复；
2. 每一列，所有**连续着空着的小方格必须是偶数个**，因为竖着的矩形必须要能嵌入。

**初始化：** $f(0,0) = 1$。

按定义这里是：前第 $-1$ 列都摆好，且从第 $-1$ 列到第 $0$ 列伸出来的状态为 $0$ 的方案数。  
首先，这里没有 $-1$ 列，最少也是 $0$ 列。  
其次，没有伸出来，即没有横着摆的。即这里第 $0$ 列只有竖着摆这 $1$ 种状态。

**目标：** $f(m,0)$。

$f(m, 0)$ 表示前 $m - 1$ 列都处理完，并且第 $m - 1$ 列没有伸出来的所有方案数。  
即整个棋盘处理完的方案数。

再用集合划分的思想来解释一下。

首先要 **“化零为整”**，即用一个集合表示一类情况，对于这道题，假设我们放矩形时是对于每列都从上往下放，那么可以**根据当前放到了第几列来划分集合**。

但这样划分我们无法找到各个集合之间的转移关系，所以还要再划分一次。

**集合划分的依据就是寻找集合中元素的不同点**，发现在摆完前 $i - 1$ 列的方案中向第 $i$ 列伸出的情况不同，所以可以以此来划分。

所以状态表示为：$f(i, state)$ 表示已经摆完了前 $i - 1$ 列，且从第 $i - 1$ 列伸到第 $i$ 列的方案数。

接着就是 **“化整为零”** 的过程，即状态计算，同上。

$\texttt{Code:}$

```cpp
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 12, M = 1 << N;
typedef long long ll;
int n, m;
vector<int> tran[M];
ll dp[N][M];
bool st[M];

bool check(int x) { //判断该状态是否满足所有连续着空着的小方格必须是偶数个
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(x >> i & 1) {
            if(cnt & 1) return false;
            cnt = 0;
        }
        else ++cnt;
    }
    if(cnt & 1) return false;
    return true;
}

int main() {
    while(scanf("%d%d", &n, &m), n || m) {
        for(int i = 0; i < 1 << n; i++) st[i] = check(i); //提前预处理那哪些状态是合法的
        
        for(int i = 0; i < 1 << n; i++) {
            tran[i].clear();  //多测清空
            for(int j = 0; j < 1 << n; j++)
                if(!(i & j) && st[i | j])
                    tran[i].push_back(j); //提前预处理出每个可行状态能由那些状态转移过来
        }
        
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        for(int i = 1; i <= m; i++)
            for(int j = 0; j < 1 << n; j++)
                for(int k = 0; k < tran[j].size(); k++)
                    dp[i][j] += dp[i - 1][tran[j][k]];
        printf("%lld\n", dp[m][0]);
    }
    return 0;
}
```

---

## 作者：ycy1124 (赞：12)

### 题意
有一个 $h \times w$ 的矩形，要把它用 $1 \times 2$ 或 $2 \times 1$ 的小长方形填满，求方案数。
### 想法
看到 $h$ 和 $w$ 的范围都小于等于 $11$，便可以打表。
### 做法
打了个比较慢的状态压缩的 dp，设 $dp_{i,j}$,$i$ 表示当前填的行数，$j$ 用二进制表示该行的**状态**，$1 \times 2$ 的矩阵都填 $1$，$2 \times 1$ 的下半部分填 $1$。我们可以定义一个函数 ```check(a,b)``` 表示上一行状态为 $b$ 的情况下，这一行的状态有没有可能为 $a$,那么转移方程就是
$$
\Large dp_{i,j} = \sum_{k = 0}^{2^w-1} dp_{i-1,j} \times check(j,k)
$$

至于 ```check``` 函数的实现就是暴力判断每一个二进制位，假如前一行和这一行的当前位都为 $1$，那么这一行的当前位置填的是一个 $1 \times 2$ 的矩形；假如前一行的当前位为 $1$，这一行的当前位是 $0$，那么这里填的是 $2 \times 1$ 的矩形，并且这里是矩形的上半部分；假如前一行的当前位是 $0$，这一行的这个位置为 $1$，那么这个位置就是 $2 \times 1$ 的矩阵的下半部分；假如前一行和这一行的当前位都是 $0$，那么前一行的当前位必然填不到了，就可以直接 ```return 0;```。最后对于每一段填 $1 \times 2$ 矩阵的地方判断是否是一段偶数长的区间。

### 打表代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[12][1<<11];
int n,m;
bool check(int a,int b){
	bool bj=0;//判断是否为偶数长度。
	for(int j=m;j>=1;j--){//枚举二进制位
		if(a>=(1<<(j-1))&&b>=(1<<(j-1))){//假如上一行和这一行的当前位都填了
			bj=!bj;//奇偶性取反
			a-=(1<<(j-1));
			b-=(1<<(j-1));
		}
		else if(a>=(1<<(j-1))){//这一行当前位填了，上一行没填。
			if(bj){//判断上一段是否为偶数长度
				return 0;
			}
			a-=(1<<(j-1));
			bj=0;
		}
		else if(b>=(1<<(j-1))){//上一行当前位填了，这一行没填
			if(bj){
				return 0;
			}
			b-=(1<<(j-1));
			bj=0;
		}
		else{//上一行填不完了，直接返回0
			return 0;
		}
	}
	if(bj){
		return 0;
	}
	return 1;
}
signed main(){
	for(n=1;n<=11;n++)
	for(m=1;m<=11;m++){
		for(int i=0;i<(1<<m);i++){//第一行单独判断。
			if(check(i,(1<<m)-1)){
				dp[1][i]=1;
			}
		}
		for(int i=2;i<=n;i++){
			for(int j=0;j<(1<<m);j++){
				for(int k=0;k<(1<<m);k++){
					dp[i][k]+=dp[i-1][j]*check(k,j);//转移
				}
			}
		}
		printf("db[%d][%d]=%lld;\n",n,m,dp[n][(1<<m)-1]);//输出答案
		for(int i=1;i<=n;i++){
			for(int j=0;j<(1<<m);j++){
				dp[i][j]=0;
			}
		}
	}
	return 0;
}
```
### 最终程序
```cpp
#include<bits/stdc++.h>
using namespace std;
long long db[12][12];
int main(){
	db[1][1]=0;
	db[1][2]=1;
	db[1][3]=0;
	db[1][4]=1;
	db[1][5]=0;
	db[1][6]=1;
	db[1][7]=0;
	db[1][8]=1;
	db[1][9]=0;
	db[1][10]=1;
	db[1][11]=0;
	db[2][1]=1;
	db[2][2]=2;
	db[2][3]=3;
	db[2][4]=5;
	db[2][5]=8;
	db[2][6]=13;
	db[2][7]=21;
	db[2][8]=34;
	db[2][9]=55;
	db[2][10]=89;
	db[2][11]=144;
	db[3][1]=0;
	db[3][2]=3;
	db[3][3]=0;
	db[3][4]=11;
	db[3][5]=0;
	db[3][6]=41;
	db[3][7]=0;
	db[3][8]=153;
	db[3][9]=0;
	db[3][10]=571;
	db[3][11]=0;
	db[4][1]=1;
	db[4][2]=5;
	db[4][3]=11;
	db[4][4]=36;
	db[4][5]=95;
	db[4][6]=281;
	db[4][7]=781;
	db[4][8]=2245;
	db[4][9]=6336;
	db[4][10]=18061;
	db[4][11]=51205;
	db[5][1]=0;
	db[5][2]=8;
	db[5][3]=0;
	db[5][4]=95;
	db[5][5]=0;
	db[5][6]=1183;
	db[5][7]=0;
	db[5][8]=14824;
	db[5][9]=0;
	db[5][10]=185921;
	db[5][11]=0;
	db[6][1]=1;
	db[6][2]=13;
	db[6][3]=41;
	db[6][4]=281;
	db[6][5]=1183;
	db[6][6]=6728;
	db[6][7]=31529;
	db[6][8]=167089;
	db[6][9]=817991;
	db[6][10]=4213133;
	db[6][11]=21001799;
	db[7][1]=0;
	db[7][2]=21;
	db[7][3]=0;
	db[7][4]=781;
	db[7][5]=0;
	db[7][6]=31529;
	db[7][7]=0;
	db[7][8]=1292697;
	db[7][9]=0;
	db[7][10]=53175517;
	db[7][11]=0;
	db[8][1]=1;
	db[8][2]=34;
	db[8][3]=153;
	db[8][4]=2245;
	db[8][5]=14824;
	db[8][6]=167089;
	db[8][7]=1292697;
	db[8][8]=12988816;
	db[8][9]=108435745;
	db[8][10]=1031151241;
	db[8][11]=8940739824;
	db[9][1]=0;
	db[9][2]=55;
	db[9][3]=0;
	db[9][4]=6336;
	db[9][5]=0;
	db[9][6]=817991;
	db[9][7]=0;
	db[9][8]=108435745;
	db[9][9]=0;
	db[9][10]=14479521761;
	db[9][11]=0;
	db[10][1]=1;
	db[10][2]=89;
	db[10][3]=571;
	db[10][4]=18061;
	db[10][5]=185921;
	db[10][6]=4213133;
	db[10][7]=53175517;
	db[10][8]=1031151241;
	db[10][9]=14479521761;
	db[10][10]=258584046368;
	db[10][11]=3852472573499;
	db[11][1]=0;
	db[11][2]=144;
	db[11][3]=0;
	db[11][4]=51205;
	db[11][5]=0;
	db[11][6]=21001799;
	db[11][7]=0;
	db[11][8]=8940739824;
	db[11][9]=0;
	db[11][10]=3852472573499;
	db[11][11]=0;
	int n,m;
	while(scanf("%d%d",&n,&m)&&n+m){
		printf("%lld\n",db[n][m]);
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/178429690)。

---

## 作者：longlinyu7 (赞：6)

# 题目分析
用 $1 \times 2$ 的小矩形填充一个大矩形，可以横着放或者竖着放，问方案数。

# 解题思路
可以观察到数据范围很小 $N,M \le 11$，可以考虑阶乘级算法或者指数级算法，那么考虑到要求记录方案数，尝试使用状态压缩。

### 设计状态

根据状态压缩的套路，把每一行当做一个“状态”。

再考虑每一行中每一列的方格归属情况：

1. 可能与上一行的方格属于一个竖着放的小矩形，将这个状态设为 $1$。
2. 剩下的所有情况都把状态设为 $0$，比如连续两个位置安排一个横着的 $1  \times 2$ 矩形，或者与下一行的方格属于一个竖着的矩形。

为什么这样安排呢？

因为我们是从上到下遍历，枚举到第 $i$ 行的时候，需要考虑上一行对当前行的影响，第一种情况的时候，第 $i-1$ 行对第 $i$ 行的状态产生了影响。第二种情况的时候并没有产生影响。

综上所述，设 $f_{i,s}$ 表示前 $i$ 行，第 $i$ 行的状态为 $s$ 时的方案数。

$s$ 是一个长为 $M$ 的二进制数，在二进制下，第 $k$ 位的为 $0$ 或 $1$ 的情况如上所述。

### 状态转移

$$f_{i,j}= f_{i,j}+f_{i-1,k}$$

转移条件。
- 状态 $j$ 和状态 $k$ 执行**按位与**运算得到的结果是 $0$。

这样就保证了每个数字 $1$ 的下方必须是 $0$，代表着补全竖着的 $1 \times 2$ 的矩形。

- 状态 $j$ 和状态 $k$ 执行**按位或**运算的二进制表示中，每一段连续的 $0$ 必须都是偶数个。

偶数个 $0$ 代表着横着的 $1  \times 2$ 的矩形。奇数个的话就无法满足了。

这两个条件保证了状态转移的合法性，对于条件一，直接计算就好了，对于条件二，可以提前预处理每一个状态是否合法，具体细节见代码。

### 边界处理与输出答案

初始状态，$f_{0,0}=1$。

很明显，答案是 $f_{n,0}$，因为第 $n$ 行的时候，已经到了最后，不能再有 $1$  状态了。

# AC CODE

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD = 1e9;
const int N=13;
ll f[N][1<<N];  //! 不开 long long 见祖宗！！！！！
int n,m;
int vis[1<<N]; // 预处理状态是否合法

signed main(){
    while(cin>>n>>m){
        if(n==0&&m==0)return 0;
       
        memset(f,0,sizeof(f)); // 多测清空
        f[0][0]=1; // 初始状态
        // 预处理
        for(int i=0;i<(1<<m);i++){
            //cnt 记录每一段的奇偶性
            // has_odd 记录是否有一段是有奇数个0的
            bool cnt=0,has_odd=0;
            // 一个合法状态中， 连续的0 必须有偶数个 
            for(int j=0;j<m;j++){
                // (i>>j)&1 是判断状态i的第j位是否为1，为1就开始新的一段 
                if((i>>j)&1)has_odd|=cnt,cnt=0;// cnt 重置
                else cnt^=1; // cnt 记录每一段的奇偶
            }
            //! 这个必须是 has_odd | cht
            //! cnt 算的是最后一段的，没有记录在has_odd 里面
            vis[i]= has_odd|cnt ? 0 :1;
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j <(1<<m);j++){
                for(int k=0;k<(1<<m);k++){
                    //转移的两个条件
                    if((j&k)==0 && vis[j|k]) f[i][j]+=f[i-1][k];
                }
            }
        }
        cout<<f[n][0]<<"\n";// 输出
    }
    return 0;
}
```

## 后记

文章整体借鉴了小蓝书《算法竞赛进阶指南》有一部分摘抄自其中。

希望可以帮助到一些初学状压的同学。

---

## 作者：cff_0102 (赞：5)

状态压缩的典型例题了。

设 $dp_{h,w,S}$ 为在填充高度为 $h$ 的矩形且剩余宽度为 $w$，最后一列被填充的状态为 $S$（用 $h$ 位二进制数表示）时，填多米诺的方案。

用记忆化搜索，代码更容易理解。

dfs 的时候枚举最后一列没被填的空的子集，选择这几个空放一个横着的多米诺，然后判断剩下的状态能不能全部填竖着的多米诺。如果可以就继续搜索左边一列，状态就是这一列被横着填的格子（显然）。

所以 $dp$ 的那个 $h$ 实际上是不会改变的，只不过对每个 $h$ 存一下的话，以后碰到一样 $h$ 的询问就可以直接把答案拿出来了。

记得开 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[15][15][5000];
bool check(int h,int S){//这个状态，要全部在空位里面填竖着的多米诺，是否合法 
	bool a[h+2];
	for(int i=1;i<=h;i++){
		a[i]=(S&(1<<(i-1)));
	}//把 S 拆开来
	a[h+1]=1;
	for(int i=1;i<=h;i++){
		if(!a[i]){
			if(a[i+1]){
				//出现单个空位，不合法
				return 0; 
			}else{
				//填上两个空位
				a[i]=a[i+1]=1; 
			}
		}
	}
	return 1;
}
int dfs(int h,int w,int S){//高度，剩余宽度，最右侧一列状态 
	if(dp[h][w][S]!=-1)return dp[h][w][S];//搜索过这个状态了
	if(w==1)return dp[h][w][S]=check(h,S);//只剩一列，就不能横着填啦，直接 check 一下走人
	//枚举这一列所有填的方案
	//先填横的，填完后看竖着的能不能填进来，如果不能则状态不合法
	int ans=0;
	for(int i=0;i<(1<<h);i++)if(!(i&S)){
		if(check(h,(S|i))){
			ans+=dfs(h,w-1,i);//左边被占用的其实就是这一列横着填的 
		}
	}
	return dp[h][w][S]=ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int h,w;
	memset(dp,-1,sizeof(dp));
	while(cin>>h>>w&&h+w){
		cout<<dfs(h,w,0)<<endl;
	}
	return 0;
}
```

---

## 作者：i_wzy (赞：5)

### 题目链接：[Mondriaan's Dream](https://www.luogu.com.cn/problem/P10975)
### 题目大意：
在 $h \times w（1 \le h,w \le 11）$ 的网格中放满 $1 \times 2$ 的木条，问有几种放置方案。
### 题目思路：
这道题一看就是一道**状压 DP**，不知道的戳这：**[状压 DP](https://blog.csdn.net/u013377068/article/details/81054112)**

#### 首先确定状态：

假设是从左上角开始依次从左至右从上至下的放方块，那么可以得出结论：假设现在要放的点为 $(i,j)$，大小按照字典序（先按行，后按列）。那么对于所有的点 $(i',j') \ge (i,j)$ 一定是还没有放；对于所有 $(i', j') < (i-1,j)$ 的点一定是已经放了方块的。

然后放置一个位置 $(i, j)$ 的时候有三种方式，分别是**不放**，**向上竖着放**，**向左横着放**；如果是**不放**，那么 $(i-1, j)$ 位置一定是已经铺了的，否则不可能转移到一个合法的状态；如果是**向上竖着放**，那么 $(i-1,j)$ 一定要是未铺的；如果**向左横着放**，那么 $(i,j-1)$ 一定是未铺的。

本题还可以转化为从多段图的一个节点到达另一个节点的路径个数，矩形里的每一个方块都是一个阶段。而且递推的时候要求一个阶段只需要用到他的上一个阶段，所以可以用**滚动数组**实现（优化空间）。


---


### 那么直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//十年OI一场空，不开 long long 见祖宗。
int n,m,res;
int f[13][1<<13];
inline void init(){//初始化
	memset(f,0,sizeof(f));
	res=0;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    while(true){
    	cin>>n>>m;
    	if(n==0&&m==0)	break;
    	init();//每一次都要清空数组！
        f[res][(1<<m)-1]=1;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                res^=1;
				for(int l=0;l<1<<m;l++)	f[res][l]=0;
				for(int k=0;k<1<<m;k++){
                    int cnt=f[res^1][k];
                    if(k&(1<<m-1)){
                        f[res][(k<<1^1<<m)]+=cnt;
                        if(j&&!(k&1))	f[res][(k<<1^1<<m)+3]+=cnt;
                    }
                    else if(i!=0)	f[res][(k<<1)+1]+=cnt;
                }                
            }
		cout<<f[res][(1<<m)-1]<<'\n';
    }
    return 0;
}
```

---

## 作者：QQzhi (赞：2)

### 详尽分析
状压动规，不熟悉则可先做下板子[P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)，关于本类题目可自行搜索了解插头动规。

我们用 $dp_{i,j}$ 表示第 $i$ 排状态为 $j$ 时的方案数，其中 $j$ 每一位记录每列下方边框是否完整，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/zid3uwc8.png)

可知上下`0 1`即构成竖砖，排除竖砖后横排`1 1`即构成横砖。

转移时，要排除以下状态：

1. （跨行嵌合）上下均为`0 0`，即非法放置的竖上半砖。
2. （行内嵌合）排除竖的上下半砖后，连续的横半砖的数量为奇数，即非法放置的横上半砖。

![](https://cdn.luogu.com.cn/upload/image_hosting/u1gha1oa.png)

动规部分判断状态合法后，统计转移即可。
### 代码
优化：`ans` 记忆结果以支持多次查询，翻转地面使 $n\ge m$ 以合并镜像情况。
```cpp
#include <cstdio>
#include <cstring>
#define w (1<<m)
int n,m;
long long dp[11][1<<11],ans[12][12];
bool chk(int a,int b){
	if ((~a)&(~b)&(w-1))return 0;//判断非法竖半砖
	bool cnt=0;
	for (int i=0;i<m;i++){
		if ((~b)&1||(~a)&1){//竖半砖处对横半砖连续段进行结算
			if (cnt)
				return 0;//判断非法横半砖
			else
				cnt=0;
		}else{
			cnt=!cnt;//奇偶反转
		}
		a>>=1,b>>=1;
	}
	return !cnt;
}
void solve(){
	memset(dp,0,sizeof(dp));
	for (int i=0;i<w;i++)
		dp[0][i]=chk(w-1,i);//第一排上方视为完整的边界
	for (int i=1;i<n;i++)
		for (int j=0;j<w;j++)
			for (int k=0;k<w;k++)
					dp[i][k]+=chk(j,k)*dp[i-1][j];
	printf("%lld\n",ans[n][m]=dp[n-1][w-1]);//最后一排下方应为完整的边界
}
int main(){
	memset(ans,-1,sizeof(ans));
	while(scanf("%d%d",&n,&m),n){
		if (n<m)
			n^=m,m^=n,n^=m;
		if (ans[n][m]==-1)
			solve();
		else
			printf("%lld\n",ans[n][m]);
	}
}
```

---

## 作者：_ChongYun_ (赞：2)

状压 dp 典题。

### Solution

可以将这样的 $1  \times 2$ 矩形组成的状态表示为 $0$ 和 $1$，也就是说对于每一个位置只有 $0$ 和 $1$ 两种取值。

我们可以自己设定一个每个位置取 $0$ 或 $1$ 的规则。例如这种规则：

- 对于每一个纵向摆放的 $1  \times 2$ 矩形，将其上面的位置取 $1$。

- 其余的纵向摆放的 $1  \times 2$ 矩形的下面、横向摆放的 $1  \times 2$ 矩形的左边、横向摆放的 $1  \times 2$ 矩形的右边，均取 $0$。

这样做的好处是若这个位置没有继续向下延伸（不是纵向摆放的 $1  \times 2$ 矩形上面的位置），其对以后的行的状态是没有任何影响的，所以我们接下来就可以使用状压 dp，将每一行的状态压成一个数。

$dp_{i,j}$ 表示枚举到第 $i$ 行，且第 $i$ 行的状态为 $j$ 的方案数。状态转移很显然，下面我们认为已经枚举了有效状态 $j$ 和 $k$，分别表示第 $i$ 行和第 $i-1$ 行的状态。

$$dp_{i,j}=\sum_{i=1}^n dp_{i-1,k}$$

注意在枚举状态的过程中，有一些状态是不可取的。由于我们的规则，发现对于两个相邻的行的状态，同一列的两个位置不可能同时为 $1$。而且不可能有连续奇数个位置两行都为 $0$，因为如果是纵向摆放的矩形，那么它的上面一定是 $1$，已经被排除，横向摆放的连续矩形的长度加起来一定是偶数。显然，这可以预处理出来。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool vis[4005];
int n,m,dp[15][4005];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
bool check(int x){
	int now=0;
	for(int i=0;i<m;i++){
		if(x>>i&1){
			if(now&1) return false;
			now=0;
		}
		else now++;
	}
	if(now&1) return false;
	return true;
}
signed main(){
	while(true){
		n=read(); m=read();
		if(!n&&!m) break;
		for(int i=0;i<(1<<m);i++) vis[i]=check(i);
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int qwq=0;qwq<(1<<m);qwq++){
				for(int qaq=0;qaq<(1<<m);qaq++){
					if(qwq&qaq) continue;
					if(!vis[qwq|qaq]) continue;
					dp[i][qwq]+=dp[i-1][qaq];
				}
			}
		}
		printf("%lld\n",dp[n][0]);
	}
	return 0;
}
```

---

## 作者：zcz0263 (赞：2)

### 做法
因为 $h,w$ 较小，所以考虑状压 DP。

设 $f_{i,S}$ 表示正在填的是第 $i$ 行，$S$ 中二进制位为 $1$ 的位置表示第 $i$ 行此列的位置要和 $i+1$ 行的对应位置合起来放置一个矩形（即钦定预留给下一行向上放矩形的位置）。

考虑什么样的 $f_{i-1,T}$ 可以转移到 $f_{i,S}$。  
第一种是不可能有 $i,i-1$ 行的同一列都预留给下面的位置，因为这样 $i-1$ 行钦定的矩形就没有下半部分了；  
第二种首先要考虑某一列若在 $S$ 或 $T$ 中对应位置为 $1$，则这个位置一定被一个矩阵占住了，第 $i$ 行剩余的列中连续 $0$ 的个数一定为偶数，因为这些格子不可能被 $i+1$ 行的格子填上了（没有钦定预留），也没有被 
$i-1$ 行的格子填上，所以一定是被横着摆放的矩形占据，如果个数为奇数则放不满。

我们发现检测上述第二种条件时复杂度会多乘一个 $m$，所以预处理所有可能性即可。

目标状态：因为放到第 $n$ 行之后不能再向下放，所以目标状态为 $f_{n,0}$。

一组数据内的时间复杂度为 $O(n\times 4^m)$。
### 代码

```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
using namespace __gnu_cxx;
//using namespace __gnu_pbds;
#define int long long
#ifndef int
#define INF INT_MAX
#endif
#ifdef int
#define INF LLONG_MAX
#endif
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define pipii pair<int,pii>
#define vpii vector<pair<int,int>>
#define _max(x,y) (((x)>(y))?(x):(y))
#define _min(x,y) (((x)<(y))?(x):(y))
#define max(...) max({__VA_ARGS__})
#define min(...) min({__VA_ARGS__})
#define tomax(x,...) ((x)=max((x),__VA_ARGS__))
#define tomin(x,...) ((x)=min((x),__VA_ARGS__))
#define tomx(x,...) tomax(x,__VA_ARGS__)
#define tomn(x,...) tomin(x,__VA_ARGS__)
#define link tfshtrj
#define y1 drshzhsrd
#define mkp make_pair
#define pb push_back
#define eb(...) emplace_back(__VA_ARGS__)
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define all(x) x.begin(),x.end()
#define allt(x,y,z) x.begin()+y,x.begin()+z
#define fi first
#define se second
//
bitset<1<<12> mp;
int n,m,f[12][1<<12];
void solve(){
	f[0][0]=1;
	rep(i,0,(1<<m)-1){
		bool cnt=0,can=0;
		rep(j,0,m-1){
			if((i>>j)&1) can|=cnt,cnt=0;
			else cnt^=1;
		}
		mp[i]=!(can|cnt);
	}
	rep(i,1,n){
		rep(j,0,(1<<m)-1){
			//	f[i][j]=0;
			rep(k,0,(1<<m)-1){
				if((!(k&j))&&(mp[k|j])){
					f[i][j]+=f[i-1][k];
				}
			}
		}
	}
	cout<<f[n][0]<<"\n";
}
main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	while(cin>>n>>m,n|m){
		solve();
		mp=0;
		memset(f,0,sizeof(f));
	}
}

```

---

## 作者：be_RISK (赞：1)

## 题意
求一个 $n\times m$ 的矩形由 $1\times 2$ 大小的矩形填满的方案数。
## 思路
首先，很容易想到这种题目是状态压缩动态规划，于是就来思考怎么压。

接着，我们可以将状态压位 $2$ 进制，$0$ 表示当前位置不放到下一行，$1$ 表示当前位置会放到下一行。（如下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/nzq4q3bk.png)

然后，我们发现，当前行是否合法，当前这一行按位或上上一行的二进制中，$0$ 的连通块，每块的长度都为偶数时合法，那么每次在更新时扫一遍判断一下就好了。

再让后，来看状态：$f_{i,c_j}$ 表示枚举到第 $i$ 行，当前状态为第 $j$ 种合法方案时的方案数。这样转移很自然的就出来了：$f_{i,j}=\sum_{k = 1}^{cnt}f_{i,c_k}$，此时，$c_k$ 表示合法的第 $k$ 种状态。那么代码就很好想了

最后，在初始化第 $1$ 行时，只用考虑 $j$ 是否合法，不用枚举上一行去判断，以及输出只用输出 $f_{n,c_1}$（$c_1$ 固定为 $(000...0)_2$）。
## code
```c++14
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	char c=getchar();
	int ret=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=getchar();
	}return ret*f;
}
inline void write(int x,int op){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10,0);
	putchar((char)(x%10+'0'));
	if(op){
		if(op>0)puts("");
		if(op<0)putchar(' ');
		if(op==0)puts("114514");
	}
}
const int N=15,M=1<<15;
int n=read();
int m=read();
int f[N][M];
bool check(int x){//判断
	int cnt=0;
	while(x){
		int t=x&1;
		if(t){
			if(cnt&1)return 0;
			else cnt=0;
		}
		else cnt++;
		x>>=1;
	}return 1;
}
void solve(){
	memset(f,0,sizeof f);//初始化
	int tmp=1<<m;
	for(int i=0;i<tmp;i++)if(check(i|tmp))f[1][i]=1;//第1行的初始化
	for(int i=2;i<=n;i++){
		for(int j=0;j<tmp;j++){
			for(int k=0;k<tmp;k++){
				if((j&k)||!check((j|k)|tmp))continue;//不合法，跳过
				f[i][k]+=f[i-1][j];//转移
			}
		}
	}
	write(f[n][0],1);//输出
	return ;
}
signed main(){
	while(n!=0||m!=0){//多组数据
		solve();
		n=read(),m=read(); 
	}
	return 0;
}//~*完结撒花*~
```

---

## 作者：Super_Cube (赞：0)

# Solution

设 $dp_{i,j}$ 表示第 $i$ 行突起处集合为 $j$ 的方案数。转移为 $dp_{i,j}=\displaystyle\sum_{f(k,j)} dp_{i-1,k}$，其中 $f(j,i)$ 表示若上一行突起状态为 $j$，当前行突起状态为 $i$ 是否符合条件。若 $j\cap i=\varnothing$ 且 $j\cup i$ 没有连续奇数个 $0$ 则 $f(j,i)=1$。初始化 $dp_{1,i}=f(0,i)$，答案为 $dp_{n,0}$。

# Code

```cpp
#include<stdio.h>
int n,m;
inline bool check(int j,int i){
	if(i&j)return false;
    i|=j;
	static int c;c=0;
	for(int k=0;k<m;++k){
		if(i>>k&1){
			if(c&1)return false;
			c=0;
		}else ++c;
	}
	return !(c&1);
}
long long dp[12][2048];
int main(){
	while(scanf("%d%d",&n,&m)){
		if(!n&&!m)break;
		for(int i=(1<<m)-1;~i;--i)
			dp[1][i]=check(0,i);
		for(int i=2;i<=n;++i)
			for(int j=(1<<m)-1;~j;--j){
				dp[i][j]=0;
				for(int k=(1<<m)-1;~k;--k)
					if(check(k,j))dp[i][j]+=dp[i-1][k];
			}
		printf("%lld\n",dp[n][0]);
	}
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路
依次考虑每一行。

每行的每个位置有两个状态：竖着摆的矩形的一部分和横着摆的矩形的一部分。由于 $N, M \le 11$，显然是状压的套路：$f _ {i, j}$ 表示 $i$ 行状态为 $j$ 的方案数。其中 $1 \le i \le N$，$0 \le j \le 2 ^ M$。$j$ 是一个二进制串，位置为 $1$ 表示该位置是一个竖着的 $1 \times 2$ 矩形的上半部分（只表示上半部分的原因是为了好区分是否与上面的矩形相连），$0$ 表示其它状态。

进行转移时，对于每一行枚举状态 $j$ 和上一行状态 $k$。能从 $k$ 转移到 $j$ 当且仅当满足以下两个条件：
- $j \operatorname {bitand} k = 0$，$\operatorname {bitand}$ 表示按位与（C++ 中的 `&` 或 `bitand`）。这是为了保证竖着的矩形相连，即 $1$ 下面必须填 $0$。
- 设字符串 $s$ 为 $j \operatorname {bitor} k$ 的结果转换为二进制，$\operatorname {bitor}$ 表示按位或（C++ 中的 `|` 或 `bitor`），则 $s$ 中的每一段连续的 $0$ 的个数必为偶数。这是为了保证每一个表示横着的 $1 \times 2$ 矩形的左半部分的 $0$ 右边都是 $0$。（即没有只有一半的横矩形）

为了保证速度，我们可以预处理出包含所有满足每一段连续的 $0$ 的个数为偶数的字符串的集合，判断是否在集合内即可。
### 代码

```cpp
#include <bits/stdc++.h>

#define reg register

typedef long long ll;
int n, m;
ll dp[12][1 << 11];
bool s[1 << 11], odd, cnt;

void init(int m)
{
    for (reg int i = 0; i < (1 << m); ++i)
    {
        odd = cnt = 0;
        for (reg int j = 0; j < m; ++j)
            if ((i >> j) & 1)
            {
                odd |= cnt;
                cnt = 0;
            }
            else
                cnt xor_eq 1;
        s[i] = not (odd | cnt);
    }
}

signed main()
{
    while (scanf("%d%d", &n, &m) and n)
    {
        init(m);
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        for (reg int i = 1; i <= n; ++i)
            for (reg int j = 0; j < (1 << m); ++j)
                for (reg int k = 0; k < (1 << m); ++k)
                    if (not (j & k) and s[j | k])
                        dp[i][j] += dp[i - 1][k];
        printf("%lld\n", dp[n][0]);
    }
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

我来写一发 dfs+刷表法。

首先我们还是按照状态压缩的流程，有 $f_{i,j}$ 表示：目前填到第 $i$ 行，且该行的状态为 $j$。

那么我们怎么样定义状态呢？我们定义每个矩形的最后一行为 $0$，其余为 $1$。具体来说，两种矩形我们分别表示为 $\begin{bmatrix} 0 ~0\end{bmatrix}$ 和 $\begin{bmatrix}1 \\0 \end{bmatrix}$。



那么当枚举到当前行 $i$，我们要枚举一下上一行的状态 $j$，然后看在 $j$ 的状态下，第 $i$ 行可能的状态有那些。这里我们用 dfs 搜索出第i行可能的状态，然后从 $f_{i-1,j}$ 转移即可。

具体来说，搜索时传入一下参数：

- 当前行，上一行的状态，当前列，当前行考虑到当前列时的状态。

在填状态的时候，考虑上一行的当前列的状态：

- 如果是 $1$，那么这里只能填 $0$。

- 如果是 $0$，这里可以填 $1$，也可以填 $0$（此时我们要考虑下一个位置是否可填 $0$，如果不行，那么这里也不可以填；如果可以，填了之后直接跳到下下列）。

对于最后一行的边界，我们直接取 $f_{n,0}$ 为答案即可。不用顾及有矩形长出来的情况。

```C++

itn f[14][10004];

int getw(int x,int k){
    return x&(1<<k)?1:0;
}

void dfs(itn x,int pre,int y,itn now){
    if(y==-1){
        f[x][now]+=f[x-1][pre];
        return ;
    }

    int cur=pre&(1<<y)?1:0;
    if(cur){
        dfs(x,pre,y-1,now<<1);
    }else{
        dfs(x,pre,y-1,now<<1|1);
        if(y>0&&getw(pre,y-1)==0)dfs(x,pre,y-2,now<<2);
    }
}


void solve(){
    itn n=rd,m=rd;
    if(n+m==0)exit(0);

    memset(f,0,sizeof f);

    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<(1<<m);j++){
            dfs(i,j,m-1,0);
        }
    }
    cout<<f[n][0]<<endl;
}

```


做了本题可以看 [CEOI2002] Bugs Integrated,Inc. 也是一样的做法。（致审核~：那个小数点不是句号，是题目名带的）

本文同步发于：[oi-beats/状态压缩](https://ntsc-yrx.github.io/oi-beats/site/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E7%8A%B6%E5%8E%8BDP/)，[个人博客/状态压缩](https://flowus.cn/ntsc/share/60456607-3106-48b4-93ac-cec48858ae26?code=3L02QC
)

---

## 作者：wdsjl (赞：0)

# P10975题解
~~看了这题数据规模，嗯就像状态压缩的动态规划题~~

## 题目分析
- 我们看对于每一行如果有竖着的长方形的上一半，那么下一行这个地方就必须补全。
- 对于不是竖着的就必须满足连续偶数个来放横着的长方形。

那我们考虑状态压缩，我们可以用二进制表示这一行的状态，即，我们用 $1$ 表示竖着长方形上边的一半， $0$ 则表示其他状态。

$f_{i,j}$ 表示第 $i$ 行的状态为 $j$。

如果 $i-1$ 行的状态 $j$ 可以转移到 $i$ 行状态 $k$：

1. $k$ 和 $j$ 按位与结果为 $0$。
2. $k$ 和 $j$ 按位或每段连续的 $0$ 为偶数个。

为了优化时间复杂度，我们可以将一行中按位或每段连续的 $0$ 为偶数个的情况预处理出来。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m;
long long f[12][1<<11];
bool c[1<<11];

int main(){
	while(cin>>n>>m&&n){
		memset(f,0,sizeof(f));
		memset(c,0,sizeof(c));
		for(int i=0;i<1<<m;i++){
			bool cnt=0,hs=0;
			for(int j=0;j<m;j++){
				if(i>>j&1)hs|=cnt,cnt=0;
				else cnt^=1;
			}
			c[i]=hs|cnt?0:1;
		}
		f[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<1<<m;j++){
				f[i][j]=0;
				for(int k=0;k<1<<m;k++){
					if((j&k)==0&&c[j|k])
						f[i][j]+=f[i-1][k];
				}
			}
		}
		printf("%lld\n",f[n][0]);
	} 
	return 0;
} 
```

---

