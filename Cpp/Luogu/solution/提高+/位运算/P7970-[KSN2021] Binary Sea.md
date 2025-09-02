# [KSN2021] Binary Sea

## 题目描述

有一个 $N\times M$ 的网格，行列从 $0$ 开始，从左上到右下编号。

第 $i$ 行，第 $j$ 列的格子是黑格当且仅当 $i\text{ and }j=0$。

两个黑格联通当且仅当它们都是黑格且它们可以经过若干个有**邻边**的黑格到达。

给定 $Q$ 个矩形，左上角为 $(x_1,y_1)$，右下角为 $(x_2,y_2)$，你需要对于每个矩形求出所有的黑格形成了多少连通块。

## 说明/提示

**【样例解释】**

以下为样例中四个询问的图示：

![](https://api.tlx.toki.id/api/v2/problems/JIDPROGSepzakraFyFK27n5u3QV/render/sample-q1.png) ![](https://api.tlx.toki.id/api/v2/problems/JIDPROGSepzakraFyFK27n5u3QV/render/sample-q2.png) ![](https://api.tlx.toki.id/api/v2/problems/JIDPROGSepzakraFyFK27n5u3QV/render/sample-q3.png) ![](https://api.tlx.toki.id/api/v2/problems/JIDPROGSepzakraFyFK27n5u3QV/render/sample-q4.png)

**【数据范围】**

**本题采用捆绑测试。**

* Subtask 1（5 points）：只存在一组数据，满足 $N = M=12$，$Q=3$，每次询问的 $(x_1,y_1,x_2,y_2)$ 依次为 $(1,1,9,8)$，$(8,8,11,11)$ 和 $(4,3,5,9)$。
* Subtask 2（11 points）：$N,M,Q\le 200$。
* Subtask 3（10 points）：$N,M,Q\le 2000$，$x_1=x_2$。
* Subtask 4（20 points）：$N,M,Q\le 2000$。
* Subtask 5（4 points）：$x_1=x_2=0$。
* Subtask 6（6 points）：保证对于每个询问存在整数 $k$ 使得 $x_1=x_2=2^k$。
* Subtask 7（29 points）：$x_1=x_2$。
* Subtask 8（15 points）：无特殊限制。

对于所有数据，$0\leq x_1\leq x_2<N\leq 10^9$，$0\leq y_1\leq y_2<M\leq 10^9$，$1\leq Q\leq 10^5$。

## 样例 #1

### 输入

```
6 5 4
0 0 3 2
0 2 1 3
0 1 2 4
5 4 5 4```

### 输出

```
1
1
2
0```

# 题解

## 作者：I_am_Accepted (赞：4)

首先发现 $n,m$ 是没有用的，可以假想平面是无限大的。

然后有一个结论：

对于任意黑格 $(x,y)[x,y>0]$，都有 $(x-1,y)$ 与 $(x,y-1)$ **两者其一**是黑格。

**证明 1：**

![](https://cdn.luogu.com.cn/upload/image_hosting/rsevgvwz.png)

（黑格组成了谢尔宾斯基三角状物）

**证明 2：**

由对称性，且 $x\ \text{and}\ y=0$，不妨设 $\text{lowbit}(x)<\text{lowbit}(y)$。

由于 $x-1=x-\text{lowbit}(x)+(\text{lowbit}(x)-1)$，就是将二进制中末尾的 $100\dots0$ 变为 $011\dots1$。

所以 $(x-1)\ \text{and}\ y=0$，对偶地 $x\ \text{and}\ (y-1)\ne 0$，得证。

* * *

所以黑格形成了一棵向右下的树啊！

所以对于一个矩形，其内的连通块数（森林的树个数）等于矩形左侧和上侧的边数。

![](https://cdn.luogu.com.cn/upload/image_hosting/sztv6p7f.png)

（就是上图的蓝圈数量）

形式化地，我们不妨只考虑上侧的边，个数为（矩形为 $(x,y,xx,yy)$）：
$$\begin{aligned}
&\sum_{i=y}^{yy}[i\ \text{and}\ x=0][i\ \text{and}\ (x-1)=0]
\\
=&\sum_{i=y}^{yy}[i\ \text{and}\ (x\ \text{or}\ (x-1))=0]
\\
=&\sum_{i=0}^{yy}[i\ \text{and}\ (x\ \text{or}\ (x-1))=0]
-\sum_{i=0}^{y-1}[i\ \text{and}\ (x\ \text{or}\ (x-1))=0]
\end{aligned}
$$

然后 $O(\log)$ DP 就做完了。

```cpp
/*
* Author: ShaoJia
* Last Modified time: 2022-09-19 11:14:26
* Motto: We'll be counting stars.
*/
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
int f[31][2];//[0,i-1] did, 0 didnt exceed y, 1 exceed y
int work(int x,int y){
	if(y<0 || x==0) return 0;
	x|=x-1;
	bool X,Y;
	int z;
	For(i,1,30){
		f[i][0]=f[i][1]=0;
		X=x>>(i-1)&1;
		Y=y>>(i-1)&1;
		z=f[i-1][0]+f[i-1][1];
		if(!X){
			if(Y){
				f[i][0]+=f[i-1][0];
				f[i][1]+=f[i-1][1];
			}else{
				f[i][1]+=z;
			}
		}
		if(Y){
			f[i][0]+=z;
		}else{
			f[i][0]+=f[i-1][0];
			f[i][1]+=f[i-1][1];
		}
	}
	return f[30][0];
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	int T,x,y,xx,yy;
	cin>>T>>T>>T;
	f[0][0]=1;
	while(T--){
		cin>>x>>y>>xx>>yy;
		if(!x && !y) cout<<"1\n";
		else cout<<(work(x,yy)-work(x,y-1))+(work(y,xx)-work(y,x-1))<<"\n";
	}
return 0;}
```

---

## 作者：enucai (赞：2)

## Analysis

通过打表不难发现：满足 $x\text{ and }y=0$ 的点 $(x,y)$ 构成了一棵树。因此某一个区域内的连通块数量的 点数 - 边数。

进一步观察，发现对于任意不是 $(0,0)$ 的黑色点 $(x,y)$，$(x,y-1)$ 与 $(x-1,y)$ 中恰有一个点是黑色点。

---

证明：设 $x$ 的二进制最低 $n$ 位均为 $0$，$y$ 的二进制最低 $m$ 位均为 $0$。由于 $x\text{ and }y=0$，故 $n\not=m$。不妨令 $n<m$。

当选择将 $n$ 进行 $-1$ 操作时，$n$ 的二进制最低 $n$ 位变为 $1$，第 $n+1$ 位变为 $0$。而 $m$ 的最低 $n+1$ 位一定都是 $0$，故 $(x-1)\text{ and }y=0$。

当选择将 $m$ 进行 $-1$ 操作时，$m$ 的二进制最低 $m$ 位变为 $1$，又因为 $n<m$，故在第 $n+1$ 低位处 $x$ 与 $y-1$ 均为 $1$，故 $x\text{ and }y\not=0$。

命题得证。

---

因此在考虑一个矩形区域内的连通块个数时，只需要计算第一行与第一列的点数与边数即可。

问题转换为：求 $\sum\limits_{i=l}^r[i\text{ and }x=0]$ 与 $\sum\limits_{i=l}^r[(i\text{ or }(i+1))\text{ and }x=0]$。

数位 dp 一下即可。复杂度 $O(q\log n)$。

求解 $\sum\limits_{i=l}^r[i\text{ and }x=0]$ 是一个标准的数位 dp，不再追述。

求解 $\sum\limits_{i=l}^r[(i\text{ or }(i+1))\text{ and }x=0]$ 时，发现 $x$ 变为 $x\text{ or }(x+1)$ 只是将 $x$ 的最低 $0$ 位变为了 $1$。那么在数位 dp 的 dfs 时只要再传一个参数，表示后面是否需要有一个“空闲”的 $0$ 即可。非常朴素。

## Code

```cpp
int dig[31],f[31][2],g[31][2][2];
int dp1(int x,int lim,int dep){
  if(f[dep][lim]!=-1) return f[dep][lim];
  int res=0,tmp=((x>>dep)&1);
  if(dep==0){
    if(tmp==0){//can be 0 or 1
      if(lim){
        res+=2;
      }else{
        if(dig[dep]==0) res+=1;
        else res+=2;
      }
    }else{//only 0
      res+=1;
    }
    return f[dep][lim]=res;
  }
  if(tmp==0){//can be 0 or 1
    if(lim){//no limit
      res+=2*dp1(x,1,dep-1);
    }else{
      if(dig[dep]==0) res+=dp1(x,0,dep-1);
      else res+=dp1(x,0,dep-1)+dp1(x,1,dep-1);
    }
  }else{//only 0
    if(lim){//no limit
      res+=dp1(x,1,dep-1);
    }else{
      if(dig[dep]==0) res+=dp1(x,0,dep-1);
      else res+=dp1(x,1,dep-1);
    }
  }
  return f[dep][lim]=res;
}
int calc1(int l,int r,int x){//(num&x)=0,num[l,r]
  if(l>r) return 0;
  int res=0;
  For(i,0,30) dig[i]=((r>>i)&1);
  memset(f,-1,sizeof(f));
  res=dp1(x,0,30);
  if(l){
    For(i,0,30) dig[i]=(((l-1)>>i)&1);
    memset(f,-1,sizeof(f));
    res-=dp1(x,0,30);
  }
  return res;
}
int dp2(int x,int lim,int dep,int ned){//lim means number limit, ned means need one dig to be 0
  if(g[dep][lim][ned]!=-1) return g[dep][lim][ned];
  int res=0,tmp=((x>>dep)&1);
  if(dep==0){
    if(ned){//must be 0
      res+=1;
    }else{
      if(tmp==0){
        if(lim){
          res+=2;
        }else{
          if(dig[dep]==0) res+=1;
          else res+=2;
        }
      }
    }
    return g[dep][lim][ned]=res;
  }
  if(tmp==0){//can be 0 or 1, when 0, ned=0
    if(lim){//no limit
      res+=dp2(x,1,dep-1,0)+dp2(x,1,dep-1,ned);
    }else{
      if(dig[dep]==0){//only 0
        res+=dp2(x,0,dep-1,0);
      }else{
        res+=dp2(x,0,dep-1,ned)+dp2(x,1,dep-1,0);
      }
    }
  }else{//only 0, ned=1
    if(lim){//no limit
      res+=dp2(x,1,dep-1,1);
    }else{
      if(dig[dep]==0){//only 0
        res+=dp2(x,0,dep-1,1);
      }else{
        res+=dp2(x,1,dep-1,1);
      }
    }
  }
  return g[dep][lim][ned]=res;
}
int calc2(int l,int r,int x){//((num|num+1)&x)=0,num[l,r]
  if((x&1)||l>r) return 0;
  int res=0;
  For(i,0,30) dig[i]=((r>>i)&1);
  memset(g,-1,sizeof(g));
  res=dp2(x,0,30,0);
  if(l){
    For(i,0,30) dig[i]=(((l-1)>>i)&1);
    memset(g,-1,sizeof(g));
    res-=dp2(x,0,30,0);
  }
  return res;
}
void work(){
  int lx,ly,rx,ry; qin>>lx>>ly>>rx>>ry;
  int res=calc1(lx,rx,ly)-calc2(lx,rx-1,ly)+calc1(ly,ry,lx)-calc2(ly,ry-1,lx)-((lx&ly)==0);
  qout<<res<<"\n";
}
```

---

