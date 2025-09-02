# [ICPC 2022 Jinan R] Quick Sort

## 题目描述

给定一个长度为 $n$ 的排列 $A$。现使用如下伪代码对 $A$ 进行排序：

```
procedure QUICKSORT(A,lo,hi)
    if lo>=0 and hi>=0 and lo<hi then
    	p=PARTITION(A,lo,hi)
        QUICKSORT(A,lo,p)
        QUICKSORT(A,p+1,hi)
    end if
end procedure
procedure PARTITION(A,lo,hi)
    pivot=A[floor((hi+lo)/2)]
    i=lo-1
    j=hi+1
    while True do
        repeat
            i=i+1
        until A[i]>=pivot
        repeat
            j=j-1
        until A[j]<=pivot
        if i>=j then
            return j
        end if
        Swap A[i] with A[j]
    end while
end procedure
```

试计算：调用 `QUICKSORT(A,1,n)` 函数过程中，`Swap` 操作执行了多少次。

## 样例 #1

### 输入

```
3
3
3 2 1
5
2 4 5 3 1
10
7 2 4 6 1 9 10 8 5 3```

### 输出

```
1
4
7```

# 题解

## 作者：Diaоsi (赞：2)

[Quick Sort](https://www.luogu.com.cn/problem/P9673)

感谢 @[_l_l_](https://www.luogu.com.cn/user/109114) 提供的证明。

首先证明快速排序的交换次数上界是 $\mathcal{O}(n\log n)$ 的，记 $T\left(n\right)$ 表示对长度为 $n$ 的序列进行快速排序的交换次数，可以得到如下递推式：

$$
T\left(n\right)=T\left(a\right)+T\left(n-a\right)+\min\left\{a,n-a\right\}
$$

根据对称性，不妨令 $a\leq n\,/\,2$，考虑这样的感性证明，将 $T\left(n-a\right)$ 继续拆分，最终会形成大于等于 $2$ 个小于等于 $n\,/\,2$ 的部分并且花费了 $\mathcal{O}(n)$ 的交换次数，由于这样的递归至多进行 $\mathcal{O}(\log n)$ 层，所以 $T\left(n\right)=\mathcal{O}(n\log n)$。

有了这个结论这题就能直接做了，由于快排退化的原因，我们不能像伪代码里面那样用双指针找需要交换的元素。注意到确定主元（下标记为 $p$）位置之后我们只需要逐个找到 $p$ 第一个大于等于 $a_p$ 的值和 $p$ 后第一个小于等于 $a_p$ 的值，只需要维护区间 $\max/\min$ 值就能进行二分了。

由于要支持修改，所以可以在线段树上进行二分。

根据上面的结论，交换次数至多 $\mathcal{O}(n\log n)$，单次线段树上二分的复杂度为 $\mathcal{O}(\log n)$，故总时间复杂度为 $\mathcal{O}\big(n\log^2 n\big)$。

Code:
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=500010,M=5000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,n,ans,a[N];
struct SegmentTree{
	int l,r;
	int dat,tag;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define dat(x) tree[x].dat
	#define tag(x) tree[x].tag
}tree[N<<2];
void pushup(int x){
	dat(x)=max(dat(x<<1),dat(x<<1|1));
	tag(x)=min(tag(x<<1),tag(x<<1|1));
}
void build(int x,int l,int r){
	l(x)=l,r(x)=r;dat(x)=tag(x)=0;
	if(l==r){dat(x)=tag(x)=a[l];return;}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void insert(int x,int pos,int val){
	int l=l(x),r=r(x);
	if(l==r){dat(x)=tag(x)=val;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)insert(x<<1,pos,val);
	if(pos>mid)insert(x<<1|1,pos,val);
	pushup(x);
}
int query1(int x,int L,int R,int val){
	int l=l(x),r=r(x);
	if(dat(x)<val)return 0;
	if(l==r)return l;
	if(L<=l&&r<=R){
		int res=query1(x<<1,L,R,val);
		if(res)return res;
		return query1(x<<1|1,L,R,val);
	}
	if(L<=r(x<<1)){
		int res=query1(x<<1,L,R,val);
		if(res)return res;
	}
	return query1(x<<1|1,L,R,val);
}
int	query2(int x,int L,int R,int val){
	int l=l(x),r=r(x);
	if(tag(x)>val)return 0;
	if(l==r)return l;
	if(L<=l&&r<=R){
		int res=query2(x<<1|1,L,R,val);
		if(res)return res;
		return query2(x<<1,L,R,val);
	}
	if(l(x<<1|1)<=R){
		int res=query2(x<<1|1,L,R,val);
		if(res)return res;
	}
	return query2(x<<1,L,R,val);
}
int partition(int l,int r){
	int mid=(l+r)>>1,p=a[mid];
	int i=l-1,j=r+1;
	while(1){
		i=query1(1,i+1,n,p);
		j=query2(1,1,j-1,p);
		if(i>=j)return j;
		insert(1,i,a[j]);
		insert(1,j,a[i]);
		swap(a[i],a[j]);
		ans++;
	}
}
void qsort(int l,int r){
	if(l<0||r<0||l>=r)return;
	int p=partition(l,r);
	qsort(l,p);
	qsort(p+1,r);
}
void solve(){
	scanf("%d",&n);ans=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	qsort(1,n);
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：无名之雾 (赞：1)

被可爱出题人搬到了省选模拟赛中作为 T1 来当作脑筋急转弯，成功签到，写题解纪念之。

### solution

首先先将题面里的伪代码实现。

随机几组数据后，仔细观察。

我们不难发现，这个 `sort` 的交换次数并不会太多。最多只会交换 $O(n \log n)$ 次。

证明如下：

我们令 $F(n)$ 表示交换次数，那么有：

$$F(n)=F(x)+F(n-x)+\min(x,n-x)$$ 

其中 $x$ 表示两段的大小。

直接模拟显然会被卡到 $O(n^2)$。

思考如何降低时间复杂度，发现瓶颈在于寻找要进行交换的 $l$ 和 $r$。

那么接下来只要快速模拟这个交换的过程，保证分治的时候只和短的那边复杂度相关即可。

一个比较暴力也好想的做法就是用线段树维护区间最值，快速找到下一个元素。

时间复杂度 $O(n \log^2 n)$。


当然也有启发式合并做法可以做到 $\dfrac{n \log^2 n}{\log \log n}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void out(int x){
    if(x==0){putchar('0');return;}
    int len=0,k1=x,c[10005];
    if(k1<0)k1=-k1,putchar('-');
    while(k1)c[len++]=k1%10+'0',k1/=10;
    while(len--)putchar(c[len]);
}
const int N=5e5+5;
int a[N],n,cnt;
struct SGT{
	int mx[N<<2],mn[N<<2];
	int ls(int p){return p<<1;}
	int rs(int p){return p<<1|1;}
	void push_up(int p){
        mx[p]=max(mx[ls(p)],mx[rs(p)]);
        mn[p]=min(mn[ls(p)],mn[rs(p)]);
    }
	void build(int p,int pl,int pr){
		if(pl==pr){mn[p]=mx[p]=a[pl];return;}
		int mid=pl+pr>>1;
		build(ls(p),pl,mid);
		build(rs(p),mid+1,pr);
		push_up(p);
	}
	void upd(int pos,int p,int pl,int pr,int d){
		if(pl==pr){mx[p]=mn[p]=d;return;}
		int mid=pl+pr>>1;
		if(pos<=mid)upd(pos,ls(p),pl,mid,d);
		else upd(pos,rs(p),mid+1,pr,d);
		push_up(p);
	}
    int queryl(int pivot,int p,int pl,int pr,bool flag){
        if(pl==pr)return pl;
        int mid=pl+pr>>1;
        if((!flag&&mx[ls(p)]>=pivot)||flag&&mx[ls(p)]>pivot)return queryl(pivot,ls(p),pl,mid,flag);
        else return queryl(pivot,rs(p),mid+1,pr,flag);
    }
    int queryr(int pivot,int p,int pl,int pr,bool flag){
        if(pl==pr)return pl;
        int mid=pl+pr>>1;
        if((!flag&&mn[rs(p)]<=pivot)||flag&&mn[rs(p)]<pivot)return queryr(pivot,rs(p),mid+1,pr,flag);
        else return queryr(pivot,ls(p),pl,mid,flag);
    }
}sgt;
struct SORT{
    int partition(int l,int r){
        int pivot=a[l+r>>1];
        bool flagl=0,flagr=0;
        while(1){
            l=sgt.queryl(pivot,1,1,n,flagl);
            r=sgt.queryr(pivot,1,1,n,flagr);
            // cout<<l<<" "<<r<<"\n";
            // cout<<i<<" "<<j<<"\n";
            // cout<<a[i]<<" "<<a[j]<<"\n";
            if(l>=r)return r;
            swap(a[l],a[r]);cnt++;
            if(a[l]==pivot)flagl=1;
            if(a[r]==pivot)flagr=1;
            sgt.upd(l,1,1,n,a[l]);
            sgt.upd(r,1,1,n,a[r]);
            // cout<<"SGT: \n";
            // for(int i=1;i<=n;i++)cout<<sgt.mx[i]<<" "<<sgt.mn[i]<<"\n";
            // if(cnt>5)exit(0);
        }
    }
    void q_sort(int l,int r){
        if(l>=1&&r>=1&&l<r){
            int p=partition(l,r);
            q_sort(l,p),q_sort(p+1,r);
        }
    }
}msort;
signed main(){
    // freopen("sugoi.in","r",stdin);
    // freopen("sugoi.out","w",stdout);
    int t=read();
    while(t--){
        n=read();cnt=0;
        for(int i=1;i<=n;i++)a[i]=read();
        sgt.build(1,1,n);
        msort.q_sort(1,n);cout<<cnt<<"\n";
    }
    return 0;
}	
```

---

