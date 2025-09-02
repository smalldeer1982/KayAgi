# [NOISG 2021 Finals] Tiles

## 题目背景

Eustace the Sheep 刚搬进新家，决定翻新他的浴室，因为他实在受不了它单调的内部装饰。目前，浴室的地板是一个 $3 \times N$ 的黑白方格网格。

他有大量相同的 $1 \times 2$ 长方形瓷砖。为了保持浴室的美观，瓷砖可以旋转，但必须平行于墙壁摆放。此外，粘贴瓷砖的胶水不能涂在黑色方格上，因此瓷砖只能放在白色方格上。


## 题目描述

Eustace 想知道，在从第 $a$ 列到第 $b$ 列的区域中，可以形成多少种不同的瓷砖铺设方案（可以不铺瓷砖）。如果两种方案中，某两个方格是否共用一块瓷砖不同，则认为两种方案不同。

在计算铺设方案的同时，Eustace 注意到由于霉菌等问题，部分方格可能会变色（从黑变白，或从白变黑）。

请帮助 Eustace 在不断变化的地板颜色中回答以下问题：
1. 翻转某个方格的颜色。
2. 查询特定区域内可能的瓷砖铺设方案数。

输出结果需要对 $10^9 + 7$ 取模。

## 说明/提示

【样例解释】

- 对于样例 $1$，在第一次查询时，可以形成 $11$ 种铺设方案。  
- 在更新操作后，某些区域的方格颜色发生变化，导致后续查询结果也发生改变。

【数据范围】

- $1 \leq N, Q \leq 30000$
- $1 \leq x \leq 3$
- $1 \leq y \leq N$
- $1 \leq a \leq b \leq N$

| 子任务编号 | 分值 | 额外限制条件                |
| :--------: | :--: | :------------------------: |
| $1$        | $17$ | $1 \leq N, Q \leq 8$      |
| $2$        | $23$ | 不存在黑色方格            |
| $3$        | $26$ | $1 \leq N, Q \leq 7000$   |
| $4$        | $34$ | 无额外限制                |

## 样例 #1

### 输入

```
4 5
.x.x
xx..
...x
2 1 4
2 3 3
1 2 3
2 1 4
2 3 3```

### 输出

```
11
3
3
1```

## 样例 #2

### 输入

```
2 1
..
..
xx
2 1 2```

### 输出

```
7```

## 样例 #3

### 输入

```
14 2
..............
..............
..............
2 2 11
2 1 14```

### 输出

```
47177097
254767228```

# 题解

## 作者：ax_by_c (赞：0)

令 $m$ 表示行数，本题中 $m=3$。

思考暴力怎么做，考虑 DP。

设 $f_{i,S}$ 表示铺完前 $i$ 列内部的瓷砖且第 $i$ 列已经不能铺设的位置集合为 $S$ 的方案数。

转移枚举横向瓷砖铺设情况与下一列纵向瓷砖铺设情况即可，单次时间复杂度 $O(n2^m)$。

显然转移只和每一列的黑白情况有关，于是考虑 ddp，预处理每一种黑白情况对应的转移矩阵即可。

