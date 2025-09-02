# Just Arrange the Icons

## 题目描述

BerPhone X is almost ready for release with $ n $ applications being preinstalled on the phone. A category of an application characterizes a genre or a theme of this application (like "game", "business", or "education"). The categories are given as integers between $ 1 $ and $ n $ , inclusive; the $ i $ -th application has category $ c_i $ .

You can choose $ m $ — the number of screens and $ s $ — the size of each screen. You need to fit all $ n $ icons of the applications (one icon representing one application) meeting the following requirements:

- On each screen, all the icons must belong to applications of the same category (but different screens can contain icons of applications of the same category);
- Each screen must be either completely filled with icons (the number of icons on the screen is equal to $ s $ ) or almost filled with icons (the number of icons is equal to $ s-1 $ ).

Your task is to find the minimal possible number of screens $ m $ .

## 说明/提示

In the first test case of the example, all the icons can be placed on three screens of size $ 4 $ : a screen with $ 4 $ icons of the category $ 1 $ , a screen with $ 3 $ icons of the category $ 1 $ , and a screen with $ 4 $ icons of the category $ 5 $ .

## 样例 #1

### 输入

```
3
11
1 5 1 5 1 5 1 1 1 1 5
6
1 2 2 2 2 1
5
4 3 3 1 2
```

### 输出

```
3
3
4
```

# 题解

## 作者：yuzhechuan (赞：1)

复杂度并不“显然”的一道偏思维题

---

### 题解：

首先要发现对于已知的单面容量$k$和面数$p$，其可承载的合法总容量是可以定量计算的一段连贯的区间，即$[(k-1)*p,k*p]$

其次，对于已知的同种类软件数$m$，若给出$k$，其所需的$p$也是唯一的（合法的前提下）,即$p=\lfloor\frac{m-1}{k}\rfloor+1$，而是否合法的判定又可以套用上方的公式

(解释一下第2个式子：贪心的装满每一面，剩余的额外开一面。)

证明一下该判定方法的正确性：由于式子2的$p$是贪心下最小方案，因此如果超出左边界肯定是不合法的，而右边界仔细想想就会发现其实是不会存在超出的情况的，因此判断时只要判左边界就行了

现在题目给出了$m$，问$\min\{p\}$，于是我们可以枚举$k$，分别累加计算$p$并判断它是否合法

---

复杂度及证明：

复杂度$O(cnt*\min\{m\})$，其中$cnt$是种类数

最劣情况显然是所有$m$都相等，此时$m=\frac{n}{cnt}$

复杂度为$O(m*cnt)\Leftrightarrow O(\frac{n}{cnt}*cnt)\Leftrightarrow O(n)$

因此复杂度最劣情况下是$O(n)$的

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}


const int N=2e6+5;
int cnt[N],n;
vector<int> g;

int calc(int x){
	int res=0;
	for(int i=0;i<g.size();i++){
		int now=(g[i]-1)/x+1; //套用式子2
		if((x-1)*now<=g[i]) res+=now; //判定是否满足式子1（只判了左边界）
		else return INT_MAX; //不合法
	}
	return res;
}

void doit(){
	read(n);
	for(int i=1;i<=n;i++) cnt[i]=0; //清空桶
	for(int i=1,x;i<=n;i++) cnt[read(x)]++;
	g.clear();
	int mi=n;
	for(int i=1;i<=n;i++) if(cnt[i]) g.push_back(cnt[i]),mi=min(mi,cnt[i]); //记录下桶中的最少数量
	int ans=n;
	for(int i=mi+1;i>1;i--) ans=min(ans,calc(i)); //枚举单页容量，分别计算出所需面数，取个最小值
	write(ans);puts("");
}

signed main(){
	int t;
	read(t);
	while(t--) doit();
}
```

---

## 作者：gyh20 (赞：1)

可知，答案的最大值为出现次数最少的类型的个数+1，再依次判断是否可行（具体方式见代码），时间复杂度即为出现次数最少的出现次数$*$出现过的类型数，可知，这个乘积是小于等于n的。

代码：

```cpp
#include<cstdio>
#include<iostream>
#define in inline
#define re register
using namespace std;
in int read() {
	re int t=0;
	re char v=getchar();	
	while(v<'0'||v>'9'){
	v=getchar();
	}	
	while(v>='0'&&v<='9'){		
	t=(t<<3)+(t<<1)+(v^48);		
	v=getchar();	}
	return t;
}
int t,n,a[2000002],mn,p[2000002],cnt;
int main(){
	t=read();
	while(t--){
		n=read();
		mn=0x7fffffff;
		cnt=0;
		bool ia=0;
		for(re int i=1;i<=n;++i)++a[read()];
		for(re int i=1;i<=n;++i)if(a[i])mn=min(mn,a[i]),p[++cnt]=a[i],a[i]=0;int ans=0;
		++mn;
		while(1){
			ans=0;
			ia=0;
			for(re int i=1;i<=cnt;++i){
				int tmp=(p[i]-1)/mn+1;
				ans+=tmp;
				if((mn-1)*tmp>p[i]){ia=1;break;
				}
			}
			if(!ia)break;
			--mn;
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：Refined_heart (赞：0)

题目大意：求一个划分，使得划分的每一部分都属于同一类，且每一部分的物品的数量都是容量或是容量$-1$.容量指的是划分的每一部分的最大容量。

对于最大容量没有给出限制，且每一部分的最大容量相等。

$\text{Solution:}$

由于没有最大容量限制，我们很容易想到找到一个最大的容量满足条件，就是最优的解。然而这个过程要$n^2$.

考虑一下范围，不难想到，它的最大范围就是最小出现次数$+1.$那么我们的搜索范围就缩小到了这个地步。

这个时候我们可以**暴力**。

下面证明暴力复杂度：

设我们的最小出现次数为$x$.因为不存在更小的出现次数，而且要让这个最小出现次数和颜色种类数乘积最大，所以其他颜色的数量就是$\frac{n}{x}.$

两者相乘，一定是不大于$n$的。

这是一个有复杂度保证的暴力。于是我们可以愉快$AC$了。

注意的是，我们找的时候，还要判断当前的解是不是无解。即使这个范围很小，也不意味着所有颜色都可以找到一个存在解的划分。所以我们不是只要一个贪心原则选那个最小出现次数$+1$.而是要确保最正确。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n,a[2000100],cnt[2000100];
int vis[2000100],ans;
vector<int>v;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;++i)scanf("%lld",&a[i]),cnt[a[i]]++;
		for(int i=1;i<=n;++i){
			if(!vis[a[i]])v.push_back(a[i]);
			vis[a[i]]=1;
		}
		int mx=(1<<30);ans=(1<<30);
		for(int i=0;i<(int)v.size();++i)mx=min(mx,cnt[v[i]]+1);
		for(int i=1;i<=mx;++i){
			int res=0;
			for(int j=0;j<(int)v.size();++j){
				if(cnt[v[j]]%i==0)res+=cnt[v[j]]/i;
				else {
					if((cnt[v[j]]/i+cnt[v[j]]%i)<i-1){
						res=2147483647;break;
					}
					else res+=cnt[v[j]]/i+1;
				}
			}
			ans=min(ans,res);
		}
		for(int i=1;i<=n;++i)cnt[a[i]]=0,vis[a[i]]=0,a[i]=0;
		v.clear(); 
		cout<<ans<<endl;
	}
	return 0;
}
```


---

