# Arrangement

## 题目描述

在公元 2500 年，开罗德国大学（GUC）的年度毕业典礼已经顺利举办了近 500 年。

典礼中最重要的部分是教授们在典礼大厅中的排列。

按照传统，GUC 有 $n$ 位教授。每位教授都有其资历等级，且所有资历等级互不相同。我们将教授编号为 $1$ 到 $n$，其中 $1$ 号教授资历最高，$n$ 号教授资历最低。

典礼大厅有 $n$ 个座位，每位教授一个座位。大厅中的某些座位对更资深的教授来说更为重要。更具体地说，有 $m$ 对座位存在“资深-资浅”关系，传统要求对于所有 $m$ 对座位 $(a_i, b_i)$，坐在“资深”位置 $a_i$ 的教授必须比坐在“资浅”位置 $b_i$ 的教授更资深。

GUC 对其传统极为严格，自 2001 年起一直严格遵守。传统要求：

- 教授的座次每年都要更换。
- 2001 年典礼采用的是教授在典礼大厅中的字典序第一个排列。
- 每一年都采用字典序下一个排列。

教授的排列是 $n$ 个整数的列表，第一个整数表示坐在第 1 号位置的教授的资历，第二个整数表示坐在第 2 号位置的教授的资历，依此类推。

给定 $n$（教授人数）、$y$（当前年份）和 $m$ 对限制条件，请输出该年份教授的座次排列。

## 说明/提示

在第一个样例中，字典序第一个排列为 1 2 3。

在第三个样例中，GUC 在第 3630800 年后将没有可用的排列。

在第四个样例中，没有合法的座次排列。

排列的字典序比较方式与现代编程语言中的 < 运算符一致。排列 $a$ 在字典序上小于排列 $b$，当且仅当存在某个 $i$（$1 \leq i \leq n$），使得 $a_i < b_i$，并且对于所有 $j$（$1 \leq j < i$）都有 $a_j = b_j$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2001 2
1 2
2 3
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
7 2020 6
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
1 2 3 7 4 6 5
```

## 样例 #3

### 输入

```
10 3630801 0
```

### 输出

```
The times have changed
```

## 样例 #4

### 输入

```
3 2001 3
1 2
2 3
3 1
```

### 输出

```
The times have changed
```

# 题解

## 作者：Zesty_Fox (赞：6)

更好的阅读体验：[点这里](https://www.cnblogs.com/acceptedzhs/p/13972263.html)

网上的题解大都不是很明白（注释都没有），我这里参考了一下这篇题解：[点这里](https://blog.csdn.net/alan_cty/article/details/78335605)，同时加入了很多注释方便大家理解。

首先，$n$很小，容易想到状压。

我们可以依次确定排列中每一位应该坐哪个人。那么，我们只需要知道某一位选辈分为$j$的人的方案数。

设$f_{i,j}$表示当前状态的方案数，其中$i$是一个二进制数，值为$1$的位表示对应的座位已经安排给了辈分为$1 \sim cnt_i$的人（$1$为最老，$cnt_i$表示$i$在二进制下$1$的位数），$j$表示第$x$个座位确定由辈分为$j$的人来坐。

最终结果是$f_{{2^n-1},y}$，$y \in [1,n]$。

如何转移呢？我们可以枚举辈分$cnt_i+1$的人坐哪个位置，进行转移即可。（具体见代码中的注释）

Code:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int BIT=(1<<17),M=110,N=25;
int n,m,cnt[BIT],a[M];
ll f[BIT][N],b[N],p[N],year;
//f[i][j]
//i中1的位表示对应的座位已经安排给了辈分为1~cnt[i]的人(1为最老)
//j表示第x位确定安排给辈分为j的人坐
//b[i]表示辈分为i的人在哪个位置

//辈分为1~n，1为最老，n为最年轻
void solve(int x){
    memset(f,0,sizeof(f));
    f[0][0]=1;int maxb=(1<<n);
    //按辈分从老到年轻依次安排座位
    for(int i=0;i<maxb;i++){
        for(int j=0;j<=n;j++){
            int y=cnt[i]+1;
            if(b[y]){//若辈分为cnt[i]+1的人已经安排了座位
                //安排过的座位不满足这一个座位的要求，continue
                if((a[b[y]]&i)!=a[b[y]]) continue;
                //当前座位已经被占用了，也continue
                if((1<<(b[y]-1)&i)==(1<<b[y]-1)) continue;
                //如果辈分为cnt[i]+1的人刚好坐在x位置上，那么j=cnt[i]+1
                if(b[y]==x) f[i|(1<<b[y]-1)][y]+=f[i][j];
                //否则继续保持原来的j
                else f[i|(1<<b[y]-1)][j]+=f[i][j];
            }
            else{
                for(int k=1;k<=n;k++){//枚举辈分为cnt[y]+1的人应该放哪个位置
                    if(!(i&(1<<k-1))){
                        if((a[k]&i)!=a[k]) continue;
                        //与上面类似的转移
                        if(k==x) f[i|(1<<k-1)][y]+=f[i][j];
                        else f[i|(1<<k-1)][j]+=f[i][j];
                    }
                }
            }
        }
    }
}

int main(){
    scanf("%d%lld%d",&n,&year,&m);year-=2000;
    //cnt[i]表示i在二进制下1的个数
    for(int i=1;i<BIT;i++) cnt[i]=cnt[i^(i&(-i))]+1;
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        a[y]|=(1<<x-1);
        //a[i]是一个二进制数，其中1的位表示 这一位对应的
        //座位上坐的人 的辈分 必须比 i座位上坐的人 的辈分 大
    }
    for(int i=1;i<=n;i++){
        solve(i);ll sum=0;
        for(int j=1;j<=n;j++){
            if(!b[j]&&sum+f[(1<<n)-1][j]>=year){
                //刚好加上这个位置坐辈分为j的人的方案数可以大过year
                b[j]=i;p[i]=j;
                year-=sum;break;
            }
            sum+=f[(1<<n)-1][j];
        }
        if(!p[i]){//这一位无法确定，无解
            puts("The times have changed");
            return 0;
        }
    }
    for(int i=1;i<=n;i++) printf("%lld ",p[i]);
    puts("");
    return 0;
}

```