时间复杂度 $O(8^m(n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=1e9+7;
const int N=3e4+5;
const int S=8;
struct matr{
	int n,m,a[S][S];
	void clr(){
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=0;
	}
}ms[S],ss;
matr __c;
matr operator * (const matr &a,const matr &b){
	__c.n=a.n,__c.m=b.m,__c.clr();
	for(int i=0;i<a.n;i++)
	for(int j=0;j<a.m;j++)
	for(int k=0;k<b.m;k++)__c.a[i][k]=(__c.a[i][k]+(ll)a.a[i][j]*b.a[j][k])%mod;
	return __c;
}
struct seg{
	matr tr[N*4];
	void pu(int u){
		tr[u]=tr[u<<1]*tr[u<<1|1];
	}
	void upd(int u,int l,int r,int p,int v){
		if(l==r){
			tr[u]=ms[v];
			return ;
		}
		int mid=l+((r-l)>>1);
		if(p<=mid)upd(u<<1,l,mid,p,v);
		else upd(u<<1|1,mid+1,r,p,v);
		pu(u);
	}
	matr Q(int u,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return tr[u];
		int mid=l+((r-l)>>1);
		if(qr<=mid)return Q(u<<1,l,mid,ql,qr);
		if(mid+1<=ql)return Q(u<<1|1,mid+1,r,ql,qr);
		return Q(u<<1,l,mid,ql,qr)*Q(u<<1|1,mid+1,r,ql,qr);
	}
}tr;
int n,q,a[N];
char s[5][N];
void main(){
	for(int s=0;s<S;s++){
		ms[s].n=ms[s].m=S,ms[s].clr();
		for(int i=0;i<S;i++){
			for(int j=0;j<S;j++){
				if((j&(i^(S-1)))==j&&(j&s)==0){
					int x=j|s;
					ms[s].a[i][x]++;
					if(!(x&3))ms[s].a[i][x|3]++;
					if(!(x&6))ms[s].a[i][x|6]++;
				}
			}
		}
	}
	scanf("%d %d %s %s %s",&n,&q,s[1]+1,s[2]+1,s[3]+1);
	for(int i=1;i<=n;i++)a[i]=((s[3][i]=='x')<<2)|((s[2][i]=='x')<<1)|(s[1][i]=='x');
	for(int i=1;i<=n;i++)tr.upd(1,1,n,i,a[i]);
	for(int i=1,op,x,y;i<=q;i++){
		scanf("%d %d %d",&op,&x,&y);
		if(op==1)a[y]^=1<<(x-1),tr.upd(1,1,n,y,a[y]);
		if(op==2){
			ss.n=1,ss.m=S,ss.clr();
			ss.a[0][S-1]++;
			ss=ss*tr.Q(1,1,n,x,y);
			int ans=0;
			for(int j=0;j<S;j++)ans=(ans+ss.a[0][j])%mod;
			printf("%d\n",ans);
		}
	}
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：qnqfff (赞：0)

纯恶心人的题。

### 思路

考虑暴力 dp，设 $dp_{i,S}$ 表示转移到第 $i$ 列，当前这一列的状态为 $S$，$1$ 表示有瓷砖，的方案数，转移时直接大力分讨。

$S=0$ 上一行所有情况都可以转移到。

$S=1,S=2,S=4,S=5$ 上一行对应位置必须为空。

$S=3,S=6$ 可以和上一行对应，也可以单独放。

$S=7$ 可以三行都和上一行对应，第一行和第三行可以分别和上一行对应，剩下两行可以放一个竖着的瓷砖。

容易发现可以 ddp，然后做完了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod=1e9+7;
using namespace std;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,a[30010];
struct Matrix{
	int a[8][8];
	int*operator[](int x){return a[x];}
	Matrix(){memset(a,0,sizeof(a));}
	Matrix operator*(Matrix b){Matrix res;for(int i=0;i<8;i++) for(int j=0;j<8;j++) for(int k=0;k<8;k++) (res[i][j]+=a[i][k]*b[k][j]%mod)%=mod;return res;}
};
struct seg{int l,r;Matrix x;}t[120010];
#define lson now<<1
#define rson now<<1|1
Matrix get(int x){
	Matrix res;if(x==n) return res;
	for(int i=0;i<8;i++) res[i][0]=1;
	if(!(a[x+1]&1)&&!(a[x]&1)) res[0][1]=res[2][1]=res[4][1]=res[6][1]=1;
	if(!(a[x+1]&2)&&!(a[x]&2)) res[0][2]=res[1][2]=res[4][2]=res[5][2]=1;
	if(!(a[x+1]&3)){
		for(int i=0;i<8;i++) res[i][3]=1;
		if(!(a[x]&3)) res[0][3]=res[4][3]=2;
	}if(!(a[x+1]&4)&&!(a[x]&4)) res[0][4]=res[1][4]=res[2][4]=res[3][4]=1;
	if(!(a[x+1]&5)&&!(a[x]&5)) res[0][5]=res[2][5]=1;
	if(!(a[x+1]&6)){
		for(int i=0;i<8;i++) res[i][6]=1;
		if(!(a[x]&6)) res[0][6]=res[1][6]=2;
	}if(!(a[x+1]&7)){
		if(!(a[x]&7)) res[0][7]++;
		if(!(a[x]&1)) res[0][7]++,res[2][7]++,res[4][7]++,res[6][7]++;
		if(!(a[x]&4)) res[0][7]++,res[1][7]++,res[2][7]++,res[3][7]++;
	}return res;
}
void build(int now,int l,int r){
	t[now]={l,r};if(l==r){t[now].x=get(l);return ;}
	int mid=(l+r)>>1;build(lson,l,mid);build(rson,mid+1,r);t[now].x=t[lson].x*t[rson].x;
}
void modify(int now,int x){
	if(t[now].l==t[now].r){t[now].x=get(x);return ;}
	int mid=(t[now].l+t[now].r)>>1;if(x<=mid) modify(lson,x);else modify(rson,x);t[now].x=t[lson].x*t[rson].x;
}
Matrix query(int now,int l,int r){
	if(l<=t[now].l&&t[now].r<=r) return t[now].x;
	int mid=(t[now].l+t[now].r)>>1;if(r<=mid) return query(lson,l,r);if(mid<l) return query(rson,l,r);return query(lson,l,r)*query(rson,l,r);
}
signed main(){
	n=read();m=read();for(int i=1;i<=3;i++){string s;cin>>s;for(int j=1;j<=n;j++) if(s[j-1]=='x') a[j]|=1<<i-1;}build(1,1,n);
	while(m--){
		int opt=read(),x=read(),y=read();
		if(!(opt^1)){a[y]^=1<<x-1;modify(1,y);if(y^1) modify(1,y-1);}
		else{
			Matrix res;res[0][0]=1;if(!(a[x]&3)) res[0][3]=1;if(!(a[x]&6)) res[0][6]=1;
			if(x<y) res=res*query(1,x,y-1);int sum=0;for(int i=0;i<8;i++) (sum+=res[0][i])%=mod;cout<<sum<<'\n';
		}
	}
	return 0;
}
```

---

