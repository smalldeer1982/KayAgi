# Chattering

## 题目描述

有 $n$ 只鹦鹉围成一圈站立。每只鹦鹉在其他鹦鹉中有一定的“尊重值”，记为 $r_i$。当一只尊重值为 $x$ 的鹦鹉开始喋喋不休时，它右边和左边各 $x$ 只邻居会在 1 秒后开始重复它的话。接着，这些邻居的邻居也会开始重复，以此类推，直到所有鹦鹉都开始喋喋不休。

现在给出所有鹦鹉的尊重值。对于每只鹦鹉，回答这样一个问题：如果这只鹦鹉最先开始喋喋不休，最少需要多少秒，所有其他鹦鹉才会全部开始重复？

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 1 4 1
```

### 输出

```
2 2 1 2 
```

## 样例 #2

### 输入

```
8
1 2 2 1 5 1 3 1
```

### 输出

```
3 3 2 2 1 2 2 3 
```

# 题解

## 作者：是个汉子 (赞：2)

### Solution

能够~~显然的~~想到每个人传递必然是连续的，也就是对于一个 $i$ ，他能够到达的区间为 $[i-a_i,i+a_i]$ 。

下一次，就会转移到 $[l,r]$ 中能往左和往右的最远端点，所以我们需要记录最值，那么不难想到用ST表去处理区间最值。

设 $l_{i,j}$ 表示从 $j$ 开始 $2^i$ 秒能达到的最左端， $r_{i,j}$ 同理。然后转移就是 $l_{i,j}=\min\limits_{l_{i-1,j}\leq t\leq r_{i-1,j}}\{l_{i-1,t}\}\\r_{i,j}=\max\limits_{l_{i-1,j}\leq t\leq r_{i-1,j}}\{r_{i-1,t}\}$ 

最后倍增求解即可。

大细节：因为是在一个环上，并且同时在两个方向走，所以要将环拆开，并复制成三份，然后再进行ST表等操作。

小细节：当区间覆盖超过 $n$ 时，是完全覆盖，肯定有比选此时更优的解，跳过此时即可。

时间复杂度： $O(n\log n)$ （好像比CF官方说的好一点？）

### 代码

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=3e5+10;
int n,a[N],b[N],c[N];
int Log[N];
int l[19][N],r[19][N];

struct rmq{
    int st[N][19],val[N];
    int type;
    inline int Max(int x,int y){
        return (val[x]<val[y])?y:x;
    }
    void build(int *b,int n,int _type){
        type=_type;
        for(int i=1;i<=n;i++) st[i][0]=i,val[i]=type*b[i];
        for(int j=1;j<=Log[n];j++){
            for(int i=1;i+(1<<j)-1<=n;i++)
                st[i][j]=Max(st[i][j-1],st[i+(1<<j-1)][j-1]);
        }
    }
    inline int query(int l,int r){
        int k=Log[r-l+1];
        return Max(st[l][k],st[r-(1<<k)+1][k]);
    }
}rmq_l,rmq_r;

int main(){
    scanf("%d",&n);
    for(int i=2;i<=3*n;i++) Log[i]=Log[i>>1]+1;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i+n*2]=a[i];
    }
    if(n==1) return puts("0"),0;
    for(int i=1;i<=3*n;i++){
        b[i]=max(1,i-a[i]);
        c[i]=min(3*n,i+a[i]);
    }
    for(int i=0;i<=Log[3*n];i++) r[i][3*n]=3*n,l[i][1]=1;
    for(int i=1;i<=3*n;i++){
        l[0][i]=b[i];
        r[0][i]=c[i];
    }
    rmq_l.build(l[0],n*3,-1);rmq_r.build(r[0],n*3,1);
    for(int i=1;i<=Log[3*n];i++)
        for(int j=1;j<=3*n;j++){
            int posl=rmq_l.query(l[i-1][j],r[i-1][j]);  
            int posr=rmq_r.query(l[i-1][j],r[i-1][j]);
            l[i][j]=min(l[i-1][posl],l[i-1][posr]);
            r[i][j]=max(r[i-1][posl],r[i-1][posr]);
        }
    for(int j=n+1;j<=n*2;j++){
        int u=j,v=j;
        int ans=0;
        for(int i=Log[3*n];i>=0;i--){
            if(max(r[i][v],r[i][u])-min(l[i][u],l[i][v])+1>=n) continue;
            int nu=rmq_l.query(l[i][u],r[i][v]);
            int nv=rmq_r.query(l[i][u],r[i][v]);
            u=nu;v=nv; 
            ans+=1<<i;
        }
        ans++;
        printf("%d ",ans);
    }
    puts("");
    return 0;
}
```



