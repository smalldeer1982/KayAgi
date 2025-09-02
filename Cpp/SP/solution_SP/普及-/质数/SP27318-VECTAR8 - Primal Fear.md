# VECTAR8 - Primal Fear

## 题目描述

Changu 和 Mangu 对质数感到害怕，但他们并不是害怕所有的质数。他们只畏惧一种特殊的质数：这种质数不含数字 0，并且无论去掉多少个前导数字，剩下的部分依然是质数。举个例子，他们会害怕 4632647，因为它不包含数字 0，而且它的每一个前导截断（632647、32647、2647、647、47 和 7）都是质数。

你的任务是，对于给定的数字 $N$，找出有多少个不大于 $N$ 且被 Changu 和 Mangu 害怕的质数。

## 说明/提示

$1 \le T \le 100$

$1 \le N \le 10^6$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2
3
4```

### 输出

```
1
2
2```

# 题解

## 作者：dg114514 (赞：2)

两种解法。

一，素数筛预处理所有“恐惧素数”。具体的，可以从小素数反推。也就是说，可以从只有个位的素数（$2,3,5,7$）一次一次的往左边添加数字，当这个新构造出来的数是素数时，把这个数添加进库（先令 $ans$ 为这个库）里面。可以用类似 dfs 的写法实现。

这个库是无序的，所以先排序。处理每次查询是直接二分第一个大于 $N$ 的库的数然后输出那个数的下标即可。可以用 STL upper_bound 实现。时间复杂度 $O(n\log \log n+T\log |ans|)$ or $O(n+T\log |ans|)$。空间复杂度不用 bitset $O(n+|ans|)$，用 bitset $O(\frac{n}{w}+|ans|)$。

### 参考代码（感觉其他题解的代码有点太长了）：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=1e6;
bitset<N+5>vis;
int p10[]={1,10,100,1000,10000,100000,1000000,10000000};
vector<int>ans;
void get(int x,int d=1){
	ans.pb(x);
	for(int i=1;i<10;i++)
		if(i*p10[d]+x<=N&&!vis[i*p10[d]+x])
			get(i*p10[d]+x,d+1);
}
signed main() {
	vis[1]=1;
	for(int i=2;i<=N;i++)
		if(!vis[i])
			for(int j=i*i;j<=N;j+=i)
				vis[j]=1;
	get(2),get(3),get(5),get(7);//小于 10 的所有素数 
	sort(ans.begin(),ans.end());
	int T,x;
	cin>>T;
	while(T--)
		cin>>x,cout<<upper_bound(ans.begin(),ans.end(),x)-ans.begin()<<"\n";
    return 0;
}
```

二，暴力预处理所有“恐惧素数”。其实也是可行的，素数筛筛出所有素数后一个个枚举所有素数是否满足题目所说的条件。复杂度 $O(n\lg n+T\log n)$。应该也能通过，只是复杂度较劣。（没试过）\
参考代码：先咕咕咕了。

---

## 作者：Aurelia_Veil (赞：1)

# 题解：SP27318 VECTAR8 - Primal Fear

这道题就是线性筛和枚举。

我们需要预处理，可以先使用线性筛筛出 $10^6$ 个质数，然后从 $1$ 到 $N$ 开始枚举，每次枚举都要枚举它的截断数，然后看这些数是否都为质数，在存储每一个 $N$ 的答案，最终输出答案。

代码如下咩：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int PR=1e6+101;
vector<int>g;
bool v[PR];
int t[PR];
void init(){
    v[0]=1;
    v[1]=1;
    for(int i=2;i<=PR-101;i++){
        if(v[i]==0){
            g.push_back(i);
        }
        for(int j=0;j<g.size()&&g[j]*i<=PR-10;j++){
            v[g[j]*i]=1;
            if(i%g[j]==0){
                break;
            }
        }
    }
}
int powk(int x){
    if(x==0){
        return 1;
    }
    if(x==1){
        return 10;
    }
    if(x%2==0){
        int y=powk(x/2);
        return y*y;
    }else{
        return powk(x-1)*10;
    }
}
int main(){
    init();
    for(int i=1;i<=PR-101;i++){
        int now=i;
        queue<int>q;
        while(now){
            q.push(now%10);
            now/=10;
        }
        bool flag=1;
        int cnt=0;
        while(!q.empty()){
            if(q.front()==0){
                flag=0;
            }
            now+=q.front()*powk(cnt);
            cnt++;
            q.pop();
            flag&=(!v[now]);
        }
        t[i]=t[i-1];
        if(flag==1){
            t[i]++;
        }
    }
    int T;
    scanf("%d",&T);
    while(T--){
        int x;
        scanf("%d",&x);
        printf("%d\n",t[x]);
    }
    return 0;
}
```

---

## 作者：Make_China_Great (赞：1)

## 思路

大家都学过筛质数吧。

首先筛出 $1\sim 2\times 10^7$ 所有的质数，再枚举筛出的质数 $i$。

对于每一个质数 $i$，我们分别去掉它的最高位，看看它还是不是质数，如果每一次都是质数，用一个数组 $b$ 记录 $i$，使得 $b_i=1$。

我们利用前缀和预处理出所有的 $1\sim b_i$ 的和，记录在数组 $e$ 中。

最后，我们输入 $n$，直接输出 $e_n$ 即可。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
bool c[10000005]={1,1};
int b[10000005],e[10000005],t,d,i=1,n;
vector<int>a;
signed main(){
	cin>>t;
	while(d<1000005){
		i++;
		if(c[i]==0){
			for(int j=2;j<=1000005/i;j++)
			c[i*j]=1;
			a.push_back(i);
		}
		d++;
	}
	for(int i=0;i<a.size();i++){
		int l=a[i],r=1,u=0;
		while(l>=r){
			r*=10;
			if(c[l%r]||((l/(r/10))%10==0)){
				u=1;
				break;
			}
		}
		if(u==0)b[a[i]]=1;
	}
	for(int i=2;i<=1000005;i++)
	e[i]=b[i]+b[i-1];
	while(t--){
		cin>>n;
		cout<<e[n]<<endl;
	}
}
```