---

## 作者：Feyn (赞：3)

一些约定：用 $cnt_x$ 来代表集合 $x$ 的元素个数；如果 $x$ 是一个集合，$y$ 是一个元素，那么 $x+y$ 就是把元素放入集合形成的新集合。

吐槽原翻译。原翻译把每个限制条件翻译成了第 $a_i$ 个数应该排在第 $b_i$ 个数之前输出，而且把第 $k$ 小翻译成了第 $k$ 大。别说这还真的是一道可以做的题目，甚至可以过样例。然后我就卡了一个小时，直到读了一下原题面。就很悲惨。

可以做一下 [CF123C](https://www.luogu.com.cn/problem/CF123C)，二者思路有许多相似之处，都是给定了一些限制条件，都是给定了一个优先顺序，方法也一样，即按优先顺序枚举位置，然后从小到大枚举这个位置放什么数（那道题是括号），然后用 DP 求出目前确定一些位置之后的方案数，和所求的 $k$ 比较。如果多了代表这个位置是正确的，如果少了代表这个位置放的数还不够大，那么把 $k$ 减去此时求出的方案数然后给这个位置填上一个稍大的数即可。

具体到这道题的 DP 过程，由于 $n$ 很小，想到用状压 DP。用 $f_x$ 来代表已经安排了 $1$ 到 $cnt_x$ 的数了，这些数对应的位置集合是 $x$ 的方案数，转移上枚举第 $cnt_x+1$ 个数放在哪个位置。一个合法的位置 $y$ 应该满足以下四个条件：

- $y$ 不应该在 $x$ 集合中。

- 令所有被要求在 $y$ 之前的位置集合为 $s$ ，那么 $s$ 应该是 $x$ 的子集，也就是说这些位置一定分配到了比当前 $cnt_x+1$ 小的数。

- 之前 $cnt_x+1$ 没有分配好位置，或者分配了并且 $y$ 就是这个位置。

- 之前位置 $y$ 没有分配过数，或者分配了数并且 $cnt_x+1$ 就是这个数。

满足以上四个条件就说明状态 $x$ 可以转移到状态 $x+y$ ，累加即可。事实证明并不需要再开一维，然而不知为何它们再开一维的 DP 跑得比我快，呜呜呜。

代码没什么细节。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=17;
const int M=1<<N-1;
const int maxn=1e18;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}
inline void add(int &s1,int s2){s1+=s2;if(s1>maxn)s1=maxn;}

int m,n,rk,s[N],f[M],bl[N],to[N],cnt[M]={1};
inline int solve(bool ws){
	memset(f,0,sizeof(f));f[0]=1;
	for(int i=0;i<(1<<m);i++){
		for(int j=1;j<=m;j++){
			if((i&(1<<j-1))!=0||(s[j]&i)!=s[j]||(to[j]!=0&&cnt[i]!=to[j])||(bl[cnt[i]]!=0&&bl[cnt[i]]!=j))continue;
			add(f[i+(1<<j-1)],f[i]);
		}
	}
	return f[(1<<m)-1];
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(rk);read(n);rk-=2000;int s1,s2,ch=0,pl,nd;
	while(n--){read(s1);read(s2);s[s2]|=(1<<s1-1);}
	for(int i=1;i<(1<<m);i++)cnt[i]=cnt[i>>1]+(i&1);
	for(int i=1;i<=m;i++){
		for(pl=1;pl<=m;pl++){
			if(((1<<pl-1)&ch)!=0||bl[pl])continue;
			bl[pl]=i;to[i]=pl;
			if((nd=solve(false))>=rk)break;
			else rk-=nd,bl[pl]=0;
			
		}
		if(pl>m){printf("The times have changed\n");return 0;}
		printf("%I64d ",pl);
	}
	
	return 0;
}
```

---