---

## 作者：Caiest_Oier (赞：1)

## [CF1032G](https://www.luogu.com.cn/problem/CF1032G)   
题外话：本人模拟赛考了这个题，考场上写了个特别离谱的 $\Theta(n\log n)$ 做法过掉了此题，所以本篇题解与其他题解可能不甚相同，代码可能会更难写，但不妨作为一种新思路。    

很明显引爆区间是连续的，所以我们只需考虑左右端点的变化。考虑一个太阳爆炸的时候，它会引爆一段区间，这个区间又会再次引爆更大的一个区间。令当前区间为 $[L,R]$，则新的区间为 $[\min l_i,\max r_i],L\le i\le R$，很明显左右端点仅由两个太阳来确定，所以我们考虑改变一下计算方法。   

对于一个太阳 $i$，它的爆炸范围为 $[l_i,r_i]$，而如果我们只考虑它的二次爆炸，那么找到一个 $[l2_i,r2_i]$，满足它引爆后的效果等同于 $[l_i,r_i]$，且 $l2_i$ 与 $r2_i$ 的太阳爆炸对左右端点作出了贡献。也就是说我们把区间缩到最小，令其在二次爆炸后仍相同。   

这个东西有个好的性质，就是它好合并。令 $f_{i,j}$ 表示一个与太阳 $i$ 引爆 $2^j$ 次后的区间再次引爆后能得到相同区间的区间。这句话可能有点难以理解。我们令 $boom([a,b],c)$ 表示 $[a,b]$ 区间引爆 $2^c$ 后得到的区间，则要令 $f_{i,j}$ 满足：  

$$boom[f_{i,j},0]=boom[boom([i,i],j),0]$$   

那么我们考虑使用第三段那里，缩小区间的记法来描述。发现，对于每个太阳，对它爆炸的区间缩小后来记录，则可以满足合并。$f_{i,j}$ 可以由 $f_{i,j-1}$ 得到的两个关键太阳 $a,b$ 的$f_{a,j-1}$ 与 $f_{b,j-1}$ 中的四个太阳，计算出哪两个对左右端点有贡献来得到。那么倍增的预处理就实现了，同样，查询一样的思路。复杂度 $\Theta(n\log n)$。     

讲得可能有点抽象，不理解的可以在评论下问，我会尽力回答。