---

## 作者：dmc0702 (赞：0)

# 题解：SP27318 VECTAR8 - Primal Fear
## 思路分析
我们先用筛法筛出 $1 \sim 10^7$ 所有的质数，再枚举筛出的素数 $i$，判断 $i$ 依次去掉最高位是否都为素数，如果是，则标记 $sum_{i}$ 为 $1$。

然后，对 $sum$ 数组进行前缀和即可求出 $1 \sim i$ 中所有的害怕质数。

最后，输入时，仅仅只需要输出 $sum_n$ 即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool vis[10000005];
int sum[10000005];
vector<int> prime;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int t;
	cin>>t;
	int cnt=0,i=1,n=1000005;
	vis[0]=1;vis[1]=1;
	while(cnt<n){
		i++;
		if(vis[i]==0){
			for(int j=2;j<=1000005/i;j++)vis[i*j]=1;
			prime.push_back(i);
		}
		cnt++;
	}
	for(int i=0;i<prime.size();i++){
		bool f=0;
		int i1=prime[i],asd=1;
		while(i1>=asd){
			asd*=10;
			if(vis[i1%asd]||((i1/(asd/10))%10==0)){
				f=1;
				break;
			}
		}
		if(f==0)sum[prime[i]]=1;
	}
	for(int i=2;i<=1000005;i++)sum[i]+=sum[i-1];
	while(t--){
		int n;
		cin>>n;
		cout<<sum[n]<<"\n";
	}
	return 0;
}
```

---

## 作者：liuyuantao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP27318)  
[SPOJ 原题](https://www.spoj.com/problems/VECTAR8/)

我们线性筛出 $10^6$ 以内的质数，之后利用递归枚举数字，显然 $n+10^gk(10^{g-1} \le n < 10^g,1 \le k\le 9)$ 是特殊质数的必要条件是 $n$ 是特殊质数。  
我们每次只枚举特殊质数，其余剪枝，用数组标记后求前缀和即可。  
修正：SPOJ 中 $N\le10^5$。  

[AC code](https://www.luogu.com.cn/record/209322702)
```cpp
#include<bits/stdc++.h>

using namespace std;

#define LL long long

const int N=1e6+3;
LL A[N],Prime[N/2],pw10[10];
LL T,n,m,ans,findP;
bool noPrime[N],iz[N];

void findPrime(int x){//O(n)
    noPrime[1]=1;
	for(int i=2;i<=x;i++){
		if(!noPrime[i])Prime[++findP]=i;
		for(int j=1;j<=findP&&i*Prime[j]<=x;j++){
			noPrime[Prime[j]*i]=1;
			if(i%Prime[j]==0)break;
		}
	}
	return ;
}

void dfs(LL x,LL y){
	if(x==7)return ;
	for(int i=1;i<=9;i++){
		y+=i*pw10[x-1];
		if(!noPrime[y]){
			iz[y]=1;
			dfs(x+1,y);
		}
		y-=i*pw10[x-1];
	}
	return ;
}

int main(){
	ios::sync_with_stdio(false);
	pw10[0]=1;
	for(int i=1;i<=7;i++)pw10[i]=pw10[i-1]*10;
	cin>>T;
	findPrime(1e6);
	dfs(1,0);
	for(int i=1;i<=1e6;i++){
		A[i]=A[i-1]+iz[i];
	}
	while(T--){
		cin>>n;
		cout<<A[n]<<endl;
	}
	
	
	
	
	return 0;
}
```

---

