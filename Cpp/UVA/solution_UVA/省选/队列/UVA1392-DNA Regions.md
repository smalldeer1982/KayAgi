# DNA Regions

## 题目描述

## 题面
给定两个长度为 $n$ 的字符串 $A$ 和 $B$，满足 $A$ 和 $B$ 都只由大写字母 A、C、G、T 组成。

求一个长度最长的闭区间 $[L,R]$，满足对于 $i \in [L,R]$，有不超过 $p \%$ 的 $i$ 满足 $A_i \neq B_i$。

## 说明/提示

$1 \le n \le 1.5 \times 10^5$，$1 \le p \le 99$。

# 题解

## 作者：jiangminghong (赞：2)

对于区间 [j+1,i][j+1,i] ，

必须满足：(sum[i]−sum[j])/(i−j)≤P/100才符合题意;

即：

sum[j]∗100−j∗p≥sum[i]∗100−i∗p

也就是说，我们要找到一对满足这个式子的 (i,j) 使得 i−j 最大

可以用单调队列，也可以直接排序，不过单调队列更优秀

我们针对每一个位置记一个 k（num）=sum[j]∗100−j∗p

按照 k（num），将所有的位置的标号排序，这样我们就能保证所有的 S 有序

从头到尾枚举，如果当前枚举到的这一位的原位置大于当前记录的最小位置，则更新答案，

如果当前枚举到的这一位的原位置小于当前记录的最小位置，则更新最小位置

时间复杂度：排序，O(nlogn)，统计答案，O(n)

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
struct A
{
    int id,num;
}k[150001];
int sum[150001],n,p;
char s1[150001],s2[150001];
int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}
bool cmp(const A &a,const A &b)
{
    if(a.num==b.num)
        return a.id<b.id;
    return a.num>b.num;
}
int main()
{
    while(scanf("%d%d",&n,&p)!=EOF&&n!=0&&p!=0)
    {
        int cnt=0;
        memset(k,0,sizeof(k));
        scanf("%s%s",s1+1,s2+1);
        for(int i=1;i<=n;i++)
        {
            if(s1[i]!=s2[i])
                cnt++;	
            k[i].num=cnt*100-i*p;
            k[i].id=i;
        }
        k[0].id=0;
        k[0].num=0;
        sort(k,k+n+1,cmp);
        int idx=k[0].id,ans=0;
        for(int i=1;i<=n;i++)
        {
            if(k[i].id<idx)
                idx=k[i].id;
            else
                ans=max(ans,k[i].id-idx);
        }
        if(ans==0)
            printf("No solution.\n");
        else
            printf("%d\n",ans);
    } 
} 
```

---

## 作者：ivyjiao (赞：0)

因为多测不清空 WA 一堆发，被羞辱了，输。

设 $s_i=\sum_{j=i}^i [a_j\neq b_j]$，则当 $\dfrac{s_i-s_j}{i-j}\geq \dfrac{p}{100}$ 时合法。

得到：$100\times \dfrac{s_i-s_j}{i-j}\geq p$。

再化简，得到：$s_j\times 100-j\times p\geq s_i\times 100-i\times p$。

我们要找到一对满足这个式子的 $(i,j)$ 使得 $i-j$ 最大。

这个好办，记下来 $s_i\times 100-i\times p$ 排序就行。

注意多测清空。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+1;
int n,p,cnt,mi,ans;
char a[N],b[N];
PII f[N];
bool cmp(PII x,PII y){
    if(x.fi==y.fi) return x.se<y.se;
    return x.fi>y.fi;
}
signed main(){
	while(cin>>n&&n){
        cnt=0;
        cin>>p;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        for(int i=1;i<=n;i++){
            if(a[i]!=b[i]) cnt++;
            f[i]={cnt*100-i*p,i};
        }
        f[n+1]={0,0};
        sort(f+1,f+2+n,cmp);
        ans=0,mi=f[1].se;
        for(int i=2;i<=n+1;i++){
            if(f[i].se<mi) mi=f[i].se;
            else ans=max(ans,f[i].se-mi);
        }
        if(!ans) cout<<"No solution."<<endl;
        else cout<<ans<<endl;
	}
}
```

---

## 作者：U•ェ•*U (赞：0)

### [我的CSDN原文地址*（转载请标明！）](https://lsm2024.blog.csdn.net/article/details/134836984)
## 分析
**先求数组的前缀和，求出满足 $ ( sum[ j ] - sum[ i ] ) \div ( j - 1 ) \le p $ 的最小 $ i $ ，公式可以变形得到 $ sum[ i ] + pi $ ，所以生成一个新的数组 $ f[ i ] = sum[ i ] \times 100 - p \times 100 \times i $ ，对于每一个 $ j $ ，找出 $f[ i ] \ge f[ j ] $ 的最小 $ i $ 。 $ vp $ 一定要再填入一个 $ 0 $ ，否则有些例子过不去。**
## 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=150005;
struct Point {
	int v,r;
	Point(int v=0,int r=0):v(v),r(r) {}
	bool operator < (const Point &rhs) const {
		return v<rhs.v;
	}
};
int n,p,diff[maxn],s[maxn],f[maxn];
char a[maxn],b[maxn];
vector<Point> vp;
int main(void) {
	while(scanf("%d%d",&n,&p)==2 && n) {
		vp.clear();
		scanf("%s",a+1);
		scanf("%s",b+1);
		for(int i=1; i<=n; ++i) {
			if(a[i]!=b[i]) diff[i]=100;
			else diff[i]=0;
			s[i]=diff[i]+s[i-1];
			f[i]=s[i]-p*i;
		}
		int ans=0;
		vp.push_back(Point(0,0));
		for(int j=1; j<=n; ++j) {
			if(f[j]>vp.back().v) {
				vp.push_back(Point(f[j],j));
			}
			auto it=lower_bound(vp.begin(),vp.end(),Point(f[j],0));
			ans=max(ans,j-max(0,it->r));
		}
		if(ans) printf("%d\n",ans);
		else printf("No solution.\n");
	}
	return 0;
}

```

---