赛时代码（奇丑无比）：    

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300003],l[300003],r[300003],l2[300003],r2[300003];
int lft,rgt,mid,k1,k2,k3,k4,k5,k6,k7,k8,k9,ans;
int bl[8];
int mnl[300003][27],mxr[300003][27];
int bzl[300003][27][2];
int lg2[300003];
int getval1(int l,int r){
	return min(mnl[l][lg2[r-l+1]],mnl[r-(1<<lg2[r-l+1])+1][lg2[r-l+1]]);
}
int getval2(int l,int r){
	return max(mxr[l][lg2[r-l+1]],mxr[r-(1<<lg2[r-l+1])+1][lg2[r-l+1]]);
}
bool chk(){
	if(k3==0||k4==0)return false;
	return (max(r[k3],r[k4])-min(l[k3],l[k4])+1)<n;
}
void tn(int X){
	bl[1]=bzl[k1][X][0];
	bl[2]=bzl[k1][X][1];
	bl[3]=bzl[k2][X][0];
	bl[4]=bzl[k2][X][1];
	k3=k4=bl[1];
	for(int i=2;i<=4;i++){
		if(l[bl[i]]<l[k3])k3=bl[i];
		if(r[bl[i]]>r[k4])k4=bl[i];
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	//freopen("b.in","r",stdin);
	//freopen("b.out","w",stdout);
	cin>>n;
	lg2[0]=-1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i+2*n]=a[i];
	}
	for(int i=1;i<=3*n;i++){
		lg2[i]=lg2[i>>1]+1;
		l[i]=max(i-a[i],1);
		r[i]=min(i+a[i],3*n);
		mnl[i][0]=l[i];
		mxr[i][0]=r[i];
	}
	for(int i=1,j=2;j<=3*n;i++,j*=2){
		for(int u=1;u+j-1<=3*n;u++){
			mnl[u][i]=min(mnl[u][i-1],mnl[u+(j>>1)][i-1]);
			mxr[u][i]=max(mxr[u][i-1],mxr[u+(j>>1)][i-1]); 
		}
	}
	for(int i=1;i<=3*n;i++){
		k1=getval1(l[i],r[i]);
		k2=getval2(l[i],r[i]);
		lft=l[i];
		rgt=r[i];
		while(lft<rgt){
			mid=((lft+rgt)>>1);
			if(getval1(l[i],mid)==k1&&getval2(l[i],mid)==k2)rgt=mid;
			else lft=mid+1;
		}
		r2[i]=lft;
		lft=l[i];
		rgt=r2[i];
		while(lft<rgt){
			mid=((lft+rgt)>>1)+1;
			if(getval1(mid,r2[i])==k1&&getval2(mid,r2[i])==k2)lft=mid;
			else rgt=mid-1;
		}
		l2[i]=lft;
		bzl[i][0][0]=l2[i];
		bzl[i][0][1]=r2[i];
	}
	for(int i=1;i<=26;i++){
		for(int j=1;j<=3*n;j++){
			k1=bzl[j][i-1][0];
			k2=bzl[j][i-1][1];
			bl[1]=bzl[k1][i-1][0];
			bl[2]=bzl[k1][i-1][1];
			bl[3]=bzl[k2][i-1][0];
			bl[4]=bzl[k2][i-1][1];
			for(int u=1;u<=4;u++){
				if(bzl[j][i][0]==0||l[bzl[j][i][0]]>l[bl[u]])bzl[j][i][0]=bl[u];
				if(bzl[j][i][1]==0||r[bzl[j][i][1]]<r[bl[u]])bzl[j][i][1]=bl[u];
			}
		}
	}
	for(int i=n+1;i<=2*n;i++){
		if(n==1){
			puts("0");
			return 0;
		}
		if(r[i]-l[i]+1>=n){
			cout<<1<<" ";
			continue;
		}
		k1=i;
		k2=i;
		k9=26;
		ans=1;
		while(k9--){
			tn(k9);
			if(chk()){
				ans+=(1<<k9);
				k1=k3;
				k2=k4;
			}
		}
		while(1){
			tn(0);
			ans++;
			k1=k3;
			k2=k4;
			if(!chk())break;
		}
		cout<<ans<<" ";
	}
	return 0;
}
```


---

## 作者：Piwry (赞：1)

这里是尝试对（一种）单个 $\log$ 写法的可能不太严谨的解释

## 解析

考虑一个问题：有一个已影响的区间 $[l, r]$，能否找出尽量少的元素，使得这些元素 $k$ 秒后的影响范围的编号跨度和 $[l, r]$ 区间 $k$ 秒后的影响范围的编号跨度相等

事实上，我们只需找两个元素即可：一次拓展（一秒后）影响的编号最小/最大的元素 $x, y$

考虑证明；

首先不难发现，当一个元素被拓展过一次后，我们就不用考虑该元素的影响了；因为所有它能影响的元素都已被影响

对于 $k=1$，可以发现 $x, y$ 影响的范围的编号跨度和整个区间 $[l, r]$ 影响的范围的编号跨度一致

对于 $k\geq 2$，原本已在 $[l, r]$ 内的元素的影响已经不用考虑，我们只关心 $k=1$ 时（及之后）添加的新元素。不难发现，由于影响的元素是从当前位置开始的一个区间，因此 $x, y$ 在 $k=1$ 时添加的新元素是最多的；即 $[l, r]$ 的任意子集在 $k=1$ 时添加的新元素集合**都包含于** $x, y$ 在 $k=1$ 时添加的新元素集合（因为 “当前” 都至少在 $[l, r]$ 内，因此每个元素添加的新元素都是从 $l-1$ 或 $r+1$ 开始向外的一段，于是 $x, y$ 添加的新元素是最多的；注意 $[l, r]$ 内的元素在 $k\geq 2$ 后的影响都**不用考虑**了，别被绕晕了 \fad）。于是就可以拿 $x, y$ “替代” 整个区间 $[l, r]$ 在 $k\geq 2$ 后的影响情况

（证明可能不是很形式化/严谨X；但大概就是这个意思）

证明完这点后就可以用 ST 表一个 $\log$ 地搞了；剩余的部分可参考代码及注释

## CODE

```cpp
#include <cstdio>
#include <iostream>
using std::max;
using std::min;

