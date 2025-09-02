# TV Subscriptions (Easy Version)

## 题目描述

### 题意简述

给定长度为 $n$ 的序列 $a$，对于 $a_i(1\leq i \leq n)$ 有 $a_i\leq k$。请你找出一段长度为 $d$ 的区间，使得这段区间所包含的不同元素的数量最小。

## 样例 #1

### 输入

```
4
5 2 2
1 2 1 2 1
9 3 3
3 3 3 2 2 2 1 1 1
4 10 4
10 8 6 4
16 9 8
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3
```

### 输出

```
2
1
4
5
```

# 题解

## 作者：Lyrella (赞：1)

# 题解：

因为 $1\leqslant n, t\leqslant 100$。

所以直接暴力枚举。

# 具体实现：

可以开个桶记录 $a_i$ 是否出现。先处理出 $1$ 到 $d$ 的个数，然后从 $d + 1$ 循环到 $n$，每次维护桶中的 $a_i$ 和 $a_{i - d}$ 是否出现，再更新 $ans$ 的最小值。

# 代码：

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 2e5 + 5, M = 1e6 + 5;
int T, n, q, b, a[N], ans, res, sum[M];
signed main()
{
//	freopen("A.in", "r", stdin);
//	freopen("A.out", "w", stdout);
	scanf("%d", &T);
	F(l, 1, T)
	{
		res = 0; memset(sum, 0, sizeof sum);
		scanf("%d %d %d", &n, &b, &q);
		F(i, 1, n)scanf("%d", &a[i]);
		F(i, 1, q)if(!sum[a[i]]++)res++;
		ans = res;
		F(i, q + 1, n)
		{
			if(!--sum[a[i - q]])res--;
			if(!sum[a[i]]++)res++;
			ans = min(ans, res);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：TachibanaKanade (赞：1)

水题。

看到数据范围 $1\le n \le 100$，直接考虑暴力枚举。

枚举的思路也很简单，以每个 $i$ 为左端点，找长度为 $d$ 的区间，开一个桶记录不同元素数量。最后取最小值即可。

时间复杂度 $O(n^2)$。可以水过。

需要注意的是右端点是 $d+i-1$ 而非 $d+i$，还有记得每次循环清空桶。

主要代码：

```cpp
int solve() {
    int n, k, d, ans = inf;
    cin >> n >> k >> d;
    for (int i = 1; i <=n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        memset(f, 0, sizeof f);
        int cnt = 0, tmp = d + i - 1;
        if(tmp == n + 1) break;
        for (int j = i; j <= tmp; j++) {
            if (f[a[j]] == false) cnt++;
            f[a[j]] = true;
        }
        ans = min(ans, cnt);
    }
    return ans;
}
```


---

## 作者：傅思维666 (赞：1)


## 题解：

#### 题目翻译：

有一个长度为$n$的数列，里面有$k$种不同的颜色（准确地说，是$1-k$的任意几种颜色），请问一个大小为$d$的滑动窗口最少能包含多少种不同的颜色。



#### 题解：

一道滑动窗口的题。因为是简单版数据都在100以内，所以我们考虑用暴力水过（正解请看我困难版的题解）。

暴力思路比较好想。就是for循环枚举区间，然后对颜色进行标记统计即可。

注意一些细节：

因为是多组数据，所以每组数据开始跑之前一定要清零。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=110;
int n,k,d,ans,tmp;
int a[maxn];
bool v[maxn];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ans=1<<30;
        scanf("%d%d%d",&n,&k,&d);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        {
            memset(v,0,sizeof(v));
            tmp=0;
            if(i+d-1==n+1)
                break;
            for(int j=i;j<=i+d-1;j++)
            {
                if(!v[a[j]])
                    tmp++;
                v[a[j]]=1;
            }
            ans=min(ans,tmp);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```



---

## 作者：Light_az (赞：0)

# 分析

考虑维护一个双指针 $l,r$，每次移动分别减去左指针的贡献并加上右指针的贡献。

然后需要特判右指针防止越界，并且记录每个数字出现的个数。

如果其中一个数减去贡献后个数为 $0$，说明数字种类减少。

如果其中一个数加上贡献后个数为 $1$，说明数字种类增加。

最后取答案最小值即可：

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,ans,t,l,r,len,T,id,sum;
ll mn=INT_MAX,mx=0,p,opt;
ll a[N],cnt[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		l=1,r=0,ans=INT_MAX,sum=0,id=1;
		F(i,1,m) cnt[i]=0;
		F(i,1,n) cin>>a[i];
		while(id+k-1<=n){//双指针,id 为左,id_k-1为右指针
			while(l<id){//移动左指针
				cnt[a[l]]--;//减去贡献
				if(cnt[a[l]]==0) sum--;//种类减少
				l++;
			}
			while(r<id+k-1){//移动右指针
				r++;
				cnt[a[r]]++;//增加贡献
				if(cnt[a[r]]==1) sum++;//种类增加
			}
			ans=min(ans,sum);//取最小值
			id++;
		}
		cout<<ans<<"\n";
	} 

	return 0;
}
```


---

## 作者：big_news (赞：0)

区间的长度是固定的，那么只需要开一个桶，维护一下在某段区间内有那些元素。

考虑从一个区间滑动到另一个区间，那么这时候区间内元素个数是可以 O(1) 维护的，然后就没什么了。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

const int CN = 1e6+6;
const int INF = 0x3f3f3f3f;

int read(){
    int s=0,ne=1; char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') ne=-1;
    for(;c>='0'&&c<='9';c=getchar()) s=(s<<1)+(s<<3)+c-'0';
    return s*ne;
}

int t,n,k,d,a[CN];
int tot[CN];

int main()
{
    t = read();
    while(t--){
        memset(tot,0,sizeof(tot));
        
        n = read(); k = read(); d = read();
        for(int i=1;i<=n;i++) a[i] = read();
        
        int ans = INF,cnt = 0;
        for(int i=1;i<d;i++) {if(!tot[ a[i] ]) cnt++; tot[ a[i] ]++;}
        for(int i=d;i<=n;i++){
            if(!tot[ a[i] ]) cnt++; tot[ a[i] ]++;
            tot[ a[i-d] ]--; if(!tot[ a[i-d] ]) cnt--;
            ans = min(ans, cnt); 
        }
        
        printf("%d\n",ans);
    }
    
    return 0;
}
```

---

