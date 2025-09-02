# [BalticOI 2008] 网格

## 题目描述

Byteland 国的地图是一个大小为 $n\times m$ 的网格（$n$ 是垂直方向长度，$m$ 是水平方向长度）。标记分隔的水平线被叫做平行线，并编号为 $0$ 到 $n$，标记分隔的垂直线被叫做子午线，并编号为 $0$ 到 $m$。

在 Byteland 国，天气预报是一个十分严肃的话题，对于每个单元格，准备天气预报需要一定时间来计算。由于地形条件和其他因素，不同的单元格有着不同的计算时间。直到目前为止，预报系统还是会依次处理每一个单元格，所以完成预报天气需要花费的时间为计算所有单元的时间。

你被要求设计一个可以在多进程处理器上运行的新系统，为了共享处理器的计算能力，Byteland 国要被 $r$ 条平行线和 $s$ 条子午线划分为 $(r+1)(s+1)$ 个矩形。每个线程会依次处理一个矩形内部的单元格，这样的话对于一个矩形区域的计算时间，就为矩形区域内单元格计算时间之和。完成预报的计算时间是一个处理器上计算时间的最大值。

你的任务是找到对于选择 $r$ 条平行线和 $s$ 条子午线分隔后最小的计算时间。

#任务

写一个程序能够：

-    从标准输入读取 Byteland 的地图，要求的平行线和子午线条数以及每个单元格的处理时间；
-    找到完成预报的最小计算时间；
-    输出这个值到标准输出。


## 说明/提示

**样例解释**

![0](https://i.loli.net/2018/02/19/5a8ae8ca02cbb.png)

第二条和第四条平行线，第四条子午线把整个国家分为六个矩形，计算时间为 $21, 13, 27, 27, 17, 31$，所以完成预报的计算时间为 $31$。

**数据范围**

对于 $40\%$ 的数据，$n\le 10,m\le 10$；

对于全部数据，$1\le r<n\le 18,1\le s<m\le 18$，$1\le i\le n,1\le j\le m,0\le c_{i,j}\le 2\times 10^6$​​。 

## 样例 #1

### 输入

```
7 8 2 1
0 0 2 6 1 1 0 0
1 4 4 4 4 4 3 0
2 4 4 4 4 4 3 0
1 4 4 4 8 4 4 0
0 3 4 4 4 4 4 3
0 1 1 3 4 4 3 0
0 0 0 1 2 1 2 0```

### 输出

```
31```

# 题解

## 作者：yuzhechuan (赞：5)

做的人真少，数据挺强，但并不卡时间，轻松最优解

---

### 题解：

套路题，对于一维（我是纵）暴力枚举状态是否切开，对于另一维二分答案后贪心的切，看看段数够不够就好了

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t,class ...A> inline void read(t &x,A &...a){
	read(x);read(a...);
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=20;
int ans=INT_MAX,mp[N][N],pre[N][N],cur[N],n,m,a,b,sum;

int count(int x){
	int res=0;
	while(x) res++,x^=x&(-x);
	return res;
}

bool check(int mid){
	int cnt=0;
	for(int i=0;i<=b;i++) cur[i]=0;
	for(int i=0;i<n;i++){
		bool flag=0;
		for(int j=0;j<=b;j++){
			cur[j]+=pre[j][i];
			if(cur[j]>mid){ //需要多切一刀
				flag=1;
				break;
			}	
		}
		if(!flag) continue;
		if(++cnt>a) return 0; //不够切
		for(int j=0;j<=b;j++) cur[j]=pre[j][i]; //重新开始
	}
	return 1;
}

signed main(){
	read(n,m,a,b);
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) sum+=read(mp[i][j]);
	for(int s=0;s<(1<<m-1);s++) if(count(s)==b){ //状态为1则表示当前列为一个块的起始列
		s=s<<1|1;
		for(int i=0;i<=b;i++) for(int j=0;j<n;j++) pre[i][j]=0;
		int l=0,r=sum,res=sum,id=-1;
		for(int i=0;i<m;i++){
			if(s>>i&1) id++;
			for(int j=0;j<n;j++) pre[id][j]+=mp[j][i],l=max(l,pre[id][j]);
		}
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid)) res=mid,r=mid-1;
			else l=mid+1;
		}
		ans=min(ans,res);
		s>>=1;
	}
	write(ans);
}
```

---

## 作者：PurpleWonder (赞：1)

在对于矩阵进行操作时，可以用暴力的方式在其中一维进行枚举，再通过经过比枚举更优一些的算法跑另外一维。相关题目：[洛谷【P2258】子矩阵](https://www.luogu.org/problemnew/show/P2258)

本题中，可以暴力枚举横向的子午线的位置，再在竖向中通过二分答案找出在此时的最优解

代码如下：（略微有点丑，开个O2才过）

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

int ma[20][20],fk[20];
int ans=0x3f3f3f3f,n,m,a,b,sum;

int pd(int x,int state){
    memset(fk,0,sizeof(fk));
    int dq=0;
    for(int i=1;i<=m;i++){
        int d=1;
        for(int j=1,jd=1;j<=n;j++,jd<<=1){
            if(fk[d]+ma[j][i]>x){
                d=1;dq++;fk[1]=0;
                if(dq>b)return false;
                for(int k=1,kd=1;k<=n;k++,kd<<=1){
                    fk[d]+=ma[k][i];
                    if(fk[d]>x)return false;
                    if(state&kd)d++,fk[d]=0;
                }
                break;
            }
            fk[d]+=ma[j][i];
            if(state&jd)d++;
        }
    }
    return true;
}

void ef(int state){
    int l=1,r=sum,res,mid;
    while(l<=r){
        mid=(l+r)>>1;
        if(pd(mid,state))res=mid,r=mid-1;
        else l=mid+1;
    }
    ans=min(res,ans);
}

void dfs(int p,int state,int gs){
    if(p>n)return;
    if(gs==a){
        ef(state);
        return;
    }
    dfs(p+1,state|(1<<(p-1)),gs+1);
    dfs(p+1,state,gs);
}

int main(){
    scanf("%d %d %d %d",&n,&m,&a,&b);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&ma[i][j]);
            sum+=ma[i][j];
        }
    }
    dfs(1,0,0);
    printf("%d",ans);
}
```

---