const int MAXN =1e5+20;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

/*------------------------------Math------------------------------*/

int log_2[MAXN*3];

void pre(const int &n){
	log_2[1] =0;
	for(int i =2; i <= n; ++i)
		log_2[i] =log_2[i>>1]+1;
}

/*------------------------------ST------------------------------*/

struct st{
	int table[19][MAXN*3], val[MAXN*3];
	bool typ;
	
	inline int cmp(const int &i, const int &j){
		if(typ)
			return (val[i] > val[j]) ? i : j;
		else
			return (val[i] < val[j]) ? i : j;
	}
	inline int query(const int &l, const int &r){/*返回最大/小权的位置下标*/
		int k =log_2[r-l+1];
		return cmp(table[k][l], table[k][r-(1<<k)+1]);
	}
	
	st(const int *Val, const int &n, const bool &Type):typ(Type){
		for(int i =1; i <= n; ++i)
			val[i] =Val[i];
		for(int i =1; i <= n; ++i)
			table[0][i] =i;
		for(int k =1; k <= log_2[n]; ++k)
			for(int i =1; i <= n-(1<<k)+1; ++i)
				table[k][i] =cmp(table[k-1][i], table[k-1][i+(1<<(k-1))]);
	}
};

/*------------------------------Array------------------------------*/

int range[MAXN*3];

int l[19][MAXN*3], r[19][MAXN*3];/*2^k 秒时能到的最左/最右位置*/

/*------------------------------Main------------------------------*/

int main(){
	int n =read();
	
	if(n == 1)
		return puts("0"), 0;
	
	pre(3*n);
	for(int i =n+1; i <= n+n; ++i)
		range[i-n] =range[i] =range[i+n] =read();
	
	for(int i =1; i <= 3*n; ++i)
		l[0][i] =max(1, i-range[i]), r[0][i] =min(3*n, i+range[i]);
	st l0(l[0], 3*n, 0), r0(r[0], 3*n, 1);
	
	for(int k =1; k <= log_2[n]; ++k)
		for(int i =1; i <= 3*n; ++i){
			// pos_tol, pos_tor -> 题解中的 x, y，对于区间 [l[k-1][i], r[k-1][i]] //
			int pos_tol =l0.query(l[k-1][i], r[k-1][i]),
				pos_tor =r0.query(l[k-1][i], r[k-1][i]);
			l[k][i] =min(l[k-1][pos_tol], l[k-1][pos_tor]);
			r[k][i] =max(r[k-1][pos_tol], r[k-1][pos_tor]);
		}
	
	for(int i =n+1; i <= n+n; ++i){
		int ans =0;
		// pos_tol, pos_tor -> 同上，对于当前 ( ans 秒时 ) 影响的区间 //
		int pos_tol =i, pos_tor =i;
		for(int k =log_2[n]; k >= 0; --k){
			if(max(r[k][pos_tol], r[k][pos_tor])-min(l[k][pos_tol], l[k][pos_tor])+1 >= n)
				continue;
			ans +=1<<k;
			int tmpl =pos_tol, tmpr =pos_tor;
			pos_tol =l0.query(l[k][tmpl], r[k][tmpr]);
			pos_tor =r0.query(l[k][tmpl], r[k][tmpr]);
		}
		
		printf("%d ", ans+1);
	}
}
```

---

## 作者：yyy爱编程 (赞：0)

没题解？发一弹。

----


ST表，倍增

有$n$个人围成一圈，要传递消息。第$i$个人会在$1$个时刻内把消息传递到距离他不超过$a_i$的人。

问第$0$时刻分别只有$1,2,3,···,n$知道消息时，各需要多少时间才能把消息传递到所有人?

序列上做法：

每一时刻传递到信息的人一定是连续的，记录这段区间为$[l,r]$。

那么，下一次传递，我们就让$[l,r]$中能往左、右传递最远的两个点进行传递。

这个可以用ST表维护区间最值，然后$O(1)$单次跳。

查询时，也倍增。

时空复杂度：$O(n \log ^2 n)$。

_____

圈上做法：

将序列变成三倍长度，建ST表。

从中间开始倍增，如果每次跳完后区间长度$\geq n$则说明完全覆盖。以此倍增。

时空复杂度同序列上做法。

但是三倍的空间开不下，三分的查询是类似的，所以可以只开一倍空间，每次查询分三段。

刚好卡进$256MB$。



---

