# Median on Segments (General Case Edition)

## 题目描述

#### 题目翻译

给定长度为 $n$ 的序列（$1 \le n \le 2 \times 10^5$），求中位数为 $m$ 的子段个数（子段长度为偶数时，取其 $\dfrac{k}{2}$ 项，$k$ 为子段长度）。

## 样例 #1

### 输入

```
5 4
1 4 5 60 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 1
1 1 1
```

### 输出

```
6
```

## 样例 #3

### 输入

```
15 2
1 2 3 1 2 3 1 2 3 1 2 3 1 2 3
```

### 输出

```
97
```

# 题解

## 作者：hwx12233 (赞：12)

只算一个数为中位数不好做

我们想到 m为中位数的方案数=大于等于m为中位数的方案数-大于m为中位数的方案数

而判断一个序列是否是大于等于m为中位数是简单

当且仅当大于等于m的数大于小于m的数

由于我们不需要知道大于等于或小于m的数的数量

所以可以直接做差

用map存（大于等于m-小于m）方案数

维护前缀和时有点小技巧

具体看代码吧

```cpp
const int N=2e5+10;
map<int,int>mp;
int n,m,ans,cur,pre,a[N];
inline int work(int k){
	mp.clear();cur=n,pre=0,ans=0;
	for(int i=1;i<=n;i++){
		mp[cur]++;
		if(a[i]>=k)pre+=mp[cur],cur++;
		else cur--,pre-=mp[cur];
        	//小技巧 -时退掉 +时加上
		ans+=pre;
	}
	return ans;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	cout<<work(m)-work(m+1);
}
```


---

## 作者：SoyTony (赞：0)

建议先移步 [E1](https://www.luogu.com.cn/problem/CF1005E1)。

由上一问我们得到了推式子开 map 动态维护的思路，看看本题有什么不同。不同之处在于本题是一个序列，即不保证无重复，那么按照上一提的做法，会出现存在多个 $m$ 的子段被多次计算，去重也不好去。

那么以 $m$ 为中位数的子段数，其实是以大于等于 $m$ 为中位数的子段数减去以大于等于 $m+1$ 为中位数的子段数，发现两个要求的量“句式”相同，来看看怎么求。

上一题讨论了子段长奇偶，本题无需，发现以大于等于 $m$ 为中位数的子段，大于等于 $m$ 的个数一定大于小于 $m$ 的个数。奇数情况非常好理解，毕竟最劣的情况都差 $1$，而偶数情况中由于中位数定义成靠左的，也就是说最劣情况会差 $2$，结论成立。

依旧是求 $cnt1,cnt2$，分别维护上述信息。

对于字段 $[l,r]$，有：
$$cnt2(r)-cnt2(l-1)>cnt1(r)-cnt1(l-1)$$
即：
$$cnt2(r)-cnt1(r)>cnt2(l-1)-cnt1(l-1)$$
这样就是求当前 $[-n,cnt2(r)-cnt1(r)-1]$ 的个数，区间求前缀和需要树状数组。不要忘了有负数情况，要开成 $2n+1$，以及 $0$ 上数据初始为 $1$。

```cpp
int n,m;
int a[maxn];
int cnt1[maxn],cnt2[maxn];
struct BianryTree{
    ll siz[maxn<<1];
    inline int lowbit(int x){return x&-x;}
    inline void update(int x){
        while(x<=2*n+1){
            ++siz[x];
            x+=lowbit(x);
        }
    }
    inline ll query(int x){
        ll res=0;
        while(x){
            res+=siz[x];
            x-=lowbit(x);
        }
        return res;
    }
}B;
inline ll solve(int x){
    cnt1[0]=cnt2[0]=0;
    memset(B.siz,0,sizeof(B.siz));
    for(int i=1;i<=n;++i){
        cnt1[i]=cnt1[i-1],cnt2[i]=cnt2[i-1];
        if(a[i]<x) ++cnt1[i];
        else ++cnt2[i];
    }
    B.update(n+1);//0
    ll res=0;
    for(int i=1;i<=n;++i){
        int tmp=cnt2[i]-cnt1[i];
        res+=B.query(tmp+n);
        B.update(tmp+n+1);
    }
    return res;
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;++i) a[i]=read();
    printf("%lld\n",solve(m)-solve(m+1));
    return 0;
}
```

---

