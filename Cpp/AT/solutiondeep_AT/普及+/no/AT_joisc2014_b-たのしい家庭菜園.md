# 题目信息

# たのしい家庭菜園

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_b

# AI分析结果

### 题目翻译

**题目名称**: 快乐的家庭菜园

**题目描述**:  
给定一个序列，每次可以交换相邻的两个元素，要求通过最少的交换次数使得序列变成一个先非递减再非递增的序列（即单峰序列）。

### 算法分类
贪心、树状数组、离散化

### 题解分析与结论

#### 综合分析
本题的核心是通过交换相邻元素，使得序列最终形成一个单峰序列，且交换次数最少。多个题解都提到了使用贪心策略结合树状数组来求解逆序对，从而计算最小交换次数。主要的思路是：

1. **贪心策略**：从最小的元素开始，每次选择将其移动到序列的最左端或最右端，选择移动次数较少的一边。
2. **树状数组**：用于高效计算每个元素左边或右边比它大的元素个数，从而决定移动方向。
3. **离散化**：由于元素值可能较大，使用离散化将元素值映射到较小的范围内，方便树状数组的处理。

#### 最优关键思路
1. **贪心选择移动方向**：对于每个元素，计算其左边和右边比它大的元素个数，选择移动次数较少的一边。
2. **树状数组优化**：通过树状数组高效计算逆序对，避免暴力枚举。
3. **离散化处理**：将元素值映射到较小的范围，减少树状数组的空间和时间复杂度。

#### 可拓展之处
1. **类似问题**：可以通过类似的贪心策略和树状数组处理其他需要最小交换次数的问题，如将序列排序、构造特定形状的序列等。
2. **其他数据结构**：除了树状数组，还可以使用线段树或其他高效的数据结构来计算逆序对。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)
3. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)

### 个人心得
1. **调试经历**：在处理相同元素时，需要注意它们的移动顺序，避免重复计算或遗漏。
2. **顿悟感想**：通过贪心策略和树状数组的结合，可以高效解决看似复杂的问题，关键在于如何将问题转化为已知的模型。

### 精选题解

#### 题解1: 是个汉子 (5星)
**关键亮点**: 清晰的贪心策略与树状数组结合，代码简洁高效。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=300010;
ll ans;
int n,l,r,c[N],h[N],p[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline int lowbit(int x){
    return x&-x;
}

inline void update(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i))
        c[i]+=v;
}

inline int query(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i))
        res+=c[i];
    return res;
}

inline bool cmp(int a,int b){
    return h[a]>h[b];
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        h[i]=read(),p[i]=i;
    sort(p+1,p+n+1,cmp);
    for(int i=1,j;i<=n;){
        for(j=i;j<=n;j++){
            int k=query(p[j]); ans+=min(k,i-1-k);   
            if(h[p[j+1]]!=h[p[j]]) break;
        }
        for(;i<=j;i++) update(p[i],1);
    }
    printf("%lld\n",ans);
    return 0;
}
```

#### 题解2: Poncirus (4星)
**关键亮点**: 详细的思路解释与树状数组的实现，适合初学者理解。
```cpp
#include<cstdio>
#include<algorithm>
#define int long long
const int maxn=3e5+5;
const int LEN=(1<<20);
int n,a[maxn];
int ans1,ans2,ans;
int Bit[2][maxn],Lsh[maxn];
inline int Lowbit(int x){return x & (-x);}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void Update(int k,int x,int typ){
	for(int i=k;i<=n;i+=Lowbit(i))
		Bit[typ][i]+=x; 
	return; 
}
inline int Sum(int k,int typ){
	int ans=0;
	for(int i=k;i;i-=Lowbit(i))
		ans+=Bit[typ][i];
	return ans;
}
inline int nec(){
    static char buf[LEN],*p=buf,*e=buf;
    if(p==e){
        if((e=buf+fread(buf,1,LEN,stdin))==buf)return EOF;
        p=buf;
    }
    return *p++;
}
inline bool read(int&x){
    static char neg=0,c=nec();
    neg=0,x=0;
    while((c<'0'||c>'9')&&c!='-'){
        if(c==EOF)return 0;
        c=nec();
    }
    if(c=='-'){
        neg=1;
        c=nec();
    }
    do{x=x*10+c-'0';}while((c=nec())>='0');
    if(neg)x=-x;
    return 1;
}
signed main(){
	read(n);
	for(int i=1;i<=n;++i){
		read(a[i]);
		Lsh[i]=a[i];
	}
	std::sort(Lsh+1,Lsh+1+n);
	int cnt=std::unique(Lsh+1,Lsh+1+n)-Lsh-1;
	for(int i=1;i<=n;++i){
		a[i]=std::lower_bound(Lsh+1,Lsh+cnt+1,a[i])-Lsh;
		Update(a[i],1,1);
	}
	for(int i=1;i<=n;++i){
		Update(a[i],-1,1);
		ans1=n-i-Sum(a[i],1);
        Update(a[i],1,0);
        ans2=i-Sum(a[i],0);
		ans+=min(ans1,ans2);
	}
	printf("%lld\n",ans);
	return 0;
}
```

#### 题解3: _zhy (4星)
**关键亮点**: 详细的思路解释与树状数组的实现，适合初学者理解。
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define int long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 300005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
int n,ans,c[N],h[N],p[N];
bool cmp(int x,int y){
	return h[x]>h[y];
}
int lowbit(int x){
	return x&(-x);
}
void update(int x,int v){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=v;
	}
}
int query(int x){
	int sum=0;
	for(int i=x;i;i-=lowbit(i)){
		sum=sum+c[i];
	}
	return sum;
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(h[i]);
		p[i]=i;
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1,j;i<=n;){
		for(j=i;j<=n;j++){
			int k=query(p[j]);
			ans=ans+min(k,i-1-k);
			if(h[p[j+1]]!=h[p[j]]){
				break;
			}
		}
		for(;i<=j;i++){
			update(p[i],1);
		}
	}
	write(ans);
	putchar('\n');
    return 0;
}
```

---
处理用时：65.73秒